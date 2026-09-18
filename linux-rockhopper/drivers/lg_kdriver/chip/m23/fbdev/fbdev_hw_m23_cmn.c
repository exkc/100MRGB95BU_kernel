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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#undef  V_MIRROR_TEST   /* 임시 코드임. 테스트시에만 임시로 풀어서 사용할것. CCC 에는 지울것 */

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_drv.h"
#include "fbdev_hw.h"
#include "fbdev_hw_m23.h"
#include "osd_reg_m23.h"
#include "osd_mif_reg_m23.h"
#include "osd_afbc_reg_m23.h"
#include "osd_top_reg_m23.h"
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/seq_file.h>
#include <linux/fb.h>

#include "hma_alloc.h"

#ifdef FBDEV_M23_USE_CTOP_REGS
#include "../sys/sys_regs.h"
#endif

#ifdef INCLUDE_KDRV_OVI
#include "be_kapi.h"
#endif

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif

#include "afbc_sw_drv.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define SAFE_LOGO_MEM_POOL "debug0"

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define CHECK_AFBC_FBDEV(id) ((id)==LX_FBDEV_ID_OSD0 || (id)==LX_FBDEV_ID_OSD1)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int FBDEV_M23_CMN_MirrorCtrl(BOOLEAN v_mirror_en);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern  int                         g_fbdev_use_isr_mon;

/*----------------------------------------------------------------------------------------
    global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_M23_CMN_InitFBCEnv(void);
#ifdef FBDEV_M23_USE_FBC_CTRL
static void FBDEV_M23_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt);
#endif

static void FBDEV_M23_CMN_InitCropEnv(void);
static void FBDEV_M23_CMN_SetupSRScaler(BOOLEAN onoff, BOOLEAN bForce);

static void FBDEV_M23_CMN_SetupExternalRenderer(int fb_dev_id, struct fb_info* fbinfo);
static void FBDEV_M23_CMN_AllocExternalRendererFrameBuffer(void);
static void FBDEV_M23_CMN_SetExternalRenderCropRegion(BOOLEAN crop_en, int img_width, int img_height, int xoffset,
        int yoffset, LX_RECT_T* crop_pos);

static void FBDEV_M23_CMN_ReInitHW(void);
static void FBDEV_M23_CMN_InitMirrorEnv(void);
static FBDEV_VSYNC_CLK_T FBDEV_M23_CMN_DetectVSyncClk(void);

static void FBDEV_M23_CMN_NotifyToPQEDriver(void);
static int  FBDEV_M23_CMN_WaitForPQEDriverInitialization(void);

static void FBDEV_M23_CMN_BootLogoClearScheduler(struct work_struct* work);

static void FBDEV_M23_CMN_ShutdownOSDPath(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_osd_hdr_spinlock);

static struct workqueue_struct* fbdev_m23_wq;
static DECLARE_DELAYED_WORK(boot_logo_clear_work, FBDEV_M23_CMN_BootLogoClearScheduler);

static int fbdev_boot_freeze_timeout       = 0;    /* see SICDTV-8491. set 0 by default */
static int fbdev_resume_freeze_timeout     = 0;    /* see SICDTV-8491. set 0 by default */
static int fbdev_pqefw_osd0_out_ctrl       = 1;    /* SICDTV-4359 */

static int fbdev_enable_logo_clear         = 0;    /* see SICDTV-8556 */
static int fbdev_boot_logo_clear_timeout   = 3000; /* see SICDTV-8556 */
static int fbdev_resume_logo_clear_timeout = 2000; /* see SICDTV-8556 */

static BOOLEAN fbdev_logo_migration_required = TRUE;

static int fbdev_afbc_version = FBDEV_HW_AFBC_VER_1_1; /* M23 = AFBC1.1 고정. see SICDTV-10618 */

module_param_named(fbdev_m23_boot_freeze_timeout, fbdev_boot_freeze_timeout, int, 0644);
module_param_named(fbdev_m23_resume_freeze_timeout, fbdev_resume_freeze_timeout, int, 0644);

module_param_named(fbdev_m23_pqefw_osd0_out_ctrl, fbdev_pqefw_osd0_out_ctrl, int, 0644);

module_param_named(fbdev_m23_enable_logo_clear, fbdev_enable_logo_clear, int, 0644);
module_param_named(fbdev_m23_boot_logo_clear_timeout, fbdev_boot_logo_clear_timeout, int, 0644);
module_param_named(fbdev_m23_resume_logo_clear_timeout, fbdev_resume_logo_clear_timeout, int, 0644);

//module_param_named(fbdev_m23_afbc_version, fbdev_afbc_version, int, 0644);

static int fbdev_hw_pm_suspend_stage = 0;
static int fbdev_hw_pm_restore_stage = 0;

static int fbdev_use_shutdown_path_on_suspend = 1;  /* see SICDTV-9009, SICDTV-9992 */
module_param_named(fbdev_m23_use_shutdown_path_on_suspend, fbdev_use_shutdown_path_on_suspend, int, 0644);

#if 0
#define CHECK_REGS(id)  __check_regs(id, __FUNCTION__,__LINE__)
static void __check_regs(int id, const char* func, const int line)
{
}
#endif

static unsigned long fbdev_bootlogo_fbmem_addr = 0x0;

// (2021/10/01)
// E-Streamer layer 의 pixel format 을 쉽게 제어할 수 있도록 한다.
#ifdef FBDEV_M23_USE_AFBC_ESTREAMER
static int fbdev_afbc_estreamer = 1;
#else
static int fbdev_afbc_estreamer = 0;
#endif
module_param_named(fbdev_m23_afbc_estreamer, fbdev_afbc_estreamer, int, 0644);

/*----------------------------------------------------------------------------------------
    Static Functions
----------------------------------------------------------------------------------------*/

/** query FB mapping information
 *
 *  fb_dev_id is the virtual indentifier for application, this functions returns the real OSD HW layer
 *
 *  @param fb_dev_id [IN] user ID
 *  @param xlst [IN] arrary to hold two OSD HW layer connected to user ID
 *  @return num of xlst
 *
 */
int FBDEV_M23_CMN_GetHWXList(int fb_dev_id, int xlst[2])
{
    int afbc_xlst[2];

    return FBDEV_M23_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
}

int FBDEV_M23_CMN_GetHWXListEx(int fb_dev_id, int xlst[2], int afbc_xlst[2])
{
    int num_xlst = 0;
    //FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    switch (fb_dev_id)
    {
        case LX_FBDEV_ID_OSD0:
        {
            num_xlst = 1;
            xlst[0] = 0;
            xlst[1] = -1;
            afbc_xlst[0] = 0;
            afbc_xlst[1] = -1;
        }
        break;

        // (2021/07/05)
        // fb1 는 실제 존재 하지 않으며, E-Streamer 등의 특수 목적으로만 사용할 수 있다.
        // 따라서 fb0, fb1 은 동일한 HW 를 설정할 수 있도록 조치한다.
        case LX_FBDEV_ID_OSD1:
        {
            num_xlst = 1;
            xlst[0] = 0;
            xlst[1] = -1;
            afbc_xlst[0] = 0;
            afbc_xlst[1] = -1;
        }
        break;

        case LX_FBDEV_ID_CSR0:
        {
            num_xlst = 1;
            xlst[0] = 3;
            xlst[1] = -1;
            afbc_xlst[0] = -1;
            afbc_xlst[1] = -1;
        }
        break;

        default:
        {
            num_xlst = 0;
            xlst[0] = -1;
            xlst[1] = -1;
            afbc_xlst[0] = -1;
            afbc_xlst[1] = -1;
        }
        break;
    }

    return num_xlst;
}

BOOLEAN  FBDEV_M23_CMN_IsUHDDispMode(void)
{
    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    return (hw_ctx->hw_disp_width > 2048) ? TRUE : FALSE;
}

/** enable OSD HW update
 *
 *  if OSD header flag is not set, OSD is not updated !
 *
 */
static void FBDEV_M23_CMN_EnableOSDHdrFlush(ULONG data)
{
    int i;

    FBDEV_NOTI("<!> enable osd_hdr_flush & exit OSD freeze stage. afbc=%d\n",
               FBDEV_M23_CMN_GetHWStatus(FBDEV_M23_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0));

    // enable osd_hdr_flush to unfreeze OSD
    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(i);
        struct scanvas*  canvas = FBDEV_GetWinCanvas(i);

        FBDEV_BOOT_DEBUG("++ fb(%d)\n", i);

        FBDEV_CHECK_CODE(NULL == wctx, continue, "invalid fb(%d) ctx\n", i);
        FBDEV_CHECK_CODE(NULL == canvas, continue, "invalid fb(%d) canvas\n", i);

        //FBDEV_CHECK_CODE(!g_fbdev_cfg->fb[i].b_active, continue, "inactive fb(%d)\n", i);

        // if freeize is already disabled, ignore osd_hdr flush
        if (wctx->status.b_osd_hdr_flush)
        {
            FBDEV_HW_DEBUG("fb(%d) osd_hdr_flush is already enabled\n", i);
            continue;
        }

        FBDEV_NOTI("++ fb(%d) flip_cnt = %d, total_flip_cnt = %d\n",
                   i,
                   wctx->status.fb_flip_cnt,
                   wctx->status.total_fb_flip_cnt);

        wctx->status.b_osd_hdr_flush = TRUE;

        // (2020/06/11)
        // 수정된 OSD 초기화 정책에 의하여 이 함수는 단순히 b_osd_hdr_flush 를 활성화 하는 역할로
        // 축소한다. 향후 함수 목적을 수정하거나, 완전히 삭제할 수도 있음

        // do nothing
    }
}

/** override the default boot_freeze_timeout
 *
 */
void FBDEV_M23_CMN_SetBootFreezeTimeout(int val)
{
    if (fbdev_boot_freeze_timeout != val)
    {
        printk("+ boot_freeze_timeout %d -> %d\n", fbdev_boot_freeze_timeout, val);
        fbdev_boot_freeze_timeout = val;
    }
}

/** clear current logo screen after a few seconds after OSD initialization
 *
 */
static void FBDEV_M23_CMN_BootLogoClearScheduler(struct work_struct* work)
{
    FBDEV_NOTI("logo clear work started\n");
    fbdev_logo_migration_required = TRUE;
    FBDEV_M23_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_CLEAR);
}

/** move boot logo framebuffer to safe region (prototype implementation)
 *
 */
void        FBDEV_M23_CMN_MigrateBootLogo(FBDEV_M23_BOOT_LOGO_MODE_T mode)
{
#define OSD_CTRL_BASE(layer) ((UINT32)(M23_CCO_BASE + 0x200 + (0x100*(layer))))

    int i;
    int rc;
    OS_CACHE_MAP_T cmap_src, cmap_dst;

    UINT32 image_size;
    int afbc_mode = 0;
    UINT32 fbmem_addr_src = 0;
    UINT32 fbmem_addr_dst = 0;

    /* allow this function to run once at cold boot regardless of result */
    if (fbdev_logo_migration_required == FALSE)
    {
        FBDEV_WARN("ignore request\n");
        return;
    }

    fbdev_logo_migration_required = FALSE;

    memset(&cmap_src, 0x0, sizeof(OS_CACHE_MAP_T));
    memset(&cmap_dst, 0x0, sizeof(OS_CACHE_MAP_T));

    // 로고 이미지 크기도 읽어야 하지 않을까 ?
    image_size = afbc_sw_get_image_size(NULL, 1920, 1080);
    image_size = ALIGN(image_size, (1 << 20));

    /* read OSD0 framebuffer */
    rc = OS_RdReg(M23_CCO_BASE + 0x238, &fbmem_addr_src);
    FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "reg op fail\n");
    FBDEV_WARN("logo fbmem (old) = 0x%08x\n", fbmem_addr_src);

    if (!fbmem_addr_src)
    {
        FBDEV_NOTI("invalid boot logo address, skip !!\n");
        return;
    }

    /* (2020/05/21) code ready for surface poool set to CMA type
     * AS-IS: bootlogo image is copied to the last region of "surface" memrory pool
     * TO-BE: bootlogo image is copied to "debug0" memory pool
     *
     * 기존 방식은 surface 메모리풀의 특정 고정된 영역에 일방적으로 백업 이미지를 복사하는 것으로 CMA 속성에 대응이 불가하다.
     * 신규 방식에서는 debug0 에서 임시 메모리를 할당 받도록 한다.
     * 할당된 메모리는 fbdev_bootlogo_fbmem_addr 에 저장되며, FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE 에서 해제된다.
     */
    FBDEV_M23_TODO("M23 에서 dbbug0/1 을 지원할 것인가 ?")
    fbmem_addr_dst = hma_alloc(SAFE_LOGO_MEM_POOL, image_size, PAGE_SIZE);
    FBDEV_CHECK_ERROR(!fbmem_addr_dst, return, "dst bfufer alloc error\n");

    afbc_mode = (FBDEV_M23_CMN_GetHWStatus(FBDEV_M23_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0)) ? 1 : 0;

    if (mode == BOOT_LOGO_MODE_IMAGE_KEEP)
    {
        rc = OS_OpenCacheMap(&cmap_src, (ULONG)fbmem_addr_src, image_size);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "cache op fail\n");
        rc = OS_OpenCacheMap(&cmap_dst, (ULONG)fbmem_addr_dst, image_size);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "cache op fail\n");

        rc = OS_InvalCacheMap(&cmap_src, 0, image_size);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "cache op fail\n");

        memcpy(cmap_dst.virt_addr, cmap_src.virt_addr, image_size);

        rc = OS_CleanCacheMap(&cmap_dst, 0, image_size);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "cache op fail\n");
    }
    else /* mode = BOOT_LOGO_MODE_IMAGE_CLEAR, see SICDTV-8556 */
    {
        if (afbc_mode)
        {
            struct afbc_framebuffer* afbc_fb = afbc_sw_alloc_framebuffer(NULL,
                                               fbmem_addr_dst, 1920, 1080, 0, 0, 0);

            if (afbc_fb)
            {
                afbc_sw_fill(NULL, afbc_fb, 0x00000000);
                afbc_sw_free_framebuffer(NULL, afbc_fb);
            }
        }
        // ARGB raw 기반의 Logo 는 더이상 없으므로 대응하지 않겠음.
        else
        {
            FBDEV_WARN("ARGB mode - do nothing\n");
        }
    }

    FBDEV_M23_TODO("shadow register 방식으로 하는게 더 맞지 않나?")

    /* update AFBC0 framebuffer */
    if (afbc_mode)
    {
        rc = OS_WrReg(M23_CCO_AFBC0_BASE + 0x004, fbmem_addr_dst);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "reg op fail\n");

        AFBC_CTRL_Wr01(0, ctrl_afbc_1, hd_base,      fbmem_addr_dst);
        AFBC_CTRL_Wr01(0, ctrl_afbc_8, pl_data_base, fbmem_addr_dst);
        AFBC_CTRL_WrFL(0, ctrl_afbc_1);
        AFBC_CTRL_WrFL(0, ctrl_afbc_8);

        rc = OS_WrReg(M23_CCO_AFBC0_BASE + 0x020, fbmem_addr_dst);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "reg op fail\n");

        /* raxis.lim (2019/10/23)
         * becuase hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
         * we should set hdr_ready_flag=1 here to update real framebuffer address
         */
        AFBC_CTRL_RdFL(0, ctrl_afbc_0);
        AFBC_CTRL_Wr01(0, ctrl_afbc_0, update_ready_flag, 0x1);
        AFBC_CTRL_WrFL(0, ctrl_afbc_0);
    }

    /* update OSD framebuffer */
    for (i = 0; i < FBDEV_M23_MAX_OSD_BLK_NUM; i++)
    {
        OS_WrReg(OSD_CTRL_BASE(i) + 0x004, fbmem_addr_dst); // osd_base_addr
        OS_WrReg(OSD_CTRL_BASE(i) + 0x034, fbmem_addr_dst); // osd_ctrl_hdr5.ptr_plte
        OS_WrReg(OSD_CTRL_BASE(i) + 0x038, fbmem_addr_dst); // osd_ctrl_hdr6.ptr_bmp
    }

    /* raxis.lim (2019/10/23)
     * becuase osd_hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
     * we should set osd_hdr_ready_flagn=1 here to update real framebuffer address
     */
    OSDX_M23_RdFL(osdx_ctrl[0], osd_ctrl_main);
    OSDX_M23_Wr01(osdx_ctrl[0], osd_ctrl_main, osd_hdr_ready_flag_en, 1);
    OSDX_M23_Wr01(osdx_ctrl[0], osd_ctrl_main, osd_hdr_ready_flag, 1);
    OSDX_M23_WrFL(osdx_ctrl[0], osd_ctrl_main);

    fbdev_bootlogo_fbmem_addr = fbmem_addr_dst;
    FBDEV_NOTI("logo fbmem old=0x%08x new=0x%08x\n", fbmem_addr_src, fbmem_addr_dst);

