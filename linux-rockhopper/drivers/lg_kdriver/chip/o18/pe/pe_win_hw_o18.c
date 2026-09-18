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

#include "pe_hw_o18.h"
#include "pe_reg_o18.h"
#include "pe_tsk_o18.h"
#include "pe_win_hw_o18.h"
#include "pe_hst_hw_o18.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* Enabling this macro will DISABLE LGSI code refactoring changes, so enable only if there is
any issue in LGSI refactored code. This provision is only for cross checking with original
source. It can be removed in the next version of the code*/

#define PE_WIN_HW_O18_UHD_H_MAX			3840
#define PE_WIN_HW_O18_UHD_V_MAX			2160
#define PE_WIN_HW_O18_FHD_H_MAX			1920
#define PE_WIN_HW_O18_FHD_V_MAX			1080
#define PE_WIN_HW_O18_SHP_WIN			0
#define PE_WIN_HW_O18_CEN_WIN			1
#define PE_WIN_HW_O18_WIN_EN_OFF		0
#define PE_WIN_HW_O18_WIN_EN__ON		1
#define PE_WIN_HW_O18_P1SHP_WIN_OFST	64

#define PE_WIN_HW_O18_WIN_OFFSET_MAX	(4)

/* 20140305, sj.youm, use win0 for lrcr win because of single path */
#define PE_WIN_HW_O18A_USE_WIN_0_ONLY

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_WIN_HW_O18_ERROR	printk

