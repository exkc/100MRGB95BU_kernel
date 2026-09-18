/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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

/** @file
 *
 *	main configuration for lg115x driver
 *
 *  author		raxis.lim@lge.com
 *  version		1.0
 *  date		2018.04.24
 *
 *  @addtogroup lg1150_base
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ctype.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/delay.h>

#include "base_types.h"
#include "base_device.h"
#include "debug_util.h"
#include "os_util.h"

#include "hma_alloc.h"
#include "audio/audio_cfg.h"

#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
#endif
#ifdef INCLUDE_KDRV_FBDEV
#include "fbdev_cfg.h"
#endif
#ifdef INCLUDE_KDRV_GFX
#include "gfx_cfg.h"
#endif
#ifdef INCLUDE_KDRV_TE
#include "te_cfg.h"
#endif
#ifdef INCLUDE_KDRV_VBI
#include "vbi_cfg.h"
#endif
#ifdef INCLUDE_KDRV_OVI
#include "ovi_cfg.h"
#endif
#ifdef INCLUDE_KDRV_BE
#include "be_cfg.h"
#endif
#ifdef INCLUDE_KDRV_SE
#include "se_cfg.h"
#endif
#ifdef INCLUDE_KDRV_VENC
#include "venc_cfg.h"
#endif
#ifdef INCLUDE_KDRV_PNG
#include "png_cfg.h"
#endif
#ifdef INCLUDE_KDRV_AFE
#include "afe_cfg.h"
#endif
#ifdef INCLUDE_KDRV_MJPEG
#include "mjpeg_cfg.h"
#endif
#ifdef INCLUDE_KDRV_PE
#include "pe_cfg.h"
#endif
#ifdef INCLUDE_KDRV_DEMOD
#include "demod_cfg.h"
#endif

#ifdef INCLUDE_KDRV_LGBUS
#include "lgbus_cfg.h"
#endif

#ifdef PLATFORM_FPGA	// When INCLUDE_KDRV_BE is not enable in FPGA, we have to use BE_FRC memory.
#include "../../core/be/be_cfg.h"
#endif

#include "platform_mem_map.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#define LX_MEMCFG_ENTRY(item)				{ .name= _STR(item), .pM=(LX_MEMCFG_T*)&(item), .nM=sizeof(item)/sizeof(LX_MEMCFG_T) }
#define LX_MEMCFG_ENTRY_EX(item,alias)		{ .name= _STR(item), .pM=(LX_MEMCFG_T*)&(item), .nM=sizeof(item)/sizeof(LX_MEMCFG_T), .flag=LX_MEMCFG_FLAG_ALIAS, .pAlias=&alias }
#define LX_MEMCFG_ENTRY_END					{ .name="Total", .pM=NULL, .nM=0}

#define	__L_BUS__			0
#define	__G_BUS__			1

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	DDR_RGN_M0_DEV 		= 0,
	DDR_RGN_M1_DEV,
	DDR_RGN_MAX,
}
DDR_RGN_T;

typedef enum
{
	MEM_DESC_ID_GFX = 0,
	MEM_DESC_ID_MJPEG,
	MEM_DESC_ID_VENC,
	MEM_DESC_ID_AUDIO,
	MEM_DESC_ID_FBDEV,
	MEM_DESC_ID_DE,
	MEM_DESC_ID_DE_PREW,
	MEM_DESC_ID_DE_FW0,
	MEM_DESC_ID_DE_FW1,
	MEM_DESC_ID_DE_FW2,
	MEM_DESC_ID_DE_FRM1,		/* DE FRAME M1 */
	MEM_DESC_ID_DE_FRM2,		/* DE FRAME M2 */
	MEM_DESC_ID_VDEC0,
	MEM_DESC_ID_VDEC1,
	MEM_DESC_ID_VDEC_HFR,
	MEM_DESC_ID_SYS,
	MEM_DESC_ID_SE,
	MEM_DESC_ID_SE_TZFW,
	MEM_DESC_ID_TE,
	MEM_DESC_ID_DEMOD,
	MEM_DESC_ID_TCON,
	MEM_DESC_ID_BT0,			/* BT M0 */
	MEM_DESC_ID_BT1,			/* BT M1 */
	MEM_DESC_ID_VT0,			/* VT M0 */
	MEM_DESC_ID_VT1,			/* VT M1 */
	MEM_DESC_ID_HDR,
	MEM_DESC_ID_VBI,
	MEM_DESC_ID_CVD,
	MEM_DESC_ID_DEMOD_FW,
	MEM_DESC_ID_BE,
	MEM_DESC_ID_BE_FRC0,		/* BE_FRC M0 */
	MEM_DESC_ID_BE_FRC1,		/* BE_FRC M1 */
	MEM_DESC_ID_BE_FRC2,		/* BE FRC M2 */
	MEM_DESC_ID_BE_FRC3,		/* BE FRC M2 */
	MEM_DESC_ID_CALIB,
	MEM_DESC_ID_PE,
	MEM_DESC_ID_MAX,
}
MEM_DESC_ID_T;

