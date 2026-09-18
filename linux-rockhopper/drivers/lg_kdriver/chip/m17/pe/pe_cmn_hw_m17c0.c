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

/** @file pe_cmn_hw_m17c0.c
 *
 *  driver for picture enhance common functions. ( used only within kdriver )
 *	
 *	@author			Seung-Jun,Youm(sj.youm@lge.com)
 *  @modifier		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *	@version		0.1
 *	@note
 *	@date			2012.04.12
 *  @modified date  2015.05.24 for SWMD
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

#include "be_cfg.h"
#include "pe_hw_m17c0.h"
#include "pe_reg_m17.h"
#include "pe_fwi_m17c0.h"
#include "pe_cmn_hw_m17c0.h"
#include "pe_dcm_hw_m17c0.h"
#include "pe_shp_hw_m17c0.h"
#include "pe_nrd_hw_m17c0.h"
#include "pe_hst_hw_m17c0.h"
#include "cvd_module.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* Enabling this macro will DISABLE LGSI code refactoring changes, so enable only if there is
any issue in LGSI refactored code. This provision is only for cross checking with original
source. It can be removed in the next version of the code*/

/* use vgain, voffset instead of lvctrl, when tnr,sc mem share mode */
#undef PE_CMN_HW_M17C0_USE_VGAIN_FOR_LVCTRL
/* use lvctrl of IMX instead of ND0 */
#define PE_CMN_HW_M17C0_USE_LVCTRL_OF_IMX

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMN_HW_M17C0_ERROR	printk
#define PE_CMN_HW_M17C0_DBG_PRINT(fmt,args...)	\
	if(_g_cmn_hw_m17c0_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CMN_HW_M17C0_CHECK_CODE(_checker,_action,fmt,args...)	\
	if(_checker){PE_CMN_HW_M17C0_ERROR(fmt,##args);_action;}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

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
static int PE_CMN_HW_M17C0_DownloadModeDb(void);
static int PE_CMN_HW_M17C0_DownloadCvdDb(void);
static void PE_CMN_HW_M17C0_Get3DModeInternalFRC( LX_PE_INF_DISPLAY_T *i_pstDispInfo,
												UINT32 				*o_ui32PE1Mode3D );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_cmn_hw_m17c0_trace=0x0;		//default should be off.
static PE_CMN_HW_M17C0_SETTINGS_T _g_pe_cmn_hw_m17c0_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init cmn
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		memset(&_g_pe_cmn_hw_m17c0_info, 0, sizeof(PE_CMN_HW_M17C0_SETTINGS_T));
		if (PE_KDRV_VER_M17CX)
		{
			#if 1
			PE_SHP_M17C0_QWr01(shp_core_ctrl_00,reg_top_mode_3d,0x0);
			PE_CEO_PE1_M17C0_QWr01(pe1_top_ctrl_02,mode_3d,0x0);
			PE_CMN_HW_M17C0_DBG_PRINT("vsp-yc,rgb, lvctrl : enable.\n");
			#ifdef PE_CMN_HW_M17C0_USE_LVCTRL_OF_IMX
			PE_IMX_M17C0_RdFL(ctrl_m0_y_level_ctrl);
			PE_IMX_M17C0_Wr01(ctrl_m0_y_level_ctrl,reg_lvctrl_en,0x1);
			PE_IMX_M17C0_Wr01(ctrl_m0_y_level_ctrl,level_offset,0x200);
			PE_IMX_M17C0_Wr01(ctrl_m0_y_level_ctrl,level_center,0x80);
			PE_IMX_M17C0_Wr01(ctrl_m0_y_level_ctrl,level_gain,0x80);
			PE_IMX_M17C0_WrFL(ctrl_m0_y_level_ctrl);
			#endif
			PE_ND0_M17C0_QWr04(lvcrtl_ctrl_00,     enable,             0x1, \
                                                    y_offset,           0x200, \
                                                    center_position,    0x80, \
                                                    y_gain,             0x80);
			/* vspyc center_position 0x0->0x10(related with 16~235 range) */
			PE_CEO_PE1_M17C0_QWr05(pe1_vspyc_ctrl_00,enable,            0x1, \
                                                     graycolor_enable,  0x0, \
                                                     color_only_enable, 0x0, \
                                                     center_position,   0x10, \
                                                     contrast,          0x200);
			PE_CEO_PE1_M17C0_QWr02(pe1_vspyc_ctrl_01,saturation,        0x80,\
                                                   brightness,        0x200);
			PE_CEO_PE1_M17C0_QWr01(pe1_cen_ctrl_02,  ihsv_vgain,        0x80);
			PE_CEO_PE1_M17C0_QWr02(pe1_cen_ctrl_03,  ihsv_voffset,      0x80, \
                                                     ihsv_hoffset,      0x80);
			#endif
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set cmn debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_cmn_hw_m17c0_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_M17C0_DBG_PRINT("set[%d] type:0x%x, print:0x%x, bypass:0x%x, fwc_en,dbg:%d,%d\n",\
			pstParams->win_id,pstParams->type,pstParams->print_lvl,pstParams->bypass,\
			pstParams->fwc.ctrl_en,pstParams->fwc.dbg_en);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmn_hw_m17c0_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CMN)))? 0x1:0x0;
			pInfo->dbg_print_lvl = pstParams->print_lvl;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if (PE_KDRV_VER_M17CX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMN)))
				{
					PE_CMN_HW_M17C0_DBG_PRINT("cont,bri,sat disable, hue bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_ND0_M17C0_QWr01(lvcrtl_ctrl_00,enable,0x0);
						PE_CEO_PE1_M17C0_QWr01(pe1_vspyc_ctrl_00,enable,0x0);
						PE_CEO_PE1_M17C0_QWr01(pe1_cen_ctrl_03,ihsv_hoffset,0x80);
					}
				}
				else
				{
					PE_CMN_HW_M17C0_DBG_PRINT("cont,bri,sat enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_ND0_M17C0_QWr01(lvcrtl_ctrl_00,enable,0x1);
						PE_CEO_PE1_M17C0_QWr01(pe1_vspyc_ctrl_00,enable,0x1);
					}
				}
			}
			else
			{
				PE_CMN_HW_M17C0_DBG_PRINT("do nothing.\n");	ret = RET_OK;
			}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				pInfo->dbg_bypass[LX_PE_WIN_0] = pstParams->bypass;
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				pInfo->dbg_bypass[LX_PE_WIN_1] = pstParams->bypass;
			}
		}
		/* set fwc */
		if(pstParams->type&LX_PE_DBG_FW)
		{
			if (PE_KDRV_VER_M17CX)
			{	
				#if 1
				PE_FWI_M17C0_FW_CTRL fw_ctrl;
				PE_FWI_M17C0_SetDbgPrint(pstParams->fwc.dbg_en);
				fw_ctrl.enable = (pstParams->fwc.ctrl_en)? 0x1:0x0;
				ret = PE_FWI_M17C0_SetFwCtrl(&fw_ctrl, FALSE);
				PE_CMN_HW_M17C0_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_M17C0_SetFwCtrl() error.\n",__F__,__L__);
				#endif
				PE_CMN_HW_M17C0_SetDbInfo(PE_CMN_HW_M17C0_DB_INF_MD0_TNR_FW_EN, PE_DDR_M17C0_SEC_TNR_LUT, pstParams->fwc.ctrl_en);
			}
			else
			{
				PE_CMN_HW_M17C0_DBG_PRINT("do nothing.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}

/**
 * get cmn debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_GetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_CMN_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_cmn_hw_m17c0_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_CHECK_WIN0(win_id))
		{
			pstParams->bypass = pInfo->dbg_bypass[LX_PE_WIN_0];
		}
		if(PE_CHECK_WIN1(win_id))
		{
			pstParams->bypass = pInfo->dbg_bypass[LX_PE_WIN_1];
		}
		pstParams->print_lvl = pInfo->dbg_print_lvl;
		if (PE_KDRV_VER_M17CX)
		{
			PE_FWI_M17C0_SETTINGS_T param;
			pstParams->fwc.dbg_en = PE_FWI_M17C0_GetDbgPrint();
			ret = PE_FWI_M17C0_GetCurFwiSettings(&param);
			PE_CMN_HW_M17C0_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_M17C0_GetCurFwiSettings() error.\n",__F__,__L__);
			pstParams->fwc.ctrl_en = param.fw_ctrl.enable;
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("not use fwc.\n");
			pstParams->fwc.dbg_en = 0;
			pstParams->fwc.ctrl_en = 0;
		}
		PE_CMN_HW_M17C0_DBG_PRINT("get[%d] type:0x%x, print:0x%x, bypass:0x%x, fwc_en,dbg:%d,%d\n",\
			pstParams->win_id,pstParams->type,pstParams->print_lvl,pstParams->bypass,\
			pstParams->fwc.ctrl_en,pstParams->fwc.dbg_en);
	}while(0);
	return ret;
}
/**
 * set pe cmn operation periodically
 *	- ud,3d mode on pe1 operation
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetOperationMode(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_M17C0_BRINGUP
	PE_CMN_HW_M17C0_OPR_MODE_T cur_param;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_CMN_HW_M17C0_OPR_MODE_T *opr_info=&_g_pe_cmn_hw_m17c0_info.opr_inf;

	do {

		CHECK_KNULL(pCfg);

		if (PE_KDRV_VER_M17CX) 
		{
			/* pe1 ud mode */
			cur_param.pe1_mode_ud = 0;

			/* set pe1 top ctrl : 3d mode(ud mode is NA for M17C0) */
			if(opr_info->pe1_mode_3d != cur_param.pe1_mode_3d) {

				PE_CMN_HW_M17C0_DBG_PRINT("[inf]out:%d,fmt:%d\n",\
					disp0_info->out_type,disp0_info->fmt_type);
				PE_CMN_HW_M17C0_DBG_PRINT("[set]ud,3d mode : prev:%d,%d, cur:%d,%d\n",\
					opr_info->pe1_mode_ud,opr_info->pe1_mode_3d,\
					cur_param.pe1_mode_ud,cur_param.pe1_mode_3d);
				PE_SHP_M17C0_QWr01(shp_core_ctrl_00,reg_top_mode_3d,cur_param.pe1_mode_3d);
				PE_CEO_PE1_M17C0_QWr01(pe1_top_ctrl_02,mode_3d,cur_param.pe1_mode_3d);
				opr_info->pe1_mode_ud = cur_param.pe1_mode_ud;
				opr_info->pe1_mode_3d = cur_param.pe1_mode_3d;
			}
		} 
		else 
		{

			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;

		}

	}while(0);
	#endif
	return ret;
}
/**
 * set contrast
 *
 * @param   *pstParams [in] LX_PE_CMN_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetContrast(LX_PE_CMN_CONTRAST_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_M17C0_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->contrast);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CEO_PE1_M17C0_QWr01(pe1_vspyc_ctrl_00, contrast, GET_BITS(pstParams->contrast,0,10));
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * get contrast
 *
 * @param   *pstParams [in/out] LX_PE_CMN_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_GetContrast(LX_PE_CMN_CONTRAST_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_M17C0_QRd01(pe1_vspyc_ctrl_00, contrast, pstParams->contrast);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_M17C0_QRd01(pe1_vspyc_ctrl_00, contrast, pstParams->contrast);
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_M17C0_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->contrast);
	}while(0);
	return ret;
}
/**
 * set brightness
 *
 * @param   *pstParams [in] LX_PE_CMN_BRIGHTNESS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetBrightness(LX_PE_CMN_BRIGHTNESS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_M17C0_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->brightness);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CEO_PE1_M17C0_QWr01(pe1_vspyc_ctrl_01, brightness, GET_BITS(pstParams->brightness,0,10));
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get brightness
 *
 * @param   *pstParams [in/out] LX_PE_CMN_BRIGHTNESS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_GetBrightness(LX_PE_CMN_BRIGHTNESS_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_M17C0_QRd01(pe1_vspyc_ctrl_01, brightness, pstParams->brightness);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_M17C0_QRd01(pe1_vspyc_ctrl_01, brightness, pstParams->brightness);
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_M17C0_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->brightness);
	}while(0);
	return ret;
}
/**
 * set saturation
 *
 * @param   *pstParams [in] LX_PE_CMN_SATURATION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_M17C0_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->saturation);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CEO_PE1_M17C0_QWr01(pe1_vspyc_ctrl_01, saturation, GET_BITS(pstParams->saturation,0,8));
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get saturation
 *
 * @param   *pstParams [in/out] LX_PE_CMN_SATURATION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_GetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_M17C0_QRd01(pe1_vspyc_ctrl_01, saturation, pstParams->saturation);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_M17C0_QRd01(pe1_vspyc_ctrl_01, saturation, pstParams->saturation);
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_M17C0_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->saturation);
	}while(0);
	return ret;
}
/**
 * set hue
 *
 * @param   *pstParams [in] LX_PE_CMN_HUE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_M17C0_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->hue);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CEO_PE1_M17C0_QWr01(pe1_cen_ctrl_03, ihsv_hoffset, GET_BITS(pstParams->hue,0,8));
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get hue
 *
 * @param   *pstParams [in/out] LX_PE_CMN_HUE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_GetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_M17C0_QRd01(pe1_cen_ctrl_03, ihsv_hoffset, pstParams->hue);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_M17C0_QRd01(pe1_cen_ctrl_03, ihsv_hoffset, pstParams->hue);
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_M17C0_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->hue);
	}while(0);
	return ret;
}
/**
 * set level control
 *
 * @param   *pstParams [in] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_CMN_HW_M17C0_USE_VGAIN_FOR_LVCTRL
	PE_CMN_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_cmn_hw_m17c0_info;
	#endif
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_M17C0_DBG_PRINT("set pstParams[%d] : ofs:%d, center:%d, gain:%d, tp:%d\n",\
			pstParams->win_id,pstParams->offset,pstParams->center,\
			pstParams->gain,pstParams->tp_on);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_CMN_HW_M17C0_USE_LVCTRL_OF_IMX
				#if 0
					PE_ND0_M17C0_RdFL(ipp_fsw_ctrl_00);
					PE_ND0_M17C0_Wr01(ipp_fsw_ctrl_00,level_offset, GET_BITS(pstParams->offset,0,10));
					PE_ND0_M17C0_Wr01(ipp_fsw_ctrl_00,level_center, GET_BITS(pstParams->center,0,8));
					PE_ND0_M17C0_Wr01(ipp_fsw_ctrl_00,level_gain,   GET_BITS(pstParams->gain,0,8));
					PE_ND0_M17C0_WrFL(ipp_fsw_ctrl_00);
					PE_CEO_PE1_M17C0_QWr01(pe1_vspyc_ctrl_00,graycolor_enable,(pstParams->tp_on)? 0x1:0x0);
				#else
				PE_IMX_M17C0_RdFL(ctrl_m0_y_level_ctrl);
				PE_IMX_M17C0_Wr01(ctrl_m0_y_level_ctrl,reg_lvctrl_en,0x1);
				PE_IMX_M17C0_Wr01(ctrl_m0_y_level_ctrl,level_offset,GET_BITS(pstParams->offset,0,10));
				PE_IMX_M17C0_Wr01(ctrl_m0_y_level_ctrl,level_center,GET_BITS(pstParams->center,0,8));
				PE_IMX_M17C0_Wr01(ctrl_m0_y_level_ctrl,level_gain,GET_BITS(pstParams->gain,0,8));
				PE_IMX_M17C0_WrFL(ctrl_m0_y_level_ctrl);
				#endif
				#if 0
				ret = PE_FWI_M17C0_SetPushMode(LX_PE_WIN_0);
				PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_M17C0_SetPushMode() error.\n",__F__,__L__);
				#endif
				#else //PE_CMN_HW_M17C0_USE_LVCTRL_OF_IMX
				#ifdef PE_CMN_HW_M17C0_USE_VGAIN_FOR_LVCTRL
				pInfo->cur_lvctrl_gain = GET_BITS(pstParams->gain,0,8);
				pInfo->cur_lvctrl_ofst = GET_BITS(pstParams->offset,0,10);
				PE_ND0_M17C0_QWr01(lvcrtl_ctrl_00, center_position, GET_BITS(pstParams->center,0,8));
				#else
				PE_ND0_M17C0_QWr03(lvcrtl_ctrl_00, y_offset,        GET_BITS(pstParams->offset,0,10), \
                                                    center_position, GET_BITS(pstParams->center,0,8), \
                                                    y_gain,          GET_BITS(pstParams->gain,0,8));
				#endif
				PE_CEO_PE1_M17C0_QWr01(pe1_vspyc_ctrl_00,graycolor_enable,(pstParams->tp_on)? 0x1:0x0);
				#endif
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get level control
 *
 * @param   *pstParams [in/out] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_GetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_ND0_M17C0_QRd03(lvcrtl_ctrl_00, y_offset,        pstParams->offset,\
                                                      center_position, pstParams->center,\
                                                      y_gain,          pstParams->gain);
				PE_CE_PE1_M17C0_QRd01(pe1_vspyc_ctrl_00,graycolor_enable,pstParams->tp_on);
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CMN_HW_M17C0_DBG_PRINT("get pstParams[%d] : ofs:%d, center:%d, gain:%d, tp:%d\n",\
			pstParams->win_id,pstParams->offset,pstParams->center,\
			pstParams->gain,pstParams->tp_on);
	}while(0);
	return ret;
}
/**
 * set level mode
 *	- set cen vgain instead of lvctrl, when tnr,sc mem share mode
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetLevelCtrlMode(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_CMN_HW_M17C0_USE_VGAIN_FOR_LVCTRL
	static UINT32 count = 0;
	UINT32 tnrw_off, delta;
	UINT32 cur_ihsv_v_gain,cur_ihsv_v_ofst,cur_lvctrl_gain,cur_lvctrl_ofst;
	PE_CMN_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_cmn_hw_m17c0_info;
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_M17CX)
		{
			PE_ND0_M17C0_QRd01(pe0_opmode,tnrw_off,tnrw_off);
			if (tnrw_off)	//mem share mode
			{
				cur_lvctrl_gain = 128;//default
				cur_lvctrl_ofst = 512;//default
				cur_ihsv_v_gain = pInfo->cur_lvctrl_gain;
				if (pInfo->cur_lvctrl_ofst>512)
				{
					delta = pInfo->cur_lvctrl_ofst-512;
					if (delta>127)	delta=127;
					cur_ihsv_v_ofst = 128+delta;
				}
				else
				{
					delta = 512-pInfo->cur_lvctrl_ofst;
					if (delta>128)	delta=128;
					cur_ihsv_v_ofst = 128-delta;
				}
			}
			else	//normal mode
			{
				cur_lvctrl_gain = pInfo->cur_lvctrl_gain;
				cur_lvctrl_ofst = pInfo->cur_lvctrl_ofst;
				cur_ihsv_v_gain = 128;//default
				cur_ihsv_v_ofst = 128;//default
			}
			/* set lvctrl gain,ofst */
			if (pInfo->pre_lvctrl_gain!=cur_lvctrl_gain || pInfo->pre_lvctrl_ofst!=cur_lvctrl_ofst)
			{
				PE_CMN_HW_M17C0_DBG_PRINT("[inf] tnrw_off:%d, cur_lvctrl gain:%d,ofst:%d\n",\
					tnrw_off, pInfo->cur_lvctrl_gain, pInfo->cur_lvctrl_ofst);
				PE_CMN_HW_M17C0_DBG_PRINT("[set] lvctrl gain:%d->%d,ofst:%d->%d\n",\
					pInfo->pre_lvctrl_gain, cur_lvctrl_gain, pInfo->pre_lvctrl_ofst, cur_lvctrl_ofst);
				PE_ND0_M17C0_QWr02(lvcrtl_ctrl_00,y_offset,cur_lvctrl_ofst,y_gain,cur_lvctrl_gain);
				pInfo->pre_lvctrl_gain=cur_lvctrl_gain;
				pInfo->pre_lvctrl_ofst=cur_lvctrl_ofst;
			}
			/* set ihsv_v gain,ofst */
			if (pInfo->pre_ihsv_v_gain!=cur_ihsv_v_gain || pInfo->pre_ihsv_v_ofst!=cur_ihsv_v_ofst)
			{
				PE_CMN_HW_M17C0_DBG_PRINT("[inf] tnrw_off:%d, cur_ihsv_v gain:%d,ofst:%d\n",\
					tnrw_off, pInfo->cur_lvctrl_gain, pInfo->cur_lvctrl_ofst);
				PE_CMN_HW_M17C0_DBG_PRINT("[set] ihsv_v gain:%d->%d,ofst:%d->%d\n",\
					pInfo->pre_ihsv_v_gain, cur_ihsv_v_gain, pInfo->pre_ihsv_v_ofst, cur_ihsv_v_ofst);
				PE_CEO_PE1_M17C0_QWr01(pe1_cen_ctrl_02, ihsv_vgain, cur_ihsv_v_gain);
				PE_CEO_PE1_M17C0_QWr01(pe1_cen_ctrl_03, ihsv_voffset, cur_ihsv_v_ofst);
				pInfo->pre_ihsv_v_gain=cur_ihsv_v_gain;
				pInfo->pre_ihsv_v_ofst=cur_ihsv_v_ofst;
			}
			if(_g_cmn_hw_m17c0_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					printk("[stat] tnrw_off:%d, cur_lvctrl gain:%d,ofst:%d\n",\
						tnrw_off, pInfo->cur_lvctrl_gain, pInfo->cur_lvctrl_ofst);
					printk("[stat] lvctrl gain:%d,ofst:%d, ihsv_v gain:%d,ofst:%d\n", \
						cur_lvctrl_gain, cur_lvctrl_ofst, cur_ihsv_v_gain, cur_ihsv_v_ofst);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	return ret;
}
/**
 * download db
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_DownloadDb(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	PE_DDR_M17C0_MD0_T *p_md0;
	PE_CMN_HW_M17C0_SETTINGS_T *p_inf = &_g_pe_cmn_hw_m17c0_info;
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = NULL;
	volatile PE_DDR_DB_PHYS_REG_M17C0_T *p_phys_db = NULL;
	gPE_DDR_DB_M17C0.phys.addr = NULL;
	p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_shdw_db);
		if (PE_KDRV_VER_M17CX)
		{
			PE_PRINT_NOTI("DL db start(resume:%d,init:%d).\n", \
				pstParams->resume_mode, p_inf->db_initialized);
			if (!p_inf->db_initialized)
			{
				/* move db mode setting here to avoid db mode clear on resume init */
				p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
				p_md0->shp_fw_en = 0;
				#ifdef PE_HW_M17C0_USE_FW_SRC_APL
				p_md0->hst_fw_en = 1;
				#else
				p_md0->hst_fw_en = 0;
				#endif
				p_md0->scl_fw_en = 1;
				p_md0->tnr_fw_en = 1;
				p_md0->dnr_fw_en = 0;
				if (!pstParams->resume_mode)
				{
					gPE_DDR_DB_M17C0.phys.addr = (volatile UINT32 *)vmap_phys(PE_M17C0_DDR_DB_BASE, \
						sizeof(PE_DDR_DB_PHYS_REG_M17C0_T));
					p_phys_db = gPE_DDR_DB_M17C0.phys.data;
					CHECK_KNULL(p_phys_db);
					p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_DDR_M17C0_DB_VER;
					p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_M17C0_DDR_DB_BASE;
					p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_DDR_M17C0_SEC_NUM;
					/* *********************************************************************/
					/* Causion : Should be arranged in enum order **************************/
					/* *********************************************************************/
					/* mode : PE_DDR_M17C0_SEC_MODE(should be 1st one) */
					ret = PE_CMN_HW_M17C0_DownloadModeDb();
					PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_CMN_HW_M17C0_DownloadModeDb() error.\n",__F__,__L__);
					/* drc : PE_DDR_M17C0_SEC_DRC_LUT */
					ret = PE_DCM_HW_M17C0_DownloadDrcDb();
					PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_DCM_HW_M17C0_DownloadDrcDb() error.\n",__F__,__L__);
					/* cvd : PE_DDR_M17C0_SEC_CVD_DFLT */
					ret = PE_CMN_HW_M17C0_DownloadCvdDb();
					PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_CMN_HW_M17C0_DownloadCvdDb() error.\n",__F__,__L__);
					/* scl : PE_DDR_M17C0_SEC_SCL_06T_M ~ PE_DDR_M17C0_SEC_SCL_04T_M */
					ret = PE_SHP_HW_M17C0_DownloadSclDb();
					PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_M17C0_DownloadSclDb() error.\n",__F__,__L__);
					/* tnr : PE_DDR_M17C0_SEC_TNR_LUT ~ PE_DDR_M17C0_SEC_TNR_USER */
					ret = PE_NRD_HW_M17C0_DownloadTnrDb();
					PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_M17C0_DownloadTnrDb() error.\n",__F__,__L__);
					/* apl : PE_DDR_M17C0_SEC_BLK_APL */
					ret = PE_HST_HW_M17C0_DownloadBlkAplDb();
					PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_HST_HW_M17C0_DownloadBlkAplDb() error.\n",__F__,__L__);
					/* drc : PE_DDR_M17C0_SEC_DRC_CURV */
					ret = PE_DCM_HW_M17C0_DownloadDrcCurvDbInit();
					PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_DCM_HW_M17C0_DownloadDrcCurvDbInit() error.\n",__F__,__L__);
					wmb();
				}
				/* inform load db data */
				ret = PE_FWI_M17C0_LoadDbData(p_shdw_db->top_h.db_base);
				PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_M17C0_LoadDbData() error.\n",__F__,__L__);
				/* *********************************************************************/
				PE_PRINT_NOTI("DL db done.(md:0x%08x)(base:0x%08x)\n", p_inf->db_mode_data[0], PE_M17C0_DDR_DB_BASE);
				p_inf->db_initialized = 1;
			}
			else
			{
				PE_PRINT_NOTI("DL db done already.(md:0x%08x)(base:0x%08x)\n", p_inf->db_mode_data[0], PE_M17C0_DDR_DB_BASE);
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	if (gPE_DDR_DB_M17C0.phys.addr) vunmap_phys((void *)gPE_DDR_DB_M17C0.phys.addr);
	return ret;
}
/**
 * download mode db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_HW_M17C0_DownloadModeDb(void)
{
	int ret = RET_OK;
	UINT32 size = 0, sec_typ = 0;
	PE_CMN_HW_M17C0_SETTINGS_T *p_inf = &_g_pe_cmn_hw_m17c0_info;
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_M17C0_T *p_phys_db = gPE_DDR_DB_M17C0.phys.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_M17CX)
		{
			/* header */
			sec_typ = PE_DDR_M17C0_SEC_MODE;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M17C0_MODE_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M17C0_MODE_SIZE;
			p_phys_db->mode.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->mode.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->mode.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->mode.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_MODE_ITEM_NUM * PE_DDR_M17C0_MODE_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.db_base+sizeof(PE_DDR_M17C0_TOP_HEADER_T);
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M17C0_HEADER_T);
			/* wr ddr */
			p_phys_db->mode.data[0] = p_inf->db_mode_data[0];
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * download cvd db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_HW_M17C0_DownloadCvdDb(void)
{
	int ret = RET_OK;
	UINT32 size, sec_typ;
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_M17C0_T *p_phys_db = gPE_DDR_DB_M17C0.phys.data;
	volatile UINT32 *p_cvd_dflt_data  = p_phys_db->cvd_dflt.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_cvd_dflt_data);
		if (PE_KDRV_VER_M17CX)
		{
			/* cvd_dflt **************************************************************/
			sec_typ = PE_DDR_M17C0_SEC_CVD_DFLT;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M17C0_CVD_DFLT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M17C0_CVD_DFLT_SIZE;
			p_phys_db->cvd_dflt.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->cvd_dflt.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->cvd_dflt.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->cvd_dflt.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_CVD_DFLT_ITEM_NUM * PE_DDR_M17C0_CVD_DFLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M17C0_HEADER_T);
			/* wr ddr */
