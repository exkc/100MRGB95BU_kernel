/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2023 by LG Electronics Inc.
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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#define PIONEER_PROBE_CFG           1       /* parse PIONEER toolopts */
#define WEBOS_PROBE_CFG             1       /* parse webOS toolopts */

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
#define LX_MEMCFG_ENTRY(item)               { .name= _STR(item), .pM=(LX_MEMCFG_T*)&(item), .nM=sizeof(item)/sizeof(LX_MEMCFG_T) }
#define LX_MEMCFG_ENTRY_EX(item,alias)      { .name= _STR(item), .pM=(LX_MEMCFG_T*)&(item), .nM=sizeof(item)/sizeof(LX_MEMCFG_T), .flag=LX_MEMCFG_FLAG_ALIAS, .pAlias=&alias }
#define LX_MEMCFG_ENTRY_END                 { .name="Total", .pM=NULL, .nM=0}

#define select_mem_value(cat0,cat1,cat2)    ((g_model_ctx.ddr_size==MODEL_OPT_4_0_GB)?(cat2):\
                                             (g_model_ctx.ddr_size==MODEL_OPT_3_5_GB)?(cat1):(cat0))

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
    DDR_RGN_BWB_DEV     = 0,
    DDR_RGN_M0_DEV,
    DDR_RGN_M1_DEV,
    DDR_RGN_M2_DEV,
    DDR_RGN_SYS_DEV,
    DDR_RGN_MAX,
}
DDR_RGN_T;

typedef struct
{
#define MEMCFG_DESC_FLAG_NONE       0x00000000  /* device such as SE/TZ should keep memory content from the booting stage */
#define MEMCFG_DESC_FLAG_CMA        0x4F434D41  /* device will manage dedicated memory according to its own policy. do nothing in platform_initializer */
#define MEMCFG_DESC_FLAG_NO_CMA     0x4E434D41  /* device requires the pre-allocated device memory even from CMA region */
    UINT32      flag;
    LX_MEMCFG_T m;
    const char* alias;
}
LX_MEMCFG_DESC_T;

typedef enum
{
    MODEL_OPT_UHD           = 0x0,
    MODEL_OPT_QUHD          = 0x1,
    MODEL_OPT_FHD           = 0x2,

    MODEL_OPT_2_5_GB        = 0x2,  /* 2.5GB 64Bit: M0=1.5GB, M1=1GB */
    MODEL_OPT_3_5_GB        = 0x3,  /* 3.0GB 64Bit: M0=1.5GB, M1=1GB, M2=1GB */
    MODEL_OPT_4_0_GB        = 0x4,  /* 4.0GB 96Bit: M0=2.0GB, M1=1GB, M2=1GB */

    MODEL_OPT_USR           = 0x1,  /* enable USR option */

    MODEL_OPT_INT_FRC       = 0x1,  /* default value */
    MODEL_OPT_EXT_FRC       = 0x2,

    MODEL_OPT_60HZ          = 0x1,
    MODEL_OPT_120HZ         = 0x2,  /* default value */

    MODEL_OPT_PANEL_NONE    = 0x0,  /* no panel = stbbox */
    MODEL_OPT_PANEL_LCD     = 0x1,
    MODEL_OPT_PANEL_OLED    = 0x2,

    MODEL_OPT_PANEL_IF_EPI      = 0x0,  /* panel interface = EPI */
    MODEL_OPT_PANEL_IF_OTHERS   = 0x1,  /* panel interface = others */

    MODEL_OPT_2K_GRAPHIC    = 0x1,  /* default value */
    MODEL_OPT_4K_GRAPHIC    = 0x2,  /* 4K graphics */

    MODEL_OPT_SYS_BOARD     = 0x0,
    MODEL_OPT_SLT_BOARD     = 0x1,  /* SLT board */
    MODEL_OPT_FPGA_BOARD    = 0x2,

    MODEL_OPT_PROD_MAP      = 0x0,  /* production memory map */
    MODEL_OPT_SLT_MAP       = 0x1,  /* SLT memory map */
}
MODEL_OPT_T;

typedef struct
{
    MODEL_OPT_T mmap_cfg;
    MODEL_OPT_T ddr_size;
    MODEL_OPT_T disp_model;
    MODEL_OPT_T frc_conn;
    MODEL_OPT_T frc_hz;
    MODEL_OPT_T panel;
    MODEL_OPT_T panel_if;
    MODEL_OPT_T graphic;

    MODEL_OPT_T board;
    MODEL_OPT_T map;

    MODEL_OPT_T usr0;
    MODEL_OPT_T usr1;               /* if defined, we try to setup test environment for 4K120 video decoder */
    MODEL_OPT_T usr2;
    MODEL_OPT_T usr3;
}
MODEL_OPT_CTX_T;

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern  char*   simple_strtok(char* s, const char* delim, char** save_ptr);
extern  int     BASE_DEVMEM_InitDevMem(LX_MEMCFG_ENTRY_T* pEntry);

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
static int pioneer_hwopt_probe = PIONEER_PROBE_CFG;// TODO: set to 1 if bringup is completed
static int webos_hwopt_probe    = WEBOS_PROBE_CFG;  // TODO: set to 1 if bringup is completed
static int memcfg_debug = 0;

module_param(webos_hwopt_probe, int, 0644);
module_param(pioneer_hwopt_probe, int, 0644);
module_param(memcfg_debug, int, 0644);

static MODEL_OPT_CTX_T  g_model_ctx =
{
    .ddr_size   = MODEL_OPT_2_5_GB,     // 2.5GB by default
    .disp_model = MODEL_OPT_UHD,        // UHD by default
    .frc_conn   = MODEL_OPT_INT_FRC,    // INT_FRC by default
    .frc_hz     = MODEL_OPT_120HZ,      // 120HZ by default
    .panel      = MODEL_OPT_PANEL_OLED, // OLED by default
    .panel_if   = MODEL_OPT_PANEL_IF_OTHERS, // Vx1 or others by default
    .graphic    = MODEL_OPT_2K_GRAPHIC, // 2K by default
    .board      = MODEL_OPT_SYS_BOARD,  // SYS_BOARD default
    .map        = MODEL_OPT_PROD_MAP,   // PROD_MAP default
    .usr0       = 0,
    .usr1       = 0,
    .usr2       = 0,
    .usr3       = 0
};


static LX_MEMCFG_T  gMemCfgHdr[DDR_RGN_MAX] =
{
    {.name = "[header]BWB", .base = 0x0, .size = 0},
    {.name = "[header]M0",  .base = 0x0, .size = 0},
    {.name = "[header]M1",  .base = 0x0, .size = 0},
    {.name = "[header]M2",  .base = 0x0, .size = 0},
    {.name = "[header]SYS", .base = 0x0, .size = 0}
};

