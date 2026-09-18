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
#include "pe_cmg.h"
#include "pe_hdr.h"
#include "pe_etc.h"
#include "pe_cmn.h"
#include "pe_csc.h"
#include "pe_nrd.h"
#include "pe_dnt.h"
#include "pe_shp.h"
#include "pe_dcm.h"
#include "pe_hst.h"
#include "pe_win.h"
#include "pe_kwrap.h"
#include "de_kapi.h"
#include "ovi_kapi.h"
#include "vpq_hwrap.h"
#include "vpq_hwrap_pe.h"
#include "vpq_hwrap_hdr.h"
#include "v4l2_vsc_event.h"
#include "v4l2_vpq_pe.h"
#include "v4l2_lgsr.h"

#include "be_proc.h"
#include "be_top_hal.h"
#include "ovi_hal.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
#define VPQ_HWRAP_USE_RESTORED_DATA

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

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/
extern int v4l2_vpq_ready_ioctl(void);

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/
extern UINT32 _g_pe_kwrap_block_defaul_setting;

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
unsigned int _g_vpq_hwrap_block_mask = 0;
unsigned int _g_vpq_hwrap_on_off = 0;
int _g_vpq_hwrap_force_pattern = 0;//0:normal,1:cc,2:hdr(SCDCR-2960),20191218,1->0

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/
static int _g_vpq_hwrap_isinitialized = 0;
static unsigned int _g_vpq_hwrap_pqmodeinfo[5];
static unsigned int _g_vpq_hwrap_pqmodeinfo1[5];
static struct v4l2_vpq_ext_pattern_info_v2 _g_vpq_hwrap_pattern = {.bOnOff=0xff,};

/*============================================================================
	Implementation Group
============================================================================*/
int vpq_hwrap_setforcepattern(int type)
{
	_g_vpq_hwrap_force_pattern = type;
	return 0;
}
int vpq_hwrap_getforcepattern(void)
{
	return _g_vpq_hwrap_force_pattern;
}

//resume_mode : 0:normal, 1:instant, 2:snapshot
int vpq_hwrap_initialize(unsigned int resume_mode)
{
	PE_CFG_CTRL_T init_param;

	/* SLT skip init(w/ task),default,ioctl(AVTASK-890) */
	if (lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		PE_PRINT_NOTI("SLT skip init (resume:%d)\n",resume_mode);
		return RET_OK;
	}

	PE_PRINT_NOTI("start(%d)(%d)\n",resume_mode,_g_vpq_hwrap_isinitialized);
	vpq_hwrap_pe_init();
	PE_IO_OpenPicEnhanceModule();
	init_param.resume_mode = resume_mode;
	PE_IO_Init(&init_param);

	KWRAP_PE_Init();
	vpq_hwrap_hdr_init();
	vpq_proc_init_block_func_pe();
	lgsr_proc_init_block_func_pe();
	PE_PRINT_NOTI("vpq block func initialized!!!!\n");

	if (_g_vpq_hwrap_isinitialized == 0)
	{
		v4l2_vpq_ready_ioctl();
	}

	_g_vpq_hwrap_isinitialized++;
	PE_PRINT_VPQ_CMN("done(%d)(%d)\n",resume_mode,_g_vpq_hwrap_isinitialized);
	return RET_OK;
}

int vpq_hwrap_uninitialize(void)
{
	PE_IO_ClosePicEnhanceModule();
	PE_PRINT_NOTI("done\n");
	return RET_OK;
}

int vpq_hwrap_isinitialized(void)
{
	return _g_vpq_hwrap_isinitialized;
}

