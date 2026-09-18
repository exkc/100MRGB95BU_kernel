/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.18
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
#define USE_DE_CVI_ACCESS_REGISTER_ON_MCU_PART
#undef	USE_DE_DOES_RESET_IN_SUSPEND_RESUME
#undef  USE_FRAME_COPY_TO_NFS_FILE

#ifdef USE_VIDEO_FOR_FPGA
#undef INCLUDE_KDRV_PE
#endif
/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <asm/io.h>

#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <asm/uaccess.h>

#include "base_types.h"
#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"
#include "hma_alloc.h"

#ifdef USE_KDRV_CODES_FOR_O18
#include "de_kapi.h"
#include "de_def.h"
#include "de_prm_def.h"
#include "de_hal_def.h"
#include "de_cfg.h"
#include "de_drv.h"

#include "de_cfg_o18.h"
#include "de_ipc_def_o18.h"
#include "de_int_def_o18.h"
#include "de_reg_def_o18.h"
#include "de_reg_o18.h"
#include "de_prm_o18.h"

#include "de_ipc_reg_o18.h"		  // 0x4e00
#include "de_ctr_reg_o18.h"		  // 0x0000
#include "de_cvi_reg_o18.h"		  // 0x0200
#include "de_vbi_reg_o18.h"		  // 0x0f00
#include "de_cvd_reg_o18.h"		  //
#include "de_atp_reg_o18.h"		  //

#ifdef USE_CTOP_CODES_FOR_O18
#include "../sys/sys_regs.h"
#endif

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define  SIZE_OF_IPC_FOR_CPU 16
#define USE_VIDEO_MCU_RUN_IN_DDR0   0x00000000
#define USE_VIDEO_MCU_ROM_BASE_ADDR 0x30000000
#define USE_VIDEO_MCU_ROM_FW_OFFSET 0x00000000
#define USE_VIDEO_MCU1_ROM_FW_OFFSET 0x00400000

#define DE_DDR_FIRMWARE_TAG_COUNT    2

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define DE_REG_WR(address,data)   \
		gMapped_address=(volatile UINT32 *)ioremap_nocache(address, sizeof(UINT32));\
		do{\
			if(gMapped_address == NULL) break;\
			*gMapped_address = data;\
			iounmap((void *)gMapped_address);\
		}while(0);\

#define DE_REG_RD(address,data)   \
		gMapped_address = (volatile UINT32 *)ioremap_nocache(address, sizeof(UINT32));\
		do{\
			if(gMapped_address == NULL) {data = 0; break;}\
			data = (unsigned int)*gMapped_address;\
			iounmap((void *)gMapped_address);\
		}while(0);\

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
#define NUM_OF_CVI_FIR_COEF 8
#define NUM_WIN_MAX	2

#define DE_REG_O18_DDR_1_5_GB	(1)
#define DE_REG_O18_DDR_2_0_GB	(0)

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_GFX
#include "gfx_cfg.h"
#endif
#ifdef INCLUDE_KDRV_BE
#include "../be/be_cfg.h"
extern BE_MEM_CFG_T *gpBeMem;
#endif
#ifdef INCLUDE_KDRV_PE
#include "pe_cco_reg_o18.h"
#include "pe_shp_reg_o18.h"
extern PE_CO_PE1_REG_TYPE_O18_T gPE_CO_PE1_O18;
extern PE_SHP_REG_TYPE_O18_T gPE_SHP_O18;
#endif
/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/
DE_IPC_REG_O18_T gDE_IPC_O18;
DE_CVI_REG_O18_T gDE_CVI_O18;
DE_CVC_REG_O18_T gDE_CVC_O18;
DE_IMX_REG_O18_T gDE_IMX_O18;
DE_SUB_REG_O18_T gDE_SUB_O18;
DE_VSD_REG_O18_T gDE_VSD_O18;
DE_CCO_REG_O18_T gDE_CCO_O18;
DE_ND0_REG_O18_T gDE_ND0_O18;
DE_VBI_REG_O18_T gDE_VBI_O18;
DE_CVD_REG_O18_T gDE_CVD_O18;
DE_HDR_REG_O18_T gDE_HDR_O18;

volatile LX_DE_VDEC_IPC_REG_T *gDE_VDEC_O18[4];


LX_DE_IN_SRC_T	g_WinsrcMap_O18[NUM_WIN_MAX] = { LX_DE_IN_SRC_MVI,	LX_DE_IN_SRC_MVI};
UINT32			g_WinsrcPort_O18[NUM_WIN_MAX] = { 0, 0};
UINT32          g_HdmiPort_O18[NUM_WIN_MAX] = { 0, };
UINT32          g_QuadWin_O18  = 0;

LX_DE_OPER_CONFIG_T		g_SrcOperType_O18 = LX_DE_OPER_ONE_WIN;
LX_DE_SUB_OPER_CONFIG_T	g_SrcSubOperType_O18 = LX_DE_SUB_OPER_OFF;
UINT16						g_SrcOperCtrlFlag_O18 = 0;
UINT16						g_SrcSubOperCtrlFlag_O18 = 0;
UINT32                  g_FwBase_O18 = VIDEO_O18_FRAME_DDR_BASE;

LX_DE_DISPLAY_DEVICE_T	g_Display_type_O18 = LX_DE_DIS_DEV_LCD;
LX_DE_DISPLAY_MIRROR_T	g_Display_mirror_O18 = LX_DE_DIS_MIRROR_OFF;
LX_DE_PANEL_TYPE_T 		g_Display_size_O18 = LX_PANEL_TYPE_3840;
LX_DE_FRC_PATH_T		g_Frc_type_O18 = LX_DE_FRC_PATH_EXTERNAL;
LX_DE_3D_CTRL_T			g_Trid_type_O18 = LX_DE_3D_CTRL_ON;

LX_DE_PANEL_TYPE_T      g_Diplay_type_from_loader = LX_PANEL_TYPE_MAX;
UINT32                  g_Zero_delay_mode = 0;
UINT32                  g_model_type_from_ctop = 0;

typedef struct {
	 SRC_O18_MAP_DATA    src;
	 BOOLEAN         valid;
	 CVI_DATA_IN_SEL_O18 cvi_0;
	 CVI_DATA_IN_SEL_O18 cvi_1;
	 CVI_DATA_IN_SEL_O18 cvi_2;
	 CVI_DATA_IN_SEL_O18 cvi_3;
} LX_DE_SRC_CONFIG;

LX_DE_SRC_CONFIG sSrc_map_O18[2][LX_DE_MULTI_IN_MAX + 1] =
{
	// A0
	{	/* src_map       valid   cvi_0       cvi_1        cvi_2       cvi_3 */
		{  SRC_O18_CVD_ADC,  TRUE,   CLK_CVD_O18,    CLK_NONE_O18,    CLK_ADC_O18,    CLK_NONE_O18},
		{  SRC_O18_CVD_HDA,  TRUE,   CLK_CVD_O18,    CLK_NONE_O18,    CLK_HDA_O18,    CLK_HDA_O18 },
		{  SRC_O18_CVD_HDC,  TRUE,   CLK_CVD_O18,    CLK_NONE_O18,    CLK_HDC_O18,    CLK_HDC_O18 },
		{  SRC_O18_CVD_CVD,  TRUE,   CLK_CVD_O18,    CLK_NONE_O18,    CLK_CVD_O18,    CLK_NONE_O18},
		{  SRC_O18_ADC_CVD,  TRUE,   CLK_ADC_O18,    CLK_NONE_O18,    CLK_CVD_O18,    CLK_NONE_O18},
		{  SRC_O18_ADC_HDA,  TRUE,   CLK_ADC_O18,    CLK_NONE_O18,    CLK_HDA_O18,    CLK_HDA_O18 },
		{  SRC_O18_ADC_HDC,  TRUE,   CLK_ADC_O18,    CLK_NONE_O18,    CLK_HDC_O18,    CLK_HDC_O18 },
		{  SRC_O18_ADC_ADC,  TRUE,   CLK_ADC_O18,    CLK_NONE_O18,    CLK_ADC_O18,    CLK_NONE_O18},
		{  SRC_O18_HDA_CVD,  TRUE,   CLK_HDA_O18,    CLK_HDA_O18,     CLK_HDA_O18,    CLK_CVD_O18 },
		{  SRC_O18_HDA_ADC,  TRUE,   CLK_HDA_O18,    CLK_HDA_O18,     CLK_ADC_O18,    CLK_NONE_O18},
		{  SRC_O18_HDA_HDC,  TRUE,   CLK_HDA_O18,    CLK_HDA_O18,     CLK_HDC_O18,    CLK_HDC_O18 },
		{  SRC_O18_HDA_HDA,  TRUE,   CLK_HDA_O18,    CLK_HDA_O18,     CLK_HDA_O18,    CLK_HDA_O18 },
		{  SRC_O18_HDC_CVD,  TRUE,   CLK_HDC_O18,    CLK_HDC_O18,     CLK_CVD_O18,    CLK_NONE_O18},
		{  SRC_O18_HDC_ADC,  TRUE,   CLK_HDC_O18,    CLK_HDC_O18,     CLK_ADC_O18,    CLK_NONE_O18},
		{  SRC_O18_HDC_HDA,  TRUE,   CLK_HDC_O18,    CLK_HDC_O18,     CLK_HDA_O18,    CLK_HDA_O18 },
		{  SRC_O18_HDC_HDC,  TRUE,   CLK_HDC_O18,    CLK_HDC_O18,     CLK_HDC_O18,    CLK_HDC_O18 }
	},
	// B0
	{
	}
};

static volatile unsigned int *gMapped_address;

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_O18_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
#ifdef USE_CTOP_CODES_FOR_O18
static DE_DPLL_SET_T sDisplayPll_O18[] = {
	{ DCLK_61_875	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_65		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_66_462	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_66_528	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_36_818	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_36_855	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_54		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_54_054	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_74_1758	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_74_25	,{ 0 ,0x2 ,0x3 } },
	{ DCLK_80_109	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_80_190	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_81		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_27		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_13_5		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_27_027	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_13_5135	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_148_3516 ,{ 0 ,0x2 ,0x2 } },
	{ DCLK_148_5	,{ 0x4 ,0xA ,0x2 } },
	{ DCLK_85_86	,{ 0 ,0x2 ,0x2 } },
};
#endif
static BOOLEAN sbDeUdMode = FALSE;
static LX_DE_CVI_SRC_TYPE_T sCviSrcType;
static LX_DE_MULTI_WIN_SRC_T sDeMultiWinSrc = {0,0};
static LX_DE_CH_MEM_T *gpAdrPreW;
#ifdef O18_PQE_NEW_MEM

#else
static LX_DE_MEM_CFG_T *gpMemCfgVT;
static LX_DE_MEM_CFG_T *gpMemCfgBT;
#endif
static LX_DE_CH_MEM_T *gpMemCfgDeFW_M0;
static LX_DE_MEM_CFG_T *gpMemCfgHDR;

#ifdef O18_PQE_NEW_MEM
static LX_DE_CH_MEM_T *gpMemCfgDeFW_M1;
static LX_DE_CH_MEM_T *gpMemCfgFrm_M1;
static LX_DE_CH_MEM_T *gpMemCfgFrm_M2;
static LX_DE_CH_MEM_T *gpMemCfgBT_M1;
static LX_DE_CH_MEM_T *gpMemCfgBT_M2;
static LX_DE_CH_MEM_T *gpMemCfgVT_M1;
static LX_DE_CH_MEM_T *gpMemCfgVT_M2;
#endif
static LX_DE_IPC_SYSTEM_NEW_T  g_Mem_Info = { 0 };

static int o18_de_debug_mem = 0;
module_param(o18_de_debug_mem, int, 0644);
/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/
static int DE_REG_GetHWOpt(UINT32 *opt)
{
	LX_DE_IPC_SYSTEM_MODEL_T panel_mode;
	char hw_opt[24];

	panel_mode.u32Data = 0;

	if(RET_OK==OS_ScanKernelCmdline("hwopt=%s", hw_opt))
	{
		if (hw_opt[1] == '1') // Vx1 5Byte
		{
			panel_mode.vx1_byte  = LX_DE_IPC_PANEL_VX1_5BYTE;
		}

		if ((hw_opt[4] == '0') // NO FRC
			|| ((hw_opt[17] != '0') && (hw_opt[17] != '1'))) // EXT FRC
		{
			panel_mode.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_60Hz;

			if ((hw_opt[17] != '0') && (hw_opt[17] != '1'))
			{
				panel_mode.external_chip = LX_DE_IPC_EXTERNAL_CHIP_USE;
			}
		}

		if (hw_opt[12] == '1') // OLED
		{
			panel_mode.panel_type = LX_DE_IPC_PANEL_TYPE_OLED;
		}
	}
	else
	{
		/* 2k/4k model 구분
		(4k 60Hz : 0xC917D004[9:7] - 1, 4k 120Hz : 0xC917D004[9:7] - 0)
		(2k 60Hz : 0xC917D004[9:7] - 3, 2k 120Hz : 0xC917D004[9:7] - 2)
		*/
#ifdef	USE_CTOP_CODES_FOR_O18
		CTOP_CTRL_O18A0_RdFL(CTRL_TCON, crg_tcon01);
		CTOP_CTRL_O18A0_Rd01(CTRL_TCON, crg_tcon01, tcon_pix2_clk_sel, g_model_type_from_ctop);
#endif

		if (g_model_type_from_ctop == 1 || g_model_type_from_ctop == 3)
		{
			panel_mode.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_60Hz;
		}
	}

	if (RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
	{
		if (!strncmp(hw_opt,"hdmi",4))
		{
			panel_mode.panel_frame_rate = LX_DE_IPC_PANEL_FRAME_RATE_60Hz;
		}

		if (!strncmp(hw_opt,"4byte",5))
		{
			panel_mode.vx1_byte  = LX_DE_IPC_PANEL_VX1_4BYTE;
		}
		else if (!strncmp(hw_opt,"5byte",5))
		{
			panel_mode.vx1_byte  = LX_DE_IPC_PANEL_VX1_5BYTE;
		}
	}

	if(RET_OK==OS_ScanKernelCmdline("dispopts=%s", hw_opt))
	{
		if (strstr(hw_opt,"y18"))
		{
			panel_mode.panel_carry_over = LX_DE_IPC_PANEL_CARRY_OVER;
		}
	}

	*opt = panel_mode.u32Data;

	return RET_OK;
}

int DE_REG_O18_InitAddrSwitch(void)
{
	gMapped_address = 0;
	return 0;
}

#if 0	//ready(?)
UINT32 DE_REG_O18_GetSizeOpt(void)
{
	UINT32 size_opt = DE_REG_O18_DDR_2_0_GB;
	char char_size_opt, model_opt[32];
	memset(model_opt, 0x0, 32);
	if (RET_OK == OS_ScanKernelCmdline("modelopt=%s",model_opt))
	{
		char_size_opt = model_opt[14];
		/* check DDR SIZE. '0' = 2GB, '1' = 1.5GB */
		switch(char_size_opt)
		{
			case 0x31: 			size_opt=DE_REG_O18_DDR_1_5_GB;break;
			case 0x30: default:	size_opt=DE_REG_O18_DDR_2_0_GB;break;
		}
	}
	DE_ERROR("DE_REG_O18_GetSizeOpt()~~~~\n");
	return size_opt;
}
#endif
/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize Reigerter Physical Address to Virtual Address and Make Shadow Register
 *
 * @return RET_OK(0)
 */
int DE_REG_O18_InitPHY2VIRT(void)
{
	int ret = RET_OK;

	gDE_IPC_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_IPC_REG_O18A0_T));
	gDE_IPC_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_IPC_REG_O18_BASE, sizeof(DE_IPC_REG_O18A0_T));
	gDE_VBI_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_VBI_REG_O18A0_T));
	gDE_VBI_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_VBI_REG_O18_BASE, sizeof(DE_VBI_REG_O18A0_T));
	gDE_CVD_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVD_REG_O18A0_T));
	gDE_CVD_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_CVD_REG_O18_BASE, sizeof(DE_CVD_REG_O18A0_T));
	gDE_CVC_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVC_REG_O18A0_T));
	gDE_CVC_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_CVC_REG_O18_BASE, sizeof(DE_CVC_REG_O18A0_T));
	gDE_CVI_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVI_REG_O18A0_T));
	gDE_CVI_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_CVI_REG_O18_BASE, sizeof(DE_CVI_REG_O18A0_T));
	gDE_VSD_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_VSD_REG_O18A0_T));
	gDE_VSD_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_VSD_REG_O18_BASE, sizeof(DE_VSD_REG_O18A0_T));
	gDE_CCO_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CCO_REG_O18A0_T));
	gDE_CCO_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_CCO_REG_O18_BASE, sizeof(DE_CCO_REG_O18A0_T));
	gDE_IMX_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_IMX_REG_O18A0_T));
	gDE_IMX_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_IMX_REG_O18_BASE, sizeof(DE_IMX_REG_O18A0_T));
	gDE_ND0_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_ND0_REG_O18A0_T));
	gDE_ND0_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_ND0_REG_O18_BASE, sizeof(DE_ND0_REG_O18A0_T));
	gDE_SUB_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_SUB_REG_O18A0_T));
	gDE_SUB_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_SUB_REG_O18_BASE, sizeof(DE_SUB_REG_O18A0_T));
	gDE_HDR_O18.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_HDR_REG_O18A0_T));
	gDE_HDR_O18.phys.addr  = (volatile UINT32 *)ioremap(DE_HDR_REG_O18_BASE, sizeof(DE_HDR_REG_O18A0_T));
	gDE_VDEC_O18[0] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_O18_BASE + 0x00, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_O18[1] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_O18_BASE + 0x40, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_O18[2] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_O18_BASE + 0x80, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_O18[3] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_O18_BASE + 0xC0, sizeof(LX_DE_VDEC_IPC_REG_T));

	/* 2k/4k model 구분
	(4k 60Hz : 0xC917D004[9:7] - 1, 4k 120Hz : 0xC917D004[9:7] - 0)
	(2k 60Hz : 0xC917D004[9:7] - 3, 2k 120Hz : 0xC917D004[9:7] - 2)
	*/
