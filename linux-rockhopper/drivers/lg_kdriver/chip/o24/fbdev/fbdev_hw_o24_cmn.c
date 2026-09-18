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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     raxis.lim
 *  @version    1.0
 *  @date       2021-04-01
 *  @note       Additional information.
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
#include "fbdev_hw_o24.h"
#include "osd_reg_o24.h"
#include "osd_shp_reg_o24.h"
#include "osd_afbc_reg_o24.h"
#include "osd_afrc_reg_o24.h"
#include "osd_top_ctrl_reg_o24.h"
#include "osd_top_ctrl1_reg_o24.h"
#include "osd_mif0_reg_o24.h"
#include "osd_mif1_reg_o24.h"
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/seq_file.h>
#include <linux/fb.h>

#include "hma_alloc.h"

#ifdef FBDEV_O24_USE_CTOP_REGS
#include "../sys/sys_regs.h"
#endif

#ifdef INCLUDE_KDRV_OVI
#include "be_kapi.h"
#include "ovi_hal.h"
#endif

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif

#include "afbc_sw_drv.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define CHECK_AFBC_FBDEV(id)        ((id)==LX_FBDEV_ID_OSD0 || (id)==LX_FBDEV_ID_OSD1)
#define CHECK_AFRC_FBDEV(id)        ((id)==LX_FBDEV_ID_OSD0 || (id)==LX_FBDEV_ID_OSD1)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int FBDEV_O24_CMN_MirrorCtrl(BOOLEAN v_mirror_en);

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
static void FBDEV_O24_CMN_InitFBCEnv(void);
static void FBDEV_O24_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt);

static void FBDEV_O24_CMN_InitCropEnv(void);
static void FBDEV_O24_CMN_SetupSRScaler(BOOLEAN onoff, BOOLEAN bForce);

static void FBDEV_O24_CMN_SetupExternalRenderer(int fb_dev_id, struct fb_info* fbinfo);
static void FBDEV_O24_CMN_AllocExternalRendererFrameBuffer(void);
static void FBDEV_O24_CMN_DestroyExternalRendererFrameBuffer(void);
static void FBDEV_O24_CMN_SetOutputCropRegion(BOOLEAN crop_en, int img_width, int img_height, int xoffset, int yoffset,
        LX_RECT_T* crop_pos);

static void FBDEV_O24_CMN_ReInitHW(void);
static void FBDEV_O24_CMN_InitMirrorEnv(void);
static FBDEV_VSYNC_CLK_T FBDEV_O24_CMN_DetectVSyncClk(void);

static int  FBDEV_O24_CMN_CheckPQEDriverInitialization(void);
static void FBDEV_O24_CMN_NotifyPQEDriver(void);
static void FBDEV_O24_CMN_WaitPQEDriverEstreamerSync(int checker);

static void FBDEV_O24_CMN_BootLogoClearScheduler(struct work_struct* work);

static void FBDEV_O24_CMN_ShutdownOSDPath(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_osd_hdr_spinlock);

static struct workqueue_struct* fbdev_o24_wq;
static DECLARE_DELAYED_WORK(boot_logo_clear_work, FBDEV_O24_CMN_BootLogoClearScheduler);

static int  osd_boot_freeze_timeout = 0;    /* see SICDTV-8491. set 0 by default */
static int  osd_resume_freeze_timeout = 0;  /* see SICDTV-8491. set 0 by default */
static int  osd_pqefw_osd0_out_ctrl = 1;    /* SICDTV-4359 */

static int  osd_enable_logo_clear = 0;    /* see SICDTV-8556 */
static int  osd_boot_logo_clear_timeout = 3000; /* see SICDTV-8556 */
static int  osd_resume_logo_clear_timeout = 2000; /* see SICDTV-8556 */

static BOOLEAN osd_logo_migration_required = TRUE;
static BOOLEAN osd_pqefw_ipc_enabled = TRUE; /* see SICDTV-12981 */

static int  osd_fbc_version = FBDEV_HW_AFBC_VER_1_1; /* 0x10:AFBC1.0, 0x11:AFBC 1.1, 0x20:AFRC see SICDTV-9405 */

module_param_named(fbdev_o24_boot_freeze_timeout, osd_boot_freeze_timeout, int, 0644);
module_param_named(fbdev_o24_resume_freeze_timeout, osd_resume_freeze_timeout, int, 0644);

module_param_named(fbdev_o24_pqefw_osd0_out_ctrl, osd_pqefw_osd0_out_ctrl, int, 0644);

module_param_named(fbdev_o24_enable_logo_clear, osd_enable_logo_clear, int, 0644);
module_param_named(fbdev_o24_boot_logo_clear_timeout, osd_boot_logo_clear_timeout, int, 0644);
module_param_named(fbdev_o24_resume_logo_clear_timeout, osd_resume_logo_clear_timeout, int, 0644);

module_param_named(fbdev_o24_afbc_version, osd_fbc_version, int, 0644);

static int osd_hw_pm_suspend_stage = 0;
static int osd_hw_pm_restore_stage = 0;

static int osd_use_shutdown_path_on_suspend = 1;  /* see SICDTV-9009, SICDTV-9992 */
module_param_named(fbdev_o24_use_shutdown_path_on_suspend, osd_use_shutdown_path_on_suspend, int, 0644);

#if 0
#define CHECK_REGS(id)  __check_regs(id, __FUNCTION__,__LINE__)
static void __check_regs(int id, const char* func, const int line)
{
}
#endif

static unsigned long fbdev_bootlogo_fbmem_addr = 0x0;

static int fbdev_afbc_estreamer = 1;
module_param_named(fbdev_o24_afbc_estreamer, fbdev_afbc_estreamer, int, 0644);

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
int FBDEV_O24_CMN_GetHWXList(int fb_dev_id, int xlst[2])
{
    int afbc_xlst[2];

    return FBDEV_O24_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
}

int FBDEV_O24_CMN_GetHWXListEx(int fb_dev_id, int xlst[2], int afbc_xlst[2])
{
    int num_xlst = 0;
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    switch (fb_dev_id)
    {
        case LX_FBDEV_ID_OSD0:
        {
            if (hw_ctx->b_support_4kosd)        {num_xlst = 2; xlst[0] = 0; xlst[1] = 1; afbc_xlst[0] = 0; afbc_xlst[1] = 1;}
            else                                {num_xlst = 1; xlst[0] = 0; xlst[1] = -1; afbc_xlst[0] = 0; afbc_xlst[1] = -1;}
        }
        break;

        // (2021/07/05)
        // fb1 는 실제 존재 하지 않으며, E-Streamer 등의 특수 목적으로만 사용할 수 있다.
        // 따라서 fb0, fb1 은 동일한 HW 를 설정할 수 있도록 조치한다.
        // fb1 은 4K OSD 전용이다.
        //
        // (2023/03/28) see http://clm.lge.com/issue/browse/SCDCR-5906
        // 4K TV 에서 E-Streamer 를 지원하는 경우를 추가 고려한다.
        case LX_FBDEV_ID_OSD1:
        {
            if (hw_ctx->b_support_ext_render)   {num_xlst = 2; xlst[0] = 0; xlst[1] = 1; afbc_xlst[0] = 0; afbc_xlst[1] = 1;}
            else if (hw_ctx->b_support_fb1)     {num_xlst = 1; xlst[0] = 0; xlst[1] = -1; afbc_xlst[0] = 0; afbc_xlst[1] = -1;}
            else                                {num_xlst = 0; xlst[0] = -1; xlst[1] = -1; afbc_xlst[0] = -1; afbc_xlst[1] = -1;}
        }
        break;

        case LX_FBDEV_ID_CSR0:                  {num_xlst = 1; xlst[0] = 3; xlst[1] = -1; afbc_xlst[0] = -1; afbc_xlst[1] = -1;} break;

        default:                                {num_xlst = 0; xlst[0] = -1; xlst[1] = -1; afbc_xlst[0] = -1; afbc_xlst[1] = -1;} break;
    }

    return num_xlst;
}

BOOLEAN  FBDEV_O24_CMN_IsUHDDispMode(void)
{
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    return (hw_ctx->hw_disp_width > 2048) ? TRUE : FALSE;
}

#ifdef FBDEV_O24_USE_REVERSE_HW_CTRL
/** check if current OSD HW is set as the reverse mode
 *
 */
static BOOLEAN  FBDEV_O24_CMN_IsReverseMode(int fb_dev_id)
{
    /* @note how to check reverse OSD mode ? */
    return FALSE;
}
#endif

/** enable OSD HW update
 *
 *  if OSD header flag is not set, OSD is not updated !
 *
 */
static void FBDEV_O24_CMN_EnableOSDHdrFlush(ULONG data)
{
    int i;

    FBDEV_NOTI("<!> enable osd_hdr_flush & exit OSD freeze stage. afbc=%d, afrc=%d\n",
               FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0),
               FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFRC, LX_FBDEV_ID_OSD0));

    /* enable osd_hdr_flush to unfreeze OSD */
    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(i);
        struct scanvas*  canvas = FBDEV_GetWinCanvas(i);

        FBDEV_BOOT_DEBUG("++ fb(%d)\n", i);

        FBDEV_CHECK_CODE(NULL == wctx, continue, "invalid fb(%d) ctx\n", i);
        FBDEV_CHECK_CODE(NULL == canvas, continue, "invalid fb(%d) canvas\n", i);

        //FBDEV_CHECK_CODE(!g_fbdev_cfg->fb[i].b_active, continue, "inactive fb(%d)\n", i);

        /* if freeize is already disabled, ignore osd hdr flush */
        if (wctx->status.b_osd_hdr_flush)
        {
            FBDEV_HW_DEBUG("fb(%d) osd_hdr_flush is already enabled\n", i);
            continue;
        }

        FBDEV_NOTI("++ fb(%d) flip_cnt = %d, total_flip_cnt = %d\n",
                   i, wctx->status.fb_flip_cnt, wctx->status.total_fb_flip_cnt);

        wctx->status.b_osd_hdr_flush = TRUE;

        /* (2020/06/11)
         * 수정된 OSD 초기화 정책에 의하여 이 함수는 단순히 b_osd_hdr_flush 를 활성화 하는 역할로
         * 축소한다. 향후 함수 목적을 수정하거나, 완전히 삭제할 수도 있음
         */
        /* do nothing */
    }
}

/** override the default boot_freeze_timeout
 *
 */
void FBDEV_O24_CMN_SetBootFreezeTimeout(int val)
{
    if (osd_boot_freeze_timeout != val)
    {
        printk("+ boot_freeze_timeout %d -> %d\n", osd_boot_freeze_timeout, val);
        osd_boot_freeze_timeout = val;
    }
}

/** clear current logo screen after a few seconds after OSD initialization
 *
 */
static void FBDEV_O24_CMN_BootLogoClearScheduler(struct work_struct* work)
{
    FBDEV_NOTI("logo clear work started\n");
    osd_logo_migration_required = TRUE;
    FBDEV_O24_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_CLEAR);
}

/** move boot logo framebuffer to safe region (prototype implementation)
 *
 */
void        FBDEV_O24_CMN_MigrateBootLogo(FBDEV_O24_BOOT_LOGO_MODE_T mode)
{
#if (CONFIG_LX_BOOT_LOGO==1)

#define OSD_CTRL_BASE(layer)    ((UINT32)(O24_CCO_BASE + 0x200 + (0x100*(layer))))

    int i;
    int rc;
    OS_CACHE_MAP_T cmap_src, cmap_dst;

    UINT32      image_size;
    int         afbc_mode = 0;
    UINT32      fbmem_addr_src = 0;
    UINT32      fbmem_addr_dst = 0;

    /* allow this function to run once at cold boot regardless of result */
    if (osd_logo_migration_required == FALSE)
    {
        FBDEV_WARN("ignore request\n");
        return;
    }

    osd_logo_migration_required = FALSE;

    memset(&cmap_src, 0x0, sizeof(OS_CACHE_MAP_T));
    memset(&cmap_dst, 0x0, sizeof(OS_CACHE_MAP_T));

    image_size = afbc_sw_get_image_size(NULL, 1920, 1080);
    image_size = ALIGN(image_size, (1 << 20));

    /* (2020/05/21) code ready for surface poool set to CMA type
     * AS-IS: bootlogo image is copied to the last region of "surface" memrory pool
     * TO-BE: bootlogo image is copied to "debug0" memory pool
     *
     * 기존 방식은 surface 메모리풀의 특정 고정된 영역에 일방적으로 백업 이미지를 복사하는 것으로 CMA 속성에 대응이 불가하다.
     * 신규 방식에서는 debug0 에서 임시 메모리를 할당 받도록 한다.
     * 할당된 메모리는 fbdev_bootlogo_fbmem_addr 에 저장되며, FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE 에서 해제된다.
     */
    fbmem_addr_dst = hma_alloc("debug0", image_size, PAGE_SIZE);
    FBDEV_CHECK_ERROR(!fbmem_addr_dst, return, "dst bfufer alloc error\n");

    /* read OSD0 framebuffer */
    OSDX_CTRL_RdFL(osdx_ctrl[0], osd_ctrl_hdr6);
    OSDX_CTRL_Rd01(osdx_ctrl[0], osd_ctrl_hdr6, osd_hdr_ptr_bmp, fbmem_addr_src);

    FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "reg op fail\n");
    FBDEV_WARN("logo fbmem (old) = 0x%08x\n", fbmem_addr_src);

    afbc_mode = (FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0)) ? 1 : 0;

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
    else if (mode == BOOT_LOGO_MODE_IMAGE_CLEAR)
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
    else /* NONE */
    {
        FBDEV_WARN("++ BOOT_LOGO_MODE_IMAGE_NONE: do nothing ++ \n");
    }

    /* update AFBC0 framebuffer */
    if (afbc_mode)
    {
        OSD_AFBC_CTRL_Wr01(0, ctrl_afbc_1, hd_base,      fbmem_addr_dst);
        OSD_AFBC_CTRL_Wr01(0, ctrl_afbc_8, pl_data_base, fbmem_addr_dst);
        OSD_AFBC_CTRL_WrFL(0, ctrl_afbc_1);
        OSD_AFBC_CTRL_WrFL(0, ctrl_afbc_8);

        /* raxis.lim (2019/10/23)
         * becuase hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
         * we should set hdr_ready_flag=1 here to update real framebuffer address
         */
        OSD_AFBC_CTRL_RdFL(0, ctrl_afbc_0);
        OSD_AFBC_CTRL_Wr01(0, ctrl_afbc_0, update_ready_flag, 0x1);
        OSD_AFBC_CTRL_WrFL(0, ctrl_afbc_0);
    }

    /* update OSD framebuffer */
    for (i = 0; i < FBDEV_O24_MAX_OSD_BLK_NUM; i++)
    {
        OSDX_CTRL_Wr(osdx_ctrl[i], osd_base_addr, fbmem_addr_dst); // osd_bad_addr
        OSDX_CTRL_Wr(osdx_ctrl[i], osd_ctrl_hdr5, fbmem_addr_dst); // osd_ctrl_hdr5.ptr_plte
        OSDX_CTRL_Wr(osdx_ctrl[i], osd_ctrl_hdr6, fbmem_addr_dst); // osd_ctrl_hdr6.ptr_bmp

        OSDX_CTRL_WrFL(osdx_ctrl[i], osd_base_addr);
        OSDX_CTRL_WrFL(osdx_ctrl[i], osd_ctrl_hdr5);
        OSDX_CTRL_WrFL(osdx_ctrl[i], osd_ctrl_hdr6);
    }

    /* raxis.lim (2019/10/23)
     * becuase osd_hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
     * we should set osd_hdr_ready_flagn=1 here to update real framebuffer address
     */

    OSDX_CTRL_RdFL(osdx_ctrl[0], osd_ctrl_main);
    OSDX_CTRL_Wr01(osdx_ctrl[0], osd_ctrl_main, osd_hdr_ready_flag_en, 1);
    OSDX_CTRL_Wr01(osdx_ctrl[0], osd_ctrl_main, osd_hdr_ready_flag, 1);
    OSDX_CTRL_WrFL(osdx_ctrl[0], osd_ctrl_main);

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

#else
    FBDEV_NOTI("boot logo disabled, so ignore logo migration\n");
#endif
}

/**
 *
 */
void FBDEV_O24_CMN_RunBootLogoTimer(UINT32 ms, BOOLEAN bForce)
{
    FBDEV_BOOT_DEBUG("start bootlogo timer %d ms whth force=%d, bootlogo=%d\n", ms, bForce, CONFIG_LX_BOOT_LOGO);

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
            OS_StartTimer(&osd_en_timer, FBDEV_O24_CMN_EnableOSDHdrFlush, OS_TIMER_TIMEOUT, ms, 0x0);
        }
        else
        {
            FBDEV_O24_CMN_EnableOSDHdrFlush(0x0);
        }
    }

#else
    FBDEV_O24_CMN_EnableOSDHdrFlush(0x0);
#endif
}

/** query tcon clk information & detect vsync clk interval
 *
 *  @note this function should be called after SYS kdriver initialization
 */
static FBDEV_VSYNC_CLK_T FBDEV_O24_CMN_DetectVSyncClk(void)
{
#if (defined FBDEV_O24_USE_CTOP_REGS && defined INCLUDE_KDRV_SYS)
    UINT32 val;
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_VSYNC_CLK_T clk = FBDEV_VSYNC_CLK_60HZ; /* default = 60Hz */

    CTOP_CTRL_O24Ax_RdFL(SCRG_CTRL_TCON, crg_tcon5);
    val = CTOP_CTRL_O24Ax_RdFd(SCRG_CTRL_TCON, crg_tcon5, reg_pix2_clk_sel);

    /* when BLEND path, read tcon clock */
    if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
    {
        if (val == 0x0 || val == 0x2) /* 0: 4K120, 2: 2K120 */
        {
            clk = FBDEV_VSYNC_CLK_120HZ;
        }

        FBDEV_NOTI("B.OSD vsync detection = %d (%dHz)\n", val, (val == 0 || val == 2) ? 120 : 60);
    }

    return clk;
#else
    FBDEV_NOTI("SYNC detector not ready.. default vsync = 60Hz\n");
    return FBDEV_VSYNC_CLK_60HZ;
#endif
}

static void FBDEV_O24_CMN_NotifyPQEDriver(void)
{
#ifdef INCLUDE_KDRV_OVI
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

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

static int  FBDEV_O24_CMN_CheckPQEDriverInitialization(void)
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

// PQE (혹은 F22) 에게 전달되는 정보가 반영되었는지 확인이 필요할때, 최소 2개의 vsync wait 를 보장해야 한다.
// 이 함수는 B.OSD path 에서만 의미가 있으며, S.OSD path 에서는 F22 에서 필요시 처리를 해주기 때문에, 최소
// usleep 으로 대응하도록 한다.
//
// (2023/10/12) OSD kdriver 와 PQE FW 간의 estreamer 상태 동기화를 추가한다.
// 67.2 ms ( 60Hz 기준으로 약 4 vsync ) 정도 충분히 wait 하도록 한다.
// see http://clm.lge.com/issue/browse/SICDTV-13258
//
// (2023/11/06) 동기화를 위한 polling 주기와 max timeout 값을 조정한다.
// SoCTS 기준인 최대 50ms 가 넘어가지 않도록 45ms(5ms x 9회) wait 하도록 한다.
//
static void FBDEV_O24_CMN_WaitPQEDriverEstreamerSync(int checker)
{
#ifdef INCLUDE_KDRV_OVI

    /* see be/top/be_top_hal.h */
    extern int BE_TOP_HAL_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T * pstParams);
    LX_BE_FW_OSD_STATUS_T pqe2osd_status;

#define PQE_VSYNC_CNT 9 // 5.0 ms * 9 = 45 ms

    int i;
    UINT64 base_tick = OS_GetMsecTicks();

    if (osd_hw_pm_suspend_stage)
    {
        FBDEV_NOTI("+ wait for PQE FW to sync estreamer. skip by the suspending stage\n");
        return;
    }

    if (!osd_pqefw_ipc_enabled)
    {
        FBDEV_NOTI("+ wait for PQE FW to sync estreamer. skip by the disabled pqe ipc\n");
        return;
    }

    for (i = PQE_VSYNC_CNT; i > 0; i--)
    {
        usleep_range(5000, 5000); // fixed 50ms

        if (RET_OK == BE_TOP_HAL_GetFWOSDStatus(&pqe2osd_status))
        {
            FBDEV_NOTI("+ wait for PQE FW to sync estreamer. req=%d, ack=%d, time=%dms\n",
                       checker,
                       pqe2osd_status.bFwEstreamerOn,
                       (int)(OS_GetMsecTicks() - base_tick));

            if (pqe2osd_status.bFwEstreamerOn == checker)
            {
                return;
            }
        }
    }

    FBDEV_ERROR("+ wait for PQE FW to sync estreamer. timeout!! \n");
#endif
}

/*========================================================================================
    Implementation Group (OSD HW Initialization)
========================================================================================*/

/** initialize HW SOC
 *
 *
 */