#define PE_WIN_HW_O18_DBG_PRINT(fmt,args...)	\
	if(_g_win_hw_o18_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_WIN_HW_O18_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_WIN_HW_O18_ERROR(fmt,##args);_action;}}

#define PE_WIN_HW_O18_DIVIDE(x,y)	(((((x)<<10)/y)+512)>>10)

#define PE_WIN_HW_O18_DBG_PRINT_ALWAYS(fmt,args...)	\
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
extern int	g_be_orbit_onoff;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void PE_WIN_HW_O18_SetVerWinReverse(UINT32 *y0,UINT32 *y1,UINT32 v_max);
static void PE_WIN_HW_O18_GetWinParams(PE_TSK_O18_CFG_T *i_pstCfg, LX_PE_WIN_PARAMS_T *o_pstWinPrms);
static void PE_WIN_HW_O18_GetActNWinCrdsForExtFRC(PE_TSK_O18_CFG_T 			*i_pstCfg,
												LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
												LX_PE_ACT_WIN_COORDINATES_T *o_pstActWinCrds);
static void PE_WIN_HW_O18_GetShpCenWinEnForExtFRC(PE_TSK_O18_CFG_T 		*i_pstCfg,
												BOOLEAN					i_bIsResizeSet,
												LX_PE_SHP_CEN_WIN_EN_T	*o_pstShpCenWinEn);
static void PE_WIN_HW_O18_ValidateWinCoords(LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
											LX_PE_ACT_WIN_COORDINATES_T *io_pstActWinCrds);
static void PE_WIN_HW_O18_SetCen(PE_TSK_O18_CFG_T 				*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 	*i_pstActWinCrds);
static void PE_WIN_HW_O18_SetShp(PE_TSK_O18_CFG_T 				*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds);
static void PE_WIN_HW_O18_SetShpWinEn(PE_TSK_O18_CFG_T 				*i_pstCfg,
									 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
									 LX_PE_SHP_CEN_WIN_EN_T 		*i_pstShpCenWinEn);
static void PE_WIN_HW_O18_SetCenWinEn(PE_TSK_O18_CFG_T 				*i_pstCfg,
									 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
									 LX_PE_SHP_CEN_WIN_EN_T 		*i_pstShpCenWinEn);
static void PE_WIN_HW_O18_SetWinResolution(PE_TSK_O18_CFG_T 			*i_pstCfg,
										   LX_PE_WIN_PARAMS_T 			*i_pstWinPrms);

static void PE_WIN_HW_O18_GetWinParamsLrcr(PE_TSK_O18_CFG_T *i_pstCfg, LX_PE_WIN_PARAMS_T *o_pstWinPrms);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_win_hw_o18_trace=0x0;	//default should be off.
static PE_WIN_HW_O18_SETTINGS_T _g_pe_win_hw_o18_info;

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
int PE_WIN_HW_O18_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			memset(&_g_pe_win_hw_o18_info,-1,sizeof(PE_WIN_HW_O18_SETTINGS_T));
			PE_WIN_HW_O18_DBG_PRINT("pe1 win ctrl init, inside.\n");
			/*esf*/
			PE_SHP_O18_QWr05(shp_core0_esf_win_ctrl_00, reg_win_esf_win0_en_c0,0x1, \
                                                        reg_win_esf_win1_en_c0,0x1, \
                                                        reg_win_esf_win01_en_c0,0x1, \
                                                        reg_win_esf_win_en_c0,0x1, \
                                                        reg_win_esf_win_outside_c0,0x0);
			PE_SHP_O18_QWr05(shp_core1_esf_win_ctrl_00, reg_win_esf_win0_en_c1,0x1, \
                                                        reg_win_esf_win1_en_c1,0x1, \
                                                        reg_win_esf_win01_en_c1,0x1, \
                                                        reg_win_esf_win_en_c1,0x1, \
                                                        reg_win_esf_win_outside_c1,0x0);
			/*dp*/
			PE_SHP_O18_QWr05(shp_core0_dp_win_ctrl_00, reg_win_dp_win0_en_c0,0x1, \
                                                  	   reg_win_dp_win1_en_c0,0x1, \
                                                  	   reg_win_dp_win01_en_c0,0x1, \
                                                  	   reg_win_dp_win_en_c0,0x1, \
                                                  	   reg_win_dp_win_outside_c0,0x0);
			PE_SHP_O18_QWr05(shp_core1_dp_win_ctrl_00, reg_win_dp_win0_en_c1,0x1, \
                                                  	   reg_win_dp_win1_en_c1,0x1, \
                                                  	   reg_win_dp_win01_en_c1,0x1, \
                                                  	   reg_win_dp_win_en_c1,0x1, \
                                                  	   reg_win_dp_win_outside_c1,0x0);
			/*dj*/
			PE_SHP_O18_QWr05(shp_core0_dj_win_ctrl_00, reg_win_dj_win0_en_c0,0x1, \
                                                  	   reg_win_dj_win1_en_c0,0x1, \
                                                  	   reg_win_dj_win01_en_c0,0x1, \
                                                  	   reg_win_dj_win_en_c0,0x1, \
                                                  	   reg_win_dj_win_outside_c0,0x0);
			PE_SHP_O18_QWr05(shp_core1_dj_win_ctrl_00, reg_win_dj_win0_en_c1,0x1, \
                                                  	   reg_win_dj_win1_en_c1,0x1, \
                                                  	   reg_win_dj_win01_en_c1,0x1, \
                                                  	   reg_win_dj_win_en_c1,0x1, \
                                                  	   reg_win_dj_win_outside_c1,0x0);
			/*cco*/
			PE_CEO_PE1_O18_QWr05(pe1_win2_ctrl_00,win0_en,0x1, \
                                                    win1_en,0x1, \
                                                    win01_en,0x1, \
                                                    win_en,0x1, \
                                                    win_outside,0x0);

			g_be_orbit_onoff=0xff;
		}
		else
		{
			PE_WIN_HW_O18_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
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
int PE_WIN_HW_O18_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_WIN_HW_O18_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(WIN)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_win_hw_o18_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(WIN)))? 0x1:0x0;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
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
static void PE_WIN_HW_O18_SetVerWinReverse(UINT32 *y0,UINT32 *y1,UINT32 v_max)
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
 * @param   *pCfg [in] PE_TSK_O18_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_HW_O18_SetEnhancingWindow(PE_TSK_O18_CFG_T *pCfg)
{
	int ret 						= RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 							is_resize_case;
	LX_PE_WIN_PARAMS_T 				stWinPrms;
	LX_PE_ACT_WIN_COORDINATES_T 	stActWinCrds;
	LX_PE_SHP_CEN_WIN_EN_T			stShpCenWinEn;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl1_info 	= &pCfg->inf.ctrl_info[LX_PE_WIN_1];

	do {

		CHECK_KNULL(pCfg);

		if(PE_KDRV_VER_O18) {

			PE_WIN_HW_O18_GetWinParams(pCfg, &stWinPrms);

			PE_WIN_HW_O18_GetActNWinCrdsForExtFRC(pCfg, &stWinPrms, &stActWinCrds);

			/* reverse mode */
			if(disp0_info->mode.is_reverse)	{
				PE_WIN_HW_O18_SetVerWinReverse(&stActWinCrds.act0_y0, &stActWinCrds.act0_y1, stWinPrms.v_max);
				PE_WIN_HW_O18_SetVerWinReverse(&stActWinCrds.act1_y0, &stActWinCrds.act1_y1, stWinPrms.v_max);
				PE_WIN_HW_O18_SetVerWinReverse(&stActWinCrds.win0_y0, &stActWinCrds.win0_y1, stWinPrms.v_max);
				PE_WIN_HW_O18_SetVerWinReverse(&stActWinCrds.win1_y0, &stActWinCrds.win1_y1, stWinPrms.v_max);
			}

			/* 20130206, sj.youm, check resize_case that is resize(ctrl1 hv_same) and not file/photo play */
			is_resize_case = ((ctrl1_info->hv_same) && \
				!(disp0_info->src_type==LX_PE_SRC_DTV&&(disp0_info->dtv_type==LX_PE_DTV_FILEPLAY || \
				disp0_info->dtv_type==LX_PE_DTV_PHOTOPLAY)))? 1:0;

			/* win enable [0]:shp win, [1]:cen win */
			/* 20130130, sj.youm, on shp,cen win for split window because of function enable */
			/* 20130206, sj.youm, off shp, on cen win for resize(non pip) because of shp artifact */
			PE_WIN_HW_O18_GetShpCenWinEnForExtFRC(pCfg, is_resize_case, &stShpCenWinEn);

			/* 20130221, sj.youm, check valid window coordinate */
			PE_WIN_HW_O18_ValidateWinCoords(&stWinPrms, &stActWinCrds);

			/* set act(cen) */
			PE_WIN_HW_O18_SetCen(pCfg, &stWinPrms, &stActWinCrds);

			/* set win(shp) */
			PE_WIN_HW_O18_SetShp(pCfg, &stWinPrms, &stActWinCrds);

			/* shp win en */
			PE_WIN_HW_O18_SetShpWinEn(pCfg, &stWinPrms, &stShpCenWinEn);

			/* cen win en */
			PE_WIN_HW_O18_SetCenWinEn(pCfg, &stWinPrms, &stShpCenWinEn);

			/* etc */
			PE_WIN_HW_O18_SetWinResolution(pCfg, &stWinPrms);

		} else {

			PE_WIN_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}

	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

int PE_WIN_HW_O18_GetCurWinSettings(PE_WIN_HW_O18_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	PE_WIN_HW_O18_SETTINGS_T *pInfo = &_g_pe_win_hw_o18_info;
	PE_WIN_HW_O18_CTRL_T *win_info = &_g_pe_win_hw_o18_info.win_inf;
	PE_WIN_HW_O18_LRCR_CTRL_T *lrcr_info = &_g_pe_win_hw_o18_info.lrcr_inf;
	PE_WIN_HW_O18_TNR_CTRL_T *tnr_info = &_g_pe_win_hw_o18_info.tnr_inf;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			memcpy(pstParams,pInfo,sizeof(PE_WIN_HW_O18_SETTINGS_T));
			PE_WIN_HW_O18_DBG_PRINT("act0:%d,%d,%d,%d, act1:%d,%d,%d,%d\n",\
				win_info->act0_x0,win_info->act0_y0,win_info->act0_x1,win_info->act0_y1,\
				win_info->act1_x0,win_info->act1_y0,win_info->act1_x1,win_info->act1_y1);
			PE_WIN_HW_O18_DBG_PRINT("win0:%d,%d,%d,%d, win1:%d,%d,%d,%d\n",\
				win_info->win0_x0,win_info->win0_y0,win_info->win0_x1,win_info->win0_y1,\
				win_info->win1_x0,win_info->win1_y0,win_info->win1_x1,win_info->win1_y1);
			PE_WIN_HW_O18_DBG_PRINT("h,v_max:%d,%d, w0,w1,w01_en:[%d,%d],[%d,%d],[%d,%d]\n",\
				win_info->h_max,win_info->v_max,win_info->win0_en[0],win_info->win0_en[1],\
				win_info->win1_en[0],win_info->win1_en[1],win_info->win01_en[0],win_info->win01_en[1]);
			PE_WIN_HW_O18_DBG_PRINT("histo_l,r, apply_r : %d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d\n",\
				lrcr_info->histo_l_x0,lrcr_info->histo_l_y0,lrcr_info->histo_l_x1,lrcr_info->histo_l_y1,\
				lrcr_info->histo_r_x0,lrcr_info->histo_r_y0,lrcr_info->histo_r_x1,lrcr_info->histo_r_y1,\
				lrcr_info->apply_r_x0,lrcr_info->apply_r_y0,lrcr_info->apply_r_x1,lrcr_info->apply_r_y1);
			PE_WIN_HW_O18_DBG_PRINT("tnr win h,v size0:%d,%d, size1:%d,%d\n",\
				tnr_info->h_size0,tnr_info->v_size0,tnr_info->h_size1,tnr_info->v_size1);
		}
		else
		{
			PE_WIN_HW_O18_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * Gets window params
 *
 * @param   *i_pstCfg		[in] 	PE_TSK_O18_CFG_T
 * @param   *o_pstWinPrms	[out]	LX_PE_WIN_PARAMS_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_GetWinParams(PE_TSK_O18_CFG_T *i_pstCfg, LX_PE_WIN_PARAMS_T *o_pstWinPrms)
{
	#ifdef PE_HW_O18_BRINGUP
	UINT16 is_orbit;
	UINT16 x_ofst;
	UINT16 y_ofst;
	UINT16 x_size;
	UINT16 y_size;
	UINT16 x1_ofst;
	UINT16 y1_ofst;
	UINT16 x1_size;
	UINT16 y1_size;
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_1];
	PE_INF_O18_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	is_orbit = (g_be_orbit_onoff == 0x1)?0x1:0x0;
	PE_VCP_DISP_O18_QRd02(vcp_u0_win_o_pos,		cdc_win_o_pos_x, x_ofst,\
											 	cdc_win_o_pos_y, y_ofst);
	
	PE_VCP_DISP_O18_QRd02(vcp_u0_win_o_size,	cdc_win_o_size_x, x_size,\
												cdc_win_o_size_y, y_size);

	PE_VCP_DISP_O18_QRd02(vcp_u1_win_o_pos,		cdc_win_o_pos_x, x1_ofst,\
											 	cdc_win_o_pos_y, y1_ofst);
	PE_VCP_DISP_O18_QRd02(vcp_u1_win_o_size,	cdc_win_o_size_x, x1_size,\
												cdc_win_o_size_y, y1_size);
	o_pstWinPrms->h_max=PE_WIN_HW_O18_UHD_H_MAX;
	o_pstWinPrms->v_max=PE_WIN_HW_O18_UHD_V_MAX;
	/* 2012xxxx, sj.youm, inner pattern for 2d,3d and so on. */
	o_pstWinPrms->is_invalid_size[LX_PE_WIN_0] = \
		(ctrl0_info->u_o_win_h_size <= (PE_WIN_HW_O18_WIN_OFFSET_MAX<<1) || \
		ctrl0_info->u_o_win_v_size <= (PE_WIN_HW_O18_WIN_OFFSET_MAX<<1))? 1:0;
	o_pstWinPrms->is_invalid_size[LX_PE_WIN_1] = \
		(ctrl1_info->u_o_win_h_size <= (PE_WIN_HW_O18_WIN_OFFSET_MAX<<1) || \
		ctrl1_info->u_o_win_v_size <= (PE_WIN_HW_O18_WIN_OFFSET_MAX<<1))? 1:0;

	if(is_orbit)
	{
		/* left ofst*/
		if(x_ofst == 0x0)//if no margin for orbit, then no offset for shp
		{
			o_pstWinPrms->x0_ofst[LX_PE_WIN_0] = 0;
			o_pstWinPrms->x0_ofst[LX_PE_WIN_1] = 0;
		}
		else
		{
			o_pstWinPrms->x0_ofst[LX_PE_WIN_0] = 5;
			o_pstWinPrms->x0_ofst[LX_PE_WIN_1] = 5;
		}

		if(y_ofst == 0x0)//if no margin for orbit, then no offset for shp
		{
			o_pstWinPrms->y0_ofst[LX_PE_WIN_0]= 0;
			o_pstWinPrms->y0_ofst[LX_PE_WIN_1]= 0;
		}
		else
		{
			o_pstWinPrms->y0_ofst[LX_PE_WIN_0]= 3;
			o_pstWinPrms->y0_ofst[LX_PE_WIN_1]= 3;
		}

		/* right ofst*/
		if((x_ofst+x_size)<PE_WIN_HW_O18_UHD_H_MAX)//offset for shp
		{
			o_pstWinPrms->x1_ofst[LX_PE_WIN_0] = 5;
			o_pstWinPrms->x1_ofst[LX_PE_WIN_1] = 5;
		}
		else										// no offset
		{
			o_pstWinPrms->x1_ofst[LX_PE_WIN_0] = 0;
			o_pstWinPrms->x1_ofst[LX_PE_WIN_1] = 0;
		}
		if((y_ofst+y_size)<PE_WIN_HW_O18_UHD_V_MAX)//offset for shp
		{
			o_pstWinPrms->y1_ofst[LX_PE_WIN_0] = 3;
			o_pstWinPrms->y1_ofst[LX_PE_WIN_1] = 3;
		}
		else										// no offset
		{
			o_pstWinPrms->y1_ofst[LX_PE_WIN_0] = 0;
			o_pstWinPrms->y1_ofst[LX_PE_WIN_1] = 0;
		}

		/* 20130121, sj.youm, add photo case because of slide show */
		if(o_pstWinPrms->is_invalid_size[LX_PE_WIN_0] || \
			(disp0_info->src_type==LX_PE_SRC_DTV && \
			disp0_info->dtv_type==LX_PE_DTV_PHOTOPLAY)) 
		{
			o_pstWinPrms->x0[LX_PE_WIN_0] = x_ofst;
			o_pstWinPrms->y0[LX_PE_WIN_0] = y_ofst;
			o_pstWinPrms->x1[LX_PE_WIN_0] = o_pstWinPrms->h_max-1;
			o_pstWinPrms->y1[LX_PE_WIN_0] = o_pstWinPrms->v_max-1;
		} 
		else 
		{
			o_pstWinPrms->x0[LX_PE_WIN_0] = x_ofst;
			o_pstWinPrms->y0[LX_PE_WIN_0] = y_ofst;
			o_pstWinPrms->x1[LX_PE_WIN_0] = x_ofst+x_size-1;
			o_pstWinPrms->y1[LX_PE_WIN_0] = y_ofst+y_size-1;
		}
	}
	else
	{
		/*171016 inkyung.park, change x offset 3->5 for O18 to avoid peaking artifact*/
		o_pstWinPrms->x0_ofst[LX_PE_WIN_0] = o_pstWinPrms->x1_ofst[LX_PE_WIN_0] = \
			(ctrl0_info->u_o_win_h_size<PE_WIN_HW_O18_UHD_H_MAX)? 4:0;
		o_pstWinPrms->x0_ofst[LX_PE_WIN_1] = o_pstWinPrms->x1_ofst[LX_PE_WIN_1] = \
			(ctrl1_info->u_o_win_h_size<PE_WIN_HW_O18_UHD_H_MAX)? 4:0;
		o_pstWinPrms->y0_ofst[LX_PE_WIN_0] = o_pstWinPrms->y1_ofst[LX_PE_WIN_0] = \
			(ctrl0_info->u_o_win_v_size<PE_WIN_HW_O18_UHD_V_MAX)? 4:0;
		o_pstWinPrms->y0_ofst[LX_PE_WIN_1] = o_pstWinPrms->y1_ofst[LX_PE_WIN_1] = \
			(ctrl1_info->u_o_win_v_size<PE_WIN_HW_O18_UHD_V_MAX)? 4:0;
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
			o_pstWinPrms->x0[LX_PE_WIN_0] = ctrl0_info->u_o_win_h_ofst;
			o_pstWinPrms->y0[LX_PE_WIN_0] = ctrl0_info->u_o_win_v_ofst;
			o_pstWinPrms->x1[LX_PE_WIN_0] = o_pstWinPrms->x0[LX_PE_WIN_0]+ctrl0_info->u_o_win_h_size-1;
			o_pstWinPrms->y1[LX_PE_WIN_0] = o_pstWinPrms->y0[LX_PE_WIN_0]+ctrl0_info->u_o_win_v_size-1;
		}
	}

	/* 20130121, sj.youm, add photo case because of slide show */
	if(o_pstWinPrms->is_invalid_size[LX_PE_WIN_1] || \
		(disp1_info->src_type==LX_PE_SRC_DTV && \
		disp1_info->dtv_type==LX_PE_DTV_PHOTOPLAY))
	{
		o_pstWinPrms->x0[LX_PE_WIN_1] = 0;
		o_pstWinPrms->y0[LX_PE_WIN_1] = 0;
		o_pstWinPrms->x1[LX_PE_WIN_1] = o_pstWinPrms->h_max-1;
		o_pstWinPrms->y1[LX_PE_WIN_1] = o_pstWinPrms->v_max-1;
	} 
	else 
	{
		if(is_orbit)
		{
			o_pstWinPrms->x0[LX_PE_WIN_1] = x1_ofst;
			o_pstWinPrms->y0[LX_PE_WIN_1] = y1_ofst;
			o_pstWinPrms->x1[LX_PE_WIN_1] = x1_ofst+x1_size-1;
			o_pstWinPrms->y1[LX_PE_WIN_1] = y1_ofst+y1_size-1;
		}
		else
		{
			o_pstWinPrms->x0[LX_PE_WIN_1] = ctrl1_info->u_o_win_h_ofst;
			o_pstWinPrms->y0[LX_PE_WIN_1] = ctrl1_info->u_o_win_v_ofst;
			o_pstWinPrms->x1[LX_PE_WIN_1] = o_pstWinPrms->x0[LX_PE_WIN_1]+ctrl1_info->u_o_win_h_size-1;
			o_pstWinPrms->y1[LX_PE_WIN_1] = o_pstWinPrms->y0[LX_PE_WIN_1]+ctrl1_info->u_o_win_v_size-1;
		}
	}
	#endif /*PE_HW_O18_BRINGUP*/
	return;
}

/**
 * Gets active window coordinates of PIP for external FRC
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O18_CFG_T
 * @param   *i_pstWinPrms		[in]	LX_PE_WIN_PARAMS_T
 * @param 	*o_pstActWinCrds	[out]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_GetActNWinCrdsForExtFRC_PIP(PE_TSK_O18_CFG_T 			*i_pstCfg,
													LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
													LX_PE_ACT_WIN_COORDINATES_T *o_pstActWinCrds)
{
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];

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

	if(disp0_info->sub_mode == LX_DE_SUB_MODE_PBP)
	{

		/* L : window 1 */
		o_pstActWinCrds->act1_x0 = x0[LX_PE_WIN_1];
		o_pstActWinCrds->act1_y0 = y0[LX_PE_WIN_1];
		o_pstActWinCrds->act1_x1 = x1[LX_PE_WIN_1];
		o_pstActWinCrds->act1_y1 = y1[LX_PE_WIN_1];
		o_pstActWinCrds->win1_x0 = x0[LX_PE_WIN_1]+x0_ofst[LX_PE_WIN_1];
		o_pstActWinCrds->win1_y0 = y0[LX_PE_WIN_1]+y0_ofst[LX_PE_WIN_1];
		o_pstActWinCrds->win1_x1 = x1[LX_PE_WIN_1]-x1_ofst[LX_PE_WIN_1];
		o_pstActWinCrds->win1_y1 = y1[LX_PE_WIN_1]-y1_ofst[LX_PE_WIN_1];

	}
	else if (disp0_info->sub_mode == LX_DE_SUB_MODE_PIP)
	{
		/* L : window 1 */
		/* 20130218, sj.youm, add inv size to avoid main cen artifact when turn on pip */
		/* 20130221, sj.youm, add x,y comp to avoid main cen artifact when turn on pip */
		#if 0
		if(i_pstWinPrms->is_invalid_size[LX_PE_WIN_1] || \
			x0[LX_PE_WIN_0]==x0[LX_PE_WIN_1] || \
			y0[LX_PE_WIN_0]==y0[LX_PE_WIN_1] || \
			x1[LX_PE_WIN_0]==x1[LX_PE_WIN_1] || \
			y1[LX_PE_WIN_0]==y1[LX_PE_WIN_1])
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
		else if(disp0_info->mul_win == 2)
		#else
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
		#endif
		else{

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
	}
	else //mirrormode  
	{
		/* L : window 1 */
		/* 20130218, sj.youm, add inv size to avoid main cen artifact when turn on pip */
		/* 20130221, sj.youm, add x,y comp to avoid main cen artifact when turn on pip */
		#if 0
		if(i_pstWinPrms->is_invalid_size[LX_PE_WIN_1] || \
			x0[LX_PE_WIN_0]==x0[LX_PE_WIN_1] || \
			y0[LX_PE_WIN_0]==y0[LX_PE_WIN_1] || \
			x1[LX_PE_WIN_0]==x1[LX_PE_WIN_1] || \
			y1[LX_PE_WIN_0]==y1[LX_PE_WIN_1])
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
		else if(disp0_info->mul_win == 2)
		#else
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
		#endif
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
 * @param   *i_pstCfg			[in] 	PE_TSK_O18_CFG_T
 * @param   *i_pstWinPrms		[in]	LX_PE_WIN_PARAMS_T
 * @param 	*o_pstActWinCrds	[out]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_GetActNWinCrdsForExtFRC(PE_TSK_O18_CFG_T 			*i_pstCfg,
												LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
												LX_PE_ACT_WIN_COORDINATES_T *o_pstActWinCrds)
{
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];

	UINT32 *x0 = i_pstWinPrms->x0;	UINT32 *y0 = i_pstWinPrms->y0;
	UINT32 *x1 = i_pstWinPrms->x1;	UINT32 *y1 = i_pstWinPrms->y1;
	UINT32 *x0_ofst = i_pstWinPrms->x0_ofst; UINT32 *y0_ofst = i_pstWinPrms->y0_ofst;
	UINT32 *x1_ofst = i_pstWinPrms->x1_ofst; UINT32 *y1_ofst = i_pstWinPrms->y1_ofst;

	if(disp0_info->sub_mode>LX_DE_SUB_MODE_NONE && disp0_info->sub_mode<LX_DE_SUB_MODE_MAXN)
	{
		PE_WIN_HW_O18_GetActNWinCrdsForExtFRC_PIP( i_pstCfg, i_pstWinPrms, o_pstActWinCrds );
	}
	else
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
		o_pstActWinCrds->act1_x0 = 0;
		o_pstActWinCrds->act1_y0 = 0;
		o_pstActWinCrds->act1_x1 = 0;
		o_pstActWinCrds->act1_y1 = 0;
		o_pstActWinCrds->win1_x0 = 0;
		o_pstActWinCrds->win1_y0 = 0;
		o_pstActWinCrds->win1_x1 = 0;
		o_pstActWinCrds->win1_y1 = 0;
	}
	return;
}

