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

/** @file pe_inf_o22.c
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

#include "pe_hw_o22.h"
#include "pe_reg_o22.h"
#include "pe_inf_o22.h"
#include "pe_fwi_o22.h"
#include "pe_win_hw_o22.h"
#include "pe_shp_hw_o22.h"
#include "pe_ccm_hw_o22.h"
#include "pe_hst_hw_o22.h"
#include "pe_cmn_hw_o22.h"
#include "pe_dnt_hw_o22.h"
#include "pe_nrd_hw_o22.h"
#include "pe_csc_hw_o22.h"
#include "pe_hdr_hw_o22.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* drv ver, yyyy/mm/dd/hh:mm */
#define PE_INF_O22_DRV_VER		"2020/10/12/19:60"

#define PE_INF_O22_BUF_MAX				50

#define PE_INF_O22_SCL_RESIZE_H_MAX		1920	/* 3840 * 0.5 */
#define PE_INF_O22_SCL_RESIZE_V_MAX		1080	/* 2160 * 0.5 */

#define PE_INF_O22_INC_CHPI_CNT_MAX		0xff

/* define for showing more detail trace log */
#undef PE_INF_O22_DETAIL_TRACE_LOG

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_INF_O22_ERROR	printk

#define PE_INF_O22_DBG_PRINT(fmt,args...)	\
	if(_g_pe_inf_o22_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_INF_O22_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_INF_O22_ERROR(fmt,##args);_action;}}

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
PE_INF_O22_TIME_T;

/**
 *	pe trace data buffer type
 */
typedef struct {
	PE_INF_O22_TIME_T time;			///< time
	char str[PE_TRACE_STR_SIZE];	///< str
}
PE_INF_O22_DATA_BUF_T;

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
UINT32 g_pe_inf_o22_vr360_mode = 0x0;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_INF_O22_GetGeneralPicInfo(LX_PE_ETC_TBL_T *pstParams);
static int PE_INF_O22_SetPathMonitor(LX_PE_ETC_TBL_T *pstParams);
static int PE_INF_O22_GetPathMonitor(LX_PE_ETC_TBL_T *pstParams);
static int PE_INF_O22_SortTraceDataBuf(UINT32 type, PE_INF_O22_DATA_BUF_T *dst);
static int PE_INF_O22_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams);
static int PE_INF_O22_SetPixelRead(LX_PE_ETC_TBL_T *pstParams);
static int PE_INF_O22_GetPixelRead(LX_PE_ETC_TBL_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_INF_O22_DATA_BUF_T _g_pe_inf_o22_buf[PE_INF_O22_BUF_MAX];
static PE_INF_O22_DATA_BUF_T _g_pe_inf_o22_buf_temp[PE_INF_O22_BUF_MAX];
static PE_INF_O22_DATA_BUF_T _g_pe_inf_o22_db_buf[PE_INF_O22_BUF_MAX];
static PE_INF_O22_DATA_BUF_T _g_pe_inf_o22_db_buf_temp[PE_INF_O22_BUF_MAX];
static PE_INF_O22_DATA_BUF_T _g_pe_inf_o22_chpi0_buf[PE_INF_O22_BUF_MAX];
static PE_INF_O22_DATA_BUF_T _g_pe_inf_o22_chpi0_buf_temp[PE_INF_O22_BUF_MAX];
static PE_INF_O22_DATA_BUF_T _g_pe_inf_o22_chpi1_buf[PE_INF_O22_BUF_MAX];
static PE_INF_O22_DATA_BUF_T _g_pe_inf_o22_chpi1_buf_temp[PE_INF_O22_BUF_MAX];

static UINT32 _g_pe_inf_o22_trace=0x0;		//default should be off.
static PE_INF_O22_SETTINGS_T _g_pe_inf_hw_o22_info;

/* see PE_INF_O22_CHPI_APB *//* O22F22_APB */
__attribute__((unused)) static UINT32 _g_pe_inf_o22_chpi_block = PE_INF_O22_CHPI_APB_H_LUT;

/* see PE_INF_O22_CHPI_TBL *//* O22F22_TBL */
__attribute__((unused)) static UINT32 _g_pe_inf_o22_chpi_count = PE_INF_O22_CHPI_TBL_NONE;

static PE_ETC_MISC_TBL_T _g_pe_inf_o22_dbg_set_fn[] = {\
	{/* 00 */ PE_TSK_O22_SetTaskOperation,		"PE_TSK_O22_SetTaskOperation"}, \
	{/* 01 */ PE_REG_O22_WrReg,				"PE_REG_O22_WrReg"}, \
	{/* 02 */ PE_INF_O22_SetPathMonitor,		"PE_INF_O22_SetPathMonitor"}, \
	{/* 03 */ PE_INF_O22_SetPixelRead,			"PE_INF_O22_SetPixelRead"}, \
	{/* 04 */ PE_CMN_O22_DownloadDbBin,		"PE_CMN_O22_DownloadDbBin"}
};
static PE_ETC_MISC_TBL_T _g_pe_inf_o22_dbg_get_fn[] = {\
	{/* 00 */ PE_TSK_O22_GetTaskOperation,		"PE_TSK_O22_GetTaskOperation"}, \
	{/* 01 */ PE_REG_O22_RdReg,				"PE_REG_O22_RdReg"}, \
	{/* 02 */ PE_INF_O22_GetGeneralPicInfo,	"PE_INF_O22_GetGeneralPicInfo"}, \
	{/* 03 */ PE_HST_HW_O22_GetGlobalHistInfo,	"PE_HST_HW_O22_GetGlobalHistInfo"}, \
	{/* 04 */ PE_INF_O22_GetPathMonitor,		"PE_INF_O22_GetPathMonitor"}, \
	{/* 05 */ PE_INF_O22_GetPathMonitor,		"PE_INF_O22_GetPathMonitor--same as 04"}, \
	{/* 06 */ PE_DNT_HW_O22_RdDefault,			"PE_DNT_HW_O22_RdDefault"}, \
	{/* 07 */ PE_NRD_HW_O22_RdDefault,			"PE_NRD_HW_O22_RdDefault"}, \
	{/* 08 */ PE_SHP_HW_O22_RdDefault,			"PE_SHP_HW_O22_RdDefault"}, \
	{/* 09 */ PE_INF_O22_GetTraceDataBuf,		"PE_INF_O22_GetTraceDataBuf"}, \
	{/* 10 */ PE_INF_O22_GetPixelRead,			"PE_INF_O22_GetPixelRead"}, \
	{/* 11 */ PE_HDR_HW_O22_GetGeneralInfo,		"PE_HDR_HW_O22_GetGeneralInfo"}, \
	{/* 12 */ PE_CMN_O22_GetDownloadInfo,		"PE_CMN_O22_GetDownloadInfo"}, \
	{/* 13 */ PE_HDR_HW_O22_GetTraceDataBuf,	"PE_HDR_HW_O22_GetTraceDataBuf"}
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
int PE_INF_O22_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	PE_REG_O22_HW_OPT_T hw_opt;
	UINT32 is_oled;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O22)
		{
			PE_PRINT_NOTI("init info values.\n");
			memset0(_g_pe_inf_hw_o22_info);
			hw_opt = PE_REG_O22_GetDispOpt();
			is_oled = (hw_opt.panel_type == 0x1)?0x1:0x0;
			_g_pe_inf_hw_o22_info.disp_info[0].mode.is_oled = is_oled;
			_g_pe_inf_hw_o22_info.disp_info[1].mode.is_oled = is_oled;
			_g_pe_inf_hw_o22_info.ctrl_info[0].panel_resolution = hw_opt.panel_resolution;
			_g_pe_inf_hw_o22_info.ctrl_info[1].panel_resolution = hw_opt.panel_resolution;
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_INF_O22_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(ETC)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_pe_inf_o22_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(ETC)))? 0x1:0x0;
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_SetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 colorimetry;
	PE_FWI_O22_SRC_INFO fwi_src;
	LX_PE_INF_DISPLAY_T *pp = NULL;
#ifdef PE_EXTEND_WINID
	UINT32 i;
	LX_PE_INF_DISPLAY_T *p_inf = _g_pe_inf_hw_o22_info.disp_info;
#else
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_1];
#endif
	do{
		static LX_PE_INF_DISPLAY_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		pp = (LX_PE_INF_DISPLAY_T *)pstParams;
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_INF_DISPLAY_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_INF_O22_DBG_PRINT("duplicated DB : LX_PE_INF_DISPLAY_T\n");
			ret=RET_OK;
			break;
		}
		PE_INF_O22_DBG_PRINT("set[%d] : info type:%d src:%d,res:%d (h:%d,v:%d)\n"\
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
		if(PE_KDRV_VER_O22)
		{
		#ifdef PE_EXTEND_WINID
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
		#else
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(disp0_info,pstParams,sizeof(LX_PE_INF_DISPLAY_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(disp1_info,pstParams,sizeof(LX_PE_INF_DISPLAY_T));
			}
			/* sync parameters with no relationship to window */
			disp0_info->hdd_type	= disp1_info->hdd_type		= pstParams->hdd_type;
			disp0_info->act_fmt 	= disp1_info->act_fmt		= pstParams->act_fmt;
			disp0_info->mul_win 	= disp1_info->mul_win		= pstParams->mul_win;
			disp0_info->mode		= disp1_info->mode			= pstParams->mode;
			/* sync parameters when all win case(ud,3d) */
			if(pstParams->win_id==LX_PE_WIN_ALL)
			{
				disp0_info->src_type	= disp1_info->src_type	= pstParams->src_type;
				disp0_info->fmt_type	= disp1_info->fmt_type	= pstParams->fmt_type;
				disp0_info->fr_type 	= disp1_info->fr_type	= pstParams->fr_type;
				disp0_info->scan_type	= disp1_info->scan_type = pstParams->scan_type;
				disp0_info->dtv_type	= disp1_info->dtv_type	= pstParams->dtv_type;
				disp0_info->cstd_type	= disp1_info->cstd_type = pstParams->cstd_type;
				disp0_info->hdmi_type	= disp1_info->hdmi_type = pstParams->hdmi_type;
				disp0_info->scart_type	= disp1_info->scart_type= pstParams->scart_type;
			}
		#endif
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* src info */
				if(pstParams->info_type == LX_PE_INFO_DEFAULT)
				{
					fwi_src.dtv_mode = pstParams->dtv_type;
					fwi_src.hdd_mode = pstParams->hdd_type;
					ret = PE_FWI_O22_SetSrcInfo(&fwi_src);
					PE_INF_O22_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_O22_SetSrcInfo() error.\n",__F__,__L__);
				}
			}

			/* colorimetry */
			if(pstParams->info_type == LX_PE_INFO_MODE)
			{
				colorimetry = pstParams->mode.is_colmetry;
				ret = PE_FWI_O22_SetColorimetry(pstParams->win_id,&colorimetry);
				PE_INF_O22_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_O22_SetColorimetry() error.\n",__F__,__L__);
			}
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_GetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	LX_PE_WIN_ID win_id,temp;
	#ifdef PE_EXTEND_WINID
	UINT32 i;
	LX_PE_INF_DISPLAY_T *p_inf = _g_pe_inf_hw_o22_info.disp_info;
	#else
	PE_INF_O22_SETTINGS_T *pInfo=&_g_pe_inf_hw_o22_info;
	#endif
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O22)
		{
			#ifdef PE_EXTEND_WINID
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				if (win_id==i)
				{
					temp = pstParams->win_id;
					memcpy(pstParams,&p_inf[i],sizeof(LX_PE_INF_DISPLAY_T));
					pstParams->win_id = temp;
				}
			}
			#else
			if(PE_CHECK_WIN0(win_id))
			{
				temp = pstParams->win_id;
				memcpy(pstParams,&pInfo->disp_info[LX_PE_WIN_0],sizeof(LX_PE_INF_DISPLAY_T));
				pstParams->win_id = temp;
			}
			if(PE_CHECK_WIN1(win_id))
			{
				temp = pstParams->win_id;
				memcpy(pstParams,&pInfo->disp_info[LX_PE_WIN_1],sizeof(LX_PE_INF_DISPLAY_T));
				pstParams->win_id = temp;
			}
			#endif
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_GetCurDispInfSettings(UINT32 wid, LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O22)
		{
			if (wid == LX_PE_WIN_1)
			{
				memcpy(pstParams,disp1_info,sizeof(LX_PE_INF_DISPLAY_T));
			}
			else
			{
				memcpy(pstParams,disp0_info,sizeof(LX_PE_INF_DISPLAY_T));
			}
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * get current ctrl info.
 *
 * @param   wid [in] UINT32
 * @param   *pstParams [in/out] PE_INF_O22_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_GetCurCtrlInfSettings(UINT32 wid, PE_INF_O22_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	__attribute__((unused)) PE_INF_O22_CTRL_T *ctrl0_info = &_g_pe_inf_hw_o22_info.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O22_CTRL_T *ctrl1_info = &_g_pe_inf_hw_o22_info.ctrl_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O22)
		{
			if (wid == LX_PE_WIN_1)
			{
				memcpy(pstParams,ctrl1_info,sizeof(PE_INF_O22_CTRL_T));
			}
			else
			{
				memcpy(pstParams,ctrl0_info,sizeof(PE_INF_O22_CTRL_T));
			}
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_GetCurModeInfSettings(UINT32 wid, LX_PE_INF_OP_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O22)
		{
			*pstParams = (wid == LX_PE_WIN_1)? disp1_info->mode:disp0_info->mode;
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_CheckSclInfo(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 r_data;
	__attribute__((unused)) PE_INF_O22_CTRL_T *ctrl0_info = &_g_pe_inf_hw_o22_info.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O22_CTRL_T *ctrl1_info = &_g_pe_inf_hw_o22_info.ctrl_info[LX_PE_WIN_1];
	LX_PE_INF_DISPLAY_T *disp0_info=&_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info=&_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_1];
	UINT32 h_max = PE_INF_O22_SCL_RESIZE_H_MAX;
	UINT32 v_max = PE_INF_O22_SCL_RESIZE_V_MAX;
	do{
		if(PE_KDRV_VER_O22)
		{
			/* L */
			ctrl0_info->u_i_win_h_ofst = disp0_info->in_win.x_ofst;
			ctrl0_info->u_i_win_v_ofst = disp0_info->in_win.y_ofst;
			ctrl0_info->u_i_win_h_size = disp0_info->in_win.h_size;
			ctrl0_info->u_i_win_v_size = disp0_info->in_win.v_size;
			ctrl0_info->u_o_win_h_ofst = disp0_info->out_win.x_ofst;
			ctrl0_info->u_o_win_v_ofst = disp0_info->out_win.y_ofst;
			ctrl0_info->u_o_win_h_size = disp0_info->out_win.h_size;
			ctrl0_info->u_o_win_v_size = disp0_info->out_win.v_size;
			PE_ND0_O22_RdFL(pe0_src_size);
			PE_ND0_O22_Rd01(pe0_src_size, cs_type, ctrl0_info->i_c_format);//0x6:444,0x5:422, else 420
			PE_ND0_O22_Rd01(pe0_src_size, hsize, ctrl0_info->pe0_src_h);
			PE_ND0_O22_Rd01(pe0_src_size, vsize, ctrl0_info->pe0_src_v);
			PE_ND0_O22_Rd01(pe0_src_size, scan_type, ctrl0_info->i_sc_type);//1:p, 0:i
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
			if(_g_pe_inf_hw_o22_info.ctrl_info[0].panel_resolution == 0)//UD
			{
				h_max = PE_INF_O22_SCL_RESIZE_H_MAX;
				v_max = PE_INF_O22_SCL_RESIZE_V_MAX;
			}
			else if(_g_pe_inf_hw_o22_info.ctrl_info[0].panel_resolution == 1)//FHD
			{
				h_max = PE_INF_O22_SCL_RESIZE_H_MAX>>1;
				v_max = PE_INF_O22_SCL_RESIZE_V_MAX>>1;
			}
			else if(_g_pe_inf_hw_o22_info.ctrl_info[0].panel_resolution == 2)//HD 1366x768
			{
				h_max = PE_INF_O22_SCL_RESIZE_H_MAX>>2;
				v_max = PE_INF_O22_SCL_RESIZE_V_MAX>>2;
			}
			ctrl0_info->hv_same = (ctrl0_info->u_o_win_h_size==ctrl1_info->u_o_win_h_size && \
				ctrl0_info->u_o_win_v_size==ctrl1_info->u_o_win_v_size)? 1:0;
			ctrl1_info->hv_same = (ctrl0_info->u_o_win_h_size<h_max && \
				ctrl0_info->u_o_win_v_size<v_max)? 1:0;
			ret = PE_HST_HW_O22_GetSaturationState(LX_PE_WIN_0,&r_data);
			if(ret)	{PE_INF_O22_ERROR("[%s,%d] PE_HST_HW_O22_GetSaturationState() error.\n",__F__,__L__);}
			ctrl0_info->sat_status = r_data;
			ret = PE_HST_HW_O22_GetSaturationState(LX_PE_WIN_1,&r_data);
			if(ret)	{PE_INF_O22_ERROR("[%s,%d] PE_HST_HW_O22_GetSaturationState() error.\n",__F__,__L__);}
			ctrl1_info->sat_status = r_data;
			PE_CC2_PE1_O22_QRd01(pe1_mute_ctrl_00, pxl_rep_in_0,	ctrl0_info->mute_on);
			PE_CC2_PE1_O22_QRd01(pe1_mute_ctrl_05, pxl_rep_in_0,	ctrl1_info->mute_on);
			PE_VCP_DISP_O22_QRd02(vcp_wcp_m_ctrl_5, set_w0_dark_en,	ctrl0_info->vcp_mute_on,\
														set_w1_dark_en,	ctrl1_info->vcp_mute_on);
			PE_CC_PE1_O22_QRd01(pe1_fsw_ctrl_00,	reg_color_filter_status,ctrl0_info->pxl_rp_st);
			ctrl1_info->pxl_rp_st = ctrl0_info->pxl_rp_st;
			PE_CC_PE1_O22_RdFL(pe1_fsw_ctrl_02);
			PE_CC_PE1_O22_Rd01(pe1_fsw_ctrl_02,	reg_src_freeze,	ctrl0_info->is_src_frz);
			PE_CC_PE1_O22_Rd01(pe1_fsw_ctrl_02,	reg_src_info,	ctrl0_info->fw_src);
			PE_CCO_VERI_O22_QRd01(video_delay_sts0, skip_nd0,	ctrl0_info->is_ndskip);
			ctrl1_info->is_src_frz = ctrl0_info->is_src_frz;
			ctrl1_info->fw_src = ctrl0_info->fw_src;
			ctrl1_info->is_ndskip = ctrl0_info->is_ndskip;
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * get current info.
 *
 * @param   *pstParams [in/out] PE_INF_O22_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_GetCurInfSettings(PE_INF_O22_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	static UINT32 count = 0;
	PE_INF_O22_SETTINGS_T *pInfo = &_g_pe_inf_hw_o22_info;
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_1];
	__attribute__((unused)) PE_INF_O22_CTRL_T *ctrl0_info = &_g_pe_inf_hw_o22_info.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O22_CTRL_T *ctrl1_info = &_g_pe_inf_hw_o22_info.ctrl_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O22)
		{
			memcpy(pstParams,pInfo,sizeof(PE_INF_O22_SETTINGS_T));
			if(_g_pe_inf_o22_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_INF_O22_DBG_PRINT("disp[0] : src:%d,fmt:%d (h:%d,v:%d)\n", \
						disp0_info->src_type, disp0_info->fmt_type, \
						disp0_info->in_h_size, disp0_info->in_v_size);
					PE_INF_O22_DBG_PRINT("disp[0] : fr:%d(%d),scan:%d,cstd,hdmi,scart,dtv,hdd:%d,%d,%d,%d,%d\n", \
						disp0_info->fr_type, disp0_info->in_f_rate, disp0_info->scan_type, \
						disp0_info->cstd_type, disp0_info->hdmi_type, disp0_info->scart_type, \
						disp0_info->dtv_type, disp0_info->hdd_type);
					PE_INF_O22_DBG_PRINT("disp[0] : in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d\n", \
						disp0_info->in_win.x_ofst, disp0_info->in_win.y_ofst, \
						disp0_info->in_win.h_size, disp0_info->in_win.v_size, \
						disp0_info->out_win.x_ofst, disp0_info->out_win.y_ofst, \
						disp0_info->out_win.h_size, disp0_info->out_win.v_size, disp0_info->act_fmt);
					PE_INF_O22_DBG_PRINT("disp[0] : rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n", \
						disp0_info->mode.is_reverse, disp0_info->mode.is_oled,\
						disp0_info->mode.is_colmetry, disp0_info->mode.is_vr, disp0_info->mode.is_420, disp0_info->mode.is_orbit,disp0_info->mode.is_dsc);
					PE_INF_O22_DBG_PRINT("ctrl[0] : src:%d,%d,sc:%d, u_w i:%d,%d,%d,%d, o:%d,%d,%d,%d\n",\
						ctrl0_info->pe0_src_h,ctrl0_info->pe0_src_v,ctrl0_info->i_sc_type,\
						ctrl0_info->u_i_win_h_ofst,ctrl0_info->u_i_win_v_ofst,\
						ctrl0_info->u_i_win_h_size,ctrl0_info->u_i_win_v_size,\
						ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,\
						ctrl0_info->u_o_win_h_size,ctrl0_info->u_o_win_v_size);
					PE_INF_O22_DBG_PRINT("ctrl[0] : c_fmt:%d,s_stat:%d,mute_on:%d,hv_same:%d\n",\
						ctrl0_info->i_c_format,\
						ctrl0_info->sat_status,\
						ctrl0_info->mute_on,ctrl0_info->hv_same);
					PE_INF_O22_DBG_PRINT("ctrl[0] : pxl_rp,s_frz,f_s,vcp_mute_on,is_ndskip:%d,%d,%d,%d,%d\n",\
						ctrl0_info->pxl_rp_st,ctrl0_info->is_src_frz,ctrl0_info->fw_src,\
						ctrl0_info->vcp_mute_on,ctrl0_info->is_ndskip);
					PE_INF_O22_DBG_PRINT("disp[1] : src:%d,fmt:%d (h:%d,v:%d)\n", \
						disp1_info->src_type, disp1_info->fmt_type, \
						disp1_info->in_h_size, disp1_info->in_v_size);
					PE_INF_O22_DBG_PRINT("disp[1] : fr:%d(%d),scan:%d,cstd,hdmi,scart,dtv,hdd:%d,%d,%d,%d,%d\n", \
						disp1_info->fr_type, disp1_info->in_f_rate, disp1_info->scan_type, \
						disp1_info->cstd_type, disp1_info->hdmi_type, disp1_info->scart_type, \
						disp1_info->dtv_type, disp1_info->hdd_type);
					PE_INF_O22_DBG_PRINT("disp[1] : in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d\n", \
						disp1_info->in_win.x_ofst, disp1_info->in_win.y_ofst, \
						disp1_info->in_win.h_size, disp1_info->in_win.v_size, \
						disp1_info->out_win.x_ofst, disp1_info->out_win.y_ofst, \
						disp1_info->out_win.h_size, disp1_info->out_win.v_size, disp1_info->act_fmt);
					PE_INF_O22_DBG_PRINT("disp[1] : rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n", \
						disp1_info->mode.is_reverse, disp1_info->mode.is_oled,\
						disp1_info->mode.is_colmetry, disp1_info->mode.is_vr,disp1_info->mode.is_420,disp1_info->mode.is_orbit,disp1_info->mode.is_dsc);
					PE_INF_O22_DBG_PRINT("ctrl[1] : src:%d,%d,sc:%d, u_w i:%d,%d,%d,%d, o:%d,%d,%d,%d\n",\
						ctrl1_info->pe0_src_h,ctrl1_info->pe0_src_v,ctrl1_info->i_sc_type,\
						ctrl1_info->u_i_win_h_ofst,ctrl1_info->u_i_win_v_ofst,\
						ctrl1_info->u_i_win_h_size,ctrl1_info->u_i_win_v_size,\
						ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
						ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);
					PE_INF_O22_DBG_PRINT("ctrl[1] : c_fmt:%d,s_stat:%d,mute_on:%d,hv_same:%d\n",\
						ctrl1_info->i_c_format,\
						ctrl1_info->sat_status,\
						ctrl1_info->mute_on,ctrl1_info->hv_same);
					PE_INF_O22_DBG_PRINT("ctrl[1] : pxl_rp,s_frz,f_s:%d,%d,%d\n",\
						ctrl1_info->pxl_rp_st,ctrl1_info->is_src_frz,ctrl1_info->fw_src);
					PE_INF_O22_DBG_PRINT("\n");
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}

/**
 * PE_INF_O22_IncChipInfoApbCount(O22F22_APB)
 *
 * @param   type [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_IncChipInfoApbCount(UINT32 type)
{
    int ret = RET_OK;

	#ifdef PE_HW_O22_BRINGUP
	UINT32 cnt;

	if (!gPE_CHPI_DDR_O22)					return ret;
	if (type & _g_pe_inf_o22_chpi_block)	return ret;

	if (type & PE_INF_O22_CHPI_APB_CMN0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt0.cmn0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt0.cmn0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt0.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_CEN0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt0.cen0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt0.cen0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt0.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_CEN1)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt0.cen1);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt0.cen1,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt0.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_CW0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt0.cw0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt0.cw0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt0.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_VSP0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt1.vsp0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt1.vsp0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt1.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_DSE0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt1.dse0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt1.dse0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt1.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_DCE0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt1.dce0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt1.dce0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt1.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_DTM0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt1.dtm0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt1.dtm0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt1.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_LLL0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt2.lll0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt2.lll0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt2.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_FSW0)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt2.fsw0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt2.fsw0,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt2.udata32);
	}
	#if 0	//fw ctrl
	if (type & PE_INF_O22_CHPI_APB_TM)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt6.tm);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt6.tm,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt6.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_YG)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt6.yg);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt6.yg,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt6.udata32);
	}
	#endif
	if (type & PE_INF_O22_CHPI_APB_HS)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt7.hs);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt7.hs,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt7.udata32);
	}
	if (type & PE_INF_O22_CHPI_APB_PCC)
	{
		cnt = PE_CHPI_APB0_O22F22_Rd(head1.cnt7.pcc);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_APB0_O22F22_Wr(head1.cnt7.pcc,cnt);
		PE_CHPI_APB0_O22F22_WrFL(head1.cnt7.udata32);
	}
	#endif

	return ret;
}

/**
 * PE_INF_O22_IncChipInfoTblCount(O22F22_TBL)
 *
 * @param   type [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_IncChipInfoTblCount(UINT32 type)
{
    int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 cnt;

	if (!gPE_CHPI_DDR_O22)					return ret;
	if (type & _g_pe_inf_o22_chpi_count)	return ret;

	if (type & PE_INF_O22_CHPI_TBL_CCO)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt0.cco);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt0.cco,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt0.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_OBC)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt0.obc);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt0.obc,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt0.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_OBE)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt0.obe);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt0.obe,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt0.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_AMG)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt0.amg);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt0.amg,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt0.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_RES)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt1.res);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt1.res,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt1.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_CTI)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt1.cti);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt1.cti,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt1.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_TNR)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt1.tnr);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt1.tnr,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt1.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_DNR)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt1.dnr);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt1.dnr,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt1.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_OSD)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt2.osd);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt2.osd,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt2.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_SQM0)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt2.sqm0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt2.sqm0,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt2.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_SQM1)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt2.sqm1);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt2.sqm1,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt2.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_SQM2)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt2.sqm2);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt2.sqm2,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt2.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_SQM3)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt3.sqm3);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt3.sqm3,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt3.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_SQM4)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt3.sqm4);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt3.sqm4,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt3.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_USR0)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt3.usr0);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt3.usr0,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt3.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_USR1)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt3.usr1);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt3.usr1,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt3.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_USR2)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt4.usr2);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt4.usr2,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt4.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_DRC)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt4.drc);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt4.drc,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt4.udata32);
	}
	if (type & PE_INF_O22_CHPI_TBL_OBEC)
	{
		cnt = PE_CHPI_TBL0_O22F22_Rd(head1.cnt4.obec);
		cnt = (cnt==PE_INF_O22_INC_CHPI_CNT_MAX)? 1:(cnt+1);
		PE_CHPI_TBL0_O22F22_Wr(head1.cnt4.obec,cnt);
		PE_CHPI_TBL0_O22F22_WrFL(head1.cnt4.udata32);
	}
	#endif
	return ret;
}

/**
 * PE_INF_O22_GetChipInfoData(O22F22_APB)
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @param   *buffer [in/out] char
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_INF_O22_GetChipInfoData(LX_PE_ETC_TBL_T *pstParams, char *buffer)
{
    int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 cnt;//, base, number, data;
	__attribute__((unused)) static volatile UINT32 *p_chpi_ddr = 0;

	do {
		CHECK_KNULL(pstParams);
		CHECK_KNULL(buffer);
		CHECK_KNULL(pstParams->data);
		cnt = pstParams->oper;

		if (pstParams->data[1]==2)
		{
			if (cnt==0)
			{
				snprintf(buffer,PE_TRACE_STR_SIZE,"block apb:0x%08x, tbl:0x%08x\n",_g_pe_inf_o22_chpi_block,_g_pe_inf_o22_chpi_count);
			}
			else
			{
				if (pstParams->data[2] == 0)
				{
					_g_pe_inf_o22_chpi_block = pstParams->data[3];
					PE_INF_O22_IncChipInfoApbCount(PE_INF_O22_CHPI_APB_MAX);
				}
				else if (pstParams->data[2] == 1)
				{
					_g_pe_inf_o22_chpi_count = pstParams->data[3];
					PE_INF_O22_IncChipInfoTblCount(PE_INF_O22_CHPI_TBL_MAX);
				}
				snprintf(buffer,PE_TRACE_STR_SIZE,"END_OF_PRINT");
			}
		}
		else
		{
			snprintf(buffer,PE_TRACE_STR_SIZE,"END_OF_PRINT");
		}
	} while(0);
	#endif
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
static int PE_INF_O22_GetGeneralPicInfo(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0;
	PE_WIN_HW_O22_SETTINGS_T *win_set = NULL;
	static PE_DDR_O22_TOP_HEADER_T *p_h_top = NULL;
	static PE_DDR_O22_DATA_T *p_sec_data = NULL;
	__attribute__((unused)) static PE_LGSR_DDR_O22_TOP_HEADER_T *p_h_top_lgsr = NULL;
	__attribute__((unused)) static PE_LGSR_DDR_O22_DATA_T *p_sec_data_lgsr = NULL;
	static PE_DDR_O22F22_TOP_HEADER_T *p_h_top_o22f22 = NULL;
	static PE_DDR_O22F22_DATA_T *p_sec_data_o22f22 = NULL;
	__attribute__((unused)) static PE_LGSR_DDR_O22F22_TOP_HEADER_T *p_h_top_lgsr_o22f22 = NULL;
	__attribute__((unused)) static PE_LGSR_DDR_O22F22_DATA_T *p_sec_data_lgsr_o22f22 = NULL;
	static UINT32 ddr_total=0;
	LX_PE_INF_DISPLAY_T *disp0_inf = &(_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_0]);
	LX_PE_INF_DISPLAY_T *disp1_inf = &(_g_pe_inf_hw_o22_info.disp_info[LX_PE_WIN_1]);
	__attribute__((unused)) PE_INF_O22_CTRL_T *ctrl0_inf = &(_g_pe_inf_hw_o22_info.ctrl_info[LX_PE_WIN_0]);
	__attribute__((unused)) PE_INF_O22_CTRL_T *ctrl1_inf = &(_g_pe_inf_hw_o22_info.ctrl_info[LX_PE_WIN_1]);

#define WIN0	LX_PE_WIN_0
#define WIN1	LX_PE_WIN_1
#define PE_INF_O22_PRINT_START		"START_OF_PRINT"
#define PE_INF_O22_PRINT_RESERVED	"RESERVED"
#define PE_INF_O22_PRINT_END		"END_OF_PRINT"
#define PE_INF_O22_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_INF_O22_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE, "   [0x%02x] %s\n", (_item), #_item);_action;break
#define PE_INF_O22_CASE_SPRINT(_cnt,_action,_buf,fmt,args...)	\
	case (_cnt):snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break
#define PE_INF_O22_DFLT_SPRINT(_action,_buf,fmt,args...)		\
	default:snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		if(PE_KDRV_VER_O22)
		{
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]==PE_INF_HW_O22_GINFO_DISPLAY)
			{
				switch (rd_cnt)
				{
					PE_INF_O22_CASE_SPRINT( 0, rd_cnt++, buffer, PE_INF_O22_PRINT_START);
					PE_INF_O22_CASE_PRMENU( 1, rd_cnt++, buffer, PE_INF_HW_O22_GINFO__KDRV_INFO);
					PE_INF_O22_CASE_PRMENU( 2, rd_cnt++, buffer, PE_INF_HW_O22_GINFO_DDR_H_PHYS);
					PE_INF_O22_CASE_PRMENU( 3, rd_cnt++, buffer, PE_INF_HW_O22_GINFO_DDR_H_SHDW);
					PE_INF_O22_CASE_PRMENU( 4, rd_cnt++, buffer, PE_INF_HW_O22_GINFO_LGSR_DDR_H_PHYS);
					PE_INF_O22_CASE_PRMENU( 5, rd_cnt++, buffer, PE_INF_HW_O22_GINFO_LGSR_DDR_H_SHDW);
					PE_INF_O22_CASE_PRMENU( 6, rd_cnt++, buffer, PE_INF_HW_O22_GINFO_CHIP_INFO);
					PE_INF_O22_CASE_PRMENU( 7, rd_cnt++, buffer, PE_INF_HW_O22_GINFO_O22F22_DDR_H_PHYS);
					PE_INF_O22_CASE_PRMENU( 8, rd_cnt++, buffer, PE_INF_HW_O22_GINFO_O22F22_DDR_H_SHDW);
					PE_INF_O22_CASE_SPRINT( 9, rd_cnt++, buffer, PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(10, rd_cnt++, buffer, PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_DFLT_SPRINT(rd_cnt=0, buffer, PE_INF_O22_PRINT_END);
				}
			}
			else if (pstParams->data[0]==PE_INF_HW_O22_GINFO_CHIP_INFO)
			{
				PE_INF_O22_GetChipInfoData(pstParams, buffer);
			}
			else if (pstParams->data[0]==PE_INF_HW_O22_GINFO__KDRV_INFO)
			{
				win_set = (PE_WIN_HW_O22_SETTINGS_T *)OS_Malloc(sizeof(PE_WIN_HW_O22_SETTINGS_T));
				PE_INF_O22_CHECK_CODE(!win_set, break, "[%s,%d] win_set is null.\n", __F__, __L__);
				/* get win settings */
				ret = PE_WIN_HW_O22_GetCurWinSettings(win_set);
				PE_INF_O22_CHECK_CODE(ret,break,\
					"[%s,%d] PE_WIN_HW_O22_GetCurWinSettings() error.\n",__F__,__L__);
				switch(rd_cnt)
				{
					PE_INF_O22_CASE_SPRINT( 0,rd_cnt++,buffer,PE_INF_O22_PRINT_START);
					PE_INF_O22_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"src       : 0~6:dtv,atv,cvbs,scart,comp,rgbpc,hdmi\n");
					PE_INF_O22_CASE_SPRINT( 3,rd_cnt++,buffer,\
						"fmt/fr    : 0~2:sd,hd,uhd / 0~1:60hz,50hz\n");
					PE_INF_O22_CASE_SPRINT( 4,rd_cnt++,buffer,\
						"scan/cstd : 0~1:i,p / 0~2:ntsc,pal,secam\n");
					PE_INF_O22_CASE_SPRINT( 5,rd_cnt++,buffer,\
						"hdmi/scart: 0~1:tv,pc / 0~1:av,rgb\n");
					PE_INF_O22_CASE_SPRINT( 6,rd_cnt++,buffer,\
						"dtv       : 0:normal,1:file,2:hdd,3:photo,4:tp,5:camera,6:invalid\n");
					PE_INF_O22_CASE_SPRINT( 7,rd_cnt++,buffer,\
						"hdd       : 0:dtv,1:atv60,2:atv50,3:av60,4:av50,5:scartrgb,6:invalid\n");
					PE_INF_O22_CASE_SPRINT( 8,rd_cnt++,buffer,\
						"out       : 0~3:2d,3_2d,2_3d,ud, 4~6:tb,ss,fs, 7~9:dual_t,s,f, 10:pip\n");
					PE_INF_O22_CASE_SPRINT( 9,rd_cnt++,buffer,\
						"in        : 0tb,ss,q,cb,fp,5fi,fa,fs,la,9ssf,dua,ca,lah\n");
					PE_INF_O22_CASE_SPRINT(10,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(11,rd_cnt++,buffer,\
						"[%02d]disp0: wid:%d,src:%d,fmt:%d (h:%d,v:%d)\n",rd_cnt,\
						disp0_inf->win_id,disp0_inf->src_type,disp0_inf->fmt_type,\
						disp0_inf->in_h_size,disp0_inf->in_v_size);
					PE_INF_O22_CASE_SPRINT(12,rd_cnt++,buffer,\
						"[%02d]disp0: fr:%d(%d),scan:%d,cstd:%d,hdmi:%d,scart:%d,dtv:%d,hdd:%d\n",rd_cnt,\
						disp0_inf->fr_type,disp0_inf->in_f_rate,disp0_inf->scan_type,disp0_inf->cstd_type,\
						disp0_inf->hdmi_type,disp0_inf->scart_type,disp0_inf->dtv_type,disp0_inf->hdd_type);
					PE_INF_O22_CASE_SPRINT(13,rd_cnt++,buffer,\
						"[%02d]disp0:empty\n",rd_cnt);
					PE_INF_O22_CASE_SPRINT(14,rd_cnt++,buffer,\
						"[%02d]disp0: in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d\n",rd_cnt,\
						disp0_inf->in_win.x_ofst,disp0_inf->in_win.y_ofst,disp0_inf->in_win.h_size,\
						disp0_inf->in_win.v_size,disp0_inf->out_win.x_ofst,disp0_inf->out_win.y_ofst,\
						disp0_inf->out_win.h_size,disp0_inf->out_win.v_size,disp0_inf->act_fmt);
					PE_INF_O22_CASE_SPRINT(15,rd_cnt++,buffer,\
						"[%02d]disp0: rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n",rd_cnt, \
						disp0_inf->mode.is_reverse, disp0_inf->mode.is_oled,\
						disp0_inf->mode.is_colmetry, disp0_inf->mode.is_vr, disp0_inf->mode.is_420,disp0_inf->mode.is_orbit,disp0_inf->mode.is_dsc);
					PE_INF_O22_CASE_SPRINT(16,rd_cnt++,buffer,\
						"[%02d]disp1: wid:%d,src:%d,fmt:%d (h:%d,v:%d)\n",rd_cnt,\
						disp1_inf->win_id,disp1_inf->src_type,disp1_inf->fmt_type,\
						disp1_inf->in_h_size,disp1_inf->in_v_size);
					PE_INF_O22_CASE_SPRINT(17,rd_cnt++,buffer,\
						"[%02d]disp1: fr:%d(%d),scan:%d,cstd:%d,hdmi:%d,scart:%d,dtv:%d,hdd:%d\n",rd_cnt,\
						disp1_inf->fr_type,disp1_inf->in_f_rate,disp1_inf->scan_type,disp1_inf->cstd_type,\
						disp1_inf->hdmi_type,disp1_inf->scart_type,disp1_inf->dtv_type,disp1_inf->hdd_type);
					PE_INF_O22_CASE_SPRINT(18,rd_cnt++,buffer,\
						"[%02d]disp1:empty\n",rd_cnt);
					PE_INF_O22_CASE_SPRINT(19,rd_cnt++,buffer,\
						"[%02d]disp1: in_win:%d,%d,%d,%d,out_win:%d,%d,%d,%d,af:%d\n",rd_cnt,\
						disp1_inf->in_win.x_ofst,disp1_inf->in_win.y_ofst,disp1_inf->in_win.h_size,\
						disp1_inf->in_win.v_size,disp1_inf->out_win.x_ofst,disp1_inf->out_win.y_ofst,\
						disp1_inf->out_win.h_size,disp1_inf->out_win.v_size,disp1_inf->act_fmt);
					PE_INF_O22_CASE_SPRINT(20,rd_cnt++,buffer,\
						"[%02d]disp1: rev,oled,cm,vr,420,orbit,dsc:%d,%d,%d,%d,%d,%d,%d\n", rd_cnt,\
						disp1_inf->mode.is_reverse, disp1_inf->mode.is_oled,\
						disp1_inf->mode.is_colmetry,disp1_inf->mode.is_vr, disp1_inf->mode.is_420, disp1_inf->mode.is_orbit,disp1_inf->mode.is_dsc);
					PE_INF_O22_CASE_SPRINT(21,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(22,rd_cnt++,buffer,\
						"det_3df: 0:2d,1:cb,2,cc,3:ll,4:ss,5:tb,6:unknown,7:max\n");
					PE_INF_O22_CASE_SPRINT(23,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(24,rd_cnt++,buffer,"[%02d]ctrl0:\n",rd_cnt);
					PE_INF_O22_CASE_SPRINT(25,rd_cnt++,buffer,\
						"[%02d]pe0_src_h,v:%d,%d, i_sc:%d\n",rd_cnt,\
						ctrl0_inf->pe0_src_h,ctrl0_inf->pe0_src_v,ctrl0_inf->i_sc_type);
					PE_INF_O22_CASE_SPRINT(26,rd_cnt++,buffer,\
						"[%02d]u_win i:%d,%d,%d,%d, o:%d,%d,%d,%d\n",rd_cnt,\
						ctrl0_inf->u_i_win_h_ofst,ctrl0_inf->u_i_win_v_ofst,\
						ctrl0_inf->u_i_win_h_size,ctrl0_inf->u_i_win_v_size,\
						ctrl0_inf->u_o_win_h_ofst,ctrl0_inf->u_o_win_v_ofst,\
						ctrl0_inf->u_o_win_h_size,ctrl0_inf->u_o_win_v_size);
					PE_INF_O22_CASE_SPRINT(27,rd_cnt++,buffer,\
						"[%02d]c_fmt:%d,s_state:%d,mute_on:%d,hv_same:%d\n",rd_cnt,\
						ctrl0_inf->i_c_format,\
						ctrl0_inf->sat_status,ctrl0_inf->mute_on,ctrl0_inf->hv_same);
					PE_INF_O22_CASE_SPRINT(28,rd_cnt++,buffer,\
						"[%02d]pxl_rp,s_frz,f_s:%d,%d,%d\n",rd_cnt,\
						ctrl0_inf->pxl_rp_st,ctrl0_inf->is_src_frz,\
						ctrl0_inf->fw_src);
					PE_INF_O22_CASE_SPRINT(29,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(30,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(31,rd_cnt++,buffer,"[%02d]ctrl1:\n",rd_cnt);
					PE_INF_O22_CASE_SPRINT(32,rd_cnt++,buffer,\
						"[%02d]pe0_src_h,v:%d,%d, i_sc:%d\n",rd_cnt,\
						ctrl1_inf->pe0_src_h,ctrl1_inf->pe0_src_v,ctrl1_inf->i_sc_type);
					PE_INF_O22_CASE_SPRINT(33,rd_cnt++,buffer,\
						"[%02d]u_win i:%d,%d,%d,%d, o:%d,%d,%d,%d\n",rd_cnt,\
						ctrl1_inf->u_i_win_h_ofst,ctrl1_inf->u_i_win_v_ofst,\
						ctrl1_inf->u_i_win_h_size,ctrl1_inf->u_i_win_v_size,\
						ctrl1_inf->u_o_win_h_ofst,ctrl1_inf->u_o_win_v_ofst,\
						ctrl1_inf->u_o_win_h_size,ctrl1_inf->u_o_win_v_size);
					PE_INF_O22_CASE_SPRINT(34,rd_cnt++,buffer,\
						"[%02d]c_fmt:%d,s_state:%d,mute_on:%d,hv_same:%d\n",rd_cnt,\
						ctrl1_inf->i_c_format,\
						ctrl1_inf->sat_status,ctrl1_inf->mute_on,ctrl1_inf->hv_same);
					PE_INF_O22_CASE_SPRINT(35,rd_cnt++,buffer,\
						"[%02d]pxl_rp,s_frz,f_s:%d,%d,%d\n",rd_cnt,\
						ctrl1_inf->pxl_rp_st,ctrl1_inf->is_src_frz,\
						ctrl1_inf->fw_src);
					PE_INF_O22_CASE_SPRINT(36,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(37,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(38,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(39,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(40,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(41,rd_cnt++,buffer,"[%02d]win:\n",rd_cnt);
					PE_INF_O22_CASE_SPRINT(42,rd_cnt++,buffer,\
						"[%02d]act0:%d,%d,%d,%d, act1:%d,%d,%d,%d\n",rd_cnt,\
						win_set->win_inf.act0_x0,win_set->win_inf.act0_y0,win_set->win_inf.act0_x1,\
						win_set->win_inf.act0_y1,win_set->win_inf.act1_x0,win_set->win_inf.act1_y0,\
						win_set->win_inf.act1_x1,win_set->win_inf.act1_y1);
					PE_INF_O22_CASE_SPRINT(43,rd_cnt++,buffer,\
						"[%02d]win0:%d,%d,%d,%d, win1:%d,%d,%d,%d\n",rd_cnt,\
						win_set->win_inf.win0_x0,win_set->win_inf.win0_y0,win_set->win_inf.win0_x1,\
						win_set->win_inf.win0_y1,win_set->win_inf.win1_x0,win_set->win_inf.win1_y0,\
						win_set->win_inf.win1_x1,win_set->win_inf.win1_y1);
					PE_INF_O22_CASE_SPRINT(44,rd_cnt++,buffer,\
						"[%02d]h,v_max:%d,%d, w0,w1,w01_en:[%d,%d],[%d,%d],[%d,%d]\n",rd_cnt,\
						win_set->win_inf.h_max,win_set->win_inf.v_max,win_set->win_inf.win0_en[0],\
						win_set->win_inf.win0_en[1],win_set->win_inf.win1_en[0],win_set->win_inf.win1_en[1],\
						win_set->win_inf.win01_en[0],win_set->win_inf.win01_en[1]);
					PE_INF_O22_CASE_SPRINT(45,rd_cnt++,buffer,\
						"[%02d]lrcr histo_l,r, apply_r : %d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d\n",rd_cnt,\
						win_set->lrcr_inf.histo_l_x0,win_set->lrcr_inf.histo_l_y0,win_set->lrcr_inf.histo_l_x1,\
						win_set->lrcr_inf.histo_l_y1,win_set->lrcr_inf.histo_r_x0,win_set->lrcr_inf.histo_r_y0,\
						win_set->lrcr_inf.histo_r_x1,win_set->lrcr_inf.histo_r_y1,win_set->lrcr_inf.apply_r_x0,\
						win_set->lrcr_inf.apply_r_y0,win_set->lrcr_inf.apply_r_x1,win_set->lrcr_inf.apply_r_y1);
					PE_INF_O22_CASE_SPRINT(46,rd_cnt++,buffer,\
						"[%02d]win: tnr win h,v size0:%d,%d, size1:%d,%d\n",rd_cnt,\
						win_set->tnr_inf.h_size0,win_set->tnr_inf.v_size0,\
						win_set->tnr_inf.h_size1,win_set->tnr_inf.v_size1);
					PE_INF_O22_CASE_SPRINT(47,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(48,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(49,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(50,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(51,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(52,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(53,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(54,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(55,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(56,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(57,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(58,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(59,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(60,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(61,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(62,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(63,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(64,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(65,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(66,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(67,rd_cnt++,buffer,\
						"[%02d]db mode : shp:%d,hst:%d,scl:%d,tnr:%d,dnr:%d\n",rd_cnt,\
						PE_CMN_HW_O22_GetDbInfo(PE_CMN_HW_O22_DB_INF_MD0_SHP_FW_EN, 0), \
						PE_CMN_HW_O22_GetDbInfo(PE_CMN_HW_O22_DB_INF_MD0_HST_FW_EN, 0), \
						PE_CMN_HW_O22_GetDbInfo(PE_CMN_HW_O22_DB_INF_MD0_SCL_FW_EN, 0), \
						PE_CMN_HW_O22_GetDbInfo(PE_CMN_HW_O22_DB_INF_MD0_TNR_FW_EN, 0), \
						PE_CMN_HW_O22_GetDbInfo(PE_CMN_HW_O22_DB_INF_MD0_DNR_FW_EN, 0));
					PE_INF_O22_CASE_SPRINT(68,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(69,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(70,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(71,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(72,rd_cnt++,buffer,\
						"- kdrv ver. : %s\n", PE_INF_O22_DRV_VER);
					PE_INF_O22_CASE_SPRINT(73,rd_cnt++,buffer,\
						"---------------------------------------------------------------------------\n");
					PE_INF_O22_DFLT_SPRINT(rd_cnt=0,buffer,PE_INF_O22_PRINT_END);
				}
			}
			else if (pstParams->data[0]==PE_INF_HW_O22_GINFO_DDR_H_PHYS || \
				pstParams->data[0]==PE_INF_HW_O22_GINFO_DDR_H_SHDW)
			{
				PE_DDR_DB_SHDW_REG_O22_T *p_shdw_db = gPE_DDR_DB_O22.shdw.data;
				UINT32 *p_s_base = NULL;
				UINT32 *p_s_size = NULL;
				UINT32 sec_typ;
				PE_DDR_O22_HEADER_T *p_sec_h = NULL;
				if (rd_cnt==0)
				{
					ddr_total = 0;
					p_sec_data = (PE_DDR_O22_DATA_T *)OS_Malloc(sizeof(PE_DDR_O22_DATA_T)*PE_DDR_O22_SEC_MAX_SIZE);
					CHECK_KNULL(p_sec_data);
					p_h_top = (PE_DDR_O22_TOP_HEADER_T *)OS_Malloc(sizeof(PE_DDR_O22_TOP_HEADER_T));
					CHECK_KNULL(p_h_top);
					if (pstParams->data[0]==PE_INF_HW_O22_GINFO_DDR_H_PHYS)
					{
						PE_INF_O22_GetCurDdrTopHeader((void *)p_h_top);
						for (sec_typ=0; sec_typ<PE_DDR_O22_SEC_NUM; sec_typ++)
						{
							p_sec_h = &(p_sec_data[sec_typ].header);
							PE_INF_O22_GetCurDdrSecHeader((void *)p_h_top, (void *)p_sec_h, sec_typ);
						}
					}
					else
					{
						memcpy(p_h_top, &(p_shdw_db->top_h), sizeof(PE_DDR_O22_TOP_HEADER_T));
						for (sec_typ=0; sec_typ<PE_DDR_O22_SEC_NUM; sec_typ++)
						{
							p_sec_data[sec_typ].header = p_shdw_db->sec_d[sec_typ].header;
						}
					}
					for (sec_typ=0; sec_typ<PE_DDR_O22_SEC_NUM; sec_typ++)
					{
						p_sec_data[sec_typ].data_base = p_shdw_db->sec_d[sec_typ].data_base;
						ddr_total += p_h_top->sec_size[sec_typ];
					}
				}
				p_s_base = p_h_top->sec_base;
				p_s_size = p_h_top->sec_size;
				/* causion : p_s_base and p_s_size should sync with PE_DDR_O22_SEC_MAX_SIZE */
				switch(rd_cnt)
				{
					PE_INF_O22_CASE_SPRINT( 0,rd_cnt++,buffer,PE_INF_O22_PRINT_START);
					PE_INF_O22_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"[%02d]top_h     : ver:%08x b_a:%08x s_n:%08x total_size:%d\n", rd_cnt, \
						p_h_top->version, p_h_top->db_base, p_h_top->sec_num, ddr_total);
					PE_INF_O22_CASE_SPRINT( 3,rd_cnt++,buffer, \
						"[%02d]top_h base: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
						p_s_base[0], p_s_base[1], p_s_base[2], p_s_base[3], p_s_base[4]);
					PE_INF_O22_CASE_SPRINT( 4,rd_cnt++,buffer, \
						"[%02d]top_h size: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
						p_s_size[0], p_s_size[1], p_s_size[2], p_s_size[3], p_s_size[4]);
					PE_INF_O22_CASE_SPRINT( 5,rd_cnt++,buffer, \
						"[%02d]top_h base: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
						p_s_base[5], p_s_base[6], p_s_base[7], p_s_base[8], p_s_base[9]);
					PE_INF_O22_CASE_SPRINT( 6,rd_cnt++,buffer, \
						"[%02d]top_h size: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
						p_s_size[5], p_s_size[6], p_s_size[7], p_s_size[8], p_s_size[9]);
					PE_INF_O22_CASE_SPRINT( 7,rd_cnt++,buffer, \
						"[%02d]top_h base: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
						p_s_base[10], p_s_base[11], p_s_base[12], p_s_base[13], p_s_base[14]);
					PE_INF_O22_CASE_SPRINT( 8,rd_cnt++,buffer, \
						"[%02d]top_h size: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
						p_s_size[10], p_s_size[11], p_s_size[12], p_s_size[13], p_s_size[14]);
					PE_INF_O22_CASE_SPRINT( 9,rd_cnt++,buffer, \
						"[%02d]top_h base: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
						p_s_base[15], p_s_base[16], p_s_base[17], p_s_base[18], p_s_base[19]);
					PE_INF_O22_CASE_SPRINT(10,rd_cnt++,buffer, \
						"[%02d]top_h size: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
						p_s_size[15], p_s_size[16], p_s_size[17], p_s_size[18], p_s_size[19]);
					PE_INF_O22_CASE_SPRINT(11,rd_cnt++,buffer, \
						"[%02d]top_h base: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
						p_s_base[20], p_s_base[21], p_s_base[22], p_s_base[23], p_s_base[24]);
					PE_INF_O22_CASE_SPRINT(12,rd_cnt++,buffer, \
						"[%02d]top_h size: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
						p_s_size[20], p_s_size[21], p_s_size[22], p_s_size[23], p_s_size[24]);
					PE_INF_O22_CASE_SPRINT(13,rd_cnt++,buffer, \
						"[%02d]top_h base: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
						p_s_base[25], p_s_base[26], p_s_base[27], p_s_base[28], p_s_base[29]);
					PE_INF_O22_CASE_SPRINT(14,rd_cnt++,buffer, \
						"[%02d]top_h size: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
						p_s_size[25], p_s_size[26], p_s_size[27], p_s_size[28], p_s_size[29]);
					PE_INF_O22_CASE_SPRINT(15,rd_cnt++,buffer, \
						"[%02d]top_h base: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
						p_s_base[30], p_s_base[31], p_s_base[32], p_s_base[33], p_s_base[34]);
					PE_INF_O22_CASE_SPRINT(16,rd_cnt++,buffer, \
						"[%02d]top_h size: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
						p_s_size[30], p_s_size[31], p_s_size[32], p_s_size[33], p_s_size[34]);
					PE_INF_O22_CASE_SPRINT(17,rd_cnt++,buffer, \
						"[%02d]top_h base: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
						p_s_base[35], p_s_base[36], p_s_base[37], p_s_base[38], p_s_base[39]);
					PE_INF_O22_CASE_SPRINT(18,rd_cnt++,buffer, \
						"[%02d]top_h size: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
						p_s_size[35], p_s_size[36], p_s_size[37], p_s_size[38], p_s_size[39]);
					PE_INF_O22_CASE_SPRINT(19,rd_cnt++,buffer, \
						"[%02d]top_h base: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
						p_s_base[40], p_s_base[41], p_s_base[42], p_s_base[43], p_s_base[44]);
					PE_INF_O22_CASE_SPRINT(20,rd_cnt++,buffer, \
						"[%02d]top_h size: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
						p_s_size[40], p_s_size[41], p_s_size[42], p_s_size[43], p_s_size[44]);
					PE_INF_O22_CASE_SPRINT(21,rd_cnt++,buffer, \
						"[%02d]top_h base: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
						p_s_base[45], p_s_base[46], p_s_base[47], p_s_base[48], p_s_base[49]);
					PE_INF_O22_CASE_SPRINT(22,rd_cnt++,buffer, \
						"[%02d]top_h size: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
						p_s_size[45], p_s_size[46], p_s_size[47], p_s_size[48], p_s_size[49]);
					PE_INF_O22_CASE_SPRINT(23,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(24,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(25,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(26,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(27,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(28,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(29,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(30,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(31,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(32,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(33,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(34,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(35,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(36,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(37,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(38,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(39,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(40,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(41,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(42,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(43,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(44,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(45,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(46,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(47,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(48,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(49,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(50,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(51,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(52,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(53,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(54,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(55,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(56,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(57,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(58,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(59,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(60,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(61,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(62,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(63,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(64,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(65,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(66,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(67,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data[rd_cnt-40].header.version, p_sec_data[rd_cnt-40].header.sec_type, \
						p_sec_data[rd_cnt-40].header.item_num, p_sec_data[rd_cnt-40].header.item_size, \
						p_sec_data[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(68,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_DFLT_SPRINT(rd_cnt=0,buffer,PE_INF_O22_PRINT_END);
				}
				if (rd_cnt==0)
				{
					if (p_h_top)	{OS_Free(p_h_top);}
					if (p_sec_data)	{OS_Free(p_sec_data);}
				}
			}
			else if (pstParams->data[0]==PE_INF_HW_O22_GINFO_O22F22_DDR_H_PHYS || \
				pstParams->data[0]==PE_INF_HW_O22_GINFO_O22F22_DDR_H_SHDW)
			{
				PE_DDR_DB_SHDW_REG_O22F22_T *p_shdw_db = gPE_DDR_DB_O22F22.shdw.data;
				__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O22F22_T *p_phys_db = gPE_DDR_DB_O22F22.phys.data;
				UINT32 *p_s_base = NULL;
				UINT32 *p_s_size = NULL;
				UINT32 sec_typ;
				PE_DDR_O22F22_HEADER_T *p_sec_h = NULL;
				if (rd_cnt==0)
				{
					ddr_total = 0;
					p_sec_data_o22f22 = (PE_DDR_O22F22_DATA_T *)OS_Malloc(sizeof(PE_DDR_O22F22_DATA_T)*PE_DDR_O22F22_SEC_MAX_SIZE);
					CHECK_KNULL(p_sec_data_o22f22);
					p_h_top_o22f22 = (PE_DDR_O22F22_TOP_HEADER_T *)OS_Malloc(sizeof(PE_DDR_O22F22_TOP_HEADER_T));
					CHECK_KNULL(p_h_top_o22f22);
					if (pstParams->data[0]==PE_INF_HW_O22_GINFO_O22F22_DDR_H_PHYS)
					{
						PE_INF_O22F22_GetCurDdrTopHeader((void *)p_h_top_o22f22);
						for (sec_typ=0; sec_typ<PE_DDR_O22F22_SEC_NUM; sec_typ++)
						{
							p_sec_h = &(p_sec_data_o22f22[sec_typ].header);
							PE_INF_O22F22_GetCurDdrSecHeader((void *)p_h_top_o22f22, (void *)p_sec_h, sec_typ);
						}
					}
					else
					{
						memcpy(p_h_top_o22f22, &(p_shdw_db->top_h), sizeof(PE_DDR_O22F22_TOP_HEADER_T));
						for (sec_typ=0; sec_typ<PE_DDR_O22F22_SEC_NUM; sec_typ++)
						{
							p_sec_data_o22f22[sec_typ].header = p_shdw_db->sec_d[sec_typ].header;
						}
					}
					for (sec_typ=0; sec_typ<PE_DDR_O22F22_SEC_NUM; sec_typ++)
					{
						p_sec_data_o22f22[sec_typ].data_base = p_shdw_db->sec_d[sec_typ].data_base;
						ddr_total += p_h_top_o22f22->sec_size[sec_typ];
					}
				}
				p_s_base = p_h_top_o22f22->sec_base;
				p_s_size = p_h_top_o22f22->sec_size;
				/* causion : p_s_base and p_s_size should sync with PE_DDR_O22F22_SEC_MAX_SIZE */
				switch(rd_cnt)
				{
					PE_INF_O22_CASE_SPRINT( 0,rd_cnt++,buffer,PE_INF_O22_PRINT_START);
					PE_INF_O22_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"[%02d]top_h	 : ver:%08x b_a:%08x s_n:%08x total_size:%d\n", rd_cnt, \
						p_h_top_o22f22->version, p_h_top_o22f22->db_base, p_h_top_o22f22->sec_num, ddr_total);
					PE_INF_O22_CASE_SPRINT( 3,rd_cnt++,buffer, \
						"[%02d]top_h base: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
						p_s_base[0], p_s_base[1], p_s_base[2], p_s_base[3], p_s_base[4]);
					PE_INF_O22_CASE_SPRINT( 4,rd_cnt++,buffer, \
						"[%02d]top_h size: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
						p_s_size[0], p_s_size[1], p_s_size[2], p_s_size[3], p_s_size[4]);
					PE_INF_O22_CASE_SPRINT( 5,rd_cnt++,buffer, \
						"[%02d]top_h base: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
						p_s_base[5], p_s_base[6], p_s_base[7], p_s_base[8], p_s_base[9]);
					PE_INF_O22_CASE_SPRINT( 6,rd_cnt++,buffer, \
						"[%02d]top_h size: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
						p_s_size[5], p_s_size[6], p_s_size[7], p_s_size[8], p_s_size[9]);
					PE_INF_O22_CASE_SPRINT( 7,rd_cnt++,buffer, \
						"[%02d]top_h base: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
						p_s_base[10], p_s_base[11], p_s_base[12], p_s_base[13], p_s_base[14]);
					PE_INF_O22_CASE_SPRINT( 8,rd_cnt++,buffer, \
						"[%02d]top_h size: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
						p_s_size[10], p_s_size[11], p_s_size[12], p_s_size[13], p_s_size[14]);
					PE_INF_O22_CASE_SPRINT( 9,rd_cnt++,buffer, \
						"[%02d]top_h base: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
						p_s_base[15], p_s_base[16], p_s_base[17], p_s_base[18], p_s_base[19]);
					PE_INF_O22_CASE_SPRINT(10,rd_cnt++,buffer, \
						"[%02d]top_h size: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
						p_s_size[15], p_s_size[16], p_s_size[17], p_s_size[18], p_s_size[19]);
					PE_INF_O22_CASE_SPRINT(11,rd_cnt++,buffer, \
						"[%02d]top_h base: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
						p_s_base[20], p_s_base[21], p_s_base[22], p_s_base[23], p_s_base[24]);
					PE_INF_O22_CASE_SPRINT(12,rd_cnt++,buffer, \
						"[%02d]top_h size: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
						p_s_size[20], p_s_size[21], p_s_size[22], p_s_size[23], p_s_size[24]);
					PE_INF_O22_CASE_SPRINT(13,rd_cnt++,buffer, \
						"[%02d]top_h base: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
						p_s_base[25], p_s_base[26], p_s_base[27], p_s_base[28], p_s_base[29]);
					PE_INF_O22_CASE_SPRINT(14,rd_cnt++,buffer, \
						"[%02d]top_h size: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
						p_s_size[25], p_s_size[26], p_s_size[27], p_s_size[28], p_s_size[29]);
					PE_INF_O22_CASE_SPRINT(15,rd_cnt++,buffer, \
						"[%02d]top_h base: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
						p_s_base[30], p_s_base[31], p_s_base[32], p_s_base[33], p_s_base[34]);
					PE_INF_O22_CASE_SPRINT(16,rd_cnt++,buffer, \
						"[%02d]top_h size: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
						p_s_size[30], p_s_size[31], p_s_size[32], p_s_size[33], p_s_size[34]);
					PE_INF_O22_CASE_SPRINT(17,rd_cnt++,buffer, \
						"[%02d]top_h base: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
						p_s_base[35], p_s_base[36], p_s_base[37], p_s_base[38], p_s_base[39]);
					PE_INF_O22_CASE_SPRINT(18,rd_cnt++,buffer, \
						"[%02d]top_h size: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
						p_s_size[35], p_s_size[36], p_s_size[37], p_s_size[38], p_s_size[39]);
					PE_INF_O22_CASE_SPRINT(19,rd_cnt++,buffer, \
						"[%02d]top_h base: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
						p_s_base[40], p_s_base[41], p_s_base[42], p_s_base[43], p_s_base[44]);
					PE_INF_O22_CASE_SPRINT(20,rd_cnt++,buffer, \
						"[%02d]top_h size: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
						p_s_size[40], p_s_size[41], p_s_size[42], p_s_size[43], p_s_size[44]);
					PE_INF_O22_CASE_SPRINT(21,rd_cnt++,buffer, \
						"[%02d]top_h base: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
						p_s_base[45], p_s_base[46], p_s_base[47], p_s_base[48], p_s_base[49]);
					PE_INF_O22_CASE_SPRINT(22,rd_cnt++,buffer, \
						"[%02d]top_h size: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
						p_s_size[45], p_s_size[46], p_s_size[47], p_s_size[48], p_s_size[49]);
					PE_INF_O22_CASE_SPRINT(23,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(24,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(25,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(26,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(27,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(28,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(29,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(30,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(31,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(32,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(33,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(34,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(35,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(36,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(37,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(38,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(39,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(40,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(41,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(42,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(43,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(44,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(45,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(46,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(47,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(48,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(49,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(50,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(51,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(52,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(53,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(54,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(55,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(56,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(57,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(58,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(59,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(60,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(61,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(62,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(63,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(64,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(65,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x i_n:%08x i_s:%08x d_b:%08x\n", rd_cnt, \
						PE_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_o22f22[rd_cnt-40].header.version, p_sec_data_o22f22[rd_cnt-40].header.sec_type, \
						p_sec_data_o22f22[rd_cnt-40].header.item_num, p_sec_data_o22f22[rd_cnt-40].header.item_size, \
						p_sec_data_o22f22[rd_cnt-40].data_base);
					rmb();
					PE_INF_O22_CASE_SPRINT(66,rd_cnt++,buffer, \
						"[%02d]crc check:%08x \n", rd_cnt, p_phys_db->crc);
					rmb();
					PE_INF_O22_CASE_SPRINT(67,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_DFLT_SPRINT(rd_cnt=0,buffer,PE_INF_O22_PRINT_END);
				}
				if (rd_cnt==0)
				{
					if (p_h_top_o22f22)	{OS_Free(p_h_top_o22f22);}
					if (p_sec_data_o22f22) {OS_Free(p_sec_data_o22f22);}
				}
			}
			#ifndef PE_HW_O22_BRINGUP
			else if (pstParams->data[0]==PE_INF_HW_O22_GINFO_LGSR_DDR_H_PHYS || \
				pstParams->data[0]==PE_INF_HW_O22_GINFO_LGSR_DDR_H_SHDW)
			{
				PE_LGSR_DDR_DB_SHDW_REG_O22_T *p_shdw_db = gPE_LGSR_DDR_DB_O22.shdw.data;
				UINT32 *p_s_base = NULL;
				UINT32 *p_s_size = NULL;
				UINT32 sec_typ;
				PE_LGSR_DDR_O22_HEADER_T *p_sec_h = NULL;
				if (rd_cnt==0)
				{
					ddr_total = 0;
					p_sec_data_lgsr = (PE_LGSR_DDR_O22_DATA_T *)OS_Malloc(sizeof(PE_LGSR_DDR_O22_DATA_T)*PE_DDR_O22_SEC_MAX_SIZE);
					CHECK_KNULL(p_sec_data_lgsr);
					p_h_top_lgsr = (PE_LGSR_DDR_O22_TOP_HEADER_T *)OS_Malloc(sizeof(PE_LGSR_DDR_O22_TOP_HEADER_T));
					CHECK_KNULL(p_h_top_lgsr);
					if (pstParams->data[0]==PE_INF_HW_O22_GINFO_LGSR_DDR_H_PHYS)
					{
						PE_INF_O22_GetCurLgsrDdrTopHeader((void *)p_h_top_lgsr);
						for (sec_typ=0; sec_typ<PE_LGSR_DDR_O22_SEC_NUM; sec_typ++)
						{
							p_sec_h = &(p_sec_data_lgsr[sec_typ].header);
							PE_INF_O22_GetCurLgsrDdrSecHeader((void *)p_h_top_lgsr, (void *)p_sec_h, sec_typ);
						}
					}
					else
					{
						memcpy(p_h_top_lgsr, &(p_shdw_db->top_h), sizeof(PE_LGSR_DDR_O22_TOP_HEADER_T));
						for (sec_typ=0; sec_typ<PE_LGSR_DDR_O22_SEC_NUM; sec_typ++)
						{
							p_sec_data_lgsr[sec_typ].header = p_shdw_db->sec_d[sec_typ].header;
						}
					}
					for (sec_typ=0; sec_typ<PE_LGSR_DDR_O22_SEC_NUM; sec_typ++)
					{
						p_sec_data_lgsr[sec_typ].data_base = p_shdw_db->sec_d[sec_typ].data_base;
						ddr_total += p_h_top_lgsr->sec_size[sec_typ];
					}
				}
				p_s_base = p_h_top_lgsr->sec_base;
				p_s_size = p_h_top_lgsr->sec_size;
				/* causion : p_s_base and p_s_size should sync with PE_DDR_O22_SEC_MAX_SIZE */
				switch(rd_cnt)
				{
					PE_INF_O22_CASE_SPRINT( 0,rd_cnt++,buffer,PE_INF_O22_PRINT_START);
					PE_INF_O22_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"[%02d]top_h     : ver:%08x b_a:%08x s_n:%08x total_size:%d\n", rd_cnt, \
						p_h_top_lgsr->version, p_h_top_lgsr->db_base, p_h_top_lgsr->sec_num, ddr_total);
					PE_INF_O22_CASE_SPRINT( 3,rd_cnt++,buffer, \
						"[%02d]top_h base: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
						p_s_base[0], p_s_base[1], p_s_base[2], p_s_base[3], p_s_base[4]);
					PE_INF_O22_CASE_SPRINT( 4,rd_cnt++,buffer, \
						"[%02d]top_h size: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
						p_s_size[0], p_s_size[1], p_s_size[2], p_s_size[3], p_s_size[4]);
					PE_INF_O22_CASE_SPRINT( 5,rd_cnt++,buffer, \
						"[%02d]top_h base: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
						p_s_base[5], p_s_base[6], p_s_base[7], p_s_base[8], p_s_base[9]);
					PE_INF_O22_CASE_SPRINT( 6,rd_cnt++,buffer, \
						"[%02d]top_h size: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
						p_s_size[5], p_s_size[6], p_s_size[7], p_s_size[8], p_s_size[9]);
					PE_INF_O22_CASE_SPRINT( 7,rd_cnt++,buffer, \
						"[%02d]top_h base: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
						p_s_base[10], p_s_base[11], p_s_base[12], p_s_base[13], p_s_base[14]);
					PE_INF_O22_CASE_SPRINT( 8,rd_cnt++,buffer, \
						"[%02d]top_h size: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
						p_s_size[10], p_s_size[11], p_s_size[12], p_s_size[13], p_s_size[14]);
					PE_INF_O22_CASE_SPRINT( 9,rd_cnt++,buffer, \
						"[%02d]top_h base: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
						p_s_base[15], p_s_base[16], p_s_base[17], p_s_base[18], p_s_base[19]);
					PE_INF_O22_CASE_SPRINT(10,rd_cnt++,buffer, \
						"[%02d]top_h size: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
						p_s_size[15], p_s_size[16], p_s_size[17], p_s_size[18], p_s_size[19]);
					PE_INF_O22_CASE_SPRINT(11,rd_cnt++,buffer, \
						"[%02d]top_h base: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
						p_s_base[20], p_s_base[21], p_s_base[22], p_s_base[23], p_s_base[24]);
					PE_INF_O22_CASE_SPRINT(12,rd_cnt++,buffer, \
						"[%02d]top_h size: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
						p_s_size[20], p_s_size[21], p_s_size[22], p_s_size[23], p_s_size[24]);
					PE_INF_O22_CASE_SPRINT(13,rd_cnt++,buffer, \
						"[%02d]top_h base: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
						p_s_base[25], p_s_base[26], p_s_base[27], p_s_base[28], p_s_base[29]);
					PE_INF_O22_CASE_SPRINT(14,rd_cnt++,buffer, \
						"[%02d]top_h size: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
						p_s_size[25], p_s_size[26], p_s_size[27], p_s_size[28], p_s_size[29]);
					PE_INF_O22_CASE_SPRINT(15,rd_cnt++,buffer, \
						"[%02d]top_h base: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
						p_s_base[30], p_s_base[31], p_s_base[32], p_s_base[33], p_s_base[34]);
					PE_INF_O22_CASE_SPRINT(16,rd_cnt++,buffer, \
						"[%02d]top_h size: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
						p_s_size[30], p_s_size[31], p_s_size[32], p_s_size[33], p_s_size[34]);
					PE_INF_O22_CASE_SPRINT(17,rd_cnt++,buffer, \
						"[%02d]top_h base: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
						p_s_base[35], p_s_base[36], p_s_base[37], p_s_base[38], p_s_base[39]);
					PE_INF_O22_CASE_SPRINT(18,rd_cnt++,buffer, \
						"[%02d]top_h size: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
						p_s_size[35], p_s_size[36], p_s_size[37], p_s_size[38], p_s_size[39]);
					PE_INF_O22_CASE_SPRINT(19,rd_cnt++,buffer, \
						"[%02d]top_h base: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
						p_s_base[40], p_s_base[41], p_s_base[42], p_s_base[43], p_s_base[44]);
					PE_INF_O22_CASE_SPRINT(20,rd_cnt++,buffer, \
						"[%02d]top_h size: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
						p_s_size[40], p_s_size[41], p_s_size[42], p_s_size[43], p_s_size[44]);
					PE_INF_O22_CASE_SPRINT(21,rd_cnt++,buffer, \
						"[%02d]top_h base: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
						p_s_base[45], p_s_base[46], p_s_base[47], p_s_base[48], p_s_base[49]);
					PE_INF_O22_CASE_SPRINT(22,rd_cnt++,buffer, \
						"[%02d]top_h size: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
						p_s_size[45], p_s_size[46], p_s_size[47], p_s_size[48], p_s_size[49]);
					PE_INF_O22_CASE_SPRINT(23,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(24,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(25,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(26,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(27,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(28,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(29,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(30,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(31,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(32,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(33,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(34,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(35,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(36,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(37,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(38,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(39,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(40,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(41,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(42,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(43,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(44,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(45,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(46,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(47,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(48,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(49,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(50,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(51,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(52,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(53,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(54,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(55,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(56,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(57,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(58,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(59,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(60,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(61,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(62,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(63,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(64,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(65,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr[rd_cnt-40].header.version, p_sec_data_lgsr[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr[rd_cnt-40].header.base_weight, p_sec_data_lgsr[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(66,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_DFLT_SPRINT(rd_cnt=0,buffer,PE_INF_O22_PRINT_END);
				}
				if (rd_cnt==0)
				{
					if (p_h_top_lgsr)	{OS_Free(p_h_top_lgsr);}
					if (p_sec_data_lgsr)	{OS_Free(p_sec_data_lgsr);}
				}
			}
			else if (pstParams->data[0]==PE_INF_HW_O22_GINFO_O22F22_LGSR_DDR_H_PHYS || \
				pstParams->data[0]==PE_INF_HW_O22_GINFO_O22F22_LGSR_DDR_H_SHDW)
			{
				PE_LGSR_DDR_DB_SHDW_REG_O22F22_T *p_shdw_db = gPE_LGSR_DDR_DB_O22F22.shdw.data;
				UINT32 *p_s_base = NULL;
				UINT32 *p_s_size = NULL;
				UINT32 sec_typ;
				PE_LGSR_DDR_O22F22_HEADER_T *p_sec_h = NULL;
				if (rd_cnt==0)
				{
					ddr_total = 0;
					p_sec_data_lgsr_o22f22 = (PE_LGSR_DDR_O22F22_DATA_T *)OS_Malloc(sizeof(PE_LGSR_DDR_O22F22_DATA_T)*PE_DDR_O22F22_SEC_MAX_SIZE);
					CHECK_KNULL(p_sec_data_lgsr_o22f22);
					p_h_top_lgsr_o22f22 = (PE_LGSR_DDR_O22F22_TOP_HEADER_T *)OS_Malloc(sizeof(PE_LGSR_DDR_O22F22_TOP_HEADER_T));
					CHECK_KNULL(p_h_top_lgsr_o22f22);
					if (pstParams->data[0]==PE_INF_HW_O22_GINFO_O22F22_LGSR_DDR_H_PHYS)
					{
						PE_INF_O22F22_GetCurLgsrDdrTopHeader((void *)p_h_top_lgsr_o22f22);
						for (sec_typ=0; sec_typ<PE_LGSR_DDR_O22F22_SEC_NUM; sec_typ++)
						{
							p_sec_h = &(p_sec_data_lgsr_o22f22[sec_typ].header);
							PE_INF_O22F22_GetCurLgsrDdrSecHeader((void *)p_h_top_lgsr_o22f22, (void *)p_sec_h, sec_typ);
						}
					}
					else
					{
						memcpy(p_h_top_lgsr_o22f22, &(p_shdw_db->top_h), sizeof(PE_LGSR_DDR_O22F22_TOP_HEADER_T));
						for (sec_typ=0; sec_typ<PE_LGSR_DDR_O22F22_SEC_NUM; sec_typ++)
						{
							p_sec_data_lgsr_o22f22[sec_typ].header = p_shdw_db->sec_d[sec_typ].header;
						}
					}
					for (sec_typ=0; sec_typ<PE_LGSR_DDR_O22F22_SEC_NUM; sec_typ++)
					{
						p_sec_data_lgsr_o22f22[sec_typ].data_base = p_shdw_db->sec_d[sec_typ].data_base;
						ddr_total += p_h_top_lgsr_o22f22->sec_size[sec_typ];
					}
				}
				p_s_base = p_h_top_lgsr_o22f22->sec_base;
				p_s_size = p_h_top_lgsr_o22f22->sec_size;
				/* causion : p_s_base and p_s_size should sync with PE_DDR_O22F22_SEC_MAX_SIZE */
				switch(rd_cnt)
				{
					PE_INF_O22_CASE_SPRINT( 0,rd_cnt++,buffer,PE_INF_O22_PRINT_START);
					PE_INF_O22_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"[%02d]top_h     : ver:%08x b_a:%08x s_n:%08x total_size:%d\n", rd_cnt, \
						p_h_top_lgsr_o22f22->version, p_h_top_lgsr_o22f22->db_base, p_h_top_lgsr_o22f22->sec_num, ddr_total);
					PE_INF_O22_CASE_SPRINT( 3,rd_cnt++,buffer, \
						"[%02d]top_h base: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
						p_s_base[0], p_s_base[1], p_s_base[2], p_s_base[3], p_s_base[4]);
					PE_INF_O22_CASE_SPRINT( 4,rd_cnt++,buffer, \
						"[%02d]top_h size: [00]%08x [01]%08x [02]%08x [03]%08x [04]%08x\n", rd_cnt, \
						p_s_size[0], p_s_size[1], p_s_size[2], p_s_size[3], p_s_size[4]);
					PE_INF_O22_CASE_SPRINT( 5,rd_cnt++,buffer, \
						"[%02d]top_h base: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
						p_s_base[5], p_s_base[6], p_s_base[7], p_s_base[8], p_s_base[9]);
					PE_INF_O22_CASE_SPRINT( 6,rd_cnt++,buffer, \
						"[%02d]top_h size: [05]%08x [06]%08x [07]%08x [08]%08x [09]%08x\n", rd_cnt, \
						p_s_size[5], p_s_size[6], p_s_size[7], p_s_size[8], p_s_size[9]);
					PE_INF_O22_CASE_SPRINT( 7,rd_cnt++,buffer, \
						"[%02d]top_h base: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
						p_s_base[10], p_s_base[11], p_s_base[12], p_s_base[13], p_s_base[14]);
					PE_INF_O22_CASE_SPRINT( 8,rd_cnt++,buffer, \
						"[%02d]top_h size: [10]%08x [11]%08x [12]%08x [13]%08x [14]%08x\n", rd_cnt, \
						p_s_size[10], p_s_size[11], p_s_size[12], p_s_size[13], p_s_size[14]);
					PE_INF_O22_CASE_SPRINT( 9,rd_cnt++,buffer, \
						"[%02d]top_h base: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
						p_s_base[15], p_s_base[16], p_s_base[17], p_s_base[18], p_s_base[19]);
					PE_INF_O22_CASE_SPRINT(10,rd_cnt++,buffer, \
						"[%02d]top_h size: [15]%08x [16]%08x [17]%08x [18]%08x [19]%08x\n", rd_cnt, \
						p_s_size[15], p_s_size[16], p_s_size[17], p_s_size[18], p_s_size[19]);
					PE_INF_O22_CASE_SPRINT(11,rd_cnt++,buffer, \
						"[%02d]top_h base: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
						p_s_base[20], p_s_base[21], p_s_base[22], p_s_base[23], p_s_base[24]);
					PE_INF_O22_CASE_SPRINT(12,rd_cnt++,buffer, \
						"[%02d]top_h size: [20]%08x [21]%08x [22]%08x [23]%08x [24]%08x\n", rd_cnt, \
						p_s_size[20], p_s_size[21], p_s_size[22], p_s_size[23], p_s_size[24]);
					PE_INF_O22_CASE_SPRINT(13,rd_cnt++,buffer, \
						"[%02d]top_h base: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
						p_s_base[25], p_s_base[26], p_s_base[27], p_s_base[28], p_s_base[29]);
					PE_INF_O22_CASE_SPRINT(14,rd_cnt++,buffer, \
						"[%02d]top_h size: [25]%08x [26]%08x [27]%08x [28]%08x [29]%08x\n", rd_cnt, \
						p_s_size[25], p_s_size[26], p_s_size[27], p_s_size[28], p_s_size[29]);
					PE_INF_O22_CASE_SPRINT(15,rd_cnt++,buffer, \
						"[%02d]top_h base: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
						p_s_base[30], p_s_base[31], p_s_base[32], p_s_base[33], p_s_base[34]);
					PE_INF_O22_CASE_SPRINT(16,rd_cnt++,buffer, \
						"[%02d]top_h size: [30]%08x [31]%08x [32]%08x [33]%08x [34]%08x\n", rd_cnt, \
						p_s_size[30], p_s_size[31], p_s_size[32], p_s_size[33], p_s_size[34]);
					PE_INF_O22_CASE_SPRINT(17,rd_cnt++,buffer, \
						"[%02d]top_h base: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
						p_s_base[35], p_s_base[36], p_s_base[37], p_s_base[38], p_s_base[39]);
					PE_INF_O22_CASE_SPRINT(18,rd_cnt++,buffer, \
						"[%02d]top_h size: [35]%08x [36]%08x [37]%08x [38]%08x [39]%08x\n", rd_cnt, \
						p_s_size[35], p_s_size[36], p_s_size[37], p_s_size[38], p_s_size[39]);
					PE_INF_O22_CASE_SPRINT(19,rd_cnt++,buffer, \
						"[%02d]top_h base: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
						p_s_base[40], p_s_base[41], p_s_base[42], p_s_base[43], p_s_base[44]);
					PE_INF_O22_CASE_SPRINT(20,rd_cnt++,buffer, \
						"[%02d]top_h size: [40]%08x [41]%08x [42]%08x [43]%08x [44]%08x\n", rd_cnt, \
						p_s_size[40], p_s_size[41], p_s_size[42], p_s_size[43], p_s_size[44]);
					PE_INF_O22_CASE_SPRINT(21,rd_cnt++,buffer, \
						"[%02d]top_h base: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
						p_s_base[45], p_s_base[46], p_s_base[47], p_s_base[48], p_s_base[49]);
					PE_INF_O22_CASE_SPRINT(22,rd_cnt++,buffer, \
						"[%02d]top_h size: [45]%08x [46]%08x [47]%08x [48]%08x [49]%08x\n", rd_cnt, \
						p_s_size[45], p_s_size[46], p_s_size[47], p_s_size[48], p_s_size[49]);
					PE_INF_O22_CASE_SPRINT(23,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(24,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(25,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(26,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(27,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(28,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(29,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(30,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(31,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(32,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(33,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(34,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(35,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(36,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(37,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(38,rd_cnt++,buffer,PE_INF_O22_PRINT_RESERVED);
					PE_INF_O22_CASE_SPRINT(39,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_CASE_SPRINT(40,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(41,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(42,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(43,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(44,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(45,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(46,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(47,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(48,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(49,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(50,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(51,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(52,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(53,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(54,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(55,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(56,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(57,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(58,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(59,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(60,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(61,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(62,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(63,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(64,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(65,rd_cnt++,buffer, \
						"[%02d]%s: ver:%08x s_t:%08x b_a:%08x b_w:%08x d_b:%08x\n", rd_cnt, \
						PE_LGSR_DDR_REG_O22F22_SEC_TYPE_TO_STR(rd_cnt-40), \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.version, p_sec_data_lgsr_o22f22[rd_cnt-40].header.sec_type, \
						 p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_apb, \
						p_sec_data_lgsr_o22f22[rd_cnt-40].header.base_weight, p_sec_data_lgsr_o22f22[rd_cnt-40].data_base);
					PE_INF_O22_CASE_SPRINT(66,rd_cnt++,buffer,\
						"--------------------------------------------------------------------------------\n");
					PE_INF_O22_DFLT_SPRINT(rd_cnt=0,buffer,PE_INF_O22_PRINT_END);
				}
				if (rd_cnt==0)
				{
					if (p_h_top_lgsr_o22f22)	{OS_Free(p_h_top_lgsr_o22f22);}
					if (p_sec_data_lgsr_o22f22)	{OS_Free(p_sec_data_lgsr_o22f22);}
				}
			}
			#endif
			else
			{
				snprintf(buffer, PE_TRACE_STR_SIZE, PE_INF_O22_PRINT_EXIT);
				rd_cnt=0;
			}
			memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	if (win_set)	{OS_Free(win_set);}
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * set PathMonitor operation
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_INF_O22_SetPathMonitor(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	return ret;
}
/**
 * get PathMonitor operation
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_INF_O22_GetPathMonitor(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * get level info
 *
 * @param   *pstParams [in/out] LX_PE_INF_LEVEL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_GetLevelInfo(LX_PE_INF_LEVEL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O22)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				if(pstParams->sel&LX_PE_LEVEL_MOTION)
				{
					PE_ND0_O22_QRd01(tnr_status_00,w_gmv,pstParams->motion_level);//motion vector 
				}
			}
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_SetMiscTbl(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 max_num = 0;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O22)
		{
			max_num = sizeof(_g_pe_inf_o22_dbg_set_fn)/sizeof(PE_ETC_MISC_TBL_T);
			PE_INF_O22_CHECK_CODE(pstParams->func_num>=max_num, break, \
				"[%s,%d] invalid func_num[%d].\n", __F__, __L__, pstParams->func_num);
			CHECK_KNULL(_g_pe_inf_o22_dbg_set_fn[pstParams->func_num].func);
			ret = _g_pe_inf_o22_dbg_set_fn[pstParams->func_num].func(pstParams);
			PE_INF_O22_CHECK_CODE(ret, break, "[%s,%d] %s() error.\n", \
				__F__, __L__, _g_pe_inf_o22_dbg_set_fn[pstParams->func_num].fn_name);
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_GetMiscTbl(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 max_num = 0;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O22)
		{
			max_num = sizeof(_g_pe_inf_o22_dbg_get_fn)/sizeof(PE_ETC_MISC_TBL_T);
			PE_INF_O22_CHECK_CODE(pstParams->func_num>=max_num, break, \
				"[%s,%d] invalid func_num[%d].\n", __F__, __L__, pstParams->func_num);
			CHECK_KNULL(_g_pe_inf_o22_dbg_get_fn[pstParams->func_num].func);
			ret = _g_pe_inf_o22_dbg_get_fn[pstParams->func_num].func(pstParams);
			PE_INF_O22_CHECK_CODE(ret, break, "[%s,%d] %s() error.\n", \
				__F__, __L__, _g_pe_inf_o22_dbg_get_fn[pstParams->func_num].fn_name);
		}
		else
		{
			PE_INF_O22_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * sort trace data buf to dst buf
 * - ascending, bubble sorting
 *
 * @param   type [in] UINT32
 * @param   *dst [in/out] PE_INF_O22_DATA_BUF_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
static int PE_INF_O22_SortTraceDataBuf(UINT32 type, PE_INF_O22_DATA_BUF_T *dst)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 size=0, i=0, max=0;
	UINT32 j=0, s0=0, s1=0, us0=0, us1=0;
	PE_INF_O22_DATA_BUF_T temp;
	PE_INF_O22_DATA_BUF_T *src;

	do{
		CHECK_KNULL(dst);
		if (type == 3)			src = _g_pe_inf_o22_chpi1_buf;
		else if (type == 2)		src = _g_pe_inf_o22_chpi0_buf;
		else if (type == 1)		src = _g_pe_inf_o22_db_buf;
		else					src = _g_pe_inf_o22_buf;
		if (src == NULL)	{ret = RET_ERROR;	break;}
		max = PE_INF_O22_BUF_MAX;
		size = sizeof(PE_INF_O22_DATA_BUF_T);
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
	#endif /*PE_HW_O22_BRINGUP*/
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
static int PE_INF_O22_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0, type=0;
	PE_INF_O22_DATA_BUF_T *p_buf;
	UINT32 *p_data = NULL;
	PE_INF_O22_TIME_T *p_time = NULL;
	char *p_str = NULL;

#define PE_INF_O22_PRINT_RESERVED	"RESERVED"
#define PE_INF_O22_PRINT_END		"END_OF_PRINT"

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		type = pstParams->data[0];
		if (type == 3)			p_buf = _g_pe_inf_o22_chpi1_buf_temp;
		else if (type == 2)		p_buf = _g_pe_inf_o22_chpi0_buf_temp;
		else if (type == 1)		p_buf = _g_pe_inf_o22_db_buf_temp;
		else					p_buf = _g_pe_inf_o22_buf_temp;
		if (p_buf == NULL)	break;
		rd_cnt = pstParams->oper;
		if (rd_cnt<PE_INF_O22_BUF_MAX)
		{
			if(rd_cnt==0)
			{
				ret = PE_INF_O22_SortTraceDataBuf(type,p_buf);
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
				snprintf(buffer,PE_TRACE_STR_SIZE, "%s", PE_INF_O22_PRINT_RESERVED);
			}
			rd_cnt++;
		}
		else
		{
			snprintf(buffer, PE_TRACE_STR_SIZE,"%s", PE_INF_O22_PRINT_END);
			rd_cnt=0;
		}
		p_data = pstParams->data;
		memcpy(p_data, buffer, PE_TRACE_STR_SIZE);
	}while (0);
	#endif /*PE_HW_O22_BRINGUP*/
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
int PE_INF_O22_SetTraceDataBuf(UINT32 type, char *data)
{
    int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 i = 0;
	char *p_str = NULL;
	PE_INF_O22_TIME_T *p_time = NULL;
	static UINT32 cnt = 0;
	PE_INF_O22_DATA_BUF_T *p_buf;
	do{
		CHECK_KNULL(data);
		if (type == 3)			p_buf = _g_pe_inf_o22_chpi1_buf;
		else if (type == 2)		p_buf = _g_pe_inf_o22_chpi0_buf;
		else if (type == 1)		p_buf = _g_pe_inf_o22_db_buf;
		else					p_buf = _g_pe_inf_o22_buf;
		if (p_buf == NULL)	{ret = RET_ERROR;	break;}
		if(cnt>=PE_INF_O22_BUF_MAX)	cnt = 0;
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
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}

/**
 * set led pixel value
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_INF_O22_SetPixelRead(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		if (PE_KDRV_VER_O22)
		{
			switch (pstParams->data[0])
			{
				case PE_INF_HW_O22_RD_PXL_WCP_HOR_POS:
					PE_VCP_DISP_O22_QWr01(vcp_wcp_m_pixel_read_ctrl,rd_pel_pos_x,pstParams->data[1]);
					break;
				case PE_INF_HW_O22_RD_PXL_WCP_VER_POS:
					PE_VCP_DISP_O22_QWr01(vcp_wcp_m_pixel_read_ctrl,rd_pel_pos_y,pstParams->data[1]);
					break;
				case PE_INF_HW_O22_RD_PXL_WCP_MARK_EN:
					PE_VCP_DISP_O22_QWr01(vcp_wcp_m_pixel_read_ctrl,rd_pel_pat_en,pstParams->data[1]);
					break;
				case PE_INF_HW_O22_RD_PXL_LED_HOR_POS:
					PE_LED_RP_O22_QWr01(ad_rp_hv_pos,rp_h_pos,pstParams->data[1]);
					break;
				case PE_INF_HW_O22_RD_PXL_LED_VER_POS:
					PE_LED_RP_O22_QWr01(ad_rp_hv_pos,rp_v_pos,pstParams->data[1]);
					break;
				case PE_INF_HW_O22_RD_PXL_LED_MARK_EN:
					PE_LED_RP_O22_QWr01(ad_rp_make_en,mark_en,pstParams->data[1]);
					break;
				default:
					break;
			}
		}
	}while (0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * get led pixel value
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_INF_O22_GetPixelRead(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0;
	UINT32 rd_data[15];

#define PE_INF_O22_RD_NO_PRINT			0
#define PE_INF_O22_RD_PRINT_START		"START_OF_PRINT"
#define PE_INF_O22_RD_PRINT_END			"END_OF_PRINT"
#define PE_INF_O22_RD_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_INF_O22_RD_PRINT_RESERV		"RESERVED"
#define PE_INF_O22_RD_CASE_PRMENU(_cnt, _action, _buf, _item, _val)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE,"   [0x%02x] %s: %d\n", (_item), #_item, (_val));_action;break
#define PE_INF_O22_RD_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE,fmt, ##args);_action;break
#define PE_INF_O22_RD_DFLT_SPRINT(_action,_buf,fmt,args...)		\
	default:snprintf(_buf,PE_TRACE_STR_SIZE,fmt,##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		if (PE_KDRV_VER_O22)
		{
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]==PE_INF_HW_O22_RD_PXL_DISPLAY)
			{
				PE_VCP_DISP_O22_QRd03(vcp_wcp_m_pixel_read_ctrl,rd_pel_pos_x,rd_data[0],\
                                                                  rd_pel_pos_y,rd_data[1],\
                                                                  rd_pel_pat_en,rd_data[2]);
				PE_VCP_DISP_O22_QRd03(vcp_wcp_m_pixel_read_data_0,msb8_rd_pel_y,rd_data[3],\
                                                                  msb8_rd_pel_cb,rd_data[4],\
                                                                  msb8_rd_pel_cr,rd_data[5]);
				PE_VCP_DISP_O22_QRd03(vcp_wcp_m_pixel_read_data_1,msb8_rd_pel_y,rd_data[6],\
                                                                  msb8_rd_pel_cb,rd_data[7],\
                                                                  msb8_rd_pel_cr,rd_data[8]);
				PE_LED_RP_O22_QRd02(ad_rp_hv_pos,rp_h_pos,rd_data[9],rp_v_pos,rd_data[10]);
				PE_LED_RP_O22_QRd01(ad_rp_make_en,mark_en,rd_data[11]);
				PE_LED_RP_O22_QRd01(ad_rp_r_value,rd_pixel_r,rd_data[12]);
				PE_LED_RP_O22_QRd01(ad_rp_g_value,rd_pixel_g,rd_data[13]);
				PE_LED_RP_O22_QRd01(ad_rp_b_value,rd_pixel_b,rd_data[14]);
				switch (rd_cnt)
				{
					PE_INF_O22_RD_CASE_SPRINT( 0, rd_cnt++, buffer, PE_INF_O22_RD_PRINT_START);
					PE_INF_O22_RD_CASE_SPRINT( 1, rd_cnt++, buffer, "   * get pixel value *\n");
					PE_INF_O22_RD_CASE_PRMENU( 2, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_HOR_POS, rd_data[0]);
					PE_INF_O22_RD_CASE_PRMENU( 3, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_VER_POS, rd_data[1]);
					PE_INF_O22_RD_CASE_PRMENU( 4, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_MARK_EN, rd_data[2]);
					PE_INF_O22_RD_CASE_PRMENU( 5, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_PXL_E_Y, rd_data[3]);
					PE_INF_O22_RD_CASE_PRMENU( 6, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_PXL_E_B, rd_data[4]);
					PE_INF_O22_RD_CASE_PRMENU( 7, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_PXL_E_R, rd_data[5]);
					PE_INF_O22_RD_CASE_PRMENU( 8, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_PXL_O_Y, rd_data[6]);
					PE_INF_O22_RD_CASE_PRMENU( 9, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_PXL_O_B, rd_data[7]);
					PE_INF_O22_RD_CASE_PRMENU(10, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_WCP_PXL_O_R, rd_data[8]);
					PE_INF_O22_RD_CASE_PRMENU(11, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_LED_HOR_POS, rd_data[9]);
					PE_INF_O22_RD_CASE_PRMENU(12, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_LED_VER_POS, rd_data[10]);
					PE_INF_O22_RD_CASE_PRMENU(13, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_LED_MARK_EN, rd_data[11]);
					PE_INF_O22_RD_CASE_PRMENU(14, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_LED_PIXEL_R, rd_data[12]);
					PE_INF_O22_RD_CASE_PRMENU(15, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_LED_PIXEL_G, rd_data[13]);
					PE_INF_O22_RD_CASE_PRMENU(16, rd_cnt++, buffer, PE_INF_HW_O22_RD_PXL_LED_PIXEL_B, rd_data[14]);
					PE_INF_O22_RD_CASE_SPRINT(17, rd_cnt++, buffer, PE_INF_O22_RD_PRINT_RESERV);
					PE_INF_O22_RD_CASE_SPRINT(18, rd_cnt++, buffer, PE_INF_O22_RD_PRINT_RESERV);
					PE_INF_O22_RD_DFLT_SPRINT(rd_cnt=0, buffer, PE_INF_O22_RD_PRINT_END);
				}
			}
			else
			{
				snprintf(buffer, PE_TRACE_STR_SIZE,PE_INF_O22_RD_PRINT_EXIT);
				rd_cnt=0;
			}
			memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
		}
		else
		{
			snprintf(buffer, PE_TRACE_STR_SIZE,PE_INF_O22_RD_PRINT_EXIT);
			memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
		}
	}while (0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}

/**
 * get current ddr top header.
 *
 * @param   *pstParams [in/out] void, see PE_DDR_O22_TOP_HEADER_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_GetCurDdrTopHeader(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 i, base, size;
	volatile PE_DDR_O22_TOP_HEADER_T *p_top  = NULL;
	PE_DDR_O22_TOP_HEADER_T *p_dst  = NULL;
	PE_DDR_DB_SHDW_REG_O22_T *p_shdw_db = gPE_DDR_DB_O22.shdw.data;
	do {
		CHECK_KNULL(pstParams);
		base = p_shdw_db->top_h.db_base;
		size = sizeof(PE_DDR_O22_TOP_HEADER_T);
		if (!base||!size)	break;
		p_top = (volatile PE_DDR_O22_TOP_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_top);
		p_dst = (PE_DDR_O22_TOP_HEADER_T *)pstParams;
		p_dst->version = p_top->version;
		p_dst->db_base = p_top->db_base;
		p_dst->sec_num = p_top->sec_num;
		for (i=0; i<PE_DDR_O22_SEC_MAX_SIZE; i++)
		{
			p_dst->sec_base[i] = p_top->sec_base[i];
			p_dst->sec_size[i] = p_top->sec_size[i];
		}
	}while(0);
	if (p_top) vunmap_phys((void *)p_top);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * get current ddr section header.
 *
 * @param   *top_h [in] void, see PE_DDR_O22_TOP_HEADER_T
 * @param   *pstParams [in/out] void, see PE_DDR_O22_HEADER_T
 * @param   sec_type [in] UINT32, see PE_DDR_O22_SEC_TYPE
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_GetCurDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 base, size;
	PE_DDR_O22_TOP_HEADER_T *p_top = NULL;
	PE_DDR_O22_HEADER_T *p_dst = NULL;
	volatile PE_DDR_O22_HEADER_T *p_sec  = NULL;
	do {
		CHECK_KNULL(top_h);
		CHECK_KNULL(pstParams);
		PE_INF_O22_CHECK_CODE(sec_type>=PE_DDR_O22_SEC_NUM,break,\
			"[%s,%d] sec_type(%d) is over.\n", __F__, __L__, sec_type);
		p_top = (PE_DDR_O22_TOP_HEADER_T *)top_h;
		base = p_top->sec_base[sec_type];
		size = sizeof(PE_DDR_O22_HEADER_T);
		if (!base || !size)	break;
		p_sec  = (volatile PE_DDR_O22_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_sec);
		p_dst = (PE_DDR_O22_HEADER_T *)pstParams;
		p_dst->version = p_sec->version;
		p_dst->sec_type = p_sec->sec_type;
		p_dst->item_num = p_sec->item_num;
		p_dst->item_size = p_sec->item_size;
	}while(0);
	if (p_sec) vunmap_phys((void *)p_sec);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * get current ddr top header.
 *
 * @param   *pstParams [in/out] void, see PE_DDR_O22_TOP_HEADER_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_GetCurLgsrDdrTopHeader(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	UINT32 i, base, size;
	volatile PE_LGSR_DDR_O22_TOP_HEADER_T *p_top  = NULL;
	PE_LGSR_DDR_O22_TOP_HEADER_T *p_dst  = NULL;
	PE_LGSR_DDR_DB_SHDW_REG_O22_T *p_shdw_db = gPE_LGSR_DDR_DB_O22.shdw.data;
	do {
		CHECK_KNULL(pstParams);
		base = p_shdw_db->top_h.db_base;
		size = sizeof(PE_LGSR_DDR_O22_TOP_HEADER_T);
		if (!base||!size)	break;
		p_top = (volatile PE_LGSR_DDR_O22_TOP_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_top);
		p_dst = (PE_LGSR_DDR_O22_TOP_HEADER_T *)pstParams;
		p_dst->version = p_top->version;
		p_dst->db_base = p_top->db_base;
		p_dst->sec_num = p_top->sec_num;
		for (i=0; i<PE_DDR_O22_SEC_MAX_SIZE; i++)
		{
			p_dst->sec_base[i] = p_top->sec_base[i];
			p_dst->sec_size[i] = p_top->sec_size[i];
		}
	}while(0);
	if (p_top) vunmap_phys((void *)p_top);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * get current ddr section header.
 *
 * @param   *top_h [in] void, see PE_DDR_O22_TOP_HEADER_T
 * @param   *pstParams [in/out] void, see PE_DDR_O22_HEADER_T
 * @param   sec_type [in] UINT32, see PE_DDR_O22_SEC_TYPE
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22_GetCurLgsrDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	UINT32 base, size;
	PE_LGSR_DDR_O22_TOP_HEADER_T *p_top = NULL;
	PE_LGSR_DDR_O22_HEADER_T *p_dst = NULL;
	volatile PE_LGSR_DDR_O22_HEADER_T *p_sec  = NULL;
	do {
		CHECK_KNULL(top_h);
		CHECK_KNULL(pstParams);
		PE_INF_O22_CHECK_CODE(sec_type>=PE_DDR_O22_SEC_NUM,break,\
			"[%s,%d] sec_type(%d) is over.\n", __F__, __L__, sec_type);
		p_top = (PE_LGSR_DDR_O22_TOP_HEADER_T *)top_h;
		base = p_top->sec_base[sec_type];
		size = sizeof(PE_LGSR_DDR_O22_HEADER_T);
		if (!base || !size)	break;
		p_sec  = (volatile PE_LGSR_DDR_O22_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_sec);
		p_dst = (PE_LGSR_DDR_O22_HEADER_T *)pstParams;
		p_dst->version = p_sec->version;
		p_dst->sec_type = p_sec->sec_type;
		p_dst->base_apb= p_sec->base_apb;
		p_dst->base_weight= p_sec->base_weight;
	}while(0);
	if (p_sec) vunmap_phys((void *)p_sec);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}


/**
 * set trace packet data
 *
 * @param   *pstParams [in] LX_PE_PKT_T int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_INF_O22_SetTracePacketData(LX_PE_PKT_T *pstParams)
{
    int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	char str[PE_TRACE_STR_SIZE];
	UINT32 rw_t=0, mdl_t=0, fn_t=0, valid=0, d_size=0;
	UINT32 *d_arg = NULL;

#define PE_INF_O22_CPY_PARAM_TO_STR(_struct, _fmt, _args...)	\
	{\
		_struct p;\
		ret = copy_from_user(&p, (void __user *)d_arg, d_size);\
		PE_INF_O22_CHECK_CODE(ret, break, "copy_from_user error.\n");\
		snprintf(str,PE_TRACE_STR_SIZE, "[%s]"_fmt, #_struct, ##_args);\
		valid = 1;\
	}

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		rw_t = PE_GET_PKTINFO_RWTYPE(pstParams->info);
		mdl_t = PE_GET_PKTINFO_MODLTYPE(pstParams->info);
		fn_t = PE_GET_PKTINFO_FUNCTYPE(pstParams->info);
		d_arg = pstParams->data;
		d_size = pstParams->size;
		switch (rw_t)
		{
			case PE_ITEM_PKTRW(INIT):
				PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_INIT_SETTINS_T, \
					"%d, %d", p.win_id, p.suspend_mode);
				break;
			case PE_ITEM_PKTRW(SET):
				switch (mdl_t)
				{
					case PE_ITEM_PKTMODL(DEFAULT):
						PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_DEFAULT_SETTINGS_T, \
							"%d", p.win_id);
						break;
					case PE_ITEM_PKTMODL(CMN):
						switch (fn_t)
						{
							#ifdef PE_INF_O22_DETAIL_TRACE_LOG
							case PE_ITEM_PKTFUNC(LX_PE_CMN_CONTRAST_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CMN_CONTRAST_T, \
									"%d, %d", p.win_id, p.contrast);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CMN_BRIGHTNESS_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CMN_BRIGHTNESS_T, \
									"%d, %d", p.win_id, p.brightness);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CMN_SATURATION_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CMN_SATURATION_T, \
									"%d, %d", p.win_id, p.saturation);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CMN_HUE_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CMN_HUE_T, \
									"%d, %d", p.win_id, p.hue);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CMN_LEVEL_CTRL_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CMN_LEVEL_CTRL_T, \
									"%d, %d,%d,%d,%d", p.win_id, \
									p.offset, p.center, p.gain, p.tp_on);
								break;
							#else
							case PE_ITEM_PKTFUNC(LX_PE_CMN_CONTRAST_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMN_BRIGHTNESS_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMN_SATURATION_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMN_HUE_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMN_LEVEL_CTRL_T):
							#endif
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(CSC):
						switch (fn_t)
						{
							case PE_ITEM_PKTFUNC(LX_PE_CSC_POST_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CSC_POST_T, \
									"%d, %x,%x,%x,%x,%x,%x,%x,%x,%x, "\
									"%d,%d,%d,%d,%d,%d", p.win_id, \
									p.matrix[0], p.matrix[1], p.matrix[2], \
									p.matrix[3], p.matrix[4], p.matrix[5], \
									p.matrix[6], p.matrix[7], p.matrix[8], \
									(SINT16)p.offset[0], (SINT16)p.offset[1], \
									(SINT16)p.offset[2], (SINT16)p.offset[3], \
									(SINT16)p.offset[4], (SINT16)p.offset[5]);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CSC_INPUT_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CSC_INPUT_T, \
									"%d, %d, %x,%x,%x,%x,%x,%x,%x,%x,%x, "\
									"%d,%d,%d,%d,%d,%d", p.win_id, p.enable, \
									p.matrix[0], p.matrix[1], p.matrix[2], \
									p.matrix[3], p.matrix[4], p.matrix[5], \
									p.matrix[6], p.matrix[7], p.matrix[8], \
									(SINT16)p.offset[0], (SINT16)p.offset[1], \
									(SINT16)p.offset[2], (SINT16)p.offset[3], \
									(SINT16)p.offset[4], (SINT16)p.offset[5]);
								break;
							#ifdef PE_INF_O22_DETAIL_TRACE_LOG
							case PE_ITEM_PKTFUNC(LX_PE_CSC_XVYCC_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CSC_XVYCC_T, \
									"%d, %d,%d", p.win_id, p.enable, p.scaler);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CSC_GAMUT_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CSC_GAMUT_T, \
									"%d, %x,%x,%x,%x,%x,%x,%x,%x,%x", p.win_id, \
									p.matrix[0], p.matrix[1], p.matrix[2], \
									p.matrix[3], p.matrix[4], p.matrix[5], \
									p.matrix[6], p.matrix[7], p.matrix[8]);
								break;
							#else
							case PE_ITEM_PKTFUNC(LX_PE_CSC_XVYCC_T):
							case PE_ITEM_PKTFUNC(LX_PE_CSC_GAMUT_T):
							#endif
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(CMG):
						switch (fn_t)
						{
							#ifdef PE_INF_O22_DETAIL_TRACE_LOG
							case PE_ITEM_PKTFUNC(LX_PE_CMG_ENABLE_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CMG_ENABLE_T, \
									"%d, %d", p.win_id, p.enable);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CMG_GLOBAL_CTRL_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CMG_GLOBAL_CTRL_T, \
									"%d, %d,%d,%d,%d,%d,%d", p.win_id, \
									p.global_delta[0], p.global_delta[1], \
									p.global_delta[2], p.global_delta[3], \
									p.global_delta[4], p.global_delta[5]);
								break;
							#else
							case PE_ITEM_PKTFUNC(LX_PE_CMG_ENABLE_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMG_GLOBAL_CTRL_T):
							#endif
							case PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_ENABLE_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_CTRL_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMG_COLOR_CTRL_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMG_CW_CTRL_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMG_CW_GAIN_CTRL_T):
							case PE_ITEM_PKTFUNC(LX_PE_CMG_SAT_GAIN_LUT_T):
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(NRD):
						switch (fn_t)
						{
							#ifdef PE_INF_O22_DETAIL_TRACE_LOG
							case PE_ITEM_PKTFUNC(LX_PE_NRD_DNR2_DETAIL_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_NRD_DNR2_DETAIL_T, \
									"%d", p.win_id);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2_CMN_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_NRD_TNR2_CMN_T, \
									"%d, %d,%d,%d,%d,%d", p.win_id, \
									p.auto_mode_en, p.adjust_nt_lvl, \
									p.adjust_nt_lvl_val, p.y_gain, p.c_gain);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2_DETAIL_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_NRD_TNR2_DETAIL_T, \
									"%d", p.win_id);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_NRD_DNR4_CMN_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_NRD_DNR4_CMN_T, \
									"%d, %d,%d,%d", p.win_id, \
									p.enable_ac_bnr, p.enable_mnr, p.enable_dc_bnr);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_NRD_DNR4_DETAIL_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_NRD_DNR4_DETAIL_T, \
									"%d", p.win_id);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR4_CMN_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_NRD_TNR4_CMN_T, \
									"%d, %d,%d,%d,%d,%d", p.win_id, \
									p.auto_mode_en, p.adjust_nt_lvl, \
									p.adjust_nt_lvl_val, p.y_gain, p.c_gain);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR4_DETAIL_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_NRD_TNR4_DETAIL_T, \
									"%d", p.win_id);
								break;
							#endif
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(DNT):
						switch (fn_t)
						{
							case PE_ITEM_PKTFUNC(LX_PE_DNT_FILMMODE_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_DNT_FILMMODE_T, \
									"%d, %d", p.win_id, p.enable);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_DNT_LD_MODE_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_DNT_LD_MODE_T, \
									"%d, %d", p.win_id, p.enable);
								break;
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(SHP):
						switch (fn_t)
						{
							#ifdef PE_INF_O22_DETAIL_TRACE_LOG
							case PE_ITEM_PKTFUNC(LX_PE_SHP_EE1_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_SHP_EE1_T, \
									"%d, %d,%d,%d,%d", p.win_id, \
									p.mp_edge_gain_b, p.mp_edge_gain_w, \
									p.sp_edge_gain_b, p.sp_edge_gain_w);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_SHP_DE1_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_SHP_DE1_T, \
									"%d, %d,%d,%d,%d", p.win_id, \
									p.mp_texture_gain_b, p.mp_texture_gain_w, \
									p.sp_texture_gain_b, p.sp_texture_gain_w);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE3_CMN_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_SHP_RE3_CMN_T, \
									"%d", p.win_id);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_HOR_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_SHP_RE3_HOR_T, \
									"%d", p.win_id);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_VER_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_SHP_RE3_VER_T, \
									"%d", p.win_id);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_MISC_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_SHP_RE3_MISC_T, \
									"%d", p.win_id);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE3_MISC_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_SHP_RE3_MISC_T, \
									"%d", p.win_id);
								break;
							#else
							case PE_ITEM_PKTFUNC(LX_PE_SHP_EE1_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_DE1_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_CMN_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_HOR_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_VER_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_MISC_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE3_MISC_T):
							#endif
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_CMN_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_HOR_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_VER_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_MISC_T):
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(CCM):
						switch (fn_t)
						{
							case PE_ITEM_PKTFUNC(LX_PE_CCM_AUTO_CR_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CCM_AUTO_CR_T, \
									"%d,%d,%d,%d,%d", p.enable, p.th_max_hist, \
									p.th_valid_bins, p.adj_th0, p.adj_th1);
								break;
							#ifdef PE_INF_O22_DETAIL_TRACE_LOG
							case PE_ITEM_PKTFUNC(LX_PE_CCM_GAMMALUT_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CCM_GAMMALUT_T, \
									"%d, %d", p.win_id, p.size);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CCM_PIXEL_REPLACE_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CCM_PIXEL_REPLACE_T, \
									"%d, %d,%d,%d", p.win_id, \
									p.pxl_rep_r, p.pxl_rep_g, p.pxl_rep_b);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_CCM_WB_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_CCM_WB_T, \
									"%d, %d,%d,%d, %d,%d,%d", p.win_id, \
									p.r_gain, p.g_gain, p.b_gain, \
									p.r_offset, p.g_offset, p.b_offset);
								break;
							#else
							case PE_ITEM_PKTFUNC(LX_PE_CCM_GAMMALUT_T):
							case PE_ITEM_PKTFUNC(LX_PE_CCM_PIXEL_REPLACE_T):
							case PE_ITEM_PKTFUNC(LX_PE_CCM_WB_T):
							#endif
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(DCM):
						switch (fn_t)
						{
							#ifdef PE_INF_O22_DETAIL_TRACE_LOG
							case PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_CONF_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_DCM_DCE_CONF_T, \
									"%d, %d,%d,%d", p.win_id, \
									p.domain, p.min_pos, p.max_pos);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_DCM_BLENDING_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_DCM_BLENDING_T, \
									"%d, %d,0x%x", p.win_id, \
									p.color_out_gain, p.region_sel);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_SMOOTH0_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_DCM_DCE_SMOOTH0_T, \
									"%d", p.win_id);
								break;
							case PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_SMOOTH1_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_DCM_DCE_SMOOTH1_T, \
									"%d", p.win_id);
								break;
							#else
							case PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_CONF_T):
							case PE_ITEM_PKTFUNC(LX_PE_DCM_BLENDING_T):
							case PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_SMOOTH0_T):
							case PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_SMOOTH1_T):
							#endif
							case PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_LUT_T):
							case PE_ITEM_PKTFUNC(LX_PE_DCM_DSE_LUT_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_VER_T):
							case PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_MISC_T):
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(HST):
						switch (fn_t)
						{
							#ifdef PE_INF_O22_DETAIL_TRACE_LOG
							case PE_ITEM_PKTFUNC(LX_PE_HST_HISTO_CFG_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_HST_HISTO_CFG_T, \
									"%d, %d,%d,%d", p.win_id, p.opr.src_apl_op, \
									p.opr.src_hist_op, p.opr.lrc_hist_op);
								break;
							#else
							case PE_ITEM_PKTFUNC(LX_PE_HST_HISTO_CFG_T):
							#endif
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(ETC):
						switch (fn_t)
						{
							case PE_ITEM_PKTFUNC(LX_PE_INF_DISPLAY_T):
								PE_INF_O22_CPY_PARAM_TO_STR(LX_PE_INF_DISPLAY_T, \
									"%d,sr,f,sc:%d,%d,%d,chsdh:%d,%d,%d,%d,%d,"\
									"fr:%d(%d),hv:%d,%d,ae:%d,ol:%d", \
									p.win_id, p.src_type, p.fmt_type, p.scan_type, p.cstd_type, \
									p.hdmi_type, p.scart_type, p.dtv_type,  p.hdd_type, \
									p.fr_type, p.in_f_rate, p.in_h_size, \
									p.in_v_size, p.act_fmt, p.mode.is_oled);
								break;
							default:
								break;
						}
						break;
					case PE_ITEM_PKTMODL(INIT):
					case PE_ITEM_PKTMODL(DBG):
					case PE_ITEM_PKTMODL(WIN):
					default:
						break;
				}
				break;
			case PE_ITEM_PKTRW(GET):
			default:
				break;
		}
		if (valid)
		{
			PE_INF_HW_O22_BACKUP_TRACE("%s",str);
		}
	}while (0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}

/**
 * get current ddr top header.
 *
 * @param   *pstParams [in/out] void, see PE_DDR_O22F22_TOP_HEADER_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22F22_GetCurDdrTopHeader(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 i, base, size;
	volatile PE_DDR_O22F22_TOP_HEADER_T *p_top  = NULL;
	PE_DDR_O22F22_TOP_HEADER_T *p_dst  = NULL;
	PE_DDR_DB_SHDW_REG_O22F22_T *p_shdw_db = gPE_DDR_DB_O22F22.shdw.data;
	do {
		CHECK_KNULL(pstParams);
		base = p_shdw_db->top_h.db_base;
		size = sizeof(PE_DDR_O22F22_TOP_HEADER_T);
		if (!base||!size)	break;
		p_top = (volatile PE_DDR_O22F22_TOP_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_top);
		p_dst = (PE_DDR_O22F22_TOP_HEADER_T *)pstParams;
		p_dst->version = p_top->version;
		p_dst->db_base = p_top->db_base;
		p_dst->sec_num = p_top->sec_num;
		for (i=0; i<PE_DDR_O22F22_SEC_MAX_SIZE; i++)
		{
			p_dst->sec_base[i] = p_top->sec_base[i];
			p_dst->sec_size[i] = p_top->sec_size[i];
		}
	}while(0);
	if (p_top) vunmap_phys((void *)p_top);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * get current ddr section header.
 *
 * @param   *top_h [in] void, see PE_DDR_O22F22_TOP_HEADER_T
 * @param   *pstParams [in/out] void, see PE_DDR_O22F22_HEADER_T
 * @param   sec_type [in] UINT32, see PE_DDR_O22F22_SEC_TYPE
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22F22_GetCurDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 base, size;
	PE_DDR_O22F22_TOP_HEADER_T *p_top = NULL;
	PE_DDR_O22F22_HEADER_T *p_dst = NULL;
	volatile PE_DDR_O22F22_HEADER_T *p_sec  = NULL;
	do {
		CHECK_KNULL(top_h);
		CHECK_KNULL(pstParams);
		PE_INF_O22_CHECK_CODE(sec_type>=PE_DDR_O22F22_SEC_NUM,break,\
			"[%s,%d] sec_type(%d) is over.\n", __F__, __L__, sec_type);
		p_top = (PE_DDR_O22F22_TOP_HEADER_T *)top_h;
		base = p_top->sec_base[sec_type];
		size = sizeof(PE_DDR_O22F22_HEADER_T);
		if (!base || !size)	break;
		p_sec  = (volatile PE_DDR_O22F22_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_sec);
		p_dst = (PE_DDR_O22F22_HEADER_T *)pstParams;
		p_dst->version = p_sec->version;
		p_dst->sec_type = p_sec->sec_type;
		p_dst->item_num = p_sec->item_num;
		p_dst->item_size = p_sec->item_size;
	}while(0);
	if (p_sec) vunmap_phys((void *)p_sec);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}

/**
 * get current ddr top header.
 *
 * @param   *pstParams [in/out] void, see PE_DDR_O22F22_TOP_HEADER_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22F22_GetCurLgsrDdrTopHeader(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	UINT32 i, base, size;
	volatile PE_LGSR_DDR_O22F22_TOP_HEADER_T *p_top  = NULL;
	PE_LGSR_DDR_O22F22_TOP_HEADER_T *p_dst  = NULL;
	PE_LGSR_DDR_DB_SHDW_REG_O22F22_T *p_shdw_db = gPE_LGSR_DDR_DB_O22F22.shdw.data;
	do {
		CHECK_KNULL(pstParams);
		base = p_shdw_db->top_h.db_base;
		size = sizeof(PE_LGSR_DDR_O22F22_TOP_HEADER_T);
		if (!base||!size)	break;
		p_top = (volatile PE_LGSR_DDR_O22F22_TOP_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_top);
		p_dst = (PE_LGSR_DDR_O22F22_TOP_HEADER_T *)pstParams;
		p_dst->version = p_top->version;
		p_dst->db_base = p_top->db_base;
		p_dst->sec_num = p_top->sec_num;
		for (i=0; i<PE_DDR_O22F22_SEC_MAX_SIZE; i++)
		{
			p_dst->sec_base[i] = p_top->sec_base[i];
			p_dst->sec_size[i] = p_top->sec_size[i];
		}
	}while(0);
	if (p_top) vunmap_phys((void *)p_top);
	#endif /*PE_HW_O22F22_BRINGUP*/
	return ret;
}
/**
 * get current ddr section header.
 *
 * @param   *top_h [in] void, see PE_DDR_O22F22_TOP_HEADER_T
 * @param   *pstParams [in/out] void, see PE_DDR_O22F22_HEADER_T
 * @param   sec_type [in] UINT32, see PE_DDR_O22F22_SEC_TYPE
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_O22F22_GetCurLgsrDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type)
{
	int ret = RET_OK;
	#ifdef PE_HW_O22_BRINGUP
	UINT32 base, size;
	PE_LGSR_DDR_O22F22_TOP_HEADER_T *p_top = NULL;
	PE_LGSR_DDR_O22F22_HEADER_T *p_dst = NULL;
	volatile PE_LGSR_DDR_O22F22_HEADER_T *p_sec  = NULL;
	do {
		CHECK_KNULL(top_h);
		CHECK_KNULL(pstParams);
		PE_INF_O22_CHECK_CODE(sec_type>=PE_DDR_O22F22_SEC_NUM,break,\
			"[%s,%d] sec_type(%d) is over.\n", __F__, __L__, sec_type);
		p_top = (PE_LGSR_DDR_O22F22_TOP_HEADER_T *)top_h;
		base = p_top->sec_base[sec_type];
		size = sizeof(PE_LGSR_DDR_O22F22_HEADER_T);
		if (!base || !size)	break;
		p_sec  = (volatile PE_LGSR_DDR_O22F22_HEADER_T *)vmap_phys(base, size);
		CHECK_KNULL(p_sec);
		p_dst = (PE_LGSR_DDR_O22F22_HEADER_T *)pstParams;
		p_dst->version = p_sec->version;
		p_dst->sec_type = p_sec->sec_type;
		p_dst->base_apb= p_sec->base_apb;
		p_dst->base_weight= p_sec->base_weight;
	}while(0);
	if (p_sec) vunmap_phys((void *)p_sec);
	#endif /*PE_HW_O22F22_BRINGUP*/
	return ret;
}

int PE_INF_O22_GetStatus(UINT32 *p_data, UINT32 count)
{
	if (!p_data)	return -1;
	if (count<3)	return -1;

	PE_ND0_O22_QRd02(tnr_status_01,w_apl_motion,p_data[0],w_apl_var,p_data[1]);
	PE_CC_PE1_O22_QRd01(pe1_fsw_ctrl_00,reg_s_status_0,p_data[2]);

	return 0;
}

