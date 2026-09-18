/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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
#include "board_opts.h"
#include "base_device.h"
#include "debug_util.h"
#include "os_util.h"
#include "base_impl.h"

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
// 0 : cat0 (3GB EVAL/SIGNAGE/SLT)
// 1 : cat1 (3GB PROD)
// 2 : catx (8GB AI-POC)
static inline int get_map_category(void)
{
    struct board_opts board_ctx = get_board_opts();
    return (board_ctx.board_type == MODELOPT_SLT_BOARD) ? MEMMAP_CAT0 :
           (board_ctx.ddr_size < DDR_SIZE_4G /*4GB*/) ? MEMMAP_CAT1 : MEMMAP_CATX;
}

#define mem_value_select(cat0,cat1,catx) ((get_map_category() == MEMMAP_CAT0)? (cat0) : (get_map_category() == MEMMAP_CAT1)? (cat1) : (catx))
#define mem_value_select_ex(name)   mem_value_select(CAT0_##name, CAT1_##name, CATX_##name)

#define __ASSERT(condition) \
do { \
    if (unlikely(!(condition)))\
    {\
        lg1k_logm_noti("WARNING: Assert Fail(%s)\n", #condition);\
        WARN_ON(1);\
    }\
} while(0)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
    RGN_BWB_S = 0,
    RGN_BWB_NS,
    RGN_M0_S,
    RGN_M0_NS,
    RGN_M1_S,
    RGN_M1_NS,
    RGN_SYS,
    RGN_MAX,
}
RGN_T;

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
void BASE_PLT_Init(void);
void BASE_PLT_Probe(u32* chip_plt, u32* board_opt);

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
static void force_hma_pool(void);
static void setup_memory_pool(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static int memcfg_debug = 1;

module_param(memcfg_debug, int, 0644);

// module memcfg variable
static LX_MEMCFG_T gfx_surf0        = {.name = "surface",      .base = 0x0, .size = 0 };

static LX_MEMCFG_T vdec_vpb0        = { .name = "vdec_vpb4k",  .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_vpb1        = { .name = "vdec_dpb8k",  .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_cpb0        = { .name = "vdec_cpb",    .base = 0x0, .size = 0 };
static LX_MEMCFG_T vdec_gen         = { .name = "vdec_gen",    .base = 0x0, .size = 0 };

static LX_MEMCFG_T audio0_buffer    = { .name = "audio0",      .base = 0x0, .size = 0 };
static LX_MEMCFG_T audio1_buffer    = { .name = "audio1",      .base = 0x0, .size = 0 };
static LX_MEMCFG_T audio_lnx_buffer = { .name = "audio_lnx",   .base = 0x0, .size = 0 };

static LX_MEMCFG_T npu_aipq         = { .name = "npu_aipq",     .base = 0x0, .size = 0 };
static LX_MEMCFG_T lne_buffer       = { .name = "lne_buffer",  .base = 0x0, .size = 0 };
static LX_MEMCFG_T npu0_buffer      = { .name = "npu0_buffer", .base = 0x0, .size = 0 };
static LX_MEMCFG_T npu1_buffer      = { .name = "npu1_buffer", .base = 0x0, .size = 0 };

static LX_MEMCFG_T sys_mem          = {.name = "sys_mem",       .base = 0x0, .size = __MB(1) };

static LX_MEMCFG_T debug0           = {.name = "debug0",       .base = 0x0, .size = 0 };
static LX_MEMCFG_T debug1           = {.name = "debug1",       .base = 0x0, .size = 0 };

static LX_MEMCFG_T bwb0_free        = {.name = "bwb0_free",    .base = 0x0, .size = 0 };
static LX_MEMCFG_T bwb1_free        = {.name = "bwb1_free",    .base = 0x0, .size = 0 };
static LX_MEMCFG_T m0_s_free        = {.name = "m0_s_free",    .base = 0x0, .size = 0 };
static LX_MEMCFG_T m1_s_free        = {.name = "m1_s_free",    .base = 0x0, .size = 0 };
static LX_MEMCFG_T m0_ns_free       = {.name = "m0_ns_free",   .base = 0x0, .size = 0 };
static LX_MEMCFG_T m1_ns_free       = {.name = "m1_ns_free",   .base = 0x0, .size = 0 };

static LX_MEMCFG_T pqe_bwb_svp      = {.name = "pqe_bwb_svp",  .base = 0x0, .size = 0 };
static LX_MEMCFG_T pqe_bwb_nsv      = {.name = "pqe_bwb_nsv",  .base = 0x0, .size = 0 };

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

    MEM_DESC_ID_PQE_BWB_SVP,
    MEM_DESC_ID_PQE_BWB_NSV,

    MEM_DESC_ID_TCON,

    MEM_DESC_ID_VBI,
    MEM_DESC_ID_CVD,

    MEM_DESC_ID_HDMI_FEC,
    MEM_DESC_ID_ESM_CODE,
    MEM_DESC_ID_ESM_DATA,

    MEM_DESC_ID_LNE,
    MEM_DESC_ID_NPU_AIPQ,
    MEM_DESC_ID_NPU0,
    MEM_DESC_ID_NPU1,

    MEM_DESC_ID_DEBUG0,         /* DEBUG(M0) */
    MEM_DESC_ID_DEBUG1,         /* DEBUG(M1) */

    MEM_DESC_ID_SYS0,
    MEM_DESC_ID_SYS1,

    MEM_DESC_ID_BWB0_FREE,      // secure BWB free mem
    MEM_DESC_ID_BWB1_FREE,      // non-secure BWB free mem

    MEM_DESC_ID_M0_S_FREE,        // M0 secure free mem
    MEM_DESC_ID_M1_S_FREE,        // M1 secure free mem
    MEM_DESC_ID_M0_NS_FREE,       // M0 free mem
    MEM_DESC_ID_M1_NS_FREE,       // M1 free mem

    MEM_DESC_ID_MAX,
}
MEM_DESC_ID_T;

/* memory alias list for CMA processing */
#define MEM_DESC_NAME(n)        (mem_desc[MEM_DESC_ID_##n].name)
#define MEM_DESC_POOL_TYPE(n)   (mem_desc[MEM_DESC_ID_##n].pool_type)
#define DEFINE_MEM_DESC(n,f,a)  [MEM_DESC_ID_##n] = { .name = #n, .pool_type=f, .alias=a }

static struct os_memcfg_desc mem_desc[MEM_DESC_ID_MAX]   =
{
    DEFINE_MEM_DESC(GFX0, CMA_POOL, "surface"),
    DEFINE_MEM_DESC(AUDIO0, HMA_POOL, "audio_s_mem"),
    DEFINE_MEM_DESC(AUDIO1, HMA_POOL, "audio_ns_mem"),
    DEFINE_MEM_DESC(AUDIO_LNX, HMA_POOL, "audio_lnx"),

    DEFINE_MEM_DESC(FBDEV, HMA_POOL, NULL),

    DEFINE_MEM_DESC(VDEC_VPB0, HMA_POOL, "vpb"),
    DEFINE_MEM_DESC(VDEC_VPB1, HMA_POOL, "vpb8k"),
    DEFINE_MEM_DESC(VDEC_CPB0, CMA_POOL, "cpb"),
    DEFINE_MEM_DESC(VDEC_GEN, HMA_POOL, "vdec"),

    DEFINE_MEM_DESC(TE, CMA_POOL, NULL),

    DEFINE_MEM_DESC(DEMOD, HMA_POOL, NULL),
    DEFINE_MEM_DESC(DEMOD_FW, HMA_POOL, NULL),

    DEFINE_MEM_DESC(PQE0_SVP, HMA_POOL, NULL),
    DEFINE_MEM_DESC(PQE0_NSV, HMA_POOL, NULL),
    DEFINE_MEM_DESC(PQE0_USR, CMA_POOL, NULL),
    DEFINE_MEM_DESC(PQE1_SVP, HMA_POOL, NULL),
    DEFINE_MEM_DESC(PQE1_NSV, HMA_POOL, NULL),
    DEFINE_MEM_DESC(PQE1_USR, CMA_POOL, NULL),

    DEFINE_MEM_DESC(PQE_BWB_SVP, HMA_POOL, "pqe-bwb-svp"),
    DEFINE_MEM_DESC(PQE_BWB_NSV, CMA_POOL, "pqe-bwb-nsv"),

    DEFINE_MEM_DESC(VBI, HMA_POOL, NULL),
    DEFINE_MEM_DESC(CVD, HMA_POOL, NULL),

    DEFINE_MEM_DESC(HDMI_FEC, HMA_POOL, NULL),
    DEFINE_MEM_DESC(ESM_CODE, HMA_POOL, NULL),
    DEFINE_MEM_DESC(ESM_DATA, HMA_POOL, NULL),

    DEFINE_MEM_DESC(LNE, HMA_POOL, "pqe-lne"),
    DEFINE_MEM_DESC(NPU_AIPQ, HMA_POOL, "npu_aipq"),
    DEFINE_MEM_DESC(NPU0, HMA_POOL, "npu0"),
    DEFINE_MEM_DESC(NPU1, HMA_POOL, "npu1"),

    DEFINE_MEM_DESC(SYS0, HMA_POOL, NULL),
    DEFINE_MEM_DESC(SYS1, HMA_POOL, NULL),

    DEFINE_MEM_DESC(DEBUG0, HMA_POOL, "debug0"),
    DEFINE_MEM_DESC(DEBUG1, CMA_POOL, "debug1"),

    DEFINE_MEM_DESC(BWB0_FREE, HMA_POOL, "bwb0_free"),
    DEFINE_MEM_DESC(BWB1_FREE, CMA_POOL, "bwb1_free"),
    DEFINE_MEM_DESC(M0_S_FREE, HMA_POOL, "m0_s_free"),
    DEFINE_MEM_DESC(M1_S_FREE, HMA_POOL, "m1_s_free"),
    DEFINE_MEM_DESC(M0_NS_FREE, CMA_POOL, "m0_ns_free"),
    DEFINE_MEM_DESC(M1_NS_FREE, CMA_POOL, "m1_ns_free"),
};

static struct os_memcfg_region* bwb0_rgn = NULL;
static struct os_memcfg_region* bwb1_rgn = NULL;
static struct os_memcfg_region* m0_s_rgn = NULL;
static struct os_memcfg_region* m0_ns_rgn = NULL;
static struct os_memcfg_region* m1_s_rgn = NULL;
static struct os_memcfg_region* m1_ns_rgn = NULL;
static struct os_memcfg_region* sys_rgn = NULL;

/*========================================================================================
    Implementation Group
========================================================================================*/
static void force_hma_pool(void)
{
    int i;

    for (i = 0; i < MEM_DESC_ID_MAX; i++)
    {
        if (mem_desc[i].pool_type == CMA_POOL)
        {
            if (mem_desc[i].alias && check_force_hma_pool(mem_desc[i].alias))
            {
                mem_desc[i].pool_type = HMA_POOL;
                lg1k_logm_noti("force_hma_pool: %s pool is set to hma pool by user\n", mem_desc[i].alias);
            }
        }
    }
}

static void setup_memory_pool(void)
{
    LX_MEMCFG_T mem;

    struct board_opts board_ctx = get_board_opts();

    lg1k_logm_noti("configure O26(0x%2x) kdriver memory\n", lx_chip());
    lg1k_logm_noti("board.ddr_size=0x%x\n", board_ctx.ddr_size);

    // setup module memory size
#ifdef INCLUDE_KDRV_GFX
    gfx_surf0.size = MOD_SURFACE_SZ;
    gMemCfgGfx.surface[0].size  = gfx_surf0.size;
#endif

    vdec_vpb0.size  = mem_value_select_ex(MOD_VPB4K_SZ);
    vdec_vpb1.size  = mem_value_select_ex(MOD_VPB8K_SZ);
    vdec_cpb0.size  = mem_value_select_ex(MOD_VDEC_CPB_SZ);
    vdec_gen.size   = MOD_VDEC_GEN_SZ;

    audio0_buffer.size = MOD_AUDIO0_SZ;
    audio1_buffer.size = MOD_AUDIO1_SZ;
    audio_lnx_buffer.size = MOD_AUDIO_LNX_SZ;

    lne_buffer.size  = MOD_LNE_SZ;
    npu_aipq.size    = MOD_NPU_AIPQ_SZ;
    npu0_buffer.size = mem_value_select_ex(MOD_NPU0_SZ);
    npu1_buffer.size = mem_value_select_ex(MOD_NPU1_SZ);

    pqe_bwb_svp.size = mem_value_select_ex(MOD_PQE_BWB_SVP_SZ);
    pqe_bwb_nsv.size = mem_value_select_ex(MOD_PQE_BWB_NSV_SZ);

    bwb0_free.size = mem_value_select_ex(MOD_BWB0_FREE_SZ);
    bwb1_free.size = mem_value_select_ex(MOD_BWB1_FREE_SZ);
    m0_s_free.size = mem_value_select_ex(MOD_M0_S_FREE_SZ);
    m1_s_free.size = mem_value_select_ex(MOD_M1_S_FREE_SZ);
    m0_ns_free.size = mem_value_select_ex(MOD_M0_NS_FREE_SZ);
    m1_ns_free.size = mem_value_select_ex(MOD_M1_NS_FREE_SZ);
    debug0.size = mem_value_select_ex(MOD_M0_DEBUG_SZ);
    debug1.size = mem_value_select_ex(MOD_M1_DEBUG_SZ);

    // register regions
    mem.base = mem_value_select_ex(RGN_BWB0_BASE);
    mem.size = mem_value_select_ex(RGN_BWB0_SZ);
    bwb0_rgn = os_memcfg_add_region("BWB0_RGN", mem.base, mem.size);

    mem.base = mem_value_select_ex(RGN_BWB1_BASE);
    mem.size = mem_value_select_ex(RGN_BWB1_SZ);
    bwb1_rgn = os_memcfg_add_region("BWB1_RGN", mem.base, mem.size);

    mem.base = mem_value_select_ex(RGN_M0_BASE);
    mem.size = mem_value_select_ex(RGN_M0_S_SZ);
    m0_s_rgn = os_memcfg_add_region("M0_S_RGN", mem.base, mem.size);

    mem.base += mem_value_select_ex(RGN_M0_S_SZ);
    mem.size = mem_value_select_ex(RGN_M0_NS_SZ);
    m0_ns_rgn = os_memcfg_add_region("M0_NS_RGN", mem.base, mem.size);

    mem.base = mem_value_select_ex(RGN_M1_BASE);
    mem.size = mem_value_select_ex(RGN_M1_S_SZ);
    m1_s_rgn = os_memcfg_add_region("M1_S_RGN", mem.base, mem.size);

    mem.base += mem_value_select_ex(RGN_M1_S_SZ);
    mem.size = mem_value_select_ex(RGN_M1_NS_SZ);
    m1_ns_rgn = os_memcfg_add_region("M1_NS_RGN", mem.base, mem.size);

    mem.base = mem_value_select_ex(RGN_SYS_BASE);
    mem.size = mem_value_select_ex(RGN_SYS_SZ);
    sys_rgn = os_memcfg_add_region("SYS_RGN", mem.base, mem.size);

    // register memory items
    // BWB0 GROUP
#ifdef INCLUDE_KDRV_VDEC
    os_memcfg_add_item(bwb0_rgn, MEM_DESC_NAME(VDEC_VPB0), &vdec_vpb0, sizeof(vdec_vpb0));
    os_memcfg_add_item(bwb0_rgn, MEM_DESC_NAME(VDEC_VPB1), &vdec_vpb1, sizeof(vdec_vpb1));
#endif
    os_memcfg_add_item(bwb0_rgn, MEM_DESC_NAME(BWB0_FREE), &bwb0_free, sizeof(bwb0_free));
#ifdef INCLUDE_KDRV_DE
    os_memcfg_add_item(bwb0_rgn, MEM_DESC_NAME(PQE_BWB_SVP), &pqe_bwb_svp, sizeof(pqe_bwb_svp));
#endif

    // BWB1 GROUP
#ifdef INCLUDE_KDRV_DE
    os_memcfg_add_item(bwb1_rgn, MEM_DESC_NAME(PQE_BWB_NSV), &pqe_bwb_nsv, sizeof(pqe_bwb_nsv));
#endif
#ifdef INCLUDE_KDRV_VDEC

    if (get_map_category() == MEMMAP_CAT0) /* EVAL/PoC/SLT/Bringup */
    {
        os_memcfg_add_item(bwb1_rgn, MEM_DESC_NAME(VDEC_CPB0), &vdec_cpb0, sizeof(vdec_cpb0));
        os_memcfg_add_item(bwb1_rgn, MEM_DESC_NAME(VDEC_GEN), &vdec_gen, sizeof(vdec_gen));
    }

#endif
    os_memcfg_add_item(bwb1_rgn, MEM_DESC_NAME(NPU_AIPQ), &npu_aipq, sizeof(npu_aipq));
    os_memcfg_add_item(bwb1_rgn, MEM_DESC_NAME(BWB1_FREE), &bwb1_free, sizeof(bwb1_free));

    // M0 SECURE MEM GROUP

#ifdef INCLUDE_KDRV_AUDIO
    os_memcfg_add_item(m0_s_rgn, MEM_DESC_NAME(AUDIO0), &audio0_buffer, sizeof(audio0_buffer));
#endif

    //os_memcfg_add_item(m0_s_rgn, MEM_DESC_NAME(NPU_AIPQ), &npu_aipq, sizeof(npu_aipq));

    os_memcfg_add_item(m0_s_rgn, MEM_DESC_NAME(M0_S_FREE), &m0_s_free, sizeof(m0_s_free));

#ifdef INCLUDE_KDRV_DE
    os_memcfg_add_item(m0_s_rgn, MEM_DESC_NAME(PQE0_SVP), &g_m0_pqe_svp, sizeof(g_m0_pqe_svp));
#endif

    // M0 NON-SECURE MEM GROUP
#ifdef INCLUDE_KDRV_DE
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(PQE0_NSV), &g_m0_pqe_nsv, sizeof(g_m0_pqe_nsv));
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(PQE0_USR), &g_m0_pqe_usr, sizeof(g_m0_pqe_usr));
#endif

#ifdef INCLUDE_KDRV_VDEC

    if (get_map_category() != MEMMAP_CAT0)  /* PROD/AI-POC */
    {
        os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(VDEC_CPB0), &vdec_cpb0, sizeof(vdec_cpb0));
        os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(VDEC_GEN), &vdec_gen, sizeof(vdec_gen));
    }

