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
/*
/@file name : fbdev_module.c
/@description : fbdev ioctl's function
**/

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#if CONFIG_LX_BOARD_FPGA
#define FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT    4000000 /* max 4M us = 4000 ms = 0.25 fps */
#else
#define FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT    50000   /* max 50,000 us = 50 ms = 20 fps */
#endif

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/tty.h>
#include <linux/slab.h>      /**< kmalloc() */
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <asm/io.h>
#include <linux/fs.h>        /**< everything\ldots{} */
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)
#include <asm/hardware.h>
#endif

#include <asm/uaccess.h>

#include <linux/device.h>

#include <linux/interrupt.h>     /** irqreturn_t */
#include <linux/irq.h>
#include <asm/irq.h>

#include <linux/fb-ext/fb-ext.h>

#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "fbdev_drm.h"
#include "hma_alloc.h"
#include "os_util.h"

#ifdef INCLUDE_KDRV_GFX
#include "gfx_export.h"
#endif

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif

#include "afbc_sw_drv.h"

#include <linux/list.h>
#include <linux/pm_runtime.h>
#include <linux/seq_file.h>
#include <linux/dma-buf.h>
#include <linux/highmem.h>

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define LCD_PANEL_CLOCK     180000  // not be used

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define report_runtime_status(level,fb_dev_id, view_status, type, result)   \
    do {\
        pr_info("LowPower::%s::%s::fb%d::%d::%s-%s::%s::%s\n",\
            level,  \
            "groupother", \
            fb_dev_id, \
            (view_status & 0x1) + ((view_status>>1) & 0x1) + ((view_status>>2) & 0x1) + ((view_status>>3) & 0x1) , \
            current->group_leader->comm, \
            current->comm, \
            type, \
            result);\
    } while(0)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
#ifndef FBEXTIO_PUT_DISPLAYREGION

/* http://clm.lge.com/issue/browse/SCDCR-2987 참조 */
#define FBEXTIO_PUT_DISPLAYREGION 0x46e03

struct fb_ext_displayregion
{
    __u32 x;
    __u32 y;
    __u32 width;
    __u32 height;
};
#endif

#ifndef FBEXTIO_PUT_INPUTBUFFER_RESOLUTION
/* http://hlm.lge.com/issue/browse/TVPLAT-88213 참조 */
#define FBEXTIO_PUT_INPUTBUFFER_RESOLUTION 0x46e04

struct fb_ext_buffer_resolution
{
    __u32 width;
    __u32 height;
};
#endif

/*---------------------------------------------------------------------------------------
    Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern void FBDEV_M17_InitHWCtx(FBDEV_HW_CTX_T* hal);
extern void FBDEV_O18_InitHWCtx(FBDEV_HW_CTX_T* hal);
extern void FBDEV_M19_InitHWCtx(FBDEV_HW_CTX_T* hal);
extern void FBDEV_O20_InitHWCtx(FBDEV_HW_CTX_T* hal);
extern void FBDEV_E60_InitHWCtx(FBDEV_HW_CTX_T* hal);
extern void FBDEV_O22_InitHWCtx(FBDEV_HW_CTX_T* hal);
extern void FBDEV_M23_InitHWCtx(FBDEV_HW_CTX_T* hal);
extern void FBDEV_O24_InitHWCtx(FBDEV_HW_CTX_T* hal);
extern void FBDEV_O26_InitHWCtx(FBDEV_HW_CTX_T* hal);

extern void FBDEV_PROC_Init(void);
extern void FBDEV_PROC_Cleanup(void);

extern ENDIAN_INFORM_T FBDEV_GetOSDImageEndian(int bpp);

int FBDEV_FlipFBImage(int fb_dev_id, LX_FBDEV_FB_IMAGE_T* fb_screen, BOOLEAN b_free_run);
int FBDEV_UpdateFBScreen(int fb_dev_id, LX_FBDEV_FB_SCREEN_T* fb_screen, BOOLEAN b_free_run);
int FBDEV_SetUserFlipOption(const char* str, int opt);
int FBDEV_GetUserFlipOption(void);
int FBDEV_WaitForRenderEvent(UINT32 timeout);
int FBDEV_set_par(struct fb_info* fbinfo);
int FBDEV_GetConfig(FBDEV_WIN_CTX_T* wctx, LX_FBDEV_CONFIG_T* config);
int FBDEV_SetConfig(FBDEV_WIN_CTX_T* wctx, LX_FBDEV_CONFIG_T* config, BOOLEAN bFlush);
int FBDEV_WaitVSync(int fb_dev_id, int vsync_cnt_on_flip);
void FBDEV_SetInterruptHandler(BOOLEAN enable);
void FBDEV_OpenDRMContext(struct platform_device* pdev, int fb_dev_id);
void FBDEV_CloseDRMContext(int fb_dev_id);
void FBDEV_InitCanvas(FBDEV_WIN_CTX_T* wctx);
int FBDEV_CleanupLayer(FBDEV_WIN_CTX_T* wctx);
int FBDEV_SyncWithVsync(void);
void FBDEV_PreInit(void);
void FBDEV_EventListener(unsigned long evnt_type);
int FBDEV_Init(void);
void FBDEV_Cleanup(void);
void FBDEV_BackupFBList(void);
void FBDEV_RestoreFBList(const char* snap_boot_mode);
void FBDEV_PMTest(const char* cmd);
void FBDEV_ReportPMStatus(struct seq_file* m);
int FBDEV_InitHardware(void);
int FBDEV_ExitHardware(void);
int FBDEV_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl);
int FBDEV_RunResume(void);
int FBDEV_RunSuspend(void);
int FBDEV_ExecHWCommand(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data);
int FBDEV_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl);
int FBDEV_WriteOSDHeader(struct scanvas* hCanvas);
int FBDEV_SetOSDEnable(int layer, int enable);
int FBDEV_GetOSDEnable(int layer);
int FBDEV_GetInterruptStatus(INTERRUPT_INFORM_T intr);
int FBDEV_SetInterruptClear(INTERRUPT_INFORM_T intr);
int FBDEV_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable);
int FBDEV_WriteOSDCSC(int layer, CSC_INFORM_T* csc);
void FBDEV_SetOSDImageEndian(int fb_dev_id, int bpp);
int FBDEV_WriteOSDEndian(int layer, ENDIAN_INFORM_T* endian);
int FBDEV_InitOSDLayer(int layer);
int FBDEV_SetZList(LX_FBDEV_ZLIST_T* zList);
int FBDEV_GetZList(LX_FBDEV_ZLIST_T* zList);
int FBDEV_SetTridCtrl(int layer, LX_FBDEV_TRID_CTRL_T* ctrl);
int FBDEV_SetVideoMixerCtrl(LX_FBDEV_VIDEO_MIXER_CTRL_T* ctrl);
int FBDEV_SetPivotCtrl(LX_FBDEV_PIVOT_CTRL_T* ctrl);
void FBDEV_SetPalette(FBDEV_WIN_CTX_T* w, UINT32* pPalette, int num_pal);
int FBDEV_CaptureControl(UINT32 ctrl);
int FBDEV_WaitCapture(UINT32* fbmem, UINT32* stride, UINT32* width, UINT32* height, UINT32* afbc_mode);
int FBDEV_FBMemHookControl(UINT32 ctrl);
int FBDEV_WaitFBMemHook(UINT32* fbmem, UINT32* stride, UINT32* width, UINT32* height, UINT32* afbc_mode);
void FBDEV_MON_Init(void);
void FBDEV_MON_SetFPSMon(BOOLEAN onoff);
void FBDEV_MON_NotiRefresh(int fb_dev_id);
void FBDEV_MON_ISRTick(void);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
UINT32 g_fbdev_vsync_counter = 0;   // vsync handler counter
UINT32 g_fbdev_isr_chk_counter = 0; // ISR healthy check counter
int g_fbdev_debug_fd = -1;
int g_fbdev_trace_depth = 0;
int g_fbdev_vsync_debug = 1;
FBDEV_FRC_CTRL_T g_fbdev_frc_ctrl;

static int g_fbdev_irq_run_flag = 0;    // isr handler is active ?
static DEFINE_SPINLOCK(g_fbdev_vsync_check_spinlock);   // spinlock for check vsync state
static DECLARE_WAIT_QUEUE_HEAD(g_fbdev_vsync_wq);   // for sync

FBDEV_HW_CTX_T g_fbdev_hw_ctx;

/* default vsync timeout value in usec */
static int g_fbdev_vsync_timeout = FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT;
module_param_named(fbdev_vsync_timeout, g_fbdev_vsync_timeout, int, 0644);

/* if enabled, g_fbdev_vsync_timeout is tuned automatically */
static int g_fbdev_use_vsync_auto_tune = 0;
module_param_named(fbdev_vsync_auto_tune, g_fbdev_use_vsync_auto_tune, int, 0644);

/* multiply vsync-wait timeout for debug/test */
static int g_fbdev_vsync_cnt_on_flip = 1;
module_param_named(fbdev_vsync_cnt_on_flip, g_fbdev_vsync_cnt_on_flip, int, 0644);

/* if enable, unncessary vsync-wait is disabled when image on the front buffer is updated */
static int g_fbdev_use_flip_check = 1;
module_param_named(fbdev_flip_check, g_fbdev_use_flip_check, int, 0644);

/* if enabled, cursor position will be modified by adding the below value */
static int g_fbdev_cursor_x_comp = 0;
static int g_fbdev_cursor_y_comp = 0;
module_param_named(fbdev_cursor_x_comp, g_fbdev_cursor_x_comp, int, 0644);
module_param_named(fbdev_cursor_y_comp, g_fbdev_cursor_y_comp, int, 0644);

/* if enabled, cursor framebuffer is ignored.
 * real HW registers is updated when shape, positon is changed.
 * below variable is experimental feature to prevent image corruption when cursor shape/image is changed frequently.
 *
 * see http://hlm.lge.com/qi/browse/QEVENTSIT-1025 (E60)
 * see http://clm.lge.com/issue/browse/SDOSTC-202 (O22)
 *
 * 과거의 상세한 문제점 분석은 아래 패치셋을 확인하도록 한다.
 * 99b86d767 - (2020-04-02 19:56:23 +0900)  fdbev: disable vsync_wait when E60 cursor image is updated
 */
static int g_fbdev_cursor_ignore_fbmem_update = 0;
module_param_named(fbdev_cursor_ignore_fbmem_update, g_fbdev_cursor_ignore_fbmem_update, int, 0644);

/* if enabled, isr time infor is printed periodically */
int g_fbdev_use_isr_mon = 0;
module_param_named(fbdev_isr_mon, g_fbdev_use_isr_mon, int, 0644);

int g_fbdev_use_boot_debug = 0;
int g_fbdev_use_hw_debug = 0;
int g_fbdev_use_force_flush_on_freeze_exit = 0;

module_param_named(fbdev_use_boot_debug, g_fbdev_use_boot_debug, int, 0644);
module_param_named(fbdev_use_hw_debug, g_fbdev_use_hw_debug, int, 0644);
module_param_named(fbdev_force_flush_on_freeze_exit, g_fbdev_use_force_flush_on_freeze_exit, int, 0644);

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static FBDEV_WIN_CTX_T* FBDEV_InitWinCtx(int fb_dev_id, char* name);
static void FBDEV_InitLinuxFrameBuffer(FBDEV_WIN_CTX_T* wctx, struct fb_var_screeninfo* var, char* id);

static void FBDEV_InitHWCtx(void);
static int FBDEV_open(struct fb_info* info, int user);
static int FBDEV_close(struct fb_info* info, int user);
static int FBDEV_ioctl(struct fb_info* info, unsigned int cmd, unsigned long arg);

static irqreturn_t FBDEV_ISRHandler(int irq, void* dev_id);
static void FBDEV_PseudoISRHandler(ULONG data);

/*----------------------------------------------------------------------------------------
    Platform Device Defnitions
----------------------------------------------------------------------------------------*/
static int /*__init*/ FBDEV_probe(struct platform_device* pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void FBDEV_remove(struct platform_device* pdev);
#else
static int FBDEV_remove(struct platform_device* pdev);
#endif

static void FBDEV_release(struct device* dev);

static int FBDEV_freeze(struct device* dev);
static int FBDEV_thaw(struct device* dev);
static int FBDEV_restore(struct device* dev);
static int FBDEV_suspend(struct device* dev);
static int FBDEV_resume(struct device* dev);
static int FBDEV_runtime_resume(struct device* dev);
static int FBDEV_runtime_suspend(struct device* dev);

static struct platform_device platform_device =
{
    .name = MODULE_NAME,
    .id = 0,
    .id = -1,
    .dev = {
        .coherent_dma_mask = 0xffffffff,
        .release = FBDEV_release,
    },
};

static struct dev_pm_ops fbdev_pm_ops =
{
    .freeze = FBDEV_freeze, // SNAPSHOT suspend
    .thaw = FBDEV_thaw, // SNAPSHOT resume right after making
    .restore_early = FBDEV_restore, // SNAPSHOT boot

    .suspend = FBDEV_suspend,   // IBOOT suspend
    .resume = FBDEV_resume, // IBOOT boot(resume)

    .runtime_suspend = FBDEV_runtime_suspend,
    .runtime_resume = FBDEV_runtime_resume,
};

static struct platform_driver platform_driver =
{
    .probe = FBDEV_probe,
    .remove = FBDEV_remove,
    .driver = {
        .name = MODULE_NAME,
        .pm = &fbdev_pm_ops,
    },
};

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
#ifdef USE_FBDEV_VSYNC_UEVENT
static FBDEV_VSYNC_EVENT_T vsync_ev_ctrl;
static int g_fbdev_vsync_ev_init = 0;
static ssize_t vsync_show_event(struct device* dev, struct device_attribute* attr, char* buf);

static DEVICE_ATTR(vsync_event, S_IRUGO, vsync_show_event, NULL);

static struct attribute* vsync_fs_attrs[] =
{
    &dev_attr_vsync_event.attr,
    NULL,
};

static struct attribute_group vsync_fs_attr_group =
{
    .attrs = vsync_fs_attrs,
};
#endif

#ifdef USE_FBDEV_USER_FLIP_HANDLER
static int g_fbdev_flip_ack_timeout = 100000;   /* 100000 us = 100 ms */
module_param_named(fbdev_flip_ack_timeout, g_fbdev_flip_ack_timeout, int, 0644);

static FBDEV_USER_FLIP_EVENT_T user_flip_ctrl;
static int g_fbdev_user_flip_ev_init = 0;   /* is context initialized */
static ssize_t user_flip_wait_event(struct device* dev, struct device_attribute* attr, char* buf);

static DEVICE_ATTR(user_flip_event, S_IRUGO, user_flip_wait_event, NULL);

static struct attribute* user_flip_fs_attrs[] =
{
    &dev_attr_user_flip_event.attr,
    NULL,
};

static struct attribute_group user_flip_fs_attr_group =
{
    .attrs = user_flip_fs_attrs,
};

#endif

#ifdef USE_FBDEV_CAPTURE
typedef struct
{
    BOOLEAN active;

    OS_SEM_T cap_req_sema;
    OS_SEM_T img_ready_sema;

    struct
    {
        UINT32 mem;
        UINT32 stride;
        UINT32 width;
        UINT32 height;
        UINT32 afbc_mode;
    } fb;
} FBDEV_CAP_CTRL_T;

static int g_cap_ctrl_init = 0;
static FBDEV_CAP_CTRL_T g_cap_ctrl = {.active = FALSE };

#endif

#ifdef USE_FBDEV_FBMEM_HOOK
typedef struct
{
    BOOLEAN active;

    OS_SEM_T cap_req_sema;
    OS_SEM_T img_ready_sema;

    struct
    {
        UINT32 mem;
        UINT32 stride;
        UINT32 width;
        UINT32 height;
        UINT32 afbc_mode;
    } fb;
} FBDEV_FBMEM_HOOK_CTRL_T;

static int g_fbmme_hook_ctrl_init = 0;
static FBDEV_FBMEM_HOOK_CTRL_T g_fbmem_hook_ctrl = {.active = FALSE };
#endif

#ifdef INCLUDE_KDRV_PQE_PM
static int FBDEV_PQE_PM_RuntimeCallback(int action);

struct pqe_pm_config g_pqe_pm_cfg =
{
    .name = MODULE_NAME,
    .opt = PQE_PM_OPT_NONE,
    .order = 0,
    .callback = FBDEV_PQE_PM_RuntimeCallback,
};

static int g_pqe_pm_id = -1;
#endif

static FBDEV_RENDER_EVENT_T render_ev_ctrl;

static FBDEV_CTX_T g_dm_ctx_static;
FBDEV_CTX_T* g_dm_ctx = &g_dm_ctx_static;

static int g_fbdev_use_capture = 0;
static int g_fbdev_use_fbmem_hook = 0;
module_param_named(fbdev_use_capture, g_fbdev_use_capture, int, 0644);
module_param_named(fbdev_use_fbmem_hook, g_fbdev_use_fbmem_hook, int, 0644);

static UINT32 g_afbc_version = FBDEV_HW_AFBC_VER_1_1;

// runtime pm suspend 에 의한 HW clock gating 기능에 의하여, 칩에 따라 vsync interrupt 가 발생하지 않음
// O22 은 15Hz 로 vsync interrupt 생성되나, O24 은 생성되지 않음
// kernel DRM 연계된 이후 clock gating 이후의 osd update 요청시 반드시 vsync ack 를 발생시켜줘야 함
// 따라서 pseudo vsync (sw vsync generator) 를 만들도록 함.
//
// 20ms 단위의 pseudo vsync 는 약 50Hz vsync 를 의미하며, 실제 kdriver 에서는 120Hz 모델 기준으로 25Hz 로
// 처리됨을 기억할것
//
// pseudo vsync 의 시작과 종료는 FBDEV_PQE_PM_RuntimeCallback() 에서 pqe_pm 의 callback 에 의하여 제어됨
// 실제 HW vsync 가 중지/시작되는 싯점과 일치 되도록 해야 함
// 시작: pqe clock gating 직전
// 종료: pqe clock gating 직후
//
// see http://clm.lge.com/issue/browse/SICDTV-12981
// see http://hlm.lge.com/qi/browse/QEVENTTF-5387
// see http://hlm.lge.com/qi/browse/QEVENTTF-5388
//
// see FBDEV_PQE_PM_RuntimeCallback
//
static OS_TIMER_T g_pseudo_vsync_timer;
static int g_pseudo_vsync_tick = 20;
module_param_named(fbdev_pseudo_vsync_tick, g_pseudo_vsync_tick, int, 0644);

static int g_runtime_pm_lazy_suspend_test = 0;
static int g_runtime_pm_lazy_suspend_test_time = 500;
module_param_named(fbdev_runtime_pm_lazy_suspend_test, g_runtime_pm_lazy_suspend_test, int, 0644);
module_param_named(fbdev_runtime_pm_lazy_suspend_test_time, g_runtime_pm_lazy_suspend_test_time, int, 0644);

/*========================================================================================
    Implementation Group
========================================================================================*/
/** update screen !!
 *
 *  @param fb_dev_id [IN] OSD id
 *  @param fb_screen [IN] new screen description
 *  @param b_free_run [IN] if TRUE, OSD doesn't wait for vsync, if FALSE, OSD waits for vsync (default)
 *  @param RET_OK if success, RET_ERROR otherwise
 *
 */
int FBDEV_FlipFBImage(int fb_dev_id, LX_FBDEV_FB_IMAGE_T* fb_screen, BOOLEAN b_free_run)
{
    // TODO: check
    BOOLEAN b_user_initcall = FALSE;
    BOOLEAN b_hdr_update = TRUE;
    BOOLEAN b_vsync_wait = TRUE;
    FBDEV_CTX_T* fbctx = FBDEV_GetCtx();
    FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(fb_dev_id);

    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(&platform_device);

    FBDEV_CHECK_ERROR(NULL == wctx, return RET_ERROR, "invalid layer %d\n", fb_dev_id);
    FBDEV_CHECK_ERROR(NULL == pdev_ctx, return RET_ERROR, "invalid pdev\n");
    FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, return RET_OK, "osd freezed\n");

    FBDEV_DEBUG("fb(%d) BEGIN\n", fb_dev_id);

#ifdef FBDEV_USE_FPS_MON
    FBDEV_MON_NotiRefresh(fb_dev_id);
#endif

    if (g_fbdev_use_flip_check)
    {
        switch (fb_dev_id)
        {
            case LX_FBDEV_ID_OSD1:  /* not graphic. see http://clm.lge.com/issue/browse/AVTASK-640 */
            case LX_FBDEV_ID_OSD3:  /* cursor */
            {
                // (2021/06/28) 커서에 대하여 vsync wait 제거함. 커서 이미지 깨짐에 재한 방어책임
                // g_fbdev_cursor_ignore_fbmem_update 에서 상세한 정보를 참조할것
                b_vsync_wait = FALSE;
            }
            break;

            default:    /* graphic */
            {
                b_vsync_wait = TRUE;
            }
            break;
        }
    }

    /* update OSD header info every screen update
     *
     * @note width & height info is not used !!!
     */
    if (b_hdr_update)
    {
        BOOLEAN osd_hdr_write = TRUE;
        UINT32 curr_bpp = wctx->pixel.bits_per_pixel;

        wctx->pixel.prev_osd_bm_paddr = wctx->pixel.osd_bm_paddr;
        wctx->pixel.osd_bm_paddr = fb_screen->phys_addr;
        wctx->pixel.bits_per_pixel = fb_screen->bits_per_pixel;
        wctx->pixel.stride = fb_screen->stride;
        wctx->pixel.fbc_fmt = fb_screen->fbc_fmt;

        if (fb_screen->pixel_fmt != LX_FBDEV_PIXEL_FORMAT_NOT_DEFINED)
        {
            wctx->pixel.pixel_format = fb_screen->pixel_fmt;
        }

        // (2021/06/28)
        // PQE 에서 clock gating 이 아닌 1/64 freq down 정책을 사용함으로써, slow mode 로 동작하게 된다.
        // 따라서 굳이 위험한(?) 방어 코드, 즉 framebuffer update 무시 체크를 할 필요가 없다.
        //
        // (노트) 혹시 아래 코드를 되살리고자 한다면, first framebuffer 를 통한 OSD HW init 방식과의
        // 충돌이 있음을 명확하게 기억하고 있어야 한다.
        // 참고: http://source.lge.com/dsw/c/DTV/bsp/kdriver/+/137109
        //
        // (노트) freq down 모드에서 늦게 동작하는 IP 의 특성에 의하여 interrupt 가 늦게 뜨는 경우가
        // 있는지 지속 모니터링 할것
#if 0

        if (!pdev_ctx->is_runtime_active)
        {
            FBDEV_PM_DEBUG("<warn> runtime suspend state. ignore framebuffer update\n");
            goto func_exit;
        }

#endif

        wctx->status.fb_flip_cnt++;
        wctx->status.total_fb_flip_cnt++;

        b_user_initcall = (wctx->status.fb_flip_cnt == 1) ? TRUE : FALSE;

        /* for vsync debug */
        if (fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            FBDEV_VSYNC_DEBUG("fb(%d) pan_display paddr=0x%08x\n", fb_dev_id, fb_screen->phys_addr);
        }

        /* (2020/06/11) -- pre processing part of lazy osd init */
        if (b_user_initcall)
        {
            FBDEV_HW_CMD_DATA_T hw_cmd;
            hw_cmd.gen[0] = fb_dev_id;

            FBDEV_NOTI("fb(%d) first flip_update (prepare) !! fmt 0x%x\n", fb_dev_id, wctx->pixel.fbc_fmt);
            (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_USER_INITCALL_PREPARE, &hw_cmd);
        }

        // (2020/11/02)
        // update OSD header only when the current time is in the "real" vsync time range.
        // in other words, wait for enough time to skip OSD update during the "fake" vsync time range.
        // the heuristic maximum wait time is 20ms (5 ms * vsync_cnt_on_flip * 2)
        //
        // check the fake vsync only when vsync_cnt_on_flip is greater than 1.
        // as you know, vsync_cnt_on_flip is vsync sw divider and value 2 makes 60Hz handler (120Hz/2=60Hz)
        //
        // see FBDEV_SyncWithVsync();
        // see http://hlm.lge.com/issue/browse/NATIVEAPP-7621
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0 && !b_free_run && g_fbdev_vsync_cnt_on_flip > 1)
        {
            int i;

            for (i = g_fbdev_vsync_cnt_on_flip * 2; i > 0; i--)
            {
                ULONG flags;
                int wait_real_vsync = 0;

                spin_lock_irqsave(&g_fbdev_vsync_check_spinlock, flags);
                wait_real_vsync = ((g_fbdev_vsync_counter + 1) % g_fbdev_vsync_cnt_on_flip) ? 1 : 0;
                spin_unlock_irqrestore(&g_fbdev_vsync_check_spinlock, flags);

                if (!wait_real_vsync)
                {
                    break;
                }

                FBDEV_VSYNC_DEBUG("fb(%d) skip fake vsync\n", fb_dev_id);
                usleep_range(5000, 5000);   /* 5ms */
            }

            FBDEV_VSYNC_DEBUG("fb(%d) run  real vsync\n", fb_dev_id);
        }

        if (curr_bpp != fb_screen->bits_per_pixel)
        {
            FBDEV_SetOSDImageEndian(fb_dev_id, fb_screen->bits_per_pixel);
        }

        // (2021/06/28) g_fbdev_cursor_ignore_fbmem_update 참조
        if (g_fbdev_cursor_ignore_fbmem_update && fb_dev_id == LX_FBDEV_ID_OSD3)
        {
            osd_hdr_write = FALSE;
        }

        if (osd_hdr_write)
        {
            FBDEV_WriteOSDHeader(&wctx->pixel);
        }
    }

    /* notify render event except cursor */
    if (fb_dev_id != LX_FBDEV_ID_OSD3 && render_ev_ctrl.wait_cnt > 0)
    {
        complete_all(&render_ev_ctrl.event);
        render_ev_ctrl.wait_cnt = 0;
    }

    /* raxis.lim (2012/06/14) -- fbdev supports freerun mode (non-vsync) */
    if (b_vsync_wait == TRUE && wctx->status.b_osd_hdr_write == TRUE && b_free_run == FALSE)
    {
        FBDEV_WaitVSync(fb_dev_id, wctx->vsync_cnt_on_flip);
    }

    if (b_hdr_update)
    {
        /* (2020/06/11) -- post processing part of lazy osd init */
        if (b_user_initcall)
        {
            FBDEV_HW_CMD_DATA_T hw_cmd;
            hw_cmd.gen[0] = fb_dev_id;

            FBDEV_NOTI("fb(%d) first flip_update (complete) !! fmt 0x%x\n", fb_dev_id, wctx->pixel.fbc_fmt);
            (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE, &hw_cmd);
        }
    }