int FBDEV_O24_CMN_InitHW(void)
{
    int i;
    UINT32 disp_width, disp_height;
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    int sosd_num = 1;
    int bosd_num = 2;
    BOOLEAN osd_shp_en = TRUE; /* turn on OSD_SR by default */

    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> user_initcall not ready +++\n");

    disp_width = hw_ctx->hw_disp_width;
    disp_height = hw_ctx->hw_disp_height;

    FBDEV_HW_DEBUG("(Re)Init OSD(O24) HW.. disp_size %dx%d\n", disp_width, disp_height);

    /* initialize S.OSD & B.OSD mixer disp size */
    for (i = 0; i < sosd_num; i++)
    {
        OSDX_CTRL_RdFL(osdx_sep_osd_mixer[i], ctrl_sosd_mixer_disp_size);
        OSDX_CTRL_Wr02(osdx_sep_osd_mixer[i], ctrl_sosd_mixer_disp_size, reg_sosd_disp_size_w, hw_ctx->sosd_disp.out_width,
                       reg_sosd_disp_size_h, hw_ctx->sosd_disp.out_height);
        OSDX_CTRL_WrFL(osdx_sep_osd_mixer[i], ctrl_sosd_mixer_disp_size);
    }

    for (i = 0; i < bosd_num; i++)
    {
        OSDX_CTRL_RdFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size);
        OSDX_CTRL_Wr02(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size,   reg_bosd_disp_size_w, hw_ctx->bosd_disp.out_width,
                       reg_bosd_disp_size_h, hw_ctx->bosd_disp.out_height);
        OSDX_CTRL_WrFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size);
    }

    /* setup all OSD common disp size */
    for (i = 0; i < FBDEV_O24_MAX_OSD_DISP_NUM /*8*/; i++)
    {
        OSD_CTRL_RdFL(osdx_common_disp_size[i]);
        OSD_CTRL_Wr01(osdx_common_disp_size[i], reg_common_disp_size_w, disp_width);
        OSD_CTRL_Wr01(osdx_common_disp_size[i], reg_common_disp_size_h, disp_height);
        OSD_CTRL_WrFL(osdx_common_disp_size[i]);
    }

    /* O24 has the fixed mux value. DO NOT change */
    {
        UINT32 mixer_mux_value = 0x76543210;
        FBDEV_NOTI("(Re)Init OSD(O24) mixer mux order = 0x%08x\n", mixer_mux_value);

        OSDX_CTRL_Wr(osdx_sep_osd_mixer[0],      ctrl_sosd_mixer_mux1, mixer_mux_value);
        OSDX_CTRL_WrFL(osdx_sep_osd_mixer[0],    ctrl_sosd_mixer_mux1);

        OSDX_CTRL_Wr(osdx_blend_osd_mixer[0],    ctrl_bosd_mixer_mux1, mixer_mux_value);
        OSDX_CTRL_WrFL(osdx_blend_osd_mixer[0],  ctrl_bosd_mixer_mux1);

        OSDX_CTRL_Wr(osdx_blend_osd_mixer[1],    ctrl_bosd_mixer_mux1, mixer_mux_value);
        OSDX_CTRL_WrFL(osdx_blend_osd_mixer[1],  ctrl_bosd_mixer_mux1);
    }

    /* raxis.lim (2014/11/11) tune osd sync pulse timer
     * CCO_CTRL.CTRL_SOSD_PLUS.reg_disp_sosd_timer controls the delay the OSD mix start time in cycle unit.
     * OSD HW engineer recommend to use 0x3000 (almost 10 line delay) can fix OSD sync & isr mismatch issue.
     *
     * value 0x3000 has been determinted at H15 development
     *
     * raxis.lim (2016/03/28) set bosd_pulse as 0x3000 (used at O24 for the first time)
     *
     */
    OSD_TOP_CTRL_RdFL(ctrl_sosd_pulse);
    OSD_TOP_CTRL_Wr01(ctrl_sosd_pulse, reg_disp_pulse_timer, hw_ctx->sosd_disp.pulse_timer_dly);
    OSD_TOP_CTRL_WrFL(ctrl_sosd_pulse);

    OSD_TOP_CTRL_RdFL(ctrl_bosd_pulse);
    OSD_TOP_CTRL_Wr01(ctrl_bosd_pulse, reg_disp_pulse_timer, hw_ctx->bosd_disp.pulse_timer_dly);
    OSD_TOP_CTRL_WrFL(ctrl_bosd_pulse);

    /* (2020/04/20)
     * when 4K OSD is enabled, turn off OSD_SR because HW is specialized for 2K to 4K upscaling
     * when Non UHD display mode, turn off OSD_SR
     *
     * (2020/07/14)
     * when EXT_FRC(F22) is connected, OSD_SR is handled by F22 not O24
     */
    if (hw_ctx->b_support_4kosd || hw_ctx->b_support_ext_frc || !FBDEV_O24_CMN_IsUHDDispMode())
    {
        osd_shp_en = FALSE;
    }

    FBDEV_NOTI("initial OSD_SR=%d (4k_osd=%d, ext_frc=%d, uhd_disp=%d)\n",
               osd_shp_en, hw_ctx->b_support_4kosd, hw_ctx->b_support_ext_frc, FBDEV_O24_CMN_IsUHDDispMode());
    FBDEV_O24_CMN_SetupSRScaler(osd_shp_en, TRUE);

    FBDEV_O24_CMN_InitMirrorEnv();
    FBDEV_O24_CMN_InitCropEnv();
    FBDEV_O24_CMN_InitFBCEnv();

    return RET_OK;
}

/** make OSD to be initial state
 *  make the basic configuration for each OSD layer.
 *
 *  @param layerId
 */
int FBDEV_O24_CMN_InitOSDLayer(int fb_dev_id)
{
    int i;
    int xidx;
    int xnum, xlst[2];
    int ret = RET_ERROR;

    /* please refer to OSD manual OSD<x>_CFG field */
    UINT32  hdr_src_sel;
    UINT32  osd_memhdr_addr;
    BOOLEAN osd_en = 0x0;           /* off by default */
    BOOLEAN hdr_rdy_flag = 0x0;     /* OFF by default */
    BOOLEAN v_mirror_en = 0x0;      /* OFF by default */

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_MIRROR_CTRL_T* mirror_ctrl = FBDEV_O24_GET_MIRROR_CTRL(hw_ctx);

    /* fetch the current output disp size */
    UINT32  disp_width = hw_ctx->hw_disp_width;
    UINT32  disp_height = hw_ctx->hw_disp_height;

    /* if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration)  */
    if (!hw_ctx->user_initcall_ctrl.ready)
    {
        FBDEV_NOTI("<i> fb(%d) user_initcall not ready +++\n", fb_dev_id);
        return RET_OK;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_render)
    {
        FBDEV_NOTI("fb(%d) ignore. ext_render disabled\n", fb_dev_id);
        return RET_ERROR;
    }

    FBDEV_NOTI("fb(%d) configure osd layer\n", fb_dev_id);

    xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

    /* hdr_src_sel 0x0: DDR, 0x1: REG */
    hdr_src_sel = (g_fbdev_hwio_cfg->hdr_op_method == FBDEV_HDR_OP_MMIO) ? 0x0 : 0x1;
    osd_memhdr_addr = (gMemCfgFBHdr[fb_dev_id].mem_header_base);

    v_mirror_en = (mirror_ctrl->status & FBDEV_O24_V_MIRROR_ON) ? 0x1 : 0x0;

    /* choose the initial osd visibility based on boot logo configuration */
    switch (fb_dev_id)
    {
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==0)

        case LX_FBDEV_ID_OSD0:  osd_en = 0x1; break;
#endif

        default:                osd_en = 0x0; break;
    }

#ifdef FBDEV_O24_USE_HDR_RDY_REG
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
         */
        sync_disp_width = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? disp_width / 2 : disp_width;

        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_pdec);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_swap);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_base_addr);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_sync1);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_scaler);

        /* (2020/12/15) remove the early osd_en control
         * osd will be enabled after the frist image update is completed
         * see FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE handler
         * see http://clm.lge.com/issue/browse/SICDTV-9043
         * see http://hlm.lge.com/qi/browse/INQAISSUE-81
         */
#if 0
        /* OSD HW requests to write both osd_en & osd_sync_enable to control osd visibility */
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main,   osd_en,         osd_en);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0,  osd_sync_enable, osd_en);
#endif

        /* raxis.lim (2014/06)
         * if BLEND mode, each OSD layer should have a half of real display size (it's HW spec)
         * this restruction is also applied to the cursor layer.
         */
        sync_hdouble_en = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? 0x0 : 0x1;

        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_hdouble_en, sync_hdouble_en);

        /* use osd_hdr_flag to avoid the possible OSD mis-configuration when OSD header is set across vsync */
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_ready_flag_en, hdr_rdy_flag);

        /* normally osd_hdr_src_sel is fixed to "read from hw register" not "DDR contains osd_hdr data" */
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_src_sel,      hdr_src_sel);

        /* configure mirror mode every layer initialization */
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en,     v_mirror_en);

        /* configure CSR0 sync for mirror mode to support virtically reversed position */
        if (fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_CSR0)
        {
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_v_reverse, v_mirror_en);
        }

        /* we should set DDR memory to hold osd_hdr data, but NOT used in normal case
         * remember that OSD always fetch header data from DDR regardless of hdr_src_sel value
         * it's safe that I set the same address as the frame buffer
         */
        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_base_addr,  osd_memhdr_addr);

#if 0 /* KEEP HW DEFAULT */
        /* set scaler sample mode to the same behavior as that of GFX */
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler, osd_sc_sampling_mode,    0x1);
#endif

        /* initialize cursor attribute (OSD4 only) */
        if (fb_dev_id == LX_FBDEV_ID_CSR0)
        {
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler, reg_crsr_h_x2_en,    0x0);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler, reg_crsr_v_x2_en,    0x0);
        }

        /* MIF feeder cfg : "10 (0x2)" L to R (HW default value)
         * this value has ben fixed to "10" inside OSD HW since older chip.
         * In O24/O24, this value can be configurable by SW But I keep this value as 0x2 forever
         *
         * HW default value = 0x2
         */
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main,   osd_manual_dlr,     0x2);

        /* raxis.lim (2019/10/17) -- fix pdec & swap configuration. re-write HW default again.
         *
         * pdec=0xe4000000, swap=0x000 equals pdec=0x1b000000, swap=0x333
         *
         */
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_alpha,           0x0);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_red,             0x1);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_green,           0x2);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_blue,            0x3);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_round,              0x0);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_pure_ck,            0x0);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_lfsr_seed,          0x0);

        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_ctrl_swap,   0x00000333);

#ifdef FBDEV_O24_USE_EXPERIMENTAL_CONFIG

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
            UINT32 buf_mode_en = (FBDEV_O24_CMN_IsUHDDispMode()) ? 0x0 : 0x1;
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler, reg_osd_buf_mode_en_n, buf_mode_en);
        }

#endif

        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_pdec);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_swap);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_base_addr);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_scaler);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);

        // TODO: add more initialization if necessary

        // setup OSD basic path & sync. primary osd only.
        //
        // raxis.lim (2019/05/21)
        // OSD_IMAGE0_1 doesn't have osd_ctrl_path, osd_ctrl_sync etc
        if (i == 0x0)
        {
            OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_path);
            ctrl_direc = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? 0x0 : 0x1;
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_direc, ctrl_direc);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_eo2s,  ctrl_direc);

            // setup each display size
            // keep in mind that width value osd_ctrl_path, osd_ctrl_sync1 is NOT real disp_width.
            // they should be set a half when B.OSD is activated.
            // these field is used to control how OSD fetch & process OSD frame data.
            //
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_path, reg_ctrl_path_width, sync_disp_width);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_bosd_pos,   0x0);   /* fixed to 0x0(BOSD1) */
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_path);

            OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_sync1);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_sync1, osd_sync_disp_w, sync_disp_width);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_sync1, osd_sync_disp_h, disp_height);
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_sync1);
        }

        /* setup 4K osd configuration. OSD_IMAGE0_1 only */
        if (hw_ctx->b_support_4kosd && fb_dev_id == LX_FBDEV_ID_OSD0 && i == 0x1 /* second posd */)
        {
            OSDX_CTRL_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0);
            OSDX_CTRL_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_1);
            OSDX_CTRL_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
            OSDX_CTRL_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3);

            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0, reg_4k_mode_en, 1);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_w, hw_ctx->hw_fb0_width);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_h, hw_ctx->hw_fb0_height);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3, reg_sc_o_w, disp_width);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3, reg_sc_o_h, disp_height);

            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_1, reg_4k_xpos, 0);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_1, reg_4k_ypos, 0);

            OSDX_CTRL_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0);
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_1);
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3);
        }
    }

    ret = RET_OK;   /* all work done */
func_exit:
    return ret;
}