#endif

#ifdef INCLUDE_KDRV_AUDIO
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(AUDIO1), &audio1_buffer, sizeof(audio1_buffer));
#endif

    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(LNE), &lne_buffer, sizeof(lne_buffer));

    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(NPU0), &npu0_buffer, sizeof(npu0_buffer));

#ifdef INCLUDE_KDRV_TE
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(TE), gMemCfgTE, sizeof(gMemCfgTE));
#endif

#ifdef INCLUDE_KDRV_DEMOD
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(DEMOD_FW), (LX_MEMCFG_T*)&gMemCfgDEMOD_FW, sizeof(gMemCfgDEMOD_FW));
#endif

#ifdef INCLUDE_KDRV_VBI
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(VBI), (LX_MEMCFG_T*)&gstBufMemCfgVBIRev[0], sizeof(gstBufMemCfgVBIRev[0]));
#endif

#ifdef INCLUDE_KDRV_GFX
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(GFX0), &gfx_surf0, sizeof(gfx_surf0));
#endif

#ifdef INCLUDE_KDRV_HDMI20
    //os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(HDMI_FEC), &gMemCfgHdmiFec[0], sizeof(gMemCfgHdmiFec[0]));
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(ESM_CODE), &gMemCfgEsm[0], sizeof(gMemCfgEsm[0]));
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(ESM_DATA), &gMemCfgEsm[1], sizeof(gMemCfgEsm[1]));
#endif