#ifdef INCLUDE_KDRV_AFE
			ret = CVD_SetPqModeToDdr(p_cvd_dflt_data);
			PE_CMN_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] CVD_SetPqModeToDdr() error.\n",__F__,__L__);
#endif
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * get db info.
 *
 * @param   inf_type [in] UINT32, see PE_CMN_HW_M17C0_DB_INF_TYPE
 * @param   sec_type [in] UINT32, see PE_DDR_M17C0_SEC_TYPE
 * @return  UINT32.
 * @see
 * @author
 */
UINT32 PE_CMN_HW_M17C0_GetDbInfo(UINT32 inf_type, UINT32 sec_type)
{
	UINT32 ret = 0;
	PE_DDR_M17C0_MD0_T *p_md0;
	PE_CMN_HW_M17C0_SETTINGS_T *p_inf = &_g_pe_cmn_hw_m17c0_info;
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;

	if (sec_type>=PE_DDR_M17C0_SEC_NUM)
		return ret;

	switch (inf_type)
	{
		case PE_CMN_HW_M17C0_DB_INF_IS_DB_INIT:
			ret = p_inf->db_initialized;
			break;
		case PE_CMN_HW_M17C0_DB_INF_TOP_VERSION:
			ret = p_shdw_db->top_h.version;
			break;
		case PE_CMN_HW_M17C0_DB_INF_TOP_BASE:
			ret = p_shdw_db->top_h.db_base;
			break;
		case PE_CMN_HW_M17C0_DB_INF_TOP_SEC_NUM:
			ret = p_shdw_db->top_h.sec_num;
			break;
		case PE_CMN_HW_M17C0_DB_INF_SEC_BASE:
			ret = p_shdw_db->top_h.sec_base[sec_type];
			break;
		case PE_CMN_HW_M17C0_DB_INF_SEC_SIZE:
			ret = p_shdw_db->top_h.sec_size[sec_type];
			break;
		case PE_CMN_HW_M17C0_DB_INF_SEC_VERSION:
			ret = p_shdw_db->sec_d[sec_type].header.version;
			break;
		case PE_CMN_HW_M17C0_DB_INF_SEC_TYPE:
			ret = p_shdw_db->sec_d[sec_type].header.sec_type;
			break;
		case PE_CMN_HW_M17C0_DB_INF_SEC_ITEM_NUM:
			ret = p_shdw_db->sec_d[sec_type].header.item_num;
			break;
		case PE_CMN_HW_M17C0_DB_INF_SEC_ITEM_SIZE:
			ret = p_shdw_db->sec_d[sec_type].header.item_size;
			break;
		case PE_CMN_HW_M17C0_DB_INF_SEC_DATA_BASE:
			ret = p_shdw_db->sec_d[sec_type].data_base;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_SHP_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->shp_fw_en;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_HST_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->hst_fw_en;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_SCL_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->scl_fw_en;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_TNR_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->tnr_fw_en;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_DNR_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->dnr_fw_en;
			break;
		default:
			ret = 0;
			break;
	}
	return ret;
}

