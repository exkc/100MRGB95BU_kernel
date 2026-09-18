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

    main configuration for lg1k driver

    author      raxis.lim@lge.com
    version     1.0
    date        2019.02.29

    @addtogroup lg1k_base
    @{
*/

//-----------------------------------------------------------------------------------------
// Control Constants
//-----------------------------------------------------------------------------------------
#define PIONEER_PROBE_CFG           1   /* parse PIONEER toolopts */
#define WEBOS_PROBE_CFG             1   /* parse webOS toolopts */

//-----------------------------------------------------------------------------------------
// File Inclusion
//-----------------------------------------------------------------------------------------
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
#include "platform_slt_mem_map.h"
#include "platform_fhd_mem_map.h"

//-----------------------------------------------------------------------------------------
// Constant Definitions
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Macro Definitions
//-----------------------------------------------------------------------------------------
#define LX_MEMCFG_ENTRY(item)               { .name= _STR(item), .pM=(LX_MEMCFG_T*)&(item), .nM=sizeof(item)/sizeof(LX_MEMCFG_T) }
#define LX_MEMCFG_ENTRY_EX(item,alias)      { .name= _STR(item), .pM=(LX_MEMCFG_T*)&(item), .nM=sizeof(item)/sizeof(LX_MEMCFG_T), .flag=LX_MEMCFG_FLAG_ALIAS, .pAlias=&alias }
#define LX_MEMCFG_ENTRY_END                 { .name="Total", .pM=NULL, .nM=0}

#define __MEM_VALUE_SELECT(val_4k,val_8k)   ((UINT32)(g_model_ctx.disp_model==MODEL_OPT_UHD)? (val_4k):(val_8k))

#define __ASSERT(condition) \
do { \
    if (unlikely(!(condition)))\
    {\
        printk("WARNING: Assert Fail(%s)\n", #condition);\
        WARN_ON(1);\
    }\
} while(0)

//-----------------------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------------------
typedef enum
{
    DDR_RGN_M0_DEV = 0,
    DDR_RGN_EXT_DEV,
    DDR_RGN_MAX,
} DDR_RGN_T;

typedef struct
{
#define MEMCFG_DESC_FLAG_NONE       0x00000000  /* device such as SE/TZ should keep memory content from the booting stage */
#define MEMCFG_DESC_FLAG_CMA        0x4F434D41  /* device will manage dedicated memory according to its own policy. do nothing in platform_initializer */
#define MEMCFG_DESC_FLAG_NO_CMA     0x4E434D41  /* device requires the pre-allocated device memory even from CMA region */
    UINT32 flag;
    LX_MEMCFG_T m;
	const char* alias;
} LX_MEMCFG_DESC_T;

typedef enum
{
    MODEL_OPT_UHD = 0x0,
    MODEL_OPT_QUHD = 0x1,
    MODEL_OPT_FHD = 0x2,
    MODEL_OPT_HD = 0x3,

    MODEL_OPT_1_0_GB = 0x1, /* 1.0GB */
    MODEL_OPT_1_5_GB = 0x2, /* 1.5GB defualt value */
    MODEL_OPT_2_0_GB = 0x3, /* 2.0GB fufure use */

    MODEL_OPT_USR = 0x1,    /* enable USR option */

    MODEL_OPT_NO_FRC = 0x0,
    MODEL_OPT_INT_FRC = 0x1,    /* default value */
    MODEL_OPT_EXT_FRC = 0x2,

    MODEL_OPT_60HZ = 0x1,   /* default value */
    MODEL_OPT_120HZ = 0x2,

    MODEL_OPT_PANEL_NONE = 0x0, /* no panel = stbbox */
    MODEL_OPT_PANEL_LCD = 0x1,
    MODEL_OPT_PANEL_OLED = 0x2,

    MODEL_OPT_2K_GRAPHIC = 0x1, /* FHD graphics, default value */
    MODEL_OPT_HD_GRAPHIC = 0x2, /* HD graphics */

    MODEL_OPT_SYS_BOARD = 0x0,
    MODEL_OPT_SLT_BOARD = 0x1,  /* SLT board */
    MODEL_OPT_FPGA_BOARD = 0x2,

    MODEL_OPT_PROD_MAP = 0x0,   /* production memory map */
    MODEL_OPT_SLT_MAP = 0x1,    /* SLT memory map */
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
    MODEL_OPT_T graphic;
    MODEL_OPT_T board;
    MODEL_OPT_T map;

    MODEL_OPT_T usr0;
    MODEL_OPT_T usr1;   /* if defined, we try to setup test environment for 4K120 video decoder */
    MODEL_OPT_T usr2;
    MODEL_OPT_T usr3;
}
MODEL_OPT_CTX_T;

//-----------------------------------------------------------------------------------------
// External Function Prototype Declarations
//-----------------------------------------------------------------------------------------
extern char* simple_strtok(char* s, const char* delim, char** save_ptr);
extern int BASE_DEVMEM_InitDevMem(LX_MEMCFG_ENTRY_T* pEntry);

//-----------------------------------------------------------------------------------------
// External Variables
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Macro Definitions
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// global Variables
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Static Function Prototypes Declarations
//-----------------------------------------------------------------------------------------
static void BASE_PLT_ForceHmaPool(void);
static void BASE_PLT_SetupCommon(void);
static void BASE_PLT_SetupMemLayout(void);

static void BASE_PLT_SetupFHDCommon(void);
static void BASE_PLT_SetupFHDMemLayout(void);

static void BASE_PLT_SetupSLTCommon(void);
static void BASE_PLT_SetupSLTMemLayout(void);

//-----------------------------------------------------------------------------------------
// Static Variables
//-----------------------------------------------------------------------------------------
static int pioneer_hwopt_probe = PIONEER_PROBE_CFG; // TODO: set to 1 if bringup is completed
static int webos_hwopt_probe = WEBOS_PROBE_CFG; // TODO: set to 1 if bringup is completed
static int lne_buffer_memsz = 0;    // 동작 설정 필요

module_param(webos_hwopt_probe, int, 0644);
module_param(pioneer_hwopt_probe, int, 0644);
module_param(lne_buffer_memsz, int, 0644);

static MODEL_OPT_CTX_T g_model_ctx =
{
    .ddr_size = MODEL_OPT_1_5_GB,   /* 1.5GB by default */
    .disp_model = MODEL_OPT_UHD,    /* UHD by default */
    .frc_conn = MODEL_OPT_INT_FRC,  /* INT_FRC default */
    .frc_hz = MODEL_OPT_60HZ,   /* 60HZ   default */
    .panel = MODEL_OPT_PANEL_OLED,  //* LCD/LED default */
    .graphic = MODEL_OPT_2K_GRAPHIC,    /* 2K      default */
    .board = MODEL_OPT_SYS_BOARD,   /* SYS_BOARD default */
    .map = MODEL_OPT_PROD_MAP, /* PROD_MAP default */
    .usr0 = 0,
    .usr1 = 0,
    .usr2 = 0,
    .usr3 = 0
};

static LX_MEMCFG_T gMemCfgHdr[DDR_RGN_MAX] =
{
    {.name = "[header] M0", .base = 0x0, .size = 0},
    {.name = "[header] EXT", .base = 0x0, .size = 0},
};

/* group memcfg */
static LX_MEMCFG_T __m0_s_mem_grp = {.name = "m0_s_mem", .base = 0x0, .size = 0 };

static LX_MEMCFG_T __m0_ns_mem_grp = {.name = "m0_ns_mem", .base = 0x0, .size = 0 };

static LX_MEMCFG_T __m0_rsvd_mem_grp = {.name = "rsvd_mem)", .base = 0x0, .size = 0 };

static LX_MEMCFG_T __ext_sys_mem_grp = {.name = "ext_sys_mem", .base = 0x0, .size = 0 };

/* module memcfg */
static LX_MEMCFG_T vdec_vpb0 = {.name = "vdec(vpb)", .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_mpb0 = {.name = "vdec(mpb)", .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_gen = {.name = "vdec(vdec)", .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_mcu = {.name = "vdec(mcu)", .base = 0x0, .size = 0 };

static LX_MEMCFG_T audio0_buffer = {.name = "audio", .base = 0x0, .size = 0 };

static LX_MEMCFG_T lne_buffer = {.name = "lne_buffer", .base = 0x0, .size = 0 };

static LX_MEMCFG_T sys0 = {.name = "sys_ns", .base = 0x0, .size = __MB(1) };

static LX_MEMCFG_T debug0 = {.name = "debug(m0)", .base = 0x0, .size = M0_DEBUG_SZ };

#ifdef INCLUDE_KDRV_GFX
static LX_MEMCFG_T gfx_surf0 = {.name = "gfx(surface)", .base = 0x0, .size = 0 };
#endif

#ifdef INCLUDE_FHD_DUMMY
// see http://clm.lge.com/issue/browse/SICDTV-11799
static LX_MEMCFG_T fhd_dummy0 = {.name = "fhd_dummy0", .base = 0x0, .size = 0 };
static LX_MEMCFG_T fhd_dummy1 = {.name = "fhd_dummy1", .base = 0x0, .size = 0 };
static LX_MEMCFG_T fhd_dummy2 = {.name = "fhd_dummy2", .base = 0x0, .size = 0 };
static LX_MEMCFG_T fhd_dummy3 = {.name = "fhd_dummy3", .base = 0x0, .size = 0 };
#endif

/* region ID definition */
typedef enum
{
    MEM_DESC_ID_GFX0 = 0,
    MEM_DESC_ID_AUDIO0,
    MEM_DESC_ID_FBDEV,
    MEM_DESC_ID_TE,

    MEM_DESC_ID_VDEC_VPB0,
    MEM_DESC_ID_VDEC_MPB0,
    MEM_DESC_ID_VDEC_GEN,
    MEM_DESC_ID_VDEC_MCU,

    MEM_DESC_ID_DEMOD,
    MEM_DESC_ID_DEMOD_FW,

    MEM_DESC_ID_PQE0_SVP,   /* secure, pqe0 */
    MEM_DESC_ID_PQE0_NSV,   /* non-secure, pqe0 */
    MEM_DESC_ID_PQE0_USR,   /* non-secure, pqe0 */
    //MEM_DESC_ID_PQE0_DBG,             /* non-secure, pqe0 */

    MEM_DESC_ID_TCON,

    MEM_DESC_ID_VBI,
    MEM_DESC_ID_CVD,

    MEM_DESC_ID_HDMI_FEC,

    MEM_DESC_ID_LNE,

    MEM_DESC_ID_DEBUG0, /* DEBUG(M0) */
    MEM_DESC_ID_DEBUG1, /* DEBUG(M1) */
    MEM_DESC_ID_DUMMY,

    MEM_DESC_ID_SYS0,
    MEM_DESC_ID_SYS1,

    MEM_DESC_ID_FHD_DUMMY0,
    MEM_DESC_ID_FHD_DUMMY1,
    MEM_DESC_ID_FHD_DUMMY2,
    MEM_DESC_ID_FHD_DUMMY3,

    MEM_DESC_ID_MAX,
} MEM_DESC_ID_T;

/* memory alias list for CMA processing */
#define MEM_DESC(n)             (mem_desc[MEM_DESC_ID_##n].m)
#define MEM_DESC_NAME(n)        (mem_desc[MEM_DESC_ID_##n].m.name)
#define MEM_DESC_BASE(n)        (mem_desc[MEM_DESC_ID_##n].m.base)
#define MEM_DESC_SIZE(n)        (mem_desc[MEM_DESC_ID_##n].m.size)
#define MEM_DESC_FLAG(n)        (mem_desc[MEM_DESC_ID_##n].flag)

#define DEFINE_MEM_DESC(n,f,a)	[MEM_DESC_ID_##n] = { .m={ .name = #n"_hma", .base = 0x0, .size = 0 }, .flag=f, .alias=a }

static LX_MEMCFG_DESC_T mem_desc[MEM_DESC_ID_MAX] =
{
    DEFINE_MEM_DESC(GFX0, MEMCFG_DESC_FLAG_CMA, "surface"),    /* CMA */
    DEFINE_MEM_DESC(AUDIO0, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(FBDEV, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(VDEC_MCU, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(VDEC_GEN, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(VDEC_VPB0, MEMCFG_DESC_FLAG_CMA, "vcma"),   /* CMA */
    DEFINE_MEM_DESC(VDEC_MPB0, MEMCFG_DESC_FLAG_CMA, "mpb"),   /* CMA */

    DEFINE_MEM_DESC(TE, MEMCFG_DESC_FLAG_CMA, NULL),  /* CMA */

    DEFINE_MEM_DESC(DEMOD, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(DEMOD_FW, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(PQE0_SVP, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(PQE0_NSV, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(PQE0_USR, MEMCFG_DESC_FLAG_CMA, NULL),

    DEFINE_MEM_DESC(TCON, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(VBI, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    //DEFINE_MEM_DESC(CVD, MEMCFG_DESC_FLAG_CMA, NULL),

    DEFINE_MEM_DESC(HDMI_FEC, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(LNE, MEMCFG_DESC_FLAG_NO_CMA, NULL),

    DEFINE_MEM_DESC(SYS0, MEMCFG_DESC_FLAG_NONE, NULL),
    DEFINE_MEM_DESC(SYS1, MEMCFG_DESC_FLAG_NONE, NULL),

    DEFINE_MEM_DESC(DEBUG0, MEMCFG_DESC_FLAG_CMA, "debug0"),  /* CMA */
    DEFINE_MEM_DESC(DEBUG1, MEMCFG_DESC_FLAG_CMA, "debug1"),  /* CMA */

#ifdef INCLUDE_FHD_DUMMY
    DEFINE_MEM_DESC(FHD_DUMMY0, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(FHD_DUMMY1, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(FHD_DUMMY2, MEMCFG_DESC_FLAG_NO_CMA, NULL),
    DEFINE_MEM_DESC(FHD_DUMMY3, MEMCFG_DESC_FLAG_NO_CMA, NULL),
#endif

    DEFINE_MEM_DESC(DUMMY, MEMCFG_DESC_FLAG_NO_CMA, NULL),
};

//==========================================================================================
//  Global Memory Configuration data base
//==========================================================================================
static LX_MEMCFG_ENTRY_T* g_mem_desc_table;


// UHD model /w 1.5GB DDR
static LX_MEMCFG_ENTRY_T g_mem_desc_table_UHD[] =
{
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),

    //-----------------------------------------------------------------------------------
    // secure mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_s_mem_grp),
    LX_MEMCFG_ENTRY_EX(vdec_vpb0, MEM_DESC(VDEC_VPB0)),
    LX_MEMCFG_ENTRY_EX(vdec_mcu, MEM_DESC(VDEC_MCU)),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_svp, MEM_DESC(PQE0_SVP)),
#endif

    //-----------------------------------------------------------------------------------
    // non-secure mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_ns_mem_grp),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_nsv, MEM_DESC(PQE0_NSV)),
#endif

#ifdef INCLUDE_KDRV_VDEC
    LX_MEMCFG_ENTRY_EX(vdec_gen, MEM_DESC(VDEC_GEN)),
    LX_MEMCFG_ENTRY_EX(vdec_mpb0, MEM_DESC(VDEC_MPB0)),
#endif

#ifdef INCLUDE_KDRV_OVI
    LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[3], MEM_DESC(TCON)),
#endif

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_usr, MEM_DESC(PQE0_USR)),
#endif

    LX_MEMCFG_ENTRY_EX(gMemCfgTE, MEM_DESC(TE)),

#ifdef INCLUDE_KDRV_DEMOD
    LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),
#endif

#ifdef INCLUDE_KDRV_AFE
    //  LX_MEMCFG_ENTRY_EX(gCvdMemCfg,  MEM_DESC(CVD)),
#endif

#ifdef INCLUDE_KDRV_GFX
    LX_MEMCFG_ENTRY_EX(gfx_surf0, MEM_DESC(GFX0)),
#endif

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio0_buffer, MEM_DESC(AUDIO0)),
#endif

#ifdef INCLUDE_KDRV_FBDEV
    LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),
#endif

    LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),

    //-----------------------------------------------------------------------------------
    // non-secure RSVD mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_rsvd_mem_grp),
    LX_MEMCFG_ENTRY_EX(debug0, MEM_DESC(DEBUG0)),

    //-----------------------------------------------------------------------------------
    // ext sys mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_EXT_DEV]),

    LX_MEMCFG_ENTRY(__ext_sys_mem_grp),
    LX_MEMCFG_ENTRY_EX(sys0, MEM_DESC(SYS0)),

    LX_MEMCFG_ENTRY_END
};

// HD/FHD model /w 1.5GB DDR
static LX_MEMCFG_ENTRY_T g_mem_desc_table_FHD[] =
{
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),

    //-----------------------------------------------------------------------------------
    // secure mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_s_mem_grp),

    LX_MEMCFG_ENTRY_EX(vdec_vpb0, MEM_DESC(VDEC_VPB0)),
#ifdef INCLUDE_FHD_DUMMY
    LX_MEMCFG_ENTRY_EX(fhd_dummy0, MEM_DESC(FHD_DUMMY0)),
    LX_MEMCFG_ENTRY_EX(fhd_dummy1, MEM_DESC(FHD_DUMMY1)),
#endif
    LX_MEMCFG_ENTRY_EX(vdec_mcu, MEM_DESC(VDEC_MCU)),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_svp, MEM_DESC(PQE0_SVP)),
#endif
    //-----------------------------------------------------------------------------------
    // non-secure mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_ns_mem_grp),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_nsv, MEM_DESC(PQE0_NSV)),
#endif

#ifdef INCLUDE_KDRV_VDEC
    LX_MEMCFG_ENTRY_EX(vdec_gen, MEM_DESC(VDEC_GEN)),
    LX_MEMCFG_ENTRY_EX(vdec_mpb0, MEM_DESC(VDEC_MPB0)),
#endif

#ifdef INCLUDE_KDRV_OVI
    LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[2], MEM_DESC(TCON)),
#endif

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_usr, MEM_DESC(PQE0_USR)),
#endif

#ifdef INCLUDE_KDRV_GFX
    LX_MEMCFG_ENTRY_EX(gfx_surf0, MEM_DESC(GFX0)),
#endif

#ifdef INCLUDE_FHD_DUMMY
    LX_MEMCFG_ENTRY_EX(fhd_dummy2, MEM_DESC(FHD_DUMMY2)),
#endif

    LX_MEMCFG_ENTRY_EX(gMemCfgTE, MEM_DESC(TE)),

#ifdef INCLUDE_KDRV_DEMOD
    LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),
#endif

#ifdef INCLUDE_KDRV_AFE
    //  LX_MEMCFG_ENTRY_EX(gCvdMemCfg,  MEM_DESC(CVD)),
#endif

#ifdef INCLUDE_FHD_DUMMY
    LX_MEMCFG_ENTRY_EX(fhd_dummy3, MEM_DESC(FHD_DUMMY3)),
#endif

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio0_buffer, MEM_DESC(AUDIO0)),
#endif

#ifdef INCLUDE_KDRV_FBDEV
    LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),
#endif

    LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),

    //-----------------------------------------------------------------------------------
    // non-secure RSVD mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_rsvd_mem_grp),
    LX_MEMCFG_ENTRY_EX(debug0, MEM_DESC(DEBUG0)),

    //-----------------------------------------------------------------------------------
    // ext sys mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_EXT_DEV]),

    LX_MEMCFG_ENTRY(__ext_sys_mem_grp),
    LX_MEMCFG_ENTRY_EX(sys0, MEM_DESC(SYS0)),

    LX_MEMCFG_ENTRY_END
};

// SLT test platform /w 1.5GB DDR
static LX_MEMCFG_ENTRY_T g_mem_desc_table_SLT[] =
{
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_M0_DEV]),

    //-----------------------------------------------------------------------------------
    // secure mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_s_mem_grp),
    LX_MEMCFG_ENTRY_EX(vdec_vpb0, MEM_DESC(VDEC_VPB0)),
    LX_MEMCFG_ENTRY_EX(vdec_mcu, MEM_DESC(VDEC_MCU)),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_svp, MEM_DESC(PQE0_SVP)),