// group memcfg variable
static LX_MEMCFG_T __m0_s_mem_grp   = { .name = "m0_s_mem",     .base = 0x0, .size = 0 };
static LX_MEMCFG_T __m0_ns_mem_grp  = { .name = "m0_ns_mem",    .base = 0x0, .size = 0 };
static LX_MEMCFG_T __m1_s_mem_grp   = { .name = "m1_s_mem",     .base = 0x0, .size = 0 };
static LX_MEMCFG_T __m1_ns_mem_grp  = { .name = "m1_ns_mem",    .base = 0x0, .size = 0 };
static LX_MEMCFG_T __m2_s_mem_grp   = { .name = "m2_s_mem",     .base = 0x0, .size = 0 };
static LX_MEMCFG_T __m2_ns_mem_grp  = { .name = "m2_ns_mem",    .base = 0x0, .size = 0 };

// module memcfg variable
static LX_MEMCFG_T gfx_surf0        = {.name = "surface",       .base = 0x0, .size = 0 };

static LX_MEMCFG_T vdec_vpb0        = { .name = "vdec(vpb4k)",  .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_vpb1        = { .name = "vdec(dpb8k)",  .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_cpb0        = { .name = "vdec(cpb)",    .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_gen         = { .name = "vdec(vdec)",   .base = 0x0, .size = 0 };

static LX_MEMCFG_T audio0_buffer    = { .name = "audio0",       .base = 0x0, .size = 0 };
static LX_MEMCFG_T audio1_buffer    = { .name = "audio1",       .base = 0x0, .size = 0 };
static LX_MEMCFG_T audio_lnx_buffer = { .name = "audio_lnx",    .base = 0x0, .size = 0 };

static LX_MEMCFG_T lne_buffer       = { .name = "lne_buffer",   .base = 0x0, .size = 0 };
static LX_MEMCFG_T npu0_buffer      = { .name = "npu0_buffer",  .base = 0x0, .size = 0 };
static LX_MEMCFG_T npu1_buffer      = { .name = "npu1_buffer",  .base = 0x0, .size = 0 };

static LX_MEMCFG_T sys0             = {.name = "sys0",          .base = 0x0, .size = __MB(1) };

static LX_MEMCFG_T debug0           = {.name = "debug(m0)",     .base = 0x0, .size = 0 };
static LX_MEMCFG_T debug1           = {.name = "debug(m1)",     .base = 0x0, .size = 0 };
static LX_MEMCFG_T debug2           = {.name = "debug(m2)",     .base = 0x0, .size = 0 };

static LX_MEMCFG_T pqe_bwb          = {.name = "pqe_bwb",       .base = 0x0, .size = 0 };

/* region ID definition */
typedef enum
{
    MEM_DESC_ID_GFX0 = 0,
    MEM_DESC_ID_GFX1,
    MEM_DESC_ID_VENC,
    MEM_DESC_ID_AUDIO0,
    MEM_DESC_ID_AUDIO1,
    MEM_DESC_ID_AUDIO_LNX,
    MEM_DESC_ID_FBDEV,
    MEM_DESC_ID_TE,

    MEM_DESC_ID_VDEC_VPB0,
    MEM_DESC_ID_VDEC_VPB1,
    MEM_DESC_ID_VDEC_CPB0,
    MEM_DESC_ID_VDEC_GEN,

    MEM_DESC_ID_DEMOD,
    MEM_DESC_ID_DEMOD_FW,

    MEM_DESC_ID_PQE0_SVP,       /* secure, pqe0 */
    MEM_DESC_ID_PQE0_NSV,       /* non-secure, pqe0 */
    MEM_DESC_ID_PQE0_USR,       /* non-secure, pqe0 */
    MEM_DESC_ID_PQE1_SVP,       /* secure, pqe1 */
    MEM_DESC_ID_PQE1_NSV,       /* non-secure, pqe1 */
    MEM_DESC_ID_PQE1_USR,       /* non-secure, pqe1 */
    MEM_DESC_ID_PQE2_SVP,       /* secure, pqe2 */
    MEM_DESC_ID_PQE2_NSV,       /* non-secure, pqe1 */
    MEM_DESC_ID_PQE2_USR,       /* non-secure, pqe1 */

    MEM_DESC_ID_PQE_BWB,

    MEM_DESC_ID_TCON,

    MEM_DESC_ID_VBI,
    MEM_DESC_ID_CVD,

    MEM_DESC_ID_HDMI_FEC,
    MEM_DESC_ID_ESM_CODE,
    MEM_DESC_ID_ESM_DATA,

    MEM_DESC_ID_LNE,
    MEM_DESC_ID_NPU0,
    MEM_DESC_ID_NPU1,

    MEM_DESC_ID_DEBUG0,         /* DEBUG(M0) */
    MEM_DESC_ID_DEBUG1,         /* DEBUG(M1) */
    MEM_DESC_ID_DEBUG2,         /* DEBUG(M2) */

    MEM_DESC_ID_SYS0,
    MEM_DESC_ID_SYS1,

    MEM_DESC_ID_FREE0,          /* free memory reporter */
    MEM_DESC_ID_FREE1,          /* free memory reporter */

    MEM_DESC_ID_MAX,
}
MEM_DESC_ID_T;

/* memory alias list for CMA processing */
#define MEM_DESC(n)             (mem_desc[MEM_DESC_ID_##n].m)
#define MEM_DESC_NAME(n)        (mem_desc[MEM_DESC_ID_##n].m.name)
#define MEM_DESC_BASE(n)        (mem_desc[MEM_DESC_ID_##n].m.base)
#define MEM_DESC_SIZE(n)        (mem_desc[MEM_DESC_ID_##n].m.size)
#define MEM_DESC_FLAG(n)        (mem_desc[MEM_DESC_ID_##n].flag)

#define DEFINE_MEM_DESC(n,f,a)  [MEM_DESC_ID_##n] = { .m={ .name = #n"_hma", .base = 0x0, .size = 0 }, .flag=f, .alias=a }

static LX_MEMCFG_DESC_T mem_desc[MEM_DESC_ID_MAX]   =
{
    DEFINE_MEM_DESC(GFX0, MEMCFG_DESC_FLAG_CMA, "surface"),             /* CMA */
    DEFINE_MEM_DESC(AUDIO0, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(AUDIO1, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(AUDIO_LNX, MEMCFG_DESC_FLAG_NO_CMA, "audio_lnx"),

    DEFINE_MEM_DESC(FBDEV, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(VDEC_VPB0, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(VDEC_VPB1, MEMCFG_DESC_FLAG_NO_CMA, "vpb8k"),       /* TODO: 필요시 CMA 조치함 */
    DEFINE_MEM_DESC(VDEC_CPB0, MEMCFG_DESC_FLAG_CMA, "cpb"),            /* CMA 조치 완료 */
    DEFINE_MEM_DESC(VDEC_GEN, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(TE, MEMCFG_DESC_FLAG_CMA, NULL),                    /* TE 모듈에서 개별 처리 */

    DEFINE_MEM_DESC(DEMOD, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(DEMOD_FW, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(PQE0_SVP, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(PQE0_NSV, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(PQE0_USR, MEMCFG_DESC_FLAG_CMA, NULL),           /* CMA 조치 완료 */
    DEFINE_MEM_DESC(PQE1_SVP, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(PQE1_NSV, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(PQE1_USR, MEMCFG_DESC_FLAG_CMA, NULL),           /* CMA 조치 완료 */
    DEFINE_MEM_DESC(PQE2_SVP, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(PQE2_NSV, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(PQE2_USR, MEMCFG_DESC_FLAG_CMA, NULL),           /* CMA 조치 완료 */

    DEFINE_MEM_DESC(PQE_BWB, MEMCFG_DESC_FLAG_CMA, NULL),               /* CMA 조치 완료 */

    DEFINE_MEM_DESC(VBI, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(CVD, MEMCFG_DESC_FLAG_NO_CMA, NULL),                /* Do Not Use CMA */

    DEFINE_MEM_DESC(HDMI_FEC, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(ESM_CODE, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(ESM_DATA, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(LNE, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(NPU0, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(NPU1, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(SYS0, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(SYS1, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(DEBUG0, MEMCFG_DESC_FLAG_CMA, "debug0"),           /* CMA 조치 완료 */
    DEFINE_MEM_DESC(DEBUG1, MEMCFG_DESC_FLAG_CMA, "debug1"),           /* CMA 조치 완료 */

    DEFINE_MEM_DESC(FREE0, MEMCFG_DESC_FLAG_CMA, "free_mem0"),         /* CMA 조치 완료 */
    DEFINE_MEM_DESC(FREE1, MEMCFG_DESC_FLAG_CMA, "free_mem1"),         /* CMA 조치 완료 */
};

/*---------------------------------------------------------------------------------------
 * Global Memory Configuration data base
 *--------------------------------------------------------------------------------------*/
static LX_MEMCFG_ENTRY_T* g_mem_desc_table;

// CAT0 for SLT, bringup for EVAL.BOARD (M0: 1.5GB, M1: 1.0GB, M2: 1.0GB)
// CAT1 for 4K SYS. BOARD (M0 1.5GB, M1 1.0GB)
// (note) cat0 and cat1 shares the same memory map
//
static LX_MEMCFG_ENTRY_T g_mem_desc_table_cat0[] =
{
    //-----------------------------------------------------------------------------------
    //  BWB GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_BWB_DEV]),

#ifdef INCLUDE_KDRV_VDEC
    LX_MEMCFG_ENTRY_EX(vdec_vpb0, MEM_DESC(VDEC_VPB0)),
    LX_MEMCFG_ENTRY_EX(vdec_vpb1, MEM_DESC(VDEC_VPB1)),
#endif

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(pqe_bwb, MEM_DESC(PQE_BWB)),
#endif

    //-----------------------------------------------------------------------------------
    //  M0 SECURE MEM GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),
    LX_MEMCFG_ENTRY(__m0_s_mem_grp),

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio0_buffer, MEM_DESC(AUDIO0)),
#endif

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_svp, MEM_DESC(PQE0_SVP)),
#endif

    //-----------------------------------------------------------------------------------
    //  M0 NON-SECURE MEM GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_ns_mem_grp),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_nsv, MEM_DESC(PQE0_NSV)),
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_usr, MEM_DESC(PQE0_USR)),
    //LX_MEMCFG_ENTRY_EX(g_m0_pqe_dbg, MEM_DESC(PQE0_DBG)), shared from debug0
#endif

#ifdef INCLUDE_KDRV_VDEC
    LX_MEMCFG_ENTRY_EX(vdec_gen, MEM_DESC(VDEC_GEN)),
    LX_MEMCFG_ENTRY_EX(vdec_cpb0, MEM_DESC(VDEC_CPB0)),
#endif

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio1_buffer, MEM_DESC(AUDIO1)),
#endif

#ifdef INCLUDE_KDRV_DEMOD
    //  LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD,MEM_DESC(DEMOD)),
    LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),
#endif

#ifdef INCLUDE_KDRV_TE
    LX_MEMCFG_ENTRY_EX(gMemCfgTE, MEM_DESC(TE)),
#endif

    //LX_MEMCFG_ENTRY_EX(free_mem0, MEM_DESC(FREE0)),

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),
#endif

#ifdef INCLUDE_KDRV_AFE
    //LX_MEMCFG_ENTRY_EX(gCvdMemCfg,  MEM_DESC(CVD)),
#endif

#ifdef INCLUDE_KDRV_HDMI20
    LX_MEMCFG_ENTRY_EX(gMemCfgHdmiFec[0], MEM_DESC(HDMI_FEC)),
    LX_MEMCFG_ENTRY_EX(gMemCfgEsm[0], MEM_DESC(ESM_CODE)),
    LX_MEMCFG_ENTRY_EX(gMemCfgEsm[1], MEM_DESC(ESM_DATA)),
#endif

    LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),


#ifdef INCLUDE_KDRV_FBDEV
    LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),
#endif

#ifdef INCLUDE_KDRV_GFX
    LX_MEMCFG_ENTRY_EX(gfx_surf0, MEM_DESC(GFX0)),
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

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio_lnx_buffer, MEM_DESC(AUDIO_LNX)),
#endif

    LX_MEMCFG_ENTRY_EX(npu0_buffer, MEM_DESC(NPU0)),

    LX_MEMCFG_ENTRY_EX(debug1, MEM_DESC(DEBUG1)),

    //-----------------------------------------------------------------------------------
    // SYS MEM GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_SYS_DEV]),
    LX_MEMCFG_ENTRY_EX(sys0, MEM_DESC(SYS0)),

    LX_MEMCFG_ENTRY_END
};

// CAT2 for 4GB DDR board
//
static LX_MEMCFG_ENTRY_T g_mem_desc_table_cat2[] =
{
    //-----------------------------------------------------------------------------------
    //  BWB GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_BWB_DEV]),

#ifdef INCLUDE_KDRV_VDEC
    LX_MEMCFG_ENTRY_EX(vdec_vpb0, MEM_DESC(VDEC_VPB0)),
    LX_MEMCFG_ENTRY_EX(vdec_vpb1, MEM_DESC(VDEC_VPB1)),
#endif

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(pqe_bwb, MEM_DESC(PQE_BWB)),
#endif

    //-----------------------------------------------------------------------------------
    //  M0 SECURE MEM GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),
    LX_MEMCFG_ENTRY(__m0_s_mem_grp),

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio0_buffer, MEM_DESC(AUDIO0)),
#endif

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_svp, MEM_DESC(PQE0_SVP)),
#endif

    //-----------------------------------------------------------------------------------
    //  M0 NON-SECURE MEM GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_ns_mem_grp),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_nsv, MEM_DESC(PQE0_NSV)),
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_usr, MEM_DESC(PQE0_USR)),
#endif

#ifdef INCLUDE_KDRV_VDEC
    LX_MEMCFG_ENTRY_EX(vdec_gen, MEM_DESC(VDEC_GEN)),
    LX_MEMCFG_ENTRY_EX(vdec_cpb0, MEM_DESC(VDEC_CPB0)),
#endif

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio1_buffer, MEM_DESC(AUDIO1)),
#endif

#ifdef INCLUDE_KDRV_DEMOD
    LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),
#endif

#ifdef INCLUDE_KDRV_TE
    LX_MEMCFG_ENTRY_EX(gMemCfgTE, MEM_DESC(TE)),
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),
#endif

#ifdef INCLUDE_KDRV_HDMI20
    LX_MEMCFG_ENTRY_EX(gMemCfgHdmiFec[0], MEM_DESC(HDMI_FEC)),
    LX_MEMCFG_ENTRY_EX(gMemCfgEsm[0], MEM_DESC(ESM_CODE)),
    LX_MEMCFG_ENTRY_EX(gMemCfgEsm[1], MEM_DESC(ESM_DATA)),
#endif

    LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),

#ifdef INCLUDE_KDRV_FBDEV
    LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),
#endif

#ifdef INCLUDE_KDRV_GFX
    LX_MEMCFG_ENTRY_EX(gfx_surf0, MEM_DESC(GFX0)),
#endif

#ifdef INCLUDE_KDRV_OVI
    LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[4], MEM_DESC(TCON)),
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

    LX_MEMCFG_ENTRY_EX(npu0_buffer, MEM_DESC(NPU0)),

    LX_MEMCFG_ENTRY_EX(debug1, MEM_DESC(DEBUG1)),

    //-----------------------------------------------------------------------------------
    // M2 SECURE MEM GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M2_DEV]),
    LX_MEMCFG_ENTRY(__m2_s_mem_grp),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m2_pqe_svp, MEM_DESC(PQE2_SVP)),
#endif

    //-----------------------------------------------------------------------------------
    // M2 NON-SECURE MEM GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m2_ns_mem_grp),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m2_pqe_nsv, MEM_DESC(PQE2_NSV)),
    LX_MEMCFG_ENTRY_EX(g_m2_pqe_usr, MEM_DESC(PQE2_USR)),
#endif

    LX_MEMCFG_ENTRY_EX(npu1_buffer, MEM_DESC(NPU1)),

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio_lnx_buffer, MEM_DESC(AUDIO_LNX)),
#endif

    LX_MEMCFG_ENTRY_EX(debug2, MEM_DESC(DEBUG2)),

    //-----------------------------------------------------------------------------------
    // SYS MEM GROUP
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_SYS_DEV]),
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
        if (mem_desc[i].flag == MEMCFG_DESC_FLAG_CMA)
        {
            if (mem_desc[i].alias && check_force_hma_pool(mem_desc[i].alias))
            {
                mem_desc[i].flag = MEMCFG_DESC_FLAG_NO_CMA;
                printk("force_hma_pool: %s pool is set to hma pool by user\n", mem_desc[i].alias);
            }
        }
    }
}



static void BASE_PLT_SetupMemLayout(void)
{
    printk("configure O24(%2X) kdriver memory\n", lx_chip_rev() & 0xff);

    gMemCfgHdr[DDR_RGN_BWB_DEV].base = select_mem_value(CAT0_RGN_BWB_BASE, CAT1_RGN_BWB_BASE, CAT2_RGN_BWB_BASE);
    gMemCfgHdr[DDR_RGN_M0_DEV].base = select_mem_value(CAT0_RGN_M0_BASE, CAT1_RGN_M0_BASE, CAT2_RGN_M0_BASE);
    gMemCfgHdr[DDR_RGN_M1_DEV].base = select_mem_value(CAT0_RGN_M1_BASE, CAT1_RGN_M1_BASE, CAT2_RGN_M1_BASE);
    gMemCfgHdr[DDR_RGN_M2_DEV].base = select_mem_value(CAT0_RGN_M2_BASE, CAT1_RGN_M2_BASE, CAT2_RGN_M2_BASE);
    gMemCfgHdr[DDR_RGN_SYS_DEV].base = select_mem_value(CAT0_RGN_SYS_BASE, CAT1_RGN_SYS_BASE, CAT2_RGN_SYS_BASE);

    gMemCfgHdr[DDR_RGN_BWB_DEV].size = select_mem_value(CAT0_RGN_BWB_SZ, CAT1_RGN_BWB_SZ, CAT2_RGN_BWB_SZ);
    gMemCfgHdr[DDR_RGN_M0_DEV].size = select_mem_value(CAT0_RGN_M0_SZ, CAT1_RGN_M0_SZ, CAT2_RGN_M0_SZ);
    gMemCfgHdr[DDR_RGN_M1_DEV].size = select_mem_value(CAT0_RGN_M1_SZ, CAT1_RGN_M1_SZ, CAT2_RGN_M1_SZ);
    gMemCfgHdr[DDR_RGN_M2_DEV].size = select_mem_value(CAT0_RGN_M1_SZ, CAT1_RGN_M1_SZ, CAT2_RGN_M2_SZ);
    gMemCfgHdr[DDR_RGN_SYS_DEV].size = select_mem_value(CAT0_RGN_SYS_SZ, CAT1_RGN_SYS_SZ, CAT2_RGN_SYS_SZ);

    BASE_PLT_SetupCommon();

    g_mem_desc_table = select_mem_value(g_mem_desc_table_cat0, g_mem_desc_table_cat0, g_mem_desc_table_cat2);
}

static void BASE_PLT_SetupCommon(void)
{
    /* setup group memcfg */
    __m0_s_mem_grp.base = gMemCfgHdr[DDR_RGN_M0_DEV].base;
    __m0_ns_mem_grp.base = __m0_s_mem_grp.base + select_mem_value(CAT0_GRP_M0_S_MEM_SZ, CAT1_GRP_M0_S_MEM_SZ,
                           CAT2_GRP_M0_S_MEM_SZ);
    __m1_s_mem_grp.base = gMemCfgHdr[DDR_RGN_M1_DEV].base;
    __m1_ns_mem_grp.base = __m1_s_mem_grp.base + select_mem_value(CAT0_GRP_M1_S_MEM_SZ, CAT1_GRP_M1_S_MEM_SZ,
                           CAT2_GRP_M1_S_MEM_SZ);
    __m2_s_mem_grp.base = gMemCfgHdr[DDR_RGN_M2_DEV].base;
    __m2_ns_mem_grp.base = __m2_s_mem_grp.base + select_mem_value(CAT0_GRP_M2_S_MEM_SZ, CAT1_GRP_M2_S_MEM_SZ,
                           CAT2_GRP_M2_S_MEM_SZ);

#ifdef INCLUDE_KDRV_GFX
    gfx_surf0.size = select_mem_value(MOD_CAT0_SURFACE_SZ, MOD_CAT1_SURFACE_SZ, MOD_CAT2_SURFACE_SZ);
    gMemCfgGfx.surface[0].size  = gfx_surf0.size;
#endif

    vdec_vpb0.size  = select_mem_value(MOD_CAT0_VPB4K_SZ, MOD_CAT1_VPB4K_SZ, MOD_CAT2_VPB4K_SZ);
    vdec_vpb1.size  = select_mem_value(MOD_CAT0_VPB8K_SZ, MOD_CAT1_VPB8K_SZ, MOD_CAT2_VPB8K_SZ);
    vdec_cpb0.size  = select_mem_value(MOD_CAT0_VDEC_CPB_SZ, MOD_CAT1_VDEC_CPB_SZ, MOD_CAT2_VDEC_CPB_SZ);
    vdec_gen.size   = MOD_VDEC_GEN_SZ;

    audio0_buffer.size = select_mem_value(MOD_CAT0_AUDIO0_SZ, MOD_CAT1_AUDIO0_SZ, MOD_CAT2_AUDIO0_SZ);
    audio1_buffer.size = select_mem_value(MOD_CAT0_AUDIO1_SZ, MOD_CAT1_AUDIO1_SZ, MOD_CAT2_AUDIO1_SZ);
    audio_lnx_buffer.size = MOD_AUDIO_LNX_SZ;

    lne_buffer.size = MOD_LNE_SZ;
    npu0_buffer.size = MOD_NPU0_SZ;
    npu1_buffer.size = select_mem_value(MOD_CAT0_NPU1_SZ, MOD_CAT1_NPU1_SZ, MOD_CAT2_NPU1_SZ);

    pqe_bwb.size = select_mem_value(MOD_CAT0_PQE_BWB_SZ, MOD_CAT1_PQE_BWB_SZ, MOD_CAT2_PQE_BWB_SZ);

    // (2024/02/29) 4GB DDR 보드의 4K 모델에서는 vpb8k 를 CMA 가 되도록 조치한다.
    if (g_model_ctx.ddr_size == MODEL_OPT_4_0_GB && g_model_ctx.disp_model != MODEL_OPT_QUHD)
    {
        mem_desc[MEM_DESC_ID_VDEC_VPB1].flag = MEMCFG_DESC_FLAG_CMA;
    }
}

/* run the post memory layout after memory allocation
 *
 */
static void BASE_PLT_DoPostMemLayout(void)
{
    int i;
    int ret;

    // make debug0/1 use the all reserved memory region
    debug0.size = gMemCfgHdr[DDR_RGN_M0_DEV].base + gMemCfgHdr[DDR_RGN_M0_DEV].size - debug0.base;
    MEM_DESC_SIZE(DEBUG0) = debug0.size;

    debug1.size = gMemCfgHdr[DDR_RGN_M1_DEV].base + gMemCfgHdr[DDR_RGN_M1_DEV].size - debug1.base;
    MEM_DESC_SIZE(DEBUG1) = debug1.size;

    debug2.size = gMemCfgHdr[DDR_RGN_M2_DEV].base + gMemCfgHdr[DDR_RGN_M2_DEV].size - debug2.base;
    MEM_DESC_SIZE(DEBUG2) = debug2.size;

    printk("\n");
    printk("++ debug size tuned. debug0=0x%08x, debug1=0x%08x, debug2=0x%08x\n", debug0.size, debug1.size, debug2.size);
    printk("\n");

    /* print tuned memory layout for debug */
    if (memcfg_debug)
    {
        extern void BASE_DEVMEM_DumpMemCfg(struct seq_file * m, UINT32 opt);
        BASE_DEVMEM_DumpMemCfg(NULL, 0x0);
    }

    /* if memory region is set to NO_CMA, get device region from kernel to device driver with help of HMA */
    printk("\n++ memory pool registeration ++\n");

    for (i = 0; i < MEM_DESC_ID_MAX; i++)
    {
        switch (mem_desc[i].flag)
        {
            case MEMCFG_DESC_FLAG_NO_CMA:
            {
                if (mem_desc[i].m.base != 0x0 && mem_desc[i].m.size != 0x0)
                {
                    ret = hma_pool_register_type(mem_desc[i].m.name, mem_desc[i].m.base, mem_desc[i].m.size, CMA_POOL);

                    if (ret == 0)
                    {
                        printk("(x) CMA(%-15s %3dM@0x%08x) HMA\n", mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
                        hma_alloc(mem_desc[i].m.name, mem_desc[i].m.size, 1 << 12);
                    }
                    else
                    {
                        printk("(?) CMA(%-15s %3dM@0x%08x) register error\n", mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
                    }
                }
                else
                {
                    printk("(x) CMA(%-15s %3dM@0x%08x) ignored\n", mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
                }
            }
            break;

            case MEMCFG_DESC_FLAG_CMA:
            {
                /* do nothing. each device will create its own CMA allocator */
                printk("(o) CMA(%-15s %3dM@0x%08x) CMA\n", mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
            }
            break;

            default:
            {
                /* do nothing. this is BSP dedicated area */
                printk("(/) CMA(%-15s %3dM@0x%08x) skip\n", mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
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
            const char* name;
            int mem_desc_id;
        }
        vdec_mem_desc[] =
        {
            { "vpb",            MEM_DESC_ID_VDEC_VPB0},
            { "vpb8k",          MEM_DESC_ID_VDEC_VPB1},
            { "cpb",            MEM_DESC_ID_VDEC_CPB0},
            { "vdec",           MEM_DESC_ID_VDEC_GEN},

            //{ "venc0",        MEM_DESC_ID_VENC},
            //{ "venc1",        MEM_DESC_ID_VENC_S},

            { "debug0",         MEM_DESC_ID_DEBUG0},
            { "debug1",         MEM_DESC_ID_DEBUG1},
            { "debug2",         MEM_DESC_ID_DEBUG2},

            { "audio_s_mem",    MEM_DESC_ID_AUDIO0},
            { "audio_ns_mem",   MEM_DESC_ID_AUDIO1},

            { "audio_lnx",      MEM_DESC_ID_AUDIO_LNX},

            { "surface",        MEM_DESC_ID_GFX0},

            { "pqe-lne",        MEM_DESC_ID_LNE},
            { "npu0",           MEM_DESC_ID_NPU0},
            { "npu1",           MEM_DESC_ID_NPU1},

            {"pqe-bwb",         MEM_DESC_ID_PQE_BWB},
        };

        int a;

        for (a = 0; a < ARRAY_SIZE(vdec_mem_desc); a++)
        {
            UINT32 base;
            const char* name;
            int size;
            int pool_type;

#define MEM_DESC_BASE(n)        (mem_desc[MEM_DESC_ID_##n].m.base)

            name = vdec_mem_desc[a].name;
            base = mem_desc[ vdec_mem_desc[a].mem_desc_id ].m.base;
            size = mem_desc[ vdec_mem_desc[a].mem_desc_id ].m.size;
            pool_type  = (mem_desc[ vdec_mem_desc[a].mem_desc_id ].flag == MEMCFG_DESC_FLAG_CMA) ? CMA_POOL : HMA_POOL;

            if (base == 0 || size == 0)
            {
                printk("---(%16s), %3dM@0x%08x, none\n", name, size >> 20, base);
                continue;
            }

            ret = hma_pool_register_type(name, base, size, pool_type);

            if (ret == 0)
            {
                printk("cma(%16s), %3dM@0x%08x, %s pool\n", name, size >> 20, base, (pool_type == CMA_POOL) ? "CMA" : "HMA");
            }
            else
            {
                printk("cannot register %s pool\n", name);
                break;
            }
        }
    }
    printk("\n");

    if (vdec_vpb1.size)
    {
        hma_pool_fallback("vpb", "vpb8k");  // redirect vpb to vpb8k if out of memory
    }
    else if (vdec_cpb0.size)
    {
        hma_pool_fallback("vpb", "cpb");  // take insurance to support multiview
    }
    else
    {
        printk("-w- no fallbacks for vpb memory\n");
    }

    if (pqe_bwb.size)
    {
        hma_pool_alias("vdec_shared", "pqe-bwb");   // access pqe-bwb through vdec_shared
    }
    else if (vdec_vpb1.size)
    {
        hma_pool_alias("pqe-bwb", "vpb8k");         // access vpb8k through pqe-bwb
        hma_pool_alias("vdec_shared", "vpb8k");     // access vpb8k through vdec_shared
    }
    else
    {
        printk("-e- no alias for pqe-bwb/vdec_shared\n");
    }

    if (vdec_cpb0.size)
    {
        printk("making hma_alias to cpb\n");

        hma_pool_alias("cpb2", "cpb");      // access cpb through "cpb2"
        hma_pool_alias("photofb", "cpb");   // access cpb through "photofb"
        hma_pool_alias("venc0", "cpb");     // access cpb through "venc0"
    }
    else if (vdec_vpb1.size)
    {
        printk("making hma_alias to vpb8k\n");

        hma_pool_alias("cpb", "vpb8k");      // access vpb8k through "cpb"
        hma_pool_alias("cpb2", "vpb8k");     // access vpb8k through "cpb2"
        hma_pool_alias("photofb", "vpb8k");  // access vpb8k through "photofb"
        hma_pool_alias("venc0", "vpb8k");    // access vpb8k through "venc0"
    }
    else
    {
        printk("making hma_alias to vpb\n");

        hma_pool_alias("cpb", "vpb");       // access vpb through "cpb2"
        hma_pool_alias("cpb2", "vpb");      // access vpb through "cpb2"
        hma_pool_alias("photofb", "vpb");   // access vpb through "photofb"
        hma_pool_alias("venc0", "vpb");     // access vpb through "venc0"
    }

    hma_pool_alias("dpb", "vpb");       // access vpb through "dpb" for legacy interface
    hma_pool_alias("venc1", "vpb");     // access vpb through "venc1"

    hma_pool_alias("mtest-ddr0", "debug0"); // access debug0 through mtest-ddr0
    hma_pool_alias("mtest-ddr1", "debug1"); // access debug1 through mtest-ddr1
    hma_pool_alias("mtest-ddr2", "debug2"); // access debug2 through mtest-ddr2

    hma_pool_alias("de-dbg-m0", "debug0");  // access debug0 through de-dbg-m0
    hma_pool_alias("de-dbg-m1", "debug1");  // access debug1 through de-dbg-m1
    hma_pool_alias("de-dbg-m2", "debug2");  // access debug2 through de-dbg-m2

    // SLT 보드는 실제 DDR 용량과 상관없이 3.5GB (8K 지원) 메모리맵 설정을 하도록 한다.
    if (g_model_ctx.board == MODEL_OPT_SLT_BOARD)
    {
        printk("SLT board uses 3.5GB memory map. ddr_size changed from %d to %d\n",
               g_model_ctx.ddr_size, MODEL_OPT_3_5_GB);

        g_model_ctx.ddr_size = MODEL_OPT_3_5_GB;
    }

    hma_pool_alias("surface_ext", "debug0");// access debug0 through surface_ext

    hma_pool_alias("audio_buffer", "audio_ns_mem"); // access audio_buffer0 through audio_buffer
    hma_pool_alias("audio_buffer0", "audio_ns_mem");  // access audio_ns_mem through audio_buffer0

    // see http://clm.lge.com/issue/browse/SICDTV-13640
    // audio fw 의 src 주소가 0x94e08000 이면 audio fw load fail 남
    // 추후 분석 필요
    //hma_pool_alias("audio_fw_bin", "debug1");  // access debug1 through audio_fw_bin
    hma_pool_alias("audio_dump", "debug1");  // access debug1 through audio_dump

    hma_pool_alias("npu0", "npu");     // access npu through "npu0"

    // make "lne_buffer" within LNE memcfg
    /* lne_buffer.base ~ 4KB are reserved */
    ret = hma_pool_register_type(lne_buffer.name, lne_buffer.base + (4 << 10),
                                 lne_buffer.size - (4 << 10), HMA_POOL);

    if (ret < 0)
        printk(KERN_ERR "hma_pool_register_type(\"%s\") failed. %d\n", lne_buffer.name, ret);

    /* TODO: add code to debug memory if necessary */

}

/** main function for kdriver platform initialization
 *
 *  this function is called from base_drv.c after core initialization, chip rev detection
 *  (including chip probe), debug initialization and pre-initialization of each driver.
 *
 */
void    BASE_PLT_Init(void)
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
void  BASE_PLT_Probe(UINT32* plt, UINT32* board_opt)
{
    int     i;

    UINT32  hdmi_tx_output = 0;
    UINT32  plt_val = 0x0;
    UINT32  board_opt_val = 0x0;

    char    optstr[80];
    const char* pioneer_board_fmtstr[2] = {"pioneer.board=%s", "pioneer.boardopts=%s"};

    /* check HDMI Tx environment */
    if (RET_OK == OS_ScanKernelCmdline("disp=%s", optstr))
    {
        if (!strncmp(optstr, "hdmi", 4))
        {
            hdmi_tx_output = 1;
        }
    }

    /* check webOS modelopt & hwopt */
    if (webos_hwopt_probe)
    {
        char modelopt_txt[32];
        char hwopt_txt[32];

        memset(modelopt_txt, 0x0, 32);
        memset(hwopt_txt, 0x0, 32);

#if 0

        if (RET_OK == OS_ScanKernelCmdline("modelopt=%s", modelopt_txt))
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
        if (RET_OK == OS_ScanKernelCmdline("hwopt=%s", hwopt_txt))
        {
            /* 0: HD(1366x768)  1: FHD(1920x1080)  2: UHD(3840x2160) 3: QUHD(7680x4320)... */
            switch (hwopt_txt[3])
            {
                case '0':
                case '1': g_model_ctx.disp_model = MODEL_OPT_FHD; break;

                case '3': g_model_ctx.disp_model = MODEL_OPT_QUHD; break;

                default:  g_model_ctx.disp_model = MODEL_OPT_UHD; break;
            }

            /* 0: NO_FRC, 1: INT_FRC, others: EXT_FRCs.
             * I will treat NO_FRC as INT_FRC for easy maintenance because there is never "NO_FRC" configuration.
             * raxis.lim (2019/01/16)
             * there is nothing special to identify whether 4K or 8K TV. just use if there is EXT_FRC or not
             */
            switch (hwopt_txt[17])
            {
                case '0':
                case '1': g_model_ctx.frc_conn = MODEL_OPT_INT_FRC; break;

                default:  g_model_ctx.frc_conn = MODEL_OPT_EXT_FRC; g_model_ctx.disp_model = MODEL_OPT_QUHD; break;
            }

            /* 2: 2K, 4: 4K */
            switch (hwopt_txt[14])
            {
                case '4': g_model_ctx.graphic = MODEL_OPT_4K_GRAPHIC; break;

                default:  g_model_ctx.graphic = MODEL_OPT_2K_GRAPHIC; break;
            }

            /* 0: EPI, 1:LVDS, 2:Vx1 etc */
            switch (hwopt_txt[2])
            {
                case '0': g_model_ctx.panel_if = MODEL_OPT_PANEL_IF_EPI; break;
defauilt: g_model_ctx.panel_if = MODEL_OPT_PANEL_IF_OTHERS; break;
            }

            /* 0: 60Hz, 1: 120Hz */
            switch (hwopt_txt[4])
            {
                case '0': g_model_ctx.frc_hz    = MODEL_OPT_60HZ; break;

                case '1':
                default:  g_model_ctx.frc_hz    = MODEL_OPT_120HZ; break;
            }

            /* 5: 2.5GB, 11: 3.5GB */
            switch (hwopt_txt[11])
            {
                case 'b': g_model_ctx.ddr_size = MODEL_OPT_3_5_GB; break;

                case '9': g_model_ctx.ddr_size = MODEL_OPT_4_0_GB; break;

                default:  g_model_ctx.ddr_size = MODEL_OPT_2_5_GB; break;
            }
        }
    }

    if (pioneer_hwopt_probe)
    {
        /* check additional configuration for the test only */
        for (i = 0; i < NELEMENTS(pioneer_board_fmtstr); i++)
        {
            if (RET_OK == OS_ScanKernelCmdline(pioneer_board_fmtstr[i], optstr))
            {
                char* tok, *sav_tok;
                char delim[] = ",\t\n";

                tok = simple_strtok(optstr, delim, &sav_tok);

                while (tok)
                {
                    if (!strncasecmp(tok, "2.5GB", 5))        g_model_ctx.ddr_size    = MODEL_OPT_2_5_GB;

                    if (!strncasecmp(tok, "3.5GB", 5))        g_model_ctx.ddr_size    = MODEL_OPT_3_5_GB;

                    if (!strncasecmp(tok, "4.0GB", 5))        g_model_ctx.ddr_size    = MODEL_OPT_4_0_GB;

                    if (!strncasecmp(tok, "FHD", 3))          g_model_ctx.disp_model  = MODEL_OPT_FHD;

                    if (!strncasecmp(tok, "UHD", 3))          g_model_ctx.disp_model  = MODEL_OPT_UHD;

                    if (!strncasecmp(tok, "QUHD", 4))         g_model_ctx.disp_model  = MODEL_OPT_QUHD;

                    if (!strncasecmp(tok, "STB", 3))          g_model_ctx.panel       = MODEL_OPT_PANEL_NONE;

                    if (!strncasecmp(tok, "LCD", 3))          g_model_ctx.panel       = MODEL_OPT_PANEL_LCD;

                    if (!strncasecmp(tok, "OLED", 4))         g_model_ctx.panel       = MODEL_OPT_PANEL_OLED;

                    if (!strncasecmp(tok, "EPI", 4))          g_model_ctx.panel       = MODEL_OPT_PANEL_IF_EPI;

                    if (!strncasecmp(tok, "60HZ", 4))         g_model_ctx.frc_hz      = MODEL_OPT_60HZ;

                    if (!strncasecmp(tok, "120HZ", 5))        g_model_ctx.frc_hz      = MODEL_OPT_120HZ;

                    if (!strncasecmp(tok, "2KOSD", 5))        g_model_ctx.graphic     = MODEL_OPT_2K_GRAPHIC;

                    if (!strncasecmp(tok, "4KOSD", 5))        g_model_ctx.graphic     = MODEL_OPT_4K_GRAPHIC;

                    if (!strncasecmp(tok, "USR0", 4))         g_model_ctx.usr0        = MODEL_OPT_USR;

                    if (!strncasecmp(tok, "USR1", 4))         g_model_ctx.usr1        = MODEL_OPT_USR;

                    if (!strncasecmp(tok, "USR2", 4))         g_model_ctx.usr2        = MODEL_OPT_USR;

                    if (!strncasecmp(tok, "USR3", 4))         g_model_ctx.usr3        = MODEL_OPT_USR;

                    if (!strncasecmp(tok, "SYS_BOARD", 9))    g_model_ctx.board       = MODEL_OPT_SYS_BOARD;

                    if (!strncasecmp(tok, "SLT_BOARD", 9))    g_model_ctx.board       = MODEL_OPT_SLT_BOARD;

                    if (!strncasecmp(tok, "FPGA_BOARD", 10))  g_model_ctx.board       = MODEL_OPT_FPGA_BOARD;

                    // 양산맵이 기본이며, SLT 테스트에 한정하여 SLT_MAP 으로 전환하도록 한다.
                    if (!strncasecmp(tok, "SLT_MAP", 7))      g_model_ctx.map = MODEL_OPT_SLT_MAP;

                    tok = simple_strtok(NULL, delim, &sav_tok);
                }
            }
        }
    }

    /* dump board option */
    printk("\n++ BOARD OPTION ++\n");
    printk("MODEL: %s\n", (g_model_ctx.disp_model == MODEL_OPT_QUHD) ? "QUHD" :
           (g_model_ctx.disp_model == MODEL_OPT_UHD) ?  "UHD" :
           (g_model_ctx.disp_model == MODEL_OPT_FHD) ?  "FHD" : "n/a");
    printk("SOC  : %s\n",       "O24(LG1214)");
    printk("DDR  : %s\n", (g_model_ctx.ddr_size == MODEL_OPT_4_0_GB) ? "4.0GB" :
           (g_model_ctx.ddr_size == MODEL_OPT_3_5_GB) ? "3.5GB" :
           (g_model_ctx.ddr_size == MODEL_OPT_2_5_GB) ? "2.5GB" : "n/a");
    printk("GFX  : %s\n", (g_model_ctx.graphic == MODEL_OPT_4K_GRAPHIC) ? "4K(3840x2160)" :
           (g_model_ctx.graphic == MODEL_OPT_2K_GRAPHIC) ? "2K(1920x1080)" : "n/a");
    printk("PANEL: %s\n", (g_model_ctx.panel == MODEL_OPT_PANEL_NONE) ? "NONE(STB)" :
           (g_model_ctx.panel == MODEL_OPT_PANEL_LCD) ?  "LCD/LED" :
           (g_model_ctx.panel == MODEL_OPT_PANEL_OLED) ? "OLED" : "n/a");
    printk("PANEL_IF: %s\n", (g_model_ctx.panel == MODEL_OPT_PANEL_IF_EPI) ? "EPI)" : "OTHERS");
    printk("FRC  : %s(%sHz)\n", (g_model_ctx.frc_conn == MODEL_OPT_EXT_FRC) ? "EXTERNAL" :
           (g_model_ctx.frc_conn == MODEL_OPT_INT_FRC) ? "INTERNAL" : "n/a",
           (g_model_ctx.frc_hz == MODEL_OPT_60HZ) ? "60" :
           (g_model_ctx.frc_hz == MODEL_OPT_120HZ) ? "120" : "n/a");

    printk("BOARD: %s\n",
           (g_model_ctx.board == MODEL_OPT_SYS_BOARD) ? "SYS_BOARD" :
           (g_model_ctx.board == MODEL_OPT_SLT_BOARD) ?  "SLT_BOARD" :
           (g_model_ctx.board == MODEL_OPT_FPGA_BOARD) ? "FPGA_BOARD" : "n/a");

    printk("MAP  : %s\n",
           (g_model_ctx.map == MODEL_OPT_SLT_MAP) ? "SLT_MAP" :
           (g_model_ctx.map == MODEL_OPT_PROD_MAP) ?  "PROUCTION_MAP" : "n/a");

    printk("HDMI : %s\n", (hdmi_tx_output) ? "HDMI Tx" : "None");

    printk("USR  : 0x%02x 0x%02x 0x%02x 0x%02x\n", g_model_ctx.usr0, g_model_ctx.usr1, g_model_ctx.usr2, g_model_ctx.usr3);

    /* make board_opt variable */
    if (g_model_ctx.usr0 == MODEL_OPT_USR) board_opt_val |= LX_BOARD_OPT_USR0;

    if (g_model_ctx.usr1 == MODEL_OPT_USR) board_opt_val |= LX_BOARD_OPT_USR1;

    if (g_model_ctx.usr2 == MODEL_OPT_USR) board_opt_val |= LX_BOARD_OPT_USR2;

    if (g_model_ctx.usr3 == MODEL_OPT_USR) board_opt_val |= LX_BOARD_OPT_USR3;

    switch (g_model_ctx.disp_model)
    {
        case MODEL_OPT_FHD:     plt_val = LX_CHIP_PLT_FHD; break;

        case MODEL_OPT_QUHD:    plt_val = LX_CHIP_PLT_QUHD; break;

        default:                plt_val = LX_CHIP_PLT_UHD; break;
    }

    switch (g_model_ctx.ddr_size)
    {
        case MODEL_OPT_3_5_GB: board_opt_val |= (LX_BOARD_OPT_DDR_3_5GB | LX_BOARD_OPT_ADV); break;

        case MODEL_OPT_2_5_GB: board_opt_val |= (LX_BOARD_OPT_DDR_2_5GB | LX_BOARD_OPT_ADV); break;

        default: /* none */ break;
    }

    switch (g_model_ctx.frc_conn)
    {
        case MODEL_OPT_INT_FRC:     board_opt_val |= LX_BOARD_OPT_INT_FRC; break;

        case MODEL_OPT_EXT_FRC:     board_opt_val |= LX_BOARD_OPT_EXT_FRC; break;

        default: /* none */ break;
    }

    switch (g_model_ctx.frc_hz)
    {
        case MODEL_OPT_60HZ:        board_opt_val |= LX_BOARD_OPT_DISP_60HZ; break;

        case MODEL_OPT_120HZ:       board_opt_val |= LX_BOARD_OPT_DISP_120HZ; break;

        default: /* none */ break;
    }

    switch (g_model_ctx.panel)
    {
        case MODEL_OPT_PANEL_NONE:  board_opt_val |= LX_BOARD_OPT_STBBOX; break;

        case MODEL_OPT_PANEL_LCD:   board_opt_val |= LX_BOARD_OPT_LCD;    break;

        case MODEL_OPT_PANEL_OLED:  board_opt_val |= LX_BOARD_OPT_OLED;   break;

        default: /* none */ break;
    }

    switch (g_model_ctx.panel_if)
    {
        case MODEL_OPT_PANEL_IF_EPI:  board_opt_val |= LX_BOARD_OPT_EPI; break;

        default: /* none */ break;
    }

    if (g_model_ctx.graphic == MODEL_OPT_4K_GRAPHIC) board_opt_val |= LX_BOARD_OPT_4K_GRAPHIC;

    if (g_model_ctx.usr0 == MODEL_OPT_USR) board_opt_val |= LX_BOARD_OPT_USR0;

    if (g_model_ctx.usr1 == MODEL_OPT_USR) board_opt_val |= LX_BOARD_OPT_USR1;

    if (g_model_ctx.usr2 == MODEL_OPT_USR) board_opt_val |= LX_BOARD_OPT_USR2;

    if (g_model_ctx.usr3 == MODEL_OPT_USR) board_opt_val |= LX_BOARD_OPT_USR3;

#ifdef BUILD_FEATURE_fpga
    board_opt_val |= LX_BOARD_OPT_FPGA;
#else
    board_opt_val |= LX_BOARD_OPT_SYSTEM;
#endif

    if (g_model_ctx.board == MODEL_OPT_SLT_BOARD)
    {
        board_opt_val |= LX_BOARD_OPT_SLT;
    }
    else
    {
        board_opt_val |= LX_BOARD_OPT_SYSTEM;
    }

    if (g_model_ctx.map == MODEL_OPT_SLT_MAP)
    {
        board_opt_val |= LX_BOARD_OPT_SLT_MAP;
    }

    *plt        = plt_val;
    *board_opt  = board_opt_val;
}

/** @} */
