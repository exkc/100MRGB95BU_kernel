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


/** @file vpq_hwrap_pe.h
 *
 *  application interface header for picture enhance
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_VPQ_HWRAP_PE_H_
#define	_VPQ_HWRAP_PE_H_

#include "base_types.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"
/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
/* define for cm region control num */
#define VPQ_HWRAP_CM_TBLPOINT		8
#define VPQ_HWRAP_CM_DELTANUM		6
#define VPQ_HWRAP_CM_RGN_CTRL_NUM	16
#define VPQ_HWRAP_CM_CW_GAINTB		5
#define VPQ_HWRAP_CM_CW_NUM			16

/*define for DRC*/
#define VPQ_HWRAP_CM_GLOBAL_POINT	4
#define VPQ_HWRAP_CM_LOCAL_POINT	6
#define VPQ_HWRAP_CM_LOCAL_CURVE	17
#define VPQ_HWRAP_CM_LOCAL_CURVE_O26	33
#define VPQ_HWRAP_CM_FREE_POINT		6

#define VPQ_HWRAP_NUM_TRANSCURVE	(16)

/* define for OBC*/
#define VPQ_HWRAP_PSP_GAIN_LUT_NUM	2
#define VPQ_HWRAP_PSP_LUT_NUM 		8
#define VPQ_HWRAP_PSP_FREE_POINT		7
#define VPQ_HWRAP_PSP_SAT_LUT_NUM 	4

#define VPQ_HWRAP_SHP_STEP	5
#define VPQ_HWRAP_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE 17

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/* 511/360=1.41944, 360/511=0.70450,
* 0~360~540degree <-> 0x0~0x1ff(511)~0x2ff(767) */
/* if degree to 10bit & x=361~540 :
* (x*255)/179 - 2.2573 + 0.5 = x*1.42458 - 1.7573 */
#define VPQ_HWRAP_CONV_DEGREE_TO_10BIT(x)	\
	(((x) <= 360) ? (UINT16)((((UINT32)(x) * 141944) + 50000) / 100000) : (((x) < 541) ? \
	(UINT16)((((UINT32)(x) * 142458) - 175730) / 100000) : 767))
/* 127/100=1.27, 100/127=0.7874, 0~100 <-> 0x0~0xff(127) */
#define VPQ_HWRAP_CONV_PERCENT_TO_8BIT(x)	\
	(((x) >= 100) ? (127) : ((UINT8)((((UINT32)(x) * 127) + 50) / 100)))
#define PE_GET_BITS(val, nd, wd)	(((val)>>(nd))&(0xFFFFFFFF>>(32-(wd))))

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/
typedef struct {
	signed int sPcVal[4];
	signed int contrast;
	signed int brightness;
	signed int saturation;
	signed int hue;
	signed short dimming;
} vpq_hwrap_pic_ctrl_t;

typedef enum
{
	VPQ_HWRAP_INPUT_ATV = 0,		///< analog rf
	VPQ_HWRAP_INPUT_AV,				///< cvbs,svideo 1
	VPQ_HWRAP_INPUT_SCARTRGB, 		///< scart-rgb   2
	VPQ_HWRAP_INPUT_COMP, 			///< component   3
	VPQ_HWRAP_INPUT_RGB_PC,			///< rgb-pc      4
	VPQ_HWRAP_INPUT_HDMI_TV,		///< hdmi non-pc(hdmi-av,dvi-dtv,mcam) 5
	VPQ_HWRAP_INPUT_HDMI_PC,		///< hdmi pc(dvi-pc) 6
	VPQ_HWRAP_INPUT_DTV,			///< digital rf      7
	VPQ_HWRAP_INPUT_PICWIZ,			///< dtv pic wiz     8
	VPQ_HWRAP_INPUT_PICTEST,		///< dtv pic test    9
	VPQ_HWRAP_INPUT_MEDIA_MOVIE,	///< divx, cp-divx   10
	VPQ_HWRAP_INPUT_MEDIA_PHOTO,	///< photo, cp-photo 11
	VPQ_HWRAP_INPUT_CAMERA,			///< vcs             12
	VPQ_HWRAP_INPUT_PVR_DTV,		///< pvr dtv         13
	VPQ_HWRAP_INPUT_PVR_ATV,		///< pvr atv         14
	VPQ_HWRAP_INPUT_PVR_AV,			///< pvr av,scart-rgb15
	VPQ_HWRAP_INPUT_MAX				///< max num         16
} vpq_hwrap_input_t;	// HAL_VPQ_INPUT_T

typedef struct
{
	vpq_hwrap_input_t vpq_input[LX_PE_WIN_NUM];	///< vpq input
	UINT32 shp_cmn_val; 						///< shp common value
	UINT32 is_vr;								///< vr 360 mode
	UINT32 dyn_color_init;						///< dynamic color
	int blacklevelinput[4];						///< see vpq_hwrap_input_t [0~3]:wid 0~3
	int blackleveltype[4];						///< see enum v4l2_ext_vpq_black_level_type [0~3]:wid 0~3
	int pre_blackleveltype[4];					///< see enum v4l2_ext_vpq_black_level_type [0~3]:wid 0~3
	int icsc_updatecnt[4];
	int pre_icsc_updatecnt[4];
	UINT32 year_option; ///< o22n:23, o22:22, others 0;
} vpq_hwrap_info_t;

typedef struct {
	unsigned short cs00;
	unsigned short cs01;
	unsigned short cs02;
	unsigned short cs03;
	unsigned short cs04;
	unsigned short cs10;
	unsigned short cs11;
	unsigned short cs12;
	unsigned short cs13;
	unsigned short cs14;
	unsigned short cs20;
	unsigned short cs21;
	unsigned short cs22;
	unsigned short cs23;
	unsigned short cs24;
}vpq_hwrap_csc_coeff_t;

typedef struct {
	unsigned char blacklevel; 	  	///blacklevel, 0:low,1:high
	vpq_hwrap_input_t inputinfo;	///<
	vpq_hwrap_csc_coeff_t data;		///<
}vpq_hwrap_blacklevel_t;

typedef struct
{
	UINT8	shp_cmn_2k[19];
	UINT8	shp_djg_2k[8];
	UINT8	shp_ui_main_2k[14];
	UINT8	shp_ui_h_main_2k[6];
	UINT8	shp_ui_v_main_2k[2];
	UINT8	shp_map_cmn_2k[20];
	UINT8	shp_balance_2k[30];
	UINT8	shp_ee_2k[14];
	UINT8	shp_de_2k[14];
	UINT8	shp_ti_cmn_2k[12];
	UINT8	shp_ti_ui_main_2k[3];
	UINT8	shp_simple_snr_2k[3];
	UINT32	shp_ui_sqm_2k[29];
	UINT32	shp_sqm_cmn_2k[11];
	UINT8	shp_cmn_vsd[23];
	UINT8	shp_djg_vsd[8];
	UINT8	shp_ui_main_vsd[15];
	UINT8	shp_ui_h_main_vsd[6];
	UINT8	shp_ui_v_main_vsd[2];
	UINT8	shp_map_cmn_vsd[20];
	UINT8	shp_balance_vsd[30];
	UINT8	shp_ee_vsd[14];
	UINT8	shp_de_vsd[14];
	UINT8	shp_ti_cmn_vsd[12];
	UINT8	shp_ti_ui_main_vsd[3];
	UINT8	shp_simple_snr_vsd[3];
	UINT8	shp_cti_cmn_vsd[8];
	UINT8	shp_cti_ui_main_vsd[2];
	UINT8	shp_motion_vsd[9];
	UINT8	shp_chroma_vsd[5];
	UINT32	shp_ui_sqm_vsd[30];
	UINT32	shp_sqm_cmn_vsd[19];
} vpq_hwrap_chip_shp_t;
typedef struct
{
	UINT8  shp_cmn_2k[17];
	UINT8  shp_djg_2k[8];
	UINT8  shp_ui_main_2k[12];
	UINT8  shp_map_cmn_2k[12];
	UINT8  shp_balance_2k[30];
	UINT8  shp_ee_2k[28];
	UINT8  shp_ti_cmn_2k[14];
	UINT32 shp_ui_sqm_2k[39];
	UINT32 shp_sqm_cmn_2k[43];
	UINT8  shp_cmn_vsd[25];
	UINT8  shp_djg_vsd[8];
	UINT8  shp_ui_main_vsd[15];
	UINT8  shp_map_cmn_vsd[12];
	UINT8  shp_balance_vsd[30];
	UINT8  shp_ee_vsd[28];
	UINT8  shp_ti_cmn_vsd[14];
	UINT8  shp_chroma_vsd[5];
	UINT16 shp_dnn_sr_vsd[9];
	UINT8  shp_face_obj_vsd[8];
	UINT32 shp_ui_sqm_vsd[40];
	UINT32 shp_sqm_cmn_vsd[51];
} vpq_hwrap_chip_shp_o20_t;
typedef struct
{
	UINT8  shp_cmn_2k[17];
	UINT8  shp_djg_2k[8];
	UINT8  shp_ui_main_2k[12];
	UINT8  shp_map_cmn_2k[12];
	UINT8  shp_balance_2k[30];
	UINT8  shp_ee_2k[28];
	UINT8  shp_ti_cmn_2k[14];
	UINT32 shp_ui_sqm_2k[39];
	UINT32 shp_sqm_cmn_2k[43];
	UINT8  shp_cmn_4k[17];
	UINT8  shp_djg_4k[8];
	UINT8  shp_ui_main_4k[12];
	UINT8  shp_map_cmn_4k[12];
	UINT8  shp_balance_4k[30];
	UINT8  shp_ee_4k[28];
	UINT8  shp_ti_cmn_4k[14];
	UINT16 shp_dnn_sr_4k[9];
	UINT32 shp_ui_sqm_4k[39];
	UINT32 shp_sqm_cmn_4k[43];
	UINT8  shp_cmn_vsd[25];
	UINT8  shp_djg_vsd[8];
	UINT8  shp_ui_main_vsd[15];
	UINT8  shp_map_cmn_vsd[12];
	UINT8  shp_balance_vsd[30];
	UINT8  shp_ee_vsd[28];
	UINT8  shp_ti_cmn_vsd[14];
	UINT8  shp_chroma_vsd[5];
	UINT8  shp_face_obj_vsd[8];
	UINT32 shp_ui_sqm_vsd[40];
	UINT32 shp_sqm_cmn_vsd[67];
} vpq_hwrap_chip_shp_e60_t;

