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

/** @file pe_hdr_hw_o24.c
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

#include "pe_hw_o24.h"
#include "pe_reg_o24.h"
#include "pe_fwi_o24.h"
#include "pe_hdr_hw_o24.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* hdr drv ver, yyyy/mm/dd/hh:mm */
#define PE_HDR_HW_O24_DRV_VER		"2024/04/29/14:24"

#define PE_HDR_HW_O24_BUF_MAX		50

#define PE_HDR_HW_O24_CONNECT_MODE_SDR	(0)
#define PE_HDR_HW_O24_CONNECT_MODE_H10	(1)
#define PE_HDR_HW_O24_CONNECT_MODE_HLG	(2)

#define PE_HDR_DDR_O24_CNT_EOTF		(0)
#define PE_HDR_DDR_O24_CNT_OETF		(1)
#define PE_HDR_DDR_O24_CNT_TONE		(2)
#define PE_HDR_DDR_O24_CNT_YLUT		(3)
#define PE_HDR_DDR_O24_CNT_CCR		(4)
#define PE_HDR_DDR_O24_CNT_PCC		(5)

#define PE_O24_H10_0_BASE			(0xCCC10800)
#define PE_O24_H10_1_BASE			(0xCCC11A00)
#define PE_O24_HDR_VERI_BASE		(0xCCC12100)

#ifdef INCLUDE_KDRV_DE
#define PE_O24_DDR_HDR_BASE			(g_pe_hdr.base)
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_HDR_HW_O24_CHECK_CODE(_checker,_action,fmt,args...) \
	{if(_checker){PE_PRINT_ERROR(fmt,##args);_action;}}

#define PE_HDR_HW_O24_BACKUP_LOG(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		PE_PRINT_NOTI(_fmt, ##args);\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_HDR_HW_O24_SetTraceDataBuf(0,_trace_buf);\
	}

#define PE_HDR_HW_O24_BACKUP_TRACE(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_HDR_HW_O24_SetTraceDataBuf(0,_trace_buf);\
	}

#define PE_HDR_HW_O24_BACKUP_LOG_LUT(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		PE_PRINT_NOTI(_fmt, ##args);\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_HDR_HW_O24_SetTraceDataBuf(1,_trace_buf);\
	}

#define PE_HDR_HW_O24_BACKUP_TRACE_LUT(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_HDR_HW_O24_SetTraceDataBuf(1,_trace_buf);\
	}

#define PE_HDR_HW_O24_CONNECT_TO_STR(_x)		(\
	((_x)==PE_HDR_HW_O24_CONNECT_MODE_SDR)?	"SDR":\
	((_x)==PE_HDR_HW_O24_CONNECT_MODE_H10)?	"H10":\
	((_x)==PE_HDR_HW_O24_CONNECT_MODE_HLG)?	"HLG":\
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
}PE_HDR_HW_O24_TIME_T;

/**
 *	pe trace data buffer type
 */
typedef struct {
	PE_HDR_HW_O24_TIME_T time;		///< time
	char str[PE_TRACE_STR_SIZE];	///< str
}PE_HDR_HW_O24_DATA_BUF_T;

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
PE_HDR_REG_O24_H10_T gPE_H10_0_O24;
PE_HDR_REG_O24_H10_T gPE_H10_1_O24;
PE_HDR_REG_O24_HDR_VERI_T gPE_HDR_VERI_O24;
volatile PE_HDR_DDR_O24_T *gPE_HDR_DDR_O24 = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_HDR_HW_O24_SortTraceDataBuf(UINT32 type, PE_HDR_HW_O24_DATA_BUF_T *dst);
static int PE_HDR_HW_O24_SetTraceDataBuf(UINT32 type, char *data);
static UINT32 PE_HDR_HW_O24_GetConnectMode(UINT32 win_id);
static UINT32 PE_HDR_HW_O24_GetToneConnectMode(UINT32 path);
static UINT32 PE_HDR_HW_O24_IncCount(UINT32 wid, UINT32 type, UINT32 idx);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static UINT32 _g_hdr_hw_o24_trace=0x0;	//default should be off.
static PE_HDR_HW_O24_SETTINGS_T _g_pe_hdr_hw_o24_info;
static PE_HDR_HW_O24_DATA_BUF_T *_gp_pe_hdr_hw_o24_buf_curr = NULL;
static PE_HDR_HW_O24_DATA_BUF_T *_gp_pe_hdr_hw_o24_buf_sort = NULL;
static PE_HDR_HW_O24_DATA_BUF_T *_gp_pe_hdr_hw_o24_lut_buf_curr = NULL;
static PE_HDR_HW_O24_DATA_BUF_T *_gp_pe_hdr_hw_o24_lut_buf_sort = NULL;

static PE_REG_O24_HW_OPT_T _g_pe_hdr_hw_o24_hw_opt = {.u32Data=0,};

/* hlg (20211012) (AVTASK-681), change this if necessary to change default */
const UINT32 _g_hdr_tm_lut_hlg_o24[66] = {
0x00000000,
0x00FF24B9,
0x015DB994,
0x024034F5,
0x02D6CD66,
0x0369FC5E,
0x03E3FED2,
0x06692D0A,
0x08160E38,
0x0A0325BA,
0x0B14B3CD,
0x0F2F4ADE,
0x13957C14,
0x1707A126,
0x1BB0D060,
0x1F8F1232,
0x25F2643F,
0x2B3F8037,
0x31918A34,
0x370BB9AF,
0x3E86C404,
0x43ED281B,
0x5136F46A,
0x59E17FA0,
0x61A7037F,
0x6C129E11,
0x7266CC03,
0x7B2C85B8,
0x8340BA6A,
0x885287E4,
0x94189DAA,
0xA8CB2651,
0xFFFFFFFF,
0x00000000,
0x00000FF9,
0x000012B3,
0x00001801,
0x00001AF5,
0x00001D90,
0x00001F8F,
0x00002883,
0x00002D7F,
0x000032A0,
0x00003543,
0x00003E59,
0x000046CE,
0x00004CC8,
0x00005432,
0x000059E2,
0x0000628F,
0x00006938,
0x000070A5,
0x000076B5,
0x00007E84,
0x000083DE,
0x00009030,
0x000097B0,
0x00009E1C,
0x0000A655,
0x0000AB22,
0x0000B192,
0x0000B74D,
0x0000BACF,
0x0000C2B5,
0x0000CFDF,
0x0000FFFF};

/* h10 (20211012) (AVTASK-681), change this if necessary to change default */
/* h10 (20240429) (SCDCR-4546), update hdr10 tone_y */
const UINT32 _g_hdr_tm_lut_h10_o24[66] = {
0x00000000,
0x00FF24B9,
0x015DB994,
0x024034F5,
0x02D6CD66,
0x0369FC5E,
0x03E3FED2,
0x06692D0A,
0x08160E38,
0x0A0325BA,
0x0B14B3CD,
0x0F2F4ADE,
0x13957C14,
0x1707A126,
0x1BB0D060,
0x1F8F1232,
0x25F2643F,
0x2B3F8037,
0x31918A34,
0x370BB9AF,
0x3E86C404,
0x43ED281B,
0x5136F46A,
0x59E17FA0,
0x61A7037F,
0x6C129E11,
0x7266CC03,
0x7B2C85B8,
0x8340BA6A,
0x885287E4,
0x94189DAA,
0xA8CB2651,
0xFFFFFFFF,
0x00000000,
0x000004E7,
0x000006BB,
0x00000B14,
0x00000DFB,
0x000010CF,
0x00001327,
0x00001EC6,
0x000025DA,
0x00002DC5,
0x00003242,
0x00004353,
0x0000544A,
0x00006289,
0x00007466,
0x00008324,
0x0000986D,
0x0000A795,
0x0000B776,
0x0000C373,
0x0000D2AF,
0x0000DC73,
0x0000F18B,
0x0000FA23,
0x0000FFFF,
0x0000FFFF,
0x0000FFFF,
0x0000FFFF,
0x0000FFFF,
0x0000FFFF,
0x0000FFFF,
0x0000FFFF,
0x0000FFFF};

/* bypass (20211012) (AVTASK-681) */
const UINT32 _g_hdr_tm_lut_bypass_o24[66] = {
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
0xa000a000,
0xa800a800,
0xb000b000,
0xb800b800,
0xc000c000,
0xc800c800,
0xd000d000,
0xd800d800,
0xe000e000,
0xe800e800,
0xf000f000,
0xf800f800,
0xffffffff,
0x00000000,
0x00000800,
0x00001000,
0x00001800,
0x00002000,
0x00002800,
0x00003000,
0x00003800,
0x00004000,
0x00004800,
0x00005000,
0x00005800,
0x00006000,
0x00006800,
0x00007000,
0x00007800,
0x00008000,
0x00008800,
0x00009000,
0x00009800,
0x0000a000,
0x0000a800,
0x0000b000,
0x0000b800,
0x0000c000,
0x0000c800,
0x0000d000,
0x0000d800,
0x0000e000,
0x0000e800,
0x0000f000,
0x0000f800,
0x0000ffff};

/* ygain (20211012) (AVTASK-681), change this if necessary to change default */
const UINT32 _g_hdr_yg_lut_hlg_o24[33] = {
0x00000000,
0x00490664,
0x008906F6,
0x01010794,
0x017407F7,
0x01E30840,
0x02860894,
0x032408D6,
0x03BF090C,
0x048A0949,
0x05840988,
0x06A909C7,
0x07F90A05,
0x09720A40,
0x0B130A79,
0x0CDC0AB0,
0x0EF80AE8,
0x11650B21,
0x144B0B5D,
0x17A60B9A,
0x1B740BD7,
0x1FDB0C14,
0x24D50C51,
0x2A870C8F,
0x313D0CCF,
0x38EC0D10,
0x41B60D51,
0x4BDF0D94,
0x57F20DDA,
0x69AB0E33,
0x85BD0EA8,
0xB32B0F3F,
0xFFFF0FFF};