func_exit:

    if (cmap_src.virt_addr)
    {
        OS_CloseCacheMap(&cmap_src);
    }

    if (cmap_dst.virt_addr)
    {
        OS_CloseCacheMap(&cmap_dst);
    }
}

/**
 *
 */
void FBDEV_M23_CMN_RunBootLogoTimer(UINT32 ms, BOOLEAN bForce)
{
#if (CONFIG_LX_BOOT_LOGO==1)
    static BOOLEAN      b_timer_req = TRUE;
    static OS_TIMER_T   osd_en_timer;

    if (b_timer_req || bForce)
    {
        b_timer_req = FALSE;
        FBDEV_BOOT_DEBUG("start boot timer %d ms (%d)\n", ms, bForce);

        if (ms > 0)
        {
            OS_InitTimer(&osd_en_timer);
            OS_StartTimer(&osd_en_timer, FBDEV_M23_CMN_EnableOSDHdrFlush, OS_TIMER_TIMEOUT, ms, 0x0);
        }
        else
        {
            FBDEV_M23_CMN_EnableOSDHdrFlush(0x0);
        }
    }

#else
    FBDEV_M23_CMN_EnableOSDHdrFlush(0x0);
#endif
}

/** query tcon clk information & detect vsync clk interval
 *
 *  @note this function should be called after SYS kdriver initialization
 */
static FBDEV_VSYNC_CLK_T FBDEV_M23_CMN_DetectVSyncClk(void)
{
#ifdef FBDEV_M23_USE_CTOP_REGS

    FBDEV_VSYNC_CLK_T clk;

    FBDEV_WARN("implement it !!\n");

    clk = FBDEV_VSYNC_CLK_60HZ;

    return clk;
#else
    FBDEV_NOTI("SYNC detector not ready.. default vsync = 60Hz\n");
    return FBDEV_VSYNC_CLK_60HZ;
#endif
}

static void FBDEV_M23_CMN_NotifyToPQEDriver(void)
{
#ifdef INCLUDE_KDRV_OVI
    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    /* see be/top/be_top_hal.h */
    extern int BE_TOP_HAL_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T * pstParams);
    LX_BE_FBDEV_STATUS_T osd2pqe_status;

    osd2pqe_status.bFbdevInitDone = hw_ctx->user_initcall_ctrl.status.osd_init_done;
    osd2pqe_status.bOsdVReverseOn = hw_ctx->user_initcall_ctrl.status.osd_v_mirror;
    osd2pqe_status.bEStreamerOn   = hw_ctx->user_initcall_ctrl.status.osd_estreamer;
    osd2pqe_status.b4kOSDResolution = (hw_ctx->b_support_4kosd) ? TRUE : FALSE;
    osd2pqe_status.bOsdSharpnessWAOn = FALSE;

    FBDEV_NOTI("+ notify PQE FW to setup : inited=%d, 4kosd=%d, vmirror=%d, est=%d, shpwa=%d\n",
               osd2pqe_status.bFbdevInitDone,
               osd2pqe_status.b4kOSDResolution,
               osd2pqe_status.bOsdVReverseOn,
               osd2pqe_status.bEStreamerOn,
               osd2pqe_status.bOsdSharpnessWAOn);

    FBDEV_CHECK_ERROR(RET_OK != BE_TOP_HAL_InformFBDEVStatus(&osd2pqe_status), /* nop */,
                      "BE_TOP_HAL_InformFBDEVStatus error\n");
#else
    FBDEV_NOTI("+ notify PQE FW to setup : dummy\n");
#endif
}

static int  FBDEV_M23_CMN_WaitForPQEDriverInitialization(void)
{
#ifdef INCLUDE_KDRV_OVI
    /* see be/top/be_top_hal.h */
    extern int BE_TOP_HAL_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T * pstParams);
    LX_BE_FW_OSD_STATUS_T pqe2osd_status;

    FBDEV_CHECK_ERROR(RET_OK != BE_TOP_HAL_GetFWOSDStatus(&pqe2osd_status), return RET_ERROR,
                      "BE_TOP_HAL_GetFWOSDStatus error\n");

    FBDEV_NOTI("+ wait for PQE FW to setup : %d/%d\n",
               pqe2osd_status.bFwOsdOrbitInitDone, pqe2osd_status.bFwOsdSrInitDone);

    if (pqe2osd_status.bFwOsdOrbitInitDone && pqe2osd_status.bFwOsdSrInitDone)
        return RET_OK;
    else
        return RET_TIMEOUT;

#else
    FBDEV_NOTI("+ wait for PQE FW to setup : dummy\n");
    return RET_OK;
#endif
}

/*========================================================================================
    Implementation Group (OSD HW Initialization)
========================================================================================*/

/** initialize HW SOC
 *
 *
 */
int FBDEV_M23_CMN_InitHW(void)
{
    int i;
    UINT32 disp_width, disp_height;
    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    int bosd_num = FBDEV_M23_BOSD_NUM;

    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> user_initcall not ready +++\n");

    disp_width = hw_ctx->hw_disp_width;
    disp_height = hw_ctx->hw_disp_height;

    FBDEV_HW_DEBUG("(Re)Init OSD(O20) HW.. disp_size %dx%d\n", disp_width, disp_height);

    /* initialize B.OSD mixer disp size */
    for (i = 0; i < bosd_num; i++)
    {
        OSDX_M23_RdFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size);
        OSDX_M23_Wr02(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size, reg_bosd_disp_size_w, hw_ctx->bosd_disp.out_width,
                      reg_bosd_disp_size_h, hw_ctx->bosd_disp.out_height);
        OSDX_M23_WrFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size);
    }

    /* setup all OSD common disp size */
    for (i = 0; i < FBDEV_M23_MAX_OSD_DISP_NUM; i++)
    {
        OSD_M23_RdFL(osdx_common_disp_size[i]);
        OSD_M23_Wr02(osdx_common_disp_size[i], reg_common_disp_size_w, disp_width,
                     reg_common_disp_size_h, disp_height);
        OSD_M23_WrFL(osdx_common_disp_size[i]);
    }

    /* O20 has the fixed mux value. DO NOT change */
    {
        UINT32 mixer_mux_value = 0x76543210;
        FBDEV_NOTI("(Re)Init OSD(O20) mixer mux order = 0x%08x\n", mixer_mux_value);

        OSDX_M23_Wr(osdx_blend_osd_mixer[0], ctrl_bosd_mixer_mux1, mixer_mux_value);
        OSDX_M23_WrFL(osdx_blend_osd_mixer[0], ctrl_bosd_mixer_mux1);
    }

    /* raxis.lim (2014/11/11) tune osd sync pulse timer
     * CCO_CTRL.CTRL_SOSD_PLUS.reg_disp_sosd_timer controls the delay the OSD mix start time in cycle unit.
     * OSD HW engineer recommend to use 0x3000 (almost 10 line delay) can fix OSD sync & isr mismatch issue.
     *
     * value 0x3000 has been determinted at H15 development
     *
     * raxis.lim (2016/03/28) set bosd_pulse as 0x3000 (used at O20 for the first time)
     *
     */
    OSD_TOP_M23_RdFL(ctrl_bosd_pulse);
    OSD_TOP_M23_Wr01(ctrl_bosd_pulse, reg_disp_pulse_timer, hw_ctx->bosd_disp.pulse_timer_dly);
    OSD_TOP_M23_WrFL(ctrl_bosd_pulse);

    FBDEV_M23_CMN_InitMirrorEnv();
    FBDEV_M23_CMN_InitCropEnv();
    FBDEV_M23_CMN_InitFBCEnv();

    return RET_OK;
}

/** make OSD to be initial state
 *  make the basic configuration for each OSD layer.
 *
 *  @param layerId
 */
int FBDEV_M23_CMN_InitOSDLayer(int fb_dev_id)
{
    int i;
    int xidx;
    int xnum, xlst[2];
    int ret = RET_ERROR;

    /* please refer to OSD manual OSD<x>_CFG field */
    UINT32  hdr_src_sel;
    UINT32  osd_memhdr_addr;
    //BOOLEAN osd_en = 0x0;       /* off by default */
    BOOLEAN hdr_rdy_flag = 0x0; /* OFF by default */
    BOOLEAN v_mirror_en = 0x0;  /* OFF by default */

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_M23_MIRROR_CTRL_T* mirror_ctrl = FBDEV_M23_GET_MIRROR_CTRL(hw_ctx);

    // fetch the current output disp size
    UINT32  disp_width = hw_ctx->hw_disp_width;
    UINT32  disp_height = hw_ctx->hw_disp_height;

    // if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration)  */
    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready,
                     return RET_OK,
                     "<i> fb(%d) user_initcall not ready +++\n", fb_dev_id);

    // (2022/01/28)
    // M23 에서는 fb(0) 과 fb(1) 이 모두 동일한 OSD0 에 연동되므로, fb(0) 기반의 초기화면 진행하면 된다.
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        FBDEV_NOTI("fb(%d) ignore. both fb(0) and fb(1) share the same HW\n", fb_dev_id);
        return RET_ERROR;
    }

    FBDEV_NOTI("fb(%d) configure osd layer...\n", fb_dev_id);

    xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

    /* hdr_src_sel 0x0: DDR, 0x1: REG */
    hdr_src_sel = (g_fbdev_hwio_cfg->hdr_op_method == FBDEV_HDR_OP_MMIO) ? 0x0 : 0x1;
    osd_memhdr_addr = (gMemCfgFBHdr[fb_dev_id].mem_header_base);

    v_mirror_en = (mirror_ctrl->status & FBDEV_M23_V_MIRROR_ON) ? 0x1 : 0x0;

    // (2022/05/12)
    // boot 에서 logo 출력 없이 수행될 수 있으므로, 여기서는 OSD enable 하지 않도록 한다.
    // 대신 1st framebuffer 업데이트 실행시 fb(0) 을 enable 시킨다.
    //
    // see http://clm.lge.com/issue/browse/SDMSTH-70
    // see https://harmony.lge.com:8443/issue/browse/SICBIT-1609
#if 0

    // choose the initial osd visibility based on boot logo configuration
    switch (fb_dev_id)
    {
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==0)

        case LX_FBDEV_ID_OSD0:
            osd_en = 0x1;
            break;
#endif

        default:
            osd_en = 0x0;
            break;
    }

#endif

#ifdef FBDEV_M23_USE_HDR_RDY_REG
    hdr_rdy_flag = 0x1;
#endif

    for (i = 0; i < xnum; i++)
    {
        UINT32  sync_disp_width;
        UINT32  sync_hdouble_en;
        UINT32  ctrl_direc;

        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), goto func_exit, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

        /* raxis.lim (2016/03/28)
         * if BLEND mode, each OSD layer should have a half of real disp size. (it's HW spec)
         * this restruction is also applied to the cursor layer.
         *
         * M23 = B.OSD 고정
         *
         * (2022/02/11)
         * 기존 칩과 달리 M23 은 sync_disp_width 가 disp_width 의 1/2 이 아니다.
         * (참고) UI layer 에서는 sync_disp_width 가 없어 설정값 영향이 없다.
         *        cursor layer 에서만 영향을 준다.
         */
        sync_disp_width = disp_width;

        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_pdec);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_swap);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_base_addr);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_sync1);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_scaler);


        /* (2020/12/15) remove the early osd_en control
         * osd will be enabled after the frist image update is completed
         * see FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE handler
         * see http://clm.lge.com/issue/browse/SICDTV-9043
         * see http://hlm.lge.com/qi/browse/INQAISSUE-81
         */
#if 0
        /* OSD HW requests to write both osd_en & osd_sync_enable to control osd visibility */
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main,   osd_en,         osd_en);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0,  osd_sync_enable, osd_en);
#endif

        /* raxis.lim (2014/06)
         * if BLEND mode, each OSD layer should have a half of real display size (it's HW spec)
         * this restruction is also applied to the cursor layer.
         *
         * M23 = B.OSD 고정
         */
        sync_hdouble_en = 0x0;

        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_hdouble_en, sync_hdouble_en);

        /* use osd_hdr_flag to avoid the possible OSD mis-configuration when OSD header is set across vsync */
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_ready_flag_en, hdr_rdy_flag);

        /* normally osd_hdr_src_sel is fixed to "read from hw register" not "DDR contains osd_hdr data" */
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_src_sel,      hdr_src_sel);

        /* configure mirror mode every layer initialization */
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en,     v_mirror_en);

        /* configure CSR0 sync for mirror mode to support virtically reversed position */
        if (fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_CSR0)
        {
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_v_reverse, v_mirror_en);
        }

        /* we should set DDR memory to hold osd_hdr data, but NOT used in normal case
         * remember that OSD always fetch header data from DDR regardless of hdr_src_sel value
         * it's safe that I set the same address as the frame buffer
         */
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_base_addr, osd_base_addr, osd_memhdr_addr);

#if 0 /* KEEP HW DEFAULT */
        /* set scaler sample mode to the same behavior as that of GFX */
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler, osd_sc_sampling_mode,    0x1);
#endif

        // initialize cursor attribute. OSD(4) only)
        if (fb_dev_id == LX_FBDEV_ID_CSR0)
        {
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler, reg_crsr_h_x2_en, 0x0);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler, reg_crsr_v_x2_en, 0x0);

            // (2022/10/19) 커서의 input, output dimension 을 의도한 HW 기본 설정값(0x0)으로 초기화 필요함
            // see http://clm.lge.com/issue/browse/SICDTV-11784, http://clm.lge.com/issue/browse/SDMSTH-405
            FBDEV_NOTI("++ SICDTV-11784: initialize cursor dimension\n");

            OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr1);
            OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr2);

            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_hdr1, osd_hdr_w_mem, 0);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_hdr1, osd_hdr_h_mem, 0);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_w_out, 0);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_h_out, 0);

            OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr1);
            OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);

            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_ready_flag, 0x1);
        }

#if 0 /* KEEP HW DEFAULT */
        /* MIF feeder cfg : "10 (0x2)" L to R (HW default value)
         * this value has ben fixed to "10" inside OSD HW since older chip.
         * In O20/O20, this value can be configurable by SW But I keep this value as 0x2 forever
         *
         * HW default value = 0x2
         */
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main,   osd_manual_dlr,     0x2);
#endif

        /* raxis.lim (2019/10/17) -- fix pdec & swap configuration. re-write HW default again.
         *
         * pdec=0xe4000000, swap=0x000 equals pdec=0x1b000000, swap=0x333
         *
         */
        FBDEV_M23_TODO("pdec, swap 값 조합에 따라, 색이 이상하게 나올수 있으니, 이상하면 설정 찾자")
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_alpha,           0x0);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_red,             0x1);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_green,           0x2);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_blue,            0x3);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_round,              0x0);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_pure_ck,            0x0);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_lfsr_seed,          0x0);

        OSDX_M23_Wr(osdx_ctrl[xidx], osd_ctrl_swap, 0x00000333);

#ifdef FBDEV_M23_USE_EXPERIMENTAL_CONFIG

        /* raxis.lim (2018/04/09)
         * according to register manual, reg_osd_buf_mode_en enables for OSD to use scaler memory as extra line memory
         * during 1:1 non-scaler mode.
         * when UHD display mode, FHD image is always scaled to UHD-sized output image. so it's good to set osd_buf_mode_en as 0x0.
         * when FHD display mode, FHD image is not scaled, so it's good to set osd_buf_mode_en as 0x1
         *
         * @note refer to SICDTV-4852
         *
         */
        if (fb_dev_id == LX_FBDEV_ID_OSD0 && xidx == 0x0)
        {
            UINT32 buf_mode_en = (FBDEV_M23_CMN_IsUHDDispMode()) ? 0x0 : 0x1;
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler, reg_osd_buf_mode_en_n, buf_mode_en);
        }

