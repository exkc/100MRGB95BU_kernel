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

/** @file pe_win.c
 *
 *  driver for picture enhance window control functions. ( used only within kdriver )
 *	- control window of each pe module
 *
 *	@author			Seung-Jun,Youm(sj.youm@lge.com)
 *  @modifier		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *	@version		0.1
 *	@note
 *	@date			2011.06.11
 *  @modified date  2015.06.18 for SWMD
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

#include "pe_hw_o26.h"
#include "pe_reg_o26.h"
#include "pe_tsk_o26.h"
#include "pe_win_hw_o26.h"
#include "pe_hst_hw_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* Enabling this macro will DISABLE LGSI code refactoring changes, so enable only if there is
any issue in LGSI refactored code. This provision is only for cross checking with original
source. It can be removed in the next version of the code*/

#define PE_WIN_HW_O26_UHD_H_MAX			3840
#define PE_WIN_HW_O26_UHD_V_MAX			2160
#define PE_WIN_HW_O26_FHD_H_MAX			1920
#define PE_WIN_HW_O26_FHD_V_MAX			1080
#define PE_WIN_HW_O26_SHP_WIN			0
#define PE_WIN_HW_O26_CEN_WIN			1
#define PE_WIN_HW_O26_WIN_EN_OFF		0
#define PE_WIN_HW_O26_WIN_EN__ON		1
#define PE_WIN_HW_O26_P1SHP_WIN_OFST	64

#define PE_WIN_HW_O26_WIN_OFFSET_MAX	(4)

/* 20140305, sj.youm, use win0 for lrcr win because of single path */
#define PE_WIN_HW_O26A_USE_WIN_0_ONLY

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_WIN_HW_O26_ERROR	printk