#ifdef	USE_CTOP_CODES_FOR_O18
	CTOP_CTRL_O18A0_RdFL(CTRL_TCON, crg_tcon01);
	CTOP_CTRL_O18A0_Rd01(CTRL_TCON, crg_tcon01, tcon_pix2_clk_sel, g_model_type_from_ctop);
#endif

#if 0 // platform_init.c 2GB ADV
	LX_MEMCFG_ENTRY_EX(gMemCfgO18[0], MEM_DESC(DE_PREW)),	/* DE PREW_M0 */

	LX_MEMCFG_ENTRY(gMemCfgO18[1]),                         /* DE_FRM_M1 */
	LX_MEMCFG_ENTRY(gMemCfgO18[2]),                         /* DE_FRM_M2 */

	LX_MEMCFG_ENTRY_EX(gMemCfgO18[6], MEM_DESC(BT)),        /* DE_BT_M1 */
	LX_MEMCFG_ENTRY_EX(gMemCfgO18[7], MEM_DESC(BT)), 	    /* DE_BT_M2 */

	LX_MEMCFG_ENTRY_EX(gMemCfgO18[8], MEM_DESC(VT)),		/* DE_VT_M1 */
	LX_MEMCFG_ENTRY_EX(gMemCfgO18[9], MEM_DESC(VT)),		/* DE_VT_M2 */
#endif

	gpMemCfgDeFW_M0 = &gMemCfgDeFW[1];
	gpMemCfgHDR  = &gMemCfgHDR[1];

#ifdef O18_PQE_NEW_MEM
	gpDeMem         = &gMemCfgDe[3];
	gpMemCfgDeFW_M1 = &gMemCfgDeFW[2];
	gpAdrPreW      = (LX_DE_CH_MEM_T *)&gMemCfgO18[0];
	gpMemCfgFrm_M1 = (LX_DE_CH_MEM_T *)&gMemCfgO18[1];
	gpMemCfgFrm_M2 = (LX_DE_CH_MEM_T *)&gMemCfgO18[2];
	gpMemCfgBT_M1  = (LX_DE_CH_MEM_T *)&gMemCfgO18[6];
	gpMemCfgBT_M2  = (LX_DE_CH_MEM_T *)&gMemCfgO18[7];
	gpMemCfgVT_M1  = (LX_DE_CH_MEM_T *)&gMemCfgO18[8];
	gpMemCfgVT_M2  = (LX_DE_CH_MEM_T *)&gMemCfgO18[9];
#else
	gpDeMem      = &gMemCfgDe[3];
	gpDeMemC     = &gMemCfgDeFrameC[0];
	gpMemCfgVT   = &gMemCfgVT_CMA[3];
	gpMemCfgBT   = &gMemCfgBT_CMA[1];
	gpAdrPreW    = &gMemCfgDePreW[0];

	DE_NOTI("Frame base [Y]0x%08x [C]0x%08x", gpDeMem->frame_base, gpDeMemC->frame_base);
	DE_NOTI("BT base/size 0x%08x/%dMB", gpMemCfgBT->frame_base, gpMemCfgBT->frame_size/1024/1024);
	DE_NOTI("VT base/size 0x%08x/%dMB", gpMemCfgVT->frame_base, gpMemCfgVT->frame_size/1024/1024);
#endif
	DE_NOTI("panel_type[ %d ] - 0:4k@120/1:4k@60/2:2k@120/3:2k@60", g_model_type_from_ctop);

	DE_NOTI("DE_IMX_REG_O18_BASE : 0x%08X", DE_IMX_REG_O18_BASE);
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Free memory alocated in Shadow Register
 *
 * @return RET_OK(0)
 */
int DE_REG_O18_FreePHY2VIRT(void)
{
	OS_Free((void *)gDE_IPC_O18.shdw.addr);
	if (gDE_IPC_O18.phys.addr) iounmap((void *)gDE_IPC_O18.phys.addr);
	OS_Free((void *)gDE_VBI_O18.shdw.addr);
	if (gDE_VBI_O18.phys.addr) iounmap((void *)gDE_VBI_O18.phys.addr);
	OS_Free((void *)gDE_CVD_O18.shdw.addr);
	if (gDE_CVD_O18.phys.addr) iounmap((void *)gDE_CVD_O18.phys.addr);
	OS_Free((void *)gDE_CVC_O18.shdw.addr);
	if (gDE_CVC_O18.phys.addr) iounmap((void *)gDE_CVC_O18.phys.addr);
	OS_Free((void *)gDE_CVI_O18.shdw.addr);
	if (gDE_CVI_O18.phys.addr) iounmap((void *)gDE_CVI_O18.phys.addr);
	OS_Free((void *)gDE_VSD_O18.shdw.addr);
	if (gDE_VSD_O18.phys.addr) iounmap((void *)gDE_VSD_O18.phys.addr);
	OS_Free((void *)gDE_CCO_O18.shdw.addr);
	if (gDE_CCO_O18.phys.addr) iounmap((void *)gDE_CCO_O18.phys.addr);
	OS_Free((void *)gDE_IMX_O18.shdw.addr);
	if (gDE_IMX_O18.phys.addr) iounmap((void *)gDE_IMX_O18.phys.addr);
	OS_Free((void *)gDE_ND0_O18.shdw.addr);
	if (gDE_ND0_O18.phys.addr) iounmap((void *)gDE_ND0_O18.phys.addr);
	OS_Free((void *)gDE_SUB_O18.shdw.addr);
	if (gDE_SUB_O18.phys.addr) iounmap((void *)gDE_SUB_O18.phys.addr);
	OS_Free((void *)gDE_HDR_O18.shdw.addr);
	if (gDE_HDR_O18.phys.addr) iounmap((void *)gDE_HDR_O18.phys.addr);
	if (gDE_VDEC_O18[0]) iounmap((void *)gDE_VDEC_O18[0]);
	if (gDE_VDEC_O18[1]) iounmap((void *)gDE_VDEC_O18[1]);
	if (gDE_VDEC_O18[2]) iounmap((void *)gDE_VDEC_O18[2]);
	if (gDE_VDEC_O18[3]) iounmap((void *)gDE_VDEC_O18[3]);
	return RET_OK;
}

 /**
 * @callgraph
 * @callergraph
 *
 * @brief Get Status of Interrupt which is one of either MCU or CPU
 *
 * @param ipcType [IN] one of either MCU and CPU
 * @param pStatus [OUT] status pointer of Interrupt
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_O18_GetStatusReg(UINT32 mcu_id,           \
                            VIDEO_IPC_TYPE_T ipcType,\
                            UINT32 *pStatus)
{
	int ret = RET_OK;

	switch (ipcType) {
		case VIDEO_IPC_MCU :
		case VIDEO_DMA_MCU :
		case VIDEO_JPG_MCU :
		case VIDEO_WEL_MCU :
		case VIDEO_WER_MCU :
			DE_IPC_O18_RdFL(int_intr_status);
			*pStatus = DE_IPC_O18_Rd(int_intr_status);
			break;
		case VIDEO_IPC_CPU :
		case VIDEO_DMA_CPU :
		case VIDEO_JPG_CPU :
		case VIDEO_WEL_CPU :
		case VIDEO_WER_CPU :
			DE_IPC_O18_RdFL(ext_intr_status);
			*pStatus = DE_IPC_O18_Rd(ext_intr_status);
			break;
		default :
			BREAK_WRONG(ipcType);
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make inerrupt status for watch dog either happen or clear
 *
 * @param turnOn [IN] determine to turn On or Off
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_WDG_O18_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn)
{
	if (turnOn) {
		DE_IPC_O18_FLWf(ext_intr_event, wdg_interrupt_event, 1);
	} else {
		DE_IPC_O18_FLWf(ext_intr_clear, wdg_interrupt_clear, 1);
	}

	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make interrupt be happen according to ipcType which is either of MCU or CPU
 *
 * @param ipcType [IN] one of either MCU and CPU
 * @param turnOn  [IN] maket Interrupt enable or clear
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_O18_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn)
{
	int ret = RET_OK;

	turnOn &= 0x1;
	switch (ipcType) {
		case VIDEO_IPC_MCU :
			if (turnOn) {
				DE_IPC_O18_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_IPC_CPU :
			if (turnOn) {
				DE_IPC_O18_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_MCU :
			if (turnOn) {
				DE_IPC_O18_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_CPU :
			if (turnOn) {
				DE_IPC_O18_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_MCU :
			if (turnOn) {
				DE_IPC_O18_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_CPU :
			if (turnOn) {
				DE_IPC_O18_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_MCU :
			if (turnOn) {
				DE_IPC_O18_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_CPU :
			if (turnOn) {
				DE_IPC_O18_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_MCU :
			if (turnOn) {
				DE_IPC_O18_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_CPU :
			if (turnOn) {
				DE_IPC_O18_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_MCU :
			if (turnOn) {
				DE_IPC_O18_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_CPU :
			if (turnOn) {
				DE_IPC_O18_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O18_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			}
			break;
		default :
			BREAK_WRONG(ipcType);
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make interrupt be happen according to ipcType which is either of MCU or CPU
 *
 * @param ipcType [IN] one of either MCU and CPU
 * @param turnOn  [IN] maket Interrupt enable or clear
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_O18_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus)
{
	int ret = RET_OK;

	switch (ipcType) {
		case VIDEO_IPC_MCU :
			DE_IPC_O18_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_IPC_CPU :
			DE_IPC_O18_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DMA_MCU :
			DE_IPC_O18_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DMA_CPU :
			DE_IPC_O18_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_JPG_MCU :
			DE_IPC_O18_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_JPG_CPU :
			DE_IPC_O18_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_USB_MCU :
			DE_IPC_O18_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_USB_CPU :
			DE_IPC_O18_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WEL_MCU :
			DE_IPC_O18_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WEL_CPU :
			DE_IPC_O18_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WER_MCU :
			DE_IPC_O18_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WER_CPU :
			DE_IPC_O18_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DHDR_CPU :
			DE_IPC_O18_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_DHDR_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DELAY_CPU :
			DE_IPC_O18_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_CB_INTERRUPT_ARM_BIT, 1));
			break;
		default :
			BREAK_WRONG(ipcType);
			break;
	}
	return ret;
}

int DE_REG_O18_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status)
{
	int ret = RET_OK;

#ifdef INCLUDE_KDRV_PE
	static UINT16 prev_mute[2];
	UINT16 curr_mute[2];
	UINT32 data;
	UINT32 i = win_id;
	PE_SHP_O18_RdFL(shp_fsw_ctrl_03);
	data = PE_SHP_O18_Rd(shp_fsw_ctrl_03);

	//for(i=0;i<2;i++)
	{
		curr_mute[i] = (UINT16)((data >> (16 * i)) & 0xFFFF);
		if(curr_mute[i] == 0 && curr_mute[i] != prev_mute[i])
		{
			DE_NOTI("@@@ scaler_local_mute____OFF win[%d]\n", i);
		}
		else if(curr_mute[i] > 0 && curr_mute[i] != prev_mute[i])
		{
			DE_NOTI("@@@ scaler_local_mute____ON win[%d] val[%d]\n", i, curr_mute[i]);
		}
		prev_mute[i] = curr_mute[i];
		*mute_status = curr_mute[i]?1:0;
	}
#endif
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Register
 *
 * @param addr [IN] accessing for register
 * @param value [IN] acccesing for register
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_WD(void *addr, UINT32 value)
{
	int ret = RET_OK;
	void *recvAddr;
	void *currAddr = 0;
	UINT32 currValue;
	UINT32 nextValue;
	uintptr_t dBit;
	uintptr_t wBit;
	void *virtAddr = 0;
	do{
		recvAddr = addr;
		if		((uintptr_t)recvAddr <= 0x6000) recvAddr = (void *)((uintptr_t)recvAddr + (uintptr_t)DTVSOC_DE_O18_BASE);
		else if ((uintptr_t)recvAddr <= 0xffff) recvAddr = (void *)((uintptr_t)recvAddr + (uintptr_t)DTVSOC_DE_O18_BASE);
		currAddr = recvAddr;
		currAddr = (void *)((uintptr_t)currAddr >> 2);
		currAddr = (void *)((uintptr_t)currAddr << 2);

		if (((uintptr_t)currAddr&(uintptr_t)0xff000000)==DTVSOC_DE_O18_BASE)	virtAddr = (void *)ioremap((uintptr_t)currAddr, 0x8);
		else										virtAddr = (void *)vmap_phys((uintptr_t)currAddr, 0x8);

		if(virtAddr == NULL) break;

		if (currAddr == recvAddr) {
			REG_WD(virtAddr, value);
			break;
		}
		currValue = REG_RD(virtAddr);
		nextValue = REG_RD((virtAddr+4));

		dBit = ((uintptr_t)recvAddr - (uintptr_t)currAddr)<<3;
		wBit = (32 - dBit);

		currValue  = GET_BITS(currValue ,0	  ,dBit);
		currValue += GET_PVAL(value		,dBit ,wBit);

		nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
		nextValue += GET_BITS(value		,0	  ,dBit);
		REG_WD(virtAddr		,currValue);
		REG_WD((virtAddr+4) ,nextValue);
	}while(0);
	if (virtAddr && currAddr)
	{
		if (((uintptr_t)currAddr&(uintptr_t)0xff000000)==DTVSOC_DE_O18_BASE)	iounmap((void *)virtAddr);
		else										vunmap_phys((void *)virtAddr);
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Register
 *
 * @param addr [IN] accessing for register
 *
 * @return value of register
 */