#endif
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_pdec);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_swap);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_base_addr);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_scaler);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);

        /* TODO: add more initialization if necessary */

        // setup OSD basic path & sync. primary osd only.
        //
        // raxis.lim (2019/05/21)
        // OSD_IMAGE0_1 doesn't have osd_ctrl_path, osd_ctrl_sync etc
        //
        // M23 에서는 OSD0 의 ctrl_path 가 RSVD 임. 알고 있을 것
        //
        // M23 = B.OSD 고정
        if (i == 0x0)
        {
            OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_path);
            ctrl_direc = 0x0; // B.OSD 고정
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_direc, ctrl_direc);

            FBDEV_M23_TODO("위 osd_ctrl_eo2s 삭제 여부 확인할것")
            // M23 삭제
            // 해당 필드가 없음
            //OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_eo2s,  ctrl_direc);

            FBDEV_M23_TODO("OSD0 에 대한 ctrl_path 는 RSVD 임")
            // setup each display size(?).
            // keep in mind that width value osd_ctrl_path, osd_ctrl_sync1 is NOT real disp_width.
            // they should be set a half when B.OSD is activated.
            // these field is used to control how OSD fetch & process OSD frame data.
            //
            // SW 적으로는 BOSD[0] 으로 처리하겠지만, 실제 HW 에서의 BOSD 위치는 BOSD1 이다.
            // BOSD1 은 tcon 바로 앞을 의미한다.
            // 개념 헷갈리지 말것
            //
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_path, reg_ctrl_path_width, sync_disp_width);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_bosd_pos, 0x0);   /* fixed to 0x0(BOSD1) */
            OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_path);

            OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_sync1);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_sync1, osd_sync_disp_w, sync_disp_width);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_sync1, osd_sync_disp_h, disp_height);
            OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_sync1);
        }

        // (2022/03/31) M23 변경 사항
        // scaler in/out size  추가 설정 필요
        // http://clm.lge.com/issue/browse/SICDTV-11111?focusedCommentId=3943685&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3943685
        if (fb_dev_id == LX_FBDEV_ID_OSD0 && xidx == 0x0)
        {
            OSDX_M23_RdFL(osdx_ctrl[xidx], osd0_scaler_in_size);
            OSDX_M23_RdFL(osdx_ctrl[xidx], osd0_scaler_out_size);

            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_scaler_in_size, reg_scaler_in_width, hw_ctx->hw_fb0_width);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_scaler_in_size, reg_scaler_in_height, hw_ctx->hw_fb0_height);

            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_scaler_out_size, reg_scaler_out_width, disp_width);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_scaler_out_size, reg_scaler_out_height, disp_height);

            OSDX_M23_WrFL(osdx_ctrl[xidx], osd0_scaler_in_size);
            OSDX_M23_WrFL(osdx_ctrl[xidx], osd0_scaler_out_size);
        }

        // (2021/01/28)
        // M23 에서는 4KOSD 지원하지 않음. 해당 코드 삭제함
    }

    ret = RET_OK;   /* all work done */
func_exit:
    return ret;
}

static void FBDEV_M23_CMN_SafeSyncEnable(void)
{
    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    /* if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration) */
    FBDEV_CHECK_ERROR(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");

    FBDEV_WARN("++ PIC_INIT ++ (I-BOOT)\n");

    // (2019/08/07)
    // pic_init 는 OSD 전용이 아니므로 필요한 bit 설정만 해야 한다.
    // O20+F20 의 chip info 전달에 문제를 읽으키 사례가 있다.
    // refer to http://clm.lge.com/issue/browse/AVTASK-386?focusedCommentId=1964037&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-1964037
    //
    FBDEV_M23_TODO("M23 은 g0, g4 만 있을것 같음. g1 은 동작하지 않을듯")
    OSD_TOP_M23_RdFL(pic_init);
    OSD_TOP_M23_Wr01(pic_init, g0_auto_init, 0x1);
    OSD_TOP_M23_Wr01(pic_init, g1_auto_init, 0x1);
    OSD_TOP_M23_Wr01(pic_init, g4_auto_init, 0x1);
    OSD_TOP_M23_WrFL(pic_init);
}

static void FBDEV_M23_CMN_ReInitHW(void)
{
    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");

    FBDEV_M23_InitHW();
    FBDEV_SetInterruptEnable(MIXER_INTR, 1);

    // 통상적으로 fb(0), fb(1), fb(3) 을 지원한다.
    FBDEV_M23_CMN_InitOSDLayer(LX_FBDEV_ID_OSD0);
    FBDEV_M23_CMN_InitOSDLayer(LX_FBDEV_ID_OSD1);
    FBDEV_M23_CMN_InitOSDLayer(LX_FBDEV_ID_OSD3);

    // refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT
    // M23 에서는 사용할 필요 없으나, 유사시 대비하여 코드는 유지함
    if (hw_ctx->hw_wa_flag & FBDEV_M23_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)
    {
        FBDEV_M23_CMN_SafeSyncEnable();
    }
}

int FBDEV_M23_CMN_ExecHWCommand(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data)
{
    int ret = RET_NOT_SUPPORTED;
    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    switch (cmd)
    {
        case FBDEV_HW_CMD_IO_POST_HW_INIT:
        {
            fbdev_m23_wq = alloc_workqueue("fbdev_m23_events", 0, 0);

            if (fbdev_enable_logo_clear)
            {
                FBDEV_NOTI("start logo clear work after %dms\n", fbdev_boot_logo_clear_timeout);
                queue_delayed_work(fbdev_m23_wq, &boot_logo_clear_work, msecs_to_jiffies(fbdev_boot_logo_clear_timeout));
            }
        }
        break;

        case FBDEV_HW_CMD_IO_POSD_OPEN:
        {
            int fbdev_id = data->gen[0];
            struct fb_info* fbinfo = (struct fb_info*)data->genex[0];

            FBDEV_HW_DEBUG("fb(%d) device open. do chip handler\n", fbdev_id);
            FBDEV_M23_CMN_RunBootLogoTimer(fbdev_boot_freeze_timeout, FALSE);

            FBDEV_M23_CMN_SetupExternalRenderer(fbdev_id, fbinfo);

            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_IO_USER_POSD_RESOL_CHANGED:
        {
            // int fbdev_id = data->gen[0];
            // add code if necesssary
            FBDEV_NOTI("FBDEV_HW_CMD_IO_USER_POSD_RESOL_CHANGED not supported\n");

            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_IO_VSYNC:
        {
            FBDEV_M23_CMN_ISRHook();
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_RD_VSYNC_CLK:
        {
            data->gen[0] = FBDEV_M23_CMN_DetectVSyncClk();

            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_RD_DISP_SIZE:
        {
            data->gen[0] = hw_ctx->hw_disp_width;
            data->gen[1] = hw_ctx->hw_disp_height;

            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_RD_POSD_MAX_RES_CAPS:
        {
            int fbdev_id = data->gen[0];

            if (fbdev_id == LX_FBDEV_ID_OSD0)
            {
                data->gen[0] = LX_MAKE_RES(hw_ctx->hw_fb0_width, hw_ctx->hw_fb0_height);
                data->gen[1] = 2; /*afbc*/
                data->gen[2] = 0; /*system default*/
            }
            else if (fbdev_id == LX_FBDEV_ID_OSD1)
            {
                data->gen[0] = LX_MAKE_RES(hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height);
                data->gen[1] = (fbdev_afbc_estreamer) ? 2 /*afbc*/ : 1 /*argb*/;
                data->gen[2] = FBDEV_M23_EXT_RENDER_EGL_FBDEV_NUM;
            }
            else
            {
                data->gen[0] = 0x0;
                data->gen[1] = 0x0;
                data->gen[2] = 0x0;
            }

            if (data->gen[0] != 0x0) ret = RET_OK;

            //printk("fb(%d) ret=%d, 0x%x, 0x%0x, 0x%0x, 0x%0x\n", fbdev_id, ret, data->gen[0], data->gen[1], data->gen[2], data->gen[3]);
        }
        break;

        case FBDEV_HW_CMD_RD_AFBC_CAPS:
        {
            data->gen[0] = fbdev_afbc_version;
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_FREEZE:
        {
#ifdef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL
            // (2017/09/18) disable PQEFW_OSD0_OUT_CTRL. ORBIT control will be re-enabled at THAW & RESTORE
            hw_ctx->hw_wa_flag &= ~FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL;
#endif
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_SUSPEND:
        {
            fbdev_hw_pm_suspend_stage = 1;

            if (fbdev_use_shutdown_path_on_suspend)
            {
                FBDEV_M23_CMN_ShutdownOSDPath();
            }

#ifdef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL
            // (2017/09/18) disable PQEFW_OSD0_OUT_CTRL to re-enable at FBDEV_M23_CMN_EnableOSDHdrFlush() during RESUME
            hw_ctx->hw_wa_flag &= ~FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL;
#endif
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_THAW:
        {
#ifdef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL
            // (2017/09/18) enable PQEFW_OSD0_OUT_CTRL here becuase THAW stage doesn't configure any HW registers
            hw_ctx->hw_wa_flag |= FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL;
            FBDEV_WARN("OSD0_PQEFW_OSD0_OUT_CTRL enabled\n");
#endif
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_RESTORE:
        {
            fbdev_hw_pm_restore_stage = 1;

            // boot logo migration is also required during snapshot boot
            fbdev_logo_migration_required = TRUE;
            FBDEV_M23_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_CLEAR);

            if (fbdev_enable_logo_clear)
            {
                FBDEV_NOTI("start logo clear work after %dms (resume mode)\n", fbdev_resume_logo_clear_timeout);
                queue_delayed_work(fbdev_m23_wq, &boot_logo_clear_work, msecs_to_jiffies(fbdev_resume_logo_clear_timeout));
            }

            // (2010/06/11) re-activate lazy-init at snapshot boot
            hw_ctx->user_initcall_ctrl.ready = FALSE;
            hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

            // (2017/09/18) DO NOT set any PQEFW_OSD0_OUT_CTRL attribute.
            // it will be enabled at FBDEV_M23_CMN_EnableOSDHdrFlush()

            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_RESUME:
        {
            // (2017/08/22) fix for async behavior of OSD0_SYNC group
            hw_ctx->hw_wa_flag |= FBDEV_M23_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
            FBDEV_WARN("OSD0_SYNC_ASYNC_WR enabled\n");

            // (2010/06/11) re-activate lazy-init at QSM+ resume
            hw_ctx->user_initcall_ctrl.ready = FALSE;
            hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

            // (2017/09/18) DO NOT set any PQEFW_OSD0_OUT_CTRL attribute.
            // it will be enabled at FBDEV_M23_CMN_EnableOSDHdrFlush()
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_COMPLETE:
        {
            fbdev_hw_pm_suspend_stage = 0;
            fbdev_hw_pm_restore_stage = 0;

            hw_ctx->hw_wa_flag &= ~FBDEV_M23_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_USER_INITCALL_PREPARE:
        {
            int  fbdev_id = data->gen[0];

            FBDEV_NOTI("fb(%d) INITCALL_PREPARE\n", fbdev_id);

            // raxis.lim (2010/06/11)
            // (re)initialize OSD HW at user frame update not at kdriver initialization !!
            //
            // (2023/01/19) DRM cursor 단독 테스트에서도 OSD 초기화 진행이 되어야 함
            // 따라서 OSD0 체커 삭제하고, 초기화 중복 여부 코드만 살림
            // see http://clm.lge.com/issue/browse/SCDCR-5652
            // if (fbdev_id == LX_FBDEV_ID_OSD0 && !hw_ctx->user_initcall_ctrl.ready)
            if (!hw_ctx->user_initcall_ctrl.ready)
            {
                hw_ctx->user_initcall_ctrl.ready = TRUE;
                FBDEV_M23_CMN_ReInitHW();
            }
        }
        break;

        // USER_INITCALL_COMPLETE 는 모든 OSD 설정의 완료를 의미하므로, 반드시 PQE FW 쪽으로 제어권을 넘겨야 한다.
        // 즉 FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL 플래그 설정이 가장 중요
        case FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE:
        {
            int i;
            int fbdev_id = data->gen[0];

            FBDEV_NOTI("fb(%d) INITCALL_COMPLETE\n", fbdev_id);

            // (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume
            if (fbdev_id == LX_FBDEV_ID_OSD0)
            {
                UINT64 base_tick;
                FBDEV_M23_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

#ifdef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL

                if (hw_ctx->b_support_ext_frc || hw_ctx->hw_disp_width <= 2048)
                {
                    fbdev_pqefw_osd0_out_ctrl = 0;
                    hw_ctx->hw_wa_flag &= ~FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL;
                    FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL disabled\n");
                }
                else
                {
                    hw_ctx->hw_wa_flag |= FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL;
                    FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
                }

#endif
                hw_ctx->user_initcall_ctrl.status.osd_init_done = 1;
                hw_ctx->user_initcall_ctrl.status.osd_v_mirror = (mirror_ctrl->status == FBDEV_M23_V_MIRROR_ON) ? 1 : 0;
                hw_ctx->user_initcall_ctrl.status.osd_estreamer = 0;

                // (2022/05/12)
                // boot logo 없이 부팅되더라도 1st framebuffer 업데이트시에 자동으로 업데이트 되게 한다.
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==0)
                FBDEV_NOTI("fb(%d) show OSD with USER_INITCALL\n", fbdev_id);
                FBDEV_M23_CMN_SetOSDEnable(fbdev_id, TRUE);
#endif
                FBDEV_M23_CMN_NotifyToPQEDriver();

                base_tick = OS_GetMsecTicks();

                for (i = 0; i < 10; i++)
                {
                    // if (FW wait time > 100 ms ) break
                    FBDEV_CHECK_NOTI((int)(OS_GetMsecTicks() - base_tick) > 100, break,
                                     "+ wait timeout\n");

                    if (RET_OK == FBDEV_M23_CMN_WaitForPQEDriverInitialization()) break;

                    msleep_interruptible(10);
                }

                // destroy temporary boot logo framebuffer
                if (fbdev_bootlogo_fbmem_addr)
                {
                    FBDEV_NOTI("destroy logo fbmem 0x%08lx\n", fbdev_bootlogo_fbmem_addr);

                    hma_free(SAFE_LOGO_MEM_POOL, fbdev_bootlogo_fbmem_addr);
                    fbdev_bootlogo_fbmem_addr = 0x0;
                }
            }
        }
        break;

        case FBDEV_HW_CMD_RD_EXTERNAL_RENDERER_INFO:
        {
            FBDEV_M23_TODO("이거 넘겨 주는것 맞나?")
            data->gen[0] = LX_FBDEV_ID_OSD1;
        }
        break;

        case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_CONFIGURE_CROP_REGION:
        {
            int fbdev_id = data->gen[0];
            int cx = LX_RES_GET_WIDTH(data->gen[1]);
            int cy = LX_RES_GET_HEIGHT(data->gen[1]);
            int cw = LX_RES_GET_WIDTH(data->gen[2]);
            int ch = LX_RES_GET_HEIGHT(data->gen[2]);

            FBDEV_M23_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_M23_GET_EXT_RENDER_CTRL(hw_ctx);

            // crop 정보는 다음 이미지 업데이트에 연동하여 동작하는 것인 자연스러운 동작성을 보임
            // 따라서 여기서는 단지 변수값만 보관함
            ext_render_ctrl->hwparam.crop_x = cx;
            ext_render_ctrl->hwparam.crop_y = cy;
            ext_render_ctrl->hwparam.crop_w = cw;
            ext_render_ctrl->hwparam.crop_h = ch;

            FBDEV_NOTI("++ configure external render fb(%d) crop %d,%d,%d,%d\n", fbdev_id, cx, cy, cw, ch);
        }
        break;

        // (2021/07/08) O208K, E608K 의 경우는 fbdev_drv.c 에서 호출이 되었으나, O22 8k, M23 의 경우는
        // 일반 OSD 처럼 입력되어 처리되어야 하므로, fbdev_drv.c 에서 호출되지 않는다.
        // SW 구조를 유지하기 위하여 fbdev_hw_m23_cmn.c 에서 호출하도록 조치한다.
        // 수정된 IPC 에서는 crop_x,y,w,h 정보와 xoffset, enable 정보만 전달된다.
        case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE:
        {
            LX_RECT_T crop_rgn;

            int    fbdev_id = data->gen[0];
            //UINT32 phys_y = data->gen[1];
            int    xoffset  = data->gen[2];
            int    yoffset  = data->gen[3];


            FBDEV_M23_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_M23_GET_EXT_RENDER_CTRL(hw_ctx);

            // fake vsync 는 현재 체제 그대로 사용한다.
            {
                UINT64 sleep_tick_us = 0;
                UINT64 curr_tick_us = OS_GetUsecTicks();
                UINT64 diff_tick_us = curr_tick_us - ext_render_ctrl->swsync.request_tick_us;

                if (diff_tick_us < ext_render_ctrl->swsync.interval_tick_us)
                {
                    sleep_tick_us = ext_render_ctrl->swsync.interval_tick_us - diff_tick_us;
                    FBDEV_HW_NOTI("++ swsync usleep %d us\n", (int)sleep_tick_us);
                    usleep_range(sleep_tick_us, sleep_tick_us);
                }
            }

            ext_render_ctrl->hwparam.xoffset = xoffset;
            ext_render_ctrl->hwparam.yoffset = yoffset;

            crop_rgn.x = ext_render_ctrl->hwparam.crop_x;
            crop_rgn.y = ext_render_ctrl->hwparam.crop_y;
            crop_rgn.w = ext_render_ctrl->hwparam.crop_w;
            crop_rgn.h = ext_render_ctrl->hwparam.crop_h;

            // 여러 프로세스가 혼재되어 동작하게 되므로, osd0 의 소유권을 반드시 확인할것
            FBDEV_CHECK_CODE(hw_ctx->hw_osd0_owner != fbdev_id,
                             break,
                             "++ fb(%d) ignore. not hw_osd0_owner\n", fbdev_id);

            FBDEV_M23_CMN_SetExternalRenderCropRegion(TRUE, hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height, xoffset, yoffset,
                    &crop_rgn);

            ext_render_ctrl->swsync.request_tick_us = OS_GetUsecTicks();
        }
        break;

        /* PQE PM framework callback */
        case FBDEV_HW_CMD_WR_PQE_PM_RUNTIME_ACTION:
        {
#ifdef INCLUDE_KDRV_PQE_PM
            int pqe_pm_action = data->gen[0];

            if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_PREPARE)
            {
                // (2023/11/06) suspend 에 준하는 동작 필요 (불필요한 PQE IPC 무시 등)
                // see FBDEV_M23_CMN_WaitPQEDriverEstreamerSync()
                fbdev_hw_pm_suspend_stage = 1;

                /* OSD 를 모두 끄는 것이 테스트에 도움이 될 것임 */
                FBDEV_M23_CMN_ShutdownOSDPath();
                FBDEV_PM_DEBUG("hide all OSD layer for safe operation\n");

                FBDEV_M23_CMN_SetInterruptEnable(MIXER_INTR, FALSE);

                // PQE 에서 1/64 freq down 정책으로 사용하기 때문에, pic_init 에 대한 제어를 하지 않아도 됨
                // 추후 필요하다 판단시 아래 코드를 사용할것
                // 참고 http://clm.lge.com/issue/browse/SICDTV-10087?focusedCommentId=3185554&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3185554
                // 필요시 이전 패치셋을 확인할것

                // TODO: 필요시 추가할것

            }
            else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND)
            {
                // TODO: 필요시 추가할것
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_COMPLETED)
            {
                // TODO: 필요시 추가할것
                fbdev_hw_pm_suspend_stage = 0;
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_PREPARE)
            {
                // TODO: 필요시 추가할것
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_RESUME)
            {
                // PQE 에서 1/64 freq down 정책으로 사용하기 때문에, pic_init 에 대한 제어를 하지 않아도 됨
                // 추후 필요하다 판단시 아래 코드를 사용할것
                // 참고 http://clm.lge.com/issue/browse/SICDTV-10087?focusedCommentId=3185554&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3185554
                // 필요시 이전 패치셋을 확인할것

                // TODO: 필요시 추가할것
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_COMPLETED)
            {
                /* TODO: 필요시 OSD0 에 대하여 enable 시킬 수도 있음 */

                FBDEV_M23_CMN_SetInterruptEnable(MIXER_INTR, TRUE);
            }
            else
            {
                // not supported action
            }

#endif
            ret = RET_OK;
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }

    return ret;
}

// enable interrupt
int FBDEV_M23_CMN_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable)
{
    //FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    switch (intr)
    {
        // MIXER interrupt 만 사용함
        // M23 = B.OSD 고정
        case MIXER_INTR:
        default:
        {
            OSD_M23_RdFL(osd_common_ctrl_irq);

            FBDEV_DEBUG("INTR <%s> for B.OSD\n", enable ? "ON" : "OFF");
            OSD_M23_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bos, enable);
            OSD_M23_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sos, 0x0);

            OSD_M23_WrFL(osd_common_ctrl_irq);
        }
        break;
    }

    return RET_OK;
}

// get interrupt status
int FBDEV_M23_CMN_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
    UINT32 osd_mixer;
    UINT32 status = 0;

    //FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    OSD_M23_RdFL(osd_common_ctrl_irq);

    // M23 = B.OSD 고정
    {
        OSD_M23_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, osd_mixer);

        if (osd_mixer) status |= (1 << MIXER_INTR);
        else           printk("OSD ISR - BOSD MIXER INTR error\n");
    }

    FBDEV_ISR_DEBUG("irq reg info = 0x%08x\n", status);

    return status;
}

// clear interrupt status
int FBDEV_M23_CMN_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
    OSD_M23_RdFL(osd_common_ctrl_irq);

    /* clear both bosd, sosd mixer intr for the safe operation */
    OSD_M23_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, 0x1);
    OSD_M23_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, 0x1);

    OSD_M23_WrFL(osd_common_ctrl_irq);

    return RET_OK;
}

/*========================================================================================
    Implementation Group (OSD Hdr Processing)
========================================================================================*/
/** setup external render if necessary
 *
 */
static void FBDEV_M23_CMN_SetupExternalRenderer(int fb_dev_id, struct fb_info* fbinfo)
{
    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_M23_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_M23_GET_EXT_RENDER_CTRL(hw_ctx);

    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        ext_render_ctrl->swsync.interval_tick_us = 1000000 / hw_ctx->hw_ext_render_swsync_hz;
    }

    // TBD
}

static void FBDEV_M23_CMN_AllocExternalRendererFrameBuffer(void)
{
    // TBD
}

static void FBDEV_M23_CMN_DestroyExternalRendererFrameBuffer(void)
{
    // TBD
}

// E-Streamer 전용으로 display 위치와 crop 정보를 일괄 설정한다.
// o20 8k, o22 8k 에서 PQE FW 동작성을 에뮬레이션한다.
//
static void FBDEV_M23_CMN_SetExternalRenderCropRegion(BOOLEAN crop_en, int img_width, int img_height, int xoffset,
        int yoffset, LX_RECT_T* crop_rgn)
{
    int i;
    int xidx;
    int xnum, xlst[2];
    int fb_dev_id = LX_FBDEV_ID_OSD1;

    FBDEV_CHECK_ERROR(!crop_rgn, return, "null param\n");

    xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);
    /* ignore noisy warning msg becase some OSD layer is not supported by HW */
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_HW_NOTI("fb(%d) crop=%s image=%dx%d, x=%d, y=%d, crop_rgn=%d,%d,%d,%d\n",
                  fb_dev_id,
                  crop_en ? "on" : "off",
                  img_width, img_height,
                  xoffset, yoffset, crop_rgn->x, crop_rgn->y, crop_rgn->w, crop_rgn->h);

    for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
    {
        xidx = xlst[i];

        OSDX_M23_RdFL(osdx_ctrl[xidx], osd0_post_crop_ctrl_0);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd0_post_crop_ctrl_1);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd0_post_crop_ctrl_2);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd0_post_crop_ctrl_3);

        OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_0, reg_crop_en, crop_en);

        if (fb_dev_id == LX_FBDEV_ID_OSD1)
        {
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_0, reg_in_pic_width, img_width);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_0, reg_in_pic_height, img_height);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_1, hoffset, crop_rgn->x);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_1, hactive, crop_rgn->w);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_2, voffset, crop_rgn->y);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_2, vactive, crop_rgn->h);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_3, crop_mixer_xpos, xoffset);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_post_crop_ctrl_3, crop_mixer_ypos, yoffset);
        }

        OSDX_M23_WrFL(osdx_ctrl[xidx], osd0_post_crop_ctrl_0);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd0_post_crop_ctrl_1);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd0_post_crop_ctrl_2);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd0_post_crop_ctrl_3);
    }
}

