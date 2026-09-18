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

/** @file pe_proc_dbg.c
 *
 *  application test functions for picture enhance
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
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
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "base_types.h"
#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"
#include "pe_kapi.h"
#include "pe_def.h"
#include "pe_drv.h"
#include "pe_cmn.h"
#include "pe_csc.h"
#include "pe_cmg.h"
#include "pe_nrd.h"
#include "pe_dnt.h"
#include "pe_shp.h"
#include "pe_dcm.h"
#include "pe_win.h"
#include "pe_etc.h"
#include "pe_hst.h"
#include "pe_hdr.h"
#include "pe_kwrap.h"
#include "vpq_hwrap.h"
#include "vpq_hwrap_pe.h"
#include "pe_proc_dbg.h"
#include "v4l2_vpq.h"
#include "v4l2_vpq_pe.h"
#include "v4l2_lgsr.h"
#ifdef INCLUDE_O20_CHIP_KDRV
#include "pe_chpi_shp_hw_f20.h"
#include "pe_chpi_dnr_hw_f20.h"
#include "pe_chpi_tnr_hw_f20.h"
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#include "pe_dcm_ddr_reg_e60f20.h"
#endif

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
#define PE_PROC_DBG_WRAP_PATH		"/proc/lg/pe/dbg_wrap_func"
#define PE_PROC_DBG_KDRV_PATH		"/proc/lg/pe/dbg_kdrv_func"
#define PE_PROC_IOC_BLOK_PATH		"/proc/lg/pe/ioct_blocking"

#define PE_PROC_DBG_USAGE_NUM		0xfff

/* ver, yyyy/mm/dd/hh:mm */
#define PE_PROC_DBG_WRAP_VER		"2021/06/28/15:30"
#define PE_PROC_DBG_KDRV_VER		"2025/08/20/15:30"

/* ver, rev xxxx */
#define PE_PROC_DBG_DEFAULT_VER		"rev.14169"

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#if 0	//org
/** 511/360=1.41944, 360/511=0.70450
* 0~360~540degree <-> 0x0~0x1ff(511)~0x2ff(767)
* if degree to 10bit & x=361~540
* : (x*255)/179 - 2.2573 + 0.5 = x*1.42458 - 1.7573
* if 10bit to degree & x=512~766
* : (x+2.273)*179/255 + 0.5 = x*0.70196 + 2.09556 */
#define PE_KADP_CONV_DEGREE_TO_10BIT(x)	\
	(((x)<=360)? ((UINT16)(((float)(x)*1.41944)+0.5)):(((x)<541)? ((UINT16)(((float)(x)*1.42458)-1.7573)):(767)))
#define PE_KADP_CONV_10BIT_TO_DEGREE(x)	\
	(((x)<=511)? ((UINT16)(((float)(x)*0.7045)+0.5)):(((x)<767)? ((UINT16)(((float)(x)*0.70196)+2.09556)):(540)))

/* 127/100=1.27, 100/127=0.7874, 0~100 <-> 0x0~0xff(127) */
#define PE_KADP_CONV_PERCENT_TO_8BIT(x)	\
	(((x)>=100)? (127):((UINT8)((float)(x)*1.27+0.5)))
#define PE_KADP_CONV_8BIT_TO_PERCENT(x)	\
	(((x)>=127)? (100):((UINT8)((float)(x)*0.7874+0.5)))
#endif

#define PE_PROC_CONV_DEGREE_TO_10BIT(x)	\
	(((x)<=360)? ((((x)*1454)+512)>>10):(((x)<541)? ((((x)*1459)-1800)>>10):(767)))

#define PE_PROC_CONV_PERCENT_TO_8BIT(x)	\
	(((x)>=100)? (127):(((x)*1270+512)>>10))

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/
#if 0
typedef enum {
	PE_PROC_DBG_KWRAP_FUNC_OPEN            = 0x0,
	PE_PROC_DBG_KWRAP_FUNC_CLOSE           = 0x1,
	PE_PROC_DBG_KWRAP_FUNC_INIT            = 0x2,
	PE_PROC_DBG_KWRAP_FUNC_CONTRAST        = 0x10,
	PE_PROC_DBG_KWRAP_FUNC_BRIGHT          = 0x11,
	PE_PROC_DBG_KWRAP_FUNC_SATURATION      = 0x12,
	PE_PROC_DBG_KWRAP_FUNC_HUE             = 0x13,
	PE_PROC_DBG_KWRAP_FUNC_INCSC           = 0x30,
	PE_PROC_DBG_KWRAP_FUNC_OUTCSC          = 0x31,
	PE_PROC_DBG_KWRAP_FUNC_TONELUT         = 0x60,
	PE_PROC_DBG_KWRAP_FUNC_MAX
}PE_PROC_DBG_KWRAP_FUNCNUM;
#endif

typedef enum {
	PE_PROC_DBG_WRAP_FUNC_INIT            = 0,
	PE_PROC_DBG_WRAP_FUNC_UNINIT          = 1,
	PE_PROC_DBG_WRAP_FUNC_PICCTRL         = 2,
	PE_PROC_DBG_WRAP_FUNC_BLKLVL_EN       = 3,
	PE_PROC_DBG_WRAP_FUNC_BLKLVL          = 4,
	PE_PROC_DBG_WRAP_FUNC_MUTEONOFF       = 5,
	PE_PROC_DBG_WRAP_FUNC_BLKLVL2         = 6,
	PE_PROC_DBG_WRAP_FUNC_LOWDELAY        = 7,
	PE_PROC_DBG_WRAP_FUNC_MAX
}PE_PROC_DBG_HWRAP_FUNCNUM;

typedef enum {
	PE_PROC_DBG_KDRV_FUNC_MSG                = 0x0,
	PE_PROC_DBG_KDRV_FUNC_LOGM               = 0x1,
	PE_PROC_DBG_KDRV_FUNC_TASK_OPERATION     = 0x2,
	PE_PROC_DBG_KDRV_FUNC_GET_PIC_DISP_INFO  = 0x3,
	PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT_ITEM = 0x4,
	PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT      = 0x5,
	PE_PROC_DBG_KDRV_FUNC_PRINT_DDR_DB       = 0x6,
	PE_PROC_DBG_KDRV_FUNC_PRINT_LGSR_DDR_DB  = 0x7,
	PE_PROC_DBG_KDRV_FUNC_BLOCK_PE_FUNCTION  = 0x8,
	PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB     = 0x9,
	PE_PROC_DBG_KDRV_FUNC_PRINT_LGSR_STATUS  = 0xa,
	PE_PROC_DBG_KDRV_FUNC_PRINT_SHP          = 0xb,
	PE_PROC_DBG_KDRV_FUNC_PRINT_SHP_SQM      = 0xc,
	PE_PROC_DBG_KDRV_FUNC_PRINT_NR_SQM       = 0xd,
	PE_PROC_DBG_KDRV_FUNC_LLLUT       		 = 0xe,
	PE_PROC_DBG_KDRV_FUNC_GET_LLLUT          = 0xf,
	PE_PROC_DBG_KDRV_FUNC_BLOCK_LGSR  		 = 0x10,
	PE_PROC_DBG_KDRV_FUNC_PRINT_F20_DDR_DB   = 0x11,
	PE_PROC_DBG_KDRV_FUNC_PRINT_F20_LGSR_DDR_DB  = 0x12,
	PE_PROC_DBG_KDRV_FUNC_GET_PIC_GENE_INFO  = 0x13,
	PE_PROC_DBG_KDRV_FUNC_GET_F20_TBL_SHP    = 0x14,
	PE_PROC_DBG_KDRV_FUNC_SET_DCE_LUT_ACCEL  = 0x15,
	PE_PROC_DBG_KDRV_FUNC_SET_DCE_DB		 = 0x16,
	PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB  		 = 0x17,
	PE_PROC_DBG_KDRV_FUNC_CMP_LGSR_DB  		 = 0x18,
	PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB_INFO	 = 0x19,
	PE_PROC_DBG_KDRV_FUNC_GET_CEN_RERION	 = 0x1a,
	PE_PROC_DBG_KDRV_FUNC_SET_AI_FACE		 = 0x1b,
	PE_PROC_DBG_KDRV_FUNC_SWITCH_HISTO		 = 0x1c,
	PE_PROC_DBG_KDRV_FUNC_GET_DBC_DB		 = 0x1d,
	PE_PROC_DBG_KDRV_FUNC_SWITCH_WID		 = 0x1f,
	PE_PROC_DBG_KDRV_FUNC_GET_LGSR_INFO		 = 0x20,
	PE_PROC_DBG_KDRV_FUNC_MAX
}PE_PROC_DBG_KDRV_FUNCNUM;

typedef enum
{
	PE_PROC_INPUT_CSC_BYPASS = 0,		///< ycbcr to ycbcr
	PE_PROC_INPUT_CSC_LIMIT,			///< ycbcr(0~255) to ycbcr(16~235)
	PE_PROC_INPUT_CSC_EXPEND,			///< ycbcr(32~235) to ycbcr(16~235)
	PE_PROC_INPUT_CSC_EXPEND_CVD,		///< ycbcr(32~235) to ycbcr(16~235)
	PE_PROC_INPUT_CSC_RGB_Y709_LINEAR,	///< rgb(16~235) to y709(16~235)
	PE_PROC_INPUT_CSC_RGB_Y709_LIMIT,	///< rgb(0~255) to y709(16~235)
	PE_PROC_INPUT_CSC_RGB_Y601_LINEAR,	///< rgb(16~235) to y601(16~235)
	PE_PROC_INPUT_CSC_RGB_Y601_LIMIT,	///< rgb(0~255) to y601(16~235)
	PE_PROC_INPUT_CSC_RGB_Y601_SECAM,	///< rgb(16~235) to y601(16~235), for secam
	PE_PROC_INPUT_CSC_NUM				///< max num
}
PE_PROC_INPUT_CSC_TYPE;

typedef enum
{
	PE_PROC_CM_REGION_WHT = 0,	///< white
	PE_PROC_CM_REGION_WTB,		///< white blue
	PE_PROC_CM_REGION_BLK,		///< black
	PE_PROC_CM_REGION_SKN,		///< skin
	PE_PROC_CM_REGION_GRN,		///< green
	PE_PROC_CM_REGION_BLU,		///< blue
	PE_PROC_CM_REGION_RED,		///< red
	PE_PROC_CM_REGION_YEL,		///< yellow
	PE_PROC_CM_REGION_MGT,		///< magenta
	PE_PROC_CM_REGION_CYN,		///< cyan
	PE_PROC_CM_REGION_R10,		///< reserved region 10th
	PE_PROC_CM_REGION_R11,		///< reserved region 11th
	PE_PROC_CM_REGION_R12,		///< reserved region 12th
	PE_PROC_CM_REGION_R13,		///< reserved region 13th
	PE_PROC_CM_REGION_R14,		///< reserved region 14th
	PE_PROC_CM_REGION_R15,		///< reserved region 15th
	PE_PROC_CM_REGION_NUM		///< max num
}
PE_PROC_CM_REGION_TYPE;

#define PE_DBG_SRC_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_SRC_DTV)?			"LX_PE_SRC_DTV":\
	((_x)==LX_PE_SRC_ATV)?			"LX_PE_SRC_ATV":\
	((_x)==LX_PE_SRC_CVBS)?			"LX_PE_SRC_CVBS":\
	((_x)==LX_PE_SRC_SCART)?		"LX_PE_SRC_SCART":\
	((_x)==LX_PE_SRC_COMP)?			"LX_PE_SRC_COMP":\
	((_x)==LX_PE_SRC_RGBPC)?		"LX_PE_SRC_RGBPC":\
	((_x)==LX_PE_SRC_HDMI)?			"LX_PE_SRC_HDMI":\
	"LX_PE_SRC_NUM")

#define PE_DBG_FMT_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_FMT_SD)?			"LX_PE_FMT_SD":\
	((_x)==LX_PE_FMT_HD)?			"LX_PE_FMT_HD":\
	((_x)==LX_PE_FMT_UHD)?			"LX_PE_FMT_UHD":\
	"LX_PE_FMT_NUM")

#define PE_DBG_CSTD_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_CSTD_NTSC)?		"LX_PE_CSTD_NTSC":\
	((_x)==LX_PE_CSTD_PAL)?			"LX_PE_CSTD_PAL":\
	((_x)==LX_PE_CSTD_SECAM)?		"LX_PE_CSTD_SECAM":\
	"LX_PE_CSTD_NUM")

#define PE_DBG_HDMI_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_HDMI_TV)?			"LX_PE_HDMI_TV":\
	((_x)==LX_PE_HDMI_PC)?			"LX_PE_HDMI_PC":\
	"LX_PE_HDMI_NUM")

#define PE_DBG_SCART_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_SCART_AV)?			"LX_PE_SCART_AV":\
	((_x)==LX_PE_SCART_RGB)?		"LX_PE_SCART_RGB":\
	"LX_PE_SCART_NUM")

#define PE_DBG_FR_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_FR_60HZ)?			"LX_PE_FR_60HZ":\
	((_x)==LX_PE_FR_50HZ)?			"LX_PE_FR_50HZ":\
	"LX_PE_FR_NUM")

#define PE_DBG_OUT_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_OUT_2D)?			"LX_PE_OUT_2D":\
	((_x)==LX_PE_OUT_3D_2D)?		"LX_PE_OUT_3D_2D":\
	((_x)==LX_PE_OUT_2D_3D)?		"LX_PE_OUT_2D_3D":\
	((_x)==LX_PE_OUT_UD)?			"LX_PE_OUT_UD":\
	((_x)==LX_PE_OUT_TB)?			"LX_PE_OUT_TB":\
	((_x)==LX_PE_OUT_SS)?			"LX_PE_OUT_SS":\
	((_x)==LX_PE_OUT_FS)?			"LX_PE_OUT_FS":\
	((_x)==LX_PE_OUT_LA)?			"LX_PE_OUT_LA":\
	((_x)==LX_PE_OUT_DUAL_TB)?		"LX_PE_OUT_DUAL_TB":\
	((_x)==LX_PE_OUT_DUAL_SS)?		"LX_PE_OUT_DUAL_SS":\
	((_x)==LX_PE_OUT_DUAL_FULL)?	"LX_PE_OUT_DUAL_FULL":\
	((_x)==LX_PE_OUT_PIP)?			"LX_PE_OUT_PIP":\
	"LX_PE_OUT_NUM")

#define PE_DBG_SCAN_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_SCAN_INTERLACE)?	"LX_PE_SCAN_INTERLACE":\
	((_x)==LX_PE_SCAN_PROGRESS)?	"LX_PE_SCAN_PROGRESS":\
	"LX_PE_SCAN_NUM")

#define PE_DBG_DTV_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_DTV_NORMAL)?		"LX_PE_DTV_NORMAL":\
	((_x)==LX_PE_DTV_FILEPLAY)?		"LX_PE_DTV_FILEPLAY":\
	((_x)==LX_PE_DTV_HDDPLAY)?		"LX_PE_DTV_HDDPLAY":\
	((_x)==LX_PE_DTV_PHOTOPLAY)?	"LX_PE_DTV_PHOTOPLAY":\
	((_x)==LX_PE_DTV_TESTPIC)?		"LX_PE_DTV_TESTPIC":\
	((_x)==LX_PE_DTV_CAMERA)?		"LX_PE_DTV_CAMERA":\
	((_x)==LX_PE_DTV_INVALID)?		"LX_PE_DTV_INVALID":\
	"LX_PE_DTV_NUM")

