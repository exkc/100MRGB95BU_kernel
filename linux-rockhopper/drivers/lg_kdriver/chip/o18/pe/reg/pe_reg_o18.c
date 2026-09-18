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

/** @file pe_reg_o18.c
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
//#include "../pe_hw_o18.h"
#include "pe_hw_o18.h"
#include "pe_reg_o18.h"
//#include "../pe_inf_o18.h"
#include "pe_inf_o18.h"
#include "pe_hdr_ddr_o18.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_REG_O18_CHECK_CODE(_checker,_action,fmt,args...)		\
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
PE_CE_PE1_REG_TYPE_O18_T   	  gPE_CE_PE1_O18;
PE_CO_PE1_REG_TYPE_O18_T   	  gPE_CO_PE1_O18;
PE_HDMI_REG_TYPE_O18_T     	  gPE_HDMI_A_O18;
PE_HDMI_REG_TYPE_O18_T     	  gPE_HDMI_B_O18;
PE_HDMI_REG_TYPE_O18_T     	  gPE_HDMI_C_O18;
PE_HDMI_REG_TYPE_O18_T     	  gPE_HDMI_D_O18;
PE_CVI_REG_TYPE_O18_T      	  gPE_CVI_A_O18;
PE_CVI_REG_TYPE_O18_T      	  gPE_CVI_B_O18;
PE_CVI_REG_TYPE_O18_T      	  gPE_CVI_C_O18;
PE_CVI_REG_TYPE_O18_T      	  gPE_CVI_D_O18;
PE_LED_RP_REG_TYPE_O18_T   	  gPE_LED_RP_O18;
PE_LED_DCNT_REG_TYPE_O18_T    gPE_LED_DCNT_O18;
PE_GSC_Y_REG_TYPE_O18_T    	  gPE_GSC_Y_O18;
PE_GSC_C_REG_TYPE_O18_T    	  gPE_GSC_C_O18;
PE_ND_ND0_REG_TYPE_O18_T   	  gPE_ND_ND0_O18;
PE_ND_DNR0_REG_TYPE_O18_T  	  gPE_ND_DNR0_O18;
PE_ND_ND0_REG_TYPE_O18_T   	  gPE_ND_ND1_O18;
PE_ND_DNR0_REG_TYPE_O18_T  	  gPE_ND_DNR1_O18;
PE_ND_PSP_REG_TYPE_O18_T  	  gPE_ND_PSP_O18;
PE_SHP_REG_TYPE_O18_T     	  gPE_SHP_O18;
PE_SHP_PSP_REG_TYPE_O18_T	  gPE_SHP_PSP_O18;
PE_SHP_PSP_GAIN_REG_TYPE_O18_T	  gPE_SHP_PSP_GAIN_O18;
PE_SHP_OSD_REG_TYPE_O18_T     	  gPE_SHP_OSD_O18;
PE_SR_CHR_SHP_REG_TYPE_O18_T  gPE_SR_CHR_SHP_O18;
PE_SR_2K_SHP_REG_TYPE_O18_T   gPE_SR_2K_SHP_O18;
PE_SR_4K_SHP_REG_TYPE_O18_T   gPE_SR_4K_SHP_O18;
PE_SR_2K_MSC_Y_REG_TYPE_O18_T gPE_SR_2K_MSC_Y_O18;
PE_SR_MSC_Y_REG_TYPE_O18_T    gPE_SR_MSC_Y_O18;
PE_SR_MSC_C_REG_TYPE_O18_T    gPE_SR_MSC_C_O18;
PE_VCP_DISP_REG_TYPE_O18_T 	  gPE_VCP_DISP_O18;
PE_TOP_IMX_REG_TYPE_O18_T  	  gPE_TOP_IMX_O18;
//PE_IPP_REG_TYPE_O18_T      	  gPE_IPP_O18;
PE_HDR10_REG_TYPE_O18_T       gPE_HDR10_O18;
PE_HDR10_REG_TYPE_O18_T       gPE_HDR10_2_O18;
PE_S2H_REG_TYPE_O18_T         gPE_S2H_O18;
PE_S2H_REG_TYPE_O18_T         gPE_S2H_2_O18;
PE_DDR_DB_REG_TYPE_O18_T      gPE_DDR_DB_O18;
volatile UINT32			 	*gpe_vsd_ctrl_block_o18;
volatile UINT32				*gPE_HDR_DDR_O18;
volatile UINT32				*gPE_DDR_BLK_APL_O18 =NULL;


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
int PE_REG_O18_InitPhyToVirt(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	int size;
	if(PE_KDRV_VER_O18)
	{
		/* shdw */
		gPE_CVI_A_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O18_T));
		gPE_CVI_B_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O18_T));
		gPE_CVI_C_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O18_T));
		gPE_CVI_D_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_O18_T));
		gPE_HDMI_A_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_O18_T));
		gPE_HDMI_B_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_O18_T));
		gPE_HDMI_C_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_O18_T));
		gPE_HDMI_D_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_HDMI_REG_O18_T));
		gPE_LED_RP_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_LED_RP_REG_O18_T));
		gPE_TOP_IMX_O18.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_TOP_IMX_REG_O18_T));
		gPE_GSC_Y_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_Y_REG_O18_T));
		gPE_GSC_C_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_C_REG_O18_T));
		gPE_ND_ND0_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_REG_O18_T));/*ND0 equal to ND1 */
		gPE_ND_DNR0_O18.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR0_REG_O18_T));/*DNR0 equal to DNR1 */
		gPE_ND_ND1_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_REG_O18_T));
		gPE_ND_DNR1_O18.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR0_REG_O18_T));
		gPE_ND_PSP_O18.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_PSP_REG_O18_T));
		gPE_VCP_DISP_O18.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DISP_REG_O18_T));
		gPE_SHP_O18.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_SHP_REG_O18_T));
		gPE_SHP_PSP_O18.shdw.addr       = (UINT32 *)OS_KMalloc(sizeof(PE_SHP_PSP_REG_O18_T));
		gPE_SHP_PSP_GAIN_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_SHP_PSP_GAIN_REG_O18_T));
		gPE_SHP_OSD_O18.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_SHP_OSD_REG_O18_T));
		gPE_SR_CHR_SHP_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_CHR_SHP_REG_O18_T));
		gPE_SR_2K_SHP_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHP_REG_O18_T));
		gPE_SR_4K_SHP_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_4K_SHP_REG_O18_T));
		gPE_SR_2K_MSC_Y_O18.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_MSC_Y_REG_O18_T));
		gPE_SR_MSC_Y_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_MSC_Y_REG_O18_T));
		gPE_SR_MSC_C_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_SR_MSC_C_REG_O18_T));
		gPE_CE_PE1_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CE_PE1_REG_O18_T));
		gPE_CO_PE1_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CO_PE1_REG_O18_T));
		gPE_HDR10_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_HDR10_REG_O18_T));
		gPE_HDR10_2_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_HDR10_REG_O18_T));
		gPE_S2H_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_S2H_REG_O18_T));
		gPE_S2H_2_O18.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_S2H_REG_O18_T));
		gPE_DDR_DB_O18.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_O18_T));
		gPE_LED_DCNT_O18.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_LED_DCNT_REG_O18_T));
		/* phys */
		gPE_CVI_A_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_CVI_A_BASE,    sizeof(PE_CVI_REG_O18_T));
		gPE_CVI_B_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_CVI_B_BASE,    sizeof(PE_CVI_REG_O18_T));
		gPE_CVI_C_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_CVI_C_BASE,    sizeof(PE_CVI_REG_O18_T));
		gPE_CVI_D_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_CVI_D_BASE,    sizeof(PE_CVI_REG_O18_T));
		gPE_HDMI_A_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_HDMI_A_BASE,   sizeof(PE_HDMI_REG_O18_T));
		gPE_HDMI_B_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_HDMI_B_BASE,   sizeof(PE_HDMI_REG_O18_T));
		gPE_HDMI_C_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_HDMI_C_BASE,   sizeof(PE_HDMI_REG_O18_T));
		gPE_HDMI_D_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_HDMI_D_BASE,   sizeof(PE_HDMI_REG_O18_T));
		gPE_LED_RP_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_LED_RP_BASE,   sizeof(PE_LED_RP_REG_O18_T));
		gPE_TOP_IMX_O18.phys.addr  	= (volatile UINT32 *)ioremap(PE_O18_IMX_BASE,      sizeof(PE_TOP_IMX_REG_O18_T));
		gPE_GSC_Y_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_GSC_Y_BASE,    sizeof(PE_GSC_Y_REG_O18_T));
		gPE_GSC_C_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_GSC_C_BASE,    sizeof(PE_GSC_C_REG_O18_T));
		gPE_ND_ND0_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_ND0_BASE,      sizeof(PE_ND_ND0_REG_O18_T));
		gPE_ND_DNR0_O18.phys.addr  	= (volatile UINT32 *)ioremap(PE_O18_DNR0_BASE,     sizeof(PE_ND_DNR0_REG_O18_T));;
		gPE_ND_ND1_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_ND1_BASE,      sizeof(PE_ND_ND0_REG_O18_T));
		gPE_ND_DNR1_O18.phys.addr  	= (volatile UINT32 *)ioremap(PE_O18_DNR1_BASE,     sizeof(PE_ND_DNR0_REG_O18_T));
		gPE_ND_PSP_O18.phys.addr  	= (volatile UINT32 *)ioremap(PE_O18_ND_PSP_BASE,     sizeof(PE_ND_PSP_REG_O18_T));
		gPE_VCP_DISP_O18.phys.addr 	= (volatile UINT32 *)ioremap(PE_O18_VCP_DISP_BASE, sizeof(PE_VCP_DISP_REG_O18_T));
		gPE_SHP_O18.phys.addr     	= (volatile UINT32 *)ioremap(PE_O18_P1_SHP_L_BASE, sizeof(PE_SHP_REG_O18_T));
		gPE_SHP_PSP_O18.phys.addr   = (volatile UINT32 *)ioremap(PE_O18_P1_SHP_PSP_BASE, sizeof(PE_SHP_PSP_REG_O18_T));
		gPE_SHP_PSP_GAIN_O18.phys.addr   = (volatile UINT32 *)ioremap(PE_O18_P1_SHP_PSP_GAIN_BASE, sizeof(PE_SHP_PSP_GAIN_REG_O18_T));
		gPE_SHP_OSD_O18.phys.addr     	= (volatile UINT32 *)ioremap(PE_O18_P1_SHP_OSD_BASE, sizeof(PE_SHP_OSD_REG_O18_T));
		gPE_SR_CHR_SHP_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_SR_CHR_SHP_BASE,   sizeof(PE_SR_CHR_SHP_REG_O18_T));
		gPE_SR_2K_SHP_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_SR_2K_SHP_BASE,   sizeof(PE_SR_2K_SHP_REG_O18_T));
		gPE_SR_4K_SHP_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_SR_4K_SHP_BASE,   sizeof(PE_SR_4K_SHP_REG_O18_T));
		#if 1
		gPE_SR_2K_MSC_Y_O18.phys.addr   = (volatile UINT32 *)ioremap(PE_O18_SR_2K_MSC_Y_BASE,   sizeof(PE_SR_2K_MSC_Y_REG_O18_T));
		gPE_SR_MSC_Y_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_SR_MSC_Y_BASE,   sizeof(PE_SR_MSC_Y_REG_O18_T));
		gPE_SR_MSC_C_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_SR_MSC_C_BASE,   sizeof(PE_SR_MSC_C_REG_O18_T));
		#endif
		gPE_CE_PE1_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_P1_CCO_E_BASE, sizeof(PE_CE_PE1_REG_O18_T));
		gPE_CO_PE1_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_P1_CCO_O_BASE, sizeof(PE_CO_PE1_REG_O18_T));
		gPE_HDR10_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_HDR10_BASE,    sizeof(PE_HDR10_REG_O18_T));
		gPE_HDR10_2_O18.phys.addr   = (volatile UINT32 *)ioremap(PE_O18_HDR10_2_BASE,    sizeof(PE_HDR10_REG_O18_T));
		gPE_S2H_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_S2H_BASE,    sizeof(PE_S2H_REG_O18_T));
		gPE_S2H_2_O18.phys.addr    	= (volatile UINT32 *)ioremap(PE_O18_S2H_2_BASE,    sizeof(PE_S2H_REG_O18_T));
		gpe_vsd_ctrl_block_o18    	= (volatile UINT32 *)ioremap(PE_O18_VSD_BASE,    sizeof(UINT32));
		size = PE_HDR_DDR_O18_TOTAL_SIZE;
		gPE_HDR_DDR_O18				= (volatile UINT32 *)vmap_phys(PE_HDR_DDR_O18_BASE_ADDR,size+PAGE_SIZE);
		PE_PRINT_NOTI("[HDR]v(%d), vmap base:0x%08x,size:0x%08x+0x%08x\n",\
			PE_HDR_DDR_O18_VERSION,PE_HDR_DDR_O18_BASE_ADDR,size,(UINT32)PAGE_SIZE);
		gPE_LED_DCNT_O18.phys.addr   	= (volatile UINT32 *)ioremap(PE_O18_LED_DCNT_BASE,   sizeof(PE_LED_DCNT_REG_O18_T));
	}
	else
	{
		PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
	}
	#endif /*PE_HW_O18_BRINGUP*/
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
int PE_REG_O18_FreePhyToVirt(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	if(PE_KDRV_VER_O18)
	{
		/* shdw */
		if (gPE_CVI_A_O18.shdw.addr   ) OS_Free((void *)gPE_CVI_A_O18.shdw.addr   );
		if (gPE_CVI_B_O18.shdw.addr   ) OS_Free((void *)gPE_CVI_B_O18.shdw.addr   );
		if (gPE_CVI_C_O18.shdw.addr   ) OS_Free((void *)gPE_CVI_C_O18.shdw.addr   );
		if (gPE_CVI_D_O18.shdw.addr   ) OS_Free((void *)gPE_CVI_D_O18.shdw.addr   );
		if (gPE_HDMI_A_O18.shdw.addr  ) OS_Free((void *)gPE_HDMI_A_O18.shdw.addr  );
		if (gPE_HDMI_B_O18.shdw.addr  ) OS_Free((void *)gPE_HDMI_B_O18.shdw.addr  );
		if (gPE_HDMI_C_O18.shdw.addr  ) OS_Free((void *)gPE_HDMI_C_O18.shdw.addr  );
		if (gPE_HDMI_D_O18.shdw.addr  ) OS_Free((void *)gPE_HDMI_D_O18.shdw.addr  );
		if (gPE_LED_RP_O18.shdw.addr  ) OS_Free((void *)gPE_LED_RP_O18.shdw.addr  );
		if (gPE_TOP_IMX_O18.shdw.addr ) OS_Free((void *)gPE_TOP_IMX_O18.shdw.addr );
		if (gPE_GSC_Y_O18.shdw.addr   ) OS_Free((void *)gPE_GSC_Y_O18.shdw.addr   );
		if (gPE_GSC_C_O18.shdw.addr   ) OS_Free((void *)gPE_GSC_C_O18.shdw.addr   );
		if (gPE_ND_ND0_O18.shdw.addr  ) OS_Free((void *)gPE_ND_ND0_O18.shdw.addr  );
		if (gPE_ND_DNR0_O18.shdw.addr ) OS_Free((void *)gPE_ND_DNR0_O18.shdw.addr );
		if (gPE_ND_ND1_O18.shdw.addr  ) OS_Free((void *)gPE_ND_ND1_O18.shdw.addr  );
		if (gPE_ND_DNR1_O18.shdw.addr ) OS_Free((void *)gPE_ND_DNR1_O18.shdw.addr );
		if (gPE_ND_PSP_O18.shdw.addr )  OS_Free((void *)gPE_ND_PSP_O18.shdw.addr );
		if (gPE_VCP_DISP_O18.shdw.addr) OS_Free((void *)gPE_VCP_DISP_O18.shdw.addr);
		if (gPE_SHP_O18.shdw.addr    ) OS_Free((void *)gPE_SHP_O18.shdw.addr    );
		if (gPE_SHP_PSP_O18.shdw.addr    ) OS_Free((void *)gPE_SHP_PSP_O18.shdw.addr    );
		if (gPE_SHP_PSP_GAIN_O18.shdw.addr    ) OS_Free((void *)gPE_SHP_PSP_GAIN_O18.shdw.addr    );
		if (gPE_SHP_OSD_O18.shdw.addr    ) OS_Free((void *)gPE_SHP_OSD_O18.shdw.addr    );
		if (gPE_SR_CHR_SHP_O18.shdw.addr    ) OS_Free((void *)gPE_SR_CHR_SHP_O18.shdw.addr);
		if (gPE_SR_2K_SHP_O18.shdw.addr    ) OS_Free((void *)gPE_SR_2K_SHP_O18.shdw.addr  );
		if (gPE_SR_4K_SHP_O18.shdw.addr    ) OS_Free((void *)gPE_SR_4K_SHP_O18.shdw.addr  );
		if (gPE_SR_2K_MSC_Y_O18.shdw.addr ) OS_Free((void *)gPE_SR_2K_MSC_Y_O18.shdw.addr   );
		if (gPE_SR_MSC_Y_O18.shdw.addr    ) OS_Free((void *)gPE_SR_MSC_Y_O18.shdw.addr    );
		if (gPE_SR_MSC_C_O18.shdw.addr    ) OS_Free((void *)gPE_SR_MSC_C_O18.shdw.addr    );
		if (gPE_CE_PE1_O18.shdw.addr  ) OS_Free((void *)gPE_CE_PE1_O18.shdw.addr  );
		if (gPE_CO_PE1_O18.shdw.addr  ) OS_Free((void *)gPE_CO_PE1_O18.shdw.addr  );
		if (gPE_DDR_DB_O18.shdw.addr    ) OS_Free((void *)gPE_DDR_DB_O18.shdw.addr    );
		if (gPE_HDR10_O18.shdw.addr   ) OS_Free((void *)gPE_HDR10_O18.shdw.addr   );
		if (gPE_HDR10_2_O18.shdw.addr   ) OS_Free((void *)gPE_HDR10_2_O18.shdw.addr   );
		if (gPE_S2H_O18.shdw.addr   ) OS_Free((void *)gPE_S2H_O18.shdw.addr   );
		if (gPE_S2H_2_O18.shdw.addr   ) OS_Free((void *)gPE_S2H_2_O18.shdw.addr   );
		if (gPE_LED_DCNT_O18.shdw.addr  ) OS_Free((void *)gPE_LED_DCNT_O18.shdw.addr  );
		/* phys */
		if (gPE_CE_PE1_O18.phys.addr  ) iounmap((void *)gPE_CE_PE1_O18.phys.addr  );
		if (gPE_CO_PE1_O18.phys.addr  ) iounmap((void *)gPE_CO_PE1_O18.phys.addr  );
		if (gPE_CVI_A_O18.phys.addr   ) iounmap((void *)gPE_CVI_A_O18.phys.addr   );
		if (gPE_CVI_B_O18.phys.addr   ) iounmap((void *)gPE_CVI_B_O18.phys.addr   );
		if (gPE_CVI_C_O18.phys.addr   ) iounmap((void *)gPE_CVI_C_O18.phys.addr   );
		if (gPE_CVI_D_O18.phys.addr   ) iounmap((void *)gPE_CVI_D_O18.phys.addr   );
		if (gPE_LED_RP_O18.phys.addr  ) iounmap((void *)gPE_LED_RP_O18.phys.addr  );
		if (gPE_VCP_DISP_O18.phys.addr) iounmap((void *)gPE_VCP_DISP_O18.phys.addr);
		if (gPE_TOP_IMX_O18.phys.addr ) iounmap((void *)gPE_TOP_IMX_O18.phys.addr );
		if (gPE_HDMI_A_O18.phys.addr  ) iounmap((void *)gPE_HDMI_A_O18.phys.addr  );
		if (gPE_HDMI_B_O18.phys.addr  ) iounmap((void *)gPE_HDMI_B_O18.phys.addr  );
		if (gPE_HDMI_C_O18.phys.addr  ) iounmap((void *)gPE_HDMI_C_O18.phys.addr  );
		if (gPE_HDMI_D_O18.phys.addr  ) iounmap((void *)gPE_HDMI_D_O18.phys.addr  );
		if (gPE_GSC_Y_O18.phys.addr   ) iounmap((void *)gPE_GSC_Y_O18.phys.addr   );
		if (gPE_GSC_C_O18.phys.addr   ) iounmap((void *)gPE_GSC_C_O18.phys.addr   );
		if (gPE_ND_ND0_O18.phys.addr  ) iounmap((void *)gPE_ND_ND0_O18.phys.addr  );
		if (gPE_ND_DNR0_O18.phys.addr ) iounmap((void *)gPE_ND_DNR0_O18.phys.addr );
		if (gPE_ND_ND1_O18.phys.addr  ) iounmap((void *)gPE_ND_ND1_O18.phys.addr  );
		if (gPE_ND_DNR1_O18.phys.addr ) iounmap((void *)gPE_ND_DNR1_O18.phys.addr );
		if (gPE_ND_PSP_O18.phys.addr ) iounmap((void *)gPE_ND_PSP_O18.phys.addr );
		if (gPE_SHP_O18.phys.addr     ) iounmap((void *)gPE_SHP_O18.phys.addr     );
		if (gPE_SHP_PSP_O18.phys.addr ) iounmap((void *)gPE_SHP_PSP_O18.phys.addr );
		if (gPE_SHP_PSP_GAIN_O18.phys.addr ) iounmap((void *)gPE_SHP_PSP_GAIN_O18.phys.addr );
		if (gPE_SHP_OSD_O18.phys.addr     ) iounmap((void *)gPE_SHP_OSD_O18.phys.addr     );
		if (gPE_SR_CHR_SHP_O18.phys.addr  ) iounmap((void *)gPE_SR_CHR_SHP_O18.phys.addr);
		if (gPE_SR_2K_SHP_O18.phys.addr  ) iounmap((void *)gPE_SR_2K_SHP_O18.phys.addr  );
		if (gPE_SR_4K_SHP_O18.phys.addr  ) iounmap((void *)gPE_SR_4K_SHP_O18.phys.addr  );
		if (gPE_SR_2K_MSC_Y_O18.phys.addr) iounmap((void *)gPE_SR_2K_MSC_Y_O18.phys.addr);
		if (gPE_SR_MSC_Y_O18.phys.addr   ) iounmap((void *)gPE_SR_MSC_Y_O18.phys.addr  );
		if (gPE_SR_MSC_C_O18.phys.addr   ) iounmap((void *)gPE_SR_MSC_C_O18.phys.addr  );
		if (gPE_HDR10_O18.phys.addr   ) iounmap((void *)gPE_HDR10_O18.phys.addr   );
		if (gPE_HDR10_2_O18.phys.addr   ) iounmap((void *)gPE_HDR10_2_O18.phys.addr   );
		if (gPE_S2H_O18.phys.addr   ) iounmap((void *)gPE_S2H_O18.phys.addr   );
		if (gPE_S2H_2_O18.phys.addr   ) iounmap((void *)gPE_S2H_2_O18.phys.addr   );
		if (gpe_vsd_ctrl_block_o18) 	iounmap((void *)gpe_vsd_ctrl_block_o18);
		if (gPE_DDR_BLK_APL_O18)		vunmap_phys((void *)gPE_DDR_BLK_APL_O18);
		if (gPE_HDR_DDR_O18)			vunmap_phys((void *)gPE_HDR_DDR_O18);
		if (gPE_LED_DCNT_O18.phys.addr  ) iounmap((void *)gPE_LED_DCNT_O18.phys.addr  );
		PE_PRINT_NOTI("[HDR]vunmap idx.& [PE]vunmap blk_apl.\n");
	}
	else
	{
		PE_PRINT_INFO("nothing to do.\n");	ret = RET_OK;
	}
	#endif /*PE_HW_O18_BRINGUP*/
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
int PE_REG_O18_WD(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	UINT32 recvPhysAddr;
	UINT32 currPhysAddr = 0;
	void *pVirtAddr = 0;
	do{
		if(PE_KDRV_VER_O18)
		{
			recvPhysAddr = addr;
			if		(recvPhysAddr <= 0x6000) recvPhysAddr += PE_O18_DE_BASE;
			else if (recvPhysAddr <= 0xffff) recvPhysAddr += PE_O18_DE_BASE;
			currPhysAddr = recvPhysAddr;
			/* 4byte align to access hw register */
			currPhysAddr >>= 2;
			currPhysAddr <<= 2;

			if ((currPhysAddr&0xff000000)==PE_O18_DE_BASE)	pVirtAddr = ioremap(currPhysAddr, 0x8);
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
		if ((currPhysAddr&0xff000000)==PE_O18_DE_BASE)	iounmap(pVirtAddr);
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
int PE_REG_O18_WrAllocatedAddr(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		if(PE_KDRV_VER_O18)
		{
			if((addr)>=PE_O18_ND0_OFST && (addr)<(PE_O18_ND0_OFST+sizeof(PE_ND_ND0_REG_O18_T)))
			{
				*((UINT32 *)(gPE_ND_ND0_O18.phys.addr+((addr-PE_O18_ND0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_ND1_OFST && (addr)<(PE_O18_ND1_OFST+sizeof(PE_ND_ND0_REG_O18_T)))
			{
				*((UINT32 *)(gPE_ND_ND1_O18.phys.addr+((addr-PE_O18_ND1_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_DNR0_OFST && (addr)<(PE_O18_DNR0_OFST+sizeof(PE_ND_DNR0_REG_O18_T)))
			{
				*((UINT32 *)(gPE_ND_DNR0_O18.phys.addr+((addr-PE_O18_DNR0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_DNR1_OFST && (addr)<(PE_O18_DNR1_OFST+sizeof(PE_ND_DNR0_REG_O18_T)))
			{
				*((UINT32 *)(gPE_ND_DNR1_O18.phys.addr+((addr-PE_O18_DNR1_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_ND_PSP_OFST && (addr)<(PE_O18_ND_PSP_OFST+sizeof(PE_ND_PSP_REG_O18_T)))
			{
				*((UINT32 *)(gPE_ND_PSP_O18.phys.addr+((addr-PE_O18_ND_PSP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_SR_CHR_SHP_OFST && (addr)<(PE_O18_SR_CHR_SHP_OFST+sizeof(PE_SR_CHR_SHP_REG_O18_T)))
			{
				*((UINT32 *)(gPE_SR_CHR_SHP_O18.phys.addr+((addr-PE_O18_SR_CHR_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_SR_2K_SHP_OFST && (addr)<(PE_O18_SR_2K_SHP_OFST+sizeof(PE_SR_2K_SHP_REG_O18_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHP_O18.phys.addr+((addr-PE_O18_SR_2K_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_SR_4K_SHP_OFST && (addr)<(PE_O18_SR_4K_SHP_OFST+sizeof(PE_SR_4K_SHP_REG_O18_T)))
			{
				*((UINT32 *)(gPE_SR_4K_SHP_O18.phys.addr+((addr-PE_O18_SR_4K_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_P1_SHP_L_OFST && (addr)<(PE_O18_P1_SHP_L_OFST+sizeof(PE_SHP_REG_O18_T)))
			{
				*((UINT32 *)(gPE_SHP_O18.phys.addr+((addr-PE_O18_P1_SHP_L_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_P1_SHP_PSP_OFST && (addr)<(PE_O18_P1_SHP_PSP_OFST+sizeof(PE_SHP_PSP_REG_O18_T)))
			{
				*((UINT32 *)(gPE_SHP_PSP_O18.phys.addr+((addr-PE_O18_P1_SHP_PSP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_P1_SHP_PSP_GAIN_OFST && (addr)<(PE_O18_P1_SHP_PSP_GAIN_OFST+sizeof(PE_SHP_PSP_GAIN_REG_O18_T)))
			{
				*((UINT32 *)(gPE_SHP_PSP_GAIN_O18.phys.addr+((addr-PE_O18_P1_SHP_PSP_GAIN_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_P1_SHP_OSD_OFST && (addr)<(PE_O18_P1_SHP_OSD_OFST+sizeof(PE_SHP_OSD_REG_O18_T)))
			{
				*((UINT32 *)(gPE_SHP_OSD_O18.phys.addr+((addr-PE_O18_P1_SHP_OSD_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_GSC_Y_OFST && (addr)<(PE_O18_GSC_Y_OFST+sizeof(PE_GSC_Y_REG_O18_T)))
			{
				*((UINT32 *)(gPE_GSC_Y_O18.phys.addr+((addr-PE_O18_GSC_Y_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_GSC_C_OFST && (addr)<(PE_O18_GSC_C_OFST+sizeof(PE_GSC_C_REG_O18_T)))
			{
				*((UINT32 *)(gPE_GSC_C_O18.phys.addr+((addr-PE_O18_GSC_C_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_IMX_OFST && (addr)<(PE_O18_IMX_OFST+sizeof(PE_TOP_IMX_REG_O18_T)))
			{
				*((UINT32 *)(gPE_TOP_IMX_O18.phys.addr+((addr-PE_O18_IMX_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_O18_LED_DCNT_OFST && (addr)<(PE_O18_LED_DCNT_OFST+sizeof(PE_LED_DCNT_REG_O18_T)))
			{
				*((UINT32 *)(gPE_LED_DCNT_O18.phys.addr+((addr-PE_O18_LED_DCNT_OFST)/sizeof(UINT32)))) = value;
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
	#endif /*PE_HW_O18_BRINGUP*/
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
UINT32 PE_REG_O18_RD(UINT32 addr)
{
	UINT32 value = 0x0;
	UINT32 recvPhysAddr;
	UINT32 currPhysAddr = 0;
	void *pVirtAddr = 0;
	do{
		if(PE_KDRV_VER_O18)
		{
			recvPhysAddr = addr;
			if		(recvPhysAddr <= 0x6000) recvPhysAddr += PE_O18_DE_BASE;
			else if (recvPhysAddr <= 0xffff) recvPhysAddr += PE_O18_DE_BASE;
			currPhysAddr = recvPhysAddr;
			/* 4byte align to access hw register */
			currPhysAddr >>= 2;
			currPhysAddr <<= 2;

			if ((currPhysAddr&0xff000000)==PE_O18_DE_BASE)	pVirtAddr = (void *)ioremap(currPhysAddr, 0x8);
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
		if ((currPhysAddr&0xff000000)==PE_O18_DE_BASE)	iounmap(pVirtAddr);
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
int PE_REG_O18_WrReg(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 addr,data;
	do {
		CHECK_KNULL(pstParams);
		PE_REG_O18_CHECK_CODE(pstParams->size!=2,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		if(PE_KDRV_VER_O18)
		{
			addr = pstParams->data[0];
			data = pstParams->data[1];
			ret = PE_REG_O18_WD(addr,data);
			PE_REG_O18_CHECK_CODE(ret,break,"[%s,%d] PE_REG_O18_WD() error.\n",__F__,__L__);
			PE_PRINT_DEBUG("set : addr:0x%x, data:0x%x\n",addr,data);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");
		}
	} while(0);
	#endif /*PE_HW_O18_BRINGUP*/
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
int PE_REG_O18_RdReg(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 addr;
	do{
		CHECK_KNULL(pstParams);
		PE_REG_O18_CHECK_CODE(pstParams->size!=2,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		if(PE_KDRV_VER_O18)
		{
			addr = pstParams->data[0];
			pstParams->data[1] = PE_REG_O18_RD(addr);
			PE_PRINT_DEBUG("get : addr:0x%x, data:0x%x\n",addr,pstParams->data[1]);
		}
		else
		{
			PE_PRINT_INFO("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
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
int PE_REG_O18_SetTraceTable(const char* fn,
							UINT32 line,
							char *tbl,
							UINT32 ofst)
{
    int ret = RET_OK;
	char str[PE_TRACE_STR_SIZE];
	do{
		CHECK_KNULL(tbl);
		snprintf(str, PE_TRACE_STR_SIZE, "[%s,%d]%s(+ 0x%x)", fn, line, tbl, ofst);
		ret = PE_INF_O18_SetTraceDataBuf(str);
		PE_REG_O18_CHECK_CODE(ret, break, \
			"[%s,%d] PE_INF_O18_SetTraceDataBuf() error.\n",__F__,__L__);
	}while (0);
	return ret;
}

