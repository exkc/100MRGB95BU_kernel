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
#ifdef INCLUDE_KDRV_GFX
#define USE_GFX_SCALER
#define GFX_MIN_INPUT_W 12
#define GFX_MIN_OUTPUT_W 2
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
#include <linux/slab.h>          /**< kmalloc() */
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <asm/io.h>
#include <linux/fs.h>            /**< everything\ldots{} */
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)
#include <asm/hardware.h>
#endif

#include <asm/uaccess.h>

#include <linux/device.h>

#include <linux/interrupt.h>     /** irqreturn_t */
#include <linux/irq.h>
#include <asm/irq.h>

#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "fbdev_drm.h"
#include "hma_alloc.h"
#include "os_util.h"
#include "proc_util.h"
#ifdef INCLUDE_KDRV_GFX
#include "gfx_export.h"
#endif

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define SW_CURSOR_W 256
#define SW_CURSOR_H 256


/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------
    Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int  osd_drm_get_fbdev(osd_drm_id id);
int  osd_drm_initialize(struct platform_device* pdev);
bool osd_drm_check_mode(int hdisplay, int vdisplay);
int  osd_drm_flip_image(osd_drm_id id, struct osd_drm_framebuffer* in_fb, unsigned int x, unsigned int y);
int  osd_drm_enable(osd_drm_id id, bool new_state);
void osd_drm_freeze(bool en);
int  osd_drm_set_cursor_region(unsigned int w, unsigned int h);
void osd_drm_vsync_tick(void);
void osd_drm_dump_context(struct seq_file* m);
void osd_drm_init_proc(struct os_proc* osd_pdir);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int osd_drm_init_sw_cursor(void);

static void osd_drm_fb_scale_sw(UINT32* src_image, UINT32 src_pitch, UINT32 src_w, UINT32 src_h, UINT32* dst_image,
                                UINT32 dst_pitch, UINT32 dst_w,
                                UINT32 dst_h);
static void osd_drm_fb_scale(struct osd_drm_framebuffer* src, struct osd_drm_framebuffer* dst);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

struct osd_drm_context
{
    struct
    {
        bool            dst_rgn_valid;

        LX_DIMENSION_T  src_rgn;
        LX_DIMENSION_T  dst_rgn;

        struct osd_drm_framebuffer last_in_fb;
        struct osd_drm_framebuffer last_out_fb;
    }
    cursor;

    void(*vsync_handler)(void);
};

struct osd_drm_sw_cursor
{
#define MAX_SW_CURSOR 2
    int idx;
    phys_addr_t paddr[MAX_SW_CURSOR];
    unsigned int stride;
    unsigned int width;
    unsigned int height;
};

static struct osd_drm_context g_ctx =
{
    .cursor = {
        .dst_rgn_valid = false,
        .src_rgn = {1920, 1080},
        .dst_rgn = {3840, 2160},
    },
};

static struct osd_drm_sw_cursor g_sw_cursor =
{
    .idx = 0,
    .paddr = {0x0, 0x0},
    .width = SW_CURSOR_W,
    .height = SW_CURSOR_H,
};

// auto detect the cursor framebuffer is changed or not
static int detect_cursor_change = 1;
module_param(detect_cursor_change, int, 0644);

static bool drm_freezed = false;
static bool vsync_debug = false;

/*========================================================================================
    Implementation Group (DRM helper function)
========================================================================================*/
int osd_drm_get_fbdev(osd_drm_id id)
{
    switch (id)
    {
        case osd_drm_id_graphic0: return LX_FBDEV_ID_OSD0;

        case osd_drm_id_graphic1: return LX_FBDEV_ID_OSD1;

        case osd_drm_id_cursor:  return LX_FBDEV_ID_CSR0;

        default:                 return -1;
    }
}

// fbdev 없는 환경에서 OSD 출력에 문제가 없도록 조치한다
// fbdev_open 에 준하는 동작을 하도록 한다.
int osd_drm_initialize(struct platform_device* pdev)
{
    FBDEV_OpenDRMContext(pdev, LX_FBDEV_ID_OSD0);
    FBDEV_OpenDRMContext(pdev, LX_FBDEV_ID_OSD1);
    FBDEV_OpenDRMContext(pdev, LX_FBDEV_ID_CSR0);

    osd_drm_init_sw_cursor();

    return 0;
}
EXPORT_SYMBOL(osd_drm_initialize);

bool osd_drm_check_mode(int hdisplay, int vdisplay)
{
    int disp_w;
    int disp_h;

    if (lx_chip_plt() & LX_CHIP_PLT_QUHD)
    {
        disp_w = 7680;
        disp_h = 4320;
    }
    else if (lx_chip_plt() & LX_CHIP_PLT_UHD)
    {
        disp_w = 3840;
        disp_h = 2160;
    }
    else if (lx_chip_plt() & LX_CHIP_PLT_FHD)
    {
        disp_w = 1920;
        disp_h = 1080;
    }
    else
    {
        disp_w = 1366;
        disp_h = 768;
    }

    if (hdisplay <= disp_w && vdisplay <= disp_h)
    {
        return true;
    }
    else
    {
        return false;
    }
}
EXPORT_SYMBOL(osd_drm_check_mode);