/**
 * set db info.
 * - I think that shdw db modification is not good.
 *
 * @param   inf_type [in] UINT32, see PE_CMN_HW_M17C0_DB_INF_TYPE
 * @param   sec_type [in] UINT32, see PE_DDR_M17C0_SEC_TYPE
 * @param   value [in] UINT32
 * @return  UINT32.
 * @see
 * @author
 */
UINT32 PE_CMN_HW_M17C0_SetDbInfo(UINT32 inf_type, UINT32 sec_type, UINT32 value)
{
	UINT32 ret = 0;
	PE_DDR_M17C0_MD0_T *p_md0;
	PE_CMN_HW_M17C0_SETTINGS_T *p_inf = &_g_pe_cmn_hw_m17c0_info;

	if (sec_type>=PE_DDR_M17C0_SEC_NUM)
		return ret;

	switch (inf_type)
	{
		case PE_CMN_HW_M17C0_DB_INF_MD0_SHP_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			p_md0->shp_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_HST_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			p_md0->hst_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_SCL_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			p_md0->scl_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_TNR_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			p_md0->tnr_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_M17C0_DB_INF_MD0_DNR_FW_EN:
			p_md0 = (PE_DDR_M17C0_MD0_T *)p_inf->db_mode_data;
			p_md0->dnr_fw_en = value? 1:0;
			break;
		default:
			ret = 0;
			break;
	}
	return ret;
}