#endif

    //-----------------------------------------------------------------------------------
    // non-secure mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_ns_mem_grp),

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_nsv, MEM_DESC(PQE0_NSV)),
#endif

#ifdef INCLUDE_KDRV_VDEC
    LX_MEMCFG_ENTRY_EX(vdec_gen, MEM_DESC(VDEC_GEN)),
    LX_MEMCFG_ENTRY_EX(vdec_mpb0, MEM_DESC(VDEC_MPB0)),
#endif

#ifdef INCLUDE_KDRV_DE
    LX_MEMCFG_ENTRY_EX(g_m0_pqe_usr, MEM_DESC(PQE0_USR)),
#endif

#ifdef INCLUDE_KDRV_OVI
    LX_MEMCFG_ENTRY_EX(gMemCfgOviTcon[3], MEM_DESC(TCON)),
#endif

    LX_MEMCFG_ENTRY_EX(gMemCfgTE, MEM_DESC(TE)),

#ifdef INCLUDE_KDRV_DEMOD
    LX_MEMCFG_ENTRY_EX(gMemCfgDEMOD_FW, MEM_DESC(DEMOD_FW)),
#endif

#ifdef INCLUDE_KDRV_VBI
    LX_MEMCFG_ENTRY_EX(gstBufMemCfgVBIRev[0], MEM_DESC(VBI)),
