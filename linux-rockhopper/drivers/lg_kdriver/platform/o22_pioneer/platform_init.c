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

#define __MEM_VALUE_SELECT(val_4k,val_8k)	((UINT32)(g_model_ctx.disp_model==MODEL_OPT_QUHD)? (val_8k):(val_4k))

#define __ASSERT(condition) \
do { \
    if (unlikely(!(condition)))\
    {\
        printk("WARNING: Assert Fail(%s)\n", #condition);\
        WARN_ON(1);\
    }\
} while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	DDR_RGN_M0_DEV 		= 0,
	DDR_RGN_M1_DEV,
	DDR_RGN_M2_DEV,
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
	const char* alias;
}
LX_MEMCFG_DESC_T;

typedef enum
{
	MODEL_OPT_UHD			= 0x0,
	MODEL_OPT_QUHD			= 0x1,
	MODEL_OPT_FHD			= 0x2,
	MODEL_OPT_HD			= 0x3,

	MODEL_OPT_2_5_GB		= 0x2,	/* 2.5GB 64Bit: M0=1.5GB, M1=1GB */
	MODEL_OPT_3_5_GB		= 0x3,	/* 3.0GB 64Bit: M0=2GB, M1=?GB */

	MODEL_OPT_USR			= 0x1,	/* enable USR option */

	MODEL_OPT_NO_FRC		= 0x0,
	MODEL_OPT_INT_FRC		= 0x1,	/* default value */
	MODEL_OPT_EXT_FRC		= 0x2,

	MODEL_OPT_60HZ			= 0x1,
	MODEL_OPT_120HZ			= 0x2,	/* default value */

	MODEL_OPT_PANEL_NONE	= 0x0,	/* no panel = stbbox */
	MODEL_OPT_PANEL_LCD		= 0x1,
	MODEL_OPT_PANEL_OLED	= 0x2,

	MODEL_OPT_2K_GRAPHIC	= 0x1,	/* default value */
	MODEL_OPT_4K_GRAPHIC	= 0x2,	/* 4K graphics */
	MODEL_OPT_HD_GRAPHIC	= 0x3,	/* HD graphics */
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
	MODEL_OPT_T usr1;				/* if defined, we try to setup test environment for 4K120 video decoder */
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
static void BASE_PLT_ForceHmaPool(void);
static void BASE_PLT_SetupCommon(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int 	pioneer_hwopt_probe = PIONEER_PROBE_CFG;// TODO: set to 1 if bringup is completed
static int 	webos_hwopt_probe 	= WEBOS_PROBE_CFG;	// TODO: set to 1 if bringup is completed

module_param(webos_hwopt_probe, int, 0644);
module_param(pioneer_hwopt_probe, int, 0644);

static MODEL_OPT_CTX_T	g_model_ctx =
{
	.ddr_size	= MODEL_OPT_2_5_GB,     /* 2.5GB by default */
	.disp_model	= MODEL_OPT_UHD,        /* UHD by default */
	.frc_conn	= MODEL_OPT_INT_FRC,    /* INT_FRC default */
	.frc_hz		= MODEL_OPT_120HZ,      /* 120HZ   default */
	.panel		= MODEL_OPT_PANEL_OLED, /* LCD/LED default */
	.graphic	= MODEL_OPT_2K_GRAPHIC, /* 2K      default */
	.usr0		= 0,
	.usr1		= 0,
	.usr2		= 0,
	.usr3		= 0
};


static LX_MEMCFG_T	gMemCfgHdr[DDR_RGN_MAX]=
{
	{.name = "[header]M0/BWB", .base = 0x0, .size = 0},
	{.name = "[header]M1",     .base = 0x0, .size = 0 },
	{.name = "[header]SYS",    .base = 0x0, .size = 0}
};

//static LX_MEMCFG_T static_rgn_m0_start	= { .name = "static(M0)",	.base = 0x0, .size = 0 };		/* mem seperator */

/* group memcfg */
static LX_MEMCFG_T __bwb_mem_grp	= { .name = "bwb_mem",		.base = 0x0, .size = 0 };
static LX_MEMCFG_T __m0_s_mem_grp	= { .name = "m0_s_mem",		.base = 0x0, .size = 0 };
static LX_MEMCFG_T __m0_ns_mem_grp	= { .name = "m1_ns_mem",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T __m1_s_mem_grp	= { .name = "vdec(vpb)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T __m1_ns_mem_grp	= { .name = "vdec(dpb0)",	.base = 0x0, .size = 0 };

/* module memcfg */
static LX_MEMCFG_T vdec_vpb0		= { .name = "vdec(vpb)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_vpb1		= { .name = "vdec(dpb8k)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_cpb0		= { .name = "vdec(cpb)",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_gen			= { .name = "vdec(vdec)",	.base = 0x0, .size = 0 };

static LX_MEMCFG_T venc				= { .name = "venc",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T venc_s			= { .name = "venc_s",	.base = 0x0, .size = 0 };

//static LX_MEMCFG_T __audio_start	= { .name = "audio_start",	.base = 0x0, .size = 0 };
static LX_MEMCFG_T audio0_buffer	= { .name = "audio",		.base = 0x0, .size = 0 };
static LX_MEMCFG_T lne_buffer		= { .name = "lne_buffer",	.base = 0x0, .size = LNE_BUFFER_SZ};
static LX_MEMCFG_T npu_buffer		= { .name = "npu_buffer",	.base = 0x0, .size = 0 };

static LX_MEMCFG_T sys0				= {.name = "sys_ns",		.base = 0x0, .size = __MB(1) };

static LX_MEMCFG_T debug0			= {.name = "debug(m0)",		.base = 0x0, .size = 0 };
static LX_MEMCFG_T debug1			= {.name = "debug(m1)",		.base = 0x0, .size = 0 };

static LX_MEMCFG_T gfx_surf0		= {.name = "gfx(surface)",	.base = 0x0, .size = 0 };

//static LX_MEMCFG_T gMemCfgFreeMem0= {.name = "free(0)", 		.base = 0x0, .size = 0 };
//static LX_MEMCFG_T gMemCfgFreeMem1= {.name = "free(1)", 		.base = 0x0, .size = 0 };
//static LX_MEMCFG_T gMemCfgFreeMem2= {.name = "free(2)", 		.base = 0x0, .size = 0 };

/* region ID definition */
typedef enum
{
	MEM_DESC_ID_GFX0 = 0,
	MEM_DESC_ID_GFX1,
	MEM_DESC_ID_VENC,
	MEM_DESC_ID_VENC_S,			/* secure venc*/
	MEM_DESC_ID_AUDIO0,
	MEM_DESC_ID_FBDEV,
	MEM_DESC_ID_TE,

	MEM_DESC_ID_VDEC_VPB0,
	MEM_DESC_ID_VDEC_VPB1,
	MEM_DESC_ID_VDEC_CPB0,
	MEM_DESC_ID_VDEC_GEN,

	MEM_DESC_ID_DEMOD,
	MEM_DESC_ID_DEMOD_FW,

	MEM_DESC_ID_PQE0_SVP,		/* secure, pqe0 */
	MEM_DESC_ID_PQE0_NSV,		/* non-secure, pqe0 */
	MEM_DESC_ID_PQE0_USR,		/* non-secure, pqe0 */
	//MEM_DESC_ID_PQE0_DBG,		/* non-secure, pqe0 */
	MEM_DESC_ID_PQE1_SVP,		/* secure, pqe1 */
	MEM_DESC_ID_PQE1_NSV,		/* non-secure, pqe1 */
	MEM_DESC_ID_PQE1_USR,		/* non-secure, pqe1 */
	//MEM_DESC_ID_PQE1_DBG,		/* non-secure, pqe1 */

	MEM_DESC_ID_TCON,

	MEM_DESC_ID_VBI,
	MEM_DESC_ID_CVD,

    MEM_DESC_ID_HDMI_FEC,
    MEM_DESC_ID_ESM_CODE,
    MEM_DESC_ID_ESM_DATA,

	MEM_DESC_ID_LNE,
	MEM_DESC_ID_NPU,

	MEM_DESC_ID_DEBUG0,			/* DEBUG(M0) */
	MEM_DESC_ID_DEBUG1,			/* DEBUG(M1) */

	MEM_DESC_ID_SYS0,
	MEM_DESC_ID_SYS1,

	MEM_DESC_ID_FREE0,			/* free memory reporter */
	MEM_DESC_ID_FREE1,			/* free memory reporter */
	MEM_DESC_ID_FREE2,			/* free memory reporter */
	MEM_DESC_ID_FREE3,			/* free memory reporter */

	MEM_DESC_ID_MAX,
}
MEM_DESC_ID_T;

/* memory alias list for CMA processing */
#define MEM_DESC(n)				(mem_desc[MEM_DESC_ID_##n].m)
#define MEM_DESC_NAME(n)		(mem_desc[MEM_DESC_ID_##n].m.name)
#define MEM_DESC_BASE(n)		(mem_desc[MEM_DESC_ID_##n].m.base)
#define MEM_DESC_SIZE(n)		(mem_desc[MEM_DESC_ID_##n].m.size)
#define MEM_DESC_FLAG(n)		(mem_desc[MEM_DESC_ID_##n].flag)

#define DEFINE_MEM_DESC(n,f,a)	[MEM_DESC_ID_##n] = { .m={ .name = #n"_hma", .base = 0x0, .size = 0 }, .flag=f, .alias=a }

static LX_MEMCFG_DESC_T mem_desc[MEM_DESC_ID_MAX]	= {
	DEFINE_MEM_DESC(GFX0		,MEMCFG_DESC_FLAG_CMA, "surface"),		/* CMA */
	DEFINE_MEM_DESC(GFX1		,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(VENC		,MEMCFG_DESC_FLAG_CMA, NULL),		/* CMA */
	DEFINE_MEM_DESC(VENC_S		,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(AUDIO0		,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(FBDEV		,MEMCFG_DESC_FLAG_NO_CMA, NULL),

	DEFINE_MEM_DESC(VDEC_VPB0	,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(VDEC_VPB1	,MEMCFG_DESC_FLAG_CMA, "vpb8k"),	/* CMA */
	DEFINE_MEM_DESC(VDEC_CPB0	,MEMCFG_DESC_FLAG_CMA, "cpb"),		/* CMA */
	DEFINE_MEM_DESC(VDEC_GEN	,MEMCFG_DESC_FLAG_NO_CMA, NULL),

	DEFINE_MEM_DESC(TE			,MEMCFG_DESC_FLAG_CMA, NULL),		/* CMA */

	DEFINE_MEM_DESC(DEMOD		,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(DEMOD_FW	,MEMCFG_DESC_FLAG_NO_CMA, NULL),

	DEFINE_MEM_DESC(PQE0_SVP	,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(PQE0_NSV	,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(PQE0_USR	,MEMCFG_DESC_FLAG_CMA, NULL),
	DEFINE_MEM_DESC(PQE1_SVP	,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(PQE1_NSV	,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(PQE1_USR	,MEMCFG_DESC_FLAG_CMA, NULL),

	DEFINE_MEM_DESC(TCON		,MEMCFG_DESC_FLAG_NO_CMA, NULL),

	DEFINE_MEM_DESC(VBI			,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(CVD			,MEMCFG_DESC_FLAG_NO_CMA, NULL),	/* Do Not Use CMA */

	DEFINE_MEM_DESC(HDMI_FEC	,MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(ESM_CODE, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(ESM_DATA, MEMCFG_DESC_FLAG_NO_CMA, NULL),

	DEFINE_MEM_DESC(LNE			,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(NPU			,MEMCFG_DESC_FLAG_CMA, NULL),		/* CMA */

	DEFINE_MEM_DESC(SYS0		,MEMCFG_DESC_FLAG_NONE, NULL),
	DEFINE_MEM_DESC(SYS1		,MEMCFG_DESC_FLAG_NONE, NULL),

	DEFINE_MEM_DESC(DEBUG0 		,MEMCFG_DESC_FLAG_CMA, "debug0"),	/* CMA */
	DEFINE_MEM_DESC(DEBUG1 		,MEMCFG_DESC_FLAG_CMA, "debug1"),	/* CMA */

	DEFINE_MEM_DESC(FREE0		,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(FREE1		,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(FREE2		,MEMCFG_DESC_FLAG_NO_CMA, NULL),
	DEFINE_MEM_DESC(FREE3		,MEMCFG_DESC_FLAG_NO_CMA, NULL),
};

/*---------------------------------------------------------------------------------------
 * Global Memory Configuration data base
 *--------------------------------------------------------------------------------------*/
static LX_MEMCFG_ENTRY_T* g_mem_desc_table;

/* 2.5GB 80bit Memory Configuration
 *
 *
 */
static LX_MEMCFG_ENTRY_T g_mem_desc_table_DDR_2_5_GB_ADV[] =
{
	//-----------------------------------------------------------------------------------
	//	BWB GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),

	LX_MEMCFG_ENTRY(__bwb_mem_grp),

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec_vpb0, MEM_DESC(VDEC_VPB0)),
	LX_MEMCFG_ENTRY_EX(vdec_vpb1, MEM_DESC(VDEC_VPB1)),
#endif

	//-----------------------------------------------------------------------------------
	//	M0 SECURE MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(__m0_s_mem_grp),

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_svp, MEM_DESC(PQE0_SVP)),
#endif

#ifdef INCLUDE_KDRV_VENC
	LX_MEMCFG_ENTRY_EX(venc_s, MEM_DESC(VENC_S)),
#endif

	//-----------------------------------------------------------------------------------
	//	M0 NON-SECURE MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(__m0_ns_mem_grp),

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec_gen, MEM_DESC(VDEC_GEN)),
#endif

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec_cpb0, MEM_DESC(VDEC_CPB0)),
#endif

#ifdef INCLUDE_KDRV_VENC
	// SICDTV-10603 venc0 is moved to cpb pool
	//LX_MEMCFG_ENTRY_EX(venc, MEM_DESC(VENC)),
#endif

#ifdef INCLUDE_KDRV_DEMOD
//	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD,MEM_DESC(DEMOD)),
	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),
#endif

#ifdef INCLUDE_KDRV_TE
	LX_MEMCFG_ENTRY_EX(gMemCfgTE, MEM_DESC(TE)),
#endif

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_nsv, MEM_DESC(PQE0_NSV)),
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_usr, MEM_DESC(PQE0_USR)),
	//LX_MEMCFG_ENTRY_EX(g_m0_pqe_dbg, MEM_DESC(PQE0_DBG)), shared from debug0
#endif

#ifdef INCLUDE_KDRV_AUDIO
	LX_MEMCFG_ENTRY_EX(audio0_buffer, MEM_DESC(AUDIO0)),
#endif

#ifdef INCLUDE_KDRV_GFX
	LX_MEMCFG_ENTRY_EX(gfx_surf0, MEM_DESC(GFX0)),
#endif

#ifdef INCLUDE_KDRV_FBDEV
	LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf,MEM_DESC(FBDEV)),
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),
#endif

#ifdef INCLUDE_KDRV_AFE
    //LX_MEMCFG_ENTRY_EX(gCvdMemCfg, 	MEM_DESC(CVD)),	// moved to te_shared pool
#endif

#ifdef INCLUDE_KDRV_HDMI20
    LX_MEMCFG_ENTRY_EX(gMemCfgHdmiFec[0], MEM_DESC(HDMI_FEC)),
#endif

	LX_MEMCFG_ENTRY_EX(npu_buffer, MEM_DESC(NPU)),

	LX_MEMCFG_ENTRY_EX(debug0, MEM_DESC(DEBUG0)),

	//-----------------------------------------------------------------------------------
	// M1 SECURE MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M1_DEV]),
	LX_MEMCFG_ENTRY(__m1_s_mem_grp),

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_svp, MEM_DESC(PQE1_SVP)),
#endif

	//-----------------------------------------------------------------------------------
	// M1 NON-SECURE MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(__m1_ns_mem_grp),

#ifdef INCLUDE_KDRV_OVI
	LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[2], MEM_DESC(TCON)),
#endif

	LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_nsv, MEM_DESC(PQE1_NSV)),
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_usr, MEM_DESC(PQE1_USR)),
#endif

#ifdef INCLUDE_KDRV_HDMI20
    LX_MEMCFG_ENTRY_EX(gMemCfgEsm[0], MEM_DESC(ESM_CODE)),
    LX_MEMCFG_ENTRY_EX(gMemCfgEsm[1], MEM_DESC(ESM_DATA)),
#endif
	LX_MEMCFG_ENTRY_EX(debug1, MEM_DESC(DEBUG1)),

	//-----------------------------------------------------------------------------------
	// SYS MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M2_DEV]),
	LX_MEMCFG_ENTRY_EX(sys0, MEM_DESC(SYS0)),

	LX_MEMCFG_ENTRY_END
};

static LX_MEMCFG_ENTRY_T g_mem_desc_table_DDR_3_5_GB_ADV[] =
{
	//-----------------------------------------------------------------------------------
	//	BWB GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),

	LX_MEMCFG_ENTRY(__bwb_mem_grp),

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec_vpb0, MEM_DESC(VDEC_VPB0)),
	LX_MEMCFG_ENTRY_EX(vdec_vpb1, MEM_DESC(VDEC_VPB1)),
#endif

	//-----------------------------------------------------------------------------------
	//	M0 SECURE MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(__m0_s_mem_grp),

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_svp, MEM_DESC(PQE0_SVP)),
#endif

#ifdef INCLUDE_KDRV_VENC
	LX_MEMCFG_ENTRY_EX(venc_s, MEM_DESC(VENC_S)),
#endif

	//-----------------------------------------------------------------------------------
	//	M0 NON-SECURE MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(__m0_ns_mem_grp),

#ifdef INCLUDE_KDRV_VDEC
	LX_MEMCFG_ENTRY_EX(vdec_gen, MEM_DESC(VDEC_GEN)),
#endif

//#ifdef INCLUDE_KDRV_VDEC
//	LX_MEMCFG_ENTRY_EX(vdec_cpb0, MEM_DESC(VDEC_CPB0)),
//#endif

//#ifdef INCLUDE_KDRV_VENC
//	LX_MEMCFG_ENTRY_EX(venc, MEM_DESC(VENC)),
//#endif

#ifdef INCLUDE_KDRV_DEMOD
//	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD,MEM_DESC(DEMOD)),
	LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),
#endif

#ifdef INCLUDE_KDRV_TE
	LX_MEMCFG_ENTRY_EX(gMemCfgTE, MEM_DESC(TE)),
#endif

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_nsv, MEM_DESC(PQE0_NSV)),
	LX_MEMCFG_ENTRY_EX(g_m0_pqe_usr, MEM_DESC(PQE0_USR)),
	//LX_MEMCFG_ENTRY_EX(g_m0_pqe_dbg, MEM_DESC(PQE0_DBG)), shared from debug0
#endif

#ifdef INCLUDE_KDRV_AUDIO
	LX_MEMCFG_ENTRY_EX(audio0_buffer, MEM_DESC(AUDIO0)),
#endif

#ifdef INCLUDE_KDRV_FBDEV
	LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf,MEM_DESC(FBDEV)),
#endif

#ifdef INCLUDE_KDRV_VBI
	LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),
#endif

#ifdef INCLUDE_KDRV_AFE
    //LX_MEMCFG_ENTRY_EX(gCvdMemCfg, 	MEM_DESC(CVD)),	// moved to te_shared pool
#endif

#ifdef INCLUDE_KDRV_HDMI20
	LX_MEMCFG_ENTRY_EX(gMemCfgHdmiFec[0], MEM_DESC(HDMI_FEC)),
#endif


	LX_MEMCFG_ENTRY_EX(debug0, MEM_DESC(DEBUG0)),

	//-----------------------------------------------------------------------------------
	// M1 SECURE MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M1_DEV]),
	LX_MEMCFG_ENTRY(__m1_s_mem_grp),

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_svp, MEM_DESC(PQE1_SVP)),
#endif

	//-----------------------------------------------------------------------------------
	// M1 NON-SECURE MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(__m1_ns_mem_grp),

#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_nsv, MEM_DESC(PQE1_NSV)),
	LX_MEMCFG_ENTRY_EX(g_m1_pqe_usr, MEM_DESC(PQE1_USR)),
#endif

#ifdef INCLUDE_KDRV_OVI
	LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[2], MEM_DESC(TCON)),
#endif

	LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),

#ifdef INCLUDE_KDRV_GFX
	LX_MEMCFG_ENTRY_EX(gfx_surf0, MEM_DESC(GFX0)),
#endif

	LX_MEMCFG_ENTRY_EX(npu_buffer, MEM_DESC(NPU)),

#ifdef INCLUDE_KDRV_HDMI20
    LX_MEMCFG_ENTRY_EX(gMemCfgEsm[0], MEM_DESC(ESM_CODE)),
    LX_MEMCFG_ENTRY_EX(gMemCfgEsm[1], MEM_DESC(ESM_DATA)),
#endif

	LX_MEMCFG_ENTRY_EX(debug1, MEM_DESC(DEBUG1)),

	//-----------------------------------------------------------------------------------
	// SYS MEM GROUP
	//-----------------------------------------------------------------------------------
	LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M2_DEV]),
	LX_MEMCFG_ENTRY_EX(sys0, MEM_DESC(SYS0)),

	LX_MEMCFG_ENTRY_END
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static void BASE_PLT_ForceHmaPool(void)
{
	int i;

    for (i = 0; i < MEM_DESC_ID_MAX; i++)
	{
		if(mem_desc[i].flag == MEMCFG_DESC_FLAG_CMA)
		{
			if(mem_desc[i].alias && check_force_hma_pool(mem_desc[i].alias))
			{
				mem_desc[i].flag = MEMCFG_DESC_FLAG_NO_CMA;
				printk("force_hma_pool: %s pool is set to hma pool by user\n", mem_desc[i].alias);
			}
		}
	}
}
static void BASE_PLT_SetupMemLayout(void)
{
	printk("configure O22(%2X) kdriver memory\n", lx_chip_rev() & 0xff);

	gMemCfgHdr[DDR_RGN_M0_DEV].base = __MEM_VALUE_SELECT(UHD_M0_2_5_GB_DEV_BASE, UHD_M0_3_5_GB_DEV_BASE);
	gMemCfgHdr[DDR_RGN_M0_DEV].size = __MEM_VALUE_SELECT(UHD_M0_2_5_GB_DEV_SZ, UHD_M0_3_5_GB_DEV_SZ);
	gMemCfgHdr[DDR_RGN_M1_DEV].base = __MEM_VALUE_SELECT(UHD_M1_2_5_GB_DEV_BASE, UHD_M1_3_5_GB_DEV_BASE);
	gMemCfgHdr[DDR_RGN_M1_DEV].size = __MEM_VALUE_SELECT(UHD_M1_2_5_GB_DEV_SZ, UHD_M1_3_5_GB_DEV_SZ);
	gMemCfgHdr[DDR_RGN_M2_DEV].base = __MEM_VALUE_SELECT(UHD_M2_2_5_GB_DEV_BASE, UHD_M2_3_5_GB_DEV_BASE);
	gMemCfgHdr[DDR_RGN_M2_DEV].size = __MEM_VALUE_SELECT(UHD_M2_2_5_GB_DEV_SZ, UHD_M2_3_5_GB_DEV_SZ);

	BASE_PLT_SetupCommon();

	switch(g_model_ctx.ddr_size)
	{
		case MODEL_OPT_3_5_GB:	g_mem_desc_table = g_mem_desc_table_DDR_3_5_GB_ADV; break;
		case MODEL_OPT_2_5_GB:
		default:				g_mem_desc_table = g_mem_desc_table_DDR_2_5_GB_ADV; break;
	}
}