/** detect current mirror mode configuration set by boot loader
 *
 */
static void FBDEV_M23_CMN_InitMirrorEnv(void)
{
    int xidx;
    int xnum, xlst[2];
    int fb_dev_id = LX_FBDEV_ID_OSD0;

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_M23_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

    xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

    xidx = xlst[0];
    FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

    /* raxis.lim (2018/07/02) -- read mirror mode configuration set from boot loader */
    if (mirror_ctrl->status == FBDEV_M23_MIRROR_NONE)
    {
        UINT32 hw_val;

#ifdef V_MIRROR_TEST
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, 0x1);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
#endif
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_M23_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, hw_val);

        mirror_ctrl->status = (hw_val) ? FBDEV_M23_V_MIRROR_ON : 0x0;

        FBDEV_WARN("OSD v_mirror detected (%d)\n", hw_val);
    }
}

static void FBDEV_M23_CMN_SetupSRScaler(BOOLEAN onoff, BOOLEAN bForce)
{
    // N/A
}

/** initialize CROP to the default state.
 *
 */
static void FBDEV_M23_CMN_InitCropEnv(void)
{
    /* do nothing */
}

/** initialize FBC variable to the default state.
 *  The real HW register will be set inside FBDEV_M23_CMN_WriteOSDHeader()
 *  This function is also called during instant boot resume to setup AFBC register again.
 *
 */
static void FBDEV_M23_CMN_InitFBCEnv(void)
{
#ifdef FBDEV_M23_USE_FBC_CTRL
    int i;

    // raxis.lim (2010/10/15) -- setup afbc for both fb(0) and fb(1)
    for (i = 0; i <= LX_FBDEV_ID_OSD1; i++)
    {
        FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
        FBDEV_M23_FBC_CTRL_T* fbc_ctrl = FBDEV_M23_GET_FBC_CTRL(hw_ctx, i);
        int hw_afbc_status = 0;

        fbc_ctrl->fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW;
        fbc_ctrl->status  = FBDEV_M23_FBC_STATUS_NONE;
        FBDEV_M23_FBC_DEBUG("fb(%d) initialize fbc env\n", LX_FBDEV_ID_OSD0);

        /* raxis.lim (2016/10/05) -- try to initialize OSD to AFBC graphic path if possible
         * boot loader can display both non-AFBC and AFBC logo image, so I should keep the current
         * graphic configuration.
         * below codes will be active if cold boot or snapshot boot (not instant boot)
         *
         *
         */
        hw_afbc_status = FBDEV_M23_CMN_GetHWStatus(FBDEV_M23_HW_STATUS_AFBC, i);

        FBDEV_NOTI("fb(%d) initial FBC mode = %d\n", i, hw_afbc_status);

        /* recover FBC if AFBC display is used at boot loader */
        if (hw_afbc_status)
        {
            FBDEV_M23_FBC_DEBUG("fb(%d) recover FBC HW config\n", i);
            FBDEV_M23_CMN_SetupFBC(i, LX_FBDEV_FBC_FORMAT_AFBC);
        }
    }

#else
    /* TODO: do someting if nessary */
#endif
}

#ifdef FBDEV_M23_USE_FBC_CTRL
/** create or destory FBC envrionment
 *
 *
 *
 */
static void FBDEV_M23_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt)
{
    int i;
    int xidx;
    int xnum, xlst[2], afbc_xlst[2];

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_M23_FBC_CTRL_T* fbc_ctrl = FBDEV_M23_GET_FBC_CTRL(hw_ctx, fb_dev_id);

    FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_HW_NOTI("fb(%d) fbc_ctrl->fbm_fmt = 0x%x, new fbc_fmt = 0x%x\n", fb_dev_id, fbc_ctrl->fbc_fmt, fbc_fmt);

    /* check HW status */
    if (fbc_ctrl->fbc_fmt == fbc_fmt)
    {
#ifdef FBDEV_M23_SW_RECOVERY_AFBC_FLAG_CORRUPTION
        int hw_afbc_status = FBDEV_M23_CMN_GetHWStatus(FBDEV_M23_HW_STATUS_AFBC, fb_dev_id);

        hw_afbc_status = (hw_afbc_status) ? LX_FBDEV_FBC_FORMAT_AFBC : LX_FBDEV_FBC_FORMAT_RAW;
        FBDEV_CHECK_CODE(fbc_ctrl->fbc_fmt != hw_afbc_status, goto afbc_config,
                         "<!> fb(%d) sw/hw status mismatch (hw:%d, sw:%d)\n", fb_dev_id, hw_afbc_status, fbc_ctrl->fbc_fmt);
#endif
        return; /* same value. do nothing */
    }

#ifdef FBDEV_M23_SW_RECOVERY_AFBC_FLAG_CORRUPTION
afbc_config:
#endif
    xnum = FBDEV_M23_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_NOTI("fb(%d) setup afbc_path=%d\n", fb_dev_id, fbc_fmt);

    OSD_TOP_M23_RdFL(ctrl_dpath);
    OSD_TOP_M23_RdFL(ctrl_auto_init_afbc);

    if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
    {
        UINT32 afbc_auto_init_src_val = 0x0; // M23 fixed B.OSD

#ifdef FBDEV_M23_USE_AFBC_READ_BW_SAVING
        UINT32 enable = FBDEV_M23_CMN_GetOSDEnable(fb_dev_id);
#else
        UINT32 enable = 1;
#endif

        FBDEV_M23_FBC_DEBUG("setup fbc_fmt = 0x1 (enable AFBC mode)\n");

        if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
        {
            OSD_TOP_M23_Wr01(ctrl_dpath, osd0_afbc_en, 0x1);
            OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,        enable);
            OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en,   enable);
            OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, idx_afbc0_pic_init_src,   0x0); /* g0_pic_init. 이건 고정 ? */

            OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_src,  afbc_auto_init_src_val);

            FBDEV_M23_FBC_DEBUG("fb(%d) afbc enabled. xlst=%d,%d view=%d\n",
                                fb_dev_id, afbc_xlst[0], afbc_xlst[1], enable);
        }
    }
    else
    {
        FBDEV_M23_FBC_DEBUG("setup fbc_fmt = 0x0 (disable AFBC mode)\n");

        if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
        {
            OSD_TOP_M23_Wr01(ctrl_dpath, osd0_afbc_en, 0x0);
            OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,        0x0);
            OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en,   0x0);

            FBDEV_M23_FBC_DEBUG("fb(%d) afbc disabled. xlst=%d,%d\n",
                                fb_dev_id, afbc_xlst[0], afbc_xlst[1]);
        }
    }


    // setup OSD registers
    for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
    {
        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xidx), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xidx);

        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);

        if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
        {
            /* enable BITMAP mode */
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main,   osd_bitmap_only_mode_en, 0x1);

            fbc_ctrl->status |=  FBDEV_M23_FBC_STATUS_PATH_CHANGE;;
        }
        else
        {
            /* disable BITMAP mode (default in raw mode) */
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main,   osd_bitmap_only_mode_en, 0x0);

            fbc_ctrl->status &= ~FBDEV_M23_FBC_STATUS_HDR_SETUP;
            fbc_ctrl->status |=  FBDEV_M23_FBC_STATUS_PATH_CHANGE;
        }

        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
    }

    // flush top registers
    OSD_TOP_M23_WrFL(ctrl_dpath);
    OSD_TOP_M23_WrFL(ctrl_auto_init_afbc);

    // (2019/05/21) I will always configure AFBC to use ready_flag
    AFBC_CTRL_RdFL(0, ctrl_afbc_0);
    AFBC_CTRL_Wr01(0, ctrl_afbc_0, update_ready_flag_en, 0x1);
    AFBC_CTRL_WrFL(0, ctrl_afbc_0);

    FBDEV_M23_FBC_DEBUG("fb(%d) fbc_mode=0x%x setup\n", fb_dev_id, fbc_fmt);

    fbc_ctrl->fbc_fmt = fbc_fmt;
}

// setup AFBC HW register for OSD input
//
// 최대 2개의 AFBC decoder 를 처리할 수 있다.
// 하나의 AFBC decoder 는 최대 width 1920 까지의 AFBC 이미지를 처리할 수 있다.
// 하나의 AFBC decdoer 는 최대 height 2160 까지의 AFBC 이미지를 처리할 수 있다.
//
// 통상적인 2K OSD (1920x1080) 은 하나의 AFBC decoder 로 처리 가능하다.
// 통상적인 4K OSD (3840x2160) 은 AFBC0 를 통해 L 1920 을, AFBC1 를 통해 R 1920을 읽도록 설정한다.
// (AFBC0 은 x=0~1919 영역을, AFBC1 은 x=1920~3839 영역을 읽도록 설정된다)
//
// 각 AFBC decoder 의 stride 정보를 통해 통 이미지인지 여부를 알 수 있게 된다.
//
// 예)
// image[0] = size=1920x2160, x_pos=0, stride=3840x4
// image[1] = size=1920x2160, x_pos=1920, stride=3840x4
//
// 이 함수는 AFBC register 기록에 집중한다.
// UI 인지 E-Streamer 인지에 따른 이미지 특성은 이 함수를 호출하는 측에서 조치가 되어야 한다.
//
// 제약사항)
// SW 복잡도 감소를 위하여 2개의 AFBC decoder 가 사용되는 경우,
// 동일한 afbc image 를 처리하게 되며, 기본적인 좌표 정보도 동일하다.
// L/R 표현을 위한 x_pos 값만 별도로 처리하도록 하겠다.
//
static void FBDEV_M23_CMN_WriteFBCHdrRegs(int fb_dev_id, FBDEV_M23_OSD_HDR_T osd_hdr[2],
        FBDEV_M23_OSD_EXHDR_T* osd_exhdr)
{
    UINT32 afbc_mode;
    UINT32 img_addr;
    int img_x;
    int img_y;
    int img_w;
    int img_h;
    int img_bpp;
    int img_stride;

    int i;
    int afbc_xidx;
    int xnum, xlst[2], afbc_xlst[2];

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_M23_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];
    FBDEV_M23_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

    FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);
    FBDEV_CHECK_DEBUG(fbc_ctrl->fbc_fmt != LX_FBDEV_FBC_FORMAT_AFBC, return, "fb(%d) non-afbc image\n", fb_dev_id);

    xnum = FBDEV_M23_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);

    /* ignore noisy warning msg becase some OSD layer is not supported by HW */
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d. fb(%d)\n", fb_dev_id, xnum, fb_dev_id);

    FBDEV_M23_TODO("M23 은 AFBC1.1 만 지원함")
    afbc_mode = 0x0; // AFBC1.1 fixed