UINT32 DE_REG_O18_RD(void *addr)
{
	UINT32 value = 0x0;
	void *recvAddr;
	void *currAddr = 0;
	UINT32 nextValue;
	uintptr_t dBit;
	uintptr_t wBit;
	void *virtAddr = 0;
	do{
		recvAddr = addr;
		if		((uintptr_t)recvAddr <= 0x6000) recvAddr = (void *)((uintptr_t)recvAddr + (uintptr_t)DTVSOC_DE_O18_BASE);
		else if ((uintptr_t)recvAddr <= 0xffff) recvAddr = (void *)((uintptr_t)recvAddr + (uintptr_t)DTVSOC_DE_O18_BASE);
		currAddr = recvAddr;
		currAddr = (void *)((uintptr_t)currAddr >> 2);
		currAddr = (void *)((uintptr_t)currAddr << 2);

		if (((uintptr_t)currAddr&(uintptr_t)0xff000000)==DTVSOC_DE_O18_BASE)	virtAddr = (void *)ioremap((uintptr_t)currAddr, 0x8);
		else										virtAddr = (void *)vmap_phys((uintptr_t)currAddr, 0x8);

		if(virtAddr == NULL) break;

		value = REG_RD(virtAddr);
		if (currAddr == recvAddr) break;

		nextValue = REG_RD(virtAddr+4);
		dBit = ((uintptr_t)recvAddr - (uintptr_t)currAddr)<<3;
		wBit = (32 - dBit);
		value  = GET_BITS(value, dBit, wBit);
		value += GET_PVAL(nextValue, wBit, dBit);
	}while(0);
	if (virtAddr && currAddr)
	{
		if (((uintptr_t)currAddr&(uintptr_t)0xff000000)==DTVSOC_DE_O18_BASE)	iounmap((void *)virtAddr);
		else										vunmap_phys((void *)virtAddr);
	}

	return value;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set Frame rate of Display
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetFrRate(DE_DPLL_CLK_T dclk)
{
	int ret = RET_OK;
#ifdef USE_CTOP_CODES_FOR_O18
#ifdef USE_KDRV_CODES_FOR_O18
	DE_DPLL_DIV_T *pDisplayPll = NULL;
	int i;

	do {
		for (i=0;i<ARRAY_SIZE(sDisplayPll_O18);i++) {
			if (sDisplayPll_O18[i].clk != dclk) continue;
			pDisplayPll =  &sDisplayPll_O18[i].div;
			break;
		}
		CHECK_KNULL(pDisplayPll);
#if 0 //default  de = 148.5 MHz(?) , dpll = 297MHz(?)
		CTOP_CTRL_O18A0_RdFL(FMS, ctr42);
		CTOP_CTRL_O18A0_Wr01(FMS, ctr42, disp_nsc_ctrl, pDisplayPll->dpllM);
		CTOP_CTRL_O18A0_Wr01(FMS, ctr42, disp_npc_ctrl, pDisplayPll->dpllN);
		CTOP_CTRL_O18A0_WrFL(FMS, ctr42);
#endif
	} while (0);
#endif
#endif
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get Frame rate of Display
 *
 * @param pFrRate [OUT] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_GetFrRate(LX_DE_FR_RATE_T *pstParams)
{
	int ret = RET_OK;

	pstParams->isForceFreeRun = FALSE;
	pstParams->fr_rate = 30;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set background color (non-active region color).
 *
 * @param [IN] structure pointer to carry infomation about non-active region color
 *
 * @return RET_OK(0)
 */
int DE_REG_O18_SetBgColor(LX_DE_COLOR_T *pBackColor)
{
	int ret = RET_OK;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set blank color of selected window
 *
 * @param pWinBlank [IN] structure pointer to carry information about window Id, whether Turn On or Off and blank color
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank)
{
	int ret = RET_OK;

	return ret;
}

BOOLEAN DE_REG_O18_CheckIrq4Vsync(UINT32 mcu_id)
{
	int ret;
	O18A0_INTR_CPU_FLAG_T		 intr_flag_cpu;
	//O18A0_SUB_INTR_REG_T		 sub_intr_reg;
	O18A0_HDR_CTRL_INTR_CPU_REG_T hdr_intr_reg;
	O18A0_IMX_INTR_REG_T          imx_intr_reg;
	UINT32 videoIntrDe;
	BOOLEAN vsyncIrq = 0;

	do {
		vsyncIrq = 0;
		ret = DE_REG_O18_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_FUNC, &videoIntrDe);
		if (ret) break;

		intr_flag_cpu  = *(O18A0_INTR_CPU_FLAG_T	*)&videoIntrDe;

		if(intr_flag_cpu.imx_mcu_intr_cpu)
		{
			ret = DE_REG_O18_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_IMX, &videoIntrDe);
			if (ret) break;
			imx_intr_reg = *(O18A0_IMX_INTR_REG_T *)&videoIntrDe;
			if(!imx_intr_reg.intr_i5_intr_pulse) break;
			vsyncIrq = 1;
		}
		if(intr_flag_cpu.hdr_mcu_intr_cpu)
		{
			ret = DE_REG_O18_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_HDR, &videoIntrDe);
			if (ret) break;
			hdr_intr_reg = *(O18A0_HDR_CTRL_INTR_CPU_REG_T *)&videoIntrDe;
			if(!hdr_intr_reg.i5_src_pulse) break;
			vsyncIrq = 1;
		}
		if (intr_flag_cpu.cvi_mcu_intr_cpu)
		{
			ret = DE_REG_O18_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_CVI, &videoIntrDe);
			if (ret) break;
		}

#if 0
		//if (!intr_flag_cpu.sub_mcu_intr_cpu) break;
		if (0)//intr_flag_cpu.sub_mcu_intr_cpu) // not used
		{
			ret = DE_REG_O18_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_SUB, &videoIntrDe);
			sub_intr_reg = *(O18A0_SUB_INTR_REG_T *)&videoIntrDe;
			if (!sub_intr_reg.intr_i5_intr_pulse) break;
			vsyncIrq = 1;
		}
#endif
	} while (0);
	return vsyncIrq;
}

int DE_REG_O18_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus)
{
	int ret = RET_OK;
	UINT32 cvi1_field = 0;

	do {
		CHECK_KNULL(pVideoIrqStatus);
		switch (intrType) {
			case VIDEO_INTR_TYPE_CVI :
				DE_CVC_O18_RdFL(intr_reg);                 //CVI_CTRL INTR_CLR
				DE_CVC_O18_Rd01(intr_reg, intr_cvi1_field, cvi1_field);

				if(cvi1_field && (g_Zero_delay_mode==2))
				//if(g_Zero_delay_mode == 2)
				{
#if 0//def	USE_CTOP_CODES_FOR_O18
					UINT32 cvi_intr = 0;
					//DE_NOTI("###  Clok from DCO by cvi interrupt  ###");
					// [M16P_GAME_MODE_SET_DCO_SEL]
					// CTRL_CVI Setting -  SYN_CVI03 DCO IN DCO
					CTOP_CTRL_O18A0_RdFL(CTRL_CVI, syn_cvi03);
					CTOP_CTRL_O18A0_Rd01(CTRL_CVI, syn_cvi03, ctr01, cvi_intr);
					cvi_intr &= ~(1 << 0); // clear bit'0
					CTOP_CTRL_O18A0_WrFL(CTRL_CVI, syn_cvi03);
					// DISPLAY PLL Frequnecy changed (Input Freq(DCO) : 27Mhz, Output Freq : 594 / 74.25Mhz)
					DE_REG_O18_SetClockPath(0);

					// [M16P_GAME_MODE_INTRCLR_DCO_SEL]
					// Interrupt clear
					CTOP_CTRL_O18A0_RdFL(CTRL_CVI, syn_cvi03);  //CTRL_CVI INTR_CLR
					CTOP_CTRL_O18A0_Rd01(CTRL_CVI, syn_cvi03, ctr01, cvi_intr);
					cvi_intr |= (1 << 7);
					CTOP_CTRL_O18A0_Wr01(CTRL_CVI, syn_cvi03, ctr01, cvi_intr);
					CTOP_CTRL_O18A0_WrFL(CTRL_CVI, syn_cvi03);
#endif
				}

				DE_CVC_O18_Wr01(intr_reg, intr_cvi1_field, 1);
				DE_CVC_O18_WrFL(intr_reg);

				DE_NOTI("CVI interrupt from PQE HW     cvi1_field = %d", cvi1_field);
				break;
			case VIDEO_INTR_TYPE_IMX :
				DE_IMX_O18_RdFL(intr_reg);
				*pVideoIrqStatus = DE_IMX_O18_Rd(intr_reg);
				DE_IMX_O18_Wr(intr_reg, 0x20);
				//DE_IMX_O18_Wr01(intr_reg, intr_i5_intr_pulse, 1);
				DE_IMX_O18_WrFL(intr_reg);
				break;
			case VIDEO_INTR_TYPE_ND1 :
				break;
			case VIDEO_INTR_TYPE_HDR :
				DE_HDR_O18_RdFL(intr_cpu_reg);
				*pVideoIrqStatus = DE_HDR_O18_Rd(intr_cpu_reg);
				DE_HDR_O18_Wr01(intr_cpu_reg, i5_src_pulse, 1);
				DE_HDR_O18_WrFL(intr_cpu_reg);
				break;
			case VIDEO_INTR_TYPE_GSC :
				break;
			case VIDEO_INTR_TYPE_VSD :
				break;
			case VIDEO_INTR_TYPE_CCO :
				break;
			case VIDEO_INTR_TYPE_SUB :
				DE_SUB_O18_RdFL(intr_reg);
				*pVideoIrqStatus = DE_SUB_O18_Rd(intr_reg);
				DE_SUB_O18_Wr01(intr_reg, intr_i5_intr_pulse, 1);
				DE_SUB_O18_WrFL(intr_reg);
				break;
			case VIDEO_INTR_TYPE_FUNC :
				DE_IPC_O18_RdFL(intr_cpu_flag);
				*pVideoIrqStatus = DE_IPC_O18_Rd(intr_cpu_flag);
				break;
			default :
				BREAK_WRONG(intrType);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief copy frame buffer of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams)
{
	int ret = RET_OK;
#ifdef USE_FRAME_COPY_TO_NFS_FILE
    OS_FILE_T   fw_file;
    char filePath[200] = "/home/jaemo.kim/res/lglib/kdrv/";
    char fileName[200];
#endif
	LX_DE_GRAB_COLOR_T *pFrameColor = NULL;
	UINT8  *pFrameAddrY8 = NULL;
	UINT8  *pFrameAddrC8 = NULL;
	UINT8  *pFrameAddrY2 = NULL;
	UINT8  *pFrameAddrC2 = NULL;
	UINT16 phyFrameAddrY8;
	UINT16 phyFrameAddrC8;
	UINT16 phyFrameAddrY2;
	UINT16 phyFrameAddrC2;

	UINT32 grabX;
	UINT32 grabY;
	UINT32 grabW;
	UINT32 grabH;
	UINT32 frameW;
	UINT32 frameH;
	UINT32 offsetY;
	UINT32 offsetC;
	UINT32 startY;
	UINT32 pixelG8;
	UINT32 pixelB8;
	UINT32 pixelR8;
	UINT32 pixelG2;
	UINT32 pixelB2;
	UINT32 pixelR2;
	UINT8  pixelY2;
	UINT8  pixelC2;
	UINT32 x;
	UINT32 y;
	UINT32 posY;
	UINT32 posC;
	UINT32 divY;
	UINT32 remY;
	UINT32 divC;
	UINT32 remC;
	UINT32 framSize;
	UINT32 grabSize;
	UINT32 grabStepW;
	UINT32 bankPrewY;
	UINT32 bankPrewC;
	UINT32 bankOffsetY;
	UINT32 bankOffsetC;
	UINT32 grabBaseAddr;
	UINT32 smuxSample;
	UINT8 colorDepth;
	UINT32 phyAddrY8;
	UINT32 phyAddrC8;
	UINT32 phyAddrY2;
	UINT32 phyAddrC2;

	do {
		CHECK_KNULL(pstParams);

		phyFrameAddrY8 = GET_BITS(pstParams->region.realPixelGrabW ,16 ,16);
		phyFrameAddrY2 = GET_BITS(pstParams->region.realPixelGrabW ,0  ,16);
		phyFrameAddrC8 = GET_BITS(pstParams->region.realPixelGrabH ,16 ,16);
		phyFrameAddrC2 = GET_BITS(pstParams->region.realPixelGrabH ,0  ,16);

		grabW		   = GET_BITS(pstParams->region.pixelGrabW	   ,16 ,16);
		grabH		   = GET_BITS(pstParams->region.pixelGrabW	   ,0  ,16);
		grabX		   = GET_BITS(pstParams->region.pixelGrabH	   ,16 ,16);
		grabY		   = GET_BITS(pstParams->region.pixelGrabH	   ,0  ,16);
		frameW		   = GET_BITS(pstParams->region.pixelGrabX	   ,16 ,16);
		frameH		   = GET_BITS(pstParams->region.pixelGrabX	   ,0  ,16);

		smuxSample	   = GET_BITS(pstParams->region.pixelGrabY	   ,12 ,4);
		bankPrewY	   = GET_BITS(pstParams->region.colorSpace	   ,4  ,4);
		bankPrewC	   = GET_BITS(pstParams->region.colorSpace	   ,0  ,4);
		grabStepW	   = GET_BITS(pstParams->bReadOnOff			   ,16 ,16);
		colorDepth	   = GET_BITS(pstParams->region.colorDepth 	   ,0  ,4);

		grabSize = grabW  * grabH;
		framSize = frameW * frameH;
		if (!grabSize) break;
		if (!framSize) break;

		grabBaseAddr = GET_SVAL(pstParams->region.colorDepth,4,4,28);
		bankOffsetY  = bankPrewY * PIXEL_PER_BANK;
		bankOffsetC  = bankPrewC * PIXEL_PER_BANK;
		phyAddrY8 = (CONV_MEM_ROW2BYTE(phyFrameAddrY8) + bankOffsetY) | grabBaseAddr;
		phyAddrY2 = (CONV_MEM_ROW2BYTE(phyFrameAddrY2) + bankOffsetY) | grabBaseAddr;
		phyAddrC8 = (CONV_MEM_ROW2BYTE(phyFrameAddrC8) + bankOffsetC) | grabBaseAddr;
		phyAddrC2 = (CONV_MEM_ROW2BYTE(phyFrameAddrC2) + bankOffsetC) | grabBaseAddr;

		pFrameAddrY8 = (UINT8 *)vmap_phys(phyAddrY8, framSize);
		pFrameAddrY2 = (UINT8 *)vmap_phys(phyAddrY2, framSize/4);
		pFrameAddrC8 = (UINT8 *)vmap_phys(phyAddrC8, framSize*smuxSample);
		pFrameAddrC2 = (UINT8 *)vmap_phys(phyAddrC2, framSize/4*smuxSample);

#ifdef USE_FRAME_COPY_TO_NFS_FILE
		do {
			sprintf(fileName, "%sVideo_Prew__%dx%d.Y.img",filePath, frameW, frameH);
			DE_PRINT("Writing %s\n", fileName);
			if ( RET_OK != OS_OpenFile( &fw_file, fileName, O_CREAT|O_RDWR|O_LARGEFILE, 0666 ) )
			{
				DE_PRINT("<error> can't open fw_file (%s)\n", fileName);
				if (ret) BREAK_WRONG(ret);
			}
			ret = OS_WriteFile(&fw_file, (char *)pFrameAddrY8, framSize);
			if (ret != framSize) BREAK_WRONG(ret);
			ret = OS_CloseFile( &fw_file );
			if (ret) BREAK_WRONG(ret);
			DE_PRINT("Done %s\n", fileName);

			sprintf(fileName, "%sVideo_Prew__%dx%d.C.img",filePath, frameW, frameH);
			DE_PRINT("Writing %s\n", fileName);
			if ( RET_OK != OS_OpenFile( &fw_file, fileName, O_CREAT|O_RDWR|O_LARGEFILE, 0666 ) )
			{
				DE_PRINT("<error> can't open fw_file (%s)\n", fileName);
				BREAK_WRONG(ret);
			}
			ret = OS_WriteFile(&fw_file, (char *)pFrameAddrC8, framSize*smuxSample);
			if (ret != framSize*smuxSample) BREAK_WRONG(ret);
			ret = OS_CloseFile( &fw_file );
			if (ret) BREAK_WRONG(ret);
			DE_PRINT("Done %s\n", fileName);
		} while (0);
		if (ret) BREAK_WRONG(ret);
#endif
		grabSize = 0;
		offsetY  = 0;
		offsetC  = 0;
		for (y=0;y<grabH;y++) {
			startY = (grabY + y) * frameW + grabX;
			grabSize = y * grabStepW;
			for (x=0;x<grabW;x++) {
				pFrameColor = &pstParams->color[grabSize+x];
				posY  = offsetY + (startY + x);
				posC  = offsetC + (startY + x) * smuxSample;
				posC &= GET_RMSK(0,1);
				if (GET_BITS(pstParams->bReadOnOff,0,1)) {
					pixelG8 = pFrameAddrY8[posY+0];
					pixelB8 = pFrameAddrC8[posC+0];
					pixelR8 = pFrameAddrC8[posC+1];
					rmb();
					pFrameColor->pixelGrabY  = GET_SVAL(pixelG8, 0,8,2);
					pFrameColor->pixelGrabCb = GET_SVAL(pixelB8, 0,8,2);
					pFrameColor->pixelGrabCr = GET_SVAL(pixelR8, 0,8,2);
				} else {
					pixelG8 = GET_BITS(pFrameColor->pixelGrabY	,2,8);
					pixelB8 = GET_BITS(pFrameColor->pixelGrabCb ,2,8);
					pixelR8 = GET_BITS(pFrameColor->pixelGrabCr ,2,8);
					pFrameAddrY8[posY+0] = pixelG8;
					pFrameAddrC8[posC+0] = pixelB8;
					pFrameAddrC8[posC+1] = pixelR8;
					wmb();
				}

				if (!colorDepth) continue;
				divY = posY/4;
				remY = posY%4;
				divC = posC/4;
				remC = posC%4;

				if (GET_BITS(pstParams->bReadOnOff,0,1)) {
					pixelY2 = pFrameAddrY2[divY];
					pixelC2 = pFrameAddrC2[divC];
					rmb();
					pixelG2 = GET_BITS(pixelY2, (remY+0)*2, 2);
					pixelB2 = GET_BITS(pixelC2, (remC+0)*2, 2);
					pixelR2 = GET_BITS(pixelC2, (remC+1)*2, 2);

					pFrameColor->pixelGrabY  |= GET_SVAL(pixelG2, 0,2,0);
					pFrameColor->pixelGrabCb |= GET_SVAL(pixelB2, 0,2,0);
					pFrameColor->pixelGrabCr |= GET_SVAL(pixelR2, 0,2,0);
				} else {
					pixelG2 = GET_BITS(pFrameColor->pixelGrabY	,0,2);
					pixelB2 = GET_BITS(pFrameColor->pixelGrabCb ,0,2);
					pixelR2 = GET_BITS(pFrameColor->pixelGrabCr ,0,2);

					pixelY2 = pFrameAddrY2[divY];
					pixelC2 = pFrameAddrC2[divC];
					rmb();
					pixelY2 |= GET_SVAL(pixelG2, 0, 2, (remY+0)*2);
					pixelC2 |= GET_SVAL(pixelB2, 0, 2, (remC+0)*2);
					pixelC2 |= GET_SVAL(pixelR2, 0, 2, (remC+1)*2);
					pFrameAddrY2[divY] = pixelY2;
					pFrameAddrC2[divC] = pixelC2;
					wmb();
				}
			}
		}
		pstParams->region.realPixelGrabW = grabW;
		pstParams->region.realPixelGrabH = grabH;
		pstParams->region.colorSpace	 = 0;
	} while (0);

	if(pFrameAddrY8) vunmap_phys(pFrameAddrY8);
	if(pFrameAddrC8) vunmap_phys(pFrameAddrC8);
	if(pFrameAddrY2) vunmap_phys(pFrameAddrY2);
	if(pFrameAddrC2) vunmap_phys(pFrameAddrC2);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief copy frame buffer of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams,\
									LX_DE_CVI_RW_PREW_FRAME_T *prewInfo)
{
	int ret = RET_OK;
// remove legacy code(20190311)
	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_CviMap(LX_DE_WIN_ID_T win_id, \
		LX_DE_IN_SRC_T in_port, \
		UINT32 port_num)
{
	int ret = RET_OK;
	UINT32 sel_cvi[2] = {0, 0};
	UINT32 sel_clk[2] = {0, 0};

	do {
		sel_cvi[0] = CVI_NONE_O18;
		sel_cvi[1] = CVI_NONE_O18;
		sel_clk[0] = CLK_NONE_O18;
		sel_clk[1] = CLK_NONE_O18;

		switch(win_id)
		{
			case LX_DE_WIN_MAIN:
			case LX_DE_WIN_1:
			case LX_DE_WIN_2:
			case LX_DE_WIN_3:
				if(in_port == LX_DE_IN_SRC_CVBS || \
						in_port == LX_DE_IN_SRC_ATV || \
						in_port == LX_DE_IN_SRC_SCART)
				{
					sel_cvi[0] = CVI_CVD_O18;
					sel_clk[0] = CLK_CVD_O18;
				}
				if(in_port == LX_DE_IN_SRC_YPBPR || \
						in_port == LX_DE_IN_SRC_VGA)
				{
					sel_cvi[0] = CVI_ADC_O18;
					sel_clk[0] = CLK_ADC_O18;
				}
				if(in_port == LX_DE_IN_SRC_HDMI)
				{
					g_HdmiPort_O18[win_id] = port_num;  // assign for resume from instanr boot !!!
					switch(port_num)
					{
						case HDMI_O18_PORT_0:
							sel_cvi[0] = CVI_HDMI_O18_A_L;
							sel_cvi[1] = CVI_HDMI_O18_A_R;
							sel_clk[0] = CLK_HDA_O18;
							sel_clk[1] = CLK_HDA_O18;
							break;
						case HDMI_O18_PORT_1:
							sel_cvi[0] = CVI_HDMI_O18_B_L;
							sel_cvi[1] = CVI_HDMI_O18_B_R;
							sel_clk[0] = CLK_HDB_O18;
							sel_clk[1] = CLK_HDB_O18;
							break;
						case HDMI_O18_PORT_2:
							sel_cvi[0] = CVI_HDMI_O18_C_L;
							sel_cvi[1] = CVI_HDMI_O18_C_R;
							sel_clk[0] = CLK_HDC_O18;
							sel_clk[1] = CLK_HDC_O18;
							break;
						case HDMI_O18_PORT_3:
							sel_cvi[0] = CVI_HDMI_O18_D_L;
							sel_cvi[1] = CVI_HDMI_O18_D_R;
							sel_clk[0] = CLK_HDD_O18;
							sel_clk[1] = CLK_HDD_O18;
							break;
						default:
							sel_cvi[0] = CVI_HDMI_O18_A_L;
							sel_cvi[1] = CVI_HDMI_O18_A_R;
							sel_clk[0] = CLK_HDA_O18;
							sel_clk[1] = CLK_HDA_O18;
							DE_ERROR("undefined hdmi port [%d]\n", port_num);
							break;
					}
				}
				break;
			default:
				break;
		}

		if(in_port == LX_DE_IN_SRC_NONE) break;

#ifdef USE_CTOP_CODES_FOR_O18
		DE_CVI_O18_RdFL(cv0_top_ctrl);
		DE_CVI_O18_RdFL(cv1_top_ctrl);
		DE_CVI_O18_RdFL(cv2_top_ctrl);
		DE_CVI_O18_RdFL(cv3_top_ctrl);
		CTOP_CTRL_O18A0_RdFL(CTRL_CVI, crg_cvi03);
		switch(win_id)
		{
			case LX_DE_WIN_MAIN:
				DE_CVI_O18_Wr01(cv0_top_ctrl, data_in_sel, sel_cvi[0]);
				CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi0_clk_sel, sel_clk[0]);
				//CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi4_clk_sel, sel_clk[0]);		// -> Related to o18 architecture of gate reduction (input of CDC4 clock)
				if(sel_cvi[1] != CVI_NONE_O18 && !g_QuadWin_O18)
				{
					DE_CVI_O18_Wr01(cv1_top_ctrl, data_in_sel, sel_cvi[1]);
					CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi1_clk_sel, sel_clk[1]);
				}
				break;
			case LX_DE_WIN_1:
				if(g_QuadWin_O18)
				{
					DE_CVI_O18_Wr01(cv1_top_ctrl, data_in_sel, sel_cvi[0]);
					CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi1_clk_sel, sel_clk[0]);
					break; // This 'break' is correct !!! (if Quad mode)
				}
			case LX_DE_WIN_2:
				DE_CVI_O18_Wr01(cv2_top_ctrl, data_in_sel, sel_cvi[0]);
				CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi2_clk_sel, sel_clk[0]);
				//CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi5_clk_sel, sel_clk[0]);		// -> Related to o18 architecture of gate reduction (input of CDC5 clock)
				if(sel_cvi[1] != CVI_NONE_O18)
				{
					DE_CVI_O18_Wr01(cv3_top_ctrl, data_in_sel, sel_cvi[1]);
					CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi3_clk_sel, sel_clk[1]);
				}
				break;
			case LX_DE_WIN_3:
				if(g_QuadWin_O18)
				{
					DE_CVI_O18_Wr01(cv2_top_ctrl, data_in_sel, sel_cvi[0]);
					CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi3_clk_sel, sel_clk[0]);
					break; // This 'break' is correct !!! (if Quad mode)
				}
			default :
				break;
		}