static void FBDEV_O24_CMN_SafeSyncEnable(void)
{
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    // if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration) */
    FBDEV_CHECK_ERROR(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");

    FBDEV_WARN("++ PIC_INIT ++ (I-BOOT)\n");

    // raxis.lim (2019/08/07) -- DO NOT full value to pic_init.
    // refer to http://clm.lge.com/issue/browse/AVTASK-386?focusedCommentId=1964037&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-1964037
    OSD_TOP_CTRL_RdFL(pic_init);
    OSD_TOP_CTRL_Wr01(pic_init, g0_auto_init, 0x1);
    OSD_TOP_CTRL_Wr01(pic_init, g1_auto_init, 0x1);
    OSD_TOP_CTRL_Wr01(pic_init, g4_auto_init, 0x1);
    OSD_TOP_CTRL_WrFL(pic_init);
}

static void FBDEV_O24_CMN_ReInitHW(void)
{
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");

    FBDEV_O24_InitHW();
    FBDEV_SetInterruptEnable(MIXER_INTR, 1);

    // O24 OSD supports only OSD0, OSD1 & OSD3
    FBDEV_O24_CMN_InitOSDLayer(LX_FBDEV_ID_OSD0);
    FBDEV_O24_CMN_InitOSDLayer(LX_FBDEV_ID_OSD1);
    FBDEV_O24_CMN_InitOSDLayer(LX_FBDEV_ID_OSD3);

    // refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT
    if (hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)
    {
        FBDEV_O24_CMN_SafeSyncEnable();
    }
}

int FBDEV_O24_CMN_ExecHWCommand(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data)
{
    int ret = RET_NOT_SUPPORTED;
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    switch (cmd)
    {
        case FBDEV_HW_CMD_IO_POST_HW_INIT:
        {
            fbdev_o24_wq = alloc_workqueue("fbdev_o24_events", 0, 0);

            if (osd_enable_logo_clear)
            {
                FBDEV_NOTI("start logo clear work after %dms\n", osd_boot_logo_clear_timeout);
                queue_delayed_work(fbdev_o24_wq, &boot_logo_clear_work, msecs_to_jiffies(osd_boot_logo_clear_timeout));
            }

#ifdef BUILD_FEATURE_pioneer
#ifdef INCLUDE_KDRV_OVI
            // tcon_mute off
            // see http://clm.lge.com/issue/browse/SICDTV-12974
            FBDEV_NOTI("tcon_mute off (pioneer only)\n");
            OVI_HAL_SetDispOutMute(0);
#endif
#endif
        }
        break;

        case FBDEV_HW_CMD_IO_POSD_OPEN:
        {
            int fbdev_id = data->gen[0];
            struct fb_info* fbinfo = (struct fb_info*)data->genex[0];

            FBDEV_HW_DEBUG("fb(%d) POSD_OPEN..\n", fbdev_id);
            FBDEV_O24_CMN_RunBootLogoTimer(osd_boot_freeze_timeout, FALSE);

            FBDEV_O24_CMN_SetupExternalRenderer(fbdev_id, fbinfo);

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
            FBDEV_O24_CMN_ISRHook();
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_RD_VSYNC_CLK:
        {
            /* raxis.lim (2019/11/21)
             *
             * I should check if S.OSD is active becuase S.OSD is set to fixed 60Hz display
             * regardless of OVI check value.
             * remember that I can call FBDEV_O24_CMN_DetectVSyncClk() only when B.OSD is active.
             */
            if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
            {
                data->gen[0] = FBDEV_O24_CMN_DetectVSyncClk();
            }
            else /* S.OSD */
            {
                data->gen[0] = FBDEV_VSYNC_CLK_60HZ;
            }

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
                data->gen[1] = (fbdev_afbc_estreamer) ? 2/*afbc*/ : 1 /*argb*/;
                data->gen[2] = (hw_ctx->b_support_ext_render) ? 1 : 2; /* single buffer when ext_render_mode */
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
            data->gen[0] = osd_fbc_version;
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_FREEZE:
        {
            /* raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL. ORBIT control will be re-enabled at THAW & RESTORE */
            hw_ctx->hw_wa_flag &= ~FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_SUSPEND:
        {
            osd_hw_pm_suspend_stage = 1;

            if (osd_use_shutdown_path_on_suspend)
            {
                FBDEV_O24_CMN_ShutdownOSDPath();
            }

            // raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL to re-enable at FBDEV_O24_CMN_EnableOSDHdrFlush() during RESUME
            hw_ctx->hw_wa_flag &= ~FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_THAW:
        {
            // raxis.lim (2017/09/18) -- enable PQEFW_OSD0_OUT_CTRL here becuase THAW stage doesn't configure any HW registers
            hw_ctx->hw_wa_flag |= FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;
            FBDEV_NOTI("OSD0_PQEFW_OSD0_OUT_CTRL enabled\n");
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_RESTORE:
        {
            osd_hw_pm_restore_stage = 1;

            // boot logo migration is also required during snapshot boot
            osd_logo_migration_required = TRUE;
            FBDEV_O24_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_KEEP);

            if (osd_enable_logo_clear)
            {
                FBDEV_NOTI("start logo clear work after %dms (resume mode)\n", osd_resume_logo_clear_timeout);
                queue_delayed_work(fbdev_o24_wq, &boot_logo_clear_work, msecs_to_jiffies(osd_resume_logo_clear_timeout));
            }

            // (2010/06/11) re-activate lazy-init at snapshot boot
            hw_ctx->user_initcall_ctrl.ready = FALSE;
            hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

            // (2024/05/13) see https://alm-lge.singlex.com/polarion/#/project/IDWebOSSWRelProjMgmt/workitem?id=IDWOSWBS-11241
            FBDEV_NOTI("osd.restore - invalidate mirror ctrl\n");
            hw_ctx->mirror_ctrl.status = FBDEV_O24_MIRROR_NONE;

            // (2023/09/8) fast interrupt enable to prevent drm vsync timeout
            FBDEV_NOTI("osd.restore - fast enable OSD vsync\n");
            FBDEV_SetInterruptEnable(MIXER_INTR, 1);

            // raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute
            // it will be enabled at FBDEV_O24_CMN_EnableOSDHdrFlush()

            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_RESUME:
        {
            // raxis.lim (2017/08/22) -- fix for async behavior of OSD0_SYNC group
            hw_ctx->hw_wa_flag |= FBDEV_O24_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
            FBDEV_WARN("OSD0_SYNC_ASYNC_WR enabled\n");

            // (2010/06/11) re-activate lazy-init at QSM+ resume
            hw_ctx->user_initcall_ctrl.ready = FALSE;
            hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

            // raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute.
            // it will be enabled at FBDEV_O24_CMN_EnableOSDHdrFlush()
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_COMPLETE:
        {
            osd_hw_pm_suspend_stage = 0;
            osd_hw_pm_restore_stage = 0;

            hw_ctx->hw_wa_flag &= ~FBDEV_O24_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
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
            //
            // (2023/05/19) OSD open 이란 동작이 없어도, 이미지 업데이트가 가능하다.
            // 따라서 FBDEV_O24_CMN_RunBootLogoTimer() 함수를 호출하여 osd_hdr_update 플래그를
            // 정상화할 수 있도록 보강이 필요하다.
            //
            if (!hw_ctx->user_initcall_ctrl.ready)
            {
                hw_ctx->user_initcall_ctrl.ready = TRUE;

                FBDEV_O24_CMN_RunBootLogoTimer(osd_boot_freeze_timeout, FALSE);

                FBDEV_O24_CMN_ReInitHW();
            }
        }
        break;

        // USER_INITCALL_COMPLETE 는 모든 OSD 설정의 완료를 의미하므로, 반드시 PQE FW 쪽으로 제어권을 넘겨야 한다.
        // 즉 FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL 플래그 설정이 가장 중요
        case FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE:
        {
            int i;
            int fbdev_id = data->gen[0];

            FBDEV_NOTI("fb(%d) INITCALL_COMPLETE\n", fbdev_id);

            // (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume
            if (fbdev_id == LX_FBDEV_ID_OSD0)
            {
                UINT64 base_tick;
                FBDEV_O24_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

                // disable OSD reigster control by PQE_FW when S.OSD path is selected or FHD model
                if (hw_ctx->b_support_ext_frc || hw_ctx->hw_disp_width <= 2048)
                {
                    osd_pqefw_osd0_out_ctrl = 0;
                    hw_ctx->hw_wa_flag &= ~FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;
                    FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL disabled\n");
                }
                else
                {
                    hw_ctx->hw_wa_flag |= FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;
                    FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
                }

                hw_ctx->user_initcall_ctrl.status.osd_init_done = 1;
                hw_ctx->user_initcall_ctrl.status.osd_v_mirror = (mirror_ctrl->status == FBDEV_O24_V_MIRROR_ON) ? 1 : 0;
                hw_ctx->user_initcall_ctrl.status.osd_estreamer = 0;

                FBDEV_O24_CMN_NotifyPQEDriver();

                base_tick = OS_GetMsecTicks();

                for (i = 0; i < 10; i++)
                {
                    // if (FW done) break;
                    FBDEV_CHECK_NOTI((int)(OS_GetMsecTicks() - base_tick) > 100 /*100ms*/,
                                     break, "+ wait timeout\n");

                    if (RET_OK == FBDEV_O24_CMN_CheckPQEDriverInitialization()) break;

                    msleep_interruptible(10);
                }

                FBDEV_O24_CMN_SetOSDEnable(fbdev_id, TRUE);

                // destroy temporary boot logo framebuffer
                if (fbdev_bootlogo_fbmem_addr)
                {
                    hma_free("debug0", fbdev_bootlogo_fbmem_addr);
                    fbdev_bootlogo_fbmem_addr = 0x0;
                }

#ifdef INCLUDE_KDRV_OVI
                // tcon_mute off
                // see http://clm.lge.com/issue/browse/SICDTV-12974
                FBDEV_NOTI("tcon_mute off\n");
                OVI_HAL_SetDispOutMute(0);
#endif
            }
        }
        break;

        case FBDEV_HW_CMD_RD_EXTERNAL_RENDERER_INFO:
        {
            data->gen[0] = LX_FBDEV_ID_OSD1;
        }
        break;

        case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_CONFIGURE_CROP_REGION:
        {
            int max_cw;
            int max_ch;

            int  fbdev_id = data->gen[0];
            int cx = LX_RES_GET_WIDTH(data->gen[1]);
            int cy = LX_RES_GET_HEIGHT(data->gen[1]);
            int cw = LX_RES_GET_WIDTH(data->gen[2]);
            int ch = LX_RES_GET_HEIGHT(data->gen[2]);

            FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

            FBDEV_CHECK_CODE(fbdev_id != LX_FBDEV_ID_OSD1, break, "++ fb(%d) invalid ext_render fbdev\n", fbdev_id);

            if (hw_ctx->b_support_ext_render)
            {
                max_cw = hw_ctx->hw_ext_render_width / 2; /* 960 */
                max_ch = hw_ctx->hw_ext_render_height * 2; /* 4320 */
            }
            else
            {
                max_cw = hw_ctx->hw_fb1_width;
                max_ch = hw_ctx->hw_fb1_height;
            }

            if (cw > max_cw) cw = max_cw;

            if (ch > max_ch) ch = max_ch;

            ext_render_ctrl->hwparam.crop_x = cx;
            ext_render_ctrl->hwparam.crop_y = cy;
            ext_render_ctrl->hwparam.crop_w = cw;
            ext_render_ctrl->hwparam.crop_h = ch;

            FBDEV_NOTI("++ configure external render crop %d,%d,%d,%d\n", cx, cy, cw, ch);
        }
        break;

        // (2021/07/08) O248K, E608K 의 경우는 fbdev_drv.c 에서 호출이 되었으나, O24 8K 의 경우는
        // 일반 OSD 처럼 입력되어 처리되어야 하므로, fbdev_drv.c 에서 호출되지 않는다.
        // SW 구조를 유지하기 위하여 fbdev_hw_o24_cmn.c 에서 호출하도록 조치한다.
        // 수정된 IPC 에서는 crop_x,y,w,h 정보와 xoffset, enable 정보만 전달된다.
        case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE:
        {
            int    fbdev_id = data->gen[0];
            UINT32 phys_y   = data->gen[1];
            int    xoffset  = data->gen[2];
            int    yoffset  = data->gen[3];

            FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

            FBDEV_CHECK_CODE(fbdev_id != LX_FBDEV_ID_OSD1, break, "++ fb(%d) invalid ext_render fbdev\n", fbdev_id);

            ext_render_ctrl->hwparam.phys_y = phys_y;
            ext_render_ctrl->hwparam.size = ((hw_ctx->hw_ext_render_width / 2) << 16) | (hw_ctx->hw_ext_render_height * 2);
            ext_render_ctrl->hwparam.xoffset = xoffset;
            ext_render_ctrl->hwparam.yoffset = yoffset;

            // fake vsync 는 현재 체제 그대로 사용한다.
            {
                UINT64 sleep_tick_us = 0;
                UINT64 curr_tick_us = OS_GetUsecTicks();
                UINT64 diff_tick_us = curr_tick_us - ext_render_ctrl->swsync.request_tick_us;

                if (diff_tick_us < ext_render_ctrl->swsync.interval_tick_us)
                {
                    sleep_tick_us = ext_render_ctrl->swsync.interval_tick_us - diff_tick_us;
                    //FBDEV_NOTI("++ usleep %d us\n", (int)sleep_tick_us);
                    usleep_range(sleep_tick_us, sleep_tick_us);
                }

                FBDEV_HW_NOTI("++ write external render phy:s0x%08x cmd:0x%08x crop:%d,%d,%d,%d xy:%d,%d en:%d - sleep: %dus tx_count: %d\n",
                              ext_render_ctrl->hwparam.phys_y,
                              ext_render_ctrl->hwparam.command,
                              ext_render_ctrl->hwparam.crop_x,
                              ext_render_ctrl->hwparam.crop_y,
                              ext_render_ctrl->hwparam.crop_w,
                              ext_render_ctrl->hwparam.crop_h,
                              ext_render_ctrl->hwparam.xoffset,
                              ext_render_ctrl->hwparam.yoffset,
                              ext_render_ctrl->hwparam.enable,
                              (int)sleep_tick_us,
                              ext_render_ctrl->hwparam.tx_count);
            }

#ifdef FBDEV_O24_USE_EXT_RENDERER_IPC

            if (hw_ctx->b_support_ext_render)
            {
                if (FBDEV_OS0_EXT_RENDER_REG_BASE)
                {
                    FBDEV_HW_NOTI("++ write external render 0x%08x=0x%08x, 0x%08x=0x%08x, 0x%08x=0x%08x\n",
                                  FBDEV_OS0_EXT_RENDER_REG_BASE + 0x0, ext_render_ctrl->hwparam.command,
                                  FBDEV_OS0_EXT_RENDER_REG_BASE + 0x4, ext_render_ctrl->hwparam.crop_xy,
                                  FBDEV_OS0_EXT_RENDER_REG_BASE + 0x8, ext_render_ctrl->hwparam.crop_wh);

                    OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE + 0x4, ext_render_ctrl->hwparam.crop_xy);
                    OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE + 0x8, ext_render_ctrl->hwparam.crop_wh);
                    OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE + 0x0, ext_render_ctrl->hwparam.command);
                }
            }

#endif
            else
            {
                LX_RECT_T crop_rgn;

                crop_rgn.x = ext_render_ctrl->hwparam.crop_x;
                crop_rgn.y = ext_render_ctrl->hwparam.crop_y;
                crop_rgn.w = ext_render_ctrl->hwparam.crop_w;
                crop_rgn.h = ext_render_ctrl->hwparam.crop_h;

                // 여러 프로세스가 혼재되어 동작하게 되므로, osd0 의 소유권을 반드시 확인할것
                FBDEV_CHECK_CODE(hw_ctx->hw_osd0_owner != fbdev_id, break,
                                 "++ fb(%d) ignore. not hw_osd0_owner\n", fbdev_id);

                FBDEV_O24_CMN_SetOutputCropRegion(TRUE, hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height, xoffset, yoffset, &crop_rgn);
            }

            ext_render_ctrl->swsync.request_tick_us = OS_GetUsecTicks();
        }
        break;

        // PQE PM framework callback
        case FBDEV_HW_CMD_WR_PQE_PM_RUNTIME_ACTION:
        {
#ifdef INCLUDE_KDRV_PQE_PM
            int pqe_pm_action = data->gen[0];

            if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_PREPARE)
            {
                // (2023/11/06) suspend 에 준하는 동작 필요 (불필요한 PQE IPC 무시 등)
                // see FBDEV_O24_CMN_WaitPQEDriverEstreamerSync()
                osd_hw_pm_suspend_stage = 1;

                FBDEV_PM_DEBUG("hide all OSD layer for safe operation\n");
                FBDEV_O24_CMN_ShutdownOSDPath();

                FBDEV_O24_CMN_SetInterruptEnable(MIXER_INTR, FALSE);

                // PQE 에서 1/64 freq down 정책으로 사용하기 때문에, pic_init 에 대한 제어를 하지 않아도 됨
                // 추후 필요하다 판단시 아래 코드를 사용할것
                // 참고 http://clm.lge.com/issue/browse/SICDTV-10087?focusedCommentId=3185554&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3185554
                // 필요시 이전 패치셋을 확인할것

                // TODO: 필요시 추가할것

            }
            else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND)
            {
                // TODO: 필요시 추가할것

                // (2023/11/06) PQE FW 가 suspend 되었으므로, PQE 와의 IPC 동작을 할 수 없음을 표시한다.
                // see FBDEV_O24_CMN_WaitPQEDriverEstreamerSync()
                osd_pqefw_ipc_enabled = FALSE;
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_COMPLETED)
            {
                // TODO: 필요시 추가할것
                osd_hw_pm_suspend_stage = 0;
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
                // TODO: 필요시 추가할것

                // (2023/11/06) PQE FW 가 resume 되었으므로, PQE 와의 IPC 동작을 할 수 있다.
                osd_pqefw_ipc_enabled = TRUE;

                FBDEV_O24_CMN_SetInterruptEnable(MIXER_INTR, TRUE);
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
int FBDEV_O24_CMN_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable)
{
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    switch (intr)
    {
        default:
        case MIXER_INTR:
        {
            int curr_status;

            OSD_CTRL_RdFL(osd_common_ctrl_irq);

            if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
            {
                OSD_CTRL_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bosd, curr_status);

                if (curr_status != enable)
                {
                    FBDEV_NOTI("INTR <%s> for B.OSD\n", enable ? "ON" : "OFF");
                    OSD_CTRL_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bosd, enable);
                    OSD_CTRL_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sosd, 0x0);
                }
            }
            else
            {
                OSD_CTRL_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sosd, curr_status);

                if (curr_status != enable)
                {
                    FBDEV_NOTI("INTR <%s> for S.OSD\n", enable ? "ON" : "OFF");
                    OSD_CTRL_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bosd, 0x0);
                    OSD_CTRL_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sosd, enable);
                }
            }

            OSD_CTRL_WrFL(osd_common_ctrl_irq);
        }
        break;
    }

    return RET_OK;
}

// get interrupt status
int FBDEV_O24_CMN_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
    UINT32 intr_status = 0;
    UINT32 intr_clear;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    OSD_CTRL_RdFL(osd_common_ctrl_irq);

    if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
    {
        OSD_CTRL_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, intr_clear);
    }
    else
    {
        OSD_CTRL_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, intr_clear);
    }

    if (intr_clear)  intr_status |= (1 << MIXER_INTR);
    else             printk("OSD ISR - BOSD MIXER INTR error\n");

    FBDEV_ISR_DEBUG("intr_status = 0x%08x\n", intr_status);

    return intr_status;
}

// clear interrupt status
int FBDEV_O24_CMN_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
    OSD_CTRL_RdFL(osd_common_ctrl_irq);

    // clear both bosd and sosd intrrupt for the safe operation
    OSD_CTRL_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, 0x1);
    OSD_CTRL_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, 0x1);

    OSD_CTRL_WrFL(osd_common_ctrl_irq);

    return RET_OK;
}

/*========================================================================================
    Implementation Group (OSD Hdr Processing)
========================================================================================*/
static void FBDEV_O24_CMN_SetupExternalRenderer(int fb_dev_id, struct fb_info* fbinfo)
{
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

    if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_render)
    {
        ext_render_ctrl->swsync.interval_tick_us = 1000000 / hw_ctx->hw_ext_render_swsync_hz;

        ext_render_ctrl->hwparam.crop_x = 0;
        ext_render_ctrl->hwparam.crop_y = 0;
        ext_render_ctrl->hwparam.crop_w = hw_ctx->hw_ext_render_width / 2; /* 960 = 1920/2 */
        ext_render_ctrl->hwparam.crop_h = hw_ctx->hw_ext_render_height * 2; /* 4320 = 1080/2 */

        FBDEV_NOTI("++ fb(%d) setup external fbmem=0x%08x,0x%08x sz=%dx%d swsync=%dus\n", fb_dev_id,
                   ext_render_ctrl->fbmem_phys[0], ext_render_ctrl->fbmem_phys[1],
                   hw_ctx->hw_ext_render_width, hw_ctx->hw_ext_render_height,
                   (int)ext_render_ctrl->swsync.interval_tick_us);

        // O20, E60 의 경우 post processing 을 위한 정보를 넘겨야 했으나,
        // O24 에서는 OSD kdriver 에서 진행한다.
        // 따라서 GPU 쪽으로 넘겨야 할 정보가 없으므로, fbinfo->var.reserved 는 조작하지 않는다.
    }
}

static void FBDEV_O24_CMN_AllocExternalRendererFrameBuffer(void)
{
    int fbmem_sz;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

    if (!hw_ctx->b_support_ext_render)
    {
        return;
    }

    if (0x0 != ext_render_ctrl->fbmem_phys[0] && 0x0 != ext_render_ctrl->fbmem_phys[1])
    {
        return;
    }

    // (2021/09/29)
    // E-streamer 의 리포맷팅용 버퍼는 원본(fb1)의 형식을 모두 담을 수 있도록 한다.
    // 즉 최대 크기인 afbc image 에 맞춘다.
    //
    // 참고로 현재 기준 1024x4320 AFBC 포맷 기준
    // 17971200바이트 (헤더276480 포함) 만큼의 버퍼를 할당한다.
    //
    fbmem_sz = afbc_sw_get_image_size(NULL, hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height);

    FBDEV_NOTI("++ alloc ext_render surface. size=%d\n", fbmem_sz);

    if (0x0 == ext_render_ctrl->fbmem_phys[0])
    {
        // FIXME: 리포맷팅용 surface 를 debug1 에서 할당했었다.
        ext_render_ctrl->fbmem_phys[0] = (UINT32)hma_alloc("debug0", fbmem_sz, PAGE_SIZE);

        if (0x0 == ext_render_ctrl->fbmem_phys[0])
        {
            FBDEV_ERROR("can't alloc external render fbmem[0]\n");
            return;
        }
    }

    if (0x0 == ext_render_ctrl->fbmem_phys[1])
    {
        ext_render_ctrl->fbmem_phys[1] = (UINT32)hma_alloc("debug0", fbmem_sz, PAGE_SIZE);

        if (0x0 == ext_render_ctrl->fbmem_phys[1])
        {
            FBDEV_ERROR("can't alloc external render fbmem[1]\n");
            return;
        }
    }

    FBDEV_NOTI("++ alloc ext_render_fbmem 0x%08x 0x%08x\n",
               ext_render_ctrl->fbmem_phys[0], ext_render_ctrl->fbmem_phys[1]);

    ext_render_ctrl->fbmem_buf_idx = 0;
}

static void FBDEV_O24_CMN_DestroyExternalRendererFrameBuffer(void)
{
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

    if (!hw_ctx->b_support_ext_render)
    {
        return;
    }

    FBDEV_NOTI("++ freeing ext_render_fbmem 0x%08x 0x%08x\n",
               ext_render_ctrl->fbmem_phys[0], ext_render_ctrl->fbmem_phys[1]);

    if (ext_render_ctrl->fbmem_phys[0])
    {
        hma_free("debug0", ext_render_ctrl->fbmem_phys[0]);
        ext_render_ctrl->fbmem_phys[0] = 0x0;
    }

    if (ext_render_ctrl->fbmem_phys[1])
    {
        hma_free("debug0", ext_render_ctrl->fbmem_phys[1]);
        ext_render_ctrl->fbmem_phys[1] = 0x0;
    }
}

// O24 OSD 에서 제공하는 output crop 기능을 E-Streamer 에서 사용하도록 한다.
// 통상적인 잘라내기 기능 외에 출력 지점도 지정할 수 있다.
// 4K E-streamer 에서 사용된다.
// (노트) M23 에서 구현된 것을 O24 에서 차용하여 구현한다.
static void FBDEV_O24_CMN_SetOutputCropRegion(BOOLEAN crop_en, int img_width, int img_height, int xoffset,
        int yoffset, LX_RECT_T* crop_rgn)
{
    int i;
    int xidx;
    int xnum, xlst[2];
    int fb_dev_id = LX_FBDEV_ID_OSD1;

    FBDEV_CHECK_ERROR(!crop_rgn, return, "null param\n");

    xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);
    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_HW_NOTI("fb(%d) crop=%s image=%dx%d, x=%d, y=%d, crop_rgn=%d,%d,%d,%d\n",
                  fb_dev_id,
                  crop_en ? "on" : "off",
                  img_width, img_height,
                  xoffset, yoffset, crop_rgn->x, crop_rgn->y, crop_rgn->w, crop_rgn->h);

    for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
    {
        xidx = xlst[i];

        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_0);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_1);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_2);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_3);

        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_crop_en, crop_en);

        if (fb_dev_id == LX_FBDEV_ID_OSD1)
        {
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_in_pic_width, img_width);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_in_pic_height, img_height);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_1, hoffset, crop_rgn->x);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_1, hactive, crop_rgn->w);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_2, voffset, crop_rgn->y);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_2, vactive, crop_rgn->h);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_3, crop_mixer_xpos, xoffset);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_3, crop_mixer_ypos, yoffset);
        }

        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_post_crop_ctrl_0);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_post_crop_ctrl_1);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_post_crop_ctrl_2);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_post_crop_ctrl_3);
    }
}

// 960x4320 (fb1 size) 으로 들어온 ARGB 데이터를 1920x2160 으로 리포매팅해야 한다.
//
// fb1 의 크기는 960x4320 혹은 960x4320 으로 들어올 것이다.
// 상하 기준으로 1/2 구분하여 top 960x2160 과 bottom 960x2160 을 1920x2160 의 Left, Right 가 넣어야 한다.
//
// 이미지 포맷이 ARGB8888 즉 32bit 를 가정한다.
// 실제 surface 의 크기와 리포맷팅하는 위치가 src, dst 각각 따로여서 코드가 깔끔하지 않다.
// 최대한 코멘트로 size 값을 기록하여 오류가 없도록 한다.

// (2091/09/29) http://clm.lge.com/issue/browse/SICDTV-10314
//
// 정책을 수정하다.
// CC00/1 의 BW 를 줄이기 위하여 ARGB -> AFBC 로 형식을 바꾼다.
// 960x4320 을 1920x2160 으로 만들기 위하여 header 섹션의 위치를 조작한다.
//

// AFBC 버전의 reformatter
// (2021/10/01) BW 절감을 위하여 향후 AFBC reformatter 만 사용할것
//
static void FBDEV_O24_CMN_ReformatAFBCExternalRenderer(struct scanvas* canvas, FBDEV_O24_OSD_HDR_T* osd_hdr)
{
    int fbmem_buf_idx;
    UINT32 fbmem_phys;

    int fb_size;

    struct afbc_ctx ctx;
    struct afbc_framebuffer* src_fb = NULL;
    struct afbc_framebuffer* dst_fb = NULL;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

    ctx = afbc_sw_init_context((osd_fbc_version == FBDEV_HW_AFBC_VER_AFRC) ? AFBC_SW_VER_AFRC :
                               (osd_fbc_version == FBDEV_HW_AFBC_VER_1_1) ?  AFBC_SW_VER_1_1 : FBDEV_HW_AFBC_VER_1_0);

    fb_size = afbc_sw_get_header_size(&ctx, canvas->input_win.w, canvas->input_win.h)
              + afbc_sw_get_payload_size(&ctx, canvas->input_win.w, canvas->input_win.h);

    fbmem_buf_idx = (ext_render_ctrl->fbmem_buf_idx + 1) % 2;
    fbmem_phys = ext_render_ctrl->fbmem_phys[fbmem_buf_idx];

    src_fb = afbc_sw_alloc_framebuffer(&ctx,
                                       canvas->osd_bm_paddr,
                                       canvas->input_win.w,
                                       canvas->input_win.h,
                                       0,
                                       0,
                                       fb_size);

    dst_fb = afbc_sw_alloc_framebuffer(&ctx,
                                       fbmem_phys,
                                       hw_ctx->hw_ext_render_width,
                                       hw_ctx->hw_ext_render_height,
                                       0,
                                       0,
                                       fb_size);

    FBDEV_CHECK_ERROR(!src_fb || !dst_fb, goto func_exit,
                      "src_fb=%p, dst_fb=%p alloc error\n", src_fb, dst_fb);

    afbc_sw_transform(&ctx, src_fb, dst_fb, AFBC_TRANSFORM_TB_TO_SS);

func_exit:

    if (src_fb)
    {
        afbc_sw_free_framebuffer(&ctx, src_fb);
    }

    if (dst_fb)
    {
        afbc_sw_free_framebuffer(&ctx, dst_fb);
    }

    ext_render_ctrl->fbmem_buf_idx = fbmem_buf_idx;
}

