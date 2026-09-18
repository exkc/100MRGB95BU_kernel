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

/** @file pe_csc_hw_m23.c
 *
 *  driver for picture enhance csc functions. ( used only within kdriver )
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

#include "pe_hw_m23.h"
#include "pe_reg_m23.h"
#include "pe_fwi_m23.h"
#include "pe_csc_hw_m23.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CSC_HW_M23_CHECK_CODE(_checker,_action,fmt,args...)	\
	if(_checker){PE_PRINT_ERROR(fmt,##args);_action;}

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
static UINT32 _g_csc_hw_m23_trace=0x0;		//default should be off.
static PE_CSC_HW_M23_SETTINGS_T _g_pe_csc_hw_m23_info;

/* input csc, bypass */
const UINT16 _g_pe_csc_hw_m23_in_mtrx_byps[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0x0000, 0x0000,		//  1.0000, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const UINT16 _g_pe_csc_hw_m23_in_ofst_byps[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0000, 0x0000, 0x0000};	//   0,   0,   0

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init csc
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CSC_HW_M23_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_CSC_INPUT_T *p_in_csc = &(_g_pe_csc_hw_m23_info.pre_in_csc);
	PE_FWI_M23_CSC_INPUT_T fwi_csc;
	do{
		CHECK_KNULL(pstParams);

		if (!pstParams->resume_mode)	//normal init
		{
			/* init input csc value(bypass) */
			p_in_csc->win_id = LX_PE_WIN_0;
			p_in_csc->enable = PE_ICSC_Y709_BYPASS;
			memcpy(p_in_csc->matrix, _g_pe_csc_hw_m23_in_mtrx_byps, sizeof(UINT16)*PE_NUM_OF_CSC_COEF);
			memcpy(p_in_csc->offset, _g_pe_csc_hw_m23_in_ofst_byps, sizeof(UINT16)*PE_NUM_OF_CSC_OFST);
			/* init cur_post_type */
			_g_pe_csc_hw_m23_info.cur_post_type = LX_PE_POST_CSC_Y601_LINEAR;
		}
		else	//resume init
		{
			/* set input csc from prev one */
			p_in_csc->win_id = LX_PE_WIN_0;
			fwi_csc.win_id = p_in_csc->win_id;
			fwi_csc.enable = p_in_csc->enable;
			ret = PE_FWI_M23_SetCviCsc(&fwi_csc);
			PE_CSC_HW_M23_CHECK_CODE(ret,break,"PE_FWI_M23_SetCviCsc() error.\n");
		}
		PE_DBG_NOTI("done\n");
	}while(0);
	#endif

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
int PE_CSC_HW_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_csc_hw_m23_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CSC)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CSC)),\
			pstParams->print_lvl,_g_csc_hw_m23_trace,pstParams->bypass);
	}while(0);
	return ret;
}