#ifdef INCLUDE_KDRV_FBDEV
    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(FBDEV), &gMemCfgFBBuf, sizeof(gMemCfgFBBuf));
#endif

    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(M0_NS_FREE), &m0_ns_free, sizeof(m0_ns_free));

    os_memcfg_add_item(m0_ns_rgn, MEM_DESC_NAME(DEBUG0), &debug0, sizeof(debug0));

    // M0 NON-SECURE MEM GROUP
#ifdef INCLUDE_KDRV_DE
    os_memcfg_add_item(m1_s_rgn, MEM_DESC_NAME(M1_S_FREE), &m1_s_free, sizeof(m1_s_free));
    os_memcfg_add_item(m1_s_rgn, MEM_DESC_NAME(PQE1_SVP), &g_m1_pqe_svp, sizeof(g_m1_pqe_svp));
#endif

    // M1 NON-SECURE MEM GROUP
#ifdef INCLUDE_KDRV_DE
    os_memcfg_add_item(m1_ns_rgn, MEM_DESC_NAME(PQE1_NSV), &g_m1_pqe_nsv, sizeof(g_m1_pqe_nsv));
    os_memcfg_add_item(m1_ns_rgn, MEM_DESC_NAME(PQE1_USR), &g_m1_pqe_usr, sizeof(g_m1_pqe_usr));