// ARGB 버전의 reformatter
// (2021/10/01) 검증 목적 이외에는 사용하지 말것
//
static void FBDEV_O24_CMN_ReformatARGBExternalRenderer(struct scanvas* canvas, FBDEV_O24_OSD_HDR_T* osd_hdr)
{
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

    int fbmem_buf_idx = (ext_render_ctrl->fbmem_buf_idx + 1) % 2;
    UINT32 fbmem_phys = ext_render_ctrl->fbmem_phys[fbmem_buf_idx];

#define get_stride(w) ((w)*FBDEV_O24_EXT_RENDER_BYTE_PER_PIXEL)

    // cached 연산으로 작업 코드 넣어 놓자
    // src = canvas.input_w = 1024, canvas.input_h = 4320
    // dst = hw_ctx->ext_render_width = 1920, hw_ctx->ext_render_height = 2160;
    // src 와 dst 가 같다는 가정을 하지 말것
    {
        struct fbmem_surf
        {
            int     w;
            int     h;
            int     stride;
            int     size;
            UINT32  phys;
        };

        int i;
        UINT8* src_img;
        UINT8* dst_img;
        int src_w, src_h, src_x;
        int dst_w, dst_h;

        UINT64 tk[2];

        struct fbmem_surf src_surf;
        struct fbmem_surf dst_surf;
        OS_CACHE_MAP_T src_cmap;
        OS_CACHE_MAP_T dst_cmap;

        src_surf.w = canvas->input_win.w; /* 1024 */
        src_surf.h = canvas->input_win.h; /* 4320 */
        src_surf.stride = get_stride(canvas->input_win.w);
        src_surf.size = src_surf.stride * src_surf.h;
        src_surf.phys = canvas->osd_bm_paddr;

        dst_surf.w = hw_ctx->hw_ext_render_width; /* 1920 */
        dst_surf.h = hw_ctx->hw_ext_render_height;/* 2160 */
        dst_surf.stride = get_stride(hw_ctx->hw_ext_render_width);
        dst_surf.size = dst_surf.stride * dst_surf.h;
        dst_surf.phys = fbmem_phys;

        src_w = src_surf.w;     /* 1024 */
        src_h = src_surf.h / 2; /* 2160 */
        src_x = 0;              /* offset */

        dst_w = dst_surf.w / 2; /* 960 */
        dst_h = dst_surf.h;     /* 2160 */

        // src_surf 의 width 가 dst_surf 보다 크기 때문에, 가운데 영역만 잘라서 복사할 수 있도록 한다.
        // src_surf 의 height 가 더 크다면, 표시 가능한 부분만 복사할 수 있도록 한다.
        if (src_w > dst_w)
        {
            src_x = (src_w - dst_w) / 2;
            src_w = dst_w;
        }

        if (src_h > dst_h)
        {
            src_h = dst_h;
        }

        tk[0] = OS_GetUsecTicks();

        OS_OpenCacheMap(&src_cmap, src_surf.phys, src_surf.size);
        OS_OpenCacheMap(&dst_cmap, dst_surf.phys, dst_surf.size);

        OS_InvalCacheMap(&src_cmap, 0x0, src_surf.size);

        // top 1024x2160 을 dst_fbmem 의 left 960x2160 로 복사한다
        src_img = src_cmap.virt_addr + get_stride(src_x);
        dst_img = dst_cmap.virt_addr;

        for (i = src_h; i > 0; i--)
        {
            memcpy(dst_img, src_img, get_stride(src_w));
            dst_img += dst_surf.stride;
            src_img += src_surf.stride;
        }

        // bottom 1024x2160 을 dst_fbmem 의 right 960x2160 로 복사한다
        // src_img 는 앞선 top 에 이어서 연속으로 계속 사용한다.
        dst_img = dst_cmap.virt_addr;
        dst_img += get_stride(dst_w);

        for (i = src_h; i > 0; i--)
        {
            memcpy(dst_img, src_img, get_stride(src_w));
            dst_img += dst_surf.stride;
            src_img += src_surf.stride;
        }

        OS_CleanCacheMap(&dst_cmap, 0x0, dst_surf.size);

        OS_CloseCacheMap(&src_cmap);
        OS_CloseCacheMap(&dst_cmap);

        tk[1] = OS_GetUsecTicks();

        FBDEV_HW_NOTI("reformat idx=%d, 0x%08x (%dx%d) -> 0x%08x (%dx%d), tick=%dus\n",
                      fbmem_buf_idx, src_surf.phys, src_surf.w, src_surf.h, dst_surf.phys, dst_surf.w, dst_surf.h,
                      (int)(tk[1] - tk[0]));
    }

    ext_render_ctrl->fbmem_buf_idx = fbmem_buf_idx;
}

/** detect current mirror mode configuration set by boot loader
 *
 */
static void FBDEV_O24_CMN_InitMirrorEnv(void)
{
    int xidx;
    int xnum, xlst[2];
    int fb_dev_id = LX_FBDEV_ID_OSD0;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

    xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

    xidx = xlst[0];
    FBDEV_CHECK_CODE(INVALID_XIDX(xidx), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xidx);

    /* raxis.lim (2018/07/02) -- read mirror mode configuration set from boot loader */
    if (mirror_ctrl->status == FBDEV_O24_MIRROR_NONE)
    {
        UINT32 hw_val;

#ifdef V_MIRROR_TEST
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, 0x1);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
#endif
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, hw_val);

        mirror_ctrl->status = (hw_val) ? FBDEV_O24_V_MIRROR_ON : 0x0;

        FBDEV_WARN("OSD v_mirror detected (%d)\n", hw_val);
    }
}

static void FBDEV_O24_CMN_SetupSRScaler(BOOLEAN onoff, BOOLEAN bForce)
{
    int i;
    int xidx;
    int xnum, xlst[2];
    UINT32 hw_onoff;
    int fb_dev_id = LX_FBDEV_ID_OSD0;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_SR_CTRL_T* sr_ctrl = FBDEV_O24_GET_SR_CTRL(hw_ctx, fb_dev_id);

    PARAM_UNUSED(bForce);

    xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

    // bitmap_ctrl0.reg_osd_shp_detour_en 제어에 의하여 OSD SHP 블럭을 지나갈지 말지 결정이 되므로,
    // OSD_SHP 블럭은 항상 동작 준비를 하도록 초기화를 진행한다.
    // see SICDTV-9405
    OSD_SHP_CTRL_RdFL(shp_core_ctrl_00);
    OSD_SHP_CTRL_Wr01(shp_core_ctrl_00, reg_top_bypass, 0x0);
    OSD_SHP_CTRL_WrFL(shp_core_ctrl_00);

    for (i = 0; i < xnum; i++)
    {
        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

        // raxis.lim (2019/05/21) -- osd_bitmap_ctrl is valid only for primary posd layer
        if (i != 0x0)
        {
            continue;
        }

        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
        OSDX_CTRL_RdFL(hdr_ui, osd_hdrui_yc2rgb_ctrl00);

        // check HW status for debug. hw_onoff is not used yet
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, hw_onoff);
        hw_onoff ^= 1;
        FBDEV_NOTI("OSD_SR(HW) = %d(%s)\n", hw_onoff, (hw_onoff) ? "on" : "off");

        sr_ctrl->status   = (onoff) ? FBDEV_O24_SR_STATUS_ON : FBDEV_O24_SR_STATUS_OFF;

#ifdef FBDEV_O24_USE_SR_CTRL
        // configure OSD SR
        //
        // OSD0_BITMAP_CTRL0.reg_rgb2yc_csc_en_de_clk
        // OSD0_BITMAP_CTRL0.reg_yc2rgb_csc_en
        // OSD0_BITMAP_CTRL0.reg_rgb2yc_csc_p_en_oclk
        // OSD_HDRUI_YC2RGB_CTRL00.reg_yuv2rgb_en
        //
        // see http://clm.lge.com/issue/browse/SICDTV-9405
        // ?focusedCommentId=3012650&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3012650
        //
        //
        // (2021/09/15)
        // see http://clm.lge.com/issue/browse/SICDTV-10278
        // enable O24 random dither to improve OSD quality when gradation appears
        // OSD0_BITMAP_CTRL0 -> reg_rgb2yc_csc_en_de_clk [31:31] = 0
        // OSD0_BITMAP_CTRL0 -> reg_yc2rgb_csc_en [22:22] = 0
        //
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en_de_clk, 0x0);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_csc_en, 0x0);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_p_en_oclk, (onoff) ? 0x1 : 0x0);
        OSDX_CTRL_Wr01(hdr_ui, osd_hdrui_yc2rgb_ctrl00, reg_yuv2rgb_en, (onoff) ? 0x1 : 0x0);

        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, (onoff) ? 0x0 : 0x1);


        FBDEV_NOTI("OSD_SR %d(%s)\n", onoff, (onoff) ? "on" : "off");
#else
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en_de_clk, 0x0);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_csc_en, 0x0);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_p_en_oclk, 0x0);
        OSDX_CTRL_Wr01(hdr_ui, osd_hdrui_yc2rgb_ctrl00, reg_yuv2rgb_en, 0x0);

        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, 0x1);

        FBDEV_NOTI("OSD_SR disabled (%s)\n", "off");
#endif

        // (2023/10/10) SW WA 효과 없어 삭제함. 대신 SICDTV-13236 정책 사용함.
        // see http://clm.lge.com/issue/browse/SCDCR-6506
        // see http://clm.lge.com/issue/browse/SICDTV-13236
#if 0
        FBDEV_NOTI("fixme fixme\n");
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_pre_mul_alpha_detour_en, 0x1);
#endif

        // see http://clm.lge.com/issue/browse/SCDCRIDPQE-51
        // see http://clm.lge.com/issue/browse/SCDCR-6971
        if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND && FBDEV_VSYNC_CLK_60HZ == FBDEV_O24_CMN_DetectVSyncClk())
        {
            FBDEV_NOTI("4K60 case. osd_bitmap_ctrl0.reg_pre_mul_alpha_detour_en=1\n");
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_pre_mul_alpha_detour_en, 0x1);
        }

        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
        OSDX_CTRL_WrFL(hdr_ui, osd_hdrui_yc2rgb_ctrl00);
    }

    // if user ti_gain is defined, initialize HW configuration using the last user ti_gain.
    // otherwise, initialize ti_gain based on HW default value.
    //
    sr_ctrl->ti_gain = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_SR_GAIN, 0x0);

    FBDEV_HW_DEBUG("fb(0) OSD_SR.sr_gain=0x%08x\n", sr_ctrl->ti_gain);
}

// initialize CROP to the default state.
//
//
static void FBDEV_O24_CMN_InitCropEnv(void)
{
    /* do nothing */
}

// initialize FBC variable to the default state.
// The real HW register will be set inside FBDEV_O24_CMN_WriteOSDHeader()
// This function is also called during instant boot resume to setup AFBC register again.
//
static void FBDEV_O24_CMN_InitFBCEnv(void)
{
    int i;

    /* raxis.lim (2010/10/15) -- setup afbc for both fb(0) and fb(1)
     */
    for (i = 0; i <= LX_FBDEV_ID_OSD1; i++)
    {
        FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
        FBDEV_O24_FBC_CTRL_T* fbc_ctrl = FBDEV_O24_GET_FBC_CTRL(hw_ctx, i);
        int hw_afbc_status = 0;
        int hw_afrc_status = 0;

        fbc_ctrl->fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW;
        fbc_ctrl->status  = FBDEV_O24_FBC_STATUS_NONE;
        FBDEV_O24_FBC_DEBUG("fb(%d) initialize fbc env\n", i);

        // raxis.lim (2016/10/05) -- try to initialize OSD to AFBC graphic path if possible
        // boot loader can display both non-AFBC and AFBC logo image, so I should keep the current
        // graphic configuration.
        // below codes will be active if cold boot or snapshot boot (not instant boot)
        //
        hw_afbc_status = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFBC, i);
        hw_afrc_status = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFRC, i);

        FBDEV_NOTI("fb(%d) initial FBC mode: afbc=%d, afrc=%d\n", i, hw_afbc_status, hw_afrc_status);

        // recover FBC if AFBC display is used at boot loader
        if (hw_afrc_status)
        {
            FBDEV_O24_CMN_SetupFBC(i, LX_FBDEV_FBC_FORMAT_AFRC);
        }
        else if (hw_afbc_status)
        {
            FBDEV_O24_CMN_SetupFBC(i, LX_FBDEV_FBC_FORMAT_AFBC);
        }
    }
}

// create or destory FBC envrionment
//
// AFBC, AFRC 를 모두 셋업할 수 있어야 한다.
//
static void FBDEV_O24_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt)
{
    int i;
    int xidx;
    int xnum, xlst[2], afbc_xlst[2];

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_FBC_CTRL_T* fbc_ctrl = FBDEV_O24_GET_FBC_CTRL(hw_ctx, fb_dev_id);

    FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_HW_NOTI("fb(%d) fbc_ctrl->fbm_fmt=0x%x(%s), new fbc_fmt=0x%x(%s)\n",
                  fb_dev_id,
                  fbc_ctrl->fbc_fmt, fbdev_util_get_fbc_string(fbc_ctrl->fbc_fmt),
                  fbc_fmt, fbdev_util_get_fbc_string(fbc_fmt));

    // check HW status
    if (fbc_ctrl->fbc_fmt == fbc_fmt)
    {
        int hw_fbc_fmt = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_FBC, fb_dev_id);

        FBDEV_CHECK_CODE(fbc_ctrl->fbc_fmt != hw_fbc_fmt, goto afbc_config,
                         "<!> fb(%d) sw/hw status mismatch (hw:%d, sw:%d)\n", fb_dev_id, hw_fbc_fmt, fbc_ctrl->fbc_fmt);

        return; /* same value. do nothing */
    }

afbc_config:
    xnum = FBDEV_O24_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_NOTI("fb(%d) setup fbc_path=%x(%s)\n", fb_dev_id, fbc_fmt, fbdev_util_get_fbc_string(fbc_fmt));

    OSD_TOP_CTRL_RdFL(ctrl_block);
    OSD_TOP_CTRL_RdFL(ctrl_dpath);
    OSD_TOP_CTRL_RdFL(ctrl_auto_init_afbc);

    if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC || fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC)
    {
        UINT32 afbc_auto_init_src_val = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? 0x0 : 0x1;
#ifdef FBDEV_O24_USE_AFBC_READ_BW_SAVING
        UINT32 enable = FBDEV_O24_CMN_GetOSDEnable(fb_dev_id);
#else
        UINT32 enable = 1;
#endif

        UINT32 afbc_afrc_sel = (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC) ? 1 : 0;


        if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
        {
            OSD_TOP_CTRL_Wr01(ctrl_dpath, osd0_afbc_en, 0x1);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,        enable);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en,   enable);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, idx_afbc0_pic_init_src,   0x0); /* g0_pic_init. 이건 고정 ? */

            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_src,  afbc_auto_init_src_val);

            FBDEV_O24_FBC_DEBUG("fb(%d) %s enabled. xlst=%d,%d view=%d\n",
                                fb_dev_id, fbdev_util_get_fbc_string(fbc_fmt), afbc_xlst[0], afbc_xlst[1], enable);
        }

        if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
        {
            OSD_TOP_CTRL_Wr01(ctrl_dpath, osd1_afbc_en, 0x1);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en,        enable);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en,   enable);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, idx_afbc1_pic_init_src,   0x1); /* g1_pic_init. 이거 선택 가능 ? */

            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_src,  afbc_auto_init_src_val);

            FBDEV_O24_FBC_DEBUG("fb(%d) %s enabled. xlst=%d,%d view=%d\n",
                                fb_dev_id, fbdev_util_get_fbc_string(fbc_fmt), afbc_xlst[0], afbc_xlst[1], enable);
        }

        FBDEV_O24_FBC_DEBUG("top_ctrl.ctrl_block fbc_mode=0x%x (%s)\n",
                            afbc_afrc_sel, (afbc_afrc_sel == 0) ? "AFBC" : "AFRC");

        OSD_TOP_CTRL_Wr01(ctrl_block, reg_afbc_afrc_sel, afbc_afrc_sel);
    }
    else
    {
        if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
        {
            OSD_TOP_CTRL_Wr01(ctrl_dpath, osd0_afbc_en, 0x0);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,        0x0);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en,   0x0);

            FBDEV_O24_FBC_DEBUG("fb(%d) fbc disabled. xlst=%d,%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1]);
        }

        if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
        {
            OSD_TOP_CTRL_Wr01(ctrl_dpath, osd1_afbc_en, 0x0);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en,        0x0);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en,   0x0);

            FBDEV_O24_FBC_DEBUG("fb(%d) fbc disabled. xlst=%d,%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1]);
        }
    }

    // setup OSD registers
    for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
    {
        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xidx), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xidx);

        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);

        if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC || fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC)
        {
            /* enable BITMAP mode */
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_bitmap_only_mode_en, 0x1);

            fbc_ctrl->status |=  FBDEV_O24_FBC_STATUS_PATH_CHANGE;;
        }
        else
        {
            /* disable BITMAP mode (default in raw mode) */
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main,  osd_bitmap_only_mode_en, 0x0);

            fbc_ctrl->status &= ~FBDEV_O24_FBC_STATUS_HDR_SETUP;
            fbc_ctrl->status |=  FBDEV_O24_FBC_STATUS_PATH_CHANGE;
        }

        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
    }

    FBDEV_O24_FBC_DEBUG("top_ctrl.ctrl_block flush...0x%08x\n", OSD_TOP_CTRL_Rd(ctrl_block));

    // flush top registers
    OSD_TOP_CTRL_WrFL(ctrl_block);
    OSD_TOP_CTRL_WrFL(ctrl_dpath);
    OSD_TOP_CTRL_WrFL(ctrl_auto_init_afbc);

    // raxis.lim (2019/05/21) -- I will always configure AFBC/AFRC to use ready_flag
    OSD_AFBC_CTRL_RdFL(0, ctrl_afbc_0);
    OSD_AFBC_CTRL_RdFL(1, ctrl_afbc_0);

    OSD_AFBC_CTRL_Wr01(0, ctrl_afbc_0, update_ready_flag_en, 0x1);
    OSD_AFBC_CTRL_Wr01(1, ctrl_afbc_0, update_ready_flag_en, 0x1);

    OSD_AFBC_CTRL_WrFL(0, ctrl_afbc_0);
    OSD_AFBC_CTRL_WrFL(1, ctrl_afbc_0);

    OSD_AFRC_CTRL_RdFL(0, ctrl_afrc_0);
    OSD_AFRC_CTRL_RdFL(1, ctrl_afrc_0);

    OSD_AFRC_CTRL_Wr01(0, ctrl_afrc_0, update_ready_flag_en, 0x1);
    OSD_AFRC_CTRL_Wr01(1, ctrl_afrc_0, update_ready_flag_en, 0x1);

    OSD_AFRC_CTRL_WrFL(0, ctrl_afrc_0);
    OSD_AFRC_CTRL_WrFL(1, ctrl_afrc_0);

    FBDEV_O24_FBC_DEBUG("fb(%d) fbc_mode=0x%x(%s) setup completed\n",
                        fb_dev_id, fbc_fmt, fbdev_util_get_fbc_string(fbc_fmt));

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
static void FBDEV_O24_CMN_WriteAFBCHdrRegs(int fb_dev_id,
        FBDEV_O24_OSD_HDR_T osd_hdr[2], FBDEV_O24_OSD_EXHDR_T* osd_exhdr)
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

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];
    FBDEV_O24_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

    FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);
    FBDEV_CHECK_DEBUG(fbc_ctrl->fbc_fmt != LX_FBDEV_FBC_FORMAT_AFBC, return, "fb(%d) non-afbc image\n", fb_dev_id);

    xnum = FBDEV_O24_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);

    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d. fb(%d)\n", fb_dev_id, xnum, fb_dev_id);

    afbc_mode = (osd_fbc_version == FBDEV_HW_AFBC_VER_1_1) ? 0x0 : 0x1;

    img_y = osd_hdr[0].osd_hdr_ypos;
    img_w = osd_hdr[0].osd_hdr_w_mem;
    img_h = osd_hdr[0].osd_hdr_h_mem;
    img_addr = osd_hdr[0].osd_hdr_ptr_bmp;
    img_stride = osd_exhdr->img_stride;
    img_bpp = FBDEV_O24_BITS_2_BYTES(osd_exhdr->bits_per_pixel);

    for (i = 0; i < xnum; i++)
    {
        UINT32 line_wait_cnt;
        UINT32 img_width;
        UINT32 new_img_width;

        afbc_xidx = afbc_xlst[i];

        // current fb_dev_id is not attached to afbc
        if (INVALID_FBC_XIDX(afbc_xidx)) continue;

        img_x = osd_hdr[i].osd_hdr_xpos;

        FBDEV_O24_FBC_DEBUG("fb(%d) afbc.xidx(%d) paddr=0x%08x pos=%d,%d dim=%dx%d, stride=%d\n",
                            fb_dev_id, afbc_xidx, img_addr,
                            img_x, img_y, img_w, img_h, img_stride);

        // once the whole AFBC registers are set, I will just update the minimal registers
        OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_1);
        OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_2);
        OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_3);
        OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_8);

        OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_1, hd_base,      img_addr);
        OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_8, pl_data_base, img_addr);

        // AFBC data size description
        OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_x,     img_x);
        OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_y,     img_y);
        OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_x,       LX_CALC_ALIGNED_VALUE(img_x + img_w - 2, 1));
        OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_y,       img_y + img_h - 1);

        OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_1);
        OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_2);
        OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_3);
        OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_8);

        // see http://clm.lge.com/issue/browse/SICDTV-13236
        // afbc img_width 의 변경 발생시 로그와 함께 설정을 진행할것
        new_img_width = img_stride / img_bpp;

        OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_4);
        OSD_AFBC_CTRL_Rd01(afbc_xidx, ctrl_afbc_4, img_width,  img_width);
        OSD_AFBC_CTRL_Rd01(afbc_xidx, ctrl_afbc_4, line_wait_cnt, line_wait_cnt);

        if (img_width != new_img_width)
        {
            FBDEV_NOTI("afbc%d.img_width changed from %d to %d, line_wait_cnt=0x%03x\n", afbc_xidx, img_width, new_img_width,
                       line_wait_cnt);

            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_4, img_width,  new_img_width);
            OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_4);
        }

        // AFRC general setup only
        // below configurations will be called when the first AFBC image is feeded
        if (!(fbc_ctrl->status & FBDEV_O24_FBC_STATUS_HDR_SETUP))
        {
            // see http://clm.lge.com/issue/browse/SICDTV-12366 김민c 가이드
            int pl_gmau_id = 7;
            int hd_gmau_txid = 6;

            OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_0);
            OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_5);
            OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_9);
            OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_c);
            OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_10);

            // HW guy said that I should set the same value to AFBC hdr & data :(
            // I think it's enough to change only below two value (hd_base, pl_data_base)
            //
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_9, pl_data_end,  0xffffffff);

            // raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
            // HW guy fixed dec_buf_depth value to 959 and pl_buf_depth value to 255.
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_5, dec_buf_depth_m1, 959);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_5, pl_buf_depth_m1,  255);

            // raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
            // HW test value : 0x0000_FF76
            //
            FBDEV_FIXME("레지스터 메뉴얼 기준 endian_arb 값은 1 이어야 할듯함")
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_endian_arb, 1);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_endian_arb, 1);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_endian_sw,  0xf);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_endian_sw,  0xf);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_gmau_id,    pl_gmau_id);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_gmau_txid,  hd_gmau_txid);

            // raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
            //
            // 0xff80_80ff @RGBA
            // 0xffff_8080 @ARGB (*)
            //
            // I've used 0xffff_fffff since O24 AFBC integration
            // 동작에 영향이 없는 값인듯함. 메뉴얼 기준 default 값은 0x0 임