/**
 * set input csc
 *
 * @param   *pstParams [in] LX_PE_CSC_INPUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CSC_HW_M23_SetInputCsc(LX_PE_CSC_INPUT_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_FWI_M23_CSC_INPUT_T fwi_csc;
	PE_CSC_HW_M23_SETTINGS_T *pInfo=&_g_pe_csc_hw_m23_info;
	LX_PE_CSC_INPUT_T *pp = (LX_PE_CSC_INPUT_T *)pstParams;
	static LX_PE_CSC_INPUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_CSC_INPUT_T);

		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CSC("duplicated DB : LX_PE_CSC_INPUT_T\n");
			ret=RET_OK;
			break;
		}

		PE_DBG_CSC("set pstParams[%d] : en:%d\n"\
			"coef:%x,%x,%x, %x,%x,%x, %x,%x,%x, ofs:%x,%x,%x, %x,%x,%x\n",\
			pstParams->win_id,pstParams->enable,\
			pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],\
			pstParams->matrix[3],pstParams->matrix[4],pstParams->matrix[5],\
			pstParams->matrix[6],pstParams->matrix[7],pstParams->matrix[8],\
			pstParams->offset[0],pstParams->offset[1],pstParams->offset[2],\
			pstParams->offset[3],pstParams->offset[4],pstParams->offset[5]);

		fwi_csc.win_id = pstParams->win_id;
		fwi_csc.enable = pstParams->enable;
		ret = PE_FWI_M23_SetCviCsc(&fwi_csc);
		PE_CSC_HW_M23_CHECK_CODE(ret,break,"PE_FWI_M23_SetCviCsc() error.\n");
		if (pstParams->win_id == LX_PE_WIN_0)
		{
			memcpy(&(pInfo->pre_in_csc), pstParams, sizeof(LX_PE_CSC_INPUT_T));
		}
	}while(0);
	#endif
	return ret;
}

/**
 * set post lllut
 *
 * @param   *pstParams [in] LX_PE_CSC_LLLUT_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CSC_HW_M23_SetLllut(LX_PE_CSC_LLLUT_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	int i;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DBG_CSC("set pstParams[%d] :\n"\
			"lllut_en : %d, lllut_csc_en:%d\n"\
			"lllut_r[0~3] : %d, %d, %d, %d\n"\
			"lllut_g[0~3] : %d, %d, %d, %d\n"\
			"lllut_b[0~3] : %d, %d, %d, %d\n"\
			"matrix[0~8] : %d, %d, %d,  %d, %d, %d,  %d, %d, %d,\n"\
			"blend_in_sel : %d\n"\
			"r2y_matrix[0~2] : %d, %d, %d\n"\
			"blend_lut_x[0~5] : %d, %d, %d, %d, %d, %d\n"\
			"blend_lut_y[0~5] : %d, %d, %d, %d, %d, %d\n"\
			"hue_gain : %d, sat_gain:%d\n",\
			pstParams->win_id,pstParams->lllut_en,pstParams->lllut_csc_en,\
			pstParams->lllut_r[0],pstParams->lllut_r[1],pstParams->lllut_r[2],pstParams->lllut_r[3],\
			pstParams->lllut_g[0],pstParams->lllut_g[1],pstParams->lllut_g[2],pstParams->lllut_g[3],\
			pstParams->lllut_b[0],pstParams->lllut_b[1],pstParams->lllut_b[2],pstParams->lllut_b[3],\
			pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],\
			pstParams->matrix[3],pstParams->matrix[4],pstParams->matrix[5],\
			pstParams->matrix[6],pstParams->matrix[7],pstParams->matrix[8],\
			pstParams->blend_in_sel,\
			pstParams->r2y_matrix[0],pstParams->r2y_matrix[1],pstParams->r2y_matrix[2],\
			pstParams->blend_lut_x[0],pstParams->blend_lut_x[1],pstParams->blend_lut_x[2],\
			pstParams->blend_lut_x[3],pstParams->blend_lut_x[4],pstParams->blend_lut_x[5],\
			pstParams->blend_lut_y[0],pstParams->blend_lut_y[1],pstParams->blend_lut_y[2],\
			pstParams->blend_lut_y[3],pstParams->blend_lut_y[4],pstParams->blend_lut_y[5],\
			pstParams->hue_gain,pstParams->sat_gain);
		if(PE_KDRV_VER_M23)
		{
			PE_CC_PE1_M23_QWr03(pe1_llcore_ctrl_00,	reg_llctrl_enable,	GET_BITS(pstParams->lllut_en,0,1),\
													reg_llpcc_en,		GET_BITS(pstParams->lllut_csc_en,0,1),\
													reg_llab_inp_sel,	GET_BITS(pstParams->blend_in_sel,0,1));
			/*
			PE_CE_PE1_M23_QWr03(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0,\
														ll_lut_load,	0x0,\
														ll_lut_ai,		0x1);
			PE_CE_PE1_M23_QWr03(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0,\
														ll_lut_load,	0x0,\
														ll_lut_ai,		0x1);
														*/
 			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_load,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_ai,		0x1);
			PE_CC_PE1_M23_WrFL(pe1_lllut_e_ia_ctrl);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_load,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_ai,		0x1);
			PE_CC_PE1_M23_WrFL(pe1_lllut_o_ia_ctrl);
			for(i =0; i <64; i++)
			{
				#if 0
				PE_CE_PE1_M23_QWr03(pe1_lllut_e_ia_data,	ll_lut_dat_rcr,	GET_BITS(pstParams->lllut_r[i],0,10),\
															ll_lut_dat_gyy,	GET_BITS(pstParams->lllut_g[i],0,10),\
															ll_lut_dat_bcb,	GET_BITS(pstParams->lllut_b[i],0,10));
				PE_CE_PE1_M23_QWr03(pe1_lllut_o_ia_data,	ll_lut_dat_rcr,	GET_BITS(pstParams->lllut_r[i],0,10),\
															ll_lut_dat_gyy,	GET_BITS(pstParams->lllut_g[i],0,10),\
															ll_lut_dat_bcb,	GET_BITS(pstParams->lllut_b[i],0,10));
				#endif
				
				PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_data,	ll_lut_dat_rcr,	GET_BITS(pstParams->lllut_r[i],0,10));	//y data
				PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_data,	ll_lut_dat_gyy,	GET_BITS(pstParams->lllut_g[i],0,10));	//y data
				PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_data,	ll_lut_dat_bcb,	GET_BITS(pstParams->lllut_b[i],0,10));	//y data
				PE_CC_PE1_M23_WrFL(pe1_lllut_e_ia_data);
				
				PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_data,	ll_lut_dat_rcr,	GET_BITS(pstParams->lllut_r[i],0,10));	//y data
				PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_data,	ll_lut_dat_gyy,	GET_BITS(pstParams->lllut_g[i],0,10));	//y data
				PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_data,	ll_lut_dat_bcb,	GET_BITS(pstParams->lllut_b[i],0,10));	//y data
				PE_CC_PE1_M23_WrFL(pe1_lllut_o_ia_data);
			}
 			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_load,	0x1);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_ai,		0x0);
			PE_CC_PE1_M23_WrFL(pe1_lllut_e_ia_ctrl);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_load,	0x1);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_ai,		0x0);
			PE_CC_PE1_M23_WrFL(pe1_lllut_o_ia_ctrl);

			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_01,	reg_llpcc_coef0,	GET_BITS(pstParams->matrix[0],0,15),\
														reg_llpcc_coef1,	GET_BITS(pstParams->matrix[1],0,15));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_02,	reg_llpcc_coef2,	GET_BITS(pstParams->matrix[2],0,15),\
														reg_llpcc_coef3,	GET_BITS(pstParams->matrix[3],0,15));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_03,	reg_llpcc_coef4,	GET_BITS(pstParams->matrix[4],0,15),\
														reg_llpcc_coef5,	GET_BITS(pstParams->matrix[5],0,15));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_04,	reg_llpcc_coef6,	GET_BITS(pstParams->matrix[6],0,15),\
														reg_llpcc_coef7,	GET_BITS(pstParams->matrix[7],0,15));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_05,	reg_llpcc_coef8,	GET_BITS(pstParams->matrix[8],0,15),\
														reg_alpha_ii_yy_coef0,	GET_BITS(pstParams->r2y_matrix[0],0,15));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_06,	reg_alpha_ii_yy_coef1,	GET_BITS(pstParams->r2y_matrix[1],0,15),\
														reg_alpha_ii_yy_coef2,	GET_BITS(pstParams->r2y_matrix[2],0,15));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_07,	reg_llab_lut_y0,	GET_BITS(pstParams->blend_lut_y[0],0,10),\
														reg_llab_lut_x0,	GET_BITS(pstParams->blend_lut_x[0],0,10));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_08,	reg_llab_lut_y1,	GET_BITS(pstParams->blend_lut_y[1],0,10),\
														reg_llab_lut_x1,	GET_BITS(pstParams->blend_lut_x[1],0,10));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_09,	reg_llab_lut_y2,	GET_BITS(pstParams->blend_lut_y[2],0,10),\
														reg_llab_lut_x2,	GET_BITS(pstParams->blend_lut_x[2],0,10));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_10,	reg_llab_lut_y3,	GET_BITS(pstParams->blend_lut_y[3],0,10),\
														reg_llab_lut_x3,	GET_BITS(pstParams->blend_lut_x[3],0,10));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_11,	reg_llab_lut_y4,	GET_BITS(pstParams->blend_lut_y[4],0,10),\
														reg_llab_lut_x4,	GET_BITS(pstParams->blend_lut_x[4],0,10));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_12,	reg_llab_lut_y5,	GET_BITS(pstParams->blend_lut_y[5],0,10),\
														reg_llab_lut_x5,	GET_BITS(pstParams->blend_lut_x[5],0,10));
			PE_CC_PE1_M23_QWr02(pe1_llcore_ctrl_13,	reg_hue_prsv_ratio,	GET_BITS(pstParams->hue_gain,0,8),\
														reg_sat_prsv_ratio,	GET_BITS(pstParams->sat_gain,0,8));
			
		}
		else
		{
			PE_DBG_CSC("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	return ret;
}

/**
 * get Lllut
 *
 * @param   *pstParams [in/out] LX_PE_CSC_LLLUT_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CSC_HW_M23_GetLllut(LX_PE_CSC_LLLUT_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	int i;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M23)
		{
			PE_CC_PE1_M23_QRd03(pe1_llcore_ctrl_00,	reg_llctrl_enable,	pstParams->lllut_en,\
													reg_llpcc_en,		pstParams->lllut_csc_en,\
													reg_llab_inp_sel,	pstParams->blend_in_sel);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_load,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_ai,		0x1);
			PE_CC_PE1_M23_WrFL(pe1_lllut_e_ia_ctrl);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_load,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_ai,		0x1);
			PE_CC_PE1_M23_WrFL(pe1_lllut_o_ia_ctrl);
			for(i =0; i <64; i++)
			{
				PE_CC_PE1_M23_QRd03(pe1_lllut_e_ia_data,	ll_lut_dat_rcr,	pstParams->lllut_r[i],\
															ll_lut_dat_gyy,	pstParams->lllut_g[i],\
															ll_lut_dat_bcb,	pstParams->lllut_b[i]);
			}
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_load,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_ai,		0x0);
			PE_CC_PE1_M23_WrFL(pe1_lllut_e_ia_ctrl);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_load,	0x0);
			PE_CC_PE1_M23_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_ai,		0x0);
			PE_CC_PE1_M23_WrFL(pe1_lllut_o_ia_ctrl);

			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_01,	reg_llpcc_coef0,	pstParams->matrix[0],\
														reg_llpcc_coef1,	pstParams->matrix[1]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_02,	reg_llpcc_coef2,	pstParams->matrix[2],\
														reg_llpcc_coef3,	pstParams->matrix[3]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_03,	reg_llpcc_coef4,	pstParams->matrix[4],\
														reg_llpcc_coef5,	pstParams->matrix[5]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_04,	reg_llpcc_coef6,	pstParams->matrix[6],\
														reg_llpcc_coef7,	pstParams->matrix[7]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_05,	reg_llpcc_coef8,	pstParams->matrix[8],\
														reg_alpha_ii_yy_coef0,	pstParams->r2y_matrix[0]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_06,	reg_alpha_ii_yy_coef1,	pstParams->r2y_matrix[1],\
														reg_alpha_ii_yy_coef2,	pstParams->r2y_matrix[2]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_07,	reg_llab_lut_y0,	pstParams->blend_lut_y[0],\
														reg_llab_lut_x0,	pstParams->blend_lut_x[0]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_08,	reg_llab_lut_y1,	pstParams->blend_lut_y[1],\
														reg_llab_lut_x1,	pstParams->blend_lut_x[1]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_09,	reg_llab_lut_y2,	pstParams->blend_lut_y[2],\
														reg_llab_lut_x2,	pstParams->blend_lut_x[2]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_10,	reg_llab_lut_y3,	pstParams->blend_lut_y[3],\
														reg_llab_lut_x3,	pstParams->blend_lut_x[3]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_11,	reg_llab_lut_y4,	pstParams->blend_lut_y[4],\
														reg_llab_lut_x4,	pstParams->blend_lut_x[4]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_12,	reg_llab_lut_y5,	pstParams->blend_lut_y[5],\
														reg_llab_lut_x5,	pstParams->blend_lut_x[5]);
			PE_CC_PE1_M23_QRd02(pe1_llcore_ctrl_13,	reg_hue_prsv_ratio,	pstParams->hue_gain,\
														reg_sat_prsv_ratio,	pstParams->sat_gain);
			
		}
		else
		{
			PE_DBG_CSC("nothing to do\n");	ret = RET_OK;
		}
		PE_DBG_CSC("get pstParams[%d] :\n"\
			"lllut_en : %d, lllut_csc_en:%d\n"\
			"lllut_r[0~3] : %d, %d, %d, %d\n"\
			"lllut_g[0~3] : %d, %d, %d, %d\n"\
			"lllut_b[0~3] : %d, %d, %d, %d\n"\
			"matrix[0~8] : %d, %d, %d,  %d, %d, %d,  %d, %d, %d,\n"\
			"blend_in_sel : %d\n"\
			"r2y_matrix[0~2] : %d, %d, %d\n"\
			"blend_lut_x[0~5] : %d, %d, %d, %d, %d, %d\n"\
			"blend_lut_y[0~5] : %d, %d, %d, %d, %d, %d\n"\
			"hue_gain : %d, sat_gain:%d\n",\
			pstParams->win_id,pstParams->lllut_en,pstParams->lllut_csc_en,\
			pstParams->lllut_r[0],pstParams->lllut_r[1],pstParams->lllut_r[2],pstParams->lllut_r[3],\
			pstParams->lllut_g[0],pstParams->lllut_g[1],pstParams->lllut_g[2],pstParams->lllut_g[3],\
			pstParams->lllut_b[0],pstParams->lllut_b[1],pstParams->lllut_b[2],pstParams->lllut_b[3],\
			pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],\
			pstParams->matrix[3],pstParams->matrix[4],pstParams->matrix[5],\
			pstParams->matrix[6],pstParams->matrix[7],pstParams->matrix[8],\
			pstParams->blend_in_sel,\
			pstParams->r2y_matrix[0],pstParams->r2y_matrix[1],pstParams->r2y_matrix[2],\
			pstParams->blend_lut_x[0],pstParams->blend_lut_x[1],pstParams->blend_lut_x[2],\
			pstParams->blend_lut_x[3],pstParams->blend_lut_x[4],pstParams->blend_lut_x[5],\
			pstParams->blend_lut_y[0],pstParams->blend_lut_y[1],pstParams->blend_lut_y[2],\
			pstParams->blend_lut_y[3],pstParams->blend_lut_y[4],pstParams->blend_lut_y[5],\
			pstParams->hue_gain,pstParams->sat_gain);
		
	}while(0);
	#endif
	return ret;
}

