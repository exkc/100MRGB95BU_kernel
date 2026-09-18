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
 *  Linux proc interface for fbdev device.
 *  fbdev device will teach you how to make device driver with new platform.
 *
 *  author      raxis
 *  version     1.0
 *  date        2010.02.01
 *  note        Additional information.
 *
 *  @addtogroup lg1150_fbdev
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_drv.h"
#include "fbdev_drm.h"
#include "proc_util.h"
#include <linux/seq_file.h>

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define LG1150_OSD_BASE 0xc0017A00

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
enum
{
    PROC_ID_AUTHOR  = 0,
    PROC_ID_OSD_INFO,
    PROC_ID_REG_DUMP,
    PROC_ID_VIEW_CTRL,
    PROC_ID_SYNC_CTRL,
    PROC_ID_PATH_CTRL,
    PROC_ID_OSD_FREEZE,
    PROC_ID_OSD_CHGRES,
    PROC_ID_OSD_GL_ALPHA,
    PROC_ID_OSD_BKUP,
    PROC_ID_OSD_FPS_MON,
    PROC_ID_STATUS,
    PROC_ID_RENDER_EVENT,
    PROC_ID_PM_TEST,
    PROC_ID_FLIP_TEST,
    PROC_ID_USER_OUTPUT_WIN,
    PROC_ID_CAPTURE,
    PROC_ID_FBMEM_HOOk,

    PROC_ID_USER_FLIP_OPT,
    PROC_ID_PM_STATUS,

    PROC_ID_DRM_FREEZE,

    PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int FBDEV_SetZList(LX_FBDEV_ZLIST_T* zList);
extern int FBDEV_GetZList(LX_FBDEV_ZLIST_T* zList);

extern int FBDEV_InitLinuxFBTestMode(int fb_dev_id);

extern int FBDEV_CaptureControl(UINT32 ctrl);
extern int FBDEV_WaitCapture(UINT32* fbmem, UINT32* stride, UINT32* width, UINT32* height, UINT32* afbc_mode);

extern int FBDEV_FBMemHookControl(UINT32 ctrl);
extern int FBDEV_WaitFBMemHook(UINT32* fbmem, UINT32* stride, UINT32* width, UINT32* height, UINT32* afbc_mode);

extern int FBDEV_GetUserFlipOption(void);
extern void FBDEV_SetUserFlipOption(const char* str, int opt);

extern void FBDEV_ReportPMStatus(struct seq_file* m);

extern void osd_drm_init_proc(struct os_proc* pdir);
extern void osd_drm_dump_context(struct seq_file* m);

void    FBDEV_PROC_Init(void);
void    FBDEV_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _FBDEV_ReadProcFunction(UINT32 procId, char* buffer);
static int _FBDEV_WriteProcFunction(UINT32 procId, char* command);

static void _FBDEV_PROC_PrintOSDInfo(struct seq_file* m);
static void _FBDEV_PROC_DumpRegs(struct seq_file* m);
static void _FBDEV_PROC_PrintStatus(struct seq_file* m, void* data);
static void _FBDEV_PROC_PrintFBMemStatus(struct seq_file* m, void* data);
static void _FBDEV_PROC_PrintFlipStatus(struct seq_file* m, void* data);
static void _FBDEV_PROC_PrintPanDispStatus(struct seq_file* m, void* data);

static int  __strhash(const char* str)
{
    int i;
    int k = 0;
    int len = strlen(str);

    for (i = 0 ; i < len ; i++)
    {
        if (str[i] == '\n') continue;

        k = 31 * k + str[i];
    }

    return k;
}

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static int fbdev_read_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return _FBDEV_ReadProcFunction(procId, buffer);
}

static int fbdev_write_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return _FBDEV_WriteProcFunction(procId, buffer);
}

static int fbdev_proc_print_osd_info(struct seq_file* m, void* data)
{
    _FBDEV_PROC_PrintOSDInfo(m);
    return 0;
}

static int fbdev_proc_dump_regs(struct seq_file* m, void* data)
{
    _FBDEV_PROC_DumpRegs(m);
    return 0;
}

static int fbdev_proc_print_status(struct seq_file* m, void* data)
{
    _FBDEV_PROC_PrintStatus(m, data);
    return 0;
}

static int fbdev_proc_print_fbmem_status(struct seq_file* m, void* data)
{
    _FBDEV_PROC_PrintFBMemStatus(m, data);
    return 0;
}

static int fbdev_proc_print_flip_status(struct seq_file* m, void* data)
{
    _FBDEV_PROC_PrintFlipStatus(m, data);
    return 0;
}

static int fbdev_proc_print_pandisplay_status(struct seq_file* m, void* data)
{
    _FBDEV_PROC_PrintPanDispStatus(m, data);
    return 0;
}

/*========================================================================================
    Implementation Group
========================================================================================*/


