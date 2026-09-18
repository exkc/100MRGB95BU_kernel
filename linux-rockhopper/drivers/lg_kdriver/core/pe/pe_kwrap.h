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


/** @file pe_kwrap.h
 *
 *  application interface header for picture enhance
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_KWRAP_H_
#define	_PE_KWRAP_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/delay.h>	/** for mdelay	*/

#include "pe_kapi.h"

#ifdef __KERNEL__
#define malloc(s)		kmalloc(s, GFP_KERNEL)
#define realloc(p,s)	krealloc(p, s, GFP_KERNEL)
#define free(p)			kfree(p)
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
#define PE_KWRAP_VER_M17			0
#define PE_KWRAP_VER_O18			0
#define PE_KWRAP_VER_M19			1

/* dcm lut */
#define PE_KWRAP_DCM_LUT_STEP		16
#define PE_KWRAP_HDR_TLUT_STEP		32
#define PE_KWRAP_DCM_LUT_MAX		33
#define PE_KWRAP_HDR_TLUT_MAX		99
#define PE_KWRAP_HDR_YLUT_MAX		33
#define PE_KWRAP_DCE_LUT_VAL_MIN	64
#define PE_KWRAP_DCE_LUT_VAL_MAX	1023

/* if defined, use valid window id check */
#define PE_KWRAP_CHK_VALID_WIN_ID

/* if defined, use simple compare, not memcmp for valid window id check */
#define PE_KWRAP_SIMPLE_CHK_VALID_WIN_ID

/* shp data step */
#define PE_KWRAP_SHP_STEP	5

/* ccm table max,size */
#define PE_KWRAP_CCM_TBL_MAX			1023
#define PE_KWRAP_CCM_TBL_SIZE		(PE_KWRAP_CCM_TBL_MAX+1)
#define PE_KWRAP_GAMMA_LUT_SIZE		1024

/* default count */
#ifdef PE_EXTEND_WINID
/* [31:25]cnt_win3,[24:18]cnt_win2,[17:11]cnt_win1,[10:4]cnt_win0 */
/* [3]chk_win3,[2]chk_win2,[1]chk_win1,[0]chk_win0 */
#define PE_KWRAP_UPDATE_CNT_BIT		7
#define PE_KWRAP_UPDATE_CHK_BIT		4
#define PE_KWRAP_DEFAULT_CNT_MAX		120
#else
/* [31:24]NA,[23:16]cnt_win1,[15:8]cnt_win0 */
/* [7:2]NA,[1]chk_win1,[0]chk_win0 */
#define PE_KWRAP_UPDATE_CNT_BIT		8
#define PE_KWRAP_UPDATE_CHK_BIT		8
#define PE_KWRAP_DEFAULT_CNT_MAX		200
#endif

/* cen */
#define PE_KWRAP_CEN_RGN_NUM			16

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/** 511/360=1.41944, 360/511=0.70450
* 0~360~540degree <-> 0x0~0x1ff(511)~0x2ff(767)
* if degree to 10bit & x=361~540
* : (x*255)/179 - 2.2573 + 0.5 = x*1.42458 - 1.7573
* if 10bit to degree & x=512~766
* : (x+2.273)*179/255 + 0.5 = x*0.70196 + 2.09556 */
#if 1
#define PE_KWRAP_CONV_DEGREE_TO_10BIT(x)	\
	(((x)<=360)? ((UINT16)(((x))+1)):(((x)<541)? \
	((UINT16)(((x))-1)):(767)))
#define PE_KWRAP_CONV_10BIT_TO_DEGREE(x)	\
	(((x)<=511)? ((UINT16)(((x))+1)):(((x)<767)? \
	((UINT16)(((x))+2)):(540)))

/* 127/100=1.27, 100/127=0.7874, 0~100 <-> 0x0~0xff(127) */
#define PE_KWRAP_CONV_PERCENT_TO_8BIT(x)	\
	(((x)>=100)? (127):((UINT8)((x)+1)))
#define PE_KWRAP_CONV_8BIT_TO_PERCENT(x)	\
	(((x)>=127)? (100):((UINT8)((x)+1)))
#else
#define PE_KWRAP_CONV_DEGREE_TO_10BIT(x)	\
	(((x)<=360)? ((UINT16)(((float)(x)*1.41944)+0.5)):(((x)<541)? \
	((UINT16)(((float)(x)*1.42458)-1.7573)):(767)))