#if 0
            OSD_AFBC_CTRL_Wr(afbc_xidx, ctrl_afbc_10, 0xffff8080);  /* +0xD0 : 0xffff8080 for argb case */
#else
            OSD_AFBC_CTRL_Wr(afbc_xidx, ctrl_afbc_10, 0xFFFFFFFF);  /* +0xD0 : 0xffffffff for argb case */
#endif
            // (2020/04/29) see http://clm.lge.com/issue/browse/SICDTV-9405
            //
            // ctrl_afbc_0.run_mode = 0x1 if AFBC 1.0
            //                      = 0x0 if AFBC 1.1
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, start,        0);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, ready,        0);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset,     0);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset_fifo, 0);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, run_mode,     afbc_mode);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, pl_addr_mode, 1);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset_ack, 0);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, gmau_arb_sw_reset, 0);

            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, flip_mode, (mirror_ctrl->status & FBDEV_O24_V_MIRROR_ON) ? 1 : 0);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, ignore_q_full, 0);
            OSD_AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, wrap_en,      1);

            // flush data
            OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_5);
            OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_9);
            OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_c);
            OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_10);
            OSD_AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_0);
        }
    }

    fbc_ctrl->status |= FBDEV_O24_FBC_STATUS_HDR_SETUP;
}


static void FBDEV_O24_CMN_WriteAFRCHdrRegs(int fb_dev_id,
        FBDEV_O24_OSD_HDR_T osd_hdr[2], FBDEV_O24_OSD_EXHDR_T* osd_exhdr)
{
    UINT32 img_addr;
    int img_x;
    int img_y;
    int img_w;
    int img_h;
    int img_bpp;
    int img_stride;

    int i;
    int afrc_xidx;
    int xnum, xlst[2], afrc_xlst[2];

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];
    FBDEV_O24_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

    FBDEV_CHECK_CODE(!CHECK_AFRC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);
    FBDEV_CHECK_DEBUG(fbc_ctrl->fbc_fmt != LX_FBDEV_FBC_FORMAT_AFRC, return, "fb(%d) non-afrc image\n", fb_dev_id);

    xnum = FBDEV_O24_CMN_GetHWXListEx(fb_dev_id, xlst, afrc_xlst);

    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d. fb(%d)\n", fb_dev_id, xnum, fb_dev_id);

    img_y = osd_hdr[0].osd_hdr_ypos;
    img_w = osd_hdr[0].osd_hdr_w_mem;
    img_h = osd_hdr[0].osd_hdr_h_mem;
    img_addr = osd_hdr[0].osd_hdr_ptr_bmp;
    img_stride = osd_exhdr->img_stride;
    img_bpp = FBDEV_O24_BITS_2_BYTES(osd_exhdr->bits_per_pixel);

    for (i = 0; i < xnum; i++)
    {
        afrc_xidx = afrc_xlst[i];

        // current fb_dev_id is not attached to afrc
        if (INVALID_FBC_XIDX(afrc_xidx)) continue;

        img_x = osd_hdr[i].osd_hdr_xpos;

        FBDEV_O24_FBC_DEBUG("fb(%d) afrc.xidx(%d) paddr=0x%08x pos=%d,%d dim=%dx%d, stride=%d\n",
                            fb_dev_id, afrc_xidx, img_addr,
                            img_x, img_y, img_w, img_h, img_stride);

        // once the whole AFRC registers are set, I will just update the minimal registers
        if (fbc_ctrl->status & FBDEV_O24_FBC_STATUS_HDR_SETUP)
        {
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_4);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_5);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_6);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_7);

            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_4, pl_data_base, img_addr);

            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_5, start_x,     img_x);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_5, start_y,     img_y);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_6, end_x,       ALIGN(img_x + img_w, 2) - 1);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_6, end_y,       img_y + img_h - 1);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_7, img_width,   img_stride / img_bpp);

            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_4);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_5);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_6);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_7);
        }
        // below configurations will be called when the first AFRC image is feeded
        else
        {
            // see http://clm.lge.com/issue/browse/SICDTV-12366 김민c 가이드
#if 0
            int pl_gmau_txid = (afrc_xidx == 0) ? 7 : 7;
#else
            int pl_gmau_txid = 7;
#endif
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_0);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_2);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_4);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_5);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_6);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_7);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_c);
            OSD_AFRC_CTRL_RdFL(afrc_xidx, ctrl_afrc_14);

            // AFRC control block description
            FBDEV_FIXME("아래 항목 동적으로 설정가능하게 코드 준비할것")
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_2, comp_size, 32);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_2, bit_depth, 8);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_2, col_format, 1);

            // HW guy said that I should set the same value to AFRC hdr & data :(
            // I think it's enough to change only below two value (hd_base, pl_data_base)
            //
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_4, pl_data_base, img_addr);

            // AFRC data size description
            // end_x:
            //  "horizontal end pixel position in full frame.
            //  decoding end horizontal pixel position of the ROI in the frame.
            //  - argb : 4 pixel unit (4 픽셀 배수)
            //  - y : 16 pixel unit
            //  - uv : 8 pixel unit
            //
            // (ex) ARGB 4K case: left.end_x = 1919, right.end_x = 3939
            //
            // end_y:
            // "vertical end pixel position in full frame.
            // decoding end vertical pixel position of the ROI in the frame.
            //
            // (ex) ARGB 4K case: end_y = 2159
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_5, start_x,     img_x);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_5, start_y,     img_y);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_6, end_x,       ALIGN(img_x + img_w, 2) - 1);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_6, end_y,       img_y + img_h - 1);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_7, img_width,   img_stride / img_bpp);

            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_14, pl_data_end,  0xffffffff);

            // use HW guide value.
            // pl_endian_arb = 1, pl_endian_sw = 0, pl_gmau_txid = 7
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_c, pl_endian_arb, 1);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_c, pl_endian_sw,  0);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_c, pl_gmau_txid,  pl_gmau_txid);

            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_0, start,        0);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_0, ready,        0);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_0, sw_reset,     0);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_0, sw_reset_fifo, 0);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_0, sw_reset_ack, 0);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_0, gmau_arb_sw_reset, 0);
            OSD_AFRC_CTRL_Wr01(afrc_xidx, ctrl_afrc_0, flip_mode, (mirror_ctrl->status & FBDEV_O24_V_MIRROR_ON) ? 1 : 0);

            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_2);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_4);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_5);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_6);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_7);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_c);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_14);
            OSD_AFRC_CTRL_WrFL(afrc_xidx, ctrl_afrc_0);
        }
    }

    fbc_ctrl->status |= FBDEV_O24_FBC_STATUS_HDR_SETUP;
}

// flush AFRC/AFBC header in register space and make HW to fetch registers from the next OSD frame
//
static void FBDEV_O24_CMN_FlushFBCHdrRegs(int fb_dev_id)
{
    int i;
    int fbc_xidx;
    int xnum, xlst[2], fbc_xlst[2];

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];

    FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_HW_NOTI("fb(%d) fbc_fmt=%s\n", fb_dev_id, fbdev_util_get_fbc_string(fbc_ctrl->fbc_fmt));

    xnum = FBDEV_O24_CMN_GetHWXListEx(fb_dev_id, xlst, fbc_xlst);
    FBDEV_O24_FBC_DEBUG("fb(%d) xnum=%d, fbc_xlst=(%d,%d)\n", fb_dev_id, xnum, fbc_xlst[0], fbc_xlst[1]);

    // current fb_dev_id is not attached to fbc
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d\n", fb_dev_id, xnum);

    if (fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC)
    {
        for (i = 0; i < xnum ; i++)
        {
            fbc_xidx = fbc_xlst[i];

            if (INVALID_FBC_XIDX(fbc_xidx)) continue;

            OSD_AFRC_CTRL_Wr01(fbc_xidx, ctrl_afrc_0, update_ready_flag, 0x1);
            OSD_AFRC_CTRL_WrFL(fbc_xidx, ctrl_afrc_0);

            FBDEV_O24_FBC_DEBUG("fb(%d) fbc_xidx(%d) flush AFRC regs\n", fb_dev_id, fbc_xidx);
        }
    }
    else if (fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
    {
        for (i = 0; i < xnum; i++)
        {
            fbc_xidx = fbc_xlst[i];

            if (INVALID_FBC_XIDX(fbc_xidx)) continue;

            OSD_AFBC_CTRL_Wr01(fbc_xidx, ctrl_afbc_0, update_ready_flag, 0x1);
            OSD_AFBC_CTRL_WrFL(fbc_xidx, ctrl_afbc_0);

            FBDEV_O24_FBC_DEBUG("fb(%d) fbc_xidx(%d) flush AFBC regs\n", fb_dev_id, fbc_xidx);
        }
    }
}

// write OSD HW register
//
// 2K OSD, 4K OSD 여부에 따라 POSD 갯수를 판단하다.
// 필요시 전달된 OSD 정보값을 조작할 수도 있다.
//
//
void    FBDEV_O24_CMN_WriteHdrRegs(int fb_dev_id, FBDEV_O24_OSD_HDR_T* osd_hdr, FBDEV_O24_OSD_EXHDR_T* osd_exhdr)
{
    int i;
    int xidx;
    int xnum, xlst[2];

    FBDEV_O24_OSD_HDR_T osd_hw_hdr[2];  // 4K OSD 출력을 위하여 최대 2개 layer 필요
    UINT32* hdr_regs;

    ULONG flags;
    struct scanvas* hCanvas = NULL;
    FBDEV_WIN_CTX_T* wctx = NULL;
    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    hCanvas = FBDEV_GetWinCanvas(fb_dev_id);
    FBDEV_CHECK_CODE(NULL == hCanvas, return, "invalid canvas. fb(%d)\n", fb_dev_id);

    wctx = FBDEV_GetWinCtx(fb_dev_id);
    FBDEV_CHECK_CODE(NULL == wctx, return, "invalid winctx. fb(%d)\n", fb_dev_id);

    xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);

    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "invalid xnum %d. fb(%d)\n", xnum, fb_dev_id);

    spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

    // notify osd freeze for debug
    if (!wctx->status.b_osd_hdr_flush)
    {
        UINT32 disp_fbmem;

        for (i = 0; i < xnum; i++)
        {
            xidx = xlst[i];

            if (INVALID_XIDX(xidx)) continue;

            OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);
            disp_fbmem = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);

            FBDEV_WARN("fb(%d) xidx(%d) freezed. osd_hdr_flush deferred. keep 0x%08x\n", fb_dev_id, xidx, disp_fbmem);
        }

        goto func_exit;
    }

    for (i = 0; i < xnum; i++)
    {
        xidx = xlst[i];

        if (INVALID_XIDX(xidx)) continue;

        // 통으로 전달된 osd_hdr 를 기반으로 최대 2개의 HW osd_hdr를 생성한다.
        memcpy(&osd_hw_hdr[i], osd_hdr, sizeof(FBDEV_O24_OSD_HDR_T));

        // xnum = 2 (4K OSD 처리)
        //
        // fb(0) 은 3840x2160 통으로 이미지가 전달되어, 4K OSD 출력 기능을 사용하여 처리되어야 한다.
        // fb(1) 은 1920x2160 으로 리포맷팅된 이미지가, L/R 동일하게 복사되어 출력된다. (F22 인터페이스)
        //
        // 이를 정리하면 4K 통이미지로 전달되는 경우, L/R 를 분리하여 각각의 osd_hw_hdr 를 만든다.
        // 그 외의 경우는 이미 앞에서 조작된 header 정보를 그대로 이용한다.
        //
        // (노트) 4K 통이미지로 구성된 AFBC 이미지에 대한 데이터 해석은 FBDEV_O24_CMN_WriteFBCHdrRegs 참조할것
        //        여기서는 L/R 에 대한 오프셋/크기 정보만을 처리한다.
        // (노트) 4K UI OSD 에 대한 input/output scaler 설정은 REG_4K_OSD_MAIN_CTRL_2, REG_4K_OSD_MAIN_CTRL_3 을
        //        통해 설정된다.
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0 && xnum == 2)
        {
            osd_hw_hdr[i].osd_hdr_ptr_bmp += (osd_exhdr->img_stride / 2) * i;

            osd_hw_hdr[i].osd_hdr_w_mem /= 2;
            osd_hw_hdr[i].osd_hdr_w_out /= 2;

            osd_hw_hdr[i].osd_hdr_xpos = (osd_hw_hdr[i].osd_hdr_w_mem) * i;
            osd_hw_hdr[i].osd_hdr_ypos = 0;
        }

        FBDEV_O24_HDR_DEBUG("fb(%d) xidx(%d), osd_hw_hdr in=%dx%d out=%dx%d\n",
                            fb_dev_id, xidx,
                            osd_hw_hdr[i].osd_hdr_w_mem,
                            osd_hw_hdr[i].osd_hdr_h_mem,
                            osd_hw_hdr[i].osd_hdr_w_out,
                            osd_hw_hdr[i].osd_hdr_h_out);

        hdr_regs = (UINT32*)&osd_hw_hdr[i];

        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_ctrl_hdr0, hdr_regs[0]);
        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_ctrl_hdr1, hdr_regs[1]);
        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_ctrl_hdr2, hdr_regs[2]);
        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_ctrl_hdr3, hdr_regs[3]);
        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_ctrl_hdr4, hdr_regs[4]);
        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_ctrl_hdr5, hdr_regs[5]);
        OSDX_CTRL_Wr(osdx_ctrl[xidx], osd_ctrl_hdr6, hdr_regs[6]);

        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr1);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr3);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr4);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr5);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr6);

        // (2017/09/15)
        // raxis.lim (2017/09/15) -- DO NOT write OSD out_win only
        // when OSD0_PQEFW_OSD0_OUT_CTRL is enabled
        //
        // raxis.lim (2019/06/19)
        // support orbit control (http://clm.lge.com/issue/browse/SDOSTB-246)
        // (note) 4KOSD 테스트 모드에서는 orbit 활성화시 OSD 출력 정상아님. orbit 제어하는 FW 에서 추가 제어 필요할 듯 예상됨
        //
        // raxis.lim (2019/07/29)
        // EXT_FRC 가 붙었을 경우에는 orbit control 을 O24 에서 하지 않는다.
        // 향후에는 flag 를 좀 더 조정하자.
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            if (osd_pqefw_osd0_out_ctrl && (hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL))
            {
                /* do nothing */
            }
            else
            {
                UINT32 w, h;
                OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_w_out, w);
                OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_h_out, h);
                FBDEV_HW_DEBUG("fb(%d) xidx(%d) flush OSD_CTRL_HDR2. %dx%d\n", fb_dev_id, xidx, w, h);
                OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
            }
        }
        else
        {
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
        }

    }

    // flush post header (AFBC,OSD_SHP etc )
    {
        /* flush AFBC register */
        if (fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1)
        {
            FBDEV_HW_NOTI("fb(%d) check AFBC\n", fb_dev_id);
            FBDEV_O24_CMN_SetupFBC(fb_dev_id, hCanvas->fbc_fmt);

            if (hCanvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC)
            {
                FBDEV_O24_CMN_WriteAFRCHdrRegs(fb_dev_id, osd_hw_hdr, osd_exhdr);
                FBDEV_O24_CMN_FlushFBCHdrRegs(fb_dev_id);
            }
            else if (hCanvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
            {
                FBDEV_O24_CMN_WriteAFBCHdrRegs(fb_dev_id, osd_hw_hdr, osd_exhdr);
                FBDEV_O24_CMN_FlushFBCHdrRegs(fb_dev_id);
            }
        }

        // raxis.lim (2018/04/09) -- sync between OSD_SHP (OSD_SR) and OSD out info
        // O18/M16P3 doesn't have any limitation regarding OSD_SR size.
        // but core_ctrl_01's width, height should have the same value with output_win to prevent image corruption.
        // refer to SICDTV-4853
        //
        // raxis.lim (2019/07/29) -- SHP control should be disabled at EXT_FRC mode.
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0 && !hw_ctx->b_support_ext_frc) // && xnum==1)
        {
            UINT32  osd_shp_width, osd_shp_height;

            OSD_SHP_CTRL_RdFL(shp_core_ctrl_01);
            OSD_SHP_CTRL_Rd01(shp_core_ctrl_01, reg_top_width, osd_shp_width);
            OSD_SHP_CTRL_Rd01(shp_core_ctrl_01, reg_top_height, osd_shp_height);

            if (osd_shp_width != osd_hdr->osd_hdr_w_out || osd_shp_height != osd_hdr->osd_hdr_h_out)
            {
                // raxis.lim (2018/11/01) -- DO NOT write OSD_SHP
                // when OSD0_PQEFW_OSD0_OUT_CTRL is enabled and TEMP_PAUSE is not enabled
                if (osd_pqefw_osd0_out_ctrl &&
                        (hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL))
                {
                    /* do nothing */
                }
                else
                {
                    FBDEV_WARN("osd_shp's size changed (%d,%d) -> (%d,%d)\n",
                               osd_shp_width, osd_shp_height, osd_hdr->osd_hdr_w_out, osd_hdr->osd_hdr_h_out);

                    OSD_SHP_CTRL_Wr01(shp_core_ctrl_01, reg_top_width, osd_hdr->osd_hdr_w_out);
                    OSD_SHP_CTRL_Wr01(shp_core_ctrl_01, reg_top_height, osd_hdr->osd_hdr_h_out);
                    OSD_SHP_CTRL_WrFL(shp_core_ctrl_01);
                }
            }
        }

        // notify OSD HW to read osd header
        for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
        {
            xidx = xlst[i];

            OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_ready_flag, 0x1);
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_main);

            FBDEV_O24_HDR_DEBUG("fb(%d) xidx(%d) flush osd_hdr regs/data\n", fb_dev_id, xidx);
        }

