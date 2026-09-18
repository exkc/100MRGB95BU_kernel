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

/** @file
 *
 *	main configuration for lg1k driver
 *
 *  author		raxis.lim@lge.com
 *  version		1.0
 *  date		2019.02.29
 *
 *  @addtogroup lg1k_base
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define PIONEER_PROBE_CFG	1		/* parse PIONEER toolopts */
#define	WEBOS_PROBE_CFG		0		/* parse webOS toolopts */

#define	USE_VDEC_PHOTOFB	0		/* use separate non-secure photofb region */
#define	USE_VDEC_CPB		0		/* use separate non-secure cpb region */

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
#ifdef INCLUDE_KDRV_HDMI20
#include "hdmi20_cfg.h"
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

#ifdef INCLUDE_KDRV_LM1
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

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	DDR_RGN0_DEV = 0,
	DDR_RGN1_DEV,
	DDR_RGN2_DEV,
	DDR_RGN3_DEV,
	DDR_RGN4_DEV,
	DDR_RGN_MAX,
}
DDR_RGN_T;

typedef struct
{
#define	MEMCFG_DESC_FLAG_NONE		0x00000000	/* device such as SE/TZ should keep memory content from the booting stage */
#define	MEMCFG_DESC_FLAG_CMA		0x4F434D41	/* device will manage dedicated memory according to its own policy. do nothing in platform_initializer */
#define	MEMCFG_DESC_FLAG_NO_CMA		0x4E434D41	/* device requires the pre-allocated device memory even from CMA region */
	UINT32		flag;
	LX_MEMCFG_T	m;
}
LX_MEMCFG_DESC_T;