static void osd_drm_cursor_get_cursor_scale(struct osd_drm_framebuffer* fb,
        int* h_pos_scale_out, int* v_pos_scale_out,
        int* h_img_scale_out, int* v_img_scale_out)
{
    int new_cursor_w;
    int new_cursor_h;
    int h_pos_scale;
    int v_pos_scale;
    int h_img_scale;
    int v_img_scale;


    // src_rgn, dst_rgn 을 근거로 position scale 값을 구한다.
    h_pos_scale = g_ctx.cursor.dst_rgn.w * 100 / g_ctx.cursor.src_rgn.w;
    v_pos_scale = g_ctx.cursor.dst_rgn.h * 100 / g_ctx.cursor.src_rgn.h;

    // src_rgn, dst_rgn 을 근거로 image scale 값을 구한다.
    // 플랫폼에서 2K 이상의 커서 이미지 리소스가 없으므로, image scale 시에 최대
    // src_rn 을 최대 2K 로 처리해야 한다.
    if (g_ctx.cursor.src_rgn.w <= 1920 && g_ctx.cursor.src_rgn.h <= 1080)
    {
        h_img_scale = g_ctx.cursor.dst_rgn.w * 100 / g_ctx.cursor.src_rgn.w;
        v_img_scale = g_ctx.cursor.dst_rgn.h * 100 / g_ctx.cursor.src_rgn.h;
    }
    else
    {
        h_img_scale = g_ctx.cursor.dst_rgn.w * 100 / 1920;
        v_img_scale = g_ctx.cursor.dst_rgn.h * 100 / 1080;
    }

    new_cursor_w = h_img_scale * fb->width / 100;
    new_cursor_h = v_img_scale * fb->height / 100;

    // cursor scale 된 값이 scale 된 값 이상이면 scale 을 다시 계산한다.
    if (new_cursor_w > SW_CURSOR_W)
    {
        h_img_scale = SW_CURSOR_W * 100 / fb->width;
    }

    if (new_cursor_h > SW_CURSOR_H)
    {
        v_img_scale = SW_CURSOR_H * 100 / fb->height;
    }

#if 0

    // img sacle 의 경우 아래 가정을 해야 한다.
    // webOS 에서 2K 이상의 커서 이미지를 지원하지 않기 때문에, 설사 4K UI 모드라고 해도,
    // 커서 이미지는 2K 로 제한이 되어 있음을 알고 있어야 한다.
    if (g_ctx.cursor.src_rgn.w > 1920)
    {
        h_img_scale = g_ctx.cursor.dst_rgn.w * 100 / 1920;
    }
    else
    {
        h_img_scale = g_ctx.cursor.dst_rgn.w * 100 / g_ctx.cursor.src_rgn.w;
    }

    if (g_ctx.cursor.src_rgn.h > 1080)
    {
        v_img_scale = g_ctx.cursor.dst_rgn.h * 100 / 1080;
    }
    else
    {
        v_img_scale = g_ctx.cursor.dst_rgn.h * 100 / g_ctx.cursor.src_rgn.h;
    }

#endif

    *h_pos_scale_out = h_pos_scale;
    *v_pos_scale_out = v_pos_scale;
    *h_img_scale_out = h_img_scale;
    *v_img_scale_out = v_img_scale;
}

