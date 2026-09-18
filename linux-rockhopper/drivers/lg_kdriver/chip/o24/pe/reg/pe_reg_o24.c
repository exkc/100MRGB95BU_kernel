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

/** @file pe_reg_o24.c
 *
 *  driver for picture enhance register read, write functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
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

#include "pe_hw_o24.h"
#include "pe_reg_o24.h"
#include "pe_inf_o24.h"
#include "pe_hdr_ddr_o24.h"
#include "pe_hdr_hw_o24.h"

#ifdef INCLUDE_KDRV_BE
#include "ovi_hal.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_REG_O24_CHECK_CODE(_checker,_action,fmt,args...)		\
	if (_checker)\
	{\
		PE_PRINT_ERROR(fmt,##args);\
		_action;\
	}

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
#ifndef PE_HW_O24_BRINGUP
PE_CC_PE1_REG_TYPE_O24_T   gPE_CC_PE1_O24;
PE_CC2_PE1_REG_TYPE_O24_T  gPE_CC2_PE1_O24;
PE_CVI_REG_TYPE_O24_T      gPE_CVI_A_O24;
PE_CVI_REG_TYPE_O24_T      gPE_CVI_B_O24;
PE_CVI_REG_TYPE_O24_T      gPE_CVI_C_O24;
PE_CVI_REG_TYPE_O24_T      gPE_CVI_D_O24;
PE_AMG_BODY_REG_TYPE_O24_T	gPE_AMG_BODY_O24;
PE_OSD_ORD_REG_TYPE_O24_T   gPE_OSD_ORD_O24;
PE_AMG_HEAD_REG_TYPE_O24_T	gPE_AMG_HEAD_O24;
PE_AMG_MTB_REG_TYPE_O24_T	gPE_AMG_MTB_O24;
PE_AMG_GRM_REG_TYPE_O24_T	gPE_AMG_GRM_O24;
PE_OSC0_Y_REG_TYPE_O24_T    gPE_OSC0_Y_O24;
PE_OSC1_Y_REG_TYPE_O24_T    gPE_OSC1_Y_O24;
PE_OSC0_C_REG_TYPE_O24_T    gPE_OSC0_C_O24;
PE_OSC1_C_REG_TYPE_O24_T    gPE_OSC1_C_O24;
PE_OSC2_YC_REG_TYPE_O24_T   gPE_OSC2_YC_O24;
PE_OSC3_YC_REG_TYPE_O24_T   gPE_OSC3_YC_O24;
PE_ND_ND0_REG_TYPE_O24_T   gPE_ND_ND0_O24;
PE_ND_DNR0_REG_TYPE_O24_T  gPE_ND_DNR0_O24;
PE_ND_DNR1_REG_TYPE_O24_T  gPE_ND_DNR1_O24;
PE_ND_ND0_REG_TYPE_O24_T   gPE_ND_ND1_O24;
PE_ND0_VERI_REG_TYPE_O24_T gPE_ND0_VERI_O24;
PE_ND1_VERI_REG_TYPE_O24_T gPE_ND1_VERI_O24;
PE_VSD_SHP_REG_TYPE_O24_T      gPE_VSD_SHP_O24;
PE_VSD_OBC_BODY_REG_TYPE_O24_T	gPE_VSD_OBC_BODY_O24;
PE_VSD_OBC_HEAD_REG_TYPE_O24_T	gPE_VSD_OBC_HEAD_O24;
//PE_VSD_OBC_M_SC_REG_TYPE_O24_T	gPE_VSD_OBC_M_SC_O24;
PE_VSD_OBE_REG_TYPE_O24_T		gPE_VSD_OBE_O24;
PE_VSD_DTM_REG_TYPE_O24_T	gPE_VSD_DTM_O24;
PE_SR_2K_SHP_REG_TYPE_O24_T  gPE_SR_2K_SHP0_O24;
PE_SR_2K_SHP_REG_TYPE_O24_T  gPE_SR_2K_SHP1_O24;
PE_SR_2K_SHC_REG_TYPE_O24_T  gPE_SR_2K_SHC_O24;
PE_SR_MERG_REG_TYPE_O24_T    gPE_SR_MERG_O24;
PE_SR_VERI_REG_TYPE_O24_T    gPE_SR_VERI_O24;
PE_GAV_SHP_REG_TYPE_O24_T    gPE_GAV_SHP_O24;
PE_VCP_DISP_REG_TYPE_O24_T 	gPE_VCP_DISP_O24;
PE_VSD0_VERI_REG_TYPE_O24_T gPE_VSD0_VERI_O24;
PE_OLB_REG_TYPE_O24_T 	    gPE_OLB_O24;
PE_DDR_DB_REG_TYPE_O24_T     gPE_DDR_DB_O24;
PE_DDR_DB_REG_TYPE_O24F22_T  gPE_DDR_DB_O24F22;
PE_DCM_DDR_DB_REG_TYPE_O24F22_T  gPE_DCM_DDR_DB_O24F22;
PE_DBC_DDR_DB_REG_TYPE_O24F22_T  gPE_DBC_DDR_DB_O24F22;

PE_TOP_IMX_REG_TYPE_O24_T gPE_TOP_IMX_O24;
PE_CCO_DECON_REG_TYPE_O24_T gPE_CCO_DCNT_O24;

PE_MCU_REG_TYPE_O24_T   gPE_MCU_O24;
PE_CCO_VERI_REG_TYPE_O24_T   gPE_CCO_VERI_O24;
PE_CHPI_REG_TYPE_O24F22_T gPE_CHPI_APB0_O24F22;
PE_CHPI_REG_TYPE_O24F22_T gPE_CHPI_APB1_O24F22;//causion : shdw not used(null)
PE_CHPI_TBL0_TYPE_O24F22_T gPE_CHPI_TBL0_O24F22;
PE_CHPI_TBL0_TYPE_O24F22_T gPE_CHPI_TBL1_O24F22;//causion : shdw not used(null)
volatile UINT32 *gPE_CHPI_DDR_O24 = NULL;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_REG_O24_HW_OPT_T _g_pe_reg_o24_disp_opt;

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef INCLUDE_KDRV_BE
static int PE_REG_O24_GetHwOpt(UINT32 *opt)
{
	PE_REG_O24_HW_OPT_T panel_mode;
	LX_OVI_HW_DISPLAY_INFO_T ovi_opt;
	int ret = RET_OK;

	panel_mode.u32Data = 0;

	ret = OVI_HAL_GetHWDisplayOption(&ovi_opt);
	if (ret == RET_OK)
	{
		if ((ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ)
			|| (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ_FIXED))
		{
			panel_mode.panel_frame_rate = 1;//see LX_DE_IPC_PANEL_FRAME_RATE_60Hz;
		}

		if (ovi_opt.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
		{
			panel_mode.panel_type = 1;//see LX_DE_IPC_PANEL_TYPE_OLED;
		}
		else if (ovi_opt.panelBacklight == LX_OVI_PANEL_BACKLIGHT_NONE)
		{
			panel_mode.panel_type = 2;//see LX_DE_IPC_PANEL_TYPE_BOX;
		}

		if (ovi_opt.isVx15Byte)
		{
			panel_mode.vx1_byte  = 1;//see LX_DE_IPC_PANEL_VX1_5BYTE;
		}

		if (ovi_opt.frcChipType > LX_OVI_FRC_CHIP_INTERNAL)
		{
			panel_mode.external_chip  = 1;//see LX_DE_IPC_EXTERNAL_CHIP_USE;
		}

		if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_7680X4320)
		{
			panel_mode.panel_resolution = 5;//LX_DE_IPC_PANEL_RESOLUTION_7680X4320;
		}
		else if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
		{
			panel_mode.panel_resolution = 1;//see LX_DE_IPC_PANEL_RESOLUTION_1920x1080;
		}
		else if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1366X768)
		{
			panel_mode.panel_resolution = 2;//see LX_DE_IPC_PANEL_RESOLUTION_1366x768;
		}
		else if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1280X720)
		{
			panel_mode.panel_resolution = 3;//see LX_DE_IPC_PANEL_RESOLUTION_1280x720;
		}
	}

	*opt = panel_mode.u32Data;

	PE_PRINT_NOTI("[Opt]fr:%d,pt:%d,vx1:%d,ext%d,pr:%d\n",panel_mode.panel_frame_rate,\
		panel_mode.panel_type,panel_mode.vx1_byte,panel_mode.external_chip,panel_mode.panel_resolution);
	PE_INF_HW_O24_BACKUP_TRACE("[Opt]fr:%d,pt:%d,vx1:%d,ext%d,pr:%d",panel_mode.panel_frame_rate,\
		panel_mode.panel_type,panel_mode.vx1_byte,panel_mode.external_chip,panel_mode.panel_resolution);

	return RET_OK;
}
#endif
/**
 * init phy to virtual addr
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_O24_InitPhyToVirt(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	/* shdw */
	
	gPE_CC_PE1_O24.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CC_PE1_REG_O24_T));
	gPE_CC2_PE1_O24.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_CC2_PE1_REG_O24_T));

	gPE_CVI_A_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O24_T));
	gPE_CVI_B_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O24_T));
	gPE_CVI_C_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O24_T));
	gPE_CVI_D_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O24_T));

	gPE_CCO_DCNT_O24.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_CCO_DECON_REG_O24_T));

	gPE_OSC0_Y_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_OSC0_Y_REG_O24_T));
	gPE_OSC1_Y_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_OSC1_Y_REG_O24_T));
	gPE_OSC0_C_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_OSC0_C_REG_O24_T));
	gPE_OSC1_C_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_OSC1_C_REG_O24_T));
	gPE_OSC2_YC_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_OSC2_YC_REG_O24_T));
	gPE_OSC3_YC_O24.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_OSC3_YC_REG_O24_T));

	gPE_ND_ND0_O24.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_REG_O24_T));
	gPE_ND_ND1_O24.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND1_REG_O24_T));
	gPE_ND_DNR0_O24.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR0_REG_O24_T));
	gPE_ND_DNR1_O24.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR1_REG_O24_T));
	gPE_ND0_VERI_O24.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_ND0_VERI_REG_O24_T));
	gPE_ND1_VERI_O24.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_ND1_VERI_REG_O24_T));
	gPE_TOP_IMX_O24.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_TOP_IMX_REG_O24_T));

	gPE_VSD_SHP_O24.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_VSD_SHP_REG_O24_T));
	gPE_VSD_OBC_BODY_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBC_BODY_REG_O24_T));
	gPE_VSD_OBC_HEAD_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBC_HEAD_REG_O24_T));
	//gPE_VSD_OBC_M_SC_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBC_M_SC_REG_O24_T));
	gPE_AMG_BODY_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_AMG_BODY_REG_O24_T));
	gPE_AMG_HEAD_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_AMG_HEAD_REG_O24_T));
	gPE_AMG_MTB_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_AMG_MTB_REG_O24_T));
	gPE_AMG_GRM_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_AMG_GRM_REG_O24_T));
	gPE_VSD_OBE_O24.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBE_REG_O24_T));
	gPE_VSD_DTM_O24.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_DTM_REG_O24_T));
	gPE_OSD_ORD_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OSD_ORD_REG_O24_T));

	gPE_VCP_DISP_O24.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DISP_REG_O24_T));
	gPE_VSD0_VERI_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD0_VERI_REG_O24_T));
	gPE_OLB_O24.shdw.addr 	    = (UINT32 *)OS_KMalloc(sizeof(PE_OLB_REG_O24_T));

	gPE_SR_2K_SHP0_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHP_REG_O24_T));
	gPE_SR_2K_SHP1_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHP_REG_O24_T));
	gPE_SR_2K_SHC_O24.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHC_REG_O24_T));
	gPE_SR_MERG_O24.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_MERG_REG_O24_T));
	gPE_SR_VERI_O24.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_VERI_REG_O24_T));
	gPE_GAV_SHP_O24.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_GAV_SHP_REG_O24_T));

	gPE_DDR_DB_O24.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O24_T));
	gPE_DDR_DB_O24F22.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O24F22_T));
	gPE_DCM_DDR_DB_O24F22.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DCM_DDR_DB_SHDW_REG_O24F22_T));
	gPE_DBC_DDR_DB_O24F22.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DBC_DDR_DB_SHDW_REG_O24F22_T));
	#if 0	//TODO: 
	gPE_LGSR_DDR_DB_O24.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O24_T));
	gPE_LGSR_DDR_DB_O24F22.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O24F22_T));
	#endif
	gPE_MCU_O24.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_MCU_REG_O24_T));
	gPE_CCO_VERI_O24.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CCO_VERI_REG_O24_T));

	gPE_CHPI_APB0_O24F22.shdw.addr	= (UINT32 *)OS_KMalloc(sizeof(PE_CHPI_REG_O24F22_T));
	gPE_CHPI_TBL0_O24F22.shdw.addr	= (UINT32 *)OS_KMalloc(sizeof(PE_CHPI_TBL0_O24F22_T));

	/* phys */

	gPE_CC_PE1_O24.phys.addr   	= (volatile UINT32 *)ioremap(PE_O24_P1_CC_BASE, sizeof(PE_CC_PE1_REG_O24_T));
	gPE_CC2_PE1_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_P1_CC2_BASE, sizeof(PE_CC2_PE1_REG_O24_T));

	gPE_CVI_A_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_CVI_A_BASE,    sizeof(PE_CVI_REG_O24_T));
	gPE_CVI_B_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_CVI_B_BASE,    sizeof(PE_CVI_REG_O24_T));
	gPE_CVI_C_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_CVI_C_BASE,    sizeof(PE_CVI_REG_O24_T));
	gPE_CVI_D_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_CVI_D_BASE,    sizeof(PE_CVI_REG_O24_T));

	gPE_CCO_DCNT_O24.phys.addr  = (volatile UINT32 *)ioremap(PE_O24_CCO_DCNT_BASE,   sizeof(PE_CCO_DECON_REG_O24_T));

	gPE_OSC0_Y_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_OSC0_Y_BASE,    sizeof(PE_OSC0_Y_REG_O24_T));
	gPE_OSC1_Y_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_OSC1_Y_BASE,    sizeof(PE_OSC1_Y_REG_O24_T));
	gPE_OSC0_C_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_OSC0_C_BASE,    sizeof(PE_OSC0_C_REG_O24_T));
	gPE_OSC1_C_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_OSC1_C_BASE,    sizeof(PE_OSC1_C_REG_O24_T));
	gPE_OSC2_YC_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_OSC2_YC_BASE,    sizeof(PE_OSC2_YC_REG_O24_T));
	gPE_OSC3_YC_O24.phys.addr    	= (volatile UINT32 *)ioremap(PE_O24_OSC3_YC_BASE,    sizeof(PE_OSC3_YC_REG_O24_T));

	gPE_ND_ND0_O24.phys.addr   	= (volatile UINT32 *)ioremap(PE_O24_ND0_BASE,      sizeof(PE_ND_ND0_REG_O24_T));
	gPE_ND_ND1_O24.phys.addr   	= (volatile UINT32 *)ioremap(PE_O24_ND1_BASE,      sizeof(PE_ND_ND1_REG_O24_T));
	gPE_ND_DNR0_O24.phys.addr  	= (volatile UINT32 *)ioremap(PE_O24_DNR0_BASE,     sizeof(PE_ND_DNR0_REG_O24_T));
	gPE_ND_DNR1_O24.phys.addr  	= (volatile UINT32 *)ioremap(PE_O24_DNR1_BASE,     sizeof(PE_ND_DNR1_REG_O24_T));
	gPE_ND0_VERI_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_ND0_VERI_BASE,  sizeof(PE_ND0_VERI_REG_O24_T));
	gPE_ND1_VERI_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_ND1_VERI_BASE,  sizeof(PE_ND1_VERI_REG_O24_T));

	gPE_TOP_IMX_O24.phys.addr  	= (volatile UINT32 *)ioremap(PE_O24_IMX_BASE,      sizeof(PE_TOP_IMX_REG_O24_T));
	gPE_VSD_SHP_O24.phys.addr     	= (volatile UINT32 *)ioremap(PE_O24_P1_VSD_SHP_L_BASE, sizeof(PE_VSD_SHP_REG_O24_T));
	gPE_VSD_OBC_BODY_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_P1_VSD_OBC_BODY_BASE, sizeof(PE_VSD_OBC_BODY_REG_O24_T));
	gPE_VSD_OBC_HEAD_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_P1_VSD_OBC_HEAD_BASE, sizeof(PE_VSD_OBC_HEAD_REG_O24_T));
	//gPE_VSD_OBC_M_SC_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_P1_VSD_OBC_M_SC_BASE, sizeof(PE_VSD_OBC_M_SC_REG_O24_T));
	gPE_AMG_BODY_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_AMG_BODY_BASE, sizeof(PE_AMG_BODY_REG_O24_T));
	gPE_AMG_HEAD_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_AMG_HEAD_BASE, sizeof(PE_AMG_HEAD_REG_O24_T));
	gPE_AMG_MTB_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_AMG_MTB_BASE, sizeof(PE_AMG_MTB_REG_O24_T));
	gPE_AMG_GRM_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_AMG_GRM_BASE, sizeof(PE_AMG_GRM_REG_O24_T));
	gPE_VSD_OBE_O24.phys.addr     = (volatile UINT32 *)ioremap(PE_O24_P1_VSD_OBE_BASE, sizeof(PE_VSD_OBE_REG_O24_T));
	gPE_OSD_ORD_O24.phys.addr   = (volatile UINT32 *)ioremap(PE_O24_OSD_ORD_BASE, sizeof(PE_OSD_ORD_REG_O24_T));
	gPE_VSD_DTM_O24.phys.addr     = (volatile UINT32 *)ioremap(PE_O24_P1_VSD_DTM_BASE, sizeof(PE_VSD_DTM_REG_O24_T));
	gPE_VCP_DISP_O24.phys.addr 	= (volatile UINT32 *)ioremap(PE_O24_VCP_DISP_BASE, sizeof(PE_VCP_DISP_REG_O24_T));
	gPE_OLB_O24.phys.addr 	    = (volatile UINT32 *)ioremap(PE_O24_OLB_BASE, sizeof(PE_OLB_REG_O24_T));
	gPE_VSD0_VERI_O24.phys.addr = (volatile UINT32 *)ioremap(PE_O24_VSD0_VERI_BASE, sizeof(PE_VSD0_VERI_REG_O24_T));
	gPE_SR_2K_SHP0_O24 .phys.addr   	= (volatile UINT32 *)ioremap(PE_O24_SR_2K_SHP0_BASE,   sizeof(PE_SR_2K_SHP_REG_O24_T));
	gPE_SR_2K_SHP1_O24 .phys.addr   	= (volatile UINT32 *)ioremap(PE_O24_SR_2K_SHP1_BASE,   sizeof(PE_SR_2K_SHP_REG_O24_T));
	gPE_SR_2K_SHC_O24 .phys.addr   	= (volatile UINT32 *)ioremap(PE_O24_SR_2K_SHC_BASE,   sizeof(PE_SR_2K_SHC_REG_O24_T));
	gPE_SR_MERG_O24.phys.addr   		= (volatile UINT32 *)ioremap(PE_O24_SR_MERG_BASE,   sizeof(PE_SR_MERG_REG_O24_T));
	gPE_SR_VERI_O24.phys.addr   		= (volatile UINT32 *)ioremap(PE_O24_SR_VERI_BASE,   sizeof(PE_SR_VERI_REG_O24_T));
	gPE_GAV_SHP_O24.phys.addr   		= (volatile UINT32 *)ioremap(PE_O24_GAV_SHP_BASE,   sizeof(PE_GAV_SHP_REG_O24_T));

	gPE_DDR_DB_O24.phys.addr    = (volatile UINT32 *)vmap_phys(PE_O24_DDR_DB0_BASE,sizeof(PE_DDR_DB_PHYS_REG_O24_T)+PAGE_SIZE);
	gPE_DDR_DB_O24F22.phys.addr    = (volatile UINT32 *)vmap_phys(PE_O24F22_DDR_BASE,sizeof(PE_DDR_DB_PHYS_REG_O24F22_T)+PAGE_SIZE);
	gPE_DCM_DDR_DB_O24F22.phys.addr    = (volatile UINT32 *)vmap_phys(PE_O24F22_DCM_DDR_BASE,sizeof(PE_DCM_DDR_DB_PHYS_REG_O24F22_T)+PAGE_SIZE);
	gPE_DBC_DDR_DB_O24F22.phys.addr    = (volatile UINT32 *)vmap_phys(PE_O24F22_DBC_DDR_BASE,sizeof(PE_DBC_DDR_DB_PHYS_REG_O24F22_T)+PAGE_SIZE);
	#if 0	//TODO: 
	gPE_LGSR_DDR_DB_O24.phys.addr    = (volatile UINT32 *)vmap_phys(PE_LGSR_DDR_O24_BASE_ADDR,sizeof(PE_LGSR_DDR_DB_PHYS_REG_O24_T)+PAGE_SIZE);
	gPE_LGSR_DDR_DB_O24F22.phys.addr    = (volatile UINT32 *)vmap_phys(PE_LGSR_DDR_O24F22_BASE_ADDR,sizeof(PE_LGSR_DDR_DB_PHYS_REG_O24F22_T)+PAGE_SIZE);
	#endif
	gPE_MCU_O24.phys.addr   	= (volatile UINT32 *)ioremap(PE_O24_MCU_BASE,      sizeof(PE_MCU_REG_O24_T));
	gPE_CCO_VERI_O24.phys.addr   		= (volatile UINT32 *)ioremap(PE_O24_CCO_VERI_BASE,   sizeof(PE_CCO_VERI_REG_O24_T));

	_g_pe_reg_o24_disp_opt.u32Data = 0;
	#ifdef INCLUDE_KDRV_BE
	ret = PE_REG_O24_GetHwOpt(&(_g_pe_reg_o24_disp_opt.u32Data));
	#endif

	do {
		UINT32 chpi_base = 0, chpi_size = 0;
		UINT32 apb_s[4],apb_e[4],st_size[3],max_size[3];

		if (_g_pe_reg_o24_disp_opt.external_chip == 0)
		{
			PE_INF_HW_O24_BACKUP_CHPI1("[CHI]skip (external_chip:0)");
			break;
		}

		#if 1
		#ifdef INCLUDE_KDRV_DE
		chpi_base = g_chipinfo.base;
		chpi_size = g_chipinfo.size;
		#endif
		if (chpi_base==0)	break;
		if (chpi_size==0)	break;
		gPE_CHPI_DDR_O24 = (volatile UINT32 *)vmap_phys(chpi_base,chpi_size);
		gPE_CHPI_APB0_O24F22.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR_O24 + (PE_CHPI_APB0_O24F22_S_OFST0>>2));//buf[1]
		gPE_CHPI_APB1_O24F22.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR_O24 + (PE_CHPI_APB1_O24F22_S_OFST0>>2));//buf[4]
		gPE_CHPI_TBL0_O24F22.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR_O24 + (PE_CHPI_TBL0_O24F22_S_OFST0>>2));//buf[2]
		gPE_CHPI_TBL1_O24F22.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR_O24 + (PE_CHPI_TBL1_O24F22_S_OFST0>>2));//buf[5]
		PE_INF_HW_O24_BACKUP_CHPI0("[CHI]0x%08x,0x%08x,0x%px",chpi_base,chpi_size,gPE_CHPI_DDR_O24);
		PE_PRINT_NOTI("[CHI]apb:0x%px,0x%px\n",gPE_CHPI_APB0_O24F22.phys.addr,gPE_CHPI_APB1_O24F22.phys.addr);
		PE_PRINT_NOTI("[CHI]tbl:0x%px,0x%px\n",gPE_CHPI_TBL0_O24F22.phys.addr,gPE_CHPI_TBL1_O24F22.phys.addr);
		#endif

		/* info apb */
		apb_s[0] = (chpi_base+PE_CHPI_APB0_O24F22_S_OFST0);
		apb_e[0] = (chpi_base+PE_CHPI_APB0_O24F22_E_OFST0);
		apb_s[1] = (chpi_base+PE_CHPI_APB0_O24F22_S_OFST1);
		apb_e[1] = (chpi_base+PE_CHPI_APB0_O24F22_E_OFST1);
		apb_s[2] = (chpi_base+PE_CHPI_APB1_O24F22_S_OFST0);
		apb_e[2] = (chpi_base+PE_CHPI_APB1_O24F22_E_OFST0);
		apb_s[3] = (chpi_base+PE_CHPI_APB1_O24F22_S_OFST1);
		apb_e[3] = (chpi_base+PE_CHPI_APB1_O24F22_E_OFST1);
		st_size[0] = sizeof(PE_CHPI_REG0_O24F22_T);
		st_size[1] = sizeof(PE_CHPI_REG1_O24F22_T);
		st_size[2] = sizeof(PE_CHPI_REG_O24F22_T);
		max_size[0] = PE_CHPI_APB_O24F22_SIZE0;
		max_size[1] = PE_CHPI_APB_O24F22_SIZE1;
		max_size[2] = PE_CHPI_APB_O24F22_TOTAL;
		PE_INF_HW_O24_BACKUP_CHPI0("[CHI]apb:0x%08x,0x%08x|0x%08x,0x%08x|0x%08x,0x%08x|0x%08x,0x%08x",apb_s[0],apb_e[0],apb_s[1],apb_e[1],apb_s[2],apb_e[2],apb_s[3],apb_e[3]);
		PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[0],max_size[0],max_size[0]-st_size[0],(max_size[0]-st_size[0])>>2);
		PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[1],max_size[1],max_size[1]-st_size[1],(max_size[1]-st_size[1])>>2);
		PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[2],max_size[2],max_size[2]-st_size[2],(max_size[2]-st_size[2])>>2);
		/* info tbl */
		apb_s[0] = (chpi_base+PE_CHPI_TBL0_O24F22_S_OFST0);
		apb_e[0] = (chpi_base+PE_CHPI_TBL0_O24F22_E_OFST0);
		apb_s[1] = (chpi_base+PE_CHPI_TBL1_O24F22_S_OFST0);
		apb_e[1] = (chpi_base+PE_CHPI_TBL1_O24F22_E_OFST0);
		st_size[0] = sizeof(PE_CHPI_TBL0_O24F22_T);
		max_size[0] = PE_CHPI_TBL_O24F22_TOTAL;
		PE_INF_HW_O24_BACKUP_CHPI1("[CHI]tbl:0x%08x,0x%08x|0x%08x,0x%08x",apb_s[0],apb_e[0],apb_s[1],apb_e[1]);
		PE_PRINT_NOTI("[CHI]tbl:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[0],max_size[0],max_size[0]-st_size[0],(max_size[0]-st_size[0])>>2);

	} while(0);

	PE_PRINT_NOTI("[PE]vmap base:0x%08x,size:0x%08x+0x%08x\n",\
		PE_O24_DDR_DB0_BASE,(UINT32)sizeof(PE_DDR_DB_PHYS_REG_O24_T),(UINT32)PAGE_SIZE);
	PE_PRINT_NOTI("[PE]vmap base:0x%08x,size:0x%08x+0x%08x\n",\
		PE_LGSR_DDR_O24_BASE_ADDR,(UINT32)sizeof(PE_LGSR_DDR_DB_PHYS_REG_O24_T),(UINT32)PAGE_SIZE);
	#endif /*PE_HW_O24_BRINGUP*/

	PE_HDR_HW_O24_InitPhyToVirt();

	return ret;
}