typedef struct
{
	UINT8  shp_cmn_2k[17];
	UINT8  shp_djg_2k[8];
	UINT8  shp_ui_main_2k[12];
	UINT8  shp_map_cmn_2k[12];
	UINT8  shp_balance_2k[30];
	UINT8  shp_ee_2k[28];
	UINT8  shp_ti_cmn_2k[14];
	UINT32 shp_ui_sqm_2k[39];
	UINT32 shp_sqm_cmn_2k[43];
	UINT8  shp_cmn_vsd[25];
	UINT8  shp_djg_vsd[8];
	UINT8  shp_ui_main_vsd[15];
	UINT8  shp_map_cmn_vsd[12];
	UINT8  shp_balance_vsd[30];
	UINT8  shp_ee_vsd[28];
	UINT8  shp_ti_cmn_vsd[14];
	UINT8  shp_chroma_vsd[5];
	UINT16 shp_dnn_sr_vsd[9];
	UINT8  shp_face_obj_vsd[25];// diff from o20
	UINT32 shp_ui_sqm_vsd[40];
	UINT32 shp_sqm_cmn_vsd[71];// diff from o20
} vpq_hwrap_chip_shp_o22_t;

/**************************
**webos24 new DB***********
**requested in SICREQ-529
***************************/
typedef struct
{
	UINT8  shp_cmn_2k[17];
	UINT8  shp_djg_2k[8];
	UINT8  shp_ui_main_2k[12];
	UINT8  shp_map_cmn_2k[12];
	UINT8  shp_balance_2k[30];
	UINT8  shp_ee_2k[28];
	UINT8  shp_ti_cmn_2k[14];
	UINT32 shp_ui_sqm_2k[49];   ///< shp_ui_sqm_2k[39] -> ?shp_ui_sqm_2k[49] <- 변경사항  요청사항 <1>번 
	UINT32 shp_sqm_cmn_2k[43];
	UINT8  shp_cmn_vsd[25];
	UINT8  shp_djg_vsd[8];
	UINT8  shp_ui_main_vsd[15];
	UINT8  shp_map_cmn_vsd[12];
	UINT8  shp_balance_vsd[30];
	UINT8  shp_ee_vsd[28];
	UINT8  shp_ti_cmn_vsd[14];
	UINT8  shp_chroma_vsd[5];
	UINT16 shp_dnn_sr_vsd[9];
	UINT8  shp_face_obj_vsd[25];
	UINT32 shp_ui_sqm_vsd[50];  //// shp_ui_sqm_vsd[40] -> shp_ui_sqm_vsd[50]  <- 변경사항 요청사항 <1>번
	UINT32 shp_sqm_cmn_vsd[71];
} vpq_hwrap_chip_shp_o22n2_t;

typedef struct
{
	UINT8  shp_cmn_2k[17];
	UINT8  shp_djg_2k[8];
	UINT8  shp_ui_main_2k[12];
	UINT32 shp_luma_en_2k;      ///UINT32 변수 하나, shp_luma_2k[1] reg_luma_dp_blend_en <- 신규 추가 요청사항 <4-1>번 
	UINT8  shp_map_cmn_2k[12];
	UINT8  shp_balance_2k[30];
	UINT8  shp_ee_2k[28];
	UINT8  shp_ti_cmn_2k[14];
	UINT32 shp_ui_sqm_2k[49];   ///< shp_ui_sqm_2k[39] -> ?shp_ui_sqm_2k[49] <- 변경사항  요청사항 <2>번 
	UINT32 shp_sqm_cmn_2k[51];  ///<shp_sqm_cmn_2k[43] -> shp_sqm_cmn_2k[51] <- 변경사항 요청사항 <3>번
	UINT8  shp_cmn_vsd[25];
	UINT8  shp_djg_vsd[8];
	UINT8  shp_ui_main_vsd[15];
	UINT32 shp_luma_en_vsd;     ///UINT32 변수 하나, shp_luma_vsd[1] reg_luma_dp_blend_en <- 신규 추가 요청사항 <4-1>번 
	UINT8  shp_map_cmn_vsd[12];
	UINT8  shp_balance_vsd[30];
	UINT8  shp_ee_vsd[28];
	UINT8  shp_ti_cmn_vsd[14];
	UINT8  shp_chroma_vsd[5];
	UINT16 shp_dnn_sr_vsd[17];  ///< shp_dnn_sr_vsd[9] -> shp_dnn_sr_vsd[17] <- 변경사항 요청사항 <3>번
	UINT8  shp_face_obj_vsd[25];
	UINT32 shp_ui_sqm_vsd[50];  ///< shp_ui_sqm_vsd[40] -> shp_ui_sqm_vsd[50]  <- 변경사항 요청사항 <2>번
	UINT32 shp_sqm_cmn_vsd[71];
} vpq_hwrap_chip_shp_o24_t;


typedef struct
{
	UINT8  shp_cmn_2k[17];
	UINT8  shp_djg_2k[8];
	UINT8  shp_ui_main_2k[12];
	UINT32 shp_luma_en_2k;		///< reg_luma_dp_blend_en
	UINT8  shp_map_cmn_2k[12];
	UINT8  shp_balance_2k[30];
	UINT8  shp_ee_2k[28];
	UINT8  shp_ti_cmn_2k[14];
	UINT32 shp_ui_sqm_2k[57];   ///< shp_ui_sqm_2k[49];  → shp_ui_sqm_2k[57];
	UINT32 shp_sqm_cmn_2k[59];  ///< shp_sqm_cmn_2k[51];  → shp_sqm_cmn_2k[59];
	UINT8  shp_cmn_vsd[25];
	UINT8  shp_djg_vsd[8];
	UINT8  shp_ui_main_vsd[15];
	UINT32 shp_luma_en_vsd;     ///< reg_luma_dp_blend_en
	UINT8  shp_map_cmn_vsd[12];
	UINT8  shp_balance_vsd[30];
	UINT8  shp_ee_vsd[28];
	UINT8  shp_ti_cmn_vsd[14];
	UINT8  shp_chroma_vsd[5];
	UINT16 shp_dnn_sr_vsd[17];  ///< 
	UINT8  shp_face_obj_vsd[17];///< shp_face_obj_vsd[25];  → shp_face_obj_vsd[17];
	UINT32 shp_ui_sqm_vsd[65];  ///< hp_ui_sqm_vsd[50];  → shp_ui_sqm_vsd[65];
	UINT32 shp_sqm_cmn_vsd[87];   ///< shp_sqm_cmn_vsd[71];  → shp_sqm_cmn_vsd[87];
} vpq_hwrap_chip_shp_o26_t;

typedef struct
{
    unsigned short ui_value[4];
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
} vpq_hwrap_shp_t;

typedef struct
{
	 UINT8	tnr0___en;		 ///< tnr enable(ui)
	 UINT32 tnr0__lut[16];	 ///< lut (ui)
	 UINT32 tnr0_gain[5];	 ///< gian (ui)
	 UINT32 tnr0_buff[32];	 ///< buff (ui)
	 UINT32 tnr0__sqm[11];	 ///< *new sqm(ui)
	 UINT8	tnr0__ctl[21];	 ///< tnr_ctrl
	 UINT8	tnr0___ma[2];	 ///< tnr_ma
	 UINT8	tnr0___me[12];	 ///< tnr_me
	 UINT8	tnr0__mlb[15];	 ///< tnr_melb
	 UINT8	tnr0___mc[26];	 ///< tnr_mc
	 UINT8  tnr0__edf[36];	 ///< tnr_df
	 UINT8	tnr0_blnd[24];	 ///< tnr_blend
	 UINT8	tnr1___en;		 ///< tnr enable(ui)
	 UINT32 tnr1__lut[16];	 ///< lut (ui)
	 UINT32 tnr1_gain[5];	 ///< gian (ui)
	 UINT32 tnr1_buff[32];	 ///< buff (ui)
	 UINT32 tnr1__sqm[11];	 ///< *new sqm(ui)
	 UINT8	tnr1__ctl[21];	 ///< tnr_ctrl
	 UINT8	tnr1___ma[2];	 ///< tnr_ma
	 UINT8	tnr1___me[12];	 ///< tnr_me
	 UINT8	tnr1__mlb[15];	 ///< tnr_melb
	 UINT8	tnr1___mc[26];	 ///< tnr_mc
	 UINT8  tnr1__edf[36];	 ///< tnr_df
	 UINT8	tnr1_blnd[24];	 ///< tnr_blend
} vpq_hwrap_chip_nr_t;