static void PE_CMN_HW_M17C0_Get3DModeInternalFRC( LX_PE_INF_DISPLAY_T *i_pstDispInfo,
												UINT32 				*o_ui32PE1Mode3D )
{
	#ifdef PE_HW_M17C0_BRINGUP
	switch(i_pstDispInfo->out_type)
	{
		case LX_PE_OUT_DUAL_TB:
		case LX_PE_OUT_DUAL_SS:
		case LX_PE_OUT_DUAL_FULL:
		case LX_PE_OUT_LA:
			*o_ui32PE1Mode3D = 1;
			break;
		case LX_PE_OUT_2D_3D:
			if(i_pstDispInfo->out_sub==LX_PE_OUT_LA)
			{
				*o_ui32PE1Mode3D = 1;
			}
			else
			{
				*o_ui32PE1Mode3D = 0;
			}
			break;
		case LX_PE_OUT_2D:
		case LX_PE_OUT_3D_2D:
		case LX_PE_OUT_UD:
		case LX_PE_OUT_TB:
		case LX_PE_OUT_SS:
		case LX_PE_OUT_FS:
		case LX_PE_OUT_PIP:
		default:
			*o_ui32PE1Mode3D = 0;
			break;
	}

	return;
	#endif
}

/**
 * download db bin
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  void
 * @see     PE_TSK_M17C0_OPR_T
 * @author
 */