/**
 * free phy to virtual addr
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_O24_FreePhyToVirt(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	/* shdw */
	
	if (gPE_CC_PE1_O24.shdw.addr  ) OS_Free((void *)gPE_CC_PE1_O24.shdw.addr  );
	if (gPE_CC2_PE1_O24.shdw.addr ) OS_Free((void *)gPE_CC2_PE1_O24.shdw.addr );

	if (gPE_CVI_A_O24.shdw.addr   ) OS_Free((void *)gPE_CVI_A_O24.shdw.addr   );
	if (gPE_CVI_B_O24.shdw.addr   ) OS_Free((void *)gPE_CVI_B_O24.shdw.addr   );
	if (gPE_CVI_C_O24.shdw.addr   ) OS_Free((void *)gPE_CVI_C_O24.shdw.addr   );
	if (gPE_CVI_D_O24.shdw.addr   ) OS_Free((void *)gPE_CVI_D_O24.shdw.addr   );
	if (gPE_CCO_DCNT_O24.shdw.addr) OS_Free((void *)gPE_CCO_DCNT_O24.shdw.addr);
	if (gPE_OSC0_Y_O24.shdw.addr   ) OS_Free((void *)gPE_OSC0_Y_O24.shdw.addr );
	if (gPE_OSC1_Y_O24.shdw.addr   ) OS_Free((void *)gPE_OSC1_Y_O24.shdw.addr );
	if (gPE_OSC0_C_O24.shdw.addr   ) OS_Free((void *)gPE_OSC0_C_O24.shdw.addr );
	if (gPE_OSC1_C_O24.shdw.addr   ) OS_Free((void *)gPE_OSC1_C_O24.shdw.addr );
	if (gPE_OSC2_YC_O24.shdw.addr   ) OS_Free((void *)gPE_OSC2_YC_O24.shdw.addr );
	if (gPE_OSC3_YC_O24.shdw.addr   ) OS_Free((void *)gPE_OSC3_YC_O24.shdw.addr );
	if (gPE_ND_ND0_O24.shdw.addr  ) OS_Free((void *)gPE_ND_ND0_O24.shdw.addr  );
	if (gPE_ND_ND1_O24.shdw.addr  ) OS_Free((void *)gPE_ND_ND1_O24.shdw.addr  );
	if (gPE_ND_DNR0_O24.shdw.addr ) OS_Free((void *)gPE_ND_DNR0_O24.shdw.addr );
	if (gPE_ND_DNR1_O24.shdw.addr ) OS_Free((void *)gPE_ND_DNR1_O24.shdw.addr );
	if (gPE_ND0_VERI_O24.shdw.addr) OS_Free((void *)gPE_ND0_VERI_O24.shdw.addr  );
	if (gPE_ND1_VERI_O24.shdw.addr) OS_Free((void *)gPE_ND1_VERI_O24.shdw.addr  );
	if (gPE_TOP_IMX_O24.shdw.addr ) OS_Free((void *)gPE_TOP_IMX_O24.shdw.addr );
	if (gPE_VSD_SHP_O24.shdw.addr     ) OS_Free((void *)gPE_VSD_SHP_O24.shdw.addr     );
	if (gPE_VSD_OBC_BODY_O24.shdw.addr  ) OS_Free((void *)gPE_VSD_OBC_BODY_O24.shdw.addr  );
	if (gPE_VSD_OBC_HEAD_O24.shdw.addr  ) OS_Free((void *)gPE_VSD_OBC_HEAD_O24.shdw.addr  );
	//if (gPE_VSD_OBC_M_SC_O24.shdw.addr  ) OS_Free((void *)gPE_VSD_OBC_M_SC_O24.shdw.addr  );
	if (gPE_AMG_BODY_O24.shdw.addr  ) OS_Free((void *)gPE_AMG_BODY_O24.shdw.addr  );
	if (gPE_AMG_HEAD_O24.shdw.addr  ) OS_Free((void *)gPE_AMG_HEAD_O24.shdw.addr  );
	if (gPE_AMG_MTB_O24.shdw.addr  ) OS_Free((void *)gPE_AMG_MTB_O24.shdw.addr  );
	if (gPE_AMG_GRM_O24.shdw.addr  ) OS_Free((void *)gPE_AMG_GRM_O24.shdw.addr  );
	if (gPE_VSD_OBE_O24.shdw.addr    ) OS_Free((void *)gPE_VSD_OBE_O24.shdw.addr    );
	if (gPE_OSD_ORD_O24.shdw.addr  ) OS_Free((void *)gPE_OSD_ORD_O24.shdw.addr  );
	if (gPE_VSD_DTM_O24.shdw.addr    ) OS_Free((void *)gPE_VSD_DTM_O24.shdw.addr    );

	if (gPE_VCP_DISP_O24.shdw.addr)  OS_Free((void *)gPE_VCP_DISP_O24.shdw.addr);
	if (gPE_VSD0_VERI_O24.shdw.addr) OS_Free((void *)gPE_VSD0_VERI_O24.shdw.addr);
	if (gPE_OLB_O24.shdw.addr)       OS_Free((void *)gPE_OLB_O24.shdw.addr);

	if (gPE_SR_2K_SHP0_O24.shdw.addr     ) OS_Free((void *)gPE_SR_2K_SHP0_O24.shdw.addr  );
	if (gPE_SR_2K_SHP1_O24.shdw.addr     ) OS_Free((void *)gPE_SR_2K_SHP1_O24.shdw.addr  );
	if (gPE_SR_2K_SHC_O24.shdw.addr     ) OS_Free((void *)gPE_SR_2K_SHC_O24.shdw.addr  );
	if (gPE_SR_MERG_O24.shdw.addr       ) OS_Free((void *)gPE_SR_MERG_O24.shdw.addr  );
	if (gPE_SR_VERI_O24.shdw.addr       ) OS_Free((void *)gPE_SR_VERI_O24.shdw.addr  );
	if (gPE_GAV_SHP_O24.shdw.addr       ) OS_Free((void *)gPE_GAV_SHP_O24.shdw.addr  );
	if (gPE_DDR_DB_O24.shdw.addr        ) OS_Free((void *)gPE_DDR_DB_O24.shdw.addr    );
	if (gPE_DDR_DB_O24F22.shdw.addr     ) OS_Free((void *)gPE_DDR_DB_O24F22.shdw.addr    );
	if (gPE_DCM_DDR_DB_O24F22.shdw.addr ) OS_Free((void *)gPE_DCM_DDR_DB_O24F22.shdw.addr    );
	if (gPE_DBC_DDR_DB_O24F22.shdw.addr ) OS_Free((void *)gPE_DBC_DDR_DB_O24F22.shdw.addr    );
	#if 0	//TODO:
	//if (gPE_HDMI_A_O24.shdw.addr  ) OS_Free((void *)gPE_HDMI_A_O24.shdw.addr  );
	//if (gPE_HDMI_B_O24.shdw.addr  ) OS_Free((void *)gPE_HDMI_B_O24.shdw.addr  );
	//if (gPE_HDMI_C_O24.shdw.addr  ) OS_Free((void *)gPE_HDMI_C_O24.shdw.addr  );
	//if (gPE_HDMI_D_O24.shdw.addr  ) OS_Free((void *)gPE_HDMI_D_O24.shdw.addr  );	
	if (gPE_LGSR_DDR_DB_O24.shdw.addr    ) OS_Free((void *)gPE_LGSR_DDR_DB_O24.shdw.addr    );
	if (gPE_LGSR_DDR_DB_O24F22.shdw.addr    ) OS_Free((void *)gPE_LGSR_DDR_DB_O24F22.shdw.addr    );

	#endif
	if (gPE_MCU_O24.shdw.addr) OS_Free((void *)gPE_MCU_O24.shdw.addr);
	if (gPE_CCO_VERI_O24.shdw.addr) OS_Free((void *)gPE_CCO_VERI_O24.shdw.addr);

	if (gPE_CHPI_APB0_O24F22.shdw.addr) OS_Free((void *)gPE_CHPI_APB0_O24F22.shdw.addr);
	if (gPE_CHPI_TBL0_O24F22.shdw.addr) OS_Free((void *)gPE_CHPI_TBL0_O24F22.shdw.addr);

	/* phys */

	if (gPE_CC_PE1_O24.phys.addr  ) iounmap((void *)gPE_CC_PE1_O24.phys.addr  );
	if (gPE_CC2_PE1_O24.phys.addr  ) iounmap((void *)gPE_CC2_PE1_O24.phys.addr  );

	if (gPE_CVI_A_O24.phys.addr   ) iounmap((void *)gPE_CVI_A_O24.phys.addr   );
	if (gPE_CVI_B_O24.phys.addr   ) iounmap((void *)gPE_CVI_B_O24.phys.addr   );
	if (gPE_CVI_C_O24.phys.addr   ) iounmap((void *)gPE_CVI_C_O24.phys.addr   );
	if (gPE_CVI_D_O24.phys.addr   ) iounmap((void *)gPE_CVI_D_O24.phys.addr   );

	if (gPE_CCO_DCNT_O24.phys.addr  ) iounmap((void *)gPE_CCO_DCNT_O24.phys.addr  );

	if (gPE_OSC0_Y_O24.phys.addr   ) iounmap((void *)gPE_OSC0_Y_O24.phys.addr );
	if (gPE_OSC1_Y_O24.phys.addr   ) iounmap((void *)gPE_OSC1_Y_O24.phys.addr );
	if (gPE_OSC0_C_O24.phys.addr   ) iounmap((void *)gPE_OSC0_C_O24.phys.addr );
	if (gPE_OSC1_C_O24.phys.addr   ) iounmap((void *)gPE_OSC1_C_O24.phys.addr );
	if (gPE_OSC2_YC_O24.phys.addr  ) iounmap((void *)gPE_OSC2_YC_O24.phys.addr );
	if (gPE_OSC3_YC_O24.phys.addr  ) iounmap((void *)gPE_OSC3_YC_O24.phys.addr );

	if (gPE_ND_ND0_O24.phys.addr  ) iounmap((void *)gPE_ND_ND0_O24.phys.addr  );
	if (gPE_ND_ND1_O24.phys.addr  ) iounmap((void *)gPE_ND_ND1_O24.phys.addr  );
	if (gPE_ND_DNR0_O24.phys.addr ) iounmap((void *)gPE_ND_DNR0_O24.phys.addr );
	if (gPE_ND_DNR1_O24.phys.addr ) iounmap((void *)gPE_ND_DNR1_O24.phys.addr );
	if (gPE_ND0_VERI_O24.phys.addr) iounmap((void *)gPE_ND0_VERI_O24.phys.addr  );
	if (gPE_ND1_VERI_O24.phys.addr) iounmap((void *)gPE_ND1_VERI_O24.phys.addr  );

	if (gPE_TOP_IMX_O24.phys.addr ) iounmap((void *)gPE_TOP_IMX_O24.phys.addr );

	if (gPE_VSD_SHP_O24.phys.addr     ) iounmap((void *)gPE_VSD_SHP_O24.phys.addr     );
	if (gPE_VSD_OBC_BODY_O24.phys.addr ) iounmap((void *)gPE_VSD_OBC_BODY_O24.phys.addr );
	if (gPE_VSD_OBC_HEAD_O24.phys.addr ) iounmap((void *)gPE_VSD_OBC_HEAD_O24.phys.addr );
	//if (gPE_VSD_OBC_M_SC_O24.phys.addr ) iounmap((void *)gPE_VSD_OBC_M_SC_O24.phys.addr );
	if (gPE_AMG_BODY_O24.phys.addr ) iounmap((void *)gPE_AMG_BODY_O24.phys.addr );
	if (gPE_AMG_HEAD_O24.phys.addr ) iounmap((void *)gPE_AMG_HEAD_O24.phys.addr );
	if (gPE_AMG_MTB_O24.phys.addr ) iounmap((void *)gPE_AMG_MTB_O24.phys.addr );
	if (gPE_AMG_GRM_O24.phys.addr ) iounmap((void *)gPE_AMG_GRM_O24.phys.addr );
	if (gPE_VSD_OBE_O24.phys.addr     ) iounmap((void *)gPE_VSD_OBE_O24.phys.addr    );
	if (gPE_OSD_ORD_O24.phys.addr ) iounmap((void *)gPE_OSD_ORD_O24.phys.addr );
	if (gPE_VSD_DTM_O24.phys.addr     ) iounmap((void *)gPE_VSD_DTM_O24.phys.addr    );

	if (gPE_VCP_DISP_O24.phys.addr)  iounmap((void *)gPE_VCP_DISP_O24.phys.addr);
	if (gPE_VSD0_VERI_O24.phys.addr) iounmap((void *)gPE_VSD0_VERI_O24.phys.addr);
	if (gPE_OLB_O24.phys.addr)       iounmap((void *)gPE_OLB_O24.phys.addr);

	if (gPE_SR_2K_SHP0_O24.phys.addr  ) iounmap((void *)gPE_SR_2K_SHP0_O24.phys.addr	);
	if (gPE_SR_2K_SHP1_O24.phys.addr  ) iounmap((void *)gPE_SR_2K_SHP1_O24.phys.addr	);
	if (gPE_SR_2K_SHC_O24.phys.addr  ) iounmap((void *)gPE_SR_2K_SHC_O24.phys.addr	);
	if (gPE_SR_MERG_O24.phys.addr  ) iounmap((void *)gPE_SR_MERG_O24.phys.addr	);
	if (gPE_SR_VERI_O24.phys.addr  ) iounmap((void *)gPE_SR_VERI_O24.phys.addr	);
	if (gPE_GAV_SHP_O24.phys.addr  ) iounmap((void *)gPE_GAV_SHP_O24.phys.addr	);

	if (gPE_DDR_DB_O24.phys.addr) vunmap_phys((void *)gPE_DDR_DB_O24.phys.addr);
	if (gPE_DCM_DDR_DB_O24F22.phys.addr) vunmap_phys((void *)gPE_DCM_DDR_DB_O24F22.phys.addr);
	if (gPE_DBC_DDR_DB_O24F22.phys.addr) vunmap_phys((void *)gPE_DBC_DDR_DB_O24F22.phys.addr);
	#if 0	//TODO:
	//if (gPE_HDMI_A_O24.phys.addr  ) iounmap((void *)gPE_HDMI_A_O24.phys.addr  );
	//if (gPE_HDMI_B_O24.phys.addr  ) iounmap((void *)gPE_HDMI_B_O24.phys.addr  );
	//if (gPE_HDMI_C_O24.phys.addr  ) iounmap((void *)gPE_HDMI_C_O24.phys.addr  );
	//if (gPE_HDMI_D_O24.phys.addr  ) iounmap((void *)gPE_HDMI_D_O24.phys.addr  );
	if (gPE_LGSR_DDR_DB_O24.phys.addr) vunmap_phys((void *)gPE_LGSR_DDR_DB_O24.phys.addr);
	if (gPE_LGSR_DDR_DB_O24F22.phys.addr) vunmap_phys((void *)gPE_LGSR_DDR_DB_O24F22.phys.addr);
	#endif
	if (gPE_MCU_O24.phys.addr) iounmap((void *)gPE_MCU_O24.phys.addr);
	if (gPE_CCO_VERI_O24.phys.addr) iounmap((void *)gPE_CCO_VERI_O24.phys.addr);

	if (gPE_CHPI_DDR_O24) vunmap_phys((void *)gPE_CHPI_DDR_O24);
	gPE_CHPI_APB0_O24F22.phys.addr = NULL;
	gPE_CHPI_TBL0_O24F22.phys.addr = NULL;

	PE_PRINT_NOTI("[HDR]vunmap idx & [PE]vunmap blk_apl\n");
	#endif /*PE_HW_O24_BRINGUP*/

	PE_HDR_HW_O24_FreePhyToVirt();

	return ret;
}