int osd_drm_flip_image(osd_drm_id id, struct osd_drm_framebuffer* in_fb, unsigned int x, unsigned int y)
{
    int ret = -1;
    int fb_dev_id;
    FBDEV_WIN_CTX_T* wctx;

    struct osd_drm_framebuffer out_fb; // modified output framebuffer by HW spec

    int cursor_hw_x = x; // default
    int cursor_hw_y = y; // default

    fb_dev_id = osd_drm_get_fbdev(id);
    FBDEV_CHECK_ERROR(fb_dev_id == -1, return -1, "id(%d) invalid\n", id);

    wctx = FBDEV_GetWinCtx(fb_dev_id);
    FBDEV_CHECK_ERROR(NULL == wctx, return -1, "fb(%d) null winctx\n", fb_dev_id);

    memcpy(&out_fb, in_fb, sizeof(struct osd_drm_framebuffer));

    /* setup global alpha if pixel format is xRGB */
    if (out_fb.fmt & osd_drm_pxlfmt_axxx)
    {
        wctx->pixel.global_alpha_en = FALSE;
    }
    else
    {
        wctx->pixel.global_alpha = 0xff;
        wctx->pixel.global_alpha_en = TRUE;
    }

    // cursor 인 경우 필요시 SW 혹은 GFX 를 활용하여 cursor scaler 을 지원한다.
    // fb 의 내용이 바뀌었다면 cursor image 가 바뀐 것이다.
    if (id == osd_drm_id_cursor)
    {
        unsigned int h_pos_scale;
        unsigned int v_pos_scale;
        unsigned int h_img_scale;
        unsigned int v_img_scale;

        bool cursor_changed = false;

        if (detect_cursor_change)
        {
            if (memcmp(&g_ctx.cursor.last_in_fb, in_fb, sizeof(struct osd_drm_framebuffer)))
            {
                FBDEV_DRM_DEBUG("cursor change detected\n");
                cursor_changed = true;
            }
        }
        else
        {
            cursor_changed = true;
        }

        // TODO: chekc if cursor content is changed ?

        osd_drm_cursor_get_cursor_scale(&out_fb, &h_pos_scale, &v_pos_scale, &h_img_scale, &v_img_scale);

        cursor_hw_x = x * h_pos_scale / 100;
        cursor_hw_y = y * v_pos_scale / 100;

        // remake & scale framebuffer to sw_cursor framebuffer
        if (cursor_changed)
        {
            FBDEV_DRM_DEBUG("cursor_scale: img_scale=%d.%d,%d.%d, pos_scal=%d.%d,%d.%d\n",
                            h_img_scale / 100, h_img_scale % 100,
                            v_img_scale / 100, v_img_scale % 100,
                            h_pos_scale / 100, h_pos_scale % 100,
                            v_pos_scale / 100, v_pos_scale % 100);

            // change framebuffer to sw_cursor image
            out_fb.fbmem = g_sw_cursor.paddr[ g_sw_cursor.idx ];
            out_fb.stride = g_sw_cursor.stride;
            out_fb.width = out_fb.width * h_img_scale / 100;
            out_fb.height = out_fb.height * v_img_scale / 100;
            out_fb.hotspot_x = out_fb.hotspot_x * h_img_scale / 100;
            out_fb.hotspot_y = out_fb.hotspot_y * v_img_scale / 100;

            FBDEV_DRM_DEBUG("org cursor fbmem=0x%llx, stride=%d, size=%dx%d hotspt=%dx%d\n",
                            in_fb->fbmem, in_fb->stride, in_fb->width, in_fb->height, in_fb->hotspot_x, in_fb->hotspot_y);
            FBDEV_DRM_DEBUG("new cursor fbmem=0x%llx, stride=%d, size=%dx%d hotspt=%dx%d\n",
                            out_fb.fbmem, out_fb.stride, out_fb.width, out_fb.height, out_fb.hotspot_x, out_fb.hotspot_y);

            osd_drm_fb_scale(in_fb, &out_fb);

            // save current framebuffer
            memcpy(&g_ctx.cursor.last_in_fb, in_fb, sizeof(struct osd_drm_framebuffer));
            memcpy(&g_ctx.cursor.last_out_fb, &out_fb, sizeof(struct osd_drm_framebuffer));

            g_sw_cursor.idx = (g_sw_cursor.idx + 1) % MAX_SW_CURSOR;
        }
        else
        {
            memcpy(&out_fb, &g_ctx.cursor.last_out_fb, sizeof(struct osd_drm_framebuffer));
        }
    }

    if (unlikely(drm_freezed))
    {
        FBDEV_DRM_DEBUG("drm freezed. ignore update\n");
        ret = 0;
        goto func_exit;
    }

    /* update framebuffer image */
    {
        LX_FBDEV_FB_IMAGE_T fb_image = { };

        fb_image.phys_addr = out_fb.fbmem;
        fb_image.stride = out_fb.stride;
        fb_image.bits_per_pixel = 32;

        switch (out_fb.fmt & osd_drm_pxlfmt_compress_type_mask)
        {
            case osd_drm_pxlfmt_afbc:
                fb_image.fbc_fmt = LX_FBDEV_FBC_FORMAT_AFBC;
                break;

            case osd_drm_pxlfmt_afrc:
                fb_image.fbc_fmt = LX_FBDEV_FBC_FORMAT_AFRC;

                // (2023/09/27)
                // AFRC 포맷일때 DRM 으로 전달되는 stride 가 cu size 에 따라 다양하게 전달됨
                // 2K framebuffer 인 경우
                // cu_size=32B, stride=3840
                // cu_size=24B, stride=2880
                // cu_size=16B, stride=1920
                //
                // OSD kdriver 는 ARGB/ABGR 포맷의 경우 7680 (1920*4) 에 맞춰 구성되어 있으므로,
                // OSD kdriver 로 전달되는 stride 값을 이에 맞게 가공하여 전달하도록 한다.
                //
                // FIXME: 현재 cu_size 32B 로 고정되어 있으나, pixel format 확장 이후 cu_size 에
                // 맞게 stride 값을 알맞게 재조정해야 한다.
                // see http://clm.lge.com/issue/browse/SICDTV-13227
                fb_image.stride *= 2;
                break;

            default:
                fb_image.fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW;
                break;
        }

        if ((out_fb.fmt & osd_drm_pxlfmt_comp_order_mask) == osd_drm_pxlfmt_xbgr)
        {
            fb_image.pixel_fmt = LX_FBDEV_PIXEL_FORMAT_BGR_8888;
        }
        else if ((out_fb.fmt & osd_drm_pxlfmt_comp_order_mask) == osd_drm_pxlfmt_xrgb)
        {
            fb_image.pixel_fmt = LX_FBDEV_PIXEL_FORMAT_RGB_8888;
        }
        else
        {
            fb_image.pixel_fmt = LX_FBDEV_PIXEL_FORMAT_RGB_8888;
        }

        if (id == osd_drm_id_cursor)
        {
            wctx->pixel.csr_size.w = out_fb.width;
            wctx->pixel.csr_size.h = out_fb.height;

            wctx->pixel.csr_hotspot.x = out_fb.hotspot_x;
            wctx->pixel.csr_hotspot.y = out_fb.hotspot_y;

            wctx->pixel.input_win.w = out_fb.width;
            wctx->pixel.input_win.h = out_fb.height;
            wctx->pixel.output_win.w = out_fb.width;
            wctx->pixel.output_win.h = out_fb.height;

            FBDEV_DRM_DEBUG("update cursor_hdr: fbmem=0x%llx, size=%dx%d, stride=%d/%d, pos=%04d,%04d/%04d,%04d, hotspot=%d,%d\n",
                            out_fb.fbmem,
                            out_fb.width,
                            out_fb.height,
                            out_fb.stride,
                            fb_image.stride,
                            x,
                            y,
                            cursor_hw_x,
                            cursor_hw_y,
                            out_fb.hotspot_x,
                            out_fb.hotspot_y);
        }
        else
        {
            wctx->pixel.input_win.w = out_fb.width;
            wctx->pixel.input_win.h = out_fb.height;

            FBDEV_DRM_DEBUG("update graphic: fbmem=0x%llx, size=%dx%d, stride=%d/%d\n",
                            out_fb.fbmem,
                            out_fb.width,
                            out_fb.height,
                            out_fb.stride,
                            fb_image.stride);
        }

        wctx->pixel.output_win.x = cursor_hw_x;
        wctx->pixel.output_win.y = cursor_hw_y;

        FBDEV_FlipFBImage(fb_dev_id, &fb_image, TRUE);
    }

    // (note) DO NOT wait vsync !! it's handled by DRM framework

    ret = 0;
func_exit:
    return ret;
}