#endif

#ifdef INCLUDE_KDRV_AUDIO
    os_memcfg_add_item(m1_ns_rgn, MEM_DESC_NAME(AUDIO_LNX), &audio_lnx_buffer, sizeof(audio_lnx_buffer));
#endif

    os_memcfg_add_item(m1_ns_rgn, MEM_DESC_NAME(NPU1), &npu1_buffer, sizeof(npu1_buffer));

    os_memcfg_add_item(m1_ns_rgn, MEM_DESC_NAME(M1_NS_FREE), &m1_ns_free, sizeof(m1_ns_free));
    os_memcfg_add_item(m1_ns_rgn, MEM_DESC_NAME(DEBUG1), &debug1, sizeof(debug1));

    // SYS GROUP
    os_memcfg_add_item(sys_rgn, MEM_DESC_NAME(SYS0), &sys_mem, sizeof(sys_mem));
}

static void make_memory_pool(void)
{
    int ret;
    int err;

    u64 rgn_base;
    u32 rgn_size;
    u32 debug0_min_size, debug1_min_size;

    //struct board_opts board_ctx = get_board_opts();

    // request memory layout
    err = os_memcfg_make_layout();
    lg1k_logm_noti("memcfg error_count=%d\n", err);

    debug0_min_size = mem_value_select_ex(MOD_M0_DEBUG_SZ);
    debug1_min_size = mem_value_select_ex(MOD_M1_DEBUG_SZ);

    // tune debug0/1 memory size to use all reserved region
    os_memcfg_get_info("M0_NS_RGN", &rgn_base, &rgn_size);
    debug0.size = rgn_base + rgn_size - debug0.base;

    os_memcfg_get_info("M1_NS_RGN", &rgn_base, &rgn_size);
    debug1.size = rgn_base + rgn_size - debug1.base;

    lg1k_logm_noti("++ debug0 size tuned. debug0.size=0x%08x(%dKB) min_size=0x%08x(%dKB)\n",
                   debug0.size, debug0.size >> 10, debug0_min_size, debug0_min_size >> 10);
    lg1k_logm_noti("++ debug1 size tuned. debug1.size=0x%08x(%dKB) min_size=0x%08x(%dKB)\n",
                   debug1.size, debug1.size >> 10, debug1_min_size, debug1_min_size >> 10);

    // see http://clm.lge.com/issue/browse/SICDTV-13880
    __ASSERT(debug0.size >= debug0_min_size);
    __ASSERT(debug1.size >= debug1_min_size);

    os_memcfg_alloc_mpool(mem_desc, NELEMENTS(mem_desc));

    if (memcfg_debug)
    {
        os_memcfg_dump(NULL, false);
    }

    // alloc cma & hma memory pool with help of hma allocator
    // setup alias and fallback
    // hma_pool_fallback("vpb", "vpb8k");  // redirect vpb to vpb8k if out of memory

    // PQE 모듈이 pqe-bwb 를 통해 항상 접근이 가능하도록 조치한다.
    // hma_pool_alias("pqe-bwb", "vpb8k"); // access vpb8k through pqe-bwb

    // for legacy, DO NOT use "vdec_shared"
    hma_pool_alias("vdec_shared", "pqe-bwb-nsv");   // access pqe-bwb-nsv through vdec_shared
    hma_pool_alias("pqe-bwb", "pqe-bwb-nsv");   // access pqe-bwb-nsv through pqe-bwb

    hma_pool_alias("cpb2", "cpb");      // access cpb through "cpb2"
    hma_pool_alias("photofb", "cpb");   // access cpb through "photofb"
    hma_pool_alias("venc0", "cpb");     // access cpb through "venc0"

    hma_pool_alias("dpb", "vpb");       // access vpb through "dpb" for legacy interface
    hma_pool_alias("venc1", "vpb");     // access vpb through "venc1"

    hma_pool_alias("mtest-ddr0", "debug0"); // access debug0 through mtest-ddr0
    hma_pool_alias("mtest-ddr1", "debug1"); // access debug1 through mtest-ddr1
    hma_pool_alias("de-dbg-m1", "debug0");  // access debug0 through de-dbg-m1
    hma_pool_alias("de-dbg-m2", "debug1");  // access debug1 through de-dbg-m2

    hma_pool_alias("surface_ext", "debug0");// access debug0 through surface_ext

    hma_pool_alias("audio_buffer", "audio_ns_mem"); // access audio_ns_mem through audio_buffer
    hma_pool_alias("audio_buffer0", "audio_ns_mem");  // access audio_s_mem through audio_buffer0
    hma_pool_alias("audio_fw_bin", "debug0");  // access debug0 through audio_fw_bin
    hma_pool_alias("audio_dump", "debug0");  // access debug0 through audio_dump

    hma_pool_alias("npu", "npu0");  // access npu0 through npu

    // make "lne_buffer" within LNE memcfg
    /* lne_buffer.base ~ 4KB are reserved */
    ret = hma_pool_register_type(lne_buffer.name, lne_buffer.base + (4 << 10),
                                 lne_buffer.size - (4 << 10), HMA_POOL);

    if (ret < 0)
    {
        lg1k_logm_error("hma_pool_register_type(\"%s\") failed. %d\n", lne_buffer.name, ret);
    }

    // TODO: add code to debug memory if necessary
}

/** main function for kdriver platform initialization
 *  this function is called from base_drv.c after core initialization, chip rev detection
 *  (including chip probe), debug initialization and pre-initialization of each driver.
 */
void BASE_PLT_Init(void)
{
    force_hma_pool();
    setup_memory_pool();
    make_memory_pool();
}

void BASE_PLT_Probe(u32* chip_plt, u32* board_opt)
{
    PARAM_UNUSED(chip_plt);
    PARAM_UNUSED(board_opt);

    // do nothing
}

/** @} */