#if 0
    // (2022/04/25)
    // M23 은 Multi AFBC 구성이 안되므로, 이 구분을 위한 x,y 를 그대로 받아주면 안됨
    osd_hdr[0].osd_hdr_xpos = 0;
    osd_hdr[0].osd_hdr_ypos = 0;
#endif

    img_y = osd_hdr[0].osd_hdr_ypos;
    img_w = osd_hdr[0].osd_hdr_w_mem;
    img_h = osd_hdr[0].osd_hdr_h_mem;
    img_addr = osd_hdr[0].osd_hdr_ptr_bmp;
    img_stride = osd_exhdr->img_stride;
    img_bpp = FBDEV_M23_BITS_2_BYTES(osd_exhdr->bits_per_pixel);

    for (i = 0; i < xnum; i++)
    {
        afbc_xidx = afbc_xlst[i];

        /* current fb_dev_id is not attached to afbc */
        if (INVALID_AFBC_XIDX(afbc_xidx)) continue;

        img_x = osd_hdr[i].osd_hdr_xpos;
        FBDEV_M23_FBC_DEBUG("fb(%d) afbc.xidx(%d) paddr=0x%08x pos=%d,%d dim=%dx%d, stride=%d\n",
                            fb_dev_id, afbc_xidx, img_addr,
                            img_x, img_y, img_w, img_h, img_stride);

        /* once the whole AFBC registers are set, I will just update the minimal registers */
        if (fbc_ctrl->status & FBDEV_M23_FBC_STATUS_HDR_SETUP)
        {
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_1);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_2);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_3);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_4);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_8);

            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_1, hd_base,      img_addr);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_8, pl_data_base, img_addr);

            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_x,     img_x);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_y,     img_y);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_x,       LX_CALC_ALIGNED_VALUE(img_x + img_w - 2, 1));
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_y,       img_y + img_h - 1);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_4, img_width,   img_stride / img_bpp);

            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_1);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_2);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_3);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_4);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_8);
        }
        /* below configurations will be called when the first AFBC image is feeded */
        else
        {
            // (2021/08/04) see http://clm.lge.com/issue/browse/SICDTV-10198
            // AFBC1 의 AXI ID 를 변경함
            // 필독 http://clm.lge.com/issue/browse/SICDTV-10198?focusedCommentId=3305728&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3305728
            int pl_gmau_id = (afbc_xidx == 0) ? 5 : 7;
            int hd_gmau_txid = (afbc_xidx == 0) ? 4 : 6;

            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_0);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_1);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_2);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_3);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_4);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_5);
            //          AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_6);
            //          AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_7);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_8);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_9);
            //          AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_a);
            //          AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_b);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_c);
            //          AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_d);
            //          AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_e);
            //          AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_f);
            AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_10);

            /* HW guy said that I should set the same value to AFBC hdr & data :(
             * I think it's enough to change only below two value (hd_base, pl_data_base)
             */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_1, hd_base,      img_addr);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_8, pl_data_base, img_addr);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_9, pl_data_end,  0xffffffff);

            /* AFBC data size description
             *
             */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_x,     img_x);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_y,     img_y);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_x,       LX_CALC_ALIGNED_VALUE(img_x + img_w - 2, 1));
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_y,       img_y + img_h - 1);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_4, img_width,   img_stride / img_bpp);

            /* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
             *
             * HW guy fixed dec_buf_depth value to 959 and pl_buf_depth value to 255.
             */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_5, dec_buf_depth_m1, 959);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_5, pl_buf_depth_m1,  255);

            //AFBC0_CTRL_Wr(ctrl_afbc_6, 0x00000000);   /* dummy */
            //AFBC0_CTRL_Wr(ctrl_afbc_7, 0x00000000);   /* dummy */
            //AFBC0_CTRL_Wr(ctrl_afbc_a, 0x00000000);   /* dummy */
            //AFBC0_CTRL_Wr(ctrl_afbc_b, 0x00000000);   /* dummy */

            /* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
             * HW test value : 0x0011_FF54
             */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_endian_arb, 1); /* no description :( */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_endian_arb, 1); /* no description :( */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_endian_sw,  0xf); /* ambiguous description :( */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_endian_sw,  0xf); /* ambiguous description :( */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_gmau_id,    pl_gmau_id); /* difficult to understand description :( */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_gmau_txid,  hd_gmau_txid); /* difficult to understand description :( */

            //AFBC0_CTRL_Wr(ctrl_afbc_d, 0x00000000);   /* dummy */
            //AFBC0_CTRL_Wr(ctrl_afbc_e, 0x00000000);   /* dummy */

            //AFBC0_CTRL_Wr(ctrl_afbc_f, 0x00000000);

            /* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
             *
             * 0xff80_80ff @RGBA
             * 0xffff_8080 @ARGB (*)
             *
             * I 've used 0xffff_fffff since O20 AFBC integration
             */
#if 0
            AFBC_CTRL_Wr(afbc_xidx, ctrl_afbc_10, 0xffff8080);  /* +0xD0 : 0xffff8080 for argb case */
#else
            AFBC_CTRL_Wr(afbc_xidx, ctrl_afbc_10, 0xFFFFFFFF);  /* +0xD0 : 0xffffffff for argb case */
#endif

            /* (2020/04/29) see http://clm.lge.com/issue/browse/SICDTV-9405
             *
             * ctrl_afbc_0.run_mode = 0x1 if AFBC 1.0
             *                      = 0x0 if AFBC 1.1
             */
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, start,        0);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, ready,        0);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset,     0);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset_fifo, 0);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, run_mode,     afbc_mode);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, pl_addr_mode, 1);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset_ack, 0);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, gmau_arb_sw_reset, 0);

            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, flip_mode, (mirror_ctrl->status & FBDEV_M23_V_MIRROR_ON) ? 1 : 0);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, ignore_q_full, 0);
            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, wrap_en,      1);

            /* flush data */
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_1);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_2);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_3);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_4);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_5);
            //AFBC0_CTRL_WrFL(ctrl_afbc_6);
            //AFBC0_CTRL_WrFL(ctrl_afbc_7);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_8);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_9);
            //AFBC0_CTRL_WrFL(ctrl_afbc_a);
            //AFBC0_CTRL_WrFL(ctrl_afbc_b);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_c);
            //AFBC0_CTRL_WrFL(ctrl_afbc_d);
            //AFBC0_CTRL_WrFL(ctrl_afbc_e);
            //AFBC0_CTRL_WrFL(ctrl_afbc_f);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_10);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_0);
        }
    }

    fbc_ctrl->status |= FBDEV_M23_FBC_STATUS_HDR_SETUP;
}

static void FBDEV_M23_CMN_FlushFBCHdrRegs(int fb_dev_id)
{
    int i;
    int afbc_xidx;
    int xnum, xlst[2], afbc_xlst[2];

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_M23_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];

    FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_HW_NOTI("fb(%d) fbc_fmt=%s\n", fb_dev_id, (fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC) ? "on" : "off");

    if (fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
    {
        xnum = FBDEV_M23_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
        FBDEV_M23_FBC_DEBUG("fb(%d) xnum=%d, afbc_xlst=(%d,%d)\n", fb_dev_id, xnum, afbc_xlst[0], afbc_xlst[1]);

        /* current fb_dev_id is not attached to afbc */
        FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d\n", fb_dev_id, xnum);

        for (i = 0; i < xnum; i++)
        {
            afbc_xidx = afbc_xlst[i];

            if (INVALID_AFBC_XIDX(afbc_xidx)) continue;

            AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, update_ready_flag, 0x1);
            AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_0);

            FBDEV_M23_FBC_DEBUG("fb(%d) afbc_xidx(%d) flush AFBC regs\n", fb_dev_id, afbc_xidx);
        }
    }
}
#endif

// write OSD HW register
//
// 2K OSD, 4K OSD 여부에 따라 POSD 갯수를 판단하다.
// 필요시 전달된 OSD 정보값을 조작할 수도 있다.
//
//
void    FBDEV_M23_CMN_WriteHdrRegs(int fb_dev_id, FBDEV_M23_OSD_HDR_T* osd_hdr, FBDEV_M23_OSD_EXHDR_T* osd_exhdr)
{
    int i;
    int xidx;
    int xnum, xlst[2];

    FBDEV_M23_OSD_HDR_T osd_hw_hdr[2];  // 4K OSD 출력을 위하여 최대 2개 layer 필요
    UINT32* hdr_regs;

    ULONG flags;
    struct scanvas* hCanvas = NULL;
    FBDEV_WIN_CTX_T* wctx = NULL;

    hCanvas = FBDEV_GetWinCanvas(fb_dev_id);
    FBDEV_CHECK_CODE(NULL == hCanvas, return, "invalid canvas. fb(%d)\n", fb_dev_id);

    wctx = FBDEV_GetWinCtx(fb_dev_id);
    FBDEV_CHECK_CODE(NULL == wctx, return, "invalid winctx. fb(%d)\n", fb_dev_id);

    xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);

    /* ignore noisy warning msg becase some OSD layer is not supported by HW */
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "invalid xnum %d. fb(%d)\n", xnum, fb_dev_id);

    spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

    /* notify osd freeze for debug */
    if (!wctx->status.b_osd_hdr_flush)
    {
        UINT32 disp_fbmem;

        for (i = 0; i < xnum; i++)
        {
            xidx = xlst[i];

            if (INVALID_XIDX(xidx)) continue;

            OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);
            disp_fbmem = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);

            FBDEV_WARN("fb(%d) xidx(%d) freezed. osd_hdr_flush deferred. keep 0x%08x\n", fb_dev_id, xidx, disp_fbmem);
        }

        goto func_exit;
    }

    for (i = 0; i < xnum; i++)
    {
        xidx = xlst[i];

        if (INVALID_XIDX(xidx)) continue;

        // 통으로 전달된 osd_hdr 를 기반으로 최대 2개의 HW osd_hdr를 생성한다.
        memcpy(&osd_hw_hdr[i], osd_hdr, sizeof(FBDEV_M23_OSD_HDR_T));

        FBDEV_M23_TODO("M23 은 4K OSD 지원하지 않으므로, 2개의 HW osd_hdr 가 필요없음")
        FBDEV_M23_HDR_DEBUG("fb(%d) osd_hw_hdr in=%dx%d out=%dx%d\n",
                            fb_dev_id,
                            osd_hw_hdr[i].osd_hdr_w_mem,
                            osd_hw_hdr[i].osd_hdr_h_mem,
                            osd_hw_hdr[i].osd_hdr_w_out,
                            osd_hw_hdr[i].osd_hdr_h_out);

        hdr_regs = (UINT32*)&osd_hw_hdr[i];

        OSDX_M23_Wr(osdx_ctrl[xidx], osd_ctrl_hdr0, hdr_regs[0]);
        OSDX_M23_Wr(osdx_ctrl[xidx], osd_ctrl_hdr1, hdr_regs[1]);
        OSDX_M23_Wr(osdx_ctrl[xidx], osd_ctrl_hdr2, hdr_regs[2]);
        OSDX_M23_Wr(osdx_ctrl[xidx], osd_ctrl_hdr3, hdr_regs[3]);
        OSDX_M23_Wr(osdx_ctrl[xidx], osd_ctrl_hdr4, hdr_regs[4]);
        OSDX_M23_Wr(osdx_ctrl[xidx], osd_ctrl_hdr5, hdr_regs[5]);
        OSDX_M23_Wr(osdx_ctrl[xidx], osd_ctrl_hdr6, hdr_regs[6]);

        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr1);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr3);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr4);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr5);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr6);

#ifdef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL

        // (2017/09/15)
        // raxis.lim (2017/09/15) -- DO NOT write OSD out_win only
        // when OSD0_PQEFW_OSD0_OUT_CTRL is enabled
        //
        // raxis.lim (2019/06/19)
        // support orbit control (http://clm.lge.com/issue/browse/SDOSTB-246)
        // (note) 4KOSD 테스트 모드에서는 orbit 활성화시 OSD 출력 정상아님. orbit 제어하는 FW 에서 추가 제어 필요할 듯 예상됨
        //
        // raxis.lim (2019/07/29)
        // EXT_FRC 가 붙었을 경우에는 orbit control 을 O20 에서 하지 않는다.
        // 향후에는 flag 를 좀 더 조정하자.
        //
        // (2022/04/25) M23 은 이 블럭을 사용하지 않음. undef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL 임을 확인할것
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            if (fbdev_pqefw_osd0_out_ctrl && (hw_ctx->hw_wa_flag & FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL))
            {
                /* do nothing */
            }
            else
            {
                UINT32 w, h;
                OSDX_M23_Rd01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_w_out, w);
                OSDX_M23_Rd01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_h_out, h);
                FBDEV_HW_DEBUG("fb(%d) xidx(%d) flush OSD_CTRL_HDR2. %dx%d\n", fb_dev_id, xidx, w, h);
                OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
            }
        }
        else
        {
            OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
        }

#else
        // (2022/04/25)
        // orbit 등 지원하지 않고, UI/Estreamer 제어를 위하여 hdr2 를 직접 다루어야 한다.
        //
        // 코드 자체를 정리해야 하나, 다음 칩에서의 사용성을 고려하여 코드는 유지함
        // M23 과 같이 여러개의 layer service 가 동일 OSD0 HW 를 사용하는 경우에는 PQEFW CTRL 과 공존할 수 없으므로
        // HW 설계 단계에서 설계 오류가 없도록 주의할것
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
#endif
    }

    /* flush post header (AFBC,OSD_SHP etc ) */
    {
        /* flush AFBC register */
#ifdef FBDEV_M23_USE_FBC_CTRL
        if (fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1)
        {
            FBDEV_HW_NOTI("fb(%d) check AFBC\n", fb_dev_id);
            FBDEV_M23_CMN_SetupFBC(fb_dev_id, hCanvas->fbc_fmt);

            if (hCanvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
            {
                FBDEV_M23_CMN_WriteFBCHdrRegs(fb_dev_id, osd_hw_hdr, osd_exhdr);
            }

            FBDEV_M23_CMN_FlushFBCHdrRegs(fb_dev_id);
        }

#endif

        /* notify OSD HW to read osd header */
        for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
        {
            xidx = xlst[i];
            g_osd_m23_reg->osdx_ctrl[xidx].osd_ctrl_main.osd_hdr_ready_flag = 0x1;
            FBDEV_M23_HDR_DEBUG("fb(%d) xidx(%d) flush osd_hdr regs/data\n", fb_dev_id, xidx);
        }

        // (2022/02/07) M23 은 4K OSD 지원하지 않으므로, 관련 레지스터 설정 코드 지움
    }

func_exit:
    spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);
}

/** OSD HW common header generator
 *
 *  OSD HW header is made based on struct scanvas data and extra environment such as 3DOSD, reverse etc.
 *
 */