EXPORT_SYMBOL(osd_drm_flip_image);

int osd_drm_enable(osd_drm_id id, bool new_state)
{
    bool last_state;
    int fb_dev_id = osd_drm_get_fbdev(id);
    FBDEV_CHECK_ERROR(fb_dev_id == -1, return -1, "invalid id %d\n", id);

    last_state = FBDEV_GetOSDEnable(fb_dev_id);

    if (last_state != new_state)
    {
        if (unlikely(drm_freezed))
        {
            FBDEV_DRM_DEBUG("drm freezed. ignore state(%d)\n", new_state);
            return 0;
        }

        // (2023/07/24) drmplanes-atomic 테스트중 드라이버 코드 보완 필요
        // UI on 요청시, E-streamer 가 동작중이라면 강제로 off 조치될 수 있도록 한다.
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0 && new_state)
        {
            if (FBDEV_GetOSDEnable(LX_FBDEV_ID_OSD1))
            {
                FBDEV_NOTI("id=%d (fb%d), view=1 -> 0  (called by driver due to UI ON)\n", osd_drm_id_graphic1, LX_FBDEV_ID_OSD1);
                FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD1, FALSE);
            }
        }

        FBDEV_NOTI("id=%d (fb%d), view=%d -> %d\n", id, fb_dev_id, last_state, new_state);

        FBDEV_SetOSDEnable(fb_dev_id, new_state);
    }

    return 0;
}

EXPORT_SYMBOL(osd_drm_enable);

void osd_drm_freeze(bool en)
{
    drm_freezed = en;
}

void osd_drm_register_vsync_handler(void(*handler)(void))
{
    g_ctx.vsync_handler = handler;
}

EXPORT_SYMBOL(osd_drm_register_vsync_handler);

// 현재의 설정을 감지하여, cursor region 을 판단한다.
// sw cursor 를 생성한다.
static int osd_drm_init_sw_cursor(void)
{
#ifdef INCLUDE_KDRV_GFX
    int i;
    int ret = -1;
    int surf_fd = -1;

    g_sw_cursor.idx = 0;
    g_sw_cursor.width = SW_CURSOR_W;
    g_sw_cursor.height = SW_CURSOR_H;
    g_sw_cursor.stride = g_sw_cursor.width * 4;

    gfx_export_lock_device();

    for (i = 0; i < MAX_SW_CURSOR; i++)
    {
        int fbsize = g_sw_cursor.width * g_sw_cursor.height * 4;

        g_sw_cursor.paddr[i] = hma_alloc("surface", fbsize, PAGE_SIZE);

        FBDEV_CHECK_ERROR(0x0 == g_sw_cursor.paddr[i],
                          goto func_exit,
                          "can't alloc sw_cursor. fbsize=%d\n", fbsize);

        // TODO: clear memory
        surf_fd = gfx_export_alloc_surface(g_sw_cursor.paddr[i], g_sw_cursor.width, g_sw_cursor.height, g_sw_cursor.stride);

        if (surf_fd >= 0)
        {
            LX_RECT_T rect = { 0, 0, g_sw_cursor.width, g_sw_cursor.height };
            gfx_export_fill_simple(surf_fd, rect, 0x00000000);

            gfx_export_free_surface(surf_fd);
        }
    }

    // detect default cursor region
    osd_drm_set_cursor_region(1920, 1080);

    ret = 0;
func_exit:
    gfx_export_unlock_device();

    return ret;
#else
    return 0;
#endif
}