#define PE_DBG_HDD_TYPE_TO_STR(_x)		(\
	((_x)==LX_PE_HDD_SRC_DTV)?		"LX_PE_HDD_SRC_DTV":\
	((_x)==LX_PE_HDD_SRC_ATV60)?	"LX_PE_HDD_SRC_ATV60":\
	((_x)==LX_PE_HDD_SRC_ATV50)?	"LX_PE_HDD_SRC_ATV50":\
	((_x)==LX_PE_HDD_SRC_AV60)?		"LX_PE_HDD_SRC_AV60":\
	((_x)==LX_PE_HDD_SRC_AV50)?		"LX_PE_HDD_SRC_AV50":\
	((_x)==LX_PE_HDD_SRC_SCARTRGB)?	"LX_PE_HDD_SRC_SCARTRGB":\
	((_x)==LX_PE_HDD_SRC_INVALID)?	"LX_PE_HDD_SRC_INVALID":\
	"LX_PE_HDD_SRC_NUM")

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/
#ifdef INCLUDE_O22_CHIP_KDRV
extern UINT32 g_hst_hw_o22_switch_hdr_hist;
#endif
/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/
static int pe_proc_dbg_getwinid (UINT32 wid);
static void pe_proc_dbg_showdisplayinfo(LX_PE_INF_DISPLAY_T *info);


/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/
/* input(cvi) csc */
const unsigned short g_pe_proc_dbg_input_mtrx_bypass[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0x0000, 0x0000,		//  1.0000, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const unsigned short g_pe_proc_dbg_input_mtrx_limit[PE_NUM_OF_CSC_COEF]= {
	0x0db0, 0x0000, 0x0000,		//  0.8555, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const unsigned short g_pe_proc_dbg_input_mtrx_expend[PE_NUM_OF_CSC_COEF]= {
	0x1166, 0x0000, 0x0000,		//  1.0874, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const unsigned short g_pe_proc_dbg_input_mtrx_expend_cvd[PE_NUM_OF_CSC_COEF]= {
	0x1142, 0x0000, 0x0000,		//  1.0786, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const unsigned short g_pe_proc_dbg_input_rgb_y709_linear[PE_NUM_OF_CSC_COEF]= {
	0x0b70, 0x0126, 0x0368,		//  0.7148, 0.0718, 0.2129
	0xf9b3, 0x082d, 0xfe22,		// -0.3938, 0.5110,-0.1167
	0xf894, 0xff40, 0x082d};	// -0.4639,-0.0469, 0.5110
const unsigned short g_pe_proc_dbg_input_rgb_y709_limit[PE_NUM_OF_CSC_COEF]= {
	0x09d2, 0x00fd, 0x02ed,		//  0.6138, 0.0618, 0.1829
	0xfa98, 0x0706, 0xfe62,		// -0.3379, 0.4390,-0.1011
	0xf99e, 0xff5d, 0x0706};	// -0.3989,-0.0398, 0.4390
const unsigned short g_pe_proc_dbg_input_rgb_y601_linear[PE_NUM_OF_CSC_COEF]= {
	0x0964, 0x01d2, 0x04c8,		//  0.5869, 0.1138, 0.2988
	0xfa94, 0x082d, 0xfd40,		// -0.3389, 0.5110,-0.1719
	0xf927, 0xfead, 0x082d};	// -0.4280,-0.0828, 0.5110
const unsigned short g_pe_proc_dbg_input_rgb_y601_limit[PE_NUM_OF_CSC_COEF]= {
	0x0810, 0x0191, 0x041c,		//  0.5039, 0.0979, 0.2568
	0xfb59, 0x0706, 0xfda2,		// -0.2908, 0.4390,-0.1479
	0xfa1d, 0xfede, 0x0706};	// -0.3679,-0.0708, 0.4390
const unsigned short g_pe_proc_dbg_input_rgb_y601_secam[PE_NUM_OF_CSC_COEF]= {
	0x1000, 0x0000, 0x0000,		//  1.0000, 0.0000, 0.0000
	0x0000, 0x0de4, 0x0000,		//  0.0000, 0.8682, 0.0000
	0x0000, 0x0000, 0x131f};	//  0.0000, 0.0000, 1.1951
const unsigned short g_pe_proc_dbg_input_ofst_bypass[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0000, 0x0000, 0x0000};	//   0,   0,   0
const unsigned short g_pe_proc_dbg_input_ofst_limit[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0040, 0x0000, 0x0000};	//  64,   0,   0
const unsigned short g_pe_proc_dbg_input_ofst_expend[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0xffae, 0x0000, 0x0000};	// -82,   0,   0
const unsigned short g_pe_proc_dbg_input_ofst_expend_cvd[PE_NUM_OF_CSC_OFST] = {
	0x0780, 0x0000, 0x0000,		//-128,   0,   0
	0x0040, 0x0000, 0x0000};	//  64,   0,   0
const unsigned short g_pe_proc_dbg_input_ofst_rgb_y_linear[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0000, 0x0200, 0x0200};	//   0, 512, 512
const unsigned short g_pe_proc_dbg_input_ofst_rgb_y_limit[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0040, 0x0200, 0x0200};	//  64, 512, 512
const unsigned short g_pe_proc_dbg_input_ofst_rgb_y_secam[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0xfe00, 0xfe00,		//   0,-512,-512
	0x0000, 0x0200, 0x0200};	//   0, 512, 512

#if 0	//region number
CMG_RGN_COL_WHT = 0,	///< 00.white
CMG_RGN_COL_WTB,		///< 01.white blue
CMG_RGN_COL_BLK,		///< 02.black
CMG_RGN_COL_SKN,		///< 03.skin
CMG_RGN_COL_GRN,		///< 04.green
CMG_RGN_COL_BLU,		///< 05.blue
CMG_RGN_COL_RED,		///< 06.red
CMG_RGN_COL_YEL,		///< 07.yellow
CMG_RGN_COL_MGT,		///< 08.magenta
CMG_RGN_COL_CYN,		///< 09.cyan
CMG_RGN_COL_R10,		///< 10
CMG_RGN_COL_R11,		///< 11
CMG_RGN_COL_R12,		///< 12
CMG_RGN_COL_R13,		///< 13
CMG_RGN_COL_R14,		///< 14
CMG_RGN_COL_R15,		///< 15
#endif

const LX_PE_CMG_REGION_ONE_T _g_pe_proc_cm_region_0[16] = {
	{{0, 35, 100, 150, 200, 250, 300, 360},
		{127, 127, 127, 127, 127, 127, 127, 127},
		{0, 5, 10, 15, 17, 21, 24, 27},
		{127, 127, 127, 127, 110, 70, 30, 0},
		{60, 100, 120, 140, 160, 190, 250, 255},
		{0, 45, 65, 80, 100, 80, 50, 20}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{359, 370, 380, 390, 395, 400, 410, 415},
		{0, 95, 120, 127, 127, 127, 80, 0},
		{30, 40, 50, 60, 90, 95, 98, 100},
		{0, 50, 95, 127, 127, 127, 127, 127},
		{15, 35, 55, 100, 170, 210, 230, 255},
		{0, 70, 127, 127, 127, 60, 30, 0}},
	{{60, 68, 75, 80, 120, 130, 140, 150},
		{0, 45, 90, 127, 127, 90, 45, 0},
		{30, 35, 40, 50, 70, 80, 90, 100},
		{0, 35, 70, 127, 127, 127, 127, 127},
		{30, 50, 80, 100, 144, 180, 216, 255},
		{0, 80, 127, 127, 127, 127, 127, 127}},
	{{155, 165, 175, 190, 240, 250, 260, 275},
		{0, 75, 127, 127, 127, 127, 100, 0},
		{0, 15, 30, 40, 80, 90, 98, 100},
		{0, 50, 100, 127, 127, 127, 127, 127},
		{0, 50, 70, 90, 100, 140, 245, 255},
		{0, 50, 75, 110, 127, 127, 127, 127}},
	{{320, 325, 330, 335, 363, 366, 372, 375},
		{0, 45, 90, 127, 127, 127, 90, 0},
		{35, 45, 55, 60, 75, 80, 90, 100},
		{0, 50, 100, 127, 127, 127, 127, 127},
		{35, 60, 90, 120, 150, 180, 210, 230},
		{0, 70, 110, 127, 127, 100, 40, 0}},
	{{41, 50, 55, 60, 65, 70, 75, 80},
		{0, 45, 90, 127, 127, 90, 45, 0},
		{35, 40, 45, 54, 65, 75, 85, 100},
		{0, 35, 70, 127, 127, 127, 127, 127},
		{20, 50, 75, 108, 144, 180, 216, 255},
		{0, 70, 127, 127, 127, 127, 127, 127}},
	{{275, 280, 285, 290, 300, 305, 310, 315},
		{0, 45, 90, 127, 127, 90, 45, 0},
		{0, 25, 40, 50, 60, 70, 90, 100},
		{0, 80, 127, 127, 127, 127, 127, 0},
		{30, 55, 80, 108, 144, 180, 216, 255},
		{0, 60, 127, 127, 127, 127, 127, 127}},
	{{150, 158, 167, 175, 184, 192, 201, 210},
		{0, 60, 110, 127, 127, 110, 60, 0},
		{15, 27, 39, 52, 64, 76, 88, 100},
		{0, 80, 120, 127, 127, 127, 127, 127},
		{50, 70, 90, 120, 144, 180, 216, 255},
		{0, 20, 50, 90, 110, 127, 127, 127}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}}
};
const LX_PE_CMG_REGION_ONE_T _g_pe_proc_cm_region_1[16] = {
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{90, 98, 107, 115, 124, 132, 141, 150},
		{0, 60, 110, 127, 127, 110, 60, 0},
		{15, 27, 39, 52, 64, 76, 88, 100},
		{0, 80, 120, 127, 127, 127, 127, 127},
		{50, 70, 90, 120, 144, 180, 216, 255},
		{0, 20, 50, 90, 110, 127, 127, 127}},
	{{210, 218, 227, 235, 244, 252, 261, 270},
		{0, 60, 110, 127, 127, 110, 60, 0},
		{15, 27, 39, 52, 64, 76, 88, 100},
		{0, 80, 120, 127, 127, 127, 127, 127},
		{50, 70, 90, 120, 144, 180, 216, 255},
		{0, 20, 50, 90, 110, 127, 127, 127}},
	{{330, 338, 347, 355, 364, 372, 381, 390},
		{0, 60, 110, 127, 127, 110, 60, 0},
		{15, 27, 39, 52, 64, 76, 88, 100},
		{0, 80, 120, 127, 127, 127, 127, 127},
		{50, 70, 90, 120, 144, 180, 216, 255},
		{0, 20, 50, 90, 115, 127, 127, 127}},
	{{30, 38, 47, 55, 64, 72, 81, 90},
		{0, 60, 110, 127, 127, 110, 60, 0},
		{15, 27, 39, 52, 64, 76, 88, 100},
		{0, 80, 120, 127, 127, 127, 127, 127},
		{50, 70, 90, 120, 144, 180, 216, 255},
		{0, 20, 50, 90, 110, 127, 127, 127}},
	{{270, 278, 287, 295, 304, 312, 321, 330},
		{0, 60, 110, 127, 127, 110, 60, 0},
		{15, 27, 39, 52, 64, 76, 88, 100},
		{0, 80, 120, 127, 127, 127, 127, 127},
		{50, 70, 90, 120, 144, 180, 216, 255},
		{0, 20, 50, 90, 110, 127, 127, 127}},
	{{150, 158, 167, 175, 184, 192, 201, 210},
		{0, 60, 110, 127, 127, 110, 60, 0},
		{15, 27, 39, 52, 64, 76, 88, 100},
		{0, 80, 120, 127, 127, 127, 127, 127},
		{50, 70, 90, 120, 144, 180, 216, 255},
		{0, 20, 50, 90, 110, 127, 127, 127}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}}
};

/*============================================================================
	Implementation Group
============================================================================*/
#if 0	//example
void pe_proc_dbg_kwrap_help(void)
{
	printk("----------------------------------------\n");
	printk("status\n");
	printk("----------------------------------------\n");
	printk(" chip ver.:0x%X,  kwrap chip ver.:0x%08X\n", lx_chip_rev(), g_pe_kwrap_ver_mask);
	printk(" open(%d), init(%d)\n", pe_kwrap_isopened(), pe_kwrap_isinitialized());
	printk("----------------------------------------\n");
	printk("dbg_kwrap_func\n");
	printk("----------------------------------------\n");
	printk(" OPEN : echo %x > %s\n",PE_PROC_DBG_KWRAP_FUNC_OPEN,PE_PROC_DBG_KWRAP_PATH);
	printk(" CLOSE : echo %x > %s\n",PE_PROC_DBG_KWRAP_FUNC_CLOSE,PE_PROC_DBG_KWRAP_PATH);
	printk(" INIT : echo %x > %s\n",PE_PROC_DBG_KWRAP_FUNC_INIT,PE_PROC_DBG_KWRAP_PATH);
	printk("----------------------------------------\n");
	printk(" CONTRAST : echo %x [wid] [val] > %s\n",PE_PROC_DBG_KWRAP_FUNC_CONTRAST,PE_PROC_DBG_KWRAP_PATH);
	printk(" BRIGNT : echo %x [wid] [val] > %s\n",PE_PROC_DBG_KWRAP_FUNC_BRIGHT,PE_PROC_DBG_KWRAP_PATH);
	printk(" SATURATION : echo %x [wid] [val] > %s\n",PE_PROC_DBG_KWRAP_FUNC_SATURATION,PE_PROC_DBG_KWRAP_PATH);
	printk(" HUE : echo %x [wid] [val] > %s\n",PE_PROC_DBG_KWRAP_FUNC_HUE,PE_PROC_DBG_KWRAP_PATH);
	printk(" INCSC : echo %x [wid] [type] > %s\n",PE_PROC_DBG_KWRAP_FUNC_INCSC,PE_PROC_DBG_KWRAP_PATH);
	printk(" OUTCSC : echo %x [wid] [type] > %s\n",PE_PROC_DBG_KWRAP_FUNC_OUTCSC,PE_PROC_DBG_KWRAP_PATH);
	printk(" TONELUT : echo %x [wid] [path] [lut] > %s\n",PE_PROC_DBG_KWRAP_FUNC_TONELUT,PE_PROC_DBG_KWRAP_PATH);
	printk(" >> usage : echo [funcnum] %x > %s\n",PE_PROC_DBG_USAGE_NUM,PE_PROC_DBG_KWRAP_PATH);
	printk("----------------------------------------\n");
	return;
}