int vpq_hwrap_setbypassblocks(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	unsigned int *p_data;
	unsigned int block_mask;
	unsigned int on_off;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	p_data = (unsigned int *)p_param->p_data;
	_g_vpq_hwrap_block_mask = block_mask = p_data[0];
	_g_vpq_hwrap_on_off = on_off = p_data[1];

	PE_PRINT_NOTI("v:%d,l:%d,wid:%d, mask:%x, en:%x\n",\
		p_param->version,p_param->length,p_param->wid,p_data[0],p_data[1]);

	if(block_mask & (0x1 | 0x2 | 0x4))
	{	// sharpness,PSP,object contrast
		LX_PE_CMN_BYPASS_BLOCKS_T peParam;

		peParam.bOnOff = on_off ? TRUE : FALSE;
		peParam.u32BlockMask = block_mask;
		PE_PRINT_VPQ_CMN("KWRAP_PE_SetBypassBlocks(): bOnOff = %d, u32BlockMask = 0x%x\n",
			peParam.bOnOff, peParam.u32BlockMask);

		ret = PE_CMN_SetBypassBlocks(&peParam);
		VPQ_HWRAP_CHECK_CODE(ret != RET_OK, return ret, "PE_CMN_SetBypassBlocks(): Error.\n");
	}

	if(block_mask & 0x8)//local dimming,UI gamma
	{
#ifdef INCLUDE_KDRV_BE
		LX_BE_SET_DEFAULT_PARAM(LX_BE_BLOCK_BYPASS_T, beBypassParams);

		beBypassParams.bLEDBypass = on_off ? TRUE : FALSE;
		ret = BE_TOP_HAL_SetBypass(&beBypassParams);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. BE_TOP_HAL_SetBypass()\n");
		PE_PRINT_VPQ_CMN("Be Bypass bLEDBypass:%d\n",beBypassParams.bLEDBypass);
#endif
	}
	if(block_mask & 0x10)//WB,4CH gamma,LODC,ODC
	{
#ifdef INCLUDE_KDRV_BE
		LX_OVI_TCON_BYPASS_T oviBypassParams;

		oviBypassParams.bEnable = on_off ? TRUE : FALSE;
		oviBypassParams.u32BlockMask = LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC;
		ret = OVI_HAL_SetBypass(&oviBypassParams);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. OVI_HAL_SetBypass()\n");
		PE_PRINT_VPQ_CMN("Ovi Bypass bEnable:%d, u32BlockMask:0x%x\n",oviBypassParams.bEnable,oviBypassParams.u32BlockMask);
#endif
	}

	if(block_mask & (0x20|0x40))//HDR
	{
		UINT32 type;
		LX_PE_HDR_MODE_INFO_T hdr_info;
		LX_PE_HDR_OP_MD_T *hdr_info_op;
		hdr_info.win_id = p_param->wid;
		type = VPQ_HWRAP_HDR_MI_HDR_OFF;
		hdr_info_op = (LX_PE_HDR_OP_MD_T *)&hdr_info.data[0];
		hdr_info_op->hdr_off = (!on_off)? 0:(block_mask & 0x20)? 1:2;
		ret = vpq_hwrap_sethdropmodeinfo(type,&hdr_info);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. vpq_hwrap_sethdropmodeinfo()\n");
		PE_PRINT_VPQ_CMN("OpMd[%d] type:%x, hdr_off:%d\n",hdr_info.win_id,type,hdr_info_op->hdr_off);
	}

	return ret;
}

int vpq_hwrap_getbypassblocks(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	unsigned int *p_data;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	p_data = (unsigned int *)p_param->p_data;
	p_data[0] = _g_vpq_hwrap_block_mask;
	p_data[1] = _g_vpq_hwrap_on_off;

	PE_PRINT_VPQ_CMN("v:%d,l:%d,wid:%d, mask:%x, en:%x\n",\
		p_param->version,p_param->length,p_param->wid,p_data[0],p_data[1]);

	return ret;
}

/**
 * [0]v4l2_ext_hdr_mode
 * - 0 : V4L2_EXT_HDR_MODE_SDR,
 * - 1 : V4L2_EXT_HDR_MODE_DOLBY,
 * - 2 : V4L2_EXT_HDR_MODE_HDR10,
 * - 3 : V4L2_EXT_HDR_MODE_HLG,
 * - 4 : V4L2_EXT_HDR_MODE_TECHNICOLOR,
 * - 5 : V4L2_EXT_HDR_MODE_HDREFFECT,
 * - 6 : V4L2_EXT_HDR_MODE_HDR2SDR,
 * [1]colorimetry
 * - 0 : BT601,
 * - 1 : BT709,
 * - 2 : BT2020,
 * [2]display_brightness
 * [3]support HDR PRIME
 * [4]reserved
 *
 * @param pData [in] HAL_VPQ_DATA_T
 * @return DTV_STATUS_T
 * @see
 * @author
 */