int PE_CMN_M17C0_DownloadDbBin(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	UINT32 db_addr = 0;
	UINT32 head_num, head_size, data_size;
	volatile UINT32 *ddr_addr = NULL;
	do {
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		db_addr = pstParams->data[0];
		head_num = 1;
		head_size = sizeof(UINT32)*head_num;
		if (pstParams->size<(head_num<<1))
		{
			PE_PRINT_NOTI("warning. invalid(0) (addr:0x%08x, size:%d)\n",db_addr,pstParams->size);
			pstParams->size = (head_num<<1);
		}
		if (db_addr<PE_M17C0_DDR_DB_BASE)
		{
			PE_PRINT_NOTI("warning. invalid(1) (addr:0x%08x, size:%d)\n",db_addr,pstParams->size);
		}
		if ((db_addr+pstParams->size)>(PE_M17C0_DDR_DB_BASE+PE_M17C0_DDR_DB_SIZE))
		{
			PE_PRINT_NOTI("warning. invalid(2) (addr:0x%08x, size:%d)\n",db_addr,pstParams->size);
		}
		data_size = (pstParams->size*sizeof(UINT32)) - head_size;
		PE_PRINT_NOTI("size:%d(%d), addr:0x%08x\n", pstParams->size, data_size, db_addr);
		ddr_addr = (volatile UINT32 *)vmap_phys(db_addr, data_size+PAGE_SIZE);
		if(!ddr_addr) {PE_PRINT_NOTI("ddr_addr is null.\n");break;}
		memcpy((UINT32 *)ddr_addr, pstParams->data + head_num, data_size);
		//for (i=0; i<(pstParams->size/sizeof(UINT32)); i++)	PE_PRINT_NOTI("db[%d]:0x%08x\n", i, pstParams->data[i]);
		wmb();
	} while(0);
	if(ddr_addr)	vunmap_phys((void*)ddr_addr);
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
int PE_CMN_M17C0_GetDownloadInfo(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0;
	UINT32 used_size = sizeof(PE_DDR_DB_PHYS_REG_M17C0_T);

#define PE_CMN_M17C0_PRINT_START		"START_OF_PRINT"
#define PE_CMN_M17C0_PRINT_RESERVED	"RESERVED"
#define PE_CMN_M17C0_PRINT_END		"END_OF_PRINT"
#define PE_CMN_M17C0_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_CMN_M17C0_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):sprintf(_buf, "   [0x%02x] %s\n", (_item), #_item);_action;break
#define PE_CMN_M17C0_CASE_SPRINT(_cnt,_action,_buf,fmt,args...)	\
	case (_cnt):sprintf(_buf,fmt,##args);_action;break
#define PE_CMN_M17C0_DFLT_SPRINT(_action,_buf,fmt,args...)		\
	default:sprintf(_buf,fmt,##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		if (PE_KDRV_VER_M17CX)
		{
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]==0)
			{
				switch(rd_cnt)
				{
					PE_CMN_M17C0_CASE_SPRINT( 0,rd_cnt++,buffer,PE_CMN_M17C0_PRINT_START);
					PE_CMN_M17C0_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"   alloc base : 0x %08x ~ 0x %08x\n", \
						PE_M17C0_DDR_DB_BASE, PE_M17C0_DDR_DB_BASE+PE_M17C0_DDR_DB_SIZE);
					PE_CMN_M17C0_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"   free  base : 0x %08x\n", PE_M17C0_DDR_DB_BASE+used_size);
					PE_CMN_M17C0_CASE_SPRINT( 3,rd_cnt++,buffer,\
						"   used  size : 0x %08x (%4d KB)\n", used_size, used_size>>10);
					PE_CMN_M17C0_CASE_SPRINT( 4,rd_cnt++,buffer,\
						"   free  size : 0x %08x (%4d KB)\n", \
						(PE_M17C0_DDR_DB_SIZE-used_size), (PE_M17C0_DDR_DB_SIZE-used_size)>>10);
					PE_CMN_M17C0_CASE_SPRINT( 5,rd_cnt++,buffer,PE_CMN_M17C0_PRINT_RESERVED);
					PE_CMN_M17C0_DFLT_SPRINT(rd_cnt=0,buffer,PE_CMN_M17C0_PRINT_END);
				}
			}
			else
			{
				sprintf(buffer, PE_CMN_M17C0_PRINT_EXIT);
				rd_cnt=0;
			}
			memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
		}
		else
		{
			PE_PRINT_NOTI("nothing to do.\n");
		}
	}while(0);
	return ret;
}
/**
 * set suspend module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SuspendModule(void)
{
	PE_TSK_M17C0_SuspendModule(0);
	return RET_OK;
}
/**
 * set vcp level control
 *
 * @param   *pstParams [in] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_M17C0_DBG_PRINT("set pstParams[%d] : enable:%d, center:%d, contrast:%d, brightness:%d, saturation:%d\n",\
			pstParams->win_id,pstParams->enable,pstParams->center_position,\
			pstParams->contrast,pstParams->brightness,pstParams->saturation);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_VCP_DISP_M17C0_QWr03(vcp_vsp_u0_ctrl_00, 	enable, 		 GET_BITS(pstParams->enable,		 0,1),\
															center_position, GET_BITS(pstParams->center_position,0,8),\
															contrast,		 GET_BITS(pstParams->contrast,		 0,10));
				PE_VCP_DISP_M17C0_QWr02(vcp_vsp_u0_ctrl_01,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
															brightness,		 GET_BITS(pstParams->brightness,	 0,10));
			}
			else if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_VCP_DISP_M17C0_QWr03(vcp_vsp_u1_ctrl_00, 	enable, 		 GET_BITS(pstParams->enable,		 0,1),\
															center_position, GET_BITS(pstParams->center_position,0,8),\
															contrast,		 GET_BITS(pstParams->contrast,		 0,10));
				PE_VCP_DISP_M17C0_QWr02(vcp_vsp_u1_ctrl_01,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
															brightness,		 GET_BITS(pstParams->brightness,	 0,10));
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get vcp level control
 *
 * @param   *pstParams [in/out] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_GetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if (PE_KDRV_VER_M17CX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_VCP_DISP_M17C0_QRd03(vcp_vsp_u0_ctrl_00, 	enable, 		 pstParams->enable,\
															center_position, pstParams->center_position,\
															contrast,		 pstParams->contrast);
				PE_VCP_DISP_M17C0_QRd02(vcp_vsp_u0_ctrl_01,	saturation,		 pstParams->saturation,\
															brightness,		 pstParams->brightness);
			}
			else if(PE_CHECK_WIN1(win_id))
			{
				PE_VCP_DISP_M17C0_QRd03(vcp_vsp_u1_ctrl_00, 	enable, 		 pstParams->enable,\
															center_position, pstParams->center_position,\
															contrast,		 pstParams->contrast);
				PE_VCP_DISP_M17C0_QRd02(vcp_vsp_u1_ctrl_01,	saturation,		 pstParams->saturation,\
															brightness,		 pstParams->brightness);
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CMN_HW_M17C0_DBG_PRINT("get pstParams[%d] : enable:%d, center:%d, contrast:%d, brightness:%d, saturation:%d\n",\
			pstParams->win_id,pstParams->enable,pstParams->center_position,\
			pstParams->contrast,pstParams->brightness,pstParams->saturation);
	}while(0);
	return ret;
}
/**
 * set bypass blocks
 *
 * @param   *pstParams [in] LX_PE_CMN_BYPASS_BLOCKS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_M17C0_SetBypassBlock(LX_PE_CMN_BYPASS_BLOCKS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		PE_CMN_HW_M17C0_DBG_PRINT("set pstParams: u32BlockMask = 0x%08x, bOnOff = %d\n",
			pstParams->u32BlockMask, pstParams->bOnOff);

		if (PE_KDRV_VER_M17CX)
		{
			if (pstParams->bOnOff)
			{
				if(pstParams->u32BlockMask & 0x1)//sharpness
				{
					PE_SR_SHP_M17C0_QWr01(shp_ctrl_00,reg_top_bypass, 0x1);
					PE_SHP_M17C0_QWr01(shp_core_ctrl_00,	reg_top_bypass,	0x1);
				}
				if(pstParams->u32BlockMask & 0x2)//PSP
				{
					PE_SHP_PSP_M17C0_Wr(reg_psp_ctrl_22, 0x00000000);
					PE_SHP_PSP_M17C0_WrFL(reg_psp_ctrl_22);
 				}
				if(pstParams->u32BlockMask & 0x4)//object contrast
				{
					//PE_CE_PE1_M17C0_QWr01(pe1_top_ctrl_02,	master_en,	0x0);
					//PE_CO_PE1_M17C0_QWr01(pe1_top_ctrl_02,	master_en,	0x0);
					PE_CE_PE1_M17C0_Wr(pe1_dce_ctrl_00, 0x050000F0);
					PE_CE_PE1_M17C0_WrFL(pe1_dce_ctrl_00);
					PE_CO_PE1_M17C0_Wr(pe1_dce_ctrl_00, 0x050000F0);
					PE_CO_PE1_M17C0_WrFL(pe1_dce_ctrl_00);
					PE_CE_PE1_M17C0_Wr(pe1_logo_ctrl_00, 0xC0010010);
					PE_CE_PE1_M17C0_WrFL(pe1_logo_ctrl_00);
					PE_CO_PE1_M17C0_Wr(pe1_logo_ctrl_00, 0xC0010010);
					PE_CO_PE1_M17C0_WrFL(pe1_logo_ctrl_00);
					PE_CE_PE1_M17C0_Wr(pe1_drc_ctrl_00, 0x00100100);
					PE_CE_PE1_M17C0_WrFL(pe1_drc_ctrl_00);
					PE_CE_PE1_M17C0_Wr(pe1_cen_ctrl_00, 0x0000002D);
					PE_CE_PE1_M17C0_WrFL(pe1_cen_ctrl_00);
					PE_CO_PE1_M17C0_Wr(pe1_cen_ctrl_00, 0x0000002D);
					PE_CO_PE1_M17C0_WrFL(pe1_cen_ctrl_00);
					PE_CE_PE1_M17C0_Wr(pe_pcc_ctrl, 0x00000000);
					PE_CE_PE1_M17C0_WrFL(pe_pcc_ctrl);
				}
				if(pstParams->u32BlockMask & 0x40)//vsp
				{
					PE_CE_PE1_M17C0_Wr(pe1_vspyc_ctrl_00, 0x02000000);
					PE_CE_PE1_M17C0_WrFL(pe1_vspyc_ctrl_00);
					PE_CO_PE1_M17C0_Wr(pe1_vspyc_ctrl_00, 0x02000000);
					PE_CO_PE1_M17C0_WrFL(pe1_vspyc_ctrl_00);
 				}
			}
			else
			{
				if(pstParams->u32BlockMask & 0x1)//sharpness
				{
					PE_SR_SHP_M17C0_QWr01(shp_ctrl_00,reg_top_bypass, 0x0);
					PE_SHP_M17C0_QWr01(shp_core_ctrl_00,	reg_top_bypass, 0x0);
				}
				if(pstParams->u32BlockMask & 0x2)//object contrast
				{
					PE_SHP_PSP_M17C0_Wr(reg_psp_ctrl_22, 0x00000005);
					PE_SHP_PSP_M17C0_WrFL(reg_psp_ctrl_22);
				}
				if(pstParams->u32BlockMask & 0x4)//object contrast
				{
					//PE_CE_PE1_M17C0_QWr01(pe1_top_ctrl_02,	master_en,	0x1);
					//PE_CO_PE1_M17C0_QWr01(pe1_top_ctrl_02,	master_en,	0x1);
					PE_CE_PE1_M17C0_Wr(pe1_dce_ctrl_00, 0x050000F1);
					PE_CE_PE1_M17C0_WrFL(pe1_dce_ctrl_00);
					PE_CO_PE1_M17C0_Wr(pe1_dce_ctrl_00, 0x050000F1);
					PE_CO_PE1_M17C0_WrFL(pe1_dce_ctrl_00);
					PE_CE_PE1_M17C0_Wr(pe1_logo_ctrl_00, 0xC0010011);
					PE_CE_PE1_M17C0_WrFL(pe1_logo_ctrl_00);
					PE_CO_PE1_M17C0_Wr(pe1_logo_ctrl_00, 0xC0010011);
					PE_CO_PE1_M17C0_WrFL(pe1_logo_ctrl_00);
					PE_CE_PE1_M17C0_Wr(pe1_drc_ctrl_00, 0x00100101);
					PE_CE_PE1_M17C0_WrFL(pe1_drc_ctrl_00);
					PE_CE_PE1_M17C0_Wr(pe1_cen_ctrl_00, 0x0000002C);
					PE_CE_PE1_M17C0_WrFL(pe1_cen_ctrl_00);
					PE_CO_PE1_M17C0_Wr(pe1_cen_ctrl_00, 0x0000002C);
					PE_CO_PE1_M17C0_WrFL(pe1_cen_ctrl_00);
					PE_CE_PE1_M17C0_Wr(pe_pcc_ctrl, 0x00001100);
					PE_CE_PE1_M17C0_WrFL(pe_pcc_ctrl);
				}
				if(pstParams->u32BlockMask & 0x40)//vsp
				{
					PE_CE_PE1_M17C0_Wr(pe1_vspyc_ctrl_00, 0x02000001);
					PE_CE_PE1_M17C0_WrFL(pe1_vspyc_ctrl_00);
					PE_CO_PE1_M17C0_Wr(pe1_vspyc_ctrl_00, 0x02000001);
					PE_CO_PE1_M17C0_WrFL(pe1_vspyc_ctrl_00);
 				}
			}
		}
		else
		{
			PE_CMN_HW_M17C0_DBG_PRINT("nothing to do\n");
			ret = RET_ERROR;
		}
	}while(0);

	return ret;
}