/**
 * Gets shp, cen & win enable for external FRC
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O18_CFG_T
 * @param   i_bIsResizeSet		[in]	BOOLEAN
 * @param 	*o_pstShpCenWinEn	[out]	LX_PE_SHP_CEN_WIN_EN_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_GetShpCenWinEnForExtFRC(PE_TSK_O18_CFG_T 		*i_pstCfg,
												BOOLEAN					i_bIsResizeSet,
												LX_PE_SHP_CEN_WIN_EN_T	*o_pstShpCenWinEn)
{
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];

	if(disp0_info->sub_mode == LX_DE_SUB_MODE_PIP)
	{
				o_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
				o_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
				o_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
				o_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
				o_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
				o_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
	}
	else if(disp0_info->sub_mode == LX_DE_SUB_MODE_PBP)
	{
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN]=(ctrl0_info->vcp_mute_on)? \
			PE_WIN_HW_O18_WIN_EN_OFF:PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
	}
	else if(disp0_info->sub_mode == LX_DE_SUB_MODE_MAGZOOM || disp0_info->sub_mode == LX_DE_SUB_MODE_LIVEZOOM) //mirror
	{
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
	}
	else
	{
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN]=(i_bIsResizeSet)? \
			PE_WIN_HW_O18_WIN_EN_OFF:PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
		o_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN__ON;
		o_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
		o_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_CEN_WIN]=PE_WIN_HW_O18_WIN_EN_OFF;
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
static void PE_WIN_HW_O18_ValidateWinCoords(LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
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

	/* check inversion, x0 vs. x1, y0 vs. y1 */
	if(io_pstActWinCrds->act0_x0>io_pstActWinCrds->act0_x1)	io_pstActWinCrds->act0_x0=io_pstActWinCrds->act0_x1;
	if(io_pstActWinCrds->act0_y0>io_pstActWinCrds->act0_y1)	io_pstActWinCrds->act0_y0=io_pstActWinCrds->act0_y1;
	if(io_pstActWinCrds->win0_x0>io_pstActWinCrds->win0_x1)	io_pstActWinCrds->win0_x0=io_pstActWinCrds->win0_x1;
	if(io_pstActWinCrds->win0_x0>io_pstActWinCrds->win0_x1)	io_pstActWinCrds->win0_x0=io_pstActWinCrds->win0_x1;
	if(io_pstActWinCrds->act1_x0>io_pstActWinCrds->act1_x1)	io_pstActWinCrds->act1_x0=io_pstActWinCrds->act1_x1;
	if(io_pstActWinCrds->act1_y0>io_pstActWinCrds->act1_y1)	io_pstActWinCrds->act1_y0=io_pstActWinCrds->act1_y1;
	if(io_pstActWinCrds->win1_x0>io_pstActWinCrds->win1_x1)	io_pstActWinCrds->win1_x0=io_pstActWinCrds->win1_x1;
	if(io_pstActWinCrds->win1_x0>io_pstActWinCrds->win1_x1)	io_pstActWinCrds->win1_x0=io_pstActWinCrds->win1_x1;

	return;
}

