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

/** @file pe_inf_m23.c
 *
 *  information management for picture enhance. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.15
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
#include <linux/kthread.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_hw_m23.h"
#include "pe_reg_m23.h"
#include "pe_inf_m23.h"
#include "pe_fwi_m23.h"
#include "pe_win_hw_m23.h"
#include "pe_shp_hw_m23.h"
#include "pe_hst_hw_m23.h"
#include "pe_cmn_hw_m23.h"
#include "pe_dnt_hw_m23.h"
#include "pe_nrd_hw_m23.h"
#include "pe_csc_hw_m23.h"
#include "pe_hdr_hw_m23.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* drv ver, yyyy/mm/dd/hh:mm */
#define PE_INF_M23_DRV_VER		"2020/10/12/19:60"

#define PE_INF_M23_BUF_MAX				50

#define PE_INF_M23_SCL_RESIZE_H_UHD_MAX		1920	/* 3840 * 0.5 */
#define PE_INF_M23_SCL_RESIZE_V_UHD_MAX		1080	/* 2160 * 0.5 */
#define PE_INF_M23_SCL_RESIZE_H_FHD_MAX		960	/* 1920 * 0.5 */
#define PE_INF_M23_SCL_RESIZE_V_FHD_MAX		540	/* 1080 * 0.5 */
#define PE_INF_M23_SCL_RESIZE_H_SHD_MAX		683	/* 1366 * 0.5 */
#define PE_INF_M23_SCL_RESIZE_V_SHD_MAX		384	/* 768  * 0.5 */

#define PE_INF_M23_INC_CHPI_CNT_MAX		0xff

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_INF_M23_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_PRINT_ERROR(fmt,##args);_action;}}

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
PE_INF_M23_TIME_T;

/**
 *	pe trace data buffer type
 */
typedef struct {
	PE_INF_M23_TIME_T time;			///< time
	char str[PE_TRACE_STR_SIZE];	///< str
}
PE_INF_M23_DATA_BUF_T;

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
static int PE_INF_M23_GetGeneralPicInfo(LX_PE_ETC_TBL_T *pstParams);
static int PE_INF_M23_SortTraceDataBuf(UINT32 type, PE_INF_M23_DATA_BUF_T *dst);
static int PE_INF_M23_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_INF_M23_DATA_BUF_T _g_pe_inf_m23_buf[PE_INF_M23_BUF_MAX];
static PE_INF_M23_DATA_BUF_T _g_pe_inf_m23_buf_temp[PE_INF_M23_BUF_MAX];
static PE_INF_M23_DATA_BUF_T _g_pe_inf_m23_db_buf[PE_INF_M23_BUF_MAX];
static PE_INF_M23_DATA_BUF_T _g_pe_inf_m23_db_buf_temp[PE_INF_M23_BUF_MAX];

static UINT32 _g_pe_inf_m23_trace=0x0;		//default should be off.
static PE_INF_M23_SETTINGS_T _g_pe_inf_hw_m23_info;

static PE_ETC_MISC_TBL_T _g_pe_inf_m23_dbg_set_fn[] = {\
	{/* 00 */ PE_TSK_M23_SetTaskOperation,		"PE_TSK_M23_SetTaskOperation"}, \
	{/* 01 */ NULL,				"NULL"}, \
	{/* 02 */ NULL,				"NULL"}, \
	{/* 03 */ NULL,				"NULL"}, \
	{/* 04 */ NULL,				"NULL"}, \
};
static PE_ETC_MISC_TBL_T _g_pe_inf_m23_dbg_get_fn[] = {\
	{/* 00 */ PE_TSK_M23_GetTaskOperation,		"PE_TSK_M23_GetTaskOperation"}, \
	{/* 01 */ NULL,				"NULL"}, \
	{/* 02 */ PE_INF_M23_GetGeneralPicInfo,		"PE_INF_M23_GetGeneralPicInfo"}, \
	{/* 03 */ PE_HST_HW_M23_GetGlobalHistInfo,	"PE_HST_HW_M23_GetGlobalHistInfo"}, \
	{/* 04 */ NULL,				"NULL"}, \
	{/* 05 */ NULL,				"NULL"}, \
	{/* 06 */ PE_DNT_HW_M23_RdDefault,			"PE_DNT_HW_M23_RdDefault"}, \
	{/* 07 */ PE_NRD_HW_M23_RdDefault,			"PE_NRD_HW_M23_RdDefault"}, \
	{/* 08 */ PE_SHP_HW_M23_RdDefault,			"PE_SHP_HW_M23_RdDefault"}, \
	{/* 09 */ PE_INF_M23_GetTraceDataBuf,		"PE_INF_M23_GetTraceDataBuf"}, \
	{/* 10 */ NULL,				"NULL"}, \
	{/* 11 */ PE_HDR_HW_M23_GetGeneralInfo,		"PE_HDR_HW_M23_GetGeneralInfo"}, \
	{/* 12 */ NULL,				"NULL"}, \
	{/* 13 */ PE_HDR_HW_M23_GetTraceDataBuf,	"PE_HDR_HW_M23_GetTraceDataBuf"}
};

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init inf
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	PE_REG_M23_HW_OPT_T hw_opt = PE_REG_M23_GetDispOpt();
	do{
		CHECK_KNULL(pstParams);
		PE_PRINT_NOTI("init info values.\n");
		memset0(_g_pe_inf_hw_m23_info);
		_g_pe_inf_hw_m23_info.ctrl_info[0].panel_resolution = hw_opt.panel_resolution;
	}while(0);
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
int PE_INF_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_pe_inf_m23_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(ETC)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(ETC)),\
			pstParams->print_lvl,_g_pe_inf_m23_trace,pstParams->bypass);
	}while(0);
	return ret;
}
/**
 * set display info
 *
 * @param   *pstParams [in] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_SetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	UINT32 colorimetry;
	PE_FWI_M23_SRC_INFO fwi_src;
	LX_PE_INF_DISPLAY_T *pp = NULL;
	UINT32 i;
	LX_PE_INF_DISPLAY_T *p_inf = _g_pe_inf_hw_m23_info.disp_info;
	do{
		static LX_PE_INF_DISPLAY_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		pp = (LX_PE_INF_DISPLAY_T *)pstParams;
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_INF_DISPLAY_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_INF("duplicated DB : LX_PE_INF_DISPLAY_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_INF("set[%d] : info type:%d src:%d,res:%d (h:%d,v:%d)\n"\
			"fr:%d(%d),scan:%d,cstd:%d,hdmi:%d,scart:%d,dtv:%d,hdd:%d\n"\
			"in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d,mw:%d,sub_m:%d\n"\
			"mode: rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n",\
			pp->win_id, pp->info_type, pp->src_type, pp->fmt_type, pp->in_h_size, pp->in_v_size, \
			pp->fr_type, pp->in_f_rate, pp->scan_type, pp->cstd_type, \
			pp->hdmi_type, pp->scart_type, pp->dtv_type, pp->hdd_type, \
			pp->in_win.x_ofst, pp->in_win.y_ofst, \
			pp->in_win.h_size, pp->in_win.v_size, \
			pp->out_win.x_ofst, pp->out_win.y_ofst, \
			pp->out_win.h_size, pp->out_win.v_size, pp->act_fmt,pp->mul_win,pp->sub_mode, \
			pp->mode.is_reverse, pp->mode.is_oled,pp->mode.is_colmetry, pp->mode.is_vr, \
			pp->mode.is_420, pp->mode.is_orbit, pp->mode.is_dsc);

		for (i=0;i<LX_PE_WIN_ALL;i++)
		{
			if (pstParams->win_id==i||pstParams->win_id==LX_PE_WIN_ALL)
			{
				switch(pstParams->info_type)
				{
					case LX_PE_INFO_PIC_FORMAT:
					{
						p_inf[i].src_type  = pstParams->src_type;
						p_inf[i].fmt_type  = pstParams->fmt_type;
						p_inf[i].in_h_size = pstParams->in_h_size;
						p_inf[i].in_v_size = pstParams->in_v_size;
						p_inf[i].fr_type   = pstParams->fr_type;
						p_inf[i].in_f_rate = pstParams->in_f_rate;
						p_inf[i].scan_type = pstParams->scan_type;
						p_inf[i].cstd_type = pstParams->cstd_type;
					}
					break;
					case LX_PE_INFO_DEFAULT:
					{
						p_inf[i].dtv_type  = pstParams->dtv_type;
						p_inf[i].hdmi_type	= pstParams->hdmi_type;
						p_inf[i].scart_type = pstParams->scart_type;
					}
					break;
					case LX_PE_INFO_IN_WIN:
					{
						p_inf[i].in_win.x_ofst= pstParams->in_win.x_ofst;
						p_inf[i].in_win.y_ofst= pstParams->in_win.y_ofst;
						p_inf[i].in_win.h_size= pstParams->in_win.h_size;
						p_inf[i].in_win.v_size= pstParams->in_win.v_size;
					}
					break;
					case LX_PE_INFO_OUT_WIN:
					{
						p_inf[i].out_win.x_ofst= pstParams->out_win.x_ofst;
						p_inf[i].out_win.y_ofst= pstParams->out_win.y_ofst;
						p_inf[i].out_win.h_size= pstParams->out_win.h_size;
						p_inf[i].out_win.v_size= pstParams->out_win.v_size;
					}
					break;
					case LX_PE_INFO_MODE:
					{
						p_inf[i].mode.is_colmetry= pstParams->mode.is_colmetry;
						p_inf[i].mode.is_420	 = pstParams->mode.is_420	 ;
						p_inf[i].mode.is_dsc	 = pstParams->mode.is_dsc	 ;
					}
					break;
					case LX_PE_INFO_NUM:
					{
						memcpy(&p_inf[i], pp, sizeof(LX_PE_INF_DISPLAY_T));
					}
					break;
					default:
					break;
				}
			}
			/* sync parameters with no relationship to window */
			switch(pstParams->info_type)
			{
				case LX_PE_INFO_DEFAULT:
				{
					p_inf[i].hdd_type		 = pstParams->hdd_type;
				}
				break;
				case LX_PE_INFO_MISC:
				{
					p_inf[i].act_fmt		 = pstParams->act_fmt;
					p_inf[i].mul_win		 = pstParams->mul_win;
					p_inf[i].sub_mode		 = pstParams->sub_mode;
				}
				break;
				case LX_PE_INFO_MODE:
				{
					p_inf[i].mode.is_reverse = pstParams->mode.is_reverse;
					p_inf[i].mode.is_oled	 = pstParams->mode.is_oled;
					p_inf[i].mode.is_vr 	 = pstParams->mode.is_vr;
					p_inf[i].mode.is_orbit = pstParams->mode.is_orbit;
				}
				break;
				default:
				break;
			}
		}
		if (pstParams->win_id==LX_PE_WIN_0)
		{
			/* src info */
			if(pstParams->info_type == LX_PE_INFO_DEFAULT)
			{
				fwi_src.dtv_mode = pstParams->dtv_type;
				fwi_src.hdd_mode = pstParams->hdd_type;
				ret = PE_FWI_M23_SetSrcInfo(&fwi_src);
				PE_INF_M23_CHECK_CODE(ret,break,"PE_FWI_M23_SetSrcInfo() error.\n");
			}
		}

		/* colorimetry */
		if(pstParams->info_type == LX_PE_INFO_MODE)
		{
			colorimetry = pstParams->mode.is_colmetry;
			ret = PE_FWI_M23_SetColorimetry(pstParams->win_id,&colorimetry);
			PE_INF_M23_CHECK_CODE(ret,break,"PE_FWI_M23_SetColorimetry() error.\n");
		}
	}while(0);
	return ret;
}