#endif

#ifdef INCLUDE_KDRV_AFE
    //  LX_MEMCFG_ENTRY_EX(gCvdMemCfg,  MEM_DESC(CVD)),
#endif

#ifdef INCLUDE_KDRV_GFX
    LX_MEMCFG_ENTRY_EX(gfx_surf0, MEM_DESC(GFX0)),
#endif

#ifdef INCLUDE_KDRV_AUDIO
    LX_MEMCFG_ENTRY_EX(audio0_buffer, MEM_DESC(AUDIO0)),
#endif

#ifdef INCLUDE_KDRV_FBDEV
    LX_MEMCFG_ENTRY_EX(gMemCfgFBBuf, MEM_DESC(FBDEV)),
#endif

    LX_MEMCFG_ENTRY_EX(lne_buffer, MEM_DESC(LNE)),

    //-----------------------------------------------------------------------------------
    // non-secure RSVD mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(__m0_rsvd_mem_grp),
    LX_MEMCFG_ENTRY_EX(debug0, MEM_DESC(DEBUG0)),

    //-----------------------------------------------------------------------------------
    // ext sys mem group
    //-----------------------------------------------------------------------------------
    LX_MEMCFG_ENTRY(gMemCfgHdr[DDR_RGN_EXT_DEV]),

    LX_MEMCFG_ENTRY(__ext_sys_mem_grp),
    LX_MEMCFG_ENTRY_EX(sys0, MEM_DESC(SYS0)),

    LX_MEMCFG_ENTRY_END
};

