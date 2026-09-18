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

/** @file pe_csc_hw_o26.c
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
#define PE_CSC_HW_O26_CVI_A		0
#define PE_CSC_HW_O26_CVI_B		1
#define PE_CSC_HW_O26_CVI_C		2
#define PE_CSC_HW_O26_CVI_D		3

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
#include "pe_fwi_o26.h"
#include "pe_csc_hw_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CSC_HW_O26_CHECK_CODE(_checker,_action,fmt,args...)	\
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
static UINT32 _g_csc_hw_o26_trace=0x0;		//default should be off.
static PE_CSC_HW_O26_SETTINGS_T _g_pe_csc_hw_o26_info;

/* input csc, bypass */
const UINT16 _g_pe_csc_hw_o26_in_mtrx_byps[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0x0000, 0x0000,		//  1.0000, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const UINT16 _g_pe_csc_hw_o26_in_ofst_byps[PE_NUM_OF_CSC_OFST] = {
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
int PE_CSC_HW_O26_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	LX_PE_CSC_INPUT_T *p_in_csc;
	PE_FWI_O26_CSC_INPUT_T fwi_csc;
	//PE_REG_O26_HW_OPT_T hw_opt = PE_REG_O26_GetDispOpt();
	int i;
	do{
		CHECK_KNULL(pstParams);
		if (!pstParams->resume_mode)	//normal init
		{
			p_in_csc = &(_g_pe_csc_hw_o26_info.pre_in_csc[0]);
			/* init input csc value(bypass) */
			p_in_csc->win_id = LX_PE_WIN_0;
			p_in_csc->enable = PE_ICSC_Y709_BYPASS;
			memcpy(p_in_csc->matrix, _g_pe_csc_hw_o26_in_mtrx_byps, sizeof(UINT16)*PE_NUM_OF_CSC_COEF);
			memcpy(p_in_csc->offset, _g_pe_csc_hw_o26_in_ofst_byps, sizeof(UINT16)*PE_NUM_OF_CSC_OFST);
		}
		else	//resume init
		{
			/* set input csc from prev one */
			for( i =0; i < LX_PE_WIN_ALL; i++)
			{
				p_in_csc = &(_g_pe_csc_hw_o26_info.pre_in_csc[i]);
				if(p_in_csc->enable == 0)
					continue;
				p_in_csc->win_id = (LX_PE_WIN_ID)i;
				fwi_csc.win_id = p_in_csc->win_id;
				fwi_csc.enable = p_in_csc->enable;
				ret = PE_FWI_O26_SetCviCsc(&fwi_csc);
				PE_CSC_HW_O26_CHECK_CODE(ret,break,"PE_FWI_O26_SetCviCsc() error.\n");
			}
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/

	#if 0	/* O26F22_APB */
	do {
		UINT32 i;
		UINT32 lut_data;
		if (pstParams->resume_mode == 1)	break;//if qsm,skip
		if (!gPE_CHPI_DDR_O26)	break;
		/* addr */
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_e_ia_ctrl_s.uaddr32,0xF4060950);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_o_ia_ctrl_s.uaddr32,0xF4060958);
		for (i=0; i<64; i++)
		{
			PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_e_ia_data[i].uaddr32,0xF4060954);
			PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_o_ia_data[i].uaddr32,0xF406095C);
		}
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_e_ia_ctrl_e.uaddr32,0xF4060950);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_o_ia_ctrl_e.uaddr32,0xF4060958);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_00.uaddr32,0xF4060960);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_01.uaddr32,0xF4060964);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_02.uaddr32,0xF4060968);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_03.uaddr32,0xF406096C);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_04.uaddr32,0xF4060970);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_05.uaddr32,0xF4060974);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_06.uaddr32,0xF4060978);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_07.uaddr32,0xF406097C);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_08.uaddr32,0xF4060980);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_09.uaddr32,0xF4060984);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_10.uaddr32,0xF4060988);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_11.uaddr32,0xF406098C);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_12.uaddr32,0xF4060990);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_13.uaddr32,0xF4060994);
		/* init */
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_e_ia_ctrl_s.udata32,0x00001000);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_o_ia_ctrl_s.udata32,0x00001000);
		for (i=0; i<64; i++)
		{
			lut_data += i;
			lut_data += (i<<10);
			lut_data += (i<<20);
			PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_e_ia_data[i].udata32,lut_data);
			PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_o_ia_data[i].udata32,lut_data);
		}
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_e_ia_ctrl_e.udata32,0x00000100);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_lllut_o_ia_ctrl_e.udata32,0x00000100);

		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_00.udata32,0x00000100);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_01.udata32,0x00001000);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_02.udata32,0x00000000);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_03.udata32,0x00001000);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_04.udata32,0x00000000);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_05.udata32,0x0AD91000);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_06.udata32,0x043400F3);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_07.udata32,0x00000000);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_08.udata32,0x00200000);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_09.udata32,0x004003FF);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_10.udata32,0x010003FF);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_11.udata32,0x020003FF);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_12.udata32,0x03FF03FF);
		PE_CHPI_APB0_O26F22_QWr(lll0.pe1_llcore_ctrl_13.udata32,0x00FF00FF);
		/* header */
		PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_LLL0);
		PE_INF_HW_O26_BACKUP_CHPI0("[APB][LLL]done(resume:%d)",pstParams->resume_mode);
	} while(0);
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
int PE_CSC_HW_O26_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_csc_hw_o26_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CSC)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CSC)),\
			pstParams->print_lvl,_g_csc_hw_o26_trace,pstParams->bypass);
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
int PE_CSC_HW_O26_SetInputCsc(LX_PE_CSC_INPUT_T *pstParams)
{
	int ret = RET_OK;
	#if 1//ndef PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	PE_FWI_O26_CSC_INPUT_T fwi_csc;
	PE_CSC_HW_O26_SETTINGS_T *pInfo=&_g_pe_csc_hw_o26_info;
	do{
		LX_PE_CSC_INPUT_T *pp;
		static LX_PE_CSC_INPUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		//__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		pp = (LX_PE_CSC_INPUT_T *)pstParams;
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CSC_INPUT_T);
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

		win_id = pstParams->win_id;
		if (win_id == LX_PE_WIN_1)			pstParams->win_id = PE_CSC_HW_O26_CVI_B;
		else if (win_id == LX_PE_WIN_2)		pstParams->win_id = PE_CSC_HW_O26_CVI_C;
		else if (win_id == LX_PE_WIN_3)		pstParams->win_id = PE_CSC_HW_O26_CVI_D;
		else								pstParams->win_id = PE_CSC_HW_O26_CVI_A;

		fwi_csc.win_id = pstParams->win_id;
		fwi_csc.enable = pstParams->enable;
		ret = PE_FWI_O26_SetCviCsc(&fwi_csc);
		PE_CSC_HW_O26_CHECK_CODE(ret,break,"PE_FWI_O26_SetCviCsc() error.\n");
		memcpy(&(pInfo->pre_in_csc[pstParams->win_id]), pstParams, sizeof(LX_PE_CSC_INPUT_T));
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_CSC_HW_O26_SetLllut(LX_PE_CSC_LLLUT_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
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

		PE_CC_PE1_O26_QWr03(pe1_llcore_ctrl_00,	reg_llctrl_enable,	GET_BITS(pstParams->lllut_en,0,1),\
												reg_llpcc_en,		GET_BITS(pstParams->lllut_csc_en,0,1),\
												reg_llab_inp_sel,	GET_BITS(pstParams->blend_in_sel,0,1));

		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_load,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_ai,		0x1);
		PE_CC_PE1_O26_WrFL(pe1_lllut_e_ia_ctrl);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_load,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_ai,		0x1);
		PE_CC_PE1_O26_WrFL(pe1_lllut_o_ia_ctrl);
		for(i =0; i <64; i++)
		{
			PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_data,	ll_lut_dat_rcr,	GET_BITS(pstParams->lllut_r[i],0,10));	//y data
			PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_data,	ll_lut_dat_gyy,	GET_BITS(pstParams->lllut_g[i],0,10));	//y data
			PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_data,	ll_lut_dat_bcb,	GET_BITS(pstParams->lllut_b[i],0,10));	//y data
			PE_CC_PE1_O26_WrFL(pe1_lllut_e_ia_data);
			
			PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_data,	ll_lut_dat_rcr,	GET_BITS(pstParams->lllut_r[i],0,10));	//y data
			PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_data,	ll_lut_dat_gyy,	GET_BITS(pstParams->lllut_g[i],0,10));	//y data
			PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_data,	ll_lut_dat_bcb,	GET_BITS(pstParams->lllut_b[i],0,10));	//y data
			PE_CC_PE1_O26_WrFL(pe1_lllut_o_ia_data);
		}
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_load,	0x1);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_ai,		0x0);
		PE_CC_PE1_O26_WrFL(pe1_lllut_e_ia_ctrl);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_load,	0x1);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_ai,		0x0);
		PE_CC_PE1_O26_WrFL(pe1_lllut_o_ia_ctrl);

		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_01,	reg_llpcc_coef0,	GET_BITS(pstParams->matrix[0],0,15),\
													reg_llpcc_coef1,	GET_BITS(pstParams->matrix[1],0,15));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_02,	reg_llpcc_coef2,	GET_BITS(pstParams->matrix[2],0,15),\
													reg_llpcc_coef3,	GET_BITS(pstParams->matrix[3],0,15));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_03,	reg_llpcc_coef4,	GET_BITS(pstParams->matrix[4],0,15),\
													reg_llpcc_coef5,	GET_BITS(pstParams->matrix[5],0,15));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_04,	reg_llpcc_coef6,	GET_BITS(pstParams->matrix[6],0,15),\
													reg_llpcc_coef7,	GET_BITS(pstParams->matrix[7],0,15));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_05,	reg_llpcc_coef8,	GET_BITS(pstParams->matrix[8],0,15),\
													reg_alpha_ii_yy_coef0,	GET_BITS(pstParams->r2y_matrix[0],0,15));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_06,	reg_alpha_ii_yy_coef1,	GET_BITS(pstParams->r2y_matrix[1],0,15),\
													reg_alpha_ii_yy_coef2,	GET_BITS(pstParams->r2y_matrix[2],0,15));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_07,	reg_llab_lut_y0,	GET_BITS(pstParams->blend_lut_y[0],0,10),\
													reg_llab_lut_x0,	GET_BITS(pstParams->blend_lut_x[0],0,10));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_08,	reg_llab_lut_y1,	GET_BITS(pstParams->blend_lut_y[1],0,10),\
													reg_llab_lut_x1,	GET_BITS(pstParams->blend_lut_x[1],0,10));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_09,	reg_llab_lut_y2,	GET_BITS(pstParams->blend_lut_y[2],0,10),\
													reg_llab_lut_x2,	GET_BITS(pstParams->blend_lut_x[2],0,10));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_10,	reg_llab_lut_y3,	GET_BITS(pstParams->blend_lut_y[3],0,10),\
													reg_llab_lut_x3,	GET_BITS(pstParams->blend_lut_x[3],0,10));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_11,	reg_llab_lut_y4,	GET_BITS(pstParams->blend_lut_y[4],0,10),\
													reg_llab_lut_x4,	GET_BITS(pstParams->blend_lut_x[4],0,10));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_12,	reg_llab_lut_y5,	GET_BITS(pstParams->blend_lut_y[5],0,10),\
													reg_llab_lut_x5,	GET_BITS(pstParams->blend_lut_x[5],0,10));
		PE_CC_PE1_O26_QWr02(pe1_llcore_ctrl_13,	reg_hue_prsv_ratio,	GET_BITS(pstParams->hue_gain,0,8),\
													reg_sat_prsv_ratio,	GET_BITS(pstParams->sat_gain,0,8));
	}while(0);

	#if 0	/* O26F22_APB */
	do {
		if (!gPE_CHPI_DDR_O26)	break;
		int i;
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_00.reg_llctrl_enable,	GET_BITS(pstParams->lllut_en,0,1));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_00.reg_llpcc_en,		GET_BITS(pstParams->lllut_csc_en,0,1));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_00.reg_llab_inp_sel,	GET_BITS(pstParams->blend_in_sel,0,1));
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_00.udata32);
		for(i=0;i<64;i++)
		{
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_e_ia_data[i].ll_lut_dat_rcr, GET_BITS(pstParams->lllut_r[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_e_ia_data[i].ll_lut_dat_gyy, GET_BITS(pstParams->lllut_g[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_e_ia_data[i].ll_lut_dat_bcb, GET_BITS(pstParams->lllut_b[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_lllut_e_ia_data[i].udata32);
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_o_ia_data[i].ll_lut_dat_rcr, GET_BITS(pstParams->lllut_r[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_o_ia_data[i].ll_lut_dat_gyy, GET_BITS(pstParams->lllut_g[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_o_ia_data[i].ll_lut_dat_bcb, GET_BITS(pstParams->lllut_b[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_lllut_o_ia_data[i].udata32);
		}

		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_01.reg_llpcc_coef0,	GET_BITS(pstParams->matrix[0],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_01.reg_llpcc_coef1,	GET_BITS(pstParams->matrix[1],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_02.reg_llpcc_coef2,	GET_BITS(pstParams->matrix[2],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_02.reg_llpcc_coef3,	GET_BITS(pstParams->matrix[3],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_03.reg_llpcc_coef4,	GET_BITS(pstParams->matrix[4],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_03.reg_llpcc_coef5,	GET_BITS(pstParams->matrix[5],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_04.reg_llpcc_coef6,	GET_BITS(pstParams->matrix[6],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_04.reg_llpcc_coef7,	GET_BITS(pstParams->matrix[7],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_05.reg_llpcc_coef8,	GET_BITS(pstParams->matrix[8],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_05.reg_alpha_ii_yy_coef0,	GET_BITS(pstParams->r2y_matrix[0],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_06.reg_alpha_ii_yy_coef1,	GET_BITS(pstParams->r2y_matrix[1],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_06.reg_alpha_ii_yy_coef2,	GET_BITS(pstParams->r2y_matrix[2],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_07.reg_llab_lut_y0,	GET_BITS(pstParams->blend_lut_y[0],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_07.reg_llab_lut_x0,	GET_BITS(pstParams->blend_lut_x[0],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_08.reg_llab_lut_y1,	GET_BITS(pstParams->blend_lut_y[1],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_08.reg_llab_lut_x1,	GET_BITS(pstParams->blend_lut_x[1],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_09.reg_llab_lut_y2,	GET_BITS(pstParams->blend_lut_y[2],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_09.reg_llab_lut_x2,	GET_BITS(pstParams->blend_lut_x[2],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_10.reg_llab_lut_y3,	GET_BITS(pstParams->blend_lut_y[3],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_10.reg_llab_lut_x3,	GET_BITS(pstParams->blend_lut_x[3],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_11.reg_llab_lut_y4,	GET_BITS(pstParams->blend_lut_y[4],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_11.reg_llab_lut_x4,	GET_BITS(pstParams->blend_lut_x[4],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_12.reg_llab_lut_y5,	GET_BITS(pstParams->blend_lut_y[5],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_12.reg_llab_lut_x5,	GET_BITS(pstParams->blend_lut_x[5],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_13.reg_hue_prsv_ratio, GET_BITS(pstParams->hue_gain,0,8));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_13.reg_sat_prsv_ratio, GET_BITS(pstParams->sat_gain,0,8));

		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_01.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_02.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_03.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_04.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_05.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_06.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_07.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_08.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_09.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_10.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_11.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_12.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_13.udata32);
		PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_LLL0);
	} while(0);
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_CSC_HW_O26_GetLllut(LX_PE_CSC_LLLUT_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	int i;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);

		PE_CC_PE1_O26_QRd03(pe1_llcore_ctrl_00,	reg_llctrl_enable,	pstParams->lllut_en,\
												reg_llpcc_en,		pstParams->lllut_csc_en,\
												reg_llab_inp_sel,	pstParams->blend_in_sel);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_load,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_ai,		0x1);
		PE_CC_PE1_O26_WrFL(pe1_lllut_e_ia_ctrl);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_load,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_ai,		0x1);
		PE_CC_PE1_O26_WrFL(pe1_lllut_o_ia_ctrl);
		for(i =0; i <64; i++)
		{
			PE_CC_PE1_O26_QRd03(pe1_lllut_e_ia_data,	ll_lut_dat_rcr,	pstParams->lllut_r[i],\
														ll_lut_dat_gyy,	pstParams->lllut_g[i],\
														ll_lut_dat_bcb,	pstParams->lllut_b[i]);
		}
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_addr,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_load,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_e_ia_ctrl,	ll_lut_ai,		0x0);
		PE_CC_PE1_O26_WrFL(pe1_lllut_e_ia_ctrl);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_addr,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_load,	0x0);
		PE_CC_PE1_O26_Wr01(pe1_lllut_o_ia_ctrl,	ll_lut_ai,		0x0);
		PE_CC_PE1_O26_WrFL(pe1_lllut_o_ia_ctrl);

		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_01,	reg_llpcc_coef0,	pstParams->matrix[0],\
													reg_llpcc_coef1,	pstParams->matrix[1]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_02,	reg_llpcc_coef2,	pstParams->matrix[2],\
													reg_llpcc_coef3,	pstParams->matrix[3]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_03,	reg_llpcc_coef4,	pstParams->matrix[4],\
													reg_llpcc_coef5,	pstParams->matrix[5]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_04,	reg_llpcc_coef6,	pstParams->matrix[6],\
													reg_llpcc_coef7,	pstParams->matrix[7]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_05,	reg_llpcc_coef8,	pstParams->matrix[8],\
													reg_alpha_ii_yy_coef0,	pstParams->r2y_matrix[0]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_06,	reg_alpha_ii_yy_coef1,	pstParams->r2y_matrix[1],\
													reg_alpha_ii_yy_coef2,	pstParams->r2y_matrix[2]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_07,	reg_llab_lut_y0,	pstParams->blend_lut_y[0],\
													reg_llab_lut_x0,	pstParams->blend_lut_x[0]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_08,	reg_llab_lut_y1,	pstParams->blend_lut_y[1],\
													reg_llab_lut_x1,	pstParams->blend_lut_x[1]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_09,	reg_llab_lut_y2,	pstParams->blend_lut_y[2],\
													reg_llab_lut_x2,	pstParams->blend_lut_x[2]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_10,	reg_llab_lut_y3,	pstParams->blend_lut_y[3],\
													reg_llab_lut_x3,	pstParams->blend_lut_x[3]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_11,	reg_llab_lut_y4,	pstParams->blend_lut_y[4],\
													reg_llab_lut_x4,	pstParams->blend_lut_x[4]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_12,	reg_llab_lut_y5,	pstParams->blend_lut_y[5],\
													reg_llab_lut_x5,	pstParams->blend_lut_x[5]);
		PE_CC_PE1_O26_QRd02(pe1_llcore_ctrl_13,	reg_hue_prsv_ratio,	pstParams->hue_gain,\
													reg_sat_prsv_ratio,	pstParams->sat_gain);

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
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_CSC_HW_O26_SetPostPcc(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	LX_PE_CSC_POST_PCC_CTRL_T *pp;
	int i;
	do{
		
		CHECK_KNULL(pstParams);
		pp = (LX_PE_CSC_POST_PCC_CTRL_T *)pstParams;
		PE_CHECK_WINID(pp->win_id);
		PE_DBG_CSC("set pstParams[%d] :\n"\
			"sat_gain : %d, hue_comp_gain:%d, sat_comp_gain%d,\n"\
			"luma_gain_lut_x[0~3] : %d, %d, %d, %d\n"\
			"luma_gain_lut_y[0~3] : %d, %d, %d, %d\n"\
			"sat_gain_lut_x[0~4] : %d, %d, %d, %d, %d\n"\
			"sat_gain_lut_y[0~4] : %d, %d, %d, %d, %d\n",\
			pp->win_id,pp->sat_gain,pp->hue_comp_gain,pp->sat_comp_gain,\
			pp->luma_gain_lut_x[0],pp->luma_gain_lut_x[1],pp->luma_gain_lut_x[2],pp->luma_gain_lut_x[3],\
			pp->luma_gain_lut_y[0],pp->luma_gain_lut_y[1],pp->luma_gain_lut_y[2],pp->luma_gain_lut_y[3],\
			pp->sat_gain_lut_x[0],pp->sat_gain_lut_x[1],pp->sat_gain_lut_x[2],\
			pp->sat_gain_lut_x[3],pp->sat_gain_lut_x[4],\
			pp->sat_gain_lut_y[0],pp->sat_gain_lut_y[1],pp->sat_gain_lut_y[2],\
			pp->sat_gain_lut_y[3],pp->sat_gain_lut_y[4]);

		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_01,	reg_sat_prsv_ratio,	GET_BITS(pp->sat_comp_gain,0,8),\
												reg_hue_prsv_ratio,	GET_BITS(pp->hue_comp_gain,0,8));

		PE_CC_PE1_O26_QWr01(pe1_ppcc_ctrl_00,	reg_sat_gain,	GET_BITS(pp->sat_gain,0,10));

		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_02,	reg_luma0_lut_x0_i,	GET_BITS(pp->luma_gain_lut_x[0],0,10),\
												reg_luma0_lut_x1_i,	GET_BITS(pp->luma_gain_lut_x[1],0,10));
		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_03,	reg_luma0_lut_x2_i,	GET_BITS(pp->luma_gain_lut_x[2],0,10),\
												reg_luma0_lut_x3_i,	GET_BITS(pp->luma_gain_lut_x[3],0,10));
		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_04,	reg_luma0_lut_y0_i,	GET_BITS(pp->luma_gain_lut_y[0],0,10),\
												reg_luma0_lut_y1_i,	GET_BITS(pp->luma_gain_lut_y[1],0,10));
		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_05,	reg_luma0_lut_y2_i,	GET_BITS(pp->luma_gain_lut_y[2],0,10),\
												reg_luma0_lut_y3_i,	GET_BITS(pp->luma_gain_lut_y[3],0,10));

		
		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_06,	reg_satu0_lut_x0_i,	GET_BITS(pp->sat_gain_lut_x[0],0,10),\
												reg_satu0_lut_x1_i,	GET_BITS(pp->sat_gain_lut_x[1],0,10));
		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_07,	reg_satu0_lut_x2_i,	GET_BITS(pp->sat_gain_lut_x[2],0,10),\
												reg_satu0_lut_x3_i,	GET_BITS(pp->sat_gain_lut_x[3],0,10));
		PE_CC_PE1_O26_QWr01(pe1_ppcc_ctrl_08,	reg_satu0_lut_x4_i,	GET_BITS(pp->sat_gain_lut_x[4],0,10));
		
		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_09,	reg_satu0_lut_y0_i,	GET_BITS(pp->sat_gain_lut_y[0],0,10),\
												reg_satu0_lut_y1_i,	GET_BITS(pp->sat_gain_lut_y[1],0,10));
		PE_CC_PE1_O26_QWr02(pe1_ppcc_ctrl_10,	reg_satu0_lut_y2_i,	GET_BITS(pp->sat_gain_lut_y[2],0,10),\
												reg_satu0_lut_y3_i,	GET_BITS(pp->sat_gain_lut_y[3],0,10));
		PE_CC_PE1_O26_QWr01(pe1_ppcc_ctrl_11,	reg_satu0_lut_y4_i,	GET_BITS(pp->sat_gain_lut_y[4],0,10));
		
	}while(0);

	#if 0	/* O26F22_APB */
	do {
		if (!gPE_CHPI_DDR_O26)	break;
		int i;
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_00.reg_llctrl_enable,	GET_BITS(pstParams->lllut_en,0,1));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_00.reg_llpcc_en,		GET_BITS(pstParams->lllut_csc_en,0,1));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_00.reg_llab_inp_sel,	GET_BITS(pstParams->blend_in_sel,0,1));
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_00.udata32);
		for(i=0;i<64;i++)
		{
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_e_ia_data[i].ll_lut_dat_rcr, GET_BITS(pstParams->lllut_r[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_e_ia_data[i].ll_lut_dat_gyy, GET_BITS(pstParams->lllut_g[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_e_ia_data[i].ll_lut_dat_bcb, GET_BITS(pstParams->lllut_b[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_lllut_e_ia_data[i].udata32);
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_o_ia_data[i].ll_lut_dat_rcr, GET_BITS(pstParams->lllut_r[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_o_ia_data[i].ll_lut_dat_gyy, GET_BITS(pstParams->lllut_g[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_Wr(lll0.pe1_lllut_o_ia_data[i].ll_lut_dat_bcb, GET_BITS(pstParams->lllut_b[i],0,10));	//y data
			PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_lllut_o_ia_data[i].udata32);
		}

		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_01.reg_llpcc_coef0,	GET_BITS(pstParams->matrix[0],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_01.reg_llpcc_coef1,	GET_BITS(pstParams->matrix[1],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_02.reg_llpcc_coef2,	GET_BITS(pstParams->matrix[2],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_02.reg_llpcc_coef3,	GET_BITS(pstParams->matrix[3],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_03.reg_llpcc_coef4,	GET_BITS(pstParams->matrix[4],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_03.reg_llpcc_coef5,	GET_BITS(pstParams->matrix[5],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_04.reg_llpcc_coef6,	GET_BITS(pstParams->matrix[6],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_04.reg_llpcc_coef7,	GET_BITS(pstParams->matrix[7],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_05.reg_llpcc_coef8,	GET_BITS(pstParams->matrix[8],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_05.reg_alpha_ii_yy_coef0,	GET_BITS(pstParams->r2y_matrix[0],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_06.reg_alpha_ii_yy_coef1,	GET_BITS(pstParams->r2y_matrix[1],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_06.reg_alpha_ii_yy_coef2,	GET_BITS(pstParams->r2y_matrix[2],0,15));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_07.reg_llab_lut_y0,	GET_BITS(pstParams->blend_lut_y[0],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_07.reg_llab_lut_x0,	GET_BITS(pstParams->blend_lut_x[0],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_08.reg_llab_lut_y1,	GET_BITS(pstParams->blend_lut_y[1],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_08.reg_llab_lut_x1,	GET_BITS(pstParams->blend_lut_x[1],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_09.reg_llab_lut_y2,	GET_BITS(pstParams->blend_lut_y[2],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_09.reg_llab_lut_x2,	GET_BITS(pstParams->blend_lut_x[2],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_10.reg_llab_lut_y3,	GET_BITS(pstParams->blend_lut_y[3],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_10.reg_llab_lut_x3,	GET_BITS(pstParams->blend_lut_x[3],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_11.reg_llab_lut_y4,	GET_BITS(pstParams->blend_lut_y[4],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_11.reg_llab_lut_x4,	GET_BITS(pstParams->blend_lut_x[4],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_12.reg_llab_lut_y5,	GET_BITS(pstParams->blend_lut_y[5],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_12.reg_llab_lut_x5,	GET_BITS(pstParams->blend_lut_x[5],0,10));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_13.reg_hue_prsv_ratio, GET_BITS(pstParams->hue_gain,0,8));
		PE_CHPI_APB0_O26F22_Wr(lll0.pe1_llcore_ctrl_13.reg_sat_prsv_ratio, GET_BITS(pstParams->sat_gain,0,8));

		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_01.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_02.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_03.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_04.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_05.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_06.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_07.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_08.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_09.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_10.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_11.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_12.udata32);
		PE_CHPI_APB0_O26F22_WrFL(lll0.pe1_llcore_ctrl_13.udata32);
		PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_LLL0);
	} while(0);
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