#if 0 // 20141007 Do not update these cvi registers.... (firmware control)
		DE_CVI_O18_WrFL(cv0_top_ctrl);
		DE_CVI_O18_WrFL(cv1_top_ctrl);
		DE_CVI_O18_WrFL(cv2_top_ctrl);
		DE_CVI_O18_WrFL(cv3_top_ctrl);
#endif
		CTOP_CTRL_O18A0_WrFL(CTRL_CVI, crg_cvi03);
#endif //#ifdef USE_CTOP_CODES_FOR_O18
	} while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_WIN_ID_T win_id = LX_DE_WIN_MAIN;
	LX_DE_IN_SRC_T in_port = LX_DE_IN_SRC_MVI;
	UINT32 srcPort = 0;

	do {
		CHECK_KNULL(pstParams);

		win_id  = pstParams->win_id;
		in_port = pstParams->inputSrc;
		srcPort = pstParams->inputResv;

		ret = DE_REG_O18_CviMap(win_id, in_port, srcPort);

		if(win_id < NUM_WIN_MAX)
		{
			g_WinsrcMap_O18[win_id] = in_port;
			g_WinsrcPort_O18[win_id] = srcPort;
		}

		DE_PRINT("Src map (NONE(0)/VGA(1)/YPBPR(2)/ATV(3)/CVD(4)/SCART(5)/HDMI(6)/MVI(7)/CPU(8))");
		DE_PRINT("  => win[%d] src[%d] port[%d]", win_id, in_port, srcPort);
	} while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set information which is comming from CVI port
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams)
{
	int ret = RET_OK;
#ifdef USE_CTOP_CODES_FOR_O18
	UINT32 hdmi_half_clk = 0;

	do {
		CHECK_KNULL(pstParams);
		memcpy(&sCviSrcType, pstParams, sizeof(LX_DE_CVI_SRC_TYPE_T));

		if(pstParams->cvi_input_src != LX_DE_CVI_SRC_HDMI) break;

		DE_NOTI("CVI-Ch[%d] HDMI Phy[%d] : hsize = %d, vsize = %d\n", \
			pstParams->cvi_channel, g_HdmiPort_O18[pstParams->cvi_channel],\
			pstParams->size_offset.hsize, pstParams->size_offset.vsize);

		CTOP_CTRL_O18A0_RdFL(CTRL_CVI, crg_cvi03);
		if(pstParams->cvi_split_info.split_mode == LX_DE_CVI_SPLIT_1X4)
		{
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi0_clk_sel, 3);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi1_clk_sel, 2);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi2_clk_sel, 1);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi3_clk_sel, 0);
			DE_NOTI("set CTOP split_mode");
		}
		else if(pstParams->cvi_split_info.split_mode == LX_DE_CVI_SPLIT_1X2 \
			||  pstParams->cvi_split_info.split_mode == LX_DE_CVI_SPLIT_1X2_DUP)
		{
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi0_clk_sel, 3); // HDMI-1
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi1_clk_sel, 2); // HDMI-2
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi2_clk_sel, 2); // don't care
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi03, cvi3_clk_sel, 0); // don't care
			DE_NOTI("set CTOP 1x2 split/duplicate");
		}
		else
		{
			ret = DE_REG_O18_CviMap(0, g_WinsrcMap_O18[0], g_WinsrcPort_O18[0]);
			DE_NOTI("set CTOP 1x1 mode");
		}
		CTOP_CTRL_O18A0_WrFL(CTRL_CVI, crg_cvi03);

		if(pstParams->size_offset.hsize > 2440 && pstParams->size_offset.vsize > 1400)
		{
			switch(pstParams->c_sample)
			{
				case LX_DE_CVI_420:
					hdmi_half_clk = 0;
					break;
				case LX_DE_CVI_422:
				case LX_DE_CVI_444:
				default:
					hdmi_half_clk = 1;
					break;
			}
		}
		else
		{
			hdmi_half_clk = 0;
		}
#if 0 // 20170612 , remove for O18
		switch(g_HdmiPort_O18[pstParams->cvi_channel])
		{
			case 0:
				CTOP_CTRL_O18A0_RdFL(CTRL_CVI, crg_cvi02);
				CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, hdmi0_clk_sel, hdmi_half_clk);
				CTOP_CTRL_O18A0_WrFL(CTRL_CVI, crg_cvi02);
				break;
			case 1:
				CTOP_CTRL_O18A0_RdFL(CTRL_CVI, crg_cvi02);
				CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, hdmi1_clk_sel, hdmi_half_clk);
				CTOP_CTRL_O18A0_WrFL(CTRL_CVI, crg_cvi02);
				break;
			case 2:
				CTOP_CTRL_O18A0_RdFL(CTRL_CVI, crg_cvi02);
				CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, hdmi2_clk_sel, hdmi_half_clk);
				CTOP_CTRL_O18A0_WrFL(CTRL_CVI, crg_cvi02);
				break;
			case 3:
				CTOP_CTRL_O18A0_RdFL(CTRL_CVI, crg_cvi02);
				CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, hdmi3_clk_sel, hdmi_half_clk);
				CTOP_CTRL_O18A0_WrFL(CTRL_CVI, crg_cvi02);
				break;
			default:
				DE_ERROR("error index\n");
				break;
		}
#endif
	} while (0);
#endif //#ifdef USE_CTOP_CODES_FOR_O18

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set Frame rate of Display
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_Init(LX_DE_PANEL_TYPE_T *pstParams)
{
	/* if ADV (120Hz) model, disable debug memory region */
    if (lx_board_opt() & LX_BOARD_OPT_ADV)
    {
        o18_de_debug_mem = 0;
    }

	DE_REG_O18_InitAddrSwitch();

	switch(g_model_type_from_ctop)
	{
		case 3:
			g_Diplay_type_from_loader = LX_PANEL_TYPE_1920;
			break;
		case 2:
			g_Diplay_type_from_loader = LX_PANEL_TYPE_1920_120P;
			break;
		case 1:
			g_Diplay_type_from_loader = LX_PANEL_TYPE_3840;
			break;
		case 0:
			g_Diplay_type_from_loader = LX_PANEL_TYPE_3840_120P;
			break;
		default:
			g_Diplay_type_from_loader = LX_PANEL_TYPE_MAX;
			DE_ERROR("Unknown display type from loader[%d]", g_model_type_from_ctop);
			break;
	}

	*pstParams = g_Diplay_type_from_loader;

	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de VCS parameter.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetVcs(LX_DE_VCS_IPC_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O18_GPIO_Init(void)
{
#ifdef	USE_CTOP_CODES_FOR_O18
#ifdef USE_VIDEO_UART2_FOR_MCU
	CTOP_CTRL_O18A0_RdFL(ND0, ctr33);
	CTOP_CTRL_O18A0_RdFL(CPU, ctr39);
	CTOP_CTRL_O18A0_Wr01(ND0, ctr33, uart0_sel, 2); // UART0 = cpu0
	CTOP_CTRL_O18A0_Wr01(ND0, ctr33, uart1_sel, 11); // UART1 = de
	CTOP_CTRL_O18A0_Wr01(ND0, ctr33, uart2_sel, 7); // UART2 = cpu1
	CTOP_CTRL_O18A0_Wr01(ND0, ctr33, rx_sel_mcu, 1); // 1:DE from UART1
	CTOP_CTRL_O18A0_Wr01(CPU, ctr39, jtag1_sel, 5); // jtag1 = de
	CTOP_CTRL_O18A0_WrFL(ND0, ctr33);
	CTOP_CTRL_O18A0_WrFL(CPU, ctr39);
#endif
#endif
	return 0;
}

int DE_REG_O18_HDMI_Init(void)
{
	return 0;
}

int DE_REG_O18_LVDS_Init(void)
{
	return 0;
}

int DE_REG_O18_MISC_Init(void)
{
	return 0;
}

int DE_REG_O18_OSD_Init(void)
{

	return 0;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set uart for MCU or CPU
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_Uart0_Switch(int whichUart)
{
	int ret = RET_OK;

#ifdef	USE_CTOP_CODES_FOR_O18
#ifdef USE_DE_SWITCH_UART
	CTOP_CTRL_O18A0_RdFL(CTOP_SRE, ctr00);
	CTOP_CTRL_O18A0_RdFL(CTOP_SRE, ctr01);
	switch (whichUart)
	{
		case 0 :
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, uart0_sel, 1); // UART0 = cpu0
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, uart1_sel, 1); // UART1 = de
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, rx_sel_pqe_mcu0, 1); // 1:DE from UART1
			break;
		case 1 :
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, uart0_sel, 4); // UART0 = de
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, uart1_sel, 4); // UART1 = cpu0
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, rx_sel_pqe_mcu0, 0); // 0:DE from UART0
			break;
		case 0x80 :
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag1_sel, 0); // jtag1 = vdec (default)
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag0_sel, 3); // jtag0 = de
			DE_PRINT("JTAG-1=vdec\n");
			break;
		case 0x81 :
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag1_sel, 3); // jtag1 = de
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag0_sel, 0); // jtag0 = vdec
			DE_PRINT("JTAG-1=de\n");
			break;
		case 0x82 :
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag0_sel, 0); // jtag0 = cpu
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag1_sel, 3); // jtag1 = de
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag_sel_pmcu0, 1); // jtag1 = de
			DE_PRINT("JTAG-0=cpu\n");
			break;
		case 0x83 :
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag0_sel, 3); // jtag0 = de
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag1_sel, 0); // jtag1 = vdec
			CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag_sel_pmcu0, 0); // jtag0 = de
			DE_PRINT("JTAG-0=de\n");
			break;
		default :
			BREAK_WRONG(whichUart);
			break;
	}
	CTOP_CTRL_O18A0_WrFL(CTOP_SRE, ctr00);
	CTOP_CTRL_O18A0_WrFL(CTOP_SRE, ctr01);
#endif
#endif
	return ret;
}

