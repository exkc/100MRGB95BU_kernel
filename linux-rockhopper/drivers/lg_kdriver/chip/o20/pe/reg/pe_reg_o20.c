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

/** @file pe_reg_o20.c
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

#include "pe_hw_o20.h"
#include "pe_reg_o20.h"
#include "pe_inf_o20.h"
#include "pe_hdr_ddr_o20.h"

#ifdef INCLUDE_KDRV_BE
#include "be_cfg.h"
#include "ovi_hal.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_REG_O20_CHECK_CODE(_checker,_action,fmt,args...)		\
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
PE_CE_PE1_REG_TYPE_O20_T   	  gPE_CE_PE1_O20;
PE_CO_PE1_REG_TYPE_O20_T   	  gPE_CO_PE1_O20;
PE_CE2_PE1_REG_TYPE_O20_T     gPE_CE2_PE1_O20;
PE_CO2_PE1_REG_TYPE_O20_T     gPE_CO2_PE1_O20;
PE_CVI_REG_TYPE_O20_T      	  gPE_CVI_A_O20;
PE_CVI_REG_TYPE_O20_T      	  gPE_CVI_B_O20;
PE_CVI_REG_TYPE_O20_T      	  gPE_CVI_C_O20;
PE_CVI_REG_TYPE_O20_T      	  gPE_CVI_D_O20;
PE_LED_RP_REG_TYPE_O20_T   	  gPE_LED_RP_O20;
PE_LED_DCNT_REG_TYPE_O20_T    gPE_LED_DCNT_O20;
PE_GSC_Y_REG_TYPE_O20_T    	  gPE_GSC_Y_O20;
PE_GSC_C_REG_TYPE_O20_T    	  gPE_GSC_C_O20;
PE_ND_ND0_REG_TYPE_O20_T   	  gPE_ND_ND0_O20;
PE_ND_DNR0_REG_TYPE_O20_T  	  gPE_ND_DNR0_O20;
PE_ND_ND0_REG_TYPE_O20_T   	  gPE_ND_ND1_O20;
PE_ND_DNR0_REG_TYPE_O20_T  	  gPE_ND_DNR1_O20;
PE_ND_OBC_O_REG_TYPE_O20_T    gPE_ND_OBC_O_O20;
PE_ND_OBC_F_REG_TYPE_O20_T    gPE_ND_OBC_F_O20;
PE_SHP_REG_TYPE_O20_T     	  gPE_SHP_O20;
PE_VSD_OBC_O_REG_TYPE_O20_T	  gPE_VSD_OBC_O_O20;
PE_VSD_OBC_F_REG_TYPE_O20_T	  gPE_VSD_OBC_F_O20;
PE_VSD_RCE_O_REG_TYPE_O20_T	  gPE_VSD_RCE_O_O20;
PE_VSD_RCE_F_REG_TYPE_O20_T	  gPE_VSD_RCE_F_O20;
PE_VSD_DTM_REG_TYPE_O20_T	  gPE_VSD_DTM_O20;
PE_SHP_OSD0_REG_TYPE_O20_T     	  gPE_SHP_OSD0_O20;
PE_SHP_OSD1_REG_TYPE_O20_T     	  gPE_SHP_OSD1_O20;
PE_SR_CHR_SHP_REG_TYPE_O20_T  gPE_SR_CHR_SHP_O20;
PE_SR_2K_SHP_REG_TYPE_O20_T   gPE_SR_2K_SHP_O20;
PE_SR_MERG_REG_TYPE_O20_T   gPE_SR_MERG_O20;
PE_VCP_DISP_REG_TYPE_O20_T 	  gPE_VCP_DISP_O20;
PE_VSD_VERI_REG_TYPE_O20_T 	  gPE_VSD_VERI_O20;
PE_TOP_IMX_REG_TYPE_O20_T  	  gPE_TOP_IMX_O20;
PE_DDR_DB_REG_TYPE_O20_T      gPE_DDR_DB_O20;
PE_DDR_DB_REG_TYPE_F20_T      gPE_DDR_DB_F20;
PE_LGSR_DDR_DB_REG_TYPE_O20_T      gPE_LGSR_DDR_DB_O20;
PE_LGSR_DDR_DB_REG_TYPE_F20_T      gPE_LGSR_DDR_DB_F20;
volatile UINT32			 	*gpe_vsd_ctrl_block_o20;

PE_HDR_REG_O20_H10_T     gPE_H10_E_O20;
PE_HDR_REG_O20_H10_T     gPE_H10_O_O20;
PE_HDR_REG_O20_H10_P_T   gPE_H10_P_O20;
PE_HDR_REG_O20_S2H_T     gPE_S2H_E_O20;
PE_HDR_REG_O20_S2H_T     gPE_S2H_O_O20;
PE_HDR_REG_O20_GAV_T     gPE_GAV_O20;
volatile UINT32          *gPE_HDR_DDR_O20;
PE_MCU_REG_TYPE_O20_T  	  	  gPE_MCU_O20;
PE_CCO_VERI_REG_TYPE_O20_T    gPE_CCO_VERI_O20;
PE_ND_ND0_VERI_REG_TYPE_O20_T gPE_ND_ND0_VERI_O20;

PE_CHPI_REG_TYPE_F20_T gPE_CHPI_APB0_F20;
PE_CHPI_REG_TYPE_F20_T gPE_CHPI_APB1_F20;//causion : shdw not used(null)
PE_CHPI_TBL0_TYPE_F20_T gPE_CHPI_TBL0_F20;
PE_CHPI_TBL0_TYPE_F20_T gPE_CHPI_TBL1_F20;//causion : shdw not used(null)
volatile UINT32 *gPE_CHPI_DDR;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_REG_O20_HW_OPT_T _g_pe_reg_o20_disp_opt;

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef INCLUDE_KDRV_BE
static int PE_REG_O20_GetHwOpt(UINT32 *opt)
{
	PE_REG_O20_HW_OPT_T panel_mode;
	LX_OVI_HW_DISPLAY_INFO_T ovi_opt;
	int ret = RET_OK;

	panel_mode.u32Data = 0;

	ret = OVI_HAL_GetHWDisplayOption(&ovi_opt);
	if (ret == RET_OK)
	{
		if (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ)
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

		if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
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
	PE_INF_HW_O20_BACKUP_TRACE("[Opt]fr:%d,pt:%d,vx1:%d,ext%d,pr:%d",panel_mode.panel_frame_rate,\
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
int PE_REG_O20_InitPhyToVirt(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	if(PE_KDRV_VER_O20)
	{
		/* shdw */
		gPE_CVI_A_O20.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O20_T));
		gPE_CVI_B_O20.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O20_T));
		gPE_CVI_C_O20.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O20_T));
		gPE_CVI_D_O20.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O20_T));
		gPE_LED_RP_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_LED_RP_REG_O20_T));
		gPE_TOP_IMX_O20.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_TOP_IMX_REG_O20_T));
		gPE_GSC_Y_O20.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_Y_REG_O20_T));
		gPE_GSC_C_O20.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_C_REG_O20_T));
		gPE_ND_ND0_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_REG_O20_T));/*ND0 equal to ND1 */
		gPE_ND_DNR0_O20.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR0_REG_O20_T));/*DNR0 equal to DNR1 */
		gPE_ND_ND1_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_REG_O20_T));
		gPE_ND_DNR1_O20.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR0_REG_O20_T));
		gPE_ND_OBC_O_O20.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_DNR0_OBC_OBJT_REG_O20_T));
		gPE_ND_OBC_F_O20.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_DNR0_OBC_FACE_REG_O20_T));
		gPE_VCP_DISP_O20.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DISP_REG_O20_T));
		gPE_VSD_VERI_O20.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_VSD_VERI_REG_O20_T));
		gPE_SHP_O20.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_SHP_REG_O20_T));
		gPE_VSD_OBC_O_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBC_OBJT_REG_O20_T));
		gPE_VSD_OBC_F_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_OBC_FACE_REG_O20_T));
		gPE_VSD_RCE_O_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_RCE_OBJT_REG_O20_T));
		gPE_VSD_RCE_F_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_RCE_FACE_REG_O20_T));
		gPE_VSD_DTM_O20.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_DTM_REG_O20_T));
		gPE_SHP_OSD0_O20.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_SHP_OSD0_REG_O20_T));
		gPE_SHP_OSD1_O20.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_SHP_OSD1_REG_O20_T));
		gPE_SR_CHR_SHP_O20.shdw.addr= (UINT32 *)OS_KMalloc(sizeof(PE_SR_CHR_SHP_REG_O20_T));
		gPE_SR_2K_SHP_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHP_REG_O20_T));
		gPE_SR_MERG_O20.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_MERG_REG_O20_T));
		gPE_CE_PE1_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CE_PE1_REG_O20_T));
		gPE_CO_PE1_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CO_PE1_REG_O20_T));
		gPE_CE2_PE1_O20.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_CE2_PE1_REG_O20_T));
		gPE_CO2_PE1_O20.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_CO2_PE1_REG_O20_T));

		gPE_DDR_DB_O20.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O20_T));
		gPE_DDR_DB_F20.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_F20_T));
		gPE_LGSR_DDR_DB_O20.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O20_T));
		gPE_LGSR_DDR_DB_F20.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_F20_T));
		gPE_LED_DCNT_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_LED_DCNT_REG_O20_T));

		gPE_H10_E_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_O20_REG_H10_T));
		gPE_H10_O_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_O20_REG_H10_T));
		gPE_H10_P_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_O20_REG_H10_P_T));
		gPE_S2H_E_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_O20_REG_S2H_T));
		gPE_S2H_O_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_O20_REG_S2H_T));
		gPE_GAV_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_O20_REG_GAV_T));
		gPE_MCU_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_MCU_REG_O20_T));
		gPE_CCO_VERI_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CCO_VERI_REG_O20_T));
		gPE_ND_ND0_VERI_O20.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_VERI_REG_O20_T));/*ND0 equal to ND1 */

		gPE_CHPI_APB0_F20.shdw.addr	= (UINT32 *)OS_KMalloc(sizeof(PE_CHPI_REG_F20_T));
		gPE_CHPI_TBL0_F20.shdw.addr	= (UINT32 *)OS_KMalloc(sizeof(PE_CHPI_TBL0_F20_T));

		/* phys */
		gPE_CVI_A_O20.phys.addr    	= (volatile UINT32 *)ioremap(PE_O20_CVI_A_BASE,    sizeof(PE_CVI_REG_O20_T));
		gPE_CVI_B_O20.phys.addr    	= (volatile UINT32 *)ioremap(PE_O20_CVI_B_BASE,    sizeof(PE_CVI_REG_O20_T));
		gPE_CVI_C_O20.phys.addr    	= (volatile UINT32 *)ioremap(PE_O20_CVI_C_BASE,    sizeof(PE_CVI_REG_O20_T));
		gPE_CVI_D_O20.phys.addr    	= (volatile UINT32 *)ioremap(PE_O20_CVI_D_BASE,    sizeof(PE_CVI_REG_O20_T));
		gPE_LED_RP_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_LED_RP_BASE,   sizeof(PE_LED_RP_REG_O20_T));
		gPE_TOP_IMX_O20.phys.addr  	= (volatile UINT32 *)ioremap(PE_O20_IMX_BASE,      sizeof(PE_TOP_IMX_REG_O20_T));
		gPE_GSC_Y_O20.phys.addr    	= (volatile UINT32 *)ioremap(PE_O20_GSC_Y_BASE,    sizeof(PE_GSC_Y_REG_O20_T));
		gPE_GSC_C_O20.phys.addr    	= (volatile UINT32 *)ioremap(PE_O20_GSC_C_BASE,    sizeof(PE_GSC_C_REG_O20_T));
		gPE_ND_ND0_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_ND0_BASE,      sizeof(PE_ND_ND0_REG_O20_T));
		gPE_ND_DNR0_O20.phys.addr  	= (volatile UINT32 *)ioremap(PE_O20_DNR0_BASE,     sizeof(PE_ND_DNR0_REG_O20_T));;
		gPE_ND_ND1_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_ND1_BASE,      sizeof(PE_ND_ND0_REG_O20_T));
		gPE_ND_DNR1_O20.phys.addr  	= (volatile UINT32 *)ioremap(PE_O20_DNR1_BASE,     sizeof(PE_ND_DNR0_REG_O20_T));
		gPE_ND_OBC_O_O20.phys.addr  	= (volatile UINT32 *)ioremap(PE_O20_ND_OBC_O_BASE,     sizeof(PE_DNR0_OBC_OBJT_REG_O20_T));
		gPE_ND_OBC_F_O20.phys.addr  	= (volatile UINT32 *)ioremap(PE_O20_ND_OBC_F_BASE,     sizeof(PE_DNR0_OBC_FACE_REG_O20_T));
		gPE_VCP_DISP_O20.phys.addr 	= (volatile UINT32 *)ioremap(PE_O20_VCP_DISP_BASE, sizeof(PE_VCP_DISP_REG_O20_T));
		gPE_VSD_VERI_O20.phys.addr 	= (volatile UINT32 *)ioremap(PE_O20_VSD_VERI_BASE, sizeof(PE_VSD_VERI_REG_O20_T));
		gPE_SHP_O20.phys.addr     	= (volatile UINT32 *)ioremap(PE_O20_P1_SHP_L_BASE, sizeof(PE_SHP_REG_O20_T));
		gPE_VSD_OBC_O_O20.phys.addr   = (volatile UINT32 *)ioremap(PE_O20_P1_VSD_OBC_O_BASE, sizeof(PE_VSD_OBC_OBJT_REG_O20_T));
		gPE_VSD_OBC_F_O20.phys.addr   = (volatile UINT32 *)ioremap(PE_O20_P1_VSD_OBC_F_BASE, sizeof(PE_VSD_OBC_FACE_REG_O20_T));
		gPE_VSD_RCE_O_O20.phys.addr   = (volatile UINT32 *)ioremap(PE_O20_P1_VSD_RCE_O_BASE, sizeof(PE_VSD_RCE_OBJT_REG_O20_T));
		gPE_VSD_RCE_F_O20.phys.addr   = (volatile UINT32 *)ioremap(PE_O20_P1_VSD_RCE_F_BASE, sizeof(PE_VSD_RCE_FACE_REG_O20_T));
		gPE_VSD_DTM_O20.phys.addr     = (volatile UINT32 *)ioremap(PE_O20_P1_VSD_DTM_BASE, sizeof(PE_VSD_DTM_REG_O20_T));
		gPE_SHP_OSD0_O20.phys.addr     	= (volatile UINT32 *)ioremap(PE_O20_P1_SHP_OSD0_BASE, sizeof(PE_SHP_OSD0_REG_O20_T));
		gPE_SHP_OSD1_O20.phys.addr     	= (volatile UINT32 *)ioremap(PE_O20_P1_SHP_OSD1_BASE, sizeof(PE_SHP_OSD1_REG_O20_T));
		gPE_SR_CHR_SHP_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_SR_CHR_SHP_BASE,   sizeof(PE_SR_CHR_SHP_REG_O20_T));
		gPE_SR_2K_SHP_O20 .phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_SR_2K_SHP_BASE,   sizeof(PE_SR_2K_SHP_REG_O20_T));
		gPE_SR_MERG_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_SR_MERG_BASE,   sizeof(PE_SR_MERG_REG_O20_T));
		gPE_CE_PE1_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_P1_CCO_E_BASE, sizeof(PE_CE_PE1_REG_O20_T));
		gPE_CO_PE1_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_P1_CCO_O_BASE, sizeof(PE_CO_PE1_REG_O20_T));
		gPE_CE2_PE1_O20.phys.addr   = (volatile UINT32 *)ioremap(PE_O20_P1_CCO2_E_BASE, sizeof(PE_CE2_PE1_REG_O20_T));
		gPE_CO2_PE1_O20.phys.addr   = (volatile UINT32 *)ioremap(PE_O20_P1_CCO2_O_BASE, sizeof(PE_CO2_PE1_REG_O20_T));

		gpe_vsd_ctrl_block_o20    	= (volatile UINT32 *)ioremap(PE_O20_VSD_BASE,    sizeof(UINT32));
		gPE_LED_DCNT_O20.phys.addr  = (volatile UINT32 *)ioremap(PE_O20_LED_DCNT_BASE,   sizeof(PE_LED_DCNT_REG_O20_T));

		gPE_H10_E_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_H10_E_BASE,sizeof(PE_O20_REG_H10_T));
		gPE_H10_O_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_H10_O_BASE,sizeof(PE_O20_REG_H10_T));
		gPE_H10_P_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_H10_P_BASE,sizeof(PE_O20_REG_H10_P_T));
		gPE_S2H_E_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_S2H_E_BASE,sizeof(PE_O20_REG_S2H_T));
		gPE_S2H_O_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_S2H_O_BASE,sizeof(PE_O20_REG_S2H_T));
		gPE_GAV_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_GAV_BASE,sizeof(PE_O20_REG_GAV_T));
		gPE_HDR_DDR_O20				= (volatile UINT32 *)vmap_phys(PE_HDR_DDR_O20_BASE_ADDR,PE_HDR_DDR_O20_TOTAL_SIZE+PAGE_SIZE);
		gPE_DDR_DB_O20.phys.addr    = (volatile UINT32 *)vmap_phys(PE_O20_DDR_DB0_BASE,sizeof(PE_DDR_DB_PHYS_REG_O20_T)+PAGE_SIZE);
		gPE_DDR_DB_F20.phys.addr    = (volatile UINT32 *)vmap_phys(PE_F20_DDR_BASE,sizeof(PE_DDR_DB_PHYS_REG_F20_T)+PAGE_SIZE);
		gPE_LGSR_DDR_DB_O20.phys.addr    = (volatile UINT32 *)vmap_phys(PE_LGSR_DDR_O20_BASE_ADDR,sizeof(PE_LGSR_DDR_DB_PHYS_REG_O20_T)+PAGE_SIZE);
		gPE_LGSR_DDR_DB_F20.phys.addr    = (volatile UINT32 *)vmap_phys(PE_LGSR_DDR_F20_BASE_ADDR,sizeof(PE_LGSR_DDR_DB_PHYS_REG_F20_T)+PAGE_SIZE);

		gPE_MCU_O20.phys.addr   	= (volatile UINT32 *)ioremap(PE_O20_MCU_BASE,      sizeof(PE_MCU_REG_O20_T));
		gPE_CCO_VERI_O20.phys.addr = (volatile UINT32 *)ioremap(PE_O20_CCO_VERI_BASE,      sizeof(PE_CCO_VERI_REG_O20_T));
		gPE_ND_ND0_VERI_O20.phys.addr   = (volatile UINT32 *)ioremap(PE_O20_ND0_VERI_BASE,      sizeof(PE_ND_ND0_VERI_REG_O20_T));

		do {
			UINT32 chpi_base = 0, chpi_size = 0;
			UINT32 apb_s[4],apb_e[4],st_size[3],max_size[3];
			#if 1
			_g_pe_reg_o20_disp_opt.u32Data = 0;
			#ifdef PQE_NEW_MAP
			chpi_base = g_chipinfo.base;
			chpi_size = g_chipinfo.size;
			#else
			#ifdef INCLUDE_KDRV_BE
			chpi_base = gpBeChInfMem->frame_base;
			chpi_size = gpBeChInfMem->frame_size;
			#endif
			#endif
			#ifdef INCLUDE_KDRV_BE
			ret = PE_REG_O20_GetHwOpt(&(_g_pe_reg_o20_disp_opt.u32Data));
			#endif
			if (chpi_base==0)	break;
			if (chpi_size==0)	break;
			gPE_CHPI_DDR = (volatile UINT32 *)vmap_phys(chpi_base,chpi_size);
			gPE_CHPI_APB0_F20.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR + (PE_CHPI_APB0_F20_S_OFST0>>2));//buf[1]
			gPE_CHPI_APB1_F20.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR + (PE_CHPI_APB1_F20_S_OFST0>>2));//buf[4]
			gPE_CHPI_TBL0_F20.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR + (PE_CHPI_TBL0_F20_S_OFST0>>2));//buf[2]
			gPE_CHPI_TBL1_F20.phys.addr = (volatile UINT32 *)(gPE_CHPI_DDR + (PE_CHPI_TBL1_F20_S_OFST0>>2));//buf[5]
			PE_PRINT_NOTI("[CHI]0x%08x,0x%08x,0x%p\n",chpi_base,chpi_size,gPE_CHPI_DDR);
			PE_PRINT_NOTI("[CHI]apb:0x%p,0x%p\n",gPE_CHPI_APB0_F20.phys.addr,gPE_CHPI_APB1_F20.phys.addr);
			PE_PRINT_NOTI("[CHI]tbl:0x%p,0x%p\n",gPE_CHPI_TBL0_F20.phys.addr,gPE_CHPI_TBL1_F20.phys.addr);
			PE_INF_HW_O20_BACKUP_TRACE("[CHI]0x%08x,0x%08x,0x%p",chpi_base,chpi_size,gPE_CHPI_DDR);
			#endif

			/* info apb */
			apb_s[0] = (chpi_base+PE_CHPI_APB0_F20_S_OFST0);
			apb_e[0] = (chpi_base+PE_CHPI_APB0_F20_E_OFST0);
			apb_s[1] = (chpi_base+PE_CHPI_APB0_F20_S_OFST1);
			apb_e[1] = (chpi_base+PE_CHPI_APB0_F20_E_OFST1);
			apb_s[2] = (chpi_base+PE_CHPI_APB1_F20_S_OFST0);
			apb_e[2] = (chpi_base+PE_CHPI_APB1_F20_E_OFST0);
			apb_s[3] = (chpi_base+PE_CHPI_APB1_F20_S_OFST1);
			apb_e[3] = (chpi_base+PE_CHPI_APB1_F20_E_OFST1);
			st_size[0] = sizeof(PE_CHPI_REG0_F20_T);
			st_size[1] = sizeof(PE_CHPI_REG1_F20_T);
			st_size[2] = sizeof(PE_CHPI_REG_F20_T);
			max_size[0] = PE_CHPI_APB_F20_SIZE0;
			max_size[1] = PE_CHPI_APB_F20_SIZE1;
			max_size[2] = PE_CHPI_APB_F20_TOTAL;
			PE_PRINT_NOTI("[CHI]apb:0x%08x,0x%08x|0x%08x,0x%08x|0x%08x,0x%08x|0x%08x,0x%08x\n",apb_s[0],apb_e[0],apb_s[1],apb_e[1],apb_s[2],apb_e[2],apb_s[3],apb_e[3]);
			PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[0],max_size[0],max_size[0]-st_size[0],(max_size[0]-st_size[0])>>2);
			PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[1],max_size[1],max_size[1]-st_size[1],(max_size[1]-st_size[1])>>2);
			PE_PRINT_NOTI("[CHI]apb:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[2],max_size[2],max_size[2]-st_size[2],(max_size[2]-st_size[2])>>2);
			PE_INF_HW_O20_BACKUP_CHPI0("[CHI]apb:0x%08x,0x%08x|0x%08x,0x%08x|0x%08x,0x%08x|0x%08x,0x%08x",apb_s[0],apb_e[0],apb_s[1],apb_e[1],apb_s[2],apb_e[2],apb_s[3],apb_e[3]);
			/* info tbl */
			apb_s[0] = (chpi_base+PE_CHPI_TBL0_F20_S_OFST0);
			apb_e[0] = (chpi_base+PE_CHPI_TBL0_F20_E_OFST0);
			apb_s[1] = (chpi_base+PE_CHPI_TBL1_F20_S_OFST0);
			apb_e[1] = (chpi_base+PE_CHPI_TBL1_F20_E_OFST0);
			st_size[0] = sizeof(PE_CHPI_TBL0_F20_T);
			max_size[0] = PE_CHPI_TBL_F20_TOTAL;
			PE_PRINT_NOTI("[CHI]tbl:0x%08x,0x%08x|0x%08x,0x%08x\n",apb_s[0],apb_e[0],apb_s[1],apb_e[1]);
			PE_PRINT_NOTI("[CHI]tbl:%5d(max:%5d),diff:%d(u32:%d)\n",st_size[0],max_size[0],max_size[0]-st_size[0],(max_size[0]-st_size[0])>>2);
			PE_INF_HW_O20_BACKUP_CHPI1("[CHI]tbl:0x%08x,0x%08x|0x%08x,0x%08x",apb_s[0],apb_e[0],apb_s[1],apb_e[1]);

		} while(0);

		PE_PRINT_NOTI("[HDR]v(%d), vmap base:0x%08x,size:0x%08x+0x%08x\n",\
			PE_HDR_DDR_O20_VERSION,PE_HDR_DDR_O20_BASE_ADDR,PE_HDR_DDR_O20_TOTAL_SIZE,(UINT32)PAGE_SIZE);
		PE_PRINT_NOTI("[PE]vmap base:0x%08x,size:0x%08x+0x%08x\n",\
			PE_O20_DDR_DB0_BASE,(UINT32)sizeof(PE_DDR_DB_PHYS_REG_O20_T),(UINT32)PAGE_SIZE);
		PE_PRINT_NOTI("[PE]vmap base:0x%08x,size:0x%08x+0x%08x\n",\
			PE_LGSR_DDR_O20_BASE_ADDR,(UINT32)sizeof(PE_LGSR_DDR_DB_PHYS_REG_O20_T),(UINT32)PAGE_SIZE);
	}
	else
	{
		PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
	}
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_REG_O20_FreePhyToVirt(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	if(PE_KDRV_VER_O20)
	{
		/* shdw */
		if (gPE_CVI_A_O20.shdw.addr   ) OS_Free((void *)gPE_CVI_A_O20.shdw.addr   );
		if (gPE_CVI_B_O20.shdw.addr   ) OS_Free((void *)gPE_CVI_B_O20.shdw.addr   );
		if (gPE_CVI_C_O20.shdw.addr   ) OS_Free((void *)gPE_CVI_C_O20.shdw.addr   );
		if (gPE_CVI_D_O20.shdw.addr   ) OS_Free((void *)gPE_CVI_D_O20.shdw.addr   );
		//if (gPE_HDMI_A_O20.shdw.addr  ) OS_Free((void *)gPE_HDMI_A_O20.shdw.addr  );
		//if (gPE_HDMI_B_O20.shdw.addr  ) OS_Free((void *)gPE_HDMI_B_O20.shdw.addr  );
		//if (gPE_HDMI_C_O20.shdw.addr  ) OS_Free((void *)gPE_HDMI_C_O20.shdw.addr  );
		//if (gPE_HDMI_D_O20.shdw.addr  ) OS_Free((void *)gPE_HDMI_D_O20.shdw.addr  );
		if (gPE_LED_RP_O20.shdw.addr  ) OS_Free((void *)gPE_LED_RP_O20.shdw.addr  );
		if (gPE_TOP_IMX_O20.shdw.addr ) OS_Free((void *)gPE_TOP_IMX_O20.shdw.addr );
		if (gPE_GSC_Y_O20.shdw.addr   ) OS_Free((void *)gPE_GSC_Y_O20.shdw.addr   );
		if (gPE_GSC_C_O20.shdw.addr   ) OS_Free((void *)gPE_GSC_C_O20.shdw.addr   );
		if (gPE_ND_ND0_O20.shdw.addr  ) OS_Free((void *)gPE_ND_ND0_O20.shdw.addr  );
		if (gPE_ND_DNR0_O20.shdw.addr ) OS_Free((void *)gPE_ND_DNR0_O20.shdw.addr );
		if (gPE_ND_ND1_O20.shdw.addr  ) OS_Free((void *)gPE_ND_ND1_O20.shdw.addr  );
		if (gPE_ND_DNR1_O20.shdw.addr ) OS_Free((void *)gPE_ND_DNR1_O20.shdw.addr );
		if (gPE_ND_OBC_O_O20.shdw.addr )  OS_Free((void *)gPE_ND_OBC_O_O20.shdw.addr );
		if (gPE_ND_OBC_F_O20.shdw.addr )  OS_Free((void *)gPE_ND_OBC_F_O20.shdw.addr );
		if (gPE_VCP_DISP_O20.shdw.addr) OS_Free((void *)gPE_VCP_DISP_O20.shdw.addr);
		if (gPE_VSD_VERI_O20.shdw.addr) OS_Free((void *)gPE_VSD_VERI_O20.shdw.addr);
		if (gPE_SHP_O20.shdw.addr    ) OS_Free((void *)gPE_SHP_O20.shdw.addr    );
		if (gPE_VSD_OBC_O_O20.shdw.addr    ) OS_Free((void *)gPE_VSD_OBC_O_O20.shdw.addr    );
		if (gPE_VSD_OBC_F_O20.shdw.addr    ) OS_Free((void *)gPE_VSD_OBC_F_O20.shdw.addr    );
		if (gPE_SHP_OSD0_O20.shdw.addr    ) OS_Free((void *)gPE_SHP_OSD0_O20.shdw.addr    );
		if (gPE_SHP_OSD1_O20.shdw.addr    ) OS_Free((void *)gPE_SHP_OSD1_O20.shdw.addr    );
		if (gPE_SR_CHR_SHP_O20.shdw.addr    ) OS_Free((void *)gPE_SR_CHR_SHP_O20.shdw.addr);
		if (gPE_SR_2K_SHP_O20.shdw.addr    ) OS_Free((void *)gPE_SR_2K_SHP_O20.shdw.addr  );
		if (gPE_SR_MERG_O20.shdw.addr    ) OS_Free((void *)gPE_SR_MERG_O20.shdw.addr  );
		if (gPE_CE_PE1_O20.shdw.addr  ) OS_Free((void *)gPE_CE_PE1_O20.shdw.addr  );
		if (gPE_CO_PE1_O20.shdw.addr  ) OS_Free((void *)gPE_CO_PE1_O20.shdw.addr  );
		if (gPE_CE2_PE1_O20.shdw.addr  ) OS_Free((void *)gPE_CE2_PE1_O20.shdw.addr  );
		if (gPE_CO2_PE1_O20.shdw.addr  ) OS_Free((void *)gPE_CO2_PE1_O20.shdw.addr  );
		if (gPE_DDR_DB_O20.shdw.addr    ) OS_Free((void *)gPE_DDR_DB_O20.shdw.addr    );
		if (gPE_DDR_DB_F20.shdw.addr    ) OS_Free((void *)gPE_DDR_DB_F20.shdw.addr    );
		if (gPE_LGSR_DDR_DB_O20.shdw.addr    ) OS_Free((void *)gPE_LGSR_DDR_DB_O20.shdw.addr    );
		if (gPE_LGSR_DDR_DB_F20.shdw.addr    ) OS_Free((void *)gPE_LGSR_DDR_DB_F20.shdw.addr    );

		if (gPE_LED_DCNT_O20.shdw.addr  ) OS_Free((void *)gPE_LED_DCNT_O20.shdw.addr  );

		if (gPE_H10_E_O20.shdw.addr) OS_Free((void *)gPE_H10_E_O20.shdw.addr);
		if (gPE_H10_O_O20.shdw.addr) OS_Free((void *)gPE_H10_O_O20.shdw.addr);
		if (gPE_H10_P_O20.shdw.addr) OS_Free((void *)gPE_H10_P_O20.shdw.addr);
		if (gPE_S2H_E_O20.shdw.addr) OS_Free((void *)gPE_S2H_E_O20.shdw.addr);
		if (gPE_S2H_O_O20.shdw.addr) OS_Free((void *)gPE_S2H_O_O20.shdw.addr);
		if (gPE_GAV_O20.shdw.addr) OS_Free((void *)gPE_GAV_O20.shdw.addr);
		if (gPE_MCU_O20.shdw.addr) OS_Free((void *)gPE_MCU_O20.shdw.addr);
		if (gPE_CCO_VERI_O20.shdw.addr) OS_Free((void *)gPE_CCO_VERI_O20.shdw.addr);
		if (gPE_ND_ND0_VERI_O20.shdw.addr  ) OS_Free((void *)gPE_ND_ND0_VERI_O20.shdw.addr  );

		if (gPE_CHPI_APB0_F20.shdw.addr) OS_Free((void *)gPE_CHPI_APB0_F20.shdw.addr);
		if (gPE_CHPI_TBL0_F20.shdw.addr) OS_Free((void *)gPE_CHPI_TBL0_F20.shdw.addr);

		/* phys */
		if (gPE_CE_PE1_O20.phys.addr  ) iounmap((void *)gPE_CE_PE1_O20.phys.addr  );
		if (gPE_CO_PE1_O20.phys.addr  ) iounmap((void *)gPE_CO_PE1_O20.phys.addr  );
		if (gPE_CE2_PE1_O20.phys.addr  ) iounmap((void *)gPE_CE2_PE1_O20.phys.addr  );
		if (gPE_CO2_PE1_O20.phys.addr  ) iounmap((void *)gPE_CO2_PE1_O20.phys.addr  );
		if (gPE_CVI_A_O20.phys.addr   ) iounmap((void *)gPE_CVI_A_O20.phys.addr   );
		if (gPE_CVI_B_O20.phys.addr   ) iounmap((void *)gPE_CVI_B_O20.phys.addr   );
		if (gPE_CVI_C_O20.phys.addr   ) iounmap((void *)gPE_CVI_C_O20.phys.addr   );
		if (gPE_CVI_D_O20.phys.addr   ) iounmap((void *)gPE_CVI_D_O20.phys.addr   );
		if (gPE_LED_RP_O20.phys.addr  ) iounmap((void *)gPE_LED_RP_O20.phys.addr  );
		if (gPE_VCP_DISP_O20.phys.addr) iounmap((void *)gPE_VCP_DISP_O20.phys.addr);
		if (gPE_VSD_VERI_O20.phys.addr) iounmap((void *)gPE_VSD_VERI_O20.phys.addr);
		if (gPE_TOP_IMX_O20.phys.addr ) iounmap((void *)gPE_TOP_IMX_O20.phys.addr );
		//if (gPE_HDMI_A_O20.phys.addr  ) iounmap((void *)gPE_HDMI_A_O20.phys.addr  );
		//if (gPE_HDMI_B_O20.phys.addr  ) iounmap((void *)gPE_HDMI_B_O20.phys.addr  );
		//if (gPE_HDMI_C_O20.phys.addr  ) iounmap((void *)gPE_HDMI_C_O20.phys.addr  );
		//if (gPE_HDMI_D_O20.phys.addr  ) iounmap((void *)gPE_HDMI_D_O20.phys.addr  );
		if (gPE_GSC_Y_O20.phys.addr   ) iounmap((void *)gPE_GSC_Y_O20.phys.addr   );
		if (gPE_GSC_C_O20.phys.addr   ) iounmap((void *)gPE_GSC_C_O20.phys.addr   );
		if (gPE_ND_ND0_O20.phys.addr  ) iounmap((void *)gPE_ND_ND0_O20.phys.addr  );
		if (gPE_ND_DNR0_O20.phys.addr ) iounmap((void *)gPE_ND_DNR0_O20.phys.addr );
		if (gPE_ND_ND1_O20.phys.addr  ) iounmap((void *)gPE_ND_ND1_O20.phys.addr  );
		if (gPE_ND_DNR1_O20.phys.addr ) iounmap((void *)gPE_ND_DNR1_O20.phys.addr );
		if (gPE_ND_OBC_O_O20.phys.addr ) iounmap((void *)gPE_ND_OBC_O_O20.phys.addr );
		if (gPE_ND_OBC_F_O20.phys.addr ) iounmap((void *)gPE_ND_OBC_F_O20.phys.addr );
		if (gPE_SHP_O20.phys.addr     ) iounmap((void *)gPE_SHP_O20.phys.addr     );
		if (gPE_VSD_OBC_O_O20.phys.addr ) iounmap((void *)gPE_VSD_OBC_O_O20.phys.addr );
		if (gPE_VSD_OBC_F_O20.phys.addr ) iounmap((void *)gPE_VSD_OBC_F_O20.phys.addr );
		if (gPE_SHP_OSD0_O20.phys.addr     ) iounmap((void *)gPE_SHP_OSD0_O20.phys.addr     );
		if (gPE_SHP_OSD1_O20.phys.addr     ) iounmap((void *)gPE_SHP_OSD1_O20.phys.addr     );
		if (gPE_SR_CHR_SHP_O20.phys.addr  ) iounmap((void *)gPE_SR_CHR_SHP_O20.phys.addr);
		if (gPE_SR_2K_SHP_O20.phys.addr  ) iounmap((void *)gPE_SR_2K_SHP_O20.phys.addr  );
		if (gPE_SR_MERG_O20.phys.addr  ) iounmap((void *)gPE_SR_MERG_O20.phys.addr  );

		if (gpe_vsd_ctrl_block_o20) 	iounmap((void *)gpe_vsd_ctrl_block_o20);
		if (gPE_LED_DCNT_O20.phys.addr  ) iounmap((void *)gPE_LED_DCNT_O20.phys.addr  );

		if (gPE_H10_E_O20.phys.addr) iounmap((void *)gPE_H10_E_O20.phys.addr);
		if (gPE_H10_O_O20.phys.addr) iounmap((void *)gPE_H10_O_O20.phys.addr);
		if (gPE_H10_P_O20.phys.addr) iounmap((void *)gPE_H10_P_O20.phys.addr);
		if (gPE_S2H_E_O20.phys.addr) iounmap((void *)gPE_S2H_E_O20.phys.addr);
		if (gPE_S2H_O_O20.phys.addr) iounmap((void *)gPE_S2H_O_O20.phys.addr);
		if (gPE_GAV_O20.phys.addr) iounmap((void *)gPE_GAV_O20.phys.addr);
		if (gPE_MCU_O20.phys.addr) iounmap((void *)gPE_MCU_O20.phys.addr);
		if (gPE_CCO_VERI_O20.phys.addr) iounmap((void *)gPE_CCO_VERI_O20.phys.addr);
		if (gPE_ND_ND0_VERI_O20.phys.addr  ) iounmap((void *)gPE_ND_ND0_VERI_O20.phys.addr  );

		if (gPE_HDR_DDR_O20) vunmap_phys((void *)gPE_HDR_DDR_O20);
		if (gPE_DDR_DB_O20.phys.addr) vunmap_phys((void *)gPE_DDR_DB_O20.phys.addr);
		if (gPE_DDR_DB_F20.phys.addr) vunmap_phys((void *)gPE_DDR_DB_F20.phys.addr);
		if (gPE_LGSR_DDR_DB_O20.phys.addr) vunmap_phys((void *)gPE_LGSR_DDR_DB_O20.phys.addr);
		if (gPE_LGSR_DDR_DB_F20.phys.addr) vunmap_phys((void *)gPE_LGSR_DDR_DB_F20.phys.addr);

		if (gPE_CHPI_DDR) vunmap_phys((void *)gPE_CHPI_DDR);
		gPE_CHPI_APB0_F20.phys.addr = NULL;
		gPE_CHPI_TBL0_F20.phys.addr = NULL;

		PE_PRINT_NOTI("[HDR]vunmap idx & [PE]vunmap blk_apl\n");
	}
	else
	{
		PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
	}
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * write address data
 *	- use address instantly allocated
 *
 * @param   addr [in] UINT32
 * @param   value [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_O20_WD(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	UINT32 recvPhysAddr;
	UINT32 currPhysAddr = 0;
	void *pVirtAddr = 0;
	do{
		if(PE_KDRV_VER_O20)
		{
			recvPhysAddr = addr;
			if		(recvPhysAddr <= 0x6000) recvPhysAddr += PE_O20_DE_BASE;
			else if (recvPhysAddr <= 0xffff) recvPhysAddr += PE_O20_DE_BASE;
			currPhysAddr = recvPhysAddr;
			/* 4byte align to access hw register */
			currPhysAddr >>= 2;
			currPhysAddr <<= 2;

			if ((currPhysAddr&0xff000000)==PE_O20_DE_BASE)	pVirtAddr = ioremap(currPhysAddr, 0x8);
			else											pVirtAddr = vmap_phys(currPhysAddr, 0x8);

			REG_WD(pVirtAddr, value);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	if (pVirtAddr)
	{
		if ((currPhysAddr&0xff000000)==PE_O20_DE_BASE)	iounmap(pVirtAddr);
		else											vunmap_phys(pVirtAddr);
	}
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
int PE_REG_O20_WrAllocatedAddr(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		if(PE_KDRV_VER_O20)
		{
			if((addr)>=PE_O20_ND0_OFST && (addr)<(PE_O20_ND0_OFST+sizeof(PE_ND_ND0_REG_O20_T)))
			{
				*((UINT32 *)(gPE_ND_ND0_O20.phys.addr+((addr-PE_O20_ND0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_ND1_OFST && (addr)<(PE_O20_ND1_OFST+sizeof(PE_ND_ND0_REG_O20_T)))
			{
				*((UINT32 *)(gPE_ND_ND1_O20.phys.addr+((addr-PE_O20_ND1_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_DNR0_OFST && (addr)<(PE_O20_DNR0_OFST+sizeof(PE_ND_DNR0_REG_O20_T)))
			{
				*((UINT32 *)(gPE_ND_DNR0_O20.phys.addr+((addr-PE_O20_DNR0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_DNR1_OFST && (addr)<(PE_O20_DNR1_OFST+sizeof(PE_ND_DNR0_REG_O20_T)))
			{
				*((UINT32 *)(gPE_ND_DNR1_O20.phys.addr+((addr-PE_O20_DNR1_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_ND_OBC_O_OFST && (addr)<(PE_O20_ND_OBC_O_OFST+sizeof(PE_DNR0_OBC_OBJT_REG_O20_T)))
			{
				*((UINT32 *)(gPE_ND_OBC_O_O20.phys.addr+((addr-PE_O20_ND_OBC_O_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_ND_OBC_F_OFST && (addr)<(PE_O20_ND_OBC_F_OFST+sizeof(PE_DNR0_OBC_FACE_REG_O20_T)))
			{
				*((UINT32 *)(gPE_ND_OBC_F_O20.phys.addr+((addr-PE_O20_ND_OBC_F_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_SR_CHR_SHP_OFST && (addr)<(PE_O20_SR_CHR_SHP_OFST+sizeof(PE_SR_CHR_SHP_REG_O20_T)))
			{
				*((UINT32 *)(gPE_SR_CHR_SHP_O20.phys.addr+((addr-PE_O20_SR_CHR_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_SR_2K_SHP_OFST && (addr)<(PE_O20_SR_2K_SHP_OFST+sizeof(PE_SR_2K_SHP_REG_O20_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHP_O20.phys.addr+((addr-PE_O20_SR_2K_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_SR_MERG_OFST && (addr)<(PE_O20_SR_MERG_OFST+sizeof(PE_SR_MERG_REG_O20_T)))
			{
				*((UINT32 *)(gPE_SR_MERG_O20.phys.addr+((addr-PE_O20_SR_MERG_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_P1_SHP_L_OFST && (addr)<(PE_O20_P1_SHP_L_OFST+sizeof(PE_SHP_REG_O20_T)))
			{
				*((UINT32 *)(gPE_SHP_O20.phys.addr+((addr-PE_O20_P1_SHP_L_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_P1_VSD_OBC_O_OFST&& (addr)<(PE_O20_P1_VSD_OBC_O_OFST+sizeof(PE_VSD_OBC_OBJT_REG_O20_T)))
			{
				*((UINT32 *)(gPE_VSD_OBC_O_O20.phys.addr+((addr-PE_O20_P1_VSD_OBC_O_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_P1_VSD_OBC_F_OFST && (addr)<(PE_O20_P1_VSD_OBC_F_OFST+sizeof(PE_VSD_OBC_FACE_REG_O20_T)))
			{
				*((UINT32 *)(gPE_VSD_OBC_F_O20.phys.addr+((addr-PE_O20_P1_VSD_OBC_F_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_P1_VSD_RCE_O_OFST&& (addr)<(PE_O20_P1_VSD_RCE_O_OFST+sizeof(PE_VSD_RCE_OBJT_REG_O20_T)))
			{
				*((UINT32 *)(gPE_VSD_RCE_O_O20.phys.addr+((addr-PE_O20_P1_VSD_RCE_O_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_P1_VSD_RCE_F_OFST && (addr)<(PE_O20_P1_VSD_RCE_F_OFST+sizeof(PE_VSD_RCE_FACE_REG_O20_T)))
			{
				*((UINT32 *)(gPE_VSD_RCE_F_O20.phys.addr+((addr-PE_O20_P1_VSD_RCE_F_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_P1_VSD_DTM_OFST && (addr)<(PE_O20_P1_VSD_DTM_OFST+sizeof(PE_VSD_DTM_REG_O20_T)))
			{
				*((UINT32 *)(gPE_VSD_DTM_O20.phys.addr+((addr-PE_O20_P1_VSD_DTM_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_P1_SHP_OSD0_OFST && (addr)<(PE_O20_P1_SHP_OSD0_OFST+sizeof(PE_SHP_OSD0_REG_O20_T)))
			{
				*((UINT32 *)(gPE_SHP_OSD0_O20.phys.addr+((addr-PE_O20_P1_SHP_OSD0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_P1_SHP_OSD1_OFST && (addr)<(PE_O20_P1_SHP_OSD1_OFST+sizeof(PE_SHP_OSD1_REG_O20_T)))
			{
				*((UINT32 *)(gPE_SHP_OSD1_O20.phys.addr+((addr-PE_O20_P1_SHP_OSD1_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_GSC_Y_OFST && (addr)<(PE_O20_GSC_Y_OFST+sizeof(PE_GSC_Y_REG_O20_T)))
			{
				*((UINT32 *)(gPE_GSC_Y_O20.phys.addr+((addr-PE_O20_GSC_Y_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_GSC_C_OFST && (addr)<(PE_O20_GSC_C_OFST+sizeof(PE_GSC_C_REG_O20_T)))
			{
				*((UINT32 *)(gPE_GSC_C_O20.phys.addr+((addr-PE_O20_GSC_C_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_IMX_OFST && (addr)<(PE_O20_IMX_OFST+sizeof(PE_TOP_IMX_REG_O20_T)))
			{
				*((UINT32 *)(gPE_TOP_IMX_O20.phys.addr+((addr-PE_O20_IMX_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_LED_DCNT_OFST && (addr)<(PE_O20_LED_DCNT_OFST+sizeof(PE_LED_DCNT_REG_O20_T)))
			{
				*((UINT32 *)(gPE_LED_DCNT_O20.phys.addr+((addr-PE_O20_LED_DCNT_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O20_ND0_VERI_OFST && (addr)<(PE_O20_ND0_VERI_OFST+sizeof(PE_ND_ND0_VERI_REG_O20_T)))
			{
				*((UINT32 *)(gPE_ND_ND0_VERI_O20.phys.addr+((addr-PE_O20_ND0_VERI_OFST)/sizeof(UINT32)))) = value;
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
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * read address data
 *
 * @param   addr [in] UINT32, accessing for register
 * @return  value of register
 * @see
 * @author
 */
UINT32 PE_REG_O20_RD(UINT32 addr)
{
	UINT32 value = 0x0;
	UINT32 recvPhysAddr;
	UINT32 currPhysAddr = 0;
	void *pVirtAddr = 0;
	do{
		if(PE_KDRV_VER_O20)
		{
			recvPhysAddr = addr;
			if		(recvPhysAddr <= 0x6000) recvPhysAddr += PE_O20_DE_BASE;
			else if (recvPhysAddr <= 0xfffff) recvPhysAddr += PE_O20_DE_BASE;
			currPhysAddr = recvPhysAddr;
			/* 4byte align to access hw register */
			currPhysAddr >>= 2;
			currPhysAddr <<= 2;

			if ((currPhysAddr&0xff000000)==PE_O20_DE_BASE)	pVirtAddr = (void *)ioremap(currPhysAddr, 0x8);
			else											pVirtAddr = (void *)vmap_phys(currPhysAddr, 0x8);

			value = REG_RD(pVirtAddr);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");
		}
	}while(0);
	if (pVirtAddr)
	{
		if ((currPhysAddr&0xff000000)==PE_O20_DE_BASE)	iounmap(pVirtAddr);
		else											vunmap_phys(pVirtAddr);
	}
	return value;
}

/**
 * write address data for debug
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  void
 * @see
 * @author
 */
int PE_REG_O20_WrReg(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 addr,data;
	do {
		CHECK_KNULL(pstParams);
		PE_REG_O20_CHECK_CODE(pstParams->size!=2,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		if(PE_KDRV_VER_O20)
		{
			addr = pstParams->data[0];
			data = pstParams->data[1];
			ret = PE_REG_O20_WD(addr,data);
			PE_REG_O20_CHECK_CODE(ret,break,"[%s,%d] PE_REG_O20_WD() error.\n",__F__,__L__);
			PE_PRINT_DEBUG("set : addr:0x%x, data:0x%x\n",addr,data);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");
		}
	} while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * read address data for debug
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  void
 * @see
 * @author
 */
int PE_REG_O20_RdReg(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 addr;
	do{
		CHECK_KNULL(pstParams);
		PE_REG_O20_CHECK_CODE(pstParams->size!=2,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		if(PE_KDRV_VER_O20)
		{
			addr = pstParams->data[0];
			pstParams->data[1] = PE_REG_O20_RD(addr);
			PE_PRINT_DEBUG("get : addr:0x%x, data:0x%x\n",addr,pstParams->data[1]);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return RET_OK;
}

/**
 * PE_REG_O20_GetDispOpt
 * see PE_REG_O20_HW_OPT_T
 *
 * @param   void
 * @return  UINT32
 * @see
 * @author
 */
PE_REG_O20_HW_OPT_T PE_REG_O20_GetDispOpt(void)
{
	return _g_pe_reg_o20_disp_opt;
}

#if 0	//legacy
/**
 * set trace table
 *
 * @param   type [in] UINT32
 * @param   *fn [in] const char, func name
 * @param   line [in] UINT32
 * @param   *tbl [in] char, table name
 * @param   ofst [in] UINT32, offset
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */ 
int PE_REG_O20_SetTraceTable(UINT32 type,const char* fn,UINT32 line,char *tbl,UINT32 ofst)
{
    int ret = RET_OK;
	char str[PE_TRACE_STR_SIZE];
	do{
		CHECK_KNULL(tbl);
		snprintf(str,PE_TRACE_STR_SIZE,"[%d][%s,%d]%s(+ 0x%x)",type,fn,line,tbl,ofst);
		ret = PE_INF_O20_SetTraceDataBuf(type,str);
		PE_REG_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_INF_O20_SetTraceDataBuf() error.\n",__F__,__L__);
	}while (0);
	return ret;
}
#endif