#define PE_WIN_HW_O26_DBG_PRINT(fmt,args...)	\
	if(_g_win_hw_o26_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_WIN_HW_O26_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_WIN_HW_O26_ERROR(fmt,##args);_action;}}

#define PE_WIN_HW_O26_DIVIDE(x,y)	(((((x)<<10)/y)+512)>>10)

#define PE_WIN_HW_O26_DBG_PRINT_ALWAYS(fmt,args...)	\
	 printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32 h_max;
	UINT32 v_max;
	UINT32 x0[LX_PE_WIN_NUM];
	UINT32 y0[LX_PE_WIN_NUM];
	UINT32 x1[LX_PE_WIN_NUM];
	UINT32 y1[LX_PE_WIN_NUM];
	UINT32 x0_ofst[LX_PE_WIN_NUM];
	UINT32 y0_ofst[LX_PE_WIN_NUM];
	UINT32 x1_ofst[LX_PE_WIN_NUM];
	UINT32 y1_ofst[LX_PE_WIN_NUM];
	UINT32 is_invalid_size[LX_PE_WIN_NUM];
}LX_PE_WIN_PARAMS_T;

typedef struct
{
	UINT32 act0_x0;
	UINT32 act0_y0;
	UINT32 act0_x1;
	UINT32 act0_y1;
	UINT32 act1_x0;
	UINT32 act1_y0;
	UINT32 act1_x1;
	UINT32 act1_y1;
	UINT32 win0_x0;
	UINT32 win0_y0;
	UINT32 win0_x1;
	UINT32 win0_y1;
	UINT32 win1_x0;
	UINT32 win1_y0;
	UINT32 win1_x1;
	UINT32 win1_y1;
	/* win 2/3 */
	UINT32 act2_x0;
	UINT32 act2_y0;
	UINT32 act2_x1;
	UINT32 act2_y1;
	UINT32 act3_x0;
	UINT32 act3_y0;
	UINT32 act3_x1;
	UINT32 act3_y1;
	UINT32 win2_x0;
	UINT32 win2_y0;
	UINT32 win2_x1;
	UINT32 win2_y1;
	UINT32 win3_x0;
	UINT32 win3_y0;
	UINT32 win3_x1;
	UINT32 win3_y1;

}LX_PE_ACT_WIN_COORDINATES_T;

typedef struct
{
	UINT32 cur_histo_l_win[4];
	UINT32 cur_histo_r_win[4];
	UINT32 cur_apply_r_win[4];

}LX_PE_HISTO_PARAMS_T;

typedef struct
{
	UINT32 win0_en[2];	//[0]:shp, [1]:cen
	UINT32 win1_en[2];	//[0]:shp, [1]:cen
	UINT32 win01_en[2];	//[0]:shp, [1]:cen

}LX_PE_SHP_CEN_WIN_EN_T;

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
__attribute__((unused)) static void PE_WIN_HW_O26_SetVerWinReverse(UINT32 *y0,UINT32 *y1,UINT32 v_max);
__attribute__((unused)) static void PE_WIN_HW_O26_GetWinParams(PE_TSK_O26_CFG_T *i_pstCfg, LX_PE_WIN_PARAMS_T *o_pstWinPrms);
__attribute__((unused)) static void PE_WIN_HW_O26_GetActNWinCrdsForExtFRC(PE_TSK_O26_CFG_T 			*i_pstCfg,
												LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
												LX_PE_ACT_WIN_COORDINATES_T *o_pstActWinCrds);
__attribute__((unused)) static void PE_WIN_HW_O26_GetShpCenWinEnForExtFRC(PE_TSK_O26_CFG_T 		*i_pstCfg,
												BOOLEAN					i_bIsResizeSet,
												LX_PE_SHP_CEN_WIN_EN_T	*o_pstShpCenWinEn);
__attribute__((unused)) static void PE_WIN_HW_O26_ValidateWinCoords(LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
											LX_PE_ACT_WIN_COORDINATES_T *io_pstActWinCrds);
__attribute__((unused)) static void PE_WIN_HW_O26_SetCen(PE_TSK_O26_CFG_T 				*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 	*i_pstActWinCrds);
__attribute__((unused)) static void PE_WIN_HW_O26_SetShp(PE_TSK_O26_CFG_T 				*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds);
__attribute__((unused)) static void PE_WIN_HW_O26_SetShpWinEn(PE_TSK_O26_CFG_T 				*i_pstCfg,
									 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
									 LX_PE_SHP_CEN_WIN_EN_T 		*i_pstShpCenWinEn);
__attribute__((unused)) static void PE_WIN_HW_O26_SetCenWinEn(PE_TSK_O26_CFG_T 				*i_pstCfg,
									 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
									 LX_PE_SHP_CEN_WIN_EN_T 		*i_pstShpCenWinEn);
__attribute__((unused)) static void PE_WIN_HW_O26_SetWinResolution(PE_TSK_O26_CFG_T 			*i_pstCfg,
										   LX_PE_WIN_PARAMS_T 			*i_pstWinPrms);

__attribute__((unused)) static void PE_WIN_HW_O26_SetDc(PE_TSK_O26_CFG_T 					*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds);
__attribute__((unused)) static void PE_WIN_HW_O26_SetPcc(PE_TSK_O26_CFG_T 					*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds);
__attribute__((unused)) static void PE_WIN_HW_O26_GetWinLeftOfst(UINT16 x_ofst,UINT16 y_ofst, LX_PE_WIN_PARAMS_T *o_pstWinPrms, UINT32 win_id);
__attribute__((unused)) static void PE_WIN_HW_O26_GetWinRightOfst(UINT16 x_ofst,UINT16 y_ofst, UINT16 x_size, UINT16 y_size, LX_PE_WIN_PARAMS_T *o_pstWinPrms, UINT32 win_id);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static UINT32 _g_win_hw_o26_trace=0x0;	//default should be off.
__attribute__((unused)) static PE_WIN_HW_O26_SETTINGS_T _g_pe_win_hw_o26_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init pe window
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_HW_O26_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	PE_REG_O26_HW_OPT_T hw_opt;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			memset(&_g_pe_win_hw_o26_info,-1,sizeof(PE_WIN_HW_O26_SETTINGS_T));
			PE_WIN_HW_O26_DBG_PRINT("pe1 win ctrl init, inside.\n");
			hw_opt = PE_REG_O26_GetDispOpt();
			if (hw_opt.external_chip ==0  || hw_opt.external_chip==2) //onechip model(0) or KDL model(2)
			{
				_g_pe_win_hw_o26_info.is_external_chip = 0;
			}
			else //8k model
			{
				_g_pe_win_hw_o26_info.is_external_chip = 1;
			}
			//_g_pe_win_hw_o26_info.is_external_chip = hw_opt.external_chip;
			/*esf*/
			PE_VSD_SHP_O26_QWr05(shp_esf_win_ctrl_00, 		reg_win_esf_win0_en,0x1, \
                                                        reg_win_esf_win1_en,0x1, \
                                                        reg_win_esf_win01_en,0x1, \
                                                        reg_win_esf_win_en,0x1, \
                                                        reg_win_esf_win_outside,0x0);
			/*dp*/
			PE_VSD_SHP_O26_QWr05(shp_dp_win_ctrl_00, reg_win_dp_win0_en,0x1, \
                                                  	   reg_win_dp_win1_en,0x1, \
                                                  	   reg_win_dp_win01_en,0x1, \
                                                  	   reg_win_dp_win_en,0x1, \
                                                  	   reg_win_dp_win_outside,0x0);
			/*dj*/
			PE_VSD_SHP_O26_QWr05(shp_dj_win_ctrl_00, reg_win_dj_win0_en,0x1, \
                                                  	   reg_win_dj_win1_en,0x1, \
                                                  	   reg_win_dj_win01_en,0x1, \
                                                  	   reg_win_dj_win_en,0x1, \
                                                  	   reg_win_dj_win_outside,0x0);
			/*cco*/
			PE_CC_PE1_O26_QWr05(pe1_win2_ctrl_00,	win0_en,0x1, \
                                                    win1_en,0x1, \
                                                    win01_en,0x1, \
                                                    win_en,0x1, \
                                                    win_outside,0x0);
			//temporally
			PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_06,	win_w0_x1_1,(PE_WIN_HW_O26_FHD_H_MAX-1),\
													win_w0_y1_1,(PE_WIN_HW_O26_UHD_V_MAX-1));

			PE_CC_PE1_O26_RdFL(pcc_winctrl_20);
			PE_CC_PE1_O26_Wr01(pcc_winctrl_20,	reg_priority_sel0,		0x1);
			PE_CC_PE1_O26_Wr01(pcc_winctrl_20,	reg_priority_sel1,		0x0);
			PE_CC_PE1_O26_Wr01(pcc_winctrl_20,	reg_priority_sel2,		0x2);
			PE_CC_PE1_O26_Wr01(pcc_winctrl_20,	reg_priority_sel3,		0x3);
			PE_CC_PE1_O26_WrFL(pcc_winctrl_20);
		}
		else
		{
			PE_WIN_HW_O26_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_HW_O26_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_WIN_HW_O26_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(WIN)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_win_hw_o26_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(WIN)))? 0x1:0x0;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set vertical window reverse
 *
 * @param   on_off [in] UINT8
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_SetVerWinReverse(UINT32 *y0,UINT32 *y1,UINT32 v_max)
{
	UINT32 cur_y0 = *y0;
	UINT32 cur_y1 = *y1;
	*y0 = (v_max-1)-cur_y1;
	*y1 = (v_max-1)-cur_y0;
	return;
}
/**
 * set pe window periodically
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_HW_O26_SetEnhancingWindow(PE_TSK_O26_CFG_T *pCfg)
{
	int ret 						= RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 							is_resize_case;
	LX_PE_WIN_PARAMS_T 				stWinPrms;
	LX_PE_ACT_WIN_COORDINATES_T 	stActWinCrds;
	LX_PE_SHP_CEN_WIN_EN_T			stShpCenWinEn;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl1_info 	= &pCfg->inf.ctrl_info[LX_PE_WIN_1];

	do {

		CHECK_KNULL(pCfg);

		if(PE_KDRV_VER_O26) {

			PE_WIN_HW_O26_GetWinParams(pCfg, &stWinPrms);

			PE_WIN_HW_O26_GetActNWinCrdsForExtFRC(pCfg, &stWinPrms, &stActWinCrds);

			/* reverse mode */
			if(disp0_info->mode.is_reverse)	{
				PE_WIN_HW_O26_SetVerWinReverse(&stActWinCrds.act0_y0, &stActWinCrds.act0_y1, stWinPrms.v_max);
				PE_WIN_HW_O26_SetVerWinReverse(&stActWinCrds.act1_y0, &stActWinCrds.act1_y1, stWinPrms.v_max);
				PE_WIN_HW_O26_SetVerWinReverse(&stActWinCrds.win0_y0, &stActWinCrds.win0_y1, stWinPrms.v_max);
				PE_WIN_HW_O26_SetVerWinReverse(&stActWinCrds.win1_y0, &stActWinCrds.win1_y1, stWinPrms.v_max);
			}

			/* 20130206, sj.youm, check resize_case that is resize(ctrl1 hv_same) and not file/photo play */
			is_resize_case = ((ctrl1_info->hv_same) && \
				!(disp0_info->src_type==LX_PE_SRC_DTV&&(disp0_info->dtv_type==LX_PE_DTV_FILEPLAY || \
				disp0_info->dtv_type==LX_PE_DTV_PHOTOPLAY)))? 1:0;

			/* win enable [0]:shp win, [1]:cen win */
			/* 20130130, sj.youm, on shp,cen win for split window because of function enable */
			/* 20130206, sj.youm, off shp, on cen win for resize(non pip) because of shp artifact */
			PE_WIN_HW_O26_GetShpCenWinEnForExtFRC(pCfg, is_resize_case, &stShpCenWinEn);

			/* 20130221, sj.youm, check valid window coordinate */
			PE_WIN_HW_O26_ValidateWinCoords(&stWinPrms, &stActWinCrds);

			/* set act(pcc) */
			PE_WIN_HW_O26_SetPcc(pCfg, &stWinPrms, &stActWinCrds);

			/* set act(cen) */
			PE_WIN_HW_O26_SetCen(pCfg, &stWinPrms, &stActWinCrds);

			/* set act(dc) */
			PE_WIN_HW_O26_SetDc(pCfg, &stWinPrms, &stActWinCrds);

			/* set win(shp) */
			PE_WIN_HW_O26_SetShp(pCfg, &stWinPrms, &stActWinCrds);

			/* shp win en */
			PE_WIN_HW_O26_SetShpWinEn(pCfg, &stWinPrms, &stShpCenWinEn);

			/* cen win en */
			PE_WIN_HW_O26_SetCenWinEn(pCfg, &stWinPrms, &stShpCenWinEn);

			/* etc */
			PE_WIN_HW_O26_SetWinResolution(pCfg, &stWinPrms);

		} else {

			PE_WIN_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}

	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_WIN_HW_O26_GetCurWinSettings(PE_WIN_HW_O26_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	PE_WIN_HW_O26_SETTINGS_T *pInfo = &_g_pe_win_hw_o26_info;
	PE_WIN_HW_O26_CTRL_T *win_info = &_g_pe_win_hw_o26_info.win_inf;
	__attribute__((unused)) PE_WIN_HW_O26_LRCR_CTRL_T *lrcr_info = &_g_pe_win_hw_o26_info.lrcr_inf;
	PE_WIN_HW_O26_TNR_CTRL_T *tnr_info = &_g_pe_win_hw_o26_info.tnr_inf;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			memcpy(pstParams,pInfo,sizeof(PE_WIN_HW_O26_SETTINGS_T));
			PE_WIN_HW_O26_DBG_PRINT("act0:%d,%d,%d,%d, act1:%d,%d,%d,%d\n",\
				win_info->act0_x0,win_info->act0_y0,win_info->act0_x1,win_info->act0_y1,\
				win_info->act1_x0,win_info->act1_y0,win_info->act1_x1,win_info->act1_y1);
			PE_WIN_HW_O26_DBG_PRINT("act2:%d,%d,%d,%d, act3:%d,%d,%d,%d\n",\
				win_info->act2_x0,win_info->act2_y0,win_info->act2_x1,win_info->act2_y1,\
				win_info->act3_x0,win_info->act3_y0,win_info->act3_x1,win_info->act3_y1);
			PE_WIN_HW_O26_DBG_PRINT("win0:%d,%d,%d,%d, win1:%d,%d,%d,%d\n",\
				win_info->win0_x0,win_info->win0_y0,win_info->win0_x1,win_info->win0_y1,\
				win_info->win1_x0,win_info->win1_y0,win_info->win1_x1,win_info->win1_y1);
			PE_WIN_HW_O26_DBG_PRINT("h,v_max:%d,%d, w0,w1,w01_en:[%d,%d],[%d,%d],[%d,%d]\n",\
				win_info->h_max,win_info->v_max,win_info->win0_en[0],win_info->win0_en[1],\
				win_info->win1_en[0],win_info->win1_en[1],win_info->win01_en[0],win_info->win01_en[1]);
			PE_WIN_HW_O26_DBG_PRINT("tnr win h,v size0:%d,%d, size1:%d,%d\n",\
				tnr_info->h_size0,tnr_info->v_size0,tnr_info->h_size1,tnr_info->v_size1);
		}
		else
		{
			PE_WIN_HW_O26_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * Gets window params
 *
 * @param   *i_pstCfg		[in] 	PE_TSK_O26_CFG_T
 * @param   *o_pstWinPrms	[out]	LX_PE_WIN_PARAMS_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_GetWinParams(PE_TSK_O26_CFG_T *i_pstCfg, LX_PE_WIN_PARAMS_T *o_pstWinPrms)
{
	#ifdef PE_HW_O26_BRINGUP
	UINT16 x_ofst[4];
	UINT16 y_ofst[4];
	UINT16 x_size[4];
	UINT16 y_size[4];
	UINT16 x_end_ofst[4];
	UINT16 y_end_ofst[4];
	UINT8  win_path_en[4];
	UINT8  use_vlb;
	UINT8  use_vcp;
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp1_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_1];
	//__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	//__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_REG_O26_HW_OPT_T hw_opt = PE_REG_O26_GetDispOpt();
	PE_FMC_VERI_O26_QRd02(sys_veri_0, use_vlb, use_vlb, use_vcp, use_vcp);
	if(use_vlb == 1) // use_vlb case - multiview
	{
		PE_VLB_O26_QRd02(reg_vlb_ctrl_07,		reg_l0_sp_x, x_ofst[0],\
												reg_l0_ep_x, x_end_ofst[0]);
		PE_VLB_O26_QRd02(reg_vlb_ctrl_08,		reg_l0_sp_y, y_ofst[0],\
												reg_l0_ep_y, y_end_ofst[0]);
		x_size[0]  = x_ofst[0] > x_end_ofst[0]? 0:(x_end_ofst[0] - x_ofst[0] + 1);
		y_size[0]  = y_ofst[0] > y_end_ofst[0]? 0:(y_end_ofst[0] - y_ofst[0] + 1);

		PE_VLB_O26_QRd02(reg_vlb_ctrl_09,		reg_l1_sp_x, x_ofst[1],\
												reg_l1_ep_x, x_end_ofst[1]);
		PE_VLB_O26_QRd02(reg_vlb_ctrl_10,		reg_l1_sp_y, y_ofst[1],\
												reg_l1_ep_y, y_end_ofst[1]);
		x_size[1] = x_ofst[1] > x_end_ofst[1]? 0:(x_end_ofst[1] - x_ofst[1] + 1);
		y_size[1] = y_ofst[1] > y_end_ofst[1]? 0:(y_end_ofst[1] - y_ofst[1] + 1);

		PE_VLB_O26_QRd02(reg_vlb_ctrl_11,		reg_l2_sp_x, x_ofst[2],\
												reg_l2_ep_x, x_end_ofst[2]);
		PE_VLB_O26_QRd02(reg_vlb_ctrl_12,		reg_l2_sp_y, y_ofst[2],\
												reg_l2_ep_y, y_end_ofst[2]);
		x_size[2]  = x_ofst[2] > x_end_ofst[2]? 0:(x_end_ofst[2] - x_ofst[2] + 1);
		y_size[2]  = y_ofst[2] > y_end_ofst[2]? 0:(y_end_ofst[2] - y_ofst[2] + 1);
		
		PE_VLB_O26_QRd02(reg_vlb_ctrl_13,		reg_l3_sp_x, x_ofst[3],\
												reg_l3_ep_x, x_end_ofst[3]);
		PE_VLB_O26_QRd02(reg_vlb_ctrl_14,		reg_l3_sp_y, y_ofst[3],\
												reg_l3_ep_y, y_end_ofst[3]);
		x_size[3]  = x_ofst[3] > x_end_ofst[3]? 0:(x_end_ofst[3] - x_ofst[3] + 1);
		y_size[3]  = y_ofst[3] > y_end_ofst[3]? 0:(y_end_ofst[3] - y_ofst[3] + 1);
		/* video path enable check */
		PE_VLB_O26_QRd04(reg_vlb_ctrl_00,	reg_l0_en, win_path_en[0],\
											reg_l1_en, win_path_en[1],\
											reg_l2_en, win_path_en[2],\
											reg_l3_en, win_path_en[3]);
		/* invalid size check */
		o_pstWinPrms->is_invalid_size[LX_PE_WIN_0] = \
			(x_size[0] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1) || \
			x_size[0] > (PE_WIN_HW_O26_UHD_H_MAX+100)       || \
			y_size[0] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1)  || \
			!win_path_en[0])? 1:0;
		o_pstWinPrms->is_invalid_size[LX_PE_WIN_1] = \
			(x_size[1] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1) || \
			x_size[1] > (PE_WIN_HW_O26_UHD_H_MAX+100)       || \
			y_size[1] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1)  || \
			!win_path_en[1])? 1:0;
		o_pstWinPrms->is_invalid_size[LX_PE_WIN_2] = \
			(x_size[2] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1) || \
			x_size[2] > (PE_WIN_HW_O26_UHD_H_MAX+100)       || \
			y_size[2] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1)  || \
			!win_path_en[2])? 1:0;
		o_pstWinPrms->is_invalid_size[LX_PE_WIN_3] = \
			(x_size[3] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1) || \
			x_size[3] > (PE_WIN_HW_O26_UHD_H_MAX+100)       || \
			y_size[3] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1)  || \
			!win_path_en[3])? 1:0;
	}
	else
	{
		PE_VCP_DISP_O26_QRd02(vcp_u0_win_o_pos,		cdc_win_o_pos_x, x_ofst[0],\
												 	cdc_win_o_pos_y, y_ofst[0]);
		
		PE_VCP_DISP_O26_QRd02(vcp_u0_win_o_size,	cdc_win_o_size_x, x_size[0],\
													cdc_win_o_size_y, y_size[0]);

		PE_VCP_DISP_O26_QRd02(vcp_u1_win_o_pos,		cdc_win_o_pos_x,  x_ofst[1],\
												 	cdc_win_o_pos_y,  y_ofst[1]);
		PE_VCP_DISP_O26_QRd02(vcp_u1_win_o_size,	cdc_win_o_size_x, x_size[1],\
													cdc_win_o_size_y, y_size[1]);
		x_size[2]  = x_ofst[2] = 0;
		y_size[2]  = y_ofst[2] = 0;
		x_size[3]  = x_ofst[3] = 0;
		y_size[3]  = y_ofst[3] = 0;
		
		/* invalid size check */
		o_pstWinPrms->is_invalid_size[LX_PE_WIN_0] = \
			(x_size[0] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1) || \
			x_size[0] > (PE_WIN_HW_O26_UHD_H_MAX+100)		|| \
			y_size[0] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1))? 1:0;
		o_pstWinPrms->is_invalid_size[LX_PE_WIN_1] = \
			(x_size[1] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1) || \
			x_size[1] > (PE_WIN_HW_O26_UHD_H_MAX+100)		|| \
			y_size[1] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1))? 1:0;
		o_pstWinPrms->is_invalid_size[LX_PE_WIN_2] = \
			(x_size[2] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1) || \
			x_size[2] > (PE_WIN_HW_O26_UHD_H_MAX+100)		|| \
			y_size[2] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1))? 1:0;
		o_pstWinPrms->is_invalid_size[LX_PE_WIN_3] = \
			(x_size[3] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1) || \
			x_size[3] > (PE_WIN_HW_O26_UHD_H_MAX+100)		|| \
			y_size[3] <= (PE_WIN_HW_O26_WIN_OFFSET_MAX<<1))? 1:0;
	}
	#if 0
	printk("x_size:%d,%d,%d,%d, y_size:%d,%d,%d,%d\n",\
		x_size[0],x_size[1],x_size[2],x_size[3],\
		y_size[0],y_size[1],y_size[2],y_size[3]);
	
	printk("x_ofst:%d,%d,%d,%d, y_ofst:%d,%d,%d,%d\n",\
		x_ofst[0],x_ofst[1],x_ofst[2],x_ofst[3],\
		y_ofst[0],y_ofst[1],y_ofst[2],y_ofst[3]);
	#endif
	if(hw_opt.panel_resolution== 1) // fulL-hd 1920,1080
	{
		o_pstWinPrms->h_max=PE_WIN_HW_O26_FHD_H_MAX;
		o_pstWinPrms->v_max=PE_WIN_HW_O26_FHD_V_MAX;
	}
	else // 4k 3840x2160
	{
		o_pstWinPrms->h_max=PE_WIN_HW_O26_UHD_H_MAX;
		o_pstWinPrms->v_max=PE_WIN_HW_O26_UHD_V_MAX;
	}
	#if 0
	printk("is_invalid_size:%d,%d,%d,%d\n",\
			o_pstWinPrms->is_invalid_size[LX_PE_WIN_0],o_pstWinPrms->is_invalid_size[LX_PE_WIN_1],\
			o_pstWinPrms->is_invalid_size[LX_PE_WIN_2],o_pstWinPrms->is_invalid_size[LX_PE_WIN_3]);
	#endif
	/* left ofst*/
	PE_WIN_HW_O26_GetWinLeftOfst(x_ofst[0], y_ofst[0],o_pstWinPrms,LX_PE_WIN_0);
	PE_WIN_HW_O26_GetWinLeftOfst(x_ofst[1], y_ofst[1],o_pstWinPrms,LX_PE_WIN_1);
	PE_WIN_HW_O26_GetWinLeftOfst(x_ofst[2], y_ofst[2],o_pstWinPrms,LX_PE_WIN_2);
	PE_WIN_HW_O26_GetWinLeftOfst(x_ofst[3], y_ofst[3],o_pstWinPrms,LX_PE_WIN_3);
	#if 0
	if(x_ofst[0] == 0x0)//if no margin for orbit, then no offset for shp
	{
		o_pstWinPrms->x0_ofst[LX_PE_WIN_0] = 0;
	}
	else
	{
		o_pstWinPrms->x0_ofst[LX_PE_WIN_0] = 6;
	}

	if(y_ofst[0] == 0x0)//if no margin for orbit, then no offset for shp
	{
		o_pstWinPrms->y0_ofst[LX_PE_WIN_0]= 0;
	}
	else
	{
		o_pstWinPrms->y0_ofst[LX_PE_WIN_0]= 3;
	}
	#endif

	/* right ofst*/
	PE_WIN_HW_O26_GetWinRightOfst(x_ofst[0], y_ofst[0],x_size[0],y_size[0],o_pstWinPrms,LX_PE_WIN_0);
	PE_WIN_HW_O26_GetWinRightOfst(x_ofst[1], y_ofst[1],x_size[1],y_size[1],o_pstWinPrms,LX_PE_WIN_1);
	PE_WIN_HW_O26_GetWinRightOfst(x_ofst[2], y_ofst[2],x_size[2],y_size[2],o_pstWinPrms,LX_PE_WIN_2);
	PE_WIN_HW_O26_GetWinRightOfst(x_ofst[3], y_ofst[3],x_size[3],y_size[3],o_pstWinPrms,LX_PE_WIN_3);
	#if 0
	if((x_ofst[0]+x_size[0])<o_pstWinPrms->h_max)//offset for shp
	{
		o_pstWinPrms->x1_ofst[LX_PE_WIN_0] = 6;
	}
	else										// no offset
	{
		o_pstWinPrms->x1_ofst[LX_PE_WIN_0] = 0;
	}
	if((y_ofst[0]+y_size[0])<o_pstWinPrms->v_max)//offset for shp
	{
		o_pstWinPrms->y1_ofst[LX_PE_WIN_0] = 3;
	}
	else										// no offset
	{
		o_pstWinPrms->y1_ofst[LX_PE_WIN_0] = 0;
	}
	#endif
	/* 20130121, sj.youm, add photo case because of slide show */
	if(o_pstWinPrms->is_invalid_size[LX_PE_WIN_0] || \
		(disp0_info->src_type==LX_PE_SRC_DTV && \
		disp0_info->dtv_type==LX_PE_DTV_PHOTOPLAY)) 
	{
		o_pstWinPrms->x0[LX_PE_WIN_0] = 0;
		o_pstWinPrms->y0[LX_PE_WIN_0] = 0;
		o_pstWinPrms->x1[LX_PE_WIN_0] = o_pstWinPrms->h_max-1;
		o_pstWinPrms->y1[LX_PE_WIN_0] = o_pstWinPrms->v_max-1;
	} 
	else 
	{
		o_pstWinPrms->x0[LX_PE_WIN_0] = x_ofst[0];
		o_pstWinPrms->y0[LX_PE_WIN_0] = y_ofst[0];
		o_pstWinPrms->x1[LX_PE_WIN_0] = x_ofst[0]+x_size[0]-1;
		o_pstWinPrms->y1[LX_PE_WIN_0] = y_ofst[0]+y_size[0]-1;
	}

	if(o_pstWinPrms->is_invalid_size[LX_PE_WIN_1] )
	{
		o_pstWinPrms->x0[LX_PE_WIN_1] = 0;
		o_pstWinPrms->y0[LX_PE_WIN_1] = 0;
		o_pstWinPrms->x1[LX_PE_WIN_1] = 0;
		o_pstWinPrms->y1[LX_PE_WIN_1] = 0;
	} 
	else 
	{
		o_pstWinPrms->x0[LX_PE_WIN_1] = x_ofst[1];
		o_pstWinPrms->y0[LX_PE_WIN_1] = y_ofst[1];
		o_pstWinPrms->x1[LX_PE_WIN_1] = x_ofst[1]+x_size[1]-1;
		o_pstWinPrms->y1[LX_PE_WIN_1] = y_ofst[1]+y_size[1]-1;
	}
	
	if(o_pstWinPrms->is_invalid_size[LX_PE_WIN_2])
	{
		o_pstWinPrms->x0[LX_PE_WIN_2] = 0;
		o_pstWinPrms->y0[LX_PE_WIN_2] = 0;
		o_pstWinPrms->x1[LX_PE_WIN_2] = 0;
		o_pstWinPrms->y1[LX_PE_WIN_2] = 0;
	} 
	else 
	{
		o_pstWinPrms->x0[LX_PE_WIN_2] = x_ofst[2];
		o_pstWinPrms->y0[LX_PE_WIN_2] = y_ofst[2];
		o_pstWinPrms->x1[LX_PE_WIN_2] = x_ofst[2]+x_size[2]-1;
		o_pstWinPrms->y1[LX_PE_WIN_2] = y_ofst[2]+y_size[2]-1;
	}
	
	if(o_pstWinPrms->is_invalid_size[LX_PE_WIN_3])
	{
		o_pstWinPrms->x0[LX_PE_WIN_3] = 0;
		o_pstWinPrms->y0[LX_PE_WIN_3] = 0;
		o_pstWinPrms->x1[LX_PE_WIN_3] = 0;
		o_pstWinPrms->y1[LX_PE_WIN_3] = 0;
	} 
	else 
	{
		o_pstWinPrms->x0[LX_PE_WIN_3] = x_ofst[3];
		o_pstWinPrms->y0[LX_PE_WIN_3] = y_ofst[3];
		o_pstWinPrms->x1[LX_PE_WIN_3] = x_ofst[3]+x_size[3]-1;
		o_pstWinPrms->y1[LX_PE_WIN_3] = y_ofst[3]+y_size[3]-1;
	}
	#if 0
	printk("[PE_WIN_HW_O26_GetWinParams]o_pstWinPrms->w[0]:%d,%d,%d,%d, o_pstWinPrms->w[1]:%d,%d,%d,%d\n",\
		o_pstWinPrms->x0[LX_PE_WIN_0],o_pstWinPrms->y0[LX_PE_WIN_0],o_pstWinPrms->x1[LX_PE_WIN_0],o_pstWinPrms->y1[LX_PE_WIN_0],\
		o_pstWinPrms->x0[LX_PE_WIN_1],o_pstWinPrms->y0[LX_PE_WIN_1],o_pstWinPrms->x1[LX_PE_WIN_1],o_pstWinPrms->y1[LX_PE_WIN_1]);
	printk("o_pstWinPrms->w[2]:%d,%d,%d,%d, o_pstWinPrms->w[3]:%d,%d,%d,%d\n",\
		o_pstWinPrms->x0[LX_PE_WIN_2],o_pstWinPrms->y0[LX_PE_WIN_2],o_pstWinPrms->x1[LX_PE_WIN_2],o_pstWinPrms->y1[LX_PE_WIN_2],\
		o_pstWinPrms->x0[LX_PE_WIN_3],o_pstWinPrms->y0[LX_PE_WIN_3],o_pstWinPrms->x1[LX_PE_WIN_3],o_pstWinPrms->y1[LX_PE_WIN_3]);
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