#ifdef FBDEV_O24_SUPPORT_4KOSD_UPSCALER

        // raxis.lim (2019/05/22)
        //
        // if you want to support OSD smaller than 4K, reg_4k_osd_main_ctrl_2 register should be configured again
        // to reduce screen corruption, I added this right after updating osd_hdr_ready_flag
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0 && xnum == 2)
        {
            xidx = xlst[1];
            OSDX_CTRL_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_w, osd_hdr->osd_hdr_w_mem);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_h, osd_hdr->osd_hdr_h_mem);
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);

            FBDEV_HW_NOTI("4kosd upscaler %dx%d -> %dx%d\n",
                          osd_hdr->osd_hdr_w_mem, osd_hdr->osd_hdr_h_mem,
                          hw_ctx->hw_disp_width, hw_ctx->hw_disp_height);
        }

        // TODO: add something if you want more OSD configuration after writing OSD header
#endif
    }

func_exit:
    spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);
}

// OSD HW common header generator
//
// OSD HW header is made based on struct scanvas data and extra environment such as 3DOSD, reverse etc.
//
int FBDEV_O24_CMN_WriteOSDHeader(struct scanvas* pCanvas)
{
    int                     fb_dev_id;
    UINT32                  bitmap_ptr;
    FBDEV_O24_OSD_HDR_T     osd_hdr;
    FBDEV_O24_OSD_EXHDR_T   osd_exhdr;
    FBDEV_WIN_CTX_T*        wctx;
    struct scanvas          canvas;
    UINT32                  disp_width, disp_height;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK,
                     "<i> fb(%d) user_initcall not ready +++\n", pCanvas->fb_dev_id);

    wctx = FBDEV_GetWinCtx(pCanvas->fb_dev_id);
    FBDEV_CHECK_CODE(NULL == wctx, return RET_ERROR,
                     "fb(%d) invalid winctx.\n", pCanvas->fb_dev_id);

    // fb(1) 이 소유권을 가지고 있는 경우에만 제어를 허용한다.
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        FBDEV_CHECK_CODE(hw_ctx->hw_osd0_owner != fb_dev_id,
                         return RET_ERROR,
                         "++ fb(%d) ignore. not hw_osd0_owner\n", fb_dev_id);
    }

    /* clear osd_hdr before writing */
    memset(&osd_hdr, 0x0, sizeof(FBDEV_O24_OSD_HDR_T));
    memset(&osd_exhdr, 0x0, sizeof(FBDEV_O24_OSD_EXHDR_T));
    memcpy(&canvas, pCanvas, sizeof(struct scanvas));

    fb_dev_id = canvas.fb_dev_id;
    disp_width = hw_ctx->hw_disp_width;
    disp_height = hw_ctx->hw_disp_height;

    // raxis.lim (2016/08/08) - if OSD is freezed, DO NOT handle/write any registers
    //
    // This patch seems to prevent OSD garbage during transition from non AFBC (boot logo) to AFBC (mercury/webOS) screen.
    // Originally, osd_hdr_flush is checked at FBDEV_O24_CMN_WriteHdrRegs().
    // I don't know the below code really prevents OSD garbage rather than the original policy.
    // <!> More tests are required.
    //
    if (!wctx->status.b_osd_hdr_flush)
    {
        int xidx, xnum, xlst[2];
        UINT32 disp_fbmem = 0x0;

        xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);
        xidx = xlst[0];

        if (!INVALID_XNUM(xnum))
        {
            OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);
            disp_fbmem = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);
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

#ifdef FBDEV_O24_USE_UNLIMITED_CURSOR_POSITION
            int csr_h_min_pxl = FBDEV_O24_BYTES_2_PIXEL(FBDEV_O24_GMAU_WORD_BYTES); /* 16 bytes -> 4 pixel */
#endif
            FBDEV_O24_HDR_DEBUG("cursor_pos req(%d,%d)\n", canvas.output_win.x, canvas.output_win.y);

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
            csr_x_max = canvas.stride / FBDEV_O24_BITS_2_BYTES(canvas.bits_per_pixel);

            csr_x_off = 0;
            csr_y_off = 0;

            csr_x_pos = canvas.output_win.x - canvas.csr_hotspot.x;
            csr_y_pos = canvas.output_win.y - canvas.csr_hotspot.y;

            csr_x_size = canvas.input_win.w;
            csr_y_size = canvas.input_win.h;

            FBDEV_O24_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d info( %dx%d h %d,%d ) max_x %d disp_x %d\n", fb_dev_id,
                                csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
                                canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y,
                                csr_x_max, csr_disp_w);

#ifdef FBDEV_O24_USE_UNLIMITED_CURSOR_POSITION

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

                if (csr_y_size < FBDEV_O24_CSR_MIN_HEIGHT)
                {
                    csr_y_size = FBDEV_O24_CSR_MIN_HEIGHT;
                    csr_y_off  = csr_y_size - FBDEV_O24_CSR_MIN_HEIGHT;
                }
            }

            // prevent OSD garbage. effective cursor width should be less than the real surface width
            if (csr_x_size > csr_x_max) csr_x_size = csr_x_max;

            // if cursor is located at the right corner, I should gaurantee the minimal viewing area of cursor.
            // without it, cursor image will be broken :(
            // see the description for FBDEV_O24_CSR_MIN_WIDTH
            if (csr_x_pos + csr_x_size > csr_disp_w)
            {
                if (csr_x_pos > csr_disp_w - FBDEV_O24_CSR_MIN_WIDTH)
                {
                    csr_x_pos = csr_disp_w - FBDEV_O24_CSR_MIN_WIDTH;
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
                if (hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_1X_CSR_DISP_ON_BLEND_PATH)
                {
                    if (FBDEV_O24_CMN_IsUHDDispMode())
                    {
                        csr_x_size *= 2;

                        if (csr_x_size > csr_x_max) csr_x_size = csr_x_max;
                    }
                }
            }

            // if cursor is located at the bottom corner, I should gaurantee the minimum viewing area, i.e 2 pixel
            if (csr_y_pos > csr_disp_h - FBDEV_O24_CSR_MIN_HEIGHT)
            {
                csr_y_pos = csr_disp_h - FBDEV_O24_CSR_MIN_HEIGHT;
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
            bitmap_ptr += (csr_y_off * canvas.stride) + FBDEV_O24_GMAU_ALIGNED_BYTES(csr_x_off * FBDEV_O24_BITS_2_BYTES(
                              canvas.bits_per_pixel));

            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl         = FBDEV_O24_BYTES_2_OSD_WORDS(canvas.stride);

            FBDEV_O24_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d <- req( %dx%d h %d,%d)\n", fb_dev_id,
                                csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
                                canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y);
            FBDEV_O24_HDR_DEBUG("fb(%d) cursor pre-processing done\n", fb_dev_id);
        }
        break;

        // E-streamer 전용 가상 레이어
        //
        // 8K-Estreamer
        //  (1) 1024x4320 --> 960x2160 T/B 을 합성하여 1920x2160 생성함
        //  (2) 960x2160을 단순 복사하여 각각 L/R 이 되게하여 최종 3840x2160 4K OSD 만듦
        //  (3) 3840x2160 OSD 를 F22 OSD path 로 전송함
        //
        // (2021/10/01) http://clm.lge.com/issue/browse/SICDTV-10314
        // 과도한 OSD 의 DDR BW (2GB/s) 을 절감하고자 AFBC 포맷으로 변경함
        // 상세한 플로우는 SICDTV-10314 를 참조할것
        //
        //
        case LX_FBDEV_ID_OSD1:
        {
            FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);
            int fbmem_buf_idx ;
            UINT32 fbmem_phys;

            if (hw_ctx->b_support_ext_render)
            {
                // (2021/08/04) see http://clm.lge.com/issue/browse/SICDTV-10200
                // fbmem 이 존재하는 경우에만 리포맷팅 및 OSD 후속 처리를 진행한다.
                FBDEV_CHECK_ERROR(!ext_render_ctrl->fbmem_phys[0] || !ext_render_ctrl->fbmem_phys[1],
                                  goto func_exit,
                                  "ext_render fbmem is NULL. ignore render\n");

                // 1024x4320 (혹은 960x4320) 을 1920x2160 으로 리포맷팅 한다.
                if (pCanvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC || pCanvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC)
                {
                    FBDEV_O24_CMN_ReformatAFBCExternalRenderer(&canvas, &osd_hdr);
                }
                else
                {
                    FBDEV_O24_CMN_ReformatARGBExternalRenderer(&canvas, &osd_hdr);
                }

                fbmem_buf_idx = ext_render_ctrl->fbmem_buf_idx;
                fbmem_phys = ext_render_ctrl->fbmem_phys[fbmem_buf_idx];

                // AFBC 이던 ARGB 이던 리포맷팅된 1920x2160 이미지가 L(Left OSD)로 출력된다.
                // 3840 line width 를 만들기 위하여 R 은 L 이미지를 복사하여 출력되게 될 것이다.
                //
                canvas.input_win.w  = hw_ctx->hw_ext_render_width;  // 1920 = 960*2
                canvas.input_win.h  = hw_ctx->hw_ext_render_height; // 2160 = 4320/2
                canvas.output_win.w = hw_ctx->hw_ext_render_width;
                canvas.output_win.h = hw_ctx->hw_ext_render_height;
                canvas.stride       = FBDEV_O24_PIXEL_2_BYTES(hw_ctx->hw_ext_render_width); // stride(1920)
            }
            else
            {
                fbmem_phys = canvas.osd_bm_paddr;
            }

            // see http://jira.lge.com/issue/browse/SCDCR-7577
            if (hw_ctx->hw_fb1_width != canvas.input_win.w || hw_ctx->hw_fb1_height != canvas.input_win.h)
            {
                FBDEV_NOTI("fb(1) hw_fb1_width, hw_fb1_height changed %dx%d => %dx%d\n",
                           hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height,
                           canvas.input_win.w, canvas.input_win.h);

                hw_ctx->hw_fb1_width = canvas.input_win.w;
                hw_ctx->hw_fb1_height = canvas.input_win.h;
            }

            osd_hdr.osd_hdr_w_out = hw_ctx->hw_fb1_width;
            osd_hdr.osd_hdr_h_out = hw_ctx->hw_fb1_height;
            osd_hdr.osd_hdr_xpos = 0; //canvas.output_win.x;
            osd_hdr.osd_hdr_ypos = 0; //canvas.output_win.y;
            osd_hdr.osd_hdr_w_mem = canvas.input_win.w;
            osd_hdr.osd_hdr_h_mem = canvas.input_win.h;

            bitmap_ptr = fbmem_phys;
            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl = FBDEV_O24_BYTES_2_OSD_WORDS(canvas.stride);
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
                FBDEV_O24_HDR_DEBUG("++ user output used (%d,%d)\n", canvas.test_output_win.w, canvas.test_output_win.h);
                memcpy(&canvas.output_win, &canvas.test_output_win, sizeof(LX_RECT_T));
            }

            // raxis.lim (2015/01/12) -- handle odd width
            // OSD doesn't support odd number as output width. so let's make it to even number
            if (canvas.output_win.w & 0x1)
            {
                FBDEV_O24_HDR_DEBUG("fb(%d) convert odd out_w %d to %d\n", fb_dev_id, canvas.output_win.w,
                                    canvas.output_win.w & 0xfffffffe);
                canvas.output_win.w &= 0xfffffffe;
            }

            // NOTE - CLUT processing is not processed anymore inside kdriver
            osd_hdr.osd_hdr_color_key_en = canvas.color_key_en;

            osd_hdr.osd_hdr_w_out       = canvas.output_win.w;  /* output w */
            osd_hdr.osd_hdr_h_out       = canvas.output_win.h;  /* output h */
            osd_hdr.osd_hdr_xpos        = canvas.output_win.x;  /* output x */
            osd_hdr.osd_hdr_ypos        = canvas.output_win.y;  /* output y */
            osd_hdr.osd_hdr_w_mem       = canvas.input_win.w;   /* input w  */
            osd_hdr.osd_hdr_h_mem       = canvas.input_win.h;   /* input h  */
            bitmap_ptr                  = canvas.osd_bm_paddr;

            // modify bitmap ptr for input position is provided
            if (canvas.input_win.x > 0 || canvas.input_win.y > 0)
            {
                FBDEV_O24_HDR_DEBUG("fb(%d) bitmap based moved ! by %d,%d\n", fb_dev_id, canvas.input_win.x, canvas.input_win.y);

                // gMAU requests 16byte aligned address
                bitmap_ptr += canvas.input_win.y * canvas.stride;
                bitmap_ptr += FBDEV_O24_GMAU_ALIGNED_BYTES(FBDEV_O24_BITS_2_BYTES(canvas.input_win.x * canvas.bits_per_pixel));
            }

            FBDEV_O24_HDR_DEBUG("fb(%d) bitmap hwparam (%d,%d,%d,%d)(%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x, pixel_format=%d\n",
                                fb_dev_id,
                                canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
                                canvas.output_win.x, canvas.output_win.y, canvas.output_win.w, canvas.output_win.h,
                                canvas.stride, bitmap_ptr, canvas.fbc_fmt, canvas.pixel_format);

            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl         = FBDEV_O24_BYTES_2_OSD_WORDS(canvas.stride);

            if (canvas.pixel_format != LX_FBDEV_PIXEL_FORMAT_NOT_DEFINED &&
                    canvas.pixel_format != canvas.pixel_format_current)
            {
                int xnum, xlst[2];
                int i;

                xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);

                for (i = 0; i < xnum; i++)
                {
                    int xidx = xlst[i];

                    OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_pdec);

                    if (canvas.pixel_format == LX_FBDEV_PIXEL_FORMAT_RGB_8888)
                    {
                        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_alpha,           0x0);
                        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_red,             0x1);
                        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_green,           0x2);
                        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_blue,            0x3);
                    }
                    else if (canvas.pixel_format == LX_FBDEV_PIXEL_FORMAT_BGR_8888)
                    {
                        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_alpha,           0x0);
                        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_red,             0x3);
                        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_green,           0x2);
                        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,   osd_ch_blue,            0x1);
                    }

                    OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_pdec);
                }

                canvas.pixel_format_current = canvas.pixel_format;
            }
        }
        break;
    }

    // copy common attribute
    osd_hdr.osd_hdr_format          = FBDEV_GetOSDPxlFmt(canvas.bits_per_pixel);
    osd_hdr.osd_hdr_depth           = FBDEV_GetOSDPxlDepth(canvas.bits_per_pixel);

    osd_hdr.osd_hdr_global_alpha_en = canvas.global_alpha_en;
    osd_hdr.osd_hdr_global_alpha    = (canvas.global_alpha_en) ? canvas.global_alpha : 0xff;
    osd_hdr.osd_hdr_color_key       = canvas.color_key;

    osd_hdr.osd_hdr_ptr_bmp         = bitmap_ptr;
    osd_hdr.osd_hdr_ptr_plte        = wctx->osd_plte_base_phys;

    // NOTE - virtual OSD is not processed anymore inside kdriver

    // handle S3D if requested

    // TOOD: add extra handleer if necessary.

    FBDEV_O24_HDR_DEBUG("fb(%d) bitmap hwparam (%d,%d,%d,%d)(%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x (final)\n",
                        fb_dev_id,
                        canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
                        canvas.output_win.x, canvas.output_win.y, canvas.output_win.w, canvas.output_win.h,
                        canvas.stride, bitmap_ptr, canvas.fbc_fmt);

    // save osd header
    memcpy(&hw_ctx->osd_hdr_sav[fb_dev_id], &osd_hdr, sizeof(FBDEV_O24_OSD_HDR_T));

    // raxis.lim (2019/05/21)
    //
    // I don't care here whether two POSDs sare necessary or not. refer to FBDEV_O24_CMN_WriteHdrRegs()
    //
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

    FBDEV_O24_CMN_WriteHdrRegs(fb_dev_id, &osd_hdr, &osd_exhdr);

    // do somthing if necessary

    // (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume
    if (fb_dev_id == LX_FBDEV_ID_OSD0)
    {
        // F22 이 존재하는 경우에는 orbit 동작이 F22 에서 벌어지므로, OSD kdriver 는 항상 OSD HDR 설정토록 조치한다.
        if (hw_ctx->b_support_ext_frc)
        {
            if (hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL)
            {
                osd_pqefw_osd0_out_ctrl = 0;
                hw_ctx->hw_wa_flag &= ~FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;
                FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL disabled\n");
            }
        }
        else // INT_FRC or NO_FRC
        {
            if (!(hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL))
            {
                hw_ctx->hw_wa_flag |= FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;
                FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
            }
        }
    }

    // see http://clm.lge.com/issue/browse/AVTASK-640
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;

        hw_cmd.gen[0] = fb_dev_id;
        hw_cmd.gen[1] = osd_hdr.osd_hdr_ptr_bmp;
        hw_cmd.gen[2] = wctx->pixel.output_win.x;
        hw_cmd.gen[3] = wctx->pixel.output_win.y;

        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE, &hw_cmd);
    }

func_exit:
    return RET_OK;
}

/*========================================================================================
    Implementation Group
========================================================================================*/

// OSD HW Layer enable/disable
//
// @param   fb_dev_id [IN] fbdev ID
//
//          enable : 0 : display off , 1 : display on
// @return  int 0 : OK , -1 : NOT OK
//
//
int FBDEV_O24_CMN_SetOSDEnable(int fb_dev_id, int enable)
{
    int     i;
    int     xidx;
    int     xnum, xlst[2], afbc_xlst[2];
    int     hw_state;
    UINT32  val = 0x0;
    UINT32  hw_osd0_owner;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> user_initcall not ready +++\n");

    // fb(0) 와 fb(1) 간의 hw owner 가 변경시 FRC(F22) 에서 특수 처리가 들어거야 하므로,
    // 이에 준하여 같이 동작할 수 있도록 한다.
    // EST 의 on/off 에 대하여 IPC 전송후 16.7 ms 의 수신 보장을 해주어야 한다.
    // http://clm.lge.com/issue/browse/AVTASK-640?focusedCommentId=3226339&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3226339
    hw_osd0_owner = hw_ctx->hw_osd0_owner;

    xnum = FBDEV_O24_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

    val = (enable) ? 0x1 : 0x0;
    FBDEV_HW_DEBUG("fb(%d) xlst=(%d,%d) view = <%s>\n", fb_dev_id, xlst[0], xlst[1], (enable) ? "on" : "off");

    hw_state = FBDEV_O24_CMN_GetOSDEnable(fb_dev_id);
    FBDEV_NOTI("fb(%d) hw_state=%s, req=%s, action=%s\n", fb_dev_id,
               (hw_state) ? "on" : "off",
               (enable) ? "on" : "off",
               "continue");

    // 시스템 부팅 초기에는 HW on 상태일 수 있지만, 실제 OSD 셋업을 마무리 하기 위해서는 같은 상태라도
    // 이후 과정을 계속 진행하도록 하는것이 안전하다.
    // 참고로 O24 에서는 OSD off 상태로 시작하기 때문에 아래 체커 있는 것이 더 낫지만,
    // 기존 O22 과의 코드 싱크를 맞추기 위하여, O22 처럼 체커 삭제조치한다.
#if 0

    if (enable == hw_state)
    {
        return RET_OK;
    }

#endif

#if 0

    if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_render == FALSE)
    {
        FBDEV_NOTI("++ fb(%d) %s ignore. ext_render disabled\n", fb_dev_id, (enable) ? "on" : "off");
        return RET_OK;
    }

#endif

    // (2021/12/04) http://hlm.lge.com/qi/browse/QEVENTTWT-8589
    // LSM 에서 TV 시작시에  fb(0) 과 fb(1) 에 대한 XOR 동작성을 위배하고 있음
    // 드라이버에서는 fb(0) 에 우선 순위를 두고, fb(1) 에 대한 on/off 을 거부할 수 있음
    if (fb_dev_id == LX_FBDEV_ID_OSD1 && FBDEV_O24_CMN_GetOSDEnable(LX_FBDEV_ID_OSD0))
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
            FBDEV_O24_CMN_AllocExternalRendererFrameBuffer();

            // (2020/10/16) Estreamer 동작전에 cursor 를 강제로 off 시킴
            // see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
            if (FBDEV_O24_CMN_GetOSDEnable(LX_FBDEV_ID_CSR0))
            {
                int csr_xnum, csr_xlst[2], csr_afbc_xlst[2];

                csr_xnum = FBDEV_O24_CMN_GetHWXListEx(LX_FBDEV_ID_CSR0, csr_xlst, csr_afbc_xlst);

                if (csr_xnum > 0)
                {
                    int csr_xidx = csr_xlst[0];

                    OSDX_CTRL_RdFL(osdx_ctrl[csr_xidx], osd_ctrl_sync0);
                    OSDX_CTRL_Wr01(osdx_ctrl[csr_xidx], osd_ctrl_sync0, osd_sync_enable, 0x0);
                    OSDX_CTRL_WrFL(osdx_ctrl[csr_xidx], osd_ctrl_sync0);

                    FBDEV_NOTI("++ set cursor invisible (sync.en=0) when EXT_RENDER is shown\n");
                }
            }
        }

        // (2021/07/05)
        // fb(1) 은 실제 FB(0) 과 동일한 HW 를 사용하고 있어, 기존 E60 과 다른 플로우를 타야 한다.
        // fb(1) 에 대한 on/off 는 F22 에 즉시 리포트가 되어야 한다.
        ext_render_ctrl->hwparam.enable = enable;
        FBDEV_NOTI("fb(%d) ext_render(e-streamer render) enable=%d\n", fb_dev_id, ext_render_ctrl->hwparam.enable);