int vpq_hwrap_setpqmodeinfo(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	unsigned int *p_data;
	unsigned int type, ipc_mode;
	LX_PE_INF_DISPLAY_T dsp_info;
	LX_PE_HDR_MODE_INFO_T hdr_info;
	LX_PE_HDR_OP_MD_T *hdr_info_op;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	PE_PRINT_VPQ_CMN("v:%d,l:%d,wid:%d\n",p_param->version,p_param->length,p_param->wid);

	p_data = (unsigned int *)p_param->p_data;

	do {
		dsp_info.win_id = p_param->wid;
		ret = vpq_hwrap_getpicdisplayinfo((void *)&dsp_info);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,break,"Error. vpq_hwrap_getpicdisplayinfo()\n");
		dsp_info.info_type = LX_PE_INFO_MODE;
		dsp_info.mode.is_colmetry = p_data[1];
		dsp_info.mode.hdr_type = p_data[0];
		ret = vpq_hwrap_setpicdisplayinfo((void *)&dsp_info);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,break,"Error. vpq_hwrap_setpicdisplayinfo()\n");
	} while(0);

	do {
		if (p_data[0] == V4L2_EXT_HDR_MODE_DOLBY)				ipc_mode = LX_HDR_TYPE_DOLBY;
		else if (p_data[0] == V4L2_EXT_HDR_MODE_HDR10)			ipc_mode = LX_HDR_TYPE_HDR10;
		else if (p_data[0] == V4L2_EXT_HDR_MODE_HLG)			ipc_mode = LX_HDR_TYPE_HLG;
		else if (p_data[0] == V4L2_EXT_HDR_MODE_TECHNICOLOR)	ipc_mode = LX_HDR_TYPE_TECHNICOLOR;
		else if (p_data[0] == V4L2_EXT_HDR_MODE_HDREFFECT)		ipc_mode = LX_HDR_TYPE_SDR2HDR;
		#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
		else if (p_data[0] == V4L2_EXT_HDR_MODE_HDR2SDR)		ipc_mode = LX_HDR_TYPE_HDR2SDR;
		#endif
		else													ipc_mode = LX_HDR_TYPE_OFF;

		#ifdef INCLUDE_KDRV_DE
		PE_PRINT_VPQ_CMN("hdr_ipc_type[%d] ipc_mode:%d(%d)\n",p_param->wid,ipc_mode,p_data[0]);

		ret = vsc_set_hdr_ipc_type((UINT8)p_param->wid, ipc_mode, LX_HDR_MODE_FROM_PQ);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,break,"Error. vsc_set_hdr_ipc_type()\n");
		#endif
	} while(0);

	do {
		type = VPQ_HWRAP_HDR_MI_HDRCASE;
		type |= VPQ_HWRAP_HDR_MI_COLMTRY;
		type |= VPQ_HWRAP_HDR_MI_SUP_MOD;
		type |= VPQ_HWRAP_HDR_MI_DISPBRI;

		hdr_info.win_id = p_param->wid;
		hdr_info_op = (LX_PE_HDR_OP_MD_T *)&hdr_info.data[0];

		/* convert user enum to kdrv enum */
		/* 0~5:off,doby,hdr10,hlg,tech,s2h -> 0~5:off,doby,hdr10,tech,s2h,hlg */
		if (p_data[0] == V4L2_EXT_HDR_MODE_DOLBY)				hdr_info_op->hdrcase = LX_HDR_TYPE_DOLBY;
		else if (p_data[0] == V4L2_EXT_HDR_MODE_HDR10)			hdr_info_op->hdrcase = LX_HDR_TYPE_HDR10;
		else if (p_data[0] == V4L2_EXT_HDR_MODE_HLG)			hdr_info_op->hdrcase = LX_HDR_TYPE_HLG;
		else if (p_data[0] == V4L2_EXT_HDR_MODE_TECHNICOLOR)	hdr_info_op->hdrcase = LX_HDR_TYPE_TECHNICOLOR;
		else if (p_data[0] == V4L2_EXT_HDR_MODE_HDREFFECT)		hdr_info_op->hdrcase = LX_HDR_TYPE_SDR2HDR;
		#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
		else if (p_data[0] == V4L2_EXT_HDR_MODE_HDR2SDR)		hdr_info_op->hdrcase = LX_HDR_TYPE_HDR2SDR;
		#endif
		else													hdr_info_op->hdrcase = LX_HDR_TYPE_OFF;

		hdr_info_op->colmtry = p_data[1];
		hdr_info.data[1] = p_data[2];
		hdr_info_op->sup_mod = p_data[3];

		PE_PRINT_VPQ_CMN("OpMd[%d] type:%x, hc:%d,cl:%d,db:%d,sm:%d\n",\
			p_param->wid,type,hdr_info_op->hdrcase,\
			hdr_info_op->colmtry,hdr_info.data[1],hdr_info_op->sup_mod);

		ret = vpq_hwrap_sethdropmodeinfo(type,&hdr_info);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,break,"Error. vpq_hwrap_sethdropmodeinfo()\n");
	} while(0);

	if (p_param->wid == 0)
	{
		_g_vpq_hwrap_pqmodeinfo[0] = p_data[0];
		_g_vpq_hwrap_pqmodeinfo[1] = p_data[1];
		_g_vpq_hwrap_pqmodeinfo[2] = p_data[2];
		_g_vpq_hwrap_pqmodeinfo[3] = p_data[3];
	}
	else
	{
		_g_vpq_hwrap_pqmodeinfo1[0] = p_data[0];
		_g_vpq_hwrap_pqmodeinfo1[1] = p_data[1];
		_g_vpq_hwrap_pqmodeinfo1[2] = p_data[2];
		_g_vpq_hwrap_pqmodeinfo1[3] = p_data[3];
	}

	return ret;
}