#if 0
func_exit:
#endif
    FBDEV_DEBUG("fb(%d) END\n", fb_dev_id);

    return RET_OK;
}

int FBDEV_UpdateFBScreen(int fb_dev_id, LX_FBDEV_FB_SCREEN_T* fb_screen, BOOLEAN b_free_run)
{
    FBDEV_CTX_T* fbctx = FBDEV_GetCtx();
    FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(fb_dev_id);

    FBDEV_CHECK_ERROR(NULL == wctx, return RET_ERROR, "invalid layer %d\n", fb_dev_id);
    FBDEV_CHECK_ERROR(LX_FBDEV_SCREEN_OPMASK_NONE == fb_screen->opmask, return RET_ERROR, "invalid opmask : 0x0\n");

    FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, return RET_OK, "osd freezed\n");

    /* disable osd header during processing 3D OSD and layer control */
    wctx->status.b_osd_hdr_write = FALSE;

    if (fb_screen->opmask & LX_FBDEV_SCREEN_OPMASK_LAYER_CTRL)
    {
        FBDEV_SetConfig(wctx, &fb_screen->layer_ctrl, TRUE);
    }

    if (fb_screen->opmask & LX_FBDEV_SCREEN_OPMASK_TRID_CTRL)
    {
        FBDEV_SetTridCtrl(fb_dev_id, &fb_screen->trid_ctrl);
    }

    /* reenable osd header before updating fb image */
    wctx->status.b_osd_hdr_write = TRUE;

    if (fb_screen->opmask & LX_FBDEV_SCREEN_OPMASK_IMG_CTRL)
    {
        FBDEV_FlipFBImage(fb_dev_id, &fb_screen->img_ctrl, b_free_run);
    }
    else
    {
        FBDEV_WriteOSDHeader(&wctx->pixel);
    }

    return RET_OK;
}

#ifdef USE_FBDEV_USER_FLIP_HANDLER
/** wait for user flip done
 *
 */
static ssize_t user_flip_wait_event(struct device* dev, struct device_attribute* attr, char* buf)
{
    ULONG flags;
    int ret = RET_ERROR;

    FBDEV_USER_FLIP_DEBUG("<kdrv> user_flip_ctrl - waiting next pan_display...\n");

    if (user_flip_ctrl.enabled) // && user_flip_ctrl.user_pid == current->pid)
    {
        ret = wait_for_completion_interruptible(&user_flip_ctrl.user_event);

        /* make ready to get next user_event */
        spin_lock_irqsave(&user_flip_ctrl.spinlock, flags);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,13,0))
        reinit_completion(&user_flip_ctrl.user_event);
#else
        INIT_COMPLETION(user_flip_ctrl.user_event);
#endif
        spin_unlock_irqrestore(&user_flip_ctrl.spinlock, flags);

        /* -ERESTARTSYS (-512) happens when user process is going to be freezed. kernel will call this again automatically, don't worry */
        FBDEV_CHECK_ERROR(ret != RET_OK, goto func_exit, "user_flip.user_event wait error. ret=%d\n", ret);

        ret = snprintf(buf, PAGE_SIZE, "0x%08x %d %d %d %d %d 0x%08x", user_flip_ctrl.fbmem.paddr, user_flip_ctrl.fbmem.stride,
                       user_flip_ctrl.fbmem.width, user_flip_ctrl.fbmem.height, user_flip_ctrl.fbmem.afbc_mode,
                       user_flip_ctrl.fbmem.session_no,   // for sync between kdriver and user processs
                       user_flip_ctrl.opt); // for multiple flip options
        buf[strlen(buf) + 1] = '\0';
    }

    FBDEV_USER_FLIP_DEBUG
    ("<kdrv> user_flip_ctrl(%04d) - pan_dispay event received. buf=(%s)\n", user_flip_ctrl.fbmem.session_no,
     buf);

func_exit:
    return ret;
}

/** set new flip option
 *
 */
int FBDEV_SetUserFlipOption(const char* str, int opt)
{
    ULONG flags;

    FBDEV_NOTI("<kdrv> user_flip_option = 0x%08x (%s)\n", opt, str);

    spin_lock_irqsave(&user_flip_ctrl.spinlock, flags);
    user_flip_ctrl.opt = opt;
    spin_unlock_irqrestore(&user_flip_ctrl.spinlock, flags);

    return RET_OK;
}

int FBDEV_GetUserFlipOption(void)
{
    return user_flip_ctrl.opt;
}
#endif

int FBDEV_WaitForRenderEvent(UINT32 timeout)
{
    int ret;

    if (render_ev_ctrl.wait_cnt == 0)
    {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,13,0))
        reinit_completion(&render_ev_ctrl.event);
#else
        INIT_COMPLETION(render_ev_ctrl.event);
#endif
    }

    render_ev_ctrl.wait_cnt++;

    if (timeout > 0)
    {
        ret = wait_for_completion_interruptible_timeout(&render_ev_ctrl.event, msecs_to_jiffies(timeout));
        ret = (ret > 0) ? RET_OK : RET_TIMEOUT;
    }
    else
    {
        ret = wait_for_completion_interruptible(&render_ev_ctrl.event);
        FBDEV_CHECK_ERROR(ret != RET_OK, /* nop */,
                          "event wait error. ret=%d\n", ret);
    }

    return ret;
}

/*========================================================================================
    Implementation Group ( Linux FrameBuffer interface )
========================================================================================*/
#ifndef MODULE
/* only necessary if your driver takes special options, */
int __init FBDEV_setup(char* options)
{
    /* Parse user speficied options (`video=l8fb:') */
    return RET_OK;
}
#endif

static int FBDEV_pan_display(struct fb_var_screeninfo* var, struct fb_info* fbinfo)
{
    int rc = 0;

    LX_FBDEV_CFG_T* cfg = FBDEV_GET_CFG();
    FBDEV_CTX_T* fbctx = FBDEV_GetCtx();
    FBDEV_WIN_CTX_T* wctx = (FBDEV_WIN_CTX_T*) fbinfo->par;
    int fb_dev_id = wctx->fb_dev_id;
    BOOLEAN afbc_image = FALSE;
    UINT32 start = 0;
    int fb_bufnum = cfg->fb[fb_dev_id].max_buf_num;
    int buf_idx = 0;

    /* confirm the write sync before further display */
    wmb();

    /* support pan_display only OSD driver is configured to LinuxFB */
    FBDEV_CHECK_ERROR(FALSE == wctx->linux_fb_mode, return RET_ERROR, "fb(%d) LinuxFB disabled..\n", fb_dev_id);
    FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, return RET_OK, "osd freezed\n");

#ifdef FBDEV_FLIP_LOCK
    OS_LockMutex(&wctx->fb_dev_mtx);
#endif

    /* record pan_display counter */
    wctx->status.fb_pan_disp_cnt++;

    // support direct render request to external renderer (O20+F20 case)
    // (2020/09/04) add yoffset. see http://hlm.lge.com/issue/browse/WEBOSHWBS-429
    // (2021/07/05) O22 8K 는 이 path 를 타지 않는다. 즉 GPU libs 에서 post processing 하지 않으며,
    // OSD chip kdriver 에서 post processing 을 진행한다. see http://clm.lge.com/issue/browse/AVTASK-640
    if (fb_dev_id == LX_FBDEV_ID_OSD1 && var->reserved[0])
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;

        hw_cmd.gen[0] = fb_dev_id;
        hw_cmd.gen[1] = var->reserved[0];
        hw_cmd.gen[2] = wctx->pixel.output_win.x;
        hw_cmd.gen[3] = wctx->pixel.output_win.y;

        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE, &hw_cmd);

        goto func_exit;
    }

    afbc_image = (var->accel_flags == FB_ACCELF_LG_AFBC) ? TRUE : FALSE;

#if 1
    /* support general N buffer */
    buf_idx = var->yoffset / fbinfo->var.yres;
    start = (UINT32) fbinfo->fix.smem_start + fbinfo->fix.smem_len * buf_idx / fb_bufnum;
#else

    if (var->yoffset > 0)
    {
        start = (UINT32) fbinfo->fix.smem_start + fbinfo->fix.smem_len / 2;
    }
    else
    {
        start = (UINT32) fbinfo->fix.smem_start;
    }

#endif

    FBDEV_LINUXFB_DEBUG
    ("fb(%d), afbc %d, yoff %d, xoff %d, stride %d, coffs %d/%d/%d/%d, smem_start 0x%08x, fbmem 0x%08x (+0x%08x)\n",
     fb_dev_id, afbc_image, var->yoffset, var->xoffset, fbinfo->fix.line_length,
     var->red.offset, var->green.offset, var->blue.offset, var->transp.offset,
     (UINT32) fbinfo->fix.smem_start, (UINT32) start, (UINT32) start - (UINT32) fbinfo->fix.smem_start);

    /* make flip image struct */
    {
        BOOLEAN b_free_run = FALSE;
        LX_FBDEV_FB_IMAGE_T fb_screen;

        memset(&fb_screen, 0x0, sizeof(LX_FBDEV_FB_IMAGE_T));

        fb_screen.fbc_fmt = (afbc_image) ? LX_FBDEV_FBC_FORMAT_AFBC : LX_FBDEV_FBC_FORMAT_RAW;
        fb_screen.phys_addr = start;
        fb_screen.stride = fbinfo->fix.line_length; //wctx->pixel.stride;
        fb_screen.bits_per_pixel = fbinfo->var.bits_per_pixel;

        if (var->red.offset == 0 && var->green.offset == 8 && var->blue.offset == 16
                && var->transp.offset == 24)
        {
            fb_screen.pixel_fmt = LX_FBDEV_PIXEL_FORMAT_BGR_8888;
        }
        else
        {
            fb_screen.pixel_fmt = LX_FBDEV_PIXEL_FORMAT_RGB_8888;
        }

        /* raxis.lim (2012/06/14) -- support non-vsync application */
        b_free_run = (var->sync == (UINT32) - 1) ? TRUE : FALSE;

#ifdef USE_FBDEV_CAPTURE

        if (g_fbdev_use_capture && g_cap_ctrl.active && fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            /* make kdriver to wait for a while unitil user app is ready for capture */
            FBDEV_ETC_DEBUG("server - waiting for capture request\n");

            FBDEV_CHECK_ERROR(RET_OK != OS_WaitMutex(&g_cap_ctrl.cap_req_sema), /*nop */,
                              "lock failed\n");

            g_cap_ctrl.fb.mem = fb_screen.phys_addr;
            g_cap_ctrl.fb.stride = fb_screen.stride;
            g_cap_ctrl.fb.width = g_fbdev_cfg->fb[0].max_xres;
            g_cap_ctrl.fb.height = g_fbdev_cfg->fb[0].max_xres;
            g_cap_ctrl.fb.afbc_mode = (afbc_image) ? 1 : 0;;

            /* make user app to get new image */
            FBDEV_ETC_DEBUG("server - notify image ready\n");
            OS_PostMutex(&g_cap_ctrl.img_ready_sema);
        }

#endif

#ifdef USE_FBDEV_FBMEM_HOOK

        if (g_fbdev_use_fbmem_hook && g_fbmem_hook_ctrl.active && fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            /* make kdriver to wait for a while unitil user app is ready for capture */
            FBDEV_ETC_DEBUG("server - waiting for capture request\n");
            FBDEV_CHECK_ERROR(RET_OK != OS_WaitMutex(&g_fbmem_hook_ctrl.cap_req_sema),
                              /*nop */,
                              "lock failed\n");

            g_fbmem_hook_ctrl.fb.mem = fb_screen.phys_addr;
            g_fbmem_hook_ctrl.fb.stride = fb_screen.stride;
            g_fbmem_hook_ctrl.fb.width = g_fbdev_cfg->fb[0].max_xres;
            g_fbmem_hook_ctrl.fb.height = g_fbdev_cfg->fb[0].max_yres;
            g_fbmem_hook_ctrl.fb.afbc_mode = (afbc_image) ? 1 : 0;;

            /* make user app to get new image */
            FBDEV_ETC_DEBUG("server - notify image ready\n");
            OS_PostMutex(&g_fbmem_hook_ctrl.img_ready_sema);

            /* skip image update because user-level composer task will do it */
            goto func_exit;
        }

#endif

#ifdef USE_FBDEV_USER_FLIP_HANDLER

        if (fb_dev_id == LX_FBDEV_ID_OSD0 && user_flip_ctrl.enabled)
        {
            ULONG flags;
            ULONG tmo;
            int ret = RET_OK;   /* default ok */
            static UINT32 session_no = 0;   /* simple incremental counter */

            spin_lock_irqsave(&user_flip_ctrl.spinlock, flags);
            ++session_no;

            FBDEV_USER_FLIP_DEBUG
            ("<kdrv> user_flip_ctrl(%04d) - pan_display request by app pid(%d)\n", session_no,
             (int)current->pid);
            user_flip_ctrl.fbmem.paddr = fb_screen.phys_addr;
            user_flip_ctrl.fbmem.stride = fb_screen.stride;
            user_flip_ctrl.fbmem.width = g_fbdev_cfg->fb[fb_dev_id].max_xres;
            user_flip_ctrl.fbmem.height = g_fbdev_cfg->fb[fb_dev_id].max_yres;
            user_flip_ctrl.fbmem.afbc_mode = (afbc_image) ? 1 : 0;;
            user_flip_ctrl.fbmem.session_no = session_no;

            // notify user process to wake up to catch pan_display
            FBDEV_USER_FLIP_DEBUG
            ("<kdrv> user_flip_ctrl(%04d) - wake up user_event. paddr=0x%08x, size=%dx%d, fmt=%s\n",
             user_flip_ctrl.fbmem.session_no,
             user_flip_ctrl.fbmem.paddr,
             user_flip_ctrl.fbmem.width, user_flip_ctrl.fbmem.height,
             (user_flip_ctrl.fbmem.afbc_mode) ? "afbc" : "argb");

            complete_all(&user_flip_ctrl.user_event);

            /* make ready to get next ack_event */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,13,0))
            reinit_completion(&user_flip_ctrl.ack_event);
#else
            INIT_COMPLETION(user_flip_ctrl.ack_event);
#endif
            spin_unlock_irqrestore(&user_flip_ctrl.spinlock, flags);

            // wait ack from user process to continue OSD display with user modified framebuffer
            // to prevent stall state, wait a while with 1~2 vsync timeout
            // if timeout happens, disconects current process to prevent stall state
            //
            //
            // (2020/10/19)
            // increase timeout from 16.7ms to more than 30ms
            // according to test result, it takes about 30ms for user process to make the initial image.
            //
            tmo =
                wait_for_completion_interruptible_timeout
                (&user_flip_ctrl.ack_event, usecs_to_jiffies(g_fbdev_flip_ack_timeout));
            FBDEV_CHECK_ERROR(tmo == 0, ret =
                                  RET_TIMEOUT,
                              "user_flip_ctrl(%04d) ack_event timeout error. ret=%d\n",
                              user_flip_ctrl.fbmem.session_no, ret);

            //ret = wait_for_completion_interruptible(&user_flip_ctrl.ack_event);
            //FBDEV_CHECK_ERROR(ret != RET_OK, /* nop */, "user_flip_ctrl(%04d) ack_event wait error. ret=%d\n",
            //              user_flip_ctrl.fbmem.session_no, ret);

            FBDEV_USER_FLIP_DEBUG
            ("<kdrv> user_flip_ctrl(%04d) - ack_event received. ret=%d\n",
             user_flip_ctrl.fbmem.session_no, ret);

            if (ret == RET_OK)
            {
                fb_screen.fbc_fmt =
                    (user_flip_ctrl.
                     fbmem.afbc_mode) ? LX_FBDEV_FBC_FORMAT_AFBC : LX_FBDEV_FBC_FORMAT_RAW;
                fb_screen.phys_addr = user_flip_ctrl.fbmem.paddr;
                fb_screen.stride = fbinfo->fix.line_length; //wctx->pixel.stride;
                fb_screen.bits_per_pixel = fbinfo->var.bits_per_pixel;
            }
            else
            {
                spin_lock_irqsave(&user_flip_ctrl.spinlock, flags);
                user_flip_ctrl.enabled = false;
                user_flip_ctrl.user_pid = -1;
                spin_unlock_irqrestore(&user_flip_ctrl.spinlock, flags);

                FBDEV_ERROR("<kdrv> user_flip disconnected due to ack_event error\n");

                /* go on, keep current pan_display request */
            }

            FBDEV_USER_FLIP_DEBUG("<kdrv> user_flip_ctrl(%04d) - screen updating...\n",
                                  user_flip_ctrl.fbmem.session_no);
        }