/* use same DB with o20, e60 ,022 */
typedef struct
{
	UINT32 tnr0___en;		///< tnr enable(ui)
	UINT32 tnr0__lut[16];	///< lut (ui)
	UINT32 tnr0_gain[5];	///< gian (ui)
	UINT32 tnr0_buff[15];	///< buff (ui)
	UINT32 tnr0__sqm[11];	///< sqm(ui)
	UINT8  tnr0__ctl[21];	///< tnr_ctrl
	UINT8  tnr0___ma[2];	///< tnr_ma
	UINT8  tnr0___me[8];	///< tnr_me
	UINT8  tnr0__mlb[15];	///< tnr_melb
	UINT16 tnr0___mc[31];	///< tnr_mc
	UINT8  tnr0_blnd[24];	///< tnr_blend
	UINT8  tnr1___en;		///< tnr enable(ui)
	UINT32 tnr1__lut[16];	///< lut (ui)
	UINT32 tnr1_gain[5];	///< gian (ui)
	UINT32 tnr1_buff[15];	///< buff (ui)
	UINT32 tnr1__sqm[11];	///< sqm(ui)
	UINT8  tnr1__ctl[21];	///< tnr_ctrl
	UINT8  tnr1___ma[2];	///< tnr_ma
	UINT8  tnr1___me[8];	///< tnr_me
	UINT8  tnr1__mlb[15];	///< tnr_melb
	UINT16 tnr1___mc[31];	///< tnr_mc
	UINT8  tnr1_blnd[24];	///< tnr_blend
} vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t;

/* use DB with o26 */
typedef struct
{
	UINT32 tnr0___en;		///< tnr enable(ui)
	UINT32 tnr0__lut[16];	///< lut (ui)
	UINT32 tnr0_gain[5];	///< gian (ui)
	UINT32 tnr0_face_gain[4];
	UINT32 tnr0_buff[15];	///< buff (ui)
	UINT32 tnr0__sqm[11];	///< sqm(ui)
	UINT8  tnr0__ctl[21];	///< tnr_ctrl
	UINT8  tnr0___ma[2];	///< tnr_ma
	UINT8  tnr0___me[8];	///< tnr_me
	UINT8  tnr0__mlb[15];	///< tnr_melb
	UINT16 tnr0___mc[31];	///< tnr_mc
	UINT8  tnr0_blnd[24];	///< tnr_blend
	UINT8  tnr1___en;		///< tnr enable(ui)
	UINT32 tnr1__lut[16];	///< lut (ui)
	UINT32 tnr1_gain[5];	///< gian (ui)
	UINT32 tnr1_buff[15];	///< buff (ui)
	UINT32 tnr1__sqm[11];	///< sqm(ui)
	UINT8  tnr1__ctl[21];	///< tnr_ctrl
	UINT8  tnr1___ma[2];	///< tnr_ma
	UINT8  tnr1___me[8];	///< tnr_me
	UINT8  tnr1__mlb[15];	///< tnr_melb
	UINT16 tnr1___mc[31];	///< tnr_mc
	UINT8  tnr1_blnd[24];	///< tnr_blend
	UINT8  tnr2___en;		///< tnr enable(ui)
	UINT32 tnr2__lut[16];	///< lut (ui)
	UINT32 tnr2_gain[5];	///< gian (ui)
	UINT32 tnr2_buff[15];	///< buff (ui)
	UINT32 tnr2__sqm[11];	///< sqm(ui)
	UINT8  tnr2__ctl[21];	///< tnr_ctrl
	UINT8  tnr2___ma[2];	///< tnr_ma
	UINT8  tnr2___me[8];	///< tnr_me
	UINT8  tnr2__mlb[15];	///< tnr_melb
	UINT16 tnr2___mc[31];	///< tnr_mc
	UINT8  tnr2_blnd[24];	///< tnr_blend
} vpq_hwrap_chip_nr_o26_t;


typedef struct
{
    unsigned short ui_value[2];
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
} vpq_hwrap_nr_t;

typedef struct
{
	 UINT8	dnr______ui[8]; ///< common(ui)
	 UINT32 dnr____buff[5];  ///< new common ui
	 UINT32 dnr___sqmui[19]; ///< new sqm ui
	 UINT8	dnr_____mnr[6]; ///< dc bnr
	 UINT8	dnr___dcbnr[34]; ///< dc bnr
	 UINT8	dnr___acbnr[31]; ///< ac bnr
} vpq_hwrap_chip_mpeg_nr_t;

/* use same DB with o20, e60 ,022 */
typedef struct
{
	UINT32 dnr______ui[13]; ///< common(ui)
	UINT32 dnr____buff[8];	///< common ui
	UINT32 dnr___sqmui[15]; ///< sqm ui
	UINT8  dnr_____mnr[6]; ///< dc bnr
	UINT8  dnr___dcbnr[34]; ///< dc bnr
	UINT8  dnr___acbnr[31]; ///< ac bnr 
} vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t;

/* use DB with o26 */
typedef struct
{
	UINT32 dnr0_____ui[11]; ///< common(ui)
	UINT32 dnr0___buff[8];	///< common ui
	UINT32 dnr0__sqmui[17]; ///< sqm ui
	UINT32 dnr0____mnr[15]; ///< dc bnr
	UINT8  dnr0__dcbnr[33]; ///< dc bnr
	UINT8  dnr0__acbnr[31]; ///< ac bnr 
	UINT32 dnr1_____ui[9]; ///< common(ui) 신규 
	UINT32 dnr1___buff[8];	///< common ui 신규 
	UINT32 dnr1__sqmui[15]; ///< sqm ui 신규 
	UINT8  dnr1____mnr[6];	///< dc bnr 신규 
	UINT8  dnr1__dcbnr[33]; ///< dc bnr 신규 
	UINT8  dnr1__acbnr[31]; ///< ac bnr  신규 
} vpq_hwrap_chip_mpeg_nr_o26_t;


typedef struct
{
	unsigned char ui_value;
	union {
		unsigned char *pst_chip_data;
		unsigned int compat_data;
		unsigned long long sizer;
	};
} vpq_hwrap_mpeg_nr_t;

typedef struct
{
	UINT8  reg_edge_shift_en;				///<reg_edge_shift_en 0xc900d0a0[4]
	UINT8  reg_master_gain; 				///<reg_master_gain   0xc900d0a4[31:24]
	UINT8  reg_max_clip;					///<reg_max_clip	   0xc900d0a4[23:16]
	UINT8  reg_base;						///<reg_base			 0xc900d0a4[15:8]
	UINT8  reg_min_ratio;					///<reg_min_ratio		0xc900d0a4[7:0]
	UINT8  reg_ltv_mul; 					///<reg_ltv_mul 		0xc900d0a8[15:8]
	UINT8  reg_ltv_offset;					///<reg_ltv_offset		0xc900d0a8[7:0]
} vpq_hwrap_chip_sr_t;

typedef struct
{
	UINT32 wId;
	UINT8 uUi;
	vpq_hwrap_chip_sr_t *pChip;
} vpq_hwrap_sr_t;

typedef struct
{ 
	UINT16 deconnd_____ui[12];
	UINT32 deconnd___buff[5];
	UINT32 deconnd__sqmui[23];
	UINT16 deconnd____cmn[61];
} vpq_hwrap_chip_decontour_t;

typedef struct
{ 
	UINT32 deconnd_____ui[15];
	UINT32 deconnd___buff[8];
	UINT32 deconnd__sqmui[23];
	UINT16 deconnd____cmn[63];
	UINT8  deconnd___face[24];
	UINT32 deconled____ui[15];
	UINT32 deconled__buff[8];
	UINT32 deconled_sqmui[23];
	UINT16 deconled___cmn[63];
	UINT8  deconled__face[24];
} vpq_hwrap_chip_decontour_o20_f20_e60_t;

typedef struct
{ 
	UINT32 deconnd_____ui[14];// diff from o20
	UINT32 deconnd___buff[8];
	UINT32 deconnd__sqmui[23];
	UINT16 deconnd____cmn[77];// diff from o20
	UINT8  deconnd___face[32];// diff from o20
} vpq_hwrap_chip_decontour_o22_f22_t;

typedef struct
{ 
	UINT32 deconnd_____ui[14];
	UINT32 deconnd___buff[8];
	UINT32 deconnd__sqmui[27]; //deconnd__sqmui[23] -> deconnd__sqmui[27], SICREQ-530
	UINT16 deconnd____cmn[77];
	UINT8  deconnd___face[28]; //deconnd___face[32] -> deconnd___face[28], SICREQ-530
	UINT32 deconcco____ui[22]; //신규 gCoeffNr_DeconLED_UI, SICREQ-530
	UINT32 deconcco__buff[8];  //신규 gCoeffNr_DeconLED_UI, SICREQ-530
	UINT32 deconcco_sqmui[35]; //신규 , SICREQ-530
	UINT16 deconcco___cmn[51]; //신규, SICREQ-530
	UINT8  deconcco__face[20]; //신규, SICREQ-530
} vpq_hwrap_chip_decontour_o24_t;

