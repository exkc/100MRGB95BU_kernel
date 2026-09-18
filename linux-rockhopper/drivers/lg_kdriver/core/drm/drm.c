/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/platform_device.h>

#include <drm/drm_atomic_helper.h>
#include <drm/drm_drv.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
#include <drm/drm_fb_cma_helper.h>
#else
#include <drm/drm_fb_dma_helper.h>
#endif
#include <drm/drm_fb_helper.h>
#include <drm/drm_fourcc.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
#include <drm/drm_gem_dma_helper.h>
#else
#include <drm/drm_gem_cma_helper.h>
#endif
#include <drm/drm_gem_framebuffer_helper.h>
#include <drm/drm_vblank.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>
#include <drm/drm_crtc_helper.h>
#include <drm/drm_framebuffer.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
#include <drm/drm_atomic.h>
#include <drm/drm_atomic_helper.h>
#endif
#include "fbdev_drm.h"
#include "hma_alloc.h"
#include "chma.h"
#include "logm.h"

logm_define(drm, log_level_info);

#define trace(fmt,args...)  logm_trace(drm,fmt,##args)
#define debug(fmt,args...)  logm_debug(drm,fmt,##args)
#define info(fmt,args...)   logm_info(drm,fmt,##args)
#define noti(fmt,args...)   logm_noti(drm,fmt,##args)
#define warn(fmt,args...)   logm_warning(drm,fmt,##args)
#define error(fmt,args...)  logm_error(drm,fmt,##args)

#define FCC_FMT     "c%c%c%c"
#define FCC_ARG(fcc)    ((fcc)&0xff), \
            (((fcc)>>8)&0xff), \
            (((fcc)>>16)&0xff), \
            (((fcc)>>24)&0xff)

#ifndef DRM_FORMAT_MOD_ARM_CODE
#define DRM_FORMAT_MOD_ARM_CODE(__type, __val) \
	fourcc_mod_code(ARM, ((((__u64)(__type)) << 52) | ((__val)&0x000fffffffffffffULL)))
#endif

#ifndef DRM_FORMAT_MOD_ARM_AFRC
#define DRM_FORMAT_MOD_ARM_AFRC(__afrc_mode) DRM_FORMAT_MOD_ARM_CODE(DRM_FORMAT_MOD_ARM_TYPE_AFRC, __afrc_mode)
#endif

#ifndef DRM_FORMAT_MOD_ARM_TYPE_AFRC
#define DRM_FORMAT_MOD_ARM_TYPE_AFRC 0x02
#endif

#ifndef AFRC_FORMAT_MOD_CU_SIZE_16
#define AFRC_FORMAT_MOD_CU_SIZE_16 (1ULL)
#endif

#ifndef AFRC_FORMAT_MOD_CU_SIZE_24
#define AFRC_FORMAT_MOD_CU_SIZE_24 (2ULL)
#endif

#ifndef AFRC_FORMAT_MOD_CU_SIZE_32
#define AFRC_FORMAT_MOD_CU_SIZE_32 (3ULL)
#endif

#ifndef AFRC_FORMAT_MOD_CU_SIZE_P0
#define AFRC_FORMAT_MOD_CU_SIZE_P0(__afrc_cu_size) (__afrc_cu_size)
#endif

#ifndef AFRC_FORMAT_MOD_LAYOUT_SCAN
#define AFRC_FORMAT_MOD_LAYOUT_SCAN ((1ULL) << 8)
#endif

enum {
	LG1K_PLANE_IMG0 = 0,
	LG1K_PLANE_IMG1,
	LG1K_PLANE_CURSOR,

	LG1K_MAX_PLANE,
};

#define MAX_CURSOR_W        128
#define MAX_CURSOR_H        128

static bool use_cursor = 1;
module_param(use_cursor, bool, 0644);

static bool use_overlay = 1;
module_param(use_overlay, bool, 0644);

struct lg1k_drm_crtc {
	struct drm_crtc base;

	struct {
		int x;
		int y;
		int hot_x;
		int hot_y;
		int width;
		int height;
		int max_width;
		int max_height;
	} cursor;

	// TODO: add anything if necessary
};

struct lg1k_drm_plane {
	struct drm_plane base;

	unsigned int osdid;

	// TODO: add anything if necessary
};

#define to_lg1k_crtc(x)   container_of(x, struct lg1k_drm_crtc, base)
#define to_lg1k_plane(x)  container_of(x, struct lg1k_drm_plane, base)

// lg1k drm device
struct lg1k_drm_priv {
	struct platform_device *pdev;
	struct drm_device *drm;

	struct lg1k_drm_crtc crtc;
	struct lg1k_drm_plane plane[LG1K_MAX_PLANE];

	struct drm_encoder encoder;
	struct drm_connector connector;

	bool vsync_enabled;
	bool graphic_enabled;
	bool cursor_enabled;
};

struct lg1k_drm_priv *g_priv;