#endif              /* USE_FBDEV_USER_FLIP_HANDLER */

        rc = FBDEV_FlipFBImage(fb_dev_id, &fb_screen, b_free_run);

        if (fb_dev_id == LX_FBDEV_ID_OSD0 && user_flip_ctrl.enabled)
        {
            FBDEV_USER_FLIP_DEBUG
            ("<kdrv> user_flip_ctrl(%04d) - screen update completed\n\n",
             user_flip_ctrl.fbmem.session_no);
        }
    }

    FBDEV_CHECK_ERROR(RET_OK != rc, /* go */,
                      "[fb%d] error during update_screen\n", fb_dev_id);

func_exit:
#ifdef FBDEV_FLIP_LOCK
    OS_UnlockMutex(&wctx->fb_dev_mtx);
#endif

    return rc;
}

/** module mmap function.
 *
 * @param   int blank ,struct fb_info *info
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_mmap(struct fb_info* fbinfo, struct vm_area_struct* vma)
{
    FBDEV_WIN_CTX_T* wctx = (FBDEV_WIN_CTX_T*) fbinfo->par;
    int fb_dev_id = wctx->fb_dev_id;
    ULONG start;
    ULONG len;
    ULONG off = (vma->vm_pgoff << PAGE_SHIFT);
    ULONG size = vma->vm_end - vma->vm_start;
    int ret = -1;

    /* support mmap only when OSD contains internal FB memory */
    FBDEV_CHECK_ERROR(FALSE == wctx->linux_fb_mode, return RET_ERROR, "fb(%d) LinuxFB disabled..\n", fb_dev_id);
    FBDEV_DEBUG("fb(%d)::FBDEV_mmap\n", fb_dev_id);

    start = wctx->fb_base_phys;
    len = PAGE_ALIGN((start & ~PAGE_MASK) + wctx->fb_size);

    if ((vma->vm_end - vma->vm_start + off) > len)
    {
        return -EINVAL;
    }

    off += start & PAGE_MASK;
    vma->vm_pgoff = off >> PAGE_SHIFT;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
    vm_flags_set(vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0))
    vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
#else
    vma->vm_flags |= VM_RESERVED;
#endif
    /* raxis.lim (2018/07/11) SDMSTG-488
     * pgprot_noncached -> pgprot_writecombine
     * change pgprot function to support non-aligned access to mmapped memory
     */
    vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
    ret = remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT, size, vma->vm_page_prot);

    FBDEV_LINUXFB_DEBUG("fb(%d) paddr 0x%08x off %d, size %d \n", fb_dev_id,
                        (UINT32) start, (UINT32) off, (UINT32) size);

    return ret;
}

static int FBDEV_check_var(struct fb_var_screeninfo* var, struct fb_info* fbinfo)
{
    const FBDEV_WIN_CTX_T* wctx = (const FBDEV_WIN_CTX_T*)fbinfo->par;
    int fb_dev_id = wctx->fb_dev_id;
    UINT32 xres, yres, xres_virt, yres_virt;

    FBDEV_CHECK_ERROR(FALSE == wctx->linux_fb_mode, return RET_ERROR, "fb(%d) LinuxFB disabled\n", fb_dev_id);
    FBDEV_DEBUG("fb(%d)::FBDEV_check_var\n", fb_dev_id);

    FBDEV_CHECK_ERROR(var->bits_per_pixel != 32, return RET_ERROR,
                      "fb(%d) %d bpp not supported\n", fb_dev_id, var->bits_per_pixel);

    /* just check for input size not to be greater than physical max size.
     * for the safe operation, x coordinate should be aligned by 8 byte ( OSD WORD unit )
     */
    xres = ALIGN(var->xres, 8);
    yres = var->yres;
    xres_virt = ALIGN(var->xres_virtual, 8);
    yres_virt = var->yres_virtual;

    if (xres > g_fbdev_cfg->fb[fb_dev_id].max_xres)
    {
        xres = g_fbdev_cfg->fb[fb_dev_id].max_xres;
    }

    if (yres > g_fbdev_cfg->fb[fb_dev_id].max_yres)
    {
        yres = g_fbdev_cfg->fb[fb_dev_id].max_yres;
    }

    if (xres_virt > g_fbdev_cfg->fb[fb_dev_id].max_xres)
    {
        xres_virt = g_fbdev_cfg->fb[fb_dev_id].max_xres;
    }

    /* input size should not be greater than virtual screen size */
    if (xres > xres_virt)
    {
        xres_virt = xres;
    }

    if (yres > yres_virt)
    {
        yres_virt = yres;
    }

    var->xres = xres;
    var->yres = yres;
    var->xres_virtual = xres_virt;
    var->yres_virtual = yres_virt;

    FBDEV_LINUXFB_DEBUG
    ("fb(%d) xres %d, yres %d, xres_virt %d, yres_virt %d\n", fb_dev_id, xres, yres, xres_virt, yres_virt);

    return RET_OK;
}

static int FBDEV_setcmap(struct fb_cmap* cmap, struct fb_info* info)
{
    FBDEV_LINUXFB_DEBUG("not supported\n");
    return RET_OK;
}

int FBDEV_set_par(struct fb_info* fbinfo)
{
    FBDEV_LINUXFB_DEBUG("not supported\n");
    return RET_OK;
}

static int FBDEV_blank(int blank, struct fb_info* info)
{
    FBDEV_LINUXFB_DEBUG("not supported\n");
    return RET_OK;
}

static struct fb_ops lg115x_fbdev_fops =
{
    .owner = THIS_MODULE,
    .fb_open = FBDEV_open,
    .fb_release = FBDEV_close,
    .fb_check_var = FBDEV_check_var,
    .fb_set_par = FBDEV_set_par,
    //      .fb_setcolreg   = FBDEV_setcolreg,
    .fb_pan_display = FBDEV_pan_display,
#ifdef CONFIG_FB_CFB_FILLRECT
    .fb_fillrect = cfb_fillrect,
#endif
#ifdef CONFIG_FB_CFB_COPYAREA
    .fb_copyarea = cfb_copyarea,
#endif
#ifdef CONFIG_FB_CFB_IMAGEBLIT
    .fb_imageblit = cfb_imageblit,
#endif
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    .fb_rotate = NULL,
#endif
    .fb_sync = NULL,
    .fb_mmap = FBDEV_mmap,
    .fb_blank = FBDEV_blank,
    .fb_ioctl = FBDEV_ioctl,
#ifdef CONFIG_COMPAT
    .fb_compat_ioctl = FBDEV_ioctl,
#endif
    .fb_setcmap = FBDEV_setcmap,
};

/*========================================================================================
    Implementation Group ( FB(OSD) native interface )
========================================================================================*/

/** Get the image configration ( ioctl interface )
 *
 * @param win [IN] osd plane information
 * @param config [OUT] image configuration
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_GetConfig(FBDEV_WIN_CTX_T* wctx, LX_FBDEV_CONFIG_T* config)
{
    int ret = 0;

    memcpy(&config->input_win, &wctx->pixel.input_win, sizeof(LX_RECT_T));
    memcpy(&config->output_win, &wctx->pixel.output_win, sizeof(LX_RECT_T));

    config->global_alpha_enable = wctx->pixel.global_alpha_en;
    config->blend_alpha_enable = wctx->pixel.blend_alpha_en;
    config->color_key_enable = wctx->pixel.color_key_en;
    config->reverse_screen_enable = wctx->pixel.reserver_screen_en;

    config->global_alpha = wctx->pixel.global_alpha;
    config->blend_alpha = wctx->pixel.blend_alpha;
    config->color_key = wctx->pixel.color_key;
    config->vsync_enable = wctx->status.b_use_vsync;

    config->fbinfo.xres = wctx->linux_fb_info.var.xres;
    config->fbinfo.yres = wctx->linux_fb_info.var.yres;
    config->fbinfo.xres_virtual = wctx->linux_fb_info.var.xres_virtual;
    config->fbinfo.yres_virtual = wctx->linux_fb_info.var.yres_virtual;
    config->fbinfo.bits_per_pixel = wctx->linux_fb_info.var.bits_per_pixel;

    return ret;
}

/** Set the image configration ( ioctl interface )
 *
 * @param   win [IN] osd plane information
 * @param   config [IN image configuration
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_SetConfig(FBDEV_WIN_CTX_T* wctx, LX_FBDEV_CONFIG_T* config, BOOLEAN bFlush)
{
    int ret = 0;
    FBDEV_CTX_T* fbctx = FBDEV_GetCtx();

    FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, return RET_OK, "osd freezed\n");

#ifdef FBDEV_FLIP_LOCK
    OS_LockMutex(&wctx->fb_dev_mtx);
#endif

    /* raxis.lim (2011/11/22) -- DO NOT change the FB information. !!! */
    //      wctx->fbinfo.var.xres                   = config->fbinfo.xres;
    //      wctx->fbinfo.var.yres                   = config->fbinfo.yres;
    //      wctx->fbinfo.var.xres_virtual   = config->fbinfo.xres_virtual;
    //      wctx->fbinfo.var.yres_virtual   = config->fbinfo.yres_virtual;
    //      wctx->fbinfo.var.bits_per_pixel= config->fbinfo.bits_per_pixel;

    wctx->status.b_use_vsync = config->vsync_enable;

#if 0

    /* raxis.lim (2012/06/20) -- process reverse mode change */
    if (wctx->pixel.reserver_screen_en != config->reverse_screen_enable)
    {
        FBDEV_HW_EVENT_DATA_T evdata;

        memset(&evdata, 0x0, sizeof(FBDEV_HW_EVENT_DATA_T));
        evdata.reverse_screen_change.fb_dev_id = wctx->fb_dev_id;
        evdata.reverse_screen_change.enable = config->reverse_screen_enable;

        FBDEV_ExecFBHWHandler(FBDEV_HW_EVENT_REVERSE_SCREEN_CHANGE, &evdata);

        wctx->pixel.reserver_screen_en = config->reverse_screen_enable;
    }

#endif

    /* raxis.lim (2012/01/27) -- update OSD header only value is changed.
     * without this protection, OSD may flicker when multiple application tries to call FBDEV_WriteOSDHeader
     */
    if (wctx->pixel.global_alpha != config->global_alpha ||
            wctx->pixel.global_alpha_en != config->global_alpha_enable ||
            wctx->pixel.blend_alpha != config->blend_alpha ||
            wctx->pixel.blend_alpha_en != config->blend_alpha_enable ||
            wctx->pixel.color_key_en != config->color_key_enable ||
            wctx->pixel.color_key != config->color_key ||
            memcmp(&wctx->pixel.input_win, &config->input_win,
                   sizeof(LX_RECT_T)) || memcmp(&wctx->pixel.output_win, &config->output_win, sizeof(LX_RECT_T)))
    {
        /* raxis.lim (2012/01/10) -- some platform should support pseudo global alpha level for POSD */
        wctx->pixel.global_alpha = config->global_alpha;
        wctx->pixel.global_alpha_en = config->global_alpha_enable;
        wctx->pixel.blend_alpha = config->blend_alpha;
        wctx->pixel.blend_alpha_en = config->blend_alpha_enable;
        wctx->pixel.reserver_screen_en = config->reverse_screen_enable;

        /* raxis.lim (2013/02/05) -- support color key */
        wctx->pixel.color_key = config->color_key;
        wctx->pixel.color_key_en = config->color_key_enable;

        /* raxis.lim (2018/04/06) -- support user output window control.
         *
         * if application set its own output window size which different from the HW default,
         * output window size is controlled by application not kdriver.
         */
        if (memcmp(&wctx->pixel.output_win, &config->output_win, sizeof(LX_RECT_T)))
        {
            FBDEV_HW_CMD_DATA_T hw_cmd;

            wctx->pixel.user_win_ctrl_en = TRUE;

            hw_cmd.gen[0] = wctx->fb_dev_id;
            (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_USER_POSD_RESOL_CHANGED, &hw_cmd);
        }

        /* if input & output window changed, update osd header again.
         * [note] wctx->pixel.osd_bm_paddr should be updated after changing input_win.
         *                the simplest way to update this value is to call pan_display again.
         */
        memcpy(&wctx->pixel.input_win, &config->input_win, sizeof(LX_RECT_T));
        memcpy(&wctx->pixel.output_win, &config->output_win, sizeof(LX_RECT_T));

        if (bFlush)
        {
            FBDEV_WriteOSDHeader(&wctx->pixel);
#if 0
            FBDEV_WaitVSync(wctx->fb_dev_id, wctx->vsync_cnt_on_flip);
#endif
        }
    }

#ifdef FBDEV_FLIP_LOCK
    OS_UnlockMutex(&wctx->fb_dev_mtx);
#endif
    //FBDEV_NOTI("fb(%d) <end>\n", wctx->fb_dev_id );
    return ret;
}

/** wait for vsync
 *
 *
 *
 */
int FBDEV_WaitVSync(int fb_dev_id, int vsync_cnt_on_flip)
{
    UINT32 vsync_usec_tmout;
    int rc = RET_OK;
    FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(fb_dev_id);

    FBDEV_CHECK_ERROR(NULL == wctx, return RET_ERROR, "invalid layer %d\n", fb_dev_id);

    /* if application don't want to wait for the vsync, return function !! */
    if (vsync_cnt_on_flip == 0)
    {
        return RET_OK;
    }

    /* if the default vsync_cnt is requested, I will wait for one vsync.... */
    if (vsync_cnt_on_flip < 0)
    {
        vsync_cnt_on_flip = 1;
    }

    /* calculate the current vsync timeout */
    vsync_usec_tmout = g_fbdev_vsync_timeout * g_fbdev_vsync_cnt_on_flip;

    /* this function is valid only when vsync_wait is enabled */
    if (g_fbdev_cfg->b_use_irq && wctx->status.b_use_vsync)
    {
        ULONG flags;

        spin_lock_irqsave(&g_fbdev_vsync_check_spinlock, flags);
        wctx->vsync_cnt = vsync_cnt_on_flip;
        spin_unlock_irqrestore(&g_fbdev_vsync_check_spinlock, flags);

        rc = wait_event_interruptible_timeout(g_fbdev_vsync_wq,
                                              wctx->vsync_cnt == 0, usecs_to_jiffies(vsync_usec_tmout));

        if (g_fbdev_vsync_debug)
        {
            FBDEV_CHECK_ERROR(rc == 0 && wctx->vsync_cnt, /* nop */,
                              "FB[%d] vsync timeout. HZ=%d, jf=%d, wcnt=%d \n",
                              fb_dev_id, HZ, (UINT32) usecs_to_jiffies(vsync_usec_tmout), wctx->vsync_cnt);
            FBDEV_CHECK_ERROR(rc < 0, /* nop */,
                              "FB[%d] vsync abort by signal !!!!\n", fb_dev_id);
        }

        /* for vsync debug */
        if (rc > 0 && fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            FBDEV_VSYNC_DEBUG("fb(%d) vsync wait done\n", fb_dev_id);
        }
    }

    return RET_OK;
}

/* Support for gpu ddk.
 * Defined in gpuddk, egl/src/winsys/linux/mali_egl_winsys_fbdev.h
 */
#define FBIOGET_DMABUF _IOR('F', 0x21, struct fb_dmabuf_export)
struct fb_dmabuf_export
{
    uint32_t fd;
    uint32_t flags;
};

static int fbdev_get_dmabuf(FBDEV_WIN_CTX_T* wctx, unsigned long arg)
{
    struct fb_dmabuf_export _dmabuf = { };
    struct dma_buf* dma_buf;
    int ret;

    _dmabuf.fd = hma_dmabuf("fbdev", wctx->fb_base_phys, wctx->fb_size);

    if (_dmabuf.fd < 0)
    {
        FBDEV_ERROR("couldn't get fd from dma_buf\n");
        return _dmabuf.fd;
    }

    ret = copy_to_user((void*)arg, &_dmabuf, sizeof(_dmabuf));

    if (ret > 0)
    {
        struct dma_buf* dmabuf;

        FBDEV_ERROR("copy_to_user() failed.\n");
        dmabuf = dma_buf_get(_dmabuf.fd);
        dma_buf_put(dma_buf);
        dma_buf_put(dma_buf);
        return -EFAULT;
    }

    return 0;
}