#define PE_KWRAP_CONV_10BIT_TO_DEGREE(x)	\
	(((x)<=511)? ((UINT16)(((float)(x)*0.7045)+0.5)):(((x)<767)? \
	((UINT16)(((float)(x)*0.70196)+2.09556)):(540)))

/* 127/100=1.27, 100/127=0.7874, 0~100 <-> 0x0~0xff(127) */
#define PE_KWRAP_CONV_PERCENT_TO_8BIT(x)	\
	(((x)>=100)? (127):((UINT8)((float)(x)*1.27+0.5)))
#define PE_KWRAP_CONV_8BIT_TO_PERCENT(x)	\
	(((x)>=127)? (100):((UINT8)((float)(x)*0.7874+0.5)))
#endif

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/

/**
 *	pe kadp info
 */
typedef struct
{
	UINT32 initialized;									///< pe initialized
	UINT32 dflt_cnt[LX_PE_WIN_NUM];						///< pe default setting count
	LX_PE_INF_DISPLAY_T	disp_info[LX_PE_WIN_NUM];		///< pe display info
	LX_PE_HST_HISTO_CFG_T hist_info[LX_PE_WIN_NUM];		///< pe histogram info
	LX_PE_DCM_DCE_CONF_T dce_cfg[LX_PE_WIN_NUM];		///< pe dynamic contrast config
	LX_PE_DCM_DRC_MODE_T drc_mode[LX_PE_WIN_NUM];		///< pe drc mode
	LX_PE_HDR_MODE_INFO_T hdr_info[LX_PE_WIN_NUM];		///< pe hdr info
	unsigned int mute_inf[LX_PE_WIN_NUM];
}
PE_KWRAP_INFO_T;

/**
 *	pe kadp picture control
 */
typedef struct
{
	UINT32 wid;			///< widow id, 0:win0,1:win1,2:all
	UINT32 data;		///< normal control data
	void *st_data;		///< struct data
}
PE_KWRAP_CTRL_T;

/**
 *	pe kwrap input csc type enumeration
 */
typedef enum
{
	PE_KWRAP_INPUT_CSC_BYPASS = 0,		///< ycbcr to ycbcr
	PE_KWRAP_INPUT_CSC_LIMIT,			///< ycbcr(0~255) to ycbcr(16~235)
	PE_KWRAP_INPUT_CSC_EXPEND,			///< ycbcr(32~235) to ycbcr(16~235)
	PE_KWRAP_INPUT_CSC_EXPEND_CVD,		///< ycbcr(32~235) to ycbcr(16~235)
	PE_KWRAP_INPUT_CSC_RGB_Y709_LINEAR,	///< rgb(16~235) to y709(16~235)
	PE_KWRAP_INPUT_CSC_RGB_Y709_LIMIT,	///< rgb(0~255) to y709(16~235)
	PE_KWRAP_INPUT_CSC_RGB_Y601_LINEAR,	///< rgb(16~235) to y601(16~235)
	PE_KWRAP_INPUT_CSC_RGB_Y601_LIMIT,	///< rgb(0~255) to y601(16~235)
	PE_KWRAP_INPUT_CSC_RGB_Y601_SECAM,	///< rgb(16~235) to y601(16~235), for secam
	PE_KWRAP_INPUT_CSC_NUM				///< max num
}
PE_KWRAP_INPUT_CSC_TYPE;

/**
 *	pe kwrap nrd type enumeration
 */
typedef enum
{
	PE_KWRAP_NRD_OFF = 0,	///< off
	PE_KWRAP_NRD_LOW,		///< low
	PE_KWRAP_NRD_MED,		///< medium
	PE_KWRAP_NRD_HGH,		///< high
	PE_KWRAP_NRD_ATO,		///< auto
	PE_KWRAP_NRD_NUM			///< max num
}
PE_KWRAP_NRD_TYPE;

/**
 *	pe kwrap nrd format type enumeration
 */
typedef enum
{
	PE_KWRAP_NRD_FMT_SD = 0,		///< sd
	PE_KWRAP_NRD_FMT_HD,			///< hd
	PE_KWRAP_NRD_FMT_NUM			///< max num
}
PE_KWRAP_NRD_FMT_TYPE;

/**
 *	pe kwrap ccm table type enumeration
 */