int FBDEV_M23_CMN_WriteOSDHeader(struct scanvas* pCanvas)
{
    int                     fb_dev_id;
    UINT32                  bitmap_ptr;
    FBDEV_M23_OSD_HDR_T     osd_hdr;
    FBDEV_M23_OSD_EXHDR_T   osd_exhdr;
    FBDEV_WIN_CTX_T*        wctx;
    struct scanvas          canvas;
    UINT32                  disp_width, disp_height;

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> fb(%d) user_initcall not ready +++\n",
                     pCanvas->fb_dev_id);

    wctx = FBDEV_GetWinCtx(pCanvas->fb_dev_id);
    FBDEV_CHECK_CODE(NULL == wctx,
                     return RET_ERROR,
                     "fb(%d) invalid winctx.\n", pCanvas->fb_dev_id);

    // fb(1) 이 소유권을 가지고 있는 경우에만 제어를 허용한다.
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        FBDEV_CHECK_CODE(hw_ctx->hw_osd0_owner != fb_dev_id,
                         return RET_ERROR,
                         "++ fb(%d) ignore. not hw_osd0_owner\n", fb_dev_id);
    }

    /* clear osd_hdr before writing */
    memset(&osd_hdr,   0x0, sizeof(FBDEV_M23_OSD_HDR_T));
    memset(&osd_exhdr, 0x0, sizeof(FBDEV_M23_OSD_EXHDR_T));
    memcpy(&canvas,    pCanvas, sizeof(struct scanvas));

    fb_dev_id = canvas.fb_dev_id;
    disp_width = hw_ctx->hw_disp_width;
    disp_height = hw_ctx->hw_disp_height;

    /* raxis.lim (2016/08/08) - if OSD is freezed, DO NOT handle/write any registers
     *
     * This patch seems to prevent OSD garbage during transition from non AFBC (boot logo) to AFBC (mercury/webOS) screen.
     * Originally, osd_hdr_flush is checked at FBDEV_M23_CMN_WriteHdrRegs().
     * I don't know the below code really prevents OSD garbage rather than the original policy.
     * <!> More tests are required.
     */
    if (!wctx->status.b_osd_hdr_flush)
    {
        int xidx, xnum, xlst[2];
        UINT32 disp_fbmem = 0x0;

        xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);
        xidx = xlst[0];

        if (!INVALID_XNUM(xnum))
        {
            OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);
            disp_fbmem = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);
        }

        FBDEV_WARN("fb(%d) freezed. osd_hdr_flush deferred & keep fbmem 0x%08x.", fb_dev_id, disp_fbmem);

        return RET_OK;
    }

    switch (fb_dev_id)
    {
        case LX_FBDEV_ID_CSR0:
        {
            int csr_x_max;
            int csr_x_off, csr_y_off, csr_x_pos, csr_y_pos, csr_x_size, csr_y_size;
            int csr_disp_w, csr_disp_h;

#ifdef FBDEV_M23_USE_UNLIMITED_CURSOR_POSITION
            int csr_h_min_pxl = FBDEV_M23_BYTES_2_PIXEL(FBDEV_M23_GMAU_WORD_BYTES); /* 16 bytes -> 4 pixel */
#endif
            FBDEV_M23_HDR_DEBUG("cursor_pos req(%d,%d)\n", canvas.output_win.x, canvas.output_win.y);

            // csr_disp_w is used to check if cursor is located at the right corner.
            // this value is set to 3840 in UHD mode, 1920 in FHD mode
            csr_disp_w = hw_ctx->hw_disp_width;
            csr_disp_h = hw_ctx->hw_disp_height;

            // if csr_hotspot is active, adjust (x,y) position of cursor layer.
            //
            // if cursor position is negative, I should move the bitmap address ( H/W doesn't accept negative position )
            //
            // IMPORTATNT !! if you change the base address, its alignment should be multiplt of 16 byte ( not 8 byte )
            // woonghyeon just said that it may be H/W bug (limitation?).
            // since we are using ARGB8888 pixel format for cursor OSD. cursor offset should be multiple of 4 pixel !!
            //
            csr_x_max = canvas.stride / FBDEV_M23_BITS_2_BYTES(canvas.bits_per_pixel);

            csr_x_off = 0;
            csr_y_off = 0;

            csr_x_pos = canvas.output_win.x - canvas.csr_hotspot.x;
            csr_y_pos = canvas.output_win.y - canvas.csr_hotspot.y;

            csr_x_size = canvas.input_win.w;
            csr_y_size = canvas.input_win.h;

            FBDEV_M23_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d info( %dx%d h %d,%d ) max_x %d disp_x %d\n", fb_dev_id,
                                csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
                                canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y,
                                csr_x_max, csr_disp_w);

#ifdef FBDEV_M23_USE_UNLIMITED_CURSOR_POSITION

            // raxis.lim (2015/07/24)
            // if cursor is located at far left corner, we should try to show only minimum cursor viewing area.
            // as described above, minimum viewing area is 4 pixel.
            //
            // @note framebuffer address will be adjusted based on csr_x_off.
            if (csr_x_pos < -(csr_x_size - csr_h_min_pxl))
            {
                csr_x_off = (csr_x_max - csr_h_min_pxl);
                csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off, 2);

                csr_x_size = csr_h_min_pxl;
                csr_x_pos = 0;
            }
            else
#endif

                // if cursor is at the left side, we calculate csr_x_pos and to change the frame buffer address
                // cursor viewing area should be shrinked by changing csr_x_size
                //
                // @note framebuffer address will be adjusted based on csr_x_off.
                if (csr_x_pos < 0)
                {
                    csr_x_off = -csr_x_pos;
                    csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off, 2);

                    csr_x_size -= csr_x_off;
                    csr_x_pos = 0;
                }

            // if cursor is at the top side, we calculate csr_y_pos to adjust the frame buffer address
            // if csr_y_size becomes zero, OSD HW will display the garbage. so we should gaurantee the minimum OSD viewing
            // area in vertical direction.
            //
            // @note framebuffer address will be adjusted based on csr_y_off.
            if (csr_y_pos < 0)
            {
                csr_y_off =  -csr_y_pos;
                csr_y_pos =  0;
                csr_y_size -= csr_y_off;

                if (csr_y_size < FBDEV_M23_CSR_MIN_HEIGHT)
                {
                    csr_y_size = FBDEV_M23_CSR_MIN_HEIGHT;
                    csr_y_off  = csr_y_size - FBDEV_M23_CSR_MIN_HEIGHT;
                }
            }

            // prevent OSD garbage. effective cursor width should be less than the real surface width
            if (csr_x_size > csr_x_max) csr_x_size = csr_x_max;

            // if cursor is located at the right corner, I should gaurantee the minimal viewing area of cursor.
            // without it, cursor image will be broken :(
            // see the description for FBDEV_M23_CSR_MIN_WIDTH
            if (csr_x_pos + csr_x_size > csr_disp_w)
            {
                if (csr_x_pos > csr_disp_w - FBDEV_M23_CSR_MIN_WIDTH)
                {
                    csr_x_pos = csr_disp_w - FBDEV_M23_CSR_MIN_WIDTH;
                }

                csr_x_pos   = LX_CALC_ALIGNED_VALUE(csr_x_pos, 2);  /* make X pos is aligned by 4 */

                csr_x_size  = csr_disp_w - csr_x_pos;

                // software workaround for 1x cursor display on blend path
                // On blend path, cursor size should be displayed x2 automatically because OSD disp size is 3840x2160
                // and cursor region is set based on 1920x1080 area
                // if 2x scale up is not supported, I should multiply csr_x_size by double manually
                //
                // raxis.lim (2020/06/02)
                // DO NOT assume B.OSD path is always set to UHD display.
                // I should support FHD display on B.OSD path.
                // So I should check output display size regardless of osd path configuration.
                if (hw_ctx->hw_wa_flag & FBDEV_M23_HW_WA_1X_CSR_DISP_ON_BLEND_PATH)
                {
                    if (FBDEV_M23_CMN_IsUHDDispMode())
                    {
                        csr_x_size *= 2;

                        if (csr_x_size > csr_x_max) csr_x_size = csr_x_max;
                    }
                }
            }

            // if cursor is located at the bottom corner, I should gaurantee the minimum viewing area, i.e 2 pixel
            if (csr_y_pos > csr_disp_h - FBDEV_M23_CSR_MIN_HEIGHT)
            {
                csr_y_pos = csr_disp_h - FBDEV_M23_CSR_MIN_HEIGHT;
            }

            // see http://clm.lge.com/issue/browse/SCDCR-6480
            csr_x_size &= 0xfffc;

            // NOTE that csr_x_pos, csr_y_pos, csr_x_size, csr_y_size is changed at the above corner checker.
            // if pos or size is set to wrong value, OSD HW will display the garbage screen.
            //
            osd_hdr.osd_hdr_xpos    = csr_x_pos;    /* output x (csr x pos) */
            osd_hdr.osd_hdr_ypos    = csr_y_pos;    /* output y (csr y pos) */
            osd_hdr.osd_hdr_w_mem   = csr_x_size;   /* viewing cursor width */
            osd_hdr.osd_hdr_h_mem   = csr_y_size;   /* viewing cursor height */
            osd_hdr.osd_hdr_w_out   = csr_x_size;   /* output w */
            osd_hdr.osd_hdr_h_out   = csr_y_size;   /* output h */

            // adjust framebuffer address if necessary
            // @note  gMAU requests 16byte aligned address
            bitmap_ptr = canvas.osd_bm_paddr;
            bitmap_ptr += (csr_y_off * canvas.stride) + FBDEV_M23_GMAU_ALIGNED_BYTES(csr_x_off * FBDEV_M23_BITS_2_BYTES(
                              canvas.bits_per_pixel));

            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl         = FBDEV_M23_BYTES_2_OSD_WORDS(canvas.stride);

            FBDEV_M23_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d <- req( %dx%d h %d,%d)\n", fb_dev_id,
                                csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
                                canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y);
            FBDEV_M23_HDR_DEBUG("fb(%d) cursor pre-processing done\n", fb_dev_id);
        }
        break;

        // E-streamer 전용 가상 레이어
        //
        // 512x2160 1:1 크기의 4K-Estreamer출력 전용으로 구성됨
        // 이미지 렌더링은 일반 OSD 처럼 처리하되, 출력 위치의 변경, crop 등은 별도의 레지스터 조작으로 조치함.
        //
        case LX_FBDEV_ID_OSD1:
        {
            osd_hdr.osd_hdr_w_out = canvas.output_win.w;
            osd_hdr.osd_hdr_h_out = canvas.output_win.h;
            osd_hdr.osd_hdr_xpos = 0; //canvas.output_win.x;
            osd_hdr.osd_hdr_ypos = 0; //canvas.output_win.y;
            osd_hdr.osd_hdr_w_mem = canvas.input_win.w;
            osd_hdr.osd_hdr_h_mem = canvas.input_win.h;

            bitmap_ptr = canvas.osd_bm_paddr;
            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl = FBDEV_M23_BYTES_2_OSD_WORDS(canvas.stride);
        }
        break;

        case LX_FBDEV_ID_OSD0:
        default:
        {
            // 기본적으로 UI는 full screen 으로 설정되어야 함
            // PQE(orbit) 에 의항 제어되는 값이므로, 실제로 register 를 설정하진 않음
            canvas.output_win.w = disp_width;
            canvas.output_win.h = disp_height;

            if (canvas.input_win.w > disp_width)    canvas.input_win.w = disp_width;

            if (canvas.input_win.h > disp_height)   canvas.input_win.h = disp_height;

            if (canvas.output_win.w > disp_width)   canvas.output_win.w = disp_width;

            if (canvas.output_win.h > disp_height)  canvas.output_win.h = disp_height;

            // raixs.lim (2017/08/25)
            // support user defined output win for debug. invalid config might make OSD corruption
            if (canvas.test_output_win.w && canvas.test_output_win.h)
            {
                FBDEV_M23_HDR_DEBUG("++ user output used (%d,%d)\n",
                                    canvas.test_output_win.w, canvas.test_output_win.h);
                memcpy(&canvas.output_win, &canvas.test_output_win, sizeof(LX_RECT_T));
            }

            // raxis.lim (2015/01/12) -- handle odd width
            // OSD doesn't support odd number as output width. so let's make it to even number
            if (canvas.output_win.w & 0x1)
            {
                FBDEV_M23_HDR_DEBUG("fb(%d) convert odd out_w %d to %d\n",
                                    fb_dev_id, canvas.output_win.w, canvas.output_win.w & 0xfffffffe);
                canvas.output_win.w &= 0xfffffffe;
            }

            // NOTE - CLUT processing is not processed anymore inside kdriver
            osd_hdr.osd_hdr_color_key_en = canvas.color_key_en;

            osd_hdr.osd_hdr_w_out = canvas.output_win.w;  /* output w */
            osd_hdr.osd_hdr_h_out = canvas.output_win.h;  /* output h */
            osd_hdr.osd_hdr_xpos  = canvas.output_win.x;  /* output x */
            osd_hdr.osd_hdr_ypos  = canvas.output_win.y;  /* output y */
            osd_hdr.osd_hdr_w_mem = canvas.input_win.w;   /* input w  */
            osd_hdr.osd_hdr_h_mem = canvas.input_win.h;   /* input h  */
            bitmap_ptr            = canvas.osd_bm_paddr;

            // modify bitmap ptr for input position is provided
            if (canvas.input_win.x > 0 || canvas.input_win.y > 0)
            {
                FBDEV_M23_HDR_DEBUG("fb(%d) bitmap based moved ! by %d,%d\n",
                                    fb_dev_id, canvas.input_win.x, canvas.input_win.y);

                /* gMAU requests 16byte aligned address */
                bitmap_ptr += canvas.input_win.y * canvas.stride;
                bitmap_ptr += FBDEV_M23_GMAU_ALIGNED_BYTES(FBDEV_M23_BITS_2_BYTES(canvas.input_win.x * canvas.bits_per_pixel));
            }

            FBDEV_M23_HDR_DEBUG("fb(%d) bitmap hwparam (%d,%d,%d,%d)(%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x, pixel_format=%d\n",
                                fb_dev_id,
                                canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
                                canvas.output_win.x, canvas.output_win.y, canvas.output_win.w, canvas.output_win.h,
                                canvas.stride, bitmap_ptr, canvas.fbc_fmt, canvas.pixel_format);

            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl         = FBDEV_M23_BYTES_2_OSD_WORDS(canvas.stride);

            if (canvas.pixel_format != LX_FBDEV_PIXEL_FORMAT_NOT_DEFINED &&
                    canvas.pixel_format != canvas.pixel_format_current)
            {
                int xnum, xlst[2];
                int i;

                xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);

                for (i = 0; i < xnum; i++)
                {
                    int xidx = xlst[i];

                    OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_pdec);

                    if (canvas.pixel_format == LX_FBDEV_PIXEL_FORMAT_RGB_8888)
                    {
                        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_alpha,           0x0);
                        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_red,             0x1);
                        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_green,           0x2);
                        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_blue,            0x3);
                    }
                    else if (canvas.pixel_format == LX_FBDEV_PIXEL_FORMAT_BGR_8888)
                    {
                        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_alpha,           0x0);
                        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_red,             0x3);
                        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_green,           0x2);
                        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_blue,            0x1);
                    }

                    OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_pdec);
                }

                canvas.pixel_format_current = canvas.pixel_format;
            }
        }
        break;
    }

    /* copy common attribute */
    osd_hdr.osd_hdr_format          = FBDEV_GetOSDPxlFmt(canvas.bits_per_pixel);
    osd_hdr.osd_hdr_depth           = FBDEV_GetOSDPxlDepth(canvas.bits_per_pixel);

    osd_hdr.osd_hdr_global_alpha_en = canvas.global_alpha_en;
    osd_hdr.osd_hdr_global_alpha    = (canvas.global_alpha_en) ? canvas.global_alpha : 0xff;
    osd_hdr.osd_hdr_color_key       = canvas.color_key;

    osd_hdr.osd_hdr_ptr_bmp         = bitmap_ptr;
    osd_hdr.osd_hdr_ptr_plte        = wctx->osd_plte_base_phys;

    // NOTE - virtual OSD is not processed anymore inside kdriver */

    /* handle S3D if requested */

    /* handle reverse OSD if requested */
    FBDEV_M23_CMN_HandleReverseOSD(fb_dev_id, &canvas, &osd_hdr);

    FBDEV_M23_HDR_DEBUG("fb(%d) bitmap hwparam (%d,%d,%d,%d)(%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x (final)\n",
                        fb_dev_id,
                        canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
                        canvas.output_win.x, canvas.output_win.y, canvas.output_win.w, canvas.output_win.h,
                        canvas.stride, bitmap_ptr, canvas.fbc_fmt);

    /* save osd header */
    memcpy(&hw_ctx->osd_hdr_sav[fb_dev_id], &osd_hdr, sizeof(FBDEV_M23_OSD_HDR_T));

    /* raxis.lim (2019/05/21)
     *
     * I don't care here whether two POSDs sare necessary or not. refer to FBDEV_M23_CMN_WriteHdrRegs()
     */
    osd_exhdr.bits_per_pixel = canvas.bits_per_pixel;
    osd_exhdr.img_stride    = canvas.stride;
    osd_exhdr.img_height    = osd_hdr.osd_hdr_h_mem;    /* 이 값이 맞나 몰라 */

    // fb(0) 과 fb(1) 이 같은 OSD HW 리소스를 사용하므로, owner만 레지스터를 쓰도록 조치함
    // 중요 상태이므로 noti 레벨로 출력함
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && hw_ctx->hw_osd0_owner != LX_FBDEV_ID_OSD0)
    {
        FBDEV_NOTI("fb(%d) is not osd0 owner, ignore\n", fb_dev_id);
        return RET_OK;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->hw_osd0_owner != LX_FBDEV_ID_OSD1)
    {
        FBDEV_NOTI("fb(%d) is not osd0 owner, ignore\n", fb_dev_id);
        return RET_OK;
    }

    FBDEV_M23_CMN_WriteHdrRegs(fb_dev_id, &osd_hdr, &osd_exhdr);

    /* do somthing if necessary */