static
struct drm_framebuffer *lg1k_drm_gem_fb_create(struct drm_device *dev,
					       struct drm_file *file,
					       const struct drm_mode_fb_cmd2
					       *mode_cmd)
{
	int i;
	int nr_pitches;
	struct drm_mode_fb_cmd2 fb_cmd;

	memcpy(&fb_cmd, mode_cmd, sizeof(struct drm_mode_fb_cmd2));

	nr_pitches = sizeof(fb_cmd.pitches) / sizeof(fb_cmd.pitches[0]);

	// FIXME: 64B align 정보를 얻어올 수 있어야 함.
	for (i = 0; i < nr_pitches; i++) {
		fb_cmd.pitches[i] = ALIGN(fb_cmd.pitches[i], 64);
	}

	return drm_gem_fb_create(dev, file, &fb_cmd);
}

static
const struct drm_format_info *search_info(const struct drm_format_info *infos,
					  int num_infos, unsigned int format)
{
	int i;
	for (i = 0; i < num_infos; i++)
		if (infos[i].format == format)
			return &infos[i];
	return NULL;
}

static
const struct drm_format_info *lg1k_get_format_info(const struct drm_mode_fb_cmd2
						   *mode_cmd)
{
	const struct drm_format_info *info = NULL;

	if (mode_cmd->modifier[0] ==
	    DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 |
				    AFBC_FORMAT_MOD_SPARSE)
	    ) {
		static const struct drm_format_info formats[] = {
			{
			 .format = DRM_FORMAT_ABGR8888,
			 .depth = 32,
			 .num_planes = 1,
			 .cpp = {4,},
			 .block_w = {16,},
			 .block_h = {16,},
			 .hsub = 1,
			 .vsub = 1,
			 .has_alpha = true,
			 },
			{
			 .format = DRM_FORMAT_XBGR8888,
			 .depth = 24,
			 .num_planes = 1,
			 .cpp = {4,},
			 .block_w = {16,},
			 .block_h = {16,},
			 .hsub = 1,
			 .vsub = 1,
			 .has_alpha = false,
			 },
		};

		info =
		    search_info(formats, ARRAY_SIZE(formats),
				mode_cmd->pixel_format);
	} else if (mode_cmd->modifier[0] ==
		   DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 |
					   AFBC_FORMAT_MOD_SPLIT |
					   AFBC_FORMAT_MOD_SPARSE)
	    ) {
		static const struct drm_format_info formats[] = {
			{
			 .format = DRM_FORMAT_ABGR8888,
			 .depth = 32,
			 .num_planes = 1,
			 .cpp = {4,},
			 .block_w = {32,},
			 .block_h = {8,},
			 .hsub = 1,
			 .vsub = 1,
			 .has_alpha = true,
			 },
			{
			 .format = DRM_FORMAT_XBGR8888,
			 .depth = 24,
			 .num_planes = 1,
			 .cpp = {4,},
			 .block_w = {32,},
			 .block_h = {8,},
			 .hsub = 1,
			 .vsub = 1,
			 .has_alpha = false,
			 },
		};

		info =
		    search_info(formats, ARRAY_SIZE(formats),
				mode_cmd->pixel_format);
	} else
	    if ((((mode_cmd->modifier[0] >> 56) & 0xff) ==
		 DRM_FORMAT_MOD_VENDOR_ARM)
		&& (((mode_cmd->modifier[0] >> 52) & 0x0f) ==
		    DRM_FORMAT_MOD_ARM_TYPE_AFRC)
	    ) {
		static const struct drm_format_info formats[] = {
			{
			 .format = DRM_FORMAT_ABGR8888,
			 .depth = 32,
			 .num_planes = 1,
			 .cpp = {},
			 .block_w = {},
			 .block_h = {},
			 .hsub = 1,
			 .vsub = 1,
			 .has_alpha = true,
			 },
			{
			 .format = DRM_FORMAT_XBGR8888,
			 .depth = 24,
			 .num_planes = 1,
			 .cpp = {},
			 .block_w = {},
			 .block_h = {},
			 .hsub = 1,
			 .vsub = 1,
			 .has_alpha = false,
			 },
		};

		info =
		    search_info(formats, ARRAY_SIZE(formats),
				mode_cmd->pixel_format);
	}

	if (info)
		return info;
	return drm_format_info(mode_cmd->pixel_format);
}

static const struct drm_mode_config_funcs mode_config_funcs = {
	.fb_create = lg1k_drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
	.get_format_info = lg1k_get_format_info,
};

static int lg1k_connector_get_modes(struct drm_connector *connector)
{
	static const struct drm_display_mode modes[] = {
		/* *INDENT-OFF* */
		// 1280x720@60Hz
		{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250,
				1280, 1390, 1430, 1650, 0,
				720, 725, 730, 750, 0,
			   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5 ,8, 0))
			  .vrefresh = 60,
#endif
			  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
		// 1920x1080@60Hz
		{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500,
				1920, 2008, 2052, 2200, 0,
				1080, 1084, 1089, 1125, 0,
			   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5 ,8, 0))
			  .vrefresh = 60,
#endif
			  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },

		// 3840x2160@60Hz
		{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000,
			   3840, 4016, 4104, 4400, 0,
			   2160, 2168, 2178, 2250, 0,
			   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5 ,8, 0))
			  .vrefresh = 60,