/*========================================================================================
    Implementation Group (Ioctl Handler)
========================================================================================*/
/** module ioctl.
 *
 * @param   struct fb_info *info,  unsigned int cmd , unsigned long arg
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_ioctl(struct fb_info* info, unsigned int cmd, unsigned long arg)
{
    int rc;
    int ret = RET_ERROR;    /* return status of ioctl handler */

    FBDEV_CTX_T* fbctx = FBDEV_GetCtx();
    FBDEV_WIN_CTX_T* wctx = (FBDEV_WIN_CTX_T*) info->par;
    int fb_dev_id = wctx->fb_dev_id;

    FBDEV_CHECK_DEBUG(!g_fbdev_cfg->fb[fb_dev_id].b_active, /* nop */,
                      "inactive fb(%d)\n", fb_dev_id);

    switch (cmd)
    {
        case FBDEV_IOR_CHIP_REV_INFO:
        {
            ret = RET_OK;
        }
        break;

        case FBDEV_IOR_GET_CFG:
        {
            rc = copy_to_user((void __user*)arg, (void*)g_fbdev_cfg, sizeof(LX_FBDEV_CFG_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_PALETTE:
        {
#if 1
            FBDEV_NOTI("palette configuration not supported\n");
#else
            LX_FBDEV_PALETTE_T input_pal;   /* temporary variable to hold palette struct */
            LX_FBDEV_PALETTE_T fbdev_pal;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

#ifdef CONFIG_COMPAT

            if (is_compat_task())
            {
                rc = copy_from_user((void*)&input_pal, (void __user*)compat_ptr(arg),
                                    sizeof(LX_FBDEV_PALETTE_T));
            }
            else
#else
            {
                rc = copy_from_user((void*)&input_pal, (void __user*)arg, sizeof(LX_FBDEV_PALETTE_T));
            }

#endif
                FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            fbdev_pal.palette_data = (UINT32*) OS_Malloc(sizeof(UINT32) * 256);
            FBDEV_CHECK_ERROR(NULL == fbdev_pal.palette_data, goto func_exit, "pallete alloc error\n");

            fbdev_pal.palette_num = input_pal.palette_num;

#ifdef CONFIG_COMPAT

            if (is_compat_task())
            {
                rc = copy_from_user((void*)
                                    fbdev_pal.palette_data, (void __user*)
                                    compat_ptr(input_pal.compat_palette_data),
                                    sizeof(UINT32) * input_pal.palette_num);
            }
            else
#endif
            {
                rc = copy_from_user((void*)
                                    fbdev_pal.palette_data,
                                    (void __user*)input_pal.palette_data,
                                    sizeof(UINT32) * input_pal.palette_num);
            }

            FBDEV_CHECK_ERROR(rc > 0, OS_Free(fbdev_pal.palette_data); goto func_exit, "copy error\n");

            FBDEV_SetPalette(wctx, fbdev_pal.palette_data, fbdev_pal.palette_num);

            OS_Free(fbdev_pal.palette_data);
#endif
            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOR_GET_CONFIG:
        {
            LX_FBDEV_CONFIG_T config;

            //                      /* support only POSD is enable(active)? */
            //                      if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

            FBDEV_GetConfig(wctx, &config);
            rc = copy_to_user((void __user*)arg, (void*)&config, sizeof(LX_FBDEV_CONFIG_T));
            FBDEV_CHECK_ERROR(rc > 0,, "copy error\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_CONFIG:
        {
            LX_FBDEV_CONFIG_T config;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&config, (void __user*)arg, sizeof(LX_FBDEV_CONFIG_T));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

            FBDEV_SetConfig(wctx, &config, TRUE);

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBEXTIO_PUT_DISPLAYPOSITION:
        {
            LX_FBDEV_CONFIG_T config;
            struct fb_ext_displayposition dinfo;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&dinfo, (void __user*)arg, sizeof(struct fb_ext_displayposition));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

            FBDEV_GetConfig(wctx, &config);
            config.output_win.x = dinfo.x;
            config.output_win.y = dinfo.y;

            /* raxis.lim (2019/07/24)
             * this ext ioctl is delayed until user requests framebuffer update
             * refer to http://clm.lge.com/issue/browse/SCDCR-2588
             */
            FBDEV_SetConfig(wctx, &config, FALSE);

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBEXTIO_PUT_DISPLAYREGION:
        {
            struct fb_ext_displayregion dregion;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&dregion, (void __user*)arg, sizeof(struct fb_ext_displayregion));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

            if (fb_dev_id == LX_FBDEV_ID_OSD1)
            {
                FBDEV_HW_CMD_DATA_T hw_cmd;

                hw_cmd.gen[0] = fb_dev_id;
                hw_cmd.gen[1] = LX_MAKE_RES(dregion.x, dregion.y);
                hw_cmd.gen[2] = LX_MAKE_RES(dregion.width, dregion.height);

                (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_CONFIGURE_CROP_REGION,
                                          &hw_cmd);
            }

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBEXTIO_PUT_INPUTBUFFER_RESOLUTION:
        {
            struct fb_ext_buffer_resolution region;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&region, (void __user*)arg,
                                sizeof(struct fb_ext_buffer_resolution));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

            // (2020/09/23) allow application to open any framebufer to use this ioctl
            // see implementation spec, http://clm.lge.com/issue/browse/SICDTV-8781
            //if(fb_dev_id == LX_FBDEV_ID_OSD0)
            {
                int osd_res_info;
                FBDEV_HW_CMD_DATA_T hw_cmd;

                FBDEV_NOTI("FBEXTIO_PUT_INPUTBUFFER_RESOLUTION size=%04dx%04d\n", region.width,
                           region.height);

                if (region.width <= 1376 && region.height <= 768)
                {
                    osd_res_info = 1;
                }
                else if (region.width <= 1920 && region.height <= 1080)
                {
                    osd_res_info = 2;
                }
                else if (region.width <= 3840 && region.height <= 2160)
                {
                    osd_res_info = 3;
                }
                else
                {
                    osd_res_info = 0;    /* error, default state */
                }

                hw_cmd.gen[0] = LX_FBDEV_ID_OSD0;
                hw_cmd.gen[1] = osd_res_info;

                (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_OSD_SHP_AUTO_CONFIG, &hw_cmd);
            }

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOR_GET_POSITION:
        {
            LX_POSITION_T cur_pos;

            cur_pos.x = wctx->pixel.output_win.x;
            cur_pos.y = wctx->pixel.output_win.y;

            rc = copy_to_user((void __user*)arg, (void*)&cur_pos, sizeof(LX_POSITION_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_POSITION:
        {
            LX_POSITION_T new_pos;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&new_pos, (void __user*)arg, sizeof(LX_POSITION_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            wctx->pixel.csr_size.w = 0; /* use the full size */
            wctx->pixel.csr_size.h = 0; /* use the full size */
            wctx->pixel.csr_hotspot.x = 0;  /* disable hotspot */
            wctx->pixel.csr_hotspot.y = 0;  /* disable hotspot */

            //                      if ( new_pos.x < 0 ) new_pos.x = 0;
            //                      if ( new_pos.y < 0 ) new_pos.y = 0;

            wctx->pixel.output_win.x = new_pos.x;
            wctx->pixel.output_win.y = new_pos.y;

            FBDEV_WriteOSDHeader(&wctx->pixel);

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_CURSOR_POSITION:
        {
            LX_FBDEV_CURSOR_POSITION_T cursor;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&cursor, (void __user*)arg, sizeof(LX_FBDEV_CURSOR_POSITION_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            wctx->pixel.csr_size.w = cursor.size.w;
            wctx->pixel.csr_size.h = cursor.size.h;
            wctx->pixel.csr_hotspot.x = cursor.hotspot.x;
            wctx->pixel.csr_hotspot.y = cursor.hotspot.y;
            wctx->pixel.output_win.x = cursor.pos.x + g_fbdev_cursor_x_comp;
            wctx->pixel.output_win.y = cursor.pos.y + g_fbdev_cursor_y_comp;

            /* raxis.lim (2018/05/02)
             * let's think about valid cursor range.
             * (1) valid cursor range is (-32767,32768) in both h and v directoin becuase its type is SINT16
             * (2) normaly application think about FHD sized OSD screen, cursor position is also set inside FHD area.
             *         if OSD HW supports 4K-output, OSD chip kdriver scales up position to 4K-area.
             *         so application's valid cursor range should be (-16383,+16384)
             * (3) if OSD HW supports 8K OSD, OSD chip kdriver scales up position to 8K-area.
             *         so application's valid cursor range should be (-8195,+8196)
             *
             * BUT OSD HW can't display cursor image outside the valid OSD area, so chip kdriver should check the valid area again.
             *
             */
#define CSR_POS_MAX ((s16)(USHRT_MAX>>3))
#define CSR_POS_MIN ((s16)(-CSR_POS_MAX - 1))

            if (wctx->pixel.output_win.x < CSR_POS_MIN)
            {
                wctx->pixel.output_win.x = CSR_POS_MIN;
            }

            if (wctx->pixel.output_win.x > CSR_POS_MAX)
            {
                wctx->pixel.output_win.x = CSR_POS_MAX;
            }

            if (wctx->pixel.output_win.y < CSR_POS_MIN)
            {
                wctx->pixel.output_win.y = CSR_POS_MIN;
            }

            if (wctx->pixel.output_win.y > CSR_POS_MAX)
            {
                wctx->pixel.output_win.y = CSR_POS_MAX;
            }

            FBDEV_DEBUG("sz %d,%d hotspot %d,%d pos %d,%d\n",
                        cursor.size.w, cursor.size.h, cursor.hotspot.x, cursor.hotspot.y, cursor.pos.x,
                        cursor.pos.y);
            FBDEV_WriteOSDHeader(&wctx->pixel);

            /* raxis.lim (2012/01/03) -- when UD mode, all POSD should be merge into the single POSD. so cursor movement should wait for vsync */
            if (fbctx->global.pivot_mode != LX_FBDEV_PIVOT_MODE_NONE)
            {
                FBDEV_WaitVSync(fb_dev_id, wctx->vsync_cnt_on_flip);    /* wait for vsync !! */
            }

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOR_GET_PHY_MEMORY:
        {
            LX_FBDEV_PHY_MEMORY_T phy_mem;
            UINT32 stride = wctx->pixel.stride;
            UINT32 len = wctx->fb_size;

            phy_mem.memptr = wctx->fb_base_phys;
            phy_mem.stride = stride;
            phy_mem.length = len;

            rc = copy_to_user((void __user*)arg, (void*)&phy_mem, sizeof(LX_FBDEV_PHY_MEMORY_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_VISIBLE:
        {
            UINT32 enable;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&enable, (void __user*)arg, sizeof(UINT32));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            FBDEV_DEBUG("fb(%d)::FBDEV_IOW_SET_VISIBLE. val(%d)\n", fb_dev_id, enable);
            FBDEV_SetOSDEnable(wctx->pixel.fb_dev_id, enable);
#if 0

            /* OSD layer actually will be turned off but after vsync of the time of disabling the lyaer not at that time of disabling it.
             * In curosr, if thw app try to re-draw the new cursor image after disabling it without waiting of vsync, the display would be cracked
             */
            if (lx_chip_plt() == LX_CHIP_PLATFORM_COSMO)
            {
                FBDEV_WaitVSync(fb_dev_id, wctx->vsync_cnt_on_flip);    /* wait for vsync !! */
            }

#endif
            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOR_GET_VISIBLE:
        {
            UINT32 enable;

            enable = (unsigned int)(FBDEV_GetOSDEnable(wctx->pixel.fb_dev_id));

            rc = copy_to_user((void __user*)arg, (void*)&enable, sizeof(UINT32));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBEXTIO_PUT_DISPLAYVISIBLE:
        {
            struct fb_ext_displayvisible vinfo;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&vinfo, (void __user*)arg, sizeof(struct fb_ext_displayvisible));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

            FBDEV_DEBUG("fb(%d)::FBEXTIO_PUT_DISPLAYVISIBLE. val(%d)\n", fb_dev_id, vinfo.visible);
            FBDEV_SetOSDEnable(wctx->pixel.fb_dev_id, vinfo.visible);

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOR_GET_FB_STATUS:
        {
            LX_FBDEV_FB_STATUS_T fb_status;
            memset(&fb_status, 0x0, sizeof(LX_FBDEV_FB_STATUS_T));

            fb_status.b_visible = FBDEV_GetOSDEnable(wctx->pixel.fb_dev_id);
            fb_status.view_fb_phys_addr = wctx->pixel.osd_bm_paddr;

            rc = copy_to_user((void __user*)arg, (void*)&fb_status, sizeof(LX_FBDEV_FB_STATUS_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IO_WAITFORVSYNC:
        {
            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_DEBUG("fb(%d)::FBDEV_IO_WAITFORVSYNC\n", fb_dev_id);

#ifdef FBDEV_FLIP_LOCK
            OS_LockMutex(&wctx->fb_dev_mtx);
#endif
            FBDEV_WaitVSync(fb_dev_id, wctx->vsync_cnt_on_flip);    /* wait for vsync !! */
#ifdef FBDEV_FLIP_LOCK
            OS_UnlockMutex(&wctx->fb_dev_mtx);
#endif
            ret = RET_OK;   /* all work done. don't detect VSYNC timeout */
        }
        break;

        /*
         * -1: donot care the vsync. use configuration setting
         *  0: donot wait vsync.
         * >0: wait vsyncs.
         */
        case FBDEV_IOW_WAITFORVSYNC_ON_FLIP:
        {
            rc = get_user(wctx->vsync_cnt_on_flip, (int*)arg);
        }
        break;

        case FBDEV_IORW_GET_ZLIST:
        {
            LX_FBDEV_ZLIST_T zList;

            rc = FBDEV_GetZList(&zList);
            FBDEV_CHECK_ERROR(rc != RET_OK, goto func_exit, "can't get zlist\n");

            rc = copy_to_user((void __user*)arg, (void*)&zList, sizeof(LX_FBDEV_ZLIST_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_ZLIST:
        {
            LX_FBDEV_ZLIST_T zList;

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&zList, (void __user*)arg, sizeof(LX_FBDEV_ZLIST_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            rc = FBDEV_SetZList(&zList);
            FBDEV_CHECK_ERROR(rc != RET_OK, goto func_exit, "can't set zlist\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_VIDEO_MIXER_CTRL:
        {
            LX_FBDEV_VIDEO_MIXER_CTRL_T mix_ctrl;

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&mix_ctrl, (void __user*)arg, sizeof(LX_FBDEV_VIDEO_MIXER_CTRL_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            rc = FBDEV_SetVideoMixerCtrl(&mix_ctrl);
            FBDEV_CHECK_ERROR(rc != RET_OK, goto func_exit, "can't set video mixer\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_TRID_CTRL:
        {
            LX_FBDEV_TRID_CTRL_T trid_ctrl;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&trid_ctrl, (void __user*)arg, sizeof(LX_FBDEV_TRID_CTRL_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            rc = FBDEV_SetTridCtrl(fb_dev_id, &trid_ctrl);
            FBDEV_CHECK_ERROR(rc != RET_OK, goto func_exit, "can't init FRC\n");

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_CONN_CTRL:
        {
            LX_FBDEV_CONN_CTRL_T conn_ctrl;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&conn_ctrl, (void __user*)arg, sizeof(LX_FBDEV_CONN_CTRL_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            rc = FBDEV_SetConnCtrl(&conn_ctrl);
            FBDEV_CHECK_ERROR(rc != RET_OK, goto func_exit, "can't update the connection\n");

            /* when changing connection mode, reset vsync timoeut to be default */
            g_fbdev_vsync_timeout = FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT;

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_FREEZE_CTRL:
        {
            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_PIVOT_CTRL:
        {
            LX_FBDEV_PIVOT_CTRL_T pivot_ctrl;

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&pivot_ctrl, (void __user*)arg, sizeof(LX_FBDEV_PIVOT_CTRL_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            FBDEV_DEBUG("fbdev::FBDEV_IOW_SET_PIVOT_CTRL. 0x%x\n", pivot_ctrl.mode);
            FBDEV_SetPivotCtrl(&pivot_ctrl);

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_VIEW_CTRL:
        {
            LX_FBDEV_VIEW_CTRL_T view_ctrl;

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&view_ctrl, (void __user*)arg, sizeof(LX_FBDEV_VIEW_CTRL_T));
            FBDEV_CHECK_ERROR(rc > 0, goto func_exit, "copy error\n");

            FBDEV_DEBUG("fbdev::FBDEV_IOW_SET_VIEW_CTRL\n");
            FBDEV_SetViewCtrl(&view_ctrl);

            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_FLIP_FB_IMAGE:
        {
            LX_FBDEV_FB_IMAGE_T fb_screen;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&fb_screen, (void __user*)arg, sizeof(LX_FBDEV_FB_IMAGE_T));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

#ifdef FBDEV_FLIP_LOCK
            OS_LockMutex(&wctx->fb_dev_mtx);
#endif
            FBDEV_DEBUG("fb(%d)::FBDEV_IOW_FLIP_FB_IMAGE\n", fb_dev_id);
            FBDEV_FlipFBImage(fb_dev_id, &fb_screen, FALSE);
#ifdef FBDEV_FLIP_LOCK
            OS_UnlockMutex(&wctx->fb_dev_mtx);
#endif
            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_UPDATE_FB_SCREEN:
        {
            LX_FBDEV_FB_SCREEN_T fb_screen;

            /* support only POSD is enable(active)? */
            if (!g_fbdev_cfg->fb[fb_dev_id].b_active)
            {
                ret = RET_OK;
                break;
            }

            FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, ret = RET_OK; break, "osd freezed\n");

            rc = copy_from_user((void*)&fb_screen, (void __user*)arg, sizeof(LX_FBDEV_FB_SCREEN_T));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

#ifdef FBDEV_FLIP_LOCK
            OS_LockMutex(&wctx->fb_dev_mtx);
#endif
            FBDEV_DEBUG("fb(%d)::FBDEV_IOW_UPDATE_FB_SCREEN\n", fb_dev_id);
            FBDEV_UpdateFBScreen(fb_dev_id, &fb_screen, FALSE);
#ifdef FBDEV_FLIP_LOCK
            OS_UnlockMutex(&wctx->fb_dev_mtx);
#endif
            ret = RET_OK;   /* all work done */
        }
        break;

        case FBDEV_IOW_SET_VSYNC_EVENT:
        {
#ifdef USE_FBDEV_VSYNC_UEVENT
            UINT32 en;
            rc = copy_from_user((void*)&en, (void __user*)arg, sizeof(UINT32));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

            vsync_ev_ctrl.vsync_irq_enabled = (en) ? 1 : 0;
#endif
            ret = RET_OK;   /* all work done */
        }
        break;

#ifdef USE_FBDEV_USER_FLIP_HANDLER

        case FBDEV_IOW_SET_USER_FLIP_HANDLER:
        {
            ULONG flags;
            UINT32 flip_en;

            FBDEV_CHECK_ERROR(fb_dev_id != LX_FBDEV_ID_OSD0, break, "fb(%d) not supported\n", fb_dev_id);

            rc = copy_from_user((void*)&flip_en, (void __user*)arg, sizeof(UINT32));
            FBDEV_CHECK_ERROR(rc > 0, break, "copy error\n");

            /* setup user_flip */
            spin_lock_irqsave(&user_flip_ctrl.spinlock, flags);
            user_flip_ctrl.enabled = flip_en;
            user_flip_ctrl.user_pid = current->pid;
            spin_unlock_irqrestore(&user_flip_ctrl.spinlock, flags);

            FBDEV_USER_FLIP_DEBUG
            ("<kdrv> user_flip_ctrl - status=%s, pid=%d, opt=0x%08x\n",
             (flip_en) ? "on" : "off", current->pid, user_flip_ctrl.opt);

            ret = RET_OK;
        }
        break;

        case FBDEV_IOW_SET_USER_FLIP_ACK:
        {
            ULONG flags;
            LX_FBDEV_USER_FLIP_T user_flip_image;

            FBDEV_CHECK_ERROR(fb_dev_id != LX_FBDEV_ID_OSD0, break, "fb(%d) not supported\n", fb_dev_id);

            rc = copy_from_user((void*)&user_flip_image, (void __user*)arg, sizeof(LX_FBDEV_USER_FLIP_T));
            FBDEV_CHECK_ERROR(rc > 0, break, "FBDEV_IOW_SET_USER_FLIP_ACK copy error\n");

            FBDEV_USER_FLIP_DEBUG
            ("<kdrv> user_flip_ctrl(%04d) - ack ioctl received. waking up ack_event. pid=%d\n",
             user_flip_image.session_no, current->pid);

            FBDEV_CHECK_ERROR(!user_flip_ctrl.enabled, break,
                              "<kdrv> ack ioctl rejected. user_flip_ctrl disconnected\n");

            /* copy data from user & notify to ack_event */
            spin_lock_irqsave(&user_flip_ctrl.spinlock, flags);

            if (user_flip_image.session_no == user_flip_ctrl.fbmem.session_no)
            {
                memcpy(&user_flip_ctrl.fbmem, &user_flip_image, sizeof(LX_FBDEV_USER_FLIP_T));
                ret = RET_OK;
            }
            else
            {
                FBDEV_WARN
                ("<kdrv> session mismatch. %d != %d\n", user_flip_image.session_no,
                 user_flip_ctrl.fbmem.session_no);
                ret = RET_ERROR;
            }

            complete_all(&user_flip_ctrl.ack_event);
            spin_unlock_irqrestore(&user_flip_ctrl.spinlock, flags);
        }
        break;
#endif

        case FBIOGET_DMABUF:
            ret = fbdev_get_dmabuf(wctx, arg);
            break;

        default:
        {
            /* redundant check but it seems more readable */
            FBDEV_ERROR("unknown/not handled ioctl cmd 0x%08X\n", cmd);

            ret = -ENOTTY;
        }
    }

func_exit:
    return ret;
}

/*========================================================================================
    Implementation Group ( open & close )
========================================================================================*/
void FBDEV_SetInterruptHandler(BOOLEAN enable)
{
    if (enable)
    {
        int rc;

        if (g_fbdev_irq_run_flag)
        {
            return;
        }

        rc = request_irq(g_fbdev_hwio_cfg->irq_num, (irq_handler_t) FBDEV_ISRHandler, 0, "osd_irq", NULL);
        FBDEV_NOTI("osd.request_irq (irq=%d, rc=%d\n", g_fbdev_hwio_cfg->irq_num, rc);
        FBDEV_CHECK_ERROR(rc, /* nop */, "request_irq failed\n");

        g_fbdev_irq_run_flag = 1;

#if defined(CONFIG_SMP) && defined(CONFIG_GENERIC_HARDIRQS)
        //              irq_set_affinity( g_fbdev_hwio_cfg->irq_num, cpumask_of(1) );
#endif
        FBDEV_SetInterruptEnable(MIXER_INTR, 1);
    }
    else
    {
        if (!g_fbdev_irq_run_flag)
        {
            return;
        }

        free_irq(g_fbdev_hwio_cfg->irq_num, NULL);
        FBDEV_NOTI("osd.free_irq (irq=%d)\n", g_fbdev_hwio_cfg->irq_num);
        g_fbdev_irq_run_flag = 0;

        FBDEV_SetInterruptEnable(MIXER_INTR, 0);
    }
}

void FBDEV_OpenDRMContext(struct platform_device* pdev, int fb_dev_id)
{
    FBDEV_WIN_CTX_T* win_ctx = FBDEV_GetWinCtx(fb_dev_id);

    win_ctx->vsync_cnt_on_flip = -1;
    win_ctx->vsync_cnt = 0;

    if (win_ctx->users++ == 0)
    {
        FBDEV_SetInterruptHandler(TRUE);
    }

    /* initialize vsync uevent */
#ifdef USE_FBDEV_VSYNC_UEVENT

    if (g_fbdev_vsync_ev_init == 0)
    {
        int ret;

        vsync_ev_ctrl.dev = &pdev->dev;
        ret = sysfs_create_group(&vsync_ev_ctrl.dev->kobj, &vsync_fs_attr_group);
        FBDEV_CHECK_ERROR(ret != RET_OK, /* nop */,
                          "sysfs group creatioin failed. ret=%d\n", ret);

        g_fbdev_vsync_ev_init = 1;

        kobject_uevent(&vsync_ev_ctrl.dev->kobj, KOBJ_ADD);
        spin_lock_init(&vsync_ev_ctrl.spinlock);
        init_completion(&vsync_ev_ctrl.event);

        vsync_ev_ctrl.vsync_irq_enabled = 0;    /* disable at start. TEST: enabled when vsync_show_event() is called */
    }

#endif

    /* notify POSD_OPEN */
    {
        struct fb_info info;
        FBDEV_HW_CMD_DATA_T hw_cmd;
        hw_cmd.gen[0] = fb_dev_id;
        hw_cmd.genex[0] = (UINT64)&info; /* dummy */
        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_POSD_OPEN, &hw_cmd);
    }
}
EXPORT_SYMBOL(FBDEV_OpenDRMContext);

void FBDEV_CloseDRMContext(int fb_dev_id)
{
    FBDEV_HW_CMD_DATA_T hw_cmd;
    FBDEV_WIN_CTX_T* win_ctx = FBDEV_GetWinCtx(fb_dev_id);

    --win_ctx->users;

    /* notify POSD_CLOSE */
    hw_cmd.gen[0] = win_ctx->fb_dev_id;
    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_POSD_CLOSE, &hw_cmd);

}
EXPORT_SYMBOL(FBDEV_CloseDRMContext);

/** module open.
 *
 * @param   struct fb_info *info , int user
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_open(struct fb_info* info, int user)
{
    FBDEV_WIN_CTX_T* win;
    int ret = RET_ERROR;
    int fb_dev_id;
    FBDEV_HW_CMD_DATA_T hw_cmd;

    win = (FBDEV_WIN_CTX_T*) info->par;

    fb_dev_id = win->fb_dev_id;
    FBDEV_CHECK_ERROR(!win, goto func_exit, "null parameter\n");

    /* by default, user dont care about vsync. use the configuration setting */
    win->vsync_cnt_on_flip = -1;
    win->vsync_cnt = 0;

    /*      raxis.lim (2010/11/20) -- register interrupt handler when IRQ enabled */
    if (win->users++ == 0)
    {
        FBDEV_SetInterruptHandler(TRUE);
        info->state |= (1 << 1);

        if (is_win(info->fix.id, OSD0))
        {
            if (g_fbdev_cfg->fb[0].b_show_on_startup)
            {
                FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD0, TRUE);
            }
        }
        else if (is_win(info->fix.id, OSD1))
        {
            if (g_fbdev_cfg->fb[1].b_show_on_startup)
            {
                FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD1, TRUE);
            }
        }
        else if (is_win(info->fix.id, OSD2))
        {
            if (g_fbdev_cfg->fb[2].b_show_on_startup)
            {
                FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD2, TRUE);
            }
        }
        else if (is_win(info->fix.id, OSD_CURSOR))
        {
            if (g_fbdev_cfg->fb[3].b_show_on_startup)
            {
                FBDEV_SetOSDEnable(LX_FBDEV_ID_CSR0, TRUE);
            }
        }
        else
        {
            /* do nothing */
        }
    }

    /* initialize vsync uevent */
#ifdef USE_FBDEV_VSYNC_UEVENT

    if (g_fbdev_vsync_ev_init == 0)
    {
        vsync_ev_ctrl.dev = info->dev;
        ret = sysfs_create_group(&vsync_ev_ctrl.dev->kobj, &vsync_fs_attr_group);
        FBDEV_CHECK_ERROR(ret != RET_OK, /* nop */,
                          "sysfs group creatioin failed. ret=%d\n", ret);

        g_fbdev_vsync_ev_init = 1;

        kobject_uevent(&vsync_ev_ctrl.dev->kobj, KOBJ_ADD);
        spin_lock_init(&vsync_ev_ctrl.spinlock);
        init_completion(&vsync_ev_ctrl.event);

        vsync_ev_ctrl.vsync_irq_enabled = 0;    /* disable at start. TEST: enabled when vsync_show_event() is called */
    }

#endif

    /* initialize user_flip context */
#ifdef USE_FBDEV_USER_FLIP_HANDLER

    if (g_fbdev_user_flip_ev_init == 0)
    {
        user_flip_ctrl.dev = info->dev;
        ret = sysfs_create_group(&user_flip_ctrl.dev->kobj, &user_flip_fs_attr_group);
        FBDEV_CHECK_ERROR(ret != RET_OK, /* nop */,
                          "sysfs group creatioin failed. ret=%d\n", ret);

        g_fbdev_user_flip_ev_init = 1;

        kobject_uevent(&user_flip_ctrl.dev->kobj, KOBJ_ADD);
        spin_lock_init(&user_flip_ctrl.spinlock);
        init_completion(&user_flip_ctrl.user_event);
        init_completion(&user_flip_ctrl.ack_event);

        user_flip_ctrl.user_pid = -1;
        user_flip_ctrl.enabled = false;
        user_flip_ctrl.opt = 0x0;
    }

#endif

#ifdef USE_FBDEV_CAPTURE

    if (g_fbdev_use_capture && g_cap_ctrl_init == 0)
    {
        OS_InitMutex(&g_cap_ctrl.cap_req_sema, OS_SEM_ATTR_DEFAULT);
        OS_InitMutex(&g_cap_ctrl.img_ready_sema, OS_SEM_ATTR_DEFAULT);

        FBDEV_CHECK_ERROR(RET_OK != OS_LockMutex(&g_cap_ctrl.cap_req_sema),
                          /* do nothing */, "lock failed\n");
        FBDEV_CHECK_ERROR(RET_OK != OS_LockMutex(&g_cap_ctrl.img_ready_sema),
                          /* do nothing */, "lock failed\n");

        g_cap_ctrl_init = 1;
    }

#endif

#ifdef USE_FBDEV_FBMEM_HOOK

    if (g_fbdev_use_fbmem_hook && g_fbmme_hook_ctrl_init == 0)
    {
        OS_InitMutex(&g_fbmem_hook_ctrl.cap_req_sema, OS_SEM_ATTR_DEFAULT);
        OS_InitMutex(&g_fbmem_hook_ctrl.img_ready_sema, OS_SEM_ATTR_DEFAULT);

        FBDEV_CHECK_ERROR(RET_OK != OS_LockMutex(&g_fbmem_hook_ctrl.cap_req_sema),
                          /* do nothing */, "lock failed\n");
        FBDEV_CHECK_ERROR(RET_OK != OS_LockMutex(&g_fbmem_hook_ctrl.img_ready_sema),    /* do nothing */
                          , "lock failed\n");

        g_fbmme_hook_ctrl_init = 1;
    }

#endif

    /* notify POSD_OPEN */
    hw_cmd.gen[0] = fb_dev_id;
    hw_cmd.genex[0] = (UINT64) info;
    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_POSD_OPEN, &hw_cmd);

    FBDEV_DEBUG("fb(%d) var.reserved = 0x%08x, 0x%08x, 0x%08x, 0x%08x\n",
                fb_dev_id, info->var.reserved[0], info->var.reserved[1], info->var.reserved[2],
                info->var.reserved[3]);

    ret = RET_OK;       /* all work done */
func_exit:
    return ret;
}

/**
 *
 * module close.
 *
 * @param   struct fb_info *info , int user
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_close(struct fb_info* info, int user)
{
    int ret = RET_ERROR;
    FBDEV_WIN_CTX_T* win;
    FBDEV_HW_CMD_DATA_T hw_cmd;

    win = (FBDEV_WIN_CTX_T*) info->par;
    FBDEV_CHECK_ERROR(!win, goto func_exit, "null parameter\n");

    /* raxis.lim (2011/03/29)
     * DO NOT clear interrupt when FB closed.
     * the below code seems to stop all interrupts of FB when a single FB device is closed.
     */
#if 0

    if (--win->users == 0 && (info->state & (1 << 1)))
    {
        /* raxis.lim (2010/11/26) -- OSD irq is never freed */
        // free_irq(IRQ_OSD,NULL);
        info->state &= ~(1 << 1);   // info state : 0bit(running, suspend) 1bit(irq enable, disable)
    }

    if (is_win(info->fix.id, OSD0))
    {
        FBDEV_SetInterruptEnable(OSD_0_INTR, FALSE);
        FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD0, FALSE);
    }
    else if (is_win(info->fix.id, OSD1))
    {
        FBDEV_SetInterruptEnable(OSD_1_INTR, FALSE);
        FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD1, FALSE);
    }
    else if (is_win(info->fix.id, OSD2))
    {
        FBDEV_SetInterruptEnable(OSD_2_INTR, FALSE);
        FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD2, FALSE);
    }
    else if (is_win(info->fix.id, OSD_CURSOR))
    {
        FBDEV_SetInterruptEnable(CRSR_INTR, FALSE);
        FBDEV_SetOSDEnable(LX_FBDEV_ID_CSR0, FALSE);
    }
    else
    {

    }

#else
    --win->users;
#endif

    /* notify POSD_CLOSE */
    hw_cmd.gen[0] = win->fb_dev_id;
    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_POSD_CLOSE, &hw_cmd);

func_exit:
    return ret;
}

/**
 *
 * probing module.
 *
 * @param   struct platform_device *pdev
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int /*__init*/ FBDEV_probe(struct platform_device* pdev)
{
    int i;
    FBDEV_PDEV_CTX_T* pdev_ctx;
    char* fbname_list[FBDEV_MAX_DEVICE] = { OSD0_FBNAME, OSD1_FBNAME, OSD2_FBNAME, OSD3_FBNAME };

    FBDEV_INFO("fbdev probe start\n");

    pdev_ctx = (FBDEV_PDEV_CTX_T*) vzalloc(sizeof(FBDEV_PDEV_CTX_T));
    FBDEV_CHECK_ERROR(NULL == pdev_ctx, return RET_ERROR, "alloc error\n");

    pdev_ctx->is_suspend = false;
    pdev_ctx->is_runtime_active = true;

    platform_set_drvdata(pdev, pdev_ctx);

    memset(g_dm_ctx, 0x0, sizeof(FBDEV_CTX_T));

    g_dm_ctx->dev = &pdev->dev;
    g_dm_ctx->global.b_freeze = FALSE;
    g_dm_ctx->global.pivot_mode = LX_FBDEV_PIVOT_MODE_NONE;

    FBDEV_CHECK_ERROR(FBDEV_InitHardware() < 0, goto func_exit, "HW init fail\n");

    /* initialize osd layer & fb structure */
    for (i = 0; i < FBDEV_MAX_DEVICE; i++)
    {
        g_dm_ctx->wctx[i] = FBDEV_InitWinCtx(i, fbname_list[i]);
        FBDEV_InitLinuxFrameBuffer(g_dm_ctx->wctx[i], FBDEV_GetVarScreenObject(i), fbname_list[i]);
    }

    /* adjust vsync counter to support always 60HZ display */
#ifdef FBDEV_USE_FIXED_60HZ_VSYNC
    {
        FBDEV_HW_CMD_DATA_T cmd_data;

        if (RET_OK == FBDEV_ExecHWCommand(FBDEV_HW_CMD_RD_VSYNC_CLK, &cmd_data))
        {
            g_fbdev_vsync_cnt_on_flip = (cmd_data.gen[0] == FBDEV_VSYNC_CLK_120HZ) ? 2 : 1;
        }
    }
#endif

    /* do something if necessary */
    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_POST_HW_INIT, NULL);

#ifdef BUILD_FEATURE_fpga
    FBDEV_NOTI("+ start osd interrutp @fpga\n");
    FBDEV_SetInterruptHandler(TRUE);
#endif

func_exit:
    //FBDEV_INFO("fbdev proble <end>\n");
    return RET_OK;
}

/** initialize OSD HW context
 *
 */
static FBDEV_WIN_CTX_T* FBDEV_InitWinCtx(int fb_dev_id, char* fbname)
{
    FBDEV_WIN_CTX_T* wctx = NULL;
    LX_FBDEV_CFG_T* cfg = FBDEV_GET_CFG();

    /* allocate window context and initialize it */
    wctx = OS_Malloc(sizeof(FBDEV_WIN_CTX_T));
    FBDEV_CHECK_ERROR(!wctx, goto err_exit, "fb(%d) can't alloc wctx\n", fb_dev_id);

    memset(wctx, 0x0, sizeof(FBDEV_WIN_CTX_T));

    /* create per-device mutex */
    OS_InitMutex(&wctx->fb_dev_mtx, OS_SEM_ATTR_DEFAULT);

    wctx->dm = g_dm_ctx;
    wctx->fb_dev_id = fb_dev_id;
    wctx->linux_fb_mode = FALSE;    /* off by default value */
    wctx->status.b_osd_hdr_write = TRUE;    /* osd write is enabled by default */
    wctx->status.b_use_vsync = cfg->fb[fb_dev_id].b_use_vsync;

#if (CONFIG_LX_BOOT_LOGO==1)
    wctx->status.b_osd_hdr_flush = FALSE;   /* keep osd header to keep boot logo shown */
#else
    wctx->status.b_osd_hdr_flush = TRUE;    /* osd header will be upated by both kdrv or app */
#endif

    /* if builtin_bmem is enabled, try to allocate OSD's private framebuffer and support linux framebuffer */
    if (cfg->fb[fb_dev_id].b_active && cfg->fb[fb_dev_id].b_use_builtin_fbmem)
    {
        wctx->linux_fb_mode = TRUE;
    }

    FBDEV_NOTI("fb(%d) linux_fb_mode = %d, abfc = %d\n", fb_dev_id, wctx->linux_fb_mode,
               cfg->fb[fb_dev_id].b_use_afbc);

    if (wctx->linux_fb_mode)
    {
        int i;
        UINT32 fbmem_size;
        int fb_xres = cfg->fb[fb_dev_id].max_xres;
        int fb_yres = cfg->fb[fb_dev_id].max_yres;
        int fb_bufnum = cfg->fb[fb_dev_id].max_buf_num;

        if (cfg->fb[fb_dev_id].b_use_afbc)
        {
            fbmem_size = afbc_sw_get_image_size(NULL, fb_xres, fb_yres);
        }
        else
        {
            fbmem_size = fb_xres * fb_yres * (cfg->fb[fb_dev_id].bits_per_pixel >> 3);
        }

        fbmem_size = ALIGN(fbmem_size, PAGE_SIZE) * fb_bufnum;

        FBDEV_NOTI("fb(%d) alloc framebuffer. size=%dx%d(%d), num=%d\n",
                   fb_dev_id, fb_xres, fb_yres, fbmem_size, fb_bufnum);

        wctx->fb_size = fbmem_size;
        wctx->fb_base_phys = (UINT32) hma_alloc("surface", fbmem_size, PAGE_SIZE);
        FBDEV_CHECK_ERROR(0x0 == wctx->fb_base_phys, dump_stack(),
                          "fb(%d). can't alloc framebuffer. size=%d\n", fb_dev_id, fbmem_size);

        /* clear two AFBC memory region */
        for (i = 0; i < fb_bufnum; i++)
        {
            struct afbc_framebuffer* afbc_fb = afbc_sw_alloc_framebuffer(NULL,
                                               wctx->fb_base_phys +
                                               (fbmem_size * i / fb_bufnum),
                                               fb_xres,
                                               fb_yres,
                                               0,
                                               0,
                                               0);

            if (afbc_fb)
            {
                afbc_sw_fill(NULL, afbc_fb, 0x00000000);
                afbc_sw_free_framebuffer(NULL, afbc_fb);
            }
        }
    }
    else
    {
        wctx->fb_base_phys = gMemCfgFBDev[fb_dev_id].mem_frame_base;    /* NA */
        wctx->fb_size = gMemCfgFBDev[fb_dev_id].mem_frame_size; /* NA */
    }

    wctx->osd_plte_base_phys = gMemCfgFBDev[fb_dev_id].mem_palette_base;    /* NA */
    wctx->osd_plte_size = gMemCfgFBDev[fb_dev_id].mem_palette_size; /* NA */

    wctx->osd_hdr_base_phys = gMemCfgFBHdr[fb_dev_id].mem_header_base;  /* NA */
    wctx->osd_hdr_size = gMemCfgFBHdr[fb_dev_id].mem_header_size;   /* NA */

    wctx->fb_base = vmap_phys(wctx->fb_base_phys, wctx->fb_size);
    FBDEV_CHECK_ERROR(!wctx->fb_base, /* nop */,
                      "fb(%d) fb_base vmap failed (0x%08x,%d)\n", fb_dev_id, wctx->fb_base_phys, wctx->fb_size);

    wctx->osd_hdr_base = vmap_phys(wctx->osd_hdr_base_phys, wctx->osd_hdr_size);    /*NA */
    FBDEV_CHECK_ERROR(!wctx->osd_hdr_base, /* nop */,
                      "fb(%d) osd_hdr_base vmap failed (0x%08x,%d)\n",
                      fb_dev_id, wctx->osd_hdr_base_phys, wctx->osd_hdr_size);

    wctx->osd_plte_base = vmap_phys(wctx->osd_plte_base_phys, wctx->osd_plte_size * sizeof(UINT32));
    FBDEV_CHECK_ERROR(!wctx->osd_plte_base, /* nop */,
                      "fb(%d) osd_plte_base vmap failed (0x%08x,%d)\n",
                      fb_dev_id, wctx->osd_plte_base_phys, wctx->osd_plte_size);

    /* initialize osd header */
    FBDEV_InitCanvas(wctx);

    return wctx;
err_exit:

    if (wctx)
    {
        FBDEV_CleanupLayer(wctx);
    }

    return NULL;
}

/** initialize layer's memory and palette.
 *
 * @param   struct fb_info *info
 * @return  void
 *
 */
void FBDEV_InitCanvas(FBDEV_WIN_CTX_T* wctx)
{
    CSC_INFORM_T csc_inform;
    ENDIAN_INFORM_T endian_inform;

    int fb_dev_id = wctx->fb_dev_id;
    struct scanvas* canvas = &wctx->pixel;
    LX_FBDEV_CFG_T* cfg = FBDEV_GET_CFG();

    /* configure OSD.
     * this function will inform OSD hardware to read OSD header data from the designated DDR ( canv->baddr )
     */
    FBDEV_InitOSDLayer(fb_dev_id);

    memset(&csc_inform, 0x0, sizeof(CSC_INFORM_T));
    memset(&endian_inform, 0x0, sizeof(ENDIAN_INFORM_T));

    /* set the default CSC param. but we use the fixed configuration. */
    csc_inform.bypass = 1;

    /* set OSD endian info. but we use the fixed configuration. */
    endian_inform = FBDEV_GetOSDImageEndian(cfg->fb[fb_dev_id].bits_per_pixel);

    FBDEV_WriteOSDEndian(fb_dev_id, &endian_inform);
    FBDEV_WriteOSDCSC(fb_dev_id, &csc_inform);

    /* initialize image data */
    canvas->fb_dev_id = fb_dev_id;
    canvas->fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW; // RAW image by default
    canvas->pixel_format = LX_FBDEV_PIXEL_FORMAT_RGB_8888; // ARGB by default

    canvas->osd_bm_paddr = wctx->fb_base_phys;
    canvas->prev_osd_bm_paddr = wctx->fb_base_phys;

    memset(&canvas->input_win, 0x0, sizeof(LX_RECT_T));
    memset(&canvas->output_win, 0x0, sizeof(LX_RECT_T));
    memset(&canvas->test_output_win, 0x0, sizeof(LX_RECT_T));

    canvas->input_win.w = cfg->fb[fb_dev_id].max_xres;  /* default input_win to be same as var->xres */
    canvas->input_win.h = cfg->fb[fb_dev_id].max_yres;  /* default input_win to be same as var->xres */
    canvas->output_win.w = cfg->fb[fb_dev_id].max_xres; /* default output_win to be same as var->xres */
    canvas->output_win.h = cfg->fb[fb_dev_id].max_yres; /* default output_win to be same as var->xres */

    canvas->reserver_screen_en = FALSE;
    canvas->pixel_order_en = FALSE;
    canvas->color_key_en = FALSE;
    canvas->blend_alpha_en = FALSE;
    canvas->global_alpha_en = cfg->fb[fb_dev_id].b_use_global_alpha;

    canvas->bits_per_pixel = cfg->fb[fb_dev_id].bits_per_pixel;
    canvas->stride = cfg->fb[fb_dev_id].max_xres * cfg->fb[fb_dev_id].bits_per_pixel / 8;

    canvas->global_alpha = 0xff;
    canvas->blend_alpha = 0xff;
    canvas->palette = (UINT32*) OS_Malloc(sizeof(UINT32) * 256);
}

/** memory freeing for each header.
 *
 * @param   dm_win_info **win - osd plane information
 * @return  int 0 : OK , -1 : NOT OK
 */
int FBDEV_CleanupLayer(FBDEV_WIN_CTX_T* wctx)
{
    if (wctx)
    {
        if (wctx->osd_hdr_base)
        {
            iounmap((void*)wctx->osd_hdr_base);
        }

        if (wctx->osd_hdr_base_phys)
        {
            release_mem_region(wctx->osd_hdr_base_phys, wctx->osd_hdr_size);
        }

        if (wctx->osd_plte_base_phys)
        {
            release_mem_region(wctx->osd_plte_base_phys, wctx->osd_plte_size);
        }

        kfree(wctx);
    }

    return (0);
}

/** initialize 'struct fb_info' of fb device based on the default param
 *  this function initializes 'struct var_screen_info' and 'struct fix_screen info'.
 *
 */
static void FBDEV_InitLinuxFrameBuffer(FBDEV_WIN_CTX_T* wctx, struct fb_var_screeninfo* default_vinfo, char* id)
{
    LX_FBDEV_CFG_T* cfg = FBDEV_GET_CFG();
    int fb_dev_id = wctx->fb_dev_id;
    struct fb_info* fbinfo = &(wctx->linux_fb_info);

    FBDEV_DEBUG("fb(%d) init FB variable\n", fb_dev_id);

    /* initialize the fb_info structure */
    // fbinfo->flags = FBINFO_DEFAULT;
    fbinfo->fbops = &lg115x_fbdev_fops;
    fbinfo->pseudo_palette = wctx->pseudo_palette;
    fbinfo->screen_base = (char*)(wctx->fb_base);
    fbinfo->screen_size = wctx->fb_size;
    fbinfo->par = (void*)wctx;

    /* initialize var_info */
    memcpy(&fbinfo->var, default_vinfo, sizeof(struct fb_var_screeninfo));

    fbinfo->var.reserved[0] = 0;
    fbinfo->var.reserved[1] = 0;
    fbinfo->var.reserved[2] = 0;
    fbinfo->var.reserved[3] = 0;

    /* initialize fix_info */
    strncpy(fbinfo->fix.id, id, sizeof(fbinfo->fix.id) - 1);

    fbinfo->fix.line_length = (fbinfo->var.xres_virtual * fbinfo->var.bits_per_pixel) / 8;
    fbinfo->fix.smem_start = wctx->fb_base_phys;
    fbinfo->fix.smem_len = wctx->fb_size;
    fbinfo->fix.type = FB_TYPE_PACKED_PIXELS;
    fbinfo->fix.visual = FB_VISUAL_TRUECOLOR;
    fbinfo->fix.xpanstep = 0;
    fbinfo->fix.ypanstep = 1;   // paning enable
    fbinfo->fix.ywrapstep = 0;
    fbinfo->fix.type_aux = 0;
    fbinfo->fix.mmio_start = 0x0;   // N/A
    fbinfo->fix.mmio_len = 0x100;   // N/A

    /* raxis.lim (2018/11/2) notify application to use AFBC pixel format */
    if (cfg->fb[fb_dev_id].b_use_afbc)
    {
        UINT32 accel_val = FB_ACCEL_LG_AFBC_1_0;

        accel_val = (g_afbc_version == FBDEV_HW_AFBC_VER_1_1) ? FB_ACCEL_LG_AFBC_1_1 : FB_ACCEL_LG_AFBC_1_0;

        fbinfo->fix.accel = accel_val;
    }

    /* DO NOT use capabilities, reserved because it is not working when 32 user & 64 kernel */

    FBDEV_NOTI
    ("fb(%d) linux.fb smem_start=0x%08x, smem_len=%d, accel=0x%x\n",
     fb_dev_id, (UINT32) fbinfo->fix.smem_start, (int)fbinfo->fix.smem_len, fbinfo->fix.accel);

    /* 이 함수 호출하면.. 각각의 fb0~fb 까지 생성이 되는데 */
    FBDEV_CHECK_ERROR(register_framebuffer(fbinfo) < 0, /* nop */,
                      "fb(%d) register failed\n", fb_dev_id);

    FBDEV_WriteOSDHeader(&wctx->pixel);
}

/*========================================================================================
    Implementation Group (IRQ)
========================================================================================*/

#ifdef USE_FBDEV_VSYNC_UEVENT
/** fbdev vsync uevent function */
static ssize_t vsync_show_event(struct device* dev, struct device_attribute* attr, char* buf)
{
    int ret;
    ULONG flags;

    vsync_ev_ctrl.vsync_irq_enabled = 1;    /* TEST: force enable vysnc event notifier !! */

    spin_lock_irqsave(&vsync_ev_ctrl.spinlock, flags);

    if (vsync_ev_ctrl.wait_vsync_cnt == 0)
    {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,13,0))
        reinit_completion(&vsync_ev_ctrl.event);
#else
        INIT_COMPLETION(vsync_ev_ctrl.event);
#endif
    }

    vsync_ev_ctrl.wait_vsync_cnt++;
    spin_unlock_irqrestore(&vsync_ev_ctrl.spinlock, flags);

    ret = wait_for_completion_interruptible(&vsync_ev_ctrl.event);

    if (ret != 0)
    {
        printk(KERN_ERR "interrupted?? %d\n", ret);
        return ret;
    }

    ret = snprintf(buf, PAGE_SIZE, "VSYNC=%llu\n", ktime_to_ns(vsync_ev_ctrl.vsync_time));

    if (ret > PAGE_SIZE)
    {
        ret = PAGE_SIZE;
    }

    return ret;
}
#endif

/** fbdev sync function.
 *
 * @param   void
 * @return  int
 *
 */
int FBDEV_SyncWithVsync(void)
{
    /* process application vsync every vsync_cnt_on_flip */
    if (++g_fbdev_vsync_counter % g_fbdev_vsync_cnt_on_flip)
    {
        FBDEV_VSYNC_DEBUG("<isr> fake vsync (%d)\n", g_fbdev_vsync_counter);
        return 0;
    }
    else
    {
        FBDEV_VSYNC_DEBUG("<isr> real vsync (%d)\n", g_fbdev_vsync_counter);
    }

    //FBDEV_DEBUG("vsync_counter=%8d (%d)\n", g_fbdev_vsync_counter, g_fbdev_vsync_counter % g_fbdev_vsync_cnt_on_flip);

    if (g_fbdev_cfg->b_use_irq)
    {
        int i;
        ULONG flags;
        FBDEV_WIN_CTX_T* wctx;

        spin_lock_irqsave(&g_fbdev_vsync_check_spinlock, flags);

        for (i = 0; i < FBDEV_MAX_DEVICE; i++)
        {
            wctx = FBDEV_GetWinCtx(i);

            if (wctx && wctx->vsync_cnt > 0)
            {
                wctx->vsync_cnt--;
            }
        }

        spin_unlock_irqrestore(&g_fbdev_vsync_check_spinlock, flags);

        /* notify vsync completion */
#ifdef USE_FBDEV_VSYNC_UEVENT

        if (vsync_ev_ctrl.vsync_irq_enabled)
        {
            ULONG flags;

            vsync_ev_ctrl.vsync_time = ktime_get();

            spin_lock_irqsave(&vsync_ev_ctrl.spinlock, flags);

            if (vsync_ev_ctrl.wait_vsync_cnt > 0)
            {
                complete_all(&vsync_ev_ctrl.event);
                vsync_ev_ctrl.wait_vsync_cnt = 0;
            }

            spin_unlock_irqrestore(&vsync_ev_ctrl.spinlock, flags);
        }

#endif

        wake_up_interruptible_all(&g_fbdev_vsync_wq);
    }

    /* tick osd_drm_helper */
    osd_drm_vsync_tick();

    return 0;
}

/** fbdev interrupt handler.
 *
 * @param   void
 * @return  int
 *
 */
static irqreturn_t FBDEV_ISRHandler(int irq, void* dev_id)
{
    UINT32 intr_status;
#ifdef USE_FBDEV_ISR_TIME_CHK
    ktime_t t;
    UINT64 ns[2];
    t = ktime_get();
    ns[0] = ktime_to_ns(t);
#endif
    /* read current ISR status */
    intr_status = FBDEV_GetInterruptStatus(ALL_INTR);

    if (g_fbdev_use_isr_mon)
    {
        static int b_first_vsync = 1;
        static UINT64 start_tick;

        FBDEV_ISR_DEBUG("osd ISR - status = 0x%x\n", intr_status);

        if (b_first_vsync)
        {
            b_first_vsync = 0;
            start_tick = OS_GetMsecTicks();
        }
        else
        {
            if (++g_fbdev_isr_chk_counter & 0xff00)     /* vsync count >= 256 */
            {
                UINT64 curr_tick = OS_GetMsecTicks();
                int diff_tick = (int)(curr_tick - start_tick);

                /* if DVB mode (50Hz) , ideal diff_tick will be 20.000 ms * 256 = 5120
                 * if DVB mode (48Hz) , ideal diff_tick will be 20.833 ms * 256 = 5333
                 * If UD  mode (30Hz) , local diff_tick will be 33.333 ms * 256 = 8532 ?
                 * else 60Hz
                 */
                if (g_fbdev_use_vsync_auto_tune)
                {
                    g_fbdev_vsync_timeout =
                        (diff_tick >=
                         8000) ? 33333 : (diff_tick >=
                                          5300) ? 20832 : (diff_tick >=
                                                           5000) ? 19999 : (diff_tick >=
                                                                   2200) ? 16666 : 8333;
                    g_fbdev_vsync_timeout += jiffies_to_usecs(1);
                }

                printk
                ("[osd] ISR - HZ=%d, max_vsync_timeout %d us (%d jiffies), diff_tm %d ms/256, avg_vsync %d.%d ms\n",
                 HZ, g_fbdev_vsync_timeout, (UINT32)
                 usecs_to_jiffies(g_fbdev_vsync_timeout), diff_tick, diff_tick / 256,
                 (diff_tick % 256) * 100 / 256);

                start_tick = curr_tick;
                g_fbdev_isr_chk_counter = 0;
            }
        }
    }
    else
    {
        if (++g_fbdev_isr_chk_counter & 0xff00)
        {
            g_fbdev_isr_chk_counter = 0;    /* vsync count >= 256 */
        }
    }

    /* ignore handler when there is not any OSD interrupt */
    if (intr_status == 0)
    {
        goto func_exit;
    }

    /* raxis.lim (2010/11/20) -- ignore interrupt service when FB doesn't use IRQ */
    if (!g_fbdev_cfg->b_use_irq)
    {
        FBDEV_SetInterruptClear(ALL_INTR);
        goto func_exit;
    }

#ifdef FBDEV_USE_FPS_MON
    FBDEV_MON_ISRTick();
#endif

    /* TODO (raxis.lim 2014/05/14) code fix for H15 ISR handler !! */
    if (lx_chip_rev() >= LX_CHIP_REV(H15, A0))
    {
        FBDEV_SetInterruptClear(ALL_INTR);
        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_VSYNC, NULL);
        FBDEV_SyncWithVsync();  /* call ISR callback */
    }
    else if (intr_status & (1 << MIXER_INTR))
    {
        FBDEV_SetInterruptClear(MIXER_INTR);
        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_VSYNC, NULL);
        FBDEV_SyncWithVsync();  /* call ISR callback */
    }

#ifdef USE_FBDEV_ISR_TIME_CHK
    t = ktime_get();
    ns[1] = ktime_to_ns(t);
    printk("fb intr tick = %d ns\n", (int)(ns[1] - ns[0]));
#endif

func_exit:
    return IRQ_HANDLED;
}

static void FBDEV_PseudoISRHandler(ULONG data)
{
    struct platform_device* pdev = &platform_device;
    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(pdev);

    // runtime pm suspend 상태에서만 pseudo vsync 생성토록 할것
    if (pdev_ctx && !pdev_ctx->is_runtime_active)
    {
#ifdef FBDEV_USE_FPS_MON
        FBDEV_MON_ISRTick();
#endif
        FBDEV_SyncWithVsync();
    }
}

/*========================================================================================
    Implementation Group
========================================================================================*/
/**
 *
 * module remove function. this function will be called in insmod fbdev module.
 *
 * @param   struct platform_device
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void FBDEV_remove(struct platform_device* pdev)
#else
static int FBDEV_remove(struct platform_device* pdev)
#endif
{
    FBDEV_DEBUG("released\n");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
    // void, do nothing
#else
    return 0;
#endif
}

/**
 *
 * module remove function. this function will be called in insmod fbdev module.
 *
 * @param   struct device
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static void FBDEV_release(struct device* dev)
{
    FBDEV_DEBUG("released\n");
}

/*========================================================================================
    Implementation Group (Intializer)
========================================================================================*/

/* initialize all variable of FB device */
static void FBDEV_InitVar(void)
{
    memset(&g_fbdev_frc_ctrl, 0x0, sizeof(FBDEV_FRC_CTRL_T));   /* clear FRC */
    memset(&g_fbdev_hw_ctx, 0x0, sizeof(FBDEV_HW_CTX_T));   /* clear HW Ctx */
    memset(g_dm_ctx, 0x0, sizeof(FBDEV_CTX_T)); /* celar dm_ctx */
}

static void FBDEV_InitHWCtx(void)
{
    int i;

    /* initialize HW Ctx (Hardware Abstraction Layer) */
    switch (lx_chip())
    {
#ifdef INCLUDE_M17_CHIP_KDRV

        case LX_CHIP_M17:
        {
            FBDEV_M17_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif
#ifdef INCLUDE_O18_CHIP_KDRV

        case LX_CHIP_O18:
        {
            FBDEV_O18_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif
#ifdef INCLUDE_M19_CHIP_KDRV

        case LX_CHIP_M19:
        {
            FBDEV_M19_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif
#ifdef INCLUDE_O20_CHIP_KDRV

        case LX_CHIP_O20:
        {
            printk("O20 kdriver\n");
            FBDEV_O20_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif
#ifdef INCLUDE_E60_CHIP_KDRV

        case LX_CHIP_E60:
        {
            printk("E60 kdriver\n");
            FBDEV_E60_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV

        case LX_CHIP_O22:
        {
            printk("O22 kdriver\n");
            FBDEV_O22_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif

#ifdef INCLUDE_M23_CHIP_KDRV

        case LX_CHIP_M23:
        {
            printk("M23 kdriver\n");
            FBDEV_M23_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif

#ifdef INCLUDE_O24_CHIP_KDRV

        case LX_CHIP_O24:
        {
            printk("O24 kdriver\n");
            FBDEV_O24_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif

#ifdef INCLUDE_O26_CHIP_KDRV

        case LX_CHIP_O26:
        {
            printk("O26 kdriver\n");
            FBDEV_O26_InitHWCtx(&g_fbdev_hw_ctx);
        }
        break;
#endif

        default:
        {
            DBG_PRINT_ERROR("unknown chip 0x%x\n", lx_chip_rev());
        }
        break;
    }

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        g_fbdev_hw_ctx.fb[i].trid_ctrl.mode = LX_FBDEV_TRID_MODE_NONE;
        g_fbdev_hw_ctx.fb[i].trid_ctrl.disparity = 0x0;
    }

    // get supported AFBC version & init afbc_sw context
    {
        FBDEV_HW_CMD_DATA_T cmd_data;
        struct afbc_ctx afbc_ctx;

        if (RET_OK == FBDEV_ExecHWCommand(FBDEV_HW_CMD_RD_AFBC_CAPS, &cmd_data))
        {
            g_afbc_version = cmd_data.gen[0];
            printk("osd.afbc_ver=0x%x\n", g_afbc_version);
        }

        afbc_ctx = afbc_sw_init_context((g_afbc_version == FBDEV_HW_AFBC_VER_AFRC) ? AFBC_SW_VER_AFRC :
                                        (g_afbc_version == FBDEV_HW_AFBC_VER_1_1) ? AFBC_SW_VER_1_1 :
                                        (g_afbc_version == FBDEV_HW_AFBC_VER_1_0) ? AFBC_SW_VER_1_0 : AFBC_SW_VER_NONE);

        printk("osd.fbc_fmt=%s,version=%s\n", afbc_sw_get_fbc_fmt_string(&afbc_ctx), afbc_sw_get_version_string(&afbc_ctx));

        afbc_sw_set_default_context(&afbc_ctx);
    }
}

/** initialize basic configuration for FB device.
 *  [note] this function is called before the real device intialization
 *
 */
void FBDEV_PreInit(void)
{
    FBDEV_InitVar();    /* initialize variable */
    FBDEV_InitHWCtx();  /* initialize HW context */
    FBDEV_InitCfg();    /* initialize configuration */
}

extern void DE_IO_AddListener(void (*fn)(unsigned long));

/** TODO: re-implement it */
void FBDEV_EventListener(unsigned long evnt_type)
{
    switch (evnt_type)
    {
        case 0x0:       /* DE firmware will be loaded */
        {
            (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_IO_PQE_FW_LOAD_DONE, NULL);
        }
        break;

        default:
            break;
    }
}

bool no_fbdev;
module_param(no_fbdev, bool, 0644);
EXPORT_SYMBOL(no_fbdev);

/* module initial function. this function will be called in insmod fbdev module. */
int FBDEV_Init(void)
{
    if (no_fbdev)
    {
        printk(KERN_INFO "%s.%d: donot use fbdev.\n", __func__, __LINE__);
        return 0;
    }

    /* open debug(logm) handler */
    g_fbdev_debug_fd = DBG_OPEN(FBDEV_MODULE);

    if (g_fbdev_debug_fd < 0)
    {
        return RET_ERROR;
    }

    OS_DEBUG_EnableModuleByIndex(g_fbdev_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED);
    OS_DEBUG_EnableModuleByIndex(g_fbdev_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_YELLOW);
    OS_DEBUG_EnableModuleByIndex(g_fbdev_debug_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_YELLOW);

#if CONFIG_LX_BOARD_FPGA
    //OS_DEBUG_EnableModuleByIndex( g_fbdev_debug_fd, LX_LOGM_LEVEL_DEBUG,  DBG_COLOR_YELLOW );
    OS_DEBUG_EnableModuleByIndex(g_fbdev_debug_fd, LX_LOGM_LEVEL_INFO, DBG_COLOR_YELLOW);

    /* enable full log for FPGA debug */
    g_fbdev_use_boot_debug = 1;
    g_fbdev_use_hw_debug = 1;
#endif

    if (g_fbdev_use_boot_debug)
    {
        OS_DEBUG_EnableModuleByIndex(g_fbdev_debug_fd, 10 /*BOOT*/, DBG_COLOR_NONE);
    }

    if (g_fbdev_use_hw_debug)
    {
        OS_DEBUG_EnableModuleByIndex(g_fbdev_debug_fd, 11 /*HW0 */,
                                     DBG_COLOR_NONE);
        OS_DEBUG_EnableModuleByIndex(g_fbdev_debug_fd, 12 /*HW1 */,
                                     DBG_COLOR_NONE);
        OS_DEBUG_EnableModuleByIndex(g_fbdev_debug_fd, 13 /*HW2 */,
                                     DBG_COLOR_NONE);
    }

    //OS_DEBUG_EnableModuleByIndex( g_fbdev_debug_fd, 31 /*USER_FLIP */,            DBG_COLOR_NONE );

    FBDEV_PostInitCfg();

#ifndef MODULE
    {
        char* option = NULL;

        /* name register */
        FBDEV_CHECK_ERROR(RET_OK != fb_get_options("lg115x_fb", &option), return -ENODEV,
                          "get fb_get_option fail\n");
        FBDEV_setup(option);
    }
#endif
    FBDEV_CHECK_ERROR(platform_driver_register(&platform_driver) < 0, return RET_ERROR, "platform drv reg fail\n");
    FBDEV_CHECK_ERROR(platform_device_register(&platform_device) != RET_OK,
                      return RET_ERROR, "platform dev reg fail\n");

    /* enable PM runtime */
    pm_runtime_set_active(&platform_device.dev);
    pm_runtime_enable(&platform_device.dev);
    /* set control mode to "on" not "auto" */
    pm_runtime_forbid(&platform_device.dev);

    /* add more initialization */
    FBDEV_PROC_Init();
#ifdef FBDEV_USE_FPS_MON
    FBDEV_MON_Init();
#endif

    // initialize pseudo vsync generator for the DRM core
    OS_InitTimer(&g_pseudo_vsync_timer);

    /* initialize render event structure */
    memset(&render_ev_ctrl, 0x0, sizeof(FBDEV_RENDER_EVENT_T));
    init_completion(&render_ev_ctrl.event);

    spin_lock_init(&render_ev_ctrl.spinlock);

#ifdef INCLUDE_KDRV_DE
    DE_IO_AddListener(FBDEV_EventListener);
#endif

#ifdef INCLUDE_KDRV_PQE_PM
    g_pqe_pm_id = pqe_pm_register(&g_pqe_pm_cfg);
    FBDEV_CHECK_ERROR(g_pqe_pm_id < 0, /* nop */,
                      "pqe_pm register error\n");
#endif

    return RET_OK;
}

/* module remove function. this function will be called in rmmod fbdev module. */
void FBDEV_Cleanup(void)
{
    int i;

    FBDEV_PROC_Cleanup();

    // register memory release
    FBDEV_ExitHardware();

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        FBDEV_WIN_CTX_T* win_ctx = FBDEV_GetWinCtx(i);

        if (win_ctx)
        {
            struct fb_info* info = &win_ctx->linux_fb_info;

            if (info)
            {
                unregister_framebuffer(info);
            }

            FBDEV_CleanupLayer(win_ctx);
        }
    }

    platform_driver_unregister(&platform_driver);
    platform_device_unregister(&platform_device);

    FBDEV_NOTI("cleanup\n");
}

/*========================================================================================
    Implementation Group (suspend/resume)
========================================================================================*/
#define MAX_BK_SURF     400 /* FIXME: 400 is enough */

typedef struct
{
#define FBDEV_FBMEM_BKUP_IMG_NONE   0x00
#define FBDEV_FBMEM_BKUP_IMG_POSD   0x01
    UINT32 attrib;
    UINT32 phys_addr;
    UINT32 length;
    void* virt_img;
} FBDEV_FBMEM_BKUP_IMG_T;

static UINT32 fbmem_bkup_num = 0;
static FBDEV_FBMEM_BKUP_IMG_T* fbmem_bkup_list = NULL;

/** save fbmem to kernel memory and reutrn it */
static void* FBDEV_SaveFBImage(UINT32 fbmem_addr, UINT32 length)
{
    OS_CACHE_MAP_T cmap;
    void* virt_img = NULL;

    virt_img = vmalloc(length);
    FBDEV_CHECK_ERROR(virt_img == NULL, return NULL, "can't vmalloc %d\n", length);

    OS_OpenCacheMap(&cmap, (ULONG) fbmem_addr, length);
    OS_InvalCacheMap(&cmap, 0x0, length);

    memcpy((void*)virt_img, (void*)cmap.virt_addr, length);
    OS_CloseCacheMap(&cmap);

    FBDEV_DEBUG("fbmem backup ok. paddr 0x%x, virt_img 0x%p, length %d\n", fbmem_addr, virt_img, length);
    return virt_img;
}

#ifdef FBDEV_SUPPORT_OSD_BKUP
#ifdef FBDEV_SUPPORT_OSD_CLEAR_ON_BKUP
static void* FBDEV_ClearFBImage(UINT32 fbmem_addr, UINT32 length)
{
    void* virt_img = NULL;

    virt_img = vmalloc(length);
    FBDEV_CHECK_ERROR(virt_img == NULL, return NULL, "can't vmalloc %d\n", length);

    memset((void*)virt_img, 0x0, length);

    FBDEV_DEBUG("fbmem clear ok. paddr 0x%x, virt_img 0x%p, length %d\n", fbmem_addr, virt_img, length);
    return virt_img;
}
#endif
#endif

/** restore fbmem with kernel memory */
static void FBDEV_RestoreFBImage(UINT32* virt_img, UINT32 fbmem_addr, UINT32 length, BOOLEAN b_restore_fb)
{
    OS_CACHE_MAP_T cmap;

    FBDEV_CHECK_ERROR(virt_img == NULL, return, "virt_img NULL\n");
    FBDEV_CHECK_ERROR(fbmem_addr == 0x0, return, "phys_addr NULL\n");
    FBDEV_CHECK_ERROR(length == 0, return, "length zero\n");

    if (b_restore_fb)
    {
        OS_OpenCacheMap(&cmap, (ULONG) fbmem_addr, length);
        memcpy((void*)cmap.virt_addr, (void*)virt_img, length);

        OS_CleanCacheMap(&cmap, 0x0, length);
        OS_CloseCacheMap(&cmap);

        FBDEV_DEBUG("fbmem resotre ok. paddr 0x%x, virt_img 0x%p, length %d\n", fbmem_addr, virt_img, length);
    }

    vfree(virt_img);
}

void FBDEV_BackupFBList(void)
{
#ifdef INCLUDE_KDRV_GFX
    int i;
    UINT32 fb_len;
    UINT32* virt_img;
    LX_GFX_SURFACE_SETTING_T surf_info;

    int bk_img_idx = 0;
    int fail_cnt = 0;
    int num_surf = 0;
    int* surf_fd_list = NULL;

    /* if backup is already done, abort request. this can't be happended in the real app */
    FBDEV_CHECK_ERROR(fbmem_bkup_list, return, "fbmem_bkup_list is NOT NULL\n");

    gfx_export_lock_device();

    surf_fd_list = vmalloc(MAX_BK_SURF * sizeof(int));
    FBDEV_CHECK_ERROR(NULL == surf_fd_list, goto func_exit,
                      "can't alloc surf_fd_list. sz=%d\n", MAX_BK_SURF * (int)sizeof(int));

    gfx_export_get_surface_list(surf_fd_list, MAX_BK_SURF, &num_surf);
    FBDEV_CHECK_ERROR(0 == num_surf, goto func_exit, "num_surf zero\n");
    FBDEV_DEBUG("max actvie surf num = %d\n", num_surf);

    /* alloc fbmem holder */
    fbmem_bkup_list = vmalloc(num_surf * sizeof(FBDEV_FBMEM_BKUP_IMG_T));
    FBDEV_CHECK_ERROR(NULL == fbmem_bkup_list, goto func_exit,
                      "can't alloc fbmem_bkup_list.sz=%d\n", num_surf * (int)sizeof(FBDEV_FBMEM_BKUP_IMG_T));

#ifdef FBDEV_SUPPORT_OSD_BKUP

    /* save graphic frame buffer (fb0 ~ fb2) */
    for (i = 0; i < LX_FBDEV_GFX_PLANE_MAX; i++)
    {
        int clear_en = 0;
        FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(i);

        // (2022/08/16) prevent AFBC lockup
        // http://clm.lge.com/issue/browse/SDMSTH-318, http://clm.lge.com/issue/browse/SDMSTH-311
        // fb(1) 에 대한 OSD 백업이 이루어지지 않을시, snapshot boot 이후 초기화되지 않은 형태의 AFBC 데이터로
        // 인하여, AFBC decoder 가 멈추는 (복구 불가능한) 상태가 될 수 있음. 따라서 fb(0), fb(1) 은 osd on/off
        // 상태와 무관하게 백업이 될 수 있도록 조치한다.
#if 0
        FBDEV_CHECK_DEBUG(FALSE == FBDEV_GetOSDEnable(i), continue, "fb(%d) off, skip save framebuffer\n", i);
#endif

#ifdef FBDEV_SUPPORT_OSD_CLEAR_ON_BKUP
        clear_en = 1;
        virt_img = FBDEV_ClearFBImage((UINT32) wctx->fb_base_phys, wctx->fb_size);
#else
        virt_img = FBDEV_SaveFBImage((UINT32) wctx->fb_base_phys, wctx->fb_size);
#endif
        FBDEV_CHECK_ERROR(NULL == virt_img, fail_cnt++; continue, "can't save fb(%d)\n", i);

        fbmem_bkup_list[bk_img_idx].attrib = FBDEV_FBMEM_BKUP_IMG_POSD;
        fbmem_bkup_list[bk_img_idx].virt_img = virt_img;
        fbmem_bkup_list[bk_img_idx].phys_addr = (UINT32) wctx->fb_base_phys;
        fbmem_bkup_list[bk_img_idx].length = wctx->fb_size;

        FBDEV_NOTI("%s posd fb(%d) ok. paddr 0x%x, len %d\n",
                   (clear_en) ? "clear" : "save", i, fbmem_bkup_list[bk_img_idx].phys_addr, wctx->fb_size);
        bk_img_idx++;
    }

#endif

#ifdef FBDEV_SUPPORT_CRSR_BKUP

    /* save cursor frame buffer by reading GFX surface list */
    for (i = 0; i < num_surf; i++)
    {
        int rc = gfx_export_get_surface_info(surf_fd_list[i], &surf_info);
        FBDEV_CHECK_ERROR(RET_OK != rc, continue, "can't get surf fd 0x%x\n", surf_fd_list[i]);

        if (surf_info.width <= 256 && surf_info.height <= 256)
        {
            fb_len = surf_info.stride * surf_info.height;
            virt_img = FBDEV_SaveFBImage((UINT32) surf_info.phys_addr, fb_len);
            FBDEV_CHECK_ERROR(NULL == virt_img, fail_cnt++; continue, "can't save fb(%d)\n", i);

            fbmem_bkup_list[bk_img_idx].attrib = FBDEV_FBMEM_BKUP_IMG_NONE;
            fbmem_bkup_list[bk_img_idx].virt_img = virt_img;
            fbmem_bkup_list[bk_img_idx].phys_addr = (UINT32) surf_info.phys_addr;
            fbmem_bkup_list[bk_img_idx].length = fb_len;
            bk_img_idx++;
        }
    }

#endif

    fbmem_bkup_num = bk_img_idx;
    FBDEV_NOTI("total %d image saved. fail_cnt %d\n", fbmem_bkup_num, fail_cnt);
func_exit:

    if (surf_fd_list)
    {
        vfree(surf_fd_list);
    }

    gfx_export_unlock_device();
#endif
}

void FBDEV_RestoreFBList(const char* snap_boot_mode)
{
    int i;

    BOOLEAN b_restore_fb = TRUE;

    FBDEV_CHECK_ERROR(NULL == fbmem_bkup_list, return, "fbmem_bkup_list NULL\n");
    FBDEV_CHECK_ERROR(0 == fbmem_bkup_num, return, "fbmem_bkup_num  zero\n");

    FBDEV_DEBUG("restoring %d fbimg\n", fbmem_bkup_num);

#ifdef INCLUDE_KDRV_GFX
    gfx_export_lock_device();
#endif

    // (2021/07/21)
    // framebuffer should be restored only when snap_boot_mode is "restore".
    // please remove the below checker if runtime spec is changed
    if (snap_boot_mode && strncmp(snap_boot_mode, "restore", 7))
    {
        FBDEV_NOTI("<!> ignore FB restore - mode=%s\n", snap_boot_mode);
        b_restore_fb = FALSE;
    }
    else
    {
        FBDEV_NOTI("<!> run FB restore - mode=%s\n", snap_boot_mode);
    }

    /* FIRST, resotre all saved surface regardless of any clear policy */
    for (i = 0; i < fbmem_bkup_num; i++)
    {
        FBDEV_RestoreFBImage(fbmem_bkup_list[i].virt_img,
                             fbmem_bkup_list[i].phys_addr, fbmem_bkup_list[i].length, b_restore_fb);
    }

    FBDEV_NOTI("total %d image restored\n", fbmem_bkup_num);

#ifdef FBDEV_SUPPORT_FBC_IMG_CLEAR_ON_RESTORE
    /* clear AFBC image in GFX surface list if necessary */
#ifdef INCLUDE_KDRV_GFX

    if (b_restore_fb)
    {
        int i;
        LX_GFX_SURFACE_SETTING_T surf_info;
        int cnt = 0;
        int* surf_fd_list = NULL;
        int num_surf = 0;

        surf_fd_list = vmalloc(MAX_BK_SURF * sizeof(int));
        FBDEV_CHECK_ERROR(NULL == surf_fd_list, goto osd_clear_exit,
                          "can't alloc surf_fd_list. sz=%d\n", MAX_BK_SURF * (int)sizeof(int));

        gfx_export_get_surface_list(surf_fd_list, MAX_BK_SURF, &num_surf);
        FBDEV_CHECK_ERROR(0 == num_surf, goto osd_clear_exit, "num_surf zero\n");

        FBDEV_NOTI("FBC surface clear - start. active surf_num=%d\n", num_surf);

        for (i = 0; i < num_surf; i++)
        {
            FBDEV_CHECK_ERROR(RET_OK != gfx_export_get_surface_info(surf_fd_list[i], &surf_info),
                              goto osd_clear_exit, "can't get surf fd 0x%x\n", surf_fd_list[i]);

            FBDEV_FIXME("FIXME: GFX 에 AFBC 정보가 있다면, AFRC 도 있어야 하는건가 ?")

            if (surf_info.pixel_format == LX_GFX_PIXEL_FORMAT_ARGB8888_AFBC)
            {
                struct afbc_framebuffer* afbc_fb = afbc_sw_alloc_framebuffer(NULL,
                                                   surf_info.phys_addr,
                                                   surf_info.width,
                                                   surf_info.height,
                                                   0,
                                                   0,
                                                   0);

                FBDEV_DEBUG("(%3d) surf info (%4dx%4d, 0x%04x)\n",
                            i, surf_info.width, surf_info.height, surf_info.pixel_format);

                if (afbc_fb)
                {
                    afbc_sw_fill(NULL, afbc_fb, 0x00000000);
                    afbc_sw_free_framebuffer(NULL, afbc_fb);

                    cnt++;
                }
            }
        }

osd_clear_exit:
        FBDEV_NOTI("FBC surface clear - end. cnt=%d\n", cnt);

        if (surf_fd_list)
        {
            vfree(surf_fd_list);
        }
    }

    vfree(fbmem_bkup_list);
    fbmem_bkup_list = NULL;
    fbmem_bkup_num = 0;

#ifdef INCLUDE_KDRV_GFX
    gfx_export_unlock_device();
#endif
#endif
#endif

#ifdef FBDEV_SUPPORT_OSD_CLEAR_ON_RESTORE

    /* raxis.lim (2019/10/15) -- linux framebuffer(OSD) should be also cleared if necessary
     * refer to http://clm.lge.com/issue/browse/SICDTV-7460 and QEVENTTWEN- issues.
     */
    if (b_restore_fb)
    {
        int fb_dev_id;

        for (fb_dev_id = 0; fb_dev_id < LX_FBDEV_ID_MAX; fb_dev_id++)
        {
            LX_FBDEV_CFG_T* cfg = FBDEV_GET_CFG();
            FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(fb_dev_id);

            if (wctx->linux_fb_mode)
            {
                if (cfg->fb[fb_dev_id].b_active && cfg->fb[fb_dev_id].b_use_afbc
                        && !cfg->fb[fb_dev_id].b_cursor)
                {
                    int j;
                    int fb_bufnum = cfg->fb[fb_dev_id].max_buf_num;
                    int fb_xres = cfg->fb[fb_dev_id].max_xres;
                    int fb_yres = cfg->fb[fb_dev_id].max_yres;

                    int fbmem_size = afbc_sw_get_image_size(NULL, fb_xres, fb_yres);

                    for (j = 0; j < fb_bufnum; j++)
                    {
                        struct afbc_framebuffer* afbc_fb = afbc_sw_alloc_framebuffer(NULL,
                                                           wctx->fb_base_phys + fbmem_size * j,
                                                           fb_xres,
                                                           fb_yres,
                                                           0,
                                                           0,
                                                           0);

                        if (afbc_fb)
                        {
                            afbc_sw_fill(NULL, afbc_fb, 0x00000000);
                            afbc_sw_free_framebuffer(NULL, afbc_fb);
                        }
                    }

                    FBDEV_NOTI("fb(%d) linuxfb/afbc surface (%d/%d) clear : size=%dx%d, phys=%08x, len=%d\n",
                               fb_dev_id, j, fb_bufnum, fb_xres, fb_yres, wctx->fb_base_phys,
                               wctx->fb_size);
                }
            }
            else
            {
                /* do nothing in ARGB mode */
            }
        }
    }

#endif
}

void FBDEV_PMTest(const char* cmd)
{
    if (!strncmp(cmd, "freeze", 6))
    {
        FBDEV_freeze(&platform_device.dev);
    }
    else if (!strncmp(cmd, "thaw", 4))
    {
        FBDEV_thaw(&platform_device.dev);
    }
    else if (!strncmp(cmd, "restore", 7))
    {
        FBDEV_restore(&platform_device.dev);
    }
    else if (!strncmp(cmd, "suspend", 7))
    {
        FBDEV_suspend(&platform_device.dev);
    }
    else if (!strncmp(cmd, "resume", 6))
    {
        FBDEV_resume(&platform_device.dev);
    }
}

/** SNAPSHOT-suspend
 *
 */
static int FBDEV_freeze(struct device* dev)
{
#ifdef KDRV_CONFIG_PM_FBDEV
    int i;
    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));
    FBDEV_CHECK_ERROR(!pdev_ctx, return RET_ERROR, "invalid pdev\n");

    printk("FBDEV - SNAPSHOT SUSPEND(FREEZE)\n");

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_PREPARE_FREEZE, NULL);

    /* backup visible status */
    pdev_ctx->hybernation.visible_status_backup = 0x0;

    for (i = 0; i < FBDEV_MAX_DEVICE; i++)
    {
        if (g_fbdev_cfg->fb[i].b_active)
        {
            pdev_ctx->hybernation.visible_status_backup |= FBDEV_GetOSDEnable(i) ? (1 << i) : 0x0;
        }
    }

    FBDEV_BackupFBList();

    // for safe operation (optional)
    FBDEV_NOTI("stop pseudo vsync timer (optional)\n");
    OS_StopTimer(&g_pseudo_vsync_timer);

    /* run HW handler if nessesary */
    FBDEV_RunSuspend();

    pdev_ctx->is_suspend = 1;

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_COMPLETE, NULL);
    printk("FBDEV - SNAPSHOT SUSPEND(FREEZE) DONE\n");
#endif
    return RET_OK;
}

/** SNAPSHOT-resume right after making snapshot image
 *
 */
static int FBDEV_thaw(struct device* dev)
{
    printk("FBDEV - SNAPSHOT THAW(RESUME)\n");
    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_PREPARE_THAW, NULL);

    /* raxis.lim (2016/07/28) -- just clear the image backup memory. DO NOT re-initialize OSD SW/HD */
    FBDEV_RestoreFBList("thaw");

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_COMPLETE, NULL);
    printk("FBDEV - SNAPSHOT THAW(RESUME) DONE\n");

    return RET_OK;
}

/** resume module.
 *
 */
static int FBDEV_restore(struct device* dev)
{
#ifdef KDRV_CONFIG_PM_FBDEV
    int i;
    BOOLEAN layer_onoff;
    FBDEV_WIN_CTX_T* wctx;
    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));
    FBDEV_CHECK_ERROR(!pdev_ctx, return RET_ERROR, "invalid pdev\n");

    printk("FBDEV - SNAPSHOT BOOT\n");

    FBDEV_CHECK_ERROR(pdev_ctx->is_suspend == 0, return RET_ERROR, "FBDEV - resume FAIL\n");

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_PREPARE_RESTORE, NULL);

    FBDEV_RestoreFBList("restore");

    /* initialize some control variables before HW initialization */
#if (CONFIG_LX_BOOT_LOGO==1)

    for (i = 0; i < FBDEV_MAX_DEVICE; i++)
    {
        if (!g_fbdev_cfg->fb[i].b_active)
        {
            continue;
        }

        wctx = FBDEV_GetWinCtx(i);

        if (wctx)
        {
            wctx->status.b_osd_hdr_flush = FALSE;   /* freeze osd header to keep boot logo shown */
        }
    }

#endif

    /* snapshot boot should consider that OSD keeps the boot logo as cold boot */
    wctx = FBDEV_GetWinCtx(LX_FBDEV_ID_OSD0);

    if (wctx)
    {
        wctx->status.fb_pan_disp_cnt = 0;
        wctx->status.fb_flip_cnt = 0;
        wctx->pixel.fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW;
    }

    /* run HW handler */
    FBDEV_RunResume();

    /* write osd header again to restore the previous state */
    for (i = 0; i < FBDEV_MAX_DEVICE; i++)
    {
        if (!g_fbdev_cfg->fb[i].b_active)
        {
            continue;
        }

        wctx = FBDEV_GetWinCtx(i);
        FBDEV_CHECK_ERROR(NULL == wctx, /* nop */,
                          "fb(%d) win ctx NULL\n", i);

        if (wctx)
        {
            layer_onoff = (pdev_ctx->hybernation.visible_status_backup & (1 << i)) ? TRUE : FALSE;

            /* raxis.lim (2014/10/18)
             * We prefer osd freeze OFF for cursor layer when it is ON !!
             * This will remove the garbage screen due to unitialized POSD3 ON.
             * TODO: it's reasonable to disable the resume timer when IBOOT is activated
             */
            if (i == LX_FBDEV_ID_CSR0 && layer_onoff)
            {
                wctx->status.b_osd_hdr_flush = TRUE;
            }

            /* raxis.lim (2018/04/09) -- set the default window control mode
             * output window is set to full-sized screen every off/on time
             */
            wctx->pixel.user_win_ctrl_en = FALSE;

            FBDEV_SetOSDImageEndian(i, wctx->pixel.bits_per_pixel);
            FBDEV_WriteOSDHeader(&wctx->pixel);

            FBDEV_SetOSDEnable(i, layer_onoff);
        }
    }

    pdev_ctx->is_suspend = 0;

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_COMPLETE, NULL);
    printk("FBDEV - SNAPSHOT BOOT DONE\n");
#endif
    return RET_OK;
}

/** IBOOT suspend handler
 *
 *
 */
static int FBDEV_suspend(struct device* dev)
{
    int i;
    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));
    FBDEV_CHECK_ERROR(!pdev_ctx, return RET_ERROR, "invalid pdev\n");

    printk("FBDEV - IBOOT SUSPEND !!\n");

    // backup visible status
    //
    // (2021/06/23)
    // O22 의 경우 PREPARE_SUSPEND 핸들러에서 OSD 를 off 시킨다. 따라서 view status 백업 작업을
    // 미리 진행해야 한다.
    //
    // view_status 를 잘못 처리하는 경우 FBDEV_resume 에서 OSD view status 가 복원되지 않는 문제는 물론,
    // OSD off 가 됨으로써 runtime_pm suspend 가 강제로 발동되는 상황도 발생한다.
    //
    // 참조 http://clm.lge.com/issue/browse/SCDBR-4694?focusedCommentId=3174252&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3174252
    //
    pdev_ctx->hybernation.visible_status_backup = 0x0;

    for (i = 0; i < FBDEV_MAX_DEVICE; i++)
    {
        if (!g_fbdev_cfg->fb[i].b_active)
        {
            continue;
        }

        pdev_ctx->hybernation.visible_status_backup |= FBDEV_GetOSDEnable(i) ? (1 << i) : 0x0;
    }

    FBDEV_NOTI("backup view_status=0x%02x\n", pdev_ctx->hybernation.visible_status_backup);

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_PREPARE_SUSPEND, NULL);

    // for safe operation (optional)
    FBDEV_NOTI("stop pseudo vsync timer (optional)\n");
    OS_StopTimer(&g_pseudo_vsync_timer);

    /* stop interrupt */
    FBDEV_SetInterruptEnable(MIXER_INTR, 0);

    /* DON'T backup OSD image because all DDRs are alive */

    /* run HW handler if nessesary */
    FBDEV_RunSuspend();

    pdev_ctx->is_suspend = 1;

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_COMPLETE, NULL);
    printk("FBDEV - IBOOT SUSPEND END !!\n");

    return RET_OK;
}

/** IBOOT-resume
 *
 *  구현스펙)
 *  (1) framebuffer 의 모든 내용이 DDR 에 남아 있기 때문에, framebuffer 에 백업/복원은 하지 않는다.
 *  (2) chip kdriver 에서 resume 을 인지할 수 있도록 코드의 시작 부분에
 *      FBDEV_HW_CMD_WR_PM_PREPARE_RESUME 을 전달, 코드 후반부에 FBDEV_HW_CMD_WR_PM_COMPLETE 를 전달한다.
 *
 *  (3) QSM+ resume 시에는 lazy init 를 사용하지 않고, 즉시 resume 핸들러에서 모든 OSD 설정 및 PQ FW 에
 *      noti 가 갈 수 있도록 한다.
 *
 *  (4) lazy init 플로우를 탈수 있도록 하기 위하여
 *      FBDEV_HW_CMD_WR_USER_INITCALL_PREPARE -> HW 초기화 -> FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE
 *      순서대로 진행하도록 한다.
 *
 *  (5) fb_flip_cnt 를 강제로 1로 설정하여 추후 불필요한 lazy init 가 발동되지 않도록 한다.
 *
 */
static int FBDEV_resume(struct device* dev)
{
#ifdef KDRV_CONFIG_PM_FBDEV
    int i;
    BOOLEAN layer_onoff;
    FBDEV_WIN_CTX_T* wctx;
    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));
    FBDEV_CHECK_ERROR(!pdev_ctx, return RET_ERROR, "invalid pdev\n");

    printk("FBDEV - IBOOT RESUME\n");

    FBDEV_CHECK_ERROR(pdev_ctx->is_suspend == 0, return RET_ERROR, "FBDEV - resume FAIL\n");

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_PREPARE_RESUME, NULL);

    /* restart interrupt */
    FBDEV_SetInterruptEnable(MIXER_INTR, 1);

    /* run HW handler */
    FBDEV_RunResume();

#ifdef FBDEV_USE_USER_INITCALL_ON_RESUME
    /* (2020/06/11) -- pre processing part of lazy osd init */
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;
        hw_cmd.gen[0] = LX_FBDEV_ID_OSD0;

        FBDEV_NOTI("fb(%d) first flip_update (prepare) /w force mode !! \n", LX_FBDEV_ID_OSD0);
        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_USER_INITCALL_PREPARE, &hw_cmd);
    }
#endif

    FBDEV_NOTI("restore view_status=0x%02x\n", pdev_ctx->hybernation.visible_status_backup);

    layer_onoff = (pdev_ctx->hybernation.visible_status_backup & (1 << i)) ? TRUE : FALSE;

    /* write osd header again to restore the previous state */
    for (i = 0; i < FBDEV_MAX_DEVICE; i++)
    {
        if (!g_fbdev_cfg->fb[i].b_active)
        {
            continue;
        }

        wctx = FBDEV_GetWinCtx(i);
        FBDEV_CHECK_ERROR(NULL == wctx, /* nop */,
                          "fb(%d) win ctx NULL\n", i);

        if (wctx)
        {
            /* (2020/06/11) -- activate user_initcall now regardless of user frame update */
#ifdef FBDEV_USE_USER_INITCALL_ON_RESUME
            wctx->status.fb_flip_cnt = 1;
#else
            wctx->status.fb_flip_cnt = 0;
#endif
            wctx->status.fb_pan_disp_cnt = 0;

            layer_onoff = (pdev_ctx->hybernation.visible_status_backup & (1 << i)) ? TRUE : FALSE;
            FBDEV_DEBUG("fb(%d) enable OSD flush now. osd status <%s>\n", i, (layer_onoff) ? "ON" : "OFF");

            /* raxis.lim (2018/04/09) -- set the default window control mode
             * output window is set to full-sized screen every off/on time
             */
            wctx->pixel.user_win_ctrl_en = FALSE;

            FBDEV_WriteOSDHeader(&wctx->pixel);
            FBDEV_SetOSDEnable(i, layer_onoff);
        }
    }

#ifdef FBDEV_USE_USER_INITCALL_ON_RESUME
    /* (2020/06/11) -- post processing part of lazy osd init */
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;
        hw_cmd.gen[0] = LX_FBDEV_ID_OSD0;

        FBDEV_NOTI("fb(%d) first flip_update (complete) /w force mode !! \n", LX_FBDEV_ID_OSD0);
        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE, &hw_cmd);
    }
#endif

    pdev_ctx->is_suspend = 0;

    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PM_COMPLETE, NULL);
    printk("FBDEV - IBOOT RESUME DONE\n");
#endif
    return RET_OK;
}

static int FBDEV_runtime_resume(struct device* dev)
{
    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));
    FBDEV_CHECK_ERROR(!pdev_ctx, return RET_ERROR, "invalid pdev\n");

    FBDEV_PM_DEBUG("runtime resume req. is_runtime_active=%d\n", pdev_ctx->is_runtime_active);

    FBDEV_CHECK_ERROR(pdev_ctx->is_runtime_active, return RET_OK, "device already runtime_active\n");

    /* TODO: do clock gating off */
    FBDEV_PM_DEBUG("call CG Off\n");
