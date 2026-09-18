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

/** @file pe_cmg_hw_o26.c
 *
 *  driver for picture enhance color management functions. ( used only within kdriver )
 *	
 *	@author			Seung-Jun,Youm(sj.youm@lge.com)
 *  @modifier		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *	@version		0.1
 *	@note
 *	@date			2012.03.15
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

#include "pe_hw_o26.h"
#include "pe_reg_o26.h"
#include "pe_fwi_o26.h"
#include "pe_inf_o26.h"
#include "pe_cmg_hw_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* Enabling this macro will DISABLE LGSI code refactoring changes, so enable only if there is
any issue in LGSI refactored code. This provision is only for cross checking with original
source. It can be removed in the next version of the code*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMG_HW_O26_ERROR	printk

/* How to turn on _g_cmg_hw_o26_trace ==> echo 0 5 1 > /proc/lg/pe/dbg_kdrv_func */
#define PE_CMG_HW_O26_DBG_PRINT(fmt,args...)	\
	if(_g_cmg_hw_o26_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CMG_HW_O26_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_CMG_HW_O26_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/* see PE_O26_CC_PE1_CEN_IA_DATA_T */
union cen_ia_data {
	UINT32 udata32;
	struct {
	UINT32 hif_cen_y_wdata                  :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 hif_cen_x_wdata                  :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
};

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
__attribute__((unused)) static void PE_CMG_HW_O26_Init_CenRegister(void);
__attribute__((unused)) static void PE_CMG_HW_O26_SetCenRegionCtrlReg(UINT32 i_ui32RegionNum, UINT32 i_ui32wdata);
// static void PE_CMG_HW_O26_CEGetRegGain(UINT32 i_ui32RegionNum, UINT32 *o_ui32RegGain);
//static void PE_CMG_HW_O26_COGetRegGain(UINT32 i_ui32RegionNum, UINT32 *o_ui32RegGain);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static UINT32 _g_cmg_hw_o26_trace=0x0;	//default should be off.
__attribute__((unused)) static PE_CMG_HW_O26_SETTINGS_T _g_pe_cmg_hw_o26_info;
__attribute__((unused)) static UINT32 _g_cmg_hw_o26_pre_dse_lut[(PE_CMG_HW_O26_LUT_MAX-1)];	///<previous dse lut

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init color management
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 count = 0;
	int i=0;
	UINT32 *p_pre_dse_lut = _g_cmg_hw_o26_pre_dse_lut;
	UINT32 dse_lut_data[32] = {\
		   0,  64, 128, 192, 256, 320, 384, 448, 512, \
		 576, 640, 704, 768, 832, 896, 960,1023,1023, \
		1023,1023,1023,1023,1023,1023,1023,1023,1023, \
		1023,1023,1023,1023,1023};
	do{
		CHECK_KNULL(pstParams);
		memset(&_g_pe_cmg_hw_o26_info,0x0,sizeof(PE_CMG_HW_O26_SETTINGS_T));
		_g_pe_cmg_hw_o26_info.dynamic_cm_ui = 0xff;
		_g_pe_cmg_hw_o26_info.pre_cen_bypass = 0xff;
		/*WA. adjust target saturation*/ 
		//_g_pe_cmg_hw_o26_info.org_target_sat = 0x80;
		if(PE_KDRV_VER_O26)
		{
			PE_CMG_HW_O26_Init_CenRegister();
			PE_CC_PE1_O26_QWr02(pe1_cen_ctrl_00,reg_cen_bypass,0x1,demo_mode,0x0);
			/* dse lut init */
			if (!pstParams->resume_mode)	//normal init
			{
				PE_CC_PE1_O26_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_O26_RdFL(pe1_dse_ctrl_02);
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_O26_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CC_PE1_O26_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,dse_lut_data[count]);	//y data
					PE_CC_PE1_O26_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,dse_lut_data[count]);	//x data
					PE_CC_PE1_O26_WrFL(pe1_dse_ia_data);
				}
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CC_PE1_O26_WrFL(pe1_dse_ctrl_02);
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CC_PE1_O26_WrFL(pe1_dse_ia_ctrl);
				for (i=0;i<(PE_CMG_HW_O26_LUT_MAX-1);i++)
				{
					p_pre_dse_lut[i] = ((dse_lut_data[i]<<16)&0x3ff0000)|(dse_lut_data[i]&0x3ff);
				}
				if(_g_cmg_hw_o26_trace)
				{
					PE_CMG_HW_O26_DBG_PRINT("\n init\n");
					PE_CMG_HW_O26_DBG_PRINT("\n   [ i]    x,    y\n");
					for (i=0;i<(PE_CMG_HW_O26_LUT_MAX-1);i++)
					{
						PE_CMG_HW_O26_DBG_PRINT("   [%02d] %4d, %4d\n", \
							i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
					}
				}
			}
			else
			{
				PE_CC_PE1_O26_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_O26_RdFL(pe1_dse_ctrl_02);
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_O26_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<32;count++)
				{
					PE_CC_PE1_O26_Wr01(pe1_dse_ia_data,	hif_dse_wdata_y,GET_BITS(p_pre_dse_lut[count],0,10));	//y data
					PE_CC_PE1_O26_Wr01(pe1_dse_ia_data,	hif_dse_wdata_x,GET_BITS(p_pre_dse_lut[count],16,10));
					PE_CC_PE1_O26_WrFL(pe1_dse_ia_data);
				}
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_y_32nd,1023);	//y data
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_02,	hif_dse_wdata_x_32nd,1023);	//x data
				PE_CC_PE1_O26_WrFL(pe1_dse_ctrl_02);
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_CC_PE1_O26_WrFL(pe1_dse_ia_ctrl);
				if(_g_cmg_hw_o26_trace)
				{
					PE_CMG_HW_O26_DBG_PRINT("\n resume init\n");
					PE_CMG_HW_O26_DBG_PRINT("\n   [ i]    x,    y\n");
					for (i=0;i<(PE_CMG_HW_O26_LUT_MAX-1);i++)
					{
						PE_CMG_HW_O26_DBG_PRINT("   [%02d] %4d, %4d\n", \
							i, (p_pre_dse_lut[i]>>16)&0x3ff, p_pre_dse_lut[i]&0x3ff);
					}
				}
			}
			#if 0	/* O26F22_APB */
			do {
				if (pstParams->resume_mode == 1)	break;//if qsm,skip
				if (!gPE_CHPI_DDR_O26)	break;

				/* DSE0 **********************************************************/
				/* addr */
				PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ctrl_01.uaddr32,0xF4060774);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ctrl_02.uaddr32,0xF4060778);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ia_ctrl_s.uaddr32,0xF406077C);
				for (i=0; i<32; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ia_data[i].uaddr32,0xF4060780);
				}
				PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ia_ctrl_e.uaddr32,0xF406077C);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt0.uaddr32,0xF406078C);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt1.uaddr32,0xF4060790);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt2.uaddr32,0xF4060794);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt3.uaddr32,0xF4060798);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt4.uaddr32,0xF406079C);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt5.uaddr32,0xF40607A0);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt6.uaddr32,0xF40607A4);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt7.uaddr32,0xF40607A8);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt0.uaddr32,0xF40607AC);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt1.uaddr32,0xF40607B0);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt2.uaddr32,0xF40607B4);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt3.uaddr32,0xF40607B8);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt4.uaddr32,0xF40607BC);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt5.uaddr32,0xF40607C0);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt6.uaddr32,0xF40607C4);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt7.uaddr32,0xF40607C8);

				/* init */
				PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ia_ctrl_s.udata32,0x00001000);
				for(i=0; i<32; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ia_data[i].udata32,p_pre_dse_lut[i]);
				}
				PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ia_ctrl_e.udata32,0x00008100);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ctrl_01.udata32,0x80000321);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ctrl_02.udata32,0x03FF03FF);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt0.udata32,0x00003C00);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt1.udata32,0x0000C88C);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt2.udata32,0x000140FF);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt3.udata32,0x000190FF);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt4.udata32,0x0002BCFF);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt5.udata32,0x00034878);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt6.udata32,0x0003703C);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_y_region_pt7.udata32,0x00039800);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt0.udata32,0x0001F100);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt1.udata32,0x000200BE);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt2.udata32,0x00020DF0);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt3.udata32,0x000214FF);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt4.udata32,0x000228FF);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt5.udata32,0x000230FF);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt6.udata32,0x00023FA0);
				PE_CHPI_APB0_O26F22_QWr(dse0.pe_dse_h_region_pt7.udata32,0x00024000);

				/* header */
				PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_DSE0);

				/* VSP0 **********************************************************/
				/* addr */
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_cc_ctrl_01.uaddr32,0xF4061034);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_cc_ctrl_02.uaddr32,0xF4061038);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_cc_ctrl_03.uaddr32,0xF406103C);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_cc_ctrl_04.uaddr32,0xF4061040);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_00.uaddr32,0xF4061050);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_01.uaddr32,0xF4061054);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_02.uaddr32,0xF4061058);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_03.uaddr32,0xF406105C);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_04.uaddr32,0xF4061060);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_05.uaddr32,0xF4061064);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_06.uaddr32,0xF4061068);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_07.uaddr32,0xF406106C);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_08.uaddr32,0xF4061070);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_09.uaddr32,0xF4061074);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_10.uaddr32,0xF4061078);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_11.uaddr32,0xF406107C);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_12.uaddr32,0xF4061080);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_13.uaddr32,0xF4061084);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_14.uaddr32,0xF4061088);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_15.uaddr32,0xF406108C);

				/* init */
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_cc_ctrl_01.udata32,0x40400000);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_cc_ctrl_02.udata32,0xFFFF8080);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_cc_ctrl_03.udata32,0x40400000);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_cc_ctrl_04.udata32,0xFFFF8080);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_00.udata32,0x01F10000);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_01.udata32,0x020000BE);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_02.udata32,0x020D00F0);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_03.udata32,0x021400FF);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_04.udata32,0x022800FF);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_05.udata32,0x023000FF);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_06.udata32,0x023F00A0);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_07.udata32,0x024D0000);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_08.udata32,0x2D6E2000);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_09.udata32,0x46FF39C8);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_10.udata32,0x66FF53FF);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_11.udata32,0x7FFF7DFF);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_12.udata32,0x328C0F00);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_13.udata32,0x64FF50FF);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_14.udata32,0xD278AFFF);
				PE_CHPI_APB0_O26F22_QWr(vsp0.pe1_vsp_crgn_ctrl_15.udata32,0xE600DC3C);

				/* header */
				PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_VSP0);

				/* CW0 **********************************************************/
				/* addr */
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_ctrl_00.uaddr32,0xF40610B0);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_ctrl_01.uaddr32,0xF40610B4);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_ctrl_02.uaddr32,0xF40610B8);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_00.uaddr32,0xF40610C0);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_01.uaddr32,0xF40610C4);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_02.uaddr32,0xF40610C8);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_03.uaddr32,0xF40610CC);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_04.uaddr32,0xF40610D0);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_05.uaddr32,0xF40610D4);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_06.uaddr32,0xF40610D8);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_07.uaddr32,0xF40610DC);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_08.uaddr32,0xF40610E0);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_09.uaddr32,0xF40610E4);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_10.uaddr32,0xF40610E8);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_11.uaddr32,0xF40610EC);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_12.uaddr32,0xF40610F0);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_13.uaddr32,0xF40610F4);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_14.uaddr32,0xF40610F8);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_15.uaddr32,0xF40610FC);

				/* init */
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_ctrl_00.udata32,0x00000100);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_ctrl_01.udata32,0x00C0C0C0);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_ctrl_02.udata32,0x00400000);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_00.udata32,0x000000FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_01.udata32,0x006400FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_02.udata32,0x011C00FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_03.udata32,0x01AA00FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_04.udata32,0x023800FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_05.udata32,0x02C600FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_06.udata32,0x035400FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_07.udata32,0x03FF00FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_08.udata32,0x06FF00FF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_09.udata32,0x12FF0DFF);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_10.udata32,0x198C14DC);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_11.udata32,0x20001D3C);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_12.udata32,0x64643C00);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_13.udata32,0x8CC87896);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_14.udata32,0xBEFFA0E6);
				PE_CHPI_APB0_O26F22_QWr(cw0.pe1_cw_crgn_ctrl_15.udata32,0xFFA0FAFF);

				/* header */
				PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CW0);

				/* CEN0 **********************************************************/
				/* addr */
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s0.uaddr32,0xF4060700);
				for (i=0; i<128; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data0[i].uaddr32,0xF4060704);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s1.uaddr32,0xF4060700);
				for (i=0; i<128; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data1[i].uaddr32,0xF4060704);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s2.uaddr32,0xF4060700);
				for (i=0; i<128; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data2[i].uaddr32,0xF4060704);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s3.uaddr32,0xF4060700);
				for (i=0; i<16; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data3[i].uaddr32,0xF4060704);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s6.uaddr32,0xF4060700);
				for (i=0; i<6; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data6[i].uaddr32,0xF4060704);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_e.uaddr32,0xF4060700);
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_upd_ctrl.uaddr32,0xF40606F8);

				/* init */
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s0.udata32,0x00001000);
				for(i=0; i<128; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data0[i].udata32,0x00000000);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s1.udata32,0x00001100);
				for(i=0; i<128; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data1[i].udata32,0x00000000);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s2.udata32,0x00001200);
				for(i=0; i<128; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data2[i].udata32,0x00000000);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s3.udata32,0x00001300);
				for(i=0; i<16; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data3[i].udata32,0x00000000);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_s6.udata32,0x00001600);
				for(i=0; i<6; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data6[i].udata32,0x00000000);
				}
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_ctrl_e.udata32,0x00008000);
				PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_upd_ctrl.udata32,0x00000001);//cen_lut_update:1

				/* header */
				PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN0);

				/* CEN1 **********************************************************/
				/* addr */
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_00.uaddr32,0xF40606D0);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_01.uaddr32,0xF40606D4);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_02.uaddr32,0xF40605B4);//PE1_APL_STAT_00 - RO not used
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_04.uaddr32,0xF40606E0);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_05.uaddr32,0xF40606E4);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_06.uaddr32,0xF40606E8);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_07.uaddr32,0xF40606EC);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_delta_ia_ctrl_s.uaddr32,0xF4060708);
				for(i=0; i<32; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_delta_ia_data[i].uaddr32,0xF406070C);
				}
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_delta_ia_ctrl_e.uaddr32,0xF4060708);

				/* init */
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_00.udata32,0x000000AC);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_01.udata32,0x00000000);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_02.udata32,0x00008080);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_04.udata32,0x00000000);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_05.udata32,0x00000000);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_06.udata32,0x00000000);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_07.udata32,0x00000000);
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_delta_ia_ctrl_s.udata32,0x00001000);
				for(i=0; i<32; i++)
				{
					PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_delta_ia_data[i].udata32,0x00000000);
				}
				PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_delta_ia_ctrl_e.udata32,0x00008000);

				/* header */
				PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN1);

				PE_INF_HW_O26_BACKUP_CHPI0("[APB][DSE][VSP][CW][CEN]done(resume:%d)",pstParams->resume_mode);
			} while(0);
			#endif
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set cen initial param
 *
 * @param   void
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_CMG_HW_O26_Init_CenRegister(void)
{
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i = 0;

	/* hue */
	PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,	0x00001000);
	PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM*LX_PE_CMG_TBLPOINT); i++)
	{
		PE_CC_PE1_O26_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
	}
	/* saturation */
	PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,	0x00001100);
	PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM*LX_PE_CMG_TBLPOINT); i++)
	{
		PE_CC_PE1_O26_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
	}
	/* value */
	PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,	0x00001200);
	PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM*LX_PE_CMG_TBLPOINT); i++)
	{
		PE_CC_PE1_O26_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
	}
	/* region debug color */
	PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,	0x00001300);
	PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM); i++)
	{
		PE_CC_PE1_O26_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
	}
	/* global delta gain */
	PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,	0x00001600);
	PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_DELTANUM); i++)
	{
		PE_CC_PE1_O26_Wr(pe1_cen_ia_data,0x00000000);
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
	}
	/* normal mode */
	PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,	0x00008000);
	PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);

	/* region delta gain */
	PE_CC_PE1_O26_Wr(pe1_cen_delta_ia_ctrl,	0x00001000);
	PE_CC_PE1_O26_WrFL(pe1_cen_delta_ia_ctrl);
	for(i=0; i<(LX_PE_CMG_REGION_NUM*LX_PE_CMG_DELTA_SETNUM); i++)
	{
		PE_CC_PE1_O26_Wr(pe1_cen_delta_ia_data,0x00000000);
		PE_CC_PE1_O26_WrFL(pe1_cen_delta_ia_data);
	}
	/* normal mode */
	PE_CC_PE1_O26_Wr(pe1_cen_delta_ia_ctrl,	0x00008000);
	PE_CC_PE1_O26_WrFL(pe1_cen_delta_ia_ctrl);

	/* master gain */
	PE_CC_PE1_O26_Wr(pe1_cen_ctrl_04,	0x00000000);
	PE_CC_PE1_O26_WrFL(pe1_cen_ctrl_04);
	PE_CC_PE1_O26_Wr(pe1_cen_ctrl_05,	0x00000000);
	PE_CC_PE1_O26_WrFL(pe1_cen_ctrl_05);
	PE_CC_PE1_O26_Wr(pe1_cen_ctrl_06,	0x00000000);
	PE_CC_PE1_O26_WrFL(pe1_cen_ctrl_06);
	PE_CC_PE1_O26_Wr(pe1_cen_ctrl_07,	0x00000000);
	PE_CC_PE1_O26_WrFL(pe1_cen_ctrl_07);
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}
/**
 * debug setting
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_HW_O26_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CMG)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmg_hw_o26_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CMG)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if(PE_KDRV_VER_O26)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMG)))
				{
					PE_CMG_HW_O26_DBG_PRINT("cen bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_00,	reg_cen_bypass,	0x0);	//CEN block OFF
					}
				}
				else
				{
					PE_CMG_HW_O26_DBG_PRINT("cen on.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_00,	reg_cen_bypass,	0x1);	//CEN block ON
					}
				}
			}
			else
			{
				PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set cen enable
 *
 * @param   *pstParams [in] LX_PE_CMG_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetCenEnable(LX_PE_CMG_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_HW_O26_DBG_PRINT(" set[%d]: cen enable:%d\n",pstParams->win_id,pstParams->enable);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_00,	reg_cen_bypass,	GET_BITS(pstParams->enable,0,1));
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get cen enable
 *
 * @param   *pstParams [in/out] LX_PE_CMG_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_GetCenEnable(LX_PE_CMG_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CE_PE1_O26_QRd01(pe1_cen_ctrl_00,	reg_cen_bypass,	pstParams->enable);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O26_QRd01(pe1_cen_ctrl_00,	reg_cen_bypass,	pstParams->enable);
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMG_HW_O26_DBG_PRINT(" get[%d]: cen enable:%d\n",pstParams->win_id,pstParams->enable);
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set cen region enable
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 wdata=0;
	UINT32 count=0;
	LX_PE_CMG_REGION_ENABLE_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_REGION_ENABLE_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_REGION_ENABLE_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_REGION_ENABLE_T\n");
			ret=RET_OK;
			break;
		}
		for(count=0;count<LX_PE_CMG_REGION_NUM;count++)
		{
			if(pstParams->enable[count])
				wdata |= (0x1<<(count+LX_PE_CMG_REGION_NUM));
			else
				wdata &= ~(0x1<<(count+LX_PE_CMG_REGION_NUM));

			if(pstParams->show_region[count])
				wdata |= (0x1<<(count));
			else
				wdata &= ~(0x1<<(count));
		}
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_O26_Wr(pe1_cen_ctrl_01,wdata);
				PE_CC_PE1_O26_WrFL(pe1_cen_ctrl_01);
				#if 1	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_01.udata32,wdata);
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN1);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get cen region enable
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_GetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 rdata=0;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_O26_RdFL(pe1_cen_ctrl_01);
				rdata = PE_CC_PE1_O26_Rd(pe1_cen_ctrl_01);
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O26_RdFL(pe1_cen_ctrl_01);
				rdata = PE_CO_PE1_O26_Rd(pe1_cen_ctrl_01);
			}*/
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		for(count=0;count<LX_PE_CMG_REGION_NUM;count++)
		{
			if(rdata & (0x1<<(count+LX_PE_CMG_REGION_NUM)))
				pstParams->enable[count] = 1;
			else
				pstParams->enable[count] = 0;

			if(rdata & (0x1<<(count)))
				pstParams->show_region[count] = 1;
			else
				pstParams->show_region[count] = 0;
		}
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetCenRegion2(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 x_wdata,y_wdata;
	UINT32 set_flag=0;
	PE_CMG_HW_O26_SETTINGS_T *pInfo=&_g_pe_cmg_hw_o26_info;
	LX_PE_CMG_REGION2_T *pp;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_REGION2_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	union cen_ia_data hue_data[LX_PE_CMG_TBLPOINT];
	union cen_ia_data sat_data[LX_PE_CMG_TBLPOINT];
	union cen_ia_data val_data[LX_PE_CMG_TBLPOINT];

	do {
		CHECK_KNULL(pstParams);
		pp = (LX_PE_CMG_REGION2_T*)pstParams;
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_REGION_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_REGION_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMG_HW_O26_CHECK_CODE(pp->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"[%s,%d] region_num(%d) is out of range.\n",__F__,__L__,pp->region_num);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				set_flag = 0;
				/* check double setting */
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					if(pInfo->rgn_set[pp->region_num].hue_x[count]!=pp->hue_x[count] || \
						pInfo->rgn_set[pp->region_num].hue_g[count]!=pp->hue_g[count] || \
						pInfo->rgn_set[pp->region_num].sat_x[count]!=pp->sat_x[count] || \
						pInfo->rgn_set[pp->region_num].sat_g[count]!=pp->sat_g[count] || \
						pInfo->rgn_set[pp->region_num].val_x[count]!=pp->val_x[count] || \
						pInfo->rgn_set[pp->region_num].val_g[count]!=pp->val_g[count])
					{
						set_flag=1;
						break;
					}
				}
				if(set_flag)
				{
					PE_CMG_HW_O26_DBG_PRINT(" set region : num:%d\n", pp->region_num);
					PE_CC_PE1_O26_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable,      0x0, 	//[15] 0:host access, 1:normal mode
																hif_cen_ai,      0x1,	//[12] ai 0:disable, 1:enable
																hif_cen_address, 0x0);	//[7:0] address
					start_addr = pp->region_num*LX_PE_CMG_TBLPOINT;
					/* H color region table : 000 */
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);			//[10:8]
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						/* hue_x,x_wdata : 0~1024(0~720 degree) */
						x_wdata = (UINT32)GET_BITS(pp->hue_x[count],0,10);
						y_wdata = GET_BITS(pp->hue_g[count],0,7);	// 0~127
						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);

						hue_data[count].hif_cen_x_wdata = x_wdata;
						hue_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* S color region table : 001 */
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);			//[10:8]
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						x_wdata = GET_BITS(pp->sat_x[count],0,7);	// 0~100
						y_wdata = GET_BITS(pp->sat_g[count],0,7);	// 0~127

						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);

						sat_data[count].hif_cen_x_wdata = x_wdata;
						sat_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* V color region table : 010 */
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);			//[10:8]
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						x_wdata = GET_BITS(pp->val_x[count],0,8);	// 0~255
						y_wdata = GET_BITS(pp->val_g[count],0,7);	// 0~127

						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);

						val_data[count].hif_cen_x_wdata = x_wdata;
						val_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* normal operation */
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
					PE_CC_PE1_O26_QWr01(pe1_cen_upd_ctrl,	cen_lut_update, 	0x1);	//[0] cen_lut_update
					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						pInfo->rgn_set[pp->region_num].hue_x[count]=pp->hue_x[count];
						pInfo->rgn_set[pp->region_num].hue_g[count]=pp->hue_g[count];
						pInfo->rgn_set[pp->region_num].sat_x[count]=pp->sat_x[count];
						pInfo->rgn_set[pp->region_num].sat_g[count]=pp->sat_g[count];
						pInfo->rgn_set[pp->region_num].val_x[count]=pp->val_x[count];
						pInfo->rgn_set[pp->region_num].val_g[count]=pp->val_g[count];
					}

					#if 1	/* O26F22_APB */
					do {
						if (!gPE_CHPI_DDR_O26)	break;
						/* H color region table : 000 */
						for (count=0; count<LX_PE_CMG_TBLPOINT; count++)
						{
							PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data0[count+start_addr].udata32,hue_data[count].udata32);
						}
						/* S color region table : 001 */
						for (count=0; count<LX_PE_CMG_TBLPOINT; count++)
						{
							PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data1[count+start_addr].udata32,sat_data[count].udata32);
						}
						/* V color region table : 010 */
						for (count=0; count<LX_PE_CMG_TBLPOINT; count++)
						{
							PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data2[count+start_addr].udata32,val_data[count].udata32);
						}
						PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN0);
					} while(0);
					#endif
				}
				switch(pp->region_num)
				{
					case 0:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_0, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 1:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_1, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 2:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_2, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 3:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_3, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 4:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_4, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 5:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_5, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 6:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_6, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 7:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_7, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 8:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_8, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 9:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_9, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 10:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_10, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 11:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_11, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 12:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_12, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 13:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_13, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 14:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_14, 	GET_BITS(pp->aiGainNum,0,2));
						break;
					case 15:
						PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_08,	reg_ai_gain_sel_15, 	GET_BITS(pp->aiGainNum,0,2));
						break;
				}
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 x_wdata,y_wdata;
	UINT32 set_flag=0;
	PE_CMG_HW_O26_SETTINGS_T *pInfo=&_g_pe_cmg_hw_o26_info;
	LX_PE_CMG_REGION_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_REGION_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	union cen_ia_data hue_data[LX_PE_CMG_TBLPOINT];
	union cen_ia_data sat_data[LX_PE_CMG_TBLPOINT];
	union cen_ia_data val_data[LX_PE_CMG_TBLPOINT];

	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_REGION_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_REGION_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMG_HW_O26_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"[%s,%d] region_num(%d) is out of range.\n",__F__,__L__,pstParams->region_num);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				set_flag = 0;
				/* check double setting */
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					if(pInfo->rgn_set[pstParams->region_num].hue_x[count]!=pstParams->hue_x[count] || \
						pInfo->rgn_set[pstParams->region_num].hue_g[count]!=pstParams->hue_g[count] || \
						pInfo->rgn_set[pstParams->region_num].sat_x[count]!=pstParams->sat_x[count] || \
						pInfo->rgn_set[pstParams->region_num].sat_g[count]!=pstParams->sat_g[count] || \
						pInfo->rgn_set[pstParams->region_num].val_x[count]!=pstParams->val_x[count] || \
						pInfo->rgn_set[pstParams->region_num].val_g[count]!=pstParams->val_g[count])
					{
						set_flag=1;
						break;
					}
				}
				if(set_flag)
				{
					PE_CMG_HW_O26_DBG_PRINT(" set region : num:%d\n", pstParams->region_num);
					PE_CC_PE1_O26_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable,      0x0, 	//[15] 0:host access, 1:normal mode
																hif_cen_ai,      0x1,	//[12] ai 0:disable, 1:enable
																hif_cen_address, 0x0);	//[7:0] address
					start_addr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
					/* H color region table : 000 */
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);			//[10:8]
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						/* hue_x,x_wdata : 0~1024(0~720 degree) */
						x_wdata = (UINT32)GET_BITS(pstParams->hue_x[count],0,10);
						y_wdata = GET_BITS(pstParams->hue_g[count],0,7);	// 0~127
						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);

						hue_data[count].hif_cen_x_wdata = x_wdata;
						hue_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* S color region table : 001 */
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);			//[10:8]
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						x_wdata = GET_BITS(pstParams->sat_x[count],0,7);	// 0~100
						y_wdata = GET_BITS(pstParams->sat_g[count],0,7);	// 0~127

						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);

						sat_data[count].hif_cen_x_wdata = x_wdata;
						sat_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* V color region table : 010 */
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);			//[10:8]
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						x_wdata = GET_BITS(pstParams->val_x[count],0,8);	// 0~255
						y_wdata = GET_BITS(pstParams->val_g[count],0,7);	// 0~127

						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_CC_PE1_O26_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);

						val_data[count].hif_cen_x_wdata = x_wdata;
						val_data[count].hif_cen_y_wdata = y_wdata;
					}
					/* normal operation */
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
					PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
					PE_CC_PE1_O26_QWr01(pe1_cen_upd_ctrl,	cen_lut_update, 	0x1);	//[0] cen_lut_update
					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						pInfo->rgn_set[pstParams->region_num].hue_x[count]=pstParams->hue_x[count];
						pInfo->rgn_set[pstParams->region_num].hue_g[count]=pstParams->hue_g[count];
						pInfo->rgn_set[pstParams->region_num].sat_x[count]=pstParams->sat_x[count];
						pInfo->rgn_set[pstParams->region_num].sat_g[count]=pstParams->sat_g[count];
						pInfo->rgn_set[pstParams->region_num].val_x[count]=pstParams->val_x[count];
						pInfo->rgn_set[pstParams->region_num].val_g[count]=pstParams->val_g[count];
					}

					#if 1	/* O26F22_APB */
					do {
						if (!gPE_CHPI_DDR_O26)	break;
						/* H color region table : 000 */
						for (count=0; count<LX_PE_CMG_TBLPOINT; count++)
						{
							PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data0[count+start_addr].udata32,hue_data[count].udata32);
						}
						/* S color region table : 001 */
						for (count=0; count<LX_PE_CMG_TBLPOINT; count++)
						{
							PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data1[count+start_addr].udata32,sat_data[count].udata32);
						}
						/* V color region table : 010 */
						for (count=0; count<LX_PE_CMG_TBLPOINT; count++)
						{
							PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data2[count+start_addr].udata32,val_data[count].udata32);
						}
						PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN0);
					} while(0);
					#endif
				}
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetCenRegionAll(LX_PE_CMG_REGION_ALL_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, j, k;
	union cen_ia_data hue_data[128];
	union cen_ia_data sat_data[128];
	union cen_ia_data val_data[128];
	static LX_PE_CMG_REGION_ALL_T prevParams;
	static UINT32 initCenRegion = 0;

	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);

		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				if (initCenRegion == 0)
				{
					PE_PRINT_NOTI("set 1st\n");
					initCenRegion = 1;
				}
				else if (memcmp(&prevParams, pstParams, sizeof(LX_PE_CMG_REGION_ALL_T))==0)
				{
					PE_CMG_HW_O26_DBG_PRINT("set skip\n");
					break;
				}
				else
				{
					PE_CMG_HW_O26_DBG_PRINT("set region\n");
				}

				memcpy(&prevParams, pstParams, sizeof(LX_PE_CMG_REGION_ALL_T));

				//LX_PE_CMG_REGION_NUM:16, LX_PE_CMG_TBLPOINT:8
				for (i=0; i<LX_PE_CMG_REGION_NUM; i++)
				{
					for (j=0; j<LX_PE_CMG_TBLPOINT; j++)
					{
						k = (i*LX_PE_CMG_TBLPOINT) + j;

						/* hue, x:0~1024(0~720 degree) */
						hue_data[k].hif_cen_x_wdata = (UINT32)GET_BITS(pstParams->cen_region_lut[i].hue_x[j],0,10);
						hue_data[k].hif_cen_y_wdata = GET_BITS(pstParams->cen_region_lut[i].hue_g[j],0,7);// 0~127

						/* saturation */
						sat_data[k].hif_cen_x_wdata = GET_BITS(pstParams->cen_region_lut[i].sat_x[j],0,7);// 0~100
						sat_data[k].hif_cen_y_wdata = GET_BITS(pstParams->cen_region_lut[i].sat_g[j],0,7);// 0~127

						/* value */
						val_data[k].hif_cen_x_wdata = GET_BITS(pstParams->cen_region_lut[i].val_x[j],0,8);// 0~255
						val_data[k].hif_cen_y_wdata = GET_BITS(pstParams->cen_region_lut[i].val_g[j],0,7);// 0~127
					}
				}

				//[10:8] reg_cen_ai_sel
				//'000'  H Color region table  :  range of address 0 ~ 127
				//'001'  S Color region table  :  range of address 0 ~ 127
				//'010'  V Color region table  :  range of address 0 ~ 127
				//'011'  Color of Region  : range of address 0 ~ 15
				//'110'  Global Delta gain : range of address 0 ~ 5

				/* H color region table : 000 */
				PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,0x00001000);//[15] 0:host access,[12] ai 1:enable,[7:0] address 0
				PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for (i=0; i<128; i++)
				{
					PE_CC_PE1_O26_Wr(pe1_cen_ia_data,hue_data[i].udata32);
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
				}
				/* S color region table : 001 */
				PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,0x00001100);//[15] 0:host access,[12] ai 1:enable,[7:0] address 0
				PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for (i=0; i<128; i++)
				{
					PE_CC_PE1_O26_Wr(pe1_cen_ia_data,sat_data[i].udata32);
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
				}
				/* V color region table : 010 */
				PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,0x00001200);//[15] 0:host access,[12] ai 1:enable,[7:0] address 0
				PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for (i=0; i<128; i++)
				{
					PE_CC_PE1_O26_Wr(pe1_cen_ia_data,val_data[i].udata32);
					PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
				}
				/* normal mode */
				PE_CC_PE1_O26_Wr(pe1_cen_ia_ctrl,0x00008000);//[15] 1:normal mode,[12] ai 0:disable,[7:0] address 0
				PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);

				/* lut update */
				PE_CC_PE1_O26_QWr01(pe1_cen_upd_ctrl,cen_lut_update,0x1);//[0] cen_lut_update

				#if 1	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					/* H color region table : 000 */
					for (i=0; i<128; i++)
					{
						PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data0[i].udata32,hue_data[i].udata32);
					}
					/* S color region table : 001 */
					for (i=0; i<128; i++)
					{
						PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data1[i].udata32,sat_data[i].udata32);
					}
					/* V color region table : 010 */
					for (i=0; i<128; i++)
					{
						PE_CHPI_APB0_O26F22_QWr(cen0.pe1_cen_ia_data2[i].udata32,val_data[i].udata32);
					}
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