int DE_REG_O18_FW_DumpStatus(void)
{
	#define PQE_DEBUG_INFO_BASE	(0xC9026360)

	int ret = RET_OK;
	UINT32 reg_ctrl0;
	UINT32 *p_pqe_debug_info = NULL;
	UINT32 i, size = 32;

	DE_IPC_O18_RdFL(set_reg_ctrl0);
	reg_ctrl0 = DE_IPC_O18_Rd(set_reg_ctrl0);

	DE_NOTI("PQE_DEBUG_INFO start\n");

	DE_NOTI("reg_ctrl0[ 0x%08X ]\n", reg_ctrl0);

	p_pqe_debug_info = (UINT32 *)ioremap(PQE_DEBUG_INFO_BASE, sizeof(UINT32) * size);

	for(i=0;i<size;i++)
	{
		DE_NOTI("[%02d] 0x%08X\n", i, p_pqe_debug_info[i]);
	}

	DE_NOTI("PQE_DEBUG_INFO end\n");

	if(p_pqe_debug_info) iounmap(p_pqe_debug_info);

	return ret;
}

static void _set_tag_info(void)
{
#define SYSTEM_MAGIC_WORD           0xDECAFE
	UINT32 						*pTagBase = NULL;
	UINT32						opt = 0;
#ifdef O18_PQE_NEW_MEM
	LX_DE_IPC_SYSTEM_NEW_T		o18_tag_info;
#else
	LX_DE_IPC_SYSTEM_T			tag_info;
#endif
	UINT64 dpb8k_addr = 0;
	UINT64 dpb_addr = 0;
	UINT64 cpb_addr = 0;
	UINT64 vdec_addr = 0;
	UINT32 dpb8k_size = 0;
	UINT32 dpb_size = 0;
	UINT32 cpb_size = 0;
	UINT32 vdec_size = 0;

	do {
		DE_REG_GetHWOpt(&opt);

		memset(&o18_tag_info, 0, sizeof(LX_DE_IPC_SYSTEM_NEW_T));
#ifdef O18_PQE_NEW_MEM
#ifdef USE_VIDEO_FOR_FPGA
		o18_tag_info.system_info    = (SYSTEM_MAGIC_WORD << 8) | 2/*1:ASIC,2:FPGA*/;
#else
		o18_tag_info.system_info    = (SYSTEM_MAGIC_WORD << 8) | 1/*1:ASIC,2:FPGA*/;
#endif
		o18_tag_info.model.u32Data  = opt;
		o18_tag_info.firmware.base  = gpMemCfgDeFW_M1->fw_base;
		o18_tag_info.firmware.size  = gpMemCfgDeFW_M1->fw_size;
		o18_tag_info.de_prew.base   = gpAdrPreW->fw_base;
		o18_tag_info.de_prew.size   = gpAdrPreW->fw_size;

		o18_tag_info.de_frm_m1.base = gpMemCfgFrm_M1->fw_base;
		o18_tag_info.de_frm_m1.size = gpMemCfgFrm_M1->fw_size;
		o18_tag_info.de_frm_m2.base = gpMemCfgFrm_M2->fw_base;
		o18_tag_info.de_frm_m2.size = gpMemCfgFrm_M2->fw_size;
		o18_tag_info.de_bt_m1.base  = gpMemCfgBT_M1->fw_base;
		o18_tag_info.de_bt_m1.size  = gpMemCfgBT_M1->fw_size;
		o18_tag_info.de_bt_m2.base  = gpMemCfgBT_M2->fw_base;
		o18_tag_info.de_bt_m2.size  = gpMemCfgBT_M2->fw_size;
		o18_tag_info.de_vt_m1.base  = gpMemCfgVT_M1->fw_base;
		o18_tag_info.de_vt_m1.size  = gpMemCfgVT_M1->fw_size;
		o18_tag_info.de_vt_m2.base  = gpMemCfgVT_M2->fw_base;
		o18_tag_info.de_vt_m2.size  = gpMemCfgVT_M2->fw_size;

		o18_tag_info.de_hdr.base    = gpMemCfgHDR->frame_base;
		o18_tag_info.de_hdr.size    = gpMemCfgHDR->frame_size;

#ifdef INCLUDE_KDRV_BE
		o18_tag_info.be_fpp.base    = gMemCfgBeFrc[2].frame_base;
		o18_tag_info.be_fpp.size    = gMemCfgBeFrc[2].frame_size;
		o18_tag_info.be_frc0.base	= gMemCfgBeFrc[3].frame_base;
		o18_tag_info.be_frc0.size	= gMemCfgBeFrc[3].frame_size;
		o18_tag_info.be_frc1.base	= gMemCfgBeFrc[4].frame_base;
		o18_tag_info.be_frc1.size	= gMemCfgBeFrc[4].frame_size;
		o18_tag_info.be_frc2.base	= gMemCfgBeFrc[5].frame_base;
		o18_tag_info.be_frc2.size	= gMemCfgBeFrc[5].frame_size;
		o18_tag_info.be_db.base     = gpBeMem->fw[2].fw_base;
		o18_tag_info.be_db.size     = 0;
#endif
		o18_tag_info.fpp_info.base  = gpMemCfgDeFW_M0->fw_base + (VIDEO_O18_FIRMWARE_MEM_SIZE_WEB_OS<<1);
		o18_tag_info.fpp_info.size  = 32*1024;

		o18_tag_info.vdec_pool_0.base = 0;
		o18_tag_info.vdec_pool_0.size = 0;
		o18_tag_info.vdec_pool_1.base = 0;
		o18_tag_info.vdec_pool_1.size = 0;

		hma_pool_info ("dpb8k", (phys_addr_t *)&dpb8k_addr, &dpb8k_size);
		hma_pool_info ("dpb", (phys_addr_t *)&dpb_addr, &dpb_size);
		hma_pool_info ("cpb", (phys_addr_t *)&cpb_addr, &cpb_size);
		hma_pool_info ("vdec", (phys_addr_t *)&vdec_addr, &vdec_size);

		if(dpb8k_size == 0)
		{
			o18_tag_info.vdec_pool_0.base = (UINT32)(dpb_addr & 0xFFFFFFFF);
		}
		else
		{
			o18_tag_info.vdec_pool_0.base = (UINT32)(dpb8k_addr & 0xFFFFFFFF);
		}
		
#ifdef INCLUDE_KDRV_GFX
			o18_tag_info.vdec_pool_0.size = dpb8k_size + dpb_size + cpb_size + vdec_size + gMemCfgGfx.surface[0].size;
#else
			o18_tag_info.vdec_pool_0.size = dpb8k_size + dpb_size + cpb_size + vdec_size;
#endif

		o18_tag_info.shared_mem_info.sys_time.base = gpMemCfgDeFW_M0->fw_base + (VIDEO_O18_FIRMWARE_MEM_SIZE_WEB_OS*3);

		o18_tag_info.shared_mem_info.video_delay_info.base = gpMemCfgDeFW_M0->fw_base + (VIDEO_O18_FIRMWARE_MEM_SIZE_WEB_OS*4);
		o18_tag_info.shared_mem_info.video_delay_info.size = 16; //

		memcpy(&g_Mem_Info, &o18_tag_info, sizeof(LX_DE_IPC_SYSTEM_NEW_T));

		// tagging magic , fw base and frame base
		pTagBase = (UINT32*)ioremap(DE_IPC_FRM_O18_BASE, DTVSOC_IPC_FROM_CPU_SIZE);
		if(pTagBase)
		{
			memcpy(pTagBase, &o18_tag_info, sizeof(LX_DE_IPC_SYSTEM_NEW_T));
			wmb();
#define SIZE_MB(a)    (a/1024/1024)
#define SIZE_KB(a)    (a/1024)
			DE_NOTI("######################################");
			DE_NOTI("System Info[0x%08x] model[%d]\n", o18_tag_info.system_info, o18_tag_info.model.u32Data);
			DE_NOTI("Firmware		%dMB at 0x%08X\n" ,SIZE_MB(o18_tag_info.firmware.size), o18_tag_info.firmware.base);
			DE_NOTI("PREW_M0		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.de_prew.size), o18_tag_info.de_prew.base);
			DE_NOTI("FRM_M1		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.de_frm_m1.size), o18_tag_info.de_frm_m1.base);
			DE_NOTI("FRM_M2		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.de_frm_m2.size), o18_tag_info.de_frm_m2.base);
			DE_NOTI("BT_M1		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.de_bt_m1.size), o18_tag_info.de_bt_m1.base);
			DE_NOTI("BT_M2		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.de_bt_m2.size), o18_tag_info.de_bt_m2.base);
			DE_NOTI("VT_M1		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.de_vt_m1.size), o18_tag_info.de_vt_m1.base);
			DE_NOTI("VT_M2		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.de_vt_m2.size), o18_tag_info.de_vt_m2.base);
			DE_NOTI("HDR_M1		%dKB at 0x%08X\n", SIZE_KB(o18_tag_info.de_hdr.size), o18_tag_info.de_hdr.base);
			DE_NOTI("be_fpp		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.be_fpp.size), o18_tag_info.be_fpp.base);
			DE_NOTI("be_frc0		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.be_frc0.size), o18_tag_info.be_frc0.base);
			DE_NOTI("be_frc1		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.be_frc1.size), o18_tag_info.be_frc1.base);
			DE_NOTI("be_frc2		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.be_frc2.size), o18_tag_info.be_frc2.base);
			DE_NOTI("be_db			%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.be_db.size), o18_tag_info.be_db.base);
			DE_NOTI("vdec_0 		%dMB at 0x%08X\n", SIZE_MB(o18_tag_info.vdec_pool_0.size), o18_tag_info.vdec_pool_0.base);
			DE_NOTI("######################################");
			iounmap((void*)pTagBase);
		}
#else //#ifdef O18_PQE_NEW_MEM
#ifdef USE_VIDEO_FOR_FPGA
		tag_info.system_info   = (SYSTEM_MAGIC_WORD << 8) | 2/*1:ASIC,2:FPGA*/;
#else
		tag_info.system_info   = (SYSTEM_MAGIC_WORD << 8) | 1/*1:ASIC,2:FPGA*/;
#endif
		tag_info.firmware_base = gpDeMem->fw[0].fw_base;;
		tag_info.de_frame_base = gpDeMem->frame_base;
		tag_info.de_grab_base  = opt; // from HW opt
		tag_info.de_prew_base  = gpAdrPreW->fw_base;
#ifdef INCLUDE_KDRV_BE
		tag_info.be_frame_base = gpBeMem->fw[0].fw_base;
#else
		tag_info.be_frame_base = 0;
#endif
		tag_info.de_shared_base = 0;
		tag_info.de_hdr_base = gpMemCfgHDR->frame_base;
		tag_info.de_bt_base  = gpMemCfgBT->frame_base; // 40MB
		tag_info.de_vt_base  = gpMemCfgVT->frame_base; // 60MB

		tag_info.de_frame_baseC = gpDeMemC->frame_base;
		tag_info.de_frame_sizeC = gpDeMemC->frame_size;

		if (!gpDeMem->frame_base) break;

		tag_info.de_frame_size = gpDeMem->frame_size;

		// tagging magic , fw base and frame base
		pTagBase = (UINT32*)ioremap(DE_IPC_FRM_O18_BASE, DTVSOC_IPC_FROM_CPU_SIZE);
		if(pTagBase)
		{
			memcpy(pTagBase, &tag_info, sizeof(LX_DE_IPC_SYSTEM_T));
			wmb();

			DE_NOTI("Tag to FW (fw & frame base) -	0:0x%08X , 1:0x%08X , 2:0x%08X (at 0x%08x)\n", \
					pTagBase[0], pTagBase[1], pTagBase[2], DE_IPC_FRM_O18_BASE);
			DE_NOTI("		  grab/prew/be_frame/de hdr base	-  3:0x%08x , 4:0x%08x , 5:0x%08x, 7:0x%08x 8:0x%08x\n",\
					pTagBase[3], pTagBase[4], pTagBase[5], pTagBase[7],pTagBase[8]);
			DE_NOTI("		  bt/3d 						   -  9:0x%08x , 10:0x%08x", pTagBase[9], pTagBase[10]);
			DE_NOTI("Y base:0x%08X, Y size:0x%08X", tag_info.de_frame_base, tag_info.de_frame_size);
			DE_NOTI("C base:0x%08X, C size:0x%08X", tag_info.de_frame_baseC, tag_info.de_frame_sizeC);
			DE_NOTI("hdr base 0x%x\n",tag_info.de_hdr_base);

			iounmap((void*)pTagBase);
		}
#endif		// #ifdef O18_PQE_NEW_MEM
	}while(0);
}

int DE_REG_O18_FW_Download(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	char						*lpAddr = NULL;
	LX_DE_CH_MEM_T				*pFwMem = NULL;
	BOOLEAN						run_stall = 0;
#if !defined(USE_DE_FIRMWARE_RUN_IN_PAK_M16)
//	BOOLEAN						tx_done = 0;
//	UINT32						edma_ctrl;
#endif
	UINT32						fwBaseAddr;
	UINT32 						fwSize;

	do {
		CHECK_KNULL(pstParams);
		DE_NOTI("start download %s  size[%d]\n", (pstParams->inx<4)?"MCU0":"MCU1", pstParams->size);
		if (!pstParams->size) break;
		if (!pstParams->pData) break;

		if(pstParams->inx == 4)
		{	// MCU1
			pFwMem     = gpMemCfgDeFW_M0;
			fwBaseAddr = pFwMem->fw_base + VIDEO_O18_MEM_SIZE_OF_SHARED_MEM;
			fwSize     = pstParams->size;
			DE_NOTI("Loading fwBaseAddr = 0x%08x, size = %d\n", fwBaseAddr, pstParams->size);
			DE_IPC_O18_RdFL(set_reg_ctrl0);
			DE_IPC_O18_Wr01(set_reg_ctrl0, run_stall1, 1);

			DE_IPC_O18_FLWr(srom_boot_map3, fwBaseAddr - USE_VIDEO_MCU1_ROM_FW_OFFSET);
			DE_IPC_O18_FLWr(srom_boot_map4, fwBaseAddr - USE_VIDEO_MCU1_ROM_FW_OFFSET);

			lpAddr	= (char *)vmap_phys((fwBaseAddr+USE_VIDEO_MCU_ROM_FW_OFFSET), pstParams->size);
			memcpy(lpAddr, pstParams->pData, fwSize);
			wmb();
			DE_IPC_O18_Wr01(set_reg_ctrl0, run_stall1, 0);
			DE_IPC_O18_WrFL(set_reg_ctrl0);

			if (lpAddr) vunmap_phys((void*)lpAddr);
			break;
		}

		DE_IPC_O18_RdFL(set_reg_ctrl0);
		DE_IPC_O18_Rd01(set_reg_ctrl0, run_stall, run_stall);
		DE_IPC_O18_Wr01(set_reg_ctrl0, uart0_mux, 0);
		DE_IPC_O18_Wr01(set_reg_ctrl0, uart1_mux, 0);

// do not check run_stall status for re-download
		//if (!run_stall) break;

		DE_IPC_O18_Wr01(set_reg_ctrl0, run_stall, 1);
		// removed DE_IPC_O18_Wr01(set_reg_ctrl0, mcu_sw_reset, 0);
		DE_IPC_O18_WrFL(set_reg_ctrl0);

#ifdef O18_PQE_NEW_MEM
		pFwMem = gpMemCfgDeFW_M1;
#else
		pFwMem = (LX_DE_CH_MEM_T *)&gpDeMem->fw[0];
#endif

		CHECK_KNULL(pFwMem);

		g_FwBase_O18 = pFwMem->fw_base;

		_set_tag_info();

		fwBaseAddr = pFwMem->fw_base;
		fwSize     = pFwMem->fw_size;
		if (fwSize < pstParams->size) fwSize = pstParams->size;
		fwSize  = GET_RDUP(fwSize, 4);
#if defined(USE_VIDEO_MCU_RUN_IN_DDR0) && (USE_VIDEO_MCU_RUN_IN_DDR0 > USE_VIDEO_MCU_ROM_BASE_ADDR)
		lpAddr	= (char *)vmap_phys((USE_VIDEO_MCU_RUN_IN_DDR0+USE_VIDEO_MCU_ROM_FW_OFFSET), pstParams->size);
#else
		lpAddr	= (char *)vmap_phys((fwBaseAddr+USE_VIDEO_MCU_ROM_FW_OFFSET), pstParams->size);
#endif
		CHECK_KNULL(lpAddr);
		memcpy(lpAddr, pstParams->pData, pstParams->size);
		wmb();
		if (lpAddr) vunmap_phys((void*)lpAddr);
		DE_NOTI("Loading fwBaseAddr = 0x%08x, size = %d\n", fwBaseAddr, pstParams->size);
		switch (pstParams->inx)
		{
#if !defined(USE_DE_FIRMWARE_RUN_IN_PAK_O18)
			case 2 :
			case 1 :
#if   defined(USE_DE_FIRMWARE_RUN_IN_ROM_O18)
				DE_NOTI("Loading DE_FW_ROM_%s\n", (1==pstParams->inx)?"IRM":"DRM");
				break;
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR_O18)
				DE_NOTI("Loading DE_FW_DDR_%s\n", (1==pstParams->inx)?"IRM":"DRM");
				break;
#elif defined(USE_DE_FIRMWARE_LOAD_DRM_IRM_EACH)
				DE_NOTI("Loading DE_FW_RAM_%s\n", (1==pstParams->inx)?"IRM":"DRM");
				if (1==pstParams->inx) break;
#else
				DE_NOTI("Loading DE_FW_DIRAM\n");
#endif
#endif
#if defined(USE_DE_FIRMWARE_RUN_IN_ROM_O18) || defined(USE_DE_FIRMWARE_RUN_IN_DDR_O18) || defined(USE_DE_FIRMWARE_RUN_IN_PAK_O18)
			case 3 :
			case 0 :
#endif
#if     defined(USE_DE_FIRMWARE_RUN_IN_PAK_O18)
				if (fwBaseAddr < USE_VIDEO_MCU_ROM_BASE_ADDR) BREAK_WRONG(fwBaseAddr);
				DE_IPC_O18_FLWr(srom_boot_map1, fwBaseAddr);
				DE_IPC_O18_FLWr(srom_boot_map2, fwBaseAddr);
				DE_IPC_O18_Wr01(set_reg_ctrl0, start_vector_sel, 0);

				// removed DE_IPC_O18_Wr01(set_reg_ctrl0, mcu_sw_reset, 1);
#elif   defined(USE_DE_FIRMWARE_RUN_IN_ROM_O18)
				DE_NOTI("Loading DE_FW_ROM_ADR5\n");
#if defined(USE_VIDEO_MCU_RUN_IN_DDR0) && (USE_VIDEO_MCU_RUN_IN_DDR0 > USE_VIDEO_MCU_ROM_BASE_ADDR)
				DE_NOTI("FW_BASE_ADDR is %x\n", USE_VIDEO_MCU_RUN_IN_DDR0);
				DE_IPC_O18_FLWr(srom_boot_map1, USE_VIDEO_MCU_RUN_IN_DDR0);
#else
				if (fwBaseAddr < USE_VIDEO_MCU_ROM_BASE_ADDR) BREAK_WRONG(fwBaseAddr);
				DE_IPC_O18_FLWr(srom_boot_map1, fwBaseAddr);
#endif
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR_M16)
				DE_IPC_O18_FLWr(atlas_port_sel, 0x1434);
				DE_NOTI("Loading DE_FW_DDR_ADR6\n");
#endif
				msleep(1); // wait ddr to ddr transition
				DE_IPC_O18_Wr01(set_reg_ctrl0, run_stall, 0);
				DE_IPC_O18_WrFL(set_reg_ctrl0);
			default :
				break;
		}
	} while (0);

	DE_NOTI("complete download %s\n", (pstParams->inx<4)?"MCU0":"MCU1");

	return ret;
}

int DE_REG_O18_FW_Verify(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	char						*lpAddr = NULL;
	LX_DE_CH_MEM_T				*pFwMem = NULL;
	BOOLEAN						run_stall = 0;
	UINT32						fwBaseAddr;
	UINT32 						fwSize;
	UINT32                      i;
	UINT32                      mismatch_count = 0;
	char temp;

	do {
		CHECK_KNULL(pstParams);
		if (!pstParams->size) break;
		if (!pstParams->pData) break;

		DE_PRINT("Verify start\n");

		DE_IPC_O18_RdFL(set_reg_ctrl0);
		DE_IPC_O18_Rd01(set_reg_ctrl0, run_stall, run_stall);
		DE_IPC_O18_Wr01(set_reg_ctrl0, run_stall, 1);
		DE_IPC_O18_WrFL(set_reg_ctrl0);

#ifdef O18_PQE_NEW_MEM
		pFwMem = gpMemCfgDeFW_M1;
#else
		pFwMem = (LX_DE_CH_MEM_T *)&gpDeMem->fw[0];
#endif

		CHECK_KNULL(pFwMem);

		fwBaseAddr = pFwMem->fw_base;
		fwSize     = pFwMem->fw_size;
		if (fwSize < pstParams->size) fwSize = pstParams->size;
		fwSize  = GET_RDUP(fwSize, 4);
#if defined(USE_VIDEO_MCU_RUN_IN_DDR0) && (USE_VIDEO_MCU_RUN_IN_DDR0 > USE_VIDEO_MCU_ROM_BASE_ADDR)
		lpAddr	= (char *)vmap_phys((USE_VIDEO_MCU_RUN_IN_DDR0+USE_VIDEO_MCU_ROM_FW_OFFSET), pstParams->size);
#else
		lpAddr	= (char *)vmap_phys((fwBaseAddr+USE_VIDEO_MCU_ROM_FW_OFFSET), pstParams->size);
#endif
		CHECK_KNULL(lpAddr);
		for(i=0;i<pstParams->size;i++)
		{
			temp = lpAddr[i];
			rmb();
			if(temp != pstParams->pData[i])
			{
				mismatch_count++;
				if(mismatch_count <= 4)
				{
					DE_ERROR("[%d]  : origin 0x%02x , read 0x%02x\n", i, pstParams->pData[i], temp);
				}
			}
		}

		DE_IPC_O18_RdFL(set_reg_ctrl0);
		DE_IPC_O18_Rd01(set_reg_ctrl0, run_stall, run_stall);
		DE_IPC_O18_Wr01(set_reg_ctrl0, run_stall, 0);
		DE_IPC_O18_WrFL(set_reg_ctrl0);

		if(mismatch_count) ret = RET_ERROR;

		DE_PRINT("Verify done.  base[0x%08x] size[%d] mismatch count [%d]\n",\
				fwBaseAddr, fwSize, mismatch_count);
		if (lpAddr) vunmap_phys((void*)lpAddr);
	} while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix and offset for each external source information.
 *
 * @param [IN] structure pointer to carry infomation about cvi FIR filter
 *
 * @return RET_OK(0)
 */
int DE_REG_O18_SetCviFir(LX_DE_CVI_FIR_T *pstParams)
{
	int ret = RET_OK;
	DE_PARAM_TYPE_T tableId;
	UINT32 firTable[ARRAY_SIZE(pstParams->fir_coef)+ARRAY_SIZE(pstParams->fir_coef_CbCr)];
	UINT32 inx = 0;
	int i;

	do {
		CHECK_KNULL(pstParams);
		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				tableId = DE_CVM_FIR_COEF;
				break;
			case LX_DE_CVI_CH_B :
			case LX_DE_CVI_CH_C :
			case LX_DE_CVI_CH_D :
				tableId = DE_CVS_FIR_COEF;
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
		for (i=0;i<ARRAY_SIZE(pstParams->fir_coef);i++)
		{
			firTable[inx++] = pstParams->fir_coef[i];
		}
		for (i=0;i<ARRAY_SIZE(pstParams->fir_coef_CbCr);i++)
		{
			firTable[inx++] = pstParams->fir_coef_CbCr[i];
		}

#ifdef USE_PARM_CODES_FOR_O18
		ret = DE_PRM_O18_LoadTable(tableId, DE_PARAM_WRITE, pstParams->isEnable, firTable, inx);
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video test pattern generator to mono-tone color.
 *
 * @param [IN] structure pointer to carry infomation about captured test pattern generator parameter.
 *
 * @return RET_OK(0)
 */
int DE_REG_O18_SetCviTpg(LX_DE_CVI_TPG_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video color sampling mode(sub sampling or 3 tap filtering).
 *
 * @param [IN] structure pointer to carry infomation about captured color sampling parameter.
 *
 * @return RET_OK(0)
 */
int DE_REG_O18_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set edge crop
 *
 * @param [IN] structure pointer to carry infomation about PE0 black boundary detection status.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetEdgeCrop(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O18_ResetDE(BOOLEAN bReset)
{
	int ret = RET_OK;

#ifdef USE_DE_DOES_RESET_IN_SUSPEND_RESUME
	bReset = (bReset)?TRUE:FALSE;
#if 0//def	USE_CTOP_CODES_FOR_O18
	if ( lx_chip_rev() >= LX_CHIP_REV(M16,B0) ) {
		CTOP_CTRL_O18_FLWr(ctr05_swrs_of_de, bReset?GET_PMSK(0,32):0);
		CTOP_CTRL_O18_RdFL(ctr06_swrst);
		CTOP_CTRL_O18_WfCM(ctr06_swrst, swrst_de_vd   ,bReset, 1);
		CTOP_CTRL_O18_WfCM(ctr06_swrst, swrst_de_apb  ,bReset, 1);
		CTOP_CTRL_O18_WfCM(ctr06_swrst, swrst_cvda    ,bReset, 1);
		CTOP_CTRL_O18_WrFL(ctr06_swrst);
	}
#endif
#endif
	return ret;
}

BOOLEAN DE_REG_O18_IPCisAlive(void)
{
	BOOLEAN isFwDownloaded = FALSE;
	DE_IPC_O18_FLRf(int_intr_enable, ipc_interrupt_enable_mcu, isFwDownloaded);
#ifdef USE_IPC_CONTROL_INTERRUPT_A_BIT
	return isFwDownloaded;
#else
	return GET_BITS(isFwDownloaded, VIDEO_IPC_INTERRUPT_ARM_BIT, 1);
#endif
}

int DE_REG_O18_SetUdMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		sbDeUdMode = (*pstParams)?TRUE:FALSE;
		if(sbDeUdMode)
		sCviSrcType.cvi_channel = LX_DE_CVI_CH_B;
		ret = DE_REG_O18_SetCviSrcType(&sCviSrcType);
		//if (ret) break;
		//g_de_CviCsc.cvi_channel = LX_DE_CVI_CH_B;
		//ret = DE_HAL_SetCviCsc(&g_de_CviCsc);
	} while (0);

	return ret;
}

int DE_REG_O18_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address = gpMemCfgDeFW_M0->fw_base; // base of vtg shared mem
	} while (0);

	return ret;
}

int DE_REG_O18_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
#ifdef O18_PQE_NEW_MEM
		pstParams->address    = gpMemCfgVT_M1->fw_base;
		pstParams->y_frame[0] = gpMemCfgVT_M1->fw_base;
		pstParams->c_frame[0] = gpMemCfgVT_M2->fw_base;
#endif
	} while (0);

	return ret;
}

int DE_REG_O18_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address = gpMemCfgDeFW_M0->fw_base + VIDEO_O18_FIRMWARE_MEM_SIZE_WEB_OS; // base of VTV shared mem
	} while (0);

	return ret;
}

int DE_REG_O18_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		sDeMultiWinSrc = *pstParams;
	} while (0);

	return ret;
}

/**
 * control vsync interrupt from de hardware
 */
int DE_REG_O18_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en)
{
	OS_FILE_T file;
	BOOLEAN vsync_sel = 0;

	DE_NOTI("\nLog enable : vi /var/vsync_log & save");
	DE_NOTI("Select interrupt source : default -> hdr, vi /var/vsync_imx & save -> imx");

	if(RET_OK == OS_OpenFile(&file, "/var/vsync_imx", O_RDONLY, 0666))
	{
		vsync_sel = 1;
	}
	else
	{
		vsync_sel = 2;
	}

	switch(mcu_id)
	{
		case 0:
			if(vsync_sel == 1) //use hdr source interrupt
			{
				DE_HDR_O18_RdFL(ctrl_intr_pulse);
				DE_HDR_O18_RdFL(intr_mux);
				DE_HDR_O18_RdFL(intr_mask);
				DE_HDR_O18_RdFL(intr_cpu_mask);

				DE_HDR_O18_Wr01(ctrl_intr_pulse, sel_src_i5_intr_pulse, 0); /* 0(src), 1(disp) */
				DE_HDR_O18_Wr01(ctrl_intr_pulse, idx_src_i5_intr_pulse, 0); /* 0(s0_src_pulse0) */

				DE_HDR_O18_Wr01(intr_mux, mux_i5_src_pulse, 1); 		   /* to cpu */
				DE_HDR_O18_Wr01(intr_mask, mask_i5_src_pulse, intr_en?0:1); /* 0:unmask */
				DE_HDR_O18_Wr01(intr_cpu_mask, mask_i5_src_pulse, intr_en?0:1); /* 0:unmask */

				DE_HDR_O18_WrFL(ctrl_intr_pulse);
				DE_HDR_O18_WrFL(intr_mux);
				DE_HDR_O18_WrFL(intr_mask);
				DE_HDR_O18_WrFL(intr_cpu_mask);

				DE_IPC_O18_RdFL(intr_cpu_flag_en);
				DE_IPC_O18_Wr01(intr_cpu_flag_en, hdr_mcu_intr_cpu_en, 1);
				DE_IPC_O18_WrFL(intr_cpu_flag_en);

				DE_NOTI("################### use HDR interrupt for source sync ###############");
			}
			else if(vsync_sel == 2) // use imx source interrupt
			{
				DE_IMX_O18_RdFL(ctrl_intr_pulse);
				DE_IMX_O18_RdFL(intr_mux);
				DE_IMX_O18_RdFL(intr_mask);

				DE_IMX_O18_Wr01(ctrl_intr_pulse, sel_src_i5_intr_pulse, 0); /* 0(src), 1(disp) */
				DE_IMX_O18_Wr01(ctrl_intr_pulse, idx_src_i5_intr_pulse, 0); /* 0(s0_src_pulse0) */

				DE_IMX_O18_Wr01(intr_mux, mux_i5_src_pulse, 1);			   /* to cpu */
				DE_IMX_O18_Wr01(intr_mask, mask_i5_src_pulse, intr_en?0:1); /* 0:unmask */

				DE_IMX_O18_WrFL(ctrl_intr_pulse);
				DE_IMX_O18_WrFL(intr_mux);
				DE_IMX_O18_WrFL(intr_mask);

				DE_IPC_O18_RdFL(intr_cpu_flag_en);
				DE_IPC_O18_Wr01(intr_cpu_flag_en, imx_mcu_intr_cpu_en, 1);
				DE_IPC_O18_WrFL(intr_cpu_flag_en);

				DE_NOTI("################### use IMX interrupt for source sync ###############");
			}

			#if 0
			// Interrupt form CVI hardware
			DE_CVC_O18_RdFL(intr_mux);
			DE_CVC_O18_RdFL(intr_mask);
			DE_CVC_O18_Wr01(intr_mux, mux_cvi1_field, 1);
			DE_CVC_O18_Wr01(intr_mask, mask_cvi1_field, 0);
			DE_CVC_O18_WrFL(intr_mux);
			DE_CVC_O18_WrFL(intr_mask);
			#endif

			break;
		case 1:
			break;
		default:
			break;
	}

	return RET_OK;
}

/**
 * get irq number
 */
int DE_REG_O18_GetIrqNum(UINT32 mcu_id, UINT32 *ipc_irq_num, UINT32 *sync_irq_num)
{
	switch(mcu_id)
	{
		case 0:
			*ipc_irq_num  = O18_IRQ_IPC_BCPU;
			*sync_irq_num = O18_IRQ_DE_BCPU;
			break;
		case 1:
			break;
		default:
			return RET_ERROR;
			break;
	}
	return RET_OK;
}

/**
 * set debug data
 */
int DE_REG_O18_SetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->config_type) {
			case LX_DE_CONFIG_TYPE_ALL :
				g_Display_type_O18 = pstParams->display_type;
				g_Display_mirror_O18 = pstParams->display_mirror;
				g_Frc_type_O18 = pstParams->frc_type;
				g_Trid_type_O18 = pstParams->trid_type;
				break;
			case LX_DE_CONFIG_TYPE_DISPLAY_DEVICE :
				g_Display_type_O18 = pstParams->display_type;
				break;
			case LX_DE_CONFIG_TYPE_DISPLAY_MIRROR:
				g_Display_mirror_O18 = pstParams->display_mirror;
				break;
			case LX_DE_CONFIG_TYPE_FRC :
				g_Frc_type_O18 = pstParams->frc_type;
				break;
			case LX_DE_CONFIG_TYPE_3D :
				g_Trid_type_O18 = pstParams->trid_type;
				break;
			case LX_DE_CONFIG_TYPE_MAX :
			default :
				BREAK_WRONG(pstParams->config_type);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->status_type) {
			case LX_DE_SYS_STATUS_ALL :
				pstParams->display_type = g_Display_type_O18;
				pstParams->display_mirror = g_Display_mirror_O18;
				pstParams->frc_type = g_Frc_type_O18;
				pstParams->trid_type = g_Trid_type_O18;
				pstParams->fc_mem = 0;
				pstParams->display_size = g_Display_size_O18;
				break;
			case LX_DE_SYS_STATUS_DISPALY_DEVICE :
				pstParams->display_type = g_Display_type_O18;
				break;
			case LX_DE_SYS_STATUS_DISPALY_MIRROR:
				pstParams->display_mirror = g_Display_mirror_O18;
				break;
			case LX_DE_SYS_STATUS_FRC :
				pstParams->frc_type = g_Frc_type_O18;
				break;
			case LX_DE_SYS_STATUS_3D :
				pstParams->trid_type = g_Trid_type_O18;
				break;
			case LX_DE_SYS_STATUS_FC_MEM:
				pstParams->fc_mem = 0;
				break;
			case LX_DE_SYS_STATUS_DISPALY_SIZE:
				pstParams->display_size = g_Display_size_O18;
				break;
			case LX_DE_SYS_STATUS_MAX :
			default :
				BREAK_WRONG(pstParams->status_type);
		}

	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->status_type) {
			case LX_DE_SRC_STATUS_ALL :
				pstParams->inSrc[LX_DE_WIN_MAIN] = g_WinsrcMap_O18[LX_DE_WIN_MAIN];
				pstParams->inSrcPort[LX_DE_WIN_MAIN] = g_WinsrcPort_O18[LX_DE_WIN_MAIN];
				pstParams->inSrc[LX_DE_WIN_SUB]	 = g_WinsrcMap_O18[LX_DE_WIN_SUB];
				pstParams->inSrcPort[LX_DE_WIN_SUB] = g_WinsrcPort_O18[LX_DE_WIN_SUB];

				pstParams->operType= g_SrcOperType_O18;
				pstParams->operCtrlFlag = g_SrcOperCtrlFlag_O18;

				pstParams->subOperType =  g_SrcSubOperType_O18;
				pstParams->subOperCtrlFlag = g_SrcSubOperCtrlFlag_O18;
				break;
			case LX_DE_SRC_STATUS_INPUT_SRC :
				pstParams->inSrc[LX_DE_WIN_MAIN] = g_WinsrcMap_O18[LX_DE_WIN_MAIN];
				pstParams->inSrcPort[LX_DE_WIN_MAIN] = g_WinsrcPort_O18[LX_DE_WIN_MAIN];
				pstParams->inSrc[LX_DE_WIN_SUB] = g_WinsrcMap_O18[LX_DE_WIN_SUB];
				pstParams->inSrcPort[LX_DE_WIN_SUB] = g_WinsrcPort_O18[LX_DE_WIN_SUB];
				break;
			case LX_DE_SRC_STATUS_OPER :
				pstParams->operType  = g_SrcOperType_O18;
				pstParams->operCtrlFlag = g_SrcOperCtrlFlag_O18;
				break;

			case LX_DE_SRC_STATUS_SUB_OPER :
				pstParams->subOperType =  g_SrcSubOperType_O18;
				pstParams->subOperCtrlFlag = g_SrcSubOperCtrlFlag_O18;
				break;

			case LX_DE_SRC_STATUS_VDEC_INFO :
				{
					UINT32 frame_rate_residual;
					UINT32 frame_rate_div;
					UINT32 framerate;
					UINT32 vdec_port;
					UINT32 scan;
					volatile LX_DE_VDEC_IPC_REG_T *p_vdec_ipc_reg;

					vdec_port = pstParams->inSrcPort[LX_DE_WIN_MAIN];
					if(vdec_port > 3)
					{
						DE_ERROR("invalid vdec port");
						vdec_port = 0;
					}

					p_vdec_ipc_reg = gDE_VDEC_O18[vdec_port];
					scan = p_vdec_ipc_reg->display_info.display_mode;

					frame_rate_residual	= p_vdec_ipc_reg->frame_rate.frame_rate_residual;
					frame_rate_div		= (p_vdec_ipc_reg->frame_rate.frame_rate_div > 0)?p_vdec_ipc_reg->frame_rate.frame_rate_div:1;
					framerate			= (frame_rate_residual * 100)/frame_rate_div;

					pstParams->vdecInfo.h_size = p_vdec_ipc_reg->picture_size.width;
					pstParams->vdecInfo.v_size = p_vdec_ipc_reg->picture_size.height;
					pstParams->vdecInfo.h_start = 0;
					pstParams->vdecInfo.v_start = 0;
					pstParams->vdecInfo.isProg = (scan==3)?1:0;
					pstParams->vdecInfo.v_freq = framerate;

					/*DE_NOTI("port->%d : h/v[%d/%d] scan[%d] fr[%d]", vdec_port, \
						pstParams->vdecInfo.h_size, pstParams->vdecInfo.v_size, \
						pstParams->vdecInfo.isProg, pstParams->vdecInfo.v_freq);*/
				}
				break;

			case LX_DE_SRC_STATUS_MAX :
			default :
				BREAK_WRONG(pstParams->status_type);
		}
	} while (0);

	return ret;


}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_OPER_CONFIG_T	type = LX_DE_OPER_ONE_WIN;
	UINT16 flag = 0;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->operation) {
			case LX_DE_OPER_ONE_WIN :
				type = LX_DE_OPER_ONE_WIN;
				break;

			case LX_DE_OPER_TWO_WIN :
				if(pstParams->multiCtrl != FALSE)		type = LX_DE_OPER_TWO_WIN;
				flag = pstParams->multiCtrl;
				break;
			case LX_DE_OPER_3D :
				if(pstParams->ctrl3D.run_mode != LX_DE_3D_RUNMODE_OFF && pstParams->ctrl3D.run_mode != LX_DE_3D_RUNMODE_MAX)
				{
					type = LX_DE_OPER_3D;
					flag = pstParams->ctrl3D.in_img_fmt;
				}
				break;

			case LX_DE_OPER_UD :
				if(pstParams->udCtrl != LX_DE_UD_OFF && pstParams->udCtrl != LX_DE_UD_MAX)
				{
					type = LX_DE_OPER_UD;
					flag = pstParams->udCtrl;
				}
				break;

			case LX_DE_OPER_VENC :
#if 0
				if(pstParams->vencCtrl.bOnOff != FALSE) {
					type = LX_DE_OPER_VENC;
					enable = TRUE;
				}
				break;
#endif
			case LX_DE_OPER_MAX :
			default :
				BREAK_WRONG(pstParams->operation);
		}

		g_SrcOperType_O18 = type;
		g_SrcOperCtrlFlag_O18 = flag;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT16 flag = 0;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->operation) {
			case LX_DE_SUB_OPER_OFF :
				g_SrcSubOperType_O18 = LX_DE_SUB_OPER_OFF;
				break;
			case LX_DE_SUB_OPER_CAPTURE:
				g_SrcSubOperType_O18 = LX_DE_SUB_OPER_CAPTURE;
				flag = pstParams->capture_enable;
				break;
			case LX_DE_SUB_OPER_VENC:
				g_SrcSubOperType_O18 = LX_DE_SUB_OPER_VENC;
				flag = pstParams->vencCtrl.bOnOff;
				break;
			case LX_DE_SUB_OPER_SCART_OUT:
				g_SrcSubOperType_O18 = LX_DE_SUB_OPER_SCART_OUT;
				flag = 1;
				break;
			case LX_DE_SUB_OPER_MAX :
			default :
				BREAK_WRONG(pstParams->operation);
		}
	} while (0);

	g_SrcSubOperCtrlFlag_O18 = flag;
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get fir coefficient for cvi
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir)
{
	int ret = RET_OK;
	int i = 0;
	// CVI FIR coefficient for Y - 11 Tap,Cbcr - 11 Tap
	UINT16 coef_FIR_Y_Normal[] = {256, 0, 0, 0, 0, 0, 0, 0};
	UINT16 coef_FIR_Y_Double[] = {256, 0, 0, 0, 0, 0, 0, 0};
	UINT16 coef_FIR_Y_Quad[]   = {64, 56, 34, 12, 0, -6, 0, 0};	// 55 >> 56 --> sum 254 >> 256
	UINT16 coef_FIR_O18_CVD_CbCr_Normal[] = {160, 49, -1, 0, 0, 0};// CVI FIR Filter for 1 pixel & 422
	UINT16 coef_FIR_CbCr_Normal[] = {128, 74, 0, -11, 0, 1};// CVI FIR Filter for 1 pixel & 422
	UINT16 coef_FIR_CbCr_Double[] = {160, 0, 49, 0, -1, 0};	// 55 >> 56 --> sum 254 >> 256
	UINT16 coef_FIR_CbCr_Quad[] = {64, 56, 34, 12, 0, -6};

	do {
		CHECK_KNULL(pstParams);

		fir->cvi_channel = pstParams->cvi_channel;

		switch (pstParams->sampling) {
			case LX_DE_CVI_NORMAL_SAMPLING:
				fir->isEnable = TRUE;
				for (i=0; i<NUM_OF_CVI_FIR_COEF; i++) {
					fir->fir_coef[i] = coef_FIR_Y_Normal[i];

					if (i<(NUM_OF_CVI_FIR_COEF-2)) {
						if (pstParams->cvi_input_src == LX_DE_CVI_SRC_ATV || pstParams->cvi_input_src == LX_DE_CVI_SRC_CVBS)
							fir->fir_coef_CbCr[i] = coef_FIR_O18_CVD_CbCr_Normal[i];
						else
							fir->fir_coef_CbCr[i] = coef_FIR_CbCr_Normal[i];
					}
				}
				break;

			case LX_DE_CVI_DOUBLE_SAMPLING:
				fir->isEnable = TRUE;
				for (i=0; i<NUM_OF_CVI_FIR_COEF; i++) {
					fir->fir_coef[i] = coef_FIR_Y_Double[i];
					if (i<(NUM_OF_CVI_FIR_COEF-2))
						fir->fir_coef_CbCr[i] = coef_FIR_CbCr_Double[i];
				}
				break;

			case LX_DE_CVI_QUAD_SAMPLING:
				fir->isEnable = TRUE;
				for (i=0; i<NUM_OF_CVI_FIR_COEF; i++) {
					fir->fir_coef[i] = coef_FIR_Y_Quad[i];
					if (i<(NUM_OF_CVI_FIR_COEF-2))
						fir->fir_coef_CbCr[i] = coef_FIR_CbCr_Quad[i];
				}
				break;

			default:
				BREAK_WRONG(pstParams->sampling);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set hdmi in-port for cvi
 *
 * @param arg [IN] hdmi port num
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams)
{
	int ret = RET_OK;

	g_HdmiPort_O18[pstParams->win_id] = pstParams->port_num;  // assign from vp_kadp
	DE_TRACE("win-hdmi map [%d / %d]", pstParams->win_id, pstParams->port_num);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get capacity
 *
 * @param arg [OUT] capa info
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_GetCapacity(LX_DE_CAPACITY_T *pstParams)
{
	int ret = RET_OK;

	pstParams->chip_id = 8;
	pstParams->max_win = 4;
	pstParams->max_layer = 4;
	pstParams->max_in_size.w = 3840;
	pstParams->max_in_size.h = 2160;
	pstParams->max_out_size.w = 3840;
	pstParams->max_out_size.h = 2160;
	pstParams->max_out_fr_rate = 60;
	pstParams->mvir_start_num = 2;
	pstParams->default_3d_out_fmt = LX_DE_3D_IMG_OUT_SINGLE_TB;

	pstParams->vtm_capa.maxResolution.x      = 0;
	pstParams->vtm_capa.maxResolution.y      = 0;
	pstParams->vtm_capa.maxResolution.w      = 3840;
	pstParams->vtm_capa.maxResolution.h      = 2160;
	pstParams->vtm_capa.bLeftTopAlign        = FALSE;
	pstParams->vtm_capa.bSupportInputVideoDeInterlacing   = TRUE;
	pstParams->vtm_capa.bSupportDisplayVideoDeInterlacing = TRUE;
	pstParams->vtm_capa.bSupportScaleUp      = TRUE;
	pstParams->vtm_capa.scaleUpLimitWidth    = 3840;
	pstParams->vtm_capa.scaleUpLimitHeight   = 2160;
	pstParams->vtm_capa.bSupportScaleDown    = TRUE;
	pstParams->vtm_capa.scaleDownLimitWidth  = 320;
	pstParams->vtm_capa.scaleDownLimitHeight = 240;
	pstParams->vtm_capa.locationLimit        = 2;

	DE_TRACE("max_win[%d], mvir_start_num[%d], 2d_3d_fmt[%d], VT deinter[%d]", \
		pstParams->max_win, \
		pstParams->mvir_start_num, \
		pstParams->default_3d_out_fmt, \
		pstParams->vtm_capa.bSupportInputVideoDeInterlacing);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get the status field of local mute register
 *
 * @param arg [OUT]  status of local mute
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_GetLocalMute(UINT32 *pstParams)
{
	int ret = RET_OK;
	UINT32 mute = 0;

	mute = DE_REG_O18_RD((void*)0xC90251F0); // PE1_MUTE_CTRL_00(b'28).pix_rep_in
	mute &= (1 << 28);
	*pstParams = mute?1:0;

	return ret;
}

int DE_REG_O18_SetMemByCma(char* mem_name)
{
	int ret = RET_OK;
	UINT32 base_addr = 0;
	int alloc_size = 0;

#ifdef O18_PQE_NEW_MEM
	g_FwBase_O18 = gpDeMem->fw[0].fw_base;

	if(strcmp(mem_name, "de-btbuf") == 0)
	{
		if (gpMemCfgBT_M1->fw_base)
		{
			alloc_size = gpMemCfgBT_M1->fw_size;
			base_addr  = gpMemCfgBT_M1->fw_base;
			if (hma_pool_register_type("de-bt-m1", base_addr, alloc_size, CMA_POOL) < 0)
			{
			     ret = RET_ERROR;
			}
			DE_NOTI("gpMemCfgBT_M1 base[0x%08X]  BT buffer size = %dMB", base_addr, alloc_size/1024/1024);

			alloc_size = gpMemCfgBT_M2->fw_size;
			base_addr  = gpMemCfgBT_M2->fw_base;
			if (hma_pool_register_type("de-bt-m2", base_addr, alloc_size, CMA_POOL) < 0)
			{
			     ret = RET_ERROR;
			}
			DE_NOTI("gpMemCfgBT_M2 base[0x%08X]  BT buffer size = %dMB", base_addr, alloc_size/1024/1024);

            if(o18_de_debug_mem)
            {
				DE_NOTI("pre-alloc %dMB@%s for debug\n", alloc_size/1024/1024, mem_name);
                hma_alloc(mem_name,  gpMemCfgBT_M1->fw_size, (1<<20));
				hma_alloc(mem_name,  gpMemCfgBT_M2->fw_size, (1<<20));
            }
		}
	}
	else if(strcmp(mem_name, "de-hdrbuf0") == 0)
	{
		if(gpMemCfgHDR->frame_base)
		{
			alloc_size = gpMemCfgHDR->frame_size;
			base_addr  = gpMemCfgHDR->frame_base;
			if(hma_pool_register_type("de-hdrbuf0",base_addr,alloc_size,HMA_POOL) < 0)
			{
				ret = RET_ERROR;
			}
			DE_NOTI("gpMemCfgHDR base[0x%08X] HDR buffer size = %dMB", base_addr, alloc_size/1024/1024);
		}
	}
	else if(strcmp(mem_name, "de-vtgshared") == 0)
	{
		alloc_size = VIDEO_O18_FIRMWARE_MEM_SIZE_WEB_OS;
		base_addr  = gpMemCfgDeFW_M0->fw_base;
		if(hma_pool_register_type("de-vtgshared",base_addr,alloc_size,HMA_POOL) < 0)
		{
			ret = RET_ERROR;
		}
		DE_NOTI("VTG shared base[0x%08X] size = %dKB", base_addr, alloc_size/1024);
	}
	else if(strcmp(mem_name, "de-vtgbuffer") == 0)
	{
		if(gpMemCfgVT_M1->fw_base)
		{
			alloc_size = gpMemCfgVT_M1->fw_size;
			base_addr  = gpMemCfgVT_M1->fw_base;
			if(hma_pool_register_type("de-vt-m1",base_addr,alloc_size,CMA_POOL) < 0)
			{
				ret = RET_ERROR;
			}
			DE_NOTI("gpMemCfgVT_M1 base[0x%08X] size = %dMB", base_addr, alloc_size/1024/1024);

			alloc_size = gpMemCfgVT_M2->fw_size;
			base_addr  = gpMemCfgVT_M2->fw_base;
			if(hma_pool_register_type("de-vt-m2",base_addr,alloc_size,CMA_POOL) < 0)
			{
				ret = RET_ERROR;
			}
			DE_NOTI("gpMemCfgVT_M2 base[0x%08X] size = %dMB", base_addr, alloc_size/1024/1024);
		}
	}
	else if(strcmp(mem_name, "de-fb") == 0)
	{

	}
#endif
	return ret;
}

static phys_addr_t bt_paddr_m1 = 0, bt_paddr_m2 = 0;
static phys_addr_t vtg_paddr_m1 = 0, vtg_paddr_m2 = 0;

int DE_REG_O18_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag)
{
	int ret = RET_OK;

#ifdef O18_PQE_NEW_MEM
	if(strcmp(mem_name, "de-btbuf") == 0)
	{
		if(flag)
		{
			/* hma alloc */
			if(bt_paddr_m1 != 0) { return -1; }
			bt_paddr_m1 = hma_alloc("de-bt-m1", gpMemCfgBT_M1->fw_size, (1<<20));
			if(bt_paddr_m1 == 0) { return -2; }
			bt_paddr_m2 = hma_alloc("de-bt-m2", gpMemCfgBT_M2->fw_size, (1<<20));
			if(bt_paddr_m2 == 0) { return -2; }
		}
		else
		{
			if(bt_paddr_m1 != 0)
			{
				hma_free("de-bt-m1", bt_paddr_m1);
				hma_free("de-bt-m2", bt_paddr_m2);
				bt_paddr_m1 = 0;
				bt_paddr_m2 = 0;
			}
		}
		DE_NOTI("BT %s : start = 0x%08X/0x%08X, size = %dMB/%dMB", flag?"alloc":"free", \
			gpMemCfgBT_M1->fw_base, gpMemCfgBT_M2->fw_base, \
			gpMemCfgBT_M1->fw_size/1024/1024, gpMemCfgBT_M2->fw_size/1024/1024);
	}
	else if(strcmp(mem_name, "de-hdrbuf") == 0)
	{

	}
	else if(strcmp(mem_name, "de-vtgshared") == 0)
	{

	}
	else if(strcmp(mem_name, "de-vtgbuffer") == 0)
	{
		if(flag)
		{
			/* hma alloc */
			if(vtg_paddr_m1 != 0) { return -1; }
			vtg_paddr_m1 = hma_alloc("de-vt-m1", count*O18_DE_MEM_SIZE_VT_M1_CMA/*gpMemCfgVT_M1->fw_size*/, (1<<20));
			if(vtg_paddr_m1 == 0) { return -2; }
			vtg_paddr_m2 = hma_alloc("de-vt-m2", count*O18_DE_MEM_SIZE_VT_M2_CMA/*gpMemCfgVT_M2->fw_size*/, (1<<20));
			if(vtg_paddr_m2 == 0) { return -2; }
		}
		else
		{
			if(vtg_paddr_m1 != 0)
			{
				hma_free("de-vt-m1", vtg_paddr_m1);
				hma_free("de-vt-m2", vtg_paddr_m2);
				vtg_paddr_m1 = 0;
				vtg_paddr_m2 = 0;
			}
		}
		DE_NOTI("VTG %s : start = 0x%08X/0x%08X, size = %dMB/%dMB", flag?"alloc":"free", \
			gpMemCfgVT_M1->fw_base, gpMemCfgVT_M2->fw_base, \
			/*gpMemCfgVT_M1->fw_size*/count*O18_DE_MEM_SIZE_VT_M1_CMA/1024/1024, \
			/*gpMemCfgVT_M2->fw_size*/count*O18_DE_MEM_SIZE_VT_M2_CMA/1024/1024);

	}
	else if(strcmp(mem_name, "de-fb") == 0)
	{

	}
#endif
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set multi window information
 *
 * @param arg [IN] control param
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetMultiWin(UINT32 *pstParams)
{
	int ret = RET_OK;

	g_QuadWin_O18 = (*pstParams==4)?TRUE:FALSE;

	DE_NOTI("multi window control for quad [%d]", *pstParams);

	return ret;
}

int DE_REG_O18_SetClockGate(CTOP_PQE_CG_O18_MODULE mod, BOOLEAN onOff)
{
	int ret = RET_OK;

#if 0//def	USE_CTOP_CODES_FOR_O18
	switch(mod)
	{
		case CG_O18_IMX: /* CG enable : 0x00000060, disable : 0x00000000 */
			CTOP_CTRL_O18A0_RdFL(IMX_SYN, crg_imx00);
			CTOP_CTRL_O18A0_Wr01(IMX_SYN, crg_imx00, hdr_clk_gate_en, onOff);      // [5]
			CTOP_CTRL_O18A0_Wr01(IMX_SYN, crg_imx00, hdrh_clk_gate_en, onOff);     // [6]
			CTOP_CTRL_O18A0_WrFL(IMX_SYN, crg_imx00);
			break;
		case CG_O18_VSD: /* CG enable : 0x00000026, disable : 0x00000000 */
			CTOP_CTRL_O18A0_RdFL(VSD_SYN, crg_vsd00);
			CTOP_CTRL_O18A0_Wr01(VSD_SYN, crg_vsd00, det_clk_gate_en, onOff);      // [1]
			CTOP_CTRL_O18A0_Wr01(VSD_SYN, crg_vsd00, disp_stb_clk_gate_en, onOff); // [2]
			CTOP_CTRL_O18A0_Wr01(VSD_SYN, crg_vsd00, h3d_le_clk_gate_en, onOff);   // [5]
			CTOP_CTRL_O18A0_WrFL(VSD_SYN, crg_vsd00);
			break;
		case CG_O18_CCO: /* CG enable : 0x000000DE, disable : 0x00000000 */
			CTOP_CTRL_O18A0_RdFL(CCO_SYN, crg_cco00);
			CTOP_CTRL_O18A0_Wr01(CCO_SYN, crg_cco00, det_clk_gate_en, onOff);      // [1]
			CTOP_CTRL_O18A0_Wr01(CCO_SYN, crg_cco00, disp_clk_gate_en, onOff);     // [2]
			CTOP_CTRL_O18A0_Wr01(CCO_SYN, crg_cco00, disp_dsc_clk_gate_en, onOff); // [3]
			CTOP_CTRL_O18A0_Wr01(CCO_SYN, crg_cco00, sosd_clk_gate_en, onOff);     // [4]
			CTOP_CTRL_O18A0_Wr01(CCO_SYN, crg_cco00, led_pxl_clk_gate_en, onOff);  // [6]
			CTOP_CTRL_O18A0_Wr01(CCO_SYN, crg_cco00, led_fbc_clk_gate_en, onOff);  // [7]
			CTOP_CTRL_O18A0_WrFL(CCO_SYN, crg_cco00);
			break;
		case CG_O18_DPE: /* CG enable : 0x002001FC , disable : 0x00200000 */
			CTOP_CTRL_O18A0_RdFL(DPE_SYN, crg_dpe00);
			CTOP_CTRL_O18A0_Wr01(DPE_SYN, crg_dpe00, tcon_pix2_clk_gate_en, onOff);// [2]
			CTOP_CTRL_O18A0_Wr01(DPE_SYN, crg_dpe00, tcon_pix_clk_gate_en, onOff); // [3]
			CTOP_CTRL_O18A0_Wr01(DPE_SYN, crg_dpe00, tcon_osd_clk_gate_en, onOff); // [4]
			CTOP_CTRL_O18A0_Wr01(DPE_SYN, crg_dpe00, tcon_osc_clk_gate_en, onOff); // [5]
			CTOP_CTRL_O18A0_Wr01(DPE_SYN, crg_dpe00, tcon_pix4_clk_gate_en, onOff);// [6]
			CTOP_CTRL_O18A0_Wr01(DPE_SYN, crg_dpe00, tcon_mcu_clk_gate_en, onOff); // [7]
			CTOP_CTRL_O18A0_Wr01(DPE_SYN, crg_dpe00, tcon_mem_clk_gate_en, onOff); // [8]
			CTOP_CTRL_O18A0_WrFL(DPE_SYN, crg_dpe00);
			break;
		case CG_O18_CVI:
			CTOP_CTRL_O18A0_RdFL(CTRL_CVI, crg_cvi02);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, cvi0_clk_gate_en, onOff);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, cvi1_clk_gate_en, onOff);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, cvi2_clk_gate_en, onOff);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, cvi3_clk_gate_en, onOff);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, cvi4_clk_gate_en, onOff);
			CTOP_CTRL_O18A0_Wr01(CTRL_CVI, crg_cvi02, cvi5_clk_gate_en, onOff);
			CTOP_CTRL_O18A0_WrFL(CTRL_CVI, crg_cvi02);
			break;
		case CG_O18_ND0:
		default:
			DE_ERROR("Not implemented.");
			break;
	}
