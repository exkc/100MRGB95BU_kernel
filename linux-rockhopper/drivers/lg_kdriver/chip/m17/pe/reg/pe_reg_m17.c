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

/** @file pe_reg_m17.c
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

#include "be_cfg.h"
//#include "../pe_hw_m17.h"
#include "pe_hw_m17.h"
#include "pe_reg_m17.h"
//#include "../pe_inf_m17.h"
#include "pe_inf_m17.h"
#include "pe_hdr_ddr_m17.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_REG_M17_CHECK_CODE(_checker,_action,fmt,args...)		\
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
/*C0*/
PE_CE_PE1_REG_TYPE_M17C0_T   	gPE_CE_PE1_M17C0;
PE_CO_PE1_REG_TYPE_M17C0_T   	gPE_CO_PE1_M17C0;
PE_HDMI_REG_TYPE_M17C0_T     	gPE_HDMI_A_M17C0;
PE_HDMI_REG_TYPE_M17C0_T     	gPE_HDMI_B_M17C0;
PE_HDMI_REG_TYPE_M17C0_T     	gPE_HDMI_C_M17C0;
PE_HDMI_REG_TYPE_M17C0_T     	gPE_HDMI_D_M17C0;
PE_CVI_REG_TYPE_M17C0_T      	gPE_CVI_A_M17C0;
PE_CVI_REG_TYPE_M17C0_T      	gPE_CVI_B_M17C0;
PE_CVI_REG_TYPE_M17C0_T      	gPE_CVI_C_M17C0;
PE_CVI_REG_TYPE_M17C0_T      	gPE_CVI_D_M17C0;
PE_LED_RP_REG_TYPE_M17C0_T   	gPE_LED_RP_M17C0;
PE_GSC_Y_REG_TYPE_M17C0_T    	gPE_GSC_Y_M17C0;
PE_GSC_C_REG_TYPE_M17C0_T    	gPE_GSC_C_M17C0;
PE_ND_ND0_REG_TYPE_M17C0_T   	gPE_ND_ND0_M17C0;
PE_ND_DNR0_REG_TYPE_M17C0_T  	gPE_ND_DNR0_M17C0;
PE_SHP_REG_TYPE_M17C0_T     	gPE_SHP_M17C0;
PE_SHP_PSP_REG_TYPE_M17C0_T	gPE_SHP_PSP_M17C0;
//PE_SR_SHP_BRG_REG_TYPE_M17C0_T	gPE_SR_SHP_BRG_M17C0;
PE_SR_SHP_REG_TYPE_M17C0_T   	gPE_SR_SHP_M17C0;
PE_SR_PSC_Y_REG_TYPE_M17C0_T  gPE_SR_PSC_Y_M17C0;
PE_SR_PSC_C_REG_TYPE_M17C0_T  gPE_SR_PSC_C_M17C0;
PE_VCP_DE_REG_TYPE_M17C0_T 	gPE_VCP_DE_M17C0;
PE_VCP_DISP_REG_TYPE_M17C0_T 	gPE_VCP_DISP_M17C0;
PE_TOP_IMX_REG_TYPE_M17C0_T  	gPE_TOP_IMX_M17C0;
PE_IPP_REG_TYPE_M17C0_T      	gPE_IPP_M17C0;
PE_HDR10_REG_TYPE_M17C0_T 		gPE_HDR10_M17C0;
PE_DDR_DB_REG_TYPE_M17C0_T    gPE_DDR_DB_M17C0;
volatile UINT32			 	*gpe_vsd_ctrl_block_m17c0;
volatile UINT32				*gPE_HDR_DDR_M17C0;
volatile UINT32				*gPE_DDR_BLK_APL_M17C0 =NULL;
PE_HDR10_REG_TYPE_M17C0_T 		gPE_HDR10_M17C0;