/** initialize proc utility for fbdev device
 *
 * @see FBDEV_Init
*/
void    FBDEV_PROC_Init(void)
{
    int i;
    struct os_proc* pdir = os_proc_create_dir(NULL, "fbdev", fbdev_read_proc_handler, fbdev_write_proc_handler);

    os_proc_create_file(pdir, "viewctrl",  PROC_ID_VIEW_CTRL, NULL);
    os_proc_create_file(pdir, "syncctrl",  PROC_ID_SYNC_CTRL, NULL);
    os_proc_create_file(pdir, "pathctrl",  PROC_ID_PATH_CTRL, NULL);
    os_proc_create_file(pdir, "freeze",     PROC_ID_OSD_FREEZE, NULL);
    os_proc_create_file(pdir, "chgres",     PROC_ID_OSD_CHGRES, NULL);
    os_proc_create_file(pdir, "glalpha",    PROC_ID_OSD_GL_ALPHA, NULL);
    os_proc_create_file(pdir, "fps_mon",    PROC_ID_OSD_FPS_MON, NULL);
    os_proc_create_file(pdir, "fb_backup",  PROC_ID_OSD_BKUP, NULL);
    os_proc_create_file(pdir, "pm_test",    PROC_ID_PM_TEST, NULL);
    os_proc_create_file(pdir, "flip_test",  PROC_ID_FLIP_TEST, NULL);

    os_proc_create_file(pdir, "drm_freeze", PROC_ID_DRM_FREEZE, NULL);

    os_proc_create_file(pdir, "user_flip_opt", PROC_ID_USER_FLIP_OPT, NULL);
    os_proc_create_file(pdir, "test_output_win", PROC_ID_USER_OUTPUT_WIN, NULL);

    os_proc_create_file(pdir, "render_event", PROC_ID_RENDER_EVENT, NULL);
    os_proc_create_file(pdir, "capture", PROC_ID_CAPTURE, NULL);
    os_proc_create_file(pdir, "fbmem_hook", PROC_ID_FBMEM_HOOk, NULL);

#ifdef USE_DRM_HELPER_TEST
    os_proc_create_file(pdir, "drm_helper_setup", PROC_ID_DRM_HELPER_SETUP, NULL);
    os_proc_create_file(pdir, "drm_helper_cursor", PROC_ID_DRM_HELPER_CURSOR_TEST, NULL);
#endif

    os_proc_create_seq_file(pdir, "status", fbdev_proc_print_osd_info, NULL, NULL);
    os_proc_create_seq_file(pdir, "regdump", fbdev_proc_dump_regs, NULL, NULL);

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        struct os_proc* fbdir;
        char fbname[LX_STR_MAX];
        snprintf(fbname, LX_STR_MAX, "fb%d", i);

        fbdir = os_proc_create_dir(pdir, fbname, NULL, NULL);

        os_proc_create_seq_file(fbdir, "status", fbdev_proc_print_status, NULL, (void*)(ulong)i);
        os_proc_create_seq_file(fbdir, "fbmem", fbdev_proc_print_fbmem_status, NULL, (void*)(ulong)i);
        os_proc_create_seq_file(fbdir, "flip_cnt", fbdev_proc_print_flip_status, NULL, (void*)(ulong)i);
        os_proc_create_seq_file(fbdir, "pan_disp_cnt", fbdev_proc_print_pandisplay_status, NULL, (void*)(ulong)i);
    }

    osd_drm_init_proc(pdir);

    /* create chip proc if necessary */
    if (g_fbdev_hw_ctx.CreateProc)
    {
#ifdef OS_API_VERSION
        g_fbdev_hw_ctx.CreateProc((void*)pdir);
#else // legacy proc
        g_fbdev_hw_ctx.CreateProc((void*)os_proc_get_entry(pdir));
#endif
    }
}

/** cleanup proc utility for fbdev device
 *
 * @see FBDEV_Cleanup
*/
void    FBDEV_PROC_Cleanup(void)
{
    OS_PROC_RemoveEntry(FBDEV_MODULE);
}