__attribute__((unused)) static void PE_WIN_HW_O26_GetWinLeftOfst(UINT16 x_ofst,UINT16 y_ofst, LX_PE_WIN_PARAMS_T *o_pstWinPrms, UINT32 win_id)
{
	if(x_ofst == 0x0)//if no margin for orbit, then no offset for shp
	{
		o_pstWinPrms->x0_ofst[win_id] = 0;
	}
	else
	{
		o_pstWinPrms->x0_ofst[win_id] = 6;
	}

	if(y_ofst == 0x0)//if no margin for orbit, then no offset for shp
	{
		o_pstWinPrms->y0_ofst[win_id]= 0;
	}
	else
	{
		o_pstWinPrms->y0_ofst[win_id]= 3;
	}
}

__attribute__((unused)) static void PE_WIN_HW_O26_GetWinRightOfst(UINT16 x_ofst,UINT16 y_ofst, UINT16 x_size,UINT16 y_size, LX_PE_WIN_PARAMS_T *o_pstWinPrms, UINT32 win_id)
{
	if((x_ofst+x_size)<o_pstWinPrms->h_max)//offset for shp
	{
		o_pstWinPrms->x1_ofst[win_id] = 6;
	}
	else										// no offset
	{
		o_pstWinPrms->x1_ofst[win_id] = 0;
	}
	if((y_ofst+y_size)<o_pstWinPrms->v_max)//offset for shp
	{
		o_pstWinPrms->y1_ofst[win_id] = 3;
	}
	else										// no offset
	{
		o_pstWinPrms->y1_ofst[win_id] = 0;
	}
}