int osd_drm_set_cursor_region(unsigned int w, unsigned int h)
{
    FBDEV_HW_CMD_DATA_T hw_cmd;

    FBDEV_DRM_DEBUG("org.src_rgn=%d,%d, org.dst_rgn=%dx%d, new.src_rgn=%dx%d\n",
                    g_ctx.cursor.src_rgn.w, g_ctx.cursor.src_rgn.h,
                    g_ctx.cursor.dst_rgn.w, g_ctx.cursor.dst_rgn.h,
                    w, h);

    // query current display resolution & initialize dst_rgn
    if (!g_ctx.cursor.dst_rgn_valid)
    {
        if (RET_OK == FBDEV_ExecHWCommand(FBDEV_HW_CMD_RD_DISP_SIZE, &hw_cmd))
        {
            g_ctx.cursor.dst_rgn.w = hw_cmd.gen[0];
            g_ctx.cursor.dst_rgn.h = hw_cmd.gen[1];

            g_ctx.cursor.dst_rgn_valid = true;
        }
    }

    // check if src and dst rgn is changed or not
    if (g_ctx.cursor.src_rgn.w == w && g_ctx.cursor.src_rgn.h == h)
    {
        return 0;
    }

    g_ctx.cursor.src_rgn.w = w;
    g_ctx.cursor.src_rgn.h = h;

    FBDEV_DRM_DEBUG("src_rgn=%d,%d updated\n", g_ctx.cursor.src_rgn.w, g_ctx.cursor.src_rgn.h);

    return 0;
}

EXPORT_SYMBOL(osd_drm_set_cursor_region);

void osd_drm_vsync_tick(void)
{
    if (g_ctx.vsync_handler)
    {
        g_ctx.vsync_handler();
    }

    if (unlikely(vsync_debug))
    {
        FBDEV_DRM_DEBUG("vsync tick\n");
    }
}

//
static void osd_drm_fb_scale(struct osd_drm_framebuffer* src, struct osd_drm_framebuffer* dst)
{
#ifdef USE_GFX_SCALER

    bool hw_scale = true;

    // HW limitation from kad-gal
    if (src->width < GFX_MIN_INPUT_W) hw_scale = false;

    if (dst->width < GFX_MIN_OUTPUT_W) hw_scale = false;

    if (hw_scale)
    {
        int src_fd = -1;
        int dst_fd = -1;

        LX_RECT_T src_rect = { 0, 0, src->width, src->height };
        LX_RECT_T dst_rect = { 0, 0, dst->width, dst->height };

        gfx_export_lock_device();

        src_fd = gfx_export_alloc_surface(src->fbmem, src->stride, src->width, src->height);
        dst_fd = gfx_export_alloc_surface(dst->fbmem, dst->stride, dst->width, dst->height);

        FBDEV_DRM_DEBUG("src_fd = 0x%x, dst_fd = 0x%x\n", src_fd, dst_fd);

        FBDEV_CHECK_ERROR(src_fd < 0,
                          goto hw_func_exit,
                          "can't alloc src surface\n");

        FBDEV_CHECK_ERROR(dst_fd < 0,
                          goto hw_func_exit,
                          "can't alloc dst surface\n");

        FBDEV_DRM_DEBUG("hw_scaler. src_paddr=0x%llx fd=%d  ptich=%d size=%dx%d, dst_paddr=%llx fd=%d ptich=%d size=%dx%d\n",
                        src->fbmem, src_fd, src->stride, src->width, src->height,
                        dst->fbmem, dst_fd, dst->stride, dst->width, dst->height);

        gfx_export_blit_simple(src_fd, src_rect, dst_fd, dst_rect);
        FBDEV_DRM_DEBUG("done..\n");

hw_func_exit:

        if (src_fd >= 0) gfx_export_free_surface(src_fd);

        if (dst_fd >= 0) gfx_export_free_surface(dst_fd);

        gfx_export_unlock_device();
    }
    else
#endif
    {
        OS_CACHE_MAP_T src_cmap;
        OS_CACHE_MAP_T dst_cmap;

        OS_OpenCacheMap(&src_cmap, (ULONG)src->fbmem, src->stride * src->height);
        OS_OpenCacheMap(&dst_cmap, (ULONG)dst->fbmem, dst->stride * dst->height);

        OS_InvalCacheMap(&src_cmap, 0, src->stride * src->height);

        memset(dst_cmap.virt_addr, 0x0, dst->stride * dst->height);

        FBDEV_DRM_DEBUG("sw_scaler. src_paddr=0x%llx ptich=%d size=%dx%d, dst_paddr=%llx ptich=%d size=%dx%d\n",
                        src->fbmem, src->stride, src->width, src->height,
                        dst->fbmem, dst->stride, dst->width, dst->height);

        osd_drm_fb_scale_sw(src_cmap.virt_addr, src->stride, src->width, src->height, dst_cmap.virt_addr, dst->stride,
                            dst->width, dst->height);

        OS_CleanCacheMap(&dst_cmap, 0, dst->stride * dst->height);

        OS_CloseCacheMap(&src_cmap);
        OS_CloseCacheMap(&dst_cmap);
    }
}