#endif
			  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },

		// 7680x4320@60Hz
		{ DRM_MODE("7680x4320", DRM_MODE_TYPE_DRIVER, 2376000,
				7680, 8232, 8408, 9000, 0,
				4320, 4336, 4356, 4400, 0,
			   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5 ,8, 0))
			  .vrefresh = 60,
#endif
			  .picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9, },
		/* *INDENT-ON* */
	};
	int i;
	int count;
	int array_size = ARRAY_SIZE(modes);

	count = 0;

	for (i = 0; i < array_size; i++) {
		struct drm_display_mode *mode;

		if (!osd_drm_check_mode(modes[i].hdisplay, modes[i].vdisplay))
			continue;

		mode = drm_mode_duplicate(connector->dev, &modes[i]);

		if (mode) {
			info("mode %dx%d add ok\n", modes[i].hdisplay,
			     modes[i].vdisplay);
			drm_mode_probed_add(connector, mode);
			count++;
		} else {
			info("mode %dx%d add fail\n", modes[i].hdisplay,
			     modes[i].vdisplay);
		}
	}

	drm_set_preferred_mode(connector, 1920, 1080);

	return count;
}

static enum drm_mode_status lg1k_connector_mode_valid(struct drm_connector
						      *connector, struct drm_display_mode
						      *mode)
{
	debug("\"%s\", %dx%d\n", mode->name, mode->hdisplay, mode->vdisplay);

	return MODE_OK;
}

static enum drm_mode_status lg1k_crtc_mode_valid(struct drm_crtc *crtc, const struct drm_display_mode
						 *mode)
{
	debug("\"%s\", %dx%d\n", mode->name, mode->hdisplay, mode->vdisplay);

	return MODE_OK;
}

static struct drm_connector_helper_funcs lg1k_connector_helper_funcs = {
	.get_modes = lg1k_connector_get_modes,
	.mode_valid = lg1k_connector_mode_valid,
};

static const struct drm_connector_funcs lg1k_connector_funcs = {
	.dpms = drm_helper_connector_dpms,
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.destroy = drm_connector_cleanup,
};
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
static void lg1k_crtc_atomic_flush(struct drm_crtc *crtc,
				   struct drm_atomic_state *state)
#else
static void lg1k_crtc_atomic_flush(struct drm_crtc *crtc,
				   struct drm_crtc_state *old_crtc_state)