/**
 * Gets active window coordinates of PIP for external FRC
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in]	LX_PE_WIN_PARAMS_T
 * @param 	*o_pstActWinCrds	[out]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_GetActNWinCrdsForExtFRC_PIP(PE_TSK_O26_CFG_T 			*i_pstCfg,
													LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
													LX_PE_ACT_WIN_COORDINATES_T *o_pstActWinCrds)
{
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	//__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];

	UINT32 *x0 = i_pstWinPrms->x0;
	UINT32 *y0 = i_pstWinPrms->y0;
	UINT32 *x1 = i_pstWinPrms->x1;
	UINT32 *y1 = i_pstWinPrms->y1;
	UINT32 *x0_ofst = i_pstWinPrms->x0_ofst;
	UINT32 *y0_ofst = i_pstWinPrms->y0_ofst;
	UINT32 *x1_ofst = i_pstWinPrms->x1_ofst;
	UINT32 *y1_ofst = i_pstWinPrms->y1_ofst;

	/* L : window 0 */
	o_pstActWinCrds->act0_x0 = x0[LX_PE_WIN_0];
	o_pstActWinCrds->act0_y0 = y0[LX_PE_WIN_0];
	o_pstActWinCrds->act0_x1 = x1[LX_PE_WIN_0];
	o_pstActWinCrds->act0_y1 = y1[LX_PE_WIN_0];
	o_pstActWinCrds->win0_x0 = x0[LX_PE_WIN_0]+x0_ofst[LX_PE_WIN_0];
	o_pstActWinCrds->win0_y0 = y0[LX_PE_WIN_0]+y0_ofst[LX_PE_WIN_0];
	o_pstActWinCrds->win0_x1 = x1[LX_PE_WIN_0]-x1_ofst[LX_PE_WIN_0];
	o_pstActWinCrds->win0_y1 = y1[LX_PE_WIN_0]-y1_ofst[LX_PE_WIN_0];

	if(disp0_info->sub_mode == LX_DE_SUB_MODE_PBP || disp0_info->sub_mode == LX_DE_SUB_MODE_DUALMON)
	{

		/* L : window 1 */
		if(i_pstWinPrms->is_invalid_size[LX_PE_WIN_1])
		{

			o_pstActWinCrds->act1_x0 = 0;
			o_pstActWinCrds->act1_y0 = 0;
			o_pstActWinCrds->act1_x1 = 0;
			o_pstActWinCrds->act1_y1 = 0;
			o_pstActWinCrds->win1_x0 = 0;
			o_pstActWinCrds->win1_y0 = 0;
			o_pstActWinCrds->win1_x1 = 0;
			o_pstActWinCrds->win1_y1 = 0;
		}
		else
		{
			o_pstActWinCrds->act1_x0 = x0[LX_PE_WIN_1];
			o_pstActWinCrds->act1_y0 = y0[LX_PE_WIN_1];
			o_pstActWinCrds->act1_x1 = x1[LX_PE_WIN_1];
			o_pstActWinCrds->act1_y1 = y1[LX_PE_WIN_1];
			o_pstActWinCrds->win1_x0 = x0[LX_PE_WIN_1]+x0_ofst[LX_PE_WIN_1];
			o_pstActWinCrds->win1_y0 = y0[LX_PE_WIN_1]+y0_ofst[LX_PE_WIN_1];
			o_pstActWinCrds->win1_x1 = x1[LX_PE_WIN_1]-x1_ofst[LX_PE_WIN_1];
			o_pstActWinCrds->win1_y1 = y1[LX_PE_WIN_1]-y1_ofst[LX_PE_WIN_1];
		}
		/* L : window 2 */
		if(i_pstWinPrms->is_invalid_size[LX_PE_WIN_2])
		{

			o_pstActWinCrds->act2_x0 = 0;
			o_pstActWinCrds->act2_y0 = 0;
			o_pstActWinCrds->act2_x1 = 0;
			o_pstActWinCrds->act2_y1 = 0;
			o_pstActWinCrds->win2_x0 = 0;
			o_pstActWinCrds->win2_y0 = 0;
			o_pstActWinCrds->win2_x1 = 0;
			o_pstActWinCrds->win2_y1 = 0;
		}
		else
		{
			o_pstActWinCrds->act2_x0 = x0[LX_PE_WIN_2];
			o_pstActWinCrds->act2_y0 = y0[LX_PE_WIN_2];
			o_pstActWinCrds->act2_x1 = x1[LX_PE_WIN_2];
			o_pstActWinCrds->act2_y1 = y1[LX_PE_WIN_2];
			o_pstActWinCrds->win2_x0 = x0[LX_PE_WIN_2]+x0_ofst[LX_PE_WIN_2];
			o_pstActWinCrds->win2_y0 = y0[LX_PE_WIN_2]+y0_ofst[LX_PE_WIN_2];
			o_pstActWinCrds->win2_x1 = x1[LX_PE_WIN_2]-x1_ofst[LX_PE_WIN_2];
			o_pstActWinCrds->win2_y1 = y1[LX_PE_WIN_2]-y1_ofst[LX_PE_WIN_2];
		}
		/* L : window 3 */
		if(i_pstWinPrms->is_invalid_size[LX_PE_WIN_3])
		{

			o_pstActWinCrds->act3_x0 = 0;
			o_pstActWinCrds->act3_y0 = 0;
			o_pstActWinCrds->act3_x1 = 0;
			o_pstActWinCrds->act3_y1 = 0;
			o_pstActWinCrds->win3_x0 = 0;
			o_pstActWinCrds->win3_y0 = 0;
			o_pstActWinCrds->win3_x1 = 0;
			o_pstActWinCrds->win3_y1 = 0;
		}
		else
		{
			o_pstActWinCrds->act3_x0 = x0[LX_PE_WIN_3];
			o_pstActWinCrds->act3_y0 = y0[LX_PE_WIN_3];
			o_pstActWinCrds->act3_x1 = x1[LX_PE_WIN_3];
			o_pstActWinCrds->act3_y1 = y1[LX_PE_WIN_3];
			o_pstActWinCrds->win3_x0 = x0[LX_PE_WIN_3]+x0_ofst[LX_PE_WIN_3];
			o_pstActWinCrds->win3_y0 = y0[LX_PE_WIN_3]+y0_ofst[LX_PE_WIN_3];
			o_pstActWinCrds->win3_x1 = x1[LX_PE_WIN_3]-x1_ofst[LX_PE_WIN_3];
			o_pstActWinCrds->win3_y1 = y1[LX_PE_WIN_3]-y1_ofst[LX_PE_WIN_3];
		}

	}
	else if(disp0_info->sub_mode == LX_DE_SUB_MODE_PIP)
	{
 		/* L : window 1 */
		/* 20130218, sj.youm, add inv size to avoid main cen artifact when turn on pip */
		/* 20130221, sj.youm, add x,y comp to avoid main cen artifact when turn on pip */
		if(i_pstWinPrms->is_invalid_size[LX_PE_WIN_1])
		{
			o_pstActWinCrds->act1_x0 = 0;
			o_pstActWinCrds->act1_y0 = 0;
			o_pstActWinCrds->act1_x1 = 0;
			o_pstActWinCrds->act1_y1 = 0;
			o_pstActWinCrds->win1_x0 = 0;
			o_pstActWinCrds->win1_y0 = 0;
			o_pstActWinCrds->win1_x1 = 0;
			o_pstActWinCrds->win1_y1 = 0;
		}
		else
		{

			o_pstActWinCrds->act1_x0 = x0[LX_PE_WIN_1];
			o_pstActWinCrds->act1_y0 = y0[LX_PE_WIN_1];
			o_pstActWinCrds->act1_x1 = x1[LX_PE_WIN_1];
			o_pstActWinCrds->act1_y1 = y1[LX_PE_WIN_1];
			o_pstActWinCrds->win1_x0 = ((x0[LX_PE_WIN_1]-x0_ofst[LX_PE_WIN_1])>0)? \
				(x0[LX_PE_WIN_1]-x0_ofst[LX_PE_WIN_1]):0;
			o_pstActWinCrds->win1_y0 = ((y0[LX_PE_WIN_1]-y0_ofst[LX_PE_WIN_1])>0)? \
				(y0[LX_PE_WIN_1]-y0_ofst[LX_PE_WIN_1]):0;
			o_pstActWinCrds->win1_x1 = x1[LX_PE_WIN_1]+x1_ofst[LX_PE_WIN_1];
			o_pstActWinCrds->win1_y1 = y1[LX_PE_WIN_1]+y1_ofst[LX_PE_WIN_1];
		}
		
			o_pstActWinCrds->act2_x0 = 0;
			o_pstActWinCrds->act2_y0 = 0;
			o_pstActWinCrds->act2_x1 = 0;
			o_pstActWinCrds->act2_y1 = 0;
			o_pstActWinCrds->win2_x0 = 0;
			o_pstActWinCrds->win2_y0 = 0;
			o_pstActWinCrds->win2_x1 = 0;
			o_pstActWinCrds->win2_y1 = 0;

			o_pstActWinCrds->act3_x0 = 0;
			o_pstActWinCrds->act3_y0 = 0;
			o_pstActWinCrds->act3_x1 = 0;
			o_pstActWinCrds->act3_y1 = 0;
			o_pstActWinCrds->win3_x0 = 0;
			o_pstActWinCrds->win3_y0 = 0;
			o_pstActWinCrds->win3_x1 = 0;
			o_pstActWinCrds->win3_y1 = 0;
	}
	else//mirrormode  
	{
		
		/* L : window 0 */
		o_pstActWinCrds->act0_x0 = x0[LX_PE_WIN_0];
		o_pstActWinCrds->act0_y0 = y0[LX_PE_WIN_0];
		o_pstActWinCrds->act0_x1 = x1[LX_PE_WIN_0];
		o_pstActWinCrds->act0_y1 = y1[LX_PE_WIN_0];
		o_pstActWinCrds->win0_x0 = x0[LX_PE_WIN_0]+x0_ofst[LX_PE_WIN_0];
		o_pstActWinCrds->win0_y0 = y0[LX_PE_WIN_0]+y0_ofst[LX_PE_WIN_0];
		o_pstActWinCrds->win0_x1 = x1[LX_PE_WIN_0]-x1_ofst[LX_PE_WIN_0];
		o_pstActWinCrds->win0_y1 = y1[LX_PE_WIN_0]-y1_ofst[LX_PE_WIN_0];

		/* L : window 1 */
		/* 20130218, sj.youm, add inv size to avoid main cen artifact when turn on pip */
		/* 20130221, sj.youm, add x,y comp to avoid main cen artifact when turn on pip */
		if(i_pstWinPrms->is_invalid_size[LX_PE_WIN_1])
		{

			o_pstActWinCrds->act1_x0 = 0;
			o_pstActWinCrds->act1_y0 = 0;
			o_pstActWinCrds->act1_x1 = 0;
			o_pstActWinCrds->act1_y1 = 0;
			o_pstActWinCrds->win1_x0 = 0;
			o_pstActWinCrds->win1_y0 = 0;
			o_pstActWinCrds->win1_x1 = 0;
			o_pstActWinCrds->win1_y1 = 0;
		}
		else
		{
			o_pstActWinCrds->act1_x0 = x0[LX_PE_WIN_1];
			o_pstActWinCrds->act1_y0 = y0[LX_PE_WIN_1];
			o_pstActWinCrds->act1_x1 = x1[LX_PE_WIN_1];
			o_pstActWinCrds->act1_y1 = y1[LX_PE_WIN_1];
			o_pstActWinCrds->win1_x0 = x0[LX_PE_WIN_1]+x0_ofst[LX_PE_WIN_1];
			o_pstActWinCrds->win1_y0 = y0[LX_PE_WIN_1]+y0_ofst[LX_PE_WIN_1];
			o_pstActWinCrds->win1_x1 = x1[LX_PE_WIN_1]-x1_ofst[LX_PE_WIN_1];
			o_pstActWinCrds->win1_y1 = y1[LX_PE_WIN_1]-y1_ofst[LX_PE_WIN_1];
		}
	}
	return;
}