#ifdef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL

    /* (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume */
    if (fb_dev_id == LX_FBDEV_ID_OSD0)
    {
        if (!(hw_ctx->hw_wa_flag & FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL))
        {
            hw_ctx->hw_wa_flag |= FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL;
            FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
        }
    }

#endif

    // see http://clm.lge.com/issue/browse/AVTASK-640
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;

        hw_cmd.gen[0] = fb_dev_id;
        hw_cmd.gen[1] = osd_hdr.osd_hdr_ptr_bmp;
        hw_cmd.gen[2] = wctx->pixel.output_win.x;
        hw_cmd.gen[3] = wctx->pixel.output_win.y;

        //FBDEV_NOTI("fb(%d) call FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE. owner=%d\n", fb_dev_id, hw_ctx->hw_osd0_owner);
        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE, &hw_cmd);
    }

    //func_exit:
    return RET_OK;
}

/*========================================================================================
    Implementation Group
========================================================================================*/

/** OSD HW Layer enable/disable
 *
 * @param   fb_dev_id [IN] fbdev ID
 *
 *          enable : 0 : display off , 1 : display on
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_M23_CMN_SetOSDEnable(int fb_dev_id, int enable)
{
    int     i;
    int     xidx;
    int     xnum, xlst[2], afbc_xlst[2];
    UINT32  val = 0x0;
    UINT32  hw_osd0_owner;
    UINT32  new_hw_osd0_owner;

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> user_initcall not ready +++\n");

    // fb(0) 와 fb(1) 가 결국 OSD0 동일 HW 를 공유하기 때문에, on/off 과정에서의 owner 관계를 잘 조정해야 한다.
    hw_osd0_owner = hw_ctx->hw_osd0_owner;
    new_hw_osd0_owner = hw_osd0_owner;

    xnum = FBDEV_M23_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

    val = (enable) ? 0x1 : 0x0;
    FBDEV_NOTI("fb(%d) xlst=(%d,%d) view = <%s>\n", fb_dev_id, xlst[0], xlst[1], (enable) ? "on" : "off");

    // (2021/12/04) http://hlm.lge.com/qi/browse/QEVENTTWT-8589
    // LSM 에서 TV 시작시에  fb(0) 과 fb(1) 에 대한 XOR 동작성을 위배하고 있음
    // 드라이버에서는 fb(0) 에 우선 순위를 두고, fb(1) 에 대한 on/off 을 거부할 수 있음
    if (fb_dev_id == LX_FBDEV_ID_OSD1 && FBDEV_M23_CMN_GetOSDEnable(LX_FBDEV_ID_OSD0))
    {
        FBDEV_NOTI("++ fb(%d) %s ignore. fb(0) is already enabled\n", fb_dev_id, (enable) ? "on" : "off");
        return RET_OK;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        if (enable)
        {
            // (2021/08/04) see http://clm.lge.com/issue/browse/SICDTV-10200
            // 플랫폼에서 무의미한 fb(1) 렌더링이 존재하기 때문에, fbmem 의 동적 할당 위치를 변경한다.
            //
            // AS-IS: 렌더링 직전
            // TO_BE: OSD On 초기
            //
            // As-IS 상황에서는 fbmem 이 할당되기만 하고, 해제 조건(OSD off) 이 발동되지 않기 때문에,
            // 불필요하게 메모리를 할당받는 상태가 된다.
            //
            FBDEV_M23_CMN_AllocExternalRendererFrameBuffer();

            // (2020/10/16) Estreamer 동작전에 cursor 를 강제로 off 시킴
            // see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
            if (FBDEV_M23_CMN_GetOSDEnable(LX_FBDEV_ID_CSR0))
            {
                int csr_xnum, csr_xlst[2], csr_afbc_xlst[2];

                csr_xnum = FBDEV_M23_CMN_GetHWXListEx(LX_FBDEV_ID_CSR0, csr_xlst, csr_afbc_xlst);

                if (csr_xnum > 0)
                {
                    int csr_xidx = csr_xlst[0];

                    OSDX_M23_RdFL(osdx_ctrl[csr_xidx], osd_ctrl_sync0);
                    OSDX_M23_Wr01(osdx_ctrl[csr_xidx], osd_ctrl_sync0, osd_sync_enable, 0x0);
                    OSDX_M23_WrFL(osdx_ctrl[csr_xidx], osd_ctrl_sync0);

                    FBDEV_NOTI("++ set cursor invisible (sync.en=0) when EXT_RENDER is shown\n");
                }
            }
        }

        // fb(1) 의 on/off 에 따른 후속 처리 넣을것
    }

    // OSD on/off 의 실제 레지스터 처리부. 즉 이 함수의 main 임
    for (i = 0; i < xnum; i++)
    {
        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, val);
        OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_enable, val);

        // (2021/07/013)
        // 만약 E-streamer 동작중 cursor ON 요청이 온다고 가정하면, 실제 화면에 보이면 안된다.
        // 커서 클릭에 의하여 EST Off, UI On 상황이 된다고 해도 첫번째 요청인 CSR ON 요청은 잠시
        // ignore 처리해야 한다.
        if (fb_dev_id == LX_FBDEV_ID_CSR0 && enable)
        {
            if (FBDEV_M23_CMN_GetOSDEnable(LX_FBDEV_ID_OSD1))
            {
                OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_enable, 0x0);
                FBDEV_NOTI("++ set cursor invisible (sync.en=0) when EXT_RENDER is shown\n");
            }
        }
    }

    // flush registers
    for (i = 0; i < xnum; i++)
    {
        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);
    }

#if 1

    // raixs.lim (2021/06/01) E60 의 상황을 참조하여, M23 의 경우를 미리 대비함.
    //
    // (2020/11/17) http://clm.lge.com/issue/browse/SICDTV-8986, QEVENTTWON-8969
    // OSD off 과정에서 20% 의 확률로 화면 우측에서의 과도 (가비지) 출력 현상 있음
    // OSD off 과정에서 실제 OSD 출력을 끊고, 후속 조치(AFBC 중지 등)이 진행되도록 함
    //
    // (2022/04/25)
    // UI -> Estreamer 로 변환하는 시간이 너무 짧은 경우 과도 현상이 보일 수 있으므로, 기존 코드 유지함.
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && !enable)
    {
        if (!fbdev_hw_pm_suspend_stage)
        {
            usleep_range(16700, 16700);
        }
    }

#endif

    // (2021/07/05) OSD0 HW 에 대한 소유권을 설정한다.
    // fb(0) 을 최우선으로 우대하는 정책을 사용할 것이며,fb(1) 의 소유권은 필요한 순간에만 설정한다.
    //
    // (2021/08/04) http://clm.lge.com/issue/browse/SICDTV-10200
    // owner 교체와 신규 owner 에대한 re-draw 과정을 실제 OSD HW on/off 전으로 이동시킨다.
    // 즉 새로운 OSD 가 ON 되었을때, 이전 owner 의 화면이 나가지 않도록 조치한다.
    //
    // 아래 코드 흐름은 fb(0) off 상태에서 fb(1) on 상태로 최대한 수무드하게 전환하는 것을 목적으로 한다.
    //
    // 참고로 fb(1) off 상태에서는 이미 F22 에서 OSD 출력을 끊어 버렸고, 최소 10 frame drop 모드에 있기 때문에
    // owner 변경에 의한 fb(0) 순간 화면이 나올 수 있나 관점에서는. 절대로 그럴 수 없다.
    //
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        hw_ctx->hw_osd0_owner = (enable) ? LX_FBDEV_ID_OSD1 : LX_FBDEV_ID_OSD0;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD0 && enable)
    {
        hw_ctx->hw_osd0_owner = LX_FBDEV_ID_OSD0;
    }

    new_hw_osd0_owner = hw_ctx->hw_osd0_owner;

    // osd0_hw_owner 변경시 추후 ON 상황에 대비하여, 이전 fb 의 사용 흔적을 지워져야 한다.
    // 즉 새로운 osd0_hw_owner 가 OSD path 를 흘러갈 수 있도록 조치한다.
    //
    // (2022/04/25) hw_osd0_owner 변경시 M23 scaler block 설정을 변경해야 한다.
    // (2022/04/26) hw_osd0_owner 변경시 crop 정보도 리셋한다.
    //
    if (hw_osd0_owner != new_hw_osd0_owner)
    {
        UINT32 scaler_in_width, scaler_in_height;
        UINT32 scaler_out_width, scaler_out_height;
        struct scanvas* canvas = FBDEV_GetWinCanvas(new_hw_osd0_owner);

        // scaler 정보를 리셋한다.
        FBDEV_NOTI("++ hw_osd0_owner changed to fb(%d) by fb(%d).%s\n",
                   new_hw_osd0_owner, fb_dev_id, (enable) ? "enable" : "disable");

        if (new_hw_osd0_owner == LX_FBDEV_ID_OSD1)
        {
            scaler_in_width = hw_ctx->hw_fb1_width;
            scaler_in_height = hw_ctx->hw_fb1_height;
            scaler_out_width = hw_ctx->hw_fb1_width;
            scaler_out_height = hw_ctx->hw_fb1_height;
        }
        else // OSD0
        {
            scaler_in_width = hw_ctx->hw_fb0_width;
            scaler_in_height = hw_ctx->hw_fb0_height;
            scaler_out_width = hw_ctx->hw_disp_width;
            scaler_out_height = hw_ctx->hw_disp_height;
        }

        FBDEV_NOTI("++ make fb(%d) default scaler config (%d,%d) => (%d,%d)\n",
                   new_hw_osd0_owner,
                   scaler_in_width, scaler_in_height,
                   scaler_out_width, scaler_out_height);

        for (i = 0; i < xnum; i++)
        {
            xidx = xlst[i];

            OSDX_M23_RdFL(osdx_ctrl[xidx], osd0_scaler_in_size);
            OSDX_M23_RdFL(osdx_ctrl[xidx], osd0_scaler_out_size);

            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_scaler_in_size, reg_scaler_in_width, scaler_in_width);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_scaler_in_size, reg_scaler_in_height, scaler_in_height);

            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_scaler_out_size, reg_scaler_out_width, scaler_out_width);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd0_scaler_out_size, reg_scaler_out_height, scaler_out_height);

            OSDX_M23_WrFL(osdx_ctrl[xidx], osd0_scaler_in_size);
            OSDX_M23_WrFL(osdx_ctrl[xidx], osd0_scaler_out_size);
        }

        // crop 정보를 리셋한다.
        // fb(1) 이 off 되거나, on 될때 모두 해당된다.
        FBDEV_NOTI("++ make fb(%d) default crop region\n", hw_ctx->hw_osd0_owner);
        {
            LX_RECT_T crop_rgn = {0, 0, scaler_in_width, scaler_in_height};
            FBDEV_M23_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_M23_GET_EXT_RENDER_CTRL(hw_ctx);

            ext_render_ctrl->hwparam.xoffset = 0;
            ext_render_ctrl->hwparam.yoffset = 0;
            ext_render_ctrl->hwparam.crop_x  = 0;
            ext_render_ctrl->hwparam.crop_y  = 0;
            ext_render_ctrl->hwparam.crop_w  = hw_ctx->hw_fb1_width;
            ext_render_ctrl->hwparam.crop_h  = hw_ctx->hw_fb1_height;

            FBDEV_M23_CMN_SetExternalRenderCropRegion(FALSE, hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height, 0, 0, &crop_rgn);
        }

        FBDEV_NOTI("++ write fb(%d) header immediately\n", new_hw_osd0_owner);

        if (canvas)
        {
            FBDEV_M23_CMN_WriteOSDHeader(canvas);
        }
    }

    /* raxis.lim (2019/10/08) -- enable/disable afbc reader if necessary
     *
     * OSD reader is configured to AFBC mode not MIF, CCO0/CCO1 will read something even though OSD is off state.
     * So we should control afbc(x)_init_en, afbc(x)_auto_init_en flag
     * refer to http://clm.lge.com/issue/browse/AVTASK-401
     */
#ifdef FBDEV_M23_USE_FBC_CTRL
#ifdef FBDEV_M23_USE_AFBC_READ_BW_SAVING
    {
        int afbc_status = FBDEV_M23_CMN_GetHWStatus(FBDEV_M23_HW_STATUS_AFBC, fb_dev_id);

        OSD_TOP_M23_RdFL(ctrl_auto_init_afbc);

        if (afbc_status)
        {
            if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
            {
                OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,        enable);
                OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en,   enable);
            }
        }
        else
        {
            if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
            {
                OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,        0x0);
                OSD_TOP_M23_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en,   0x0);
            }
        }

        FBDEV_M23_FBC_DEBUG("fb(%d) afbc=%d, view=%d\n", fb_dev_id, afbc_status, enable);

        OSD_TOP_M23_WrFL(ctrl_auto_init_afbc);
    }
#endif
#endif

    // (2020/10/16)  Estreamer 동작 종료후, UI 가 켜질때 cursor 를 복구시킬 수 있도록 함
    // see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && enable)
    {
        if (FBDEV_M23_CMN_GetOSDEnable(LX_FBDEV_ID_CSR0))
        {
            int csr_xnum, csr_xlst[2], csr_afbc_xlst[2];

            csr_xnum = FBDEV_M23_CMN_GetHWXListEx(LX_FBDEV_ID_CSR0, csr_xlst, csr_afbc_xlst);

            if (csr_xnum > 0)
            {
                int csr_xidx = csr_xlst[0];

                OSDX_M23_RdFL(osdx_ctrl[csr_xidx], osd_ctrl_sync0);
                OSDX_M23_Wr01(osdx_ctrl[csr_xidx], osd_ctrl_sync0, osd_sync_enable, 0x1);
                OSDX_M23_WrFL(osdx_ctrl[csr_xidx], osd_ctrl_sync0);

                FBDEV_NOTI("++ set cursor visible (sync.en=1) when UI is shown\n");
            }
        }
    }

#ifdef FBDEV_M23_SUPPORT_SW_WA_SICDTV_10362

    // M23. 코드 삭제함

#endif

    // 메모리절감을 통해서 fb(1) 이 off 되면, 즉시 IPC용 framebuffer 를 제거하도록 하자.
    if (fb_dev_id == LX_FBDEV_ID_OSD1 && !enable)
    {
        FBDEV_M23_CMN_DestroyExternalRendererFrameBuffer();
    }

    return RET_OK;
}

/** disable all active OSD path (hide all OSDs)
 *
 */
static void FBDEV_M23_CMN_ShutdownOSDPath(void)
{
    int     fb_dev_id;

    for (fb_dev_id = 0; fb_dev_id < LX_FBDEV_ID_MAX; fb_dev_id++)
    {
        if (g_fbdev_cfg->fb[fb_dev_id].b_active)
        {
            FBDEV_NOTI("shutdown fb(%d)\n", fb_dev_id);
            FBDEV_M23_CMN_SetOSDEnable(fb_dev_id, FALSE);
        }
    }
}

/** OSD HW Layer status
 *
 * wparam   void
 * @return  int 1 : ON , 0 : OFF
 *
 */
int FBDEV_M23_CMN_GetOSDEnable(int fb_dev_id)
{
    UINT32 val;
    int xidx;
    int xnum, xlst[2];

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);

    /* ignore noisy warning msg becase some OSD layer is not supported by HW */
    if (INVALID_XNUM(xnum)) return FALSE;

    /* raxis.lim (2019/05/21) -- event though OSD requires two POSD for 4K display, we can just check the first POSD value */
    xidx = xlst[0];
    FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

    OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
    OSDX_M23_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, val);

    if (fb_dev_id == LX_FBDEV_ID_OSD0 && hw_ctx->hw_osd0_owner != LX_FBDEV_ID_OSD0)
    {
        FBDEV_HW_NOTI("fb(%d) not osd0_ownwer. real=%d, ret=%d\n", fb_dev_id, val, 0);
        val = 0;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->hw_osd0_owner != LX_FBDEV_ID_OSD1)
    {
        FBDEV_HW_NOTI("fb(%d) not osd0_ownwer. real=%d, ret=%d\n", fb_dev_id, val, 0);
        val = 0;
    }

    return val;
}

int     FBDEV_M23_CMN_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl)
{
    int i;
    ULONG flags;

    /* we can't do spinlock when pivot mode is enabled because sleep ocurrs during GFX merge */
    spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        if (ctrl->view_status[i] == 0x0 || ctrl->view_status[i] == 0x1)
        {
            FBDEV_M23_CMN_SetOSDEnable(i, ctrl->view_status[i]);
        }
    }

    spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);

    return RET_OK;
}

/** set OSD out connection ctrl
 *
 *  param pConnCtrl [IN] connection control data
 *  @return RET_OK if success, RET_ERROR otherwise
 *
 */