/**
 * Sets color enhancer
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O18_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstActWinCrds	[in]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_SetCen(PE_TSK_O18_CFG_T 					*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds)
{
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O18_CTRL_T *win_info	= &_g_pe_win_hw_o18_info.win_inf;

	if((win_info->act0_x0 != i_pstActWinCrds->act0_x0)|| (win_info->act0_y0 != i_pstActWinCrds->act0_y0)|| \
		(win_info->act0_x1 != i_pstActWinCrds->act0_x1)|| (win_info->act0_y1 != i_pstActWinCrds->act0_y1)|| \
		(win_info->act1_x0 != i_pstActWinCrds->act1_x0)|| (win_info->act1_y0 != i_pstActWinCrds->act1_y0)|| \
		(win_info->act1_x1 != i_pstActWinCrds->act1_x1)|| (win_info->act1_y1 != i_pstActWinCrds->act1_y1)) {

		if(_g_win_hw_o18_trace) {

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[set]act0 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->act0_x0,win_info->act0_y0,win_info->act0_x1,\
				win_info->act0_y1,i_pstActWinCrds->act0_x0,i_pstActWinCrds->act0_y0,\
				i_pstActWinCrds->act0_x1,i_pstActWinCrds->act0_y1);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[set]act1 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->act1_x0,win_info->act1_y0,win_info->act1_x1,\
				win_info->act1_y1,i_pstActWinCrds->act1_x0,i_pstActWinCrds->act1_y0,\
				i_pstActWinCrds->act1_x1,i_pstActWinCrds->act1_y1);
		}

		if(PE_KDRV_VER_O18)	{
            if (i_pstCfg->opr.pause_task == PE_TSK_O18_RUN_STOP_WIN2)
			{
	            PE_CEO_PE1_O18_QWr02(pe1_win2_ctrl_01,win_w0_x0,(i_pstActWinCrds->act0_x0>>1),\
	                                                  win_w0_y0,i_pstActWinCrds->act0_y0);
	            PE_CEO_PE1_O18_QWr02(pe1_win2_ctrl_02,win_w0_x1,(i_pstActWinCrds->act0_x1>>1),\
	                                                  win_w0_y1,i_pstActWinCrds->act0_y1);
			}
			else
			{
				if(_g_win_hw_o18_trace) 
				{
					PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]pause_task:%d, w0 SKIP.\n",i_pstCfg->opr.pause_task);
				}
			}
            PE_CEO_PE1_O18_QWr02(pe1_win2_ctrl_03,win_w1_x0,(i_pstActWinCrds->act1_x0>>1),\
                                                  win_w1_y0,i_pstActWinCrds->act1_y0);
            PE_CEO_PE1_O18_QWr02(pe1_win2_ctrl_04,win_w1_x1,(i_pstActWinCrds->act1_x1>>1),\
                                                  win_w1_y1,i_pstActWinCrds->act1_y1);
			#if 0
			PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_00,apl_win_ctrl_x0,(i_pstActWinCrds->act0_x0>>1),\
			 										apl_win_ctrl_y0,i_pstActWinCrds->act0_y0);
			if (disp0_info->out_type==LX_PE_OUT_PIP && ctrl0_info->hv_same)	//double window
			{
				PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_01,apl_win_ctrl_x1,(i_pstActWinCrds->act1_x1>>1),
													apl_win_ctrl_y1,i_pstActWinCrds->act1_y1);
			}
			else
			{
				PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_01,apl_win_ctrl_x1,(i_pstActWinCrds->act0_x1>>1),
													apl_win_ctrl_y1,i_pstActWinCrds->act0_y1);
			}
			#else
			if(disp0_info->sub_mode==LX_DE_SUB_MODE_PIP)//miracast
			{
				PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_00,	apl_win_ctrl_x0,(i_pstActWinCrds->act1_x0>>1),\
			 											apl_win_ctrl_y0,i_pstActWinCrds->act1_y0);
				PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_01,	apl_win_ctrl_x1,(i_pstActWinCrds->act1_x1>>1),
														apl_win_ctrl_y1,i_pstActWinCrds->act1_y1);
			}
			else if(disp0_info->sub_mode==LX_DE_SUB_MODE_PBP)//multi view
			{
				PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_00,	apl_win_ctrl_x0,(i_pstActWinCrds->act0_x0>>1),\
		 												apl_win_ctrl_y0,i_pstActWinCrds->act0_y0);
				PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_01,	apl_win_ctrl_x1,(i_pstActWinCrds->act1_x1>>1),
														apl_win_ctrl_y1,i_pstActWinCrds->act1_y1);
			}
			else
			{
				PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_00,	apl_win_ctrl_x0,(i_pstActWinCrds->act0_x0>>1),\
			 											apl_win_ctrl_y0,i_pstActWinCrds->act0_y0);
				PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_01,apl_win_ctrl_x1,(i_pstActWinCrds->act0_x1>>1),
													apl_win_ctrl_y1,i_pstActWinCrds->act0_y1);
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
	#endif /*PE_HW_O18_BRINGUP*/
	return;
}

