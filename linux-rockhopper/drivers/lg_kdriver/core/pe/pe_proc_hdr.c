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
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"
//#include "linux/v4l2-ext/v4l2-ext-pq.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"
#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"
#include "pe_def.h"
#include "pe_hdr.h"
#include "vpq_hwrap.h"
#include "vpq_hwrap_hdr.h"
#include "v4l2_vpq_cmn.h"
#include "v4l2_vpq_hdr.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
/* ver, yyyy/mm/dd/hh:mm */
#define PE_PROC_HDR_VER		"2023/05/16/17:22"

#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
#ifndef V4L2_EXT_HDR_MODE_HDR2SDR
#define V4L2_EXT_HDR_MODE_HDR2SDR	9
#endif
#endif

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/
typedef enum {
	PE_PROC_HDR_FUNC_TRACE           = 0,
	PE_PROC_HDR_FUNC_ENABLE          = 1,
	PE_PROC_HDR_FUNC_G_MODE          = 2,
	PE_PROC_HDR_FUNC_S_MODE          = 3,
	PE_PROC_HDR_FUNC_G_TONE          = 4,
	PE_PROC_HDR_FUNC_S_TONE          = 5,
	PE_PROC_HDR_FUNC_G_Y_GN          = 6,
	PE_PROC_HDR_FUNC_S_Y_GN          = 7,
	PE_PROC_HDR_FUNC_G_HIST          = 8,
	PE_PROC_HDR_FUNC_G_CSC           = 9,
	PE_PROC_HDR_FUNC_S_CSC           = 10,
	PE_PROC_HDR_FUNC_PAT_POS         = 11,
	PE_PROC_HDR_FUNC_G_PAT           = 12,
	PE_PROC_HDR_FUNC_S_PAT           = 13,
	PE_PROC_HDR_FUNC_G_CC            = 14,
	PE_PROC_HDR_FUNC_S_CC            = 15,
	PE_PROC_HDR_FUNC_G_EOTF          = 16,
	PE_PROC_HDR_FUNC_S_EOTF          = 17,
	PE_PROC_HDR_FUNC_G_OETF          = 18,
	PE_PROC_HDR_FUNC_S_OETF          = 19,
	PE_PROC_HDR_FUNC_G_IPXL          = 20,
	PE_PROC_HDR_FUNC_MAX
}PE_PROC_HDR_FUNCNUM;

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/
extern int pe_proc_dbg_printmisctable(int func_num,int *cmd,int size,struct seq_file *m);

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/
int pe_proc_hdr_help(char* buffer);
void pe_proc_hdr_func(char *command);
void pe_proc_hdr_init(struct proc_dir_entry *entry);

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/
/* h10(2017) */
const UINT32 _g_pe_h10_tm_dflt0[33] = {
	0x00000000,
	0x08004FC5,
	0x100095F9,
	0x1800BA9B,
	0x2000CFCC,
	0x2800DD5D,
	0x3000E6B6,
	0x3800ED86,
	0x4000F29E,
	0x4800F6A4,
	0x5000F9CF,
	0x5800FC63,
	0x6000FE8A,
	0x6800FFFF,
	0x7000FFFF,
	0x7800FFFF,
	0x8000FFFF,
	0x8800FFFF,
	0x9000FFFF,
	0x9800FFFF,
	0xA000FFFF,
	0xA800FFFF,
	0xB000FFFF,
	0xB800FFFF,
	0xC000FFFF,
	0xC800FFFF,
	0xD000FFFF,
	0xD800FFFF,
	0xE000FFFF,
	0xE800FFFF,
	0xF000FFFF,
	0xF800FFFF,
	0xFFFFFFFF};