/*
 * read_proc implementation of fbdev device
 *
*/
static int  _FBDEV_ReadProcFunction(UINT32 procId, char* buffer)
{
    int     ret;

    /* TODO: add your proc_write implementation */
    switch (procId)
    {
        case PROC_ID_AUTHOR:
        {
            ret = sprintf(buffer, "%s\n", "raxis.lim@lge.com");
        }
        break;

        case PROC_ID_VIEW_CTRL:
        {
            int len = 0;
            len += sprintf(buffer + len, "OSD VIEW CTRL status\n");
            len += sprintf(buffer + len, "OSD 0 : %d\n", FBDEV_GetOSDEnable(0));
            len += sprintf(buffer + len, "OSD 1 : %d\n", FBDEV_GetOSDEnable(1));
            len += sprintf(buffer + len, "OSD 2 : %d\n", FBDEV_GetOSDEnable(2));
            len += sprintf(buffer + len, "OSD 3 : %d\n", FBDEV_GetOSDEnable(3));
            len += sprintf(buffer + len, "\n");
            len += sprintf(buffer + len, "[usage] echo osd_id on_off_val > /proc/lg/fbdev/viewctrl\n");
            len += sprintf(buffer + len, "        osd_id     : 0 ~ 3\n");
            len += sprintf(buffer + len, "        on_off_val : 0 (off), 1(on)\n");
            ret = len;
        }
        break;

        case PROC_ID_SYNC_CTRL:
        {
            int len = 0;
            FBDEV_WIN_CTX_T* w;

            len += sprintf(buffer + len, "OSD SYNC CTRL status\n");
            w = FBDEV_GetWinCtx(0);
            w = FBDEV_GetWinCtx(0);
            len += sprintf(buffer + len, "OSD 0 : %d\n", w->status.b_use_vsync);
            w = FBDEV_GetWinCtx(1);
            len += sprintf(buffer + len, "OSD 1 : %d\n", w->status.b_use_vsync);
            w = FBDEV_GetWinCtx(2);
            len += sprintf(buffer + len, "OSD 2 : %d\n", w->status.b_use_vsync);
            w = FBDEV_GetWinCtx(3);
            len += sprintf(buffer + len, "OSD 3 : %d\n", w->status.b_use_vsync);
            len += sprintf(buffer + len, "\n");

            len += sprintf(buffer + len, "[usage] echo osd_id on_off_val > /proc/lg/fbdev/syncctrl\n");
            len += sprintf(buffer + len, "        osd_id     : 0 ~ 3\n");
            len += sprintf(buffer + len, "        on_off_val : 0 (off), 1(on)\n");
            ret = len;
        }
        break;

        case PROC_ID_OSD_CHGRES:
        {
            int len = 0;
            len += sprintf(buffer + len, "OSD framebuffer resolution\n");
            len += sprintf(buffer + len, "[usage] echo osd_id x y w h > /proc/lg/fbdev/chgres\n");
            ret = len;
        }
        break;

        case PROC_ID_OSD_GL_ALPHA:
        {
            int len = 0;
            len += sprintf(buffer + len, "OSD framebuffer glpha_alpha ctrl\n");
            len += sprintf(buffer + len, "[usage] echo osd_id alpha > /proc/lg/fbdev/glalpha\n");
            len += sprintf(buffer + len, "        alpha : hexdecimal value (0x0~0xff)\n");
            len += sprintf(buffer + len, "                if alpha is 0x00, global lapha is disabled\n");
            ret = len;
        }
        break;

        case PROC_ID_OSD_BKUP:
        {
            int len = 0;
            len += sprintf(buffer + len, "OSD framebuffer backup/restore\n");
            len += sprintf(buffer + len, "[usage] echo on_off_val > /proc/lg/fbdev/fb_bkup\n");
            len += sprintf(buffer + len, "        on_off_val : 0 (restore), 1(backup)\n");
            ret = len;
        }
        break;

        case PROC_ID_OSD_FPS_MON:
        {
            int len = 0;
            len += sprintf(buffer + len, "view OSD fps status\n");
            len += sprintf(buffer + len, "[usage] echo on_off_val > /proc/lg/fbdev/fps_mon\n");
            len += sprintf(buffer + len, "        on_off_val : 0 (off), 1(on)\n");
            ret = len;
        }
        break;

        case PROC_ID_PATH_CTRL:
        {
            int len = 0;
            len += sprintf(buffer + len, "OSD path ctrl\n");
            len += sprintf(buffer + len, "[usage] echo path_val > /proc/lg/fbdev/pathctrl\n");
            len += sprintf(buffer + len, "        path_val : bosd, sosd\n");
            ret = len;
        }
        break;

        case PROC_ID_RENDER_EVENT:
        {
            int len = 0;

            /* wait render event with 500 ms timeout */
            int rc = FBDEV_WaitForRenderEvent(500);
            len += sprintf(buffer + len, "%d\n", rc);
            ret = len;
        }
        break;

        case PROC_ID_PM_TEST:
        {
            int len = 0;
            len += sprintf(buffer + len, "test PM handler\n");
            len += sprintf(buffer + len, "usage) echo pmstr > pm_test\n");
            len += sprintf(buffer + len, "       pmstr=freeze,restore,thaw,suspend,resume\n");
            ret = len;
        }
        break;

        case PROC_ID_FLIP_TEST:
        {
            int len = 0;
            len += sprintf(buffer + len, "display memory content to OSD screen\n");
            len += sprintf(buffer + len, "usage) echo fb_dev_id phsy_addr stride width height fmtstr > flip_test\n");
            len += sprintf(buffer + len, "       fmtstr= afbc,fbc0,fbc1,argb\n");
            ret = len;
        }
        break;

        case PROC_ID_USER_OUTPUT_WIN:
        {
            int len = 0;
            len += sprintf(buffer + len, "set user-defined fixed output win (supports OSD0 only)\n");
            len += sprintf(buffer + len, "usage) echo fb_dev_id x y width height > test_output_win\n");
            ret = len;
        }
        break;

        case PROC_ID_CAPTURE:
        {
            UINT32 fbmem, stride, width, height, afbc_mode;
            int len = 0;

            FBDEV_WaitCapture(&fbmem, &stride, &width, &height, &afbc_mode);

            /* this proc just returns new framebuffer information.
             * so the real capture process should be implemented at user level test app
             */
            len += sprintf(buffer + len, "0x%08x %d %d %d %s\n", fbmem, stride, width, height, (afbc_mode) ? "afbc" : "argb");
            ret = len;
        }
        break;

        case PROC_ID_FBMEM_HOOk:
        {
            UINT32 fbmem, stride, width, height, afbc_mode;
            int len = 0;

            FBDEV_WaitFBMemHook(&fbmem, &stride, &width, &height, &afbc_mode);

            /* this proc just returns new framebuffer information.
             * so the real composition process should be implemented at user level test app
             */
            len += sprintf(buffer + len, "0x%08x %d %d %d %s\n", fbmem, stride, width, height, (afbc_mode) ? "afbc" : "argb");
            ret = len;
        }
        break;

        case PROC_ID_USER_FLIP_OPT:
        {
            int len = 0;
            len += sprintf(buffer + len, "0x%08x\n", FBDEV_GetUserFlipOption());
            ret = len;
        }
        break;

        default:
        {
            ret = sprintf(buffer, "%s(%d)\n", "unimplemented read proc", procId);
        }
    }

    return ret;
}

