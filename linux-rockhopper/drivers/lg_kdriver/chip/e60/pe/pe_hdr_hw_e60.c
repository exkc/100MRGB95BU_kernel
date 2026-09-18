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

/** @file pe_hdr_hw_e60.c
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
#include "sys_io.h"

#include "pe_hw_e60.h"
#include "pe_reg_e60.h"
#include "pe_fwi_e60.h"
#include "pe_hdr_hw_e60.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* hdr drv ver, yyyy/mm/dd/hh:mm */
#define PE_HDR_HW_E60_DRV_VER		"2022/10/24/13:60"

#define PE_HDR_HW_E60_BUF_MAX		50

#define PE_HDR_HW_E60_CONNECT_MODE_SDR	(0)
#define PE_HDR_HW_E60_CONNECT_MODE_H10	(1)
#define PE_HDR_HW_E60_CONNECT_MODE_HLG	(2)
#define PE_HDR_HW_E60_CONNECT_MODE_S2H	(3)
#define PE_HDR_HW_E60_CONNECT_MODE_TEC	(4)

#define PE_HDR_HW_E60_LUT_TYPE_A	(0xA)
#define PE_HDR_HW_E60_LUT_TYPE_B	(0xB)
#define PE_HDR_HW_E60_LUT_TYPE_C	(0xC)
#define PE_HDR_HW_E60_LUT_TYPE_D	(0xD)
#define PE_HDR_HW_E60_LUT_TYPE_E	(0xE)
#define PE_HDR_HW_E60_LUT_TYPE_F	(0xF)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_HDR_HW_E60_ERROR	printk

#define PE_HDR_HW_E60_DBG_PRINT(fmt,args...)	\
	if(_g_hdr_hw_e60_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)

#define PE_HDR_HW_E60_CHECK_CODE(_checker,_action,fmt,args...) \
	{if(_checker){PE_HDR_HW_E60_ERROR(fmt,##args);_action;}}

#define PE_HDR_HW_E60_BACKUP_TRACE(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_HDR_HW_E60_SetTraceDataBuf(0,_trace_buf);\
	}

#define PE_HDR_HW_E60_BACKUP_TRACE_LUT(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_HDR_HW_E60_SetTraceDataBuf(1,_trace_buf);\
	}

#define PE_HDR_HW_E60_CONNECT_TO_STR(_x)		(\
	((_x)==PE_HDR_HW_E60_CONNECT_MODE_SDR)?	"SDR":\
	((_x)==PE_HDR_HW_E60_CONNECT_MODE_H10)?	"H10":\
	((_x)==PE_HDR_HW_E60_CONNECT_MODE_HLG)?	"HLG":\
	((_x)==PE_HDR_HW_E60_CONNECT_MODE_S2H)?	"S2H":\
	((_x)==PE_HDR_HW_E60_CONNECT_MODE_TEC)?	"TEC":\
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
PE_HDR_HW_E60_TIME_T;

/**
 *	pe trace data buffer type
 */
typedef struct {
	PE_HDR_HW_E60_TIME_T time;		///< time
	char str[PE_TRACE_STR_SIZE];	///< str
}
PE_HDR_HW_E60_DATA_BUF_T;

typedef enum
{
	PE_HDR_HW_E60_CORE_MODE_1_2K,
	PE_HDR_HW_E60_CORE_MODE_2_4K,
	PE_HDR_HW_E60_CORE_MODE_4_8K,
	PE_HDR_HW_E60_CORE_MODE_NOP
}
PE_HDR_HW_E60_CORE_MODE_T;

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
static int PE_HDR_HW_E60_SortTraceDataBuf(UINT32 type, PE_HDR_HW_E60_DATA_BUF_T *dst);
static int PE_HDR_HW_E60_SetTraceDataBuf(UINT32 type, char *data);
static UINT32 PE_HDR_HW_E60_GetConnectMode(UINT32 win_id);
//static UINT32 PE_HDR_HW_E60_GetInfoOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_E60_GetToneConnectMode(UINT32 path);
static UINT32 PE_HDR_HW_E60_GetToneOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_E60_IncreaseToneCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_E60_GetYlutOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_E60_IncreaseYlutCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_E60_GetEotfOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_E60_IncreaseEotfCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_E60_GetEotfCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_E60_GetOetfOffset(UINT32 win_id, UINT32 type);
static UINT32 PE_HDR_HW_E60_IncreaseOetfCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_E60_GetOetfCount(UINT32 win_id, UINT32 ofst);
static UINT32 PE_HDR_HW_E60_SetSupportInfo(UINT32 win_id, UINT32 info);
static int PE_HDR_HW_E60_InitTonemapLut(PE_CFG_CTRL_T *pstParams);
static int PE_HDR_HW_E60_InitYgainLut(PE_CFG_CTRL_T *pstParams);
static int PE_HDR_HW_E60_InitHdrInfo(PE_CFG_CTRL_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_hdr_hw_e60_trace=0x0;	//default should be off.
static PE_HDR_HW_E60_SETTINGS_T _g_pe_hdr_hw_e60_info;
static PE_HDR_HW_E60_DATA_BUF_T *_gp_pe_hdr_hw_e60_buf_curr = NULL;
static PE_HDR_HW_E60_DATA_BUF_T *_gp_pe_hdr_hw_e60_buf_sort = NULL;
static PE_HDR_HW_E60_DATA_BUF_T *_gp_pe_hdr_hw_e60_lut_buf_curr = NULL;
static PE_HDR_HW_E60_DATA_BUF_T *_gp_pe_hdr_hw_e60_lut_buf_sort = NULL;

/* normal bypass */
const UINT32 _g_hdr_tm_lut_bypass_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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

/* s2h bypass llut0,1 */
const UINT32 _g_hdr_tm_lut_x_data1_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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
/* s2h bypass llut0,1 */
const UINT32 _g_hdr_tm_lut_y_data1_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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

/* s2h bypass llut2 */
const UINT32 _g_hdr_tm_lut_x_data2_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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
/* s2h bypass llut2 */
const UINT32 _g_hdr_tm_lut_y_data2_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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
const UINT32 _g_hdr_tm_lut_x_data3_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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
const UINT32 _g_hdr_tm_lut_y_data3_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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

/* h10 x(201801) */
const UINT32 _g_hdr_tm_lut_x_data5_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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
const UINT32 _g_hdr_tm_lut_y_data5_e60[PE_HDR_HW_E60_TM_LUT_MAX] = {
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
const UINT32 _g_hdr_yg_lut_bypass_e60[PE_HDR_HW_E60_YG_LUT_MAX] = {
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
/* hlg */
const UINT32 _g_hdr_yg_lut_data0_e60[PE_HDR_HW_E60_YG_LUT_MAX] = {
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

const UINT16 _g_pe_hdr_hw_e60_csc_mtrx_bypass[PE_NUM_OF_CSC_COEF] = {
0x1000, 0x0000, 0x0000,		//  1.000, 0.000, 0.000
0x0000, 0x1000, 0x0000,		//  0.000, 1.000, 0.000
0x0000, 0x0000, 0x1000};	//  0.000, 0.000, 1.000

const UINT16 _g_pe_hdr_hw_e60_pcc_mtrx_default[PE_NUM_OF_CSC_COEF] = {
0x121f, 0x7fde, 0x7e02,		//   1.1326, -0.0083, -0.1245,
0x7e65, 0x11e5, 0x7fb6,		//  -0.1003, 1.1184, -0.0181,
0x769a, 0x7ed6, 0x1a8f};	//  -0.5874, -0.0728, 1.6599,

/*========================================================================================
	Implementation Group
========================================================================================*/
static int PE_HDR_HW_E60_SortTraceDataBuf(UINT32 type, PE_HDR_HW_E60_DATA_BUF_T *dst)
{
	int ret = RET_OK;
	UINT32 size=0, i=0, max=0;
	UINT32 j=0, s0=0, s1=0, us0=0, us1=0;
	PE_HDR_HW_E60_DATA_BUF_T temp;
	PE_HDR_HW_E60_DATA_BUF_T *src;

	do{
		CHECK_KNULL(dst);
		if (type == 1)	src = _gp_pe_hdr_hw_e60_lut_buf_curr;
		else			src = _gp_pe_hdr_hw_e60_buf_curr;
		if (src == NULL)	{ret = RET_ERROR;	break;}
		max = PE_HDR_HW_E60_BUF_MAX;
		size = sizeof(PE_HDR_HW_E60_DATA_BUF_T);
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
	return ret;
}

int PE_HDR_HW_E60_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0, type=0;
	PE_HDR_HW_E60_DATA_BUF_T *p_buf;
	UINT32 *p_data = NULL;
	PE_HDR_HW_E60_TIME_T *p_time = NULL;
	char *p_str = NULL;

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		type = pstParams->data[0];
		if (type == 1)	p_buf = _gp_pe_hdr_hw_e60_lut_buf_sort;
		else			p_buf = _gp_pe_hdr_hw_e60_buf_sort;
		if (p_buf == NULL)	{ret = RET_ERROR;	break;}
		rd_cnt = pstParams->oper;
		if (rd_cnt<PE_HDR_HW_E60_BUF_MAX)
		{
			if(rd_cnt==0)
			{
				ret = PE_HDR_HW_E60_SortTraceDataBuf(type,p_buf);
				if (ret != RET_OK)	{ret = RET_ERROR;	break;}
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

static int PE_HDR_HW_E60_SetTraceDataBuf(UINT32 type, char *data)
{
    int ret = RET_OK;
	UINT32 i = 0;
	char *p_str = NULL;
	PE_HDR_HW_E60_TIME_T *p_time = NULL;
	static UINT32 cnt = 0;
	PE_HDR_HW_E60_DATA_BUF_T *p_buf;
	do{
		CHECK_KNULL(data);
		if (type == 1)	p_buf = _gp_pe_hdr_hw_e60_lut_buf_curr;
		else			p_buf = _gp_pe_hdr_hw_e60_buf_curr;
		if (p_buf == NULL)	{ret = RET_ERROR;	break;}
		if(cnt>=PE_HDR_HW_E60_BUF_MAX)	cnt = 0;
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

static UINT32 PE_HDR_HW_E60_GetConnectMode(UINT32 win_id)
{
	UINT32 mode;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	/* wid0 only */
	LX_PE_HDR_OP_MD_T *p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_0].data[0]));//main info only

	if (p_op->connect == 2)								mode = PE_HDR_HW_E60_CONNECT_MODE_H10;
	else if (p_op->connect == 5)						mode = PE_HDR_HW_E60_CONNECT_MODE_HLG;
	else if (p_op->connect == 3)						mode = PE_HDR_HW_E60_CONNECT_MODE_TEC;
	else if (p_op->connect == 0 && p_op->hdrcase == 4)	mode = PE_HDR_HW_E60_CONNECT_MODE_S2H;
	else												mode = PE_HDR_HW_E60_CONNECT_MODE_SDR;

	return mode;
}
#if 0	//ready
static UINT32 PE_HDR_HW_E60_GetInfoOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst = 0xffffffff;
	PE_HDR_DDR_E60_HEADER0_T header0;
	UINT32 *pU32Header0 = (UINT32 *)&header0;

	if (win_id!=0)	return ofst;

	wmb();rmb();
	*pU32Header0 = gPE_HDR_DDR_E60[0];
	rmb();

	if (type == PE_HDR_HW_E60_LUT_TYPE_A)
	{
		if (header0.cnt_info_a == 1)		ofst = PE_HDR_DDR_E60_INFO_A1_OFST;
		else if (header0.cnt_info_a == 2)	ofst = PE_HDR_DDR_E60_INFO_A2_OFST;
		else if (header0.cnt_info_a == 3)	ofst = PE_HDR_DDR_E60_INFO_A3_OFST;
	}
	else if (type == PE_HDR_HW_E60_LUT_TYPE_B)
	{
		if (header0.cnt_info_b == 1)		ofst = PE_HDR_DDR_E60_INFO_B1_OFST;
		else if (header0.cnt_info_b == 2)	ofst = PE_HDR_DDR_E60_INFO_B2_OFST;
		else if (header0.cnt_info_b == 3)	ofst = PE_HDR_DDR_E60_INFO_B3_OFST;
	}
	else if (type == PE_HDR_HW_E60_LUT_TYPE_C)
	{
		if (header0.cnt_info_c == 1)		ofst = PE_HDR_DDR_E60_INFO_C1_OFST;
		else if (header0.cnt_info_c == 2)	ofst = PE_HDR_DDR_E60_INFO_C2_OFST;
		else if (header0.cnt_info_c == 3)	ofst = PE_HDR_DDR_E60_INFO_C3_OFST;
	}
	else if (type == PE_HDR_HW_E60_LUT_TYPE_D)
	{
		if (header0.cnt_info_d == 1)		ofst = PE_HDR_DDR_E60_INFO_D1_OFST;
		else if (header0.cnt_info_d == 2)	ofst = PE_HDR_DDR_E60_INFO_D2_OFST;
		else if (header0.cnt_info_d == 3)	ofst = PE_HDR_DDR_E60_INFO_D3_OFST;
	}

	return ofst;
}
#endif
static UINT32 PE_HDR_HW_E60_GetToneConnectMode(UINT32 path)
{
	UINT32 mode;
	if (path == 2)			mode = PE_HDR_HW_E60_CONNECT_MODE_H10;
	else if (path == 5)		mode = PE_HDR_HW_E60_CONNECT_MODE_HLG;
	else if (path == 3)		mode = PE_HDR_HW_E60_CONNECT_MODE_TEC;
	else if (path == 4)		mode = PE_HDR_HW_E60_CONNECT_MODE_S2H;
	else					mode = PE_HDR_HW_E60_CONNECT_MODE_SDR;
	return mode;
}

static UINT32 PE_HDR_HW_E60_GetToneOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	/* A:HLG, B:HDR10, C:S2H, D:PRIME, E:SDR, F:reserved */
	if (type == PE_HDR_HW_E60_LUT_TYPE_A)				ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_A_OFST:PE_HDR_DDR1_E60_TONE_A_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_B)			ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_B_OFST:PE_HDR_DDR1_E60_TONE_B_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_C)			ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_C_OFST:PE_HDR_DDR1_E60_TONE_C_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_D)			ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_D_OFST:PE_HDR_DDR1_E60_TONE_D_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_E)			ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_E_OFST:PE_HDR_DDR1_E60_TONE_E_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_F)			ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_F_OFST:PE_HDR_DDR1_E60_TONE_F_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_HLG)	ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_A_OFST:PE_HDR_DDR1_E60_TONE_A_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_H10)	ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_B_OFST:PE_HDR_DDR1_E60_TONE_B_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_S2H)	ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_C_OFST:PE_HDR_DDR1_E60_TONE_C_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_TEC)	ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_D_OFST:PE_HDR_DDR1_E60_TONE_D_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_SDR)	ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_E_OFST:PE_HDR_DDR1_E60_TONE_E_OFST;
	else												ofst = (win_id==0)? PE_HDR_DDR0_E60_TONE_F_OFST:PE_HDR_DDR1_E60_TONE_F_OFST;

	return ofst;
}

static UINT32 PE_HDR_HW_E60_IncreaseToneCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_E60_HEADER2_T header2;
	PE_HDR_DDR_E60_HEADER5_T header5;
	UINT32 *pU32Header2 = (UINT32 *)&header2;
	UINT32 *pU32Header5 = (UINT32 *)&header5;
	rmb();
	if (win_id==0)
	{
		*pU32Header2 = gPE_HDR_DDR_E60[2];
		if (ofst == PE_HDR_DDR0_E60_TONE_A_OFST)
			count = header2.cnt_tone_a = (header2.cnt_tone_a == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header2.cnt_tone_a+1);
		else if (ofst == PE_HDR_DDR0_E60_TONE_B_OFST)
			count = header2.cnt_tone_b = (header2.cnt_tone_b == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header2.cnt_tone_b+1);
		else if (ofst == PE_HDR_DDR0_E60_TONE_C_OFST)
			count = header2.cnt_tone_c = (header2.cnt_tone_c == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header2.cnt_tone_c+1);
		else if (ofst == PE_HDR_DDR0_E60_TONE_D_OFST)
			count = header2.cnt_tone_d = (header2.cnt_tone_d == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header2.cnt_tone_d+1);
		else if (ofst == PE_HDR_DDR0_E60_TONE_E_OFST)
			count = header2.cnt_tone_e = (header2.cnt_tone_e == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header2.cnt_tone_e+1);
		else//if (ofst == PE_HDR_DDR0_E60_TONE_F_OFST)
			count = header2.cnt_tone_f = (header2.cnt_tone_f == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header2.cnt_tone_f+1);
		gPE_HDR_DDR_E60[2] = *pU32Header2;
	}
	else
	{
		*pU32Header5 = gPE_HDR_DDR_E60[5];
		if (ofst == PE_HDR_DDR1_E60_TONE_A_OFST)
			count = header5.cnt_tone_a = (header5.cnt_tone_a == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header5.cnt_tone_a+1);
		else if (ofst == PE_HDR_DDR1_E60_TONE_B_OFST)
			count = header5.cnt_tone_b = (header5.cnt_tone_b == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header5.cnt_tone_b+1);
		else if (ofst == PE_HDR_DDR1_E60_TONE_C_OFST)
			count = header5.cnt_tone_c = (header5.cnt_tone_c == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header5.cnt_tone_c+1);
		else if (ofst == PE_HDR_DDR1_E60_TONE_D_OFST)
			count = header5.cnt_tone_d = (header5.cnt_tone_d == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header5.cnt_tone_d+1);
		else if (ofst == PE_HDR_DDR1_E60_TONE_E_OFST)
			count = header5.cnt_tone_e = (header5.cnt_tone_e == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header5.cnt_tone_e+1);
		else//if (ofst == PE_HDR_DDR1_E60_TONE_F_OFST)
			count = header5.cnt_tone_f = (header5.cnt_tone_f == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header5.cnt_tone_f+1);
		gPE_HDR_DDR_E60[5] = *pU32Header5;
	}
	wmb();
	return count;
}

static UINT32 PE_HDR_HW_E60_GetYlutOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	/* A:HLG, B:reserved */
	if (type == PE_HDR_HW_E60_LUT_TYPE_A)				ofst = (win_id==0)? PE_HDR_DDR0_E60_YLUT_A_OFST:PE_HDR_DDR1_E60_YLUT_A_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_B)			ofst = (win_id==0)? PE_HDR_DDR0_E60_YLUT_B_OFST:PE_HDR_DDR1_E60_YLUT_B_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_HLG)	ofst = (win_id==0)? PE_HDR_DDR0_E60_YLUT_A_OFST:PE_HDR_DDR1_E60_YLUT_A_OFST;
	else												ofst = (win_id==0)? PE_HDR_DDR0_E60_YLUT_B_OFST:PE_HDR_DDR1_E60_YLUT_B_OFST;

	return ofst;
}