typedef struct
{
#define	MEMCFG_DESC_FLAG_NONE		0x00000000	/* device such as SE/TZ should keep memory content from the booting stage */
#define	MEMCFG_DESC_FLAG_CMA		0x4F434D41	/* device will manage dedicated memory according to its own policy */
#define	MEMCFG_DESC_FLAG_NO_CMA		0x4E434D41	/* device requires the pre-allocated device memory */
	UINT32		flag;
	LX_MEMCFG_T	m;
}
LX_MEMCFG_DESC_T;

typedef enum
{
	MODEL_OPT_UHD				= 0x0,
	MODEL_OPT_FHD				= 0x1,

	MODEL_OPT_DDR_1_5_GB_STD	= 0x1,		/* 60Hz panel OR HDMI Tx */
	MODEL_OPT_DDR_2_0_GB_ADV	= 0x2,		/* 120Hz panel */
	MODEL_OPT_DDR_3_0_GB_ADV	= 0x3,		/* 120Hz panel */

	MODEL_OPT_USR				= 0x1,		/* enable USR option */

	MODEL_OPT_NO_FRC			= 0x0,
	MODEL_OPT_INT_FRC			= 0x1,		/* default value */
	MODEL_OPT_EXT_FRC			= 0x2,

    MODEL_OPT_60HZ              = 0x0,
    MODEL_OPT_120HZ             = 0x1,      /* default value */

	MODEL_OPT_PANEL_NONE		= 0x0,		/* no panel = stbbox */
	MODEL_OPT_PANEL_LCD			= 0x1,
	MODEL_OPT_PANEL_OLED		= 0x2,

	MODEL_OPT_LOW_POWER			= 0x1,
}
MODEL_OPT_T;

typedef struct
{
	MODEL_OPT_T	mmap_cfg;
	MODEL_OPT_T	ddr_size;
	MODEL_OPT_T disp_model;
	MODEL_OPT_T frc_conn;
	MODEL_OPT_T frc_hz;
	MODEL_OPT_T panel;

	MODEL_OPT_T low_power;

	MODEL_OPT_T usr0;
	MODEL_OPT_T usr1;					/* if defined, we try to setup test environment for 4K120 video decoder */
	MODEL_OPT_T usr2;
	MODEL_OPT_T usr3;
}
MODEL_OPT_CTX_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern 	char*	simple_strtok(char *s, const char *delim, char **save_ptr);
extern	int     BASE_DEVMEM_InitDevMem( LX_MEMCFG_ENTRY_T* pEntry );

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
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
static int 	webos_hwopt_probe = 1;
module_param_named(webos_hwopt_probe, webos_hwopt_probe, int, 0644 );

static MODEL_OPT_CTX_T	g_model_ctx = { .ddr_size	= MODEL_OPT_DDR_2_0_GB_ADV,	/* 2GB by default */
										.disp_model = MODEL_OPT_UHD,			/* UHD by default */
										.frc_conn	= MODEL_OPT_INT_FRC,		/* INT_FRC default */
										.frc_hz     = MODEL_OPT_120HZ,          /* 120HZ   default */
										.panel		= MODEL_OPT_PANEL_LCD,		/* LCD/LED default */
										.low_power	= 0,						/* LOW_POWER_OFF default */
										.usr0		= 0,
										.usr1		= 0,
										.usr2		= 0,
										.usr3		= 0 };


static LX_MEMCFG_T	gMemCfgHdr[DDR_RGN_MAX]={{.name = "[header] DDR0",	.base = 0x0, .size = 0 },	/* mem header */
											{ .name = "[header] DDR1",	.base = 0x0, .size = 0 }};	/* mem header */

static LX_MEMCFG_T	static_rgn_m0_start 	= { .name = "static(DDR0)",	.base = 0x0, .size = 0 };	/* mem separator */
static LX_MEMCFG_T	static_rgn_m1_start		= { .name = "static(DDR1)",	.base = 0x0, .size = 0 };	/* mem separator */

