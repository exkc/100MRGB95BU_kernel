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

/** @file pe_reg_m23.c
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

#include "pe_hw_m23.h"
#include "pe_reg_m23.h"
#include "pe_inf_m23.h"
#include "pe_hdr_ddr_m23.h"
#include "pe_hdr_hw_m23.h"

#ifdef INCLUDE_KDRV_BE
#include "ovi_hal.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

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
PE_CC_PE1_REG_TYPE_M23_T   gPE_CC_PE1_M23;
PE_CC2_PE1_REG_TYPE_M23_T  gPE_CC2_PE1_M23;
PE_CVI_REG_TYPE_M23_T      gPE_CVI_A_M23;
PE_CVI_REG_TYPE_M23_T      gPE_CVI_B_M23;
PE_GSC_Y_REG_TYPE_M23_T    gPE_GSC_Y_M23;
PE_GSC_C_REG_TYPE_M23_T    gPE_GSC_C_M23;
PE_ND_ND0_REG_TYPE_M23_T   gPE_ND_ND0_M23;
PE_ND_DNR0_REG_TYPE_M23_T  gPE_ND_DNR0_M23;
PE_ND0_VERI_REG_TYPE_M23_T gPE_ND0_VERI_M23;
PE_SHP_REG_TYPE_M23_T      gPE_SHP_M23;
PE_VSD_DTM_REG_TYPE_M23_T	 gPE_VSD_DTM_M23;
PE_SR_2K_SHP_REG_TYPE_M23_T  gPE_SR_2K_SHP_M23;
PE_VCP_DISP_REG_TYPE_M23_T 	 gPE_VCP_DISP_M23;
PE_VSD0_VERI_REG_TYPE_M23_T  gPE_VSD0_VERI_M23;
PE_DDR_DB_REG_TYPE_M23_T     gPE_DDR_DB_M23;
PE_TOP_IMX_REG_TYPE_M23_T    gPE_TOP_IMX_M23;
PE_CCO_VERI_REG_TYPE_M23_T   gPE_CCO_VERI_M23;
PE_SRE_VERI_REG_TYPE_M23_T   gPE_SRE_VERI_M23;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_REG_M23_HW_OPT_T _g_pe_reg_m23_disp_opt;

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef INCLUDE_KDRV_BE
static int PE_REG_M23_GetHwOpt(UINT32 *opt)
{
	PE_REG_M23_HW_OPT_T panel_mode;
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
	PE_INF_HW_M23_BACKUP_TRACE("[Opt]fr:%d,pt:%d,vx1:%d,ext%d,pr:%d",panel_mode.panel_frame_rate,\
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
int PE_REG_M23_InitPhyToVirt(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP

	/* shdw */
	gPE_CC_PE1_M23.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_CC_PE1_REG_M23_T));
	gPE_CC2_PE1_M23.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_CC2_PE1_REG_M23_T));
	gPE_CVI_A_M23.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M23_T));
	gPE_CVI_B_M23.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_CVI_REG_M23_T));
	gPE_GSC_Y_M23.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_Y_REG_M23_T));
	gPE_GSC_C_M23.shdw.addr    	= (UINT32 *)OS_KMalloc(sizeof(PE_GSC_C_REG_M23_T));
	gPE_ND_ND0_M23.shdw.addr   	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_ND0_REG_M23_T));/*ND0 equal to ND1 */
	gPE_ND_DNR0_M23.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_ND_DNR0_REG_M23_T));/*DNR0 equal to DNR1 */
	gPE_ND0_VERI_M23.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_ND0_VERI_REG_M23_T));
	gPE_TOP_IMX_M23.shdw.addr  	= (UINT32 *)OS_KMalloc(sizeof(PE_TOP_IMX_REG_M23_T));
	gPE_SHP_M23.shdw.addr     	= (UINT32 *)OS_KMalloc(sizeof(PE_SHP_REG_M23_T));
	gPE_VSD_DTM_M23.shdw.addr   = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_DTM_REG_M23_T));
	gPE_VCP_DISP_M23.shdw.addr 	= (UINT32 *)OS_KMalloc(sizeof(PE_VCP_DISP_REG_M23_T));
	gPE_VSD0_VERI_M23.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD0_VERI_REG_M23_T));
	gPE_SR_2K_SHP_M23.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SR_2K_SHP_REG_M23_T));
	gPE_DDR_DB_M23.shdw.addr    = (UINT32 *)OS_KMalloc(sizeof(PE_DDR_DB_SHDW_REG_M23_T));
	gPE_CCO_VERI_M23.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_CCO_VERI_REG_M23_T));
	gPE_SRE_VERI_M23.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(PE_SRE_VERI_REG_M23_T));


	/* phys */
	gPE_CC_PE1_M23.phys.addr   	= (volatile UINT32 *)ioremap(PE_M23_P1_CC_BASE, sizeof(PE_CC_PE1_REG_M23_T));
	gPE_CC2_PE1_M23.phys.addr   = (volatile UINT32 *)ioremap(PE_M23_P1_CC2_BASE, sizeof(PE_CC2_PE1_REG_M23_T));
	gPE_CVI_A_M23.phys.addr    	= (volatile UINT32 *)ioremap(PE_M23_CVI_A_BASE,    sizeof(PE_CVI_REG_M23_T));
	gPE_CVI_B_M23.phys.addr    	= (volatile UINT32 *)ioremap(PE_M23_CVI_B_BASE,    sizeof(PE_CVI_REG_M23_T));
	gPE_GSC_Y_M23.phys.addr    	= (volatile UINT32 *)ioremap(PE_M23_GSC_Y_BASE,    sizeof(PE_GSC_Y_REG_M23_T));
	gPE_GSC_C_M23.phys.addr    	= (volatile UINT32 *)ioremap(PE_M23_GSC_C_BASE,    sizeof(PE_GSC_C_REG_M23_T));
	gPE_ND_ND0_M23.phys.addr   	= (volatile UINT32 *)ioremap(PE_M23_ND0_BASE,      sizeof(PE_ND_ND0_REG_M23_T));
	gPE_ND_DNR0_M23.phys.addr  	= (volatile UINT32 *)ioremap(PE_M23_DNR0_BASE,     sizeof(PE_ND_DNR0_REG_M23_T));;
	gPE_ND0_VERI_M23.phys.addr  = (volatile UINT32 *)ioremap(PE_M23_ND0_VERI_BASE,  sizeof(PE_ND0_VERI_REG_M23_T));
	gPE_TOP_IMX_M23.phys.addr  	= (volatile UINT32 *)ioremap(PE_M23_IMX_BASE,      sizeof(PE_TOP_IMX_REG_M23_T));
	gPE_SHP_M23.phys.addr     	= (volatile UINT32 *)ioremap(PE_M23_P1_SHP_L_BASE, sizeof(PE_SHP_REG_M23_T));
	gPE_VSD_DTM_M23.phys.addr   = (volatile UINT32 *)ioremap(PE_M23_P1_VSD_DTM_BASE, sizeof(PE_VSD_DTM_REG_M23_T));
	gPE_VCP_DISP_M23.phys.addr 	= (volatile UINT32 *)ioremap(PE_M23_VCP_DISP_BASE, sizeof(PE_VCP_DISP_REG_M23_T));
	gPE_VSD0_VERI_M23.phys.addr = (volatile UINT32 *)ioremap(PE_M23_VSD0_VERI_BASE, sizeof(PE_VSD0_VERI_REG_M23_T));
	gPE_SR_2K_SHP_M23 .phys.addr= (volatile UINT32 *)ioremap(PE_M23_SR_2K_SHP_BASE,   sizeof(PE_SR_2K_SHP_REG_M23_T));
	gPE_DDR_DB_M23.phys.addr    = (volatile UINT32 *)vmap_phys(PE_M23_DDR_DB0_BASE,sizeof(PE_DDR_DB_PHYS_REG_M23_T)+PAGE_SIZE);
	gPE_CCO_VERI_M23.phys.addr  = (volatile UINT32 *)ioremap(PE_M23_CCO_VERI_BASE,   sizeof(PE_CCO_VERI_REG_M23_T));
	gPE_SRE_VERI_M23.phys.addr  = (volatile UINT32 *)ioremap(PE_M23_SRE_VERI_BASE,  sizeof(PE_SRE_VERI_REG_M23_T));

	_g_pe_reg_m23_disp_opt.u32Data = 0;
	#ifdef INCLUDE_KDRV_BE
	ret = PE_REG_M23_GetHwOpt(&(_g_pe_reg_m23_disp_opt.u32Data));
	#endif

	PE_PRINT_NOTI("[PE]vmap base:0x%08x,size:0x%08x+0x%08x\n",\
		PE_M23_DDR_DB0_BASE,(UINT32)sizeof(PE_DDR_DB_PHYS_REG_M23_T),(UINT32)PAGE_SIZE);
	PE_PRINT_NOTI("[PE]vmap base:0x%08x,size:0x%08x+0x%08x\n",\
		PE_LGSR_DDR_M23_BASE_ADDR,(UINT32)sizeof(PE_LGSR_DDR_DB_PHYS_REG_M23_T),(UINT32)PAGE_SIZE);

	#endif /*PE_HW_M23_BRINGUP*/

	PE_HDR_HW_M23_InitPhyToVirt();

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
int PE_REG_M23_FreePhyToVirt(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP

	/* shdw */
	if (gPE_CC_PE1_M23.shdw.addr  ) OS_Free((void *)gPE_CC_PE1_M23.shdw.addr  );
	if (gPE_CC2_PE1_M23.shdw.addr ) OS_Free((void *)gPE_CC2_PE1_M23.shdw.addr );
	if (gPE_CVI_A_M23.shdw.addr   ) OS_Free((void *)gPE_CVI_A_M23.shdw.addr   );
	if (gPE_CVI_B_M23.shdw.addr   ) OS_Free((void *)gPE_CVI_B_M23.shdw.addr   );
	if (gPE_GSC_Y_M23.shdw.addr   ) OS_Free((void *)gPE_GSC_Y_M23.shdw.addr   );
	if (gPE_GSC_C_M23.shdw.addr   ) OS_Free((void *)gPE_GSC_C_M23.shdw.addr   );
	if (gPE_ND_ND0_M23.shdw.addr  ) OS_Free((void *)gPE_ND_ND0_M23.shdw.addr  );
	if (gPE_ND_DNR0_M23.shdw.addr ) OS_Free((void *)gPE_ND_DNR0_M23.shdw.addr );
	if (gPE_ND0_VERI_M23.shdw.addr) OS_Free((void *)gPE_ND0_VERI_M23.shdw.addr);
	if (gPE_TOP_IMX_M23.shdw.addr ) OS_Free((void *)gPE_TOP_IMX_M23.shdw.addr );
	if (gPE_SHP_M23.shdw.addr     ) OS_Free((void *)gPE_SHP_M23.shdw.addr     );
	if (gPE_VSD_DTM_M23.shdw.addr ) OS_Free((void *)gPE_VSD_DTM_M23.shdw.addr );
	if (gPE_VCP_DISP_M23.shdw.addr) OS_Free((void *)gPE_VCP_DISP_M23.shdw.addr);
	if (gPE_VSD0_VERI_M23.shdw.addr) OS_Free((void *)gPE_VSD0_VERI_M23.shdw.addr);
	if (gPE_SR_2K_SHP_M23.shdw.addr) OS_Free((void *)gPE_SR_2K_SHP_M23.shdw.addr);
	if (gPE_DDR_DB_M23.shdw.addr   ) OS_Free((void *)gPE_DDR_DB_M23.shdw.addr   );
	if (gPE_CCO_VERI_M23.shdw.addr ) OS_Free((void *)gPE_CCO_VERI_M23.shdw.addr );
	if (gPE_SRE_VERI_M23.shdw.addr)  OS_Free((void *)gPE_SRE_VERI_M23.shdw.addr);

	/* phys */
	if (gPE_CC_PE1_M23.phys.addr  ) iounmap((void *)gPE_CC_PE1_M23.phys.addr  );
	if (gPE_CC2_PE1_M23.phys.addr ) iounmap((void *)gPE_CC2_PE1_M23.phys.addr );
	if (gPE_CVI_A_M23.phys.addr   ) iounmap((void *)gPE_CVI_A_M23.phys.addr   );
	if (gPE_CVI_B_M23.phys.addr   ) iounmap((void *)gPE_CVI_B_M23.phys.addr   );
	if (gPE_GSC_Y_M23.phys.addr   ) iounmap((void *)gPE_GSC_Y_M23.phys.addr   );
	if (gPE_GSC_C_M23.phys.addr   ) iounmap((void *)gPE_GSC_C_M23.phys.addr   );
	if (gPE_ND_ND0_M23.phys.addr  ) iounmap((void *)gPE_ND_ND0_M23.phys.addr  );
	if (gPE_ND_DNR0_M23.phys.addr ) iounmap((void *)gPE_ND_DNR0_M23.phys.addr );
	if (gPE_ND0_VERI_M23.phys.addr) iounmap((void *)gPE_ND0_VERI_M23.phys.addr);
	if (gPE_TOP_IMX_M23.phys.addr ) iounmap((void *)gPE_TOP_IMX_M23.phys.addr );
	if (gPE_SHP_M23.phys.addr     ) iounmap((void *)gPE_SHP_M23.phys.addr     );
	if (gPE_VSD_DTM_M23.phys.addr ) iounmap((void *)gPE_VSD_DTM_M23.phys.addr );
	if (gPE_VCP_DISP_M23.phys.addr) iounmap((void *)gPE_VCP_DISP_M23.phys.addr);
	if (gPE_VSD0_VERI_M23.phys.addr) iounmap((void *)gPE_VSD0_VERI_M23.phys.addr);
	if (gPE_SR_2K_SHP_M23.phys.addr) iounmap((void *)gPE_SR_2K_SHP_M23.phys.addr);
	if (gPE_DDR_DB_M23.phys.addr)   vunmap_phys((void *)gPE_DDR_DB_M23.phys.addr);
	if (gPE_CCO_VERI_M23.phys.addr) iounmap((void *)gPE_CCO_VERI_M23.phys.addr);
	if (gPE_SRE_VERI_M23.phys.addr) iounmap((void *)gPE_SRE_VERI_M23.phys.addr);

	PE_PRINT_NOTI("[PE]vunmap blk_apl\n");

	#endif /*PE_HW_M23_BRINGUP*/

	PE_HDR_HW_M23_FreePhyToVirt();

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
int PE_REG_M23_WrAllocatedAddr(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		if(PE_KDRV_VER_M23)
		{
			if((addr)>=PE_M23_ND0_OFST && (addr)<(PE_M23_ND0_OFST+sizeof(PE_ND_ND0_REG_M23_T)))
			{
				*((UINT32 *)(gPE_ND_ND0_M23.phys.addr+((addr-PE_M23_ND0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M23_DNR0_OFST && (addr)<(PE_M23_DNR0_OFST+sizeof(PE_ND_DNR0_REG_M23_T)))
			{
				*((UINT32 *)(gPE_ND_DNR0_M23.phys.addr+((addr-PE_M23_DNR0_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M23_ND0_VERI_OFST && (addr)<(PE_M23_ND0_VERI_OFST+sizeof(PE_ND0_VERI_REG_M23_T)))
			{
				*((UINT32 *)(gPE_ND0_VERI_M23.phys.addr+((addr-PE_M23_ND0_VERI_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M23_SR_2K_SHP_OFST && (addr)<(PE_M23_SR_2K_SHP_OFST+sizeof(PE_SR_2K_SHP_REG_M23_T)))
			{
				*((UINT32 *)(gPE_SR_2K_SHP_M23.phys.addr+((addr-PE_M23_SR_2K_SHP_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M23_P1_SHP_L_OFST && (addr)<(PE_M23_P1_SHP_L_OFST+sizeof(PE_SHP_REG_M23_T)))
			{
				*((UINT32 *)(gPE_SHP_M23.phys.addr+((addr-PE_M23_P1_SHP_L_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M23_P1_VSD_DTM_OFST && (addr)<(PE_M23_P1_VSD_DTM_OFST+sizeof(PE_VSD_DTM_REG_M23_T)))
			{
				*((UINT32 *)(gPE_VSD_DTM_M23.phys.addr+((addr-PE_M23_P1_VSD_DTM_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M23_GSC_Y_OFST && (addr)<(PE_M23_GSC_Y_OFST+sizeof(PE_GSC_Y_REG_M23_T)))
			{
				*((UINT32 *)(gPE_GSC_Y_M23.phys.addr+((addr-PE_M23_GSC_Y_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M23_GSC_C_OFST && (addr)<(PE_M23_GSC_C_OFST+sizeof(PE_GSC_C_REG_M23_T)))
			{
				*((UINT32 *)(gPE_GSC_C_M23.phys.addr+((addr-PE_M23_GSC_C_OFST)/sizeof(UINT32)))) = value;
			}
			else if((addr)>=PE_M23_IMX_OFST && (addr)<(PE_M23_IMX_OFST+sizeof(PE_TOP_IMX_REG_M23_T)))
			{
				*((UINT32 *)(gPE_TOP_IMX_M23.phys.addr+((addr-PE_M23_IMX_OFST)/sizeof(UINT32)))) = value;
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
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * PE_REG_M23_GetDispOpt
 * see PE_REG_M23_HW_OPT_T
 *
 * @param   void
 * @return  UINT32
 * @see
 * @author
 */
PE_REG_M23_HW_OPT_T PE_REG_M23_GetDispOpt(void)
{
	return _g_pe_reg_m23_disp_opt;
}