//==========================================================================================
// Implementation Group
//==========================================================================================
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

// BASE_PLT_SetupMemLayout 와 중복적인 부분이 있으나, side effect 방지 목적으로 전체 분리함
static void BASE_PLT_SetupSLTMemLayout(void)
{
    gMemCfgHdr[DDR_RGN_M0_DEV].base = SLT_M0_1_5_GB_DEV_BASE;
    gMemCfgHdr[DDR_RGN_M0_DEV].size = SLT_M0_1_5_GB_DEV_SZ;

    gMemCfgHdr[DDR_RGN_EXT_DEV].base = SLT_EXT_DEV_BASE;
    gMemCfgHdr[DDR_RGN_EXT_DEV].size = SLT_EXT_DEV_SZ;

    BASE_PLT_SetupSLTCommon();

    g_mem_desc_table = g_mem_desc_table_SLT;
}

// BASE_PLT_SetupCommon 와 중복적인 부분이 많으나, side effect 방지 목적으로 전체 분리함
static void BASE_PLT_SetupSLTCommon(void)
{
    // setup group memcfg
    __m0_s_mem_grp.base = gMemCfgHdr[DDR_RGN_M0_DEV].base;
    __m0_ns_mem_grp.base = __m0_s_mem_grp.base + SLT_M0_S_MEM0_GRP_SZ + SLT_M0_S_MEM1_GRP_SZ;
    __ext_sys_mem_grp.base = gMemCfgHdr[DDR_RGN_EXT_DEV].base;

    // setup gfx
#ifdef INCLUDE_KDRV_GFX
    gfx_surf0.size = SLT_GFXOSD_SURFACE_SZ;
    gMemCfgGfx.surface[0].size = gfx_surf0.size;
#endif

    // setup vdec
    vdec_vpb0.size = SLT_UHD_VPB4K_SZ;
    vdec_mpb0.size = VDEC_MPB_SZ;
    vdec_gen.size = VDEC_GEN_SZ;
    vdec_mcu.size = VDEC_MCU_SZ;

    audio0_buffer.size = AUDIO_BUFFER_SZ;

    // setup LNE
    lne_buffer.size = SLT_LNE_BUFFER_SZ;
}

// BASE_PLT_SetupCommon 와 중복적인 부분이 많으나, side effect 방지 목적으로 전체 분리함
static void BASE_PLT_SetupFHDMemLayout(void)
{
    if (g_model_ctx.ddr_size == MODEL_OPT_1_5_GB)
    {
        gMemCfgHdr[DDR_RGN_M0_DEV].base = FHD_M0_1_5_GB_DEV_BASE;
        gMemCfgHdr[DDR_RGN_M0_DEV].size = FHD_M0_1_5_GB_DEV_SZ;
    }
    else // 1.0GB
    {
        gMemCfgHdr[DDR_RGN_M0_DEV].base = FHD_M0_1_0_GB_DEV_BASE;
        gMemCfgHdr[DDR_RGN_M0_DEV].size = FHD_M0_1_0_GB_DEV_SZ;
    }

    gMemCfgHdr[DDR_RGN_EXT_DEV].base = EXT_DEV_BASE;
    gMemCfgHdr[DDR_RGN_EXT_DEV].size = EXT_DEV_SZ;

    BASE_PLT_SetupFHDCommon();

    g_mem_desc_table = g_mem_desc_table_FHD;
}

