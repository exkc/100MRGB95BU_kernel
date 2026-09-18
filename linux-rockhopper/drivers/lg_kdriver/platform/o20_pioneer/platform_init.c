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
#define PIONEER_PROBE_CFG			1		/* parse PIONEER toolopts */
#define	WEBOS_PROBE_CFG				1		/* parse webOS toolopts */

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


#ifdef INCLUDE_KDRV_AUDIO
#include "audio/audio_cfg.h"
#endif
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
#ifdef INCLUDE_KDRV_DEMOD
#include "demod_cfg.h"
#endif

#ifdef INCLUDE_KDRV_LM1
#include "lgbus_cfg.h"
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

#define __MEM_VALUE_SELECT(val_4k,val_8k)	(g_model_ctx.disp_model==MODEL_OPT_UHD)? (val_4k):(val_8k)

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
	MODEL_OPT_FHD				= 0x2,

	MODEL_OPT_DDR_3_0_GB_ADV	= 0x2,		/* 3.0GB 64Bit: M0=2GB, M1=1GB */
	MODEL_OPT_DDR_4_0_GB_ADV	= 0x3,		/* 4.0GB 64Bit: M0=?GB, M1=?GB */

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
static int 	pioneer_hwopt_probe = PIONEER_PROBE_CFG;// TODO: set to 1 if bringup is completed
static int 	webos_hwopt_probe 	= WEBOS_PROBE_CFG;	// TODO: set to 1 if bringup is completed
module_param_named(webos_hwopt_probe, webos_hwopt_probe, int, 0644 );
module_param_named(pioneer_hwopt_probe, pioneer_hwopt_probe, int, 0644 );

static MODEL_OPT_CTX_T	g_model_ctx = { .ddr_size	= MODEL_OPT_DDR_3_0_GB_ADV,	/* 3GB by default */
										.disp_model = MODEL_OPT_UHD,			/* UHD by default */
										.frc_conn	= MODEL_OPT_INT_FRC,		/* INT_FRC default */
										.frc_hz		= MODEL_OPT_120HZ,			/* 120HZ   default */
										.panel		= MODEL_OPT_PANEL_OLED,		/* LCD/LED default */
										.graphic	= MODEL_OPT_2K_GRAPHIC,		/* 2K      default */
										.usr0		= 0,
										.usr1		= 0,
										.usr2		= 0,
										.usr3		= 0 };


static LX_MEMCFG_T	gMemCfgHdr[DDR_RGN_MAX]={{.name = "[header]DDR0",	.base = 0x0, .size = 0 },	/* mem header */
											{ .name = "[header]DDR1",	.base = 0x0, .size = 0 }};	/* mem header */

static LX_MEMCFG_T static_rgn_sys0_start= { .name = "static(SYS0)",	.base = 0x0, .size = 0 };		/* mem separator */
static LX_MEMCFG_T static_rgn_sys1_start= { .name = "static(M1)",	.base = 0x0, .size = 0 };		/* mem separator */

static LX_MEMCFG_T static_rgn_m0_start	= { .name = "static(M0)",	.base = 0x0, .size = 0 };		/* mem seperator */