/**
 * Gets active window coordinates for external FRC
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in]	LX_PE_WIN_PARAMS_T
 * @param 	*o_pstActWinCrds	[out]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_GetActNWinCrdsForExtFRC(PE_TSK_O26_CFG_T 			*i_pstCfg,
												LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
												LX_PE_ACT_WIN_COORDINATES_T *o_pstActWinCrds)
{
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];

	UINT32 *x0 = i_pstWinPrms->x0;	UINT32 *y0 = i_pstWinPrms->y0;
	UINT32 *x1 = i_pstWinPrms->x1;	UINT32 *y1 = i_pstWinPrms->y1;
	UINT32 *x0_ofst = i_pstWinPrms->x0_ofst; UINT32 *y0_ofst = i_pstWinPrms->y0_ofst;
	UINT32 *x1_ofst = i_pstWinPrms->x1_ofst; UINT32 *y1_ofst = i_pstWinPrms->y1_ofst;
	//PE_REG_O26_HW_OPT_T hw_opt = PE_REG_O26_GetDispOpt();
	//211122, only 4k model sub window care, SWPRETEST-883
	if(_g_pe_win_hw_o26_info.is_external_chip==0x0 &&\
		disp0_info->sub_mode > LX_DE_SUB_MODE_NONE && disp0_info->sub_mode <LX_DE_SUB_MODE_MAXN)
	{
		PE_WIN_HW_O26_GetActNWinCrdsForExtFRC_PIP( i_pstCfg, i_pstWinPrms, o_pstActWinCrds );
	}
	else
	{
		/* window 0 */
		o_pstActWinCrds->act0_x0 = x0[LX_PE_WIN_0];
		o_pstActWinCrds->act0_y0 = y0[LX_PE_WIN_0];
		o_pstActWinCrds->act0_x1 = x1[LX_PE_WIN_0];
		o_pstActWinCrds->act0_y1 = y1[LX_PE_WIN_0];
		o_pstActWinCrds->win0_x0 = x0[LX_PE_WIN_0]+x0_ofst[LX_PE_WIN_0];
		o_pstActWinCrds->win0_y0 = y0[LX_PE_WIN_0]+y0_ofst[LX_PE_WIN_0];
		o_pstActWinCrds->win0_x1 = x1[LX_PE_WIN_0]-x1_ofst[LX_PE_WIN_0];
		o_pstActWinCrds->win0_y1 = y1[LX_PE_WIN_0]-y1_ofst[LX_PE_WIN_0];
		/* window 1 */
		o_pstActWinCrds->act1_x0 = 0;
		o_pstActWinCrds->act1_y0 = 0;
		o_pstActWinCrds->act1_x1 = 0;
		o_pstActWinCrds->act1_y1 = 0;
		o_pstActWinCrds->win1_x0 = 0;
		o_pstActWinCrds->win1_y0 = 0;
		o_pstActWinCrds->win1_x1 = 0;
		o_pstActWinCrds->win1_y1 = 0;

		o_pstActWinCrds->act2_x0 = 0;
		o_pstActWinCrds->act2_y0 = 0;
		o_pstActWinCrds->act2_x1 = 0;
		o_pstActWinCrds->act2_y1 = 0;
		o_pstActWinCrds->win2_x0 = 0;
		o_pstActWinCrds->win2_y0 = 0;
		o_pstActWinCrds->win2_x1 = 0;
		o_pstActWinCrds->win2_y1 = 0;

		o_pstActWinCrds->act3_x0 = 0;
		o_pstActWinCrds->act3_y0 = 0;
		o_pstActWinCrds->act3_x1 = 0;
		o_pstActWinCrds->act3_y1 = 0;
		o_pstActWinCrds->win3_x0 = 0;
		o_pstActWinCrds->win3_y0 = 0;
		o_pstActWinCrds->win3_x1 = 0;
		o_pstActWinCrds->win3_y1 = 0;
	}

#if 0
	printk("[PE_WIN_HW_O26_GetActNWinCrdsForExtFRC]o_pstActWinCrds->act0:%d,%d,%d,%d, o_pstActWinCrds->win0:%d,%d,%d,%d\n",\
		o_pstActWinCrds->act0_x0,o_pstActWinCrds->act0_y0,o_pstActWinCrds->act0_x1,o_pstActWinCrds->act0_y1,\
		o_pstActWinCrds->win0_x0,o_pstActWinCrds->win0_y0,o_pstActWinCrds->win0_x1,o_pstActWinCrds->win0_y1);
#endif
	return;
}

/**
 * Gets shp, cen & win enable for external FRC
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   i_bIsResizeSet		[in]	BOOLEAN
 * @param 	*o_pstShpCenWinEn	[out]	LX_PE_SHP_CEN_WIN_EN_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_GetShpCenWinEnForExtFRC(PE_TSK_O26_CFG_T 		*i_pstCfg,
												BOOLEAN					i_bIsResizeSet,
												LX_PE_SHP_CEN_WIN_EN_T	*o_pstShpCenWinEn)
{
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];

	if(disp0_info->sub_mode == LX_DE_SUB_MODE_PIP)
	{
				o_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
				o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
				o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
				o_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
				o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
				o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
	}
	else if(disp0_info->sub_mode == LX_DE_SUB_MODE_PBP || disp0_info->sub_mode == LX_DE_SUB_MODE_DUALMON)
	{
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		#if 0
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN]=(ctrl0_info->vcp_mute_on)? \
			PE_WIN_HW_O26_WIN_EN_OFF:PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
		#else
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN]= PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
		#endif
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
	}
	else if(disp0_info->sub_mode == LX_DE_SUB_MODE_MAGZOOM || disp0_info->sub_mode == LX_DE_SUB_MODE_LIVEZOOM) //mirror
	{
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
	}
	else
	{
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN]=(i_bIsResizeSet)? \
			PE_WIN_HW_O26_WIN_EN_OFF:PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_CEN_WIN]=PE_WIN_HW_O26_WIN_EN_OFF;
	} 
	return;
}

/**
 * Validates win coords
 *
 * @param   *i_pstWinPrms		[in] 		LX_PE_WIN_PARAMS_T
 * @param 	*io_pstActWinCrds	[in+out]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_ValidateWinCoords(LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
											LX_PE_ACT_WIN_COORDINATES_T 	*io_pstActWinCrds)
{
	/* check limit, x1, y1 */
	if(io_pstActWinCrds->act0_x1>=i_pstWinPrms->h_max)	io_pstActWinCrds->act0_x1=i_pstWinPrms->h_max-1;
	if(io_pstActWinCrds->act0_y1>=i_pstWinPrms->v_max)	io_pstActWinCrds->act0_y1=i_pstWinPrms->v_max-1;
	if(io_pstActWinCrds->win0_x1>=i_pstWinPrms->h_max)	io_pstActWinCrds->win0_x1=i_pstWinPrms->h_max-1;
	if(io_pstActWinCrds->win0_y1>=i_pstWinPrms->v_max)	io_pstActWinCrds->win0_y1=i_pstWinPrms->v_max-1;
	if(io_pstActWinCrds->act1_x1>=i_pstWinPrms->h_max)	io_pstActWinCrds->act1_x1=i_pstWinPrms->h_max-1;
	if(io_pstActWinCrds->act1_y1>=i_pstWinPrms->v_max)	io_pstActWinCrds->act1_y1=i_pstWinPrms->v_max-1;
	if(io_pstActWinCrds->win1_x1>=i_pstWinPrms->h_max)	io_pstActWinCrds->win1_x1=i_pstWinPrms->h_max-1;
	if(io_pstActWinCrds->win1_y1>=i_pstWinPrms->v_max)	io_pstActWinCrds->win1_y1=i_pstWinPrms->v_max-1;
	if(io_pstActWinCrds->act2_x1>=i_pstWinPrms->h_max)	io_pstActWinCrds->act2_x1=i_pstWinPrms->h_max-1;
	if(io_pstActWinCrds->act2_y1>=i_pstWinPrms->v_max)	io_pstActWinCrds->act2_y1=i_pstWinPrms->v_max-1;
	if(io_pstActWinCrds->win2_x1>=i_pstWinPrms->h_max)	io_pstActWinCrds->win2_x1=i_pstWinPrms->h_max-1;
	if(io_pstActWinCrds->win2_y1>=i_pstWinPrms->v_max)	io_pstActWinCrds->win2_y1=i_pstWinPrms->v_max-1;
	if(io_pstActWinCrds->act3_x1>=i_pstWinPrms->h_max)	io_pstActWinCrds->act3_x1=i_pstWinPrms->h_max-1;
	if(io_pstActWinCrds->act3_y1>=i_pstWinPrms->v_max)	io_pstActWinCrds->act3_y1=i_pstWinPrms->v_max-1;
	if(io_pstActWinCrds->win3_x1>=i_pstWinPrms->h_max)	io_pstActWinCrds->win3_x1=i_pstWinPrms->h_max-1;
	if(io_pstActWinCrds->win3_y1>=i_pstWinPrms->v_max)	io_pstActWinCrds->win3_y1=i_pstWinPrms->v_max-1;

	/* check inversion, x0 vs. x1, y0 vs. y1 */
	if(io_pstActWinCrds->act0_x0>io_pstActWinCrds->act0_x1)	io_pstActWinCrds->act0_x0=io_pstActWinCrds->act0_x1;
	if(io_pstActWinCrds->act0_y0>io_pstActWinCrds->act0_y1)	io_pstActWinCrds->act0_y0=io_pstActWinCrds->act0_y1;
	if(io_pstActWinCrds->win0_x0>io_pstActWinCrds->win0_x1)	io_pstActWinCrds->win0_x0=io_pstActWinCrds->win0_x1;
	if(io_pstActWinCrds->win0_x0>io_pstActWinCrds->win0_x1)	io_pstActWinCrds->win0_x0=io_pstActWinCrds->win0_x1;
	if(io_pstActWinCrds->act1_x0>io_pstActWinCrds->act1_x1)	io_pstActWinCrds->act1_x0=io_pstActWinCrds->act1_x1;
	if(io_pstActWinCrds->act1_y0>io_pstActWinCrds->act1_y1)	io_pstActWinCrds->act1_y0=io_pstActWinCrds->act1_y1;
	if(io_pstActWinCrds->win1_x0>io_pstActWinCrds->win1_x1)	io_pstActWinCrds->win1_x0=io_pstActWinCrds->win1_x1;
	if(io_pstActWinCrds->win1_x0>io_pstActWinCrds->win1_x1)	io_pstActWinCrds->win1_x0=io_pstActWinCrds->win1_x1;
	if(io_pstActWinCrds->act2_x0>io_pstActWinCrds->act2_x1)	io_pstActWinCrds->act2_x0=io_pstActWinCrds->act2_x1;
	if(io_pstActWinCrds->act2_y0>io_pstActWinCrds->act2_y1)	io_pstActWinCrds->act2_y0=io_pstActWinCrds->act2_y1;
	if(io_pstActWinCrds->win2_x0>io_pstActWinCrds->win2_x1)	io_pstActWinCrds->win2_x0=io_pstActWinCrds->win2_x1;
	if(io_pstActWinCrds->win2_x0>io_pstActWinCrds->win2_x1)	io_pstActWinCrds->win2_x0=io_pstActWinCrds->win2_x1;
	if(io_pstActWinCrds->act3_x0>io_pstActWinCrds->act3_x1)	io_pstActWinCrds->act3_x0=io_pstActWinCrds->act3_x1;
	if(io_pstActWinCrds->act3_y0>io_pstActWinCrds->act3_y1)	io_pstActWinCrds->act3_y0=io_pstActWinCrds->act3_y1;
	if(io_pstActWinCrds->win3_x0>io_pstActWinCrds->win3_x1)	io_pstActWinCrds->win3_x0=io_pstActWinCrds->win3_x1;
	if(io_pstActWinCrds->win3_x0>io_pstActWinCrds->win3_x1)	io_pstActWinCrds->win3_x0=io_pstActWinCrds->win3_x1;

	#if 0
	printk("[PE_WIN_HW_O26_ValidateWinCoords]o_pstActWinCrds->act0:%d,%d,%d,%d, o_pstActWinCrds->win0:%d,%d,%d,%d\n",\
		io_pstActWinCrds->act0_x0,io_pstActWinCrds->act0_y0,io_pstActWinCrds->act0_x1,io_pstActWinCrds->act0_y1,\
		io_pstActWinCrds->win0_x0,io_pstActWinCrds->win0_y0,io_pstActWinCrds->win0_x1,io_pstActWinCrds->win0_y1);
	#endif

	return;
}