void pe_proc_dbg_kwrap_func(char *command)
{
	int ret = RET_OK;
	UINT32 val[5];
	PE_PROC_DBG_KWRAP_FUNCNUM func_num;
	sscanf(command," %x",(int *)&func_num);
	printk(" ** kwrap dbg func num : 0x%x, command : %s\n",func_num,command);
	switch(func_num)
	{
		case PE_PROC_DBG_KWRAP_FUNC_OPEN:
		{
			printk("pe_kwrap_open\n");
			pe_kwrap_open();
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_CLOSE:
		{
			printk("pe_kwrap_close\n");
			pe_kwrap_close();
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_INIT:
		{
			printk("pe_kwrap_init\n");
			pe_kwrap_init();
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_CONTRAST:
		{
			sscanf(command," %x %x %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" CONTRAST : echo %x [wid] [value] > %s\n",PE_PROC_DBG_KWRAP_FUNC_CONTRAST,PE_PROC_DBG_KWRAP_PATH);
				printk("   contrast(0~512~1023, else:get)\n");
				printk("\n");
				break;
			}
			printk("   wid:%d\n",val[0]);
			printk("   contrast(0~512~1023, else:get) : %x\n",val[1]);
			if (val[1]<1024)
			{
				LX_PE_CMN_CONTRAST_T param;
				param.win_id = val[0];
				param.contrast = (UINT16)val[1];
				ret = KWRAP_PE_SetContrast((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_SetContrast() error\n", __F__, __L__);
					break;
				}
			}
			else
			{
				LX_PE_CMN_CONTRAST_T param;
				param.win_id = val[0];
				ret = KWRAP_PE_GetContrast((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_GetContrast() error\n", __F__, __L__);
					break;
				}
				printk("[wid:%d] contrast : %d\n",param.win_id,param.contrast);
			}
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_BRIGHT:
		{
			sscanf(command," %x %x %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" BRIGHT : echo %x [wid] [value] > %s\n",PE_PROC_DBG_KWRAP_FUNC_BRIGHT,PE_PROC_DBG_KWRAP_PATH);
				printk("   bright(0~512~1023, else:get)\n");
				printk("\n");
				break;
			}
			printk("   wid:%d\n",val[0]);
			printk("   bright(0~512~1023, else:get) : %x\n",val[1]);
			if (val[1]<1024)
			{
				LX_PE_CMN_BRIGHTNESS_T param;
				param.win_id = val[0];
				param.brightness = (UINT16)val[1];
				ret = KWRAP_PE_SetBrightness((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_SetBrightness() error\n", __F__, __L__);
					break;
				}
			}
			else
			{
				LX_PE_CMN_BRIGHTNESS_T param;
				param.win_id = val[0];
				ret = KWRAP_PE_GetBrightness((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_GetBrightness() error\n", __F__, __L__);
					break;
				}
				printk("[wid:%d] bright : %d\n",param.win_id,param.brightness);
			}
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_SATURATION:
		{
			sscanf(command," %x %x %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" SATURATION : echo %x [wid] [value] > %s\n",PE_PROC_DBG_KWRAP_FUNC_SATURATION,PE_PROC_DBG_KWRAP_PATH);
				printk("   saturation(0~128~255, else:get)\n");
				printk("\n");
				break;
			}
			printk("   wid:%d\n",val[0]);
			printk("   saturation(0~128~255, else:get) : %x\n",val[1]);
			if (val[1]<256)
			{
				LX_PE_CMN_SATURATION_T param;
				param.win_id = val[0];
				param.saturation = (UINT16)val[1];
				ret = KWRAP_PE_SetSaturation((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_SetSaturation() error\n", __F__, __L__);
					break;
				}
			}
			else
			{
				LX_PE_CMN_SATURATION_T param;
				param.win_id = val[0];
				ret = KWRAP_PE_GetSaturation((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_GetSaturation() error\n", __F__, __L__);
					break;
				}
				printk("[wid:%d] saturation : %d\n",param.win_id,param.saturation);
			}
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_HUE:
		{
			sscanf(command," %x %x %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" HUE : echo %x [wid] [value] > %s\n",PE_PROC_DBG_KWRAP_FUNC_HUE,PE_PROC_DBG_KWRAP_PATH);
				printk("   hue(0~128~255, else:get)\n");
				printk("\n");
				break;
			}
			printk("   wid:%d\n",val[0]);
			printk("   hue(0~128~255, else:get) : %x\n",val[1]);
			if (val[1]<256)
			{
				LX_PE_CMN_HUE_T param;
				param.win_id = val[0];
				param.hue = (UINT16)val[1];
				ret = KWRAP_PE_SetHue((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_SetHue() error\n", __F__, __L__);
					break;
				}
			}
			else
			{
				LX_PE_CMN_HUE_T param;
				param.win_id = val[0];
				ret = KWRAP_PE_GetHue((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_GetHue() error\n", __F__, __L__);
					break;
				}
				printk("[wid:%d] hue : %d\n",param.win_id,param.hue);
			}
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_INCSC:
		{
			sscanf(command," %x %x %x",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" INCSC   : echo %x [wid] [type] > %s\n",PE_PROC_DBG_KWRAP_FUNC_INCSC,PE_PROC_DBG_KWRAP_PATH);
				printk("   type : \n");
				printk("   [00] PE_PROC_INPUT_CSC_BYPASS\n");
				printk("   [01] PE_PROC_INPUT_CSC_LIMIT\n");
				printk("   [02] PE_PROC_INPUT_CSC_EXPEND\n");
				printk("   [03] PE_PROC_INPUT_CSC_EXPEND_CVD\n");
				printk("   [04] PE_PROC_INPUT_CSC_RGB_Y709_LINEAR\n");
				printk("   [05] PE_PROC_INPUT_CSC_RGB_Y709_LIMIT\n");
				printk("   [06] PE_PROC_INPUT_CSC_RGB_Y601_LINEAR\n");
				printk("   [07] PE_PROC_INPUT_CSC_RGB_Y601_LIMIT\n");
				printk("   [08] PE_PROC_INPUT_CSC_RGB_Y601_SECAM\n");
				printk("   else get\n");
				printk("\n");
				break;
			}
			printk("   wid:%d, type:%d\n",val[0],val[1]);
			if (val[1]<PE_PROC_INPUT_CSC_NUM)
			{
				PE_PROC_CTRL_T ctrl_param;
				ctrl_param.wid = val[0];
				ctrl_param.data = (PE_PROC_INPUT_CSC_TYPE)val[1];
				ret = KWRAP_PE_SetInputCscCtrl(&ctrl_param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_SetInputCscCtrl() error\n", __F__, __L__);
					break;
				}
			}
			else
			{
				LX_PE_CSC_INPUT_T param;
				UINT16 *coeff, *offset;
				param.win_id = val[0];
				param.enable = TRUE;
				ret = KWRAP_PE_GetInputCscParam((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_SetInputCscCtrl() error\n", __F__, __L__);
					break;
				}
				printk("\n	>>> get input csc <<< \n");
				printk("	ch_id:0x%x, en:%d\n", param.win_id, param.enable? 1:0);
				coeff = param.matrix;
				offset = param.offset;
				printk(" ----------------------------------------\n"\
					  " matrix 0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n"\
					  " matrix 3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n"\
					  " matrix 6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n", \
						coeff[0], coeff[1], coeff[2], offset[0], offset[3], \
						coeff[3], coeff[4], coeff[5], offset[1], offset[4], \
						coeff[6], coeff[7], coeff[8], offset[2], offset[5]);
				printk(" ----------------------------------------\n");
			}
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_OUTCSC:
		{
			sscanf(command," %x %x %x",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" OUTCSC  : echo %x [wid] [type] > %s\n",PE_PROC_DBG_KWRAP_FUNC_OUTCSC,PE_PROC_DBG_KWRAP_PATH);
				printk("   type : \n");
				printk("   [00] LX_PE_POST_CSC_BYPASS\n");
				printk("   [01] LX_PE_POST_CSC_Y709_EXPEND\n");
				printk("   [02] LX_PE_POST_CSC_Y709_LINEAR\n");
				printk("   [03] LX_PE_POST_CSC_Y601_EXPEND\n");
				printk("   [04] LX_PE_POST_CSC_Y601_LINEAR\n");
				printk("   [05] LX_PE_POST_CSC_2020_NCL_EX\n");
				printk("   [06] LX_PE_POST_CSC_2020_NCL_LI\n");
				printk("   [07] LX_PE_POST_CSC_2020_CL_EXP\n");
				printk("   [08] LX_PE_POST_CSC_2020_CL_LIN\n");
				printk("   [09] LX_PE_POST_CSC_YGBR_INVERS\n");
				printk("   else get\n");
				printk("\n");
				break;
			}
			printk("   wid:%d, type:%d\n",val[0],val[1]);
			if (val[1]<LX_PE_POST_CSC_NUM)
			{
				PE_PROC_CTRL_T ctrl_param;
				ctrl_param.wid = val[0];
				ctrl_param.data = (LX_PE_POST_CSC_TYPE)val[1];
				ret = KWRAP_PE_SetPostCscCtrl(&ctrl_param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_SetPostCscCtrl() error\n", __F__, __L__);
					break;
				}
			}
			else
			{
				LX_PE_CSC_POST_T param;
				UINT16 *x_coeff, *x_offst, *x_coef0, *x_coef1, *x_ofst0;
				param.win_id = val[0];
				ret = KWRAP_PE_GetPostCscParam((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_GetPostCscParam() error\n", __F__, __L__);
					break;
				}
				printk("\n	>>> get post csc <<< \n");
				printk("	wid:%d, type:%d\n", param.win_id, param.type);
				x_coeff = param.matrix;
				x_offst = param.offset;
				x_coef0 = param.coeff0;
				x_coef1 = param.coeff1;
				x_ofst0 = param.offst0;
				printk(" ------------------------------------------------------------\n"\
					  " matrix 0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n"\
					  " matrix 3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n"\
					  " matrix 6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n", \
						x_coeff[0], x_coeff[1], x_coeff[2], x_offst[0], x_offst[3], \
						x_coeff[3], x_coeff[4], x_coeff[5], x_offst[1], x_offst[4], \
						x_coeff[6], x_coeff[7], x_coeff[8], x_offst[2], x_offst[5]);
				printk(" ------------------------------------------------------------\n"\
					  " coeff0 0,1,2      = 0x%04x, 0x%04x, 0x%04x\n"\
					  " coeff0 3,4,5      = 0x%04x, 0x%04x, 0x%04x\n"\
					  " coeff0 6,7,8      = 0x%04x, 0x%04x, 0x%04x\n", \
						x_coef0[0], x_coef0[1], x_coef0[2], \
						x_coef0[3], x_coef0[4], x_coef0[5], \
						x_coef0[6], x_coef0[7], x_coef0[8]);
				printk(" ----------------------------------------------\n"\
					  " coeff1 0,1,2      = 0x%04x, 0x%04x, 0x%04x\n"\
					  " coeff1 3,4,5      = 0x%04x, 0x%04x, 0x%04x\n"\
					  " coeff1 6,7,8      = 0x%04x, 0x%04x, 0x%04x\n", \
						x_coef1[0], x_coef1[1], x_coef1[2], \
						x_coef1[3], x_coef1[4], x_coef1[5], \
						x_coef1[6], x_coef1[7], x_coef1[8]);
				printk(" ----------------------------------------------\n"\
					  " ofst0 0,3         = 0x%04x, 0x%04x\n"\
					  " ofst0 1,4         = 0x%04x, 0x%04x\n"\
					  " ofst0 2,5         = 0x%04x, 0x%04x\n", \
						x_ofst0[0], x_ofst0[3], x_ofst0[1], \
						x_ofst0[4], x_ofst0[2], x_ofst0[5]);
				printk(" ----------------------------------------------\n");
			}
		}break;
		case PE_PROC_DBG_KWRAP_FUNC_TONELUT:
		{
			sscanf(command," %x %x %x %x",(int *)&func_num,&val[0],&val[2],&val[3]);
			val[1] = 2;//fix version 2
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" TONELUT : echo %x [wid] [path] [lut] > %s\n",PE_PROC_DBG_KWRAP_FUNC_TONELUT,PE_PROC_DBG_KWRAP_PATH);
				printk("   path(0~6:sdr,dovi,h10,tec,s2h,hlg,ll, f:force)\n");
				printk("   lut(0~5:bypass,h10,h10,sdr,hlg,s2h, else:get)\n");
				printk("\n");
				break;
			}
			printk("   wid:%d, version:%d\n",val[0],val[1]);
			printk("   path(0~6:sdr,dovi,h10,tec,s2h,hlg,ll, f:force) : %x\n", val[2]);
			printk("   lut(0~5:bypass,h10,h10,sdr,hlg,s2h, else:get) : %x\n", val[3]);
			if (val[3]<0xff)
			{
				PE_PROC_CTRL_T ctrl_param;
				ctrl_param.wid = val[0];
				ctrl_param.data = val[1]<<8|val[2]<<4|val[3];
				ret = KWRAP_PE_SetHdrTonemapLutCtrl(&ctrl_param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_SetHdrTonemapLutCtrl() error\n", __F__, __L__);
					break;
				}
			}
			else
			{
				UINT32 i;
				LX_PE_HDR_TONEMAP_LUT_T param;
				param.win_id = val[0];
				param.oper = 0;
				param.size = PE_PROC_HDR_TLUT_MAX<<1;
				param.data=(UINT32 *)OS_Malloc(param.size*sizeof(UINT32));
				if (!param.data){
					printk("[%s,%d]param.data is null\n", __F__, __L__);
					break;
				}
				ret = KWRAP_PE_GetHdrTonemapLutParam((void *)&param);
				if (ret!=RET_OK){
					printk("[%s,%d]KWRAP_PE_GetHdrTonemapLutParam() error\n", __F__, __L__);
					if (param.data){OS_Free(param.data);}
					break;
				}
				printk("[wid:%d] lut size:%d\n", param.win_id, param.size);
				printk("\n   [ i]\n");
				for (i=0;i<param.size;i++)
				{
					printk("   [%03d] %08x\n", i, param.data[i]);
				}
				printk("\n");
				if (param.data){OS_Free(param.data);}
			}
		}break;
		default:
		{
			printk("invalid func numner passed from proc command\n");
		}break;
	}
	return;
}
#endif

int pe_proc_dbg_wrap_help(char* buffer)
{
	int len = 0;
	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, " dbg_wrap_func (%s)\n", PE_PROC_DBG_WRAP_VER);
	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, " PATH : %s\n", PE_PROC_DBG_WRAP_PATH);
	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, " %-10s : echo %d [resume] > PATH\n","INIT",PE_PROC_DBG_WRAP_FUNC_INIT);
	len += sprintf( buffer+len, " %-10s : echo %d > PATH\n","UNINIT",PE_PROC_DBG_WRAP_FUNC_UNINIT);
	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, " %-10s : echo %d [wid] [c] [b] [s] [h] > PATH\n","PICCTRL",PE_PROC_DBG_WRAP_FUNC_PICCTRL);
	len += sprintf( buffer+len, " %-10s : echo %d [en] > PATH\n","BLKLVL_EN",PE_PROC_DBG_WRAP_FUNC_BLKLVL_EN);
	len += sprintf( buffer+len, " %-10s : %d\n","BLKLVL_EN",vpq_hwrap_getblacklevelenable());
	len += sprintf( buffer+len, " %-10s : echo %d [wid] [type] > PATH\n","BLKLVL",PE_PROC_DBG_WRAP_FUNC_BLKLVL);
	len += sprintf( buffer+len, " %-10s : echo %d [wid] [en] > PATH\n","MUTEONOFF",PE_PROC_DBG_WRAP_FUNC_MUTEONOFF);
	len += sprintf( buffer+len, " %-10s : %d\n","MUTEONOFF",KWRAP_PE_IsMuteOn(0));
	len += sprintf( buffer+len, " %-10s : echo %d [wid] [type] > PATH\n","BLKLVL2",PE_PROC_DBG_WRAP_FUNC_BLKLVL2);
	len += sprintf( buffer+len, " %-10s : echo %d [en] > PATH\n","LOWDELAY",PE_PROC_DBG_WRAP_FUNC_LOWDELAY);
	len += sprintf( buffer+len, "----------------------------------------\n");
	return len;
}

void pe_proc_dbg_wrap_func(char *command)
{
	int ret = RET_OK;
	UINT32 val[5];
	PE_PROC_DBG_HWRAP_FUNCNUM func_num;
	sscanf(command," %x",(int *)&func_num);
	printk(" ** hwrap dbg func num : 0x%x, command : %s\n",func_num,command);
	switch(func_num)
	{
		case PE_PROC_DBG_WRAP_FUNC_INIT:
		{
			sscanf(command," %x %x",(int *)&func_num,&val[0]);
			printk("vpq_hwrap_initialize(%d)\n",val[0]);
			vpq_hwrap_initialize(val[0]);
		}break;
		case PE_PROC_DBG_WRAP_FUNC_UNINIT:
		{
			printk("vpq_hwrap_uninitialize\n");
			vpq_hwrap_uninitialize();
		}break;
		case PE_PROC_DBG_WRAP_FUNC_PICCTRL:
		{
			struct v4l2_ext_vpq_cmn_data param;
			vpq_hwrap_pic_ctrl_t ctrl_data;
			param.wid = 0;
			param.version = 0;
			param.length = sizeof(vpq_hwrap_pic_ctrl_t);
			param.p_data = (unsigned char *)&ctrl_data;
			sscanf(command," %x %x %d %d %d %d",(int *)&func_num,&val[0],&val[1],&val[2],&val[3],&val[4]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" PICCTRL : echo %x [wid] [c] [b] [s] [h] > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("   contrast(0~512~1023)\n");
				printk("   bright(0~512~1023)\n");
				printk("   saturation(0~128~255)\n");
				printk("   hue(0~128~255)\n");
				printk("   eg. echo %x 0 512 512 128 128 > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 154 512 38 128 > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 512 256 128 128 > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 512 768 128 128 > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 512 512 255 128 > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 512 512 0 128 > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 512 512 128 211 > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 9999 > %s\n",PE_PROC_DBG_WRAP_FUNC_PICCTRL,PE_PROC_DBG_WRAP_PATH);
				printk("\n");
				break;
			}
			printk("   wid:%d\n",val[0]);
			printk("   set contrast(0~512~1023) : %d\n", val[1]);
			printk("   set bright(0~512~1023) : %d\n", val[2]);
			printk("   set saturation(0~128~255) : %d\n", val[3]);
			printk("   set hue(0~128~255) : %d\n", val[4]);
			param.wid = val[0];
			if (val[1]<1024 && val[2]<1024 && val[3]<256 && val[4]<256)
			{
				ctrl_data.contrast = (int)val[1];
				ctrl_data.brightness = (int)val[2];
				ctrl_data.saturation = (int)val[3];
				ctrl_data.hue = (int)val[4];
				ret = vpq_hwrap_setpicturectrl(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_setpicturectrl() error\n", __F__, __L__);
					break;
				}
			}
			else
			{
				ret = vpq_hwrap_getpicturectrl(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_getpicturectrl() error\n", __F__, __L__);
					break;
				}
				printk("   wid:%d\n",val[0]);
				printk("   get contrast(0~512~1023) : %d\n", ctrl_data.contrast);
				printk("   get bright(0~512~1023) : %d\n", ctrl_data.brightness);
				printk("   get saturation(0~128~255) : %d\n", ctrl_data.saturation);
				printk("   get hue(0~128~255) : %d\n", ctrl_data.hue);
			}
		}break;
		case PE_PROC_DBG_WRAP_FUNC_BLKLVL_EN:
		{
			sscanf(command," %x %x",(int *)&func_num,&val[0]);
			vpq_hwrap_setblacklevelenable((int)val[0]);
		}break;
		case PE_PROC_DBG_WRAP_FUNC_BLKLVL:
		{
			struct v4l2_ext_vpq_cmn_data param;
			const unsigned short *p_mtrx, *p_ofst;
			vpq_hwrap_blacklevel_t ctrl_data;
			param.wid = 0;
			param.version = 0;
			param.length = sizeof(vpq_hwrap_blacklevel_t);
			param.p_data = (unsigned char *)&ctrl_data;
			sscanf(command," %x %x %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" BLKLVL : echo %x [wid] [type] > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   [00] LOW  ATV\n");
				printk("   [01] HIGH ATV\n");
				printk("   [02] LOW  HDMI_TV\n");
				printk("   [03] HIGH HDMI_TV\n");
				printk("   [04] LOW  HDMI_PC\n");
				printk("   [05] HIGH HDMI_PC\n");
				printk("   [06] LOW  MOVIE\n");
				printk("   [07] HIGH MOVIE\n");
				printk("   [99] exit\n");
				printk("   eg. echo %x 0 0 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 1 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 2 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 3 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 4 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 5 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 6 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 7 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 99 > %s\n",PE_PROC_DBG_WRAP_FUNC_BLKLVL,PE_PROC_DBG_WRAP_PATH);
				printk("\n");
				break;
			}
			printk("   wid:%d\n",val[0]);
			printk("   set type : %d\n", val[1]);
			param.wid = val[0];
			if (val[1]>10) {printk(" exit.\n");break;}
			if (val[1]==0) {
				ctrl_data.blacklevel = 0;
				ctrl_data.inputinfo = VPQ_HWRAP_INPUT_ATV;
				val[4] = PE_PROC_INPUT_CSC_BYPASS;
			}
			else if (val[1]==1) {
				ctrl_data.blacklevel = 1;
				ctrl_data.inputinfo = VPQ_HWRAP_INPUT_ATV;
				val[4] = PE_PROC_INPUT_CSC_EXPEND_CVD;
			}
			else if (val[1]==2) {
				ctrl_data.blacklevel = 0;
				ctrl_data.inputinfo = VPQ_HWRAP_INPUT_HDMI_TV;
				val[4] = PE_PROC_INPUT_CSC_BYPASS;
			}
			else if (val[1]==3) {
				ctrl_data.blacklevel = 1;
				ctrl_data.inputinfo = VPQ_HWRAP_INPUT_HDMI_TV;
				val[4] = PE_PROC_INPUT_CSC_LIMIT;
			}
			else if (val[1]==4) {
				ctrl_data.blacklevel = 0;
				ctrl_data.inputinfo = VPQ_HWRAP_INPUT_HDMI_PC;
				val[4] = PE_PROC_INPUT_CSC_RGB_Y709_LINEAR;
			}
			else if (val[1]==5) {
				ctrl_data.blacklevel = 1;
				ctrl_data.inputinfo = VPQ_HWRAP_INPUT_HDMI_PC;
				val[4] = PE_PROC_INPUT_CSC_RGB_Y709_LIMIT;
			}
			else if (val[1]==6) {
				ctrl_data.blacklevel = 0;
				ctrl_data.inputinfo = VPQ_HWRAP_INPUT_MEDIA_MOVIE;
				val[4] = PE_PROC_INPUT_CSC_BYPASS;
			}
			else {
				ctrl_data.blacklevel = 1;
				ctrl_data.inputinfo = VPQ_HWRAP_INPUT_MEDIA_MOVIE;
				val[4] = PE_PROC_INPUT_CSC_BYPASS;
			}
			switch (val[4])
			{
				case PE_PROC_INPUT_CSC_BYPASS:
					p_mtrx=g_pe_proc_dbg_input_mtrx_bypass;
					p_ofst=g_pe_proc_dbg_input_ofst_bypass;
					break;
				case PE_PROC_INPUT_CSC_LIMIT:
					p_mtrx=g_pe_proc_dbg_input_mtrx_limit;
					p_ofst=g_pe_proc_dbg_input_ofst_limit;
					break;
				case PE_PROC_INPUT_CSC_EXPEND:
					p_mtrx=g_pe_proc_dbg_input_mtrx_expend;
					p_ofst=g_pe_proc_dbg_input_ofst_expend;
					break;
				case PE_PROC_INPUT_CSC_EXPEND_CVD:
					p_mtrx=g_pe_proc_dbg_input_mtrx_expend_cvd;
					p_ofst=g_pe_proc_dbg_input_ofst_expend_cvd;
					break;
				case PE_PROC_INPUT_CSC_RGB_Y709_LINEAR:
					p_mtrx=g_pe_proc_dbg_input_rgb_y709_linear;
					p_ofst=g_pe_proc_dbg_input_ofst_rgb_y_linear;
					break;
				case PE_PROC_INPUT_CSC_RGB_Y709_LIMIT:
					p_mtrx=g_pe_proc_dbg_input_rgb_y709_limit;
					p_ofst=g_pe_proc_dbg_input_ofst_rgb_y_limit;
					break;
				case PE_PROC_INPUT_CSC_RGB_Y601_LINEAR:
					p_mtrx=g_pe_proc_dbg_input_rgb_y601_linear;
					p_ofst=g_pe_proc_dbg_input_ofst_rgb_y_linear;
					break;
				case PE_PROC_INPUT_CSC_RGB_Y601_LIMIT:
					p_mtrx=g_pe_proc_dbg_input_rgb_y601_limit;
					p_ofst=g_pe_proc_dbg_input_ofst_rgb_y_limit;
					break;
				case PE_PROC_INPUT_CSC_RGB_Y601_SECAM:
					p_mtrx=g_pe_proc_dbg_input_rgb_y601_secam;
					p_ofst=g_pe_proc_dbg_input_ofst_rgb_y_secam;
					break;
				default:
					p_mtrx=g_pe_proc_dbg_input_mtrx_bypass;
					p_ofst=g_pe_proc_dbg_input_ofst_bypass;
					break;
			}
			ctrl_data.data.cs00 = p_mtrx[0];
			ctrl_data.data.cs01 = p_mtrx[1];
			ctrl_data.data.cs02 = p_mtrx[2];
			ctrl_data.data.cs10 = p_mtrx[3];
			ctrl_data.data.cs11 = p_mtrx[4];
			ctrl_data.data.cs12 = p_mtrx[5];
			ctrl_data.data.cs20 = p_mtrx[6];
			ctrl_data.data.cs21 = p_mtrx[7];
			ctrl_data.data.cs22 = p_mtrx[8];
			ctrl_data.data.cs03 = p_ofst[0];
			ctrl_data.data.cs13 = p_ofst[1];
			ctrl_data.data.cs23 = p_ofst[2];
			ctrl_data.data.cs04 = p_ofst[3];
			ctrl_data.data.cs14 = p_ofst[4];
			ctrl_data.data.cs24 = p_ofst[5];
			printk("[pe_proc][%d] bl:%d,inf:%d\n",val[0],\
				ctrl_data.blacklevel,ctrl_data.inputinfo);
			printk("%04x,%04x,%04x, %04x,%04x\n",ctrl_data.data.cs00,ctrl_data.data.cs01,\
				ctrl_data.data.cs02,ctrl_data.data.cs03,ctrl_data.data.cs04);
			printk("%04x,%04x,%04x, %04x,%04x\n",ctrl_data.data.cs10,ctrl_data.data.cs11,\
				ctrl_data.data.cs12,ctrl_data.data.cs13,ctrl_data.data.cs14);
			printk("%04x,%04x,%04x, %04x,%04x\n",ctrl_data.data.cs20,ctrl_data.data.cs21,\
				ctrl_data.data.cs22,ctrl_data.data.cs23,ctrl_data.data.cs24);
			ret = vpq_hwrap_setblacklevel(&param);
			if (ret!=RET_OK){
				printk("[%s,%d]vpq_hwrap_setblacklevel() error\n", __F__, __L__);
				break;
			}
		}break;
		case PE_PROC_DBG_WRAP_FUNC_BLKLVL2:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_vpq_black_level_info ctrl_data;
			param.wid = 0;
			param.version = 0;
			param.length = sizeof(struct v4l2_ext_vpq_black_level_info);
			param.p_data = (unsigned char *)&ctrl_data;
			sscanf(command," %x %x %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" BLKLVL2 : echo 6 [wid] [type]\n");
				printk("   [w0] LOW  ATV     : echo 6 0 0 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] HIGH ATV     : echo 6 0 1 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] LOW  HDMI_TV : echo 6 0 2 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] HIGH HDMI_TV : echo 6 0 3 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] LOW  HDMI_PC : echo 6 0 4 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] HIGH HDMI_PC : echo 6 0 5 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] LOW  MOVIE   : echo 6 0 6 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] HIGH MOVIE   : echo 6 0 7 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] LOW  PHOTO   : echo 6 0 8 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w0] HIGH PHOTO   : echo 6 0 9 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] LOW  ATV     : echo 6 1 0 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] HIGH ATV     : echo 6 1 1 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] LOW  HDMI_TV : echo 6 1 2 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] HIGH HDMI_TV : echo 6 1 3 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] LOW  HDMI_PC : echo 6 1 4 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] HIGH HDMI_PC : echo 6 1 5 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] LOW  MOVIE   : echo 6 1 6 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] HIGH MOVIE   : echo 6 1 7 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] LOW  PHOTO   : echo 6 1 8 > /proc/lg/pe/dbg_wrap_func\n");
				printk("   [w1] HIGH PHOTO   : echo 6 1 9 > /proc/lg/pe/dbg_wrap_func\n");
				printk("\n");
				break;
			}
			param.wid = val[0];
			ctrl_data.color_space = 0;
			if (val[1]==0) {
				ctrl_data.ui_value = 0;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_ATV;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
			}
			else if (val[1]==1) {
				ctrl_data.ui_value = 1;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_ATV;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_AV_RF_EXTENSION;
			}
			else if (val[1]==2) {
				ctrl_data.ui_value = 0;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_HDMI_TV;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
				val[4] = PE_PROC_INPUT_CSC_BYPASS;
			}
			else if (val[1]==3) {
				ctrl_data.ui_value = 1;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_HDMI_TV;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_Y709_LINEAR_LIMIT_HIGH;
			}
			else if (val[1]==4) {
				ctrl_data.ui_value = 0;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_HDMI_PC;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LINEAR_LOW;
			}
			else if (val[1]==5) {
				ctrl_data.ui_value = 1;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_HDMI_PC;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LIMIT_HIGH;
			}
			else if (val[1]==6) {
				ctrl_data.ui_value = 0;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_MEDIA_MOVIE;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
			}
			else if (val[1]==7) {
				ctrl_data.ui_value = 1;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_MEDIA_MOVIE;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
			}
			else if (val[1]==8) {
				ctrl_data.ui_value = 0;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_MEDIA_PHOTO;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
			}
			else if (val[1]==9) {
				ctrl_data.ui_value = 1;
				ctrl_data.curr_input = VPQ_HWRAP_INPUT_MEDIA_PHOTO;
				ctrl_data.black_level_type = V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS;
			}
			else {
				printk(" exit\n");
				break;
			}
			printk("[pe_proc][%d] ui:%d,input:%d,csc:%d,black_level_type:%d\n",val[0],\
				ctrl_data.ui_value,ctrl_data.curr_input,ctrl_data.color_space,ctrl_data.black_level_type);
			ret = vpq_hwrap_setblacklevel2(&param);
			if (ret!=RET_OK){
				printk("[%s,%d]vpq_hwrap_setblacklevel2() error\n", __F__, __L__);
				break;
			}
		}break;
		case PE_PROC_DBG_WRAP_FUNC_MUTEONOFF:
		{
			sscanf(command," %x %x %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]==PE_PROC_DBG_USAGE_NUM){
				printk(" MUTEONOFF : echo %x [wid] [en] > %s\n",PE_PROC_DBG_WRAP_FUNC_MUTEONOFF,PE_PROC_DBG_WRAP_PATH);
				printk("   mute : %d, %d, %d, %d\n",KWRAP_PE_IsMuteOn(0),KWRAP_PE_IsMuteOn(1),KWRAP_PE_IsMuteOn(2),KWRAP_PE_IsMuteOn(3));
				printk("   wid(0~3)\n");
				printk("   en(0:off,1:black,2:blue,3:gray\n");
				printk("   eg. echo %x 0 0 > %s\n",PE_PROC_DBG_WRAP_FUNC_MUTEONOFF,PE_PROC_DBG_WRAP_PATH);
				printk("   eg. echo %x 0 1 > %s\n",PE_PROC_DBG_WRAP_FUNC_MUTEONOFF,PE_PROC_DBG_WRAP_PATH);
				printk("\n");
				break;
			}
			KWRAP_PE_SetMuteInfo(val[0], val[1]);
		}break;
		case PE_PROC_DBG_WRAP_FUNC_LOWDELAY:
		{
			#ifdef INCLUDE_KDRV_DE
			extern int de_kwrap_setlowdelaymode(UINT32 param);
			sscanf(command," %x %x",(int *)&func_num,&val[0]);
			de_kwrap_setlowdelaymode(val[0]);
			#endif
		}break;
		default:
		{
			printk("invalid func numner passed from proc command\n");
		}break;
	}
	return;
}

void pe_proc_dbg_kdrv_help(void)
{
	printk("----------------------------------------\n");
	printk("dbg_kdrv_func (%s)\n", PE_PROC_DBG_KDRV_VER);
	printk("----------------------------------------\n");
	printk("      >> usage : echo [funcnum] %x > %s\n",PE_PROC_DBG_USAGE_NUM,PE_PROC_DBG_KDRV_PATH);
	if(PE_KDRV_VER_M23)
	{
		printk("0x%x. Chip level           : echo %x [mod] [en] > %s\n", PE_PROC_DBG_KDRV_FUNC_MSG,PE_PROC_DBG_KDRV_FUNC_MSG,PE_PROC_DBG_KDRV_PATH);
		printk("      mod : CMG(6) , CMN(7) , CSC(8) , DCM(9) , DNT(10), FWI(11), HST(12), \n");
		printk("          : INF(13), NRD(14), SHP(15), TSK(16), WIN(17), HDR(30)\n");
		printk("      en  : 0, 1\n");
	}
	else
	{
		printk("0x%x. MSG           : echo %x [mod] [en] > %s\n", PE_PROC_DBG_KDRV_FUNC_MSG,PE_PROC_DBG_KDRV_FUNC_MSG,PE_PROC_DBG_KDRV_PATH);
		printk("      mod : ALL_OFF(0), ALL_ON(1), DBG(2), CMN(3), CSC(4), CMG(5), NRD(6), DNT(7), SHP(8), DCM(10), WIN(11), ETC(12), HST(13), HDR(14)\n");
		printk("      en  : 0, 1\n");
	}
	printk("0x%x. LOGM                 : echo %x [lvl] [en] > %s\n", PE_PROC_DBG_KDRV_FUNC_LOGM, PE_PROC_DBG_KDRV_FUNC_LOGM,PE_PROC_DBG_KDRV_PATH);
	printk("      *g_pe_debug_fd* : %d\n", g_pe_debug_fd);
	printk("      lvl : LOGMLEVEL(0~31):ERR(0),NOTI(2),INFOR(3),DEBUG(4),TRACE(5),VPQCMN(6),VPQPE(7),VPQBE(8),\n");
	printk("                           :NRD(11),SHP(12),CMG(13),DCM(14),DCELUT(15),OBCLUT(16),CMN(17),DTM(18),OBC(19),DSE(20)\n");
	printk("0x%x  Task Operation: echo %x 0 0 > %s\n", PE_PROC_DBG_KDRV_FUNC_TASK_OPERATION,PE_PROC_DBG_KDRV_FUNC_TASK_OPERATION,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x  GetPicDisplayInfo    : echo %x [win] > %s\n", PE_PROC_DBG_KDRV_FUNC_GET_PIC_DISP_INFO,PE_PROC_DBG_KDRV_FUNC_GET_PIC_DISP_INFO,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x   >>> get default svn release: %s <<<\n",PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT_ITEM, PE_PROC_DBG_DEFAULT_VER);
	printk("   ----------------------------\n");
	printk("      1.DNT default tables : echo %x 1 > %s\n",PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT_ITEM, PE_PROC_DBG_KDRV_PATH);
	printk("      2.NRD default tables : echo %x 2 > %s\n",PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT_ITEM, PE_PROC_DBG_KDRV_PATH);
	printk("      3.SHP default tables : echo %x 3 > %s\n",PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT_ITEM, PE_PROC_DBG_KDRV_PATH);
	printk("   ----------------------------\n");
	printk("0x%x. DDR          info    : echo %x > %s\n", PE_PROC_DBG_KDRV_FUNC_PRINT_DDR_DB,PE_PROC_DBG_KDRV_FUNC_PRINT_DDR_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. LGSR DDR     info    : echo %x > %s\n", PE_PROC_DBG_KDRV_FUNC_PRINT_LGSR_DDR_DB,PE_PROC_DBG_KDRV_FUNC_PRINT_LGSR_DDR_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. F20 DDR      info    : echo %x > %s\n", PE_PROC_DBG_KDRV_FUNC_PRINT_F20_DDR_DB,PE_PROC_DBG_KDRV_FUNC_PRINT_F20_DDR_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. F20 LGSR DDR info    : echo %x > %s\n", PE_PROC_DBG_KDRV_FUNC_PRINT_F20_LGSR_DDR_DB,PE_PROC_DBG_KDRV_FUNC_PRINT_F20_LGSR_DDR_DB,PE_PROC_DBG_KDRV_PATH);
	printk("   ----------------------------\n");
	printk("0x%x. show&set block func  : echo %x 0 > %s\n", PE_PROC_DBG_KDRV_FUNC_BLOCK_PE_FUNCTION,PE_PROC_DBG_KDRV_FUNC_BLOCK_PE_FUNCTION,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. toggle platform DB  shp (%d) : echo %x 0 > %s\n", \
				PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,vpq_hwrap_getshpdbenalbe(),PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. toggle platform DB  tnr (%d) : echo %x 1 > %s\n", \
				PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,vpq_hwrap_gettnrdbenalbe(),PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. toggle platform DB  dnr (%d) : echo %x 2 > %s\n", \
				PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,vpq_hwrap_getdnrdbenalbe(),PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. toggle platform DB  dct (%d) : echo %x 3 > %s\n", \
				PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,vpq_hwrap_getdctdbenalbe(),PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. set ALL DB  enable           : echo %x 4 > %s\n", \
				PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. set ALL DB  disable          : echo %x 5 > %s\n", \
				PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. toggle cen DB  switch   (%d) : echo %x 6 > %s\n", \
				PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,vpq_hwrap_getcendbswich(),PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. toggle picturectrl  switch   (%d) : echo %x 7 > %s\n", \
				PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,vpq_hwrap_getpicturectrldbswich(),PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. Print shp data       : echo %x > %s\n", PE_PROC_DBG_KDRV_FUNC_PRINT_SHP,PE_PROC_DBG_KDRV_FUNC_PRINT_SHP,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. Print shp ddr data   : echo %x > %s\n", PE_PROC_DBG_KDRV_FUNC_PRINT_SHP_SQM,PE_PROC_DBG_KDRV_FUNC_PRINT_SHP_SQM,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. Print nr ddr data    : echo %x > %s\n", PE_PROC_DBG_KDRV_FUNC_PRINT_NR_SQM,PE_PROC_DBG_KDRV_FUNC_PRINT_NR_SQM,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. LGSR status          : echo %x > %s\n", PE_PROC_DBG_KDRV_FUNC_PRINT_LGSR_STATUS,PE_PROC_DBG_KDRV_FUNC_PRINT_LGSR_STATUS,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. LLLUT                : echo %x [val] > %s\n", PE_PROC_DBG_KDRV_FUNC_LLLUT,PE_PROC_DBG_KDRV_FUNC_LLLUT,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. show&set lgsr func   : echo %x [val] > %s\n", PE_PROC_DBG_KDRV_FUNC_BLOCK_LGSR,PE_PROC_DBG_KDRV_FUNC_BLOCK_LGSR,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. PE_INF_HW_O20_GINFO__KDRV_INFO   : echo %x [win] > %s\n", PE_PROC_DBG_KDRV_FUNC_GET_PIC_GENE_INFO,PE_PROC_DBG_KDRV_FUNC_GET_PIC_GENE_INFO,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. print f20 DB         : echo %x  > %s\n", PE_PROC_DBG_KDRV_FUNC_GET_F20_TBL_SHP,PE_PROC_DBG_KDRV_FUNC_GET_F20_TBL_SHP,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. set declut accel mode: echo %x  > %s\n", PE_PROC_DBG_KDRV_FUNC_SET_DCE_LUT_ACCEL,PE_PROC_DBG_KDRV_FUNC_SET_DCE_LUT_ACCEL,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. set dc DB            : echo %x [setNum] [dny] [apl] [gain] [table] > %s\n", PE_PROC_DBG_KDRV_FUNC_SET_DCE_DB,PE_PROC_DBG_KDRV_FUNC_SET_DCE_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. get dc DB            : echo %x [0:dyn,1:apl,2:gain,3:table] [setNum] > %s\n", PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB,PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. get dc DB addr       : echo %x  > %s\n", PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB_INFO,PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB_INFO,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. compare LGSR DB      : echo %x  > %s\n", PE_PROC_DBG_KDRV_FUNC_CMP_LGSR_DB,PE_PROC_DBG_KDRV_FUNC_CMP_LGSR_DB,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. print cen region     : echo %x  [regionNum] > %s\n", PE_PROC_DBG_KDRV_FUNC_GET_CEN_RERION,PE_PROC_DBG_KDRV_FUNC_GET_CEN_RERION,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. set AI FACE          : echo %x [ui:0~2] > %s\n", PE_PROC_DBG_KDRV_FUNC_SET_AI_FACE,PE_PROC_DBG_KDRV_FUNC_SET_AI_FACE,PE_PROC_DBG_KDRV_PATH);
	printk("0x%x. switch histo         : echo %x 0:nd 1:hdr > %s\n", PE_PROC_DBG_KDRV_FUNC_SWITCH_HISTO,PE_PROC_DBG_KDRV_FUNC_SWITCH_HISTO,PE_PROC_DBG_KDRV_PATH);
	printk("----------------------------------------\n");
	printk("0x%x. print lgsr info      : echo %x  > %s\n", PE_PROC_DBG_KDRV_FUNC_GET_LGSR_INFO,PE_PROC_DBG_KDRV_FUNC_GET_LGSR_INFO,PE_PROC_DBG_KDRV_PATH);
	printk("\n");
	return;
}

void pe_proc_dbg_kdrv_func(char *command)
{
	UINT32 val[6], i;
	PE_PROC_DBG_KDRV_FUNCNUM func_num;
	int ret = RET_OK;
	sscanf(command," %x",(int *)&func_num);
	printk(" ** kdrv dbg func num : 0x%x, command : %s\n",func_num,command);
	switch(func_num)
	{
		case PE_PROC_DBG_KDRV_FUNC_MSG:
		{
			static UINT32 uPrev = 0;
			LX_PE_DBG_SETTINGS_T stDbgParam;
			int (*pFnSetDebug[PE_ITEM_PKTMODL(NUM)])(LX_PE_DBG_SETTINGS_T *) = {
				NULL,
				NULL,
				KWRAP_PE_SetDebugSettings,
				PE_CMN_SetDebugSettings,
				PE_CSC_SetDebugSettings,
				PE_CMG_SetDebugSettings,
				PE_NRD_SetDebugSettings,
				PE_DNT_SetDebugSettings,
				PE_SHP_SetDebugSettings,
				NULL,
				PE_DCM_SetDebugSettings,
				PE_WIN_SetDebugSettings,
				PE_ETC_SetDebugSettings,
				PE_HST_SetDebugSettings,
				PE_HDR_SetDebugSettings
			};
			sscanf(command," %x %d %d", (int *)&func_num, &val[0], &val[1]);
			if(PE_KDRV_VER_M23 || PE_KDRV_VER_O24)
			{
				if (val[0]<=LX_LOGM_LEVEL_MAX)
				{
					if (!val[1])	OS_DEBUG_DisableModuleByIndex(g_pe_dbg_fd, val[0]);
					else			OS_DEBUG_EnableModuleByIndex(g_pe_dbg_fd, val[0], DBG_COLOR_NONE );
				}
			}
			else
			{
				if (val[0] >= PE_ITEM_PKTMODL(NUM))
				{
					printk("[%s,%d] out of range.\n", __F__, __L__);
					break;
				}

				memset(&stDbgParam, 0, sizeof(stDbgParam));
				stDbgParam.type = LX_PE_DBG_LV;
				stDbgParam.print_lvl = uPrev;
				for (i = PE_ITEM_PKTMODL(DBG); i < PE_ITEM_PKTMODL(NUM); i++)
				{
					if (val[0] == 0)
						stDbgParam.print_lvl &= ~(0x1 << i);
					else if (val[0] == 1)
						stDbgParam.print_lvl |= (0x1 << i);
					else if (val[0] == i)
					{
						if (val[1])
							stDbgParam.print_lvl |= (0x1 << val[0]);
						else
							stDbgParam.print_lvl &= ~(0x1 << val[0]);
					}
					if (pFnSetDebug[i] && (pFnSetDebug[i](&stDbgParam) != RET_OK))
					{
						printk("[%s,%d] pFnSetDebug[%d]() error\n", __F__, __L__, i);
						break;
					}
				}
				uPrev = stDbgParam.print_lvl;
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_LOGM:
		{
			sscanf(command," %x %d %d", (int *)&func_num, &val[0], &val[1]);

			if (val[0]<=LX_LOGM_LEVEL_MAX)
			{
				if (!val[1])	OS_DEBUG_DisableModuleByIndex(g_pe_debug_fd, val[0]);
				else			OS_DEBUG_EnableModuleByIndex(g_pe_debug_fd, val[0], DBG_COLOR_NONE );
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_TASK_OPERATION:
		{
			UINT32 tbl_data[3];
			LX_PE_ETC_TBL_T tbl;
			tbl.func_num = 0;
			tbl.oper = 0;
			tbl.size = 3;
			tbl.data = tbl_data;
			sscanf(command," %x %d %d", (int *)&func_num, &val[0], &val[1]);
			PE_ETC_GetMiscTbl(&tbl);
			if (val[0] == 1)
			{
				tbl_data[0] = val[1];
				PE_ETC_SetMiscTbl(&tbl);
			}
			else if (val[0] == 2)
			{
				tbl_data[1] = val[1];
				PE_ETC_SetMiscTbl(&tbl);
			}
			else if (val[0] == 3)
			{
				tbl_data[2] = val[1];
				PE_ETC_SetMiscTbl(&tbl);
			}
			else
			{
				printk("usage :\n");
				printk("pause_task : echo %x 1 [value] > %s\n",PE_PROC_DBG_KDRV_FUNC_TASK_OPERATION,PE_PROC_DBG_KDRV_PATH);
				printk("timeout    : echo %x 2 [value] > %s\n",PE_PROC_DBG_KDRV_FUNC_TASK_OPERATION,PE_PROC_DBG_KDRV_PATH);
				printk("mode       : echo %x 3 [value] > %s\n",PE_PROC_DBG_KDRV_FUNC_TASK_OPERATION,PE_PROC_DBG_KDRV_PATH);
			}
			printk(" -----------------------------------------------------\n");
			printk("     [pause_task] : 0:run,1~6:stop_tsk,hdlr,owr,alg,win,7:tsk\n");
			printk(" 01. [pause_task]                : %d\n", tbl_data[0]);
			printk(" 02. [timeout](msec)             : %d\n", tbl_data[1]);
			printk(" 03. [mode](0~:off,on,time,cnt)  : %d\n", tbl_data[2]);
			printk(" -----------------------------------------------------\n");
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT_ITEM :
		{
			sscanf(command," %x %d", (int *)&func_num, &val[0]);

			if (val[0]==0x1)			val[1] = 6;		// depend on chip rev.
			else if (val[0]==0x2)		val[1] = 7;		// depend on chip rev.
			else if (val[0]==0x3)		val[1] = 8;		// depend on chip rev.
			else						val[0] = 0xff;
			if (val[0]!=0xff)
			{
				val[2] = 0;
				/* display menu */
				printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
				printk("   ----------------------------\n");
				printk("DNT tables: echo %x 1 [item num] > %s\n",PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT, PE_PROC_DBG_KDRV_PATH);
				printk("NRD tables: echo %x 2 [item num] > %s\n",PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT, PE_PROC_DBG_KDRV_PATH);
				printk("SHP tables: echo %x 3 [item num] > %s\n",PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT, PE_PROC_DBG_KDRV_PATH);
				printk("   ----------------------------\n");
				printk("\n");
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_DEFAULT :
		{
			sscanf(command," %x %d %x", (int *)&func_num, &val[0], &val[2]);

			if (val[0]==0x1)			val[1] = 6;		// depend on chip rev.
			else if (val[0]==0x2)		val[1] = 7;		// depend on chip rev.
			else if (val[0]==0x3)		val[1] = 8;		// depend on chip rev.
			else						val[0] = 0xff;
			if (val[0]!=0xff)
			{
				/* display menu */
				printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
				printk("   ----------------------------\n");
				printk("\n");
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_GET_PIC_DISP_INFO:
		{
			sscanf(command," %x %d", (int *)&func_num, &val[0]);
			{
				LX_PE_INF_DISPLAY_T param0, param1,param2, param3;
				param0.win_id = param1.win_id = pe_proc_dbg_getwinid(val[0]);
				ret = vpq_hwrap_getpicdisplayinfo((void *)&param0);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_getpicdisplayinfo() error\n", __F__, __L__);
					break;
				}
				ret = vpq_hwrap_getpicdisplayinfo(&param1);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_getpicdisplayinfo() error\n", __F__, __L__);
					break;
				}				
				ret = vpq_hwrap_getpicdisplayinfo(&param2);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_getpicdisplayinfo() error\n", __F__, __L__);
					break;
				}
				ret = vpq_hwrap_getpicdisplayinfo(&param3);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_getpicdisplayinfo() error\n", __F__, __L__);
					break;
				}
				printk("get[0] cur : \n");
				pe_proc_dbg_showdisplayinfo(&param0);
				printk("get[1] drv : \n");
				pe_proc_dbg_showdisplayinfo(&param1);
				printk("get[2] drv : \n");
				pe_proc_dbg_showdisplayinfo(&param2);
				printk("get[3] drv : \n");
				pe_proc_dbg_showdisplayinfo(&param3);
				return;
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_DDR_DB:
		{
			val[1] = 2;		// _g_pe_inf_xxx_dbg_get_fn, depend on chip rev.
			val[2] = 2;		//PE_INF_HW_XXX_GINFO_DDR_H_PHYS
			printk("   ----------------------------\n");
			printk("   DDR PHYS info.\n");
			printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
			printk("   ----------------------------\n");
			printk("\n");
			
			val[2] = 3;		//PE_INF_HW_XXX_GINFO_DDR_H_SHDW
			printk("   ----------------------------\n");
			printk("   DDR SHDW info.\n");
			printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
			printk("   ----------------------------\n");
			printk("\n");
			
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_F20_DDR_DB:
		{
			val[1] = 2;		// _g_pe_inf_xxx_dbg_get_fn, depend on chip rev.
			val[2] = 7;		//PE_INF_HW_XXX_GINFO_F20_DDR_H_PHYS
			printk("   ----------------------------\n");
			printk("   F20 DDR PHYS info.\n");
			printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
			printk("   ----------------------------\n");
			printk("\n");
			
			val[2] = 8;		//PE_INF_HW_XXX_GINFO_F20_DDR_H_SHDW
			printk("   ----------------------------\n");
			printk("   F20 DDR SHDW info.\n");
			printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
			printk("   ----------------------------\n");
			printk("\n");
			
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_LGSR_DDR_DB:
		{
			val[1] = 2;		// _g_pe_inf_xxx_dbg_get_fn, depend on chip rev.
			val[2] = 4;		//PE_INF_HW_XXX_GINFO_LGSR_DDR_H_PHYS
			printk("   ----------------------------\n");
			printk("   LGSR DDR PHYS info.\n");
			printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
			printk("   ----------------------------\n");
			printk("\n");
			
			val[2] = 5;		//PE_INF_HW_XXX_GINFO_LGSR_DDR_H_SHDW
			printk("   ----------------------------\n");
			printk("   LGSR DDR SHDW info.\n");
			printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
			printk("   ----------------------------\n");
			printk("\n");
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_F20_LGSR_DDR_DB:
		{
			val[1] = 2;		// _g_pe_inf_xxx_dbg_get_fn, depend on chip rev.
			val[2] = 9;		//PE_INF_HW_XXX_GINFO_LGSR_DDR_H_PHYS
			printk("   ----------------------------\n");
			printk("   F20 LGSR DDR PHYS info.\n");
			printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
			printk("   ----------------------------\n");
			printk("\n");
			
			val[2] = 10;		//PE_INF_HW_XXX_GINFO_LGSR_DDR_H_SHDW
			printk("   ----------------------------\n");
			printk("   F20 LGSR DDR SHDW info.\n");
			printk("   ----------------------------\n");
				pe_proc_dbg_printmisctable(val[1], &val[2], (int)sizeof(UINT32), NULL);
			printk("   ----------------------------\n");
			printk("\n");
		} break;
		case PE_PROC_DBG_KDRV_FUNC_BLOCK_PE_FUNCTION:
		{
			sscanf(command," %x %d", (int *)&func_num, &val[0]);
			if(val[0] == 0)
			{
				vpq_proc_show_func_status_pe();
				printk("	select func  : echo %x [num] > %s\n", PE_PROC_DBG_KDRV_FUNC_BLOCK_PE_FUNCTION,PE_PROC_DBG_KDRV_PATH);
			}
			else
			{
			    ret = vpq_proc_set_block_func_pe(val[0]);
				vpq_proc_show_func_status_pe();
				printk("	select func  : echo %x [num] > %s\n", PE_PROC_DBG_KDRV_FUNC_BLOCK_PE_FUNCTION,PE_PROC_DBG_KDRV_PATH);
			}	
		} break;
		case PE_PROC_DBG_KDRV_FUNC_TOGGLE_EASY_DB:
		{
			sscanf(command," %x %d", (int *)&func_num, &val[0]);
			if(val[0] == 0)
			{
				vpq_hwrap_toggleshpdbenalbe();
				printk("set shp platform db enalbe : %d\n", vpq_hwrap_getshpdbenalbe());
			}
			else if(val[0] == 1)
			{
				vpq_hwrap_toggletnrdbenalbe();
				printk("set tnr platform db enalbe : %d\n", vpq_hwrap_gettnrdbenalbe());
			}
			else if(val[0] == 2)
			{
				vpq_hwrap_togglednrdbenalbe();
				printk("set dnr platform db enalbe : %d\n", vpq_hwrap_getdnrdbenalbe());
			}
			else if(val[0] == 3)
			{
				vpq_hwrap_toggledctdbenalbe();
				printk("set dct platform db enalbe : %d\n", vpq_hwrap_getdctdbenalbe());
			}
			else if(val[0] == 4)
			{
				vpq_hwrap_setalldbenalbe(1);
				printk("set shp platform db enalbe : %d\n", vpq_hwrap_getshpdbenalbe());
				printk("set tnr platform db enalbe : %d\n", vpq_hwrap_gettnrdbenalbe());
				printk("set dnr platform db enalbe : %d\n", vpq_hwrap_getdnrdbenalbe());
				printk("set dnr platform db enalbe : %d\n", vpq_hwrap_getdctdbenalbe());
			}
			else if(val[0] == 5)
			{
				vpq_hwrap_setalldbenalbe(0);
				printk("set shp platform db enalbe : %d\n", vpq_hwrap_getshpdbenalbe());
				printk("set tnr platform db enalbe : %d\n", vpq_hwrap_gettnrdbenalbe());
				printk("set dnr platform db enalbe : %d\n", vpq_hwrap_getdnrdbenalbe());
				printk("set dnr platform db enalbe : %d\n", vpq_hwrap_getdctdbenalbe());
			}
			else if(val[0] == 6)
			{
				vpq_hwrap_togglecendbswitch();
				printk("set cen db switch : %d\n", vpq_hwrap_getcendbswich());
			}
			else if(val[0] == 7)
			{
				vpq_hwrap_picturectrldbswitch();
				printk("set picture ctrl switch : %d\n", vpq_hwrap_getpicturectrldbswich());
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_LGSR_STATUS:
		{
			ret = PE_LGSR_PrintStatus();
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_SHP:
		{
			if(PE_KDRV_VER_E60)
			{
				LX_PE_SHP_RE1_CMN_T shp_cmn;
				LX_PE_SHP_RE1_MISC_T shp_misc;
				LX_PE_SHP_EE1_T shp_edg;
				LX_PE_SHP_SR2K_RE2_CMN_T sre_cmn;
				LX_PE_SHP_SR2K_RE1_MISC_T sre_misc;
				LX_PE_SHP_SR2K_EE1_T sre_edg;
				LX_PE_SHP_SR4K_RE1_CMN_T sre_cmn_4k;
				LX_PE_SHP_SR4K_RE1_MISC_T sre_misc_4k;
				LX_PE_SHP_SR4K_EE1_T sre_edg_4k;
				shp_cmn.win_id = shp_misc.win_id = shp_edg.win_id = 0x0;
				sre_cmn.win_id = sre_misc.win_id = sre_edg.win_id = 0x0;
				sre_cmn_4k.win_id = sre_misc_4k.win_id = sre_edg_4k.win_id = 0x0;
				PE_SHP_GetReCmnCtrl(&shp_cmn);
				PE_SHP_GetReMiscCtrl(&shp_misc);
				PE_SHP_GetEdgeEnhanceCtrl(&shp_edg);
				PE_SHP_GetSre2KReCmnCtrl(&sre_cmn);
				PE_SHP_GetSre2KReMiscCtrl(&sre_misc);
				PE_SHP_GetSre2KEdgeEnhanceCtrl(&sre_edg);
				PE_SHP_GetSreReCmnCtrl(&sre_cmn_4k);
				PE_SHP_GetSreReMiscCtrl(&sre_misc_4k);
				PE_SHP_GetSreEdgeEnhanceCtrl(&sre_edg_4k);
			}
			else
			{
				LX_PE_SHP_RE2_CMN_T shp_cmn;
				LX_PE_SHP_RE1_MISC_T shp_misc;
				LX_PE_SHP_EE1_T shp_edg;
				LX_PE_SHP_SR2K_RE1_CMN_T sre_cmn;
				LX_PE_SHP_SR2K_RE1_MISC_T sre_misc;
				LX_PE_SHP_SR2K_EE1_T sre_edg;
				shp_cmn.win_id = shp_misc.win_id = shp_edg.win_id = 0x0;
				sre_cmn.win_id = sre_misc.win_id = sre_edg.win_id = 0x0;
				PE_SHP_GetReCmnCtrl(&shp_cmn);
				PE_SHP_GetReMiscCtrl(&shp_misc);
				PE_SHP_GetEdgeEnhanceCtrl(&shp_edg);
				PE_SHP_GetSre2KReCmnCtrl(&sre_cmn);
				PE_SHP_GetSre2KReMiscCtrl(&sre_misc);
				PE_SHP_GetSre2KEdgeEnhanceCtrl(&sre_edg);
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_SHP_SQM:
		{
			if(PE_KDRV_VER_O26)
			{
				LX_PE_SHP_RE_SQM4_CMN_T shp_sqm_cmn;
				LX_PE_SHP_RE_SQM5_DETAIL_T shp_sqm_dtl;
				LX_PE_SHP_SR2K_SQM4_CMN_T sre_sqm_cmn_2k;
				LX_PE_SHP_SR2K_SQM4_DETAIL_T sre_sqm_dtl_2k;
				PE_SHP_GetSqmCmnCtrl(&shp_sqm_cmn);
				PE_SHP_GetSqmDetailCtrl(&shp_sqm_dtl);
				PE_SHP_GetSre2KSqmCmnCtrl(&sre_sqm_cmn_2k);
				PE_SHP_GetSre2KSqmDetailCtrl(&sre_sqm_dtl_2k);
			}
			else if(PE_KDRV_VER_O24)
			{
				LX_PE_SHP_RE_SQM3_CMN_T shp_sqm_cmn;
				LX_PE_SHP_RE_SQM4_DETAIL_T shp_sqm_dtl;
				LX_PE_SHP_SR2K_SQM3_CMN_T sre_sqm_cmn_2k;
				LX_PE_SHP_SR2K_SQM3_DETAIL_T sre_sqm_dtl_2k;
				PE_SHP_GetSqmCmnCtrl(&shp_sqm_cmn);
				PE_SHP_GetSqmDetailCtrl(&shp_sqm_dtl);
				PE_SHP_GetSre2KSqmCmnCtrl(&sre_sqm_cmn_2k);
				PE_SHP_GetSre2KSqmDetailCtrl(&sre_sqm_dtl_2k);
			}
			else if(PE_KDRV_VER_O22)
			{
				LX_PE_SHP_RE_SQM3_CMN_T shp_sqm_cmn;
				LX_PE_SHP_RE_SQM4_DETAIL_T shp_sqm_dtl;
				LX_PE_SHP_SR2K_SQM2_CMN_T sre_sqm_cmn_2k;
				LX_PE_SHP_SR2K_SQM2_DETAIL_T sre_sqm_dtl_2k;
				PE_SHP_GetSqmCmnCtrl(&shp_sqm_cmn);
				PE_SHP_GetSqmDetailCtrl(&shp_sqm_dtl);
				PE_SHP_GetSre2KSqmCmnCtrl(&sre_sqm_cmn_2k);
				PE_SHP_GetSre2KSqmDetailCtrl(&sre_sqm_dtl_2k);
			}
			else if(PE_KDRV_VER_E60)
			{
				LX_PE_SHP_RE_SQM2_CMN_T shp_sqm_cmn;
				LX_PE_SHP_RE_SQM3_DETAIL_T shp_sqm_dtl;
				LX_PE_SHP_SR2K_SQM2_CMN_T sre_sqm_cmn_2k;
				LX_PE_SHP_SR2K_SQM2_DETAIL_T sre_sqm_dtl_2k;
				LX_PE_SHP_SR4K_SQM1_CMN_T sre_sqm_cmn_4k;
				LX_PE_SHP_SR4K_SQM1_DETAIL_T sre_sqm_dtl_4k;
				PE_SHP_GetSqmCmnCtrl(&shp_sqm_cmn);
				PE_SHP_GetSqmDetailCtrl(&shp_sqm_dtl);
				PE_SHP_GetSre2KSqmCmnCtrl(&sre_sqm_cmn_2k);
				PE_SHP_GetSre2KSqmDetailCtrl(&sre_sqm_dtl_2k);
				PE_SHP_GetSreSqmCmnCtrl(&sre_sqm_cmn_4k);
				PE_SHP_GetSreSqmDetailCtrl(&sre_sqm_dtl_4k);
			}
			else 
			{
				LX_PE_SHP_RE_SQM2_CMN_T shp_sqm_cmn;
				LX_PE_SHP_RE_SQM4_DETAIL_T shp_sqm_dtl;
				LX_PE_SHP_SR2K_SQM2_CMN_T sre_sqm_cmn;
				LX_PE_SHP_SR2K_SQM2_DETAIL_T sre_sqm_dtl;
				PE_SHP_GetSqmCmnCtrl(&shp_sqm_cmn);
				PE_SHP_GetSqmDetailCtrl(&shp_sqm_dtl);
				PE_SHP_GetSre2KSqmCmnCtrl(&sre_sqm_cmn);
				PE_SHP_GetSre2KSqmDetailCtrl(&sre_sqm_dtl);
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_PRINT_NR_SQM:
		{
			if(PE_KDRV_VER_O26)
			{
				LX_PE_NRD_TNR1_CMN_T tnr0_cmn;
				LX_PE_NRD_TNR2ND2_CMN_T tnr1_cmn;
				LX_PE_NRD_TNR2ND2_CMN_T tnr2_cmn;
				LX_PE_NRD_TNR_SQM1_CMN_T tmr0_sqm;
				LX_PE_NRD_TNR2ND_SQM1_CMN_T tmr1_sqm;
				LX_PE_NRD_TNR2ND_SQM1_CMN_T tmr2_sqm;
				LX_PE_NRD_DNR4_CMN_T dnr_usr;
				LX_PE_NRD_DNR_SQM2_CMN_T dnr_sqm;
				LX_PE_NRD_DNR4_CMN_T dnr1_usr;
				LX_PE_NRD_DNR_SQM2_CMN_T dnr1_sqm;
				LX_PE_NRD_DCNT3_CMN_T dcnt_usr;
				LX_PE_NRD_DCNT3_CMN_T dcnt1_usr;
				LX_PE_NRD_DCNT_SQM2_CMN_T dcnt_sqm;
				LX_PE_NRD_DCNT_SQM2_CMN_T dcnt1_sqm;
				LX_PE_CCO_DCNT1_CMN_T led_dcnt_user;
				LX_PE_CCO_DCNT_SQM1_CMN_T led_dcnt_sqm;
				tnr0_cmn.win_id =tnr1_cmn.win_id =tnr2_cmn.win_id = 0x0;
				tmr0_sqm.win_id =tmr1_sqm.win_id=tmr2_sqm.win_id = 0x0;
				dnr_usr.win_id =dnr_sqm.win_id = 0x0;
				dnr1_usr.win_id =dnr1_sqm.win_id = 0x0;
				dcnt_usr.win_id =dcnt_sqm.win_id = 0x0;
				led_dcnt_user.win_id =led_dcnt_sqm.win_id = 0x0;
				PE_NRD_GetTnrCmnCtrl(&tnr0_cmn);
				PE_NRD_GetTnr2ndCmnCtrl(&tnr1_cmn);
				PE_NRD_GetTnr3rdCmnCtrl(&tnr2_cmn);
				PE_NRD_GetTnrSqmCmnCtrl(&tmr0_sqm);
				PE_NRD_GetTnr2ndSqmCmnCtrl(&tmr1_sqm);
				PE_NRD_GetTnr3rdSqmCmnCtrl(&tmr2_sqm);
				PE_NRD_GetDnrCmnCtrl(&dnr_usr);
				PE_NRD_GetDnr2ndCmnCtrl(&dnr1_usr);
				PE_NRD_GetDnrSqmCmnCtrl(&dnr_sqm);
				PE_NRD_GetDnr2ndSqmCmnCtrl(&dnr1_sqm);
				PE_NRD_GetDnrDcntCmnCtrl(&dcnt_usr);
				PE_NRD_GetDnrDcnt2ndCmnCtrl(&dcnt1_usr);
				PE_NRD_GetDnrDcntSqmCmnCtrl(&dcnt_sqm);
				PE_NRD_GetDnrDcnt2ndSqmCmnCtrl(&dcnt1_sqm);
				PE_NRD_GetLedDcntCmnCtrl(&led_dcnt_user);
				PE_NRD_GetLedDcntSqmCmnCtrl(&led_dcnt_sqm);
			}
			else
			{
				LX_PE_NRD_TNR1_CMN_T tnr0_cmn;
				LX_PE_NRD_TNR2ND1_CMN_T tnr1_cmn;
				LX_PE_NRD_TNR_SQM1_CMN_T tmr0_sqm;
				LX_PE_NRD_TNR2ND_SQM1_CMN_T tmr1_sqm;
				LX_PE_NRD_DNR3_CMN_T dnr_usr;
				LX_PE_NRD_DNR_SQM2_CMN_T dnr_sqm;
				LX_PE_NRD_DCNT2_CMN_T dcnt_usr;
				LX_PE_NRD_DCNT_SQM1_CMN_T dcnt_sqm;
				LX_PE_LED_DCNT2_CMN_T led_dcnt_user;
				LX_PE_LED_DCNT_SQM1_CMN_T led_dcnt_sqm;
				tnr0_cmn.win_id =tnr1_cmn.win_id = 0x0;
				tmr0_sqm.win_id =tmr1_sqm.win_id = 0x0;
				dnr_usr.win_id =dnr_sqm.win_id = 0x0;
				dcnt_usr.win_id =dcnt_sqm.win_id = 0x0;
				led_dcnt_user.win_id =led_dcnt_sqm.win_id = 0x0;
				PE_NRD_GetTnrCmnCtrl(&tnr0_cmn);
				PE_NRD_GetTnr2ndCmnCtrl(&tnr1_cmn);
				PE_NRD_GetTnrSqmCmnCtrl(&tmr0_sqm);
				PE_NRD_GetTnr2ndSqmCmnCtrl(&tmr1_sqm);
				PE_NRD_GetDnrCmnCtrl(&dnr_usr);
				PE_NRD_GetDnrSqmCmnCtrl(&dnr_sqm);
				PE_NRD_GetDnrDcntCmnCtrl(&dcnt_usr);
				PE_NRD_GetDnrDcntSqmCmnCtrl(&dcnt_sqm);
				PE_NRD_GetLedDcntCmnCtrl(&led_dcnt_user);
				PE_NRD_GetLedDcntSqmCmnCtrl(&led_dcnt_sqm);
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_LLLUT:
		{
			LX_PE_CSC_LLLUT_CTRL_T *plllut_param;
			plllut_param = OS_Malloc(sizeof(LX_PE_CSC_LLLUT_CTRL_T));
			sscanf(command," %x %d", (int *)&func_num, &val[0]);
			plllut_param->win_id = 0x0;
			plllut_param->lllut_csc_en = plllut_param->lllut_en = 0;
			for( i =0; i<128; i++)
				plllut_param->lllut_r[i]=plllut_param->lllut_g[i] = plllut_param->lllut_b[i] = val[0];
			for(i=0 ; i<9; i++)
				plllut_param->matrix[i] = i+ val[0];
			plllut_param->blend_in_sel = 0;
			plllut_param->r2y_matrix[0]=plllut_param->r2y_matrix[1]=plllut_param->r2y_matrix[2]= val[0];
			for(i=0 ; i<6; i++)
				plllut_param->blend_lut_x[i] = plllut_param->blend_lut_y[i] = i*2 + val[0];

			plllut_param->hue_gain = plllut_param->sat_gain = val[0]*5;
			PE_CSC_SetLllut(plllut_param);
			if(plllut_param) {OS_Free(plllut_param);}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_GET_LLLUT:
		{
			LX_PE_CSC_LLLUT_CTRL_T *plllut_param;
			plllut_param = OS_Malloc(sizeof(LX_PE_CSC_LLLUT_CTRL_T));
			plllut_param->win_id =0x0;
			PE_CSC_GetLllut(plllut_param);
			printk("lllut[] :\n"\
				"lllut_en : %d, lllut_csc_en:%d\n",\
				plllut_param->lllut_en,plllut_param->lllut_csc_en);
			for( i =0; i<128; i++)
				printk("lllut_r,g,b [%d]: %d, %d, %d\n",\
				i, plllut_param->lllut_r[i],plllut_param->lllut_g[i],plllut_param->lllut_b[i]);
			printk(	"matrix[0~8] : %d, %d, %d,	%d, %d, %d,  %d, %d, %d,\n"\
				"blend_in_sel : %d\n",\
				plllut_param->matrix[0],plllut_param->matrix[1],plllut_param->matrix[2],\
				plllut_param->matrix[3],plllut_param->matrix[4],plllut_param->matrix[5],\
				plllut_param->matrix[6],plllut_param->matrix[7],plllut_param->matrix[8],plllut_param->blend_in_sel);
			printk("r2y_matrix[0~2] : %d, %d, %d\n"\
				"blend_lut_x[0~5] : %d, %d, %d, %d, %d, %d\n"\
				"blend_lut_y[0~5] : %d, %d, %d, %d, %d, %d\n"\
				"hue_gain : %d, sat_gain:%d\n",\
				plllut_param->r2y_matrix[0],plllut_param->r2y_matrix[1],plllut_param->r2y_matrix[2],\
				plllut_param->blend_lut_x[0],plllut_param->blend_lut_x[1],plllut_param->blend_lut_x[2],\
				plllut_param->blend_lut_x[3],plllut_param->blend_lut_x[4],plllut_param->blend_lut_x[5],\
				plllut_param->blend_lut_y[0],plllut_param->blend_lut_y[1],plllut_param->blend_lut_y[2],\
				plllut_param->blend_lut_y[3],plllut_param->blend_lut_y[4],plllut_param->blend_lut_y[5],\
				plllut_param->hue_gain,plllut_param->sat_gain);
			if(plllut_param) {OS_Free(plllut_param);}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_BLOCK_LGSR:
		{
			sscanf(command," %x %d", (int *)&func_num, &val[0]);
			if(val[0] == 15)
			{
				lgsr_proc_show_func_status_lgsr();
				printk("	select func  : echo %x [num] > %s\n", PE_PROC_DBG_KDRV_FUNC_BLOCK_PE_FUNCTION,PE_PROC_DBG_KDRV_PATH);
			}
			else
			{
			    ret = lgsr_proc_set_block_func_lgsr(val[0]);
				lgsr_proc_show_func_status_lgsr();
				printk("	select func  : echo %x [num] > %s\n", PE_PROC_DBG_KDRV_FUNC_BLOCK_PE_FUNCTION,PE_PROC_DBG_KDRV_PATH);
			}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_GET_PIC_GENE_INFO:
		{
			val[0] = 2;		// _g_pe_inf_xxx_dbg_get_fn, depend on chip rev.
			val[1] = 1;		//PE_INF_HW_XXX_GINFO_LGSR_DDR_H_PHYS
			/* display menu */
			printk("   ----------------------------\n");
			printk("   >>> get kdrv info <<<\n");
			printk("   ----------------------------\n");
			pe_proc_dbg_printmisctable(val[0],&val[1],(int)sizeof(UINT32),NULL);
			printk("\n");
		} break;
		case PE_PROC_DBG_KDRV_FUNC_GET_F20_TBL_SHP:
		{
			ret = PE_SHP_GetReAllCtrl();//PE_CHPI_SHP_HW_F20_GetCtrl();
			ret = PE_NRD_GetTnrCmnAllCtrl();//PE_CHPI_TNR_HW_F20_GetCtrl();
			ret = PE_NRD_GetDnrCmnAllCtrl();//PE_CHPI_DNR_HW_F20_GetCtrl();
			ret = PE_NRD_GetDnrDcntCmnAllCtrl();//PE_CHPI_DNR_HW_F20_GetDcntCtrl();
		} break;
		case PE_PROC_DBG_KDRV_FUNC_SET_DCE_LUT_ACCEL:
		{
			ret = PE_DCM_SetAccelDceLut();
		} break;
		case PE_PROC_DBG_KDRV_FUNC_SET_DCE_DB:
		{
			#ifdef INCLUDE_E60_CHIP_KDRV
			LX_PE_DCM_LIB_DB_ALL_T stDcmDBAll;
			UINT32 *pp;
			int j;
			sscanf(command," %x %d %d %d %d %d %d", (int *)&func_num, &val[0], &val[1], &val[2], &val[3], &val[4], &val[5]);
			stDcmDBAll.dynContDB.pAddrData = OS_Malloc(sizeof(UINT32)*val[0]*PE_DCM_DDR_E60F20_DCM_DYN_SIZE);
			stDcmDBAll.aplDB.pAddrData      = OS_Malloc(sizeof(UINT32)*val[0]*PE_DCM_DDR_E60F20_DCM_APL_SIZE);
			stDcmDBAll.aiGainDB.pAddrData     = OS_Malloc(sizeof(UINT32)*val[0]*PE_DCM_DDR_E60F20_DCM_GAIN_SIZE);
			stDcmDBAll.stabilzerDB.pAddrData  = OS_Malloc(sizeof(UINT32)*val[0]*PE_DCM_DDR_E60F20_DCM_TABLE_SIZE);

			stDcmDBAll.dynContDB.sizeOfItem   = PE_DCM_DDR_E60F20_DCM_DYN_SIZE;
			stDcmDBAll.aplDB.sizeOfItem        = PE_DCM_DDR_E60F20_DCM_APL_SIZE;
			stDcmDBAll.aiGainDB.sizeOfItem     = PE_DCM_DDR_E60F20_DCM_GAIN_SIZE;
			stDcmDBAll.stabilzerDB.sizeOfItem    = PE_DCM_DDR_E60F20_DCM_TABLE_SIZE;

			stDcmDBAll.dynContDB.lengthOfData =val[0];
			stDcmDBAll.aplDB.lengthOfData       =val[0];
			stDcmDBAll.aiGainDB.lengthOfData   =val[0];
			stDcmDBAll.stabilzerDB.lengthOfData  =val[0];

			stDcmDBAll.dynContDB.sizeOfData   = PE_DCM_DDR_E60F20_DCM_DYN_SIZE*val[0];
			stDcmDBAll.aplDB.sizeOfData 	   	  = PE_DCM_DDR_E60F20_DCM_APL_SIZE*val[0];
			stDcmDBAll.aiGainDB.sizeOfData	  = PE_DCM_DDR_E60F20_DCM_GAIN_SIZE*val[0];
			stDcmDBAll.stabilzerDB.sizeOfData = PE_DCM_DDR_E60F20_DCM_TABLE_SIZE*val[0];

			//memset(stDcmDBAll.dynContDB.pAddrData, val[1], sizeof(UINT32)*val[0]*PE_DCM_DDR_E60F20_DCM_DYN_SIZE);
			//memset(stDcmDBAll.aplDB.pAddrData,      val[2], sizeof(UINT32)*val[0]*PE_DCM_DDR_E60F20_DCM_APL_SIZE);
			//memset(stDcmDBAll.aiGainDB.pAddrData,   val[3], sizeof(UINT32)*val[0]*PE_DCM_DDR_E60F20_DCM_GAIN_SIZE);
			//memset(stDcmDBAll.dynContDB.pAddrData,  val[4], sizeof(UINT32)*val[0]*PE_DCM_DDR_E60F20_DCM_TABLE_SIZE);
			pp = (UINT32 *)stDcmDBAll.dynContDB.pAddrData;
			for(i=0; i<PE_DCM_DDR_E60F20_DCM_DYN_SIZE; i++)
			{
				for(j=0; j< val[0]; j++)
					pp[j*PE_DCM_DDR_E60F20_DCM_DYN_SIZE+i]= val[1];
			}
			pp = (UINT32 *)stDcmDBAll.aplDB.pAddrData;
			for(i=0; i<PE_DCM_DDR_E60F20_DCM_APL_SIZE; i++)
			{
				for(j=0; j< val[0]; j++)
					pp[j*PE_DCM_DDR_E60F20_DCM_APL_SIZE+i]= val[2];
			}
			pp = (UINT32 *)stDcmDBAll.aiGainDB.pAddrData;
			for(i=0; i<PE_DCM_DDR_E60F20_DCM_GAIN_SIZE; i++)
			{
				for(j=0; j< val[0]; j++)
					pp[j*PE_DCM_DDR_E60F20_DCM_GAIN_SIZE+i]= val[3];
			}
			pp = (UINT32 *)stDcmDBAll.stabilzerDB.pAddrData;
			for(i=0; i<PE_DCM_DDR_E60F20_DCM_TABLE_SIZE; i++)
			{
				for(j=0; j< val[0]; j++)
					pp[j*PE_DCM_DDR_E60F20_DCM_TABLE_SIZE+i]= val[4];
			}
			pp = (UINT32 *)stDcmDBAll.contrast_gain;
			for(i=0; i<17; i++)
			{
				pp[i]= val[5]+i;
			}
			ret = PE_DCM_SetDceDB((void *)&stDcmDBAll);
			if(stDcmDBAll.dynContDB.pAddrData) {OS_Free(stDcmDBAll.dynContDB.pAddrData);}
			if(stDcmDBAll.aplDB.pAddrData) {OS_Free(stDcmDBAll.aplDB.pAddrData);}
			if(stDcmDBAll.aiGainDB.pAddrData) {OS_Free(stDcmDBAll.aiGainDB.pAddrData);}
			if(stDcmDBAll.stabilzerDB.pAddrData) {OS_Free(stDcmDBAll.stabilzerDB.pAddrData);}
			#endif
		}
		break;
		case PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB:
		{
			sscanf(command," %x %d %d", (int *)&func_num, &val[0], &val[1]);
			ret = PE_DCM_GetDceDB(val[0], val[1]);
		}
		break;
		case PE_PROC_DBG_KDRV_FUNC_CMP_LGSR_DB:
		{
			//ret = PE_LGSR_HW_O20_CompareDdr(0);
		}
		break;
		case PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB_INFO:
		{
			sscanf(command," %x ", (int *)&func_num);
			ret = PE_DCM_GetDceDBAddr();
		}
		break;
		#if 0
		case PE_PROC_DBG_KDRV_FUNC_GET_DCE_DB_INFO +1:
		{
			LX_MEMCFG_T param;
			ret = PE_LGSR_GetMemInfo((void *)&param);
			printk(" base: %x, sizse:%x\n", param.base, param.size);
		}
		break;
		#endif
		case PE_PROC_DBG_KDRV_FUNC_GET_CEN_RERION:
		{
			LX_PE_CMG_REGION_T *pCenparam;
			int j;
			sscanf(command," %x %d", (int *)&func_num, &val[0]);
			pCenparam = OS_Malloc(sizeof(LX_PE_CMG_REGION_T));
			pCenparam->win_id = 0x0;
			pCenparam->region_num = val[0];
			ret = PE_CMG_GetCenRegion(pCenparam);
			for (j = 0; j < LX_PE_CMG_TBLPOINT; j++)
			{
				printk("tblpint[%d] hue_x/g:%d,%d, sat_x/g:%d,%d, val_x/g:%d,%d\n", \
					j, pCenparam->hue_x[j],pCenparam->hue_g[j],pCenparam->sat_x[j],\
					pCenparam->sat_g[j],pCenparam->val_x[j],pCenparam->val_g[j]);
			}
			if(pCenparam) {OS_Free(pCenparam);}
		} break;
		case PE_PROC_DBG_KDRV_FUNC_SET_AI_FACE:
		{
			sscanf(command," %x %x", (int *)&func_num, &val[0]);
			ret = PE_SHP_SetObcStereoCtrl(&val[0]);
		}
		 break;
		case PE_PROC_DBG_KDRV_FUNC_SWITCH_HISTO:
		{
			#ifdef INCLUDE_O22_CHIP_KDRV
			sscanf(command," %x %x", (int *)&func_num, &val[0]);
			g_hst_hw_o22_switch_hdr_hist = val[0];
			printk("g_hst_hw_o22_switch_hdr_hist : %d\n", g_hst_hw_o22_switch_hdr_hist);
			#endif
		}
		 break;
		case PE_PROC_DBG_KDRV_FUNC_GET_DBC_DB:
		{
			ret = PE_DCM_GetDbcDB();
			if (ret)
			{
				PE_PRINT_ERROR("PE_DCM_GetDbcDB error(%d)\n", ret);
			}
		}break;
		case PE_PROC_DBG_KDRV_FUNC_SWITCH_WID:
		{
			sscanf(command," %x %d", (int *)&func_num, &val[0]);
			vpq_hwrap_switch_win_id(val[0]);
			printk("set shp platform db enalbe : %d\n", val[0]);
		}break;
		case PE_PROC_DBG_KDRV_FUNC_GET_LGSR_INFO:
		{
			sscanf(command," %x ", (int *)&func_num);
			ret = PE_LGSR_PrintStatus();
			
		}break;
		default:
		{
			printk("invalid func numner passed from proc command\n");
		}break;
	}
	return;
}

int pe_proc_dbg_printmisctable(int func_num,int *cmd,int size,struct seq_file *m)
{
	int ret = RET_OK;
	unsigned int next_step=0, fn_call_cnt=0;
	LX_PE_ETC_TBL_T tbl;
	int use_printk = 1;
	tbl.data = NULL;

#define PE_PROC_DBG_PRINT_START		"START_OF_PRINT"
#define PE_PROC_DBG_PRINT_RESERVED	"RESERVED"
#define PE_PROC_DBG_PRINT_END		"END_OF_PRINT"
#define PE_PROC_DBG_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_PROC_DBG_CONTINUE		0
#define PE_PROC_DBG_BREAK			1
#define PE_PROC_DBG_EXIT			2
#define PE_PROC_DBG_FTN_CALL_MAX	256
#define PE_PROC_DBG_STR_MAX_SIZE	128
#define PE_PROC_DBG_TBL_DFL_SIZE	1023

	if (m==NULL)	use_printk = 1;
	else			use_printk = 0;

	if (!cmd)
	{
		if (use_printk == 1)	printk("[%s,%d]cmd null\n", __F__, __L__);
		else					seq_printf(m, "[%s,%d]cmd null\n", __F__, __L__);
		return 0;
	}
	if (size > PE_PROC_DBG_STR_MAX_SIZE)
	{
		if (use_printk == 1)	printk("[%s,%d]size(%d) wrong\n", __F__, __L__, size);
		else					seq_printf(m, "[%s,%d]size(%d) wrong\n", __F__, __L__, size);
		return 0;
	}

	do {
		next_step = PE_PROC_DBG_EXIT;
		tbl.func_num = func_num;
		tbl.oper = 0;
		tbl.size = PE_PROC_DBG_TBL_DFL_SIZE;
		tbl.data = (UINT32 *)OS_Malloc(sizeof(char)*PE_PROC_DBG_STR_MAX_SIZE);
		if (!tbl.data)
		{
			if (use_printk == 1)	printk("[%s,%d]malloc fail\n", __F__, __L__);
			else					seq_printf(m, "[%s,%d]malloc fail\n", __F__, __L__);
			break;
		}
		do {
			memcpy(tbl.data,cmd,size);
			ret = PE_ETC_GetMiscTbl(&tbl);
			if (ret!=RET_OK){
				if (use_printk == 1)
				{
					printk("[%s,%d]PE_ETC_GetMiscTbl() error\n", __F__, __L__);
				}
				else
				{
					seq_printf(m, "[%s,%d]PE_ETC_GetMiscTbl() error\n", __F__, __L__);
				}
				break;
			}
			if (!strcmp((char *)(tbl.data), PE_PROC_DBG_PRINT_START))
			{
				next_step = PE_PROC_DBG_CONTINUE;
			}
			else if (!strcmp((char *)(tbl.data), PE_PROC_DBG_PRINT_RESERVED))
			{
				next_step = PE_PROC_DBG_CONTINUE;
			}
			else if (!strcmp((char *)(tbl.data), PE_PROC_DBG_PRINT_END))
			{
				next_step = PE_PROC_DBG_BREAK;
			}
			else if (!strcmp((char *)(tbl.data), PE_PROC_DBG_PRINT_EXIT))
			{
				next_step = PE_PROC_DBG_EXIT;
			}
			else
			{
				if (use_printk == 1)
				{
					printk("%s", (char *)(tbl.data));
				}
				else
				{
					seq_printf(m, "%s", (char *)(tbl.data));
				}
				next_step = PE_PROC_DBG_CONTINUE;
			}
			fn_call_cnt++;
			tbl.oper++;
		} while ((next_step==PE_PROC_DBG_CONTINUE)&&(fn_call_cnt<PE_PROC_DBG_FTN_CALL_MAX));
		ret = (next_step==PE_PROC_DBG_EXIT)? RET_ERROR:RET_OK;
	} while (0);

	if (tbl.data)
		OS_Free(tbl.data);

	return ret;
}

static int pe_proc_dbg_getwinid (UINT32 wid)
{
	LX_PE_WIN_ID win_id;

	if (wid==0xa)
		win_id = LX_PE_WIN_ALL;
	else if (wid==0x1)
		win_id = LX_PE_WIN_1;
	#ifdef PE_EXTEND_WINID
	else if (wid==0x2)
		win_id = LX_PE_WIN_2;
	else if (wid==0x3)
		win_id = LX_PE_WIN_3;
	#endif
	else
		win_id = LX_PE_WIN_0;

	return (UINT32)win_id;
}

static void pe_proc_dbg_showdisplayinfo(LX_PE_INF_DISPLAY_T *info)
{
	printk("disp[wid:%d]\n"\
		"src:%s, fmt:%s (h:%d, v:%d), fr:%s(%d)\n"\
		"scan:%s, cstd:%s, hdmi:%s\n"\
		"scart:%s, dtv:%s, hdd:%s\n"\
		"in_win:%d,%d,%d,%d, out_win:%d,%d,%d,%d, af:%d, mw:%d, sm:%d,zorder:%d,%d\n"\
		"mode: rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n", \
		info->win_id, \
		PE_DBG_SRC_TYPE_TO_STR(info->src_type), \
		PE_DBG_FMT_TYPE_TO_STR(info->fmt_type), \
		info->in_h_size, info->in_v_size, \
		PE_DBG_FR_TYPE_TO_STR(info->fr_type), info->in_f_rate, \
		PE_DBG_SCAN_TYPE_TO_STR(info->scan_type), \
		PE_DBG_CSTD_TYPE_TO_STR(info->cstd_type), \
		PE_DBG_HDMI_TYPE_TO_STR(info->hdmi_type), \
		PE_DBG_SCART_TYPE_TO_STR(info->scart_type), \
		PE_DBG_DTV_TYPE_TO_STR(info->dtv_type), \
		PE_DBG_HDD_TYPE_TO_STR(info->hdd_type), \
		info->in_win.x_ofst, info->in_win.y_ofst, \
		info->in_win.h_size, info->in_win.v_size, \
		info->out_win.x_ofst, info->out_win.y_ofst, \
		info->out_win.h_size, info->out_win.v_size, \
		info->act_fmt,info->mul_win, info->sub_mode, \
		info->zoder[0],info->zoder[1], \
		info->mode.is_reverse, info->mode.is_oled,\
		info->mode.is_colmetry, info->mode.is_vr, info->mode.is_420, info->mode.is_orbit, info->mode.is_dsc);
	return;
}

int pe_proc_show_status(struct seq_file *m)
{
	int cmd,size;
	if (!m)	return 0;

	seq_printf(m, "V4L2_CID_EXT_LED_BASE   : 0x%08x\n",V4L2_CID_EXT_LED_BASE);
	seq_printf(m, "V4L2_CID_EXT_MEMC_BASE  : 0x%08x\n",V4L2_CID_EXT_MEMC_BASE);
	seq_printf(m, "V4L2_CID_EXT_HDR_BASE   : 0x%08x\n",V4L2_CID_EXT_HDR_BASE);
	seq_printf(m, "V4L2_CID_EXT_DOLBY_BASE : 0x%08x\n",V4L2_CID_EXT_DOLBY_BASE);
	seq_printf(m, "V4L2_CID_EXT_VPQ_BASE   : 0x%08x\n",V4L2_CID_EXT_VPQ_BASE);

	size = (int)(sizeof(int));

	seq_printf(m, "---- pe trace0 ----\n");
	cmd = 0;
	pe_proc_dbg_printmisctable(9,&cmd,size,m);

	seq_printf(m, "---- pe trace1 ----\n");
	cmd = 1;
	pe_proc_dbg_printmisctable(9,&cmd,size,m);

	seq_printf(m, "---- pe trace2 ----\n");
	cmd = 2;
	pe_proc_dbg_printmisctable(9,&cmd,size,m);

	seq_printf(m, "---- pe trace3 ----\n");
	cmd = 3;
	pe_proc_dbg_printmisctable(9,&cmd,size,m);

	seq_printf(m, "---- pe info ----\n");
	cmd = 1;
	pe_proc_dbg_printmisctable(2,&cmd,size,m);

	return 0;
}