#ifdef FBDEV_O24_USE_EXT_RENDERER_IPC

        if (FBDEV_OS0_EXT_RENDER_REG_BASE)
        {
            FBDEV_HW_NOTI("++ write external render 0x%08x=0x%08x enable=0x%x\n",
                          FBDEV_OS0_EXT_RENDER_REG_BASE + 0x0,
                          ext_render_ctrl->hwparam.command,
                          enable);

            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE + 0x0, ext_render_ctrl->hwparam.command);
        }

#endif

        // (2023/11/06) OSD ON 시의 PQE notify 코드로 통합함. 아래 코드 블럭 참조
#if 0
        // see SICDTV-8491 : report estreamer visibility
        hw_ctx->user_initcall_ctrl.status.osd_estreamer = enable;
        FBDEV_O24_CMN_NotifyPQEDriver();
#endif

        // (2023/07/21)
        // F22 상태 변화 (가비지 제거) 등은 F22 에서 처리토록 하며, OSD kdriver 는 대기하지 않도록 한다.
        // OSD on/off 관련하여 불필요한 sleep 을 제거하기 위함이다.
#if 0

        // F22 이 상태 변경을 수신하기 까지 1 frame 정도 대기한다.
        if (!osd_hw_pm_suspend_stage)
        {
            usleep_range(16700, 16700);
        }

#endif
    }

    // see http://clm.lge.com/issue/browse/SCDCR-6376
    //
    // (추가) UI on/off 디버그 경우에 EST flag 가 제대로 전달되지 못하게 되므로, UI on 시에 EST flag
    // 가 켜져 있다면, 끌 수 있도록 조치한다.
    //
    // (2023/08/09) http://hlm.lge.com/qi/browse/DITTEST-3706 분석 과정에서 UI on/off 에 대한 처리는
    // 실제 OSD 가 on 되기 직전에 수행되어야 함. 이에 실행 위치를 이동함.
    //
    // (2023/11/06) PQE FW 와 E-streamer flag 동기화는 fb(1) ON 상태 한정으로 이동시킴.
    // 그외의 경우에는 E-Streamer flag off 상태로 리포트 하는것이 안정적이다.
    //
    if ((fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1) && enable)
    {
        int pqe_fw_estreamer_flag = 0;
        //LX_RECT_T crop_rgn;

        if (fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            pqe_fw_estreamer_flag = 0;
        }
        else
        {
            pqe_fw_estreamer_flag = 1;
        }

        hw_ctx->user_initcall_ctrl.status.osd_estreamer = pqe_fw_estreamer_flag;
        FBDEV_O24_CMN_NotifyPQEDriver();

        FBDEV_NOTI("fb(%d) on. notify PQE to ready estreamer <%s>\n",
                   fb_dev_id, pqe_fw_estreamer_flag ? "on" : "off");

        FBDEV_O24_CMN_WaitPQEDriverEstreamerSync(pqe_fw_estreamer_flag);

        //crop_rgn.x = 0;
        //crop_rgn.y = 0;
        //crop_rgn.w = hw_ctx->hw_fb0_width;
        //crop_rgn.h = hw_ctx->hw_fb0_height;

        //FBDEV_O24_CMN_SetOutputCropRegion(FALSE, hw_ctx->hw_fb0_width, hw_ctx->hw_fb0_height, 0, 0, &crop_rgn);
    }

    // 실제 OSD plane 에 대한 on/off 가 아래 코드 수행후 다음 vsync 이후에 반영이 될 것이다.
    for (i = 0; i < xnum; i++)
    {
        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, val);
        OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_enable, val);

        // (2021/07/013)
        // 만약 E-streamer 동작중 cursor ON 요청이 온다고 가정하면, 실제 화면에 보이면 안된다.
        // 커서 클릭에 의하여 EST Off, UI On 상황이 된다고 해도 첫번째 요청인 CSR ON 요청은 잠시
        // ignore 처리해야 한다.
        //
        // (2022/04/21)
        // 4K E-streamer 제공 필요에 따라, E-stramer ON 체크시에 외부 FRC 여부는 보지 않도록 한다.
        if (fb_dev_id == LX_FBDEV_ID_CSR0 && enable)
        {
            if (FBDEV_O24_CMN_GetOSDEnable(LX_FBDEV_ID_OSD1))
            {
                OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_enable, 0x0);
                FBDEV_NOTI("++ set cursor invisible (sync.en=0) when EXT_RENDER is shown\n");
            }
        }
    }

    for (i = 0; i < xnum && VALID_XIDX(xlst[i]) ; i++)
    {
        xidx = xlst[i];
        //FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);
    }

    FBDEV_NOTI("fb(%d) osd_ctrl_main, osd_ctrl_sync configured\n", fb_dev_id);

    // 이하 코드는 OSD plane 에 대한 on/off 에 연속하거나, 그 이후에 수행되어야 하는 부가적인 SW WA 들의 연속이다.
    // 만약 OSD on 동작이라면 아래 코드에서 AFBC 설정 등 연속으로 이어져야 하는 부분이 있으므로, 절대로 sleep 이
    // 있어서는 안된다.
    // 단 OSD off 동작의 경우라면 그 이후의 상태 변화에 맞게 출력의 안정성 고려하여 sleep 동작을 추가할 수 있다.

    // (2023/07/21)
    // UI off 시의 sleep 부분은 4K E-streamer 지원 부분 코드와 통합한다.
    // 즉 EST off, UI off 시의 2 vsync sleep 코드가 추가되어, 아래 sleep 은 무의미하다.
    //
    // see http://clm.lge.com/issue/browse/SICDTV-13023
#if 0

    // raixs.lim (2021/06/01) E60 의 상황을 참조하여, O24+F22 의 경우를 미리 대비함.
    //
    // (2020/11/17) http://clm.lge.com/issue/browse/SICDTV-8986, QEVENTTWON-8969
    // OSD off 과정에서 20% 의 확률로 화면 우측에서의 과도 (가비지) 출력 현상 있음
    // OSD off 과정에서 실제 OSD 출력을 끊고, 후속 조치(AFBC 중지 등)이 진행되도록 함
    //
    // (NOTE) O24 에서 아래 코드가 반드시 필요할지에 대하여 검증이 필요하다.
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && !enable)
    {
        if (!osd_hw_pm_suspend_stage)
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

    // osd0_hw_owner 변경시 추후 ON 상황에 대비하여, 이전 fb 의 사용 흔적을 지워져야 한다.
    // 즉 새로운 osd0_hw_owner 가 OSD path 를 흘러갈 수 있도록 조치한다.
    //
    // 다시 그림을 그린다고 해도, 이전 프레임 정보가 F22 쪽으로 흘러갈 수 있다.
    // 따라서 F22 에서는 OSD on/off 상태가 바뀌는 경우 일정 frame 을 ignore 처리하도록 설정해야 한다.
    // 현재는 약 10 frame 정보를 ignore 처리한다고 한다.
    // see http://clm.lge.com/issue/browse/AVTASK-640
    //
    // (2023/03/28) 4K-Estreamer 스펙에 따른 고려 사항
    // see http://clm.lge.com/issue/browse/SCDCR-5906
    //
    // (1) 4K-Estreamer 모드에서 UI 로 제어권이 넘어왔을때, 출력 해상도 값을 복원해야 한다.
    // 간단한 방법으로 PQEFW 제어를 1회 off 설정 + OSD header 강제 업데이트 요청 조치한다.
    //
    // (2) 4K-Estreamer 에서 hw_osd0 의 주인이 바뀌는 순간 crop 영역 정보를 초기화 해주어야 한다.
    // 특히 4K-Estreamer 모드에서 UI 로 전환시 crop 을 UI 에 맞도록 재설정 해주지 않으면,
    // crop 된 상태로 UI 가 출력되어 이상하게 보인다.
    //
    // 주인이 E-Streamer 로 바뀔때도 512x2160 기본 crop 모드를 먼저 활성화 조치한다. (nice to have)
    //
    // (2023/07/24) 4K OLED E-Streamer 지원에 따른 정책 수정
    // hw_osd0_owner 변경에 따라 필요시 화면 업데이트는 변함이 없으나,
    // crop region 업데이트는 osd off 에서만 진행하도록 수정한다.
    //
    if (hw_osd0_owner != hw_ctx->hw_osd0_owner)
    {
        struct scanvas* hw_osd0_owner_canvas = FBDEV_GetWinCanvas(hw_ctx->hw_osd0_owner);

        FBDEV_NOTI("++ hw_osd0_owner changed by fb(%d).%s\n", fb_dev_id, (enable) ? "enable" : "disable");

        if (hw_ctx->b_support_fb1 && !hw_ctx->b_support_ext_render)
        {
            int fb_width;
            int fb_height;
            LX_RECT_T crop_rgn;
            FBDEV_O24_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O24_GET_EXT_RENDER_CTRL(hw_ctx);

            FBDEV_NOTI("++ make fb(%d) default crop region by hw_osd0_owner change\n", hw_ctx->hw_osd0_owner);

            if (hw_ctx->hw_osd0_owner == LX_FBDEV_ID_OSD0)
            {
                fb_width = hw_ctx->hw_fb0_width;
                fb_height = hw_ctx->hw_fb0_height;
            }
            else
            {
                fb_width = hw_ctx->hw_fb1_width;
                fb_height = hw_ctx->hw_fb1_height;
            }

            crop_rgn.x = 0;
            crop_rgn.y = 0;
            crop_rgn.w = fb_width;
            crop_rgn.h = fb_height;

            ext_render_ctrl->hwparam.xoffset = 0;
            ext_render_ctrl->hwparam.yoffset = 0;
            ext_render_ctrl->hwparam.crop_x  = 0;
            ext_render_ctrl->hwparam.crop_y  = 0;
            ext_render_ctrl->hwparam.crop_w  = fb_width;
            ext_render_ctrl->hwparam.crop_h  = fb_height;

            FBDEV_O24_CMN_SetOutputCropRegion(FALSE, fb_width, fb_height, 0, 0, &crop_rgn);
        }

        if (hw_osd0_owner_canvas)
        {
            if (hw_ctx->hw_osd0_owner == LX_FBDEV_ID_OSD0 && !hw_ctx->b_support_ext_render)
            {
                FBDEV_NOTI("++ disable PQEFW_OSD0_OUT_CTRL temporarily\n");
                hw_ctx->hw_wa_flag &= ~FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;
            }

            FBDEV_NOTI("++ write fb(%d) header immediately\n", hw_ctx->hw_osd0_owner);
            FBDEV_O24_CMN_WriteOSDHeader(hw_osd0_owner_canvas);
        }
    }

    // raxis.lim (2019/10/08) -- enable/disable afbc reader if necessary
    //
    // OSD reader is configured to AFBC mode not MIF, CCO0/CCO1 will read something even though OSD is off state.
    // So we should control afbc(x)_init_en, afbc(x)_auto_init_en flag
    // refer to http://clm.lge.com/issue/browse/AVTASK-401
    //
#ifdef FBDEV_O24_USE_AFBC_READ_BW_SAVING
    {
        int afbc_status = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFBC, fb_dev_id);
        int afrc_status = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFRC, fb_dev_id);

        OSD_TOP_CTRL_RdFL(ctrl_auto_init_afbc);

        FBDEV_HW_NOTI("fb(%d) afbc_status=%d, afrc_status=%d, enable=%d\n",
                      fb_dev_id, afbc_status, afrc_status, enable);

        if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
        {
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,        enable);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en,   enable);
        }

        if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
        {
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en,        enable);
            OSD_TOP_CTRL_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en,   enable);
        }

        OSD_TOP_CTRL_Wr01(ctrl_block, reg_afbc_afrc_sel, afrc_status);

        FBDEV_O24_FBC_DEBUG("fb(%d) afbc_status=%d, afrc_status=%d, view=%d\n",
                            fb_dev_id, afbc_status, afrc_status, enable);

        OSD_TOP_CTRL_WrFL(ctrl_auto_init_afbc);
        OSD_TOP_CTRL_WrFL(ctrl_block);

        if (afbc_status || afrc_status)
        {
            FBDEV_NOTI("fb(%d) afbc/afrc configured\n", fb_dev_id);
        }
    }
#endif

    // (2020/10/16)  Estreamer 동작 종료후, UI 가 켜질때 cursor 를 복구시킬 수 있도록 함
    // see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && enable && FBDEV_O24_CMN_GetOSDEnable(LX_FBDEV_ID_CSR0))
    {
        int csr_xnum, csr_xlst[2], csr_afbc_xlst[2];

        csr_xnum = FBDEV_O24_CMN_GetHWXListEx(LX_FBDEV_ID_CSR0, csr_xlst, csr_afbc_xlst);

        if (csr_xnum > 0)
        {
            int csr_xidx = csr_xlst[0];

            OSDX_CTRL_RdFL(osdx_ctrl[csr_xidx], osd_ctrl_sync0);
            OSDX_CTRL_Wr01(osdx_ctrl[csr_xidx], osd_ctrl_sync0, osd_sync_enable, 0x1);
            OSDX_CTRL_WrFL(osdx_ctrl[csr_xidx], osd_ctrl_sync0);

            FBDEV_NOTI("++ set cursor visible (sync.en=1) when UI is shown\n");
        }
    }

#ifdef FBDEV_O24_SUPPORT_SW_WA_SICDTV_10362

    // O24+F22 osd_change_flag 인터페이스 미진한 부분 보강
    // see http://clm.lge.com/issue/browse/SICDTV-10362
    //
    if (hw_ctx->b_support_ext_frc)
    {
        // (2020/10/20)
        // cursor layer off 시에 x 값을 +1 하여 F22 로 OSD 변경으로 리포트 되게 함
        //
        if (fb_dev_id == LX_FBDEV_ID_CSR0 && !enable)
        {
            struct scanvas* canvas = FBDEV_GetWinCanvas(fb_dev_id);

            if (canvas)
            {
                int org_x = canvas->output_win.x;

                canvas->output_win.x += 1;

                FBDEV_NOTI("fb(%d) SICDTV_10362 activated (org_x=%d, tmp_x=%d)\n",
                           fb_dev_id, org_x, canvas->output_win.x);

                FBDEV_O24_CMN_WriteOSDHeader(canvas);

                canvas->output_win.x = org_x;
            }
        }

        // (2020/11/01) UI 부분 보강
        //
        // UI layer off 시에 이전의 osd framebuffer를 기록함으로써, F22 의 osd change flag 를
        // 생성시킨다.
        if (((fb_dev_id == LX_FBDEV_ID_OSD0) || (fb_dev_id == LX_FBDEV_ID_OSD1)) && !enable)
        {
            struct scanvas* canvas = FBDEV_GetWinCanvas(fb_dev_id);

            if (canvas)
            {
                UINT32 org_fbmem = canvas->osd_bm_paddr;

                canvas->osd_bm_paddr = canvas->prev_osd_bm_paddr;

                FBDEV_NOTI("fb(%d) SICDTV_10362 activated (org_fb=0x%08x, tmp_fb=0x%08x)\n",
                           fb_dev_id, org_fbmem, canvas->osd_bm_paddr);

                FBDEV_O24_CMN_WriteOSDHeader(canvas);

                canvas->osd_bm_paddr = org_fbmem;
            }
        }
    }

#endif

#if 0

    // (2023/03/28) 4K-Estreamer 모드에서 UI 가 enable 될때, 원래 4K output_win 설정을 복원해 줘야 한다.
    // 간단한 방법으로 PQEFW 제어를 잠시 off 설정 + OSD 강제 업데이트 요청 조치한다.
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && enable && !hw_ctx->b_support_ext_render)
    {
        struct scanvas* canvas = FBDEV_GetWinCanvas(fb_dev_id);

        if (canvas)
        {
            hw_ctx->hw_wa_flag &= ~FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL;

            FBDEV_O24_CMN_WriteOSDHeader(canvas);
        }
    }

#endif

    // (2023/07/21) 4k E-Streamer 제어 관련 추가
    //
    // UI off 시에 PQE FW 로 estreamer 시작을 준비할 수 있도록 한다.
    // EST off 시에 PQE Fw 로 estreamer 종료를 준비할 수 있도록 한다.
    // 2 vsync 만큼의 안정화 기간을 보장할 수 있도록 한다.
    //
    // (note) 8K 60Hz 까지 고려하여 2 vsync = 33.3 ms sleep 추가한다. 4K 120Hz 기준 4 vsync 에 해당하는
    // 긴 시간이지만 큰 값이 아니다. 추후 필요시 vsync 주기 고려하여 수정하도록 한다.
    //
    // see http://clm.lge.com/issue/browse/SCDCR-6376
    //
    // (추가) UI on/off 디버그 경우에 EST flag 가 제대로 전달되지 못하게 되므로, UI on 시에 EST flag
    // 가 켜져 있다면, 끌 수 있도록 조치한다.
    //
    // (2023/08/09) http://hlm.lge.com/qi/browse/DITTEST-3706 분석 과정에서 UI on/off 에 대한 처리는
    // 실제 OSD 가 on 되기 직전에 수행되어야 함. 이에 위치를 앞 부분으로 이동함.
    //
    // (2023/11/06) PQE FW 와 E-streamer flag 동기화는 fb(1) ON 상태 한정으로 이동시킴.
    // 그외의 경우에는 E-Streamer flag off 상태로 리포트 하는것이 안정적이다.
    //
    if ((fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1) && !enable)
    {
        int pqe_fw_estreamer_flag = 0; // 고정값 0

        hw_ctx->user_initcall_ctrl.status.osd_estreamer = pqe_fw_estreamer_flag;
        FBDEV_O24_CMN_NotifyPQEDriver();

        FBDEV_NOTI("fb(%d) off. notify PQE to ready estreamer <%s>\n",
                   fb_dev_id, pqe_fw_estreamer_flag ? "on" : "off");

        FBDEV_O24_CMN_WaitPQEDriverEstreamerSync(pqe_fw_estreamer_flag);
    }


    // 메모리절감을 통해서 fb(1) 이 off 되면, 즉시 IPC용 framebuffer 를 제거하도록 하자.
    if (fb_dev_id == LX_FBDEV_ID_OSD1 && !enable)
    {
        FBDEV_O24_CMN_DestroyExternalRendererFrameBuffer();
    }

    return RET_OK;
}

// disable all active OSD path (hide all OSDs)
//
//
static void FBDEV_O24_CMN_ShutdownOSDPath(void)
{
    int i;

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        if (g_fbdev_cfg->fb[i].b_active)
        {
            FBDEV_NOTI("shutdown fb(%d)\n", i);
            FBDEV_O24_CMN_SetOSDEnable(i, FALSE);
        }
    }

    FBDEV_NOTI("completed\n");
}

// OSD HW Layer status
//
// wparam   void
// @return  int 1 : ON , 0 : OFF
//
int FBDEV_O24_CMN_GetOSDEnable(int fb_dev_id)
{
    UINT32 val;
    int xidx;
    int xnum, xlst[2];

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);

    // ignore noisy warning msg becase some OSD layer is not supported by HW
    if (INVALID_XNUM(xnum)) return FALSE;

    // raxis.lim (2019/05/21) -- event though OSD requires two POSD for 4K display, we can just check the first POSD value
    xidx = xlst[0];
    FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

    OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
    OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, val);

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

int FBDEV_O24_CMN_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl)
{
    int i;
    //ULONG flags;

    // we can't do spinlock when pivot mode is enabled because sleep ocurrs during GFX merge
    // (2023/04/11) osd on/off 처리중 sleep 가능성이 크므로, spin lock 제거함.
    // spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        if (ctrl->view_status[i] == 0x0 || ctrl->view_status[i] == 0x1)
        {
            FBDEV_O24_CMN_SetOSDEnable(i, ctrl->view_status[i]);
        }
    }

    // spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);

    return RET_OK;
}