// BASE_PLT_SetupCommon 와 중복적인 부분이 많으나, side effect 방지 목적으로 전체 분리함
static void BASE_PLT_SetupFHDCommon(void)
{
    // setup group memcfg
    __m0_s_mem_grp.base = gMemCfgHdr[DDR_RGN_M0_DEV].base;
    __ext_sys_mem_grp.base = gMemCfgHdr[DDR_RGN_EXT_DEV].base;

    if (g_model_ctx.ddr_size == MODEL_OPT_1_5_GB)
    {
        __m0_ns_mem_grp.base = __m0_s_mem_grp.base + FHD_M0_1_5_GB_S_MEM0_GRP_SZ + FHD_M0_1_5_GB_S_MEM1_GRP_SZ;
    }
    else
    {
        __m0_ns_mem_grp.base = __m0_s_mem_grp.base + FHD_M0_1_0_GB_S_MEM0_GRP_SZ + FHD_M0_1_0_GB_S_MEM1_GRP_SZ;
    }

#ifdef INCLUDE_KDRV_GFX
    gfx_surf0.size = FHD_SURFACE_SZ;
    gMemCfgGfx.surface[0].size = gfx_surf0.size;
#endif

    // setup vdec
    vdec_vpb0.size = FHD_VPB4K_SZ;
    vdec_mpb0.size = VDEC_MPB_SZ;
    vdec_gen.size = VDEC_GEN_SZ;
    vdec_mcu.size = VDEC_MCU_SZ;

    audio0_buffer.size = AUDIO_BUFFER_SZ;

    // setup LNE
    lne_buffer.size = lne_buffer_memsz;

#ifdef INCLUDE_FHD_DUMMY

    // 임시코드임. M23 1.5GB UHD 맵을 그대로 차용하여 FHD 맵 최적화 테스트에 사용할것
    // 하드 코딩값이 보기 좋지 않음
    // 추후에는 삭제하자
    if (g_model_ctx.ddr_size == MODEL_OPT_1_5_GB)
    {
        printk("++ (temporary) adding dummy memblk for FHD 1.5GB board\n");

        fhd_dummy2.base = FHD_M0_1_5_GB_DEV_BASE + (FHD_M0_1_5_GB_S_MEM0_GRP_SZ + FHD_M0_1_5_GB_S_MEM1_GRP_SZ) + 0x65a8000;
        fhd_dummy3.base = FHD_M0_1_5_GB_DEV_BASE + (FHD_M0_1_5_GB_S_MEM0_GRP_SZ + FHD_M0_1_5_GB_S_MEM1_GRP_SZ) + 0xd6b8000;
    }

#endif
}

static void BASE_PLT_SetupMemLayout(void)
{
    printk("configure M23(%2X) kdriver memory\n", lx_chip_rev() & 0xff);

    if (g_model_ctx.map == MODEL_OPT_SLT_MAP)
    {
        return BASE_PLT_SetupSLTMemLayout();
    }

    if (g_model_ctx.disp_model == MODEL_OPT_HD || g_model_ctx.disp_model == MODEL_OPT_FHD)
    {
        return BASE_PLT_SetupFHDMemLayout();
    }

    gMemCfgHdr[DDR_RGN_M0_DEV].base = M0_1_5_GB_DEV_BASE;
    gMemCfgHdr[DDR_RGN_M0_DEV].size = M0_1_5_GB_DEV_SZ;

    gMemCfgHdr[DDR_RGN_EXT_DEV].base = EXT_DEV_BASE;
    gMemCfgHdr[DDR_RGN_EXT_DEV].size = EXT_DEV_SZ;

    BASE_PLT_SetupCommon();

    g_mem_desc_table = g_mem_desc_table_UHD;
}


static void BASE_PLT_SetupCommon(void)
{
    // setup group memcfg
    __m0_s_mem_grp.base = gMemCfgHdr[DDR_RGN_M0_DEV].base;
    __ext_sys_mem_grp.base = gMemCfgHdr[DDR_RGN_EXT_DEV].base;

    __m0_ns_mem_grp.base = __m0_s_mem_grp.base + M0_S_MEM0_GRP_SZ + M0_S_MEM1_GRP_SZ;

    // setup gfx
#ifdef INCLUDE_KDRV_GFX
    gfx_surf0.size = SURFACE_SZ;
    gMemCfgGfx.surface[0].size = gfx_surf0.size;
#endif

    // setup vdec
    vdec_vpb0.size = UHD_VPB4K_SZ;
    vdec_mpb0.size = VDEC_MPB_SZ;
    vdec_gen.size = VDEC_GEN_SZ;
    vdec_mcu.size = VDEC_MCU_SZ;

    audio0_buffer.size = AUDIO_BUFFER_SZ;

    // setup LNE
    lne_buffer.size = lne_buffer_memsz;
}