typedef enum
{
	PE_KWRAP_CCM_TBL_BPS_10BIT = 0,		///< bypass_10bit
	PE_KWRAP_CCM_TBL_195_10BIT,			///< 1_95_10bit
	PE_KWRAP_CCM_TBL_235_10BIT,			///< 2_35_10bit
	PE_KWRAP_CCM_TBL_RED_10BIT,			///< R_only_10bit
	PE_KWRAP_CCM_TBL_GRN_10BIT,			///< G_only_10bit
	PE_KWRAP_CCM_TBL_BLU_10BIT,			///< B_only_10bit
	PE_KWRAP_CCM_TBL_BPS_08BIT,			///< bypass_8bit
	PE_KWRAP_CCM_TBL_195_08BIT,			///< 1_95_8bit
	PE_KWRAP_CCM_TBL_235_08BIT,			///< 2_35_8bit
	PE_KWRAP_CCM_TBL_RED_08BIT,			///< R_only_8bit
	PE_KWRAP_CCM_TBL_GRN_08BIT,			///< G_only_8bit
	PE_KWRAP_CCM_TBL_BLU_08BIT,			///< B_only_8bit
	PE_KWRAP_CCM_TBL_NUM					///< max num
}
PE_KWRAP_CCM_TBL_TYPE;

/**
 *	pe kwrap cmg region color number type enumeration
 */
typedef enum
{
	PE_KWRAP_CMG_RGN_V00 = 0,	///< type 0
	PE_KWRAP_CMG_RGN_V01,		///< type 1
	PE_KWRAP_CMG_RGN_NUM			///< max num
}
PE_KWRAP_CMG_RGN_TYPE;

/**
 *	pe kwrap cmg region color number type enumeration
 */
typedef enum
{
	PE_KWRAP_CMG_RGN_COL_WHT = 0,	///< white
	PE_KWRAP_CMG_RGN_COL_WTB,		///< white blue
	PE_KWRAP_CMG_RGN_COL_BLK,		///< black
	PE_KWRAP_CMG_RGN_COL_SKN,		///< skin
	PE_KWRAP_CMG_RGN_COL_GRN,		///< green
	PE_KWRAP_CMG_RGN_COL_BLU,		///< blue
	PE_KWRAP_CMG_RGN_COL_RED,		///< red
	PE_KWRAP_CMG_RGN_COL_YEL,		///< yellow
	PE_KWRAP_CMG_RGN_COL_MGT,		///< magenta
	PE_KWRAP_CMG_RGN_COL_CYN,		///< cyan
	PE_KWRAP_CMG_RGN_COL_R10,		///< reserved region 10th
	PE_KWRAP_CMG_RGN_COL_R11,		///< reserved region 11th
	PE_KWRAP_CMG_RGN_COL_R12,		///< reserved region 12th
	PE_KWRAP_CMG_RGN_COL_R13,		///< reserved region 13th
	PE_KWRAP_CMG_RGN_COL_R14,		///< reserved region 14th
	PE_KWRAP_CMG_RGN_COL_R15,		///< reserved region 15th
	PE_KWRAP_CMG_RGN_COL_NUM			///< max num
}
PE_KWRAP_CMG_RGN_COL_TYPE;

/**
 *	pe kwrap cmg control type enumeration
 */
typedef enum
{
	PE_KWRAP_CMG_CTRL_OFF = 0,	///< off
	PE_KWRAP_CMG_CTRL_LOW,		///< low
	PE_KWRAP_CMG_CTRL_HGH,		///< high
	PE_KWRAP_CMG_CTRL_NUM		///< max num
}
PE_KWRAP_CMG_CTRL_TYPE;

/**
 *	pe kwrap dcm dce lut type enumeration
 */
typedef enum
{
	PE_KWRAP_DCM_DCE_LUT_BYPASS = 0,	///< bypass
	PE_KWRAP_DCM_DCE_LUT_SCURVE,		///< s_curve
	PE_KWRAP_DCM_DCE_LUT_LOWPAR,		///< low_parabola
	PE_KWRAP_DCM_DCE_LUT_HGHPAR,		///< high_parabola
	PE_KWRAP_DCM_DCE_LUT_NUM			///< max num
}
PE_KWRAP_DCM_DCE_LUT_TYPE;

/**
 *	pe kwrap dcm dse lut type enumeration
 */