/*
 * write_proc implementation of fbdev device
 *
*/
static int _FBDEV_WriteProcFunction(UINT32 procId, char* command)
{
    /* TODO: add your proc_write implementation */
    switch (procId)
    {
        case PROC_ID_VIEW_CTRL:
        {
            int osd_id;
            int on_off_val;

            sscanf(command, " %d %d", &osd_id, &on_off_val);

            if (osd_id >= 0 && osd_id < LX_FBDEV_ID_MAX)
            {
                FBDEV_SetOSDEnable(osd_id, on_off_val);
            }
        }
        break;

        case PROC_ID_SYNC_CTRL:
        {
            int osd_id;
            int on_off_val;

            sscanf(command, " %d %d", &osd_id, &on_off_val);

            if (osd_id >= 0 && osd_id < LX_FBDEV_ID_MAX)
            {
                FBDEV_WIN_CTX_T* w = g_dm_ctx->wctx[osd_id];
                w->status.b_use_vsync = on_off_val;
            }
        }
        break;

        case PROC_ID_OSD_FREEZE:
        {
            UINT32 val;
            FBDEV_CTX_T* fbctx = FBDEV_GetCtx();

            sscanf(command, " %d", &val);
            fbctx->global.b_freeze = val;
        }
        break;

        case PROC_ID_OSD_CHGRES:
        {
            FBDEV_WIN_CTX_T*    wctx;
            LX_FBDEV_CONFIG_T   config;

            UINT32  osd_id, x, y, width, height;
            sscanf(command, " %d %d %d %d %d", &osd_id, &x, &y, &width, &height);

            wctx = FBDEV_GetWinCtx(osd_id);

            if (wctx == NULL) { printk("invalid win info\n"); break; }

            FBDEV_GetConfig(wctx, &config);
            config.input_win.x = x;
            config.input_win.y = y;
            config.input_win.w = width;
            config.input_win.h = height;
            FBDEV_SetConfig(wctx, &config, TRUE);
        }
        break;

        case PROC_ID_OSD_GL_ALPHA:
        {
            FBDEV_WIN_CTX_T* wctx;
            UINT32 osd_id, glalpha;
            sscanf(command, " %d %x", &osd_id, &glalpha);
            wctx = FBDEV_GetWinCtx(osd_id);

            if (wctx == NULL) { printk("invalid win info\n"); break; }

            wctx->pixel.user_global_alpha_en = (glalpha > 0) ? 1 : 0;
            wctx->pixel.user_global_alpha = glalpha;

            FBDEV_WriteOSDHeader(&wctx->pixel);
        }
        break;

        case PROC_ID_OSD_BKUP:
        {
            UINT32  onoff;
            sscanf(command, " %d", &onoff);

            if (onoff)  FBDEV_BackupFBList();
            else        FBDEV_RestoreFBList("restore");
        }
        break;

        case PROC_ID_OSD_FPS_MON:
        {
            UINT32  onoff;
            sscanf(command, " %d", &onoff);

            FBDEV_MON_SetFPSMon(onoff);
        }
        break;

        case PROC_ID_PATH_CTRL:
        {
            LX_FBDEV_CONN_CTRL_T conn_ctrl;

            if (!strncmp(command, "bosd", 4))
            {
                conn_ctrl.conn_type = LX_FBDEV_CONN_OSD_VIDEO_BLEND;
            }
            else if (!strncmp(command, "sosd", 4))
            {
                conn_ctrl.conn_type = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE;
            }
            else
            {
                /* do nothing */ break;
            }

            FBDEV_SetConnCtrl(&conn_ctrl);
        }
        break;

        case PROC_ID_PM_TEST:
        {
            /* PM emulation test. valid input = freeze, restore, thaw, suspend, resume */
            FBDEV_PMTest(command);
        }
        break;

        case PROC_ID_FLIP_TEST:
        {
            char    fmtstr[8];
            char    pxlfmt[8];
            UINT32  fb_dev_id, phys_addr, stride, width, height;
            FBDEV_WIN_CTX_T* wctx;

            LX_FBDEV_FB_SCREEN_T fb_screen;
            memset(&fb_screen, 0x0, sizeof(LX_FBDEV_FB_SCREEN_T));

            sscanf(command, " %d %x %d %d %d %s %s", &fb_dev_id, &phys_addr, &stride, &width, &height, fmtstr, pxlfmt);

            wctx = FBDEV_GetWinCtx(fb_dev_id);
            FBDEV_CHECK_ERROR(wctx == NULL, break, "invalid fb(%d)\n", fb_dev_id);

            FBDEV_GetConfig(wctx, &fb_screen.layer_ctrl);
            fb_screen.layer_ctrl.input_win.w = width;
            fb_screen.layer_ctrl.input_win.h = height;

            fb_screen.img_ctrl.fbc_fmt      = (!strncmp(fmtstr, "afrc", 4)) ? LX_FBDEV_FBC_FORMAT_AFRC :
                                              (!strncmp(fmtstr, "afbc", 4)) ? LX_FBDEV_FBC_FORMAT_AFBC :
                                              (!strncmp(fmtstr, "fbc0", 4)) ? LX_FBDEV_FBC_FORMAT_FBC0 :
                                              (!strncmp(fmtstr, "fbc1", 4)) ? LX_FBDEV_FBC_FORMAT_FBC1 :
                                              LX_FBDEV_FBC_FORMAT_RAW;
            fb_screen.img_ctrl.phys_addr        = phys_addr;
            fb_screen.img_ctrl.stride           = stride;
            fb_screen.img_ctrl.bits_per_pixel   = 32;
            fb_screen.img_ctrl.pixel_fmt        = (!strncmp(pxlfmt, "argb", 4)) ? LX_FBDEV_PIXEL_FORMAT_RGB_8888 :
                                                  LX_FBDEV_PIXEL_FORMAT_BGR_8888;

            fb_screen.opmask |= (LX_FBDEV_SCREEN_OPMASK_IMG_CTRL | LX_FBDEV_SCREEN_OPMASK_LAYER_CTRL);

            FBDEV_UpdateFBScreen(fb_dev_id, &fb_screen, FALSE);
        }
        break;

        case PROC_ID_USER_OUTPUT_WIN:
        {
            UINT32  fb_dev_id, x, y, w, h;
            FBDEV_WIN_CTX_T* wctx;

            sscanf(command, " %d %d %d %d %d", &fb_dev_id, &x, &y, &w, &h);

            wctx = FBDEV_GetWinCtx(fb_dev_id);
            FBDEV_CHECK_ERROR(wctx == NULL, break, "invalid fb(%d)\n", fb_dev_id);

            wctx->pixel.test_output_win.x = x;
            wctx->pixel.test_output_win.y = y;
            wctx->pixel.test_output_win.w = w;
            wctx->pixel.test_output_win.h = h;

            FBDEV_WriteOSDHeader(&wctx->pixel);
        }
        break;

        case PROC_ID_CAPTURE:
        {
            UINT32 ctrl;
            sscanf(command, " %d", &ctrl);
            FBDEV_CaptureControl(ctrl);
        }
        break;

        case PROC_ID_FBMEM_HOOk:
        {
            UINT32 ctrl;
            sscanf(command, " %d", &ctrl);
            FBDEV_FBMemHookControl(ctrl);
        }
        break;

        // test command to switch user flip option
        case PROC_ID_USER_FLIP_OPT:
        {
            char opt[32];
            sscanf(command, " %s", opt);
            FBDEV_SetUserFlipOption(opt, __strhash(command));
        }
        break;

#ifdef USE_DRM_HELPER_TEST

        case PROC_ID_DRM_HELPER_SETUP:
        {
            osd_drm_enable(osd_drm_id_graphic0, TRUE);
            osd_drm_enable(osd_drm_id_cursor, TRUE);

            osd_drm_set_cursor_region(1920, 1080);

            osd_drm_flip_image(osd_drm_id_cursor, 0x56c00000, osd_drm_pxlfmt_raw_xrgb, 64 * 4, 64, 64);

            osd_drm_move_cursor(960, 540);
        }
        break;

        case PROC_ID_DRM_HELPER_CURSOR_TEST:
        {
            int cx, cy;
            sscanf(command, " %d %d", &cx, &cy);

            osd_drm_move_cursor(cx, cy);
        }
        break;


#endif

        case PROC_ID_DRM_FREEZE:
        {
            UINT32 ctrl;
            sscanf(command, " %d", &ctrl);

            osd_drm_freeze(ctrl);
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }

    return strlen(command);
}

static void _FBDEV_PROC_DumpWinCtx(FBDEV_WIN_CTX_T* w, struct seq_file* m)
{
    int id = w->fb_dev_id;
    LX_FBDEV_CFG_T* cfg = FBDEV_GET_CFG();

    seq_printf(m, " cfg.b_active         = %d\n", cfg->fb[id].b_active);
    seq_printf(m, " cfg.b_cursor         = %d\n", cfg->fb[id].b_cursor);
    seq_printf(m, " cfg.b_use_afbc       = %d\n", cfg->fb[id].b_use_afbc);
    seq_printf(m, " cfg..b_use_bltn_fbmem= %d\n", cfg->fb[id].b_use_builtin_fbmem);
    seq_printf(m, " cfg.max_xres         = %d\n", cfg->fb[id].max_xres);
    seq_printf(m, " cfg.max_yres         = %d\n", cfg->fb[id].max_yres);
    seq_printf(m, " cfg.max_buf_num      = %d\n", cfg->fb[id].max_buf_num);

    seq_printf(m, " linux_fb_mode        = %d\n",   w->linux_fb_mode);
    seq_printf(m, " users                = %d\n",   w->users);
    seq_printf(m, " fb_base_phys         = 0x%x\n", (UINT32)w->fb_base_phys);
    seq_printf(m, " fb_base              = %p\n",   w->fb_base);
    seq_printf(m, " fb_size              = %d\n", (int)w->fb_size);

    seq_printf(m, " osd_hdr_base_phys    = 0x%x\n", (UINT32)w->osd_hdr_base_phys);
    seq_printf(m, " osd_hdr_base         = %p\n",   w->osd_hdr_base);
    seq_printf(m, " osd_hdr_size         = 0x%x\n", (UINT32)w->osd_hdr_size);

    seq_printf(m, " osd_plte_base_phys   = 0x%x\n", (UINT32)w->osd_plte_base_phys);
    seq_printf(m, " osd_plte_base        = %p\n",   w->osd_plte_base);
    seq_printf(m, " osd_plte_size        = %d\n", (int)w->osd_plte_size);

    seq_printf(m, " status.b_use_vsync     = %d\n", w->status.b_use_vsync);
    seq_printf(m, " status.b_sd_hdr_write  = %d\n", w->status.b_osd_hdr_write);
    seq_printf(m, " status.b_osd_hdr_flush = %d\n", w->status.b_osd_hdr_flush);
    seq_printf(m, " status.fb_pan_disp_cnt = %d\n", w->status.fb_pan_disp_cnt);
    seq_printf(m, " status.fb_flip_cnt     = %d\n", w->status.fb_flip_cnt);
    seq_printf(m, " status.total_fb_flip_cnt= %d\n",    w->status.total_fb_flip_cnt);

    seq_printf(m, "\n");
    seq_printf(m, " pixel.fb_dev_id      = %d\n",   w->pixel.fbc_fmt);
    seq_printf(m, " pixel.fbc_fmtid      = %d\n",   w->pixel.fb_dev_id);

    seq_printf(m, " pixel.osd_bm_paddr   = 0x%x\n", (UINT32)w->pixel.osd_bm_paddr);
    seq_printf(m, " pixel.stride         = %d\n", w->pixel.stride);
    seq_printf(m, " pixel.bits_per_pixel = %d (pxlfmt 0x%x, pxldepth 0x%x)\n", w->pixel.bits_per_pixel,
               FBDEV_GetOSDPxlFmt(w->pixel.bits_per_pixel),
               FBDEV_GetOSDPxlDepth(w->pixel.bits_per_pixel));
    seq_printf(m, " pixel.input_win.x    = %d\n", w->pixel.input_win.x);
    seq_printf(m, " pixel.input_win.y    = %d\n", w->pixel.input_win.y);
    seq_printf(m, " pixel.input_win.w    = %d\n", w->pixel.input_win.w);
    seq_printf(m, " pixel.input_win.h    = %d\n", w->pixel.input_win.h);
    seq_printf(m, " pixel.output_win.x   = %d\n", w->pixel.output_win.x);
    seq_printf(m, " pixel.output_win.y   = %d\n", w->pixel.output_win.y);
    seq_printf(m, " pixel.output_win.w   = %d\n", w->pixel.output_win.w);
    seq_printf(m, " pixel.output_win.h   = %d\n", w->pixel.output_win.h);
    seq_printf(m, " pixel.test_output_win.x = %d\n", w->pixel.test_output_win.x);
    seq_printf(m, " pixel.test_output_win.y = %d\n", w->pixel.test_output_win.y);
    seq_printf(m, " pixel.test_output_win.w = %d\n", w->pixel.test_output_win.w);
    seq_printf(m, " pixel.test_output_win.h = %d\n", w->pixel.test_output_win.h);

    seq_printf(m, " pixel.user_win_ctrl_en    = %d\n", w->pixel.user_win_ctrl_en);
    seq_printf(m, " pixel.color_key_en        = %d\n", w->pixel.color_key_en);
    seq_printf(m, " pixel.color_key           = 0x%x\n", (UINT32)w->pixel.color_key);
    seq_printf(m, " pixel.pixel_order_en      = %d\n", w->pixel.pixel_order_en);
    seq_printf(m, " pixel.global_alpha_en     = %d\n", w->pixel.global_alpha_en);
    seq_printf(m, " pixel.global_alpha        = 0x%x\n", (UINT32)w->pixel.global_alpha);
    seq_printf(m, " pixel.user_global_alpha_en= %d\n", w->pixel.user_global_alpha_en);
    seq_printf(m, " pixel.user_global_alpha   = 0x%x\n", (UINT32)w->pixel.user_global_alpha);

    if (w->fb_dev_id == LX_FBDEV_ID_CSR0)
    {
        seq_printf(m, " pixel.csr_size       = %dx%d\n", w->pixel.csr_size.w, w->pixel.csr_size.h);
        seq_printf(m, " pixel.csr_hotspot    = %dx%d\n", w->pixel.csr_hotspot.x, w->pixel.csr_hotspot.y);
    }

    seq_printf(m, "\n");

    seq_printf(m, " fbinfo.state           = 0x%x\n", (UINT32)w->linux_fb_info.state);
    seq_printf(m, " fbinfo.flags           = 0x%x\n", (UINT32)w->linux_fb_info.flags);
    seq_printf(m, " fbinfo.screen_base     = %p\n", w->linux_fb_info.screen_base);
    seq_printf(m, " fbinfo.screen_size     = %d\n", (UINT32)w->linux_fb_info.screen_size);
    seq_printf(m, " fbinfo.fbcon_par       = %p\n", w->linux_fb_info.fbcon_par);
    seq_printf(m, " fbinfo.par             = %p\n", w->linux_fb_info.par);
    seq_printf(m, " fbinfo.fix.id          = %s\n", (char*)w->linux_fb_info.fix.id);
    seq_printf(m, " fbinfo.fix.smem_start  = 0x%x\n", (UINT32)w->linux_fb_info.fix.smem_start);
    seq_printf(m, " fbinfo.fix.smem_len    = %d\n", (int)w->linux_fb_info.fix.smem_len);
    seq_printf(m, " fbinfo.fix.type        = 0x%x\n", (UINT32)w->linux_fb_info.fix.type);
    seq_printf(m, " fbinfo.fix.type_aux    = 0x%x\n", (UINT32)w->linux_fb_info.fix.type_aux);
    seq_printf(m, " fbinfo.fix.visual      = 0x%x\n", (UINT32)w->linux_fb_info.fix.visual);
    seq_printf(m, " fbinfo.fix.xpanstep    = %d\n", (int)w->linux_fb_info.fix.xpanstep);
    seq_printf(m, " fbinfo.fix.ypanstep    = %d\n", (int)w->linux_fb_info.fix.ypanstep);
    seq_printf(m, " fbinfo.fix.ywrapstep   = %d\n", (int)w->linux_fb_info.fix.ywrapstep);
    seq_printf(m, " fbinfo.fix.line_length = %d\n", (int)w->linux_fb_info.fix.line_length);
    seq_printf(m, " fbinfo.fix.mmio_start  = 0x%x\n", (UINT32)w->linux_fb_info.fix.mmio_start);
    seq_printf(m, " fbinfo.fix.mmio_len    = %d\n", (int)w->linux_fb_info.fix.mmio_len);
    seq_printf(m, " fbinfo.fix.accel       = %x\n", (UINT32)w->linux_fb_info.fix.accel);
    seq_printf(m, " fbinfo.fix.reserved[3] 2B\n\n");

    seq_printf(m, " fbinfo.var.xres        = %d\n", (int)w->linux_fb_info.var.xres);
    seq_printf(m, " fbinfo.var.yres        = %d\n", (int)w->linux_fb_info.var.yres);
    seq_printf(m, " fbinfo.var.xres_virtual= %d\n", (int)w->linux_fb_info.var.xres_virtual);
    seq_printf(m, " fbinfo.var.yres_virtual= %d\n", (int)w->linux_fb_info.var.yres_virtual);
    seq_printf(m, " fbinfo.var.xoffset     = %d\n", (int)w->linux_fb_info.var.xoffset);
    seq_printf(m, " fbinfo.var.yoffset     = %d\n", (int)w->linux_fb_info.var.yoffset);
    seq_printf(m, " fbinfo.var.bits_per_pxl= %d\n", (int)w->linux_fb_info.var.bits_per_pixel);
    seq_printf(m, " fbinfo.var.grayscale   = %d\n", (int)w->linux_fb_info.var.grayscale);
    seq_printf(m, " fbinfo.var.transp      = (%2d,%2d,%2d)\n", (int)w->linux_fb_info.var.transp.offset,
               (int)w->linux_fb_info.var.transp.length,
               (int)w->linux_fb_info.var.transp.msb_right);
    seq_printf(m, " fbinfo.var.red         = (%2d,%2d,%2d)\n", (int)w->linux_fb_info.var.red.offset,
               (int)w->linux_fb_info.var.red.length,
               (int)w->linux_fb_info.var.red.msb_right);
    seq_printf(m, " fbinfo.var.green       = (%2d,%2d,%2d)\n", (int)w->linux_fb_info.var.green.offset,
               (int)w->linux_fb_info.var.green.length,
               (int)w->linux_fb_info.var.green.msb_right);
    seq_printf(m, " fbinfo.var.blue        = (%2d,%2d,%2d)\n", (int)w->linux_fb_info.var.blue.offset,
               (int)w->linux_fb_info.var.blue.length,
               (int)w->linux_fb_info.var.blue.msb_right);
    seq_printf(m, " fbinfo.var.nonstd      = %d\n", (int)w->linux_fb_info.var.nonstd);
    seq_printf(m, " fbinfo.var.activate    = 0x%x\n", (UINT32)w->linux_fb_info.var.activate);
    seq_printf(m, " fbinfo.var.width(mm)   = %d\n", (int)w->linux_fb_info.var.width);
    seq_printf(m, " fbinfo.var.height(mm)  = %d\n", (int)w->linux_fb_info.var.height);
    seq_printf(m, " fbinfo.var.pixclock    = %d\n", (int)w->linux_fb_info.var.pixclock);
    seq_printf(m, " fbinfo.var.left_margin = %d\n", (int)w->linux_fb_info.var.left_margin);
    seq_printf(m, " fbinfo.var.right_margin= %d\n", (int)w->linux_fb_info.var.right_margin);
    seq_printf(m, " fbinfo.var.upper_margin= %d\n", (int)w->linux_fb_info.var.upper_margin);
    seq_printf(m, " fbinfo.var.lower_margin= %d\n", (int)w->linux_fb_info.var.lower_margin);
    seq_printf(m, " fbinfo.var.hsync_len   = 0x%x\n", (UINT32)w->linux_fb_info.var.hsync_len);
    seq_printf(m, " fbinfo.var.vsync_len   = 0x%x\n", (UINT32)w->linux_fb_info.var.vsync_len);
    seq_printf(m, " fbinfo.var.sync        = 0x%x\n", (UINT32)w->linux_fb_info.var.sync);
    seq_printf(m, " fbinfo.var.vmode       = 0x%x\n", (UINT32)w->linux_fb_info.var.vmode);
    seq_printf(m, " fbinfo.var.rotate      = %d\n", (int)w->linux_fb_info.var.rotate);
    seq_printf(m, "\n");
}

/** print OSD info
 *
 */
static void _FBDEV_PROC_PrintOSDInfo(struct seq_file* m)
{
    int i;
    extern FBDEV_CTX_T* g_dm_ctx;

    for (i = 0; i < 4 ; i++)
    {
        FBDEV_WIN_CTX_T* w = g_dm_ctx->wctx[i];

        if (!g_fbdev_cfg->fb[i].b_active) continue;

        seq_printf(m, "FB(%d)\n", w->fb_dev_id);
        _FBDEV_PROC_DumpWinCtx(w, m);
    }
}

static void _FBDEV_PROC_DumpRegs(struct seq_file* m)
{
    int     i;
    UINT32  val;

    FBDEV_HW_CTX_T* hw_cmn_ctx = FBDEV_GET_HW_CTX();

    UINT32  reg_base = g_fbdev_hwio_cfg->reg_base_addr;
    int     reg_num  = g_fbdev_hwio_cfg->reg_size >> 2;

    if (reg_base && reg_num > 0)
    {
        seq_printf(m, "FBDEV Register : 0x%08x\n", reg_base);

        for (i = 0; i < reg_num; i++)
        {
            OS_RdReg(reg_base + (i << 2), &val);

            seq_printf(m, " 0x%08x (+0x%04x) = %08x\n", reg_base + (i << 2), (i << 2), val);
        }
    }

    /* print more register related to chip */
    if (hw_cmn_ctx && hw_cmn_ctx->ProcHandler)
    {
        hw_cmn_ctx->ProcHandler(FBDEV_HW_PROC_ID_REG_DUMP, m, NULL);
    }
}

static void _FBDEV_PROC_PrintStatus(struct seq_file* m, void* data)
{
    FBDEV_HW_CTX_T* hw_cmn_ctx = FBDEV_GET_HW_CTX();

    LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

    FBDEV_WIN_CTX_T* w = FBDEV_GetWinCtx(fb_dev_id);

    // print each layer info
    if (w)
    {
        _FBDEV_PROC_DumpWinCtx(w, m);

        if (hw_cmn_ctx && hw_cmn_ctx->ProcHandler)
        {
            hw_cmn_ctx->ProcHandler(FBDEV_HW_PROC_ID_DETAIL_INFO, m, NULL);
            seq_printf(m, "\n");
            hw_cmn_ctx->ProcHandler(FBDEV_HW_PROC_ID_OSD_HDR, m, (void*)fb_dev_id);
        }
    }
    // print general osd system info
    else
    {
        osd_drm_dump_context(m);
    }
}

static void _FBDEV_PROC_PrintFBMemStatus(struct seq_file* m, void* data)
{
    FBDEV_WIN_CTX_T* w;
    LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

    FBDEV_HW_CMD_DATA_T cmd_data;
    UINT32 afbc_cap = FBDEV_HW_AFBC_VER_1_0;

    if (RET_OK == FBDEV_ExecHWCommand(FBDEV_HW_CMD_RD_AFBC_CAPS, &cmd_data))
    {
        afbc_cap = cmd_data.gen[0];
    }

    w = FBDEV_GetWinCtx(fb_dev_id);

    /* frame phys, stride, width, height, pixel format, extra info, pixel byte order */
    if (w)
    {
        seq_printf(m, "0x%x %d %d %d %s %s %s\n",
                   (UINT32)w->pixel.osd_bm_paddr,
                   w->pixel.stride,
                   w->pixel.input_win.w,
                   w->pixel.input_win.h,

                   (w->pixel.fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC ? "afbc" :
                    w->pixel.fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC ? "afrc" : "raw"),

                   (w->pixel.fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC ?
                    (afbc_cap == FBDEV_HW_AFBC_VER_1_1 ? "32x8" : "16x16") :
                    w->pixel.fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC ? "16x16" : "none"),

                   (w->pixel.pixel_format == LX_FBDEV_PIXEL_FORMAT_BGR_8888 ? "abgr" :
                    w->pixel.pixel_format == LX_FBDEV_PIXEL_FORMAT_RGB_8888 ? "argb" : "unknown"));
    }
}

static void _FBDEV_PROC_PrintFlipStatus(struct seq_file* m, void* data)
{
    FBDEV_WIN_CTX_T* w;
    LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

    w = FBDEV_GetWinCtx(fb_dev_id);

    if (w)
    {
        seq_printf(m, "%d\n", (UINT32)w->status.fb_flip_cnt);
    }
}

static void _FBDEV_PROC_PrintPanDispStatus(struct seq_file* m, void* data)
{
    FBDEV_WIN_CTX_T* w;
    LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

    w = FBDEV_GetWinCtx(fb_dev_id);

    if (w)
    {
        seq_printf(m, "%d\n", (UINT32)w->status.fb_pan_disp_cnt);
    }
}

/** @} */


