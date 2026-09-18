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

/** @file pe_dcm_hw_o20.c
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

#include "pe_hw_o20.h"
#include "pe_reg_o20.h"
#include "pe_fwi_o20.h"
#include "pe_cmn_hw_o20.h"
#include "pe_dcm_hw_o20.h"
#include "pe_drc_def.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_HW_O20_DCE_LUT_NUM	2
#define PE_DCM_HW_O20_DCE_CNT_NUM	0xfff

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_HW_O20_ERROR	printk

#define PE_DCM_HW_O20_DBG_PRINT(fmt,args...)	\
	if(_g_dcm_hw_o20_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
		
#define PE_DCM_HW_O20_CHECK_CODE(_checker,_action,fmt,args...) \
	{if(_checker){PE_DCM_HW_O20_ERROR(fmt,##args);_action;}}

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
static UINT32 _g_dcm_hw_o20_trace=0x0;	//default should be off.
static PE_DCM_HW_O20_SETTINGS_T _g_pe_dcm_hw_o20_info;

static UINT32 _g_dcm_hw_o20_pre_dse_lut[(PE_DCM_HW_O20_LUT_MAX-1)];	///<previous dse lut


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
int PE_DCM_HW_O20_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 count = 0;
	int i;
	LX_PE_DCM_DCE_CONF_T stParams;
	UINT32 *p_pre_dse_lut = _g_dcm_hw_o20_pre_dse_lut;
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
	PE_REG_O20_HW_OPT_T hw_opt = PE_REG_O20_GetDispOpt();
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			PE_DCM_HW_O20_DBG_PRINT("init histo info.\n");
			memset0(_g_pe_dcm_hw_o20_info);
			_g_pe_dcm_hw_o20_info.cur_blur_gain = 0xf;
			_g_pe_dcm_hw_o20_info.pre_blur_gain = 0xf;
			/* dce init */
			PE_CEO_PE1_O20_QWr(pe1_dce_hist_ia_ctrl,0x00008000);	//0:read mode, 1:normal mode
			PE_CE_PE1_O20_WrFL(pe1_dce_hist_ia_ctrl);
			/* set blur_v_gain 0xf temporally */
			//PE_CEO_PE1_O20_QWr01(pe1_dce_ctrl_01,blur_v_gain,0xf);	//0x0:blur V ~ 0xf:original V
			PE_DCM_HW_O20_DBG_PRINT("init dce config\n");
			/* synchronization with pe1_win2_ctrl_00 win_en(0,1,01) aettings in win.c */
			PE_CEO_PE1_O20_QWr03(pe1_dce_ctrl_00,window0_enable, 0x1,\
                                                   window1_enable, 0x1,\
                                                   window01_enable,0x1);
			stParams.domain = LX_PE_YC_DOMAIN;
			stParams.min_pos = 26;
			stParams.max_pos = 220;
			stParams.win_id = LX_PE_WIN_ALL;
			ret = PE_DCM_HW_O20_SetDceConfig(&stParams);
			PE_DCM_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d][win all] PE_DCM_HW_O20_SetDceConfig() error.\n", __F__, __L__);
			/* dce lut init */
			PE_CEO_PE1_O20_RdFL(pe1_dce_ia_ctrl);
			PE_CEO_PE1_O20_RdFL(pe1_dce_ctrl_08);
			PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
			PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
			PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
			PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
			for(count=0;count<32;count++)
			{
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,	hif_dyc_wdata_y,dce_lut_data[count]);	//y data
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,	hif_dyc_wdata_x,dce_lut_data[count]);	//x data
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_data);
			}
			PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_08,	hif_dyc_wdata_y_32nd,1023);	//y data
			PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_08,	hif_dyc_wdata_x_32nd,1023);	//x data
			PE_CEO_PE1_O20_WrFL(pe1_dce_ctrl_08);
			PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
			PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x1);		//0:host access, 1:normal mode
			PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
			/* dse init */
			/* synchronization with pe1_win2_ctrl_00 win_en(0,1,01) aettings in win.c, DSE YH */
			PE_CE_PE1_O20_QWr03(pe1_dse_ctrl_00,window0_enable, 0x1,\
                                                     window1_enable, 0x1,\
                                                     window01_enable,0x1);
			PE_CO_PE1_O20_QWr03(pe1_dse_ctrl_00,window0_enable, 0x1,\
                                                     window1_enable, 0x1,\
                                                     window01_enable,0x1);
			PE_CEO_PE1_O20_QWr01(pe1_dse_ctrl_01,r_dse_h_grad, 0x2);
			PE_VSD_DTM_O20_QWr02(dtm_hue_sat_ctrl,	reg_hue_prsv_en, 0x1,\
													reg_sat_prsv_en, 0x1);
			/*DTM lut init*/
			PE_VSD_DTM_O20_RdFL(dtm_llut0_ia_data);
			//PE_VSD_DTM_O20_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x0);
			PE_VSD_DTM_O20_QWr03(dtm_llut0_ia_ctrl, hif_llut0_ai,		0x1,\
													hif_llut0_enable,	0x0,\
													hif_llut0_address,	0x0);
			PE_DCM_HW_O20_DBG_PRINT("\n update dmt lut\n");
			PE_DCM_HW_O20_DBG_PRINT("\n   [ i]	  x,	y\n");
			for(count=0; count<32 ;count++)
			{
				//dse_lut_data is bypass curv
				PE_VSD_DTM_O20_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_y,GET_BITS(dse_lut_data[count],0,10));	//y data
				PE_VSD_DTM_O20_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_x,GET_BITS(dse_lut_data[count],0,10));//x data
				PE_VSD_DTM_O20_WrFL(dtm_llut0_ia_data);
				PE_DCM_HW_O20_DBG_PRINT("	[%02d] %4d, %4d\n", \
					count,GET_BITS(dse_lut_data[count],0,10), GET_BITS(dse_lut_data[count],0,10));
			}
			PE_VSD_DTM_O20_QWr02(dtm_llut_ctrl_05, hif_llut_wdata_y_33rd, 0x3ff,\
												   hif_llut_wdata_x_33rd, 0x3ff);
			PE_VSD_DTM_O20_QWr03(dtm_llut0_ia_ctrl, hif_llut0_ai,		0x0,\
													hif_llut0_enable,	0x1,\
													hif_llut0_load, 	0x1);
			PE_VSD_DTM_O20_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x1);

			/* dse lut init */
			if (!pstParams->resume_mode)	//normal init
			{
				PE_CEO_PE1_O20_RdFL(pe1_dse_ia_ctrl);
				PE_CEO_PE1_O20_RdFL(pe1_dse_ctrl_02);
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CEO_PE1_O20_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CEO_PE1_O20_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,dse_lut_data[count]);	//y data
					PE_CEO_PE1_O20_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,dse_lut_data[count]);	//x data
					PE_CEO_PE1_O20_WrFL(pe1_dse_ia_data);
				}
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CEO_PE1_O20_WrFL(pe1_dse_ctrl_02);
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CEO_PE1_O20_WrFL(pe1_dse_ia_ctrl);
				for (i=0;i<(PE_DCM_HW_O20_LUT_MAX-1);i++)
				{
					p_pre_dse_lut[i] = ((dse_lut_data[i]<<16)&0x3ff0000)|(dse_lut_data[i]&0x3ff);
				}
				if(_g_dcm_hw_o20_trace)
				{
					PE_DCM_HW_O20_DBG_PRINT("\n init\n");
					PE_DCM_HW_O20_DBG_PRINT("\n   [ i]    x,    y\n");
					for (i=0;i<(PE_DCM_HW_O20_LUT_MAX-1);i++)
					{
						PE_DCM_HW_O20_DBG_PRINT("   [%02d] %4d, %4d\n", \
							i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
					}
				}
			}
			else
			{
				PE_CEO_PE1_O20_RdFL(pe1_dse_ia_ctrl);
				PE_CEO_PE1_O20_RdFL(pe1_dse_ctrl_02);
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CEO_PE1_O20_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CEO_PE1_O20_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,GET_BITS(p_pre_dse_lut[count],0,10));	//y data
					PE_CEO_PE1_O20_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,GET_BITS(p_pre_dse_lut[count],16,10));
					PE_CEO_PE1_O20_WrFL(pe1_dse_ia_data);
				}
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CEO_PE1_O20_WrFL(pe1_dse_ctrl_02);
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CEO_PE1_O20_WrFL(pe1_dse_ia_ctrl);
				if(_g_dcm_hw_o20_trace)
				{
					PE_DCM_HW_O20_DBG_PRINT("\n resume init\n");
					PE_DCM_HW_O20_DBG_PRINT("\n   [ i]    x,    y\n");
					for (i=0;i<(PE_DCM_HW_O20_LUT_MAX-1);i++)
					{
						PE_DCM_HW_O20_DBG_PRINT("   [%02d] %4d, %4d\n", \
							i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
					}
				}
			}
			
			/* dce config */
			PE_CEO_PE1_O20_RdFL(pe1_dce_ctrl_00);
			PE_CEO_PE1_O20_RdFL(pe1_dce_ctrl_01);
			PE_CEO_PE1_O20_RdFL(pe1_apl_ctrl_02);
			if (hw_opt.external_chip ==0) //4k model
			{
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
			}
			else //8k model
			{
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x0);
			}
			PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	hist_bin_mode,			0x0);					//32bin mode
			PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	window_acquire, 		0x1);					//window acquire on
			PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	dce_domain_sel, 		0x1);	//0:ktd,1:yc
			//PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);					//from pe1 win2
			PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	window_mode_enable, 	0x1);					//window sync
			PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	window_inout_sel,		0x0);					//window inout selection by win0,win1
			PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	histogram_mode, 		0x0);					//histogram mode, use own side's histo
			//PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
			//PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
			PE_CEO_PE1_O20_Wr01(pe1_apl_ctrl_02,	apl_position,			0x0);	//0x0:PE1 input(Y/C),0x2:ocsc out(RGB)
			PE_CEO_PE1_O20_WrFL(pe1_dce_ctrl_00);
			PE_CEO_PE1_O20_WrFL(pe1_dce_ctrl_01);
			PE_CEO_PE1_O20_WrFL(pe1_apl_ctrl_02);
			/* cen block */
			PE_CEO_PE1_O20_RdFL(pe1_cen_ctrl_00);
			PE_CEO_PE1_O20_Wr01(pe1_cen_ctrl_00,	vsp_sel,		0x1);	//0:hsl,1:hsv
			PE_CEO_PE1_O20_WrFL(pe1_cen_ctrl_00);
			/****************/
			/* dse config */
			PE_CEO_PE1_O20_RdFL(pe1_dse_ctrl_00);
			if (hw_opt.external_chip ==0) //4k model
			{
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x1);
			}
			else //8k model
			{
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x0);
			}
			PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	window_mode_enable, 	0x1);	//window sync
			PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	window_inout_sel,		0x0);	//window inout selection by win0,win1
			//PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);	//from pe1 win2
			PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	window_acquire, 		0x1);	//window acquire on
			PE_CEO_PE1_O20_WrFL(pe1_dse_ctrl_00);

			/*temporally obc disable*/
			//PE_VSD_OBC_O_O20_QWr01(psp_ctrl02,	reg_psp_en,	0x0);
			//PE_VSD_OBC_F_O20_QWr01(psp_ctrl02,	reg_psp_en,	0x0);
			#if 1	/* F20_APB */
			do {
				UINT32 lut_data;

				if (pstParams->resume_mode == 1)	break;//if qsm,skip

				/* addr */
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_ia_ctrl_s.uaddr32,0xF0342738);
				for (i=0; i<32; i++)
				{
					PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_ia_data[i].uaddr32,0xF034273C);
				}
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_ia_ctrl_e.uaddr32,0xF0342738);
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_ctrl_08.uaddr32,0xF0342740);
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_chr_gain.uaddr32,0xF0342754);
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_chr_alpha.uaddr32,0xF0342758);
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut_ctrl_05.uaddr32,0xF0175C84);
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut0_ia_ctrl_s.uaddr32,0xF0175C88);
				for (i=0; i<32; i++)
				{
					PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut0_ia_data[i].uaddr32,0xF0175C8C);
				}
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut0_ia_ctrl_e.uaddr32,0xF0175C88);
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut_ctrl_00.uaddr32,0xF0175C70);
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_hue_sat_ctrl.uaddr32,0xF0175CE0);
				PE_CHPI_APB0_F20_QWr(fsw0.pe1_fsw_ctrl_01.uaddr32,0xF0342524);
				PE_CHPI_APB0_F20_QWr(fsw0.shp_fsw_ctrl_00.uaddr32,0xF0342300);
				PE_CHPI_APB0_F20_QWr(fsw0.shp_fsw_ctrl_01.uaddr32,0xF0342304);
				PE_CHPI_APB0_F20_QWr(fsw0.shp_fsw_ctrl_02.uaddr32,0xF0342308);
				PE_CHPI_APB0_F20_QWr(fsw0.vsd0_veri_vsp_0.uaddr32,0xF0175800);
				PE_CHPI_APB0_F20_QWr(fsw0.vsd0_veri_vsp_1.uaddr32,0xF0175804);
				PE_CHPI_APB0_F20_QWr(fsw0.vsd1_veri_vsp_0.uaddr32,0xF017BF00);
				PE_CHPI_APB0_F20_QWr(fsw0.vsd1_veri_vsp_1.uaddr32,0xF017BF04);

				/* init */
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_ia_ctrl_s.udata32,0x00001000);
				for (i=0; i<32; i++)
				{
					lut_data = ((dce_lut_data[i]<<16)&0x3ff0000)|(dce_lut_data[i]&0x3ff);
					PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_ia_data[i].udata32,lut_data);
				}
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_ia_ctrl_e.udata32,0x00008100);
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_ctrl_08.udata32,0x03FF03FF);
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_chr_gain.udata32,0x02000200);
				PE_CHPI_APB0_F20_QWr(dce0.pe1_dce_chr_alpha.udata32,0x02000200);
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut_ctrl_05.udata32,0x03FF03FF);
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut0_ia_ctrl_s.udata32,0x00001000);
				for (i=0; i<32; i++)
				{
					PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut0_ia_data[i].udata32,p_pre_dse_lut[i]);
				}
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut0_ia_ctrl_e.udata32,0x00008100);
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_llut_ctrl_00.udata32,0x00000001);
				PE_CHPI_APB0_F20_QWr(dtm0.dtm_hue_sat_ctrl.udata32,0xFF000011);
				PE_CHPI_APB0_F20_QWr(fsw0.pe1_fsw_ctrl_01.udata32,0x00000000);
				PE_CHPI_APB0_F20_QWr(fsw0.shp_fsw_ctrl_00.udata32,0x00000000);
				PE_CHPI_APB0_F20_QWr(fsw0.shp_fsw_ctrl_01.udata32,0x00000000);
				PE_CHPI_APB0_F20_QWr(fsw0.shp_fsw_ctrl_02.udata32,0x00000000);
				PE_CHPI_APB0_F20_QWr(fsw0.vsd0_veri_vsp_0.udata32,0x02000000);
				PE_CHPI_APB0_F20_QWr(fsw0.vsd0_veri_vsp_1.udata32,0x02008000);
				PE_CHPI_APB0_F20_QWr(fsw0.vsd1_veri_vsp_0.udata32,0x02000000);
				PE_CHPI_APB0_F20_QWr(fsw0.vsd1_veri_vsp_1.udata32,0x02008000);

				/* header */
				PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DCE0);
				PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DTM0);
				PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_FSW0);

				PE_PRINT_NOTI("[APB][DCM]done(resume:%d)\n",pstParams->resume_mode);
				PE_INF_HW_O20_BACKUP_CHPI0("[APB][DCM]done(resume:%d)",pstParams->resume_mode);
			} while(0);
			#endif
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_O20_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(DCM)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_dcm_hw_o20_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(DCM)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if(PE_KDRV_VER_O20)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(DCM)))
				{
					PE_DCM_HW_O20_DBG_PRINT("dynamic_contrast_en : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_CEO_PE1_O20_QWr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x0);
					}
				}
				else
				{
					PE_DCM_HW_O20_DBG_PRINT("dynamic_contrast_en : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_CEO_PE1_O20_QWr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);
					}
				}
			}
			else
			{
				PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
			}
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 is_yc,min_pos,max_pos;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		is_yc = (pstParams->domain==LX_PE_YC_DOMAIN)? 1:0;
		min_pos = pstParams->min_pos;
		max_pos = pstParams->max_pos;
		PE_DCM_HW_O20_DBG_PRINT("[win id:%d] domain:%d, min:%d, max:%d\n",\
			pstParams->win_id,pstParams->domain,pstParams->min_pos,pstParams->max_pos);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* dce config */
				PE_CEO_PE1_O20_RdFL(pe1_dce_ctrl_00);
				PE_CEO_PE1_O20_RdFL(pe1_dce_ctrl_01);
				PE_CEO_PE1_O20_RdFL(pe1_apl_ctrl_02);
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	hist_bin_mode,			0x0);					//32bin mode
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	window_acquire,			0x1);					//window acquire on
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	dce_domain_sel,			(is_yc==1)? 0x1:0x0);	//0:ktd,1:yc
				//PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);					//from pe1 win2
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	window_mode_enable,		0x1);					//window sync
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	window_inout_sel,		0x0);					//window inout selection by win0,win1
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	histogram_mode,			0x0);					//histogram mode, use own side's histo
				//PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
				//PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
				PE_CEO_PE1_O20_Wr01(pe1_apl_ctrl_02,	apl_position,			(is_yc==1)? 0x0:0x2);	//0x0:PE1 input(Y/C),0x2:ocsc out(RGB)
				PE_CEO_PE1_O20_WrFL(pe1_dce_ctrl_00);
				PE_CEO_PE1_O20_WrFL(pe1_dce_ctrl_01);
				PE_CEO_PE1_O20_WrFL(pe1_apl_ctrl_02);
				/* cen block */
				PE_CEO_PE1_O20_RdFL(pe1_cen_ctrl_00);
				PE_CEO_PE1_O20_Wr01(pe1_cen_ctrl_00,	vsp_sel,		0x1);	//0:hsl,1:hsv
				PE_CEO_PE1_O20_WrFL(pe1_cen_ctrl_00);
				/****************/
				/* dse config */
				PE_CEO_PE1_O20_RdFL(pe1_dse_ctrl_00);
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x1);
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	window_mode_enable,		0x1);	//window sync
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	window_inout_sel,		0x0);	//window inout selection by win0,win1
				//PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	win_selection,			0x0);	//from pe1 win2
				PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_00,	window_acquire,			0x1);	//window acquire on
				PE_CEO_PE1_O20_WrFL(pe1_dse_ctrl_00);
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
/**
 * get dce config
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DCE_CONF_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_GetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 domain=0, min_pos=0, max_pos=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_O20_RdFL(pe1_dce_ctrl_00);
				PE_CE_PE1_O20_RdFL(pe1_dce_ctrl_01);
				PE_CE_PE1_O20_Rd01(pe1_dce_ctrl_00,	dce_domain_sel,			domain);	//0:ktd,1:yc
				//PE_CE_PE1_O20_Rd01(pe1_dce_ctrl_01,	hist_bin_min_position,	min_pos);	//min position
				//PE_CE_PE1_O20_Rd01(pe1_dce_ctrl_01,	hist_bin_max_position,	max_pos);	//max position
				pstParams->domain = (domain)? LX_PE_YC_DOMAIN:LX_PE_KTD_DOMAIN;
				pstParams->min_pos = min_pos;
				pstParams->max_pos = max_pos;
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O20_RdFL(pe1_dce_ctrl_00);
				PE_CO_PE1_O20_RdFL(pe1_dce_ctrl_01);
				PE_CO_PE1_O20_Rd01(pe1_dce_ctrl_00,	dce_domain_sel,			domain);	//0:ktd,1:yc
				//PE_CO_PE1_O20_Rd01(pe1_dce_ctrl_01,	hist_bin_min_position,	min_pos);	//min position
				//PE_CO_PE1_O20_Rd01(pe1_dce_ctrl_01,	hist_bin_max_position,	max_pos);	//max position
				pstParams->domain = (domain)? LX_PE_YC_DOMAIN:LX_PE_KTD_DOMAIN;
				pstParams->min_pos = min_pos;
				pstParams->max_pos = max_pos;
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	#ifdef PE_DCM_HW_O20_SET_DCE_LUT_ON_SYNC
	UINT32 cur_dce_lut_num;
	PE_DCM_HW_O20_SETTINGS_T *pInfo=&_g_pe_dcm_hw_o20_info;
	#else
	UINT32 count=0;
	UINT32 lut_data=0;
	//int i;
	#endif
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_O20_CHECK_CODE((pstParams->size>PE_DCM_HW_O20_LUT_STEP), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pstParams->size);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_DCM_HW_O20_SET_DCE_LUT_ON_SYNC
				if (pstParams->size<PE_DCM_HW_O20_LUT_STEP)	break;
				cur_dce_lut_num = (!pInfo->dce_lut_num)? 1:0;
				if (cur_dce_lut_num==1)
					memcpy(pInfo->dce_lut1, pstParams->data, sizeof(UINT32)*PE_DCM_HW_O20_LUT_STEP);
				else
					memcpy(pInfo->dce_lut0, pstParams->data, sizeof(UINT32)*PE_DCM_HW_O20_LUT_STEP);
				pInfo->dce_lut_num = cur_dce_lut_num;
				if (pInfo->dce_lut_cnt<PE_DCM_HW_O20_DCE_CNT_NUM)
					pInfo->dce_lut_cnt++;
				else
					pInfo->dce_lut_cnt=0;
				#else
				PE_CEO_PE1_O20_RdFL(pe1_dce_ia_ctrl);
				PE_CEO_PE1_O20_RdFL(pe1_dce_ia_data);
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				PE_DCM_HW_O20_DBG_PRINT("\n update dce lut\n");
				PE_DCM_HW_O20_DBG_PRINT("\n   [ i]    x,    y\n");
				for(count=0;count<(pstParams->size);count++)
				{
					lut_data = pstParams->data[count];
					#if 0
					if (count<(PE_DCM_HW_O20_LUT_MAX-1))
					{
						PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(lut_data,0,10));	//y data
						PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(lut_data,16,10));//x data
						PE_CEO_PE1_O20_WrFL(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_O20_LUT_MAX-1)
					{
						PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_08,hif_dyc_wdata_y_32nd,GET_BITS(lut_data,0,10));//y data
						PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_08,hif_dyc_wdata_x_32nd,GET_BITS(lut_data,16,10));//x data
						PE_CEO_PE1_O20_WrFL(pe1_dce_ctrl_08);
					}
					#else
					PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(lut_data,0,10));//y data
					PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(lut_data,16,10));//x data
					PE_CEO_PE1_O20_WrFL(pe1_dce_ia_data);
					PE_DCM_HW_O20_DBG_PRINT("   [%02d] %4d, %4d\n", count, GET_BITS(lut_data,16,10), GET_BITS(lut_data,0,10));
					#endif
				}
				/* 20160601, read register on addr0 to avoid white flash */
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				PE_CEO_PE1_O20_RdFL(pe1_dce_ia_data);
				
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				#endif
				#if 1	/* F20_APB */
				do {
					for(count=0;count<(pstParams->size);count++)
					{
						lut_data = pstParams->data[count];
						PE_CHPI_APB0_F20_Wr(dce0.pe1_dce_ia_data[count].hif_dyc_wdata_y,GET_BITS(lut_data,0,10));//y data
						PE_CHPI_APB0_F20_Wr(dce0.pe1_dce_ia_data[count].hif_dyc_wdata_x,GET_BITS(lut_data,16,10));//x data
						PE_CHPI_APB0_F20_WrFL(dce0.pe1_dce_ia_data[count].udata32);
					}
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DCE0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_O20_CHECK_CODE((pstParams->size>PE_DCM_HW_O20_LUT_STEP), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_O20_RdFL(pe1_dce_ia_ctrl);
				PE_CE_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_CE_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_CE_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CE_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_O20_LUT_MAX-1))
					{
						PE_CE_PE1_O20_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CE_PE1_O20_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_O20_LUT_MAX-1)
					{
						PE_CE_PE1_O20_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CE_PE1_O20_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_CE_PE1_O20_RdFL(pe1_dce_ia_data);
					pstParams->data[count] = PE_CE_PE1_O20_Rd(pe1_dce_ia_data);
					#endif
				}
				PE_CE_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CE_PE1_O20_WrFL(pe1_dce_ia_ctrl);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O20_RdFL(pe1_dce_ia_ctrl);
				PE_CO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_CO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_CO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_O20_LUT_MAX-1))
					{
						PE_CO_PE1_O20_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CO_PE1_O20_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_O20_LUT_MAX-1)
					{
						PE_CO_PE1_O20_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CO_PE1_O20_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_CO_PE1_O20_RdFL(pe1_dce_ia_data);
					pstParams->data[count] = PE_CO_PE1_O20_Rd(pe1_dce_ia_data);
					#endif
				}
				PE_CO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