static LX_MEMCFG_T vdec0_hma				= { .name = "vdec0_hma",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec1_hma				= { .name = "vdec1_hma",	.base = 0x0, .size = 0 };

#ifdef USE_AUDIO_STATIC_RGN
static LX_MEMCFG_T	static_rgn_aud_start 	= { .name = "static(AUD)",	.base = 0x0, .size = 0 };	/* mem separator */
#endif

static LX_MEMCFG_T gMemCfgM1Calib			= {.name = "calib(DDR1)", 	.base = 0x0, .size = DDR_CALIB_RGN_SZ };
static LX_MEMCFG_T gMemCfgSYS				= {.name = "system",		.base = 0x0, .size = __MB(1) };

/* memory alias list for CMA processing */
#define MEM_DESC(n)				(mem_desc[MEM_DESC_ID_##n].m)
#define MEM_DESC_NAME(n)		(mem_desc[MEM_DESC_ID_##n].m.name)
#define MEM_DESC_BASE(n)		(mem_desc[MEM_DESC_ID_##n].m.base)
#define MEM_DESC_SIZE(n)		(mem_desc[MEM_DESC_ID_##n].m.size)
#define MEM_DESC_FLAG(n)		(mem_desc[MEM_DESC_ID_##n].flag)

#define DEFINE_MEM_DESC(n,f)	[MEM_DESC_ID_##n] = { .m={ .name = #n"_cma", .base = 0x0, .size = 0 }, .flag=f }

static LX_MEMCFG_DESC_T mem_desc[MEM_DESC_ID_MAX]	= {
	DEFINE_MEM_DESC(GFX		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(MJPEG	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VENC	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(AUDIO	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(FBDEV	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW0	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW1	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW2	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FRM1	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FRM2	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_PREW	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VDEC0	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VDEC1	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VDEC_HFR,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(TE		,MEMCFG_DESC_FLAG_CMA),

	DEFINE_MEM_DESC(SYS		,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(SE		,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(SE_TZFW	,MEMCFG_DESC_FLAG_NONE),

	DEFINE_MEM_DESC(DEMOD	,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(TCON	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BT0		,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(BT1		,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(VT0		,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(VT1		,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(HDR		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VBI		,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(CVD		,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(DEMOD_FW,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC0	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC1	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC2	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC3	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(CALIB	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(PE		,MEMCFG_DESC_FLAG_NO_CMA),
};

/*---------------------------------------------------------------------------------------
 * Global Memory Configuration data base
 *--------------------------------------------------------------------------------------*/
static LX_MEMCFG_ENTRY_T* g_mem_desc_table;

/* DDR 1.5 MODEL */
static LX_MEMCFG_ENTRY_T g_mem_desc_table_DDR_1_5_GB_STD[] =	/* default map */
{
	/* null */
};

static LX_MEMCFG_ENTRY_T g_mem_desc_table_DDR_2_0_GB_ADV[] =	/* 2.0GB ADV */
{
	//-----------------------------------------------------------------------------------
	//	DDR (LBUS_DEV)
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec0_hma, MEM_DESC(VDEC0)),				/* VDEC HMA */
	LX_MEMCFG_ENTRY_EX(vdec1_hma, MEM_DESC(VDEC1)),				/* VDEC HMA */
#endif

#ifdef INCLUDE_KDRV_GFX
	LX_MEMCFG_ENTRY_EX(gMemCfgGfx.surface[0], MEM_DESC(GFX)),	/* GFX */
#endif

#ifdef INCLUDE_KDRV_VENC
	LX_MEMCFG_ENTRY_EX(gMemCfgVenc, MEM_DESC(VENC)),			/* VENC */
#endif

#ifdef INCLUDE_KDRV_MJPEG
	LX_MEMCFG_ENTRY_EX(gMemCfgMjpeg, MEM_DESC(MJPEG)),			/* MJPEG */
#endif

#ifdef INCLUDE_KDRV_OVI
    LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[1], MEM_DESC(TCON)),		/* OVI TCON */
#endif

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(gMemCfgDeFW[0], MEM_DESC(DE_FW1)),		/* DE FW(1MB)_M0 MCU1 + shared mem */
	LX_MEMCFG_ENTRY_EX(gMemCfgM19[0], MEM_DESC(DE_PREW)),		/* DE PREW_M0 */
	LX_MEMCFG_ENTRY_EX(gMemCfgHDR[1], MEM_DESC(HDR)),			/* HDR(3MB) M0 */
#endif

#ifdef INCLUDE_KDRV_FBDEV
	LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),			/* FBDEV */
#endif
	LX_MEMCFG_ENTRY(static_rgn_aud_start),
	LX_MEMCFG_ENTRY_EX(gMemCfgAud[1], MEM_DESC(AUDIO)),			/* AUDIO - MS12 V20 */

	LX_MEMCFG_ENTRY(static_rgn_m0_start),
	LX_MEMCFG_ENTRY_EX(gMemCfgSYS, MEM_DESC(SYS)),				/* SYS */
#ifdef INCLUDE_KDRV_SE
	LX_MEMCFG_ENTRY_EX(gMemCfgSE[0], MEM_DESC(SE)),				/* SE */
	LX_MEMCFG_ENTRY_EX(gMemCfgSE_TZFW[0], MEM_DESC(SE_TZFW)),	/* SE/TZ */
#endif

	//-----------------------------------------------------------------------------------
	//	DDR (RGN_M1_DEV)
	//----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M1_DEV]),


#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(gMemCfgDeFW[2], MEM_DESC(DE_FW2)),		/* DE FW(4MB)_M1 MCU0  */
	//LX_MEMCFG_ENTRY_EX(gMemCfgM19[1], MEM_DESC(DE_FRM1)),		/* DE_FRM1 : not used at M16P3 */
	LX_MEMCFG_ENTRY_EX(gMemCfgM19[2], MEM_DESC(DE_FRM2)),		/* DE FRM2 */
	//LX_MEMCFG_ENTRY_EX(gMemCfgM19[3], MEM_DESC(BT0)),			/* DE_BT0 : not used at M16P3 */
	LX_MEMCFG_ENTRY_EX(gMemCfgM19[4], MEM_DESC(BT1)),			/* DE_BT1 */
	//LX_MEMCFG_ENTRY_EX(gMemCfgM19[5], MEM_DESC(VT0)),			/* DE_VT0 : not used at M16P3 */
	LX_MEMCFG_ENTRY_EX(gMemCfgM19[6], MEM_DESC(VT1)),			/* DE_VT1 */
#endif

#ifdef INCLUDE_KDRV_DE
	#ifdef INCLUDE_KDRV_BE
	LX_MEMCFG_ENTRY_EX(gMemCfgBe[2], 	MEM_DESC(BE)),			/* BE */
//    LX_MEMCFG_ENTRY_EX(gMemCfgBeFrc[2], MEM_DESC(BE_FRC0)),		/* BE FRC */
//    LX_MEMCFG_ENTRY_EX(gMemCfgBeFrc[3], MEM_DESC(BE_FRC1)),		/* BE FRC0 */
//    LX_MEMCFG_ENTRY_EX(gMemCfgBeFrc[4], MEM_DESC(BE_FRC2)),		/* BE FRC1 */
//    LX_MEMCFG_ENTRY_EX(gMemCfgBeFrc[5], MEM_DESC(BE_FRC3)),		/* BE FRC2 */
	#endif
#endif

#ifdef INCLUDE_KDRV_PE
	LX_MEMCFG_ENTRY_EX(gMemCfgPe[0], 	MEM_DESC(PE)),			/* PE */
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),	/* VBI Buffer */
#endif

#ifdef INCLUDE_KDRV_AFE
    LX_MEMCFG_ENTRY_EX(gCvdMemCfg, MEM_DESC(CVD)),				/* CVD (3DComb H/W Memory) */
#endif

#ifdef INCLUDE_KDRV_TE
	LX_MEMCFG_ENTRY_EX(gMemCfgTE,	MEM_DESC(TE)),				/* SDEC/TE */
#endif

#ifdef INCLUDE_KDRV_DEMOD
	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),	/* DEMOD_FW */
#endif

	LX_MEMCFG_ENTRY(static_rgn_m1_start),
    LX_MEMCFG_ENTRY_EX(gMemCfgM1Calib, MEM_DESC(CALIB)),		/* CALIB */

	LX_MEMCFG_ENTRY_END
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static void BASE_PLT_SetupCommon(void)
{
	/* setup static mem region - 16MB @ L_BUS */
	static_rgn_m0_start.base = gMemCfgHdr[DDR_RGN_M0_DEV].base + gMemCfgHdr[DDR_RGN_M0_DEV].size - M0_SYSTEM_RGN_SZ;

    /* setup static mem region - 16KB E_BUS */
    static_rgn_m1_start.base = gMemCfgHdr[DDR_RGN_M1_DEV].base + gMemCfgHdr[DDR_RGN_M1_DEV].size - M1_SYSTEM_RGN_SZ;

    /* setup DDR calibration - end address of M1 */
    gMemCfgM1Calib.base 	= gMemCfgHdr[DDR_RGN_M1_DEV].base + gMemCfgHdr[DDR_RGN_M1_DEV].size - DDR_CALIB_RGN_SZ;

    // setup AUDIO to guarantee the minimal memory requirement.
#ifdef USE_AUDIO_STATIC_RGN
    static_rgn_aud_start.base = static_rgn_m0_start.base - UHD_AUDIO_SZ;
#endif

	// setup GFX
#ifdef INCLUDE_KDRV_GFX
	gMemCfgGfx.surface[0].size	= UHD_GFXOSD_SZ;
#endif

	// setup VDEC
#ifdef INCLUDE_KDRV_VDEC
	vdec0_hma.size = UHD_VDEC0_HMA_SZ;
	vdec1_hma.size = UHD_VDEC1_HMA_SZ;
#endif
}

static void BASE_PLT_Setup_1_5_GB_STD(void)
{
	printk("configure M16P3(%2X) kdriver memory (1.5GB DDR/STD)\n", lx_chip_rev()&0xff);

	gMemCfgHdr[DDR_RGN_M0_DEV].base 	= LM_2_0GB_DEV_RGN_A0_BASE;
	gMemCfgHdr[DDR_RGN_M0_DEV].size 	= LM_DEV_RGN_END - gMemCfgHdr[DDR_RGN_M0_DEV].base;
	gMemCfgHdr[DDR_RGN_M1_DEV].base 	= GM_2_0GB_DEV_RGN_A0_BASE;
	gMemCfgHdr[DDR_RGN_M1_DEV].size 	= GM_DEV_RGN_END - gMemCfgHdr[DDR_RGN_M1_DEV].base;

	BASE_PLT_SetupCommon();
	g_mem_desc_table = g_mem_desc_table_DDR_2_0_GB_ADV;	// 2GB map table is shared by both 2GB and 3GB board
}

static void BASE_PLT_Setup_2_0_GB_ADV(void)
{
	printk("configure M16P3(%2X) kdriver memory (2.0GB DDR/ADV)\n", lx_chip_rev()&0xff);

	gMemCfgHdr[DDR_RGN_M0_DEV].base 	= LM_2_0GB_DEV_RGN_A0_BASE;
	gMemCfgHdr[DDR_RGN_M0_DEV].size 	= LM_DEV_RGN_END - gMemCfgHdr[DDR_RGN_M0_DEV].base;
	gMemCfgHdr[DDR_RGN_M1_DEV].base 	= GM_2_0GB_DEV_RGN_A0_BASE;
	gMemCfgHdr[DDR_RGN_M1_DEV].size 	= GM_DEV_RGN_END - gMemCfgHdr[DDR_RGN_M1_DEV].base;

	BASE_PLT_SetupCommon();
	g_mem_desc_table = g_mem_desc_table_DDR_2_0_GB_ADV;	// 2GB map table is shared by both 2GB and 3GB board
}

static void BASE_PLT_Setup_3_0_GB_ADV(void)
{
	printk("configure M16P3(%2X) kdriver memory (3.0GB DDR/ADV)\n", lx_chip_rev()&0xff);

	gMemCfgHdr[DDR_RGN_M0_DEV].base 	= LM_3_0GB_DEV_RGN_A0_BASE;
	gMemCfgHdr[DDR_RGN_M0_DEV].size 	= LM_DEV_RGN_END - gMemCfgHdr[DDR_RGN_M0_DEV].base;
	gMemCfgHdr[DDR_RGN_M1_DEV].base 	= GM_3_0GB_DEV_RGN_A0_BASE;
	gMemCfgHdr[DDR_RGN_M1_DEV].size 	= GM_DEV_RGN_END - gMemCfgHdr[DDR_RGN_M1_DEV].base;

	BASE_PLT_SetupCommon();
	g_mem_desc_table = g_mem_desc_table_DDR_2_0_GB_ADV;	// 2GB map table is shared by both 2GB and 3GB board
}


/* run the post memory layout after memory allocation
 *
 */
static void BASE_PLT_DoPostMemoryLayout(void)
{
	int i;
	int	a;
	int ret;

	struct
	{
		const char *name;
		int size;
		const char* pool_name;
		int pool_type;
	}
	vdec0_section[] =
	{
		{ "dpb", 		0, "ddr0",	HMA_POOL},
		{ "hfr_core", 	0, "ddr0",	CMA_POOL},
		{ "cpb", 		0, "ddr1",	HMA_POOL},
		{ "vdec", 		0, "ddr1",	HMA_POOL},
	};

	// if memory region is set to NO_CMA, get device region from kernel to device driver with help of HMA
	printk("++ CMA registeration ++\n");
	for (i=0; i<MEM_DESC_ID_MAX; i++)
	{
		switch(mem_desc[i].flag)
		{
			case MEMCFG_DESC_FLAG_NO_CMA:
			{
				if( mem_desc[i].m.base != 0x0 && mem_desc[i].m.size != 0x0)
				{
					ret = hma_pool_register_type (mem_desc[i].m.name, mem_desc[i].m.base, mem_desc[i].m.size, CMA_POOL);

					if(ret==0)
					{
						printk("(x) CMA(%-12s %3dM@0x%08x) disabled\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
						hma_alloc(mem_desc[i].m.name, mem_desc[i].m.size, 1<<12);
					}
					else
					{
						printk("(?) CMA(%-12s %3dM@0x%08x) register error\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
					}
				}
				else
				{
					printk("(x) CMA(%-12s %3dM@0x%08x) can't be disabled\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
				}
			}
			break;

			case MEMCFG_DESC_FLAG_CMA:
			{
				// do nothing. each device will create its own CMA allocator
				printk("(o) CMA(%-12s %3dM@0x%08x) enabled\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
			}
			break;

			default:
			{
				// do nothing. this is BSP dedicated area
				printk("(/) CMA(%-12s %3dM@0x%08x) skip\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
			}
			break;
		}
	}

	// setup VDEC internal memory layout (register vdec0_hma hma pool and alloc vdec components memory)
	//
	vdec0_section[0].size = UHD_VDEC0_DPB_SZ;
	vdec0_section[1].size = UHD_VDEC0_HFR_SZ;
	vdec0_section[2].size = UHD_VDEC1_CPB_SZ;
	vdec0_section[3].size = UHD_VDEC1_MCU_SZ;

	// raxis.lim (2018/08/13)
	// split ddr0 region to two seperate region (ddr0 for DPB and ddr1 for CPB & MCU)
	// this policy is due to remove DPB region from CMA area at lxboot
	ret = hma_pool_register ("ddr0", vdec0_hma.base, vdec0_hma.size);
	if (ret < 0)
	{
		printk (KERN_ERR "hma_pool_register(ddr0) failed\n");
		return;
	}

	ret = hma_pool_register ("ddr1", vdec1_hma.base, vdec1_hma.size);
	if (ret < 0)
	{
		printk (KERN_ERR "hma_pool_register(ddr1) failed\n");
		return;
	}

	for (a=0; a<ARRAY_SIZE(vdec0_section); a++)
	{
		phys_addr_t base;
		const char *name;
		const char *pool_name;
		int size;
		int pool_type;

		name = vdec0_section[a].name;
		size = vdec0_section[a].size;
		pool_name = vdec0_section[a].pool_name;
		pool_type = vdec0_section[a].pool_type;

		if(size>0)
		{
			base = hma_alloc_user (pool_name, size, 1<<12, name);

			printk("(%c) vdec0(%-10s %3dM@0x%08x) allocated\n", (pool_type==CMA_POOL)?'o':'x', name, size>>20, (UINT32)base);

			if (base == 0)
			{
				printk (KERN_ERR "no memory for \"%s\", %d\n", name, size);
				break;
			}

			ret = hma_pool_register_type (name, base, size, pool_type);

			if (ret < 0)
			{
				printk (KERN_ERR "cannot register \"%s\" pool\n", name);
				break;
			}
		}
	}

	// remove fallback relation because VDEC has the enough DPB memory
	// hma_pool_fallback ("dpb", "surface");

#ifdef INCLUDE_KDRV_AUDIO
	ret = hma_pool_register_type ("audio_buffer",
			gMemCfgAud[1].hma_memory_base, gMemCfgAud[1].hma_memory_size, HMA_POOL);
	if (ret < 0)
		printk (KERN_ERR "hma_pool_register_type(\"audio_buffer\") failed. %d\n", ret);
#endif

	// TODO: add code to debug memory if necessary
}

/** main function for kdriver platform initialization
 *
 *  this function is called from base_drv.c after core initialization, chip rev detection
 * 	(including chip probe), debug initialization and pre-initialization of each driver.
 *
 */
void	BASE_PLT_Init (void)
{
	int ret;

	switch(g_model_ctx.ddr_size)
	{
		case MODEL_OPT_DDR_1_5_GB_STD:	BASE_PLT_Setup_1_5_GB_STD(); break;
		case MODEL_OPT_DDR_3_0_GB_ADV:	BASE_PLT_Setup_3_0_GB_ADV(); break;
		case MODEL_OPT_DDR_2_0_GB_ADV:
		default:						BASE_PLT_Setup_2_0_GB_ADV(); break;
	}

	ret = BASE_DEVMEM_InitDevMem(g_mem_desc_table);
	if (ret != RET_OK) DBG_PRINT_ERROR("fatal error during making kdriver memory layout\n");

	BASE_PLT_DoPostMemoryLayout();
}

/** main function for kdriver platform probing process
 *
 *  this function is called from base_drv.c after core initialization and chip rev detection.
 *
 */
void  BASE_PLT_Probe (UINT32* plt, UINT32* board_opt)
{
	int		i;

	UINT32	hdmi_tx_output = 0;
	UINT32	plt_val = 0x0;
	UINT32	board_opt_val = 0x0;

	char	optstr[80];
	const char* pioneer_board_fmtstr[2] = {"pioneer.board=%s", "pioneer.boardopts=%s"};

	// check HDMI Tx environment
	if (RET_OK == OS_ScanKernelCmdline("disp=%s", optstr))
	{
		if(!strncmp(optstr, "hdmi",4))
		{
			hdmi_tx_output = 1;
		}
	}

	// check webOS modelopt & hwopt
	if(webos_hwopt_probe)
	{
		char modelopt_txt[32];
		char hwopt_txt[32];

		memset(modelopt_txt, 0x0, 32);
		memset(hwopt_txt, 0x0, 32);

		if (RET_OK == OS_ScanKernelCmdline("modelopt=%s",modelopt_txt))
		{
			// detect panel_type (NON/LCD/OLED)
			if ((modelopt_txt[6] == '1') && (modelopt_txt[7] == '1') && (modelopt_txt[8] == '0') && (modelopt_txt[9] == '1'))
			{
				g_model_ctx.panel = MODEL_OPT_PANEL_NONE;
			}
			else if ((modelopt_txt[6] == '1') && (modelopt_txt[7] == '0') && (modelopt_txt[8] == '0'))
			{
				g_model_ctx.panel = MODEL_OPT_PANEL_OLED;
			}
			else
			{
				g_model_ctx.panel = MODEL_OPT_PANEL_LCD;
			}
		}

		if (RET_OK == OS_ScanKernelCmdline("hwopt=%s",hwopt_txt))
		{
			// webOS3.5 spec = 0: HD(1366x768)  1: FHD(1920x1080)  2: UHD(3840x2160)
			switch(hwopt_txt[3])
			{
				case '0':
				case '1': g_model_ctx.disp_model  = MODEL_OPT_FHD; break;
				case '2':
				default:  g_model_ctx.disp_model  = MODEL_OPT_UHD; break;
			}

			switch(hwopt_txt[4])
			{
				case '0': g_model_ctx.frc_hz    = MODEL_OPT_60HZ; break;
				case '1':
				default:  g_model_ctx.frc_hz    = MODEL_OPT_120HZ; break;
			}

			// webOS3.5 spec = 0:768M, 1:1.0GB, 2:1.25GB, 3:1.5GB, 4:2.0GB, 5:2.5GB, 6:3.0GB, 7:2.0GB_ADV, 8:2.0GB_STD
			switch(hwopt_txt[11])
			{
				case '3': g_model_ctx.ddr_size	= MODEL_OPT_DDR_1_5_GB_STD; break;
				case '6': g_model_ctx.ddr_size	= MODEL_OPT_DDR_3_0_GB_ADV; break;
				case '4':
				case '7':
				default: g_model_ctx.ddr_size	= MODEL_OPT_DDR_2_0_GB_ADV; break;	/* '4' OR '7' */
			}

#if 0 // webOS test is necessary
			switch(hwopt_txt[17])
			{
				case '0': g_model_ctx.frc_conn = MODEL_OPT_NO_FRC; break;
				case '2':
				case '3':
				case '4':
				case '5':
				case '6': g_model_ctx.frc_conn = MODEL_OPT_EXT_FRC; break;
				case '1':
				default:  g_model_ctx.frc_conn = MODEL_OPT_INT_FRC; break;
			}
#endif
		}

		if( RET_OK == OS_ScanKernelCmdlineToken("factory") )
		{
			g_model_ctx.low_power = MODEL_OPT_LOW_POWER;
		}
	}

	// check additional configuration for the test only
	for (i=0; i<NELEMENTS(pioneer_board_fmtstr); i++)
	{
		if (RET_OK == OS_ScanKernelCmdline(pioneer_board_fmtstr[i], optstr))
		{
			char *tok, *sav_tok;
			char delim[] = ",\t\n";

			tok = simple_strtok(optstr, delim, &sav_tok);

			while(tok)
			{
				if(!strncasecmp(tok, "1.5GB_STD",9))	g_model_ctx.ddr_size    = MODEL_OPT_DDR_1_5_GB_STD;
				if(!strncasecmp(tok, "2.0GB_ADV",9)) 	g_model_ctx.ddr_size    = MODEL_OPT_DDR_2_0_GB_ADV;
				if(!strncasecmp(tok, "3.0GB_ADV",9))	g_model_ctx.ddr_size    = MODEL_OPT_DDR_3_0_GB_ADV;
				if(!strncasecmp(tok, "1.5GB",5))		g_model_ctx.ddr_size    = MODEL_OPT_DDR_1_5_GB_STD;
				if(!strncasecmp(tok, "2.0GB",5))	 	g_model_ctx.ddr_size    = MODEL_OPT_DDR_2_0_GB_ADV;
				if(!strncasecmp(tok, "3.0GB",5))		g_model_ctx.ddr_size    = MODEL_OPT_DDR_3_0_GB_ADV;

				if(!strncasecmp(tok, "UHD",3))			g_model_ctx.disp_model	= MODEL_OPT_UHD;
				if(!strncasecmp(tok, "FHD",3))			g_model_ctx.disp_model	= MODEL_OPT_FHD;

				if(!strncasecmp(tok, "STB",3))			g_model_ctx.disp_model	= MODEL_OPT_PANEL_NONE;
				if(!strncasecmp(tok, "LCD",3))			g_model_ctx.disp_model	= MODEL_OPT_PANEL_LCD;
				if(!strncasecmp(tok, "OLED",4))			g_model_ctx.disp_model	= MODEL_OPT_PANEL_OLED;

				if(!strncasecmp(tok, "USR0",4))			g_model_ctx.usr0	 	= MODEL_OPT_USR;
				if(!strncasecmp(tok, "USR1",4))			g_model_ctx.usr1 		= MODEL_OPT_USR;
				if(!strncasecmp(tok, "USR2",4))			g_model_ctx.usr2 		= MODEL_OPT_USR;
				if(!strncasecmp(tok, "USR3",4))			g_model_ctx.usr3 		= MODEL_OPT_USR;

				if(!strncasecmp(tok, "60HZ",4))         g_model_ctx.frc_hz      = MODEL_OPT_60HZ;
				if(!strncasecmp(tok, "120HZ",5))        g_model_ctx.frc_hz      = MODEL_OPT_120HZ;

				tok = simple_strtok(NULL, delim, &sav_tok);
			}
		}
	}

	// dump board option
	printk("\n++ BOARD OPTION ++\n");
	printk("MODEL: %s\n",		(g_model_ctx.disp_model== MODEL_OPT_FHD)? "FHD":
						 		(g_model_ctx.disp_model== MODEL_OPT_UHD)? "UHD":"n/a");
	printk("SOC  : %s\n", 		"M19(LG1314)");
    printk("DDR  : %s\n",	 	(g_model_ctx.ddr_size == MODEL_OPT_DDR_1_5_GB_STD)? "1.5GB(STD)":
								(g_model_ctx.ddr_size == MODEL_OPT_DDR_2_0_GB_ADV)? "2.0GB(ADV)":
								(g_model_ctx.ddr_size == MODEL_OPT_DDR_3_0_GB_ADV)? "3.0GB(ADV)": "n/a");
	printk("PANEL: %s\n",		(g_model_ctx.panel == MODEL_OPT_PANEL_NONE)? "NONE(STB)":
 								(g_model_ctx.panel == MODEL_OPT_PANEL_LCD)?  "LCD/LED":
								(g_model_ctx.panel == MODEL_OPT_PANEL_OLED)? "OLED":"n/a");
	printk("FRC  : %s(%sHz)\n",	(g_model_ctx.frc_conn  == MODEL_OPT_NO_FRC)? "NONE":
								(g_model_ctx.frc_conn  == MODEL_OPT_INT_FRC)?"BUILT-IN":
								(g_model_ctx.frc_conn  == MODEL_OPT_EXT_FRC)?"EXTERNAL": "n/a",
                                (g_model_ctx.frc_hz == MODEL_OPT_60HZ)? "60":
                                (g_model_ctx.frc_hz == MODEL_OPT_120HZ)?"120": "n/a");

	printk("HDMI : %s\n",		(hdmi_tx_output)? "HDMI_TX" : "n/a");
	printk("LOWPW: %s\n",		(g_model_ctx.low_power==MODEL_OPT_LOW_POWER)? "ON":"n/a");

	printk("USR  : 0x%02x 0x%02x 0x%02x 0x%02x\n", g_model_ctx.usr0, g_model_ctx.usr1, g_model_ctx.usr2, g_model_ctx.usr3);

	// make board_opt variable
	if(g_model_ctx.usr0==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR0;
	if(g_model_ctx.usr1==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR1;
	if(g_model_ctx.usr2==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR2;
	if(g_model_ctx.usr3==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR3;

	plt_val	= (g_model_ctx.disp_model==MODEL_OPT_FHD)? LX_CHIP_PLT_FHD: LX_CHIP_PLT_UHD;

	switch(g_model_ctx.ddr_size)
	{
		case MODEL_OPT_DDR_3_0_GB_ADV: board_opt_val |= (LX_BOARD_OPT_DDR_3_0GB|LX_BOARD_OPT_ADV); break;
		case MODEL_OPT_DDR_2_0_GB_ADV: board_opt_val |= (LX_BOARD_OPT_DDR_2_0GB|LX_BOARD_OPT_ADV); break;
		case MODEL_OPT_DDR_1_5_GB_STD: board_opt_val |= (LX_BOARD_OPT_DDR_1_5GB|LX_BOARD_OPT_STD); break;
		default: /* none */ break;
	}

	switch(g_model_ctx.frc_conn)
	{
		case MODEL_OPT_NO_FRC:		board_opt_val |= LX_BOARD_OPT_NO_FRC;  break;
		case MODEL_OPT_INT_FRC:		board_opt_val |= LX_BOARD_OPT_INT_FRC; break;
		case MODEL_OPT_EXT_FRC:		board_opt_val |= LX_BOARD_OPT_EXT_FRC; break;
		default: /* none */ break;
	}


	switch(g_model_ctx.frc_hz)
	{
		case MODEL_OPT_60HZ:        board_opt_val |= LX_BOARD_OPT_DISP_60HZ; break;
		case MODEL_OPT_120HZ:       board_opt_val |= LX_BOARD_OPT_DISP_120HZ; break;
		default: /* none */ break;
	}

	switch(g_model_ctx.panel)
	{
		case MODEL_OPT_PANEL_NONE:	board_opt_val |= LX_BOARD_OPT_STBBOX; break;
		case MODEL_OPT_PANEL_LCD:	board_opt_val |= LX_BOARD_OPT_LCD; 	  break;
		case MODEL_OPT_PANEL_OLED:	board_opt_val |= LX_BOARD_OPT_OLED;	  break;
		default: /* none */ break;
	}

	if(g_model_ctx.low_power==MODEL_OPT_LOW_POWER)	board_opt_val |= LX_BOARD_OPT_LOW_POWER;

	if(g_model_ctx.usr0==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR0;
	if(g_model_ctx.usr1==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR1;
	if(g_model_ctx.usr2==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR2;
	if(g_model_ctx.usr3==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR3;

#ifdef INCLUDE_KDRV_VER_FPGA
	board_opt_val |= LX_BOARD_OPT_FPGA;
#else
	board_opt_val |= LX_BOARD_OPT_SYSTEM;
#endif

	*plt		= plt_val;
	*board_opt	= board_opt_val;
}

/** @} */

