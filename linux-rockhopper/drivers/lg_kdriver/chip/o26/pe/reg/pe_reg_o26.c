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

/** @file pe_reg_o26.c
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

#include "pe_hw_o26.h"
#include "pe_reg_o26.h"
#include "pe_inf_o26.h"
#include "pe_hdr_ddr_o26.h"
#include "pe_hdr_hw_o26.h"

#ifdef INCLUDE_KDRV_BE
#include "ovi_hal.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_REG_O26_CHECK_CODE(_checker,_action,fmt,args...)		\
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
//update done
PE_CC_PE1_REG_TYPE_O26_T    gPE_CC_PE1_O26;
PE_CC2_PE1_REG_TYPE_O26_T   gPE_CC2_PE1_O26;
PE_CCO_DECON_REG_TYPE_O26_T gPE_CCO_DCNT_O26;
PE_CCO_VERI_REG_TYPE_O26_T  gPE_CCO_VERI_O26;
PE_OSD_ORD_REG_TYPE_O26_T   gPE_OSD_ORD_O26;
PE_CVI_REG_TYPE_O26_T       gPE_CVI_A_O26;
PE_CVI_REG_TYPE_O26_T       gPE_CVI_B_O26;
PE_CVI_REG_TYPE_O26_T       gPE_CVI_C_O26;
PE_CVI_REG_TYPE_O26_T       gPE_CVI_D_O26;
PE_OSC0_Y_REG_TYPE_O26_T    gPE_OSC0_Y_O26;
PE_OSC1_Y_REG_TYPE_O26_T    gPE_OSC1_Y_O26;
PE_OSC0_C_REG_TYPE_O26_T    gPE_OSC0_C_O26;
PE_OSC1_C_REG_TYPE_O26_T    gPE_OSC1_C_O26;
PE_OSC2_Y_REG_TYPE_O26_T    gPE_OSC2_Y_O26;
PE_OSC2_C_REG_TYPE_O26_T    gPE_OSC2_C_O26;
PE_OSC3_Y_REG_TYPE_O26_T    gPE_OSC3_Y_O26;
PE_OSC3_C_REG_TYPE_O26_T    gPE_OSC3_C_O26;
PE_ND_REG_TYPE_O26_T        gPE_ND0_O26;
PE_ND_REG_TYPE_O26_T        gPE_ND1_O26;
PE_ND_REG_TYPE_O26_T        gPE_ND2_O26;
PE_DNR0_REG_TYPE_O26_T      gPE_DNR0_O26;
PE_DNR1_REG_TYPE_O26_T      gPE_DNR1_O26;
PE_ND0_VERI_REG_TYPE_O26_T  gPE_ND0_VERI_O26;
PE_ND1_VERI_REG_TYPE_O26_T  gPE_ND1_VERI_O26;
PE_TOP_IMX_REG_TYPE_O26_T   gPE_TOP_IMX_O26;
PE_SR_2K_SHP_REG_TYPE_O26_T gPE_SR_2K_SHP0_O26;
PE_SR_2K_SHP_REG_TYPE_O26_T gPE_SR_2K_SHP1_O26;
PE_SR_2K_SHC_REG_TYPE_O26_T gPE_SR_2K_SHC_O26;
PE_SR_MERG_REG_TYPE_O26_T   gPE_SR_MERG_O26;
PE_SR_BLEND_REG_TYPE_O26_T  gPE_SR_BLEND_O26;
PE_SR_VERI_REG_TYPE_O26_T   gPE_SR_VERI_O26;
PE_GAV_SHP_REG_TYPE_O26_T   gPE_GAV_SHP_O26;
PE_VCP_DISP_REG_TYPE_O26_T 	gPE_VCP_DISP_O26;
PE_VLB_REG_TYPE_O26_T 		gPE_VLB_O26;
PE_FMC_VERI_REG_TYPE_O26_T 	gPE_FMC_VERI_O26;
PE_VSD_VERI_REG_TYPE_O26_T  gPE_VSD_VERI_O26;
PE_AMG_BODY_REG_TYPE_O26_T  gPE_AMG_BODY_O26;
PE_AMG_HEAD_REG_TYPE_O26_T  gPE_AMG_HEAD_O26;
PE_AMG_MTB_REG_TYPE_O26_T   gPE_AMG_MTB_O26;
PE_AMG_GRM_REG_TYPE_O26_T   gPE_AMG_GRM_O26;
PE_VSD_SHP_REG_TYPE_O26_T   gPE_VSD_SHP_O26;
PE_VSD_OBC_BODY_REG_TYPE_O26_T gPE_VSD_OBC_BODY_O26;
PE_VSD_OBC_HEAD_REG_TYPE_O26_T gPE_VSD_OBC_HEAD_O26;
PE_VSD_OBE_REG_TYPE_O26_T   gPE_VSD_OBE_O26;
PE_VSD_DTM_REG_TYPE_O26_T   gPE_VSD_DTM_O26;
PE_LOC_REG_TYPE_O26_T       gPE_LOC_O26;
PE_DDR_DB_REG_TYPE_O26_T    gPE_DDR_DB_O26;
PE_DDR_DB_REG_TYPE_O26F22_T gPE_DDR_DB_O26F22;
PE_DCM_DDR_DB_REG_TYPE_O26F22_T gPE_DCM_DDR_DB_O26F22;
PE_DBC_DDR_DB_REG_TYPE_O26F22_T gPE_DBC_DDR_DB_O26F22;
PE_CHPI_REG_TYPE_O26F22_T   gPE_CHPI_APB0_O26F22;
PE_CHPI_REG_TYPE_O26F22_T   gPE_CHPI_APB1_O26F22;//causion : shdw not used(null)
PE_CHPI_TBL0_TYPE_O26F22_T  gPE_CHPI_TBL0_O26F22;
PE_CHPI_TBL0_TYPE_O26F22_T  gPE_CHPI_TBL1_O26F22;//causion : shdw not used(null)
volatile UINT32 *gPE_CHPI_DDR_O26 = NULL;

#ifndef PE_HW_O26_BRINGUP
PE_MCU_REG_TYPE_O26_T gPE_MCU_O26;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_REG_O26_HW_OPT_T _g_pe_reg_o26_disp_opt;

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef INCLUDE_KDRV_BE
static int PE_REG_O26_GetHwOpt(UINT32 *opt)
{
	PE_REG_O26_HW_OPT_T panel_mode;
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
			if (ovi_opt.frcChipType == LX_OVI_FRC_CHIP_UD_BE_KLD) {
				panel_mode.external_chip  = 2;//see LX_DE_IPC_EXTERNAL_CHIP_KLD;
			} else {
				panel_mode.external_chip  = 1;//see LX_DE_IPC_EXTERNAL_CHIP_USE;
			}
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
	PE_INF_HW_O26_BACKUP_TRACE("[Opt]fr:%d,pt:%d,vx1:%d,ext%d,pr:%d",panel_mode.panel_frame_rate,\
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
int PE_REG_O26_InitPhyToVirt(void)
{
	int ret = RET_OK;

	/* shdw */
	gPE_CC_PE1_O26.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CC_PE1_REG_O26_T));
	gPE_CC2_PE1_O26.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_CC2_PE1_REG_O26_T));
	gPE_CCO_DCNT_O26.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_CCO_DECON_REG_O26_T));
	gPE_CCO_VERI_O26.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_CCO_VERI_REG_O26_T));
	gPE_OSD_ORD_O26.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_OSD_ORD_REG_O26_T));
	gPE_CVI_A_O26.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O26_T));
	gPE_CVI_B_O26.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O26_T));
	gPE_CVI_C_O26.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O26_T));
	gPE_CVI_D_O26.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O26_T));
	gPE_OSC0_Y_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_OSC0_Y_REG_O26_T));
	gPE_OSC1_Y_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_OSC1_Y_REG_O26_T));
	gPE_OSC0_C_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_OSC0_C_REG_O26_T));
	gPE_OSC1_C_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_OSC1_C_REG_O26_T));
	gPE_OSC2_Y_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_OSC2_Y_REG_O26_T));
	gPE_OSC2_C_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_OSC2_C_REG_O26_T));
	gPE_OSC3_Y_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_OSC3_Y_REG_O26_T));
	gPE_OSC3_C_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_OSC3_C_REG_O26_T));
	gPE_ND0_O26.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_REG_O26_T));
	gPE_ND1_O26.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_REG_O26_T));
	gPE_ND2_O26.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_REG_O26_T));
	gPE_DNR0_O26.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_DNR0_REG_O26_T));
	gPE_DNR1_O26.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_DNR1_REG_O26_T));
	gPE_ND0_VERI_O26.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_ND0_VERI_REG_O26_T));
	gPE_ND1_VERI_O26.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_ND1_VERI_REG_O26_T));
	gPE_TOP_IMX_O26.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_TOP_IMX_REG_O26_T));
	gPE_SR_2K_SHP0_O26.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHP_REG_O26_T));
	gPE_SR_2K_SHP1_O26.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHP_REG_O26_T));
	gPE_SR_2K_SHC_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHC_REG_O26_T));
	gPE_SR_MERG_O26.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_MERG_REG_O26_T));
	gPE_SR_BLEND_O26.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_SR_BLEND_REG_O26_T));
	gPE_SR_VERI_O26.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_SRE_VERI_REG_O26_T));
	gPE_GAV_SHP_O26.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_GAV_SHP_REG_O26_T));
	gPE_VCP_DISP_O26.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DISP_REG_O26_T));
	gPE_VLB_O26.shdw.addr 	    = (UINT32 *)OS_KMalloc(sizeof(PE_VLB_REG_O26_T));
	gPE_FMC_VERI_O26.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_FMC_VERI_REG_O26_T));
	gPE_VSD_VERI_O26.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_VERI_REG_O26_T));
	gPE_VSD_SHP_O26.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_SHP_REG_O26_T));
	gPE_VSD_OBC_BODY_O26.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBC_BODY_REG_O26_T));
	gPE_VSD_OBC_HEAD_O26.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBC_HEAD_REG_O26_T));
	gPE_AMG_BODY_O26.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_AMG_BODY_REG_O26_T));
	gPE_AMG_HEAD_O26.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_AMG_HEAD_REG_O26_T));
	gPE_AMG_MTB_O26.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_AMG_MTB_REG_O26_T));
	gPE_AMG_GRM_O26.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_AMG_GRM_REG_O26_T));
	gPE_VSD_OBE_O26.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBE_REG_O26_T));
	gPE_VSD_DTM_O26.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_DTM_REG_O26_T));
	gPE_LOC_O26.shdw.addr       = (UINT32 *)OS_KMalloc(sizeof(PE_LOC_REG_O26_T));
	gPE_DDR_DB_O26.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O26_T));
	gPE_DDR_DB_O26F22.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O26F22_T));
	gPE_DCM_DDR_DB_O26F22.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_DCM_DDR_DB_SHDW_REG_O26F22_T));
	gPE_DBC_DDR_DB_O26F22.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_DBC_DDR_DB_SHDW_REG_O26F22_T));
	gPE_CHPI_APB0_O26F22.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_CHPI_REG_O26F22_T));
	gPE_CHPI_TBL0_O26F22.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_CHPI_TBL0_O26F22_T));

	/* phys */
	gPE_CC_PE1_O26.phys.addr   	= (volatile UINT32 *)ioremap(PE_O26_CC_BASE,       sizeof(PE_CC_PE1_REG_O26_T));
	gPE_CC2_PE1_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_CC2_BASE,      sizeof(PE_CC2_PE1_REG_O26_T));
	gPE_CCO_DCNT_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_CCO_DEC_BASE,  sizeof(PE_CCO_DECON_REG_O26_T));
	gPE_CCO_VERI_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_CCO_VERI_BASE, sizeof(PE_CCO_VERI_REG_O26_T));
	gPE_OSD_ORD_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_OSD_ORD_BASE,  sizeof(PE_OSD_ORD_REG_O26_T));
	gPE_CVI_A_O26.phys.addr    	= (volatile UINT32 *)ioremap(PE_O26_CVI_A_BASE,    sizeof(PE_CVI_REG_O26_T));
	gPE_CVI_B_O26.phys.addr    	= (volatile UINT32 *)ioremap(PE_O26_CVI_B_BASE,    sizeof(PE_CVI_REG_O26_T));
	gPE_CVI_C_O26.phys.addr    	= (volatile UINT32 *)ioremap(PE_O26_CVI_C_BASE,    sizeof(PE_CVI_REG_O26_T));
	gPE_CVI_D_O26.phys.addr    	= (volatile UINT32 *)ioremap(PE_O26_CVI_D_BASE,    sizeof(PE_CVI_REG_O26_T));
	gPE_OSC0_Y_O26.phys.addr    = (volatile UINT32 *)ioremap(PE_O26_OSC0_Y_BASE,   sizeof(PE_OSC0_Y_REG_O26_T));
	gPE_OSC1_Y_O26.phys.addr    = (volatile UINT32 *)ioremap(PE_O26_OSC1_Y_BASE,   sizeof(PE_OSC1_Y_REG_O26_T));
	gPE_OSC0_C_O26.phys.addr    = (volatile UINT32 *)ioremap(PE_O26_OSC0_C_BASE,   sizeof(PE_OSC0_C_REG_O26_T));
	gPE_OSC1_C_O26.phys.addr    = (volatile UINT32 *)ioremap(PE_O26_OSC1_C_BASE,   sizeof(PE_OSC1_C_REG_O26_T));
	gPE_OSC2_Y_O26.phys.addr    = (volatile UINT32 *)ioremap(PE_O26_OSC2_Y_BASE,   sizeof(PE_OSC2_Y_REG_O26_T));
	gPE_OSC2_C_O26.phys.addr    = (volatile UINT32 *)ioremap(PE_O26_OSC2_C_BASE,   sizeof(PE_OSC2_C_REG_O26_T));
	gPE_OSC3_Y_O26.phys.addr    = (volatile UINT32 *)ioremap(PE_O26_OSC3_Y_BASE,   sizeof(PE_OSC3_Y_REG_O26_T));
	gPE_OSC3_C_O26.phys.addr    = (volatile UINT32 *)ioremap(PE_O26_OSC3_C_BASE,   sizeof(PE_OSC3_C_REG_O26_T));
	gPE_ND0_O26.phys.addr       = (volatile UINT32 *)ioremap(PE_O26_ND0_BASE,      sizeof(PE_ND_REG_O26_T));
	gPE_ND1_O26.phys.addr       = (volatile UINT32 *)ioremap(PE_O26_ND1_BASE,      sizeof(PE_ND_REG_O26_T));
	gPE_ND2_O26.phys.addr       = (volatile UINT32 *)ioremap(PE_O26_ND2_BASE,      sizeof(PE_ND_REG_O26_T));
	gPE_DNR0_O26.phys.addr      = (volatile UINT32 *)ioremap(PE_O26_DNR0_BASE,     sizeof(PE_DNR0_REG_O26_T));
	gPE_DNR1_O26.phys.addr      = (volatile UINT32 *)ioremap(PE_O26_DNR1_BASE,     sizeof(PE_DNR1_REG_O26_T));
	gPE_ND0_VERI_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_ND0_VERI_BASE, sizeof(PE_ND0_VERI_REG_O26_T));
	gPE_ND1_VERI_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_ND1_VERI_BASE, sizeof(PE_ND1_VERI_REG_O26_T));
	gPE_TOP_IMX_O26.phys.addr  	= (volatile UINT32 *)ioremap(PE_O26_IMX_BASE,      sizeof(PE_TOP_IMX_REG_O26_T));
	gPE_SR_2K_SHP0_O26 .phys.addr=(volatile UINT32 *)ioremap(PE_O26_SR_2K_SHP0_BASE,sizeof(PE_SR_2K_SHP_REG_O26_T));
	gPE_SR_2K_SHP1_O26 .phys.addr=(volatile UINT32 *)ioremap(PE_O26_SR_2K_SHP1_BASE,sizeof(PE_SR_2K_SHP_REG_O26_T));
	gPE_SR_2K_SHC_O26 .phys.addr= (volatile UINT32 *)ioremap(PE_O26_SR_2K_SHC_BASE,sizeof(PE_SR_2K_SHC_REG_O26_T));
	gPE_SR_MERG_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_SR_MERG_BASE,  sizeof(PE_SR_MERG_REG_O26_T));
	gPE_SR_BLEND_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_SR_BLEND_BASE, sizeof(PE_SR_BLEND_REG_O26_T));
	gPE_SR_VERI_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_SRE_VERI_BASE, sizeof(PE_SRE_VERI_REG_O26_T));
	gPE_GAV_SHP_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_GAV_SHP_BASE,  sizeof(PE_GAV_SHP_REG_O26_T));
	gPE_VCP_DISP_O26.phys.addr 	= (volatile UINT32 *)ioremap(PE_O26_VCP_DISP_BASE, sizeof(PE_VCP_DISP_REG_O26_T));
	gPE_VLB_O26.phys.addr 		= (volatile UINT32 *)ioremap(PE_O26_VLB_BASE,      sizeof(PE_VLB_REG_O26_T));
	gPE_VSD_VERI_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_VSD_VERI_BASE, sizeof(PE_VSD_VERI_REG_O26_T));
	gPE_FMC_VERI_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_FMC_VERI_BASE, sizeof(PE_FMC_VERI_REG_O26_T));
	gPE_VSD_SHP_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_VSD_SHP_BASE,  sizeof(PE_VSD_SHP_REG_O26_T));
	gPE_VSD_OBC_BODY_O26.phys.addr=(volatile UINT32 *)ioremap(PE_O26_OBC_BODY_BASE,sizeof(PE_VSD_OBC_BODY_REG_O26_T));
	gPE_VSD_OBC_HEAD_O26.phys.addr=(volatile UINT32 *)ioremap(PE_O26_OBC_HEAD_BASE,sizeof(PE_VSD_OBC_HEAD_REG_O26_T));
	gPE_AMG_BODY_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_AMG1_BODY_BASE,sizeof(PE_AMG_BODY_REG_O26_T));
	gPE_AMG_HEAD_O26.phys.addr  = (volatile UINT32 *)ioremap(PE_O26_AMG0_HEAD_BASE,sizeof(PE_AMG_HEAD_REG_O26_T));
	gPE_AMG_MTB_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_AMG2_MTB_BASE, sizeof(PE_AMG_MTB_REG_O26_T));
	gPE_AMG_GRM_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_AMG3_GRM_BASE, sizeof(PE_AMG_GRM_REG_O26_T));
	gPE_VSD_OBE_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_OBE_BASE,      sizeof(PE_VSD_OBE_REG_O26_T));
	gPE_VSD_DTM_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_DTM_BASE,      sizeof(PE_VSD_DTM_REG_O26_T));
	gPE_LOC_O26.phys.addr       = (volatile UINT32 *)ioremap(PE_O26_LOC_BASE,      sizeof(PE_LOC_REG_O26_T));
	gPE_DDR_DB_O26.phys.addr    = (volatile UINT32 *)vmap_phys(PE_O26_DDR_DB0_BASE,sizeof(PE_DDR_DB_PHYS_REG_O26_T)+PAGE_SIZE);
	gPE_DDR_DB_O26F22.phys.addr = (volatile UINT32 *)vmap_phys(PE_O26F22_DDR_BASE,sizeof(PE_DDR_DB_PHYS_REG_O26F22_T)+PAGE_SIZE);
	gPE_DCM_DDR_DB_O26F22.phys.addr= (volatile UINT32 *)vmap_phys(PE_O26F22_DCM_DDR_BASE,sizeof(PE_DCM_DDR_DB_PHYS_REG_O26F22_T)+PAGE_SIZE);
	gPE_DBC_DDR_DB_O26F22.phys.addr= (volatile UINT32 *)vmap_phys(PE_O26F22_DBC_DDR_BASE,sizeof(PE_DBC_DDR_DB_PHYS_REG_O26F22_T)+PAGE_SIZE);

	#if 0
	gPE_MCU_O26.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_MCU_REG_O26_T));
	gPE_MCU_O26.phys.addr   = (volatile UINT32 *)ioremap(PE_O26_MCU_BASE,      sizeof(PE_MCU_REG_O26_T));
	#endif /*PE_HW_O26_BRINGUP*/

	_g_pe_reg_o26_disp_opt.u32Data = 0;
	#ifdef INCLUDE_KDRV_BE
	ret = PE_REG_O26_GetHwOpt(&(_g_pe_reg_o26_disp_opt.u32Data));
	#endif

	do {
		UINT32 chpi_base = 0, chpi_size = 0;
		UINT32 apb_s[4],apb_e[4],st_size[3],max_size[3];

		if (_g_pe_reg_o26_disp_opt.external_chip == 0)
		{
			PE_INF_HW_O26_BACKUP_CHPI1("[CHI]skip (external_chip:0)");
			break;
		}

		#if 1
		#ifdef INCLUDE_KDRV_DE
		chpi_base = g_chipinfo.base;
		chpi_size = g_chipinfo.size;
		#endif
		if (chpi_base==0)	break;
		if (chpi_size==0)	break;
		gPE_CHPI_DDR_O26 = (volatile UINT32 *)vmap_phys(chpi_base,chpi_size);
		gPE_CHPI_APB0_O26F22.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR_O26 + (PE_CHPI_APB0_O26F22_S_OFST0>>2));//buf[1]
		gPE_CHPI_APB1_O26F22.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR_O26 + (PE_CHPI_APB1_O26F22_S_OFST0>>2));//buf[4]
		gPE_CHPI_TBL0_O26F22.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR_O26 + (PE_CHPI_TBL0_O26F22_S_OFST0>>2));//buf[2]
		gPE_CHPI_TBL1_O26F22.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR_O26 + (PE_CHPI_TBL1_O26F22_S_OFST0>>2));//buf[5]
		PE_INF_HW_O26_BACKUP_CHPI0("[CHI]0x%08x,0x%08x,0x%px",chpi_base,chpi_size,gPE_CHPI_DDR_O26);
		PE_PRINT_NOTI("[CHI]apb:0x%px,0x%px\n",gPE_CHPI_APB0_O26F22.phys.addr,gPE_CHPI_APB1_O26F22.phys.addr);
		PE_PRINT_NOTI("[CHI]tbl:0x%px,0x%px\n",gPE_CHPI_TBL0_O26F22.phys.addr,gPE_CHPI_TBL1_O26F22.phys.addr);
		#endif

		/* info apb */
		apb_s[0] = (chpi_base+PE_CHPI_APB0_O26F22_S_OFST0);
		apb_e[0] = (chpi_base+PE_CHPI_APB0_O26F22_E_OFST0);
		apb_s[1] = (chpi_base+PE_CHPI_APB0_O26F22_S_OFST1);
		apb_e[1] = (chpi_base+PE_CHPI_APB0_O26F22_E_OFST1);
		apb_s[2] = (chpi_base+PE_CHPI_APB1_O26F22_S_OFST0);
		apb_e[2] = (chpi_base+PE_CHPI_APB1_O26F22_E_OFST0);
		apb_s[3] = (chpi_base+PE_CHPI_APB1_O26F22_S_OFST1);
		apb_e[3] = (chpi_base+PE_CHPI_APB1_O26F22_E_OFST1);
		st_size[0] = sizeof(PE_CHPI_REG0_O26F22_T);
		st_size[1] = sizeof(PE_CHPI_REG1_O26F22_T);
		st_size[2] = sizeof(PE_CHPI_REG_O26F22_T);
		max_size[0] = PE_CHPI_APB_O26F22_SIZE0;
		max_size[1] = PE_CHPI_APB_O26F22_SIZE1;
		max_size[2] = PE_CHPI_APB_O26F22_TOTAL;
		PE_INF_HW_O26_BACKUP_CHPI0("[CHI]apb:0x%08x,0x%08x|0x%08x,0x%08x|0x%08x,0x%08x|0x%08x,0x%08x",apb_s[0],apb_e[0],apb_s[1],apb_e[1],apb_s[2],apb_e[2],apb_s[3],apb_e[3]);
		PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[0],max_size[0],max_size[0]-st_size[0],(max_size[0]-st_size[0])>>2);
		PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[1],max_size[1],max_size[1]-st_size[1],(max_size[1]-st_size[1])>>2);
		PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[2],max_size[2],max_size[2]-st_size[2],(max_size[2]-st_size[2])>>2);
		/* info tbl */
		apb_s[0] = (chpi_base+PE_CHPI_TBL0_O26F22_S_OFST0);
		apb_e[0] = (chpi_base+PE_CHPI_TBL0_O26F22_E_OFST0);
		apb_s[1] = (chpi_base+PE_CHPI_TBL1_O26F22_S_OFST0);
		apb_e[1] = (chpi_base+PE_CHPI_TBL1_O26F22_E_OFST0);
		st_size[0] = sizeof(PE_CHPI_TBL0_O26F22_T);
		max_size[0] = PE_CHPI_TBL_O26F22_TOTAL;
		PE_INF_HW_O26_BACKUP_CHPI1("[CHI]tbl:0x%08x,0x%08x|0x%08x,0x%08x",apb_s[0],apb_e[0],apb_s[1],apb_e[1]);
		PE_PRINT_NOTI("[CHI]tbl:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[0],max_size[0],max_size[0]-st_size[0],(max_size[0]-st_size[0])>>2);

	} while(0);

	PE_PRINT_NOTI("[PE]vmap base:0x%08x,size:0x%08x+0x%08x\n",\
		PE_O26_DDR_DB0_BASE,(UINT32)sizeof(PE_DDR_DB_PHYS_REG_O26_T),(UINT32)PAGE_SIZE);
	PE_PRINT_NOTI("[PE]vmap base:0x%08x,size:0x%08x+0x%08x\n",\
		PE_LGSR_DDR_O26_BASE_ADDR,(UINT32)sizeof(PE_LGSR_DDR_DB_PHYS_REG_O26_T),(UINT32)PAGE_SIZE);

	PE_HDR_HW_O26_InitPhyToVirt();

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
int PE_REG_O26_FreePhyToVirt(void)
{
	int ret = RET_OK;
	/* shdw */
	if (gPE_CC_PE1_O26.shdw.addr  ) OS_Free((void *)gPE_CC_PE1_O26.shdw.addr  );
	if (gPE_CC2_PE1_O26.shdw.addr ) OS_Free((void *)gPE_CC2_PE1_O26.shdw.addr );
	if (gPE_CCO_DCNT_O26.shdw.addr) OS_Free((void *)gPE_CCO_DCNT_O26.shdw.addr);
	if (gPE_CCO_VERI_O26.shdw.addr) OS_Free((void *)gPE_CCO_VERI_O26.shdw.addr);
	if (gPE_OSD_ORD_O26.shdw.addr ) OS_Free((void *)gPE_OSD_ORD_O26.shdw.addr );
	if (gPE_CVI_A_O26.shdw.addr   ) OS_Free((void *)gPE_CVI_A_O26.shdw.addr   );
	if (gPE_CVI_B_O26.shdw.addr   ) OS_Free((void *)gPE_CVI_B_O26.shdw.addr   );
	if (gPE_CVI_C_O26.shdw.addr   ) OS_Free((void *)gPE_CVI_C_O26.shdw.addr   );
	if (gPE_CVI_D_O26.shdw.addr   ) OS_Free((void *)gPE_CVI_D_O26.shdw.addr   );
	if (gPE_OSC0_Y_O26.shdw.addr  ) OS_Free((void *)gPE_OSC0_Y_O26.shdw.addr );
	if (gPE_OSC1_Y_O26.shdw.addr  ) OS_Free((void *)gPE_OSC1_Y_O26.shdw.addr );
	if (gPE_OSC0_C_O26.shdw.addr  ) OS_Free((void *)gPE_OSC0_C_O26.shdw.addr );
	if (gPE_OSC1_C_O26.shdw.addr  ) OS_Free((void *)gPE_OSC1_C_O26.shdw.addr );
	if (gPE_OSC2_Y_O26.shdw.addr  ) OS_Free((void *)gPE_OSC2_Y_O26.shdw.addr );
	if (gPE_OSC2_C_O26.shdw.addr  ) OS_Free((void *)gPE_OSC2_C_O26.shdw.addr );
	if (gPE_OSC3_Y_O26.shdw.addr  ) OS_Free((void *)gPE_OSC3_Y_O26.shdw.addr );
	if (gPE_OSC3_C_O26.shdw.addr  ) OS_Free((void *)gPE_OSC3_C_O26.shdw.addr );
	if (gPE_ND0_O26.shdw.addr     ) OS_Free((void *)gPE_ND0_O26.shdw.addr  );
	if (gPE_ND1_O26.shdw.addr     ) OS_Free((void *)gPE_ND1_O26.shdw.addr  );
	if (gPE_ND2_O26.shdw.addr     ) OS_Free((void *)gPE_ND2_O26.shdw.addr  );
	if (gPE_DNR0_O26.shdw.addr    ) OS_Free((void *)gPE_DNR0_O26.shdw.addr );
	if (gPE_DNR1_O26.shdw.addr    ) OS_Free((void *)gPE_DNR1_O26.shdw.addr );
	if (gPE_ND0_VERI_O26.shdw.addr) OS_Free((void *)gPE_ND0_VERI_O26.shdw.addr);
	if (gPE_ND1_VERI_O26.shdw.addr) OS_Free((void *)gPE_ND1_VERI_O26.shdw.addr);
	if (gPE_TOP_IMX_O26.shdw.addr ) OS_Free((void *)gPE_TOP_IMX_O26.shdw.addr );
	if (gPE_SR_2K_SHP0_O26.shdw.addr) OS_Free((void *)gPE_SR_2K_SHP0_O26.shdw.addr);
	if (gPE_SR_2K_SHP1_O26.shdw.addr) OS_Free((void *)gPE_SR_2K_SHP1_O26.shdw.addr);
	if (gPE_SR_2K_SHC_O26.shdw.addr) OS_Free((void *)gPE_SR_2K_SHC_O26.shdw.addr);
	if (gPE_SR_MERG_O26.shdw.addr  ) OS_Free((void *)gPE_SR_MERG_O26.shdw.addr  );
	if (gPE_SR_BLEND_O26.shdw.addr ) OS_Free((void *)gPE_SR_BLEND_O26.shdw.addr  );
	if (gPE_SR_VERI_O26.shdw.addr  ) OS_Free((void *)gPE_SR_VERI_O26.shdw.addr  );
	if (gPE_GAV_SHP_O26.shdw.addr  ) OS_Free((void *)gPE_GAV_SHP_O26.shdw.addr  );
	if (gPE_VCP_DISP_O26.shdw.addr ) OS_Free((void *)gPE_VCP_DISP_O26.shdw.addr );
	if (gPE_VLB_O26.shdw.addr )      OS_Free((void *)gPE_VLB_O26.shdw.addr );
	if (gPE_VSD_VERI_O26.shdw.addr ) OS_Free((void *)gPE_VSD_VERI_O26.shdw.addr );
	if (gPE_FMC_VERI_O26.shdw.addr ) OS_Free((void *)gPE_FMC_VERI_O26.shdw.addr );
	if (gPE_VSD_SHP_O26.shdw.addr  ) OS_Free((void *)gPE_VSD_SHP_O26.shdw.addr  );
	if (gPE_VSD_OBC_BODY_O26.shdw.addr) OS_Free((void *)gPE_VSD_OBC_BODY_O26.shdw.addr);
	if (gPE_VSD_OBC_HEAD_O26.shdw.addr) OS_Free((void *)gPE_VSD_OBC_HEAD_O26.shdw.addr);
	if (gPE_AMG_BODY_O26.shdw.addr ) OS_Free((void *)gPE_AMG_BODY_O26.shdw.addr );
	if (gPE_AMG_HEAD_O26.shdw.addr ) OS_Free((void *)gPE_AMG_HEAD_O26.shdw.addr );
	if (gPE_AMG_MTB_O26.shdw.addr  ) OS_Free((void *)gPE_AMG_MTB_O26.shdw.addr  );
	if (gPE_AMG_GRM_O26.shdw.addr  ) OS_Free((void *)gPE_AMG_GRM_O26.shdw.addr  );
	if (gPE_VSD_OBE_O26.shdw.addr  ) OS_Free((void *)gPE_VSD_OBE_O26.shdw.addr  );
	if (gPE_VSD_DTM_O26.shdw.addr  ) OS_Free((void *)gPE_VSD_DTM_O26.shdw.addr  );
	if (gPE_LOC_O26.shdw.addr      ) OS_Free((void *)gPE_LOC_O26.shdw.addr      );
	if (gPE_DDR_DB_O26.shdw.addr   ) OS_Free((void *)gPE_DDR_DB_O26.shdw.addr   );
	if (gPE_DDR_DB_O26F22.shdw.addr) OS_Free((void *)gPE_DDR_DB_O26F22.shdw.addr);
	if (gPE_DCM_DDR_DB_O26F22.shdw.addr) OS_Free((void *)gPE_DCM_DDR_DB_O26F22.shdw.addr);
	if (gPE_DBC_DDR_DB_O26F22.shdw.addr) OS_Free((void *)gPE_DBC_DDR_DB_O26F22.shdw.addr);
	if (gPE_CHPI_APB0_O26F22.shdw.addr) OS_Free((void *)gPE_CHPI_APB0_O26F22.shdw.addr);
	if (gPE_CHPI_TBL0_O26F22.shdw.addr) OS_Free((void *)gPE_CHPI_TBL0_O26F22.shdw.addr);

	/* phys */
	if (gPE_CC_PE1_O26.phys.addr  ) iounmap((void *)gPE_CC_PE1_O26.phys.addr  );
	if (gPE_CC2_PE1_O26.phys.addr ) iounmap((void *)gPE_CC2_PE1_O26.phys.addr );
	if (gPE_CCO_DCNT_O26.phys.addr) iounmap((void *)gPE_CCO_DCNT_O26.phys.addr);
	if (gPE_CCO_VERI_O26.phys.addr) iounmap((void *)gPE_CCO_VERI_O26.phys.addr);
	if (gPE_OSD_ORD_O26.phys.addr ) iounmap((void *)gPE_OSD_ORD_O26.phys.addr );
	if (gPE_CVI_A_O26.phys.addr   ) iounmap((void *)gPE_CVI_A_O26.phys.addr   );
	if (gPE_CVI_B_O26.phys.addr   ) iounmap((void *)gPE_CVI_B_O26.phys.addr   );
	if (gPE_CVI_C_O26.phys.addr   ) iounmap((void *)gPE_CVI_C_O26.phys.addr   );
	if (gPE_CVI_D_O26.phys.addr   ) iounmap((void *)gPE_CVI_D_O26.phys.addr   );
	if (gPE_OSC0_Y_O26.phys.addr  ) iounmap((void *)gPE_OSC0_Y_O26.phys.addr );
	if (gPE_OSC1_Y_O26.phys.addr  ) iounmap((void *)gPE_OSC1_Y_O26.phys.addr );
	if (gPE_OSC0_C_O26.phys.addr  ) iounmap((void *)gPE_OSC0_C_O26.phys.addr );
	if (gPE_OSC1_C_O26.phys.addr  ) iounmap((void *)gPE_OSC1_C_O26.phys.addr );
	if (gPE_OSC2_Y_O26.phys.addr  ) iounmap((void *)gPE_OSC2_Y_O26.phys.addr );
	if (gPE_OSC2_C_O26.phys.addr  ) iounmap((void *)gPE_OSC2_C_O26.phys.addr );
	if (gPE_OSC3_Y_O26.phys.addr  ) iounmap((void *)gPE_OSC3_Y_O26.phys.addr );
	if (gPE_OSC3_C_O26.phys.addr  ) iounmap((void *)gPE_OSC3_C_O26.phys.addr );
	if (gPE_ND0_O26.phys.addr     ) iounmap((void *)gPE_ND0_O26.phys.addr  );
	if (gPE_ND1_O26.phys.addr     ) iounmap((void *)gPE_ND1_O26.phys.addr  );
	if (gPE_ND2_O26.phys.addr     ) iounmap((void *)gPE_ND2_O26.phys.addr  );
	if (gPE_DNR0_O26.phys.addr    ) iounmap((void *)gPE_DNR0_O26.phys.addr );
	if (gPE_DNR1_O26.phys.addr    ) iounmap((void *)gPE_DNR1_O26.phys.addr );
	if (gPE_ND0_VERI_O26.phys.addr) iounmap((void *)gPE_ND0_VERI_O26.phys.addr);
	if (gPE_ND1_VERI_O26.phys.addr) iounmap((void *)gPE_ND1_VERI_O26.phys.addr);
	if (gPE_TOP_IMX_O26.phys.addr ) iounmap((void *)gPE_TOP_IMX_O26.phys.addr );
	if (gPE_SR_2K_SHP0_O26.phys.addr) iounmap((void *)gPE_SR_2K_SHP0_O26.phys.addr);
	if (gPE_SR_2K_SHP1_O26.phys.addr) iounmap((void *)gPE_SR_2K_SHP1_O26.phys.addr);
	if (gPE_SR_2K_SHC_O26.phys.addr) iounmap((void *)gPE_SR_2K_SHC_O26.phys.addr);
	if (gPE_SR_MERG_O26.phys.addr  ) iounmap((void *)gPE_SR_MERG_O26.phys.addr	);
	if (gPE_SR_BLEND_O26.phys.addr ) iounmap((void *)gPE_SR_BLEND_O26.phys.addr	);
	if (gPE_SR_VERI_O26.phys.addr  ) iounmap((void *)gPE_SR_VERI_O26.phys.addr	);
	if (gPE_GAV_SHP_O26.phys.addr  ) iounmap((void *)gPE_GAV_SHP_O26.phys.addr	);
	if (gPE_VCP_DISP_O26.phys.addr ) iounmap((void *)gPE_VCP_DISP_O26.phys.addr );
	if (gPE_VLB_O26.phys.addr )      iounmap((void *)gPE_VLB_O26.phys.addr );
	if (gPE_VSD_VERI_O26.phys.addr ) iounmap((void *)gPE_VSD_VERI_O26.phys.addr );
	if (gPE_FMC_VERI_O26.phys.addr ) iounmap((void *)gPE_FMC_VERI_O26.phys.addr );
	if (gPE_VSD_SHP_O26.phys.addr  ) iounmap((void *)gPE_VSD_SHP_O26.phys.addr  );
	if (gPE_VSD_OBC_BODY_O26.phys.addr) iounmap((void *)gPE_VSD_OBC_BODY_O26.phys.addr);
	if (gPE_VSD_OBC_HEAD_O26.phys.addr) iounmap((void *)gPE_VSD_OBC_HEAD_O26.phys.addr);
	if (gPE_AMG_BODY_O26.phys.addr ) iounmap((void *)gPE_AMG_BODY_O26.phys.addr );
	if (gPE_AMG_HEAD_O26.phys.addr ) iounmap((void *)gPE_AMG_HEAD_O26.phys.addr );
	if (gPE_AMG_MTB_O26.phys.addr  ) iounmap((void *)gPE_AMG_MTB_O26.phys.addr  );
	if (gPE_AMG_GRM_O26.phys.addr  ) iounmap((void *)gPE_AMG_GRM_O26.phys.addr  );
	if (gPE_VSD_OBE_O26.phys.addr  ) iounmap((void *)gPE_VSD_OBE_O26.phys.addr  );
	if (gPE_VSD_DTM_O26.phys.addr  ) iounmap((void *)gPE_VSD_DTM_O26.phys.addr  );
	if (gPE_LOC_O26.phys.addr      ) iounmap((void *)gPE_LOC_O26.phys.addr      );
	if (gPE_DDR_DB_O26.phys.addr   ) vunmap_phys((void *)gPE_DDR_DB_O26.phys.addr);
	if (gPE_DCM_DDR_DB_O26F22.phys.addr) vunmap_phys((void *)gPE_DCM_DDR_DB_O26F22.phys.addr);
	if (gPE_DBC_DDR_DB_O26F22.phys.addr) vunmap_phys((void *)gPE_DBC_DDR_DB_O26F22.phys.addr);
	if (gPE_CHPI_DDR_O26)                vunmap_phys((void *)gPE_CHPI_DDR_O26);
	gPE_CHPI_APB0_O26F22.phys.addr = NULL;
	gPE_CHPI_TBL0_O26F22.phys.addr = NULL;

	#ifndef PE_HW_O26_BRINGUP
	if (gPE_MCU_O26.shdw.addr) OS_Free((void *)gPE_MCU_O26.shdw.addr);
	if (gPE_MCU_O26.phys.addr) iounmap((void *)gPE_MCU_O26.phys.addr);
	#endif /*PE_HW_O26_BRINGUP*/

	PE_HDR_HW_O26_FreePhyToVirt();

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
int PE_REG_O26_WrAllocatedAddr(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	addr = 0xCC000000 | (addr&0x00ffffff);
	do{
		if(PE_KDRV_VER_O26)
		{
			if((addr)>=PE_O26_ND0_BASE && (addr)<(PE_O26_ND0_BASE+sizeof(PE_ND_REG_O26_T)))
			{
				*((UINT32 *)(gPE_ND0_O26.phys.addr+((addr-PE_O26_ND0_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_ND1_BASE && (addr)<(PE_O26_ND1_BASE+sizeof(PE_ND_REG_O26_T)))
			{
				*((UINT32 *)(gPE_ND1_O26.phys.addr+((addr-PE_O26_ND1_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_ND2_BASE && (addr)<(PE_O26_ND2_BASE+sizeof(PE_ND_REG_O26_T)))
			{
				*((UINT32 *)(gPE_ND2_O26.phys.addr+((addr-PE_O26_ND2_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_ND0_VERI_BASE && (addr)<(PE_O26_ND0_VERI_BASE+sizeof(PE_ND0_VERI_REG_O26_T)))
			{
				*((UINT32 *)(gPE_ND0_VERI_O26.phys.addr+((addr-PE_O26_ND0_VERI_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_DNR0_BASE && (addr)<(PE_O26_DNR0_BASE+sizeof(PE_DNR0_REG_O26_T)))
			{
				*((UINT32 *)(gPE_DNR0_O26.phys.addr+((addr-PE_O26_DNR0_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_DNR1_BASE && (addr)<(PE_O26_DNR1_BASE+sizeof(PE_DNR1_REG_O26_T)))
			{
				*((UINT32 *)(gPE_DNR1_O26.phys.addr+((addr-PE_O26_DNR1_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_ND1_VERI_BASE && (addr)<(PE_O26_ND1_VERI_BASE+sizeof(PE_ND1_VERI_REG_O26_T)))
			{
				*((UINT32 *)(gPE_ND1_VERI_O26.phys.addr+((addr-PE_O26_ND1_VERI_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_SR_2K_SHP0_BASE && (addr)<(PE_O26_SR_2K_SHP0_BASE+sizeof(PE_SR_2K_SHP_REG_O26_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHP0_O26.phys.addr+((addr-PE_O26_SR_2K_SHP0_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_SR_2K_SHP1_BASE && (addr)<(PE_O26_SR_2K_SHP1_BASE+sizeof(PE_SR_2K_SHP_REG_O26_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHP1_O26.phys.addr+((addr-PE_O26_SR_2K_SHP1_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_SR_2K_SHC_BASE && (addr)<(PE_O26_SR_2K_SHC_BASE+sizeof(PE_SR_2K_SHC_REG_O26_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHC_O26.phys.addr+((addr-PE_O26_SR_2K_SHC_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_SR_MERG_BASE && (addr)<(PE_O26_SR_MERG_BASE+sizeof(PE_SR_MERG_REG_O26_T)))
			{
				*((UINT32 *)(gPE_SR_MERG_O26.phys.addr+((addr-PE_O26_SR_MERG_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_SR_BLEND_BASE && (addr)<(PE_O26_SR_BLEND_BASE+sizeof(PE_SR_BLEND_REG_O26_T)))
			{
				*((UINT32 *)(gPE_SR_BLEND_O26.phys.addr+((addr-PE_O26_SR_BLEND_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_GAV_SHP_BASE && (addr)<(PE_O26_GAV_SHP_BASE+sizeof(PE_GAV_SHP_REG_O26_T)))
			{
				*((UINT32 *)(gPE_GAV_SHP_O26.phys.addr+((addr-PE_O26_GAV_SHP_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_VSD_SHP_BASE && (addr)<(PE_O26_VSD_SHP_BASE+sizeof(PE_VSD_SHP_REG_O26_T)))
			{
				*((UINT32 *)(gPE_VSD_SHP_O26.phys.addr+((addr-PE_O26_VSD_SHP_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_OBC_BODY_BASE&& (addr)<(PE_O26_OBC_BODY_BASE+sizeof(PE_VSD_OBC_BODY_REG_O26_T)))
			{
				*((UINT32 *)(gPE_VSD_OBC_BODY_O26.phys.addr+((addr-PE_O26_OBC_BODY_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_OBC_HEAD_BASE && (addr)<(PE_O26_OBC_HEAD_BASE+sizeof(PE_VSD_OBC_HEAD_REG_O26_T)))
			{
				*((UINT32 *)(gPE_VSD_OBC_HEAD_O26.phys.addr+((addr-PE_O26_OBC_HEAD_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_AMG1_BODY_BASE&& (addr)<(PE_O26_AMG1_BODY_BASE+sizeof(PE_AMG_BODY_REG_O26_T)))
			{
				*((UINT32 *)(gPE_AMG_BODY_O26.phys.addr+((addr-PE_O26_AMG1_BODY_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_AMG0_HEAD_BASE && (addr)<(PE_O26_AMG0_HEAD_BASE+sizeof(PE_AMG_HEAD_REG_O26_T)))
			{
				*((UINT32 *)(gPE_AMG_HEAD_O26.phys.addr+((addr-PE_O26_AMG0_HEAD_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_AMG2_MTB_BASE && (addr)<(PE_O26_AMG2_MTB_BASE+sizeof(PE_AMG_MTB_REG_O26_T)))
			{
				*((UINT32 *)(gPE_AMG_MTB_O26.phys.addr+((addr-PE_O26_AMG2_MTB_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_AMG3_GRM_BASE && (addr)<(PE_O26_AMG3_GRM_BASE+sizeof(PE_AMG_GRM_REG_O26_T)))
			{
				*((UINT32 *)(gPE_AMG_GRM_O26.phys.addr+((addr-PE_O26_AMG3_GRM_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_OBE_BASE && (addr)<(PE_O26_OBE_BASE+sizeof(PE_VSD_OBE_REG_O26_T)))
			{
				*((UINT32 *)(gPE_VSD_OBE_O26.phys.addr+((addr-PE_O26_OBE_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_OSD_ORD_BASE&& (addr)<(PE_O26_OSD_ORD_BASE+sizeof(PE_OSD_ORD_REG_O26_T)))
			{
				*((UINT32 *)(gPE_OSD_ORD_O26.phys.addr+((addr-PE_O26_OSD_ORD_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_DTM_BASE && (addr)<(PE_O26_DTM_BASE+sizeof(PE_VSD_DTM_REG_O26_T)))
			{
				*((UINT32 *)(gPE_VSD_DTM_O26.phys.addr+((addr-PE_O26_DTM_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_LOC_BASE && (addr)<(PE_O26_LOC_BASE+sizeof(PE_LOC_REG_O26_T)))
			{
				*((UINT32 *)(gPE_LOC_O26.phys.addr+((addr-PE_O26_LOC_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_IMX_BASE && (addr)<(PE_O26_IMX_BASE+sizeof(PE_TOP_IMX_REG_O26_T)))
			{
				*((UINT32 *)(gPE_TOP_IMX_O26.phys.addr+((addr-PE_O26_IMX_BASE)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O26_CCO_DEC_BASE && (addr)<(PE_O26_CCO_DEC_BASE+sizeof(PE_CCO_DECON_REG_O26_T)))
			{
				*((UINT32 *)(gPE_CCO_DCNT_O26.phys.addr+((addr-PE_O26_CCO_DEC_BASE)/sizeof(UINT32)))) = value;
			}
			else
			{
				PE_PRINT_NOTI("[%x]not support(0x%04x, 0x%08x)\n",PE_CHIP_VER,(addr),(value));
			}
		}
		else
		{
			PE_PRINT_NOTI("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * PE_REG_O26_GetDispOpt
 * see PE_REG_O26_HW_OPT_T
 *
 * @param   void
 * @return  UINT32
 * @see
 * @author
 */
PE_REG_O26_HW_OPT_T PE_REG_O26_GetDispOpt(void)
{
	return _g_pe_reg_o26_disp_opt;
}