/**
 * get display info
 *
 * @param   *pstParams [in/out] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_GetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id,temp;
	UINT32 i;
	LX_PE_INF_DISPLAY_T *p_inf = _g_pe_inf_hw_m23_info.disp_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		for (i=0;i<LX_PE_WIN_ALL;i++)
		{
			if (win_id==i)
			{
				temp = pstParams->win_id;
				memcpy(pstParams,&p_inf[i],sizeof(LX_PE_INF_DISPLAY_T));
				pstParams->win_id = temp;
			}
		}
	}while(0);
	return ret;
}
/**
 * get current disp info.
 *
 * @param   wid [in] UINT32
 * @param   *pstParams [in/out] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_GetCurDispInfSettings(UINT32 wid, LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pstParams);
		if (wid == LX_PE_WIN_1)
		{
			memcpy(pstParams,disp1_info,sizeof(LX_PE_INF_DISPLAY_T));
		}
		else
		{
			memcpy(pstParams,disp0_info,sizeof(LX_PE_INF_DISPLAY_T));
		}
	}while(0);
	return ret;
}
/**
 * get current ctrl info.
 *
 * @param   wid [in] UINT32
 * @param   *pstParams [in/out] PE_INF_M23_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_GetCurCtrlInfSettings(UINT32 wid, PE_INF_M23_CTRL_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl0_info = &_g_pe_inf_hw_m23_info.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl1_info = &_g_pe_inf_hw_m23_info.ctrl_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pstParams);
		if (wid == LX_PE_WIN_1)
		{
			memcpy(pstParams,ctrl1_info,sizeof(PE_INF_M23_CTRL_T));
		}
		else
		{
			memcpy(pstParams,ctrl0_info,sizeof(PE_INF_M23_CTRL_T));
		}
	}while(0);
	return ret;
}
/**
 * get current mode info.
 *
 * @param   wid [in] UINT32
 * @param   *pstParams [in/out] LX_PE_INF_OP_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_GetCurModeInfSettings(UINT32 wid, LX_PE_INF_OP_MODE_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pstParams);
		*pstParams = (wid == LX_PE_WIN_1)? disp1_info->mode:disp0_info->mode;
	}while(0);
	return ret;
}
/**
 * check(get) scaler info.
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_CheckSclInfo(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 r_data;
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl0_info = &_g_pe_inf_hw_m23_info.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl1_info = &_g_pe_inf_hw_m23_info.ctrl_info[LX_PE_WIN_1];
	LX_PE_INF_DISPLAY_T *disp0_info=&_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info=&_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_1];
	UINT32 resize_h_max;
	UINT32 resize_v_max;
	do{
		/* L */
		ctrl0_info->u_i_win_h_ofst = disp0_info->in_win.x_ofst;
		ctrl0_info->u_i_win_v_ofst = disp0_info->in_win.y_ofst;
		ctrl0_info->u_i_win_h_size = disp0_info->in_win.h_size;
		ctrl0_info->u_i_win_v_size = disp0_info->in_win.v_size;
		ctrl0_info->u_o_win_h_ofst = disp0_info->out_win.x_ofst;
		ctrl0_info->u_o_win_v_ofst = disp0_info->out_win.y_ofst;
		ctrl0_info->u_o_win_h_size = disp0_info->out_win.h_size;
		ctrl0_info->u_o_win_v_size = disp0_info->out_win.v_size;
		PE_ND0_M23_RdFL(pe0_src_size);
		PE_ND0_M23_Rd01(pe0_src_size, cs_type, ctrl0_info->i_c_format);//0x6:444,0x5:422, else 420
		PE_ND0_M23_Rd01(pe0_src_size, hsize, ctrl0_info->pe0_src_h);
		PE_ND0_M23_Rd01(pe0_src_size, vsize, ctrl0_info->pe0_src_v);
		PE_ND0_M23_Rd01(pe0_src_size, scan_type, ctrl0_info->i_sc_type);//1:p, 0:i
		/* R */
		ctrl1_info->u_i_win_h_ofst = disp1_info->in_win.x_ofst;
		ctrl1_info->u_i_win_v_ofst = disp1_info->in_win.y_ofst;
		ctrl1_info->u_i_win_h_size = disp1_info->in_win.h_size;
		ctrl1_info->u_i_win_v_size = disp1_info->in_win.v_size;
		ctrl1_info->u_o_win_h_ofst = disp1_info->out_win.x_ofst;
		ctrl1_info->u_o_win_v_ofst = disp1_info->out_win.y_ofst;
		ctrl1_info->u_o_win_h_size = disp1_info->out_win.h_size;
		ctrl1_info->u_o_win_v_size = disp1_info->out_win.v_size;
		ctrl1_info->i_c_format = ctrl0_info->i_c_format;
		ctrl1_info->pe0_src_h = ctrl0_info->pe0_src_h;
		ctrl1_info->pe0_src_v = ctrl0_info->pe0_src_v;
		ctrl1_info->i_sc_type = ctrl0_info->i_sc_type;
		/* etc */
		ctrl0_info->hv_same = (ctrl0_info->u_o_win_h_size==ctrl1_info->u_o_win_h_size && \
			ctrl0_info->u_o_win_v_size==ctrl1_info->u_o_win_v_size)? 1:0;
		if(ctrl0_info->panel_resolution == 1) // FHD
		{
			resize_h_max = PE_INF_M23_SCL_RESIZE_H_FHD_MAX;
			resize_v_max = PE_INF_M23_SCL_RESIZE_V_FHD_MAX;
		}
		else if(ctrl0_info->panel_resolution == 2) //HD 1366x768
		{
			resize_h_max = PE_INF_M23_SCL_RESIZE_H_SHD_MAX;
			resize_v_max = PE_INF_M23_SCL_RESIZE_V_SHD_MAX;
		}
		else //4k
		{
			resize_h_max = PE_INF_M23_SCL_RESIZE_H_UHD_MAX;
			resize_v_max = PE_INF_M23_SCL_RESIZE_V_UHD_MAX;
		}

		ctrl1_info->hv_same = (ctrl0_info->u_o_win_h_size<resize_h_max && \
			ctrl0_info->u_o_win_v_size<resize_v_max)? 1:0;
		ret = PE_HST_HW_M23_GetSaturationState(LX_PE_WIN_0,&r_data);
		if(ret)	{PE_PRINT_ERROR("PE_HST_HW_M23_GetSaturationState() error.\n");}
		ctrl0_info->sat_status = r_data;
		ret = PE_HST_HW_M23_GetSaturationState(LX_PE_WIN_1,&r_data);
		if(ret)	{PE_PRINT_ERROR("PE_HST_HW_M23_GetSaturationState() error.\n");}
		ctrl1_info->sat_status = r_data;
		PE_CC2_PE1_M23_QRd01(pe1_mute_ctrl_00, pxl_rep_in_0,	ctrl0_info->mute_on);
		PE_CC2_PE1_M23_QRd01(pe1_mute_ctrl_05, pxl_rep_in_0,	ctrl1_info->mute_on);
		PE_VCP_DISP_M23_QRd02(vcp_wcp_m_ctrl_5, set_w0_dark_en,	ctrl0_info->vcp_mute_on,\
													set_w1_dark_en,	ctrl1_info->vcp_mute_on);
		PE_CC_PE1_M23_QRd01(pe1_fsw_ctrl_00,	reg_color_filter_status,ctrl0_info->pxl_rp_st);
		ctrl1_info->pxl_rp_st = ctrl0_info->pxl_rp_st;
		PE_CC_PE1_M23_RdFL(pe1_fsw_ctrl_02);
		PE_CC_PE1_M23_Rd01(pe1_fsw_ctrl_02,	reg_src_freeze,	ctrl0_info->is_src_frz);
		PE_CC_PE1_M23_Rd01(pe1_fsw_ctrl_02,	reg_src_info,	ctrl0_info->fw_src);
		PE_CCO_VERI_M23_QRd01(video_delay_sts0, skip_nd0,	ctrl0_info->is_ndskip);
		ctrl1_info->is_src_frz = ctrl0_info->is_src_frz;
		ctrl1_info->fw_src = ctrl0_info->fw_src;
		ctrl1_info->is_ndskip = ctrl0_info->is_ndskip;
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get current info.
 *
 * @param   *pstParams [in/out] PE_INF_M23_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_GetCurInfSettings(PE_INF_M23_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	static UINT32 count = 0;
	PE_INF_M23_SETTINGS_T *pInfo = &_g_pe_inf_hw_m23_info;
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_1];
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl0_info = &_g_pe_inf_hw_m23_info.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl1_info = &_g_pe_inf_hw_m23_info.ctrl_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pstParams);

		memcpy(pstParams,pInfo,sizeof(PE_INF_M23_SETTINGS_T));
		if(count>PE_PRINT_COUNT_NUM)
		{
			PE_DBG_INF("disp[0] : src:%d,fmt:%d (h:%d,v:%d)\n", \
				disp0_info->src_type, disp0_info->fmt_type, \
				disp0_info->in_h_size, disp0_info->in_v_size);
			PE_DBG_INF("disp[0] : fr:%d(%d),scan:%d,cstd,hdmi,scart,dtv,hdd:%d,%d,%d,%d,%d\n", \
				disp0_info->fr_type, disp0_info->in_f_rate, disp0_info->scan_type, \
				disp0_info->cstd_type, disp0_info->hdmi_type, disp0_info->scart_type, \
				disp0_info->dtv_type, disp0_info->hdd_type);
			PE_DBG_INF("disp[0] : in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d\n", \
				disp0_info->in_win.x_ofst, disp0_info->in_win.y_ofst, \
				disp0_info->in_win.h_size, disp0_info->in_win.v_size, \
				disp0_info->out_win.x_ofst, disp0_info->out_win.y_ofst, \
				disp0_info->out_win.h_size, disp0_info->out_win.v_size, disp0_info->act_fmt);
			PE_DBG_INF("disp[0] : rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n", \
				disp0_info->mode.is_reverse, disp0_info->mode.is_oled,\
				disp0_info->mode.is_colmetry, disp0_info->mode.is_vr, disp0_info->mode.is_420, disp0_info->mode.is_orbit,disp0_info->mode.is_dsc);
			PE_DBG_INF("ctrl[0] : src:%d,%d,sc:%d, u_w i:%d,%d,%d,%d, o:%d,%d,%d,%d\n",\
				ctrl0_info->pe0_src_h,ctrl0_info->pe0_src_v,ctrl0_info->i_sc_type,\
				ctrl0_info->u_i_win_h_ofst,ctrl0_info->u_i_win_v_ofst,\
				ctrl0_info->u_i_win_h_size,ctrl0_info->u_i_win_v_size,\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,\
				ctrl0_info->u_o_win_h_size,ctrl0_info->u_o_win_v_size);
			PE_DBG_INF("ctrl[0] : c_fmt:%d,s_stat:%d,mute_on:%d,hv_same:%d\n",\
				ctrl0_info->i_c_format,\
				ctrl0_info->sat_status,\
				ctrl0_info->mute_on,ctrl0_info->hv_same);
			PE_DBG_INF("ctrl[0] : pxl_rp,s_frz,f_s,vcp_mute_on,is_ndskip,panel_resolution:%d,%d,%d,%d,%d,%d\n",\
				ctrl0_info->pxl_rp_st,ctrl0_info->is_src_frz,ctrl0_info->fw_src,\
				ctrl0_info->vcp_mute_on,ctrl0_info->is_ndskip,ctrl0_info->panel_resolution);
			PE_DBG_INF("disp[1] : src:%d,fmt:%d (h:%d,v:%d)\n", \
				disp1_info->src_type, disp1_info->fmt_type, \
				disp1_info->in_h_size, disp1_info->in_v_size);
			PE_DBG_INF("disp[1] : fr:%d(%d),scan:%d,cstd,hdmi,scart,dtv,hdd:%d,%d,%d,%d,%d\n", \
				disp1_info->fr_type, disp1_info->in_f_rate, disp1_info->scan_type, \
				disp1_info->cstd_type, disp1_info->hdmi_type, disp1_info->scart_type, \
				disp1_info->dtv_type, disp1_info->hdd_type);
			PE_DBG_INF("disp[1] : in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d\n", \
				disp1_info->in_win.x_ofst, disp1_info->in_win.y_ofst, \
				disp1_info->in_win.h_size, disp1_info->in_win.v_size, \
				disp1_info->out_win.x_ofst, disp1_info->out_win.y_ofst, \
				disp1_info->out_win.h_size, disp1_info->out_win.v_size, disp1_info->act_fmt);
			PE_DBG_INF("disp[1] : rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n", \
				disp1_info->mode.is_reverse, disp1_info->mode.is_oled,\
				disp1_info->mode.is_colmetry, disp1_info->mode.is_vr,disp1_info->mode.is_420,disp1_info->mode.is_orbit,disp1_info->mode.is_dsc);
			PE_DBG_INF("ctrl[1] : src:%d,%d,sc:%d, u_w i:%d,%d,%d,%d, o:%d,%d,%d,%d\n",\
				ctrl1_info->pe0_src_h,ctrl1_info->pe0_src_v,ctrl1_info->i_sc_type,\
				ctrl1_info->u_i_win_h_ofst,ctrl1_info->u_i_win_v_ofst,\
				ctrl1_info->u_i_win_h_size,ctrl1_info->u_i_win_v_size,\
				ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);
			PE_DBG_INF("ctrl[1] : c_fmt:%d,s_stat:%d,mute_on:%d,hv_same:%d\n",\
				ctrl1_info->i_c_format,\
				ctrl1_info->sat_status,\
				ctrl1_info->mute_on,ctrl1_info->hv_same);
			PE_DBG_INF("ctrl[1] : pxl_rp,s_frz,f_s,vcp_mute_on,is_ndskip,panel_resolution:%d,%d,%d,%d,%d,%d\n",\
				ctrl1_info->pxl_rp_st,ctrl1_info->is_src_frz,ctrl1_info->fw_src,\
				ctrl1_info->vcp_mute_on,ctrl1_info->is_ndskip,ctrl1_info->panel_resolution);
			
			PE_DBG_INF("\n");
			count=0;
		}
		count++;
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get general(all) picture info
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_INF_M23_GetGeneralPicInfo(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0;
	PE_WIN_HW_M23_SETTINGS_T *win_set = NULL;
	static PE_DDR_M23_TOP_HEADER_T *p_h_top = NULL;
	static PE_DDR_M23_DATA_T *p_sec_data = NULL;
	__attribute__((unused)) static PE_LGSR_DDR_M23_TOP_HEADER_T *p_h_top_lgsr = NULL;
	__attribute__((unused)) static PE_LGSR_DDR_M23_DATA_T *p_sec_data_lgsr = NULL;
	static UINT32 ddr_total=0;
	LX_PE_INF_DISPLAY_T *disp0_inf = &(_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_0]);
	LX_PE_INF_DISPLAY_T *disp1_inf = &(_g_pe_inf_hw_m23_info.disp_info[LX_PE_WIN_1]);
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl0_inf = &(_g_pe_inf_hw_m23_info.ctrl_info[LX_PE_WIN_0]);
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl1_inf = &(_g_pe_inf_hw_m23_info.ctrl_info[LX_PE_WIN_1]);

