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

/** @file pe_dcm_hw_m23.c
 *
 *  driver for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	- dynamic contrast enhancement, histogram information and configuration.
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.16
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
#include "pe_cmn_hw_m23.h"
#include "pe_dcm_hw_m23.h"
#include "pe_drc_def.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_HW_M23_DCE_LUT_NUM	2
#define PE_DCM_HW_M23_DCE_CNT_NUM	0xfff

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_HW_M23_CHECK_CODE(_checker,_action,fmt,args...) \
	{if(_checker){PE_PRINT_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern const UINT32 g_pe_cmn_hw_m23_crc_table[256];

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_DCM_HW_M23_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
// static int PE_DCM_HW_M23F22_DownloadDYN(void *pstParams);
// static int PE_DCM_HW_M23F22_DownloadAPL(void *pstParams);
// static int PE_DCM_HW_M23F22_DownloadGain(void *pstParams);
// static int PE_DCM_HW_M23F22_DownloadTable(void *pstParams);
// static int PE_DCM_HW_M23F22_DownloadCNTGain(void *pstParams);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_dcm_hw_m23_trace=0x0;	//default should be off.
static PE_DCM_HW_M23_SETTINGS_T _g_pe_dcm_hw_m23_info;
static UINT32 _g_dcm_hw_m23_pre_dse_lut[(PE_DCM_HW_M23_LUT_MAX-1)];	///<previous dse lut

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init dynamic contrast module
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 count = 0;
	int i;
	LX_PE_DCM_DCE_CONF_T stParams;
	UINT32 *p_pre_dse_lut = _g_dcm_hw_m23_pre_dse_lut;
	UINT32 dce_lut_data[32] = {\
		0, 64, 96, 128, 160, 192, 224, 256, \
		288, 320, 352, 384, 416, 448, 480, 512, \
		544, 576, 608, 640, 672, 704, 736, 768, \
		800, 832, 864, 896, 928, 940, 992, 1023};
	UINT32 dse_lut_data[32] = {\
		   0,  64, 128, 192, 256, 320, 384, 448, 512, \
		 576, 640, 704, 768, 832, 896, 960,1023,1023, \
		1023,1023,1023,1023,1023,1023,1023,1023,1023, \
		1023,1023,1023,1023,1023};
	PE_REG_M23_HW_OPT_T hw_opt = PE_REG_M23_GetDispOpt();
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			PE_DBG_DCM("init histo info.\n");
			memset0(_g_pe_dcm_hw_m23_info);
			_g_pe_dcm_hw_m23_info.cur_blur_gain = 0xf;
			_g_pe_dcm_hw_m23_info.pre_blur_gain = 0xf;
			/* dce init */
			PE_CC_PE1_M23_Wr(pe1_dce_hist_ia_ctrl,0x00008000);	//0:read mode, 1:normal mode
			PE_CC_PE1_M23_WrFL(pe1_dce_hist_ia_ctrl);
			/* set blur_v_gain 0xf temporally */
			//PE_CEO_PE1_M23_QWr01(pe1_dce_ctrl_01,blur_v_gain,0xf);	//0x0:blur V ~ 0xf:original V
			PE_DBG_DCM("init dce config\n");
			/* synchronization with pe1_win2_ctrl_00 win_en(0,1,01) aettings in win.c */
			PE_CC_PE1_M23_QWr03(pe1_dce_ctrl_00,window0_enable, 0x1,\
                                                   window1_enable, 0x1,\
                                                   window01_enable,0x1);
			stParams.domain = LX_PE_YC_DOMAIN;
			stParams.min_pos = 26;
			stParams.max_pos = 220;
			stParams.win_id = LX_PE_WIN_ALL;
			ret = PE_DCM_HW_M23_SetDceConfig(&stParams);
			PE_DCM_HW_M23_CHECK_CODE(ret, break, \
				"[win all] PE_DCM_HW_M23_SetDceConfig() error.\n");
			/* dce lut init */
			PE_CC_PE1_M23_RdFL(pe1_dce_ia_ctrl);
			PE_CC_PE1_M23_RdFL(pe1_dce_ctrl_08);
			PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
			PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
			PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
			PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
			for(count=0;count<32;count++)
			{
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_data,	hif_dyc_wdata_y,dce_lut_data[count]);	//y data
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_data,	hif_dyc_wdata_x,dce_lut_data[count]);	//x data
				PE_CC_PE1_M23_WrFL(pe1_dce_ia_data);
			}
			PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_08,	hif_dyc_wdata_y_32nd,1023);	//y data
			PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_08,	hif_dyc_wdata_x_32nd,1023);	//x data
			PE_CC_PE1_M23_WrFL(pe1_dce_ctrl_08);
			PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
			PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x1);		//0:host access, 1:normal mode
			PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
			/* dse init */
			/* synchronization with pe1_win2_ctrl_00 win_en(0,1,01) aettings in win.c, DSE YH */
			PE_CC_PE1_M23_QWr03(pe1_dse_ctrl_00,window0_enable, 0x1,\
                                                     window1_enable, 0x1,\
                                                     window01_enable,0x1);
			/*PE_CO_PE1_M23_QWr03(pe1_dse_ctrl_00,window0_enable, 0x1,\
                                                     window1_enable, 0x1,\
                                                     window01_enable,0x1);*/
			PE_CC_PE1_M23_QWr01(pe1_dse_ctrl_01,r_dse_h_grad, 0x2);
			/*DTM lut init*/
			#if 1
			if (hw_opt.external_chip ==0) //one chip model
			{
				PE_VSD_DTM_M23_QWr01(dtm_top_ctrl_02, 		reg_master_en, 0x1);
				PE_VSD_DTM_M23_QWr02(dtm_hue_sat_ctrl_00,	reg_hue_prsv_en, 0x1,\
															reg_sat_prsv_en, 0x1);
			}
			else
			{
				PE_VSD_DTM_M23_QWr01(dtm_top_ctrl_02, reg_master_en, 0x0);
				PE_VSD_DTM_M23_QWr02(dtm_hue_sat_ctrl_00,	reg_hue_prsv_en, 0x0,\
															reg_sat_prsv_en, 0x0);
			}
			PE_VSD_DTM_M23_RdFL(dtm_llut0_ia_data);
			//PE_VSD_DTM_M23_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x0);
			PE_VSD_DTM_M23_QWr03(dtm_llut0_ia_ctrl, hif_llut0_ai,		0x1,\
													hif_llut0_enable,	0x0,\
													hif_llut0_address,	0x0);
			PE_DBG_DCM("\n update dmt lut\n");
			PE_DBG_DCM("\n   [ i]	  x,	y\n");
			for(count=0; count<32 ;count++)
			{
				//dse_lut_data is bypass curv
				PE_VSD_DTM_M23_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_y,GET_BITS(dse_lut_data[count],0,10));	//y data
				PE_VSD_DTM_M23_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_x,GET_BITS(dse_lut_data[count],0,10));//x data
				PE_VSD_DTM_M23_WrFL(dtm_llut0_ia_data);
				PE_DBG_DCM("	[%02d] %4d, %4d\n", \
					count,GET_BITS(dse_lut_data[count],0,10), GET_BITS(dse_lut_data[count],0,10));
			}
			PE_VSD_DTM_M23_QWr02(dtm_llut_ctrl_05, hif_llut_wdata_y_33rd, 0x3ff,\
												   hif_llut_wdata_x_33rd, 0x3ff);
			PE_VSD_DTM_M23_QWr03(dtm_llut0_ia_ctrl, hif_llut0_ai,		0x0,\
													hif_llut0_enable,	0x1,\
													hif_llut0_load, 	0x1);
			PE_VSD_DTM_M23_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x1);
			#endif
			/* dse lut init */
			if (!pstParams->resume_mode)	//normal init
			{
				PE_CC_PE1_M23_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,dse_lut_data[count]);	//y data
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,dse_lut_data[count]);	//x data
					PE_CC_PE1_M23_WrFL(pe1_dse_ia_data);
				}
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CC_PE1_M23_WrFL(pe1_dse_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				for (i=0;i<(PE_DCM_HW_M23_LUT_MAX-1);i++)
				{
					p_pre_dse_lut[i] = ((dse_lut_data[i]<<16)&0x3ff0000)|(dse_lut_data[i]&0x3ff);
				}
				#if 1
				PE_DBG_DCM("\n init\n");
				PE_DBG_DCM("\n   [ i]    x,    y\n");
				for (i=0;i<(PE_DCM_HW_M23_LUT_MAX-1);i++)
				{
					PE_DBG_DCM("   [%02d] %4d, %4d\n", \
						i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
				}
				#endif
			}
			else
			{
				PE_CC_PE1_M23_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,GET_BITS(p_pre_dse_lut[count],0,10));	//y data
					PE_CC_PE1_M23_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,GET_BITS(p_pre_dse_lut[count],16,10));
					PE_CC_PE1_M23_WrFL(pe1_dse_ia_data);
				}
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CC_PE1_M23_WrFL(pe1_dse_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CC_PE1_M23_WrFL(pe1_dse_ia_ctrl);
				#if 1
				PE_DBG_DCM("\n resume init\n");
				PE_DBG_DCM("\n   [ i]    x,    y\n");
				for (i=0;i<(PE_DCM_HW_M23_LUT_MAX-1);i++)
				{
					PE_DBG_DCM("   [%02d] %4d, %4d\n", \
						i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
				}
				#endif
			}
			
			/* dce config */
			PE_CC_PE1_M23_RdFL(pe1_dce_ctrl_00);
			PE_CC_PE1_M23_RdFL(pe1_dce_ctrl_01);
			PE_CC_PE1_M23_RdFL(pe1_apl_ctrl_02);
			if (hw_opt.external_chip ==0) //one chip model
			{
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
			}
			else //two chip model
			{
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x0);
			}
			PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	hist_bin_mode,			0x0);					//32bin mode
			PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	window_acquire, 		0x1);					//window acquire on
			PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	dce_domain_sel, 		0x1);	//0:ktd,1:yc
			//PE_CEO_PE1_M23_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);					//from pe1 win2
			PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	window_mode_enable, 	0x1);					//window sync
			PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	window_inout_sel,		0x0);					//window inout selection by win0,win1
			PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	histogram_mode, 		0x0);					//histogram mode, use own side's histo
			//PE_CEO_PE1_M23_Wr01(pe1_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
			//PE_CEO_PE1_M23_Wr01(pe1_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
			PE_CC_PE1_M23_Wr01(pe1_apl_ctrl_02,	apl_position,			0x0);	//0x0:PE1 input(Y/C),0x2:ocsc out(RGB)
			//PE_CC_PE1_M23_Wr01(pe1_apl_ctrl_02,	dummy,			0x3);	//dummy for apl stuck
			PE_CC_PE1_M23_WrFL(pe1_dce_ctrl_00);
			PE_CC_PE1_M23_WrFL(pe1_dce_ctrl_01);
			PE_CC_PE1_M23_WrFL(pe1_apl_ctrl_02);
			/* cen block */
			PE_CC_PE1_M23_RdFL(pe1_cen_ctrl_00);
			PE_CC_PE1_M23_Wr01(pe1_cen_ctrl_00,	vsp_sel,		0x1);	//0:hsl,1:hsv
			PE_CC_PE1_M23_WrFL(pe1_cen_ctrl_00);
			/****************/
			/* dse config */
			PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_00);
			if (hw_opt.external_chip ==0) //one chip model
			{
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x1);
			}
			else //two chip model
			{
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x0);
			}
			PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	window_mode_enable, 	0x1);	//window sync
			PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	window_inout_sel,		0x0);	//window inout selection by win0,win1
			//PE_CEO_PE1_M23_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);	//from pe1 win2
			PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	window_acquire, 		0x1);	//window acquire on
			PE_CC_PE1_M23_WrFL(pe1_dse_ctrl_00);

			if (hw_opt.external_chip ==0) //one chip model
			{
				_g_pe_dcm_hw_m23_info.is_external_chip =0;
			}
			else //two chip model
			{
				_g_pe_dcm_hw_m23_info.is_external_chip =1;
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_DCM_HW_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_dcm_hw_m23_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(DCM)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(DCM)),\
			pstParams->print_lvl,_g_dcm_hw_m23_trace,pstParams->bypass);
	}while(0);
	return ret;

}
/**
 * set dce config
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_CONF_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_HW_M23_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 is_yc,min_pos,max_pos;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		is_yc = (pstParams->domain==LX_PE_YC_DOMAIN)? 1:0;
		min_pos = pstParams->min_pos;
		max_pos = pstParams->max_pos;
		PE_DBG_DCM("[win id:%d] domain:%d, min:%d, max:%d\n",\
			pstParams->win_id,pstParams->domain,pstParams->min_pos,pstParams->max_pos);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* dce config */
				PE_CC_PE1_M23_RdFL(pe1_dce_ctrl_00);
				PE_CC_PE1_M23_RdFL(pe1_dce_ctrl_01);
				PE_CC_PE1_M23_RdFL(pe1_apl_ctrl_02);
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	hist_bin_mode,			0x0);					//32bin mode
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	window_acquire,			0x1);					//window acquire on
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	dce_domain_sel,			(is_yc==1)? 0x1:0x0);	//0:ktd,1:yc
				//PE_CEO_PE1_M23_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);					//from pe1 win2
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	window_mode_enable,		0x1);					//window sync
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	window_inout_sel,		0x0);					//window inout selection by win0,win1
				PE_CC_PE1_M23_Wr01(pe1_dce_ctrl_00,	histogram_mode,			0x0);					//histogram mode, use own side's histo
				//PE_CEO_PE1_M23_Wr01(pe1_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
				//PE_CEO_PE1_M23_Wr01(pe1_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
				PE_CC_PE1_M23_Wr01(pe1_apl_ctrl_02,	apl_position,			(is_yc==1)? 0x0:0x2);	//0x0:PE1 input(Y/C),0x2:ocsc out(RGB)
				PE_CC_PE1_M23_WrFL(pe1_dce_ctrl_00);
				PE_CC_PE1_M23_WrFL(pe1_dce_ctrl_01);
				PE_CC_PE1_M23_WrFL(pe1_apl_ctrl_02);
				/* cen block */
				PE_CC_PE1_M23_RdFL(pe1_cen_ctrl_00);
				PE_CC_PE1_M23_Wr01(pe1_cen_ctrl_00,	vsp_sel,		0x1);	//0:hsl,1:hsv
				PE_CC_PE1_M23_WrFL(pe1_cen_ctrl_00);
				/****************/
				/* dse config */
				PE_CC_PE1_M23_RdFL(pe1_dse_ctrl_00);
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x1);
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	window_mode_enable,		0x1);	//window sync
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	window_inout_sel,		0x0);	//window inout selection by win0,win1
				//PE_CEO_PE1_M23_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);	//from pe1 win2
				PE_CC_PE1_M23_Wr01(pe1_dse_ctrl_00,	window_acquire,			0x1);	//window acquire on
				PE_CC_PE1_M23_WrFL(pe1_dse_ctrl_00);
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}
/**
 * set dce lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 count=0;
	UINT32 lut_data=0;
	do {
		LX_PE_DCM_DCE_LUT_T *pp = (LX_PE_DCM_DCE_LUT_T *)pstParams;
		static LX_PE_DCM_DCE_LUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_DCM_DCE_LUT_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_DCM("duplicated DB : LX_PE_DCM_DCE_LUT_T\n");
			ret=RET_OK;
			break;
		}
		PE_DCM_HW_M23_CHECK_CODE((pstParams->size>PE_DCM_HW_M23_LUT_STEP), break, \
			" pstParams->size(%d) is over.\n", pstParams->size);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_M23_RdFL(pe1_dce_ia_ctrl);
				PE_CC_PE1_M23_RdFL(pe1_dce_ia_data);
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
				PE_DBG_DCM("\n update dce lut\n");
				PE_DBG_DCM("\n   [ i]    x,    y\n");
				for(count=0;count<(pstParams->size);count++)
				{
					lut_data = pstParams->data[count];
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(lut_data,0,10));//y data
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(lut_data,16,10));//x data
					PE_CC_PE1_M23_WrFL(pe1_dce_ia_data);
					PE_DBG_DCM("   [%02d] %4d, %4d\n", count, GET_BITS(lut_data,16,10), GET_BITS(lut_data,0,10));
				}
				/* 20160601, read register on addr0 to avoid white flash */
				PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
				PE_CC_PE1_M23_RdFL(pe1_dce_ia_data);
				
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}
/**
 * get dce lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_M23_CHECK_CODE((pstParams->size>PE_DCM_HW_M23_LUT_STEP), break, \
			" pstParams->size(%d) is over.\n", pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_M23_RdFL(pe1_dce_ia_ctrl);
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_M23_LUT_MAX-1))
					{
						PE_CE_PE1_M23_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CE_PE1_M23_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_M23_LUT_MAX-1)
					{
						PE_CE_PE1_M23_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CE_PE1_M23_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_CC_PE1_M23_RdFL(pe1_dce_ia_data);
					pstParams->data[count] = PE_CC_PE1_M23_Rd(pe1_dce_ia_data);
					#endif
				}
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
			}
			#if 0
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_M23_RdFL(pe1_dce_ia_ctrl);
				PE_CO_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_CO_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_CO_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CO_PE1_M23_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_M23_LUT_MAX-1))
					{
						PE_CO_PE1_M23_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CO_PE1_M23_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_M23_LUT_MAX-1)
					{
						PE_CO_PE1_M23_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CO_PE1_M23_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_CO_PE1_M23_RdFL(pe1_dce_ia_data);
					pstParams->data[count] = PE_CO_PE1_M23_Rd(pe1_dce_ia_data);
					#endif
				}
				PE_CO_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CO_PE1_M23_WrFL(pe1_dce_ia_ctrl);
			}
			#endif
		}
		else
		{
			PE_DBG_DCM("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}
/**
 * set drc mode
 *
 * @param   *pstParams [in] LX_PE_DCM_DRC_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 hdr_effect;
	do {
		LX_PE_DCM_DRC_MODE_T *pp = (LX_PE_DCM_DRC_MODE_T *)pstParams;
		static LX_PE_DCM_DRC_MODE_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_DCM_DRC_MODE_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_DCM("duplicated DB : LX_PE_DCM_DRC_MODE_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_DCM("[wid:%d] set: dc_md,byps,sc_cnt,pic_mode:%d,%d,%d,0x%08x\n",\
			pstParams->win_id, pstParams->dc_mode, \
			pstParams->dc_bypass, pstParams->dc_sc_cnt, pstParams->picture_mode);

		//m16p, DRC always on
		hdr_effect = 0x2; //normal ipcture mode
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_M23_RdFL(pe1_fsw_ctrl_01);
				if(pstParams->db_type == LX_PE_DRC_UI)
				{
					PE_CC_PE1_M23_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_mode,  GET_BITS(pstParams->dc_mode,0,2));
				}
				else if(pstParams->db_type == LX_PE_DRC_DC_BYPASS)
				{
					PE_CC_PE1_M23_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_bypass,GET_BITS(pstParams->dc_bypass,0,1));
				}
				PE_CC_PE1_M23_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_sc_cnt,GET_BITS(pstParams->dc_sc_cnt,0,4));
				if(pstParams->db_type == LX_PE_DRC_PIC_MODE)
				{
					PE_CC_PE1_M23_Wr01(pe1_fsw_ctrl_01,reg_hdr_effect,	GET_BITS(pstParams->picture_mode,0,2));
				}
				PE_CC_PE1_M23_WrFL(pe1_fsw_ctrl_01);
				if(pstParams->db_type == LX_PE_DRC_PIC_MODE)
				{
					ret = PE_FWI_M23_SetPicMode(pstParams->picture_mode);
					PE_DCM_HW_M23_CHECK_CODE(ret,break,"PE_FWI_M23_SetPicMode() error.\n");
					_g_pe_dcm_hw_m23_info.cur_pic_mode = pstParams->picture_mode;
				}
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get dce blending
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DRC_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_GetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_M23_RdFL(pe1_fsw_ctrl_01);
				PE_CC_PE1_M23_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_mode,  pstParams->dc_mode);
				PE_CC_PE1_M23_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_bypass,pstParams->dc_bypass);
				PE_CC_PE1_M23_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_sc_cnt,pstParams->dc_sc_cnt);
				pstParams->picture_mode = _g_pe_dcm_hw_m23_info.cur_pic_mode;
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
		}
		PE_DBG_DCM("[wid:%d] get: dc_md,byps,sc_cnt:%d,%d,%d\n",\
			pstParams->win_id, pstParams->dc_mode, \
			pstParams->dc_bypass, pstParams->dc_sc_cnt);
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * download drc db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_DownloadDrcDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_drc_data = p_phys_db->drc_lut.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_data);
		if (PE_KDRV_VER_M23)
		{
			/* header */
			sec_typ = PE_DDR_M23_SEC_DRC_LUT;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M23_DRC_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_DRC_LUT_SIZE;
			p_phys_db->drc_lut.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_lut.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_lut.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M23_DRC_LUT_ITEM_NUM * PE_DDR_M23_DRC_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			//	memcpy((UINT32 *)p_drc_data, pe_drc_lut_m16p, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}
/**
 * set drc curv
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDrcCurv(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
 			LX_PE_DCM_DRC_CUV_T *pp=(LX_PE_DCM_DRC_CUV_T *)pstParams;
			//PE_CHECK_WINID(pp->win_id);
			PE_DBG_DCM( \
			"DRC table:\n"\
			"global apl:%d,%d,%d,%d\n"\
			"local	apl:%d,%d,%d,%d,%d,%d\n"\
			"w_gain:%d, b_gain:%d\n",\
			pp->global_apl[0],pp->global_apl[1],pp->global_apl[2],pp->global_apl[3],
			pp->local_apl[0],pp->local_apl[1],pp->local_apl[2],pp->local_apl[3],pp->local_apl[4],pp->local_apl[5],
			pp->cuv_gain_w,pp->cuv_gain_b);
			PE_DBG_DCM( \
			"n1_curv0: %x,%x,%x,%x,%x,%x\n"\
			"n1_curv1: %x,%x,%x,%x,%x,%x\n"\
			"n1_curv2: %x,%x,%x,%x,%x,%x\n"\
			"n1_curv3: %x,%x,%x,%x,%x,%x\n"\
			"n1_curv4: %x,%x,%x,%x,%x,%x\n"\
			"n1_curv5: %x,%x,%x,%x,%x,%x\n",\
			pp->n1p_trans_curv[0][0],pp->n1p_trans_curv[0][1],pp->n1p_trans_curv[0][2],\
			pp->n1p_trans_curv[0][3],pp->n1p_trans_curv[0][4],pp->n1p_trans_curv[0][5],\
			pp->n1p_trans_curv[1][0],pp->n1p_trans_curv[1][1],pp->n1p_trans_curv[1][2],\
			pp->n1p_trans_curv[1][3],pp->n1p_trans_curv[1][4],pp->n1p_trans_curv[1][5],\
			pp->n1p_trans_curv[2][0],pp->n1p_trans_curv[2][1],pp->n1p_trans_curv[2][2],\
			pp->n1p_trans_curv[2][3],pp->n1p_trans_curv[2][4],pp->n1p_trans_curv[2][5],\
			pp->n1p_trans_curv[3][0],pp->n1p_trans_curv[3][1],pp->n1p_trans_curv[3][2],\
			pp->n1p_trans_curv[3][3],pp->n1p_trans_curv[3][4],pp->n1p_trans_curv[3][5],\
			pp->n1p_trans_curv[4][0],pp->n1p_trans_curv[4][1],pp->n1p_trans_curv[4][2],\
			pp->n1p_trans_curv[4][3],pp->n1p_trans_curv[4][4],pp->n1p_trans_curv[4][5],\
			pp->n1p_trans_curv[5][0],pp->n1p_trans_curv[5][1],pp->n1p_trans_curv[5][2],\
			pp->n1p_trans_curv[5][3],pp->n1p_trans_curv[5][4],pp->n1p_trans_curv[5][5]);
			ret = PE_DCM_HW_M23_DownloadDrcCurvDb((void *)pp);
			PE_DCM_HW_M23_CHECK_CODE(ret,break,"PE_DCM_HW_M23_DownloadDrcCurvDb() error.\n");
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}
/**
 * set drc param
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDrcParam(void *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) static UINT32 update_cnt=0;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
 			LX_PE_DCM_DRC_CONT1_T *pp=(LX_PE_DCM_DRC_CONT1_T *)pstParams;
			static LX_PE_DCM_DRC_CONT1_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			//PE_CHECK_DUPLICATE(LX_PE_DCM_DRC_CONT1_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DCM("duplicated DB : LX_PE_DCM_DRC_CONT_T\n");
				ret=RET_OK;
				break;
			}
			PE_DBG_DCM("DRC table:\n"\
			"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
			"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n"\
			"nApl_lut_x   :%d, %d, %d, %d\n"\
			"nApl_lut_y   :%d, %d, %d, %d\n"\
			"nTxt_lut_x   :%d, %d, %d, %d\n"\
			"nTxt_lut_y   :%d, %d, %d, %d\n"\
			"nDark_lut_x  :%d, %d, %d, %d\n"\
			"nDark_lut_y  :%d, %d, %d, %d\n"\
			"nBright_lut_x:%d, %d, %d, %d\n"\
			"nBright_lut_y:%d, %d, %d, %d\n",\
			pp->pre_norm,pp->cur_norm,pp->pre_sc,pp->cur_sc,
			pp->ui_gain_w,pp->ui_gain_b,pp->vy_mode,\
			pp->apl_lut_x[0],pp->apl_lut_x[1],pp->apl_lut_x[2],pp->apl_lut_x[3],\
			pp->apl_lut_y[0],pp->apl_lut_y[1],pp->apl_lut_y[2],pp->apl_lut_y[3],\
			pp->txt_lut_x[0],pp->txt_lut_x[1],pp->txt_lut_x[2],pp->txt_lut_x[3],\
			pp->txt_lut_y[0],pp->txt_lut_y[1],pp->txt_lut_y[2],pp->txt_lut_y[3],\
			pp->dark_lut_x[0],pp->dark_lut_x[1],pp->dark_lut_x[2],pp->dark_lut_x[3],\
			pp->dark_lut_y[0],pp->dark_lut_y[1],pp->dark_lut_y[2],pp->dark_lut_y[3],\
			pp->bright_lut_x[0],pp->bright_lut_x[1],pp->bright_lut_x[2],pp->bright_lut_x[3],\
			pp->bright_lut_y[0],pp->bright_lut_y[1],pp->bright_lut_y[2],pp->bright_lut_y[3]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(update_cnt == 0x3)
					update_cnt = 0x0;
				else
					update_cnt+=1;
				PE_SHP_M23_QWr04(shp_fsw_ctrl_00, 	reg_pre_norm, GET_BITS(pp->pre_norm,0,8),\
													reg_cur_norm, GET_BITS(pp->cur_norm,0,8),\
													reg_pre_sc  , GET_BITS(pp->pre_sc,0,8),\
													reg_drc_apb_write_cont, GET_BITS(update_cnt,0,2));
				PE_SHP_M23_QWr04(shp_fsw_ctrl_01, 	reg_cur_sc 	, GET_BITS(pp->cur_sc,0,8),\
													reg_ui_gain_w,GET_BITS(pp->ui_gain_w,0,8),\
													reg_ui_gain_b,GET_BITS(pp->ui_gain_b,0,8),\
													reg_vy_mode , GET_BITS(pp->vy_mode,0,8));
				PE_CC_PE1_M23_QWr02(pe1_drc_ctrl_07,		reg_drc_apl_lut_x0,		GET_BITS(pp->apl_lut_x[0],0,10),\
															reg_drc_apl_lut_x1,		GET_BITS(pp->apl_lut_x[1],0,10));
				PE_CC_PE1_M23_QWr02(pe1_drc_ctrl_08,		reg_drc_apl_lut_x2,		GET_BITS(pp->apl_lut_x[2],0,10),\
															reg_drc_apl_lut_x3,		GET_BITS(pp->apl_lut_x[3],0,10));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_09,		reg_drc_apl_lut_y3,		GET_BITS(pp->apl_lut_y[3],0,8),\
															reg_drc_apl_lut_y2,		GET_BITS(pp->apl_lut_y[2],0,8),\
															reg_drc_apl_lut_y1,		GET_BITS(pp->apl_lut_y[1],0,8),\
															reg_drc_apl_lut_y0,		GET_BITS(pp->apl_lut_y[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_10,		reg_drc_txt_lut_x3,		GET_BITS(pp->txt_lut_x[3],0,8),\
															reg_drc_txt_lut_x2,		GET_BITS(pp->txt_lut_x[2],0,8),\
															reg_drc_txt_lut_x1,		GET_BITS(pp->txt_lut_x[1],0,8),\
															reg_drc_txt_lut_x0,		GET_BITS(pp->txt_lut_x[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_11,		reg_drc_txt_lut_y3,		GET_BITS(pp->txt_lut_y[3],0,8),\
															reg_drc_txt_lut_y2,		GET_BITS(pp->txt_lut_y[2],0,8),\
															reg_drc_txt_lut_y1,		GET_BITS(pp->txt_lut_y[1],0,8),\
															reg_drc_txt_lut_y0,		GET_BITS(pp->txt_lut_y[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_12,		reg_drc_dark_lut_x3,	GET_BITS(pp->dark_lut_x[3],0,8),\
															reg_drc_dark_lut_x2,	GET_BITS(pp->dark_lut_x[2],0,8),\
															reg_drc_dark_lut_x1,	GET_BITS(pp->dark_lut_x[1],0,8),\
															reg_drc_dark_lut_x0,	GET_BITS(pp->dark_lut_x[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_13,		reg_drc_dark_lut_y3,	GET_BITS(pp->dark_lut_y[3],0,8),\
															reg_drc_dark_lut_y2,	GET_BITS(pp->dark_lut_y[2],0,8),\
															reg_drc_dark_lut_y1,	GET_BITS(pp->dark_lut_y[1],0,8),\
															reg_drc_dark_lut_y0,	GET_BITS(pp->dark_lut_y[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_14,		reg_drc_bright_lut_x3,	GET_BITS(pp->bright_lut_x[3],0,8),\
															reg_drc_bright_lut_x2,	GET_BITS(pp->bright_lut_x[2],0,8),\
															reg_drc_bright_lut_x1,	GET_BITS(pp->bright_lut_x[1],0,8),\
															reg_drc_bright_lut_x0,	GET_BITS(pp->bright_lut_x[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_15,		reg_drc_bright_lut_y3,	GET_BITS(pp->bright_lut_y[3],0,8),\
															reg_drc_bright_lut_y2,	GET_BITS(pp->bright_lut_y[2],0,8),\
															reg_drc_bright_lut_y1,	GET_BITS(pp->bright_lut_y[1],0,8),\
															reg_drc_bright_lut_y0,	GET_BITS(pp->bright_lut_y[0],0,8));
			}
 		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}
/**
 * set drc param
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDrcParam2(void *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) static UINT32 update_cnt=0;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
 			LX_PE_DCM_DRC_CONT2_T *pp=(LX_PE_DCM_DRC_CONT2_T *)pstParams;
			static LX_PE_DCM_DRC_CONT2_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			//PE_CHECK_DUPLICATE(LX_PE_DCM_DRC_CONT2_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DCM("duplicated DB : LX_PE_DCM_DRC_CONT_T\n");
				ret=RET_OK;
				break;
			}
			PE_DBG_DCM("DRC table:\n"\
			"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
			"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n"\
			"nApl_lut_x   :%d, %d, %d, %d\n"\
			"nApl_lut_y   :%d, %d, %d, %d\n"\
			"nTxt_lut_x   :%d, %d, %d, %d\n"\
			"nTxt_lut_y   :%d, %d, %d, %d\n"\
			"nDark_lut_x  :%d, %d, %d, %d\n"\
			"nDark_lut_y  :%d, %d, %d, %d\n"\
			"nBright_lut_x:%d, %d, %d, %d\n"\
			"nBright_lut_y:%d, %d, %d, %d\n",\
			pp->pre_norm,pp->cur_norm,pp->pre_sc,pp->cur_sc,
			pp->ui_gain_w,pp->ui_gain_b,pp->vy_mode,\
			pp->apl_lut_x[0],pp->apl_lut_x[1],pp->apl_lut_x[2],pp->apl_lut_x[3],\
			pp->apl_lut_y[0],pp->apl_lut_y[1],pp->apl_lut_y[2],pp->apl_lut_y[3],\
			pp->txt_lut_x[0],pp->txt_lut_x[1],pp->txt_lut_x[2],pp->txt_lut_x[3],\
			pp->txt_lut_y[0],pp->txt_lut_y[1],pp->txt_lut_y[2],pp->txt_lut_y[3],\
			pp->dark_lut_x[0],pp->dark_lut_x[1],pp->dark_lut_x[2],pp->dark_lut_x[3],\
			pp->dark_lut_y[0],pp->dark_lut_y[1],pp->dark_lut_y[2],pp->dark_lut_y[3],\
			pp->bright_lut_x[0],pp->bright_lut_x[1],pp->bright_lut_x[2],pp->bright_lut_x[3],\
			pp->bright_lut_y[0],pp->bright_lut_y[1],pp->bright_lut_y[2],pp->bright_lut_y[3]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(update_cnt == 0x3)
					update_cnt = 0x0;
				else
					update_cnt+=1;
				PE_SHP_M23_QWr04(shp_fsw_ctrl_00, 	reg_pre_norm, GET_BITS(pp->pre_norm,0,8),\
													reg_cur_norm, GET_BITS(pp->cur_norm,0,8),\
													reg_pre_sc  , GET_BITS(pp->pre_sc,0,8),\
													reg_drc_apb_write_cont, GET_BITS(update_cnt,0,2));
				PE_SHP_M23_QWr04(shp_fsw_ctrl_01, 	reg_cur_sc 	, GET_BITS(pp->cur_sc,0,8),\
													reg_ui_gain_w,GET_BITS(pp->ui_gain_w,0,8),\
													reg_ui_gain_b,GET_BITS(pp->ui_gain_b,0,8),\
													reg_vy_mode , GET_BITS(pp->vy_mode,0,8));
				PE_CC_PE1_M23_QWr02(pe1_drc_ctrl_07,		reg_drc_apl_lut_x0,		GET_BITS(pp->apl_lut_x[0],0,10),\
															reg_drc_apl_lut_x1,		GET_BITS(pp->apl_lut_x[1],0,10));
				PE_CC_PE1_M23_QWr02(pe1_drc_ctrl_08,		reg_drc_apl_lut_x2,		GET_BITS(pp->apl_lut_x[2],0,10),\
															reg_drc_apl_lut_x3,		GET_BITS(pp->apl_lut_x[3],0,10));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_09,		reg_drc_apl_lut_y3,		GET_BITS(pp->apl_lut_y[3],0,8),\
															reg_drc_apl_lut_y2,		GET_BITS(pp->apl_lut_y[2],0,8),\
															reg_drc_apl_lut_y1,		GET_BITS(pp->apl_lut_y[1],0,8),\
															reg_drc_apl_lut_y0,		GET_BITS(pp->apl_lut_y[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_10,		reg_drc_txt_lut_x3,		GET_BITS(pp->txt_lut_x[3],0,8),\
															reg_drc_txt_lut_x2,		GET_BITS(pp->txt_lut_x[2],0,8),\
															reg_drc_txt_lut_x1,		GET_BITS(pp->txt_lut_x[1],0,8),\
															reg_drc_txt_lut_x0,		GET_BITS(pp->txt_lut_x[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_11,		reg_drc_txt_lut_y3,		GET_BITS(pp->txt_lut_y[3],0,8),\
															reg_drc_txt_lut_y2,		GET_BITS(pp->txt_lut_y[2],0,8),\
															reg_drc_txt_lut_y1,		GET_BITS(pp->txt_lut_y[1],0,8),\
															reg_drc_txt_lut_y0,		GET_BITS(pp->txt_lut_y[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_12,		reg_drc_dark_lut_x3,	GET_BITS(pp->dark_lut_x[3],0,8),\
															reg_drc_dark_lut_x2,	GET_BITS(pp->dark_lut_x[2],0,8),\
															reg_drc_dark_lut_x1,	GET_BITS(pp->dark_lut_x[1],0,8),\
															reg_drc_dark_lut_x0,	GET_BITS(pp->dark_lut_x[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_13,		reg_drc_dark_lut_y3,	GET_BITS(pp->dark_lut_y[3],0,8),\
															reg_drc_dark_lut_y2,	GET_BITS(pp->dark_lut_y[2],0,8),\
															reg_drc_dark_lut_y1,	GET_BITS(pp->dark_lut_y[1],0,8),\
															reg_drc_dark_lut_y0,	GET_BITS(pp->dark_lut_y[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_14,		reg_drc_bright_lut_x3,	GET_BITS(pp->bright_lut_x[3],0,8),\
															reg_drc_bright_lut_x2,	GET_BITS(pp->bright_lut_x[2],0,8),\
															reg_drc_bright_lut_x1,	GET_BITS(pp->bright_lut_x[1],0,8),\
															reg_drc_bright_lut_x0,	GET_BITS(pp->bright_lut_x[0],0,8));
				PE_CC_PE1_M23_QWr04(pe1_drc_ctrl_15,		reg_drc_bright_lut_y3,	GET_BITS(pp->bright_lut_y[3],0,8),\
															reg_drc_bright_lut_y2,	GET_BITS(pp->bright_lut_y[2],0,8),\
															reg_drc_bright_lut_y1,	GET_BITS(pp->bright_lut_y[1],0,8),\
															reg_drc_bright_lut_y0,	GET_BITS(pp->bright_lut_y[0],0,8));
			}
 		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

/**
 * set drc param
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_GetDrcParam(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
 			LX_PE_DCM_DRC_CONT_T *pp=(LX_PE_DCM_DRC_CONT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_M23_QRd03(shp_fsw_ctrl_00, 	reg_pre_norm, pp->pre_norm,\
													reg_cur_norm, pp->cur_norm,\
													reg_pre_sc  , pp->pre_sc);
				PE_SHP_M23_QRd04(shp_fsw_ctrl_01, 	reg_cur_sc 	, pp->cur_sc,\
													reg_ui_gain_w,pp->ui_gain_w,\
													reg_ui_gain_b,pp->ui_gain_b,\
													reg_vy_mode , pp->vy_mode);
			}
			PE_DBG_DCM( \
			"DRC table:\n"\
			"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
			"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n",\
			pp->pre_norm,pp->cur_norm,pp->pre_sc,pp->cur_sc,
			pp->ui_gain_w,pp->ui_gain_b,pp->vy_mode);
 		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}


/**
 * download drc curv
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_DownloadDrcCurvDbInit(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_drc_cuv = p_phys_db->drc_cuv.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_cuv);
		if (PE_KDRV_VER_M23)
		{
			/* header */
			sec_typ = PE_DDR_M23_SEC_DRC_CURV;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M23_DRC_CURV_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DRC_M23_FW_LUT_SIZE;
			p_phys_db->drc_cuv.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_cuv.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_cuv.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_cuv.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M23_DRC_CURV_ITEM_NUM * PE_DRC_M23_FW_LUT_SIZE * sizeof(SINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			memcpy((UINT32 *)p_drc_cuv, pe_drc_lut_init, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x, size:%d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->top_h.sec_size[sec_typ]);
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

/**
 * download drc curv
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_DownloadDrcCurvDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 size, sec_typ;
	UINT32 base;
	UINT32 *pp = NULL;
	__attribute__((unused)) static UINT32 update_cnt=0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->drc_cuv.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DRC_CURV;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = PE_DDR_M23_DRC_CURV_ITEM_NUM*PE_DDR_M23_DRC_CURV_SIZE*sizeof(UINT32);
			pp = (UINT32 *)pstParams;
			memcpy((void *)p_db_data, pstParams, size);
			wmb();
			if(update_cnt == 0x3)
				update_cnt = 0x0;
			else
				update_cnt+=1;
			PE_SHP_M23_QWr01(shp_fsw_ctrl_00, reg_drc_write_cont,GET_BITS(update_cnt,0,2));
			PE_DBG_DCM("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], update_cnt);
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}


/**
 * set dse ctrl webos5.0
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL3_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	//UINT32 color_out_gain;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_DCM_DSE_CTRL3_T *pp = (LX_PE_DCM_DSE_CTRL3_T *)pstParams;
			static LX_PE_DCM_DSE_CTRL3_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			//PE_CHECK_DUPLICATE(LX_PE_DCM_DSE_CTRL3_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DCM("duplicated DB : LX_PE_DCM_DSE_CTRL3_T\n");
				ret=RET_OK;
				break;
			}
			PE_DBG_DCM("[wid:%d] set: chroma_gain_en:%d\n"\
				"dce_chr_gain1:%d,dce_chr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
				"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
				pp->win_id,	pp->chroma_gain_en, \
				pp->chroma_chr_gain1,pp->chroma_chr_gain2,pp->chroma_chr_alpha1,pp->chroma_chr_alpha2,\
				pp->dtm_hue_gain, pp->dtm_sat_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CC_PE1_M23_QWr03(pe1_dce_chr_gain,		chroma_gain_enable, GET_BITS(pp->chroma_gain_en,0,1),\
															dce_cb_gain1,		GET_BITS(pp->chroma_chr_gain1,0,10),\
															dce_cb_gain2,		GET_BITS(pp->chroma_chr_gain2,0,10));
				PE_CC_PE1_M23_QWr02(pe1_dce_chr_alpha,		dce_chr_alpha1,		GET_BITS(pp->chroma_chr_alpha1,0,10),\
															dce_chr_alpha2,		GET_BITS(pp->chroma_chr_alpha2,0,10));
				#if 1
				PE_VSD_DTM_M23_QWr02(dtm_hue_sat_ctrl_00,		reg_sat_prsv_ratio,	GET_BITS(pp->dtm_sat_gain,0,8),\
															reg_hue_prsv_ratio, GET_BITS(pp->dtm_hue_gain,0,8));
				#endif
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

/**
 * get dse ctrl
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_GetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_DCM_DSE_CTRL3_T *pp=(LX_PE_DCM_DSE_CTRL3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				
				PE_CC_PE1_M23_QRd03(pe1_dce_chr_gain,		chroma_gain_enable, pp->chroma_gain_en,\
															dce_cb_gain1,		pp->chroma_chr_gain1,\
															dce_cb_gain2,		pp->chroma_chr_gain2);
				PE_CC_PE1_M23_QRd02(pe1_dce_chr_alpha,		dce_chr_alpha1,	pp->chroma_chr_alpha1,\
															dce_chr_alpha2,		pp->chroma_chr_alpha2);
				PE_VSD_DTM_M23_QRd02(dtm_hue_sat_ctrl_00,		reg_sat_prsv_ratio,	pp->dtm_sat_gain,\
															reg_hue_prsv_ratio, pp->dtm_hue_gain);
			}
			PE_DBG_DCM("[wid:%d] get: chroma_gain_en:%d\n"\
				"dce_chr_gain1:%d,dce_chr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
				"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
				pp->win_id,	pp->chroma_gain_en, \
				pp->chroma_chr_gain1,pp->chroma_chr_gain2,pp->chroma_chr_alpha1,pp->chroma_chr_alpha2,\
				pp->dtm_hue_gain, pp->dtm_sat_gain);
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

/**
 * set dce lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDtmLut(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
#define PE_DCM_DTM_LUT_SIZE 33
	UINT32 count=0;
	UINT32 lut_data=0;
	static UINT32 preDtmLut[PE_DCM_DTM_LUT_SIZE]={0,};
	//int i;
	do {
		LX_PE_DCM_DTM_LUT_T *pp = (LX_PE_DCM_DTM_LUT_T *)pstParams;
		static LX_PE_DCM_DTM_LUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		if(memcmp(preDtmLut, pp->data, pp->size*sizeof(UINT32))==0)
		{
			pp->win_id =0xff;
		}
		//PE_CHECK_DUPLICATE(LX_PE_DCM_DTM_LUT_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_DCM("duplicated DB : LX_PE_DCM_DTM_LUT_T\n");
			ret=RET_OK;
			break;
		}
		PE_DCM_HW_M23_CHECK_CODE((pp->size>PE_DCM_DTM_LUT_SIZE), break, \
			" pstParams->size(%d) is over.\n", pp->size);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_DTM_M23_RdFL(dtm_llut0_ia_data);
				//PE_VSD_DTM_M23_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x0);
				PE_VSD_DTM_M23_QWr03(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x1,\
														hif_llut0_enable,	0x0,\
													 	hif_llut0_address,	0x0);
				PE_DBG_DCM("\n update dmt lut\n");
				PE_DBG_DCM("\n   [ i]    x,    y\n");
				for(count=0; count<32 ;count++)
				{
					lut_data = pp->data[count];
					PE_VSD_DTM_M23_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_y,GET_BITS(lut_data,0,10));//y data
					PE_VSD_DTM_M23_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_x,GET_BITS(lut_data,16,10));//x data
					PE_VSD_DTM_M23_WrFL(dtm_llut0_ia_data);
					PE_DBG_DCM("   [%02d] %4d, %4d\n", \
						count, GET_BITS(lut_data,16,10), GET_BITS(lut_data,0,10));
				}
				lut_data = pp->data[32];
				PE_VSD_DTM_M23_QWr02(dtm_llut_ctrl_05, hif_llut_wdata_y_33rd, GET_BITS(lut_data,0,10),\
													   hif_llut_wdata_x_33rd, GET_BITS(lut_data,16,10));
				PE_VSD_DTM_M23_QWr03(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x0,\
														hif_llut0_enable,	0x1,\
														hif_llut0_load,		0x1);

				memcpy(preDtmLut,pp->data, pp->size*sizeof(UINT32));
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get dce lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_GetDtmLut(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	do {
		LX_PE_DCM_DTM_LUT_T *pp = (LX_PE_DCM_DTM_LUT_T *)pstParams;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_DCM_HW_M23_CHECK_CODE((pp->size>PE_DCM_HW_M23_LUT_STEP), break, \
			" pstParams->size(%d) is over.\n", pp->size);
		win_id = PE_GET_CHECKED_WINID(pp->win_id);
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				
				PE_VSD_DTM_M23_QWr02(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x1,\
														hif_llut0_enable,	0x0);
				for(count=0;count<(pp->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_M23_LUT_MAX-1))
					{
						PE_CE_PE1_M23_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CE_PE1_M23_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_M23_LUT_MAX-1)
					{
						PE_CE_PE1_M23_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CE_PE1_M23_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_VSD_DTM_M23_RdFL(dtm_llut0_ia_data);
					pp->data[count] = PE_VSD_DTM_M23_Rd(dtm_llut0_ia_data);
					#endif
				}
				PE_VSD_DTM_M23_QWr02(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x0,\
														hif_llut0_enable,	0x1);
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set Dcm lut accel mode for DGMS (prevent recurrence)
 *
 * @param   *onoff [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetAccelDceLut(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 dyn_bypass[16] = {0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960};
	int count=0;
	int print_co=0;
	do{
		PE_DBG_DCM("set dce lut accel mode\n");
		if(PE_KDRV_VER_M23)
		{
			while(1)
			{
				PE_CC_PE1_M23_RdFL(pe1_dce_ia_ctrl);
				PE_CC_PE1_M23_RdFL(pe1_dce_ia_data);
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<16;count++)
				{
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(dyn_bypass[count],0,10));	//y data
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(dyn_bypass[count],0,10));//x data
					PE_CC_PE1_M23_WrFL(pe1_dce_ia_data);
				}
				/* 20160601, read register on addr0 to avoid white flash */
				//PE_CEO_PE1_M23_WrFL(pe1_dce_ia_ctrl);
				//PE_CEO_PE1_M23_RdFL(pe1_dce_ia_data);
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
				if(print_co == 1024)
				{
					printk("keep setting DCE\n");
					print_co =0;
				}
				print_co++;
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

/**
 * set dse ctrl webos5.0
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL4_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDseCtrl2(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_DCM_DSE_CTRL5_T *pp = (LX_PE_DCM_DSE_CTRL5_T *)pstParams;
			static LX_PE_DCM_DSE_CTRL5_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			//PE_CHECK_DUPLICATE(LX_PE_DCM_DSE_CTRL5_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DCM("duplicated DB : LX_PE_DCM_DSE_CTRL3_T\n");
				ret=RET_OK;
				break;
			}
			PE_DBG_DCM("[wid:%d] set: chroma_gain_en:%d\n"\
			"chroma_cb_gain1:%d,chroma_cb_gain2:%d,chroma_cr_gain1:%d,chroma_cr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
			"luma_x:%d,%d,%d,%d luma_y:%d,%d,%d,%d\n"\
			"sat_x :%d,%d,%d,%d sat_y:%d,%d,%d,%d\n"\
			"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
			pp->win_id,pp->chroma_gain_en, \
			pp->chroma_cb_gain1,pp->chroma_cb_gain2,\
			pp->chroma_cr_gain1,pp->chroma_cr_gain2,\
			pp->chroma_alpha1,pp->chroma_alpha2,\
			pp->luma_gain_x[0],pp->luma_gain_x[1],pp->luma_gain_x[2],pp->luma_gain_x[3],\
			pp->luma_gain_y[0],pp->luma_gain_y[1],pp->luma_gain_y[2],pp->luma_gain_y[3],\
			pp->sat_gain_x[0],pp->sat_gain_x[1],pp->sat_gain_x[2],pp->sat_gain_x[3],\
			pp->sat_gain_y[0],pp->sat_gain_y[1],pp->sat_gain_y[2],pp->sat_gain_y[3],\
			pp->dtm_hue_gain,pp->dtm_sat_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(_g_pe_dcm_hw_m23_info.is_external_chip ==0x0)//single chip
				{
					//pe1_dce_chr_gain
					PE_CCO_VERI_M23_QWr03(sys_veri_9,		chroma_gain_enable, GET_BITS(pp->chroma_gain_en,0,1),\
																dce_cb_gain1,		GET_BITS(pp->chroma_cb_gain1,0,10),\
																dce_cb_gain2,		GET_BITS(pp->chroma_cb_gain2,0,10));
				}
				else
				{
					//pe1_dce_chr_gain
					PE_CCO_VERI_M23_QWr03(sys_veri_9,		chroma_gain_enable, 0x0,\
																dce_cb_gain1,		GET_BITS(pp->chroma_cb_gain1,0,10),\
																dce_cb_gain2,		GET_BITS(pp->chroma_cb_gain2,0,10));
				}
				
				PE_CC_PE1_M23_QWr02(pe1_dce_chr_gain2,	dce_cr_gain1,		GET_BITS(pp->chroma_cr_gain1,0,10),\
															dce_cr_gain2,		GET_BITS(pp->chroma_cr_gain2,0,10));
				#if 1
				/* do not setting dce_chr_alpha1, dce_chr_alpha2 bc f/w overwrite */
				PE_VSD_DTM_M23_QWr04(dtm_lut_lum_sat_ctrl_00,	reg_lut_lum_x3,	GET_BITS(pp->luma_gain_x[3],0,8),\
																reg_lut_lum_x2,	GET_BITS(pp->luma_gain_x[2],0,8),\
																reg_lut_lum_x1,	GET_BITS(pp->luma_gain_x[1],0,8),\
																reg_lut_lum_x0,	GET_BITS(pp->luma_gain_x[0],0,8));
				PE_VSD_DTM_M23_QWr04(dtm_lut_lum_sat_ctrl_01,	reg_lut_lum_y3,	GET_BITS(pp->luma_gain_y[3],0,8),\
																reg_lut_lum_y2,	GET_BITS(pp->luma_gain_y[2],0,8),\
																reg_lut_lum_y1,	GET_BITS(pp->luma_gain_y[1],0,8),\
																reg_lut_lum_y0,	GET_BITS(pp->luma_gain_y[0],0,8));
				PE_VSD_DTM_M23_QWr04(dtm_lut_lum_sat_ctrl_02,	reg_lut_sat_x3,	GET_BITS(pp->sat_gain_x[3],0,8),\
																reg_lut_sat_x2,	GET_BITS(pp->sat_gain_x[2],0,8),\
																reg_lut_sat_x1,	GET_BITS(pp->sat_gain_x[1],0,8),\
																reg_lut_sat_x0,	GET_BITS(pp->sat_gain_x[0],0,8));
				PE_VSD_DTM_M23_QWr04(dtm_lut_lum_sat_ctrl_03,	reg_lut_sat_y3,	GET_BITS(pp->sat_gain_y[3],0,8),\
																reg_lut_sat_y2,	GET_BITS(pp->sat_gain_y[2],0,8),\
																reg_lut_sat_y1,	GET_BITS(pp->sat_gain_y[1],0,8),\
																reg_lut_sat_y0,	GET_BITS(pp->sat_gain_y[0],0,8));
				PE_VSD_DTM_M23_QWr02(dtm_hue_sat_ctrl_00,	reg_sat_prsv_ratio,	GET_BITS(pp->dtm_sat_gain,0,8),\
															reg_hue_prsv_ratio, GET_BITS(pp->dtm_hue_gain,0,8));
				#endif
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

/**
 * get dse ctrl
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL4_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_GetDseCtrl2(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_DCM_DSE_CTRL4_T *pp=(LX_PE_DCM_DSE_CTRL4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				
				PE_CC_PE1_M23_QRd03(pe1_dce_chr_gain,		chroma_gain_enable, pp->chroma_gain_en,\
															dce_cb_gain1,		pp->chroma_cb_gain1,\
															dce_cb_gain2,		pp->chroma_cb_gain2);
				PE_CC_PE1_M23_QRd02(pe1_dce_chr_gain2,	dce_cr_gain1,		pp->chroma_cr_gain1,\
															dce_cr_gain2,		pp->chroma_cr_gain2);
				PE_CC_PE1_M23_QRd02(pe1_dce_chr_alpha,	dce_chr_alpha1,		pp->chroma_alpha1,\
															dce_chr_alpha2,		pp->chroma_alpha2);
				PE_VSD_DTM_M23_QRd02(dtm_hue_sat_ctrl_00,	reg_sat_prsv_ratio,	pp->dtm_sat_gain,\
															reg_hue_prsv_ratio, pp->dtm_hue_gain);
			}
			PE_DBG_DCM("[wid:%d] get: chroma_gain_en:%d\n"\
				"chroma_cb_gain1:%d,chroma_cb_gain2:%d,chroma_cr_gain1:%d,chroma_cr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
				"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
				pp->win_id,\
				pp->chroma_gain_en, \
				pp->chroma_cb_gain1,pp->chroma_cb_gain2,\
				pp->chroma_cr_gain1,pp->chroma_cr_gain2,\
				pp->chroma_alpha1,pp->chroma_alpha2,\
				pp->dtm_hue_gain,pp->dtm_sat_gain);
		}
		else
		{
			PE_DBG_DCM("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}
/**
 * set dce lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_M23_SetDceLut2(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 count=0;
	do {
		LX_PE_DCM_DCE_LUT1_T *pp = (LX_PE_DCM_DCE_LUT1_T *)pstParams;
		static LX_PE_DCM_DCE_LUT1_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_DCM_DCE_LUT1_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_DCM("duplicated DB : LX_PE_DCM_DCE_LUT1_T\n");
			ret=RET_OK;
			break;
		}
		if(PE_KDRV_VER_M23)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(_g_pe_dcm_hw_m23_info.is_external_chip ==0x0)//single chip
				{
					PE_CC_PE1_M23_RdFL(pe1_dce_ia_ctrl);
					PE_CC_PE1_M23_RdFL(pe1_dce_ia_data);
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl, hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl, hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl, hif_dyc_address,	0x0);	//address
					PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
				}
				PE_DBG_DCM("\n update dce lut\n");
				PE_DBG_DCM("\n   [ i]	  x,	y\n");
				for(count=0;count<32;count++)
				{
					if(_g_pe_dcm_hw_m23_info.is_external_chip ==0x0)//single chip
					{
						PE_CC_PE1_M23_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(pp->lumalut_y[count],0,10));//y data
						PE_CC_PE1_M23_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(pp->lumalut_x[count],0,10));//x data
						PE_CC_PE1_M23_WrFL(pe1_dce_ia_data);
					}
					PE_DBG_DCM("   [%02d] %4d, %4d\n", count, \
						GET_BITS(pp->lumalut_x[count],0,10), GET_BITS(pp->lumalut_y[count],0,10));
				}
				if(_g_pe_dcm_hw_m23_info.is_external_chip ==0x0)//single chip
				{
					PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);
					PE_CC_PE1_M23_RdFL(pe1_dce_ia_data);
					
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl, hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
					PE_CC_PE1_M23_Wr01(pe1_dce_ia_ctrl, hif_dce_load,		0x1);	//0:clear, 1:enable
					PE_CC_PE1_M23_WrFL(pe1_dce_ia_ctrl);

					PE_CCO_VERI_M23_QWr02(sys_veri_20,chroma_face_alpha_lut1_x0, GET_BITS(pp->chroma_face_alpha_lut1_x[0],0,8),\
														  chroma_face_alpha_lut1_x1, GET_BITS(pp->chroma_face_alpha_lut1_x[1],0,8));
					PE_CCO_VERI_M23_QWr02(sys_veri_21,chroma_face_alpha_lut1_x2, GET_BITS(pp->chroma_face_alpha_lut1_x[2],0,8),\
														  chroma_face_alpha_lut1_x3, GET_BITS(pp->chroma_face_alpha_lut1_x[3],0,8));
					PE_CCO_VERI_M23_QWr02(sys_veri_22,chroma_face_alpha_lut1_y0, GET_BITS(pp->chroma_face_alpha_lut1_y[0],0,10),\
														  chroma_face_alpha_lut1_y1, GET_BITS(pp->chroma_face_alpha_lut1_y[1],0,10));
					PE_CCO_VERI_M23_QWr02(sys_veri_23,chroma_face_alpha_lut1_y2, GET_BITS(pp->chroma_face_alpha_lut1_y[2],0,10),\
														  chroma_face_alpha_lut1_y3, GET_BITS(pp->chroma_face_alpha_lut1_y[3],0,10));
					PE_CCO_VERI_M23_QWr02(sys_veri_24,chroma_face_alpha_lut2_x0, GET_BITS(pp->chroma_face_alpha_lut2_x[0],0,8),\
														  chroma_face_alpha_lut2_x1, GET_BITS(pp->chroma_face_alpha_lut2_x[1],0,8));
					PE_CCO_VERI_M23_QWr02(sys_veri_25,chroma_face_alpha_lut2_x2, GET_BITS(pp->chroma_face_alpha_lut2_x[2],0,8),\
														  chroma_face_alpha_lut2_x3, GET_BITS(pp->chroma_face_alpha_lut2_x[3],0,8));
					PE_CCO_VERI_M23_QWr02(sys_veri_26,chroma_face_alpha_lut2_y0, GET_BITS(pp->chroma_face_alpha_lut2_y[0],0,10),\
														  chroma_face_alpha_lut2_y1, GET_BITS(pp->chroma_face_alpha_lut2_y[1],0,10));
					PE_CCO_VERI_M23_QWr02(sys_veri_27,chroma_face_alpha_lut2_y2, GET_BITS(pp->chroma_face_alpha_lut2_y[2],0,10),\
														  chroma_face_alpha_lut2_y3, GET_BITS(pp->chroma_face_alpha_lut2_y[3],0,10));
				}
				
				PE_DBG_DCM("[wid:%d] set: \n"\
					"lut1_x: %d, %d, %d, %d\n" \
					"lut1_y: %d, %d, %d, %d\n" \
					"lut2_x: %d, %d, %d, %d\n" \
					"lut2_y: %d, %d, %d, %d\n", \
					pp->win_id,\
					pp->chroma_face_alpha_lut1_x[0],pp->chroma_face_alpha_lut1_x[1],\
					pp->chroma_face_alpha_lut1_x[2],pp->chroma_face_alpha_lut1_x[3],\
					pp->chroma_face_alpha_lut1_y[0],pp->chroma_face_alpha_lut1_y[1],\
					pp->chroma_face_alpha_lut1_y[2],pp->chroma_face_alpha_lut1_y[3],\
					pp->chroma_face_alpha_lut2_x[0],pp->chroma_face_alpha_lut2_x[1],\
					pp->chroma_face_alpha_lut2_x[2],pp->chroma_face_alpha_lut2_x[3],\
					pp->chroma_face_alpha_lut2_y[0],pp->chroma_face_alpha_lut2_y[1],\
					pp->chroma_face_alpha_lut2_y[2],pp->chroma_face_alpha_lut2_y[3]);
			}
		}
		else
		{
			PE_DBG_DCM("nothing to do\n"); ret = RET_OK;
		}
	} while (0);
#endif /*PE_HW_M23_BRINGUP*/
	return ret;

}