int vpq_hwrap_getcurpqmodeinfo(unsigned int wid, unsigned int index)
{
	int ret;

	if (wid>1)		return 0;
	if (index>=5)	return 0;

	if (wid ==0)	ret = _g_vpq_hwrap_pqmodeinfo[index];
	else			ret = _g_vpq_hwrap_pqmodeinfo1[index];

	return ret;
}

/**
 * [0]v4l2_ext_hdr_mode
 * - 0 : V4L2_EXT_HDR_MODE_SDR,
 * - 1 : V4L2_EXT_HDR_MODE_DOLBY,
 * - 2 : V4L2_EXT_HDR_MODE_HDR10,
 * - 3 : V4L2_EXT_HDR_MODE_HLG,
 * - 4 : V4L2_EXT_HDR_MODE_TECHNICOLOR,
 * - 5 : V4L2_EXT_HDR_MODE_HDREFFECT,
 * - 6 : V4L2_EXT_HDR_MODE_HDR2SDR,
 * [1]colorimetry
 * - 0 : BT601,
 * - 1 : BT709,
 * - 2 : BT2020,
 * [2]display_brightness
 * [3]support HDR PRIME
 * [4]reserved
 *
 * @param pData [in] HAL_VPQ_DATA_T
 * @return DTV_STATUS_T
 * @see
 * @author
 */