#endif
	return ret;
}

//#define ADD_CLOCK_GATING
int DE_REG_O18_SetClockPath(BOOLEAN onOff)
{
	DE_NOTI("select clock source [ %s ]", onOff?"HDMI":"DCO");

#ifdef ADD_CLOCK_GATING
	// PQE/DISP Block Clock gating Enable
	DE_REG_O18_SetClockGate(CG_O18_CCO, TRUE);
	DE_REG_O18_SetClockGate(CG_O18_DPE, TRUE);
	DE_REG_O18_SetClockGate(CG_O18_IMX, TRUE);
	DE_REG_O18_SetClockGate(CG_O18_VSD, TRUE);
//	DE_REG_O18_SetClockGate(CG_O18_CVI, TRUE);
#endif
#if 0//def	USE_CTOP_CODES_FOR_O18
	switch(g_Diplay_type_from_loader)
	{
		case LX_PANEL_TYPE_1920: // 60Hz
		case LX_PANEL_TYPE_3840:

			DE_NOTI("60Hz mode");

			if(onOff) // game mode enable
			{
				// DISPLAY PLL Frequnecy changed (Input Freq : 37.125Mhz, Output Freq : 594 / 74.25Mhz)
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r30);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB00045DC);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r29, 0x07A40280);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r30, 0x01400000);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r30);

				// Game mode setting (HDMI_PIX_CLK : 148.5Mhz, 8bit )
				CTOP_CTRL_O18A0_RdFL(CTRL_CVI, syn_cvi03);
				CTOP_CTRL_O18A0_Wr(CTRL_CVI, syn_cvi03, 0x63);//[0]:dco_clock_selection,[1]:game_mode_enable,[6:5]:594,297,148.5,74.25,[7]int_clear
				CTOP_CTRL_O18A0_WrFL(CTRL_CVI, syn_cvi03);

				// Disp pll의 Spread setting
				// Game Mode DISPLAY PLL Frequnecy changed (Input Freq : 37.125Mhz , 0.5%, 27Khz)
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r30);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB0022514);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r29, 0x07A40280);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r30, 0x01400000);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r30);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB0022510);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
			}
			else // game mode disable
			{
				// Game mode disable setting
				CTOP_CTRL_O18A0_RdFL(CTRL_CVI, syn_cvi03);
				CTOP_CTRL_O18A0_Wr(CTRL_CVI, syn_cvi03, 0x22);
				CTOP_CTRL_O18A0_WrFL(CTRL_CVI, syn_cvi03);

				//DISPLAY PLL Frequnecy changed (Input Freq(DCO) : 27Mhz, Output Freq : 594 / 74.25Mhz)
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r30);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0x100045DC);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r29, 0x0AA40280);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r30, 0x00400000);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r30);

				// Disp pll의 Spread setting
				// Normal Mode DISPLAY PLL Frequnecy changed (Input Freq : 27Mhz , 0.5%, 27Khz)
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r30);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB8013694);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r29, 0x0AA40280);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r30, 0x01400000);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r30);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB0013688);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
			}
			break;
		case LX_PANEL_TYPE_1920_120P: // 120Hz
		case LX_PANEL_TYPE_3840_120P:

			DE_NOTI("120Hz mode");

			if(onOff) // game mode enable
			{
				// DISPLAY PLL Frequnecy changed (Input Freq : 37.125Mhz, Output Freq : 594 / 74.25Mhz)
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r30);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB00045DC);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r29, 0x07A40280);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r30, 0x00400000);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r30);

				// Game mode setting (HDMI_PIX_CLK : 148.5Mhz, 8bit )
				//[0]:dco_clock_selection,[1]:game_mode_enable,[6:5]:594,297,148.5,74.25,[7]int_clear
				CTOP_CTRL_O18A0_RdFL(CTRL_CVI, syn_cvi03);
				CTOP_CTRL_O18A0_Wr(CTRL_CVI, syn_cvi03, 0x63); // [0]:0-from dpll, 1-from hdmi rx clock
				CTOP_CTRL_O18A0_WrFL(CTRL_CVI, syn_cvi03);
			}
			else // game mode disable
			{
				//DISPLAY PLL Frequnecy changed (Input Freq(DCO) : 27Mhz, Output Freq : 594 / 74.25Mhz)
				#if 1
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r30);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0x100045DC);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r29, 0x0AA40280);
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r30, 0x00400000);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r29);
				CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r30);
				#endif

				// Game mode disable setting
				CTOP_CTRL_O18A0_RdFL(CTRL_CVI, syn_cvi03);
				CTOP_CTRL_O18A0_Wr(CTRL_CVI, syn_cvi03, 0x22); // [0]:0-from dpll, 1-from hdmi rx clock
				CTOP_CTRL_O18A0_WrFL(CTRL_CVI, syn_cvi03);
			}
			break;
		default:
			break;
	}