static void __attribute__((used)) osd_drm_fb_scale_sw(UINT32* src_image, UINT32 src_pitch, UINT32 src_w, UINT32 src_h,
        UINT32* dst_image,
        UINT32 dst_pitch, UINT32 dst_w,
        UINT32 dst_h)
{
    unsigned int coef_w, coef_h, x, y;
    unsigned int pixel1, pixel2, pixel3, pixel4;
    unsigned int hc1, hc2, wc1, wc2, off_x, off_y;
    unsigned int r, g, b, a;
    unsigned int* dst_ptr;

    unsigned int src_inc32 = (src_pitch >> 2);  /** assume 32bpp */
    unsigned int dst_inc32 = (dst_pitch >> 2);  /** assume 32bpp */

    /* calculate step_sz, if dst size is less than 1, set step_sz to zero for preventing 'divide by zero' error */
    unsigned int w_step_sz = (dst_w > 1) ? ((src_w - 1) << 16) / (dst_w - 1) : 0x0;
    unsigned int h_step_sz = (dst_h > 1) ? ((src_h - 1) << 16) / (dst_h - 1) : 0x0;

    coef_h = 0;

    for (y = 0; y < dst_h ; y++)
    {
        off_y   = (coef_h >> 16);
        hc2     = (coef_h >> 9) & 127;
        hc1     = 128 - hc2;

        coef_w  = 0;
        dst_ptr = dst_image;

        for (x = 0; x < dst_w ; x++)
        {
            off_x   = (coef_w >> 16);
            wc2     = (coef_w >> 9) & 127;
            wc1     = 128 - wc2;

            pixel1 = *(src_image + off_y  * src_inc32 + off_x);
            pixel2 = *(src_image + (off_y + 1) * src_inc32 + off_x);
            pixel3 = *(src_image + off_y  * src_inc32 + off_x + 1);
            pixel4 = *(src_image + (off_y + 1) * src_inc32 + off_x + 1);

            a = ((((pixel1 >> 24) & 255) * hc1 + ((pixel2 >> 24) & 255) * hc2) * wc1 +
                 (((pixel3 >> 24) & 255) * hc1 + ((pixel4 >> 24) & 255) * hc2) * wc2) >> 14;
            r = ((((pixel1 >> 16) & 255) * hc1 + ((pixel2 >> 16) & 255) * hc2) * wc1 +
                 (((pixel3 >> 16) & 255) * hc1 + ((pixel4 >> 16) & 255) * hc2) * wc2) >> 14;
            g = ((((pixel1 >> 8) & 255) * hc1 + ((pixel2 >> 8) & 255) * hc2) * wc1 +
                 (((pixel3 >> 8) & 255)  * hc1 + ((pixel4 >> 8) & 255) * hc2) * wc2) >> 14;
            b = ((((pixel1 >> 0) & 255) * hc1 + ((pixel2 >> 0) & 255) * hc2) * wc1 +
                 (((pixel3 >> 0) & 255)  * hc1 + ((pixel4 >> 0) & 255) * hc2) * wc2) >> 14;

            *dst_ptr++ = (a << 24) | (r << 16) | (g << 8) | (b);
            coef_w += w_step_sz;
        }

        coef_h      += h_step_sz;
        dst_image   += dst_inc32;
    }
}

/*========================================================================================
    Implementation Group (proc test function)
========================================================================================*/
enum
{
    PROC_ID_TEST_RENDER = 0,
    PROC_ID_OSD_ENABLE,
    PROC_ID_CHECK_MODE,
    PROC_ID_VSYNC_DEBUG,
    PROC_ID_CURSOR_REGION,
    PROC_ID_DRM_FREEZE,
};

struct osd_drm_symbol_desc
{
    const char* name;
    const uint32_t id;
};

static struct osd_drm_symbol_desc plane_name_desc[] =
{
    { "grp0", osd_drm_id_graphic0 },
    { "grp1", osd_drm_id_graphic1 },
    { "grp2", osd_drm_id_graphic2 },
    { "grp3", osd_drm_id_graphic3 },
    { "csr0", osd_drm_id_cursor },
};

static struct osd_drm_symbol_desc pxlfmt_name_desc[] =
{
    { "argb", osd_drm_pxlfmt_argb},
    { "abgr", osd_drm_pxlfmt_abgr},
    { "afbc_xrgb", osd_drm_pxlfmt_afbc_xrgb},
    { "afbc_xbgr", osd_drm_pxlfmt_afbc_xbgr},
    { "afbc_argb", osd_drm_pxlfmt_afbc_argb},
    { "afbc_abgr", osd_drm_pxlfmt_afbc_abgr},
    { "afrc_xrgb", osd_drm_pxlfmt_afrc_xrgb},
    { "afrc_xbgr", osd_drm_pxlfmt_afrc_xbgr},
    { "afrc_argb", osd_drm_pxlfmt_afrc_argb},
    { "afrc_abgr", osd_drm_pxlfmt_afrc_abgr},
};