/**
 * set dse lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_SetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 count=0;
	UINT32 lut_data=0;
	int i;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_O20_CHECK_CODE((pstParams->size>PE_DCM_HW_O20_LUT_STEP), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pstParams->size);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CEO_PE1_O20_RdFL(pe1_dse_ia_ctrl);
				PE_CEO_PE1_O20_RdFL(pe1_dse_ia_data);
				PE_CEO_PE1_O20_RdFL(pe1_dce_ctrl_08);
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_CEO_PE1_O20_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					lut_data = pstParams->data[count];
					#if 0
					if (count<(PE_DCM_HW_O20_LUT_MAX-1))
					{
						PE_CEO_PE1_O20_Wr01(pe1_dse_ia_data,hif_dse_wdata_y,GET_BITS(lut_data,0,10));	//y data
						PE_CEO_PE1_O20_Wr01(pe1_dse_ia_data,hif_dse_wdata_x,GET_BITS(lut_data,16,10));//x data
						PE_CEO_PE1_O20_WrFL(pe1_dse_ia_data);
					}
					else	//count == (PE_DCM_HW_O20_LUT_MAX-1)
					{
						PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_02,hif_dse_wdata_y_32nd,GET_BITS(lut_data,0,10));//y data
						PE_CEO_PE1_O20_Wr01(pe1_dse_ctrl_02,hif_dse_wdata_x_32nd,GET_BITS(lut_data,16,10));//x data
						PE_CEO_PE1_O20_WrFL(pe1_dse_ctrl_02);
					}
					#else
					PE_CEO_PE1_O20_Wr01(pe1_dse_ia_data,hif_dse_wdata_y,GET_BITS(lut_data,0,10));	//y data
					PE_CEO_PE1_O20_Wr01(pe1_dse_ia_data,hif_dse_wdata_x,GET_BITS(lut_data,16,10));//x data
					PE_CEO_PE1_O20_WrFL(pe1_dse_ia_data);
					#endif
				}
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_CEO_PE1_O20_WrFL(pe1_dse_ia_ctrl);
				memcpy(_g_dcm_hw_o20_pre_dse_lut, pstParams->data, sizeof(UINT32)*(pstParams->size));
				if(_g_dcm_hw_o20_trace)
				{
					PE_DCM_HW_O20_DBG_PRINT("\n update dse lut\n");
					PE_DCM_HW_O20_DBG_PRINT("\n   [ i]    x,    y\n");
					for (i=0;i<(PE_DCM_HW_O20_LUT_MAX-1);i++)
					{
						PE_DCM_HW_O20_DBG_PRINT("   [%02d] %4d, %4d\n", \
							i, (_g_dcm_hw_o20_pre_dse_lut[i]>>16)&0x3ff, _g_dcm_hw_o20_pre_dse_lut[i]&0x3ff);
					}
				}
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
/**
 * get dse lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DSE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_GetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_O20_CHECK_CODE((pstParams->size>PE_DCM_HW_O20_LUT_STEP), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pstParams->size);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_O20_RdFL(pe1_dse_ia_ctrl);
				PE_CE_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CE_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CE_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CE_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_CE_PE1_O20_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_O20_LUT_MAX-1))
					{
						PE_CE_PE1_O20_RdFL(pe1_dse_ia_data);
						pstParams->data[count] = PE_CE_PE1_O20_Rd(pe1_dse_ia_data);
					}
					else	//count == (PE_DCM_HW_O20_LUT_MAX-1)
					{
						PE_CE_PE1_O20_RdFL(pe1_dse_ctrl_02);
						pstParams->data[count] = PE_CE_PE1_O20_Rd(pe1_dse_ctrl_02);
					}
					#else
					PE_CE_PE1_O20_RdFL(pe1_dse_ia_data);
					pstParams->data[count] = PE_CE_PE1_O20_Rd(pe1_dse_ia_data);
					#endif
				}
				PE_CE_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CE_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_CE_PE1_O20_WrFL(pe1_dse_ia_ctrl);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O20_RdFL(pe1_dse_ia_ctrl);
				PE_CO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_CO_PE1_O20_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_O20_LUT_MAX-1))
					{
						PE_CO_PE1_O20_RdFL(pe1_dse_ia_data);
						pstParams->data[count] = PE_CO_PE1_O20_Rd(pe1_dse_ia_data);
					}
					else	//count == (PE_DCM_HW_O20_LUT_MAX-1)
					{
						PE_CO_PE1_O20_RdFL(pe1_dse_ctrl_02);
						pstParams->data[count] = PE_CO_PE1_O20_Rd(pe1_dse_ctrl_02);
					}
					#else
					PE_CO_PE1_O20_RdFL(pe1_dse_ia_data);
					pstParams->data[count] = PE_CO_PE1_O20_Rd(pe1_dse_ia_data);
					#endif
				}
				PE_CO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CO_PE1_O20_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_CO_PE1_O20_WrFL(pe1_dse_ia_ctrl);
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set smooth contrast
 * - use input struct LX_PE_DCM_DCE_SMOOTH1_T for O20A
 * - use input struct LX_PE_DCM_DCE_SMOOTH0_T for O20A
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_SetDceSmoothCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * get smooth contrast
 * - use input struct LX_PE_DCM_DCE_SMOOTH1_T for O20A
 * - use input struct LX_PE_DCM_DCE_SMOOTH0_T for O20A
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_GetDceSmoothCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set blur_v_gain 0xf(protection) for pattern
 *
 * @param   *pCfg [in] PE_TSK_O20_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_SetBlurGain(PE_TSK_O20_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	static UINT32 count = 0;
	static UINT32 sat_th = PE_DCM_HW_O20_SAT_STATUS_DTV_TH;		//pre threshold
	static LX_PE_SRC_TYPE pre_src_type = LX_PE_SRC_DTV;
	static UINT32 pre_sat_st = 0;	//pre status
	UINT32 blur_gain,is_atv_case,high_val,mid_val,low_val;
	PE_INF_O20_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_DCM_HW_O20_SETTINGS_T *pInfo=&_g_pe_dcm_hw_o20_info;
	do{
		CHECK_KNULL(pCfg);
		is_atv_case = (disp0_info->src_type==LX_PE_SRC_ATV || \
			disp0_info->src_type==LX_PE_SRC_CVBS || \
			disp0_info->src_type==LX_PE_SRC_SCART)? 1:0;
		if(pre_src_type!=disp0_info->src_type)	// init saturation status threshold on input change
		{
			sat_th = (is_atv_case)? PE_DCM_HW_O20_SAT_STATUS_ATV_HIGH_TH:PE_DCM_HW_O20_SAT_STATUS_DTV_HIGH_TH;
			pre_src_type=disp0_info->src_type;
			blur_gain = (ctrl0_info->sat_status>sat_th)? PE_DCM_HW_O20_BLUR_ORG_VAL:pInfo->cur_blur_gain;
			pre_sat_st = ctrl0_info->sat_status;
		}
		else	// apply hysterisis : increase:use high th, decrease:use low th
		{
			if(pre_sat_st!=ctrl0_info->sat_status)
			{
				high_val = PE_DCM_HW_O20_BLUR_ORG_VAL;
				mid_val = pInfo->pre_blur_gain;
				low_val = pInfo->cur_blur_gain;
				if(is_atv_case)
				{
					if(pre_sat_st<ctrl0_info->sat_status)	//increase
					{
						/* if higher than hi_th, use high val, else mid_val */
						blur_gain = (ctrl0_info->sat_status>PE_DCM_HW_O20_SAT_STATUS_ATV_HIGH_TH)? high_val:mid_val;
					}
					else	//decrease
					{
						/* if lower than lo_th, use low val, else mid_val */
						blur_gain = (ctrl0_info->sat_status>PE_DCM_HW_O20_SAT_STATUS_ATV_LOW_TH)? mid_val:low_val;
					}
				}
				else
				{
					if(pre_sat_st<ctrl0_info->sat_status)	//increase
					{
						/* if higher than hi_th, use high val, else mid_val */
						blur_gain = (ctrl0_info->sat_status>PE_DCM_HW_O20_SAT_STATUS_DTV_HIGH_TH)? high_val:mid_val;
					}
					else	//decrease
					{
						/* if lower than lo_th, use low val, else mid_val */
						blur_gain = (ctrl0_info->sat_status>PE_DCM_HW_O20_SAT_STATUS_DTV_LOW_TH)? mid_val:low_val;
					}
				}
				/*PE_DCM_HW_O20_DBG_PRINT("[inf ] sat:%d -> %d, blur_gain:%d -> %d\n",\
					pre_sat_st,ctrl0_info->sat_status,pInfo->pre_blur_gain,blur_gain);*/
				pre_sat_st = ctrl0_info->sat_status;
			}
			else
			{
				blur_gain = pInfo->pre_blur_gain;
			}
		}
		/* if it's a pattern, turn off blur gain(set 0xf). */
		#if 0
		if(pInfo->pre_blur_gain!=blur_gain)
		{
			PE_DCM_HW_O20_DBG_PRINT("[set ] src:%d(atv_case:%d), sat:%d(th:%d), cur_gain:%d, blur_gain:%d -> %d\n",\
				disp0_info->src_type,is_atv_case,ctrl0_info->sat_status,sat_th,\
				pInfo->cur_blur_gain,pInfo->pre_blur_gain,blur_gain);
			if(PE_KDRV_VER_O20)
			{
				PE_CEO_PE1_O20_QWr01(pe1_dce_ctrl_01,	blur_v_gain, GET_BITS(blur_gain,0,4));
			}
			pInfo->pre_blur_gain=blur_gain;
		}
		#endif
		if(_g_dcm_hw_o20_trace)
		{
			if(count>PE_PRINT_COUNT_NUM)
			{
				PE_DCM_HW_O20_DBG_PRINT("[info] src:%d(atv_case:%d), sat:%d(th:%d), cur_gain:%d, blur_gain:%d\n",\
					disp0_info->src_type,is_atv_case,ctrl0_info->sat_status,sat_th,pInfo->pre_blur_gain,blur_gain);
				count=0;
			}
			count++;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set dce blending
 *
 * @param   *pstParams [in] LX_PE_DCM_BLENDING_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_SetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 color_out_gain;
	UINT32 region_sel;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		color_out_gain = (pstParams->color_out_gain==0)? \
			0x1:pstParams->color_out_gain;
		region_sel = pstParams->region_sel;
		PE_DCM_HW_O20_DBG_PRINT("[wid:%d] set: color_out_gain:%d, color_sel:0x%08x\n"\
			"color_region_en: %d\n"\
			"grad_gain(y,cb,cr):%d,%d,%d\n"\
			"y_range(min,max):%d,%d, cb_range:%d,%d, cr_range:%d,%d\n",\
			pstParams->win_id,color_out_gain,region_sel,\
			pstParams->color_region_en, pstParams->y_grad_gain, \
			pstParams->cb_grad_gain, pstParams->cr_grad_gain,\
			pstParams->y_range_min, pstParams->y_range_max,\
			pstParams->cb_range_min, pstParams->cb_range_max,\
			pstParams->cr_range_min, pstParams->cr_range_max);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CEO_PE1_O20_RdFL(pe1_dce_ctrl_00);
				PE_CEO_PE1_O20_RdFL(pe1_dce_ctrl_01);
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region0_sel,	GET_BITS(region_sel,0,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region1_sel,	GET_BITS(region_sel,1,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region2_sel,	GET_BITS(region_sel,2,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region3_sel,	GET_BITS(region_sel,3,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region4_sel,	GET_BITS(region_sel,4,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region5_sel,	GET_BITS(region_sel,5,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region6_sel,	GET_BITS(region_sel,6,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region7_sel,	GET_BITS(region_sel,7,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region8_sel,	GET_BITS(region_sel,8,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region9_sel,	GET_BITS(region_sel,9,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region10_sel,	GET_BITS(region_sel,10,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region11_sel,	GET_BITS(region_sel,11,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region12_sel,	GET_BITS(region_sel,12,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region13_sel,	GET_BITS(region_sel,13,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region14_sel,	GET_BITS(region_sel,14,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_00,	color_region15_sel,	GET_BITS(region_sel,15,1));
				PE_CEO_PE1_O20_Wr01(pe1_dce_ctrl_01,	color_region_gain,	GET_BITS(color_out_gain,0,8));
				PE_CEO_PE1_O20_WrFL(pe1_dce_ctrl_00);
				PE_CEO_PE1_O20_WrFL(pe1_dce_ctrl_01);
				PE_CEO_PE1_O20_QWr04(pe1_dce_ctrl_02,	color_region_en,	GET_BITS(pstParams->color_region_en,0,1),\
														y_grad_gain,		GET_BITS(pstParams->y_grad_gain,0,2),\
														cb_grad_gain,		GET_BITS(pstParams->cb_grad_gain,0,2),\
														cr_grad_gain,		GET_BITS(pstParams->cr_grad_gain,0,2));
				PE_CEO_PE1_O20_QWr02(pe1_dce_ctrl_03,	y_range_min,		GET_BITS(pstParams->y_range_min,0,10),\
														y_range_max,		GET_BITS(pstParams->y_range_max,0,10));
				PE_CEO_PE1_O20_QWr02(pe1_dce_ctrl_04,	cb_range_min,		GET_BITS(pstParams->cb_range_min,0,10),\
														cb_range_max,		GET_BITS(pstParams->cb_range_max,0,10));
				PE_CEO_PE1_O20_QWr02(pe1_dce_ctrl_05,	cr_range_min,		GET_BITS(pstParams->cr_range_min,0,10),\
														cr_range_max,		GET_BITS(pstParams->cr_range_max,0,10));
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}
/**
 * get dce blending
 *
 * @param   *pstParams [in/out] LX_PE_DCM_BLENDING_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_GetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 r_data;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_O20_RdFL(pe1_dce_ctrl_00);
				PE_CE_PE1_O20_RdFL(pe1_dce_ctrl_01);
				PE_CE_PE1_O20_Rd01(pe1_dce_ctrl_01,	color_region_gain,	pstParams->color_out_gain);
				r_data = PE_CE_PE1_O20_Rd(pe1_dce_ctrl_00);
				pstParams->region_sel = GET_BITS(r_data,8,16);	//[23:8]
				PE_CE_PE1_O20_QRd04(pe1_dce_ctrl_02,	color_region_en,	pstParams->color_region_en,\
														y_grad_gain,		pstParams->y_grad_gain,\
														cb_grad_gain,		pstParams->cb_grad_gain,\
														cr_grad_gain,		pstParams->cr_grad_gain);
				PE_CE_PE1_O20_QRd02(pe1_dce_ctrl_03,	y_range_min,		pstParams->y_range_min,\
														y_range_max,		pstParams->y_range_max);
				PE_CE_PE1_O20_QRd02(pe1_dce_ctrl_04,	cb_range_min,		pstParams->cb_range_min,\
														cb_range_max,		pstParams->cb_range_max);
				PE_CE_PE1_O20_QRd02(pe1_dce_ctrl_05,	cr_range_min,		pstParams->cr_range_min,\
														cr_range_max,		pstParams->cr_range_max);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O20_RdFL(pe1_dce_ctrl_00);
				PE_CO_PE1_O20_RdFL(pe1_dce_ctrl_01);
				PE_CO_PE1_O20_Rd01(pe1_dce_ctrl_01,	color_region_gain,	pstParams->color_out_gain);
				r_data = PE_CO_PE1_O20_Rd(pe1_dce_ctrl_00);
				pstParams->region_sel = GET_BITS(r_data,8,16);	//[23:8]
				PE_CO_PE1_O20_QRd04(pe1_dce_ctrl_02,	color_region_en,	pstParams->color_region_en,\
														y_grad_gain,		pstParams->y_grad_gain,\
														cb_grad_gain,		pstParams->cb_grad_gain,\
														cr_grad_gain,		pstParams->cr_grad_gain);
				PE_CO_PE1_O20_QRd02(pe1_dce_ctrl_03,	y_range_min,		pstParams->y_range_min,\
														y_range_max,		pstParams->y_range_max);
				PE_CO_PE1_O20_QRd02(pe1_dce_ctrl_04,	cb_range_min,		pstParams->cb_range_min,\
														cb_range_max,		pstParams->cb_range_max);
				PE_CO_PE1_O20_QRd02(pe1_dce_ctrl_05,	cr_range_min,		pstParams->cr_range_min,\
														cr_range_max,		pstParams->cr_range_max);
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
		}
		PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: color_out_gain:%d, color_sel:0x%08x\n"\
			"color_region_en: %d\n"\
			"grad_gain(y,cb,cr):%d,%d,%d\n"\
			"y_range(min,max):%d,%d, cb_range:%d,%d, cr_range:%d,%d\n",\
			pstParams->win_id,pstParams->color_out_gain,pstParams->region_sel,\
			pstParams->color_region_en, pstParams->y_grad_gain, \
			pstParams->cb_grad_gain, pstParams->cr_grad_gain,\
			pstParams->y_range_min, pstParams->y_range_max,\
			pstParams->cb_range_min, pstParams->cb_range_max,\
			pstParams->cr_range_min, pstParams->cr_range_max);
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 hdr_effect;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_HW_O20_DBG_PRINT("[wid:%d] set: dc_md,byps,sc_cnt,pic_mode:%d,%d,%d,0x%08x\n",\
			pstParams->win_id, pstParams->dc_mode, \
			pstParams->dc_bypass, pstParams->dc_sc_cnt, pstParams->picture_mode);

		//m16p, DRC always on
		hdr_effect = 0x2; //normal ipcture mode
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CE_PE1_O20_RdFL(pe1_fsw_ctrl_01);
				PE_CE_PE1_O20_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_mode,  GET_BITS(pstParams->dc_mode,0,2));
				PE_CE_PE1_O20_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_bypass,GET_BITS(pstParams->dc_bypass,0,1));
				PE_CE_PE1_O20_Wr01(pe1_fsw_ctrl_01,reg_drc_dc_sc_cnt,GET_BITS(pstParams->dc_sc_cnt,0,4));
				PE_CE_PE1_O20_Wr01(pe1_fsw_ctrl_01,reg_hdr_effect,       GET_BITS(hdr_effect,0,2));
				PE_CE_PE1_O20_WrFL(pe1_fsw_ctrl_01);
				ret = PE_FWI_O20_SetPicMode(pstParams->picture_mode);
				PE_DCM_HW_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_O20_SetPicMode() error.\n", __F__, __L__);
				#if 1	/* F20_APB */
				do {
					PE_CHPI_APB0_F20_Wr(fsw0.pe1_fsw_ctrl_01.reg_drc_dc_mode,GET_BITS(pstParams->dc_mode,0,2));
					PE_CHPI_APB0_F20_Wr(fsw0.pe1_fsw_ctrl_01.reg_drc_dc_bypass,GET_BITS(pstParams->dc_bypass,0,1));
					PE_CHPI_APB0_F20_Wr(fsw0.pe1_fsw_ctrl_01.reg_drc_dc_sc_cnt,GET_BITS(pstParams->dc_sc_cnt,0,4));
					PE_CHPI_APB0_F20_Wr(fsw0.pe1_fsw_ctrl_01.reg_hdr_effect,GET_BITS(hdr_effect,0,2));
					PE_CHPI_APB0_F20_WrFL(fsw0.pe1_fsw_ctrl_01.udata32);
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_FSW0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_GetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_O20_RdFL(pe1_fsw_ctrl_01);
				PE_CE_PE1_O20_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_mode,  pstParams->dc_mode);
				PE_CE_PE1_O20_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_bypass,pstParams->dc_bypass);
				PE_CE_PE1_O20_Rd01(pe1_fsw_ctrl_01,reg_drc_dc_sc_cnt,pstParams->dc_sc_cnt);
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
		}
		PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: dc_md,byps,sc_cnt:%d,%d,%d\n",\
			pstParams->win_id, pstParams->dc_mode, \
			pstParams->dc_bypass, pstParams->dc_sc_cnt);
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_DownloadDrcDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_drc_data = p_phys_db->drc_lut.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_data);
		if (PE_KDRV_VER_O20)
		{
			/* header */
			sec_typ = PE_DDR_O20_SEC_DRC_LUT;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O20_DRC_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O20_DRC_LUT_SIZE;
			p_phys_db->drc_lut.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_lut.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_lut.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_O20_DRC_LUT_ITEM_NUM * PE_DDR_O20_DRC_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O20_HEADER_T);
			/* wr ddr */
				memcpy((UINT32 *)p_drc_data, pe_drc_lut_m16p, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetDrcCurv(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_DCM_DRC_CUV_T *pp=(LX_PE_DCM_DRC_CUV_T *)pstParams;
			//PE_CHECK_WINID(pp->win_id);
			if (_g_dcm_hw_o20_trace)
			{
				PE_DCM_HW_O20_DBG_PRINT( \
				"DRC table:\n"\
				"global apl:%d,%d,%d,%d\n"\
				"local	apl:%d,%d,%d,%d,%d,%d\n"\
				"w_gain:%d, b_gain:%d\n",\
				pp->global_apl[0],pp->global_apl[1],pp->global_apl[2],pp->global_apl[3],
				pp->local_apl[0],pp->local_apl[1],pp->local_apl[2],pp->local_apl[3],pp->local_apl[4],pp->local_apl[5],
				pp->cuv_gain_w,pp->cuv_gain_b);
				PE_DCM_HW_O20_DBG_PRINT( \
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
			ret = PE_DCM_HW_O20_DownloadDrcCurvDb((void *)pp);
			PE_DCM_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DCM_HW_O20_DownloadDrcCurvDb() error.\n",__F__,__L__);
			ret = PE_DCM_HW_F20_DownloadDrcCurvDb((void *)pp);
			PE_DCM_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DCM_HW_F20_DownloadDrcCurvDb() error.\n",__F__,__L__);
 		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetDrcParam(void *pstParams)
{
	int ret = RET_OK;
	static UINT32 update_cnt=0;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_DCM_DRC_CONT_T *pp=(LX_PE_DCM_DRC_CONT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_dcm_hw_o20_trace)
			{
				PE_DCM_HW_O20_DBG_PRINT( \
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
				PE_SHP_O20_QWr04(shp_fsw_ctrl_00, 	reg_pre_norm, GET_BITS(pp->pre_norm,0,8),\
													reg_cur_norm, GET_BITS(pp->cur_norm,0,8),\
													reg_pre_sc  , GET_BITS(pp->pre_sc,0,8),\
													drc_apb_write_cont, GET_BITS(update_cnt,0,2));
				PE_SHP_O20_QWr04(shp_fsw_ctrl_01, 	reg_cur_sc 	, GET_BITS(pp->cur_sc,0,8),\
													reg_ui_gain_w,GET_BITS(pp->ui_gain_w,0,8),\
													reg_ui_gain_b,GET_BITS(pp->ui_gain_b,0,8),\
													reg_vy_mode , GET_BITS(pp->vy_mode,0,8));
				#if 1	/* F20_APB */
				do {
					PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_00.reg_pre_norm,GET_BITS(pp->pre_norm,0,8));
					PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_00.reg_cur_norm,GET_BITS(pp->cur_norm,0,8));
					PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_00.reg_pre_sc,GET_BITS(pp->pre_sc,0,8));
					PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_00.drc_apb_write_cont,GET_BITS(update_cnt,0,2));
					PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_01.reg_cur_sc,GET_BITS(pp->cur_sc,0,8));
					PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_01.reg_ui_gain_w,GET_BITS(pp->ui_gain_w,0,8));
					PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_01.reg_ui_gain_b,GET_BITS(pp->ui_gain_b,0,8));
					PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_01.reg_vy_mode,GET_BITS(pp->vy_mode,0,8));
					PE_CHPI_APB0_F20_WrFL(fsw0.shp_fsw_ctrl_00.udata32);
					PE_CHPI_APB0_F20_WrFL(fsw0.shp_fsw_ctrl_01.udata32);
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_FSW0);
				} while(0);
				#endif
			}
 		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_GetDrcParam(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_DCM_DRC_CONT_T *pp=(LX_PE_DCM_DRC_CONT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O20_QRd03(shp_fsw_ctrl_00, 	reg_pre_norm, pp->pre_norm,\
													reg_cur_norm, pp->cur_norm,\
													reg_pre_sc  , pp->pre_sc);
				PE_SHP_O20_QRd04(shp_fsw_ctrl_01, 	reg_cur_sc 	, pp->cur_sc,\
													reg_ui_gain_w,pp->ui_gain_w,\
													reg_ui_gain_b,pp->ui_gain_b,\
													reg_vy_mode , pp->vy_mode);
			}
			if (_g_dcm_hw_o20_trace)
			{
				PE_DCM_HW_O20_DBG_PRINT( \
				"DRC table:\n"\
				"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
				"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n",\
				pp->pre_norm,pp->cur_norm,pp->pre_sc,pp->cur_sc,
				pp->ui_gain_w,pp->ui_gain_b,pp->vy_mode);
			}
 		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_DownloadDrcCurvDbInit(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_drc_cuv = p_phys_db->drc_cuv.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_cuv);
		if (PE_KDRV_VER_O20)
		{
			/* header */
			sec_typ = PE_DDR_O20_SEC_DRC_CURV;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O20_DRC_CURV_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DRC_O20_FW_LUT_SIZE;
			p_phys_db->drc_cuv.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_cuv.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_cuv.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_cuv.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_O20_DRC_CURV_ITEM_NUM * PE_DRC_O20_FW_LUT_SIZE * sizeof(SINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O20_HEADER_T);
			/* wr ddr */
			memcpy((UINT32 *)p_drc_cuv, pe_drc_lut_init, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x, size:%d)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->top_h.sec_size[sec_typ]);
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_DownloadDrcCurvDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size, sec_typ;
	UINT32 base;
	UINT32 *pp = NULL;
	static UINT32 update_cnt=0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->drc_cuv.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_DRC_CURV;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = PE_DDR_O20_DRC_CURV_ITEM_NUM*PE_DDR_O20_DRC_CURV_SIZE*sizeof(UINT32);
			pp = (UINT32 *)pstParams;
			memcpy((void *)p_db_data, pstParams, size);
			wmb();
			if(update_cnt == 0x3)
				update_cnt = 0x0;
			else
				update_cnt+=1;
			PE_SHP_O20_QWr01(shp_fsw_ctrl_00, drc_write_cont,GET_BITS(update_cnt,0,2));
			PE_DCM_HW_O20_DBG_PRINT("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], update_cnt);
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}


/**
 * set dse ctrl
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_SetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	//UINT32 color_out_gain;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_DCM_DSE_CTRL3_T *pp=(LX_PE_DCM_DSE_CTRL3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_DCM_HW_O20_DBG_PRINT("[wid:%d] set: chroma_gain_en:%d\n"\
				"dce_chr_gain1:%d,dce_chr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
				"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
				pp->win_id,	pp->chroma_gain_en, \
				pp->chroma_chr_gain1,pp->chroma_chr_gain2,pp->chroma_chr_alpha1,pp->chroma_chr_alpha2,\
				pp->dtm_hue_gain, pp->dtm_sat_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CEO_PE1_O20_QWr03(pe1_dce_chr_gain,		chroma_gain_enable, GET_BITS(pp->chroma_gain_en,0,1),\
															dce_cb_gain1,		GET_BITS(pp->chroma_chr_gain1,0,10),\
															dce_cb_gain2,		GET_BITS(pp->chroma_chr_gain2,0,10));
				PE_CEO_PE1_O20_QWr02(pe1_dce_chr_alpha,		dce_chr_alpha1,		GET_BITS(pp->chroma_chr_alpha1,0,10),\
															dce_chr_alpha2,		GET_BITS(pp->chroma_chr_alpha2,0,10));
				PE_VSD_DTM_O20_QWr02(dtm_hue_sat_ctrl,		reg_sat_prsv_ratio,	GET_BITS(pp->dtm_sat_gain,0,8),\
															reg_hue_prsv_ratio, GET_BITS(pp->dtm_hue_gain,0,8));
				#if 1	/* F20_APB */
				do {
					PE_CHPI_APB0_F20_Wr(dce0.pe1_dce_chr_gain.chroma_gain_enable,GET_BITS(pp->chroma_gain_en,0,1));
					PE_CHPI_APB0_F20_Wr(dce0.pe1_dce_chr_gain.dce_cb_gain1,GET_BITS(pp->chroma_chr_gain1,0,10));
					PE_CHPI_APB0_F20_Wr(dce0.pe1_dce_chr_gain.dce_cb_gain2,GET_BITS(pp->chroma_chr_gain2,0,10));
					PE_CHPI_APB0_F20_Wr(dce0.pe1_dce_chr_alpha.dce_chr_alpha1,GET_BITS(pp->chroma_chr_alpha1,0,10));
					PE_CHPI_APB0_F20_Wr(dce0.pe1_dce_chr_alpha.dce_chr_alpha2,GET_BITS(pp->chroma_chr_alpha2,0,10));
					PE_CHPI_APB0_F20_Wr(dtm0.dtm_hue_sat_ctrl.reg_sat_prsv_ratio,GET_BITS(pp->dtm_sat_gain,0,8));
					PE_CHPI_APB0_F20_Wr(dtm0.dtm_hue_sat_ctrl.reg_hue_prsv_ratio,GET_BITS(pp->dtm_hue_gain,0,8));
					PE_CHPI_APB0_F20_WrFL(dce0.pe1_dce_chr_gain.udata32);
					PE_CHPI_APB0_F20_WrFL(dce0.pe1_dce_chr_alpha.udata32);
					PE_CHPI_APB0_F20_WrFL(dtm0.dtm_hue_sat_ctrl.udata32);
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DCE0);
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DTM0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_GetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_DCM_DSE_CTRL2_T *pp=(LX_PE_DCM_DSE_CTRL2_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CE_PE1_O20_RdFL(pe1_dse_ctrl_00);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region0_sel,	pp->region_onoff[0]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region1_sel,	pp->region_onoff[1]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region2_sel,	pp->region_onoff[2]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region3_sel,	pp->region_onoff[3]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region4_sel,	pp->region_onoff[4]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region5_sel,	pp->region_onoff[5]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region6_sel,	pp->region_onoff[6]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region7_sel,	pp->region_onoff[7]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region8_sel,	pp->region_onoff[8]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region9_sel,	pp->region_onoff[9]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region10_sel,	pp->region_onoff[10]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region11_sel,	pp->region_onoff[11]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region12_sel,	pp->region_onoff[12]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region13_sel,	pp->region_onoff[13]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region14_sel,	pp->region_onoff[14]);
				PE_CE_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region15_sel,	pp->region_onoff[15]);
				PE_CE_PE1_O20_RdFL(pe1_dse_ctrl_00);
				
				PE_CE_PE1_O20_QRd03(pe1_dse_ctrl_01,		reg_dse_cr_mode_sel,pp->saturation_cr_mode,\
															reg_yh_cr_en,		pp->saturation_cr_mode,\
															color_region_gain,	pp->saturation_region_gain);
				PE_CE_PE1_O20_QRd02(pe_dse_y_region_pt0,	reg_y_region_pt0_y,	pp->dse_y_y[0],\
															reg_y_region_pt0_x,	pp->dse_y_x[0]);
				PE_CE_PE1_O20_QRd02(pe_dse_y_region_pt1,	reg_y_region_pt1_y,	pp->dse_y_y[1],\
															reg_y_region_pt1_x,	pp->dse_y_x[1]);
				PE_CE_PE1_O20_QRd02(pe_dse_y_region_pt2,	reg_y_region_pt2_y,	pp->dse_y_y[2],\
															reg_y_region_pt2_x,	pp->dse_y_x[2]);
				PE_CE_PE1_O20_QRd02(pe_dse_y_region_pt3,	reg_y_region_pt3_y,	pp->dse_y_y[3],\
															reg_y_region_pt3_x,	pp->dse_y_x[3]);
				PE_CE_PE1_O20_QRd02(pe_dse_y_region_pt4,	reg_y_region_pt4_y,	pp->dse_y_y[4],\
															reg_y_region_pt4_x,	pp->dse_y_x[4]);
				PE_CE_PE1_O20_QRd02(pe_dse_y_region_pt5,	reg_y_region_pt5_y,	pp->dse_y_y[5],\
															reg_y_region_pt5_x,	pp->dse_y_x[5]);
				PE_CE_PE1_O20_QRd02(pe_dse_y_region_pt6,	reg_y_region_pt6_y,	pp->dse_y_y[6],\
															reg_y_region_pt6_x,	pp->dse_y_x[6]);
				PE_CE_PE1_O20_QRd02(pe_dse_y_region_pt7,	reg_y_region_pt7_y,	pp->dse_y_y[7],\
															reg_y_region_pt7_x,	pp->dse_y_x[7]);
				PE_CE_PE1_O20_QRd02(pe_dse_h_region_pt0,	reg_h_region_pt0_y,	pp->dse_h_y[0],\
															reg_h_region_pt0_x,	pp->dse_h_x[0]);
				PE_CE_PE1_O20_QRd02(pe_dse_h_region_pt1,	reg_h_region_pt1_y,	pp->dse_h_y[1],\
															reg_h_region_pt1_x,	pp->dse_h_x[1]);
				PE_CE_PE1_O20_QRd02(pe_dse_h_region_pt2,	reg_h_region_pt2_y,	pp->dse_h_y[2],\
															reg_h_region_pt2_x,	pp->dse_h_x[2]);
				PE_CE_PE1_O20_QRd02(pe_dse_h_region_pt3,	reg_h_region_pt3_y,	pp->dse_h_y[3],\
															reg_h_region_pt3_x,	pp->dse_h_x[3]);
				PE_CE_PE1_O20_QRd02(pe_dse_h_region_pt4,	reg_h_region_pt4_y,	pp->dse_h_y[4],\
															reg_h_region_pt4_x,	pp->dse_h_x[4]);
				PE_CE_PE1_O20_QRd02(pe_dse_h_region_pt5,	reg_h_region_pt5_y,	pp->dse_h_y[5],\
															reg_h_region_pt5_x,	pp->dse_h_x[5]);
				PE_CE_PE1_O20_QRd02(pe_dse_h_region_pt6,	reg_h_region_pt6_y,	pp->dse_h_y[6],\
															reg_h_region_pt6_x,	pp->dse_h_x[6]);
				PE_CE_PE1_O20_QRd02(pe_dse_h_region_pt7,	reg_h_region_pt7_y,	pp->dse_h_y[7],\
															reg_h_region_pt7_x,	pp->dse_h_x[7]);
				PE_CE_PE1_O20_QRd03(pe1_dce_chr_gain,		chroma_gain_enable, pp->chroma_gain_en,\
															dce_cb_gain1,		pp->dce_chr_gain1,\
															dce_cb_gain2,		pp->dce_chr_gain2);
				PE_CE_PE1_O20_QRd02(pe1_dce_chr_alpha,		dce_chr_alpha1,		pp->dce_chr_alpha1,\
															dce_chr_alpha2,		pp->dce_chr_alpha2);
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_CO_PE1_O20_RdFL(pe1_dse_ctrl_00);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region0_sel,	pp->region_onoff[0]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region1_sel,	pp->region_onoff[1]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region2_sel,	pp->region_onoff[2]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region3_sel,	pp->region_onoff[3]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region4_sel,	pp->region_onoff[4]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region5_sel,	pp->region_onoff[5]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region6_sel,	pp->region_onoff[6]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region7_sel,	pp->region_onoff[7]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region8_sel,	pp->region_onoff[8]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region9_sel,	pp->region_onoff[9]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region10_sel,	pp->region_onoff[10]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region11_sel,	pp->region_onoff[11]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region12_sel,	pp->region_onoff[12]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region13_sel,	pp->region_onoff[13]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region14_sel,	pp->region_onoff[14]);
				PE_CO_PE1_O20_Rd01(pe1_dse_ctrl_00,	color_region15_sel,	pp->region_onoff[15]);
				PE_CO_PE1_O20_RdFL(pe1_dse_ctrl_00);
				
				PE_CO_PE1_O20_QRd03(pe1_dse_ctrl_01,		reg_dse_cr_mode_sel,pp->saturation_cr_mode,\
															reg_yh_cr_en,		pp->saturation_cr_mode,\
															color_region_gain,	pp->saturation_region_gain);
				PE_CO_PE1_O20_QRd02(pe_dse_y_region_pt0,	reg_y_region_pt0_y,	pp->dse_y_y[0],\
															reg_y_region_pt0_x,	pp->dse_y_x[0]);
				PE_CO_PE1_O20_QRd02(pe_dse_y_region_pt1,	reg_y_region_pt1_y,	pp->dse_y_y[1],\
															reg_y_region_pt1_x,	pp->dse_y_x[1]);
				PE_CO_PE1_O20_QRd02(pe_dse_y_region_pt2,	reg_y_region_pt2_y,	pp->dse_y_y[2],\
															reg_y_region_pt2_x,	pp->dse_y_x[2]);
				PE_CO_PE1_O20_QRd02(pe_dse_y_region_pt3,	reg_y_region_pt3_y,	pp->dse_y_y[3],\
															reg_y_region_pt3_x,	pp->dse_y_x[3]);
				PE_CO_PE1_O20_QRd02(pe_dse_y_region_pt4,	reg_y_region_pt4_y,	pp->dse_y_y[4],\
															reg_y_region_pt4_x,	pp->dse_y_x[4]);
				PE_CO_PE1_O20_QRd02(pe_dse_y_region_pt5,	reg_y_region_pt5_y,	pp->dse_y_y[5],\
															reg_y_region_pt5_x,	pp->dse_y_x[5]);
				PE_CO_PE1_O20_QRd02(pe_dse_y_region_pt6,	reg_y_region_pt6_y,	pp->dse_y_y[6],\
															reg_y_region_pt6_x,	pp->dse_y_x[6]);
				PE_CO_PE1_O20_QRd02(pe_dse_y_region_pt7,	reg_y_region_pt7_y,	pp->dse_y_y[7],\
															reg_y_region_pt7_x,	pp->dse_y_x[7]);
				PE_CO_PE1_O20_QRd02(pe_dse_h_region_pt0,	reg_h_region_pt0_y,	pp->dse_h_y[0],\
															reg_h_region_pt0_x,	pp->dse_h_x[0]);
				PE_CO_PE1_O20_QRd02(pe_dse_h_region_pt1,	reg_h_region_pt1_y,	pp->dse_h_y[1],\
															reg_h_region_pt1_x,	pp->dse_h_x[1]);
				PE_CO_PE1_O20_QRd02(pe_dse_h_region_pt2,	reg_h_region_pt2_y,	pp->dse_h_y[2],\
															reg_h_region_pt2_x,	pp->dse_h_x[2]);
				PE_CO_PE1_O20_QRd02(pe_dse_h_region_pt3,	reg_h_region_pt3_y,	pp->dse_h_y[3],\
															reg_h_region_pt3_x,	pp->dse_h_x[3]);
				PE_CO_PE1_O20_QRd02(pe_dse_h_region_pt4,	reg_h_region_pt4_y,	pp->dse_h_y[4],\
															reg_h_region_pt4_x,	pp->dse_h_x[4]);
				PE_CO_PE1_O20_QRd02(pe_dse_h_region_pt5,	reg_h_region_pt5_y,	pp->dse_h_y[5],\
															reg_h_region_pt5_x,	pp->dse_h_x[5]);
				PE_CO_PE1_O20_QRd02(pe_dse_h_region_pt6,	reg_h_region_pt6_y,	pp->dse_h_y[6],\
															reg_h_region_pt6_x,	pp->dse_h_x[6]);
				PE_CO_PE1_O20_QRd02(pe_dse_h_region_pt7,	reg_h_region_pt7_y,	pp->dse_h_y[7],\
															reg_h_region_pt7_x,	pp->dse_h_x[7]);
				PE_CO_PE1_O20_QRd03(pe1_dce_chr_gain,		chroma_gain_enable, pp->chroma_gain_en,\
															dce_cb_gain1,		pp->dce_chr_gain1,\
															dce_cb_gain2,		pp->dce_chr_gain2);
				PE_CO_PE1_O20_QRd02(pe1_dce_chr_alpha,		dce_chr_alpha1,		pp->dce_chr_alpha1,\
															dce_chr_alpha2,		pp->dce_chr_alpha2);
			}
			PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: saturation_cr_mode:%d, saturation_region_gain:%d\n"\
				"region sel:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
				pp->win_id,\
				pp->saturation_cr_mode, pp->saturation_region_gain, \
				pp->region_onoff[0],pp->region_onoff[1],pp->region_onoff[2],pp->region_onoff[3],\
				pp->region_onoff[4],pp->region_onoff[5],pp->region_onoff[6],pp->region_onoff[7],\
				pp->region_onoff[8],pp->region_onoff[9],pp->region_onoff[10],pp->region_onoff[11],\
				pp->region_onoff[12],pp->region_onoff[13],pp->region_onoff[14],pp->region_onoff[15]);
			PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: n"\
				"dse_gain_h_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_h_y:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_y_x:%d,%d,%d,%d,%d,%d,%d,%d\n" \
				"dse_gain_y_y:%d,%d,%d,%d,%d,%d,%d,%d\n", \
				pp->win_id,\
				pp->dse_h_x[0],pp->dse_h_x[1],pp->dse_h_x[2],pp->dse_h_x[3],\
				pp->dse_h_x[4],pp->dse_h_x[5],pp->dse_h_x[6],pp->dse_h_x[7],\
				pp->dse_h_y[0],pp->dse_h_y[1],pp->dse_h_y[2],pp->dse_h_y[3],\
				pp->dse_h_y[4],pp->dse_h_y[5],pp->dse_h_y[6],pp->dse_h_y[7],\
				pp->dse_y_x[0],pp->dse_y_x[1],pp->dse_y_x[2],pp->dse_y_x[3],\
				pp->dse_y_x[4],pp->dse_y_x[5],pp->dse_y_x[6],pp->dse_y_x[7],\
				pp->dse_y_y[0],pp->dse_y_y[1],pp->dse_y_y[2],pp->dse_y_y[3],\
				pp->dse_y_y[4],pp->dse_y_y[5],pp->dse_y_y[6],pp->dse_y_y[7]);
			PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: chroma_gain_en:%d\n"\
				"dce_chr_gain1:%d,dce_chr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n",\
				pp->win_id,	pp->chroma_gain_en, \
				pp->dce_chr_gain1,pp->dce_chr_gain2,pp->dce_chr_alpha1,pp->dce_chr_alpha2);
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

/**
 * set dce lut on sync
 *
 * @param   *pCfg [in] PE_TSK_O20_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_SetDceLutOnSync(PE_TSK_O20_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	#ifdef PE_DCM_HW_O20_SET_DCE_LUT_ON_SYNC
	static UINT32 pre_lut_cnt = 0xffff;
	PE_DCM_HW_O20_SETTINGS_T *pInfo=&_g_pe_dcm_hw_o20_info;
	UINT32 *pLut = NULL;
	UINT32 count;
	do {
		if (pInfo->dce_lut_off==1)							break;
		if (pInfo->dce_lut_cnt>PE_DCM_HW_O20_DCE_CNT_NUM)	break;
		if (pInfo->dce_lut_num>PE_DCM_HW_O20_DCE_LUT_NUM)	break;
		if (pre_lut_cnt==pInfo->dce_lut_cnt)	break;
		if (pInfo->dce_lut_num==1)	pLut = pInfo->dce_lut1;
		else						pLut = pInfo->dce_lut0;
		PE_CEO_PE1_O20_RdFL(pe1_dce_ia_ctrl);
		//PE_CEO_PE1_O20A0_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	0x0);	//0:clear, 1:enable
		PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,	0x0);	//0:host access, 1:normal mode
		PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,		0x1);	//ai 0:disable, 1:enable
		PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,0x0);	//address
		PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
		for(count=0;count<PE_DCM_HW_O20_LUT_STEP;count++)
		{
			PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(pLut[count],0,10));//y data
			PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(pLut[count],16,10));//x data
			PE_CEO_PE1_O20_WrFL(pe1_dce_ia_data);
		}
		PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 0x1);	//0:host access, 1:normal mode
		PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	0x1);	//0:clear, 1:enable
		PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
		PE_DCM_HW_O20_DBG_PRINT("[Dce]cnt:%d<-%d,num:%4d, lut:|%3d|%3d|%3d|%3d|%3d| |%3d|%3d|%3d|%3d|%3d|\n",\
			pre_lut_cnt, pInfo->dce_lut_cnt, pInfo->dce_lut_num, \
			GET_BITS(pLut[0],16,10), GET_BITS(pLut[1],16,10), GET_BITS(pLut[2],16,10), \
			GET_BITS(pLut[3],16,10), GET_BITS(pLut[4],16,10), \
			GET_BITS(pLut[0],0,10), GET_BITS(pLut[1],0,10), GET_BITS(pLut[2],0,10), \
			GET_BITS(pLut[3],0,10), GET_BITS(pLut[4],0,10));
		pre_lut_cnt=pInfo->dce_lut_cnt;
	} while (0);
	#endif
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

/**
 * set obc
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_SetObcParam(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_DCM_OBC_CTRL_T *pp=(LX_PE_DCM_OBC_CTRL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_dcm_hw_o20_trace)
			{
				PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: n"\
				"enable :%d\n"\
				"object_fg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_fg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_bg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_bg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"fg_gain_x0,x1: %d, %d,\n"\
				"fg_gain_y0,y1: %d, %d,\n"\
				"bg_gain_x0,x1: %d, %d,\n"\
				"bg_gain_y0,y1: %d, %d,\n",\
				pp->win_id,\
				pp->bOBC_enable, \
				pp->object_fg_x[0],pp->object_fg_x[1],pp->object_fg_x[2],pp->object_fg_x[3], \
				pp->object_fg_x[4],pp->object_fg_x[5],pp->object_fg_x[6],pp->object_fg_x[7], \
				pp->object_fg_y[0],pp->object_fg_y[1],pp->object_fg_y[2],pp->object_fg_y[3], \
				pp->object_fg_y[4],pp->object_fg_y[5],pp->object_fg_y[6],pp->object_fg_y[7], \
				pp->object_bg_x[0],pp->object_bg_x[1],pp->object_bg_x[2],pp->object_bg_x[3], \
				pp->object_bg_x[4],pp->object_bg_x[5],pp->object_bg_x[6],pp->object_bg_x[7], \
				pp->object_bg_y[0],pp->object_bg_y[1],pp->object_bg_y[2],pp->object_bg_y[3], \
				pp->object_bg_y[4],pp->object_bg_y[5],pp->object_bg_y[6],pp->object_bg_y[7], \
				pp->fg_gain_x0,pp->fg_gain_x1,pp->fg_gain_y0,pp->fg_gain_y1, \
				pp->bg_gain_x0,pp->bg_gain_x1,pp->bg_gain_y0,pp->bg_gain_y1);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_O20_QWr01(reg_psp_ctrl_00,	reg_psp_en,  	 GET_BITS(pp->bOBC_enable,0,1));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_05, 	reg_psp_lut_x0,  GET_BITS(pp->object_fg_x[0],0,10),\
														reg_psp_lut_y0,  GET_BITS(pp->object_fg_y[0],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_06, 	reg_psp_lut0_x1, GET_BITS(pp->object_fg_x[1],0,10),\
														reg_psp_lut0_y1, GET_BITS(pp->object_fg_y[1],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_07, 	reg_psp_lut0_x2, GET_BITS(pp->object_fg_x[2],0,10),\
														reg_psp_lut0_y2, GET_BITS(pp->object_fg_y[2],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_08, 	reg_psp_lut0_x3, GET_BITS(pp->object_fg_x[3],0,10),\
														reg_psp_lut0_y3, GET_BITS(pp->object_fg_y[3],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_09, 	reg_psp_lut0_x4, GET_BITS(pp->object_fg_x[4],0,10),\
														reg_psp_lut0_y4, GET_BITS(pp->object_fg_y[4],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_10, 	reg_psp_lut0_x5, GET_BITS(pp->object_fg_x[5],0,10),\
														reg_psp_lut0_y5, GET_BITS(pp->object_fg_y[5],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_11, 	reg_psp_lut0_x6, GET_BITS(pp->object_fg_x[6],0,10),\
														reg_psp_lut0_y6, GET_BITS(pp->object_fg_y[6],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_12, 	reg_psp_lut0_x7, GET_BITS(pp->object_fg_x[7],0,10),\
														reg_psp_lut0_y7, GET_BITS(pp->object_fg_y[7],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_13, 	reg_psp_lut1_x0, GET_BITS(pp->object_bg_x[0],0,10),\
														reg_psp_lut1_y0, GET_BITS(pp->object_bg_y[0],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_14, 	reg_psp_lut1_x1, GET_BITS(pp->object_bg_x[1],0,10),\
														reg_psp_lut1_y1, GET_BITS(pp->object_bg_y[1],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_15, 	reg_psp_lut1_x2, GET_BITS(pp->object_bg_x[2],0,10),\
														reg_psp_lut1_y2, GET_BITS(pp->object_bg_y[2],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_16, 	reg_psp_lut1_x3, GET_BITS(pp->object_bg_x[3],0,10),\
														reg_psp_lut1_y3, GET_BITS(pp->object_bg_y[3],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_17, 	reg_psp_lut1_x4, GET_BITS(pp->object_bg_x[4],0,10),\
														reg_psp_lut1_y4, GET_BITS(pp->object_bg_y[4],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_18, 	reg_psp_lut1_x5, GET_BITS(pp->object_bg_x[5],0,10),\
														reg_psp_lut1_y5, GET_BITS(pp->object_bg_y[5],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_19, 	reg_psp_lut1_x6, GET_BITS(pp->object_bg_x[6],0,10),\
														reg_psp_lut1_y6, GET_BITS(pp->object_bg_y[6],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_20, 	reg_psp_lut1_x7, GET_BITS(pp->object_bg_x[7],0,10),\
														reg_psp_lut1_y7, GET_BITS(pp->object_bg_y[7],0,10));
				PE_SHP_PSP_O20_QWr04(reg_psp_ctrl_21, 	reg_psp_gain_lut0_y0, GET_BITS(pp->fg_gain_y0,0,8),\
														reg_psp_gain_lut0_x0, GET_BITS(pp->fg_gain_x0,0,8),\
														reg_psp_gain_lut0_y1, GET_BITS(pp->fg_gain_y1,0,8),\
														reg_psp_gain_lut0_x1, GET_BITS(pp->fg_gain_x1,0,8));
				PE_SHP_PSP_O20_QWr04(reg_psp_ctrl_22, 	reg_psp_gain_lut0_y0, GET_BITS(pp->bg_gain_y0,0,8),\
														reg_psp_gain_lut0_x0, GET_BITS(pp->bg_gain_x0,0,8),\
														reg_psp_gain_lut0_y1, GET_BITS(pp->bg_gain_y1,0,8),\
														reg_psp_gain_lut0_x1, GET_BITS(pp->bg_gain_x1,0,8));
			}
 		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * get obc
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_GetObcParam(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_DCM_OBC_CTRL_T *pp=(LX_PE_DCM_OBC_CTRL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_O20_QRd01(reg_psp_ctrl_00,	reg_psp_en,  	 pp->bOBC_enable);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_05, 	reg_psp_lut_x0,  pp->object_fg_x[0],\
														reg_psp_lut_y0,  pp->object_fg_y[0]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_06, 	reg_psp_lut0_x1, pp->object_fg_x[1],\
														reg_psp_lut0_y1, pp->object_fg_y[1]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_07, 	reg_psp_lut0_x2, pp->object_fg_x[2],\
														reg_psp_lut0_y2, pp->object_fg_y[2]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_08, 	reg_psp_lut0_x3, pp->object_fg_x[3],\
														reg_psp_lut0_y3, pp->object_fg_y[3]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_09, 	reg_psp_lut0_x4, pp->object_fg_x[4],\
														reg_psp_lut0_y4, pp->object_fg_y[4]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_10, 	reg_psp_lut0_x5, pp->object_fg_x[5],\
														reg_psp_lut0_y5, pp->object_fg_y[5]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_11, 	reg_psp_lut0_x6, pp->object_fg_x[6],\
														reg_psp_lut0_y6, pp->object_fg_y[6]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_12, 	reg_psp_lut0_x7, pp->object_fg_x[7],\
														reg_psp_lut0_y7, pp->object_fg_y[7]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_13, 	reg_psp_lut1_x0, pp->object_bg_x[0],\
														reg_psp_lut1_y0, pp->object_bg_y[0]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_14, 	reg_psp_lut1_x1, pp->object_bg_x[1],\
														reg_psp_lut1_y1, pp->object_bg_y[1]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_15, 	reg_psp_lut1_x2, pp->object_bg_x[2],\
														reg_psp_lut1_y2, pp->object_bg_y[2]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_16, 	reg_psp_lut1_x3, pp->object_bg_x[3],\
														reg_psp_lut1_y3, pp->object_bg_y[3]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_17, 	reg_psp_lut1_x4, pp->object_bg_x[4],\
														reg_psp_lut1_y4, pp->object_bg_y[4]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_18, 	reg_psp_lut1_x5, pp->object_bg_x[5],\
														reg_psp_lut1_y5, pp->object_bg_y[5]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_19, 	reg_psp_lut1_x6, pp->object_bg_x[6],\
														reg_psp_lut1_y6, pp->object_bg_y[6]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_20, 	reg_psp_lut1_x7, pp->object_bg_x[7],\
														reg_psp_lut1_y7, pp->object_bg_y[7]);
				PE_SHP_PSP_O20_QRd04(reg_psp_ctrl_21, 	reg_psp_gain_lut0_y0, pp->fg_gain_y0,\
														reg_psp_gain_lut0_x0, pp->fg_gain_x0,\
														reg_psp_gain_lut0_y1, pp->fg_gain_y1,\
														reg_psp_gain_lut0_x1, pp->fg_gain_x1);
				PE_SHP_PSP_O20_QRd04(reg_psp_ctrl_22, 	reg_psp_gain_lut0_y0, pp->bg_gain_y0,\
														reg_psp_gain_lut0_x0, pp->bg_gain_x0,\
														reg_psp_gain_lut0_y1, pp->bg_gain_y1,\
														reg_psp_gain_lut0_x1, pp->bg_gain_x1);
			}
			if (_g_dcm_hw_o20_trace)
			{
				PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: n"\
				"enable :%d\n"\
				"object_fg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_fg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_bg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_bg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"fg_gain_x0,x1: %d, %d,\n"\
				"fg_gain_y0,y1: %d, %d,\n"\
				"bg_gain_x0,x1: %d, %d,\n"\
				"bg_gain_y0,y1: %d, %d,\n",\
				pp->win_id,\
				pp->bOBC_enable, \
				pp->object_fg_x[0],pp->object_fg_x[1],pp->object_fg_x[2],pp->object_fg_x[3], \
				pp->object_fg_x[4],pp->object_fg_x[5],pp->object_fg_x[6],pp->object_fg_x[7], \
				pp->object_fg_y[0],pp->object_fg_y[1],pp->object_fg_y[2],pp->object_fg_y[3], \
				pp->object_fg_y[4],pp->object_fg_y[5],pp->object_fg_y[6],pp->object_fg_y[7], \
				pp->object_bg_x[0],pp->object_bg_x[1],pp->object_bg_x[2],pp->object_bg_x[3], \
				pp->object_bg_x[4],pp->object_bg_x[5],pp->object_bg_x[6],pp->object_bg_x[7], \
				pp->object_bg_y[0],pp->object_bg_y[1],pp->object_bg_y[2],pp->object_bg_y[3], \
				pp->object_bg_y[4],pp->object_bg_y[5],pp->object_bg_y[6],pp->object_bg_y[7], \
				pp->fg_gain_x0,pp->fg_gain_x1,pp->fg_gain_y0,pp->fg_gain_y1, \
				pp->bg_gain_x0,pp->bg_gain_x1,pp->bg_gain_y0,pp->bg_gain_y1);
			}
 		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * get obc data
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_GetObcData(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_DCM_OBC1_DATA_T *pp=(LX_PE_DCM_OBC1_DATA_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_OBC_F_O20_QRd01(reg_perspect_gain_ctrl_0,	object_relibility,  pp->face_relibility);
				PE_VSD_OBC_F_O20_QRd02(reg_perspect_lut_x_0, 	object_fg_pel_num,  pp->face_fg_pel_num,\
																	object_fg_apl,  	pp->face_fg_apl);
				PE_VSD_OBC_F_O20_QRd02(reg_perspect_lut_x_1, 	object_bg_pel_num, 	pp->face_bg_pel_num,\
																	object_bg_apl, 		pp->face_bg_apl);
				PE_VSD_OBC_F_O20_QRd04(reg_perspect_lut_x_2, 	object_boxh1, 		pp->face_boxh1,\
																	object_boxh2, 		pp->face_boxh2,\
																	object_boxw1, 		pp->face_boxw1,\
																	object_boxw2, 		pp->face_boxw2);
				pp->object_relibility = pp->face_relibility;
				pp->object_fg_pel_num = pp->face_fg_pel_num;
				pp->object_fg_apl      = pp->face_fg_apl;
				pp->object_bg_pel_num = pp->face_bg_pel_num;
				pp->object_bg_apl      = pp->face_bg_apl;
				pp->object_boxh1      = pp->face_boxh1;
				pp->object_boxh2      = pp->face_boxh2;
				pp->object_boxw1      = pp->face_boxw1;
				pp->object_boxw2      = pp->face_boxw2;
				pp->face_data00 = pp->face_data01 = pp->object_data00 = pp->object_data01 = 0x0;
				pp->face_data02 = pp->face_data03 = pp->object_data02 = pp->object_data03 = 0x0;
				pp->face_data04 = pp->face_data05 = pp->object_data04 = pp->object_data05 = 0x0;
				pp->face_data06 = pp->face_data07 = pp->object_data06 = pp->object_data07 = 0x0;
				pp->face_data08 = pp->face_data09 = pp->object_data08 = pp->object_data09 = 0x0;
				pp->face_data10 = pp->face_data11 = pp->object_data10 = pp->object_data11 = 0x0;

			}
			if (_g_dcm_hw_o20_trace)
			{
				PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: n"\
				"object_relibility: %d\n"\
				"object_fg_pel_num: %d\n"\
				"object_fg_apl:     %d\n"\
				"object_bg_pel_num: %d\n"\
				"object_bg_apl:     %d\n"\
				"object_boxh1:      %d\n"\
				"object_boxh2:      %d\n"\
				"object_boxw1:      %d\n"\
				"object_boxw2:      %d\n"\
				"face_relibility: %d\n"\
				"face_fg_pel_num: %d\n"\
				"face_fg_apl: 	%d\n"\
				"face_bg_pel_num: %d\n"\
				"face_bg_apl: 	%d\n"\
				"face_boxh1:		%d\n"\
				"face_boxh2:		%d\n"\
				"face_boxw1:		%d\n"\
				"face_boxw2:		%d\n",\
				pp->win_id,\
				pp->object_relibility, \
				pp->object_fg_pel_num, \
				pp->object_fg_apl, \
				pp->object_bg_pel_num, \
				pp->object_bg_apl, \
				pp->object_boxh1, \
				pp->object_boxh2, \
				pp->object_boxw1, \
				pp->object_boxw2, \
				pp->face_relibility, \
				pp->face_fg_pel_num, \
				pp->face_fg_apl, \
				pp->face_bg_pel_num, \
				pp->face_bg_apl, \
				pp->face_boxh1, \
				pp->face_boxh2, \
				pp->face_boxw1, \
				pp->face_boxw2);
			}
 		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetDtmLut(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
#define PE_DCM_DTM_LUT_SIZE 33
	UINT32 count=0;
	UINT32 lut_data=0;
	//int i;
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DTM_LUT_T *pp = (LX_PE_DCM_DTM_LUT_T *)pstParams;
		PE_CHECK_WINID(pp->win_id);
		PE_DCM_HW_O20_CHECK_CODE((pp->size>PE_DCM_DTM_LUT_SIZE), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pp->size);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_DTM_O20_RdFL(dtm_llut0_ia_data);
				//PE_VSD_DTM_O20_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x0);
				PE_VSD_DTM_O20_QWr03(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x1,\
														hif_llut0_enable,	0x0,\
													 	hif_llut0_address,	0x0);
				PE_DCM_HW_O20_DBG_PRINT("\n update dmt lut\n");
				PE_DCM_HW_O20_DBG_PRINT("\n   [ i]    x,    y\n");
				for(count=0; count<32 ;count++)
				{
					lut_data = pp->data[count];
					PE_VSD_DTM_O20_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_y,GET_BITS(lut_data,0,10));//y data
					PE_VSD_DTM_O20_Wr01(dtm_llut0_ia_data,hif_llut0_wdata_x,GET_BITS(lut_data,16,10));//x data
					PE_VSD_DTM_O20_WrFL(dtm_llut0_ia_data);
					PE_DCM_HW_O20_DBG_PRINT("   [%02d] %4d, %4d\n", \
						count, GET_BITS(lut_data,16,10), GET_BITS(lut_data,0,10));
				}
				lut_data = pp->data[32];
				PE_VSD_DTM_O20_QWr02(dtm_llut_ctrl_05, hif_llut_wdata_y_33rd, GET_BITS(lut_data,0,10),\
													   hif_llut_wdata_x_33rd, GET_BITS(lut_data,16,10));
				PE_VSD_DTM_O20_QWr03(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x0,\
														hif_llut0_enable,	0x1,\
														hif_llut0_load,		0x1);
				//PE_VSD_DTM_O20_QWr01(dtm_llut_ctrl_00,	luminance_lut_enable, 0x1);
				#if 1	/* F20_APB */
				do {
					for(count=0; count<32 ;count++)
					{
						lut_data = pp->data[count];
						PE_CHPI_APB0_F20_Wr(dtm0.dtm_llut0_ia_data[count].hif_llut0_wdata_y,GET_BITS(lut_data,0,10));//y data
						PE_CHPI_APB0_F20_Wr(dtm0.dtm_llut0_ia_data[count].hif_llut0_wdata_x,GET_BITS(lut_data,16,10));//x data
						PE_CHPI_APB0_F20_WrFL(dtm0.dtm_llut0_ia_data[count].udata32);
					}
					lut_data = pp->data[32];
					PE_CHPI_APB0_F20_Wr(dtm0.dtm_llut_ctrl_05.hif_llut_wdata_y_33rd,GET_BITS(lut_data,0,10));
					PE_CHPI_APB0_F20_Wr(dtm0.dtm_llut_ctrl_05.hif_llut_wdata_x_33rd,GET_BITS(lut_data,16,10));
					PE_CHPI_APB0_F20_WrFL(dtm0.dtm_llut_ctrl_05.udata32);
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DTM0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_GetDtmLut(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DTM_LUT_T *pp = (LX_PE_DCM_DTM_LUT_T *)pstParams;
		PE_CHECK_WINID(pp->win_id);
		PE_DCM_HW_O20_CHECK_CODE((pp->size>PE_DCM_HW_O20_LUT_STEP), break, \
			"[%s,%d] pstParams->size(%d) is over.\n", __F__,__L__, pp->size);
		win_id = PE_GET_CHECKED_WINID(pp->win_id);
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				
				PE_VSD_DTM_O20_QWr02(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x1,\
														hif_llut0_enable,	0x0);
				for(count=0;count<(pp->size);count++)
				{
					#if 0
					if (count<(PE_DCM_HW_O20_LUT_MAX-1))
					{
						PE_CE_PE1_O20_RdFL(pe1_dce_ia_data);
						pstParams->data[count] = PE_CE_PE1_O20_Rd(pe1_dce_ia_data);
					}
					else	//count == (PE_DCM_HW_O20_LUT_MAX-1)
					{
						PE_CE_PE1_O20_RdFL(pe1_dce_ctrl_08);
						pstParams->data[count] = PE_CE_PE1_O20_Rd(pe1_dce_ctrl_08);
					}
					#else
					PE_VSD_DTM_O20_RdFL(dtm_llut0_ia_data);
					pp->data[count] = PE_VSD_DTM_O20_Rd(dtm_llut0_ia_data);
					#endif
				}
				PE_VSD_DTM_O20_QWr02(dtm_llut0_ia_ctrl,	hif_llut0_ai,		0x0,\
														hif_llut0_enable,	0x1);
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_F20_DownloadDrcDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_F20_T *p_shdw_db = gPE_DDR_DB_F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_F20_T *p_phys_db = gPE_DDR_DB_F20.phys.data;
	volatile UINT32 *p_drc_data = p_phys_db->drc_lut.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_data);
		if (PE_KDRV_VER_O20)
		{
			/* header */
			sec_typ = PE_DDR_F20_SEC_DRC_LUT;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_F20_DRC_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_F20_DRC_LUT_SIZE;
			p_phys_db->drc_lut.header.version	= p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_lut.header.sec_type	= p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_lut.header.item_num	= p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_F20_DRC_LUT_ITEM_NUM * PE_DDR_F20_DRC_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_F20_HEADER_T);
			/* wr ddr */
				memcpy((UINT32 *)p_drc_data, pe_drc_lut_f20, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_F20_DownloadDrcCurvDbInit(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_DDR_DB_SHDW_REG_F20_T *p_shdw_db = gPE_DDR_DB_F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_F20_T *p_phys_db = gPE_DDR_DB_F20.phys.data;
	volatile UINT32 *p_drc_cuv = p_phys_db->drc_cuv.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_drc_cuv);
		if (PE_KDRV_VER_O20)
		{
			/* header */
			sec_typ = PE_DDR_F20_SEC_DRC_CURV;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_F20_DRC_CURV_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DRC_F20_FW_LUT_SIZE;
			p_phys_db->drc_cuv.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->drc_cuv.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->drc_cuv.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->drc_cuv.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_F20_DRC_CURV_ITEM_NUM * PE_DRC_F20_FW_LUT_SIZE * sizeof(SINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_F20_HEADER_T);
			/* wr ddr */
			memcpy((UINT32 *)p_drc_cuv, pe_drc_lut_init, size);
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x, size:%d)\n", \
				PE_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->top_h.sec_size[sec_typ]);
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_F20_DownloadDrcCurvDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_DCM_DRC_CUV_T *pp;
	int i, j;
 	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O20)
		{
			pp=(LX_PE_DCM_DRC_CUV_T *)pstParams;
			for (i=0; i<LX_PE_CM_GLOBAL_POINT; i++)
			{
				PE_CHPI_TBL0_F20_QWr(drc.global_apl[i],pp->global_apl[i]);
 			}
  			for (i=0; i<LX_PE_CM_LOCAL_POINT; i++)
			{
				PE_CHPI_TBL0_F20_QWr(drc.local_apl[i],pp->local_apl[i]);
 			}
			PE_CHPI_TBL0_F20_QWr(drc.cuv_gain_w,pp->cuv_gain_w);
			PE_CHPI_TBL0_F20_QWr(drc.cuv_gain_b,pp->cuv_gain_b);
			for (i=0; i<LX_PE_CM_FREE_POINT; i++)
			{
				for (j=0; j<LX_PE_CM_LOCAL_CURVE_FW; j++)
				{
					PE_CHPI_TBL0_F20_QWr(drc.n1p_trans_curv[i][j],pp->n1p_trans_curv[i][j]);
					PE_CHPI_TBL0_F20_QWr(drc.n2p_trans_curv[i][j],pp->n2p_trans_curv[i][j]);
					PE_CHPI_TBL0_F20_QWr(drc.n3p_trans_curv[i][j],pp->n3p_trans_curv[i][j]);
					PE_CHPI_TBL0_F20_QWr(drc.n4p_trans_curv[i][j],pp->n4p_trans_curv[i][j]);
				}
			}
			PE_INF_O20_IncChipInfoCount(PE_INF_O20_CHPI_CNT_DRC);
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetAccelDceLut(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 dyn_bypass[16] = {0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960};
	int count=0;
	int print_co=0;
	do{
		PE_DCM_HW_O20_DBG_PRINT("set dce lut accel mode\n");
		if(PE_KDRV_VER_O20)
		{
			while(1)
			{
				PE_CEO_PE1_O20_RdFL(pe1_dce_ia_ctrl);
				PE_CEO_PE1_O20_RdFL(pe1_dce_ia_data);
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				for(count=0;count<16;count++)
				{
					PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(dyn_bypass[count],0,10));	//y data
					PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(dyn_bypass[count],0,10));//x data
					PE_CEO_PE1_O20_WrFL(pe1_dce_ia_data);
				}
				/* 20160601, read register on addr0 to avoid white flash */
				//PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				//PE_CEO_PE1_O20_RdFL(pe1_dce_ia_data);
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
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
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_SetDseCtrl2(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	//UINT32 color_out_gain;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_DCM_DSE_CTRL4_T *pp = (LX_PE_DCM_DSE_CTRL4_T *)pstParams;
			static LX_PE_DCM_DSE_CTRL4_T prev[LX_PE_WIN_NUM];
			static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_DCM_DSE_CTRL4_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DCM_HW_O20_DBG_PRINT("duplicated DB : LX_PE_DCM_DSE_CTRL4_T\n");
				ret=RET_OK;
				break;
			}
			PE_DCM_HW_O20_DBG_PRINT("[wid:%d] set: chroma_gain_en:%d\n"\
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
				PE_CEO_PE1_O20_QWr03(pe1_dce_chr_gain,	chroma_gain_enable, GET_BITS(pp->chroma_gain_en,0,1),\
															dce_cb_gain1,		GET_BITS(pp->chroma_cb_gain1,0,10),\
															dce_cb_gain2,		GET_BITS(pp->chroma_cb_gain2,0,10));
				PE_CEO_PE1_O20_QWr02(pe1_dce_chr_gain2,	dce_cr_gain1,		GET_BITS(pp->chroma_cr_gain1,0,10),\
															dce_cr_gain2,		GET_BITS(pp->chroma_cr_gain2,0,10));
				/* do not setting dce_chr_alpha1, dce_chr_alpha2 bc f/w overwrite */
				//PE_CEO_PE1_O20_QWr02(pe1_dce_chr_alpha,	dce_chr_alpha1,		GET_BITS(pp->chroma_alpha1,0,10),\
				//											dce_chr_alpha2,		GET_BITS(pp->chroma_alpha2,0,10));
				PE_VSD_DTM_O20_QWr02(dtm_hue_sat_ctrl,	reg_sat_prsv_ratio,	GET_BITS(pp->dtm_sat_gain,0,8),\
															reg_hue_prsv_ratio, GET_BITS(pp->dtm_hue_gain,0,8));
				#if 0	/* O20F20_APB */
				do {
					PE_CHPI_APB0_O20F20_Wr(dce0.pe1_dce_chr_gain.chroma_gain_enable,GET_BITS(pp->chroma_gain_en,0,1));
					PE_CHPI_APB0_O20F20_Wr(dce0.pe1_dce_chr_gain.dce_cb_gain1,GET_BITS(pp->chroma_chr_gain1,0,10));
					PE_CHPI_APB0_O20F20_Wr(dce0.pe1_dce_chr_gain.dce_cb_gain2,GET_BITS(pp->chroma_chr_gain2,0,10));
					PE_CHPI_APB0_O20F20_Wr(dce0.pe1_dce_chr_alpha.dce_chr_alpha1,GET_BITS(pp->chroma_chr_alpha1,0,10));
					PE_CHPI_APB0_O20F20_Wr(dce0.pe1_dce_chr_alpha.dce_chr_alpha2,GET_BITS(pp->chroma_chr_alpha2,0,10));
					PE_CHPI_APB0_O20F20_Wr(dtm0.dtm_hue_sat_ctrl.reg_sat_prsv_ratio,GET_BITS(pp->dtm_sat_gain,0,8));
					PE_CHPI_APB0_O20F20_Wr(dtm0.dtm_hue_sat_ctrl.reg_hue_prsv_ratio,GET_BITS(pp->dtm_hue_gain,0,8));
					PE_CHPI_APB0_O20F20_WrFL(dce0.pe1_dce_chr_gain.udata32);
					PE_CHPI_APB0_O20F20_WrFL(dce0.pe1_dce_chr_alpha.udata32);
					PE_CHPI_APB0_O20F20_WrFL(dtm0.dtm_hue_sat_ctrl.udata32);
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DCE0);
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DTM0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_DCM_HW_O20_GetDseCtrl2(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_DCM_DSE_CTRL4_T *pp=(LX_PE_DCM_DSE_CTRL4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				
				PE_CE_PE1_O20_QRd03(pe1_dce_chr_gain,		chroma_gain_enable, pp->chroma_gain_en,\
															dce_cb_gain1,		pp->chroma_cb_gain1,\
															dce_cb_gain2,		pp->chroma_cb_gain2);
				PE_CE_PE1_O20_QRd02(pe1_dce_chr_gain2,	dce_cr_gain1,		pp->chroma_cr_gain1,\
															dce_cr_gain2,		pp->chroma_cr_gain2);
				PE_CE_PE1_O20_QRd02(pe1_dce_chr_alpha,	dce_chr_alpha1,		pp->chroma_alpha1,\
															dce_chr_alpha2,		pp->chroma_alpha2);
				PE_VSD_DTM_O20_QRd02(dtm_hue_sat_ctrl,	reg_sat_prsv_ratio,	pp->dtm_sat_gain,\
															reg_hue_prsv_ratio, pp->dtm_hue_gain);
			}
			PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: chroma_gain_en:%d\n"\
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
			PE_DCM_HW_O20_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}

/**
 * set chroma face lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_O20_SetDceLut2(void *pstParams)
{
	int ret = RET_OK;
#ifdef PE_HW_O20_BRINGUP
	UINT32 count=0;
	UINT32 lut_data=0;
	do {
		CHECK_KNULL(pstParams);
		LX_PE_DCM_DCE_LUT1_T *pp = (LX_PE_DCM_DCE_LUT1_T *)pstParams;
		static LX_PE_DCM_DCE_LUT1_T prev[LX_PE_WIN_NUM];
		static UINT32 chk = 0x0;
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_DCM_DCE_LUT1_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DCM_HW_O20_DBG_PRINT("duplicated DB : LX_PE_DCM_DCE_LUT1_T\n");
			ret=RET_OK;
			break;
		}
		if(PE_KDRV_VER_O20)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CEO_PE1_O20_RdFL(pe1_dce_ia_ctrl);
				PE_CEO_PE1_O20_RdFL(pe1_dce_ia_data);
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl, hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl, hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl, hif_dyc_address,	0x0);	//address
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				PE_DCM_HW_O20_DBG_PRINT("\n update dce lut\n");
				PE_DCM_HW_O20_DBG_PRINT("\n   [ i]	  x,	y\n");
				for(count=0;count<32;count++)
				{
					PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(pp->lumalut_y[count],0,10));//y data
					PE_CEO_PE1_O20_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(pp->lumalut_x[count],0,10));//x data
					PE_CEO_PE1_O20_WrFL(pe1_dce_ia_data);
					PE_DCM_HW_O20_DBG_PRINT("   [%02d] %4d, %4d\n", count, \
						GET_BITS(pp->lumalut_x[count],0,10), GET_BITS(pp->lumalut_y[count],0,10));
				}
				/* 20160601, read register on addr0 to avoid white flash */
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);
				PE_CEO_PE1_O20_RdFL(pe1_dce_ia_data);
				
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl, hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CEO_PE1_O20_Wr01(pe1_dce_ia_ctrl, hif_dce_load,		0x1);	//0:clear, 1:enable
				PE_CEO_PE1_O20_WrFL(pe1_dce_ia_ctrl);

				/* chroma gain lut write down to dummy reg for F/W */
				PE_CCO_VERI_O20_QWr02(sys_veri_20, chroma_face_alpha_lut1_x0, GET_BITS(pp->chroma_face_alpha_lut1_x[0],0,8),\
													  chroma_face_alpha_lut1_x1, GET_BITS(pp->chroma_face_alpha_lut1_x[1],0,8));
				PE_CCO_VERI_O20_QWr02(sys_veri_21, chroma_face_alpha_lut1_x2, GET_BITS(pp->chroma_face_alpha_lut1_x[2],0,8),\
													  chroma_face_alpha_lut1_x3, GET_BITS(pp->chroma_face_alpha_lut1_x[3],0,8));
				PE_CCO_VERI_O20_QWr02(sys_veri_22, chroma_face_alpha_lut1_y0, GET_BITS(pp->chroma_face_alpha_lut1_y[0],0,10),\
													  chroma_face_alpha_lut1_y1, GET_BITS(pp->chroma_face_alpha_lut1_y[1],0,10));
				PE_CCO_VERI_O20_QWr02(sys_veri_23, chroma_face_alpha_lut1_y2, GET_BITS(pp->chroma_face_alpha_lut1_y[2],0,10),\
													  chroma_face_alpha_lut1_y3, GET_BITS(pp->chroma_face_alpha_lut1_y[3],0,10));
				PE_CCO_VERI_O20_QWr02(sys_veri_24, chroma_face_alpha_lut2_x0, GET_BITS(pp->chroma_face_alpha_lut2_x[0],0,8),\
													  chroma_face_alpha_lut2_x1, GET_BITS(pp->chroma_face_alpha_lut2_x[1],0,8));
				PE_CCO_VERI_O20_QWr02(sys_veri_25, chroma_face_alpha_lut2_x2, GET_BITS(pp->chroma_face_alpha_lut2_x[2],0,8),\
													  chroma_face_alpha_lut2_x3, GET_BITS(pp->chroma_face_alpha_lut2_x[3],0,8));
				PE_CCO_VERI_O20_QWr02(sys_veri_26, chroma_face_alpha_lut2_y0, GET_BITS(pp->chroma_face_alpha_lut2_y[0],0,10),\
													  chroma_face_alpha_lut2_y1, GET_BITS(pp->chroma_face_alpha_lut2_y[1],0,10));
				PE_CCO_VERI_O20_QWr02(sys_veri_27, chroma_face_alpha_lut2_y2, GET_BITS(pp->chroma_face_alpha_lut2_y[2],0,10),\
													  chroma_face_alpha_lut2_y3, GET_BITS(pp->chroma_face_alpha_lut2_y[3],0,10));

				PE_DCM_HW_O20_DBG_PRINT("[wid:%d] get: \n"\
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
			#if 0	/* O20F20_APB */
				do {
					for(count=0;count<(pstParams->size);count++)
					{
						lut_data = pstParams->data[count];
						PE_CHPI_APB0_O20F20_Wr(dce0.pe1_dce_ia_data[count].hif_dyc_wdata_y,GET_BITS(lut_data,0,10));//y data
						PE_CHPI_APB0_O20F20_Wr(dce0.pe1_dce_ia_data[count].hif_dyc_wdata_x,GET_BITS(lut_data,16,10));//x data
						PE_CHPI_APB0_O20F20_WrFL(dce0.pe1_dce_ia_data[count].udata32);
					}
					PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_DCE0);
				} while(0);
			#endif
			}
		}
		else
		{
			PE_DCM_HW_O20_DBG_PRINT("nothing to do\n"); ret = RET_OK;
		}
	} while (0);
#endif /*PE_HW_O20_BRINGUP*/
	return ret;

}