#ifdef INCLUDE_KDRV_PQE_PM
    pqe_pm_request_resume(g_pqe_pm_id);
#endif

    pdev_ctx->is_runtime_active = true;
    FBDEV_PM_DEBUG("runtime resume completed. pvdev_ctx.is_runtime_active=%d\n", pdev_ctx->is_runtime_active);

    report_runtime_status("info", 0, pdev_ctx->visible_status, "resume", "ok");

    return RET_OK;
}

static int FBDEV_runtime_suspend(struct device* dev)
{
    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));
    FBDEV_CHECK_ERROR(!pdev_ctx, return RET_ERROR, "invalid pdev\n");

    FBDEV_PM_DEBUG("runtime suspend req. is_runtime_active=%d\n", pdev_ctx->is_runtime_active);

    FBDEV_CHECK_ERROR(!pdev_ctx->is_runtime_active, return RET_OK, "device already runtime_suspend\n");

    /* TODO: do clock gating on */
    FBDEV_PM_DEBUG("call CG On\n");
#ifdef INCLUDE_KDRV_PQE_PM
    pqe_pm_request_suspend(g_pqe_pm_id);
#endif

    pdev_ctx->is_runtime_active = false;
    FBDEV_PM_DEBUG("runtime suspend completed. pvdev_ctx.is_runtime_active=%d\n", pdev_ctx->is_runtime_active);

    report_runtime_status("info", 0, pdev_ctx->visible_status, "suspend", "ok");

    return RET_OK;
}