// set OSD out connection ctrl
//
//  param pConnCtrl [IN] connection control data
//  @return RET_OK if success, RET_ERROR otherwise
//
//
int     FBDEV_O24_CMN_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
    int     i;
    BOOLEAN osd_view_status[LX_FBDEV_ID_MAX];

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    FBDEV_WARN("OSD conn change. conn_type 0x%x (%s disp)\n", pConnCtrl->conn_type,
               (g_fbdev_cfg->uhd_disp_mode) ? "UHD" : "FHD");

    FBDEV_CHECK_DEBUG(hw_ctx->hw_conn_type == pConnCtrl->conn_type, return RET_OK, "ignore the dup calls (0x%x)\n",
                      pConnCtrl->conn_type);

    // save current config. diable OSD before changing OSD config
    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        osd_view_status[i] = FBDEV_O24_CMN_GetOSDEnable(i);
        FBDEV_O24_CMN_SetOSDEnable(i, FALSE);
    }

    // disable ISR to change ISR source
    FBDEV_O24_CMN_SetInterruptEnable(MIXER_INTR, FALSE);

    // sleep until OSD stablized. not necessary to sleep in O24

    if (pConnCtrl->conn_type & LX_FBDEV_CONN_OSD_VIDEO_SEPARATE)
    {
        FBDEV_HW_DEBUG("O24::S.OSD\n");

        hw_ctx->hw_disp_width   = hw_ctx->sosd_disp.out_width;
        hw_ctx->hw_disp_height  = hw_ctx->sosd_disp.out_height;
    }
    else if (pConnCtrl->conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
    {
        FBDEV_HW_DEBUG("O24::B.OSD\n");

        hw_ctx->hw_disp_width   = hw_ctx->bosd_disp.out_width;
        hw_ctx->hw_disp_height  = hw_ctx->bosd_disp.out_height;
    }
    else
    {
        FBDEV_WARN("invalid connection 0x%x\n", pConnCtrl->conn_type);
        goto func_exit;
    }

    // save the current connection
    hw_ctx->hw_conn_type = pConnCtrl->conn_type;

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        hw_ctx->conn_ctrl[i].conn_type = hw_ctx->hw_conn_type;
    }

    // reinit HW. OSD might be off during re-initialization
    FBDEV_O24_CMN_ReInitHW();

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        FBDEV_WriteOSDHeader(&g_dm_ctx->wctx[i]->pixel);
    }

func_exit:

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        FBDEV_O24_CMN_SetOSDEnable(i, osd_view_status[i]);
    }

    return RET_OK;
}

int     FBDEV_O24_CMN_SRCtrl(BOOLEAN onoff)
{
    FBDEV_O24_CMN_SetupSRScaler(onoff, TRUE);
    return RET_OK;
}

// debug only
//
int     FBDEV_O24_CMN_MirrorCtrl(BOOLEAN v_mirror_en)
{
    int i, j;
    int fb_list[] = {LX_FBDEV_ID_OSD0, LX_FBDEV_ID_OSD3};

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();
    FBDEV_O24_MIRROR_CTRL_T* mirror_ctrl = FBDEV_O24_GET_MIRROR_CTRL(hw_ctx);
    FBDEV_O24_FBC_CTRL_T* fbc_ctrl = FBDEV_O24_GET_FBC_CTRL(hw_ctx, LX_FBDEV_ID_OSD0);

    int hw_status = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_VMIRROR, 0x0);

    FBDEV_NOTI("request mirror_ctrl. req_val=%d, hw_status=%d\n", v_mirror_en, hw_status);

    if (hw_status == v_mirror_en)
    {
        FBDEV_NOTI("ignore vmirror change. hw_status=%d\n", hw_status);
        return RET_OK;
    }

    /* change mirror configuratin */
    mirror_ctrl->status = (v_mirror_en) ? FBDEV_O24_V_MIRROR_ON : 0x0;

    for (j = 0; j < NELEMENTS(fb_list); j++)
    {
        int xidx;
        int xnum, xlst[2];

        xnum = FBDEV_O24_CMN_GetHWXList(fb_list[j], xlst);

        for (i = 0; i < xnum; i++)
        {
            xidx = xlst[i];

            if (INVALID_XIDX(xlst[i])) continue;

            OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
            OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

            FBDEV_NOTI("fb(%d) before: 0x%08x 0x%08x\n", fb_list[j],
                       OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_main),
                       OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_sync0));

            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, v_mirror_en);
            OSDX_CTRL_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_v_reverse, v_mirror_en);

            OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
            OSDX_CTRL_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);

            FBDEV_NOTI("fb(%d) after: 0x%08x 0x%08x\n", fb_list[j],
                       OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_main),
                       OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_sync0));
        }
    }

    // make AFBC header to setup again when next framebuffer is updated
    fbc_ctrl->status &= ~FBDEV_O24_FBC_STATUS_HDR_SETUP;

    {
        FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(LX_FBDEV_ID_OSD0);

        if (wctx)
        {
            FBDEV_O24_CMN_WriteOSDHeader(&wctx->pixel);
        }
    }

    return RET_OK;
}

// VOSD ISR handler
void     FBDEV_O24_CMN_ISRHook(void)
{
    // monitor afbc line_wait_cnt change by PQE FW
    // see http://clm.lge.com/issue/browse/SICDTV-13236
    {
        int afbc_xidx = 0;
        UINT32 img_width;
        UINT32 line_wait_cnt;
        static UINT32 line_wait_cnt_sav = 0x0;

        OSD_AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_4);
        OSD_AFBC_CTRL_Rd01(afbc_xidx, ctrl_afbc_4, line_wait_cnt, line_wait_cnt);
        OSD_AFBC_CTRL_Rd01(afbc_xidx, ctrl_afbc_4, img_width, img_width);

        if (line_wait_cnt_sav != line_wait_cnt)
        {
            FBDEV_NOTI("afbc%d.line_wait_cnt changed from 0x%03x to 0x%03x, img_width=%d\n", afbc_xidx, line_wait_cnt_sav,
                       line_wait_cnt, img_width);

            line_wait_cnt_sav = line_wait_cnt;
        }
    }

    /* do nothing */
}

/*========================================================================================
    Implementation Group (DIAG/PROC)
========================================================================================*/
// HW status
//
//  read register(s) to get some HW status
//  return value seems to be boolean value but there might be exceptions
//  read comments before using the functioin
//
int      FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_T status, UINT32 opt)
{
    int val = 0;

    switch (status)
    {
        // return 1 if HW is set to AFBC configuration. otherwise return 0
        case FBDEV_O24_HW_STATUS_AFBC:
        {
            int afbc_en = 0;
            int fbc_block_sel;

            OSD_TOP_CTRL_RdFL(ctrl_dpath);
            OSD_TOP_CTRL_RdFL(ctrl_block);

            OSD_TOP_CTRL_Rd01(ctrl_block, reg_afbc_afrc_sel, fbc_block_sel);

            if (opt == LX_FBDEV_ID_OSD0)
            {
                OSD_TOP_CTRL_Rd01(ctrl_dpath, osd0_afbc_en, afbc_en);
            }
            // (2021/07/05) fb(1) 과 fb(0) 이 같은 HW 를 읽고 있음을 기억하자.
            else if (opt == LX_FBDEV_ID_OSD1)
            {
                OSD_TOP_CTRL_Rd01(ctrl_dpath, osd0_afbc_en, afbc_en);
            }

            val = (afbc_en && !fbc_block_sel) ? 1 : 0;

        }
        break;

        case FBDEV_O24_HW_STATUS_AFRC:
        {
            int afrc_en = 0;
            int fbc_block_sel;

            OSD_TOP_CTRL_RdFL(ctrl_dpath);
            OSD_TOP_CTRL_RdFL(ctrl_block);

            OSD_TOP_CTRL_Rd01(ctrl_block, reg_afbc_afrc_sel, fbc_block_sel);

            if (opt == LX_FBDEV_ID_OSD0)
            {
                OSD_TOP_CTRL_Rd01(ctrl_dpath, osd0_afbc_en, afrc_en);
            }
            // (2021/07/05) fb(1) 과 fb(0) 이 같은 HW 를 읽고 있음을 기억하자.
            else if (opt == LX_FBDEV_ID_OSD1)
            {
                OSD_TOP_CTRL_Rd01(ctrl_dpath, osd0_afbc_en, afrc_en);
            }

            val = (afrc_en && fbc_block_sel) ? 1 : 0;
        }
        break;

        case FBDEV_O24_HW_STATUS_FBC:
        {
            int afbc_status = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFBC, opt);
            int afrc_status = FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFRC, opt);

            val = (afrc_status) ? LX_FBDEV_FBC_FORMAT_AFRC :
                  (afbc_status) ? LX_FBDEV_FBC_FORMAT_AFBC : LX_FBDEV_FBC_FORMAT_RAW;
        }
        break;

        case FBDEV_O24_HW_STATUS_VISIBLE:
        {
            val = FBDEV_O24_CMN_GetOSDEnable(opt);
        }
        break;

        case FBDEV_O24_HW_STATUS_SR_GAIN:
        {
            OSD_SHP_CTRL_RdFL(shp_lti_ctrl_00);
            OSD_SHP_CTRL_Rd01(shp_lti_ctrl_00, reg_lti_2d_gain, val);
        }
        break;

        case FBDEV_O24_HW_STATUS_VMIRROR:
        {
            OSDX_CTRL_RdFL(osdx_ctrl[0], osd_ctrl_main);
            OSDX_CTRL_Rd01(osdx_ctrl[0], osd_ctrl_main, osd_v_reverse_en, val);
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

// HW diagnostics
//
// dump important paramters and valiate settings. this function will help to view HW status
// (usage) cat /proc/lg/fbdev/chip/diag
//
void FBDEV_O24_CMN_DiagHW(struct seq_file* m)
{
    UINT32 val;

    int xidx;
    int xnum, xlst[2];
    int fb_dev_id = LX_FBDEV_ID_OSD0;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

    xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);
    xidx = xlst[0];

    /* print HW core info */
    {
        seq_printf(m, "disp.path: %s\n", (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? "bosd" : "sosd");
        seq_printf(m, "disp.width: %d\n", hw_ctx->hw_disp_width);
        seq_printf(m, "disp.height: %d\n", hw_ctx->hw_disp_height);

        seq_printf(m, "\n");
        seq_printf(m, "disp.uhd_mode: %d\n", FBDEV_O24_CMN_IsUHDDispMode() ? 1 : 0);
        seq_printf(m, "fb0.width: %d\n", hw_ctx->hw_fb0_width);
        seq_printf(m, "fb0.height: %d\n", hw_ctx->hw_fb0_height);
        seq_printf(m, "fb1.width: %d\n",  hw_ctx->hw_fb1_width);
        seq_printf(m, "fb1.height: %d\n", hw_ctx->hw_fb1_height);
        seq_printf(m, "ext.width: %d\n", hw_ctx->hw_ext_render_width);
        seq_printf(m, "ext.height: %d\n", hw_ctx->hw_ext_render_height);
        seq_printf(m, "hw_osd0_owner: fb(%d)\n", hw_ctx->hw_osd0_owner);
        seq_printf(m, "\n");
        seq_printf(m, "vsync_clk: %dHz\n", (FBDEV_O24_CMN_DetectVSyncClk() == FBDEV_VSYNC_CLK_60HZ) ? 60 : 120);

        seq_printf(m, "support_ext_frc: %d\n", hw_ctx->b_support_ext_frc);
        seq_printf(m, "support_fb1: %d\n", hw_ctx->b_support_fb1);
        seq_printf(m, "support_4kosd: %d\n", hw_ctx->b_support_4kosd);
        seq_printf(m, "support_ext_render: %d\n", hw_ctx->b_support_ext_render);
        seq_printf(m, "\n");

        seq_printf(m, "sr_ctrl[0].status: 0x%08x\n", hw_ctx->sr_ctrl[0].status);
        seq_printf(m, "sr_ctrl[0].ti_gain: 0x%08x\n", hw_ctx->sr_ctrl[0].ti_gain);
        seq_printf(m, "sr_ctrl[1].status: 0x%08x\n", hw_ctx->sr_ctrl[1].status);
        seq_printf(m, "sr_ctrl[1].ti_gain: 0x%08x\n", hw_ctx->sr_ctrl[1].ti_gain);
        seq_printf(m, "\n");

        // (2020/01/18) read the real HW configuration NOT status value.
        // because application might refer this proc to make its reverse-mode config BEFORE kdriver initialization
        // see " user_initcall based HW initialization" policy.
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, val);
        seq_printf(m, "mirror.status: 0x%08x\n", val);
        seq_printf(m, "\n");

        seq_printf(m, "ext_rener.fbmem0: 0x%08x\n", hw_ctx->ext_render_ctrl.fbmem_phys[0]);
        seq_printf(m, "ext_rener.fbmem1: 0x%08x\n", hw_ctx->ext_render_ctrl.fbmem_phys[1]);
        seq_printf(m, "ext_rener.fbmem_idx: %d\n",  hw_ctx->ext_render_ctrl.fbmem_buf_idx);

        seq_printf(m, "ext_rener.hwparam.phys_y: 0x%08x\n", hw_ctx->ext_render_ctrl.hwparam.phys_y);
        seq_printf(m, "ext_rener.hwparam.size: 0x%08x\n", hw_ctx->ext_render_ctrl.hwparam.size);
        seq_printf(m, "ext_rener.hwparam.xoffset: %d\n", hw_ctx->ext_render_ctrl.hwparam.xoffset);
        seq_printf(m, "ext_rener.hwparam.yoffset: %d\n", hw_ctx->ext_render_ctrl.hwparam.yoffset);
        seq_printf(m, "ext_rener.hwparam.enable: %d\n", hw_ctx->ext_render_ctrl.hwparam.enable);
        seq_printf(m, "ext_rener.hwparam.crop_x: %d\n", hw_ctx->ext_render_ctrl.hwparam.crop_x);
        seq_printf(m, "ext_rener.hwparam.crop_y: %d\n", hw_ctx->ext_render_ctrl.hwparam.crop_y);
        seq_printf(m, "ext_rener.hwparam.crop_w: %d\n", hw_ctx->ext_render_ctrl.hwparam.crop_w);
        seq_printf(m, "ext_rener.hwparam.crop_h: %d\n", hw_ctx->ext_render_ctrl.hwparam.crop_h);
        seq_printf(m, "ext_rener.hwparam.tx_count: %d\n", hw_ctx->ext_render_ctrl.hwparam.tx_count);
    }

    /* print SW WA info */
    {
        seq_printf(m, "\n");
        seq_printf(m, "pqefw_osd0_out_ctrl: 0x%x\n", osd_pqefw_osd0_out_ctrl);
        seq_printf(m, "hw_wa.1x_csr_disp_on_blend_path: 0x%x\n",
                   (hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_1X_CSR_DISP_ON_BLEND_PATH) ? 1 : 0);
        seq_printf(m, "hw_wa.osd0_async_wr_error:       0x%x\n",
                   (hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR) ? 1 : 0);
        seq_printf(m, "hw_wa.pqwfw_osd0_out_ctrl:       0x%x\n",
                   (hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_PQEFW_OSD0_OUT_CTRL) ? 1 : 0);
        seq_printf(m, "hw_wa_flag:                      0x%x\n", hw_ctx->hw_wa_flag);
        seq_printf(m, "\n");
    }

    /* print OSD_SHP info */
    {
        int xidx;
        int xnum, xlst[2];
        int fb_dev_id = LX_FBDEV_ID_OSD0;

        UINT32 bypass_en, detour_en;
        UINT32 rgb2yc_csc_en_de_clk, yc2rgb_csc_en, rgb2yc_csc_p_en_oclk, yuv2rgb_en;

        FBDEV_O24_SR_CTRL_T* sr_ctrl = FBDEV_O24_GET_SR_CTRL(hw_ctx, fb_dev_id);

        xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);
        FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

        xidx = xlst[0];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

        OSD_SHP_CTRL_RdFL(shp_core_ctrl_00);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

        OSD_SHP_CTRL_Rd01(shp_core_ctrl_00, reg_top_bypass, bypass_en);

        OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, detour_en);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en_de_clk, rgb2yc_csc_en_de_clk);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_csc_en, yc2rgb_csc_en);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_p_en_oclk, rgb2yc_csc_p_en_oclk);
        OSDX_CTRL_Rd01(hdr_ui, osd_hdrui_yc2rgb_ctrl00, reg_yuv2rgb_en, yuv2rgb_en);

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

    /* print 4kosd */
    {
        int xidx = 1; /* OSD_IMAGE0_1 */
        UINT32 osd_4k_enable;
        UINT32 sc_i_w, sc_i_h;
        UINT32 sc_o_w, sc_o_h;

        OSDX_CTRL_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
        OSDX_CTRL_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3);

        OSDX_CTRL_Rd01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0, reg_4k_mode_en, osd_4k_enable);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_w, sc_i_w);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_h, sc_i_h);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3, reg_sc_o_w, sc_o_w);
        OSDX_CTRL_Rd01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3, reg_sc_o_h, sc_o_h);

        seq_printf(m, "4kosd.enable: 0x%x\n", osd_4k_enable);
        seq_printf(m, "4kosd.input: %dx%d\n", sc_i_w, sc_i_h);
        seq_printf(m, "4kosd.output: %dx%d\n", sc_o_w, sc_o_h);
    }

    /* print HW_CTX status */

    /* TODO: add something */
}

/** chip specific proc handler
 *
 */
void FBDEV_O24_CMN_ProcHandler(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
    switch (proc_id)
    {
        case FBDEV_HW_PROC_ID_DETAIL_INFO:
        {
#if 0
            FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

            seq_printf(m, "<HW INFO>\n");
            seq_printf(m, "path: %s\n", (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? "bosd" : "sosd");
            seq_printf(m, "hw_disp_width: %d\n",    hw_ctx->hw_disp_width);
            seq_printf(m, "hw_disp_height: %d\n",   hw_ctx->hw_disp_height);
            seq_printf(m, "hw_fb0_width: %d\n",     hw_ctx->hw_fb0_width);
            seq_printf(m, "hw_fb0_height: %d\n",    hw_ctx->hw_fb0_height);
            seq_printf(m, "vsync_clk: %dHz\n", (FBDEV_O24_CMN_DetectVSyncClk() == FBDEV_VSYNC_CLK_60HZ) ? 60 : 120);

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
            FBDEV_O24_OSD_HDR_T* osd_hdr = (FBDEV_O24_OSD_HDR_T*)hdr_lst;
            LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

            xnum = FBDEV_O24_CMN_GetHWXList(fb_dev_id, xlst);
            seq_printf(m, "posd_num: %d\n", xnum);

            for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
            {
                xidx = xlst[i];

                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

                OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, osd_en);
                OSDX_CTRL_Rd01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_enable, sync_en);

                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr1);
                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr3);
                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr4);
                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr5);
                OSDX_CTRL_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);

                hdr_lst[0] = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr0);
                hdr_lst[1] = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr1);
                hdr_lst[2] = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr2);
                hdr_lst[3] = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr3);
                hdr_lst[4] = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr4);
                hdr_lst[5] = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr5);
                hdr_lst[6] = OSDX_CTRL_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);

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
                { .desc = "OSD",  .reg_base = O24_CCO_BASE,                 .reg_size = sizeof(OSD_O24_REG_T) }, //1536 }, //sizeof(OSD_O24_REG_T) },
                { .desc = "TOP",  .reg_base = O24_CCO_TOP_CTRL_BASE,        .reg_size = sizeof(OSD_TOP_CTRL_O24_REG_T) }, //256 }, //sizeof(OSD_TOP_O24_REG_T) },
                { .desc = "TOP1", .reg_base = O24_CCO_TOP_CTRL1_BASE,        .reg_size = sizeof(OSD_TOP_CTRL1_O24_REG_T) }, //256 }, //sizeof(OSD_TOP_O24_REG_T) },

                { .desc = "SHP",  .reg_base = O24_CCO_SHP0_BASE,            .reg_size = sizeof(OSD_SHP_O24_REG_T) }, //768 }, //sizeof(OSD_SHP_O24_REG_T) },
                { .desc = "MIF0", .reg_base = O24_CCO_MIF0_BASE,            .reg_size = sizeof(OSD_MIF0_CTRL_O24_REG_T) },
                { .desc = "MIF1", .reg_base = O24_CCO_MIF1_BASE,            .reg_size = sizeof(OSD_MIF1_CTRL_O24_REG_T) },

                { .desc = "AFBC0", .reg_base = O24_CCO_AFBC0_BASE,           .reg_size = sizeof(OSD_AFBC_O24_REG_T) }, //256 }, //sizeof(OSD_AFBC_O24_REG_T) },
                { .desc = "AFBC1", .reg_base = O24_CCO_AFBC1_BASE,           .reg_size = sizeof(OSD_AFBC_O24_REG_T) }, //256 }, //sizeof(OSD_AFBC_O24_REG_T) },
                { .desc = "AFRC0", .reg_base = O24_CCO_AFRC0_BASE,           .reg_size = sizeof(OSD_AFRC_O24_REG_T) }, //256 }, //sizeof(OSD_AFBC_O24_REG_T) },
                { .desc = "AFRC1", .reg_base = O24_CCO_AFRC1_BASE,           .reg_size = sizeof(OSD_AFRC_O24_REG_T) }, //256 }, //sizeof(OSD_AFBC_O24_REG_T) },
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
int FBDEV_O24_CMN_RunResume(void)
{
    // OSD freeze will be stopped after 500 ms
    FBDEV_O24_CMN_RunBootLogoTimer(osd_resume_freeze_timeout, TRUE);

    FBDEV_O24_CMN_ReInitHW();

    return RET_OK;
}

int FBDEV_O24_CMN_RunSuspend(void)
{
    // do nothing
    return RET_OK;
}

/*========================================================================================
    common OSD HW handler
========================================================================================*/
FBDEV_O24_HW_FUNC_T  g_fbdev_o24_cmn_hw_func =
{
    /* variable is initialize at fbdev_drv_O24.c */

    .O24_InitHW          = FBDEV_O24_CMN_InitHW,
};