typedef enum
{
	MODEL_OPT_UHD				= 0x0,
	MODEL_OPT_QUHD				= 0x1,

	MODEL_OPT_DDR_4GB_ADV		= 0x2,		/* 5.0GB 64Bit: M0=2GB, M1=2GB, M2=1GB */
	MODEL_OPT_DDR_5GB_ADV		= 0x3,		/* 6.0GB 64Bit: M0=2GB, M1=2GB, M2=2GB?? */

	MODEL_OPT_USR				= 0x1,		/* enable USR option */

	MODEL_OPT_NO_FRC			= 0x0,
	MODEL_OPT_INT_FRC			= 0x1,		/* default value */
	MODEL_OPT_EXT_FRC			= 0x2,

	MODEL_OPT_60HZ				= 0x1,
	MODEL_OPT_120HZ				= 0x2,		/* default value */

	MODEL_OPT_PANEL_NONE		= 0x0,		/* no panel = stbbox */
	MODEL_OPT_PANEL_LCD			= 0x1,
	MODEL_OPT_PANEL_OLED		= 0x2,

	MODEL_OPT_2K_GRAPHIC		= 0x1,		/* default value */
	MODEL_OPT_4K_GRAPHIC		= 0x2,		/* 4K graphics */
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
	MODEL_OPT_T graphic;

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
static int 	pioneer_hwopt_probe = PIONEER_PROBE_CFG;	// TODO: set to 1 if bringup is completed
static int 	webos_hwopt_probe 	= WEBOS_PROBE_CFG;		// TODO: set to 1 if bringup is completed
module_param_named(webos_hwopt_probe, webos_hwopt_probe, int, 0644 );
module_param_named(pioneer_hwopt_probe, pioneer_hwopt_probe, int, 0644 );

static MODEL_OPT_CTX_T	g_model_ctx = { .ddr_size	= MODEL_OPT_DDR_4GB_ADV,	/* 4GB     default */
										.disp_model = MODEL_OPT_QUHD,			/* QUHD    default */
										.frc_conn	= MODEL_OPT_INT_FRC,		/* INT_FRC default */
										.frc_hz		= MODEL_OPT_60HZ,			/* 120HZ   default */
										.panel		= MODEL_OPT_PANEL_OLED,		/* LCD/LED default */
										.graphic	= MODEL_OPT_2K_GRAPHIC,		/* 2K      default */
										.usr0		= 0,
										.usr1		= 0,
										.usr2		= 0,
										.usr3		= 0 };

static LX_MEMCFG_T gMemCfgHdr[DDR_RGN_MAX]={
											{.name = "[header]DEV0_BLK",.base = 0x0, .size = 0 },
											{.name = "[header]VDEC_BLK",.base = 0x0, .size = 0 },
											{.name = "[header]DEV1_BLK",.base = 0x0, .size = 0 },
											{.name = "[header]PQE_BLK",	.base = 0x0, .size = 0 },
											{.name = "[header]DEV3_BLK",.base = 0x0, .size = 0 }};

static LX_MEMCFG_T vdec_vpb0			= { .name = "vdec(vpb)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_vpb1			= { .name = "vdec(vpb8k)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_photo			= { .name = "vdec(photo)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_cpb0			= { .name = "vdec(cpb0)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_cpb1			= { .name = "vdec(cpb1)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_mcu				= { .name = "vdec(vdec)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T audio_buffer			= { .name = "audio",		.base = 0x0, .size = 0 };
static LX_MEMCFG_T lne_buffer			= { .name = "lne_buffer", };

static LX_MEMCFG_T gMemCfgFreeMem0		= {.name = "free(0)", 		.base = 0x0, .size = 0 };
static LX_MEMCFG_T gMemCfgFreeMem1		= {.name = "free(1)", 		.base = 0x0, .size = 0 };
static LX_MEMCFG_T gMemCfgFreeMem2		= {.name = "free(2)", 		.base = 0x0, .size = 0 };
static LX_MEMCFG_T gMemCfgFreeMem3		= {.name = "free(3)", 		.base = 0x0, .size = 0 };
static LX_MEMCFG_T gMemCfgFreeMem4		= {.name = "free(4)", 		.base = 0x0, .size = 0 };

/* region ID definition */
typedef enum
{
	MEM_DESC_ID_GFX0 = 0,
	MEM_DESC_ID_GFX1,
	MEM_DESC_ID_MJPEG,
	MEM_DESC_ID_VENC,
	MEM_DESC_ID_AUDIO,
	MEM_DESC_ID_AUDIO_SEP,
	MEM_DESC_ID_FBDEV,
	MEM_DESC_ID_TE,

	MEM_DESC_ID_VDEC_VPB0,		/* secure vdec DPB + vdec CPB */
	MEM_DESC_ID_VDEC_VPB1,		/* non-secure vdec DPB */
	MEM_DESC_ID_VDEC_PHOTO,		/* non-secure vdec DPB (not used) */
	MEM_DESC_ID_VDEC_CPB0,		/* non-secure vdec CPB (not used) */
	MEM_DESC_ID_VDEC_CPB1,		/* non-secure vdec CPB (not used) */
	MEM_DESC_ID_VDEC_VDEC,		/* vdec MCU */

	MEM_DESC_ID_SYS0,
	MEM_DESC_ID_SYS1,
	MEM_DESC_ID_SYS2,
	MEM_DESC_ID_SE,
	MEM_DESC_ID_TZ,

	MEM_DESC_ID_DEMOD,
	MEM_DESC_ID_DEMOD_FW,

	MEM_DESC_ID_DE,
	MEM_DESC_ID_DE_PREW,
	MEM_DESC_ID_DE_FW0,
	MEM_DESC_ID_DE_FW1,
	MEM_DESC_ID_DE_FW2,
	MEM_DESC_ID_DE_FW3,
	MEM_DESC_ID_DE_FW4,
	MEM_DESC_ID_DE_FW5,
	MEM_DESC_ID_DE_FW6,
	MEM_DESC_ID_DE_FRM1,		/* DE FRAME M1 */
	MEM_DESC_ID_DE_FRM2,		/* DE FRAME M2 */

	MEM_DESC_ID_TCON,
	MEM_DESC_ID_BT0,			/* BT M0 */
	MEM_DESC_ID_BT1,			/* BT M1 */
	MEM_DESC_ID_VT0,			/* VT M0 */
	MEM_DESC_ID_VT1,			/* VT M1 */

	MEM_DESC_ID_BE,
	MEM_DESC_ID_BE_FPP,			/* BE_FPP */
	MEM_DESC_ID_BE_FRC0,		/* BE_FRC0 */
	MEM_DESC_ID_BE_FRC1,		/* BE FRC1 */
	MEM_DESC_ID_BE_FRC2,		/* BE FRC2 */
	MEM_DESC_ID_BE_FRC3,		/* BE FRC3 */
	MEM_DESC_ID_BE_CINF,		/* BE_CHIP_INFO */

	MEM_DESC_ID_PE,

	MEM_DESC_ID_HDR,
	MEM_DESC_ID_VBI,
	MEM_DESC_ID_CVD,

	MEM_DESC_ID_HDMI_FEC,

	MEM_DESC_ID_LNE,

	MEM_DESC_ID_MTEST0,			/* MTEST DDR0(M0) */
	MEM_DESC_ID_MTEST1,			/* MTEST DDR1(M1) */
	MEM_DESC_ID_MTEST2,			/* MTEST DDR2(M2) */

	MEM_DESC_ID_FREE0,			/* free memory reporter */
	MEM_DESC_ID_FREE1,			/* free memory reporter */
	MEM_DESC_ID_FREE2,			/* free memory reporter */
	MEM_DESC_ID_FREE3,			/* free memory reporter */
	MEM_DESC_ID_FREE4,			/* free memory reporter */
	MEM_DESC_ID_FREE5,			/* free memory reporter */

	MEM_DESC_ID_DDR_CRASH,		/* reserved memory to prevent DDR crash */

	MEM_DESC_ID_MAX,
}
MEM_DESC_ID_T;

/* memory alias list for CMA processing */
#define MEM_DESC(n)				(mem_desc[MEM_DESC_ID_##n].m)
#define MEM_DESC_NAME(n)		(mem_desc[MEM_DESC_ID_##n].m.name)
#define MEM_DESC_BASE(n)		(mem_desc[MEM_DESC_ID_##n].m.base)
#define MEM_DESC_SIZE(n)		(mem_desc[MEM_DESC_ID_##n].m.size)
#define MEM_DESC_FLAG(n)		(mem_desc[MEM_DESC_ID_##n].flag)

#define DEFINE_MEM_DESC(n,f)	[MEM_DESC_ID_##n] = { .m={ .name = #n"_cma", .base = 0x0, .size = 0 }, .flag=f }

static LX_MEMCFG_DESC_T mem_desc[MEM_DESC_ID_MAX]	= {
	DEFINE_MEM_DESC(GFX0		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(GFX1		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(MJPEG		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VENC		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(AUDIO		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(FBDEV		,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(VDEC_VPB0	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VDEC_VPB1	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VDEC_PHOTO,	MEMCFG_DESC_FLAG_NO_CMA),		/* PHOTO has its own memory policy */
	DEFINE_MEM_DESC(VDEC_CPB0	,MEMCFG_DESC_FLAG_NO_CMA),		/* <TODO> CPB has its own memory policy */
	DEFINE_MEM_DESC(VDEC_CPB1	,MEMCFG_DESC_FLAG_NO_CMA),		/* <TODO> CPB has its own memory policy */
	DEFINE_MEM_DESC(VDEC_VDEC	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(TE			,MEMCFG_DESC_FLAG_CMA),			/* TE has its own memory manager */

	DEFINE_MEM_DESC(SYS0		,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(SYS1		,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(SE			,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(TZ			,MEMCFG_DESC_FLAG_NONE),

	DEFINE_MEM_DESC(DEMOD		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DEMOD_FW	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(DE			,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW0		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW1		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW2		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW3		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW4		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW5		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FW6		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FRM1		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_FRM2		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DE_PREW		,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(TCON		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BT0			,MEMCFG_DESC_FLAG_NO_CMA),		/* BT size is set to 0. do not use CMA (SICDTV-8432) */
	DEFINE_MEM_DESC(BT1			,MEMCFG_DESC_FLAG_NO_CMA),		/* BT size is set to 0. do not use CMA (SICDTV-8432) */
	DEFINE_MEM_DESC(VT0			,MEMCFG_DESC_FLAG_CMA),			/* VT0 has its own memory memory. (SICDTV-7015) */
	DEFINE_MEM_DESC(VT1			,MEMCFG_DESC_FLAG_CMA),			/* VT1 has its own memory memory. (SICDTV-7015) */

	DEFINE_MEM_DESC(HDMI_FEC	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(HDR			,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VBI			,MEMCFG_DESC_FLAG_NO_CMA),		/* VBI has its own memory manager. use HMA pool temporarility (SICDTV-7015) */
	DEFINE_MEM_DESC(CVD			,MEMCFG_DESC_FLAG_NO_CMA),			/* Do Not Use CMA */

	DEFINE_MEM_DESC(BE			,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FPP		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC0		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC1		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC2		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_FRC3		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(BE_CINF		,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(PE			,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(SYS1,		MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(LNE			,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(MTEST0 		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(MTEST1 		,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(FREE0		,MEMCFG_DESC_FLAG_NO_CMA), 	/* not used */
	DEFINE_MEM_DESC(FREE1		,MEMCFG_DESC_FLAG_CMA), 	/* enable CMA (SICDTV-8432) */
	DEFINE_MEM_DESC(FREE2		,MEMCFG_DESC_FLAG_CMA), 	/* enable CMA (SICDTV-8432) */
	DEFINE_MEM_DESC(FREE3		,MEMCFG_DESC_FLAG_CMA), 	/* enable CMA (SICDTV-8432) */
	DEFINE_MEM_DESC(FREE4		,MEMCFG_DESC_FLAG_NO_CMA), 	/* do not use CMA */
	DEFINE_MEM_DESC(FREE5		,MEMCFG_DESC_FLAG_NO_CMA), 	/* do not use CMA */

	DEFINE_MEM_DESC(DDR_CRASH	,MEMCFG_DESC_FLAG_NO_CMA), 	/* do not use CMA (SICDTV-8506) */
};

/*---------------------------------------------------------------------------------------
 * Global Memory Configuration data base
 *--------------------------------------------------------------------------------------*/
static LX_MEMCFG_ENTRY_T* g_mem_desc_table;

/* 2.5GB 80bit Memory Configuration
 *
 *
 */
static LX_MEMCFG_ENTRY_T g_mem_desc_table_DDR_5GB_ADV[] =
{
	//-----------------------------------------------------------------------------------
	//	DDR (RGN0)
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN0_DEV]),
#ifdef INCLUDE_KDRV_GFX
	LX_MEMCFG_ENTRY_EX(gMemCfgGfx.surface[0], MEM_DESC(GFX0)),/* GFXOSD. see O22 r4.8 map */
#endif
#ifdef INCLUDE_KDRV_FBDEV
	LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),      /* FBDEV. see O22 r4.8 map */
#endif

#ifdef INCLUDE_KDRV_SE
	LX_MEMCFG_ENTRY_EX(gMemCfgSE[0], MEM_DESC(SE)),			/* SE (fixed) */
	LX_MEMCFG_ENTRY_EX(gMemCfgSE_TZFW[0], MEM_DESC(TZ)),	/* TZFW (fixed) */
#endif

	LX_MEMCFG_ENTRY_EX(gMemCfgFreeMem0, MEM_DESC(FREE0)),

	//-----------------------------------------------------------------------------------
	//	DDR (RGN1)
	//----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN1_DEV]),

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec_vpb0, 	MEM_DESC(VDEC_VPB0)),	/* VDEC HMA */
	LX_MEMCFG_ENTRY_EX(vdec_vpb1, 	MEM_DESC(VDEC_VPB1)),	/* VDEC CMA */
	LX_MEMCFG_ENTRY_EX(vdec_photo, 	MEM_DESC(VDEC_PHOTO)),	/* VDEC CMA */
	LX_MEMCFG_ENTRY_EX(vdec_cpb0, 	MEM_DESC(VDEC_CPB0)),	/* VDEC CMA */
	LX_MEMCFG_ENTRY_EX(vdec_cpb1,   MEM_DESC(VDEC_CPB1)),   /* VDEC CMA */
	LX_MEMCFG_ENTRY_EX(vdec_mcu, 	MEM_DESC(VDEC_VDEC)),	/* VDEC HMA */
#endif

#ifdef INCLUDE_KDRV_MJPEG
	LX_MEMCFG_ENTRY_EX(gMemCfgMjpeg, MEM_DESC(MJPEG)),		/* MJPEG */
#endif

#ifdef INCLUDE_KDRV_VENC
	LX_MEMCFG_ENTRY_EX(gMemCfgVenc, MEM_DESC(VENC)),		/* VENC */
#endif

	LX_MEMCFG_ENTRY_EX(gMemCfgFreeMem1, MEM_DESC(FREE1)),

	//-----------------------------------------------------------------------------------
	//	DDR (RGN2)
	//----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN2_DEV]),

#ifdef INCLUDE_KDRV_AUDIO
	LX_MEMCFG_ENTRY_EX(audio_buffer,	MEM_DESC(AUDIO)),		/* AUDIO */
#endif

	LX_MEMCFG_ENTRY_EX(gMemCfgFreeMem2, MEM_DESC(FREE2)),

	//-----------------------------------------------------------------------------------
	//	DDR (RGN3)
	//----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN3_DEV]),
#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[7], MEM_DESC(DE_FW0)),	/* fw_mcu0 */
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[8], MEM_DESC(DE_FW1)),	/* fw_mcu1 */
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[0],	MEM_DESC(DE_PREW)),	/* de_prew */
#ifdef INCLUDE_KDRV_BE
	LX_MEMCFG_ENTRY_EX(gMemCfgBeFrc[0], MEM_DESC(BE_FPP)),	/* be_fpp  */
	LX_MEMCFG_ENTRY_EX(gMemCfgBeFrc[1], MEM_DESC(BE_FRC0)),	/* be_frc0  */
#endif
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[3],	MEM_DESC(BT0)),		/* de_bt_m0 */
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[14],MEM_DESC(HDR)),		/* de_hdr */
#ifdef INCLUDE_KDRV_BE
	LX_MEMCFG_ENTRY_EX(gMemCfgBe[0], 	MEM_DESC(BE)),		/* be_db  */
#endif
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[12], MEM_DESC(DE_FW5)),	/* fw_dnn */
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[9], MEM_DESC(DE_FW2)),	/* fw_mcu2 */
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[10], MEM_DESC(DE_FW3)),	/* fw_mcu3 */
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[11], MEM_DESC(DE_FW4)),	/* fw_shared */
#ifdef INCLUDE_KDRV_BE
	LX_MEMCFG_ENTRY_EX(gMemCfgBeChInf[0], MEM_DESC(BE_CINF)), /* be_chip_info */
#endif
#endif

#ifdef INCLUDE_KDRV_DE
#ifdef INCLUDE_KDRV_BE
	LX_MEMCFG_ENTRY_EX(gMemCfgBeFrc[3], MEM_DESC(BE_FRC2)),	/* be_frc2 */
#endif
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[6], MEM_DESC(VT1)),		/* de_vt_m2 */
#endif

#ifdef INCLUDE_KDRV_OVI
	LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[2], MEM_DESC(TCON)),	/* OVI TCON */
#endif

#ifdef INCLUDE_KDRV_PE
	LX_MEMCFG_ENTRY_EX(gMemCfgPe[0], MEM_DESC(PE)),         /* pe_db,pe_hdr */
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),/* VBI Buffer */
#endif

#ifdef INCLUDE_KDRV_AFE
    LX_MEMCFG_ENTRY_EX(gCvdMemCfg, MEM_DESC(CVD)),          /* CVD (3DComb H/W Memory) */
#endif

#ifdef INCLUDE_KDRV_HDMI20
		LX_MEMCFG_ENTRY_EX(gMemCfgHdmiFec[0], MEM_DESC(HDMI_FEC)),/* HDMI for FEC/DSC */
#endif

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[4], MEM_DESC(BT1)),	    /* de_bt_m1 */
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[1], MEM_DESC(DE_FRM1)),	/* de_frm_m1 */
#ifdef INCLUDE_KDRV_BE
	LX_MEMCFG_ENTRY_EX(gMemCfgBeFrc[12], MEM_DESC(BE_FRC1)), /* be_frc1 */
#endif
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[5], MEM_DESC(VT0)),		/* de_vt_m1 */
#endif

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(gMemCfgDeO22[2], MEM_DESC(DE_FRM2)),	/* de_frm_m2 */
#endif

	LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),			/* LNE */

	LX_MEMCFG_ENTRY_EX(gMemCfgFreeMem3, MEM_DESC(FREE3)),

	//-----------------------------------------------------------------------------------
	//	DDR (RGN4)
	//----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN4_DEV]),

#ifdef INCLUDE_KDRV_TE
	LX_MEMCFG_ENTRY_EX(gMemCfgTE,		MEM_DESC(TE)),		/* SDEC/TE */
#endif

#ifdef INCLUDE_KDRV_DEMOD
//	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD, 	MEM_DESC(DEMOD)),	/* DEMOD */
	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),/* DEMOD_FW */
#endif
	LX_MEMCFG_ENTRY_EX(gMemCfgFreeMem4, MEM_DESC(FREE4)),

	LX_MEMCFG_ENTRY_END
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static void BASE_PLT_SetupCommon(void)
{
	/* setup GFX */
#ifdef INCLUDE_KDRV_GFX
	gMemCfgGfx.surface[0].size	= GFXOSD_MEM_SZ;
#endif

	/* setup VDEC memory */
//#ifdef INCLUDE_KDRV_VDEC
	vdec_vpb0.size 	= VDEC_VPB0_SZ;
	vdec_vpb1.size 	= VDEC_VPB1_SZ;

#if	USE_VDEC_PHOTOFB
	vdec_photo.size = VDEC_PHOTO_SZ;
#else
	vdec_photo.size = 0;
#endif

#if USE_VDEC_CPB
	vdec_cpb0.size	= VDEC_CPB_SZ;
	vdec_cpb1.size	= VDEC_CPB_SZ;
#else
	vdec_cpb0.size	= 0;
	vdec_cpb1.size	= 0;
#endif
	vdec_mcu.size	= VDEC_MCU_SZ;
//#endif

	audio_buffer.size = AUDIO_BUFFER_SZ;

	lne_buffer.size = LNE_BUFFER_SZ;
}

static void BASE_PLT_Setup_3GB_ADV(void)
{
	printk("configure O22(%2X) kdriver memory (3.0GB DDR)\n", lx_chip_rev() & 0xff);

	gMemCfgHdr[DDR_RGN0_DEV].base = DDR_RGN0_BASE; gMemCfgHdr[DDR_RGN0_DEV].size = DDR_RGN0_SZ;
	gMemCfgHdr[DDR_RGN1_DEV].base = DDR_RGN1_BASE; gMemCfgHdr[DDR_RGN1_DEV].size = DDR_RGN1_SZ;
	gMemCfgHdr[DDR_RGN2_DEV].base = DDR_RGN2_BASE; gMemCfgHdr[DDR_RGN2_DEV].size = DDR_RGN2_SZ;
	gMemCfgHdr[DDR_RGN3_DEV].base = DDR_RGN3_BASE; gMemCfgHdr[DDR_RGN3_DEV].size = DDR_RGN3_SZ;
	gMemCfgHdr[DDR_RGN4_DEV].base = DDR_RGN4_BASE; gMemCfgHdr[DDR_RGN4_DEV].size = DDR_RGN4_SZ;

	BASE_PLT_SetupCommon();

	g_mem_desc_table = g_mem_desc_table_DDR_5GB_ADV;	/* 2GB map table is shared by both 2GB and 3GB board */
}

/* run the post memory layout after memory allocation
 *
 */
static void BASE_PLT_DoPostMemoryLayout(void)
{
	int i;
	int ret;

	/* re-calculate stuff0 & memory guard for free memory */
	gMemCfgFreeMem0.size = DDR_RGN0_END - gMemCfgFreeMem0.base;
	gMemCfgFreeMem1.size = DDR_RGN1_END - gMemCfgFreeMem1.base;
	gMemCfgFreeMem2.size = DDR_RGN2_END - gMemCfgFreeMem2.base;
	gMemCfgFreeMem3.size = DDR_RGN3_END - gMemCfgFreeMem3.base;
	gMemCfgFreeMem4.size = DDR_RGN4_END - gMemCfgFreeMem4.base;

	MEM_DESC_SIZE(FREE0) = gMemCfgFreeMem0.size;
	MEM_DESC_SIZE(FREE1) = gMemCfgFreeMem1.size;
	MEM_DESC_SIZE(FREE2) = gMemCfgFreeMem2.size;
	MEM_DESC_SIZE(FREE3) = gMemCfgFreeMem3.size;
	MEM_DESC_SIZE(FREE4) = gMemCfgFreeMem4.size;

	/* if memory region is set to NO_CMA, get device region from kernel to device driver with help of HMA */
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
				/* do nothing. each device will create its own CMA allocator */
				printk("(o) CMA(%-12s %3dM@0x%08x) enabled\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
			}
			break;

			default:
			{
				/* do nothing. this is BSP dedicated area */
				printk("(/) CMA(%-12s %3dM@0x%08x) skip\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
			}
			break;
		}
	}

	/* http://clm.lge.com/issue/browse/SICDTV-8002
	 * change memory pool creation order from dpb,vdec to vdec,dpb
	 */
	{
		struct
		{
			const char *name;
			int	mem_desc_id;
			int pool_type;
		}
		vdec_mem_desc[] =
		{
			{ "vpb",   MEM_DESC_ID_VDEC_VPB0,	HMA_POOL},		/* secure framebuffer */
			{ "vpb8k", MEM_DESC_ID_VDEC_VPB1,	HMA_POOL},		/* used for 2nd vpb when vdec bwb is unavailabl */
#if USE_VDEC_PHOTOFB
			{ "photofb",MEM_DESC_ID_VDEC_PHOTO,	HMA_POOL},		/* non-secure framebuffer */
#endif
#if USE_VDEC_CPB
			{ "cpb",   MEM_DESC_ID_VDEC_CPB0,	HMA_POOL},
			{ "cpb2",  MEM_DESC_ID_VDEC_CPB1,	HMA_POOL},
#endif
			{ "vdec",  MEM_DESC_ID_VDEC_VDEC,	HMA_POOL},
		};

		int a;

		for (a=0; a<ARRAY_SIZE(vdec_mem_desc); a++)
		{
			UINT32 base;
			const char *name;
			int size;
			int pool_type;

			#define MEM_DESC_BASE(n)		(mem_desc[MEM_DESC_ID_##n].m.base)

			name = vdec_mem_desc[a].name;
			base = mem_desc[ vdec_mem_desc[a].mem_desc_id ].m.base;
			size = mem_desc[ vdec_mem_desc[a].mem_desc_id ].m.size;
			pool_type = vdec_mem_desc[a].pool_type;

			if(size>0)
			{
				if (base == 0)
				{
					printk (KERN_ERR "no memory for \"%s\", %d\n", name, size);
					break;
				}

				ret = hma_pool_register_type(name, base, size, pool_type);

				if (ret==0)
				{
					printk("vdec(%5s) created at %dM@0x%08x with %s pool\n", name, size>>20, base, (pool_type==CMA_POOL)?"cma":"hma");
				}
				else
				{
					printk (KERN_ERR "cannot register \"%s\" pool\n", name);
					break;
				}
			}
		}
    }

#if USE_VDEC_CPB
	hma_pool_fallback("cpb", "cpb2");	/* reidrect cpb to cpb2 if out of memory */
#else
	hma_pool_alias("cpb", "vpb8k");		/* allow cpb to alloc from vpb8k. supported for legacy interface */
#endif

#if !USE_VDEC_PHOTOFB
	hma_pool_alias("photofb", "vpb8k");	/* allow photofb to alloc from vpb8k. supported for photofb interface */
#endif

	hma_pool_alias("dpb", "vpb");		/* allow dpb to alloc from vpb. supported for legacy interface */
	hma_pool_fallback("vpb", "vpb8k");	/* redirect vpb to vpb8k if out of memory */

#ifdef INCLUDE_KDRV_AUDIO
	ret = hma_pool_register_type ("audio_buffer",
			audio_buffer.base, audio_buffer.size, HMA_POOL);
	if (ret < 0)
		printk (KERN_ERR "hma_pool_register_type(\"audio_buffer\") failed. %d\n", ret);
#endif

	/* http://clm.lge.com/issue/browse/SICDTV-8565 */
	/* pqe-lne pool is used only for pool info */
	ret = hma_pool_register_type ("pqe-lne", lne_buffer.base, lne_buffer.size, HMA_POOL);
	if (ret < 0)
		printk (KERN_ERR "hma_pool_register_type(\"pqe-lne\") failed. %d\n", ret);

	/* lne_buffer.base ~ 4KB are reserved */
	ret = hma_pool_register_type (lne_buffer.name, lne_buffer.base + (4 * 1024),
			lne_buffer.size - (4 * 1024), HMA_POOL);
	if (ret < 0)
		printk (KERN_ERR "hma_pool_register_type(\"%s\") failed. %d\n", lne_buffer.name, ret);

	/* do nothing. DEMOD will alloc memory from "te_shared" region */

	/* TODO: add code to debug memory if necessary */

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
		case MODEL_OPT_DDR_4GB_ADV:
		case MODEL_OPT_DDR_5GB_ADV:
		default:						BASE_PLT_Setup_3GB_ADV(); break;
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

	/* check HDMI Tx environment */
	if (RET_OK == OS_ScanKernelCmdline("disp=%s", optstr))
	{
		if(!strncmp(optstr, "hdmi",4))
		{
			hdmi_tx_output = 1;
		}
	}

	/* check webOS modelopt & hwopt */
	if(webos_hwopt_probe)
	{
		char modelopt_txt[32];
		char hwopt_txt[32];

		memset(modelopt_txt, 0x0, 32);
		memset(hwopt_txt, 0x0, 32);

		#if 0
		if (RET_OK == OS_ScanKernelCmdline("modelopt=%s",modelopt_txt))
		{
			/* detect panel_type (NON/LCD/OLED) */
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
		#endif

		if (RET_OK == OS_ScanKernelCmdline("hwopt=%s",hwopt_txt))
		{
			#if 0
			/* webOS3.5 spec = 0: HD(1366x768)  1: FHD(1920x1080)  2: UHD(3840x2160) ... */
			switch(hwopt_txt[3])
			{
				case '0': /* ignore HD */
				case '1': /* ignore FHD */
				case '2': /* UHD */
				default:  g_model_ctx.disp_model  = MODEL_OPT_UHD; break;
			}
			#endif

			/* 0: NO_FRC, 1: INT_FRC, others: EXT_FRCs.
	 		 * I will treat NO_FRC as INT_FRC for easy maintenance because there is never "NO_FRC" configuration.
			 * raxis.lim (2019/01/16)
			 * there is nothing special to identify whether 4K or 8K TV. just use if there is EXT_FRC or not
			 */
			switch(hwopt_txt[17])
			{
				case '0':
				case '1': g_model_ctx.frc_conn = MODEL_OPT_INT_FRC; break;
				default:  g_model_ctx.frc_conn = MODEL_OPT_EXT_FRC; break;
			}

			switch(hwopt_txt[14])
			{
				case '4': g_model_ctx.graphic = MODEL_OPT_4K_GRAPHIC; break;
				default:  g_model_ctx.graphic = MODEL_OPT_2K_GRAPHIC; break;
			}

			switch(hwopt_txt[4])
			{
				case '0': g_model_ctx.frc_hz = MODEL_OPT_60HZ; break;
				default:  g_model_ctx.frc_hz = MODEL_OPT_120HZ; break;
			}

			#if 0	/* O22 platform is fixed to 4GB DDR */
			/* webOS3.5 spec = 0:768M, 1:1.0GB, 2:1.25GB, 3:1.5GB, 4:2.0GB, 5:2.0GB, 6:3.0GB, 7:2.0GB_ADV, 8:2.0GB_STD */
			switch(hwopt_txt[11])
			{
				case '6': g_model_ctx.ddr_size = MODEL_OPT_DDR_5GB_ADV; break;
				default:  g_model_ctx.ddr_size = MODEL_OPT_DDR_6GB_ADV; break;	/* '4' OR '7' */
			}
			#endif
		}
	}

	if (pioneer_hwopt_probe)
	{
		/* check additional configuration for the test only */
		for (i=0; i<NELEMENTS(pioneer_board_fmtstr); i++)
		{
			if (RET_OK == OS_ScanKernelCmdline(pioneer_board_fmtstr[i], optstr))
			{
				char *tok, *sav_tok;
				char delim[] = ",\t\n";

				tok = simple_strtok(optstr, delim, &sav_tok);

				while(tok)
				{
					if(!strncasecmp(tok, "4.0GB",5))        g_model_ctx.ddr_size    = MODEL_OPT_DDR_4GB_ADV;
					if(!strncasecmp(tok, "5.0GB",5))        g_model_ctx.ddr_size    = MODEL_OPT_DDR_4GB_ADV;

					if(!strncasecmp(tok, "UHD",3))			g_model_ctx.disp_model	= MODEL_OPT_UHD;
					if(!strncasecmp(tok, "QUHD",4))			g_model_ctx.disp_model	= MODEL_OPT_QUHD;

					if(!strncasecmp(tok, "STB",3))			g_model_ctx.panel		= MODEL_OPT_PANEL_NONE;
					if(!strncasecmp(tok, "LCD",3))			g_model_ctx.panel		= MODEL_OPT_PANEL_LCD;
					if(!strncasecmp(tok, "OLED",4))			g_model_ctx.panel		= MODEL_OPT_PANEL_OLED;

					if(!strncasecmp(tok, "60HZ",4)) 		g_model_ctx.frc_hz		= MODEL_OPT_60HZ;
					if(!strncasecmp(tok, "120HZ",5))		g_model_ctx.frc_hz		= MODEL_OPT_120HZ;

					if(!strncasecmp(tok, "2KOSD",5))		g_model_ctx.graphic		= MODEL_OPT_2K_GRAPHIC;
					if(!strncasecmp(tok, "4KOSD",5))		g_model_ctx.graphic		= MODEL_OPT_4K_GRAPHIC;

					if(!strncasecmp(tok, "USR0",4))			g_model_ctx.usr0	 	= MODEL_OPT_USR;
					if(!strncasecmp(tok, "USR1",4))			g_model_ctx.usr1 		= MODEL_OPT_USR;
					if(!strncasecmp(tok, "USR2",4))			g_model_ctx.usr2 		= MODEL_OPT_USR;
					if(!strncasecmp(tok, "USR3",4))			g_model_ctx.usr3 		= MODEL_OPT_USR;

					tok = simple_strtok(NULL, delim, &sav_tok);
				}
			}
		}
	}

	/* dump board option */
	printk("\n++ BOARD OPTION ++\n");
	printk("MODEL: %s\n",		(g_model_ctx.disp_model== MODEL_OPT_QUHD)? "QUHD":
								(g_model_ctx.disp_model== MODEL_OPT_UHD)?  "UHD":"n/a");
	printk("SOC  : %s\n",		"O22(LG1213)");
    printk("DDR  : %s\n",		(g_model_ctx.ddr_size == MODEL_OPT_DDR_5GB_ADV)? "5.0GB(ADV)":
								(g_model_ctx.ddr_size == MODEL_OPT_DDR_4GB_ADV)? "4.0GB(ADV)": "n/a");
    printk("GFX  : %s\n",		(g_model_ctx.graphic == MODEL_OPT_4K_GRAPHIC)? "4K(3840x2160)":
								(g_model_ctx.graphic == MODEL_OPT_2K_GRAPHIC)? "2K(1920x1080)": "n/a");
	printk("PANEL: %s\n",		(g_model_ctx.panel == MODEL_OPT_PANEL_NONE)? "NONE(STB)":
                           		(g_model_ctx.panel == MODEL_OPT_PANEL_LCD)?  "LCD/LED":
                            	(g_model_ctx.panel == MODEL_OPT_PANEL_OLED)? "OLED":"n/a");
    printk("FRC  : %s(%sHz)\n",	(g_model_ctx.frc_conn == MODEL_OPT_NO_FRC)?  "NONE":
                                (g_model_ctx.frc_conn == MODEL_OPT_EXT_FRC)? "EXTERNAL":"INTERNAL",
                                (g_model_ctx.frc_hz == MODEL_OPT_60HZ)? "60":
                                (g_model_ctx.frc_hz == MODEL_OPT_120HZ)?"120": "n/a");

	printk("HDMI : %s\n",		(hdmi_tx_output)? "HDMI Tx" : "None");

	printk("USR  : 0x%02x 0x%02x 0x%02x 0x%02x\n", g_model_ctx.usr0, g_model_ctx.usr1, g_model_ctx.usr2, g_model_ctx.usr3);

	/* make board_opt variable */
	if(g_model_ctx.usr0==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR0;
	if(g_model_ctx.usr1==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR1;
	if(g_model_ctx.usr2==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR2;
	if(g_model_ctx.usr3==MODEL_OPT_USR)	board_opt_val |= LX_BOARD_OPT_USR3;

	plt_val = (g_model_ctx.disp_model==MODEL_OPT_QUHD)? LX_CHIP_PLT_QUHD: LX_CHIP_PLT_UHD;

	switch(g_model_ctx.ddr_size)
	{
		case MODEL_OPT_DDR_4GB_ADV: board_opt_val |= (LX_BOARD_OPT_DDR_4_0GB|LX_BOARD_OPT_ADV); break;
		case MODEL_OPT_DDR_5GB_ADV: board_opt_val |= (LX_BOARD_OPT_DDR_4_0GB|LX_BOARD_OPT_ADV); break;
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
		case MODEL_OPT_120HZ:       board_opt_val |= LX_BOARD_OPT_DISP_120HZ;break;
		default: /* none */ break;
	}

	switch(g_model_ctx.panel)
	{
		case MODEL_OPT_PANEL_NONE:	board_opt_val |= LX_BOARD_OPT_STBBOX; break;
		case MODEL_OPT_PANEL_LCD:	board_opt_val |= LX_BOARD_OPT_LCD; 	  break;
		case MODEL_OPT_PANEL_OLED:	board_opt_val |= LX_BOARD_OPT_OLED;	  break;
		default: /* none */ break;
	}

	if(g_model_ctx.graphic==MODEL_OPT_4K_GRAPHIC) board_opt_val |= LX_BOARD_OPT_4K_GRAPHIC;

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