#endif
#ifdef ADD_CLOCK_GATING
	// PQE/DISP Block Clock gating Disable
	DE_REG_O18_SetClockGate(CG_O18_CCO, FALSE);
	DE_REG_O18_SetClockGate(CG_O18_DPE, FALSE);
	DE_REG_O18_SetClockGate(CG_O18_IMX, FALSE);
	DE_REG_O18_SetClockGate(CG_O18_VSD, FALSE);
//	DE_REG_O18_SetClockGate(CG_O18_CVI, FALSE);
#endif
	return RET_OK;
}

int DE_REG_O18_GetLowDelayClock(UINT32 *pstParams)
{
	int ret = RET_OK;

	*pstParams = g_Zero_delay_mode;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set ctop clock for zero delay
 *
 * @param arg [IN] control param
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_SetLowDelayClock(UINT32 *pstParams)
{
	int ret = RET_OK;
	OS_FILE_T file;

	ret = DE_REG_O18_SetClockPath((BOOLEAN)*pstParams);

	g_Zero_delay_mode = *pstParams; // 0:OFF, 1:5V_HPD, 2:CVI_INTR

	DE_CVC_O18_RdFL(intr_mask);

	if(g_Zero_delay_mode)
	{
		if(RET_OK != OS_OpenFile(&file, "/var/cvi_intr", O_RDONLY, 0666))
		{
			DE_CVC_O18_Wr01(intr_mask, mask_cvi1_field, 1);// intr mask
			g_Zero_delay_mode = 1;
			DE_NOTI("use HDMI HPD down");
		}
		else
		{
			DE_CVC_O18_Wr01(intr_mask, mask_cvi1_field, 0);// intr unmask
			g_Zero_delay_mode = 2;
			OS_CloseFile(&file);
			DE_NOTI("use CVI Intr");
		}
	}
	DE_CVC_O18_WrFL(intr_mask);

	DE_NOTI("g_Zero_delay_mode = %d  (0:OFF, 1:5V_HPD, 2:CVI_INTR)", g_Zero_delay_mode);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get shared mem for mmap
 *
 * @param arg [IN] page_offset, mem_info(start/end/size)
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_O18_GetSharedMem(UINT32 page_offset, UINT32 **mem_info)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(mem_info);

		*mem_info[0] = gpMemCfgDeFW_M0->fw_base;
		*mem_info[1] = gpMemCfgDeFW_M0->fw_base + gpMemCfgDeFW_M0->fw_size;
		*mem_info[2] = gpMemCfgDeFW_M0->fw_size;
	} while(0);

	return ret;
}