/**
 * Sets sharpness
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O18_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstActWinCrds	[in]	LX_PE_ACT_WIN_COORDINATES_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_SetShp(PE_TSK_O18_CFG_T 					*i_pstCfg,
								 LX_PE_WIN_PARAMS_T 				*i_pstWinPrms,
								 LX_PE_ACT_WIN_COORDINATES_T 		*i_pstActWinCrds)
{
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O18_CTRL_T *win_info	= &_g_pe_win_hw_o18_info.win_inf;
	UINT32 shp_l_w0_x0, shp_l_w0_x1, shp_r_w0_x0, shp_r_w0_x1;
	UINT32 shp_l_w1_x0, shp_l_w1_x1, shp_r_w1_x0, shp_r_w1_x1;
	/* set win(shp) */
	if((win_info->win0_x0 != i_pstActWinCrds->win0_x0)|| (win_info->win0_y0 != i_pstActWinCrds->win0_y0)|| \
		(win_info->win0_x1 != i_pstActWinCrds->win0_x1)|| (win_info->win0_y1 != i_pstActWinCrds->win0_y1)|| \
		(win_info->win1_x0 != i_pstActWinCrds->win1_x0)|| (win_info->win1_y0 != i_pstActWinCrds->win1_y0)|| \
		(win_info->win1_x1 != i_pstActWinCrds->win1_x1)|| (win_info->win1_y1 != i_pstActWinCrds->win1_y1)) {

		if(_g_win_hw_o18_trace) {

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[set]win0 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->win0_x0,win_info->win0_y0,win_info->win0_x1,\
				win_info->win0_y1,i_pstActWinCrds->win0_x0,i_pstActWinCrds->win0_y0,\
				i_pstActWinCrds->win0_x1,i_pstActWinCrds->win0_y1);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[set]win1 : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				win_info->win1_x0,win_info->win1_y0,win_info->win1_x1,\
				win_info->win1_y1,i_pstActWinCrds->win1_x0,i_pstActWinCrds->win1_y0,\
				i_pstActWinCrds->win1_x1,i_pstActWinCrds->win1_y1);
		}

		if(PE_KDRV_VER_O18) {

			/* shp_l */
			shp_l_w0_x0 = (i_pstActWinCrds->win0_x0 < PE_WIN_HW_O18_FHD_H_MAX)? \
				i_pstActWinCrds->win0_x0:(PE_WIN_HW_O18_FHD_H_MAX-1);
			shp_l_w0_x1 = (i_pstActWinCrds->win0_x1 < PE_WIN_HW_O18_FHD_H_MAX)? \
				i_pstActWinCrds->win0_x1:(PE_WIN_HW_O18_FHD_H_MAX+PE_WIN_HW_O18_P1SHP_WIN_OFST-1);
			shp_l_w1_x0 = (i_pstActWinCrds->win1_x0 < PE_WIN_HW_O18_FHD_H_MAX)? \
				i_pstActWinCrds->win1_x0:(PE_WIN_HW_O18_FHD_H_MAX-1);
			shp_l_w1_x1 = (i_pstActWinCrds->win1_x1 < PE_WIN_HW_O18_FHD_H_MAX)? \
				i_pstActWinCrds->win1_x1:(PE_WIN_HW_O18_FHD_H_MAX+PE_WIN_HW_O18_P1SHP_WIN_OFST-1);

			/* shp_r */
			shp_r_w0_x0 = (i_pstActWinCrds->win0_x0 > PE_WIN_HW_O18_FHD_H_MAX)? \
				(i_pstActWinCrds->win0_x0-PE_WIN_HW_O18_FHD_H_MAX+PE_WIN_HW_O18_P1SHP_WIN_OFST):0;
			shp_r_w0_x1 = (i_pstActWinCrds->win0_x1 > PE_WIN_HW_O18_FHD_H_MAX)? \
				(i_pstActWinCrds->win0_x1-PE_WIN_HW_O18_FHD_H_MAX+PE_WIN_HW_O18_P1SHP_WIN_OFST):PE_WIN_HW_O18_P1SHP_WIN_OFST;
			shp_r_w1_x0 = (i_pstActWinCrds->win1_x0 > PE_WIN_HW_O18_FHD_H_MAX)? \
				(i_pstActWinCrds->win1_x0-PE_WIN_HW_O18_FHD_H_MAX+PE_WIN_HW_O18_P1SHP_WIN_OFST):0;
			shp_r_w1_x1 = (i_pstActWinCrds->win1_x1 > PE_WIN_HW_O18_FHD_H_MAX)? \
				(i_pstActWinCrds->win1_x1-PE_WIN_HW_O18_FHD_H_MAX+PE_WIN_HW_O18_P1SHP_WIN_OFST):PE_WIN_HW_O18_P1SHP_WIN_OFST;

			/* shp_l */
			/* esf */
            PE_SHP_O18_QWr02(shp_core0_esf_win_ctrl_01,	reg_win_esf_win_w0_x0_c0,	shp_l_w0_x0,\
														reg_win_esf_win_w0_y0_c0,	i_pstActWinCrds->win0_y0);
            PE_SHP_O18_QWr02(shp_core0_esf_win_ctrl_02,	reg_win_esf_win_w0_x1_c0,	shp_l_w0_x1,\
														reg_win_esf_win_w0_y1_c0,	i_pstActWinCrds->win0_y1);
            PE_SHP_O18_QWr02(shp_core0_esf_win_ctrl_03,	reg_win_esf_win_w1_x0_c0,	shp_l_w1_x0,\
														reg_win_esf_win_w1_y0_c0,	i_pstActWinCrds->win1_y0);
            PE_SHP_O18_QWr02(shp_core0_esf_win_ctrl_04,	reg_win_esf_win_w1_x1_c0,	shp_l_w1_x1,\
														reg_win_esf_win_w1_y1_c0,	i_pstActWinCrds->win1_y1);
			/* dp*/
			PE_SHP_O18_QWr02(shp_core0_dp_win_ctrl_01,	reg_win_dp_win_w0_x0_c0,	shp_l_w0_x0,\
														reg_win_dp_win_w0_y0_c0,	i_pstActWinCrds->win0_y0);
            PE_SHP_O18_QWr02(shp_core0_dp_win_ctrl_02,	reg_win_dp_win_w0_x1_c0,	shp_l_w0_x1,\
														reg_win_dp_win_w0_y1_c0,	i_pstActWinCrds->win0_y1);
            PE_SHP_O18_QWr02(shp_core0_dp_win_ctrl_03,	reg_win_dp_win_w1_x0_c0,	shp_l_w1_x0,\
														reg_win_dp_win_w1_y0_c0,	i_pstActWinCrds->win1_y0);
            PE_SHP_O18_QWr02(shp_core0_dp_win_ctrl_04,	reg_win_dp_win_w1_x1_c0,	shp_l_w1_x1,\
														reg_win_dp_win_w1_y1_c0,	i_pstActWinCrds->win1_y1);
			/* dj*/
			PE_SHP_O18_QWr02(shp_core0_dj_win_ctrl_01,	reg_win_dj_win_w0_x0_c0,	shp_l_w0_x0,\
														reg_win_dj_win_w0_y0_c0,	i_pstActWinCrds->win0_y0);
            PE_SHP_O18_QWr02(shp_core0_dj_win_ctrl_02,	reg_win_dj_win_w0_x1_c0,	shp_l_w0_x1,\
														reg_win_dj_win_w0_y1_c0,	i_pstActWinCrds->win0_y1);
            PE_SHP_O18_QWr02(shp_core0_dj_win_ctrl_03,	reg_win_dj_win_w1_x0_c0,	shp_l_w1_x0,\
														reg_win_dj_win_w1_y0_c0,	i_pstActWinCrds->win1_y0);
            PE_SHP_O18_QWr02(shp_core0_dj_win_ctrl_04,	reg_win_dj_win_w1_x1_c0,	shp_l_w1_x1,\
														reg_win_dj_win_w1_y1_c0,	i_pstActWinCrds->win1_y1);

			/* shp_r */
			/* esf */
            PE_SHP_O18_QWr02(shp_core1_esf_win_ctrl_01,	reg_win_esf_win_w0_x0_c1,	shp_r_w0_x0,\
														reg_win_esf_win_w0_y0_c1,	i_pstActWinCrds->win0_y0);
            PE_SHP_O18_QWr02(shp_core1_esf_win_ctrl_02,	reg_win_esf_win_w0_x1_c1,	shp_r_w0_x1,\
														reg_win_esf_win_w0_y1_c1,	i_pstActWinCrds->win0_y1);
            PE_SHP_O18_QWr02(shp_core1_esf_win_ctrl_03,	reg_win_esf_win_w1_x0_c1,	shp_r_w1_x0,\
														reg_win_esf_win_w1_y0_c1,	i_pstActWinCrds->win1_y0);
            PE_SHP_O18_QWr02(shp_core1_esf_win_ctrl_04,	reg_win_esf_win_w1_x1_c1,	shp_r_w1_x1,\
														reg_win_esf_win_w1_y1_c1,	i_pstActWinCrds->win1_y1);
			/* dp*/
			PE_SHP_O18_QWr02(shp_core1_dp_win_ctrl_01,	reg_win_dp_win_w0_x0_c1,	shp_r_w0_x0,\
														reg_win_dp_win_w0_y0_c1,	i_pstActWinCrds->win0_y0);
            PE_SHP_O18_QWr02(shp_core1_dp_win_ctrl_02,	reg_win_dp_win_w0_x1_c1,	shp_r_w0_x1,\
														reg_win_dp_win_w0_y1_c1,	i_pstActWinCrds->win0_y1);
            PE_SHP_O18_QWr02(shp_core1_dp_win_ctrl_03,	reg_win_dp_win_w1_x0_c1,	shp_r_w1_x0,\
														reg_win_dp_win_w1_y0_c1,	i_pstActWinCrds->win1_y0);
            PE_SHP_O18_QWr02(shp_core1_dp_win_ctrl_04,	reg_win_dp_win_w1_x1_c1,	shp_r_w1_x1,\
														reg_win_dp_win_w1_y1_c1,	i_pstActWinCrds->win1_y1);

			/* dj*/
			PE_SHP_O18_QWr02(shp_core1_dj_win_ctrl_01,	reg_win_dj_win_w0_x0_c1,	shp_r_w0_x0,\
														reg_win_dj_win_w0_y0_c1,	i_pstActWinCrds->win0_y0);
            PE_SHP_O18_QWr02(shp_core1_dj_win_ctrl_02,	reg_win_dj_win_w0_x1_c1,	shp_r_w0_x1,\
														reg_win_dj_win_w0_y1_c1,	i_pstActWinCrds->win0_y1);
            PE_SHP_O18_QWr02(shp_core1_dj_win_ctrl_03,	reg_win_dj_win_w1_x0_c1,	shp_r_w1_x0,\
														reg_win_dj_win_w1_y0_c1,	i_pstActWinCrds->win1_y0);
            PE_SHP_O18_QWr02(shp_core1_dj_win_ctrl_04,	reg_win_dj_win_w1_x1_c1,	shp_r_w1_x1,\
														reg_win_dj_win_w1_y1_c1,	i_pstActWinCrds->win1_y1);

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
	#endif /*PE_HW_O18_BRINGUP*/
	return;
}

