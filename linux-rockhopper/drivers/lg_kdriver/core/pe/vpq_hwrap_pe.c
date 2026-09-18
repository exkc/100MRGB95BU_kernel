/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file vpq_hwrap.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- master pe kwrap file includes init & misc functions
 *
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj, S(kanthiraj.s@lge.com)
 *	@version	0.1
 *	@note
 *	@date			2011.06.11
 *	@modified date	2015.05.20
 *	@see
 */

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_def.h"
#include "pe_drv.h"
#include "pe_io.h"
#include "pe_cmn.h"
#include "pe_csc.h"
#include "pe_shp.h"
#include "pe_etc.h"
#include "pe_cmg.h"
#include "pe_nrd.h"
#include "pe_hst.h"
#include "pe_hdr.h"	
#include "pe_win.h"
#include "pe_dnt.h"
#include "pe_dcm.h"
#include "pe_kwrap.h"
#include "vpq_hwrap.h"
#include "vpq_hwrap_pe.h"
#ifdef INCLUDE_KDRV_AFE
#include "afe_kwrap.h"
#endif
#ifdef INCLUDE_KDRV_DE
#include "vp_kwrap.h"
#endif

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
/* input(cvi) csc */
const UINT16 g_pe_hwrap_p_input_mtrx_bypass[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0x0000, 0x0000, 	//	1.0000, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000, 	//	0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//	0.0000, 0.0000, 1.0000
const UINT16 g_pe_hwrap_p_input_mtrx_limit[PE_NUM_OF_CSC_COEF]= {
	0x0db0, 0x0000, 0x0000, 	//	0.8555, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000, 	//	0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//	0.0000, 0.0000, 1.0000
const UINT16 g_pe_hwrap_p_input_mtrx_expend[PE_NUM_OF_CSC_COEF]= {
	0x1166, 0x0000, 0x0000, 	//	1.0875, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000, 	//	0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//	0.0000, 0.0000, 1.0000
const UINT16 g_pe_hwrap_p_input_mtrx_expend_cvd[PE_NUM_OF_CSC_COEF]= {
	0x1143, 0x0000, 0x0000, 	//	1.0788, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000, 	//	0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//	0.0000, 0.0000, 1.0000
const UINT16 g_pe_hwrap_p_input_rgb_y709_linear[PE_NUM_OF_CSC_COEF]= {
	0x0b71, 0x0128, 0x0367, 	//	0.7152, 0.0722, 0.2126
	0xf9b1, 0x082f, 0xfe20, 	// -0.3942, 0.5114,-0.1172
	0xf891, 0xff40, 0x082f};	// -0.4645,-0.0469, 0.5114
const UINT16 g_pe_hwrap_p_input_rgb_y709_limit[PE_NUM_OF_CSC_COEF]= {
	0x09cd, 0x00fd, 0x02ea, 	//	0.6124,	0.0618,	0.1821
	0xfa99, 0x0702, 0xfe65, 	// -0.3376,	0.4379,	-0.1003
	0xf9a3, 0xff5c, 0x0702};	// -0.3978,	-0.0402,	0.4379
const UINT16 g_pe_hwrap_p_input_rgb_y601_linear[PE_NUM_OF_CSC_COEF]= {
	0x0964, 0x01d3, 0x04c9, 	//	0.5870, 0.1140, 0.2990
	0xfa94, 0x082f, 0xfd3d, 	// -0.3388, 0.5114,-0.1726
	0xf926, 0xfeab, 0x082f};	// -0.4282,-0.0832, 0.5114
const UINT16 g_pe_hwrap_p_input_rgb_y601_limit[PE_NUM_OF_CSC_COEF]= {
	0x080b, 0x0190, 0x0419, 	//	0.5027, 0.0976, 0.2560
	0xfb59, 0x0706, 0xfda3, 	// -0.2901, 0.4379-0.1478
	0xfa22, 0xfedc, 0x0702};	// -0.3667,-0.0712 0.4379
const UINT16 g_pe_hwrap_p_input_rgb_bt2020_linear[PE_NUM_OF_CSC_COEF]= {
	0x0ad9, 0x00f3, 0x0434, 	//  0.6780, 0.0593, 0.2627
	0xfa1a, 0x082f, 0xfdb7, 	// -0.3686, 0.5114,-0.1428
	0xf87a, 0xff58, 0x082f};	// -0.4703,-0.0411, 0.5114
const UINT16 g_pe_hwrap_p_input_rgb_bt2020_limit[PE_NUM_OF_CSC_COEF]= {
	0x094a, 0x00d0, 0x0399, 	//  0.5806, 0.0508, 0.2250
	0xfaf3, 0x0702, 0xfe0b, 	// -0.3156, 0.4379,-0.1223
	0xf98f, 0xff70, 0x0702};	// -0.4027,-0.0352, 0.4379
const UINT16 g_pe_hwrap_p_input_ofst_bypass[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000, 	//	 0,   0,   0
	0x0000, 0x0000, 0x0000};	//	 0,   0,   0
const UINT16 g_pe_hwrap_p_input_ofst_limit[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000, 	//	 0,   0,   0
	0x0040, 0x0000, 0x0000};	//	64,   0,   0
const UINT16 g_pe_hwrap_p_input_ofst_expend[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000, 	//	 0,   0,   0
	0xffae, 0x0000, 0x0000};	// -82,   0,   0
const UINT16 g_pe_hwrap_p_input_ofst_expend_cvd[PE_NUM_OF_CSC_OFST] = {
	0xff80, 0x0000, 0x0000, 	//-128,   0,   0
	0x0040, 0x0000, 0x0000};	//	64,   0,   0
const UINT16 g_pe_hwrap_p_input_ofst_rgb_y_linear[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000, 	//	 0,   0,   0
	0x0000, 0x0200, 0x0200};	//	 0, 512, 512
const UINT16 g_pe_hwrap_p_input_ofst_rgb_y_limit[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000, 	//	 0,   0,   0
	0x0040, 0x0200, 0x0200};	//	64, 512, 512
const LX_PE_NRD_TNR1_CMN_T g_pe_hwrap_p_tnr1_drvsetting_cmn[VPQ_HWRAP_NRD_NUM] = {\
	{0, 0, \
	{0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, 0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, \
	0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, 0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00}, \
	{0x00, 0x00, 0x00, 0x00, 0x00},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00}\
	}, \
	{0, 1, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, 0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, 0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98}, \
	{0x80, 0x80, 0x60, 0x60, 0x04},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00}\
	}, \
	{0, 2, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4}, \
	{0x80, 0x80, 0x80, 0x80, 0x04},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00}\
	}, \
	{0, 3, \
	{0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, 0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, \
	0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, 0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0}, \
	{0x80, 0x80, 0xa0, 0xa0, 0x04},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00}\
	}, \
	{0, 4, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4}, \
	{0x80, 0x80, 0x80, 0x80, 0x04},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00}\
	} \
};
const LX_PE_NRD_EASY_DNR_CMN_T g_pe_hwrap_p_easy_dnr_cmn[VPQ_HWRAP_NRD_NUM] = {\
	{0, \
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	0x00, 0x00, 0x00}},
	{0, \
	{0x01, 0xD0, 0x01, 0x01, 0x01, 0x20, 0x10, 0x01, 0x01, \
	0x01, 0x01, 0x10}}, \
	{0, \
	{0x01, 0xFF, 0x01, 0x01, 0x01, 0x38, 0x1E, 0x01, 0x01, \
	0x01, 0x01, 0x1B}}, \
	{0, \
	{0x01, 0xFF, 0x01, 0x01, 0x01, 0x50, 0x28, 0x01, 0x01, \
	0x01, 0x01, 0x20}}, \
	{0, \
	{0x01, 0xFF, 0x01, 0x01, 0x01, 0x38, 0x1E, 0x01, 0x01, \
	0x01, 0x01, 0x1B}}
};
const LX_PE_NRD_EASY_DCNT_CMN_T g_pe_hwrap_p_easy_dcnt_cmn[VPQ_HWRAP_NRD_NUM] = {\
	{0, 0,\
	{/*deconnd_____ui off*/
	 0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 0x00,0x00}}, \
	{0, 1,\
	{/*deconnd_____ui low*/
	 0x01,0x01,0x01,0x01,0x40,0x0b,0x04,0x02,0x00,0x16,\
	 0x2c,0xb2}}, \
	{0, 2,\
	{/*deconnd_____ui mid*/
	 0x01,0x01,0x01,0x01,0x80,0x10,0x06,0x03,0x00,0x20,\
	 0x40,0xff}}, \
	{0, 3,\
	{/*deconnd_____ui high*/
	 0x01,0x01,0x01,0x01,0xb0,0x14,0x07,0x03,0x00,0x29,\
	 0x53,0xff}}, \
	{0, 4,\
	{/*deconnd_____ui auto*/
	 0x01,0x01,0x01,0x01,0x40,0x10,0x06,0x03,0x00,0x20,\
	 0x40,0xff}}
};
const LX_PE_CMG_REGION_T g_pe_hwrap_p_cmg_rgn_v0[LX_PE_CMG_REGION_NUM] = {
	{0,	VPQ_HWRAP_CMG_RGN_COL_WHT, \
		{0, 35, 100, 150, 200, 250, 300, 360}, \
		{127, 127, 127, 127, 127, 127, 127, 127}, \
		{0, 5, 10, 15, 17, 21, 24, 27}, \
		{127, 127, 127, 127, 110, 70, 30, 0}, \
		{60, 100, 120, 140, 160, 190, 250, 255}, \
		{0, 45, 65, 80, 100, 80, 50, 20}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_WTB, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 1}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_BLK, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_SKN, \
		{359, 370, 380, 390, 395, 400, 410, 415}, \
		{0, 95, 120, 127, 127, 127, 80, 0}, \
		{30, 40, 50, 60, 90, 95, 98, 100}, \
		{0, 50, 95, 127, 127, 127, 127, 127}, \
		{15, 35, 55, 100, 170, 210, 230, 255}, \
		{0, 70, 127, 127, 127, 60, 30, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_GRN, \
		{60, 68, 75, 80, 120, 130, 140, 150}, \
		{0, 45, 90, 127, 127, 90, 45, 0}, \
		{30, 35, 40, 50, 70, 80, 90, 100}, \
		{0, 35, 70, 127, 127, 127, 127, 127}, \
		{30, 50, 80, 100, 144, 180, 216, 255}, \
		{0, 80, 127, 127, 127, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_BLU, \
		{155, 165, 175, 190, 240, 250, 260, 275}, \
		{0, 75, 127, 127, 127, 127, 100, 0}, \
		{0, 15, 30, 40, 80, 90, 98, 100}, \
		{0, 50, 100, 127, 127, 127, 127, 127}, \
		{0, 50, 70, 90, 100, 140, 245, 255}, \
		{0, 50, 75, 110, 127, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_RED, \
		{320, 325, 330, 335, 363, 366, 372, 375}, \
		{0, 45, 90, 127, 127, 127, 90, 0}, \
		{35, 45, 55, 60, 75, 80, 90, 100}, \
		{0, 50, 100, 127, 127, 127, 127, 127}, \
		{35, 60, 90, 120, 150, 180, 210, 230}, \
		{0, 70, 110, 127, 127, 100, 40, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_YEL, \
		{41, 50, 55, 60, 65, 70, 75, 80}, \
		{0, 45, 90, 127, 127, 90, 45, 0}, \
		{35, 40, 45, 54, 65, 75, 85, 100}, \
		{0, 35, 70, 127, 127, 127, 127, 127}, \
		{20, 50, 75, 108, 144, 180, 216, 255}, \
		{0, 70, 127, 127, 127, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_MGT, \
		{275, 280, 285, 290, 300, 305, 310, 315}, \
		{0, 45, 90, 127, 127, 90, 45, 0}, \
		{0, 25, 40, 50, 60, 70, 90, 100}, \
		{0, 80, 127, 127, 127, 127, 127, 0}, \
		{30, 55, 80, 108, 144, 180, 216, 255}, \
		{0, 60, 127, 127, 127, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_CYN, \
		{150, 158, 167, 175, 184, 192, 201, 210}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R10, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R11, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R12, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R13, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R14, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R15, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}
};
/* cmg region(ver1) */
const LX_PE_CMG_REGION_T g_pe_hwrap_p_cmg_rgn_v1[LX_PE_CMG_REGION_NUM] = {
	{0,	VPQ_HWRAP_CMG_RGN_COL_WHT, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_WTB, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_BLK, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_SKN, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_GRN, \
		{90, 98, 107, 115, 124, 132, 141, 150}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_BLU, \
		{210, 218, 227, 235, 244, 252, 261, 270}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_RED, \
		{330, 338, 347, 355, 364, 372, 381, 390}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 115, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_YEL, \
		{30, 38, 47, 55, 64, 72, 81, 90}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_MGT, \
		{270, 278, 287, 295, 304, 312, 321, 330}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_CYN, \
		{150, 158, 167, 175, 184, 192, 201, 210}, \
		{0, 60, 110, 127, 127, 110, 60, 0}, \
		{15, 27, 39, 52, 64, 76, 88, 100}, \
		{0, 80, 120, 127, 127, 127, 127, 127}, \
		{50, 70, 90, 120, 144, 180, 216, 255}, \
		{0, 20, 50, 90, 110, 127, 127, 127}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R10, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R11, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R12, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R13, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R14, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R15, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}, \
		{0, 0, 0, 0, 0, 0, 0, 0}
	}
};
const LX_PE_CMG_REGION_CTRL_T g_pe_hwrap_p_cmg_rgn_ctrl[LX_PE_CMG_REGION_NUM] = {
	{0,	VPQ_HWRAP_CMG_RGN_COL_WHT,	{0, 0, 0, 0, 25, 0}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_WTB,	{0, 0, 0, 0, 0, 0}, 			0}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_BLK,	{0, 0, 0, 0, 0, 0}, 			0}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_SKN,	{-9, 0, 0, -15, -18, 18}, 		170}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_GRN,	{15, 10, -10, 23, -15, -25}, 	255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_BLU,	{0, 25, 0, -14, 19, -19}, 		255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_RED,	{-10, 15, 0, -5, -5, 10}, 		255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_YEL,	{0, 5, 0, 0, -10, 0}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_MGT,	{0, 30, -5, 0, 15, 5}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_CYN,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R10,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R11,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R12,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R13,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R14,	{0, 0, 0, 0, 0, 0}, 			255}, \
	{0,	VPQ_HWRAP_CMG_RGN_COL_R15,	{0, 0, 0, 0, 0, 0}, 			255}
	};


/* define for default value */
#define VPQ_HWRAP_PE_DYN_COL_INIT		0
#define VPQ_HWRAP_PE_DYN_COL_NORM		1
#define VPQ_HWRAP_PE_DYN_COL_EXPT		2

/* define for db data max size */
#define VPQ_HWRAP_DB_DATA_MAX		2048

#define VPQ_HWRAP_HISTO_BIN_NUM		(32)
#define VPQ_HWRAP_HISTO_DCE_BIN_NUM		(128)

/* preferred color selection */
#define VPQ_HWRAP_PF_COLOR_SKIN		0
#define VPQ_HWRAP_PF_COLOR_BSKY		1
#define VPQ_HWRAP_PF_COLOR_GRASS	2

#define VPQ_HWRAP_CM_REGION_WHITE    0
#define VPQ_HWRAP_CM_REGION_WHT_BLU  1
#define VPQ_HWRAP_CM_REGION_BLACK    2
#define VPQ_HWRAP_CM_REGION_SKIN     3
#define VPQ_HWRAP_CM_REGION_GRN      4
#define VPQ_HWRAP_CM_REGION_BLU      5
#define VPQ_HWRAP_CM_REGION_RED      6
#define VPQ_HWRAP_CM_REGION_YEL      7
#define VPQ_HWRAP_CM_REGION_MGT      8
#define VPQ_HWRAP_CM_REGION_CYN      9
#define VPQ_HWRAP_CM_REGION_A        10
#define VPQ_HWRAP_CM_REGION_B        11
#define VPQ_HWRAP_CM_REGION_C        12
#define VPQ_HWRAP_CM_REGION_D        13
#define VPQ_HWRAP_CM_REGION_E        14
#define VPQ_HWRAP_CM_REGION_F        15

/* fresh color, contrast */
#define VPQ_HWRAP_FC_OFF		0
#define VPQ_HWRAP_FC_LOW		1
#define VPQ_HWRAP_FC_MED		2
#define VPQ_HWRAP_FC_HIGH		3

#define VPQ_HWRAP_DB_TBL_MIN	0
#define VPQ_HWRAP_DB_TBL_MAX	3

/* clear white gain num, default, max */
#define VPQ_HWRAP_CW_GAIN_NUM			3
#define VPQ_HWRAP_CW_GAIN_DEFAULT		192
#define VPQ_HWRAP_CW_GAIN_MAX			255

#if 0	//not_used
#define VPQ_HWRAP_PE_DYN_LUT_NUM		16
#define VPQ_HWRAP_PE_GMC_LUT_NUM		1024
#endif

#undef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
/* 10000 to 4096 */
#define VPQ_HWRAP_10000_TO_4K(_x)	(((_x)<<12)/10000)
/* 4096 to 10000 */
#define VPQ_HWRAP_4K_TO_10000(_x)	(((_x)*10000)/4096)

#define VPQ_HWRAP_COV_RGB2V(r, g, b)	((PE_GET_MAX((r), (g), (b))+PE_GET_MIN((r), (g), (b)))>>1)

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
static vpq_hwrap_info_t _g_vpq_hwrap_info;

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/
static int vpq_hwrap_setsharpness_o20(vpq_hwrap_shp_t *pShpData, UINT32 wId);
static int vpq_hwrap_setsharpness_o22(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version);
static int vpq_hwrap_setsharpness_f20(vpq_hwrap_shp_t *pShpData, UINT32 wId);
static int vpq_hwrap_setsharpness_f22(vpq_hwrap_shp_t *pShpData, UINT32 wId);
// static int vpq_hwrap_setnoisereduction_m19(vpq_hwrap_nr_t *pNrData);
static int vpq_hwrap_setnoisereduction_o26(vpq_hwrap_nr_t *pNrData, UINT32 wId);
static int vpq_hwrap_setnoisereduction_o20_e60_o22_o24(vpq_hwrap_nr_t *pNrData, UINT32 wId);
static int vpq_hwrap_setnoisereduction_f20_f22(vpq_hwrap_nr_t *pNrData, UINT32 wId);
// static int vpq_hwrap_setmpegnoisereduction_m19(vpq_hwrap_mpeg_nr_t *pMpegNrData);
static int vpq_hwrap_setmpegnoisereduction_o26(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId);
static int vpq_hwrap_setmpegnoisereduction_o20_e60_o22(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId);
static int vpq_hwrap_setmpegnoisereduction_f20_f22(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId);
// static int vpq_hwrap_setdecontour_m19(vpq_hwrap_decontour_t *pDecontourData);
static int vpq_hwrap_setdecontour_o20_e60(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId);
static int vpq_hwrap_setdecontour_f20(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId);
static int vpq_hwrap_setsharpness_e60(vpq_hwrap_shp_t *pShpData, UINT32 wId);
static int vpq_hwrap_getoutvalbyinterpol(int in, int *in_tbl, int *out_tbl, UINT8 min, UINT8 max);
static int vpq_hwrap_setdecontour_o22(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId);
static int vpq_hwrap_setdecontour_f22(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId);
static int vpq_hwrap_setdecontour_o26(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId);
static int vpq_hwrap_setdecontour_o24(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId);
static int vpq_hwrap_setsharpness_o24(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version);
static int vpq_hwrap_vsd_setsharpness_o24(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version);
static int vpq_hwrap_sre_setsharpness_o24(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version);
static int vpq_hwrap_setsharpness_o26(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version);
static int vpq_hwrap_vsd_setsharpness_o26(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version);
static int vpq_hwrap_sre_setsharpness_o26(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version);
static int vpq_hwrap_setcmdbdata_o26(unsigned char wId, struct v4l2_ext_cm_info *pCmInfo);
static int vpq_hwrap_setcmdbdata_o24(unsigned char wId, struct v4l2_ext_cm_info *pCmInfo);
/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/
static int _g_vpq_hwrap_blklvl_enable = 0;
static int _g_vpq_hwrap_shp_platform_db_enable = 0x1;
static int _g_vpq_hwrap_tnr_platform_db_enable = 0x1;
static int _g_vpq_hwrap_dnr_platform_db_enable = 0x1;
static int _g_vpq_hwrap_dct_platform_db_enable = 0x1;
static int _g_vpq_hwrap_cen_platform_db_switch = 0x0;
static int _g_vpq_hwrap_picturectrl_csc_switch = 0x0;
static int _g_vpq_hwrap_switch_win_id = 0x0;

/* http://jira.lge.com/issue/browse/SICDTV-15851 */
static uint _g_vpq_hwrap_use_db = 0;//for db bringup(set bootopts lg1k.vpq_use_db=1)
module_param_named(vpq_use_db, _g_vpq_hwrap_use_db, uint, 0644);

/*============================================================================
	Implementation Group
============================================================================*/
void vpq_hwrap_pe_init(void)
{
	__attribute__((unused)) UINT32 temp =0;
	_g_vpq_hwrap_info.dyn_color_init = VPQ_HWRAP_PE_DYN_COL_INIT;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	_g_vpq_hwrap_shp_platform_db_enable = 0xff;
	_g_vpq_hwrap_tnr_platform_db_enable = 0xff;
	_g_vpq_hwrap_dnr_platform_db_enable = 0xff;
	_g_vpq_hwrap_dct_platform_db_enable = 0xff;
	#endif
	#if 0
	if(lx_chip() == LX_CHIP_O26 && !_g_vpq_hwrap_use_db)
	{
		_g_vpq_hwrap_shp_platform_db_enable = 0x0;
		_g_vpq_hwrap_tnr_platform_db_enable = 0x0;
		_g_vpq_hwrap_dnr_platform_db_enable = 0x0;
		_g_vpq_hwrap_dct_platform_db_enable = 0x0;
	}
	#endif
	_g_vpq_hwrap_info.blacklevelinput[0] = VPQ_HWRAP_INPUT_MAX;
	_g_vpq_hwrap_info.blacklevelinput[1] = VPQ_HWRAP_INPUT_MAX;
	_g_vpq_hwrap_info.blacklevelinput[2] = VPQ_HWRAP_INPUT_MAX;
	_g_vpq_hwrap_info.blacklevelinput[3] = VPQ_HWRAP_INPUT_MAX;
	_g_vpq_hwrap_info.blackleveltype[0] = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
	_g_vpq_hwrap_info.blackleveltype[1] = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
	_g_vpq_hwrap_info.blackleveltype[2] = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
	_g_vpq_hwrap_info.blackleveltype[3] = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
	_g_vpq_hwrap_info.pre_blackleveltype[0] = 0xff;
	_g_vpq_hwrap_info.pre_blackleveltype[1] = 0xff;
	_g_vpq_hwrap_info.pre_blackleveltype[2] = 0xff;
	_g_vpq_hwrap_info.pre_blackleveltype[3] = 0xff;
	_g_vpq_hwrap_info.icsc_updatecnt[0]=0;
	_g_vpq_hwrap_info.icsc_updatecnt[1]=0;
	_g_vpq_hwrap_info.icsc_updatecnt[2]=0;
	_g_vpq_hwrap_info.icsc_updatecnt[3]=0;
	_g_vpq_hwrap_info.pre_icsc_updatecnt[0]=0;
	_g_vpq_hwrap_info.pre_icsc_updatecnt[1]=0;
	_g_vpq_hwrap_info.pre_icsc_updatecnt[2]=0;
	_g_vpq_hwrap_info.pre_icsc_updatecnt[3]=0;
	
	#ifdef BUILD_FEATURE_y29_board
		_g_vpq_hwrap_info.year_option = 29;
	#elif defined BUILD_FEATURE_y28_board
		_g_vpq_hwrap_info.year_option = 28;
	#elif defined BUILD_FEATURE_y27_board
		_g_vpq_hwrap_info.year_option = 27;
	#elif defined BUILD_FEATURE_y26_board
		_g_vpq_hwrap_info.year_option = 26;
	#elif defined BUILD_FEATURE_y25_board
		_g_vpq_hwrap_info.year_option = 25;
	#elif defined BUILD_FEATURE_y24_board
		_g_vpq_hwrap_info.year_option = 24;
	#elif defined BUILD_FEATURE_y23_board
		_g_vpq_hwrap_info.year_option = 23;
	#elif defined BUILD_FEATURE_y22_board
		_g_vpq_hwrap_info.year_option = 22;
	#endif
}

int vpq_hwrap_setpicturectrl(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	vpq_hwrap_pic_ctrl_t *p_ctrl;
	LX_PE_CMN1_CONTRAST_T cont_param;
	LX_PE_CMN1_BRIGHTNESS_T bri_param;
	LX_PE_CMN_SATURATION_T sat_param;
	LX_PE_CMN_HUE_T hue_param;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	PE_PRINT_VPQ_PE("v:%d,l:%d,wid:%d\n",p_param->version,p_param->length,p_param->wid);

	p_ctrl = (vpq_hwrap_pic_ctrl_t *)p_param->p_data;
	PE_PRINT_CMN("[%d] c:%d,b:%d,s:%d,h:%d,\n",\
		p_param->wid,p_ctrl->contrast,p_ctrl->brightness,p_ctrl->saturation,p_ctrl->hue);

	cont_param.win_id = bri_param.win_id = (LX_PE_WIN_ID)p_param->wid;
	sat_param.win_id = hue_param.win_id = (LX_PE_WIN_ID)p_param->wid;

	cont_param.contrast = (UINT16)p_ctrl->contrast;
	bri_param.brightness = (UINT16)p_ctrl->brightness;
	sat_param.saturation = (UINT16)p_ctrl->saturation;
	hue_param.hue = (UINT16)p_ctrl->hue;
	if(p_param->version == 0x60)// @O24, contrast bit increased 10bit -> 12bit.
	{
		if (cont_param.contrast>4095)			cont_param.contrast=4095;
		else if (cont_param.contrast<0) 		cont_param.contrast=0;
	}
	else
	{
		if (cont_param.contrast>1023)			cont_param.contrast=1023;
		else if (cont_param.contrast<0) 		cont_param.contrast=0;
	}
	if (bri_param.brightness>1023)		bri_param.brightness=1023;
	else if (bri_param.brightness<0)		bri_param.brightness=0;
	if (sat_param.saturation>255) 		sat_param.saturation=255;
	else if (sat_param.saturation<0)		sat_param.saturation=0;
	if (hue_param.hue>255) 				hue_param.hue=255;
	else if (hue_param.hue<0)				hue_param.hue=0;

	/* contrast/brightness
	*** E60/O20/O24/O26 : vspyc
	*** O22/M23     : outputcsc
	***************************/
	if(PE_KDRV_VER_O26 || PE_KDRV_VER_O24)//contast/brigtness : outputcsc -> vspyc roll-back from TVPLAT-139852
	{
		if(p_param->version == 0x60) // @O24, contrast bit increased 10bit -> 12bit. 
		{
			if (cont_param.contrast<2048) //adjust satuation
			{
				/* saturation control according to contrast. 1/2048=0.00048828125 */
				/* saturation = saturation * (contrast * 0.00048828125) */
				sat_param.saturation = (sat_param.saturation * cont_param.contrast)>>11;
			}
			//cont_param.contrast = cont_param.contrast*4;
		}
		else
		{
			if (cont_param.contrast<512) //adjust satuation
			{
				/* saturation control according to contrast. 1/512=0.001953125 */
				/* saturation = saturation * (contrast * 0.001953125) */
				sat_param.saturation = (sat_param.saturation * cont_param.contrast)>>9;
			}
			cont_param.contrast = cont_param.contrast*4; //till DB changed for 12bit, contrast value should be quadruple
		}
		
		cont_param.setbycsc =0;
		bri_param.setbycsc =0;
	}
	else if(PE_KDRV_VER_O20 || PE_KDRV_VER_E60)//contast/brigtness : vspyc
	{
		if (cont_param.contrast<512)//adjust satuation
		{
			/* saturation control according to contrast. 1/512=0.001953125 */
			/* saturation = saturation * (contrast * 0.001953125) */
			sat_param.saturation = (sat_param.saturation * cont_param.contrast)>>9;
		}
		cont_param.setbycsc =0;
		bri_param.setbycsc =0;
	}
	else //O22/M23 contast/brigtness : vspyc -> outputcsc, do not adjust satuation TVPLAT-139852
	{
		cont_param.setbycsc =1;
		bri_param.setbycsc =1;
	}
	PE_PRINT_CMN("[%d] c:%d,b:%d,s:%d,h:%d, c:%d,b:%d,s:%d,h:%d\n",\
		p_param->wid,p_ctrl->contrast,p_ctrl->brightness,p_ctrl->saturation,p_ctrl->hue,\
		cont_param.contrast,bri_param.brightness,sat_param.saturation,hue_param.hue);
	/* contrast */
	ret = PE_CMN_SetContrast((void *)&cont_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_SetContrast()\n");

	/* brightness */
	ret = PE_CMN_SetBrightness((void *)&bri_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_SetBrightness()\n");

	/* saturation */
	ret = PE_CMN_SetSaturation(&sat_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_SetSaturation()\n");

	/* hue */
	ret = PE_CMN_SetHue(&hue_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_SetHue()\n");

	return ret;
}

int vpq_hwrap_getpicturectrl(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	vpq_hwrap_pic_ctrl_t *p_ctrl;
	LX_PE_CMN1_CONTRAST_T cont_param;
	LX_PE_CMN1_BRIGHTNESS_T bri_param;
	LX_PE_CMN_SATURATION_T sat_param;
	LX_PE_CMN_HUE_T hue_param;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	PE_PRINT_VPQ_PE("v:%d,l:%d,wid:%d\n",p_param->version,p_param->length,p_param->wid);

	p_ctrl = (vpq_hwrap_pic_ctrl_t *)p_param->p_data;

	cont_param.win_id = bri_param.win_id = (LX_PE_WIN_ID)p_param->wid;
	sat_param.win_id = hue_param.win_id = (LX_PE_WIN_ID)p_param->wid;

	/* contrast */
	ret = PE_CMN_GetContrast((void *)&cont_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_GetContrast()\n");

	/* brightness */
	ret = PE_CMN_GetBrightness((void *)&bri_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_GetBrightness()\n");

	/* saturation */
	ret = PE_CMN_GetSaturation(&sat_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_GetSaturation()\n");

	/* hue */
	ret = PE_CMN_GetHue(&hue_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_GetHue()\n");

	p_ctrl->contrast = (int)cont_param.contrast;
	p_ctrl->brightness = (int)bri_param.brightness;
	p_ctrl->saturation = (int)sat_param.saturation;
	p_ctrl->hue = (int)hue_param.hue;

	PE_PRINT_DEBUG("[%d] c:%d,b:%d,s:%d,h:%d, c:%d,b:%d,s:%d,h:%d\n",\
		p_param->wid,cont_param.contrast,bri_param.brightness,sat_param.saturation,hue_param.hue,\
		p_ctrl->contrast,p_ctrl->brightness,p_ctrl->saturation,p_ctrl->hue);

	return ret;
}

int vpq_hwrap_setblacklevelenable(int enable)
{
	_g_vpq_hwrap_blklvl_enable = enable;
	return 0;
}

int vpq_hwrap_getblacklevelenable(void)
{
	return _g_vpq_hwrap_blklvl_enable;
}

int vpq_hwrap_getblackleveltype(UINT32 wId)
{
	return _g_vpq_hwrap_info.blackleveltype[wId];
}

vpq_hwrap_info_t vpq_hwrap_get_vpq_hwrap_info(void)
{
	return _g_vpq_hwrap_info;
}
int vpq_hwrap_updatecnt_icsc(UINT32 wId)
{
	_g_vpq_hwrap_info.icsc_updatecnt[wId]++;
	return 0;
}
int vpq_hwrap_saveprecnt_icsc(UINT32 wId, int cnt)
{
	_g_vpq_hwrap_info.pre_icsc_updatecnt[wId] =cnt;
	return 0;
}

int vpq_hwrap_setpreblacklevel(UINT32 wId,int enable)
{
	_g_vpq_hwrap_info.pre_blackleveltype[wId] = enable;
	return 0;
}

int vpq_hwrap_setblacklevel(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	vpq_hwrap_blacklevel_t *p_ctrl;
	LX_PE_CSC_INPUT_T csc_param;
	LX_PE_CMN_LEVEL_CTRL_T lvl_param;
	LX_PE_CMN_VCP_LEVEL_CTRL_T vcp_lvl_param;

	if (0==vpq_hwrap_getblacklevelenable())	{PE_PRINT_VPQ_PE("stop\n");return RET_OK;}
	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	p_ctrl = (vpq_hwrap_blacklevel_t *)p_param->p_data;


	PE_PRINT_VPQ_PE("v:%d,l:%d,wid:%d, bl:%d,inf:%d\n",\
		p_param->version,p_param->length,p_param->wid,p_ctrl->blacklevel,p_ctrl->inputinfo);

#ifdef INCLUDE_KDRV_DE
	vp_kwrap_updateinputcschistory(0);
#endif

	/* 1. black level for CVD */
	if (p_ctrl->inputinfo==VPQ_HWRAP_INPUT_ATV || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_AV || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_SCARTRGB)
	{
		//PE_PRINT_VPQ_PE("cvd_set_blacklevel bl:%d\n",p_ctrl->blacklevel);
#ifdef INCLUDE_KDRV_AFE
		ret = afe_kwrap_cvd_set_blacklevel((UINT32)p_ctrl->blacklevel);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. afe_kwrap_cvd_set_blacklevel()\n");
#endif
	}

	/* 2. black level for cvi input */
	if (p_ctrl->inputinfo==VPQ_HWRAP_INPUT_ATV || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_AV || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_SCARTRGB || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_COMP || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_RGB_PC || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_HDMI_TV || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_HDMI_PC)
	{
		csc_param.win_id = (LX_PE_WIN_ID)p_param->wid;
		csc_param.enable = 1;
		csc_param.matrix[0] = p_ctrl->data.cs00;
		csc_param.matrix[1] = p_ctrl->data.cs01;
		csc_param.matrix[2] = p_ctrl->data.cs02;
		csc_param.matrix[3] = p_ctrl->data.cs10;
		csc_param.matrix[4] = p_ctrl->data.cs11;
		csc_param.matrix[5] = p_ctrl->data.cs12;
		csc_param.matrix[6] = p_ctrl->data.cs20;
		csc_param.matrix[7] = p_ctrl->data.cs21;
		csc_param.matrix[8] = p_ctrl->data.cs22;
		csc_param.offset[0] = p_ctrl->data.cs03;
		csc_param.offset[1] = p_ctrl->data.cs13;
		csc_param.offset[2] = p_ctrl->data.cs23;
		csc_param.offset[3] = p_ctrl->data.cs04;
		csc_param.offset[4] = p_ctrl->data.cs14;
		csc_param.offset[5] = p_ctrl->data.cs24;

		PE_PRINT_VPQ_PE("csc[%d],%d, %04x,%04x,%04x,%04x,%04x, %04x,%04x,%04x,%04x,%04x, %04x,%04x,%04x,%04x,%04x\n",\
			csc_param.win_id,csc_param.enable,\
			csc_param.matrix[0],csc_param.matrix[1],csc_param.matrix[2],csc_param.offset[0],csc_param.offset[3],\
			csc_param.matrix[3],csc_param.matrix[4],csc_param.matrix[5],csc_param.offset[1],csc_param.offset[4],\
			csc_param.matrix[6],csc_param.matrix[7],csc_param.matrix[8],csc_param.offset[2],csc_param.offset[5]);
		if(PE_KDRV_VER_O20)
			ret = KWRAP_PE_SetInputCscParam(&csc_param);
		else
			ret = PE_CSC_SetInputCsc(&csc_param);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CSC_SetInputCsc()\n");
	}

	/* 3. black level for mvi input */
	lvl_param.win_id = vcp_lvl_param.win_id = (LX_PE_WIN_ID)p_param->wid;
	lvl_param.center = 0;
	lvl_param.tp_on = 0;
	if (PE_KDRV_VER_M17CX &&
		((p_ctrl->inputinfo == VPQ_HWRAP_INPUT_MEDIA_MOVIE) ||
		(p_ctrl->inputinfo == VPQ_HWRAP_INPUT_CAMERA) ||
		(p_ctrl->inputinfo == VPQ_HWRAP_INPUT_MEDIA_PHOTO)))
	{
		lvl_param.gain = 128;
		lvl_param.offset = 512;
		vcp_lvl_param.enable = 0x1;
		vcp_lvl_param.center_position = 0;
		vcp_lvl_param.saturation = 128;

		if (p_ctrl->blacklevel == 1)
		{
			vcp_lvl_param.contrast = 440; // 110 * 4
			vcp_lvl_param.brightness = 576;
		}
		else
		{
			vcp_lvl_param.contrast = 512; // 128 * 4
			vcp_lvl_param.brightness = 512;
		}
	}
	else if (p_ctrl->inputinfo==VPQ_HWRAP_INPUT_MEDIA_MOVIE || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_CAMERA)
	{
		if (p_ctrl->blacklevel == 1)
		{
			/* gain : 110 = 128 * 0.855469 */
			lvl_param.gain = 110;
			/* offset : 576(=512+64, 10bit) */
			lvl_param.offset = 576;
		}
		else
		{
			/* gain : 128 * 1.0000 */
			lvl_param.gain = 128;
			/* offset : 512(10bit) */
			lvl_param.offset = 512;
		}
		//vcp level bypass
		vcp_lvl_param.contrast = 512;
		vcp_lvl_param.brightness = 512;
		vcp_lvl_param.enable = 0x0;
		vcp_lvl_param.center_position = 0;
		vcp_lvl_param.saturation = 128;
	}
	else if(p_ctrl->inputinfo==VPQ_HWRAP_INPUT_MEDIA_PHOTO)
	{
		if (p_ctrl->blacklevel == 1)
		{
			/* gain : 128 * 1.0000 */
			lvl_param.gain = 128;
			/* offset : 512(10bit) */
			lvl_param.offset = 512;

			//vcp level on
			vcp_lvl_param.contrast = 440; //110*4
			vcp_lvl_param.brightness = 576;
			vcp_lvl_param.enable = 0x1;
			vcp_lvl_param.center_position = 0;
			vcp_lvl_param.saturation = 128;
		}
		else
		{
			/* gain : 128 * 1.0000 */
			lvl_param.gain = 128;
			/* offset : 512(10bit) */
			lvl_param.offset = 512;

			//vcp level on
			vcp_lvl_param.contrast = 512; //128*4
			vcp_lvl_param.brightness = 512;
			vcp_lvl_param.enable = 0x1;
			vcp_lvl_param.center_position = 0;
			vcp_lvl_param.saturation = 128;
		}
	}
	else if (p_ctrl->inputinfo==VPQ_HWRAP_INPUT_PVR_ATV || \
		p_ctrl->inputinfo==VPQ_HWRAP_INPUT_PVR_AV)
	{
		if (p_ctrl->blacklevel == 1)
		{
			/* gain : 128 * 1.0000 */
			lvl_param.gain = 128;
			/* offset : 512(10bit) */
			lvl_param.offset = 512;
		}
		else
		{
			/* gain : 137 = 128 * 1.0788(y=1.0788(x-128)+64)) */
			lvl_param.gain = 137;
			/* offset : 438(=512-74.0864, 10bit)(y=1.0788(x-128)+64)) */
			lvl_param.offset = 438;
		}
		//vcp level bypass
		vcp_lvl_param.contrast = 512;
		vcp_lvl_param.brightness = 512;
		vcp_lvl_param.enable = 0x0;
		vcp_lvl_param.center_position = 0;
		vcp_lvl_param.saturation = 128;
	}
	else
	{
		/* gain : 128 * 1.0000 */
		lvl_param.gain = 128;
		/* offset : 512(10bit) */
		lvl_param.offset = 512;

		//vcp level bypass
		vcp_lvl_param.contrast = 512;
		vcp_lvl_param.brightness = 512;
		vcp_lvl_param.enable = 0x0;
		vcp_lvl_param.center_position = 0;
		vcp_lvl_param.saturation = 128;
	}

	PE_PRINT_VPQ_PE("lvl[%d] o,c,g,t:%d,%d,%d,%d, vcp lvl[%d] e,ct,c,b,s:%d,%d,%d,%d,%d\n",\
		lvl_param.win_id,lvl_param.offset,lvl_param.center,lvl_param.gain,lvl_param.tp_on,\
		vcp_lvl_param.win_id,vcp_lvl_param.enable,vcp_lvl_param.center_position,\
		vcp_lvl_param.contrast,vcp_lvl_param.brightness,vcp_lvl_param.saturation);
	if(PE_KDRV_VER_O20)
		ret = KWRAP_PE_SetLevelCtrl(&lvl_param);
	else
		ret = PE_CMN_SetLevelCtrl(&lvl_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_SetLevelCtrl()\n");

	if(PE_KDRV_VER_O20)
		ret = KWRAP_PE_SetVcpLevelCtrl(&vcp_lvl_param);
	else
		ret = PE_CMN_SetVcpLevelCtrl(&vcp_lvl_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_SetVcpLevelCtrl()\n");

	return ret;
}

int vpq_hwrap_setblacklevel2(struct v4l2_ext_vpq_cmn_data *p_param)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) struct v4l2_ext_vpq_black_level_info_v2 *p_ctrl;
	__attribute__((unused)) LX_PE_CSC_INPUT_T csc_param;
	__attribute__((unused)) LX_PE_CMN_LEVEL_CTRL_T lvl_param;
	__attribute__((unused)) LX_PE_CMN_VCP_LEVEL_CTRL_T vcp_lvl_param;
	__attribute__((unused)) const UINT16 *p_mtrx, *p_ofst;
	__attribute__((unused)) unsigned char current_input;
	__attribute__((unused)) UINT32 matching_type; /*v4l2_ext_vpq_black_level_type_v2, black level enum changed by HE SICREQ-520 */

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");
	
	p_ctrl = (struct v4l2_ext_vpq_black_level_info_v2 *)p_param->p_data;
	matching_type = p_ctrl->black_level_type;// initalize as PQDB value
	PE_PRINT_VPQ_PE("v:%d,l:%d,wid:%d, ui_value:%d, curr_input:%d, color_space:%d, black_level_type:%d\n",\
		p_param->version,p_param->length,p_param->wid,p_ctrl->ui_value,p_ctrl->curr_input,\
		p_ctrl->color_space, p_ctrl->black_level_type);

#ifdef INCLUDE_KDRV_DE
	vp_kwrap_updateinputcschistory(0);
#endif

	/* 3. black level for mvi input */
	lvl_param.win_id = vcp_lvl_param.win_id = (LX_PE_WIN_ID)p_param->wid;
	lvl_param.center = 0;
	lvl_param.tp_on = 0;
	/* subpath blacklevel ctrl @airplay input SICREQ-274, AVTASK-729*/
	if (p_param->wid == 1 && p_param->version < 0x50)
		current_input = VPQ_HWRAP_INPUT_MEDIA_MOVIE;
	else
		current_input = p_ctrl->curr_input;

	if ((current_input == VPQ_HWRAP_INPUT_MEDIA_MOVIE) ||
		(current_input == VPQ_HWRAP_INPUT_CAMERA) ||
		(current_input == VPQ_HWRAP_INPUT_MEDIA_PHOTO))
	{
		lvl_param.gain = 128;
		lvl_param.offset = 512;
		vcp_lvl_param.enable = 0x1;
		vcp_lvl_param.center_position = 0;
		vcp_lvl_param.saturation = 128;

		if (p_ctrl->ui_value == 1)
		{
			vcp_lvl_param.contrast = 440; // 110 * 4
			vcp_lvl_param.brightness = 576;
		}
		else
		{
			vcp_lvl_param.contrast = 512; // 128 * 4
			vcp_lvl_param.brightness = 512;
		}
	}
	else if (current_input==VPQ_HWRAP_INPUT_PVR_ATV || \
			current_input==VPQ_HWRAP_INPUT_PVR_AV)
	{
		if (p_ctrl->ui_value == 1)
		{
			/* gain : 128 * 1.0000 */
			lvl_param.gain = 128;
			/* offset : 512(10bit) */
			lvl_param.offset = 512;
		}
		else
		{
			/* gain : 137 = 128 * 1.0788(y=1.0788(x-128)+64)) */
			lvl_param.gain = 137;
			/* offset : 438(=512-74.0864, 10bit)(y=1.0788(x-128)+64)) */
			lvl_param.offset = 438;
		}
		//vcp level bypass
		vcp_lvl_param.contrast = 512;
		vcp_lvl_param.brightness = 512;
		vcp_lvl_param.enable = 0x0;
		vcp_lvl_param.center_position = 0;
		vcp_lvl_param.saturation = 128;
	}
	else
	{
		/* gain : 128 * 1.0000 */
		lvl_param.gain = 128;
		/* offset : 512(10bit) */
		lvl_param.offset = 512;

		//vcp level bypass
		vcp_lvl_param.contrast = 512;
		vcp_lvl_param.brightness = 512;
		vcp_lvl_param.enable = 0x0;
		vcp_lvl_param.center_position = 0;
		vcp_lvl_param.saturation = 128;
	}

	PE_PRINT_DEBUG("lvl[%d] o,c,g,t:%d,%d,%d,%d, vcp lvl[%d] e,ct,c,b,s:%d,%d,%d,%d,%d\n",\
		lvl_param.win_id,lvl_param.offset,lvl_param.center,lvl_param.gain,lvl_param.tp_on,\
		vcp_lvl_param.win_id,vcp_lvl_param.enable,vcp_lvl_param.center_position,\
		vcp_lvl_param.contrast,vcp_lvl_param.brightness,vcp_lvl_param.saturation);
	if(PE_KDRV_VER_O20)
		ret = KWRAP_PE_SetLevelCtrl(&lvl_param);
	else
		ret = PE_CMN_SetLevelCtrl(&lvl_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_SetLevelCtrl()\n");

	if(PE_KDRV_VER_O20)
		ret = KWRAP_PE_SetVcpLevelCtrl(&vcp_lvl_param);
	else
		ret = PE_CMN_SetVcpLevelCtrl(&vcp_lvl_param);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CMN_SetVcpLevelCtrl()\n");

	/* 1. black level for CVD */
	if (p_ctrl->curr_input==VPQ_HWRAP_INPUT_ATV || \
		p_ctrl->curr_input==VPQ_HWRAP_INPUT_AV || \
		p_ctrl->curr_input==VPQ_HWRAP_INPUT_SCARTRGB)
	{
#ifdef INCLUDE_KDRV_AFE
		ret = afe_kwrap_cvd_set_blacklevel((UINT32)p_ctrl->ui_value);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. afe_kwrap_cvd_set_blacklevel()\n");
#endif
	}

	/* 2. black level for cvi input */
	if (p_ctrl->curr_input==VPQ_HWRAP_INPUT_ATV || \
		p_ctrl->curr_input==VPQ_HWRAP_INPUT_AV || \
		p_ctrl->curr_input==VPQ_HWRAP_INPUT_SCARTRGB || \
		p_ctrl->curr_input==VPQ_HWRAP_INPUT_COMP || \
		p_ctrl->curr_input==VPQ_HWRAP_INPUT_RGB_PC || \
		p_ctrl->curr_input==VPQ_HWRAP_INPUT_HDMI_TV || \
		p_ctrl->curr_input==VPQ_HWRAP_INPUT_HDMI_PC)
	{
		csc_param.win_id = (LX_PE_WIN_ID)p_param->wid;
		/*black level enum changed by HE SICREQ-520 */
		if(p_param->version >=  0x60)
		{
			switch (p_ctrl->black_level_type)
			{
				case V4L2_EXT_VPQ_BLK_LVL_Y709_LINEAR_LIMIT_HIGH:
					matching_type = V4L2_EXT_VPQ_BLACKLEVEL_Y709_LINEAR_LIMIT_HIGH;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_Y709_BYPASS:
					matching_type = V4L2_EXT_VPQ_BLK_LVL_Y709_BYPASS;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_Y709_COMP_LOW:
					matching_type = V4L2_EXT_VPQ_BLK_LVL_Y709_COMP_LOW;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_AV_RF_EXTENSION:
					matching_type = V4L2_EXT_VPQ_BLACKLEVEL_AV_RF_EXTENSION;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT709_LIMIT_LIMIT:
					matching_type = V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LINEAR_LOW;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT709_LIMIT_FULL:
					matching_type = V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LIMIT_HIGH;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT709_FULL_LIMIT:
					matching_type = V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LINEAR_LOW;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT709_FULL_FULL:
					matching_type = V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LIMIT_HIGH;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT2020_LIMIT_LIMIT:
					matching_type = V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LINEAR_LOW;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT2020_LIMIT_FULL:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LIMIT_HIGH;
					break;				
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT2020_FULL_LIMIT:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LINEAR_LOW;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT2020_FULL_FULL:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LIMIT_HIGH;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT601_LIMIT_LIMIT:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LINEAR_LOW;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT601_LIMIT_FULL:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LIMIT_HIGH;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT601_FULL_LIMIT:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LINEAR_LOW;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_RGB_BT601_FULL_FULL:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LIMIT_HIGH;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_YCBCR_LIMIT_LIMIT:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_YCBCR_LIMIT_FULL:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_Y709_LINEAR_LIMIT_HIGH;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_YCBCR_FULL_LIMIT:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
					break;
				case V4L2_EXT_VPQ_BLK_LVL_YCBCR_FULL_FULL:
					matching_type =  V4L2_EXT_VPQ_BLACKLEVEL_Y709_LINEAR_LIMIT_HIGH;
					break;
				default:
					matching_type = V4L2_EXT_VPQ_BLK_LVL_MAX_INDEX;
					break;
			}
			PE_PRINT_NOTI("v:%d,wid:%d,re-matching black_level_type:%d -> %d\n",
				p_param->version,p_param->wid,p_ctrl->black_level_type, matching_type);
		}
		else
		{
			matching_type = p_ctrl->black_level_type;
		}

		if(p_param->wid >= 1)
		{
			if(current_input >= VPQ_HWRAP_INPUT_ATV && current_input<=VPQ_HWRAP_INPUT_HDMI_PC)
			{
				_g_vpq_hwrap_info.blacklevelinput[p_param->wid] = (int)p_ctrl->curr_input;
				_g_vpq_hwrap_info.blackleveltype[p_param->wid]	= (int)matching_type;
		#ifdef INCLUDE_KDRV_DE
				vp_kwrap_updateinputcschistory(p_param->wid);
		#endif
			}
			return ret;
		}

		csc_param.enable = (1 + matching_type);//see LX_PE_ICSC_TYPE
		switch (matching_type)
		{
			case V4L2_EXT_VPQ_BLACKLEVEL_Y709_LINEAR_LIMIT_HIGH:
				p_mtrx = g_pe_hwrap_p_input_mtrx_limit;
				p_ofst = g_pe_hwrap_p_input_ofst_limit;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS:
				p_mtrx = g_pe_hwrap_p_input_mtrx_bypass;
				p_ofst = g_pe_hwrap_p_input_ofst_bypass;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LINEAR_LOW:
				p_mtrx = g_pe_hwrap_p_input_rgb_y709_linear;
				p_ofst = g_pe_hwrap_p_input_ofst_rgb_y_linear;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LIMIT_HIGH:
				p_mtrx = g_pe_hwrap_p_input_rgb_y709_limit;
				p_ofst = g_pe_hwrap_p_input_ofst_rgb_y_limit;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_Y709_COMP_LOW:
				p_mtrx = g_pe_hwrap_p_input_mtrx_expend;
				p_ofst = g_pe_hwrap_p_input_ofst_expend;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_AV_RF_EXTENSION:
				p_mtrx = g_pe_hwrap_p_input_mtrx_expend_cvd;
				p_ofst = g_pe_hwrap_p_input_ofst_expend_cvd;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LINEAR_LOW:
				p_mtrx = g_pe_hwrap_p_input_rgb_bt2020_linear;
				p_ofst = g_pe_hwrap_p_input_ofst_rgb_y_linear;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LIMIT_HIGH:
				p_mtrx = g_pe_hwrap_p_input_rgb_bt2020_limit;
				p_ofst = g_pe_hwrap_p_input_ofst_rgb_y_limit;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LINEAR_LOW:
				p_mtrx = g_pe_hwrap_p_input_rgb_y601_linear;
				p_ofst = g_pe_hwrap_p_input_ofst_rgb_y_linear;
				break;
			case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LIMIT_HIGH:
				p_mtrx = g_pe_hwrap_p_input_rgb_y601_limit;
				p_ofst = g_pe_hwrap_p_input_ofst_rgb_y_limit;
				break;
			default:
				p_mtrx = g_pe_hwrap_p_input_mtrx_bypass;
				p_ofst = g_pe_hwrap_p_input_ofst_bypass;
				break;
		}
		memcpy(csc_param.matrix, p_mtrx, sizeof(UINT16) * PE_NUM_OF_CSC_COEF);
		memcpy(csc_param.offset, p_ofst, sizeof(UINT16) * PE_NUM_OF_CSC_OFST);
		PE_PRINT_DEBUG("csc[%d],%d, %04x,%04x,%04x,%04x,%04x, %04x,%04x,%04x,%04x,%04x, %04x,%04x,%04x,%04x,%04x\n",\
			csc_param.win_id,csc_param.enable,\
			csc_param.matrix[0],csc_param.matrix[1],csc_param.matrix[2],csc_param.offset[0],csc_param.offset[3],\
			csc_param.matrix[3],csc_param.matrix[4],csc_param.matrix[5],csc_param.offset[1],csc_param.offset[4],\
			csc_param.matrix[6],csc_param.matrix[7],csc_param.matrix[8],csc_param.offset[2],csc_param.offset[5]);
		if(PE_KDRV_VER_O20)
			ret = KWRAP_PE_SetInputCscParam(&csc_param);
		else
			ret = PE_CSC_SetInputCsc(&csc_param);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_CSC_SetInputCsc()\n");
		_g_vpq_hwrap_info.blackleveltype[p_param->wid]  = (int)matching_type;
	}
	_g_vpq_hwrap_info.blacklevelinput[p_param->wid] = (int)p_ctrl->curr_input;
	return ret;
}

int vpq_hwrap_gethistodata(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	UINT8 i=0;
	struct v4l2_ext_vpq_dc2p_histodata_info *pHistoInfo;
	vpq_hwrap_ext_histodata_info *pHistoInfo2;
	// LX_PE_HST_HISTO_INFO_T cur_param;
	//static LX_PE_HST_HISTO_INFO_T pre_param;
	LX_PE_HST_HISTO1_INFO_T cur_param1;
	static LX_PE_HST_HISTO1_INFO_T pre_param1;
	unsigned int tmp_dce_bin[128];

	VPQ_HWRAP_CHECK_CODE(!p_param, return RET_ERROR, "Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data, return RET_ERROR, "Error. p_data is null.\n");
	if(p_param->version == 0x1)
		pHistoInfo = (struct v4l2_ext_vpq_dc2p_histodata_info *)p_param->p_data;
	else if(p_param->version == 0x2)
		pHistoInfo2 = (vpq_hwrap_ext_histodata_info *)p_param->p_data;

	cur_param1.win_id = LX_PE_WIN_0;
	if (KWRAP_PE_IsMuteOn(LX_PE_WIN_0)&& KWRAP_PE_IsMuteOn(LX_PE_WIN_1)&& KWRAP_PE_IsMuteOn(LX_PE_WIN_2)&& KWRAP_PE_IsMuteOn(LX_PE_WIN_3))
	{
		memcpy(&cur_param1, &pre_param1, sizeof(LX_PE_HST_HISTO1_INFO_T));
	}
	else
	{
		cur_param1.domain = LX_PE_YC_DOMAIN;
		if(PE_KDRV_VER_O20)
			ret = KWRAP_PE_GetHistogramInfo((void *)&cur_param1);
		else
			ret = PE_HST_GetHistogramInfo((void *)&cur_param1);
		if (ret)
		{
			if(p_param->version == 0x1)
				pHistoInfo->peak_high = 0xffffffff;
			else if(p_param->version == 0x2)
				pHistoInfo2->peak_high = 0xffffffff;
			ret = RET_OK;
			return ret;
		}
		memcpy(&pre_param1, &cur_param1, sizeof(LX_PE_HST_HISTO1_INFO_T));
	}

	if (cur_param1.histo_ready)
	{
		if(p_param->version == 0x1)//til no ready for new DCE bin (128)
		{
			for (i = 0 ; i < VPQ_HWRAP_HISTO_DCE_BIN_NUM; i++)
			{
				tmp_dce_bin[i] = cur_param1.histogram[i];
				//PE_PRINT_ETC("[%d] hist : %d\n",i,tmp_dce_bin[i]);
			}
			for (i = 0 ; i < VPQ_HWRAP_HISTO_BIN_NUM; i++)
			{
				pHistoInfo->chrm_bin[i] = \
					cur_param1.histogram[i+VPQ_HWRAP_HISTO_DCE_BIN_NUM];
				pHistoInfo->hue_bin[i] = \
					cur_param1.histogram[i+VPQ_HWRAP_HISTO_DCE_BIN_NUM+VPQ_HWRAP_HISTO_BIN_NUM];
				pHistoInfo->bin[i] = tmp_dce_bin[i*4] + tmp_dce_bin[i*4+1] + tmp_dce_bin[i*4+2]+ tmp_dce_bin[i*4+3];
			}
			
			pHistoInfo->skin_count = GET_BITS(cur_param1.status[4], 0, 23);
			if (cur_param1.domain == LX_PE_YC_DOMAIN)
			{
				pHistoInfo->apl = cur_param1.average[0];	//10bit
			}
			else	//LX_PE_HSV_DOMAIN
			{
				/**
				* s=(max(rgb)-min(rgb))/max(rgb), v=max(rgb),
				* v'=(1-s*0.5)v=(max(rgb)+min(rgb))*0.5
				*/
				pHistoInfo->apl = VPQ_HWRAP_COV_RGB2V(cur_param1.average[0], \
					cur_param1.average[1], cur_param1.average[2]);	//10bit
			}

			pHistoInfo->min = cur_param1.min;
			pHistoInfo->max = cur_param1.max;
			pHistoInfo->peak_low = cur_param1.min;
			pHistoInfo->peak_high = cur_param1.max;

			pHistoInfo->sat_status = cur_param1.status[5];
			pHistoInfo->diff_sum = GET_BITS(cur_param1.status[3], 0, 22);
			pHistoInfo->motion = cur_param1.status[6];
			pHistoInfo->texture = cur_param1.status[7];
		}
		else if(p_param->version == 0x2)
		{
			for (i = 0 ; i < VPQ_HWRAP_HISTO_DCE_BIN_NUM; i++)
			{
				pHistoInfo2->bin[i] = cur_param1.histogram[i];
				PE_PRINT_ETC("[%d] hist : %d\n",i,pHistoInfo2->bin[i]);
			}
			for (i = 0 ; i < VPQ_HWRAP_HISTO_BIN_NUM; i++)
			{
				pHistoInfo2->chrm_bin[i] = \
					cur_param1.histogram[i+VPQ_HWRAP_HISTO_DCE_BIN_NUM];
				pHistoInfo2->hue_bin[i] = \
					cur_param1.histogram[i+VPQ_HWRAP_HISTO_DCE_BIN_NUM+VPQ_HWRAP_HISTO_BIN_NUM];
			}
			
			pHistoInfo2->skin_count = GET_BITS(cur_param1.status[4], 0, 23);
			if (cur_param1.domain == LX_PE_YC_DOMAIN)
			{
				pHistoInfo2->apl = cur_param1.average[0];	//10bit
			}
			else	//LX_PE_HSV_DOMAIN
			{
				/**
				* s=(max(rgb)-min(rgb))/max(rgb), v=max(rgb),
				* v'=(1-s*0.5)v=(max(rgb)+min(rgb))*0.5
				*/
				pHistoInfo2->apl = VPQ_HWRAP_COV_RGB2V(cur_param1.average[0], \
					cur_param1.average[1], cur_param1.average[2]);	//10bit
			}

			pHistoInfo2->min = cur_param1.min;
			pHistoInfo2->max = cur_param1.max;
			pHistoInfo2->peak_low = cur_param1.min;
			pHistoInfo2->peak_high = cur_param1.max;

			pHistoInfo2->sat_status = cur_param1.status[5];
			pHistoInfo2->diff_sum = GET_BITS(cur_param1.status[3], 0, 22);
			pHistoInfo2->motion = cur_param1.status[6];
			pHistoInfo2->texture = cur_param1.status[7];
		}
	}
	else
	{	
		if(p_param->version == 0x1)
			pHistoInfo->peak_high = 0xffffffff;
		else if(p_param->version == 0x2)
			pHistoInfo2->peak_high = 0xffffffff;
		ret = RET_OK;
		return ret;
	}
	return ret;
}

int vpq_hwrap_gethistodata_o24(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	UINT8 i=0;
	LX_PE_WIN_ID wid;
	struct v4l2_ext_vpq_dc2p_histodata_info *pHistoInfo;
	vpq_hwrap_ext_histodata_info *pHistoInfo2;
	//static LX_PE_HST_HISTO_INFO_T pre_param;
	LX_PE_HST_HISTO1_INFO_T cur_param1;
	static LX_PE_HST_HISTO1_INFO_T pre_param1[4];
	unsigned int tmp_dce_bin[128];

	VPQ_HWRAP_CHECK_CODE(!p_param, return RET_ERROR, "Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data, return RET_ERROR, "Error. p_data is null.\n");
	if(p_param->version == 0x1)
		pHistoInfo = (struct v4l2_ext_vpq_dc2p_histodata_info *)p_param->p_data;
	else if(p_param->version == 0x2)
		pHistoInfo2 = (vpq_hwrap_ext_histodata_info *)p_param->p_data;
	wid = p_param->wid;
	cur_param1.win_id = wid;
	if (KWRAP_PE_IsMuteOn(wid))
	{
		memcpy(&cur_param1, &pre_param1[wid], sizeof(LX_PE_HST_HISTO1_INFO_T));
	}
	else
	{
		cur_param1.domain = LX_PE_YC_DOMAIN;
		ret = PE_HST_GetHistogramInfo((void *)&cur_param1);
		if (ret)
		{
			if(p_param->version == 0x1)
				pHistoInfo->peak_high = 0xffffffff;
			else if(p_param->version == 0x2)
				pHistoInfo2->peak_high = 0xffffffff;
			ret = RET_OK;
			return ret;
		}
		memcpy(&pre_param1[wid], &cur_param1, sizeof(LX_PE_HST_HISTO1_INFO_T));
	}

	if (cur_param1.histo_ready)
	{
		if(p_param->version == 0x1)//til no ready for new DCE bin (128)
		{
			for (i = 0 ; i < VPQ_HWRAP_HISTO_DCE_BIN_NUM; i++)
			{
				tmp_dce_bin[i] = cur_param1.histogram[i];
				//PE_PRINT_ETC("[%d] hist : %d\n",i,tmp_dce_bin[i]);
			}
			for (i = 0 ; i < VPQ_HWRAP_HISTO_BIN_NUM; i++)
			{
				pHistoInfo->chrm_bin[i] = \
					cur_param1.histogram[i+VPQ_HWRAP_HISTO_DCE_BIN_NUM];
				pHistoInfo->hue_bin[i] = \
					cur_param1.histogram[i+VPQ_HWRAP_HISTO_DCE_BIN_NUM+VPQ_HWRAP_HISTO_BIN_NUM];
				pHistoInfo->bin[i] = tmp_dce_bin[i*4] + tmp_dce_bin[i*4+1] + tmp_dce_bin[i*4+2]+ tmp_dce_bin[i*4+3];
			}
			if(wid == LX_PE_WIN_0)
			{
				pHistoInfo->skin_count = GET_BITS(cur_param1.status[4], 0, 23);
				if (cur_param1.domain == LX_PE_YC_DOMAIN)
				{
					pHistoInfo->apl = cur_param1.average[0];	//10bit
				}
				else	//LX_PE_HSV_DOMAIN
				{
					/**
					* s=(max(rgb)-min(rgb))/max(rgb), v=max(rgb),
					* v'=(1-s*0.5)v=(max(rgb)+min(rgb))*0.5
					*/
					pHistoInfo->apl = VPQ_HWRAP_COV_RGB2V(cur_param1.average[0], \
						cur_param1.average[1], cur_param1.average[2]);	//10bit
				}

				pHistoInfo->min = cur_param1.min;
				pHistoInfo->max = cur_param1.max;
				pHistoInfo->peak_low = cur_param1.min;
				pHistoInfo->peak_high = cur_param1.max;

				pHistoInfo->sat_status = cur_param1.status[5];
				pHistoInfo->diff_sum = GET_BITS(cur_param1.status[3], 0, 22);
				pHistoInfo->motion = cur_param1.status[6];
				pHistoInfo->texture = cur_param1.status[7];
			}
		}
		else if(p_param->version == 0x2)
		{
			for (i = 0 ; i < VPQ_HWRAP_HISTO_DCE_BIN_NUM; i++)
			{
				pHistoInfo2->bin[i] = cur_param1.histogram[i];
				PE_PRINT_ETC("[%d] hist : %d\n",i,pHistoInfo2->bin[i]);
			}
			for (i = 0 ; i < VPQ_HWRAP_HISTO_BIN_NUM; i++)
			{
				pHistoInfo2->chrm_bin[i] = \
					cur_param1.histogram[i+VPQ_HWRAP_HISTO_DCE_BIN_NUM];
				pHistoInfo2->hue_bin[i] = \
					cur_param1.histogram[i+VPQ_HWRAP_HISTO_DCE_BIN_NUM+VPQ_HWRAP_HISTO_BIN_NUM];
			}
			if(wid == LX_PE_WIN_0)
			{
				pHistoInfo2->skin_count = GET_BITS(cur_param1.status[4], 0, 23);
				if (cur_param1.domain == LX_PE_YC_DOMAIN)
				{
					pHistoInfo2->apl = cur_param1.average[0];	//10bit
				}
				else	//LX_PE_HSV_DOMAIN
				{
					/**
					* s=(max(rgb)-min(rgb))/max(rgb), v=max(rgb),
					* v'=(1-s*0.5)v=(max(rgb)+min(rgb))*0.5
					*/
					pHistoInfo2->apl = VPQ_HWRAP_COV_RGB2V(cur_param1.average[0], \
						cur_param1.average[1], cur_param1.average[2]);	//10bit
				}

				pHistoInfo2->min = cur_param1.min;
				pHistoInfo2->max = cur_param1.max;
				pHistoInfo2->peak_low = cur_param1.min;
				pHistoInfo2->peak_high = cur_param1.max;

				pHistoInfo2->sat_status = cur_param1.status[5];
				pHistoInfo2->diff_sum = GET_BITS(cur_param1.status[3], 0, 22);
				pHistoInfo2->motion = cur_param1.status[6];
				pHistoInfo2->texture = cur_param1.status[7];
			}
		}
#if 0
		PE_PRINT_HST("[%s.%d] hist1 Y\n"\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
			__F__, __L__,\
			cur_param1.histogram[1][0],cur_param1.histogram[1][1],cur_param1.histogram[1][2],cur_param1.histogram[1][3],cur_param1.histogram[1][4],cur_param1.histogram[1][5],cur_param1.histogram[1][6],cur_param1.histogram[1][7],\
			cur_param1.histogram[1][8],cur_param1.histogram[1][9],cur_param1.histogram[1][10],cur_param1.histogram[1][11],cur_param1.histogram[1][12],cur_param1.histogram[1][13],cur_param1.histogram[1][14],cur_param1.histogram[1][15],\
			cur_param1.histogram[1][16],cur_param1.histogram[1][17],cur_param1.histogram[1][18],cur_param1.histogram[1][19],cur_param1.histogram[1][20],cur_param1.histogram[1][21],cur_param1.histogram[1][22],cur_param1.histogram[1][23],\
			cur_param1.histogram[1][24],cur_param1.histogram[1][25],cur_param1.histogram[1][26],cur_param1.histogram[1][27],cur_param1.histogram[1][28],cur_param1.histogram[1][29],cur_param1.histogram[1][30],cur_param1.histogram[1][31],\
			cur_param1.histogram[1][32],cur_param1.histogram[1][33],cur_param1.histogram[1][34],cur_param1.histogram[1][35],cur_param1.histogram[1][36],cur_param1.histogram[1][37],cur_param1.histogram[1][38],cur_param1.histogram[1][39],\
			cur_param1.histogram[1][40],cur_param1.histogram[1][41],cur_param1.histogram[1][42],cur_param1.histogram[1][43],cur_param1.histogram[1][44],cur_param1.histogram[1][45],cur_param1.histogram[1][46],cur_param1.histogram[1][47],\
			cur_param1.histogram[1][48],cur_param1.histogram[1][49],cur_param1.histogram[1][50],cur_param1.histogram[1][51],cur_param1.histogram[1][52],cur_param1.histogram[1][53],cur_param1.histogram[1][54],cur_param1.histogram[1][55],\
			cur_param1.histogram[1][56],cur_param1.histogram[1][57],cur_param1.histogram[1][58],cur_param1.histogram[1][59],cur_param1.histogram[1][60],cur_param1.histogram[1][61],cur_param1.histogram[1][62],cur_param1.histogram[1][63],\
			cur_param1.histogram[1][64],cur_param1.histogram[1][65],cur_param1.histogram[1][66],cur_param1.histogram[1][67],cur_param1.histogram[1][68],cur_param1.histogram[1][69],cur_param1.histogram[1][70],cur_param1.histogram[1][71],\
			cur_param1.histogram[1][72],cur_param1.histogram[1][73],cur_param1.histogram[1][74],cur_param1.histogram[1][75],cur_param1.histogram[1][76],cur_param1.histogram[1][77],cur_param1.histogram[1][78],cur_param1.histogram[1][79],\
			cur_param1.histogram[1][80],cur_param1.histogram[1][81],cur_param1.histogram[1][82],cur_param1.histogram[1][83],cur_param1.histogram[1][84],cur_param1.histogram[1][85],cur_param1.histogram[1][86],cur_param1.histogram[1][87],\
			cur_param1.histogram[1][88],cur_param1.histogram[1][89],cur_param1.histogram[1][90],cur_param1.histogram[1][91],cur_param1.histogram[1][92],cur_param1.histogram[1][93],cur_param1.histogram[1][94],cur_param1.histogram[1][95],\
			cur_param1.histogram[1][96],cur_param1.histogram[1][97],cur_param1.histogram[1][98],cur_param1.histogram[1][99],cur_param1.histogram[1][100],cur_param1.histogram[1][101],cur_param1.histogram[1][102],cur_param1.histogram[1][103],\
			cur_param1.histogram[1][104],cur_param1.histogram[1][105],cur_param1.histogram[1][106],cur_param1.histogram[1][107],cur_param1.histogram[1][108],cur_param1.histogram[1][109],cur_param1.histogram[1][110],cur_param1.histogram[1][111],\
			cur_param1.histogram[1][112],cur_param1.histogram[1][113],cur_param1.histogram[1][114],cur_param1.histogram[1][115],cur_param1.histogram[1][116],cur_param1.histogram[1][117],cur_param1.histogram[1][118],cur_param1.histogram[1][119],\
			cur_param1.histogram[1][120],cur_param1.histogram[1][121],cur_param1.histogram[1][122],cur_param1.histogram[1][123],cur_param1.histogram[1][124],cur_param1.histogram[1][125],cur_param1.histogram[1][126],cur_param1.histogram[1][127]);
		
		PE_PRINT_HST("[%s.%d] hist2 Y\n"\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
			__F__, __L__,\
			cur_param1.histogram[2][0],cur_param1.histogram[2][1],cur_param1.histogram[2][2],cur_param1.histogram[2][3],cur_param1.histogram[2][4],cur_param1.histogram[2][5],cur_param1.histogram[2][6],cur_param1.histogram[2][7],\
			cur_param1.histogram[2][8],cur_param1.histogram[2][9],cur_param1.histogram[2][10],cur_param1.histogram[2][11],cur_param1.histogram[2][12],cur_param1.histogram[2][13],cur_param1.histogram[2][14],cur_param1.histogram[2][15],\
			cur_param1.histogram[2][16],cur_param1.histogram[2][17],cur_param1.histogram[2][18],cur_param1.histogram[2][19],cur_param1.histogram[2][20],cur_param1.histogram[2][21],cur_param1.histogram[2][22],cur_param1.histogram[2][23],\
			cur_param1.histogram[2][24],cur_param1.histogram[2][25],cur_param1.histogram[2][26],cur_param1.histogram[2][27],cur_param1.histogram[2][28],cur_param1.histogram[2][29],cur_param1.histogram[2][30],cur_param1.histogram[2][31],\
			cur_param1.histogram[2][32],cur_param1.histogram[2][33],cur_param1.histogram[2][34],cur_param1.histogram[2][35],cur_param1.histogram[2][36],cur_param1.histogram[2][37],cur_param1.histogram[2][38],cur_param1.histogram[2][39],\
			cur_param1.histogram[2][40],cur_param1.histogram[2][41],cur_param1.histogram[2][42],cur_param1.histogram[2][43],cur_param1.histogram[2][44],cur_param1.histogram[2][45],cur_param1.histogram[2][46],cur_param1.histogram[2][47],\
			cur_param1.histogram[2][48],cur_param1.histogram[2][49],cur_param1.histogram[2][50],cur_param1.histogram[2][51],cur_param1.histogram[2][52],cur_param1.histogram[2][53],cur_param1.histogram[2][54],cur_param1.histogram[2][55],\
			cur_param1.histogram[2][56],cur_param1.histogram[2][57],cur_param1.histogram[2][58],cur_param1.histogram[2][59],cur_param1.histogram[2][60],cur_param1.histogram[2][61],cur_param1.histogram[2][62],cur_param1.histogram[2][63],\
			cur_param1.histogram[2][64],cur_param1.histogram[2][65],cur_param1.histogram[2][66],cur_param1.histogram[2][67],cur_param1.histogram[2][68],cur_param1.histogram[2][69],cur_param1.histogram[2][70],cur_param1.histogram[2][71],\
			cur_param1.histogram[2][72],cur_param1.histogram[2][73],cur_param1.histogram[2][74],cur_param1.histogram[2][75],cur_param1.histogram[2][76],cur_param1.histogram[2][77],cur_param1.histogram[2][78],cur_param1.histogram[2][79],\
			cur_param1.histogram[2][80],cur_param1.histogram[2][81],cur_param1.histogram[2][82],cur_param1.histogram[2][83],cur_param1.histogram[2][84],cur_param1.histogram[2][85],cur_param1.histogram[2][86],cur_param1.histogram[2][87],\
			cur_param1.histogram[2][88],cur_param1.histogram[2][89],cur_param1.histogram[2][90],cur_param1.histogram[2][91],cur_param1.histogram[2][92],cur_param1.histogram[2][93],cur_param1.histogram[2][94],cur_param1.histogram[2][95],\
			cur_param1.histogram[2][96],cur_param1.histogram[2][97],cur_param1.histogram[2][98],cur_param1.histogram[2][99],cur_param1.histogram[2][100],cur_param1.histogram[2][101],cur_param1.histogram[2][102],cur_param1.histogram[2][103],\
			cur_param1.histogram[2][104],cur_param1.histogram[2][105],cur_param1.histogram[2][106],cur_param1.histogram[2][107],cur_param1.histogram[2][108],cur_param1.histogram[2][109],cur_param1.histogram[2][110],cur_param1.histogram[2][111],\
			cur_param1.histogram[2][112],cur_param1.histogram[2][113],cur_param1.histogram[2][114],cur_param1.histogram[2][115],cur_param1.histogram[2][116],cur_param1.histogram[2][117],cur_param1.histogram[2][118],cur_param1.histogram[2][119],\
			cur_param1.histogram[2][120],cur_param1.histogram[2][121],cur_param1.histogram[2][122],cur_param1.histogram[2][123],cur_param1.histogram[2][124],cur_param1.histogram[2][125],cur_param1.histogram[2][126],cur_param1.histogram[2][127]);

		PE_PRINT_HST("[%s.%d] hist3 Y\n"\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
			"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
			__F__, __L__,\
			cur_param1.histogram[3][0],cur_param1.histogram[3][1],cur_param1.histogram[3][2],cur_param1.histogram[3][3],cur_param1.histogram[3][4],cur_param1.histogram[3][5],cur_param1.histogram[3][6],cur_param1.histogram[3][7],\
			cur_param1.histogram[3][8],cur_param1.histogram[3][9],cur_param1.histogram[3][10],cur_param1.histogram[3][11],cur_param1.histogram[3][12],cur_param1.histogram[3][13],cur_param1.histogram[3][14],cur_param1.histogram[3][15],\
			cur_param1.histogram[3][16],cur_param1.histogram[3][17],cur_param1.histogram[3][18],cur_param1.histogram[3][19],cur_param1.histogram[3][20],cur_param1.histogram[3][21],cur_param1.histogram[3][22],cur_param1.histogram[3][23],\
			cur_param1.histogram[3][24],cur_param1.histogram[3][25],cur_param1.histogram[3][26],cur_param1.histogram[3][27],cur_param1.histogram[3][28],cur_param1.histogram[3][29],cur_param1.histogram[3][30],cur_param1.histogram[3][31],\
			cur_param1.histogram[3][32],cur_param1.histogram[3][33],cur_param1.histogram[3][34],cur_param1.histogram[3][35],cur_param1.histogram[3][36],cur_param1.histogram[3][37],cur_param1.histogram[3][38],cur_param1.histogram[3][39],\
			cur_param1.histogram[3][40],cur_param1.histogram[3][41],cur_param1.histogram[3][42],cur_param1.histogram[3][43],cur_param1.histogram[3][44],cur_param1.histogram[3][45],cur_param1.histogram[3][46],cur_param1.histogram[3][47],\
			cur_param1.histogram[3][48],cur_param1.histogram[3][49],cur_param1.histogram[3][50],cur_param1.histogram[3][51],cur_param1.histogram[3][52],cur_param1.histogram[3][53],cur_param1.histogram[3][54],cur_param1.histogram[3][55],\
			cur_param1.histogram[3][56],cur_param1.histogram[3][57],cur_param1.histogram[3][58],cur_param1.histogram[3][59],cur_param1.histogram[3][60],cur_param1.histogram[3][61],cur_param1.histogram[3][62],cur_param1.histogram[3][63],\
			cur_param1.histogram[3][64],cur_param1.histogram[3][65],cur_param1.histogram[3][66],cur_param1.histogram[3][67],cur_param1.histogram[3][68],cur_param1.histogram[3][69],cur_param1.histogram[3][70],cur_param1.histogram[3][71],\
			cur_param1.histogram[3][72],cur_param1.histogram[3][73],cur_param1.histogram[3][74],cur_param1.histogram[3][75],cur_param1.histogram[3][76],cur_param1.histogram[3][77],cur_param1.histogram[3][78],cur_param1.histogram[3][79],\
			cur_param1.histogram[3][80],cur_param1.histogram[3][81],cur_param1.histogram[3][82],cur_param1.histogram[3][83],cur_param1.histogram[3][84],cur_param1.histogram[3][85],cur_param1.histogram[3][86],cur_param1.histogram[3][87],\
			cur_param1.histogram[3][88],cur_param1.histogram[3][89],cur_param1.histogram[3][90],cur_param1.histogram[3][91],cur_param1.histogram[3][92],cur_param1.histogram[3][93],cur_param1.histogram[3][94],cur_param1.histogram[3][95],\
			cur_param1.histogram[3][96],cur_param1.histogram[3][97],cur_param1.histogram[3][98],cur_param1.histogram[3][99],cur_param1.histogram[3][100],cur_param1.histogram[3][101],cur_param1.histogram[3][102],cur_param1.histogram[3][103],\
			cur_param1.histogram[3][104],cur_param1.histogram[3][105],cur_param1.histogram[3][106],cur_param1.histogram[3][107],cur_param1.histogram[3][108],cur_param1.histogram[3][109],cur_param1.histogram[3][110],cur_param1.histogram[3][111],\
			cur_param1.histogram[3][112],cur_param1.histogram[3][113],cur_param1.histogram[3][114],cur_param1.histogram[3][115],cur_param1.histogram[3][116],cur_param1.histogram[3][117],cur_param1.histogram[3][118],cur_param1.histogram[3][119],\
			cur_param1.histogram[3][120],cur_param1.histogram[3][121],cur_param1.histogram[3][122],cur_param1.histogram[3][123],cur_param1.histogram[3][124],cur_param1.histogram[3][125],cur_param1.histogram[3][126],cur_param1.histogram[3][127]);
		#endif
	}
	else
	{	
		if(p_param->version == 0x1)
			pHistoInfo->peak_high = 0xffffffff;
		else if(p_param->version == 0x2)
			pHistoInfo2->peak_high = 0xffffffff;
		ret = RET_OK;
		return ret;
	}
	return ret;
}

int vpq_hwrap_getnoiselevel(UINT16 *uLevel)
{
	int ret = RET_OK;
	LX_PE_INF_LEVEL_T param;
	UINT32 cvd_n_lvl = 0;
	vpq_hwrap_info_t *p_info = &_g_vpq_hwrap_info;

	VPQ_HWRAP_CHECK_CODE(!uLevel, return RET_ERROR, \
		"Error.[%s.%d] input is null.\n", __F__, __L__);

	param.win_id=LX_PE_WIN_0;
	param.sel=LX_PE_LEVEL_NOISE|LX_PE_LEVEL_PEAKPOS;
	ret = PE_ETC_GetLevelInfo(&param);
	VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
		"Error.[%s.%d] KWRAP_PE_GetLevelInfo(): %d\n", __F__, __L__, ret);
	if (p_info->vpq_input[LX_PE_WIN_0] == VPQ_HWRAP_INPUT_ATV)
	{
#ifdef INCLUDE_KDRV_AFE
		(void)afe_kwrap_cvd_get_noise_status(&cvd_n_lvl);
#endif
		uLevel[0] = (UINT16)cvd_n_lvl;
	}
	else
	{
		uLevel[0] = (UINT16)param.noise_level;
	}

	PE_PRINT_ETC("[%s.%d] noise: %d,\n", __F__, __L__, uLevel[0]);

	return ret;
}

int vpq_hwrap_setsharpness(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version)
{
	int ret = RET_OK;
	unsigned short *pUi = pShpData->ui_value;
	LX_PE_WIN_ID win_id;;
	LX_PE_EXTRN_CHIP_WIN_ID extrn_win_id;
	vpq_hwrap_input_t input_info = VPQ_HWRAP_INPUT_MAX;
	vpq_hwrap_info_t *p_info = &_g_vpq_hwrap_info;
	LX_PE_DEFAULT_SETTINGS_T dft_param;
	LX_PE_INF_DISPLAY_T pre_inf_param;
	LX_PE_INF_DISPLAY_T cur_inf_param;

	VPQ_HWRAP_CHECK_CODE(!pShpData, return RET_ERROR, "Error. pShpData is null.\n");

	win_id = (LX_PE_WIN_ID)wId;
	extrn_win_id = (LX_PE_EXTRN_CHIP_WIN_ID)wId;
	input_info = (vpq_hwrap_input_t)pUi[2];
	p_info->vpq_input[win_id] = input_info;
	p_info->is_vr = pUi[3] ? 0x1 : 0x0;

	/* 1. set display info. */
	cur_inf_param.win_id = win_id;
	if (PE_KDRV_VER_O20)
	{
		ret = KWRAP_PE_GetCurPicDisplayInfo((void *)&cur_inf_param);
	}
	else
	{
		ret = PE_ETC_GetDisplayInfo(&cur_inf_param);
	}
	cur_inf_param.info_type = LX_PE_INFO_DEFAULT;
	memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));

	/* hdmi_type */
	if (input_info == VPQ_HWRAP_INPUT_HDMI_PC)
	{
		cur_inf_param.hdmi_type = LX_PE_HDMI_PC;
	}
	else
	{
		cur_inf_param.hdmi_type = LX_PE_HDMI_TV;	//default
	}
	/* scart_type */
	if (input_info == VPQ_HWRAP_INPUT_SCARTRGB)
	{
		cur_inf_param.scart_type = LX_PE_SCART_RGB;
	}
	else
	{
		cur_inf_param.scart_type = LX_PE_SCART_AV;	//default
	}
	/* dtv_type */
	switch (input_info)
	{
		case VPQ_HWRAP_INPUT_DTV:
			cur_inf_param.dtv_type = LX_PE_DTV_NORMAL;
			break;
		case VPQ_HWRAP_INPUT_PICWIZ:
		case VPQ_HWRAP_INPUT_PICTEST:
			cur_inf_param.dtv_type = LX_PE_DTV_TESTPIC;
			break;
		case VPQ_HWRAP_INPUT_MEDIA_MOVIE:
			cur_inf_param.dtv_type = LX_PE_DTV_FILEPLAY;
			break;
		case VPQ_HWRAP_INPUT_CAMERA:
			cur_inf_param.dtv_type = LX_PE_DTV_CAMERA;
			break;
		case VPQ_HWRAP_INPUT_MEDIA_PHOTO:
			cur_inf_param.dtv_type = LX_PE_DTV_PHOTOPLAY;
			break;
		case VPQ_HWRAP_INPUT_PVR_DTV:
		case VPQ_HWRAP_INPUT_PVR_ATV:
		case VPQ_HWRAP_INPUT_PVR_AV:
			cur_inf_param.dtv_type = LX_PE_DTV_HDDPLAY;
			break;
		default:
			cur_inf_param.dtv_type = LX_PE_DTV_INVALID;
			break;
	}
	/* hdd_type */
	switch (input_info)
	{
		case VPQ_HWRAP_INPUT_PVR_DTV:
			cur_inf_param.hdd_type = LX_PE_HDD_SRC_DTV;
			break;
		case VPQ_HWRAP_INPUT_PVR_ATV:
			if (cur_inf_param.fr_type == LX_PE_FR_60HZ)
				cur_inf_param.hdd_type = LX_PE_HDD_SRC_ATV60;
			else
				cur_inf_param.hdd_type = LX_PE_HDD_SRC_ATV50;
			break;
		case VPQ_HWRAP_INPUT_PVR_AV:
			if (cur_inf_param.fr_type == LX_PE_FR_60HZ)
				cur_inf_param.hdd_type = LX_PE_HDD_SRC_AV60;
			else
				cur_inf_param.hdd_type = LX_PE_HDD_SRC_AV50;
			break;
		default:
			cur_inf_param.hdd_type = LX_PE_HDD_SRC_INVALID;
			break;
	}
	/* vr 360 mode*/
	cur_inf_param.mode.is_vr = p_info->is_vr;

	/* 1. set default */
	if (pre_inf_param.hdmi_type != cur_inf_param.hdmi_type ||
		pre_inf_param.scart_type != cur_inf_param.scart_type ||
		pre_inf_param.dtv_type != cur_inf_param.dtv_type ||
		pre_inf_param.hdd_type != cur_inf_param.hdd_type ||
		pre_inf_param.mode.is_vr != cur_inf_param.mode.is_vr)
	{
		PE_PRINT_SHP("[%s.%d][wid:%d]vpq_in_type:%d,fr:%d\n",
			__F__, __L__, cur_inf_param.win_id, input_info,
			cur_inf_param.fr_type);
		PE_PRINT_SHP("[%s.%d]set wid:%d, hdmi:%d,scart:%d,dtv:%d,hdd:%d,vr:%d\n",
			__F__, __L__, cur_inf_param.win_id, cur_inf_param.hdmi_type,
			cur_inf_param.scart_type, cur_inf_param.dtv_type,
			cur_inf_param.hdd_type,cur_inf_param.mode.is_vr);

		/* set disp info */
		if(PE_KDRV_VER_O20)
			ret = KWRAP_PE_SetPicDisplayInfo((void *)&cur_inf_param);
		else
			ret = PE_ETC_SetDisplayInfo(&cur_inf_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_ETC_SetDisplayInfo(): error %d\n", ret);

		/* set default settings */
		dft_param.win_id = win_id;
		{
			LX_PE_DEFAULT_SETTINGS_T __attribute__((unused)) *pp = (LX_PE_DEFAULT_SETTINGS_T *)&dft_param;
			ret = vpq_hwrap_setdefaultsettings((void *)pp);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setdefaultsettings(): error %d\n", ret);
		}
	}
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE // for test 8k model to set win = 2
	if(_g_vpq_hwrap_shp_platform_db_enable != 0xff)
		win_id= (LX_PE_WIN_ID)_g_vpq_hwrap_shp_platform_db_enable;
	#endif 
	if(_g_vpq_hwrap_switch_win_id != 0x0)
		win_id= (LX_PE_WIN_ID)_g_vpq_hwrap_switch_win_id;

	PE_PRINT_SHP("[%s.%d]set pq wid:%d\n",
				__F__, __L__,win_id);
	/* 2. set sharpness */
	if(version == 0x80) // webos24
	{
		if(PE_KDRV_VER_O26)
		{
			if(win_id < LX_PE_WIN_ALL)
			{
				ret = vpq_hwrap_setsharpness_o26(pShpData, win_id, version);
				VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_o26(): error %d\n", ret);
			}
			else if(extrn_win_id == LX_PE_EXTRN_CHIP_WIN_0 || extrn_win_id == LX_PE_EXTRN_CHIP_WIN_1)
			{
				ret = vpq_hwrap_setsharpness_f22(pShpData, win_id);
				VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_f22(): error %d\n", ret);
			}
		}	
	}
	else if(version == 0x60) // webos24
	{
		if(PE_KDRV_VER_O22)
		{
			if(win_id == LX_PE_WIN_0 || win_id == LX_PE_WIN_1)
			{
				ret = vpq_hwrap_setsharpness_o22(pShpData, win_id, version);
				VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_o22(): error %d\n", ret);
			}
			else
			{
				ret = vpq_hwrap_setsharpness_f22(pShpData, win_id);
				VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_f20(): error %d\n", ret);
			}
		}
		else if(PE_KDRV_VER_O24 || PE_KDRV_VER_O26)
		{
			if(win_id < LX_PE_WIN_ALL)
			{
				ret = vpq_hwrap_setsharpness_o24(pShpData, win_id, version);
				VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_o24(): error %d\n", ret);
			}
			else if(extrn_win_id == LX_PE_EXTRN_CHIP_WIN_0 || extrn_win_id == LX_PE_EXTRN_CHIP_WIN_1)
			{
				ret = vpq_hwrap_setsharpness_f22(pShpData, win_id);
				VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_f20(): error %d\n", ret);
			}
		}	
	}
	else if(PE_KDRV_VER_O22 || PE_KDRV_VER_M23 ) //webos23
	{
		if(win_id == LX_PE_WIN_0 || win_id == LX_PE_WIN_1)
		{
			ret = vpq_hwrap_setsharpness_o22(pShpData, win_id, version);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_o22(): error %d\n", ret);
		}
		else
		{
			ret = vpq_hwrap_setsharpness_f22(pShpData, win_id);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_f20(): error %d\n", ret);
		}
	}
	else if(PE_KDRV_VER_E60 )
	{
		if(win_id == LX_PE_WIN_0 || win_id == LX_PE_WIN_1)
		{
			ret = vpq_hwrap_setsharpness_e60(pShpData, win_id);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_e60(): error %d\n", ret);
		}
		else
		{
			ret = vpq_hwrap_setsharpness_f20(pShpData, win_id);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_f20(): error %d\n", ret);
		}
	}
	else if(PE_KDRV_VER_O20)
	{
		if(win_id == LX_PE_WIN_0 || win_id == LX_PE_WIN_1)
		{
			ret = vpq_hwrap_setsharpness_o20(pShpData, win_id);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_o20(): error %d\n", ret);
		}
		else
		{
			ret = vpq_hwrap_setsharpness_f20(pShpData, win_id);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setsharpness_f20(): error %d\n", ret);
		}
	}
	else
	{
		PE_PRINT_NOTI("not surpported\n");
		ret = RET_OK;
	}
	return ret;
}

static int vpq_hwrap_setsharpness_o26(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	win_id = wId;
	if(win_id == LX_PE_WIN_0)// set only @ winid=0
	{
		ret = vpq_hwrap_vsd_setsharpness_o26(pShpData, win_id, version);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_vsd_setsharpness_o26(): error %d\n", ret);
	}
	ret = vpq_hwrap_sre_setsharpness_o26(pShpData, win_id, version);
	VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_sre_setsharpness_o26(): error %d\n", ret);
	return ret;
}

static int vpq_hwrap_vsd_setsharpness_o26(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_o26_t *pChip = (vpq_hwrap_chip_shp_o26_t *)pShpData->pst_chip_data;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) PE_KWRAP_CTRL_T kwrap_ctrl;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) LX_PE_SHP_RE3_CMN_T cmn_param;// updated @o26
	__attribute__((unused)) LX_PE_SHP_RE1_MISC_T misc_param;
	__attribute__((unused)) LX_PE_SHP_EE1_T ee_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM4_CMN_T sqm_cmn_param;// updated @o26
	__attribute__((unused)) LX_PE_SHP_RE_SQM5_DETAIL_T sqm_dtl_param; // updated @o26
	__attribute__((unused)) LX_PE_SHP_DE4_T tmp_ede_param;	/* for super resolution menu   */
	__attribute__((unused)) int fnum, i;
	__attribute__((unused)) UINT8 *pd;
	__attribute__((unused)) UINT32 *pd32;
	__attribute__((unused)) UINT16 *pd16;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode = _g_vpq_hwrap_shp_platform_db_enable;
	/* 1. set post sharpness */
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (pChip)
	#else
	if ((pChip) && db_mode)
	#endif
	{
		/*vsd shp wid*/
		misc_param.win_id = cmn_param.win_id = ee_param.win_id  = win_id;
		/*sqm wid*/
		sqm_cmn_param.win_id = sqm_dtl_param.win_id = win_id;

		//memcpy //
		memcpy(&(cmn_param.shp_ui_main_vsd), \
			&(pChip->shp_ui_main_vsd), sizeof(pChip->shp_ui_main_vsd));
		cmn_param.shp_luma_en_vsd = pChip->shp_luma_en_vsd;
		memcpy(&(cmn_param.shp_face_obj_vsd), \
			&(pChip->shp_face_obj_vsd), sizeof(pChip->shp_face_obj_vsd));
		memcpy(&(misc_param.shp_djg_vsd), \
			&(pChip->shp_djg_vsd), sizeof(pChip->shp_djg_vsd));
		memcpy(&(misc_param.shp_cmn_vsd), \
			&(pChip->shp_cmn_vsd), sizeof(pChip->shp_cmn_vsd));
		memcpy(&(misc_param.shp_map_cmn_vsd), \
			&(pChip->shp_map_cmn_vsd), sizeof(pChip->shp_map_cmn_vsd));
		memcpy(&(misc_param.shp_balance_vsd), \
			&(pChip->shp_balance_vsd), sizeof(pChip->shp_balance_vsd));
		memcpy(&(misc_param.shp_ti_cmn_vsd), \
			&(pChip->shp_ti_cmn_vsd), sizeof(pChip->shp_ti_cmn_vsd));
		memcpy(&(misc_param.shp_chroma_vsd), \
			&(pChip->shp_chroma_vsd), sizeof(pChip->shp_chroma_vsd));

		pd = cmn_param.shp_ui_main_vsd;
		PQ_PRINT_SHP("set : shp_ui_main_vsd\n"
		"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd = cmn_param.shp_face_obj_vsd;
		PQ_PRINT_SHP("set : shp_face_obj_vsd\n"
		"shp_face_obj_vsd	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd	 [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], \
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);
		pd = misc_param.shp_cmn_vsd;
		PQ_PRINT_SHP("set : shp_cmn_vsd\n"
		"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = misc_param.shp_djg_vsd;
		PQ_PRINT_SHP("set : shp_djg_vsd\n"
		"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		PQ_PRINT_SHP("set : shp_luma_en_vsd: %d\n", cmn_param.shp_luma_en_vsd);
		pd = misc_param.shp_map_cmn_vsd;
		PQ_PRINT_SHP("set : shp_map_cmn_vsd\n"
		"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = misc_param.shp_balance_vsd;
		PQ_PRINT_SHP("set : shp_balance_vsd\n"
		"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
		pd = misc_param.shp_ti_cmn_vsd;
		PQ_PRINT_SHP("set : shp_ti_cmn_vsd\n"
		"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = misc_param.shp_chroma_vsd;
		PQ_PRINT_SHP("set : shp_chroma_vsd\n"
		"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4]);
		//memcpy(&(ee_param.shp_ee_vsd),&(pChip->shp_ee_vsd), sizeof(pChip->shp_ee_vsd));
		pd = pChip->shp_ee_vsd;
		PQ_PRINT_SHP("before sr weight sr-ui:%d,\n"\
		"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
	 	pUi[1],\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_vsd)/sizeof(UINT8); i++)
		{
			ee_param.shp_ee_vsd[i] = (UINT8)((UINT32)pChip->shp_ee_vsd[i] * fnum / 1000);
		}
		pd = ee_param.shp_ee_vsd;
		PQ_PRINT_SHP("after sr weight sr-ui:%d,\n"\
		"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
	 	pUi[1],\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		
		/*sqm*/
		sqm_cmn_param.shp_sqm____val = cmn_val;
		sqm_dtl_param.shp_sqm_____val = pUi[1];// add super resolution ui value AVTASK-1435, TVPM-26505
		memcpy(&(sqm_cmn_param.shp_ui_sqm_vsd), \
		&(pChip->shp_ui_sqm_vsd), sizeof(pChip->shp_ui_sqm_vsd));
		memcpy(&(sqm_dtl_param.shp_sqm_cmn_vsd), \
		&(pChip->shp_sqm_cmn_vsd), sizeof(pChip->shp_sqm_cmn_vsd));
		pd32 = sqm_cmn_param.shp_ui_sqm_vsd;
		PQ_PRINT_SHP("set : shp_ui_sqm_vsd\n"\
		"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X \n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39],\
		pd32[40],pd32[41],	pd32[42],  pd32[43], pd32[44],  pd32[45],  pd32[46],	pd32[47], pd32[48],  pd32[49],\
		pd32[50],pd32[51],	pd32[52],  pd32[53], pd32[54],  pd32[55],  pd32[56],	pd32[57], pd32[58],  pd32[59],\
		pd32[60],pd32[61],	pd32[62],  pd32[63], pd32[64] );
		pd32 = sqm_dtl_param.shp_sqm_cmn_vsd;
		PQ_PRINT_SHP("set : shp_sqm_cmn_vsd\n"\
		"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[70]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[80]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39],\
		pd32[40],pd32[41],	pd32[42],  pd32[43], pd32[34],  pd32[45],  pd32[46],	pd32[47], pd32[48],  pd32[49],\
		pd32[50],pd32[51],	pd32[52],  pd32[53], pd32[34],  pd32[55],  pd32[56],	pd32[57], pd32[58],  pd32[59],\
		pd32[60],pd32[61],	pd32[62],  pd32[63], pd32[34],  pd32[65],  pd32[66],	pd32[67], pd32[68],  pd32[69],\
		pd32[70],pd32[71],	pd32[72],  pd32[73], pd32[34],  pd32[75],  pd32[76],	pd32[77], pd32[78],  pd32[79],\
		pd32[80],pd32[81],	pd32[82],  pd32[83], pd32[34],  pd32[85],  pd32[86]);

		ret = PE_SHP_SetReCmnCtrl((void *)&cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetReMiscCtrl((void *)&misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReMiscCtrl(): error %d\n", ret);
		ret = PE_SHP_SetEdgeEnhanceCtrl((void *)&ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetEdgeEnhanceCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSqmCmnCtrl((void *)&sqm_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSqmCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSqmDetailCtrl((void *)&sqm_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSqmDetailCtrl(): error %d\n", ret);
	}
	else
	{
		tmp_ede_param.win_id  = win_id;
		/* 1. set post sharpness */
		{
			kwrap_ctrl.wid = win_id;
			kwrap_ctrl.data = cmn_val;
			ret = KWRAP_PE_SetRenCmnCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetRenCmnCtrl(): error %d\n", ret);

			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = PE_KWRAP_SHP_FMT_HD;
			//ret = KWRAP_PE_SetRenMiscCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenMiscCtrl() \n", __F__, __L__);

			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenHorCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenHorCtrl() \n", __F__, __L__);
			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenVerCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenVerCtrl() \n", __F__, __L__);
			
			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = (UINT32)cmn_val;
			//ret = KWRAP_PE_SetRenSqmCmnCtrl(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenSqmCmnCtrl(): error %d \n", __F__, __L__, ret);

			kwrap_ctrl.wid = win_id;
			kwrap_ctrl.data = cmn_val;
			kwrap_ctrl.st_data = (void*)&tmp_ede_param;
			ret = KWRAP_PE_GetDetailEnhanceDefaultSettings(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetDetailEnhanceDefaultSettings(): error %d\n", ret);
			tmp_ede_param.win_id = win_id;
			pd = tmp_ede_param.shp_de_vsd;
			PQ_PRINT_SHP("before sr weight sr-ui:%d,\n"\
				"shp_ee_vsd   [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_vsd   [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pUi[1],\
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10],pd[11],pd[12],pd[13]);

			if(pUi[1] == 0)
			{
				fnum = 0;
			}
			else if(pUi[1] == 1)
			{
				fnum = 500;
			}
			else if(pUi[1] == 3)
			{
				fnum = 1300;
			}
			else
			{
				fnum = 1000;
			}

			tmp_ede_param.shp_de_vsd[0] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[1] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[2] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[3] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[4] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[5] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[6] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[7] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[8] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[9] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[10]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[11]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[12]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[13]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			PQ_PRINT_SHP("after sr weight sr-ui:%d,\n"\
				"shp_ee_vsd   [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_vsd   [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pUi[1],\
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10],pd[11],pd[12],pd[13]);

			ret = KWRAP_PE_SetDetailEnhanceParam((void *)&tmp_ede_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDetailEnhanceParam(): error %d\n", ret);


		}
	}
	
	return ret;
}

static int vpq_hwrap_sre_setsharpness_o26(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_o26_t *pChip = (vpq_hwrap_chip_shp_o26_t *)pShpData->pst_chip_data;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) PE_KWRAP_CTRL_T kwrap_ctrl;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_CMN_T sr2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_MISC_T sr2k_misc_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_EE1_T sr2k_ee_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM4_CMN_T sqm2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM4_DETAIL_T sqm2k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_DE_T tmp_sr2k_de_param; /* for super resolution menu */
	__attribute__((unused)) LX_PE_SHP_SR_RE2_CMN_SUB_T sr_sub_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR_RE2_MISC_SUB_T sr_sub_misc_param;
	__attribute__((unused)) int fnum, i;
	__attribute__((unused)) UINT8 *pd;
	__attribute__((unused)) UINT32 *pd32;
	__attribute__((unused)) UINT16 *pd16;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode = _g_vpq_hwrap_shp_platform_db_enable;
	/* 2. set pre sharpness */
	if (pChip && db_mode)
	{
		/*sre shp*/
		/*2k*/
		sr2k_misc_param.win_id = sr2k_cmn_param.win_id = sr2k_ee_param.win_id = win_id;
		/*sqm*/
		sqm2k_cmn_param.win_id = sqm2k_dtl_param.win_id = win_id;

		memcpy(&(sr2k_cmn_param.shp_ui_main_2k), \
			&(pChip->shp_ui_main_2k), sizeof(pChip->shp_ui_main_2k));
		sr2k_cmn_param.shp_luma_en_2k = pChip->shp_luma_en_2k;
		memcpy(&(sr2k_cmn_param.shp_dnn_sr_vsd), \
			&(pChip->shp_dnn_sr_vsd), sizeof(pChip->shp_dnn_sr_vsd));
		memcpy(&(sr2k_misc_param.shp_cmn_2k), \
			&(pChip->shp_cmn_2k), sizeof(pChip->shp_cmn_2k));
		memcpy(&(sr2k_misc_param.shp_djg_2k), \
			&(pChip->shp_djg_2k), sizeof(pChip->shp_djg_2k));
		memcpy(&(sr2k_misc_param.shp_map_cmn_2k), \
			&(pChip->shp_map_cmn_2k), sizeof(pChip->shp_map_cmn_2k));
		memcpy(&(sr2k_misc_param.shp_balance_2k), \
			&(pChip->shp_balance_2k), sizeof(pChip->shp_balance_2k));
		memcpy(&(sr2k_misc_param.shp_ti_cmn_2k), \
			&(pChip->shp_ti_cmn_2k), sizeof(pChip->shp_ti_cmn_2k));
		//memcpy(&(sr2k_ee_param.shp_ee_2k),&(pChip->shp_ee_2k), sizeof(pChip->shp_ee_2k));
		
		pd = sr2k_cmn_param.shp_ui_main_2k;
		PQ_PRINT_SRE("set[%d] : shp_ui_main_2k\n"
		"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_2k    [10]0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd16 = sr2k_cmn_param.shp_dnn_sr_vsd;
		PQ_PRINT_SRE("set[%d] : shp_dnn_sr_vsd\n"
		"shp_dnn_sr_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_dnn_sr_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",win_id,\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16]);
		pd = sr2k_misc_param.shp_cmn_2k;
		PQ_PRINT_SRE("set[%d] : shp_cmn_2k\n"
		"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);

		pd = sr2k_misc_param.shp_djg_2k;
		PQ_PRINT_SRE("set[%d] : shp_djg_2k\n"
		"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

		PQ_PRINT_SRE("set[%d] : shp_luma_en_2k: %d\n", win_id, sr2k_cmn_param.shp_luma_en_2k);
		pd = sr2k_misc_param.shp_map_cmn_2k;
		PQ_PRINT_SRE("set[%d] : shp_map_cmn_2k\n"
		"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_2k    [10]0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = sr2k_misc_param.shp_balance_2k;

		PQ_PRINT_SRE("set[%d] : shp_balance_2k\n"
		"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

		pd = sr2k_misc_param.shp_ti_cmn_2k;
		PQ_PRINT_SRE("set[%d] : shp_ti_cmn_2k\n"
		"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = pChip->shp_ee_2k;
		PQ_PRINT_SRE("set[%d] before sr weight sr-ui:%d, size:%zu \n"\
		"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
	 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_2k)/sizeof(UINT8); i++)
		{
			sr2k_ee_param.shp_ee_2k[i] = (UINT8)((UINT32)pChip->shp_ee_2k[i] * fnum / 1000);
		}
		pd = sr2k_ee_param.shp_ee_2k;
		PQ_PRINT_SRE("set[%d] after sr weight sr-ui:%d, size:%zu \n"\
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		/*sqm*/
		sqm2k_cmn_param.shp_sqm___val= cmn_val;
		sqm2k_dtl_param.shp_sqm____val = pUi[1];// add super resolution ui value AVTASK-1435, TVPM-26505
		memcpy(&(sqm2k_cmn_param.shp_ui_sqm_2k), \
		&(pChip->shp_ui_sqm_2k), sizeof(pChip->shp_ui_sqm_2k));
		memcpy(&(sqm2k_dtl_param.shp_sqm_cmn_2k), \
		&(pChip->shp_sqm_cmn_2k), sizeof(pChip->shp_sqm_cmn_2k));
		pd32 = sqm2k_cmn_param.shp_ui_sqm_2k;
		PQ_PRINT_SRE("set[%d] : shp_ui_sqm_2k\n"
		"shp_ui_sqm_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,,0x%02X,\n"\
		"shp_ui_sqm_2k	  [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,,0x%02X,\n"\
		"shp_ui_sqm_2k	  [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",win_id,\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19],\
		pd32[20], pd32[21], pd32[22], pd32[23], pd32[24], pd32[25], pd32[26], pd32[27], pd32[28], pd32[29],\
		pd32[30], pd32[31], pd32[32], pd32[33], pd32[34], pd32[35], pd32[36], pd32[37], pd32[38], pd32[39],\
		pd32[40], pd32[41], pd32[42], pd32[43], pd32[44], pd32[45], pd32[46], pd32[47], pd32[48], pd32[49],\
		pd32[50], pd32[51], pd32[52], pd32[53], pd32[54], pd32[55], pd32[56]);
		pd32  = sqm2k_dtl_param.shp_sqm_cmn_2k;
		PQ_PRINT_SRE("set[%d] : shp_sqm_cmn_2k\n"\
		"shp_sqm_cmn_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",win_id,\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],  pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17],  pd32[18],	pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23], pd32[24],	pd32[25],  pd32[26],  pd32[27],  pd32[28],	pd32[29],\
		pd32[30],  pd32[31],  pd32[32],  pd32[33], pd32[34],	pd32[35],  pd32[36],  pd32[37],  pd32[38],	pd32[39],\
		pd32[40],  pd32[41],  pd32[42],  pd32[43], pd32[44],	pd32[45],  pd32[46],  pd32[47],  pd32[48],	pd32[49],\
		pd32[50],  pd32[51],  pd32[52],  pd32[53], pd32[54],	pd32[55],  pd32[56],  pd32[57],  pd32[58]);
		if(win_id == LX_PE_WIN_0)
		{
			ret = PE_SHP_SetSre2KReCmnCtrl((void *)&sr2k_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KReCmnCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSre2KReMiscCtrl((void *)&sr2k_misc_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KReMiscCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSre2KEdgeEnhanceCtrl((void *)&sr2k_ee_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KEdgeEnhanceCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSre2KSqmCmnCtrl((void *)&sqm2k_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KSqmCmnCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSre2KSqmDetailCtrl((void *)&sqm2k_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KSqmDetailCtrl(): error %d\n", ret);
		}
		else
		{
			sr_sub_cmn_param.win_id = sr_sub_misc_param.win_id= win_id;
			memcpy(&(sr_sub_cmn_param.sr_sub_cmn_ui), \
			&sr2k_cmn_param, sizeof(sr2k_cmn_param));
			memcpy(&(sr_sub_cmn_param.sr_sub_sqm_ui), \
			&sqm2k_cmn_param, sizeof(sqm2k_cmn_param));
			memcpy(&(sr_sub_misc_param.sr_sub_misc), \
			&sr2k_misc_param, sizeof(sr2k_misc_param));
			memcpy(&(sr_sub_misc_param.sr_sub_sqm_cmn), \
			&sqm2k_dtl_param, sizeof(sqm2k_dtl_param));
			ret = PE_SHP_SetSreSubReCmnCtrl((void *)&sr_sub_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreSubReCmnCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSreSubReMiscCtrl((void *)&sr_sub_misc_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreSubReMiscCtrl(): error %d\n", ret);
		
		}
		
	}
	else if(win_id == LX_PE_WIN_0)
	{
		tmp_sr2k_de_param.win_id  = win_id;
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		PQ_PRINT_SRE("wid_id:%d, cmn_val:%d (kwrap)\n",win_id,cmn_val);
		ret = KWRAP_PE_SetSre2KRenCmnCtrl((void *)&kwrap_ctrl);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KRenCmnCtrl(): error %d\n", ret);
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		kwrap_ctrl.st_data = (void*)&tmp_sr2k_de_param;
		
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		ret = KWRAP_PE_SetSre2KSqmCmnCtrl((void *)&kwrap_ctrl);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KSqmCmnCtrl(): error %d\n", ret);

		ret = KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(&kwrap_ctrl);
		tmp_sr2k_de_param.win_id = win_id;
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(): error %d\n", ret);

		if(pUi[1] == 0)
		{
			fnum = 0;
		}
		else if(pUi[1] == 1)
		{
			fnum = 500;
		}
		else if(pUi[1] == 3)
		{
			fnum = 1300;
		}
		else
		{
			fnum = 1000;
		}

		tmp_sr2k_de_param.shp_de_2k[0] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[0] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[1] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[1] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[2] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[2] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[3] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[3] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[4] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[4] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[5] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[5] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[6] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[6] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[7] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[7] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[8] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[8] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[9] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[9] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[10]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[10] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[11]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[11] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[12]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[12] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[13]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[13] * fnum / 1000);

		ret = KWRAP_PE_SetSre2KDetailEnhanceParam((void *)&tmp_sr2k_de_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KDetailEnhanceParam(): error %d\n", ret);
	}
	return ret;
}


static int vpq_hwrap_setsharpness_o24(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	win_id = wId;
	if(win_id == LX_PE_WIN_0)// set only @ winid=0
	{
		ret = vpq_hwrap_vsd_setsharpness_o24(pShpData, win_id, version);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_vsd_setsharpness_o24(): error %d\n", ret);
	}
	ret = vpq_hwrap_sre_setsharpness_o24(pShpData, win_id, version);
	VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_sre_setsharpness_o24(): error %d\n", ret);
	return ret;
}

static int vpq_hwrap_vsd_setsharpness_o24(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_o24_t *pChip = (vpq_hwrap_chip_shp_o24_t *)pShpData->pst_chip_data;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) PE_KWRAP_CTRL_T kwrap_ctrl;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) LX_PE_SHP_RE2_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE1_MISC_T misc_param;
	__attribute__((unused)) LX_PE_SHP_EE1_T ee_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM3_CMN_T sqm_cmn_param; //o24
	__attribute__((unused)) LX_PE_SHP_RE_SQM4_DETAIL_T sqm_dtl_param;
	__attribute__((unused)) LX_PE_SHP_DE4_T tmp_ede_param;	/* for super resolution menu   */
	__attribute__((unused)) int fnum, i;
	__attribute__((unused)) UINT8 *pd;
	__attribute__((unused)) UINT32 *pd32;
	__attribute__((unused)) UINT16 *pd16;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode = _g_vpq_hwrap_shp_platform_db_enable;
	/* 1. set post sharpness */
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (pChip)
	#else
	if ((pChip) && db_mode)
	#endif
	{
		/*vsd shp wid*/
		misc_param.win_id = cmn_param.win_id = ee_param.win_id  = win_id;
		/*sqm wid*/
		sqm_cmn_param.win_id = sqm_dtl_param.win_id = win_id;

		//memcpy //
		memcpy(&(cmn_param.shp_ui_main_vsd), \
			&(pChip->shp_ui_main_vsd), sizeof(pChip->shp_ui_main_vsd));
		cmn_param.shp_luma_en_vsd = pChip->shp_luma_en_vsd;
		memcpy(&(cmn_param.shp_face_obj_vsd), \
			&(pChip->shp_face_obj_vsd), sizeof(pChip->shp_face_obj_vsd));
		memcpy(&(misc_param.shp_djg_vsd), \
			&(pChip->shp_djg_vsd), sizeof(pChip->shp_djg_vsd));
		memcpy(&(misc_param.shp_cmn_vsd), \
			&(pChip->shp_cmn_vsd), sizeof(pChip->shp_cmn_vsd));
		memcpy(&(misc_param.shp_map_cmn_vsd), \
			&(pChip->shp_map_cmn_vsd), sizeof(pChip->shp_map_cmn_vsd));
		memcpy(&(misc_param.shp_balance_vsd), \
			&(pChip->shp_balance_vsd), sizeof(pChip->shp_balance_vsd));
		memcpy(&(misc_param.shp_ti_cmn_vsd), \
			&(pChip->shp_ti_cmn_vsd), sizeof(pChip->shp_ti_cmn_vsd));
		memcpy(&(misc_param.shp_chroma_vsd), \
			&(pChip->shp_chroma_vsd), sizeof(pChip->shp_chroma_vsd));

		pd = cmn_param.shp_ui_main_vsd;
		PQ_PRINT_SHP("set : shp_ui_main_vsd\n"
		"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd = cmn_param.shp_face_obj_vsd;
		PQ_PRINT_SHP("set : shp_face_obj_vsd\n"
		"shp_face_obj_vsd	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd	 [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd	 [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], \
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = misc_param.shp_cmn_vsd;
		PQ_PRINT_SHP("set : shp_cmn_vsd\n"
		"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = misc_param.shp_djg_vsd;
		PQ_PRINT_SHP("set : shp_djg_vsd\n"
		"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		PQ_PRINT_SHP("set : shp_luma_en_vsd: %d\n", cmn_param.shp_luma_en_vsd);
		pd = misc_param.shp_map_cmn_vsd;
		PQ_PRINT_SHP("set : shp_map_cmn_vsd\n"
		"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = misc_param.shp_balance_vsd;
		PQ_PRINT_SHP("set : shp_balance_vsd\n"
		"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
		pd = misc_param.shp_ti_cmn_vsd;
		PQ_PRINT_SHP("set : shp_ti_cmn_vsd\n"
		"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = misc_param.shp_chroma_vsd;
		PQ_PRINT_SHP("set : shp_chroma_vsd\n"
		"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4]);
		//memcpy(&(ee_param.shp_ee_vsd),&(pChip->shp_ee_vsd), sizeof(pChip->shp_ee_vsd));
		pd = pChip->shp_ee_vsd;
		PQ_PRINT_SHP("before sr weight sr-ui:%d,\n"\
		"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
	 	pUi[1],\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_vsd)/sizeof(UINT8); i++)
		{
			ee_param.shp_ee_vsd[i] = (UINT8)((UINT32)pChip->shp_ee_vsd[i] * fnum / 1000);
		}
		pd = ee_param.shp_ee_vsd;
		PQ_PRINT_SHP("after sr weight sr-ui:%d,\n"\
		"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
	 	pUi[1],\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		
		/*sqm*/
		sqm_cmn_param.shp_sqm____val = cmn_val;
		sqm_dtl_param.shp_sqm_____val = pUi[1];// add super resolution ui value AVTASK-1435, TVPM-26505
		memcpy(&(sqm_cmn_param.shp_ui_sqm_vsd), \
		&(pChip->shp_ui_sqm_vsd), sizeof(pChip->shp_ui_sqm_vsd));
		memcpy(&(sqm_dtl_param.shp_sqm_cmn_vsd), \
		&(pChip->shp_sqm_cmn_vsd), sizeof(pChip->shp_sqm_cmn_vsd));
		pd32 = sqm_cmn_param.shp_ui_sqm_vsd;
		PQ_PRINT_SHP("set : shp_ui_sqm_vsd\n"\
		"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39],\
		pd32[40],pd32[41],	pd32[42],  pd32[43], pd32[44],  pd32[45],  pd32[46],	pd32[47], pd32[48],  pd32[49]);
		pd32 = sqm_dtl_param.shp_sqm_cmn_vsd;
		PQ_PRINT_SHP("set : shp_sqm_cmn_vsd\n"\
		"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[70]0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39],\
		pd32[40],pd32[41],	pd32[42],  pd32[43], pd32[34],  pd32[45],  pd32[46],	pd32[47], pd32[48],  pd32[49],\
		pd32[50],pd32[51],	pd32[52],  pd32[53], pd32[34],  pd32[55],  pd32[56],	pd32[57], pd32[58],  pd32[59],\
		pd32[60],pd32[61],	pd32[62],  pd32[63], pd32[34],  pd32[65],  pd32[66],	pd32[67], pd32[68],  pd32[69],\
		pd32[70]);

		ret = PE_SHP_SetReCmnCtrl((void *)&cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetReMiscCtrl((void *)&misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReMiscCtrl(): error %d\n", ret);
		ret = PE_SHP_SetEdgeEnhanceCtrl((void *)&ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetEdgeEnhanceCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSqmCmnCtrl((void *)&sqm_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSqmCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSqmDetailCtrl((void *)&sqm_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSqmDetailCtrl(): error %d\n", ret);
	}
	else
	{
		tmp_ede_param.win_id  = win_id;
		/* 1. set post sharpness */
		{
			kwrap_ctrl.wid = win_id;
			kwrap_ctrl.data = cmn_val;
			ret = KWRAP_PE_SetRenCmnCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetRenCmnCtrl(): error %d\n", ret);

			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = PE_KWRAP_SHP_FMT_HD;
			//ret = KWRAP_PE_SetRenMiscCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenMiscCtrl() \n", __F__, __L__);

			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenHorCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenHorCtrl() \n", __F__, __L__);
			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenVerCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenVerCtrl() \n", __F__, __L__);
			
			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = (UINT32)cmn_val;
			//ret = KWRAP_PE_SetRenSqmCmnCtrl(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenSqmCmnCtrl(): error %d \n", __F__, __L__, ret);

			kwrap_ctrl.wid = win_id;
			kwrap_ctrl.data = cmn_val;
			kwrap_ctrl.st_data = (void*)&tmp_ede_param;
			ret = KWRAP_PE_GetDetailEnhanceDefaultSettings(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetDetailEnhanceDefaultSettings(): error %d\n", ret);
			tmp_ede_param.win_id = win_id;
			pd = tmp_ede_param.shp_de_vsd;
			PQ_PRINT_SHP("before sr weight sr-ui:%d,\n"\
				"shp_ee_vsd   [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_vsd   [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pUi[1],\
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10],pd[11],pd[12],pd[13]);

			if(pUi[1] == 0)
			{
				fnum = 0;
			}
			else if(pUi[1] == 1)
			{
				fnum = 500;
			}
			else if(pUi[1] == 3)
			{
				fnum = 1300;
			}
			else
			{
				fnum = 1000;
			}

			tmp_ede_param.shp_de_vsd[0] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[1] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[2] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[3] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[4] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[5] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[6] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[7] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[8] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[9] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[10]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[11]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[12]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[13]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			PQ_PRINT_SHP("after sr weight sr-ui:%d,\n"\
				"shp_ee_vsd   [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_vsd   [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pUi[1],\
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10],pd[11],pd[12],pd[13]);

			ret = KWRAP_PE_SetDetailEnhanceParam((void *)&tmp_ede_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDetailEnhanceParam(): error %d\n", ret);


		}
	}
	
	return ret;
}

static int vpq_hwrap_sre_setsharpness_o24(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_o24_t *pChip = (vpq_hwrap_chip_shp_o24_t *)pShpData->pst_chip_data;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) PE_KWRAP_CTRL_T kwrap_ctrl;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_CMN_T sr2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_MISC_T sr2k_misc_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_EE1_T sr2k_ee_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM3_CMN_T sqm2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM3_DETAIL_T sqm2k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_DE_T tmp_sr2k_de_param; /* for super resolution menu */
	__attribute__((unused)) LX_PE_SHP_SR_RE1_CMN_SUB_T sr_sub_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR_RE1_MISC_SUB_T sr_sub_misc_param;
	__attribute__((unused)) int fnum, i;
	__attribute__((unused)) UINT8 *pd;
	__attribute__((unused)) UINT32 *pd32;
	__attribute__((unused)) UINT16 *pd16;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode = _g_vpq_hwrap_shp_platform_db_enable;
	/* 2. set pre sharpness */
	if (pChip && db_mode)
	{
		/*sre shp*/
		/*2k*/
		sr2k_misc_param.win_id = sr2k_cmn_param.win_id = sr2k_ee_param.win_id = win_id;
		/*sqm*/
		sqm2k_cmn_param.win_id = sqm2k_dtl_param.win_id = win_id;

		memcpy(&(sr2k_cmn_param.shp_ui_main_2k), \
			&(pChip->shp_ui_main_2k), sizeof(pChip->shp_ui_main_2k));
		sr2k_cmn_param.shp_luma_en_2k = pChip->shp_luma_en_2k;
		memcpy(&(sr2k_cmn_param.shp_dnn_sr_vsd), \
			&(pChip->shp_dnn_sr_vsd), sizeof(pChip->shp_dnn_sr_vsd));
		memcpy(&(sr2k_misc_param.shp_cmn_2k), \
			&(pChip->shp_cmn_2k), sizeof(pChip->shp_cmn_2k));
		memcpy(&(sr2k_misc_param.shp_djg_2k), \
			&(pChip->shp_djg_2k), sizeof(pChip->shp_djg_2k));
		memcpy(&(sr2k_misc_param.shp_map_cmn_2k), \
			&(pChip->shp_map_cmn_2k), sizeof(pChip->shp_map_cmn_2k));
		memcpy(&(sr2k_misc_param.shp_balance_2k), \
			&(pChip->shp_balance_2k), sizeof(pChip->shp_balance_2k));
		memcpy(&(sr2k_misc_param.shp_ti_cmn_2k), \
			&(pChip->shp_ti_cmn_2k), sizeof(pChip->shp_ti_cmn_2k));
		//memcpy(&(sr2k_ee_param.shp_ee_2k),&(pChip->shp_ee_2k), sizeof(pChip->shp_ee_2k));
		
		pd = sr2k_cmn_param.shp_ui_main_2k;
		PQ_PRINT_SRE("set[%d] : shp_ui_main_2k\n"
		"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_2k    [10]0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd16 = sr2k_cmn_param.shp_dnn_sr_vsd;
		PQ_PRINT_SRE("set[%d] : shp_dnn_sr_vsd\n"
		"shp_dnn_sr_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_dnn_sr_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",win_id,\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16]);
		pd = sr2k_misc_param.shp_cmn_2k;
		PQ_PRINT_SRE("set[%d] : shp_cmn_2k\n"
		"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);

		pd = sr2k_misc_param.shp_djg_2k;
		PQ_PRINT_SRE("set[%d] : shp_djg_2k\n"
		"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

		PQ_PRINT_SRE("set[%d] : shp_luma_en_2k: %d\n", win_id, sr2k_cmn_param.shp_luma_en_2k);
		pd = sr2k_misc_param.shp_map_cmn_2k;
		PQ_PRINT_SRE("set[%d] : shp_map_cmn_2k\n"
		"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_2k    [10]0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = sr2k_misc_param.shp_balance_2k;

		PQ_PRINT_SRE("set[%d] : shp_balance_2k\n"
		"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

		pd = sr2k_misc_param.shp_ti_cmn_2k;
		PQ_PRINT_SRE("set[%d] : shp_ti_cmn_2k\n"
		"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = pChip->shp_ee_2k;
		PQ_PRINT_SRE("set[%d] before sr weight sr-ui:%d, size:%zu \n"\
		"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
	 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_2k)/sizeof(UINT8); i++)
		{
			sr2k_ee_param.shp_ee_2k[i] = (UINT8)((UINT32)pChip->shp_ee_2k[i] * fnum / 1000);
		}
		pd = sr2k_ee_param.shp_ee_2k;
		PQ_PRINT_SRE("set[%d] after sr weight sr-ui:%d, size:%zu \n"\
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		/*sqm*/
		sqm2k_cmn_param.shp_sqm___val= cmn_val;
		sqm2k_dtl_param.shp_sqm____val = pUi[1];// add super resolution ui value AVTASK-1435, TVPM-26505
		memcpy(&(sqm2k_cmn_param.shp_ui_sqm_2k), \
		&(pChip->shp_ui_sqm_2k), sizeof(pChip->shp_ui_sqm_2k));
		memcpy(&(sqm2k_dtl_param.shp_sqm_cmn_2k), \
		&(pChip->shp_sqm_cmn_2k), sizeof(pChip->shp_sqm_cmn_2k));
		pd32 = sqm2k_cmn_param.shp_ui_sqm_2k;
		PQ_PRINT_SRE("set[%d] : shp_ui_sqm_2k\n"
		"shp_ui_sqm_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,,0x%02X,\n"\
		"shp_ui_sqm_2k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",win_id,\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19],\
		pd32[20], pd32[21], pd32[22], pd32[23], pd32[24], pd32[25], pd32[26], pd32[27], pd32[28], pd32[29],\
		pd32[30], pd32[31], pd32[32], pd32[33], pd32[34], pd32[35], pd32[36], pd32[37], pd32[38], pd32[39],\
		pd32[40], pd32[41], pd32[42], pd32[43], pd32[44], pd32[45], pd32[46], pd32[47], pd32[48]);
		pd32  = sqm2k_dtl_param.shp_sqm_cmn_2k;
		PQ_PRINT_SRE("set[%d] : shp_sqm_cmn_2k\n"\
		"shp_sqm_cmn_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[50]0x%08X\n",win_id,\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],  pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17],  pd32[18],	pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23], pd32[24],	pd32[25],  pd32[26],  pd32[27],  pd32[28],	pd32[29],\
		pd32[30],  pd32[31],  pd32[32],  pd32[33], pd32[34],	pd32[35],  pd32[36],  pd32[37],  pd32[38],	pd32[39],\
		pd32[40],  pd32[41],  pd32[42],  pd32[43], pd32[44],	pd32[45],  pd32[46],  pd32[47],  pd32[48],	pd32[49],\
		pd32[50]);
		if(win_id == LX_PE_WIN_0)
		{
			ret = PE_SHP_SetSre2KReCmnCtrl((void *)&sr2k_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KReCmnCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSre2KReMiscCtrl((void *)&sr2k_misc_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KReMiscCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSre2KEdgeEnhanceCtrl((void *)&sr2k_ee_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KEdgeEnhanceCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSre2KSqmCmnCtrl((void *)&sqm2k_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KSqmCmnCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSre2KSqmDetailCtrl((void *)&sqm2k_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KSqmDetailCtrl(): error %d\n", ret);
		}
		else
		{
			sr_sub_cmn_param.win_id = sr_sub_misc_param.win_id= win_id;
			memcpy(&(sr_sub_cmn_param.sr_sub_cmn_ui), \
			&sr2k_cmn_param, sizeof(sr2k_cmn_param));
			memcpy(&(sr_sub_cmn_param.sr_sub_sqm_ui), \
			&sqm2k_cmn_param, sizeof(sqm2k_cmn_param));
			memcpy(&(sr_sub_misc_param.sr_sub_misc), \
			&sr2k_misc_param, sizeof(sr2k_misc_param));
			memcpy(&(sr_sub_misc_param.sr_sub_sqm_cmn), \
			&sqm2k_dtl_param, sizeof(sqm2k_dtl_param));
			ret = PE_SHP_SetSreSubReCmnCtrl((void *)&sr_sub_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreSubReCmnCtrl(): error %d\n", ret);
			ret = PE_SHP_SetSreSubReMiscCtrl((void *)&sr_sub_misc_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreSubReMiscCtrl(): error %d\n", ret);
		
		}
		
	}
	else if(win_id == LX_PE_WIN_0)
	{
		tmp_sr2k_de_param.win_id  = win_id;
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		PQ_PRINT_SRE("wid_id:%d, cmn_val:%d (kwrap)\n",win_id,cmn_val);
		ret = KWRAP_PE_SetSre2KRenCmnCtrl((void *)&kwrap_ctrl);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KRenCmnCtrl(): error %d\n", ret);
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		kwrap_ctrl.st_data = (void*)&tmp_sr2k_de_param;
		
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		ret = KWRAP_PE_SetSre2KSqmCmnCtrl((void *)&kwrap_ctrl);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KSqmCmnCtrl(): error %d\n", ret);

		ret = KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(&kwrap_ctrl);
		tmp_sr2k_de_param.win_id = win_id;
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(): error %d\n", ret);

		if(pUi[1] == 0)
		{
			fnum = 0;
		}
		else if(pUi[1] == 1)
		{
			fnum = 500;
		}
		else if(pUi[1] == 3)
		{
			fnum = 1300;
		}
		else
		{
			fnum = 1000;
		}

		tmp_sr2k_de_param.shp_de_2k[0] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[0] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[1] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[1] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[2] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[2] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[3] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[3] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[4] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[4] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[5] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[5] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[6] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[6] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[7] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[7] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[8] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[8] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[9] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[9] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[10]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[10] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[11]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[11] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[12]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[12] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[13]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[13] * fnum / 1000);

		ret = KWRAP_PE_SetSre2KDetailEnhanceParam((void *)&tmp_sr2k_de_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KDetailEnhanceParam(): error %d\n", ret);
	}
	return ret;
}


static int vpq_hwrap_setsharpness_o22(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_o22_t *pChip = (vpq_hwrap_chip_shp_o22_t *)pShpData->pst_chip_data;
	__attribute__((unused)) vpq_hwrap_chip_shp_o22n2_t *pChip_n2 = (vpq_hwrap_chip_shp_o22n2_t *)pShpData->pst_chip_data;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) PE_KWRAP_CTRL_T kwrap_ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) LX_PE_SHP_RE2_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE1_MISC_T misc_param;
	__attribute__((unused)) LX_PE_SHP_EE1_T ee_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_CMN_T sr2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_MISC_T sr2k_misc_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_EE1_T sr2k_ee_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM_CMN_T c_sqm_cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM_DETAIL_T c_sqm_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM_CMN_T c_sqm2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM_DETAIL_T c_sqm2k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM2_CMN_T sqm_cmn_param; //o22, m23, o22n
	__attribute__((unused)) LX_PE_SHP_RE_SQM3_CMN_T sqm_cmn_param_n2; //o22n2
	__attribute__((unused)) LX_PE_SHP_RE_SQM4_DETAIL_T sqm_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM2_CMN_T sqm2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM3_CMN_T sqm2k_cmn_param_n2;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM2_DETAIL_T sqm2k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_DE_T tmp_sr2k_de_param; /* for super resolution menu */
	__attribute__((unused)) LX_PE_SHP_DE4_T tmp_ede_param;	/* for super resolution menu   */
	__attribute__((unused)) int fnum;
	__attribute__((unused)) int i;
	__attribute__((unused)) UINT8 *pd;
	__attribute__((unused)) UINT32 *pd32;
	__attribute__((unused)) UINT16 *pd16;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode = _g_vpq_hwrap_shp_platform_db_enable;
	if (PE_KDRV_VER_O22 || PE_KDRV_VER_M23)
		db_mode = 1;
	/* 1. set post sharpness */
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (pChip ||pChip_n2)
	#else
	if ((pChip ||pChip_n2) && db_mode)
	#endif
	{
		/*vsd shp wid*/
		misc_param.win_id = cmn_param.win_id = ee_param.win_id  = win_id;
		/*sqm wid*/
		c_sqm_cmn_param.win_id = c_sqm_dtl_param.win_id = win_id;
		sqm_cmn_param.win_id = sqm_cmn_param_n2.win_id = sqm_dtl_param.win_id = win_id;

		c_sqm_cmn_param.oper = c_sqm_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm_dtl_param.size = sizeof(LX_PE_SHP_RE_SQM4_DETAIL_T);
		c_sqm_dtl_param.data = (UINT32 *)&sqm_dtl_param;
		if(version == 0x60) //o22n2
		{
			c_sqm_cmn_param.data = (UINT32 *)&sqm_cmn_param_n2;
			c_sqm_cmn_param.size = sizeof(LX_PE_SHP_RE_SQM3_CMN_T);
		}
		else // o22, o22n, m23
		{
			c_sqm_cmn_param.data = (UINT32 *)&sqm_cmn_param;
			c_sqm_cmn_param.size = sizeof(LX_PE_SHP_RE_SQM2_CMN_T);
		}
		//memcpy //
		if(version == 0x60) //o22n2
		{
			memcpy(&(cmn_param.shp_ui_main_vsd), \
				&(pChip_n2->shp_ui_main_vsd), sizeof(pChip_n2->shp_ui_main_vsd));
			memcpy(&(cmn_param.shp_face_obj_vsd), \
				&(pChip_n2->shp_face_obj_vsd), sizeof(pChip_n2->shp_face_obj_vsd));
			memcpy(&(misc_param.shp_djg_vsd), \
				&(pChip_n2->shp_djg_vsd), sizeof(pChip_n2->shp_djg_vsd));
			memcpy(&(misc_param.shp_cmn_vsd), \
				&(pChip_n2->shp_cmn_vsd), sizeof(pChip_n2->shp_cmn_vsd));
			memcpy(&(misc_param.shp_map_cmn_vsd), \
				&(pChip_n2->shp_map_cmn_vsd), sizeof(pChip_n2->shp_map_cmn_vsd));
			memcpy(&(misc_param.shp_balance_vsd), \
				&(pChip_n2->shp_balance_vsd), sizeof(pChip_n2->shp_balance_vsd));
			memcpy(&(misc_param.shp_ti_cmn_vsd), \
				&(pChip_n2->shp_ti_cmn_vsd), sizeof(pChip_n2->shp_ti_cmn_vsd));
			memcpy(&(misc_param.shp_chroma_vsd), \
				&(pChip_n2->shp_chroma_vsd), sizeof(pChip_n2->shp_chroma_vsd));
		}
		else // o22, o22n, m23
		{
			memcpy(&(cmn_param.shp_ui_main_vsd), \
				&(pChip->shp_ui_main_vsd), sizeof(pChip->shp_ui_main_vsd));
			memcpy(&(cmn_param.shp_face_obj_vsd), \
				&(pChip->shp_face_obj_vsd), sizeof(pChip->shp_face_obj_vsd));
			memcpy(&(misc_param.shp_djg_vsd), \
				&(pChip->shp_djg_vsd), sizeof(pChip->shp_djg_vsd));
			memcpy(&(misc_param.shp_cmn_vsd), \
				&(pChip->shp_cmn_vsd), sizeof(pChip->shp_cmn_vsd));
			memcpy(&(misc_param.shp_map_cmn_vsd), \
				&(pChip->shp_map_cmn_vsd), sizeof(pChip->shp_map_cmn_vsd));
			memcpy(&(misc_param.shp_balance_vsd), \
				&(pChip->shp_balance_vsd), sizeof(pChip->shp_balance_vsd));
			memcpy(&(misc_param.shp_ti_cmn_vsd), \
				&(pChip->shp_ti_cmn_vsd), sizeof(pChip->shp_ti_cmn_vsd));
			memcpy(&(misc_param.shp_chroma_vsd), \
				&(pChip->shp_chroma_vsd), sizeof(pChip->shp_chroma_vsd));
		}

		pd = cmn_param.shp_ui_main_vsd;
		PE_PRINT_SHP("set : shp_ui_main_vsd\n"
		"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd = cmn_param.shp_face_obj_vsd;
		PE_PRINT_SHP("set : shp_face_obj_vsd\n"
		"shp_face_obj_vsd	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd	 [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd	 [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], \
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = misc_param.shp_cmn_vsd;
		PE_PRINT_SHP("set : shp_cmn_vsd\n"
		"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = misc_param.shp_djg_vsd;
		PE_PRINT_SHP("set : shp_djg_vsd\n"
		"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = misc_param.shp_map_cmn_vsd;
		PE_PRINT_SHP("set : shp_map_cmn_vsd\n"
		"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = misc_param.shp_balance_vsd;
		PE_PRINT_SHP("set : shp_balance_vsd\n"
		"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
		pd = misc_param.shp_ti_cmn_vsd;
		PE_PRINT_SHP("set : shp_ti_cmn_vsd\n"
		"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = misc_param.shp_chroma_vsd;
		PE_PRINT_SHP("set : shp_chroma_vsd\n"
		"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4]);
		//memcpy(&(ee_param.shp_ee_vsd),&(pChip->shp_ee_vsd), sizeof(pChip->shp_ee_vsd));
		if(version == 0x60) //o22n2
			pd = pChip_n2->shp_ee_vsd;
		else                // o22, o22n, o22n2, m23
			pd = pChip->shp_ee_vsd;
		PE_PRINT_SHP("before sr weight sr-ui:%d,\n"\
		"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
	 	pUi[1],\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		if(version == 0x60) //o22n2
		{
			for(i=0; i < sizeof(pChip_n2->shp_ee_vsd)/sizeof(UINT8); i++)
			{
				ee_param.shp_ee_vsd[i] = (UINT8)((UINT32)pChip_n2->shp_ee_vsd[i] * fnum / 1000);
			}
		}
		else               // o22, o22n, m23
		{
			for(i=0; i < sizeof(pChip->shp_ee_vsd)/sizeof(UINT8); i++)
			{
				ee_param.shp_ee_vsd[i] = (UINT8)((UINT32)pChip->shp_ee_vsd[i] * fnum / 1000);
			}
		}
		pd = ee_param.shp_ee_vsd;
		PE_PRINT_SHP("after sr weight sr-ui:%d,\n"\
		"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
	 	pUi[1],\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		
		/*sqm*/
		if(version == 0x60) //o22n2
		{
			sqm_cmn_param_n2.shp_sqm____val = cmn_val;
			sqm_dtl_param.shp_sqm_____val = pUi[1];// add super resolution ui value AVTASK-1435, TVPM-26505
			memcpy(&(sqm_cmn_param_n2.shp_ui_sqm_vsd), \
			&(pChip_n2->shp_ui_sqm_vsd), sizeof(pChip_n2->shp_ui_sqm_vsd));
			memcpy(&(sqm_dtl_param.shp_sqm_cmn_vsd), \
			&(pChip_n2->shp_sqm_cmn_vsd), sizeof(pChip_n2->shp_sqm_cmn_vsd));
			pd32 = sqm_cmn_param_n2.shp_ui_sqm_vsd;
			PE_PRINT_SHP("set : shp_ui_sqm_vsd\n"\
			"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
			pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
			pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
			pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
			pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39],\
			pd32[40],pd32[41],	pd32[42],  pd32[43], pd32[44],  pd32[45],  pd32[46],	pd32[47], pd32[48],  pd32[49]);
		}
		else               // o22, o22n, m23
		{
			sqm_cmn_param.shp_sqm____val = cmn_val;
			sqm_dtl_param.shp_sqm_____val = 0x0;
			memcpy(&(sqm_cmn_param.shp_ui_sqm_vsd), \
			&(pChip->shp_ui_sqm_vsd), sizeof(pChip->shp_ui_sqm_vsd));
			memcpy(&(sqm_dtl_param.shp_sqm_cmn_vsd), \
			&(pChip->shp_sqm_cmn_vsd), sizeof(pChip->shp_sqm_cmn_vsd));
			pd32 = sqm_cmn_param.shp_ui_sqm_vsd;
			PE_PRINT_SHP("set : shp_ui_sqm_vsd\n"\
			"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
			pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
			pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
			pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
			pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39]);
		}
		pd32 = sqm_dtl_param.shp_sqm_cmn_vsd;
		PE_PRINT_SHP("set : shp_sqm_cmn_vsd\n"\
		"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[70]0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39],\
		pd32[40],pd32[41],	pd32[42],  pd32[43], pd32[34],  pd32[45],  pd32[46],	pd32[47], pd32[48],  pd32[49],\
		pd32[50],pd32[51],	pd32[52],  pd32[53], pd32[34],  pd32[55],  pd32[56],	pd32[57], pd32[58],  pd32[59],\
		pd32[60],pd32[61],	pd32[62],  pd32[63], pd32[34],  pd32[65],  pd32[66],	pd32[67], pd32[68],  pd32[69],\
		pd32[70]);

		ret = PE_SHP_SetReCmnCtrl((void *)&cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetReMiscCtrl((void *)&misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReMiscCtrl(): error %d\n", ret);
		ret = PE_SHP_SetEdgeEnhanceCtrl((void *)&ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetEdgeEnhanceCtrl(): error %d\n", ret);
		if(version == 0x60) //o22n2
			ret = PE_SHP_SetSqmCmnCtrl2((void *)&c_sqm_cmn_param);
		else // o22, o22n, m23
			ret = PE_SHP_SetSqmCmnCtrl((void *)&c_sqm_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSqmCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSqmDetailCtrl((void *)&c_sqm_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSqmDetailCtrl(): error %d\n", ret);
	}
	else
	{
		tmp_ede_param.win_id  = win_id;
		/* 1. set post sharpness */
		{
			kwrap_ctrl.wid = win_id;
			kwrap_ctrl.data = cmn_val;
			ret = KWRAP_PE_SetRenCmnCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetRenCmnCtrl(): error %d\n", ret);

			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = PE_KWRAP_SHP_FMT_HD;
			//ret = KWRAP_PE_SetRenMiscCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenMiscCtrl() \n", __F__, __L__);

			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenHorCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenHorCtrl() \n", __F__, __L__);
			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenVerCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenVerCtrl() \n", __F__, __L__);
			
			dbtype = LX_PE_PLATFORM_NUM; //easy DB
			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = (UINT32)cmn_val;
			kwrap_ctrl.st_data = (void *)&dbtype;
			//ret = KWRAP_PE_SetRenSqmCmnCtrl(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenSqmCmnCtrl(): error %d \n", __F__, __L__, ret);

			kwrap_ctrl.wid = win_id;
			kwrap_ctrl.data = cmn_val;
			kwrap_ctrl.st_data = (void*)&tmp_ede_param;
			ret = KWRAP_PE_GetDetailEnhanceDefaultSettings(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetDetailEnhanceDefaultSettings(): error %d\n", ret);
			tmp_ede_param.win_id = win_id;
			pd = tmp_ede_param.shp_de_vsd;
			PE_PRINT_SHP("before sr weight sr-ui:%d,\n"\
				"shp_ee_vsd   [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_vsd   [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pUi[1],\
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10],pd[11],pd[12],pd[13]);

			if(pUi[1] == 0)
			{
				fnum = 0;
			}
			else if(pUi[1] == 1)
			{
				fnum = 500;
			}
			else if(pUi[1] == 3)
			{
				fnum = 1300;
			}
			else
			{
				fnum = 1000;
			}

			tmp_ede_param.shp_de_vsd[0] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[1] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[2] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[3] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[4] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[5] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[6] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[7] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[8] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[9] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[10]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[11]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[12]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[13]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			PE_PRINT_SHP("after sr weight sr-ui:%d,\n"\
				"shp_ee_vsd   [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_vsd   [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pUi[1],\
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10],pd[11],pd[12],pd[13]);

			ret = KWRAP_PE_SetDetailEnhanceParam((void *)&tmp_ede_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDetailEnhanceParam(): error %d\n", ret);


		}
	}
	/* 2. set pre sharpness */
	if (pChip && db_mode)
	{
		/*sre shp*/
		/*sqm*/
		c_sqm2k_cmn_param.win_id = c_sqm2k_dtl_param.win_id = win_id;
		sqm2k_cmn_param.win_id =sqm2k_cmn_param_n2.win_id = sqm2k_dtl_param.win_id = win_id;
		c_sqm2k_cmn_param.oper = c_sqm2k_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm2k_dtl_param.size = sizeof(LX_PE_SHP_SR2K_SQM2_DETAIL_T);
		if(version == 0x60) //o22n2
		{
			c_sqm2k_cmn_param.data = (UINT32 *)&sqm2k_cmn_param_n2;
			c_sqm2k_cmn_param.size = sizeof(LX_PE_SHP_SR2K_SQM3_CMN_T);
		}
		else // o22, o22n, m23
		{
			c_sqm2k_cmn_param.data = (UINT32 *)&sqm2k_cmn_param;
			c_sqm2k_cmn_param.size = sizeof(LX_PE_SHP_SR2K_SQM2_CMN_T);
		}
		c_sqm2k_dtl_param.data = (UINT32 *)&sqm2k_dtl_param;
		/*2k*/
		sr2k_misc_param.win_id = sr2k_cmn_param.win_id = sr2k_ee_param.win_id = win_id;
		if(version == 0x60) //o22n2
		{
			memcpy(&(sr2k_cmn_param.shp_ui_main_2k), \
				&(pChip_n2->shp_ui_main_2k), sizeof(pChip_n2->shp_ui_main_2k));
			memcpy(&(sr2k_cmn_param.shp_dnn_sr_vsd), \
				&(pChip_n2->shp_dnn_sr_vsd), sizeof(pChip_n2->shp_dnn_sr_vsd));
			memcpy(&(sr2k_misc_param.shp_cmn_2k), \
				&(pChip_n2->shp_cmn_2k), sizeof(pChip_n2->shp_cmn_2k));
			memcpy(&(sr2k_misc_param.shp_djg_2k), \
				&(pChip_n2->shp_djg_2k), sizeof(pChip_n2->shp_djg_2k));
			memcpy(&(sr2k_misc_param.shp_map_cmn_2k), \
				&(pChip_n2->shp_map_cmn_2k), sizeof(pChip_n2->shp_map_cmn_2k));
			memcpy(&(sr2k_misc_param.shp_balance_2k), \
				&(pChip_n2->shp_balance_2k), sizeof(pChip_n2->shp_balance_2k));
			memcpy(&(sr2k_misc_param.shp_ti_cmn_2k), \
				&(pChip_n2->shp_ti_cmn_2k), sizeof(pChip_n2->shp_ti_cmn_2k));
		}
		else // o22, o22n, m23
		{
			memcpy(&(sr2k_cmn_param.shp_ui_main_2k), \
				&(pChip->shp_ui_main_2k), sizeof(pChip->shp_ui_main_2k));
			memcpy(&(sr2k_cmn_param.shp_dnn_sr_vsd), \
				&(pChip->shp_dnn_sr_vsd), sizeof(pChip->shp_dnn_sr_vsd));
			memcpy(&(sr2k_misc_param.shp_cmn_2k), \
				&(pChip->shp_cmn_2k), sizeof(pChip->shp_cmn_2k));
			memcpy(&(sr2k_misc_param.shp_djg_2k), \
				&(pChip->shp_djg_2k), sizeof(pChip->shp_djg_2k));
			memcpy(&(sr2k_misc_param.shp_map_cmn_2k), \
				&(pChip->shp_map_cmn_2k), sizeof(pChip->shp_map_cmn_2k));
			memcpy(&(sr2k_misc_param.shp_balance_2k), \
				&(pChip->shp_balance_2k), sizeof(pChip->shp_balance_2k));
			memcpy(&(sr2k_misc_param.shp_ti_cmn_2k), \
				&(pChip->shp_ti_cmn_2k), sizeof(pChip->shp_ti_cmn_2k));
		}
		//memcpy(&(sr2k_ee_param.shp_ee_2k),&(pChip->shp_ee_2k), sizeof(pChip->shp_ee_2k));
		
		pd = sr2k_cmn_param.shp_ui_main_2k;
		PE_PRINT_SHP("set : shp_ui_main_2k\n"
		"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_2k    [10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd16 = sr2k_cmn_param.shp_dnn_sr_vsd;
		PE_PRINT_SHP("set : shp_dnn_sr_vsd\n"
		"shp_dnn_sr_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8]);
		pd = sr2k_misc_param.shp_cmn_2k;
		PE_PRINT_SHP("set : shp_cmn_2k\n"
		"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);

		pd = sr2k_misc_param.shp_djg_2k;
		PE_PRINT_SHP("set : shp_djg_2k\n"
		"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

		pd = sr2k_misc_param.shp_map_cmn_2k;
		PE_PRINT_SHP("set : shp_map_cmn_2k\n"
		"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_2k    [10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = sr2k_misc_param.shp_balance_2k;

		PE_PRINT_SHP("set : shp_balance_2k\n"
		"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

		pd = sr2k_misc_param.shp_ti_cmn_2k;
		PE_PRINT_SHP("set : shp_ti_cmn_2k\n"
		"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = pChip->shp_ee_2k;
		PE_PRINT_SHP("before sr weight sr-ui:%d, size:%zu \n"\
		"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
	 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
	 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
	 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
	 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		if(version == 0x60) //o22n2
		{
			for(i=0; i < sizeof(pChip_n2->shp_ee_2k)/sizeof(UINT8); i++)
			{
				sr2k_ee_param.shp_ee_2k[i] = (UINT8)((UINT32)pChip_n2->shp_ee_2k[i] * fnum / 1000);
			}
		}
		else
		{
			for(i=0; i < sizeof(pChip->shp_ee_2k)/sizeof(UINT8); i++)
			{
				sr2k_ee_param.shp_ee_2k[i] = (UINT8)((UINT32)pChip->shp_ee_2k[i] * fnum / 1000);
			}
		}
		pd = sr2k_ee_param.shp_ee_2k;
		PE_PRINT_SHP("after sr weight sr-ui:%d\n"\
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		/*sqm*/
		if(version == 0x60) //o22n2
		{
			sqm2k_cmn_param_n2.shp_sqm___val= cmn_val;
			sqm2k_dtl_param.shp_sqm____val = pUi[1];// add super resolution ui value AVTASK-1435, TVPM-26505
			memcpy(&(sqm2k_cmn_param_n2.shp_ui_sqm_2k), \
			&(pChip_n2->shp_ui_sqm_2k), sizeof(pChip_n2->shp_ui_sqm_2k));
			memcpy(&(sqm2k_dtl_param.shp_sqm_cmn_2k), \
			&(pChip_n2->shp_sqm_cmn_2k), sizeof(pChip_n2->shp_sqm_cmn_2k));
			pd32 = sqm2k_cmn_param_n2.shp_ui_sqm_2k;
			PE_PRINT_SHP("set : shp_ui_sqm_2k o22n2\n"
			"shp_ui_sqm_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
			pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19],\
			pd32[20], pd32[21], pd32[22], pd32[23], pd32[24], pd32[25], pd32[26], pd32[27], pd32[28], pd32[29],\
			pd32[30], pd32[31], pd32[32], pd32[33], pd32[34], pd32[35], pd32[36], pd32[37], pd32[38], pd32[39],\
			pd32[40], pd32[41], pd32[42], pd32[43], pd32[44], pd32[45], pd32[46], pd32[47], pd32[48]);
		}
		else // o22, o22n, m23
		{
			sqm2k_cmn_param.shp_sqm___val= cmn_val;
			sqm2k_dtl_param.shp_sqm____val = 0x0;
			memcpy(&(sqm2k_cmn_param.shp_ui_sqm_2k), \
			&(pChip->shp_ui_sqm_2k), sizeof(pChip->shp_ui_sqm_2k));
			memcpy(&(sqm2k_dtl_param.shp_sqm_cmn_2k), \
			&(pChip->shp_sqm_cmn_2k), sizeof(pChip->shp_sqm_cmn_2k));
			pd32 = sqm2k_cmn_param.shp_ui_sqm_2k;
			PE_PRINT_SHP("set : shp_ui_sqm_2k\n"
			"shp_ui_sqm_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
			pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19],\
			pd32[20], pd32[21], pd32[22], pd32[23], pd32[24], pd32[25], pd32[26], pd32[27], pd32[28], pd32[29],\
			pd32[30], pd32[31], pd32[32], pd32[33], pd32[34], pd32[35], pd32[36], pd32[37], pd32[38]);
		}
		pd32  = sqm2k_dtl_param.shp_sqm_cmn_2k;
		PE_PRINT_SHP("set : shp_sqm_cmn_2k\n"\
		"shp_sqm_cmn_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[40]0x%08X,0x%08X,0x%08X,\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],  pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17],  pd32[18],	pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23], pd32[24],	pd32[25],  pd32[26],  pd32[27],  pd32[28],	pd32[29],\
		pd32[30],  pd32[31],  pd32[32],  pd32[33], pd32[34],	pd32[35],  pd32[36],  pd32[37],  pd32[38],	pd32[39],\
		pd32[40],  pd32[41],  pd32[42]);

		ret = PE_SHP_SetSre2KReCmnCtrl((void *)&sr2k_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSre2KReMiscCtrl((void *)&sr2k_misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KReMiscCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSre2KEdgeEnhanceCtrl((void *)&sr2k_ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KEdgeEnhanceCtrl(): error %d\n", ret);
		if(version == 0x60) //o22n2
			ret = PE_SHP_SetSre2KSqmCmnCtrl2((void *)&c_sqm2k_cmn_param);
		else // o22, o22n, m23
			ret = PE_SHP_SetSre2KSqmCmnCtrl((void *)&c_sqm2k_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KSqmCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSre2KSqmDetailCtrl((void *)&c_sqm2k_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KSqmDetailCtrl(): error %d\n", ret);
		
	}
	else
	{
		tmp_sr2k_de_param.win_id  = win_id;
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		ret = KWRAP_PE_SetSre2KRenCmnCtrl((void *)&kwrap_ctrl);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KRenCmnCtrl(): error %d\n", ret);
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		kwrap_ctrl.st_data = (void*)&tmp_sr2k_de_param;
		
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		ret = KWRAP_PE_SetSre2KSqmCmnCtrl((void *)&kwrap_ctrl);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KSqmCmnCtrl(): error %d\n", ret);

		ret = KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(&kwrap_ctrl);
		tmp_sr2k_de_param.win_id = win_id;
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(): error %d\n", ret);

		if(pUi[1] == 0)
		{
			fnum = 0;
		}
		else if(pUi[1] == 1)
		{
			fnum = 500;
		}
		else if(pUi[1] == 3)
		{
			fnum = 1300;
		}
		else
		{
			fnum = 1000;
		}

		tmp_sr2k_de_param.shp_de_2k[0] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[0] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[1] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[1] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[2] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[2] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[3] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[3] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[4] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[4] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[5] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[5] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[6] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[6] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[7] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[7] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[8] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[8] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[9] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[9] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[10]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[10] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[11]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[11] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[12]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[12] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[13]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[13] * fnum / 1000);

		ret = KWRAP_PE_SetSre2KDetailEnhanceParam((void *)&tmp_sr2k_de_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KDetailEnhanceParam(): error %d\n", ret);
	}
	return ret;
}


static int vpq_hwrap_setsharpness_o20(vpq_hwrap_shp_t *pShpData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_o20_t *pChip = (vpq_hwrap_chip_shp_o20_t *)pShpData->pst_chip_data;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) PE_KWRAP_CTRL_T kwrap_ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) LX_PE_SHP_RE1_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE1_MISC_T misc_param;
	__attribute__((unused)) LX_PE_SHP_EE1_T ee_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_CMN_T sr2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_MISC_T sr2k_misc_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_EE1_T sr2k_ee_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM_CMN_T c_sqm_cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM_DETAIL_T c_sqm_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM_CMN_T c_sqm2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM_DETAIL_T c_sqm2k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM2_CMN_T sqm_cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM2_DETAIL_T sqm_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM2_CMN_T sqm2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM2_DETAIL_T sqm2k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_DE_T tmp_sr2k_de_param; /* for super resolution menu */
	__attribute__((unused)) LX_PE_SHP_DE4_T tmp_ede_param;	/* for super resolution menu   */
	__attribute__((unused)) int fnum, i;
	__attribute__((unused)) UINT8 *pd;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode =  0x1;//_g_vpq_hwrap_shp_platform_db_enable;
	/* 1. set post sharpness */
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (pChip)
	#else
	if (pChip)
	#endif
	{
		/*vsd shp*/
		misc_param.win_id = cmn_param.win_id = ee_param.win_id  = win_id;
		/*sqm*/
		c_sqm_cmn_param.win_id = c_sqm_dtl_param.win_id = win_id;
		sqm_cmn_param.win_id = sqm_dtl_param.win_id = win_id;
		c_sqm_cmn_param.oper = c_sqm_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm_cmn_param.size = sizeof(LX_PE_SHP_RE_SQM2_CMN_T);
		c_sqm_dtl_param.size = sizeof(LX_PE_SHP_RE_SQM2_DETAIL_T);
		c_sqm_cmn_param.data = (UINT32 *)&sqm_cmn_param;
		c_sqm_dtl_param.data = (UINT32 *)&sqm_dtl_param;
		memcpy(&(cmn_param.shp_ui_main_vsd), \
			&(pChip->shp_ui_main_vsd), sizeof(pChip->shp_ui_main_vsd));
		memcpy(&(cmn_param.shp_face_obj_vsd), \
			&(pChip->shp_face_obj_vsd), sizeof(pChip->shp_face_obj_vsd));
		memcpy(&(misc_param.shp_djg_vsd), \
			&(pChip->shp_djg_vsd), sizeof(pChip->shp_djg_vsd));
		memcpy(&(misc_param.shp_cmn_vsd), \
			&(pChip->shp_cmn_vsd), sizeof(pChip->shp_cmn_vsd));
		memcpy(&(misc_param.shp_map_cmn_vsd), \
			&(pChip->shp_map_cmn_vsd), sizeof(pChip->shp_map_cmn_vsd));
		memcpy(&(misc_param.shp_balance_vsd), \
			&(pChip->shp_balance_vsd), sizeof(pChip->shp_balance_vsd));
		memcpy(&(misc_param.shp_ti_cmn_vsd), \
			&(pChip->shp_ti_cmn_vsd), sizeof(pChip->shp_ti_cmn_vsd));
		memcpy(&(misc_param.shp_chroma_vsd), \
			&(pChip->shp_chroma_vsd), sizeof(pChip->shp_chroma_vsd));
		//memcpy(&(ee_param.shp_ee_vsd),&(pChip->shp_ee_vsd), sizeof(pChip->shp_ee_vsd));
		pd = pChip->shp_ee_vsd;
		PE_PRINT_SHP("before sr weight sr-ui:%d,\n"\
			"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_vsd)/sizeof(UINT8); i++)
		{
			ee_param.shp_ee_vsd[i] = (UINT8)((UINT32)pChip->shp_ee_vsd[i] * fnum / 1000);
		}
		pd = ee_param.shp_ee_vsd;
		PE_PRINT_SHP("after sr weight sr-ui:%d,\n"\
			"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		
		/*sqm*/
		sqm_cmn_param.shp_sqm____val = cmn_val;
		sqm_dtl_param.shp_sqm_____val = 0x0;
		memcpy(&(sqm_cmn_param.shp_ui_sqm_vsd), \
		&(pChip->shp_ui_sqm_vsd), sizeof(pChip->shp_ui_sqm_vsd));
		memcpy(&(sqm_dtl_param.shp_sqm_cmn_vsd), \
		&(pChip->shp_sqm_cmn_vsd), sizeof(pChip->shp_sqm_cmn_vsd));

		ret = KWRAP_PE_SetRenCmnParam((void *)&cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetRenCmnParam(): error %d\n", ret);
		ret = KWRAP_PE_SetRenMiscParam((void *)&misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetRenMiscParam(): error %d\n", ret);
		ret = KWRAP_PE_SetEdgeEnhanceParam((void *)&ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetEdgeEnhanceParam(): error %d\n", ret);
		ret = KWRAP_PE_SetRenSqmCmnParam((void *)&c_sqm_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetRenSqmCmnParam(): error %d\n", ret);
		ret = KWRAP_PE_SetRenSqmDetailParam((void *)&c_sqm_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetRenSqmDetailParam(): error %d\n", ret);
	}
	else
	{
		tmp_ede_param.win_id  = win_id;
		/* 1. set post sharpness */
		{
			kwrap_ctrl.wid = win_id;
			kwrap_ctrl.data = cmn_val;
			ret = KWRAP_PE_SetRenCmnCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetRenCmnCtrl(): error %d\n", ret);

			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = PE_KWRAP_SHP_FMT_HD;
			//ret = KWRAP_PE_SetRenMiscCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenMiscCtrl() \n", __F__, __L__);

			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenHorCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenHorCtrl() \n", __F__, __L__);
			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenVerCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenVerCtrl() \n", __F__, __L__);
			
			dbtype = LX_PE_PLATFORM_NUM; //easy DB
			kwrap_ctrl.wid = LX_PE_WIN_0;
			kwrap_ctrl.data = (UINT32)cmn_val;
			kwrap_ctrl.st_data = (void *)&dbtype;
			//ret = KWRAP_PE_SetRenSqmCmnCtrl(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenSqmCmnCtrl(): error %d \n", __F__, __L__, ret);

			kwrap_ctrl.wid = win_id;
			kwrap_ctrl.data = cmn_val;
			kwrap_ctrl.st_data = (void*)&tmp_ede_param;
			ret = KWRAP_PE_GetDetailEnhanceDefaultSettings(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetDetailEnhanceDefaultSettings(): error %d\n", ret);
			tmp_ede_param.win_id = win_id;
			pd = tmp_ede_param.shp_de_vsd;
			PE_PRINT_SHP("before sr weight sr-ui:%d,\n"\
				"shp_ee_vsd   [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_vsd   [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pUi[1],\
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10],pd[11],pd[12],pd[13]);

			if(pUi[1] == 0)
			{
				fnum = 0;
			}
			else if(pUi[1] == 1)
			{
				fnum = 500;
			}
			else if(pUi[1] == 3)
			{
				fnum = 1300;
			}
			else
			{
				fnum = 1000;
			}

			tmp_ede_param.shp_de_vsd[0] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[1] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[2] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[3] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[4] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[5] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[6] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[7] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[8] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[9] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[10]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[11]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[12]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[13]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);

			ret = KWRAP_PE_SetDetailEnhanceParam((void *)&tmp_ede_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDetailEnhanceParam(): error %d\n", ret);


		}
	}
	/* 2. set pre sharpness */
	if (pChip)
	{
		/*sre shp*/
		/*sqm*/
		c_sqm2k_cmn_param.win_id = c_sqm2k_dtl_param.win_id = win_id;
		sqm2k_cmn_param.win_id = sqm2k_dtl_param.win_id = win_id;
		c_sqm2k_cmn_param.oper = c_sqm2k_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm2k_cmn_param.size = sizeof(LX_PE_SHP_SR2K_SQM2_CMN_T);
		c_sqm2k_dtl_param.size = sizeof(LX_PE_SHP_SR2K_SQM2_DETAIL_T);
		c_sqm2k_cmn_param.data = (UINT32 *)&sqm2k_cmn_param;
		c_sqm2k_dtl_param.data = (UINT32 *)&sqm2k_dtl_param;
		/*2k*/
		sr2k_misc_param.win_id = sr2k_cmn_param.win_id = sr2k_ee_param.win_id = win_id;
		memcpy(&(sr2k_cmn_param.shp_ui_main_2k), \
			&(pChip->shp_ui_main_2k), sizeof(pChip->shp_ui_main_2k));
		memcpy(&(sr2k_cmn_param.shp_dnn_sr_vsd), \
			&(pChip->shp_dnn_sr_vsd), sizeof(pChip->shp_dnn_sr_vsd));
		memcpy(&(sr2k_misc_param.shp_cmn_2k), \
			&(pChip->shp_cmn_2k), sizeof(pChip->shp_cmn_2k));
		memcpy(&(sr2k_misc_param.shp_djg_2k), \
			&(pChip->shp_djg_2k), sizeof(pChip->shp_djg_2k));
		memcpy(&(sr2k_misc_param.shp_map_cmn_2k), \
			&(pChip->shp_map_cmn_2k), sizeof(pChip->shp_map_cmn_2k));
		memcpy(&(sr2k_misc_param.shp_balance_2k), \
			&(pChip->shp_balance_2k), sizeof(pChip->shp_balance_2k));
		memcpy(&(sr2k_misc_param.shp_ti_cmn_2k), \
			&(pChip->shp_ti_cmn_2k), sizeof(pChip->shp_ti_cmn_2k));
		//memcpy(&(sr2k_ee_param.shp_ee_2k),&(pChip->shp_ee_2k), sizeof(pChip->shp_ee_2k));
		pd = pChip->shp_ee_2k;
		PE_PRINT_SHP("before sr weight sr-ui:%d, size:%zu \n"\
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_2k)/sizeof(UINT8); i++)
		{
			sr2k_ee_param.shp_ee_2k[i] = (UINT8)((UINT32)pChip->shp_ee_2k[i] * fnum / 1000);
		}
		pd = sr2k_ee_param.shp_ee_2k;
		PE_PRINT_SHP("after sr weight sr-ui:%d, size:%zu \n"\
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		/*sqm*/
		sqm2k_cmn_param.shp_sqm___val= cmn_val;
		sqm2k_dtl_param.shp_sqm____val = 0x0;
		memcpy(&(sqm2k_cmn_param.shp_ui_sqm_2k), \
		&(pChip->shp_ui_sqm_2k), sizeof(pChip->shp_ui_sqm_2k));
		memcpy(&(sqm2k_dtl_param.shp_sqm_cmn_2k), \
		&(pChip->shp_sqm_cmn_2k), sizeof(pChip->shp_sqm_cmn_2k));

		ret = KWRAP_PE_SetSre2KRenCmnParam((void *)&sr2k_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KRenCmnParam(): error %d\n", ret);
		ret = KWRAP_PE_SetSre2KRenMiscParam((void *)&sr2k_misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KRenMiscParam(): error %d\n", ret);
		ret = KWRAP_PE_SetSre2KEdgeEnhanceParam((void *)&sr2k_ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KDetailEnhanceParam(): error %d\n", ret);
		ret = KWRAP_PE_SetSre2KSqmCmnParam((void *)&c_sqm2k_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KSqmCmnParam(): error %d\n", ret);
		ret = KWRAP_PE_SetSre2KRenSqmDetailParam((void *)&c_sqm2k_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KRenSqmDetailParam(): error %d\n", ret);
		
	}
	else
	{
		tmp_sr2k_de_param.win_id  = win_id;
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		ret = KWRAP_PE_SetSre2KRenCmnCtrl((void *)&kwrap_ctrl);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KRenCmnCtrl(): error %d\n", ret);
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		kwrap_ctrl.st_data = (void*)&tmp_sr2k_de_param;
		
		kwrap_ctrl.wid = win_id;
		kwrap_ctrl.data = cmn_val;
		ret = KWRAP_PE_SetSre2KSqmCmnCtrl((void *)&kwrap_ctrl);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KSqmCmnCtrl(): error %d\n", ret);

		ret = KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(&kwrap_ctrl);
		tmp_sr2k_de_param.win_id = win_id;
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(): error %d\n", ret);

		if(pUi[1] == 0)
		{
			fnum = 0;
		}
		else if(pUi[1] == 1)
		{
			fnum = 500;
		}
		else if(pUi[1] == 3)
		{
			fnum = 1300;
		}
		else
		{
			fnum = 1000;
		}

		tmp_sr2k_de_param.shp_de_2k[0] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[0] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[1] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[1] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[2] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[2] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[3] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[3] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[4] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[4] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[5] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[5] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[6] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[6] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[7] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[7] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[8] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[8] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[9] = (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[9] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[10]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[10] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[11]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[11] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[12]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[12] * fnum / 1000);
		tmp_sr2k_de_param.shp_de_2k[13]= (UINT8)((UINT32)tmp_sr2k_de_param.shp_de_2k[13] * fnum / 1000);

		ret = KWRAP_PE_SetSre2KDetailEnhanceParam((void *)&tmp_sr2k_de_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetSre2KDetailEnhanceParam(): error %d\n", ret);
	}
	return ret;
}
static int vpq_hwrap_setsharpness_f22(vpq_hwrap_shp_t *pShpData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_o22_t *pChip = (vpq_hwrap_chip_shp_o22_t *)pShpData->pst_chip_data;
	__attribute__((unused)) LX_PE_SHP1_ALL_CMN_T shp_param_f22;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) int fnum;
	__attribute__((unused)) int i;
	__attribute__((unused)) UINT8 *pd;
	__attribute__((unused)) UINT32 *pd32;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode = _g_vpq_hwrap_shp_platform_db_enable;
	/* 1. set post sharpness */
	if (pChip)
	{
		shp_param_f22.win_id = win_id;
		/*vsd shp*/
  		memcpy(&(shp_param_f22.shp_ui_main_vsd), \
			&(pChip->shp_ui_main_vsd), sizeof(pChip->shp_ui_main_vsd));
		memcpy(&(shp_param_f22.shp_face_obj_vsd), \
			&(pChip->shp_face_obj_vsd), sizeof(pChip->shp_face_obj_vsd));
		memcpy(&(shp_param_f22.shp_djg_vsd), \
			&(pChip->shp_djg_vsd), sizeof(pChip->shp_djg_vsd));
		memcpy(&(shp_param_f22.shp_cmn_vsd), \
			&(pChip->shp_cmn_vsd), sizeof(pChip->shp_cmn_vsd));
		memcpy(&(shp_param_f22.shp_map_cmn_vsd), \
			&(pChip->shp_map_cmn_vsd), sizeof(pChip->shp_map_cmn_vsd));
		memcpy(&(shp_param_f22.shp_balance_vsd), \
			&(pChip->shp_balance_vsd), sizeof(pChip->shp_balance_vsd));
		memcpy(&(shp_param_f22.shp_ti_cmn_vsd), \
			&(pChip->shp_ti_cmn_vsd), sizeof(pChip->shp_ti_cmn_vsd));
		memcpy(&(shp_param_f22.shp_chroma_vsd), \
			&(pChip->shp_chroma_vsd), sizeof(pChip->shp_chroma_vsd));
		memcpy(&(shp_param_f22.shp_dnn_sr_vsd), \
			&(pChip->shp_dnn_sr_vsd), sizeof(pChip->shp_dnn_sr_vsd));
		memcpy(&(shp_param_f22.shp_face_obj_vsd), \
			&(pChip->shp_face_obj_vsd), sizeof(pChip->shp_face_obj_vsd));
		//memcpy(&(ee_param.shp_ee_vsd),&(pChip->shp_ee_vsd), sizeof(pChip->shp_ee_vsd));

		pd = shp_param_f22.shp_ui_main_vsd;
		PE_PRINT_SHP("set : shp_ui_main_vsd\n"
		"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd = shp_param_f22.shp_face_obj_vsd;
		PE_PRINT_SHP("set : shp_face_obj_vsd\n"
		"shp_face_obj_vsd	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd	 [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_face_obj_vsd	 [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], \
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = shp_param_f22.shp_cmn_vsd;
		PE_PRINT_SHP("set : shp_cmn_vsd\n"
		"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = shp_param_f22.shp_djg_vsd;
		PE_PRINT_SHP("set : shp_djg_vsd\n"
		"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = shp_param_f22.shp_map_cmn_vsd;
		PE_PRINT_SHP("set : shp_map_cmn_vsd\n"
		"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = shp_param_f22.shp_balance_vsd;
		PE_PRINT_SHP("set : shp_balance_vsd\n"
		"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
		pd = shp_param_f22.shp_ti_cmn_vsd;
		PE_PRINT_SHP("set : shp_ti_cmn_vsd\n"
		"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = shp_param_f22.shp_chroma_vsd;
		PE_PRINT_SHP("set : shp_chroma_vsd\n"
		"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4]);
		pd = pChip->shp_ee_vsd;
		PE_PRINT_SHP("[F22] before sr weight sr-ui:%d,\n"\
			"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_vsd)/sizeof(UINT8); i++)
		{
			shp_param_f22.shp_ee_vsd[i] = (UINT8)((UINT32)pChip->shp_ee_vsd[i] * fnum / 1000);
		}
		pd = shp_param_f22.shp_ee_vsd;
		PE_PRINT_SHP("[F22] after sr weight sr-ui:%d,\n"\
			"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		
		/*sqm*/
		shp_param_f22.shp_val = cmn_val;
		memcpy(&(shp_param_f22.shp_ui_sqm_vsd), \
		&(pChip->shp_ui_sqm_vsd), sizeof(pChip->shp_ui_sqm_vsd));
		memcpy(&(shp_param_f22.shp_sqm_cmn_vsd), \
		&(pChip->shp_sqm_cmn_vsd), sizeof(pChip->shp_sqm_cmn_vsd));
		pd32 = shp_param_f22.shp_ui_sqm_vsd;
		PE_PRINT_SHP("set : shp_ui_sqm_vsd\n"\
		"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39]);
		pd32 = shp_param_f22.shp_sqm_cmn_vsd;
		PE_PRINT_SHP("set : shp_sqm_cmn_vsd\n"\
		"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[70]0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39],\
		pd32[40],pd32[41],	pd32[42],  pd32[43], pd32[34],  pd32[45],  pd32[46],	pd32[47], pd32[48],  pd32[49],\
		pd32[50],pd32[51],	pd32[52],  pd32[53], pd32[34],  pd32[55],  pd32[56],	pd32[57], pd32[58],  pd32[59],\
		pd32[60],pd32[61],	pd32[62],  pd32[63], pd32[34],  pd32[65],  pd32[66],	pd32[67], pd32[68],  pd32[69],\
		pd32[70]);

		ret = PE_SHP_SetReAllCtrl((void *)&shp_param_f22);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReAllCtrl(): error %d\n", ret);

	}
	return ret;
}

static int vpq_hwrap_setsharpness_f20(vpq_hwrap_shp_t *pShpData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_o20_t *pChip = (vpq_hwrap_chip_shp_o20_t *)pShpData->pst_chip_data;
	__attribute__((unused)) LX_PE_SHP_ALL_CMN_T shp_param_f20;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) int fnum;
	__attribute__((unused)) int i;
	__attribute__((unused)) UINT8 *pd;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode =  0x1;//_g_vpq_hwrap_shp_platform_db_enable;
	/* 1. set post sharpness */
	if (pChip)
	{
		shp_param_f20.win_id = win_id;
		/*vsd shp*/
  		memcpy(&(shp_param_f20.shp_ui_main_vsd), \
			&(pChip->shp_ui_main_vsd), sizeof(pChip->shp_ui_main_vsd));
		memcpy(&(shp_param_f20.shp_face_obj_vsd), \
			&(pChip->shp_face_obj_vsd), sizeof(pChip->shp_face_obj_vsd));
		memcpy(&(shp_param_f20.shp_djg_vsd), \
			&(pChip->shp_djg_vsd), sizeof(pChip->shp_djg_vsd));
		memcpy(&(shp_param_f20.shp_cmn_vsd), \
			&(pChip->shp_cmn_vsd), sizeof(pChip->shp_cmn_vsd));
		memcpy(&(shp_param_f20.shp_map_cmn_vsd), \
			&(pChip->shp_map_cmn_vsd), sizeof(pChip->shp_map_cmn_vsd));
		memcpy(&(shp_param_f20.shp_balance_vsd), \
			&(pChip->shp_balance_vsd), sizeof(pChip->shp_balance_vsd));
		memcpy(&(shp_param_f20.shp_ti_cmn_vsd), \
			&(pChip->shp_ti_cmn_vsd), sizeof(pChip->shp_ti_cmn_vsd));
		memcpy(&(shp_param_f20.shp_chroma_vsd), \
			&(pChip->shp_chroma_vsd), sizeof(pChip->shp_chroma_vsd));
		memcpy(&(shp_param_f20.shp_dnn_sr_vsd), \
			&(pChip->shp_dnn_sr_vsd), sizeof(pChip->shp_dnn_sr_vsd));
		//memcpy(&(ee_param.shp_ee_vsd),&(pChip->shp_ee_vsd), sizeof(pChip->shp_ee_vsd));
		pd = pChip->shp_ee_vsd;
		PE_PRINT_SHP("[F20] before sr weight sr-ui:%d,\n"\
			"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_vsd)/sizeof(UINT8); i++)
		{
			shp_param_f20.shp_ee_vsd[i] = (UINT8)((UINT32)pChip->shp_ee_vsd[i] * fnum / 1000);
		}
		pd = shp_param_f20.shp_ee_vsd;
		PE_PRINT_SHP("[F20] after sr weight sr-ui:%d,\n"\
			"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		
		/*sqm*/
		shp_param_f20.shp_val = cmn_val;
		memcpy(&(shp_param_f20.shp_ui_sqm_vsd), \
		&(pChip->shp_ui_sqm_vsd), sizeof(pChip->shp_ui_sqm_vsd));
		memcpy(&(shp_param_f20.shp_sqm_cmn_vsd), \
		&(pChip->shp_sqm_cmn_vsd), sizeof(pChip->shp_sqm_cmn_vsd));
		ret = PE_SHP_SetReAllCtrl((void *)&shp_param_f20);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReAllCtrl(): error %d\n", ret);

	}
	return ret;
}
static int vpq_hwrap_setsharpness_e60(vpq_hwrap_shp_t *pShpData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID win_id;
	__attribute__((unused)) vpq_hwrap_chip_shp_e60_t *pChip = (vpq_hwrap_chip_shp_e60_t *)pShpData->pst_chip_data;
	__attribute__((unused)) unsigned short *pUi = pShpData->ui_value;
	__attribute__((unused)) UINT32 db_mode = 1;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) UINT32 cmn_val = 0, hor_val = 0, ver_val = 0;
	__attribute__((unused)) LX_PE_SHP_RE1_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE1_MISC_T misc_param;
	__attribute__((unused)) LX_PE_SHP_EE1_T ee_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE2_CMN_T sr2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_RE1_MISC_T sr2k_misc_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_EE1_T sr2k_ee_param;
	__attribute__((unused)) LX_PE_SHP_SR4K_RE1_CMN_T sr4k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR4K_RE1_MISC_T sr4k_misc_param;
	__attribute__((unused)) LX_PE_SHP_SR4K_EE1_T sr4k_ee_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM_CMN_T c_sqm_cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM_DETAIL_T c_sqm_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM_CMN_T c_sqm2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM_DETAIL_T c_sqm2k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM2_CMN_T sqm_cmn_param;
	__attribute__((unused)) LX_PE_SHP_RE_SQM3_DETAIL_T sqm_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM2_CMN_T sqm2k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR2K_SQM2_DETAIL_T sqm2k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_SR4K_SQM1_CMN_T sqm4k_cmn_param;
	__attribute__((unused)) LX_PE_SHP_SR4K_SQM1_DETAIL_T sqm4k_dtl_param;
	__attribute__((unused)) LX_PE_SHP_DE4_T tmp_ede_param;	/* for super resolution menu   */
	__attribute__((unused)) int fnum;
	__attribute__((unused)) int i;
	__attribute__((unused)) UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	__attribute__((unused)) UINT32 *pd32;

	win_id = wId;
	ver_val = hor_val = cmn_val = (UINT32)pUi[0];
	db_mode = 0x1;//_g_vpq_hwrap_shp_platform_db_enable;
	/* 1. set post sharpness */
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (pChip)
	#else
	if (pChip)
	#endif
	{
		/*************vsd***********************/
		misc_param.win_id = cmn_param.win_id = ee_param.win_id  = win_id;
		/*sqm*/
		c_sqm_cmn_param.win_id = c_sqm_dtl_param.win_id = win_id;
		sqm_cmn_param.win_id = sqm_dtl_param.win_id = win_id;
		c_sqm_cmn_param.oper = c_sqm_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm_cmn_param.size = sizeof(LX_PE_SHP_RE_SQM2_CMN_T);
		c_sqm_dtl_param.size = sizeof(LX_PE_SHP_RE_SQM2_DETAIL_T);
		c_sqm_cmn_param.data = (UINT32 *)&sqm_cmn_param;
		c_sqm_dtl_param.data = (UINT32 *)&sqm_dtl_param;
		memcpy(&(cmn_param.shp_ui_main_vsd), \
			&(pChip->shp_ui_main_vsd), sizeof(pChip->shp_ui_main_vsd));
		memcpy(&(cmn_param.shp_face_obj_vsd), \
			&(pChip->shp_face_obj_vsd), sizeof(pChip->shp_face_obj_vsd));
		memcpy(&(misc_param.shp_djg_vsd), \
			&(pChip->shp_djg_vsd), sizeof(pChip->shp_djg_vsd));
		memcpy(&(misc_param.shp_cmn_vsd), \
			&(pChip->shp_cmn_vsd), sizeof(pChip->shp_cmn_vsd));
		memcpy(&(misc_param.shp_map_cmn_vsd), \
			&(pChip->shp_map_cmn_vsd), sizeof(pChip->shp_map_cmn_vsd));
		memcpy(&(misc_param.shp_balance_vsd), \
			&(pChip->shp_balance_vsd), sizeof(pChip->shp_balance_vsd));
		memcpy(&(misc_param.shp_ti_cmn_vsd), \
			&(pChip->shp_ti_cmn_vsd), sizeof(pChip->shp_ti_cmn_vsd));
		memcpy(&(misc_param.shp_chroma_vsd), \
			&(pChip->shp_chroma_vsd), sizeof(pChip->shp_chroma_vsd));
		//memcpy(&(ee_param.shp_ee_vsd),&(pChip->shp_ee_vsd), sizeof(pChip->shp_ee_vsd));
		pd = pChip->shp_ui_main_vsd;
		PE_PRINT_SHP("shp_ui_main_vsd\n"
		"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd = pChip->shp_face_obj_vsd;
		PE_PRINT_SHP("shp_face_obj_vsd\n"
		"shp_face_obj_vsd	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = pChip->shp_ee_vsd;
		PE_PRINT_SHP("before sr weight sr-ui:%d,\n"\
			"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);

		pd = pChip->shp_cmn_vsd;
		PE_PRINT_SHP("shp_cmn_vsd\n"
		"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24]);
		pd = pChip->shp_djg_vsd;
		PE_PRINT_SHP("shp_djg_vsd\n"
		"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = pChip->shp_map_cmn_vsd;
		PE_PRINT_SHP("shp_map_cmn_vsd\n"
		"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = pChip->shp_balance_vsd;
		PE_PRINT_SHP("shp_balance_vsd\n"
		"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
		pd = pChip->shp_ti_cmn_vsd;
		PE_PRINT_SHP("shp_ti_cmn_vsd\n"
		"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		pd = pChip->shp_chroma_vsd;
		PE_PRINT_SHP("shp_chroma_vsd\n"
		"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_vsd)/sizeof(UINT8); i++)
		{
			ee_param.shp_ee_vsd[i] = (UINT8)((UINT32)pChip->shp_ee_vsd[i] * fnum / 1000);
		}
		pd = ee_param.shp_ee_vsd;
		PE_PRINT_SHP("after sr weight sr-ui:%d,\n"\
			"shp_ee_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);

		/*sqm*/
		sqm_cmn_param.shp_sqm____val = cmn_val;
		sqm_dtl_param.shp_sqm_____val = 0x0;
		memcpy(&(sqm_cmn_param.shp_ui_sqm_vsd), \
		&(pChip->shp_ui_sqm_vsd), sizeof(pChip->shp_ui_sqm_vsd));
		memcpy(&(sqm_dtl_param.shp_sqm_cmn_vsd), \
		&(pChip->shp_sqm_cmn_vsd), sizeof(pChip->shp_sqm_cmn_vsd));
		pd32 = pChip->shp_ui_sqm_vsd;
		PE_PRINT_SHP( \
		"shp_ui_sqm_2k\n"\
		"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
		pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
		pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
		pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39]);
		pd32 = pChip->shp_sqm_cmn_vsd;
		PE_PRINT_SHP( \
		"shp_sqm_cmn_vsd:\n"\
		"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
		pd32[0], pd32[1],	pd32[2], pd32[3], pd32[4], pd32[5], pd32[6],  pd32[7],pd32[8], pd32[9], \
		pd32[10],pd32[11],	pd32[12],pd32[13],pd32[14],pd32[15],pd32[16],	pd32[17],pd32[18],pd32[19], \
		pd32[20],pd32[21],	pd32[22],pd32[23],pd32[24],pd32[25],pd32[26],	pd32[27],pd32[28],pd32[29],\
		pd32[30],pd32[31],	pd32[32],pd32[33],pd32[34],pd32[35],pd32[36],	pd32[37],pd32[38],pd32[39],\
		pd32[40],pd32[41],	pd32[42],pd32[43],pd32[44],pd32[45],pd32[46],	pd32[47],pd32[48],pd32[49],\
		pd32[50],pd32[51],	pd32[52],pd32[53],pd32[54],pd32[55],pd32[56],	pd32[57],pd32[58],pd32[59],\
		pd32[60],pd32[61],	pd32[62],pd32[63],pd32[64],pd32[65],pd32[66]);

		ret = PE_SHP_SetReCmnCtrl((void *)&cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetReMiscCtrl((void *)&misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetEdgeEnhanceCtrl((void *)&ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSqmCmnCtrl((void *)&c_sqm_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSqmDetailCtrl((void *)&c_sqm_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReCmnCtrl(): error %d\n", ret);
	}
	else
	{
		tmp_ede_param.win_id  = win_id;
		/* 1. set post sharpness */
		{
			{ // PE_SHP_SetReEasyCmnCtrl
				LX_PE_SHP_RE_EASY_CMN_T ctrl;
				int in=0;
				int in_tbl[VPQ_HWRAP_SHP_STEP]={0, 10, 25, 30, 50};
				int out_tbl[VPQ_HWRAP_SHP_STEP]={0x0, 0x10, 0x18, 0x20, 0x30};
				int i;

				in = (cmn_val>50)? 50:cmn_val;
				ctrl.win_id = win_id;

				for (i=0; i<20; i++)
				{
					ctrl.shp_ui_vsd[i] = vpq_hwrap_getoutvalbyinterpol(in, in_tbl, out_tbl, 0, VPQ_HWRAP_SHP_STEP);
				}

				ret = PE_SHP_SetReEasyCmnCtrl((void*)&ctrl);
				VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetReEasyCmnCtrl(): error %d\n", ret);
			}

			//kwrap_ctrl.wid = LX_PE_WIN_0;
			//kwrap_ctrl.data = PE_KWRAP_SHP_FMT_HD;
			//ret = KWRAP_PE_SetRenMiscCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenMiscCtrl() \n", __F__, __L__);

			//kwrap_ctrl.wid = LX_PE_WIN_0;
			//kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenHorCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenHorCtrl() \n", __F__, __L__);
			//kwrap_ctrl.wid = LX_PE_WIN_0;
			//kwrap_ctrl.data = cmn_val;
			//ret = KWRAP_PE_SetRenVerCtrl((void *)&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenVerCtrl() \n", __F__, __L__);
			
			dbtype = LX_PE_PLATFORM_NUM; //easy DB
			//kwrap_ctrl.wid = LX_PE_WIN_0;
			//kwrap_ctrl.data = (UINT32)cmn_val;
			//kwrap_ctrl.st_data = (void *)&dbtype;
			//ret = KWRAP_PE_SetRenSqmCmnCtrl(&kwrap_ctrl);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, \
				"Error.[%s.%d] KWRAP_PE_SetRenSqmCmnCtrl(): error %d \n", __F__, __L__, ret);

			{ //KWRAP_PE_GetDetailEnhanceDefaultSettings
				int in=0;
				int in_tbl[VPQ_HWRAP_SHP_STEP]={0, 10, 25, 30, 50};
				int out_tbl[VPQ_HWRAP_SHP_STEP]={0x0, 0x10, 0x1C, 0x20, 0x28};
				int i;

				in = (cmn_val>50)? 50: cmn_val;

				for (i=0; i<14; i++)
				{
					tmp_ede_param.shp_de_vsd[i] = vpq_hwrap_getoutvalbyinterpol(in, in_tbl, out_tbl, 0, VPQ_HWRAP_SHP_STEP);
				}
		
				//VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_GetDetailEnhanceDefaultSettings(): error %d\n", ret);
			}
			tmp_ede_param.win_id = win_id;
			pd = tmp_ede_param.shp_de_vsd;
			PE_PRINT_SHP("before sr weight sr-ui:%d,\n"\
				"shp_ee_vsd   [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_vsd   [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pUi[1],\
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10],pd[11],pd[12],pd[13]);

			if(pUi[1] == 0)
			{
				fnum = 0;
			}
			else if(pUi[1] == 1)
			{
				fnum = 500;
			}
			else if(pUi[1] == 3)
			{
				fnum = 1300;
			}
			else
			{
				fnum = 1000;
			}

			tmp_ede_param.shp_de_vsd[0] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[1] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[2] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[3] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[4] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[5] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[6] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[7] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[8] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[9] = (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[10]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[2] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[11]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[3] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[12]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[0] * fnum / 1000);
			tmp_ede_param.shp_de_vsd[13]= (UINT8)((UINT32)tmp_ede_param.shp_de_vsd[1] * fnum / 1000);

			ret = PE_SHP_SetDetailEnhanceCtrl((void *)&tmp_ede_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetDetailEnhanceCtrl(): error %d\n", ret);

		}
	}
	/* 2. set pre sharpness */
	if (pChip && db_mode)
	{
		/*sre shp*/
		/*sqm*/
		c_sqm2k_cmn_param.win_id = c_sqm2k_dtl_param.win_id = win_id;
		sqm2k_cmn_param.win_id = sqm2k_dtl_param.win_id = win_id;
		c_sqm2k_cmn_param.oper = c_sqm2k_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm2k_cmn_param.size = sizeof(LX_PE_SHP_SR2K_SQM2_CMN_T);
		c_sqm2k_dtl_param.size = sizeof(LX_PE_SHP_SR2K_SQM2_DETAIL_T);
		c_sqm2k_cmn_param.data = (UINT32 *)&sqm2k_cmn_param;
		c_sqm2k_dtl_param.data = (UINT32 *)&sqm2k_dtl_param;
		/*************2k***********************/
		sr2k_misc_param.win_id = sr2k_cmn_param.win_id = sr2k_ee_param.win_id = win_id;
		memcpy(&(sr2k_cmn_param.shp_ui_main_2k), \
			&(pChip->shp_ui_main_2k), sizeof(pChip->shp_ui_main_2k));
		memcpy(&(sr2k_misc_param.shp_cmn_2k), \
			&(pChip->shp_cmn_2k), sizeof(pChip->shp_cmn_2k));
		memcpy(&(sr2k_misc_param.shp_djg_2k), \
			&(pChip->shp_djg_2k), sizeof(pChip->shp_djg_2k));
		memcpy(&(sr2k_misc_param.shp_map_cmn_2k), \
			&(pChip->shp_map_cmn_2k), sizeof(pChip->shp_map_cmn_2k));
		memcpy(&(sr2k_misc_param.shp_balance_2k), \
			&(pChip->shp_balance_2k), sizeof(pChip->shp_balance_2k));
		memcpy(&(sr2k_misc_param.shp_ti_cmn_2k), \
			&(pChip->shp_ti_cmn_2k), sizeof(pChip->shp_ti_cmn_2k));
		//memcpy(&(sr2k_ee_param.shp_ee_2k),&(pChip->shp_ee_2k), sizeof(pChip->shp_ee_2k));
		pd = pChip->shp_ui_main_2k;
		PE_PRINT_SHP("shp_ui_main_2k\n"
		"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_2k    [10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd = pChip->shp_cmn_2k;
		PE_PRINT_SHP("shp_cmn_2k\n"
		"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);

		pd = pChip->shp_djg_2k;
		PE_PRINT_SHP("shp_djg_2k\n"
		"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		
		pd = pChip->shp_map_cmn_2k;
		PE_PRINT_SHP("shp_map_cmn_2k\n"
		"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_2k    [10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);

		pd = pChip->shp_balance_2k;
		PE_PRINT_SHP("shp_balance_2k\n"
		"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

		pd = pChip->shp_ti_cmn_2k;
		PE_PRINT_SHP("shp_ti_cmn_2k\n"
		"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);

		pd = pChip->shp_ee_2k;
		PE_PRINT_SHP("before sr weight sr-ui:%d, size:%zu \n"\
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_2k)/sizeof(UINT8); i++)
		{
			sr2k_ee_param.shp_ee_2k[i] = (UINT8)((UINT32)pChip->shp_ee_2k[i] * fnum / 1000);
		}
		pd = sr2k_ee_param.shp_ee_2k;
		PE_PRINT_SHP("after sr weight sr-ui:%d, size:%zu \n"\
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],sizeof(pChip->shp_ee_2k)/sizeof(UINT8),\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		/*sqm*/
		sqm2k_cmn_param.shp_sqm___val= cmn_val;
		sqm2k_dtl_param.shp_sqm____val = 0x0;
		memcpy(&(sqm2k_cmn_param.shp_ui_sqm_2k), \
		&(pChip->shp_ui_sqm_2k), sizeof(pChip->shp_ui_sqm_2k));
		memcpy(&(sqm2k_dtl_param.shp_sqm_cmn_2k), \
		&(pChip->shp_sqm_cmn_2k), sizeof(pChip->shp_sqm_cmn_2k));
		pd32 = pChip->shp_ui_sqm_2k;
		PE_PRINT_SHP("shp_ui_sqm_2k\n"
		"shp_ui_sqm_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_2k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19],\
		pd32[20], pd32[21], pd32[22], pd32[23], pd32[24], pd32[25], pd32[26], pd32[27], pd32[28], pd32[29],\
		pd32[30], pd32[31], pd32[32], pd32[33], pd32[34], pd32[35], pd32[36], pd32[37], pd32[38]);

		pd32 = pChip->shp_sqm_cmn_2k;
		PE_PRINT_SHP( \
		"shp_sqm_cmn_2k:\n"\
		"shp_sqm_cmn_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_2k[40]0x%08X,0x%08X,0x%08X,\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],  pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17],  pd32[18],	pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23], pd32[24],	pd32[25],  pd32[26],  pd32[27],  pd32[28],	pd32[29],\
		pd32[30],  pd32[31],  pd32[32],  pd32[33], pd32[34],	pd32[35],  pd32[36],  pd32[37],  pd32[38],	pd32[39],\
		pd32[40],  pd32[41],  pd32[42]);

		ret = PE_SHP_SetSre2KReCmnCtrl((void *)&sr2k_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSre2KReMiscCtrl((void *)&sr2k_misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KReMiscCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSre2KEdgeEnhanceCtrl((void *)&sr2k_ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KEdgeEnhanceCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSre2KSqmCmnCtrl((void *)&c_sqm2k_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KSqmCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSre2KSqmDetailCtrl((void *)&c_sqm2k_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSre2KSqmDetailCtrl(): error %d\n", ret);

		/*************4k***********************/
		sr4k_misc_param.win_id = sr4k_cmn_param.win_id = sr4k_ee_param.win_id = win_id;
		memcpy(&(sr4k_cmn_param.shp_ui_main_4k), \
			&(pChip->shp_ui_main_4k), sizeof(pChip->shp_ui_main_4k));
		memcpy(&(sr4k_cmn_param.shp_dnn_sr_4k), \
			&(pChip->shp_dnn_sr_4k), sizeof(pChip->shp_dnn_sr_4k));
		memcpy(&(sr4k_misc_param.shp_cmn_4k), \
			&(pChip->shp_cmn_4k), sizeof(pChip->shp_cmn_4k));
		memcpy(&(sr4k_misc_param.shp_djg_4k), \
			&(pChip->shp_djg_4k), sizeof(pChip->shp_djg_4k));
		memcpy(&(sr4k_misc_param.shp_map_cmn_4k), \
			&(pChip->shp_map_cmn_4k), sizeof(pChip->shp_map_cmn_4k));
		memcpy(&(sr4k_misc_param.shp_balance_4k), \
			&(pChip->shp_balance_4k), sizeof(pChip->shp_balance_4k));
		memcpy(&(sr4k_misc_param.shp_ti_cmn_4k), \
			&(pChip->shp_ti_cmn_4k), sizeof(pChip->shp_ti_cmn_4k));
		//memcpy(&(sr4k_ee_param.shp_ee_4k),&(pChip->shp_ee_4k), sizeof(pChip->shp_ee_4k));

		pd = pChip->shp_ui_main_4k;
		PE_PRINT_SHP("shp_ui_main_4k\n"
		"shp_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_4k    [10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);
		pd16 = pChip->shp_dnn_sr_4k;
		PE_PRINT_SHP("shp_dnn_sr_4k\n"
		"shp_dnn_sr_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8]);
		pd = pChip->shp_ee_4k;
		PE_PRINT_SHP("before sr weight sr-ui:%d,\n"\
			"shp_ee_4k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);

		pd = pChip->shp_cmn_4k;
		PE_PRINT_SHP("shp_cmn_4k\n"
		"shp_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);
		pd = pChip->shp_djg_4k;

		PE_PRINT_SHP("shp_djg_4k\n"
		"shp_djg_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

		pd = pChip->shp_map_cmn_4k;
		PE_PRINT_SHP("hp_map_cmn_4k\n"
		"shp_map_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_map_cmn_4k    [10]0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11]);

		pd = pChip->shp_balance_4k;
		PE_PRINT_SHP("shp_balance_4k\n"
		"shp_balance_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_balance_4k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

		pd = pChip->shp_ti_cmn_4k;
		PE_PRINT_SHP("shp_ti_cmn_4k\n"
		"shp_ti_cmn_4k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ti_cmn_4k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		if(pUi[1] == 0)//off
		{
			fnum = 500;
		}
		else if(pUi[1] == 1)//low
		{
			fnum = 1000;
		}
		else if(pUi[1] == 3)//high
		{
			fnum = 1500;
		}
		else 				//mideum, auto
		{
			fnum = 1000;
		}
		for(i=0; i < sizeof(pChip->shp_ee_4k)/sizeof(UINT8); i++)
		{
			sr4k_ee_param.shp_ee_4k[i] = (UINT8)((UINT32)pChip->shp_ee_4k[i] * fnum / 1000);
		}
		pd = sr4k_ee_param.shp_ee_4k;
		PE_PRINT_SHP("after sr weight sr-ui:%d\n"\
			"shp_ee_4k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		 	pUi[1],\
		 	pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		 	pd[10],pd[11],pd[12],pd[13],pd[14],pd[15],pd[16],pd[17],pd[18],pd[19],\
		 	pd[20],pd[21],pd[22],pd[23],pd[24],pd[25],pd[26],pd[27]);
		/*sqm*/
		sqm4k_cmn_param.win_id = sqm4k_dtl_param.win_id = win_id;
		sqm4k_cmn_param.shp_sqm___val= cmn_val;
		sqm4k_dtl_param.shp_sqm____val = 0x0;
		memcpy(&(sqm4k_cmn_param.shp_ui_sqm_4k), \
		&(pChip->shp_ui_sqm_4k), sizeof(pChip->shp_ui_sqm_4k));
		memcpy(&(sqm4k_dtl_param.shp_sqm_cmn_4k), \
		&(pChip->shp_sqm_cmn_4k), sizeof(pChip->shp_sqm_cmn_4k));
		pd32 = pChip->shp_ui_sqm_4k;
		PE_PRINT_SHP("shp_ui_sqm_4k\n"
		"shp_ui_sqm_4k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_4k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_4k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_sqm_4k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19],\
		pd32[20], pd32[21], pd32[22], pd32[23], pd32[24], pd32[25], pd32[26], pd32[27], pd32[28], pd32[29],\
		pd32[30], pd32[31], pd32[32], pd32[33], pd32[34], pd32[35], pd32[36], pd32[37], pd32[38]);
		pd32 = pChip->shp_sqm_cmn_4k;
		PE_PRINT_SHP( \
		"shp_sqm_cmn_4k\n"\
		"shp_sqm_cmn_4k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_4k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_4k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_4k[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"shp_sqm_cmn_4k[40]0x%08X,0x%08X,0x%08X,\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],  pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17],  pd32[18],	pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23], pd32[24],	pd32[25],  pd32[26],  pd32[27],  pd32[28],	pd32[29],\
		pd32[30],  pd32[31],  pd32[32],  pd32[33], pd32[34],	pd32[35],  pd32[36],  pd32[37],  pd32[38],	pd32[39],\
		pd32[40],  pd32[41],  pd32[42]);

		ret = PE_SHP_SetSreReCmnCtrl((void *)&sr4k_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreReCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSreReMiscCtrl((void *)&sr4k_misc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreReMiscCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSreEdgeEnhanceCtrl((void *)&sr4k_ee_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreEdgeEnhanceCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSreSqmCmnCtrl((void *)&sqm4k_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreSqmCmnCtrl(): error %d\n", ret);
		ret = PE_SHP_SetSreSqmDetailCtrl((void *)&sqm4k_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_SHP_SetSreSqmDetailCtrl(): error %d\n", ret);
		
	}

	return ret;
}

int vpq_hwrap_setnoisereduction(vpq_hwrap_nr_t *pNrData, UINT32 wId, unsigned int ver)
{
	int ret = RET_OK;
	LX_PE_WIN_ID wid;
	vpq_hwrap_info_t *p_info = &_g_vpq_hwrap_info;

	/*for pioneer*/
	//PE_KWRAP_CTRL_T ctrl;//warning: unused variable
	//LX_PE_NRD_TNR2ND1_CMN_T tmp_cmn2nd_param;//warning: unused variable
	//LX_PE_NRD_TNR2ND2_DETAIL_T tmp_dtl2nd_param;//warning: unused variable

	VPQ_HWRAP_CHECK_CODE(!pNrData, return RET_ERROR, "Error. pNrData is null.\n");

	wid = wId;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE  // for test 8k model to set win = 2
	if(_g_vpq_hwrap_tnr_platform_db_enable != 0xff)
		wid= (LX_PE_WIN_ID)_g_vpq_hwrap_tnr_platform_db_enable;
	#endif

	/* 1. set vpq input info */
	p_info->vpq_input[wid] = (vpq_hwrap_input_t)pNrData->ui_value[1];

	/* 2. set noise reduction */
	if(wid == LX_PE_WIN_0 || wid == LX_PE_WIN_1)
	{
		if(ver == 0x80 || lx_chip() == LX_CHIP_O26) // webos26
		{
			ret = vpq_hwrap_setnoisereduction_o26(pNrData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setnoisereduction_o26(): error %d\n", ret);
		}
		else
		{
			ret = vpq_hwrap_setnoisereduction_o20_e60_o22_o24(pNrData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setnoisereduction_o20_e60_o22_o24(): error %d\n", ret);
		}
	}
	else
	{
		ret = vpq_hwrap_setnoisereduction_f20_f22(pNrData, wid);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setnoisereduction_f20_f22(): error %d\n", ret);
	}
	return ret;
}
static int vpq_hwrap_setnoisereduction_o26(vpq_hwrap_nr_t *pNrData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) vpq_hwrap_chip_nr_o26_t *tnr_data = (vpq_hwrap_chip_nr_o26_t *)pNrData->pst_chip_data;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;
	__attribute__((unused)) LX_PE_NRD_TNR_CMN_T 	   c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_TNR_DETAIL_T	   c_dtl_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_CMN_T	   c_cmn2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_DETAIL_T  c_dtl2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_CMN_T	   c_cmn3rd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_DETAIL_T  c_dtl3rd_param;
	__attribute__((unused)) LX_PE_NRD_TNR_SQM_CMN_T    c_sqm_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_SQM_CMN_T c_sqm2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_SQM_CMN_T c_sqm3rd_param;
	__attribute__((unused)) LX_PE_NRD_TNR1_CMN_T		cmn_param; // added @026 , sicreq-1154
	__attribute__((unused)) LX_PE_NRD_TNR2_DETAIL_T 	dtl_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND2_CMN_T 	cmn2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND3_DETAIL_T	dtl2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND2_CMN_T 	cmn3rd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND3_DETAIL_T	dtl3rd_param;
	__attribute__((unused)) LX_PE_NRD_TNR_SQM1_CMN_T	sqm_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_SQM1_CMN_T sqm2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_SQM1_CMN_T sqm3rd_param;
	__attribute__((unused)) LX_PE_NRD_TNR_FACE_T		face_param; // added @026 , sicreq-1154

	/*for pioneer*/
	//PE_KWRAP_CTRL_T ctrl;//warning: unused variable
	//LX_PE_NRD_TNR2ND1_CMN_T tmp_cmn2nd_param;//warning: unused variable
	//LX_PE_NRD_TNR2ND2_DETAIL_T tmp_dtl2nd_param;//warning: unused variable

	VPQ_HWRAP_CHECK_CODE(!pNrData, return RET_ERROR, "Error. pNrData is null.\n");

	wid = wId;

	db_mode = _g_vpq_hwrap_tnr_platform_db_enable;
	if (PE_KDRV_VER_O22||PE_KDRV_VER_M23)
		db_mode = 1;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE // for test 8k model to set win = 2
	if(tnr_data)
	#else
	if(tnr_data && db_mode)
	#endif
	{
		/*set config of common struncture*/
		c_cmn_param.win_id = c_dtl_param.win_id = c_cmn2nd_param.win_id = c_dtl2nd_param.win_id = wid;
		c_sqm_param.win_id = c_sqm2nd_param.win_id = wid;
		c_cmn3rd_param.win_id = c_dtl3rd_param.win_id = c_sqm3rd_param.win_id = wid;
		c_cmn_param.oper = c_dtl_param.oper = c_cmn2nd_param.oper = c_dtl2nd_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm_param.oper = c_sqm2nd_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn3rd_param.oper = c_dtl3rd_param.oper = c_sqm3rd_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data	= (UINT32 *)&cmn_param;
		c_dtl_param.data	= (UINT32 *)&dtl_param;
		c_cmn2nd_param.data = (UINT32 *)&cmn2nd_param;
		c_dtl2nd_param.data = (UINT32 *)&dtl2nd_param;
		c_sqm_param.data	= (UINT32 *)&sqm_param;
		c_sqm2nd_param.data = (UINT32 *)&sqm2nd_param;
		c_cmn3rd_param.data = (UINT32 *)&cmn3rd_param;
		c_dtl3rd_param.data = (UINT32 *)&dtl3rd_param;
		c_sqm3rd_param.data = (UINT32 *)&sqm3rd_param;
		c_cmn_param.size	= sizeof(LX_PE_NRD_TNR1_CMN_T);
		c_dtl_param.size	= sizeof(LX_PE_NRD_TNR2_DETAIL_T);
		c_cmn2nd_param.size = sizeof(LX_PE_NRD_TNR2ND2_CMN_T);
		c_dtl2nd_param.size = sizeof(LX_PE_NRD_TNR2ND3_DETAIL_T);
		c_sqm_param.size	= sizeof(LX_PE_NRD_TNR_SQM1_CMN_T);
		c_sqm2nd_param.size = sizeof(LX_PE_NRD_TNR2ND_SQM1_CMN_T);
		c_cmn3rd_param.size = sizeof(LX_PE_NRD_TNR2ND_CMN_T);
		c_dtl3rd_param.size = sizeof(LX_PE_NRD_TNR2ND_DETAIL_T);
		c_sqm3rd_param.size = sizeof(LX_PE_NRD_TNR2ND_SQM_CMN_T);
		sqm_param.tnr___val = sqm2nd_param.tnr___val = pNrData->ui_value[0];

		/******** ND0 *************/
		/*copy to local register*/
		memcpy(&(cmn_param.tnr0__lut), &(tnr_data->tnr0__lut), sizeof(tnr_data->tnr0__lut));
		memcpy(&(cmn_param.tnr0_gain), &(tnr_data->tnr0_gain), sizeof(tnr_data->tnr0_gain));
		memcpy(&(cmn_param.tnr0_buff), &(tnr_data->tnr0_buff), sizeof(tnr_data->tnr0_buff));
		memcpy(&(dtl_param.tnr0__ctl), &(tnr_data->tnr0__ctl), sizeof(tnr_data->tnr0__ctl));
		memcpy(&(dtl_param.tnr0___ma), &(tnr_data->tnr0___ma), sizeof(tnr_data->tnr0___ma));
		memcpy(&(dtl_param.tnr0___me), &(tnr_data->tnr0___me), sizeof(tnr_data->tnr0___me));
		memcpy(&(dtl_param.tnr0__mlb), &(tnr_data->tnr0__mlb), sizeof(tnr_data->tnr0__mlb));
		memcpy(&(dtl_param.tnr0___mc), &(tnr_data->tnr0___mc), sizeof(tnr_data->tnr0___mc));
		memcpy(&(dtl_param.tnr0_blnd), &(tnr_data->tnr0_blnd), sizeof(tnr_data->tnr0_blnd));
		memcpy(&(sqm_param.tnr0__sqm), &(tnr_data->tnr0__sqm), sizeof(tnr_data->tnr0__sqm));
		memcpy(&(face_param.tnr0_face_gain), &(tnr_data->tnr0_face_gain), sizeof(tnr_data->tnr0_face_gain));

		/*set ui value*/
		if(tnr_data->tnr0___en == 0x0)
		{
			cmn_param.tnr0___en = 0x0;
		}
		else
		{
			cmn_param.tnr0___en = pNrData->ui_value[0];
		}
		cmn_param.win_id = dtl_param.win_id = sqm_param.win_id	= face_param.win_id = wid;
		PQ_PRINT_TNR("\n=========== pltf param===============\n");
		PQ_PRINT_TNR("tnr0___en:%d\n",cmn_param.tnr0___en);
		pd32 = (tnr_data->tnr0__lut);
		PQ_PRINT_TNR("tnr0__lut\n" \
		"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (tnr_data->tnr0_gain);
		PQ_PRINT_TNR("tnr0_gain\n" \
		"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (tnr_data->tnr0_face_gain);
		PQ_PRINT_TNR("tnr0_face\n" \
		"tnr0_face[00]0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3]);
		pd32 = (tnr_data->tnr0_buff);
		PQ_PRINT_TNR("tnr0_buff\n" \
		"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (tnr_data->tnr0__ctl);
		PQ_PRINT_TNR("tnr0__ctl\n"
		"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (tnr_data->tnr0___ma);
		PQ_PRINT_TNR("tnr0___ma\n"
		"tnr0___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (tnr_data->tnr0___me);
		PQ_PRINT_TNR("tnr0___me\n"
		"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (tnr_data->tnr0__mlb);
		PQ_PRINT_TNR("tnr0__mlb\n"
		"tnr0__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (tnr_data->tnr0___mc);
		PQ_PRINT_TNR("tnr0___mc\n"
		"tnr0___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);
		pd = (tnr_data->tnr0_blnd);
		PQ_PRINT_TNR("tnr0_blnd\n"
		"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (tnr_data->tnr0__sqm);
		PQ_PRINT_TNR("tnr0_blnd\n"
		"tnr0__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__sqm[10]0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10]);

		ret = PE_NRD_SetTnrCmnCtrl((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnrCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetTnrFaceCtrl((void *)&face_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnrFaceCtrl(): error %d\n", ret);
		ret = PE_NRD_SetTnrDetailCtrl((void *)&c_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnrDetailCtrl(): error %d\n", ret);
		ret = PE_NRD_SetTnrSqmCmnCtrl((void *)&c_sqm_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnrSqmCmnCtrl(): error %d\n", ret);

		/******** ND1 *************/
		/*copy to local register*/
		memcpy(&(cmn2nd_param.tnr1__lut), &(tnr_data->tnr1__lut), sizeof(tnr_data->tnr1__lut));
		memcpy(&(cmn2nd_param.tnr1_gain), &(tnr_data->tnr1_gain), sizeof(tnr_data->tnr1_gain));
		memcpy(&(cmn2nd_param.tnr1_buff), &(tnr_data->tnr1_buff), sizeof(tnr_data->tnr1_buff));
		memcpy(&(dtl2nd_param.tnr1__ctl), &(tnr_data->tnr1__ctl), sizeof(tnr_data->tnr1__ctl));
		memcpy(&(dtl2nd_param.tnr1___ma), &(tnr_data->tnr1___ma), sizeof(tnr_data->tnr1___ma));
		memcpy(&(dtl2nd_param.tnr1___me), &(tnr_data->tnr1___me), sizeof(tnr_data->tnr1___me));
		memcpy(&(dtl2nd_param.tnr1__mlb), &(tnr_data->tnr1__mlb), sizeof(tnr_data->tnr1__mlb));
		memcpy(&(dtl2nd_param.tnr1___mc), &(tnr_data->tnr1___mc), sizeof(tnr_data->tnr1___mc));
		memcpy(&(dtl2nd_param.tnr1_blnd), &(tnr_data->tnr1_blnd), sizeof(tnr_data->tnr1_blnd));
		memcpy(&(sqm2nd_param.tnr1__sqm), &(tnr_data->tnr1__sqm), sizeof(tnr_data->tnr1__sqm));
		/*set ui value*/
		if(tnr_data->tnr1___en == 0x0)
		{
			cmn2nd_param.tnr1___en = 0x0;
		}
		else
		{
			cmn2nd_param.tnr1___en = pNrData->ui_value[0];
		}
		cmn2nd_param.win_id = dtl2nd_param.win_id = sqm2nd_param.win_id = wid;
		PQ_PRINT_TNR("\n=========== pltf param===============\n");
		PQ_PRINT_TNR("tnr1___en:%d\n",tnr_data->tnr1___en);
		pd32 = (tnr_data->tnr1__lut);
		PQ_PRINT_TNR("tnr1__lut\n" \
		"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (tnr_data->tnr1_gain);
		PQ_PRINT_TNR("tnr1_gain\n" \
		"tnr1_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (tnr_data->tnr1_buff);
		PQ_PRINT_TNR("tnr1_buff\n" \
		"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (tnr_data->tnr1__ctl);
		PQ_PRINT_TNR("tnr1__ctl\n"
		"tnr1__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (tnr_data->tnr1___ma);
		PQ_PRINT_TNR("tnr1___ma\n"
		"tnr1___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (tnr_data->tnr1___me);
		PQ_PRINT_TNR("tnr1___me\n"
		"tnr1___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (tnr_data->tnr1__mlb);
		PQ_PRINT_TNR("tnr1__mlb\n"
		"tnr1__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (tnr_data->tnr1___mc);
		PQ_PRINT_TNR("tnr1___mc\n"
		"tnr1___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);
		pd = (tnr_data->tnr1_blnd);
		PQ_PRINT_TNR("tnr1_blnd\n"
		"tnr1_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (tnr_data->tnr1__sqm);
		PQ_PRINT_TNR("tnr1__sqm\n"
		"tnr1__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr1__sqm[10]0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10]);

		ret = PE_NRD_SetTnr2ndCmnCtrl((void *)&c_cmn2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr2ndCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetTnr2ndDetailCtrl((void *)&c_dtl2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr2ndDetailCtrl(): error %d\n", ret);
		ret = PE_NRD_SetTnr2ndSqmCmnCtrl((void *)&c_sqm2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr2ndSqmCmnCtrl(): error %d\n", ret);

		/******** ND2 *************/
		/*copy to local register*/
		memcpy(&(cmn3rd_param.tnr1__lut), &(tnr_data->tnr2__lut), sizeof(tnr_data->tnr2__lut));
		memcpy(&(cmn3rd_param.tnr1_gain), &(tnr_data->tnr2_gain), sizeof(tnr_data->tnr2_gain));
		memcpy(&(cmn3rd_param.tnr1_buff), &(tnr_data->tnr2_buff), sizeof(tnr_data->tnr2_buff));
		memcpy(&(dtl3rd_param.tnr1__ctl), &(tnr_data->tnr2__ctl), sizeof(tnr_data->tnr2__ctl));
		memcpy(&(dtl3rd_param.tnr1___ma), &(tnr_data->tnr2___ma), sizeof(tnr_data->tnr2___ma));
		memcpy(&(dtl3rd_param.tnr1___me), &(tnr_data->tnr2___me), sizeof(tnr_data->tnr2___me));
		memcpy(&(dtl3rd_param.tnr1__mlb), &(tnr_data->tnr2__mlb), sizeof(tnr_data->tnr2__mlb));
		memcpy(&(dtl3rd_param.tnr1___mc), &(tnr_data->tnr2___mc), sizeof(tnr_data->tnr2___mc));
		memcpy(&(dtl3rd_param.tnr1_blnd), &(tnr_data->tnr2_blnd), sizeof(tnr_data->tnr2_blnd));
		memcpy(&(sqm3rd_param.tnr1__sqm), &(tnr_data->tnr2__sqm), sizeof(tnr_data->tnr2__sqm));
		/*set ui value*/
		if(tnr_data->tnr2___en == 0x0)
		{
			cmn3rd_param.tnr1___en = 0x0;
		}
		else
		{
			cmn3rd_param.tnr1___en = pNrData->ui_value[0];
		}
		cmn3rd_param.win_id = dtl3rd_param.win_id = sqm3rd_param.win_id = wid;
		PQ_PRINT_TNR("\n=========== pltf param===============\n");
		PQ_PRINT_TNR("tnr2___en:%d\n",tnr_data->tnr2___en);
		pd32 = (tnr_data->tnr2__lut);
		PQ_PRINT_TNR("tnr2__lut\n" \
		"tnr2__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr2__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (tnr_data->tnr2_gain);
		PQ_PRINT_TNR("tnr2_gain\n" \
		"tnr2_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (tnr_data->tnr2_buff);
		PQ_PRINT_TNR("tnr2_buff\n" \
		"tnr2_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr2_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (tnr_data->tnr2__ctl);
		PQ_PRINT_TNR("tnr2__ctl\n"
		"tnr2__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr2__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr2__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (tnr_data->tnr2___ma);
		PQ_PRINT_TNR("tnr2___ma\n"
		"tnr2___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (tnr_data->tnr2___me);
		PQ_PRINT_TNR("tnr2___me\n"
		"tnr2___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (tnr_data->tnr2__mlb);
		PQ_PRINT_TNR("tnr2__mlb\n"
		"tnr2__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr2__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (tnr_data->tnr2___mc);
		PQ_PRINT_TNR("tnr2___mc\n"
		"tnr2___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr2___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr2___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr2___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);
		pd = (tnr_data->tnr2_blnd);
		PQ_PRINT_TNR("tnr2_blnd\n"
		"tnr2_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr2_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr2_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (tnr_data->tnr2__sqm);
		PQ_PRINT_TNR("tnr2__sqm\n"
		"tnr2__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr2__sqm[10]0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10]);


		ret = PE_NRD_SetTnr3rdCmnCtrl((void *)&c_cmn3rd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr3rdCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetTnr3rdDetailCtrl((void *)&c_dtl3rd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr3rdCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetTnr3rdSqmCmnCtrl((void *)&c_sqm3rd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr3rdSqmCmnCtrl(): error %d\n", ret);

	}
	else
	{
		UINT32 param_data = 0;
		LX_PE_DBTYPE dbtype = LX_PE_PLATFORM_NUM;
		LX_PE_NRD_TNR_CMN_T pstParam;
		LX_PE_NRD_TNR1_CMN_T ctrl;

		param_data = (pNrData->ui_value[0]<VPQ_HWRAP_NRD_NUM)? \
			pNrData->ui_value[0]:VPQ_HWRAP_NRD_OFF;
		memcpy(&ctrl, &(g_pe_hwrap_p_tnr1_drvsetting_cmn[param_data]), sizeof(LX_PE_NRD_TNR1_CMN_T));
		pd32 = (ctrl.tnr0__lut);
		PQ_PRINT_TNR( \
		"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (ctrl.tnr0_gain);
		PQ_PRINT_TNR(\
		"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (ctrl.tnr0_buff);
		PQ_PRINT_TNR(\
		"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pstParam.win_id = wid;
		pstParam.oper = dbtype;
		pstParam.size = sizeof(LX_PE_NRD_TNR1_CMN_T);
		pstParam.data = (UINT32*)&ctrl;
		ret = PE_NRD_SetTnrCmnCtrl((void*)&pstParam);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnrCmnCtrl(): error %d\n", ret);
	}
	return ret;
}

static int vpq_hwrap_setnoisereduction_o20_e60_o22_o24(vpq_hwrap_nr_t *pNrData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t *tnr_data = (vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t *)pNrData->pst_chip_data;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;
	__attribute__((unused)) LX_PE_NRD_TNR_CMN_T 	   c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_TNR_DETAIL_T	   c_dtl_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_CMN_T	   c_cmn2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_DETAIL_T  c_dtl2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR_SQM_CMN_T    c_sqm_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_SQM_CMN_T c_sqm2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR1_CMN_T		cmn_param;
	__attribute__((unused)) LX_PE_NRD_TNR2_DETAIL_T 	dtl_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND2_CMN_T 	cmn2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND3_DETAIL_T	dtl2nd_param;
	__attribute__((unused)) LX_PE_NRD_TNR_SQM1_CMN_T	sqm_param;
	__attribute__((unused)) LX_PE_NRD_TNR2ND_SQM1_CMN_T sqm2nd_param;

	/*for pioneer*/
	//PE_KWRAP_CTRL_T ctrl;//warning: unused variable
	//LX_PE_NRD_TNR2ND1_CMN_T tmp_cmn2nd_param;//warning: unused variable
	//LX_PE_NRD_TNR2ND2_DETAIL_T tmp_dtl2nd_param;//warning: unused variable

	VPQ_HWRAP_CHECK_CODE(!pNrData, return RET_ERROR, "Error. pNrData is null.\n");

	wid = wId;

	db_mode = _g_vpq_hwrap_tnr_platform_db_enable;
	if (PE_KDRV_VER_O22||PE_KDRV_VER_M23)
		db_mode = 1;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE // for test 8k model to set win = 2
	if(tnr_data)
	#else
	if(tnr_data && db_mode)
	#endif
	{
		/*set config of common struncture*/
		c_cmn_param.win_id = c_dtl_param.win_id = c_cmn2nd_param.win_id = c_dtl2nd_param.win_id = wid;
		c_sqm_param.win_id = c_sqm2nd_param.win_id = wid;
		c_cmn_param.oper = c_dtl_param.oper = c_cmn2nd_param.oper = c_dtl2nd_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm_param.oper = c_sqm2nd_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data	= (UINT32 *)&cmn_param;
		c_dtl_param.data	= (UINT32 *)&dtl_param;
		c_cmn2nd_param.data = (UINT32 *)&cmn2nd_param;
		c_dtl2nd_param.data = (UINT32 *)&dtl2nd_param;
		c_sqm_param.data	= (UINT32 *)&sqm_param;
		c_sqm2nd_param.data = (UINT32 *)&sqm2nd_param;
		c_cmn_param.size	= sizeof(LX_PE_NRD_TNR1_CMN_T);
		c_dtl_param.size	= sizeof(LX_PE_NRD_TNR2_DETAIL_T);
		c_cmn2nd_param.size = sizeof(LX_PE_NRD_TNR2ND2_CMN_T);
		c_dtl2nd_param.size = sizeof(LX_PE_NRD_TNR2ND3_DETAIL_T);
		c_sqm_param.size	= sizeof(LX_PE_NRD_TNR_SQM1_CMN_T);
		c_sqm2nd_param.size = sizeof(LX_PE_NRD_TNR2ND_SQM1_CMN_T);
		sqm_param.tnr___val = sqm2nd_param.tnr___val = pNrData->ui_value[0];

		/*copy to local register*/
		memcpy(&(cmn_param.tnr0__lut), &(tnr_data->tnr0__lut), sizeof(tnr_data->tnr0__lut));
		memcpy(&(cmn_param.tnr0_gain), &(tnr_data->tnr0_gain), sizeof(tnr_data->tnr0_gain));
		memcpy(&(cmn_param.tnr0_buff), &(tnr_data->tnr0_buff), sizeof(tnr_data->tnr0_buff));
		memcpy(&(dtl_param.tnr0__ctl), &(tnr_data->tnr0__ctl), sizeof(tnr_data->tnr0__ctl));
		memcpy(&(dtl_param.tnr0___ma), &(tnr_data->tnr0___ma), sizeof(tnr_data->tnr0___ma));
		memcpy(&(dtl_param.tnr0___me), &(tnr_data->tnr0___me), sizeof(tnr_data->tnr0___me));
		memcpy(&(dtl_param.tnr0__mlb), &(tnr_data->tnr0__mlb), sizeof(tnr_data->tnr0__mlb));
		memcpy(&(dtl_param.tnr0___mc), &(tnr_data->tnr0___mc), sizeof(tnr_data->tnr0___mc));
		memcpy(&(dtl_param.tnr0_blnd), &(tnr_data->tnr0_blnd), sizeof(tnr_data->tnr0_blnd));
		memcpy(&(sqm_param.tnr0__sqm), &(tnr_data->tnr0__sqm), sizeof(tnr_data->tnr0__sqm));

		/*set ui value*/
		if(tnr_data->tnr0___en == 0x0)
		{
			cmn_param.tnr0___en = 0x0;
		}
		else
		{
			cmn_param.tnr0___en = pNrData->ui_value[0];
		}
		cmn_param.win_id = dtl_param.win_id = sqm_param.win_id	= wid;
		#if 0
		PE_PRINT_NRD("\n=========== drv param===============\n");
		PE_PRINT_NRD("tnr0___en:%d\n",cmn_param.tnr0___en);
		pd32 = (cmn_param.tnr0__lut);
		PE_PRINT_NRD( \
		"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (cmn_param.tnr0_gain);
		PE_PRINT_NRD(\
		"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (cmn_param.tnr0_buff);
		PE_PRINT_NRD(\
		"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (dtl_param.tnr0__ctl);
		PE_PRINT_NRD("tnr0__ctl\n"
		"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (dtl_param.tnr0___ma);
		PE_PRINT_NRD("tnr0___ma\n"
		"tnr0___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (dtl_param.tnr0___me);
		PE_PRINT_NRD("tnr0___me\n"
		"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (dtl_param.tnr0__mlb);
		PE_PRINT_NRD("tnr0__mlb\n"
		"tnr0__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (dtl_param.tnr0___mc);
		PE_PRINT_NRD("tnr0___mc\n"
		"tnr0___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);
		pd = (dtl_param.tnr0_blnd);
		PE_PRINT_NRD("tnr0_blnd\n"
		"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		#endif
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		PE_PRINT_NRD("tnr0___en:%d\n",cmn_param.tnr0___en);
		pd32 = (tnr_data->tnr0__lut);
		PE_PRINT_NRD( \
		"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (tnr_data->tnr0_gain);
		PE_PRINT_NRD(\
		"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (tnr_data->tnr0_buff);
		PE_PRINT_NRD(\
		"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (tnr_data->tnr0__ctl);
		PE_PRINT_NRD("tnr0__ctl\n"
		"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (tnr_data->tnr0___ma);
		PE_PRINT_NRD("tnr0___ma\n"
		"tnr0___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (tnr_data->tnr0___me);
		PE_PRINT_NRD("tnr0___me\n"
		"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (tnr_data->tnr0__mlb);
		PE_PRINT_NRD("tnr0__mlb\n"
		"tnr0__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (tnr_data->tnr0___mc);
		PE_PRINT_NRD("tnr0___mc\n"
		"tnr0___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);
		pd = (tnr_data->tnr0_blnd);
		PE_PRINT_NRD("tnr0_blnd\n"
		"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (tnr_data->tnr0__sqm);
		PE_PRINT_NRD("tnr0_blnd\n"
		"tnr0__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__sqm[10]0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10]);
		/*copy to local register*/
		memcpy(&(cmn2nd_param.tnr1__lut), &(tnr_data->tnr1__lut), sizeof(tnr_data->tnr1__lut));
		memcpy(&(cmn2nd_param.tnr1_gain), &(tnr_data->tnr1_gain), sizeof(tnr_data->tnr1_gain));
		memcpy(&(cmn2nd_param.tnr1_buff), &(tnr_data->tnr1_buff), sizeof(tnr_data->tnr1_buff));
		memcpy(&(dtl2nd_param.tnr1__ctl), &(tnr_data->tnr1__ctl), sizeof(tnr_data->tnr1__ctl));
		memcpy(&(dtl2nd_param.tnr1___ma), &(tnr_data->tnr1___ma), sizeof(tnr_data->tnr1___ma));
		memcpy(&(dtl2nd_param.tnr1___me), &(tnr_data->tnr1___me), sizeof(tnr_data->tnr1___me));
		memcpy(&(dtl2nd_param.tnr1__mlb), &(tnr_data->tnr1__mlb), sizeof(tnr_data->tnr1__mlb));
		memcpy(&(dtl2nd_param.tnr1___mc), &(tnr_data->tnr1___mc), sizeof(tnr_data->tnr1___mc));
		memcpy(&(dtl2nd_param.tnr1_blnd), &(tnr_data->tnr1_blnd), sizeof(tnr_data->tnr1_blnd));
		memcpy(&(sqm2nd_param.tnr1__sqm), &(tnr_data->tnr1__sqm), sizeof(tnr_data->tnr1__sqm));
		/*set ui value*/
		if(tnr_data->tnr1___en == 0x0)
		{
			cmn2nd_param.tnr1___en = 0x0;
		}
		else
		{
			cmn2nd_param.tnr1___en = pNrData->ui_value[0];
		}
		cmn2nd_param.win_id = dtl2nd_param.win_id = sqm2nd_param.win_id = wid;
		#if 0
		PE_PRINT_NRD("\n=========== drv param===============\n");
		PE_PRINT_NRD("tnr1___en:%d\n",cmn2nd_param.tnr1___en);
		pd32 = (cmn2nd_param.tnr1__lut);
		PE_PRINT_NRD( \
		"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (cmn2nd_param.tnr1_gain);
		PE_PRINT_NRD(\
		"tnr1_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (cmn2nd_param.tnr1_buff);
		PE_PRINT_NRD(\
		"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (dtl2nd_param.tnr1__ctl);
		PE_PRINT_NRD("tnr1__ctl\n"
		"tnr1__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (dtl2nd_param.tnr1___ma);
		PE_PRINT_NRD("tnr1___ma\n"
		"tnr1___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (dtl2nd_param.tnr1___me);
		PE_PRINT_NRD("tnr1___me\n"
		"tnr1___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (dtl2nd_param.tnr1__mlb);
		PE_PRINT_NRD("tnr1__mlb\n"
		"tnr1__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (dtl2nd_param.tnr1___mc);
		PE_PRINT_NRD("tnr1___mc\n"
		"tnr1___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);

		pd = (dtl2nd_param.tnr1_blnd);
		PE_PRINT_NRD("tnr1_blnd\n"
		"tnr1_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		#endif
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		PE_PRINT_NRD("tnr1___en:%d\n",tnr_data->tnr1___en);
		pd32 = (tnr_data->tnr1__lut);
		PE_PRINT_NRD( \
		"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (tnr_data->tnr1_gain);
		PE_PRINT_NRD(\
		"tnr1_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (tnr_data->tnr1_buff);
		PE_PRINT_NRD(\
		"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (tnr_data->tnr1__ctl);
		PE_PRINT_NRD("tnr1__ctl\n"
		"tnr1__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (tnr_data->tnr1___ma);
		PE_PRINT_NRD("tnr1___ma\n"
		"tnr1___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (tnr_data->tnr1___me);
		PE_PRINT_NRD("tnr1___me\n"
		"tnr1___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (tnr_data->tnr1__mlb);
		PE_PRINT_NRD("tnr1__mlb\n"
		"tnr1__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (tnr_data->tnr1___mc);
		PE_PRINT_NRD("tnr1___mc\n"
		"tnr1___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);
		pd = (tnr_data->tnr1_blnd);
		PE_PRINT_NRD("tnr1_blnd\n"
		"tnr1_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr1_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (tnr_data->tnr1__sqm);
		PE_PRINT_NRD("tnr0_blnd\n"
		"tnr1__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr1__sqm[10]0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10]);

		if(PE_KDRV_VER_O20)
		{
			ret = KWRAP_PE_SetTnrCmnParam((void *)&c_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnrCmnParam(): error %d\n", ret);
			ret = KWRAP_PE_SetTnr2ndCmnParam((void *)&c_cmn2nd_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnr2ndCmnParam(): error %d\n", ret);
			ret = KWRAP_PE_SetTnrDetailParam((void *)&c_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnrDetailParam(): error %d\n", ret);
			ret = KWRAP_PE_SetTnr2ndDetailParam((void *)&c_dtl2nd_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnr2ndDetailParam(): error %d\n", ret);
			ret = KWRAP_PE_SetTnrSqmCmnParam((void *)&c_sqm_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnrSqmCmnParam(): error %d\n", ret);
			ret = KWRAP_PE_SetTnr2ndSqmCmnParam((void *)&c_sqm2nd_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnr2ndSqmCmnParam(): error %d\n", ret);
		}
		else
		{
			ret = PE_NRD_SetTnrCmnCtrl((void *)&c_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnrCmnCtrl(): error %d\n", ret);
			ret = PE_NRD_SetTnr2ndCmnCtrl((void *)&c_cmn2nd_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr2ndCmnCtrl(): error %d\n", ret);
			ret = PE_NRD_SetTnrDetailCtrl((void *)&c_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnrDetailCtrl(): error %d\n", ret);
			ret = PE_NRD_SetTnr2ndDetailCtrl((void *)&c_dtl2nd_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr2ndDetailCtrl(): error %d\n", ret);
			ret = PE_NRD_SetTnrSqmCmnCtrl((void *)&c_sqm_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnrSqmCmnCtrl(): error %d\n", ret);
			ret = PE_NRD_SetTnr2ndSqmCmnCtrl((void *)&c_sqm2nd_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetTnr2ndSqmCmnCtrl(): error %d\n", ret);
		}
	}
	else
	{
		#if 1
		UINT32 param_data = 0;
		LX_PE_DBTYPE dbtype = LX_PE_PLATFORM_NUM;
		LX_PE_NRD_TNR_CMN_T pstParam;
		LX_PE_NRD_TNR1_CMN_T ctrl;

		param_data = (pNrData->ui_value[0]<VPQ_HWRAP_NRD_NUM)? \
			pNrData->ui_value[0]:VPQ_HWRAP_NRD_OFF;
		memcpy(&ctrl, &(g_pe_hwrap_p_tnr1_drvsetting_cmn[param_data]), sizeof(LX_PE_NRD_TNR1_CMN_T));
		pd32 = (ctrl.tnr0__lut);
		PE_PRINT_NRD( \
		"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (ctrl.tnr0_gain);
		PE_PRINT_NRD(\
		"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (ctrl.tnr0_buff);
		PE_PRINT_NRD(\
		"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pstParam.win_id = wid;
		pstParam.oper = dbtype;
		pstParam.size = sizeof(LX_PE_NRD_TNR1_CMN_T);
		pstParam.data = (UINT32*)&ctrl;
		ret = PE_NRD_SetTnrCmnCtrl((void*)&pstParam);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnrCmnCtrl(): error %d\n", ret);
		#endif
	}
	return ret;
}


static int vpq_hwrap_setnoisereduction_f20_f22(vpq_hwrap_nr_t *pNrData, UINT32 wId)
{
	int ret = RET_OK;
	//unsigned short *pUi = pNrData->uUi;//warning: unused variable
	__attribute__((unused)) vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t *tnr_data = (vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t *)pNrData->pst_chip_data;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;
	LX_PE_NRD_TNR_CMN_T 	   c_cmn_param;
	LX_PE_NRD_TNR_ALL_CMN_T		cmn_param;

	/*for pioneer*/
	//PE_KWRAP_CTRL_T ctrl;//warning: unused variable
	//LX_PE_NRD_TNR2ND1_CMN_T tmp_cmn2nd_param;//warning: unused variable
	//LX_PE_NRD_TNR2ND2_DETAIL_T tmp_dtl2nd_param;//warning: unused variable

	VPQ_HWRAP_CHECK_CODE(!pNrData, return RET_ERROR, "Error. pNrData is null.\n");

	wid = wId;
	if(tnr_data)
	{
		/*set config of common struncture*/
		c_cmn_param.win_id = wid;
		c_cmn_param.oper =  LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data	= (UINT32 *)&cmn_param;
		c_cmn_param.size	= sizeof(LX_PE_NRD_TNR_ALL_CMN_T);

		/*copy to local register*/
		cmn_param.tnr___val = pNrData->ui_value[0];
		memcpy(&(cmn_param.tnr0__lut), &(tnr_data->tnr0__lut), sizeof(tnr_data->tnr0__lut));
		memcpy(&(cmn_param.tnr0_gain), &(tnr_data->tnr0_gain), sizeof(tnr_data->tnr0_gain));
		memcpy(&(cmn_param.tnr0_buff), &(tnr_data->tnr0_buff), sizeof(tnr_data->tnr0_buff));
		memcpy(&(cmn_param.tnr0__ctl), &(tnr_data->tnr0__ctl), sizeof(tnr_data->tnr0__ctl));
		memcpy(&(cmn_param.tnr0___ma), &(tnr_data->tnr0___ma), sizeof(tnr_data->tnr0___ma));
		memcpy(&(cmn_param.tnr0___me), &(tnr_data->tnr0___me), sizeof(tnr_data->tnr0___me));
		memcpy(&(cmn_param.tnr0__mlb), &(tnr_data->tnr0__mlb), sizeof(tnr_data->tnr0__mlb));
		memcpy(&(cmn_param.tnr0___mc), &(tnr_data->tnr0___mc), sizeof(tnr_data->tnr0___mc));
		memcpy(&(cmn_param.tnr0_blnd), &(tnr_data->tnr0_blnd), sizeof(tnr_data->tnr0_blnd));
		memcpy(&(cmn_param.tnr0__sqm), &(tnr_data->tnr0__sqm), sizeof(tnr_data->tnr0__sqm));

		/*set ui value*/
		if(tnr_data->tnr0___en == 0x0)
		{
			cmn_param.tnr0___en = 0x0;
		}
		else
		{
			cmn_param.tnr0___en = pNrData->ui_value[0];
		}
		cmn_param.win_id = wid;
		#if 0
		PE_PRINT_NRD("\n=========== drv param===============\n");
		PE_PRINT_NRD("tnr0___en:%d\n",cmn_param.tnr0___en);
		pd32 = (cmn_param.tnr0__lut);
		PE_PRINT_NRD( \
		"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (cmn_param.tnr0_gain);
		PE_PRINT_NRD(\
		"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (cmn_param.tnr0_buff);
		PE_PRINT_NRD(\
		"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (cmn_param.tnr0__ctl);
		PE_PRINT_NRD("tnr0__ctl\n"
		"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (cmn_param.tnr0___ma);
		PE_PRINT_NRD("tnr0___ma\n"
		"tnr0___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (cmn_param.tnr0___me);
		PE_PRINT_NRD("tnr0___me\n"
		"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (cmn_param.tnr0__mlb);
		PE_PRINT_NRD("tnr0__mlb\n"
		"tnr0__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (cmn_param.tnr0___mc);
		PE_PRINT_NRD("tnr0___mc\n"
		"tnr0___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);
		pd = (cmn_param.tnr0_blnd);
		PE_PRINT_NRD("tnr0_blnd\n"
		"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		#endif
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		PE_PRINT_NRD("tnr0___en:%d\n",cmn_param.tnr0___en);
		pd32 = (tnr_data->tnr0__lut);
		PE_PRINT_NRD( \
		"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
		pd32 = (tnr_data->tnr0_gain);
		PE_PRINT_NRD(\
		"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4]);
		pd32 = (tnr_data->tnr0_buff);
		PE_PRINT_NRD(\
		"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
		pd32[8],	pd32[9],	pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

		pd = (tnr_data->tnr0__ctl);
		PE_PRINT_NRD("tnr0__ctl\n"
		"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__ctl	  [20]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20]);
		pd = (tnr_data->tnr0___ma);
		PE_PRINT_NRD("tnr0___ma\n"
		"tnr0___ma	  [00]0x%02X,0x%02X,\n",\
		pd[0], pd[1]);
		pd = (tnr_data->tnr0___me);
		PE_PRINT_NRD("tnr0___me\n"
		"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
		pd = (tnr_data->tnr0__mlb);
		PE_PRINT_NRD("tnr0__mlb\n"
		"tnr0__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		pd16 = (tnr_data->tnr0___mc);
		PE_PRINT_NRD("tnr0___mc\n"
		"tnr0___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0___mc	  [30]0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30]);
		pd = (tnr_data->tnr0_blnd);
		PE_PRINT_NRD("tnr0_blnd\n"
		"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);

		

		ret = PE_NRD_SetTnrCmnAllCtrl((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetTnrCmnParam(): error %d\n", ret);
	}
	return ret;
}

int vpq_hwrap_setmpegnoisereduction(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId, unsigned int ver)
{
	int ret = RET_OK;
	LX_PE_WIN_ID wid;
	//vpq_hwrap_info_t *p_info = &_g_vpq_hwrap_info;

	/*for pioneer*/
	//PE_KWRAP_CTRL_T ctrl;//warning: unused variable
	//LX_PE_NRD_TNR2ND1_CMN_T tmp_cmn2nd_param;//warning: unused variable
	//LX_PE_NRD_TNR2ND2_DETAIL_T tmp_dtl2nd_param;//warning: unused variable

	VPQ_HWRAP_CHECK_CODE(!pMpegNrData, return RET_ERROR, "Error. pNrData is null.\n");

	wid = wId;

	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE // for test 8k model to set win = 2
	if(_g_vpq_hwrap_dnr_platform_db_enable != 0xff)
		wid= (LX_PE_WIN_ID)_g_vpq_hwrap_dnr_platform_db_enable;
	#endif

	/* 1. set noise reduction */
	if(wid == LX_PE_WIN_0 || wid == LX_PE_WIN_1)
	{
		if(ver == 0x80 || lx_chip() == LX_CHIP_O26) // webos26
		{
			ret = vpq_hwrap_setmpegnoisereduction_o26(pMpegNrData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setmpegnoisereduction_o26(): error %d\n", ret);
		}
		else
		{
			ret = vpq_hwrap_setmpegnoisereduction_o20_e60_o22(pMpegNrData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setmpegnoisereduction_o20_e60_o22(): error %d\n", ret);
		}
	}
	else
	{
		ret = vpq_hwrap_setmpegnoisereduction_f20_f22(pMpegNrData, wid);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setmpegnoisereduction_o20_e60_o22(): error %d\n", ret);
	}
	return ret;
}

static int vpq_hwrap_setmpegnoisereduction_o26(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	__attribute__((unused)) PE_KWRAP_CTRL_T ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) LX_PE_NRD_DNR_CMN_T c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_DNR4_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_NRD_DNR_CMN_T c_cmn2nd_param;
	__attribute__((unused)) LX_PE_NRD_DNR4_CMN_T cmn2nd_param;
	__attribute__((unused)) LX_PE_NRD_DNR_DETAIL_T c_dtl_param;
	__attribute__((unused)) LX_PE_NRD_DNR4_DETAIL_T dtl_param;
	__attribute__((unused)) LX_PE_NRD_DNR_DETAIL_T c_dtl2nd_param;
	__attribute__((unused)) LX_PE_NRD_DNR3_DETAIL_T dtl2nd_param;
	__attribute__((unused)) LX_PE_NRD_DNR_SQM_CMN_T c_sqm_param;
	__attribute__((unused)) LX_PE_NRD_DNR_SQM3_CMN_T sqm_param;
	__attribute__((unused)) LX_PE_NRD_DNR_SQM_CMN_T c_sqm2nd_param;
	__attribute__((unused)) LX_PE_NRD_DNR_SQM2_CMN_T sqm2nd_param;
	__attribute__((unused)) vpq_hwrap_chip_mpeg_nr_o26_t *dnr_data;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pMpegNrData, return RET_ERROR, "Error. pMpegNrData is null.\n");

	wid = wId;
	dnr_data = (vpq_hwrap_chip_mpeg_nr_o26_t *)pMpegNrData->pst_chip_data;
	db_mode = _g_vpq_hwrap_dnr_platform_db_enable;
	if(dnr_data && db_mode)
	{
		c_cmn_param.win_id = c_dtl_param.win_id = c_sqm_param.win_id = wid;
		c_cmn_param.oper = c_dtl_param.oper= c_sqm_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32 *)&cmn_param;
		c_dtl_param.data = (UINT32 *)&dtl_param;
		c_sqm_param.data = (UINT32 *)&sqm_param;
		c_cmn_param.size = sizeof(LX_PE_NRD_DNR4_CMN_T);
		c_dtl_param.size = sizeof(LX_PE_NRD_DNR4_DETAIL_T);
		c_sqm_param.size = sizeof(LX_PE_NRD_DNR_SQM3_CMN_T);
		
		c_cmn2nd_param.win_id = c_dtl2nd_param.win_id = c_sqm2nd_param.win_id = wid;
		c_cmn2nd_param.oper = c_dtl2nd_param.oper= c_sqm2nd_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn2nd_param.data = (UINT32 *)&cmn2nd_param;
		c_dtl2nd_param.data = (UINT32 *)&dtl2nd_param;
		c_sqm2nd_param.data = (UINT32 *)&sqm2nd_param;
		c_cmn2nd_param.size = sizeof(LX_PE_NRD_DNR4_CMN_T);
		c_dtl2nd_param.size = sizeof(LX_PE_NRD_DNR4_DETAIL_T);
		c_sqm2nd_param.size = sizeof(LX_PE_NRD_DNR_SQM2_CMN_T);
		/******** ND0 *************/
		cmn_param.dnr__ui_val = sqm_param.dnr_____val = (UINT8)pMpegNrData->ui_value;
		memcpy(&(cmn_param.dnr______ui), &(dnr_data->dnr0_____ui), sizeof(dnr_data->dnr0_____ui));
		memcpy(&(cmn_param.dnr____buff), &(dnr_data->dnr0___buff), sizeof(dnr_data->dnr0___buff));
		memcpy(&(sqm_param.dnr___sqmui), &(dnr_data->dnr0__sqmui), sizeof(dnr_data->dnr0__sqmui));
		memcpy(&(dtl_param.dnr_____mnr), &(dnr_data->dnr0____mnr), sizeof(dnr_data->dnr0____mnr));
		memcpy(&(dtl_param.dnr___dcbnr), &(dnr_data->dnr0__dcbnr), sizeof(dnr_data->dnr0__dcbnr));
		memcpy(&(dtl_param.dnr___acbnr), &(dnr_data->dnr0__acbnr), sizeof(dnr_data->dnr0__acbnr));
		dtl_param.win_id = cmn_param.win_id = wid;
		sqm_param.win_id = wid;
		PQ_PRINT_DNR("\n=========== pltf param===============\n");
		pd32 =	(dnr_data->dnr0_____ui);
		PQ_PRINT_DNR(" dnr0_____ui\n"
		"dnr0_____ui	[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr0_____ui	[10]0x%08X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10]);
		pd32 = (dnr_data->dnr0___buff);
		PQ_PRINT_DNR(" dnr0___buff\n"\
		"dnr0___buff	[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		
		pd32 = (dnr_data->dnr0____mnr);
		PQ_PRINT_DNR(" dnr0____mnr\n"
		"dnr0____mnr	[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr0____mnr	[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		
		pd = (dnr_data->dnr0__dcbnr);
		PQ_PRINT_DNR(" dnr0__dcbnr\n"
		"dnr0__dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr0__dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr0__dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr0__dcbnr	[30]0x%02X,0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32]);
		
		pd =(dnr_data->dnr0__acbnr);
		PQ_PRINT_DNR(" dnr0__acbnr\n"
		"dnr0__acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr0__acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr0__acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr0__acbnr	[30]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30]);
		pd32 =(dnr_data->dnr0__sqmui);
		PQ_PRINT_DNR(" dnr0__sqmui\n"
		"dnr0__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr0__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16]);
		ret = PE_NRD_SetDnrCmnCtrl((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrSqmCmnCtrl((void *)&c_sqm_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrSqmCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDetailCtrl((void *)&c_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDetailCtrl(): error %d\n", ret);

		
		/******** ND1 *************/
		cmn2nd_param.dnr__ui_val = sqm2nd_param.dnr_____val = (UINT8)pMpegNrData->ui_value;
		memcpy(&(cmn2nd_param.dnr______ui), &(dnr_data->dnr1_____ui), sizeof(dnr_data->dnr1_____ui));
		memcpy(&(cmn2nd_param.dnr____buff), &(dnr_data->dnr1___buff), sizeof(dnr_data->dnr1___buff));
		memcpy(&(sqm2nd_param.dnr___sqmui), &(dnr_data->dnr1__sqmui), sizeof(dnr_data->dnr1__sqmui));
		memcpy(&(dtl2nd_param.dnr_____mnr), &(dnr_data->dnr1____mnr), sizeof(dnr_data->dnr1____mnr));
		memcpy(&(dtl2nd_param.dnr___dcbnr), &(dnr_data->dnr1__dcbnr), sizeof(dnr_data->dnr1__dcbnr));
		memcpy(&(dtl2nd_param.dnr___acbnr), &(dnr_data->dnr1__acbnr), sizeof(dnr_data->dnr1__acbnr));
		dtl2nd_param.win_id = cmn2nd_param.win_id = wid;
		sqm2nd_param.win_id = wid;
		PQ_PRINT_DNR("\n=========== pltf param===============\n");
		pd32 =	(dnr_data->dnr1_____ui);
		PQ_PRINT_DNR(" dnr1_____ui\n"
		"dnr1_____ui	[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8]);
		pd32 = (dnr_data->dnr1___buff);
		PQ_PRINT_DNR(" dnr1___buff\n"\
		"dnr1___buff	[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		
		pd = (dnr_data->dnr1____mnr);
		PQ_PRINT_DNR(" dnr1____mnr\n"
		"dnr1____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		
		pd = (dnr_data->dnr1__dcbnr);
		PQ_PRINT_DNR(" dnr1__dcbnr\n"
		"dnr1__dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr1__dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr1__dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr1__dcbnr	[30]0x%02X,0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32]);
		
		pd =(dnr_data->dnr1__acbnr);
		PQ_PRINT_DNR(" dnr1__acbnr\n"
		"dnr1__acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr1__acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr1__acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr1__acbnr	[30]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30]);
		pd32 =(dnr_data->dnr1__sqmui);
		PQ_PRINT_DNR(" dnr1__sqmui\n"
		"dnr1__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr1__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14]);
		ret = PE_NRD_SetDnr2ndCmnCtrl((void *)&c_cmn2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnr2ndCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnr2ndSqmCmnCtrl((void *)&c_sqm2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnr2ndSqmCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnr2ndDetailCtrl((void *)&c_dtl2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnr2ndDetailCtrl(): error %d\n", ret);
	}
	else
	{
		dbtype = LX_PE_PLATFORM_NUM; //easy DB
		ctrl.wid = LX_PE_WIN_0;
		ctrl.data = (UINT32)pMpegNrData->ui_value;
		ctrl.st_data = (void *)&dbtype;
		{
			UINT32 param_data = 0;
			LX_PE_NRD_DNR_CMN_T pstParam;
			LX_PE_NRD_EASY_DNR_CMN_T ctrl;
			param_data = (pMpegNrData->ui_value<VPQ_HWRAP_NRD_NUM)? \
				pMpegNrData->ui_value:VPQ_HWRAP_NRD_OFF;
			memcpy(&ctrl, &(g_pe_hwrap_p_easy_dnr_cmn[param_data]), sizeof(LX_PE_NRD_EASY_DNR_CMN_T));
			pd =	(ctrl.data);
			PQ_PRINT_DNR(" dnr______ui\n"
			"dnr eay db	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnr eay db	[10]0x%02X,0x%02X\n",\
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);

			pstParam.win_id = ctrl.win_id;
			pstParam.oper = dbtype;
			pstParam.size = sizeof(LX_PE_NRD_EASY_DNR_CMN_T);
			pstParam.data = (UINT32*)&ctrl;
			ret = PE_NRD_SetDnrCmnCtrl(&pstParam);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrCmnCtrl(): error %d\n", ret);
		}
	}
	return ret;
}

static int vpq_hwrap_setmpegnoisereduction_o20_e60_o22(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	__attribute__((unused)) PE_KWRAP_CTRL_T ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) LX_PE_NRD_DNR_CMN_T c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_DNR3_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_NRD_DNR_DETAIL_T c_dtl_param;
	__attribute__((unused)) LX_PE_NRD_DNR3_DETAIL_T dtl_param;
	__attribute__((unused)) LX_PE_NRD_DNR_SQM_CMN_T c_sqm_param;
	__attribute__((unused)) LX_PE_NRD_DNR_SQM2_CMN_T sqm_param;
	__attribute__((unused)) vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t *dnr_data;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pMpegNrData, return RET_ERROR, "Error. pMpegNrData is null.\n");

	wid = wId;
	dnr_data = (vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t *)pMpegNrData->pst_chip_data;
	db_mode = _g_vpq_hwrap_dnr_platform_db_enable;
	if (PE_KDRV_VER_O22||PE_KDRV_VER_M23)
		db_mode = 1;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE // for test 8k model to set win = 2
	if(dnr_data)
	#else
	if(dnr_data && db_mode)
	#endif
	{
		c_cmn_param.win_id = c_dtl_param.win_id = c_sqm_param.win_id = wid;
		c_cmn_param.oper = c_dtl_param.oper= c_sqm_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32 *)&cmn_param;
		c_dtl_param.data = (UINT32 *)&dtl_param;
		c_sqm_param.data = (UINT32 *)&sqm_param;
		c_cmn_param.size = sizeof(LX_PE_NRD_DNR3_CMN_T);
		c_dtl_param.size = sizeof(LX_PE_NRD_DNR3_DETAIL_T);
		c_sqm_param.size = sizeof(LX_PE_NRD_DNR_SQM2_CMN_T);
		cmn_param.dnr__ui_val = sqm_param.dnr_____val = (UINT8)pMpegNrData->ui_value;
		memcpy(&(cmn_param.dnr______ui), &(dnr_data->dnr______ui), sizeof(dnr_data->dnr______ui));
		memcpy(&(cmn_param.dnr____buff), &(dnr_data->dnr____buff), sizeof(dnr_data->dnr____buff));
		memcpy(&(sqm_param.dnr___sqmui), &(dnr_data->dnr___sqmui), sizeof(dnr_data->dnr___sqmui));
		memcpy(&(dtl_param.dnr_____mnr), &(dnr_data->dnr_____mnr), sizeof(dnr_data->dnr_____mnr));
		memcpy(&(dtl_param.dnr___dcbnr), &(dnr_data->dnr___dcbnr), sizeof(dnr_data->dnr___dcbnr));
		memcpy(&(dtl_param.dnr___acbnr), &(dnr_data->dnr___acbnr), sizeof(dnr_data->dnr___acbnr));
		dtl_param.win_id = cmn_param.win_id = wid;
		sqm_param.win_id = wid;
		#if 0
		PE_PRINT_NRD("\n=========== drv param===============\n");
		pd32 =	(cmn_param.dnr______ui);
		PE_PRINT_NRD(" dnr______ui\n"
		"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12]);
		pd32 = (cmn_param.dnr____buff);
		PE_PRINT_NRD(" dnr____buff\n"\
		"dnr____buff	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		
		pd = (dtl_param.dnr_____mnr);
		PE_PRINT_NRD(" dnr_____mnr\n"
		"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		
		pd = (dtl_param.dnr___dcbnr);
		PE_PRINT_NRD(" dnr___dcbnr\n"
		"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32], pd[33]);
		
		pd =(dtl_param.dnr___acbnr);
		PE_PRINT_NRD(" dnr___acbnr\n"
		"dnr___acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[30]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30]);
		pd32 =(sqm_param.dnr___sqmui);
		PE_PRINT_NRD(" dnr___acbnr\n"
		"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14]);
		#endif
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		pd32 =	(dnr_data->dnr______ui);
		PE_PRINT_NRD(" dnr______ui\n"
		"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12]);
		pd32 = (dnr_data->dnr____buff);
		PE_PRINT_NRD(" dnr____buff\n"\
		"dnr____buff	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		
		pd = (dnr_data->dnr_____mnr);
		PE_PRINT_NRD(" dnr_____mnr\n"
		"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		
		pd = (dnr_data->dnr___dcbnr);
		PE_PRINT_NRD(" dnr___dcbnr\n"
		"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32], pd[33]);
		
		pd =(dnr_data->dnr___acbnr);
		PE_PRINT_NRD(" dnr___acbnr\n"
		"dnr___acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[30]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30]);
		pd32 =(dnr_data->dnr___sqmui);
		PE_PRINT_NRD(" dnr___acbnr\n"
		"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14]);
		if(PE_KDRV_VER_O20)
		{
			ret = KWRAP_PE_SetDnrCmnParam((void *)&c_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDnrCmnParam(): error %d\n", ret);
			ret = KWRAP_PE_SetDnrSqmCmnParam((void *)&c_sqm_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDnrSqmCmnParam(): error %d\n", ret);
			ret = KWRAP_PE_SetDnrDetailParam((void *)&c_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDnrDetailParam(): error %d\n", ret);
		}
		else
		{
			ret = PE_NRD_SetDnrCmnCtrl((void *)&c_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrCmnCtrl(): error %d\n", ret);
			ret = PE_NRD_SetDnrSqmCmnCtrl((void *)&c_sqm_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrSqmCmnCtrl(): error %d\n", ret);
			ret = PE_NRD_SetDnrDetailCtrl((void *)&c_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDetailCtrl(): error %d\n", ret);
		}
	}
	else
	{
		dbtype = LX_PE_PLATFORM_NUM; //easy DB
		ctrl.wid = LX_PE_WIN_0;
		ctrl.data = (UINT32)pMpegNrData->ui_value;
		ctrl.st_data = (void *)&dbtype;
		{
			UINT32 param_data = 0;
			LX_PE_NRD_DNR_CMN_T pstParam;
			LX_PE_NRD_EASY_DNR_CMN_T ctrl;
			param_data = (pMpegNrData->ui_value<VPQ_HWRAP_NRD_NUM)? \
				pMpegNrData->ui_value:VPQ_HWRAP_NRD_OFF;
			memcpy(&ctrl, &(g_pe_hwrap_p_easy_dnr_cmn[param_data]), sizeof(LX_PE_NRD_EASY_DNR_CMN_T));
			pd =	(ctrl.data);
			PE_PRINT_NRD(" dnr______ui\n"
			"dnr eay db	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnr eay db	[10]0x%02X,0x%02X\n",\
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);

			pstParam.win_id = ctrl.win_id;
			pstParam.oper = dbtype;
			pstParam.size = sizeof(LX_PE_NRD_EASY_DNR_CMN_T);
			pstParam.data = (UINT32*)&ctrl;
			ret = PE_NRD_SetDnrCmnCtrl(&pstParam);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrCmnCtrl(): error %d\n", ret);
		}
	}
	return ret;
}
static int vpq_hwrap_setmpegnoisereduction_f20_f22(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId)
{
	int ret = RET_OK;
	LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	//PE_KWRAP_CTRL_T ctrl;
	//LX_PE_DBTYPE dbtype;
	LX_PE_NRD_DNR_CMN_T c_cmn_param;
	LX_PE_NRD_DNR_ALL_CMN_T cmn_param;
	vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t *dnr_data;
	__attribute__((unused)) UINT8 *pd = NULL;
	//UINT16 *pd16 = NULL;
	UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pMpegNrData, return RET_ERROR, "Error. pMpegNrData is null.\n");

	wid = wId;
	dnr_data = (vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t *)pMpegNrData->pst_chip_data;
	if(dnr_data)
	{
		c_cmn_param.win_id =  wid;
		c_cmn_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32 *)&cmn_param;
		c_cmn_param.size = sizeof(LX_PE_NRD_DNR3_CMN_T);
		cmn_param.win_id= wid;
		cmn_param.dnr__ui_val = (UINT8)pMpegNrData->ui_value;
		memcpy(&(cmn_param.dnr______ui), &(dnr_data->dnr______ui), sizeof(dnr_data->dnr______ui));
		memcpy(&(cmn_param.dnr____buff), &(dnr_data->dnr____buff), sizeof(dnr_data->dnr____buff));
		memcpy(&(cmn_param.dnr___sqmui), &(dnr_data->dnr___sqmui), sizeof(dnr_data->dnr___sqmui));
		memcpy(&(cmn_param.dnr_____mnr), &(dnr_data->dnr_____mnr), sizeof(dnr_data->dnr_____mnr));
		memcpy(&(cmn_param.dnr___dcbnr), &(dnr_data->dnr___dcbnr), sizeof(dnr_data->dnr___dcbnr));
		memcpy(&(cmn_param.dnr___acbnr), &(dnr_data->dnr___acbnr), sizeof(dnr_data->dnr___acbnr));
		#if 0
		PE_PRINT_NRD("\n=========== drv param===============\n");
		pd32 =	(cmn_param.dnr______ui);
		PE_PRINT_NRD(" dnr______ui\n"
		"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12]);
		pd32 = (cmn_param.dnr____buff);
		PE_PRINT_NRD(" dnr____buff\n"\
		"dnr____buff	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		
		pd = (cmn_param.dnr_____mnr);
		PE_PRINT_NRD(" dnr_____mnr\n"
		"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		
		pd = (cmn_param.dnr___dcbnr);
		PE_PRINT_NRD(" dnr___dcbnr\n"
		"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32], pd[33]);
		
		pd =(cmn_param.dnr___acbnr);
		PE_PRINT_NRD(" dnr___acbnr\n"
		"dnr___acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[30]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30]);
		pd32 =(cmn_param.dnr___sqmui);
		PE_PRINT_NRD(" dnr___acbnr\n"
		"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14]);
		#endif
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		pd32 =	(dnr_data->dnr______ui);
		PE_PRINT_NRD(" dnr______ui\n"
		"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12]);
		pd32 = (dnr_data->dnr____buff);
		PE_PRINT_NRD(" dnr____buff\n"\
		"dnr____buff	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		
		pd = (dnr_data->dnr_____mnr);
		PE_PRINT_NRD(" dnr_____mnr\n"
		"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		
		pd = (dnr_data->dnr___dcbnr);
		PE_PRINT_NRD(" dnr___dcbnr\n"
		"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31], pd[32], pd[33]);
		
		pd =(dnr_data->dnr___acbnr);
		PE_PRINT_NRD(" dnr___acbnr\n"
		"dnr___acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"dnr___acbnr	[30]0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30]);
		pd32 =(dnr_data->dnr___sqmui);
		PE_PRINT_NRD(" dnr___acbnr\n"
		"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14]);
		ret = PE_NRD_SetDnrCmnAllCtrl((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrCmnAllCtrl(): error %d\n", ret);
	}
	return ret;
}

int vpq_hwrap_setsuperresoulution(vpq_hwrap_sr_t *pSrData)
{
	int ret = RET_OK;

	return ret;
}
int vpq_hwrap_setdecontour(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId, unsigned int ver)
{
	int ret = RET_OK;
	LX_PE_WIN_ID wid;
	//vpq_hwrap_info_t *p_info = &_g_vpq_hwrap_info;

	/*for pioneer*/
	//PE_KWRAP_CTRL_T ctrl;//warning: unused variable
	//LX_PE_NRD_TNR2ND1_CMN_T tmp_cmn2nd_param;//warning: unused variable
	//LX_PE_NRD_TNR2ND2_DETAIL_T tmp_dtl2nd_param;//warning: unused variable

	VPQ_HWRAP_CHECK_CODE(!pDecontourData, return RET_ERROR, "Error. pNrData is null.\n");

	wid = wId;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE  // for test 8k model to set win = 2
	if(_g_vpq_hwrap_dct_platform_db_enable != 0xff)
		wid= (LX_PE_WIN_ID)_g_vpq_hwrap_dct_platform_db_enable;
	#endif

	/* 1. set decontour */
	if(wid == LX_PE_WIN_0 || wid == LX_PE_WIN_1) // onechip model
	{
		if(ver == 0x80 || lx_chip() == LX_CHIP_O26)
		{
			ret = vpq_hwrap_setdecontour_o26(pDecontourData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setdecontour_o26(): error %d\n", ret);
		}
		else if(ver == 0x60)
		{
			ret = vpq_hwrap_setdecontour_o24(pDecontourData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setdecontour_o24(): error %d\n", ret);
		}
		else if(PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
		{
			ret = vpq_hwrap_setdecontour_o20_e60(pDecontourData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setmpegnoisereduction_o20_e60(): error %d\n", ret);
		}
		else
		{
			ret = vpq_hwrap_setdecontour_o22(pDecontourData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setdecontour_o22(): error %d\n", ret);
		}
	}
	else // externel chip model
	{
		if(PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
		{
			ret = vpq_hwrap_setdecontour_f20(pDecontourData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setmpegnoisereduction_f20(): error %d\n", ret);
		}
		else if(PE_KDRV_VER_O22)
		{
			ret = vpq_hwrap_setdecontour_f22(pDecontourData, wid);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "vpq_hwrap_setdecontour_f22(): error %d\n", ret);
		}
	}
	return ret;
}

static int vpq_hwrap_setdecontour_o26(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	__attribute__((unused)) vpq_hwrap_chip_decontour_o26_t *dcnt_data;
	__attribute__((unused)) PE_KWRAP_CTRL_T ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	//nd0
	__attribute__((unused)) LX_PE_NRD_DCNT_CMN_T c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT3_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM_CMN_T c_sqm_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM2_CMN_T sqm_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_DETAIL_T c_dtl_param;
	__attribute__((unused)) LX_PE_NRD_DCNT5_DETAIL_T dtl_param;
	//nd1
	__attribute__((unused)) LX_PE_NRD_DCNT_CMN_T c_cmn2nd_param;
	__attribute__((unused)) LX_PE_NRD_DCNT3_CMN_T cmn2nd_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM_CMN_T c_sqm2nd_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM2_CMN_T sqm2nd_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_DETAIL_T c_dtl2nd_param;
	__attribute__((unused)) LX_PE_NRD_DCNT5_DETAIL_T dtl2nd_param; // use same DB because dcnt0 db > dcnt1 db
	//cco
	__attribute__((unused)) LX_PE_CCO_DCNT_CMN_T c_cco_cmn_param;
	__attribute__((unused)) LX_PE_CCO_DCNT1_CMN_T cco_cmn_param;
	__attribute__((unused)) LX_PE_CCO_DCNT_SQM_CMN_T c_cco_sqm_param;
	__attribute__((unused)) LX_PE_CCO_DCNT_SQM1_CMN_T cco_sqm_param;
	__attribute__((unused)) LX_PE_CCO_DCNT_DETAIL_T c_cco_dtl_param;
	__attribute__((unused)) LX_PE_CCO_DCNT1_DETAIL_T cco_dtl_param;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pDecontourData, return RET_ERROR, "Error. pDecontourData is null.\n");
	wid = wId;
	dcnt_data = (vpq_hwrap_chip_decontour_o26_t *)pDecontourData->pst_chip_data;
	db_mode = _g_vpq_hwrap_dct_platform_db_enable;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (dcnt_data)
	#else
	if (dcnt_data && db_mode)
	#endif
	{
		//nd 0
		c_cmn_param.win_id = c_dtl_param.win_id = c_sqm_param.win_id =  wid;
		c_cmn_param.oper = c_dtl_param.oper = c_sqm_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32*)&cmn_param;
		c_dtl_param.data = (UINT32*)&dtl_param;
		c_sqm_param.data = (UINT32*)&sqm_param;
		c_cmn_param.size = sizeof(LX_PE_NRD_DCNT3_CMN_T);
		c_dtl_param.size = sizeof(LX_PE_NRD_DCNT5_DETAIL_T);
		c_sqm_param.size = sizeof(LX_PE_NRD_DCNT_SQM2_CMN_T);

		cmn_param.deconnd_ui_val = sqm_param.deconnd____val= pDecontourData->ui_value;
		memcpy(&(cmn_param.deconnd_____ui), &(dcnt_data->deconnd0____ui), sizeof(dcnt_data->deconnd0____ui));
		memcpy(&(cmn_param.deconnd___buff), &(dcnt_data->deconnd0__buff), sizeof(dcnt_data->deconnd0__buff));
		memcpy(&(dtl_param.deconnd____cmn), &(dcnt_data->deconnd0___cmn), sizeof(dcnt_data->deconnd0___cmn));
		memcpy(&(dtl_param.deconnd___face), &(dcnt_data->deconnd0__face), sizeof(dcnt_data->deconnd0__face));
		memcpy(&(sqm_param.deconnd__sqmui), &(dcnt_data->deconnd0_sqmui), sizeof(dcnt_data->deconnd0_sqmui));
		cmn_param.win_id = dtl_param.win_id =  sqm_param.win_id = wid;

		ret = PE_NRD_SetDnrDcntCmnCtrl((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDcntDetailCtrl((void *)&c_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntDetailCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDcntSqmCmnCtrl((void *)&c_sqm_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntSqmCmnCtrl(): error %d\n", ret);

		//nd 1
		c_cmn2nd_param.win_id = c_dtl2nd_param.win_id = c_sqm2nd_param.win_id =  wid;
		c_cmn2nd_param.oper = c_dtl2nd_param.oper = c_sqm2nd_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn2nd_param.data = (UINT32*)&cmn2nd_param;
		c_dtl2nd_param.data = (UINT32*)&dtl2nd_param;
		c_sqm2nd_param.data = (UINT32*)&sqm2nd_param;
		c_cmn2nd_param.size = sizeof(LX_PE_NRD_DCNT3_CMN_T);
		c_dtl2nd_param.size = sizeof(LX_PE_NRD_DCNT5_DETAIL_T);
		c_sqm2nd_param.size = sizeof(LX_PE_NRD_DCNT_SQM2_CMN_T);

		cmn2nd_param.deconnd_ui_val = sqm2nd_param.deconnd____val= pDecontourData->ui_value;
		memcpy(&(cmn2nd_param.deconnd_____ui), &(dcnt_data->deconnd1____ui), sizeof(dcnt_data->deconnd1____ui));
		memcpy(&(cmn2nd_param.deconnd___buff), &(dcnt_data->deconnd1__buff), sizeof(dcnt_data->deconnd1__buff));
		memcpy(&(dtl2nd_param.deconnd____cmn), &(dcnt_data->deconnd1___cmn), sizeof(dcnt_data->deconnd1___cmn));
		memcpy(&(dtl2nd_param.deconnd___face), &(dcnt_data->deconnd1__face), sizeof(dcnt_data->deconnd1__face));
		memcpy(&(sqm2nd_param.deconnd__sqmui), &(dcnt_data->deconnd1_sqmui), sizeof(dcnt_data->deconnd1_sqmui));
		cmn2nd_param.win_id = dtl2nd_param.win_id =  sqm2nd_param.win_id = wid;

		ret = PE_NRD_SetDnrDcnt2ndCmnCtrl((void *)&c_cmn2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcnt2ndCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDcnt2ndDetailCtrl((void *)&c_dtl2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcnt2ndDetailCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDcnt2ndSqmCmnCtrl((void *)&c_sqm2nd_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntSqmCmnCtrl(): error %d\n", ret);

		//cco
		c_cco_cmn_param.win_id = c_cco_dtl_param.win_id = c_cco_sqm_param.win_id =  wid;
		c_cco_cmn_param.oper = c_cco_dtl_param.oper = c_cco_sqm_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cco_cmn_param.data = (UINT32*)&cco_cmn_param;
		c_cco_dtl_param.data = (UINT32*)&cco_dtl_param;
		c_cco_sqm_param.data = (UINT32*)&cco_sqm_param;
		c_cco_cmn_param.size = sizeof(LX_PE_CCO_DCNT1_CMN_T);
		c_cco_dtl_param.size = sizeof(LX_PE_CCO_DCNT1_DETAIL_T);
		c_cco_sqm_param.size = sizeof(LX_PE_CCO_DCNT_SQM1_CMN_T);

		cco_cmn_param.deconnd_ui_val = cco_sqm_param.deconnd____val= pDecontourData->ui_value;
		memcpy(&(cco_cmn_param.deconcco____ui), &(dcnt_data->deconcco____ui), sizeof(dcnt_data->deconcco____ui));
		memcpy(&(cco_cmn_param.deconcco__buff), &(dcnt_data->deconcco__buff), sizeof(dcnt_data->deconcco__buff));
		memcpy(&(cco_dtl_param.deconcco___cmn), &(dcnt_data->deconcco___cmn), sizeof(dcnt_data->deconcco___cmn));
		memcpy(&(cco_dtl_param.deconcco__face), &(dcnt_data->deconcco__face), sizeof(dcnt_data->deconcco__face));
		memcpy(&(cco_sqm_param.deconcco_sqmui), &(dcnt_data->deconcco_sqmui), sizeof(dcnt_data->deconcco_sqmui));
		cco_cmn_param.win_id = cco_dtl_param.win_id = cco_sqm_param.win_id = wid;

		ret = PE_NRD_SetLedDcntCmnCtrl((void *)&c_cco_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetLedDcntDetailCtrl((void *)&c_cco_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntDetailCtrl(): error %d\n", ret);
		ret = PE_NRD_SetLedDcntSqmCmnCtrl((void *)&c_cco_sqm_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntSqmCmnCtrl(): error %d\n", ret);

		PQ_PRINT_DEC("\n=========== drv param===============\n");
		/*nd 0*/
		pd32 = cmn_param.deconnd_____ui;
		PQ_PRINT_DEC("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
		pd32 = cmn_param.deconnd___buff;
		PQ_PRINT_DEC("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (dtl_param.deconnd____cmn);
		PQ_PRINT_DEC(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [70]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62], pd16[63], pd16[64], pd16[65], pd16[66], pd16[67], pd16[68], pd16[69],\
		pd16[70], pd16[71], pd16[72], pd16[73], pd16[74], pd16[75]);
		pd = (dtl_param.deconnd___face);
		PQ_PRINT_DEC(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X \n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
		pd32 = (sqm_param.deconnd__sqmui);
		PQ_PRINT_DEC(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13],  pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23],  pd32[24],  pd32[25],  pd32[26]);

		
		/*nd 1*/
		pd32 = cmn2nd_param.deconnd_____ui;
		PQ_PRINT_DEC("2nd deconnd_____ui\n"
		"2nd deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
		pd32 = cmn2nd_param.deconnd___buff;
		PQ_PRINT_DEC("2nd deconnd___buff\n"\
		"2nd deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (dtl2nd_param.deconnd____cmn);
		PQ_PRINT_DEC("2nd deconnd____cmn\n"
		"2nd deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd____cmn    [70]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62], pd16[63], pd16[64], pd16[65], pd16[66], pd16[67], pd16[68], pd16[69],\
		pd16[70], pd16[71], pd16[72], pd16[73], pd16[74], pd16[75]);
		pd = (dtl2nd_param.deconnd___face);
		PQ_PRINT_DEC("2nd deconnd___face\n"
		"2nd deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"2nd deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X \n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
		pd32 = (sqm2nd_param.deconnd__sqmui);
		PQ_PRINT_DEC("2nd deconnd__sqmui\n"
		"2nd deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"2nd deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"2nd deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13],  pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23],  pd32[24],  pd32[25],  pd32[26]);

		//cco
		pd32 = cco_cmn_param.deconcco____ui;
		PQ_PRINT_DEC("deconcco____ui\n"
		"deconcco____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco____ui    [20]0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19],\
		pd32[20], pd32[21]);
		pd32 = cco_cmn_param.deconcco__buff;
		PQ_PRINT_DEC("deconcco__buff\n"\
		"deconcco__buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (cco_dtl_param.deconcco___cmn);
		PQ_PRINT_DEC(" deconcco___cmn\n"
		"deconcco___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco___cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco___cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco___cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco___cmn    [50]0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50]);
		pd = (cco_dtl_param.deconcco__face);
		PQ_PRINT_DEC(" deconcco__face\n"
		"deconcco__face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco__face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
		pd32 = (cco_sqm_param.deconcco_sqmui);
		PQ_PRINT_DEC(" deconcco_sqmui\n"
		"deconcco_sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconcco_sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconcco_sqmui[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconcco_sqmui[30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13],  pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23],  pd32[24],  pd32[25],  pd32[26],  pd32[27], pd32[28],  pd32[29],\
		pd32[30],  pd32[31],  pd32[32],  pd32[33],  pd32[34]);
	}
	else
	{
		dbtype = LX_PE_PLATFORM_NUM;
		ctrl.wid = LX_PE_WIN_0;
		ctrl.data = (UINT32)pDecontourData->ui_value;
		ctrl.st_data = (void *)&dbtype;
		{
			UINT32 param_data = 0;
			LX_PE_NRD_DCNT_CMN_T pstParam;
			LX_PE_NRD_EASY_DCNT_CMN_T ctrl;
			param_data = (pDecontourData->ui_value<VPQ_HWRAP_NRD_NUM)? \
				pDecontourData->ui_value:VPQ_HWRAP_NRD_OFF;
			memcpy(&ctrl, &(g_pe_hwrap_p_easy_dcnt_cmn[param_data]), sizeof(LX_PE_NRD_EASY_DCNT_CMN_T));
			pd16 = (ctrl.data);
			PQ_PRINT_DEC(" deconled___cmn\n"
			"decon eay db    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"decon eay db    [10]0x%02X,0x%02X\n",\
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
			pd16[10], pd16[11]);
			pstParam.win_id = ctrl.win_id;
			pstParam.oper = dbtype;
			pstParam.size = sizeof(LX_PE_NRD_EASY_DCNT_CMN_T);
			pstParam.data = (UINT32*)&ctrl;
			ret = PE_NRD_SetDnrDcntCmnCtrl(&pstParam);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDnrDcntCmnBspDB(): error %d\n", ret);
		}
	}

	return ret;
}

static int vpq_hwrap_setdecontour_o24(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	__attribute__((unused)) vpq_hwrap_chip_decontour_o24_t *dcnt_data;
	__attribute__((unused)) PE_KWRAP_CTRL_T ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) LX_PE_NRD_DCNT_CMN_T c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT3_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM_CMN_T c_sqm_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM2_CMN_T sqm_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_DETAIL_T c_dtl_param;
	__attribute__((unused)) LX_PE_NRD_DCNT5_DETAIL_T dtl_param;
	__attribute__((unused)) LX_PE_CCO_DCNT_CMN_T c_cco_cmn_param;
	__attribute__((unused)) LX_PE_CCO_DCNT1_CMN_T cco_cmn_param;
	__attribute__((unused)) LX_PE_CCO_DCNT_SQM_CMN_T c_cco_sqm_param;
	__attribute__((unused)) LX_PE_CCO_DCNT_SQM1_CMN_T cco_sqm_param;
	__attribute__((unused)) LX_PE_CCO_DCNT_DETAIL_T c_cco_dtl_param;
	__attribute__((unused)) LX_PE_CCO_DCNT1_DETAIL_T cco_dtl_param;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pDecontourData, return RET_ERROR, "Error. pDecontourData is null.\n");
	wid = wId;
	dcnt_data = (vpq_hwrap_chip_decontour_o24_t *)pDecontourData->pst_chip_data;
	db_mode = _g_vpq_hwrap_dct_platform_db_enable;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (dcnt_data)
	#else
	if (dcnt_data && db_mode)
	#endif
	{
		//nrd
		c_cmn_param.win_id = c_dtl_param.win_id = wid;
		c_sqm_param.win_id =  wid;
		c_cmn_param.oper = c_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32*)&cmn_param;
		c_dtl_param.data = (UINT32*)&dtl_param;
		c_sqm_param.data = (UINT32*)&sqm_param;
		c_cmn_param.size = sizeof(LX_PE_NRD_DCNT3_CMN_T);
		c_dtl_param.size = sizeof(LX_PE_NRD_DCNT5_DETAIL_T);
		c_sqm_param.size = sizeof(LX_PE_NRD_DCNT_SQM2_CMN_T);

		cmn_param.deconnd_ui_val = sqm_param.deconnd____val= pDecontourData->ui_value;
		memcpy(&(cmn_param.deconnd_____ui), &(dcnt_data->deconnd_____ui), sizeof(dcnt_data->deconnd_____ui));
		memcpy(&(cmn_param.deconnd___buff), &(dcnt_data->deconnd___buff), sizeof(dcnt_data->deconnd___buff));
		memcpy(&(dtl_param.deconnd____cmn), &(dcnt_data->deconnd____cmn), sizeof(dcnt_data->deconnd____cmn));
		memcpy(&(dtl_param.deconnd___face), &(dcnt_data->deconnd___face), sizeof(dcnt_data->deconnd___face));
		memcpy(&(sqm_param.deconnd__sqmui), &(dcnt_data->deconnd__sqmui), sizeof(dcnt_data->deconnd__sqmui));
		cmn_param.win_id = dtl_param.win_id =  wid;
		sqm_param.win_id = wid;

		ret = PE_NRD_SetDnrDcntCmnCtrl((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDcntDetailCtrl((void *)&c_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntDetailCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDcntSqmCmnCtrl((void *)&c_sqm_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntSqmCmnCtrl(): error %d\n", ret);


		//cco
		c_cco_cmn_param.win_id = c_cco_dtl_param.win_id = wid;
		c_cco_sqm_param.win_id =  wid;
		c_cco_cmn_param.oper = c_cco_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cco_sqm_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cco_cmn_param.data = (UINT32*)&cco_cmn_param;
		c_cco_dtl_param.data = (UINT32*)&cco_dtl_param;
		c_cco_sqm_param.data = (UINT32*)&cco_sqm_param;
		c_cco_cmn_param.size = sizeof(LX_PE_CCO_DCNT1_CMN_T);
		c_cco_dtl_param.size = sizeof(LX_PE_CCO_DCNT1_DETAIL_T);
		c_cco_sqm_param.size = sizeof(LX_PE_CCO_DCNT_SQM1_CMN_T);

		cco_cmn_param.deconnd_ui_val = cco_sqm_param.deconnd____val= pDecontourData->ui_value;
		memcpy(&(cco_cmn_param.deconcco____ui), &(dcnt_data->deconcco____ui), sizeof(dcnt_data->deconcco____ui));
		memcpy(&(cco_cmn_param.deconcco__buff), &(dcnt_data->deconcco__buff), sizeof(dcnt_data->deconcco__buff));
		memcpy(&(cco_dtl_param.deconcco___cmn), &(dcnt_data->deconcco___cmn), sizeof(dcnt_data->deconcco___cmn));
		memcpy(&(cco_dtl_param.deconcco__face), &(dcnt_data->deconcco__face), sizeof(dcnt_data->deconcco__face));
		memcpy(&(cco_sqm_param.deconcco_sqmui), &(dcnt_data->deconcco_sqmui), sizeof(dcnt_data->deconcco_sqmui));
		cco_cmn_param.win_id = cco_dtl_param.win_id =  wid;
		cco_sqm_param.win_id = wid;

		ret = PE_NRD_SetLedDcntCmnCtrl((void *)&c_cco_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetLedDcntDetailCtrl((void *)&c_cco_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntDetailCtrl(): error %d\n", ret);
		ret = PE_NRD_SetLedDcntSqmCmnCtrl((void *)&c_cco_sqm_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntSqmCmnCtrl(): error %d\n", ret);

		PE_PRINT_NRD("\n=========== drv param===============\n");
		/*dnr*/
		pd32 = cmn_param.deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
		pd32 = cmn_param.deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (dtl_param.deconnd____cmn);
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [70]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62], pd16[63], pd16[64], pd16[65], pd16[66], pd16[67], pd16[68], pd16[69],\
		pd16[70], pd16[71], pd16[72], pd16[73], pd16[74], pd16[75]);
		pd = (dtl_param.deconnd___face);
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X \n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
		pd32 = (sqm_param.deconnd__sqmui);
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13],  pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23],  pd32[24],  pd32[25],  pd32[26]);

		
		pd32 = cco_cmn_param.deconcco____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [20]0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19],\
		pd32[20], pd32[21]);
		pd32 = cco_cmn_param.deconcco__buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (cco_dtl_param.deconcco___cmn);
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50]);
		pd = (cco_dtl_param.deconcco__face);
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
		pd32 = (cco_sqm_param.deconcco_sqmui);
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd__sqmui[30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13],  pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23],  pd32[24],  pd32[25],  pd32[26],  pd32[27], pd32[28],  pd32[29],\
		pd32[30],  pd32[31],  pd32[32],  pd32[33],  pd32[34]);
		#if 0
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		/*dnr*/
		pd32 = dcnt_data->deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
		pd32 = dcnt_data->deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = dcnt_data->deconnd____cmn;
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [70]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62], pd16[63], pd16[64], pd16[65], pd16[66], pd16[67], pd16[68], pd16[69],\
		pd16[70], pd16[71], pd16[72], pd16[73], pd16[74], pd16[75]);
		pd = dcnt_data->deconnd___face;
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [30]0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31]);
		pd32 = sqm_param.deconnd__sqmui;
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13],	pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22],  pd32[23],	pd32[24],  pd32[25],  pd32[26]);
		#endif
	}
	else
	{
		dbtype = LX_PE_PLATFORM_NUM;
		ctrl.wid = LX_PE_WIN_0;
		ctrl.data = (UINT32)pDecontourData->ui_value;
		ctrl.st_data = (void *)&dbtype;
		{
			UINT32 param_data = 0;
			LX_PE_NRD_DCNT_CMN_T pstParam;
			LX_PE_NRD_EASY_DCNT_CMN_T ctrl;
			param_data = (pDecontourData->ui_value<VPQ_HWRAP_NRD_NUM)? \
				pDecontourData->ui_value:VPQ_HWRAP_NRD_OFF;
			memcpy(&ctrl, &(g_pe_hwrap_p_easy_dcnt_cmn[param_data]), sizeof(LX_PE_NRD_EASY_DCNT_CMN_T));
			pd16 = (ctrl.data);
			PE_PRINT_NRD(" deconled___cmn\n"
			"decon eay db    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"decon eay db    [10]0x%02X,0x%02X\n",\
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
			pd16[10], pd16[11]);
			pstParam.win_id = ctrl.win_id;
			pstParam.oper = dbtype;
			pstParam.size = sizeof(LX_PE_NRD_EASY_DCNT_CMN_T);
			pstParam.data = (UINT32*)&ctrl;
			ret = PE_NRD_SetDnrDcntCmnCtrl(&pstParam);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDnrDcntCmnBspDB(): error %d\n", ret);
		}
	}

	return ret;
}

static int vpq_hwrap_setdecontour_o20_e60(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	//UINT16 *pd16;//warning: unused variable
	//UINT32 *pd32;//warning: unused variable
	__attribute__((unused)) vpq_hwrap_chip_decontour_o20_f20_e60_t *dcnt_data;
	__attribute__((unused)) PE_KWRAP_CTRL_T ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) LX_PE_NRD_DCNT_CMN_T c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT2_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM_CMN_T c_sqm_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM1_CMN_T sqm_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_DETAIL_T c_dtl_param;
	__attribute__((unused)) LX_PE_NRD_DCNT3_DETAIL_T dtl_param;
	__attribute__((unused)) LX_PE_LED_DCNT_CMN_T c_led_cmn_param;
	__attribute__((unused)) LX_PE_LED_DCNT2_CMN_T led_cmn_param;
	__attribute__((unused)) LX_PE_LED_DCNT_DETAIL_T c_led_dtl_param;
	__attribute__((unused)) LX_PE_LED_DCNT2_DETAIL_T led_dtl_param;
	__attribute__((unused)) LX_PE_LED_DCNT_SQM_CMN_T c_led_sqm_param;
	__attribute__((unused)) LX_PE_LED_DCNT_SQM1_CMN_T led_sqm_param;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pDecontourData, return RET_ERROR, "Error. pDecontourData is null.\n");
	wid = wId;
	dcnt_data = (vpq_hwrap_chip_decontour_o20_f20_e60_t *)pDecontourData->pst_chip_data;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (dcnt_data)
	#else
	if (dcnt_data)
	#endif
	{
		c_cmn_param.win_id = c_led_cmn_param.win_id = c_dtl_param.win_id = c_led_dtl_param.win_id = wid;
		c_sqm_param.win_id = c_led_sqm_param.win_id= wid;
		c_cmn_param.oper = c_led_cmn_param.oper = c_dtl_param.oper = c_led_dtl_param.oper= LX_PE_PLATFORM_WEBOS;
		c_sqm_param.oper = c_led_sqm_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32*)&cmn_param;
		c_led_cmn_param.data = (UINT32*)&led_cmn_param;
		c_dtl_param.data = (UINT32*)&dtl_param;
		c_led_dtl_param.data = (UINT32*)&led_dtl_param;
		c_sqm_param.data = (UINT32*)&sqm_param;
		c_led_sqm_param.data = (UINT32*)&led_sqm_param;
		c_cmn_param.size = sizeof(LX_PE_NRD_DCNT2_CMN_T);
		c_led_cmn_param.size = sizeof(LX_PE_LED_DCNT2_CMN_T);
		c_dtl_param.size = sizeof(LX_PE_NRD_DCNT3_DETAIL_T);
		c_led_dtl_param.size = sizeof(LX_PE_LED_DCNT2_DETAIL_T);
		c_sqm_param.size = sizeof(LX_PE_NRD_DCNT_SQM1_CMN_T);
		c_led_sqm_param.size = sizeof(LX_PE_LED_DCNT_SQM1_CMN_T);
		cmn_param.deconnd_ui_val = sqm_param.deconnd____val= pDecontourData->ui_value;
		memcpy(&(cmn_param.deconnd_____ui), &(dcnt_data->deconnd_____ui), sizeof(dcnt_data->deconnd_____ui));
		memcpy(&(cmn_param.deconnd___buff), &(dcnt_data->deconnd___buff), sizeof(dcnt_data->deconnd___buff));
		memcpy(&(dtl_param.deconnd____cmn), &(dcnt_data->deconnd____cmn), sizeof(dcnt_data->deconnd____cmn));
		memcpy(&(dtl_param.deconnd___face), &(dcnt_data->deconnd___face), sizeof(dcnt_data->deconnd___face));
		memcpy(&(sqm_param.deconnd__sqmui), &(dcnt_data->deconnd__sqmui), sizeof(dcnt_data->deconnd__sqmui));
		led_cmn_param.deconledui_val = led_sqm_param.deconled___val = pDecontourData->ui_value;
		memcpy(&(led_cmn_param.deconled____ui), &(dcnt_data->deconled____ui), sizeof(dcnt_data->deconled____ui));
		memcpy(&(led_cmn_param.deconled__buff), &(dcnt_data->deconled__buff), sizeof(dcnt_data->deconled__buff));
		memcpy(&(led_dtl_param.deconled___cmn), &(dcnt_data->deconled___cmn), sizeof(dcnt_data->deconled___cmn));
		memcpy(&(led_dtl_param.deconled__face), &(dcnt_data->deconled__face), sizeof(dcnt_data->deconled__face));
		memcpy(&(led_sqm_param.deconled_sqmui), &(dcnt_data->deconled_sqmui), sizeof(dcnt_data->deconled_sqmui));
		cmn_param.win_id = dtl_param.win_id = led_dtl_param.win_id = led_cmn_param.win_id = wid;
		sqm_param.win_id = led_sqm_param.win_id= wid;
		if(PE_KDRV_VER_O20)
		{
			ret = KWRAP_PE_SetDnrDcntCmnParam((void *)&c_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntCmnCtrl(): error %d\n", ret);
			ret = KWRAP_PE_SetDnrDcntDetailParam((void *)&c_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntDetailCtrl(): error %d\n", ret);
			ret = KWRAP_PE_SetDnrDcntSqmCmnParam((void *)&c_sqm_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntSqmCmnCtrl(): error %d\n", ret);
		}
		else
		{
			ret = PE_NRD_SetDnrDcntCmnCtrl((void *)&c_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntCmnCtrl(): error %d\n", ret);
			ret = PE_NRD_SetDnrDcntDetailCtrl((void *)&c_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntDetailCtrl(): error %d\n", ret);
			ret = PE_NRD_SetDnrDcntSqmCmnCtrl((void *)&c_sqm_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntSqmCmnCtrl(): error %d\n", ret);
		}
		#if 0
		PE_PRINT_NRD("\n=========== drv param===============\n");
		/*dnr*/
		pd32 = cmn_param.deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = cmn_param.deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (dtl_param.deconnd____cmn);
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62]);
		pd = (dtl_param.deconnd___face);
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (sqm_param.deconnd__sqmui);
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		/*led*/
		pd32 = led_cmn_param.deconled____ui;
		PE_PRINT_NRD("deconled____ui\n"
		"deconled____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = led_cmn_param.deconled__buff;
		PE_PRINT_NRD("deconled__buff\n"\
		"deconled__buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (led_dtl_param.deconled___cmn);
		PE_PRINT_NRD(" deconled___cmn\n"
		"deconled___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62]);
		pd = (led_dtl_param.deconled__face);
		PE_PRINT_NRD(" deconled__face\n"
		"deconled__face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (led_sqm_param.deconled_sqmui);
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		#endif
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		/*dnr*/
		pd32 = dcnt_data->deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = dcnt_data->deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = dcnt_data->deconnd____cmn;
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62]);
		pd = dcnt_data->deconnd___face;
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = sqm_param.deconnd__sqmui;
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		/*led*/
		pd32 = dcnt_data->deconled____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = dcnt_data->deconled__buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = dcnt_data->deconled___cmn;
		PE_PRINT_NRD(" deconled___cmn\n"
		"deconled___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62]);
		pd = dcnt_data->deconled__face;
		PE_PRINT_NRD(" deconled__face\n"
		"deconled__face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = dcnt_data->deconled_sqmui;
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		if(PE_KDRV_VER_O20)
		{
			ret = KWRAP_PE_SetLedDcntCmnParam((void *)&c_led_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetLedDcntCmnParam(): error %d\n", ret);
			ret = KWRAP_PE_SetLedDcntDetailParam((void *)&c_led_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetLedDcntDetailParam(): error %d\n", ret);
			ret = KWRAP_PE_SetLedDcntSqmCmnParam((void *)&c_led_sqm_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetLedDcntSqmCmnParam(): error %d\n", ret);
		}
		else
		{
			ret = PE_NRD_SetLedDcntCmnCtrl((void *)&c_led_cmn_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntCmnCtrl(): error %d\n", ret);
			ret = PE_NRD_SetLedDcntDetailCtrl((void *)&c_led_dtl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntDetailCtrl(): error %d\n", ret);
			ret = PE_NRD_SetLedDcntSqmCmnCtrl((void *)&c_led_sqm_param);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetLedDcntSqmCmnCtrl(): error %d\n", ret);
		}
	}
	else
	{
		dbtype = LX_PE_PLATFORM_NUM;
		ctrl.wid = LX_PE_WIN_0;
		ctrl.data = (UINT32)pDecontourData->ui_value;
		ctrl.st_data = (void *)&dbtype;
		{
			UINT32 param_data = 0;
			LX_PE_NRD_DCNT_CMN_T pstParam;
			LX_PE_NRD_EASY_DCNT_CMN_T ctrl;
			param_data = (pDecontourData->ui_value<VPQ_HWRAP_NRD_NUM)? \
				pDecontourData->ui_value:VPQ_HWRAP_NRD_OFF;
			memcpy(&ctrl, &(g_pe_hwrap_p_easy_dcnt_cmn[param_data]), sizeof(LX_PE_NRD_EASY_DCNT_CMN_T));
			pd16 = (ctrl.data);
			PE_PRINT_NRD(" deconled___cmn\n"
			"decon eay db    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"decon eay db    [10]0x%02X,0x%02X\n",\
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
			pd16[10], pd16[11]);
			pstParam.win_id = ctrl.win_id;
			pstParam.oper = dbtype;
			pstParam.size = sizeof(LX_PE_NRD_EASY_DCNT_CMN_T);
			pstParam.data = (UINT32*)&ctrl;
			ret = PE_NRD_SetDnrDcntCmnCtrl(&pstParam);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDnrDcntCmnBspDB(): error %d\n", ret);
		}
	}

	return ret;
}
static int vpq_hwrap_setdecontour_o22(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	//UINT16 *pd16;//warning: unused variable
	//UINT32 *pd32;//warning: unused variable
	__attribute__((unused)) vpq_hwrap_chip_decontour_o22_f22_t *dcnt_data;
	__attribute__((unused)) PE_KWRAP_CTRL_T ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) LX_PE_NRD_DCNT_CMN_T c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT3_CMN_T cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM_CMN_T c_sqm_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_SQM1_CMN_T sqm_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_DETAIL_T c_dtl_param;
	__attribute__((unused)) LX_PE_NRD_DCNT4_DETAIL_T dtl_param;
	
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pDecontourData, return RET_ERROR, "Error. pDecontourData is null.\n");
	wid = wId;
	dcnt_data = (vpq_hwrap_chip_decontour_o22_f22_t *)pDecontourData->pst_chip_data;
	db_mode = _g_vpq_hwrap_dct_platform_db_enable;
	if (PE_KDRV_VER_O22||PE_KDRV_VER_M23)
		db_mode = 1;
	#ifdef VPQ_HWRAP_EXTERNEL_CHIP_TEST_MODE
	if (dcnt_data)
	#else
	if (dcnt_data && db_mode)
	#endif
	{
		c_cmn_param.win_id = c_dtl_param.win_id = wid;
		c_sqm_param.win_id =  wid;
		c_cmn_param.oper = c_dtl_param.oper = LX_PE_PLATFORM_WEBOS;
		c_sqm_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32*)&cmn_param;
		c_dtl_param.data = (UINT32*)&dtl_param;
		c_sqm_param.data = (UINT32*)&sqm_param;
		c_cmn_param.size = sizeof(LX_PE_NRD_DCNT3_CMN_T);
		c_dtl_param.size = sizeof(LX_PE_NRD_DCNT4_DETAIL_T);
		c_sqm_param.size = sizeof(LX_PE_NRD_DCNT_SQM1_CMN_T);
		cmn_param.deconnd_ui_val = sqm_param.deconnd____val= pDecontourData->ui_value;
		memcpy(&(cmn_param.deconnd_____ui), &(dcnt_data->deconnd_____ui), sizeof(dcnt_data->deconnd_____ui));
		memcpy(&(cmn_param.deconnd___buff), &(dcnt_data->deconnd___buff), sizeof(dcnt_data->deconnd___buff));
		memcpy(&(dtl_param.deconnd____cmn), &(dcnt_data->deconnd____cmn), sizeof(dcnt_data->deconnd____cmn));
		memcpy(&(dtl_param.deconnd___face), &(dcnt_data->deconnd___face), sizeof(dcnt_data->deconnd___face));
		memcpy(&(sqm_param.deconnd__sqmui), &(dcnt_data->deconnd__sqmui), sizeof(dcnt_data->deconnd__sqmui));
		cmn_param.win_id = dtl_param.win_id =  wid;
		sqm_param.win_id = wid;

		ret = PE_NRD_SetDnrDcntCmnCtrl((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntCmnCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDcntDetailCtrl((void *)&c_dtl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntDetailCtrl(): error %d\n", ret);
		ret = PE_NRD_SetDnrDcntSqmCmnCtrl((void *)&c_sqm_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntSqmCmnCtrl(): error %d\n", ret);

		PE_PRINT_NRD("\n=========== drv param===============\n");
		/*dnr*/
		pd32 = cmn_param.deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
		pd32 = cmn_param.deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (dtl_param.deconnd____cmn);
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [70]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62], pd16[63], pd16[64], pd16[65], pd16[66], pd16[67], pd16[68], pd16[69],\
		pd16[70], pd16[71], pd16[72], pd16[73], pd16[74], pd16[75]);
		pd = (dtl_param.deconnd___face);
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [30]0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31]);
		pd32 = (sqm_param.deconnd__sqmui);
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		/*dnr*/
		pd32 = dcnt_data->deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
		pd32 = dcnt_data->deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = dcnt_data->deconnd____cmn;
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [70]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62], pd16[63], pd16[64], pd16[65], pd16[66], pd16[67], pd16[68], pd16[69],\
		pd16[70], pd16[71], pd16[72], pd16[73], pd16[74], pd16[75]);
		pd = dcnt_data->deconnd___face;
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [30]0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31]);
		pd32 = sqm_param.deconnd__sqmui;
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
	}
	else
	{
		dbtype = LX_PE_PLATFORM_NUM;
		ctrl.wid = LX_PE_WIN_0;
		ctrl.data = (UINT32)pDecontourData->ui_value;
		ctrl.st_data = (void *)&dbtype;
		{
			UINT32 param_data = 0;
			LX_PE_NRD_DCNT_CMN_T pstParam;
			LX_PE_NRD_EASY_DCNT_CMN_T ctrl;
			param_data = (pDecontourData->ui_value<VPQ_HWRAP_NRD_NUM)? \
				pDecontourData->ui_value:VPQ_HWRAP_NRD_OFF;
			memcpy(&ctrl, &(g_pe_hwrap_p_easy_dcnt_cmn[param_data]), sizeof(LX_PE_NRD_EASY_DCNT_CMN_T));
			pd16 = (ctrl.data);
			PE_PRINT_NRD(" deconled___cmn\n"
			"decon eay db    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"decon eay db    [10]0x%02X,0x%02X\n",\
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
			pd16[10], pd16[11]);
			pstParam.win_id = ctrl.win_id;
			pstParam.oper = dbtype;
			pstParam.size = sizeof(LX_PE_NRD_EASY_DCNT_CMN_T);
			pstParam.data = (UINT32*)&ctrl;
			ret = PE_NRD_SetDnrDcntCmnCtrl(&pstParam);
			VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDnrDcntCmnBspDB(): error %d\n", ret);
		}
	}

	return ret;
}
static int vpq_hwrap_setdecontour_f22(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	//UINT16 *pd16;//warning: unused variable
	//UINT32 *pd32;//warning: unused variable
	__attribute__((unused)) vpq_hwrap_chip_decontour_o22_f22_t *dcnt_data;
	__attribute__((unused)) PE_KWRAP_CTRL_T ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) LX_PE_NRD_DCNT_CMN_T c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT1_ALL_CMN_T cmn_param;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pDecontourData, return RET_ERROR, "Error. pDecontourData is null.\n");
	wid = wId;
	dcnt_data = (vpq_hwrap_chip_decontour_o22_f22_t *)pDecontourData->pst_chip_data;
	db_mode = _g_vpq_hwrap_dct_platform_db_enable;
	if (dcnt_data)
	{
		c_cmn_param.win_id = wid;
		c_cmn_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32*)&cmn_param;
		c_cmn_param.size = sizeof(LX_PE_NRD_DCNT1_ALL_CMN_T);
		cmn_param.deconnd_ui_val = pDecontourData->ui_value;
		memcpy(&(cmn_param.deconnd_____ui), &(dcnt_data->deconnd_____ui), sizeof(dcnt_data->deconnd_____ui));
		memcpy(&(cmn_param.deconnd___buff), &(dcnt_data->deconnd___buff), sizeof(dcnt_data->deconnd___buff));
		memcpy(&(cmn_param.deconnd____cmn), &(dcnt_data->deconnd____cmn), sizeof(dcnt_data->deconnd____cmn));
		memcpy(&(cmn_param.deconnd___face), &(dcnt_data->deconnd___face), sizeof(dcnt_data->deconnd___face));
		memcpy(&(cmn_param.deconnd__sqmui), &(dcnt_data->deconnd__sqmui), sizeof(dcnt_data->deconnd__sqmui));
		cmn_param.win_id = wid;
		#if 0
		PE_PRINT_NRD("\n=========== drv param===============\n");
		/*dnr*/
		pd32 = cmn_param.deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
		pd32 = cmn_param.deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (cmn_param.deconnd____cmn);
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62], pd16[63], pd16[64], pd16[65], pd16[66], pd16[67], pd16[68], pd16[69],\
		pd16[70], pd16[71], pd16[72], pd16[73], pd16[74], pd16[75], pd16[76]);
		pd = (cmn_param.deconnd___face);
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [30]0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31]);
		pd32 = (cmn_param.deconnd__sqmui);
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		#endif
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		/*dnr*/
		pd32 = dcnt_data->deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13]);
		pd32 = dcnt_data->deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = dcnt_data->deconnd____cmn;
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62], pd16[63], pd16[64], pd16[65], pd16[66], pd16[67], pd16[68], pd16[69],\
		pd16[70], pd16[71], pd16[72], pd16[73], pd16[74], pd16[75], pd16[76]);
		pd = dcnt_data->deconnd___face;
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [30]0x%02X,0x%02X\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
		pd[30], pd[31]);
		pd32 = dcnt_data->deconnd__sqmui;
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		ret = PE_NRD_SetDnrDcntCmnAllCtrl((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "PE_NRD_SetDnrDcntCmnAllCtrl(): error %d\n", ret);
	}
	return ret;
}

static int vpq_hwrap_setdecontour_f20(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) LX_PE_WIN_ID wid;
	__attribute__((unused)) UINT32 db_mode = 0;
	//UINT16 *pd16;//warning: unused variable
	//UINT32 *pd32;//warning: unused variable
	__attribute__((unused)) vpq_hwrap_chip_decontour_o20_f20_e60_t *dcnt_data;
	__attribute__((unused)) PE_KWRAP_CTRL_T ctrl;
	__attribute__((unused)) LX_PE_DBTYPE dbtype;
	__attribute__((unused)) LX_PE_NRD_DCNT_CMN_T c_cmn_param;
	__attribute__((unused)) LX_PE_NRD_DCNT_ALL_CMN_T cmn_param;
	__attribute__((unused)) UINT8 *pd = NULL;
	__attribute__((unused)) UINT16 *pd16 = NULL;
	__attribute__((unused)) UINT32 *pd32 = NULL;

	VPQ_HWRAP_CHECK_CODE(!pDecontourData, return RET_ERROR, "Error. pDecontourData is null.\n");
	wid = wId;
	dcnt_data = (vpq_hwrap_chip_decontour_o20_f20_e60_t *)pDecontourData->pst_chip_data;
	db_mode = _g_vpq_hwrap_dct_platform_db_enable;
	if (dcnt_data)
	{
		c_cmn_param.win_id = wid;
		c_cmn_param.oper = LX_PE_PLATFORM_WEBOS;
		c_cmn_param.data = (UINT32*)&cmn_param;
		
		c_cmn_param.size = sizeof(LX_PE_NRD_DCNT_ALL_CMN_T);
		cmn_param.deconnd_ui_val = pDecontourData->ui_value;
		memcpy(&(cmn_param.deconnd_____ui), &(dcnt_data->deconnd_____ui), sizeof(dcnt_data->deconnd_____ui));
		memcpy(&(cmn_param.deconnd___buff), &(dcnt_data->deconnd___buff), sizeof(dcnt_data->deconnd___buff));
		memcpy(&(cmn_param.deconnd____cmn), &(dcnt_data->deconnd____cmn), sizeof(dcnt_data->deconnd____cmn));
		memcpy(&(cmn_param.deconnd___face), &(dcnt_data->deconnd___face), sizeof(dcnt_data->deconnd___face));
		memcpy(&(cmn_param.deconnd__sqmui), &(dcnt_data->deconnd__sqmui), sizeof(dcnt_data->deconnd__sqmui));
		memcpy(&(cmn_param.deconled____ui), &(dcnt_data->deconled____ui), sizeof(dcnt_data->deconled____ui));
		memcpy(&(cmn_param.deconled__buff), &(dcnt_data->deconled__buff), sizeof(dcnt_data->deconled__buff));
		memcpy(&(cmn_param.deconled___cmn), &(dcnt_data->deconled___cmn), sizeof(dcnt_data->deconled___cmn));
		memcpy(&(cmn_param.deconled__face), &(dcnt_data->deconled__face), sizeof(dcnt_data->deconled__face));
		memcpy(&(cmn_param.deconled_sqmui), &(dcnt_data->deconled_sqmui), sizeof(dcnt_data->deconled_sqmui));
		cmn_param.win_id = wid;
		#if 0
		PE_PRINT_NRD("\n=========== drv param===============\n");
		/*dnr*/
		pd32 = cmn_param.deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = cmn_param.deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (cmn_param.deconnd____cmn);
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62]);
		pd = (cmn_param.deconnd___face);
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (cmn_param.deconnd__sqmui);
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		/*led*/
		pd32 = cmn_param.deconled____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = cmn_param.deconled__buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = (cmn_param.deconled___cmn);
		PE_PRINT_NRD(" deconled___cmn\n"
		"deconled___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62]);
		pd = (cmn_param.deconled__face);
		PE_PRINT_NRD(" deconled__face\n"
		"deconled__face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = (cmn_param.deconled_sqmui);
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		#endif
		PE_PRINT_NRD("\n=========== pltf param===============\n");
		/*dnr*/
		pd32 = dcnt_data->deconnd_____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = dcnt_data->deconnd___buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = dcnt_data->deconnd____cmn;
		PE_PRINT_NRD(" deconnd____cmn\n"
		"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62]);
		pd = dcnt_data->deconnd___face;
		PE_PRINT_NRD(" deconnd___face\n"
		"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = dcnt_data->deconnd__sqmui;
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);
		/*led*/
		pd32 = dcnt_data->deconled____ui;
		PE_PRINT_NRD("deconnd_____ui\n"
		"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
		pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
		pd32 = dcnt_data->deconled__buff;
		PE_PRINT_NRD("deconnd___buff\n"\
		"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		pd16 = dcnt_data->deconled___cmn;
		PE_PRINT_NRD(" deconled___cmn\n"
		"deconled___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled___cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
		pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
		pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
		pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
		pd16[30], pd16[31], pd16[32], pd16[33], pd16[34], pd16[35], pd16[36], pd16[37], pd16[38], pd16[39],\
		pd16[40], pd16[41], pd16[42], pd16[43], pd16[44], pd16[45], pd16[46], pd16[47], pd16[48], pd16[49],\
		pd16[50], pd16[51], pd16[52], pd16[53], pd16[54], pd16[55], pd16[56], pd16[57], pd16[58], pd16[59],\
		pd16[60], pd16[61], pd16[62]);
		pd = dcnt_data->deconled__face;
		PE_PRINT_NRD(" deconled__face\n"
		"deconled__face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"deconled__face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
		pd[20], pd[21], pd[22], pd[23]);
		pd32 = dcnt_data->deconnd__sqmui;
		PE_PRINT_NRD(" deconnd__sqmui\n"
		"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
		"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
		pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
		pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
		pd32[20],  pd32[21],  pd32[22]);

		ret = KWRAP_PE_SetDnrDcntCmnAllParam((void *)&c_cmn_param);
		VPQ_HWRAP_CHECK_CODE(ret, return RET_ERROR, "KWRAP_PE_SetDnrDcntCmnParam(): error %d\n", ret);
	}
	return ret;
}

static int vpq_hwrap_db_getinitcolorforadvancedvalue(UINT32 wId, void *pstData, UINT32 uDataSize)
{
	__attribute__((unused)) int ret = RET_OK;
	__attribute__((unused)) UINT32 i, j;
	__attribute__((unused)) PE_KWRAP_CTRL_T dflt_param;
	__attribute__((unused)) LX_PE_CMG_REGION_T ctrl_param;
	__attribute__((unused)) vpq_hwrap_cm_init_adv_color_t *p_init_adv_color = NULL;
	__attribute__((unused)) vpq_hwrap_cm_region_b0_t *p_cm_data = NULL;
	__attribute__((unused)) UINT32 rgn_num=0, rgn_ver=0;
	__attribute__((unused)) const LX_PE_CMG_REGION_T *p_val=NULL;

	VPQ_HWRAP_CHECK_CODE(!pstData, return RET_ERROR, \
		"Error.[%s.%d] pstData is null.\n", __F__, __L__);
	VPQ_HWRAP_CHECK_CODE(sizeof(vpq_hwrap_cm_init_adv_color_t) > uDataSize, return RET_ERROR, \
		"Error.[%s.%d] size is over(>%d).\n", __F__, __L__, uDataSize);

	p_init_adv_color = (vpq_hwrap_cm_init_adv_color_t *)pstData;

	for (i = 0; i < VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
	{
		dflt_param.wid = 0;	//default
		/* use PE_KWRAP_CMG_RGN_V00 for adv color */
		dflt_param.data = (PE_KWRAP_CMG_RGN_V00 << 16) | i;
		dflt_param.st_data = (void*)&ctrl_param;

		rgn_num = (PE_GET_BITS(dflt_param.data, 0, 16)<LX_PE_CMG_REGION_NUM)? \
			PE_GET_BITS(dflt_param.data, 0, 16):0;
		rgn_ver = PE_GET_BITS(dflt_param.data, 16, 16);
		p_val = (rgn_ver==VPQ_HWRAP_CMG_RGN_V00)? \
			g_pe_hwrap_p_cmg_rgn_v0:g_pe_hwrap_p_cmg_rgn_v1;
		memcpy(dflt_param.st_data, &(p_val[rgn_num]), sizeof(LX_PE_CMG_REGION_T));
		ret = RET_OK;
		VPQ_HWRAP_CHECK_CODE(ret, return ret, "KWRAP_PE_GetCenRgnDefaultSettings(): error %d\n", ret);
		p_cm_data = &(p_init_adv_color->data[i]);
		p_cm_data->region_en = TRUE;
		p_cm_data->regionNum = ctrl_param.region_num;
		for (j = 0; j < LX_PE_CMG_TBLPOINT; j++)
		{
			p_cm_data->hue_x[j]=ctrl_param.hue_x[j];
			p_cm_data->hue_g[j]=ctrl_param.hue_g[j];
			p_cm_data->sat_x[j]=ctrl_param.sat_x[j];
			p_cm_data->sat_g[j]=ctrl_param.sat_g[j];
			p_cm_data->val_x[j]=ctrl_param.val_x[j];
			p_cm_data->val_g[j]=ctrl_param.val_g[j];
		}
	}

	return ret;
}

static int vpq_hwrap_initcolor(UINT32 wId, UINT32 uVal, char *db_data)
{
	int ret = RET_OK;
	UINT32 i, j;
	vpq_hwrap_info_t *pInfo = &_g_vpq_hwrap_info;
	//char db_data[VPQ_HWRAP_DB_DATA_MAX];
	LX_PE_CMG_REGION_T re_param;
	LX_PE_CMG_REGION_ENABLE_T en_param;
	vpq_hwrap_cm_init_adv_color_t *p_cm_data = (vpq_hwrap_cm_init_adv_color_t *)db_data;
	vpq_hwrap_cm_region_b0_t *p_rgn_data = NULL;

	if ((uVal == VPQ_HWRAP_PE_DYN_COL_NORM) && (pInfo->dyn_color_init != VPQ_HWRAP_PE_DYN_COL_NORM))
	{
		ret = vpq_hwrap_db_getinitcolorforadvancedvalue(wId, \
			(void *)db_data, VPQ_HWRAP_DB_DATA_MAX);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, "vpq_hwrap_db_getinitcolorforadvancedvalue(): error %d\n", ret);

		/* 1. set region enable */
		memset(&(en_param), 0, sizeof(en_param));
		en_param.win_id = wId;
		for (i = 0; i < VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
		{
			p_rgn_data = &(p_cm_data->data[i]);
			en_param.enable[i] = (p_rgn_data->region_en)? 1 : 0;
		}
		ret = PE_CMG_SetCenRegionEnable(&en_param);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, "PE_CMG_SetCenRegionEnable(): error %d\n", ret);

		/* 2. setting region for all color */
		for (i = 0; i < VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
		{
			p_rgn_data = &(p_cm_data->data[i]);
			re_param.win_id = wId;
			re_param.region_num = p_rgn_data->regionNum;
			for (j = 0; j < LX_PE_CMG_TBLPOINT; j++)
			{
				re_param.hue_x[j] = VPQ_HWRAP_CONV_DEGREE_TO_10BIT(p_rgn_data->hue_x[j]);
				re_param.hue_g[j] = p_rgn_data->hue_g[j];
				re_param.sat_x[j] = VPQ_HWRAP_CONV_PERCENT_TO_8BIT(p_rgn_data->sat_x[j]);
				re_param.sat_g[j] = p_rgn_data->sat_g[j];
				re_param.val_x[j] = p_rgn_data->val_x[j];
				re_param.val_g[j] = p_rgn_data->val_g[j];
				PE_PRINT_CMG("[wid:%d] [%d] hue_x %d(%d), hue_g %d, sat_x %d(%d), sat_g %d, val_x %d, val_g %d",
					wId, i, re_param.hue_x[j], p_rgn_data->hue_x[j], re_param.hue_g[j], re_param.sat_x[j], p_rgn_data->sat_x[j], re_param.sat_g[j], re_param.val_x[j], re_param.val_g[j]);
			}

			ret = PE_CMG_SetCenRegion(&re_param);
			VPQ_HWRAP_CHECK_CODE(ret, return ret, "PE_CMG_SetCenRegion(): error %d\n", ret);
		}

		pInfo->dyn_color_init = VPQ_HWRAP_PE_DYN_COL_NORM;
	}
	else if ((uVal == VPQ_HWRAP_PE_DYN_COL_EXPT) && (pInfo->dyn_color_init != VPQ_HWRAP_PE_DYN_COL_EXPT))
	{	// TODO
		VPQ_HWRAP_CHECK_CODE(ret, return ret, "vpq_hwrap_initcolor(): error %d\n", ret);
	}

	return ret;
}

static int vpq_hwrap_db_getfreshcolorvalue(UINT32 wId, UINT32 uFcVal, void *pstData, UINT32 uDataSize)
{
	int ret = RET_OK;
	UINT32 i, j;
	PE_KWRAP_CTRL_T dflt_param;
	LX_PE_CMG_REGION_CTRL_T ctrl_param;
	vpq_hwrap_cm_dynamic_color_t *p_fresh_color = NULL;
	vpq_hwrap_cm_regionctrl_b0_t *p_cm_gain = NULL;
	vpq_hwrap_cm_clear_white_t *p_cw_data = NULL;
	UINT32 rgn_num = 0;
	const LX_PE_CMG_REGION_CTRL_T *p_val=NULL;

	VPQ_HWRAP_CHECK_CODE(!pstData, return ret, \
		"Error.[%s.%d] pstData is null.\n", __F__, __L__);
	VPQ_HWRAP_CHECK_CODE(sizeof(vpq_hwrap_cm_dynamic_color_t) > uDataSize, return ret, \
		"Error.[%s.%d] size is over(>%d).\n", __F__, __L__, uDataSize);

	p_fresh_color = (vpq_hwrap_cm_dynamic_color_t *)pstData;

	/* 1. get cm gain */
	for (i = 0; i < VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
	{
		dflt_param.wid = 0;	//default
		dflt_param.data = i;
		dflt_param.st_data = (void*)&ctrl_param;

		rgn_num = (i<LX_PE_CMG_REGION_NUM)? i:0;
		p_val = g_pe_hwrap_p_cmg_rgn_ctrl;
		memcpy(&ctrl_param, &(p_val[rgn_num]), sizeof(LX_PE_CMG_REGION_CTRL_T));
		ret = RET_OK;

		p_cm_gain = &(p_fresh_color->gain[i]);
		p_cm_gain->regionNum = ctrl_param.region_num;
		for (j = 0; j < LX_PE_CMG_DELTANUM; j++)
		{
			p_cm_gain->reDelta[j] = ctrl_param.region_delta[j];
		}
		if (uFcVal == VPQ_HWRAP_FC_LOW)
		{
			p_cm_gain->reMasterGain = (ctrl_param.master_gain >> 1);
		}
		else if (uFcVal == VPQ_HWRAP_FC_OFF)
		{
			p_cm_gain->reMasterGain = 0;
		}
		else
		{
			p_cm_gain->reMasterGain = ctrl_param.master_gain;
		}
	}

	/* 2. get cm clear white */
	p_cw_data = &(p_fresh_color->clear_white);
	memset(p_cw_data, 0x0, sizeof(vpq_hwrap_cm_clear_white_t));
	p_cw_data->cw_en = 0x1;
	p_cw_data->cw_sel = 0x1;
	p_cw_data->color_region_gain = 128;
	p_cw_data->color_region_onoff[0] = 0x1;
	p_cw_data->cw_r = 0xc0;
	p_cw_data->cw_g = 0xc0;
	p_cw_data->cw_b = (uFcVal != VPQ_HWRAP_FC_OFF) ? 0xe0 : 0xc0;

	return ret;
}

static int vpq_hwrap_setfreshcolor(UINT32 wId, UINT32 uFcVal, vpq_hwrap_cm_dynamic_color_t *pstDynamicContrast)
{
	int                      ret = RET_OK;
	UINT8                    i, j;
	UINT32                   cw_region_sel = 0;
	LX_PE_CMG_REGION_CTRL_T  ctrl_param;
	LX_PE_CMG_CW_CTRL_T      cw_param;
	LX_PE_CMG_SAT_GAIN_LUT_T sg_param;

	vpq_hwrap_cm_dynamic_color_t  *p_fc_data = NULL;
	vpq_hwrap_cm_regionctrl_b0_t  *p_cm_gain = NULL;
	vpq_hwrap_cm_clear_white_t    *p_cm_cw   = NULL;

	VPQ_HWRAP_CHECK_CODE(!pstDynamicContrast, return RET_ERROR, \
		"Error.[%s.%d] pstData is null.\n", __F__, __L__);

	p_fc_data = (vpq_hwrap_cm_dynamic_color_t *)pstDynamicContrast;

	/* 1. set region gain */
	p_cm_gain = p_fc_data->gain;
	ctrl_param.win_id = (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;

	for (i = 0; i < VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
	{
		ctrl_param.region_num = p_cm_gain[i].regionNum;
		for (j = 0; j < LX_PE_CMG_DELTANUM; j++)
		{
			ctrl_param.region_delta[j] = p_cm_gain[i].reDelta[j];
		}
		ctrl_param.master_gain = p_cm_gain[i].reMasterGain;

		PE_PRINT_CMG("[%s.%d] ui fc:%d\n", __F__, __L__, uFcVal);
		PE_PRINT_CMG(" ----------------------------------------\n");
		PE_PRINT_CMG(" path:%d\n num:%d\n"\
			" m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n", \
			ctrl_param.win_id, ctrl_param.region_num, ctrl_param.master_gain, \
			ctrl_param.region_delta[0], ctrl_param.region_delta[1], \
			ctrl_param.region_delta[2], ctrl_param.region_delta[3], \
			ctrl_param.region_delta[4], ctrl_param.region_delta[5]);
		PE_PRINT_CMG(" ----------------------------------------\n");
		ret = PE_CMG_SetCenRegionCtrl(&ctrl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_CMG_SetCenRegionCtrl() \n", __F__, __L__);
	}

	/* 2. set clear white ctrl */
	p_cm_cw = &(p_fc_data->clear_white);
	cw_param.win_id = (wId == 0)? LX_PE_WIN_0 : LX_PE_WIN_1;
	cw_param.cw_en = (UINT32)p_cm_cw->cw_en;
	cw_param.gain_sel = (UINT32)p_cm_cw->cw_sel;
	for (i = 0; i < VPQ_HWRAP_CM_CW_GAINTB; i++)
	{
		cw_param.gain_x[i] = p_cm_cw->gain_table_x[i];
		cw_param.gain_y[i] = p_cm_cw->gain_table_y[i];
	}
	for (i = 0; i < VPQ_HWRAP_CM_CW_NUM; i++)
	{
		cw_region_sel |= (UINT32)(p_cm_cw->color_region_onoff[i] << i);
	}
	cw_param.region_sel = cw_region_sel;
	cw_param.region_gain = (UINT32)p_cm_cw->color_region_gain;
	// for debug
	PE_PRINT_CMG("[%s.%d][wid:%d]cw en:%d, yc:%d\n"\
		"x,y:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d, sel:0x%02x, g:%d\n", \
		__F__, __L__, cw_param.win_id, cw_param.cw_en, cw_param.gain_sel, \
		cw_param.gain_x[0], cw_param.gain_x[1], cw_param.gain_x[2], \
		cw_param.gain_x[3], cw_param.gain_x[4], cw_param.gain_y[0], \
		cw_param.gain_y[1], cw_param.gain_y[2], cw_param.gain_y[3], \
		cw_param.gain_y[4], cw_param.region_sel, cw_param.region_gain);
	ret = PE_CMG_SetClearWhiteCtrl(&cw_param);
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
		"Error.[%s.%d] PE_CMG_SetClearWhiteCtrl() \n", __F__, __L__);

	/* 3. set saturation gain lut */
	sg_param.win_id = (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
	for (i = 0; i < 9; i++)
	{
		sg_param.x[i] = p_fc_data->sat_gain_lut_x[i];
		sg_param.y[i] = p_fc_data->sat_gain_lut_y[i];
	}
	PE_PRINT_CMG("[%s.%d][wid:%d] X: %08x %08x %08x %08x %08x %08x %08x %08x %08x\n"
		"\t\tY: %08x %08x %08x %08x %08x %08x %08x %08x %08x",
		__F__, __L__, sg_param.win_id,
		sg_param.x[0], sg_param.x[1], sg_param.x[2],
		sg_param.x[3], sg_param.x[4], sg_param.x[5],
		sg_param.x[6], sg_param.x[7], sg_param.x[8],
		sg_param.y[0], sg_param.y[1], sg_param.y[2],
		sg_param.y[3], sg_param.y[4], sg_param.y[5],
		sg_param.y[6], sg_param.y[7], sg_param.y[8]);
	ret = PE_CMG_SetSaturationGainLUT((LX_PE_CMG_SAT_GAIN_LUT_T *)&sg_param);
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
		"Error.[%s.%d] PE_CMG_SetSaturationGainLUT() \n", __F__, __L__);

	return ret;
}

static int vpq_hwrap_getoutvalbyinterpol(int in,
                              int *in_tbl,
                              int *out_tbl,
                              UINT8 min,
                              UINT8 max)
{
	UINT8 i, pre_id = 0, cur_id = 0;
	int out, x1, x2, y1, y2;

	if (in >= in_tbl[max - 1])
	{
		out = out_tbl[max - 1];
	}
	else if (in <= in_tbl[min])
	{
		out = out_tbl[min];
	}
	else
	{
		for (i = 0; i < (max - 1); i++)
		{
			if ((in_tbl[i] <= in) && (in < in_tbl[i + 1]))
			{
				pre_id = i; cur_id = i + 1;
				break;
			}
		}
		x1 = in_tbl[pre_id];
		x2 = in_tbl[cur_id];
		y1 = out_tbl[pre_id];
		y2 = out_tbl[cur_id];
		out = (in - x1) * (y2 - y1) / (x2 - x1) + y1;
	}
	return out;
}

static int vpq_hwrap_db_getpreferredcolorvalue(UINT32 wId, SINT8 *pstPfVal, void *pstData, UINT32 uDataSize)
{
	int ret = RET_OK;
	UINT8 i;
	SINT8 cm_preferred = 0;
	SINT8 preferred_color_value = 0;
	SINT8 fresh_color_value = 0;
	int i_val, o_val;
	int i_tbl[VPQ_HWRAP_DB_TBL_MAX] = { -5,  0,  5};
	int o_tbl[VPQ_HWRAP_DB_TBL_MAX] = {-50,  0, 50};
	PE_KWRAP_CTRL_T dflt_param;
	LX_PE_CMG_REGION_CTRL_T ctrl_param;
	vpq_hwrap_cm_color_control_t *pf_data = NULL;
	vpq_hwrap_cm_regionctrl_b0_t *p_cm_gain = NULL;
	UINT32 rgn_num = 0;
	const LX_PE_CMG_REGION_CTRL_T *p_val=NULL;

	VPQ_HWRAP_CHECK_CODE(!pstPfVal, return RET_ERROR, \
		"Error.[%s.%d] pstPfVal is null.\n", __F__, __L__);
	VPQ_HWRAP_CHECK_CODE(!pstData, return RET_ERROR, \
		"Error.[%s.%d] pstData is null.\n", __F__, __L__);
	VPQ_HWRAP_CHECK_CODE(sizeof(vpq_hwrap_cm_color_control_t) > uDataSize, return RET_ERROR, \
		"Error.[%s.%d] size is over(>%d).\n", __F__, __L__, uDataSize);

	pf_data = (vpq_hwrap_cm_color_control_t *)pstData;

	cm_preferred = pstPfVal[0];
	preferred_color_value = pstPfVal[1];
	fresh_color_value = pstPfVal[2];

	/* 1. get cm gain */
	dflt_param.wid = 0;	//default
	if (cm_preferred == V4L2_EXT_CM_PREFERRED_COLOR_SKIN)
	{
		dflt_param.data = PE_KWRAP_CMG_RGN_COL_SKN;
	}
	else if (cm_preferred == V4L2_EXT_CM_PREFERRED_COLOR_GRASS)
	{
		dflt_param.data = PE_KWRAP_CMG_RGN_COL_GRN;
	}
	else
	{
		dflt_param.data = PE_KWRAP_CMG_RGN_COL_BLU;
	}
	dflt_param.st_data = (void*)&ctrl_param;

	rgn_num = (dflt_param.data<LX_PE_CMG_REGION_NUM)? dflt_param.data:0;
	p_val = g_pe_hwrap_p_cmg_rgn_ctrl;
	memcpy(&ctrl_param, &(p_val[rgn_num]), sizeof(LX_PE_CMG_REGION_CTRL_T));
	ret = RET_OK;
	p_cm_gain = &(pf_data->gain);
	p_cm_gain->regionNum = ctrl_param.region_num;
	for (i = 0; i < LX_PE_CMG_DELTANUM; i++)
	{
		p_cm_gain->reDelta[i] = ctrl_param.region_delta[i];
	}
	if (fresh_color_value == VPQ_HWRAP_FC_LOW)
	{
		p_cm_gain->reMasterGain = (ctrl_param.master_gain>>1);
	}
	else if (fresh_color_value == VPQ_HWRAP_FC_OFF)
	{
		p_cm_gain->reMasterGain = 0;
	}
	else
	{
		p_cm_gain->reMasterGain = ctrl_param.master_gain;
	}

	/* 2. get preffered color hue offset */
	i_val = (int)preferred_color_value;
	o_val = ((vpq_hwrap_getoutvalbyinterpol(i_val, \
		i_tbl, o_tbl, VPQ_HWRAP_DB_TBL_MIN, VPQ_HWRAP_DB_TBL_MAX) * 10) + 5) / 10;
	PE_PRINT_CMG("[%s.%d] i_val %d -> o_val %d\n", __F__, __L__, i_val, o_val);
	if (cm_preferred == VPQ_HWRAP_PF_COLOR_SKIN)
	{
		pf_data->skin_hue_val = (SINT8)o_val;
	}
	else if (cm_preferred == VPQ_HWRAP_PF_COLOR_BSKY)
	{
		pf_data->bsky_hue_val = (SINT8)o_val;
	}
	else
	{
		pf_data->grass_hue_val = (SINT8)o_val;
	}

	return ret;
}

static int vpq_hwrap_db_getcolormanagementvalue (UINT32 wId,
										SINT8 *pCmVal,
										void *pstData,
										UINT32 uDataSize)
{
	int ret = RET_OK;
	SINT8 cm_rgn_num=0, sat_val=0, hue_val=0, lum_val=0;
	UINT32 i=0;
	vpq_hwrap_cm_data_t *p_color_mgnt = NULL;
	vpq_hwrap_cm_regionctrl_b0_t *p_cm_gain = NULL;

	int i_val, o_val;
	int i_tbl[VPQ_HWRAP_DB_TBL_MAX] = {-30,   0,  30};
	int o_tbl[VPQ_HWRAP_DB_TBL_MAX] = {-120,  0, 120};

	#if 0//SEE_TV
	VPQ_CHECK_CODE(!KADP_VP_IsInitialized(), return NOT_OK, \
		"Error.[%s.%d] not ready.\n", __F__, __L__);
	#endif
	VPQ_HWRAP_CHECK_CODE(!pCmVal, return RET_ERROR, \
		"Error.[%s.%d] pCmVal is null.\n", __F__, __L__);
	VPQ_HWRAP_CHECK_CODE(!pstData, return RET_ERROR, \
		"Error.[%s.%d] pstData is null.\n", __F__, __L__);
	VPQ_HWRAP_CHECK_CODE(sizeof(vpq_hwrap_cm_data_t)>uDataSize, return RET_ERROR, \
		"Error.[%s.%d] size is over(>%d).\n", __F__, __L__, uDataSize);

	p_color_mgnt = (vpq_hwrap_cm_data_t *)pstData;
	cm_rgn_num = pCmVal[0];
	sat_val = pCmVal[1];
	hue_val = pCmVal[2];
	lum_val = pCmVal[3];
	/*fc_val = pCmVal[4];*/

	/* 1. get cm gain */
	p_cm_gain = &(p_color_mgnt->gain);
	p_cm_gain->regionNum = cm_rgn_num;
	for (i=0;i<LX_PE_CMG_DELTANUM;i++)
	{
		p_cm_gain->reDelta[i] = 0;
	}
	p_cm_gain->reMasterGain = 255;

	/* 2. get cm gain offset */
	i_val = (int)sat_val;
	o_val = ((vpq_hwrap_getoutvalbyinterpol(i_val, \
		i_tbl, o_tbl, VPQ_HWRAP_DB_TBL_MIN, VPQ_HWRAP_DB_TBL_MAX)*10)+ 5)/ 10;
	p_color_mgnt->sat_offset = (SINT32)o_val;
	i_val = (int)hue_val;
	o_val = ((vpq_hwrap_getoutvalbyinterpol(i_val, \
		i_tbl, o_tbl, VPQ_HWRAP_DB_TBL_MIN, VPQ_HWRAP_DB_TBL_MAX)*10)+ 5)/ 10;
	p_color_mgnt->hue_offset = (SINT32)o_val;
	i_val = (int)lum_val;
	o_val = ((vpq_hwrap_getoutvalbyinterpol(i_val, \
		i_tbl, o_tbl, VPQ_HWRAP_DB_TBL_MIN, VPQ_HWRAP_DB_TBL_MAX)*10)+ 5)/ 10;
	p_color_mgnt->val_offset = (SINT32)o_val;

	return ret;
}

int vpq_hwrap_setcmdbdata(unsigned char wId, struct v4l2_ext_cm_info *pCmInfo, int version)
{
	int ret = RET_OK;
	vpq_hwrap_cm_db_t *pCmDb = NULL;
	char *db_data;
	//vpq_hwrap_info_t *pInfo = &_g_vpq_hwrap_info;
	LX_PE_WIN_ID win_id = (wId == 0)? LX_PE_WIN_0 : LX_PE_WIN_1;
	UINT32 i, j;
	LX_PE_CMG_REGION_CTRL_T  gain_param;
	__attribute__((unused)) static LX_PE_CMG_REGION_ALL_T total_cen_region;
	__attribute__((unused)) UINT32 region_num_param = 0;
	VPQ_HWRAP_CHECK_CODE(!pCmInfo, return ret, "Error. pCmInfo is null.\n");

	pCmDb = (vpq_hwrap_cm_db_t *)pCmInfo->dbInfo;

	PE_PRINT_CMG("[%s.%d][wid:%d] use_internal_cm_db: %d, pCmDb: 0x%p\n",
		__F__, __L__, wId, pCmInfo->use_internal_cm_db, pCmDb);
	if (pCmInfo->use_internal_cm_db) // internal DB
	{
		db_data = OS_Malloc(VPQ_HWRAP_DB_DATA_MAX);
		/*dynamic color*/
		if (pCmInfo->uiInfo.dynamic.enable)
		{
			(void)vpq_hwrap_initcolor(wId, VPQ_HWRAP_PE_DYN_COL_NORM, db_data);
			ret = vpq_hwrap_db_getfreshcolorvalue(win_id, \
				pCmInfo->uiInfo.dynamic.value, (void *)db_data, VPQ_HWRAP_DB_DATA_MAX);
			ret = vpq_hwrap_setfreshcolor(win_id, pCmInfo->uiInfo.dynamic.value, (vpq_hwrap_cm_dynamic_color_t *)db_data);
			if(ret && db_data)
			{
				OS_Free(db_data);
			}
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"[%s,%d] vpq_hwrap_setfreshcolor() error.\n", __F__, __L__);
		}
		/* preffered color */
		if (pCmInfo->uiInfo.preferred.enable)
		{
			enum v4l2_ext_cm_perferred_color_type cm_preferred;
			SINT8 sVal[3];
			SINT16 temp = 0;
			vpq_hwrap_cm_color_control_t *pf_data = (vpq_hwrap_cm_color_control_t *)db_data;
			(void)vpq_hwrap_initcolor(wId, VPQ_HWRAP_PE_DYN_COL_NORM, db_data);

			for (cm_preferred = V4L2_EXT_CM_PREFERRED_COLOR_SKIN; cm_preferred < V4L2_EXT_CM_PREFERRED_COLOR_MAX; cm_preferred++)
			{
				sVal[0] = (cm_preferred == V4L2_EXT_CM_PREFERRED_COLOR_SKIN) ? VPQ_HWRAP_PF_COLOR_SKIN :
					(cm_preferred == V4L2_EXT_CM_PREFERRED_COLOR_SKYBLUE) ? VPQ_HWRAP_PF_COLOR_BSKY : VPQ_HWRAP_PF_COLOR_GRASS;
				sVal[1] = pCmInfo->uiInfo.preferred.value[cm_preferred];
				sVal[2] = pCmInfo->uiInfo.dynamic.value;

				ret = vpq_hwrap_db_getpreferredcolorvalue(win_id,
					sVal, (void *)db_data, VPQ_HWRAP_DB_DATA_MAX);
				if(ret)
				{
					OS_Free(db_data);
				}
				VPQ_HWRAP_CHECK_CODE(ret, return ret, \
					"[%s,%d]vpq_hwrap_db_getpreferredcolorvalue() error.", __F__, __L__);

				gain_param.win_id = (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
				gain_param.region_num = pf_data->gain.regionNum;
				for (i = 0; i < LX_PE_CMG_DELTANUM; i++)
				{
					gain_param.region_delta[i] = pf_data->gain.reDelta[i];
				}
				gain_param.master_gain = pf_data->gain.reMasterGain;

				/* adjusting a preferred color hue with the offset */
				switch (cm_preferred)
				{
					case V4L2_EXT_CM_PREFERRED_COLOR_SKIN:
						temp = gain_param.region_delta[0] + pf_data->skin_hue_val;
						PE_PRINT_CMG("[%s.%d]ui_skin, fc:%d, %d, offset:%d\n", \
							__F__, __L__, sVal[1], \
							sVal[2], pf_data->skin_hue_val);
						break;
					case V4L2_EXT_CM_PREFERRED_COLOR_GRASS:
						temp = gain_param.region_delta[0] + pf_data->grass_hue_val;
						PE_PRINT_CMG("[%s.%d]ui_grass, fc:%d, %d, offset:%d\n", \
							__F__, __L__, sVal[1], \
							sVal[2], pf_data->grass_hue_val);
						break;
					case V4L2_EXT_CM_PREFERRED_COLOR_SKYBLUE:
					default:
						temp = gain_param.region_delta[0] + pf_data->bsky_hue_val;
						PE_PRINT_CMG("[%s.%d]ui_bsky, fc:%d, %d, offset:%d\n", \
							__F__, __L__, sVal[1], \
							sVal[2], pf_data->bsky_hue_val);
						break;
				}
				if (temp > 127)
					temp = 127;
				else if (temp < -128)
					temp = -128;
				gain_param.region_delta[0] = (SINT8)temp;	// hue

				PE_PRINT_CMG(" ----------------------------------------\n");
				PE_PRINT_CMG(" path:%d\n num:%d\n"\
					" m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n", \
					gain_param.win_id, gain_param.region_num, gain_param.master_gain, \
					gain_param.region_delta[0], gain_param.region_delta[1], \
					gain_param.region_delta[2], gain_param.region_delta[3], \
					gain_param.region_delta[4], gain_param.region_delta[5]);
				ret = PE_CMG_SetCenRegionCtrl(&gain_param);
				if(ret)
				{
					OS_Free(db_data);
				}
				VPQ_HWRAP_CHECK_CODE(ret, return ret, \
					"Error.[%s.%d] PE_CMG_SetCenRegionCtrl() \n", __F__, __L__);
			}
		}
		/* cms */
		if (pCmInfo->uiInfo.cms.enable)
		{
			SINT8 cm_val[5];
			UINT32 regionNum;
			vpq_hwrap_cm_data_t *p_cm_data = NULL;

			for (i=0; i< V4L2_EXT_CM_CMS_MAX ; i++)
			{
				if(i == V4L2_EXT_CM_CMS_RED)
					regionNum = VPQ_HWRAP_CM_REGION_RED;
				else if(i == V4L2_EXT_CM_CMS_GREEN)
					regionNum = VPQ_HWRAP_CM_REGION_GRN;
				else if(i == V4L2_EXT_CM_CMS_BLUE)
					regionNum = VPQ_HWRAP_CM_REGION_BLU;
				else if(i == V4L2_EXT_CM_CMS_CYAN)
					regionNum = VPQ_HWRAP_CM_REGION_CYN;
				else if(i == V4L2_EXT_CM_CMS_MAGENTA)
					regionNum = VPQ_HWRAP_CM_REGION_MGT;
				else if(i == V4L2_EXT_CM_CMS_YELLOW)
					regionNum = VPQ_HWRAP_CM_REGION_YEL;
				cm_val[0] = (UINT32)regionNum;
				cm_val[1] = pCmInfo->uiInfo.cms.gain_saturation[i];
				cm_val[2] = pCmInfo->uiInfo.cms.gain_hue[i];
				cm_val[3] = pCmInfo->uiInfo.cms.gain_luminance[i];
				cm_val[4] = pCmInfo->uiInfo.dynamic.value; //default

				ret = vpq_hwrap_db_getcolormanagementvalue(win_id, \
					cm_val, (void *)db_data, VPQ_HWRAP_DB_DATA_MAX);
				if(ret)
				{
					OS_Free(db_data);
				}
				VPQ_HWRAP_CHECK_CODE(ret, return ret, \
					"Error.[%s.%d] vpq_hwrap_db_getcolormanagementvalue() \n", __F__, __L__);
				p_cm_data = (vpq_hwrap_cm_data_t *)db_data;
				gain_param.win_id = (wId==LX_PE_WIN_0)? LX_PE_WIN_0:LX_PE_WIN_1;
				gain_param.region_num = p_cm_data->gain.regionNum;
				for (j=0;j<LX_PE_CMG_DELTANUM;j++)
				{
					gain_param.region_delta[j] = p_cm_data->gain.reDelta[j];
				}
				gain_param.master_gain = p_cm_data->gain.reMasterGain;
				
				//3. adjusting hue/sat with the offset
				gain_param.region_delta[0] += p_cm_data->hue_offset;
				gain_param.region_delta[1] += p_cm_data->sat_offset;
				gain_param.region_delta[2] += p_cm_data->val_offset;

				ret = PE_CMG_SetCenRegionCtrl(&gain_param);
				if(ret)
				{
					OS_Free(db_data);
				}
				VPQ_HWRAP_CHECK_CODE(ret, return ret, \
					"Error.[%s.%d] PE_CMG_SetCenRegionCtrl() \n", __F__, __L__);
			}
		}
		if (db_data)
		{
			OS_Free(db_data);
		}
	}
	else // PQ DB
	{
		if(version == 0x80) // webos24
		{
			ret = vpq_hwrap_setcmdbdata_o26(wId, pCmInfo);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setcmdbdata_o26 error(%d)\n", ret);
			}
		}
		else
		{
			ret = vpq_hwrap_setcmdbdata_o24(wId, pCmInfo);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setcmdbdata_o24 error(%d)\n", ret);
			}
		}
	}

	return ret;
}

static int vpq_hwrap_setcmdbdata_o26(unsigned char wId, struct v4l2_ext_cm_info *pCmInfo)
{
	int ret = RET_OK;
	vpq_hwrap_cm_db_o26_t *pCmDb_o26 = NULL;
	//vpq_hwrap_info_t *pInfo = &_g_vpq_hwrap_info;
	//LX_PE_WIN_ID win_id = (wId == 0)? LX_PE_WIN_0 : LX_PE_WIN_1;
	UINT32 i, j;
	LX_PE_CMG_REGION_CTRL_T  gain_param;
	LX_PE_CMG_REGION2_T		 ctrl_param;
	LX_PE_CMG_REGION_ENABLE_T en_param;
	LX_PE_CMG_CW_CTRL_T 	 cw_param;
	LX_PE_CMG_CW_GAIN_CTRL_T cw_gain_param;
	LX_PE_CMG_CW_TABLE_CTRL_T 	 cw_table_param;
	LX_PE_CMG_VSPCC2_CTRL_T 	 vspcc_param;
	LX_PE_CMG_DSE_CTRL_T 	 dse_param;
	UINT32                   cw_region_sel = 0;
	__attribute__((unused)) static LX_PE_CMG_REGION_ALL_T total_cen_region;
	__attribute__((unused)) UINT32 region_num_param = 0;
	VPQ_HWRAP_CHECK_CODE(!pCmInfo, return ret, "Error. pCmInfo is null.\n");

	pCmDb_o26 = (vpq_hwrap_cm_db_o26_t *)pCmInfo->dbInfo;

	PE_PRINT_CMG("[%s.%d][wid:%d] use_internal_cm_db: %d, pCmDb: 0x%p\n",
		__F__, __L__, wId, pCmInfo->use_internal_cm_db, pCmDb_o26);
		memset(&en_param, 0x00, sizeof(en_param));
		VPQ_HWRAP_CHECK_CODE(!pCmInfo, return RET_ERROR, \
			"Error.[%s.%d] pCmInfo is null.\n", __F__, __L__);
		//gain_param.win_id = ctrl_param.win_id = total_cen_region.win_id = en_param.win_id= (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
	for (i = 0; i < VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
	{
		gain_param.win_id = ctrl_param.win_id = en_param.win_id= (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
		gain_param.dynamic_ui = pCmInfo->uiInfo.dynamic.value;
		/* 1. set region gain */
		if(pCmDb_o26->region_gain[i].needUpdate)
		{
			gain_param.region_num = pCmDb_o26->region_gain[i].regionNum;
			for (j = 0; j < LX_PE_CMG_DELTANUM; j++)
			{
				gain_param.region_delta[j] = pCmDb_o26->region_gain[i].delta[j];
			}
			gain_param.master_gain = pCmDb_o26->region_gain[i].masterGain;

			//PE_PRINT_CMG("[%s.%d] ui :%d\n", __F__, __L__, uFcVal);
			PE_PRINT_CMG(" ----------------------------------------\n");
			PE_PRINT_CMG(" path:%d\n num:%d, m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n", \
				gain_param.win_id, gain_param.region_num, gain_param.master_gain, \
				gain_param.region_delta[0], gain_param.region_delta[1], \
				gain_param.region_delta[2], gain_param.region_delta[3], \
				gain_param.region_delta[4], gain_param.region_delta[5]);
			PE_PRINT_CMG(" ----------------------------------------\n");
			ret = PE_CMG_SetCenRegionCtrl(&gain_param);
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_CMG_SetCenRegionCtrl() \n", __F__, __L__);
		}

		/* 2. set region ctrl  changed @o26 */
		if(pCmDb_o26->region_ctrl[i].needUpdate)
		{
			ctrl_param.region_num = pCmDb_o26->region_ctrl[i].regionNum;
			ctrl_param.aiGainNum = pCmDb_o26->region_ctrl[i].aiGainNum;
			en_param.enable[i]= pCmDb_o26->region_ctrl[i].region_en;

			PE_PRINT_CMG(" ----------------------------------------\n");
			PE_PRINT_CMG(" path:%d\n num:%d, en %d, aigainNum: %d\n",\
				ctrl_param.win_id, ctrl_param.region_num, en_param.enable[i], ctrl_param.aiGainNum);
			for (j = 0; j < LX_PE_CMG_TBLPOINT; j++)
			{
				ctrl_param.hue_x[j] = VPQ_HWRAP_CONV_DEGREE_TO_10BIT(pCmDb_o26->region_ctrl[i].hue_x[j]);
				ctrl_param.hue_g[j] = pCmDb_o26->region_ctrl[i].hue_g[j];
				ctrl_param.sat_x[j] = VPQ_HWRAP_CONV_PERCENT_TO_8BIT(pCmDb_o26->region_ctrl[i].sat_x[j]);
				ctrl_param.sat_g[j] = pCmDb_o26->region_ctrl[i].sat_g[j];
				ctrl_param.val_x[j] = pCmDb_o26->region_ctrl[i].val_x[j];
				ctrl_param.val_g[j] = pCmDb_o26->region_ctrl[i].val_g[j];

				PE_PRINT_CMG("tblpint[%d] hue_x/g:%d,%d, sat_x/g:%d,%d, val_x/g:%d,%d\n", \
					j, ctrl_param.hue_x[j],ctrl_param.hue_g[j],ctrl_param.sat_x[j],\
					ctrl_param.sat_g[j],ctrl_param.val_x[j],ctrl_param.val_g[j]);
			}
			PE_PRINT_CMG(" ----------------------------------------\n");
			ret = PE_CMG_SetCenRegion2((void *)&ctrl_param);
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_CMG_SetCenRegion() \n", __F__, __L__);

			ret = PE_CMG_SetCenRegionEnable(&en_param);
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
						"Error.[%s.%d] PE_CMG_SetCenRegionEnable() \n", __F__, __L__);
		}
	}
	/*3 clear white*/
	PE_PRINT_CMG("clear white needUpdate:%d n",pCmDb_o26->clear_white.needUpdate);
	if(pCmDb_o26->clear_white.needUpdate)
	{
		memset(&cw_param, 0x00, sizeof(cw_param));
		cw_param.win_id = cw_gain_param.win_id= cw_table_param.win_id =(wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
		cw_param.cw_en= (UINT32)pCmDb_o26->clear_white.cw_en;
		cw_param.gain_sel = (UINT32)pCmDb_o26->clear_white.cw_sel;
		for (i=0; i<VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
		{
			cw_region_sel |= (UINT32)(pCmDb_o26->clear_white.color_region_onoff[i]<<i);
		}
		cw_param.region_sel = cw_region_sel;
		cw_param.region_gain= (UINT32)pCmDb_o26->clear_white.color_region_gain;
		ret = PE_CMG_SetClearWhiteCtrl(&cw_param);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_CMG_SetClearWhiteCtrl() \n", __F__, __L__);

		cw_gain_param.r_gain = (pCmDb_o26->clear_white.gain_r>VPQ_HWRAP_CW_GAIN_MAX)? \
			VPQ_HWRAP_CW_GAIN_MAX:pCmDb_o26->clear_white.gain_r;
		cw_gain_param.g_gain = (pCmDb_o26->clear_white.gain_g>VPQ_HWRAP_CW_GAIN_MAX)? \
			VPQ_HWRAP_CW_GAIN_MAX:pCmDb_o26->clear_white.gain_g;
		cw_gain_param.b_gain = (pCmDb_o26->clear_white.gain_b>VPQ_HWRAP_CW_GAIN_MAX)? \
			VPQ_HWRAP_CW_GAIN_MAX:pCmDb_o26->clear_white.gain_b;
		if(PE_KDRV_VER_O20)
		{
			ret = KWRAP_PE_SetClearWhiteGainParam(&cw_gain_param);
		}
		else
		{
			ret = PE_CMG_SetClearWhiteGainCtrl(&cw_gain_param);
		}
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_CMG_SetClearWhiteGainCtrl() \n", __F__, __L__);
		#if 0
		printk(\
			" hue_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" hue_y: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_y: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_y: %d, %d, %d, %d, %d, %d, %d, %d,\n", \
			pCmDb->clear_white.cw_hue_x[0], pCmDb->clear_white.cw_hue_x[1], pCmDb->clear_white.cw_hue_x[2], pCmDb->clear_white.cw_hue_x[3], \
			pCmDb->clear_white.cw_hue_x[4], pCmDb->clear_white.cw_hue_x[5], pCmDb->clear_white.cw_hue_x[6], pCmDb->clear_white.cw_hue_x[7], \
			pCmDb->clear_white.cw_hue_y[0], pCmDb->clear_white.cw_hue_y[1], pCmDb->clear_white.cw_hue_y[2], pCmDb->clear_white.cw_hue_y[3], \
			pCmDb->clear_white.cw_hue_y[4], pCmDb->clear_white.cw_hue_y[5], pCmDb->clear_white.cw_hue_y[6], pCmDb->clear_white.cw_hue_y[7], \
			pCmDb->clear_white.cw_sat_x[0], pCmDb->clear_white.cw_sat_x[1], pCmDb->clear_white.cw_sat_x[2], pCmDb->clear_white.cw_sat_x[3], \
			pCmDb->clear_white.cw_sat_x[4], pCmDb->clear_white.cw_sat_x[5], pCmDb->clear_white.cw_sat_x[6], pCmDb->clear_white.cw_sat_x[7], \
			pCmDb->clear_white.cw_sat_y[0], pCmDb->clear_white.cw_sat_y[1], pCmDb->clear_white.cw_sat_y[2], pCmDb->clear_white.cw_sat_y[3], \
			pCmDb->clear_white.cw_sat_y[4], pCmDb->clear_white.cw_sat_y[5], pCmDb->clear_white.cw_sat_y[6], pCmDb->clear_white.cw_sat_y[7], \
			pCmDb->clear_white.cw_val_x[0], pCmDb->clear_white.cw_val_x[1], pCmDb->clear_white.cw_val_x[2], pCmDb->clear_white.cw_val_x[3], \
			pCmDb->clear_white.cw_val_x[4], pCmDb->clear_white.cw_val_x[5], pCmDb->clear_white.cw_val_x[6], pCmDb->clear_white.cw_val_x[7], \
			pCmDb->clear_white.cw_val_y[0], pCmDb->clear_white.cw_val_y[1], pCmDb->clear_white.cw_val_y[2], pCmDb->clear_white.cw_val_y[3], \
			pCmDb->clear_white.cw_val_y[4], pCmDb->clear_white.cw_val_y[5], pCmDb->clear_white.cw_val_y[6], pCmDb->clear_white.cw_val_y[7]);
		#endif
		memcpy(&(cw_table_param.cw_hue_x),&(pCmDb_o26->clear_white.cw_hue_x) ,sizeof(unsigned short)*VPQ_HWRAP_CM_TBLPOINT );
		memcpy(&(cw_table_param.cw_hue_y),&(pCmDb_o26->clear_white.cw_hue_y) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
		memcpy(&(cw_table_param.cw_sat_x),&(pCmDb_o26->clear_white.cw_sat_x) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
		memcpy(&(cw_table_param.cw_sat_y),&(pCmDb_o26->clear_white.cw_sat_y) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
		memcpy(&(cw_table_param.cw_val_x),&(pCmDb_o26->clear_white.cw_val_x) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
		memcpy(&(cw_table_param.cw_val_y),&(pCmDb_o26->clear_white.cw_val_y) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
		if(PE_KDRV_VER_O20)
		{
			ret = KWRAP_PE_SetClearWhiteTableParam(&cw_table_param);
		}
		else
		{
			ret = PE_CMG_SetClearWhiteTableCtrl(&cw_table_param);
		}
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_CMG_SetClearWhiteTableCtrl() \n", __F__, __L__);
	}
	PE_PRINT_CMG("dse needUpdate:%d n",pCmDb_o26->cm_dse.needUpdate);
	/*4 dse*/
	if(pCmDb_o26->cm_dse.needUpdate)
	{
		memset(&dse_param, 0x00, sizeof(dse_param));
		dse_param.win_id = (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
		dse_param.saturation_cr_mode     = pCmDb_o26->cm_dse.saturation_cr_mode;
		dse_param.saturation_region_gain = pCmDb_o26->cm_dse.saturation_region_gain;
		memcpy(&(dse_param.dse_h_x),&(pCmDb_o26->cm_dse.dse_h_x) ,sizeof(UINT16)*LX_PE_CMG_TBLPOINT);
		memcpy(&(dse_param.dse_h_y),&(pCmDb_o26->cm_dse.dse_h_y) ,sizeof(UINT16)*LX_PE_CMG_TBLPOINT);
		memcpy(&(dse_param.dse_y_x),&(pCmDb_o26->cm_dse.dse_y_x) ,sizeof(UINT16)*LX_PE_CMG_TBLPOINT);
		memcpy(&(dse_param.dse_y_y),&(pCmDb_o26->cm_dse.dse_y_y) ,sizeof(UINT16)*LX_PE_CMG_TBLPOINT);
		memcpy(&(dse_param.sSaturationLUT_x),&(pCmDb_o26->cm_dse.sSaturationLUT_x) ,sizeof(UINT16)*16);
		memcpy(&(dse_param.sSaturationLUT_y),&(pCmDb_o26->cm_dse.sSaturationLUT_y) ,sizeof(UINT16)*16);
		memcpy(&(dse_param.region_onoff),&(pCmDb_o26->cm_dse.region_onoff) ,sizeof(UINT8)*LX_PE_CMG_REGION_NUM);
		PE_PRINT_CMG("set: saturation_cr_mode:%d, saturation_region_gain:%d\n"\
			"region sel:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
			dse_param.saturation_cr_mode, dse_param.saturation_region_gain, \
			dse_param.region_onoff[0],dse_param.region_onoff[1],dse_param.region_onoff[2],dse_param.region_onoff[3],\
			dse_param.region_onoff[4],dse_param.region_onoff[5],dse_param.region_onoff[6],dse_param.region_onoff[7],\
			dse_param.region_onoff[8],dse_param.region_onoff[9],dse_param.region_onoff[10],dse_param.region_onoff[11],\
			dse_param.region_onoff[12],dse_param.region_onoff[13],dse_param.region_onoff[14],dse_param.region_onoff[15]);
		PE_PRINT_CMG("set dse_gain: n"\
			"dse_gain_h_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
			"dse_gain_h_y:%d,%d,%d,%d,%d,%d,%d,%d\n" \
			"dse_gain_y_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
			"dse_gain_y_y:%d,%d,%d,%d,%d,%d,%d,%d\n", \
			dse_param.dse_h_x[0],dse_param.dse_h_x[1],dse_param.dse_h_x[2],dse_param.dse_h_x[3],\
			dse_param.dse_h_x[4],dse_param.dse_h_x[5],dse_param.dse_h_x[6],dse_param.dse_h_x[7],\
			dse_param.dse_h_y[0],dse_param.dse_h_y[1],dse_param.dse_h_y[2],dse_param.dse_h_y[3],\
			dse_param.dse_h_y[4],dse_param.dse_h_y[5],dse_param.dse_h_y[6],dse_param.dse_h_y[7],\
			dse_param.dse_y_x[0],dse_param.dse_y_x[1],dse_param.dse_y_x[2],dse_param.dse_y_x[3],\
			dse_param.dse_y_x[4],dse_param.dse_y_x[5],dse_param.dse_y_x[6],dse_param.dse_y_x[7],\
			dse_param.dse_y_y[0],dse_param.dse_y_y[1],dse_param.dse_y_y[2],dse_param.dse_y_y[3],\
			dse_param.dse_y_y[4],dse_param.dse_y_y[5],dse_param.dse_y_y[6],dse_param.dse_y_y[7]);
		if(PE_KDRV_VER_O20)
		{
			ret = KWRAP_PE_SetDseParam(&dse_param);
		}
		else
		{
			ret = PE_CMG_SetDseCtrl(&dse_param);
		}
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_CMG_SetDseCtrl() \n", __F__, __L__);
	}
	/*5 vspcc*/
	if(pCmDb_o26->cm_vspcc.needUpdate)
	{
		memset(&vspcc_param, 0x00, sizeof(vspcc_param));
		vspcc_param.win_id = (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
		vspcc_param.headMap0Gain  = pCmDb_o26->cm_vspcc.headMap0Gain;
		vspcc_param.bodyMap0Gain  = pCmDb_o26->cm_vspcc.bodyMap0Gain;
		vspcc_param.textMap0Gain  = pCmDb_o26->cm_vspcc.textMap0Gain;
		vspcc_param.motionMap0Gain= pCmDb_o26->cm_vspcc.motionMap0Gain;
		vspcc_param.headMap1Gain  = pCmDb_o26->cm_vspcc.headMap1Gain;
		vspcc_param.bodyMap1Gain  = pCmDb_o26->cm_vspcc.bodyMap1Gain;
		vspcc_param.textMap1Gain  = pCmDb_o26->cm_vspcc.textMap1Gain;
		vspcc_param.motionMap1Gain= pCmDb_o26->cm_vspcc.motionMap1Gain;

		for(i =0 ; i< 4 ; i++)
		{
			vspcc_param.headMap0GainLUT_x[i]  	= pCmDb_o26->cm_vspcc.headMap0GainLUT_x[i];			
			vspcc_param.headMap0GainLUT_y[i]	= pCmDb_o26->cm_vspcc.headMap0GainLUT_y[i];
			vspcc_param.bodyMap0GainLUT_x[i]	= pCmDb_o26->cm_vspcc.bodyMap0GainLUT_x[i];
			vspcc_param.bodyMap0GainLUT_y[i]	= pCmDb_o26->cm_vspcc.bodyMap0GainLUT_y[i];
			vspcc_param.textMap0GainLUT_x[i]	= pCmDb_o26->cm_vspcc.textMap0GainLUT_x[i];
			vspcc_param.textMap0GainLUT_y[i]	= pCmDb_o26->cm_vspcc.textMap0GainLUT_y[i];
			vspcc_param.motionMap0GainLUT_x[i]	= pCmDb_o26->cm_vspcc.motionMap0GainLUT_x[i];
			vspcc_param.motionMap0GainLUT_y[i]	= pCmDb_o26->cm_vspcc.motionMap0GainLUT_y[i];
			vspcc_param.headMap1GainLUT_x[i]	= pCmDb_o26->cm_vspcc.headMap1GainLUT_x[i];
			vspcc_param.headMap1GainLUT_y[i]	= pCmDb_o26->cm_vspcc.headMap1GainLUT_y[i];
			vspcc_param.bodyMap1GainLUT_x[i]	= pCmDb_o26->cm_vspcc.bodyMap1GainLUT_x[i];
			vspcc_param.bodyMap1GainLUT_y[i]	= pCmDb_o26->cm_vspcc.bodyMap1GainLUT_y[i];
			vspcc_param.textMap1GainLUT_x[i]	= pCmDb_o26->cm_vspcc.textMap1GainLUT_x[i];
			vspcc_param.textMap1GainLUT_y[i]	= pCmDb_o26->cm_vspcc.textMap1GainLUT_y[i];
			vspcc_param.motionMap1GainLUT_x[i]	= pCmDb_o26->cm_vspcc.motionMap1GainLUT_x[i];
			vspcc_param.motionMap1GainLUT_y[i]	= pCmDb_o26->cm_vspcc.motionMap1GainLUT_y[i];
		}


		
		PE_PRINT_CMG("set[%d] \n"\
			"headMap0Gain  : %d\n" \
			"bodyMap0Gain  : %d\n" \
			"textMap0Gain  : %d\n" \
			"motionMap0Gain: %d\n" \
			"headMap1Gain  : %d\n" \
			"bodyMap1Gain  : %d\n" \
			"textMap1Gain  : %d\n" \
			"motionMap1Gain: %d\n" \
			"headMap0GainLUT_x:%d, %d, %d, %d\n" \
			"headMap0GainLUT_y:%d, %d, %d, %d\n" \
			"bodyMap0GainLUT_x:%d, %d, %d, %d\n" \
			"bodyMap0GainLUT_y:%d, %d, %d, %d\n" \
			"textMap0GainLUT_x:%d, %d, %d, %d\n" \
			"textMap0GainLUT_y:%d, %d, %d, %d\n" \
			"motionMap0GainLUT_x:%d, %d, %d, %d\n" \
			"motionMap0GainLUT_y:%d, %d, %d, %d\n" \
			"headMap1GainLUT_x:%d, %d, %d, %d\n" \
			"headMap1GainLUT_y:%d, %d, %d, %d\n" \
			"bodyMap1GainLUT_x:%d, %d, %d, %d\n" \
			"bodyMap1GainLUT_y:%d, %d, %d, %d\n" \
			"textMap1GainLUT_x:%d, %d, %d, %d\n" \
			"textMap1GainLUT_y:%d, %d, %d, %d\n" \
			"motionMap1GainLUT_x:%d, %d, %d, %d\n"\
			"motionMap1GainLUT_y:%d, %d, %d, %d\n",\
			vspcc_param.win_id, \
			vspcc_param.headMap0Gain, \ 
			vspcc_param.bodyMap0Gain, \ 
			vspcc_param.textMap0Gain, \ 
			vspcc_param.motionMap0Gain, \
			vspcc_param.headMap1Gain, \
			vspcc_param.bodyMap1Gain, \
			vspcc_param.textMap1Gain, \
			vspcc_param.motionMap1Gain, \
			vspcc_param.headMap0GainLUT_x[0], vspcc_param.headMap0GainLUT_x[1], vspcc_param.headMap0GainLUT_x[2], vspcc_param.headMap0GainLUT_x[3], \
			vspcc_param.headMap0GainLUT_y[0], vspcc_param.headMap0GainLUT_y[1], vspcc_param.headMap0GainLUT_y[2], vspcc_param.headMap0GainLUT_y[3], \
			vspcc_param.bodyMap0GainLUT_x[0], vspcc_param.bodyMap0GainLUT_x[1], vspcc_param.bodyMap0GainLUT_x[2], vspcc_param.bodyMap0GainLUT_x[3], \
			vspcc_param.bodyMap0GainLUT_y[0], vspcc_param.bodyMap0GainLUT_y[1], vspcc_param.bodyMap0GainLUT_y[2], vspcc_param.bodyMap0GainLUT_y[3], \
			vspcc_param.textMap0GainLUT_x[0], vspcc_param.textMap0GainLUT_x[1], vspcc_param.textMap0GainLUT_x[2], vspcc_param.textMap0GainLUT_x[3], \
			vspcc_param.textMap0GainLUT_y[0], vspcc_param.textMap0GainLUT_y[1], vspcc_param.textMap0GainLUT_y[2], vspcc_param.textMap0GainLUT_y[3], \
			vspcc_param.motionMap0GainLUT_x[0], vspcc_param.motionMap0GainLUT_x[1], vspcc_param.motionMap0GainLUT_x[2], vspcc_param.motionMap0GainLUT_x[3], \
			vspcc_param.motionMap0GainLUT_y[0], vspcc_param.motionMap0GainLUT_y[1], vspcc_param.motionMap0GainLUT_y[2], vspcc_param.motionMap0GainLUT_y[3], \
			vspcc_param.headMap1GainLUT_x[0], vspcc_param.headMap1GainLUT_x[1], vspcc_param.headMap1GainLUT_x[2], vspcc_param.headMap1GainLUT_x[3], \
			vspcc_param.headMap1GainLUT_y[0], vspcc_param.headMap1GainLUT_y[1], vspcc_param.headMap1GainLUT_y[2], vspcc_param.headMap1GainLUT_y[3], \
			vspcc_param.bodyMap1GainLUT_x[0], vspcc_param.bodyMap1GainLUT_x[1], vspcc_param.bodyMap1GainLUT_x[2], vspcc_param.bodyMap1GainLUT_x[3], \
			vspcc_param.bodyMap1GainLUT_y[0], vspcc_param.bodyMap1GainLUT_y[1], vspcc_param.bodyMap1GainLUT_y[2], vspcc_param.bodyMap1GainLUT_y[3], \
			vspcc_param.textMap1GainLUT_x[0], vspcc_param.textMap1GainLUT_x[1], vspcc_param.textMap1GainLUT_x[2], vspcc_param.textMap1GainLUT_x[3], \
			vspcc_param.textMap1GainLUT_y[0], vspcc_param.textMap1GainLUT_y[1], vspcc_param.textMap1GainLUT_y[2], vspcc_param.textMap1GainLUT_y[3], \
			vspcc_param.motionMap1GainLUT_x[0], vspcc_param.motionMap1GainLUT_x[1], vspcc_param.motionMap1GainLUT_x[2], vspcc_param.motionMap1GainLUT_x[3], \
			vspcc_param.motionMap1GainLUT_y[0], vspcc_param.motionMap1GainLUT_y[1], vspcc_param.motionMap1GainLUT_y[2], vspcc_param.motionMap1GainLUT_y[3]);

		ret = PE_CMG_SetVspccCtrl2((void *)&vspcc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_CMG_SetVspccCtrl() \n", __F__, __L__);
	}

	return ret;
}

int vpq_hwrap_setcmdbdata_o24(unsigned char wId, struct v4l2_ext_cm_info *pCmInfo)
{
	int ret = RET_OK;
	vpq_hwrap_cm_db_t *pCmDb = NULL;
	//vpq_hwrap_info_t *pInfo = &_g_vpq_hwrap_info;
	//LX_PE_WIN_ID win_id = (wId == 0)? LX_PE_WIN_0 : LX_PE_WIN_1;
	UINT32 i, j;
	LX_PE_CMG_REGION_CTRL_T  gain_param;
	LX_PE_CMG_REGION_T		 ctrl_param;
	LX_PE_CMG_REGION_ENABLE_T en_param;
	LX_PE_CMG_CW_CTRL_T 	 cw_param;
	LX_PE_CMG_CW_GAIN_CTRL_T cw_gain_param;
	LX_PE_CMG_CW_TABLE_CTRL_T 	 cw_table_param;
	LX_PE_CMG_VSPCC_CTRL_T 	 vspcc_param;
	LX_PE_CMG_DSE_CTRL_T 	 dse_param;
	UINT32                   cw_region_sel = 0;
	__attribute__((unused)) static LX_PE_CMG_REGION_ALL_T total_cen_region;
	__attribute__((unused)) UINT32 region_num_param = 0;
	VPQ_HWRAP_CHECK_CODE(!pCmInfo, return ret, "Error. pCmInfo is null.\n");

	pCmDb = (vpq_hwrap_cm_db_t *)pCmInfo->dbInfo;

	PE_PRINT_CMG("[%s.%d][wid:%d] use_internal_cm_db: %d, pCmDb: 0x%p\n",
		__F__, __L__, wId, pCmInfo->use_internal_cm_db, pCmDb);
		memset(&en_param, 0x00, sizeof(en_param));
		VPQ_HWRAP_CHECK_CODE(!pCmInfo, return RET_ERROR, \
			"Error.[%s.%d] pCmInfo is null.\n", __F__, __L__);
		//gain_param.win_id = ctrl_param.win_id = total_cen_region.win_id = en_param.win_id= (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
		for (i = 0; i < VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
		{
			gain_param.win_id = ctrl_param.win_id = en_param.win_id= (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
			gain_param.dynamic_ui = pCmInfo->uiInfo.dynamic.value;
			/* 1. set region gain */
			if(pCmDb->region_gain[i].needUpdate)
			{
				gain_param.region_num = pCmDb->region_gain[i].regionNum;
				for (j = 0; j < LX_PE_CMG_DELTANUM; j++)
				{
					gain_param.region_delta[j] = pCmDb->region_gain[i].delta[j];
				}
				gain_param.master_gain = pCmDb->region_gain[i].masterGain;

				//PE_PRINT_CMG("[%s.%d] ui :%d\n", __F__, __L__, uFcVal);
				PE_PRINT_CMG(" ----------------------------------------\n");
				PE_PRINT_CMG(" path:%d\n num:%d, m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n", \
					gain_param.win_id, gain_param.region_num, gain_param.master_gain, \
					gain_param.region_delta[0], gain_param.region_delta[1], \
					gain_param.region_delta[2], gain_param.region_delta[3], \
					gain_param.region_delta[4], gain_param.region_delta[5]);
				PE_PRINT_CMG(" ----------------------------------------\n");
				if(PE_KDRV_VER_O20)
				{
					ret = KWRAP_PE_SetCenRgnGainParam((void *)&gain_param);
				}
				else
				{
					ret = PE_CMG_SetCenRegionCtrl(&gain_param);
				}
				VPQ_HWRAP_CHECK_CODE(ret, return ret, \
					"Error.[%s.%d] PE_CMG_SetCenRegionCtrl() \n", __F__, __L__);
			}

			/* 2. set region ctrl */
			if(pCmDb->region_ctrl[i].needUpdate)
			{
				ctrl_param.region_num = pCmDb->region_ctrl[i].regionNum;
				en_param.enable[i]= pCmDb->region_ctrl[i].region_en;

				PE_PRINT_CMG(" ----------------------------------------\n");
				PE_PRINT_CMG(" path:%d\n num:%d, en %d\n",\
					ctrl_param.win_id, ctrl_param.region_num, en_param.enable[i]);
				for (j = 0; j < LX_PE_CMG_TBLPOINT; j++)
				{
					ctrl_param.hue_x[j] = VPQ_HWRAP_CONV_DEGREE_TO_10BIT(pCmDb->region_ctrl[i].hue_x[j]);
					ctrl_param.hue_g[j] = pCmDb->region_ctrl[i].hue_g[j];
					ctrl_param.sat_x[j] = VPQ_HWRAP_CONV_PERCENT_TO_8BIT(pCmDb->region_ctrl[i].sat_x[j]);
					ctrl_param.sat_g[j] = pCmDb->region_ctrl[i].sat_g[j];
					ctrl_param.val_x[j] = pCmDb->region_ctrl[i].val_x[j];
					ctrl_param.val_g[j] = pCmDb->region_ctrl[i].val_g[j];

					PE_PRINT_CMG("tblpint[%d] hue_x/g:%d,%d, sat_x/g:%d,%d, val_x/g:%d,%d\n", \
						j, ctrl_param.hue_x[j],ctrl_param.hue_g[j],ctrl_param.sat_x[j],\
						ctrl_param.sat_g[j],ctrl_param.val_x[j],ctrl_param.val_g[j]);
				}
				PE_PRINT_CMG(" ----------------------------------------\n");
				if(PE_KDRV_VER_O20)
				{
				ret = KWRAP_PE_SetCenRgnParam(&ctrl_param);
				}
				else
				{
				ret = PE_CMG_SetCenRegion(&ctrl_param);
				}
				VPQ_HWRAP_CHECK_CODE(ret, return ret, \
					"Error.[%s.%d] PE_CMG_SetCenRegion() \n", __F__, __L__);

				if(PE_KDRV_VER_O20)
				{
					ret = KWRAP_PE_SetCenRgnEnable(&en_param);
				}
				else
				{
					ret = PE_CMG_SetCenRegionEnable(&en_param);
				}
				VPQ_HWRAP_CHECK_CODE(ret, return ret, \
					"Error.[%s.%d] PE_CMG_SetCenRegionEnable() \n", __F__, __L__);
			}
		}
		/*3 clear white*/
		PE_PRINT_CMG("clear white needUpdate:%d n",pCmDb->clear_white.needUpdate);
		if(pCmDb->clear_white.needUpdate)
		{
			memset(&cw_param, 0x00, sizeof(cw_param));
			cw_param.win_id = cw_gain_param.win_id= cw_table_param.win_id =(wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
			cw_param.cw_en= (UINT32)pCmDb->clear_white.cw_en;
			cw_param.gain_sel = (UINT32)pCmDb->clear_white.cw_sel;
			for (i=0; i<VPQ_HWRAP_CM_RGN_CTRL_NUM; i++)
			{
				cw_region_sel |= (UINT32)(pCmDb->clear_white.color_region_onoff[i]<<i);
			}
			cw_param.region_sel = cw_region_sel;
			cw_param.region_gain= (UINT32)pCmDb->clear_white.color_region_gain;
			if(PE_KDRV_VER_O20)
			{
				ret = KWRAP_PE_SetClearWhiteParam(&cw_param);
			}
			else
			{
				ret = PE_CMG_SetClearWhiteCtrl(&cw_param);
			}
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_CMG_SetClearWhiteCtrl() \n", __F__, __L__);

			cw_gain_param.r_gain = (pCmDb->clear_white.gain_r>VPQ_HWRAP_CW_GAIN_MAX)? \
				VPQ_HWRAP_CW_GAIN_MAX:pCmDb->clear_white.gain_r;
			cw_gain_param.g_gain = (pCmDb->clear_white.gain_g>VPQ_HWRAP_CW_GAIN_MAX)? \
				VPQ_HWRAP_CW_GAIN_MAX:pCmDb->clear_white.gain_g;
			cw_gain_param.b_gain = (pCmDb->clear_white.gain_b>VPQ_HWRAP_CW_GAIN_MAX)? \
				VPQ_HWRAP_CW_GAIN_MAX:pCmDb->clear_white.gain_b;
			if(PE_KDRV_VER_O20)
			{
				ret = KWRAP_PE_SetClearWhiteGainParam(&cw_gain_param);
			}
			else
			{
				ret = PE_CMG_SetClearWhiteGainCtrl(&cw_gain_param);
			}
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_CMG_SetClearWhiteGainCtrl() \n", __F__, __L__);
			#if 0
			printk(\
				" hue_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" hue_y: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" sat_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" sat_y: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" val_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" val_y: %d, %d, %d, %d, %d, %d, %d, %d,\n", \
				pCmDb->clear_white.cw_hue_x[0], pCmDb->clear_white.cw_hue_x[1], pCmDb->clear_white.cw_hue_x[2], pCmDb->clear_white.cw_hue_x[3], \
				pCmDb->clear_white.cw_hue_x[4], pCmDb->clear_white.cw_hue_x[5], pCmDb->clear_white.cw_hue_x[6], pCmDb->clear_white.cw_hue_x[7], \
				pCmDb->clear_white.cw_hue_y[0], pCmDb->clear_white.cw_hue_y[1], pCmDb->clear_white.cw_hue_y[2], pCmDb->clear_white.cw_hue_y[3], \
				pCmDb->clear_white.cw_hue_y[4], pCmDb->clear_white.cw_hue_y[5], pCmDb->clear_white.cw_hue_y[6], pCmDb->clear_white.cw_hue_y[7], \
				pCmDb->clear_white.cw_sat_x[0], pCmDb->clear_white.cw_sat_x[1], pCmDb->clear_white.cw_sat_x[2], pCmDb->clear_white.cw_sat_x[3], \
				pCmDb->clear_white.cw_sat_x[4], pCmDb->clear_white.cw_sat_x[5], pCmDb->clear_white.cw_sat_x[6], pCmDb->clear_white.cw_sat_x[7], \
				pCmDb->clear_white.cw_sat_y[0], pCmDb->clear_white.cw_sat_y[1], pCmDb->clear_white.cw_sat_y[2], pCmDb->clear_white.cw_sat_y[3], \
				pCmDb->clear_white.cw_sat_y[4], pCmDb->clear_white.cw_sat_y[5], pCmDb->clear_white.cw_sat_y[6], pCmDb->clear_white.cw_sat_y[7], \
				pCmDb->clear_white.cw_val_x[0], pCmDb->clear_white.cw_val_x[1], pCmDb->clear_white.cw_val_x[2], pCmDb->clear_white.cw_val_x[3], \
				pCmDb->clear_white.cw_val_x[4], pCmDb->clear_white.cw_val_x[5], pCmDb->clear_white.cw_val_x[6], pCmDb->clear_white.cw_val_x[7], \
				pCmDb->clear_white.cw_val_y[0], pCmDb->clear_white.cw_val_y[1], pCmDb->clear_white.cw_val_y[2], pCmDb->clear_white.cw_val_y[3], \
				pCmDb->clear_white.cw_val_y[4], pCmDb->clear_white.cw_val_y[5], pCmDb->clear_white.cw_val_y[6], pCmDb->clear_white.cw_val_y[7]);
			#endif
			memcpy(&(cw_table_param.cw_hue_x),&(pCmDb->clear_white.cw_hue_x) ,sizeof(unsigned short)*VPQ_HWRAP_CM_TBLPOINT );
			memcpy(&(cw_table_param.cw_hue_y),&(pCmDb->clear_white.cw_hue_y) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
			memcpy(&(cw_table_param.cw_sat_x),&(pCmDb->clear_white.cw_sat_x) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
			memcpy(&(cw_table_param.cw_sat_y),&(pCmDb->clear_white.cw_sat_y) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
			memcpy(&(cw_table_param.cw_val_x),&(pCmDb->clear_white.cw_val_x) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
			memcpy(&(cw_table_param.cw_val_y),&(pCmDb->clear_white.cw_val_y) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT  );
			if(PE_KDRV_VER_O20)
			{
				ret = KWRAP_PE_SetClearWhiteTableParam(&cw_table_param);
			}
			else
			{
				ret = PE_CMG_SetClearWhiteTableCtrl(&cw_table_param);
			}
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_CMG_SetClearWhiteTableCtrl() \n", __F__, __L__);
		}
		PE_PRINT_CMG("dse needUpdate:%d n",pCmDb->cm_dse.needUpdate);
		/*4 dse*/
		if(pCmDb->cm_dse.needUpdate)
		{
			memset(&dse_param, 0x00, sizeof(dse_param));
			dse_param.win_id = (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
			dse_param.saturation_cr_mode     = pCmDb->cm_dse.saturation_cr_mode;
			dse_param.saturation_region_gain = pCmDb->cm_dse.saturation_region_gain;
			memcpy(&(dse_param.dse_h_x),&(pCmDb->cm_dse.dse_h_x) ,sizeof(UINT16)*LX_PE_CMG_TBLPOINT);
			memcpy(&(dse_param.dse_h_y),&(pCmDb->cm_dse.dse_h_y) ,sizeof(UINT16)*LX_PE_CMG_TBLPOINT);
			memcpy(&(dse_param.dse_y_x),&(pCmDb->cm_dse.dse_y_x) ,sizeof(UINT16)*LX_PE_CMG_TBLPOINT);
			memcpy(&(dse_param.dse_y_y),&(pCmDb->cm_dse.dse_y_y) ,sizeof(UINT16)*LX_PE_CMG_TBLPOINT);
			memcpy(&(dse_param.sSaturationLUT_x),&(pCmDb->cm_dse.sSaturationLUT_x) ,sizeof(UINT16)*16);
			memcpy(&(dse_param.sSaturationLUT_y),&(pCmDb->cm_dse.sSaturationLUT_y) ,sizeof(UINT16)*16);
			memcpy(&(dse_param.region_onoff),&(pCmDb->cm_dse.region_onoff) ,sizeof(UINT8)*LX_PE_CMG_REGION_NUM);
			PE_PRINT_CMG("set: saturation_cr_mode:%d, saturation_region_gain:%d\n"\
				"region sel:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
				dse_param.saturation_cr_mode, dse_param.saturation_region_gain, \
				dse_param.region_onoff[0],dse_param.region_onoff[1],dse_param.region_onoff[2],dse_param.region_onoff[3],\
				dse_param.region_onoff[4],dse_param.region_onoff[5],dse_param.region_onoff[6],dse_param.region_onoff[7],\
				dse_param.region_onoff[8],dse_param.region_onoff[9],dse_param.region_onoff[10],dse_param.region_onoff[11],\
				dse_param.region_onoff[12],dse_param.region_onoff[13],dse_param.region_onoff[14],dse_param.region_onoff[15]);
			PE_PRINT_CMG("set dse_gain: n"\
				"dse_gain_h_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_h_y:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_y_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_y_y:%d,%d,%d,%d,%d,%d,%d,%d\n", \
				dse_param.dse_h_x[0],dse_param.dse_h_x[1],dse_param.dse_h_x[2],dse_param.dse_h_x[3],\
				dse_param.dse_h_x[4],dse_param.dse_h_x[5],dse_param.dse_h_x[6],dse_param.dse_h_x[7],\
				dse_param.dse_h_y[0],dse_param.dse_h_y[1],dse_param.dse_h_y[2],dse_param.dse_h_y[3],\
				dse_param.dse_h_y[4],dse_param.dse_h_y[5],dse_param.dse_h_y[6],dse_param.dse_h_y[7],\
				dse_param.dse_y_x[0],dse_param.dse_y_x[1],dse_param.dse_y_x[2],dse_param.dse_y_x[3],\
				dse_param.dse_y_x[4],dse_param.dse_y_x[5],dse_param.dse_y_x[6],dse_param.dse_y_x[7],\
				dse_param.dse_y_y[0],dse_param.dse_y_y[1],dse_param.dse_y_y[2],dse_param.dse_y_y[3],\
				dse_param.dse_y_y[4],dse_param.dse_y_y[5],dse_param.dse_y_y[6],dse_param.dse_y_y[7]);
			if(PE_KDRV_VER_O20)
			{
				ret = KWRAP_PE_SetDseParam(&dse_param);
			}
			else
			{
				ret = PE_CMG_SetDseCtrl(&dse_param);
			}
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_CMG_SetDseCtrl() \n", __F__, __L__);
		}
		/*5 vspcc*/
		if(pCmDb->cm_vspcc.needUpdate)
		{
			memset(&vspcc_param, 0x00, sizeof(vspcc_param));
			vspcc_param.win_id = (wId == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
			vspcc_param.satTarget = pCmDb->cm_vspcc.satTarget;
			memcpy(&(vspcc_param.objMapGainLUT_x),&(pCmDb->cm_vspcc.objMapGainLUT_x) ,sizeof(unsigned char)*4 );
			memcpy(&(vspcc_param.objMapGainLUT_y),&(pCmDb->cm_vspcc.objMapGainLUT_y) ,sizeof(unsigned char)*4 );
			memcpy(&(vspcc_param.faceMapGainLUT_x),&(pCmDb->cm_vspcc.faceMapGainLUT_x) ,sizeof(unsigned char)*4 );
			memcpy(&(vspcc_param.faceMapGainLUT_y),&(pCmDb->cm_vspcc.faceMapGainLUT_y) ,sizeof(unsigned char)*4 );
			memcpy(&(vspcc_param.hue_g),&(pCmDb->cm_vspcc.hue_g) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT );
			memcpy(&(vspcc_param.hue_x),&(pCmDb->cm_vspcc.hue_x) ,sizeof(unsigned short)*VPQ_HWRAP_CM_TBLPOINT );
			memcpy(&(vspcc_param.sat_g),&(pCmDb->cm_vspcc.sat_g) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT );
			memcpy(&(vspcc_param.sat_x),&(pCmDb->cm_vspcc.sat_x) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT );
			memcpy(&(vspcc_param.val_g),&(pCmDb->cm_vspcc.val_g) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT );
			memcpy(&(vspcc_param.val_x),&(pCmDb->cm_vspcc.val_x) ,sizeof(unsigned char)*VPQ_HWRAP_CM_TBLPOINT );
			
			PE_PRINT_CMG("set[%d] \n"\
				"satTarget : %d\n" \
				"objMapGainLUT_x : %d, %d, %d, %d" \
				"objMapGainLUT_y : %d, %d, %d, %d" \
				"faceMapGainLUT_x : %d, %d, %d, %d" \
				"faceMapGainLUT_y : %d, %d, %d, %d" \
				" hue_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" hue_g: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" sat_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" sat_g: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" val_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
				" val_g: %d, %d, %d, %d, %d, %d, %d, %d,\n", \
				vspcc_param.win_id, \
				vspcc_param.satTarget,\
				vspcc_param.objMapGainLUT_x[0],vspcc_param.objMapGainLUT_x[1],vspcc_param.objMapGainLUT_x[2],vspcc_param.objMapGainLUT_x[3],\
				vspcc_param.objMapGainLUT_y[0],vspcc_param.objMapGainLUT_y[1],vspcc_param.objMapGainLUT_y[2],vspcc_param.objMapGainLUT_y[3],\
				vspcc_param.faceMapGainLUT_x[0],vspcc_param.faceMapGainLUT_x[1],vspcc_param.faceMapGainLUT_x[2],vspcc_param.faceMapGainLUT_x[3],\
				vspcc_param.faceMapGainLUT_y[0],vspcc_param.faceMapGainLUT_y[1],vspcc_param.faceMapGainLUT_y[2],vspcc_param.faceMapGainLUT_y[3],\
				vspcc_param.hue_x[0], vspcc_param.hue_x[1], vspcc_param.hue_x[2], vspcc_param.hue_x[3], \
				vspcc_param.hue_x[4], vspcc_param.hue_x[5], vspcc_param.hue_x[6], vspcc_param.hue_x[7], \
				vspcc_param.hue_g[0], vspcc_param.hue_g[1], vspcc_param.hue_g[2], vspcc_param.hue_g[3], \
				vspcc_param.hue_g[4], vspcc_param.hue_g[5], vspcc_param.hue_g[6], vspcc_param.hue_g[7], \
				vspcc_param.sat_x[0], vspcc_param.sat_x[1], vspcc_param.sat_x[2], vspcc_param.sat_x[3], \
				vspcc_param.sat_x[4], vspcc_param.sat_x[5], vspcc_param.sat_x[6], vspcc_param.sat_x[7], \
				vspcc_param.sat_g[0], vspcc_param.sat_g[1], vspcc_param.sat_g[2], vspcc_param.sat_g[3], \
				vspcc_param.sat_g[4], vspcc_param.sat_g[5], vspcc_param.sat_g[6], vspcc_param.sat_g[7], \
				vspcc_param.val_x[0], vspcc_param.val_x[1], vspcc_param.val_x[2], vspcc_param.val_x[3], \
				vspcc_param.val_x[4], vspcc_param.val_x[5], vspcc_param.val_x[6], vspcc_param.val_x[7], \
				vspcc_param.val_g[0], vspcc_param.val_g[1], vspcc_param.val_g[2], vspcc_param.val_g[3], \
				vspcc_param.val_g[4], vspcc_param.val_g[5], vspcc_param.val_g[6], vspcc_param.val_g[7]);
			if(PE_KDRV_VER_O20)
			{
				ret = KWRAP_PE_SetVspccParam((void *)&vspcc_param);
			}
			else if(!PE_KDRV_VER_O26)
			{
				ret = PE_CMG_SetVspccCtrl((void *)&vspcc_param);
			}
			VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_CMG_SetVspccCtrl() \n", __F__, __L__);
		}

	return ret;
}


int vpq_hwrap_setdynamiccontrast(struct v4l2_ext_dynamnic_contrast_ctrl *pDynamicContrast)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	//UINT32 i=0, region_select=0;
	UINT32 pic_mode =0;
	vpq_hwrap_dc_dynamic_t *p_dyn_data2 = NULL; 

	VPQ_HWRAP_CHECK_CODE(!pDynamicContrast, return RET_ERROR, "Error. pstDynamicContrast is null.\n");

	p_dyn_data2 = (vpq_hwrap_dc_dynamic_t *)(pDynamicContrast->pst_chip_data);
	win_id = LX_PE_WIN_0;
	pic_mode = p_dyn_data2->picture_mode;
	PE_PRINT_DCM("[%s.%d]wId:%d, uDcVal:%d\n", __F__, __L__, win_id, pDynamicContrast->uDcVal);

	/*4. DRC */
	{
		LX_PE_DCM_DRC_MODE_T drc_param;
		drc_param.win_id = win_id;
		ret = PE_DCM_GetDceDrcMode(&drc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_DCM_GetDceDrcMode() \n", __F__, __L__);
		drc_param.dc_mode = (UINT32)pDynamicContrast->uDcVal;
		drc_param.picture_mode = pic_mode;
		PE_PRINT_DCM("[%s.%d] set[%d] drc_mode[%d], drc_md,byps,sc_cnt:%d,%d,%d, pic_mode:0x%08x\n", \
			__F__, __L__, drc_param.win_id, pDynamicContrast->uDcVal, \
			drc_param.dc_mode, drc_param.dc_bypass, drc_param.dc_sc_cnt,drc_param.picture_mode);
		ret = PE_DCM_SetDceDrcMode(&drc_param);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_DCM_SetDceDrcMode() \n", __F__, __L__);
	}
	/*5. set DSE control */
	{
		LX_PE_DCM_DSE_CTRL3_T dse_ctrl_param;
		dse_ctrl_param.win_id = win_id;
		dse_ctrl_param.chroma_gain_en = p_dyn_data2->chroma_gain_en;
		dse_ctrl_param.chroma_chr_gain1  = p_dyn_data2->chroma_chr_gain1;
		dse_ctrl_param.chroma_chr_gain2  = p_dyn_data2->chroma_chr_gain2;
		dse_ctrl_param.chroma_chr_alpha1 = p_dyn_data2->chroma_chr_alpha1;
		dse_ctrl_param.chroma_chr_alpha2 = p_dyn_data2->chroma_chr_alpha2;
		dse_ctrl_param.dtm_hue_gain   = p_dyn_data2->dtm_hue_gain;
		dse_ctrl_param.dtm_sat_gain   = p_dyn_data2->dtm_sat_gain;
		ret = PE_DCM_SetDseCtrl((void *)&dse_ctrl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_DCM_SetDseCtrl() \n", __F__, __L__);
	}
	return ret;
}

int vpq_hwrap_setdynamiccontrast_webos60(struct v4l2_ext_dynamnic_contrast_ctrl *pDynamicContrast)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	//UINT32 i=0, region_select=0;
	UINT32 pic_mode =0;
	vpq_hwrap_dc_dynamic_webos60_t *p_dyn_data2 = NULL;
	LX_PE_DCM_DRC_MODE_T drc_param;
	LX_PE_DCM_DSE_CTRL4_T dse_ctrl_param;

	VPQ_HWRAP_CHECK_CODE(!pDynamicContrast, return RET_ERROR, "Error. pstDynamicContrast is null.\n");

	p_dyn_data2 = (vpq_hwrap_dc_dynamic_webos60_t *)(pDynamicContrast->pst_chip_data);
	win_id = LX_PE_WIN_0;
	pic_mode = p_dyn_data2->picture_mode;
	PE_PRINT_DCM("[%s.%d]wId:%d, uDcVal:%d\n", __F__, __L__, win_id, pDynamicContrast->uDcVal);

	/*4. DRC */
	drc_param.win_id = win_id;
	if (PE_KDRV_VER_O20)
	{
	        ret = KWRAP_PE_GetCurDceDrcMode((void *)&drc_param);
	}
	else
	{
	       ret = PE_DCM_GetDceDrcMode(&drc_param);
	}
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_DCM_GetDceDrcMode() \n", __F__, __L__);
	drc_param.dc_mode = (UINT32)pDynamicContrast->uDcVal;
	drc_param.picture_mode = pic_mode;
	PE_PRINT_DCM("[%s.%d] set[%d] drc_mode[%d], drc_md,byps,sc_cnt:%d,%d,%d, pic_mode:0x%08x\n", \
		__F__, __L__, drc_param.win_id, pDynamicContrast->uDcVal, \
		drc_param.dc_mode, drc_param.dc_bypass, drc_param.dc_sc_cnt,drc_param.picture_mode);
	if (PE_KDRV_VER_O20)
	{
		ret = KWRAP_PE_SetDceDrcMode((void *)&drc_param);
	}
	else
	{
		ret = PE_DCM_SetDceDrcMode(&drc_param);
	}
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] KWRAP_PE_SetDceDrcMode() \n", __F__, __L__);
	/*5. set DSE control */
	dse_ctrl_param.win_id = win_id;
	dse_ctrl_param.chroma_gain_en  = p_dyn_data2->chroma_gain_en;
	dse_ctrl_param.chroma_cb_gain1 = p_dyn_data2->chroma_cb_gain1;
	dse_ctrl_param.chroma_cb_gain2 = p_dyn_data2->chroma_cb_gain2;
	dse_ctrl_param.chroma_cr_gain1 = p_dyn_data2->chroma_cr_gain1;
	dse_ctrl_param.chroma_cr_gain2 = p_dyn_data2->chroma_cr_gain2;
	dse_ctrl_param.chroma_alpha1   = p_dyn_data2->chroma_alpha1;
	dse_ctrl_param.chroma_alpha2   = p_dyn_data2->chroma_alpha2;
	dse_ctrl_param.dtm_hue_gain    = p_dyn_data2->dtm_hue_gain;
	dse_ctrl_param.dtm_sat_gain    = p_dyn_data2->dtm_sat_gain;
	PE_PRINT_DSE("[%s.%d] set[%d]chroma_gain_en:%d\n"\
		"chroma_cb_gain1:%d,chroma_cb_gain2:%d,chroma_cr_gain1:%d,chroma_cr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
		"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
		__F__, __L__, drc_param.win_id,dse_ctrl_param.chroma_gain_en, \
		dse_ctrl_param.chroma_cb_gain1,dse_ctrl_param.chroma_cb_gain2,\
		dse_ctrl_param.chroma_cr_gain1,dse_ctrl_param.chroma_cr_gain2,\
		dse_ctrl_param.chroma_alpha1,dse_ctrl_param.chroma_alpha2,\
		dse_ctrl_param.dtm_hue_gain,dse_ctrl_param.dtm_sat_gain);
	if (PE_KDRV_VER_O20||PE_KDRV_VER_E60)
	{
		ret = PE_DCM_SetDseCtrl2((void *)&dse_ctrl_param);
		VPQ_HWRAP_CHECK_CODE(ret, return ret, \
				"Error.[%s.%d] PE_DCM_SetDseCtrl2() \n", __F__, __L__);
	}
	return ret;
}
int vpq_hwrap_setdynamiccontrast_weboso26(struct v4l2_ext_dynamnic_contrast_ctrl *pDynamicContrast)
{
	int ret = RET_OK;
	int i;
	LX_PE_WIN_ID win_id;
	//UINT32 i=0, region_select=0;
	UINT32 pic_mode =0;
	vpq_hwrap_dc_dynamic_weboso26_t *p_dyn_data2 = NULL;
	LX_PE_DCM_DRC_MODE_T drc_param;
	LX_PE_DCM_DSE_CTRL6_T dse_ctrl_param;

	VPQ_HWRAP_CHECK_CODE(!pDynamicContrast, return RET_ERROR, "Error. pstDynamicContrast is null.\n");

	p_dyn_data2 = (vpq_hwrap_dc_dynamic_weboso26_t *)(pDynamicContrast->pst_chip_data);
	win_id = LX_PE_WIN_0;
	pic_mode = p_dyn_data2->picture_mode;
	PE_PRINT_DCM("[%s.%d]wId:%d, uDcVal:%d\n", __F__, __L__, win_id, pDynamicContrast->uDcVal);

	/*4. DRC */
	drc_param.win_id = win_id;
	ret = PE_DCM_GetDceDrcMode(&drc_param);
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_DCM_GetDceDrcMode() \n", __F__, __L__);
	drc_param.picture_mode = pic_mode;
	if (_g_vpq_hwrap_info.year_option == 22)// for O22, webos22
	{
		drc_param.dc_mode = (UINT32)pDynamicContrast->uDcVal;
		drc_param.db_type = LX_PE_DRC_UI_PICM;
	}
	else //for O22N, M23, webos23
	{
		drc_param.db_type = LX_PE_DRC_PIC_MODE;
	}
	PE_PRINT_DCM("[%s.%d] set[%d] drc_mode[%d], drc_md,byps,sc_cnt:%d,%d,%d, pic_mode:0x%08x\n", \
		__F__, __L__, drc_param.win_id, pDynamicContrast->uDcVal, \
		drc_param.dc_mode, drc_param.dc_bypass, drc_param.dc_sc_cnt,drc_param.picture_mode);
	ret = PE_DCM_SetDceDrcMode(&drc_param);
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_DCM_SetDceDrcMode() \n", __F__, __L__);
	/*5. set DSE control */
	dse_ctrl_param.win_id = win_id;
	dse_ctrl_param.chroma_gain_en  = p_dyn_data2->chroma_gain_en;
	dse_ctrl_param.chroma_cb_gain1 = p_dyn_data2->chroma_cb_gain1;
	dse_ctrl_param.chroma_cb_gain2 = p_dyn_data2->chroma_cb_gain2;
	dse_ctrl_param.chroma_cr_gain1 = p_dyn_data2->chroma_cr_gain1;
	dse_ctrl_param.chroma_cr_gain2 = p_dyn_data2->chroma_cr_gain2;
	dse_ctrl_param.chroma_alpha1   = p_dyn_data2->chroma_alpha1;
	dse_ctrl_param.chroma_alpha2   = p_dyn_data2->chroma_alpha2;
	for(i =0 ; i < 8 ; i++)
	{
		dse_ctrl_param.luma_gain_x[i]    = p_dyn_data2->luma_gain_x[i];
		dse_ctrl_param.luma_gain_y[i]    = p_dyn_data2->luma_gain_y[i];
		dse_ctrl_param.sat_gain_x[i]     = p_dyn_data2->sat_gain_x[i];
		dse_ctrl_param.sat_gain_y[i]     = p_dyn_data2->sat_gain_y[i];
		dse_ctrl_param.dtm_hue_gain_x[i] = p_dyn_data2->dtm_hue_gain_x[i];
		dse_ctrl_param.dtm_hue_gain_y[i] = p_dyn_data2->dtm_hue_gain_y[i];
		dse_ctrl_param.dtm_sat_gain_x[i] = p_dyn_data2->dtm_sat_gain_x[i];
		dse_ctrl_param.dtm_sat_gain_y[i] = p_dyn_data2->dtm_sat_gain_y[i];
		dse_ctrl_param.dtm_val_gain_x[i] = p_dyn_data2->dtm_val_gain_x[i];
		dse_ctrl_param.dtm_val_gain_y[i] = p_dyn_data2->dtm_val_gain_y[i];
	}
	dse_ctrl_param.dtm_hue_gain    = p_dyn_data2->dtm_hue_gain;
	dse_ctrl_param.dtm_sat_gain    = p_dyn_data2->dtm_sat_gain;
	dse_ctrl_param.dtm_target_hue_gain    = p_dyn_data2->dtm_target_hue_gain;
	dse_ctrl_param.dtm_target_sat_gain    = p_dyn_data2->dtm_target_sat_gain;
	PE_PRINT_DSE("[%s.%d] set[%d]chroma_gain_en:%u\n"\
		"chroma_cb_gain1:%d,chroma_cb_gain2:%d,chroma_cr_gain1:%d,chroma_cr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
		"dtm_hue_gain:%d,dtm_sat_gain: %d\n" \
		"dtm_target_hue_gain:%d,dtm_target_sat_gain: %d\n" \
		"luma_x:   %d,%d,%d,%d,%d,%d,%d,%d luma_y:   %d,%d,%d,%d,%d,%d,%d,%d\n"\
		"sat_x :   %d,%d,%d,%d,%d,%d,%d,%d sat_y:    %d,%d,%d,%d,%d,%d,%d,%d\n"\
		"dtm_hue_x:%d,%d,%d,%d,%d,%d,%d,%d dtm_hue_y:%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"dtm_sat_x:%d,%d,%d,%d,%d,%d,%d,%d dtm_sat_y:%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"dtm_val_x:%d,%d,%d,%d,%d,%d,%d,%d dtm_val_y:%d,%d,%d,%d,%d,%d,%d,%d\n",\
		__F__, __L__, drc_param.win_id,dse_ctrl_param.chroma_gain_en, \
		dse_ctrl_param.chroma_cb_gain1,dse_ctrl_param.chroma_cb_gain2,\
		dse_ctrl_param.chroma_cr_gain1,dse_ctrl_param.chroma_cr_gain2,\
		dse_ctrl_param.chroma_alpha1,dse_ctrl_param.chroma_alpha2,\
		dse_ctrl_param.dtm_hue_gain,dse_ctrl_param.dtm_sat_gain,\
		dse_ctrl_param.dtm_target_hue_gain,dse_ctrl_param.dtm_target_sat_gain,\
		dse_ctrl_param.luma_gain_x[0],dse_ctrl_param.luma_gain_x[1],dse_ctrl_param.luma_gain_x[2],dse_ctrl_param.luma_gain_x[3],\
		dse_ctrl_param.luma_gain_x[4],dse_ctrl_param.luma_gain_x[5],dse_ctrl_param.luma_gain_x[6],dse_ctrl_param.luma_gain_x[7],\
		dse_ctrl_param.luma_gain_y[0],dse_ctrl_param.luma_gain_y[1],dse_ctrl_param.luma_gain_y[2],dse_ctrl_param.luma_gain_y[3],\
		dse_ctrl_param.luma_gain_y[4],dse_ctrl_param.luma_gain_y[5],dse_ctrl_param.luma_gain_y[6],dse_ctrl_param.luma_gain_y[7],\
		dse_ctrl_param.sat_gain_x[0],dse_ctrl_param.sat_gain_x[1],dse_ctrl_param.sat_gain_x[2],dse_ctrl_param.sat_gain_x[3],\
		dse_ctrl_param.sat_gain_x[4],dse_ctrl_param.sat_gain_x[5],dse_ctrl_param.sat_gain_x[6],dse_ctrl_param.sat_gain_x[7],\
		dse_ctrl_param.sat_gain_y[0],dse_ctrl_param.sat_gain_y[1],dse_ctrl_param.sat_gain_y[2],dse_ctrl_param.sat_gain_y[3],\
		dse_ctrl_param.sat_gain_y[4],dse_ctrl_param.sat_gain_y[5],dse_ctrl_param.sat_gain_y[6],dse_ctrl_param.sat_gain_y[7],\
		dse_ctrl_param.dtm_hue_gain_x[0],dse_ctrl_param.dtm_hue_gain_x[1],dse_ctrl_param.dtm_hue_gain_x[2],dse_ctrl_param.dtm_hue_gain_x[3],\
		dse_ctrl_param.dtm_hue_gain_x[4],dse_ctrl_param.dtm_hue_gain_x[5],dse_ctrl_param.dtm_hue_gain_x[6],dse_ctrl_param.dtm_hue_gain_x[7],\
		dse_ctrl_param.dtm_hue_gain_y[0],dse_ctrl_param.dtm_hue_gain_y[1],dse_ctrl_param.dtm_hue_gain_y[2],dse_ctrl_param.dtm_hue_gain_y[3],\
		dse_ctrl_param.dtm_hue_gain_y[4],dse_ctrl_param.dtm_hue_gain_y[5],dse_ctrl_param.dtm_hue_gain_y[6],dse_ctrl_param.dtm_hue_gain_y[7],\
		dse_ctrl_param.dtm_sat_gain_x[0],dse_ctrl_param.dtm_sat_gain_x[1],dse_ctrl_param.dtm_sat_gain_x[2],dse_ctrl_param.dtm_sat_gain_x[3],\
		dse_ctrl_param.dtm_sat_gain_x[4],dse_ctrl_param.dtm_sat_gain_x[5],dse_ctrl_param.dtm_sat_gain_x[6],dse_ctrl_param.dtm_sat_gain_x[7],\
		dse_ctrl_param.dtm_sat_gain_y[0],dse_ctrl_param.dtm_sat_gain_y[1],dse_ctrl_param.dtm_sat_gain_y[2],dse_ctrl_param.dtm_sat_gain_y[3],\
		dse_ctrl_param.dtm_sat_gain_y[4],dse_ctrl_param.dtm_sat_gain_y[5],dse_ctrl_param.dtm_sat_gain_y[6],dse_ctrl_param.dtm_sat_gain_y[7],\
		dse_ctrl_param.dtm_val_gain_x[0],dse_ctrl_param.dtm_val_gain_x[1],dse_ctrl_param.dtm_val_gain_x[2],dse_ctrl_param.dtm_val_gain_x[3],\
		dse_ctrl_param.dtm_val_gain_x[4],dse_ctrl_param.dtm_val_gain_x[5],dse_ctrl_param.dtm_val_gain_x[6],dse_ctrl_param.dtm_val_gain_x[7],\
		dse_ctrl_param.dtm_val_gain_y[0],dse_ctrl_param.dtm_val_gain_y[1],dse_ctrl_param.dtm_val_gain_y[2],dse_ctrl_param.dtm_val_gain_y[3],\
		dse_ctrl_param.dtm_val_gain_y[4],dse_ctrl_param.dtm_val_gain_y[5],dse_ctrl_param.dtm_val_gain_y[6],dse_ctrl_param.dtm_val_gain_y[7]);
	ret = PE_DCM_SetDseCtrl((void *)&dse_ctrl_param);
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_DCM_SetDseCtrl() \n", __F__, __L__);
	return ret;
}


int vpq_hwrap_setdynamiccontrast_weboso22(struct v4l2_ext_dynamnic_contrast_ctrl *pDynamicContrast)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	//UINT32 i=0, region_select=0;
	UINT32 pic_mode =0;
	vpq_hwrap_dc_dynamic_weboso22_t *p_dyn_data2 = NULL;
	LX_PE_DCM_DRC_MODE_T drc_param;
	LX_PE_DCM_DSE_CTRL5_T dse_ctrl_param;

	VPQ_HWRAP_CHECK_CODE(!pDynamicContrast, return RET_ERROR, "Error. pstDynamicContrast is null.\n");

	p_dyn_data2 = (vpq_hwrap_dc_dynamic_weboso22_t *)(pDynamicContrast->pst_chip_data);
	win_id = LX_PE_WIN_0;
	pic_mode = p_dyn_data2->picture_mode;
	PE_PRINT_DCM("[%s.%d]wId:%d, uDcVal:%d\n", __F__, __L__, win_id, pDynamicContrast->uDcVal);

	/*4. DRC */
	drc_param.win_id = win_id;
	ret = PE_DCM_GetDceDrcMode(&drc_param);
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_DCM_GetDceDrcMode() \n", __F__, __L__);
	drc_param.picture_mode = pic_mode;
	if (_g_vpq_hwrap_info.year_option == 22)// for O22, webos22
	{
		drc_param.dc_mode = (UINT32)pDynamicContrast->uDcVal;
		drc_param.db_type = LX_PE_DRC_UI_PICM;
	}
	else //for O22N, M23, webos23
	{
		drc_param.db_type = LX_PE_DRC_PIC_MODE;
	}
	PE_PRINT_DCM("[%s.%d] set[%d] drc_mode[%d], drc_md,byps,sc_cnt:%d,%d,%d, pic_mode:0x%08x\n", \
		__F__, __L__, drc_param.win_id, pDynamicContrast->uDcVal, \
		drc_param.dc_mode, drc_param.dc_bypass, drc_param.dc_sc_cnt,drc_param.picture_mode);
	ret = PE_DCM_SetDceDrcMode(&drc_param);
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_DCM_SetDceDrcMode() \n", __F__, __L__);
	/*5. set DSE control */
	dse_ctrl_param.win_id = win_id;
	dse_ctrl_param.chroma_gain_en  = p_dyn_data2->chroma_gain_en;
	dse_ctrl_param.chroma_cb_gain1 = p_dyn_data2->chroma_cb_gain1;
	dse_ctrl_param.chroma_cb_gain2 = p_dyn_data2->chroma_cb_gain2;
	dse_ctrl_param.chroma_cr_gain1 = p_dyn_data2->chroma_cr_gain1;
	dse_ctrl_param.chroma_cr_gain2 = p_dyn_data2->chroma_cr_gain2;
	dse_ctrl_param.chroma_alpha1   = p_dyn_data2->chroma_alpha1;
	dse_ctrl_param.chroma_alpha2   = p_dyn_data2->chroma_alpha2;
	dse_ctrl_param.luma_gain_x[0]  = p_dyn_data2->luma_gain_x[0];
	dse_ctrl_param.luma_gain_x[1]  = p_dyn_data2->luma_gain_x[1];
	dse_ctrl_param.luma_gain_x[2]  = p_dyn_data2->luma_gain_x[2];
	dse_ctrl_param.luma_gain_x[3]  = p_dyn_data2->luma_gain_x[3];
	dse_ctrl_param.luma_gain_y[0]  = p_dyn_data2->luma_gain_y[0];
	dse_ctrl_param.luma_gain_y[1]  = p_dyn_data2->luma_gain_y[1];
	dse_ctrl_param.luma_gain_y[2]  = p_dyn_data2->luma_gain_y[2];
	dse_ctrl_param.luma_gain_y[3]  = p_dyn_data2->luma_gain_y[3];
	dse_ctrl_param.sat_gain_x[0]  = p_dyn_data2->sat_gain_x[0];
	dse_ctrl_param.sat_gain_x[1]  = p_dyn_data2->sat_gain_x[1];
	dse_ctrl_param.sat_gain_x[2]  = p_dyn_data2->sat_gain_x[2];
	dse_ctrl_param.sat_gain_x[3]  = p_dyn_data2->sat_gain_x[3];
	dse_ctrl_param.sat_gain_y[0]  = p_dyn_data2->sat_gain_y[0];
	dse_ctrl_param.sat_gain_y[1]  = p_dyn_data2->sat_gain_y[1];
	dse_ctrl_param.sat_gain_y[2]  = p_dyn_data2->sat_gain_y[2];
	dse_ctrl_param.sat_gain_y[3]  = p_dyn_data2->sat_gain_y[3];
	dse_ctrl_param.dtm_hue_gain    = p_dyn_data2->dtm_hue_gain;
	dse_ctrl_param.dtm_sat_gain    = p_dyn_data2->dtm_sat_gain;
	PE_PRINT_DSE("[%s.%d] set[%d]chroma_gain_en:%d\n"\
		"chroma_cb_gain1:%d,chroma_cb_gain2:%d,chroma_cr_gain1:%d,chroma_cr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
		"luma_x:%d,%d,%d,%d luma_y:%d,%d,%d,%d\n"\
		"sat_x :%d,%d,%d,%d sat_y:%d,%d,%d,%d\n"\
		"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
		__F__, __L__, drc_param.win_id,dse_ctrl_param.chroma_gain_en, \
		dse_ctrl_param.chroma_cb_gain1,dse_ctrl_param.chroma_cb_gain2,\
		dse_ctrl_param.chroma_cr_gain1,dse_ctrl_param.chroma_cr_gain2,\
		dse_ctrl_param.chroma_alpha1,dse_ctrl_param.chroma_alpha2,\
		dse_ctrl_param.luma_gain_x[0],dse_ctrl_param.luma_gain_x[1],dse_ctrl_param.luma_gain_x[2],dse_ctrl_param.luma_gain_x[3],\
		dse_ctrl_param.luma_gain_y[0],dse_ctrl_param.luma_gain_y[1],dse_ctrl_param.luma_gain_y[2],dse_ctrl_param.luma_gain_y[3],\
		dse_ctrl_param.sat_gain_x[0],dse_ctrl_param.sat_gain_x[1],dse_ctrl_param.sat_gain_x[2],dse_ctrl_param.sat_gain_x[3],\
		dse_ctrl_param.sat_gain_y[0],dse_ctrl_param.sat_gain_y[1],dse_ctrl_param.sat_gain_y[2],dse_ctrl_param.sat_gain_y[3],\
		dse_ctrl_param.dtm_hue_gain,dse_ctrl_param.dtm_sat_gain);
	ret = PE_DCM_SetDseCtrl2((void *)&dse_ctrl_param);
	VPQ_HWRAP_CHECK_CODE(ret, return ret, \
			"Error.[%s.%d] PE_DCM_SetDseCtrl2() \n", __F__, __L__);
	return ret;
}
int vpq_hwrap_setlocalcontrasttable_o26(vpq_hwrap_chip_dc2p_localcontrast_table_o26_t *plocaltable)
{
	int ret = RET_OK;
	LX_PE_DCM_DRC_CUV2_T *p = NULL;
	UINT32 i, j;
	SINT32 d_data;
	
	VPQ_HWRAP_CHECK_CODE(!plocaltable, return RET_ERROR, "Error. plocaltable is null.\n");
	PE_PRINT_DCM(
		"[%s.%d] DRC table:\n"\
		"global apl:%d,%d,%d,%d\n"\
		"local	apl:%d,%d,%d,%d,%d,%d\n"\
		"w_gain:%d, b_gain:%d\n",\
		__F__, __L__,\
		plocaltable->global_apl[0],plocaltable->global_apl[1],plocaltable->global_apl[2],plocaltable->global_apl[3],
		plocaltable->local_apl[0],plocaltable->local_apl[1],plocaltable->local_apl[2],plocaltable->local_apl[3],plocaltable->local_apl[4],plocaltable->local_apl[5],
		plocaltable->cuv_gain_w,plocaltable->cuv_gain_b);
	for(i =0 ; i<LX_PE_CM_FREE_POINT ; i++)
	{
		PE_PRINT_DCM(
			"n1_curv%d: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
			"n1_curv%d: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
			i,\
			plocaltable->n1p_trans_curv[i][0],plocaltable->n1p_trans_curv[i][1],plocaltable->n1p_trans_curv[i][2],\
			plocaltable->n1p_trans_curv[i][3],plocaltable->n1p_trans_curv[i][4],plocaltable->n1p_trans_curv[i][5],\
			plocaltable->n1p_trans_curv[i][6],plocaltable->n1p_trans_curv[i][7],plocaltable->n1p_trans_curv[i][8],\
			plocaltable->n1p_trans_curv[i][9],plocaltable->n1p_trans_curv[i][10],plocaltable->n1p_trans_curv[i][11],\
			plocaltable->n1p_trans_curv[i][12],plocaltable->n1p_trans_curv[i][13],plocaltable->n1p_trans_curv[i][14],\
			plocaltable->n1p_trans_curv[i][15],plocaltable->n1p_trans_curv[i][16],\
			i,\
			plocaltable->n1p_trans_curv[i][17],plocaltable->n1p_trans_curv[i][18],plocaltable->n1p_trans_curv[i][19],\
			plocaltable->n1p_trans_curv[i][20],plocaltable->n1p_trans_curv[i][21],plocaltable->n1p_trans_curv[i][22],\
			plocaltable->n1p_trans_curv[i][23],plocaltable->n1p_trans_curv[i][24],plocaltable->n1p_trans_curv[i][25],\
			plocaltable->n1p_trans_curv[i][26],plocaltable->n1p_trans_curv[i][27],plocaltable->n1p_trans_curv[i][28],\
			plocaltable->n1p_trans_curv[i][29],plocaltable->n1p_trans_curv[i][30],plocaltable->n1p_trans_curv[i][31],\
			plocaltable->n1p_trans_curv[i][32]);
		PE_PRINT_DCM(
			"n2_curv%d: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
			"n2_curv%d: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
			i,\
			plocaltable->n2p_trans_curv[i][0],plocaltable->n2p_trans_curv[i][1],plocaltable->n2p_trans_curv[i][2],\
			plocaltable->n2p_trans_curv[i][3],plocaltable->n2p_trans_curv[i][4],plocaltable->n2p_trans_curv[i][5],\
			plocaltable->n2p_trans_curv[i][6],plocaltable->n2p_trans_curv[i][7],plocaltable->n2p_trans_curv[i][8],\
			plocaltable->n2p_trans_curv[i][9],plocaltable->n2p_trans_curv[i][10],plocaltable->n2p_trans_curv[i][11],\
			plocaltable->n2p_trans_curv[i][12],plocaltable->n2p_trans_curv[i][13],plocaltable->n2p_trans_curv[i][14],\
			plocaltable->n2p_trans_curv[i][15],plocaltable->n2p_trans_curv[i][16],\
			i,\
			plocaltable->n2p_trans_curv[i][17],plocaltable->n2p_trans_curv[i][18],plocaltable->n2p_trans_curv[i][19],\
			plocaltable->n2p_trans_curv[i][20],plocaltable->n2p_trans_curv[i][21],plocaltable->n2p_trans_curv[i][22],\
			plocaltable->n2p_trans_curv[i][23],plocaltable->n2p_trans_curv[i][24],plocaltable->n2p_trans_curv[i][25],\
			plocaltable->n2p_trans_curv[i][26],plocaltable->n2p_trans_curv[i][27],plocaltable->n2p_trans_curv[i][28],\
			plocaltable->n2p_trans_curv[i][29],plocaltable->n2p_trans_curv[i][30],plocaltable->n2p_trans_curv[i][31],\
			plocaltable->n2p_trans_curv[i][32]);
		PE_PRINT_DCM(
			"n3_curv%d: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
			"n3_curv%d: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
			i,\
			plocaltable->n3p_trans_curv[i][0],plocaltable->n3p_trans_curv[i][1],plocaltable->n3p_trans_curv[i][2],\
			plocaltable->n3p_trans_curv[i][3],plocaltable->n3p_trans_curv[i][4],plocaltable->n3p_trans_curv[i][5],\
			plocaltable->n3p_trans_curv[i][6],plocaltable->n3p_trans_curv[i][7],plocaltable->n3p_trans_curv[i][8],\
			plocaltable->n3p_trans_curv[i][9],plocaltable->n3p_trans_curv[i][10],plocaltable->n3p_trans_curv[i][11],\
			plocaltable->n3p_trans_curv[i][12],plocaltable->n3p_trans_curv[i][13],plocaltable->n3p_trans_curv[i][14],\
			plocaltable->n3p_trans_curv[i][15],plocaltable->n3p_trans_curv[i][16],\
			i,\
			plocaltable->n3p_trans_curv[i][17],plocaltable->n3p_trans_curv[i][18],plocaltable->n3p_trans_curv[i][19],\
			plocaltable->n3p_trans_curv[i][20],plocaltable->n3p_trans_curv[i][21],plocaltable->n3p_trans_curv[i][22],\
			plocaltable->n3p_trans_curv[i][23],plocaltable->n3p_trans_curv[i][24],plocaltable->n3p_trans_curv[i][25],\
			plocaltable->n3p_trans_curv[i][26],plocaltable->n3p_trans_curv[i][27],plocaltable->n3p_trans_curv[i][28],\
			plocaltable->n3p_trans_curv[i][29],plocaltable->n3p_trans_curv[i][30],plocaltable->n3p_trans_curv[i][31],\
			plocaltable->n3p_trans_curv[i][32]);
		PE_PRINT_DCM(
			"n4_curv%d: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
			"n4_curv%d: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
			i,\
			plocaltable->n4p_trans_curv[i][0],plocaltable->n4p_trans_curv[i][1],plocaltable->n4p_trans_curv[i][2],\
			plocaltable->n4p_trans_curv[i][3],plocaltable->n4p_trans_curv[i][4],plocaltable->n4p_trans_curv[i][5],\
			plocaltable->n4p_trans_curv[i][6],plocaltable->n4p_trans_curv[i][7],plocaltable->n4p_trans_curv[i][8],\
			plocaltable->n4p_trans_curv[i][9],plocaltable->n4p_trans_curv[i][10],plocaltable->n4p_trans_curv[i][11],\
			plocaltable->n4p_trans_curv[i][12],plocaltable->n4p_trans_curv[i][13],plocaltable->n4p_trans_curv[i][14],\
			plocaltable->n4p_trans_curv[i][15],plocaltable->n4p_trans_curv[i][16],\
			i,\
			plocaltable->n4p_trans_curv[i][17],plocaltable->n4p_trans_curv[i][18],plocaltable->n4p_trans_curv[i][19],\
			plocaltable->n4p_trans_curv[i][20],plocaltable->n4p_trans_curv[i][21],plocaltable->n4p_trans_curv[i][22],\
			plocaltable->n4p_trans_curv[i][23],plocaltable->n4p_trans_curv[i][24],plocaltable->n4p_trans_curv[i][25],\
			plocaltable->n4p_trans_curv[i][26],plocaltable->n4p_trans_curv[i][27],plocaltable->n4p_trans_curv[i][28],\
			plocaltable->n4p_trans_curv[i][29],plocaltable->n4p_trans_curv[i][30],plocaltable->n4p_trans_curv[i][31],\
			plocaltable->n4p_trans_curv[i][32]);
	}

	p = OS_Malloc(sizeof(LX_PE_DCM_DRC_CUV2_T));
	if (!p)	{PE_PRINT_ERROR("p is null\n");return ret;}
	PE_PRINT_DCM("size of plocaltable : %zu, size of p : %zu\n", sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_o26_t), sizeof(LX_PE_DCM_DRC_CUV2_T));
	memcpy(p->global_apl, plocaltable->global_apl, sizeof(SINT32) * LX_PE_CM_GLOBAL_POINT);
	memcpy(p->local_apl, plocaltable->local_apl, sizeof(SINT32) * LX_PE_CM_LOCAL_POINT);
	p->cuv_gain_b = plocaltable->cuv_gain_b;
	p->cuv_gain_w = plocaltable->cuv_gain_w;
	PE_PRINT_DCM(
		"[%s.%d] DRC table drv:\n"\
		"global apl:%d,%d,%d,%d\n"\
		"local	apl:%d,%d,%d,%d,%d,%d\n"\
		"w_gain:%d, b_gain:%d\n",\
		__F__, __L__,\
		p->global_apl[0],p->global_apl[1],p->global_apl[2],p->global_apl[3],
		p->local_apl[0],p->local_apl[1],p->local_apl[2],p->local_apl[3],p->local_apl[4],p->local_apl[5],
		p->cuv_gain_w,p->cuv_gain_b);
	for(i = 0; i < LX_PE_CM_FREE_POINT; i++)
	{
		for(j = 0; j < LX_PE_CM_LOCAL_CURVE_FW2; j++)
		{
			d_data =  GET_BITS(plocaltable->n1p_trans_curv[i][j*3],0,10);
			d_data += GET_BITS(plocaltable->n1p_trans_curv[i][j*3+1],0,10)<<10;
			d_data += GET_BITS(plocaltable->n1p_trans_curv[i][j*3+2],0,10)<<20;
			p->n1p_trans_curv[i][j] =d_data;
			
			d_data =  GET_BITS(plocaltable->n2p_trans_curv[i][j*3],0,10);
			d_data += GET_BITS(plocaltable->n2p_trans_curv[i][j*3+1],0,10)<<10;
			d_data += GET_BITS(plocaltable->n2p_trans_curv[i][j*3+2],0,10)<<20;
			p->n2p_trans_curv[i][j] =d_data;
			
			d_data =  GET_BITS(plocaltable->n3p_trans_curv[i][j*3],0,10);
			d_data += GET_BITS(plocaltable->n3p_trans_curv[i][j*3+1],0,10)<<10;
			d_data += GET_BITS(plocaltable->n3p_trans_curv[i][j*3+2],0,10)<<20;
			p->n3p_trans_curv[i][j] =d_data;
			
			d_data =  GET_BITS(plocaltable->n4p_trans_curv[i][j*3],0,10);
			d_data += GET_BITS(plocaltable->n4p_trans_curv[i][j*3+1],0,10)<<10;
			d_data += GET_BITS(plocaltable->n4p_trans_curv[i][j*3+2],0,10)<<20;
			p->n4p_trans_curv[i][j] =d_data;
		}
	}

	for(i =0 ; i<LX_PE_CM_FREE_POINT ; i++)
	{
		PE_PRINT_DCM(
			"n1_curv%d: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",\
			i,\
			p->n1p_trans_curv[i][0],p->n1p_trans_curv[i][1],p->n1p_trans_curv[i][2],\
			p->n1p_trans_curv[i][3],p->n1p_trans_curv[i][4],p->n1p_trans_curv[i][5],\
			p->n1p_trans_curv[i][6],p->n1p_trans_curv[i][7],p->n1p_trans_curv[i][8],\
			p->n1p_trans_curv[i][9],p->n1p_trans_curv[i][10]);
		PE_PRINT_DCM(
			"n2_curv%d: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",\
			i,\
			p->n2p_trans_curv[i][0],p->n2p_trans_curv[i][1],p->n2p_trans_curv[i][2],\
			p->n2p_trans_curv[i][3],p->n2p_trans_curv[i][4],p->n2p_trans_curv[i][5],\
			p->n2p_trans_curv[i][6],p->n2p_trans_curv[i][7],p->n2p_trans_curv[i][8],\
			p->n2p_trans_curv[i][9],p->n2p_trans_curv[i][10]);
		
		PE_PRINT_DCM(
			"n3_curv%d: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",\
			i,\
			p->n3p_trans_curv[i][0],p->n3p_trans_curv[i][1],p->n3p_trans_curv[i][2],\
			p->n3p_trans_curv[i][3],p->n3p_trans_curv[i][4],p->n3p_trans_curv[i][5],\
			p->n3p_trans_curv[i][6],p->n3p_trans_curv[i][7],p->n3p_trans_curv[i][8],\
			p->n3p_trans_curv[i][9],p->n3p_trans_curv[i][10]);
		
		PE_PRINT_DCM(
			"n4_curv%d: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",\
			i,\
			p->n4p_trans_curv[i][0],p->n4p_trans_curv[i][1],p->n4p_trans_curv[i][2],\
			p->n4p_trans_curv[i][3],p->n4p_trans_curv[i][4],p->n4p_trans_curv[i][5],\
			p->n4p_trans_curv[i][6],p->n4p_trans_curv[i][7],p->n4p_trans_curv[i][8],\
			p->n4p_trans_curv[i][9],p->n4p_trans_curv[i][10]);

	}
	
	if (PE_KDRV_VER_O20)
	{
		ret = KWRAP_PE_SetDrcCurv((void *)p);
	}
	else
	{
		ret = PE_DCM_SetDrcCurv((void *)p);
	}
	if(p) {OS_Free(p);}
	return ret;
}


int vpq_hwrap_setlocalcontrasttable(vpq_hwrap_chip_dc2p_localcontrast_table_t *plocaltable)
{
	int ret = RET_OK;
	LX_PE_DCM_DRC_CUV_T *p = NULL;
	UINT32 i;
	SINT32 d_data;
	
	VPQ_HWRAP_CHECK_CODE(!plocaltable, return RET_ERROR, "Error. plocaltable is null.\n");
	p = OS_Malloc(sizeof(LX_PE_DCM_DRC_CUV_T));
	if (!p)	{PE_PRINT_ERROR("p is null\n");return ret;}
	PE_PRINT_DCM("size of plocaltable : %zu, size of p : %zu\n", sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_t), sizeof(LX_PE_DCM_DRC_CUV_T));
	memcpy(p->global_apl, plocaltable->global_apl, sizeof(SINT32) * LX_PE_CM_GLOBAL_POINT);
	memcpy(p->local_apl, plocaltable->local_apl, sizeof(SINT32) * LX_PE_CM_LOCAL_POINT);
	p->cuv_gain_b = plocaltable->cuv_gain_b;
	p->cuv_gain_w = plocaltable->cuv_gain_w;
	for(i = 0; i < LX_PE_CM_FREE_POINT; i++)
	{
		d_data =  GET_BITS(plocaltable->n1p_trans_curv[i][0],0,10);
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][1],0,10)<<10;
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][2],0,10)<<20;
		p->n1p_trans_curv[i][0] =d_data;
		d_data =  GET_BITS(plocaltable->n1p_trans_curv[i][3],0,10);
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][4],0,10)<<10;
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][5],0,10)<<20;
		p->n1p_trans_curv[i][1] =d_data;
		d_data =  GET_BITS(plocaltable->n1p_trans_curv[i][6],0,10);
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][7],0,10)<<10;
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][8],0,10)<<20;
		p->n1p_trans_curv[i][2] =d_data;
		d_data =  GET_BITS(plocaltable->n1p_trans_curv[i][9],0,10);
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][10],0,10)<<10;
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][11],0,10)<<20;
		p->n1p_trans_curv[i][3] =d_data;
		d_data =  GET_BITS(plocaltable->n1p_trans_curv[i][12],0,10);
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][13],0,10)<<10;
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][14],0,10)<<20;
		p->n1p_trans_curv[i][4] =d_data;
		d_data =  GET_BITS(plocaltable->n1p_trans_curv[i][15],0,10);
		d_data += GET_BITS(plocaltable->n1p_trans_curv[i][16],0,10)<<10;
		p->n1p_trans_curv[i][5] =d_data;

		d_data =  GET_BITS(plocaltable->n2p_trans_curv[i][0],0,10);
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][1],0,10)<<10;
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][2],0,10)<<20;
		p->n2p_trans_curv[i][0] =d_data;
		d_data =  GET_BITS(plocaltable->n2p_trans_curv[i][3],0,10);
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][4],0,10)<<10;
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][5],0,10)<<20;
		p->n2p_trans_curv[i][1] =d_data;
		d_data =  GET_BITS(plocaltable->n2p_trans_curv[i][6],0,10);
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][7],0,10)<<10;
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][8],0,10)<<20;
		p->n2p_trans_curv[i][2] =d_data;
		d_data =  GET_BITS(plocaltable->n2p_trans_curv[i][9],0,10);
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][10],0,10)<<10;
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][11],0,10)<<20;
		p->n2p_trans_curv[i][3] =d_data;
		d_data =  GET_BITS(plocaltable->n2p_trans_curv[i][12],0,10);
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][13],0,10)<<10;
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][14],0,10)<<20;
		p->n2p_trans_curv[i][4] =d_data;
		d_data =  GET_BITS(plocaltable->n2p_trans_curv[i][15],0,10);
		d_data += GET_BITS(plocaltable->n2p_trans_curv[i][16],0,10)<<10;
		p->n2p_trans_curv[i][5] =d_data;

		d_data =  GET_BITS(plocaltable->n3p_trans_curv[i][0],0,10);
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][1],0,10)<<10;
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][2],0,10)<<20;
		p->n3p_trans_curv[i][0] =d_data;
		d_data =  GET_BITS(plocaltable->n3p_trans_curv[i][3],0,10);
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][4],0,10)<<10;
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][5],0,10)<<20;
		p->n3p_trans_curv[i][1] =d_data;
		d_data =  GET_BITS(plocaltable->n3p_trans_curv[i][6],0,10);
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][7],0,10)<<10;
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][8],0,10)<<20;
		p->n3p_trans_curv[i][2] =d_data;
		d_data =  GET_BITS(plocaltable->n3p_trans_curv[i][9],0,10);
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][10],0,10)<<10;
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][11],0,10)<<20;
		p->n3p_trans_curv[i][3] =d_data;
		d_data =  GET_BITS(plocaltable->n3p_trans_curv[i][12],0,10);
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][13],0,10)<<10;
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][14],0,10)<<20;
		p->n3p_trans_curv[i][4] =d_data;
		d_data =  GET_BITS(plocaltable->n3p_trans_curv[i][15],0,10);
		d_data += GET_BITS(plocaltable->n3p_trans_curv[i][16],0,10)<<10;
		p->n3p_trans_curv[i][5] =d_data;

		d_data =  GET_BITS(plocaltable->n4p_trans_curv[i][0],0,10);
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][1],0,10)<<10;
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][2],0,10)<<20;
		p->n4p_trans_curv[i][0] =d_data;
		d_data =  GET_BITS(plocaltable->n4p_trans_curv[i][3],0,10);
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][4],0,10)<<10;
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][5],0,10)<<20;
		p->n4p_trans_curv[i][1] =d_data;
		d_data =  GET_BITS(plocaltable->n4p_trans_curv[i][6],0,10);
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][7],0,10)<<10;
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][8],0,10)<<20;
		p->n4p_trans_curv[i][2] =d_data;
		d_data =  GET_BITS(plocaltable->n4p_trans_curv[i][9],0,10);
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][10],0,10)<<10;
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][11],0,10)<<20;
		p->n4p_trans_curv[i][3] =d_data;
		d_data =  GET_BITS(plocaltable->n4p_trans_curv[i][12],0,10);
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][13],0,10)<<10;
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][14],0,10)<<20;
		p->n4p_trans_curv[i][4] =d_data;
		d_data =  GET_BITS(plocaltable->n4p_trans_curv[i][15],0,10);
		d_data += GET_BITS(plocaltable->n4p_trans_curv[i][16],0,10)<<10;
		p->n4p_trans_curv[i][5] =d_data;
	}
	PE_PRINT_DCM(
		"n1_curv0: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n1_curv1: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n1_curv2: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n1_curv3: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n1_curv4: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n1_curv5: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",\
		p->n1p_trans_curv[0][0],p->n1p_trans_curv[0][1],p->n1p_trans_curv[0][2],\
		p->n1p_trans_curv[0][3],p->n1p_trans_curv[0][4],p->n1p_trans_curv[0][5],\
		p->n1p_trans_curv[1][0],p->n1p_trans_curv[1][1],p->n1p_trans_curv[1][2],\
		p->n1p_trans_curv[1][3],p->n1p_trans_curv[1][4],p->n1p_trans_curv[1][5],\
		p->n1p_trans_curv[2][0],p->n1p_trans_curv[2][1],p->n1p_trans_curv[2][2],\
		p->n1p_trans_curv[2][3],p->n1p_trans_curv[2][4],p->n1p_trans_curv[2][5],\
		p->n1p_trans_curv[3][0],p->n1p_trans_curv[3][1],p->n1p_trans_curv[3][2],\
		p->n1p_trans_curv[3][3],p->n1p_trans_curv[3][4],p->n1p_trans_curv[3][5],\
		p->n1p_trans_curv[4][0],p->n1p_trans_curv[4][1],p->n1p_trans_curv[4][2],\
		p->n1p_trans_curv[4][3],p->n1p_trans_curv[4][4],p->n1p_trans_curv[4][5],\
		p->n1p_trans_curv[5][0],p->n1p_trans_curv[5][1],p->n1p_trans_curv[5][2],\
		p->n1p_trans_curv[5][3],p->n1p_trans_curv[5][4],p->n1p_trans_curv[5][5]);
	PE_PRINT_DCM(
		"n2_curv0: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n2_curv1: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n2_curv2: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n2_curv3: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n2_curv4: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n2_curv5: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",\
		p->n2p_trans_curv[0][0],p->n2p_trans_curv[0][1],p->n2p_trans_curv[0][2],\
		p->n2p_trans_curv[0][3],p->n2p_trans_curv[0][4],p->n2p_trans_curv[0][5],\
		p->n2p_trans_curv[1][0],p->n2p_trans_curv[1][1],p->n2p_trans_curv[1][2],\
		p->n2p_trans_curv[1][3],p->n2p_trans_curv[1][4],p->n2p_trans_curv[1][5],\
		p->n2p_trans_curv[2][0],p->n2p_trans_curv[2][1],p->n2p_trans_curv[2][2],\
		p->n2p_trans_curv[2][3],p->n2p_trans_curv[2][4],p->n2p_trans_curv[2][5],\
		p->n2p_trans_curv[3][0],p->n2p_trans_curv[3][1],p->n2p_trans_curv[3][2],\
		p->n2p_trans_curv[3][3],p->n2p_trans_curv[3][4],p->n2p_trans_curv[3][5],\
		p->n2p_trans_curv[4][0],p->n2p_trans_curv[4][1],p->n2p_trans_curv[4][2],\
		p->n2p_trans_curv[4][3],p->n2p_trans_curv[4][4],p->n2p_trans_curv[4][5],\
		p->n2p_trans_curv[5][0],p->n2p_trans_curv[5][1],p->n2p_trans_curv[5][2],\
		p->n2p_trans_curv[5][3],p->n2p_trans_curv[5][4],p->n2p_trans_curv[5][5]);
	PE_PRINT_DCM(
		"n3_curv0: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n3_curv1: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n3_curv2: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n3_curv3: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n3_curv4: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n3_curv5: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",\
		p->n3p_trans_curv[0][0],p->n3p_trans_curv[0][1],p->n3p_trans_curv[0][2],\
		p->n3p_trans_curv[0][3],p->n3p_trans_curv[0][4],p->n3p_trans_curv[0][5],\
		p->n3p_trans_curv[1][0],p->n3p_trans_curv[1][1],p->n3p_trans_curv[1][2],\
		p->n3p_trans_curv[1][3],p->n3p_trans_curv[1][4],p->n3p_trans_curv[1][5],\
		p->n3p_trans_curv[2][0],p->n3p_trans_curv[2][1],p->n3p_trans_curv[2][2],\
		p->n3p_trans_curv[2][3],p->n3p_trans_curv[2][4],p->n3p_trans_curv[2][5],\
		p->n3p_trans_curv[3][0],p->n3p_trans_curv[3][1],p->n3p_trans_curv[3][2],\
		p->n3p_trans_curv[3][3],p->n3p_trans_curv[3][4],p->n3p_trans_curv[3][5],\
		p->n3p_trans_curv[4][0],p->n3p_trans_curv[4][1],p->n3p_trans_curv[4][2],\
		p->n3p_trans_curv[4][3],p->n3p_trans_curv[4][4],p->n3p_trans_curv[4][5],\
		p->n3p_trans_curv[5][0],p->n3p_trans_curv[5][1],p->n3p_trans_curv[5][2],\
		p->n3p_trans_curv[5][3],p->n3p_trans_curv[5][4],p->n3p_trans_curv[5][5]);
	PE_PRINT_DCM(
		"n4_curv0: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n4_curv1: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n4_curv2: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n4_curv3: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n4_curv4: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n"\
		"n4_curv5: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",\
		p->n4p_trans_curv[0][0],p->n4p_trans_curv[0][1],p->n4p_trans_curv[0][2],\
		p->n4p_trans_curv[0][3],p->n4p_trans_curv[0][4],p->n4p_trans_curv[0][5],\
		p->n4p_trans_curv[1][0],p->n4p_trans_curv[1][1],p->n4p_trans_curv[1][2],\
		p->n4p_trans_curv[1][3],p->n4p_trans_curv[1][4],p->n4p_trans_curv[1][5],\
		p->n4p_trans_curv[2][0],p->n4p_trans_curv[2][1],p->n4p_trans_curv[2][2],\
		p->n4p_trans_curv[2][3],p->n4p_trans_curv[2][4],p->n4p_trans_curv[2][5],\
		p->n4p_trans_curv[3][0],p->n4p_trans_curv[3][1],p->n4p_trans_curv[3][2],\
		p->n4p_trans_curv[3][3],p->n4p_trans_curv[3][4],p->n4p_trans_curv[3][5],\
		p->n4p_trans_curv[4][0],p->n4p_trans_curv[4][1],p->n4p_trans_curv[4][2],\
		p->n4p_trans_curv[4][3],p->n4p_trans_curv[4][4],p->n4p_trans_curv[4][5],\
		p->n4p_trans_curv[5][0],p->n4p_trans_curv[5][1],p->n4p_trans_curv[5][2],\
		p->n4p_trans_curv[5][3],p->n4p_trans_curv[5][4],p->n4p_trans_curv[5][5]);
	PE_PRINT_DCM(
		"[%s.%d] DRC table:\n"\
		"global apl:%d,%d,%d,%d\n"\
		"local	apl:%d,%d,%d,%d,%d,%d\n"\
		"w_gain:%d, b_gain:%d\n",\
		__F__, __L__,\
		plocaltable->global_apl[0],plocaltable->global_apl[1],plocaltable->global_apl[2],plocaltable->global_apl[3],
		plocaltable->local_apl[0],plocaltable->local_apl[1],plocaltable->local_apl[2],plocaltable->local_apl[3],plocaltable->local_apl[4],plocaltable->local_apl[5],
		plocaltable->cuv_gain_w,plocaltable->cuv_gain_b);
	PE_PRINT_DCM(
		"n1_curv0: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n1_curv1: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n1_curv2: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n1_curv3: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n1_curv4: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n1_curv5: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
		plocaltable->n1p_trans_curv[0][0],plocaltable->n1p_trans_curv[0][1],plocaltable->n1p_trans_curv[0][2],\
		plocaltable->n1p_trans_curv[0][3],plocaltable->n1p_trans_curv[0][4],plocaltable->n1p_trans_curv[0][5],\
		plocaltable->n1p_trans_curv[0][6],plocaltable->n1p_trans_curv[0][7],plocaltable->n1p_trans_curv[0][8],\
		plocaltable->n1p_trans_curv[0][9],plocaltable->n1p_trans_curv[0][10],plocaltable->n1p_trans_curv[0][11],\
		plocaltable->n1p_trans_curv[0][12],plocaltable->n1p_trans_curv[0][13],plocaltable->n1p_trans_curv[0][14],\
		plocaltable->n1p_trans_curv[0][15],plocaltable->n1p_trans_curv[0][16],\
		plocaltable->n1p_trans_curv[1][0],plocaltable->n1p_trans_curv[1][1],plocaltable->n1p_trans_curv[1][2],\
		plocaltable->n1p_trans_curv[1][3],plocaltable->n1p_trans_curv[1][4],plocaltable->n1p_trans_curv[1][5],\
		plocaltable->n1p_trans_curv[1][6],plocaltable->n1p_trans_curv[1][7],plocaltable->n1p_trans_curv[1][8],\
		plocaltable->n1p_trans_curv[1][9],plocaltable->n1p_trans_curv[1][10],plocaltable->n1p_trans_curv[1][11],\
		plocaltable->n1p_trans_curv[1][12],plocaltable->n1p_trans_curv[1][13],plocaltable->n1p_trans_curv[1][14],\
		plocaltable->n1p_trans_curv[1][15],plocaltable->n1p_trans_curv[1][16],\
		plocaltable->n1p_trans_curv[2][0],plocaltable->n1p_trans_curv[2][1],plocaltable->n1p_trans_curv[2][2],\
		plocaltable->n1p_trans_curv[2][3],plocaltable->n1p_trans_curv[2][4],plocaltable->n1p_trans_curv[2][5],\
		plocaltable->n1p_trans_curv[2][6],plocaltable->n1p_trans_curv[2][7],plocaltable->n1p_trans_curv[2][8],\
		plocaltable->n1p_trans_curv[2][9],plocaltable->n1p_trans_curv[2][10],plocaltable->n1p_trans_curv[2][11],\
		plocaltable->n1p_trans_curv[2][12],plocaltable->n1p_trans_curv[2][13],plocaltable->n1p_trans_curv[2][14],\
		plocaltable->n1p_trans_curv[2][15],plocaltable->n1p_trans_curv[2][16],\
		plocaltable->n1p_trans_curv[3][0],plocaltable->n1p_trans_curv[3][1],plocaltable->n1p_trans_curv[3][2],\
		plocaltable->n1p_trans_curv[3][3],plocaltable->n1p_trans_curv[3][4],plocaltable->n1p_trans_curv[3][5],\
		plocaltable->n1p_trans_curv[3][6],plocaltable->n1p_trans_curv[3][7],plocaltable->n1p_trans_curv[3][8],\
		plocaltable->n1p_trans_curv[3][9],plocaltable->n1p_trans_curv[3][10],plocaltable->n1p_trans_curv[3][11],\
		plocaltable->n1p_trans_curv[3][12],plocaltable->n1p_trans_curv[3][13],plocaltable->n1p_trans_curv[3][14],\
		plocaltable->n1p_trans_curv[3][15],plocaltable->n1p_trans_curv[3][16],\
		plocaltable->n1p_trans_curv[4][0],plocaltable->n1p_trans_curv[4][1],plocaltable->n1p_trans_curv[4][2],\
		plocaltable->n1p_trans_curv[4][3],plocaltable->n1p_trans_curv[4][4],plocaltable->n1p_trans_curv[4][5],\
		plocaltable->n1p_trans_curv[4][6],plocaltable->n1p_trans_curv[4][7],plocaltable->n1p_trans_curv[4][8],\
		plocaltable->n1p_trans_curv[4][9],plocaltable->n1p_trans_curv[4][10],plocaltable->n1p_trans_curv[4][11],\
		plocaltable->n1p_trans_curv[4][12],plocaltable->n1p_trans_curv[4][13],plocaltable->n1p_trans_curv[4][14],\
		plocaltable->n1p_trans_curv[4][15],plocaltable->n1p_trans_curv[4][16],\
		plocaltable->n1p_trans_curv[5][0],plocaltable->n1p_trans_curv[5][1],plocaltable->n1p_trans_curv[5][2],\
		plocaltable->n1p_trans_curv[5][3],plocaltable->n1p_trans_curv[5][4],plocaltable->n1p_trans_curv[5][5],\
		plocaltable->n1p_trans_curv[5][6],plocaltable->n1p_trans_curv[5][7],plocaltable->n1p_trans_curv[5][8],\
		plocaltable->n1p_trans_curv[5][9],plocaltable->n1p_trans_curv[5][10],plocaltable->n1p_trans_curv[5][11],\
		plocaltable->n1p_trans_curv[5][12],plocaltable->n1p_trans_curv[5][13],plocaltable->n1p_trans_curv[5][14],\
		plocaltable->n1p_trans_curv[5][15],plocaltable->n1p_trans_curv[5][16]);
	PE_PRINT_DCM(
		"n2_curv0: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n2_curv1: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n2_curv2: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n2_curv3: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n2_curv4: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n2_curv5: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
		plocaltable->n2p_trans_curv[0][0],plocaltable->n2p_trans_curv[0][1],plocaltable->n2p_trans_curv[0][2],\
		plocaltable->n2p_trans_curv[0][3],plocaltable->n2p_trans_curv[0][4],plocaltable->n2p_trans_curv[0][5],\
		plocaltable->n2p_trans_curv[0][6],plocaltable->n2p_trans_curv[0][7],plocaltable->n2p_trans_curv[0][8],\
		plocaltable->n2p_trans_curv[0][9],plocaltable->n2p_trans_curv[0][10],plocaltable->n2p_trans_curv[0][11],\
		plocaltable->n2p_trans_curv[0][12],plocaltable->n2p_trans_curv[0][13],plocaltable->n2p_trans_curv[0][14],\
		plocaltable->n2p_trans_curv[0][15],plocaltable->n2p_trans_curv[0][16],\
		plocaltable->n2p_trans_curv[1][0],plocaltable->n2p_trans_curv[1][1],plocaltable->n2p_trans_curv[1][2],\
		plocaltable->n2p_trans_curv[1][3],plocaltable->n2p_trans_curv[1][4],plocaltable->n2p_trans_curv[1][5],\
		plocaltable->n2p_trans_curv[1][6],plocaltable->n2p_trans_curv[1][7],plocaltable->n2p_trans_curv[1][8],\
		plocaltable->n2p_trans_curv[1][9],plocaltable->n2p_trans_curv[1][10],plocaltable->n2p_trans_curv[1][11],\
		plocaltable->n2p_trans_curv[1][12],plocaltable->n2p_trans_curv[1][13],plocaltable->n2p_trans_curv[1][14],\
		plocaltable->n2p_trans_curv[1][15],plocaltable->n2p_trans_curv[1][16],\
		plocaltable->n2p_trans_curv[2][0],plocaltable->n2p_trans_curv[2][1],plocaltable->n2p_trans_curv[2][2],\
		plocaltable->n2p_trans_curv[2][3],plocaltable->n2p_trans_curv[2][4],plocaltable->n2p_trans_curv[2][5],\
		plocaltable->n2p_trans_curv[2][6],plocaltable->n2p_trans_curv[2][7],plocaltable->n2p_trans_curv[2][8],\
		plocaltable->n2p_trans_curv[2][9],plocaltable->n2p_trans_curv[2][10],plocaltable->n2p_trans_curv[2][11],\
		plocaltable->n2p_trans_curv[2][12],plocaltable->n2p_trans_curv[2][13],plocaltable->n2p_trans_curv[2][14],\
		plocaltable->n2p_trans_curv[2][15],plocaltable->n2p_trans_curv[2][16],\
		plocaltable->n2p_trans_curv[3][0],plocaltable->n2p_trans_curv[3][1],plocaltable->n2p_trans_curv[3][2],\
		plocaltable->n2p_trans_curv[3][3],plocaltable->n2p_trans_curv[3][4],plocaltable->n2p_trans_curv[3][5],\
		plocaltable->n2p_trans_curv[3][6],plocaltable->n2p_trans_curv[3][7],plocaltable->n2p_trans_curv[3][8],\
		plocaltable->n2p_trans_curv[3][9],plocaltable->n2p_trans_curv[3][10],plocaltable->n2p_trans_curv[3][11],\
		plocaltable->n2p_trans_curv[3][12],plocaltable->n2p_trans_curv[3][13],plocaltable->n2p_trans_curv[3][14],\
		plocaltable->n2p_trans_curv[3][15],plocaltable->n2p_trans_curv[3][16],\
		plocaltable->n2p_trans_curv[4][0],plocaltable->n2p_trans_curv[4][1],plocaltable->n2p_trans_curv[4][2],\
		plocaltable->n2p_trans_curv[4][3],plocaltable->n2p_trans_curv[4][4],plocaltable->n2p_trans_curv[4][5],\
		plocaltable->n2p_trans_curv[4][6],plocaltable->n2p_trans_curv[4][7],plocaltable->n2p_trans_curv[4][8],\
		plocaltable->n2p_trans_curv[4][9],plocaltable->n2p_trans_curv[4][10],plocaltable->n2p_trans_curv[4][11],\
		plocaltable->n2p_trans_curv[4][12],plocaltable->n2p_trans_curv[4][13],plocaltable->n2p_trans_curv[4][14],\
		plocaltable->n2p_trans_curv[4][15],plocaltable->n2p_trans_curv[4][16],\
		plocaltable->n2p_trans_curv[5][0],plocaltable->n2p_trans_curv[5][1],plocaltable->n2p_trans_curv[5][2],\
		plocaltable->n2p_trans_curv[5][3],plocaltable->n2p_trans_curv[5][4],plocaltable->n2p_trans_curv[5][5],\
		plocaltable->n2p_trans_curv[5][6],plocaltable->n2p_trans_curv[5][7],plocaltable->n2p_trans_curv[5][8],\
		plocaltable->n2p_trans_curv[5][9],plocaltable->n2p_trans_curv[5][10],plocaltable->n2p_trans_curv[5][11],\
		plocaltable->n2p_trans_curv[5][12],plocaltable->n2p_trans_curv[5][13],plocaltable->n2p_trans_curv[5][14],\
		plocaltable->n2p_trans_curv[5][15],plocaltable->n2p_trans_curv[5][16]);
	PE_PRINT_DCM(
		"n3_curv0: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n3_curv1: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n3_curv2: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n3_curv3: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n3_curv4: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n3_curv5: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
		plocaltable->n3p_trans_curv[0][0],plocaltable->n3p_trans_curv[0][1],plocaltable->n3p_trans_curv[0][2],\
		plocaltable->n3p_trans_curv[0][3],plocaltable->n3p_trans_curv[0][4],plocaltable->n3p_trans_curv[0][5],\
		plocaltable->n3p_trans_curv[0][6],plocaltable->n3p_trans_curv[0][7],plocaltable->n3p_trans_curv[0][8],\
		plocaltable->n3p_trans_curv[0][9],plocaltable->n3p_trans_curv[0][10],plocaltable->n3p_trans_curv[0][11],\
		plocaltable->n3p_trans_curv[0][12],plocaltable->n3p_trans_curv[0][13],plocaltable->n3p_trans_curv[0][14],\
		plocaltable->n3p_trans_curv[0][15],plocaltable->n3p_trans_curv[0][16],\
		plocaltable->n3p_trans_curv[1][0],plocaltable->n3p_trans_curv[1][1],plocaltable->n3p_trans_curv[1][2],\
		plocaltable->n3p_trans_curv[1][3],plocaltable->n3p_trans_curv[1][4],plocaltable->n3p_trans_curv[1][5],\
		plocaltable->n3p_trans_curv[1][6],plocaltable->n3p_trans_curv[1][7],plocaltable->n3p_trans_curv[1][8],\
		plocaltable->n3p_trans_curv[1][9],plocaltable->n3p_trans_curv[1][10],plocaltable->n3p_trans_curv[1][11],\
		plocaltable->n3p_trans_curv[1][12],plocaltable->n3p_trans_curv[1][13],plocaltable->n3p_trans_curv[1][14],\
		plocaltable->n3p_trans_curv[1][15],plocaltable->n3p_trans_curv[1][16],\
		plocaltable->n3p_trans_curv[2][0],plocaltable->n3p_trans_curv[2][1],plocaltable->n3p_trans_curv[2][2],\
		plocaltable->n3p_trans_curv[2][3],plocaltable->n3p_trans_curv[2][4],plocaltable->n3p_trans_curv[2][5],\
		plocaltable->n3p_trans_curv[2][6],plocaltable->n3p_trans_curv[2][7],plocaltable->n3p_trans_curv[2][8],\
		plocaltable->n3p_trans_curv[2][9],plocaltable->n3p_trans_curv[2][10],plocaltable->n3p_trans_curv[2][11],\
		plocaltable->n3p_trans_curv[2][12],plocaltable->n3p_trans_curv[2][13],plocaltable->n3p_trans_curv[2][14],\
		plocaltable->n3p_trans_curv[2][15],plocaltable->n3p_trans_curv[2][16],\
		plocaltable->n3p_trans_curv[3][0],plocaltable->n3p_trans_curv[3][1],plocaltable->n3p_trans_curv[3][2],\
		plocaltable->n3p_trans_curv[3][3],plocaltable->n3p_trans_curv[3][4],plocaltable->n3p_trans_curv[3][5],\
		plocaltable->n3p_trans_curv[3][6],plocaltable->n3p_trans_curv[3][7],plocaltable->n3p_trans_curv[3][8],\
		plocaltable->n3p_trans_curv[3][9],plocaltable->n3p_trans_curv[3][10],plocaltable->n3p_trans_curv[3][11],\
		plocaltable->n3p_trans_curv[3][12],plocaltable->n3p_trans_curv[3][13],plocaltable->n3p_trans_curv[3][14],\
		plocaltable->n3p_trans_curv[3][15],plocaltable->n3p_trans_curv[3][16],\
		plocaltable->n3p_trans_curv[4][0],plocaltable->n3p_trans_curv[4][1],plocaltable->n3p_trans_curv[4][2],\
		plocaltable->n3p_trans_curv[4][3],plocaltable->n3p_trans_curv[4][4],plocaltable->n3p_trans_curv[4][5],\
		plocaltable->n3p_trans_curv[4][6],plocaltable->n3p_trans_curv[4][7],plocaltable->n3p_trans_curv[4][8],\
		plocaltable->n3p_trans_curv[4][9],plocaltable->n3p_trans_curv[4][10],plocaltable->n3p_trans_curv[4][11],\
		plocaltable->n3p_trans_curv[4][12],plocaltable->n3p_trans_curv[4][13],plocaltable->n3p_trans_curv[4][14],\
		plocaltable->n3p_trans_curv[4][15],plocaltable->n3p_trans_curv[4][16],\
		plocaltable->n3p_trans_curv[5][0],plocaltable->n3p_trans_curv[5][1],plocaltable->n3p_trans_curv[5][2],\
		plocaltable->n3p_trans_curv[5][3],plocaltable->n3p_trans_curv[5][4],plocaltable->n3p_trans_curv[5][5],\
		plocaltable->n3p_trans_curv[5][6],plocaltable->n3p_trans_curv[5][7],plocaltable->n3p_trans_curv[5][8],\
		plocaltable->n3p_trans_curv[5][9],plocaltable->n3p_trans_curv[5][10],plocaltable->n3p_trans_curv[5][11],\
		plocaltable->n3p_trans_curv[5][12],plocaltable->n3p_trans_curv[5][13],plocaltable->n3p_trans_curv[5][14],\
		plocaltable->n3p_trans_curv[5][15],plocaltable->n3p_trans_curv[5][16] );
	PE_PRINT_DCM(
		"n4_curv0: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n4_curv1: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n4_curv2: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n4_curv3: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n4_curv4: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
		"n4_curv5: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
		plocaltable->n4p_trans_curv[0][0],plocaltable->n4p_trans_curv[0][1],plocaltable->n4p_trans_curv[0][2],\
		plocaltable->n4p_trans_curv[0][3],plocaltable->n4p_trans_curv[0][4],plocaltable->n4p_trans_curv[0][5],\
		plocaltable->n4p_trans_curv[0][6],plocaltable->n4p_trans_curv[0][7],plocaltable->n4p_trans_curv[0][8],\
		plocaltable->n4p_trans_curv[0][9],plocaltable->n4p_trans_curv[0][10],plocaltable->n4p_trans_curv[0][11],\
		plocaltable->n4p_trans_curv[0][12],plocaltable->n4p_trans_curv[0][13],plocaltable->n4p_trans_curv[0][14],\
		plocaltable->n4p_trans_curv[0][15],plocaltable->n4p_trans_curv[0][16],\
		plocaltable->n4p_trans_curv[1][0],plocaltable->n4p_trans_curv[1][1],plocaltable->n4p_trans_curv[1][2],\
		plocaltable->n4p_trans_curv[1][3],plocaltable->n4p_trans_curv[1][4],plocaltable->n4p_trans_curv[1][5],\
		plocaltable->n4p_trans_curv[1][6],plocaltable->n4p_trans_curv[1][7],plocaltable->n4p_trans_curv[1][8],\
		plocaltable->n4p_trans_curv[1][9],plocaltable->n4p_trans_curv[1][10],plocaltable->n4p_trans_curv[1][11],\
		plocaltable->n4p_trans_curv[1][12],plocaltable->n4p_trans_curv[1][13],plocaltable->n4p_trans_curv[1][14],\
		plocaltable->n4p_trans_curv[1][15],plocaltable->n4p_trans_curv[1][16],\
		plocaltable->n4p_trans_curv[2][0],plocaltable->n4p_trans_curv[2][1],plocaltable->n4p_trans_curv[2][2],\
		plocaltable->n4p_trans_curv[2][3],plocaltable->n4p_trans_curv[2][4],plocaltable->n4p_trans_curv[2][5],\
		plocaltable->n4p_trans_curv[2][6],plocaltable->n4p_trans_curv[2][7],plocaltable->n4p_trans_curv[2][8],\
		plocaltable->n4p_trans_curv[2][9],plocaltable->n4p_trans_curv[2][10],plocaltable->n4p_trans_curv[2][11],\
		plocaltable->n4p_trans_curv[2][12],plocaltable->n4p_trans_curv[2][13],plocaltable->n4p_trans_curv[2][14],\
		plocaltable->n4p_trans_curv[2][15],plocaltable->n4p_trans_curv[2][16],\
		plocaltable->n4p_trans_curv[3][0],plocaltable->n4p_trans_curv[3][1],plocaltable->n4p_trans_curv[3][2],\
		plocaltable->n4p_trans_curv[3][3],plocaltable->n4p_trans_curv[3][4],plocaltable->n4p_trans_curv[3][5],\
		plocaltable->n4p_trans_curv[3][6],plocaltable->n4p_trans_curv[3][7],plocaltable->n4p_trans_curv[3][8],\
		plocaltable->n4p_trans_curv[3][9],plocaltable->n4p_trans_curv[3][10],plocaltable->n4p_trans_curv[3][11],\
		plocaltable->n4p_trans_curv[3][12],plocaltable->n4p_trans_curv[3][13],plocaltable->n4p_trans_curv[3][14],\
		plocaltable->n4p_trans_curv[3][15],plocaltable->n4p_trans_curv[3][16],\
		plocaltable->n4p_trans_curv[4][0],plocaltable->n4p_trans_curv[4][1],plocaltable->n4p_trans_curv[4][2],\
		plocaltable->n4p_trans_curv[4][3],plocaltable->n4p_trans_curv[4][4],plocaltable->n4p_trans_curv[4][5],\
		plocaltable->n4p_trans_curv[4][6],plocaltable->n4p_trans_curv[4][7],plocaltable->n4p_trans_curv[4][8],\
		plocaltable->n4p_trans_curv[4][9],plocaltable->n4p_trans_curv[4][10],plocaltable->n4p_trans_curv[4][11],\
		plocaltable->n4p_trans_curv[4][12],plocaltable->n4p_trans_curv[4][13],plocaltable->n4p_trans_curv[4][14],\
		plocaltable->n4p_trans_curv[4][15],plocaltable->n4p_trans_curv[4][16],\
		plocaltable->n4p_trans_curv[5][0],plocaltable->n4p_trans_curv[5][1],plocaltable->n4p_trans_curv[5][2],\
		plocaltable->n4p_trans_curv[5][3],plocaltable->n4p_trans_curv[5][4],plocaltable->n4p_trans_curv[5][5],\
		plocaltable->n4p_trans_curv[5][6],plocaltable->n4p_trans_curv[5][7],plocaltable->n4p_trans_curv[5][8],\
		plocaltable->n4p_trans_curv[5][9],plocaltable->n4p_trans_curv[5][10],plocaltable->n4p_trans_curv[5][11],\
		plocaltable->n4p_trans_curv[5][12],plocaltable->n4p_trans_curv[5][13],plocaltable->n4p_trans_curv[5][14],\
		plocaltable->n4p_trans_curv[5][15],plocaltable->n4p_trans_curv[5][16]);
	PE_PRINT_DCM(
		"[%s.%d] DRC table:\n"\
		"global apl:%d,%d,%d,%d\n"\
		"local	apl:%d,%d,%d,%d,%d,%d\n"\
		"w_gain:%d, b_gain:%d\n",\
		__F__, __L__,\
		p->global_apl[0],p->global_apl[1],p->global_apl[2],p->global_apl[3],
		p->local_apl[0],p->local_apl[1],p->local_apl[2],p->local_apl[3],p->local_apl[4],p->local_apl[5],
		p->cuv_gain_w,p->cuv_gain_b);
	
	if (PE_KDRV_VER_O20)
	{
		ret = KWRAP_PE_SetDrcCurv((void *)p);
	}
	else
	{
		if(PE_KDRV_VER_O26)
			ret = PE_DCM_SetDrcCurv_Old((void *)p);
		else
			ret = PE_DCM_SetDrcCurv((void *)p);
	}
	if(p) {OS_Free(p);}
	return ret;
}


#ifdef INCLUDE_KDRV_SYS
#include "sys_io.h"
#endif
void vpq_hwrap_getnetonoff(UINT32 net_onoff)
{
	int ret = RET_OK;
	if (_g_vpq_hwrap_info.year_option == 23)// for O22n
	{
		#ifdef INCLUDE_KDRV_SYS
		ret = SYS_IO_WriteRegArray(0xCCC40200, 4, &net_onoff);
		#endif
	}
}

int vpq_hwrap_getpicturectrldbswich(void)
{
	return _g_vpq_hwrap_picturectrl_csc_switch;
}
int vpq_hwrap_getcendbswich(void)
{
	return _g_vpq_hwrap_cen_platform_db_switch;
}
int vpq_hwrap_getshpdbenalbe(void)
{
	return _g_vpq_hwrap_shp_platform_db_enable;
}
int vpq_hwrap_gettnrdbenalbe(void)
{
	return _g_vpq_hwrap_tnr_platform_db_enable;
}
int vpq_hwrap_getdnrdbenalbe(void)
{
	return _g_vpq_hwrap_dnr_platform_db_enable;
}
int vpq_hwrap_getdctdbenalbe(void)
{
	return _g_vpq_hwrap_dct_platform_db_enable;
}
void vpq_hwrap_picturectrldbswitch(void)
{
	if(_g_vpq_hwrap_picturectrl_csc_switch)
		_g_vpq_hwrap_picturectrl_csc_switch = 0x0;
	else
		_g_vpq_hwrap_picturectrl_csc_switch = 0x2;
}
void vpq_hwrap_togglecendbswitch(void)
{
	if(_g_vpq_hwrap_cen_platform_db_switch)
		_g_vpq_hwrap_cen_platform_db_switch = 0x0;
	else
		_g_vpq_hwrap_cen_platform_db_switch = 0x2;
}
void vpq_hwrap_toggleshpdbenalbe(void)
{
	if(_g_vpq_hwrap_shp_platform_db_enable)
		_g_vpq_hwrap_shp_platform_db_enable = 0x0;
	else
		_g_vpq_hwrap_shp_platform_db_enable = 0x2;
}
void vpq_hwrap_toggletnrdbenalbe(void)
{
	if(_g_vpq_hwrap_tnr_platform_db_enable)
		_g_vpq_hwrap_tnr_platform_db_enable = 0x0;
	else
		_g_vpq_hwrap_tnr_platform_db_enable = 0x2;
}
void vpq_hwrap_togglednrdbenalbe(void)
{
	if(_g_vpq_hwrap_dnr_platform_db_enable)
		_g_vpq_hwrap_dnr_platform_db_enable = 0x0;
	else
		_g_vpq_hwrap_dnr_platform_db_enable = 0x2;
}
void vpq_hwrap_toggledctdbenalbe(void)
{
	if(_g_vpq_hwrap_dct_platform_db_enable)
		_g_vpq_hwrap_dct_platform_db_enable = 0x0;
	else
		_g_vpq_hwrap_dct_platform_db_enable = 0x2;
}
void vpq_hwrap_setalldbenalbe(UINT32 onoff)
{
	if(onoff)
	{
		_g_vpq_hwrap_shp_platform_db_enable = 2;
		_g_vpq_hwrap_tnr_platform_db_enable = 2;
		_g_vpq_hwrap_dnr_platform_db_enable = 2;
		_g_vpq_hwrap_dct_platform_db_enable = 2;
	}
	else
	{
		_g_vpq_hwrap_shp_platform_db_enable = 0;
		_g_vpq_hwrap_tnr_platform_db_enable = 0;
		_g_vpq_hwrap_dnr_platform_db_enable = 0;
		_g_vpq_hwrap_dct_platform_db_enable = 0;
	}
	
}

void vpq_hwrap_switch_win_id(int winId)
{
	_g_vpq_hwrap_switch_win_id = winId;
}