typedef struct
{ 
	UINT32 deconnd0____ui[14];
	UINT32 deconnd0__buff[8];
	UINT32 deconnd0_sqmui[27];
	UINT16 deconnd0___cmn[77];
	UINT8  deconnd0__face[28];
	UINT32 deconnd1____ui[14]; //신규
	UINT32 deconnd1__buff[8];  //신규
	UINT32 deconnd1_sqmui[27]; //신규
	UINT16 deconnd1___cmn[61]; //신규
	UINT8  deconnd1__face[20]; //신규
	UINT32 deconcco____ui[22];
	UINT32 deconcco__buff[8];
	UINT32 deconcco_sqmui[35];
	UINT16 deconcco___cmn[51];
	UINT8  deconcco__face[20];
} vpq_hwrap_chip_decontour_o26_t;


typedef struct
{
    unsigned short ui_value;
    union {
        unsigned char *pst_chip_data;
        unsigned int compat_data;
        unsigned long long sizer;
    };
} vpq_hwrap_decontour_t;

struct vpq_hwrap_cm_db_region_gain
{
	unsigned char	needUpdate;	// 0: skip action, 1: update CM using this struct values
	unsigned char	regionNum;
	unsigned char	masterGain;
	signed char		delta[VPQ_HWRAP_CM_DELTANUM];
};