static int osd_drm_read_proc_handler(UINT32 proc_id, char* buffer, int size, void* data)
{
    int ret;

    switch (proc_id)
    {
        case PROC_ID_TEST_RENDER:
        {
            int len = 0;
            len += sprintf(buffer + len, "drm helper, test render\n");
            len += sprintf(buffer + len,
                           "usage) echo osd_drm_id fbmem width height stride pxlfmt [hotpot_x hotspot_y out_x out_y] > test_render\n");
            len += sprintf(buffer + len, "osd_drm_id: \n");
            len += sprintf(buffer + len, "   grp0 (prmary)\n");
            len += sprintf(buffer + len, "   grp1 (prmary)\n");
            len += sprintf(buffer + len, "   csr0 (cursor)\n");
            len += sprintf(buffer + len, "pxlfmt: \n");
            len += sprintf(buffer + len, "   argb (ARGB RAW)\n");
            len += sprintf(buffer + len, "   abgr (ABGR RAW)\n");
            len += sprintf(buffer + len, "   afbc_argb (ARGB AFBC)\n");
            len += sprintf(buffer + len, "   afbc_abgr (ABGR AFBC)\n");
            ret = len;
        }
        break;

        case PROC_ID_CHECK_MODE:
        {
            int len = 0;
            len += sprintf(buffer + len, "1920x1080: %s\n", osd_drm_check_mode(1920, 1080) ? "ok" : "err");
            len += sprintf(buffer + len, "3840x2160: %s\n", osd_drm_check_mode(3840, 2160) ? "ok" : "err");
            len += sprintf(buffer + len, "7680x4320: %s\n", osd_drm_check_mode(7680, 4320) ? "ok" : "err");
            ret = len;
        }
        break;

        case PROC_ID_OSD_ENABLE:
        {
            int len = 0;
            len += sprintf(buffer + len, "drm helper, osd enable/disable for debug\n");
            len += sprintf(buffer + len, "usage) echo osd_drm_id VAL > enable\n");
            len += sprintf(buffer + len, "osd_drm_id: \n");
            len += sprintf(buffer + len, "   grp0 (prmary)\n");
            len += sprintf(buffer + len, "   grp1 (prmary)\n");
            len += sprintf(buffer + len, "   csr0 (cursor)\n");
            len += sprintf(buffer + len, "VAL: \n");
            len += sprintf(buffer + len, "      0 (off)\n");
            len += sprintf(buffer + len, "      1 (on)\n");
            ret = len;
        }
        break;

        case PROC_ID_DRM_FREEZE:
        {
            int len = 0;
            len += sprintf(buffer + len, "drm helper, freeze for debug\n");
            len += sprintf(buffer + len, "usage) echo VAL > freeze\n");
            ret = len;
        }
        break;

        case PROC_ID_VSYNC_DEBUG:
        {
            int len = 0;
            len += sprintf(buffer + len, "drm helper, monitor vsync tick\n");
            len += sprintf(buffer + len, "usage) echo VAL > vsync_debug\n");
            len += sprintf(buffer + len, "VAL: \n");
            len += sprintf(buffer + len, "      0 (off)\n");
            len += sprintf(buffer + len, "      1 (on)\n");
            ret = len;
        }
        break;

        case PROC_ID_CURSOR_REGION:
        {
            int len = 0;
            len += sprintf(buffer + len, "drm helper, get/set cursor region\n");
            len += sprintf(buffer + len, "usage) echo width height > cursor_region\n");
            len += sprintf(buffer + len, "\n");
            len += sprintf(buffer + len, "cursor.src_rgn.w: %d\n", g_ctx.cursor.src_rgn.w);
            len += sprintf(buffer + len, "cursor.src_rgn.h: %d\n", g_ctx.cursor.src_rgn.h);
            len += sprintf(buffer + len, "cursor.dst_rgn.w: %d\n", g_ctx.cursor.dst_rgn.w);
            len += sprintf(buffer + len, "cursor.dst_rgn.h: %d\n", g_ctx.cursor.dst_rgn.h);
            ret = len;
        }
        break;

        default:
        {
            ret = sprintf(buffer, "%s(%d)\n", "unimplemented read proc", proc_id);
        }
    }

    return ret;
}