typedef enum
{
	PE_KWRAP_DCM_DSE_LUT_BYPASS = 0,	///< bypass, color 1.0
	PE_KWRAP_DCM_DSE_LUT_COL_00,		///< curve for color 0.0
	PE_KWRAP_DCM_DSE_LUT_COL_04,		///< curve for color 0.4
	PE_KWRAP_DCM_DSE_LUT_COL_06,		///< curve for color 0.6
	PE_KWRAP_DCM_DSE_LUT_COL_12,		///< curve for color 1.2
	PE_KWRAP_DCM_DSE_LUT_COL_14,		///< curve for color 1.4
	PE_KWRAP_DCM_DSE_LUT_COL_20,		///< curve for color 2.0
	PE_KWRAP_DCM_DSE_LUT_NUM			///< max num
}
PE_KWRAP_DCM_DSE_LUT_TYPE;

/**
 *	pe kwrap shp type enumeration
 */
typedef enum
{
	PE_KWRAP_SHP_OFF = 0,	///< off
	PE_KWRAP_SHP_LOW,		///< low
	PE_KWRAP_SHP_MED,		///< medium
	PE_KWRAP_SHP_HGH,		///< high
	PE_KWRAP_SHP_NUM			///< max num
}
PE_KWRAP_SHP_TYPE;

/**
 *	pe kwrap shp format type enumeration
 */