static LX_MEMCFG_T vdec_dpb0		= { .name = "vdec(dpb0)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_dpb1		= { .name = "vdec(dpb1)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_cpb0		= { .name = "vdec(cpb0)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_cpb1		= { .name = "vdec(cpb1)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_mcu			= { .name = "vdec(vdec)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T venc		= { .name = "venc",		.base = 0x0, .size = 0 };
static LX_MEMCFG_T audio_buffer		= { .name = "audio",		.base = 0x0, .size = 0 };
static LX_MEMCFG_T lne_buffer		= { .name = "lne_buffer", };

static LX_MEMCFG_T gMemCfgSYS0		= {.name = "sys(M0)",		.base = 0x0, .size = __MB(1) };
static LX_MEMCFG_T gMemCfgSYS1		= {.name = "sys(M1)", 		.base = 0x0, .size = DDR_CALIB_RGN_SZ };

#ifdef USE_MTEST_RGN
static LX_MEMCFG_T gMemCfgMemTest0		= {.name = "mt_ddr0", 		.base = 0x0, .size = __MB(1) };
static LX_MEMCFG_T gMemCfgMemTest1		= {.name = "mt_ddr1", 		.base = 0x0, .size = __MB(1) };
static LX_MEMCFG_T gMemCfgMemTestNsSram = {.name = "mt_nssram",		.base = 0xFFF00000, .size = __KB(16) };
#endif

static LX_MEMCFG_T gMemCfgFreeMem0		= {.name = "free(M0)", 		.base = 0x0, .size = 0 };
static LX_MEMCFG_T gMemCfgFreeMem1		= {.name = "free(M1)", 		.base = 0x0, .size = 0 };
static LX_MEMCFG_T gMemCfgMemStuff0		= {.name = "stuff0", 		.base = 0x0, .size = 0 };

/* region ID definition */
typedef enum
{
	MEM_DESC_ID_GFX0 = 0,
	MEM_DESC_ID_GFX1,
	MEM_DESC_ID_MJPEG,
	MEM_DESC_ID_VENC,
	MEM_DESC_ID_AUDIO,
	MEM_DESC_ID_FBDEV,
	MEM_DESC_ID_TE,

	MEM_DESC_ID_VDEC_DPB0,		/* secure vdec DPB + vdec CPB */
	MEM_DESC_ID_VDEC_DPB1,		/* non-secure vdec DPB (photo) */
	MEM_DESC_ID_VDEC_CPB0,		/* non-secure vdec CPB */
	MEM_DESC_ID_VDEC_CPB1,		/* non-secure vdec CPB */
	MEM_DESC_ID_VDEC_VDEC,		/* vdec MCU */

	MEM_DESC_ID_SYS0,
	MEM_DESC_ID_SYS1,
	MEM_DESC_ID_SE,
	MEM_DESC_ID_TZ,

	MEM_DESC_ID_DEMOD,
	MEM_DESC_ID_DEMOD_FW,

	MEM_DESC_ID_PQE0_SVP,		/* secure, pqe0 */
	MEM_DESC_ID_PQE0_NSV,		/* non-secure, pqe0 */
	MEM_DESC_ID_PQE0_USR,		/* non-secure, pqe0 */
	MEM_DESC_ID_PQE0_DBG,		/* non-secure, pqe0 */
	MEM_DESC_ID_PQE1_SVP,		/* secure, pqe1 */
	MEM_DESC_ID_PQE1_NSV,		/* non-secure, pqe1 */
	MEM_DESC_ID_PQE1_USR,		/* non-secure, pqe1 */
	MEM_DESC_ID_PQE1_DBG,		/* non-secure, pqe1 */

	MEM_DESC_ID_TCON,

	MEM_DESC_ID_VBI,
	MEM_DESC_ID_CVD,

	MEM_DESC_ID_HDMI_FEC,

	MEM_DESC_ID_LNE,

	MEM_DESC_ID_MTEST0,			/* MTEST DDR0(M0) */
	MEM_DESC_ID_MTEST1,			/* MTEST DDR1(M1) */
	MEM_DESC_ID_MTEST2,			/* MTEST DDR2(M2) */

	MEM_DESC_ID_STUFF0,			/* test stuff or memory guard */
	MEM_DESC_ID_FREE0,			/* free memory reporter */
	MEM_DESC_ID_FREE1,			/* free memory reporter */

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

	DEFINE_MEM_DESC(VDEC_DPB0	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(VDEC_DPB1	,MEMCFG_DESC_FLAG_CMA),		/* DPB1(photo) has its own memory policy */
	DEFINE_MEM_DESC(VDEC_CPB0	,MEMCFG_DESC_FLAG_CMA),		/* <TODO> CPB has its own memory policy */
	DEFINE_MEM_DESC(VDEC_CPB1	,MEMCFG_DESC_FLAG_CMA),		/* <TODO> CPB has its own memory policy */
	DEFINE_MEM_DESC(VDEC_VDEC	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(TE			,MEMCFG_DESC_FLAG_CMA),		/* TE has its own memory manager */

	DEFINE_MEM_DESC(SYS0		,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(SE			,MEMCFG_DESC_FLAG_NONE),
	DEFINE_MEM_DESC(TZ			,MEMCFG_DESC_FLAG_NONE),

	DEFINE_MEM_DESC(DEMOD		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(DEMOD_FW	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(PQE0_SVP	,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(PQE0_NSV	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(PQE0_USR	,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(PQE0_DBG	,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(PQE1_SVP	,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(PQE1_NSV	,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(PQE1_USR	,MEMCFG_DESC_FLAG_CMA),
	DEFINE_MEM_DESC(PQE1_DBG	,MEMCFG_DESC_FLAG_CMA),

	DEFINE_MEM_DESC(TCON		,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(VBI			,MEMCFG_DESC_FLAG_NO_CMA),		/* VBI has its own memory manager. use HMA pool temporarility (SICDTV-7015) */
	DEFINE_MEM_DESC(CVD			,MEMCFG_DESC_FLAG_NO_CMA),		/* Do Not Use CMA */

	DEFINE_MEM_DESC(HDMI_FEC	,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(SYS1,		MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(LNE		,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(MTEST0 		,MEMCFG_DESC_FLAG_NO_CMA),
	DEFINE_MEM_DESC(MTEST1 		,MEMCFG_DESC_FLAG_NO_CMA),

	DEFINE_MEM_DESC(STUFF0 		,MEMCFG_DESC_FLAG_CMA), 	/* add to CMA region */
	DEFINE_MEM_DESC(FREE0		,MEMCFG_DESC_FLAG_CMA), 	/* add to CMA region */
	DEFINE_MEM_DESC(FREE1		,MEMCFG_DESC_FLAG_CMA), 	/* add to CMA region */
};

/*---------------------------------------------------------------------------------------
 * Global Memory Configuration data base
 *--------------------------------------------------------------------------------------*/
static LX_MEMCFG_ENTRY_T* g_mem_desc_table;

/* 2.5GB 80bit Memory Configuration
 *
 *
 */
static LX_MEMCFG_ENTRY_T g_mem_desc_table_DDR_3_0_GB_ADV[] =
{
	//-----------------------------------------------------------------------------------
	//	DDR0 (M0)
	//
	//	메모리맵상에서 M0 에서 명시된 장치는 여기에 순서를 배치해 주세요.
	//	- VDEC 은 건드리지 마시고, VDEC 뒤에 배치해주세요.
	//	- 가장 뒤에는 SYS, SE, TZ 가 배치 됩니다.
	//----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec_dpb0, 	MEM_DESC(VDEC_DPB0)),	/* VDEC HMA */
	LX_MEMCFG_ENTRY_EX(vdec_dpb1, 	MEM_DESC(VDEC_DPB1)),	/* VDEC CMA */
	LX_MEMCFG_ENTRY_EX(vdec_cpb0, 	MEM_DESC(VDEC_CPB0)),	/* VDEC CMA */
	LX_MEMCFG_ENTRY_EX(vdec_cpb1,   MEM_DESC(VDEC_CPB1)),   /* VDEC CMA */
	LX_MEMCFG_ENTRY_EX(vdec_mcu, 	MEM_DESC(VDEC_VDEC)),	/* VDEC HMA */
#endif

#ifdef INCLUDE_KDRV_GFX
	LX_MEMCFG_ENTRY_EX(gMemCfgGfx.surface[0], MEM_DESC(GFX0)),/* GFXOSD */
#endif

#ifdef INCLUDE_KDRV_MJPEG
	LX_MEMCFG_ENTRY_EX(gMemCfgMjpeg, MEM_DESC(MJPEG)),		/* MJPEG */
#endif

#ifdef INCLUDE_KDRV_VENC
	LX_MEMCFG_ENTRY_EX(venc, MEM_DESC(VENC)),		/* VENC */
#endif

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_svp, MEM_DESC(PQE0_SVP)),
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_nsv, MEM_DESC(PQE0_NSV)),
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_usr, MEM_DESC(PQE0_USR)),
	LX_MEMCFG_ENTRY_EX(g_de_dbg_m1,  MEM_DESC(PQE0_DBG)),
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),/* VBI Buffer */
#endif

#ifdef INCLUDE_KDRV_AFE
    LX_MEMCFG_ENTRY_EX(gCvdMemCfg, MEM_DESC(CVD)),			/* CVD (3DComb H/W Memory) */
#endif

#ifdef INCLUDE_KDRV_HDMI20
    LX_MEMCFG_ENTRY_EX(gMemCfgHdmiFec[0], MEM_DESC(HDMI_FEC)),			/* HDMI for FEC/DSC */
#endif

#ifdef INCLUDE_KDRV_FBDEV
	LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),		/* FBDEV */
#endif

	LX_MEMCFG_ENTRY_EX(gMemCfgFreeMem0, MEM_DESC(FREE0)),

	LX_MEMCFG_ENTRY(static_rgn_m0_start),					/* semi-static driver memory */

#ifdef INCLUDE_KDRV_TE
	LX_MEMCFG_ENTRY_EX(gMemCfgTE,		MEM_DESC(TE)),		/* SDEC/TE */
#endif

#ifdef INCLUDE_KDRV_AUDIO
	LX_MEMCFG_ENTRY_EX(gMemCfgAud[1], MEM_DESC(AUDIO)),		/* AUDIO */
#endif

#ifdef INCLUDE_KDRV_DEMOD
//	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD, 	MEM_DESC(DEMOD)),	/* DEMOD */
	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),/* DEMOD_FW */
#endif

#ifdef USE_MTEST_RGN
	LX_MEMCFG_ENTRY_EX(gMemCfgMemTest0, MEM_DESC(MTEST0)),	/* MTEST */
#endif

	LX_MEMCFG_ENTRY_EX(gMemCfgMemStuff0,MEM_DESC(STUFF0)),	/* memory stuff */

	LX_MEMCFG_ENTRY(static_rgn_sys0_start),
	LX_MEMCFG_ENTRY_EX(gMemCfgSYS0, MEM_DESC(SYS0)),			/* SYSTEM */

#ifdef INCLUDE_KDRV_SE
	LX_MEMCFG_ENTRY_EX(gMemCfgSE[0], MEM_DESC(SE)),			/* SE */
	LX_MEMCFG_ENTRY_EX(gMemCfgSE_TZFW[0], MEM_DESC(TZ)),	/* TZFW */
#endif

	//-----------------------------------------------------------------------------------
	//	DDR1 (M1)
	//
	//	메모리맵상에서 M0 에서 명시된 장치는 여기에 순서를 배치해 주세요.
	//	- VDEC 은 건드리지 마시고, VDEC 뒤에 배치해주세요.
	//	- 가장 뒤에는 TE 가 배치됩니다.
	//----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M1_DEV]),

#ifdef INCLUDE_KDRV_OVI
	LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[2], MEM_DESC(TCON)),	/* OVI TCON */
#endif

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_svp, MEM_DESC(PQE1_SVP)),
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_nsv, MEM_DESC(PQE1_NSV)),
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_usr, MEM_DESC(PQE1_USR)),
	LX_MEMCFG_ENTRY_EX(g_de_dbg_m2,  MEM_DESC(PQE1_DBG)),
#endif

	LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),

#ifdef USE_MTEST_RGN
	LX_MEMCFG_ENTRY_EX(gMemCfgMemTest1, MEM_DESC(MTEST1)),	/* MTEST */
#endif

	LX_MEMCFG_ENTRY_EX(gMemCfgFreeMem1, MEM_DESC(FREE1)),

	LX_MEMCFG_ENTRY(static_rgn_sys1_start),
    LX_MEMCFG_ENTRY_EX(gMemCfgSYS1, MEM_DESC(SYS1)),		/* CALIB */

	LX_MEMCFG_ENTRY_END
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static void BASE_PLT_SetupCommon(void)
{
	/* setup static mem region - 16MB @ L_BUS */
	static_rgn_sys0_start.base = gMemCfgHdr[DDR_RGN_M0_DEV].base + gMemCfgHdr[DDR_RGN_M0_DEV].size - M0_SYSTEM_RGN_SZ;

	/* setup static mem region - M0, M1 */
	static_rgn_sys1_start.base = gMemCfgHdr[DDR_RGN_M1_DEV].base + gMemCfgHdr[DDR_RGN_M1_DEV].size - M1_SYSTEM_RGN_SZ;

	/* setup semi-static driver memory */
	static_rgn_m0_start.base = static_rgn_sys0_start.base - STATIC_BSP_MEM_SZ;

	/* setup GFX */
#ifdef INCLUDE_KDRV_GFX
	gMemCfgGfx.surface[0].size	= GFXOSD_MEM_SZ;
#endif

	/* setup VDEC memory */
#if 1 //def INCLUDE_KDRV_VDEC
	vdec_dpb0.size 	= UHD_VDEC_DPB_SZ;
	vdec_dpb1.size 	= UHD_VDEC_PHOTO_SZ;
	vdec_cpb0.size	= UHD_VDEC_CPB_SZ;
	vdec_cpb1.size	= UHD_VDEC_CPB_SZ;
	vdec_mcu.size	= UHD_VDEC_MCU_SZ;
	venc.size	= VENC_SZ;
#endif

	audio_buffer.size = AUDIO_BUFFER_SZ;

	lne_buffer.size = LNE_BUFFER_SZ;
}

static void BASE_PLT_Setup_3_0_GB_ADV(void)
{
	printk("configure O20(%2X) kdriver memory (3.0GB DDR)\n", lx_chip_rev() & 0xff);

	gMemCfgHdr[DDR_RGN_M0_DEV].base 	= __MEM_VALUE_SELECT(UHD_M0_3_0_GB_DEV_RGN_BASE, QUHD_M0_3_0_GB_DEV_RGN_BASE);
	gMemCfgHdr[DDR_RGN_M0_DEV].size 	= __MEM_VALUE_SELECT(UHD_M0_3_0_GB_DEV_RGN_SZ,   QUHD_M0_3_0_GB_DEV_RGN_SZ);
	gMemCfgHdr[DDR_RGN_M1_DEV].base 	= __MEM_VALUE_SELECT(UHD_M1_3_0_GB_DEV_RGN_BASE, QUHD_M1_3_0_GB_DEV_RGN_BASE);
	gMemCfgHdr[DDR_RGN_M1_DEV].size 	= __MEM_VALUE_SELECT(UHD_M1_3_0_GB_DEV_RGN_SZ,   QUHD_M1_3_0_GB_DEV_RGN_SZ);

	BASE_PLT_SetupCommon();

	g_mem_desc_table = g_mem_desc_table_DDR_3_0_GB_ADV;	/* 2GB map table is shared by both 2GB and 3GB board */
}

static void BASE_PLT_Setup_4_0_GB_ADV(void)
{
	printk("-error- 4GB config not supported\n");
	BASE_PLT_Setup_3_0_GB_ADV();
}

/* run the post memory layout after memory allocation
 *
 */
static void BASE_PLT_DoPostMemoryLayout(void)
{
	int i;
	int ret;

	/* setup stuff0 memory for memory guard */
	gMemCfgMemStuff0.size = static_rgn_sys0_start.base - gMemCfgMemStuff0.base;
	MEM_DESC_SIZE(STUFF0) = gMemCfgMemStuff0.size;

	/* setup free mem reporter */
	gMemCfgFreeMem0.size = static_rgn_m0_start.base - gMemCfgFreeMem0.base;
	MEM_DESC_SIZE(FREE0) = gMemCfgFreeMem0.size;

	gMemCfgFreeMem1.size = static_rgn_sys1_start.base - gMemCfgFreeMem1.base;
	MEM_DESC_SIZE(FREE1) = gMemCfgFreeMem1.size;

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

	/* http://clm.lge.com/issue/browse/SICDTV-4138
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
			{ "vpb",   MEM_DESC_ID_VDEC_DPB0,	HMA_POOL},
			{ "photofb",MEM_DESC_ID_VDEC_DPB1,	CMA_POOL},
			{ "cpb",   MEM_DESC_ID_VDEC_CPB0,	CMA_POOL},
			{ "cpb2",  MEM_DESC_ID_VDEC_CPB1,	CMA_POOL},
			{ "vdec",  MEM_DESC_ID_VDEC_VDEC,	HMA_POOL},
			{ "venc0",  MEM_DESC_ID_VENC,	HMA_POOL},
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

	hma_pool_fallback("cpb", "cpb2");
	hma_pool_fallback("venc0", "photofb");

	hma_pool_alias("dpb", "vpb");	// for legacy code

#ifdef INCLUDE_KDRV_AUDIO
	ret = hma_pool_register_type ("audio_buffer",
			gMemCfgAud[1].hma_memory_base, gMemCfgAud[1].hma_memory_size, HMA_POOL);
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

#ifdef USE_MTEST_RGN
	/* register hma region for memtest */
	ret = hma_pool_register_type ("mtest-ddr0", 	gMemCfgMemTest0.base, gMemCfgMemTest0.size, HMA_POOL);
	if (ret < 0) printk (KERN_ERR "cannot register \"%s\" pool\n", "mtest_ddr0");

	ret = hma_pool_register_type ("mtest-ddr1", 	gMemCfgMemTest1.base, gMemCfgMemTest1.size, HMA_POOL);
	if (ret < 0) printk (KERN_ERR "cannot register \"%s\" pool\n", "mtest_ddr1");

	ret = hma_pool_register_type ("mtest-nssram", 	gMemCfgMemTestNsSram.base, gMemCfgMemTestNsSram.size, HMA_POOL);
	if (ret < 0) printk (KERN_ERR "cannot register \"%s\" pool\n", "mtest_nssram");
#endif

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
		case MODEL_OPT_DDR_4_0_GB_ADV:	BASE_PLT_Setup_4_0_GB_ADV(); break;
		case MODEL_OPT_DDR_3_0_GB_ADV:
		default:						BASE_PLT_Setup_3_0_GB_ADV(); break;
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
			/* 0: HD(1366x768)  1: FHD(1920x1080)  2: UHD(3840x2160) 3: QUHD(7680x4320)... */
			switch(hwopt_txt[3])
			{
				case '0':
				case '1': g_model_ctx.disp_model = MODEL_OPT_FHD; break;
				case '3': g_model_ctx.disp_model = MODEL_OPT_QUHD;break;
				default:  g_model_ctx.disp_model = MODEL_OPT_UHD; break;
			}

			/* 0: NO_FRC, 1: INT_FRC, others: EXT_FRCs.
	 		 * I will treat NO_FRC as INT_FRC for easy maintenance because there is never "NO_FRC" configuration.
			 * raxis.lim (2019/01/16)
			 * there is nothing special to identify whether 4K or 8K TV. just use if there is EXT_FRC or not
			 */
			switch(hwopt_txt[17])
			{
				case '0':
				case '1': g_model_ctx.frc_conn = MODEL_OPT_INT_FRC; break;
				default:  g_model_ctx.frc_conn = MODEL_OPT_EXT_FRC; g_model_ctx.disp_model = MODEL_OPT_QUHD; break;
			}

			switch(hwopt_txt[14])
			{
				case '4': g_model_ctx.graphic = MODEL_OPT_4K_GRAPHIC; break;
				default:  g_model_ctx.graphic = MODEL_OPT_2K_GRAPHIC; break;
			}

			#if 0	/* O20 platform is fixed to 120Hz display */
			switch(hwopt_txt[4])
			{
				case '0': g_model_ctx.frc_hz    = MODEL_OPT_60HZ; break;
				case '1':
				default:  g_model_ctx.frc_hz    = MODEL_OPT_120HZ; break;
			}
			#endif

			#if 0	/* O20 platform is fixed to 3GB DDR */
			/* webOS3.5 spec = 0:768M, 1:1.0GB, 2:1.25GB, 3:1.5GB, 4:2.0GB, 5:2.0GB, 6:3.0GB, 7:2.0GB_ADV, 8:2.0GB_STD */
			switch(hwopt_txt[11])
			{
				case '6': g_model_ctx.ddr_size = MODEL_OPT_DDR_3_0_GB_ADV; break;
				default:  g_model_ctx.ddr_size = MODEL_OPT_DDR_4_0_GB_ADV; break;	/* '4' OR '7' */
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
					if(!strncasecmp(tok, "3.0GB_ADV",9)) 	g_model_ctx.ddr_size    = MODEL_OPT_DDR_3_0_GB_ADV;
					if(!strncasecmp(tok, "4.0GB_ADV",9))	g_model_ctx.ddr_size    = MODEL_OPT_DDR_4_0_GB_ADV;

					if(!strncasecmp(tok, "3.0GB",5))        g_model_ctx.ddr_size    = MODEL_OPT_DDR_3_0_GB_ADV;
					if(!strncasecmp(tok, "4.0GB",5))        g_model_ctx.ddr_size    = MODEL_OPT_DDR_4_0_GB_ADV;

					if(!strncasecmp(tok, "FHD",3))			g_model_ctx.disp_model	= MODEL_OPT_FHD;
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
								(g_model_ctx.disp_model== MODEL_OPT_UHD)?  "UHD":
								(g_model_ctx.disp_model== MODEL_OPT_FHD)?  "FHD":"n/a");
	printk("SOC  : %s\n",		"O20(LG1212)");
    printk("DDR  : %s\n",		(g_model_ctx.ddr_size == MODEL_OPT_DDR_4_0_GB_ADV)? "2.5GB(ADV)":
								(g_model_ctx.ddr_size == MODEL_OPT_DDR_3_0_GB_ADV)? "3.0GB(ADV)": "n/a");
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

	switch(g_model_ctx.disp_model)
	{
		case MODEL_OPT_FHD:		plt_val = LX_CHIP_PLT_FHD; break;
		case MODEL_OPT_QUHD:	plt_val = LX_CHIP_PLT_QUHD;break;
		default:				plt_val = LX_CHIP_PLT_UHD; break;
	}

	switch(g_model_ctx.ddr_size)
	{
		case MODEL_OPT_DDR_4_0_GB_ADV: board_opt_val |= (LX_BOARD_OPT_DDR_2_5GB|LX_BOARD_OPT_ADV); break;
		case MODEL_OPT_DDR_3_0_GB_ADV: board_opt_val |= (LX_BOARD_OPT_DDR_3_0GB|LX_BOARD_OPT_ADV); break;
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