static void BASE_PLT_SetupCommon(void)
{
	/* setup group memcfg */
	__bwb_mem_grp.base	= gMemCfgHdr[DDR_RGN_M0_DEV].base;
	__m0_s_mem_grp.base	= __bwb_mem_grp.base + __MEM_VALUE_SELECT(BWB_MEM_GRP_4K_SZ, BWB_MEM_GRP_8K_SZ);
	__m0_ns_mem_grp.base= __m0_s_mem_grp.base + __MEM_VALUE_SELECT(M0_S_MEM_GRP_4K_SZ, M0_S_MEM_GRP_8K_SZ);

	__m1_s_mem_grp.base	= gMemCfgHdr[DDR_RGN_M1_DEV].base;
	__m1_ns_mem_grp.base= __m1_s_mem_grp.base + __MEM_VALUE_SELECT(M1_S_MEM_GRP_4K_SZ, M1_S_MEM_GRP_8K_SZ);

	/* setup gfx */
#ifdef INCLUDE_KDRV_GFX
	gfx_surf0.size = __MEM_VALUE_SELECT(GFXOSD_SURFACE_4K_SZ, GFXOSD_SURFACE_8K_SZ);
	gMemCfgGfx.surface[0].size	= gfx_surf0.size;
#endif

	/* setup vdec */
	vdec_vpb0.size 	= UHD_VPB4K_SZ;
	vdec_vpb1.size 	= __MEM_VALUE_SELECT(UHD_VPB8K_4K_SZ, UHD_VPB8K_8K_SZ);
	vdec_cpb0.size	= UHD_VDEC_CPB_SZ;
	vdec_gen.size	= UHD_VDEC_GEN_SZ;
	venc.size		= VENC_SZ;
	venc_s.size		= VENC_S_SZ;

	// make vpb8k HMA pool instead of default desc to prevent OOM killer.
	// see http://clm.lge.com/issue/browse/SCDCR-4683
	if (g_model_ctx.disp_model== MODEL_OPT_QUHD)
	{
		printk("make vpb8k HMA pool. see SCDCR-4683\n");
		mem_desc[MEM_DESC_ID_VDEC_VPB1].flag = MEMCFG_DESC_FLAG_NO_CMA;
	}

	/* setup audio */
	audio0_buffer.size = AUDIO_BUFFER_SZ_0;

	/* setup npu */
	npu_buffer.size = NPU_BUFFER_SZ;

}

