/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_hdr_hw_m19.c
 *
 *  driver for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	- dynamic contrast enhancement, histogram information and configuration.
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.16
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_hw_m19.h"
#include "pe_reg_m19.h"
#include "pe_fwi_m19.h"
#include "pe_cmn_hw_m19.h"
#include "pe_hdr_hw_m19.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* hdr drv ver, yyyy/mm/dd/hh:mm */
#define PE_HDR_HW_M19_DRV_VER		"2019/04/09/13:19"

#define PE_HDR_HW_M19_BUF_MAX			100

#define PE_HDR_HW_M19_CONNECT_MODE_SDR	(0)
#define PE_HDR_HW_M19_CONNECT_MODE_H10	(1)
#define PE_HDR_HW_M19_CONNECT_MODE_HLG	(2)
#define PE_HDR_HW_M19_CONNECT_MODE_S2H	(3)
#define PE_HDR_HW_M19_CONNECT_MODE_TEC	(4)

#define PE_HDR_HW_M19_LUT_TYPE_A	(0xA)
#define PE_HDR_HW_M19_LUT_TYPE_B	(0xB)
#define PE_HDR_HW_M19_LUT_TYPE_C	(0xC)
#define PE_HDR_HW_M19_LUT_TYPE_D	(0xD)
#define PE_HDR_HW_M19_LUT_TYPE_E	(0xE)
#define PE_HDR_HW_M19_LUT_TYPE_F	(0xF)

/* will be moved to fw */
#undef PE_HDR_HW_M19_MOVE_TO_FW

/* 20170913, set hfr 4k hdr main,sub at the same time, using only main info */
#define PE_HDR_HW_M19_HFR_DUAL_SETTINGS

/* 20171110, enable color correction on SDR(SCDCR-1302) */
/* 20180827, adjust SDR(TVPQ-1069) */
/** HDR
* pInfo->reg_hue_prsv_en = 0x1;//fix
* pInfo->reg_sat_prsv_en = 0x1;//fix
* pInfo->reg_out_sgain_sel = 0x0;//20171117,TVPQ-708,1->0
* pInfo->reg_out_lgain_sel = 0x1;//20171117,TVPQ-708,0->1
* pInfo->reg_inp_s_sel = 0x1;//reg_inp_s_sel, 0->1, 20170905,TVPQ Req. 1->0, 20170920,TVPQ Req.//20171117,TVPQ-708,0->1
* pInfo->reg_inp_l_sel = 0x0;//fix */
/** SDR
* pInfo->reg_hue_prsv_en = 0x1;//fix
* pInfo->reg_sat_prsv_en = 0x1;//fix
* pInfo->reg_out_sgain_sel = 0x1;//20180827,TVPQ-1069,0->1
* pInfo->reg_out_lgain_sel = 0x0;//20180827,TVPQ-1069,1->0
* pInfo->reg_inp_s_sel = 0x1;
* pInfo->reg_inp_l_sel = 0x0;//fix */
#define PE_HDR_HW_M19_EN_CC_SDR

/* 20180504, WA Rd Lut(indirect) */
#define PE_HDR_HW_M19_WA_RD_LUT

/* 20180716, WA for overflow(dot noise) when dither off(SDMSTG-403)(SICDTV-5168) */
/* "dither off" -> "dither on +  bit mode bypass" */
/* "dither on" -> "dither on +  bit mode 10bit" */
#define PE_HDR_HW_M19_DITEHER_BY_BIT_MODE

/* 20181204, mode info sync with main (self test) */
#define PE_HDR_HW_M19_MODE_INFO_SYNC_WITH_MAIN

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_HDR_HW_M19_ERROR	printk

#define PE_HDR_HW_M19_DBG_PRINT(fmt,args...)	\
	if(_g_hdr_hw_m19_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)

#define PE_HDR_HW_M19_CHECK_CODE(_checker,_action,fmt,args...) \
	{if(_checker){PE_HDR_HW_M19_ERROR(fmt,##args);_action;}}

#define PE_HDR_HW_M19_MAX(x, y, z)	\
	(((x)>=(y))? (((z)>=(x))? (z):(x)):(((z)>=(y))? (z):(y)))
#define PE_HDR_HW_M19_MIN(x, y, z)	\
	(((x)<=(y))? (((z)<=(x))? (z):(x)):(((z)<=(y))? (z):(y)))

#define PE_HDR_HW_M19_BACKUP_TRACE(_fmt, args...)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_HDR_HW_M19_SetTraceDataBuf(_str_buf);\
	}

#define PE_HDR_HW_M19_CONNECT_TO_STR(_x)		(\
	((_x)==PE_HDR_HW_M19_CONNECT_MODE_SDR)?	"SDR":\
	((_x)==PE_HDR_HW_M19_CONNECT_MODE_H10)?	"H10":\
	((_x)==PE_HDR_HW_M19_CONNECT_MODE_HLG)?	"HLG":\
	((_x)==PE_HDR_HW_M19_CONNECT_MODE_S2H)?	"S2H":\
	((_x)==PE_HDR_HW_M19_CONNECT_MODE_TEC)?	"TEC":\
	"MAX")

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe trace time type
 */
typedef struct {
	UINT32 sec;			///< sec
	UINT32 msec;		///< msec
	UINT32 usec;		///< usec
}
PE_HDR_HW_M19_TIME_T;

/**
 *	pe trace data buffer type
 */
typedef struct {
	PE_HDR_HW_M19_TIME_T time;		///< time
	char str[PE_TRACE_STR_SIZE];	///< str
}
PE_HDR_HW_M19_DATA_BUF_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void PE_HDR_HW_M19_SortTraceDataBuf(PE_HDR_HW_M19_DATA_BUF_T *dst);
static int PE_HDR_HW_M19_SetTraceDataBuf(char *data);
static UINT32 PE_HDR_HW_M19_GetConnectMode(UINT32 win_id);
static UINT32 PE_HDR_HW_M19_GetToneConnectMode(UINT32 path);
static UINT32 PE_HDR_HW_M19_GetToneOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_M19_IncreaseToneCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_M19_GetYlutOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_M19_IncreaseYlutCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_M19_GetEotfOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_M19_IncreaseEotfCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_M19_GetEotfCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_M19_GetOetfOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_M19_IncreaseOetfCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_M19_GetOetfCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_M19_Get3dLutOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_M19_Set3dLutCount(UINT32 win_id, UINT32 ofst, UINT32 indx);
static UINT32 PE_HDR_HW_M19_Get3dLutCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_M19_SetSupportInfo(UINT32 win_id, UINT32 info);
static int PE_HDR_HW_M19_InitHisto(PE_CFG_CTRL_T *pstParams);
static int PE_HDR_HW_M19_InitTonemapLut(PE_CFG_CTRL_T *pstParams);
static int PE_HDR_HW_M19_InitYgainLut(PE_CFG_CTRL_T *pstParams);
static int PE_HDR_HW_M19_SetCscReg(UINT32 win_id, UINT32 type);
static int PE_HDR_HW_M19_InitCsc(PE_CFG_CTRL_T *pstParams);
static int PE_HDR_HW_M19_InitHdrInfo(PE_CFG_CTRL_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_hdr_hw_m19_trace=0x0;	//default should be off.
static PE_HDR_HW_M19_SETTINGS_T _g_pe_hdr_hw_m19_info;
static PE_HDR_HW_M19_DATA_BUF_T *_gp_pe_hdr_hw_m19_buf_curr = NULL;
static PE_HDR_HW_M19_DATA_BUF_T *_gp_pe_hdr_hw_m19_buf_sort = NULL;

/* normal bypass */
const UINT32 _g_hdr_tm_lut_bypass_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x08000800,
	0x10001000,
	0x18001800,
	0x20002000,
	0x28002800,
	0x30003000,
	0x38003800,
	0x40004000,
	0x48004800,
	0x50005000,
	0x58005800,
	0x60006000,
	0x68006800,
	0x70007000,
	0x78007800,
	0x80008000,
	0x88008800,
	0x90009000,
	0x98009800,
	0xA000A000,
	0xA800A800,
	0xB000B000,
	0xB800B800,
	0xC000C000,
	0xC800C800,
	0xD000D000,
	0xD800D800,
	0xE000E000,
	0xE800E800,
	0xF000F000,
	0xF800F800,
	0xFFFFFFFF};

/* hdr10 x(2016) */
const UINT32 _g_hdr_tm_lut_x_data0_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x01F403F0,
	0x03E807E1,
	0x05DC0BD1,
	0x07D00FC1,
	0x09C413B2,
	0x0BB6179E,
	0x0C4D18CF,
	0x0CF61A23,
	0x1997339B,
	0x230746A4,
	0x2868517D,
	0x2E735DAD,
	0x353E6B60,
	0x3CE17AC6,
	0x45798C1B,
	0x4F259F9D,
	0x538EA882,
	0x571AAFA9,
	0x6098C2CD,
	0x672CD011,
	0x6C62DA8D,
	0x7433E7BF,
	0x7B0BF0C8,
	0x8248F880,
	0x88D0FDCC,
	0x93D3FE12,
	0xA3ABFE6E,
	0xBA77FEE4,
	0xCE82FF40,
	0xE021FF8A,
	0xF055FFC8,
	0xFFFFFFFF};
/* hdr10 y(2016) */
const UINT32 _g_hdr_tm_lut_y_data0_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x01F403F0,
	0x03E807E1,
	0x05DC0BD1,
	0x07D00FC1,
	0x09C413B2,
	0x0BB6179E,
	0x0C4D18CF,
	0x0CF61A23,
	0x1997339B,
	0x230746A4,
	0x2868517D,
	0x2E735DAD,
	0x353E6B60,
	0x3CE17AC6,
	0x45798C1B,
	0x4F259F9D,
	0x538EA882,
	0x571AAFA9,
	0x6098C2CD,
	0x672CD011,
	0x6C62DA8D,
	0x7433E7BF,
	0x7B0BF0C8,
	0x8248F880,
	0x88D0FDCC,
	0x93D3FE12,
	0xA3ABFE6E,
	0xBA77FEE4,
	0xCE82FF40,
	0xE021FF8A,
	0xF055FFC8,
	0xFFFFFFFF};

/* s2h bypass llut0,1 */
const UINT32 _g_hdr_tm_lut_data1_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x00400100,
	0x007701DC,
	0x00AE02B8,
	0x00E40390,
	0x011B046C,
	0x01520548,
	0x01890624,
	0x01C00700,
	0x01F607D8,
	0x022D08B4,
	0x02640990,
	0x029B0A6C,
	0x02D20B48,
	0x03080C20,
	0x033F0CFC,
	0x03650D94,
	0x03AC0EB0,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF,
	0x03FF0FFF};

/* s2h bypass llut2 */
const UINT32 _g_hdr_tm_lut_data2_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000003,
	0x000c000a,
	0x0018001b,
	0x00240038,
	0x00300058,
	0x003c0068,
	0x0048005e,
	0x00540044,
	0x0060002d,
	0x006c0023,
	0x00780022,
	0x0084001e,
	0x0090001b,
	0x009c0017,
	0x00a80014,
	0x00b40011,
	0x00c0000f,
	0x00cc000c,
	0x00d8000a,
	0x00e40009,
	0x00f00009,
	0x00fc0009,
	0x01080009,
	0x01140009,
	0x01200009,
	0x012c0009,
	0x01380009,
	0x01440009,
	0x01500006,
	0x015c0003,
	0x01670001,
	0x01670001,
	0x01670001};

/* s2h bypass llut0,1(m19,2017) */
const UINT32 _g_hdr_tm_lut_x_data1_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x00000040,
	0x00000077,
	0x000000AE,
	0x000000E4,
	0x0000011B,
	0x00000152,
	0x00000189,
	0x000001C0,
	0x000001F6,
	0x0000022D,
	0x00000264,
	0x0000029B,
	0x000002D2,
	0x00000308,
	0x0000033F,
	0x00000365,
	0x000003AC,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF,
	0x000003FF};
/* s2h bypass llut0,1(m19,2017) */
const UINT32 _g_hdr_tm_lut_y_data1_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x00000100,
	0x000001DC,
	0x000002B8,
	0x00000390,
	0x0000046C,
	0x00000548,
	0x00000624,
	0x00000700,
	0x000007D8,
	0x000008B4,
	0x00000990,
	0x00000A6C,
	0x00000B48,
	0x00000C20,
	0x00000CFC,
	0x00000D94,
	0x00000EB0,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF,
	0x00000FFF};
/* s2h bypass llut2(m19,2017) */
const UINT32 _g_hdr_tm_lut_x_data2_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x0000000c,
	0x00000018,
	0x00000024,
	0x00000030,
	0x0000003c,
	0x00000048,
	0x00000054,
	0x00000060,
	0x0000006c,
	0x00000078,
	0x00000084,
	0x00000090,
	0x0000009c,
	0x000000a8,
	0x000000b4,
	0x000000c0,
	0x000000cc,
	0x000000d8,
	0x000000e4,
	0x000000f0,
	0x000000fc,
	0x00000108,
	0x00000114,
	0x00000120,
	0x0000012c,
	0x00000138,
	0x00000144,
	0x00000150,
	0x0000015c,
	0x00000167,
	0x00000167,
	0x00000167};
/* s2h bypass llut2(m19,2017) */
const UINT32 _g_hdr_tm_lut_y_data2_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000003,
	0x0000000a,
	0x0000001b,
	0x00000038,
	0x00000058,
	0x00000068,
	0x0000005e,
	0x00000044,
	0x0000002d,
	0x00000023,
	0x00000022,
	0x0000001e,
	0x0000001b,
	0x00000017,
	0x00000014,
	0x00000011,
	0x0000000f,
	0x0000000c,
	0x0000000a,
	0x00000009,
	0x00000009,
	0x00000009,
	0x00000009,
	0x00000009,
	0x00000009,
	0x00000009,
	0x00000009,
	0x00000009,
	0x00000006,
	0x00000003,
	0x00000001,
	0x00000001,
	0x00000001};

/* hlg x(2017) */
const UINT32 _g_hdr_tm_lut_x_data3_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x08000800,
	0x10001000,
	0x18001800,
	0x20002000,
	0x28002800,
	0x30003000,
	0x38003800,
	0x40004000,
	0x48004800,
	0x50005000,
	0x58005800,
	0x60006000,
	0x68006800,
	0x70007000,
	0x78007800,
	0x80008000,
	0x88008800,
	0x90009000,
	0x98009800,
	0xA000A000,
	0xA800A800,
	0xB000B000,
	0xB800B800,
	0xC000C000,
	0xC800C800,
	0xD000D000,
	0xD800D800,
	0xE000E000,
	0xE800E800,
	0xF000F000,
	0xF800F800,
	0xFFFFFFFF};
/* hlg y(2017) */
const UINT32 _g_hdr_tm_lut_y_data3_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x00000C41,
	0x00001883,
	0x000024C4,
	0x00003105,
	0x00003D47,
	0x00004988,
	0x000055CA,
	0x0000620B,
	0x00006E4C,
	0x00007A8E,
	0x000086CF,
	0x00009310,
	0x00009FA4,
	0x0000AC34,
	0x0000B846,
	0x0000C3E2,
	0x0000CF0D,
	0x0000D9CE,
	0x0000E42C,
	0x0000EE2A,
	0x0000F7CF,
	0x0000FB54,
	0x0000FBE3,
	0x0000FC6B,
	0x0000FCED,
	0x0000FD6A,
	0x0000FDE3,
	0x0000FE57,
	0x0000FEC6,
	0x0000FF32,
	0x0000FF9A,
	0x0000FFFF};

/* h10 x(2017) */
const UINT32 _g_hdr_tm_lut_x_data4_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x000053D4,
	0x0000A7BE,
	0x0001F72C,
	0x0003469D,
	0x0004E9CF,
	0x00068D4C,
	0x0013A74E,
	0x0020C2E5,
	0x003468F9,
	0x004185B6,
	0x00830B87,
	0x00E5504D,
	0x01479CAB,
	0x01EB6BC1,
	0x028F37C1,
	0x03D6BD73,
	0x051E528E,
	0x06E9289A,
	0x08B3A224,
	0x0B846BA7,
	0x0DD24D2E,
	0x147A1418,
	0x199800E5,
	0x1EB63FBE,
	0x266450B1,
	0x2B832CAB,
	0x33312D7B,
	0x3ADEEC67,
	0x3FFD47EB,
	0x4CC7FEC6,
	0x6662BED4,
	0xFFFFFFFF};
/* h10 y(2017) */
const UINT32 _g_hdr_tm_lut_y_data4_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x00000004,
	0x00000007,
	0x00000016,
	0x00000024,
	0x00000036,
	0x00000048,
	0x000000D8,
	0x00000168,
	0x00000241,
	0x000002D1,
	0x000005A2,
	0x000009DB,
	0x00000E14,
	0x0000151E,
	0x00001C29,
	0x00002A3D,
	0x00003851,
	0x00004C08,
	0x00005FBE,
	0x00007EB8,
	0x00009810,
	0x0000E147,
	0x0000FEB7,
	0x0000FEBF,
	0x0000FECA,
	0x0000FED1,
	0x0000FEDC,
	0x0000FEE7,
	0x0000FEEE,
	0x0000FF00,
	0x0000FF25,
	0x0000FFFF};

/* h10 x(201801) */
const UINT32 _g_hdr_tm_lut_x_data5_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x00FF24B9,
	0x015DB7AF,
	0x024031D5,
	0x02D6C9DA,
	0x0369D71B,
	0x03E3F96C,
	0x0668F631,
	0x08160151,
	0x0A02D93D,
	0x0B14A0A9,
	0x0F2F2E53,
	0x1394F3CE,
	0x170770A6,
	0x1BB092FC,
	0x1F8EC994,
	0x25F16095,
	0x2B3E5708,
	0x31910832,
	0x370A3A4F,
	0x3E850C37,
	0x43EC6474,
	0x5135FD8C,
	0x59E065E1,
	0x61A432BC,
	0x6C1137A9,
	0x726549EC,
	0x7B2ADC72,
	0x833EEC41,
	0x8850A236,
	0x94168046,
	0xA8C8A38E,
	0xFFFFFFFF};
/* h10 y(201801) */
const UINT32 _g_hdr_tm_lut_y_data5_m19[PE_HDR_HW_M19_TM_LUT_MAX] = {
	0x00000000,
	0x00000259,
	0x00000338,
	0x0000054E,
	0x000006B1,
	0x0000080C,
	0x0000092C,
	0x00000F1C,
	0x0000130F,
	0x00001799,
	0x00001A1E,
	0x000023CA,
	0x00002E28,
	0x00003648,
	0x00004144,
	0x00004A62,
	0x0000596F,
	0x000065ED,
	0x000074D4,
	0x000081BB,
	0x0000935C,
	0x0000A019,
	0x0000BF6A,
	0x0000CCCC,
	0x0000D5C2,
	0x0000E147,
	0x0000E7AD,
	0x0000EF5B,
	0x0000F47A,
	0x0000F709,
	0x0000FC28,
	0x0000FEB7,
	0x0000FFFF};

/* normal bypass */
const UINT32 _g_hdr_yg_lut_bypass_m19[PE_HDR_HW_M19_YG_LUT_MAX] = {
	0x00000000,
	0x00150015,
	0x00550055,
	0x00C000C0,
	0x01560156,
	0x02160216,
	0x03010301,
	0x04170417,
	0x05580558,
	0x06C306C3,
	0x08590859,
	0x0A1A0A1A,
	0x0C060C06,
	0x0E1C0E1C,
	0x105D105D,
	0x12C912C9,
	0x15601560,
	0x184C184C,
	0x1BC81BC8,
	0x1FEF1FEF,
	0x24E024E0,
	0x2AC32AC3,
	0x31C731C7,
	0x3A223A22,
	0x44154415,
	0x4FEF4FEF,
	0x5E0E5E0E,
	0x6EDF6EDF,
	0x82E782E7,
	0x9AC49AC4,
	0xB730B730,
	0xD90BD90B,
	0xFFFFFFFF};
/* hlg(2017) */
const UINT32 _g_hdr_yg_lut_data0_m19[PE_HDR_HW_M19_YG_LUT_MAX] = {
	0x00000000,
	0x00150333,
	0x0055043C,
	0x00C004FC,
	0x01560598,
	0x0216061D,
	0x03010694,
	0x041706FF,
	0x05580761,
	0x06C307BC,
	0x08590812,
	0x0A1A0862,
	0x0C0608AE,
	0x0E1C08F6,
	0x105D093B,
	0x12C9097D,
	0x156009BD,
	0x184C09FE,
	0x1BC80A43,
	0x1FEF0A8D,
	0x24E00ADC,
	0x2AC30B30,
	0x31C70B88,
	0x3A220BE5,
	0x44150C47,
	0x4FEF0CAD,
	0x5E0E0D19,
	0x6EDF0D89,
	0x82E70DFE,
	0x9AC40E78,
	0xB7300EF7,
	0xD90B0F7B,
	0xFFFF1000};
/* hlg(2018) */
const UINT32 _g_hdr_yg_lut_data1_m19[PE_HDR_HW_M19_YG_LUT_MAX] = {
	0x00000000,
	0x00060490,
	0x00550686,
	0x00c00748,
	0x015607df,
	0x0216085c,
	0x030108c8,
	0x04170928,
	0x0558097e,
	0x06c309cc,
	0x08590a15,
	0x0a1a0a58,
	0x0c060a97,
	0x0e1c0ad2,
	0x105d0b0a,
	0x12c90b3f,
	0x15600b72,
	0x184c0ba5,
	0x1bc80bdb,
	0x1fef0c15,
	0x24e00c52,
	0x2ac30c91,
	0x31c70cd4,
	0x3a220d19,
	0x44150d62,
	0x4fef0dad,
	0x5e0e0dfa,
	0x6edf0e4b,
	0x82e70e9e,
	0x9ac40ef3,
	0xb7300f4b,
	0xd90b0fa6,
	0xffff1000};

/* hdr csc 1st(y2gbr), (expend for HDR) (65_960 for SDR) */
/* hdr csc 3rd(gbr2y), (limit for HDR) (65_960 for SDR) */
const UINT16 _g_pe_hdr_hw_m19_csc_mtrx_bypass[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0x0000, 0x0000,		//  1.000, 0.000, 0.000
	0x0000, 0x1000, 0x0000,		//  0.000, 1.000, 0.000
	0x0000, 0x0000, 0x1000};	//  0.000, 0.000, 1.000
const UINT16 _g_pe_hdr_hw_m19_csc_ofst_bypass[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0000, 0x0000, 0x0000};	//   0,   0,   0

const UINT16 _g_pe_hdr_hw_m19_pcc_mtrx_default[PE_NUM_OF_CSC_COEF] = {
	0x121f, 0x7fde, 0x7e02,		//   1.1326, -0.0083, -0.1245,
	0x7e65, 0x11e5, 0x7fb6,		//  -0.1003, 1.1184, -0.0181,
	0x769a, 0x7ed6, 0x1a8f};	//  -0.5874, -0.0728, 1.6599,

#if 1	//use 10bit csc
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_601_64_940[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFA9E, 0xF4D4,		//  1.0000,-0.3365,-0.6982
	0x1000, 0x1BB8, 0x0000,		//  1.0000, 1.7324, 0.0000
	0x1000, 0x0000, 0x15EE};	//  1.0000, 0.0000, 1.3707
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_601_64_940[PE_NUM_OF_CSC_COEF]= {
	0x0964, 0x01D3, 0x04C9,		//  0.5870, 0.1140, 0.0299
	0xFA94, 0x082F, 0xFD3D,		// -0.3388, 0.5114,-0.1726
	0xF926, 0xFEAB, 0x082F};	// -0.4282,-0.0832, 0.5114
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_709_64_940[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFD12, 0xF8AD,		//  1.0000,-0.1831,-0.4577
	0x1000, 0x1D07, 0x0000,		//  1.0000, 1.8142, 0.0000
	0x1000, 0x0000, 0x18A2};	//  1.0000, 0.0000, 1.5396
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_709_64_940[PE_NUM_OF_CSC_COEF]= {
	0x0B71, 0x0128, 0x0367,		//  0.7152, 0.0722, 0.2126
	0xF9B1, 0x082F, 0xFE20,		// -0.3942, 0.5114,-0.1172
	0xF891, 0xFF40, 0x082F};	// -0.4645,-0.0469, 0.5114

const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_601_lin[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFA9E, 0xF4D4,		//	1.000,-0.336,-0.698
	0x1000, 0x1BB8, 0x0000,		//	1.000, 1.732, 0.000
	0x1000, 0x0000, 0x15EE};	//	1.000, 0.000, 1.371
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_601_exp[PE_NUM_OF_CSC_COEF] = {
	0x12AF, 0xF9B7, 0xF2F4,		//	1.164,-0.391,-0.813
	0x12AF, 0x205F, 0x0000,		//	1.164, 2.018, 0.000
	0x12AF, 0x0000, 0x199D};	//	1.164, 0.000, 1.596
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_709_lin[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFD12, 0xF8AD,		//  1.000,-0.183,-0.459
	0x1000, 0x1D07, 0x0000,   	//  1.000, 1.816, 0.000
	0x1000, 0x0000, 0x18A2};  	//  1.000, 0.000, 1.540
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_709_exp[PE_NUM_OF_CSC_COEF] = {
	0x12AF, 0xFC94, 0xF773,		//  1.164,-0.213,-0.534
	0x12AF, 0x21E6, 0x0000,   	//  1.164, 2.115, 0.000
	0x12AF, 0x0000, 0x1CC5};  	//  1.164, 0.000, 1.793

const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_601_linea[PE_NUM_OF_CSC_COEF]= {
	0x0964, 0x01D3, 0x04C9,		// 0.587, 0.114, 0.299
	0xFA94, 0x082F, 0xFD3D,		//-0.339, 0.511,-0.172
	0xF926, 0xFEAB, 0x082F};	//-0.428,-0.083, 0.511
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_601_limit[PE_NUM_OF_CSC_COEF]= {
	0x080B, 0x0190, 0x0419,		// 0.504, 0.098, 0.257
	0xFB5C, 0x0702, 0xFDA3,		//-0.291, 0.439,-0.148
	0xFA22, 0xFEDC, 0x0702};	//-0.368,-0.071, 0.439
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_709_linea[PE_NUM_OF_CSC_COEF]= {
	0x0b71, 0x0128, 0x0367,		//  0.7148, 0.0718, 0.2129
	0xf9b1, 0x082f, 0xfe20,		// -0.3938, 0.5110,-0.1167
	0xf891, 0xff40, 0x082f};	// -0.4639,-0.0469, 0.5110
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_709_limit[PE_NUM_OF_CSC_COEF]= {
	0x09cd, 0x00fd, 0x02ea,		//  0.6138, 0.0618, 0.1829
	0xfa99, 0x0702, 0xfe65,		// -0.3379, 0.4390,-0.1011
	0xf9a3, 0xff5c, 0x0702};	// -0.3989,-0.0398, 0.4390
#else
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_601_lin[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFAA0, 0xF4D5,		//	1.000,-0.336,-0.698
	0x1000, 0x1BB6, 0x0000,		//	1.000, 1.732, 0.000
	0x1000, 0x0000, 0x15F0};	//	1.000, 0.000, 1.371
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_601_exp[PE_NUM_OF_CSC_COEF] = {
	0x12A0, 0xF9BE, 0xF2FE,		//	1.164,-0.391,-0.813
	0x12A0, 0x204A, 0x0000,		//	1.164, 2.018, 0.000
	0x12A0, 0x0000, 0x1989};	//	1.164, 0.000, 1.596
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_709_lin[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFD13, 0xF8A8,		//  1.000,-0.183,-0.459
	0x1000, 0x1D0E, 0x0000,   	//  1.000, 1.816, 0.000
	0x1000, 0x0000, 0x18A3};  	//  1.000, 0.000, 1.540
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_709_exp[PE_NUM_OF_CSC_COEF] = {
	0x129F, 0xFC98, 0xF775,		//  1.164,-0.213,-0.534
	0x129F, 0x21D7, 0x0000,   	//  1.164, 2.115, 0.000
	0x129F, 0x0000, 0x1CB0};  	//  1.164, 0.000, 1.793

const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_601_linea[PE_NUM_OF_CSC_COEF]= {
	0x0964, 0x01D3, 0x04C9,		// 0.587, 0.114, 0.299
	0xFA93, 0x082D, 0xFD3F,		//-0.339, 0.511,-0.172
	0xF927, 0xFEAC, 0x082D};	//-0.428,-0.083, 0.511
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_601_limit[PE_NUM_OF_CSC_COEF]= {
	0x0810, 0x0191, 0x041D,		// 0.504, 0.098, 0.257
	0xFB58, 0x0706, 0xFDA2,		//-0.291, 0.439,-0.148
	0xFA1D, 0xFEDD, 0x0706};	//-0.368,-0.071, 0.439
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_709_linea[PE_NUM_OF_CSC_COEF]= {
	0x0b70, 0x0126, 0x0368,		//  0.7148, 0.0718, 0.2129
	0xf9b3, 0x082d, 0xfe22,		// -0.3938, 0.5110,-0.1167
	0xf894, 0xff40, 0x082d};	// -0.4639,-0.0469, 0.5110
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_709_limit[PE_NUM_OF_CSC_COEF]= {
	0x09d2, 0x00fd, 0x02ed,		//  0.6138, 0.0618, 0.1829
	0xfa98, 0x0706, 0xfe62,		// -0.3379, 0.4390,-0.1011
	0xf99e, 0xff5d, 0x0706};	// -0.3989,-0.0398, 0.4390

const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_601_65_960[PE_NUM_OF_CSC_COEF] = {
	0x1057, 0xFA81, 0xF497,		//	1.0213,-0.3436,-0.7131
	0x1057, 0x1C4F, 0x0000,		//	1.0213, 1.7693, 0.0000
	0x1057, 0x0000, 0x1666};	//	1.0213, 0.0000, 1.3999
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_601_65_960[PE_NUM_OF_CSC_COEF]= {
	0x0932, 0x01C9, 0x04AF,		//  0.5748, 0.1116, 0.2928
	0xFAB1, 0x0803, 0xFD4C,		// -0.3318, 0.5008,-0.1690
	0xF94A, 0xFEB2, 0x0803};	// -0.4193,-0.0814, 0.5008
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_709_65_960[PE_NUM_OF_CSC_COEF] = {
	0x1057, 0xFD02, 0xF885,		//  1.0213,-0.1870,-0.4674
	0x1057, 0x1DA5, 0x0000,   	//  1.0213, 1.8528, 0.0000
	0x1057, 0x0000, 0x1929};  	//  1.0213, 0.0000, 1.5724
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_709_65_960[PE_NUM_OF_CSC_COEF]= {
	0x0B34, 0x0122, 0x0355,		//  0.7003, 0.0707, 0.2082
	0xF9D3, 0x0803, 0xFE2A,   	// -0.3860, 0.5008,-0.1147
	0xF8B9, 0xFF44, 0x0803};  	// -0.4548,-0.0459, 0.5008
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_n2020_65_960[PE_NUM_OF_CSC_COEF] = {
	0x1057, 0xFD5F, 0xF6DF,		//  1.0213,-0.1643,-0.5705
	0x1057, 0x1E0F, 0x0000,		//  1.0213, 1.8785, 0.0000
	0x1057, 0x0000, 0x178F};	//  1.0213, 0.0000, 1.4724
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_n2020_65_960[PE_NUM_OF_CSC_COEF]= {
	0x0A9F, 0x00EE, 0x041E,		//  0.6639, 0.0581, 0.2572
	0xFA3A, 0x0803, 0xFDC3,		// -0.3609, 0.5008,-0.1398
	0xF8A2, 0xFF5B, 0x0803};	// -0.4605,-0.0403, 0.5008
#endif

const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_n2020_lin[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFD6D, 0xF710,		//	1.000,-0.161,-0.559
	0x1000, 0x1D6E, 0x0000,		//	1.000, 1.839, 0.000
	0x1000, 0x0000, 0x1711};	//	1.000, 0.000, 1.442
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_n2020_exp[PE_NUM_OF_CSC_COEF] = {
	0x12AF, 0xFCFE, 0xF590,		//  1.168,-0.188,-0.652
	0x12AF, 0x225F, 0x0000,		//  1.168, 2.148, 0.000
	0x12AF, 0x0000, 0x1AF0};	//  1.168, 0.000, 1.684
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_n2020_lin[PE_NUM_OF_CSC_COEF]= {
	0x0AD9, 0x00F3, 0x0434,		// 0.6780000, 0.0593000, 0.2627000
	0xFA1A, 0x082F, 0xFDB7,		//-0.3685976, 0.5114155,-0.1428180
	0xF87A, 0xFF58, 0x082F};	//-0.4702831,-0.0411324, 0.5114155
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_n2020_lim[PE_NUM_OF_CSC_COEF]= {
	0x094A, 0x00D0, 0x0399,		// 0.5806, 0.0508, 0.2249
	0xFAF3, 0x0702, 0xFE0B,		//-0.3157, 0.4379,-0.1223
	0xF98F, 0xFF70, 0x0702};	//-0.4028,-0.0352, 0.4379