void FBDEV_ReportPMStatus(struct seq_file* m)
{
    struct platform_device* pdev = &platform_device;
    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(pdev);

    if (pdev_ctx)
    {
        seq_printf(m, "pm_runtime.status: %s\n", (pdev_ctx->is_runtime_active) ? "active" : "suspend");
        seq_printf(m, "pm_runtime.usage_count: %d\n", atomic_read(&pdev->dev.power.usage_count));
        seq_printf(m, "dev_show_status: 0x%04x\n", pdev_ctx->visible_status);
    }
}

#ifdef INCLUDE_KDRV_PQE_PM
static int FBDEV_PQE_PM_RuntimeCallback(int pqe_pm_action)
{
    struct device* dev;
    FBDEV_HW_CMD_DATA_T hw_cmd;
    hw_cmd.gen[0] = pqe_pm_action;

    dev = &platform_device.dev;

    if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_PREPARE)
    {
        // make fbdev to be pseudo suspend state
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND)
    {
        // TODO: 필요시 추가할것

        // (2023/10/24) make pseudo vsync handler. see http://clm.lge.com/issue/browse/SICDTV-12981
        // pqepm clock gating 이후 osd vsync 가 뜨지 않으므로, 가상으로 vsync handler 동작이 필요하다.
        //
        // (2023/11/06) pqe_pm 주관으로 처리되는 PQE 전체 동작에 연계하여, 실제 HW vsync 가 멈추기 직전에
        // pseudo vsync 용 timer 를 동작하게 한다. 즉 runtime pm 발동하더라도 pqm_pm 의 HW clock gating 이
        // 없으면, HW vsync 는 계속 발생하기 때문이다.
        FBDEV_NOTI("start pseudo vsync timer\n");
        OS_StartTimer(&g_pseudo_vsync_timer, FBDEV_PseudoISRHandler, OS_TIMER_TIMETICK, g_pseudo_vsync_tick, 0);
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_COMPLETED)
    {
        // TODO: 필요시 추가할것
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_PREPARE)
    {
        // TODO: 필요시 추가할것
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME)
    {
        // TODO: 필요시 추가할것

        // (2023/11/06) pqe_pm 의 HW clock gating off 직후 pseudo vsync 를 중지한다.
        FBDEV_NOTI("stop pseudo vsync timer\n");
        OS_StopTimer(&g_pseudo_vsync_timer);
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_COMPLETED)
    {
        // TODO: 필요시 추가할것
    }
    else
    {
        // not supported action
    }

    /* forward pqe_pm messagess to chip kdriver */
    (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_PQE_PM_RUNTIME_ACTION, &hw_cmd);

    return RET_OK;
}
#endif