static UINT32 PE_HDR_HW_E60_IncreaseYlutCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_E60_HEADER2_T header2;
	PE_HDR_DDR_E60_HEADER5_T header5;
	UINT32 *pU32Header2 = (UINT32 *)&header2;
	UINT32 *pU32Header5 = (UINT32 *)&header5;
	rmb();
	if (win_id==0)
	{
		*pU32Header2 = gPE_HDR_DDR_E60[2];
		if (ofst == PE_HDR_DDR0_E60_YLUT_A_OFST)
			count = header2.cnt_ylut_a = (header2.cnt_ylut_a == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header2.cnt_ylut_a+1);
		else
			count = header2.cnt_ylut_b = (header2.cnt_ylut_b == PE_HDR_DDR_E60_YG_CNT_MAX)? 1:(header2.cnt_ylut_b+1);
		gPE_HDR_DDR_E60[2] = *pU32Header2;
	}
	else
	{
		*pU32Header5 = gPE_HDR_DDR_E60[5];
		if (ofst == PE_HDR_DDR1_E60_YLUT_A_OFST)
			count = header5.cnt_ylut_a = (header5.cnt_ylut_a == PE_HDR_DDR_E60_TM_CNT_MAX)? 1:(header5.cnt_ylut_a+1);
		else
			count = header5.cnt_ylut_b = (header5.cnt_ylut_b == PE_HDR_DDR_E60_YG_CNT_MAX)? 1:(header5.cnt_ylut_b+1);
		gPE_HDR_DDR_E60[5] = *pU32Header5;
	}
	wmb();
	return count;
}

static UINT32 PE_HDR_HW_E60_GetEotfOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	/* A:HLG, B:HDR10(10K), C,D:reserved */
	if (type == PE_HDR_HW_E60_LUT_TYPE_A)				ofst = (win_id==0)? PE_HDR_DDR0_E60_EOTF_A_OFST:PE_HDR_DDR1_E60_EOTF_A_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_B)			ofst = (win_id==0)? PE_HDR_DDR0_E60_EOTF_B_OFST:PE_HDR_DDR1_E60_EOTF_B_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_C)			ofst = (win_id==0)? PE_HDR_DDR0_E60_EOTF_C_OFST:PE_HDR_DDR1_E60_EOTF_C_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_D)			ofst = (win_id==0)? PE_HDR_DDR0_E60_EOTF_D_OFST:PE_HDR_DDR1_E60_EOTF_D_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_HLG)	ofst = (win_id==0)? PE_HDR_DDR0_E60_EOTF_A_OFST:PE_HDR_DDR1_E60_EOTF_A_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_H10)	ofst = (win_id==0)? PE_HDR_DDR0_E60_EOTF_B_OFST:PE_HDR_DDR1_E60_EOTF_B_OFST;
	else												ofst = (win_id==0)? PE_HDR_DDR0_E60_EOTF_D_OFST:PE_HDR_DDR1_E60_EOTF_D_OFST;

	return ofst;
}

static UINT32 PE_HDR_HW_E60_IncreaseEotfCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_E60_HEADER1_T header1;
	PE_HDR_DDR_E60_HEADER4_T header4;
	UINT32 *pU32Header1 = (UINT32 *)&header1;
	UINT32 *pU32Header4 = (UINT32 *)&header4;
	rmb();
	if (win_id==0)
	{
		*pU32Header1 = gPE_HDR_DDR_E60[1];
		if (ofst == PE_HDR_DDR0_E60_EOTF_A_OFST)
			count = header1.cnt_eotf_a = (header1.cnt_eotf_a == PE_HDR_DDR_E60_EO_CNT_MAX)? 1:(header1.cnt_eotf_a+1);
		else if (ofst == PE_HDR_DDR0_E60_EOTF_B_OFST)
			count = header1.cnt_eotf_b = (header1.cnt_eotf_b == PE_HDR_DDR_E60_EO_CNT_MAX)? 1:(header1.cnt_eotf_b+1);
		else if (ofst == PE_HDR_DDR0_E60_EOTF_C_OFST)
			count = header1.cnt_eotf_c = (header1.cnt_eotf_c == PE_HDR_DDR_E60_EO_CNT_MAX)? 1:(header1.cnt_eotf_c+1);
		else
			count = header1.cnt_eotf_d = (header1.cnt_eotf_d == PE_HDR_DDR_E60_EO_CNT_MAX)? 1:(header1.cnt_eotf_d+1);
		gPE_HDR_DDR_E60[1] = *pU32Header1;
	}
	else
	{
		*pU32Header4 = gPE_HDR_DDR_E60[4];
		if (ofst == PE_HDR_DDR1_E60_EOTF_A_OFST)
			count = header4.cnt_eotf_a = (header4.cnt_eotf_a == PE_HDR_DDR_E60_EO_CNT_MAX)? 1:(header4.cnt_eotf_a+1);
		else if (ofst == PE_HDR_DDR1_E60_EOTF_B_OFST)
			count = header4.cnt_eotf_b = (header4.cnt_eotf_b == PE_HDR_DDR_E60_EO_CNT_MAX)? 1:(header4.cnt_eotf_b+1);
		else if (ofst == PE_HDR_DDR1_E60_EOTF_C_OFST)
			count = header4.cnt_eotf_c = (header4.cnt_eotf_c == PE_HDR_DDR_E60_EO_CNT_MAX)? 1:(header4.cnt_eotf_c+1);
		else
			count = header4.cnt_eotf_d = (header4.cnt_eotf_d == PE_HDR_DDR_E60_EO_CNT_MAX)? 1:(header4.cnt_eotf_d+1);
		gPE_HDR_DDR_E60[4] = *pU32Header4;
	}
	wmb();
	return count;
}

static UINT32 PE_HDR_HW_E60_GetEotfCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_E60_HEADER1_T header1;
	PE_HDR_DDR_E60_HEADER4_T header4;
	UINT32 *pU32Header1 = (UINT32 *)&header1;
	UINT32 *pU32Header4 = (UINT32 *)&header4;
	rmb();
	if (win_id==0)
	{
		*pU32Header1 = gPE_HDR_DDR_E60[1];
		if (ofst == PE_HDR_DDR0_E60_EOTF_A_OFST)		count = header1.cnt_eotf_a;
		else if (ofst == PE_HDR_DDR0_E60_EOTF_B_OFST)	count = header1.cnt_eotf_b;
		else if (ofst == PE_HDR_DDR0_E60_EOTF_C_OFST)	count = header1.cnt_eotf_c;
		else											count = header1.cnt_eotf_d;
	}
	else
	{
		*pU32Header4 = gPE_HDR_DDR_E60[4];
		if (ofst == PE_HDR_DDR1_E60_EOTF_A_OFST)		count = header4.cnt_eotf_a;
		else if (ofst == PE_HDR_DDR1_E60_EOTF_B_OFST)	count = header4.cnt_eotf_b;
		else if (ofst == PE_HDR_DDR1_E60_EOTF_C_OFST)	count = header4.cnt_eotf_c;
		else											count = header4.cnt_eotf_d;
	}
	return count;
}

static UINT32 PE_HDR_HW_E60_GetOetfOffset(UINT32 win_id, UINT32 type)
{
	UINT32 ofst;

	/* A:HLG, B:TEC, C:HDR10, D:default */
	if (type == PE_HDR_HW_E60_LUT_TYPE_A)				ofst = (win_id==0)? PE_HDR_DDR0_E60_OETF_A_OFST:PE_HDR_DDR1_E60_OETF_A_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_B)			ofst = (win_id==0)? PE_HDR_DDR0_E60_OETF_B_OFST:PE_HDR_DDR1_E60_OETF_B_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_C)			ofst = (win_id==0)? PE_HDR_DDR0_E60_OETF_C_OFST:PE_HDR_DDR1_E60_OETF_C_OFST;
	else if (type == PE_HDR_HW_E60_LUT_TYPE_D)			ofst = (win_id==0)? PE_HDR_DDR0_E60_OETF_D_OFST:PE_HDR_DDR1_E60_OETF_D_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_HLG)	ofst = (win_id==0)? PE_HDR_DDR0_E60_OETF_A_OFST:PE_HDR_DDR1_E60_OETF_A_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_TEC)	ofst = (win_id==0)? PE_HDR_DDR0_E60_OETF_B_OFST:PE_HDR_DDR1_E60_OETF_B_OFST;
	else if (type == PE_HDR_HW_E60_CONNECT_MODE_H10)	ofst = (win_id==0)? PE_HDR_DDR0_E60_OETF_C_OFST:PE_HDR_DDR1_E60_OETF_C_OFST;
	else												ofst = (win_id==0)? PE_HDR_DDR0_E60_OETF_D_OFST:PE_HDR_DDR1_E60_OETF_D_OFST;

	return ofst;
}

static UINT32 PE_HDR_HW_E60_IncreaseOetfCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_E60_HEADER1_T header1;
	PE_HDR_DDR_E60_HEADER4_T header4;
	UINT32 *pU32Header1 = (UINT32 *)&header1;
	UINT32 *pU32Header4 = (UINT32 *)&header4;
	rmb();
	if (win_id==0)
	{
		*pU32Header1 = gPE_HDR_DDR_E60[1];
		if (ofst == PE_HDR_DDR0_E60_OETF_A_OFST)
			count = header1.cnt_oetf_a = (header1.cnt_oetf_a == PE_HDR_DDR_E60_OE_CNT_MAX)? 1:(header1.cnt_oetf_a+1);
		else if (ofst == PE_HDR_DDR0_E60_OETF_B_OFST)
			count = header1.cnt_oetf_b = (header1.cnt_oetf_b == PE_HDR_DDR_E60_OE_CNT_MAX)? 1:(header1.cnt_oetf_b+1);
		else if (ofst == PE_HDR_DDR0_E60_OETF_C_OFST)
			count = header1.cnt_oetf_c = (header1.cnt_oetf_c == PE_HDR_DDR_E60_OE_CNT_MAX)? 1:(header1.cnt_oetf_c+1);
		else
			count = header1.cnt_oetf_d = (header1.cnt_oetf_d == PE_HDR_DDR_E60_OE_CNT_MAX)? 1:(header1.cnt_oetf_d+1);
		gPE_HDR_DDR_E60[1] = *pU32Header1;
	}
	else
	{
		*pU32Header4 = gPE_HDR_DDR_E60[4];
		if (ofst == PE_HDR_DDR1_E60_OETF_A_OFST)
			count = header4.cnt_oetf_a = (header4.cnt_oetf_a == PE_HDR_DDR_E60_OE_CNT_MAX)? 1:(header4.cnt_oetf_a+1);
		else if (ofst == PE_HDR_DDR1_E60_OETF_B_OFST)
			count = header4.cnt_oetf_b = (header4.cnt_oetf_b == PE_HDR_DDR_E60_OE_CNT_MAX)? 1:(header4.cnt_oetf_b+1);
		else if (ofst == PE_HDR_DDR1_E60_OETF_C_OFST)
			count = header4.cnt_oetf_c = (header4.cnt_oetf_c == PE_HDR_DDR_E60_OE_CNT_MAX)? 1:(header4.cnt_oetf_c+1);
		else
			count = header4.cnt_oetf_d = (header4.cnt_oetf_d == PE_HDR_DDR_E60_OE_CNT_MAX)? 1:(header4.cnt_oetf_d+1);
		gPE_HDR_DDR_E60[4] = *pU32Header4;
	}
	wmb();
	return count;
}

static UINT32 PE_HDR_HW_E60_GetOetfCount(UINT32 win_id, UINT32 ofst)
{
	UINT32 count;
	PE_HDR_DDR_E60_HEADER1_T header1;
	PE_HDR_DDR_E60_HEADER4_T header4;
	UINT32 *pU32Header1 = (UINT32 *)&header1;
	UINT32 *pU32Header4 = (UINT32 *)&header4;
	rmb();
	if (win_id==0)
	{
		*pU32Header1 = gPE_HDR_DDR_E60[1];
		if (ofst == PE_HDR_DDR0_E60_OETF_A_OFST)		count = header1.cnt_oetf_a;
		else if (ofst == PE_HDR_DDR0_E60_OETF_B_OFST)	count = header1.cnt_oetf_b;
		else if (ofst == PE_HDR_DDR0_E60_OETF_C_OFST)	count = header1.cnt_oetf_c;
		else											count = header1.cnt_oetf_d;
	}
	else
	{
		*pU32Header4 = gPE_HDR_DDR_E60[4];
		if (ofst == PE_HDR_DDR1_E60_OETF_A_OFST)		count = header4.cnt_oetf_a;
		else if (ofst == PE_HDR_DDR1_E60_OETF_B_OFST)	count = header4.cnt_oetf_b;
		else if (ofst == PE_HDR_DDR1_E60_OETF_C_OFST)	count = header4.cnt_oetf_c;
		else											count = header4.cnt_oetf_d;
	}
	return count;
}

static UINT32 PE_HDR_HW_E60_SetSupportInfo(UINT32 win_id, UINT32 info)
{
	PE_HDR_DDR_E60_HEADER0_T header0;
	UINT32 *pU32Header0 = (UINT32 *)&header0;
	static UINT32 pre_info = -1;
	UINT32 cur_info;

	if (win_id!=0)				return RET_OK;

	cur_info = info&0xff;
	if (pre_info == cur_info)	return RET_OK;
	pre_info = cur_info;

	wmb();rmb();
	*pU32Header0 = gPE_HDR_DDR_E60[0];
	header0.support = cur_info;
	gPE_HDR_DDR_E60[0] = *pU32Header0;
	wmb();

	return RET_OK;
}