int vpq_hwrap_getpqmodeinfo(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	unsigned int mute;
	unsigned int *p_data;
	LX_PE_HDR_MODE_INFO_T hdr_info;
	LX_PE_HDR_OP_MD_T *hdr_info_op;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	PE_PRINT_VPQ_CMN("v:%d,l:%d,wid:%d\n",p_param->version,p_param->length,p_param->wid);

	p_data = (unsigned int *)p_param->p_data;

	hdr_info.win_id = p_param->wid;

	ret = vpq_hwrap_gethdrmodeinfo(&hdr_info);
	VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. vpq_hwrap_gethdrmodeinfo()\n");

	hdr_info_op = (LX_PE_HDR_OP_MD_T *)&hdr_info.data[0];

	if (hdr_info_op->cur_mod == LX_HDR_TYPE_DOLBY)				p_data[0] = V4L2_EXT_HDR_MODE_DOLBY;
	else if (hdr_info_op->cur_mod == LX_HDR_TYPE_DOLBY_LL)		p_data[0] = V4L2_EXT_HDR_MODE_DOLBY;
	else if (hdr_info_op->cur_mod == LX_HDR_TYPE_HDR10)			p_data[0] = V4L2_EXT_HDR_MODE_HDR10;
	else if (hdr_info_op->cur_mod == LX_HDR_TYPE_HLG)			p_data[0] = V4L2_EXT_HDR_MODE_HLG;
	else if (hdr_info_op->cur_mod == LX_HDR_TYPE_TECHNICOLOR)	p_data[0] = V4L2_EXT_HDR_MODE_TECHNICOLOR;
	else if (hdr_info_op->cur_mod == LX_HDR_TYPE_SDR2HDR)		p_data[0] = V4L2_EXT_HDR_MODE_HDREFFECT;
	#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
	else if (hdr_info_op->cur_mod == LX_HDR_TYPE_HDR2SDR)		p_data[0] = V4L2_EXT_HDR_MODE_HDR2SDR;
	#endif
	else														p_data[0] = V4L2_EXT_HDR_MODE_SDR;

	#ifdef VPQ_HWRAP_USE_RESTORED_DATA
	if (p_param->wid == 0)
	{
		p_data[1] = _g_vpq_hwrap_pqmodeinfo[1];
		p_data[2] = _g_vpq_hwrap_pqmodeinfo[2];
		p_data[3] = _g_vpq_hwrap_pqmodeinfo[3];
	}
	else
	{
		p_data[1] = _g_vpq_hwrap_pqmodeinfo1[1];
		p_data[2] = _g_vpq_hwrap_pqmodeinfo1[2];
		p_data[3] = _g_vpq_hwrap_pqmodeinfo1[3];
	}
	#else
	p_data[1] = hdr_info_op->colmtry;
	p_data[2] = hdr_info.data[1];//display_brightness
	p_data[3] = hdr_info_op->sup_mod;
	#endif

	mute = KWRAP_PE_IsMuteOn(hdr_info.win_id);

	PE_PRINT_VPQ_CMN("OpMd[%d] cm,cl,db,sm:%d,%d,%d,%d, data:%d,%d,%d,%d,%d, mute:%d\n",\
		hdr_info.win_id,hdr_info_op->cur_mod,hdr_info_op->colmtry,hdr_info.data[1],\
		hdr_info_op->sup_mod,p_data[0],p_data[1],p_data[2],p_data[3],p_data[4],mute);

	return ret;
}