int DE_REG_O18_GetFPPInfo(UINT32 *start_address)
{
	int ret = RET_OK;

	*start_address = gpMemCfgDeFW_M0->fw_base + (VIDEO_O18_FIRMWARE_MEM_SIZE_WEB_OS<<1);

	return ret;
}

int DE_REG_O18_GetMEMInfo(LX_DE_IPC_SYSTEM_NEW_T *pstParams)
{
	int ret = RET_OK;

	if(!pstParams) return RET_ERROR;

	memcpy(pstParams, &g_Mem_Info, sizeof(LX_DE_IPC_SYSTEM_NEW_T));

	return ret;
}

int DE_REG_O18_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f)
{
	int ret = RET_OK;
	UINT32 *lpAddr = NULL;
	UINT32 phys = g_Mem_Info.fpp_info.base + VIDEO_O18_FIRMWARE_MEM_SIZE_WEB_OS; // fpp_info.base + 32*1024

	lpAddr	= (UINT32 *)vmap_phys(phys, 4 * 6);

	if (!lpAddr)
	{
		DE_ERROR("vmap fail");
		return RET_ERROR;
	}

	*a = lpAddr[0];
	*b = lpAddr[1];
	*c = lpAddr[2];
	*d = lpAddr[3];
	*e = lpAddr[4];
	*f = lpAddr[5];
	
	if (lpAddr) vunmap_phys(lpAddr);

	return ret;
}

int DE_REG_O18_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_VIDEO_DELAY_INFO_T *lpAddr = NULL;

	if(!pstParams) return RET_ERROR;

	lpAddr	= (LX_DE_VIDEO_DELAY_INFO_T *)vmap_phys(g_Mem_Info.shared_mem_info.video_delay_info.base,  g_Mem_Info.shared_mem_info.video_delay_info.size);
	if(!lpAddr)
	{
		return RET_ERROR;
	}
	pstParams->win_id = lpAddr->win_id;
	pstParams->delay = lpAddr->delay;
	pstParams->rect.x = lpAddr->rect.x;
	pstParams->rect.y = lpAddr->rect.y;
	pstParams->rect.w = lpAddr->rect.w;
	pstParams->rect.h = lpAddr->rect.h;

	if (lpAddr) vunmap_phys((void*)lpAddr);

	return ret;
}


#endif
/**  @} */