const UINT32 _g_hdr_yg_lut_bypass_o24[33] = {
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

const UINT16 _g_pe_hdr_hw_o24_csc_mtrx_bypass[PE_NUM_OF_CSC_COEF] = {
0x1000, 0x0000, 0x0000,		//  1.000, 0.000, 0.000
0x0000, 0x1000, 0x0000,		//  0.000, 1.000, 0.000
0x0000, 0x0000, 0x1000};	//  0.000, 0.000, 1.000

const UINT16 _g_pe_hdr_hw_o24_pcc_mtrx_default[PE_NUM_OF_CSC_COEF] = {
0x121f, 0x7fde, 0x7e02,		//   1.1326, -0.0083, -0.1245,
0x7e65, 0x11e5, 0x7fb6,		//  -0.1003, 1.1184, -0.0181,
0x769a, 0x7ed6, 0x1a8f};	//  -0.5874, -0.0728, 1.6599,

/*========================================================================================
	Implementation Group
========================================================================================*/
static int PE_HDR_HW_O24_SortTraceDataBuf(UINT32 type, PE_HDR_HW_O24_DATA_BUF_T *dst)
{
	int ret = RET_OK;
	UINT32 size=0, i=0, max=0;
	UINT32 j=0, s0=0, s1=0, us0=0, us1=0;
	PE_HDR_HW_O24_DATA_BUF_T temp;
	PE_HDR_HW_O24_DATA_BUF_T *src;

	do{
		CHECK_KNULL(dst);
		if (type == 1)	src = _gp_pe_hdr_hw_o24_lut_buf_curr;
		else			src = _gp_pe_hdr_hw_o24_buf_curr;
		if (src == NULL)	{ret = RET_ERROR;	break;}
		max = PE_HDR_HW_O24_BUF_MAX;
		size = sizeof(PE_HDR_HW_O24_DATA_BUF_T);
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

int PE_HDR_HW_O24_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0, type=0;
	PE_HDR_HW_O24_DATA_BUF_T *p_buf;
	UINT32 *p_data = NULL;
	PE_HDR_HW_O24_TIME_T *p_time = NULL;
	char *p_str = NULL;

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		type = pstParams->data[0];
		if (type == 1)	p_buf = _gp_pe_hdr_hw_o24_lut_buf_sort;
		else			p_buf = _gp_pe_hdr_hw_o24_buf_sort;
		if (p_buf == NULL)	{ret = RET_ERROR;	break;}
		rd_cnt = pstParams->oper;
		if (rd_cnt<PE_HDR_HW_O24_BUF_MAX)
		{
			if(rd_cnt==0)
			{
				ret = PE_HDR_HW_O24_SortTraceDataBuf(type,p_buf);
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

static int PE_HDR_HW_O24_SetTraceDataBuf(UINT32 type, char *data)
{
    int ret = RET_OK;
	UINT32 i = 0;
	char *p_str = NULL;
	PE_HDR_HW_O24_TIME_T *p_time = NULL;
	static UINT32 cnt = 0;
	PE_HDR_HW_O24_DATA_BUF_T *p_buf;
	do{
		CHECK_KNULL(data);
		if (type == 1)	p_buf = _gp_pe_hdr_hw_o24_lut_buf_curr;
		else			p_buf = _gp_pe_hdr_hw_o24_buf_curr;
		if (p_buf == NULL)	{ret = RET_ERROR;	break;}
		if(cnt>=PE_HDR_HW_O24_BUF_MAX)	cnt = 0;
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

static UINT32 PE_HDR_HW_O24_GetConnectMode(UINT32 win_id)
{
	UINT32 mode;
	LX_PE_HDR_OP_MD_T op;

	if (win_id >= LX_PE_WIN_NUM)	return 0;

	op.udata32 = _g_pe_hdr_hw_o24_info.md_inf[win_id].data[0];//get info of each wid (AVTASK-681)

	if (op.connect == 2)		mode = PE_HDR_HW_O24_CONNECT_MODE_H10;
	else if (op.connect == 5)	mode = PE_HDR_HW_O24_CONNECT_MODE_HLG;
	else						mode = PE_HDR_HW_O24_CONNECT_MODE_SDR;

	return mode;
}

static UINT32 PE_HDR_HW_O24_GetToneConnectMode(UINT32 path)
{
	UINT32 mode;
	if (path == 2)			mode = PE_HDR_HW_O24_CONNECT_MODE_H10;
	else if (path == 5)		mode = PE_HDR_HW_O24_CONNECT_MODE_HLG;
	else					mode = PE_HDR_HW_O24_CONNECT_MODE_SDR;
	return mode;
}

static UINT32 PE_HDR_HW_O24_IncCount(UINT32 wid, UINT32 type, UINT32 idx)
{
	UINT32 count = 0;

	if (type == PE_HDR_DDR_O24_CNT_EOTF || type == PE_HDR_DDR_O24_CNT_OETF) {
		PE_HDR_DDR_CNT0_O24_T cnt;

		rmb();
		if (wid == 0) {
			cnt.udata32 = gPE_HDR_DDR_O24->head.cnt00.udata32;
		}
		else {
			cnt.udata32 = gPE_HDR_DDR_O24->head.cnt10.udata32;
		}

		if (type == PE_HDR_DDR_O24_CNT_EOTF) {
			if (idx == 0)		count = cnt.eotf_0 = (cnt.eotf_0 == 0xf)? 1:(cnt.eotf_0+1);
			else if (idx == 1)	count = cnt.eotf_1 = (cnt.eotf_1 == 0xf)? 1:(cnt.eotf_1+1);
			else if (idx == 2)	count = cnt.eotf_2 = (cnt.eotf_2 == 0xf)? 1:(cnt.eotf_2+1);
			else				count = cnt.eotf_3 = (cnt.eotf_3 == 0xf)? 1:(cnt.eotf_3+1);
		}
		else {
			if (idx == 0)		count = cnt.oetf_0 = (cnt.oetf_0 == 0xf)? 1:(cnt.oetf_0+1);
			else if (idx == 1)	count = cnt.oetf_1 = (cnt.oetf_1 == 0xf)? 1:(cnt.oetf_1+1);
			else if (idx == 2)	count = cnt.oetf_2 = (cnt.oetf_2 == 0xf)? 1:(cnt.oetf_2+1);
			else				count = cnt.oetf_3 = (cnt.oetf_3 == 0xf)? 1:(cnt.oetf_3+1);
		}

		wmb();
		if (wid == 0) {
			gPE_HDR_DDR_O24->head.cnt00.udata32 = cnt.udata32;
		}
		else {
			gPE_HDR_DDR_O24->head.cnt10.udata32 = cnt.udata32;
		}
		wmb();
	}
	else if (type == PE_HDR_DDR_O24_CNT_TONE || type == PE_HDR_DDR_O24_CNT_YLUT) {
		PE_HDR_DDR_CNT1_O24_T cnt;

		rmb();
		if (wid == 0) {
			cnt.udata32 = gPE_HDR_DDR_O24->head.cnt01.udata32;
		}
		else {
			cnt.udata32 = gPE_HDR_DDR_O24->head.cnt11.udata32;
		}

		if (type == PE_HDR_DDR_O24_CNT_TONE) {
			if (idx == 0)		count = cnt.tone_0 = (cnt.tone_0 == 0xf)? 1:(cnt.tone_0+1);
			else if (idx == 1)	count = cnt.tone_1 = (cnt.tone_1 == 0xf)? 1:(cnt.tone_1+1);
			else if (idx == 2)	count = cnt.tone_2 = (cnt.tone_2 == 0xf)? 1:(cnt.tone_2+1);
			else if (idx == 3)	count = cnt.tone_3 = (cnt.tone_3 == 0xf)? 1:(cnt.tone_3+1);
			else if (idx == 4)	count = cnt.tone_4 = (cnt.tone_4 == 0xf)? 1:(cnt.tone_4+1);
			else				count = cnt.tone_5 = (cnt.tone_5 == 0xf)? 1:(cnt.tone_5+1);
		}
		else {
			if (idx == 0)		count = cnt.ylut_0 = (cnt.ylut_0 == 0xf)? 1:(cnt.ylut_0+1);
			else				count = cnt.ylut_1 = (cnt.ylut_1 == 0xf)? 1:(cnt.ylut_1+1);
		}

		wmb();
		if (wid == 0) {
			gPE_HDR_DDR_O24->head.cnt01.udata32 = cnt.udata32;
		}
		else {
			gPE_HDR_DDR_O24->head.cnt11.udata32 = cnt.udata32;
		}
		wmb();
	}
	else if (type == PE_HDR_DDR_O24_CNT_CCR || type == PE_HDR_DDR_O24_CNT_PCC) {
		PE_HDR_DDR_CNT2_O24_T cnt;

		rmb();
		if (wid == 0) {
			cnt.udata32 = gPE_HDR_DDR_O24->head.cnt02.udata32;
		}
		else {
			cnt.udata32 = gPE_HDR_DDR_O24->head.cnt12.udata32;
		}

		if (type == PE_HDR_DDR_O24_CNT_CCR) {
			count = cnt.ccr_0 = (cnt.ccr_0 == 0xf)? 1:(cnt.ccr_0+1);
		}
		else {
			count = cnt.pcc_0 = (cnt.pcc_0 == 0xf)? 1:(cnt.pcc_0+1);
		}

		wmb();
		if (wid == 0) {
			gPE_HDR_DDR_O24->head.cnt02.udata32 = cnt.udata32;
		}
		else {
			gPE_HDR_DDR_O24->head.cnt12.udata32 = cnt.udata32;
		}
		wmb();
	}
	else
	{
		count = 0;
	}

	return count;
}

int PE_HDR_HW_O24_InitPhyToVirt(void)
{
	int ret = RET_OK;

	gPE_H10_0_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_O24_REG_H10_T));
	gPE_H10_1_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_O24_REG_H10_T));
	gPE_H10_0_O24.phys.addr = (volatile UINT32 *)ioremap(PE_O24_H10_0_BASE,sizeof(PE_O24_REG_H10_T));
	gPE_H10_1_O24.phys.addr = (volatile UINT32 *)ioremap(PE_O24_H10_1_BASE,sizeof(PE_O24_REG_H10_T));
	#ifdef INCLUDE_KDRV_DE
	gPE_HDR_DDR_O24 = (volatile PE_HDR_DDR_O24_T *)vmap_phys(PE_O24_DDR_HDR_BASE,sizeof(PE_HDR_DDR_O24_T));
	#endif

	gPE_HDR_VERI_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_O24_REG_HDR_VERI_T));
	gPE_HDR_VERI_O24.phys.addr = (volatile UINT32 *)ioremap(PE_O24_HDR_VERI_BASE,sizeof(PE_O24_REG_HDR_VERI_T));

	PE_PRINT_NOTI("done\n");

	return ret;
}

int PE_HDR_HW_O24_FreePhyToVirt(void)
{
	int ret = RET_OK;

	if (gPE_H10_0_O24.shdw.addr) OS_Free((void *)gPE_H10_0_O24.shdw.addr);
	if (gPE_H10_1_O24.shdw.addr) OS_Free((void *)gPE_H10_1_O24.shdw.addr);
	if (gPE_H10_0_O24.phys.addr) iounmap((void *)gPE_H10_0_O24.phys.addr);
	if (gPE_H10_1_O24.phys.addr) iounmap((void *)gPE_H10_1_O24.phys.addr);
	#ifdef INCLUDE_KDRV_DE
	if (gPE_HDR_DDR_O24) vunmap_phys((void *)gPE_HDR_DDR_O24);
	#endif

	if (gPE_HDR_VERI_O24.shdw.addr) OS_Free((void *)gPE_HDR_VERI_O24.shdw.addr);
	if (gPE_HDR_VERI_O24.phys.addr) iounmap((void *)gPE_HDR_VERI_O24.phys.addr);

	PE_PRINT_NOTI("done\n");

	return ret;
}

int PE_HDR_HW_O24_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, size, cnt;
	PE_CFG_CTRL_T stParams;
	PE_HDR_HW_O24_SETTINGS_T *pInfo = &_g_pe_hdr_hw_o24_info;

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);

		_g_pe_hdr_hw_o24_hw_opt = PE_REG_O24_GetDispOpt();

		if (pstParams->resume_mode == 2) {
			stParams.resume_mode = 0;//force normal
		}
		else if (pstParams->resume_mode == 1) {
			rmb();
			if (gPE_HDR_DDR_O24->head.info.version == PE_HDR_DDR_O24_VERSION) {
				stParams.resume_mode = 1;
			}
			else {
				stParams.resume_mode = 0;//force normal
			}
			rmb();
		}
		else {
			stParams.resume_mode = 0;//normal
		}

		size = sizeof(PE_HDR_HW_O24_DATA_BUF_T)*PE_HDR_HW_O24_BUF_MAX;
		if (_gp_pe_hdr_hw_o24_buf_curr==NULL)
		{
			_gp_pe_hdr_hw_o24_buf_curr = (PE_HDR_HW_O24_DATA_BUF_T *)OS_Malloc(size);
			memset(_gp_pe_hdr_hw_o24_buf_curr, 0, size);
		}
		if (_gp_pe_hdr_hw_o24_buf_sort==NULL)
		{
			_gp_pe_hdr_hw_o24_buf_sort = (PE_HDR_HW_O24_DATA_BUF_T *)OS_Malloc(size);
			memset(_gp_pe_hdr_hw_o24_buf_sort, 0, size);
		}
		if (_gp_pe_hdr_hw_o24_lut_buf_curr==NULL)
		{
			_gp_pe_hdr_hw_o24_lut_buf_curr = (PE_HDR_HW_O24_DATA_BUF_T *)OS_Malloc(size);
			memset(_gp_pe_hdr_hw_o24_lut_buf_curr, 0, size);
		}
		if (_gp_pe_hdr_hw_o24_lut_buf_sort==NULL)
		{
			_gp_pe_hdr_hw_o24_lut_buf_sort = (PE_HDR_HW_O24_DATA_BUF_T *)OS_Malloc(size);
			memset(_gp_pe_hdr_hw_o24_lut_buf_sort, 0, size);
		}

		PE_HDR_HW_O24_BACKUP_LOG("[HW_O24Init]start(resume:%d(%d))(ext:%d)(%s)",stParams.resume_mode,\
			pstParams->resume_mode,_g_pe_hdr_hw_o24_hw_opt.external_chip,PE_HDR_HW_O24_DRV_VER);

		if (stParams.resume_mode == 0)	//normal init
		{
			PE_HDR_DDR_POS_O24_T pos;
			memset(pInfo->md_inf,0,sizeof(LX_PE_HDR_MODE_INFO_T)*LX_PE_WIN_NUM);
			wmb();
			memset((void *)(gPE_HDR_DDR_O24),0,sizeof(PE_HDR_DDR_O24_T));
			wmb();
			gPE_HDR_DDR_O24->head.info.version = PE_HDR_DDR_O24_VERSION;

			/* pos0 */
			pos.ofst = sizeof(PE_HDR_DDR_H_O24_T);
			size = sizeof(UINT32)*1024;
			gPE_HDR_DDR_O24->head.pos0[0].udata32  = pos.udata32;//pos0.eotf_0
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[1].udata32  = pos.udata32;//pos0.eotf_1
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[2].udata32  = pos.udata32;//pos0.eotf_2
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[3].udata32  = pos.udata32;//pos0.eotf_3
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[4].udata32  = pos.udata32;//pos0.oetf_0
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[5].udata32  = pos.udata32;//pos0.oetf_1
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[6].udata32  = pos.udata32;//pos0.oetf_2
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[7].udata32  = pos.udata32;//pos0.oetf_3

			pos.ofst += size;
			size = sizeof(UINT32)*198;
			gPE_HDR_DDR_O24->head.pos0[8].udata32  = pos.udata32;//pos0.tone_0
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[9].udata32  = pos.udata32;//pos0.tone_1
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[10].udata32 = pos.udata32;//pos0.tone_2
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[11].udata32 = pos.udata32;//pos0.tone_3
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[12].udata32 = pos.udata32;//pos0.tone_4
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[13].udata32 = pos.udata32;//pos0.tone_5

			pos.ofst += size;
			size = sizeof(UINT32)*33;
			gPE_HDR_DDR_O24->head.pos0[14].udata32 = pos.udata32;//pos0.ylut_0
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos0[15].udata32 = pos.udata32;//pos0.ylut_1

			pos.ofst += size;
			size = sizeof(UINT32)*30;
			gPE_HDR_DDR_O24->head.pos0[16].udata32 = pos.udata32;//pos0.ccr_0
			pos.ofst += size;
			size = sizeof(UINT32)*10;
			gPE_HDR_DDR_O24->head.pos0[17].udata32 = pos.udata32;//pos0.pcc_0

			/* pos1 */
			pos.ofst += size;
			size = sizeof(UINT32)*1024;
			gPE_HDR_DDR_O24->head.pos1[0].udata32  = pos.udata32;//pos1.eotf_0
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[1].udata32  = pos.udata32;//pos1.eotf_1
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[2].udata32  = pos.udata32;//pos1.eotf_2
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[3].udata32  = pos.udata32;//pos1.eotf_3
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[4].udata32  = pos.udata32;//pos1.oetf_0
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[5].udata32  = pos.udata32;//pos1.oetf_1
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[6].udata32  = pos.udata32;//pos1.oetf_2
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[7].udata32  = pos.udata32;//pos1.oetf_3

			pos.ofst += size;
			size = sizeof(UINT32)*198;
			gPE_HDR_DDR_O24->head.pos1[8].udata32  = pos.udata32;//pos1.tone_0
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[9].udata32  = pos.udata32;//pos1.tone_1
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[10].udata32 = pos.udata32;//pos1.tone_2
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[11].udata32 = pos.udata32;//pos1.tone_3
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[12].udata32 = pos.udata32;//pos1.tone_4
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[13].udata32 = pos.udata32;//pos1.tone_5

			pos.ofst += size;
			size = sizeof(UINT32)*33;
			gPE_HDR_DDR_O24->head.pos1[14].udata32 = pos.udata32;//pos1.ylut_0
			pos.ofst += size;
			gPE_HDR_DDR_O24->head.pos1[15].udata32 = pos.udata32;//pos1.ylut_1

			pos.ofst += size;
			size = sizeof(UINT32)*30;
			gPE_HDR_DDR_O24->head.pos1[16].udata32 = pos.udata32;//pos1.ccr_0
			pos.ofst += size;
			size = sizeof(UINT32)*10;
			gPE_HDR_DDR_O24->head.pos1[17].udata32 = pos.udata32;//pos1.pcc_0

			/* reserved */
			size += sizeof(PE_HDR_DDR_RSVD_O24_T);

			/* histogram */
			pos.ofst += size;
			size = sizeof(UINT32);//hist_cnt
			size += sizeof(UINT32)*128*3;
			gPE_HDR_DDR_O24->head.pos0[24].udata32 = pos.udata32;//pos0.hist
			pos.ofst += size;
			size = sizeof(UINT32);//hist_cnt
			size += sizeof(UINT32)*128*3;
			gPE_HDR_DDR_O24->head.pos1[24].udata32 = pos.udata32;//pos1.hist

			/* TONE : 0:HLG, 1:HDR10, 2:SDR, 3~5:reserved */
			for (i=0; i<66; i++)
			{
				gPE_HDR_DDR_O24->lut0.tone_0[i]     = _g_hdr_tm_lut_hlg_o24[i];
				gPE_HDR_DDR_O24->lut0.tone_0[i+66]  = _g_hdr_tm_lut_hlg_o24[i];
				gPE_HDR_DDR_O24->lut0.tone_0[i+132] = _g_hdr_tm_lut_hlg_o24[i];
				gPE_HDR_DDR_O24->lut0.tone_1[i]     = _g_hdr_tm_lut_h10_o24[i];
				gPE_HDR_DDR_O24->lut0.tone_1[i+66]  = _g_hdr_tm_lut_h10_o24[i];
				gPE_HDR_DDR_O24->lut0.tone_1[i+132] = _g_hdr_tm_lut_h10_o24[i];
				gPE_HDR_DDR_O24->lut0.tone_2[i]     = _g_hdr_tm_lut_bypass_o24[i];
				gPE_HDR_DDR_O24->lut0.tone_2[i+66]  = _g_hdr_tm_lut_bypass_o24[i];
				gPE_HDR_DDR_O24->lut0.tone_2[i+132] = _g_hdr_tm_lut_bypass_o24[i];

				gPE_HDR_DDR_O24->lut1.tone_0[i]     = _g_hdr_tm_lut_hlg_o24[i];
				gPE_HDR_DDR_O24->lut1.tone_0[i+66]  = _g_hdr_tm_lut_hlg_o24[i];
				gPE_HDR_DDR_O24->lut1.tone_0[i+132] = _g_hdr_tm_lut_hlg_o24[i];
				gPE_HDR_DDR_O24->lut1.tone_1[i]     = _g_hdr_tm_lut_h10_o24[i];
				gPE_HDR_DDR_O24->lut1.tone_1[i+66]  = _g_hdr_tm_lut_h10_o24[i];
				gPE_HDR_DDR_O24->lut1.tone_1[i+132] = _g_hdr_tm_lut_h10_o24[i];
				gPE_HDR_DDR_O24->lut1.tone_2[i]     = _g_hdr_tm_lut_bypass_o24[i];
				gPE_HDR_DDR_O24->lut1.tone_2[i+66]  = _g_hdr_tm_lut_bypass_o24[i];
				gPE_HDR_DDR_O24->lut1.tone_2[i+132] = _g_hdr_tm_lut_bypass_o24[i];
			}

			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_0,PE_HDR_DDR_O24_CNT_TONE,0);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_0,PE_HDR_DDR_O24_CNT_TONE,1);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_0,PE_HDR_DDR_O24_CNT_TONE,2);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_1,PE_HDR_DDR_O24_CNT_TONE,0);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_1,PE_HDR_DDR_O24_CNT_TONE,1);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_1,PE_HDR_DDR_O24_CNT_TONE,2);
			wmb();
			PE_HDR_HW_O24_BACKUP_LOG_LUT("[HW_O24Init] TONE init done (cnt:%d)",cnt);

			/* YLUT : 0:HLG, 1:reserved */
			for (i=0; i<33; i++)
			{
				gPE_HDR_DDR_O24->lut0.ylut_0[i] = _g_hdr_yg_lut_hlg_o24[i];
				gPE_HDR_DDR_O24->lut0.ylut_1[i] = _g_hdr_yg_lut_bypass_o24[i];

				gPE_HDR_DDR_O24->lut1.ylut_0[i] = _g_hdr_yg_lut_hlg_o24[i];
				gPE_HDR_DDR_O24->lut1.ylut_1[i] = _g_hdr_yg_lut_bypass_o24[i];
			}

			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_0,PE_HDR_DDR_O24_CNT_YLUT,0);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_0,PE_HDR_DDR_O24_CNT_YLUT,1);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_1,PE_HDR_DDR_O24_CNT_YLUT,0);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_1,PE_HDR_DDR_O24_CNT_YLUT,1);
			wmb();

			/* (AVTASK-681), change this if necessary to change default */
			pInfo->reg_hue_prsv_en = 0x1;
			pInfo->reg_sat_prsv_en = 0x1;
			pInfo->reg_hue_prsv_ratio = 0x200;
			pInfo->reg_sat_prsv_ratio = 0x0;
			pInfo->lgain_lut[0] = 0x000000FF;
			pInfo->lgain_lut[1] = 0x249200FF;
			pInfo->lgain_lut[2] = 0x492400FF;
			pInfo->lgain_lut[3] = 0x6DB600FF;
			pInfo->lgain_lut[4] = 0x924900FF;
			pInfo->lgain_lut[5] = 0xB6DB00FF;
			pInfo->lgain_lut[6] = 0xDB6D00FF;
			pInfo->lgain_lut[7] = 0xFFFF00FF;
			pInfo->sgain_lut[0] = 0x000000FF;
			pInfo->sgain_lut[1] = 0x249200FF;
			pInfo->sgain_lut[2] = 0x492400FF;
			pInfo->sgain_lut[3] = 0x6DB600FF;
			pInfo->sgain_lut[4] = 0x924900FF;
			pInfo->sgain_lut[5] = 0xB6DB00FF;
			pInfo->sgain_lut[6] = 0xDB6D00FF;
			pInfo->sgain_lut[7] = 0xFFFF00FF;

			/* CCR */
			do {
				PE_O24_REG_H10_HUE_SAT_CTRL_T hdr_hue_sat_ctrl;
				hdr_hue_sat_ctrl.udata32 = 0;
				hdr_hue_sat_ctrl.reg_hue_prsv_en = pInfo->reg_hue_prsv_en;
				hdr_hue_sat_ctrl.reg_sat_prsv_en = pInfo->reg_sat_prsv_en;
				hdr_hue_sat_ctrl.reg_hue_prsv_ratio = pInfo->reg_hue_prsv_ratio;
				hdr_hue_sat_ctrl.reg_sat_prsv_ratio = pInfo->reg_sat_prsv_ratio;
				gPE_HDR_DDR_O24->lut0.ccr_0[0]  = hdr_hue_sat_ctrl.udata32;
				gPE_HDR_DDR_O24->lut1.ccr_0[0]  = hdr_hue_sat_ctrl.udata32;

				gPE_HDR_DDR_O24->lut0.ccr_0[1]  = pInfo->lgain_lut[0];
				gPE_HDR_DDR_O24->lut0.ccr_0[2]  = pInfo->lgain_lut[1];
				gPE_HDR_DDR_O24->lut0.ccr_0[3]  = pInfo->lgain_lut[2];
				gPE_HDR_DDR_O24->lut0.ccr_0[4]  = pInfo->lgain_lut[3];
				gPE_HDR_DDR_O24->lut0.ccr_0[5]  = pInfo->lgain_lut[4];
				gPE_HDR_DDR_O24->lut0.ccr_0[6]  = pInfo->lgain_lut[5];
				gPE_HDR_DDR_O24->lut0.ccr_0[7]  = pInfo->lgain_lut[6];
				gPE_HDR_DDR_O24->lut0.ccr_0[8]  = pInfo->lgain_lut[7];
				gPE_HDR_DDR_O24->lut0.ccr_0[9]  = pInfo->sgain_lut[0];
				gPE_HDR_DDR_O24->lut0.ccr_0[10] = pInfo->sgain_lut[1];
				gPE_HDR_DDR_O24->lut0.ccr_0[11] = pInfo->sgain_lut[2];
				gPE_HDR_DDR_O24->lut0.ccr_0[12] = pInfo->sgain_lut[3];
				gPE_HDR_DDR_O24->lut0.ccr_0[13] = pInfo->sgain_lut[4];
				gPE_HDR_DDR_O24->lut0.ccr_0[14] = pInfo->sgain_lut[5];
				gPE_HDR_DDR_O24->lut0.ccr_0[15] = pInfo->sgain_lut[6];
				gPE_HDR_DDR_O24->lut0.ccr_0[16] = pInfo->sgain_lut[7];

				gPE_HDR_DDR_O24->lut1.ccr_0[1]  = pInfo->lgain_lut[0];
				gPE_HDR_DDR_O24->lut1.ccr_0[2]  = pInfo->lgain_lut[1];
				gPE_HDR_DDR_O24->lut1.ccr_0[3]  = pInfo->lgain_lut[2];
				gPE_HDR_DDR_O24->lut1.ccr_0[4]  = pInfo->lgain_lut[3];
				gPE_HDR_DDR_O24->lut1.ccr_0[5]  = pInfo->lgain_lut[4];
				gPE_HDR_DDR_O24->lut1.ccr_0[6]  = pInfo->lgain_lut[5];
				gPE_HDR_DDR_O24->lut1.ccr_0[7]  = pInfo->lgain_lut[6];
				gPE_HDR_DDR_O24->lut1.ccr_0[8]  = pInfo->lgain_lut[7];
				gPE_HDR_DDR_O24->lut1.ccr_0[9]  = pInfo->sgain_lut[0];
				gPE_HDR_DDR_O24->lut1.ccr_0[10] = pInfo->sgain_lut[1];
				gPE_HDR_DDR_O24->lut1.ccr_0[11] = pInfo->sgain_lut[2];
				gPE_HDR_DDR_O24->lut1.ccr_0[12] = pInfo->sgain_lut[3];
				gPE_HDR_DDR_O24->lut1.ccr_0[13] = pInfo->sgain_lut[4];
				gPE_HDR_DDR_O24->lut1.ccr_0[14] = pInfo->sgain_lut[5];
				gPE_HDR_DDR_O24->lut1.ccr_0[15] = pInfo->sgain_lut[6];
				gPE_HDR_DDR_O24->lut1.ccr_0[16] = pInfo->sgain_lut[7];
			} while(0);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_0,PE_HDR_DDR_O24_CNT_CCR,0);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_1,PE_HDR_DDR_O24_CNT_CCR,0);
			wmb();

			/* PCC */
			do {
				const UINT16 *p_pcc = _g_pe_hdr_hw_o24_csc_mtrx_bypass;

				gPE_HDR_DDR_O24->lut0.pcc_0[0] = (p_pcc[0]<<16)|p_pcc[1];
				gPE_HDR_DDR_O24->lut0.pcc_0[1] = (p_pcc[2]<<16)|p_pcc[3];
				gPE_HDR_DDR_O24->lut0.pcc_0[2] = (p_pcc[4]<<16)|p_pcc[5];
				gPE_HDR_DDR_O24->lut0.pcc_0[3] = (p_pcc[6]<<16)|p_pcc[7];
				gPE_HDR_DDR_O24->lut0.pcc_0[4] = (p_pcc[8]<<16);

				gPE_HDR_DDR_O24->lut1.pcc_0[0] = (p_pcc[0]<<16)|p_pcc[1];
				gPE_HDR_DDR_O24->lut1.pcc_0[1] = (p_pcc[2]<<16)|p_pcc[3];
				gPE_HDR_DDR_O24->lut1.pcc_0[2] = (p_pcc[4]<<16)|p_pcc[5];
				gPE_HDR_DDR_O24->lut1.pcc_0[3] = (p_pcc[6]<<16)|p_pcc[7];
				gPE_HDR_DDR_O24->lut1.pcc_0[4] = (p_pcc[8]<<16);
			} while(0);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_0,PE_HDR_DDR_O24_CNT_PCC,0);
			cnt = PE_HDR_HW_O24_IncCount(LX_PE_WIN_1,PE_HDR_DDR_O24_CNT_PCC,0);
			wmb();
		}

		#if 0	/* O24F22_APB */
		do {
			const UINT16 *p_pcc = _g_pe_hdr_hw_o24_csc_mtrx_bypass;

			if (!gPE_CHPI_DDR_O24)	break;
			if (stParams.resume_mode == 1)	break;//if qsm,skip

			/* addr */
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_hue_sat_ctrl.uaddr32,0xF10008D0);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_00.uaddr32,0xF1000B60);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_01.uaddr32,0xF1000B64);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_02.uaddr32,0xF1000B68);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_03.uaddr32,0xF1000B6C);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_04.uaddr32,0xF1000B70);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_05.uaddr32,0xF1000B74);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_06.uaddr32,0xF1000B78);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_07.uaddr32,0xF1000B7C);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_00.uaddr32,0xF1000B80);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_01.uaddr32,0xF1000B84);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_02.uaddr32,0xF1000B88);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_03.uaddr32,0xF1000B8C);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_04.uaddr32,0xF1000B90);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_05.uaddr32,0xF1000B94);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_06.uaddr32,0xF1000B98);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_07.uaddr32,0xF1000B9C);

			PE_CHPI_APB0_O24F22_QWr(pcc.hdr_pcc_ctrl_01.uaddr32,0xF10008A4);
			PE_CHPI_APB0_O24F22_QWr(pcc.hdr_pcc_ctrl_02.uaddr32,0xF10008A8);
			PE_CHPI_APB0_O24F22_QWr(pcc.hdr_pcc_ctrl_03.uaddr32,0xF10008AC);
			PE_CHPI_APB0_O24F22_QWr(pcc.hdr_pcc_ctrl_04.uaddr32,0xF10008B0);
			PE_CHPI_APB0_O24F22_QWr(pcc.hdr_pcc_ctrl_05.uaddr32,0xF10008B4);

			/* init */
			PE_CHPI_APB0_O24F22_Wr(hs.hdr_hue_sat_ctrl.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(hs.hdr_hue_sat_ctrl.reg_hue_prsv_en,pInfo->reg_hue_prsv_en);
			PE_CHPI_APB0_O24F22_Wr(hs.hdr_hue_sat_ctrl.reg_sat_prsv_en,pInfo->reg_sat_prsv_en);
			PE_CHPI_APB0_O24F22_Wr(hs.hdr_hue_sat_ctrl.reg_hue_prsv_ratio,pInfo->reg_hue_prsv_ratio);
			PE_CHPI_APB0_O24F22_Wr(hs.hdr_hue_sat_ctrl.reg_sat_prsv_ratio,pInfo->reg_sat_prsv_ratio);
			PE_CHPI_APB0_O24F22_WrFL(hs.hdr_hue_sat_ctrl.udata32);

			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_00.udata32,pInfo->lgain_lut[0]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_01.udata32,pInfo->lgain_lut[1]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_02.udata32,pInfo->lgain_lut[2]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_03.udata32,pInfo->lgain_lut[3]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_04.udata32,pInfo->lgain_lut[4]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_05.udata32,pInfo->lgain_lut[5]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_06.udata32,pInfo->lgain_lut[6]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_07.udata32,pInfo->lgain_lut[7]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_00.udata32,pInfo->sgain_lut[0]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_01.udata32,pInfo->sgain_lut[1]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_02.udata32,pInfo->sgain_lut[2]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_03.udata32,pInfo->sgain_lut[3]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_04.udata32,pInfo->sgain_lut[4]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_05.udata32,pInfo->sgain_lut[5]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_06.udata32,pInfo->sgain_lut[6]);
			PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_07.udata32,pInfo->sgain_lut[7]);

			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_01.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_01.r_pcc_coef0,GET_BITS(p_pcc[0],0,16));
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_01.r_pcc_coef1,GET_BITS(p_pcc[1],0,16));
			PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_01.udata32);
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_02.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_02.r_pcc_coef2,GET_BITS(p_pcc[2],0,16));
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_02.r_pcc_coef3,GET_BITS(p_pcc[3],0,16));
			PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_02.udata32);
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_03.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_03.r_pcc_coef4,GET_BITS(p_pcc[4],0,16));
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_03.r_pcc_coef5,GET_BITS(p_pcc[5],0,16));
			PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_03.udata32);
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_04.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_04.r_pcc_coef6,GET_BITS(p_pcc[6],0,16));
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_04.r_pcc_coef7,GET_BITS(p_pcc[7],0,16));
			PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_04.udata32);
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_05.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_05.r_pcc_coef8,GET_BITS(p_pcc[8],0,16));
			PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_05.udata32);

			/* header */
			PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_HS);
			PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_PCC);

			PE_INF_HW_O24_BACKUP_CHPI0("[APB][HDR]done(resume:%d(%d))",stParams.resume_mode,pstParams->resume_mode);
		} while(0);
		/* inform load db done *//* O24F22_APB */
		do {
			UINT32 load_data[5];
			__attribute__((unused)) UINT32 load_size;

			if (!gPE_CHPI_DDR_O24)	break;

			load_data[0] = PE_O24_DDR_DB1_BASE;
			load_data[1] = sizeof(PE_HDR_DDR_O24_T);
			load_data[2] = 2;
			load_data[3] = (1&0xf);//buf num
			load_data[4] = PE_CHPI_APB_O24F22_OFST1;
			load_size = (UINT32)(sizeof(UINT32)*5);
			ret = PE_FWI_O24_LoadDbDone(load_data,load_size);
			PE_HDR_HW_O24_CHECK_CODE(ret,break,"PE_FWI_O24_LoadDbDone() error\n");
			PE_HDR_HW_O24_BACKUP_LOG("[HW_O24Init]LoadDbDone(0x%08x)(%d)(%d)(%d)(0x%08x)(size:%d)",load_data[0],load_data[1],load_data[2],load_data[3],load_data[4],load_size);
		} while(0);
		#endif
		PE_HDR_HW_O24_BACKUP_LOG("[HW_O24Init]done");
	} while(0);

	return ret;
}