#endif
{
	struct drm_pending_vblank_event *event;

	spin_lock_irq(&crtc->dev->event_lock);
	event = crtc->state->event;

	if (event) {
		crtc->state->event = NULL;

		if (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		else
			drm_crtc_send_vblank_event(crtc, event);
	}

	spin_unlock_irq(&crtc->dev->event_lock);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
static void
lg1k_crtc_enable(struct drm_crtc *crtc, struct drm_atomic_state *state)
#else
static void
lg1k_crtc_enable(struct drm_crtc *crtc, struct drm_crtc_state *old_state)
#endif
{
	//struct lg1k_drm_priv *priv = container_of(crtc, struct lg1k_drm_priv, crtc);

	info("..\n");
	//osd_drm_enable(osd_drm_id_graphic0, true);    // 이게 필요하나 ?
	drm_crtc_vblank_on(crtc);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
static void
lg1k_crtc_disable(struct drm_crtc *crtc, struct drm_atomic_state *state)
#else
static void
lg1k_crtc_disable(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state)
#endif
{
	//struct lg1k_drm_priv *priv = container_of(crtc, struct lg1k_drm_priv, crtc);

	info("..\n");
	//osd_drm_enable(osd_drm_id_graphic0, false);
	drm_crtc_vblank_off(crtc);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
static void
lg1k_plane_disable(struct drm_plane *plane, struct drm_atomic_state *old_state)
#else
static void
lg1k_plane_disable(struct drm_plane *plane, struct drm_plane_state *old_state)
#endif
{
	struct lg1k_drm_plane *lg1k_plane = to_lg1k_plane(plane);
	int osdid = lg1k_plane->osdid;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5 ,14, 0))
	if (!old_state->crtc) {
		return;
	}
#endif
	debug("..\n");

	// hide osd
	osd_drm_enable(osdid, false);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
static void
lg1k_plane_update(struct drm_plane *plane, struct drm_atomic_state *old_state)
#else
static void
lg1k_plane_update(struct drm_plane *plane, struct drm_plane_state *old_state)
#endif
{
	struct lg1k_drm_plane *lg1k_plane = to_lg1k_plane(plane);
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = plane->state->fb;
	struct drm_crtc *crtc = state->crtc;

	int osdid = lg1k_plane->osdid;

	phys_addr_t paddr;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
	struct drm_gem_dma_object *cmaobj;
#else
	struct drm_gem_cma_object *cmaobj;
#endif
	osd_drm_pxlfmt pixel_format;
	struct osd_drm_framebuffer osd_fb;

	// drm 호출 앱이 죽을때도 이 함수가 호출될 수 있는데, 다른 칩 구현을 보면
	// 항상 fb NULL 여부를 확인하고 있음. 아래 코드 없으면 kernel panic 발생함.
	if (!fb) {
		info("fb is null, hide or close application\n");
		lg1k_plane_disable(plane, old_state);
		return;
	}

	debug("plane_type=%d, state->fb=%p, crtc->xywh=%dx%d(%dx%d), "
	      "state->src_xy=%dx%d), visible=%d, rot=%d, event=%p\n",
	      plane->type, state->fb,
	      state->crtc_x, state->crtc_y,
	      state->crtc_w, state->crtc_h,
	      state->src_x >> 16, state->src_y >> 16,
	      //state->src_x, state->src_y,
	      state->visible, state->rotation, crtc->state->event);


#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
	cmaobj = drm_fb_dma_get_gem_obj(fb, 0);
	paddr = cmaobj->dma_addr;
#else
	cmaobj = drm_fb_cma_get_gem_obj(fb, 0);
	paddr = cmaobj->paddr;
#endif

	debug("fb %dx%d(%d,%d), paddr %pad, %c%c%c%c(0x%016llx)\n",
	      fb->width, fb->height, fb->pitches[0], fb->offsets[0],
	      &paddr, (fb->format->format >> 0) & 0xff,
	      (fb->format->format >> 8) & 0xff,
	      (fb->format->format >> 16) & 0xff,
	      (fb->format->format >> 24) & 0xff, fb->modifier);

	switch (fb->format->format) {
	default:
		error("unknown pixel format. 0x%08x(%c%c%c%c)\n",
		      fb->format->format,
		      (fb->format->format >> 0) & 0xff,
		      (fb->format->format >> 8) & 0xff,
		      (fb->format->format >> 16) & 0xff,
		      (fb->format->format >> 24) & 0xff);

		pixel_format = osd_drm_pxlfmt_raw_abgr;
		break;

	case DRM_FORMAT_ABGR8888:
		pixel_format = osd_drm_pxlfmt_raw_abgr;
		break;

	case DRM_FORMAT_ARGB8888:
		pixel_format = osd_drm_pxlfmt_raw_argb;
		break;

	case DRM_FORMAT_XBGR8888:
		pixel_format = osd_drm_pxlfmt_raw_xbgr;
		break;

	case DRM_FORMAT_XRGB8888:
		pixel_format = osd_drm_pxlfmt_raw_xrgb;
		break;
	}

	if (fb->modifier != DRM_FORMAT_MOD_LINEAR) {
		if (((fb->modifier >> 52) & 0x0f) ==
		    DRM_FORMAT_MOD_ARM_TYPE_AFRC)
			pixel_format |= osd_drm_pxlfmt_afrc;
		else
			pixel_format |= osd_drm_pxlfmt_afbc;
	}

	memset(&osd_fb, 0x0, sizeof(struct osd_drm_framebuffer));

	osd_fb.fbmem = paddr + fb->offsets[0], osd_fb.stride = fb->pitches[0];
	osd_fb.width = fb->width;
	osd_fb.height = fb->height;
	osd_fb.fmt = pixel_format;

	osd_drm_flip_image(osdid, &osd_fb, state->crtc_x, state->crtc_y);

	// 커서 좌표계는 UI plane 정보와 알치하므로, 해당 정보를 업데이트 하도록 한다.
	if (osdid == osd_drm_id_graphic0) {
		osd_drm_set_cursor_region(state->crtc_w, state->crtc_h);
	}
	//if (state->visible) {
	{
		debug("osd(%d) show", osdid);
		osd_drm_enable(osdid, true);
	}
}

static void vsync_func(void)
{
	struct lg1k_drm_crtc *lg1k_crtc = &g_priv->crtc;
	struct drm_crtc *crtc = &(lg1k_crtc->base);

	debug("vsync..\n");
	drm_crtc_handle_vblank(crtc);
}

static int lg1k_crtc_enable_vblank(struct drm_crtc *crtc)
{
	debug("..\n");
	osd_drm_register_vsync_handler(vsync_func);

	return 0;
}

static void lg1k_crtc_disable_vblank(struct drm_crtc *crtc)
{
	//struct lg1k_drm_priv *priv = container_of(crtc, struct lg1k_drm_priv, crtc);

	debug("..\n");
	osd_drm_register_vsync_handler(NULL);
}

static bool
lg1k_plane_format_mod_supported(struct drm_plane *plane,
				uint32_t format, uint64_t modifier)
{
	if (modifier == DRM_FORMAT_MOD_LINEAR)
		return true;

	if (format == DRM_FORMAT_ABGR8888 || format == DRM_FORMAT_XBGR8888)
		return true;

	// AFBC does not supported with ARGB color order
	return false;
}

// 지정된 위치에 커서 이미지를 출력한다.
static void
lg1k_cursor_update_framebuffer(struct drm_plane *plane, int x, int y)
{
	struct lg1k_drm_plane *lg1k_plane = to_lg1k_plane(plane);
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = plane->state->fb;
	struct drm_crtc *crtc = state->crtc;

	int osdid = lg1k_plane->osdid;

	//struct drm_pending_vblank_event *event;

	debug("cursor, xy=%d,%d, state->fb=%p, crtc->xywh=%dx%d(%dx%d), "
	      "state->src_xy=%dx%d), visible=%d, rot=%d, event=%p\n",
	      x, y,
	      state->fb,
	      state->crtc_x, state->crtc_y,
	      state->crtc_w, state->crtc_h,
	      state->src_x >> 16, state->src_y >> 16,
	      //state->src_x, state->src_y,
	      state->visible, state->rotation, crtc->state->event);

	if (x < 0)
		x = state->crtc_x;

	if (y < 0)
		y = state->crtc_y;

	if (fb) {

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
		struct drm_gem_dma_object *cmaobj;
#else
		struct drm_gem_cma_object *cmaobj;
#endif
		struct osd_drm_framebuffer osd_fb;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
		cmaobj = drm_fb_dma_get_gem_obj(fb, 0);
#else
		cmaobj = drm_fb_cma_get_gem_obj(fb, 0);
#endif
		memset(&osd_fb, 0x0, sizeof(struct osd_drm_framebuffer));

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
		osd_fb.fbmem = cmaobj->dma_addr;
#else
		osd_fb.fbmem = cmaobj->paddr;
#endif
		osd_fb.stride = fb->pitches[0];
		osd_fb.width = fb->width;
		osd_fb.height = fb->height;
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
		osd_fb.hotspot_x = fb->hot_x;
		osd_fb.hotspot_y = fb->hot_y;
#else
		osd_fb.hotspot_x = state->hotspot_x;
		osd_fb.hotspot_y = state->hotspot_y;
#endif
		osd_fb.fmt = osd_drm_pxlfmt_raw_argb;	// fixed

		// FIXME
		// DRM 에서 커서 크기와 무관하게 256x256 framebuffer 크기 정보를 그대로 전달해 주는 경우에 대비
		// 실제 커서 이미지 크기 정보가 전달되지 않는한, 입력 커서 크기는 무조건 128x128 로 제한조치함
#if 1

		if (osd_fb.width > MAX_CURSOR_W) {
			osd_fb.width = MAX_CURSOR_W;
		}

		if (osd_fb.height > MAX_CURSOR_H) {
			osd_fb.height = MAX_CURSOR_H;
		}
#endif
		debug
		    ("cursor: gemfb=0x%llx, fmt=%c%c%c%c, sz=%dx%d(%d) pos=%dx%d, hotspot=%dx%d\n",
		     osd_fb.fbmem, (fb->format->format >> 0) & 0xff,
		     (fb->format->format >> 8) & 0xff,
		     (fb->format->format >> 16) & 0xff,
		     (fb->format->format >> 24) & 0xff, osd_fb.width,
		     osd_fb.height, osd_fb.stride, x, y, osd_fb.hotspot_x,
		     osd_fb.hotspot_y);

		osd_drm_flip_image(osdid, &osd_fb, x, y);
	}
}


#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
static int
lg1k_crtc_cursor_move(struct drm_crtc *crtc, int x, int y)
{
	struct lg1k_drm_plane *lg1k_plane = &g_priv->plane[LG1K_PLANE_CURSOR];
	struct drm_plane *plane = &lg1k_plane->base;

	if (!crtc)
		return 0;

	info("cursor: pos=%3d,%3d\n", x, y);

	lg1k_cursor_update_framebuffer(plane, x, y);

	return 0;
}

// FIXME
// univeral plane 형식으로 커서 등록시에는 아래 핸들러 호출되지 않음
// 추후 cursor plane 등록 방식 확정 필요함
static int
lg1k_crtc_cursor_set2(struct drm_crtc *crtc,
		      struct drm_file *file_priv,
		      uint32_t handle,
		      uint32_t width,
		      uint32_t height, int32_t hot_x, int32_t hot_y)
{
	if (!crtc)
		return 0;

	debug("cursor: handle=%08x, pos=%3d,%3d, hotspt=%2d,%2d\n",
	      handle, width, height, hot_x, hot_y);

	if (!handle) {
		debug("cursor: set off\n");
		osd_drm_enable(osd_drm_id_cursor, false);
	} else {

		//struct lg1k_drm_plane *lg1k_plane = &g_priv->plane[LG1K_PLANE_CURSOR];
		//struct drm_plane *plane = &lg1k_plane->base;
		//struct drm_plane_state *state = plane->state;
		//struct drm_framebuffer *fb = plane->state->fb;

		debug("cursor: set on\n");
#if 0
		// FIXME: 커서 이미지 업데이트가 필요한가 ?
		lg1k_cursor_update_framebuffer(plane, state->crtc_x,
					       state->crtc_y);
#endif
		osd_drm_enable(osd_drm_id_cursor, true);
	}

	return 0;
}
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
static int
lg1k_cursor_atomic_check(struct drm_plane *plane, struct drm_atomic_state *state)
#else
static int
lg1k_cursor_atomic_check(struct drm_plane *plane, struct drm_plane_state *state)
#endif
{
	//struct lg1k_drm_plane *lg1k_plane = to_lg1k_plane(plane);
	//struct drm_crtc *crtc = state->crtc;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
	struct drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	struct drm_framebuffer *fb = new_plane_state->fb;
	struct drm_crtc *crtc = new_plane_state->crtc;
#else
	struct drm_framebuffer *fb = state->fb;
	struct drm_crtc *crtc = state->crtc;
#endif

	if (!crtc || !fb)
		return 0;

	debug("..\n");

	// check if cursor is changed ?

	return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
static void
lg1k_cursor_atomic_disable(struct drm_plane *plane,
			   struct drm_atomic_state *old_state)
#else
static void
lg1k_cursor_atomic_disable(struct drm_plane *plane,
			   struct drm_plane_state *old_state)
#endif
{
	struct lg1k_drm_plane *lg1k_plane = to_lg1k_plane(plane);
	int osdid = lg1k_plane->osdid;

	debug("cursor: set off\n");
	osd_drm_enable(osdid, false);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5 ,14, 0))
static void
lg1k_cursor_atomic_update(struct drm_plane *plane,
			  struct drm_atomic_state *old_state)
#else
static void
lg1k_cursor_atomic_update(struct drm_plane *plane,
			  struct drm_plane_state *old_state)
#endif
{
	struct lg1k_drm_plane *lg1k_plane = to_lg1k_plane(plane);
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = plane->state->fb;
	int osdid = lg1k_plane->osdid;

	if (!fb) {
		info("fb is null, hide or close application\n");
		lg1k_cursor_atomic_disable(plane, old_state);
		return;
	}

	debug("cursor..\n");

	lg1k_cursor_update_framebuffer(plane, state->crtc_x, state->crtc_y);

	//if (state->visible) {
	{
		debug("cursor: set on\n");
		osd_drm_enable(osdid, true);
	}
}

static const struct drm_crtc_funcs lg1k_crtc_funcs = {
	.reset = drm_atomic_helper_crtc_reset,
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = lg1k_crtc_enable_vblank,
	.disable_vblank = lg1k_crtc_disable_vblank,

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
	.cursor_set2 = lg1k_crtc_cursor_set2,
	.cursor_move = lg1k_crtc_cursor_move,
#endif
};

static const struct drm_crtc_helper_funcs lg1k_crtc_helper_funcs = {
	.mode_valid = lg1k_crtc_mode_valid,
	.atomic_flush = lg1k_crtc_atomic_flush,
	.atomic_enable = lg1k_crtc_enable,
	.atomic_disable = lg1k_crtc_disable,
};

static const struct drm_plane_funcs lg1k_plane_funcs = {
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.format_mod_supported = lg1k_plane_format_mod_supported,
};

static const struct drm_plane_helper_funcs lg1k_plane_helper_funcs = {
	.atomic_update = lg1k_plane_update,
	.atomic_disable = lg1k_plane_disable,
};

static const struct drm_plane_funcs lg1k_cursor_funcs = {
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
};

static const struct drm_plane_helper_funcs lg1k_cursor_helper_funcs = {
	.atomic_check = lg1k_cursor_atomic_check,
	.atomic_update = lg1k_cursor_atomic_update,
	.atomic_disable = lg1k_cursor_atomic_disable,
};

static const struct drm_encoder_funcs lg1k_encoder_funcs = {
	.destroy = drm_encoder_cleanup,
};

static unsigned int use_afrc;
module_param(use_afrc, uint, 0644);
MODULE_PARM_DESC(use_afrc,
		 "Add AFRC modifier at list. 0 for disable AFRC. "
		 "Or, CU size(16,24,32) must be specified.");

static bool use_afbc = true;
module_param(use_afbc, bool, 0644);
MODULE_PARM_DESC(use_afbc, "Add AFBC modifier at list");

static int
lg1k_init_plane(struct drm_device *drm,
		struct lg1k_drm_plane *lg1k_plane, int plane_type)
{
	int ret;
	static const uint32_t formats[] = {
		DRM_FORMAT_ARGB8888,
		DRM_FORMAT_XRGB8888,
		DRM_FORMAT_ABGR8888,
		DRM_FORMAT_XBGR8888,
	};
	uint64_t modifiers[4];
	int i;

	struct drm_plane *plane = &lg1k_plane->base;
	unsigned long possible_crtc = 1 << 0;

	i = 0;
#if defined(CHIP_NAME_e60) || defined(CHIP_NAME_o20)
#else
	if (use_afrc == 16)
		modifiers[i++] =
		    DRM_FORMAT_MOD_ARM_AFRC(AFRC_FORMAT_MOD_CU_SIZE_P0
					    (AFRC_FORMAT_MOD_CU_SIZE_16) |
					    AFRC_FORMAT_MOD_LAYOUT_SCAN);
	else if (use_afrc == 24)
		modifiers[i++] =
		    DRM_FORMAT_MOD_ARM_AFRC(AFRC_FORMAT_MOD_CU_SIZE_P0
					    (AFRC_FORMAT_MOD_CU_SIZE_24) |
					    AFRC_FORMAT_MOD_LAYOUT_SCAN);
	else if (use_afrc == 32)
		modifiers[i++] =
		    DRM_FORMAT_MOD_ARM_AFRC(AFRC_FORMAT_MOD_CU_SIZE_P0
					    (AFRC_FORMAT_MOD_CU_SIZE_32) |
					    AFRC_FORMAT_MOD_LAYOUT_SCAN);
	else if (use_afrc != 0)
		warn("unknown CU size for AFRC. ignore. %d\n", use_afrc);
#endif

	if (use_afbc) {
#if defined(CHIP_NAME_e60) || defined(CHIP_NAME_o20)
		modifiers[i++] =
		    DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 |
					    AFBC_FORMAT_MOD_SPARSE);
#else
		modifiers[i++] =
		    DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 |
					    AFBC_FORMAT_MOD_SPLIT |
					    AFBC_FORMAT_MOD_SPARSE);
#endif
	}

	modifiers[i++] = DRM_FORMAT_MOD_LINEAR;
	modifiers[i++] = DRM_FORMAT_MOD_INVALID;

	for (i = 0; modifiers[i] != DRM_FORMAT_MOD_INVALID; i++)
		debug("supported modifiers[%d] : 0x%016llx\n", i, modifiers[i]);

	drm_plane_helper_add(plane, &lg1k_plane_helper_funcs);
	ret = drm_universal_plane_init(drm, plane, possible_crtc,
				       &lg1k_plane_funcs,
				       formats, ARRAY_SIZE(formats),
				       modifiers, plane_type, NULL);

	if (ret) {
		error("plane_init() failed. %d\n", ret);
		return ret;
	}

	if (plane_type == DRM_PLANE_TYPE_PRIMARY) {
		lg1k_plane->osdid = osd_drm_id_graphic0;	// fixed
	} else {
		lg1k_plane->osdid = osd_drm_id_graphic1;	// fixed
	}

	return 0;
}

static int
lg1k_init_cursor(struct drm_device *drm, struct lg1k_drm_plane *lg1k_plane)
{
	int ret;
	static const uint32_t formats[] = {
		DRM_FORMAT_ARGB8888,
	};

	struct drm_plane *plane = &lg1k_plane->base;
	unsigned long possible_crtc = 1 << 0;

	drm_plane_helper_add(plane, &lg1k_cursor_helper_funcs);
	ret = drm_universal_plane_init(drm, plane, possible_crtc,
				       &lg1k_cursor_funcs,
				       formats, ARRAY_SIZE(formats),
				       NULL, DRM_PLANE_TYPE_CURSOR, NULL);

	if (ret) {
		error("plane_init() failed. %d\n", ret);
		return ret;
	}

	lg1k_plane->osdid = osd_drm_id_cursor;	// fixed

	return 0;
}

static int lg1k_modeset_init(struct drm_device *drm)
{
	int ret;

	struct lg1k_drm_priv *priv = drm->dev_private;
	struct drm_mode_config *mode_config = &drm->mode_config;

	struct lg1k_drm_crtc *lg1k_crtc = &priv->crtc;
	struct drm_plane *primary = &priv->plane[LG1K_PLANE_IMG0].base;
	struct drm_plane *cursor;

	info("..\n");

	drm_mode_config_init(drm);
	mode_config->funcs = &mode_config_funcs;
	mode_config->min_width = 1;
	mode_config->min_height = 1;

	if (osd_drm_check_mode(7680, 4320))	// QUHD
	{
		mode_config->max_width = 7680;
		mode_config->max_height = 4320;
	} else if (osd_drm_check_mode(3840, 2160))	// UHD
	{
		mode_config->max_width = 3840;
		mode_config->max_height = 2160;
	} else if (osd_drm_check_mode(1920, 1080))	// FHD
	{
		mode_config->max_width = 1920;
		mode_config->max_height = 1080;
	} else if (osd_drm_check_mode(1366, 768))	// HD
	{
		mode_config->max_width = 1366;
		mode_config->max_height = 768;
	} else {
		error("mode check error\n");
		return -1;
	}

#if 0				// TEST
	mode_config->max_width = 7680;
	mode_config->max_height = 4320;
#endif

	mode_config->cursor_width = MAX_CURSOR_W;
	mode_config->cursor_height = MAX_CURSOR_H;

	priv->connector.force = DRM_FORCE_ON;
	drm_connector_helper_add(&priv->connector,
				 &lg1k_connector_helper_funcs);
	drm_connector_init(drm, &priv->connector, &lg1k_connector_funcs,
			   DRM_MODE_CONNECTOR_TV);
	drm_connector_register(&priv->connector);

	// init plane
	lg1k_init_plane(drm, &priv->plane[LG1K_PLANE_IMG0],
			DRM_PLANE_TYPE_PRIMARY);

	if (use_overlay) {
		lg1k_init_plane(drm, &priv->plane[LG1K_PLANE_IMG1],
				DRM_PLANE_TYPE_OVERLAY);
	}

	if (use_cursor) {
		lg1k_init_cursor(drm, &priv->plane[LG1K_PLANE_CURSOR]);
		cursor = &priv->plane[LG1K_PLANE_CURSOR].base;
	}
	else {
		cursor = NULL;
	}

	// init crtc
	drm_crtc_helper_add(&lg1k_crtc->base, &lg1k_crtc_helper_funcs);
	ret = drm_crtc_init_with_planes(drm, &lg1k_crtc->base, primary, cursor,
					&lg1k_crtc_funcs, NULL);

	if (ret) {
		error("crtc_init() failed. %d\n", ret);
		return ret;
	}

	// init encoder
	priv->encoder.possible_crtcs = drm_crtc_mask(&lg1k_crtc->base);
	ret = drm_encoder_init(drm, &priv->encoder, &lg1k_encoder_funcs,
			       DRM_MODE_ENCODER_NONE, NULL);

	if (ret) {
		error("encoder_init() failed. %d\n", ret);
		return ret;
	}

	// init connecter
	ret = drm_connector_attach_encoder(&priv->connector, &priv->encoder);

	if (ret) {
		error("connector_attach_encoder() failed. %d\n", ret);
		return ret;
	}

	drm_vblank_init(drm, 1);

	return 0;
}

static const struct file_operations drm_fops = {
	.owner = THIS_MODULE,
	.open = drm_open,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.compat_ioctl = drm_compat_ioctl,
	.poll = drm_poll,
	.read = drm_read,
	.llseek = noop_llseek,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
	.mmap = drm_gem_mmap,
	.fop_flags = FOP_UNSIGNED_OFFSET,
#else
	.mmap = drm_gem_cma_mmap,
#endif
};

static struct drm_driver lg1k_drm_driver = {
	.driver_features =
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
	    DRIVER_CURSOR_HOTSPOT |
#endif
	    DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC | DRIVER_RENDER,
	.ioctls = NULL,
	.fops = &drm_fops,
	.name = "lg1k",
	.desc = "LG Graphics Output Driver",
	.date = "20210215",
	.major = 1,
	.minor = 0,
	.patchlevel = 0,

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
	.dumb_create = drm_gem_cma_dumb_create,
	.dumb_map_offset = drm_gem_dumb_map_offset,
	.dumb_destroy = drm_gem_dumb_destroy,
	.gem_free_object_unlocked = drm_gem_cma_free_object,
	.gem_vm_ops = &drm_gem_cma_vm_ops,
	.gem_prime_mmap = drm_gem_cma_prime_mmap,
	.gem_prime_vmap = drm_gem_cma_prime_vmap,
	.gem_prime_export = drm_gem_prime_export,
	.gem_prime_import = drm_gem_prime_import,
	.gem_prime_import_sg_table = drm_gem_cma_prime_import_sg_table,
	.gem_prime_get_sg_table = drm_gem_cma_prime_get_sg_table,
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
#else
	DRM_GEM_DMA_DRIVER_OPS,
#endif
};

static int lg1kdrm_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct lg1k_drm_priv *priv;
	struct drm_device *drm;
	int ret;

	noti("probe..\n");
	g_priv = priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);

	if (!priv)
		return -ENOMEM;

	drm = drm_dev_alloc(&lg1k_drm_driver, dev);

	if (IS_ERR(drm))
		return PTR_ERR(drm);

	//debug("dma ops %p\n", drm->dev->dma_ops);
	//arch_setup_dma_ops(drm->dev, 0, 0, NULL, true);
	chma_set_dma_ops(drm->dev, "surface");

	platform_set_drvdata(pdev, drm);
	priv->pdev = pdev;
	priv->drm = drm;
	drm->dev_private = priv;
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,9,0)
	drm->irq_enabled = true;