/**
 * Sets sharpness window enable
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O18_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstShpCenWinEn	[in]	LX_PE_SHP_CEN_WIN_EN_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_SetShpWinEn(PE_TSK_O18_CFG_T 				*i_pstCfg,
									 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
									 LX_PE_SHP_CEN_WIN_EN_T 		*i_pstShpCenWinEn)
{
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O18_CTRL_T *win_info	= &_g_pe_win_hw_o18_info.win_inf;

	if((win_info->win0_en[PE_WIN_HW_O18_SHP_WIN] != i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN]) || \
		(win_info->win1_en[PE_WIN_HW_O18_SHP_WIN] != i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN]) || \
		(win_info->win01_en[PE_WIN_HW_O18_SHP_WIN] != i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]))
	{
		if(_g_win_hw_o18_trace) {

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[set]shp_win_en(0,1,01):%d,%d,%d \n",\
				win_info->win0_en[PE_WIN_HW_O18_SHP_WIN], win_info->win1_en[PE_WIN_HW_O18_SHP_WIN],\
				win_info->win01_en[PE_WIN_HW_O18_SHP_WIN]);
		}

		if(PE_KDRV_VER_O18) {
			#if 0

			PE_SHP_O18_QWr03(shp_core0_win1_ctrl_00,	reg_win_esf_core0_win0_en,i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN], \
														reg_win_esf_core0_win1_en,i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN], \
														reg_win_esf_core0_win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			PE_SHP_O18_QWr03(shp_core0_win2_ctrl_00,	reg_win_dpdj_core0_win0_en, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN] , \
														reg_win_dpdj_core0_win1_en, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN] , \
														reg_win_dpdj_core0_win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			PE_SHP_O18_QWr03(shp_core1_win1_ctrl_00,	reg_win_esf_core1_win0_en, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN] , \
														reg_win_esf_core1_win1_en, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN] , \
														reg_win_esf_core1_win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			PE_SHP_O18_QWr03(shp_core1_win2_ctrl_00,	reg_win_dpdj_core1_win0_en, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN] , \
														reg_win_dpdj_core1_win1_en, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN] , \
														reg_win_dpdj_core1_win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			#endif
			/*esf*/
			PE_SHP_O18_QWr03(shp_core0_esf_win_ctrl_00, reg_win_esf_win0_en_c0, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN], \
                                                        reg_win_esf_win1_en_c0, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN], \
                                                        reg_win_esf_win01_en_c0,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			PE_SHP_O18_QWr03(shp_core1_esf_win_ctrl_00, reg_win_esf_win0_en_c1, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                        reg_win_esf_win1_en_c1, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                        reg_win_esf_win01_en_c1,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			/*dp*/
			PE_SHP_O18_QWr03(shp_core0_dp_win_ctrl_00, reg_win_dp_win0_en_c0, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                  	   reg_win_dp_win1_en_c0, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                  	   reg_win_dp_win01_en_c0,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			PE_SHP_O18_QWr03(shp_core1_dp_win_ctrl_00, reg_win_dp_win0_en_c1, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                  	   reg_win_dp_win1_en_c1, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                  	   reg_win_dp_win01_en_c1,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			/*dj*/
			PE_SHP_O18_QWr03(shp_core0_dj_win_ctrl_00, reg_win_dj_win0_en_c0, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                  	   reg_win_dj_win1_en_c0, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                  	   reg_win_dj_win01_en_c0,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
			PE_SHP_O18_QWr03(shp_core1_dj_win_ctrl_00, reg_win_dj_win0_en_c1, i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                  	   reg_win_dj_win1_en_c1, i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN] , \
                                                  	   reg_win_dj_win01_en_c1,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN]);
		}

		win_info->win0_en[PE_WIN_HW_O18_SHP_WIN] = i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_SHP_WIN];
		win_info->win1_en[PE_WIN_HW_O18_SHP_WIN] = i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_SHP_WIN];
		win_info->win01_en[PE_WIN_HW_O18_SHP_WIN] = i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_SHP_WIN];
	}
	#endif /*PE_HW_O18_BRINGUP*/
	return;
}