/* run the post memory layout after memory allocation
 *
 */
static void BASE_PLT_DoPostMemLayout(void)
{
	int i;
	int ret;

	unsigned int debug0_min_size = __MEM_VALUE_SELECT(M0_DEBUG_4K_SZ, M0_DEBUG_8K_SZ);
	unsigned int debug1_min_size = __MEM_VALUE_SELECT(M1_DEBUG_4K_SZ, M1_DEBUG_8K_SZ);

	/* make the full-sized debug0, debug1 memory */
	debug0.size = gMemCfgHdr[DDR_RGN_M0_DEV].base + gMemCfgHdr[DDR_RGN_M0_DEV].size - debug0.base;
	MEM_DESC_SIZE(DEBUG0) = debug0.size;

	debug1.size = gMemCfgHdr[DDR_RGN_M1_DEV].base + gMemCfgHdr[DDR_RGN_M1_DEV].size - debug1.base;
	MEM_DESC_SIZE(DEBUG1) = debug1.size;

	printk("\n");
	printk("++ debug0 size tuned. debug0.size=0x%08x(%dKB) min_size=0x%08x(%dKB)\n",
		debug0.size, debug0.size >> 10, debug0_min_size, debug0_min_size >> 10);
	printk("++ debug1 size tuned. debug1.size=0x%08x(%dKB) min_size=0x%08x(%dKB)\n",
		debug1.size, debug1.size >> 10, debug1_min_size, debug1_min_size >> 10);
	printk("\n");

	// see http://clm.lge.com/issue/browse/SICDTV-13880
	__ASSERT(debug0.size >= debug0_min_size);
	__ASSERT(debug1.size >= debug1_min_size);

#if 0
	/* print tuned memory layout for debug */
	extern void BASE_DEVMEM_DumpMemCfg(struct seq_file* m, UINT32 opt);
	BASE_DEVMEM_DumpMemCfg(NULL, 0x0);
#endif

	/* if memory region is set to NO_CMA, get device region from kernel to device driver with help of HMA */
	printk("\n++ memory pool registeration ++\n");
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
						printk("(x) CMA(%-15s %3dM@0x%08x) HMA\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
						hma_alloc(mem_desc[i].m.name, mem_desc[i].m.size, 1<<12);
					}
					else
					{
						printk("(?) CMA(%-15s %3dM@0x%08x) register error\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
					}
				}
				else
				{
					printk("(x) CMA(%-15s %3dM@0x%08x) ignored\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
				}
			}
			break;

			case MEMCFG_DESC_FLAG_CMA:
			{
				/* do nothing. each device will create its own CMA allocator */
				printk("(o) CMA(%-15s %3dM@0x%08x) CMA\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
			}
			break;

			default:
			{
				/* do nothing. this is BSP dedicated area */
				printk("(/) CMA(%-15s %3dM@0x%08x) skip\n", mem_desc[i].m.name, mem_desc[i].m.size>>20, mem_desc[i].m.base);
			}
			break;
		}
	}
	printk("\n");

	// make the real hma(cma) pool for the kdriver and application
	printk("++ exported cma/hma pool registeration ++\n");
	{
		struct
		{
			const char *name;
			int	mem_desc_id;
		}
		vdec_mem_desc[] =
		{
			{ "vpb",   			MEM_DESC_ID_VDEC_VPB0},
			{ "vpb8k",  		MEM_DESC_ID_VDEC_VPB1},
			{ "cpb",			MEM_DESC_ID_VDEC_CPB0},
			{ "vdec",			MEM_DESC_ID_VDEC_GEN},

			{ "venc0",			MEM_DESC_ID_VENC},
			{ "venc1",			MEM_DESC_ID_VENC_S},

			{ "debug0",			MEM_DESC_ID_DEBUG0},
			{ "debug1",			MEM_DESC_ID_DEBUG1},
#ifdef INCLUDE_KDRV_AUDIO
			{ "audio_buffer0",	MEM_DESC_ID_AUDIO0},
#endif
			{ "surface",		MEM_DESC_ID_GFX0},
			{ "npu",    		MEM_DESC_ID_NPU},
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
			pool_type  = (mem_desc[ vdec_mem_desc[a].mem_desc_id ].flag == MEMCFG_DESC_FLAG_CMA)? CMA_POOL: HMA_POOL;

			if (base == 0 || size == 0)
			{
				printk("---(%16s), %3dM@0x%08x, none\n", name, size>>20, base);
				continue;
			}

			ret = hma_pool_register_type(name, base, size, pool_type);

			if (ret==0)
			{
				printk("cma(%16s), %3dM@0x%08x, %s pool\n", name, size>>20, base, (pool_type==CMA_POOL)?"CMA":"HMA");
			}
			else
			{
				printk ("cannot register %s pool\n", name);
				break;
			}
		}
    }
	printk("\n");

	if (g_model_ctx.disp_model == MODEL_OPT_QUHD)
	{
		hma_pool_alias("photofb","vpb8k");	// access vpb8k through "photofb"
		hma_pool_alias("venc0", "vpb8k");	// access vpb8k through "vecn0"
		hma_pool_alias("cpb", "vpb8k");		// access vpb8k through "cpb"
		hma_pool_alias("cpb2", "vpb8k");	// access vpb8k through "cpb2"

		hma_pool_fallback("vpb", "vpb8k");	// redirect vpb to vpb8k if out of memory
	}
	else
	{
		hma_pool_alias("cpb2","cpb"); 		// access cpb through "cpb2"
		hma_pool_alias("photofb","cpb");	// access cpb through "photofb"
		hma_pool_alias("venc0","cpb");      // access cpb through "venc0"
	}

	hma_pool_alias("dpb", "vpb"); 			// access vpb through "dpb" for legacy interface
	hma_pool_alias("mtest-ddr0", "debug0"); // access debug0 through mtest-ddr0
	hma_pool_alias("mtest-ddr1", "debug1");	// access debug1 through mtest-ddr1
	hma_pool_alias("de-dbg-m1", "debug0");	// access debug0 through de-dbg-m1
	hma_pool_alias("de-dbg-m2", "debug1");	// access debug1 through de-dbg-m2

	hma_pool_alias("surface_ext", "debug0");// access debug0 through surface_ext
	hma_pool_alias("audio_buffer", "audio_buffer0");  // access audio_buffer0 through audio_buffer

	// http://clm.lge.com/issue/browse/SICDTV-8565
	// pqe-lne pool is used only for pool info
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

	BASE_PLT_ForceHmaPool();

	BASE_PLT_SetupMemLayout();

	ret = BASE_DEVMEM_InitDevMem(g_mem_desc_table);
	if (ret != RET_OK) DBG_PRINT_ERROR("fatal error during making kdriver memory layout\n");

	BASE_PLT_DoPostMemLayout();
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

		/* scan webOS board config */
		if (RET_OK == OS_ScanKernelCmdline("hwopt=%s",hwopt_txt))
		{
			/* 0: HD(1366x768)  1: FHD(1920x1080)  2: UHD(3840x2160) 3: QUHD(7680x4320)... */
			switch(hwopt_txt[3])
			{
				case '0': g_model_ctx.disp_model = MODEL_OPT_HD; break;
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

			/* 2: 2K, 4: 4K */
			switch(hwopt_txt[14])
			{
				case '6': g_model_ctx.graphic = MODEL_OPT_HD_GRAPHIC; break;
				case '4': g_model_ctx.graphic = MODEL_OPT_4K_GRAPHIC; break;
				default:  g_model_ctx.graphic = MODEL_OPT_2K_GRAPHIC; break;
			}

			/* 0: 60Hz, 1: 120Hz */
			switch(hwopt_txt[4])
			{
				case '0': g_model_ctx.frc_hz    = MODEL_OPT_60HZ; break;
				case '1':
				default:  g_model_ctx.frc_hz    = MODEL_OPT_120HZ; break;
			}

			/* 5: 2.5GB, 11: 3.5GB */
			switch(hwopt_txt[11])
			{
				case 'b': g_model_ctx.ddr_size = MODEL_OPT_3_5_GB; break;
				default:  g_model_ctx.ddr_size = MODEL_OPT_2_5_GB; break;
			}
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
					if(!strncasecmp(tok, "2.5GB",5))        g_model_ctx.ddr_size    = MODEL_OPT_2_5_GB;
					if(!strncasecmp(tok, "3.5GB",5))        g_model_ctx.ddr_size    = MODEL_OPT_3_5_GB;

					if(!strncasecmp(tok, "HD",2))			g_model_ctx.disp_model	= MODEL_OPT_HD;
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
					if(!strncasecmp(tok, "HDOSD",5))		g_model_ctx.graphic		= MODEL_OPT_HD_GRAPHIC;

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
								(g_model_ctx.disp_model== MODEL_OPT_FHD)?  "FHD":
								(g_model_ctx.disp_model== MODEL_OPT_HD)?  "HD": "n/a");
	printk("SOC  : %s\n",		"O22(LG1213)");
    printk("DDR  : %s\n",		(g_model_ctx.ddr_size == MODEL_OPT_3_5_GB)? "3.5GB":
								(g_model_ctx.ddr_size == MODEL_OPT_2_5_GB)? "2.5GB": "n/a");
    printk("GFX  : %s\n",		(g_model_ctx.graphic == MODEL_OPT_4K_GRAPHIC)? "4K(3840x2160)":
								(g_model_ctx.graphic == MODEL_OPT_2K_GRAPHIC)? "2K(1920x1080)":
								(g_model_ctx.graphic == MODEL_OPT_HD_GRAPHIC)? "HD(1280x720)": "n/a");
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
		case MODEL_OPT_HD:		plt_val = LX_CHIP_PLT_HD; break;
		case MODEL_OPT_FHD:		plt_val = LX_CHIP_PLT_FHD; break;
		case MODEL_OPT_QUHD:	plt_val = LX_CHIP_PLT_QUHD;break;
		default:				plt_val = LX_CHIP_PLT_UHD; break;
	}

	switch(g_model_ctx.ddr_size)
	{
		case MODEL_OPT_3_5_GB: board_opt_val |= (LX_BOARD_OPT_DDR_3_5GB|LX_BOARD_OPT_ADV); break;
		case MODEL_OPT_2_5_GB: board_opt_val |= (LX_BOARD_OPT_DDR_2_5GB|LX_BOARD_OPT_ADV); break;
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

	switch(g_model_ctx.graphic)
	{
		case MODEL_OPT_4K_GRAPHIC: board_opt_val |= LX_BOARD_OPT_4K_GRAPHIC; break;
		case MODEL_OPT_HD_GRAPHIC: board_opt_val |= LX_BOARD_OPT_HD_GRAPHIC; break;
		case MODEL_OPT_2K_GRAPHIC:
		default:					board_opt_val |= LX_BOARD_OPT_2K_GRAPHIC; break;
	}

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