/**
 * write address data
 *	- use address already allocated
 *
 * @param   addr [in] UINT32
 * @param   value [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_O24_WrAllocatedAddr(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do{
		if(PE_KDRV_VER_O24)
		{
			if((addr)>=PE_O24_ND0_OFST && (addr)<(PE_O24_ND0_OFST+sizeof(PE_ND_ND0_REG_O24_T)))
			{
				*((UINT32 *)(gPE_ND_ND0_O24.phys.addr+((addr-PE_O24_ND0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_ND1_OFST && (addr)<(PE_O24_ND1_OFST+sizeof(PE_ND_ND1_REG_O24_T)))
			{
				*((UINT32 *)(gPE_ND_ND1_O24.phys.addr+((addr-PE_O24_ND1_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_ND0_VERI_OFST && (addr)<(PE_O24_ND0_VERI_OFST+sizeof(PE_ND0_VERI_REG_O24_T)))
			{
				*((UINT32 *)(gPE_ND0_VERI_O24.phys.addr+((addr-PE_O24_ND0_VERI_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_DNR0_OFST && (addr)<(PE_O24_DNR0_OFST+sizeof(PE_ND_DNR0_REG_O24_T)))
			{
				*((UINT32 *)(gPE_ND_DNR0_O24.phys.addr+((addr-PE_O24_DNR0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_DNR1_OFST && (addr)<(PE_O24_DNR1_OFST+sizeof(PE_ND_DNR1_REG_O24_T)))
			{
				*((UINT32 *)(gPE_ND_DNR1_O24.phys.addr+((addr-PE_O24_DNR1_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_ND1_VERI_OFST && (addr)<(PE_O24_ND1_VERI_OFST+sizeof(PE_ND1_VERI_REG_O24_T)))
			{
				*((UINT32 *)(gPE_ND1_VERI_O24.phys.addr+((addr-PE_O24_ND1_VERI_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_SR_2K_SHP0_OFST && (addr)<(PE_O24_SR_2K_SHP0_OFST+sizeof(PE_SR_2K_SHP_REG_O24_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHP0_O24.phys.addr+((addr-PE_O24_SR_2K_SHP0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_SR_2K_SHP1_OFST && (addr)<(PE_O24_SR_2K_SHP1_OFST+sizeof(PE_SR_2K_SHP_REG_O24_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHP1_O24.phys.addr+((addr-PE_O24_SR_2K_SHP1_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_SR_2K_SHC_OFST && (addr)<(PE_O24_SR_2K_SHC_OFST+sizeof(PE_SR_2K_SHC_REG_O24_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHC_O24.phys.addr+((addr-PE_O24_SR_2K_SHC_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_SR_MERG_OFST && (addr)<(PE_O24_SR_MERG_OFST+sizeof(PE_SR_MERG_REG_O24_T)))
			{
				*((UINT32 *)(gPE_SR_MERG_O24.phys.addr+((addr-PE_O24_SR_MERG_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_GAV_SHP_OFST && (addr)<(PE_O24_GAV_SHP_OFST+sizeof(PE_GAV_SHP_REG_O24_T)))
			{
				*((UINT32 *)(gPE_GAV_SHP_O24.phys.addr+((addr-PE_O24_GAV_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_P1_VSD_SHP_L_OFST && (addr)<(PE_O24_P1_VSD_SHP_L_OFST+sizeof(PE_VSD_SHP_REG_O24_T)))
			{
				*((UINT32 *)(gPE_VSD_SHP_O24.phys.addr+((addr-PE_O24_P1_VSD_SHP_L_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_P1_VSD_OBC_BODY_OFST&& (addr)<(PE_O24_P1_VSD_OBC_BODY_OFST+sizeof(PE_VSD_OBC_BODY_REG_O24_T)))
			{
				*((UINT32 *)(gPE_VSD_OBC_BODY_O24.phys.addr+((addr-PE_O24_P1_VSD_OBC_BODY_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_P1_VSD_OBC_HEAD_OFST && (addr)<(PE_O24_P1_VSD_OBC_HEAD_OFST+sizeof(PE_VSD_OBC_HEAD_REG_O24_T)))
			{
				*((UINT32 *)(gPE_VSD_OBC_HEAD_O24.phys.addr+((addr-PE_O24_P1_VSD_OBC_HEAD_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_AMG_BODY_OFST&& (addr)<(PE_O24_AMG_BODY_OFST+sizeof(PE_AMG_BODY_REG_O24_T)))
			{
				*((UINT32 *)(gPE_AMG_BODY_O24.phys.addr+((addr-PE_O24_AMG_BODY_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_AMG_HEAD_OFST && (addr)<(PE_O24_AMG_HEAD_OFST+sizeof(PE_AMG_HEAD_REG_O24_T)))
			{
				*((UINT32 *)(gPE_AMG_HEAD_O24.phys.addr+((addr-PE_O24_AMG_HEAD_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_AMG_MTB_OFST && (addr)<(PE_O24_AMG_MTB_OFST+sizeof(PE_AMG_MTB_REG_O24_T)))
			{
				*((UINT32 *)(gPE_AMG_MTB_O24.phys.addr+((addr-PE_O24_AMG_MTB_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_AMG_GRM_OFST && (addr)<(PE_O24_AMG_GRM_OFST+sizeof(PE_AMG_GRM_REG_O24_T)))
			{
				*((UINT32 *)(gPE_AMG_GRM_O24.phys.addr+((addr-PE_O24_AMG_GRM_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_P1_VSD_OBE_OFST && (addr)<(PE_O24_P1_VSD_OBE_OFST+sizeof(PE_VSD_OBE_REG_O24_T)))
			{
				*((UINT32 *)(gPE_VSD_OBE_O24.phys.addr+((addr-PE_O24_P1_VSD_OBE_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_OSD_ORD_OFST&& (addr)<(PE_O24_OSD_ORD_OFST+sizeof(PE_OSD_ORD_REG_O24_T)))
			{
				*((UINT32 *)(gPE_OSD_ORD_O24.phys.addr+((addr-PE_O24_OSD_ORD_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_P1_VSD_DTM_OFST && (addr)<(PE_O24_P1_VSD_DTM_OFST+sizeof(PE_VSD_DTM_REG_O24_T)))
			{
				*((UINT32 *)(gPE_VSD_DTM_O24.phys.addr+((addr-PE_O24_P1_VSD_DTM_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_IMX_OFST && (addr)<(PE_O24_IMX_OFST+sizeof(PE_TOP_IMX_REG_O24_T)))
			{
				*((UINT32 *)(gPE_TOP_IMX_O24.phys.addr+((addr-PE_O24_IMX_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O24_CCO_DCNT_OFST && (addr)<(PE_O24_CCO_DCNT_OFST+sizeof(PE_CCO_DECON_REG_O24_T)))
			{
				*((UINT32 *)(gPE_CCO_DCNT_O24.phys.addr+((addr-PE_O24_CCO_DCNT_OFST)/sizeof(UINT32)))) = value;
			}
			else
			{
				PE_PRINT_WARN("[%x]not support.(0x%04x, 0x%08x)\n",\
					PE_CHIP_VER,(addr),(value));
			}
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}

/**
 * PE_REG_O24_GetDispOpt
 * see PE_REG_O24_HW_OPT_T
 *
 * @param   void
 * @return  UINT32
 * @see
 * @author
 */
PE_REG_O24_HW_OPT_T PE_REG_O24_GetDispOpt(void)
{
	return _g_pe_reg_o24_disp_opt;
}