typedef enum
{
	PE_KWRAP_SHP_FMT_SD = 0,		///< sd
	PE_KWRAP_SHP_FMT_HD,			///< hd
	PE_KWRAP_SHP_FMT_NUM			///< max num
}
PE_KWRAP_SHP_FMT_TYPE;

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/
extern UINT32 _g_kwrap_trace;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/* pe_kwrap */
int KWRAP_PE_Init(void);
int KWRAP_PE_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int KWRAP_PE_SetPicDisplayInfo(void *param);
int KWRAP_PE_GetCurPicDisplayInfo(void *param);
int KWRAP_PE_GetPicDisplayInfo(void *param);
void KWRAP_PE_SetMuteInfo(unsigned int wid, unsigned int mute);
unsigned int KWRAP_PE_IsMuteOn(unsigned int wid);
//int KWRAP_PE_SetDefaultSettings(void *param);
//int KWRAP_PE_GetDefaultSettings(void *param);
int KWRAP_PE_SetContrast(void *param);
int KWRAP_PE_GetContrast(void *param);
int KWRAP_PE_SetBrightness(void *param);
int KWRAP_PE_GetBrightness(void *param);
int KWRAP_PE_SetSaturation(void *param);
int KWRAP_PE_GetSaturation(void *param);
int KWRAP_PE_SetHue(void *param);
int KWRAP_PE_GetHue(void *param);
int KWRAP_PE_SetLevelCtrl(void *param);
int KWRAP_PE_GetLevelCtrl(void *param);
int KWRAP_PE_SetVcpLevelCtrl(void *param);
int KWRAP_PE_GetVcpLevelCtrl(void *param);
int KWRAP_PE_SetBypassBlocks(void *param);
int KWRAP_PE_SetWhiteBalance(void *param);
int KWRAP_PE_GetWhiteBalance(void *param);
int KWRAP_PE_SetDceConfig(void *param);
int KWRAP_PE_GetCurDceConfig(void *param);
int KWRAP_PE_GetDceConfig(void *param);
int KWRAP_PE_SetDceLutCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDceLutParam(void *param);
int KWRAP_PE_GetDceLutParam(void *param);
int KWRAP_PE_SetDseLutCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDseLutParam(void *param);
int KWRAP_PE_GetDseLutParam(void *param);
int KWRAP_PE_SetHdrLutCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetHdrLutParam(void *param);
int KWRAP_PE_GetHdrLutParam(void *param);
int KWRAP_PE_SetHdrMode(void *param);
int KWRAP_PE_GetHdrMode(void *param);
int KWRAP_PE_SetDceBlending(void *param);
int KWRAP_PE_GetDceBlending(void *param);
int KWRAP_PE_SetDceDrcMode(void *param);
int KWRAP_PE_GetCurDceDrcMode(void *param);
int KWRAP_PE_GetDceDrcMode(void *param);
int KWRAP_PE_SetDseCtrl(void *param);
int KWRAP_PE_GetDseCtrl(void *param);
int KWRAP_PE_SetDrcCtrl(void *param);
int KWRAP_PE_GetDrcCtrl(void *param);
int KWRAP_PE_SetDrcCurv(void *param);
int KWRAP_PE_SetObcCtrl(void *param);
int KWRAP_PE_GetObcCtrl(void *param);
int KWRAP_PE_GetObcData(void *param);
int KWRAP_PE_SetDtmLutParam(void *param);
int KWRAP_PE_GetDtmLutParam(void *param);
int KWRAP_PE_GetHistogramInfo(void *param);
int KWRAP_PE_SetHistoConfig(void *param);
int KWRAP_PE_GetHistoConfig(void *param);
int KWRAP_PE_GetCurHistoConfig(void *param);
int KWRAP_PE_SetXvYccScale(void *param);
int KWRAP_PE_GetXvYccScale(void *param);
int KWRAP_PE_GetAplInfo(void *param);
int KWRAP_PE_GetHdrInfo(void *param);
int KWRAP_PE_GetBlkApl(void *param);
int KWRAP_PE_GetGamutCscDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetGamutCscCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetGamutCscParam(void *param);
int KWRAP_PE_GetGamutCscParam(void *param);
int KWRAP_PE_GetPostCscDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetPostCscCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetPostCscParam(void *param);
int KWRAP_PE_GetPostCscParam(void *param);
int KWRAP_PE_GetInputCscDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetInputCscCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetInputCscParam(void *param);
int KWRAP_PE_GetInputCscParam(void *param);
int KWRAP_PE_SetCenEnable(void *param);
int KWRAP_PE_GetCenEnable(void *param);
int KWRAP_PE_SetCenRgnEnable(void *param);
int KWRAP_PE_GetCenRgnEnable(void *param);
int KWRAP_PE_GetCenRgnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetCenRgnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetCenRgnParam(void *param);
int KWRAP_PE_GetCenRgnParam(void *param);
int KWRAP_PE_GetCenRgnGainDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetCenRgnGainCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetCenRgnGainParam(void *param);
int KWRAP_PE_GetCenRgnGainParam(void *param);
int KWRAP_PE_SetCenGblGainParam(void *param);
int KWRAP_PE_GetCenGblGainParam(void *param);
int KWRAP_PE_SetCenColorParam(void *param);
int KWRAP_PE_GetCenColorParam(void *param);
int KWRAP_PE_SetClearWhiteParam(void *param);
int KWRAP_PE_GetClearWhiteParam(void *param);
int KWRAP_PE_SetClearWhiteGainParam(void *param);
int KWRAP_PE_GetClearWhiteGainParam(void *param);
int KWRAP_PE_SetSaturationGainLUT(void *param);
int KWRAP_PE_GetSaturationGainLUT(void *param);
int KWRAP_PE_SetExtInnerPattern(void *param);
int KWRAP_PE_SetClearWhiteTableParam(void *param);
int KWRAP_PE_SetVspccParam(void *param);
int KWRAP_PE_SetDseParam(void *param);
int KWRAP_PE_GetDseParam(void *param);
int KWRAP_PE_GetDnrCmnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrDcntCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrCmnParam(void *param);
int KWRAP_PE_GetDnrCmnParam(void *param);
int KWRAP_PE_SetLedDcntCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetLedDnrCmnParam(void *param);
int KWRAP_PE_GetLedDnrCmnParam(void *param);
int KWRAP_PE_SetLedDcntCmnParam(void *param);
int KWRAP_PE_GetLedDcntCmnParam(void *param);
int KWRAP_PE_GetDnrDetailDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrDetailCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrDetailParam(void *param);
int KWRAP_PE_GetDnrDetailParam(void *param);
int KWRAP_PE_SetDnrDcntDetailParam(void *param);
int KWRAP_PE_GetDnrDcntDetailParam(void *param);
int KWRAP_PE_SetLedDnrDetailParam(void *param);
int KWRAP_PE_GetLedDnrDetailParam(void *param);
int KWRAP_PE_SetLedDcntDetailParam(void *param);
int KWRAP_PE_GetLedDcntDetailParam(void *param);
int KWRAP_PE_GetTnrCmnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnrCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnrCmnParam(void *param);
int KWRAP_PE_GetTnrCmnParam(void *param);
int KWRAP_PE_GetTnrDetailDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnrDetailCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnrDetailParam(void *param);
int KWRAP_PE_GetTnrDetailParam(void *param);
int KWRAP_PE_GetTnr2ndCmnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnr2ndCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnr2ndCmnParam(void *param);
int KWRAP_PE_GetTnr2ndCmnParam(void *param);
int KWRAP_PE_GetTnr2ndDetailDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnr2ndDetailCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnr2ndDetailParam(void *param);
int KWRAP_PE_GetTnr2ndDetailParam(void *param);
int KWRAP_PE_SetDnrSqmCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrSqmCmnParam(void *param);
int KWRAP_PE_SetTnrSqmCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetTnrSqmCmnParam(void *param);
int KWRAP_PE_SetTnr2ndSqmCmnParam(void *param);
int KWRAP_PE_SetDnrDcntSqmCmnParam(void *param);
int KWRAP_PE_SetLedDcntSqmCmnParam(void *param);
int KWRAP_PE_SetFilmMode(void *param);
int KWRAP_PE_GetFilmMode(void *param);
int KWRAP_PE_SetLowDelayMode(void *param);
int KWRAP_PE_GetLowDelayMode(void *param);
int KWRAP_PE_GetRenCmnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenCmnParam(void *param);
int KWRAP_PE_GetRenCmnParam(void *param);
int KWRAP_PE_GetRenHorDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenHorCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenHorParam(void *param);
int KWRAP_PE_GetRenHorParam(void *param);
int KWRAP_PE_GetRenVerDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenVerCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenVerParam(void *param);
int KWRAP_PE_GetRenVerParam(void *param);
int KWRAP_PE_GetRenMiscDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenMiscCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenMiscParam(void *param);
int KWRAP_PE_GetRenMiscParam(void *param);
int KWRAP_PE_GetEdgeEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetEdgeEnhanceCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetEdgeEnhanceParam(void *param);
int KWRAP_PE_GetEdgeEnhanceParam(void *param);
int KWRAP_PE_GetDetailEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDetailEnhanceCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDetailEnhanceParam(void *param);
int KWRAP_PE_GetDetailEnhanceParam(void *param);
int KWRAP_PE_GetSreRenCmnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreRenCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreRenCmnParam(void *param);
int KWRAP_PE_GetSreRenCmnParam(void *param);
int KWRAP_PE_GetSreRenHorDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreRenHorCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreRenHorParam(void *param);
int KWRAP_PE_GetSreRenHorParam(void *param);
int KWRAP_PE_GetSreRenVerDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreRenVerCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreRenVerParam(void *param);
int KWRAP_PE_GetSreRenVerParam(void *param);
int KWRAP_PE_GetSreRenMiscDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreRenMiscCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreRenMiscParam(void *param);
int KWRAP_PE_GetSreRenMiscParam(void *param);
int KWRAP_PE_GetSreEdgeEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreEdgeEnhanceCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreEdgeEnhanceParam(void *param);
int KWRAP_PE_GetSreEdgeEnhanceParam(void *param);
int KWRAP_PE_GetSreDetailEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreDetailEnhanceCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSreDetailEnhanceParam(void *param);
int KWRAP_PE_GetSreDetailEnhanceParam(void *param);
int KWRAP_PE_SetRenSqmCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenSqmCmnParam(void *param);
int KWRAP_PE_SetRenSqmDetailParam(void *param);
int KWRAP_PE_GetSre2KRenCmnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KRenCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KRenCmnParam(void *param);
int KWRAP_PE_GetSre2KRenCmnParam(void *param);
int KWRAP_PE_GetSre2KRenHorDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KRenHorCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KRenHorParam(void *param);
int KWRAP_PE_GetSre2KRenHorParam(void *param);
int KWRAP_PE_GetSre2KRenVerDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KRenVerCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KRenVerParam(void *param);
int KWRAP_PE_GetSre2KRenVerParam(void *param);
int KWRAP_PE_GetSre2KRenMiscDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KRenMiscCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KRenMiscParam(void *param);
int KWRAP_PE_GetSre2KRenMiscParam(void *param);
int KWRAP_PE_GetSre2KEdgeEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KEdgeEnhanceCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KEdgeEnhanceParam(void *param);
int KWRAP_PE_GetSre2KEdgeEnhanceParam(void *param);
int KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KDetailEnhanceCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KDetailEnhanceParam(void *param);
int KWRAP_PE_GetSre2KDetailEnhanceParam(void *param);
int KWRAP_PE_SetSre2KSqmCmnCtrl(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KSqmCmnParam(void *param);
int KWRAP_PE_SetSre2KRenSqmDetailParam(void *param);
int KWRAP_PE_SetPspParam(void *param);
int KWRAP_PE_GetPspParam(void *param);
int KWRAP_PE_SetObcParam(void *param);
int KWRAP_PE_GetObcParam(void *param);
int KWRAP_PE_SetObcLUT(void *param);
int KWRAP_PE_GetObcLUT(void *param);
int KWRAP_PE_SetMiscTable(void *param);
int KWRAP_PE_GetMiscTable(void *param);
int KWRAP_PE_SetPicDisplayInfo(void *param);
int KWRAP_PE_GetCurPicDisplayInfo(void *param);
int KWRAP_PE_GetPicDisplayInfo(void *param);
int KWRAP_PE_GetLevelInfo(void *param);
int KWRAP_PE_CheckDnrCmnParam(void *param);
int KWRAP_PE_SetDnrCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckDnrDetailParam(void *param);
int KWRAP_PE_SetDnrDetailBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckDnrDcntCmnParam(void *param);
int KWRAP_PE_GetDnrDcntCmnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrDcntCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckLedDcntCmnParam(void *param);
int KWRAP_PE_GetLedDcntCmnDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetLedDcntCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_GetLedDcntDetailDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetLedDcntDetailBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckLedDcntDetailParam(void *param);
int KWRAP_PE_CheckTnrCmnParam(void *param);
int KWRAP_PE_SetTnrCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckTnrDetailParam(void *param);
int KWRAP_PE_SetTnrDetailBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckTnr2ndCmnParam(void *param);
int KWRAP_PE_SetTnr2ndCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckTnr2ndDetailParam(void *param);
int KWRAP_PE_SetTnr2ndDetailBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrSqmCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckDnrSqmCmnParam(void *param);
int KWRAP_PE_SetTnrSqmCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_CheckTnrSqmCmnParam(void *param);
int KWRAP_PE_CheckTnr2ndSqmCmnParam(void *param);
int KWRAP_PE_CheckDnrDcntSqmCmnParam(void *param);
int KWRAP_PE_CheckLedDcntSqmCmnParam(void *param);
int KWRAP_PE_CheckResSqmCmnParam(void *param);
int KWRAP_PE_CheckResSqmDetailParam(void *param);
int KWRAP_PE_CheckSre2KSqmCmnParam(void *param);
int KWRAP_PE_CheckSre2KSqmDetailParam(void *param);

int KWRAP_PE_SetDefaultParam(PE_KWRAP_CTRL_T *param, \
				UINT32 type, void *ctrl, const char *func, int line);
int KWRAP_PE_CheckDnrDcntDetailParam(void *param);
int KWRAP_PE_GetDnrDcntDetailDefaultSettings(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrDcntDetailBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetDnrDcntCmnParam(void *param);

void KWRAP_PE_PrintTnrCmnParam(void *setting);
void KWRAP_PE_PrintTnrDetailParam(void *setting);
void KWRAP_PE_PrintDnrCmnParam(void *setting);
void KWRAP_PE_PrintDnrDetailParam(void *setting);
void KWRAP_PE_PrintDnrDcntCmnParam(void *setting);
void KWRAP_PE_PrintDnrDcntDetailParam(void *setting);
void KWRAP_PE_PrintLedDcntCmnParam(void *setting);
void KWRAP_PE_PrintLedDcntDetailParam(void *setting);

int KWRAP_PE_SetRenSqmCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetSre2KSqmCmnBspDB(PE_KWRAP_CTRL_T *param);
int KWRAP_PE_SetRenEasyCmnParam(void *param);
int KWRAP_PE_SetSre2KRenEasyCmnParam(void *param);

void KWRAP_PE_DebugPrint(unsigned int _type, char* _fmt, ...);

/*for F20*/
int KWRAP_PE_SetReAllParam(void *param);
int KWRAP_PE_SetTnrCmnAllParam(void *param);
int KWRAP_PE_SetDnrCmnAllParam(void *param);
int KWRAP_PE_SetDnrDcntCmnAllParam(void *param);
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_KWRAP_H_ */