#if 0
static void PE_CMG_HW_O26_CallbackDelayedCenLut(struct work_struct *work)
{
	int i;
	UINT32 cen_lut_status=0xff;
	PE_CMG_HW_O26_SETTINGS_T *pInfo=&_g_pe_cmg_hw_o26_info;
	UINT32 region_num = pInfo->delayed_cmg_lut.cmg_region_ctrl.region_num;


	PE_DEBUG("\n\nRetry Cen Lut setting!\n\n\r");

	PE_CC_PE1_O26_QRd01(pe1_cen_upd_ctrl, cen_lut_status, cen_lut_status);
	if(cen_lut_status != 0)
	{
		schedule_delayed_work(&pInfo->delayed_cmg_lut[region_num].dlyWork, msecs_to_jiffies(10));
	}
	else
	{
		PE_CMG_HW_O26_DBG_PRINT(" set region : num:%d\n", pstParams->region_num);
		PE_CC_PE1_O26_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	 0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 	 0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address, 0x0);	//[7:0] address
		start_addr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
		/* H color region table : 000 */
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_ai_sel, 	0x0);			//[10:8]
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_address,	start_addr);	//[7:0] address
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
	
		for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
		{
			/* hue_x,x_wdata : 0~1024(0~720 degree) */
			x_wdata = (UINT32)GET_BITS(pstParams->hue_x[count],0,10);
			y_wdata = GET_BITS(pstParams->hue_g[count],0,7);	// 0~127
			PE_CC_PE1_O26_Wr01(pe1_cen_ia_data, hif_cen_x_wdata,	x_wdata);	//[25:16] x data
			PE_CC_PE1_O26_Wr01(pe1_cen_ia_data, hif_cen_y_wdata,	y_wdata);	//[9:0] y data
			PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
		}
		/* S color region table : 001 */
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_ai_sel, 	0x1);			//[10:8]
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_address,	start_addr);	//[7:0] address
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
		for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
		{
			x_wdata = GET_BITS(pstParams->sat_x[count],0,7);	// 0~100
			y_wdata = GET_BITS(pstParams->sat_g[count],0,7);	// 0~127
	
			PE_CC_PE1_O26_Wr01(pe1_cen_ia_data, hif_cen_x_wdata,	x_wdata);	//[25:16] x data
			PE_CC_PE1_O26_Wr01(pe1_cen_ia_data, hif_cen_y_wdata,	y_wdata);	//[9:0] y data
			PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
		}
		/* V color region table : 010 */
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_ai_sel, 	0x2);			//[10:8]
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_address,	start_addr);	//[7:0] address
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
	
		for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
		{
			x_wdata = GET_BITS(pstParams->val_x[count],0,8);	// 0~255
			y_wdata = GET_BITS(pstParams->val_g[count],0,7);	// 0~127
	
			PE_CC_PE1_O26_Wr01(pe1_cen_ia_data, hif_cen_x_wdata,	x_wdata);	//[25:16] x data
			PE_CC_PE1_O26_Wr01(pe1_cen_ia_data, hif_cen_y_wdata,	y_wdata);	//[9:0] y data
			PE_CC_PE1_O26_WrFL(pe1_cen_ia_data);
		}
		/* normal operation */
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_ai_sel, 	0x0);	//[10:8]
		PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl, hif_cen_address,	0x0);	//[7:0] address
		PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
		PE_CC_PE1_O26_QWr01(pe1_cen_upd_ctrl,	cen_lut_update, 	0x1);	//[0] cen_lut_update
		for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
		{
			pInfo->rgn_set[pstParams->region_num].hue_x[count]=pstParams->hue_x[count];
			pInfo->rgn_set[pstParams->region_num].hue_g[count]=pstParams->hue_g[count];
			pInfo->rgn_set[pstParams->region_num].sat_x[count]=pstParams->sat_x[count];
			pInfo->rgn_set[pstParams->region_num].sat_g[count]=pstParams->sat_g[count];
			pInfo->rgn_set[pstParams->region_num].val_x[count]=pstParams->val_x[count];
			pInfo->rgn_set[pstParams->region_num].val_g[count]=pstParams->val_g[count];
		}
	}

}
#endif
/**
 * get cen region
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_GetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 x_wdata=0,y_wdata=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_HW_O26_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"[%s,%d] region_num(%d) is out of range.\n",__F__,__L__,pstParams->region_num);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		start_addr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_O26_RdFL(pe1_cen_ia_ctrl);
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0);	//[15] 0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x1);	//[12] ai 0:disable, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address

				/* H color region table : 000 */
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);		//[10:8]
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CC_PE1_O26_RdFL(pe1_cen_ia_data);
					PE_CC_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CC_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data
					/* x_wdata,hue_x 0~1024 (0~720 degree) */
					pstParams->hue_x[count] = (UINT16)GET_BITS(x_wdata,0,10);
					pstParams->hue_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* S color region table : 001 */
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);		//[10:8]
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CC_PE1_O26_RdFL(pe1_cen_ia_data);
					PE_CC_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CC_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data
					pstParams->sat_x[count] = (UINT8)GET_BITS(x_wdata,0,7);	// 0~100
					pstParams->sat_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* V color region table : 010 */
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);		//[10:8]
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CC_PE1_O26_RdFL(pe1_cen_ia_data);
					PE_CC_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CC_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					pstParams->val_x[count] = (UINT8)GET_BITS(x_wdata,0,8);	// 0~255
					pstParams->val_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* normal operation */
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_CC_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_CC_PE1_O26_WrFL(pe1_cen_ia_ctrl);
			}
			#if 0
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O26_RdFL(pe1_cen_ia_ctrl);
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0);	//[15] 0:host access, 1:normal mode
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x1);	//[12] ai 0:disable, 1:enable
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address

				/* H color region table : 000 */
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);		//[10:8]
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CO_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CO_PE1_O26_RdFL(pe1_cen_ia_data);
					PE_CO_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CO_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data
					/* x_wdata,hue_x 0~1024 (0~720 degree) */
					pstParams->hue_x[count] = (UINT16)GET_BITS(x_wdata,0,10);
					pstParams->hue_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* S color region table : 001 */
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);		//[10:8]
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CO_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CO_PE1_O26_RdFL(pe1_cen_ia_data);
					PE_CO_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CO_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data
					pstParams->sat_x[count] = (UINT8)GET_BITS(x_wdata,0,7);	// 0~100
					pstParams->sat_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* V color region table : 010 */
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);		//[10:8]
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	start_addr); //[7:0] address
				PE_CO_PE1_O26_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_CO_PE1_O26_RdFL(pe1_cen_ia_data);
					PE_CO_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_CO_PE1_O26_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					pstParams->val_x[count] = (UINT8)GET_BITS(x_wdata,0,8);	// 0~255
					pstParams->val_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* normal operation */
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_CO_PE1_O26_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_CO_PE1_O26_WrFL(pe1_cen_ia_ctrl);
			}
			#endif
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set cen region ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 delta[3];		// -128 ~ 127, hsv or gbr
	UINT32 wdata=0;
	UINT32 region_num=0;
	PE_CMG_HW_O26_SETTINGS_T *pInfo=&_g_pe_cmg_hw_o26_info;
	LX_PE_CMG_REGION_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_REGION_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_REGION_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_REGION_CTRL_T\n");
			ret=RET_OK;
			break;
		}

		PE_CMG_HW_O26_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"[%s,%d] region_num(%d) is out of range.\n",__F__,__L__,pstParams->region_num);

		PE_CMG_HW_O26_DBG_PRINT(" set: path:%d num:%d, m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n",\
				pstParams->win_id,pstParams->region_num,pstParams->master_gain,\
				pstParams->region_delta[0],pstParams->region_delta[1],pstParams->region_delta[2],\
				pstParams->region_delta[3],pstParams->region_delta[4],pstParams->region_delta[5]);

		region_num = pstParams->region_num;

		if(PE_KDRV_VER_O26) 
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				pInfo->dynamic_cm_ui = pstParams->dynamic_ui;
				/* region delta */
				if(pInfo->rgn_ctrl[region_num].region_delta[0]!=pstParams->region_delta[0] || \
					pInfo->rgn_ctrl[region_num].region_delta[1]!=pstParams->region_delta[1] || \
					pInfo->rgn_ctrl[region_num].region_delta[2]!=pstParams->region_delta[2] || \
					pInfo->rgn_ctrl[region_num].region_delta[3]!=pstParams->region_delta[3] || \
					pInfo->rgn_ctrl[region_num].region_delta[4]!=pstParams->region_delta[4] || \
					pInfo->rgn_ctrl[region_num].region_delta[5]!=pstParams->region_delta[5])
				{

					PE_CMG_HW_O26_DBG_PRINT(" set delta\n");

					start_addr = region_num*LX_PE_CMG_DELTA_SETNUM;

					PE_CC_PE1_O26_RdFL(pe1_cen_delta_ia_ctrl);
					PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x0);	//[15] 0:host access, 1:normal mode
					PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x1);	//[12] ai 0:disable, 1:enable
					PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,start_addr);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_delta_ia_ctrl);

					for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++) 
					{

						wdata=0;

						delta[0] = GET_BITS(pstParams->region_delta[count*3],0,8);		// -128 ~ 127
						delta[1] = GET_BITS(pstParams->region_delta[count*3+1],0,8);	// -128 ~ 127
						delta[2] = GET_BITS(pstParams->region_delta[count*3+2],0,8);	// -128 ~ 127

						wdata = (delta[0]<<16)|(delta[1]<<8)|(delta[2]);

						PE_CC_PE1_O26_Wr(pe1_cen_delta_ia_data,	wdata);
						PE_CC_PE1_O26_WrFL(pe1_cen_delta_ia_data);
					}

					PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x1);	//[15] 0:host access, 1:normal mode
					PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x0);	//[12] ai 0:disable, 1:enable
					PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,0x0);	//[7:0] address
					PE_CC_PE1_O26_WrFL(pe1_cen_delta_ia_ctrl);

					pInfo->rgn_ctrl[region_num].region_delta[0]=pstParams->region_delta[0];
					pInfo->rgn_ctrl[region_num].region_delta[1]=pstParams->region_delta[1];
					pInfo->rgn_ctrl[region_num].region_delta[2]=pstParams->region_delta[2];
					pInfo->rgn_ctrl[region_num].region_delta[3]=pstParams->region_delta[3];
					pInfo->rgn_ctrl[region_num].region_delta[4]=pstParams->region_delta[4];
					pInfo->rgn_ctrl[region_num].region_delta[5]=pstParams->region_delta[5];
					#if 1	/* O26F22_APB */
					do {
						if (!gPE_CHPI_DDR_O26)	break;
						for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++)
						{
							wdata=0;
							delta[0] = GET_BITS(pstParams->region_delta[count*3],0,8);		// -128 ~ 127
							delta[1] = GET_BITS(pstParams->region_delta[count*3+1],0,8);	// -128 ~ 127
							delta[2] = GET_BITS(pstParams->region_delta[count*3+2],0,8);	// -128 ~ 127
							wdata = (delta[0]<<16)|(delta[1]<<8)|(delta[2]);
							PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_delta_ia_data[start_addr+count].udata32,wdata);
						}
						PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN1);
					} while(0);
					#endif
				}

				/* region gain */
				if(pInfo->rgn_ctrl[region_num].master_gain!=pstParams->master_gain) {

					PE_CMG_HW_O26_DBG_PRINT(" set master_gain\n");

					wdata = GET_BITS(pstParams->master_gain,0,8);	// 0~128~255

					PE_CMG_HW_O26_SetCenRegionCtrlReg(region_num, wdata);

					pInfo->rgn_ctrl[region_num].master_gain=pstParams->master_gain;
				}
			}
		}
		else 
		{

			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}

	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * get cen region ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	UINT32 start_addr=0;
	UINT32 re_mgain=0;
	UINT32 re_delta[LX_PE_CMG_DELTA_SETNUM];	// hsv or gbr

	do {

		CHECK_KNULL(pstParams);

		PE_CHECK_WINID(pstParams->win_id);

		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(win_id)) {

				/* region delta */
				start_addr = pstParams->region_num*LX_PE_CMG_DELTA_SETNUM;
				PE_CC_PE1_O26_RdFL(pe1_cen_delta_ia_ctrl);
				PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x0);	//[15] 0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x1);	//[12] ai 0:disable, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,start_addr);	//[7:0] address
				PE_CC_PE1_O26_WrFL(pe1_cen_delta_ia_ctrl);

				for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++) {

					PE_CC_PE1_O26_RdFL(pe1_cen_delta_ia_data);
					re_delta[count] = PE_CC_PE1_O26_Rd(pe1_cen_delta_ia_data);
				}

				PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x1);	//[15] 0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x0);	//[12] ai 0:disable, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,0x0);	//[7:0] address
				PE_CC_PE1_O26_WrFL(pe1_cen_delta_ia_ctrl);

				/* region gain */
				PE_CMG_HW_O26_CEGetRegGain(pstParams->region_num, &re_mgain);

				pstParams->master_gain = (UINT8)GET_BITS(re_mgain,0,8);	// region master gain, 0~128~255
				pstParams->region_delta[0] = (SINT8)GET_BITS(re_delta[0],16,8);	// h, -128 ~ 127
				pstParams->region_delta[1] = (SINT8)GET_BITS(re_delta[0],8,8);	// s, -128 ~ 127
				pstParams->region_delta[2] = (SINT8)GET_BITS(re_delta[0],0,8);	// v, -128 ~ 127
				pstParams->region_delta[3] = (SINT8)GET_BITS(re_delta[1],16,8);	// g, -128 ~ 127
				pstParams->region_delta[4] = (SINT8)GET_BITS(re_delta[1],8,8);	// b, -128 ~ 127
				pstParams->region_delta[5] = (SINT8)GET_BITS(re_delta[1],0,8);	// r, -128 ~ 127
			}
			#if 0	//not used
			if(PE_CHECK_WIN1(win_id)) {

				/* region delta */
				start_addr = pstParams->region_num*LX_PE_CMG_DELTA_SETNUM;
				PE_CO_PE1_O26_RdFL(pe1_cen_delta_ia_ctrl);
				PE_CO_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x0);	//[15] 0:host access, 1:normal mode
				PE_CO_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x1);	//[12] ai 0:disable, 1:enable
				PE_CO_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,start_addr);	//[7:0] address
				PE_CO_PE1_O26_WrFL(pe1_cen_delta_ia_ctrl);

				for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++) {

					PE_CO_PE1_O26_RdFL(pe1_cen_delta_ia_data);
					re_delta[count] = PE_CO_PE1_O26_Rd(pe1_cen_delta_ia_data);
				}

				PE_CO_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_enable, 0x1);	//[15] 0:host access, 1:normal mode
				PE_CO_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_ai, 	0x0);	//[12] ai 0:disable, 1:enable
				PE_CO_PE1_O26_Wr01(pe1_cen_delta_ia_ctrl,	hif_cen_delta_address,0x0);	//[7:0] address
				PE_CO_PE1_O26_WrFL(pe1_cen_delta_ia_ctrl);

				/* region gain */
				PE_CMG_HW_O26_COGetRegGain(pstParams->region_num, &re_mgain);

				pstParams->master_gain = (UINT8)GET_BITS(re_mgain,0,8);	// region master gain, 0~128~255
				pstParams->region_delta[0] = (SINT8)GET_BITS(re_delta[0],16,8);	// h, -128 ~ 127
				pstParams->region_delta[1] = (SINT8)GET_BITS(re_delta[0],8,8);	// s, -128 ~ 127
				pstParams->region_delta[2] = (SINT8)GET_BITS(re_delta[0],0,8);	// v, -128 ~ 127
				pstParams->region_delta[3] = (SINT8)GET_BITS(re_delta[1],16,8);	// g, -128 ~ 127
				pstParams->region_delta[4] = (SINT8)GET_BITS(re_delta[1],8,8);	// b, -128 ~ 127
				pstParams->region_delta[5] = (SINT8)GET_BITS(re_delta[1],0,8);	// r, -128 ~ 127
			}
			#endif
		}
		else
		{

			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}

		PE_CMG_HW_O26_DBG_PRINT(" Get: path:%d num:%d, m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n",\
				pstParams->win_id,pstParams->region_num,pstParams->master_gain,\
				pstParams->region_delta[0],pstParams->region_delta[1],pstParams->region_delta[2],\
				pstParams->region_delta[3],pstParams->region_delta[4],pstParams->region_delta[5]);

	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set cen color ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_COLOR_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	LX_PE_CMG_COLOR_CTRL_T *pp =  pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_SHP_RE_EASY_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_CMG_COLOR_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			//PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_COLOR_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMG_HW_O26_DBG_PRINT("set pstParams[%d] : sat:%d\n", \
			pstParams->win_id,pstParams->saturation);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_02, ihsv_sgain,	GET_BITS(pstParams->saturation,0,8));//[7:0] reg_ihsv_sgain

				/* O26F22_APB do not set bc dc DC control build in F20*/ 
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get cen color ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_COLOR_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_GetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 rdata=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
				pstParams->saturation=(UINT16)rdata;
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O26_QRd01(pe1_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
				pstParams->saturation=(UINT16)rdata;
			}*/
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMG_HW_O26_DBG_PRINT("get pstParams[%d] : sat:%d\n",pstParams->win_id,pstParams->saturation);
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set clear white
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	PE_REG_O26_HW_OPT_T hw_opt = PE_REG_O26_GetDispOpt();
	LX_PE_CMG_CW_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_CW_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_CW_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_CW_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMG_HW_O26_DBG_PRINT("set[%d] en:%d, yc:%d, x:%d,%d,%d,%d,%d\n"\
			" y:%d,%d,%d,%d,%d, sel:0x%x, g:%d\n", \
			pstParams->win_id, pstParams->cw_en, \
			pstParams->gain_sel, pstParams->gain_x[0], \
			pstParams->gain_x[1], pstParams->gain_x[2], pstParams->gain_x[3], \
			pstParams->gain_x[4], pstParams->gain_y[0], pstParams->gain_y[1], \
			pstParams->gain_y[2], pstParams->gain_y[3], pstParams->gain_y[4], \
			pstParams->region_sel, pstParams->region_gain);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				if (hw_opt.external_chip==0)
				{
					PE_CC2_PE1_O26_QWr01(pe1_cw_ctrl_00, reg_cw_en,				GET_BITS(pstParams->cw_en,0,1));
				}
				else
				{
					PE_CC2_PE1_O26_QWr01(pe1_cw_ctrl_00, reg_cw_en,				0x0);
				}
				#if 0
				PE_CEO_PE1_O26_QWr04(pe1_cw_ctrl_00, reg_cw_en,				GET_BITS(pstParams->cw_en,0,1),\
														cw_gain_selection,	GET_BITS(pstParams->gain_sel,0,1),\
														reg_cw_y4,			GET_BITS(pstParams->gain_y[4],0,8),\
														reg_cw_x4,			GET_BITS(pstParams->gain_x[4],0,8));
				PE_CEO_PE1_O26_QWr04(pe1_cw_ctrl_03, reg_cw_y0,			GET_BITS(pstParams->gain_y[0],0,8),\
														reg_cw_x0,			GET_BITS(pstParams->gain_x[0],0,8),\
														reg_cw_y1,			GET_BITS(pstParams->gain_y[1],0,8),\
														reg_cw_x1,			GET_BITS(pstParams->gain_x[1],0,8));
				PE_CEO_PE1_O26_QWr04(pe1_cw_ctrl_02, reg_cw_y2,			GET_BITS(pstParams->gain_y[2],0,8),\
														reg_cw_x2,			GET_BITS(pstParams->gain_x[2],0,8),\
														reg_cw_y3,			GET_BITS(pstParams->gain_y[3],0,8),\
														reg_cw_x3,			GET_BITS(pstParams->gain_x[3],0,8));
				#endif
				PE_CC2_PE1_O26_RdFL(pe1_cw_ctrl_02);
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region0_sel,	GET_BITS(pstParams->region_sel,0,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region1_sel,	GET_BITS(pstParams->region_sel,1,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region2_sel,	GET_BITS(pstParams->region_sel,2,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region3_sel,	GET_BITS(pstParams->region_sel,3,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region4_sel,	GET_BITS(pstParams->region_sel,4,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region5_sel,	GET_BITS(pstParams->region_sel,5,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region6_sel,	GET_BITS(pstParams->region_sel,6,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region7_sel,	GET_BITS(pstParams->region_sel,7,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region8_sel,	GET_BITS(pstParams->region_sel,8,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region9_sel,	GET_BITS(pstParams->region_sel,9,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region10_sel,	GET_BITS(pstParams->region_sel,10,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region11_sel,	GET_BITS(pstParams->region_sel,11,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region12_sel,	GET_BITS(pstParams->region_sel,12,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region13_sel,	GET_BITS(pstParams->region_sel,13,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region14_sel,	GET_BITS(pstParams->region_sel,14,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region15_sel,	GET_BITS(pstParams->region_sel,15,1));
				PE_CC2_PE1_O26_Wr01(pe1_cw_ctrl_02,	color_region_gain,	GET_BITS(pstParams->region_gain,0,8));
				PE_CC2_PE1_O26_WrFL(pe1_cw_ctrl_02);
				#if 1	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_00.reg_cw_en,GET_BITS(pstParams->cw_en,0,1));
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_ctrl_00.udata32);
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region0_sel, GET_BITS(pstParams->region_sel,0,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region1_sel, GET_BITS(pstParams->region_sel,1,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region2_sel, GET_BITS(pstParams->region_sel,2,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region3_sel, GET_BITS(pstParams->region_sel,3,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region4_sel, GET_BITS(pstParams->region_sel,4,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region5_sel, GET_BITS(pstParams->region_sel,5,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region6_sel, GET_BITS(pstParams->region_sel,6,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region7_sel, GET_BITS(pstParams->region_sel,7,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region8_sel, GET_BITS(pstParams->region_sel,8,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region9_sel, GET_BITS(pstParams->region_sel,9,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region10_sel,GET_BITS(pstParams->region_sel,10,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region11_sel,GET_BITS(pstParams->region_sel,11,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region12_sel,GET_BITS(pstParams->region_sel,12,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region13_sel,GET_BITS(pstParams->region_sel,13,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region14_sel,GET_BITS(pstParams->region_sel,14,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region15_sel,GET_BITS(pstParams->region_sel,15,1));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_02.color_region_gain, GET_BITS(pstParams->region_gain,0,8));
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_ctrl_02.udata32);
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CW0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get clear white
 *
 * @param   *pstParams [in/out] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_GetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT32 sel_data;
	do{
		CHECK_KNULL(pstParams);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				if(pstParams->region_gain==0)	pstParams->region_gain=1;
				PE_CC2_PE1_O26_QRd01(pe1_cw_ctrl_00,reg_cw_en,             (pstParams->cw_en));
				#if 0
				PE_CE_PE1_O26_QRd04(pe1_cw_ctrl_00,reg_cw_en,             (pstParams->cw_en),\
                                                     cw_gain_selection, (pstParams->gain_sel),\
                                                     reg_cw_y4,         (pstParams->gain_y[4]),\
                                                     reg_cw_x4,         (pstParams->gain_x[4]));
				PE_CE_PE1_O26_QRd04(pe1_cw_ctrl_03,reg_cw_y0,         (pstParams->gain_y[0]),\
                                                     reg_cw_x0,         (pstParams->gain_x[0]),\
                                                     reg_cw_y1,         (pstParams->gain_y[1]),\
                                                     reg_cw_x1,         (pstParams->gain_x[1]));
				PE_CE_PE1_O26_QRd04(pe1_cw_ctrl_02,reg_cw_y2,         (pstParams->gain_y[2]),\
                                                     reg_cw_x2,         (pstParams->gain_x[2]),\
                                                     reg_cw_y3,         (pstParams->gain_y[3]),\
                                                     reg_cw_x3,         (pstParams->gain_x[3]));
				#endif
				PE_CC2_PE1_O26_RdFL(pe1_cw_ctrl_02);
				sel_data = PE_CC2_PE1_O26_Rd(pe1_cw_ctrl_02);
				pstParams->region_sel = GET_BITS(sel_data,0,16);	//[15:0]
				PE_CC2_PE1_O26_Rd01(pe1_cw_ctrl_02,color_region_gain, (pstParams->region_gain));
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				if(pstParams->region_gain==0)	pstParams->region_gain=1;
				PE_CO_PE1_O26_QRd01(pe1_cw_ctrl_00,reg_cw_en,             (pstParams->cw_en));
				#if 0
				PE_CO_PE1_O26_QRd04(pe1_cw_ctrl_00,reg_cw_en,             (pstParams->cw_en),\
                                                     cw_gain_selection, (pstParams->gain_sel),\
                                                     reg_cw_y4,         (pstParams->gain_y[4]),\
                                                     reg_cw_x4,         (pstParams->gain_x[4]));
				PE_CO_PE1_O26_QRd04(pe1_cw_ctrl_03,reg_cw_y0,         (pstParams->gain_y[0]),\
                                                     reg_cw_x0,         (pstParams->gain_x[0]),\
                                                     reg_cw_y1,         (pstParams->gain_y[1]),\
                                                     reg_cw_x1,         (pstParams->gain_x[1]));
				PE_CO_PE1_O26_QRd04(pe1_cw_ctrl_02,reg_cw_y2,         (pstParams->gain_y[2]),\
                                                     reg_cw_x2,         (pstParams->gain_x[2]),\
                                                     reg_cw_y3,         (pstParams->gain_y[3]),\
                                                     reg_cw_x3,         (pstParams->gain_x[3]));
				#endif
				PE_CO_PE1_O26_RdFL(pe1_cw_ctrl_04);
				sel_data = PE_CO_PE1_O26_Rd(pe1_cw_ctrl_04);
				pstParams->region_sel = GET_BITS(sel_data,0,16);	//[15:0]
				PE_CO_PE1_O26_Rd01(pe1_cw_ctrl_04,color_region_gain, (pstParams->region_gain));
			}*/
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMG_HW_O26_DBG_PRINT("get[%d] en:%d, yc:%d, x:%d,%d,%d,%d,%d\n"\
			" y:%d,%d,%d,%d,%d, sel:0x%x, g:%d\n", \
			pstParams->win_id, pstParams->cw_en, \
			pstParams->gain_sel, pstParams->gain_x[0], \
			pstParams->gain_x[1], pstParams->gain_x[2], pstParams->gain_x[3], \
			pstParams->gain_x[4], pstParams->gain_y[0], pstParams->gain_y[1], \
			pstParams->gain_y[2], pstParams->gain_y[3], pstParams->gain_y[4], \
			pstParams->region_sel, pstParams->region_gain);
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set clear white gain
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_GAIN_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	LX_PE_CMG_CW_GAIN_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_CW_GAIN_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_CW_GAIN_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_CW_GAIN_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC2_PE1_O26_QWr03(pe1_cw_ctrl_01,user_ctrl_g_gain, GET_BITS(pstParams->g_gain,0,8),\
                                                      user_ctrl_b_gain, GET_BITS(pstParams->b_gain,0,8),\
                                                      user_ctrl_r_gain, GET_BITS(pstParams->r_gain,0,8));
				#if 1	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_01.user_ctrl_g_gain, GET_BITS(pstParams->g_gain,0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_01.user_ctrl_b_gain, GET_BITS(pstParams->b_gain,0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_ctrl_01.user_ctrl_r_gain, GET_BITS(pstParams->r_gain,0,8));
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_ctrl_01.udata32);
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CW0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get clear white gain
 *
 * @param   *pstParams [in/out] LX_PE_CMG_CW_GAIN_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_GetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC2_PE1_O26_QRd03(pe1_cw_ctrl_01,user_ctrl_g_gain, pstParams->g_gain,\
                                                     user_ctrl_b_gain, pstParams->b_gain,\
                                                     user_ctrl_r_gain, pstParams->r_gain);
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_O26_QRd03(pe1_cw_ctrl_01,user_ctrl_g_gain, pstParams->g_gain,\
                                                     user_ctrl_b_gain, pstParams->b_gain,\
                                                     user_ctrl_r_gain, pstParams->r_gain);
			}*/
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * Sets the cen region control registers
 *
 * @param   i_ui32RegionNum 	[in] UINT32
 * @param   i_ui32wdata 		[in] UINT32
 * @return  void
 * @see
 * @author
 */
__attribute__((unused)) static void PE_CMG_HW_O26_SetCenRegionCtrlReg(UINT32 i_ui32RegionNum, UINT32 i_ui32wdata)
{
	#ifdef PE_HW_O26_BRINGUP
	switch(i_ui32RegionNum)
	{
		case 0:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_04,	reg_master_gain_cr0,	i_ui32wdata);
			break;
		case 1:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_04,	reg_master_gain_cr1,	i_ui32wdata);
			break;
		case 2:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_04,	reg_master_gain_cr2,	i_ui32wdata);
			break;
		case 3:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_04,	reg_master_gain_cr3,	i_ui32wdata);
			break;
		case 4:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_05,	reg_master_gain_cr4,	i_ui32wdata);
			break;
		case 5:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_05,	reg_master_gain_cr5,	i_ui32wdata);
			break;
		case 6:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_05,	reg_master_gain_cr6,	i_ui32wdata);
			break;
		case 7:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_05,	reg_master_gain_cr7,	i_ui32wdata);
			break;
		case 8:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_06,	reg_master_gain_cr8,	i_ui32wdata);
			break;
		case 9:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_06,	reg_master_gain_cr9,	i_ui32wdata);
			break;
		case 10:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_06,	reg_master_gain_cr10,	i_ui32wdata);
			break;
		case 11:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_06,	reg_master_gain_cr11,	i_ui32wdata);
			break;
		case 12:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_07,	reg_master_gain_cr12,	i_ui32wdata);
			break;
		case 13:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_07,	reg_master_gain_cr13,	i_ui32wdata);
			break;
		case 14:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_07,	reg_master_gain_cr14,	i_ui32wdata);
			break;
		case 15:
		default:
			PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_07,	reg_master_gain_cr15,	i_ui32wdata);
			break;
	}
	#if 0	/* O26F22_APB */
	do {
		if (!gPE_CHPI_DDR_O26)	break;
		switch(i_ui32RegionNum)
		{
			case 0:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_04.reg_master_gain_cr0,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_04.udata32);
				break;
			case 1:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_04.reg_master_gain_cr1,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_04.udata32);
				break;
			case 2:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_04.reg_master_gain_cr2,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_04.udata32);
				break;
			case 3:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_04.reg_master_gain_cr3,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_04.udata32);
				break;
			case 4:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_05.reg_master_gain_cr4,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_05.udata32);
				break;
			case 5:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_05.reg_master_gain_cr5,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_05.udata32);
				break;
			case 6:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_05.reg_master_gain_cr6,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_05.udata32);
				break;
			case 7:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_05.reg_master_gain_cr7,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_05.udata32);
				break;
			case 8:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_06.reg_master_gain_cr8,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_06.udata32);
				break;
			case 9:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_06.reg_master_gain_cr9,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_06.udata32);
				break;
			case 10:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_06.reg_master_gain_cr10,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_06.udata32);
				break;
			case 11:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_06.reg_master_gain_cr11,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_06.udata32);
				break;
			case 12:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_07.reg_master_gain_cr12,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_07.udata32);
				break;
			case 13:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_07.reg_master_gain_cr13,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_07.udata32);
				break;
			case 14:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_07.reg_master_gain_cr14,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_07.udata32);
				break;
			case 15:
			default:
				PE_CHPI_APB0_O26F22_Wr(cen1.pe1_cen_ctrl_07.reg_master_gain_cr15,i_ui32wdata);
				PE_CHPI_APB0_O26F22_WrFL(cen1.pe1_cen_ctrl_07.udata32);
				break;
		}
		PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN1);
	} while(0);
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}
#if 0	//not used
/**
 * Gets CE region gain register value
 *
 * @param   i_ui32RegionNum 	[in] 	UINT32
 * @param   *o_ui32RegGain		[out] 	UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_CMG_HW_O26_CEGetRegGain(UINT32 i_ui32RegionNum, UINT32 *o_ui32RegGain)
{
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 re_mgain = 0;

	switch(i_ui32RegionNum)
	{
		case 0:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr0,	re_mgain);
			break;
		case 1:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr1,	re_mgain);
			break;
		case 2:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr2,	re_mgain);
			break;
		case 3:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr3,	re_mgain);
			break;
		case 4:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr4,	re_mgain);
			break;
		case 5:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr5,	re_mgain);
			break;
		case 6:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr6,	re_mgain);
			break;
		case 7:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr7,	re_mgain);
			break;
		case 8:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr8,	re_mgain);
			break;
		case 9:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr9,	re_mgain);
			break;
		case 10:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr10,	re_mgain);
			break;
		case 11:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr11,	re_mgain);
			break;
		case 12:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr12,	re_mgain);
			break;
		case 13:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr13,	re_mgain);
			break;
		case 14:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr14,	re_mgain);
			break;
		case 15:
		default:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr15,	re_mgain);
			break;
	}

	*o_ui32RegGain = re_mgain;
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}

/**
 * Gets CO region master gain register value
 *
 * @param   i_ui32RegionNum 	[in] 	UINT32
 * @param   *o_ui32RegGain		[out] 	UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_CMG_HW_O26_COGetRegGain(UINT32 i_ui32RegionNum, UINT32 *o_ui32RegGain)
{
	#if 0 //def PE_HW_O26_BRINGUP

	UINT32 re_mgain = 0;

	switch(i_ui32RegionNum)
	{
		case 0:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr0,	re_mgain);
			break;
		case 1:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr1,	re_mgain);
			break;
		case 2:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr2,	re_mgain);
			break;
		case 3:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_04,	reg_master_gain_cr3,	re_mgain);
			break;
		case 4:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr4,	re_mgain);
			break;
		case 5:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr5,	re_mgain);
			break;
		case 6:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr6,	re_mgain);
			break;
		case 7:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_05,	reg_master_gain_cr7,	re_mgain);
			break;
		case 8:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr8,	re_mgain);
			break;
		case 9:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr9,	re_mgain);
			break;
		case 10:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr10,	re_mgain);
			break;
		case 11:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_06,	reg_master_gain_cr11,	re_mgain);
			break;
		case 12:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr12,	re_mgain);
			break;
		case 13:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr13,	re_mgain);
			break;
		case 14:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr14,	re_mgain);
			break;
		case 15:
		default:
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_07,	reg_master_gain_cr15,	re_mgain);
			break;
	}

	*o_ui32RegGain = re_mgain;
	#endif /*PE_HW_O26_BRINGUP*/
	return;
}
#endif
/**
 * set Ext/Inner Pattern
 *
 * @param	*pstParams [in] LX_PE_CMG_EXT_PATTERN_INFO_T
 * @return	OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetExtInnerPattern(LX_PE_CMG_EXT_PATTERN_INFO_T *p)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 iter, ia_data;
	UINT32 x_ofst,y_ofst,x_size,y_size;
	#endif

#define PE_CMG_HW_O26_4K_H_MAX			3840
#define PE_CMG_HW_O26_4K_V_MAX			2160
#define PE_CMG_HW_O26_CORE_NUM			2

	do {
		CHECK_KNULL(p);
		#ifdef PE_HW_O26_BRINGUP
		if (PE_KDRV_VER_O26)
		{
			LX_PE_CMG_EXT_PATTERN_INFO_T *pp = (LX_PE_CMG_EXT_PATTERN_INFO_T *)p;
			static LX_PE_CMG_EXT_PATTERN_INFO_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			//PE_CHECK_DUPLICATE(LX_PE_CMG_EXT_PATTERN_INFO_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_EXT_PATTERN_INFO_T\n");
				ret=RET_OK;
				break;
			}
 			if (PE_CHECK_WIN0(p->win_id))
			{
				PE_CMG_HW_O26_DBG_PRINT("set[%d] bOnOff:%d, eMode:%d\n"\
				" stGradInfo: numGrad   : %d\n" \
				"             eGradMode : %d\n" \
				" stWinboxInfo: u8NumWin: %d\n", \
				p->win_id, p->bOnOff, p->eMode, p->stGradInfo.numGrad, p->stGradInfo.eGradMode,\
				p->stWinboxInfo.u8NumWin);
				PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_00, 0x00000000);
				PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_00);
				PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_01, 0x00000000);
				PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_01);
				PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_02, 0x00000000);
				PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_02);
				PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_03, 0x00000000);
				PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_03);
				PE_CC_PE1_O26_Wr(pe1_tpg_ia_ctrl, 0x00000000);
				PE_CC_PE1_O26_WrFL(pe1_tpg_ia_ctrl);
				OS_MsecSleep(30);

				if (!p->bOnOff)
					break;

				if (p->eMode == LX_PE_EXT_PATTERN_WINBOX)
				{
					if (p->stWinboxInfo.u8NumWin > LX_PE_MAX_EXT_PATTERN_WINBOX)
						p->stWinboxInfo.u8NumWin = LX_PE_MAX_EXT_PATTERN_WINBOX;

					PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_00, 0x07800000);
					PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_00);

					PE_CC_PE1_O26_Wr(pe1_tpg_ia_ctrl, 0x00001000);	// patch color
					PE_CC_PE1_O26_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stWinboxInfo.u8NumWin; iter++)
					{
						ia_data = p->stWinboxInfo.stWinBoxAttr[iter].fill_R |
							(p->stWinboxInfo.stWinBoxAttr[iter].fill_B << 10) |
							(p->stWinboxInfo.stWinBoxAttr[iter].fill_G << 20);
						PE_CC_PE1_O26_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_O26_WrFL(pe1_tpg_ia_data);
					}
					PE_CC_PE1_O26_Wr(pe1_tpg_ia_ctrl, 0x00001020);	// patch start (x,y)
					PE_CC_PE1_O26_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stWinboxInfo.u8NumWin; iter++)
					{
						x_ofst = (p->stWinboxInfo.stWinBoxAttr[iter].x);
						y_ofst = (p->stWinboxInfo.stWinBoxAttr[iter].y);
						ia_data = ((x_ofst / PE_CMG_HW_O26_CORE_NUM) << 16) | (y_ofst);
						PE_CC_PE1_O26_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_O26_WrFL(pe1_tpg_ia_data);
					}
					PE_CC_PE1_O26_Wr(pe1_tpg_ia_ctrl, 0x00001040);	// patch end (x,y)
					PE_CC_PE1_O26_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stWinboxInfo.u8NumWin; iter++)
					{
						x_ofst = (p->stWinboxInfo.stWinBoxAttr[iter].x);
						y_ofst = (p->stWinboxInfo.stWinBoxAttr[iter].y);
						x_size = (p->stWinboxInfo.stWinBoxAttr[iter].w);
						y_size = (p->stWinboxInfo.stWinBoxAttr[iter].h);
						ia_data = (((x_ofst + x_size) / PE_CMG_HW_O26_CORE_NUM) << 16) | (y_ofst + y_size);
						PE_CC_PE1_O26_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_O26_WrFL(pe1_tpg_ia_data);
					}
					if (p->stWinboxInfo.u8NumWin > 0)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_0_en, 1);
					if (p->stWinboxInfo.u8NumWin > 1)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_1_en, 1);
					if (p->stWinboxInfo.u8NumWin > 2)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_2_en, 1);
					if (p->stWinboxInfo.u8NumWin > 3)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_3_en, 1);
					if (p->stWinboxInfo.u8NumWin > 4)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_4_en, 1);
					if (p->stWinboxInfo.u8NumWin > 5)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_5_en, 1);
					if (p->stWinboxInfo.u8NumWin > 6)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_6_en, 1);
					if (p->stWinboxInfo.u8NumWin > 7)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_7_en, 1);
					if (p->stWinboxInfo.u8NumWin > 8)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_8_en, 1);
					if (p->stWinboxInfo.u8NumWin > 9)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_02, patch_9_en, 1);
					PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_02);
					PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_03, 0x00000000);
					PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_03);
					PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_00, 0x07800001);
					PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_00);
				}
				else if (p->eMode == LX_PE_EXT_PATTERN_GRADATION)
				{
					if (p->stGradInfo.numGrad > LX_PE_MAX_EXT_PATTERN_GRADATION_LINE)
						p->stGradInfo.numGrad = LX_PE_MAX_EXT_PATTERN_GRADATION_LINE;
					if (p->stGradInfo.numGrad % 2)
					{
						PE_CMG_HW_O26_DBG_PRINT("ERROR.\n");
						ret = RET_ERROR;
						break;
					}

					PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_00, 0x07800002);
					PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_00);

					PE_CC_PE1_O26_Wr(pe1_tpg_ia_ctrl, 0x00001060);	// gradation start color
					PE_CC_PE1_O26_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stGradInfo.numGrad; iter++)
					{
						ia_data = p->stGradInfo.stLineAttr[iter].start_R |
							(p->stGradInfo.stLineAttr[iter].start_B << 10) |
							(p->stGradInfo.stLineAttr[iter].start_G << 20);
						PE_CC_PE1_O26_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_O26_WrFL(pe1_tpg_ia_data);
					}
					PE_CC_PE1_O26_Wr(pe1_tpg_ia_ctrl, 0x00001064);	// gradation step color
					PE_CC_PE1_O26_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stGradInfo.numGrad; iter++)
					{
						ia_data = p->stGradInfo.stLineAttr[iter].step_R |
							(p->stGradInfo.stLineAttr[iter].step_B << 10) |
							(p->stGradInfo.stLineAttr[iter].step_G << 20);
						PE_CC_PE1_O26_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_O26_WrFL(pe1_tpg_ia_data);
					}
					PE_CC_PE1_O26_Wr(pe1_tpg_ia_ctrl, 0x00001068);	// gradation region size
					PE_CC_PE1_O26_WrFL(pe1_tpg_ia_ctrl);
					for (iter = 0; iter < p->stGradInfo.numGrad; iter++)
					{
						if (p->stGradInfo.eGradMode == LX_PE_EXT_PATTERN_GRADATION_DIRECTION_HORIZONTAL)
							ia_data = ((PE_CMG_HW_O26_4K_V_MAX) / p->stGradInfo.numGrad) * (iter + 1);
						else
							ia_data = ((PE_CMG_HW_O26_4K_H_MAX / PE_CMG_HW_O26_CORE_NUM) / p->stGradInfo.numGrad) * (iter + 1);
						PE_CC_PE1_O26_Wr(pe1_tpg_ia_data, ia_data);
						PE_CC_PE1_O26_WrFL(pe1_tpg_ia_data);
					}

					PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_01, gradation_direction, p->stGradInfo.eGradMode ? 0 : 1);
					PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_01, gradation_stride, p->stGradInfo.stLineAttr[0].strideSize);
					if (p->stGradInfo.numGrad > 0)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_01, gradation_bar_0_en, 1);
					if (p->stGradInfo.numGrad > 1)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_01, gradation_bar_1_en, 1);
					if (p->stGradInfo.numGrad > 2)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_01, gradation_bar_2_en, 1);
					if (p->stGradInfo.numGrad > 3)
						PE_CC_PE1_O26_Wr01(pe1_tpg_ctrl_01, gradation_bar_3_en, 1);
					PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_01);
					PE_CC_PE1_O26_Wr(pe1_tpg_ctrl_00, 0x07800003);
					PE_CC_PE1_O26_WrFL(pe1_tpg_ctrl_00);
				}
				else
				{
					PE_CMG_HW_O26_DBG_PRINT("ERROR.\n");	ret = RET_ERROR;
				}
			}
			OS_MsecSleep(30);
 		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		#endif
	} while (0);
	return ret;
}
/**
 * set clear white table setting
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetClearWhiteTableCtrl(LX_PE_CMG_CW_TABLE_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	LX_PE_CMG_CW_TABLE_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_CW_TABLE_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_CW_TABLE_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_CW_TABLE_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMG_HW_O26_DBG_PRINT("set[%d] \n"\
			" hue_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" hue_y: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_y: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_y: %d, %d, %d, %d, %d, %d, %d, %d,\n", \
			pstParams->win_id, \
			pstParams->cw_hue_x[0], pstParams->cw_hue_x[1], pstParams->cw_hue_x[2], pstParams->cw_hue_x[3], \
			pstParams->cw_hue_x[4], pstParams->cw_hue_x[5], pstParams->cw_hue_x[6], pstParams->cw_hue_x[7], \
			pstParams->cw_hue_y[0], pstParams->cw_hue_y[1], pstParams->cw_hue_y[2], pstParams->cw_hue_y[3], \
			pstParams->cw_hue_y[4], pstParams->cw_hue_y[5], pstParams->cw_hue_y[6], pstParams->cw_hue_y[7], \
			pstParams->cw_sat_x[0], pstParams->cw_sat_x[1], pstParams->cw_sat_x[2], pstParams->cw_sat_x[3], \
			pstParams->cw_sat_x[4], pstParams->cw_sat_x[5], pstParams->cw_sat_x[6], pstParams->cw_sat_x[7], \
			pstParams->cw_sat_y[0], pstParams->cw_sat_y[1], pstParams->cw_sat_y[2], pstParams->cw_sat_y[3], \
			pstParams->cw_sat_y[4], pstParams->cw_sat_y[5], pstParams->cw_sat_y[6], pstParams->cw_sat_y[7], \
			pstParams->cw_val_x[0], pstParams->cw_val_x[1], pstParams->cw_val_x[2], pstParams->cw_val_x[3], \
			pstParams->cw_val_x[4], pstParams->cw_val_x[5], pstParams->cw_val_x[6], pstParams->cw_val_x[7], \
			pstParams->cw_val_y[0], pstParams->cw_val_y[1], pstParams->cw_val_y[2], pstParams->cw_val_y[3], \
			pstParams->cw_val_y[4], pstParams->cw_val_y[5], pstParams->cw_val_y[6], pstParams->cw_val_y[7]);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* hue */
				PE_CC2_PE1_O26_QWr02(pe1_cw_crgn_ctrl_00, reg_crgn_hue_gain_y0,	GET_BITS(pstParams->cw_hue_y[0],0,8),\
														   reg_crgn_hue_gain_x0,	GET_BITS(pstParams->cw_hue_x[0],0,10));
				PE_CC2_PE1_O26_QWr02(pe1_cw_crgn_ctrl_01, reg_crgn_hue_gain_y1,	GET_BITS(pstParams->cw_hue_y[1],0,8),\
														   reg_crgn_hue_gain_x1,	GET_BITS(pstParams->cw_hue_x[1],0,10));
				PE_CC2_PE1_O26_QWr02(pe1_cw_crgn_ctrl_02, reg_crgn_hue_gain_y2,	GET_BITS(pstParams->cw_hue_y[2],0,8),\
														   reg_crgn_hue_gain_x2,	GET_BITS(pstParams->cw_hue_x[2],0,10));
				PE_CC2_PE1_O26_QWr02(pe1_cw_crgn_ctrl_03, reg_crgn_hue_gain_y3,	GET_BITS(pstParams->cw_hue_y[3],0,8),\
														   reg_crgn_hue_gain_x3,	GET_BITS(pstParams->cw_hue_x[3],0,10));
				PE_CC2_PE1_O26_QWr02(pe1_cw_crgn_ctrl_04, reg_crgn_hue_gain_y4,	GET_BITS(pstParams->cw_hue_y[4],0,8),\
														   reg_crgn_hue_gain_x4,	GET_BITS(pstParams->cw_hue_x[4],0,10));
				PE_CC2_PE1_O26_QWr02(pe1_cw_crgn_ctrl_05, reg_crgn_hue_gain_y5,	GET_BITS(pstParams->cw_hue_y[5],0,8),\
														   reg_crgn_hue_gain_x5,	GET_BITS(pstParams->cw_hue_x[5],0,10));
				PE_CC2_PE1_O26_QWr02(pe1_cw_crgn_ctrl_06, reg_crgn_hue_gain_y6,	GET_BITS(pstParams->cw_hue_y[6],0,8),\
														   reg_crgn_hue_gain_x6,	GET_BITS(pstParams->cw_hue_x[6],0,10));
				PE_CC2_PE1_O26_QWr02(pe1_cw_crgn_ctrl_07, reg_crgn_hue_gain_y7,	GET_BITS(pstParams->cw_hue_y[7],0,8),\
														   reg_crgn_hue_gain_x7,	GET_BITS(pstParams->cw_hue_x[7],0,10));
				/* sat */
				PE_CC2_PE1_O26_QWr04(pe1_cw_crgn_ctrl_08, reg_crgn_sat_gain_y0,	GET_BITS(pstParams->cw_sat_y[0],0,8),\
														   reg_crgn_sat_gain_x0,	GET_BITS(pstParams->cw_sat_x[0],0,8),\
														   reg_crgn_sat_gain_y1,	GET_BITS(pstParams->cw_sat_y[1],0,8),\
														   reg_crgn_sat_gain_x1,	GET_BITS(pstParams->cw_sat_x[1],0,8));
				PE_CC2_PE1_O26_QWr04(pe1_cw_crgn_ctrl_09, reg_crgn_sat_gain_y2,	GET_BITS(pstParams->cw_sat_y[2],0,8),\
														   reg_crgn_sat_gain_x2,	GET_BITS(pstParams->cw_sat_x[2],0,8),\
														   reg_crgn_sat_gain_y3,	GET_BITS(pstParams->cw_sat_y[3],0,8),\
														   reg_crgn_sat_gain_x3,	GET_BITS(pstParams->cw_sat_x[3],0,8));
				PE_CC2_PE1_O26_QWr04(pe1_cw_crgn_ctrl_10, reg_crgn_sat_gain_y4,	GET_BITS(pstParams->cw_sat_y[4],0,8),\
														   reg_crgn_sat_gain_x4,	GET_BITS(pstParams->cw_sat_x[4],0,8),\
														   reg_crgn_sat_gain_y5,	GET_BITS(pstParams->cw_sat_y[5],0,8),\
														   reg_crgn_sat_gain_x5,	GET_BITS(pstParams->cw_sat_x[5],0,8));
				PE_CC2_PE1_O26_QWr04(pe1_cw_crgn_ctrl_11, reg_crgn_sat_gain_y6,	GET_BITS(pstParams->cw_sat_y[6],0,8),\
														   reg_crgn_sat_gain_x6,	GET_BITS(pstParams->cw_sat_x[6],0,8),\
														   reg_crgn_sat_gain_y7,	GET_BITS(pstParams->cw_sat_y[7],0,8),\
														   reg_crgn_sat_gain_x7,	GET_BITS(pstParams->cw_sat_x[7],0,8));
				/* val */
				PE_CC2_PE1_O26_QWr04(pe1_cw_crgn_ctrl_12, reg_crgn_val_gain_y0,	GET_BITS(pstParams->cw_val_y[0],0,8),\
														   reg_crgn_val_gain_x0,	GET_BITS(pstParams->cw_val_x[0],0,8),\
														   reg_crgn_val_gain_y1,	GET_BITS(pstParams->cw_val_y[1],0,8),\
														   reg_crgn_val_gain_x1,	GET_BITS(pstParams->cw_val_x[1],0,8));
				PE_CC2_PE1_O26_QWr04(pe1_cw_crgn_ctrl_13, reg_crgn_val_gain_y2,	GET_BITS(pstParams->cw_val_y[2],0,8),\
														   reg_crgn_val_gain_x2,	GET_BITS(pstParams->cw_val_x[2],0,8),\
														   reg_crgn_val_gain_y3,	GET_BITS(pstParams->cw_val_y[3],0,8),\
														   reg_crgn_val_gain_x3,	GET_BITS(pstParams->cw_val_x[3],0,8));
				PE_CC2_PE1_O26_QWr04(pe1_cw_crgn_ctrl_14, reg_crgn_val_gain_y4,	GET_BITS(pstParams->cw_val_y[4],0,8),\
														   reg_crgn_val_gain_x4,	GET_BITS(pstParams->cw_val_x[4],0,8),\
														   reg_crgn_val_gain_y5,	GET_BITS(pstParams->cw_val_y[5],0,8),\
														   reg_crgn_val_gain_x5,	GET_BITS(pstParams->cw_val_x[5],0,8));
				PE_CC2_PE1_O26_QWr04(pe1_cw_crgn_ctrl_15, reg_crgn_val_gain_y6,	GET_BITS(pstParams->cw_val_y[6],0,8),\
														   reg_crgn_val_gain_x6,	GET_BITS(pstParams->cw_val_x[6],0,8),\
														   reg_crgn_val_gain_y7,	GET_BITS(pstParams->cw_val_y[7],0,8),\
														   reg_crgn_val_gain_x7,	GET_BITS(pstParams->cw_val_x[7],0,8));
				#if 1	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					/* hue */
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_00.reg_crgn_hue_gain_y0, GET_BITS(pstParams->cw_hue_y[0],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_00.reg_crgn_hue_gain_x0, GET_BITS(pstParams->cw_hue_x[0],0,10));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_01.reg_crgn_hue_gain_y1, GET_BITS(pstParams->cw_hue_y[1],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_01.reg_crgn_hue_gain_x1, GET_BITS(pstParams->cw_hue_x[1],0,10));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_02.reg_crgn_hue_gain_y2, GET_BITS(pstParams->cw_hue_y[2],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_02.reg_crgn_hue_gain_x2, GET_BITS(pstParams->cw_hue_x[2],0,10));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_03.reg_crgn_hue_gain_y3, GET_BITS(pstParams->cw_hue_y[3],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_03.reg_crgn_hue_gain_x3, GET_BITS(pstParams->cw_hue_x[3],0,10));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_04.reg_crgn_hue_gain_y4, GET_BITS(pstParams->cw_hue_y[4],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_04.reg_crgn_hue_gain_x4, GET_BITS(pstParams->cw_hue_x[4],0,10));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_05.reg_crgn_hue_gain_y5, GET_BITS(pstParams->cw_hue_y[5],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_05.reg_crgn_hue_gain_x5, GET_BITS(pstParams->cw_hue_x[5],0,10));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_06.reg_crgn_hue_gain_y6, GET_BITS(pstParams->cw_hue_y[6],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_06.reg_crgn_hue_gain_x6, GET_BITS(pstParams->cw_hue_x[6],0,10));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_07.reg_crgn_hue_gain_y7, GET_BITS(pstParams->cw_hue_y[7],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_07.reg_crgn_hue_gain_x7, GET_BITS(pstParams->cw_hue_x[7],0,10));
					/* sat */
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_08.reg_crgn_sat_gain_y0, GET_BITS(pstParams->cw_sat_y[0],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_08.reg_crgn_sat_gain_x0, GET_BITS(pstParams->cw_sat_x[0],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_08.reg_crgn_sat_gain_y1, GET_BITS(pstParams->cw_sat_y[1],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_08.reg_crgn_sat_gain_x1, GET_BITS(pstParams->cw_sat_x[1],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_09.reg_crgn_sat_gain_y2, GET_BITS(pstParams->cw_sat_y[2],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_09.reg_crgn_sat_gain_x2, GET_BITS(pstParams->cw_sat_x[2],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_09.reg_crgn_sat_gain_y3, GET_BITS(pstParams->cw_sat_y[3],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_09.reg_crgn_sat_gain_x3, GET_BITS(pstParams->cw_sat_x[3],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_10.reg_crgn_sat_gain_y4, GET_BITS(pstParams->cw_sat_y[4],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_10.reg_crgn_sat_gain_x4, GET_BITS(pstParams->cw_sat_x[4],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_10.reg_crgn_sat_gain_y5, GET_BITS(pstParams->cw_sat_y[5],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_10.reg_crgn_sat_gain_x5, GET_BITS(pstParams->cw_sat_x[5],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_11.reg_crgn_sat_gain_y6, GET_BITS(pstParams->cw_sat_y[6],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_11.reg_crgn_sat_gain_x6, GET_BITS(pstParams->cw_sat_x[6],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_11.reg_crgn_sat_gain_y7, GET_BITS(pstParams->cw_sat_y[7],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_11.reg_crgn_sat_gain_x7, GET_BITS(pstParams->cw_sat_x[7],0,8));
					/* val */
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_12.reg_crgn_val_gain_y0, GET_BITS(pstParams->cw_val_y[0],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_12.reg_crgn_val_gain_x0, GET_BITS(pstParams->cw_val_x[0],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_12.reg_crgn_val_gain_y1, GET_BITS(pstParams->cw_val_y[1],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_12.reg_crgn_val_gain_x1, GET_BITS(pstParams->cw_val_x[1],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_13.reg_crgn_val_gain_y2, GET_BITS(pstParams->cw_val_y[2],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_13.reg_crgn_val_gain_x2, GET_BITS(pstParams->cw_val_x[2],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_13.reg_crgn_val_gain_y3, GET_BITS(pstParams->cw_val_y[3],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_13.reg_crgn_val_gain_x3, GET_BITS(pstParams->cw_val_x[3],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_14.reg_crgn_val_gain_y4, GET_BITS(pstParams->cw_val_y[4],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_14.reg_crgn_val_gain_x4, GET_BITS(pstParams->cw_val_x[4],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_14.reg_crgn_val_gain_y5, GET_BITS(pstParams->cw_val_y[5],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_14.reg_crgn_val_gain_x5, GET_BITS(pstParams->cw_val_x[5],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_15.reg_crgn_val_gain_y6, GET_BITS(pstParams->cw_val_y[6],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_15.reg_crgn_val_gain_x6, GET_BITS(pstParams->cw_val_x[6],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_15.reg_crgn_val_gain_y7, GET_BITS(pstParams->cw_val_y[7],0,8));
					PE_CHPI_APB0_O26F22_Wr(cw0.pe1_cw_crgn_ctrl_15.reg_crgn_val_gain_x7, GET_BITS(pstParams->cw_val_x[7],0,8));
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_00.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_01.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_02.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_03.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_04.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_05.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_06.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_07.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_08.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_09.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_10.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_11.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_12.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_13.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_14.udata32);
					PE_CHPI_APB0_O26F22_WrFL(cw0.pe1_cw_crgn_ctrl_15.udata32);
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CW0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set clear white table setting
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetVspccCtrl(LX_PE_CMG_VSPCC_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	PE_CMG_HW_O26_SETTINGS_T *pInfo=&_g_pe_cmg_hw_o26_info;
	LX_PE_CMG_VSPCC_CTRL_T *pp = pstParams;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_VSPCC_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_VSPCC_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_VSPCC_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMG_HW_O26_DBG_PRINT("set[%d] \n"\
			"satTarget : %d\n" \
			"objMapGainLUT_x : %d, %d, %d, %d" \
			"objMapGainLUT_y : %d, %d, %d, %d" \
			"faceMapGainLUT_x : %d, %d, %d, %d" \
			"faceMapGainLUT_y : %d, %d, %d, %d" \
			" hue_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" hue_g: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" sat_g: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
			" val_g: %d, %d, %d, %d, %d, %d, %d, %d,\n", \
			pstParams->win_id, \
			pstParams->satTarget,\
			pstParams->objMapGainLUT_x[0],pstParams->objMapGainLUT_x[1],pstParams->objMapGainLUT_x[2],pstParams->objMapGainLUT_x[3],\
			pstParams->objMapGainLUT_y[0],pstParams->objMapGainLUT_y[1],pstParams->objMapGainLUT_y[2],pstParams->objMapGainLUT_y[3],\
			pstParams->faceMapGainLUT_x[0],pstParams->faceMapGainLUT_x[1],pstParams->faceMapGainLUT_x[2],pstParams->faceMapGainLUT_x[3],\
			pstParams->faceMapGainLUT_y[0],pstParams->faceMapGainLUT_y[1],pstParams->faceMapGainLUT_y[2],pstParams->faceMapGainLUT_y[3],\
			pstParams->hue_x[0], pstParams->hue_x[1], pstParams->hue_x[2], pstParams->hue_x[3], \
			pstParams->hue_x[4], pstParams->hue_x[5], pstParams->hue_x[6], pstParams->hue_x[7], \
			pstParams->hue_g[0], pstParams->hue_g[1], pstParams->hue_g[2], pstParams->hue_g[3], \
			pstParams->hue_g[4], pstParams->hue_g[5], pstParams->hue_g[6], pstParams->hue_g[7], \
			pstParams->sat_x[0], pstParams->sat_x[1], pstParams->sat_x[2], pstParams->sat_x[3], \
			pstParams->sat_x[4], pstParams->sat_x[5], pstParams->sat_x[6], pstParams->sat_x[7], \
			pstParams->sat_g[0], pstParams->sat_g[1], pstParams->sat_g[2], pstParams->sat_g[3], \
			pstParams->sat_g[4], pstParams->sat_g[5], pstParams->sat_g[6], pstParams->sat_g[7], \
			pstParams->val_x[0], pstParams->val_x[1], pstParams->val_x[2], pstParams->val_x[3], \
			pstParams->val_x[4], pstParams->val_x[5], pstParams->val_x[6], pstParams->val_x[7], \
			pstParams->val_g[0], pstParams->val_g[1], pstParams->val_g[2], pstParams->val_g[3], \
			pstParams->val_g[4], pstParams->val_g[5], pstParams->val_g[6], pstParams->val_g[7]);
		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* to adjust target_sat according to vsp saturation see */
				//PE_CEO_PE1_O26_QWr01(pe1_vspyc_ctrl_01, saturation_target, GET_BITS(pstParams->satTarget, 0, 8));
				//pInfo->org_target_sat = pstParams->satTarget;
				#if 0 // no register
				/* objMapGainLUT_y,x */
				PE_CC2_PE1_O26_QWr04(pe1_vsp_cc_ctrl_01,	reg_objt_gain_y0, GET_BITS(pstParams->objMapGainLUT_y[0], 0, 8),\
															reg_objt_gain_x0, GET_BITS(pstParams->objMapGainLUT_x[0], 0, 8),\
															reg_objt_gain_y1, GET_BITS(pstParams->objMapGainLUT_y[1], 0, 8),\
															reg_objt_gain_x1, GET_BITS(pstParams->objMapGainLUT_x[1], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_vsp_cc_ctrl_02,	reg_objt_gain_y2, GET_BITS(pstParams->objMapGainLUT_y[2], 0, 8),\
															reg_objt_gain_x2, GET_BITS(pstParams->objMapGainLUT_x[2], 0, 8),\
															reg_objt_gain_y3, GET_BITS(pstParams->objMapGainLUT_y[3], 0, 8),\
															reg_objt_gain_x3, GET_BITS(pstParams->objMapGainLUT_x[3], 0, 8));
				/* faceMapGainLUT_y,x */
				PE_CC2_PE1_O26_QWr04(pe1_vsp_cc_ctrl_03,	reg_face_gain_y0, GET_BITS(pstParams->faceMapGainLUT_y[0], 0, 8),\
															reg_face_gain_x0, GET_BITS(pstParams->faceMapGainLUT_x[0], 0, 8),\
															reg_face_gain_y1, GET_BITS(pstParams->faceMapGainLUT_y[1], 0, 8),\
															reg_face_gain_x1, GET_BITS(pstParams->faceMapGainLUT_x[1], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_vsp_cc_ctrl_04,	reg_face_gain_y2, GET_BITS(pstParams->faceMapGainLUT_y[2], 0, 8),\
															reg_face_gain_x2, GET_BITS(pstParams->faceMapGainLUT_x[2], 0, 8),\
															reg_face_gain_y3, GET_BITS(pstParams->faceMapGainLUT_y[3], 0, 8),\
															reg_face_gain_x3, GET_BITS(pstParams->faceMapGainLUT_x[3], 0, 8));
				#endif
				/* hue_g,x */
				PE_CC2_PE1_O26_QWr02(pe1_vsp_crgn_ctrl_00,	reg_crgn_hue_gain_y0, GET_BITS(pstParams->hue_g[0], 0, 8),\
															reg_crgn_hue_gain_x0, GET_BITS(pstParams->hue_x[0], 0, 10));
				PE_CC2_PE1_O26_QWr02(pe1_vsp_crgn_ctrl_01,	reg_crgn_hue_gain_y1, GET_BITS(pstParams->hue_g[1], 0, 8),\
															reg_crgn_hue_gain_x1, GET_BITS(pstParams->hue_x[1], 0, 10));
				PE_CC2_PE1_O26_QWr02(pe1_vsp_crgn_ctrl_02,	reg_crgn_hue_gain_y2, GET_BITS(pstParams->hue_g[2], 0, 8),\
															reg_crgn_hue_gain_x2, GET_BITS(pstParams->hue_x[2], 0, 10));
				PE_CC2_PE1_O26_QWr02(pe1_vsp_crgn_ctrl_03,	reg_crgn_hue_gain_y3, GET_BITS(pstParams->hue_g[3], 0, 8),\
															reg_crgn_hue_gain_x3, GET_BITS(pstParams->hue_x[3], 0, 10));
				PE_CC2_PE1_O26_QWr02(pe1_vsp_crgn_ctrl_04,	reg_crgn_hue_gain_y4, GET_BITS(pstParams->hue_g[4], 0, 8),\
															reg_crgn_hue_gain_x4, GET_BITS(pstParams->hue_x[4], 0, 10));
				PE_CC2_PE1_O26_QWr02(pe1_vsp_crgn_ctrl_05,	reg_crgn_hue_gain_y5, GET_BITS(pstParams->hue_g[5], 0, 8),\
															reg_crgn_hue_gain_x5, GET_BITS(pstParams->hue_x[5], 0, 10));
				PE_CC2_PE1_O26_QWr02(pe1_vsp_crgn_ctrl_06,	reg_crgn_hue_gain_y6, GET_BITS(pstParams->hue_g[6], 0, 8),\
															reg_crgn_hue_gain_x6, GET_BITS(pstParams->hue_x[6], 0, 10));
				PE_CC2_PE1_O26_QWr02(pe1_vsp_crgn_ctrl_07,	reg_crgn_hue_gain_y7, GET_BITS(pstParams->hue_g[7], 0, 8),\
															reg_crgn_hue_gain_x7, GET_BITS(pstParams->hue_x[7], 0, 10));
				/* sat_g,x */
				PE_CC2_PE1_O26_QWr04(pe1_vsp_crgn_ctrl_08,	reg_crgn_sat_gain_y0, GET_BITS(pstParams->sat_g[0], 0, 8),\
															reg_crgn_sat_gain_x0, GET_BITS(pstParams->sat_x[0], 0, 7),\
															reg_crgn_sat_gain_y1, GET_BITS(pstParams->sat_g[1], 0, 8),\
															reg_crgn_sat_gain_x1, GET_BITS(pstParams->sat_x[1], 0, 7));
				PE_CC2_PE1_O26_QWr04(pe1_vsp_crgn_ctrl_09,	reg_crgn_sat_gain_y2, GET_BITS(pstParams->sat_g[2], 0, 8),\
															reg_crgn_sat_gain_x2, GET_BITS(pstParams->sat_x[2], 0, 7),\
															reg_crgn_sat_gain_y3, GET_BITS(pstParams->sat_g[3], 0, 8),\
															reg_crgn_sat_gain_x3, GET_BITS(pstParams->sat_x[3], 0, 7));
				PE_CC2_PE1_O26_QWr04(pe1_vsp_crgn_ctrl_10,	reg_crgn_sat_gain_y4, GET_BITS(pstParams->sat_g[4], 0, 8),\
															reg_crgn_sat_gain_x4, GET_BITS(pstParams->sat_x[4], 0, 7),\
															reg_crgn_sat_gain_y5, GET_BITS(pstParams->sat_g[5], 0, 8),\
															reg_crgn_sat_gain_x5, GET_BITS(pstParams->sat_x[5], 0, 7));
				PE_CC2_PE1_O26_QWr04(pe1_vsp_crgn_ctrl_11,	reg_crgn_sat_gain_y6, GET_BITS(pstParams->sat_g[6], 0, 8),\
															reg_crgn_sat_gain_x6, GET_BITS(pstParams->sat_x[6], 0, 7),\
															reg_crgn_sat_gain_y7, GET_BITS(pstParams->sat_g[7], 0, 8),\
															reg_crgn_sat_gain_x7, GET_BITS(pstParams->sat_x[7], 0, 7));
				/* val_g,x */
				PE_CC2_PE1_O26_QWr04(pe1_vsp_crgn_ctrl_12,	reg_crgn_val_gain_y0, GET_BITS(pstParams->val_g[0], 0, 8),\
															reg_crgn_val_gain_x0, GET_BITS(pstParams->val_x[0], 0, 8),\
															reg_crgn_val_gain_y1, GET_BITS(pstParams->val_g[1], 0, 8),\
															reg_crgn_val_gain_x1, GET_BITS(pstParams->val_x[1], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_vsp_crgn_ctrl_13,	reg_crgn_val_gain_y2, GET_BITS(pstParams->val_g[2], 0, 8),\
															reg_crgn_val_gain_x2, GET_BITS(pstParams->val_x[2], 0, 8),\
															reg_crgn_val_gain_y3, GET_BITS(pstParams->val_g[3], 0, 8),\
															reg_crgn_val_gain_x3, GET_BITS(pstParams->val_x[3], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_vsp_crgn_ctrl_14,	reg_crgn_val_gain_y4, GET_BITS(pstParams->val_g[4], 0, 8),\
															reg_crgn_val_gain_x4, GET_BITS(pstParams->val_x[4], 0, 8),\
															reg_crgn_val_gain_y5, GET_BITS(pstParams->val_g[5], 0, 8),\
															reg_crgn_val_gain_x5, GET_BITS(pstParams->val_x[5], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_vsp_crgn_ctrl_15,	reg_crgn_val_gain_y6, GET_BITS(pstParams->val_g[6], 0, 8),\
															reg_crgn_val_gain_x6, GET_BITS(pstParams->val_x[6], 0, 8),\
															reg_crgn_val_gain_y7, GET_BITS(pstParams->val_g[7], 0, 8),\
															reg_crgn_val_gain_x7, GET_BITS(pstParams->val_x[7], 0, 8));
				#if 0	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					/* objMapGainLUT_y,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_01.reg_objt_gain_y0, GET_BITS(pstParams->objMapGainLUT_y[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_01.reg_objt_gain_x0, GET_BITS(pstParams->objMapGainLUT_x[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_01.reg_objt_gain_y1, GET_BITS(pstParams->objMapGainLUT_y[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_01.reg_objt_gain_x1, GET_BITS(pstParams->objMapGainLUT_x[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_02.reg_objt_gain_y2, GET_BITS(pstParams->objMapGainLUT_y[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_02.reg_objt_gain_x2, GET_BITS(pstParams->objMapGainLUT_x[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_02.reg_objt_gain_y3, GET_BITS(pstParams->objMapGainLUT_y[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_02.reg_objt_gain_x3, GET_BITS(pstParams->objMapGainLUT_x[3], 0, 8));
					/* faceMapGainLUT_y,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_03.reg_face_gain_y0, GET_BITS(pstParams->faceMapGainLUT_y[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_03.reg_face_gain_x0, GET_BITS(pstParams->faceMapGainLUT_x[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_03.reg_face_gain_y1, GET_BITS(pstParams->faceMapGainLUT_y[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_03.reg_face_gain_x1, GET_BITS(pstParams->faceMapGainLUT_x[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_04.reg_face_gain_y2, GET_BITS(pstParams->faceMapGainLUT_y[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_04.reg_face_gain_x2, GET_BITS(pstParams->faceMapGainLUT_x[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_04.reg_face_gain_y3, GET_BITS(pstParams->faceMapGainLUT_y[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_04.reg_face_gain_x3, GET_BITS(pstParams->faceMapGainLUT_x[3], 0, 8));
					/* hue_g,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_00.reg_crgn_hue_gain_y0, GET_BITS(pstParams->hue_g[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_00.reg_crgn_hue_gain_x0, GET_BITS(pstParams->hue_x[0], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_01.reg_crgn_hue_gain_y1, GET_BITS(pstParams->hue_g[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_01.reg_crgn_hue_gain_x1, GET_BITS(pstParams->hue_x[1], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_02.reg_crgn_hue_gain_y2, GET_BITS(pstParams->hue_g[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_02.reg_crgn_hue_gain_x2, GET_BITS(pstParams->hue_x[2], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_03.reg_crgn_hue_gain_y3, GET_BITS(pstParams->hue_g[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_03.reg_crgn_hue_gain_x3, GET_BITS(pstParams->hue_x[3], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_04.reg_crgn_hue_gain_y4, GET_BITS(pstParams->hue_g[4], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_04.reg_crgn_hue_gain_x4, GET_BITS(pstParams->hue_x[4], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_05.reg_crgn_hue_gain_y5, GET_BITS(pstParams->hue_g[5], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_05.reg_crgn_hue_gain_x5, GET_BITS(pstParams->hue_x[5], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_06.reg_crgn_hue_gain_y6, GET_BITS(pstParams->hue_g[6], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_06.reg_crgn_hue_gain_x6, GET_BITS(pstParams->hue_x[6], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_07.reg_crgn_hue_gain_y7, GET_BITS(pstParams->hue_g[7], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_07.reg_crgn_hue_gain_x7, GET_BITS(pstParams->hue_x[7], 0, 10));
					/* sat_g,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_08.reg_crgn_sat_gain_y0, GET_BITS(pstParams->sat_g[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_08.reg_crgn_sat_gain_x0, GET_BITS(pstParams->sat_x[0], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_08.reg_crgn_sat_gain_y1, GET_BITS(pstParams->sat_g[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_08.reg_crgn_sat_gain_x1, GET_BITS(pstParams->sat_x[1], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_09.reg_crgn_sat_gain_y2, GET_BITS(pstParams->sat_g[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_09.reg_crgn_sat_gain_x2, GET_BITS(pstParams->sat_x[2], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_09.reg_crgn_sat_gain_y3, GET_BITS(pstParams->sat_g[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_09.reg_crgn_sat_gain_x3, GET_BITS(pstParams->sat_x[3], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_10.reg_crgn_sat_gain_y4, GET_BITS(pstParams->sat_g[4], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_10.reg_crgn_sat_gain_x4, GET_BITS(pstParams->sat_x[4], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_10.reg_crgn_sat_gain_y5, GET_BITS(pstParams->sat_g[5], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_10.reg_crgn_sat_gain_x5, GET_BITS(pstParams->sat_x[5], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_11.reg_crgn_sat_gain_y6, GET_BITS(pstParams->sat_g[6], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_11.reg_crgn_sat_gain_x6, GET_BITS(pstParams->sat_x[6], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_11.reg_crgn_sat_gain_y7, GET_BITS(pstParams->sat_g[7], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_11.reg_crgn_sat_gain_x7, GET_BITS(pstParams->sat_x[7], 0, 7));
					/* val_g,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_12.reg_crgn_val_gain_y0, GET_BITS(pstParams->val_g[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_12.reg_crgn_val_gain_x0, GET_BITS(pstParams->val_x[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_12.reg_crgn_val_gain_y1, GET_BITS(pstParams->val_g[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_12.reg_crgn_val_gain_x1, GET_BITS(pstParams->val_x[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_13.reg_crgn_val_gain_y2, GET_BITS(pstParams->val_g[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_13.reg_crgn_val_gain_x2, GET_BITS(pstParams->val_x[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_13.reg_crgn_val_gain_y3, GET_BITS(pstParams->val_g[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_13.reg_crgn_val_gain_x3, GET_BITS(pstParams->val_x[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_14.reg_crgn_val_gain_y4, GET_BITS(pstParams->val_g[4], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_14.reg_crgn_val_gain_x4, GET_BITS(pstParams->val_x[4], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_14.reg_crgn_val_gain_y5, GET_BITS(pstParams->val_g[5], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_14.reg_crgn_val_gain_x5, GET_BITS(pstParams->val_x[5], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_15.reg_crgn_val_gain_y6, GET_BITS(pstParams->val_g[6], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_15.reg_crgn_val_gain_x6, GET_BITS(pstParams->val_x[6], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_15.reg_crgn_val_gain_y7, GET_BITS(pstParams->val_g[7], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_15.reg_crgn_val_gain_x7, GET_BITS(pstParams->val_x[7], 0, 8));
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_cc_ctrl_01.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_cc_ctrl_02.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_cc_ctrl_03.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_cc_ctrl_04.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_00.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_01.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_02.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_03.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_04.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_05.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_06.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_07.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_08.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_09.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_10.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_11.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_12.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_13.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_14.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_15.udata32);
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_VSP0);
				} while(0);
				#endif

			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set clear white table setting
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetVspccCtrl2(void *pstParams)
{
	int ret = RET_OK;
#ifdef PE_HW_O26_BRINGUP
	PE_CMG_HW_O26_SETTINGS_T *pInfo=&_g_pe_cmg_hw_o26_info;
	LX_PE_CMG_VSPCC2_CTRL_T *pp;//fix warning: ISO C90 forbids mixed declarations and code
	static LX_PE_CMG_VSPCC2_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;

	do{
		CHECK_KNULL(pstParams);
		pp = (LX_PE_CMG_VSPCC2_CTRL_T *)pstParams;
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMG_VSPCC_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_VSPCC2_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMG_HW_O26_DBG_PRINT("set[%d] \n"\
			"headMap0Gain  : %d\n" \
			"bodyMap0Gain  : %d\n" \
			"textMap0Gain  : %d\n" \
			"motionMap0Gain: %d\n" \
			"headMap1Gain  : %d\n" \
			"bodyMap1Gain  : %d\n" \
			"textMap1Gain  : %d\n" \
			"motionMap1Gain: %d\n" \
			"headMap0GainLUT_x:%d, %d, %d, %d\n" \
			"headMap0GainLUT_y:%d, %d, %d, %d\n" \
			"bodyMap0GainLUT_x:%d, %d, %d, %d\n" \
			"bodyMap0GainLUT_y:%d, %d, %d, %d\n" \
			"textMap0GainLUT_x:%d, %d, %d, %d\n" \
			"textMap0GainLUT_y:%d, %d, %d, %d\n" \
			"motionMap0GainLUT_x:%d, %d, %d, %d\n" \
			"motionMap0GainLUT_y:%d, %d, %d, %d\n" \
			"headMap1GainLUT_x:%d, %d, %d, %d\n" \
			"headMap1GainLUT_y:%d, %d, %d, %d\n" \
			"bodyMap1GainLUT_x:%d, %d, %d, %d\n" \
			"bodyMap1GainLUT_y:%d, %d, %d, %d\n" \
			"textMap1GainLUT_x:%d, %d, %d, %d\n" \
			"textMap1GainLUT_y:%d, %d, %d, %d\n"
			"motionMap1GainLUT_x:%d, %d, %d, %d\n"\
			"motionMap1GainLUT_y:%d, %d, %d, %d\n",\ 
			pp->win_id, \
			pp->headMap0Gain, \ 
			pp->bodyMap0Gain, \ 
			pp->textMap0Gain, \ 
			pp->motionMap0Gain, \
			pp->headMap1Gain, \
			pp->bodyMap1Gain, \
			pp->textMap1Gain, \
			pp->motionMap1Gain, \
			pp->headMap0GainLUT_x[0], pp->headMap0GainLUT_x[1], pp->headMap0GainLUT_x[2], pp->headMap0GainLUT_x[3], \
			pp->headMap0GainLUT_y[0], pp->headMap0GainLUT_y[1], pp->headMap0GainLUT_y[2], pp->headMap0GainLUT_y[3], \
			pp->bodyMap0GainLUT_x[0], pp->bodyMap0GainLUT_x[1], pp->bodyMap0GainLUT_x[2], pp->bodyMap0GainLUT_x[3], \
			pp->bodyMap0GainLUT_y[0], pp->bodyMap0GainLUT_y[1], pp->bodyMap0GainLUT_y[2], pp->bodyMap0GainLUT_y[3], \
			pp->textMap0GainLUT_x[0], pp->textMap0GainLUT_x[1], pp->textMap0GainLUT_x[2], pp->textMap0GainLUT_x[3], \
			pp->textMap0GainLUT_y[0], pp->textMap0GainLUT_y[1], pp->textMap0GainLUT_y[2], pp->textMap0GainLUT_y[3], \
			pp->motionMap0GainLUT_x[0], pp->motionMap0GainLUT_x[1], pp->motionMap0GainLUT_x[2], pp->motionMap0GainLUT_x[3], \
			pp->motionMap0GainLUT_y[0], pp->motionMap0GainLUT_y[1], pp->motionMap0GainLUT_y[2], pp->motionMap0GainLUT_y[3], \
			pp->headMap1GainLUT_x[0], pp->headMap1GainLUT_x[1], pp->headMap1GainLUT_x[2], pp->headMap1GainLUT_x[3], \
			pp->headMap1GainLUT_y[0], pp->headMap1GainLUT_y[1], pp->headMap1GainLUT_y[2], pp->headMap1GainLUT_y[3], \
			pp->bodyMap1GainLUT_x[0], pp->bodyMap1GainLUT_x[1], pp->bodyMap1GainLUT_x[2], pp->bodyMap1GainLUT_x[3], \
			pp->bodyMap1GainLUT_y[0], pp->bodyMap1GainLUT_y[1], pp->bodyMap1GainLUT_y[2], pp->bodyMap1GainLUT_y[3], \
			pp->textMap1GainLUT_x[0], pp->textMap1GainLUT_x[1], pp->textMap1GainLUT_x[2], pp->textMap1GainLUT_x[3], \
			pp->textMap1GainLUT_y[0], pp->textMap1GainLUT_y[1], pp->textMap1GainLUT_y[2], pp->textMap1GainLUT_y[3], \
			pp->motionMap1GainLUT_x[0], pp->motionMap1GainLUT_x[1], pp->motionMap1GainLUT_x[2], pp->motionMap1GainLUT_x[3], \
			pp->motionMap1GainLUT_y[0], pp->motionMap1GainLUT_y[1], pp->motionMap1GainLUT_y[2], pp->motionMap1GainLUT_y[3]);

		if(PE_KDRV_VER_O26)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/** map 0 **/			
				/* hue_g,x */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_01, 	reg_motion_master_gain, GET_BITS(pp->motionMap0Gain, 0, 8),\
															reg_text_master_gain, GET_BITS(pp->textMap0Gain, 0, 8),\
															reg_body_master_gain, GET_BITS(pp->bodyMap0Gain, 0, 8),\
															reg_head_master_gain, GET_BITS(pp->headMap0Gain, 0, 8));
				/* head map gain */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_02, 	reg_headgain_y1_i, GET_BITS(pp->headMap0GainLUT_y[1], 0, 8),\
															reg_headgain_x1_i, GET_BITS(pp->headMap0GainLUT_x[1], 0, 8),\
															reg_headgain_y0_i, GET_BITS(pp->headMap0GainLUT_y[0], 0, 8),\
															reg_headgain_x0_i, GET_BITS(pp->headMap0GainLUT_x[0], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_03, 	reg_headgain_y2_i, GET_BITS(pp->headMap0GainLUT_y[2], 0, 8),\
															reg_headgain_x2_i, GET_BITS(pp->headMap0GainLUT_x[2], 0, 8),\
															reg_headgain_y3_i, GET_BITS(pp->headMap0GainLUT_y[3], 0, 8),\
															reg_headgain_x3_i, GET_BITS(pp->headMap0GainLUT_x[3], 0, 8));
				/* body map gain */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_04, 	reg_bodygain_y1_i, GET_BITS(pp->bodyMap0GainLUT_y[1], 0, 8),\
															reg_bodygain_x1_i, GET_BITS(pp->bodyMap0GainLUT_x[1], 0, 8),\
															reg_bodygain_y0_i, GET_BITS(pp->bodyMap0GainLUT_y[0], 0, 8),\
															reg_bodygain_x0_i, GET_BITS(pp->bodyMap0GainLUT_x[0], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_05, 	reg_bodygain_y2_i, GET_BITS(pp->bodyMap0GainLUT_y[2], 0, 8),\
															reg_bodygain_x2_i, GET_BITS(pp->bodyMap0GainLUT_x[2], 0, 8),\
															reg_bodygain_y3_i, GET_BITS(pp->bodyMap0GainLUT_y[3], 0, 8),\
															reg_bodygain_x3_i, GET_BITS(pp->bodyMap0GainLUT_x[3], 0, 8));
				/* text map gain */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_06, 	reg_textgain_y1_i, GET_BITS(pp->textMap0GainLUT_y[1], 0, 8),\
															reg_textgain_x1_i, GET_BITS(pp->textMap0GainLUT_x[1], 0, 8),\
															reg_textgain_y0_i, GET_BITS(pp->textMap0GainLUT_y[0], 0, 8),\
															reg_textgain_x0_i, GET_BITS(pp->textMap0GainLUT_x[0], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_07, 	reg_textgain_y2_i, GET_BITS(pp->textMap0GainLUT_y[2], 0, 8),\
															reg_textgain_x2_i, GET_BITS(pp->textMap0GainLUT_x[2], 0, 8),\
															reg_textgain_y3_i, GET_BITS(pp->textMap0GainLUT_y[3], 0, 8),\
															reg_textgain_x3_i, GET_BITS(pp->textMap0GainLUT_x[3], 0, 8));
				/* motion map gain */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_08, 	reg_motiongain_y1_i, GET_BITS(pp->motionMap0GainLUT_y[1], 0, 8),\
															reg_motiongain_x1_i, GET_BITS(pp->motionMap0GainLUT_x[1], 0, 8),\
															reg_motiongain_y0_i, GET_BITS(pp->motionMap0GainLUT_y[0], 0, 8),\
															reg_motiongain_x0_i, GET_BITS(pp->motionMap0GainLUT_x[0], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_09, 	reg_motiongain_y2_i, GET_BITS(pp->motionMap0GainLUT_y[2], 0, 8),\
															reg_motiongain_x2_i, GET_BITS(pp->motionMap0GainLUT_x[2], 0, 8),\
															reg_motiongain_y3_i, GET_BITS(pp->motionMap0GainLUT_y[3], 0, 8),\
															reg_motiongain_x3_i, GET_BITS(pp->motionMap0GainLUT_x[3], 0, 8));


				/** map 1 **/
				/* hue_g,x */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_14, 	reg_motion_master_gain, GET_BITS(pp->motionMap1Gain, 0, 8),\
															reg_text_master_gain, GET_BITS(pp->textMap1Gain, 0, 8),\
															reg_body_master_gain, GET_BITS(pp->bodyMap1Gain, 0, 8),\
															reg_head_master_gain, GET_BITS(pp->headMap1Gain, 0, 8));
				/* head map gain */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_15, 	reg_headgain_y1_i, GET_BITS(pp->headMap1GainLUT_y[1], 0, 8),\
															reg_headgain_x1_i, GET_BITS(pp->headMap1GainLUT_x[1], 0, 8),\
															reg_headgain_y0_i, GET_BITS(pp->headMap1GainLUT_y[0], 0, 8),\
															reg_headgain_x0_i, GET_BITS(pp->headMap1GainLUT_x[0], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_16, 	reg_headgain_y2_i, GET_BITS(pp->headMap1GainLUT_y[2], 0, 8),\
															reg_headgain_x2_i, GET_BITS(pp->headMap1GainLUT_x[2], 0, 8),\
															reg_headgain_y3_i, GET_BITS(pp->headMap1GainLUT_y[3], 0, 8),\
															reg_headgain_x3_i, GET_BITS(pp->headMap1GainLUT_x[3], 0, 8));
				/* body map gain */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_17, 	reg_bodygain_y1_i, GET_BITS(pp->bodyMap1GainLUT_y[1], 0, 8),\
															reg_bodygain_x1_i, GET_BITS(pp->bodyMap1GainLUT_x[1], 0, 8),\
															reg_bodygain_y0_i, GET_BITS(pp->bodyMap1GainLUT_y[0], 0, 8),\
															reg_bodygain_x0_i, GET_BITS(pp->bodyMap1GainLUT_x[0], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_18, 	reg_bodygain_y2_i, GET_BITS(pp->bodyMap1GainLUT_y[2], 0, 8),\
															reg_bodygain_x2_i, GET_BITS(pp->bodyMap1GainLUT_x[2], 0, 8),\
															reg_bodygain_y3_i, GET_BITS(pp->bodyMap1GainLUT_y[3], 0, 8),\
															reg_bodygain_x3_i, GET_BITS(pp->bodyMap1GainLUT_x[3], 0, 8));
				/* text map gain */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_19, 	reg_textgain_y1_i, GET_BITS(pp->textMap1GainLUT_y[1], 0, 8),\
															reg_textgain_x1_i, GET_BITS(pp->textMap1GainLUT_x[1], 0, 8),\
															reg_textgain_y0_i, GET_BITS(pp->textMap1GainLUT_y[0], 0, 8),\
															reg_textgain_x0_i, GET_BITS(pp->textMap1GainLUT_x[0], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_20, 	reg_textgain_y2_i, GET_BITS(pp->textMap1GainLUT_y[2], 0, 8),\
															reg_textgain_x2_i, GET_BITS(pp->textMap1GainLUT_x[2], 0, 8),\
															reg_textgain_y3_i, GET_BITS(pp->textMap1GainLUT_y[3], 0, 8),\
															reg_textgain_x3_i, GET_BITS(pp->textMap1GainLUT_x[3], 0, 8));
				/* motion map gain */
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_21, 	reg_motiongain_y1_i, GET_BITS(pp->motionMap1GainLUT_y[1], 0, 8),\
															reg_motiongain_x1_i, GET_BITS(pp->motionMap1GainLUT_x[1], 0, 8),\
															reg_motiongain_y0_i, GET_BITS(pp->motionMap1GainLUT_y[0], 0, 8),\
															reg_motiongain_x0_i, GET_BITS(pp->motionMap1GainLUT_x[0], 0, 8));
				PE_CC2_PE1_O26_QWr04(pe1_merge_ctrl_22, 	reg_motiongain_y2_i, GET_BITS(pp->motionMap1GainLUT_y[2], 0, 8),\
															reg_motiongain_x2_i, GET_BITS(pp->motionMap1GainLUT_x[2], 0, 8),\
															reg_motiongain_y3_i, GET_BITS(pp->motionMap1GainLUT_y[3], 0, 8),\
															reg_motiongain_x3_i, GET_BITS(pp->motionMap1GainLUT_x[3], 0, 8));
			#if 0	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					/* objMapGainLUT_y,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_01.reg_objt_gain_y0, GET_BITS(pp->objMapGainLUT_y[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_01.reg_objt_gain_x0, GET_BITS(pp->objMapGainLUT_x[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_01.reg_objt_gain_y1, GET_BITS(pp->objMapGainLUT_y[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_01.reg_objt_gain_x1, GET_BITS(pp->objMapGainLUT_x[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_02.reg_objt_gain_y2, GET_BITS(pp->objMapGainLUT_y[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_02.reg_objt_gain_x2, GET_BITS(pp->objMapGainLUT_x[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_02.reg_objt_gain_y3, GET_BITS(pp->objMapGainLUT_y[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_02.reg_objt_gain_x3, GET_BITS(pp->objMapGainLUT_x[3], 0, 8));
					/* faceMapGainLUT_y,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_03.reg_face_gain_y0, GET_BITS(pp->faceMapGainLUT_y[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_03.reg_face_gain_x0, GET_BITS(pp->faceMapGainLUT_x[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_03.reg_face_gain_y1, GET_BITS(pp->faceMapGainLUT_y[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_03.reg_face_gain_x1, GET_BITS(pp->faceMapGainLUT_x[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_04.reg_face_gain_y2, GET_BITS(pp->faceMapGainLUT_y[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_04.reg_face_gain_x2, GET_BITS(pp->faceMapGainLUT_x[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_04.reg_face_gain_y3, GET_BITS(pp->faceMapGainLUT_y[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_cc_ctrl_04.reg_face_gain_x3, GET_BITS(pp->faceMapGainLUT_x[3], 0, 8));
					/* hue_g,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_00.reg_crgn_hue_gain_y0, GET_BITS(pp->hue_g[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_00.reg_crgn_hue_gain_x0, GET_BITS(pp->hue_x[0], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_01.reg_crgn_hue_gain_y1, GET_BITS(pp->hue_g[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_01.reg_crgn_hue_gain_x1, GET_BITS(pp->hue_x[1], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_02.reg_crgn_hue_gain_y2, GET_BITS(pp->hue_g[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_02.reg_crgn_hue_gain_x2, GET_BITS(pp->hue_x[2], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_03.reg_crgn_hue_gain_y3, GET_BITS(pp->hue_g[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_03.reg_crgn_hue_gain_x3, GET_BITS(pp->hue_x[3], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_04.reg_crgn_hue_gain_y4, GET_BITS(pp->hue_g[4], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_04.reg_crgn_hue_gain_x4, GET_BITS(pp->hue_x[4], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_05.reg_crgn_hue_gain_y5, GET_BITS(pp->hue_g[5], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_05.reg_crgn_hue_gain_x5, GET_BITS(pp->hue_x[5], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_06.reg_crgn_hue_gain_y6, GET_BITS(pp->hue_g[6], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_06.reg_crgn_hue_gain_x6, GET_BITS(pp->hue_x[6], 0, 10));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_07.reg_crgn_hue_gain_y7, GET_BITS(pp->hue_g[7], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_07.reg_crgn_hue_gain_x7, GET_BITS(pp->hue_x[7], 0, 10));
					/* sat_g,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_08.reg_crgn_sat_gain_y0, GET_BITS(pp->sat_g[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_08.reg_crgn_sat_gain_x0, GET_BITS(pp->sat_x[0], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_08.reg_crgn_sat_gain_y1, GET_BITS(pp->sat_g[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_08.reg_crgn_sat_gain_x1, GET_BITS(pp->sat_x[1], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_09.reg_crgn_sat_gain_y2, GET_BITS(pp->sat_g[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_09.reg_crgn_sat_gain_x2, GET_BITS(pp->sat_x[2], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_09.reg_crgn_sat_gain_y3, GET_BITS(pp->sat_g[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_09.reg_crgn_sat_gain_x3, GET_BITS(pp->sat_x[3], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_10.reg_crgn_sat_gain_y4, GET_BITS(pp->sat_g[4], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_10.reg_crgn_sat_gain_x4, GET_BITS(pp->sat_x[4], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_10.reg_crgn_sat_gain_y5, GET_BITS(pp->sat_g[5], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_10.reg_crgn_sat_gain_x5, GET_BITS(pp->sat_x[5], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_11.reg_crgn_sat_gain_y6, GET_BITS(pp->sat_g[6], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_11.reg_crgn_sat_gain_x6, GET_BITS(pp->sat_x[6], 0, 7));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_11.reg_crgn_sat_gain_y7, GET_BITS(pp->sat_g[7], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_11.reg_crgn_sat_gain_x7, GET_BITS(pp->sat_x[7], 0, 7));
					/* val_g,x */
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_12.reg_crgn_val_gain_y0, GET_BITS(pp->val_g[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_12.reg_crgn_val_gain_x0, GET_BITS(pp->val_x[0], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_12.reg_crgn_val_gain_y1, GET_BITS(pp->val_g[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_12.reg_crgn_val_gain_x1, GET_BITS(pp->val_x[1], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_13.reg_crgn_val_gain_y2, GET_BITS(pp->val_g[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_13.reg_crgn_val_gain_x2, GET_BITS(pp->val_x[2], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_13.reg_crgn_val_gain_y3, GET_BITS(pp->val_g[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_13.reg_crgn_val_gain_x3, GET_BITS(pp->val_x[3], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_14.reg_crgn_val_gain_y4, GET_BITS(pp->val_g[4], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_14.reg_crgn_val_gain_x4, GET_BITS(pp->val_x[4], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_14.reg_crgn_val_gain_y5, GET_BITS(pp->val_g[5], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_14.reg_crgn_val_gain_x5, GET_BITS(pp->val_x[5], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_15.reg_crgn_val_gain_y6, GET_BITS(pp->val_g[6], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_15.reg_crgn_val_gain_x6, GET_BITS(pp->val_x[6], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_15.reg_crgn_val_gain_y7, GET_BITS(pp->val_g[7], 0, 8));
					PE_CHPI_APB0_O26F22_Wr(vsp0.pe1_vsp_crgn_ctrl_15.reg_crgn_val_gain_x7, GET_BITS(pp->val_x[7], 0, 8));
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_cc_ctrl_01.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_cc_ctrl_02.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_cc_ctrl_03.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_cc_ctrl_04.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_00.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_01.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_02.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_03.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_04.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_05.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_06.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_07.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_08.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_09.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_10.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_11.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_12.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_13.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_14.udata32);
					PE_CHPI_APB0_O26F22_WrFL(vsp0.pe1_vsp_crgn_ctrl_15.udata32);
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_VSP0);
				} while(0);
			#endif

			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set dse ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 count = 0;
	UINT32 color_out_gain, x_data, y_data;
	UINT32 dse_lut_param[PE_CMG_HW_O26_LUT_STEP];
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_CMG_DSE_CTRL_T *pp=(LX_PE_CMG_DSE_CTRL_T *)pstParams;
			static LX_PE_CMG_DSE_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			//PE_CHECK_DUPLICATE(LX_PE_CMG_DSE_CTRL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_CMG_HW_O26_DBG_PRINT("duplicated DB : LX_PE_CMG_DSE_CTRL_T\n");
				ret=RET_OK;
				break;
			}
			color_out_gain = (pp->saturation_region_gain==0)? \
				0x1:pp->saturation_region_gain;
			PE_CMG_HW_O26_DBG_PRINT("[wid:%d] set: saturation_cr_mode:%d, saturation_region_gain:%d\n"\
				"region sel:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
				pp->win_id,\
				pp->saturation_cr_mode, pp->saturation_region_gain, \
				pp->region_onoff[0],pp->region_onoff[1],pp->region_onoff[2],pp->region_onoff[3],\
				pp->region_onoff[4],pp->region_onoff[5],pp->region_onoff[6],pp->region_onoff[7],\
				pp->region_onoff[8],pp->region_onoff[9],pp->region_onoff[10],pp->region_onoff[11],\
				pp->region_onoff[12],pp->region_onoff[13],pp->region_onoff[14],pp->region_onoff[15]);
			PE_CMG_HW_O26_DBG_PRINT("[wid:%d] set: n"\
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
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CC_PE1_O26_RdFL(pe1_dse_ctrl_00);
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region0_sel,	GET_BITS(pp->region_onoff[0],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region1_sel,	GET_BITS(pp->region_onoff[1],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region2_sel,	GET_BITS(pp->region_onoff[2],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region3_sel,	GET_BITS(pp->region_onoff[3],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region4_sel,	GET_BITS(pp->region_onoff[4],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region5_sel,	GET_BITS(pp->region_onoff[5],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region6_sel,	GET_BITS(pp->region_onoff[6],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region7_sel,	GET_BITS(pp->region_onoff[7],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region8_sel,	GET_BITS(pp->region_onoff[8],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region9_sel,	GET_BITS(pp->region_onoff[9],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region10_sel,	GET_BITS(pp->region_onoff[10],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region11_sel,	GET_BITS(pp->region_onoff[11],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region12_sel,	GET_BITS(pp->region_onoff[12],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region13_sel,	GET_BITS(pp->region_onoff[13],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region14_sel,	GET_BITS(pp->region_onoff[14],0,1));
				PE_CC_PE1_O26_Wr01(pe1_dse_ctrl_00,	color_region15_sel,	GET_BITS(pp->region_onoff[15],0,1));
				PE_CC_PE1_O26_WrFL(pe1_dse_ctrl_00);

				PE_CC_PE1_O26_QWr03(pe1_dse_ctrl_01,	reg_dse_cr_mode_sel,GET_BITS(pp->saturation_cr_mode,0,1),\
														reg_yh_cr_en,		GET_BITS(pp->saturation_cr_mode,0,1),\
														color_region_gain,	GET_BITS(color_out_gain,0,8));
				PE_CC_PE1_O26_QWr02(pe_dse_y_region_pt0,	reg_y_region_pt0_y,	GET_BITS(pp->dse_y_y[0],0,8),\
															reg_y_region_pt0_x,	GET_BITS(pp->dse_y_x[0],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_y_region_pt1,	reg_y_region_pt1_y,	GET_BITS(pp->dse_y_y[1],0,8),\
															reg_y_region_pt1_x,	GET_BITS(pp->dse_y_x[1],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_y_region_pt2,	reg_y_region_pt2_y,	GET_BITS(pp->dse_y_y[2],0,8),\
															reg_y_region_pt2_x,	GET_BITS(pp->dse_y_x[2],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_y_region_pt3,	reg_y_region_pt3_y,	GET_BITS(pp->dse_y_y[3],0,8),\
															reg_y_region_pt3_x,	GET_BITS(pp->dse_y_x[3],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_y_region_pt4,	reg_y_region_pt4_y,	GET_BITS(pp->dse_y_y[4],0,8),\
															reg_y_region_pt4_x,	GET_BITS(pp->dse_y_x[4],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_y_region_pt5,	reg_y_region_pt5_y,	GET_BITS(pp->dse_y_y[5],0,8),\
															reg_y_region_pt5_x,	GET_BITS(pp->dse_y_x[5],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_y_region_pt6,	reg_y_region_pt6_y,	GET_BITS(pp->dse_y_y[6],0,8),\
															reg_y_region_pt6_x,	GET_BITS(pp->dse_y_x[6],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_y_region_pt7,	reg_y_region_pt7_y,	GET_BITS(pp->dse_y_y[7],0,8),\
															reg_y_region_pt7_x,	GET_BITS(pp->dse_y_x[7],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_h_region_pt0,	reg_h_region_pt0_y,	GET_BITS(pp->dse_h_y[0],0,8),\
															reg_h_region_pt0_x,	GET_BITS(pp->dse_h_x[0],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_h_region_pt1,	reg_h_region_pt1_y,	GET_BITS(pp->dse_h_y[1],0,8),\
															reg_h_region_pt1_x,	GET_BITS(pp->dse_h_x[1],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_h_region_pt2,	reg_h_region_pt2_y,	GET_BITS(pp->dse_h_y[2],0,8),\
															reg_h_region_pt2_x,	GET_BITS(pp->dse_h_x[2],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_h_region_pt3,	reg_h_region_pt3_y,	GET_BITS(pp->dse_h_y[3],0,8),\
															reg_h_region_pt3_x,	GET_BITS(pp->dse_h_x[3],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_h_region_pt4,	reg_h_region_pt4_y,	GET_BITS(pp->dse_h_y[4],0,8),\
															reg_h_region_pt4_x,	GET_BITS(pp->dse_h_x[4],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_h_region_pt5,	reg_h_region_pt5_y,	GET_BITS(pp->dse_h_y[5],0,8),\
															reg_h_region_pt5_x,	GET_BITS(pp->dse_h_x[5],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_h_region_pt6,	reg_h_region_pt6_y,	GET_BITS(pp->dse_h_y[6],0,8),\
															reg_h_region_pt6_x,	GET_BITS(pp->dse_h_x[6],0,10));
				PE_CC_PE1_O26_QWr02(pe_dse_h_region_pt7,	reg_h_region_pt7_y,	GET_BITS(pp->dse_h_y[7],0,8),\
															reg_h_region_pt7_x,	GET_BITS(pp->dse_h_x[7],0,10));
				PE_CC_PE1_O26_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_O26_RdFL(pe1_dse_ia_data);
				PE_CC_PE1_O26_RdFL(pe1_dce_ctrl_08);
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_CC_PE1_O26_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<PE_CMG_HW_O26_LUT_STEP;count++)
				{
					PE_CC_PE1_O26_Wr01(pe1_dse_ia_data,hif_dse_wdata_y,GET_BITS(pp->sSaturationLUT_y[count],0,10));	//y data
					PE_CC_PE1_O26_Wr01(pe1_dse_ia_data,hif_dse_wdata_x,GET_BITS(pp->sSaturationLUT_x[count],0,10));//x data
					PE_CC_PE1_O26_WrFL(pe1_dse_ia_data);
					x_data = (UINT32)(pp->sSaturationLUT_x[count])<<16;
					y_data = (UINT32)(pp->sSaturationLUT_y[count]);
					if (y_data>1023)
					{
						y_data=1023;
					}
					dse_lut_param[count] = x_data + y_data;
				}
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_CC_PE1_O26_WrFL(pe1_dse_ia_ctrl);
				memcpy(_g_cmg_hw_o26_pre_dse_lut, dse_lut_param, sizeof(UINT32)*PE_CMG_HW_O26_LUT_STEP);
				if(_g_cmg_hw_o26_trace)
				{
					PE_CMG_HW_O26_DBG_PRINT("\n update dse lut\n");
					PE_CMG_HW_O26_DBG_PRINT("\n   [ i]    x,    y\n");
					for (count=0;count<(PE_CMG_HW_O26_LUT_MAX-1);count++)
					{
						PE_CMG_HW_O26_DBG_PRINT("   [%02d] %4d, %4d\n", \
							count, (_g_cmg_hw_o26_pre_dse_lut[count]>>16)&0x3ff, _g_cmg_hw_o26_pre_dse_lut[count]&0x3ff);
					}
				}
				#if 1	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					for(count=0;count<PE_CMG_HW_O26_LUT_STEP;count++)
					{
						PE_CHPI_APB0_O26F22_QWr(dse0.pe1_dse_ia_data[count].udata32,dse_lut_param[count]);
					}
					PE_CHPI_APB0_O26F22_Wr(dse0.pe1_dse_ctrl_01.reg_dse_cr_mode_sel,GET_BITS(pp->saturation_cr_mode,0,1));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe1_dse_ctrl_01.reg_yh_cr_en,GET_BITS(pp->saturation_cr_mode,0,1));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe1_dse_ctrl_01.color_region_gain,GET_BITS(color_out_gain,0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt0.reg_y_region_pt0_y,GET_BITS(pp->dse_y_y[0],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt0.reg_y_region_pt0_x,GET_BITS(pp->dse_y_x[0],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt1.reg_y_region_pt1_y,GET_BITS(pp->dse_y_y[1],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt1.reg_y_region_pt1_x,GET_BITS(pp->dse_y_x[1],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt2.reg_y_region_pt2_y,GET_BITS(pp->dse_y_y[2],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt2.reg_y_region_pt2_x,GET_BITS(pp->dse_y_x[2],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt3.reg_y_region_pt3_y,GET_BITS(pp->dse_y_y[3],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt3.reg_y_region_pt3_x,GET_BITS(pp->dse_y_x[3],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt4.reg_y_region_pt4_y,GET_BITS(pp->dse_y_y[4],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt4.reg_y_region_pt4_x,GET_BITS(pp->dse_y_x[4],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt5.reg_y_region_pt5_y,GET_BITS(pp->dse_y_y[5],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt5.reg_y_region_pt5_x,GET_BITS(pp->dse_y_x[5],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt6.reg_y_region_pt6_y,GET_BITS(pp->dse_y_y[6],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt6.reg_y_region_pt6_x,GET_BITS(pp->dse_y_x[6],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt7.reg_y_region_pt7_y,GET_BITS(pp->dse_y_y[7],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_y_region_pt7.reg_y_region_pt7_x,GET_BITS(pp->dse_y_x[7],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt0.reg_h_region_pt0_y,GET_BITS(pp->dse_h_y[0],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt0.reg_h_region_pt0_x,GET_BITS(pp->dse_h_x[0],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt1.reg_h_region_pt1_y,GET_BITS(pp->dse_h_y[1],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt1.reg_h_region_pt1_x,GET_BITS(pp->dse_h_x[1],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt2.reg_h_region_pt2_y,GET_BITS(pp->dse_h_y[2],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt2.reg_h_region_pt2_x,GET_BITS(pp->dse_h_x[2],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt3.reg_h_region_pt3_y,GET_BITS(pp->dse_h_y[3],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt3.reg_h_region_pt3_x,GET_BITS(pp->dse_h_x[3],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt4.reg_h_region_pt4_y,GET_BITS(pp->dse_h_y[4],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt4.reg_h_region_pt4_x,GET_BITS(pp->dse_h_x[4],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt5.reg_h_region_pt5_y,GET_BITS(pp->dse_h_y[5],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt5.reg_h_region_pt5_x,GET_BITS(pp->dse_h_x[5],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt6.reg_h_region_pt6_y,GET_BITS(pp->dse_h_y[6],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt6.reg_h_region_pt6_x,GET_BITS(pp->dse_h_x[6],0,10));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt7.reg_h_region_pt7_y,GET_BITS(pp->dse_h_y[7],0,8));
					PE_CHPI_APB0_O26F22_Wr(dse0.pe_dse_h_region_pt7.reg_h_region_pt7_x,GET_BITS(pp->dse_h_x[7],0,10));
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe1_dse_ctrl_01.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_y_region_pt0.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_y_region_pt1.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_y_region_pt2.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_y_region_pt3.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_y_region_pt4.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_y_region_pt5.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_y_region_pt6.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_y_region_pt7.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_h_region_pt0.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_h_region_pt1.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_h_region_pt2.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_h_region_pt3.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_h_region_pt4.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_h_region_pt5.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_h_region_pt6.udata32);
					PE_CHPI_APB0_O26F22_WrFL(dse0.pe_dse_h_region_pt7.udata32);
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_DSE0);
				} while(0);
				#endif
				#if 1	/* O26F22_TBL */
				do {
					if (!gPE_CHPI_DDR_O26)	break;

					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region0_sel,GET_BITS(pp->region_onoff[0],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region1_sel,GET_BITS(pp->region_onoff[1],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region2_sel,GET_BITS(pp->region_onoff[2],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region3_sel,GET_BITS(pp->region_onoff[3],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region4_sel,GET_BITS(pp->region_onoff[4],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region5_sel,GET_BITS(pp->region_onoff[5],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region6_sel,GET_BITS(pp->region_onoff[6],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region7_sel,GET_BITS(pp->region_onoff[7],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region8_sel,GET_BITS(pp->region_onoff[8],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region9_sel,GET_BITS(pp->region_onoff[9],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region10_sel,GET_BITS(pp->region_onoff[10],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region11_sel,GET_BITS(pp->region_onoff[11],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region12_sel,GET_BITS(pp->region_onoff[12],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region13_sel,GET_BITS(pp->region_onoff[13],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region14_sel,GET_BITS(pp->region_onoff[14],0,1));
					PE_CHPI_TBL0_O26F22_Wr(cco.pe1_dse_ctrl_00.color_region15_sel,GET_BITS(pp->region_onoff[15],0,1));
					PE_CHPI_TBL0_O26F22_WrFL(cco.pe1_dse_ctrl_00.udata32);

					/* count */
					PE_INF_O26_IncChipInfoTblCount(PE_INF_O26_CHPI_TBL_CCO);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;

}

/**
 * get dse ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_GetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 count = 0;
	//int i = 0;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_CMG_DSE_CTRL_T *pp=(LX_PE_CMG_DSE_CTRL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CC_PE1_O26_RdFL(pe1_dse_ctrl_00);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region0_sel,	pp->region_onoff[0]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region1_sel,	pp->region_onoff[1]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region2_sel,	pp->region_onoff[2]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region3_sel,	pp->region_onoff[3]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region4_sel,	pp->region_onoff[4]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region5_sel,	pp->region_onoff[5]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region6_sel,	pp->region_onoff[6]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region7_sel,	pp->region_onoff[7]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region8_sel,	pp->region_onoff[8]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region9_sel,	pp->region_onoff[9]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region10_sel,	pp->region_onoff[10]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region11_sel,	pp->region_onoff[11]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region12_sel,	pp->region_onoff[12]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region13_sel,	pp->region_onoff[13]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region14_sel,	pp->region_onoff[14]);
				PE_CC_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region15_sel,	pp->region_onoff[15]);
				PE_CC_PE1_O26_RdFL(pe1_dse_ctrl_00);

				PE_CC_PE1_O26_QRd03(pe1_dse_ctrl_01,		reg_dse_cr_mode_sel,pp->saturation_cr_mode,\
															reg_yh_cr_en,		pp->saturation_cr_mode,\
															color_region_gain,	pp->saturation_region_gain);
				PE_CC_PE1_O26_QRd02(pe_dse_y_region_pt0,	reg_y_region_pt0_y,	pp->dse_y_y[0],\
															reg_y_region_pt0_x,	pp->dse_y_x[0]);
				PE_CC_PE1_O26_QRd02(pe_dse_y_region_pt1,	reg_y_region_pt1_y,	pp->dse_y_y[1],\
															reg_y_region_pt1_x,	pp->dse_y_x[1]);
				PE_CC_PE1_O26_QRd02(pe_dse_y_region_pt2,	reg_y_region_pt2_y,	pp->dse_y_y[2],\
															reg_y_region_pt2_x,	pp->dse_y_x[2]);
				PE_CC_PE1_O26_QRd02(pe_dse_y_region_pt3,	reg_y_region_pt3_y,	pp->dse_y_y[3],\
															reg_y_region_pt3_x,	pp->dse_y_x[3]);
				PE_CC_PE1_O26_QRd02(pe_dse_y_region_pt4,	reg_y_region_pt4_y,	pp->dse_y_y[4],\
															reg_y_region_pt4_x,	pp->dse_y_x[4]);
				PE_CC_PE1_O26_QRd02(pe_dse_y_region_pt5,	reg_y_region_pt5_y,	pp->dse_y_y[5],\
															reg_y_region_pt5_x,	pp->dse_y_x[5]);
				PE_CC_PE1_O26_QRd02(pe_dse_y_region_pt6,	reg_y_region_pt6_y,	pp->dse_y_y[6],\
															reg_y_region_pt6_x,	pp->dse_y_x[6]);
				PE_CC_PE1_O26_QRd02(pe_dse_y_region_pt7,	reg_y_region_pt7_y,	pp->dse_y_y[7],\
															reg_y_region_pt7_x,	pp->dse_y_x[7]);
				PE_CC_PE1_O26_QRd02(pe_dse_h_region_pt0,	reg_h_region_pt0_y,	pp->dse_h_y[0],\
															reg_h_region_pt0_x,	pp->dse_h_x[0]);
				PE_CC_PE1_O26_QRd02(pe_dse_h_region_pt1,	reg_h_region_pt1_y,	pp->dse_h_y[1],\
															reg_h_region_pt1_x,	pp->dse_h_x[1]);
				PE_CC_PE1_O26_QRd02(pe_dse_h_region_pt2,	reg_h_region_pt2_y,	pp->dse_h_y[2],\
															reg_h_region_pt2_x,	pp->dse_h_x[2]);
				PE_CC_PE1_O26_QRd02(pe_dse_h_region_pt3,	reg_h_region_pt3_y,	pp->dse_h_y[3],\
															reg_h_region_pt3_x,	pp->dse_h_x[3]);
				PE_CC_PE1_O26_QRd02(pe_dse_h_region_pt4,	reg_h_region_pt4_y,	pp->dse_h_y[4],\
															reg_h_region_pt4_x,	pp->dse_h_x[4]);
				PE_CC_PE1_O26_QRd02(pe_dse_h_region_pt5,	reg_h_region_pt5_y,	pp->dse_h_y[5],\
															reg_h_region_pt5_x,	pp->dse_h_x[5]);
				PE_CC_PE1_O26_QRd02(pe_dse_h_region_pt6,	reg_h_region_pt6_y,	pp->dse_h_y[6],\
															reg_h_region_pt6_x,	pp->dse_h_x[6]);
				PE_CC_PE1_O26_QRd02(pe_dse_h_region_pt7,	reg_h_region_pt7_y,	pp->dse_h_y[7],\
															reg_h_region_pt7_x,	pp->dse_h_x[7]);
				PE_CC_PE1_O26_RdFL(pe1_dse_ia_ctrl);
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_CC_PE1_O26_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<PE_CMG_HW_O26_LUT_STEP;count++)
				{
					PE_CC_PE1_O26_QRd02(pe1_dse_ia_data, hif_dse_wdata_y, pp->sSaturationLUT_y[count],\
														 hif_dse_wdata_x, pp->sSaturationLUT_x[count]);//x data
				}
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CC_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_CC_PE1_O26_WrFL(pe1_dse_ia_ctrl);
			}
			#if 0
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_CO_PE1_O26_RdFL(pe1_dse_ctrl_00);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region0_sel,	pp->region_onoff[0]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region1_sel,	pp->region_onoff[1]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region2_sel,	pp->region_onoff[2]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region3_sel,	pp->region_onoff[3]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region4_sel,	pp->region_onoff[4]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region5_sel,	pp->region_onoff[5]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region6_sel,	pp->region_onoff[6]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region7_sel,	pp->region_onoff[7]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region8_sel,	pp->region_onoff[8]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region9_sel,	pp->region_onoff[9]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region10_sel,	pp->region_onoff[10]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region11_sel,	pp->region_onoff[11]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region12_sel,	pp->region_onoff[12]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region13_sel,	pp->region_onoff[13]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region14_sel,	pp->region_onoff[14]);
				PE_CO_PE1_O26_Rd01(pe1_dse_ctrl_00,	color_region15_sel,	pp->region_onoff[15]);
				PE_CO_PE1_O26_RdFL(pe1_dse_ctrl_00);

				PE_CO_PE1_O26_QRd03(pe1_dse_ctrl_01,		reg_dse_cr_mode_sel,pp->saturation_cr_mode,\
															reg_yh_cr_en,		pp->saturation_cr_mode,\
															color_region_gain,	pp->saturation_region_gain);
				PE_CO_PE1_O26_QRd02(pe_dse_y_region_pt0,	reg_y_region_pt0_y,	pp->dse_y_y[0],\
															reg_y_region_pt0_x,	pp->dse_y_x[0]);
				PE_CO_PE1_O26_QRd02(pe_dse_y_region_pt1,	reg_y_region_pt1_y,	pp->dse_y_y[1],\
															reg_y_region_pt1_x,	pp->dse_y_x[1]);
				PE_CO_PE1_O26_QRd02(pe_dse_y_region_pt2,	reg_y_region_pt2_y,	pp->dse_y_y[2],\
															reg_y_region_pt2_x,	pp->dse_y_x[2]);
				PE_CO_PE1_O26_QRd02(pe_dse_y_region_pt3,	reg_y_region_pt3_y,	pp->dse_y_y[3],\
															reg_y_region_pt3_x,	pp->dse_y_x[3]);
				PE_CO_PE1_O26_QRd02(pe_dse_y_region_pt4,	reg_y_region_pt4_y,	pp->dse_y_y[4],\
															reg_y_region_pt4_x,	pp->dse_y_x[4]);
				PE_CO_PE1_O26_QRd02(pe_dse_y_region_pt5,	reg_y_region_pt5_y,	pp->dse_y_y[5],\
															reg_y_region_pt5_x,	pp->dse_y_x[5]);
				PE_CO_PE1_O26_QRd02(pe_dse_y_region_pt6,	reg_y_region_pt6_y,	pp->dse_y_y[6],\
															reg_y_region_pt6_x,	pp->dse_y_x[6]);
				PE_CO_PE1_O26_QRd02(pe_dse_y_region_pt7,	reg_y_region_pt7_y,	pp->dse_y_y[7],\
															reg_y_region_pt7_x,	pp->dse_y_x[7]);
				PE_CO_PE1_O26_QRd02(pe_dse_h_region_pt0,	reg_h_region_pt0_y,	pp->dse_h_y[0],\
															reg_h_region_pt0_x,	pp->dse_h_x[0]);
				PE_CO_PE1_O26_QRd02(pe_dse_h_region_pt1,	reg_h_region_pt1_y,	pp->dse_h_y[1],\
															reg_h_region_pt1_x,	pp->dse_h_x[1]);
				PE_CO_PE1_O26_QRd02(pe_dse_h_region_pt2,	reg_h_region_pt2_y,	pp->dse_h_y[2],\
															reg_h_region_pt2_x,	pp->dse_h_x[2]);
				PE_CO_PE1_O26_QRd02(pe_dse_h_region_pt3,	reg_h_region_pt3_y,	pp->dse_h_y[3],\
															reg_h_region_pt3_x,	pp->dse_h_x[3]);
				PE_CO_PE1_O26_QRd02(pe_dse_h_region_pt4,	reg_h_region_pt4_y,	pp->dse_h_y[4],\
															reg_h_region_pt4_x,	pp->dse_h_x[4]);
				PE_CO_PE1_O26_QRd02(pe_dse_h_region_pt5,	reg_h_region_pt5_y,	pp->dse_h_y[5],\
															reg_h_region_pt5_x,	pp->dse_h_x[5]);
				PE_CO_PE1_O26_QRd02(pe_dse_h_region_pt6,	reg_h_region_pt6_y,	pp->dse_h_y[6],\
															reg_h_region_pt6_x,	pp->dse_h_x[6]);
				PE_CO_PE1_O26_QRd02(pe_dse_h_region_pt7,	reg_h_region_pt7_y,	pp->dse_h_y[7],\
															reg_h_region_pt7_x,	pp->dse_h_x[7]);
				PE_CO_PE1_O26_RdFL(pe1_dse_ia_ctrl);
				PE_CO_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_CO_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_CO_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_CO_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_CO_PE1_O26_WrFL(pe1_dse_ia_ctrl);
				for(count=0;count<PE_CMG_HW_O26_LUT_STEP;count++)
				{
					PE_CO_PE1_O26_QRd02(pe1_dse_ia_data,hif_dse_wdata_y,pp->sSaturationLUT_y[count],\
														hif_dse_wdata_x,pp->sSaturationLUT_x[count]);//x data
				}
				PE_CO_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_CO_PE1_O26_Wr01(pe1_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_CO_PE1_O26_WrFL(pe1_dse_ia_ctrl);
			}
			#endif
			PE_CMG_HW_O26_DBG_PRINT("[wid:%d] get: saturation_cr_mode:%d, saturation_region_gain:%d\n"\
				"region sel:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
				pp->win_id,\
				pp->saturation_cr_mode, pp->saturation_region_gain, \
				pp->region_onoff[0],pp->region_onoff[1],pp->region_onoff[2],pp->region_onoff[3],\
				pp->region_onoff[4],pp->region_onoff[5],pp->region_onoff[6],pp->region_onoff[7],\
				pp->region_onoff[8],pp->region_onoff[9],pp->region_onoff[10],pp->region_onoff[11],\
				pp->region_onoff[12],pp->region_onoff[13],pp->region_onoff[14],pp->region_onoff[15]);
			PE_CMG_HW_O26_DBG_PRINT("[wid:%d] get: n"\
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
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;

}

/**
 * set target saturation not used @O26
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetTargetSat(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	PE_CMG_HW_O26_SETTINGS_T *pInfo=&_g_pe_cmg_hw_o26_info;
	UINT32 vsp_sat;
	UINT32 org_target_sat = pInfo->org_target_sat;
	UINT32 target_sat;
	do {
		if(PE_KDRV_VER_O26)
		{
			PE_CC2_PE1_O26_QRd01(pe1_vspyc_ctrl_01, saturation, vsp_sat);
			target_sat = (vsp_sat * org_target_sat)>>7; // now 9bit data
			if(target_sat > 255)
				target_sat = 255;
			else
				target_sat &= 0xff; //now 8bit
			if(pInfo->pre_target_sat != target_sat)
			{
				PE_CMG_HW_O26_DBG_PRINT("vsp_sat 0x%02x org_target_sat 0x%02x target sat 0x%02x -> 0x%02x\n",vsp_sat, org_target_sat, pInfo->pre_target_sat, target_sat);
				PE_CC2_PE1_O26_QWr01(pe1_vspyc_ctrl_01, saturation_target, GET_BITS(target_sat, 0, 8));
				pInfo->pre_target_sat = target_sat;
				#if 1	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					PE_CHPI_APB0_O26F22_Wr(cmn0.pe1_vspyc_ctrl_01.saturation_target, GET_BITS(target_sat, 0, 8));
					PE_CHPI_APB0_O26F22_WrFL(cmn0.pe1_vspyc_ctrl_01.udata32);
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CMN0);
					PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
						PE_CHPI_APB0_O26F22_Rd(cmn0.cco_veri_sys_veri_8.uaddr32),PE_CHPI_APB0_O26F22_Rd(cmn0.cco_veri_sys_veri_8.udata32),\
						PE_CHPI_APB0_O26F22_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_O26F22_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
						PE_CHPI_APB0_O26F22_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_O26F22_Rd(cmn0.pe1_cen_ctrl_03.udata32));
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif
	return ret;
}
/**
 * set CenBypass
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_O26_SetCenBypass(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 hdr_effect;
	UINT32 picturemode;
	UINT32 dynamic_cm_ui;
	UINT32 Hoffset;
	UINT32 Sgain;
	UINT32 cur_cen_bypass = 1;
	UINT32 decontour_ui;
	UINT32 net_onoff;// (AI ï¿½å¸£ UI | AI ï¿½ï¿½ï¿?UI)
	LX_PE_INF_DISPLAY_T cur0_inf;
	static UINT32 cnt;
	PE_CMG_HW_O26_SETTINGS_T *pInfo=&_g_pe_cmg_hw_o26_info;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->nrd_dcnt_user.data;
	do {
		if(!p_db_data) 
		{
			break; 
		}
		if(PE_KDRV_VER_O26)
		{
			ret = PE_INF_O26_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf); // to get HDR mode
			dynamic_cm_ui = pInfo->dynamic_cm_ui; //CM ui
			decontour_ui  = p_db_data[1]; //decontour ui ref.PE_NRD_HW_O26_DownloadDnrDcntUserDb
			PE_SR_VERI_O26_RdFL(sys_veri_0);
			net_onoff=PE_SR_VERI_O26_Rd(sys_veri_0);
			PE_CC_PE1_O26_QRd01(pe1_fsw_ctrl_01,reg_hdr_effect,      hdr_effect);
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_03, ihsv_hoffset, Hoffset);
			PE_CC_PE1_O26_QRd01(pe1_cen_ctrl_02, ihsv_sgain,	Sgain);//[7:0] reg_ihsv_sgain
			
			if (lx_chip_rev() >= LX_CHIP_REV(O26, A3))
			{
				#if 0
				if(cur0_inf.mode.is_oled && hdr_effect==0x2 && dynamic_cm_ui==0 && Hoffset==0x80 && Sgain==0x80 &&\
					decontour_ui!=0 && net_onoff ==0)
				{
					cur_cen_bypass = 0x0;
				}
				else
				{
					cur_cen_bypass = 0x1;
				}
				#else
				cur_cen_bypass = 0x1;
				#endif
			}
			else
			{
				if(hdr_effect==0x1 && dynamic_cm_ui==0 && Hoffset==0x80 && Sgain==0x80)
				{
					cur_cen_bypass = 0x0;
				}
				else
				{
					cur_cen_bypass = 0x1;
				}
			}
			if(pInfo->pre_cen_bypass!= cur_cen_bypass)
			{
				if (lx_chip_rev() >= LX_CHIP_REV(O26, A3))
				{
					PE_PRINT_NOTI("[O26N]cen_bypass change!!! %d->%d is_oled:%d, hdr_effect:%d, dynamic_cm_ui:%d, Hoffset:%d, Sgain:%d, hdr_type:%d, decontour_ui:%d, net_onoff:%d\n",\
						pInfo->pre_cen_bypass,cur_cen_bypass,cur0_inf.mode.is_oled,hdr_effect,dynamic_cm_ui,Hoffset,Sgain,	cur0_inf.mode.hdr_type,	decontour_ui,net_onoff);
				}
				else
				{
					PE_PRINT_NOTI("[O26]cen_bypass change!!! %d->%d hdr_effect:%d, dynamic_cm_ui:%d, Hoffset:%d, Sgain:%d\n",\
						pInfo->pre_cen_bypass,cur_cen_bypass,hdr_effect,dynamic_cm_ui,Hoffset,Sgain);
				}
				PE_CC_PE1_O26_QWr01(pe1_cen_ctrl_00,	reg_cen_bypass,	GET_BITS(cur_cen_bypass,0,1));
				#if 1	/* O26F22_APB */
				do {
					if (!gPE_CHPI_DDR_O26)	break;
					PE_CHPI_APB0_O26F22_QWr(cen1.pe1_cen_ctrl_00.reg_cen_bypass,GET_BITS(cur_cen_bypass,0,1));
					PE_INF_O26_IncChipInfoApbCount(PE_INF_O26_CHPI_APB_CEN1);
				} while(0);
				#endif
				pInfo->pre_cen_bypass = cur_cen_bypass;
			}
		}
		else
		{
			PE_CMG_HW_O26_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	#endif
	return ret;
}