/**
 * Sets color enhancer
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstActWinCrds	[in]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_SetCen(PE_TSK_O26_CFG_T 					*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds)
{
	#ifdef PE_HW_O26_BRINGUP
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O26_CTRL_T *win_info	= &_g_pe_win_hw_o26_info.win_inf;

	if((win_info->act0_x0 != i_pstActWinCrds->act0_x0)|| (win_info->act0_y0 != i_pstActWinCrds->act0_y0)|| \
		(win_info->act0_x1 != i_pstActWinCrds->act0_x1)|| (win_info->act0_y1 != i_pstActWinCrds->act0_y1)|| \
		(win_info->act1_x0 != i_pstActWinCrds->act1_x0)|| (win_info->act1_y0 != i_pstActWinCrds->act1_y0)|| \
		(win_info->act1_x1 != i_pstActWinCrds->act1_x1)|| (win_info->act1_y1 != i_pstActWinCrds->act1_y1)) {

		if(_g_win_hw_o26_trace) {

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]act0 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->act0_x0,win_info->act0_y0,win_info->act0_x1,\
				win_info->act0_y1,i_pstActWinCrds->act0_x0,i_pstActWinCrds->act0_y0,\
				i_pstActWinCrds->act0_x1,i_pstActWinCrds->act0_y1);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]act1 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->act1_x0,win_info->act1_y0,win_info->act1_x1,\
				win_info->act1_y1,i_pstActWinCrds->act1_x0,i_pstActWinCrds->act1_y0,\
				i_pstActWinCrds->act1_x1,i_pstActWinCrds->act1_y1);
		}

		if(PE_KDRV_VER_O26)	{
            if (i_pstCfg->opr.pause_task == PE_TSK_O26_RUN_STOP_WIN2)
			{
	            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_01,	win_w0_x0_0,((i_pstActWinCrds->act0_x0+1)>>1),\
	                                                  	win_w0_y0_0,i_pstActWinCrds->act0_y0);
	            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_02,	win_w0_x1_0,(i_pstActWinCrds->act0_x1>>1),\
	                                                  	win_w0_y1_0,i_pstActWinCrds->act0_y1);
	            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_05,	win_w0_x0_1,(i_pstActWinCrds->act0_x0>>1),\
	                                                  	win_w0_y0_1,i_pstActWinCrds->act0_y0);
	            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_06,	win_w0_x1_1,((i_pstActWinCrds->act0_x1-1)>>1),\
	                                                  	win_w0_y1_1,i_pstActWinCrds->act0_y1);
				// added for DC AVTASK-1314
				#if 0
	            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_17,	win_w0_x0_2,((i_pstActWinCrds->act0_x0+1)>>1),\
	                                                  	win_w0_y0_2,i_pstActWinCrds->act0_y0);
	            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_18,	win_w0_x1_2,(i_pstActWinCrds->act0_x1>>1),\
	                                                  	win_w0_y1_2,i_pstActWinCrds->act0_y1);
	            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_21,	win_w0_x0_3,(i_pstActWinCrds->act0_x0>>1),\
	                                                  	win_w0_y0_3,i_pstActWinCrds->act0_y0);
	            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_22,	win_w0_x1_3,((i_pstActWinCrds->act0_x1-1)>>1),\
	                                                  	win_w0_y1_3,i_pstActWinCrds->act0_y1);
				#endif
			}
			else
			{
				if(_g_win_hw_o26_trace) 
				{
					PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]pause_task:%d, w0 SKIP.\n",i_pstCfg->opr.pause_task);
				}
			}
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_03,	win_w1_x0_0,((i_pstActWinCrds->act1_x0+1)>>1),\
                                                  	win_w1_y0_0,i_pstActWinCrds->act1_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_04,	win_w1_x1_0,(i_pstActWinCrds->act1_x1>>1),\
                                                  	win_w1_y1_0,i_pstActWinCrds->act1_y1);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_07,	win_w1_x0_1,(i_pstActWinCrds->act1_x0>>1),\
                                                  	win_w1_y0_1,i_pstActWinCrds->act1_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_08,	win_w1_x1_1,((i_pstActWinCrds->act1_x1-1)>>1),\
                                                  	win_w1_y1_1,i_pstActWinCrds->act1_y1);
			// added for DC AVTASK-1314
			#if 0
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_19,	win_w1_x0_2,((i_pstActWinCrds->act1_x0+1)>>1),\
                                                  	win_w1_y0_2,i_pstActWinCrds->act1_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_20,	win_w1_x1_2,(i_pstActWinCrds->act1_x1>>1),\
                                                  	win_w1_y1_2,i_pstActWinCrds->act1_y1);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_23,	win_w1_x0_3,(i_pstActWinCrds->act1_x0>>1),\
                                                  	win_w1_y0_3,i_pstActWinCrds->act1_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_24,	win_w1_x1_3,((i_pstActWinCrds->act1_x1-1)>>1),\
                                                  	win_w1_y1_3,i_pstActWinCrds->act1_y1);
			#endif
			#if 0
			PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_00,apl_win_ctrl_x0,(i_pstActWinCrds->act0_x0>>1),\
			 										apl_win_ctrl_y0,i_pstActWinCrds->act0_y0);
			if (disp0_info->out_type==LX_PE_OUT_PIP && ctrl0_info->hv_same)	//double window
			{
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_01,apl_win_ctrl_x1,(i_pstActWinCrds->act1_x1>>1),
													apl_win_ctrl_y1,i_pstActWinCrds->act1_y1);
			}
			else
			{
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_01,apl_win_ctrl_x1,(i_pstActWinCrds->act0_x1>>1),
													apl_win_ctrl_y1,i_pstActWinCrds->act0_y1);
			}
			#else
			if(_g_pe_win_hw_o26_info.is_external_chip==0 && \
				disp0_info->sub_mode==LX_DE_SUB_MODE_PIP && !i_pstWinPrms->is_invalid_size[LX_PE_WIN_1])//miracast & sub video on
			{
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_00,	apl_win_ctrl_x0_0,(i_pstActWinCrds->act1_x0>>1),\
			 											apl_win_ctrl_y0_0,i_pstActWinCrds->act1_y0);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_01,	apl_win_ctrl_x1_0,(i_pstActWinCrds->act1_x1>>1),
														apl_win_ctrl_y1_0,i_pstActWinCrds->act1_y1);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_03,	apl_win_ctrl_x0_1,(i_pstActWinCrds->act1_x0>>1),\
			 											apl_win_ctrl_y0_1,i_pstActWinCrds->act1_y0);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_04,	apl_win_ctrl_x1_1,(i_pstActWinCrds->act1_x1>>1),
														apl_win_ctrl_y1_1,i_pstActWinCrds->act1_y1);
			}
			else if(_g_pe_win_hw_o26_info.is_external_chip==0 && \
				(disp0_info->sub_mode==LX_DE_SUB_MODE_PBP || disp0_info->sub_mode==LX_DE_SUB_MODE_DUALMON) && \
				!i_pstWinPrms->is_invalid_size[LX_PE_WIN_1])//multi view & sub video on
			{
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_00,	apl_win_ctrl_x0_0,(i_pstActWinCrds->act0_x0>>1),\
		 												apl_win_ctrl_y0_0,i_pstActWinCrds->act0_y0);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_01,	apl_win_ctrl_x1_0,(i_pstActWinCrds->act1_x1>>1),
														apl_win_ctrl_y1_0,i_pstActWinCrds->act1_y1);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_03,	apl_win_ctrl_x0_1,(i_pstActWinCrds->act0_x0>>1),\
		 												apl_win_ctrl_y0_1,i_pstActWinCrds->act0_y0);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_04,	apl_win_ctrl_x1_1,(i_pstActWinCrds->act1_x1>>1),
														apl_win_ctrl_y1_1,i_pstActWinCrds->act1_y1);
			}
			else
			{
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_00,	apl_win_ctrl_x0_0,(i_pstActWinCrds->act0_x0>>1),\
			 											apl_win_ctrl_y0_0,i_pstActWinCrds->act0_y0);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_01,	apl_win_ctrl_x1_0,(i_pstActWinCrds->act0_x1>>1),
														apl_win_ctrl_y1_0,i_pstActWinCrds->act0_y1);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_03,	apl_win_ctrl_x0_1,(i_pstActWinCrds->act0_x0>>1),\
			 											apl_win_ctrl_y0_1,i_pstActWinCrds->act0_y0);
				PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_04,	apl_win_ctrl_x1_1,(i_pstActWinCrds->act0_x1>>1),
														apl_win_ctrl_y1_1,i_pstActWinCrds->act0_y1);
			}
			#endif
		}
		win_info->act0_x0 = i_pstActWinCrds->act0_x0;
		win_info->act0_y0 = i_pstActWinCrds->act0_y0;
		win_info->act0_x1 = i_pstActWinCrds->act0_x1;
		win_info->act0_y1 = i_pstActWinCrds->act0_y1;
		win_info->act1_x0 = i_pstActWinCrds->act1_x0;
		win_info->act1_y0 = i_pstActWinCrds->act1_y0;
		win_info->act1_x1 = i_pstActWinCrds->act1_x1;
		win_info->act1_y1 = i_pstActWinCrds->act1_y1;
	}
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

/**
 * Sets sharpness
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstActWinCrds	[in]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_SetShp(PE_TSK_O26_CFG_T 					*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds)
{
	#ifdef PE_HW_O26_BRINGUP
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O26_CTRL_T *win_info	= &_g_pe_win_hw_o26_info.win_inf;
	UINT32 shp_l_w0_x0, shp_l_w0_x1;
	UINT32 shp_l_w1_x0, shp_l_w1_x1;
	/* set win(shp) */
	if((win_info->win0_x0 != i_pstActWinCrds->win0_x0)|| (win_info->win0_y0 != i_pstActWinCrds->win0_y0)|| \
		(win_info->win0_x1 != i_pstActWinCrds->win0_x1)|| (win_info->win0_y1 != i_pstActWinCrds->win0_y1)|| \
		(win_info->win1_x0 != i_pstActWinCrds->win1_x0)|| (win_info->win1_y0 != i_pstActWinCrds->win1_y0)|| \
		(win_info->win1_x1 != i_pstActWinCrds->win1_x1)|| (win_info->win1_y1 != i_pstActWinCrds->win1_y1)) {

		if(_g_win_hw_o26_trace) {

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]win0 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->win0_x0,win_info->win0_y0,win_info->win0_x1,\
				win_info->win0_y1,i_pstActWinCrds->win0_x0,i_pstActWinCrds->win0_y0,\
				i_pstActWinCrds->win0_x1,i_pstActWinCrds->win0_y1);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]win1 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->win1_x0,win_info->win1_y0,win_info->win1_x1,\
				win_info->win1_y1,i_pstActWinCrds->win1_x0,i_pstActWinCrds->win1_y0,\
				i_pstActWinCrds->win1_x1,i_pstActWinCrds->win1_y1);
			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]hmax, vmax : cur:%d,%d\n",\
				i_pstWinPrms->h_max,i_pstWinPrms->v_max);
		}

		#if 0
		printk("[PE_WIN_HW_O26_SetShp]i_pstActWinCrds->act0:%d,%d,%d,%d, i_pstActWinCrds->win0:%d,%d,%d,%d\n",\
			i_pstActWinCrds->act0_x0,i_pstActWinCrds->act0_y0,i_pstActWinCrds->act0_x1,i_pstActWinCrds->act0_y1,\
			i_pstActWinCrds->win0_x0,i_pstActWinCrds->win0_y0,i_pstActWinCrds->win0_x1,i_pstActWinCrds->win0_y1);
		#endif
		if(PE_KDRV_VER_O26) {
			shp_l_w0_x0 = (i_pstActWinCrds->win0_x0 < i_pstWinPrms->h_max)? \
				i_pstActWinCrds->win0_x0:(i_pstWinPrms->h_max-1);
			shp_l_w0_x1 = (i_pstActWinCrds->win0_x1 < i_pstWinPrms->h_max)? \
				i_pstActWinCrds->win0_x1:(i_pstWinPrms->h_max-1);
			shp_l_w1_x0 = (i_pstActWinCrds->win1_x0 < i_pstWinPrms->h_max)? \
				i_pstActWinCrds->win1_x0:(i_pstWinPrms->h_max-1);
			shp_l_w1_x1 = (i_pstActWinCrds->win1_x1 < i_pstWinPrms->h_max)? \
				i_pstActWinCrds->win1_x1:(i_pstWinPrms->h_max-1);

			/* shp_l */
			/* esf */
            PE_VSD_SHP_O26_QWr02(shp_esf_win_ctrl_01,	reg_win_esf_win_w0_x0,	shp_l_w0_x0,\
													reg_win_esf_win_w0_y0,	i_pstActWinCrds->win0_y0);
            PE_VSD_SHP_O26_QWr02(shp_esf_win_ctrl_02,	reg_win_esf_win_w0_x1,	shp_l_w0_x1,\
													reg_win_esf_win_w0_y1,	i_pstActWinCrds->win0_y1);
            PE_VSD_SHP_O26_QWr02(shp_esf_win_ctrl_03,	reg_win_esf_win_w1_x0,	shp_l_w1_x0,\
													reg_win_esf_win_w1_y0,	i_pstActWinCrds->win1_y0);
            PE_VSD_SHP_O26_QWr02(shp_esf_win_ctrl_04,	reg_win_esf_win_w1_x1,	shp_l_w1_x1,\
													reg_win_esf_win_w1_y1,	i_pstActWinCrds->win1_y1);
			/* dp*/
			PE_VSD_SHP_O26_QWr02(shp_dp_win_ctrl_01,	reg_win_dp_win_w0_x0,	shp_l_w0_x0,\
													reg_win_dp_win_w0_y0,	i_pstActWinCrds->win0_y0);
            PE_VSD_SHP_O26_QWr02(shp_dp_win_ctrl_02,	reg_win_dp_win_w0_x1,	shp_l_w0_x1,\
													reg_win_dp_win_w0_y1,	i_pstActWinCrds->win0_y1);
            PE_VSD_SHP_O26_QWr02(shp_dp_win_ctrl_03,	reg_win_dp_win_w1_x0,	shp_l_w1_x0,\
													reg_win_dp_win_w1_y0,	i_pstActWinCrds->win1_y0);
            PE_VSD_SHP_O26_QWr02(shp_dp_win_ctrl_04,	reg_win_dp_win_w1_x1,	shp_l_w1_x1,\
													reg_win_dp_win_w1_y1,	i_pstActWinCrds->win1_y1);
			/* dj*/
			PE_VSD_SHP_O26_QWr02(shp_dj_win_ctrl_01,	reg_win_dj_win_w0_x0,	shp_l_w0_x0,\
													reg_win_dj_win_w0_y0,	i_pstActWinCrds->win0_y0);
            PE_VSD_SHP_O26_QWr02(shp_dj_win_ctrl_02,	reg_win_dj_win_w0_x1,	shp_l_w0_x1,\
													reg_win_dj_win_w0_y1,	i_pstActWinCrds->win0_y1);
            PE_VSD_SHP_O26_QWr02(shp_dj_win_ctrl_03,	reg_win_dj_win_w1_x0,	shp_l_w1_x0,\
													reg_win_dj_win_w1_y0,	i_pstActWinCrds->win1_y0);
            PE_VSD_SHP_O26_QWr02(shp_dj_win_ctrl_04,	reg_win_dj_win_w1_x1,	shp_l_w1_x1,\
													reg_win_dj_win_w1_y1,	i_pstActWinCrds->win1_y1);
		}

		win_info->win0_x0 = i_pstActWinCrds->win0_x0;
		win_info->win0_y0 = i_pstActWinCrds->win0_y0;
		win_info->win0_x1 = i_pstActWinCrds->win0_x1;
		win_info->win0_y1 = i_pstActWinCrds->win0_y1;
		win_info->win1_x0 = i_pstActWinCrds->win1_x0;
		win_info->win1_y0 = i_pstActWinCrds->win1_y0;
		win_info->win1_x1 = i_pstActWinCrds->win1_x1;
		win_info->win1_y1 = i_pstActWinCrds->win1_y1;
	}	
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