struct vpq_hwrap_cm_db_region_ctrl
{
	unsigned char	needUpdate;	// 0: skip action, 1: update CM using this struct values
	unsigned char	regionNum;
	unsigned char	region_en;
	unsigned short	hue_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	hue_g[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	sat_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	sat_g[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	val_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	val_g[VPQ_HWRAP_CM_TBLPOINT];
};

struct vpq_hwrap_cm_db_region_ctrl_o26
{
	unsigned char	needUpdate;	// 0: skip action, 1: update CM using this struct values
	unsigned char	regionNum;
	unsigned char	region_en;
	unsigned char	aiGainNum;	//추가
	unsigned short	hue_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	hue_g[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	sat_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	sat_g[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	val_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char	val_g[VPQ_HWRAP_CM_TBLPOINT];
};


struct vpq_hwrap_cm_db_clear_white
{
	unsigned char	needUpdate;	// 0: skip action, 1: update CM using this struct values
    unsigned char   color_region_gain;
    unsigned char   color_region_onoff[VPQ_HWRAP_CM_RGN_CTRL_NUM];
    unsigned char   cw_en;
    unsigned char   cw_sel;
	unsigned char	gain_r;
	unsigned char	gain_g;
	unsigned char	gain_b;
    unsigned short  cw_hue_x[VPQ_HWRAP_CM_TBLPOINT];
    unsigned char  cw_hue_y[VPQ_HWRAP_CM_TBLPOINT];
    unsigned char  cw_sat_x[VPQ_HWRAP_CM_TBLPOINT];
    unsigned char  cw_sat_y[VPQ_HWRAP_CM_TBLPOINT];
    unsigned char  cw_val_x[VPQ_HWRAP_CM_TBLPOINT];
    unsigned char  cw_val_y[VPQ_HWRAP_CM_TBLPOINT];
};

struct vpq_hwrap_cm_db_dse
{
	unsigned char	needUpdate;	// 0: skip action, 1: update CM using this struct values
	unsigned char	saturation_cr_mode;
	unsigned short	saturation_region_gain;
	unsigned short	dse_h_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned short	dse_h_y[VPQ_HWRAP_CM_TBLPOINT];
	unsigned short	dse_y_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned short	dse_y_y[VPQ_HWRAP_CM_TBLPOINT];
	unsigned short	sSaturationLUT_x[16];
	unsigned short	sSaturationLUT_y[16];
	unsigned char	region_onoff[VPQ_HWRAP_CM_RGN_CTRL_NUM];
};

struct vpq_hwrap_cm_db_vspcc
{
	unsigned char	needUpdate;	// 0: skip action, 1: update CM using this struct values
	unsigned char	satTarget;
	unsigned char	objMapGainLUT_x[4];
	unsigned char	objMapGainLUT_y[4];
	unsigned char	faceMapGainLUT_x[4];
	unsigned char	faceMapGainLUT_y[4];
	unsigned short	hue_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char 	hue_g[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char 	sat_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char 	sat_g[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char 	val_x[VPQ_HWRAP_CM_TBLPOINT];
	unsigned char 	val_g[VPQ_HWRAP_CM_TBLPOINT];
};

struct vpq_hwrap_cm_db_vspcc_o26
{
	unsigned char	needUpdate;	// 0: skip action, 1: update CM using this struct values
	unsigned char	headMap0Gain;
	unsigned char	headMap0GainLUT_x[4];
	unsigned char	headMap0GainLUT_y[4];
	unsigned char	bodyMap0Gain;
	unsigned char	bodyMap0GainLUT_x[4];
	unsigned char	bodyMap0GainLUT_y[4];
	unsigned char	textMap0Gain;
	unsigned char	textMap0GainLUT_x[4];
	unsigned char	textMap0GainLUT_y[4];
	unsigned char	motionMap0Gain;
	unsigned char	motionMap0GainLUT_x[4];
	unsigned char	motionMap0GainLUT_y[4];
	unsigned char	headMap1Gain;
	unsigned char	headMap1GainLUT_x[4];
	unsigned char	headMap1GainLUT_y[4];
	unsigned char	bodyMap1Gain;
	unsigned char	bodyMap1GainLUT_x[4];
	unsigned char	bodyMap1GainLUT_y[4];
	unsigned char	textMap1Gain;
	unsigned char	textMap1GainLUT_x[4];
	unsigned char	textMap1GainLUT_y[4];
	unsigned char	motionMap1Gain;
	unsigned char	motionMap1GainLUT_x[4];
	unsigned char	motionMap1GainLUT_y[4];
};

typedef struct
{
    struct vpq_hwrap_cm_db_region_gain	region_gain[VPQ_HWRAP_CM_RGN_CTRL_NUM];
    struct vpq_hwrap_cm_db_region_ctrl	region_ctrl[VPQ_HWRAP_CM_RGN_CTRL_NUM];
    struct vpq_hwrap_cm_db_clear_white	clear_white;
	struct vpq_hwrap_cm_db_dse			cm_dse;
	struct vpq_hwrap_cm_db_vspcc		cm_vspcc;
} vpq_hwrap_cm_db_t;

typedef struct
{
    struct vpq_hwrap_cm_db_region_gain		region_gain[VPQ_HWRAP_CM_RGN_CTRL_NUM];
    struct vpq_hwrap_cm_db_region_ctrl_o26	region_ctrl[VPQ_HWRAP_CM_RGN_CTRL_NUM];
    struct vpq_hwrap_cm_db_clear_white		clear_white;
	struct vpq_hwrap_cm_db_dse				cm_dse;
	struct vpq_hwrap_cm_db_vspcc_o26			cm_vspcc;
} vpq_hwrap_cm_db_o26_t;

typedef struct
{
	BOOLEAN	region_en;
	UINT32 regionNum;		// 0~15
	UINT16 hue_x[VPQ_HWRAP_CM_TBLPOINT];		// 0~360~720 degree
	UINT8 hue_g[VPQ_HWRAP_CM_TBLPOINT];		// 0~127
	UINT8 sat_x[VPQ_HWRAP_CM_TBLPOINT];		// 0~100
	UINT8 sat_g[VPQ_HWRAP_CM_TBLPOINT];		// 0~127
	UINT8 val_x[VPQ_HWRAP_CM_TBLPOINT];		// 0~255
	UINT8 val_g[VPQ_HWRAP_CM_TBLPOINT];		// 0~127
} vpq_hwrap_cm_region_b0_t;	// CHIP_CM_REGION_B0_T

typedef struct
{
	UINT32 regionNum;		// 0~15
	SINT8 reDelta[VPQ_HWRAP_CM_DELTANUM];		// -128 ~ 127, [0]h [1]s [2]v [3]g [4]b [5]r
	UINT8 reMasterGain;		// 0~128~255
} vpq_hwrap_cm_regionctrl_b0_t;	// CHIP_CM_REGIONCTRL_B0_T

typedef struct
{
	UINT32 gain_table_x[VPQ_HWRAP_CM_CW_GAINTB];
	UINT32 gain_table_y[VPQ_HWRAP_CM_CW_GAINTB];
	UINT8  color_region_gain;
	UINT8  color_region_onoff[VPQ_HWRAP_CM_CW_NUM];
	UINT8  cw_en;
	UINT8  cw_sel;
	UINT32 cw_r;
	UINT32 cw_g;
	UINT32 cw_b;
} vpq_hwrap_cm_clear_white_t;	// CHIP_CM_CLEAR_WHITE_T

typedef struct
{
	vpq_hwrap_cm_region_b0_t data[VPQ_HWRAP_CM_RGN_CTRL_NUM];		///< region data
} vpq_hwrap_cm_init_adv_color_t;	// CHIP_CM_INIT_ADV_COLOR_T

typedef struct
{
	vpq_hwrap_cm_regionctrl_b0_t gain[VPQ_HWRAP_CM_RGN_CTRL_NUM];	///< region gain
	vpq_hwrap_cm_clear_white_t clear_white;							///< clear white
	UINT32 sat_gain_lut_x[9];										///<dynamic sturation gainLUT_x
	UINT32 sat_gain_lut_y[9];										///<dynamic sturation gainLUT_y
} vpq_hwrap_cm_dynamic_color_t;	// CHIP_CM_DYNAMIC_COLOR_T

typedef struct
{
	vpq_hwrap_cm_regionctrl_b0_t gain;	///< region gain
	SINT8 skin_hue_val;					///< skin hue value
	SINT8 bsky_hue_val;					///< blue sky hue value
	SINT8 grass_hue_val;				///< grass hue value
} vpq_hwrap_cm_color_control_t;	// CHIP_COLOR_CONTROL_T

typedef struct
{
	vpq_hwrap_cm_region_b0_t data[VPQ_HWRAP_CM_RGN_CTRL_NUM];		///< region data
	vpq_hwrap_cm_regionctrl_b0_t gain[VPQ_HWRAP_CM_RGN_CTRL_NUM];	///< region gain
	vpq_hwrap_cm_clear_white_t clear_white;							///< clear white
	UINT32 sat_gain_lut_x[9];										///<dynamic sturation gainLUT_x
	UINT32 sat_gain_lut_y[9];										///<dynamic sturation gainLUT_y
} vpq_hwrap_cm_init_exp_color_t;	// CHIP_CM_INIT_EXP_COLOR_T

typedef struct
{
	vpq_hwrap_cm_regionctrl_b0_t gain;	///< region gain
	SINT32 hue_offset;					///< hue offset
	SINT32 sat_offset;					///< saturation offset
	SINT32 val_offset;					///< value offset
} vpq_hwrap_cm_data_t;	// CHIP_CM_DATA_T

typedef struct
{
	SINT32 global_apl[VPQ_HWRAP_CM_GLOBAL_POINT];	// global_apl
	SINT32 local_apl[VPQ_HWRAP_CM_LOCAL_POINT];		// local_apl
	SINT32 cuv_gain_w;								// CURV white gain
	SINT32 cuv_gain_b;								// CURV black gain
	SINT32 n1p_trans_curv[VPQ_HWRAP_CM_FREE_POINT][VPQ_HWRAP_CM_LOCAL_CURVE];	// n1p_trans_curv
	SINT32 n2p_trans_curv[VPQ_HWRAP_CM_FREE_POINT][VPQ_HWRAP_CM_LOCAL_CURVE];	// n2p_trans_curv
	SINT32 n3p_trans_curv[VPQ_HWRAP_CM_FREE_POINT][VPQ_HWRAP_CM_LOCAL_CURVE];	// n3p_trans_curv
	SINT32 n4p_trans_curv[VPQ_HWRAP_CM_FREE_POINT][VPQ_HWRAP_CM_LOCAL_CURVE];	// n4p_trans_curv
} vpq_hwrap_chip_dc2p_localcontrast_table_t;

typedef struct
{
	SINT32 global_apl[VPQ_HWRAP_CM_GLOBAL_POINT];	// global_apl
	SINT32 local_apl[VPQ_HWRAP_CM_LOCAL_POINT];		// local_apl
	SINT32 cuv_gain_w;								// CURV white gain
	SINT32 cuv_gain_b;								// CURV black gain
	SINT32 n1p_trans_curv[VPQ_HWRAP_CM_FREE_POINT][VPQ_HWRAP_CM_LOCAL_CURVE_O26];	// n1p_trans_curv
	SINT32 n2p_trans_curv[VPQ_HWRAP_CM_FREE_POINT][VPQ_HWRAP_CM_LOCAL_CURVE_O26];	// n2p_trans_curv
	SINT32 n3p_trans_curv[VPQ_HWRAP_CM_FREE_POINT][VPQ_HWRAP_CM_LOCAL_CURVE_O26];	// n3p_trans_curv
	SINT32 n4p_trans_curv[VPQ_HWRAP_CM_FREE_POINT][VPQ_HWRAP_CM_LOCAL_CURVE_O26];	// n4p_trans_curv
} vpq_hwrap_chip_dc2p_localcontrast_table_o26_t;


typedef struct
{
    unsigned char object_relibility;
    unsigned short object_fg_apl;
    unsigned short object_fg_pel_num;
    unsigned short object_bg_apl;
    unsigned short object_bg_pel_num;
    unsigned char object_boxw2;
    unsigned char object_boxw1;
    unsigned char object_boxh2;
    unsigned char object_boxh1;
    unsigned short object_data00;
    unsigned short object_data01;
    unsigned short object_data02;
    unsigned short object_data03;
    unsigned short object_data04;
    unsigned short object_data05;
    unsigned short object_data06;
    unsigned short object_data07;
    unsigned short object_data08;
    unsigned short object_data09;
    unsigned short object_data10;
    unsigned short  object_data11;
    unsigned char face_relibility;
    unsigned short face_fg_apl;
    unsigned short face_fg_pel_num;
    unsigned short face_bg_apl;
    unsigned short face_bg_pel_num;
    unsigned char face_boxw2;
    unsigned char face_boxw1;
    unsigned char face_boxh2;
    unsigned char face_boxh1;
    unsigned short face_data00;
    unsigned short face_data01;
    unsigned short face_data02;
    unsigned short face_data03;
    unsigned short face_data04;
    unsigned short face_data05;
    unsigned short face_data06;
    unsigned short face_data07;
    unsigned short face_data08;
    unsigned short face_data09;
    unsigned short face_data10;
    unsigned short face_data11;

} vpq_hwrap_obc_data_t;
typedef struct
{
	unsigned short head_apl;
	unsigned short body_apl;
} vpq_hwrap_obc_data_e60_t;

typedef struct
{
	unsigned short head_apl;
	unsigned short body_apl;
	unsigned short head_map_apl;
	unsigned short depth_map_apl;
} vpq_hwrap_obc_data_o22_t;

typedef struct
{
	UINT8 saturation_cr_mode; 						///< low saturation_cr_mode
	UINT32 saturation_region_gain; 					///< saturation_region_gainposition
	UINT32 dse_h_x[VPQ_HWRAP_CM_TBLPOINT];				///< hue x_range_max
	UINT32 dse_h_y[VPQ_HWRAP_CM_TBLPOINT];				///< hue y_range_min
	UINT32 dse_y_x[VPQ_HWRAP_CM_TBLPOINT];				///< Y x_range_max
	UINT32 dse_y_y[VPQ_HWRAP_CM_TBLPOINT];				///< Y y_range_min
	UINT32 sSaturationLUT_x[VPQ_HWRAP_NUM_TRANSCURVE];	///< sSaturationLUT
	UINT32 sSaturationLUT_y[VPQ_HWRAP_NUM_TRANSCURVE];	///< sSaturationLUT
	UINT8  region_onoff[VPQ_HWRAP_CM_RGN_CTRL_NUM];		///< region_onoff
	UINT8  chroma_gain_en;							///< chroma_gain_en
	UINT32 dce_chr_gain1;							///< dce_chr_gain1
	UINT32 dce_chr_gain2;							///< dce_chr_gain2
	UINT32 dce_chr_alpha1;							///< dce_chr_alpha1
	UINT32 dce_chr_alpha2;							///< dce_chr_alpha2
} vpq_hwrap_dc_dc_saturation2_t;

typedef struct
{
	UINT32 sc_map_sel;			///< 0x0:MAX(e,t map),0x1:t map,0x2:e map
	UINT32 sc_amap_filter_tap;	///< amap, 0x0~0x3 : 5,7,9,15-tap
	UINT32 amap_gain;			///< e map gain:(2.3u)0x0=0 ~ 0x8=1.0 ~ 0x1F=3.99x
	UINT32 tmap_gain;			///< t map gain:(2.3u)0x0=0 ~ 0x8=1.0 ~ 0x1F=3.99x
	UINT32 e_to_w_th_x0;		///< edge to weight : x0
	UINT32 e_to_w_th_x1;		///< edge to weight : x1
	UINT32 e_to_w_th_y0;		///< edge to weight : y0
	UINT32 e_to_w_th_y1;		///< edge to weight : y1
	UINT32 blur_v_gain;			///< 0x0 : blur V <-> 0xF : original V
} vpq_hwrap_dc_dce_smoothv1_t;

typedef struct
{
	UINT32 dce_bypass_gain;			///< dce out gain, 1(0%)~128(200%)~255(400%) (forbidden 0)
	UINT8 region_onoff[VPQ_HWRAP_CM_RGN_CTRL_NUM];	///< color region apply for dce y
	UINT32 color_region_en;			///< color region apply for dce y
	UINT32 y_grad_gain;				///< Gradient of Y  signal,0x0:128to0, 0x1:64to0, 0x2:32to0, 0x3:16to0
	UINT32 cb_grad_gain;			///< Gradient of Cb signal,0x0:128to0, 0x1:64to0, 0x2:32to0, 0x3:16to0
	UINT32 cr_grad_gain;			///< Gradient of Cr signal,0x0:128to0, 0x1:64to0, 0x2:32to0, 0x3:16to0
	UINT32 y_range_min;				///< y_range_min : 0~1023
	UINT32 y_range_max;				///< y_range_max : 0~1023
	UINT32 cb_range_min;			///< cb_range_min : 0~1023
	UINT32 cb_range_max;			///< cb_range_max : 0~1023
	UINT32 cr_range_min;			///< cr_range_min : 0~1023
	UINT32 cr_range_max;			///< cr_range_max : 0~1023
} vpq_hwrap_dc_desaturation_t;

typedef struct
{
	unsigned char  chroma_gain_en;
	unsigned short chroma_chr_gain1;
	unsigned short chroma_chr_gain2;
	unsigned short chroma_chr_alpha1;
	unsigned short chroma_chr_alpha2;
	unsigned short picture_mode;
	unsigned char  dtm_hue_gain; ///< 0~255
	unsigned char  dtm_sat_gain; ///< 0~255
} vpq_hwrap_dc_dynamic_t;

typedef struct
{
	unsigned char  chroma_gain_en;
	unsigned short chroma_cb_gain1;
	unsigned short chroma_cb_gain2;
	unsigned short chroma_cr_gain1;
	unsigned short chroma_cr_gain2;
	unsigned short chroma_alpha1;
	unsigned short chroma_alpha2;
	unsigned short picture_mode;
	unsigned char  dtm_hue_gain; ///< 0~255
	unsigned char  dtm_sat_gain; ///< 0~255
} vpq_hwrap_dc_dynamic_webos60_t;

typedef struct
{
	unsigned char  chroma_gain_en;
	unsigned short chroma_cb_gain1;
	unsigned short chroma_cb_gain2;
	unsigned short chroma_cr_gain1;
	unsigned short chroma_cr_gain2;
	unsigned short chroma_alpha1;
	unsigned short chroma_alpha2;
	unsigned short picture_mode;
	unsigned char  dtm_hue_gain; ///< 0~255
	unsigned char  dtm_sat_gain; ///< 0~255
	unsigned char  luma_gain_x[4]; //추가  
 	unsigned char  luma_gain_y[4]; //추가
 	unsigned char  sat_gain_x[4]; //추가
 	unsigned char  sat_gain_y[4]; //추가
} vpq_hwrap_dc_dynamic_weboso22_t;

typedef struct
{
	unsigned char  chroma_gain_en;
	unsigned short chroma_cb_gain1;
	unsigned short chroma_cb_gain2;
	unsigned short chroma_cr_gain1;
	unsigned short chroma_cr_gain2;
	unsigned short chroma_alpha1;
	unsigned short chroma_alpha2;
	unsigned short picture_mode;
	unsigned char  dtm_hue_gain; ///< 0~255
	unsigned char  dtm_sat_gain; ///< 0~255
	unsigned char  dtm_target_hue_gain; ///추가
	unsigned char  dtm_target_sat_gain; ///추가
	unsigned char  luma_gain_x[8]; // 4->8
 	unsigned char  luma_gain_y[8]; // 4->8
 	unsigned char  sat_gain_x[8]; // 4->8
 	unsigned char  sat_gain_y[8]; // 4->8
	unsigned char  dtm_hue_gain_x[10]; ///추가
 	unsigned char  dtm_hue_gain_y[8]; ///추가
 	unsigned char  dtm_sat_gain_x[8]; ///추가
 	unsigned char  dtm_sat_gain_y[8]; ///추가
 	unsigned char  dtm_val_gain_x[8]; ///추가
 	unsigned char  dtm_val_gain_y[8]; ///추가
} vpq_hwrap_dc_dynamic_weboso26_t;


typedef struct
{
	unsigned short uDcVal;
	vpq_hwrap_dc_dynamic_t pstDynamicContrast;
} vpq_hwrap_dynamic_contrast_t;

typedef struct
{
	UINT32 wId;
	SINT32 nColorGain;
} vpq_hwrap_dc_color_gain_t;

typedef struct {
 BOOLEAN		filmMode;
 unsigned char	*chip_data;
} vpq_hwrap_real_cinema_t;

typedef struct
{
	SINT32 pre_norm;						///pre normal IIR filter
	SINT32 cur_norm;						///current normal IIR filter
	SINT32 pre_sc;							///pre scene change IIR filter
	SINT32 cur_sc;							///current scene change IIR filter
	SINT32 ui_gain_w;						///UI white gain
	SINT32 ui_gain_b;						///UI black gain
	SINT32 vy_mode;							///V_Y_mode
} vpq_hwrap_chip_dc2p_drc_cont_t;

/******
*** webos22
*********/
typedef struct
{
	SINT32 pre_norm;						///pre normal IIR filter
	SINT32 cur_norm;						///current normal IIR filter
	SINT32 pre_sc;							///pre scene change IIR filter
	SINT32 cur_sc;							///current scene change IIR filter
	SINT32 ui_gain_w;						///UI white gain
	SINT32 ui_gain_b;						///UI black gain
	SINT32 vy_mode;							///V_Y_mode
	unsigned short nApl_lut_x[4]; //추가 
	unsigned short nApl_lut_y[4]; //추가 
	unsigned short nTxt_lut_x[4]; //추가
	unsigned short nTxt_lut_y[4]; //추가
	unsigned short nDark_lut_x[4]; //추가 
	unsigned short nDark_lut_y[4]; //추가 
	unsigned short nBright_lut_x[4]; //추가 
	unsigned short nBright_lut_y[4]; //추가 
} vpq_hwrap_chip_dc2p_drc_cont_weboso22_t;

/******
*** webos23
*********/
typedef struct vpq_hwrap_chip_dc2p_drc_cont_weboso23_t {
	int ui_mode_loc; // DC UI(0~3) or EE UI (0~2)
    int pre_norm;
    int cur_norm;
    int pre_sc;
    int cur_sc;
    int ui_gain_w;
    int ui_gain_b;
    int vy_mode;
    unsigned short nApl_lut_x[4];
    unsigned short nApl_lut_y[4];
    unsigned short nTxt_lut_x[4];
    unsigned short nTxt_lut_y[4];
    unsigned short nDark_lut_x[4];
    unsigned short nDark_lut_y[4];
    unsigned short nBright_lut_x[4];
    unsigned short nBright_lut_y[4];
    unsigned short nHead_lut_x[4];
    unsigned short nHead_lut_y[4];
    unsigned short nBody_lut_x[4];
    unsigned short nBody_lut_y[4];
    unsigned short nText_lut_x[4];
    unsigned short nText_lut_y[4];
} vpq_hwrap_chip_dc2p_drc_cont_weboso23_t;

/******
*** webos26
*********/
typedef struct vpq_hwrap_chip_dc2p_drc_cont_weboso26_t {
	int ui_mode_loc; // DC UI(0~3) or EE UI (0~2)
    int pre_norm;
    int cur_norm;
    int pre_sc;
    int cur_sc;
    int ui_gain_w;
    int ui_gain_b;
    int vy_mode;
    unsigned short nApl_lut_x[4];
    unsigned short nApl_lut_y[4];
    unsigned short nTxt_lut_x[8];// 4 -> 8
    unsigned short nTxt_lut_y[8];// 4 -> 8
    unsigned short nDark_lut_x[4];
    unsigned short nDark_lut_y[4];
    unsigned short nBright_lut_x[4];
    unsigned short nBright_lut_y[4];
    unsigned short nHead_lut_x[4];
    unsigned short nHead_lut_y[4];
    unsigned short nBody_lut_x[4];
    unsigned short nBody_lut_y[4];
    unsigned short nText_lut_x[4];
    unsigned short nText_lut_y[4];
    int y_ma_sel;					//new
	int t_ma_sel;					//new
	unsigned short bapp_y_lut_x[4]; //new
	unsigned short bapp_y_lut_y[4]; //new
	unsigned short bapp_t_lut_x[4]; //new
	unsigned short bapp_t_lut_y[4]; //new
} vpq_hwrap_chip_dc2p_drc_cont_weboso26_t;

typedef struct
{
	UINT8  iir_en;						//uIIREnBit
	UINT8  psp_en;						//uPspEnBit
	UINT8  chroma_protection_en;		//uChrmProtectEnBit
	UINT8  map_master_gain; 			//uMapGain
	UINT8  iir_gain;					//uIIRGain
	UINT16 cb_offset_gain;				//uCbOffset
	UINT16 cr_offset_gain;				//uCrOffset
	UINT8  position_lut_x[16];			//0~255, uPerspectiveLUT_x
	UINT8  position_lut_y[16];			//0~255 uPerspectiveLUT_y
	UINT16 psp_lut_x[17];				//0~1024 uLumaLUT_x
	UINT16 psp_lut_y[17];				//0~1024 uLumaLUT_y
} vpq_hwrap_chip_perspective_t;

typedef struct
{
    unsigned short object_fg_x[8];
    unsigned short object_fg_y[8];
    unsigned short object_bg_x[8];
    unsigned short object_bg_y[8];
} vpq_hwrap_obc_lut_t;

typedef struct
{
	unsigned short object_fg_x[8];
	unsigned short object_fg_y[8];
	unsigned short object_bg_x[8];
	unsigned short object_bg_y[8];
	unsigned short face_fg_x[8];
	unsigned short face_fg_y[8];
	unsigned short face_bg_x[8];
	unsigned short face_bg_y[8];
} vpq_hwrap_obc_lut_o20_t;

typedef struct
{
	unsigned short head_g_lut_x[6];
	unsigned short head_g_lut_y[6];
	unsigned short head_b_lut_x[6];
	unsigned short head_b_lut_y[6];
	unsigned short head_r_lut_x[6];
	unsigned short head_r_lut_y[6];
	unsigned short body_g_lut_x[6];
	unsigned short body_g_lut_y[6];
	unsigned short body_b_lut_x[6];
	unsigned short body_b_lut_y[6];
	unsigned short body_r_lut_x[6];
	unsigned short body_r_lut_y[6];
} vpq_hwrap_obc_lut_e60_o22_t;

typedef struct
{
	unsigned char obj_fg_gain_x[2];
	unsigned char obj_fg_gain_y[2];
	unsigned char obj_bg_gain_x[2];
	unsigned char obj_bg_gain_y[2];
	unsigned char obj_sat_enable;
	unsigned char obj_ch_bst_enable;
	unsigned short obj_yy_lut_pts_x[4];
	unsigned char obj_yy_lut_pts_y[4];
	unsigned char obj_cc_lut_pts_x[4];
	unsigned char obj_cc_lut_pts_y[4];
	unsigned char obj_cbst_lut_pts_x[4];
	unsigned char obj_cbst_lut_pts_y[4];
	unsigned char face_fg_gain_x[2];
	unsigned char face_fg_gain_y[2];
	unsigned char face_bg_gain_x[2];
	unsigned char face_bg_gain_y[2];
	unsigned char face_sat_enable;
	unsigned char face_ch_bst_enable;
	unsigned short face_yy_lut_pts_x[4];
	unsigned char face_yy_lut_pts_y[4];
	unsigned char face_cc_lut_pts_x[4];
	unsigned char face_cc_lut_pts_y[4];
	unsigned char face_cbst_lut_pts_x[4];
	unsigned char face_cbst_lut_pts_y[4];
	unsigned char face_obj_lut_x[4];
	unsigned char face_obj_lut_y[4];
	unsigned char obj_face_lut_x[4];
	unsigned char obj_face_lut_y[4];
} vpq_hwrap_obc_ctrl_o20_t;
typedef struct
{
	unsigned char head_gain_x[2];
	unsigned char head_gain_y[2];
	unsigned char body_gain_x[2];
	unsigned char body_gain_y[2];
} vpq_hwrap_obc_ctrl_e60_t;

typedef struct
{
	unsigned char head_gain_x[4];
	unsigned char head_gain_y[4];
	unsigned char body_gain_x[4];
	unsigned char body_gain_y[4];
} vpq_hwrap_obc_ctrl_o22_t;

typedef struct
{
	UINT8  obj_fg_gain_x[2];
	UINT8  obj_fg_gain_y[2];
	UINT8  obj_bg_gain_x[2];
	UINT8  obj_bg_gain_y[2];
	UINT8  obj_sat_enable;
	UINT8  obj_ch_bst_enable;
	UINT16 obj_yy_lut_pts_x[4];
	UINT8  obj_yy_lut_pts_y[4];
	UINT8  obj_cc_lut_pts_x[4];
	UINT8  obj_cc_lut_pts_y[4];
	UINT8  obj_cbst_lut_pts_x[4];
	UINT8  obj_cbst_lut_pts_y[4];
	UINT8  face_fg_gain_x[2];
	UINT8  face_fg_gain_y[2];
	UINT8  face_bg_gain_x[2];
	UINT8  face_bg_gain_y[2];
	UINT8  face_sat_enable;
	UINT8  face_ch_bst_enable;
	UINT16 face_yy_lut_pts_x[4];
	UINT8  face_yy_lut_pts_y[4];
	UINT8  face_cc_lut_pts_x[4];
	UINT8  face_cc_lut_pts_y[4];
	UINT8  face_cbst_lut_pts_x[4];
	UINT8  face_cbst_lut_pts_y[4];
	UINT8  face_obj_lut_x[4];
	UINT8  face_obj_lut_y[4];
	UINT8  obj_face_lut_x[4];
	UINT8  obj_face_lut_y[4];
} vpq_hwrap_obc_ctrl_t;

typedef struct
{
	UINT32 sLumaLutY[16];
	UINT32 sLumaLutX[16];
	UINT16 dtm_lut[66]; ///<0~1023, 33point x,y data
} vpq_hwrap_dynamic_lut_t;

typedef struct
{
	UINT32 sLumaLutY[32];// from webos6.0 size 16 -> 32
	UINT32 sLumaLutX[32];// from webos6.0 size 16 -> 32
	UINT16 dtm_lut[66]; ///<0~1023, 33point x,y data
	UINT16 chroma_face_alpha_lut1_x[4];
	UINT16 chroma_face_alpha_lut1_y[4];
	UINT16 chroma_face_alpha_lut2_x[4];
	UINT16 chroma_face_alpha_lut2_y[4];
} vpq_hwrap_dynamic_lut_webos60_t;

typedef struct
{
	UINT32 sLumaLutY[32];// from webos6.0 size 16 -> 32
	UINT32 sLumaLutX[32];// from webos6.0 size 16 -> 32
	UINT16 chroma_face_alpha_lut1_x[4];
	UINT16 chroma_face_alpha_lut1_y[4];
	UINT16 chroma_face_alpha_lut2_x[4];
	UINT16 chroma_face_alpha_lut2_y[4];
} vpq_hwrap_dynamic_lut_pioneer_t;


typedef struct pqdb_dc_db_f20
{
	union {
        	unsigned char *pAddrData;
        	unsigned int compat_data;
        	unsigned long long sizer;
   	 };
	unsigned int sizeOfItem;
	unsigned int lengthOfData;
	unsigned int sizeOfData;
} vpq_hwrap_dc_db_t;

typedef struct {
	vpq_hwrap_dc_db_t dynContDB;
	vpq_hwrap_dc_db_t aplDB;
	vpq_hwrap_dc_db_t aiGainDB;
	vpq_hwrap_dc_db_t stabilzerDB;
	UINT32 contrast_gain[17]; // added since f22 210915
}vpq_hwrap_dc_db_all_t;


typedef struct {
	UINT16 input_freq[VPQ_HWRAP_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
	UINT16 contrast_gain[VPQ_HWRAP_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
	UINT16 brightness_gain[VPQ_HWRAP_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE];
}vpq_hwrap_dbc_db_t;

typedef struct
{
	UINT32 sLumaLutY[32];
	UINT32 sLumaLutX[32];
	UINT16 dtm_lut[66]; 
	UINT16 chroma_face_alpha_lut1_x[4];
	UINT16 chroma_face_alpha_lut1_y[4];
	UINT16 chroma_face_alpha_lut2_x[4];
	UINT16 chroma_face_alpha_lut2_y[4];
	UINT8  shp_luma_ylut_2k[16]; // added SICREQ-529
	UINT8  shp_luma_ylut_vsd[16]; // added SICREQ-529
} vpq_hwrap_dynamic_lut_o24_t;

typedef struct
{
	UINT32 sLumaLutY[4][32];
	UINT32 sLumaLutX[4][32];
	UINT16 dtm_lut[66]; 
	UINT16 chroma_face_alpha_lut1_x[4];
	UINT16 chroma_face_alpha_lut1_y[4];
	UINT16 chroma_face_alpha_lut2_x[4];
	UINT16 chroma_face_alpha_lut2_y[4];
	UINT8  shp_luma_ylut_2k[16]; // added SICREQ-529
	UINT8  shp_luma_ylut_vsd[16]; // added SICREQ-529
} vpq_hwrap_dynamic_lut_o24_v2_t;


#define VPQ_HWRAP_MAX_EXT_PATTERN_GRADATION_LINE (4)		// it depends on chip limitation
#define VPQ_HWRAP_MAX_EXT_PATTERN_WINBOX (10)				// it depends on chip limitation
#define VPQ_HWRAP_MAX_EXT_PATTERN_GRADATION_H_STRIDE_SIZE (254)				// it depends on chip limitation
#define VPQ_HWRAP_EXT_PATTERN_GRADATION_H_STRIDE_STEP (2)				// it depends on chip limitation
#define VPQ_HWRAP_MAX_EXT_PATTERN_GRADATION_V_STRIDE_SIZE (127)				// it depends on chip limitation
#define VPQ_HWRAP_EXT_PATTERN_GRADATION_V_STRIDE_STEP (1)				// it depends on chip limitation
#define VPQ_HWRAP_EXT_PATTERN_WIDTH (3840)				// it depends on chip limitation
#define VPQ_HWRAP_EXT_PATTERN_HEIGHT (2160)				// it depends on chip limitation

typedef enum {
	VPQ_HWRAP_EXT_PATTERN_WINBOX,
	VPQ_HWRAP_EXT_PATTERN_GRADATION,
} vpq_hwrap_ext_pattern_mode_t;

typedef enum {
	VPQ_HWRAP_EXT_PATTERN_GRADATION_DIRECTION_HORIZONTAL,
	VPQ_HWRAP_EXT_PATTERN_GRADATION_DIRECTION_VERTICAL,
	VPQ_HWRAP_EXT_PATTERN_GRADATION_DIRECTION_MAX
} vpq_hwrap_ext_pattern_gradation_direction_t;

typedef struct {
	UINT8 lineIdx;		// gradation line index
	UINT16 start_R;		// 1st gradation block's red level as a 10bit resolution
	UINT16 start_G;		// 1st gradation block's green level as a 10bit resolution
	UINT16 start_B;		// 1st gradation block's blue level as a 10bit resolution
	UINT16 step_R;		// step size for next gradation block
	UINT16 step_G;		// step size for next gradation block
	UINT16 step_B;		// step size for next gradation block
	UINT16 strideSize;	// gradation block's width(horizontal mode)/height(vertical mode)
} vpq_hwrap_ext_pattern_gradation_line_attr_t;

typedef struct {
	UINT8 numGrad;	// number of gradation lines in a screen
	vpq_hwrap_ext_pattern_gradation_direction_t eGradMode;
	vpq_hwrap_ext_pattern_gradation_line_attr_t stLineAttr[MAX_EXT_PATTERN_GRADATION_LINE];
} vpq_hwrap_ext_pattern_gradation_info_t;

typedef struct {
	UINT8 winIdx;	// window layer index. 0:background(bottom layer), ... , 10?:top layer	
	UINT16 x;
	UINT16 y;
	UINT16 w;
	UINT16 h;
	UINT16 fill_R;  // 10 bit resolution
	UINT16 fill_G;  // 10 bit resolution
	UINT16 fill_B;  // 10 bit resolution
} vpq_hwrap_ext_pattern_winbox_window_attr_t;


typedef struct {
	UINT8 u8NumWin;	// number of windows in a screen(including background window)	  
	vpq_hwrap_ext_pattern_winbox_window_attr_t stWinBoxAttr[MAX_EXT_PATTERN_WINBOX];
} vpq_hwrap_ext_pattern_winbox_info_t;

typedef struct {
	BOOLEAN bOnOff;
	vpq_hwrap_ext_pattern_mode_t eMode;
    union {
        unsigned char *pstGradInfo;
        unsigned int grad_compat_data;
        unsigned long long grad_sizer;
    };
    union {
        unsigned char *pstWinboxInfo;
        unsigned int winbox_compat_data;
        unsigned long long winbox_sizer;
    };
} vpq_hwrap_ext_pattern_info_t;

struct vpq_hwrap_ext_pattern_info {
    unsigned char bOnOff;
    enum V4L2_VPQ_EXT_PATTERN_MODE eMode;
    struct v4l2_vpq_ext_pattern_gradation_info stGradInfo;
    struct v4l2_vpq_ext_pattern_winbox_info stWinboxInfo;
};

typedef struct {
    unsigned int apl;                              ///< apl
    signed int min;                                ///< min
    signed int max;                                ///< max
    signed int peak_low;                           ///< peak low
    signed int peak_high;                          ///< peak high
    unsigned int skin_count;                       ///< skin count
    unsigned int sat_status;                       ///< saturation status
    unsigned int diff_sum;                         ///< diff sum
    unsigned int motion;                           ///< motion
    unsigned int texture;                          ///< texture
    unsigned int bin[128];        ///< count bin
    unsigned int chrm_bin[32]; ///< count chroma bin
    unsigned int hue_bin[32];  ///< count chroma bin
}vpq_hwrap_ext_histodata_info;

typedef enum
{
	VPQ_HWRAP_NRD_OFF = 0,	///< off
	VPQ_HWRAP_NRD_LOW,		///< low
	VPQ_HWRAP_NRD_MED,		///< medium
	VPQ_HWRAP_NRD_HGH,		///< high
	VPQ_HWRAP_NRD_ATO,		///< auto
	VPQ_HWRAP_NRD_NUM			///< max num
}vpq_hwrap_nrd_type;

typedef enum
{
	VPQ_HWRAP_CMG_RGN_V00 = 0,	///< type 0
	VPQ_HWRAP_CMG_RGN_V01,		///< type 1
	VPQ_HWRAP_CMG_RGN_NUM			///< max num
}
vpq_hwrap_cmg_rgn_type;
typedef enum
{
	VPQ_HWRAP_CMG_RGN_COL_WHT = 0,	///< white
	VPQ_HWRAP_CMG_RGN_COL_WTB,		///< white blue
	VPQ_HWRAP_CMG_RGN_COL_BLK,		///< black
	VPQ_HWRAP_CMG_RGN_COL_SKN,		///< skin
	VPQ_HWRAP_CMG_RGN_COL_GRN,		///< green
	VPQ_HWRAP_CMG_RGN_COL_BLU,		///< blue
	VPQ_HWRAP_CMG_RGN_COL_RED,		///< red
	VPQ_HWRAP_CMG_RGN_COL_YEL,		///< yellow
	VPQ_HWRAP_CMG_RGN_COL_MGT,		///< magenta
	VPQ_HWRAP_CMG_RGN_COL_CYN,		///< cyan
	VPQ_HWRAP_CMG_RGN_COL_R10,		///< reserved region 10th
	VPQ_HWRAP_CMG_RGN_COL_R11,		///< reserved region 11th
	VPQ_HWRAP_CMG_RGN_COL_R12,		///< reserved region 12th
	VPQ_HWRAP_CMG_RGN_COL_R13,		///< reserved region 13th
	VPQ_HWRAP_CMG_RGN_COL_R14,		///< reserved region 14th
	VPQ_HWRAP_CMG_RGN_COL_R15,		///< reserved region 15th
	VPQ_HWRAP_CMG_RGN_COL_NUM			///< max num
}
vpq_kwrap_cmg_rgn_col_type;

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/
extern int vpq_hwrap_setpicturectrl(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_getpicturectrl(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_setblacklevelenable(int enable);
extern int vpq_hwrap_getblacklevelenable(void);
extern int vpq_hwrap_getblackleveltype(UINT32 wId);
extern int vpq_hwrap_setblacklevel(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_setblacklevel2(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_gethistodata(struct v4l2_ext_vpq_cmn_data *p_param);
extern int vpq_hwrap_getnoiselevel(UINT16 *uLevel);
extern int vpq_hwrap_setsharpness(vpq_hwrap_shp_t *pShpData, UINT32 wId, unsigned int version);
extern int vpq_hwrap_setnoisereduction(vpq_hwrap_nr_t *pNrData, UINT32 wId, unsigned int ver);
extern int vpq_hwrap_setmpegnoisereduction(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId, unsigned int ver);
//extern int vpq_hwrap_setmpegnoisereduction_m19(vpq_hwrap_mpeg_nr_t *pMpegNrData);
//extern int vpq_hwrap_setmpegnoisereduction_o20(vpq_hwrap_mpeg_nr_t *pMpegNrData);
extern int vpq_hwrap_setsuperresoulution(vpq_hwrap_sr_t *pSrData);
extern int vpq_hwrap_setdecontour(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId, unsigned int ver);
//extern int vpq_hwrap_setdecontour_m19(vpq_hwrap_decontour_t *pDecontourData);
//extern int vpq_hwrap_setdecontour_o20(vpq_hwrap_decontour_t *pDecontourData);
extern int vpq_hwrap_setcmdbdata(unsigned char wId, struct v4l2_ext_cm_info *pCmInfo, int version);
extern int vpq_hwrap_setdynamiccontrast(struct v4l2_ext_dynamnic_contrast_ctrl *pDynamicContrast);
extern int vpq_hwrap_setdynamiccontrast_webos60(struct v4l2_ext_dynamnic_contrast_ctrl *pDynamicContrast);
extern int vpq_hwrap_setdynamiccontrast_weboso22(struct v4l2_ext_dynamnic_contrast_ctrl *pDynamicContrast);
extern int vpq_hwrap_setdynamiccontrast_weboso26(struct v4l2_ext_dynamnic_contrast_ctrl *pDynamicContrast);
extern int vpq_hwrap_getshpdbenalbe(void);
extern int vpq_hwrap_gettnrdbenalbe(void);
extern int vpq_hwrap_getdnrdbenalbe(void);
extern int vpq_hwrap_getdctdbenalbe(void);
extern void vpq_hwrap_toggleshpdbenalbe(void);
extern void vpq_hwrap_toggletnrdbenalbe(void);
extern void vpq_hwrap_togglednrdbenalbe(void);
extern void vpq_hwrap_toggledctdbenalbe(void);
extern void vpq_hwrap_pe_init(void);
extern void vpq_hwrap_setalldbenalbe(UINT32 onoff);
int vpq_hwrap_setnoisereduction_external(vpq_hwrap_nr_t *pNrData, UINT32 wId);
int vpq_hwrap_setmpegnoisereduction_external(vpq_hwrap_mpeg_nr_t *pMpegNrData, UINT32 wId);
int vpq_hwrap_setdecontour_external(vpq_hwrap_decontour_t *pDecontourData, UINT32 wId);
int vpq_hwrap_setsharpness_external(vpq_hwrap_shp_t *pShpData, UINT32 wId);
int vpq_hwrap_getcendbswich(void);
void vpq_hwrap_togglecendbswitch(void);
int vpq_hwrap_getpicturectrldbswich(void);
void vpq_hwrap_picturectrldbswitch(void);
extern vpq_hwrap_info_t vpq_hwrap_getvpq_hwrap_info(void);
extern int vpq_hwrap_updatecnt_icsc(UINT32 wId);
extern int vpq_hwrap_saveprecnt_icsc(UINT32 wId, int cnt);
extern vpq_hwrap_info_t vpq_hwrap_get_vpq_hwrap_info(void);
extern int vpq_hwrap_setpreblacklevel(UINT32 wId,int enable);
extern void vpq_hwrap_getnetonoff(UINT32 net_onoff);
extern int vpq_hwrap_gethistodata_o24(struct v4l2_ext_vpq_cmn_data *p_param);
extern void vpq_hwrap_switch_win_id(int winId);
extern int vpq_hwrap_setlocalcontrasttable(vpq_hwrap_chip_dc2p_localcontrast_table_t *plocaltable);
extern int vpq_hwrap_setlocalcontrasttable_o26(vpq_hwrap_chip_dc2p_localcontrast_table_o26_t *plocaltable);


#endif /* _VPQ_HWRAP_PE_H_ */