int     FBDEV_M23_CMN_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
    // N/A
    return RET_OK;
}

/** control OSD SR (Picture Enhancement)
 *  - on/off
 *  - filter update
 *  - etc
 *
 */
int     FBDEV_M23_CMN_SRCtrl(BOOLEAN onoff)
{
    FBDEV_M23_CMN_SetupSRScaler(onoff, TRUE);
    return RET_OK;
}

int     FBDEV_M23_CMN_MirrorCtrl(BOOLEAN v_mirror_en)
{
    int i, j;
    int fb_list[] = {LX_FBDEV_ID_OSD0, LX_FBDEV_ID_OSD3};

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();
    FBDEV_M23_MIRROR_CTRL_T* mirror_ctrl = FBDEV_M23_GET_MIRROR_CTRL(hw_ctx);
    FBDEV_M23_FBC_CTRL_T* fbc_ctrl = FBDEV_M23_GET_FBC_CTRL(hw_ctx, LX_FBDEV_ID_OSD0);

    /* change mirror configuratin */
    mirror_ctrl->status = (v_mirror_en) ? FBDEV_M23_V_MIRROR_ON : 0x0;

    for (j = 0; j < NELEMENTS(fb_list); j++)
    {
        int xidx;
        int xnum, xlst[2];

        xnum = FBDEV_M23_CMN_GetHWXList(fb_list[j], xlst);

        for (i = 0; i < xnum; i++)
        {
            xidx = xlst[i];

            if (INVALID_XIDX(xlst[i])) continue;

            OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
            OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

            FBDEV_NOTI("fb(%d) before: 0x%08x 0x%08x\n", fb_list[j],
                       OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_main),
                       OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_sync0));

            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, v_mirror_en);
            OSDX_M23_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_v_reverse, v_mirror_en);

            OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
            OSDX_M23_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);

            FBDEV_NOTI("fb(%d) after: 0x%08x 0x%08x\n", fb_list[j],
                       OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_main),
                       OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_sync0));
        }
    }

    /* make AFBC header to setup again when next framebuffer is updated */
    fbc_ctrl->status &= ~FBDEV_M23_FBC_STATUS_HDR_SETUP;

    {
        FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(LX_FBDEV_ID_OSD0);

        if (wctx)
        {
            FBDEV_M23_CMN_WriteOSDHeader(&wctx->pixel);
        }
    }

    return RET_OK;
}


/*========================================================================================
    Implementation Group (VOSD emulation)
========================================================================================*/
/** handle osd scaler workaround during reverse screen
 *
 *  this workaround makes OSD scaler output to be similar to GFX.
 *  so this workaround code should run only when framebuffer is scaled up !!
 *
 */
void    FBDEV_M23_CMN_HandleReverseOSD(int fb_dev_id, struct scanvas* hCanvas, FBDEV_M23_OSD_HDR_T* osd_hdr)
{

}

/** VOSD ISR handler
 *
 *
 */
void     FBDEV_M23_CMN_ISRHook(void)
{
    /* do nothing */
}

/*========================================================================================
    Implementation Group (DIAG/PROC)
========================================================================================*/

/** HW status
 *
 *  read register(s) to get some HW status
 *  return value seems to be boolean value but there might be exceptions
 *  read comments before using the functioin
 *
 */
int      FBDEV_M23_CMN_GetHWStatus(FBDEV_M23_HW_STATUS_T status, UINT32 opt)
{
    int val = 0;

    switch (status)
    {
        /* return 1 if HW is set to AFBC configuration. otherwise return 0 */
        case FBDEV_M23_HW_STATUS_AFBC:
        {
            OSD_TOP_M23_RdFL(ctrl_dpath);

            if (opt == LX_FBDEV_ID_OSD0)
            {
                OSD_TOP_M23_Rd01(ctrl_dpath, osd0_afbc_en, val);
            }
            // (2021/07/05) fb(1) 과 fb(0) 이 같은 HW 를 읽고 있음을 기억하자.
            else if (opt == LX_FBDEV_ID_OSD1)
            {
                OSD_TOP_M23_Rd01(ctrl_dpath, osd0_afbc_en, val);
            }
            else
            {
                val = 0;
            }
        }
        break;

        case FBDEV_M23_HW_STATUS_VISIBLE:
        {
            val = FBDEV_M23_CMN_GetOSDEnable(opt);
        }
        break;

        case FBDEV_M23_HW_STATUS_SR_GAIN:
        {
            val = 0;
        }
        break;

        default:
        {
            val = 0;
        }
        break;
    }

    return val;
}

/** HW diagnostics
 *
 *  dump important paramters and valiate settings. this function will help to view HW status
 *  (usage) cat /proc/lg/fbdev/chip/diag
 *
 */
void FBDEV_M23_CMN_DiagHW(struct seq_file* m)
{
    UINT32 val;

    int xidx;
    int xnum, xlst[2];
    int fb_dev_id = LX_FBDEV_ID_OSD0;

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);
    xidx = xlst[0];

    /* print HW core info */
    {
        seq_printf(m, "disp.path: %s\n", (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? "bosd" : "sosd");
        seq_printf(m, "disp.width: %d\n", hw_ctx->hw_disp_width);
        seq_printf(m, "disp.height: %d\n", hw_ctx->hw_disp_height);

        seq_printf(m, "\n");
        seq_printf(m, "disp.uhd_mode: %d\n", FBDEV_M23_CMN_IsUHDDispMode() ? 1 : 0);
        seq_printf(m, "fb0.width: %d\n", hw_ctx->hw_fb0_width);
        seq_printf(m, "fb0.height: %d\n", hw_ctx->hw_fb0_height);
        seq_printf(m, "fb1.width: %d\n",  hw_ctx->hw_fb1_width);
        seq_printf(m, "fb1.height: %d\n", hw_ctx->hw_fb1_height);
        seq_printf(m, "\n");
        seq_printf(m, "hw_osd0_owner: fb(%d)\n", hw_ctx->hw_osd0_owner);
        seq_printf(m, "\n");
        seq_printf(m, "vsync_clk: %dHz\n", (FBDEV_M23_CMN_DetectVSyncClk() == FBDEV_VSYNC_CLK_60HZ) ? 60 : 120);

        seq_printf(m, "support_ext_frc: %d\n", hw_ctx->b_support_ext_frc);
        seq_printf(m, "support_fb1: %d\n", hw_ctx->b_support_fb1);
        seq_printf(m, "support_4kosd: %d\n", hw_ctx->b_support_4kosd);
        seq_printf(m, "\n");

        // (2020/01/18) read the real HW configuration NOT status value.
        // because application might refer this proc to make its reverse-mode config BEFORE kdriver initialization
        // see " user_initcall based HW initialization" policy.
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_M23_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, val);
        seq_printf(m, "mirror.status: 0x%08x\n", val);
        seq_printf(m, "\n");

        seq_printf(m, "hw_wa.1x_csr_disp_on_blend_path: 0x%x\n",
                   (hw_ctx->hw_wa_flag & FBDEV_M23_HW_WA_1X_CSR_DISP_ON_BLEND_PATH) ? 1 : 0);
        seq_printf(m, "hw_wa.osd0_async_wr_error:       0x%x\n",
                   (hw_ctx->hw_wa_flag & FBDEV_M23_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR) ? 1 : 0);
#ifdef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL
        seq_printf(m, "hw_wa.pqwfw_osd0_out_ctrl:       0x%x\n",
                   (hw_ctx->hw_wa_flag & FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL) ? 1 : 0);
#endif
        seq_printf(m, "hw_wa_flag:                      0x%x\n", hw_ctx->hw_wa_flag);
        seq_printf(m, "\n");
    }

#if 0
    /* print OSD_SHP info */
    {
        int xidx;
        int xnum, xlst[2];
        int fb_dev_id = LX_FBDEV_ID_OSD0;

        UINT32 bypass_en, detour_en;
        UINT32 rgb2yc_csc_en_de_clk, yc2rgb_csc_en, rgb2yc_csc_p_en_oclk, yuv2rgb_en;

        FBDEV_M23_SR_CTRL_T* sr_ctrl = FBDEV_M23_GET_SR_CTRL(hw_ctx, fb_dev_id);

        xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);
        FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

        xidx = xlst[0];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

        SHP0_CTRL_RdFL(shp_core_ctrl_00);
        OSDX_M23_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

        SHP0_CTRL_Rd01(shp_core_ctrl_00, reg_top_bypass, bypass_en);

        OSDX_M23_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, detour_en);
        OSDX_M23_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en_de_clk, rgb2yc_csc_en_de_clk);
        OSDX_M23_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_csc_en, yc2rgb_csc_en);
        OSDX_M23_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_p_en_oclk, rgb2yc_csc_p_en_oclk);
        OSDX_M23_Rd01(hdr_ui, osd_hdrui_yc2rgb_ctrl00, reg_yuv2rgb_en, yuv2rgb_en);

        seq_printf(m, "osd_sr.sw_status: 0x%x\n", sr_ctrl->status);
        seq_printf(m, "osd_sr.hw_status: 0x%x\n", !detour_en);

        seq_printf(m, "osd_sr.shp_ctrl0.bypass_en: 0x%x (fixed)\n", bypass_en);
        seq_printf(m, "osd_sr.bmp_ctrl0.detour_en: 0x%x\n", detour_en);

        seq_printf(m, "osd_sr.bmp_ctrl0.reg_rgb2yc_csc_en_de_clk: 0x%x\n", rgb2yc_csc_en_de_clk);
        seq_printf(m, "osd_sr.bmp_ctrl0.reg_yc2rgb_csc_en: 0x%x\n", yc2rgb_csc_en);
        seq_printf(m, "osd_sr.bmp_ctrl0.reg_rgb2yc_csc_p_en_oclk: 0x%x\n", rgb2yc_csc_p_en_oclk);
        seq_printf(m, "osd_sr.osd_hdrui_yc2rgb_ctrl00.reg_yuv2rgb_en: 0x%x\n", yuv2rgb_en);

        seq_printf(m, "\n");
    }
#endif

#if 0
    /* print 4kosd */
    {
        int xidx = 1; /* OSD_IMAGE0_1 */
        UINT32 osd_4k_mux;

        OSDX_M23_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0);
        OSDX_M23_Rd01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0, reg_4k_mode_en, osd_4k_mux);

        seq_printf(m, "4kosd.muxcfg: 0x%x\n", osd_4k_mux);
    }
#endif

    /* print HW_CTX status */

    /* TODO: add something */
}

/** chip specific proc handler
 *
 */
void FBDEV_M23_CMN_ProcHandler(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
    switch (proc_id)
    {
        case FBDEV_HW_PROC_ID_DETAIL_INFO:
        {
#if 0
            FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

            seq_printf(m, "<HW INFO>\n");
            seq_printf(m, "path: %s\n", (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? "bosd" : "sosd");
            seq_printf(m, "hw_disp_width: %d\n",    hw_ctx->hw_disp_width);
            seq_printf(m, "hw_disp_height: %d\n",   hw_ctx->hw_disp_height);
            seq_printf(m, "hw_fb0_width: %d\n",     hw_ctx->hw_fb0_width);
            seq_printf(m, "hw_fb0_height: %d\n",    hw_ctx->hw_fb0_height);
            seq_printf(m, "vsync_clk: %dHz\n", (FBDEV_M23_CMN_DetectVSyncClk() == FBDEV_VSYNC_CLK_60HZ) ? 60 : 120);

            seq_printf(m, "support_ext_frc: %d\n",  hw_ctx->b_support_ext_frc);
            seq_printf(m, "support_4kosd: %d\n",    hw_ctx->b_support_4kosd);
#endif
        }
        break;

        case FBDEV_HW_PROC_ID_OSD_HDR:
        {
            int i;
            int xidx;
            int xnum, xlst[2];

            UINT32  osd_en, sync_en;
            UINT32  hdr_lst[7];
            FBDEV_M23_OSD_HDR_T* osd_hdr = (FBDEV_M23_OSD_HDR_T*)hdr_lst;
            LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

            xnum = FBDEV_M23_CMN_GetHWXList(fb_dev_id, xlst);
            seq_printf(m, "posd_num: %d\n", xnum);

            for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
            {
                xidx = xlst[i];

                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

                OSDX_M23_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, osd_en);
                OSDX_M23_Rd01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_enable, sync_en);

                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr1);
                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr3);
                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr4);
                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr5);
                OSDX_M23_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);

                hdr_lst[0] = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr0);
                hdr_lst[1] = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr1);
                hdr_lst[2] = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr2);
                hdr_lst[3] = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr3);
                hdr_lst[4] = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr4);
                hdr_lst[5] = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr5);
                hdr_lst[6] = OSDX_M23_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);

                seq_printf(m, "posd_idx: %d\n",             xidx);
                seq_printf(m, " visible: %s (osd:%d, sync:%d)\n", (osd_en && sync_en) ? "on" : "off", osd_en, sync_en);
                seq_printf(m, " hdr.xpos: %d\n",            osd_hdr->osd_hdr_xpos);
                seq_printf(m, " hdr.ypos: %d\n",            osd_hdr->osd_hdr_ypos);
                seq_printf(m, " hdr.w_mem: %d\n",           osd_hdr->osd_hdr_w_mem);
                seq_printf(m, " hdr.h_mem: %d\n",           osd_hdr->osd_hdr_h_mem);
                seq_printf(m, " hdr.w_out: %d\n",           osd_hdr->osd_hdr_w_out);
                seq_printf(m, " hdr.h_out: %d\n",           osd_hdr->osd_hdr_h_out);
                seq_printf(m, " hdr.pixel_order: 0x%x\n",   osd_hdr->osd_hdr_pixel_order);
                seq_printf(m, " hdr.wpl: %d\n",             osd_hdr->osd_hdr_wpl);
                seq_printf(m, " hdr.global_alpha_en: %d\n", osd_hdr->osd_hdr_global_alpha_en);
                seq_printf(m, " hdr.global_alpha: 0x%x\n",  osd_hdr->osd_hdr_global_alpha);
                seq_printf(m, " hdr.color_key_en: %d\n",    osd_hdr->osd_hdr_color_key_en);
                seq_printf(m, " hdr.color_key: 0x%x\n",     osd_hdr->osd_hdr_color_key);
                seq_printf(m, " hdr.ptr_plte: 0x%x\n",      osd_hdr->osd_hdr_ptr_plte);
                seq_printf(m, " hdr.ptr_bmp: 0x%x\n",       osd_hdr->osd_hdr_ptr_bmp);
            }
        }
        break;

        case FBDEV_HW_PROC_ID_REG_DUMP:
        {
            int     i;
            UINT32  off;
            UINT32  val;

            struct
            {
                char*  desc;
                UINT32 reg_base;
                UINT32 reg_size;
            } reg_list[] =
            {
                { .desc = "OSD",  .reg_base = M23_CCO_BASE,                 .reg_size = sizeof(OSD_M23_REG_T) },
                { .desc = "TOP",  .reg_base = M23_CCO_TOP_CTRL_BASE,        .reg_size = sizeof(OSD_TOP_M23_REG_T) },
                { .desc = "AFBC0", .reg_base = M23_CCO_AFBC0_BASE,           .reg_size = sizeof(OSD_AFBC_M23_REG_T) },
                { .desc = "MIF0", .reg_base = M23_CCO_MIF0_BASE,            .reg_size = sizeof(OSD_MIF_M23_REG_T) },
            };

            for (i = 0; i < NELEMENTS(reg_list); i++)
            {
                seq_printf(m, "\n\n");
                seq_printf(m, "FBDEV (%s) : 0x%08x (size=%d)\n", reg_list[i].desc, reg_list[i].reg_base, reg_list[i].reg_size);

                for (off = 0; off < reg_list[i].reg_size; off += 4)
                {
                    UINT32 reg_addr = reg_list[i].reg_base + off;

                    OS_RdReg(reg_addr, &val);
                    seq_printf(m, " 0x%08x (+0x%04x) = %08x\n", reg_addr, off, val);
                }
            }
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }
}

/*========================================================================================
    Implementation Group (Suspend/Resume)
========================================================================================*/
/** common resume/suspend handler
 *
 */
int FBDEV_M23_CMN_RunResume(void)
{
    /* OSD freeze will be stopped after 500 ms */
    FBDEV_M23_CMN_RunBootLogoTimer(fbdev_resume_freeze_timeout, TRUE);

    FBDEV_M23_CMN_ReInitHW();

    return RET_OK;
}

int FBDEV_M23_CMN_RunSuspend(void)
{
    /* do nothing */
    return RET_OK;
}

/*========================================================================================
    common OSD HW handler
========================================================================================*/
FBDEV_M23_HW_FUNC_T  g_fbdev_m23_cmn_hw_func =
{
    /* variable is initialize at fbdev_drv_M23.c */

    .M23_InitHW          = FBDEV_M23_CMN_InitHW,
};