/* h10(201801) x */
const UINT32 _g_pe_h10_tm_dflt1_x[33] = {
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
/* h10(201801) y */
const UINT32 _g_pe_h10_tm_dflt1_y[33] = {
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

/* h10 (20211012) (AVTASK-681), change this if necessary to change default */
const UINT32 _g_pe_h10_tm_dflt2[66] = {
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
	0x000003E4,
	0x00000555,
	0x000008C9,
	0x00000B14,
	0x00000D53,
	0x00000F2F,
	0x00001905,
	0x00001F8F,
	0x00002713,
	0x00002B3F,
	0x00003B43,
	0x00004C6E,
	0x000059E1,
	0x00006C11,
	0x00007B2A,
	0x00009418,
	0x0000A8C8,
	0x0000C173,
	0x0000D68E,
	0x0000E9E6,
	0x0000F2A9,
	0x0000FE17,
	0x0000FFFF,
	0x0000FFFF,
	0x0000FFFF,
	0x0000FFFF,
	0x0000FFFF,
	0x0000FFFF,
	0x0000FFFF,
	0x0000FFFF,
	0x0000FFFF,
	0x0000FFFF};

/* hlg (2017) */
const UINT32 _g_pe_hlg_tm_dflt0[66] = {
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
	0xFFFFFFFF,
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

/* hlg (20211012) (AVTASK-681), change this if necessary to change default */
const UINT32 _g_pe_hlg_tm_dflt1[66] = {
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

/* s2h_0 */
const UINT32 _g_pe_s2h_tm_dflt0[33] = {
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

/* s2h_1 */
const UINT32 _g_pe_s2h_tm_dflt1[33] = {
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

/* ygain */
const UINT32 _g_pe_yg_lut_dflt0[33] = {
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

/* ygain (20211012) (AVTASK-681), change this if necessary to change default */
const UINT32 _g_pe_yg_lut_dflt1[33] = {
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

/*============================================================================
	Implementation Group
============================================================================*/
int pe_proc_hdr_help(char* buffer)
{
	int len = 0;
	#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
	UINT32 h2s = V4L2_EXT_HDR_MODE_HDR2SDR;
	#else
	UINT32 h2s = 9;
	#endif

	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, " hdr_func (%s)\n", PE_PROC_HDR_VER);
	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, " G_TRACE    : echo %d > hdr_func\n",PE_PROC_HDR_FUNC_TRACE);
	len += sprintf( buffer+len, " ENABLE(%d) : echo %d [0:off,1:on] > hdr_func\n",vpq_hwrap_gethdrfunctionenable(),PE_PROC_HDR_FUNC_ENABLE);
	len += sprintf( buffer+len, " G_MODE     : echo %d [0:main,1:sub] > hdr_func\n",PE_PROC_HDR_FUNC_G_MODE);
	len += sprintf( buffer+len, " S_MODE     : echo %d [0:main,1:sub] [0:SDR,1:DOBY,2:H10,3:HLG,4:TEC,5:S2H,%d:H2S] [0:BT601,1:BT709,2:BT2020] > hdr_func\n",PE_PROC_HDR_FUNC_S_MODE,h2s);
	len += sprintf( buffer+len, " G_TONE     : echo %d [0:main,1:sub] > hdr_func\n",PE_PROC_HDR_FUNC_G_TONE);
	len += sprintf( buffer+len, " S_TONE     : echo %d [0:main,1:sub] [0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg,7:h2s] [0:byp,1:s2h,2~4:h10,5~6:hlg] > hdr_func\n",PE_PROC_HDR_FUNC_S_TONE);
	len += sprintf( buffer+len, " G_Y_GN     : echo %d [0,10:main,1,11:sub] > hdr_func\n",PE_PROC_HDR_FUNC_G_Y_GN);
	len += sprintf( buffer+len, " S_Y_GN     : echo %d [0,10:main,1,11:sub] [0:byp,1,2:dflt] > hdr_func\n",PE_PROC_HDR_FUNC_S_Y_GN);
	len += sprintf( buffer+len, " G_HIST     : echo %d [0,2:main,1,3:sub] > hdr_func\n",PE_PROC_HDR_FUNC_G_HIST);
	len += sprintf( buffer+len, " G_CSC      : echo %d 1 > hdr_func\n",PE_PROC_HDR_FUNC_G_CSC);
	len += sprintf( buffer+len, " S_CSC      : echo %d [0:main,1:sub] [0:byp,1:dflt] > hdr_func\n",PE_PROC_HDR_FUNC_S_CSC);
	len += sprintf( buffer+len, " PAT_POS(%d): echo %d [0:normal,1:cc,2:hdr] > hdr_func\n",vpq_hwrap_getforcepattern(),PE_PROC_HDR_FUNC_PAT_POS);
	len += sprintf( buffer+len, " G_PAT      : echo %d > hdr_func\n",PE_PROC_HDR_FUNC_G_PAT);
	len += sprintf( buffer+len, " S_PAT      : echo %d [0~3] > hdr_func\n",PE_PROC_HDR_FUNC_S_PAT);
	len += sprintf( buffer+len, " G_CC       : echo %d [0,10:main,1,11:sub] > hdr_func\n",PE_PROC_HDR_FUNC_G_CC);
	len += sprintf( buffer+len, " S_CC       : echo %d [0,10:main,1,11:sub] [0:zero,1:dflt] > hdr_func\n",PE_PROC_HDR_FUNC_S_CC);
	len += sprintf( buffer+len, " G_EOTF     : echo %d [0:main,1:sub] [start] [end] > hdr_func\n",PE_PROC_HDR_FUNC_G_EOTF);
	len += sprintf( buffer+len, " S_EOTF     : echo %d [0:main,1:sub] [0:byp,1~:curve] > hdr_func\n",PE_PROC_HDR_FUNC_S_EOTF);
	len += sprintf( buffer+len, " G_OETF     : echo %d [0:main,1:sub] [start] [end] > hdr_func\n",PE_PROC_HDR_FUNC_G_OETF);
	len += sprintf( buffer+len, " S_OETF     : echo %d [0:main,1:sub] [0:byp,1~:curve] > hdr_func\n",PE_PROC_HDR_FUNC_S_OETF);
	len += sprintf( buffer+len, " G_IPXL     : echo %d [pos_x] [pos_y] [csc_en] > hdr_func\n",PE_PROC_HDR_FUNC_G_IPXL);
	len += sprintf( buffer+len, "----------------------------------------\n");
	return len;
}

void pe_proc_hdr_func(char *command)
{
	int ret = RET_OK;
	UINT32 val[5], i;
	PE_PROC_HDR_FUNCNUM func_num;
	sscanf(command," %d",(int *)&func_num);
	printk(" ** khdr dbg func num : %d, command : %s\n",func_num,command);
	switch(func_num)
	{
		case PE_PROC_HDR_FUNC_TRACE:
		{
			sscanf(command," %d",(int *)&func_num);
			val[0] = 0;
			pe_proc_dbg_printmisctable(13,&val[0],(int)sizeof(UINT32),NULL);
		}break;
		case PE_PROC_HDR_FUNC_ENABLE:
		{
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			vpq_hwrap_sethdrfunctionenable((int)val[0]);
		}break;
		case PE_PROC_HDR_FUNC_G_MODE:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int data[5] = {0xff,0xff,0xff,0xff,0xff};
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			param.wid = val[0];
			param.version = 0;
			param.length = sizeof(unsigned int)*5;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getpqmodeinfo(&param);
			if (ret!=RET_OK){
				printk("[%s,%d]vpq_hwrap_getpqmodeinfo() error\n", __F__, __L__);
				break;
			}
			printk("v:%d,l:%d,wid:%d, d:%d,%d,%d,%d,%d\n",\
				param.version,param.length,param.wid,\
				data[0],data[1],data[2],data[3],data[4]);
		}break;
		case PE_PROC_HDR_FUNC_S_MODE:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int data[5] = {0,0,1000,0,0};
			sscanf(command," %d %d %d %d",(int *)&func_num,&val[0],&val[1],&val[2]);
			param.wid = val[0];
			param.version = 2;
			param.length = sizeof(unsigned int)*5;
			param.p_data = (unsigned char *)data;
			data[0] = val[1];//0:SDR,1:DOBY,2:H10,3:HLG,4:TEC,5:S2H
			data[1] = val[2];//0:BT601,1:BT709,2:BT2020
			ret = vpq_hwrap_setpqmodeinfo(&param);
			if (ret!=RET_OK){
				printk("[%s,%d]vpq_hwrap_setpqmodeinfo() error\n", __F__, __L__);
				break;
			}
			printk("v:%d,l:%d,wid:%d, d:%d,%d,%d,%d,%d\n",\
				param.version,param.length,param.wid,\
				data[0],data[1],data[2],data[3],data[4]);
		}break;
		case PE_PROC_HDR_FUNC_G_TONE:
		{
			UINT32 lut_data[198];
			LX_PE_HDR_TONEMAP_LUT_T param;
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			param.win_id = val[0];
			param.oper = 0x1000;
			param.size = 198;
			param.data = (unsigned int *)lut_data;
			ret = PE_HDR_GetHdrTonemapLut(&param);
			if (ret!=RET_OK){
				printk("[%s,%d]PE_HDR_GetHdrTonemapLut() error\n", __F__, __L__);
				break;
			}
			printk("[TM][wid:%d] op:%d, size:%d\n", param.win_id, param.oper, param.size);
			printk("\n   [ i]\n");
			for (i=0;i<param.size;i++)
			{
				printk("   [%03d] %08x\n", i, param.data[i]);
			}
			printk("\n");
		}break;
		case PE_PROC_HDR_FUNC_S_TONE:
		{
			UINT32 lut_data[198];
			LX_PE_HDR_TONEMAP_LUT_T param;
			sscanf(command," %d %d %d %d",(int *)&func_num,&val[0],&val[1],&val[2]);
			param.win_id = val[0];
			param.oper = 0x1020;
			param.size = 198;
			param.data = (unsigned int *)lut_data;
			param.oper |= val[1];//0:off,1:doby,2:hdr10,3:tech,4:s2h,5:hlg
			/* 0:byp,1:s2h,2~4:h10,5~6:hlg */
			if (val[2]==0)
			{
				for (i=0;i<33;i++)	lut_data[i] =      (_g_pe_h10_tm_dflt0[i]);
				for (i=0;i<33;i++)	lut_data[i+33] =   (_g_pe_h10_tm_dflt0[i]>>16);
				for (i=0;i<33;i++)	lut_data[i+33*2] = (_g_pe_h10_tm_dflt0[i]);
				for (i=0;i<33;i++)	lut_data[i+33*3] = (_g_pe_h10_tm_dflt0[i]>>16);
				for (i=0;i<33;i++)	lut_data[i+33*4] = (_g_pe_h10_tm_dflt0[i]);
				for (i=0;i<33;i++)	lut_data[i+33*5] = (_g_pe_h10_tm_dflt0[i]>>16);
			}
			else if (val[2]==1)
			{
				for (i=0;i<33;i++)	lut_data[i] =      (_g_pe_s2h_tm_dflt0[i]>>16);
				for (i=0;i<33;i++)	lut_data[i+33] =   (_g_pe_s2h_tm_dflt0[i]&0xffff);
				for (i=0;i<33;i++)	lut_data[i+33*2] = (_g_pe_s2h_tm_dflt0[i]>>16);
				for (i=0;i<33;i++)	lut_data[i+33*3] = (_g_pe_s2h_tm_dflt0[i]&0xffff);
				for (i=0;i<33;i++)	lut_data[i+33*4] = (_g_pe_s2h_tm_dflt1[i]>>16);
				for (i=0;i<33;i++)	lut_data[i+33*5] = (_g_pe_s2h_tm_dflt1[i]&0xffff);
			}
			else if (val[2]==2)
			{
				for (i=0;i<33;i++)	lut_data[i] =      (_g_pe_h10_tm_dflt0[i]);
				for (i=0;i<33;i++)	lut_data[i+33] =   (_g_pe_h10_tm_dflt0[i]&0xffff);
				for (i=0;i<33;i++)	lut_data[i+33*2] = (_g_pe_h10_tm_dflt0[i]);
				for (i=0;i<33;i++)	lut_data[i+33*3] = (_g_pe_h10_tm_dflt0[i]&0xffff);
				for (i=0;i<33;i++)	lut_data[i+33*4] = (_g_pe_h10_tm_dflt0[i]);
				for (i=0;i<33;i++)	lut_data[i+33*5] = (_g_pe_h10_tm_dflt0[i]&0xffff);
			}
			else if (val[2]==3)
			{
				for (i=0;i<33;i++)	lut_data[i] =      (_g_pe_h10_tm_dflt1_x[i]);
				for (i=0;i<33;i++)	lut_data[i+33] =   (_g_pe_h10_tm_dflt1_y[i]);
				for (i=0;i<33;i++)	lut_data[i+33*2] = (_g_pe_h10_tm_dflt1_x[i]);
				for (i=0;i<33;i++)	lut_data[i+33*3] = (_g_pe_h10_tm_dflt1_y[i]);
				for (i=0;i<33;i++)	lut_data[i+33*4] = (_g_pe_h10_tm_dflt1_x[i]);
				for (i=0;i<33;i++)	lut_data[i+33*5] = (_g_pe_h10_tm_dflt1_y[i]);
			}
			else if (val[2]==4)
			{
				for (i=0;i<66;i++)	lut_data[i+66*0] = (_g_pe_h10_tm_dflt2[i]);
				for (i=0;i<66;i++)	lut_data[i+66*1] = (_g_pe_h10_tm_dflt2[i]);
				for (i=0;i<66;i++)	lut_data[i+66*2] = (_g_pe_h10_tm_dflt2[i]);
			}
			else if (val[2]==5)
			{
				for (i=0;i<66;i++)	lut_data[i+66*0] = (_g_pe_hlg_tm_dflt0[i]);
				for (i=0;i<66;i++)	lut_data[i+66*1] = (_g_pe_hlg_tm_dflt0[i]);
				for (i=0;i<66;i++)	lut_data[i+66*2] = (_g_pe_hlg_tm_dflt0[i]);
			}
			else
			{
				for (i=0;i<66;i++)	lut_data[i+66*0] = (_g_pe_hlg_tm_dflt1[i]);
				for (i=0;i<66;i++)	lut_data[i+66*1] = (_g_pe_hlg_tm_dflt1[i]);
				for (i=0;i<66;i++)	lut_data[i+66*2] = (_g_pe_hlg_tm_dflt1[i]);
			}
			ret = PE_HDR_SetHdrTonemapLut(&param);
			if (ret!=RET_OK){
				printk("[%s,%d]PE_HDR_SetHdrTonemapLut() error\n", __F__, __L__);
				break;
			}
			printk("[TM]d:%08x,%08x,%08x,%08x,%08x\n",\
				lut_data[0],lut_data[1],lut_data[2],lut_data[3],lut_data[4]);
		}break;
		case PE_PROC_HDR_FUNC_G_Y_GN:
		{
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			if (val[0]>=10)
			{
				unsigned short lut_data[66];//66point x,y
				struct v4l2_ext_vpq_cmn_data param;
				param.version = 0;
				param.length = sizeof(unsigned short)*66;
				param.wid = (val[0]==10)? 0:1;
				param.p_data = (unsigned char *)lut_data;
				ret = vpq_hwrap_gethlgygaintable(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_gethlgygaintable() error\n", __F__, __L__);
					break;
				}
				printk("[YG] v:%d, l:%d, w:%d\n",param.version,param.length,param.wid);
				printk("\n   [  i]\n");
				for (i=0;i<33;i++)
				{
					printk("   [%03d] %04x %04x\n", i, lut_data[i], lut_data[i+33]);
				}
				printk("\n");
			}
			else
			{
				unsigned int lut_data[33];//33point x|y
				LX_PE_HDR_YGAIN_LUT_T param;
				param.win_id = val[0];
				param.oper = 0x1;
				param.size = 33;
				param.data = (unsigned int *)lut_data;
				ret = PE_HDR_GetHdrYgainLut(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]PE_HDR_GetHdrYgainLut() error\n", __F__, __L__);
					break;
				}
				printk("[YG][wid:%d] op:%d, size:%d\n", param.win_id, param.oper, param.size);
				printk("\n   [  i]\n");
				for (i=0;i<param.size;i++)
				{
					printk("   [%03d] %08x\n", i, param.data[i]);
				}
				printk("\n");
			}
		}break;
		case PE_PROC_HDR_FUNC_S_Y_GN:
		{
			sscanf(command," %d %d %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]>=10)
			{
				unsigned short lut_data[66],lut_x,lut_y;//66point x,y
				struct v4l2_ext_vpq_cmn_data param;
				param.version = 0;
				param.length = sizeof(unsigned short)*66;
				param.wid = (val[0]==10)? 0:1;
				param.p_data = (unsigned char *)lut_data;
				/* 0:byp,1:dflt */
				for (i=0;i<33;i++)
				{
					if (val[1]==2) {
						lut_x = (_g_pe_yg_lut_dflt1[i]>>16);
						lut_y = (_g_pe_yg_lut_dflt1[i]&0xffff);
					}
					else if (val[1]==1) {
						lut_x = (_g_pe_yg_lut_dflt0[i]>>16);
						lut_y = (_g_pe_yg_lut_dflt0[i]&0xffff);
					}
					else {
						lut_x = (_g_pe_yg_lut_dflt0[i]>>16);
						lut_y = (_g_pe_yg_lut_dflt0[i]>>16);
					}
					lut_data[i] = lut_x;
					lut_data[i+33] = lut_y;
				}
				ret = vpq_hwrap_sethlgygaintable(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_sethlgygaintable() error\n", __F__, __L__);
					break;
				}
				printk("[YG]x:%04x,%04x,%04x,%04x,%04x, y:%04x,%04x,%04x,%04x,%04x\n",\
					lut_data[0],lut_data[1],lut_data[2],lut_data[3],lut_data[4],\
					lut_data[33],lut_data[34],lut_data[35],lut_data[36],lut_data[37]);
			}
			else
			{
				unsigned int lut_data[33];//33point x|y
				LX_PE_HDR_YGAIN_LUT_T param;
				param.win_id = val[0];
				param.oper = 0x1;
				param.size = 33;
				param.data = (unsigned int *)lut_data;
				/* 0:byp,1:dflt */
				for (i=0;i<33;i++)
				{
					if (val[1]==2) {
						lut_data[i] = _g_pe_yg_lut_dflt1[i];
					}
					else if (val[1]==1) {
						lut_data[i] = _g_pe_yg_lut_dflt0[i];
					}
					else {
						lut_data[i] = (_g_pe_yg_lut_dflt0[i]&0xffff0000)|(_g_pe_yg_lut_dflt0[i]>>16);
					}
				}
				ret = PE_HDR_SetHdrYgainLut(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]PE_HDR_SetHdrYgainLut() error\n", __F__, __L__);
					break;
				}
				printk("[YG]d:%08x,%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x,%08x\n",\
					lut_data[0],lut_data[1],lut_data[2],lut_data[3],lut_data[4],\
					lut_data[28],lut_data[29],lut_data[30],lut_data[31],lut_data[32]);
			}
		}break;
		case PE_PROC_HDR_FUNC_G_HIST:
		{
			UINT32 sum;
			LX_PE_HDR_HISTO_INFO_T param;
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			param.win_id = val[0];
			ret = PE_HDR_GetHistoInfo(&param);
			if (ret!=RET_OK){
				printk("[%s,%d]PE_HDR_GetHistoInfo() error\n", __F__, __L__);
				break;
			}
			printk("wid:%d\n", param.win_id);
			//printk("min:%d, max:%d\n", param.status[0], param.status[1]);
			printk("histo0\n");
			for (i=0;i<16;i++)
			{
				printk("[%03d]%8d [%03d]%8d [%03d]%8d [%03d]%8d [%03d]%8d [%03d]%8d [%03d]%8d [%03d]%8d\n",\
					i*8+0,param.status[i*8+0],i*8+1,param.status[i*8+1],i*8+2,param.status[i*8+2],i*8+3,param.status[i*8+3],\
					i*8+4,param.status[i*8+4],i*8+5,param.status[i*8+5],i*8+6,param.status[i*8+6],i*8+7,param.status[i*8+7]);
			}
			sum = 0;
			for (i=0;i<128;i++)
			{
				sum += param.status[i];
			}
			printk("histo_sum = %d\n\n", sum);
		}break;
		case PE_PROC_HDR_FUNC_G_CSC:
		{
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			pe_proc_dbg_printmisctable(11,&val[0],(int)sizeof(UINT32),NULL);
		}break;
		case PE_PROC_HDR_FUNC_S_CSC:
		{
			LX_PE_HDR_CSC_T param;
			sscanf(command," %d %d %d",(int *)&func_num,&val[0],&val[1]);
			memset(&param,0,sizeof(LX_PE_HDR_CSC_T));
			param.win_id = val[0];
			param.type0 = LX_PE_HDR_CSC_BYPASS;
			param.type1 = (val[1]==0)? LX_PE_HDR_CSC_BYPASS:LX_PE_HDR_CSC_DEFAULT;
			param.type2 = LX_PE_HDR_CSC_BYPASS;
			ret = PE_HDR_SetCsc(&param);
			if (ret!=RET_OK){
				printk("[%s,%d]PE_HDR_SetCsc() error\n", __F__, __L__);
				break;
			}
			printk("[CSC]type:%d,%d,%d\n",param.type0,param.type1,param.type2);
		}break;
		case PE_PROC_HDR_FUNC_PAT_POS:
		{
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			ret = vpq_hwrap_setforcepattern((int)val[0]);
		}break;
		case PE_PROC_HDR_FUNC_G_PAT:
		{
			struct v4l2_vpq_ext_pattern_info_v2 param;
			struct v4l2_ext_vpq_cmn_data stParam;
			sscanf(command," %d",(int *)&func_num);
			stParam.version = 0;
			stParam.length = sizeof(struct v4l2_vpq_ext_pattern_info_v2);
			stParam.wid = 0;
			stParam.p_data = (unsigned char *)&param;
			vpq_hwrap_getextpattern(&stParam);
			printk("on:%d,mode:%d\n",param.bOnOff,param.eMode);
			printk("grad num:%d,mode:%d\n",param.stGradInfo.numGrad,param.stGradInfo.eGradMode);
			for (i=0; i<4; i++)
			{
				printk("[%d] %d, %x,%x,%x, %x,%x,%x, %x\n",i,\
					param.stGradInfo.stLineAttr[i].lineIdx,param.stGradInfo.stLineAttr[i].start_R,\
					param.stGradInfo.stLineAttr[i].start_G,param.stGradInfo.stLineAttr[i].start_B,\
					param.stGradInfo.stLineAttr[i].step_R,param.stGradInfo.stLineAttr[i].step_G,\
					param.stGradInfo.stLineAttr[i].step_B,param.stGradInfo.stLineAttr[i].strideSize);
			}
			printk("winbox num:%d\n",param.stWinboxInfo.u8NumWin);
			for (i=0; i<4; i++)
			{
				printk("[%d] %d, %d,%d,%d,%d, %x,%x,%x\n",i,\
					param.stWinboxInfo.stWinBoxAttr[i].winIdx,param.stWinboxInfo.stWinBoxAttr[i].x,\
					param.stWinboxInfo.stWinBoxAttr[i].y,param.stWinboxInfo.stWinBoxAttr[i].w,\
					param.stWinboxInfo.stWinBoxAttr[i].h,param.stWinboxInfo.stWinBoxAttr[i].fill_R,\
					param.stWinboxInfo.stWinBoxAttr[i].fill_G,param.stWinboxInfo.stWinBoxAttr[i].fill_B);
			}
		}break;
		case PE_PROC_HDR_FUNC_S_PAT:
		{
			static int winbox_cnt = 0;
			short winbox_ofst[4] = {0,0,0,0};
			struct v4l2_vpq_ext_pattern_info_v2 param;
			struct v4l2_ext_vpq_cmn_data stParam;
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			stParam.version = 0;
			stParam.length = sizeof(struct v4l2_vpq_ext_pattern_info_v2);
			stParam.wid = 0;
			stParam.p_data = (unsigned char *)&param;
			memset(&param,0,sizeof(struct v4l2_vpq_ext_pattern_info_v2));
			if (val[0] == 1)
			{
				param.bOnOff = 1;
				param.eMode = V4L2_VPQ_EXT_PATTERN_WINBOX;
			}
			else if (val[0] == 2)
			{
				param.bOnOff = 1;
				param.eMode = V4L2_VPQ_EXT_PATTERN_GRADATION;
				param.stGradInfo.eGradMode = V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION_HORIZONTAL;
			}
			else if (val[0] == 3)
			{
				param.bOnOff = 1;
				param.eMode = V4L2_VPQ_EXT_PATTERN_GRADATION;
				param.stGradInfo.eGradMode = V4L2_VPQ_EXT_PATTERN_GRADATION_DIRECTION_VERTICAL;
			}
			else
			{
				param.bOnOff = 0;
			}
			switch (winbox_cnt)
			{
				case 1:
					winbox_ofst[0] = 1920;
					break;
				case 2:
					winbox_ofst[1] = 1080;
					break;
				case 3:
					winbox_ofst[0] = 1920;
					winbox_ofst[1] = 1080;
					break;
				case 4:
					winbox_ofst[2] = 1920;
					break;
				case 5:
					winbox_ofst[1] = 1080;
					winbox_ofst[2] = 1920;
					break;
				case 6:
					winbox_ofst[3] = 1080;
					break;
				case 7:
					winbox_ofst[0] = 1920;
					winbox_ofst[3] = 1080;
					break;
				case 8:
					winbox_ofst[2] = 1920;
					winbox_ofst[3] = 1080;
					break;
				default:
					break;
			}
			param.stGradInfo.numGrad = 4;
			param.stGradInfo.stLineAttr[0].lineIdx = 0;
			param.stGradInfo.stLineAttr[0].start_R = 0;
			param.stGradInfo.stLineAttr[0].start_G = 0;
			param.stGradInfo.stLineAttr[0].start_B = 0;
			param.stGradInfo.stLineAttr[0].step_R = 1;
			param.stGradInfo.stLineAttr[0].step_G = 0;
			param.stGradInfo.stLineAttr[0].step_B = 0;
			param.stGradInfo.stLineAttr[0].strideSize = 1;
			param.stGradInfo.stLineAttr[1].lineIdx = 1;
			param.stGradInfo.stLineAttr[1].start_R = 0;
			param.stGradInfo.stLineAttr[1].start_G = 0;
			param.stGradInfo.stLineAttr[1].start_B = 0;
			param.stGradInfo.stLineAttr[1].step_R = 0;
			param.stGradInfo.stLineAttr[1].step_G = 1;
			param.stGradInfo.stLineAttr[1].step_B = 0;
			param.stGradInfo.stLineAttr[1].strideSize = 1;
			param.stGradInfo.stLineAttr[2].lineIdx = 2;
			param.stGradInfo.stLineAttr[2].start_R = 0;
			param.stGradInfo.stLineAttr[2].start_G = 0;
			param.stGradInfo.stLineAttr[2].start_B = 0;
			param.stGradInfo.stLineAttr[2].step_R = 0;
			param.stGradInfo.stLineAttr[2].step_G = 0;
			param.stGradInfo.stLineAttr[2].step_B = 1;
			param.stGradInfo.stLineAttr[2].strideSize = 1;
			param.stGradInfo.stLineAttr[3].lineIdx = 3;
			param.stGradInfo.stLineAttr[3].start_R = 0;
			param.stGradInfo.stLineAttr[3].start_G = 0;
			param.stGradInfo.stLineAttr[3].start_B = 0;
			param.stGradInfo.stLineAttr[3].step_R = 1;
			param.stGradInfo.stLineAttr[3].step_G = 1;
			param.stGradInfo.stLineAttr[3].step_B = 1;
			param.stGradInfo.stLineAttr[3].strideSize = 1;
			if (MAX_EXT_PATTERN_WINBOX >= 10)
			{
				param.stWinboxInfo.u8NumWin = 10;
				param.stWinboxInfo.stWinBoxAttr[0].winIdx = 0;
				param.stWinboxInfo.stWinBoxAttr[0].x = 0;
				param.stWinboxInfo.stWinBoxAttr[0].y = 0;
				param.stWinboxInfo.stWinBoxAttr[0].w = 1920;
				param.stWinboxInfo.stWinBoxAttr[0].h = 1080;
				param.stWinboxInfo.stWinBoxAttr[0].fill_R = 0x0;
				param.stWinboxInfo.stWinBoxAttr[0].fill_G = 0x0;
				param.stWinboxInfo.stWinBoxAttr[0].fill_B = 0x0;
				param.stWinboxInfo.stWinBoxAttr[1].winIdx = 1;
				param.stWinboxInfo.stWinBoxAttr[1].x = 1920;
				param.stWinboxInfo.stWinBoxAttr[1].y = 0;
				param.stWinboxInfo.stWinBoxAttr[1].w = 1920;
				param.stWinboxInfo.stWinBoxAttr[1].h = 1080;
				param.stWinboxInfo.stWinBoxAttr[1].fill_R = 0x155;
				param.stWinboxInfo.stWinBoxAttr[1].fill_G = 0x155;
				param.stWinboxInfo.stWinBoxAttr[1].fill_B = 0x155;
				param.stWinboxInfo.stWinBoxAttr[2].winIdx = 2;
				param.stWinboxInfo.stWinBoxAttr[2].x = 0;
				param.stWinboxInfo.stWinBoxAttr[2].y = 1080;
				param.stWinboxInfo.stWinBoxAttr[2].w = 1920;
				param.stWinboxInfo.stWinBoxAttr[2].h = 1080;
				param.stWinboxInfo.stWinBoxAttr[2].fill_R = 0x2aa;
				param.stWinboxInfo.stWinBoxAttr[2].fill_G = 0x2aa;
				param.stWinboxInfo.stWinBoxAttr[2].fill_B = 0x2aa;
				param.stWinboxInfo.stWinBoxAttr[3].winIdx = 3;
				param.stWinboxInfo.stWinBoxAttr[3].x = 1920;
				param.stWinboxInfo.stWinBoxAttr[3].y = 1080;
				param.stWinboxInfo.stWinBoxAttr[3].w = 1920;
				param.stWinboxInfo.stWinBoxAttr[3].h = 1080;
				param.stWinboxInfo.stWinBoxAttr[3].fill_R = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[3].fill_G = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[3].fill_B = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[4].winIdx = 4;
				param.stWinboxInfo.stWinBoxAttr[4].x = 100 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[4].y = 100 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[4].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[4].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[4].fill_R = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[4].fill_G = 0x0;
				param.stWinboxInfo.stWinBoxAttr[4].fill_B = 0x0;
				param.stWinboxInfo.stWinBoxAttr[5].winIdx = 5;
				param.stWinboxInfo.stWinBoxAttr[5].x = 200 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[5].y = 200 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[5].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[5].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[5].fill_R = 0x0;
				param.stWinboxInfo.stWinBoxAttr[5].fill_G = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[5].fill_B = 0x0;
				param.stWinboxInfo.stWinBoxAttr[6].winIdx = 6;
				param.stWinboxInfo.stWinBoxAttr[6].x = 300 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[6].y = 250 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[6].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[6].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[6].fill_R = 0x0;
				param.stWinboxInfo.stWinBoxAttr[6].fill_G = 0x0;
				param.stWinboxInfo.stWinBoxAttr[6].fill_B = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[7].winIdx = 7;
				param.stWinboxInfo.stWinBoxAttr[7].x = 400 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[7].y = 300 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[7].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[7].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[7].fill_R = 0x0;
				param.stWinboxInfo.stWinBoxAttr[7].fill_G = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[7].fill_B = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[8].winIdx = 8;
				param.stWinboxInfo.stWinBoxAttr[8].x = 500 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[8].y = 350 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[8].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[8].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[8].fill_R = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[8].fill_G = 0x0;
				param.stWinboxInfo.stWinBoxAttr[8].fill_B = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[9].winIdx = 9;
				param.stWinboxInfo.stWinBoxAttr[9].x = 600 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[9].y = 400 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[9].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[9].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[9].fill_R = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[9].fill_G = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[9].fill_B = 0x0;
			}
			else
			{
				param.stWinboxInfo.u8NumWin = 4;
				param.stWinboxInfo.stWinBoxAttr[0].winIdx = 0;
				param.stWinboxInfo.stWinBoxAttr[0].x = 0;
				param.stWinboxInfo.stWinBoxAttr[0].y = 0;
				param.stWinboxInfo.stWinBoxAttr[0].w = 3840;
				param.stWinboxInfo.stWinBoxAttr[0].h = 2160;
				param.stWinboxInfo.stWinBoxAttr[0].fill_R = 0x0;
				param.stWinboxInfo.stWinBoxAttr[0].fill_G = 0x0;
				param.stWinboxInfo.stWinBoxAttr[0].fill_B = 0x0;
				param.stWinboxInfo.stWinBoxAttr[1].winIdx = 1;
				param.stWinboxInfo.stWinBoxAttr[1].x = 200 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[1].y = 200 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[1].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[1].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[1].fill_R = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[1].fill_G = 0x0;
				param.stWinboxInfo.stWinBoxAttr[1].fill_B = 0x0;
				param.stWinboxInfo.stWinBoxAttr[2].winIdx = 2;
				param.stWinboxInfo.stWinBoxAttr[2].x = 400 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[2].y = 300 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[2].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[2].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[2].fill_R = 0x0;
				param.stWinboxInfo.stWinBoxAttr[2].fill_G = 0x3ff;
				param.stWinboxInfo.stWinBoxAttr[2].fill_B = 0x0;
				param.stWinboxInfo.stWinBoxAttr[3].winIdx = 3;
				param.stWinboxInfo.stWinBoxAttr[3].x = 600 + winbox_ofst[0];
				param.stWinboxInfo.stWinBoxAttr[3].y = 400 + winbox_ofst[1];
				param.stWinboxInfo.stWinBoxAttr[3].w = 640 + winbox_ofst[2];
				param.stWinboxInfo.stWinBoxAttr[3].h = 480 + winbox_ofst[3];
				param.stWinboxInfo.stWinBoxAttr[3].fill_R = 0x0;
				param.stWinboxInfo.stWinBoxAttr[3].fill_G = 0x0;
				param.stWinboxInfo.stWinBoxAttr[3].fill_B = 0x3ff;
			}
			vpq_hwrap_setextpattern(&stParam);
			if (val[0] == 1)	winbox_cnt++;
			else				winbox_cnt=0;
			if (winbox_cnt>8)	winbox_cnt=0;
		}break;
		case PE_PROC_HDR_FUNC_G_CC:
		{
			sscanf(command," %d %d",(int *)&func_num,&val[0]);
			if (val[0]>=10)
			{
				struct v4l2_ext_hdr_color_correction cc_data;
				struct v4l2_ext_vpq_cmn_data param;
				param.version = 0;
				param.length = sizeof(cc_data);
				param.wid = (val[0]==10)? 0:1;
				param.p_data = (unsigned char *)&cc_data;
				ret = vpq_hwrap_gethdrcolorcorrection(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_gethdrcolorcorrection() error\n", __F__, __L__);
					break;
				}
				printk("[CC]v:%d,l:%d,wid:%d, hs:%x,%x, lxy:%x,%x,%x,%x, %x,%x,%x,%x, sxy:%x,%x,%x,%x, %x,%x,%x,%x\n",\
					param.version,param.length,param.wid,cc_data.hue_blend,cc_data.sat_blend,\
					cc_data.l_gain_x[0],cc_data.l_gain_x[1],cc_data.l_gain_x[6],cc_data.l_gain_x[7],\
					cc_data.l_gain_y[0],cc_data.l_gain_y[1],cc_data.l_gain_y[6],cc_data.l_gain_y[7],\
					cc_data.s_gain_x[0],cc_data.s_gain_x[1],cc_data.s_gain_x[6],cc_data.s_gain_x[7],\
					cc_data.s_gain_y[0],cc_data.s_gain_y[1],cc_data.s_gain_y[6],cc_data.s_gain_y[7]);
			}
			else
			{
				LX_PE_HDR_CCR_T param;
				param.win_id = val[0];
				ret = PE_HDR_GetColorCorrect(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]PE_HDR_GetColorCorrect() error\n", __F__, __L__);
					break;
				}
				printk("[CC][wid:%d]%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x\n", \
					param.win_id,param.data[0],param.data[1],\
					param.data[2],param.data[3],param.data[4],param.data[5],\
					param.data[6],param.data[7],param.data[12],param.data[13],\
					param.data[14],param.data[15],param.data[20],param.data[21]);
			}
		}break;
		case PE_PROC_HDR_FUNC_S_CC:
		{
			sscanf(command," %d %d %d",(int *)&func_num,&val[0],&val[1]);
			if (val[0]>=10)
			{
				struct v4l2_ext_hdr_color_correction cc_data;
				struct v4l2_ext_vpq_cmn_data param;
				memset(&cc_data,0,sizeof(cc_data));
				param.version = 0;
				param.length = sizeof(cc_data);
				param.wid = (val[0]==10)? 0:1;
				param.p_data = (unsigned char *)&cc_data;
				if (val[1]==1)
				{
					cc_data.hue_blend = 0x3ff;
					cc_data.sat_blend = 0x3ff;
					cc_data.l_gain_x[0] = 0x0000;
					cc_data.l_gain_x[1] = 0x2492;
					cc_data.l_gain_x[2] = 0x4924;
					cc_data.l_gain_x[3] = 0x6DB6;
					cc_data.l_gain_x[4] = 0x9248;
					cc_data.l_gain_x[5] = 0xB6DA;
					cc_data.l_gain_x[6] = 0xDB6C;
					cc_data.l_gain_x[7] = 0xFFFF;
					cc_data.l_gain_y[0] = 0x0000;
					cc_data.l_gain_y[1] = 0x0040;
					cc_data.l_gain_y[2] = 0x0080;
					cc_data.l_gain_y[3] = 0x0080;
					cc_data.l_gain_y[4] = 0x0080;
					cc_data.l_gain_y[5] = 0x0080;
					cc_data.l_gain_y[6] = 0x0080;
					cc_data.l_gain_y[7] = 0x0080;
					cc_data.s_gain_x[0] = 0x0000;
					cc_data.s_gain_x[1] = 0x2492;
					cc_data.s_gain_x[2] = 0x4924;
					cc_data.s_gain_x[3] = 0x6DB6;
					cc_data.s_gain_x[4] = 0x9248;
					cc_data.s_gain_x[5] = 0xB6DA;
					cc_data.s_gain_x[6] = 0xDB6C;
					cc_data.s_gain_x[7] = 0xFFFF;
					cc_data.s_gain_y[0] = 0x0080;
					cc_data.s_gain_y[1] = 0x0080;
					cc_data.s_gain_y[2] = 0x0080;
					cc_data.s_gain_y[3] = 0x0080;
					cc_data.s_gain_y[4] = 0x0080;
					cc_data.s_gain_y[5] = 0x0080;
					cc_data.s_gain_y[6] = 0x0040;
					cc_data.s_gain_y[7] = 0x0000;
				}
				ret = vpq_hwrap_sethdrcolorcorrection(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]vpq_hwrap_sethdrcolorcorrection() error\n", __F__, __L__);
					break;
				}
				printk("[CC]v:%d,l:%d,wid:%d, hs:%x,%x, lxy:%x,%x,%x,%x, %x,%x,%x,%x, sxy:%x,%x,%x,%x, %x,%x,%x,%x\n",\
					param.version,param.length,param.wid,cc_data.hue_blend,cc_data.sat_blend,\
					cc_data.l_gain_x[0],cc_data.l_gain_x[1],cc_data.l_gain_x[6],cc_data.l_gain_x[7],\
					cc_data.l_gain_y[0],cc_data.l_gain_y[1],cc_data.l_gain_y[6],cc_data.l_gain_y[7],\
					cc_data.s_gain_x[0],cc_data.s_gain_x[1],cc_data.s_gain_x[6],cc_data.s_gain_x[7],\
					cc_data.s_gain_y[0],cc_data.s_gain_y[1],cc_data.s_gain_y[6],cc_data.s_gain_y[7]);
			}
			else
			{
				LX_PE_HDR_CCR_T param;
				memset(&param,0,sizeof(LX_PE_HDR_CCR_T));
				param.win_id = val[0];
				if (val[1]==1)
				{
					param.data[0]  = 0x3ff;//hue
					param.data[1]  = 0x3ff;//sat
					param.data[2]  = 1;
					param.data[3]  = 0;
					param.data[4]  = 0;
					param.data[5]  = 0;
					param.data[6]  = 0x00000000;
					param.data[7]  = 0x24920040;
					param.data[8]  = 0x49240080;
					param.data[9]  = 0x6DB60080;
					param.data[10] = 0x92480080;
					param.data[11] = 0xB6DA0080;
					param.data[12] = 0xDB6C0080;
					param.data[13] = 0xFFFF0080;
					param.data[14] = 0x00000080;
					param.data[15] = 0x24920080;
					param.data[16] = 0x49240080;
					param.data[17] = 0x6DB60080;
					param.data[18] = 0x92480080;
					param.data[19] = 0xB6DA0080;
					param.data[20] = 0xDB6C0040;
					param.data[21] = 0xFFFF0000;
				}
				ret = PE_HDR_SetColorCorrect(&param);
				if (ret!=RET_OK){
					printk("[%s,%d]PE_HDR_SetColorCorrect() error\n", __F__, __L__);
					break;
				}
				printk("[CC][wid:%d]%04x,%04x|%x,%x,%x,%x|%08x,%08x,%08x,%08x|%08x,%08x,%08x,%08x\n", \
					param.win_id,param.data[0],param.data[1],\
					param.data[2],param.data[3],param.data[4],param.data[5],\
					param.data[6],param.data[7],param.data[12],param.data[13],\
					param.data[14],param.data[15],param.data[20],param.data[21]);
			}
		}break;
		case PE_PROC_HDR_FUNC_G_EOTF:
		{
			LX_PE_HDR_EOTF_LUT_T param;
			UINT32 *p_lut_data = NULL;
			sscanf(command," %d %d %d %d",(int *)&func_num,&val[0],&val[1],&val[2]);
			if (val[2]>1023)	val[2] = 1023;
			if (val[1]>val[2])	val[1] = val[2];
			p_lut_data = (UINT32 *)OS_Malloc(sizeof(UINT32)*1024);
			if (!p_lut_data)	{printk("p_lut_data is null\n");break;}
			param.win_id = val[0];
			param.oper = 0;
			param.size = 1024;
			param.data = (UINT32 *)p_lut_data;
			ret = PE_HDR_GetEotfLut(&param);
			if (ret==RET_OK){
				for (i=val[1]; i<=val[2]; i++)	printk("[EOTF][%4d] 0x%08x\n",i,p_lut_data[i]);
			}
			if (p_lut_data)	{OS_Free(p_lut_data);}
		}break;
		case PE_PROC_HDR_FUNC_S_EOTF:
		{
			sscanf(command," %d %d %d",(int *)&func_num,&val[0],&val[1]);
			ret = vpq_hwrap_dbg_sethdreotflut(val[0],val[1]);
			if (ret!=RET_OK){
				printk("[%s,%d]vpq_hwrap_dbg_sethdreotflut() error\n", __F__, __L__);
				break;
			}
			printk("[EOTF][wid:%d]%d\n",val[0],val[1]);
		}break;
		case PE_PROC_HDR_FUNC_G_OETF:
		{
			LX_PE_HDR_OETF_LUT_T param;
			UINT32 *p_lut_data = NULL;
			sscanf(command," %d %d %d %d",(int *)&func_num,&val[0],&val[1],&val[2]);
			if (val[2]>1023)	val[2] = 1023;
			if (val[1]>val[2])	val[1] = val[2];
			p_lut_data = (UINT32 *)OS_Malloc(sizeof(UINT32)*1024);
			if (!p_lut_data)	{printk("p_lut_data is null\n");break;}
			param.win_id = val[0];
			param.oper = 0;
			param.size = 1024;
			param.data = (UINT32 *)p_lut_data;
			ret = PE_HDR_GetOetfLut(&param);
			if (ret==RET_OK){
				for (i=val[1]; i<=val[2]; i++)	printk("[OETF][%4d] 0x%08x\n",i,p_lut_data[i]);
			}
			if (p_lut_data)	{OS_Free(p_lut_data);}
		}break;
		case PE_PROC_HDR_FUNC_S_OETF:
		{
			sscanf(command," %d %d %d",(int *)&func_num,&val[0],&val[1]);
			ret = vpq_hwrap_dbg_sethdroetflut(val[0],val[1]);
			if (ret!=RET_OK){
				printk("[%s,%d]vpq_hwrap_dbg_sethdroetflut() error\n", __F__, __L__);
				break;
			}
			printk("[OETF][wid:%d]%d\n",val[0],val[1]);
		}break;
		case PE_PROC_HDR_FUNC_G_IPXL:
		{
			unsigned int status[20];
			sscanf(command," %d %d %d %d",(int *)&func_num,&val[0],&val[1],&val[2]);
			status[0] = val[0];
			status[1] = val[1];
			status[2] = val[2];
			ret = PE_HDR_GetPixelData((void *)status);
			if (ret!=RET_OK){
				printk("[%s,%d]PE_HDR_GetPixelData() error\n", __F__, __L__);
				break;
			}
			printk("[proc] %d %d %d | %d %d %d | %d %d %d\n",\
				status[0],status[1],status[2],status[3],status[4],status[5],status[6],status[7],status[8]);
		}break;
		default:
		{
			printk("invalid func numner passed from proc command\n");
		}break;
	}
	return;
}

static int pe_proc_hdr_show(struct seq_file *m, void *v)
{
	int cmd,size;
	if (!m)	return 0;

	size = (int)(sizeof(int));

	seq_printf(m, "---- hdr trace0 ----\n");
	cmd = 0;
	pe_proc_dbg_printmisctable(13,&cmd,size,m);

	seq_printf(m, "---- hdr trace1 ----\n");
	cmd = 1;
	pe_proc_dbg_printmisctable(13,&cmd,size,m);

	seq_printf(m, "---- hdr csc ----\n");
	cmd = 1;
	pe_proc_dbg_printmisctable(11,&cmd,size,m);

	seq_printf(m, "VPQ_BYPASS_BLOCK=\n");
	vpq_proc_show_status_cmn(m,v,V4L2_CID_EXT_VPQ_BYPASS_BLOCK,1);

	seq_printf(m, "VPQ_PQ_MODE_INFO=\n");
	vpq_proc_show_status_cmn(m,v,V4L2_CID_EXT_VPQ_PQ_MODE_INFO,1);

	seq_printf(m, "VPQ_EXTRA_PATTERN=\n");
	vpq_proc_show_status_cmn(m,v,V4L2_CID_EXT_VPQ_EXTRA_PATTERN,1);

	seq_printf(m, "HDR_COLOR_CORRECTION=\n");
	vpq_proc_show_status_hdr(m,v,V4L2_CID_EXT_HDR_COLOR_CORRECTION,1);

	seq_printf(m, "HDR_HLG_Y_GAIN_TBL=\n");
	vpq_proc_show_status_hdr(m,v,V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL,1);

	seq_printf(m, "VPQ_GAMUT_MATRIX_PRE=\n");
	vpq_proc_show_status_hdr(m,v,V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE,1);

	seq_printf(m, "HDR_TONEMAP=\n");
	vpq_proc_show_status_hdr(m,v,V4L2_CID_EXT_HDR_TONEMAP,1);

	return 0;
}

static int pe_proc_hdr_open(struct inode *inode, struct file *file)
{
	int ret;

	if (!file)	return 0;

	ret = single_open (file, pe_proc_hdr_show, NULL);
	if (ret < 0)
		return ret;

	return ret;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops pe_proc_hdr_fops = {
	.proc_open = pe_proc_hdr_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations pe_proc_hdr_fops = {
	.open = pe_proc_hdr_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif
void pe_proc_hdr_init(struct proc_dir_entry *entry)
{
	if (!entry)
	{
		PE_PRINT_ERROR("entry is not ready\n");
		return;
	}

	proc_create_data("hdr_status", 0440, entry, &pe_proc_hdr_fops, NULL);

	return;
}