#endif
	// initialize osd drm system
	osd_drm_initialize(pdev);

	ret = lg1k_modeset_init(drm);

	if (ret < 0) {
		drm_dev_put(drm);
		return ret;
	}

	drm_mode_config_reset(drm);

	ret = drm_dev_register(drm, 0);

	if (ret < 0) {
		drm_dev_put(drm);
		return ret;
	}

	//drm_fbdev_generic_setup(drm, 0);

	return 0;
}

static int _lg1kdrm_probe(struct platform_device *pdev)
{
	int ret = lg1kdrm_probe(pdev);

	if (ret < 0)
		error("lg1k probe() failed. %d\n", ret);
	else
		noti("lg1k probed.\n");

	return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
static void  lg1kdrm_remove(struct platform_device *pdev)
#else
static int lg1kdrm_remove(struct platform_device *pdev)
#endif
{
	struct drm_device *drm = platform_get_drvdata(pdev);

	noti("remove..\n");
	drm_dev_unregister(drm);
	drm_mode_config_cleanup(drm);

	drm_dev_put(drm);

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
	return 0;
#endif
}

static const struct of_device_id  lgsoc_drm_of_match[] = {
	{
		.compatible = "lge,lgsoc-dp",
	},
	{},
};
MODULE_DEVICE_TABLE(of, lgsoc_drm_of_match);

static struct platform_driver pdriver = {
	.probe = _lg1kdrm_probe,
	.remove = lg1kdrm_remove,
	.driver = {
		   .name = "lg1kdrm",
		   .of_match_table = lgsoc_drm_of_match,
	},
};

static int lg1kdrm_init(void)
{
	extern bool no_fbdev;
	int ret;

	if (no_fbdev) {
		noti("donot use drm driver\n");
		return 0;
	}

	ret = platform_driver_register(&pdriver);
	if (ret) {
		error("driver register failed. %d\n", ret);
		return ret;
	}

	return 0;
}

static void lg1kdrm_exit(void)
{
	noti("unload..\n");
	platform_driver_unregister(&pdriver);

	return;
}

//module_platform_driver(pdriver);
module_init(lg1kdrm_init);
module_exit(lg1kdrm_exit);

MODULE_DESCRIPTION("LGElectronics SoC Graphics Display DRM driver");
MODULE_AUTHOR("LGE SIC");
MODULE_LICENSE("GPL");