#define WIN0	LX_PE_WIN_0
#define WIN1	LX_PE_WIN_1
#define PE_INF_M23_PRINT_START		"START_OF_PRINT"
#define PE_INF_M23_PRINT_RESERVED	"RESERVED"
#define PE_INF_M23_PRINT_END		"END_OF_PRINT"
#define PE_INF_M23_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_INF_M23_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE, "   [0x%02x] %s\n", (_item), #_item);_action;break
#define PE_INF_M23_CASE_SPRINT(_cnt,_action,_buf,fmt,args...)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break
#define PE_INF_M23_DFLT_SPRINT(_action,_buf,fmt,args...)		\
	default:snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);

		rd_cnt = pstParams->oper;
		if (pstParams->data[0]==PE_INF_HW_M23_GINFO_DISPLAY)
		{
			switch (rd_cnt)
			{
				PE_INF_M23_CASE_SPRINT( 0, rd_cnt++, buffer, PE_INF_M23_PRINT_START);
				PE_INF_M23_CASE_PRMENU( 1, rd_cnt++, buffer, PE_INF_HW_M23_GINFO__KDRV_INFO);
				PE_INF_M23_CASE_PRMENU( 2, rd_cnt++, buffer, PE_INF_HW_M23_GINFO_DDR_H_PHYS);
				PE_INF_M23_CASE_PRMENU( 3, rd_cnt++, buffer, PE_INF_HW_M23_GINFO_DDR_H_SHDW);
				PE_INF_M23_CASE_PRMENU( 4, rd_cnt++, buffer, PE_INF_HW_M23_GINFO_LGSR_DDR_H_PHYS);
				PE_INF_M23_CASE_PRMENU( 5, rd_cnt++, buffer, PE_INF_HW_M23_GINFO_LGSR_DDR_H_SHDW);
				PE_INF_M23_CASE_SPRINT( 9, rd_cnt++, buffer, PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(10, rd_cnt++, buffer, PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_DFLT_SPRINT(rd_cnt=0, buffer, PE_INF_M23_PRINT_END);
			}
		}
		else if (pstParams->data[0]==PE_INF_HW_M23_GINFO__KDRV_INFO)
		{
			win_set = (PE_WIN_HW_M23_SETTINGS_T *)OS_Malloc(sizeof(PE_WIN_HW_M23_SETTINGS_T));
			PE_INF_M23_CHECK_CODE(!win_set, break, "win_set is null.\n");
			/* get win settings */
			ret = PE_WIN_HW_M23_GetCurWinSettings(win_set);
			PE_INF_M23_CHECK_CODE(ret,break,"PE_WIN_HW_M23_GetCurWinSettings() error.\n");
			switch(rd_cnt)
			{
				PE_INF_M23_CASE_SPRINT( 0,rd_cnt++,buffer,PE_INF_M23_PRINT_START);
				PE_INF_M23_CASE_SPRINT( 1,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_INF_M23_CASE_SPRINT( 2,rd_cnt++,buffer,\
					"src       : 0~6:dtv,atv,cvbs,scart,comp,rgbpc,hdmi\n");
				PE_INF_M23_CASE_SPRINT( 3,rd_cnt++,buffer,\
					"fmt/fr    : 0~2:sd,hd,uhd / 0~1:60hz,50hz\n");
				PE_INF_M23_CASE_SPRINT( 4,rd_cnt++,buffer,\
					"scan/cstd : 0~1:i,p / 0~2:ntsc,pal,secam\n");
				PE_INF_M23_CASE_SPRINT( 5,rd_cnt++,buffer,\
					"hdmi/scart: 0~1:tv,pc / 0~1:av,rgb\n");
				PE_INF_M23_CASE_SPRINT( 6,rd_cnt++,buffer,\
					"dtv       : 0:normal,1:file,2:hdd,3:photo,4:tp,5:camera,6:invalid\n");
				PE_INF_M23_CASE_SPRINT( 7,rd_cnt++,buffer,\
					"hdd       : 0:dtv,1:atv60,2:atv50,3:av60,4:av50,5:scartrgb,6:invalid\n");
				PE_INF_M23_CASE_SPRINT( 8,rd_cnt++,buffer,\
					"out       : 0~3:2d,3_2d,2_3d,ud, 4~6:tb,ss,fs, 7~9:dual_t,s,f, 10:pip\n");
				PE_INF_M23_CASE_SPRINT( 9,rd_cnt++,buffer,\
					"in        : 0tb,ss,q,cb,fp,5fi,fa,fs,la,9ssf,dua,ca,lah\n");
				PE_INF_M23_CASE_SPRINT(10,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_INF_M23_CASE_SPRINT(11,rd_cnt++,buffer,\
					"[%02d]disp0: wid:%d,src:%d,fmt:%d (h:%d,v:%d)\n",rd_cnt,\
					disp0_inf->win_id,disp0_inf->src_type,disp0_inf->fmt_type,\
					disp0_inf->in_h_size,disp0_inf->in_v_size);
				PE_INF_M23_CASE_SPRINT(12,rd_cnt++,buffer,\
					"[%02d]disp0: fr:%d(%d),scan:%d,cstd:%d,hdmi:%d,scart:%d,dtv:%d,hdd:%d\n",rd_cnt,\
					disp0_inf->fr_type,disp0_inf->in_f_rate,disp0_inf->scan_type,disp0_inf->cstd_type,\
					disp0_inf->hdmi_type,disp0_inf->scart_type,disp0_inf->dtv_type,disp0_inf->hdd_type);
				PE_INF_M23_CASE_SPRINT(13,rd_cnt++,buffer,\
					"[%02d]disp0:empty\n",rd_cnt);
				PE_INF_M23_CASE_SPRINT(14,rd_cnt++,buffer,\
					"[%02d]disp0: in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d\n",rd_cnt,\
					disp0_inf->in_win.x_ofst,disp0_inf->in_win.y_ofst,disp0_inf->in_win.h_size,\
					disp0_inf->in_win.v_size,disp0_inf->out_win.x_ofst,disp0_inf->out_win.y_ofst,\
					disp0_inf->out_win.h_size,disp0_inf->out_win.v_size,disp0_inf->act_fmt);
				PE_INF_M23_CASE_SPRINT(15,rd_cnt++,buffer,\
					"[%02d]disp0: rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n",rd_cnt, \
					disp0_inf->mode.is_reverse, disp0_inf->mode.is_oled,\
					disp0_inf->mode.is_colmetry, disp0_inf->mode.is_vr, disp0_inf->mode.is_420,disp0_inf->mode.is_orbit,disp0_inf->mode.is_dsc);
				PE_INF_M23_CASE_SPRINT(16,rd_cnt++,buffer,\
					"[%02d]disp1: wid:%d,src:%d,fmt:%d (h:%d,v:%d)\n",rd_cnt,\
					disp1_inf->win_id,disp1_inf->src_type,disp1_inf->fmt_type,\
					disp1_inf->in_h_size,disp1_inf->in_v_size);
				PE_INF_M23_CASE_SPRINT(17,rd_cnt++,buffer,\
					"[%02d]disp1: fr:%d(%d),scan:%d,cstd:%d,hdmi:%d,scart:%d,dtv:%d,hdd:%d\n",rd_cnt,\
					disp1_inf->fr_type,disp1_inf->in_f_rate,disp1_inf->scan_type,disp1_inf->cstd_type,\
					disp1_inf->hdmi_type,disp1_inf->scart_type,disp1_inf->dtv_type,disp1_inf->hdd_type);
				PE_INF_M23_CASE_SPRINT(18,rd_cnt++,buffer,\
					"[%02d]disp1:empty\n",rd_cnt);
				PE_INF_M23_CASE_SPRINT(19,rd_cnt++,buffer,\
					"[%02d]disp1: in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d\n",rd_cnt,\
					disp1_inf->in_win.x_ofst,disp1_inf->in_win.y_ofst,disp1_inf->in_win.h_size,\
					disp1_inf->in_win.v_size,disp1_inf->out_win.x_ofst,disp1_inf->out_win.y_ofst,\
					disp1_inf->out_win.h_size,disp1_inf->out_win.v_size,disp1_inf->act_fmt);
				PE_INF_M23_CASE_SPRINT(20,rd_cnt++,buffer,\
					"[%02d]disp1: rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n", rd_cnt,\
					disp1_inf->mode.is_reverse, disp1_inf->mode.is_oled,\
					disp1_inf->mode.is_colmetry,disp1_inf->mode.is_vr, disp1_inf->mode.is_420, disp1_inf->mode.is_orbit,disp1_inf->mode.is_dsc);
				PE_INF_M23_CASE_SPRINT(21,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_INF_M23_CASE_SPRINT(22,rd_cnt++,buffer,\
					"det_3df: 0:2d,1:cb,2,cc,3:ll,4:ss,5:tb,6:unknown,7:max\n");
				PE_INF_M23_CASE_SPRINT(23,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_INF_M23_CASE_SPRINT(24,rd_cnt++,buffer,"[%02d]ctrl0:\n",rd_cnt);
				PE_INF_M23_CASE_SPRINT(25,rd_cnt++,buffer,\
					"[%02d]pe0_src_h,v:%d,%d, i_sc:%d\n",rd_cnt,\
					ctrl0_inf->pe0_src_h,ctrl0_inf->pe0_src_v,ctrl0_inf->i_sc_type);
				PE_INF_M23_CASE_SPRINT(26,rd_cnt++,buffer,\
					"[%02d]u_win i:%d,%d,%d,%d, o:%d,%d,%d,%d\n",rd_cnt,\
					ctrl0_inf->u_i_win_h_ofst,ctrl0_inf->u_i_win_v_ofst,\
					ctrl0_inf->u_i_win_h_size,ctrl0_inf->u_i_win_v_size,\
					ctrl0_inf->u_o_win_h_ofst,ctrl0_inf->u_o_win_v_ofst,\
					ctrl0_inf->u_o_win_h_size,ctrl0_inf->u_o_win_v_size);
				PE_INF_M23_CASE_SPRINT(27,rd_cnt++,buffer,\
					"[%02d]c_fmt:%d,s_state:%d,mute_on:%d,hv_same:%d\n",rd_cnt,\
					ctrl0_inf->i_c_format,\
					ctrl0_inf->sat_status,ctrl0_inf->mute_on,ctrl0_inf->hv_same);
				PE_INF_M23_CASE_SPRINT(28,rd_cnt++,buffer,\
					"[%02d]pxl_rp,s_frz,f_s,vcp_mute_on,is_ndskip,panel_resolution:%d,%d,%d,%d,%d,%d\n",rd_cnt,\
					ctrl0_inf->pxl_rp_st,ctrl0_inf->is_src_frz,\
					ctrl0_inf->fw_src,ctrl0_inf->vcp_mute_on,ctrl0_inf->is_ndskip,ctrl0_inf->panel_resolution);
				PE_INF_M23_CASE_SPRINT(29,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(30,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(31,rd_cnt++,buffer,"[%02d]ctrl1:\n",rd_cnt);
				PE_INF_M23_CASE_SPRINT(32,rd_cnt++,buffer,\
					"[%02d]pe0_src_h,v:%d,%d, i_sc:%d\n",rd_cnt,\
					ctrl1_inf->pe0_src_h,ctrl1_inf->pe0_src_v,ctrl1_inf->i_sc_type);
				PE_INF_M23_CASE_SPRINT(33,rd_cnt++,buffer,\
					"[%02d]u_win i:%d,%d,%d,%d, o:%d,%d,%d,%d\n",rd_cnt,\
					ctrl1_inf->u_i_win_h_ofst,ctrl1_inf->u_i_win_v_ofst,\
					ctrl1_inf->u_i_win_h_size,ctrl1_inf->u_i_win_v_size,\
					ctrl1_inf->u_o_win_h_ofst,ctrl1_inf->u_o_win_v_ofst,\
					ctrl1_inf->u_o_win_h_size,ctrl1_inf->u_o_win_v_size);
				PE_INF_M23_CASE_SPRINT(34,rd_cnt++,buffer,\
					"[%02d]c_fmt:%d,s_state:%d,mute_on:%d,hv_same:%d\n",rd_cnt,\
					ctrl1_inf->i_c_format,\
					ctrl1_inf->sat_status,ctrl1_inf->mute_on,ctrl1_inf->hv_same);
				PE_INF_M23_CASE_SPRINT(35,rd_cnt++,buffer,\
					"[%02d]pxl_rp,s_frz,f_s,vcp_mute_on,is_ndskip,panel_resolution:%d,%d,%d,%d,%d,%d\n",rd_cnt,\
					ctrl1_inf->pxl_rp_st,ctrl1_inf->is_src_frz,\
					ctrl1_inf->fw_src,ctrl1_inf->vcp_mute_on,ctrl1_inf->is_ndskip,ctrl1_inf->panel_resolution);
				PE_INF_M23_CASE_SPRINT(36,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(37,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(38,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(39,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(40,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(41,rd_cnt++,buffer,"[%02d]win:\n",rd_cnt);
				PE_INF_M23_CASE_SPRINT(42,rd_cnt++,buffer,\
					"[%02d]act0:%d,%d,%d,%d, act1:%d,%d,%d,%d\n",rd_cnt,\
					win_set->win_inf.act0_x0,win_set->win_inf.act0_y0,win_set->win_inf.act0_x1,\
					win_set->win_inf.act0_y1,win_set->win_inf.act1_x0,win_set->win_inf.act1_y0,\
					win_set->win_inf.act1_x1,win_set->win_inf.act1_y1);
				PE_INF_M23_CASE_SPRINT(43,rd_cnt++,buffer,\
					"[%02d]win0:%d,%d,%d,%d, win1:%d,%d,%d,%d\n",rd_cnt,\
					win_set->win_inf.win0_x0,win_set->win_inf.win0_y0,win_set->win_inf.win0_x1,\
					win_set->win_inf.win0_y1,win_set->win_inf.win1_x0,win_set->win_inf.win1_y0,\
					win_set->win_inf.win1_x1,win_set->win_inf.win1_y1);
				PE_INF_M23_CASE_SPRINT(44,rd_cnt++,buffer,\
					"[%02d]h,v_max:%d,%d, w0,w1,w01_en:[%d,%d],[%d,%d],[%d,%d]\n",rd_cnt,\
					win_set->win_inf.h_max,win_set->win_inf.v_max,win_set->win_inf.win0_en[0],\
					win_set->win_inf.win0_en[1],win_set->win_inf.win1_en[0],win_set->win_inf.win1_en[1],\
					win_set->win_inf.win01_en[0],win_set->win_inf.win01_en[1]);
				PE_INF_M23_CASE_SPRINT(45,rd_cnt++,buffer,\
					"[%02d]lrcr histo_l,r, apply_r : %d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d\n",rd_cnt,\
					win_set->lrcr_inf.histo_l_x0,win_set->lrcr_inf.histo_l_y0,win_set->lrcr_inf.histo_l_x1,\
					win_set->lrcr_inf.histo_l_y1,win_set->lrcr_inf.histo_r_x0,win_set->lrcr_inf.histo_r_y0,\
					win_set->lrcr_inf.histo_r_x1,win_set->lrcr_inf.histo_r_y1,win_set->lrcr_inf.apply_r_x0,\
					win_set->lrcr_inf.apply_r_y0,win_set->lrcr_inf.apply_r_x1,win_set->lrcr_inf.apply_r_y1);
				PE_INF_M23_CASE_SPRINT(46,rd_cnt++,buffer,\
					"[%02d]win: tnr win h,v size0:%d,%d, size1:%d,%d\n",rd_cnt,\
					win_set->tnr_inf.h_size0,win_set->tnr_inf.v_size0,\
					win_set->tnr_inf.h_size1,win_set->tnr_inf.v_size1);
				PE_INF_M23_CASE_SPRINT(47,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(48,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(49,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(50,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(51,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(52,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(53,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(54,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(55,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(56,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(57,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(58,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(59,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(60,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(61,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(62,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(63,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(64,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(65,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(66,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_INF_M23_CASE_SPRINT(67,rd_cnt++,buffer,\
					"[%02d]db mode : shp:%d,hst:%d,scl:%d,tnr:%d,dnr:%d\n",rd_cnt,\
					PE_CMN_HW_M23_GetDbInfo(PE_CMN_HW_M23_DB_INF_MD0_SHP_FW_EN, 0), \
					PE_CMN_HW_M23_GetDbInfo(PE_CMN_HW_M23_DB_INF_MD0_HST_FW_EN, 0), \
					PE_CMN_HW_M23_GetDbInfo(PE_CMN_HW_M23_DB_INF_MD0_SCL_FW_EN, 0), \
					PE_CMN_HW_M23_GetDbInfo(PE_CMN_HW_M23_DB_INF_MD0_TNR_FW_EN, 0), \
					PE_CMN_HW_M23_GetDbInfo(PE_CMN_HW_M23_DB_INF_MD0_DNR_FW_EN, 0));
				PE_INF_M23_CASE_SPRINT(68,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(69,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(70,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(71,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_INF_M23_CASE_SPRINT(72,rd_cnt++,buffer,\
					"- kdrv ver. : %s\n", PE_INF_M23_DRV_VER);
				PE_INF_M23_CASE_SPRINT(73,rd_cnt++,buffer,\
					"---------------------------------------------------------------------------\n");
				PE_INF_M23_DFLT_SPRINT(rd_cnt=0,buffer,PE_INF_M23_PRINT_END);
			}
		}
		else if (pstParams->data[0]==PE_INF_HW_M23_GINFO_DDR_H_PHYS || \
			pstParams->data[0]==PE_INF_HW_M23_GINFO_DDR_H_SHDW)
		{
			PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
			UINT32 *p_s_base = NULL;
			UINT32 *p_s_size = NULL;
			UINT32 sec_typ;
			PE_DDR_M23_HEADER_T *p_sec_h = NULL;
			if (rd_cnt==0)
			{
				ddr_total = 0;
				p_sec_data = (PE_DDR_M23_DATA_T *)OS_Malloc(sizeof(PE_DDR_M23_DATA_T)*PE_DDR_M23_SEC_MAX_SIZE);
				CHECK_KNULL(p_sec_data);
				p_h_top = (PE_DDR_M23_TOP_HEADER_T *)OS_Malloc(sizeof(PE_DDR_M23_TOP_HEADER_T));
				CHECK_KNULL(p_h_top);
				if (pstParams->data[0]==PE_INF_HW_M23_GINFO_DDR_H_PHYS)
				{
					PE_INF_M23_GetCurDdrTopHeader((void *)p_h_top);
					for (sec_typ=0; sec_typ<PE_DDR_M23_SEC_NUM; sec_typ++)
					{
						p_sec_h = &(p_sec_data[sec_typ].header);
						PE_INF_M23_GetCurDdrSecHeader((void *)p_h_top, (void *)p_sec_h, sec_typ);
					}
				}
				else
				{
					memcpy(p_h_top, &(p_shdw_db->top_h), sizeof(PE_DDR_M23_TOP_HEADER_T));
					for (sec_typ=0; sec_typ<PE_DDR_M23_SEC_NUM; sec_typ++)
					{
						p_sec_data[sec_typ].header = p_shdw_db->sec_d[sec_typ].header;
					}
				}
				for (sec_typ=0; sec_typ<PE_DDR_M23_SEC_NUM; sec_typ++)
				{
					p_sec_data[sec_typ].data_base = p_shdw_db->sec_d[sec_typ].data_base;
					ddr_total += p_h_top->sec_size[sec_typ];
				}
			}
			p_s_base = p_h_top->sec_base;
			p_s_size = p_h_top->sec_size;
			/* causion : p_s_base and p_s_size should sync with PE_DDR_M23_SEC_MAX_SIZE */
			switch(rd_cnt)
			{
				PE_INF_M23_CASE_SPRINT( 0,rd_cnt++,buffer,PE_INF_M23_PRINT_START);
				PE_INF_M23_CASE_SPRINT( 1,rd_cnt++,buffer,\
					"--------------------------------------------------------------------------------\n");
				PE_INF_M23_CASE_SPRINT( 2,rd_cnt++,buffer,\
					"[%02d]top_h     : ver:%08x b_a:%08x s_n:%08x total_size:%d\n", rd_cnt, \
					p_h_top->version, p_h_top->db_base, p_h_top->sec_num, ddr_total);
				PE_INF_M23_CASE_SPRINT( 3,rd_cnt++,buffer, \
					"[%02d]top_h base: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
					p_s_base[0], p_s_base[1], p_s_base[2], p_s_base[3], p_s_base[4]);
				PE_INF_M23_CASE_SPRINT( 4,rd_cnt++,buffer, \
					"[%02d]top_h size: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
					p_s_size[0], p_s_size[1], p_s_size[2], p_s_size[3], p_s_size[4]);
				PE_INF_M23_CASE_SPRINT( 5,rd_cnt++,buffer, \
					"[%02d]top_h base: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
					p_s_base[5], p_s_base[6], p_s_base[7], p_s_base[8], p_s_base[9]);
				PE_INF_M23_CASE_SPRINT( 6,rd_cnt++,buffer, \
					"[%02d]top_h size: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
					p_s_size[5], p_s_size[6], p_s_size[7], p_s_size[8], p_s_size[9]);
				PE_INF_M23_CASE_SPRINT( 7,rd_cnt++,buffer, \
					"[%02d]top_h base: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
					p_s_base[10], p_s_base[11], p_s_base[12], p_s_base[13], p_s_base[14]);
				PE_INF_M23_CASE_SPRINT( 8,rd_cnt++,buffer, \
					"[%02d]top_h size: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
					p_s_size[10], p_s_size[11], p_s_size[12], p_s_size[13], p_s_size[14]);
				PE_INF_M23_CASE_SPRINT( 9,rd_cnt++,buffer, \
					"[%02d]top_h base: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
					p_s_base[15], p_s_base[16], p_s_base[17], p_s_base[18], p_s_base[19]);
				PE_INF_M23_CASE_SPRINT(10,rd_cnt++,buffer, \
					"[%02d]top_h size: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
					p_s_size[15], p_s_size[16], p_s_size[17], p_s_size[18], p_s_size[19]);
				PE_INF_M23_CASE_SPRINT(11,rd_cnt++,buffer, \
					"[%02d]top_h base: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
					p_s_base[20], p_s_base[21], p_s_base[22], p_s_base[23], p_s_base[24]);
				PE_INF_M23_CASE_SPRINT(12,rd_cnt++,buffer, \
					"[%02d]top_h size: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
					p_s_size[20], p_s_size[21], p_s_size[22], p_s_size[23], p_s_size[24]);
				PE_INF_M23_CASE_SPRINT(13,rd_cnt++,buffer, \
					"[%02d]top_h base: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
					p_s_base[25], p_s_base[26], p_s_base[27], p_s_base[28], p_s_base[29]);
				PE_INF_M23_CASE_SPRINT(14,rd_cnt++,buffer, \
					"[%02d]top_h size: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
					p_s_size[25], p_s_size[26], p_s_size[27], p_s_size[28], p_s_size[29]);
				PE_INF_M23_CASE_SPRINT(15,rd_cnt++,buffer, \
					"[%02d]top_h base: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
					p_s_base[30], p_s_base[31], p_s_base[32], p_s_base[33], p_s_base[34]);
				PE_INF_M23_CASE_SPRINT(16,rd_cnt++,buffer, \
					"[%02d]top_h size: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
					p_s_size[30], p_s_size[31], p_s_size[32], p_s_size[33], p_s_size[34]);
				PE_INF_M23_CASE_SPRINT(17,rd_cnt++,buffer, \
					"[%02d]top_h base: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
					p_s_base[35], p_s_base[36], p_s_base[37], p_s_base[38], p_s_base[39]);
				PE_INF_M23_CASE_SPRINT(18,rd_cnt++,buffer, \
					"[%02d]top_h size: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
					p_s_size[35], p_s_size[36], p_s_size[37], p_s_size[38], p_s_size[39]);
				PE_INF_M23_CASE_SPRINT(19,rd_cnt++,buffer, \
					"[%02d]top_h base: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
					p_s_base[40], p_s_base[41], p_s_base[42], p_s_base[43], p_s_base[44]);
				PE_INF_M23_CASE_SPRINT(20,rd_cnt++,buffer, \
					"[%02d]top_h size: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
					p_s_size[40], p_s_size[41], p_s_size[42], p_s_size[43], p_s_size[44]);
				PE_INF_M23_CASE_SPRINT(21,rd_cnt++,buffer, \
					"[%02d]top_h base: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
					p_s_base[45], p_s_base[46], p_s_base[47], p_s_base[48], p_s_base[49]);
				PE_INF_M23_CASE_SPRINT(22,rd_cnt++,buffer, \
					"[%02d]top_h size: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
					p_s_size[45], p_s_size[46], p_s_size[47], p_s_size[48], p_s_size[49]);
				PE_INF_M23_CASE_SPRINT(23,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(24,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(25,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(26,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(27,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(28,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(29,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(30,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(31,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(32,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(33,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(34,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(35,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(36,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(37,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(38,rd_cnt++,buffer,PE_INF_M23_PRINT_RESERVED);
				PE_INF_M23_CASE_SPRINT(39,rd_cnt++,buffer,\
					"--------------------------------------------------------------------------------\n");
				PE_INF_M23_CASE_SPRINT(40,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(41,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(42,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(43,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(44,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(45,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(46,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(47,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(48,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(49,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(50,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(51,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(52,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(53,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(54,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(55,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(56,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(57,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(58,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(59,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(60,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(61,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(62,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(63,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(64,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(65,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(66,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(67,rd_cnt++,buffer, \
					"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
					PE_DDR_REG_M23_SEC_TYPE_TO_STR(rd_cnt-40), \
					p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
					p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
					p_sec_data[rd_cnt-40].data_base);
				PE_INF_M23_CASE_SPRINT(68,rd_cnt++,buffer,\
					"--------------------------------------------------------------------------------\n");
				PE_INF_M23_DFLT_SPRINT(rd_cnt=0,buffer,PE_INF_M23_PRINT_END);
			}
			if (rd_cnt==0)
			{
				if (p_h_top)	{OS_Free(p_h_top);}
				if (p_sec_data)	{OS_Free(p_sec_data);}
			}
		}
		else
		{
			snprintf(buffer, PE_TRACE_STR_SIZE, PE_INF_M23_PRINT_EXIT);
			rd_cnt=0;
		}
		memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
	}while(0);
	if (win_set)	{OS_Free(win_set);}
	return ret;
}

/**
 * set misc table
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_SetMiscTbl(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	UINT32 max_num = 0;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M23)
		{
			max_num = sizeof(_g_pe_inf_m23_dbg_set_fn)/sizeof(PE_ETC_MISC_TBL_T);
			PE_INF_M23_CHECK_CODE(pstParams->func_num>=max_num, break, \
				"invalid func_num[%d].\n", pstParams->func_num);
			CHECK_KNULL(_g_pe_inf_m23_dbg_set_fn[pstParams->func_num].func);
			ret = _g_pe_inf_m23_dbg_set_fn[pstParams->func_num].func(pstParams);
			PE_INF_M23_CHECK_CODE(ret, break, "%s() error.\n", \
				_g_pe_inf_m23_dbg_set_fn[pstParams->func_num].fn_name);
		}
		else
		{
			PE_DBG_INF("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	return ret;
}
/**
 * get misc debug(for debug)
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_GetMiscTbl(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	UINT32 max_num = 0;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M23)
		{
			max_num = sizeof(_g_pe_inf_m23_dbg_get_fn)/sizeof(PE_ETC_MISC_TBL_T);
			PE_INF_M23_CHECK_CODE(pstParams->func_num>=max_num, break, \
				"invalid func_num[%d].\n", pstParams->func_num);
			CHECK_KNULL(_g_pe_inf_m23_dbg_get_fn[pstParams->func_num].func);
			ret = _g_pe_inf_m23_dbg_get_fn[pstParams->func_num].func(pstParams);
			PE_INF_M23_CHECK_CODE(ret, break, "%s() error.\n", \
				_g_pe_inf_m23_dbg_get_fn[pstParams->func_num].fn_name);
		}
		else
		{
			PE_DBG_INF("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	return ret;
}
/**
 * sort trace data buf to dst buf
 * - ascending, bubble sorting
 *
 * @param   type [in] UINT32
 * @param   *dst [in/out] PE_INF_M23_DATA_BUF_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
static int PE_INF_M23_SortTraceDataBuf(UINT32 type, PE_INF_M23_DATA_BUF_T *dst)
{
	int ret = RET_OK;
	UINT32 size=0, i=0, max=0;
	UINT32 j=0, s0=0, s1=0, us0=0, us1=0;
	PE_INF_M23_DATA_BUF_T temp;
	PE_INF_M23_DATA_BUF_T *src;

	do{
		CHECK_KNULL(dst);
		if (type == 1)		src = _g_pe_inf_m23_db_buf;
		else				src = _g_pe_inf_m23_buf;
		if (src == NULL)	{ret = RET_ERROR;	break;}
		max = PE_INF_M23_BUF_MAX;
		size = sizeof(PE_INF_M23_DATA_BUF_T);
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
/**
 * get trace data buf
 *
 * @param   *data [in] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
static int PE_INF_M23_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0, type=0;
	PE_INF_M23_DATA_BUF_T *p_buf;
	UINT32 *p_data = NULL;
	PE_INF_M23_TIME_T *p_time = NULL;
	char *p_str = NULL;

#define PE_INF_M23_PRINT_RESERVED	"RESERVED"
#define PE_INF_M23_PRINT_END		"END_OF_PRINT"

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		type = pstParams->data[0];
		if (type == 1)		p_buf = _g_pe_inf_m23_db_buf_temp;
		else				p_buf = _g_pe_inf_m23_buf_temp;
		if (p_buf == NULL)	break;
		rd_cnt = pstParams->oper;
		if (rd_cnt<PE_INF_M23_BUF_MAX)
		{
			if(rd_cnt==0)
			{
				ret = PE_INF_M23_SortTraceDataBuf(type,p_buf);
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
				snprintf(buffer,PE_TRACE_STR_SIZE, "%s", PE_INF_M23_PRINT_RESERVED);
			}
			rd_cnt++;
		}
		else
		{
			snprintf(buffer, PE_TRACE_STR_SIZE,"%s", PE_INF_M23_PRINT_END);
			rd_cnt=0;
		}
		p_data = pstParams->data;
		memcpy(p_data, buffer, PE_TRACE_STR_SIZE);
	}while (0);
	return ret;
}

/**
 * set trace data buf
 * type: 0:normal,1:db
 *
 * @param   type [in] UINT32
 * @param   *data [in] char
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_INF_M23_SetTraceDataBuf(UINT32 type, char *data)
{
    int ret = RET_OK;
	UINT32 i = 0;
	char *p_str = NULL;
	PE_INF_M23_TIME_T *p_time = NULL;
	static UINT32 cnt = 0;
	PE_INF_M23_DATA_BUF_T *p_buf;
	do{
		CHECK_KNULL(data);
		if (type == 1)		p_buf = _g_pe_inf_m23_db_buf;
		else				p_buf = _g_pe_inf_m23_buf;
		if (p_buf == NULL)	{ret = RET_ERROR;	break;}
		if(cnt>=PE_INF_M23_BUF_MAX)	cnt = 0;
		p_str = p_buf[cnt].str;
		p_time = &(p_buf[cnt].time);
		OS_GetCurrentTicks(&(p_time->sec),&(p_time->msec),&(p_time->usec));
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
 * get current ddr top header.
 *
 * @param   *pstParams [in/out] void, see PE_DDR_M23_TOP_HEADER_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_GetCurDdrTopHeader(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, base, size;
	volatile PE_DDR_M23_TOP_HEADER_T *p_top  = NULL;
	PE_DDR_M23_TOP_HEADER_T *p_dst  = NULL;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	do {
		CHECK_KNULL(pstParams);
		base = p_shdw_db->top_h.db_base;
		size = sizeof(PE_DDR_M23_TOP_HEADER_T);
		if (!base||!size)	break;
		p_top = (volatile PE_DDR_M23_TOP_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_top);
		p_dst = (PE_DDR_M23_TOP_HEADER_T *)pstParams;
		p_dst->version = p_top->version;
		p_dst->db_base = p_top->db_base;
		p_dst->sec_num = p_top->sec_num;
		for (i=0; i<PE_DDR_M23_SEC_MAX_SIZE; i++)
		{
			p_dst->sec_base[i] = p_top->sec_base[i];
			p_dst->sec_size[i] = p_top->sec_size[i];
		}
	}while(0);
	if (p_top) vunmap_phys((void *)p_top);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get current ddr section header.
 *
 * @param   *top_h [in] void, see PE_DDR_M23_TOP_HEADER_T
 * @param   *pstParams [in/out] void, see PE_DDR_M23_HEADER_T
 * @param   sec_type [in] UINT32, see PE_DDR_M23_SEC_TYPE
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_M23_GetCurDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 base, size;
	PE_DDR_M23_TOP_HEADER_T *p_top = NULL;
	PE_DDR_M23_HEADER_T *p_dst = NULL;
	volatile PE_DDR_M23_HEADER_T *p_sec  = NULL;
	do {
		CHECK_KNULL(top_h);
		CHECK_KNULL(pstParams);
		PE_INF_M23_CHECK_CODE(sec_type>=PE_DDR_M23_SEC_NUM,break,"sec_type(%d) is over.\n",sec_type);
		p_top = (PE_DDR_M23_TOP_HEADER_T *)top_h;
		base = p_top->sec_base[sec_type];
		size = sizeof(PE_DDR_M23_HEADER_T);
		if (!base || !size)	break;
		p_sec  = (volatile PE_DDR_M23_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_sec);
		p_dst = (PE_DDR_M23_HEADER_T *)pstParams;
		p_dst->version = p_sec->version;
		p_dst->sec_type = p_sec->sec_type;
		p_dst->item_num = p_sec->item_num;
		p_dst->item_size = p_sec->item_size;
	}while(0);
	if (p_sec) vunmap_phys((void *)p_sec);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

int PE_INF_M23_GetStatus(UINT32 *p_data, UINT32 count)
{
	if (!p_data)	return -1;
	if (count<3)	return -1;

	#ifdef PE_HW_M23_BRINGUP
	PE_ND0_M23_QRd02(tnr_status_01,w_apl_motion,p_data[0],w_apl_var,p_data[1]);
	PE_CC_PE1_M23_QRd01(pe1_fsw_ctrl_00,reg_s_status_0,p_data[2]);
	#endif

	return 0;
}