/**
 * Sets color enhancement window enable
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O18_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @param 	*i_pstShpCenWinEn	[in]	LX_PE_SHP_CEN_WIN_EN_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_SetCenWinEn(PE_TSK_O18_CFG_T 				*i_pstCfg,
									 LX_PE_WIN_PARAMS_T 			*i_pstWinPrms,
									 LX_PE_SHP_CEN_WIN_EN_T 		*i_pstShpCenWinEn)
{
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O18_CTRL_T *win_info	= &_g_pe_win_hw_o18_info.win_inf;

	if((win_info->win0_en[PE_WIN_HW_O18_CEN_WIN] != i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_CEN_WIN]) || \
	   (win_info->win1_en[PE_WIN_HW_O18_CEN_WIN] != i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_CEN_WIN]) || \
	   (win_info->win01_en[PE_WIN_HW_O18_CEN_WIN] != i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_CEN_WIN]))
	{
		if(_g_win_hw_o18_trace) {

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[set]cen_win_en(0,1,01):%d,%d,%d \n",\
				win_info->win0_en[PE_WIN_HW_O18_CEN_WIN], win_info->win1_en[PE_WIN_HW_O18_CEN_WIN],\
				win_info->win01_en[PE_WIN_HW_O18_CEN_WIN]);
		}

		if(PE_KDRV_VER_O18) {

			PE_CEO_PE1_O18_QWr03(pe1_win2_ctrl_00,win0_en,i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_CEN_WIN], \
                                                    win1_en,i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_CEN_WIN], \
                                                    win01_en,i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_CEN_WIN]);
		}

		win_info->win0_en[PE_WIN_HW_O18_CEN_WIN] = i_pstShpCenWinEn->win0_en[PE_WIN_HW_O18_CEN_WIN];
		win_info->win1_en[PE_WIN_HW_O18_CEN_WIN] = i_pstShpCenWinEn->win1_en[PE_WIN_HW_O18_CEN_WIN];
		win_info->win01_en[PE_WIN_HW_O18_CEN_WIN] = i_pstShpCenWinEn->win01_en[PE_WIN_HW_O18_CEN_WIN];
	}
	#endif /*PE_HW_O18_BRINGUP*/
	return;
}