static int osd_drm_write_proc_handler(UINT32 proc_id, char* buffer, int size, void* data)
{
    switch (proc_id)
    {
        case PROC_ID_TEST_RENDER:
        {
            struct osd_drm_framebuffer osd_fb;

            uint32_t osd_drm_id;
            osd_drm_pxlfmt pxlfmt;
            uint32_t fbmem, width, height, stride;
            uint32_t hotspot_x = 0, hotspot_y = 0, out_x = 0, out_y = 0;
            char plane_text[16];
            char pxlfmt_text[16];
            int i;

            int cnt = sscanf(buffer, " %s %x %d %d %d %s %d %d %d %d",
                             plane_text, &fbmem, &width, &height, &stride, pxlfmt_text,
                             &hotspot_x, &hotspot_y, &out_x, &out_y);

            if (cnt < 6)
            {
                FBDEV_NOTI("PROC_ID_TEST_RENDER, insufficient args=%d < 6\n", cnt);
                break;
            }

            osd_drm_id = osd_drm_id_graphic0;
            pxlfmt = osd_drm_pxlfmt_afbc_abgr;

            for (i = 0; i < NELEMENTS(plane_name_desc); i++)
            {
                if (!strcmp(plane_name_desc[i].name, plane_text))
                {
                    osd_drm_id = plane_name_desc[i].id;
                    break;
                }
            }

            for (i = 0; i < NELEMENTS(pxlfmt_name_desc); i++)
            {
                if (!strcmp(pxlfmt_name_desc[i].name, pxlfmt_text))
                {
                    pxlfmt = pxlfmt_name_desc[i].id;
                    break;
                }
            }

            memset(&osd_fb, 0x0, sizeof(struct osd_drm_framebuffer));

            osd_fb.fbmem = fbmem;
            osd_fb.width = width;
            osd_fb.height = height;
            osd_fb.stride = stride;
            osd_fb.fmt = pxlfmt;
            osd_fb.hotspot_x = hotspot_x;
            osd_fb.hotspot_y = hotspot_y;

            FBDEV_NOTI("PROC_ID_TEST_RENDER, id=%4s(%d) osd_fb=0x%08llx,%d,%d,%d,%s(0x%02x), hot=%dx%d, pos=%dx%d\n",
                       plane_text, osd_drm_id, osd_fb.fbmem, osd_fb.width, osd_fb.height, osd_fb.stride, pxlfmt_text, osd_fb.fmt,
                       osd_fb.hotspot_x, osd_fb.hotspot_y, out_x, out_y);

            osd_drm_flip_image(osd_drm_id, &osd_fb, out_x, out_y);
        }
        break;

        case PROC_ID_OSD_ENABLE:
        {
            uint32_t osd_drm_id;
            uint32_t on_off;
            char plane_text[16];
            int i;

            int cnt = sscanf(buffer, " %s %d", plane_text, &on_off);

            if (cnt < 2)
            {
                FBDEV_NOTI("PROC_ID_OSD_ENABLE, insufficient args=%d < 2\n", cnt);
                break;
            }

            osd_drm_id = osd_drm_id_graphic0;

            for (i = 0; i < NELEMENTS(plane_name_desc); i++)
            {
                if (!strcmp(plane_name_desc[i].name, plane_text))
                {
                    osd_drm_id = plane_name_desc[i].id;
                    break;
                }
            }

            osd_drm_enable(osd_drm_id, on_off);
        }
        break;

        case PROC_ID_DRM_FREEZE:
        {
            UINT32 ctrl;
            sscanf(buffer, " %d", &ctrl);

            osd_drm_freeze(ctrl);
        }
        break;

        case PROC_ID_VSYNC_DEBUG:
        {
            uint32_t on_off;

            sscanf(buffer, " %d", &on_off);

            vsync_debug = (on_off) ? true : false;
        }
        break;

        case PROC_ID_CURSOR_REGION:
        {
            uint32_t w, h;

            int cnt = sscanf(buffer, " %d %d", &w, &h);

            if (cnt < 2)
            {
                FBDEV_NOTI("PROC_ID_CURSOR_REGION, insufficient args=%d < 2\n", cnt);
                break;
            }

            osd_drm_set_cursor_region(w, h);
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }

    return strlen(buffer);
}

void osd_drm_dump_context(struct seq_file* m)
{
    int i;

    seq_printf(m, "<osd_drm info>\n");

    seq_printf(m, "osd_drm.freezed: %d\n", drm_freezed);

    seq_printf(m, "osd_drm.cursor.src_rgn.w: %d\n", g_ctx.cursor.src_rgn.w);
    seq_printf(m, "osd_drm.cursor.src_rgn.h: %d\n", g_ctx.cursor.src_rgn.h);
    seq_printf(m, "osd_drm.cursor.dst_rgn.w: %d\n", g_ctx.cursor.dst_rgn.w);
    seq_printf(m, "osd_drm.cursor.dst_rgn.h: %d\n", g_ctx.cursor.dst_rgn.h);

    for (i = 0; i < MAX_SW_CURSOR; i++)
    {
        seq_printf(m, "osd_drm.sw_cursor.addr[%d]: 0x%08llx\n", i, g_sw_cursor.paddr[i]);
    }

    seq_printf(m, "osd_drm.sw_cursor.width: %d\n", g_sw_cursor.width);
    seq_printf(m, "osd_drm.sw_cursor.height: %d\n", g_sw_cursor.height);
}

static int osd_drm_print_status(struct seq_file* m, void* data)
{
    osd_drm_dump_context(m);

    return 0;
}

void osd_drm_init_proc(struct os_proc* osd_pdir)
{
    struct os_proc* pdir = os_proc_create_dir(osd_pdir, "drm-helper", osd_drm_read_proc_handler,
                           osd_drm_write_proc_handler);

    os_proc_create_file(pdir, "test_render",  PROC_ID_TEST_RENDER, NULL);
    os_proc_create_file(pdir, "freeze",  PROC_ID_DRM_FREEZE, NULL);
    os_proc_create_file(pdir, "enable",  PROC_ID_OSD_ENABLE, NULL);
    os_proc_create_file(pdir, "check_mode",  PROC_ID_CHECK_MODE, NULL);
    os_proc_create_file(pdir, "vsync_debug",  PROC_ID_VSYNC_DEBUG, NULL);
    os_proc_create_file(pdir, "cursor_region",  PROC_ID_CURSOR_REGION, NULL);

    os_proc_create_seq_file(pdir, "status", osd_drm_print_status, NULL, NULL);
}