/*  run the post memory layout after memory allocation

*/
static void BASE_PLT_DoPostMemLayout(void)
{
    int i;
    int ret;

    unsigned int debug0_min_size = M0_DEBUG_SZ;

    /* make the full-sized debug0, debug1 memory */
    debug0.size = gMemCfgHdr[DDR_RGN_M0_DEV].base + gMemCfgHdr[DDR_RGN_M0_DEV].size - debug0.base;
    MEM_DESC_SIZE(DEBUG0) = debug0.size;

    printk("\n");
    printk("++ debug0 size tuned. debug0.size=0x%08x(%dKB) min_size=0x%08x(%dKB)\n",
           debug0.size, debug0.size >> 10, debug0_min_size, debug0_min_size >> 10);
    printk("\n");

    // see http://clm.lge.com/issue/browse/SICDTV-13880
    __ASSERT(debug0.size >= debug0_min_size);

#ifdef INCLUDE_FHD_DUMMY

    // 메모리맵 순서에 따라 구현되었음.
    // 분석하지 말것
    // 추후 삭제할것임
    if (g_model_ctx.disp_model == MODEL_OPT_HD || g_model_ctx.disp_model == MODEL_OPT_FHD)
        //            && g_model_ctx.ddr_size == MODEL_OPT_1_5_GB)
    {
        UINT32 mem0_grp_sz;
        UINT32 mem1_grp_sz;

        if (g_model_ctx.ddr_size == MODEL_OPT_1_5_GB)
        {
            mem0_grp_sz = FHD_M0_1_5_GB_S_MEM0_GRP_SZ;
            mem1_grp_sz = FHD_M0_1_5_GB_S_MEM1_GRP_SZ;
        }
        else
        {
            mem0_grp_sz = FHD_M0_1_0_GB_S_MEM0_GRP_SZ;
            mem1_grp_sz = FHD_M0_1_0_GB_S_MEM1_GRP_SZ;
        }

        MEM_DESC_BASE(PQE0_SVP) = __m0_ns_mem_grp.base - MEM_DESC_SIZE(PQE0_SVP);
        MEM_DESC_BASE(VDEC_MCU) = MEM_DESC_BASE(PQE0_SVP) - MEM_DESC_SIZE(VDEC_MCU);

        g_m0_pqe_svp.base = MEM_DESC_BASE(PQE0_SVP);
        vdec_mcu.base = MEM_DESC_BASE(VDEC_MCU);

        printk("++ vdec_mcu rebased. base=0x%08x\n", MEM_DESC_BASE(VDEC_MCU));
        printk("++ pqe_svp  rebased. base=0x%08x\n", MEM_DESC_BASE(PQE0_SVP));

        MEM_DESC_SIZE(FHD_DUMMY0) = mem0_grp_sz - MEM_DESC_SIZE(VDEC_VPB0);
        MEM_DESC_BASE(FHD_DUMMY0) = MEM_DESC_BASE(VDEC_VPB0) + MEM_DESC_SIZE(VDEC_VPB0);

        MEM_DESC_SIZE(FHD_DUMMY1) = mem1_grp_sz - (MEM_DESC_SIZE(VDEC_MCU) + MEM_DESC_SIZE(PQE0_SVP));
        MEM_DESC_BASE(FHD_DUMMY1) = MEM_DESC_BASE(VDEC_MCU) - MEM_DESC_SIZE(FHD_DUMMY1);

        MEM_DESC_SIZE(FHD_DUMMY2) = MEM_DESC_BASE(FHD_DUMMY2) - (MEM_DESC_BASE(GFX0) + MEM_DESC_SIZE(GFX0));
        MEM_DESC_BASE(FHD_DUMMY2) -= MEM_DESC_SIZE(FHD_DUMMY2);

        MEM_DESC_SIZE(FHD_DUMMY3) = MEM_DESC_BASE(FHD_DUMMY3) - (MEM_DESC_BASE(VBI) + MEM_DESC_SIZE(VBI));
        MEM_DESC_BASE(FHD_DUMMY3) -= MEM_DESC_SIZE(FHD_DUMMY3);

        fhd_dummy0.base = MEM_DESC_BASE(FHD_DUMMY0);
        fhd_dummy0.size = MEM_DESC_SIZE(FHD_DUMMY0);
        fhd_dummy1.base = MEM_DESC_BASE(FHD_DUMMY1);
        fhd_dummy1.size = MEM_DESC_SIZE(FHD_DUMMY1);
        fhd_dummy2.base = MEM_DESC_BASE(FHD_DUMMY2);
        fhd_dummy2.size = MEM_DESC_SIZE(FHD_DUMMY2);
        fhd_dummy3.base = MEM_DESC_BASE(FHD_DUMMY3);
        fhd_dummy3.size = MEM_DESC_SIZE(FHD_DUMMY3);

        printk("++ fhd_dummy0 tuned. base=0x%08x size=0x%08x\n", MEM_DESC_BASE(FHD_DUMMY0), MEM_DESC_SIZE(FHD_DUMMY0));
        printk("++ fhd_dummy1 tuned. base=0x%08x size=0x%08x\n", MEM_DESC_BASE(FHD_DUMMY1), MEM_DESC_SIZE(FHD_DUMMY1));
        printk("++ fhd_dummy2 tuned. base=0x%08x size=0x%08x\n", MEM_DESC_BASE(FHD_DUMMY2), MEM_DESC_SIZE(FHD_DUMMY2));
        printk("++ fhd_dummy3 tuned. base=0x%08x size=0x%08x\n", MEM_DESC_BASE(FHD_DUMMY3), MEM_DESC_SIZE(FHD_DUMMY3));
    }

#endif

#if 0
    /* print tuned memory layout for debug */
    extern void BASE_DEVMEM_DumpMemCfg(struct seq_file * m, UINT32 opt);
    BASE_DEVMEM_DumpMemCfg(NULL, 0x0);
#endif

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
                        printk("(x) CMA(%-15s %3dM@0x%08x) HMA\n",
                               mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
                        hma_alloc(mem_desc[i].m.name, mem_desc[i].m.size, 1 << 12);
                    }
                    else
                    {
                        printk("(?) CMA(%-15s %3dM@0x%08x) register error\n",
                               mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
                    }
                }
                else
                {
                    printk("(x) CMA(%-15s %3dM@0x%08x) ignored\n",
                           mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
                }
            }
            break;

            case MEMCFG_DESC_FLAG_CMA:
            {
                /* do nothing. each device will create its own CMA allocator */
                printk("(o) CMA(%-15s %3dM@0x%08x) CMA\n",
                       mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
            }
            break;

            default:
            {
                /* do nothing. this is BSP dedicated area */
                printk("(/) CMA(%-15s %3dM@0x%08x) skip\n",
                       mem_desc[i].m.name, mem_desc[i].m.size >> 20, mem_desc[i].m.base);
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
        } vdec_mem_desc[] =
        {
            { "vcma", MEM_DESC_ID_VDEC_VPB0 },
            { "mpb", MEM_DESC_ID_VDEC_MPB0 },
            { "vdec", MEM_DESC_ID_VDEC_GEN },
            { "vmcu", MEM_DESC_ID_VDEC_MCU },
            { "debug0", MEM_DESC_ID_DEBUG0 },
#ifdef INCLUDE_KDRV_AUDIO
            { "audio_buffer0", MEM_DESC_ID_AUDIO0 },
#endif
            { "surface", MEM_DESC_ID_GFX0 },
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
            base = mem_desc[vdec_mem_desc[a].mem_desc_id].m.base;
            size = mem_desc[vdec_mem_desc[a].mem_desc_id].m.size;
            pool_type =
                (mem_desc[vdec_mem_desc[a].mem_desc_id].flag ==
                 MEMCFG_DESC_FLAG_CMA) ? CMA_POOL : HMA_POOL;

            if (base == 0 || size == 0)
            {
                printk("---(%16s), %3dM@0x%08x, none\n", name,
                       size >> 20, base);
                continue;
            }

            ret =
                hma_pool_register_type(name, base, size, pool_type);

            if (ret == 0)
            {
                printk("cma(%16s), %3dM@0x%08x, %s pool\n",
                       name, size >> 20, base,
                       (pool_type == CMA_POOL) ? "CMA" : "HMA");
            }
            else
            {
                printk("cannot register %s pool\n", name);
                break;
            }
        }
    }
    printk("\n");

    hma_pool_register_name("vpb");
    hma_pool_fallback("vpb", "vcma");

    hma_pool_alias("venc0", "mpb"); // access mpb through "venc0"
    hma_pool_alias("venc1", "mpb"); // access mpb through "venc1"
    hma_pool_alias("photofb", "vpb");   // access vpb through "photofb"

    hma_pool_alias("dpb", "vpb");   // access vpb through "dpb" for legacy interface
    hma_pool_alias("cpb", "mpb");   // access mpb through "cpb" for laegacy interface

    hma_pool_fallback("cpb", "vpb");    // redirect cpb to vpb if out of memory

    hma_pool_alias("mtest-ddr0", "debug0"); // access debug0 through mtest-ddr0
    hma_pool_alias("de-dbg-m0", "debug0");  // access debug0 through de-dbg-m0
    hma_pool_alias("de-dbg-m1", "debug0");  // access debug0 through de-dbg-m1

    hma_pool_alias("vdec_shared", "vpb");   // access vpb through vdec_shared (http://clm.lge.com/issue/browse/AVTASK-769)

    hma_pool_alias("surface_ext", "debug0");    // access debug0 through surface_ext
    hma_pool_alias("audio_buffer", "audio_buffer0");    // access debug0 through audio_buffer

    // http://clm.lge.com/issue/browse/SICDTV-8565
    // pqe-lne pool is used only for pool info
    if (lne_buffer.size > 0x1000)
    {
        ret =
            hma_pool_register_type("pqe-lne", lne_buffer.base,
                                   lne_buffer.size, HMA_POOL);

        if (ret < 0)
        {
            printk(KERN_ERR
                   "hma_pool_register_type(\"pqe-lne\") failed. %d\n",
                   ret);
        }

        // lne_buffer.base ~ 4KB are reserved
        ret =
            hma_pool_register_type(lne_buffer.name,
                                   lne_buffer.base + 0x1000,
                                   lne_buffer.size - 0x1000, HMA_POOL);

        if (ret < 0)
        {
            printk(KERN_ERR
                   "hma_pool_register_type(\"%s\") failed. %d\n",
                   lne_buffer.name, ret);
        }
    }

    /* do nothing. DEMOD will alloc memory from "te_shared" region */

    /* TODO: add code to debug memory if necessary */

}