/**
 * Sets window resolution
 *
 * @param   *i_pstCfg			[in] 	PE_TSK_O18_CFG_T
 * @param   *i_pstWinPrms		[in] 	LX_PE_WIN_PARAMS_T
 * @return  void
 * @see
 * @author
 */
static void PE_WIN_HW_O18_SetWinResolution(PE_TSK_O18_CFG_T 			*i_pstCfg,
										   LX_PE_WIN_PARAMS_T 			*i_pstWinPrms)
{
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_INF_DISPLAY_T *disp0_info = &i_pstCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl0_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_O18_CTRL_T *ctrl1_info 	= &i_pstCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_WIN_HW_O18_CTRL_T *win_info	= &_g_pe_win_hw_o18_info.win_inf;
	UINT32 shp_top_w;

	if((win_info->h_max != i_pstWinPrms->h_max)|| (win_info->v_max != i_pstWinPrms->v_max))	{

		if(_g_win_hw_o18_trace) {

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]rev:%d,submode:%d,ofs0,1:%d,%d,%d,%d, %d,%d,%d,%d\n",\
				disp0_info->mode.is_reverse,disp0_info->sub_mode,\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_0],i_pstWinPrms->y0_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_0],i_pstWinPrms->y1_ofst[LX_PE_WIN_0],\
				i_pstWinPrms->x0_ofst[LX_PE_WIN_1],i_pstWinPrms->y0_ofst[LX_PE_WIN_1],\
				i_pstWinPrms->x1_ofst[LX_PE_WIN_1],i_pstWinPrms->y1_ofst[LX_PE_WIN_1]);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[inf]o_win0:%d,%d,%d,%d,o_win1:%d,%d,%d,%d\n",\
				ctrl0_info->u_o_win_h_ofst,ctrl0_info->u_o_win_v_ofst,ctrl0_info->u_o_win_h_size,\
				ctrl0_info->u_o_win_v_size,ctrl1_info->u_o_win_h_ofst,ctrl1_info->u_o_win_v_ofst,\
				ctrl1_info->u_o_win_h_size,ctrl1_info->u_o_win_v_size);

			PE_WIN_HW_O18_DBG_PRINT_ALWAYS("[set]h,v_max : prev:%d,%d, cur:%d,%d\n",\
				win_info->h_max,win_info->v_max,i_pstWinPrms->h_max,i_pstWinPrms->v_max);
		}

		shp_top_w = (i_pstWinPrms->h_max>>1)+PE_WIN_HW_O18_P1SHP_WIN_OFST;

		if(PE_KDRV_VER_O18) {

			PE_SHP_O18_QWr02(shp_core_ctrl_01,reg_top_width,shp_top_w,reg_top_height,i_pstWinPrms->v_max);
			PE_CEO_PE1_O18_QWr02(pe1_top_ctrl_01,width,(i_pstWinPrms->h_max>>1),height,i_pstWinPrms->v_max);
            //PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_00,apl_win_ctrl_x0,0,apl_win_ctrl_y0,0);
            //PE_CEO_PE1_O18_QWr02(pe1_apl_ctrl_01,apl_win_ctrl_x1,(i_pstWinPrms->h_max>>1),apl_win_ctrl_y1,i_pstWinPrms->v_max);
		}

		win_info->h_max = i_pstWinPrms->h_max;
		win_info->v_max = i_pstWinPrms->v_max;
	}
	#endif /*PE_HW_O18_BRINGUP*/
	return;
}