/**
 * Sets sharpness window enable
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstShpCenWinEn	[in]	LX_PE_SHP_CEN_WIN_EN_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_SetShpWinEn(PE_TSK_O26_CFG_T 				*i_pstCfg,
									 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
									 LX_PE_SHP_CEN_WIN_EN_T 		*i_pstShpCenWinEn)
{
	#ifdef PE_HW_O26_BRINGUP
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O26_CTRL_T *win_info	= &_g_pe_win_hw_o26_info.win_inf;

	if((win_info->win0_en[PE_WIN_HW_O26_SHP_WIN] != i_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN]) || \
		(win_info->win1_en[PE_WIN_HW_O26_SHP_WIN] != i_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN]) || \
		(win_info->win01_en[PE_WIN_HW_O26_SHP_WIN] != i_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]))
	{
		if(_g_win_hw_o26_trace) {

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]shp_win_en(0,1,01):%d,%d,%d \n",\
				win_info->win0_en[PE_WIN_HW_O26_SHP_WIN], win_info->win1_en[PE_WIN_HW_O26_SHP_WIN],\
				win_info->win01_en[PE_WIN_HW_O26_SHP_WIN]);
		}

		if(PE_KDRV_VER_O26) {
			/*esf*/
			PE_VSD_SHP_O26_QWr03(shp_esf_win_ctrl_00, reg_win_esf_win0_en, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN], \
                                                  reg_win_esf_win1_en, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN], \
                                                  reg_win_esf_win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]);
			/*dp*/
			PE_VSD_SHP_O26_QWr03(shp_dp_win_ctrl_00, reg_win_dp_win0_en, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN] , \
                                                 reg_win_dp_win1_en, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN] , \
                                                 reg_win_dp_win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]);
			/*dj*/
			PE_VSD_SHP_O26_QWr03(shp_dj_win_ctrl_00, reg_win_dj_win0_en, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN] , \
                                                 reg_win_dj_win1_en, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN] , \
                                                 reg_win_dj_win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN]);
		}

		win_info->win0_en[PE_WIN_HW_O26_SHP_WIN] = i_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_SHP_WIN];
		win_info->win1_en[PE_WIN_HW_O26_SHP_WIN] = i_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_SHP_WIN];
		win_info->win01_en[PE_WIN_HW_O26_SHP_WIN] = i_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_SHP_WIN];
	}
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