/** main function for kdriver platform initialization

    this function is called from base_drv.c after core initialization, chip rev detection
    (including chip probe), debug initialization and pre-initialization of each driver.

*/
void BASE_PLT_Init(void)
{
    int ret;

	BASE_PLT_ForceHmaPool();

    BASE_PLT_SetupMemLayout();

    ret = BASE_DEVMEM_InitDevMem(g_mem_desc_table);

    if (ret != RET_OK)
    {
        DBG_PRINT_ERROR
        ("fatal error during making kdriver memory layout\n");
    }

    BASE_PLT_DoPostMemLayout();
}

/** main function for kdriver platform probing process

    this function is called from base_drv.c after core initialization and chip rev detection.

*/
void BASE_PLT_Probe(UINT32* plt, UINT32* board_opt)
{
    int i;

    UINT32 hdmi_tx_output = 0;
    UINT32 plt_val = 0x0;
    UINT32 board_opt_val = 0x0;

    char optstr[80];
    const char* pioneer_board_fmtstr[2] =
    { "pioneer.board=%s", "pioneer.boardopts=%s" };

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
            if ((modelopt_txt[6] == '1') && (modelopt_txt[7] == '1')
                    && (modelopt_txt[8] == '0')
                    && (modelopt_txt[9] == '1'))
            {
                g_model_ctx.panel = MODEL_OPT_PANEL_NONE;
            }
            else if ((modelopt_txt[6] == '1')
                     && (modelopt_txt[7] == '0')
                     && (modelopt_txt[8] == '0'))
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
                    g_model_ctx.disp_model = MODEL_OPT_HD;
                    break;

                case '1':
                    g_model_ctx.disp_model = MODEL_OPT_FHD;
                    break;

                default:
                    g_model_ctx.disp_model = MODEL_OPT_UHD;
                    break;
            }

            /*  0: NO_FRC, 1: INT_FRC, others: EXT_FRCs.
               I will treat NO_FRC as INT_FRC for easy maintenance because there is never "NO_FRC" configuration.
               raxis.lim (2019/01/16)
               there is nothing special to identify whether 4K or 8K TV. just use if there is EXT_FRC or not
             */
            switch (hwopt_txt[17])
            {
                case '0':
                case '1':
                    g_model_ctx.frc_conn = MODEL_OPT_INT_FRC;
                    break;

                default:
                    g_model_ctx.frc_conn = MODEL_OPT_EXT_FRC;
                    g_model_ctx.disp_model = MODEL_OPT_QUHD;
                    break;
            }

            /* 2: 2K, 4: 4K  6: HD */
            switch (hwopt_txt[14])
            {
                case '6':
                    g_model_ctx.graphic = MODEL_OPT_HD_GRAPHIC;
                    break;

                default:
                    g_model_ctx.graphic = MODEL_OPT_2K_GRAPHIC;
                    break;
            }

            /* 0: 60Hz, 1: 120Hz */
            switch (hwopt_txt[4])
            {
                case '1':
                    g_model_ctx.frc_hz = MODEL_OPT_120HZ;
                    break;

                case '0':
                default:
                    break;
            }

            /* 1: 1GB, 3: 1.5GB */
            switch (hwopt_txt[11])
            {
                case '1':
                    g_model_ctx.ddr_size = MODEL_OPT_1_0_GB;
                    break;

                default:
                    g_model_ctx.ddr_size = MODEL_OPT_1_5_GB;
                    break;
            }
        }
    }

    if (pioneer_hwopt_probe)
    {
        /* check additional configuration for the test only */
        for (i = 0; i < NELEMENTS(pioneer_board_fmtstr); i++)
        {
            if (RET_OK ==
                    OS_ScanKernelCmdline(pioneer_board_fmtstr[i],
                                         optstr))
            {
                char* tok, *sav_tok;
                char delim[] = ",\t\n";

                tok = simple_strtok(optstr, delim, &sav_tok);

                while (tok)
                {
                    if (!strncasecmp(tok, "2.0GB", 5)) g_model_ctx.ddr_size = MODEL_OPT_2_0_GB;

                    if (!strncasecmp(tok, "1.5GB", 5)) g_model_ctx.ddr_size = MODEL_OPT_1_5_GB;

                    if (!strncasecmp(tok, "1.0GB", 5)) g_model_ctx.ddr_size = MODEL_OPT_1_0_GB;

                    if (!strncasecmp(tok, "HD", 2)) g_model_ctx.disp_model = MODEL_OPT_HD;

                    if (!strncasecmp(tok, "FHD", 3)) g_model_ctx.disp_model = MODEL_OPT_FHD;

                    if (!strncasecmp(tok, "UHD", 3)) g_model_ctx.disp_model = MODEL_OPT_UHD;

                    if (!strncasecmp(tok, "STB", 3)) g_model_ctx.panel = MODEL_OPT_PANEL_NONE;

                    if (!strncasecmp(tok, "LCD", 3)) g_model_ctx.panel = MODEL_OPT_PANEL_LCD;

                    if (!strncasecmp(tok, "OLED", 4)) g_model_ctx.panel = MODEL_OPT_PANEL_OLED;

                    if (!strncasecmp(tok, "60HZ", 4)) g_model_ctx.frc_hz = MODEL_OPT_60HZ;

                    if (!strncasecmp(tok, "120HZ", 5)) g_model_ctx.frc_hz = MODEL_OPT_120HZ;

                    if (!strncasecmp(tok, "2KOSD", 5)) g_model_ctx.graphic = MODEL_OPT_2K_GRAPHIC;

                    if (!strncasecmp(tok, "HDOSD", 5)) g_model_ctx.graphic = MODEL_OPT_HD_GRAPHIC;

                    if (!strncasecmp(tok, "SYS_BOARD", 9)) g_model_ctx.board = MODEL_OPT_SYS_BOARD;

                    if (!strncasecmp(tok, "SLT", 3)) g_model_ctx.board = MODEL_OPT_SLT_BOARD;

                    if (!strncasecmp(tok, "SLT_BOARD", 9)) g_model_ctx.board = MODEL_OPT_SLT_BOARD;

                    if (!strncasecmp(tok, "FPGA_BOARD", 10)) g_model_ctx.board = MODEL_OPT_FPGA_BOARD;

                    // 양산맵이 기본이며, SLT 테스트에 한정하여 SLT_MAP 으로 전환하도록 한다.
                    if (!strncasecmp(tok, "SLT_MAP", 7)) g_model_ctx.map = MODEL_OPT_SLT_MAP;

                    tok = simple_strtok(NULL, delim, &sav_tok);
                }
            }
        }
    }

    /* dump board option */
    printk("\n++ BOARD OPTION ++\n");

    printk("MODEL: %s\n",
           (g_model_ctx.disp_model == MODEL_OPT_UHD) ? "UHD" :
           (g_model_ctx.disp_model == MODEL_OPT_FHD) ? "FHD" :
           (g_model_ctx.disp_model == MODEL_OPT_HD)  ? "HD" : "n/a");

    printk("SOC  : %s\n", "M23(LG1315)");

    printk("DDR  : %s\n",
           (g_model_ctx.ddr_size == MODEL_OPT_1_0_GB) ? "1.0GB" :
           (g_model_ctx.ddr_size == MODEL_OPT_1_5_GB) ? "1.5GB" : "n/a");

    printk("GFX  : %s\n",
           (g_model_ctx.graphic == MODEL_OPT_2K_GRAPHIC) ? "2K(1920x1080)" :
           (g_model_ctx.graphic == MODEL_OPT_HD_GRAPHIC) ? "HD(1280x720)"  : "n/a");

    printk("PANEL: %s\n",
           (g_model_ctx.panel == MODEL_OPT_PANEL_NONE) ? "NONE(STB)" :
           (g_model_ctx.panel == MODEL_OPT_PANEL_LCD) ? "LCD/LED" :
           (g_model_ctx.panel == MODEL_OPT_PANEL_OLED) ? "OLED" : "n/a");

    printk("FRC  : %s(%sHz)\n",
           (g_model_ctx.frc_conn == MODEL_OPT_NO_FRC) ? "NONE" :
           (g_model_ctx.frc_conn == MODEL_OPT_EXT_FRC) ? "EXTERNAL" : "INTERNAL",
           (g_model_ctx.frc_hz == MODEL_OPT_60HZ) ? "60" : (g_model_ctx.frc_hz ==
                   MODEL_OPT_120HZ) ? "120" : "n/a");

    printk("BOARD: %s\n",
           (g_model_ctx.board == MODEL_OPT_SYS_BOARD) ? "SYS_BOARD" :
           (g_model_ctx.board == MODEL_OPT_SLT_BOARD) ?  "SLT_BOARD" : (g_model_ctx.board ==
                   MODEL_OPT_FPGA_BOARD) ? "FPGA_BOARD" : "n/a");

    printk("MAP  : %s\n",
           (g_model_ctx.map == MODEL_OPT_SLT_MAP) ? "SLT_MAP" :
           (g_model_ctx.map == MODEL_OPT_PROD_MAP) ?  "PROUCTION_MAP" : "n/a");

    printk("HDMI : %s\n", (hdmi_tx_output) ? "HDMI Tx" : "None");

    printk("USR  : 0x%02x 0x%02x 0x%02x 0x%02x\n",
           g_model_ctx.usr0, g_model_ctx.usr1, g_model_ctx.usr2,
           g_model_ctx.usr3);

    // make board_opt variable
    switch (g_model_ctx.disp_model)
    {
        case MODEL_OPT_HD:
            plt_val = LX_CHIP_PLT_HD;
            break;

        case MODEL_OPT_FHD:
            plt_val = LX_CHIP_PLT_FHD;
            break;

        default:
            plt_val = LX_CHIP_PLT_UHD;
            break;
    }

    switch (g_model_ctx.ddr_size)
    {
        case MODEL_OPT_1_0_GB:
            board_opt_val |= (LX_BOARD_OPT_DDR_1_0GB | LX_BOARD_OPT_ADV);
			break;

        case MODEL_OPT_1_5_GB:
        default:
            board_opt_val |= (LX_BOARD_OPT_DDR_1_5GB | LX_BOARD_OPT_ADV);
            break;
    }

    switch (g_model_ctx.frc_conn)
    {
        case MODEL_OPT_NO_FRC:
            board_opt_val |= LX_BOARD_OPT_NO_FRC;
            break;

        case MODEL_OPT_INT_FRC:
            board_opt_val |= LX_BOARD_OPT_INT_FRC;
            break;

        case MODEL_OPT_EXT_FRC:
            board_opt_val |= LX_BOARD_OPT_EXT_FRC;
            break;

        default:        /* none */
            break;
    }

    switch (g_model_ctx.frc_hz)
    {
        case MODEL_OPT_60HZ:
            board_opt_val |= LX_BOARD_OPT_DISP_60HZ;
            break;

        case MODEL_OPT_120HZ:
            board_opt_val |= LX_BOARD_OPT_DISP_120HZ;
            break;

        default:        /* none */
            break;
    }

    switch (g_model_ctx.panel)
    {
        case MODEL_OPT_PANEL_NONE:
            board_opt_val |= LX_BOARD_OPT_STBBOX;
            break;

        case MODEL_OPT_PANEL_LCD:
            board_opt_val |= LX_BOARD_OPT_LCD;
            break;

        case MODEL_OPT_PANEL_OLED:
            board_opt_val |= LX_BOARD_OPT_OLED;
            break;

        default:        /* none */
            break;
    }

    switch (g_model_ctx.graphic)
    {
        case MODEL_OPT_HD_GRAPHIC:
            board_opt_val |= LX_BOARD_OPT_HD_GRAPHIC;
            break;

        case MODEL_OPT_2K_GRAPHIC:
        default:
            board_opt_val |= LX_BOARD_OPT_2K_GRAPHIC;
            break;
    }

    if (g_model_ctx.usr0 == MODEL_OPT_USR)
    {
        board_opt_val |= LX_BOARD_OPT_USR0;
    }

    if (g_model_ctx.usr1 == MODEL_OPT_USR)
    {
        board_opt_val |= LX_BOARD_OPT_USR1;
    }

    if (g_model_ctx.usr2 == MODEL_OPT_USR)
    {
        board_opt_val |= LX_BOARD_OPT_USR2;
    }

    if (g_model_ctx.usr3 == MODEL_OPT_USR)
    {
        board_opt_val |= LX_BOARD_OPT_USR3;
    }

#ifdef INCLUDE_KDRV_VER_FPGA
    board_opt_val |= LX_BOARD_OPT_FPGA;
#else

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

#endif

    *plt = plt_val;
    *board_opt = board_opt_val;
}

/** @} */