const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_ofst_lin[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0xFE00, 0xFE00,		//   0,-512,-512
	0x0000, 0x0000, 0x0000};	//   0,   0,   0
const UINT16 _g_pe_hdr_hw_m19_csc_y2gbr_ofst_exp[PE_NUM_OF_CSC_OFST] = {
	0xFFC0, 0xFE00, 0xFE00,		// -64,-512,-512
	0x0000, 0x0000, 0x0000};	//   0,   0,   0
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_ofst_linr[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0000, 0x0200, 0x0200};	//   0, 512, 512
const UINT16 _g_pe_hdr_hw_m19_csc_gbr2y_ofst_limt[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0040, 0x0200, 0x0200};	//  64, 512, 512

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * sort trace data buf to dst buf
 * - ascending, bubble sorting
 *
 * @param   *dst [in/out] PE_HDR_HW_M19_DATA_BUF_T
 * @return  void
 * @see
 * @author	sj.youm@lge.com
 */
static void PE_HDR_HW_M19_SortTraceDataBuf(PE_HDR_HW_M19_DATA_BUF_T *dst)
{
	int ret = RET_OK;
	UINT32 size=0, i=0, max=0;
	UINT32 j=0, s0=0, s1=0, us0=0, us1=0;
	PE_HDR_HW_M19_DATA_BUF_T temp;
	PE_HDR_HW_M19_DATA_BUF_T *src = _gp_pe_hdr_hw_m19_buf_curr;

	do{
		CHECK_KNULL(dst);
		CHECK_KNULL(_gp_pe_hdr_hw_m19_buf_curr);
		max = PE_HDR_HW_M19_BUF_MAX;
		size = sizeof(PE_HDR_HW_M19_DATA_BUF_T);
		memcpy(dst, src, (size*max));
		for (i=0; i<max; i++)
		{
			for (j=0; j<(max-1-i); j++)
			{
				s0 = dst[j].time.sec;
				s1 = dst[j+1].time.sec;
				us0 = dst[j].time.msec * 1000 + dst[j].time.usec;
				us1 = dst[j+1].time.msec * 1000 + dst[j+1].time.usec;
				if ((s0>s1) || (s0==s1 && us0>us1))
				{
					memcpy(&temp, &dst[j], size);
					memcpy(&dst[j], &dst[j+1], size);
					memcpy(&dst[j+1], &temp, size);
				}
			}
		}
	}while (0);
	return;
}
/**
 * get trace data buf
 *
 * @param   *data [in] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_HDR_HW_M19_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0, type=0;;
	PE_HDR_HW_M19_DATA_BUF_T *p_buf = _gp_pe_hdr_hw_m19_buf_sort;
	UINT32 *p_data = NULL;
	PE_HDR_HW_M19_TIME_T *p_time = NULL;
	char *p_str = NULL;

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		CHECK_KNULL(_gp_pe_hdr_hw_m19_buf_curr);
		CHECK_KNULL(_gp_pe_hdr_hw_m19_buf_sort);
		type = pstParams->data[0];
		if (type==0)	rd_cnt = pstParams->oper;
		else			rd_cnt = PE_HDR_HW_M19_BUF_MAX;
		if (rd_cnt<PE_HDR_HW_M19_BUF_MAX)
		{
			if(rd_cnt==0)
			{
				PE_HDR_HW_M19_SortTraceDataBuf(p_buf);
			}
			p_time = &(p_buf[rd_cnt].time);
			p_str = p_buf[rd_cnt].str;
			if(p_time->sec || p_time->msec || p_time->usec)
			{
				snprintf(buffer, PE_TRACE_STR_SIZE, "[%06d.%03d%03d] %s\n", \
					p_time->sec, p_time->msec, p_time->usec, p_str);
			}
			else
			{
				snprintf(buffer, PE_TRACE_STR_SIZE, "RESERVED");
			}
			rd_cnt++;
		}
		else
		{
			snprintf(buffer, PE_TRACE_STR_SIZE, "END_OF_PRINT");
			rd_cnt=0;
		}
		p_data = pstParams->data;
		memcpy(p_data, buffer, PE_TRACE_STR_SIZE);
	}while (0);
	return ret;
}

/**
 * set trace data buf
 *
 * @param   *data [in] char
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
static int PE_HDR_HW_M19_SetTraceDataBuf(char *data)
{
    int ret = RET_OK;
	UINT32 i = 0;
	char *p_str = NULL;
	PE_HDR_HW_M19_TIME_T *p_time = NULL;
	static UINT32 cnt = 0;
	PE_HDR_HW_M19_DATA_BUF_T *p_buf = _gp_pe_hdr_hw_m19_buf_curr;
	do{
		CHECK_KNULL(data);
		CHECK_KNULL(_gp_pe_hdr_hw_m19_buf_curr);
		if(cnt>=PE_HDR_HW_M19_BUF_MAX)	cnt = 0;
		p_str = p_buf[cnt].str;
		p_time = &(p_buf[cnt].time);
		OS_GetCurrentTicks(&(p_time->sec), &(p_time->msec), &(p_time->usec));
		memset(p_str, 0, PE_TRACE_STR_SIZE);
		for(i=0;i<PE_TRACE_STR_SIZE;i++)
		{
			p_str[i] = data[i];
			if(data[i] == 0) break;
		}
		cnt++;
	}while (0);
	return ret;
}
/**
 * PE_HDR_HW_M19_GetConnectMode
 *
 * @param   void
 * @return  0:SDR,1:HDR10,2:HLG,3:S2H
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_GetConnectMode(UINT32 win_id)
{
	UINT32 mode;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
	LX_PE_HDR_OP_MD_T *p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_0].data[0]));//main info only
	#else
	LX_PE_HDR_OP_MD_T *p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[win_id].data[0]));
	#endif
	if (p_op->connect == 2)								mode = PE_HDR_HW_M19_CONNECT_MODE_H10;
	else if (p_op->connect == 5)						mode = PE_HDR_HW_M19_CONNECT_MODE_HLG;
	else if (p_op->connect == 3)						mode = PE_HDR_HW_M19_CONNECT_MODE_TEC;
	else if (p_op->connect == 0 && p_op->hdrcase == 4)	mode = PE_HDR_HW_M19_CONNECT_MODE_S2H;
	else												mode = PE_HDR_HW_M19_CONNECT_MODE_SDR;
	return mode;
}
/**
 * PE_HDR_HW_M19_GetToneConnectMode
 *
 * @param   path: 0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg
 * @return  mode: 0:SDR,1:HDR10,2:HLG,3:S2H,4:TEC
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_GetToneConnectMode(UINT32 path)
{
	UINT32 mode;
	if (path == 2)			mode = PE_HDR_HW_M19_CONNECT_MODE_H10;
	else if (path == 5)		mode = PE_HDR_HW_M19_CONNECT_MODE_HLG;
	else if (path == 3)		mode = PE_HDR_HW_M19_CONNECT_MODE_TEC;
	else if (path == 4)		mode = PE_HDR_HW_M19_CONNECT_MODE_S2H;
	else					mode = PE_HDR_HW_M19_CONNECT_MODE_SDR;
	return mode;
}
/**
 * PE_HDR_HW_M19_GetToneOffset
 *
 * @param   win_id [in] UINT32
 * @param   type [in] UINT32
 * @return  offset
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_GetToneOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	/* A:HLG, B:HDR10, C:S2H, D:PRIME, E:SDR, F:reserved */
	if (type == PE_HDR_HW_M19_LUT_TYPE_A)				ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_A_OFST:PE_HDR_DDR_2_M19_TONE_A_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_B)			ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_B_OFST:PE_HDR_DDR_2_M19_TONE_B_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_C)			ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_C_OFST:PE_HDR_DDR_2_M19_TONE_C_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_D)			ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_D_OFST:PE_HDR_DDR_2_M19_TONE_D_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_E)			ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_E_OFST:PE_HDR_DDR_2_M19_TONE_E_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_F)			ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_F_OFST:PE_HDR_DDR_2_M19_TONE_F_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_HLG)	ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_A_OFST:PE_HDR_DDR_2_M19_TONE_A_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_H10)	ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_B_OFST:PE_HDR_DDR_2_M19_TONE_B_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_S2H)	ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_C_OFST:PE_HDR_DDR_2_M19_TONE_C_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_TEC)	ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_D_OFST:PE_HDR_DDR_2_M19_TONE_D_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_SDR)	ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_E_OFST:PE_HDR_DDR_2_M19_TONE_E_OFST;
	else												ofst = (win_id==0)? PE_HDR_DDR_M19_TONE_F_OFST:PE_HDR_DDR_2_M19_TONE_F_OFST;

	return ofst;
}
/**
 * PE_HDR_HW_M19_IncreaseToneCount
 *
 * @param   win_id [in] UINT32
 * @param   ofst [in] UINT32
 * @return  count
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_IncreaseToneCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_M19_HEADER2_T header2;
	PE_HDR_DDR_M19_HEADER5_T header5;
	UINT32 *pU32Header2 = (UINT32 *)&header2;
	UINT32 *pU32Header5 = (UINT32 *)&header5;
	rmb();
	if (win_id==0)
	{
		*pU32Header2 = gPE_HDR_DDR_M19[2];
		if (ofst == PE_HDR_DDR_M19_TONE_A_OFST)
			count = header2.cnt_tone_a = (header2.cnt_tone_a == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header2.cnt_tone_a+1);
		else if (ofst == PE_HDR_DDR_M19_TONE_B_OFST)
			count = header2.cnt_tone_b = (header2.cnt_tone_b == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header2.cnt_tone_b+1);
		else if (ofst == PE_HDR_DDR_M19_TONE_C_OFST)
			count = header2.cnt_tone_c = (header2.cnt_tone_c == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header2.cnt_tone_c+1);
		else if (ofst == PE_HDR_DDR_M19_TONE_D_OFST)
			count = header2.cnt_tone_d = (header2.cnt_tone_d == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header2.cnt_tone_d+1);
		else if (ofst == PE_HDR_DDR_M19_TONE_E_OFST)
			count = header2.cnt_tone_e = (header2.cnt_tone_e == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header2.cnt_tone_e+1);
		else//if (ofst == PE_HDR_DDR_M19_TONE_F_OFST)
			count = header2.cnt_tone_f = (header2.cnt_tone_f == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header2.cnt_tone_f+1);
		gPE_HDR_DDR_M19[2] = *pU32Header2;
	}
	else
	{
		*pU32Header5 = gPE_HDR_DDR_M19[5];
		if (ofst == PE_HDR_DDR_2_M19_TONE_A_OFST)
			count = header5.cnt_tone_a = (header5.cnt_tone_a == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header5.cnt_tone_a+1);
		else if (ofst == PE_HDR_DDR_2_M19_TONE_B_OFST)
			count = header5.cnt_tone_b = (header5.cnt_tone_b == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header5.cnt_tone_b+1);
		else if (ofst == PE_HDR_DDR_2_M19_TONE_C_OFST)
			count = header5.cnt_tone_c = (header5.cnt_tone_c == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header5.cnt_tone_c+1);
		else if (ofst == PE_HDR_DDR_2_M19_TONE_D_OFST)
			count = header5.cnt_tone_d = (header5.cnt_tone_d == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header5.cnt_tone_d+1);
		else if (ofst == PE_HDR_DDR_2_M19_TONE_E_OFST)
			count = header5.cnt_tone_e = (header5.cnt_tone_e == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header5.cnt_tone_e+1);
		else//if (ofst == PE_HDR_DDR_2_M19_TONE_F_OFST)
			count = header5.cnt_tone_f = (header5.cnt_tone_f == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header5.cnt_tone_f+1);
		gPE_HDR_DDR_M19[5] = *pU32Header5;
	}
	wmb();
	return count;
}

/**
 * PE_HDR_HW_M19_GetYlutOffset
 *
 * @param   win_id [in] UINT32
 * @param   type [in] UINT32
 * @return  offset
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_GetYlutOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	/* A:HLG, B:reserved */
	if (type == PE_HDR_HW_M19_LUT_TYPE_A)				ofst = (win_id==0)? PE_HDR_DDR_M19_YLUT_A_OFST:PE_HDR_DDR_2_M19_YLUT_A_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_B)			ofst = (win_id==0)? PE_HDR_DDR_M19_YLUT_B_OFST:PE_HDR_DDR_2_M19_YLUT_B_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_HLG)	ofst = (win_id==0)? PE_HDR_DDR_M19_YLUT_A_OFST:PE_HDR_DDR_2_M19_YLUT_A_OFST;
	else												ofst = (win_id==0)? PE_HDR_DDR_M19_YLUT_B_OFST:PE_HDR_DDR_2_M19_YLUT_B_OFST;

	return ofst;
}
/**
 * PE_HDR_HW_M19_IncreaseYlutCount
 *
 * @param   win_id [in] UINT32
 * @param   ofst [in] UINT32
 * @return  count
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_IncreaseYlutCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_M19_HEADER2_T header2;
	PE_HDR_DDR_M19_HEADER5_T header5;
	UINT32 *pU32Header2 = (UINT32 *)&header2;
	UINT32 *pU32Header5 = (UINT32 *)&header5;
	rmb();
	if (win_id==0)
	{
		*pU32Header2 = gPE_HDR_DDR_M19[2];
		if (ofst == PE_HDR_DDR_M19_YLUT_A_OFST)
			count = header2.cnt_ylut_a = (header2.cnt_ylut_a == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header2.cnt_ylut_a+1);
		else
			count = header2.cnt_ylut_b = (header2.cnt_ylut_b == PE_HDR_DDR_M19_YG_CNT_MAX)? 1:(header2.cnt_ylut_b+1);
		gPE_HDR_DDR_M19[2] = *pU32Header2;
	}
	else
	{
		*pU32Header5 = gPE_HDR_DDR_M19[5];
		if (ofst == PE_HDR_DDR_2_M19_YLUT_A_OFST)
			count = header5.cnt_ylut_a = (header5.cnt_ylut_a == PE_HDR_DDR_M19_TM_CNT_MAX)? 1:(header5.cnt_ylut_a+1);
		else
			count = header5.cnt_ylut_b = (header5.cnt_ylut_b == PE_HDR_DDR_M19_YG_CNT_MAX)? 1:(header5.cnt_ylut_b+1);
		gPE_HDR_DDR_M19[5] = *pU32Header5;
	}
	wmb();
	return count;
}
/**
 * PE_HDR_HW_M19_GetEotfOffset
 *
 * @param   win_id [in] UINT32
 * @param   type [in] UINT32
 * @return  offset
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_GetEotfOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	/* A:HLG, B:HDR10(4K), C:HDR10(10K), D:prime(10K) */
	if (type == PE_HDR_HW_M19_LUT_TYPE_A)				ofst = (win_id==0)? PE_HDR_DDR_M19_EOTF_A_OFST:PE_HDR_DDR_2_M19_EOTF_A_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_B)			ofst = (win_id==0)? PE_HDR_DDR_M19_EOTF_B_OFST:PE_HDR_DDR_2_M19_EOTF_B_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_C)			ofst = (win_id==0)? PE_HDR_DDR_M19_EOTF_C_OFST:PE_HDR_DDR_2_M19_EOTF_C_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_D)			ofst = (win_id==0)? PE_HDR_DDR_M19_EOTF_D_OFST:PE_HDR_DDR_2_M19_EOTF_D_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_HLG)	ofst = (win_id==0)? PE_HDR_DDR_M19_EOTF_A_OFST:PE_HDR_DDR_2_M19_EOTF_A_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_H10)	ofst = (win_id==0)? PE_HDR_DDR_M19_EOTF_B_OFST:PE_HDR_DDR_2_M19_EOTF_B_OFST;
	else												ofst = (win_id==0)? PE_HDR_DDR_M19_EOTF_D_OFST:PE_HDR_DDR_2_M19_EOTF_D_OFST;

	return ofst;
}
/**
 * PE_HDR_HW_M19_IncreaseEotfCount
 *
 * @param   win_id [in] UINT32
 * @param   ofst [in] UINT32
 * @return  count
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_IncreaseEotfCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_M19_HEADER1_T header1;
	PE_HDR_DDR_M19_HEADER4_T header4;
	UINT32 *pU32Header1 = (UINT32 *)&header1;
	UINT32 *pU32Header4 = (UINT32 *)&header4;
	rmb();
	if (win_id==0)
	{
		*pU32Header1 = gPE_HDR_DDR_M19[1];
		if (ofst == PE_HDR_DDR_M19_EOTF_A_OFST)
			count = header1.cnt_eotf_a = (header1.cnt_eotf_a == PE_HDR_DDR_M19_EO_CNT_MAX)? 1:(header1.cnt_eotf_a+1);
		else if (ofst == PE_HDR_DDR_M19_EOTF_B_OFST)
			count = header1.cnt_eotf_b = (header1.cnt_eotf_b == PE_HDR_DDR_M19_EO_CNT_MAX)? 1:(header1.cnt_eotf_b+1);
		else if (ofst == PE_HDR_DDR_M19_EOTF_C_OFST)
			count = header1.cnt_eotf_c = (header1.cnt_eotf_c == PE_HDR_DDR_M19_EO_CNT_MAX)? 1:(header1.cnt_eotf_c+1);
		else
			count = header1.cnt_eotf_d = (header1.cnt_eotf_d == PE_HDR_DDR_M19_EO_CNT_MAX)? 1:(header1.cnt_eotf_d+1);
		gPE_HDR_DDR_M19[1] = *pU32Header1;
	}
	else
	{
		*pU32Header4 = gPE_HDR_DDR_M19[4];
		if (ofst == PE_HDR_DDR_2_M19_EOTF_A_OFST)
			count = header4.cnt_eotf_a = (header4.cnt_eotf_a == PE_HDR_DDR_M19_EO_CNT_MAX)? 1:(header4.cnt_eotf_a+1);
		else if (ofst == PE_HDR_DDR_2_M19_EOTF_B_OFST)
			count = header4.cnt_eotf_b = (header4.cnt_eotf_b == PE_HDR_DDR_M19_EO_CNT_MAX)? 1:(header4.cnt_eotf_b+1);
		else if (ofst == PE_HDR_DDR_2_M19_EOTF_C_OFST)
			count = header4.cnt_eotf_c = (header4.cnt_eotf_c == PE_HDR_DDR_M19_EO_CNT_MAX)? 1:(header4.cnt_eotf_c+1);
		else
			count = header4.cnt_eotf_d = (header4.cnt_eotf_d == PE_HDR_DDR_M19_EO_CNT_MAX)? 1:(header4.cnt_eotf_d+1);
		gPE_HDR_DDR_M19[4] = *pU32Header4;
	}
	wmb();
	return count;
}
/**
 * PE_HDR_HW_M19_GetEotfCount
 *
 * @param   win_id [in] UINT32
 * @param   ofst [in] UINT32
 * @return  count
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_GetEotfCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_M19_HEADER1_T header1;
	PE_HDR_DDR_M19_HEADER4_T header4;
	UINT32 *pU32Header1 = (UINT32 *)&header1;
	UINT32 *pU32Header4 = (UINT32 *)&header4;
	rmb();
	if (win_id==0)
	{
		*pU32Header1 = gPE_HDR_DDR_M19[1];
		if (ofst == PE_HDR_DDR_M19_EOTF_A_OFST)			count = header1.cnt_eotf_a;
		else if (ofst == PE_HDR_DDR_M19_EOTF_B_OFST)	count = header1.cnt_eotf_b;
		else if (ofst == PE_HDR_DDR_M19_EOTF_C_OFST)	count = header1.cnt_eotf_c;
		else											count = header1.cnt_eotf_d;
	}
	else
	{
		*pU32Header4 = gPE_HDR_DDR_M19[4];
		if (ofst == PE_HDR_DDR_2_M19_EOTF_A_OFST)		count = header4.cnt_eotf_a;
		else if (ofst == PE_HDR_DDR_2_M19_EOTF_B_OFST)	count = header4.cnt_eotf_b;
		else if (ofst == PE_HDR_DDR_2_M19_EOTF_C_OFST)	count = header4.cnt_eotf_c;
		else											count = header4.cnt_eotf_d;
	}
	return count;
}
/**
 * PE_HDR_HW_M19_GetOetfOffset
 *
 * @param   win_id [in] UINT32
 * @param   type [in] UINT32
 * @return  offset
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_GetOetfOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	/* A:HLG, B:TEC, C:HDR10, D:default */
	if (type == PE_HDR_HW_M19_LUT_TYPE_A)				ofst = (win_id==0)? PE_HDR_DDR_M19_OETF_A_OFST:PE_HDR_DDR_2_M19_OETF_A_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_B)			ofst = (win_id==0)? PE_HDR_DDR_M19_OETF_B_OFST:PE_HDR_DDR_2_M19_OETF_B_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_C)			ofst = (win_id==0)? PE_HDR_DDR_M19_OETF_C_OFST:PE_HDR_DDR_2_M19_OETF_C_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_D)			ofst = (win_id==0)? PE_HDR_DDR_M19_OETF_D_OFST:PE_HDR_DDR_2_M19_OETF_D_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_HLG)	ofst = (win_id==0)? PE_HDR_DDR_M19_OETF_A_OFST:PE_HDR_DDR_2_M19_OETF_A_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_TEC)	ofst = (win_id==0)? PE_HDR_DDR_M19_OETF_B_OFST:PE_HDR_DDR_2_M19_OETF_B_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_H10)	ofst = (win_id==0)? PE_HDR_DDR_M19_OETF_C_OFST:PE_HDR_DDR_2_M19_OETF_C_OFST;
	else												ofst = (win_id==0)? PE_HDR_DDR_M19_OETF_D_OFST:PE_HDR_DDR_2_M19_OETF_D_OFST;

	return ofst;
}
/**
 * PE_HDR_HW_M19_IncreaseOetfCount
 *
 * @param   win_id [in] UINT32
 * @param   ofst [in] UINT32
 * @return  count
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_IncreaseOetfCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_M19_HEADER1_T header1;
	PE_HDR_DDR_M19_HEADER4_T header4;
	UINT32 *pU32Header1 = (UINT32 *)&header1;
	UINT32 *pU32Header4 = (UINT32 *)&header4;
	rmb();
	if (win_id==0)
	{
		*pU32Header1 = gPE_HDR_DDR_M19[1];
		if (ofst == PE_HDR_DDR_M19_OETF_A_OFST)
			count = header1.cnt_oetf_a = (header1.cnt_oetf_a == PE_HDR_DDR_M19_OE_CNT_MAX)? 1:(header1.cnt_oetf_a+1);
		else if (ofst == PE_HDR_DDR_M19_OETF_B_OFST)
			count = header1.cnt_oetf_b = (header1.cnt_oetf_b == PE_HDR_DDR_M19_OE_CNT_MAX)? 1:(header1.cnt_oetf_b+1);
		else if (ofst == PE_HDR_DDR_M19_OETF_C_OFST)
			count = header1.cnt_oetf_c = (header1.cnt_oetf_c == PE_HDR_DDR_M19_OE_CNT_MAX)? 1:(header1.cnt_oetf_c+1);
		else
			count = header1.cnt_oetf_d = (header1.cnt_oetf_d == PE_HDR_DDR_M19_OE_CNT_MAX)? 1:(header1.cnt_oetf_d+1);
		gPE_HDR_DDR_M19[1] = *pU32Header1;
	}
	else
	{
		*pU32Header4 = gPE_HDR_DDR_M19[4];
		if (ofst == PE_HDR_DDR_2_M19_OETF_A_OFST)
			count = header4.cnt_oetf_a = (header4.cnt_oetf_a == PE_HDR_DDR_M19_OE_CNT_MAX)? 1:(header4.cnt_oetf_a+1);
		else if (ofst == PE_HDR_DDR_2_M19_OETF_B_OFST)
			count = header4.cnt_oetf_b = (header4.cnt_oetf_b == PE_HDR_DDR_M19_OE_CNT_MAX)? 1:(header4.cnt_oetf_b+1);
		else if (ofst == PE_HDR_DDR_2_M19_OETF_C_OFST)
			count = header4.cnt_oetf_c = (header4.cnt_oetf_c == PE_HDR_DDR_M19_OE_CNT_MAX)? 1:(header4.cnt_oetf_c+1);
		else
			count = header4.cnt_oetf_d = (header4.cnt_oetf_d == PE_HDR_DDR_M19_OE_CNT_MAX)? 1:(header4.cnt_oetf_d+1);
		gPE_HDR_DDR_M19[4] = *pU32Header4;
	}
	wmb();
	return count;
}
/**
 * PE_HDR_HW_M19_GetOetfCount
 *
 * @param   win_id [in] UINT32
 * @param   ofst [in] UINT32
 * @return  count
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_GetOetfCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_M19_HEADER1_T header1;
	PE_HDR_DDR_M19_HEADER4_T header4;
	UINT32 *pU32Header1 = (UINT32 *)&header1;
	UINT32 *pU32Header4 = (UINT32 *)&header4;
	rmb();
	if (win_id==0)
	{
		*pU32Header1 = gPE_HDR_DDR_M19[1];
		if (ofst == PE_HDR_DDR_M19_OETF_A_OFST)			count = header1.cnt_oetf_a;
		else if (ofst == PE_HDR_DDR_M19_OETF_B_OFST)	count = header1.cnt_oetf_b;
		else if (ofst == PE_HDR_DDR_M19_OETF_C_OFST)	count = header1.cnt_oetf_c;
		else											count = header1.cnt_oetf_d;
	}
	else
	{
		*pU32Header4 = gPE_HDR_DDR_M19[4];
		if (ofst == PE_HDR_DDR_2_M19_OETF_A_OFST)		count = header4.cnt_oetf_a;
		else if (ofst == PE_HDR_DDR_2_M19_OETF_B_OFST)	count = header4.cnt_oetf_b;
		else if (ofst == PE_HDR_DDR_2_M19_OETF_C_OFST)	count = header4.cnt_oetf_c;
		else											count = header4.cnt_oetf_d;
	}
	return count;
}
/**
 * PE_HDR_HW_M19_Get3dLutOffset
 *
 * @param   win_id [in] UINT32
 * @param   type [in] UINT32
 * @return  offset
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_Get3dLutOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	if (win_id!=0)	return 0xffffffff;

	/* A:SDR, B:HDR10+, C,D:reserved */
	if (type == PE_HDR_HW_M19_LUT_TYPE_A)				ofst = PE_HDR_DDR_M19_3LUT_A1_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_B)			ofst = PE_HDR_DDR_M19_3LUT_B1_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_C)			ofst = PE_HDR_DDR_M19_3LUT_C1_OFST;
	else if (type == PE_HDR_HW_M19_LUT_TYPE_D)			ofst = PE_HDR_DDR_M19_3LUT_D1_OFST;
	else if (type == PE_HDR_HW_M19_CONNECT_MODE_SDR)	ofst = PE_HDR_DDR_M19_3LUT_A1_OFST;
	else												ofst = PE_HDR_DDR_M19_3LUT_B1_OFST;

	return ofst;
}
/**
 * PE_HDR_HW_M19_Set3dLutCount
 *
 * @param   win_id [in] UINT32
 * @param   ofst [in] UINT32
 * @param   indx [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_Set3dLutCount(UINT32 win_id, UINT32 ofst, UINT32 indx)
{
	PE_HDR_DDR_M19_HEADER0_T header0;
	UINT32 *pU32Header0 = (UINT32 *)&header0;

	if (win_id!=0)	return RET_OK;

	wmb();rmb();
	*pU32Header0 = gPE_HDR_DDR_M19[0];
	if (ofst == PE_HDR_DDR_M19_3LUT_A1_OFST)		header0.idx_3lut_a = indx;
	else if (ofst == PE_HDR_DDR_M19_3LUT_B1_OFST)	header0.idx_3lut_b = indx;
	else if (ofst == PE_HDR_DDR_M19_3LUT_C1_OFST)	header0.idx_3lut_c = indx;
	else											header0.idx_3lut_d = indx;
	gPE_HDR_DDR_M19[0] = *pU32Header0;
	wmb();

	return RET_OK;
}
/**
 * PE_HDR_HW_M19_Increase3dLutCount
 *
 * @param   win_id [in] UINT32
 * @param   ofst [in] UINT32
 * @return  count
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_Get3dLutCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_M19_HEADER0_T header0;
	UINT32 *pU32Header0 = (UINT32 *)&header0;

	if (win_id!=0)	return 0;

	wmb();rmb();
	*pU32Header0 = gPE_HDR_DDR_M19[0];

	if (ofst == PE_HDR_DDR_M19_3LUT_A1_OFST)		count = header0.idx_3lut_a;
	else if (ofst == PE_HDR_DDR_M19_3LUT_B1_OFST)	count = header0.idx_3lut_b;
	else if (ofst == PE_HDR_DDR_M19_3LUT_C1_OFST)	count = header0.idx_3lut_c;
	else											count = header0.idx_3lut_d;
	rmb();

	return count;
}
/**
 * PE_HDR_HW_M19_SetSupportInfo
 *
 * @param   win_id [in] UINT32
 * @param   info [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static UINT32 PE_HDR_HW_M19_SetSupportInfo(UINT32 win_id, UINT32 info)
{
	PE_HDR_DDR_M19_HEADER0_T header0;
	UINT32 *pU32Header0 = (UINT32 *)&header0;
	static UINT32 pre_info = -1;
	UINT32 cur_info;

	if (win_id!=0)				return RET_OK;

	cur_info = info&0xff;
	if (pre_info == cur_info)	return RET_OK;
	pre_info = cur_info;

	wmb();rmb();
	*pU32Header0 = gPE_HDR_DDR_M19[0];
	header0.support = cur_info;
	gPE_HDR_DDR_M19[0] = *pU32Header0;
	wmb();

	return RET_OK;
}
#if 0	//not used
/* PAGE_SIZE:0x00001000, PAGE_MASK:0xfffff000 */
/* page aligned offset, size */
#define PE_VMAP_P_OFST(_addr)			((_addr)&(PAGE_SIZE-1))
#define PE_VMAP_P_ADDR(_addr)			((_addr)-PE_VMAP_P_OFST(_addr))
#define PE_VMAP_P_SIZE(_addr,_size)		((_size)+PE_VMAP_P_OFST(_addr))
void *PE_VMAP(unsigned long addr, int size, int *pofst)
{
	void *p;
	int paddr, psize;
	paddr = PE_VMAP_P_ADDR(PE_HDR_DDR_M19_EOTF_LUT_BASE);
	psize = PE_VMAP_P_SIZE(PE_HDR_DDR_M19_EOTF_LUT_BASE,PE_HDR_DDR_M19_EOTF_LUT_SIZE);
	*pofst = PE_VMAP_P_OFST(PE_HDR_DDR_M19_EOTF_LUT_BASE);
	p = (void *)vmap_phys(paddr,psize);
	return p;
}
#endif
/**
 * init dynamic contrast module
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 bufsize;
	//UINT32 alloc_size[10], refer_size[10];
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M19)
		{
			if (!pstParams->resume_mode)	//normal init
			{
				bufsize = sizeof(PE_HDR_HW_M19_DATA_BUF_T)*PE_HDR_HW_M19_BUF_MAX;
				_gp_pe_hdr_hw_m19_buf_curr = (PE_HDR_HW_M19_DATA_BUF_T *)OS_Malloc(bufsize);
				_gp_pe_hdr_hw_m19_buf_sort = (PE_HDR_HW_M19_DATA_BUF_T *)OS_Malloc(bufsize);
				memset(_gp_pe_hdr_hw_m19_buf_curr, 0, bufsize);
				memset(_gp_pe_hdr_hw_m19_buf_sort, 0, bufsize);
			}
			PE_HDR_HW_M19_BACKUP_TRACE("[HW_M19Init]start.(ver:%d,resume:%d)(%s)",\
				PE_HDR_DDR_M19_VERSION, pstParams->resume_mode, PE_HDR_HW_M19_DRV_VER);
			/* first step, init ddr header */
			ret = PE_HDR_HW_M19_InitHdrInfo(pstParams);
			PE_HDR_HW_M19_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_M19_InitHdrInfo() error.\n",__F__,__L__);
			/**************************************/
			ret = PE_HDR_HW_M19_InitHisto(pstParams);
			PE_HDR_HW_M19_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_M19_InitHisto() error.\n",__F__,__L__);
			ret = PE_HDR_HW_M19_InitTonemapLut(pstParams);
			PE_HDR_HW_M19_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_M19_InitTonemapLut() error.\n",__F__,__L__);
			ret = PE_HDR_HW_M19_InitCsc(pstParams);
			PE_HDR_HW_M19_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_M19_InitCsc() error.\n",__F__,__L__);
			ret = PE_HDR_HW_M19_InitYgainLut(pstParams);
			PE_HDR_HW_M19_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_M19_InitYgainLut() error.\n",__F__,__L__);
			/* etc : default setting, request for TV PQ team */
			if (!pstParams->resume_mode)	//normal init
			{
				pInfo->gamma045_enable[LX_PE_WIN_0] = pInfo->gamma045_enable[LX_PE_WIN_1] = 0x0;
				#ifdef PE_HDR_HW_M19_EN_CC_SDR
				pInfo->reg_hue_prsv_en[LX_PE_WIN_0] = pInfo->reg_hue_prsv_en[LX_PE_WIN_1] = 0x1;
				pInfo->reg_sat_prsv_en[LX_PE_WIN_0] = pInfo->reg_sat_prsv_en[LX_PE_WIN_1] = 0x1;
				pInfo->reg_hue_prsv_ratio[LX_PE_WIN_0] = pInfo->reg_hue_prsv_ratio[LX_PE_WIN_1] = 0x3ff;
				pInfo->reg_sat_prsv_ratio[LX_PE_WIN_0] = pInfo->reg_sat_prsv_ratio[LX_PE_WIN_1] = 0x0;
				pInfo->reg_out_sgain_sel[LX_PE_WIN_0] = pInfo->reg_out_sgain_sel[LX_PE_WIN_1] = 0x1;
				pInfo->reg_out_lgain_sel[LX_PE_WIN_0] = pInfo->reg_out_lgain_sel[LX_PE_WIN_1] = 0x0;
				pInfo->reg_inp_s_sel[LX_PE_WIN_0] = pInfo->reg_inp_s_sel[LX_PE_WIN_1] = 0x1;
				pInfo->reg_inp_l_sel[LX_PE_WIN_0] = pInfo->reg_inp_l_sel[LX_PE_WIN_1] = 0x0;
				#else
				pInfo->reg_hue_prsv_en[LX_PE_WIN_0] = pInfo->reg_hue_prsv_en[LX_PE_WIN_1] = 0x0;
				pInfo->reg_sat_prsv_en[LX_PE_WIN_0] = pInfo->reg_sat_prsv_en[LX_PE_WIN_1] = 0x0;
				pInfo->reg_hue_prsv_ratio[LX_PE_WIN_0] = pInfo->reg_hue_prsv_ratio[LX_PE_WIN_1] = 0x3ff;
				pInfo->reg_sat_prsv_ratio[LX_PE_WIN_0] = pInfo->reg_sat_prsv_ratio[LX_PE_WIN_1] = 0x0;
				pInfo->reg_out_sgain_sel[LX_PE_WIN_0] = pInfo->reg_out_sgain_sel[LX_PE_WIN_1] = 0x1;
				pInfo->reg_out_lgain_sel[LX_PE_WIN_0] = pInfo->reg_out_lgain_sel[LX_PE_WIN_1] = 0x0;
				pInfo->reg_inp_s_sel[LX_PE_WIN_0] = pInfo->reg_inp_s_sel[LX_PE_WIN_1] = 0x1;
				pInfo->reg_inp_l_sel[LX_PE_WIN_0] = pInfo->reg_inp_l_sel[LX_PE_WIN_1] = 0x0;
				#endif
				pInfo->lgain_lut[LX_PE_WIN_0][0] = pInfo->lgain_lut[LX_PE_WIN_1][0] = 0x00000000;
				pInfo->lgain_lut[LX_PE_WIN_0][1] = pInfo->lgain_lut[LX_PE_WIN_1][1] = 0x24920040;
				pInfo->lgain_lut[LX_PE_WIN_0][2] = pInfo->lgain_lut[LX_PE_WIN_1][2] = 0x49240080;
				pInfo->lgain_lut[LX_PE_WIN_0][3] = pInfo->lgain_lut[LX_PE_WIN_1][3] = 0x6DB60080;
				pInfo->lgain_lut[LX_PE_WIN_0][4] = pInfo->lgain_lut[LX_PE_WIN_1][4] = 0x92480080;
				pInfo->lgain_lut[LX_PE_WIN_0][5] = pInfo->lgain_lut[LX_PE_WIN_1][5] = 0xB6DA0080;
				pInfo->lgain_lut[LX_PE_WIN_0][6] = pInfo->lgain_lut[LX_PE_WIN_1][6] = 0xDB6C0080;
				pInfo->lgain_lut[LX_PE_WIN_0][7] = pInfo->lgain_lut[LX_PE_WIN_1][7] = 0xFFFF0080;
				pInfo->sgain_lut[LX_PE_WIN_0][0] = pInfo->sgain_lut[LX_PE_WIN_1][0] = 0x00000080;
				pInfo->sgain_lut[LX_PE_WIN_0][1] = pInfo->sgain_lut[LX_PE_WIN_1][1] = 0x24920080;
				pInfo->sgain_lut[LX_PE_WIN_0][2] = pInfo->sgain_lut[LX_PE_WIN_1][2] = 0x49240080;
				pInfo->sgain_lut[LX_PE_WIN_0][3] = pInfo->sgain_lut[LX_PE_WIN_1][3] = 0x6DB60080;
				pInfo->sgain_lut[LX_PE_WIN_0][4] = pInfo->sgain_lut[LX_PE_WIN_1][4] = 0x92480080;
				pInfo->sgain_lut[LX_PE_WIN_0][5] = pInfo->sgain_lut[LX_PE_WIN_1][5] = 0xB6DA0080;
				pInfo->sgain_lut[LX_PE_WIN_0][6] = pInfo->sgain_lut[LX_PE_WIN_1][6] = 0xDB6C0040;
				pInfo->sgain_lut[LX_PE_WIN_0][7] = pInfo->sgain_lut[LX_PE_WIN_1][7] = 0xFFFF0000;
				pInfo->dither_en[LX_PE_WIN_0] = pInfo->dither_en[LX_PE_WIN_1] = 0;//1:on,0:off
			}
			/**************************************************************************/
			/* main */
			/**************************************************************************/
			/* hdr10 */
			PE_HDR_LG_0_M19_RdFL(hdr_top_ctrl_05);
			//"0: hue/sat source from oetf output 1: hue/sat source from oetf input 2: hue/sat source from pcc32"
			PE_HDR_LG_0_M19_Wr01(hdr_top_ctrl_05,reg_hue_sat_prsv_src,0x2);
			/* 20180529, set 0 to avoid 1pixel shifting(bug w/a), need to fix the manual description */
			/*"1: Tone Map input source = 045gm Out 0: Tone Map input source = 045gm Input"*/
			PE_HDR_LG_0_M19_Wr01(hdr_top_ctrl_05,reg_tcm_inp_src, 0x0);
			PE_HDR_LG_0_M19_WrFL(hdr_top_ctrl_05);
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_0_M19_RdFL(hdr_gamma045_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_gamma045_ctrl_00,gamma045_enable,pInfo->gamma045_enable[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_WrFL(hdr_gamma045_ctrl_00);
			#endif
			PE_HDR_LG_0_M19_RdFL(hdr_hue_sat_ctrl);
			PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_en,pInfo->reg_hue_prsv_en[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_en,pInfo->reg_sat_prsv_en[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pInfo->reg_hue_prsv_ratio[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pInfo->reg_sat_prsv_ratio[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_WrFL(hdr_hue_sat_ctrl);
			PE_HDR_LG_0_M19_RdFL(hdr_hue_sat_alpha_ctrl);
			PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pInfo->reg_out_sgain_sel[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pInfo->reg_out_lgain_sel[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pInfo->reg_inp_s_sel[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pInfo->reg_inp_l_sel[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_WrFL(hdr_hue_sat_alpha_ctrl);
			PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_00,pInfo->lgain_lut[LX_PE_WIN_0][0]);
			PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_01,pInfo->lgain_lut[LX_PE_WIN_0][1]);
			PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_02,pInfo->lgain_lut[LX_PE_WIN_0][2]);
			PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_03,pInfo->lgain_lut[LX_PE_WIN_0][3]);
			PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_04,pInfo->lgain_lut[LX_PE_WIN_0][4]);
			PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_05,pInfo->lgain_lut[LX_PE_WIN_0][5]);
			PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_06,pInfo->lgain_lut[LX_PE_WIN_0][6]);
			PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_07,pInfo->lgain_lut[LX_PE_WIN_0][7]);
			PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_00,pInfo->sgain_lut[LX_PE_WIN_0][0]);
			PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_01,pInfo->sgain_lut[LX_PE_WIN_0][1]);
			PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_02,pInfo->sgain_lut[LX_PE_WIN_0][2]);
			PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_03,pInfo->sgain_lut[LX_PE_WIN_0][3]);
			PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_04,pInfo->sgain_lut[LX_PE_WIN_0][4]);
			PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_05,pInfo->sgain_lut[LX_PE_WIN_0][5]);
			PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_06,pInfo->sgain_lut[LX_PE_WIN_0][6]);
			PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_07,pInfo->sgain_lut[LX_PE_WIN_0][7]);
			/* sdr2hdr */
			#ifdef PE_HDR_HW_M19_DITEHER_BY_BIT_MODE
			/* "00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass */
			PE_HDR_LG_0_M19_RdFL(hdr_dither_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,dither_en,0x1);
			PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,dither_random_freeze_en,0x0);
			PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,demo_pattern_enable,0x0);
			PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,bit_mode,(pInfo->dither_en[LX_PE_WIN_0]==1)? 0x0:0x3);
			PE_HDR_LG_0_M19_WrFL(hdr_dither_ctrl_00);
			#else
			PE_HDR_LG_0_M19_RdFL(hdr_dither_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,dither_en,pInfo->dither_en[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,dither_random_freeze_en,0x0);
			PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,demo_pattern_enable,0x0);
			PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,bit_mode,0x0);
			PE_HDR_LG_0_M19_WrFL(hdr_dither_ctrl_00);
			#endif
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			//lut0,1,2 win mode
			PE_HDR_LG_0_M19_RdFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut0_ctrl_00,luminance_lut0_enable,1);
			PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut1_ctrl_00,luminance_lut1_enable,1);
			PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_llut2_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut2_ctrl_00,luminance_lut2_enable,1);
			PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_00);
			#endif
			/**************************************************************************/
			/* sub */
			/**************************************************************************/
			/* hdr10 */
			PE_HDR_LG_1_M19_RdFL(hdr_top_ctrl_05);
			//"0: hue/sat source from oetf output 1: hue/sat source from oetf input 2: hue/sat source from pcc32"
			PE_HDR_LG_1_M19_Wr01(hdr_top_ctrl_05,reg_hue_sat_prsv_src,0x2);
			/* 20180529, set 0 to avoid 1pixel shifting(bug w/a), need to fix the manual description */
			/*"1: Tone Map input source = 045gm Out 0: Tone Map input source = 045gm Input"*/
			PE_HDR_LG_1_M19_Wr01(hdr_top_ctrl_05,reg_tcm_inp_src, 0x0);
			PE_HDR_LG_1_M19_WrFL(hdr_top_ctrl_05);
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_1_M19_RdFL(hdr_gamma045_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_gamma045_ctrl_00,gamma045_enable,pInfo->gamma045_enable[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_WrFL(hdr_gamma045_ctrl_00);
			#endif
			PE_HDR_LG_1_M19_RdFL(hdr_hue_sat_ctrl);
			PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_en,pInfo->reg_hue_prsv_en[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_en,pInfo->reg_sat_prsv_en[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pInfo->reg_hue_prsv_ratio[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pInfo->reg_sat_prsv_ratio[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_WrFL(hdr_hue_sat_ctrl);
			PE_HDR_LG_1_M19_RdFL(hdr_hue_sat_alpha_ctrl);
			PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pInfo->reg_out_sgain_sel[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pInfo->reg_out_lgain_sel[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pInfo->reg_inp_s_sel[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pInfo->reg_inp_l_sel[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_WrFL(hdr_hue_sat_alpha_ctrl);
			PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_00,pInfo->lgain_lut[LX_PE_WIN_1][0]);
			PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_01,pInfo->lgain_lut[LX_PE_WIN_1][1]);
			PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_02,pInfo->lgain_lut[LX_PE_WIN_1][2]);
			PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_03,pInfo->lgain_lut[LX_PE_WIN_1][3]);
			PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_04,pInfo->lgain_lut[LX_PE_WIN_1][4]);
			PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_05,pInfo->lgain_lut[LX_PE_WIN_1][5]);
			PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_06,pInfo->lgain_lut[LX_PE_WIN_1][6]);
			PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_07,pInfo->lgain_lut[LX_PE_WIN_1][7]);
			PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_00,pInfo->sgain_lut[LX_PE_WIN_1][0]);
			PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_01,pInfo->sgain_lut[LX_PE_WIN_1][1]);
			PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_02,pInfo->sgain_lut[LX_PE_WIN_1][2]);
			PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_03,pInfo->sgain_lut[LX_PE_WIN_1][3]);
			PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_04,pInfo->sgain_lut[LX_PE_WIN_1][4]);
			PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_05,pInfo->sgain_lut[LX_PE_WIN_1][5]);
			PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_06,pInfo->sgain_lut[LX_PE_WIN_1][6]);
			PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_07,pInfo->sgain_lut[LX_PE_WIN_1][7]);
			/* sdr2hdr */
			#ifdef PE_HDR_HW_M19_DITEHER_BY_BIT_MODE
			/* "00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass */
			PE_HDR_LG_1_M19_RdFL(hdr_dither_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,dither_en,0x1);
			PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,dither_random_freeze_en,0x0);
			PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,demo_pattern_enable,0x0);
			PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,bit_mode,(pInfo->dither_en[LX_PE_WIN_1]==1)? 0x0:0x3);
			PE_HDR_LG_1_M19_WrFL(hdr_dither_ctrl_00);
			#else
			PE_HDR_LG_1_M19_RdFL(hdr_dither_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,dither_en,pInfo->dither_en[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,dither_random_freeze_en,0x0);
			PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,demo_pattern_enable,0x0);
			PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,bit_mode,0x0);
			PE_HDR_LG_1_M19_WrFL(hdr_dither_ctrl_00);
			#endif
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			//lut0,1,2 win mode
			PE_HDR_LG_1_M19_RdFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut0_ctrl_00,luminance_lut0_enable,1);
			PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut1_ctrl_00,luminance_lut1_enable,1);
			PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_llut2_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut2_ctrl_00,luminance_lut2_enable,1);
			PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_00);
			#endif
			/**************************************************************************/
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_0_M19_RdFL(hdr_3dlut_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_3dlut_ctrl_00,reg_3d_lut_en,0);
			PE_HDR_LG_0_M19_WrFL(hdr_3dlut_ctrl_00);
			#endif
			/* valid check */
			#if 0	//for debug
			if (!pstParams->resume_mode)	//normal init
			{
				refer_size[0] = refer_size[1] = refer_size[2] = refer_size[3] = PE_M19_HDR10_SIZE;
				refer_size[4] = refer_size[5] = refer_size[6] = refer_size[7] = PE_M19_S2H_SIZE;
				alloc_size[0] = (UINT32)&gPE_HDR10_M19.shdw.data->hdr_ctcp_ctrl_02 - (UINT32)&gPE_HDR10_M19.shdw.data->hdr_top_ctrl_00;
				alloc_size[1] = (UINT32)&gPE_HDR10_M19.phys.data->hdr_ctcp_ctrl_02 - (UINT32)&gPE_HDR10_M19.phys.data->hdr_top_ctrl_00;
				alloc_size[2] = (UINT32)&gPE_HDR10_2_M19.shdw.data->hdr_ctcp_ctrl_02 - (UINT32)&gPE_HDR10_2_M19.shdw.data->hdr_top_ctrl_00;
				alloc_size[3] = (UINT32)&gPE_HDR10_2_M19.phys.data->hdr_ctcp_ctrl_02 - (UINT32)&gPE_HDR10_2_M19.phys.data->hdr_top_ctrl_00;
				alloc_size[4] = (UINT32)&gPE_S2H_M19.shdw.data->hdr_llut2_ia_data - (UINT32)&gPE_S2H_M19.shdw.data->hdr_top_ctrl_00;
				alloc_size[5] = (UINT32)&gPE_S2H_M19.phys.data->hdr_llut2_ia_data - (UINT32)&gPE_S2H_M19.phys.data->hdr_top_ctrl_00;
				alloc_size[6] = (UINT32)&gPE_S2H_2_M19.shdw.data->hdr_llut2_ia_data - (UINT32)&gPE_S2H_2_M19.shdw.data->hdr_top_ctrl_00;
				alloc_size[7] = (UINT32)&gPE_S2H_2_M19.phys.data->hdr_llut2_ia_data - (UINT32)&gPE_S2H_2_M19.phys.data->hdr_top_ctrl_00;
				for (i=0; i<8; i++)
				{
					PE_PRINT_NOTI("[%d]alloc size check:%s. (%x,%x)\n",i,(refer_size[i]!=alloc_size[i])? "diff":"same", refer_size[i], alloc_size[i]);
					PE_HDR_HW_M19_BACKUP_TRACE("[%d]alloc size check:%s. (%x,%x)",i,(refer_size[i]!=alloc_size[i])? "diff":"same", refer_size[i], alloc_size[i]);
				}
			}
			#endif
			PE_PRINT_NOTI("[HW_M19Init]done.(ver:%d,resume:%d)(%s)\n",PE_HDR_DDR_M19_VERSION,pstParams->resume_mode,PE_HDR_HW_M19_DRV_VER);
			PE_HDR_HW_M19_BACKUP_TRACE("[HW_M19Init]done.(ver:%d,resume:%d)",PE_HDR_DDR_M19_VERSION,pstParams->resume_mode);
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * init hdr info
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HDR_HW_M19_InitHdrInfo(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 base_addr;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M19)
		{
			base_addr = PE_HDR_DDR_M19_BASE_ADDR;
			if (!pstParams->resume_mode)	//normal init
			{
				memset(pInfo->db_base, 0, sizeof(UINT32)*PE_HDR_DDR_M19_ITEM_V4_MAX);
				memset(pInfo->db_size, 0, sizeof(UINT32)*PE_HDR_DDR_M19_ITEM_V4_MAX);
				memset(pInfo->md_inf,  0, sizeof(LX_PE_HDR_MODE_INFO_T)*LX_PE_WIN_NUM);
				gPE_HDR_DDR_M19[0] = PE_HDR_DDR_M19_VERSION;
				gPE_HDR_DDR_M19[1] = 0x0;
				gPE_HDR_DDR_M19[2] = 0x0;
				gPE_HDR_DDR_M19[3] = 0x0;
				gPE_HDR_DDR_M19[4] = 0x0;
				gPE_HDR_DDR_M19[5] = 0x0;
				gPE_HDR_DDR_M19[6] = 0x0;
				gPE_HDR_DDR_M19[7] = 0x0;
				wmb();
				/* base */
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_INDEX]    = PE_HDR_DDR_M19_HEADER_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_A1]  = PE_HDR_DDR_M19_3LUT_A1_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_A2]  = PE_HDR_DDR_M19_3LUT_A2_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_A3]  = PE_HDR_DDR_M19_3LUT_A3_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_B1]  = PE_HDR_DDR_M19_3LUT_B1_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_B2]  = PE_HDR_DDR_M19_3LUT_B2_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_B3]  = PE_HDR_DDR_M19_3LUT_B3_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_C1]  = PE_HDR_DDR_M19_3LUT_C1_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_C2]  = PE_HDR_DDR_M19_3LUT_C2_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_C3]  = PE_HDR_DDR_M19_3LUT_C3_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_D1]  = PE_HDR_DDR_M19_3LUT_D1_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_D2]  = PE_HDR_DDR_M19_3LUT_D2_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_3LUT_D3]  = PE_HDR_DDR_M19_3LUT_D3_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_EOTF_A] = PE_HDR_DDR_M19_EOTF_A_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_EOTF_B] = PE_HDR_DDR_M19_EOTF_B_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_EOTF_C] = PE_HDR_DDR_M19_EOTF_C_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_EOTF_D] = PE_HDR_DDR_M19_EOTF_D_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_OETF_A] = PE_HDR_DDR_M19_OETF_A_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_OETF_B] = PE_HDR_DDR_M19_OETF_B_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_OETF_C] = PE_HDR_DDR_M19_OETF_C_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_OETF_D] = PE_HDR_DDR_M19_OETF_D_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_TONE_A] = PE_HDR_DDR_M19_TONE_A_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_TONE_B] = PE_HDR_DDR_M19_TONE_B_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_TONE_C] = PE_HDR_DDR_M19_TONE_C_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_TONE_D] = PE_HDR_DDR_M19_TONE_D_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_TONE_E] = PE_HDR_DDR_M19_TONE_E_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_TONE_F] = PE_HDR_DDR_M19_TONE_F_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_YLUT_A] = PE_HDR_DDR_M19_YLUT_A_BASE;
				pInfo->db_base[PE_HDR_DDR_M19_ITEM_YLUT_B] = PE_HDR_DDR_M19_YLUT_B_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_EOTF_A] = PE_HDR_DDR_2_M19_EOTF_A_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_EOTF_B] = PE_HDR_DDR_2_M19_EOTF_B_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_EOTF_C] = PE_HDR_DDR_2_M19_EOTF_C_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_EOTF_D] = PE_HDR_DDR_2_M19_EOTF_D_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_OETF_A] = PE_HDR_DDR_2_M19_OETF_A_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_OETF_B] = PE_HDR_DDR_2_M19_OETF_B_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_OETF_C] = PE_HDR_DDR_2_M19_OETF_C_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_OETF_D] = PE_HDR_DDR_2_M19_OETF_D_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_TONE_A] = PE_HDR_DDR_2_M19_TONE_A_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_TONE_B] = PE_HDR_DDR_2_M19_TONE_B_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_TONE_C] = PE_HDR_DDR_2_M19_TONE_C_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_TONE_D] = PE_HDR_DDR_2_M19_TONE_D_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_TONE_E] = PE_HDR_DDR_2_M19_TONE_E_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_TONE_F] = PE_HDR_DDR_2_M19_TONE_F_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_YLUT_A] = PE_HDR_DDR_2_M19_YLUT_A_BASE;
				pInfo->db_base[PE_HDR_DDR_2_M19_ITEM_YLUT_B] = PE_HDR_DDR_2_M19_YLUT_B_BASE;
				/* size */
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_INDEX]    = PE_HDR_DDR_M19_HEADER_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_A1]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_A2]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_A3]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_B1]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_B2]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_B3]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_C1]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_C2]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_C3]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_D1]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_D2]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_3LUT_D3]  = PE_HDR_DDR_M19_3LUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_EOTF_A] = PE_HDR_DDR_M19_EOTF_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_EOTF_B] = PE_HDR_DDR_M19_EOTF_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_EOTF_C] = PE_HDR_DDR_M19_EOTF_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_EOTF_D] = PE_HDR_DDR_M19_EOTF_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_OETF_A] = PE_HDR_DDR_M19_OETF_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_OETF_B] = PE_HDR_DDR_M19_OETF_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_OETF_C] = PE_HDR_DDR_M19_OETF_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_OETF_D] = PE_HDR_DDR_M19_OETF_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_TONE_A] = PE_HDR_DDR_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_TONE_B] = PE_HDR_DDR_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_TONE_C] = PE_HDR_DDR_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_TONE_D] = PE_HDR_DDR_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_TONE_E] = PE_HDR_DDR_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_TONE_F] = PE_HDR_DDR_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_YLUT_A] = PE_HDR_DDR_M19_YLUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_M19_ITEM_YLUT_B] = PE_HDR_DDR_M19_YLUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_EOTF_A] = PE_HDR_DDR_2_M19_EOTF_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_EOTF_B] = PE_HDR_DDR_2_M19_EOTF_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_EOTF_C] = PE_HDR_DDR_2_M19_EOTF_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_EOTF_D] = PE_HDR_DDR_2_M19_EOTF_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_OETF_A] = PE_HDR_DDR_2_M19_OETF_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_OETF_B] = PE_HDR_DDR_2_M19_OETF_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_OETF_C] = PE_HDR_DDR_2_M19_OETF_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_OETF_D] = PE_HDR_DDR_2_M19_OETF_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_TONE_A] = PE_HDR_DDR_2_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_TONE_B] = PE_HDR_DDR_2_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_TONE_C] = PE_HDR_DDR_2_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_TONE_D] = PE_HDR_DDR_2_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_TONE_E] = PE_HDR_DDR_2_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_TONE_F] = PE_HDR_DDR_2_M19_TONE_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_YLUT_A] = PE_HDR_DDR_2_M19_YLUT_SIZE;
				pInfo->db_size[PE_HDR_DDR_2_M19_ITEM_YLUT_B] = PE_HDR_DDR_2_M19_YLUT_SIZE;
				pInfo->alloc_size = PE_HDR_DDR_M19_TOTAL_SIZE;
			}
			ret = PE_FWI_M19_LoadHdrInfo(&base_addr);
			PE_HDR_HW_M19_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_M19_LoadHdrInfo() error.\n",__F__,__L__);
			PE_PRINT_NOTI("done.(resume:%d) base:0x%08x,alloc_size:0x%08x\n",\
				pstParams->resume_mode, PE_HDR_DDR_M19_BASE_ADDR, pInfo->alloc_size);
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * init hst
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HDR_HW_M19_InitHisto(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	//LX_PE_HDR_MODE_INFO_T *pInfo = _g_pe_hdr_hw_m19_info.md_inf;
	//LX_PE_HDR_OP_MD_T *p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->data[0]));
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M19)
		{
			/**************************************************************************/
			/* main */
			/**************************************************************************/
			PE_HDR_LG_0_M19_RdFL(hdr_hist_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_hist_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_hist_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_hist_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(hdr_hist_ctrl_00);
			#ifdef PE_HDR_HW_M19_WA_RD_LUT
			/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
			PE_HDR_LG_0_M19_Wr(hdr_hist_ia_ctrl,0x00018000);
			#else
			PE_HDR_LG_0_M19_RdFL(hdr_hist_ia_ctrl);
			PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_enable,   0x1);	//0:read mode,  1:normal mode
			PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_ai,       0x1);	//ai 0:disable,  1:enable
			PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_address,  0x0);	//bin address
			PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_status_address,0x0);	//min,max
			#endif
			PE_HDR_LG_0_M19_WrFL(hdr_hist_ia_ctrl);
			/* hist_src */
			PE_HDR_LG_0_M19_RdFL(hdr_top_ctrl_05);
			PE_HDR_LG_0_M19_Wr01(hdr_top_ctrl_05,reg_hist_src,0x0);//0:Y(hlg),4:MAX(RGB)(hdr10)
			PE_HDR_LG_0_M19_WrFL(hdr_top_ctrl_05);
			/**************************************************************************/
			/* sub */
			/**************************************************************************/
			PE_HDR_LG_1_M19_RdFL(hdr_hist_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_hist_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_hist_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_hist_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(hdr_hist_ctrl_00);
			#ifdef PE_HDR_HW_M19_WA_RD_LUT
			/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
			PE_HDR_LG_1_M19_Wr(hdr_hist_ia_ctrl,0x00018000);
			#else
			PE_HDR_LG_1_M19_RdFL(hdr_hist_ia_ctrl);
			PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_enable,   0x1);	//0:read mode,  1:normal mode
			PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_ai,       0x1);	//ai 0:disable,  1:enable
			PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_address,  0x0);	//bin address
			PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_status_address,0x0);	//min,max
			#endif
			PE_HDR_LG_1_M19_WrFL(hdr_hist_ia_ctrl);
			/* hist_src */
			PE_HDR_LG_1_M19_RdFL(hdr_top_ctrl_05);
			PE_HDR_LG_1_M19_Wr01(hdr_top_ctrl_05,reg_hist_src,0x0);//0:Y(hlg),4:MAX(RGB)(hdr10)
			PE_HDR_LG_1_M19_WrFL(hdr_top_ctrl_05);
			/**************************************************************************/
			/* main - SDR2HDR */
			/**************************************************************************/
			PE_HDR_LG_0_M19_RdFL(sdr2hdr_hist_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(sdr2hdr_hist_ctrl_00,hist_brm_th,0x0);//Threshold for histogram calculation (BRM_MAP)
			PE_HDR_LG_0_M19_Wr01(sdr2hdr_hist_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(sdr2hdr_hist_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(sdr2hdr_hist_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(sdr2hdr_hist_ctrl_00);
			#ifdef PE_HDR_HW_M19_WA_RD_LUT
			/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
			PE_HDR_LG_0_M19_Wr(sdr2hdr_hist_ia_ctrl,0x00018000);
			#else
			PE_HDR_LG_0_M19_RdFL(sdr2hdr_hist_ia_ctrl);
			PE_HDR_LG_0_M19_Wr01(sdr2hdr_hist_ia_ctrl,hif_hist_enable,   0x1);	//0:read mode,  1:normal mode
			PE_HDR_LG_0_M19_Wr01(sdr2hdr_hist_ia_ctrl,hif_hist_ai,       0x1);	//ai 0:disable,  1:enable
			PE_HDR_LG_0_M19_Wr01(sdr2hdr_hist_ia_ctrl,hif_hist_address,  0x0);	//bin address
			PE_HDR_LG_0_M19_Wr01(sdr2hdr_hist_ia_ctrl,hif_status_address,0x0);	//min,max
			#endif
			PE_HDR_LG_0_M19_WrFL(sdr2hdr_hist_ia_ctrl);
			/**************************************************************************/
			/* sub */
			/**************************************************************************/
			PE_HDR_LG_1_M19_RdFL(sdr2hdr_hist_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(sdr2hdr_hist_ctrl_00,hist_brm_th,0x0);//Threshold for histogram calculation (BRM_MAP)
			PE_HDR_LG_1_M19_Wr01(sdr2hdr_hist_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(sdr2hdr_hist_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(sdr2hdr_hist_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(sdr2hdr_hist_ctrl_00);
			#ifdef PE_HDR_HW_M19_WA_RD_LUT
			/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
			PE_HDR_LG_1_M19_Wr(sdr2hdr_hist_ia_ctrl,0x00018000);
			#else
			PE_HDR_LG_1_M19_RdFL(sdr2hdr_hist_ia_ctrl);
			PE_HDR_LG_1_M19_Wr01(sdr2hdr_hist_ia_ctrl,hif_hist_enable,   0x1);	//0:read mode,  1:normal mode
			PE_HDR_LG_1_M19_Wr01(sdr2hdr_hist_ia_ctrl,hif_hist_ai,       0x1);	//ai 0:disable,  1:enable
			PE_HDR_LG_1_M19_Wr01(sdr2hdr_hist_ia_ctrl,hif_hist_address,  0x0);	//bin address
			PE_HDR_LG_1_M19_Wr01(sdr2hdr_hist_ia_ctrl,hif_status_address,0x0);	//min,max
			#endif
			PE_HDR_LG_1_M19_WrFL(sdr2hdr_hist_ia_ctrl);
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * init tonemap lut
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HDR_HW_M19_InitTonemapLut(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i=0, size=0, ofst, count[6];
	volatile UINT32 *p_pe_hdr_hw_m19_ddr = NULL;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M19)
		{
			/**************************************************************************/
			/* main */
			/**************************************************************************/
			/* hdr10 tone ***********************************************/
			PE_HDR_LG_0_M19_RdFL(hdr_top_ctrl_05);
			PE_HDR_LG_0_M19_Wr01(hdr_top_ctrl_05,reg_use_equal_llut_en,0x0);//0:use own LUT,1:use G
			PE_HDR_LG_0_M19_WrFL(hdr_top_ctrl_05);
			PE_HDR_LG_0_M19_RdFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut0_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut0_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut0_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut1_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut1_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut1_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_llut2_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut2_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut2_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut2_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_00);
			/* s2h tone ***********************************************/
			PE_HDR_LG_0_M19_RdFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut0_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut0_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut0_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut1_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut1_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut1_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_llut2_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_llut2_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut2_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_llut2_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_00);
			/**************************************************************************/
			/* sub */
			/**************************************************************************/
			/* hdr10 tone ***********************************************/
			PE_HDR_LG_1_M19_RdFL(hdr_top_ctrl_05);
			PE_HDR_LG_1_M19_Wr01(hdr_top_ctrl_05,reg_use_equal_llut_en,0x0);//0:use own LUT,1:use G
			PE_HDR_LG_1_M19_WrFL(hdr_top_ctrl_05);
			PE_HDR_LG_1_M19_RdFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut0_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut0_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut0_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut1_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut1_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut1_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_llut2_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut2_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut2_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut2_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_00);
			/* s2h tone ***********************************************/
			PE_HDR_LG_1_M19_RdFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut0_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut0_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut0_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut1_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut1_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut1_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_llut2_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_llut2_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut2_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_llut2_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_00);
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			{
				/* *************************************************************************/
				/* H10 main ****************************************************************/
				/* *************************************************************************/
				/* llut0 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_data,_g_hdr_tm_lut_x_data5_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ctrl_05,_g_hdr_tm_lut_x_data5_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_05);
				/* llut0 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_data,_g_hdr_tm_lut_y_data5_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ctrl_06,_g_hdr_tm_lut_y_data5_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_06);
				/* llut1 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_data,_g_hdr_tm_lut_x_data5_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ctrl_05,_g_hdr_tm_lut_x_data5_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_05);
				/* llut1 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_data,_g_hdr_tm_lut_y_data5_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ctrl_06,_g_hdr_tm_lut_y_data5_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_06);
				/* llut2 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_data,_g_hdr_tm_lut_x_data5_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ctrl_05,_g_hdr_tm_lut_x_data5_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_05);
				/* llut2 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_data,_g_hdr_tm_lut_y_data5_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ctrl_06,_g_hdr_tm_lut_y_data5_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_06);
			}
			{
				/* *************************************************************************/
				/* H10 sub  ****************************************************************/
				/* *************************************************************************/
				/* llut0 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_data,_g_hdr_tm_lut_x_data5_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ctrl_05,_g_hdr_tm_lut_x_data5_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_05);
				/* llut0 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_data,_g_hdr_tm_lut_y_data5_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ctrl_06,_g_hdr_tm_lut_y_data5_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_06);
				/* llut1 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_data,_g_hdr_tm_lut_x_data5_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ctrl_05,_g_hdr_tm_lut_x_data5_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_05);
				/* llut1 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_data,_g_hdr_tm_lut_y_data5_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ctrl_06,_g_hdr_tm_lut_y_data5_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_06);
				/* llut2 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_data,_g_hdr_tm_lut_x_data5_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ctrl_05,_g_hdr_tm_lut_x_data5_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_05);
				/* llut2 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_data,_g_hdr_tm_lut_y_data5_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ctrl_06,_g_hdr_tm_lut_y_data5_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_06);
			}
			{
				/* *************************************************************************/
				/* S2H main ****************************************************************/
				/* *************************************************************************/
				/* llut0 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_data,_g_hdr_tm_lut_data2_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ctrl_05,_g_hdr_tm_lut_data2_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_05);
				/* llut1 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_data,_g_hdr_tm_lut_data1_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ctrl_05,_g_hdr_tm_lut_data1_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_05);
				/* llut2 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_data,_g_hdr_tm_lut_data1_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ctrl_05,_g_hdr_tm_lut_data1_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_05);
				/* *************************************************************************/
			}
			{
				/* *************************************************************************/
				/* S2H sub  ****************************************************************/
				/* *************************************************************************/
				/* llut0 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_data,_g_hdr_tm_lut_data2_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ctrl_05,_g_hdr_tm_lut_data2_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_05);
				/* llut1 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_data,_g_hdr_tm_lut_data1_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ctrl_05,_g_hdr_tm_lut_data1_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_05);
				/* llut2 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_data,_g_hdr_tm_lut_data1_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ctrl_05,_g_hdr_tm_lut_data1_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_05);
				/* *************************************************************************/
			}
			#endif
			if (!pstParams->resume_mode)	//normal init
			{
				/* *************************************************************************/
				/* main ********************************************************************/
				/* *************************************************************************/
				ofst = PE_HDR_DDR_M19_TONE_A_OFST;
				p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
				CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
				size = sizeof(UINT32)*PE_HDR_HW_M19_TM_LUT_MAX;
				i=0;
				/*A(HLG) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data1_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data1_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data1_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data1_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data2_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data2_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				wmb();
				count[0] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR_M19_TONE_A_OFST);
				count[1] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR_M19_TONE_B_OFST);
				count[2] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR_M19_TONE_C_OFST);
				count[3] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR_M19_TONE_D_OFST);
				count[4] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR_M19_TONE_E_OFST);
				count[5] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR_M19_TONE_F_OFST);
				PE_PRINT_NOTI("[TM0]of:%x,size:%d, cnt:%d,%d,%d,%d,%d,%d\n",\
					ofst,size,count[0],count[1],count[2],count[3],count[4],count[5]);
				/* *************************************************************************/
				/* sub  ********************************************************************/
				/* *************************************************************************/
				ofst = PE_HDR_DDR_2_M19_TONE_A_OFST;
				p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
				CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
				size = sizeof(UINT32)*PE_HDR_HW_M19_TM_LUT_MAX;
				i=0;
				/*A(HLG) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*A(HLG) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data3_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(H10) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data1_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data1_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data1_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data1_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data2_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*C(S2H) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data2_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_x_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*D(TEC) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_y_data5_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*E(SDR) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut0 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut0 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut1 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut1 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut2 x*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*F(DFT) lut2 y*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_tm_lut_bypass_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				wmb();
				count[0] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR_2_M19_TONE_A_OFST);
				count[1] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR_2_M19_TONE_B_OFST);
				count[2] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR_2_M19_TONE_C_OFST);
				count[3] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR_2_M19_TONE_D_OFST);
				count[4] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR_2_M19_TONE_E_OFST);
				count[5] = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR_2_M19_TONE_F_OFST);
				PE_PRINT_NOTI("[TM1]of:%x,size:%d, cnt:%d,%d,%d,%d,%d,%d\n",\
					ofst,size,count[0],count[1],count[2],count[3],count[4],count[5]);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * init ygain lut
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HDR_HW_M19_InitYgainLut(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, i=0, size=0, count[2];
	volatile UINT32 *p_pe_hdr_hw_m19_ddr = NULL;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M19)
		{
			/* *************************************************************************/
			/* main ********************************************************************/
			/* *************************************************************************/
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			if (!pstParams->resume_mode)	//normal init
			{
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_data,_g_hdr_yg_lut_data1_m19[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_YG_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ctrl_05,_g_hdr_yg_lut_data1_m19[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ctrl_05);
				//back up lut init
				memcpy((pInfo->yg_lut[LX_PE_WIN_0]), _g_hdr_yg_lut_data1_m19, sizeof(UINT32)*PE_HDR_HW_M19_YG_LUT_MAX);
			}
			else
			{
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_data,pInfo->yg_lut[LX_PE_WIN_0][i]);
					PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_YG_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ctrl_05,pInfo->yg_lut[LX_PE_WIN_0][i]);
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ctrl_05);
			}
			#endif
			//lut enable
			if (!pstParams->resume_mode)	//normal init
			{
				pInfo->yg_lut_en[LX_PE_WIN_0] = 0;//1:on,0:off
				pInfo->yg_orgsel[LX_PE_WIN_0] = 1;//1:hdr10,0:hlg
			}
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_0_M19_RdFL(hdr_ygain_lut_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_ygain_lut_ctrl_00,luminance_lut2_enable,pInfo->yg_lut_en[LX_PE_WIN_0]);
			PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ctrl_00);
			#endif
			PE_HDR_LG_0_M19_RdFL(hdr_ygain_lut_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_ygain_lut_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_ygain_lut_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_0_M19_Wr01(hdr_ygain_lut_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ctrl_00);
			//others
			PE_HDR_LG_0_M19_RdFL(hdr_rgb2y_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_rgb2y_ctrl_00,reg_rgb2yrd_en,0x1);
			PE_HDR_LG_0_M19_Wr01(hdr_rgb2y_ctrl_00,r_rgb2yrd_coef0,0x0AD9);
			PE_HDR_LG_0_M19_WrFL(hdr_rgb2y_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_rgb2y_ctrl_01);
			PE_HDR_LG_0_M19_Wr01(hdr_rgb2y_ctrl_01,r_rgb2yrd_coef1,0x00F3);
			PE_HDR_LG_0_M19_Wr01(hdr_rgb2y_ctrl_01,r_rgb2yrd_coef2,0x0434);
			PE_HDR_LG_0_M19_WrFL(hdr_rgb2y_ctrl_01);
			PE_HDR_LG_0_M19_RdFL(hdr_rgb2y_ctrl_02);
			PE_HDR_LG_0_M19_Wr01(hdr_rgb2y_ctrl_02,r_rgb2yrd_ofst0,0x0);
			PE_HDR_LG_0_M19_WrFL(hdr_rgb2y_ctrl_02);
			PE_HDR_LG_0_M19_RdFL(hdr_rgb2y_ctrl_03);
			PE_HDR_LG_0_M19_Wr01(hdr_rgb2y_ctrl_03,r_rgb2yrd_ofst3,0x0);
			PE_HDR_LG_0_M19_WrFL(hdr_rgb2y_ctrl_03);
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_0_M19_RdFL(hdr_pcc32_gain_ctrl);
			PE_HDR_LG_0_M19_Wr01(hdr_pcc32_gain_ctrl,hif_pcc32_ygain_shift,0x0);
			PE_HDR_LG_0_M19_Wr01(hdr_pcc32_gain_ctrl,hif_pcc32_ygain_orig_sel,pInfo->yg_orgsel[LX_PE_WIN_0]);//1:hdr10,0:hlg
			PE_HDR_LG_0_M19_WrFL(hdr_pcc32_gain_ctrl);
			#endif
			/* *************************************************************************/
			/* sub  ********************************************************************/
			/* *************************************************************************/
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			if (!pstParams->resume_mode)	//normal init
			{
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_data,_g_hdr_yg_lut_data1_m19[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_YG_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ctrl_05,_g_hdr_yg_lut_data1_m19[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ctrl_05);
				//back up lut init
				memcpy((pInfo->yg_lut[LX_PE_WIN_1]), _g_hdr_yg_lut_data1_m19, sizeof(UINT32)*PE_HDR_HW_M19_YG_LUT_MAX);
			}
			else
			{
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_data,pInfo->yg_lut[LX_PE_WIN_1][i]);
					PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_YG_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ctrl_05,pInfo->yg_lut[LX_PE_WIN_1][i]);
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ctrl_05);
			}
			#endif
			//lut enable
			if (!pstParams->resume_mode)	//normal init
			{
				pInfo->yg_lut_en[LX_PE_WIN_1] = 0;//1:on,0:off
				pInfo->yg_orgsel[LX_PE_WIN_1] = 1;//1:hdr10,0:hlg
			}
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_1_M19_RdFL(hdr_ygain_lut_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_ygain_lut_ctrl_00,luminance_lut2_enable,pInfo->yg_lut_en[LX_PE_WIN_1]);
			PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ctrl_00);
			#endif
			PE_HDR_LG_1_M19_RdFL(hdr_ygain_lut_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_ygain_lut_ctrl_00,window0_enable,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_ygain_lut_ctrl_00,window_acquire,0x1);//enable
			PE_HDR_LG_1_M19_Wr01(hdr_ygain_lut_ctrl_00,window_mode_enable,0x0);//enable//20160925,disable(amazon h peaking)
			PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ctrl_00);
			//others
			PE_HDR_LG_1_M19_RdFL(hdr_rgb2y_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_rgb2y_ctrl_00,reg_rgb2yrd_en,0x1);
			PE_HDR_LG_1_M19_Wr01(hdr_rgb2y_ctrl_00,r_rgb2yrd_coef0,0x0AD9);
			PE_HDR_LG_1_M19_WrFL(hdr_rgb2y_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_rgb2y_ctrl_01);
			PE_HDR_LG_1_M19_Wr01(hdr_rgb2y_ctrl_01,r_rgb2yrd_coef1,0x00F3);
			PE_HDR_LG_1_M19_Wr01(hdr_rgb2y_ctrl_01,r_rgb2yrd_coef2,0x0434);
			PE_HDR_LG_1_M19_WrFL(hdr_rgb2y_ctrl_01);
			PE_HDR_LG_1_M19_RdFL(hdr_rgb2y_ctrl_02);
			PE_HDR_LG_1_M19_Wr01(hdr_rgb2y_ctrl_02,r_rgb2yrd_ofst0,0x0);
			PE_HDR_LG_1_M19_WrFL(hdr_rgb2y_ctrl_02);
			PE_HDR_LG_1_M19_RdFL(hdr_rgb2y_ctrl_03);
			PE_HDR_LG_1_M19_Wr01(hdr_rgb2y_ctrl_03,r_rgb2yrd_ofst3,0x0);
			PE_HDR_LG_1_M19_WrFL(hdr_rgb2y_ctrl_03);
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_1_M19_RdFL(hdr_pcc32_gain_ctrl);
			PE_HDR_LG_1_M19_Wr01(hdr_pcc32_gain_ctrl,hif_pcc32_ygain_shift,0x0);
			PE_HDR_LG_1_M19_Wr01(hdr_pcc32_gain_ctrl,hif_pcc32_ygain_orig_sel,pInfo->yg_orgsel[LX_PE_WIN_1]);//1:hdr10,0:hlg
			PE_HDR_LG_1_M19_WrFL(hdr_pcc32_gain_ctrl);
			#endif
			if (!pstParams->resume_mode)	//normal init
			{
				/* *************************************************************************/
				/* main ********************************************************************/
				/* *************************************************************************/
				ofst = PE_HDR_DDR_M19_YLUT_A_OFST;
				p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
				CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
				size = sizeof(UINT32)*PE_HDR_HW_M19_YG_LUT_MAX;
				i = 0;
				/*A(HLG)*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_yg_lut_data1_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(DFT)*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_yg_lut_bypass_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				wmb();
				count[0] = PE_HDR_HW_M19_IncreaseYlutCount(LX_PE_WIN_0, PE_HDR_DDR_M19_YLUT_A_OFST);
				count[1] = PE_HDR_HW_M19_IncreaseYlutCount(LX_PE_WIN_0, PE_HDR_DDR_M19_YLUT_B_OFST);
				PE_PRINT_NOTI("[YG0]of:%x,size:%d, cnt:%d,%d\n",\
					ofst,size,count[0],count[1]);
				/* *************************************************************************/
				/* main ********************************************************************/
				/* *************************************************************************/
				ofst = PE_HDR_DDR_2_M19_YLUT_A_OFST;
				p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
				CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
				size = sizeof(UINT32)*PE_HDR_HW_M19_YG_LUT_MAX;
				i = 0;
				/*A(HLG)*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_yg_lut_data1_m19 , size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				/*B(DFT)*/memcpy((void *)(p_pe_hdr_hw_m19_ddr+i), (void *)_g_hdr_yg_lut_bypass_m19, size);i += PE_HDR_HW_M19_TM_LUT_MAX;
				wmb();
				count[0] = PE_HDR_HW_M19_IncreaseYlutCount(LX_PE_WIN_1, PE_HDR_DDR_2_M19_YLUT_A_OFST);
				count[1] = PE_HDR_HW_M19_IncreaseYlutCount(LX_PE_WIN_1, PE_HDR_DDR_2_M19_YLUT_B_OFST);
				PE_PRINT_NOTI("[YG1]of:%x,size:%d, cnt:%d,%d\n",\
					ofst,size,count[0],count[1]);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * init csc
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HDR_HW_M19_InitCsc(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M19)
		{
			/* *************************************************************************/
			/* main ********************************************************************/
			/* *************************************************************************/
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_0_M19_RdFL(hdr_csc1_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_csc1_ctrl_00,reg_csc1st_en,0x1);
			PE_HDR_LG_0_M19_WrFL(hdr_csc1_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_pcc_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_pcc_ctrl_00,reg_pcc_en,0x1);
			PE_HDR_LG_0_M19_WrFL(hdr_pcc_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_csc3_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_csc3_ctrl_00,reg_csc3rd_en,0x1);
			PE_HDR_LG_0_M19_WrFL(hdr_csc3_ctrl_00);
			PE_HDR_LG_0_M19_RdFL(hdr_csc1_ctrl_00);
			PE_HDR_LG_0_M19_Wr01(hdr_csc1_ctrl_00,reg_csc1st_en,0x1);
			PE_HDR_LG_0_M19_WrFL(hdr_csc1_ctrl_00);
			#endif
			pInfo->pre_csc[LX_PE_WIN_0].win_id = LX_PE_WIN_0;
			if (!pstParams->resume_mode)	//normal init
			{
				pInfo->pre_csc[LX_PE_WIN_0].type0 = LX_PE_HDR_CSC_Y709_GBR_LIN;
				pInfo->pre_csc[LX_PE_WIN_0].type1 = LX_PE_HDR_CSC_BYPASS;
				pInfo->pre_csc[LX_PE_WIN_0].type2 = LX_PE_HDR_CSC_GBR_Y709_LIN;
			}
			ret = PE_HDR_HW_M19_SetCsc(&(pInfo->pre_csc[LX_PE_WIN_0]));
			PE_HDR_HW_M19_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_M19_SetCsc() error.\n",__F__,__L__);
			/* init hdr type */
			_g_pe_hdr_hw_m19_info.cur_hdr_type[LX_PE_WIN_0] = PE_HDR_HW_M19_CSC_SDR_Y601;
			_g_pe_hdr_hw_m19_info.pre_hdr_type[LX_PE_WIN_0] = PE_HDR_HW_M19_CSC_NUM;
			/* *************************************************************************/
			/* sub  ********************************************************************/
			/* *************************************************************************/
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			PE_HDR_LG_1_M19_RdFL(hdr_csc1_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_csc1_ctrl_00,reg_csc1st_en,0x1);
			PE_HDR_LG_1_M19_WrFL(hdr_csc1_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_pcc_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_pcc_ctrl_00,reg_pcc_en,0x1);
			PE_HDR_LG_1_M19_WrFL(hdr_pcc_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_csc3_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_csc3_ctrl_00,reg_csc3rd_en,0x1);
			PE_HDR_LG_1_M19_WrFL(hdr_csc3_ctrl_00);
			PE_HDR_LG_1_M19_RdFL(hdr_csc1_ctrl_00);
			PE_HDR_LG_1_M19_Wr01(hdr_csc1_ctrl_00,reg_csc1st_en,0x1);
			PE_HDR_LG_1_M19_WrFL(hdr_csc1_ctrl_00);
			#endif
			pInfo->pre_csc[LX_PE_WIN_1].win_id = LX_PE_WIN_1;
			if (!pstParams->resume_mode)	//normal init
			{
				pInfo->pre_csc[LX_PE_WIN_1].type0 = LX_PE_HDR_CSC_Y709_GBR_LIN;
				pInfo->pre_csc[LX_PE_WIN_1].type1 = LX_PE_HDR_CSC_BYPASS;
				pInfo->pre_csc[LX_PE_WIN_1].type2 = LX_PE_HDR_CSC_GBR_Y709_LIN;
			}
			ret = PE_HDR_HW_M19_SetCsc(&(pInfo->pre_csc[LX_PE_WIN_1]));
			PE_HDR_HW_M19_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_M19_SetCsc() error.\n",__F__,__L__);
			/* init hdr type */
			_g_pe_hdr_hw_m19_info.cur_hdr_type[LX_PE_WIN_1] = PE_HDR_HW_M19_CSC_SDR_Y601;
			_g_pe_hdr_hw_m19_info.pre_hdr_type[LX_PE_WIN_1] = PE_HDR_HW_M19_CSC_NUM;
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * debug setting
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(HDR)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_hdr_hw_m19_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(HDR)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if(PE_KDRV_VER_M19)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(HDR)))
				{
					PE_HDR_HW_M19_DBG_PRINT("not support.\n");
				}
				else
				{
					PE_HDR_HW_M19_DBG_PRINT("not support.\n");
				}
			}
			else
			{
				PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
			}
		}
	} while(0);
	return ret;
}
/**
 * set tonemap lut
 *
 * @param   *pstParams [in] LX_PE_HDR_TONEMAP_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, invalid=0, count=0, size;
	UINT32 lut_type=0, y_31=0, y_32=0, x_31=0, x_32=0;
	UINT32 connect[2];
	volatile UINT32 *p_pe_hdr_hw_m19_ddr = NULL;
	UINT32 lut_step = PE_HDR_HW_M19_TM_LUT_MAX+PE_HDR_HW_M19_TM_LUT_MAX;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_M19_CHECK_CODE((pstParams->size!=(lut_step*3)), break, \
			"[%s,%d] pstParams->size(%d) is wrong(ref:%d).\n", __F__,__L__, pstParams->size, (lut_step*3));
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* *************************************************************************/
				/* H10   *******************************************************************/
				/* *************************************************************************/
				/* llut0 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ctrl_05,pstParams->data[i+ofst]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_05);
				/* llut0 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ctrl_06,pstParams->data[i+ofst]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_06);
				/* llut1 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ctrl_05,pstParams->data[i+ofst]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_05);
				/* llut1 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ctrl_06,pstParams->data[i+ofst]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_06);
				/* llut2 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ctrl_05,pstParams->data[i+ofst]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_05);
				/* llut2 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ctrl_06,pstParams->data[i+ofst]);
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_06);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				/* *************************************************************************/
				/* H10   *******************************************************************/
				/* *************************************************************************/
				/* llut0 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ctrl_05,pstParams->data[i+ofst]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_05);
				/* llut0 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ctrl_06,pstParams->data[i+ofst]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_06);
				/* llut1 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ctrl_05,pstParams->data[i+ofst]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_05);
				/* llut1 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ctrl_06,pstParams->data[i+ofst]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_06);
				/* llut2 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40003000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ctrl_05,pstParams->data[i+ofst]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_05);
				/* llut2 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_data,pstParams->data[i+ofst]);
					PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ctrl_06,pstParams->data[i+ofst]);
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_06);
			}
			if(PE_CHECK_WIN2(pstParams->win_id))
			{
				lut_step = PE_HDR_HW_M19_TM_LUT_MAX;
				/* *************************************************************************/
				/* S2H   *******************************************************************/
				/* *************************************************************************/
				/* llut0 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_data,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
					PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ctrl_05,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_05);
				/* llut1 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_data,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
					PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ctrl_05,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_05);
				/* llut2 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_data,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
					PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ctrl_05,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_05);
				/* *************************************************************************/
			}
			if(PE_CHECK_WIN3(pstParams->win_id))
			{
				lut_step = PE_HDR_HW_M19_TM_LUT_MAX;
				/* *************************************************************************/
				/* S2H   *******************************************************************/
				/* *************************************************************************/
				/* llut0 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_data,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
					PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ctrl_05,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_05);
				/* llut1 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_data,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
					PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ctrl_05,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_05);
				/* llut2 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_data,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
					PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ctrl_05,(pstParams->data[i+ofst]<<16|pstParams->data[i+ofst+lut_step]&0xffff));
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_05);
				/* *************************************************************************/
			}
			#endif
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				x_31 = 31;
				x_32 = 32;
				y_31 = PE_HDR_HW_M19_TM_LUT_MAX+31;
				y_32 = PE_HDR_HW_M19_TM_LUT_MAX+32;
				/* for hal_ver:2 */
				do {
					if (((pstParams->oper&0xf00)>>8) < 2)	break;//operation, [11:8]version [7:4]ctrl [3:0]hdrpath
					connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetToneConnectMode(pstParams->oper&0xf);
					ofst = PE_HDR_HW_M19_GetToneOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[TM0]c[%d]ofst invalid.\n", connect[LX_PE_WIN_0]);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*(lut_step*3);
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_M19_DBG_PRINT("%s)of:%x,size:%d, cnt[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst, size, connect[LX_PE_WIN_0], count);
					PE_HDR_HW_M19_BACKUP_TRACE("TM0]%s)v%d,o:%X,of:%x,c:%2d,d:%08x,%08x,%08x~%08x,%08x~%08x,%08x,%d:ST %d",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_M19_VERSION,pstParams->oper,\
						ofst,count,pstParams->data[0],pstParams->data[1],\
						pstParams->data[2],pstParams->data[x_31],pstParams->data[x_32],\
						pstParams->data[y_31],pstParams->data[y_32],lut_type,invalid);
				} while(0);
				/* for hal_ver:1 */
				do {
					if (((pstParams->oper&0xf00)>>8) >= 2)	break;//operation, [11:8]version [7:4]ctrl [3:0]hdrpath
					connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
					ofst = PE_HDR_HW_M19_GetToneOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[TM0]c[%d]ofst invalid.\n", connect[LX_PE_WIN_0]);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					#if 1
					/**********************************************************/
					/* 20171124, protection : check invalid */
					/* if (y[32]&0xFFFF) != 0xFFFF(65535), HDR effect LUT(2) */
					/* else if x[31] < 0xE0000000(3758096384), HDR10 or PRIME LUT(1),20171229,0xA..->0xE.. */
					/* else HLG or SDR LUT(0) */
					/* if HDR mode != LUT, tonemap skip.(except for force mode) */
					/**********************************************************/
					/* y[32] => data[i] : i = PE_HDR_HW_M19_TM_LUT_MAX+32 */
					/* x[31] => data[i] : i = 31 */
					/**********************************************************/
					do {
						if ((pstParams->data[y_32]&0xffff)!=0xffff)	{lut_type=2;break;}	//HDR effect LUT(2)
						if (pstParams->data[x_31]<0xE0000000)		{lut_type=1;break;}	//HDR10 or PRIME LUT(1),20171229,0xA..->0xE..
						lut_type=0;	//HLG or SDR LUT(0)
					} while(0);
					invalid = 0;
					switch (connect[LX_PE_WIN_0])
					{
						case PE_HDR_HW_M19_CONNECT_MODE_S2H:
							if (((pstParams->oper)&0xf)!=0x1)	invalid = 1;//hdrpath
							else if (lut_type!=2)				invalid = 2;
							break;
						case PE_HDR_HW_M19_CONNECT_MODE_H10:
						case PE_HDR_HW_M19_CONNECT_MODE_TEC:
							if (lut_type!=1)					invalid = 3;
							break;
						case PE_HDR_HW_M19_CONNECT_MODE_SDR:
						case PE_HDR_HW_M19_CONNECT_MODE_HLG:
						default:
							if (lut_type!=0)					invalid = 4;
							break;
					}
					/* if invalid and no-force mode */
					if (invalid>0 && (((pstParams->oper)&0xf)!=0xf))
					{
						PE_HDR_HW_M19_BACKUP_TRACE("TM0]%s]v%d,o:%X,of:%x,c:%2d,d:%08x,%08x,%08x~%08x,%08x~%08x,%08x,%d:SK %d",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_M19_VERSION,pstParams->oper,\
							ofst,count,pstParams->data[0],pstParams->data[1],\
							pstParams->data[2],pstParams->data[x_31],pstParams->data[x_32],\
							pstParams->data[y_31],pstParams->data[y_32],lut_type,invalid);
						break;
					}
					#else
					/* protection : check invalid lut(except for sdr,s2h) */
					/* protection : add sdr case(20171110)(SDCSRT-159) */
					do {
						invalid = 0;
						//if (connect[LX_PE_WIN_0] == PE_HDR_HW_M19_CONNECT_MODE_SDR)	break;
						if (connect[LX_PE_WIN_0] == PE_HDR_HW_M19_CONNECT_MODE_S2H)	break;
						i = lut_step*3-1;
						if ((pstParams->data[i]&0xffff)==0xffff)		break;
						invalid = 1;
						PE_HDR_HW_M19_BACKUP_TRACE("TM0]%s]v%d,o,s:%X,%d,of:%x,c[%d],d:%08x,%08x,%08x~%08x,SKIP 0",\
							PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_M19_VERSION,pstParams->oper,pstParams->size,\
							ofst,connect[LX_PE_WIN_0],\
							pstParams->data[0],pstParams->data[1],pstParams->data[2],pstParams->data[i]);
					} while(0);
					if (invalid)	break;
					/**********************************************************/
					/* protection : check invalid oper for s2h */
					do {
						invalid = 0;
						if (connect[LX_PE_WIN_0] != PE_HDR_HW_M19_CONNECT_MODE_S2H)	break;
						if (((pstParams->oper)&0xf)==0x1)							break;//if sdr2hdr lut, ok
						invalid = 1;
						PE_HDR_HW_M19_BACKUP_TRACE("TM0]%s]v%d,o,s:%X,%d,of:%x,c[%d],d:%08x,%08x,%08x~%08x,SKIP 1",\
							PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_M19_VERSION,pstParams->oper,pstParams->size,\
							ofst,connect[LX_PE_WIN_0],\
							pstParams->data[0],pstParams->data[1],pstParams->data[2],pstParams->data[i]);
					} while(0);
					if (invalid)	break;
					/**********************************************************/
					#endif
					size = sizeof(UINT32)*(lut_step*3);
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_M19_DBG_PRINT("%s]of:%x,size:%d, cnt[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst, size, connect[LX_PE_WIN_0], count);
					PE_HDR_HW_M19_BACKUP_TRACE("TM0]%s]v%d,o:%X,of:%x,c:%2d,d:%08x,%08x,%08x~%08x,%08x~%08x,%08x,%d:ST %d",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_M19_VERSION,pstParams->oper,\
						ofst,count,pstParams->data[0],pstParams->data[1],\
						pstParams->data[2],pstParams->data[x_31],pstParams->data[x_32],\
						pstParams->data[y_31],pstParams->data[y_32],lut_type,invalid);
				} while(0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				x_31 = 31;
				x_32 = 32;
				y_31 = PE_HDR_HW_M19_TM_LUT_MAX+31;
				y_32 = PE_HDR_HW_M19_TM_LUT_MAX+32;
				/* for hal_ver:2 */
				do {
					if (((pstParams->oper&0xf00)>>8) < 2)	break;//operation, [11:8]version [7:4]ctrl [3:0]hdrpath
					connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetToneConnectMode(pstParams->oper&0xf);
					ofst = PE_HDR_HW_M19_GetToneOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[TM1]c[%d]ofst invalid.\n", connect[LX_PE_WIN_1]);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*(lut_step*3);
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_M19_DBG_PRINT("%s)of:%x,size:%d, cnt[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst, size, connect[LX_PE_WIN_1], count);
					PE_HDR_HW_M19_BACKUP_TRACE("TM1]%s)v%d,o:%X,of:%x,c:%2d,d:%08x,%08x,%08x~%08x,%08x~%08x,%08x,%d:ST %d",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_M19_VERSION,pstParams->oper,\
						ofst,count,pstParams->data[0],pstParams->data[1],\
						pstParams->data[2],pstParams->data[x_31],pstParams->data[x_32],\
						pstParams->data[y_31],pstParams->data[y_32],lut_type,invalid);
				} while(0);
				/* for hal_ver:1 */
				do {
					if (((pstParams->oper&0xf00)>>8) >= 2)	break;//operation, [11:8]version [7:4]ctrl [3:0]hdrpath
					connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_1);
					ofst = PE_HDR_HW_M19_GetToneOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[TM1]c[%d]ofst invalid.\n", connect[LX_PE_WIN_1]);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					#if 1
					/**********************************************************/
					/* 20171124, protection : check invalid */
					/* if (y[32]&0xFFFF) != 0xFFFF(65535), HDR effect LUT(2) */
					/* else if x[31] < 0xE0000000(3758096384), HDR10 or PRIME LUT(1),20171229,0xA..->0xE.. */
					/* else HLG or SDR LUT(0) */
					/* if HDR mode != LUT, tonemap skip.(except for force mode) */
					/**********************************************************/
					/* y[32] => data[i] : i = PE_HDR_HW_M19_TM_LUT_MAX+32 */
					/* x[31] => data[i] : i = 31 */
					/**********************************************************/
					do {
						if ((pstParams->data[y_32]&0xffff)!=0xffff)	{lut_type=2;break;}	//HDR effect LUT(2)
						if (pstParams->data[x_31]<0xE0000000)		{lut_type=1;break;}	//HDR10 or PRIME LUT(1),20171229,0xA..->0xE..
						lut_type=0;	//HLG or SDR LUT(0)
					} while(0);
					invalid = 0;
					switch (connect[LX_PE_WIN_1])
					{
						case PE_HDR_HW_M19_CONNECT_MODE_S2H:
							if (((pstParams->oper)&0xf)!=0x1)	invalid = 1;//hdrpath
							else if (lut_type!=2)				invalid = 2;
							break;
						case PE_HDR_HW_M19_CONNECT_MODE_H10:
						case PE_HDR_HW_M19_CONNECT_MODE_TEC:
							if (lut_type!=1)					invalid = 3;
							break;
						case PE_HDR_HW_M19_CONNECT_MODE_SDR:
						case PE_HDR_HW_M19_CONNECT_MODE_HLG:
						default:
							if (lut_type!=0)					invalid = 4;
							break;
					}
					/* if invalid and no-force mode */
					if (invalid>0 && (((pstParams->oper)&0xf)!=0xf))
					{
						PE_HDR_HW_M19_BACKUP_TRACE("TM1]%s]v%d,o:%X,of:%x,c:%2d,d:%08x,%08x,%08x~%08x,%08x~%08x,%08x,%d:SK %d",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_M19_VERSION,pstParams->oper,\
							ofst,count,pstParams->data[0],pstParams->data[1],\
							pstParams->data[2],pstParams->data[x_31],pstParams->data[x_32],\
							pstParams->data[y_31],pstParams->data[y_32],lut_type,invalid);
						break;
					}
					#else
					/**********************************************************/
					/* protection : check invalid lut(except for sdr,s2h) */
					/* protection : add sdr case(20171110)(SDCSRT-159) */
					do {
						invalid = 0;
						//if (connect[LX_PE_WIN_1] == PE_HDR_HW_M19_CONNECT_MODE_SDR)	break;
						if (connect[LX_PE_WIN_1] == PE_HDR_HW_M19_CONNECT_MODE_S2H)	break;
						i = lut_step*3-1;
						if ((pstParams->data[i]&0xffff)==0xffff)		break;
						invalid = 1;
						PE_HDR_HW_M19_BACKUP_TRACE("TM1]%s]v%d,o,s:%X,%d,of:%x,c[%d],d:%08x,%08x,%08x~%08x,SKIP 0",\
							PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_M19_VERSION,pstParams->oper,pstParams->size,\
							ofst,connect[LX_PE_WIN_1],\
							pstParams->data[0],pstParams->data[1],pstParams->data[2],pstParams->data[i]);
					} while(0);
					if (invalid)	break;
					/**********************************************************/
					/* protection : check invalid oper for s2h */
					do {
						invalid = 0;
						if (connect[LX_PE_WIN_1] != PE_HDR_HW_M19_CONNECT_MODE_S2H)	break;
						if (((pstParams->oper)&0xf)==0x1)							break;//if sdr2hdr lut, ok
						invalid = 1;
						PE_HDR_HW_M19_BACKUP_TRACE("TM1]%s]v%d,o,s:%X,%d,of:%x,c[%d],d:%08x,%08x,%08x~%08x,SKIP 1",\
							PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_M19_VERSION,pstParams->oper,pstParams->size,\
							ofst,connect[LX_PE_WIN_1],\
							pstParams->data[0],pstParams->data[1],pstParams->data[2],pstParams->data[i]);
					} while(0);
					if (invalid)	break;
					/**********************************************************/
					#endif
					size = sizeof(UINT32)*(lut_step*3);
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_M19_IncreaseToneCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_M19_DBG_PRINT("%s]of:%x,size:%d, cnt[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst, size, connect[LX_PE_WIN_1], count);
					PE_HDR_HW_M19_BACKUP_TRACE("TM1]%s]v%d,o:%X,of:%x,c:%2d,d:%08x,%08x,%08x~%08x,%08x~%08x,%08x,%d:ST %d",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_M19_VERSION,pstParams->oper,\
						ofst,count,pstParams->data[0],pstParams->data[1],\
						pstParams->data[2],pstParams->data[x_31],pstParams->data[x_32],\
						pstParams->data[y_31],pstParams->data[y_32],lut_type,invalid);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get tonemap lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_TONEMAP_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 i=0, ofst=0;
	UINT32 lut_step = PE_HDR_HW_M19_TM_LUT_MAX+PE_HDR_HW_M19_TM_LUT_MAX;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_M19_CHECK_CODE((pstParams->size!=(lut_step*3)), break, \
			"[%s,%d] pstParams->size(%d) is wrong(ref:%d).\n", __F__,__L__, pstParams->size, (lut_step*3));
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				/* llut0 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40005000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut0_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut0_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut0_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut0_ctrl_05);
				/* llut0 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut0_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut0_ctrl_06);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut0_ctrl_06);
				/* llut1 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40005000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut1_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut1_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut1_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut1_ctrl_05);
				/* llut1 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut1_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut1_ctrl_06);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut1_ctrl_06);
				/* llut2 x ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40005000);//ai,x
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut2_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut2_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut2_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut2_ctrl_05);
				/* llut2 y ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut2_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut2_ctrl_06);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut2_ctrl_06);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				/* llut0 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40005000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut0_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut0_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut0_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut0_ctrl_05);
				/* llut0 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut0_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut0_ctrl_06);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut0_ctrl_06);
				/* llut1 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40005000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut1_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut1_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut1_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut1_ctrl_05);
				/* llut1 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut1_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut1_ctrl_06);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut1_ctrl_06);
				/* llut2 x ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40005000);//ai,x
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut2_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut2_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut2_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut2_ctrl_05);
				/* llut2 y ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_M19_TM_LUT_MAX;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut2_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut2_ctrl_06);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut2_ctrl_06);
			}
			if(PE_CHECK_WIN2(win_id))
			{
				lut_step = PE_HDR_HW_M19_TM_LUT_MAX;
				/* llut0 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut0_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut0_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_HDR_LG_0_M19_Rd(hdr_llut0_ia_data)&0xffff;
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut0_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut0_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_HDR_LG_0_M19_Rd(hdr_llut0_ctrl_05)&0xffff;
				/* llut1 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut1_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut1_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_HDR_LG_0_M19_Rd(hdr_llut1_ia_data)&0xffff;
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut1_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut1_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_HDR_LG_0_M19_Rd(hdr_llut1_ctrl_05)&0xffff;
				/* llut2 ***********************************************/
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_llut2_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut2_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_HDR_LG_0_M19_Rd(hdr_llut2_ia_data)&0xffff;
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_0_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_llut2_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_0_M19_Rd(hdr_llut2_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_HDR_LG_0_M19_Rd(hdr_llut2_ctrl_05)&0xffff;
			}
			if(PE_CHECK_WIN3(win_id))
			{
				lut_step = PE_HDR_HW_M19_TM_LUT_MAX;
				/* llut0 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut0_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut0_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_HDR_LG_1_M19_Rd(hdr_llut0_ia_data)&0xffff;
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut0_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut0_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_HDR_LG_1_M19_Rd(hdr_llut0_ctrl_05)&0xffff;
				/* llut1 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut1_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut1_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_HDR_LG_1_M19_Rd(hdr_llut1_ia_data)&0xffff;
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut1_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut1_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_HDR_LG_1_M19_Rd(hdr_llut1_ctrl_05)&0xffff;
				/* llut2 ***********************************************/
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				ofst += (PE_HDR_HW_M19_TM_LUT_MAX<<1);
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_llut2_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_TM_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut2_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_HDR_LG_1_M19_Rd(hdr_llut2_ia_data)&0xffff;
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_HDR_LG_1_M19_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_TM_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_llut2_ctrl_05);
				pstParams->data[i+ofst] = PE_HDR_LG_1_M19_Rd(hdr_llut2_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_HDR_LG_1_M19_Rd(hdr_llut2_ctrl_05)&0xffff;
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set ygain lut
 *
 * @param   *pstParams [in] LX_PE_HDR_YGAIN_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, i, size;
	UINT32 connect[2];
	UINT32 lut_step = PE_HDR_HW_M19_YG_LUT_MAX;
	volatile UINT32 *p_pe_hdr_hw_m19_ddr = NULL;
	//PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_M19_CHECK_CODE(pstParams->size!=lut_step, break, \
			"[%s,%d] pstParams->size(%d) is wrong.\n", __F__,__L__, pstParams->size);
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_data,pstParams->data[i]);
					PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_YG_LUT_MAX-1;
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ctrl_05,pstParams->data[i]);
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ctrl_05);
				//back up lut init
				memcpy((pInfo->yg_lut[LX_PE_WIN_0]), pstParams->data, sizeof(UINT32)*lut_step);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_data,pstParams->data[i]);
					PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_YG_LUT_MAX-1;
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ctrl_05,pstParams->data[i]);
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ctrl_05);
				//back up lut init
				memcpy((pInfo->yg_lut[LX_PE_WIN_1]), pstParams->data, sizeof(UINT32)*lut_step);
			}
			#endif
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
				do {
					ofst = PE_HDR_HW_M19_GetYlutOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[YG0]c[%d]ofst invalid.\n", connect[LX_PE_WIN_0]);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					i = PE_HDR_HW_M19_IncreaseYlutCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[%s]of:%x,size:%d c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]), \
						ofst, size, connect[LX_PE_WIN_0], i);
					PE_HDR_HW_M19_BACKUP_TRACE("[YG0][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_M19_VERSION,\
						pstParams->oper, pstParams->size,  \
						ofst, connect[LX_PE_WIN_0], i, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_1);
				do {
					ofst = PE_HDR_HW_M19_GetYlutOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[YG1]c[%d]ofst invalid.\n", connect[LX_PE_WIN_1]);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					i = PE_HDR_HW_M19_IncreaseYlutCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[%s]of:%x,size:%d c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]), \
						ofst, size, connect[LX_PE_WIN_1], i);
					PE_HDR_HW_M19_BACKUP_TRACE("[YG1][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_M19_VERSION,\
						pstParams->oper, pstParams->size,  \
						ofst, connect[LX_PE_WIN_1], i, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get ygain lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_YGAIN_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 i=0;
	UINT32 lut_step = PE_HDR_HW_M19_YG_LUT_MAX;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_M19_CHECK_CODE(pstParams->size!=lut_step, break, \
			"[%s,%d] pstParams->size(%d) is wrong.\n", __F__,__L__, pstParams->size);
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_0_M19_RdFL(hdr_ygain_lut_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_ygain_lut_ia_data);
					pstParams->data[i] = PE_HDR_LG_0_M19_Rd(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_HDR_LG_0_M19_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_YG_LUT_MAX-1;
				PE_HDR_LG_0_M19_RdFL(hdr_ygain_lut_ctrl_05);
				pstParams->data[i] = PE_HDR_LG_0_M19_Rd(hdr_ygain_lut_ctrl_05);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				PE_HDR_LG_1_M19_RdFL(hdr_ygain_lut_ia_data);
				#endif
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_ygain_lut_ia_data);
					pstParams->data[i] = PE_HDR_LG_1_M19_Rd(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_HDR_LG_1_M19_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_M19_YG_LUT_MAX-1;
				PE_HDR_LG_1_M19_RdFL(hdr_ygain_lut_ctrl_05);
				pstParams->data[i] = PE_HDR_LG_1_M19_Rd(hdr_ygain_lut_ctrl_05);
			}
			if(PE_CHECK_WIN2(win_id))
			{
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)	pstParams->data[i] = pInfo->yg_lut[LX_PE_WIN_0][i];
				pstParams->data[i] = pInfo->yg_lut[LX_PE_WIN_0][PE_HDR_HW_M19_YG_LUT_MAX-1];
			}
			if(PE_CHECK_WIN3(win_id))
			{
				for(i=0;i<(PE_HDR_HW_M19_YG_LUT_MAX-1);i++)	pstParams->data[i] = pInfo->yg_lut[LX_PE_WIN_1][i];
				pstParams->data[i] = pInfo->yg_lut[LX_PE_WIN_1][PE_HDR_HW_M19_YG_LUT_MAX-1];
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set csc
 *
 * @param   *pstParams [in] LX_PE_HDR_CSC_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetCsc(LX_PE_HDR_CSC_T *pstParams)
{
	int ret = RET_OK;
	const UINT16 *p_co0,*p_of0,*p_co1,*p_co2,*p_of2;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("set pstParams[%d]\n"\
			"tp0:%d, coef:%04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x, ofs:%04x,%04x,%04x, %04x,%04x,%04x\n"\
			"tp1:%d, coef:%04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x, ofs:%04x,%04x,%04x, %04x,%04x,%04x\n"\
			"tp2:%d, coef:%04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x, ofs:%04x,%04x,%04x, %04x,%04x,%04x\n",\
			pstParams->win_id,pstParams->type0,\
			pstParams->coef0[0],pstParams->coef0[1],pstParams->coef0[2],\
			pstParams->coef0[3],pstParams->coef0[4],pstParams->coef0[5],\
			pstParams->coef0[6],pstParams->coef0[7],pstParams->coef0[8],\
			pstParams->ofst0[0],pstParams->ofst0[1],pstParams->ofst0[2],\
			pstParams->ofst0[3],pstParams->ofst0[4],pstParams->ofst0[5],\
			pstParams->type1,\
			pstParams->coef1[0],pstParams->coef1[1],pstParams->coef1[2],\
			pstParams->coef1[3],pstParams->coef1[4],pstParams->coef1[5],\
			pstParams->coef1[6],pstParams->coef1[7],pstParams->coef1[8],\
			pstParams->ofst1[0],pstParams->ofst1[1],pstParams->ofst1[2],\
			pstParams->ofst1[3],pstParams->ofst1[4],pstParams->ofst1[5],\
			pstParams->type2,\
			pstParams->coef2[0],pstParams->coef2[1],pstParams->coef2[2],\
			pstParams->coef2[3],pstParams->coef2[4],pstParams->coef2[5],\
			pstParams->coef2[6],pstParams->coef2[7],pstParams->coef2[8],\
			pstParams->ofst2[0],pstParams->ofst2[1],pstParams->ofst2[2],\
			pstParams->ofst2[3],pstParams->ofst2[4],pstParams->ofst2[5]);
		if(PE_KDRV_VER_M19)
		{
			switch (pstParams->type0)
			{
				case LX_PE_HDR_CSC_MANUAL:
					p_co0 = pstParams->coef0;
					p_of0 = pstParams->ofst0;
					break;
				case LX_PE_HDR_CSC_Y709_GBR_LIN:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_709_lin;
					p_of0 = _g_pe_hdr_hw_m19_csc_y2gbr_ofst_lin;
					break;
				case LX_PE_HDR_CSC_Y709_GBR_EXP:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_709_exp;
					p_of0 = _g_pe_hdr_hw_m19_csc_y2gbr_ofst_exp;
					break;
				case LX_PE_HDR_CSC_2020_GBR_EXP:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_n2020_exp;
					p_of0 = _g_pe_hdr_hw_m19_csc_y2gbr_ofst_exp;
					break;
				case LX_PE_HDR_CSC_BYPASS:
				default:
					p_co0 = _g_pe_hdr_hw_m19_csc_mtrx_bypass;
					p_of0 = _g_pe_hdr_hw_m19_csc_ofst_bypass;
					break;
			}
			switch (pstParams->type1)
			{
				case LX_PE_HDR_CSC_MANUAL:
					p_co1 = pstParams->coef1;
					break;
				case LX_PE_HDR_CSC_BYPASS:
					p_co1 = _g_pe_hdr_hw_m19_csc_mtrx_bypass;
					break;
				case LX_PE_HDR_CSC_DEFAULT:
				case LX_PE_HDR_CSC_DEFAULT1:
				default:
					p_co1 = _g_pe_hdr_hw_m19_pcc_mtrx_default;
					break;
			}
			switch (pstParams->type2)
			{
				case LX_PE_HDR_CSC_MANUAL:
					p_co2 = pstParams->coef2;
					p_of2 = pstParams->ofst2;
					break;
				case LX_PE_HDR_CSC_GBR_Y709_LIN:
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_709_linea;
					p_of2 = _g_pe_hdr_hw_m19_csc_gbr2y_ofst_linr;
					break;
				case LX_PE_HDR_CSC_GBR_Y709_LIM:
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_709_limit;
					p_of2 = _g_pe_hdr_hw_m19_csc_gbr2y_ofst_limt;
					break;
				case LX_PE_HDR_CSC_GBR_2020_LIM:
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_n2020_lim;
					p_of2 = _g_pe_hdr_hw_m19_csc_gbr2y_ofst_limt;
					break;
				case LX_PE_HDR_CSC_BYPASS:
				default:
					p_co2 = _g_pe_hdr_hw_m19_csc_mtrx_bypass;
					p_of2 = _g_pe_hdr_hw_m19_csc_ofst_bypass;
					break;
			}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* pcc */
				PE_HDR_LG_0_M19_QWr02(hdr_pcc_ctrl_01,r_pcc_coef0,GET_BITS(p_co1[0],0,16),r_pcc_coef1,GET_BITS(p_co1[1],0,16));
				PE_HDR_LG_0_M19_QWr02(hdr_pcc_ctrl_02,r_pcc_coef2,GET_BITS(p_co1[2],0,16),r_pcc_coef3,GET_BITS(p_co1[3],0,16));
				PE_HDR_LG_0_M19_QWr02(hdr_pcc_ctrl_03,r_pcc_coef4,GET_BITS(p_co1[4],0,16),r_pcc_coef5,GET_BITS(p_co1[5],0,16));
				PE_HDR_LG_0_M19_QWr02(hdr_pcc_ctrl_04,r_pcc_coef6,GET_BITS(p_co1[6],0,16),r_pcc_coef7,GET_BITS(p_co1[7],0,16));
				PE_HDR_LG_0_M19_QWr01(hdr_pcc_ctrl_05,r_pcc_coef8,GET_BITS(p_co1[8],0,16));
				#if 0	//use csc task
				/* csc1 */
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_01,r_csc1st_coef0,GET_BITS(p_co0[0],0,15),r_csc1st_coef1,GET_BITS(p_co0[1],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_02,r_csc1st_coef2,GET_BITS(p_co0[2],0,15),r_csc1st_coef3,GET_BITS(p_co0[3],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_03,r_csc1st_coef4,GET_BITS(p_co0[4],0,15),r_csc1st_coef5,GET_BITS(p_co0[5],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_04,r_csc1st_coef6,GET_BITS(p_co0[6],0,15),r_csc1st_coef7,GET_BITS(p_co0[7],0,15));
				PE_HDR_LG_0_M19_QWr01(hdr_csc1_ctrl_05,r_csc1st_coef8,GET_BITS(p_co0[8],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_06,r_csc1st_ofst0,GET_BITS(p_of0[0],0,11),r_csc1st_ofst1,GET_BITS(p_of0[1],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_07,r_csc1st_ofst2,GET_BITS(p_of0[2],0,11),r_csc1st_ofst3,GET_BITS(p_of0[3],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_08,r_csc1st_ofst4,GET_BITS(p_of0[4],0,11),r_csc1st_ofst5,GET_BITS(p_of0[5],0,11));
				/* csc3 */
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_01,r_csc3rd_coef0,GET_BITS(p_co2[0],0,15),r_csc3rd_coef1,GET_BITS(p_co2[1],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_02,r_csc3rd_coef2,GET_BITS(p_co2[2],0,15),r_csc3rd_coef3,GET_BITS(p_co2[3],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_03,r_csc3rd_coef4,GET_BITS(p_co2[4],0,15),r_csc3rd_coef5,GET_BITS(p_co2[5],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_04,r_csc3rd_coef6,GET_BITS(p_co2[6],0,15),r_csc3rd_coef7,GET_BITS(p_co2[7],0,15));
				PE_HDR_LG_0_M19_QWr01(hdr_csc3_ctrl_05,r_csc3rd_coef8,GET_BITS(p_co2[8],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,GET_BITS(p_of2[0],0,11),r_csc3rd_ofst1,GET_BITS(p_of2[1],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,GET_BITS(p_of2[2],0,11),r_csc3rd_ofst3,GET_BITS(p_of2[3],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,GET_BITS(p_of2[4],0,11),r_csc3rd_ofst5,GET_BITS(p_of2[5],0,11));
				#endif
				memcpy(&(pInfo->pre_csc[LX_PE_WIN_0]), pstParams, sizeof(LX_PE_HDR_CSC_T));
				PE_HDR_HW_M19_BACKUP_TRACE("[PCC0]t1:%d, %04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x",\
					pstParams->type1,pstParams->coef1[0],pstParams->coef1[1],pstParams->coef1[2],\
					pstParams->coef1[3],pstParams->coef1[4],pstParams->coef1[5],\
					pstParams->coef1[6],pstParams->coef1[7],pstParams->coef1[8]);
			}
			#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
			if(PE_CHECK_WIN0(pstParams->win_id))
			#else
			if(PE_CHECK_WIN1(pstParams->win_id))
			#endif
			{
				/* pcc */
				PE_HDR_LG_1_M19_QWr02(hdr_pcc_ctrl_01,r_pcc_coef0,GET_BITS(p_co1[0],0,16),r_pcc_coef1,GET_BITS(p_co1[1],0,16));
				PE_HDR_LG_1_M19_QWr02(hdr_pcc_ctrl_02,r_pcc_coef2,GET_BITS(p_co1[2],0,16),r_pcc_coef3,GET_BITS(p_co1[3],0,16));
				PE_HDR_LG_1_M19_QWr02(hdr_pcc_ctrl_03,r_pcc_coef4,GET_BITS(p_co1[4],0,16),r_pcc_coef5,GET_BITS(p_co1[5],0,16));
				PE_HDR_LG_1_M19_QWr02(hdr_pcc_ctrl_04,r_pcc_coef6,GET_BITS(p_co1[6],0,16),r_pcc_coef7,GET_BITS(p_co1[7],0,16));
				PE_HDR_LG_1_M19_QWr01(hdr_pcc_ctrl_05,r_pcc_coef8,GET_BITS(p_co1[8],0,16));
				#if 0	//use csc task
				/* csc1 */
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_01,r_csc1st_coef0,GET_BITS(p_co0[0],0,15),r_csc1st_coef1,GET_BITS(p_co0[1],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_02,r_csc1st_coef2,GET_BITS(p_co0[2],0,15),r_csc1st_coef3,GET_BITS(p_co0[3],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_03,r_csc1st_coef4,GET_BITS(p_co0[4],0,15),r_csc1st_coef5,GET_BITS(p_co0[5],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_04,r_csc1st_coef6,GET_BITS(p_co0[6],0,15),r_csc1st_coef7,GET_BITS(p_co0[7],0,15));
				PE_HDR_LG_1_M19_QWr01(hdr_csc1_ctrl_05,r_csc1st_coef8,GET_BITS(p_co0[8],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_06,r_csc1st_ofst0,GET_BITS(p_of0[0],0,11),r_csc1st_ofst1,GET_BITS(p_of0[1],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_07,r_csc1st_ofst2,GET_BITS(p_of0[2],0,11),r_csc1st_ofst3,GET_BITS(p_of0[3],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_08,r_csc1st_ofst4,GET_BITS(p_of0[4],0,11),r_csc1st_ofst5,GET_BITS(p_of0[5],0,11));
				/* csc3 */
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_01,r_csc3rd_coef0,GET_BITS(p_co2[0],0,15),r_csc3rd_coef1,GET_BITS(p_co2[1],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_02,r_csc3rd_coef2,GET_BITS(p_co2[2],0,15),r_csc3rd_coef3,GET_BITS(p_co2[3],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_03,r_csc3rd_coef4,GET_BITS(p_co2[4],0,15),r_csc3rd_coef5,GET_BITS(p_co2[5],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_04,r_csc3rd_coef6,GET_BITS(p_co2[6],0,15),r_csc3rd_coef7,GET_BITS(p_co2[7],0,15));
				PE_HDR_LG_1_M19_QWr01(hdr_csc3_ctrl_05,r_csc3rd_coef8,GET_BITS(p_co2[8],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,GET_BITS(p_of2[0],0,11),r_csc3rd_ofst1,GET_BITS(p_of2[1],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,GET_BITS(p_of2[2],0,11),r_csc3rd_ofst3,GET_BITS(p_of2[3],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,GET_BITS(p_of2[4],0,11),r_csc3rd_ofst5,GET_BITS(p_of2[5],0,11));
				#endif
				memcpy(&(pInfo->pre_csc[LX_PE_WIN_1]), pstParams, sizeof(LX_PE_HDR_CSC_T));
				#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
				// no need to print backup
				#else
				PE_HDR_HW_M19_BACKUP_TRACE("[PCC1]t1:%d, %04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x",\
					pstParams->type1,pstParams->coef1[0],pstParams->coef1[1],pstParams->coef1[2],\
					pstParams->coef1[3],pstParams->coef1[4],pstParams->coef1[5],\
					pstParams->coef1[6],pstParams->coef1[7],pstParams->coef1[8]);
				#endif
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get csc
 *
 * @param   *pstParams [in] LX_PE_HDR_CSC_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetCsc(LX_PE_HDR_CSC_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT16 *p_co0,*p_of0,*p_co1,*p_of1,*p_co2,*p_of2;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))//check register
			{
				pstParams->type0 = pInfo->pre_csc[LX_PE_WIN_0].type0;
				pstParams->type1 = pInfo->pre_csc[LX_PE_WIN_0].type1;
				pstParams->type2 = pInfo->pre_csc[LX_PE_WIN_0].type2;
				p_co0 = pstParams->coef0;	p_of0 = pstParams->ofst0;
				p_co1 = pstParams->coef1;	p_of1 = pstParams->ofst1;
				p_co2 = pstParams->coef2;	p_of2 = pstParams->ofst2;
				/* csc1 */
				PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
				PE_HDR_LG_0_M19_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
				/* pcc */
				PE_HDR_LG_0_M19_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
				PE_HDR_LG_0_M19_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
				PE_HDR_LG_0_M19_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
				PE_HDR_LG_0_M19_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
				PE_HDR_LG_0_M19_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
				p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
				/* csc3 */
				PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_01,r_csc3rd_coef0,p_co2[0],r_csc3rd_coef1,p_co2[1]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_02,r_csc3rd_coef2,p_co2[2],r_csc3rd_coef3,p_co2[3]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_03,r_csc3rd_coef4,p_co2[4],r_csc3rd_coef5,p_co2[5]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_04,r_csc3rd_coef6,p_co2[6],r_csc3rd_coef7,p_co2[7]);
				PE_HDR_LG_0_M19_QRd01(hdr_csc3_ctrl_05,r_csc3rd_coef8,p_co2[8]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,p_of2[0],r_csc3rd_ofst1,p_of2[1]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,p_of2[2],r_csc3rd_ofst3,p_of2[3]);
				PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,p_of2[4],r_csc3rd_ofst5,p_of2[5]);
			}
			if(PE_CHECK_WIN1(win_id))//check register
			{
				pstParams->type0 = pInfo->pre_csc[LX_PE_WIN_1].type0;
				pstParams->type1 = pInfo->pre_csc[LX_PE_WIN_1].type1;
				pstParams->type2 = pInfo->pre_csc[LX_PE_WIN_1].type2;
				p_co0 = pstParams->coef0;	p_of0 = pstParams->ofst0;
				p_co1 = pstParams->coef1;	p_of1 = pstParams->ofst1;
				p_co2 = pstParams->coef2;	p_of2 = pstParams->ofst2;
				/* csc1 */
				PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
				PE_HDR_LG_1_M19_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
				/* pcc */
				PE_HDR_LG_1_M19_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
				PE_HDR_LG_1_M19_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
				PE_HDR_LG_1_M19_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
				PE_HDR_LG_1_M19_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
				PE_HDR_LG_1_M19_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
				p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
				/* csc3 */
				PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_01,r_csc3rd_coef0,p_co2[0],r_csc3rd_coef1,p_co2[1]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_02,r_csc3rd_coef2,p_co2[2],r_csc3rd_coef3,p_co2[3]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_03,r_csc3rd_coef4,p_co2[4],r_csc3rd_coef5,p_co2[5]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_04,r_csc3rd_coef6,p_co2[6],r_csc3rd_coef7,p_co2[7]);
				PE_HDR_LG_1_M19_QRd01(hdr_csc3_ctrl_05,r_csc3rd_coef8,p_co2[8]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,p_of2[0],r_csc3rd_ofst1,p_of2[1]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,p_of2[2],r_csc3rd_ofst3,p_of2[3]);
				PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,p_of2[4],r_csc3rd_ofst5,p_of2[5]);
			}
			if(PE_CHECK_WIN2(win_id))//check pre value
			{
				memcpy(pstParams, &pInfo->pre_csc[LX_PE_WIN_0], sizeof(LX_PE_HDR_CSC_T));
			}
			if(PE_CHECK_WIN3(win_id))//check pre value
			{
				memcpy(pstParams, &pInfo->pre_csc[LX_PE_WIN_1], sizeof(LX_PE_HDR_CSC_T));
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_HDR_HW_M19_DBG_PRINT("get pstParams[%d]\n"\
			"tp0:%d, coef:%04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x, ofs:%04x,%04x,%04x, %04x,%04x,%04x\n"\
			"tp1:%d, coef:%04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x, ofs:%04x,%04x,%04x, %04x,%04x,%04x\n"\
			"tp2:%d, coef:%04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x, ofs:%04x,%04x,%04x, %04x,%04x,%04x\n",\
			pstParams->win_id,pstParams->type0,\
			pstParams->coef0[0],pstParams->coef0[1],pstParams->coef0[2],\
			pstParams->coef0[3],pstParams->coef0[4],pstParams->coef0[5],\
			pstParams->coef0[6],pstParams->coef0[7],pstParams->coef0[8],\
			pstParams->ofst0[0],pstParams->ofst0[1],pstParams->ofst0[2],\
			pstParams->ofst0[3],pstParams->ofst0[4],pstParams->ofst0[5],\
			pstParams->type1,\
			pstParams->coef1[0],pstParams->coef1[1],pstParams->coef1[2],\
			pstParams->coef1[3],pstParams->coef1[4],pstParams->coef1[5],\
			pstParams->coef1[6],pstParams->coef1[7],pstParams->coef1[8],\
			pstParams->ofst1[0],pstParams->ofst1[1],pstParams->ofst1[2],\
			pstParams->ofst1[3],pstParams->ofst1[4],pstParams->ofst1[5],\
			pstParams->type2,\
			pstParams->coef2[0],pstParams->coef2[1],pstParams->coef2[2],\
			pstParams->coef2[3],pstParams->coef2[4],pstParams->coef2[5],\
			pstParams->coef2[6],pstParams->coef2[7],pstParams->coef2[8],\
			pstParams->ofst2[0],pstParams->ofst2[1],pstParams->ofst2[2],\
			pstParams->ofst2[3],pstParams->ofst2[4],pstParams->ofst2[5]);
	} while(0);
	return ret;
}
/**
 * set csc mode
 *
 * @param   *pCfg [in] PE_TSK_M19_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetCscMode(PE_TSK_M19_CFG_T *pCfg)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	UINT32 cur_hdr_type[2];
	PE_TSK_M19_OPR_T *p_opr = &(pCfg->opr);
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	UINT32 connect[2];
	LX_PE_HDR_OP_MD_T *p_op0 = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_0].data[0]));
	LX_PE_HDR_OP_MD_T *p_op1 = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_1].data[0]));
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_M19)
		{
			if (p_opr->pause_task == PE_TSK_M19_RUN_STOP_MODE)	break;
			/* *************************************************************************/
			/* main ********************************************************************/
			/* *************************************************************************/
			connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
			if (connect[LX_PE_WIN_0] == PE_HDR_HW_M19_CONNECT_MODE_H10 || \
				connect[LX_PE_WIN_0] == PE_HDR_HW_M19_CONNECT_MODE_HLG)
			{
				//colorimetry, 0:601,1:709,2:2020
				if (p_op0->colmtry == 2)		cur_hdr_type[LX_PE_WIN_0] = PE_HDR_HW_M19_CSC_HDR_2020;
				else if (p_op0->colmtry == 1)	cur_hdr_type[LX_PE_WIN_0] = PE_HDR_HW_M19_CSC_HDR_Y709;
				else							cur_hdr_type[LX_PE_WIN_0] = PE_HDR_HW_M19_CSC_HDR_Y601;
			}
			else	//SDR,S2H,DOLBY etc.
			{
				//colorimetry, 0:601,1:709,2:2020
				if (p_op0->colmtry == 2)		cur_hdr_type[LX_PE_WIN_0] = PE_HDR_HW_M19_CSC_SDR_2020;
				else if (p_op0->colmtry == 1)	cur_hdr_type[LX_PE_WIN_0] = PE_HDR_HW_M19_CSC_SDR_Y709;
				else							cur_hdr_type[LX_PE_WIN_0] = PE_HDR_HW_M19_CSC_SDR_Y601;
			}
			pInfo->cur_hdr_type[LX_PE_WIN_0] = cur_hdr_type[LX_PE_WIN_0];
			if (pInfo->pre_hdr_type[LX_PE_WIN_0] != cur_hdr_type[LX_PE_WIN_0])
			{
				PE_HDR_HW_M19_DBG_PRINT("[inf0] c:%d, co,ht,hc,cm:%d,%d,%d,%d\n", connect[LX_PE_WIN_0], \
					p_op0->connect, p_op0->hdrtone, p_op0->hdrcase, p_op0->colmtry);
				PE_HDR_HW_M19_DBG_PRINT("[set0] opr:%d, hdr_type:%d -> %d\n",\
					p_opr->pause_task, pInfo->pre_hdr_type[LX_PE_WIN_0], cur_hdr_type[LX_PE_WIN_0]);
				ret = PE_HDR_HW_M19_SetCscReg(LX_PE_WIN_0, cur_hdr_type[LX_PE_WIN_0]);
				PE_HDR_HW_M19_CHECK_CODE(ret, break, \
					"[%s,%d] PE_HDR_HW_M19_SetCscReg() error.\n",__F__,__L__);
				pInfo->pre_hdr_type[LX_PE_WIN_0] = cur_hdr_type[LX_PE_WIN_0];
			}
			/* **********************************************************/
			if(_g_hdr_hw_m19_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_HDR_HW_M19_DBG_PRINT("[stat0] c:%d, co,ht,hc,cm:%d,%d,%d,%d\n", connect[LX_PE_WIN_0], \
						p_op0->connect, p_op0->hdrtone, p_op0->hdrcase, p_op0->colmtry);
					PE_HDR_HW_M19_DBG_PRINT("[stat0] opr:%d, hdr_type:%d\n",\
						p_opr->pause_task, cur_hdr_type[LX_PE_WIN_0]);
					count=0;
				}
				count++;
			}
			/* *************************************************************************/
			/* sub  ********************************************************************/
			/* *************************************************************************/
			connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_1);
			if (connect[LX_PE_WIN_1] == PE_HDR_HW_M19_CONNECT_MODE_H10 || \
				connect[LX_PE_WIN_1] == PE_HDR_HW_M19_CONNECT_MODE_HLG)
			{
				//colorimetry, 0:601,1:709,2:2020
				if (p_op1->colmtry == 2)		cur_hdr_type[LX_PE_WIN_1] = PE_HDR_HW_M19_CSC_HDR_2020;
				else if (p_op1->colmtry == 1)	cur_hdr_type[LX_PE_WIN_1] = PE_HDR_HW_M19_CSC_HDR_Y709;
				else							cur_hdr_type[LX_PE_WIN_1] = PE_HDR_HW_M19_CSC_HDR_Y601;
			}
			else	//SDR,S2H,DOLBY etc.
			{
				//colorimetry, 0:601,1:709,2:2020
				if (p_op1->colmtry == 2)		cur_hdr_type[LX_PE_WIN_1] = PE_HDR_HW_M19_CSC_SDR_2020;
				else if (p_op1->colmtry == 1)	cur_hdr_type[LX_PE_WIN_1] = PE_HDR_HW_M19_CSC_SDR_Y709;
				else							cur_hdr_type[LX_PE_WIN_1] = PE_HDR_HW_M19_CSC_SDR_Y601;
			}
			pInfo->cur_hdr_type[LX_PE_WIN_1] = cur_hdr_type[LX_PE_WIN_1];
			if (pInfo->pre_hdr_type[LX_PE_WIN_1] != cur_hdr_type[LX_PE_WIN_1])
			{
				PE_HDR_HW_M19_DBG_PRINT("[inf1] c:%d, co,ht,hc,cm:%d,%d,%d,%d\n", connect[LX_PE_WIN_1], \
					p_op1->connect, p_op1->hdrtone, p_op1->hdrcase, p_op1->colmtry);
				PE_HDR_HW_M19_DBG_PRINT("[set1] opr:%d, hdr_type:%d -> %d\n",\
					p_opr->pause_task, pInfo->pre_hdr_type[LX_PE_WIN_1], cur_hdr_type[LX_PE_WIN_1]);
				ret = PE_HDR_HW_M19_SetCscReg(LX_PE_WIN_1, cur_hdr_type[LX_PE_WIN_1]);
				PE_HDR_HW_M19_CHECK_CODE(ret, break, \
					"[%s,%d] PE_HDR_HW_M19_SetCscReg() error.\n",__F__,__L__);
				pInfo->pre_hdr_type[LX_PE_WIN_1] = cur_hdr_type[LX_PE_WIN_1];
			}
			/* **********************************************************/
			if(_g_hdr_hw_m19_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_HDR_HW_M19_DBG_PRINT("[stat1] c:%d, co,ht,hc,cm:%d,%d,%d,%d\n", connect[LX_PE_WIN_1], \
						p_op1->connect, p_op1->hdrtone, p_op1->hdrcase, p_op1->colmtry);
					PE_HDR_HW_M19_DBG_PRINT("[stat1] opr:%d, hdr_type:%d\n",\
						p_opr->pause_task, cur_hdr_type[LX_PE_WIN_1]);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set csc register
 *
 * @param   win_id [in] UINT32
 * @param   type [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HDR_HW_M19_SetCscReg(UINT32 win_id, UINT32 type)
{
	int ret = RET_OK;
	const UINT16 *p_co0,*p_of0,*p_co2,*p_of2;
	do{
		if(PE_KDRV_VER_M19)
		{
			/** HDR csc (TVPQ team request) 20180504
			SDR BT601  YCbCr601toRGB940(Limited -> Limited), RGB940toYCbCr601(Limited -> Limited)
			SDR BT709  YCbCr709toRGB940(Limited -> Limited), RGB940toYCbCr709(Limited -> Limited)
			SDR BT2020 YCbCr2020toRGB1023(Limited -> Limited),  RGB1023toYCbCr2020(Limited -> Limited)
			HDR BT601  YCbCr601toRGB1023(Limited -> Full),   RGB1023toYCbCr601(Full -> Limited)
			HDR BT709  YCbCr709toRGB1023(Limited -> Full),   RGB1023toYCbCr709(Full -> Limited)
			HDR BT2020 YCbCr2020toRGB1023(Limited -> Full),  RGB1023toYCbCr2020(Full -> Limited)
			*/
			/* coeff */
			switch (type)
			{
				case PE_HDR_HW_M19_CSC_HDR_2020:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_n2020_exp;
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_n2020_lim;
					break;
				case PE_HDR_HW_M19_CSC_HDR_Y709:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_709_exp;
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_709_limit;
					break;
				case PE_HDR_HW_M19_CSC_HDR_Y601:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_601_exp;
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_601_limit;
					break;
				case PE_HDR_HW_M19_CSC_SDR_2020:
				case PE_HDR_HW_M19_CSC_S2H_2020:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_n2020_lin;//20170215,65_960->exp,20180504,exp->lin
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_n2020_lin;//20170215,65_960->lim,20180504,lim->lin
					break;
				case PE_HDR_HW_M19_CSC_SDR_Y709:
				case PE_HDR_HW_M19_CSC_S2H_Y709:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_709_64_940;//20170222,65_960->64_940
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_709_64_940;//20170222,65_960->64_940
					break;
				case PE_HDR_HW_M19_CSC_SDR_Y601:
				case PE_HDR_HW_M19_CSC_S2H_Y601:
				default:
					p_co0 = _g_pe_hdr_hw_m19_csc_y2gbr_601_64_940;//20170222,65_960->64_940
					p_co2 = _g_pe_hdr_hw_m19_csc_gbr2y_601_64_940;//20170222,65_960->64_940
					break;
			}
			/* offset */
			switch (type)
			{
				case PE_HDR_HW_M19_CSC_HDR_2020:
				case PE_HDR_HW_M19_CSC_HDR_Y709:
				case PE_HDR_HW_M19_CSC_HDR_Y601:
					p_of0 = _g_pe_hdr_hw_m19_csc_y2gbr_ofst_exp;
					p_of2 = _g_pe_hdr_hw_m19_csc_gbr2y_ofst_limt;
					break;
				case PE_HDR_HW_M19_CSC_SDR_2020:
				case PE_HDR_HW_M19_CSC_S2H_2020:
				case PE_HDR_HW_M19_CSC_SDR_Y709:
				case PE_HDR_HW_M19_CSC_S2H_Y709:
				case PE_HDR_HW_M19_CSC_SDR_Y601:
				case PE_HDR_HW_M19_CSC_S2H_Y601:
				default:
					p_of0 = _g_pe_hdr_hw_m19_csc_y2gbr_ofst_lin;
					p_of2 = _g_pe_hdr_hw_m19_csc_gbr2y_ofst_linr;
					break;
			}
			if (win_id == LX_PE_WIN_0)
			{
				/* csc1 */
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_01,r_csc1st_coef0,GET_BITS(p_co0[0],0,15),r_csc1st_coef1,GET_BITS(p_co0[1],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_02,r_csc1st_coef2,GET_BITS(p_co0[2],0,15),r_csc1st_coef3,GET_BITS(p_co0[3],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_03,r_csc1st_coef4,GET_BITS(p_co0[4],0,15),r_csc1st_coef5,GET_BITS(p_co0[5],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_04,r_csc1st_coef6,GET_BITS(p_co0[6],0,15),r_csc1st_coef7,GET_BITS(p_co0[7],0,15));
				PE_HDR_LG_0_M19_QWr01(hdr_csc1_ctrl_05,r_csc1st_coef8,GET_BITS(p_co0[8],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_06,r_csc1st_ofst0,GET_BITS(p_of0[0],0,11),r_csc1st_ofst1,GET_BITS(p_of0[1],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_07,r_csc1st_ofst2,GET_BITS(p_of0[2],0,11),r_csc1st_ofst3,GET_BITS(p_of0[3],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_08,r_csc1st_ofst4,GET_BITS(p_of0[4],0,11),r_csc1st_ofst5,GET_BITS(p_of0[5],0,11));
				/* csc3 */
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_01,r_csc3rd_coef0,GET_BITS(p_co2[0],0,15),r_csc3rd_coef1,GET_BITS(p_co2[1],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_02,r_csc3rd_coef2,GET_BITS(p_co2[2],0,15),r_csc3rd_coef3,GET_BITS(p_co2[3],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_03,r_csc3rd_coef4,GET_BITS(p_co2[4],0,15),r_csc3rd_coef5,GET_BITS(p_co2[5],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_04,r_csc3rd_coef6,GET_BITS(p_co2[6],0,15),r_csc3rd_coef7,GET_BITS(p_co2[7],0,15));
				PE_HDR_LG_0_M19_QWr01(hdr_csc3_ctrl_05,r_csc3rd_coef8,GET_BITS(p_co2[8],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,GET_BITS(p_of2[0],0,11),r_csc3rd_ofst1,GET_BITS(p_of2[1],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,GET_BITS(p_of2[2],0,11),r_csc3rd_ofst3,GET_BITS(p_of2[3],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,GET_BITS(p_of2[4],0,11),r_csc3rd_ofst5,GET_BITS(p_of2[5],0,11));
				/* csc1(s2h) */
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_01,r_csc1st_coef0,GET_BITS(p_co0[0],0,15),r_csc1st_coef1,GET_BITS(p_co0[1],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_02,r_csc1st_coef2,GET_BITS(p_co0[2],0,15),r_csc1st_coef3,GET_BITS(p_co0[3],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_03,r_csc1st_coef4,GET_BITS(p_co0[4],0,15),r_csc1st_coef5,GET_BITS(p_co0[5],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_04,r_csc1st_coef6,GET_BITS(p_co0[6],0,15),r_csc1st_coef7,GET_BITS(p_co0[7],0,15));
				PE_HDR_LG_0_M19_QWr01(hdr_csc1_ctrl_05,r_csc1st_coef8,GET_BITS(p_co0[8],0,15));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_06,r_csc1st_ofst0,GET_BITS(p_of0[0],0,11),r_csc1st_ofst1,GET_BITS(p_of0[1],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_07,r_csc1st_ofst2,GET_BITS(p_of0[2],0,11),r_csc1st_ofst3,GET_BITS(p_of0[3],0,11));
				PE_HDR_LG_0_M19_QWr02(hdr_csc1_ctrl_08,r_csc1st_ofst4,GET_BITS(p_of0[4],0,11),r_csc1st_ofst5,GET_BITS(p_of0[5],0,11));
			}
			else
			{
				/* csc1 */
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_01,r_csc1st_coef0,GET_BITS(p_co0[0],0,15),r_csc1st_coef1,GET_BITS(p_co0[1],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_02,r_csc1st_coef2,GET_BITS(p_co0[2],0,15),r_csc1st_coef3,GET_BITS(p_co0[3],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_03,r_csc1st_coef4,GET_BITS(p_co0[4],0,15),r_csc1st_coef5,GET_BITS(p_co0[5],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_04,r_csc1st_coef6,GET_BITS(p_co0[6],0,15),r_csc1st_coef7,GET_BITS(p_co0[7],0,15));
				PE_HDR_LG_1_M19_QWr01(hdr_csc1_ctrl_05,r_csc1st_coef8,GET_BITS(p_co0[8],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_06,r_csc1st_ofst0,GET_BITS(p_of0[0],0,11),r_csc1st_ofst1,GET_BITS(p_of0[1],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_07,r_csc1st_ofst2,GET_BITS(p_of0[2],0,11),r_csc1st_ofst3,GET_BITS(p_of0[3],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_08,r_csc1st_ofst4,GET_BITS(p_of0[4],0,11),r_csc1st_ofst5,GET_BITS(p_of0[5],0,11));
				/* csc3 */
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_01,r_csc3rd_coef0,GET_BITS(p_co2[0],0,15),r_csc3rd_coef1,GET_BITS(p_co2[1],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_02,r_csc3rd_coef2,GET_BITS(p_co2[2],0,15),r_csc3rd_coef3,GET_BITS(p_co2[3],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_03,r_csc3rd_coef4,GET_BITS(p_co2[4],0,15),r_csc3rd_coef5,GET_BITS(p_co2[5],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_04,r_csc3rd_coef6,GET_BITS(p_co2[6],0,15),r_csc3rd_coef7,GET_BITS(p_co2[7],0,15));
				PE_HDR_LG_1_M19_QWr01(hdr_csc3_ctrl_05,r_csc3rd_coef8,GET_BITS(p_co2[8],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,GET_BITS(p_of2[0],0,11),r_csc3rd_ofst1,GET_BITS(p_of2[1],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,GET_BITS(p_of2[2],0,11),r_csc3rd_ofst3,GET_BITS(p_of2[3],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,GET_BITS(p_of2[4],0,11),r_csc3rd_ofst5,GET_BITS(p_of2[5],0,11));
				/* csc1(s2h) */
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_01,r_csc1st_coef0,GET_BITS(p_co0[0],0,15),r_csc1st_coef1,GET_BITS(p_co0[1],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_02,r_csc1st_coef2,GET_BITS(p_co0[2],0,15),r_csc1st_coef3,GET_BITS(p_co0[3],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_03,r_csc1st_coef4,GET_BITS(p_co0[4],0,15),r_csc1st_coef5,GET_BITS(p_co0[5],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_04,r_csc1st_coef6,GET_BITS(p_co0[6],0,15),r_csc1st_coef7,GET_BITS(p_co0[7],0,15));
				PE_HDR_LG_1_M19_QWr01(hdr_csc1_ctrl_05,r_csc1st_coef8,GET_BITS(p_co0[8],0,15));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_06,r_csc1st_ofst0,GET_BITS(p_of0[0],0,11),r_csc1st_ofst1,GET_BITS(p_of0[1],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_07,r_csc1st_ofst2,GET_BITS(p_of0[2],0,11),r_csc1st_ofst3,GET_BITS(p_of0[3],0,11));
				PE_HDR_LG_1_M19_QWr02(hdr_csc1_ctrl_08,r_csc1st_ofst4,GET_BITS(p_of0[4],0,11),r_csc1st_ofst5,GET_BITS(p_of0[5],0,11));
			}
			/* debug */
			PE_HDR_HW_M19_DBG_PRINT("[set] hdr wid:%d, type:%d\n", win_id, type);
			PE_HDR_HW_M19_DBG_PRINT("[set] co0:%04x,%04x,%04x,%04x,%04x,%04x,%04x,%04x,%04x\n", \
				p_co0[0], p_co0[1], p_co0[2], p_co0[3], p_co0[4], p_co0[5], p_co0[6], p_co0[7], p_co0[8]);
			PE_HDR_HW_M19_DBG_PRINT("[set] of0:%04x,%04x,%04x,%04x,%04x,%04x\n", \
				p_of0[0], p_of0[1], p_of0[2], p_of0[3], p_of0[4], p_of0[5]);
			PE_HDR_HW_M19_DBG_PRINT("[set] co2:%04x,%04x,%04x,%04x,%04x,%04x,%04x,%04x,%04x\n", \
				p_co2[0], p_co2[1], p_co2[2], p_co2[3], p_co2[4], p_co2[5], p_co2[6], p_co2[7], p_co2[8]);
			PE_HDR_HW_M19_DBG_PRINT("[set] of2:%04x,%04x,%04x,%04x,%04x,%04x\n", \
				p_of2[0], p_of2[1], p_of2[2], p_of2[3], p_of2[4], p_of2[5]);
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get csc info
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetCscInfo(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0;
	UINT32 *p_co0 = _g_pe_hdr_hw_m19_info.hdr_co0;
	UINT32 *p_of0 = _g_pe_hdr_hw_m19_info.hdr_of0;
	UINT32 *p_co1 = _g_pe_hdr_hw_m19_info.hdr_co1;
	UINT32 *p_of1 = _g_pe_hdr_hw_m19_info.hdr_of1;
	UINT32 *p_co2 = _g_pe_hdr_hw_m19_info.hdr_co2;
	UINT32 *p_of2 = _g_pe_hdr_hw_m19_info.hdr_of2;
	UINT32 *p_co3 = _g_pe_hdr_hw_m19_info.hdr_co3;
	UINT32 *p_of3 = _g_pe_hdr_hw_m19_info.hdr_of3;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;

#define PE_HDR_M19_PRINT_START		"START_OF_PRINT"
#define PE_HDR_M19_PRINT_RESERVED	"RESERVED"
#define PE_HDR_M19_PRINT_END		"END_OF_PRINT"
#define PE_HDR_M19_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_HDR_M19_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE,"   [0x%02x] %s\n",(_item),#_item);_action;break
#define PE_HDR_M19_CASE_SPRINT(_cnt,_action,_buf,fmt,args...)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break
#define PE_HDR_M19_DFLT_SPRINT(_action,_buf,fmt,args...)		\
	default:snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		if(PE_KDRV_VER_M19)
		{
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]==PE_HDR_HW_M19_CSC_DISPLAY)
			{
				switch (rd_cnt)
				{
					PE_HDR_M19_CASE_SPRINT( 0, rd_cnt++, buffer, PE_HDR_M19_PRINT_START);
					PE_HDR_M19_CASE_PRMENU( 1, rd_cnt++, buffer, PE_HDR_HW_M19_CSC_RD_INF0);
					PE_HDR_M19_CASE_PRMENU( 2, rd_cnt++, buffer, PE_HDR_HW_M19_CSC_RD_INF1);
					PE_HDR_M19_CASE_PRMENU( 3, rd_cnt++, buffer, PE_HDR_HW_M19_CSC_RD_INF2);
					PE_HDR_M19_CASE_PRMENU( 4, rd_cnt++, buffer, PE_HDR_HW_M19_CSC_RD_INF3);
					PE_HDR_M19_CASE_SPRINT( 5, rd_cnt++, buffer, PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_DFLT_SPRINT(rd_cnt=0, buffer, PE_HDR_M19_PRINT_END);
				}
			}
			else if (pstParams->data[0]==PE_HDR_HW_M19_CSC_RD_INF0)
			{
				if (rd_cnt==0)
				{
					/* csc1 */
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
					PE_HDR_LG_0_M19_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
					/* pcc */
					PE_HDR_LG_0_M19_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
					PE_HDR_LG_0_M19_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
					PE_HDR_LG_0_M19_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
					PE_HDR_LG_0_M19_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
					PE_HDR_LG_0_M19_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
					/* csc3 */
					PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_01,r_csc3rd_coef0,p_co2[0],r_csc3rd_coef1,p_co2[1]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_02,r_csc3rd_coef2,p_co2[2],r_csc3rd_coef3,p_co2[3]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_03,r_csc3rd_coef4,p_co2[4],r_csc3rd_coef5,p_co2[5]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_04,r_csc3rd_coef6,p_co2[6],r_csc3rd_coef7,p_co2[7]);
					PE_HDR_LG_0_M19_QRd01(hdr_csc3_ctrl_05,r_csc3rd_coef8,p_co2[8]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,p_of2[0],r_csc3rd_ofst1,p_of2[1]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,p_of2[2],r_csc3rd_ofst3,p_of2[3]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,p_of2[4],r_csc3rd_ofst5,p_of2[5]);
					/* csc1(s2h) */
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co3[0],r_csc1st_coef1,p_co3[1]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co3[2],r_csc1st_coef3,p_co3[3]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co3[4],r_csc1st_coef5,p_co3[5]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co3[6],r_csc1st_coef7,p_co3[7]);
					PE_HDR_LG_0_M19_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co3[8]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of3[0],r_csc1st_ofst1,p_of3[1]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of3[2],r_csc1st_ofst3,p_of3[3]);
					PE_HDR_LG_0_M19_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of3[4],r_csc1st_ofst5,p_of3[5]);
				}
				switch(rd_cnt)
				{
					PE_HDR_M19_CASE_SPRINT( 0,rd_cnt++,buffer,PE_HDR_M19_PRINT_START);
					PE_HDR_M19_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"(0)hdr csc1 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_0].type0,pInfo->cur_hdr_type[LX_PE_WIN_0],pInfo->pre_hdr_type[LX_PE_WIN_0]);
					PE_HDR_M19_CASE_SPRINT( 3,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT( 4,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[0], p_co0[1], p_co0[2], p_of0[0], p_of0[3]);
					PE_HDR_M19_CASE_SPRINT( 5,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[3], p_co0[4], p_co0[5], p_of0[1], p_of0[4]);
					PE_HDR_M19_CASE_SPRINT( 6,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[6], p_co0[7], p_co0[8], p_of0[2], p_of0[5]);
					PE_HDR_M19_CASE_SPRINT( 7,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT( 8,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT( 9,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(10,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(11,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(12,rd_cnt++,buffer,\
						"(0)hdr pcc type:%d\n",pInfo->pre_csc[LX_PE_WIN_0].type1);
					PE_HDR_M19_CASE_SPRINT(13,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(14,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[0], p_co1[1], p_co1[2], p_of1[0], p_of1[3]);
					PE_HDR_M19_CASE_SPRINT(15,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[3], p_co1[4], p_co1[5], p_of1[1], p_of1[4]);
					PE_HDR_M19_CASE_SPRINT(16,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[6], p_co1[7], p_co1[8], p_of1[2], p_of1[5]);
					PE_HDR_M19_CASE_SPRINT(17,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(18,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(19,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(20,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(21,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(22,rd_cnt++,buffer,\
						"(0)hdr csc3 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_0].type2,pInfo->cur_hdr_type[LX_PE_WIN_0],pInfo->pre_hdr_type[LX_PE_WIN_0]);
					PE_HDR_M19_CASE_SPRINT(23,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(24,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[0], p_co2[1], p_co2[2], p_of2[0], p_of2[3]);
					PE_HDR_M19_CASE_SPRINT(25,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[3], p_co2[4], p_co2[5], p_of2[1], p_of2[4]);
					PE_HDR_M19_CASE_SPRINT(26,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[6], p_co2[7], p_co2[8], p_of2[2], p_of2[5]);
					PE_HDR_M19_CASE_SPRINT(27,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(28,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(29,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(30,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(31,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(32,rd_cnt++,buffer,\
						"(0)hdr csc1(s2h) type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_0].type0,pInfo->cur_hdr_type[LX_PE_WIN_0],pInfo->pre_hdr_type[LX_PE_WIN_0]);
					PE_HDR_M19_CASE_SPRINT(33,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(34,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[0], p_co3[1], p_co3[2], p_of3[0], p_of3[3]);
					PE_HDR_M19_CASE_SPRINT(35,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[3], p_co3[4], p_co3[5], p_of3[1], p_of3[4]);
					PE_HDR_M19_CASE_SPRINT(36,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[6], p_co3[7], p_co3[8], p_of3[2], p_of3[5]);
					PE_HDR_M19_CASE_SPRINT(37,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(38,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(39,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(40,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_DFLT_SPRINT(rd_cnt=0,buffer,PE_HDR_M19_PRINT_END);
				}
			}
			else if (pstParams->data[0]==PE_HDR_HW_M19_CSC_RD_INF1)
			{
				if (rd_cnt==0)
				{
					/* csc1 */
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
					PE_HDR_LG_1_M19_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
					/* pcc */
					PE_HDR_LG_1_M19_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
					PE_HDR_LG_1_M19_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
					PE_HDR_LG_1_M19_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
					PE_HDR_LG_1_M19_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
					PE_HDR_LG_1_M19_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
					/* csc3 */
					PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_01,r_csc3rd_coef0,p_co2[0],r_csc3rd_coef1,p_co2[1]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_02,r_csc3rd_coef2,p_co2[2],r_csc3rd_coef3,p_co2[3]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_03,r_csc3rd_coef4,p_co2[4],r_csc3rd_coef5,p_co2[5]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_04,r_csc3rd_coef6,p_co2[6],r_csc3rd_coef7,p_co2[7]);
					PE_HDR_LG_1_M19_QRd01(hdr_csc3_ctrl_05,r_csc3rd_coef8,p_co2[8]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,p_of2[0],r_csc3rd_ofst1,p_of2[1]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,p_of2[2],r_csc3rd_ofst3,p_of2[3]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,p_of2[4],r_csc3rd_ofst5,p_of2[5]);
					/* csc1(s2h) */
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co3[0],r_csc1st_coef1,p_co3[1]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co3[2],r_csc1st_coef3,p_co3[3]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co3[4],r_csc1st_coef5,p_co3[5]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co3[6],r_csc1st_coef7,p_co3[7]);
					PE_HDR_LG_1_M19_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co3[8]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of3[0],r_csc1st_ofst1,p_of3[1]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of3[2],r_csc1st_ofst3,p_of3[3]);
					PE_HDR_LG_1_M19_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of3[4],r_csc1st_ofst5,p_of3[5]);
				}
				switch(rd_cnt)
				{
					PE_HDR_M19_CASE_SPRINT( 0,rd_cnt++,buffer,PE_HDR_M19_PRINT_START);
					PE_HDR_M19_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"(1)hdr csc1 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_1].type0,pInfo->cur_hdr_type[LX_PE_WIN_1],pInfo->pre_hdr_type[LX_PE_WIN_1]);
					PE_HDR_M19_CASE_SPRINT( 3,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT( 4,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[0], p_co0[1], p_co0[2], p_of0[0], p_of0[3]);
					PE_HDR_M19_CASE_SPRINT( 5,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[3], p_co0[4], p_co0[5], p_of0[1], p_of0[4]);
					PE_HDR_M19_CASE_SPRINT( 6,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[6], p_co0[7], p_co0[8], p_of0[2], p_of0[5]);
					PE_HDR_M19_CASE_SPRINT( 7,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT( 8,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT( 9,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(10,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(11,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(12,rd_cnt++,buffer,\
						"(1)hdr pcc type:%d\n",pInfo->pre_csc[LX_PE_WIN_1].type1);
					PE_HDR_M19_CASE_SPRINT(13,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(14,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[0], p_co1[1], p_co1[2], p_of1[0], p_of1[3]);
					PE_HDR_M19_CASE_SPRINT(15,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[3], p_co1[4], p_co1[5], p_of1[1], p_of1[4]);
					PE_HDR_M19_CASE_SPRINT(16,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[6], p_co1[7], p_co1[8], p_of1[2], p_of1[5]);
					PE_HDR_M19_CASE_SPRINT(17,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(18,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(19,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(20,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(21,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(22,rd_cnt++,buffer,\
						"(1)hdr csc3 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_1].type2,pInfo->cur_hdr_type[LX_PE_WIN_1],pInfo->pre_hdr_type[LX_PE_WIN_1]);
					PE_HDR_M19_CASE_SPRINT(23,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(24,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[0], p_co2[1], p_co2[2], p_of2[0], p_of2[3]);
					PE_HDR_M19_CASE_SPRINT(25,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[3], p_co2[4], p_co2[5], p_of2[1], p_of2[4]);
					PE_HDR_M19_CASE_SPRINT(26,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[6], p_co2[7], p_co2[8], p_of2[2], p_of2[5]);
					PE_HDR_M19_CASE_SPRINT(27,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(28,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(29,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(30,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(31,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(32,rd_cnt++,buffer,\
						"(1)hdr csc1(s2h) type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_1].type0,pInfo->cur_hdr_type[LX_PE_WIN_1],pInfo->pre_hdr_type[LX_PE_WIN_1]);
					PE_HDR_M19_CASE_SPRINT(33,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(34,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[0], p_co3[1], p_co3[2], p_of3[0], p_of3[3]);
					PE_HDR_M19_CASE_SPRINT(35,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[3], p_co3[4], p_co3[5], p_of3[1], p_of3[4]);
					PE_HDR_M19_CASE_SPRINT(36,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[6], p_co3[7], p_co3[8], p_of3[2], p_of3[5]);
					PE_HDR_M19_CASE_SPRINT(37,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_M19_CASE_SPRINT(38,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(39,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_CASE_SPRINT(40,rd_cnt++,buffer,PE_HDR_M19_PRINT_RESERVED);
					PE_HDR_M19_DFLT_SPRINT(rd_cnt=0,buffer,PE_HDR_M19_PRINT_END);
				}
			}
			else
			{
				snprintf(buffer,PE_TRACE_STR_SIZE,PE_HDR_M19_PRINT_EXIT);
				rd_cnt=0;
			}
			memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");
		}
	} while(0);
	return ret;
}
/**
 * get histo info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_HISTO_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetHistoInfo(LX_PE_HDR_HISTO_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	//static UINT32 count=0;
	UINT32 i, ofst0, ofst1;
	#ifdef PE_HDR_HW_M19_USE_FW_HDR_HST
	UINT32 min[3],max[3];
	#endif
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				#ifdef PE_HDR_HW_M19_USE_FW_HDR_HST
				PE_HDR_LG_0_M19_RdFL(hdr_fsw_ctrl_00);
				PE_HDR_LG_0_M19_RdFL(hdr_fsw_ctrl_01);
				PE_HDR_LG_0_M19_Rd01(hdr_fsw_ctrl_00, min_g, min[0]);
				PE_HDR_LG_0_M19_Rd01(hdr_fsw_ctrl_00, min_b, min[1]);
				PE_HDR_LG_0_M19_Rd01(hdr_fsw_ctrl_00, min_r, min[2]);
				PE_HDR_LG_0_M19_Rd01(hdr_fsw_ctrl_01, max_g, max[0]);
				PE_HDR_LG_0_M19_Rd01(hdr_fsw_ctrl_01, max_b, max[1]);
				PE_HDR_LG_0_M19_Rd01(hdr_fsw_ctrl_01, max_r, max[2]);
				pstParams->status[0] = PE_HDR_HW_M19_MIN(min[0],min[1],min[2]);
				pstParams->status[1] = PE_HDR_HW_M19_MAX(max[0],max[1],max[2]);
				PE_HDR_HW_M19_DBG_PRINT("get hdr histo:min:%4d,%4d,%4d, max:%4d,%4d,%4d\n",\
					min[0],min[1],min[2],max[0],max[1],max[2]);
				ofst0 = 2;
				for(i=0;i<PE_HDR_HW_M19_HST_BIN_NUM;i++)
				{
					pstParams->status[i+ofst0] = 0;
				}
				ofst1 = ofst0 + PE_HDR_HW_M19_HST_BIN_NUM;
				for(i=0;i<PE_HDR_HW_M19_HST_BIN_NUM;i++)
				{
					pstParams->status[i+ofst1] = 0;
				}
				#else
				//PE_HDR_LG_0_M19_RdFL(hdr_top_ctrl_05);
				//PE_HDR_LG_0_M19_Wr01(hdr_top_ctrl_05,reg_hist_src,(count&1)? 4:0);//0:Y,4:MAX(RGB)
				//PE_HDR_LG_0_M19_WrFL(hdr_top_ctrl_05);
				// pre-setting
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
				PE_HDR_LG_0_M19_Wr(hdr_hist_ia_ctrl,0x00011000);
				PE_HDR_LG_0_M19_WrFL(hdr_hist_ia_ctrl);
				#else
				PE_HDR_LG_0_M19_RdFL(hdr_hist_ia_ctrl);
				PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_enable,   0x0);	//0:read mode,  1:normal mode
				PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_ai,       0x1);	//ai 0:disable,  1:enable
				PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_address,  0x0);	//bin address
				PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_status_address,0x0);	//min,max
				PE_HDR_LG_0_M19_WrFL(hdr_hist_ia_ctrl);
				#endif
				//rd histogram
				ofst0 = 2;
				ofst1 = ofst0 + PE_HDR_HW_M19_HST_BIN_NUM;
				for(i=0;i<PE_HDR_HW_M19_HST_BIN_NUM;i++)
				{
					PE_HDR_LG_0_M19_RdFL(hdr_hist_ia_data1);
					pstParams->status[i+ofst0] = GET_BITS(PE_HDR_LG_0_M19_Rd(hdr_hist_ia_data1), 0,23);
					pstParams->status[i+ofst1] = pstParams->status[i+ofst0];
				}
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
				PE_HDR_LG_0_M19_Wr(hdr_hist_ia_ctrl,0x00018000);
				PE_HDR_LG_0_M19_WrFL(hdr_hist_ia_ctrl);
				#else
				PE_HDR_LG_0_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_enable,0x1);
				PE_HDR_LG_0_M19_WrFL(hdr_hist_ia_ctrl);
				#endif
				//rd min,max
				PE_HDR_LG_0_M19_RdFL(hdr_hist_ia_data2);
				pstParams->status[0] = GET_BITS(PE_HDR_LG_0_M19_Rd(hdr_hist_ia_data2), 0,10);
				pstParams->status[1] = GET_BITS(PE_HDR_LG_0_M19_Rd(hdr_hist_ia_data2),16,10);
				//count++;
				//if (count>=100)	count=0;
				//for(i=0;i<34;i++)	printk("M[%d][%3d] %d\n", pstParams->win_id, i, pstParams->status[i]);
				#endif
			}
			if(PE_CHECK_WIN1(win_id))
			{
				#ifdef PE_HDR_HW_M19_USE_FW_HDR_HST
				PE_HDR_LG_1_M19_RdFL(hdr_fsw_ctrl_00);
				PE_HDR_LG_1_M19_RdFL(hdr_fsw_ctrl_01);
				PE_HDR_LG_1_M19_Rd01(hdr_fsw_ctrl_00, min_g, min[0]);
				PE_HDR_LG_1_M19_Rd01(hdr_fsw_ctrl_00, min_b, min[1]);
				PE_HDR_LG_1_M19_Rd01(hdr_fsw_ctrl_00, min_r, min[2]);
				PE_HDR_LG_1_M19_Rd01(hdr_fsw_ctrl_01, max_g, max[0]);
				PE_HDR_LG_1_M19_Rd01(hdr_fsw_ctrl_01, max_b, max[1]);
				PE_HDR_LG_1_M19_Rd01(hdr_fsw_ctrl_01, max_r, max[2]);
				pstParams->status[0] = PE_HDR_HW_M19_MIN(min[0],min[1],min[2]);
				pstParams->status[1] = PE_HDR_HW_M19_MAX(max[0],max[1],max[2]);
				PE_HDR_HW_M19_DBG_PRINT("get hdr histo:min:%4d,%4d,%4d, max:%4d,%4d,%4d\n",\
					min[0],min[1],min[2],max[0],max[1],max[2]);
				ofst0 = 2;
				for(i=0;i<PE_HDR_HW_M19_HST_BIN_NUM;i++)
				{
					pstParams->status[i+ofst0] = 0;
				}
				ofst1 = ofst0 + PE_HDR_HW_M19_HST_BIN_NUM;
				for(i=0;i<PE_HDR_HW_M19_HST_BIN_NUM;i++)
				{
					pstParams->status[i+ofst1] = 0;
				}
				#else
				//PE_HDR_LG_1_M19_RdFL(hdr_top_ctrl_05);
				//PE_HDR_LG_1_M19_Wr01(hdr_top_ctrl_05,reg_hist_src,(count&1)? 4:0);//0:Y,4:MAX(RGB)
				//PE_HDR_LG_1_M19_WrFL(hdr_top_ctrl_05);
				// pre-setting
				#ifdef PE_HDR_HW_M19_WA_RD_LUT
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
				PE_HDR_LG_1_M19_Wr(hdr_hist_ia_ctrl,0x00011000);
				PE_HDR_LG_1_M19_WrFL(hdr_hist_ia_ctrl);
				#else
				PE_HDR_LG_1_M19_RdFL(hdr_hist_ia_ctrl);
				PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_enable,   0x0);	//0:read mode,  1:normal mode
				PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_ai,       0x1);	//ai 0:disable,  1:enable
				PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_address,  0x0);	//bin address
				PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_status_address,0x0);	//min,max
				PE_HDR_LG_1_M19_WrFL(hdr_hist_ia_ctrl);
				#endif
				//rd histogram
				ofst0 = 2;
				ofst1 = ofst0 + PE_HDR_HW_M19_HST_BIN_NUM;
				for(i=0;i<PE_HDR_HW_M19_HST_BIN_NUM;i++)
				{
					PE_HDR_LG_1_M19_RdFL(hdr_hist_ia_data1);
					pstParams->status[i+ofst0] = GET_BITS(PE_HDR_LG_1_M19_Rd(hdr_hist_ia_data1), 0,23);
					pstParams->status[i+ofst1] = pstParams->status[i+ofst0];
				}
				PE_HDR_LG_1_M19_Wr01(hdr_hist_ia_ctrl,hif_hist_enable,0x1);
				PE_HDR_LG_1_M19_WrFL(hdr_hist_ia_ctrl);
				//rd min,max
				PE_HDR_LG_1_M19_RdFL(hdr_hist_ia_data2);
				pstParams->status[0] = GET_BITS(PE_HDR_LG_1_M19_Rd(hdr_hist_ia_data2), 0,10);
				pstParams->status[1] = GET_BITS(PE_HDR_LG_1_M19_Rd(hdr_hist_ia_data2),16,10);
				//count++;
				//if (count>=100)	count=0;
				//for(i=0;i<34;i++)	printk("S[%d][%3d] %d\n", pstParams->win_id, i, pstParams->status[i]);
				#endif
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetInfo(LX_PE_HDR_INFO_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, total_size, ofst, item_max, db_ofst;
	LX_PE_WIN_ID win_id;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("get[%d]:size:%d\n",pstParams->win_id, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id)||PE_CHECK_WIN1(win_id))
			{
				ofst = 8;
				item_max = PE_HDR_DDR_M19_ITEM_V4_MAX;
				total_size = (item_max<<1)+ofst;
				PE_HDR_HW_M19_CHECK_CODE((pstParams->size<total_size), break, \
					"[%s,%d] pstParams->size(%d) is short.\n", __F__,__L__, pstParams->size);
				pstParams->size = total_size;
				rmb();
				for (i=0; i<ofst; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_M19[i];
				}
				for (i=0; i<(item_max); i++)
				{
					db_ofst = (pInfo->db_base[i]>PE_M19_DDR_DB0_BASE)? (pInfo->db_base[i]-PE_M19_DDR_DB0_BASE):0;
					pstParams->data[i+i+ofst]   = db_ofst;
					pstParams->data[i+i+1+ofst] = pInfo->db_size[i];
				}
				PE_HDR_HW_M19_DBG_PRINT("size,max:%d,%d\n",pstParams->size,item_max);
				PE_HDR_HW_M19_BACKUP_TRACE("[GetInfo]size,max:%d,%d [0]~[4]0x%08x,0x%08x,0x%08x,0x%08x",\
					pstParams->size,item_max,pstParams->data[0],pstParams->data[1],\
					pstParams->data[2],pstParams->data[3]);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set eotf lut
 *
 * @param   *pstParams [in] LX_PE_HDR_EOTF_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, count, oper, size, connect[2];
	#ifdef PE_HDR_HW_M19_MOVE_TO_FW
	UINT32 i;
	#endif
	volatile UINT32 *p_pe_hdr_hw_m19_ddr = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_HDR_LG_0_M19_QWr01(hdr_top_ctrl_05,reg_eotf_en,0x0);
				PE_HDR_LG_0_M19_QWr(hdr_eotf_ia_ctrl, 0x40001000);
				for (i=0; i<pstParams->size; i++)
				{
					PE_HDR_LG_0_M19_QWr(hdr_eotf_ia_data,pstParams->data[i]);
				}
				PE_HDR_LG_0_M19_QWr(hdr_eotf_ia_ctrl, 0x80001000);
				PE_HDR_LG_0_M19_QWr01(hdr_top_ctrl_05,reg_eotf_en,0x1);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_HDR_LG_1_M19_QWr01(hdr_top_ctrl_05,reg_eotf_en,0x0);
				PE_HDR_LG_1_M19_QWr(hdr_eotf_ia_ctrl, 0x40001000);
				for (i=0; i<pstParams->size; i++)
				{
					PE_HDR_LG_1_M19_QWr(hdr_eotf_ia_data,pstParams->data[i]);
				}
				PE_HDR_LG_1_M19_QWr(hdr_eotf_ia_ctrl, 0x80001000);
				PE_HDR_LG_1_M19_QWr01(hdr_top_ctrl_05,reg_eotf_en,0x1);
			}
			#endif
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_GetEotfOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_M19_GetEotfOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[EO]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_M19_IncreaseEotfCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[EO0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst,size,connect[LX_PE_WIN_0],count);
					PE_HDR_HW_M19_BACKUP_TRACE("[EO0][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_M19_VERSION,\
						pstParams->oper, pstParams->size, \
						ofst, connect[LX_PE_WIN_0], count, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_1);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_GetEotfOffset(LX_PE_WIN_1, oper);
					else								ofst = PE_HDR_HW_M19_GetEotfOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[EO]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_1], pstParams->oper);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_M19_IncreaseEotfCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[EO1][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst,size,connect[LX_PE_WIN_1],count);
					PE_HDR_HW_M19_BACKUP_TRACE("[EO1][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_M19_VERSION,\
						pstParams->oper, pstParams->size, \
						ofst, connect[LX_PE_WIN_1], count, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get eotf lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_EOTF_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 ofst, count, oper, size;
	UINT32 connect[2];
	volatile UINT32 *p_pe_hdr_hw_m19_ddr = NULL;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					//addr = (void *)gPE_HDR_DDR_M19;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_GetEotfOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_M19_GetEotfOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[EO]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)pstParams->data, (void *)p_pe_hdr_hw_m19_ddr, size);
					count = PE_HDR_HW_M19_GetEotfCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[EO0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst,size,connect[LX_PE_WIN_0],count);
				} while(0);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_1);
				do {
					oper = pstParams->oper&0xF;
					//addr = (void *)gPE_HDR_DDR_M19;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_GetEotfOffset(LX_PE_WIN_1, oper);
					else								ofst = PE_HDR_HW_M19_GetEotfOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[EO]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_1], pstParams->oper);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)pstParams->data, (void *)p_pe_hdr_hw_m19_ddr, size);
					count = PE_HDR_HW_M19_GetEotfCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[EO1][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst,size,connect[LX_PE_WIN_1],count);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set oetf lut
 *
 * @param   *pstParams [in] LX_PE_HDR_OETF_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams)
{
	int ret = RET_OK;
	//void *addr;
	//UINT32 i;
	UINT32 ofst, count, oper, size;
	UINT32 connect[2];
	volatile UINT32 *p_pe_hdr_hw_m19_ddr = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			#ifdef PE_HDR_HW_M19_MOVE_TO_FW
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_HDR_LG_0_M19_QWr01(hdr_top_ctrl_05,reg_oetf_en,0x0);
				PE_HDR_LG_0_M19_QWr(hdr_oetf_ia_ctrl, 0x40001000);
				for (i=0; i<pstParams->size; i++)
				{
					PE_HDR_LG_0_M19_QWr(hdr_oetf_ia_data,pstParams->data[i]);
				}
				PE_HDR_LG_0_M19_QWr(hdr_oetf_ia_ctrl, 0x80001000);
				PE_HDR_LG_0_M19_QWr01(hdr_top_ctrl_05,reg_oetf_en,0x1);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_HDR_LG_1_M19_QWr01(hdr_top_ctrl_05,reg_oetf_en,0x0);
				PE_HDR_LG_1_M19_QWr(hdr_oetf_ia_ctrl, 0x40001000);
				for (i=0; i<pstParams->size; i++)
				{
					PE_HDR_LG_1_M19_QWr(hdr_oetf_ia_data,pstParams->data[i]);
				}
				PE_HDR_LG_1_M19_QWr(hdr_oetf_ia_ctrl, 0x80001000);
				PE_HDR_LG_1_M19_QWr01(hdr_top_ctrl_05,reg_oetf_en,0x1);
			}
			#endif
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					//addr = (void *)gPE_HDR_DDR_M19;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_GetOetfOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_M19_GetOetfOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[OE]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_M19_IncreaseOetfCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[OE0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst,size,connect[LX_PE_WIN_0],count);
					PE_HDR_HW_M19_BACKUP_TRACE("[OE0][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_M19_VERSION,\
						pstParams->oper, pstParams->size, \
						ofst, connect[LX_PE_WIN_0], count, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_1);
				do {
					oper = pstParams->oper&0xF;
					//addr = (void *)gPE_HDR_DDR_M19;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_GetOetfOffset(LX_PE_WIN_1, oper);
					else								ofst = PE_HDR_HW_M19_GetOetfOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[OE]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_1], pstParams->oper);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_m19_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_M19_IncreaseOetfCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[OE1][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst,size,connect[LX_PE_WIN_1],count);
					PE_HDR_HW_M19_BACKUP_TRACE("[OE1][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_M19_VERSION,\
						pstParams->oper, pstParams->size, \
						ofst, connect[LX_PE_WIN_1], count, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get oetf lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_OETF_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 ofst, count, oper, size;
	UINT32 connect[2];
	volatile UINT32 *p_pe_hdr_hw_m19_ddr = NULL;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					//addr = (void *)gPE_HDR_DDR_M19;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_GetOetfOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_M19_GetOetfOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[OE]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)pstParams->data, (void *)p_pe_hdr_hw_m19_ddr, size);
					wmb();
					count = PE_HDR_HW_M19_GetOetfCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[OE0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst,size,connect[LX_PE_WIN_0],count);
				} while(0);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_1);
				do {
					oper = pstParams->oper&0xF;
					//addr = (void *)gPE_HDR_DDR_M19;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_GetOetfOffset(LX_PE_WIN_1, oper);
					else								ofst = PE_HDR_HW_M19_GetOetfOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[OE]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_1], pstParams->oper);break;}
					p_pe_hdr_hw_m19_ddr = gPE_HDR_DDR_M19 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_m19_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)pstParams->data, (void *)p_pe_hdr_hw_m19_ddr, size);
					wmb();
					count = PE_HDR_HW_M19_GetOetfCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_M19_DBG_PRINT("[OE0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst,size,connect[LX_PE_WIN_1],count);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set 3d lut info
 *
 * @param   *pstParams [in] LX_PE_HDR_3D_LUT_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_Set3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, connect, count, oper;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				do {
					connect = pstParams->data[1];
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_Get3dLutOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_M19_Get3dLutOffset(LX_PE_WIN_0, connect);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[S3L]c[%d]ofst invalid.\n", connect);break;}
					count = GET_BITS(pstParams->data[0],0,4);
					PE_HDR_HW_M19_Set3dLutCount(LX_PE_WIN_0, ofst, count);
					PE_HDR_HW_M19_DBG_PRINT("[S3L][%s] cur of:%x, c[%d]:%d, d:%08x,%08x\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect), ofst, connect, count, pstParams->data[0], pstParams->data[1]);
					PE_HDR_HW_M19_BACKUP_TRACE("[S3L][%s]o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect), pstParams->oper, pstParams->size, \
						ofst, connect, count, pstParams->data[0], pstParams->data[1]);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get 3d lut info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_3D_LUT_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_Get3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 ofst, count, oper;
	UINT32 connect[2];
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_M19_CHECK_CODE((pstParams->size<10), break, \
			"[%s,%d] pstParams->size(%d) is wrong.\n", __F__,__L__, pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_M19_LUT_TYPE_A)	ofst = PE_HDR_HW_M19_Get3dLutOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_M19_Get3dLutOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_M19_DBG_PRINT("[G3L]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					count = PE_HDR_HW_M19_Get3dLutCount(LX_PE_WIN_0, ofst);
					pstParams->data[0] = count;
					pstParams->data[1] = connect[LX_PE_WIN_0];
					pstParams->data[3] = pstParams->data[5] = pstParams->data[7] = PE_HDR_DDR_M19_3LUT_SIZE;
					if (ofst==PE_HDR_DDR_M19_3LUT_A1_OFST)
					{
						pstParams->data[2] = PE_HDR_DDR_M19_3LUT_A1_OFST;
						pstParams->data[4] = PE_HDR_DDR_M19_3LUT_A2_OFST;
						pstParams->data[6] = PE_HDR_DDR_M19_3LUT_A3_OFST;
					}
					else if (ofst==PE_HDR_DDR_M19_3LUT_B1_OFST)
					{
						pstParams->data[2] = PE_HDR_DDR_M19_3LUT_B1_OFST;
						pstParams->data[4] = PE_HDR_DDR_M19_3LUT_B2_OFST;
						pstParams->data[6] = PE_HDR_DDR_M19_3LUT_B3_OFST;
					}
					else if (ofst==PE_HDR_DDR_M19_3LUT_C1_OFST)
					{
						pstParams->data[2] = PE_HDR_DDR_M19_3LUT_C1_OFST;
						pstParams->data[4] = PE_HDR_DDR_M19_3LUT_C2_OFST;
						pstParams->data[6] = PE_HDR_DDR_M19_3LUT_C3_OFST;
					}
					else//if (ofst==PE_HDR_DDR_M19_3LUT_D1_OFST)
					{
						pstParams->data[2] = PE_HDR_DDR_M19_3LUT_D1_OFST;
						pstParams->data[4] = PE_HDR_DDR_M19_3LUT_D2_OFST;
						pstParams->data[6] = PE_HDR_DDR_M19_3LUT_D3_OFST;
					}
					PE_HDR_HW_M19_DBG_PRINT("[G3L][%s] size:%d, cur of:%x, c[%d]:%d, d:%08x,%08x\n", \
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]), pstParams->size, ofst, connect[LX_PE_WIN_0], count, \
						pstParams->data[0], pstParams->data[1]);
					PE_HDR_HW_M19_DBG_PRINT("0x%08x,0x%08x,0x%08x,0x%08x,0x%08x,0x%08x\n", \
						pstParams->data[2], pstParams->data[3], pstParams->data[4], \
						pstParams->data[5], pstParams->data[6], pstParams->data[7]);
					PE_HDR_HW_M19_BACKUP_TRACE("[G3L][%s]o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%04x,b:%08x,%08x,%08x,s:%04x",\
						PE_HDR_HW_M19_CONNECT_TO_STR(connect[LX_PE_WIN_0]), pstParams->oper, \
						pstParams->size, ofst, connect[LX_PE_WIN_0], count, \
						pstParams->data[0], pstParams->data[1], pstParams->data[2], \
						pstParams->data[4], pstParams->data[6], pstParams->data[3]);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set mode info
 *
 * @param   *pstParams [in] LX_PE_HDR_MODE_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 hdr_info = 0;
	UINT32 i, cur_hdr_info, connect[2], support, hist_src;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	LX_PE_HDR_OP_MD_T *p_op = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("set[%d] : data[0]:0x%08x\n", pstParams->win_id, pstParams->data[0]);
		if(PE_KDRV_VER_M19)
		{
			#ifdef PE_HDR_HW_M19_MODE_INFO_SYNC_WITH_MAIN
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				for (i=0;i<LX_PE_WIN_ALL;i++)
				{
					memcpy(&(pInfo->md_inf[i]), pstParams, sizeof(LX_PE_HDR_MODE_INFO_T));
				}
			}
			#else
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				if (pstParams->win_id==i||pstParams->win_id==LX_PE_WIN_ALL)
				{
					memcpy(&(pInfo->md_inf[i]), pstParams, sizeof(LX_PE_HDR_MODE_INFO_T));
				}
				/* sync parameters with no relationship to window */
				//pInfo->md_inf[i].data[0] = pstParams->data[0];
			}
			#endif
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_0);
				p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_0].data[0]));
				/* hist_src */
				/* 20181102, tvpq req. adjust techni hist_src: 0x4 -> 0x0 */
				if (connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_HLG || \
					connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_TEC)
				{
					hist_src = 0x0;//0:Y,4:MAX(RGB)
				}
				else
				{
					hist_src = 0x4;//0:Y,4:MAX(RGB)
				}
				PE_HDR_LG_0_M19_RdFL(hdr_top_ctrl_05);
				PE_HDR_LG_0_M19_Wr01(hdr_top_ctrl_05,reg_hist_src,hist_src);//0:Y,4:MAX(RGB)
				PE_HDR_LG_0_M19_WrFL(hdr_top_ctrl_05);
				#ifdef PE_HDR_HW_M19_EN_CC_SDR
				if (connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_H10 || \
					connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_HLG || \
					connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_TEC)
				{
					pInfo->reg_out_sgain_sel[LX_PE_WIN_0] = 0x0;//20171117,TVPQ-708,1->0
					pInfo->reg_out_lgain_sel[LX_PE_WIN_0] = 0x1;//20171117,TVPQ-708,0->1
					pInfo->reg_inp_s_sel[LX_PE_WIN_0] = 0x1;//20171117,TVPQ-708,0->1
					pInfo->reg_inp_l_sel[LX_PE_WIN_0] = 0x0;
				}
				else
				{
					pInfo->reg_out_sgain_sel[LX_PE_WIN_0] = 0x1;//20180827,TVPQ-1069,0->1
					pInfo->reg_out_lgain_sel[LX_PE_WIN_0] = 0x0;//20180827,TVPQ-1069,1->0
					pInfo->reg_inp_s_sel[LX_PE_WIN_0] = 0x1;
					pInfo->reg_inp_l_sel[LX_PE_WIN_0] = 0x0;
				}
				PE_HDR_LG_0_M19_RdFL(hdr_hue_sat_alpha_ctrl);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pInfo->reg_out_sgain_sel[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pInfo->reg_out_lgain_sel[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pInfo->reg_inp_s_sel[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pInfo->reg_inp_l_sel[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_WrFL(hdr_hue_sat_alpha_ctrl);
				#else
				/* hue,sat_prsv_en */
				if (connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_H10 || \
					connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_HLG || \
					connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_TEC)
					pInfo->reg_hue_prsv_en[LX_PE_WIN_0] = pInfo->reg_sat_prsv_en[LX_PE_WIN_0] = 1;
				else
					pInfo->reg_hue_prsv_en[LX_PE_WIN_0] = pInfo->reg_sat_prsv_en[LX_PE_WIN_0] = 0;
				PE_HDR_LG_0_M19_RdFL(hdr_hue_sat_ctrl);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_en,pInfo->reg_hue_prsv_en[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_en,pInfo->reg_sat_prsv_en[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_WrFL(hdr_hue_sat_ctrl);
				#endif
				/* ygain_orig_sel, yg_lut_en */
				pInfo->yg_lut_en[LX_PE_WIN_0] = (connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_HLG)? 1:0;//hlg:1, others:0
				pInfo->yg_orgsel[LX_PE_WIN_0] = (connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_HLG)? 0:1;//hlg:0, others:1
				/*****************************************/
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				PE_HDR_LG_0_M19_RdFL(hdr_rgb2lms_ctrl_00);
				PE_HDR_LG_0_M19_Wr01(hdr_rgb2lms_ctrl_00,rgb2lms_inp_mux,pInfo->yg_lut_en[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_WrFL(hdr_rgb2lms_ctrl_00);
				PE_HDR_LG_0_M19_RdFL(hdr_ygain_lut_ctrl_00);
				PE_HDR_LG_0_M19_Wr01(hdr_ygain_lut_ctrl_00,luminance_lut2_enable,pInfo->yg_lut_en[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_WrFL(hdr_ygain_lut_ctrl_00);
				PE_HDR_LG_0_M19_RdFL(hdr_pcc32_gain_ctrl);
				PE_HDR_LG_0_M19_Wr01(hdr_pcc32_gain_ctrl,hif_pcc32_ygain_orig_sel,pInfo->yg_orgsel[LX_PE_WIN_0]);//1:hdr10,0:hlg
				PE_HDR_LG_0_M19_WrFL(hdr_pcc32_gain_ctrl);
				#endif
				/*****************************************/
				/* dither_en */
				pInfo->dither_en[LX_PE_WIN_0] = (connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_H10 || \
							connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_HLG || \
							connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_TEC)? 1:0;//hdr10,prime,hlg:on
				#ifdef PE_HDR_HW_M19_DITEHER_BY_BIT_MODE
				/* "00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass */
				PE_HDR_LG_0_M19_RdFL(hdr_dither_ctrl_00);
				PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,bit_mode,(pInfo->dither_en[LX_PE_WIN_0]==1)? 0x0:0x3);
				PE_HDR_LG_0_M19_WrFL(hdr_dither_ctrl_00);
				#else
				PE_HDR_LG_0_M19_RdFL(hdr_dither_ctrl_00);
				PE_HDR_LG_0_M19_Wr01(hdr_dither_ctrl_00,dither_en,pInfo->dither_en[LX_PE_WIN_0]);
				PE_HDR_LG_0_M19_WrFL(hdr_dither_ctrl_00);
				#endif
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				PE_HDR_LG_0_M19_RdFL(hdr_3dlut_ctrl_00);
				PE_HDR_LG_0_M19_Wr01(hdr_3dlut_ctrl_00,reg_3d_lut_en,(connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_SDR)? 1:0);
				PE_HDR_LG_0_M19_WrFL(hdr_3dlut_ctrl_00);
				#endif
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				PE_HDR_LG_0_M19_RdFL(hdr_sdr2hdr_ctrl_00);
				PE_HDR_LG_0_M19_Wr01(hdr_sdr2hdr_ctrl_00,reg_sdr2hdr_bypass,(connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_S2H)? 0:1);
				//PE_HDR_LG_0_M19_Wr01(hdr_sdr2hdr_ctrl_00,reg_va_length,2160);
				//PE_HDR_LG_0_M19_Wr01(hdr_sdr2hdr_ctrl_00,reg_ha_length,3840);
				PE_HDR_LG_0_M19_WrFL(hdr_sdr2hdr_ctrl_00);
				#endif
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				do {
					UINT32 llut_en;
					llut_en = 1;//(connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_S2H)? 0:1;
					//lut0,1,2 win mode
					PE_HDR_LG_0_M19_RdFL(hdr_llut0_ctrl_00);
					PE_HDR_LG_0_M19_Wr01(hdr_llut0_ctrl_00,luminance_lut0_enable,llut_en);
					PE_HDR_LG_0_M19_WrFL(hdr_llut0_ctrl_00);
					PE_HDR_LG_0_M19_RdFL(hdr_llut1_ctrl_00);
					PE_HDR_LG_0_M19_Wr01(hdr_llut1_ctrl_00,luminance_lut1_enable,llut_en);
					PE_HDR_LG_0_M19_WrFL(hdr_llut1_ctrl_00);
					PE_HDR_LG_0_M19_RdFL(hdr_llut2_ctrl_00);
					PE_HDR_LG_0_M19_Wr01(hdr_llut2_ctrl_00,luminance_lut2_enable,llut_en);
					PE_HDR_LG_0_M19_WrFL(hdr_llut2_ctrl_00);
				} while(0);
				#endif
				/* set support info */
				support = p_op->sup_mod;
				ret = PE_HDR_HW_M19_SetSupportInfo(LX_PE_WIN_0,support);
				PE_HDR_HW_M19_CHECK_CODE(ret, break, \
					"[%s,%d] PE_HDR_HW_M19_SetSupportInfo() error.\n",__F__,__L__);
				/* info normal, sdr2hdr, hdr_off */
				cur_hdr_info = (p_op->hdr_off == 2)? 3:(p_op->hdr_off == 1)? 2:(connect[LX_PE_WIN_0]==PE_HDR_HW_M19_CONNECT_MODE_S2H)? 1:0;
				hdr_info = (hdr_info&0xffff0000)|(cur_hdr_info&0x0000ffff);//[15:0] update
				ret = PE_FWI_M19_SetHdrInfo(&hdr_info);
				PE_HDR_HW_M19_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_M19_SetHdrInfo() error.\n",__F__,__L__);
				PE_HDR_HW_M19_BACKUP_TRACE("[MI0]co(c)/ht,hc/cl,of,sp/dt,if:%d(%d)/%d,%d/%d,%d,%d/%d,%d(0x%08x)", \
					p_op->connect, connect[LX_PE_WIN_0], p_op->hdrtone, p_op->hdrcase, \
					p_op->colmtry, p_op->hdr_off, p_op->sup_mod, pInfo->dither_en[LX_PE_WIN_0], cur_hdr_info, hdr_info);
				PE_PRINT_NOTI("[MI0]co(c)/ht,hc/cl,of,sp/dt,if:%d(%d)/%d,%d/%d,%d,%d/%d,%d(0x%08x)", \
					p_op->connect, connect[LX_PE_WIN_0], p_op->hdrtone, p_op->hdrcase, \
					p_op->colmtry, p_op->hdr_off, p_op->sup_mod, pInfo->dither_en[LX_PE_WIN_0], cur_hdr_info, hdr_info);
			}
			#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
			if(PE_CHECK_WIN0(pstParams->win_id))
			#else
			if(PE_CHECK_WIN1(pstParams->win_id))
			#endif
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_M19_GetConnectMode(LX_PE_WIN_1);
				p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_1].data[0]));
				/* hist_src */
				/* 20181102, tvpq req. adjust techni hist_src: 0x4 -> 0x0 */
				if (connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_HLG || \
					connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_TEC)
				{
					hist_src = 0x0;//0:Y,4:MAX(RGB)
				}
				else
				{
					hist_src = 0x4;//0:Y,4:MAX(RGB)
				}
				PE_HDR_LG_1_M19_RdFL(hdr_top_ctrl_05);
				PE_HDR_LG_1_M19_Wr01(hdr_top_ctrl_05,reg_hist_src,hist_src);//0:Y,4:MAX(RGB)
				PE_HDR_LG_1_M19_WrFL(hdr_top_ctrl_05);
				#ifdef PE_HDR_HW_M19_EN_CC_SDR
				if (connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_H10 || \
					connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_HLG || \
					connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_TEC)
				{
					pInfo->reg_out_sgain_sel[LX_PE_WIN_1] = 0x0;//20171117,TVPQ-708,1->0
					pInfo->reg_out_lgain_sel[LX_PE_WIN_1] = 0x1;//20171117,TVPQ-708,0->1
					pInfo->reg_inp_s_sel[LX_PE_WIN_1] = 0x1;//20171117,TVPQ-708,0->1
					pInfo->reg_inp_l_sel[LX_PE_WIN_1] = 0x0;
				}
				else
				{
					pInfo->reg_out_sgain_sel[LX_PE_WIN_1] = 0x1;//20180827,TVPQ-1069,0->1
					pInfo->reg_out_lgain_sel[LX_PE_WIN_1] = 0x0;//20180827,TVPQ-1069,1->0
					pInfo->reg_inp_s_sel[LX_PE_WIN_1] = 0x1;
					pInfo->reg_inp_l_sel[LX_PE_WIN_1] = 0x0;
				}
				PE_HDR_LG_1_M19_RdFL(hdr_hue_sat_alpha_ctrl);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pInfo->reg_out_sgain_sel[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pInfo->reg_out_lgain_sel[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pInfo->reg_inp_s_sel[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pInfo->reg_inp_l_sel[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_WrFL(hdr_hue_sat_alpha_ctrl);
				#else
				/* hue,sat_prsv_en */
				if (connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_H10 || \
					connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_HLG || \
					connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_TEC)
					pInfo->reg_hue_prsv_en[LX_PE_WIN_1] = pInfo->reg_sat_prsv_en[LX_PE_WIN_1] = 1;
				else
					pInfo->reg_hue_prsv_en[LX_PE_WIN_1] = pInfo->reg_sat_prsv_en[LX_PE_WIN_1] = 0;
				PE_HDR_LG_1_M19_RdFL(hdr_hue_sat_ctrl);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_en,pInfo->reg_hue_prsv_en[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_en,pInfo->reg_sat_prsv_en[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_WrFL(hdr_hue_sat_ctrl);
				#endif
				/* ygain_orig_sel, yg_lut_en */
				pInfo->yg_lut_en[LX_PE_WIN_1] = (connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_HLG)? 1:0;//hlg:1, others:0
				pInfo->yg_orgsel[LX_PE_WIN_1] = (connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_HLG)? 0:1;//hlg:0, others:1
				/*****************************************/
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				PE_HDR_LG_1_M19_RdFL(hdr_rgb2lms_ctrl_00);
				PE_HDR_LG_1_M19_Wr01(hdr_rgb2lms_ctrl_00,rgb2lms_inp_mux,pInfo->yg_lut_en[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_WrFL(hdr_rgb2lms_ctrl_00);
				PE_HDR_LG_1_M19_RdFL(hdr_ygain_lut_ctrl_00);
				PE_HDR_LG_1_M19_Wr01(hdr_ygain_lut_ctrl_00,luminance_lut2_enable,pInfo->yg_lut_en[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_WrFL(hdr_ygain_lut_ctrl_00);
				PE_HDR_LG_1_M19_RdFL(hdr_pcc32_gain_ctrl);
				PE_HDR_LG_1_M19_Wr01(hdr_pcc32_gain_ctrl,hif_pcc32_ygain_orig_sel,pInfo->yg_orgsel[LX_PE_WIN_1]);//1:hdr10,0:hlg
				PE_HDR_LG_1_M19_WrFL(hdr_pcc32_gain_ctrl);
				#endif
				/*****************************************/
				/* dither_en */
				pInfo->dither_en[LX_PE_WIN_1] = (connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_H10 || \
							connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_HLG || \
							connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_TEC)? 1:0;//hdr10,prime,hlg:on
				#ifdef PE_HDR_HW_M19_DITEHER_BY_BIT_MODE
				/* "00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass */
				PE_HDR_LG_1_M19_RdFL(hdr_dither_ctrl_00);
				PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,bit_mode,(pInfo->dither_en[LX_PE_WIN_1]==1)? 0x0:0x3);
				PE_HDR_LG_1_M19_WrFL(hdr_dither_ctrl_00);
				#else
				PE_HDR_LG_1_M19_RdFL(hdr_dither_ctrl_00);
				PE_HDR_LG_1_M19_Wr01(hdr_dither_ctrl_00,dither_en,pInfo->dither_en[LX_PE_WIN_1]);
				PE_HDR_LG_1_M19_WrFL(hdr_dither_ctrl_00);
				#endif
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				PE_HDR_LG_1_M19_RdFL(hdr_3dlut_ctrl_00);
				PE_HDR_LG_1_M19_Wr01(hdr_3dlut_ctrl_00,reg_3d_lut_en,(connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_SDR)? 1:0);
				PE_HDR_LG_1_M19_WrFL(hdr_3dlut_ctrl_00);
				#endif
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				PE_HDR_LG_1_M19_RdFL(hdr_sdr2hdr_ctrl_00);
				PE_HDR_LG_1_M19_Wr01(hdr_sdr2hdr_ctrl_00,reg_sdr2hdr_bypass,(connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_S2H)? 0:1);
				PE_HDR_LG_1_M19_Wr01(hdr_sdr2hdr_ctrl_00,reg_va_length,2160);
				PE_HDR_LG_1_M19_Wr01(hdr_sdr2hdr_ctrl_00,reg_ha_length,3840);
				PE_HDR_LG_1_M19_WrFL(hdr_sdr2hdr_ctrl_00);
				#endif
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				do {
					UINT32 llut_en;
					llut_en = 1;//(connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_S2H)? 0:1;
					//lut0,1,2 win mode
					PE_HDR_LG_1_M19_RdFL(hdr_llut0_ctrl_00);
					PE_HDR_LG_1_M19_Wr01(hdr_llut0_ctrl_00,luminance_lut0_enable,llut_en);
					PE_HDR_LG_1_M19_WrFL(hdr_llut0_ctrl_00);
					PE_HDR_LG_1_M19_RdFL(hdr_llut1_ctrl_00);
					PE_HDR_LG_1_M19_Wr01(hdr_llut1_ctrl_00,luminance_lut1_enable,llut_en);
					PE_HDR_LG_1_M19_WrFL(hdr_llut1_ctrl_00);
					PE_HDR_LG_1_M19_RdFL(hdr_llut2_ctrl_00);
					PE_HDR_LG_1_M19_Wr01(hdr_llut2_ctrl_00,luminance_lut2_enable,llut_en);
					PE_HDR_LG_1_M19_WrFL(hdr_llut2_ctrl_00);
				} while(0);
				#endif
				#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
				// no need to set fwi hdr info and print
				#else
				/* set support info */
				support = p_op->sup_mod;
				ret = PE_HDR_HW_M19_SetSupportInfo(LX_PE_WIN_1,support);
				PE_HDR_HW_M19_CHECK_CODE(ret, break, \
					"[%s,%d] PE_HDR_HW_M19_SetSupportInfo() error.\n",__F__,__L__);
				/* info normal, sdr2hdr, hdr_off */
				cur_hdr_info = (p_op->hdr_off == 2)? 3:(p_op->hdr_off == 1)? 2:(connect[LX_PE_WIN_1]==PE_HDR_HW_M19_CONNECT_MODE_S2H)? 1:0;
				hdr_info = (hdr_info&0x0000ffff)|(cur_hdr_info<<16);//[31:16] update
				ret = PE_FWI_M19_SetHdrInfo(&hdr_info);
				PE_HDR_HW_M19_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_M19_SetHdrInfo() error.\n",__F__,__L__);
				PE_HDR_HW_M19_BACKUP_TRACE("[MI1]co(c)/ht,hc/cl,of,sp/dt,if:%d(%d)/%d,%d/%d,%d,%d/%d,%d(0x%08x)", \
					p_op->connect, connect[LX_PE_WIN_1], p_op->hdrtone, p_op->hdrcase, \
					p_op->colmtry, p_op->hdr_off, p_op->sup_mod, pInfo->dither_en[LX_PE_WIN_1], cur_hdr_info, hdr_info);
				PE_PRINT_NOTI("[MI1]co(c)/ht,hc/cl,of,sp/dt,if:%d(%d)/%d,%d/%d,%d,%d/%d,%d(0x%08x)", \
					p_op->connect, connect[LX_PE_WIN_1], p_op->hdrtone, p_op->hdrcase, \
					p_op->colmtry, p_op->hdr_off, p_op->sup_mod, pInfo->dither_en[LX_PE_WIN_1], cur_hdr_info, hdr_info);
				#endif
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get mode info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_MODE_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id, temp;
	UINT32 i, hdr_mode;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	LX_PE_HDR_OP_MD_T *p_op = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_0].data[0]));
				hdr_mode = 0;
				ret = PE_FWI_M19_GetHdrMode(&hdr_mode);
				PE_HDR_HW_M19_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_M19_GetHdrMode() error.\n",__F__,__L__);
				p_op->cur_mod = hdr_mode;
			}
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				if (win_id==i)
				{
					temp = pstParams->win_id;
					memcpy(pstParams,&(pInfo->md_inf[i]),sizeof(LX_PE_HDR_MODE_INFO_T));
					pstParams->win_id = temp;
				}
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set gamma_en
 *
 * @param   *pstParams [in] LX_PE_HDR_GAMMA_EN_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams)
{
	int ret = RET_OK;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("set pstParams[%d] : 0x%08x\n",pstParams->win_id,pstParams->data[0]);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/*****************************************/
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				PE_HDR_LG_0_M19_RdFL(hdr_gamma045_ctrl_00);
				PE_HDR_LG_0_M19_Wr01(hdr_gamma045_ctrl_00,gamma045_mode,0);//0:PQ OETF, 1:0.45gamma
				PE_HDR_LG_0_M19_Wr01(hdr_gamma045_ctrl_00,gamma045_enable,GET_BITS(pstParams->data[0],0,1));
				PE_HDR_LG_0_M19_WrFL(hdr_gamma045_ctrl_00);
				#endif
				/*****************************************/
				pInfo->gamma045_enable[LX_PE_WIN_0] = pstParams->data[0];
				PE_HDR_HW_M19_BACKUP_TRACE("[GM0]en:0x%08x", pstParams->data[0]);
			}
			#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
			if(PE_CHECK_WIN0(pstParams->win_id))
			#else
			if(PE_CHECK_WIN1(pstParams->win_id))
			#endif
			{
				/*****************************************/
				#ifdef PE_HDR_HW_M19_MOVE_TO_FW
				PE_HDR_LG_1_M19_RdFL(hdr_gamma045_ctrl_00);
				PE_HDR_LG_1_M19_Wr01(hdr_gamma045_ctrl_00,gamma045_mode,0);//0:PQ OETF, 1:0.45gamma
				PE_HDR_LG_1_M19_Wr01(hdr_gamma045_ctrl_00,gamma045_enable,GET_BITS(pstParams->data[0],0,1));
				PE_HDR_LG_1_M19_WrFL(hdr_gamma045_ctrl_00);
				#endif
				/*****************************************/
				pInfo->gamma045_enable[LX_PE_WIN_1] = pstParams->data[0];
				#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
				// no need to print
				#else
				PE_HDR_HW_M19_BACKUP_TRACE("[GM1]en:0x%08x", pstParams->data[0]);
				#endif
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get gamma_en
 *
 * @param   *pstParams [in] LX_PE_HDR_GAMMA_EN_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_HDR_LG_0_M19_RdFL(hdr_gamma045_ctrl_00);
				PE_HDR_LG_0_M19_Rd01(hdr_gamma045_ctrl_00,gamma045_enable,pstParams->data[0]);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_HDR_LG_1_M19_RdFL(hdr_gamma045_ctrl_00);
				PE_HDR_LG_1_M19_Rd01(hdr_gamma045_ctrl_00,gamma045_enable,pstParams->data[0]);
			}
			if(PE_CHECK_WIN2(win_id))
			{
				pstParams->data[0] = pInfo->gamma045_enable[LX_PE_WIN_0];
			}
			if(PE_CHECK_WIN3(win_id))
			{
				pstParams->data[0] = pInfo->gamma045_enable[LX_PE_WIN_1];
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_HDR_HW_M19_DBG_PRINT("get pstParams[%d] : 0x%08x\n",pstParams->win_id,pstParams->data[0]);
	} while(0);
	return ret;
}

/**
 * set ccr
 *
 * @param   *pstParams [in] LX_PE_HDR_CCR_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_SetColorCorrect(LX_PE_HDR_CCR_T *pstParams)
{
	int ret = RET_OK;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_M19_DBG_PRINT("set[%d]:%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x\n", \
			pstParams->win_id,pstParams->data[0],pstParams->data[1],\
			pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
			pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
			pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_HDR_LG_0_M19_RdFL(hdr_hue_sat_ctrl);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
				PE_HDR_LG_0_M19_WrFL(hdr_hue_sat_ctrl);
				#ifdef PE_HDR_HW_M19_EN_CC_SDR
				#else
				PE_HDR_LG_0_M19_RdFL(hdr_hue_sat_alpha_ctrl);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pstParams->data[2]);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pstParams->data[3]);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pstParams->data[4]);
				PE_HDR_LG_0_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pstParams->data[5]);
				PE_HDR_LG_0_M19_WrFL(hdr_hue_sat_alpha_ctrl);
				#endif
				PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_00,pstParams->data[6]);
				PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_01,pstParams->data[7]);
				PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_02,pstParams->data[8]);
				PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_03,pstParams->data[9]);
				PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_04,pstParams->data[10]);
				PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_05,pstParams->data[11]);
				PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_06,pstParams->data[12]);
				PE_HDR_LG_0_M19_QWr(hdr_lgain_lut_ctrl_07,pstParams->data[13]);
				PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_00,pstParams->data[14]);
				PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_01,pstParams->data[15]);
				PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_02,pstParams->data[16]);
				PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_03,pstParams->data[17]);
				PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_04,pstParams->data[18]);
				PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_05,pstParams->data[19]);
				PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_06,pstParams->data[20]);
				PE_HDR_LG_0_M19_QWr(hdr_sgain_lut_ctrl_07,pstParams->data[21]);
				pInfo->reg_hue_prsv_ratio[LX_PE_WIN_0] = pstParams->data[0];
				pInfo->reg_sat_prsv_ratio[LX_PE_WIN_0] = pstParams->data[1];
				#ifdef PE_HDR_HW_M19_EN_CC_SDR
				#else
				pInfo->reg_out_sgain_sel[LX_PE_WIN_0] = pstParams->data[2];
				pInfo->reg_out_lgain_sel[LX_PE_WIN_0] = pstParams->data[3];
				pInfo->reg_inp_s_sel[LX_PE_WIN_0] = pstParams->data[4];
				pInfo->reg_inp_l_sel[LX_PE_WIN_0] = pstParams->data[5];
				#endif
				pInfo->lgain_lut[LX_PE_WIN_0][0] = pstParams->data[6];
				pInfo->lgain_lut[LX_PE_WIN_0][1] = pstParams->data[7];
				pInfo->lgain_lut[LX_PE_WIN_0][2] = pstParams->data[8];
				pInfo->lgain_lut[LX_PE_WIN_0][3] = pstParams->data[9];
				pInfo->lgain_lut[LX_PE_WIN_0][4] = pstParams->data[10];
				pInfo->lgain_lut[LX_PE_WIN_0][5] = pstParams->data[11];
				pInfo->lgain_lut[LX_PE_WIN_0][6] = pstParams->data[12];
				pInfo->lgain_lut[LX_PE_WIN_0][7] = pstParams->data[13];
				pInfo->sgain_lut[LX_PE_WIN_0][0] = pstParams->data[14];
				pInfo->sgain_lut[LX_PE_WIN_0][1] = pstParams->data[15];
				pInfo->sgain_lut[LX_PE_WIN_0][2] = pstParams->data[16];
				pInfo->sgain_lut[LX_PE_WIN_0][3] = pstParams->data[17];
				pInfo->sgain_lut[LX_PE_WIN_0][4] = pstParams->data[18];
				pInfo->sgain_lut[LX_PE_WIN_0][5] = pstParams->data[19];
				pInfo->sgain_lut[LX_PE_WIN_0][6] = pstParams->data[20];
				pInfo->sgain_lut[LX_PE_WIN_0][7] = pstParams->data[21];
				PE_HDR_HW_M19_BACKUP_TRACE("[CC0]%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x", \
					pstParams->data[0],pstParams->data[1],\
					pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
					pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
					pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);
			}
			#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
			if(PE_CHECK_WIN0(pstParams->win_id))
			#else
			if(PE_CHECK_WIN1(pstParams->win_id))
			#endif
			{
				PE_HDR_LG_1_M19_RdFL(hdr_hue_sat_ctrl);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
				PE_HDR_LG_1_M19_WrFL(hdr_hue_sat_ctrl);
				#ifdef PE_HDR_HW_M19_EN_CC_SDR
				#else
				PE_HDR_LG_1_M19_RdFL(hdr_hue_sat_alpha_ctrl);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pstParams->data[2]);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pstParams->data[3]);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pstParams->data[4]);
				PE_HDR_LG_1_M19_Wr01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pstParams->data[5]);
				PE_HDR_LG_1_M19_WrFL(hdr_hue_sat_alpha_ctrl);
				#endif
				PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_00,pstParams->data[6]);
				PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_01,pstParams->data[7]);
				PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_02,pstParams->data[8]);
				PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_03,pstParams->data[9]);
				PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_04,pstParams->data[10]);
				PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_05,pstParams->data[11]);
				PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_06,pstParams->data[12]);
				PE_HDR_LG_1_M19_QWr(hdr_lgain_lut_ctrl_07,pstParams->data[13]);
				PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_00,pstParams->data[14]);
				PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_01,pstParams->data[15]);
				PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_02,pstParams->data[16]);
				PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_03,pstParams->data[17]);
				PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_04,pstParams->data[18]);
				PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_05,pstParams->data[19]);
				PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_06,pstParams->data[20]);
				PE_HDR_LG_1_M19_QWr(hdr_sgain_lut_ctrl_07,pstParams->data[21]);
				pInfo->reg_hue_prsv_ratio[LX_PE_WIN_1] = pstParams->data[0];
				pInfo->reg_sat_prsv_ratio[LX_PE_WIN_1] = pstParams->data[1];
				#ifdef PE_HDR_HW_M19_EN_CC_SDR
				#else
				pInfo->reg_out_sgain_sel[LX_PE_WIN_1] = pstParams->data[2];
				pInfo->reg_out_lgain_sel[LX_PE_WIN_1] = pstParams->data[3];
				pInfo->reg_inp_s_sel[LX_PE_WIN_1] = pstParams->data[4];
				pInfo->reg_inp_l_sel[LX_PE_WIN_1] = pstParams->data[5];
				#endif
				pInfo->lgain_lut[LX_PE_WIN_1][0] = pstParams->data[6];
				pInfo->lgain_lut[LX_PE_WIN_1][1] = pstParams->data[7];
				pInfo->lgain_lut[LX_PE_WIN_1][2] = pstParams->data[8];
				pInfo->lgain_lut[LX_PE_WIN_1][3] = pstParams->data[9];
				pInfo->lgain_lut[LX_PE_WIN_1][4] = pstParams->data[10];
				pInfo->lgain_lut[LX_PE_WIN_1][5] = pstParams->data[11];
				pInfo->lgain_lut[LX_PE_WIN_1][6] = pstParams->data[12];
				pInfo->lgain_lut[LX_PE_WIN_1][7] = pstParams->data[13];
				pInfo->sgain_lut[LX_PE_WIN_1][0] = pstParams->data[14];
				pInfo->sgain_lut[LX_PE_WIN_1][1] = pstParams->data[15];
				pInfo->sgain_lut[LX_PE_WIN_1][2] = pstParams->data[16];
				pInfo->sgain_lut[LX_PE_WIN_1][3] = pstParams->data[17];
				pInfo->sgain_lut[LX_PE_WIN_1][4] = pstParams->data[18];
				pInfo->sgain_lut[LX_PE_WIN_1][5] = pstParams->data[19];
				pInfo->sgain_lut[LX_PE_WIN_1][6] = pstParams->data[20];
				pInfo->sgain_lut[LX_PE_WIN_1][7] = pstParams->data[21];
				#ifdef PE_HDR_HW_M19_HFR_DUAL_SETTINGS
				// no need to print
				#else
				PE_HDR_HW_M19_BACKUP_TRACE("[CC1]%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x", \
					pstParams->data[0],pstParams->data[1],\
					pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
					pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
					pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);
				#endif
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get ccr
 *
 * @param   *pstParams [in] LX_PE_HDR_CCR_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_HW_M19_GetColorCorrect(LX_PE_HDR_CCR_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_HDR_HW_M19_SETTINGS_T *pInfo=&_g_pe_hdr_hw_m19_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M19)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_HDR_LG_0_M19_RdFL(hdr_hue_sat_ctrl);
				PE_HDR_LG_0_M19_Rd01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
				PE_HDR_LG_0_M19_Rd01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
				PE_HDR_LG_0_M19_RdFL(hdr_hue_sat_alpha_ctrl);
				PE_HDR_LG_0_M19_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pstParams->data[2]);
				PE_HDR_LG_0_M19_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pstParams->data[3]);
				PE_HDR_LG_0_M19_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pstParams->data[4]);
				PE_HDR_LG_0_M19_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pstParams->data[5]);
				PE_HDR_LG_0_M19_RdFL(hdr_lgain_lut_ctrl_00);
				PE_HDR_LG_0_M19_RdFL(hdr_lgain_lut_ctrl_01);
				PE_HDR_LG_0_M19_RdFL(hdr_lgain_lut_ctrl_02);
				PE_HDR_LG_0_M19_RdFL(hdr_lgain_lut_ctrl_03);
				PE_HDR_LG_0_M19_RdFL(hdr_lgain_lut_ctrl_04);
				PE_HDR_LG_0_M19_RdFL(hdr_lgain_lut_ctrl_05);
				PE_HDR_LG_0_M19_RdFL(hdr_lgain_lut_ctrl_06);
				PE_HDR_LG_0_M19_RdFL(hdr_lgain_lut_ctrl_07);
				PE_HDR_LG_0_M19_RdFL(hdr_sgain_lut_ctrl_00);
				PE_HDR_LG_0_M19_RdFL(hdr_sgain_lut_ctrl_01);
				PE_HDR_LG_0_M19_RdFL(hdr_sgain_lut_ctrl_02);
				PE_HDR_LG_0_M19_RdFL(hdr_sgain_lut_ctrl_03);
				PE_HDR_LG_0_M19_RdFL(hdr_sgain_lut_ctrl_04);
				PE_HDR_LG_0_M19_RdFL(hdr_sgain_lut_ctrl_05);
				PE_HDR_LG_0_M19_RdFL(hdr_sgain_lut_ctrl_06);
				PE_HDR_LG_0_M19_RdFL(hdr_sgain_lut_ctrl_07);
				pstParams->data[6]  = PE_HDR_LG_0_M19_Rd(hdr_lgain_lut_ctrl_00);
				pstParams->data[7]  = PE_HDR_LG_0_M19_Rd(hdr_lgain_lut_ctrl_01);
				pstParams->data[8]  = PE_HDR_LG_0_M19_Rd(hdr_lgain_lut_ctrl_02);
				pstParams->data[9]  = PE_HDR_LG_0_M19_Rd(hdr_lgain_lut_ctrl_03);
				pstParams->data[10] = PE_HDR_LG_0_M19_Rd(hdr_lgain_lut_ctrl_04);
				pstParams->data[11] = PE_HDR_LG_0_M19_Rd(hdr_lgain_lut_ctrl_05);
				pstParams->data[12] = PE_HDR_LG_0_M19_Rd(hdr_lgain_lut_ctrl_06);
				pstParams->data[13] = PE_HDR_LG_0_M19_Rd(hdr_lgain_lut_ctrl_07);
				pstParams->data[14] = PE_HDR_LG_0_M19_Rd(hdr_sgain_lut_ctrl_00);
				pstParams->data[15] = PE_HDR_LG_0_M19_Rd(hdr_sgain_lut_ctrl_01);
				pstParams->data[16] = PE_HDR_LG_0_M19_Rd(hdr_sgain_lut_ctrl_02);
				pstParams->data[17] = PE_HDR_LG_0_M19_Rd(hdr_sgain_lut_ctrl_03);
				pstParams->data[18] = PE_HDR_LG_0_M19_Rd(hdr_sgain_lut_ctrl_04);
				pstParams->data[19] = PE_HDR_LG_0_M19_Rd(hdr_sgain_lut_ctrl_05);
				pstParams->data[20] = PE_HDR_LG_0_M19_Rd(hdr_sgain_lut_ctrl_06);
				pstParams->data[21] = PE_HDR_LG_0_M19_Rd(hdr_sgain_lut_ctrl_07);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_HDR_LG_1_M19_RdFL(hdr_hue_sat_ctrl);
				PE_HDR_LG_1_M19_Rd01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
				PE_HDR_LG_1_M19_Rd01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
				PE_HDR_LG_1_M19_RdFL(hdr_hue_sat_alpha_ctrl);
				PE_HDR_LG_1_M19_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pstParams->data[2]);
				PE_HDR_LG_1_M19_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pstParams->data[3]);
				PE_HDR_LG_1_M19_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pstParams->data[4]);
				PE_HDR_LG_1_M19_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pstParams->data[5]);
				PE_HDR_LG_1_M19_RdFL(hdr_lgain_lut_ctrl_00);
				PE_HDR_LG_1_M19_RdFL(hdr_lgain_lut_ctrl_01);
				PE_HDR_LG_1_M19_RdFL(hdr_lgain_lut_ctrl_02);
				PE_HDR_LG_1_M19_RdFL(hdr_lgain_lut_ctrl_03);
				PE_HDR_LG_1_M19_RdFL(hdr_lgain_lut_ctrl_04);
				PE_HDR_LG_1_M19_RdFL(hdr_lgain_lut_ctrl_05);
				PE_HDR_LG_1_M19_RdFL(hdr_lgain_lut_ctrl_06);
				PE_HDR_LG_1_M19_RdFL(hdr_lgain_lut_ctrl_07);
				PE_HDR_LG_1_M19_RdFL(hdr_sgain_lut_ctrl_00);
				PE_HDR_LG_1_M19_RdFL(hdr_sgain_lut_ctrl_01);
				PE_HDR_LG_1_M19_RdFL(hdr_sgain_lut_ctrl_02);
				PE_HDR_LG_1_M19_RdFL(hdr_sgain_lut_ctrl_03);
				PE_HDR_LG_1_M19_RdFL(hdr_sgain_lut_ctrl_04);
				PE_HDR_LG_1_M19_RdFL(hdr_sgain_lut_ctrl_05);
				PE_HDR_LG_1_M19_RdFL(hdr_sgain_lut_ctrl_06);
				PE_HDR_LG_1_M19_RdFL(hdr_sgain_lut_ctrl_07);
				pstParams->data[6]  = PE_HDR_LG_1_M19_Rd(hdr_lgain_lut_ctrl_00);
				pstParams->data[7]  = PE_HDR_LG_1_M19_Rd(hdr_lgain_lut_ctrl_01);
				pstParams->data[8]  = PE_HDR_LG_1_M19_Rd(hdr_lgain_lut_ctrl_02);
				pstParams->data[9]  = PE_HDR_LG_1_M19_Rd(hdr_lgain_lut_ctrl_03);
				pstParams->data[10] = PE_HDR_LG_1_M19_Rd(hdr_lgain_lut_ctrl_04);
				pstParams->data[11] = PE_HDR_LG_1_M19_Rd(hdr_lgain_lut_ctrl_05);
				pstParams->data[12] = PE_HDR_LG_1_M19_Rd(hdr_lgain_lut_ctrl_06);
				pstParams->data[13] = PE_HDR_LG_1_M19_Rd(hdr_lgain_lut_ctrl_07);
				pstParams->data[14] = PE_HDR_LG_1_M19_Rd(hdr_sgain_lut_ctrl_00);
				pstParams->data[15] = PE_HDR_LG_1_M19_Rd(hdr_sgain_lut_ctrl_01);
				pstParams->data[16] = PE_HDR_LG_1_M19_Rd(hdr_sgain_lut_ctrl_02);
				pstParams->data[17] = PE_HDR_LG_1_M19_Rd(hdr_sgain_lut_ctrl_03);
				pstParams->data[18] = PE_HDR_LG_1_M19_Rd(hdr_sgain_lut_ctrl_04);
				pstParams->data[19] = PE_HDR_LG_1_M19_Rd(hdr_sgain_lut_ctrl_05);
				pstParams->data[20] = PE_HDR_LG_1_M19_Rd(hdr_sgain_lut_ctrl_06);
				pstParams->data[21] = PE_HDR_LG_1_M19_Rd(hdr_sgain_lut_ctrl_07);
			}
			if(PE_CHECK_WIN2(win_id))
			{
				pstParams->data[0] = pInfo->reg_hue_prsv_ratio[LX_PE_WIN_0];
				pstParams->data[1] = pInfo->reg_sat_prsv_ratio[LX_PE_WIN_0];
				pstParams->data[2] = pInfo->reg_out_sgain_sel[LX_PE_WIN_0];
				pstParams->data[3] = pInfo->reg_out_lgain_sel[LX_PE_WIN_0];
				pstParams->data[4] = pInfo->reg_inp_s_sel[LX_PE_WIN_0];
				pstParams->data[5] = pInfo->reg_inp_l_sel[LX_PE_WIN_0];
				pstParams->data[6]  = pInfo->lgain_lut[LX_PE_WIN_0][0];
				pstParams->data[7]  = pInfo->lgain_lut[LX_PE_WIN_0][1];
				pstParams->data[8]  = pInfo->lgain_lut[LX_PE_WIN_0][2];
				pstParams->data[9]  = pInfo->lgain_lut[LX_PE_WIN_0][3];
				pstParams->data[10] = pInfo->lgain_lut[LX_PE_WIN_0][4];
				pstParams->data[11] = pInfo->lgain_lut[LX_PE_WIN_0][5];
				pstParams->data[12] = pInfo->lgain_lut[LX_PE_WIN_0][6];
				pstParams->data[13] = pInfo->lgain_lut[LX_PE_WIN_0][7];
				pstParams->data[14] = pInfo->sgain_lut[LX_PE_WIN_0][0];
				pstParams->data[15] = pInfo->sgain_lut[LX_PE_WIN_0][1];
				pstParams->data[16] = pInfo->sgain_lut[LX_PE_WIN_0][2];
				pstParams->data[17] = pInfo->sgain_lut[LX_PE_WIN_0][3];
				pstParams->data[18] = pInfo->sgain_lut[LX_PE_WIN_0][4];
				pstParams->data[19] = pInfo->sgain_lut[LX_PE_WIN_0][5];
				pstParams->data[20] = pInfo->sgain_lut[LX_PE_WIN_0][6];
				pstParams->data[21] = pInfo->sgain_lut[LX_PE_WIN_0][7];
			}
			if(PE_CHECK_WIN3(win_id))
			{
				pstParams->data[0] = pInfo->reg_hue_prsv_ratio[LX_PE_WIN_1];
				pstParams->data[1] = pInfo->reg_sat_prsv_ratio[LX_PE_WIN_1];
				pstParams->data[2] = pInfo->reg_out_sgain_sel[LX_PE_WIN_1];
				pstParams->data[3] = pInfo->reg_out_lgain_sel[LX_PE_WIN_1];
				pstParams->data[4] = pInfo->reg_inp_s_sel[LX_PE_WIN_1];
				pstParams->data[5] = pInfo->reg_inp_l_sel[LX_PE_WIN_1];
				pstParams->data[6]  = pInfo->lgain_lut[LX_PE_WIN_1][0];
				pstParams->data[7]  = pInfo->lgain_lut[LX_PE_WIN_1][1];
				pstParams->data[8]  = pInfo->lgain_lut[LX_PE_WIN_1][2];
				pstParams->data[9]  = pInfo->lgain_lut[LX_PE_WIN_1][3];
				pstParams->data[10] = pInfo->lgain_lut[LX_PE_WIN_1][4];
				pstParams->data[11] = pInfo->lgain_lut[LX_PE_WIN_1][5];
				pstParams->data[12] = pInfo->lgain_lut[LX_PE_WIN_1][6];
				pstParams->data[13] = pInfo->lgain_lut[LX_PE_WIN_1][7];
				pstParams->data[14] = pInfo->sgain_lut[LX_PE_WIN_1][0];
				pstParams->data[15] = pInfo->sgain_lut[LX_PE_WIN_1][1];
				pstParams->data[16] = pInfo->sgain_lut[LX_PE_WIN_1][2];
				pstParams->data[17] = pInfo->sgain_lut[LX_PE_WIN_1][3];
				pstParams->data[18] = pInfo->sgain_lut[LX_PE_WIN_1][4];
				pstParams->data[19] = pInfo->sgain_lut[LX_PE_WIN_1][5];
				pstParams->data[20] = pInfo->sgain_lut[LX_PE_WIN_1][6];
				pstParams->data[21] = pInfo->sgain_lut[LX_PE_WIN_1][7];
			}
		}
		else
		{
			PE_HDR_HW_M19_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_HDR_HW_M19_DBG_PRINT("get[%d]:%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x\n", \
			pstParams->win_id,pstParams->data[0],pstParams->data[1],\
			pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
			pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
			pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);
	} while(0);
	return ret;
}