/*========================================================================================
    Implementation Group (module utility)
========================================================================================*/
FBDEV_CTX_T* FBDEV_GetCtx(void)
{
    return g_dm_ctx;
}

FBDEV_WIN_CTX_T* FBDEV_GetWinCtx(int layer)
{
    switch (layer)
    {
        case LX_FBDEV_ID_OSD0:
        case LX_FBDEV_ID_OSD1:
        case LX_FBDEV_ID_OSD2:
        case LX_FBDEV_ID_OSD3:
            return g_dm_ctx->wctx[layer];

        default:
            return NULL;
    }
}

struct scanvas* FBDEV_GetWinCanvas(int layer)
{
    FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(layer);
    return (wctx) ? &wctx->pixel : NULL;
}

/* initialize or re-initialize OSD IP HW and register */
int FBDEV_InitHardware(void)
{
    return g_fbdev_hw_ctx.InitHW();
}

int FBDEV_ExitHardware(void)
{
    return g_fbdev_hw_ctx.ShutdownHW();
}

int FBDEV_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl)
{
    int ret = RET_OK;

    if (g_fbdev_hw_ctx.SetConnCtrl)
    {
        ret = g_fbdev_hw_ctx.SetConnCtrl(ctrl);
    }

    return ret;
}

int FBDEV_RunResume(void)
{
    return g_fbdev_hw_ctx.RunResume();
}

