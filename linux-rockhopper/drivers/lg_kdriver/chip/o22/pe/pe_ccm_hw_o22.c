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

/** @file pe_ccm_hw_o22.c
 *
 *  driver for picture enhance color correction module functions. ( used only within kdriver )
 *
 *	@author			Seung-Jun,Youm(sj.youm@lge.com)
 *  @modifier		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *	@version		0.1
 *	@note
 *	@date			2012.04.12
 *  @modified date  2015.05.22 for SWMD
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

#include "pe_hw_o22.h"
#include "pe_reg_o22.h"
#include "pe_fwi_o22.h"
#include "pe_ccm_hw_o22.h"
#include "pe_hst_hw_o22.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* Enabling this macro will DISABLE LGSI code refactoring changes, so enable only if there is
any issue in LGSI refactored code. This provision is only for cross checking with original
source. It can be removed in the next version of the code*/

#define PE_CCM_HW_O22_SAT_STATUS_TH		200
#define PE_CCM_HW_O22_LRCR_GAIN			0xa
#define PE_CCM_HW_O22_LRCR_MAX_HIS		224
#define PE_CCM_HW_O22_LRCR_VAL_BIN		72
#define PE_CCM_HW_O22_LRCR_TH1			128
#define PE_CCM_HW_O22_LRCR_TH0			129

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CCM_HW_O22_ERROR	printk

#define PE_CCM_HW_O22_DBG_PRINT(fmt,args...)	\
	if(_g_ccm_hw_o22_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CCM_HW_O22_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_CCM_HW_O22_ERROR(fmt,##args);_action;}}

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
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_ccm_hw_o22_trace=0x0;		//default should be off.

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * set debug print on off
 *
 * @param   on_off [in] UINT8
 * @return  void
 * @see
 * @author
 */
void PE_CCM_HW_O22_SetDbgPrint(UINT32 on_off)
{
	_g_ccm_hw_o22_trace = on_off? 1:0;
	return;
}
/**
 * init ccm
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_O22_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O22)
		{
			PE_CCM_HW_O22_DBG_PRINT("init param.\n");
			//memset(&_g_pe_ccm_hw_o22_info,0xff,sizeof(PE_CCM_HW_O22_SETTINGS_T));
			PE_CE_PE1_O22_QWr01(pe1_fsw_ctrl_00,reg_color_filter_status,0x0);//0x0~0x2:off,r,g,b
		}
		else
		{
			PE_CCM_HW_O22_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * ccm Debug setting
 *
 * @param   *pstParams [in/out] LX_PE_DBG_SETTINGS_T int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_O22_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CCM_HW_O22_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CCM)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_ccm_hw_o22_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CCM)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if(PE_KDRV_VER_O22)
			{
				PE_CCM_HW_O22_DBG_PRINT("not supported.\n");
			}
			else
			{
				PE_CCM_HW_O22_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}

/**
 * set pixel replacement
 *
 * @param   *pstParams [in/out] LX_PE_CCM_PIXEL_REPLACE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_O22_SetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	UINT32 pxl_en,r_rep_off,g_rep_off,b_rep_off,cflter_state;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CCM_HW_O22_DBG_PRINT("set[%d] : r:%d,g:%d,b:%d\n",pstParams->win_id,\
			pstParams->pxl_rep_r,pstParams->pxl_rep_g,pstParams->pxl_rep_b);
		r_rep_off = (pstParams->pxl_rep_r)? 0x0:0x1;
		g_rep_off = (pstParams->pxl_rep_g)? 0x0:0x1;
		b_rep_off = (pstParams->pxl_rep_b)? 0x0:0x1;
		pxl_en = (pstParams->pxl_rep_r | pstParams->pxl_rep_g | pstParams->pxl_rep_b)? 0x1:0x0;
		if(PE_KDRV_VER_O22)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* 0x0~0x2:off,r,g,b */
				cflter_state = (!pxl_en)? 0x0:(!pstParams->pxl_rep_r)? 0x1:\
					(!pstParams->pxl_rep_g)? 0x2:0x3;
				ret = PE_FWI_O22_SetColorFilter(cflter_state);
		PE_CCM_HW_O22_DBG_PRINT("set[%d] : flt_status:%d\n",pstParams->win_id,\
			cflter_state);
				PE_CCM_HW_O22_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_O22_SetColorFilter() error.\n", __F__, __L__);
				PE_CE_PE1_O22_QWr01(pe1_fsw_ctrl_00,reg_color_filter_status,cflter_state);
			}
		}
		else
		{
			PE_CCM_HW_O22_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}
/**
 * get pixel replacement
 *
 * @param   *pstParams [in/out] LX_PE_CCM_PIXEL_REPLACE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_O22_GetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O22_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 cflter_state=0;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O22)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_O22_QRd01(pe1_fsw_ctrl_00,reg_color_filter_status,cflter_state);
			}
		}
		else
		{
			PE_CCM_HW_O22_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		pstParams->pxl_rep_r = (cflter_state==0x1)? 0x1:0x0;
		pstParams->pxl_rep_g = (cflter_state==0x2)? 0x1:0x0;
		pstParams->pxl_rep_b = (cflter_state==0x3)? 0x1:0x0;
		PE_CCM_HW_O22_DBG_PRINT("get[%d] : r:%d, g:%d, b:%d\n", pstParams->win_id, \
			pstParams->pxl_rep_r, pstParams->pxl_rep_g, pstParams->pxl_rep_b);
	}while(0);
	#endif /*PE_HW_O22_BRINGUP*/
	return ret;
}

/**
 * set auto correction
 *
 * @param   *pstParams [in/out] LX_PE_CCM_AUTO_CR_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */

