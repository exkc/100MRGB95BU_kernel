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

/** @file pe_dcm_hw_e60.c
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

#include "pe_hw_e60.h"
#include "pe_reg_e60.h"
#include "pe_fwi_e60.h"
#include "pe_cmn_hw_e60.h"
#include "pe_dcm_hw_e60.h"
#include "pe_drc_def.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_HW_E60_DCE_LUT_NUM	2
#define PE_DCM_HW_E60_DCE_CNT_NUM	0xfff

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_HW_E60_ERROR	printk

#define PE_DCM_HW_E60_DBG_PRINT(fmt,args...)	\
	if(_g_dcm_hw_e60_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
		
#define PE_DCM_HW_E60_CHECK_CODE(_checker,_action,fmt,args...) \
	{if(_checker){PE_DCM_HW_E60_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern const UINT32 g_pe_cmn_hw_e60_crc_table[256];

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_DCM_HW_E60_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
static int PE_DCM_HW_E60F20_DownloadDYN(void *pstParams);
static int PE_DCM_HW_E60F20_DownloadAPL(void *pstParams);
static int PE_DCM_HW_E60F20_DownloadGain(void *pstParams);
static int PE_DCM_HW_E60F20_DownloadTable(void *pstParams);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_dcm_hw_e60_trace=0x0;	//default should be off.
static PE_DCM_HW_E60_SETTINGS_T _g_pe_dcm_hw_e60_info;

static UINT32 _g_dcm_hw_e60_pre_dse_lut[(PE_DCM_HW_E60_LUT_MAX-1)];	///<previous dse lut


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
int PE_DCM_HW_E60_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 count = 0;
	int i;
	LX_PE_DCM_DCE_CONF_T stParams;
	UINT32 *p_pre_dse_lut = _g_dcm_hw_e60_pre_dse_lut;
	UINT32 dce_lut_data[32] = {\
		   0,  64, 122, 181, 239, 298, 356, 415, 473, \
		 532, 590, 649, 707, 766, 824, 882, 940,1023, \
		1023,1023,1023,1023,1023,1023,1023,1023,1023, \
		1023,1023,1023,1023,1023};
	UINT32 dse_lut_data[32] = {\
		   0,  64, 128, 192, 256, 320, 384, 448, 512, \
		 576, 640, 704, 768, 832, 896, 960,1023,1023, \
		1023,1023,1023,1023,1023,1023,1023,1023,1023, \
		1023,1023,1023,1023,1023};
	PE_REG_E60_HW_OPT_T hw_opt = PE_REG_E60_GetDispOpt();
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			PE_DCM_HW_E60_DBG_PRINT("init histo info.\n");
			memset0(_g_pe_dcm_hw_e60_info);
			_g_pe_dcm_hw_e60_info.cur_blur_gain = 0xf;
			_g_pe_dcm_hw_e60_info.pre_blur_gain = 0xf;
			/* dce init */
			PE_CC_PE1_E60_Wr(pe1_dce_hist_ia_ctrl,0x00008000);	//0:read mode, 1:normal mode
			PE_CC_PE1_E60_WrFL(pe1_dce_hist_ia_ctrl);
			/* set blur_v_gain 0xf temporally */
			//PE_CEO_PE1_E60_QWr01(pe1_dce_ctrl_01,blur_v_gain,0xf);	//0x0:blur V ~ 0xf:original V
			PE_DCM_HW_E60_DBG_PRINT("init dce config\n");
			/* synchronization with pe1_win2_ctrl_00 win_en(0,1,01) aettings in win.c */
			PE_CC_PE1_E60_QWr03(pe1_dce_ctrl_00,window0_enable, 0x1,\
                                                   window1_enable, 0x1,\
                                                   window01_enable,0x1);
			stParams.domain = LX_PE_YC_DOMAIN;
			stParams.min_pos = 26;
			stParams.max_pos = 220;
			stParams.win_id = LX_PE_WIN_ALL;
			ret = PE_DCM_HW_E60_SetDceConfig(&stParams);
			PE_DCM_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d][win all] PE_DCM_HW_E60_SetDceConfig() error.\n", __F__, __L__);
			/* dce lut init */
			PE_CC_PE1_E60_RdFL(pe1_dce_ia_ctrl);
			PE_CC_PE1_E60_RdFL(pe1_dce_ctrl_08);
			PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
			PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
			PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
			PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
			for(count=0;count<32;count++)
			{
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,	hif_dyc_wdata_y,dce_lut_data[count]);	//y data
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,	hif_dyc_wdata_x,dce_lut_data[count]);	//x data
				PE_CC_PE1_E60_WrFL(pe1_dce_ia_data);
			}
			PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_08,	hif_dyc_wdata_y_32nd,1023);	//y data
			PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_08,	hif_dyc_wdata_x_32nd,1023);	//x data
			PE_CC_PE1_E60_WrFL(pe1_dce_ctrl_08);
			PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
			PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x1);		//0:host access, 1:normal mode
			PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
			/* dse init */
			/* synchronization with pe1_win2_ctrl_00 win_en(0,1,01) aettings in win.c, DSE YH */
			PE_CC_PE1_E60_QWr03(pe1_dse_ctrl_00,window0_enable, 0x1,\
                                                     window1_enable, 0x1,\
                                                     window01_enable,0x1);
			/*PE_CO_PE1_E60_QWr03(pe1_dse_ctrl_00,window0_enable, 0x1,\
                                                     window1_enable, 0x1,\
                                                     window01_enable,0x1);*/
			PE_CC_PE1_E60_QWr01(pe1_dse_ctrl_01,r_dse_h_grad, 0x2);
			PE_VSD_DTM_E60_QWr02(dtm_hue_sat_ctrl,	reg_hue_prsv_en, 0x1,\
													reg_sat_prsv_en, 0x1);
			/*DTM lut init*/
			PE_VSD_DTM_E60_RdFL(dtm_llut0_ia_data);
			//PE_VSD_DTM_E60_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x0);
			PE_VSD_DTM_E60_QWr03(dtm_llut0_ia_ctrl, hif_llut0_ai,		0x1,\
													hif_llut0_enable,	0x0,\
													hif_llut0_address,	0x0);
			PE_DCM_HW_E60_DBG_PRINT("\n update dmt lut\n");
			PE_DCM_HW_E60_DBG_PRINT("\n   [ i]	  x,	y\n");
			for(count=0; count<32 ;count++)
			{
				//dse_lut_data is bypass curv
				PE_VSD_DTM_E60_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_y,GET_BITS(dse_lut_data[count],0,10));	//y data
				PE_VSD_DTM_E60_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_x,GET_BITS(dse_lut_data[count],0,10));//x data
				PE_VSD_DTM_E60_WrFL(dtm_llut0_ia_data);
				PE_DCM_HW_E60_DBG_PRINT("	[%02d] %4d, %4d\n", \
					count,GET_BITS(dse_lut_data[count],0,10), GET_BITS(dse_lut_data[count],0,10));
			}
			PE_VSD_DTM_E60_QWr02(dtm_llut_ctrl_05, hif_llut_wdata_y_33rd, 0x3ff,\
												   hif_llut_wdata_x_33rd, 0x3ff);
			PE_VSD_DTM_E60_QWr03(dtm_llut0_ia_ctrl, hif_llut0_ai,		0x0,\
													hif_llut0_enable,	0x1,\
													hif_llut0_load, 	0x1);
			PE_VSD_DTM_E60_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x1);

			/* dse lut init */
			if (!pstParams->resume_mode)	//normal init
			{
				PE_CC_PE1_E60_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_E60_RdFL(pe1_dse_ctrl_02);
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_E60_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CC_PE1_E60_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,dse_lut_data[count]);	//y data
					PE_CC_PE1_E60_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,dse_lut_data[count]);	//x data
					PE_CC_PE1_E60_WrFL(pe1_dse_ia_data);
				}
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CC_PE1_E60_WrFL(pe1_dse_ctrl_02);
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CC_PE1_E60_WrFL(pe1_dse_ia_ctrl);
				for (i=0;i<(PE_DCM_HW_E60_LUT_MAX-1);i++)
				{
					p_pre_dse_lut[i] = ((dse_lut_data[i]<<16)&0x3ff0000)|(dse_lut_data[i]&0x3ff);
				}
				if(_g_dcm_hw_e60_trace)
				{
					PE_DCM_HW_E60_DBG_PRINT("\n init\n");
					PE_DCM_HW_E60_DBG_PRINT("\n   [ i]    x,    y\n");
					for (i=0;i<(PE_DCM_HW_E60_LUT_MAX-1);i++)
					{
						PE_DCM_HW_E60_DBG_PRINT("   [%02d] %4d, %4d\n", \
							i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
					}
				}
			}
			else
			{
				PE_CC_PE1_E60_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_E60_RdFL(pe1_dse_ctrl_02);
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_E60_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CC_PE1_E60_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,GET_BITS(p_pre_dse_lut[count],0,10));	//y data
					PE_CC_PE1_E60_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,GET_BITS(p_pre_dse_lut[count],16,10));
					PE_CC_PE1_E60_WrFL(pe1_dse_ia_data);
				}
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CC_PE1_E60_WrFL(pe1_dse_ctrl_02);
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CC_PE1_E60_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CC_PE1_E60_WrFL(pe1_dse_ia_ctrl);
				if(_g_dcm_hw_e60_trace)
				{
					PE_DCM_HW_E60_DBG_PRINT("\n resume init\n");
					PE_DCM_HW_E60_DBG_PRINT("\n   [ i]    x,    y\n");
					for (i=0;i<(PE_DCM_HW_E60_LUT_MAX-1);i++)
					{
						PE_DCM_HW_E60_DBG_PRINT("   [%02d] %4d, %4d\n", \
							i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
					}
				}
			}
			
			/* dce config */
			PE_CC_PE1_E60_RdFL(pe1_dce_ctrl_00);
			PE_CC_PE1_E60_RdFL(pe1_dce_ctrl_01);
			PE_CC_PE1_E60_RdFL(pe1_apl_ctrl_02);
			if (hw_opt.external_chip ==0) //one chip model
			{
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
			}
			else //two chip model
			{
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x0);
			}
			PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	hist_bin_mode,			0x0);					//32bin mode
			PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	window_acquire, 		0x1);					//window acquire on
			PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	dce_domain_sel, 		0x1);	//0:ktd,1:yc
			//PE_CEO_PE1_E60_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);					//from pe1 win2
			PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	window_mode_enable, 	0x1);					//window sync
			PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	window_inout_sel,		0x0);					//window inout selection by win0,win1
			PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	histogram_mode, 		0x0);					//histogram mode, use own side's histo
			//PE_CEO_PE1_E60_Wr01(pe1_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
			//PE_CEO_PE1_E60_Wr01(pe1_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
			PE_CC_PE1_E60_Wr01(pe1_apl_ctrl_02,	apl_position,			0x0);	//0x0:PE1 input(Y/C),0x2:ocsc out(RGB)
			PE_CC_PE1_E60_Wr01(pe1_apl_ctrl_02,	dummy,			0x3);	//dummy for apl stuck
			PE_CC_PE1_E60_WrFL(pe1_dce_ctrl_00);
			PE_CC_PE1_E60_WrFL(pe1_dce_ctrl_01);
			PE_CC_PE1_E60_WrFL(pe1_apl_ctrl_02);
			/* cen block */
			PE_CC_PE1_E60_RdFL(pe1_cen_ctrl_00);
			PE_CC_PE1_E60_Wr01(pe1_cen_ctrl_00,	vsp_sel,		0x1);	//0:hsl,1:hsv
			PE_CC_PE1_E60_WrFL(pe1_cen_ctrl_00);
			/****************/
			/* dse config */
			PE_CC_PE1_E60_RdFL(pe1_dse_ctrl_00);
			if (hw_opt.external_chip ==0) //one chip model
			{
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x1);
			}
			else //two chip model
			{
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x0);
			}
			PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	window_mode_enable, 	0x1);	//window sync
			PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	window_inout_sel,		0x0);	//window inout selection by win0,win1
			//PE_CEO_PE1_E60_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);	//from pe1 win2
			PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	window_acquire, 		0x1);	//window acquire on
			PE_CC_PE1_E60_WrFL(pe1_dse_ctrl_00);

			if (hw_opt.external_chip ==0) //one chip model
			{
				_g_pe_dcm_hw_e60_info.is_external_chip =0;
			}
			else //two chip model
			{
				_g_pe_dcm_hw_e60_info.is_external_chip =1;
			}

			/*temporally obc disable*/
			//PE_VSD_OBC_O_E60_QWr01(psp_ctrl02,	reg_psp_en,	0x0);
			//PE_VSD_OBC_F_E60_QWr01(psp_ctrl02,	reg_psp_en,	0x0);
			#if 1	/* E60F20_APB */
			do {
				UINT32 lut_data;

				if (pstParams->resume_mode == 1)	break;//if qsm,skip

				/* addr */
				/* 200902, bc DC library, change purpose of dc lut */ 
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_ctrl_s.uaddr32,0xF03425B4);//PE1_APL_STAT_00 - RO not used
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[0].uaddr32,0xF0355370);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[1].uaddr32,0xF0355374);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[2].uaddr32,0xF0355378);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[3].uaddr32,0xF035537C);
				for (i=4; i<32; i++)
				{
					PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[i].uaddr32,0xF03425B4);//PE1_APL_STAT_00 - RO not used
				}
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_ctrl_e.uaddr32,0xF03425B4);//PE1_APL_STAT_00 - RO not used
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ctrl_08.uaddr32,0xF0342740);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_chr_gain.uaddr32,0xF0342754);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_chr_gain2.uaddr32,0xF034275C);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_20.uaddr32,0xF0342350);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_21.uaddr32,0xF0342354);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_22.uaddr32,0xF0342358);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_23.uaddr32,0xF034235C);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_24.uaddr32,0xF0342360);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_25.uaddr32,0xF0342364);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_26.uaddr32,0xF0342368);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_27.uaddr32,0xF034236C);
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut_ctrl_05.uaddr32,0xF0175C84);
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut0_ia_ctrl_s.uaddr32,0xF0175C88);
				for (i=0; i<32; i++)
				{
					PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut0_ia_data[i].uaddr32,0xF0175C8C);
				}
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut0_ia_ctrl_e.uaddr32,0xF0175C88);
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut_ctrl_00.uaddr32,0xF0175C70);
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_hue_sat_ctrl.uaddr32,0xF0175CE0);
				PE_CHPI_APB0_E60F20_QWr(fsw0.pe1_fsw_ctrl_01.uaddr32,0xF0342524);
				PE_CHPI_APB0_E60F20_QWr(fsw0.shp_fsw_ctrl_00.uaddr32,0xF0342300);
				PE_CHPI_APB0_E60F20_QWr(fsw0.shp_fsw_ctrl_01.uaddr32,0xF0342304);
				PE_CHPI_APB0_E60F20_QWr(fsw0.shp_fsw_ctrl_02.uaddr32,0xF0342308);
				PE_CHPI_APB0_E60F20_QWr(fsw0.vsd0_veri_vsp_0.uaddr32,0xF0175800);
				PE_CHPI_APB0_E60F20_QWr(fsw0.vsd0_veri_vsp_1.uaddr32,0xF0175804);
				PE_CHPI_APB0_E60F20_QWr(fsw0.vsd1_veri_vsp_0.uaddr32,0xF017BF00);
				PE_CHPI_APB0_E60F20_QWr(fsw0.vsd1_veri_vsp_1.uaddr32,0xF017BF04);

				/* init */
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_ctrl_s.udata32,0x0);//PE1_APL_STAT_00 - RO not used
				
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[0].udata32,0x020A0000);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[1].udata32,0x0);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[2].udata32,0x00021760);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[3].udata32,0x0);
				for (i=4; i<32; i++)
				{
					PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[i].udata32,0x0);//PE1_APL_STAT_00 - RO not used
				}
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_ctrl_e.udata32,0x0);//PE1_APL_STAT_00 - RO not used
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ctrl_08.udata32,0x03FF03FF);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_chr_gain.udata32,0x02000200);
				PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_chr_gain2.udata32,0x02000200);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_20.udata32,0x00200000);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_21.udata32,0x00C00064);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_22.udata32,0x00800200);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_23.udata32,0x00000040);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_24.udata32,0x00200000);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_25.udata32,0x00C00064);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_26.udata32,0x00800200);
				PE_CHPI_APB0_E60F20_QWr(dce0.cco1_veri_27.udata32,0x00000040);
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut_ctrl_05.udata32,0x03FF03FF);
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut0_ia_ctrl_s.udata32,0x00001000);
				for (i=0; i<32; i++)
				{
					PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut0_ia_data[i].udata32,p_pre_dse_lut[i]);
				}
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut0_ia_ctrl_e.udata32,0x00008100);
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_llut_ctrl_00.udata32,0x00000001);
				PE_CHPI_APB0_E60F20_QWr(dtm0.dtm_hue_sat_ctrl.udata32,0xFF000011);
				PE_CHPI_APB0_E60F20_QWr(fsw0.pe1_fsw_ctrl_01.udata32,0x00000000);
				PE_CHPI_APB0_E60F20_QWr(fsw0.shp_fsw_ctrl_00.udata32,0x00000000);
				PE_CHPI_APB0_E60F20_QWr(fsw0.shp_fsw_ctrl_01.udata32,0x00000000);
				PE_CHPI_APB0_E60F20_QWr(fsw0.shp_fsw_ctrl_02.udata32,0x00000000);
				PE_CHPI_APB0_E60F20_QWr(fsw0.vsd0_veri_vsp_0.udata32,0x02000000);
				PE_CHPI_APB0_E60F20_QWr(fsw0.vsd0_veri_vsp_1.udata32,0x02008000);
				PE_CHPI_APB0_E60F20_QWr(fsw0.vsd1_veri_vsp_0.udata32,0x02000000);
				PE_CHPI_APB0_E60F20_QWr(fsw0.vsd1_veri_vsp_1.udata32,0x02008000);

				/* header */
				PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DCE0);
				PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DTM0);
				PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_FSW0);

				PE_PRINT_NOTI("[APB][DCM]done(resume:%d)\n",pstParams->resume_mode);
				PE_INF_HW_E60_BACKUP_CHPI0("[APB][DCM]done(resume:%d)",pstParams->resume_mode);
			} while(0);
			#endif
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_E60_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(DCM)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_dcm_hw_e60_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(DCM)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if(PE_KDRV_VER_E60)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(DCM)))
				{
					PE_DCM_HW_E60_DBG_PRINT("dynamic_contrast_en : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_CC_PE1_E60_QWr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x0);
					}
				}
				else
				{
					PE_DCM_HW_E60_DBG_PRINT("dynamic_contrast_en : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_CC_PE1_E60_QWr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);
					}
				}
			}
			else
			{
				PE_DCM_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
			}
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
static int PE_DCM_HW_E60_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 is_yc,min_pos,max_pos;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		is_yc = (pstParams->domain==LX_PE_YC_DOMAIN)? 1:0;
		min_pos = pstParams->min_pos;
		max_pos = pstParams->max_pos;
		PE_DCM_HW_E60_DBG_PRINT("[win id:%d] domain:%d, min:%d, max:%d\n",\
			pstParams->win_id,pstParams->domain,pstParams->min_pos,pstParams->max_pos);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* dce config */
				PE_CC_PE1_E60_RdFL(pe1_dce_ctrl_00);
				PE_CC_PE1_E60_RdFL(pe1_dce_ctrl_01);
				PE_CC_PE1_E60_RdFL(pe1_apl_ctrl_02);
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	hist_bin_mode,			0x0);					//32bin mode
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	window_acquire,			0x1);					//window acquire on
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	dce_domain_sel,			(is_yc==1)? 0x1:0x0);	//0:ktd,1:yc
				//PE_CEO_PE1_E60_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);					//from pe1 win2
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	window_mode_enable,		0x1);					//window sync
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	window_inout_sel,		0x0);					//window inout selection by win0,win1
				PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_00,	histogram_mode,			0x0);					//histogram mode, use own side's histo
				//PE_CEO_PE1_E60_Wr01(pe1_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
				//PE_CEO_PE1_E60_Wr01(pe1_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
				PE_CC_PE1_E60_Wr01(pe1_apl_ctrl_02,	apl_position,			(is_yc==1)? 0x0:0x2);	//0x0:PE1 input(Y/C),0x2:ocsc out(RGB)
				PE_CC_PE1_E60_WrFL(pe1_dce_ctrl_00);
				PE_CC_PE1_E60_WrFL(pe1_dce_ctrl_01);
				PE_CC_PE1_E60_WrFL(pe1_apl_ctrl_02);
				/* cen block */
				PE_CC_PE1_E60_RdFL(pe1_cen_ctrl_00);
				PE_CC_PE1_E60_Wr01(pe1_cen_ctrl_00,	vsp_sel,		0x1);	//0:hsl,1:hsv
				PE_CC_PE1_E60_WrFL(pe1_cen_ctrl_00);
				/****************/
				/* dse config */
				PE_CC_PE1_E60_RdFL(pe1_dse_ctrl_00);
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x1);
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	window_mode_enable,		0x1);	//window sync
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	window_inout_sel,		0x0);	//window inout selection by win0,win1
				//PE_CEO_PE1_E60_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);	//from pe1 win2
				PE_CC_PE1_E60_Wr01(pe1_dse_ctrl_00,	window_acquire,			0x1);	//window acquire on
				PE_CC_PE1_E60_WrFL(pe1_dse_ctrl_00);
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	#ifdef PE_DCM_HW_E60_SET_DCE_LUT_ON_SYNC
	UINT32 cur_dce_lut_num;
	PE_DCM_HW_E60_SETTINGS_T *pInfo=&_g_pe_dcm_hw_e60_info;
	#else
	UINT32 count=0;
	UINT32 lut_data=0;
	//int i;
	#endif
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DCE_LUT_T *pp = (LX_PE_DCM_DCE_LUT_T *)pstParams;
		static LX_PE_DCM_DCE_LUT_T prev[LX_PE_WIN_NUM];
		static UINT32 chk = 0x0;
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_DCM_DCE_LUT_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DCM_HW_E60_DBG_PRINT("duplicated DB : LX_PE_DCM_DCE_LUT_T\n");
			ret=RET_OK;
			break;
		}
		PE_DCM_HW_E60_CHECK_CODE((pstParams->size>PE_DCM_HW_E60_LUT_STEP), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pstParams->size);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_DCM_HW_E60_SET_DCE_LUT_ON_SYNC
				if (pstParams->size<PE_DCM_HW_E60_LUT_STEP)	break;
				cur_dce_lut_num = (!pInfo->dce_lut_num)? 1:0;
				if (cur_dce_lut_num==1)
					memcpy(pInfo->dce_lut1, pstParams->data, sizeof(UINT32)*PE_DCM_HW_E60_LUT_STEP);
				else
					memcpy(pInfo->dce_lut0, pstParams->data, sizeof(UINT32)*PE_DCM_HW_E60_LUT_STEP);
				pInfo->dce_lut_num = cur_dce_lut_num;
				if (pInfo->dce_lut_cnt<PE_DCM_HW_E60_DCE_CNT_NUM)
					pInfo->dce_lut_cnt++;
				else
					pInfo->dce_lut_cnt=0;
				#else
				PE_CC_PE1_E60_RdFL(pe1_dce_ia_ctrl);
				PE_CC_PE1_E60_RdFL(pe1_dce_ia_data);
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
				PE_DCM_HW_E60_DBG_PRINT("\n update dce lut\n");
				PE_DCM_HW_E60_DBG_PRINT("\n   [ i]    x,    y\n");
				for(count=0;count<(pstParams->size);count++)
				{
					lut_data = pstParams->data[count];
					#if 0
					if (count<(PE_DCM_HW_E60_LUT_MAX-1))
					{
						PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(lut_data,0,10));	//y data
						PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(lut_data,16,10));//x data
						PE_CC_PE1_E60_WrFL(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_E60_LUT_MAX-1)
					{
						PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_08,hif_dyc_wdata_y_32nd,GET_BITS(lut_data,0,10));//y data
						PE_CC_PE1_E60_Wr01(pe1_dce_ctrl_08,hif_dyc_wdata_x_32nd,GET_BITS(lut_data,16,10));//x data
						PE_CC_PE1_E60_WrFL(pe1_dce_ctrl_08);
					}
					#else
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(lut_data,0,10));//y data
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(lut_data,16,10));//x data
					PE_CC_PE1_E60_WrFL(pe1_dce_ia_data);
					PE_DCM_HW_E60_DBG_PRINT("   [%02d] %4d, %4d\n", count, GET_BITS(lut_data,16,10), GET_BITS(lut_data,0,10));
					#endif
				}
				/* 20160601, read register on addr0 to avoid white flash */
				PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
				PE_CC_PE1_E60_RdFL(pe1_dce_ia_data);
				
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
				#endif
				#if 1	/* E60F20_APB */
				do {
					for(count=0;count<(pstParams->size);count++)
					{
						lut_data = pstParams->data[count];
						PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_ia_data[count].hif_dyc_wdata_y,GET_BITS(lut_data,0,10));//y data
						PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_ia_data[count].hif_dyc_wdata_x,GET_BITS(lut_data,16,10));//x data
						PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_ia_data[count].udata32);
					}
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DCE0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_E60_CHECK_CODE((pstParams->size>PE_DCM_HW_E60_LUT_STEP), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_E60_RdFL(pe1_dce_ia_ctrl);
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_E60_LUT_MAX-1))
					{
						PE_CE_PE1_E60_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CE_PE1_E60_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_E60_LUT_MAX-1)
					{
						PE_CE_PE1_E60_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CE_PE1_E60_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_CC_PE1_E60_RdFL(pe1_dce_ia_data);
					pstParams->data[count] = PE_CC_PE1_E60_Rd(pe1_dce_ia_data);
					#endif
				}
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
			}
			#if 0
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_E60_RdFL(pe1_dce_ia_ctrl);
				PE_CO_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_CO_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_CO_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CO_PE1_E60_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_E60_LUT_MAX-1))
					{
						PE_CO_PE1_E60_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CO_PE1_E60_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_E60_LUT_MAX-1)
					{
						PE_CO_PE1_E60_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CO_PE1_E60_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_CO_PE1_E60_RdFL(pe1_dce_ia_data);
					pstParams->data[count] = PE_CO_PE1_E60_Rd(pe1_dce_ia_data);
					#endif
				}
				PE_CO_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CO_PE1_E60_WrFL(pe1_dce_ia_ctrl);
			}
			#endif
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 hdr_effect;
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DRC_MODE_T *pp = (LX_PE_DCM_DRC_MODE_T *)pstParams;
		static LX_PE_DCM_DRC_MODE_T prev[LX_PE_WIN_NUM];
		static UINT32 chk = 0x0;
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_DCM_DRC_MODE_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DCM_HW_E60_DBG_PRINT("duplicated DB : LX_PE_DCM_DRC_MODE_T\n");
			ret=RET_OK;
			break;
		}
		PE_DCM_HW_E60_DBG_PRINT("[wid:%d] set: dc_md,byps,sc_cnt,pic_mode:%d,%d,%d,0x%08x\n",\
			pstParams->win_id, pstParams->dc_mode, \
			pstParams->dc_bypass, pstParams->dc_sc_cnt, pstParams->picture_mode);

		//m16p, DRC always on
		hdr_effect = 0x2; //normal ipcture mode
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_E60_RdFL(pe1_fsw_ctrl_01);
				PE_CC_PE1_E60_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_mode,  GET_BITS(pstParams->dc_mode,0,2));
				PE_CC_PE1_E60_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_bypass,GET_BITS(pstParams->dc_bypass,0,1));
				PE_CC_PE1_E60_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_sc_cnt,GET_BITS(pstParams->dc_sc_cnt,0,4));
				PE_CC_PE1_E60_Wr01(pe1_fsw_ctrl_01,reg_hdr_effect,       GET_BITS(hdr_effect,0,2));
				PE_CC_PE1_E60_WrFL(pe1_fsw_ctrl_01);

				ret = PE_FWI_E60_SetPicMode(pstParams->picture_mode);
				PE_DCM_HW_E60_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_E60_SetPicMode() error.\n", __F__, __L__);
				_g_pe_dcm_hw_e60_info.cur_pic_mode = pstParams->picture_mode;
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(fsw0.pe1_fsw_ctrl_01.reg_drc_dc_mode,GET_BITS(pstParams->dc_mode,0,2));
					PE_CHPI_APB0_E60F20_Wr(fsw0.pe1_fsw_ctrl_01.reg_drc_dc_bypass,GET_BITS(pstParams->dc_bypass,0,1));
					PE_CHPI_APB0_E60F20_Wr(fsw0.pe1_fsw_ctrl_01.reg_drc_dc_sc_cnt,GET_BITS(pstParams->dc_sc_cnt,0,4));
					PE_CHPI_APB0_E60F20_Wr(fsw0.pe1_fsw_ctrl_01.reg_hdr_effect,GET_BITS(hdr_effect,0,2));
					PE_CHPI_APB0_E60F20_WrFL(fsw0.pe1_fsw_ctrl_01.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_FSW0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_GetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_E60_RdFL(pe1_fsw_ctrl_01);
				PE_CC_PE1_E60_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_mode,  pstParams->dc_mode);
				PE_CC_PE1_E60_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_bypass,pstParams->dc_bypass);
				PE_CC_PE1_E60_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_sc_cnt,pstParams->dc_sc_cnt);
				pstParams->picture_mode = _g_pe_dcm_hw_e60_info.cur_pic_mode;
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
		}
		PE_DCM_HW_E60_DBG_PRINT("[wid:%d] get: dc_md,byps,sc_cnt:%d,%d,%d\n",\
			pstParams->win_id, pstParams->dc_mode, \
			pstParams->dc_bypass, pstParams->dc_sc_cnt);
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_DownloadDrcDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_E60_T *p_shdw_db = gPE_DDR_DB_E60.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_E60_T *p_phys_db = gPE_DDR_DB_E60.phys.data;
	volatile UINT32 *p_drc_data = p_phys_db->drc_lut.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_data);
		if (PE_KDRV_VER_E60)
		{
			/* header */
			sec_typ = PE_DDR_E60_SEC_DRC_LUT;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_E60_DRC_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_E60_DRC_LUT_SIZE;
			p_phys_db->drc_lut.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_lut.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_lut.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_E60_DRC_LUT_ITEM_NUM * PE_DDR_E60_DRC_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_E60_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_E60_HEADER_T);
			/* wr ddr */
			//	memcpy((UINT32 *)p_drc_data, pe_drc_lut_m16p, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_E60_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDrcCurv(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
 			LX_PE_DCM_DRC_CUV_T *pp=(LX_PE_DCM_DRC_CUV_T *)pstParams;
			//PE_CHECK_WINID(pp->win_id);
			if (_g_dcm_hw_e60_trace)
			{
				PE_DCM_HW_E60_DBG_PRINT( \
				"DRC table:\n"\
				"global apl:%d,%d,%d,%d\n"\
				"local	apl:%d,%d,%d,%d,%d,%d\n"\
				"w_gain:%d, b_gain:%d\n",\
				pp->global_apl[0],pp->global_apl[1],pp->global_apl[2],pp->global_apl[3],
				pp->local_apl[0],pp->local_apl[1],pp->local_apl[2],pp->local_apl[3],pp->local_apl[4],pp->local_apl[5],
				pp->cuv_gain_w,pp->cuv_gain_b);
				PE_DCM_HW_E60_DBG_PRINT( \
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
			}
			ret = PE_DCM_HW_E60_DownloadDrcCurvDb((void *)pp);
			PE_DCM_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DCM_HW_E60_DownloadDrcCurvDb() error.\n",__F__,__L__);
			ret = PE_DCM_HW_E60F20_DownloadDrcCurvDb((void *)pp);
			PE_DCM_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DCM_HW_E60F20_DownloadDrcCurvDb() error.\n",__F__,__L__);
 		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDrcParam(void *pstParams)
{
	int ret = RET_OK;
	static UINT32 update_cnt=0;
	#ifndef PE_HW_E60_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
 			LX_PE_DCM_DRC_CONT_T *pp=(LX_PE_DCM_DRC_CONT_T *)pstParams;
			static LX_PE_DCM_DRC_CONT_T prev[LX_PE_WIN_NUM];
			static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_DCM_DRC_CONT_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DCM_HW_E60_DBG_PRINT("duplicated DB : LX_PE_DCM_DRC_CONT_T\n");
				ret=RET_OK;
				break;
			}
			if (_g_dcm_hw_e60_trace)
			{
				PE_DCM_HW_E60_DBG_PRINT( \
				"DRC table:\n"\
				"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
				"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n",\
				pp->pre_norm,pp->cur_norm,pp->pre_sc,pp->cur_sc,
				pp->ui_gain_w,pp->ui_gain_b,pp->vy_mode);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(update_cnt == 0x3)
					update_cnt = 0x0;
				else
					update_cnt+=1;
				PE_SHP_E60_QWr04(shp_fsw_ctrl_00, 	reg_pre_norm, GET_BITS(pp->pre_norm,0,8),\
													reg_cur_norm, GET_BITS(pp->cur_norm,0,8),\
													reg_pre_sc  , GET_BITS(pp->pre_sc,0,8),\
													drc_apb_write_cont, GET_BITS(update_cnt,0,2));
				PE_SHP_E60_QWr04(shp_fsw_ctrl_01, 	reg_cur_sc 	, GET_BITS(pp->cur_sc,0,8),\
													reg_ui_gain_w,GET_BITS(pp->ui_gain_w,0,8),\
													reg_ui_gain_b,GET_BITS(pp->ui_gain_b,0,8),\
													reg_vy_mode , GET_BITS(pp->vy_mode,0,8));
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(fsw0.shp_fsw_ctrl_00.reg_pre_norm,GET_BITS(pp->pre_norm,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.shp_fsw_ctrl_00.reg_cur_norm,GET_BITS(pp->cur_norm,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.shp_fsw_ctrl_00.reg_pre_sc,GET_BITS(pp->pre_sc,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.shp_fsw_ctrl_00.drc_apb_write_cont,GET_BITS(update_cnt,0,2));
					PE_CHPI_APB0_E60F20_Wr(fsw0.shp_fsw_ctrl_01.reg_cur_sc,GET_BITS(pp->cur_sc,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.shp_fsw_ctrl_01.reg_ui_gain_w,GET_BITS(pp->ui_gain_w,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.shp_fsw_ctrl_01.reg_ui_gain_b,GET_BITS(pp->ui_gain_b,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.shp_fsw_ctrl_01.reg_vy_mode,GET_BITS(pp->vy_mode,0,8));
					PE_CHPI_APB0_E60F20_WrFL(fsw0.shp_fsw_ctrl_00.udata32);
					PE_CHPI_APB0_E60F20_WrFL(fsw0.shp_fsw_ctrl_01.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_FSW0);
				} while(0);
				#endif
			}
 		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_GetDrcParam(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
 			LX_PE_DCM_DRC_CONT_T *pp=(LX_PE_DCM_DRC_CONT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_E60_QRd03(shp_fsw_ctrl_00, 	reg_pre_norm, pp->pre_norm,\
													reg_cur_norm, pp->cur_norm,\
													reg_pre_sc  , pp->pre_sc);
				PE_SHP_E60_QRd04(shp_fsw_ctrl_01, 	reg_cur_sc 	, pp->cur_sc,\
													reg_ui_gain_w,pp->ui_gain_w,\
													reg_ui_gain_b,pp->ui_gain_b,\
													reg_vy_mode , pp->vy_mode);
			}
			if (_g_dcm_hw_e60_trace)
			{
				PE_DCM_HW_E60_DBG_PRINT( \
				"DRC table:\n"\
				"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
				"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n",\
				pp->pre_norm,pp->cur_norm,pp->pre_sc,pp->cur_sc,
				pp->ui_gain_w,pp->ui_gain_b,pp->vy_mode);
			}
 		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_DownloadDrcCurvDbInit(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_E60_T *p_shdw_db = gPE_DDR_DB_E60.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_E60_T *p_phys_db = gPE_DDR_DB_E60.phys.data;
	volatile UINT32 *p_drc_cuv = p_phys_db->drc_cuv.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_cuv);
		if (PE_KDRV_VER_E60)
		{
			/* header */
			sec_typ = PE_DDR_E60_SEC_DRC_CURV;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_E60_DRC_CURV_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DRC_E60_FW_LUT_SIZE;
			p_phys_db->drc_cuv.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_cuv.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_cuv.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_cuv.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_E60_DRC_CURV_ITEM_NUM * PE_DRC_E60_FW_LUT_SIZE * sizeof(SINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_E60_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_E60_HEADER_T);
			/* wr ddr */
			memcpy((UINT32 *)p_drc_cuv, pe_drc_lut_init, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x, size:%d)\n", \
				PE_DDR_REG_E60_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->top_h.sec_size[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_DownloadDrcCurvDb(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size, sec_typ;
	UINT32 base;
	UINT32 *pp = NULL;
	static UINT32 update_cnt=0;
	PE_DDR_DB_SHDW_REG_E60_T *p_shdw_db = gPE_DDR_DB_E60.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_E60_T *p_phys_db = gPE_DDR_DB_E60.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->drc_cuv.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_E60)
		{
			sec_typ = PE_DDR_E60_SEC_DRC_CURV;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = PE_DDR_E60_DRC_CURV_ITEM_NUM*PE_DDR_E60_DRC_CURV_SIZE*sizeof(UINT32);
			pp = (UINT32 *)pstParams;
			memcpy((void *)p_db_data, pstParams, size);
			wmb();
			if(update_cnt == 0x3)
				update_cnt = 0x0;
			else
				update_cnt+=1;
			PE_SHP_E60_QWr01(shp_fsw_ctrl_00, drc_write_cont,GET_BITS(update_cnt,0,2));
			PE_DCM_HW_E60_DBG_PRINT("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_E60_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], update_cnt);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	//UINT32 color_out_gain;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			LX_PE_DCM_DSE_CTRL3_T *pp = (LX_PE_DCM_DSE_CTRL3_T *)pstParams;
			static LX_PE_DCM_DSE_CTRL3_T prev[LX_PE_WIN_NUM];
			static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_DCM_DSE_CTRL3_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DCM_HW_E60_DBG_PRINT("duplicated DB : LX_PE_DCM_DSE_CTRL3_T\n");
				ret=RET_OK;
				break;
			}
			PE_DCM_HW_E60_DBG_PRINT("[wid:%d] set: chroma_gain_en:%d\n"\
				"dce_chr_gain1:%d,dce_chr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
				"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
				pp->win_id,	pp->chroma_gain_en, \
				pp->chroma_chr_gain1,pp->chroma_chr_gain2,pp->chroma_chr_alpha1,pp->chroma_chr_alpha2,\
				pp->dtm_hue_gain, pp->dtm_sat_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CC_PE1_E60_QWr03(pe1_dce_chr_gain,		chroma_gain_enable, GET_BITS(pp->chroma_gain_en,0,1),\
															dce_cb_gain1,		GET_BITS(pp->chroma_chr_gain1,0,10),\
															dce_cb_gain2,		GET_BITS(pp->chroma_chr_gain2,0,10));
				PE_CC_PE1_E60_QWr02(pe1_dce_chr_alpha,		dce_chr_alpha1,		GET_BITS(pp->chroma_chr_alpha1,0,10),\
															dce_chr_alpha2,		GET_BITS(pp->chroma_chr_alpha2,0,10));
				PE_VSD_DTM_E60_QWr02(dtm_hue_sat_ctrl,		reg_sat_prsv_ratio,	GET_BITS(pp->dtm_sat_gain,0,8),\
															reg_hue_prsv_ratio, GET_BITS(pp->dtm_hue_gain,0,8));
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_gain.chroma_gain_enable,GET_BITS(pp->chroma_gain_en,0,1));
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_gain.dce_cb_gain1,GET_BITS(pp->chroma_chr_gain1,0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_gain.dce_cb_gain2,GET_BITS(pp->chroma_chr_gain2,0,10));
					//PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_alpha.dce_chr_alpha1,GET_BITS(pp->chroma_chr_alpha1,0,10));
					//PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_alpha.dce_chr_alpha2,GET_BITS(pp->chroma_chr_alpha2,0,10));
					PE_CHPI_APB0_E60F20_Wr(dtm0.dtm_hue_sat_ctrl.reg_sat_prsv_ratio,GET_BITS(pp->dtm_sat_gain,0,8));
					PE_CHPI_APB0_E60F20_Wr(dtm0.dtm_hue_sat_ctrl.reg_hue_prsv_ratio,GET_BITS(pp->dtm_hue_gain,0,8));
					PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_chr_gain.udata32);
					//PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_chr_alpha.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dtm0.dtm_hue_sat_ctrl.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DCE0);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DTM0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_GetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			LX_PE_DCM_DSE_CTRL3_T *pp=(LX_PE_DCM_DSE_CTRL3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				
				PE_CC_PE1_E60_QRd03(pe1_dce_chr_gain,		chroma_gain_enable, pp->chroma_gain_en,\
															dce_cb_gain1,		pp->chroma_chr_gain1,\
															dce_cb_gain2,		pp->chroma_chr_gain2);
				PE_CC_PE1_E60_QRd02(pe1_dce_chr_alpha,		dce_chr_alpha1,	pp->chroma_chr_alpha1,\
															dce_chr_alpha2,		pp->chroma_chr_alpha2);
				PE_VSD_DTM_E60_QRd02(dtm_hue_sat_ctrl,		reg_sat_prsv_ratio,	pp->dtm_sat_gain,\
															reg_hue_prsv_ratio, pp->dtm_hue_gain);
			}
			PE_DCM_HW_E60_DBG_PRINT("[wid:%d] get: chroma_gain_en:%d\n"\
				"dce_chr_gain1:%d,dce_chr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
				"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
				pp->win_id,	pp->chroma_gain_en, \
				pp->chroma_chr_gain1,pp->chroma_chr_gain2,pp->chroma_chr_alpha1,pp->chroma_chr_alpha2,\
				pp->dtm_hue_gain, pp->dtm_sat_gain);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;

}

/**
 * set dce lut on sync
 *
 * @param   *pCfg [in] PE_TSK_E60_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_E60_SetDceLutOnSync(PE_TSK_E60_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	#ifdef PE_DCM_HW_E60_SET_DCE_LUT_ON_SYNC
	static UINT32 pre_lut_cnt = 0xffff;
	PE_DCM_HW_E60_SETTINGS_T *pInfo=&_g_pe_dcm_hw_e60_info;
	UINT32 *pLut = NULL;
	UINT32 count;
	do {
		if (pInfo->dce_lut_off==1)							break;
		if (pInfo->dce_lut_cnt>PE_DCM_HW_E60_DCE_CNT_NUM)	break;
		if (pInfo->dce_lut_num>PE_DCM_HW_E60_DCE_LUT_NUM)	break;
		if (pre_lut_cnt==pInfo->dce_lut_cnt)	break;
		if (pInfo->dce_lut_num==1)	pLut = pInfo->dce_lut1;
		else						pLut = pInfo->dce_lut0;
		PE_CC_PE1_E60_RdFL(pe1_dce_ia_ctrl);
		//PE_CEO_PE1_E60A0_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	0x0);	//0:clear, 1:enable
		PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,	0x0);	//0:host access, 1:normal mode
		PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,		0x1);	//ai 0:disable, 1:enable
		PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,0x0);	//address
		PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
		for(count=0;count<PE_DCM_HW_E60_LUT_STEP;count++)
		{
			PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(pLut[count],0,10));//y data
			PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(pLut[count],16,10));//x data
			PE_CC_PE1_E60_WrFL(pe1_dce_ia_data);
		}
		PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 0x1);	//0:host access, 1:normal mode
		PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	0x1);	//0:clear, 1:enable
		PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
		PE_DCM_HW_E60_DBG_PRINT("[Dce]cnt:%d<-%d,num:%4d, lut:|%3d|%3d|%3d|%3d|%3d| |%3d|%3d|%3d|%3d|%3d|\n",\
			pre_lut_cnt, pInfo->dce_lut_cnt, pInfo->dce_lut_num, \
			GET_BITS(pLut[0],16,10), GET_BITS(pLut[1],16,10), GET_BITS(pLut[2],16,10), \
			GET_BITS(pLut[3],16,10), GET_BITS(pLut[4],16,10), \
			GET_BITS(pLut[0],0,10), GET_BITS(pLut[1],0,10), GET_BITS(pLut[2],0,10), \
			GET_BITS(pLut[3],0,10), GET_BITS(pLut[4],0,10));
		pre_lut_cnt=pInfo->dce_lut_cnt;
	} while (0);
	#endif
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDtmLut(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
#define PE_DCM_DTM_LUT_SIZE 33
	UINT32 count=0;
	UINT32 lut_data=0;
	static UINT32 preDtmLut[PE_DCM_DTM_LUT_SIZE]={0,};
	//int i;
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DTM_LUT_T *pp = (LX_PE_DCM_DTM_LUT_T *)pstParams;
		static LX_PE_DCM_DTM_LUT_T prev[LX_PE_WIN_NUM];
		static UINT32 chk = 0x0;
		PE_CHECK_WINID(pp->win_id);
		if(memcmp(preDtmLut, pp->data, pp->size*sizeof(UINT32))==0)
		{
			pp->win_id =0xff;
		}
		//PE_CHECK_DUPLICATE(LX_PE_DCM_DTM_LUT_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DCM_HW_E60_DBG_PRINT("duplicated DB : LX_PE_DCM_DTM_LUT_T\n");
			ret=RET_OK;
			break;
		}
		PE_DCM_HW_E60_CHECK_CODE((pp->size>PE_DCM_DTM_LUT_SIZE), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pp->size);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_DTM_E60_RdFL(dtm_llut0_ia_data);
				//PE_VSD_DTM_E60_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x0);
				PE_VSD_DTM_E60_QWr03(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x1,\
														hif_llut0_enable,	0x0,\
													 	hif_llut0_address,	0x0);
				PE_DCM_HW_E60_DBG_PRINT("\n update dmt lut\n");
				PE_DCM_HW_E60_DBG_PRINT("\n   [ i]    x,    y\n");
				for(count=0; count<32 ;count++)
				{
					lut_data = pp->data[count];
					PE_VSD_DTM_E60_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_y,GET_BITS(lut_data,0,10));//y data
					PE_VSD_DTM_E60_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_x,GET_BITS(lut_data,16,10));//x data
					PE_VSD_DTM_E60_WrFL(dtm_llut0_ia_data);
					PE_DCM_HW_E60_DBG_PRINT("   [%02d] %4d, %4d\n", \
						count, GET_BITS(lut_data,16,10), GET_BITS(lut_data,0,10));
				}
				lut_data = pp->data[32];
				PE_VSD_DTM_E60_QWr02(dtm_llut_ctrl_05, hif_llut_wdata_y_33rd, GET_BITS(lut_data,0,10),\
													   hif_llut_wdata_x_33rd, GET_BITS(lut_data,16,10));
				PE_VSD_DTM_E60_QWr03(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x0,\
														hif_llut0_enable,	0x1,\
														hif_llut0_load,		0x1);
				//PE_VSD_DTM_E60_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x1);
				#if 1	/* E60F20_APB */
				do {
					for(count=0; count<32 ;count++)
					{
						lut_data = pp->data[count];
						PE_CHPI_APB0_E60F20_Wr(dtm0.dtm_llut0_ia_data[count].hif_llut0_wdata_y,GET_BITS(lut_data,0,10));//y data
						PE_CHPI_APB0_E60F20_Wr(dtm0.dtm_llut0_ia_data[count].hif_llut0_wdata_x,GET_BITS(lut_data,16,10));//x data
						PE_CHPI_APB0_E60F20_WrFL(dtm0.dtm_llut0_ia_data[count].udata32);
					}
					lut_data = pp->data[32];
					PE_CHPI_APB0_E60F20_Wr(dtm0.dtm_llut_ctrl_05.hif_llut_wdata_y_33rd,GET_BITS(lut_data,0,10));
					PE_CHPI_APB0_E60F20_Wr(dtm0.dtm_llut_ctrl_05.hif_llut_wdata_x_33rd,GET_BITS(lut_data,16,10));
					PE_CHPI_APB0_E60F20_WrFL(dtm0.dtm_llut_ctrl_05.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DTM0);
				} while(0);
				#endif
				memcpy(preDtmLut,pp->data, pp->size*sizeof(UINT32));
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_GetDtmLut(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DTM_LUT_T *pp = (LX_PE_DCM_DTM_LUT_T *)pstParams;
		PE_CHECK_WINID(pp->win_id);
		PE_DCM_HW_E60_CHECK_CODE((pp->size>PE_DCM_HW_E60_LUT_STEP), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pp->size);
		win_id = PE_GET_CHECKED_WINID(pp->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				
				PE_VSD_DTM_E60_QWr02(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x1,\
														hif_llut0_enable,	0x0);
				for(count=0;count<(pp->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_E60_LUT_MAX-1))
					{
						PE_CE_PE1_E60_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CE_PE1_E60_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_E60_LUT_MAX-1)
					{
						PE_CE_PE1_E60_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CE_PE1_E60_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_VSD_DTM_E60_RdFL(dtm_llut0_ia_data);
					pp->data[count] = PE_VSD_DTM_E60_Rd(dtm_llut0_ia_data);
					#endif
				}
				PE_VSD_DTM_E60_QWr02(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x0,\
														hif_llut0_enable,	0x1);
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60F20_DownloadDrcDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DDR_DB_E60F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_drc_data = p_phys_db->drc_lut.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_data);
		if (PE_KDRV_VER_E60)
		{
			/* header */
			sec_typ = PE_DDR_E60F20_SEC_DRC_LUT;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_E60F20_DRC_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_E60F20_DRC_LUT_SIZE;
			p_phys_db->drc_lut.header.version	= p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_lut.header.sec_type	= p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_lut.header.item_num	= p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_E60F20_DRC_LUT_ITEM_NUM * PE_DDR_E60F20_DRC_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_E60F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_E60F20_HEADER_T);
			/* wr ddr */
				memcpy((UINT32 *)p_drc_data, pe_drc_lut_f20, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60F20_DownloadDrcCurvDbInit(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DDR_DB_E60F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_drc_cuv = p_phys_db->drc_cuv.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_cuv);
		if (PE_KDRV_VER_E60)
		{
			/* header */
			sec_typ = PE_DDR_E60F20_SEC_DRC_CURV;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_E60F20_DRC_CURV_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DRC_E60F20_FW_LUT_SIZE;
			p_phys_db->drc_cuv.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_cuv.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_cuv.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_cuv.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_E60F20_DRC_CURV_ITEM_NUM * PE_DRC_E60F20_FW_LUT_SIZE * sizeof(SINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_E60F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_E60F20_HEADER_T);
			/* wr ddr */
			memcpy((UINT32 *)p_drc_cuv, pe_drc_lut_init, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x, size:%d)\n", \
				PE_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->top_h.sec_size[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60F20_DownloadDrcCurvDb(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_DCM_DRC_CUV_T *pp;
	int i, j;
 	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_E60)
		{
			pp=(LX_PE_DCM_DRC_CUV_T *)pstParams;
			for (i=0; i<LX_PE_CM_GLOBAL_POINT; i++)
			{
				PE_CHPI_TBL0_E60F20_QWr(drc.global_apl[i],pp->global_apl[i]);
 			}
  			for (i=0; i<LX_PE_CM_LOCAL_POINT; i++)
			{
				PE_CHPI_TBL0_E60F20_QWr(drc.local_apl[i],pp->local_apl[i]);
 			}
			PE_CHPI_TBL0_E60F20_QWr(drc.cuv_gain_w,pp->cuv_gain_w);
			PE_CHPI_TBL0_E60F20_QWr(drc.cuv_gain_b,pp->cuv_gain_b);
			for (i=0; i<LX_PE_CM_FREE_POINT; i++)
			{
				for (j=0; j<LX_PE_CM_LOCAL_CURVE_FW; j++)
				{
					PE_CHPI_TBL0_E60F20_QWr(drc.n1p_trans_curv[i][j],pp->n1p_trans_curv[i][j]);
					PE_CHPI_TBL0_E60F20_QWr(drc.n2p_trans_curv[i][j],pp->n2p_trans_curv[i][j]);
					PE_CHPI_TBL0_E60F20_QWr(drc.n3p_trans_curv[i][j],pp->n3p_trans_curv[i][j]);
					PE_CHPI_TBL0_E60F20_QWr(drc.n4p_trans_curv[i][j],pp->n4p_trans_curv[i][j]);
				}
			}
			PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_DRC);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif 
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
int PE_DCM_HW_E60_SetAccelDceLut(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 dyn_bypass[16] = {0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960};
	int count=0;
	int print_co=0;
	do{
		PE_DCM_HW_E60_DBG_PRINT("set dce lut accel mode\n");
		if(PE_KDRV_VER_E60)
		{
			while(1)
			{
				PE_CC_PE1_E60_RdFL(pe1_dce_ia_ctrl);
				PE_CC_PE1_E60_RdFL(pe1_dce_ia_data);
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<16;count++)
				{
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(dyn_bypass[count],0,10));	//y data
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(dyn_bypass[count],0,10));//x data
					PE_CC_PE1_E60_WrFL(pe1_dce_ia_data);
				}
				/* 20160601, read register on addr0 to avoid white flash */
				//PE_CEO_PE1_E60_WrFL(pe1_dce_ia_ctrl);
				//PE_CEO_PE1_E60_RdFL(pe1_dce_ia_data);
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
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
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDseCtrl2(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			LX_PE_DCM_DSE_CTRL4_T *pp = (LX_PE_DCM_DSE_CTRL4_T *)pstParams;
			static LX_PE_DCM_DSE_CTRL4_T prev[LX_PE_WIN_NUM];
			static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_DCM_DSE_CTRL4_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DCM_HW_E60_DBG_PRINT("duplicated DB : LX_PE_DCM_DSE_CTRL3_T\n");
				ret=RET_OK;
				break;
			}
			PE_DCM_HW_E60_DBG_PRINT("[wid:%d] set: chroma_gain_en:%d\n"\
					"chroma_cb_gain1:%d,chroma_cb_gain2:%d,chroma_cr_gain1:%d,chroma_cr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
					"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
					pp->win_id,\
					pp->chroma_gain_en, \
					pp->chroma_cb_gain1,pp->chroma_cb_gain2,\
					pp->chroma_cr_gain1,pp->chroma_cr_gain2,\
					pp->chroma_alpha1,pp->chroma_alpha2,\
					pp->dtm_hue_gain,pp->dtm_sat_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(_g_pe_dcm_hw_e60_info.is_external_chip ==0x0)//single chip
				{
					PE_CC_PE1_E60_QWr03(pe1_dce_chr_gain,		chroma_gain_enable, GET_BITS(pp->chroma_gain_en,0,1),\
																dce_cb_gain1,		GET_BITS(pp->chroma_cb_gain1,0,10),\
																dce_cb_gain2,		GET_BITS(pp->chroma_cb_gain2,0,10));
				}
				else
				{
					PE_CC_PE1_E60_QWr03(pe1_dce_chr_gain,		chroma_gain_enable, 0x0,\
																dce_cb_gain1,		GET_BITS(pp->chroma_cb_gain1,0,10),\
																dce_cb_gain2,		GET_BITS(pp->chroma_cb_gain2,0,10));
				}
				
				PE_CC_PE1_E60_QWr02(pe1_dce_chr_gain2,	dce_cr_gain1,		GET_BITS(pp->chroma_cr_gain1,0,10),\
															dce_cr_gain2,		GET_BITS(pp->chroma_cr_gain2,0,10));
				/* do not setting dce_chr_alpha1, dce_chr_alpha2 bc f/w overwrite */
				//PE_CC_PE1_E60_QWr02(pe1_dce_chr_alpha,	dce_chr_alpha1,		GET_BITS(pp->chroma_alpha1,0,10),\
				//											dce_chr_alpha2,		GET_BITS(pp->chroma_alpha2,0,10));
				PE_VSD_DTM_E60_QWr02(dtm_hue_sat_ctrl,	reg_sat_prsv_ratio,	GET_BITS(pp->dtm_sat_gain,0,8),\
															reg_hue_prsv_ratio, GET_BITS(pp->dtm_hue_gain,0,8));
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_gain.chroma_gain_enable,GET_BITS(pp->chroma_gain_en,0,1));
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_gain.dce_cb_gain1,GET_BITS(pp->chroma_cb_gain1,0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_gain.dce_cb_gain2,GET_BITS(pp->chroma_cb_gain2,0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_gain2.dce_cr_gain1,GET_BITS(pp->chroma_cr_gain1,0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_chr_gain2.dce_cr_gain2,GET_BITS(pp->chroma_cr_gain2,0,10));
					PE_CHPI_APB0_E60F20_Wr(dtm0.dtm_hue_sat_ctrl.reg_sat_prsv_ratio,GET_BITS(pp->dtm_sat_gain,0,8));
					PE_CHPI_APB0_E60F20_Wr(dtm0.dtm_hue_sat_ctrl.reg_hue_prsv_ratio,GET_BITS(pp->dtm_hue_gain,0,8));
					PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_chr_gain.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_chr_gain2.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dtm0.dtm_hue_sat_ctrl.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DCE0);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DTM0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_GetDseCtrl2(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_E60)
		{
			LX_PE_DCM_DSE_CTRL4_T *pp=(LX_PE_DCM_DSE_CTRL4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				
				PE_CC_PE1_E60_QRd03(pe1_dce_chr_gain,		chroma_gain_enable, pp->chroma_gain_en,\
															dce_cb_gain1,		pp->chroma_cb_gain1,\
															dce_cb_gain2,		pp->chroma_cb_gain2);
				PE_CC_PE1_E60_QRd02(pe1_dce_chr_gain2,	dce_cr_gain1,		pp->chroma_cr_gain1,\
															dce_cr_gain2,		pp->chroma_cr_gain2);
				PE_CC_PE1_E60_QRd02(pe1_dce_chr_alpha,	dce_chr_alpha1,		pp->chroma_alpha1,\
															dce_chr_alpha2,		pp->chroma_alpha2);
				PE_VSD_DTM_E60_QRd02(dtm_hue_sat_ctrl,	reg_sat_prsv_ratio,	pp->dtm_sat_gain,\
															reg_hue_prsv_ratio, pp->dtm_hue_gain);
			}
			PE_DCM_HW_E60_DBG_PRINT("[wid:%d] get: chroma_gain_en:%d\n"\
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
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_DCM_HW_E60_SetDceLut2(void *pstParams)
{
	int ret = RET_OK;
#ifndef PE_HW_E60_BRINGUP
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DCE_LUT1_T *pp = (LX_PE_DCM_DCE_LUT1_T *)pstParams;
		static LX_PE_DCM_DCE_LUT1_T prev[LX_PE_WIN_NUM];
		static UINT32 chk = 0x0;
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_DCM_DCE_LUT1_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DCM_HW_E60_DBG_PRINT("duplicated DB : LX_PE_DCM_DCE_LUT1_T\n");
			ret=RET_OK;
			break;
		}
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(_g_pe_dcm_hw_e60_info.is_external_chip ==0x0)//single chip
				{
					PE_CC_PE1_E60_RdFL(pe1_dce_ia_ctrl);
					PE_CC_PE1_E60_RdFL(pe1_dce_ia_data);
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl, hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl, hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl, hif_dyc_address,	0x0);	//address
					PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
				}
				PE_DCM_HW_E60_DBG_PRINT("\n update dce lut\n");
				PE_DCM_HW_E60_DBG_PRINT("\n   [ i]	  x,	y\n");
				for(count=0;count<32;count++)
				{
					if(_g_pe_dcm_hw_e60_info.is_external_chip ==0x0)//single chip
					{
						PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(pp->lumalut_y[count],0,10));//y data
						PE_CC_PE1_E60_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(pp->lumalut_x[count],0,10));//x data
						PE_CC_PE1_E60_WrFL(pe1_dce_ia_data);
					}
					PE_DCM_HW_E60_DBG_PRINT("   [%02d] %4d, %4d\n", count, \
						GET_BITS(pp->lumalut_x[count],0,10), GET_BITS(pp->lumalut_y[count],0,10));
				}
				/* 20160601, read register on addr0 to avoid white flash */
				if(_g_pe_dcm_hw_e60_info.is_external_chip ==0x0)//single chip
				{
					PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);
					PE_CC_PE1_E60_RdFL(pe1_dce_ia_data);
					
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl, hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
					PE_CC_PE1_E60_Wr01(pe1_dce_ia_ctrl, hif_dce_load,		0x1);	//0:clear, 1:enable
					PE_CC_PE1_E60_WrFL(pe1_dce_ia_ctrl);

					PE_CCO1_VERI_E60_QWr02(sys_veri_20,chroma_face_alpha_lut1_x0, GET_BITS(pp->chroma_face_alpha_lut1_x[0],0,8),\
														  chroma_face_alpha_lut1_x1, GET_BITS(pp->chroma_face_alpha_lut1_x[1],0,8));
					PE_CCO1_VERI_E60_QWr02(sys_veri_21,chroma_face_alpha_lut1_x2, GET_BITS(pp->chroma_face_alpha_lut1_x[2],0,8),\
														  chroma_face_alpha_lut1_x3, GET_BITS(pp->chroma_face_alpha_lut1_x[3],0,8));
					PE_CCO1_VERI_E60_QWr02(sys_veri_22,chroma_face_alpha_lut1_y0, GET_BITS(pp->chroma_face_alpha_lut1_y[0],0,10),\
														  chroma_face_alpha_lut1_y1, GET_BITS(pp->chroma_face_alpha_lut1_y[1],0,10));
					PE_CCO1_VERI_E60_QWr02(sys_veri_23,chroma_face_alpha_lut1_y2, GET_BITS(pp->chroma_face_alpha_lut1_y[2],0,10),\
														  chroma_face_alpha_lut1_y3, GET_BITS(pp->chroma_face_alpha_lut1_y[3],0,10));
					PE_CCO1_VERI_E60_QWr02(sys_veri_24,chroma_face_alpha_lut2_x0, GET_BITS(pp->chroma_face_alpha_lut2_x[0],0,8),\
														  chroma_face_alpha_lut2_x1, GET_BITS(pp->chroma_face_alpha_lut2_x[1],0,8));
					PE_CCO1_VERI_E60_QWr02(sys_veri_25,chroma_face_alpha_lut2_x2, GET_BITS(pp->chroma_face_alpha_lut2_x[2],0,8),\
														  chroma_face_alpha_lut2_x3, GET_BITS(pp->chroma_face_alpha_lut2_x[3],0,8));
					PE_CCO1_VERI_E60_QWr02(sys_veri_26,chroma_face_alpha_lut2_y0, GET_BITS(pp->chroma_face_alpha_lut2_y[0],0,10),\
														  chroma_face_alpha_lut2_y1, GET_BITS(pp->chroma_face_alpha_lut2_y[1],0,10));
					PE_CCO1_VERI_E60_QWr02(sys_veri_27,chroma_face_alpha_lut2_y2, GET_BITS(pp->chroma_face_alpha_lut2_y[2],0,10),\
														  chroma_face_alpha_lut2_y3, GET_BITS(pp->chroma_face_alpha_lut2_y[3],0,10));
				}
				
				PE_DCM_HW_E60_DBG_PRINT("[wid:%d] set: \n"\
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
				#if 0	/* E60F20_APB - seperated out to PE_DCM_HW_E60F20_SetDceLut*/ 
				do {
					tmp0 =	GET_BITS(pp->lumalut_y[0],0,8)<<24 | GET_BITS(pp->lumalut_y[1],0,8)<<16 |\
							GET_BITS(pp->lumalut_y[2],0,8)<<8  |  GET_BITS(pp->lumalut_y[3],0,8);
					tmp1 =	GET_BITS(pp->lumalut_y[4],0,8)<<24 | GET_BITS(pp->lumalut_y[5],0,8)<<16 |\
							GET_BITS(pp->lumalut_y[6],0,8)<<8  |  GET_BITS(pp->lumalut_y[7],0,8);
					tmp2 =	GET_BITS(pp->lumalut_y[8],0,32);
					tmp3 =	GET_BITS(pp->lumalut_y[9],0,8)<<24 | GET_BITS(pp->lumalut_y[10],0,8)<<16 |\
							GET_BITS(pp->lumalut_y[11],0,8)<<8 |  GET_BITS(pp->lumalut_y[12],0,8);
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_ia_data[0].hif_dyc_wdata_x,tmp0);
					PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_ia_data[0].udata32);
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_ia_data[1].hif_dyc_wdata_x,tmp1);
					PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_ia_data[1].udata32);
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_ia_data[2].hif_dyc_wdata_x,tmp2);
					PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_ia_data[2].udata32);
					PE_CHPI_APB0_E60F20_Wr(dce0.pe1_dce_ia_data[3].hif_dyc_wdata_x,tmp3);
					PE_CHPI_APB0_E60F20_WrFL(dce0.pe1_dce_ia_data[3].udata32);
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_20.chroma_face_alpha_lut1_x0,GET_BITS(pp->chroma_face_alpha_lut1_x[0],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_20.chroma_face_alpha_lut1_x1,GET_BITS(pp->chroma_face_alpha_lut1_x[1],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_21.chroma_face_alpha_lut1_x2,GET_BITS(pp->chroma_face_alpha_lut1_x[2],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_21.chroma_face_alpha_lut1_x3,GET_BITS(pp->chroma_face_alpha_lut1_x[3],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_22.chroma_face_alpha_lut1_y0,GET_BITS(pp->chroma_face_alpha_lut1_y[0],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_22.chroma_face_alpha_lut1_y1,GET_BITS(pp->chroma_face_alpha_lut1_y[1],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_23.chroma_face_alpha_lut1_y2,GET_BITS(pp->chroma_face_alpha_lut1_y[2],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_23.chroma_face_alpha_lut1_y3,GET_BITS(pp->chroma_face_alpha_lut1_y[3],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_24.chroma_face_alpha_lut2_x0,GET_BITS(pp->chroma_face_alpha_lut2_x[0],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_24.chroma_face_alpha_lut2_x1,GET_BITS(pp->chroma_face_alpha_lut2_x[1],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_25.chroma_face_alpha_lut2_x2,GET_BITS(pp->chroma_face_alpha_lut2_x[2],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_25.chroma_face_alpha_lut2_x3,GET_BITS(pp->chroma_face_alpha_lut2_x[3],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_26.chroma_face_alpha_lut2_y0,GET_BITS(pp->chroma_face_alpha_lut2_y[0],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_26.chroma_face_alpha_lut2_y1,GET_BITS(pp->chroma_face_alpha_lut2_y[1],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_27.chroma_face_alpha_lut2_y2,GET_BITS(pp->chroma_face_alpha_lut2_y[2],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_27.chroma_face_alpha_lut2_y3,GET_BITS(pp->chroma_face_alpha_lut2_y[3],0,10));
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_20.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_21.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_22.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_23.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_24.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_25.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_26.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_27.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DCE0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do\n"); ret = RET_OK;
		}
	} while (0);
#endif /*PE_HW_E60_BRINGUP*/
	return ret;

}

/**
 * set dce lut for f20
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_E60F20_SetDceLut(void *pstParams)
{
	int ret = RET_OK;
#ifndef PE_HW_E60_BRINGUP
	UINT32 tmp0,tmp1,tmp2,tmp3;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DCE_LUT1_T *pp = (LX_PE_DCM_DCE_LUT1_T *)pstParams;
		static LX_PE_DCM_DCE_LUT1_T prev[LX_PE_WIN_NUM];
		static UINT32 chk = 0x0;
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_DCM_DCE_LUT1_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DCM_HW_E60_DBG_PRINT("duplicated DB : LX_PE_DCM_DCE_LUT1_T\n");
			ret=RET_OK;
			break;
		}
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				
				PE_DCM_HW_E60_DBG_PRINT("\n update dce lut\n");
				PE_DCM_HW_E60_DBG_PRINT("\n   [ i]	  x,	y\n");
				for(count=0;count<32;count++)
				{
					
					PE_DCM_HW_E60_DBG_PRINT("   [%02d] %4d, %4d\n", count, \
						GET_BITS(pp->lumalut_x[count],0,10), GET_BITS(pp->lumalut_y[count],0,10));
				}
				PE_DCM_HW_E60_DBG_PRINT("[wid:%d] get: \n"\
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

				PE_CCO1_VERI_E60_QWr02(sys_veri_20,chroma_face_alpha_lut1_x0, GET_BITS(pp->chroma_face_alpha_lut1_x[0],0,8),\
													  chroma_face_alpha_lut1_x1, GET_BITS(pp->chroma_face_alpha_lut1_x[1],0,8));
				PE_CCO1_VERI_E60_QWr02(sys_veri_21,chroma_face_alpha_lut1_x2, GET_BITS(pp->chroma_face_alpha_lut1_x[2],0,8),\
													  chroma_face_alpha_lut1_x3, GET_BITS(pp->chroma_face_alpha_lut1_x[3],0,8));
				PE_CCO1_VERI_E60_QWr02(sys_veri_22,chroma_face_alpha_lut1_y0, GET_BITS(pp->chroma_face_alpha_lut1_y[0],0,10),\
													  chroma_face_alpha_lut1_y1, GET_BITS(pp->chroma_face_alpha_lut1_y[1],0,10));
				PE_CCO1_VERI_E60_QWr02(sys_veri_23,chroma_face_alpha_lut1_y2, GET_BITS(pp->chroma_face_alpha_lut1_y[2],0,10),\
													  chroma_face_alpha_lut1_y3, GET_BITS(pp->chroma_face_alpha_lut1_y[3],0,10));
				PE_CCO1_VERI_E60_QWr02(sys_veri_24,chroma_face_alpha_lut2_x0, GET_BITS(pp->chroma_face_alpha_lut2_x[0],0,8),\
													  chroma_face_alpha_lut2_x1, GET_BITS(pp->chroma_face_alpha_lut2_x[1],0,8));
				PE_CCO1_VERI_E60_QWr02(sys_veri_25,chroma_face_alpha_lut2_x2, GET_BITS(pp->chroma_face_alpha_lut2_x[2],0,8),\
													  chroma_face_alpha_lut2_x3, GET_BITS(pp->chroma_face_alpha_lut2_x[3],0,8));
				PE_CCO1_VERI_E60_QWr02(sys_veri_26,chroma_face_alpha_lut2_y0, GET_BITS(pp->chroma_face_alpha_lut2_y[0],0,10),\
													  chroma_face_alpha_lut2_y1, GET_BITS(pp->chroma_face_alpha_lut2_y[1],0,10));
				PE_CCO1_VERI_E60_QWr02(sys_veri_27,chroma_face_alpha_lut2_y2, GET_BITS(pp->chroma_face_alpha_lut2_y[2],0,10),\
													  chroma_face_alpha_lut2_y3, GET_BITS(pp->chroma_face_alpha_lut2_y[3],0,10));
				#if 1	/* E60F20_APB */
				do {
					tmp0 =	GET_BITS(pp->lumalut_y[0],0,8)<<24 | GET_BITS(pp->lumalut_y[1],0,8)<<16 |\
							GET_BITS(pp->lumalut_y[2],0,8)<<8  | GET_BITS(pp->lumalut_y[3],0,8);
					tmp1 =	GET_BITS(pp->lumalut_y[4],0,8)<<24 | GET_BITS(pp->lumalut_y[5],0,8)<<16 |\
							GET_BITS(pp->lumalut_y[6],0,8)<<8  | GET_BITS(pp->lumalut_y[8],0,8);
					tmp2 =	GET_BITS(pp->lumalut_y[7],0,32);
					tmp3 =	GET_BITS(pp->lumalut_y[9],0,8)<<24 | GET_BITS(pp->lumalut_y[10],0,8)<<16 |\
							GET_BITS(pp->lumalut_y[11],0,8)<<8 | GET_BITS(pp->lumalut_y[12],0,8);
					PE_DCM_HW_E60_DBG_PRINT("veri28:0x%08x, veri29:0x%08x, veri30:0x%08x, veri31:0x%08x\n", \
						tmp0, tmp1, tmp2, tmp3);
					PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[0].udata32,tmp0);
					PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[1].udata32,tmp1);
					PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[2].udata32,tmp2);
					PE_CHPI_APB0_E60F20_QWr(dce0.pe1_dce_ia_data[3].udata32,tmp3);
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_20.chroma_face_alpha_lut1_x0,GET_BITS(pp->chroma_face_alpha_lut1_x[0],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_20.chroma_face_alpha_lut1_x1,GET_BITS(pp->chroma_face_alpha_lut1_x[1],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_21.chroma_face_alpha_lut1_x2,GET_BITS(pp->chroma_face_alpha_lut1_x[2],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_21.chroma_face_alpha_lut1_x3,GET_BITS(pp->chroma_face_alpha_lut1_x[3],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_22.chroma_face_alpha_lut1_y0,GET_BITS(pp->chroma_face_alpha_lut1_y[0],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_22.chroma_face_alpha_lut1_y1,GET_BITS(pp->chroma_face_alpha_lut1_y[1],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_23.chroma_face_alpha_lut1_y2,GET_BITS(pp->chroma_face_alpha_lut1_y[2],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_23.chroma_face_alpha_lut1_y3,GET_BITS(pp->chroma_face_alpha_lut1_y[3],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_24.chroma_face_alpha_lut2_x0,GET_BITS(pp->chroma_face_alpha_lut2_x[0],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_24.chroma_face_alpha_lut2_x1,GET_BITS(pp->chroma_face_alpha_lut2_x[1],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_25.chroma_face_alpha_lut2_x2,GET_BITS(pp->chroma_face_alpha_lut2_x[2],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_25.chroma_face_alpha_lut2_x3,GET_BITS(pp->chroma_face_alpha_lut2_x[3],0,8));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_26.chroma_face_alpha_lut2_y0,GET_BITS(pp->chroma_face_alpha_lut2_y[0],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_26.chroma_face_alpha_lut2_y1,GET_BITS(pp->chroma_face_alpha_lut2_y[1],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_27.chroma_face_alpha_lut2_y2,GET_BITS(pp->chroma_face_alpha_lut2_y[2],0,10));
					PE_CHPI_APB0_E60F20_Wr(dce0.cco1_veri_27.chroma_face_alpha_lut2_y3,GET_BITS(pp->chroma_face_alpha_lut2_y[3],0,10));
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_20.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_21.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_22.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_23.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_24.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_25.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_26.udata32);
					PE_CHPI_APB0_E60F20_WrFL(dce0.cco1_veri_27.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_DCE0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do\n"); ret = RET_OK;
		}
	} while (0);
#endif /*PE_HW_E60_BRINGUP*/
	return ret;

}

int PE_DCM_HW_E60F20_DownloadLibDb(void *pstParams)
{
	int ret = RET_OK;
#ifndef PE_HW_E60_BRINGUP
	PE_CFG_CTRL_T stParams;
	PE_DCM_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = NULL;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = NULL;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db_chk = NULL;
	LX_PE_DCM_LIB_DB_ALL_T *pp =(LX_PE_DCM_LIB_DB_ALL_T*)pstParams;
	UINT32 load_data[3];
	UINT32 load_size;
	p_shdw_db = gPE_DCM_DDR_DB_E60F20.shdw.data;
	p_phys_db = gPE_DCM_DDR_DB_E60F20.phys.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_E60)
		{
			PE_PRINT_NOTI("DC db start.\n");
			PE_INF_HW_E60_BACKUP_TRACE("[DCMDb][E60F20]start");
			memset(p_phys_db,0,sizeof(PE_DCM_DDR_DB_PHYS_REG_E60F20_T));
			wmb();
			p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_DCM_DDR_E60F20_DB_VER;
			p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_E60F20_DCM_DDR_BASE;
			p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_DCM_DDR_E60F20_SEC_NUM;
			PE_PRINT_NOTI("PE_E60F20_DDR_BASE: 0x%08x\n", PE_E60F20_DCM_DDR_BASE);
			/* *********************************************************************/
			/* Causion : Should be arranged in enum order **************************/
			/* *********************************************************************/
			/* dyn : PE_DCM_DDR_E60F20_SEC_DNY */
			ret = PE_DCM_HW_E60F20_DownloadDYN(&pp->dynContDB);
			PE_DCM_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DCM_HW_E60F20_DownloadDYN() error.\n",__F__,__L__);
			/* apl : PE_DCM_DDR_E60F20_SEC_APL */
			ret = PE_DCM_HW_E60F20_DownloadAPL(&pp->aplDB);
			PE_DCM_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DCM_HW_E60F20_DownloadAPL() error.\n",__F__,__L__);
			/* ai gain : PE_DCM_DDR_E60F20_SEC_GAIN */
			ret = PE_DCM_HW_E60F20_DownloadGain(&pp->aiGainDB);
			PE_DCM_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DCM_DDR_E60F20_SEC_GAIN() error.\n",__F__,__L__);
			/* StabilizerGainTable : PE_DCM_DDR_E60F20_SEC_TABLE */
			ret = PE_DCM_HW_E60F20_DownloadTable(&pp->stabilzerDB);
			PE_DCM_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DCM_HW_E60F20_DownloadTable() error.\n",__F__,__L__);
			wmb();
			/* E60F20_CRC */
			#if 1
			do {
				UINT32 i, j, ddr_size32, crc32 = 0xFFFFFFFF;
				volatile UINT32 *pddr_data32;
				UINT32 ddr_data32;
				UINT8 *pddr_data08;
				ddr_size32 = (sizeof(PE_DCM_DDR_DB_PHYS_REG_E60F20_T)>>2)-1;//except for crc
				pddr_data32 = (volatile UINT32 *)p_phys_db;
				pddr_data08 = (UINT8 *)&ddr_data32;
				PE_PRINT_NOTI("[CRC]S: size32:%d\n",ddr_size32);
				PE_INF_HW_E60_BACKUP_TRACE("[CRC]S: size32:%d",ddr_size32);
				for (i=0;i<ddr_size32;i++)
				{
					rmb();
					ddr_data32 = (UINT32)pddr_data32[i];
					rmb();

					j = ((int) (crc32 >> 24) ^ pddr_data08[0]) & 0xFF;
					crc32 = (crc32 << 8) ^ g_pe_cmn_hw_e60_crc_table[j];

					j = ((int) (crc32 >> 24) ^ pddr_data08[1]) & 0xFF;
					crc32 = (crc32 << 8) ^ g_pe_cmn_hw_e60_crc_table[j];

					j = ((int) (crc32 >> 24) ^ pddr_data08[2]) & 0xFF;
					crc32 = (crc32 << 8) ^ g_pe_cmn_hw_e60_crc_table[j];

					j = ((int) (crc32 >> 24) ^ pddr_data08[3]) & 0xFF;
					crc32 = (crc32 << 8) ^ g_pe_cmn_hw_e60_crc_table[j];
					#if 0
					PE_PRINT_NOTI("[%03d]data32:%08X,data08:%02X|%02X|%02X|%02X,table[%03d]:%08X,crc32:%08X\n",\
						i,ddr_data32,pddr_data08[0],pddr_data08[1],pddr_data08[2],pddr_data08[3],j,_g_pe_crc_table[j],crc32);
				#endif
				}
				p_phys_db->crc = ~crc32;
				wmb();
				PE_PRINT_NOTI("[CRC]E: crc:0x%08X <- 0x%08X\n",~crc32,crc32);
				PE_INF_HW_E60_BACKUP_TRACE("[CRC]E: crc:0x%08X <- 0x%08X",~crc32,crc32);
			} while(0);
			#endif
			/* inform load db done *//* E60F20_APB */
			do {
				UINT32 load_data[3];
				UINT32 load_size=0;
				load_data[0] = PE_E60F20_DCM_DDR_BASE;
				load_data[1] = sizeof(PE_DCM_DDR_DB_PHYS_REG_E60F20_T);
				load_data[2] = 3;
				load_size = (UINT32)(sizeof(UINT32)*3);
				ret = PE_FWI_E60_LoadDbDone(load_data,load_size);
				PE_DCM_HW_E60_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_E60F20_DownloadLibDb() error.\n",__F__,__L__);
				PE_PRINT_NOTI("[Db]DcmDbDone(0x%08x)(%d)(%d)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_size);
				PE_INF_HW_E60_BACKUP_TRACE("[Db]DcmDbDone(0x%08x)(%d)(%d)(size:%d)",load_data[0],load_data[1],load_data[2],load_size);
			} while(0);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

static int PE_DCM_HW_E60F20_DownloadDYN(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	UINT32 item_size =0, item_num =0;
	PE_DCM_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DCM_DDR_DB_E60F20.shdw.data;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DCM_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_dcm_dny = p_phys_db->dcm_dny.data;
	LX_PE_DCM_LIB_DB_T *pp = (LX_PE_DCM_LIB_DB_T*)pstParams;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dcm_dny);
		if (PE_KDRV_VER_E60)
		{
			item_size = pp->sizeOfItem;
			item_num  = pp->lengthOfData;
			/* header */
			sec_typ = PE_DCM_DDR_E60F20_SEC_DNY;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DCM_DDR_E60F20_DCM_DYN_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DCM_DDR_E60F20_DCM_DYN_SIZE;
			p_phys_db->dcm_dny.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dcm_dny.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dcm_dny.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dcm_dny.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DCM_DDR_E60F20_DCM_DYN_ITEM_NUM * PE_DCM_DDR_E60F20_DCM_DYN_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.db_base+sizeof(PE_DCM_DDR_E60F20_TOP_HEADER_T);
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			/* wr ddr */
			PE_INF_HW_E60_BACKUP_TRACE("%s: item_size: %d, item_num %d", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ),item_size,item_num );
			memcpy((UINT32 *)p_dcm_dny, pp->pAddrData, item_size*item_num*sizeof(UINT32));
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

static int PE_DCM_HW_E60F20_DownloadAPL(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	UINT32 item_size =0, item_num =0;
	PE_DCM_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DCM_DDR_DB_E60F20.shdw.data;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DCM_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_dcm_apl = p_phys_db->dcm_apl.data;
	LX_PE_DCM_LIB_DB_T *pp = (LX_PE_DCM_LIB_DB_T*)pstParams;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dcm_apl);
		if (PE_KDRV_VER_E60)
		{
			item_size = pp->sizeOfItem;
			item_num  = pp->lengthOfData;
			/* header */
			sec_typ = PE_DCM_DDR_E60F20_SEC_APL;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DCM_DDR_E60F20_DCM_APL_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DCM_DDR_E60F20_DCM_APL_SIZE;
			p_phys_db->dcm_apl.header.version	= p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dcm_apl.header.sec_type	= p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dcm_apl.header.item_num	= p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dcm_apl.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DCM_DDR_E60F20_DCM_APL_ITEM_NUM * PE_DCM_DDR_E60F20_DCM_APL_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			/* wr ddr */
			PE_INF_HW_E60_BACKUP_TRACE("%s: item_size: %d, item_num %d", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ),item_size,item_num );
			memcpy((UINT32 *)p_dcm_apl,pp->pAddrData, item_size*item_num*sizeof(UINT32));
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

static int PE_DCM_HW_E60F20_DownloadGain(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP

	#if 1
	UINT32 size = 0, sec_typ = 0;
	UINT32 item_size =0, item_num =0;
	PE_DCM_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DCM_DDR_DB_E60F20.shdw.data;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DCM_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_dcm_gain = p_phys_db->dcm_gain.data;
	LX_PE_DCM_LIB_DB_T *pp = (LX_PE_DCM_LIB_DB_T*)pstParams;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dcm_gain);
		if (PE_KDRV_VER_E60)
		{
			item_size = pp->sizeOfItem;
			item_num  = pp->lengthOfData;
			/* header */
			sec_typ = PE_DCM_DDR_E60F20_SEC_GAIN;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DCM_DDR_E60F20_DCM_GAIN_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DCM_DDR_E60F20_DCM_GAIN_SIZE;
			p_phys_db->dcm_gain.header.version	= p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dcm_gain.header.sec_type	= p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dcm_gain.header.item_num	= p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dcm_gain.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DCM_DDR_E60F20_DCM_GAIN_ITEM_NUM * PE_DCM_DDR_E60F20_DCM_GAIN_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			/* wr ddr */
			PE_INF_HW_E60_BACKUP_TRACE("%s: item_size: %d, item_num %d", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ),item_size,item_num );
			memcpy((UINT32 *)p_dcm_gain,pp->pAddrData, item_size*item_num*sizeof(UINT32));
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#else
/********defind types****************/

#define PE_DCM_NUM_TRANSCURVE_E60F20   32
#define PE_DCM_FREE_POINT_E60F20        7
typedef struct  
{
	UINT16	nAplPoint[PE_DCM_FREE_POINT_E60F20];
	UINT32	aiSceneGain[PE_DCM_NUM_TRANSCURVE_E60F20][PE_DCM_FREE_POINT_E60F20];
}
PE_DCM_PLATFROM_DB_E60F20_T;
typedef struct  
{
	UINT32	nAplPoint[PE_DCM_FREE_POINT_E60F20];
	UINT32	aiSceneGain[PE_DCM_NUM_TRANSCURVE_E60F20][PE_DCM_FREE_POINT_E60F20];
}
PE_DCM_DDR_DB_E60F20_T;
	
/************************************/
	int i, j;
	UINT32 size = 0, sec_typ = 0;
	UINT32 item_size =0, item_num =0;
	PE_DCM_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DCM_DDR_DB_E60F20.shdw.data;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DCM_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_dcm_gain = p_phys_db->dcm_gain.data;
	LX_PE_DCM_LIB_DB_T *pp = (LX_PE_DCM_LIB_DB_T*)pstParams;
	PE_DCM_PLATFROM_DB_E60F20_T *p_platform_db;
	PE_DCM_DDR_DB_E60F20_T *p_ddr_db;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dcm_gain);
		if (PE_KDRV_VER_E60)
		{
			item_size = pp->sizeOfItem;
			item_num  = pp->lengthOfData;
			/*malloc for local type transformation*/
			p_platform_db = (PE_DCM_PLATFROM_DB_E60F20_T *)OS_Malloc(sizeof(PE_DCM_PLATFROM_DB_E60F20_T)*item_num);
			p_ddr_db = (PE_DCM_DDR_DB_E60F20_T *)OS_Malloc(sizeof(PE_DCM_DDR_DB_E60F20_T)*item_num);
			/* header */
			sec_typ = PE_DCM_DDR_E60F20_SEC_GAIN;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DCM_DDR_E60F20_DCM_GAIN_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DCM_DDR_E60F20_DCM_GAIN_SIZE;
			p_phys_db->dcm_gain.header.version	= p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dcm_gain.header.sec_type	= p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dcm_gain.header.item_num	= p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dcm_gain.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DCM_DDR_E60F20_DCM_GAIN_ITEM_NUM * PE_DCM_DDR_E60F20_DCM_GAIN_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			/* wr ddr */
			PE_INF_HW_E60_BACKUP_TRACE("%s: item_size platform/ddr: %d/%d, item_num %d", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ),\
				item_size,sizeof(PE_DCM_DDR_DB_E60F20_T)/4,item_num );
			memcpy((UINT32 *)p_platform_db,pp->pAddrData, item_size*item_num*sizeof(UINT32));
			for( i =0; i <item_num; i++)
			{
				for( j =0; j <PE_DCM_FREE_POINT_E60F20; j++)
				{
					p_ddr_db[i].nAplPoint[j] = p_platform_db[i].nAplPoint[j];
				}
				memcpy((UINT32*)p_ddr_db[i].aiSceneGain, (UINT32*)p_platform_db[i].aiSceneGain, \
					sizeof(UINT32)*PE_DCM_NUM_TRANSCURVE_E60F20);
			}
			memcpy((UINT32*)p_dcm_gain, (UINT32*)p_ddr_db, sizeof(PE_DCM_DDR_DB_E60F20_T)*item_num);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

static int PE_DCM_HW_E60F20_DownloadTable(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	UINT32 item_size =0, item_num =0;
	PE_DCM_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DCM_DDR_DB_E60F20.shdw.data;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DCM_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_dcm_table = p_phys_db->dcm_table.data;
	LX_PE_DCM_LIB_DB_T *pp = (LX_PE_DCM_LIB_DB_T*)pstParams;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dcm_table);
		if (PE_KDRV_VER_E60)
		{
			item_size = pp->sizeOfItem;
			item_num  = pp->lengthOfData;
			/* header */
			sec_typ = PE_DCM_DDR_E60F20_SEC_TABLE;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DCM_DDR_E60F20_DCM_TABLE_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DCM_DDR_E60F20_DCM_TABLE_SIZE;
			p_phys_db->dcm_table.header.version	= p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dcm_table.header.sec_type	= p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dcm_table.header.item_num	= p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dcm_table.header.item_size  = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DCM_DDR_E60F20_DCM_TABLE_ITEM_NUM * PE_DCM_DDR_E60F20_DCM_TABLE_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DCM_DDR_E60F20_HEADER_T);
			/* wr ddr */
			PE_INF_HW_E60_BACKUP_TRACE("%s: item_size: %d, item_num %d", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ),item_size,item_num );
			memcpy((UINT32 *)p_dcm_table,pp->pAddrData, item_size*item_num*sizeof(UINT32));
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DCM_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

int PE_DCM_HW_E60F20_GetDCDB(int idexDb, int lengthOfData)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	int i;
	UINT32 size = 0, sec_typ = 0;
	UINT32 item_size =0, item_num =0;
	//PE_DCM_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DCM_DDR_DB_E60F20.shdw.data;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DCM_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_dcm;
	do{
		//CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_E60)
		{
			/* header */
			sec_typ = PE_DCM_DDR_E60F20_SEC_APL;
			//p_shdw_db->sec_d[sec_typ].header.item_size = PE_DCM_DDR_E60F20_DCM_APL_SIZE;
			/* rd ddr */
			//memcpy((UINT32 *)p_dcm_apl,pp->pAddrData, item_size*item_num*sizeof(UINT32));
			switch(idexDb)
			{
				case 0:
				{
					p_dcm = p_phys_db->dcm_dny.data;
					for(i=0; i< PE_DCM_DDR_E60F20_DCM_DYN_SIZE*lengthOfData; i++)
						printk("0x%08X\n",p_dcm[i]);
				}break;
				case 1:
				{
					p_dcm = p_phys_db->dcm_apl.data;
					for(i=0; i< PE_DCM_DDR_E60F20_DCM_APL_SIZE*lengthOfData; i++)
						printk("0x%08X\n",p_dcm[i]);
				}break;
				case 2:
				{
					p_dcm = p_phys_db->dcm_gain.data;
					for(i=0; i< PE_DCM_DDR_E60F20_DCM_GAIN_SIZE*lengthOfData; i++)
						printk("0x%08X\n",p_dcm[i]);
				}break;
				case 3:
				{
					p_dcm = p_phys_db->dcm_table.data;
					for(i=0; i< PE_DCM_DDR_E60F20_DCM_TABLE_SIZE*lengthOfData; i++)
						printk("0x%08X\n",p_dcm[i]);
				}break;
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

int PE_DCM_HW_E60F20_GetDCDBAddr(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	int i;
	UINT32 size = 0, sec_typ = 0;
	UINT32 item_size =0, item_num =0;
	//PE_DCM_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DCM_DDR_DB_E60F20.shdw.data;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DCM_DDR_DB_E60F20.phys.data;
	volatile UINT32 *p_dcm;
	do{
		//CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_E60)
		{
			/* header */
			//sec_typ = PE_DCM_DDR_E60F20_SEC_APL;
			//p_shdw_db->sec_d[sec_typ].header.item_size = PE_DCM_DDR_E60F20_DCM_APL_SIZE;
			/* rd ddr */
			//memcpy((UINT32 *)p_dcm_apl,pp->pAddrData, item_size*item_num*sizeof(UINT32));
			/*DNY*/
			sec_typ = PE_DCM_DDR_E60F20_SEC_DNY;
			printk(">>DNY<<\n");
			for(i=0; i<PE_DCM_DDR_E60F20_DCM_DYN_ITEM_NUM ; i++)
			{
				printk("DNY[%d]: addr 0x%08X\n", i,p_phys_db->top_h.sec_base[sec_typ]+i*4*PE_DCM_DDR_E60F20_DCM_DYN_SIZE);
			}
			/*APL*/
			sec_typ = PE_DCM_DDR_E60F20_SEC_APL;
			printk(">>APL<<\n");
			for(i=0; i<PE_DCM_DDR_E60F20_DCM_APL_ITEM_NUM ; i++)
			{
				printk("APL[%d]: addr 0x%08X\n", i,p_phys_db->top_h.sec_base[sec_typ]+i*4*PE_DCM_DDR_E60F20_DCM_APL_SIZE);
			}
			/*GAIN*/
			sec_typ = PE_DCM_DDR_E60F20_SEC_GAIN;
			printk(">>GAIN<<\n");
			for(i=0; i<PE_DCM_DDR_E60F20_DCM_GAIN_ITEM_NUM ; i++)
			{
				printk("GAIN[%d]: addr 0x%08X\n", i,p_phys_db->top_h.sec_base[sec_typ]+i*4*PE_DCM_DDR_E60F20_DCM_GAIN_SIZE);
			}
			/*TABLE*/
			sec_typ = PE_DCM_DDR_E60F20_SEC_TABLE;
			printk(">>TABLE<<\n");
			for(i=0; i<PE_DCM_DDR_E60F20_DCM_TABLE_ITEM_NUM ; i++)
			{
				printk("TABLE[%d]: addr 0x%08X\n", i,p_phys_db->top_h.sec_base[sec_typ]+i*4*PE_DCM_DDR_E60F20_DCM_TABLE_SIZE);
			}
		}
		else
		{
			PE_DCM_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}