int vpq_hwrap_setextpattern(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	int i, pattern_location = 0;
	struct v4l2_vpq_ext_pattern_info_v2 *p;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	p = (struct v4l2_vpq_ext_pattern_info_v2 *)p_param->p_data;

	switch (_g_vpq_hwrap_pqmodeinfo[0])
	{
		case V4L2_EXT_HDR_MODE_SDR:
		case V4L2_EXT_HDR_MODE_HDR10:
		case V4L2_EXT_HDR_MODE_HLG:
		case V4L2_EXT_HDR_MODE_TECHNICOLOR:
		case V4L2_EXT_HDR_MODE_HDREFFECT:
			pattern_location = 1;
			break;
		default:
			pattern_location = 0;
			break;
	}

	if (_g_vpq_hwrap_force_pattern>0)
	{
		pattern_location = _g_vpq_hwrap_force_pattern-1;
	}

	PE_PRINT_NOTI("loc:%d(%d) (dbg:%d)\n",pattern_location,_g_vpq_hwrap_pqmodeinfo[0],_g_vpq_hwrap_force_pattern);
	PE_PRINT_NOTI("on:%d,mode:%d\n",p->bOnOff,p->eMode);
	PE_PRINT_NOTI("grad num:%d,mode:%d\n",p->stGradInfo.numGrad,p->stGradInfo.eGradMode);
	for (i=0; i<p->stGradInfo.numGrad; i++)
	{
		PE_PRINT_NOTI("[%d] %d, %x,%x,%x, %x,%x,%x, %x\n",i,\
			p->stGradInfo.stLineAttr[i].lineIdx,p->stGradInfo.stLineAttr[i].start_R,\
			p->stGradInfo.stLineAttr[i].start_G,p->stGradInfo.stLineAttr[i].start_B,\
			p->stGradInfo.stLineAttr[i].step_R,p->stGradInfo.stLineAttr[i].step_G,\
			p->stGradInfo.stLineAttr[i].step_B,p->stGradInfo.stLineAttr[i].strideSize);
	}
	PE_PRINT_NOTI("winbox num:%d\n",p->stWinboxInfo.u8NumWin);
	for (i=0; i<p->stWinboxInfo.u8NumWin; i++)
	{
		PE_PRINT_NOTI("[%d] %d, %d,%d,%d,%d, %x,%x,%x\n",i,\
			p->stWinboxInfo.stWinBoxAttr[i].winIdx,p->stWinboxInfo.stWinBoxAttr[i].x,\
			p->stWinboxInfo.stWinBoxAttr[i].y,p->stWinboxInfo.stWinBoxAttr[i].w,\
			p->stWinboxInfo.stWinBoxAttr[i].h,p->stWinboxInfo.stWinBoxAttr[i].fill_R,\
			p->stWinboxInfo.stWinBoxAttr[i].fill_G,p->stWinboxInfo.stWinBoxAttr[i].fill_B);
	}

	do {
		LX_PE_CMG_EXT_PATTERN_INFO_T stParam;
		struct v4l2_vpq_ext_pattern_winbox_info *pstWinboxInfo;
		struct v4l2_vpq_ext_pattern_gradation_info *pstGradInfo;
		pstWinboxInfo = &p->stWinboxInfo;
		pstGradInfo = &p->stGradInfo;
		memset(&stParam,0,sizeof(LX_PE_CMG_EXT_PATTERN_INFO_T));
		if (pattern_location == 0)	stParam.bOnOff = (UINT32)p->bOnOff;
		else						stParam.bOnOff = 0;
		stParam.eMode = (LX_PE_EXT_PATTERN_MODE_T)p->eMode;
		if (p->bOnOff == 1 && p->eMode == V4L2_VPQ_EXT_PATTERN_WINBOX)
		{
			stParam.stWinboxInfo.u8NumWin = (UINT32)pstWinboxInfo->u8NumWin;
			for (i = 0; i < stParam.stWinboxInfo.u8NumWin; i++)
			{
				stParam.stWinboxInfo.stWinBoxAttr[i].winIdx = pstWinboxInfo->stWinBoxAttr[i].winIdx;
				stParam.stWinboxInfo.stWinBoxAttr[i].x = pstWinboxInfo->stWinBoxAttr[i].x;
				stParam.stWinboxInfo.stWinBoxAttr[i].y = pstWinboxInfo->stWinBoxAttr[i].y;
				stParam.stWinboxInfo.stWinBoxAttr[i].w = pstWinboxInfo->stWinBoxAttr[i].w;
				stParam.stWinboxInfo.stWinBoxAttr[i].h = pstWinboxInfo->stWinBoxAttr[i].h;
				stParam.stWinboxInfo.stWinBoxAttr[i].fill_R = pstWinboxInfo->stWinBoxAttr[i].fill_R;
				stParam.stWinboxInfo.stWinBoxAttr[i].fill_G = pstWinboxInfo->stWinBoxAttr[i].fill_G;
				stParam.stWinboxInfo.stWinBoxAttr[i].fill_B = pstWinboxInfo->stWinBoxAttr[i].fill_B;
			}
		}
		else if (p->bOnOff == 1 && p->eMode == V4L2_VPQ_EXT_PATTERN_GRADATION)
		{
			stParam.stGradInfo.numGrad = (UINT32)pstGradInfo->numGrad;
			stParam.stGradInfo.eGradMode = (LX_PE_EXT_PATTERN_GRADATION_DIRECTION_T)pstGradInfo->eGradMode;
			for (i = 0; i < stParam.stGradInfo.numGrad; i++)
			{
				stParam.stGradInfo.stLineAttr[i].lineIdx = pstGradInfo->stLineAttr[i].lineIdx;
				stParam.stGradInfo.stLineAttr[i].start_R = pstGradInfo->stLineAttr[i].start_R;
				stParam.stGradInfo.stLineAttr[i].start_G = pstGradInfo->stLineAttr[i].start_G;
				stParam.stGradInfo.stLineAttr[i].start_B = pstGradInfo->stLineAttr[i].start_B;
				stParam.stGradInfo.stLineAttr[i].step_R = pstGradInfo->stLineAttr[i].step_R;
				stParam.stGradInfo.stLineAttr[i].step_G = pstGradInfo->stLineAttr[i].step_G;
				stParam.stGradInfo.stLineAttr[i].step_B = pstGradInfo->stLineAttr[i].step_B;
				stParam.stGradInfo.stLineAttr[i].strideSize = pstGradInfo->stLineAttr[i].strideSize;
			}
		}
		PE_PRINT_NOTI("[CMG]loc:%d,on:%d,mode:%d\n",pattern_location,stParam.bOnOff,stParam.eMode);
		ret = PE_CMG_SetExtInnerPattern(&stParam);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,break,"Error. PE_CMG_SetExtInnerPattern()\n");
	} while(0);

	do {
		struct v4l2_vpq_ext_pattern_info_v2 param;
		memcpy(&param,p,sizeof(struct v4l2_vpq_ext_pattern_info_v2));
		if (pattern_location == 1)	param.bOnOff = p->bOnOff;
		else						param.bOnOff = 0;
		PE_PRINT_NOTI("[HDR]loc:%d,on:%d,mode:%d\n",pattern_location,param.bOnOff,param.eMode);
		ret = PE_HDR_SetPattern((void *)&param);
		VPQ_HWRAP_CHECK_CODE(ret!=RET_OK,return ret,"Error. PE_HDR_SetPattern()\n");
	} while(0);

	memcpy(&_g_vpq_hwrap_pattern,p,sizeof(struct v4l2_vpq_ext_pattern_info_v2));

	return ret;
}