int PE_HDR_HW_O24_SetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, count=0, connect;
	do {
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);
		PE_HDR_HW_O24_CHECK_CODE((pstParams->size!=198),break,"size(%d) is wrong\n",pstParams->size);
		PE_DBG_HDR("[wid:%d] oper:0x%x, size:%d\n",pstParams->win_id,pstParams->oper,pstParams->size);

		//operation, [11:8]version [7:4]ctrl [3:0]hdrpath
		connect = PE_HDR_HW_O24_GetToneConnectMode(pstParams->oper&0xf);

		if (pstParams->win_id == LX_PE_WIN_0)
		{
			do {
				/* TONE : 0:HLG, 1:HDR10, 2:SDR, 3~5:reserved */
				if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
				{
					wmb();
					for (i=0; i<198; i++)
					{
						gPE_HDR_DDR_O24->lut0.tone_0[i] = pstParams->data[i];
					}
					wmb();
					count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_TONE,0);
				}
				else if (connect == PE_HDR_HW_O24_CONNECT_MODE_H10)
				{
					wmb();
					for (i=0; i<198; i++)
					{
						gPE_HDR_DDR_O24->lut0.tone_1[i] = pstParams->data[i];
					}
					wmb();
					count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_TONE,1);
				}
				else
				{
					wmb();
					for (i=0; i<198; i++)
					{
						gPE_HDR_DDR_O24->lut0.tone_2[i] = pstParams->data[i];
					}
					wmb();
					count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_TONE,2);
				}
			} while(0);
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			do {
				/* TONE : 0:HLG, 1:HDR10, 2:SDR, 3~5:reserved */
				if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
				{
					wmb();
					for (i=0; i<198; i++)
					{
						gPE_HDR_DDR_O24->lut1.tone_0[i] = pstParams->data[i];
					}
					wmb();
					count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_TONE,0);
				}
				else if (connect == PE_HDR_HW_O24_CONNECT_MODE_H10)
				{
					wmb();
					for (i=0; i<198; i++)
					{
						gPE_HDR_DDR_O24->lut1.tone_1[i] = pstParams->data[i];
					}
					wmb();
					count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_TONE,1);
				}
				else
				{
					wmb();
					for (i=0; i<198; i++)
					{
						gPE_HDR_DDR_O24->lut1.tone_2[i] = pstParams->data[i];
					}
					wmb();
					count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_TONE,2);
				}
			} while(0);
		}
		PE_HDR_HW_O24_BACKUP_TRACE_LUT("T%d]%s)%x,%2d|%x,%x,%x~%x,%x|%x,%x,%x~%x,%x",\
			pstParams->win_id,PE_HDR_HW_O24_CONNECT_TO_STR(connect),pstParams->oper,count,\
			pstParams->data[0],pstParams->data[1],pstParams->data[2],pstParams->data[31],pstParams->data[32],\
			pstParams->data[33],pstParams->data[34],pstParams->data[35],pstParams->data[64],pstParams->data[65]);
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_GetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, ofst;

	do {
		CHECK_KNULL(pstParams);
		PE_HDR_HW_O24_CHECK_CODE((pstParams->size!=198),break,"size(%d) is wrong\n",pstParams->size);
		PE_DBG_HDR("[wid:%d] oper:0x%x, size:%d\n",pstParams->win_id,pstParams->oper,pstParams->size);
		if (pstParams->win_id == LX_PE_WIN_0)
		{
			/* llut0 x ***********************************************/
			PE_H10_0_O24_Wr(hdr_llut0_ia_ctrl,0x40005000);//ai,x
			PE_H10_0_O24_WrFL(hdr_llut0_ia_ctrl);
			ofst = 0;
			for(i=0; i<32; i++)
			{
				PE_H10_0_O24_RdFL(hdr_llut0_ia_data);
				pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut0_ia_data);
			}
			/* last point */
			i = 32;
			PE_H10_0_O24_RdFL(hdr_llut0_ctrl_05);
			pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut0_ctrl_05);
			/* llut0 y ***********************************************/
			PE_H10_0_O24_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
			PE_H10_0_O24_WrFL(hdr_llut0_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_0_O24_RdFL(hdr_llut0_ia_data);
				pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut0_ia_data);
			}
			/* set normal */
			PE_H10_0_O24_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
			PE_H10_0_O24_WrFL(hdr_llut0_ia_ctrl);
			/* last point */
			i = 32;
			PE_H10_0_O24_RdFL(hdr_llut0_ctrl_06);
			pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut0_ctrl_06);
			/* llut1 x ***********************************************/
			PE_H10_0_O24_Wr(hdr_llut1_ia_ctrl,0x40005000);//ai,x
			PE_H10_0_O24_WrFL(hdr_llut1_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_0_O24_RdFL(hdr_llut1_ia_data);
				pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut1_ia_data);
			}
			/* last point */
			i = 32;
			PE_H10_0_O24_RdFL(hdr_llut1_ctrl_05);
			pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut1_ctrl_05);
			/* llut1 y ***********************************************/
			PE_H10_0_O24_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
			PE_H10_0_O24_WrFL(hdr_llut1_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_0_O24_RdFL(hdr_llut1_ia_data);
				pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut1_ia_data);
			}
			/* set normal */
			PE_H10_0_O24_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
			PE_H10_0_O24_WrFL(hdr_llut1_ia_ctrl);
			/* last point */
			i = 32;
			PE_H10_0_O24_RdFL(hdr_llut1_ctrl_06);
			pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut1_ctrl_06);
			/* llut2 x ***********************************************/
			PE_H10_0_O24_Wr(hdr_llut2_ia_ctrl,0x40005000);//ai,x
			PE_H10_0_O24_WrFL(hdr_llut2_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_0_O24_RdFL(hdr_llut2_ia_data);
				pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut2_ia_data);
			}
			/* last point */
			i = 32;
			PE_H10_0_O24_RdFL(hdr_llut2_ctrl_05);
			pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut2_ctrl_05);
			/* llut2 y ***********************************************/
			PE_H10_0_O24_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
			PE_H10_0_O24_WrFL(hdr_llut2_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_0_O24_RdFL(hdr_llut2_ia_data);
				pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut2_ia_data);
			}
			/* set normal */
			PE_H10_0_O24_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
			PE_H10_0_O24_WrFL(hdr_llut2_ia_ctrl);
			/* last point */
			i = 32;
			PE_H10_0_O24_RdFL(hdr_llut2_ctrl_06);
			pstParams->data[i+ofst] = PE_H10_0_O24_Rd(hdr_llut2_ctrl_06);
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			/* llut0 x ***********************************************/
			PE_H10_1_O24_Wr(hdr_llut0_ia_ctrl,0x40005000);//ai,x
			PE_H10_1_O24_WrFL(hdr_llut0_ia_ctrl);
			ofst = 0;
			for(i=0; i<32; i++)
			{
				PE_H10_1_O24_RdFL(hdr_llut0_ia_data);
				pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut0_ia_data);
			}
			/* last point */
			i = 32;
			PE_H10_1_O24_RdFL(hdr_llut0_ctrl_05);
			pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut0_ctrl_05);
			/* llut0 y ***********************************************/
			PE_H10_1_O24_Wr(hdr_llut0_ia_ctrl,0x40001000);//ai,y
			PE_H10_1_O24_WrFL(hdr_llut0_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_1_O24_RdFL(hdr_llut0_ia_data);
				pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut0_ia_data);
			}
			/* set normal */
			PE_H10_1_O24_Wr(hdr_llut0_ia_ctrl,0x00008100);//normal
			PE_H10_1_O24_WrFL(hdr_llut0_ia_ctrl);
			/* last point */
			i = 32;
			PE_H10_1_O24_RdFL(hdr_llut0_ctrl_06);
			pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut0_ctrl_06);
			/* llut1 x ***********************************************/
			PE_H10_1_O24_Wr(hdr_llut1_ia_ctrl,0x40005000);//ai,x
			PE_H10_1_O24_WrFL(hdr_llut1_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_1_O24_RdFL(hdr_llut1_ia_data);
				pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut1_ia_data);
			}
			/* last point */
			i = 32;
			PE_H10_1_O24_RdFL(hdr_llut1_ctrl_05);
			pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut1_ctrl_05);
			/* llut1 y ***********************************************/
			PE_H10_1_O24_Wr(hdr_llut1_ia_ctrl,0x40001000);//ai,y
			PE_H10_1_O24_WrFL(hdr_llut1_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_1_O24_RdFL(hdr_llut1_ia_data);
				pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut1_ia_data);
			}
			/* set normal */
			PE_H10_1_O24_Wr(hdr_llut1_ia_ctrl,0x00008100);//normal
			PE_H10_1_O24_WrFL(hdr_llut1_ia_ctrl);
			/* last point */
			i = 32;
			PE_H10_1_O24_RdFL(hdr_llut1_ctrl_06);
			pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut1_ctrl_06);
			/* llut2 x ***********************************************/
			PE_H10_1_O24_Wr(hdr_llut2_ia_ctrl,0x40005000);//ai,x
			PE_H10_1_O24_WrFL(hdr_llut2_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_1_O24_RdFL(hdr_llut2_ia_data);
				pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut2_ia_data);
			}
			/* last point */
			i = 32;
			PE_H10_1_O24_RdFL(hdr_llut2_ctrl_05);
			pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut2_ctrl_05);
			/* llut2 y ***********************************************/
			PE_H10_1_O24_Wr(hdr_llut2_ia_ctrl,0x40001000);//ai,y
			PE_H10_1_O24_WrFL(hdr_llut2_ia_ctrl);
			ofst += 33;
			for(i=0; i<32; i++)
			{
				PE_H10_1_O24_RdFL(hdr_llut2_ia_data);
				pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut2_ia_data);
			}
			/* set normal */
			PE_H10_1_O24_Wr(hdr_llut2_ia_ctrl,0x00008100);//normal
			PE_H10_1_O24_WrFL(hdr_llut2_ia_ctrl);
			/* last point */
			i = 32;
			PE_H10_1_O24_RdFL(hdr_llut2_ctrl_06);
			pstParams->data[i+ofst] = PE_H10_1_O24_Rd(hdr_llut2_ctrl_06);
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_SetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, count=0, connect;
	do {
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);
		PE_HDR_HW_O24_CHECK_CODE((pstParams->size!=33),break,"size(%d) is wrong\n",pstParams->size);
		PE_DBG_HDR("[wid:%d] oper:0x%x, size:%d\n",pstParams->win_id,pstParams->oper,pstParams->size);

		connect = PE_HDR_HW_O24_GetConnectMode(pstParams->win_id);

		if (pstParams->win_id == LX_PE_WIN_0)
		{
			/* YLUT : 0:HLG, 1:reserved */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				wmb();
				for (i=0; i<33; i++)
				{
					gPE_HDR_DDR_O24->lut0.ylut_0[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_YLUT,0);
			}
			else
			{
				wmb();
				for (i=0; i<33; i++)
				{
					gPE_HDR_DDR_O24->lut0.ylut_1[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_YLUT,1);
			}
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			/* YLUT : 0:HLG, 1:reserved */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				wmb();
				for (i=0; i<33; i++)
				{
					gPE_HDR_DDR_O24->lut1.ylut_0[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_YLUT,0);
			}
			else
			{
				wmb();
				for (i=0; i<33; i++)
				{
					gPE_HDR_DDR_O24->lut1.ylut_1[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_YLUT,1);
			}
		}

		PE_HDR_HW_O24_BACKUP_TRACE("Y%d]%s)%x,%2d|%x,%x,%x~%x,%x",\
			pstParams->win_id,PE_HDR_HW_O24_CONNECT_TO_STR(connect),pstParams->oper,count,\
			pstParams->data[0],pstParams->data[1],pstParams->data[2],pstParams->data[31],pstParams->data[32]);
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_GetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	do {
		CHECK_KNULL(pstParams);
		PE_HDR_HW_O24_CHECK_CODE((pstParams->size!=33),break,"size(%d) is wrong\n",pstParams->size);
		PE_DBG_HDR("[wid:%d] oper:0x%x, size:%d\n",pstParams->win_id,pstParams->oper,pstParams->size);

		if (pstParams->win_id == LX_PE_WIN_0)
		{
			PE_H10_0_O24_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
			PE_H10_0_O24_WrFL(hdr_ygain_lut_ia_ctrl);
			for(i=0;i<32;i++)
			{
				PE_H10_0_O24_RdFL(hdr_ygain_lut_ia_data);
				pstParams->data[i] = PE_H10_0_O24_Rd(hdr_ygain_lut_ia_data);
			}
			/* set normal */
			PE_H10_0_O24_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
			PE_H10_0_O24_WrFL(hdr_ygain_lut_ia_ctrl);
			/* last point */
			i = 32;
			PE_H10_0_O24_RdFL(hdr_ygain_lut_ctrl_05);
			pstParams->data[i] = PE_H10_0_O24_Rd(hdr_ygain_lut_ctrl_05);
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			PE_H10_1_O24_Wr(hdr_ygain_lut_ia_ctrl,0x40001000);//ai
			PE_H10_1_O24_WrFL(hdr_ygain_lut_ia_ctrl);
			for(i=0;i<32;i++)
			{
				PE_H10_1_O24_RdFL(hdr_ygain_lut_ia_data);
				pstParams->data[i] = PE_H10_1_O24_Rd(hdr_ygain_lut_ia_data);
			}
			/* set normal */
			PE_H10_1_O24_Wr(hdr_ygain_lut_ia_ctrl,0x00008100);//ai
			PE_H10_1_O24_WrFL(hdr_ygain_lut_ia_ctrl);
			/* last point */
			i = 32;
			PE_H10_1_O24_RdFL(hdr_ygain_lut_ctrl_05);
			pstParams->data[i] = PE_H10_1_O24_Rd(hdr_ygain_lut_ctrl_05);
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_SetCsc(LX_PE_HDR_CSC_T *pstParams)
{
	int ret = RET_OK;
	UINT32 count = 0;
	const UINT16 *p_pcc;
	PE_HDR_HW_O24_SETTINGS_T *pInfo=&_g_pe_hdr_hw_o24_info;

	do{
		CHECK_KNULL(pstParams);
		PE_DBG_HDR("set pstParams[%d]\n"\
			"tp1:%d, coef:%04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x\n",\
			pstParams->win_id,pstParams->type1,\
			pstParams->coef1[0],pstParams->coef1[1],pstParams->coef1[2],\
			pstParams->coef1[3],pstParams->coef1[4],pstParams->coef1[5],\
			pstParams->coef1[6],pstParams->coef1[7],pstParams->coef1[8]);

		switch (pstParams->type1)
		{
			case LX_PE_HDR_CSC_MANUAL:
				p_pcc = pstParams->coef1;
				break;
			case LX_PE_HDR_CSC_BYPASS:
				p_pcc = _g_pe_hdr_hw_o24_csc_mtrx_bypass;
				break;
			case LX_PE_HDR_CSC_DEFAULT:
			case LX_PE_HDR_CSC_DEFAULT1:
			default:
				p_pcc = _g_pe_hdr_hw_o24_pcc_mtrx_default;
				break;
		}
		if (pstParams->win_id == LX_PE_WIN_0)
		{
			wmb();
			gPE_HDR_DDR_O24->lut0.pcc_0[0] = (p_pcc[0]<<16)|p_pcc[1];
			gPE_HDR_DDR_O24->lut0.pcc_0[1] = (p_pcc[2]<<16)|p_pcc[3];
			gPE_HDR_DDR_O24->lut0.pcc_0[2] = (p_pcc[4]<<16)|p_pcc[5];
			gPE_HDR_DDR_O24->lut0.pcc_0[3] = (p_pcc[6]<<16)|p_pcc[7];
			gPE_HDR_DDR_O24->lut0.pcc_0[4] = (p_pcc[8]<<16);
			wmb();
			count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_PCC,0);

			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;

				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_01.r_pcc_coef0,GET_BITS(p_pcc[0],0,16));
				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_01.r_pcc_coef1,GET_BITS(p_pcc[1],0,16));
				PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_01.udata32);
				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_02.r_pcc_coef2,GET_BITS(p_pcc[2],0,16));
				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_02.r_pcc_coef3,GET_BITS(p_pcc[3],0,16));
				PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_02.udata32);
				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_03.r_pcc_coef4,GET_BITS(p_pcc[4],0,16));
				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_03.r_pcc_coef5,GET_BITS(p_pcc[5],0,16));
				PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_03.udata32);
				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_04.r_pcc_coef6,GET_BITS(p_pcc[6],0,16));
				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_04.r_pcc_coef7,GET_BITS(p_pcc[7],0,16));
				PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_04.udata32);
				PE_CHPI_APB0_O24F22_Wr(pcc.hdr_pcc_ctrl_05.r_pcc_coef8,GET_BITS(p_pcc[8],0,16));
				PE_CHPI_APB0_O24F22_WrFL(pcc.hdr_pcc_ctrl_05.udata32);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_PCC);
			} while(0);
			#endif
			memcpy(&(pInfo->pre_csc[0]),pstParams, sizeof(LX_PE_HDR_CSC_T));
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			wmb();
			gPE_HDR_DDR_O24->lut1.pcc_0[0] = (p_pcc[0]<<16)|p_pcc[1];
			gPE_HDR_DDR_O24->lut1.pcc_0[1] = (p_pcc[2]<<16)|p_pcc[3];
			gPE_HDR_DDR_O24->lut1.pcc_0[2] = (p_pcc[4]<<16)|p_pcc[5];
			gPE_HDR_DDR_O24->lut1.pcc_0[3] = (p_pcc[6]<<16)|p_pcc[7];
			gPE_HDR_DDR_O24->lut1.pcc_0[4] = (p_pcc[8]<<16);
			wmb();
			count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_PCC,0);
			memcpy(&(pInfo->pre_csc[1]),pstParams, sizeof(LX_PE_HDR_CSC_T));
		}

		PE_HDR_HW_O24_BACKUP_TRACE("[PCC%d]%2d,%d, %04x,%04x,%04x, %04x,%04x,%04x, %04x,%04x,%04x",\
			pstParams->win_id,count,pstParams->type1,\
			pstParams->coef1[0],pstParams->coef1[1],pstParams->coef1[2],\
			pstParams->coef1[3],pstParams->coef1[4],pstParams->coef1[5],\
			pstParams->coef1[6],pstParams->coef1[7],pstParams->coef1[8]);
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_GetCsc(LX_PE_HDR_CSC_T *pstParams)
{
	int ret = RET_OK;
	UINT32 udata32;
	UINT16 *p_co0,*p_of0,*p_co1,*p_of1,*p_co2,*p_of2;
	PE_HDR_HW_O24_SETTINGS_T *pInfo=&_g_pe_hdr_hw_o24_info;
	do{
		CHECK_KNULL(pstParams);
		if (pstParams->win_id == LX_PE_WIN_0)//check register
		{
			pstParams->type0 = pInfo->pre_csc[0].type0;
			pstParams->type1 = pInfo->pre_csc[0].type1;
			pstParams->type2 = pInfo->pre_csc[0].type2;
			p_co0 = pstParams->coef0;	p_of0 = pstParams->ofst0;
			p_co1 = pstParams->coef1;	p_of1 = pstParams->ofst1;
			p_co2 = pstParams->coef2;	p_of2 = pstParams->ofst2;
			/* csc1 */
			PE_H10_0_O24_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
			PE_H10_0_O24_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
			PE_H10_0_O24_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
			PE_H10_0_O24_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
			PE_H10_0_O24_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
			PE_H10_0_O24_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
			PE_H10_0_O24_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
			PE_H10_0_O24_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
			/* pcc */
			PE_H10_0_O24_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
			PE_H10_0_O24_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
			PE_H10_0_O24_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
			PE_H10_0_O24_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
			PE_H10_0_O24_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
			p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
			/* csc4 */
			PE_H10_0_O24_QRd02(hdr_csc4_ctrl_01,r_csc4th_coef0,p_co2[0],r_csc4th_coef1,p_co2[1]);
			PE_H10_0_O24_QRd02(hdr_csc4_ctrl_02,r_csc4th_coef2,p_co2[2],r_csc4th_coef3,p_co2[3]);
			PE_H10_0_O24_QRd02(hdr_csc4_ctrl_03,r_csc4th_coef4,p_co2[4],r_csc4th_coef5,p_co2[5]);
			PE_H10_0_O24_QRd02(hdr_csc4_ctrl_04,r_csc4th_coef6,p_co2[6],r_csc4th_coef7,p_co2[7]);
			PE_H10_0_O24_QRd01(hdr_csc4_ctrl_05,r_csc4th_coef8,p_co2[8]);
			PE_H10_0_O24_QRd02(hdr_csc4_ctrl_06,r_csc4th_ofst0,p_of2[0],r_csc4th_ofst1,p_of2[1]);
			PE_H10_0_O24_QRd02(hdr_csc4_ctrl_07,r_csc4th_ofst2,p_of2[2],r_csc4th_ofst3,p_of2[3]);
			PE_H10_0_O24_QRd02(hdr_csc4_ctrl_08,r_csc4th_ofst4,p_of2[4],r_csc4th_ofst5,p_of2[5]);
		}
		else if (pstParams->win_id == LX_PE_WIN_1)//check register
		{
			pstParams->type0 = pInfo->pre_csc[1].type0;
			pstParams->type1 = pInfo->pre_csc[1].type1;
			pstParams->type2 = pInfo->pre_csc[1].type2;
			p_co0 = pstParams->coef0;	p_of0 = pstParams->ofst0;
			p_co1 = pstParams->coef1;	p_of1 = pstParams->ofst1;
			p_co2 = pstParams->coef2;	p_of2 = pstParams->ofst2;
			/* csc1 */
			PE_H10_1_O24_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
			PE_H10_1_O24_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
			PE_H10_1_O24_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
			PE_H10_1_O24_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
			PE_H10_1_O24_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
			PE_H10_1_O24_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
			PE_H10_1_O24_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
			PE_H10_1_O24_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
			/* pcc */
			PE_H10_1_O24_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
			PE_H10_1_O24_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
			PE_H10_1_O24_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
			PE_H10_1_O24_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
			PE_H10_1_O24_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
			p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
			/* csc4 */
			PE_H10_1_O24_QRd02(hdr_csc4_ctrl_01,r_csc4th_coef0,p_co2[0],r_csc4th_coef1,p_co2[1]);
			PE_H10_1_O24_QRd02(hdr_csc4_ctrl_02,r_csc4th_coef2,p_co2[2],r_csc4th_coef3,p_co2[3]);
			PE_H10_1_O24_QRd02(hdr_csc4_ctrl_03,r_csc4th_coef4,p_co2[4],r_csc4th_coef5,p_co2[5]);
			PE_H10_1_O24_QRd02(hdr_csc4_ctrl_04,r_csc4th_coef6,p_co2[6],r_csc4th_coef7,p_co2[7]);
			PE_H10_1_O24_QRd01(hdr_csc4_ctrl_05,r_csc4th_coef8,p_co2[8]);
			PE_H10_1_O24_QRd02(hdr_csc4_ctrl_06,r_csc4th_ofst0,p_of2[0],r_csc4th_ofst1,p_of2[1]);
			PE_H10_1_O24_QRd02(hdr_csc4_ctrl_07,r_csc4th_ofst2,p_of2[2],r_csc4th_ofst3,p_of2[3]);
			PE_H10_1_O24_QRd02(hdr_csc4_ctrl_08,r_csc4th_ofst4,p_of2[4],r_csc4th_ofst5,p_of2[5]);
		}
		else if (pstParams->win_id == LX_PE_WIN_2)//check pre value
		{
			pstParams->type0 = pInfo->pre_csc[0].type0;
			pstParams->type1 = pInfo->pre_csc[0].type1;
			pstParams->type2 = pInfo->pre_csc[0].type2;
			rmb();
			udata32 = gPE_HDR_DDR_O24->lut0.pcc_0[0];
			pstParams->coef1[0] = (udata32>>16)&0xffff;
			pstParams->coef1[1] = udata32&0xffff;
			udata32 = gPE_HDR_DDR_O24->lut0.pcc_0[1];
			pstParams->coef1[2] = (udata32>>16)&0xffff;
			pstParams->coef1[3] = udata32&0xffff;
			udata32 = gPE_HDR_DDR_O24->lut0.pcc_0[2];
			pstParams->coef1[4] = (udata32>>16)&0xffff;
			pstParams->coef1[5] = udata32&0xffff;
			udata32 = gPE_HDR_DDR_O24->lut0.pcc_0[3];
			pstParams->coef1[6] = (udata32>>16)&0xffff;
			pstParams->coef1[7] = udata32&0xffff;
			udata32 = gPE_HDR_DDR_O24->lut0.pcc_0[4];
			pstParams->coef1[8] = (udata32>>16)&0xffff;
			rmb();
		}
		else if (pstParams->win_id == LX_PE_WIN_3)//check pre value
		{
			pstParams->type0 = pInfo->pre_csc[1].type0;
			pstParams->type1 = pInfo->pre_csc[1].type1;
			pstParams->type2 = pInfo->pre_csc[1].type2;
			rmb();
			udata32 = gPE_HDR_DDR_O24->lut1.pcc_0[0];
			pstParams->coef1[0] = (udata32>>16)&0xffff;
			pstParams->coef1[1] = udata32&0xffff;
			udata32 = gPE_HDR_DDR_O24->lut1.pcc_0[1];
			pstParams->coef1[2] = (udata32>>16)&0xffff;
			pstParams->coef1[3] = udata32&0xffff;
			udata32 = gPE_HDR_DDR_O24->lut1.pcc_0[2];
			pstParams->coef1[4] = (udata32>>16)&0xffff;
			pstParams->coef1[5] = udata32&0xffff;
			udata32 = gPE_HDR_DDR_O24->lut1.pcc_0[3];
			pstParams->coef1[6] = (udata32>>16)&0xffff;
			pstParams->coef1[7] = udata32&0xffff;
			udata32 = gPE_HDR_DDR_O24->lut1.pcc_0[4];
			pstParams->coef1[8] = (udata32>>16)&0xffff;
			rmb();
		}

		PE_DBG_HDR("get pstParams[%d]\n"\
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

int PE_HDR_HW_O24_GetGeneralInfo(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0;
	UINT32 *p_co0 = _g_pe_hdr_hw_o24_info.hdr_co0;
	UINT32 *p_of0 = _g_pe_hdr_hw_o24_info.hdr_of0;
	UINT32 *p_co1 = _g_pe_hdr_hw_o24_info.hdr_co1;
	UINT32 *p_of1 = _g_pe_hdr_hw_o24_info.hdr_of1;
	UINT32 *p_co2 = _g_pe_hdr_hw_o24_info.hdr_co2;
	UINT32 *p_of2 = _g_pe_hdr_hw_o24_info.hdr_of2;
	UINT32 *p_co3 = _g_pe_hdr_hw_o24_info.hdr_co3;
	UINT32 *p_of3 = _g_pe_hdr_hw_o24_info.hdr_of3;
	UINT32 *p_co4 = _g_pe_hdr_hw_o24_info.hdr_co4;
	UINT32 *p_of4 = _g_pe_hdr_hw_o24_info.hdr_of4;
	PE_HDR_HW_O24_SETTINGS_T *pInfo=&_g_pe_hdr_hw_o24_info;

#define PE_HDR_O24_PRINT_START		"START_OF_PRINT"
#define PE_HDR_O24_PRINT_RESERVED	"RESERVED"
#define PE_HDR_O24_PRINT_END		"END_OF_PRINT"
#define PE_HDR_O24_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_HDR_O24_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE,"   [0x%02x] %s\n",(_item),#_item);_action;break
#define PE_HDR_O24_CASE_SPRINT(_cnt,_action,_buf,fmt,args...)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break
#define PE_HDR_O24_DFLT_SPRINT(_action,_buf,fmt,args...)		\
	default:snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		rd_cnt = pstParams->oper;
		if (pstParams->data[0]==PE_HDR_HW_O24_INFO_MENU_DISPLAY)
		{
			switch (rd_cnt)
			{
				PE_HDR_O24_CASE_SPRINT( 0, rd_cnt++, buffer, PE_HDR_O24_PRINT_START);
				PE_HDR_O24_CASE_PRMENU( 1, rd_cnt++, buffer, PE_HDR_HW_O24_INFO_MENU_RD_INF0);
				PE_HDR_O24_CASE_PRMENU( 2, rd_cnt++, buffer, PE_HDR_HW_O24_INFO_MENU_RD_INF1);
				PE_HDR_O24_CASE_PRMENU( 3, rd_cnt++, buffer, PE_HDR_HW_O24_INFO_MENU_RD_INF2);
				PE_HDR_O24_CASE_PRMENU( 4, rd_cnt++, buffer, PE_HDR_HW_O24_INFO_MENU_RD_INF3);
				PE_HDR_O24_CASE_PRMENU( 5, rd_cnt++, buffer, PE_HDR_HW_O24_INFO_MENU_RD_INF4);
				PE_HDR_O24_CASE_SPRINT( 6, rd_cnt++, buffer, PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_DFLT_SPRINT(rd_cnt=0, buffer, PE_HDR_O24_PRINT_END);
			}
		}
		else if (pstParams->data[0]==PE_HDR_HW_O24_INFO_MENU_RD_INF0)
		{
			if (rd_cnt==0)
			{
				/* csc1 */
				PE_H10_0_O24_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
				PE_H10_0_O24_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
				PE_H10_0_O24_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
				PE_H10_0_O24_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
				PE_H10_0_O24_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
				PE_H10_0_O24_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
				PE_H10_0_O24_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
				PE_H10_0_O24_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
				/* pcc */
				PE_H10_0_O24_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
				PE_H10_0_O24_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
				PE_H10_0_O24_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
				PE_H10_0_O24_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
				PE_H10_0_O24_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
				p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
				/* csc3 */
				PE_H10_0_O24_QRd02(hdr_csc3_ctrl_01,r_csc3rd_coef0,p_co2[0],r_csc3rd_coef1,p_co2[1]);
				PE_H10_0_O24_QRd02(hdr_csc3_ctrl_02,r_csc3rd_coef2,p_co2[2],r_csc3rd_coef3,p_co2[3]);
				PE_H10_0_O24_QRd02(hdr_csc3_ctrl_03,r_csc3rd_coef4,p_co2[4],r_csc3rd_coef5,p_co2[5]);
				PE_H10_0_O24_QRd02(hdr_csc3_ctrl_04,r_csc3rd_coef6,p_co2[6],r_csc3rd_coef7,p_co2[7]);
				PE_H10_0_O24_QRd01(hdr_csc3_ctrl_05,r_csc3rd_coef8,p_co2[8]);
				PE_H10_0_O24_QRd02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,p_of2[0],r_csc3rd_ofst1,p_of2[1]);
				PE_H10_0_O24_QRd02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,p_of2[2],r_csc3rd_ofst3,p_of2[3]);
				PE_H10_0_O24_QRd02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,p_of2[4],r_csc3rd_ofst5,p_of2[5]);
				/* csc4 */
				PE_H10_0_O24_QRd02(hdr_csc4_ctrl_01,r_csc4th_coef0,p_co3[0],r_csc4th_coef1,p_co3[1]);
				PE_H10_0_O24_QRd02(hdr_csc4_ctrl_02,r_csc4th_coef2,p_co3[2],r_csc4th_coef3,p_co3[3]);
				PE_H10_0_O24_QRd02(hdr_csc4_ctrl_03,r_csc4th_coef4,p_co3[4],r_csc4th_coef5,p_co3[5]);
				PE_H10_0_O24_QRd02(hdr_csc4_ctrl_04,r_csc4th_coef6,p_co3[6],r_csc4th_coef7,p_co3[7]);
				PE_H10_0_O24_QRd01(hdr_csc4_ctrl_05,r_csc4th_coef8,p_co3[8]);
				PE_H10_0_O24_QRd02(hdr_csc4_ctrl_06,r_csc4th_ofst0,p_of3[0],r_csc4th_ofst1,p_of3[1]);
				PE_H10_0_O24_QRd02(hdr_csc4_ctrl_07,r_csc4th_ofst2,p_of3[2],r_csc4th_ofst3,p_of3[3]);
				PE_H10_0_O24_QRd02(hdr_csc4_ctrl_08,r_csc4th_ofst4,p_of3[4],r_csc4th_ofst5,p_of3[5]);
			}
			switch(rd_cnt)
			{
				PE_HDR_O24_CASE_SPRINT( 0,rd_cnt++,buffer,PE_HDR_O24_PRINT_START);
				PE_HDR_O24_CASE_SPRINT( 1,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT( 2,rd_cnt++,buffer,\
					"(0)hdr csc1 type:%d (hdr_type:%d <- %d)\n",\
					pInfo->pre_csc[0].type0,pInfo->cur_hdr_type[0],pInfo->pre_hdr_type[0]);
				PE_HDR_O24_CASE_SPRINT( 3,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT( 4,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co0[0], p_co0[1], p_co0[2], p_of0[0], p_of0[3]);
				PE_HDR_O24_CASE_SPRINT( 5,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co0[3], p_co0[4], p_co0[5], p_of0[1], p_of0[4]);
				PE_HDR_O24_CASE_SPRINT( 6,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co0[6], p_co0[7], p_co0[8], p_of0[2], p_of0[5]);
				PE_HDR_O24_CASE_SPRINT( 7,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT( 8,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT( 9,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(10,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(11,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(12,rd_cnt++,buffer,\
					"(0)hdr pcc type:%d\n",pInfo->pre_csc[0].type1);
				PE_HDR_O24_CASE_SPRINT(13,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(14,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co1[0], p_co1[1], p_co1[2], p_of1[0], p_of1[3]);
				PE_HDR_O24_CASE_SPRINT(15,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co1[3], p_co1[4], p_co1[5], p_of1[1], p_of1[4]);
				PE_HDR_O24_CASE_SPRINT(16,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co1[6], p_co1[7], p_co1[8], p_of1[2], p_of1[5]);
				PE_HDR_O24_CASE_SPRINT(17,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(18,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(19,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(20,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(21,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(22,rd_cnt++,buffer,\
					"(0)hdr csc3 type:%d (hdr_type:%d <- %d)\n",\
					pInfo->pre_csc[0].type2,pInfo->cur_hdr_type[0],pInfo->pre_hdr_type[0]);
				PE_HDR_O24_CASE_SPRINT(23,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(24,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co2[0], p_co2[1], p_co2[2], p_of2[0], p_of2[3]);
				PE_HDR_O24_CASE_SPRINT(25,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co2[3], p_co2[4], p_co2[5], p_of2[1], p_of2[4]);
				PE_HDR_O24_CASE_SPRINT(26,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co2[6], p_co2[7], p_co2[8], p_of2[2], p_of2[5]);
				PE_HDR_O24_CASE_SPRINT(27,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(28,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(29,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(30,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(31,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(32,rd_cnt++,buffer,\
					"(0)hdr csc4 type:%d (hdr_type:%d <- %d)\n",\
					pInfo->pre_csc[0].type0,pInfo->cur_hdr_type[0],pInfo->pre_hdr_type[0]);
				PE_HDR_O24_CASE_SPRINT(33,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(34,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co3[0], p_co3[1], p_co3[2], p_of3[0], p_of3[3]);
				PE_HDR_O24_CASE_SPRINT(35,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co3[3], p_co3[4], p_co3[5], p_of3[1], p_of3[4]);
				PE_HDR_O24_CASE_SPRINT(36,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co3[6], p_co3[7], p_co3[8], p_of3[2], p_of3[5]);
				PE_HDR_O24_CASE_SPRINT(37,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(38,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(39,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(40,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(41,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(42,rd_cnt++,buffer,\
					"(0)hdr csc1(s2h) type:%d (hdr_type:%d <- %d)\n",\
					pInfo->pre_csc[0].type0,pInfo->cur_hdr_type[0],pInfo->pre_hdr_type[0]);
				PE_HDR_O24_CASE_SPRINT(43,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(44,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co4[0], p_co4[1], p_co4[2], p_of4[0], p_of4[3]);
				PE_HDR_O24_CASE_SPRINT(45,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co4[3], p_co4[4], p_co4[5], p_of4[1], p_of4[4]);
				PE_HDR_O24_CASE_SPRINT(46,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co4[6], p_co4[7], p_co4[8], p_of4[2], p_of4[5]);
				PE_HDR_O24_CASE_SPRINT(47,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(48,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(49,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(50,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_DFLT_SPRINT(rd_cnt=0,buffer,PE_HDR_O24_PRINT_END);
			}
		}
		else if (pstParams->data[0]==PE_HDR_HW_O24_INFO_MENU_RD_INF1)
		{
			if (rd_cnt==0)
			{
				/* csc1 */
				PE_H10_1_O24_QRd02(hdr_csc1_ctrl_01,r_csc1st_coef0,p_co0[0],r_csc1st_coef1,p_co0[1]);
				PE_H10_1_O24_QRd02(hdr_csc1_ctrl_02,r_csc1st_coef2,p_co0[2],r_csc1st_coef3,p_co0[3]);
				PE_H10_1_O24_QRd02(hdr_csc1_ctrl_03,r_csc1st_coef4,p_co0[4],r_csc1st_coef5,p_co0[5]);
				PE_H10_1_O24_QRd02(hdr_csc1_ctrl_04,r_csc1st_coef6,p_co0[6],r_csc1st_coef7,p_co0[7]);
				PE_H10_1_O24_QRd01(hdr_csc1_ctrl_05,r_csc1st_coef8,p_co0[8]);
				PE_H10_1_O24_QRd02(hdr_csc1_ctrl_06,r_csc1st_ofst0,p_of0[0],r_csc1st_ofst1,p_of0[1]);
				PE_H10_1_O24_QRd02(hdr_csc1_ctrl_07,r_csc1st_ofst2,p_of0[2],r_csc1st_ofst3,p_of0[3]);
				PE_H10_1_O24_QRd02(hdr_csc1_ctrl_08,r_csc1st_ofst4,p_of0[4],r_csc1st_ofst5,p_of0[5]);
				/* pcc */
				PE_H10_1_O24_QRd02(hdr_pcc_ctrl_01,r_pcc_coef0,p_co1[0],r_pcc_coef1,p_co1[1]);
				PE_H10_1_O24_QRd02(hdr_pcc_ctrl_02,r_pcc_coef2,p_co1[2],r_pcc_coef3,p_co1[3]);
				PE_H10_1_O24_QRd02(hdr_pcc_ctrl_03,r_pcc_coef4,p_co1[4],r_pcc_coef5,p_co1[5]);
				PE_H10_1_O24_QRd02(hdr_pcc_ctrl_04,r_pcc_coef6,p_co1[6],r_pcc_coef7,p_co1[7]);
				PE_H10_1_O24_QRd01(hdr_pcc_ctrl_05,r_pcc_coef8,p_co1[8]);
				p_of1[0] = p_of1[1] = p_of1[2] = p_of1[3] = p_of1[4] = p_of1[5] = 0;
				/* csc3 */
				PE_H10_1_O24_QRd02(hdr_csc3_ctrl_01,r_csc3rd_coef0,p_co2[0],r_csc3rd_coef1,p_co2[1]);
				PE_H10_1_O24_QRd02(hdr_csc3_ctrl_02,r_csc3rd_coef2,p_co2[2],r_csc3rd_coef3,p_co2[3]);
				PE_H10_1_O24_QRd02(hdr_csc3_ctrl_03,r_csc3rd_coef4,p_co2[4],r_csc3rd_coef5,p_co2[5]);
				PE_H10_1_O24_QRd02(hdr_csc3_ctrl_04,r_csc3rd_coef6,p_co2[6],r_csc3rd_coef7,p_co2[7]);
				PE_H10_1_O24_QRd01(hdr_csc3_ctrl_05,r_csc3rd_coef8,p_co2[8]);
				PE_H10_1_O24_QRd02(hdr_csc3_ctrl_06,r_csc3rd_ofst0,p_of2[0],r_csc3rd_ofst1,p_of2[1]);
				PE_H10_1_O24_QRd02(hdr_csc3_ctrl_07,r_csc3rd_ofst2,p_of2[2],r_csc3rd_ofst3,p_of2[3]);
				PE_H10_1_O24_QRd02(hdr_csc3_ctrl_08,r_csc3rd_ofst4,p_of2[4],r_csc3rd_ofst5,p_of2[5]);
				/* csc4 */
				PE_H10_1_O24_QRd02(hdr_csc4_ctrl_01,r_csc4th_coef0,p_co3[0],r_csc4th_coef1,p_co3[1]);
				PE_H10_1_O24_QRd02(hdr_csc4_ctrl_02,r_csc4th_coef2,p_co3[2],r_csc4th_coef3,p_co3[3]);
				PE_H10_1_O24_QRd02(hdr_csc4_ctrl_03,r_csc4th_coef4,p_co3[4],r_csc4th_coef5,p_co3[5]);
				PE_H10_1_O24_QRd02(hdr_csc4_ctrl_04,r_csc4th_coef6,p_co3[6],r_csc4th_coef7,p_co3[7]);
				PE_H10_1_O24_QRd01(hdr_csc4_ctrl_05,r_csc4th_coef8,p_co3[8]);
				PE_H10_1_O24_QRd02(hdr_csc4_ctrl_06,r_csc4th_ofst0,p_of3[0],r_csc4th_ofst1,p_of3[1]);
				PE_H10_1_O24_QRd02(hdr_csc4_ctrl_07,r_csc4th_ofst2,p_of3[2],r_csc4th_ofst3,p_of3[3]);
				PE_H10_1_O24_QRd02(hdr_csc4_ctrl_08,r_csc4th_ofst4,p_of3[4],r_csc4th_ofst5,p_of3[5]);
			}
			switch(rd_cnt)
			{
				PE_HDR_O24_CASE_SPRINT( 0,rd_cnt++,buffer,PE_HDR_O24_PRINT_START);
				PE_HDR_O24_CASE_SPRINT( 1,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT( 2,rd_cnt++,buffer,\
					"(0)hdr csc1 type:%d (hdr_type:%d <- %d)\n",\
					pInfo->pre_csc[1].type0,pInfo->cur_hdr_type[1],pInfo->pre_hdr_type[1]);
				PE_HDR_O24_CASE_SPRINT( 3,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT( 4,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co0[0], p_co0[1], p_co0[2], p_of0[0], p_of0[3]);
				PE_HDR_O24_CASE_SPRINT( 5,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co0[3], p_co0[4], p_co0[5], p_of0[1], p_of0[4]);
				PE_HDR_O24_CASE_SPRINT( 6,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co0[6], p_co0[7], p_co0[8], p_of0[2], p_of0[5]);
				PE_HDR_O24_CASE_SPRINT( 7,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT( 8,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT( 9,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(10,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(11,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(12,rd_cnt++,buffer,\
					"(0)hdr pcc type:%d\n",pInfo->pre_csc[1].type1);
				PE_HDR_O24_CASE_SPRINT(13,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(14,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co1[0], p_co1[1], p_co1[2], p_of1[0], p_of1[3]);
				PE_HDR_O24_CASE_SPRINT(15,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co1[3], p_co1[4], p_co1[5], p_of1[1], p_of1[4]);
				PE_HDR_O24_CASE_SPRINT(16,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co1[6], p_co1[7], p_co1[8], p_of1[2], p_of1[5]);
				PE_HDR_O24_CASE_SPRINT(17,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(18,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(19,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(20,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(21,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(22,rd_cnt++,buffer,\
					"(0)hdr csc3 type:%d (hdr_type:%d <- %d)\n",\
					pInfo->pre_csc[1].type2,pInfo->cur_hdr_type[1],pInfo->pre_hdr_type[1]);
				PE_HDR_O24_CASE_SPRINT(23,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(24,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co2[0], p_co2[1], p_co2[2], p_of2[0], p_of2[3]);
				PE_HDR_O24_CASE_SPRINT(25,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co2[3], p_co2[4], p_co2[5], p_of2[1], p_of2[4]);
				PE_HDR_O24_CASE_SPRINT(26,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co2[6], p_co2[7], p_co2[8], p_of2[2], p_of2[5]);
				PE_HDR_O24_CASE_SPRINT(27,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(28,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(29,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(30,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(31,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(32,rd_cnt++,buffer,\
					"(0)hdr csc4 type:%d (hdr_type:%d <- %d)\n",\
					pInfo->pre_csc[1].type0,pInfo->cur_hdr_type[1],pInfo->pre_hdr_type[1]);
				PE_HDR_O24_CASE_SPRINT(33,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(34,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co3[0], p_co3[1], p_co3[2], p_of3[0], p_of3[3]);
				PE_HDR_O24_CASE_SPRINT(35,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co3[3], p_co3[4], p_co3[5], p_of3[1], p_of3[4]);
				PE_HDR_O24_CASE_SPRINT(36,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co3[6], p_co3[7], p_co3[8], p_of3[2], p_of3[5]);
				PE_HDR_O24_CASE_SPRINT(37,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(38,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(39,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(40,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(41,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(42,rd_cnt++,buffer,\
					"(0)hdr csc1(s2h) type:%d (hdr_type:%d <- %d)\n",\
					pInfo->pre_csc[1].type0,pInfo->cur_hdr_type[1],pInfo->pre_hdr_type[1]);
				PE_HDR_O24_CASE_SPRINT(43,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(44,rd_cnt++,buffer,\
					"0,1,2, 0,3 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co4[0], p_co4[1], p_co4[2], p_of4[0], p_of4[3]);
				PE_HDR_O24_CASE_SPRINT(45,rd_cnt++,buffer,\
					"3,4,5, 1,4 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co4[3], p_co4[4], p_co4[5], p_of4[1], p_of4[4]);
				PE_HDR_O24_CASE_SPRINT(46,rd_cnt++,buffer,\
					"6,7,8, 2,5 = 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x\n",\
					p_co4[6], p_co4[7], p_co4[8], p_of4[2], p_of4[5]);
				PE_HDR_O24_CASE_SPRINT(47,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_HDR_O24_CASE_SPRINT(48,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(49,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_CASE_SPRINT(50,rd_cnt++,buffer,PE_HDR_O24_PRINT_RESERVED);
				PE_HDR_O24_DFLT_SPRINT(rd_cnt=0,buffer,PE_HDR_O24_PRINT_END);
			}
		}
		else
		{
			snprintf(buffer,PE_TRACE_STR_SIZE,PE_HDR_O24_PRINT_EXIT);
			rd_cnt=0;
		}
		memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_GetHistoInfo(LX_PE_HDR_HISTO_INFO_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, buf_id;
	do {
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);
		if (pstParams->win_id == LX_PE_WIN_0)
		{
			rmb();
			buf_id = gPE_HDR_DDR_O24->stat0.hist_cnt;
			rmb();

			PE_PRINT_HDR_HIST("buf_id_0:%d\n",buf_id);

			if (buf_id == 1) {
				for(i=0;i<128;i++)
				{
					pstParams->status[i] = gPE_HDR_DDR_O24->stat0.hist_1[i];
					pstParams->status[i+128] = pstParams->status[i];
				}
			}
			else if (buf_id == 2) {
				for(i=0;i<128;i++)
				{
					pstParams->status[i] = gPE_HDR_DDR_O24->stat0.hist_2[i];
					pstParams->status[i+128] = pstParams->status[i];
				}
			}
			else if (buf_id == 3) {
				for(i=0;i<128;i++)
				{
					pstParams->status[i] = gPE_HDR_DDR_O24->stat0.hist_3[i];
					pstParams->status[i+128] = pstParams->status[i];
				}
			}
			else {
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
				PE_H10_0_O24_Wr(hdr_hist_ia_ctrl,0x00011000);
				PE_H10_0_O24_WrFL(hdr_hist_ia_ctrl);
				//rd histogram
				for(i=0;i<128;i++)
				{
					PE_H10_0_O24_RdFL(hdr_hist_ia_data1);
					pstParams->status[i] = PE_H10_0_O24_Rd(hdr_hist_ia_data1);
					pstParams->status[i+128] = pstParams->status[i];
				}
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
				PE_H10_0_O24_Wr(hdr_hist_ia_ctrl,0x00018000);
				PE_H10_0_O24_WrFL(hdr_hist_ia_ctrl);
			}
			rmb();
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			rmb();
			buf_id = gPE_HDR_DDR_O24->stat1.hist_cnt;
			rmb();

			PE_PRINT_HDR_HIST("buf_id_1:%d\n",buf_id);

			if (buf_id == 1) {
				for(i=0;i<128;i++)
				{
					pstParams->status[i] = gPE_HDR_DDR_O24->stat1.hist_1[i];
					pstParams->status[i+128] = pstParams->status[i];
				}
			}
			else if (buf_id == 2) {
				for(i=0;i<128;i++)
				{
					pstParams->status[i] = gPE_HDR_DDR_O24->stat1.hist_2[i];
					pstParams->status[i+128] = pstParams->status[i];
				}
			}
			else if (buf_id == 3) {
				for(i=0;i<128;i++)
				{
					pstParams->status[i] = gPE_HDR_DDR_O24->stat1.hist_3[i];
					pstParams->status[i+128] = pstParams->status[i];
				}
			}
			else {
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
				PE_H10_1_O24_Wr(hdr_hist_ia_ctrl,0x00011000);
				PE_H10_1_O24_WrFL(hdr_hist_ia_ctrl);
				//rd histogram
				for(i=0;i<128;i++)
				{
					PE_H10_1_O24_RdFL(hdr_hist_ia_data1);
					pstParams->status[i] = PE_H10_1_O24_Rd(hdr_hist_ia_data1);
					pstParams->status[i+128] = pstParams->status[i];
				}
				/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
				PE_H10_1_O24_Wr(hdr_hist_ia_ctrl,0x00018000);
				PE_H10_1_O24_WrFL(hdr_hist_ia_ctrl);
			}
			rmb();
		}
		else if (pstParams->win_id == LX_PE_WIN_2)
		{
			/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
			PE_H10_0_O24_Wr(hdr_hist_ia_ctrl,0x00011000);
			PE_H10_0_O24_WrFL(hdr_hist_ia_ctrl);
			//rd histogram
			for(i=0;i<128;i++)
			{
				PE_H10_0_O24_RdFL(hdr_hist_ia_data1);
				pstParams->status[i] = PE_H10_0_O24_Rd(hdr_hist_ia_data1);
				pstParams->status[i+128] = pstParams->status[i];
			}
			/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:1,[12]hif_hist_ai:0,[4:0]hif_hist_address:0 */
			PE_H10_0_O24_Wr(hdr_hist_ia_ctrl,0x00018000);
			PE_H10_0_O24_WrFL(hdr_hist_ia_ctrl);
		}
		else if (pstParams->win_id == LX_PE_WIN_3)
		{
			/* [28]hif_status_ai:0,[18:16]hif_status_address:1,[15]hif_hist_enable:0,[12]hif_hist_ai:1,[4:0]hif_hist_address:0 */
			PE_H10_1_O24_Wr(hdr_hist_ia_ctrl,0x00011000);
			PE_H10_1_O24_WrFL(hdr_hist_ia_ctrl);
			//rd histogram
			for(i=0;i<128;i++)
			{
				PE_H10_1_O24_RdFL(hdr_hist_ia_data1);
				pstParams->status[i] = PE_H10_1_O24_Rd(hdr_hist_ia_data1);
				pstParams->status[i+128] = pstParams->status[i];
			}
			PE_H10_1_O24_Wr01(hdr_hist_ia_ctrl,hif_hist_enable,0x1);
			PE_H10_1_O24_WrFL(hdr_hist_ia_ctrl);
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_SetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, count=0, connect, oper;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);
		PE_HDR_HW_O24_CHECK_CODE((pstParams->size!=1024),break,"size(%d) is wrong\n",pstParams->size);
		PE_DBG_HDR("[wid:%d] oper:0x%x, size:%d\n",pstParams->win_id,pstParams->oper,pstParams->size);

		connect = PE_HDR_HW_O24_GetConnectMode(pstParams->win_id);

		oper = pstParams->oper&0xF;//operation, [11:8]version [7:4]ctrl [3:0]hdrpath

		if (oper==0xA)			connect = PE_HDR_HW_O24_CONNECT_MODE_HLG;
		else if (oper==0xB)		connect = PE_HDR_HW_O24_CONNECT_MODE_H10;
		else if (oper>=0xC)		break;

		if (pstParams->win_id == LX_PE_WIN_0)
		{
			/* EOTF : 0:HLG, 1:HDR10, 2,3:disable */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				wmb();
				for (i=0; i<1024; i++)
				{
					gPE_HDR_DDR_O24->lut0.eotf_0[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_EOTF,0);
			}
			else
			{
				wmb();
				for (i=0; i<1024; i++)
				{
					gPE_HDR_DDR_O24->lut0.eotf_1[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_EOTF,1);
			}
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			/* EOTF : 0:HLG, 1:HDR10, 2,3:disable */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				wmb();
				for (i=0; i<1024; i++)
				{
					gPE_HDR_DDR_O24->lut1.eotf_0[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_EOTF,0);
			}
			else
			{
				wmb();
				for (i=0; i<1024; i++)
				{
					gPE_HDR_DDR_O24->lut1.eotf_1[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_EOTF,1);
			}
		}

		PE_HDR_HW_O24_BACKUP_TRACE("E%d]%s)%x,%2d|%x,%x,%x~%x,%x",\
			pstParams->win_id,PE_HDR_HW_O24_CONNECT_TO_STR(connect),pstParams->oper,count,\
			pstParams->data[0],pstParams->data[1],pstParams->data[2],pstParams->data[1022],pstParams->data[1023]);
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_GetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, connect;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);
		PE_HDR_HW_O24_CHECK_CODE((pstParams->size!=1024),break,"size(%d) is wrong\n",pstParams->size);
		PE_DBG_HDR("[wid:%d] oper:0x%x, size:%d\n",pstParams->win_id,pstParams->oper,pstParams->size);

		connect = PE_HDR_HW_O24_GetConnectMode(pstParams->win_id);

		if (pstParams->win_id == LX_PE_WIN_0)
		{
			/* EOTF : 0:HLG, 1:HDR10, 2,3:disable */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				rmb();
				for (i=0; i<1024; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_O24->lut0.eotf_0[i];
				}
				rmb();
			}
			else
			{
				rmb();
				for (i=0; i<1024; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_O24->lut0.eotf_1[i];
				}
				rmb();
			}
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			/* EOTF : 0:HLG, 1:HDR10, 2,3:disable */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				rmb();
				for (i=0; i<1024; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_O24->lut1.eotf_0[i];
				}
				rmb();
			}
			else
			{
				rmb();
				for (i=0; i<1024; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_O24->lut1.eotf_1[i];
				}
				rmb();
			}
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_SetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, count=0, connect, oper;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);
		PE_HDR_HW_O24_CHECK_CODE((pstParams->size!=1024),break,"size(%d) is wrong\n",pstParams->size);
		PE_DBG_HDR("[wid:%d] oper:0x%x, size:%d\n",pstParams->win_id,pstParams->oper,pstParams->size);

		connect = PE_HDR_HW_O24_GetConnectMode(pstParams->win_id);

		oper = pstParams->oper&0xF;//operation, [11:8]version [7:4]ctrl [3:0]hdrpath

		if (oper==0xA)			connect = PE_HDR_HW_O24_CONNECT_MODE_HLG;
		else if (oper==0xB)		connect = PE_HDR_HW_O24_CONNECT_MODE_H10;
		else if (oper>=0xC)		break;

		if (pstParams->win_id == LX_PE_WIN_0)
		{
			/* OETF : 0:HLG, 1:HDR10, 2,3:disable */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				wmb();
				for (i=0; i<1024; i++)
				{
					gPE_HDR_DDR_O24->lut0.oetf_0[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_OETF,0);
			}
			else
			{
				wmb();
				for (i=0; i<1024; i++)
				{
					gPE_HDR_DDR_O24->lut0.oetf_1[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_OETF,1);
			}
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			/* OETF : 0:HLG, 1:HDR10, 2,3:disable */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				wmb();
				for (i=0; i<1024; i++)
				{
					gPE_HDR_DDR_O24->lut1.oetf_0[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_OETF,0);
			}
			else
			{
				wmb();
				for (i=0; i<1024; i++)
				{
					gPE_HDR_DDR_O24->lut1.oetf_1[i] = pstParams->data[i];
				}
				wmb();
				count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_OETF,1);
			}
		}

		PE_HDR_HW_O24_BACKUP_TRACE("O%d]%s)%x,%2d|%x,%x,%x~%x,%x",\
			pstParams->win_id,PE_HDR_HW_O24_CONNECT_TO_STR(connect),pstParams->oper,count,\
			pstParams->data[0],pstParams->data[1],pstParams->data[2],pstParams->data[1022],pstParams->data[1023]);
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_GetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, connect;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);
		PE_HDR_HW_O24_CHECK_CODE((pstParams->size!=1024),break,"size(%d) is wrong\n",pstParams->size);
		PE_DBG_HDR("[wid:%d] oper:0x%x, size:%d\n",pstParams->win_id,pstParams->oper,pstParams->size);

		connect = PE_HDR_HW_O24_GetConnectMode(pstParams->win_id);

		if (pstParams->win_id == LX_PE_WIN_0)
		{
			/* OETF : 0:HLG, 1:HDR10, 2,3:disable */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				rmb();
				for (i=0; i<1024; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_O24->lut0.oetf_0[i];
				}
				rmb();
			}
			else
			{
				rmb();
				for (i=0; i<1024; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_O24->lut0.oetf_1[i];
				}
				rmb();
			}
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			/* OETF : 0:HLG, 1:HDR10, 2,3:disable */
			if (connect == PE_HDR_HW_O24_CONNECT_MODE_HLG)
			{
				rmb();
				for (i=0; i<1024; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_O24->lut1.oetf_0[i];
				}
				rmb();
			}
			else
			{
				rmb();
				for (i=0; i<1024; i++)
				{
					pstParams->data[i] = gPE_HDR_DDR_O24->lut1.oetf_1[i];
				}
				rmb();
			}
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_SetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i, cur_hdr_info;
	static UINT32 pre_support = 0;
	PE_HDR_HW_O24_SETTINGS_T *pInfo=&_g_pe_hdr_hw_o24_info;
	LX_PE_HDR_OP_MD_T op;
	PE_HDR_DDR_INFO_O24_T head_info;

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_HDR_DDR_O24);
		PE_DBG_HDR("set[%d] : data[0]:0x%08x\n",pstParams->win_id,pstParams->data[0]);
		for (i=0;i<LX_PE_WIN_ALL;i++)
		{
			if (pstParams->win_id==i)
			{
				memcpy(&(pInfo->md_inf[i]),pstParams, sizeof(LX_PE_HDR_MODE_INFO_T));
			}
		}
		if (pstParams->win_id == LX_PE_WIN_0)
		{
			op.udata32 = pInfo->md_inf[LX_PE_WIN_0].data[0];
			/* set support info */
			if (pre_support != op.sup_mod) {
				wmb();rmb();
				head_info.udata32 = gPE_HDR_DDR_O24->head.info.udata32;
				head_info.support = op.sup_mod;
				gPE_HDR_DDR_O24->head.info.udata32 = head_info.udata32;
				wmb();
				pre_support = op.sup_mod;
			}
			/* set hdr_off */
			cur_hdr_info = op.hdr_off;
			ret = PE_FWI_O24_SetHdrInfo(&cur_hdr_info);
			PE_HDR_HW_O24_CHECK_CODE(ret,break,"PE_FWI_O24_SetHdrInfo() error\n");
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_GetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 i, hdr_mode;
	PE_HDR_HW_O24_SETTINGS_T *pInfo=&_g_pe_hdr_hw_o24_info;
	LX_PE_HDR_OP_MD_T op;
	do{
		CHECK_KNULL(pstParams);
		if (pstParams->win_id == LX_PE_WIN_0)
		{
			op.udata32 = pInfo->md_inf[LX_PE_WIN_0].data[0];
			hdr_mode = 0;
			ret = PE_FWI_O24_GetHdrMode(&hdr_mode);
			PE_HDR_HW_O24_CHECK_CODE(ret,break,"PE_FWI_O24_GetHdrMode() error\n");
			op.cur_mod = hdr_mode;
			pInfo->md_inf[LX_PE_WIN_0].data[0] = op.udata32;
		}
		for (i=0;i<LX_PE_WIN_ALL;i++)
		{
			if (pstParams->win_id==i)
			{
				win_id = pstParams->win_id;
				memcpy(pstParams,&(pInfo->md_inf[i]),sizeof(LX_PE_HDR_MODE_INFO_T));
				pstParams->win_id = win_id;
			}
		}
	} while(0);
	return ret;
}

int PE_HDR_HW_O24_SetColorCorrect(LX_PE_HDR_CCR_T *pstParams)
{
	int ret = RET_OK;
	PE_HDR_HW_O24_SETTINGS_T *pInfo=&_g_pe_hdr_hw_o24_info;
	PE_O24_REG_H10_HUE_SAT_CTRL_T hdr_hue_sat_ctrl;
	UINT32 count = 0;
	do{
		CHECK_KNULL(pstParams);
		PE_DBG_HDR("set[%d]:%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x\n", \
			pstParams->win_id,pstParams->data[0],pstParams->data[1],\
			pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
			pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
			pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);

		if (pstParams->win_id == LX_PE_WIN_0)
		{
			wmb();
			hdr_hue_sat_ctrl.udata32 = 0;
			hdr_hue_sat_ctrl.reg_hue_prsv_en = pInfo->reg_hue_prsv_en;
			hdr_hue_sat_ctrl.reg_sat_prsv_en = pInfo->reg_sat_prsv_en;
			hdr_hue_sat_ctrl.reg_hue_prsv_ratio = pstParams->data[0];
			hdr_hue_sat_ctrl.reg_sat_prsv_ratio = pstParams->data[1];
			gPE_HDR_DDR_O24->lut0.ccr_0[0]  = hdr_hue_sat_ctrl.udata32;
			gPE_HDR_DDR_O24->lut0.ccr_0[1]  = pstParams->data[6];
			gPE_HDR_DDR_O24->lut0.ccr_0[2]  = pstParams->data[7];
			gPE_HDR_DDR_O24->lut0.ccr_0[3]  = pstParams->data[8];
			gPE_HDR_DDR_O24->lut0.ccr_0[4]  = pstParams->data[9];
			gPE_HDR_DDR_O24->lut0.ccr_0[5]  = pstParams->data[10];
			gPE_HDR_DDR_O24->lut0.ccr_0[6]  = pstParams->data[11];
			gPE_HDR_DDR_O24->lut0.ccr_0[7]  = pstParams->data[12];
			gPE_HDR_DDR_O24->lut0.ccr_0[8]  = pstParams->data[13];
			gPE_HDR_DDR_O24->lut0.ccr_0[9]  = pstParams->data[14];
			gPE_HDR_DDR_O24->lut0.ccr_0[10] = pstParams->data[15];
			gPE_HDR_DDR_O24->lut0.ccr_0[11] = pstParams->data[16];
			gPE_HDR_DDR_O24->lut0.ccr_0[12] = pstParams->data[17];
			gPE_HDR_DDR_O24->lut0.ccr_0[13] = pstParams->data[18];
			gPE_HDR_DDR_O24->lut0.ccr_0[14] = pstParams->data[19];
			gPE_HDR_DDR_O24->lut0.ccr_0[15] = pstParams->data[20];
			gPE_HDR_DDR_O24->lut0.ccr_0[16] = pstParams->data[21];
			wmb();
			count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_CCR,0);

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

			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;

				PE_CHPI_APB0_O24F22_Wr(hs.hdr_hue_sat_ctrl.reg_hue_prsv_ratio,pstParams->data[0]);
				PE_CHPI_APB0_O24F22_Wr(hs.hdr_hue_sat_ctrl.reg_sat_prsv_ratio,pstParams->data[1]);
				PE_CHPI_APB0_O24F22_WrFL(hs.hdr_hue_sat_ctrl.udata32);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_00.udata32,pstParams->data[6]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_01.udata32,pstParams->data[7]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_02.udata32,pstParams->data[8]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_03.udata32,pstParams->data[9]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_04.udata32,pstParams->data[10]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_05.udata32,pstParams->data[11]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_06.udata32,pstParams->data[12]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_lgain_lut_ctrl_07.udata32,pstParams->data[13]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_00.udata32,pstParams->data[14]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_01.udata32,pstParams->data[15]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_02.udata32,pstParams->data[16]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_03.udata32,pstParams->data[17]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_04.udata32,pstParams->data[18]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_05.udata32,pstParams->data[19]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_06.udata32,pstParams->data[20]);
				PE_CHPI_APB0_O24F22_QWr(hs.hdr_sgain_lut_ctrl_07.udata32,pstParams->data[21]);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_HS);
			} while(0);
			#endif
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			wmb();
			hdr_hue_sat_ctrl.udata32 = 0;
			hdr_hue_sat_ctrl.reg_hue_prsv_en = pInfo->reg_hue_prsv_en;
			hdr_hue_sat_ctrl.reg_sat_prsv_en = pInfo->reg_sat_prsv_en;
			hdr_hue_sat_ctrl.reg_hue_prsv_ratio = pstParams->data[0];
			hdr_hue_sat_ctrl.reg_sat_prsv_ratio = pstParams->data[1];
			gPE_HDR_DDR_O24->lut1.ccr_0[0]  = hdr_hue_sat_ctrl.udata32;
			gPE_HDR_DDR_O24->lut1.ccr_0[1]  = pstParams->data[6];
			gPE_HDR_DDR_O24->lut1.ccr_0[2]  = pstParams->data[7];
			gPE_HDR_DDR_O24->lut1.ccr_0[3]  = pstParams->data[8];
			gPE_HDR_DDR_O24->lut1.ccr_0[4]  = pstParams->data[9];
			gPE_HDR_DDR_O24->lut1.ccr_0[5]  = pstParams->data[10];
			gPE_HDR_DDR_O24->lut1.ccr_0[6]  = pstParams->data[11];
			gPE_HDR_DDR_O24->lut1.ccr_0[7]  = pstParams->data[12];
			gPE_HDR_DDR_O24->lut1.ccr_0[8]  = pstParams->data[13];
			gPE_HDR_DDR_O24->lut1.ccr_0[9]  = pstParams->data[14];
			gPE_HDR_DDR_O24->lut1.ccr_0[10] = pstParams->data[15];
			gPE_HDR_DDR_O24->lut1.ccr_0[11] = pstParams->data[16];
			gPE_HDR_DDR_O24->lut1.ccr_0[12] = pstParams->data[17];
			gPE_HDR_DDR_O24->lut1.ccr_0[13] = pstParams->data[18];
			gPE_HDR_DDR_O24->lut1.ccr_0[14] = pstParams->data[19];
			gPE_HDR_DDR_O24->lut1.ccr_0[15] = pstParams->data[20];
			gPE_HDR_DDR_O24->lut1.ccr_0[16] = pstParams->data[21];
			wmb();
			count = PE_HDR_HW_O24_IncCount(pstParams->win_id,PE_HDR_DDR_O24_CNT_CCR,0);
		}

		PE_HDR_HW_O24_BACKUP_TRACE("CC%d]%2d|%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x", \
			pstParams->win_id,count,pstParams->data[0],pstParams->data[1],\
			pstParams->data[2],pstParams->data[3],pstParams->data[4],pstParams->data[5],\
			pstParams->data[6],pstParams->data[7],pstParams->data[12],pstParams->data[13],\
			pstParams->data[14],pstParams->data[15],pstParams->data[20],pstParams->data[21]);
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
int PE_HDR_HW_O24_GetColorCorrect(LX_PE_HDR_CCR_T *pstParams)
{
	int ret = RET_OK;
	PE_O24_REG_H10_HUE_SAT_CTRL_T hdr_hue_sat_ctrl;
	do{
		CHECK_KNULL(pstParams);
		if (pstParams->win_id == LX_PE_WIN_0)
		{
			PE_H10_0_O24_RdFL(hdr_hue_sat_ctrl);
			PE_H10_0_O24_Rd01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
			PE_H10_0_O24_Rd01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
			PE_H10_0_O24_RdFL(hdr_hue_sat_alpha_ctrl);
			PE_H10_0_O24_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pstParams->data[2]);
			PE_H10_0_O24_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pstParams->data[3]);
			PE_H10_0_O24_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pstParams->data[4]);
			PE_H10_0_O24_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pstParams->data[5]);
			PE_H10_0_O24_RdFL(hdr_lgain_lut_ctrl_00);
			PE_H10_0_O24_RdFL(hdr_lgain_lut_ctrl_01);
			PE_H10_0_O24_RdFL(hdr_lgain_lut_ctrl_02);
			PE_H10_0_O24_RdFL(hdr_lgain_lut_ctrl_03);
			PE_H10_0_O24_RdFL(hdr_lgain_lut_ctrl_04);
			PE_H10_0_O24_RdFL(hdr_lgain_lut_ctrl_05);
			PE_H10_0_O24_RdFL(hdr_lgain_lut_ctrl_06);
			PE_H10_0_O24_RdFL(hdr_lgain_lut_ctrl_07);
			PE_H10_0_O24_RdFL(hdr_sgain_lut_ctrl_00);
			PE_H10_0_O24_RdFL(hdr_sgain_lut_ctrl_01);
			PE_H10_0_O24_RdFL(hdr_sgain_lut_ctrl_02);
			PE_H10_0_O24_RdFL(hdr_sgain_lut_ctrl_03);
			PE_H10_0_O24_RdFL(hdr_sgain_lut_ctrl_04);
			PE_H10_0_O24_RdFL(hdr_sgain_lut_ctrl_05);
			PE_H10_0_O24_RdFL(hdr_sgain_lut_ctrl_06);
			PE_H10_0_O24_RdFL(hdr_sgain_lut_ctrl_07);
			pstParams->data[6]  = PE_H10_0_O24_Rd(hdr_lgain_lut_ctrl_00);
			pstParams->data[7]  = PE_H10_0_O24_Rd(hdr_lgain_lut_ctrl_01);
			pstParams->data[8]  = PE_H10_0_O24_Rd(hdr_lgain_lut_ctrl_02);
			pstParams->data[9]  = PE_H10_0_O24_Rd(hdr_lgain_lut_ctrl_03);
			pstParams->data[10] = PE_H10_0_O24_Rd(hdr_lgain_lut_ctrl_04);
			pstParams->data[11] = PE_H10_0_O24_Rd(hdr_lgain_lut_ctrl_05);
			pstParams->data[12] = PE_H10_0_O24_Rd(hdr_lgain_lut_ctrl_06);
			pstParams->data[13] = PE_H10_0_O24_Rd(hdr_lgain_lut_ctrl_07);
			pstParams->data[14] = PE_H10_0_O24_Rd(hdr_sgain_lut_ctrl_00);
			pstParams->data[15] = PE_H10_0_O24_Rd(hdr_sgain_lut_ctrl_01);
			pstParams->data[16] = PE_H10_0_O24_Rd(hdr_sgain_lut_ctrl_02);
			pstParams->data[17] = PE_H10_0_O24_Rd(hdr_sgain_lut_ctrl_03);
			pstParams->data[18] = PE_H10_0_O24_Rd(hdr_sgain_lut_ctrl_04);
			pstParams->data[19] = PE_H10_0_O24_Rd(hdr_sgain_lut_ctrl_05);
			pstParams->data[20] = PE_H10_0_O24_Rd(hdr_sgain_lut_ctrl_06);
			pstParams->data[21] = PE_H10_0_O24_Rd(hdr_sgain_lut_ctrl_07);
		}
		else if (pstParams->win_id == LX_PE_WIN_1)
		{
			PE_H10_1_O24_RdFL(hdr_hue_sat_ctrl);
			PE_H10_1_O24_Rd01(hdr_hue_sat_ctrl,reg_hue_prsv_ratio,pstParams->data[0]);
			PE_H10_1_O24_Rd01(hdr_hue_sat_ctrl,reg_sat_prsv_ratio,pstParams->data[1]);
			PE_H10_1_O24_RdFL(hdr_hue_sat_alpha_ctrl);
			PE_H10_1_O24_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_sgain_sel,pstParams->data[2]);
			PE_H10_1_O24_Rd01(hdr_hue_sat_alpha_ctrl,reg_out_lgain_sel,pstParams->data[3]);
			PE_H10_1_O24_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_s_sel,pstParams->data[4]);
			PE_H10_1_O24_Rd01(hdr_hue_sat_alpha_ctrl,reg_inp_l_sel,pstParams->data[5]);
			PE_H10_1_O24_RdFL(hdr_lgain_lut_ctrl_00);
			PE_H10_1_O24_RdFL(hdr_lgain_lut_ctrl_01);
			PE_H10_1_O24_RdFL(hdr_lgain_lut_ctrl_02);
			PE_H10_1_O24_RdFL(hdr_lgain_lut_ctrl_03);
			PE_H10_1_O24_RdFL(hdr_lgain_lut_ctrl_04);
			PE_H10_1_O24_RdFL(hdr_lgain_lut_ctrl_05);
			PE_H10_1_O24_RdFL(hdr_lgain_lut_ctrl_06);
			PE_H10_1_O24_RdFL(hdr_lgain_lut_ctrl_07);
			PE_H10_1_O24_RdFL(hdr_sgain_lut_ctrl_00);
			PE_H10_1_O24_RdFL(hdr_sgain_lut_ctrl_01);
			PE_H10_1_O24_RdFL(hdr_sgain_lut_ctrl_02);
			PE_H10_1_O24_RdFL(hdr_sgain_lut_ctrl_03);
			PE_H10_1_O24_RdFL(hdr_sgain_lut_ctrl_04);
			PE_H10_1_O24_RdFL(hdr_sgain_lut_ctrl_05);
			PE_H10_1_O24_RdFL(hdr_sgain_lut_ctrl_06);
			PE_H10_1_O24_RdFL(hdr_sgain_lut_ctrl_07);
			pstParams->data[6]  = PE_H10_1_O24_Rd(hdr_lgain_lut_ctrl_00);
			pstParams->data[7]  = PE_H10_1_O24_Rd(hdr_lgain_lut_ctrl_01);
			pstParams->data[8]  = PE_H10_1_O24_Rd(hdr_lgain_lut_ctrl_02);
			pstParams->data[9]  = PE_H10_1_O24_Rd(hdr_lgain_lut_ctrl_03);
			pstParams->data[10] = PE_H10_1_O24_Rd(hdr_lgain_lut_ctrl_04);
			pstParams->data[11] = PE_H10_1_O24_Rd(hdr_lgain_lut_ctrl_05);
			pstParams->data[12] = PE_H10_1_O24_Rd(hdr_lgain_lut_ctrl_06);
			pstParams->data[13] = PE_H10_1_O24_Rd(hdr_lgain_lut_ctrl_07);
			pstParams->data[14] = PE_H10_1_O24_Rd(hdr_sgain_lut_ctrl_00);
			pstParams->data[15] = PE_H10_1_O24_Rd(hdr_sgain_lut_ctrl_01);
			pstParams->data[16] = PE_H10_1_O24_Rd(hdr_sgain_lut_ctrl_02);
			pstParams->data[17] = PE_H10_1_O24_Rd(hdr_sgain_lut_ctrl_03);
			pstParams->data[18] = PE_H10_1_O24_Rd(hdr_sgain_lut_ctrl_04);
			pstParams->data[19] = PE_H10_1_O24_Rd(hdr_sgain_lut_ctrl_05);
			pstParams->data[20] = PE_H10_1_O24_Rd(hdr_sgain_lut_ctrl_06);
			pstParams->data[21] = PE_H10_1_O24_Rd(hdr_sgain_lut_ctrl_07);
		}
		else if (pstParams->win_id == LX_PE_WIN_2)
		{
			rmb();
			hdr_hue_sat_ctrl.udata32 = gPE_HDR_DDR_O24->lut0.ccr_0[0];
			pstParams->data[0]  = hdr_hue_sat_ctrl.reg_hue_prsv_ratio;
			pstParams->data[1]  = hdr_hue_sat_ctrl.reg_sat_prsv_ratio;
			pstParams->data[6]  = gPE_HDR_DDR_O24->lut0.ccr_0[1];
			pstParams->data[7]  = gPE_HDR_DDR_O24->lut0.ccr_0[2];
			pstParams->data[8]  = gPE_HDR_DDR_O24->lut0.ccr_0[3];
			pstParams->data[9]  = gPE_HDR_DDR_O24->lut0.ccr_0[4];
			pstParams->data[10] = gPE_HDR_DDR_O24->lut0.ccr_0[5];
			pstParams->data[11] = gPE_HDR_DDR_O24->lut0.ccr_0[6];
			pstParams->data[12] = gPE_HDR_DDR_O24->lut0.ccr_0[7];
			pstParams->data[13] = gPE_HDR_DDR_O24->lut0.ccr_0[8];
			pstParams->data[14] = gPE_HDR_DDR_O24->lut0.ccr_0[9];
			pstParams->data[15] = gPE_HDR_DDR_O24->lut0.ccr_0[10];
			pstParams->data[16] = gPE_HDR_DDR_O24->lut0.ccr_0[11];
			pstParams->data[17] = gPE_HDR_DDR_O24->lut0.ccr_0[12];
			pstParams->data[18] = gPE_HDR_DDR_O24->lut0.ccr_0[13];
			pstParams->data[19] = gPE_HDR_DDR_O24->lut0.ccr_0[14];
			pstParams->data[20] = gPE_HDR_DDR_O24->lut0.ccr_0[15];
			pstParams->data[21] = gPE_HDR_DDR_O24->lut0.ccr_0[16];
			rmb();
		}
		else if (pstParams->win_id == LX_PE_WIN_3)
		{
			rmb();
			hdr_hue_sat_ctrl.udata32 = gPE_HDR_DDR_O24->lut1.ccr_0[0];
			pstParams->data[0]  = hdr_hue_sat_ctrl.reg_hue_prsv_ratio;
			pstParams->data[1]  = hdr_hue_sat_ctrl.reg_sat_prsv_ratio;
			pstParams->data[6]  = gPE_HDR_DDR_O24->lut1.ccr_0[1];
			pstParams->data[7]  = gPE_HDR_DDR_O24->lut1.ccr_0[2];
			pstParams->data[8]  = gPE_HDR_DDR_O24->lut1.ccr_0[3];
			pstParams->data[9]  = gPE_HDR_DDR_O24->lut1.ccr_0[4];
			pstParams->data[10] = gPE_HDR_DDR_O24->lut1.ccr_0[5];
			pstParams->data[11] = gPE_HDR_DDR_O24->lut1.ccr_0[6];
			pstParams->data[12] = gPE_HDR_DDR_O24->lut1.ccr_0[7];
			pstParams->data[13] = gPE_HDR_DDR_O24->lut1.ccr_0[8];
			pstParams->data[14] = gPE_HDR_DDR_O24->lut1.ccr_0[9];
			pstParams->data[15] = gPE_HDR_DDR_O24->lut1.ccr_0[10];
			pstParams->data[16] = gPE_HDR_DDR_O24->lut1.ccr_0[11];
			pstParams->data[17] = gPE_HDR_DDR_O24->lut1.ccr_0[12];
			pstParams->data[18] = gPE_HDR_DDR_O24->lut1.ccr_0[13];
			pstParams->data[19] = gPE_HDR_DDR_O24->lut1.ccr_0[14];
			pstParams->data[20] = gPE_HDR_DDR_O24->lut1.ccr_0[15];
			pstParams->data[21] = gPE_HDR_DDR_O24->lut1.ccr_0[16];
			rmb();
		}

		PE_DBG_HDR("get[%d]:%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x\n", \
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

int PE_HDR_HW_O24_SetPattern(void *pstParams)
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

		PE_DBG_HDR("on:%d,mode:%d\n",p->bOnOff,p->eMode);
		PE_DBG_HDR("grad num:%d,mode:%d\n",p->stGradInfo.numGrad,p->stGradInfo.eGradMode);
		for (i=0; i<p->stGradInfo.numGrad; i++)
		{
			PE_DBG_HDR("[%d] %d, %x,%x,%x, %x,%x,%x, %x\n",i,\
				p->stGradInfo.stLineAttr[i].lineIdx,p->stGradInfo.stLineAttr[i].start_R,\
				p->stGradInfo.stLineAttr[i].start_G,p->stGradInfo.stLineAttr[i].start_B,\
				p->stGradInfo.stLineAttr[i].step_R,p->stGradInfo.stLineAttr[i].step_G,\
				p->stGradInfo.stLineAttr[i].step_B,p->stGradInfo.stLineAttr[i].strideSize);
		}
		PE_DBG_HDR("winbox num:%d\n",p->stWinboxInfo.u8NumWin);
		for (i=0; i<p->stWinboxInfo.u8NumWin; i++)
		{
			PE_DBG_HDR("[%d] %d, %d,%d,%d,%d, %x,%x,%x\n",i,\
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
		ret = PE_FWI_O24_SetPattern(&en_type);
		PE_HDR_HW_O24_CHECK_CODE(ret,break,"PE_FWI_O24_SetPattern() error\n");

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
		PE_H10_0_O24_RdFL(hdr_top_ctrl_01);
		PE_H10_0_O24_Rd01(hdr_top_ctrl_01,width,size_x);
		PE_H10_0_O24_Rd01(hdr_top_ctrl_01,height,size_y);

		ratio_x = (size_x<<10)/EXT_HDR_PATTERN_WIDTH;
		ratio_y = (size_y<<10)/EXT_HDR_PATTERN_HEIGHT;

		PE_DBG_HDR("num:%d,%d, en,typ:%d,%d, grd,h_g:0x%x,%d, strd:%d\n",\
			num_win,num_grd,enable,type,grad_en,h_grad,stride);
		PE_DBG_HDR("size:%d,%d, flag:0x%x, ratio:%d,%d\n",\
			size_x,size_y,mask_flag,ratio_x,ratio_y);

		#if 0	//20200130, need to confirm
		if (size_x>=3840)			stride = 3;
		else if (size_x>=1920)		stride = 2;
		else if (size_x>=960)		stride = 1;
		else						stride = 0;
		#endif

		do {
			/* PE_H10_E */
			PE_H10_0_O24_RdFL(hdr_tpg_ctrl_00);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_00,tpg_enable,0);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_00,tpg_type,type);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_00,tpg_grad_en,grad_en)
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_00,tpg_h_grad,h_grad);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_00,tpg_stride,stride);
			PE_H10_0_O24_WrFL(hdr_tpg_ctrl_00);
			OS_MsecSleep(30);

			PE_H10_0_O24_RdFL(hdr_tpg_ctrl_01);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_01,tpg_size_x,size_x);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_01,tpg_size_y,size_y);
			PE_H10_0_O24_WrFL(hdr_tpg_ctrl_01);

			PE_H10_0_O24_RdFL(hdr_tpg_ctrl_02);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_02,tpg_mask_flag,mask_flag);
			PE_H10_0_O24_WrFL(hdr_tpg_ctrl_02);

			PE_H10_0_O24_RdFL(hdr_tpg_ctrl_03);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_03,tpg_in_out_sel,0x0);
			PE_H10_0_O24_WrFL(hdr_tpg_ctrl_03);

			PE_H10_0_O24_RdFL(hdr_tpg_ctrl_04);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_04,tpg_color_r,0x0);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_04,tpg_color_b,0x0);
			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_04,tpg_color_g,0x0);
			PE_H10_0_O24_WrFL(hdr_tpg_ctrl_04);

			PE_H10_0_O24_QWr(hdr_tpg_ia_ctrl,0x00001000);//patch color
			for (i=0; i<num_win; i++)
			{
				wr_data = p->stWinboxInfo.stWinBoxAttr[i].fill_R;
				wr_data |= (p->stWinboxInfo.stWinBoxAttr[i].fill_B << 10);
				wr_data |= (p->stWinboxInfo.stWinBoxAttr[i].fill_G << 20);
				PE_DBG_HDR("H10_0[%d]win color:0x%08x\n",i,wr_data);
				PE_H10_0_O24_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_0_O24_QWr(hdr_tpg_ia_ctrl,0x00001020);//patch start (x,y)
			for (i=0; i<num_win; i++)
			{
				wr_data = (p->stWinboxInfo.stWinBoxAttr[i].y*ratio_y)>>10;
				wr_data |= (((p->stWinboxInfo.stWinBoxAttr[i].x*ratio_x)>>10) << 16);
				PE_H10_0_O24_QWr(hdr_tpg_ia_data,wr_data);
				PE_DBG_HDR("H10_0[%d]win start:0x%08x\n",i,wr_data);
			}
			PE_H10_0_O24_QWr(hdr_tpg_ia_ctrl,0x00001040);//patch end (x,y)

			for (i=0; i<num_win; i++)
			{
				wr_data = ((p->stWinboxInfo.stWinBoxAttr[i].y + p->stWinboxInfo.stWinBoxAttr[i].h)*ratio_y)>>10;
				wr_data |= ((((p->stWinboxInfo.stWinBoxAttr[i].x + p->stWinboxInfo.stWinBoxAttr[i].w)*ratio_x)>>10) << 16);
				PE_DBG_HDR("H10_0[%d]win end  :0x%08x\n",i,wr_data);
				PE_H10_0_O24_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_0_O24_QWr(hdr_tpg_ia_ctrl,0x00001060);//gradation start color
			for (i=0; i<num_grd; i++)
			{
				wr_data = p->stGradInfo.stLineAttr[i].start_R;
				wr_data |= (p->stGradInfo.stLineAttr[i].start_B << 10);
				wr_data |= (p->stGradInfo.stLineAttr[i].start_G << 20);
				PE_DBG_HDR("H10_0[%d]grd start:0x%08x\n",i,wr_data);
				PE_H10_0_O24_QWr(hdr_tpg_ia_data,wr_data);
			}
			PE_H10_0_O24_QWr(hdr_tpg_ia_ctrl,0x00001064);//gradation step color
			for (i=0; i<num_grd; i++)
			{
				wr_data = p->stGradInfo.stLineAttr[i].step_R;
				wr_data |= (p->stGradInfo.stLineAttr[i].step_B << 10);
				wr_data |= (p->stGradInfo.stLineAttr[i].step_G << 20);
				PE_DBG_HDR("H10_0[%d]grd color:0x%08x\n",i,wr_data);
				PE_H10_0_O24_QWr(hdr_tpg_ia_data,wr_data);
			}
			PE_H10_0_O24_QWr(hdr_tpg_ia_ctrl,0x00001068);//gradation region size
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
				PE_DBG_HDR("H10_0[%d]grd end  :0x%08x\n",i,wr_data);
				PE_H10_0_O24_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_0_O24_Wr01(hdr_tpg_ctrl_00,tpg_enable,enable);
			PE_H10_0_O24_WrFL(hdr_tpg_ctrl_00);

			/* 20191218, 1st csc off during pattern on(SCDCR-2960) */
			/* 20200115, moved to fw(AVTASK-423) */
			//PE_H10_0_O24_QWr01(hdr_csc1_ctrl_00,reg_csc1st_en,(enable>0)? 0:1);
		} while(0);

		do {
			/* PE_H10_O */
			PE_H10_1_O24_RdFL(hdr_tpg_ctrl_00);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_00,tpg_enable,0);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_00,tpg_type,type);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_00,tpg_grad_en,grad_en)
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_00,tpg_h_grad,h_grad);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_00,tpg_stride,stride);
			PE_H10_1_O24_WrFL(hdr_tpg_ctrl_00);
			OS_MsecSleep(30);

			PE_H10_1_O24_RdFL(hdr_tpg_ctrl_01);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_01,tpg_size_x,size_x);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_01,tpg_size_y,size_y);
			PE_H10_1_O24_WrFL(hdr_tpg_ctrl_01);

			PE_H10_1_O24_RdFL(hdr_tpg_ctrl_02);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_02,tpg_mask_flag,mask_flag);
			PE_H10_1_O24_WrFL(hdr_tpg_ctrl_02);

			PE_H10_1_O24_RdFL(hdr_tpg_ctrl_03);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_03,tpg_in_out_sel,0x0);
			PE_H10_1_O24_WrFL(hdr_tpg_ctrl_03);

			PE_H10_1_O24_RdFL(hdr_tpg_ctrl_04);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_04,tpg_color_r,0x0);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_04,tpg_color_b,0x0);
			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_04,tpg_color_g,0x0);
			PE_H10_1_O24_WrFL(hdr_tpg_ctrl_04);

			PE_H10_1_O24_QWr(hdr_tpg_ia_ctrl,0x00001000);//patch color
			for (i=0; i<num_win; i++)
			{
				wr_data = p->stWinboxInfo.stWinBoxAttr[i].fill_R;
				wr_data |= (p->stWinboxInfo.stWinBoxAttr[i].fill_B << 10);
				wr_data |= (p->stWinboxInfo.stWinBoxAttr[i].fill_G << 20);
				PE_DBG_HDR("H10_1[%d]win color:0x%08x\n",i,wr_data);
				PE_H10_1_O24_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_1_O24_QWr(hdr_tpg_ia_ctrl,0x00001020);//patch start (x,y)
			for (i=0; i<num_win; i++)
			{
				wr_data = (p->stWinboxInfo.stWinBoxAttr[i].y*ratio_y)>>10;
				wr_data |= (((p->stWinboxInfo.stWinBoxAttr[i].x*ratio_x)>>10) << 16);
				PE_H10_1_O24_QWr(hdr_tpg_ia_data,wr_data);
				PE_DBG_HDR("H10_1[%d]win start:0x%08x\n",i,wr_data);
			}
			PE_H10_1_O24_QWr(hdr_tpg_ia_ctrl,0x00001040);//patch end (x,y)

			for (i=0; i<num_win; i++)
			{
				wr_data = ((p->stWinboxInfo.stWinBoxAttr[i].y + p->stWinboxInfo.stWinBoxAttr[i].h)*ratio_y)>>10;
				wr_data |= ((((p->stWinboxInfo.stWinBoxAttr[i].x + p->stWinboxInfo.stWinBoxAttr[i].w)*ratio_x)>>10) << 16);
				PE_DBG_HDR("H10_1[%d]win end  :0x%08x\n",i,wr_data);
				PE_H10_1_O24_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_1_O24_QWr(hdr_tpg_ia_ctrl,0x00001060);//gradation start color
			for (i=0; i<num_grd; i++)
			{
				wr_data = p->stGradInfo.stLineAttr[i].start_R;
				wr_data |= (p->stGradInfo.stLineAttr[i].start_B << 10);
				wr_data |= (p->stGradInfo.stLineAttr[i].start_G << 20);
				PE_DBG_HDR("H10_1[%d]grd start:0x%08x\n",i,wr_data);
				PE_H10_1_O24_QWr(hdr_tpg_ia_data,wr_data);
			}
			PE_H10_1_O24_QWr(hdr_tpg_ia_ctrl,0x00001064);//gradation step color
			for (i=0; i<num_grd; i++)
			{
				wr_data = p->stGradInfo.stLineAttr[i].step_R;
				wr_data |= (p->stGradInfo.stLineAttr[i].step_B << 10);
				wr_data |= (p->stGradInfo.stLineAttr[i].step_G << 20);
				PE_DBG_HDR("H10_1[%d]grd color:0x%08x\n",i,wr_data);
				PE_H10_1_O24_QWr(hdr_tpg_ia_data,wr_data);
			}
			PE_H10_1_O24_QWr(hdr_tpg_ia_ctrl,0x00001068);//gradation region size
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
				PE_DBG_HDR("H10_1[%d]grd end  :0x%08x\n",i,wr_data);
				PE_H10_1_O24_QWr(hdr_tpg_ia_data,wr_data);
			}

			PE_H10_1_O24_Wr01(hdr_tpg_ctrl_00,tpg_enable,enable);
			PE_H10_1_O24_WrFL(hdr_tpg_ctrl_00);

			/* 20191218, 1st csc off during pattern on(SCDCR-2960) */
			/* 20200115, moved to fw(AVTASK-423) */
			//PE_H10_1_O24_QWr01(hdr_csc1_ctrl_00,reg_csc1st_en,(enable>0)? 0:1);
		} while(0);
		OS_MsecSleep(30);
	} while(0);
	return ret;
}