int FBDEV_RunSuspend(void)
{
    return g_fbdev_hw_ctx.RunSuspend();
}

int FBDEV_ExecHWCommand(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data)
{
    FBDEV_HW_CMD_DATA_T dummy;

    /* if driver doesn't want any feedback or any information, just use dummy data to avoid null access */
    if (data == NULL)
    {
        data = &dummy;
    }

    if (!g_fbdev_hw_ctx.ExecHWCommand)
    {
        return RET_NOT_SUPPORTED;
    }

    return g_fbdev_hw_ctx.ExecHWCommand(cmd, data);
}

int FBDEV_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl)
{
    FBDEV_CHECK_ERROR(NULL == g_fbdev_hw_ctx.SetViewCtrl, return RET_ERROR, "not supported function\n");

    return g_fbdev_hw_ctx.SetViewCtrl(ctrl);
}

int FBDEV_WriteOSDHeader(struct scanvas* hCanvas)
{
    int fb_dev_id;
    FBDEV_WIN_CTX_T* wctx;
    FBDEV_CTX_T* fbctx = FBDEV_GetCtx();

    FBDEV_CHECK_ERROR(NULL == hCanvas, return RET_ERROR, "null param\n");
    FBDEV_CHECK_ERROR(NULL == g_fbdev_hw_ctx.WriteOSDHeader, return RET_ERROR, "null callback\n");
    FBDEV_CHECK_DEBUG(fbctx->global.b_freeze, return RET_OK, "osd freezed\n");

    fb_dev_id = hCanvas->fb_dev_id;
    wctx = FBDEV_GetWinCtx(fb_dev_id);

    FBDEV_CHECK_ERROR(NULL == wctx, return RET_ERROR, "fb(%d) null winctx\n", fb_dev_id);
    FBDEV_CHECK_ERROR(FALSE == g_fbdev_cfg->fb[fb_dev_id].b_active,
                      return RET_OK, "fb(%d) inactive. ignore osd_hdr update\n", fb_dev_id);

    FBDEV_CHECK_DEBUG(FALSE == wctx->status.b_osd_hdr_write, return RET_OK,
                      "fb(%d) osd_hdr disabled. ignore osd_hdr update\n", fb_dev_id);

    return g_fbdev_hw_ctx.WriteOSDHeader(hCanvas);
}

int FBDEV_SetOSDEnable(int layer, int enable)
{
    int ret = RET_ERROR;
    struct platform_device* pdev = &platform_device;
    struct device* dev = &pdev->dev;

    FBDEV_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(pdev);
    FBDEV_CHECK_ERROR(!pdev_ctx, return RET_ERROR, "invalid pdev\n");

    FBDEV_PM_DEBUG("fb(%d) enable=%d, visible_status=0x%04x (BEGIN)\n", layer, enable, pdev_ctx->visible_status);

    /* 신규 enable 요청이 있는 경우, OSD 설정 이전에 PM runtime 설정  */
    if (!(pdev_ctx->visible_status & (1 << layer)) && enable)
    {
        pdev_ctx->visible_status |= (1 << layer);
        FBDEV_PM_DEBUG("fb(%d) get_sync, visible_status=0x%04x\n", layer, pdev_ctx->visible_status);
        pm_runtime_get_sync(dev);

        report_runtime_status("info", layer, pdev_ctx->visible_status, "start", "ok");
    }

    // OSD 의 runtime pm suspend 가 늦게 발동되는 경우를 필요시 테스트할 수 있도록 테스트 코드 지원함
    // see http://clm.lge.com/issue/browse/SICDTV-12981
    if (g_runtime_pm_lazy_suspend_test == 0x1234)
    {
        if (!enable)
        {
            FBDEV_NOTI("call g_fbdev_hw_ctx.SetOSDEnable(%d,off) after %dms\n", layer, g_runtime_pm_lazy_suspend_test_time);
            msleep(g_runtime_pm_lazy_suspend_test_time);
        }
    }

    ret = g_fbdev_hw_ctx.SetOSDEnable(layer, enable);

    /* 신규 disable 요청이 있는 경우, OSD 설정 이후에 PM runtime 설정 */
    if ((pdev_ctx->visible_status & (1 << layer)) && !enable)
    {
        pdev_ctx->visible_status &= ~(1 << layer);
        FBDEV_PM_DEBUG("fb(%d) put_sync, visible_status=0x%04x\n", layer, pdev_ctx->visible_status);
        pm_runtime_put_sync(dev);

        report_runtime_status("info", layer, pdev_ctx->visible_status, "stop", "ok");
    }

    FBDEV_PM_DEBUG("fb(%d) enable=%d, visible_status=0x%04x (COMPLETED)\n", layer, enable,
                   pdev_ctx->visible_status);
    return ret;
}

int FBDEV_GetOSDEnable(int layer)
{
    return g_fbdev_hw_ctx.GetOSDEnable(layer);
}

int FBDEV_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
    return g_fbdev_hw_ctx.GetInterruptStatus(intr);
}

int FBDEV_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
    return g_fbdev_hw_ctx.SetInterruptClear(intr);
}

int FBDEV_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable)
{
    return g_fbdev_hw_ctx.SetInterruptEnable(intr, enable);
}

int FBDEV_WriteOSDCSC(int layer, CSC_INFORM_T* csc)
{
    return g_fbdev_hw_ctx.WriteOSDCSC(layer, csc);
}

void FBDEV_SetOSDImageEndian(int fb_dev_id, int bpp)
{

    ENDIAN_INFORM_T endian = FBDEV_GetOSDImageEndian(bpp);
    FBDEV_WriteOSDEndian(fb_dev_id, &endian);
}

int FBDEV_WriteOSDEndian(int layer, ENDIAN_INFORM_T* endian)
{
    return g_fbdev_hw_ctx.WriteOSDEndian(layer, endian);
}

int FBDEV_InitOSDLayer(int layer)
{
    return g_fbdev_hw_ctx.InitOSDLayer(layer);
}

int FBDEV_SetZList(LX_FBDEV_ZLIST_T* zList)
{
    return g_fbdev_hw_ctx.SetZList(zList);
}

int FBDEV_GetZList(LX_FBDEV_ZLIST_T* zList)
{
    return g_fbdev_hw_ctx.GetZList(zList);
}

int FBDEV_SetTridCtrl(int layer, LX_FBDEV_TRID_CTRL_T* ctrl)
{
    /* do nothing */ return RET_OK;
}

int FBDEV_SetVideoMixerCtrl(LX_FBDEV_VIDEO_MIXER_CTRL_T* ctrl)
{
    /* do nothing */ return RET_OK;
}

int FBDEV_SetPivotCtrl(LX_FBDEV_PIVOT_CTRL_T* ctrl)
{
    /* do nothing */ return RET_OK;
}

void FBDEV_SetPalette(FBDEV_WIN_CTX_T* w, UINT32* pPalette, int num_pal)
{
    unsigned long base_phys;
    unsigned long size;
    struct scanvas* canvas = &w->pixel;

    if (num_pal > 256)
    {
        FBDEV_WARN("palette data is too big\n");
        num_pal = 256;
    }

    memcpy(canvas->palette, pPalette, sizeof(UINT32) * num_pal);

    base_phys = w->osd_plte_base_phys;
    size = w->osd_plte_size;

#ifdef FBDEV_SUPPORT_8BPP_EMUL
    /* do nothing */
#else
    OS_WrData(base_phys, pPalette, num_pal);
#endif

    return;
}

/*========================================================================================
    Implementation Group (debug utility)
========================================================================================*/
int FBDEV_CaptureControl(UINT32 ctrl)
{
#ifdef USE_FBDEV_CAPTURE

    if (!g_fbdev_use_capture)
    {
        return RET_NOT_SUPPORTED;
    }

    if (ctrl == 1)
    {
        if (g_cap_ctrl.active == FALSE)
        {
            g_cap_ctrl.active = TRUE;
        }
    }
    else if (ctrl == 0)
    {
        if (g_cap_ctrl.active)
        {
            OS_PostMutex(&g_cap_ctrl.cap_req_sema);
            g_cap_ctrl.active = FALSE;
        }
    }

#endif

    return RET_OK;
}

int FBDEV_WaitCapture(UINT32* fbmem, UINT32* stride, UINT32* width, UINT32* height, UINT32* afbc_mode)
{
    int ret = RET_ERROR;

#ifdef USE_FBDEV_CAPTURE

    if (!g_fbdev_use_capture)
    {
        return RET_NOT_SUPPORTED;
    }

    if (g_cap_ctrl.active)
    {
        /* user app requests capture */
        FBDEV_ETC_DEBUG("client - request new capture\n");
        OS_PostMutex(&g_cap_ctrl.cap_req_sema);

        /* user app waits for kdriver to be ready for new image */
        FBDEV_ETC_DEBUG("clent - waiting for image ready\n");
        FBDEV_CHECK_ERROR(RET_OK != OS_WaitMutex(&g_cap_ctrl.img_ready_sema),
                          /*nop */, "unlock failed\n");

        /* ok. got cap event */
        *fbmem = g_cap_ctrl.fb.mem;
        *stride = g_cap_ctrl.fb.stride;
        *width = g_cap_ctrl.fb.width;
        *height = g_cap_ctrl.fb.height;
        *afbc_mode = g_cap_ctrl.fb.afbc_mode;;

        ret = RET_OK;
    }

#endif

    return ret;
}

int FBDEV_FBMemHookControl(UINT32 ctrl)
{
#ifdef USE_FBDEV_CAPTURE

    if (!g_fbdev_use_fbmem_hook)
    {
        return RET_NOT_SUPPORTED;
    }

    if (ctrl == 1)
    {
        if (g_fbmem_hook_ctrl.active == FALSE)
        {
            g_fbmem_hook_ctrl.active = TRUE;
        }
    }
    else if (ctrl == 0)
    {
        if (g_fbmem_hook_ctrl.active)
        {
            OS_PostMutex(&g_fbmem_hook_ctrl.cap_req_sema);
            g_fbmem_hook_ctrl.active = FALSE;
        }
    }

#endif

    return RET_OK;
}

int FBDEV_WaitFBMemHook(UINT32* fbmem, UINT32* stride, UINT32* width, UINT32* height, UINT32* afbc_mode)
{
    int ret = RET_ERROR;

#ifdef USE_FBDEV_CAPTURE

    if (!g_fbdev_use_fbmem_hook)
    {
        return RET_NOT_SUPPORTED;
    }

    if (g_fbmem_hook_ctrl.active)
    {
        /* user app requests capture */
        FBDEV_ETC_DEBUG("client - request new capture\n");
        OS_PostMutex(&g_fbmem_hook_ctrl.cap_req_sema);

        /* user app waits for kdriver to be ready for new image */
        FBDEV_ETC_DEBUG("clent - waiting for image ready\n");
        FBDEV_CHECK_ERROR(RET_OK != OS_WaitMutex(&g_fbmem_hook_ctrl.img_ready_sema),    /*nop */
                          , "unlock failed\n");

        /* ok. got cap event */
        *fbmem = g_fbmem_hook_ctrl.fb.mem;
        *stride = g_fbmem_hook_ctrl.fb.stride;
        *width = g_fbmem_hook_ctrl.fb.width;
        *height = g_fbmem_hook_ctrl.fb.height;
        *afbc_mode = g_fbmem_hook_ctrl.fb.afbc_mode;;

        ret = RET_OK;
    }

#endif

    return ret;
}

#ifdef FBDEV_USE_FPS_MON
typedef struct
{
    BOOLEAN b_onoff;
    UINT32 isr_cnt;
    UINT32 refresh_cnt[LX_FBDEV_ID_MAX];

    UINT64 start_ns_tk;
    OS_TIMER_T tmr;
} FBDEV_FPS_MON_T;

static FBDEV_FPS_MON_T g_fbdev_fps_mon;

static void FBDEV_FPSMon_Report(ULONG data)
{
    int i;
    //UINT64        curr_ns_tk = OS_GetNsecTicks();
    UINT32 duration = data;

    FBDEV_NOTI("+ isr_cnt=%03d (%dsec), vsync=%03dHz\n",
               g_fbdev_fps_mon.isr_cnt, duration, g_fbdev_fps_mon.isr_cnt / duration);

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        if (g_fbdev_cfg->fb[i].b_active)
        {
            FBDEV_NOTI("+ fb(%d) draw_cnt=%03d (%dsec), fps=%03d\n",
                       i, g_fbdev_fps_mon.refresh_cnt[i], duration, g_fbdev_fps_mon.refresh_cnt[i] / duration);
        }
    }

    /* reinit data */
    g_fbdev_fps_mon.isr_cnt = 0;
    memset(g_fbdev_fps_mon.refresh_cnt, 0x0, sizeof(UINT32) * LX_FBDEV_ID_MAX);

    g_fbdev_fps_mon.start_ns_tk = OS_GetNsecTicks();

}

void FBDEV_MON_Init(void)
{
    memset(&g_fbdev_fps_mon, 0x0, sizeof(FBDEV_FPS_MON_T));

    OS_InitTimer(&g_fbdev_fps_mon.tmr);
}

void FBDEV_MON_SetFPSMon(BOOLEAN onoff)
{
    if (onoff)
    {
        g_fbdev_fps_mon.b_onoff = TRUE;
        g_fbdev_fps_mon.isr_cnt = 0;
        memset(g_fbdev_fps_mon.refresh_cnt, 0x0, sizeof(UINT32) * LX_FBDEV_ID_MAX);
        g_fbdev_fps_mon.start_ns_tk = OS_GetNsecTicks();

        OS_StartTimer(&g_fbdev_fps_mon.tmr, FBDEV_FPSMon_Report, OS_TIMER_TIMETICK, 2000, (ULONG) 2);
    }
    else
    {
        g_fbdev_fps_mon.b_onoff = FALSE;
        OS_StopTimer(&g_fbdev_fps_mon.tmr);
    }
}

void FBDEV_MON_NotiRefresh(int fb_dev_id)
{
    if (g_fbdev_fps_mon.b_onoff)
    {
        if (LX_FBDEV_IS_VALID_ID(fb_dev_id))
        {
            g_fbdev_fps_mon.refresh_cnt[fb_dev_id]++;
        }
    }
}

void FBDEV_MON_ISRTick(void)
{
    if (g_fbdev_fps_mon.b_onoff)
    {
        g_fbdev_fps_mon.isr_cnt++;
    }
}
#endif

/*
 *  Declaration of the init and exit functions
 */
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", FBDEV_Init);
#else
module_init(FBDEV_Init);
#endif
module_exit(FBDEV_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("FBDEV driver");
MODULE_LICENSE("GPL");
#endif