int vpq_hwrap_getextpattern(struct v4l2_ext_vpq_cmn_data *p_param)
{
	int ret = RET_OK;
	int i, pattern_location = 0;
	struct v4l2_vpq_ext_pattern_info_v2 *p;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");
	VPQ_HWRAP_CHECK_CODE(!p_param->p_data,return RET_ERROR,"Error. p_param->p_data is null.\n");

	p = (struct v4l2_vpq_ext_pattern_info_v2 *)p_param->p_data;

	memcpy(p,&_g_vpq_hwrap_pattern,sizeof(struct v4l2_vpq_ext_pattern_info_v2));

	switch (_g_vpq_hwrap_pqmodeinfo[0])
	{
		case V4L2_EXT_HDR_MODE_SDR:
		case V4L2_EXT_HDR_MODE_HDR10:
		case V4L2_EXT_HDR_MODE_HLG:
		case V4L2_EXT_HDR_MODE_TECHNICOLOR:
		case V4L2_EXT_HDR_MODE_HDREFFECT:
			pattern_location = 2;
			break;
		default:
			pattern_location = 1;
			break;
	}

	if (_g_vpq_hwrap_force_pattern>0)
	{
		pattern_location = _g_vpq_hwrap_force_pattern;
	}

	PE_PRINT_NOTI("loc:%d(%d) (dbg:%d)\n",pattern_location,_g_vpq_hwrap_pqmodeinfo[0],_g_vpq_hwrap_force_pattern);
	PE_PRINT_NOTI("on:%d,mode:%d\n",p->bOnOff,p->eMode);
	PE_PRINT_NOTI("grad num:%d,mode:%d\n",p->stGradInfo.numGrad,p->stGradInfo.eGradMode);
	for (i=0; i<4; i++)
	{
		PE_PRINT_NOTI("[%d] %d, %x,%x,%x, %x,%x,%x, %x\n",i,\
			p->stGradInfo.stLineAttr[i].lineIdx,p->stGradInfo.stLineAttr[i].start_R,\
			p->stGradInfo.stLineAttr[i].start_G,p->stGradInfo.stLineAttr[i].start_B,\
			p->stGradInfo.stLineAttr[i].step_R,p->stGradInfo.stLineAttr[i].step_G,\
			p->stGradInfo.stLineAttr[i].step_B,p->stGradInfo.stLineAttr[i].strideSize);
	}
	PE_PRINT_NOTI("winbox num:%d\n",p->stWinboxInfo.u8NumWin);
	for (i=0; i<4; i++)
	{
		PE_PRINT_NOTI("[%d] %d, %d,%d,%d,%d, %x,%x,%x\n",i,\
			p->stWinboxInfo.stWinBoxAttr[i].winIdx,p->stWinboxInfo.stWinBoxAttr[i].x,\
			p->stWinboxInfo.stWinBoxAttr[i].y,p->stWinboxInfo.stWinBoxAttr[i].w,\
			p->stWinboxInfo.stWinBoxAttr[i].h,p->stWinboxInfo.stWinBoxAttr[i].fill_R,\
			p->stWinboxInfo.stWinBoxAttr[i].fill_G,p->stWinboxInfo.stWinBoxAttr[i].fill_B);
	}
	return ret;
}