/**
 * Sets color enhancement window enable
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstShpCenWinEn	[in]	LX_PE_SHP_CEN_WIN_EN_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_SetCenWinEn(PE_TSK_O26_CFG_T 				*i_pstCfg,
									 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
									 LX_PE_SHP_CEN_WIN_EN_T 		*i_pstShpCenWinEn)
{
	#ifdef PE_HW_O26_BRINGUP
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O26_CTRL_T *win_info	= &_g_pe_win_hw_o26_info.win_inf;

	if((win_info->win0_en[PE_WIN_HW_O26_CEN_WIN] != i_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_CEN_WIN]) || \
	   (win_info->win1_en[PE_WIN_HW_O26_CEN_WIN] != i_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_CEN_WIN]) || \
	   (win_info->win01_en[PE_WIN_HW_O26_CEN_WIN] != i_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_CEN_WIN]))
	{
		if(_g_win_hw_o26_trace) {

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]cen_win_en(0,1,01):%d,%d,%d \n",\
				win_info->win0_en[PE_WIN_HW_O26_CEN_WIN], win_info->win1_en[PE_WIN_HW_O26_CEN_WIN],\
				win_info->win01_en[PE_WIN_HW_O26_CEN_WIN]);
		}

		if(PE_KDRV_VER_O26) {

			PE_CC_PE1_O26_QWr03(pe1_win2_ctrl_00,win0_en,i_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_CEN_WIN], \
                                                    win1_en,i_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_CEN_WIN], \
                                                    win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_CEN_WIN]);
		}

		win_info->win0_en[PE_WIN_HW_O26_CEN_WIN] = i_pstShpCenWinEn->win0_en[PE_WIN_HW_O26_CEN_WIN];
		win_info->win1_en[PE_WIN_HW_O26_CEN_WIN] = i_pstShpCenWinEn->win1_en[PE_WIN_HW_O26_CEN_WIN];
		win_info->win01_en[PE_WIN_HW_O26_CEN_WIN] = i_pstShpCenWinEn->win01_en[PE_WIN_HW_O26_CEN_WIN];
	}
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

/**
 * Sets window resolution
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_SetWinResolution(PE_TSK_O26_CFG_T 			*i_pstCfg,
										   LX_PE_WIN_PARAMS_T 			*i_pstWinPrms)
{
	#ifdef PE_HW_O26_BRINGUP
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O26_CTRL_T *win_info	= &_g_pe_win_hw_o26_info.win_inf;
	UINT32 shp_top_w;

	if((win_info->h_max != i_pstWinPrms->h_max)|| (win_info->v_max != i_pstWinPrms->v_max))	{

		if(_g_win_hw_o26_trace) {

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]rev:%d,sub_mode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]h,v_max : prev:%d,%d, cur:%d,%d\n",\
				win_info->h_max,win_info->v_max,i_pstWinPrms->h_max,i_pstWinPrms->v_max);
		}

		shp_top_w = (i_pstWinPrms->h_max);

		if(PE_KDRV_VER_O26) {

			PE_VSD_SHP_O26_QWr02(shp_core_ctrl_01,reg_top_width,shp_top_w,reg_top_height,i_pstWinPrms->v_max);
			PE_CC_PE1_O26_QWr02(pe1_top_ctrl_01,width,(i_pstWinPrms->h_max>>1),height,i_pstWinPrms->v_max);
            //PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_00,apl_win_ctrl_x0,0,apl_win_ctrl_y0,0);
            //PE_CC_PE1_O26_QWr02(pe1_apl_ctrl_01,apl_win_ctrl_x1,(i_pstWinPrms->h_max>>1),apl_win_ctrl_y1,i_pstWinPrms->v_max);
		}
		win_info->h_max = i_pstWinPrms->h_max;
		win_info->v_max = i_pstWinPrms->v_max;
	}
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

/**
 * Sets DC win
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstActWinCrds	[in]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_SetDc(PE_TSK_O26_CFG_T 					*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds)
{
	#ifdef PE_HW_O26_BRINGUP
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl2_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_2];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl3_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_3];
	PE_WIN_HW_O26_CTRL_T *win_info	= &_g_pe_win_hw_o26_info.win_inf;

	//win0, win1 setting @PE_WIN_HW_O26_SetCen with PE1_WIN2_CTRL_01~09
	// set only win2, win3 
	if(	(win_info->act2_x0 != i_pstActWinCrds->act2_x0)|| (win_info->act2_y0 != i_pstActWinCrds->act2_y0)|| \
		(win_info->act2_x1 != i_pstActWinCrds->act2_x1)|| (win_info->act2_y1 != i_pstActWinCrds->act2_y1)|| \
		(win_info->act3_x0 != i_pstActWinCrds->act3_x0)|| (win_info->act3_y0 != i_pstActWinCrds->act3_y0)|| \
		(win_info->act3_x1 != i_pstActWinCrds->act3_x1)|| (win_info->act3_y1 != i_pstActWinCrds->act3_y1)) {

		if(_g_win_hw_o26_trace) {

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_2],i_pstWinPrms->y0_ofst[LX_PE_WIN_2],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_2],i_pstWinPrms->y1_ofst[LX_PE_WIN_2],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_3],i_pstWinPrms->y0_ofst[LX_PE_WIN_3],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_3],i_pstWinPrms->y1_ofst[LX_PE_WIN_3]);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl2_info->u_o_win_h_ofst,ctrl2_info->u_o_win_v_ofst,ctrl2_info->u_o_win_h_size,\
				ctrl2_info->u_o_win_v_size,ctrl3_info->u_o_win_h_ofst,ctrl3_info->u_o_win_v_ofst,\
				ctrl3_info->u_o_win_h_size,ctrl3_info->u_o_win_v_size);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]act0 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->act2_x0,win_info->act2_y0,win_info->act2_x1,\
				win_info->act2_y1,i_pstActWinCrds->act2_x0,i_pstActWinCrds->act2_y0,\
				i_pstActWinCrds->act2_x1,i_pstActWinCrds->act2_y1);

			PE_WIN_HW_O26_DBG_PRINT_ALWAYS("[set]act1 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->act3_x0,win_info->act3_y0,win_info->act3_x1,\
				win_info->act3_y1,i_pstActWinCrds->act3_x0,i_pstActWinCrds->act3_y0,\
				i_pstActWinCrds->act3_x1,i_pstActWinCrds->act3_y1);
		}

		if(PE_KDRV_VER_O26)	{
			//win2 ch 0,1,2,3
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_09,	win_w2_x0_0,((i_pstActWinCrds->act2_x0+1)>>1),\
                                                    win_w2_y0_0,i_pstActWinCrds->act2_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_10,	win_w2_x1_0,(i_pstActWinCrds->act2_x1>>1),\
                                                    win_w2_y1_0,i_pstActWinCrds->act2_y1);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_13,	win_w2_x0_1,(i_pstActWinCrds->act2_x0>>1),\
                                                    win_w2_y0_1,i_pstActWinCrds->act2_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_14,	win_w2_x1_1,((i_pstActWinCrds->act2_x1-1)>>1),\
                                                    win_w2_y1_1,i_pstActWinCrds->act2_y1);
			#if 0
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_25,	win_w2_x0_2,((i_pstActWinCrds->act2_x0+1)>>1),\
                                                    win_w2_y0_2,i_pstActWinCrds->act2_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_26,	win_w2_x1_2,(i_pstActWinCrds->act2_x1>>1),\
                                                    win_w2_y1_2,i_pstActWinCrds->act2_y1);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_29,	win_w2_x0_3,(i_pstActWinCrds->act2_x0>>1),\
                                                    win_w2_y0_3,i_pstActWinCrds->act2_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_30,	win_w2_x1_3,((i_pstActWinCrds->act2_x1-1)>>1),\
                                                    win_w2_y1_3,i_pstActWinCrds->act2_y1);
			#endif
			//win3 ch 0,1,2,3
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_11,	win_w3_x0_0,((i_pstActWinCrds->act3_x0+1)>>1),\
                                                    win_w3_y0_0,i_pstActWinCrds->act3_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_12,	win_w3_x1_0,(i_pstActWinCrds->act3_x1>>1),\
                                                    win_w3_y1_0,i_pstActWinCrds->act3_y1);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_15,	win_w3_x0_1,(i_pstActWinCrds->act3_x0>>1),\
                                                    win_w3_y0_1,i_pstActWinCrds->act3_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_16,	win_w3_x1_1,((i_pstActWinCrds->act3_x1-1)>>1),\
                                                    win_w3_y1_1,i_pstActWinCrds->act3_y1);
			#if 0
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_27,	win_w3_x0_2,((i_pstActWinCrds->act3_x0+1)>>1),\
                                                    win_w3_y0_2,i_pstActWinCrds->act3_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_28,	win_w3_x1_2,(i_pstActWinCrds->act3_x1>>1),\
                                                    win_w3_y1_2,i_pstActWinCrds->act3_y1);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_31,	win_w3_x0_3,(i_pstActWinCrds->act3_x0>>1),\
                                                    win_w3_y0_3,i_pstActWinCrds->act3_y0);
            PE_CC_PE1_O26_QWr02(pe1_win2_ctrl_32,	win_w3_x1_3,((i_pstActWinCrds->act3_x1-1)>>1),\
                                                    win_w3_y1_3,i_pstActWinCrds->act3_y1);
			#endif
		}
		win_info->act2_x0 = i_pstActWinCrds->act2_x0;
		win_info->act2_y0 = i_pstActWinCrds->act2_y0;
		win_info->act2_x1 = i_pstActWinCrds->act2_x1;
		win_info->act2_y1 = i_pstActWinCrds->act2_y1;
		win_info->act3_x0 = i_pstActWinCrds->act3_x0;
		win_info->act3_y0 = i_pstActWinCrds->act3_y0;
		win_info->act3_x1 = i_pstActWinCrds->act3_x1;
		win_info->act3_y1 = i_pstActWinCrds->act3_y1;
	}
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

/**
 * Sets Pcc win
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O26_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstActWinCrds	[in]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_WIN_HW_O26_SetPcc(PE_TSK_O26_CFG_T 					*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds)
{
	#ifdef PE_HW_O26_BRINGUP
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl2_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_2];
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl3_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_3];
	PE_WIN_HW_O26_CTRL_T *win_info	= &_g_pe_win_hw_o26_info.win_inf;

	if(	(win_info->act0_x0 != i_pstActWinCrds->act0_x0)|| (win_info->act0_y0 != i_pstActWinCrds->act0_y0)|| \
		(win_info->act0_x1 != i_pstActWinCrds->act0_x1)|| (win_info->act0_y1 != i_pstActWinCrds->act0_y1)|| \
		(win_info->act1_x0 != i_pstActWinCrds->act1_x0)|| (win_info->act1_y0 != i_pstActWinCrds->act1_y0)|| \
		(win_info->act1_x1 != i_pstActWinCrds->act1_x1)|| (win_info->act1_y1 != i_pstActWinCrds->act1_y1)|| \
		(win_info->act2_x0 != i_pstActWinCrds->act2_x0)|| (win_info->act2_y0 != i_pstActWinCrds->act2_y0)|| \
		(win_info->act2_x1 != i_pstActWinCrds->act2_x1)|| (win_info->act2_y1 != i_pstActWinCrds->act2_y1)|| \
		(win_info->act3_x0 != i_pstActWinCrds->act3_x0)|| (win_info->act3_y0 != i_pstActWinCrds->act3_y0)|| \
		(win_info->act3_x1 != i_pstActWinCrds->act3_x1)|| (win_info->act3_y1 != i_pstActWinCrds->act3_y1)) {
		if(PE_KDRV_VER_O26)	{
			//win0 ch0,1
            PE_CC_PE1_O26_QWr02(pcc_winctrl_04,	win0_w0_x0,(i_pstActWinCrds->act0_x0>>1),\
                                                win0_w0_y0,i_pstActWinCrds->act0_y0);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_05,	win0_w0_x1,(i_pstActWinCrds->act0_x1>>1),\
                                                win0_w0_y1,i_pstActWinCrds->act0_y1);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_12,	win0_w0_x0,(i_pstActWinCrds->act0_x0>>1),\
                                                win0_w0_y0,i_pstActWinCrds->act0_y0);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_13,	win0_w0_x1,(i_pstActWinCrds->act0_x1>>1),\
                                                win0_w0_y1,i_pstActWinCrds->act0_y1);
			//win1 ch0,1
            PE_CC_PE1_O26_QWr02(pcc_winctrl_06,	win1_w0_x0,(i_pstActWinCrds->act1_x0>>1),\
                                                win1_w0_y0,i_pstActWinCrds->act1_y0);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_07,	win1_w0_x1,(i_pstActWinCrds->act1_x1>>1),\
                                                win1_w0_y1,i_pstActWinCrds->act1_y1);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_14,	win1_w0_x0,(i_pstActWinCrds->act1_x0>>1),\
                                                win1_w0_y0,i_pstActWinCrds->act1_y0);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_15,	win1_w0_x1,(i_pstActWinCrds->act1_x1>>1),\
                                                win1_w0_y1,i_pstActWinCrds->act1_y1);
			//win2 ch0,1
            PE_CC_PE1_O26_QWr02(pcc_winctrl_08,	win2_w0_x0,(i_pstActWinCrds->act2_x0>>1),\
                                                win2_w0_y0,i_pstActWinCrds->act2_y0);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_09,	win2_w0_x1,(i_pstActWinCrds->act2_x1>>1),\
                                                win2_w0_y1,i_pstActWinCrds->act2_y1);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_16,	win2_w0_x0,(i_pstActWinCrds->act2_x0>>1),\
                                                win2_w0_y0,i_pstActWinCrds->act2_y0);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_17,	win2_w0_x1,(i_pstActWinCrds->act2_x1>>1),\
                                                win2_w0_y1,i_pstActWinCrds->act2_y1);
			//win3 ch0,1
            PE_CC_PE1_O26_QWr02(pcc_winctrl_10,	win3_w0_x0,(i_pstActWinCrds->act3_x0>>1),\
                                                win3_w0_y0,i_pstActWinCrds->act3_y0);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_11,	win3_w0_x1,(i_pstActWinCrds->act3_x1>>1),\
                                                win3_w0_y1,i_pstActWinCrds->act3_y1);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_18,	win3_w0_x0,(i_pstActWinCrds->act3_x0>>1),\
                                                win3_w0_y0,i_pstActWinCrds->act3_y0);
            PE_CC_PE1_O26_QWr02(pcc_winctrl_19,	win3_w0_x1,(i_pstActWinCrds->act3_x1>>1),\
                                                win3_w0_y1,i_pstActWinCrds->act3_y1);
		}
	}
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