/*B0, A0*/
PE_CE_PE1_REG_TYPE_M17_T   	gPE_CE_PE1_M17;
PE_CO_PE1_REG_TYPE_M17_T   	gPE_CO_PE1_M17;
PE_HDMI_REG_TYPE_M17_T     	gPE_HDMI_A_M17;
PE_HDMI_REG_TYPE_M17_T     	gPE_HDMI_B_M17;
PE_HDMI_REG_TYPE_M17_T     	gPE_HDMI_C_M17;
PE_HDMI_REG_TYPE_M17_T     	gPE_HDMI_D_M17;
PE_CVI_REG_TYPE_M17_T      	gPE_CVI_A_M17;
PE_CVI_REG_TYPE_M17_T      	gPE_CVI_B_M17;
PE_CVI_REG_TYPE_M17_T      	gPE_CVI_C_M17;
PE_CVI_REG_TYPE_M17_T      	gPE_CVI_D_M17;
PE_LED_RP_REG_TYPE_M17_T   	gPE_LED_RP_M17;
PE_GSC_Y_REG_TYPE_M17_T    	gPE_GSC_Y_M17;
PE_GSC_C_REG_TYPE_M17_T    	gPE_GSC_C_M17;
PE_ND_ND0_REG_TYPE_M17_T   	gPE_ND_ND0_M17;
PE_ND_DNR0_REG_TYPE_M17_T  	gPE_ND_DNR0_M17;
PE_SHP_REG_TYPE_M17_T     	gPE_SHP_M17;
PE_SHP_PSP_REG_TYPE_M17_T	gPE_SHP_PSP_M17;
PE_SR_SHP_BRG_REG_TYPE_M17_T	gPE_SR_SHP_BRG_M17;
PE_SR_SHP_REG_TYPE_M17_T   	gPE_SR_SHP_M17;
PE_SR_PSC_Y_REG_TYPE_M17_T  gPE_SR_PSC_Y_M17;
PE_SR_PSC_C_REG_TYPE_M17_T  gPE_SR_PSC_C_M17;
PE_VCP_DE_REG_TYPE_M17_T 	gPE_VCP_DE_M17;
PE_VCP_DISP_REG_TYPE_M17_T 	gPE_VCP_DISP_M17;
PE_TOP_IMX_REG_TYPE_M17_T  	gPE_TOP_IMX_M17;
PE_IPP_REG_TYPE_M17_T      	gPE_IPP_M17;
PE_HDR10_REG_TYPE_M17_T     gPE_HDR10_M17;
PE_DDR_DB_REG_TYPE_M17_T    gPE_DDR_DB_M17;
volatile UINT32			 	*gpe_vsd_ctrl_block_m17;
volatile UINT32				*gPE_HDR_DDR_M17;
volatile UINT32				*gPE_DDR_BLK_APL_M17 =NULL;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init phy to virtual addr
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_M17_InitPhyToVirt(void)
{
	int ret = RET_OK;
	int size;
	if(PE_KDRV_VER_M17CX)
	{
		PE_PRINT_NOTI("[PE] ioremap start\n");
		/* shdw */
		gPE_CE_PE1_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CE_PE1_REG_M17C0_T));
		gPE_CO_PE1_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CO_PE1_REG_M17C0_T));
		gPE_CVI_A_M17C0.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M17C0_T));
		gPE_CVI_B_M17C0.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M17C0_T));
		gPE_CVI_C_M17C0.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M17C0_T));
		gPE_CVI_D_M17C0.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M17C0_T));
		gPE_HDMI_A_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_M17C0_T));
		gPE_HDMI_B_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_M17C0_T));
		gPE_HDMI_C_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_M17C0_T));
		gPE_HDMI_D_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_M17C0_T));
		gPE_LED_RP_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_LED_RP_REG_M17C0_T));
		gPE_GSC_Y_M17C0.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_Y_REG_M17C0_T));
		gPE_GSC_C_M17C0.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_C_REG_M17C0_T));
		gPE_ND_ND0_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_REG_M17C0_T));
		gPE_ND_DNR0_M17C0.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR0_REG_M17C0_T));
		gPE_SHP_M17C0.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_SHP_REG_M17C0_T));
		gPE_SHP_PSP_M17C0.shdw.addr     = (UINT32 *)OS_KMalloc(sizeof(PE_SHP_PSP_REG_M17C0_T));
		//gPE_SR_SHP_BRG_M17C0.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_SR_SHP_BRG_REG_M17C0_T));
		gPE_SR_SHP_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_SHP_REG_M17C0_T));
		gPE_SR_PSC_Y_M17C0.shdw.addr     = (UINT32 *)OS_KMalloc(sizeof(PE_SR_PSC_Y_REG_M17C0_T));
		gPE_SR_PSC_C_M17C0.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_PSC_C_REG_M17C0_T));
		gPE_VCP_DE_M17C0.shdw.addr 	    = (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DE_REG_M17C0_T));
		gPE_VCP_DISP_M17C0.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DISP_REG_M17C0_T));
		gPE_TOP_IMX_M17C0.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_TOP_IMX_REG_M17C0_T));
		gPE_IPP_M17C0.shdw.addr      	= (UINT32 *)OS_KMalloc(sizeof(PE_IPP_REG_M17C0_T));
		gPE_HDR10_M17C0.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_HDR10_REG_M17C0_T));
		gPE_DDR_DB_M17C0.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_M17C0_T));
		/* phys */
		gPE_CE_PE1_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_P1_CCO_E_BASE, sizeof(PE_CE_PE1_REG_M17C0_T));
		gPE_CO_PE1_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_P1_CCO_O_BASE, sizeof(PE_CO_PE1_REG_M17C0_T));
		gPE_CVI_A_M17C0.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17C0_CVI_A_BASE,    sizeof(PE_CVI_REG_M17C0_T));
		gPE_CVI_B_M17C0.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17C0_CVI_B_BASE,    sizeof(PE_CVI_REG_M17C0_T));
		gPE_CVI_C_M17C0.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17C0_CVI_C_BASE,    sizeof(PE_CVI_REG_M17C0_T));
		gPE_CVI_D_M17C0.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17C0_CVI_D_BASE,    sizeof(PE_CVI_REG_M17C0_T));
		gPE_HDMI_A_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_HDMI_A_BASE,   sizeof(PE_HDMI_REG_M17C0_T));
		gPE_HDMI_B_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_HDMI_B_BASE,   sizeof(PE_HDMI_REG_M17C0_T));
		gPE_HDMI_C_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_HDMI_C_BASE,   sizeof(PE_HDMI_REG_M17C0_T));
		gPE_HDMI_D_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_HDMI_D_BASE,   sizeof(PE_HDMI_REG_M17C0_T));
		gPE_LED_RP_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_LED_RP_BASE,   sizeof(PE_LED_RP_REG_M17C0_T));
		gPE_GSC_Y_M17C0.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17C0_GSC_Y_BASE,    sizeof(PE_GSC_Y_REG_M17C0_T));
		gPE_GSC_C_M17C0.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17C0_GSC_C_BASE,    sizeof(PE_GSC_C_REG_M17C0_T));
		gPE_ND_ND0_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_ND0_BASE,      sizeof(PE_ND_ND0_REG_M17C0_T));
		gPE_ND_DNR0_M17C0.phys.addr  	= (volatile UINT32 *)ioremap(PE_M17C0_DNR0_BASE,     sizeof(PE_ND_DNR0_REG_M17C0_T));
		gPE_SHP_M17C0.phys.addr     	= (volatile UINT32 *)ioremap(PE_M17C0_P1_SHP_L_BASE, sizeof(PE_SHP_REG_M17C0_T));
		gPE_SHP_PSP_M17C0.phys.addr   = (volatile UINT32 *)ioremap(PE_M17C0_P1_SHP_PSP_BASE, sizeof(PE_SHP_REG_M17C0_T));
		//gPE_SR_SHP_BRG_M17C0.phys.addr   = (volatile UINT32 *)ioremap(PE_M17C0_SR_SHP_BASE,   sizeof(PE_SR_SHP_BRG_REG_M17C0_T));
		gPE_SR_SHP_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_SR_SHP_BASE,   sizeof(PE_SR_SHP_REG_M17C0_T));
		gPE_SR_PSC_Y_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_SR_SHP_BASE,   sizeof(PE_SR_PSC_Y_REG_M17C0_T));
		gPE_SR_PSC_C_M17C0.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17C0_SR_SHP_BASE,   sizeof(PE_SR_PSC_C_REG_M17C0_T));
		gPE_VCP_DE_M17C0.phys.addr 	    = (volatile UINT32 *)ioremap(PE_M17C0_VCP_DE_BASE, sizeof(PE_VCP_DE_REG_M17C0_T));
		gPE_VCP_DISP_M17C0.phys.addr 	= (volatile UINT32 *)ioremap(PE_M17C0_VCP_DISP_BASE, sizeof(PE_VCP_DISP_REG_M17C0_T));
		gPE_TOP_IMX_M17C0.phys.addr  	= (volatile UINT32 *)ioremap(PE_M17C0_IMX_BASE,      sizeof(PE_TOP_IMX_REG_M17C0_T));
		gPE_IPP_M17C0.phys.addr      	= (volatile UINT32 *)ioremap(PE_M17C0_IPP_BASE,      sizeof(PE_IPP_REG_M17C0_T));
		gPE_HDR10_M17C0.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17C0_HDR10_BASE,    sizeof(PE_HDR10_REG_M17C0_T));
		gpe_vsd_ctrl_block_m17c0    	= (volatile UINT32 *)ioremap(PE_M17C0_VSD_BASE,    sizeof(UINT32));
		size = PE_HDR_DDR_M17C0_TOTAL_SIZE;
		gPE_HDR_DDR_M17				= (volatile UINT32 *)vmap_phys(PE_HDR_DDR_M17C0_BASE_ADDR,size+PAGE_SIZE);
		PE_PRINT_NOTI("[HDR]v(%d), vmap base:0x%08x,size:0x%08x+0x%08x\n",\
			PE_HDR_DDR_M17C0_VERSION,PE_HDR_DDR_M17C0_BASE_ADDR,size,(UINT32)PAGE_SIZE);
		
		PE_PRINT_NOTI("[PE] ioremap done\n");
	}
	else if(PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
	{
		PE_PRINT_NOTI("[PE] ioremap start B0\n");
		/* shdw */
		gPE_CE_PE1_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CE_PE1_REG_M17_T));
		gPE_CO_PE1_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CO_PE1_REG_M17_T));
		gPE_CVI_A_M17.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M17_T));
		gPE_CVI_B_M17.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M17_T));
		gPE_CVI_C_M17.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M17_T));
		gPE_CVI_D_M17.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M17_T));
		gPE_HDMI_A_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_M17_T));
		gPE_HDMI_B_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_M17_T));
		gPE_HDMI_C_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_M17_T));
		gPE_HDMI_D_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_M17_T));
		gPE_LED_RP_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_LED_RP_REG_M17_T));
		gPE_GSC_Y_M17.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_Y_REG_M17_T));
		gPE_GSC_C_M17.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_C_REG_M17_T));
		gPE_ND_ND0_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_REG_M17_T));
		gPE_ND_DNR0_M17.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR0_REG_M17_T));
		gPE_SHP_M17.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_SHP_REG_M17_T));
		gPE_SHP_PSP_M17.shdw.addr     = (UINT32 *)OS_KMalloc(sizeof(PE_SHP_PSP_REG_M17_T));
		gPE_SR_SHP_BRG_M17.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_SR_SHP_BRG_REG_M17_T));
		gPE_SR_SHP_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_SHP_REG_M17_T));
		gPE_SR_PSC_Y_M17.shdw.addr     = (UINT32 *)OS_KMalloc(sizeof(PE_SR_PSC_Y_REG_M17_T));
		gPE_SR_PSC_C_M17.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_PSC_C_REG_M17_T));
		gPE_VCP_DE_M17.shdw.addr 	    = (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DE_REG_M17_T));
		gPE_VCP_DISP_M17.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DISP_REG_M17_T));
		gPE_TOP_IMX_M17.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_TOP_IMX_REG_M17_T));
		gPE_IPP_M17.shdw.addr      	= (UINT32 *)OS_KMalloc(sizeof(PE_IPP_REG_M17_T));
		gPE_HDR10_M17.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_HDR10_REG_M17_T));
		gPE_DDR_DB_M17.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_M17_T));
		/* phys */
		gPE_CE_PE1_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_P1_CCO_E_BASE, sizeof(PE_CE_PE1_REG_M17_T));
		gPE_CO_PE1_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_P1_CCO_O_BASE, sizeof(PE_CO_PE1_REG_M17_T));
		gPE_CVI_A_M17.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17_CVI_A_BASE,    sizeof(PE_CVI_REG_M17_T));
		gPE_CVI_B_M17.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17_CVI_B_BASE,    sizeof(PE_CVI_REG_M17_T));
		gPE_CVI_C_M17.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17_CVI_C_BASE,    sizeof(PE_CVI_REG_M17_T));
		gPE_CVI_D_M17.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17_CVI_D_BASE,    sizeof(PE_CVI_REG_M17_T));
		gPE_HDMI_A_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_HDMI_A_BASE,   sizeof(PE_HDMI_REG_M17_T));
		gPE_HDMI_B_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_HDMI_B_BASE,   sizeof(PE_HDMI_REG_M17_T));
		gPE_HDMI_C_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_HDMI_C_BASE,   sizeof(PE_HDMI_REG_M17_T));
		gPE_HDMI_D_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_HDMI_D_BASE,   sizeof(PE_HDMI_REG_M17_T));
		gPE_LED_RP_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_LED_RP_BASE,   sizeof(PE_LED_RP_REG_M17_T));
		gPE_GSC_Y_M17.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17_GSC_Y_BASE,    sizeof(PE_GSC_Y_REG_M17_T));
		gPE_GSC_C_M17.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17_GSC_C_BASE,    sizeof(PE_GSC_C_REG_M17_T));
		gPE_ND_ND0_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_ND0_BASE,      sizeof(PE_ND_ND0_REG_M17_T));
		gPE_ND_DNR0_M17.phys.addr  	= (volatile UINT32 *)ioremap(PE_M17_DNR0_BASE,     sizeof(PE_ND_DNR0_REG_M17_T));
		gPE_SHP_M17.phys.addr     	= (volatile UINT32 *)ioremap(PE_M17_P1_SHP_L_BASE, sizeof(PE_SHP_REG_M17_T));
		gPE_SHP_PSP_M17.phys.addr   = (volatile UINT32 *)ioremap(PE_M17_P1_SHP_PSP_BASE, sizeof(PE_SHP_REG_M17_T));
		gPE_SR_SHP_BRG_M17.phys.addr   = (volatile UINT32 *)ioremap(PE_M17_SR_SHP_BASE,   sizeof(PE_SR_SHP_BRG_REG_M17_T));
		gPE_SR_SHP_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_SR_SHP_BASE,   sizeof(PE_SR_SHP_REG_M17_T));
		gPE_SR_PSC_Y_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_SR_SHP_BASE,   sizeof(PE_SR_PSC_Y_REG_M17_T));
		gPE_SR_PSC_C_M17.phys.addr   	= (volatile UINT32 *)ioremap(PE_M17_SR_SHP_BASE,   sizeof(PE_SR_PSC_C_REG_M17_T));
		gPE_VCP_DE_M17.phys.addr 	    = (volatile UINT32 *)ioremap(PE_M17_VCP_DE_BASE, sizeof(PE_VCP_DE_REG_M17_T));
		gPE_VCP_DISP_M17.phys.addr 	= (volatile UINT32 *)ioremap(PE_M17_VCP_DISP_BASE, sizeof(PE_VCP_DISP_REG_M17_T));
		gPE_TOP_IMX_M17.phys.addr  	= (volatile UINT32 *)ioremap(PE_M17_IMX_BASE,      sizeof(PE_TOP_IMX_REG_M17_T));
		gPE_IPP_M17.phys.addr      	= (volatile UINT32 *)ioremap(PE_M17_IPP_BASE,      sizeof(PE_IPP_REG_M17_T));
		gPE_HDR10_M17.phys.addr    	= (volatile UINT32 *)ioremap(PE_M17_HDR10_BASE,    sizeof(PE_HDR10_REG_M17_T));
		gpe_vsd_ctrl_block_m17    	= (volatile UINT32 *)ioremap(PE_M17_VSD_BASE,    sizeof(UINT32));
		if (PE_HDR_DDR_M17_VERSION>=0x3)		size = PE_HDR_DDR_M17_V3_TOTAL_SIZE;
		else if (PE_HDR_DDR_M17_VERSION>=0x2)	size = PE_HDR_DDR_M17_V2_TOTAL_SIZE;
		else									size = PE_HDR_DDR_M17_TOTAL_SIZE;
		gPE_HDR_DDR_M17				= (volatile UINT32 *)vmap_phys(PE_HDR_DDR_M17_BASE_ADDR,size+PAGE_SIZE);
		PE_PRINT_NOTI("[M17B][HDR]v(%d), vmap base:0x%08x,size:0x%08x+0x%08x\n",\
			PE_HDR_DDR_M17_VERSION,PE_HDR_DDR_M17_BASE_ADDR,size,(UINT32)PAGE_SIZE);
		
		
		PE_PRINT_NOTI("[PE] ioremap done B0\n");
	}
	else
	{
		PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
	}
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
int PE_REG_M17_FreePhyToVirt(void)
{
	int ret = RET_OK;
	
	if(PE_KDRV_VER_M17CX)
	{
		/* shdw */
		if (gPE_CE_PE1_M17C0.shdw.addr  ) OS_Free((void *)gPE_CE_PE1_M17C0.shdw.addr  );
		if (gPE_CO_PE1_M17C0.shdw.addr  ) OS_Free((void *)gPE_CO_PE1_M17C0.shdw.addr  );
		if (gPE_CVI_A_M17C0.shdw.addr   ) OS_Free((void *)gPE_CVI_A_M17C0.shdw.addr   );
		if (gPE_CVI_B_M17C0.shdw.addr   ) OS_Free((void *)gPE_CVI_B_M17C0.shdw.addr   );
		if (gPE_CVI_C_M17C0.shdw.addr   ) OS_Free((void *)gPE_CVI_C_M17C0.shdw.addr   );
		if (gPE_CVI_D_M17C0.shdw.addr   ) OS_Free((void *)gPE_CVI_D_M17C0.shdw.addr   );
		if (gPE_LED_RP_M17C0.shdw.addr  ) OS_Free((void *)gPE_LED_RP_M17C0.shdw.addr  );
		if (gPE_VCP_DE_M17C0.shdw.addr) OS_Free((void *)gPE_VCP_DE_M17C0.shdw.addr);
		if (gPE_VCP_DISP_M17C0.shdw.addr) OS_Free((void *)gPE_VCP_DISP_M17C0.shdw.addr);
		if (gPE_TOP_IMX_M17C0.shdw.addr ) OS_Free((void *)gPE_TOP_IMX_M17C0.shdw.addr );
		if (gPE_IPP_M17C0.shdw.addr     ) OS_Free((void *)gPE_IPP_M17C0.shdw.addr     );
		if (gPE_HDMI_A_M17C0.shdw.addr  ) OS_Free((void *)gPE_HDMI_A_M17C0.shdw.addr  );
		if (gPE_HDMI_B_M17C0.shdw.addr  ) OS_Free((void *)gPE_HDMI_B_M17C0.shdw.addr  );
		if (gPE_HDMI_C_M17C0.shdw.addr  ) OS_Free((void *)gPE_HDMI_C_M17C0.shdw.addr  );
		if (gPE_HDMI_D_M17C0.shdw.addr  ) OS_Free((void *)gPE_HDMI_D_M17C0.shdw.addr  );
		if (gPE_GSC_Y_M17C0.shdw.addr   ) OS_Free((void *)gPE_GSC_Y_M17C0.shdw.addr   );
		if (gPE_GSC_C_M17C0.shdw.addr   ) OS_Free((void *)gPE_GSC_C_M17C0.shdw.addr   );
		if (gPE_ND_ND0_M17C0.shdw.addr  ) OS_Free((void *)gPE_ND_ND0_M17C0.shdw.addr  );
		if (gPE_ND_DNR0_M17C0.shdw.addr ) OS_Free((void *)gPE_ND_DNR0_M17C0.shdw.addr );
		if (gPE_SHP_M17C0.shdw.addr    ) OS_Free((void *)gPE_SHP_M17C0.shdw.addr    );
		if (gPE_SHP_PSP_M17C0.shdw.addr    ) OS_Free((void *)gPE_SHP_PSP_M17C0.shdw.addr    );
		if (gPE_SR_SHP_M17C0.shdw.addr  ) OS_Free((void *)gPE_SR_SHP_M17C0.shdw.addr  );
		//if (gPE_SR_SHP_BRG_M17C0.shdw.addr  ) OS_Free((void *)gPE_SR_SHP_BRG_M17C0.shdw.addr  );
		if (gPE_DDR_DB_M17C0.shdw.addr    ) OS_Free((void *)gPE_DDR_DB_M17C0.shdw.addr    );
		if (gPE_HDR10_M17C0.shdw.addr   ) OS_Free((void *)gPE_HDR10_M17C0.shdw.addr   );
		/* phys */
		if (gPE_CE_PE1_M17C0.phys.addr  ) iounmap((void *)gPE_CE_PE1_M17C0.phys.addr  );
		if (gPE_CO_PE1_M17C0.phys.addr  ) iounmap((void *)gPE_CO_PE1_M17C0.phys.addr  );
		if (gPE_CVI_A_M17C0.phys.addr   ) iounmap((void *)gPE_CVI_A_M17C0.phys.addr   );
		if (gPE_CVI_B_M17C0.phys.addr   ) iounmap((void *)gPE_CVI_B_M17C0.phys.addr   );
		if (gPE_CVI_C_M17C0.phys.addr   ) iounmap((void *)gPE_CVI_C_M17C0.phys.addr   );
		if (gPE_CVI_D_M17C0.phys.addr   ) iounmap((void *)gPE_CVI_D_M17C0.phys.addr   );
		if (gPE_LED_RP_M17C0.phys.addr  ) iounmap((void *)gPE_LED_RP_M17C0.phys.addr  );
		if (gPE_VCP_DE_M17C0.phys.addr) iounmap((void *)gPE_VCP_DE_M17C0.phys.addr);
		if (gPE_VCP_DISP_M17C0.phys.addr) iounmap((void *)gPE_VCP_DISP_M17C0.phys.addr);
		if (gPE_TOP_IMX_M17C0.phys.addr ) iounmap((void *)gPE_TOP_IMX_M17C0.phys.addr );
		if (gPE_IPP_M17C0.phys.addr     ) iounmap((void *)gPE_IPP_M17C0.phys.addr     );
		if (gPE_HDMI_A_M17C0.phys.addr  ) iounmap((void *)gPE_HDMI_A_M17C0.phys.addr  );
		if (gPE_HDMI_B_M17C0.phys.addr  ) iounmap((void *)gPE_HDMI_B_M17C0.phys.addr  );
		if (gPE_HDMI_C_M17C0.phys.addr  ) iounmap((void *)gPE_HDMI_C_M17C0.phys.addr  );
		if (gPE_HDMI_D_M17C0.phys.addr  ) iounmap((void *)gPE_HDMI_D_M17C0.phys.addr  );
		if (gPE_GSC_Y_M17C0.phys.addr   ) iounmap((void *)gPE_GSC_Y_M17C0.phys.addr   );
		if (gPE_GSC_C_M17C0.phys.addr   ) iounmap((void *)gPE_GSC_C_M17C0.phys.addr   );
		if (gPE_ND_ND0_M17C0.phys.addr  ) iounmap((void *)gPE_ND_ND0_M17C0.phys.addr  );
		if (gPE_ND_DNR0_M17C0.phys.addr ) iounmap((void *)gPE_ND_DNR0_M17C0.phys.addr );
		if (gPE_SHP_M17C0.phys.addr     ) iounmap((void *)gPE_SHP_M17C0.phys.addr     );
		if (gPE_SHP_PSP_M17C0.phys.addr ) iounmap((void *)gPE_SHP_PSP_M17C0.phys.addr );
		if (gPE_SR_SHP_M17C0.phys.addr  ) iounmap((void *)gPE_SR_SHP_M17C0.phys.addr  );
		//if (gPE_SR_SHP_BRG_M17C0.phys.addr  ) iounmap((void *)gPE_SR_SHP_BRG_M17C0.phys.addr  );
		if (gPE_HDR10_M17C0.phys.addr   ) iounmap((void *)gPE_HDR10_M17C0.phys.addr   );
		if (gpe_vsd_ctrl_block_m17c0) 	iounmap((void *)gpe_vsd_ctrl_block_m17c0);
		if (gPE_DDR_BLK_APL_M17C0)		vunmap_phys((void *)gPE_DDR_BLK_APL_M17C0);
		if (gPE_HDR_DDR_M17)			vunmap_phys((void *)gPE_HDR_DDR_M17);
		PE_PRINT_NOTI("[HDR]vunmap idx.& [PE]vunmap blk_apl.\n");
	}
	else if(PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
	{
		/* shdw */
		if (gPE_CE_PE1_M17.shdw.addr  ) OS_Free((void *)gPE_CE_PE1_M17.shdw.addr  );
		if (gPE_CO_PE1_M17.shdw.addr  ) OS_Free((void *)gPE_CO_PE1_M17.shdw.addr  );
		if (gPE_CVI_A_M17.shdw.addr   ) OS_Free((void *)gPE_CVI_A_M17.shdw.addr   );
		if (gPE_CVI_B_M17.shdw.addr   ) OS_Free((void *)gPE_CVI_B_M17.shdw.addr   );
		if (gPE_CVI_C_M17.shdw.addr   ) OS_Free((void *)gPE_CVI_C_M17.shdw.addr   );
		if (gPE_CVI_D_M17.shdw.addr   ) OS_Free((void *)gPE_CVI_D_M17.shdw.addr   );
		if (gPE_LED_RP_M17.shdw.addr  ) OS_Free((void *)gPE_LED_RP_M17.shdw.addr  );
		if (gPE_VCP_DE_M17.shdw.addr) OS_Free((void *)gPE_VCP_DE_M17.shdw.addr);
		if (gPE_VCP_DISP_M17.shdw.addr) OS_Free((void *)gPE_VCP_DISP_M17.shdw.addr);
		if (gPE_TOP_IMX_M17.shdw.addr ) OS_Free((void *)gPE_TOP_IMX_M17.shdw.addr );
		if (gPE_IPP_M17.shdw.addr     ) OS_Free((void *)gPE_IPP_M17.shdw.addr     );
		if (gPE_HDMI_A_M17.shdw.addr  ) OS_Free((void *)gPE_HDMI_A_M17.shdw.addr  );
		if (gPE_HDMI_B_M17.shdw.addr  ) OS_Free((void *)gPE_HDMI_B_M17.shdw.addr  );
		if (gPE_HDMI_C_M17.shdw.addr  ) OS_Free((void *)gPE_HDMI_C_M17.shdw.addr  );
		if (gPE_HDMI_D_M17.shdw.addr  ) OS_Free((void *)gPE_HDMI_D_M17.shdw.addr  );
		if (gPE_GSC_Y_M17.shdw.addr   ) OS_Free((void *)gPE_GSC_Y_M17.shdw.addr   );
		if (gPE_GSC_C_M17.shdw.addr   ) OS_Free((void *)gPE_GSC_C_M17.shdw.addr   );
		if (gPE_ND_ND0_M17.shdw.addr  ) OS_Free((void *)gPE_ND_ND0_M17.shdw.addr  );
		if (gPE_ND_DNR0_M17.shdw.addr ) OS_Free((void *)gPE_ND_DNR0_M17.shdw.addr );
		if (gPE_SHP_M17.shdw.addr    ) OS_Free((void *)gPE_SHP_M17.shdw.addr    );
		if (gPE_SHP_PSP_M17.shdw.addr    ) OS_Free((void *)gPE_SHP_PSP_M17.shdw.addr    );
		if (gPE_SR_SHP_M17.shdw.addr  ) OS_Free((void *)gPE_SR_SHP_M17.shdw.addr  );
		if (gPE_SR_SHP_BRG_M17.shdw.addr  ) OS_Free((void *)gPE_SR_SHP_BRG_M17.shdw.addr  );
		if (gPE_DDR_DB_M17.shdw.addr    ) OS_Free((void *)gPE_DDR_DB_M17.shdw.addr    );
		if (gPE_HDR10_M17.shdw.addr   ) OS_Free((void *)gPE_HDR10_M17.shdw.addr   );
		/* phys */
		if (gPE_CE_PE1_M17.phys.addr  ) iounmap((void *)gPE_CE_PE1_M17.phys.addr  );
		if (gPE_CO_PE1_M17.phys.addr  ) iounmap((void *)gPE_CO_PE1_M17.phys.addr  );
		if (gPE_CVI_A_M17.phys.addr   ) iounmap((void *)gPE_CVI_A_M17.phys.addr   );
		if (gPE_CVI_B_M17.phys.addr   ) iounmap((void *)gPE_CVI_B_M17.phys.addr   );
		if (gPE_CVI_C_M17.phys.addr   ) iounmap((void *)gPE_CVI_C_M17.phys.addr   );
		if (gPE_CVI_D_M17.phys.addr   ) iounmap((void *)gPE_CVI_D_M17.phys.addr   );
		if (gPE_LED_RP_M17.phys.addr  ) iounmap((void *)gPE_LED_RP_M17.phys.addr  );
		if (gPE_VCP_DE_M17.phys.addr) iounmap((void *)gPE_VCP_DE_M17.phys.addr);
		if (gPE_VCP_DISP_M17.phys.addr) iounmap((void *)gPE_VCP_DISP_M17.phys.addr);
		if (gPE_TOP_IMX_M17.phys.addr ) iounmap((void *)gPE_TOP_IMX_M17.phys.addr );
		if (gPE_IPP_M17.phys.addr     ) iounmap((void *)gPE_IPP_M17.phys.addr     );
		if (gPE_HDMI_A_M17.phys.addr  ) iounmap((void *)gPE_HDMI_A_M17.phys.addr  );
		if (gPE_HDMI_B_M17.phys.addr  ) iounmap((void *)gPE_HDMI_B_M17.phys.addr  );
		if (gPE_HDMI_C_M17.phys.addr  ) iounmap((void *)gPE_HDMI_C_M17.phys.addr  );
		if (gPE_HDMI_D_M17.phys.addr  ) iounmap((void *)gPE_HDMI_D_M17.phys.addr  );
		if (gPE_GSC_Y_M17.phys.addr   ) iounmap((void *)gPE_GSC_Y_M17.phys.addr   );
		if (gPE_GSC_C_M17.phys.addr   ) iounmap((void *)gPE_GSC_C_M17.phys.addr   );
		if (gPE_ND_ND0_M17.phys.addr  ) iounmap((void *)gPE_ND_ND0_M17.phys.addr  );
		if (gPE_ND_DNR0_M17.phys.addr ) iounmap((void *)gPE_ND_DNR0_M17.phys.addr );
		if (gPE_SHP_M17.phys.addr     ) iounmap((void *)gPE_SHP_M17.phys.addr     );
		if (gPE_SHP_PSP_M17.phys.addr ) iounmap((void *)gPE_SHP_PSP_M17.phys.addr );
		if (gPE_SR_SHP_M17.phys.addr  ) iounmap((void *)gPE_SR_SHP_M17.phys.addr  );
		if (gPE_SR_SHP_BRG_M17.phys.addr  ) iounmap((void *)gPE_SR_SHP_BRG_M17.phys.addr  );
		if (gPE_HDR10_M17.phys.addr   ) iounmap((void *)gPE_HDR10_M17.phys.addr   );
		if (gpe_vsd_ctrl_block_m17) 	iounmap((void *)gpe_vsd_ctrl_block_m17);
		if (gPE_DDR_BLK_APL_M17)		vunmap_phys((void *)gPE_DDR_BLK_APL_M17);
		if (gPE_HDR_DDR_M17)			vunmap_phys((void *)gPE_HDR_DDR_M17);
		PE_PRINT_NOTI("[M17B][HDR]vunmap idx.& [PE]vunmap blk_apl.\n");
	}
	else
	{
		PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
	}
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
int PE_REG_M17_WD(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	UINT32 recvPhysAddr;
	UINT32 currPhysAddr = 0;
	void *pVirtAddr = 0;
	do{
		if(PE_KDRV_VER_M17)
		{
			recvPhysAddr = addr;
			if		(recvPhysAddr <= 0x6000) recvPhysAddr += PE_M17_DE_BASE;
			else if (recvPhysAddr <= 0xffff) recvPhysAddr += PE_M17_DE_BASE;
			currPhysAddr = recvPhysAddr;
			/* 4byte align to access hw register */
			currPhysAddr >>= 2;
			currPhysAddr <<= 2;

			if ((currPhysAddr&0xff000000)==PE_M17_DE_BASE)	pVirtAddr = ioremap(currPhysAddr, 0x8);
			else											pVirtAddr = vmap_phys(currPhysAddr, 0x8);

			REG_WD(pVirtAddr, value);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	if (!pVirtAddr)
	{
		if ((currPhysAddr&0xff000000)==PE_M17_DE_BASE)	iounmap(pVirtAddr);
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
int PE_REG_M17_WrAllocatedAddr(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_M17CX)
		{
			if((addr)>=PE_M17C0_ND_OFST && (addr)<(PE_M17C0_ND_OFST+sizeof(PE_ND_ND0_REG_M17C0_T)))
			{
				*((UINT32 *)(gPE_ND_ND0_M17C0.phys.addr+((addr-PE_M17C0_ND_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17C0_DNR_OFST && (addr)<(PE_M17C0_DNR_OFST+sizeof(PE_ND_DNR0_REG_M17C0_T)))
			{
				*((UINT32 *)(gPE_ND_DNR0_M17C0.phys.addr+((addr-PE_M17C0_DNR_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17C0_SR_SHP_OFST && (addr)<(PE_M17C0_SR_SHP_OFST+sizeof(PE_SR_SHP_REG_M17C0_T)))
			{
				*((UINT32 *)(gPE_SR_SHP_M17C0.phys.addr+((addr-PE_M17C0_SR_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17C0_P1_SHP_L_OFST && (addr)<(PE_M17C0_P1_SHP_L_OFST+sizeof(PE_SHP_REG_M17C0_T)))
			{
				*((UINT32 *)(gPE_SHP_M17C0.phys.addr+((addr-PE_M17C0_P1_SHP_L_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17C0_GSC_Y_OFST && (addr)<(PE_M17C0_GSC_Y_OFST+sizeof(PE_GSC_Y_REG_M17C0_T)))
			{
				*((UINT32 *)(gPE_GSC_Y_M17C0.phys.addr+((addr-PE_M17C0_GSC_Y_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17C0_GSC_C_OFST && (addr)<(PE_M17C0_GSC_C_OFST+sizeof(PE_GSC_C_REG_M17C0_T)))
			{
				*((UINT32 *)(gPE_GSC_C_M17C0.phys.addr+((addr-PE_M17C0_GSC_C_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17C0_IMX_OFST && (addr)<(PE_M17C0_IMX_OFST+sizeof(PE_TOP_IMX_REG_M17C0_T)))
			{
				*((UINT32 *)(gPE_TOP_IMX_M17C0.phys.addr+((addr-PE_M17C0_IMX_OFST)/sizeof(UINT32)))) = value;
			}
			else
			{
				PE_PRINT_WARN("[%x]not support.(0x%04x, 0x%08x)\n",\
					PE_CHIP_VER,(addr),(value));
			}
		}
		else if(PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
		{
			if((addr)>=PE_M17_ND_OFST && (addr)<(PE_M17_ND_OFST+sizeof(PE_ND_ND0_REG_M17_T)))
			{
				*((UINT32 *)(gPE_ND_ND0_M17.phys.addr+((addr-PE_M17_ND_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17_DNR_OFST && (addr)<(PE_M17_DNR_OFST+sizeof(PE_ND_DNR0_REG_M17_T)))
			{
				*((UINT32 *)(gPE_ND_DNR0_M17.phys.addr+((addr-PE_M17_DNR_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17_SR_SHP_OFST && (addr)<(PE_M17_SR_SHP_OFST+sizeof(PE_SR_SHP_REG_M17_T)))
			{
				*((UINT32 *)(gPE_SR_SHP_M17.phys.addr+((addr-PE_M17_SR_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17_P1_SHP_L_OFST && (addr)<(PE_M17_P1_SHP_L_OFST+sizeof(PE_SHP_REG_M17_T)))
			{
				*((UINT32 *)(gPE_SHP_M17.phys.addr+((addr-PE_M17_P1_SHP_L_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17_GSC_Y_OFST && (addr)<(PE_M17_GSC_Y_OFST+sizeof(PE_GSC_Y_REG_M17_T)))
			{
				*((UINT32 *)(gPE_GSC_Y_M17.phys.addr+((addr-PE_M17_GSC_Y_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17_GSC_C_OFST && (addr)<(PE_M17_GSC_C_OFST+sizeof(PE_GSC_C_REG_M17_T)))
			{
				*((UINT32 *)(gPE_GSC_C_M17.phys.addr+((addr-PE_M17_GSC_C_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M17_IMX_OFST && (addr)<(PE_M17_IMX_OFST+sizeof(PE_TOP_IMX_REG_M17_T)))
			{
				*((UINT32 *)(gPE_TOP_IMX_M17.phys.addr+((addr-PE_M17_IMX_OFST)/sizeof(UINT32)))) = value;
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
UINT32 PE_REG_M17_RD(UINT32 addr)
{
	UINT32 value = 0x0;
	UINT32 recvPhysAddr;
	UINT32 currPhysAddr = 0;
	void *pVirtAddr = 0;
	do{
		if(PE_KDRV_VER_M17)
		{
			recvPhysAddr = addr;
			if		(recvPhysAddr <= 0x6000) recvPhysAddr += PE_M17_DE_BASE;
			else if (recvPhysAddr <= 0xffff) recvPhysAddr += PE_M17_DE_BASE;
			currPhysAddr = recvPhysAddr;
			/* 4byte align to access hw register */
			currPhysAddr >>= 2;
			currPhysAddr <<= 2;

			if ((currPhysAddr&0xff000000)==PE_M17_DE_BASE)	pVirtAddr = (void *)ioremap(currPhysAddr, 0x8);
			else											pVirtAddr = (void *)vmap_phys(currPhysAddr, 0x8);

			value = REG_RD(pVirtAddr);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");
		}
	}while(0);
	if (!pVirtAddr)
	{
		if ((currPhysAddr&0xff000000)==PE_M17_DE_BASE)	iounmap(pVirtAddr);
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
int PE_REG_M17_WrReg(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	UINT32 addr,data;
	do {
		CHECK_KNULL(pstParams);
		PE_REG_M17_CHECK_CODE(pstParams->size!=2,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		if(PE_KDRV_VER_M17)
		{
			addr = pstParams->data[0];
			data = pstParams->data[1];
			ret = PE_REG_M17_WD(addr,data);
			PE_REG_M17_CHECK_CODE(ret,break,"[%s,%d] PE_REG_M17_WD() error.\n",__F__,__L__);
			PE_PRINT_DEBUG("set : addr:0x%x, data:0x%x\n",addr,data);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");
		}
	} while(0);
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
int PE_REG_M17_RdReg(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	UINT32 addr;
	do{
		CHECK_KNULL(pstParams);
		PE_REG_M17_CHECK_CODE(pstParams->size!=2,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		if(PE_KDRV_VER_M17)
		{
			addr = pstParams->data[0];
			pstParams->data[1] = PE_REG_M17_RD(addr);
			PE_PRINT_DEBUG("get : addr:0x%x, data:0x%x\n",addr,pstParams->data[1]);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");
		}
	}while(0);
	return RET_OK;
}

/**
 * set trace table
 *
 * @param   *fn [in] const char, func name
 * @param   line [in] UINT32
 * @param   *tbl [in] char, table name
 * @param   ofst [in] UINT32, offset
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */ 
int PE_REG_M17_SetTraceTable(const char* fn,
							UINT32 line,
							char *tbl,
							UINT32 ofst)
{
    int ret = RET_OK;
	char str[PE_TRACE_STR_SIZE];
	do{
		CHECK_KNULL(tbl);
		sprintf(str, "[%s,%d]%s(+ 0x%x)", fn, line, tbl, ofst);
		ret = PE_INF_M17_SetTraceDataBuf(str);
		PE_REG_M17_CHECK_CODE(ret, break, \
			"[%s,%d] PE_INF_M17_SetTraceDataBuf() error.\n",__F__,__L__);
	}while (0);
	return ret;
}