int vpq_hwrap_getpicdisplayinfo(void *p_param)
{
	int ret = RET_OK;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");

	ret = PE_ETC_GetDisplayInfo((LX_PE_INF_DISPLAY_T *)p_param);
	return ret;
}

int vpq_hwrap_setpicdisplayinfo(void *p_param)
{
	int ret = RET_OK;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");

	ret = PE_ETC_SetDisplayInfo((LX_PE_INF_DISPLAY_T *)p_param);
	return ret;
}

int vpq_hwrap_setdefaultsettings(void *param)
{
	int ret = RET_OK;
	LX_PE_DEFAULT_SETTINGS_T *pp = NULL;
	if (_g_pe_kwrap_block_defaul_setting)
		return ret;
	VPQ_HWRAP_CHECK_CODE(!param,return RET_ERROR,"Error. p_param is null.\n");

	/* SLT skip init(w/ task),default,ioctl(AVTASK-890) */
	if (lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		PE_PRINT_NOTI("SLT skip default\n");
		return RET_OK;
	}

	pp = (LX_PE_DEFAULT_SETTINGS_T *)param;
	ret = PE_CMN_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_CMN_SetDefaultSettings() error..\n");
	ret = PE_CSC_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_CSC_SetDefaultSettings() error..\n");
	ret = PE_CMG_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_CMG_SetDefaultSettings() error..\n");
	ret = PE_NRD_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_NRD_SetDefaultSettings() error..\n");
	ret = PE_DNT_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_DNT_SetDefaultSettings() error..\n");
	ret = PE_SHP_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_SHP_SetDefaultSettings() error..\n");
	ret = PE_DCM_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_DCM_SetDefaultSettings() error..\n");
	ret = PE_HST_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_HST_SetDefaultSettings() error..\n");
	ret = PE_HDR_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_HDR_SetDefaultSettings() error..\n");
	ret = PE_WIN_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_WIN_SetDefaultSettings() error..\n");
	ret = PE_ETC_SetDefaultSettings(pp);
	VPQ_HWRAP_CHECK_CODE(ret,return RET_ERROR, "PE_ETC_SetDefaultSettings() error..\n");
	return ret;
}

int vpq_hwrap_setinputcscparam(void *p_param)
{
	int ret = RET_OK;

	VPQ_HWRAP_CHECK_CODE(!p_param,return RET_ERROR,"Error. p_param is null.\n");

	ret = PE_CSC_SetInputCsc((LX_PE_CSC_INPUT_T *)p_param);
	return ret;
}