int PE_HDR_HW_E60_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 bufsize;
	PE_CFG_CTRL_T stParams;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			stParams.resume_mode = pstParams->resume_mode;
			if (stParams.resume_mode > 0)//if normal or snapshot
			{
				if (stParams.resume_mode == 2)//snapshot
				{
					stParams.resume_mode = 0;//force normal
				}
				else//instant
				{
					rmb();
					if (gPE_HDR_DDR_E60[0] == PE_HDR_DDR_E60_VERSION)
					{
						stParams.resume_mode = pstParams->resume_mode;
					}
					else
					{
						stParams.resume_mode = 0;//force normal
					}
					rmb();
				}
			}
			bufsize = sizeof(PE_HDR_HW_E60_DATA_BUF_T)*PE_HDR_HW_E60_BUF_MAX;
			if (_gp_pe_hdr_hw_e60_buf_curr==NULL)
			{
				_gp_pe_hdr_hw_e60_buf_curr = (PE_HDR_HW_E60_DATA_BUF_T *)OS_Malloc(bufsize);
				memset(_gp_pe_hdr_hw_e60_buf_curr, 0, bufsize);
			}
			if (_gp_pe_hdr_hw_e60_buf_sort==NULL)
			{
				_gp_pe_hdr_hw_e60_buf_sort = (PE_HDR_HW_E60_DATA_BUF_T *)OS_Malloc(bufsize);
				memset(_gp_pe_hdr_hw_e60_buf_sort, 0, bufsize);
			}
			if (_gp_pe_hdr_hw_e60_lut_buf_curr==NULL)
			{
				_gp_pe_hdr_hw_e60_lut_buf_curr = (PE_HDR_HW_E60_DATA_BUF_T *)OS_Malloc(bufsize);
				memset(_gp_pe_hdr_hw_e60_lut_buf_curr, 0, bufsize);
			}
			if (_gp_pe_hdr_hw_e60_lut_buf_sort==NULL)
			{
				_gp_pe_hdr_hw_e60_lut_buf_sort = (PE_HDR_HW_E60_DATA_BUF_T *)OS_Malloc(bufsize);
				memset(_gp_pe_hdr_hw_e60_lut_buf_sort, 0, bufsize);
			}
			PE_PRINT_NOTI("[HW_E60Init]start.(ver:%d,resume:%d(%d))(%s)\n",\
				PE_HDR_DDR_E60_VERSION,stParams.resume_mode,pstParams->resume_mode,PE_HDR_HW_E60_DRV_VER);
			PE_HDR_HW_E60_BACKUP_TRACE("[HW_E60Init]start.(ver:%d,resume:%d(%d))(%s)",\
				PE_HDR_DDR_E60_VERSION,stParams.resume_mode,pstParams->resume_mode,PE_HDR_HW_E60_DRV_VER);
			ret = PE_HDR_HW_E60_InitHdrInfo(&stParams);
			PE_HDR_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_E60_InitHdrInfo() error.\n",__F__,__L__);
			/**************************************/
			ret = PE_HDR_HW_E60_InitTonemapLut(&stParams);
			PE_HDR_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_E60_InitTonemapLut() error.\n",__F__,__L__);
			ret = PE_HDR_HW_E60_InitYgainLut(&stParams);
			PE_HDR_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_HDR_HW_E60_InitYgainLut() error.\n",__F__,__L__);
			if (!stParams.resume_mode)	//normal init
			{
				pInfo->reg_hue_prsv_en = 0x1;
				pInfo->reg_sat_prsv_en = 0x1;
				pInfo->reg_hue_prsv_ratio = 0x3ff;
				pInfo->reg_sat_prsv_ratio = 0x0;
				pInfo->lgain_lut[0] = 0x00000000;
				pInfo->lgain_lut[1] = 0x24920040;
				pInfo->lgain_lut[2] = 0x49240080;
				pInfo->lgain_lut[3] = 0x6DB60080;
				pInfo->lgain_lut[4] = 0x92480080;
				pInfo->lgain_lut[5] = 0xB6DA0080;
				pInfo->lgain_lut[6] = 0xDB6C0080;
				pInfo->lgain_lut[7] = 0xFFFF0080;
				pInfo->sgain_lut[0] = 0x00000080;
				pInfo->sgain_lut[1] = 0x24920080;
				pInfo->sgain_lut[2] = 0x49240080;
				pInfo->sgain_lut[3] = 0x6DB60080;
				pInfo->sgain_lut[4] = 0x92480080;
				pInfo->sgain_lut[5] = 0xB6DA0080;
				pInfo->sgain_lut[6] = 0xDB6C0040;
				pInfo->sgain_lut[7] = 0xFFFF0000;
			}
			#if 1	/* E60F20_APB */
			do {
				const UINT16 *p_pcc = _g_pe_hdr_hw_e60_csc_mtrx_bypass;

				if (stParams.resume_mode == 1)	break;//if qsm,skip

				/* addr */
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_hue_sat_ctrl.uaddr32,0xF02058D0);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_00.uaddr32,0xF0205B60);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_01.uaddr32,0xF0205B64);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_02.uaddr32,0xF0205B68);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_03.uaddr32,0xF0205B6C);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_04.uaddr32,0xF0205B70);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_05.uaddr32,0xF0205B74);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_06.uaddr32,0xF0205B78);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_07.uaddr32,0xF0205B7C);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_00.uaddr32,0xF0205B80);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_01.uaddr32,0xF0205B84);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_02.uaddr32,0xF0205B88);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_03.uaddr32,0xF0205B8C);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_04.uaddr32,0xF0205B90);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_05.uaddr32,0xF0205B94);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_06.uaddr32,0xF0205B98);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_07.uaddr32,0xF0205B9C);

				PE_CHPI_APB0_E60F20_QWr(pcc.hdr_pcc_ctrl_01.uaddr32,0xF02058A4);
				PE_CHPI_APB0_E60F20_QWr(pcc.hdr_pcc_ctrl_02.uaddr32,0xF02058A8);
				PE_CHPI_APB0_E60F20_QWr(pcc.hdr_pcc_ctrl_03.uaddr32,0xF02058AC);
				PE_CHPI_APB0_E60F20_QWr(pcc.hdr_pcc_ctrl_04.uaddr32,0xF02058B0);
				PE_CHPI_APB0_E60F20_QWr(pcc.hdr_pcc_ctrl_05.uaddr32,0xF02058B4);

				/* init */
				PE_CHPI_APB0_E60F20_Wr(hs.hdr_hue_sat_ctrl.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(hs.hdr_hue_sat_ctrl.reg_hue_prsv_en,pInfo->reg_hue_prsv_en);
				PE_CHPI_APB0_E60F20_Wr(hs.hdr_hue_sat_ctrl.reg_sat_prsv_en,pInfo->reg_sat_prsv_en);
				PE_CHPI_APB0_E60F20_Wr(hs.hdr_hue_sat_ctrl.reg_hue_prsv_ratio,pInfo->reg_hue_prsv_ratio);
				PE_CHPI_APB0_E60F20_Wr(hs.hdr_hue_sat_ctrl.reg_sat_prsv_ratio,pInfo->reg_sat_prsv_ratio);
				PE_CHPI_APB0_E60F20_WrFL(hs.hdr_hue_sat_ctrl.udata32);

				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_00.udata32,pInfo->lgain_lut[0]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_01.udata32,pInfo->lgain_lut[1]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_02.udata32,pInfo->lgain_lut[2]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_03.udata32,pInfo->lgain_lut[3]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_04.udata32,pInfo->lgain_lut[4]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_05.udata32,pInfo->lgain_lut[5]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_06.udata32,pInfo->lgain_lut[6]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_07.udata32,pInfo->lgain_lut[7]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_00.udata32,pInfo->sgain_lut[0]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_01.udata32,pInfo->sgain_lut[1]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_02.udata32,pInfo->sgain_lut[2]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_03.udata32,pInfo->sgain_lut[3]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_04.udata32,pInfo->sgain_lut[4]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_05.udata32,pInfo->sgain_lut[5]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_06.udata32,pInfo->sgain_lut[6]);
				PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_07.udata32,pInfo->sgain_lut[7]);

				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_01.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_01.r_pcc_coef0,GET_BITS(p_pcc[0],0,16));
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_01.r_pcc_coef1,GET_BITS(p_pcc[1],0,16));
				PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_01.udata32);
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_02.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_02.r_pcc_coef2,GET_BITS(p_pcc[2],0,16));
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_02.r_pcc_coef3,GET_BITS(p_pcc[3],0,16));
				PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_02.udata32);
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_03.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_03.r_pcc_coef4,GET_BITS(p_pcc[4],0,16));
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_03.r_pcc_coef5,GET_BITS(p_pcc[5],0,16));
				PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_03.udata32);
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_04.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_04.r_pcc_coef6,GET_BITS(p_pcc[6],0,16));
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_04.r_pcc_coef7,GET_BITS(p_pcc[7],0,16));
				PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_04.udata32);
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_05.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_05.r_pcc_coef8,GET_BITS(p_pcc[8],0,16));
				PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_05.udata32);

				/* header */
				PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_HS);
				PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_PCC);

				PE_PRINT_NOTI("[APB][HDR]done(resume:%d(%d))\n",stParams.resume_mode,pstParams->resume_mode);
				PE_INF_HW_E60_BACKUP_CHPI0("[APB][HDR]done(resume:%d(%d))",stParams.resume_mode,pstParams->resume_mode);
			} while(0);
			/* inform load db done *//* E60F20_APB */
			do {
				UINT32 load_data[5];
				UINT32 load_size;
				load_data[0] = PE_HDR_DDR_E60_BASE_ADDR;
				load_data[1] = PE_HDR_DDR_E60_TOTAL_SIZE;
				load_data[2] = 2;
				load_data[3] = (1&0xf);//buf num
				load_data[4] = PE_CHPI_APB_E60F20_OFST1;
				load_size = (UINT32)(sizeof(UINT32)*5);
				ret = PE_FWI_E60_LoadDbDone(load_data,load_size);
				PE_HDR_HW_E60_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_E60_LoadDbDone() error.\n",__F__,__L__);
				PE_PRINT_NOTI("[HW_E60Init]LoadDbDone(0x%08x)(%d)(%d)(%d)(0x%08x)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_data[3],load_data[4],load_size);
				PE_HDR_HW_E60_BACKUP_TRACE("[HW_E60Init]LoadDbDone(0x%08x)(%d)(%d)(%d)(0x%08x)(size:%d)",load_data[0],load_data[1],load_data[2],load_data[3],load_data[4],load_size);
			} while(0);
			#endif
			PE_PRINT_NOTI("[HW_E60Init]done.(0x%08x)(%d)\n",PE_HDR_DDR_E60_BASE_ADDR,PE_HDR_DDR_E60_TOTAL_SIZE);
			PE_HDR_HW_E60_BACKUP_TRACE("[HW_E60Init]done.(0x%08x)(%d)",PE_HDR_DDR_E60_BASE_ADDR,PE_HDR_DDR_E60_TOTAL_SIZE);
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

static int PE_HDR_HW_E60_InitHdrInfo(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 base_addr;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			base_addr = PE_HDR_DDR_E60_BASE_ADDR;
			if (!pstParams->resume_mode)	//normal init
			{
				CHECK_KNULL(gPE_HDR_DDR_E60);
				memset(pInfo->md_inf,0,sizeof(LX_PE_HDR_MODE_INFO_T)*LX_PE_WIN_NUM);
				wmb();
				gPE_HDR_DDR_E60[0] = PE_HDR_DDR_E60_VERSION;
				gPE_HDR_DDR_E60[1] = 0x0;
				gPE_HDR_DDR_E60[2] = 0x0;
				gPE_HDR_DDR_E60[3] = 0x0;
				gPE_HDR_DDR_E60[4] = 0x0;
				gPE_HDR_DDR_E60[5] = 0x0;
				gPE_HDR_DDR_E60[6] = 0x0;
				gPE_HDR_DDR_E60[7] = 0x0;
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_A1_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_A2_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_A3_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_B1_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_B2_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_B3_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_C1_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_C2_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_C3_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_D1_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_D2_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				memset((void *)(gPE_HDR_DDR_E60 + (PE_HDR_DDR_E60_INFO_D3_OFST>>2)),0,PE_HDR_DDR_E60_INFO_SIZE);
				wmb();
			}
			#if 0	//not used
			ret = PE_FWI_E60_LoadHdrInfo(&base_addr);
			PE_HDR_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_E60_LoadHdrInfo() error.\n",__F__,__L__);
			#endif
			PE_PRINT_NOTI("done.(resume:%d) b,d:0x%08x,0x%08x, alloc_size:0x%08x\n",\
				pstParams->resume_mode,PE_HDR_DDR_E60_BASE_ADDR,gPE_HDR_DDR_E60[0],PE_HDR_DDR_E60_TOTAL_SIZE);
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

static int PE_HDR_HW_E60_InitTonemapLut(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i=0, size=0, ofst, count[6];
	volatile UINT32 *p_pe_hdr_hw_e60_ddr = NULL;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			if (!pstParams->resume_mode)	//normal init
			{
				/* *************************************************************************/
				/* main ********************************************************************/
				/* *************************************************************************/
				ofst = PE_HDR_DDR0_E60_TONE_A_OFST;
				p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
				CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
				size = sizeof(UINT32)*PE_HDR_HW_E60_TM_LUT_MAX;
				i=0;
				wmb();
				/*A(HLG) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data1_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data1_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data1_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data1_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data2_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data2_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				wmb();
				count[0] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR0_E60_TONE_A_OFST);
				count[1] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR0_E60_TONE_B_OFST);
				count[2] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR0_E60_TONE_C_OFST);
				count[3] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR0_E60_TONE_D_OFST);
				count[4] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR0_E60_TONE_E_OFST);
				count[5] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_0, PE_HDR_DDR0_E60_TONE_F_OFST);
				PE_PRINT_NOTI("[TM0]of:%x,size:%d, cnt:%d,%d,%d,%d,%d,%d\n",\
					ofst,size,count[0],count[1],count[2],count[3],count[4],count[5]);
				PE_HDR_HW_E60_BACKUP_TRACE_LUT("[TM0Init]of:%x,size:%d, cnt:%d,%d,%d,%d,%d,%d",\
					ofst,size,count[0],count[1],count[2],count[3],count[4],count[5]);
				/* *************************************************************************/
				/* sub  ********************************************************************/
				/* *************************************************************************/
				ofst = PE_HDR_DDR1_E60_TONE_A_OFST;
				p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
				CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
				size = sizeof(UINT32)*PE_HDR_HW_E60_TM_LUT_MAX;
				i=0;
				wmb();
				/*A(HLG) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*A(HLG) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data3_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(H10) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data1_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data1_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data1_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data1_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data2_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*C(S2H) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data2_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_x_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*D(TEC) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_y_data5_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*E(SDR) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut0 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut0 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut1 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut1 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut2 x*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*F(DFT) lut2 y*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_tm_lut_bypass_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				wmb();
				count[0] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR1_E60_TONE_A_OFST);
				count[1] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR1_E60_TONE_B_OFST);
				count[2] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR1_E60_TONE_C_OFST);
				count[3] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR1_E60_TONE_D_OFST);
				count[4] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR1_E60_TONE_E_OFST);
				count[5] = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_1, PE_HDR_DDR1_E60_TONE_F_OFST);
				PE_PRINT_NOTI("[TM1]of:%x,size:%d, cnt:%d,%d,%d,%d,%d,%d\n",\
					ofst,size,count[0],count[1],count[2],count[3],count[4],count[5]);
				PE_HDR_HW_E60_BACKUP_TRACE_LUT("[TM1Init]of:%x,size:%d, cnt:%d,%d,%d,%d,%d,%d",\
					ofst,size,count[0],count[1],count[2],count[3],count[4],count[5]);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

static int PE_HDR_HW_E60_InitYgainLut(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, i=0, size=0, count[2];
	volatile UINT32 *p_pe_hdr_hw_e60_ddr = NULL;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			if (!pstParams->resume_mode)	//normal init
			{
				/* *************************************************************************/
				/* main ********************************************************************/
				/* *************************************************************************/
				ofst = PE_HDR_DDR0_E60_YLUT_A_OFST;
				p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
				CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
				size = sizeof(UINT32)*PE_HDR_HW_E60_YG_LUT_MAX;
				i = 0;
				wmb();
				/*A(HLG)*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_yg_lut_data0_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(DFT)*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_yg_lut_bypass_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				wmb();
				count[0] = PE_HDR_HW_E60_IncreaseYlutCount(LX_PE_WIN_0, PE_HDR_DDR0_E60_YLUT_A_OFST);
				count[1] = PE_HDR_HW_E60_IncreaseYlutCount(LX_PE_WIN_0, PE_HDR_DDR0_E60_YLUT_B_OFST);
				PE_PRINT_NOTI("[YG0]of:%x,size:%d, cnt:%d,%d\n",\
					ofst,size,count[0],count[1]);
				/* *************************************************************************/
				/* main ********************************************************************/
				/* *************************************************************************/
				ofst = PE_HDR_DDR1_E60_YLUT_A_OFST;
				p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
				CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
				size = sizeof(UINT32)*PE_HDR_HW_E60_YG_LUT_MAX;
				i = 0;
				wmb();
				/*A(HLG)*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_yg_lut_data0_e60 , size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				/*B(DFT)*/memcpy((void *)(p_pe_hdr_hw_e60_ddr+i), (void *)_g_hdr_yg_lut_bypass_e60, size);i += PE_HDR_HW_E60_TM_LUT_MAX;
				wmb();
				count[0] = PE_HDR_HW_E60_IncreaseYlutCount(LX_PE_WIN_1, PE_HDR_DDR1_E60_YLUT_A_OFST);
				count[1] = PE_HDR_HW_E60_IncreaseYlutCount(LX_PE_WIN_1, PE_HDR_DDR1_E60_YLUT_B_OFST);
				PE_PRINT_NOTI("[YG1]of:%x,size:%d, cnt:%d,%d\n",\
					ofst,size,count[0],count[1]);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
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
int PE_HDR_HW_E60_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_hdr_hw_e60_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(HDR)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if(PE_KDRV_VER_E60)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(HDR)))
				{
					PE_HDR_HW_E60_DBG_PRINT("not support.\n");
				}
				else
				{
					PE_HDR_HW_E60_DBG_PRINT("not support.\n");
				}
			}
			else
			{
				PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
			}
		}
		PE_HDR_HW_E60_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(HDR)),\
			pstParams->print_lvl,_g_hdr_hw_e60_trace,pstParams->bypass);
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_SetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, invalid=0, count=0, size;
	UINT32 lut_type=0;
	UINT32 y_31=31;
	UINT32 y_32=32;
	UINT32 x_31=PE_HDR_HW_E60_TM_LUT_MAX+31;
	UINT32 x_32=PE_HDR_HW_E60_TM_LUT_MAX+32;
	UINT32 connect[2];
	volatile UINT32 *p_pe_hdr_hw_e60_ddr = NULL;
	UINT32 lut_step = PE_HDR_HW_E60_TM_LUT_MAX+PE_HDR_HW_E60_TM_LUT_MAX;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_E60_CHECK_CODE((pstParams->size!=(lut_step*3)), break, \
			"[%s,%d] pstParams->size(%d) is wrong(ref:%d).\n", __F__,__L__, pstParams->size, (lut_step*3));
		PE_HDR_HW_E60_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				//operation, [11:8]version [7:4]ctrl [3:0]hdrpath
				connect[LX_PE_WIN_0] = PE_HDR_HW_E60_GetToneConnectMode(pstParams->oper&0xf);
				do {
					ofst = PE_HDR_HW_E60_GetToneOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("TM0]c[%d]ofst invalid.\n", connect[LX_PE_WIN_0]);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*(lut_step*3);
					wmb();
					memcpy((void *)p_pe_hdr_hw_e60_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_E60_DBG_PRINT("%s)of:%x,size:%d, cnt[%d]:%d\n",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst, size, connect[LX_PE_WIN_0], count);
					PE_HDR_HW_E60_BACKUP_TRACE_LUT("TM0]%s)v%d,o:%X,of:%x,c:%2d,d:%08x,%08x,%08x~%08x,%08x~%08x,%08x,%d:ST %d",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_E60_VERSION,pstParams->oper,\
						ofst,count,pstParams->data[0],pstParams->data[1],\
						pstParams->data[2],pstParams->data[x_31],pstParams->data[x_32],\
						pstParams->data[y_31],pstParams->data[y_32],lut_type,invalid);
				} while(0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				//operation, [11:8]version [7:4]ctrl [3:0]hdrpath
				connect[LX_PE_WIN_1] = PE_HDR_HW_E60_GetToneConnectMode(pstParams->oper&0xf);
				do {
					ofst = PE_HDR_HW_E60_GetToneOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("TM1]c[%d]ofst invalid.\n", connect[LX_PE_WIN_1]);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*(lut_step*3);
					wmb();
					memcpy((void *)p_pe_hdr_hw_e60_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_E60_IncreaseToneCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_E60_DBG_PRINT("%s)of:%x,size:%d, cnt[%d]:%d\n",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst, size, connect[LX_PE_WIN_1], count);
					PE_HDR_HW_E60_BACKUP_TRACE_LUT("TM1]%s)v%d,o:%X,of:%x,c:%2d,d:%08x,%08x,%08x~%08x,%08x~%08x,%08x,%d:ST %d",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_E60_VERSION,pstParams->oper,\
						ofst,count,pstParams->data[0],pstParams->data[1],\
						pstParams->data[2],pstParams->data[x_31],pstParams->data[x_32],\
						pstParams->data[y_31],pstParams->data[y_32],lut_type,invalid);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
int PE_HDR_HW_E60_GetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 i=0, ofst=0;
	UINT32 lut_step = PE_HDR_HW_E60_TM_LUT_MAX+PE_HDR_HW_E60_TM_LUT_MAX;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_E60_CHECK_CODE((pstParams->size!=(lut_step*3)), break, \
			"[%s,%d] pstParams->size(%d) is wrong(ref:%d).\n", __F__,__L__, pstParams->size, (lut_step*3));
		PE_HDR_HW_E60_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				/* llut0 x ***********************************************/
				PE_H10_0_E60_Wr(hdr_llut0_ia_ctrl,0x40005000);//ai,x
				PE_H10_0_E60_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_0_E60_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut0_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_0_E60_RdFL(hdr_llut0_ctrl_05);
				pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut0_ctrl_05);
				/* llut0 y ***********************************************/
				PE_H10_0_E60_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
				PE_H10_0_E60_WrFL(hdr_llut0_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_0_E60_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_H10_0_E60_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_H10_0_E60_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_0_E60_RdFL(hdr_llut0_ctrl_06);
				pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut0_ctrl_06);
				/* llut1 x ***********************************************/
				PE_H10_0_E60_Wr(hdr_llut1_ia_ctrl,0x40005000);//ai,x
				PE_H10_0_E60_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_0_E60_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut1_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_0_E60_RdFL(hdr_llut1_ctrl_05);
				pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut1_ctrl_05);
				/* llut1 y ***********************************************/
				PE_H10_0_E60_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
				PE_H10_0_E60_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_0_E60_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_H10_0_E60_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_H10_0_E60_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_0_E60_RdFL(hdr_llut1_ctrl_06);
				pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut1_ctrl_06);
				/* llut2 x ***********************************************/
				PE_H10_0_E60_Wr(hdr_llut2_ia_ctrl,0x40005000);//ai,x
				PE_H10_0_E60_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_0_E60_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut2_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_0_E60_RdFL(hdr_llut2_ctrl_05);
				pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut2_ctrl_05);
				/* llut2 y ***********************************************/
				PE_H10_0_E60_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
				PE_H10_0_E60_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_0_E60_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_H10_0_E60_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_H10_0_E60_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_0_E60_RdFL(hdr_llut2_ctrl_06);
				pstParams->data[i+ofst] = PE_H10_0_E60_Rd(hdr_llut2_ctrl_06);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				/* llut0 x ***********************************************/
				PE_H10_1_E60_Wr(hdr_llut0_ia_ctrl,0x40005000);//ai,x
				PE_H10_1_E60_WrFL(hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_1_E60_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut0_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_1_E60_RdFL(hdr_llut0_ctrl_05);
				pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut0_ctrl_05);
				/* llut0 y ***********************************************/
				PE_H10_1_E60_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
				PE_H10_1_E60_WrFL(hdr_llut0_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_1_E60_RdFL(hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut0_ia_data);
				}
				/* set normal */
				PE_H10_1_E60_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_H10_1_E60_WrFL(hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_1_E60_RdFL(hdr_llut0_ctrl_06);
				pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut0_ctrl_06);
				/* llut1 x ***********************************************/
				PE_H10_1_E60_Wr(hdr_llut1_ia_ctrl,0x40005000);//ai,x
				PE_H10_1_E60_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_1_E60_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut1_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_1_E60_RdFL(hdr_llut1_ctrl_05);
				pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut1_ctrl_05);
				/* llut1 y ***********************************************/
				PE_H10_1_E60_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
				PE_H10_1_E60_WrFL(hdr_llut1_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_1_E60_RdFL(hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut1_ia_data);
				}
				/* set normal */
				PE_H10_1_E60_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_H10_1_E60_WrFL(hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_1_E60_RdFL(hdr_llut1_ctrl_06);
				pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut1_ctrl_06);
				/* llut2 x ***********************************************/
				PE_H10_1_E60_Wr(hdr_llut2_ia_ctrl,0x40005000);//ai,x
				PE_H10_1_E60_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_1_E60_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut2_ia_data);
				}
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_1_E60_RdFL(hdr_llut2_ctrl_05);
				pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut2_ctrl_05);
				/* llut2 y ***********************************************/
				PE_H10_1_E60_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
				PE_H10_1_E60_WrFL(hdr_llut2_ia_ctrl);
				ofst += PE_HDR_HW_E60_TM_LUT_MAX;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_H10_1_E60_RdFL(hdr_llut2_ia_data);
					pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut2_ia_data);
				}
				/* set normal */
				PE_H10_1_E60_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
				PE_H10_1_E60_WrFL(hdr_llut2_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_H10_1_E60_RdFL(hdr_llut2_ctrl_06);
				pstParams->data[i+ofst] = PE_H10_1_E60_Rd(hdr_llut2_ctrl_06);
			}
			if(PE_CHECK_WIN2(win_id))
			{
				lut_step = PE_HDR_HW_E60_TM_LUT_MAX;
				/* llut0 ***********************************************/
				PE_S2H_0_E60_Wr(sdr2hdr_llut0_ia_ctrl,0x40001000);//ai
				PE_S2H_0_E60_WrFL(sdr2hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_S2H_0_E60_RdFL(sdr2hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_S2H_0_E60_Rd(sdr2hdr_llut0_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_S2H_0_E60_Rd(sdr2hdr_llut0_ia_data)&0xffff;
				}
				/* set normal */
				PE_S2H_0_E60_Wr(sdr2hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_S2H_0_E60_WrFL(sdr2hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_S2H_0_E60_RdFL(sdr2hdr_llut0_ctrl_05);
				pstParams->data[i+ofst] = PE_S2H_0_E60_Rd(sdr2hdr_llut0_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_S2H_0_E60_Rd(sdr2hdr_llut0_ctrl_05)&0xffff;
				/* llut1 ***********************************************/
				PE_S2H_0_E60_Wr(sdr2hdr_llut1_ia_ctrl,0x40001000);//ai
				PE_S2H_0_E60_WrFL(sdr2hdr_llut1_ia_ctrl);
				ofst += (PE_HDR_HW_E60_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_S2H_0_E60_RdFL(sdr2hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_S2H_0_E60_Rd(sdr2hdr_llut1_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_S2H_0_E60_Rd(sdr2hdr_llut1_ia_data)&0xffff;
				}
				/* set normal */
				PE_S2H_0_E60_Wr(sdr2hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_S2H_0_E60_WrFL(sdr2hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_S2H_0_E60_RdFL(sdr2hdr_llut1_ctrl_05);
				pstParams->data[i+ofst] = PE_S2H_0_E60_Rd(sdr2hdr_llut1_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_S2H_0_E60_Rd(sdr2hdr_llut1_ctrl_05)&0xffff;
				/* llut2 ***********************************************/
				PE_S2H_0_E60_Wr(sdr2hdr_fbslut_ia_ctrl,0x40001000);//ai
				PE_S2H_0_E60_WrFL(sdr2hdr_fbslut_ia_ctrl);
				ofst += (PE_HDR_HW_E60_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_S2H_0_E60_RdFL(hdr_fbs_lut_ia_data);
					pstParams->data[i+ofst] = PE_S2H_0_E60_Rd(hdr_fbs_lut_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_S2H_0_E60_Rd(hdr_fbs_lut_ia_data)&0xffff;
				}
				/* set normal */
				PE_S2H_0_E60_Wr(sdr2hdr_fbslut_ia_ctrl,0x00008100);//normal
				PE_S2H_0_E60_WrFL(sdr2hdr_fbslut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_S2H_0_E60_RdFL(sdr2hdr_fbslut_ctrl_05);
				pstParams->data[i+ofst] = PE_S2H_0_E60_Rd(sdr2hdr_fbslut_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_S2H_0_E60_Rd(sdr2hdr_fbslut_ctrl_05)&0xffff;
			}
			if(PE_CHECK_WIN3(win_id))
			{
				lut_step = PE_HDR_HW_E60_TM_LUT_MAX;
				/* llut0 ***********************************************/
				PE_S2H_1_E60_Wr(sdr2hdr_llut0_ia_ctrl,0x40001000);//ai
				PE_S2H_1_E60_WrFL(sdr2hdr_llut0_ia_ctrl);
				ofst = 0;
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_S2H_1_E60_RdFL(sdr2hdr_llut0_ia_data);
					pstParams->data[i+ofst] = PE_S2H_1_E60_Rd(sdr2hdr_llut0_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_S2H_1_E60_Rd(sdr2hdr_llut0_ia_data)&0xffff;
				}
				/* set normal */
				PE_S2H_1_E60_Wr(sdr2hdr_llut0_ia_ctrl,0x00008100);//normal
				PE_S2H_1_E60_WrFL(sdr2hdr_llut0_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_S2H_1_E60_RdFL(sdr2hdr_llut0_ctrl_05);
				pstParams->data[i+ofst] = PE_S2H_1_E60_Rd(sdr2hdr_llut0_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_S2H_1_E60_Rd(sdr2hdr_llut0_ctrl_05)&0xffff;
				/* llut1 ***********************************************/
				PE_S2H_1_E60_Wr(sdr2hdr_llut1_ia_ctrl,0x40001000);//ai
				PE_S2H_1_E60_WrFL(sdr2hdr_llut1_ia_ctrl);
				ofst += (PE_HDR_HW_E60_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_S2H_1_E60_RdFL(sdr2hdr_llut1_ia_data);
					pstParams->data[i+ofst] = PE_S2H_1_E60_Rd(sdr2hdr_llut1_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_S2H_1_E60_Rd(sdr2hdr_llut1_ia_data)&0xffff;
				}
				/* set normal */
				PE_S2H_1_E60_Wr(sdr2hdr_llut1_ia_ctrl,0x00008100);//normal
				PE_S2H_1_E60_WrFL(sdr2hdr_llut1_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_S2H_1_E60_RdFL(sdr2hdr_llut1_ctrl_05);
				pstParams->data[i+ofst] = PE_S2H_1_E60_Rd(sdr2hdr_llut1_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_S2H_1_E60_Rd(sdr2hdr_llut1_ctrl_05)&0xffff;
				/* llut2 ***********************************************/
				PE_S2H_1_E60_Wr(sdr2hdr_fbslut_ia_ctrl,0x40001000);//ai
				PE_S2H_1_E60_WrFL(sdr2hdr_fbslut_ia_ctrl);
				ofst += (PE_HDR_HW_E60_TM_LUT_MAX<<1);
				for(i=0;i<(PE_HDR_HW_E60_TM_LUT_MAX-1);i++)
				{
					PE_S2H_1_E60_RdFL(hdr_fbs_lut_ia_data);
					pstParams->data[i+ofst] = PE_S2H_1_E60_Rd(hdr_fbs_lut_ia_data)>>16;
					pstParams->data[i+ofst+lut_step] = PE_S2H_1_E60_Rd(hdr_fbs_lut_ia_data)&0xffff;
				}
				/* set normal */
				PE_S2H_1_E60_Wr(sdr2hdr_fbslut_ia_ctrl,0x00008100);//normal
				PE_S2H_1_E60_WrFL(sdr2hdr_fbslut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_TM_LUT_MAX-1;
				PE_S2H_1_E60_RdFL(sdr2hdr_fbslut_ctrl_05);
				pstParams->data[i+ofst] = PE_S2H_1_E60_Rd(sdr2hdr_fbslut_ctrl_05)>>16;
				pstParams->data[i+ofst+lut_step] = PE_S2H_1_E60_Rd(sdr2hdr_fbslut_ctrl_05)&0xffff;
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_SetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, i, size;
	UINT32 connect[2];
	UINT32 lut_step = PE_HDR_HW_E60_YG_LUT_MAX;
	volatile UINT32 *p_pe_hdr_hw_e60_ddr = NULL;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_E60_CHECK_CODE(pstParams->size!=lut_step, break, \
			"[%s,%d] pstParams->size(%d) is wrong.\n", __F__,__L__, pstParams->size);
		PE_HDR_HW_E60_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_0);
				do {
					ofst = PE_HDR_HW_E60_GetYlutOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[YG0]c[%d]ofst invalid.\n", connect[LX_PE_WIN_0]);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_e60_ddr, (void *)pstParams->data, size);
					wmb();
					i = PE_HDR_HW_E60_IncreaseYlutCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[%s]of:%x,size:%d c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]), \
						ofst, size, connect[LX_PE_WIN_0], i);
					PE_HDR_HW_E60_BACKUP_TRACE("[YG0]%s]v%d,os:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_E60_VERSION,\
						pstParams->oper, pstParams->size,  \
						ofst, connect[LX_PE_WIN_0], i, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_1);
				do {
					ofst = PE_HDR_HW_E60_GetYlutOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[YG1]c[%d]ofst invalid.\n", connect[LX_PE_WIN_1]);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_e60_ddr, (void *)pstParams->data, size);
					wmb();
					i = PE_HDR_HW_E60_IncreaseYlutCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[%s]of:%x,size:%d c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]), \
						ofst, size, connect[LX_PE_WIN_1], i);
					PE_HDR_HW_E60_BACKUP_TRACE("[YG1]%s]v%d,os:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_E60_VERSION,\
						pstParams->oper, pstParams->size,  \
						ofst, connect[LX_PE_WIN_1], i, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_GetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 i=0;
	UINT32 lut_step = PE_HDR_HW_E60_YG_LUT_MAX;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_E60_CHECK_CODE(pstParams->size!=lut_step, break, \
			"[%s,%d] pstParams->size(%d) is wrong.\n", __F__,__L__, pstParams->size);
		PE_HDR_HW_E60_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_H10_0_E60_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_H10_0_E60_WrFL(hdr_ygain_lut_ia_ctrl);
				for(i=0;i<(PE_HDR_HW_E60_YG_LUT_MAX-1);i++)
				{
					PE_H10_0_E60_RdFL(hdr_ygain_lut_ia_data);
					pstParams->data[i] = PE_H10_0_E60_Rd(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_H10_0_E60_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_H10_0_E60_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_YG_LUT_MAX-1;
				PE_H10_0_E60_RdFL(hdr_ygain_lut_ctrl_05);
				pstParams->data[i] = PE_H10_0_E60_Rd(hdr_ygain_lut_ctrl_05);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_H10_1_E60_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
				PE_H10_1_E60_WrFL(hdr_ygain_lut_ia_ctrl);
				for(i=0;i<(PE_HDR_HW_E60_YG_LUT_MAX-1);i++)
				{
					PE_H10_1_E60_RdFL(hdr_ygain_lut_ia_data);
					pstParams->data[i] = PE_H10_1_E60_Rd(hdr_ygain_lut_ia_data);
				}
				/* set normal */
				PE_H10_1_E60_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
				PE_H10_1_E60_WrFL(hdr_ygain_lut_ia_ctrl);
				/* last point */
				i = PE_HDR_HW_E60_YG_LUT_MAX-1;
				PE_H10_1_E60_RdFL(hdr_ygain_lut_ctrl_05);
				pstParams->data[i] = PE_H10_1_E60_Rd(hdr_ygain_lut_ctrl_05);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_SetCsc(LX_PE_HDR_CSC_T *pstParams)
{
	int ret = RET_OK;
	const UINT16 *p_co1;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_E60_DBG_PRINT("set pstParams[%d]\n"\
			"tp1:%d, coef:%04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x\n",\
			pstParams->win_id,pstParams->type1,\
			pstParams->coef1[0],pstParams->coef1[1],pstParams->coef1[2],\
			pstParams->coef1[3],pstParams->coef1[4],pstParams->coef1[5],\
			pstParams->coef1[6],pstParams->coef1[7],pstParams->coef1[8]);
		if(PE_KDRV_VER_E60)
		{
			switch (pstParams->type1)
			{
				case LX_PE_HDR_CSC_MANUAL:
					p_co1 = pstParams->coef1;
					break;
				case LX_PE_HDR_CSC_BYPASS:
					p_co1 = _g_pe_hdr_hw_e60_csc_mtrx_bypass;
					break;
				case LX_PE_HDR_CSC_DEFAULT:
				case LX_PE_HDR_CSC_DEFAULT1:
				default:
					p_co1 = _g_pe_hdr_hw_e60_pcc_mtrx_default;
					break;
			}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_H10_0_E60_QWr02(hdr_pcc_ctrl_01,r_pcc_coef0,GET_BITS(p_co1[0],0,16),r_pcc_coef1,GET_BITS(p_co1[1],0,16));
				PE_H10_0_E60_QWr02(hdr_pcc_ctrl_02,r_pcc_coef2,GET_BITS(p_co1[2],0,16),r_pcc_coef3,GET_BITS(p_co1[3],0,16));
				PE_H10_0_E60_QWr02(hdr_pcc_ctrl_03,r_pcc_coef4,GET_BITS(p_co1[4],0,16),r_pcc_coef5,GET_BITS(p_co1[5],0,16));
				PE_H10_0_E60_QWr02(hdr_pcc_ctrl_04,r_pcc_coef6,GET_BITS(p_co1[6],0,16),r_pcc_coef7,GET_BITS(p_co1[7],0,16));
				PE_H10_0_E60_QWr01(hdr_pcc_ctrl_05,r_pcc_coef8,GET_BITS(p_co1[8],0,16));

				PE_H10_1_E60_QWr02(hdr_pcc_ctrl_01,r_pcc_coef0,GET_BITS(p_co1[0],0,16),r_pcc_coef1,GET_BITS(p_co1[1],0,16));
				PE_H10_1_E60_QWr02(hdr_pcc_ctrl_02,r_pcc_coef2,GET_BITS(p_co1[2],0,16),r_pcc_coef3,GET_BITS(p_co1[3],0,16));
				PE_H10_1_E60_QWr02(hdr_pcc_ctrl_03,r_pcc_coef4,GET_BITS(p_co1[4],0,16),r_pcc_coef5,GET_BITS(p_co1[5],0,16));
				PE_H10_1_E60_QWr02(hdr_pcc_ctrl_04,r_pcc_coef6,GET_BITS(p_co1[6],0,16),r_pcc_coef7,GET_BITS(p_co1[7],0,16));
				PE_H10_1_E60_QWr01(hdr_pcc_ctrl_05,r_pcc_coef8,GET_BITS(p_co1[8],0,16));
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_01.r_pcc_coef0,GET_BITS(p_co1[0],0,16));
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_01.r_pcc_coef1,GET_BITS(p_co1[1],0,16));
					PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_01.udata32);
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_02.r_pcc_coef2,GET_BITS(p_co1[2],0,16));
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_02.r_pcc_coef3,GET_BITS(p_co1[3],0,16));
					PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_02.udata32);
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_03.r_pcc_coef4,GET_BITS(p_co1[4],0,16));
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_03.r_pcc_coef5,GET_BITS(p_co1[5],0,16));
					PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_03.udata32);
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_04.r_pcc_coef6,GET_BITS(p_co1[6],0,16));
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_04.r_pcc_coef7,GET_BITS(p_co1[7],0,16));
					PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_04.udata32);
					PE_CHPI_APB0_E60F20_Wr(pcc.hdr_pcc_ctrl_05.r_pcc_coef8,GET_BITS(p_co1[8],0,16));
					PE_CHPI_APB0_E60F20_WrFL(pcc.hdr_pcc_ctrl_05.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_PCC);
				} while(0);
				#endif
				memcpy(&(pInfo->pre_csc[LX_PE_WIN_0]), pstParams, sizeof(LX_PE_HDR_CSC_T));
				PE_HDR_HW_E60_BACKUP_TRACE("[PCC0]t1:%d, %04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x",\
					pstParams->type1,pstParams->coef1[0],pstParams->coef1[1],pstParams->coef1[2],\
					pstParams->coef1[3],pstParams->coef1[4],pstParams->coef1[5],\
					pstParams->coef1[6],pstParams->coef1[7],pstParams->coef1[8]);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_GetCsc(LX_PE_HDR_CSC_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT16 *p_co0,*p_of0,*p_co1,*p_of1,*p_co2,*p_of2;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
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
				PE_H10_0_E60_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
				PE_H10_0_E60_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
				PE_H10_0_E60_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
				PE_H10_0_E60_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
				PE_H10_0_E60_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
				PE_H10_0_E60_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
				PE_H10_0_E60_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
				PE_H10_0_E60_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
				/* pcc */
				PE_H10_0_E60_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
				PE_H10_0_E60_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
				PE_H10_0_E60_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
				PE_H10_0_E60_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
				PE_H10_0_E60_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
				p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
				/* csc4 */
				PE_H10_0_E60_QRd02(hdr_csc4_ctrl_01,r_csc4th_coef0,p_co2[0],r_csc4th_coef1,p_co2[1]);
				PE_H10_0_E60_QRd02(hdr_csc4_ctrl_02,r_csc4th_coef2,p_co2[2],r_csc4th_coef3,p_co2[3]);
				PE_H10_0_E60_QRd02(hdr_csc4_ctrl_03,r_csc4th_coef4,p_co2[4],r_csc4th_coef5,p_co2[5]);
				PE_H10_0_E60_QRd02(hdr_csc4_ctrl_04,r_csc4th_coef6,p_co2[6],r_csc4th_coef7,p_co2[7]);
				PE_H10_0_E60_QRd01(hdr_csc4_ctrl_05,r_csc4th_coef8,p_co2[8]);
				PE_H10_0_E60_QRd02(hdr_csc4_ctrl_06,r_csc4th_ofst0,p_of2[0],r_csc4th_ofst1,p_of2[1]);
				PE_H10_0_E60_QRd02(hdr_csc4_ctrl_07,r_csc4th_ofst2,p_of2[2],r_csc4th_ofst3,p_of2[3]);
				PE_H10_0_E60_QRd02(hdr_csc4_ctrl_08,r_csc4th_ofst4,p_of2[4],r_csc4th_ofst5,p_of2[5]);
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
				PE_H10_1_E60_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
				PE_H10_1_E60_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
				PE_H10_1_E60_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
				PE_H10_1_E60_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
				PE_H10_1_E60_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
				PE_H10_1_E60_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
				PE_H10_1_E60_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
				PE_H10_1_E60_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
				/* pcc */
				PE_H10_1_E60_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
				PE_H10_1_E60_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
				PE_H10_1_E60_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
				PE_H10_1_E60_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
				PE_H10_1_E60_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
				p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
				/* csc4 */
				PE_H10_1_E60_QRd02(hdr_csc4_ctrl_01,r_csc4th_coef0,p_co2[0],r_csc4th_coef1,p_co2[1]);
				PE_H10_1_E60_QRd02(hdr_csc4_ctrl_02,r_csc4th_coef2,p_co2[2],r_csc4th_coef3,p_co2[3]);
				PE_H10_1_E60_QRd02(hdr_csc4_ctrl_03,r_csc4th_coef4,p_co2[4],r_csc4th_coef5,p_co2[5]);
				PE_H10_1_E60_QRd02(hdr_csc4_ctrl_04,r_csc4th_coef6,p_co2[6],r_csc4th_coef7,p_co2[7]);
				PE_H10_1_E60_QRd01(hdr_csc4_ctrl_05,r_csc4th_coef8,p_co2[8]);
				PE_H10_1_E60_QRd02(hdr_csc4_ctrl_06,r_csc4th_ofst0,p_of2[0],r_csc4th_ofst1,p_of2[1]);
				PE_H10_1_E60_QRd02(hdr_csc4_ctrl_07,r_csc4th_ofst2,p_of2[2],r_csc4th_ofst3,p_of2[3]);
				PE_H10_1_E60_QRd02(hdr_csc4_ctrl_08,r_csc4th_ofst4,p_of2[4],r_csc4th_ofst5,p_of2[5]);
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
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_HDR_HW_E60_DBG_PRINT("get pstParams[%d]\n"\
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

int PE_HDR_HW_E60_SetHdrTask(PE_TSK_E60_CFG_T *pCfg)
{
	return RET_OK;
}

int PE_HDR_HW_E60_GetGeneralInfo(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0;
	UINT32 *p_co0 = _g_pe_hdr_hw_e60_info.hdr_co0;
	UINT32 *p_of0 = _g_pe_hdr_hw_e60_info.hdr_of0;
	UINT32 *p_co1 = _g_pe_hdr_hw_e60_info.hdr_co1;
	UINT32 *p_of1 = _g_pe_hdr_hw_e60_info.hdr_of1;
	UINT32 *p_co2 = _g_pe_hdr_hw_e60_info.hdr_co2;
	UINT32 *p_of2 = _g_pe_hdr_hw_e60_info.hdr_of2;
	UINT32 *p_co3 = _g_pe_hdr_hw_e60_info.hdr_co3;
	UINT32 *p_of3 = _g_pe_hdr_hw_e60_info.hdr_of3;
	UINT32 *p_co4 = _g_pe_hdr_hw_e60_info.hdr_co4;
	UINT32 *p_of4 = _g_pe_hdr_hw_e60_info.hdr_of4;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;

#define PE_HDR_E60_PRINT_START		"START_OF_PRINT"
#define PE_HDR_E60_PRINT_RESERVED	"RESERVED"
#define PE_HDR_E60_PRINT_END		"END_OF_PRINT"
#define PE_HDR_E60_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_HDR_E60_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE,"   [0x%02x] %s\n",(_item),#_item);_action;break
#define PE_HDR_E60_CASE_SPRINT(_cnt,_action,_buf,fmt,args...)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break
#define PE_HDR_E60_DFLT_SPRINT(_action,_buf,fmt,args...)		\
	default:snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		if(PE_KDRV_VER_E60)
		{
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]==PE_HDR_HW_E60_INFO_MENU_DISPLAY)
			{
				switch (rd_cnt)
				{
					PE_HDR_E60_CASE_SPRINT( 0, rd_cnt++, buffer, PE_HDR_E60_PRINT_START);
					PE_HDR_E60_CASE_PRMENU( 1, rd_cnt++, buffer, PE_HDR_HW_E60_INFO_MENU_RD_INF0);
					PE_HDR_E60_CASE_PRMENU( 2, rd_cnt++, buffer, PE_HDR_HW_E60_INFO_MENU_RD_INF1);
					PE_HDR_E60_CASE_PRMENU( 3, rd_cnt++, buffer, PE_HDR_HW_E60_INFO_MENU_RD_INF2);
					PE_HDR_E60_CASE_PRMENU( 4, rd_cnt++, buffer, PE_HDR_HW_E60_INFO_MENU_RD_INF3);
					PE_HDR_E60_CASE_PRMENU( 5, rd_cnt++, buffer, PE_HDR_HW_E60_INFO_MENU_RD_INF4);
					PE_HDR_E60_CASE_SPRINT( 6, rd_cnt++, buffer, PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_DFLT_SPRINT(rd_cnt=0, buffer, PE_HDR_E60_PRINT_END);
				}
			}
			else if (pstParams->data[0]==PE_HDR_HW_E60_INFO_MENU_RD_INF0)
			{
				if (rd_cnt==0)
				{
					/* csc1 */
					PE_H10_0_E60_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
					PE_H10_0_E60_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
					PE_H10_0_E60_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
					PE_H10_0_E60_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
					PE_H10_0_E60_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
					PE_H10_0_E60_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
					PE_H10_0_E60_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
					PE_H10_0_E60_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
					/* pcc */
					PE_H10_0_E60_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
					PE_H10_0_E60_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
					PE_H10_0_E60_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
					PE_H10_0_E60_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
					PE_H10_0_E60_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
					p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
					/* csc3 */
					PE_H10_0_E60_QRd02(hdr_csc3_ctrl_01,r_csc3rd_coef0,p_co2[0],r_csc3rd_coef1,p_co2[1]);
					PE_H10_0_E60_QRd02(hdr_csc3_ctrl_02,r_csc3rd_coef2,p_co2[2],r_csc3rd_coef3,p_co2[3]);
					PE_H10_0_E60_QRd02(hdr_csc3_ctrl_03,r_csc3rd_coef4,p_co2[4],r_csc3rd_coef5,p_co2[5]);
					PE_H10_0_E60_QRd02(hdr_csc3_ctrl_04,r_csc3rd_coef6,p_co2[6],r_csc3rd_coef7,p_co2[7]);
					PE_H10_0_E60_QRd01(hdr_csc3_ctrl_05,r_csc3rd_coef8,p_co2[8]);
					PE_H10_0_E60_QRd02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,p_of2[0],r_csc3rd_ofst1,p_of2[1]);
					PE_H10_0_E60_QRd02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,p_of2[2],r_csc3rd_ofst3,p_of2[3]);
					PE_H10_0_E60_QRd02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,p_of2[4],r_csc3rd_ofst5,p_of2[5]);
					/* csc4 */
					PE_H10_0_E60_QRd02(hdr_csc4_ctrl_01,r_csc4th_coef0,p_co3[0],r_csc4th_coef1,p_co3[1]);
					PE_H10_0_E60_QRd02(hdr_csc4_ctrl_02,r_csc4th_coef2,p_co3[2],r_csc4th_coef3,p_co3[3]);
					PE_H10_0_E60_QRd02(hdr_csc4_ctrl_03,r_csc4th_coef4,p_co3[4],r_csc4th_coef5,p_co3[5]);
					PE_H10_0_E60_QRd02(hdr_csc4_ctrl_04,r_csc4th_coef6,p_co3[6],r_csc4th_coef7,p_co3[7]);
					PE_H10_0_E60_QRd01(hdr_csc4_ctrl_05,r_csc4th_coef8,p_co3[8]);
					PE_H10_0_E60_QRd02(hdr_csc4_ctrl_06,r_csc4th_ofst0,p_of3[0],r_csc4th_ofst1,p_of3[1]);
					PE_H10_0_E60_QRd02(hdr_csc4_ctrl_07,r_csc4th_ofst2,p_of3[2],r_csc4th_ofst3,p_of3[3]);
					PE_H10_0_E60_QRd02(hdr_csc4_ctrl_08,r_csc4th_ofst4,p_of3[4],r_csc4th_ofst5,p_of3[5]);
					/* csc1(s2h) */
					PE_S2H_0_E60_QRd02(hdr_sdr2hdr_ctrl_02,r_csc1st_coef0,p_co4[0],r_csc1st_coef1,p_co4[1]);
					PE_S2H_0_E60_QRd02(hdr_sdr2hdr_ctrl_03,r_csc1st_coef2,p_co4[2],r_csc1st_coef3,p_co4[3]);
					PE_S2H_0_E60_QRd02(hdr_sdr2hdr_ctrl_04,r_csc1st_coef4,p_co4[4],r_csc1st_coef5,p_co4[5]);
					PE_S2H_0_E60_QRd02(hdr_sdr2hdr_ctrl_05,r_csc1st_coef6,p_co4[6],r_csc1st_coef7,p_co4[7]);
					PE_S2H_0_E60_QRd01(hdr_sdr2hdr_ctrl_06,r_csc1st_coef8,p_co4[8]);
					PE_S2H_0_E60_QRd02(hdr_sdr2hdr_ctrl_07,r_csc1st_ofst0,p_of4[0],r_csc1st_ofst1,p_of4[1]);
					PE_S2H_0_E60_QRd02(hdr_sdr2hdr_ctrl_08,r_csc1st_ofst2,p_of4[2],r_csc1st_ofst3,p_of4[3]);
					PE_S2H_0_E60_QRd02(hdr_sdr2hdr_ctrl_09,r_csc1st_ofst4,p_of4[4],r_csc1st_ofst5,p_of4[5]);
				}
				switch(rd_cnt)
				{
					PE_HDR_E60_CASE_SPRINT( 0,rd_cnt++,buffer,PE_HDR_E60_PRINT_START);
					PE_HDR_E60_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"(0)hdr csc1 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_0].type0,pInfo->cur_hdr_type[LX_PE_WIN_0],pInfo->pre_hdr_type[LX_PE_WIN_0]);
					PE_HDR_E60_CASE_SPRINT( 3,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT( 4,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[0], p_co0[1], p_co0[2], p_of0[0], p_of0[3]);
					PE_HDR_E60_CASE_SPRINT( 5,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[3], p_co0[4], p_co0[5], p_of0[1], p_of0[4]);
					PE_HDR_E60_CASE_SPRINT( 6,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[6], p_co0[7], p_co0[8], p_of0[2], p_of0[5]);
					PE_HDR_E60_CASE_SPRINT( 7,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT( 8,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT( 9,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(10,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(11,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(12,rd_cnt++,buffer,\
						"(0)hdr pcc type:%d\n",pInfo->pre_csc[LX_PE_WIN_0].type1);
					PE_HDR_E60_CASE_SPRINT(13,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(14,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[0], p_co1[1], p_co1[2], p_of1[0], p_of1[3]);
					PE_HDR_E60_CASE_SPRINT(15,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[3], p_co1[4], p_co1[5], p_of1[1], p_of1[4]);
					PE_HDR_E60_CASE_SPRINT(16,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[6], p_co1[7], p_co1[8], p_of1[2], p_of1[5]);
					PE_HDR_E60_CASE_SPRINT(17,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(18,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(19,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(20,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(21,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(22,rd_cnt++,buffer,\
						"(0)hdr csc3 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_0].type2,pInfo->cur_hdr_type[LX_PE_WIN_0],pInfo->pre_hdr_type[LX_PE_WIN_0]);
					PE_HDR_E60_CASE_SPRINT(23,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(24,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[0], p_co2[1], p_co2[2], p_of2[0], p_of2[3]);
					PE_HDR_E60_CASE_SPRINT(25,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[3], p_co2[4], p_co2[5], p_of2[1], p_of2[4]);
					PE_HDR_E60_CASE_SPRINT(26,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[6], p_co2[7], p_co2[8], p_of2[2], p_of2[5]);
					PE_HDR_E60_CASE_SPRINT(27,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(28,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(29,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(30,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(31,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(32,rd_cnt++,buffer,\
						"(0)hdr csc4 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_0].type0,pInfo->cur_hdr_type[LX_PE_WIN_0],pInfo->pre_hdr_type[LX_PE_WIN_0]);
					PE_HDR_E60_CASE_SPRINT(33,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(34,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[0], p_co3[1], p_co3[2], p_of3[0], p_of3[3]);
					PE_HDR_E60_CASE_SPRINT(35,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[3], p_co3[4], p_co3[5], p_of3[1], p_of3[4]);
					PE_HDR_E60_CASE_SPRINT(36,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[6], p_co3[7], p_co3[8], p_of3[2], p_of3[5]);
					PE_HDR_E60_CASE_SPRINT(37,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(38,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(39,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(40,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(41,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(42,rd_cnt++,buffer,\
						"(0)hdr csc1(s2h) type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_0].type0,pInfo->cur_hdr_type[LX_PE_WIN_0],pInfo->pre_hdr_type[LX_PE_WIN_0]);
					PE_HDR_E60_CASE_SPRINT(43,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(44,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co4[0], p_co4[1], p_co4[2], p_of4[0], p_of4[3]);
					PE_HDR_E60_CASE_SPRINT(45,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co4[3], p_co4[4], p_co4[5], p_of4[1], p_of4[4]);
					PE_HDR_E60_CASE_SPRINT(46,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co4[6], p_co4[7], p_co4[8], p_of4[2], p_of4[5]);
					PE_HDR_E60_CASE_SPRINT(47,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(48,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(49,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(50,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_DFLT_SPRINT(rd_cnt=0,buffer,PE_HDR_E60_PRINT_END);
				}
			}
			else if (pstParams->data[0]==PE_HDR_HW_E60_INFO_MENU_RD_INF1)
			{
				if (rd_cnt==0)
				{
					/* csc1 */
					PE_H10_1_E60_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
					PE_H10_1_E60_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
					PE_H10_1_E60_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
					PE_H10_1_E60_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
					PE_H10_1_E60_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
					PE_H10_1_E60_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
					PE_H10_1_E60_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
					PE_H10_1_E60_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
					/* pcc */
					PE_H10_1_E60_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
					PE_H10_1_E60_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
					PE_H10_1_E60_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
					PE_H10_1_E60_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
					PE_H10_1_E60_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
					p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
					/* csc3 */
					PE_H10_1_E60_QRd02(hdr_csc3_ctrl_01,r_csc3rd_coef0,p_co2[0],r_csc3rd_coef1,p_co2[1]);
					PE_H10_1_E60_QRd02(hdr_csc3_ctrl_02,r_csc3rd_coef2,p_co2[2],r_csc3rd_coef3,p_co2[3]);
					PE_H10_1_E60_QRd02(hdr_csc3_ctrl_03,r_csc3rd_coef4,p_co2[4],r_csc3rd_coef5,p_co2[5]);
					PE_H10_1_E60_QRd02(hdr_csc3_ctrl_04,r_csc3rd_coef6,p_co2[6],r_csc3rd_coef7,p_co2[7]);
					PE_H10_1_E60_QRd01(hdr_csc3_ctrl_05,r_csc3rd_coef8,p_co2[8]);
					PE_H10_1_E60_QRd02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,p_of2[0],r_csc3rd_ofst1,p_of2[1]);
					PE_H10_1_E60_QRd02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,p_of2[2],r_csc3rd_ofst3,p_of2[3]);
					PE_H10_1_E60_QRd02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,p_of2[4],r_csc3rd_ofst5,p_of2[5]);
					/* csc4 */
					PE_H10_1_E60_QRd02(hdr_csc4_ctrl_01,r_csc4th_coef0,p_co3[0],r_csc4th_coef1,p_co3[1]);
					PE_H10_1_E60_QRd02(hdr_csc4_ctrl_02,r_csc4th_coef2,p_co3[2],r_csc4th_coef3,p_co3[3]);
					PE_H10_1_E60_QRd02(hdr_csc4_ctrl_03,r_csc4th_coef4,p_co3[4],r_csc4th_coef5,p_co3[5]);
					PE_H10_1_E60_QRd02(hdr_csc4_ctrl_04,r_csc4th_coef6,p_co3[6],r_csc4th_coef7,p_co3[7]);
					PE_H10_1_E60_QRd01(hdr_csc4_ctrl_05,r_csc4th_coef8,p_co3[8]);
					PE_H10_1_E60_QRd02(hdr_csc4_ctrl_06,r_csc4th_ofst0,p_of3[0],r_csc4th_ofst1,p_of3[1]);
					PE_H10_1_E60_QRd02(hdr_csc4_ctrl_07,r_csc4th_ofst2,p_of3[2],r_csc4th_ofst3,p_of3[3]);
					PE_H10_1_E60_QRd02(hdr_csc4_ctrl_08,r_csc4th_ofst4,p_of3[4],r_csc4th_ofst5,p_of3[5]);
					/* csc1(s2h) */
					PE_S2H_1_E60_QRd02(hdr_sdr2hdr_ctrl_02,r_csc1st_coef0,p_co4[0],r_csc1st_coef1,p_co4[1]);
					PE_S2H_1_E60_QRd02(hdr_sdr2hdr_ctrl_03,r_csc1st_coef2,p_co4[2],r_csc1st_coef3,p_co4[3]);
					PE_S2H_1_E60_QRd02(hdr_sdr2hdr_ctrl_04,r_csc1st_coef4,p_co4[4],r_csc1st_coef5,p_co4[5]);
					PE_S2H_1_E60_QRd02(hdr_sdr2hdr_ctrl_05,r_csc1st_coef6,p_co4[6],r_csc1st_coef7,p_co4[7]);
					PE_S2H_1_E60_QRd01(hdr_sdr2hdr_ctrl_06,r_csc1st_coef8,p_co4[8]);
					PE_S2H_1_E60_QRd02(hdr_sdr2hdr_ctrl_07,r_csc1st_ofst0,p_of4[0],r_csc1st_ofst1,p_of4[1]);
					PE_S2H_1_E60_QRd02(hdr_sdr2hdr_ctrl_08,r_csc1st_ofst2,p_of4[2],r_csc1st_ofst3,p_of4[3]);
					PE_S2H_1_E60_QRd02(hdr_sdr2hdr_ctrl_09,r_csc1st_ofst4,p_of4[4],r_csc1st_ofst5,p_of4[5]);
				}
				switch(rd_cnt)
				{
					PE_HDR_E60_CASE_SPRINT( 0,rd_cnt++,buffer,PE_HDR_E60_PRINT_START);
					PE_HDR_E60_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"(0)hdr csc1 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_1].type0,pInfo->cur_hdr_type[LX_PE_WIN_1],pInfo->pre_hdr_type[LX_PE_WIN_1]);
					PE_HDR_E60_CASE_SPRINT( 3,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT( 4,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[0], p_co0[1], p_co0[2], p_of0[0], p_of0[3]);
					PE_HDR_E60_CASE_SPRINT( 5,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[3], p_co0[4], p_co0[5], p_of0[1], p_of0[4]);
					PE_HDR_E60_CASE_SPRINT( 6,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co0[6], p_co0[7], p_co0[8], p_of0[2], p_of0[5]);
					PE_HDR_E60_CASE_SPRINT( 7,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT( 8,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT( 9,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(10,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(11,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(12,rd_cnt++,buffer,\
						"(0)hdr pcc type:%d\n",pInfo->pre_csc[LX_PE_WIN_1].type1);
					PE_HDR_E60_CASE_SPRINT(13,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(14,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[0], p_co1[1], p_co1[2], p_of1[0], p_of1[3]);
					PE_HDR_E60_CASE_SPRINT(15,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[3], p_co1[4], p_co1[5], p_of1[1], p_of1[4]);
					PE_HDR_E60_CASE_SPRINT(16,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co1[6], p_co1[7], p_co1[8], p_of1[2], p_of1[5]);
					PE_HDR_E60_CASE_SPRINT(17,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(18,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(19,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(20,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(21,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(22,rd_cnt++,buffer,\
						"(0)hdr csc3 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_1].type2,pInfo->cur_hdr_type[LX_PE_WIN_1],pInfo->pre_hdr_type[LX_PE_WIN_1]);
					PE_HDR_E60_CASE_SPRINT(23,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(24,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[0], p_co2[1], p_co2[2], p_of2[0], p_of2[3]);
					PE_HDR_E60_CASE_SPRINT(25,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[3], p_co2[4], p_co2[5], p_of2[1], p_of2[4]);
					PE_HDR_E60_CASE_SPRINT(26,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co2[6], p_co2[7], p_co2[8], p_of2[2], p_of2[5]);
					PE_HDR_E60_CASE_SPRINT(27,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(28,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(29,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(30,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(31,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(32,rd_cnt++,buffer,\
						"(0)hdr csc4 type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_1].type0,pInfo->cur_hdr_type[LX_PE_WIN_1],pInfo->pre_hdr_type[LX_PE_WIN_1]);
					PE_HDR_E60_CASE_SPRINT(33,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(34,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[0], p_co3[1], p_co3[2], p_of3[0], p_of3[3]);
					PE_HDR_E60_CASE_SPRINT(35,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[3], p_co3[4], p_co3[5], p_of3[1], p_of3[4]);
					PE_HDR_E60_CASE_SPRINT(36,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co3[6], p_co3[7], p_co3[8], p_of3[2], p_of3[5]);
					PE_HDR_E60_CASE_SPRINT(37,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(38,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(39,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(40,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(41,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(42,rd_cnt++,buffer,\
						"(0)hdr csc1(s2h) type:%d (hdr_type:%d <- %d)\n",\
						pInfo->pre_csc[LX_PE_WIN_1].type0,pInfo->cur_hdr_type[LX_PE_WIN_1],pInfo->pre_hdr_type[LX_PE_WIN_1]);
					PE_HDR_E60_CASE_SPRINT(43,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(44,rd_cnt++,buffer,\
						"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co4[0], p_co4[1], p_co4[2], p_of4[0], p_of4[3]);
					PE_HDR_E60_CASE_SPRINT(45,rd_cnt++,buffer,\
						"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co4[3], p_co4[4], p_co4[5], p_of4[1], p_of4[4]);
					PE_HDR_E60_CASE_SPRINT(46,rd_cnt++,buffer,\
						"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
						p_co4[6], p_co4[7], p_co4[8], p_of4[2], p_of4[5]);
					PE_HDR_E60_CASE_SPRINT(47,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_HDR_E60_CASE_SPRINT(48,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(49,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_CASE_SPRINT(50,rd_cnt++,buffer,PE_HDR_E60_PRINT_RESERVED);
					PE_HDR_E60_DFLT_SPRINT(rd_cnt=0,buffer,PE_HDR_E60_PRINT_END);
				}
			}
			else
			{
				snprintf(buffer,PE_TRACE_STR_SIZE,PE_HDR_E60_PRINT_EXIT);
				rd_cnt=0;
			}
			memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_GetHistoInfo(LX_PE_HDR_HISTO_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 i, ofst0, ofst1;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				UINT32 mode;
				PE_HDR_VERI_E60_QRd01(info_0,coremode0,mode);
				if (mode == PE_HDR_HW_E60_CORE_MODE_4_8K)
				{
					/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
					PE_H10_0_E60_Wr(hdr_c4_hist_ia_ctrl,0x00011000);
					PE_H10_0_E60_WrFL(hdr_c4_hist_ia_ctrl);
					//rd histogram
					ofst0 = 0;
					ofst1 = ofst0 + PE_HDR_HW_E60_HST_BIN_NUM;
					for(i=0;i<PE_HDR_HW_E60_HST_BIN_NUM;i++)
					{
						PE_H10_0_E60_RdFL(hdr_c4_hist_ia_data1);
						pstParams->status[i+ofst0] = PE_H10_0_E60_Rd(hdr_c4_hist_ia_data1);
						pstParams->status[i+ofst1] = pstParams->status[i+ofst0];
					}
					/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
					PE_H10_0_E60_Wr(hdr_c4_hist_ia_ctrl,0x00018000);
					PE_H10_0_E60_WrFL(hdr_c4_hist_ia_ctrl);
				}
				else
				{
					/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
					PE_H10_0_E60_Wr(hdr_hist_ia_ctrl,0x00011000);
					PE_H10_0_E60_WrFL(hdr_hist_ia_ctrl);
					//rd histogram
					ofst0 = 0;
					ofst1 = ofst0 + PE_HDR_HW_E60_HST_BIN_NUM;
					for(i=0;i<PE_HDR_HW_E60_HST_BIN_NUM;i++)
					{
						PE_H10_0_E60_RdFL(hdr_hist_ia_data1);
						pstParams->status[i+ofst0] = PE_H10_0_E60_Rd(hdr_hist_ia_data1);
						pstParams->status[i+ofst1] = pstParams->status[i+ofst0];
					}
					/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
					PE_H10_0_E60_Wr(hdr_hist_ia_ctrl,0x00018000);
					PE_H10_0_E60_WrFL(hdr_hist_ia_ctrl);
				}
				#if 0
				if(_g_hdr_hw_e60_trace)
				{
					UINT32 sum = 0;
					printk("mode:%d\n",mode);
					for (i=0;i<128;i++)
					{
						if ((i!=0) && (i%8==0))	printk("\n");
						printk("[%03d]%08x ", i, pstParams->status[i]);
						sum += pstParams->status[i];
					}
					printk("\n histo_sum = %d\n\n", sum);
				}
				#endif
			}
			if(PE_CHECK_WIN1(win_id))
			{
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
				PE_H10_1_E60_Wr(hdr_hist_ia_ctrl,0x00011000);
				PE_H10_1_E60_WrFL(hdr_hist_ia_ctrl);
				//rd histogram
				ofst0 = 0;
				ofst1 = ofst0 + PE_HDR_HW_E60_HST_BIN_NUM;
				for(i=0;i<PE_HDR_HW_E60_HST_BIN_NUM;i++)
				{
					PE_H10_1_E60_RdFL(hdr_hist_ia_data1);
					pstParams->status[i+ofst0] = PE_H10_1_E60_Rd(hdr_hist_ia_data1);
					pstParams->status[i+ofst1] = pstParams->status[i+ofst0];
				}
				PE_H10_1_E60_Wr01(hdr_hist_ia_ctrl,hif_hist_enable,0x1);
				PE_H10_1_E60_WrFL(hdr_hist_ia_ctrl);
			}
			if(PE_CHECK_WIN2(win_id))
			{
				UINT32 mode;
				PE_HDR_VERI_E60_QRd01(info_0,coremode0,mode);
				if (mode == PE_HDR_HW_E60_CORE_MODE_4_8K)
				{
					/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
					PE_S2H_0_E60_Wr(sdr2hdr_c4_hist_ia_ctrl,0x00011000);
					PE_S2H_0_E60_WrFL(sdr2hdr_c4_hist_ia_ctrl);
					//rd histogram
					ofst0 = 0;
					ofst1 = ofst0 + PE_HDR_HW_E60_HST_BIN_NUM;
					for(i=0;i<PE_HDR_HW_E60_HST_BIN_NUM;i++)
					{
						PE_S2H_0_E60_RdFL(sdr2hdr_c4_hist_ia_data1);
						pstParams->status[i+ofst0] = PE_S2H_0_E60_Rd(sdr2hdr_c4_hist_ia_data1);
						pstParams->status[i+ofst1] = pstParams->status[i+ofst0];
					}
					/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
					PE_S2H_0_E60_Wr(sdr2hdr_c4_hist_ia_ctrl,0x00018000);
					PE_S2H_0_E60_WrFL(sdr2hdr_c4_hist_ia_ctrl);
				}
				else
				{
					/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
					PE_S2H_0_E60_Wr(sdr2hdr_hist_ia_ctrl,0x00011000);
					PE_S2H_0_E60_WrFL(sdr2hdr_hist_ia_ctrl);
					//rd histogram
					ofst0 = 0;
					ofst1 = ofst0 + PE_HDR_HW_E60_HST_BIN_NUM;
					for(i=0;i<PE_HDR_HW_E60_HST_BIN_NUM;i++)
					{
						PE_S2H_0_E60_RdFL(sdr2hdr_hist_ia_data1);
						pstParams->status[i+ofst0] = PE_S2H_0_E60_Rd(sdr2hdr_hist_ia_data1);
						pstParams->status[i+ofst1] = pstParams->status[i+ofst0];
					}
					/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
					PE_S2H_0_E60_Wr(sdr2hdr_hist_ia_ctrl,0x00018000);
					PE_S2H_0_E60_WrFL(sdr2hdr_hist_ia_ctrl);
				}
			}
			if(PE_CHECK_WIN3(win_id))
			{
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
				PE_S2H_1_E60_Wr(sdr2hdr_hist_ia_ctrl,0x00011000);
				PE_S2H_1_E60_WrFL(sdr2hdr_hist_ia_ctrl);
				//rd histogram
				ofst0 = 0;
				ofst1 = ofst0 + PE_HDR_HW_E60_HST_BIN_NUM;
				for(i=0;i<PE_HDR_HW_E60_HST_BIN_NUM;i++)
				{
					PE_S2H_1_E60_RdFL(sdr2hdr_hist_ia_data1);
					pstParams->status[i+ofst0] = PE_S2H_1_E60_Rd(sdr2hdr_hist_ia_data1);
					pstParams->status[i+ofst1] = pstParams->status[i+ofst0];
				}
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
				PE_S2H_1_E60_Wr(sdr2hdr_hist_ia_ctrl,0x00018000);
				PE_S2H_1_E60_WrFL(sdr2hdr_hist_ia_ctrl);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_SetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, count, oper, size, connect[2];
	volatile UINT32 *p_pe_hdr_hw_e60_ddr = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_E60_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_E60_LUT_TYPE_A)	ofst = PE_HDR_HW_E60_GetEotfOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_E60_GetEotfOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[EO]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_e60_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_E60_IncreaseEotfCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[EO0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst,size,connect[LX_PE_WIN_0],count);
					PE_HDR_HW_E60_BACKUP_TRACE("[EO0][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_E60_VERSION,\
						pstParams->oper, pstParams->size, \
						ofst, connect[LX_PE_WIN_0], count, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_1);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_E60_LUT_TYPE_A)	ofst = PE_HDR_HW_E60_GetEotfOffset(LX_PE_WIN_1, oper);
					else								ofst = PE_HDR_HW_E60_GetEotfOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[EO]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_1], pstParams->oper);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_e60_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_E60_IncreaseEotfCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[EO1][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst,size,connect[LX_PE_WIN_1],count);
					PE_HDR_HW_E60_BACKUP_TRACE("[EO1][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_E60_VERSION,\
						pstParams->oper, pstParams->size, \
						ofst, connect[LX_PE_WIN_1], count, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_GetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 ofst, count, oper, size;
	UINT32 connect[2];
	volatile UINT32 *p_pe_hdr_hw_e60_ddr = NULL;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		PE_HDR_HW_E60_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					//addr = (void *)gPE_HDR_DDR_E60;
					if (oper>=PE_HDR_HW_E60_LUT_TYPE_A)	ofst = PE_HDR_HW_E60_GetEotfOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_E60_GetEotfOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[EO]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)pstParams->data, (void *)p_pe_hdr_hw_e60_ddr, size);
					count = PE_HDR_HW_E60_GetEotfCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[EO0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst,size,connect[LX_PE_WIN_0],count);
				} while(0);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_1);
				do {
					oper = pstParams->oper&0xF;
					//addr = (void *)gPE_HDR_DDR_E60;
					if (oper>=PE_HDR_HW_E60_LUT_TYPE_A)	ofst = PE_HDR_HW_E60_GetEotfOffset(LX_PE_WIN_1, oper);
					else								ofst = PE_HDR_HW_E60_GetEotfOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[EO]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_1], pstParams->oper);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)pstParams->data, (void *)p_pe_hdr_hw_e60_ddr, size);
					count = PE_HDR_HW_E60_GetEotfCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[EO1][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst,size,connect[LX_PE_WIN_1],count);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
int PE_HDR_HW_E60_SetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 ofst, count, oper, size;
	UINT32 connect[2];
	volatile UINT32 *p_pe_hdr_hw_e60_ddr = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		PE_HDR_HW_E60_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_E60_LUT_TYPE_A)	ofst = PE_HDR_HW_E60_GetOetfOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_E60_GetOetfOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[OE]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_e60_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_E60_IncreaseOetfCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[OE0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst,size,connect[LX_PE_WIN_0],count);
					PE_HDR_HW_E60_BACKUP_TRACE("[OE0][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),PE_HDR_DDR_E60_VERSION,\
						pstParams->oper, pstParams->size, \
						ofst, connect[LX_PE_WIN_0], count, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_1);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_E60_LUT_TYPE_A)	ofst = PE_HDR_HW_E60_GetOetfOffset(LX_PE_WIN_1, oper);
					else								ofst = PE_HDR_HW_E60_GetOetfOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[OE]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_1], pstParams->oper);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)p_pe_hdr_hw_e60_ddr, (void *)pstParams->data, size);
					wmb();
					count = PE_HDR_HW_E60_IncreaseOetfCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[OE1][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst,size,connect[LX_PE_WIN_1],count);
					PE_HDR_HW_E60_BACKUP_TRACE("[OE1][%s]v%d,o,s:%X,%d,of:%x,c[%d]:%d,d:%08x,%08x,%08x",\
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),PE_HDR_DDR_E60_VERSION,\
						pstParams->oper, pstParams->size, \
						ofst, connect[LX_PE_WIN_1], count, pstParams->data[0], pstParams->data[1], pstParams->data[2]);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_GetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 ofst, count, oper, size;
	UINT32 connect[2];
	volatile UINT32 *p_pe_hdr_hw_e60_ddr = NULL;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		PE_HDR_HW_E60_DBG_PRINT("[wid:%d] oper:0x%x, size:%d\n", pstParams->win_id, pstParams->oper, pstParams->size);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				connect[LX_PE_WIN_0] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_0);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_E60_LUT_TYPE_A)	ofst = PE_HDR_HW_E60_GetOetfOffset(LX_PE_WIN_0, oper);
					else								ofst = PE_HDR_HW_E60_GetOetfOffset(LX_PE_WIN_0, connect[LX_PE_WIN_0]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[OE]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_0], pstParams->oper);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)pstParams->data, (void *)p_pe_hdr_hw_e60_ddr, size);
					wmb();
					count = PE_HDR_HW_E60_GetOetfCount(LX_PE_WIN_0, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[OE0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_0]),\
						ofst,size,connect[LX_PE_WIN_0],count);
				} while(0);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				connect[LX_PE_WIN_1] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_1);
				do {
					oper = pstParams->oper&0xF;
					if (oper>=PE_HDR_HW_E60_LUT_TYPE_A)	ofst = PE_HDR_HW_E60_GetOetfOffset(LX_PE_WIN_1, oper);
					else								ofst = PE_HDR_HW_E60_GetOetfOffset(LX_PE_WIN_1, connect[LX_PE_WIN_1]);
					if (ofst==0xffffffff)	{PE_HDR_HW_E60_DBG_PRINT("[OE]c[%d,%d]ofst invalid.\n", connect[LX_PE_WIN_1], pstParams->oper);break;}
					p_pe_hdr_hw_e60_ddr = gPE_HDR_DDR_E60 + (ofst>>2);//u32_addr
					CHECK_KNULL(p_pe_hdr_hw_e60_ddr);
					size = sizeof(UINT32)*pstParams->size;
					memcpy((void *)pstParams->data, (void *)p_pe_hdr_hw_e60_ddr, size);
					wmb();
					count = PE_HDR_HW_E60_GetOetfCount(LX_PE_WIN_1, ofst);
					PE_HDR_HW_E60_DBG_PRINT("[OE0][%s]of:%x,size:%d, c[%d]:%d\n", \
						PE_HDR_HW_E60_CONNECT_TO_STR(connect[LX_PE_WIN_1]),\
						ofst,size,connect[LX_PE_WIN_1],count);
				} while(0);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_SetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, cur_hdr_info, connect[2], support;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	LX_PE_HDR_OP_MD_T *p_op = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_E60_DBG_PRINT("set[%d] : data[0]:0x%08x\n", pstParams->win_id, pstParams->data[0]);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				for (i=0;i<LX_PE_WIN_ALL;i++)
				{
					memcpy(&(pInfo->md_inf[i]), pstParams, sizeof(LX_PE_HDR_MODE_INFO_T));
				}
				connect[LX_PE_WIN_0] = PE_HDR_HW_E60_GetConnectMode(LX_PE_WIN_0);
				p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_0].data[0]));
				/* set support info */
				support = p_op->sup_mod;
				ret = PE_HDR_HW_E60_SetSupportInfo(LX_PE_WIN_0,support);
				PE_HDR_HW_E60_CHECK_CODE(ret, break, \
					"[%s,%d] PE_HDR_HW_E60_SetSupportInfo() error.\n",__F__,__L__);
				/* set hdr_off */
				cur_hdr_info = p_op->hdr_off;
				ret = PE_FWI_E60_SetHdrInfo(&cur_hdr_info);
				PE_HDR_HW_E60_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_E60_SetHdrInfo() error.\n",__F__,__L__);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_GetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id, temp;
	UINT32 i, hdr_mode;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	LX_PE_HDR_OP_MD_T *p_op = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				p_op = (LX_PE_HDR_OP_MD_T *)(&(pInfo->md_inf[LX_PE_WIN_0].data[0]));
				hdr_mode = 0;
				ret = PE_FWI_E60_GetHdrMode(&hdr_mode);
				PE_HDR_HW_E60_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_E60_GetHdrMode() error.\n",__F__,__L__);
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
			PE_HDR_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_E60_SetColorCorrect(LX_PE_HDR_CCR_T *pstParams)
{
	int ret = RET_OK;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_HW_E60_DBG_PRINT("set[%d]:%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x\n", \
			pstParams->win_id,pstParams->data[0],pstParams->data[1],\
			pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
			pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
			pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_H10_0_E60_RdFL(hdr_hue_sat_ctrl);
				PE_H10_0_E60_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
				PE_H10_0_E60_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
				PE_H10_0_E60_WrFL(hdr_hue_sat_ctrl);

				PE_H10_0_E60_QWr(hdr_lgain_lut_ctrl_00,pstParams->data[6]);
				PE_H10_0_E60_QWr(hdr_lgain_lut_ctrl_01,pstParams->data[7]);
				PE_H10_0_E60_QWr(hdr_lgain_lut_ctrl_02,pstParams->data[8]);
				PE_H10_0_E60_QWr(hdr_lgain_lut_ctrl_03,pstParams->data[9]);
				PE_H10_0_E60_QWr(hdr_lgain_lut_ctrl_04,pstParams->data[10]);
				PE_H10_0_E60_QWr(hdr_lgain_lut_ctrl_05,pstParams->data[11]);
				PE_H10_0_E60_QWr(hdr_lgain_lut_ctrl_06,pstParams->data[12]);
				PE_H10_0_E60_QWr(hdr_lgain_lut_ctrl_07,pstParams->data[13]);
				PE_H10_0_E60_QWr(hdr_sgain_lut_ctrl_00,pstParams->data[14]);
				PE_H10_0_E60_QWr(hdr_sgain_lut_ctrl_01,pstParams->data[15]);
				PE_H10_0_E60_QWr(hdr_sgain_lut_ctrl_02,pstParams->data[16]);
				PE_H10_0_E60_QWr(hdr_sgain_lut_ctrl_03,pstParams->data[17]);
				PE_H10_0_E60_QWr(hdr_sgain_lut_ctrl_04,pstParams->data[18]);
				PE_H10_0_E60_QWr(hdr_sgain_lut_ctrl_05,pstParams->data[19]);
				PE_H10_0_E60_QWr(hdr_sgain_lut_ctrl_06,pstParams->data[20]);
				PE_H10_0_E60_QWr(hdr_sgain_lut_ctrl_07,pstParams->data[21]);

				PE_H10_1_E60_RdFL(hdr_hue_sat_ctrl);
				PE_H10_1_E60_Wr01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
				PE_H10_1_E60_Wr01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
				PE_H10_1_E60_WrFL(hdr_hue_sat_ctrl);

				PE_H10_1_E60_QWr(hdr_lgain_lut_ctrl_00,pstParams->data[6]);
				PE_H10_1_E60_QWr(hdr_lgain_lut_ctrl_01,pstParams->data[7]);
				PE_H10_1_E60_QWr(hdr_lgain_lut_ctrl_02,pstParams->data[8]);
				PE_H10_1_E60_QWr(hdr_lgain_lut_ctrl_03,pstParams->data[9]);
				PE_H10_1_E60_QWr(hdr_lgain_lut_ctrl_04,pstParams->data[10]);
				PE_H10_1_E60_QWr(hdr_lgain_lut_ctrl_05,pstParams->data[11]);
				PE_H10_1_E60_QWr(hdr_lgain_lut_ctrl_06,pstParams->data[12]);
				PE_H10_1_E60_QWr(hdr_lgain_lut_ctrl_07,pstParams->data[13]);
				PE_H10_1_E60_QWr(hdr_sgain_lut_ctrl_00,pstParams->data[14]);
				PE_H10_1_E60_QWr(hdr_sgain_lut_ctrl_01,pstParams->data[15]);
				PE_H10_1_E60_QWr(hdr_sgain_lut_ctrl_02,pstParams->data[16]);
				PE_H10_1_E60_QWr(hdr_sgain_lut_ctrl_03,pstParams->data[17]);
				PE_H10_1_E60_QWr(hdr_sgain_lut_ctrl_04,pstParams->data[18]);
				PE_H10_1_E60_QWr(hdr_sgain_lut_ctrl_05,pstParams->data[19]);
				PE_H10_1_E60_QWr(hdr_sgain_lut_ctrl_06,pstParams->data[20]);
				PE_H10_1_E60_QWr(hdr_sgain_lut_ctrl_07,pstParams->data[21]);

				pInfo->reg_hue_prsv_ratio = pstParams->data[0];
				pInfo->reg_sat_prsv_ratio = pstParams->data[1];

				pInfo->lgain_lut[0] = pstParams->data[6];
				pInfo->lgain_lut[1] = pstParams->data[7];
				pInfo->lgain_lut[2] = pstParams->data[8];
				pInfo->lgain_lut[3] = pstParams->data[9];
				pInfo->lgain_lut[4] = pstParams->data[10];
				pInfo->lgain_lut[5] = pstParams->data[11];
				pInfo->lgain_lut[6] = pstParams->data[12];
				pInfo->lgain_lut[7] = pstParams->data[13];
				pInfo->sgain_lut[0] = pstParams->data[14];
				pInfo->sgain_lut[1] = pstParams->data[15];
				pInfo->sgain_lut[2] = pstParams->data[16];
				pInfo->sgain_lut[3] = pstParams->data[17];
				pInfo->sgain_lut[4] = pstParams->data[18];
				pInfo->sgain_lut[5] = pstParams->data[19];
				pInfo->sgain_lut[6] = pstParams->data[20];
				pInfo->sgain_lut[7] = pstParams->data[21];

				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(hs.hdr_hue_sat_ctrl.reg_hue_prsv_ratio,pstParams->data[0]);
					PE_CHPI_APB0_E60F20_Wr(hs.hdr_hue_sat_ctrl.reg_sat_prsv_ratio,pstParams->data[1]);
					PE_CHPI_APB0_E60F20_WrFL(hs.hdr_hue_sat_ctrl.udata32);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_00.udata32,pstParams->data[6]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_01.udata32,pstParams->data[7]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_02.udata32,pstParams->data[8]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_03.udata32,pstParams->data[9]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_04.udata32,pstParams->data[10]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_05.udata32,pstParams->data[11]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_06.udata32,pstParams->data[12]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_lgain_lut_ctrl_07.udata32,pstParams->data[13]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_00.udata32,pstParams->data[14]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_01.udata32,pstParams->data[15]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_02.udata32,pstParams->data[16]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_03.udata32,pstParams->data[17]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_04.udata32,pstParams->data[18]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_05.udata32,pstParams->data[19]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_06.udata32,pstParams->data[20]);
					PE_CHPI_APB0_E60F20_QWr(hs.hdr_sgain_lut_ctrl_07.udata32,pstParams->data[21]);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_HS);
				} while(0);
				#endif
				PE_HDR_HW_E60_BACKUP_TRACE("[CC0]%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x", \
					pstParams->data[0],pstParams->data[1],\
					pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
					pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
					pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
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
int PE_HDR_HW_E60_GetColorCorrect(LX_PE_HDR_CCR_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_HDR_HW_E60_SETTINGS_T *pInfo=&_g_pe_hdr_hw_e60_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_H10_0_E60_RdFL(hdr_hue_sat_ctrl);
				PE_H10_0_E60_Rd01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
				PE_H10_0_E60_Rd01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
				PE_H10_0_E60_RdFL(hdr_hue_sat_alpha_ctrl);
				PE_H10_0_E60_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pstParams->data[2]);
				PE_H10_0_E60_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pstParams->data[3]);
				PE_H10_0_E60_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pstParams->data[4]);
				PE_H10_0_E60_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pstParams->data[5]);
				PE_H10_0_E60_RdFL(hdr_lgain_lut_ctrl_00);
				PE_H10_0_E60_RdFL(hdr_lgain_lut_ctrl_01);
				PE_H10_0_E60_RdFL(hdr_lgain_lut_ctrl_02);
				PE_H10_0_E60_RdFL(hdr_lgain_lut_ctrl_03);
				PE_H10_0_E60_RdFL(hdr_lgain_lut_ctrl_04);
				PE_H10_0_E60_RdFL(hdr_lgain_lut_ctrl_05);
				PE_H10_0_E60_RdFL(hdr_lgain_lut_ctrl_06);
				PE_H10_0_E60_RdFL(hdr_lgain_lut_ctrl_07);
				PE_H10_0_E60_RdFL(hdr_sgain_lut_ctrl_00);
				PE_H10_0_E60_RdFL(hdr_sgain_lut_ctrl_01);
				PE_H10_0_E60_RdFL(hdr_sgain_lut_ctrl_02);
				PE_H10_0_E60_RdFL(hdr_sgain_lut_ctrl_03);
				PE_H10_0_E60_RdFL(hdr_sgain_lut_ctrl_04);
				PE_H10_0_E60_RdFL(hdr_sgain_lut_ctrl_05);
				PE_H10_0_E60_RdFL(hdr_sgain_lut_ctrl_06);
				PE_H10_0_E60_RdFL(hdr_sgain_lut_ctrl_07);
				pstParams->data[6]  = PE_H10_0_E60_Rd(hdr_lgain_lut_ctrl_00);
				pstParams->data[7]  = PE_H10_0_E60_Rd(hdr_lgain_lut_ctrl_01);
				pstParams->data[8]  = PE_H10_0_E60_Rd(hdr_lgain_lut_ctrl_02);
				pstParams->data[9]  = PE_H10_0_E60_Rd(hdr_lgain_lut_ctrl_03);
				pstParams->data[10] = PE_H10_0_E60_Rd(hdr_lgain_lut_ctrl_04);
				pstParams->data[11] = PE_H10_0_E60_Rd(hdr_lgain_lut_ctrl_05);
				pstParams->data[12] = PE_H10_0_E60_Rd(hdr_lgain_lut_ctrl_06);
				pstParams->data[13] = PE_H10_0_E60_Rd(hdr_lgain_lut_ctrl_07);
				pstParams->data[14] = PE_H10_0_E60_Rd(hdr_sgain_lut_ctrl_00);
				pstParams->data[15] = PE_H10_0_E60_Rd(hdr_sgain_lut_ctrl_01);
				pstParams->data[16] = PE_H10_0_E60_Rd(hdr_sgain_lut_ctrl_02);
				pstParams->data[17] = PE_H10_0_E60_Rd(hdr_sgain_lut_ctrl_03);
				pstParams->data[18] = PE_H10_0_E60_Rd(hdr_sgain_lut_ctrl_04);
				pstParams->data[19] = PE_H10_0_E60_Rd(hdr_sgain_lut_ctrl_05);
				pstParams->data[20] = PE_H10_0_E60_Rd(hdr_sgain_lut_ctrl_06);
				pstParams->data[21] = PE_H10_0_E60_Rd(hdr_sgain_lut_ctrl_07);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_H10_1_E60_RdFL(hdr_hue_sat_ctrl);
				PE_H10_1_E60_Rd01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
				PE_H10_1_E60_Rd01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
				PE_H10_1_E60_RdFL(hdr_hue_sat_alpha_ctrl);
				PE_H10_1_E60_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pstParams->data[2]);
				PE_H10_1_E60_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pstParams->data[3]);
				PE_H10_1_E60_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pstParams->data[4]);
				PE_H10_1_E60_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pstParams->data[5]);
				PE_H10_1_E60_RdFL(hdr_lgain_lut_ctrl_00);
				PE_H10_1_E60_RdFL(hdr_lgain_lut_ctrl_01);
				PE_H10_1_E60_RdFL(hdr_lgain_lut_ctrl_02);
				PE_H10_1_E60_RdFL(hdr_lgain_lut_ctrl_03);
				PE_H10_1_E60_RdFL(hdr_lgain_lut_ctrl_04);
				PE_H10_1_E60_RdFL(hdr_lgain_lut_ctrl_05);
				PE_H10_1_E60_RdFL(hdr_lgain_lut_ctrl_06);
				PE_H10_1_E60_RdFL(hdr_lgain_lut_ctrl_07);
				PE_H10_1_E60_RdFL(hdr_sgain_lut_ctrl_00);
				PE_H10_1_E60_RdFL(hdr_sgain_lut_ctrl_01);
				PE_H10_1_E60_RdFL(hdr_sgain_lut_ctrl_02);
				PE_H10_1_E60_RdFL(hdr_sgain_lut_ctrl_03);
				PE_H10_1_E60_RdFL(hdr_sgain_lut_ctrl_04);
				PE_H10_1_E60_RdFL(hdr_sgain_lut_ctrl_05);
				PE_H10_1_E60_RdFL(hdr_sgain_lut_ctrl_06);
				PE_H10_1_E60_RdFL(hdr_sgain_lut_ctrl_07);
				pstParams->data[6]  = PE_H10_1_E60_Rd(hdr_lgain_lut_ctrl_00);
				pstParams->data[7]  = PE_H10_1_E60_Rd(hdr_lgain_lut_ctrl_01);
				pstParams->data[8]  = PE_H10_1_E60_Rd(hdr_lgain_lut_ctrl_02);
				pstParams->data[9]  = PE_H10_1_E60_Rd(hdr_lgain_lut_ctrl_03);
				pstParams->data[10] = PE_H10_1_E60_Rd(hdr_lgain_lut_ctrl_04);
				pstParams->data[11] = PE_H10_1_E60_Rd(hdr_lgain_lut_ctrl_05);
				pstParams->data[12] = PE_H10_1_E60_Rd(hdr_lgain_lut_ctrl_06);
				pstParams->data[13] = PE_H10_1_E60_Rd(hdr_lgain_lut_ctrl_07);
				pstParams->data[14] = PE_H10_1_E60_Rd(hdr_sgain_lut_ctrl_00);
				pstParams->data[15] = PE_H10_1_E60_Rd(hdr_sgain_lut_ctrl_01);
				pstParams->data[16] = PE_H10_1_E60_Rd(hdr_sgain_lut_ctrl_02);
				pstParams->data[17] = PE_H10_1_E60_Rd(hdr_sgain_lut_ctrl_03);
				pstParams->data[18] = PE_H10_1_E60_Rd(hdr_sgain_lut_ctrl_04);
				pstParams->data[19] = PE_H10_1_E60_Rd(hdr_sgain_lut_ctrl_05);
				pstParams->data[20] = PE_H10_1_E60_Rd(hdr_sgain_lut_ctrl_06);
				pstParams->data[21] = PE_H10_1_E60_Rd(hdr_sgain_lut_ctrl_07);
			}
			if(PE_CHECK_WIN2(win_id))
			{
				pstParams->data[0] = pInfo->reg_hue_prsv_ratio;
				pstParams->data[1] = pInfo->reg_sat_prsv_ratio;
				pstParams->data[2] = 2;
				pstParams->data[3] = 2;
				pstParams->data[4] = 2;
				pstParams->data[5] = 2;
				pstParams->data[6]  = pInfo->lgain_lut[0];
				pstParams->data[7]  = pInfo->lgain_lut[1];
				pstParams->data[8]  = pInfo->lgain_lut[2];
				pstParams->data[9]  = pInfo->lgain_lut[3];
				pstParams->data[10] = pInfo->lgain_lut[4];
				pstParams->data[11] = pInfo->lgain_lut[5];
				pstParams->data[12] = pInfo->lgain_lut[6];
				pstParams->data[13] = pInfo->lgain_lut[7];
				pstParams->data[14] = pInfo->sgain_lut[0];
				pstParams->data[15] = pInfo->sgain_lut[1];
				pstParams->data[16] = pInfo->sgain_lut[2];
				pstParams->data[17] = pInfo->sgain_lut[3];
				pstParams->data[18] = pInfo->sgain_lut[4];
				pstParams->data[19] = pInfo->sgain_lut[5];
				pstParams->data[20] = pInfo->sgain_lut[6];
				pstParams->data[21] = pInfo->sgain_lut[7];
			}
		}
		else
		{
			PE_HDR_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_HDR_HW_E60_DBG_PRINT("get[%d]:%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x\n", \
			pstParams->win_id,pstParams->data[0],pstParams->data[1],\
			pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
			pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
			pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);
	} while(0);
	return ret;
}

/* see videodev2_ext.h */
/* extra PQ inner pattern */
#define MAX_EXT_HDR_PATTERN_GRADATION_LINE (4) // it may depends on chip limitation
#define MAX_EXT_HDR_PATTERN_WINBOX (10)         // it may depends on chip limitation
#define MAX_EXT_HDR_PATTERN_GRADATION_H_STRIDE_SIZE                                \
    (254) // it may depends on chip limitation
#define EXT_HDR_PATTERN_GRADATION_H_STRIDE_STEP                                    \
    (2) // it may depends on chip limitation
#define MAX_EXT_HDR_PATTERN_GRADATION_V_STRIDE_SIZE                                \
    (127) // it may depends on chip limitation
#define EXT_HDR_PATTERN_GRADATION_V_STRIDE_STEP                                    \
    (1)                           // it may depends on chip limitation
#define EXT_HDR_PATTERN_WIDTH (3840)  // it may depends on chip limitation
#define EXT_HDR_PATTERN_HEIGHT (2160) // it may depends on chip limitation

enum V4L2_VPQ_EXT_HDR_PATTERN_MODE {
    V4L2_VPQ_EXT_HDR_PATTERN_WINBOX,
    V4L2_VPQ_EXT_HDR_PATTERN_GRADATION,
    V4L2_VPQ_EXT_HDR_PATTERN_MAX
};
enum V4L2_VPQ_EXT_HDR_PATTERN_GRADATION_DIRECTION {
    V4L2_VPQ_EXT_HDR_PATTERN_GRADATION_DIRECTION_HORIZONTAL,
    V4L2_VPQ_EXT_HDR_PATTERN_GRADATION_DIRECTION_VERTICAL,
    V4L2_VPQ_EXT_HDR_PATTERN_GRADATION_DIRECTION_MAX
};
struct v4l2_vpq_ext_hdr_pattern_gradation_line_attr {
    unsigned char lineIdx; // gradation line index
    unsigned short
        start_R; // 1st gradation block's red level as a 10bit resolution
    unsigned short
        start_G; // 1st gradation block's green level as a 10bit resolution
    unsigned short
        start_B; // 1st gradation block's blue level as a 10bit resolution
    unsigned short step_R;     // step size for next gradation block
    unsigned short step_G;     // step size for next gradation block
    unsigned short step_B;     // step size for next gradation block
    unsigned short strideSize; // gradation block's width(horizontal
                               // mode)/height(vertical mode)
};
struct v4l2_vpq_ext_hdr_pattern_gradation_info {
    unsigned char numGrad; // number of gradation lines in a screen
    enum V4L2_VPQ_EXT_HDR_PATTERN_GRADATION_DIRECTION eGradMode;
    struct v4l2_vpq_ext_hdr_pattern_gradation_line_attr
        stLineAttr[MAX_EXT_HDR_PATTERN_GRADATION_LINE];
};
struct v4l2_vpq_ext_hdr_pattern_winbox_win_attr {
    unsigned short winIdx; // window layer index. 0:background
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
    unsigned short fill_R; // 10 bit resolution
    unsigned short fill_G; // 10 bit resolution
    unsigned short fill_B; // 10 bit resolution
};
struct v4l2_vpq_ext_hdr_pattern_winbox_info {
    unsigned char
        u8NumWin; // number of windows in a screen(including background window)
    struct v4l2_vpq_ext_hdr_pattern_winbox_win_attr
        stWinBoxAttr[MAX_EXT_HDR_PATTERN_WINBOX];
};
struct v4l2_vpq_ext_hdr_pattern_info {		// old version : this will be removed in near-time
    unsigned char bOnOff;
    enum V4L2_VPQ_EXT_HDR_PATTERN_MODE eMode;
    struct v4l2_vpq_ext_hdr_pattern_gradation_info *pstGradInfo;
    struct v4l2_vpq_ext_hdr_pattern_winbox_info *pstWinboxInfo;
};
#define USE_EXT_HDR_PATTERN_INFO_V2
struct v4l2_vpq_ext_hdr_pattern_info_v2 {
    unsigned char bOnOff;
    enum V4L2_VPQ_EXT_HDR_PATTERN_MODE eMode;
    struct v4l2_vpq_ext_hdr_pattern_gradation_info stGradInfo;
    struct v4l2_vpq_ext_hdr_pattern_winbox_info stWinboxInfo;
};

int PE_HDR_HW_E60_SetPattern(void *pstParams)
{
	int ret = RET_OK;
	UINT32 i,wr_data;
	UINT32 num_win,num_grd;
	UINT32 enable,type,en_type,grad_en,h_grad,stride;
	UINT32 mask_flag,size_x,size_y,ratio_x,ratio_y;
	struct v4l2_vpq_ext_hdr_pattern_info_v2 *p;
	do{
		CHECK_KNULL(pstParams);
		p = (struct v4l2_vpq_ext_hdr_pattern_info_v2 *)pstParams;

		PE_HDR_HW_E60_DBG_PRINT("on:%d,mode:%d\n",p->bOnOff,p->eMode);
		PE_HDR_HW_E60_DBG_PRINT("grad num:%d,mode:%d\n",p->stGradInfo.numGrad,p->stGradInfo.eGradMode);
		for (i=0; i<p->stGradInfo.numGrad; i++)
		{
			PE_HDR_HW_E60_DBG_PRINT("[%d] %d, %x,%x,%x, %x,%x,%x, %x\n",i,\
				p->stGradInfo.stLineAttr[i].lineIdx,p->stGradInfo.stLineAttr[i].start_R,\
				p->stGradInfo.stLineAttr[i].start_G,p->stGradInfo.stLineAttr[i].start_B,\
				p->stGradInfo.stLineAttr[i].step_R,p->stGradInfo.stLineAttr[i].step_G,\
				p->stGradInfo.stLineAttr[i].step_B,p->stGradInfo.stLineAttr[i].strideSize);
		}
		PE_HDR_HW_E60_DBG_PRINT("winbox num:%d\n",p->stWinboxInfo.u8NumWin);
		for (i=0; i<p->stWinboxInfo.u8NumWin; i++)
		{
			PE_HDR_HW_E60_DBG_PRINT("[%d] %d, %d,%d,%d,%d, %x,%x,%x\n",i,\
				p->stWinboxInfo.stWinBoxAttr[i].winIdx,p->stWinboxInfo.stWinBoxAttr[i].x,\
				p->stWinboxInfo.stWinBoxAttr[i].y,p->stWinboxInfo.stWinBoxAttr[i].w,\
				p->stWinboxInfo.stWinBoxAttr[i].h,p->stWinboxInfo.stWinBoxAttr[i].fill_R,\
				p->stWinboxInfo.stWinBoxAttr[i].fill_G,p->stWinboxInfo.stWinBoxAttr[i].fill_B);
		}

		/* get settings */
		enable = (p->bOnOff>0)? 1:0;
		type = (p->eMode==V4L2_VPQ_EXT_HDR_PATTERN_WINBOX)? 0:1;
		en_type = (!enable)? 0:(type==0)? 1:2;

		/* 20200115, 4k 1core mode(AVTASK-423) */
		ret = PE_FWI_E60_SetPattern(&en_type);
		PE_HDR_HW_E60_CHECK_CODE(ret, break, \
			"[%s,%d] PE_FWI_E60_SetPattern() error.\n",__F__,__L__);

		num_win = p->stWinboxInfo.u8NumWin;
		if (num_win > MAX_EXT_HDR_PATTERN_WINBOX)
		{
			num_win = MAX_EXT_HDR_PATTERN_WINBOX;
		}
		else if (num_win == 0)
		{
			num_win = 1;
		}
		num_grd = p->stGradInfo.numGrad;
		num_grd = (num_grd<<1)>>1;
		if (num_grd > MAX_EXT_HDR_PATTERN_GRADATION_LINE)
		{
			num_grd = MAX_EXT_HDR_PATTERN_GRADATION_LINE;
		}
		else if (num_grd == 0)
		{
			num_grd = 2;
		}

		grad_en = 0;
		for (i=0; i<num_grd; i++)
		{
			grad_en |= (1<<i);
		}

		h_grad = (p->stGradInfo.eGradMode==V4L2_VPQ_EXT_HDR_PATTERN_GRADATION_DIRECTION_HORIZONTAL)? 1:0;
		stride = p->stGradInfo.stLineAttr[0].strideSize;

		mask_flag = 0;
		for (i=0; i<num_win; i++)
		{
			mask_flag |= (1<<i);
		}

		//OS_MsecSleep(100);//SCDCR-5568
		#if 0
		PE_H10_0_E60_RdFL(hdr_top_ctrl_01);
		PE_H10_0_E60_Rd01(hdr_top_ctrl_01,width,size_x);
		PE_H10_0_E60_Rd01(hdr_top_ctrl_01,height,size_y);
		#else
		do {
			UINT32 i_size;
			int ret0 = SYS_IO_ReadRegArray(0xc9003634,4,&i_size);//IPP_M0
			size_x = i_size&0xffff;
			size_y = (i_size>>16)&0xffff;
		} while(0);
		#endif

		ratio_x = (size_x<<10)/EXT_HDR_PATTERN_WIDTH;
		ratio_y = (size_y<<10)/EXT_HDR_PATTERN_HEIGHT;

		PE_HDR_HW_E60_DBG_PRINT("num:%d,%d, en,typ:%d,%d, grd,h_g:0x%x,%d, strd:%d\n",\
			num_win,num_grd,enable,type,grad_en,h_grad,stride);
		PE_HDR_HW_E60_DBG_PRINT("size:%d,%d, flag:0x%x, ratio:%d,%d\n",\
			size_x,size_y,mask_flag,ratio_x,ratio_y);

		#if 0	//20200130, need to confirm
		if (size_x>=3840)			stride = 3;
		else if (size_x>=1920)		stride = 2;
		else if (size_x>=960)		stride = 1;
		else						stride = 0;
		#endif

		do {
			/* PE_H10_E */
			PE_H10_0_E60_RdFL(hdr_tpg_ctrl_00);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_00,tpg_enable,0);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_00,tpg_type,type);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_00,tpg_grad_en,grad_en)
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_00,tpg_h_grad,h_grad);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_00,tpg_stride,stride);
			PE_H10_0_E60_WrFL(hdr_tpg_ctrl_00);
			OS_MsecSleep(30);

			PE_H10_0_E60_RdFL(hdr_tpg_ctrl_01);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_01,tpg_size_x,size_x);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_01,tpg_size_y,size_y);
			PE_H10_0_E60_WrFL(hdr_tpg_ctrl_01);

			PE_H10_0_E60_RdFL(hdr_tpg_ctrl_02);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_02,tpg_mask_flag,mask_flag);
			PE_H10_0_E60_WrFL(hdr_tpg_ctrl_02);

			PE_H10_0_E60_RdFL(hdr_tpg_ctrl_03);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_03,tpg_in_out_sel,0x0);
			PE_H10_0_E60_WrFL(hdr_tpg_ctrl_03);

			PE_H10_0_E60_RdFL(hdr_tpg_ctrl_04);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_04,tpg_color_r,0x0);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_04,tpg_color_b,0x0);
			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_04,tpg_color_g,0x0);
			PE_H10_0_E60_WrFL(hdr_tpg_ctrl_04);

			PE_H10_0_E60_QWr(hdr_tpg_ia_ctrl,0x00001000);//patch color
			for (i=0; i<num_win; i++)
			{
				wr_data = p->stWinboxInfo.stWinBoxAttr[i].fill_R;
				wr_data |= (p->stWinboxInfo.stWinBoxAttr[i].fill_B << 10);
				wr_data |= (p->stWinboxInfo.stWinBoxAttr[i].fill_G << 20);
				PE_HDR_HW_E60_DBG_PRINT("H10_0[%d]win color:0x%08x\n",i,wr_data);
				PE_H10_0_E60_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_0_E60_QWr(hdr_tpg_ia_ctrl,0x00001020);//patch start (x,y)
			for (i=0; i<num_win; i++)
			{
				wr_data = (p->stWinboxInfo.stWinBoxAttr[i].y*ratio_y)>>10;
				wr_data |= (((p->stWinboxInfo.stWinBoxAttr[i].x*ratio_x)>>10) << 16);
				PE_H10_0_E60_QWr(hdr_tpg_ia_data,wr_data);
				PE_HDR_HW_E60_DBG_PRINT("H10_0[%d]win start:0x%08x\n",i,wr_data);
			}
			PE_H10_0_E60_QWr(hdr_tpg_ia_ctrl,0x00001040);//patch end (x,y)

			for (i=0; i<num_win; i++)
			{
				wr_data = ((p->stWinboxInfo.stWinBoxAttr[i].y + p->stWinboxInfo.stWinBoxAttr[i].h)*ratio_y)>>10;
				wr_data |= ((((p->stWinboxInfo.stWinBoxAttr[i].x + p->stWinboxInfo.stWinBoxAttr[i].w)*ratio_x)>>10) << 16);
				PE_HDR_HW_E60_DBG_PRINT("H10_0[%d]win end  :0x%08x\n",i,wr_data);
				PE_H10_0_E60_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_0_E60_QWr(hdr_tpg_ia_ctrl,0x00001060);//gradation start color
			for (i=0; i<num_grd; i++)
			{
				wr_data = p->stGradInfo.stLineAttr[i].start_R;
				wr_data |= (p->stGradInfo.stLineAttr[i].start_B << 10);
				wr_data |= (p->stGradInfo.stLineAttr[i].start_G << 20);
				PE_HDR_HW_E60_DBG_PRINT("H10_0[%d]grd start:0x%08x\n",i,wr_data);
				PE_H10_0_E60_QWr(hdr_tpg_ia_data,wr_data);
			}
			PE_H10_0_E60_QWr(hdr_tpg_ia_ctrl,0x00001064);//gradation step color
			for (i=0; i<num_grd; i++)
			{
				wr_data = p->stGradInfo.stLineAttr[i].step_R;
				wr_data |= (p->stGradInfo.stLineAttr[i].step_B << 10);
				wr_data |= (p->stGradInfo.stLineAttr[i].step_G << 20);
				PE_HDR_HW_E60_DBG_PRINT("H10_0[%d]grd color:0x%08x\n",i,wr_data);
				PE_H10_0_E60_QWr(hdr_tpg_ia_data,wr_data);
			}
			PE_H10_0_E60_QWr(hdr_tpg_ia_ctrl,0x00001068);//gradation region size
			for (i=0; i<num_grd; i++)
			{
				if (h_grad == 1)
				{
					wr_data = (size_y / num_grd) * (i + 1);
				}
				else
				{
					wr_data = (size_x / num_grd) * (i + 1);
				}
				PE_HDR_HW_E60_DBG_PRINT("H10_0[%d]grd end  :0x%08x\n",i,wr_data);
				PE_H10_0_E60_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_0_E60_Wr01(hdr_tpg_ctrl_00,tpg_enable,enable);
			PE_H10_0_E60_WrFL(hdr_tpg_ctrl_00);

			/* 20191218, 1st csc off during pattern on(SCDCR-2960) */
			/* 20200115, moved to fw(AVTASK-423) */
			//PE_H10_0_E60_QWr01(hdr_csc1_ctrl_00,reg_csc1st_en,(enable>0)? 0:1);
		} while(0);

		do {
			/* PE_H10_O */
			PE_H10_1_E60_RdFL(hdr_tpg_ctrl_00);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_00,tpg_enable,0);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_00,tpg_type,type);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_00,tpg_grad_en,grad_en)
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_00,tpg_h_grad,h_grad);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_00,tpg_stride,stride);
			PE_H10_1_E60_WrFL(hdr_tpg_ctrl_00);
			OS_MsecSleep(30);

			PE_H10_1_E60_RdFL(hdr_tpg_ctrl_01);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_01,tpg_size_x,size_x);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_01,tpg_size_y,size_y);
			PE_H10_1_E60_WrFL(hdr_tpg_ctrl_01);

			PE_H10_1_E60_RdFL(hdr_tpg_ctrl_02);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_02,tpg_mask_flag,mask_flag);
			PE_H10_1_E60_WrFL(hdr_tpg_ctrl_02);

			PE_H10_1_E60_RdFL(hdr_tpg_ctrl_03);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_03,tpg_in_out_sel,0x0);
			PE_H10_1_E60_WrFL(hdr_tpg_ctrl_03);

			PE_H10_1_E60_RdFL(hdr_tpg_ctrl_04);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_04,tpg_color_r,0x0);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_04,tpg_color_b,0x0);
			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_04,tpg_color_g,0x0);
			PE_H10_1_E60_WrFL(hdr_tpg_ctrl_04);

			PE_H10_1_E60_QWr(hdr_tpg_ia_ctrl,0x00001000);//patch color
			for (i=0; i<num_win; i++)
			{
				wr_data = p->stWinboxInfo.stWinBoxAttr[i].fill_R;
				wr_data |= (p->stWinboxInfo.stWinBoxAttr[i].fill_B << 10);
				wr_data |= (p->stWinboxInfo.stWinBoxAttr[i].fill_G << 20);
				PE_HDR_HW_E60_DBG_PRINT("H10_1[%d]win color:0x%08x\n",i,wr_data);
				PE_H10_1_E60_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_1_E60_QWr(hdr_tpg_ia_ctrl,0x00001020);//patch start (x,y)
			for (i=0; i<num_win; i++)
			{
				wr_data = (p->stWinboxInfo.stWinBoxAttr[i].y*ratio_y)>>10;
				wr_data |= (((p->stWinboxInfo.stWinBoxAttr[i].x*ratio_x)>>10) << 16);
				PE_H10_1_E60_QWr(hdr_tpg_ia_data,wr_data);
				PE_HDR_HW_E60_DBG_PRINT("H10_1[%d]win start:0x%08x\n",i,wr_data);
			}
			PE_H10_1_E60_QWr(hdr_tpg_ia_ctrl,0x00001040);//patch end (x,y)

			for (i=0; i<num_win; i++)
			{
				wr_data = ((p->stWinboxInfo.stWinBoxAttr[i].y + p->stWinboxInfo.stWinBoxAttr[i].h)*ratio_y)>>10;
				wr_data |= ((((p->stWinboxInfo.stWinBoxAttr[i].x + p->stWinboxInfo.stWinBoxAttr[i].w)*ratio_x)>>10) << 16);
				PE_HDR_HW_E60_DBG_PRINT("H10_1[%d]win end  :0x%08x\n",i,wr_data);
				PE_H10_1_E60_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_1_E60_QWr(hdr_tpg_ia_ctrl,0x00001060);//gradation start color
			for (i=0; i<num_grd; i++)
			{
				wr_data = p->stGradInfo.stLineAttr[i].start_R;
				wr_data |= (p->stGradInfo.stLineAttr[i].start_B << 10);
				wr_data |= (p->stGradInfo.stLineAttr[i].start_G << 20);
				PE_HDR_HW_E60_DBG_PRINT("H10_1[%d]grd start:0x%08x\n",i,wr_data);
				PE_H10_1_E60_QWr(hdr_tpg_ia_data,wr_data);
			}
			PE_H10_1_E60_QWr(hdr_tpg_ia_ctrl,0x00001064);//gradation step color
			for (i=0; i<num_grd; i++)
			{
				wr_data = p->stGradInfo.stLineAttr[i].step_R;
				wr_data |= (p->stGradInfo.stLineAttr[i].step_B << 10);
				wr_data |= (p->stGradInfo.stLineAttr[i].step_G << 20);
				PE_HDR_HW_E60_DBG_PRINT("H10_1[%d]grd color:0x%08x\n",i,wr_data);
				PE_H10_1_E60_QWr(hdr_tpg_ia_data,wr_data);
			}
			PE_H10_1_E60_QWr(hdr_tpg_ia_ctrl,0x00001068);//gradation region size
			for (i=0; i<num_grd; i++)
			{
				if (h_grad == 1)
				{
					wr_data = (size_y / num_grd) * (i + 1);
				}
				else
				{
					wr_data = (size_x / num_grd) * (i + 1);
				}
				PE_HDR_HW_E60_DBG_PRINT("H10_1[%d]grd end  :0x%08x\n",i,wr_data);
				PE_H10_1_E60_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_1_E60_Wr01(hdr_tpg_ctrl_00,tpg_enable,enable);
			PE_H10_1_E60_WrFL(hdr_tpg_ctrl_00);

			/* 20191218, 1st csc off during pattern on(SCDCR-2960) */
			/* 20200115, moved to fw(AVTASK-423) */
			//PE_H10_1_E60_QWr01(hdr_csc1_ctrl_00,reg_csc1st_en,(enable>0)? 0:1);
		} while(0);
		OS_MsecSleep(30);
	} while(0);
	return ret;
}

