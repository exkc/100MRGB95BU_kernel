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

#include <drm/drm_atomic_helper.h>
#include <drm/drmP.h>
#include <drm/drm_fb_cma_helper.h>
#include <drm/drm_fb_helper.h>
#include <drm/drm_gem_cma_helper.h>
#include <drm/drm_plane_helper.h>
#include <drm/drm_crtc_helper.h>
#include <drm/drm_panel.h>
//#include <drm/drm_probe_helper.h>

#include "fbdev_drm.h"
#include "hma_alloc.h"
#include "chma.h"
#include "logm.h"

logm_define(drm, log_level_info);

#define trace(fmt,args...)	logm_trace(drm,fmt,##args)
#define debug(fmt,args...)	logm_debug(drm,fmt,##args)
#define info(fmt,args...)	logm_info(drm,fmt,##args)
#define noti(fmt,args...)	logm_noti(drm,fmt,##args)
#define error(fmt,args...)	logm_error(drm,fmt,##args)

struct lg1k_drm_priv {
	struct drm_device *drm;
	struct drm_connector connector;

	//struct drm_simple_display_pipe pipe;
	struct drm_plane plane[3];
	struct drm_crtc crtc;
	struct drm_encoder encoder;

	struct drm_framebuffer fb;
	phys_addr_t fb_paddr;
	struct drm_fb_helper fb_helper;

	bool vsync_enabled;
	bool graphic_enabled;
	bool cursor_enabled;
};

struct lg1k_drm_priv *g_priv;

static struct drm_gem_object *lg1k_gem_import_sg_table(struct drm_device *drm, struct dma_buf_attachment
						       *attach,
						       struct sg_table *sgt)
{
	//struct lg1k_drm_priv *priv = drm->dev_private;

	//if (priv->use_device_memory)
	//      return ERR_PTR(-EINVAL);
	info("..\n");

	return drm_gem_cma_prime_import_sg_table(drm, attach, sgt);
}

static struct drm_framebuffer *lg1k_fb_create(struct drm_device *drm,
					      struct drm_file *file_priv,
					      struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_framebuffer *ret;

	ret = drm_fb_cma_create(drm, file_priv, mode_cmd);
	info("created fb %p\n", ret);
	if (ret) {
		//ret->funcs = &lg1k_fb_funcs;
	}

	return ret;
}

static int lg1k_atomic_helper_commit(struct drm_device *drm,
				     struct drm_atomic_state *state, bool async)
{
	return drm_atomic_helper_commit(drm, state, async);
}

static const struct drm_mode_config_funcs mode_config_funcs = {
	.fb_create = lg1k_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = lg1k_atomic_helper_commit,	//drm_atomic_helper_commit,
};

static const struct drm_plane_funcs lg1k_plane_funcs = {
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	//.format_mod_supported   = drm_simple_kms_format_mod_supported,
};

struct vsync_event {
	struct list_head list;
	struct drm_pending_vblank_event *event;
	struct lg1k_drm_priv *priv;
};

static spinlock_t vsync_event_lock;
static LIST_HEAD(vsync_event_pending);

static void vsync_func(void)
{
	struct vsync_event *e;

	drm_crtc_handle_vblank(&g_priv->crtc);

	spin_lock(&vsync_event_lock);
	while ((e =
		list_first_entry_or_null(&vsync_event_pending,
					 struct vsync_event, list)) != NULL) {
		unsigned long irqflags;
		struct lg1k_drm_priv *priv;
		struct drm_crtc *crtc;

		spin_unlock(&vsync_event_lock);

		priv = e->priv;
		crtc = &priv->crtc;

		debug("report vsync event. %p\n", e->event);
		spin_lock_irqsave(&priv->drm->event_lock, irqflags);
		drm_crtc_send_vblank_event(crtc, e->event);
		spin_unlock_irqrestore(&priv->drm->event_lock, irqflags);

		list_del(&e->list);
		kfree(e);

		spin_lock(&vsync_event_lock);
	}
	spin_unlock(&vsync_event_lock);
}

static int lg1k_crtc_set_config(struct drm_mode_set *set)
{
	struct lg1k_drm_priv *priv =
	    container_of(set->crtc, struct lg1k_drm_priv, crtc);
	int ret;
	struct drm_display_mode *mode = set->mode;
	struct drm_framebuffer *fb = set->fb;

	if (fb) {
		struct drm_gem_cma_object *cmaobj;

		cmaobj = drm_fb_cma_get_gem_obj(fb, 0);

		info("fb %dx%d(%d,%d), depth %d, bpp %d\n", fb->width,
		     fb->height, fb->pitches[0], fb->offsets[0], fb->depth,
		     fb->bits_per_pixel);
		info("fb paddr %pad\n", &cmaobj->paddr);

		if (mode) {
			info("set mode. %s. %dx%d, %dHz\n", mode->name,
			     mode->hdisplay, mode->vdisplay, mode->vrefresh);

			osd_drm_flip_image(osd_drm_id_graphic,
					   cmaobj->paddr + fb->offsets[0],
					   osd_drm_pxlfmt_xrgb, fb->pitches[0],
					   fb->width, fb->height);
			osd_drm_enable(osd_drm_id_graphic, true);
			priv->graphic_enabled = true;
		} else
			info("no mode\n");

	} else {
		struct vsync_event *e;

		info("no fb. clear vsync event..\n");

		spin_lock(&vsync_event_lock);
		while ((e =
			list_first_entry_or_null(&vsync_event_pending,
						 struct vsync_event,
						 list)) != NULL) {
			list_del(&e->list);
			kfree(e->event);
			kfree(e);
		}
		spin_unlock(&vsync_event_lock);

		if (priv->vsync_enabled) {
			priv->vsync_enabled = false;
			info("disable vblank..\n");
			drm_crtc_vblank_put(&priv->crtc);
		}
		osd_drm_enable(osd_drm_id_graphic, false);
		priv->graphic_enabled = false;
		if (priv->cursor_enabled) {
			info("disable cursor..\n");
			osd_drm_enable(osd_drm_id_cursor, false);
			priv->cursor_enabled = false;
		}
	}

	ret = 0;		//drm_atomic_helper_set_config (set);

	return ret;
}

static int lg1k_crtc_page_flip(struct drm_crtc *crtc,
			       struct drm_framebuffer *fb,
			       struct drm_pending_vblank_event *event,
			       uint32_t flags)
{
	struct lg1k_drm_priv *priv =
	    container_of(crtc, struct lg1k_drm_priv, crtc);

	if (fb) {
		struct drm_gem_cma_object *cmaobj;

		cmaobj = drm_fb_cma_get_gem_obj(fb, 0);

		debug("fb %dx%d(%d,%d), depth %d, bpp %d, paddr %pad\n",
		      fb->width, fb->height, fb->pitches[0], fb->offsets[0],
		      fb->depth, fb->bits_per_pixel, &cmaobj->paddr);

		osd_drm_flip_image(osd_drm_id_graphic,
				   cmaobj->paddr + fb->offsets[0],
				   osd_drm_pxlfmt_xrgb, fb->pitches[0],
				   fb->width, fb->height);

		if (!priv->graphic_enabled) {
			osd_drm_enable(osd_drm_id_graphic, true);
			priv->graphic_enabled = true;
		}
	} else
		debug("no fb\n");

	if (event) {
		struct vsync_event *e;

		e = kzalloc(sizeof(*e), GFP_KERNEL);
		e->event = event;
		e->priv = priv;

		if (!priv->vsync_enabled) {
			priv->vsync_enabled = true;
			info("enable vblank..\n");
			drm_crtc_vblank_get(&priv->crtc);
		}

		debug("pending vsync event. %p\n", event);
		spin_lock(&vsync_event_lock);
		list_add_tail(&e->list, &vsync_event_pending);
		spin_unlock(&vsync_event_lock);
	}

	if (flags & DRM_MODE_PAGE_FLIP_ASYNC) {
	} else {
	}

	return 0;
}

static void lg1k_crtc_gamma_set(struct drm_crtc *crtc, u16 * r, u16 * g,
				u16 * b, uint32_t start, uint32_t size)
{
	debug("..\n");
}

static const struct drm_crtc_funcs lg1k_crtc_funcs = {
	.reset = drm_atomic_helper_crtc_reset,
	.destroy = drm_crtc_cleanup,
	.set_config = lg1k_crtc_set_config,	//drm_atomic_helper_set_config,
	.page_flip = lg1k_crtc_page_flip,	//drm_atomic_helper_page_flip,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	//.enable_vblank = drm_simple_kms_crtc_enable_vblank,
	//.disable_vblank = drm_simple_kms_crtc_disable_vblank,
	.gamma_set = lg1k_crtc_gamma_set,
};

static const struct drm_encoder_funcs lg1k_encoder_funcs = {
	.destroy = drm_encoder_cleanup,
};

static bool lg1k_encoder_mode_fixup(struct drm_encoder *encoder,
				    const struct drm_display_mode *mode,
				    struct drm_display_mode *adjusted_mode)
{
	debug("..\n");
	return true;
}

static void lg1k_encoder_mode_set(struct drm_encoder *encoder,
				  struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode)
{
	debug("..\n");
}

static void lg1k_encoder_dpms(struct drm_encoder *encoder, int state)
{
	debug("..\n");
}

static void lg1k_encoder_prepare(struct drm_encoder *encoder)
{
	debug("..\n");
}

static void lg1k_encoder_commit(struct drm_encoder *encoder)
{
	debug("..\n");
}

static const struct drm_encoder_helper_funcs lg1k_encoder_helper_funcs = {
	.dpms = lg1k_encoder_dpms,
	.mode_fixup = lg1k_encoder_mode_fixup,
	.mode_set = lg1k_encoder_mode_set,
	.prepare = lg1k_encoder_prepare,
	.commit = lg1k_encoder_commit,
};

static int lg1k_connector_get_modes(struct drm_connector *connector)
{
	int count;

	count = drm_add_modes_noedid(connector, 8192, 8192);
	drm_set_preferred_mode(connector, 1920, 1080);
	debug("count %d\n", count);

	return count;
}

static int lg1k_connector_mode_valid(struct drm_connector *connector,
				     struct drm_display_mode *mode)
{
	//debug("%dx%d\n", mode->hdisplay, mode->vdisplay);

	return MODE_OK;
}

static struct drm_encoder *lg1k_connector_best_encoder(struct drm_connector
						       *connector)
{
	struct lg1k_drm_priv *priv =
	    container_of(connector, struct lg1k_drm_priv, connector);

	debug("enc_id %d\n", connector->encoder_ids[0]);
	debug("enc %p\n", connector->encoder);
	return &priv->encoder;
}

static struct drm_connector_helper_funcs lg1k_connector_helper_funcs = {
	.get_modes = lg1k_connector_get_modes,
	.mode_valid = lg1k_connector_mode_valid,
	.best_encoder = lg1k_connector_best_encoder,
};

static const struct drm_connector_funcs lg1k_connector_funcs = {
	.dpms = drm_atomic_helper_connector_dpms,
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.destroy = drm_connector_cleanup,
};

static int lg1k_plane_prepare_fb(struct drm_plane *plane,
				 const struct drm_plane_state *state)
{
	//struct drm_device *drm = plane->dev;
	//struct lg1k_drm_priv *priv = drm->dev_private;

	debug("..\n");
	return 0;
}

static void lg1k_plane_cleanup_fb(struct drm_plane *plane,
				  const struct drm_plane_state *state)
{
	struct lg1k_drm_priv *priv =
	    container_of(state->crtc, struct lg1k_drm_priv, crtc);
	struct drm_framebuffer *fb = state->fb;

	debug
	    ("plane type %d, fb %p, old_fb %p, st->fb %p, crtc %dx%d(%dx%d), src %dx%d(%08xx%08x), rot %d\n",
	     plane->type, plane->fb, plane->old_fb, state->fb, state->crtc_x,
	     state->crtc_y, state->crtc_w, state->crtc_h, state->src_x >> 16,
	     state->src_y >> 16, state->src_x, state->src_y, state->rotation);

	if (fb) {
		phys_addr_t paddr;

		if (fb == &priv->fb)
			paddr = priv->fb_paddr;
		else {
			struct drm_gem_cma_object *cmaobj;

			cmaobj = drm_fb_cma_get_gem_obj(fb, 0);

			paddr = cmaobj->paddr;
		}

		debug("fb %dx%d(%d,%d), depth %d, bpp %d, paddr %pad\n",
		      fb->width, fb->height, fb->pitches[0], fb->offsets[0],
		      fb->depth, fb->bits_per_pixel, &paddr);
	}
}

static int lg1k_plane_atomic_check(struct drm_plane *plane,
				   struct drm_plane_state *plane_state)
{
	debug("..\n");
	return 0;
}

static void lg1k_plane_atomic_update(struct drm_plane *plane,
				     struct drm_plane_state *old_pstate)
{
	struct lg1k_drm_priv *priv =
	    container_of(old_pstate->crtc, struct lg1k_drm_priv, crtc);
	struct drm_framebuffer *fb = old_pstate->fb;
	osd_drm_id osd_type;

	debug
	    ("plane type %d, fb %p, old_fb %p, st->fb %p, crtc %dx%d(%dx%d), src %dx%d(%08xx%08x), rot %d\n",
	     plane->type, plane->fb, plane->old_fb, old_pstate->fb,
	     old_pstate->crtc_x, old_pstate->crtc_y, old_pstate->crtc_w,
	     old_pstate->crtc_h, old_pstate->src_x >> 16,
	     old_pstate->src_y >> 16, old_pstate->src_x, old_pstate->src_y,
	     old_pstate->rotation);

	if (plane->type == DRM_PLANE_TYPE_CURSOR)
		osd_type = osd_drm_id_cursor;
	else
		osd_type = osd_drm_id_graphic;

	if (fb) {
		phys_addr_t paddr;

		if (fb == &priv->fb)
			paddr = priv->fb_paddr;
		else {
			struct drm_gem_cma_object *cmaobj;

			cmaobj = drm_fb_cma_get_gem_obj(fb, 0);

			paddr = cmaobj->paddr;
		}

		debug("priv %p, priv->fb %p\n", priv, &priv->fb);
		debug("fb %dx%d(%d,%d), depth %d, bpp %d, paddr %pad\n",
		      fb->width, fb->height, fb->pitches[0], fb->offsets[0],
		      fb->depth, fb->bits_per_pixel, &paddr);

		osd_drm_flip_image(osd_type, paddr + fb->offsets[0],
				   osd_drm_pxlfmt_xrgb, fb->pitches[0],
				   fb->width, fb->height);

		if (osd_type == osd_drm_id_cursor) {
			osd_drm_move_cursor(old_pstate->crtc_x,
					    old_pstate->crtc_y);
			osd_drm_set_cursor_region(old_pstate->crtc_w,
						  old_pstate->crtc_h);

			if (!priv->cursor_enabled) {
				info("enable cursor..\n");
				priv->cursor_enabled = true;
				osd_drm_enable(osd_drm_id_cursor, true);
			}
		}
	} else {
		debug("plane%d, no fb..\n", plane->type);
	}
}

static const struct drm_plane_helper_funcs lg1k_plane_helper_funcs = {
	.prepare_fb = lg1k_plane_prepare_fb,
	.cleanup_fb = lg1k_plane_cleanup_fb,
	.atomic_check = lg1k_plane_atomic_check,
	.atomic_update = lg1k_plane_atomic_update,
};

static int lg1k_crtc_check(struct drm_crtc *crtc, struct drm_crtc_state *state)
{
	//struct drm_device *drm = crtc->dev;
	//struct lg1k_drm_priv *priv = drm->dev_private;

	info("..\n");
	return 0;
}

static void lg1k_crtc_enable(struct drm_crtc *crtc)
{
	//struct drm_device *drm = crtc->dev;
	//struct lg1k_drm_priv *priv = drm->dev_private;

	info("..\n");
}

static void lg1k_crtc_disable(struct drm_crtc *crtc)
{
	//struct drm_device *drm = crtc->dev;
	//struct lg1k_drm_priv *priv = drm->dev_private;

	info("..\n");
}

static int lg1k_crtc_mode_set(struct drm_crtc *crtc,
			      struct drm_display_mode *mode,
			      struct drm_display_mode *adjusted_mode, int x,
			      int y, struct drm_framebuffer *old_fb)
{
	debug("set mode. %s. %dx%d, %dHz\n", adjusted_mode->name,
	      adjusted_mode->hdisplay, adjusted_mode->vdisplay,
	      adjusted_mode->vrefresh);
	debug("old_fb %p\n", old_fb);
	if (old_fb) {
		debug("old_fb %dx%d, depth %d, bpp %d\n", old_fb->width,
		      old_fb->height, old_fb->depth, old_fb->bits_per_pixel);
	}
	return 0;
}

static const struct drm_crtc_helper_funcs lg1k_crtc_helper_funcs = {
	.atomic_check = lg1k_crtc_check,
	.enable = lg1k_crtc_enable,
	.disable = lg1k_crtc_disable,
	.mode_set = lg1k_crtc_mode_set,
};

static int lg1k_modeset_init(struct drm_device *drm)
{
	struct lg1k_drm_priv *priv = drm->dev_private;
	struct drm_mode_config *mode_config = &drm->mode_config;
	static const uint32_t formats[] = {
		DRM_FORMAT_ABGR8888,
		DRM_FORMAT_XBGR8888,
		DRM_FORMAT_ARGB8888,
		DRM_FORMAT_XRGB8888,
	};

	info("..\n");

	drm_mode_config_init(drm);
	mode_config->funcs = &mode_config_funcs;
	mode_config->min_width = 1;
	mode_config->max_width = 3840;
	mode_config->min_height = 1;
	mode_config->max_height = 2160;

	drm_universal_plane_init(drm, &priv->plane[0], 0, &lg1k_plane_funcs,
				 formats, ARRAY_SIZE(formats),
				 DRM_PLANE_TYPE_PRIMARY);
#if 0
	drm_universal_plane_init(drm, &priv->plane[1], 0, &lg1k_plane_funcs,
				 formats, ARRAY_SIZE(formats),
				 DRM_PLANE_TYPE_CURSOR);
#endif
	drm_plane_helper_add(&priv->plane[0], &lg1k_plane_helper_funcs);
	//drm_plane_helper_add(&priv->plane[1], &lg1k_plane_helper_funcs);

	debug("crtc %p, %p, %p\n", &priv->crtc, &lg1k_crtc_funcs,
	      &lg1k_crtc_gamma_set);
	drm_crtc_init_with_planes(drm, &priv->crtc, &priv->plane[0],
				  NULL /* &priv->plane[1] */ ,
				  &lg1k_crtc_funcs);
	drm_crtc_helper_add(&priv->crtc, &lg1k_crtc_helper_funcs);

	priv->encoder.possible_crtcs = 0x1;
	drm_encoder_init(drm, &priv->encoder, &lg1k_encoder_funcs,
			 DRM_MODE_ENCODER_NONE);
	drm_encoder_helper_add(&priv->encoder, &lg1k_encoder_helper_funcs);

	priv->connector.force = DRM_FORCE_ON;
	drm_connector_helper_add(&priv->connector,
				 &lg1k_connector_helper_funcs);
	drm_connector_init(drm, &priv->connector, &lg1k_connector_funcs,
			   DRM_MODE_CONNECTOR_Unknown);
	drm_connector_register(&priv->connector);

	drm_mode_connector_attach_encoder(&priv->connector, &priv->encoder);
	priv->connector.encoder = &priv->encoder;

	drm_vblank_init(drm, 1);
	drm_mode_config_reset(drm);

	return 0;
}

static int lg1k_gem_dumb_create(struct drm_file *file_priv,
				struct drm_device *drm,
				struct drm_mode_create_dumb *args)
{
	int ret;

	debug("%dx%d, %dbpp, 0x%08x\n", args->width, args->height, args->bpp,
	      args->flags);
	debug("dma ops %p\n", drm->dev->archdata.dma_ops);
	ret = drm_gem_cma_dumb_create(file_priv, drm, args);
	debug("ret %d, handle 0x%08x, pitch 0x%08x, size 0x%016llx\n", ret,
	      args->handle, args->pitch, args->size);

	return ret;
}

static int lg1k_gem_dumb_map_offset(struct drm_file *file_priv,
				    struct drm_device *drm, u32 handle,
				    u64 * offset)
{
	int ret;

	debug("map. 0x%08x\n", handle);
	ret = drm_gem_cma_dumb_map_offset(file_priv, drm, handle, offset);
	debug("ret %d\n", ret);
	return ret;
}

static int lg1k_gem_dumb_destroy(struct drm_file *file_priv,
				 struct drm_device *dev, uint32_t handle)
{
	debug("destroy 0x%08x\n", handle);
	drm_gem_dumb_destroy(file_priv, dev, handle);

	return 0;
}

static int lg1k_enable_vblank(struct drm_device *dev, unsigned int pipe)
{
	debug("..\n");
	osd_drm_register_vsync_handler(vsync_func);

	return 0;
}

static void lg1k_disable_vblank(struct drm_device *dev, unsigned int pipe)
{
	debug("..\n");
	osd_drm_register_vsync_handler(NULL);
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
	.mmap = drm_gem_cma_mmap,
};

static struct drm_driver lg1k_drm_driver = {
	.driver_features =
	    DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC | DRIVER_PRIME,
	.ioctls = NULL,
	.fops = &drm_fops,
	.name = "lg1k",
	.desc = "LG Graphics Output Driver",
	.date = "20210215",
	.major = 1,
	.minor = 0,
	.patchlevel = 0,
	.set_busid = drm_platform_set_busid,
	.dumb_create = lg1k_gem_dumb_create,
	.dumb_map_offset = lg1k_gem_dumb_map_offset,
	.dumb_destroy = lg1k_gem_dumb_destroy,
	.gem_free_object = drm_gem_cma_free_object,
	.gem_vm_ops = &drm_gem_cma_vm_ops,
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_export = drm_gem_prime_export,
	.gem_prime_import = drm_gem_prime_import,
	.gem_prime_import_sg_table = lg1k_gem_import_sg_table,
	.gem_prime_get_sg_table = drm_gem_cma_prime_get_sg_table,
	.gem_prime_mmap = drm_gem_cma_prime_mmap,
	.gem_prime_vmap = drm_gem_cma_prime_vmap,
	.enable_vblank = lg1k_enable_vblank,
	.disable_vblank = lg1k_disable_vblank,
	.get_vblank_counter = drm_vblank_count,

	//.debugfs_init = pl111_debugfs_init,
};

static void drm_dev_put(struct drm_device *dev)
{
	info("..\n");
	drm_dev_unref(dev);
}

static void lg1k_fb_destroy(struct drm_framebuffer *fb)
{
	debug("..\n");
}

static int lg1k_fb_create_handle(struct drm_framebuffer *fb,
				 struct drm_file *dfile, unsigned int *handle)
{
	debug("..\n");
	return 0;
}

static int lg1k_fb_dirty(struct drm_framebuffer *framebuffer,
			 struct drm_file *file_priv, unsigned flags,
			 unsigned color, struct drm_clip_rect *clips,
			 unsigned num_clips)
{
	debug("..\n");
	return 0;
}

static const struct drm_framebuffer_funcs lg1k_fb_funcs = {
	.destroy = lg1k_fb_destroy,
	.create_handle = lg1k_fb_create_handle,
	.dirty = lg1k_fb_dirty,
};

static /*const */ struct fb_ops lg1k_fb_ops = {
	.owner = THIS_MODULE,
	.fb_check_var = drm_fb_helper_check_var,
	.fb_set_par = drm_fb_helper_set_par,
	.fb_fillrect = drm_fb_helper_cfb_fillrect,
	.fb_copyarea = drm_fb_helper_cfb_copyarea,
	.fb_imageblit = drm_fb_helper_cfb_imageblit,
	.fb_pan_display = drm_fb_helper_pan_display,
	.fb_blank = drm_fb_helper_blank,
	.fb_setcmap = drm_fb_helper_setcmap,
	.fb_debug_enter = drm_fb_helper_debug_enter,
	.fb_debug_leave = drm_fb_helper_debug_leave,
};

// drm_fb_helper_generic_probe()
static int lg1kfbdev_probe(struct drm_fb_helper *helper,
			   struct drm_fb_helper_surface_size *sizes)
{
	struct lg1k_drm_priv *priv =
	    container_of(helper, struct lg1k_drm_priv, fb_helper);
	struct drm_device *drm = priv->drm;
	struct fb_info *fbi;
	struct drm_mode_fb_cmd2 mode;

	info("%dx%d, sufrace %dx%d(%dbpp, depth %d)\n",
	     sizes->fb_width, sizes->fb_height,
	     sizes->surface_width, sizes->surface_height,
	     sizes->surface_bpp, sizes->surface_depth);

	fbi = drm_fb_helper_alloc_fbi(helper);

	strlcpy(fbi->fix.id, "lg1k-drmfb", sizeof(fbi->fix.id));
	fbi->par = helper;
	fbi->flags = FBINFO_DEFAULT | FBINFO_CAN_FORCE_OUTPUT;
	fbi->fbops = &lg1k_fb_ops;

	{
		phys_addr_t fbaddr;
		void *fbvaddr;
		int fbsize;

		fbsize =
		    sizes->surface_height * sizes->surface_width *
		    sizes->surface_bpp / 8;

		priv->fb_paddr = fbaddr =
		    hma_alloc_user("surface", fbsize, PAGE_SIZE, "fbdev");
		fbvaddr = hma_map(fbaddr, fbsize);
		if (!fbaddr || !fbvaddr)
			error("no fbdev mem for %dx%d(%dbpp)\n",
			      sizes->surface_width, sizes->surface_height,
			      sizes->surface_bpp);
		else {
			fbi->fix.smem_start = fbaddr;
			fbi->fix.smem_len = fbsize;
			fbi->screen_size = fbsize;
			fbi->screen_base = fbvaddr;
		}
	}

	memset(&mode, 0, sizeof(mode));
	mode.width = sizes->surface_width;
	mode.height = sizes->surface_height;
	mode.pitches[0] = mode.width * sizes->surface_bpp / 8;
	mode.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
						      sizes->surface_depth);

	drm_helper_mode_fill_fb_struct(&priv->fb, &mode);
	debug("fb %p\n", &priv->fb);
	drm_framebuffer_init(drm, &priv->fb, &lg1k_fb_funcs);
	helper->fb = &priv->fb;

	drm_fb_helper_fill_fix(fbi, sizes->fb_width * sizes->surface_bpp / 8,
			       sizes->surface_depth);
	drm_fb_helper_fill_var(fbi, helper, sizes->fb_width, sizes->fb_height);

	return 0;
}

static bool lg1kfbdev_initial_config(struct drm_fb_helper *fb_helper,
				     struct drm_fb_helper_crtc **crtcs,
				     struct drm_display_mode **modes,
				     struct drm_fb_offset *offsets,
				     bool * enabled, int width, int height)
{
	debug("max %dx%d\n", width, height);

	crtcs[0] = &fb_helper->crtc_info[0];
	modes[0] =
	    drm_has_preferred_mode(fb_helper->connector_info[0], INT_MAX,
				   INT_MAX);

	return true;
}

static const struct drm_fb_helper_funcs fb_helper_funcs = {
	.fb_probe = lg1kfbdev_probe,
	.initial_config = lg1kfbdev_initial_config,
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

	debug("dma ops %p\n", drm->dev->archdata.dma_ops);
	//arch_setup_dma_ops(drm->dev, 0, 0, NULL, true);
	chma_set_dma_ops(drm->dev, "surface");

	platform_set_drvdata(pdev, drm);
	priv->drm = drm;
	drm->dev_private = priv;
	drm->platformdev = pdev;
	drm->irq_enabled = true;

	ret = drm_dev_register(drm, 0);
	if (ret < 0) {
		drm_dev_put(drm);
		return ret;
	}

	ret = lg1k_modeset_init(drm);
	if (ret < 0) {
		drm_dev_put(drm);
		return ret;
	}
	drm_fb_helper_prepare(drm, &priv->fb_helper, &fb_helper_funcs);
	drm_fb_helper_init(drm, &priv->fb_helper, 1, 1);
	drm_fb_helper_single_add_all_connectors(&priv->fb_helper);
	drm_fb_helper_initial_config(&priv->fb_helper, 32);

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

static int lg1kdrm_remove(struct platform_device *pdev)
{
	struct drm_device *drm = platform_get_drvdata(pdev);
	struct lg1k_drm_priv *priv = drm->dev_private;

	noti("remove..\n");
	drm_dev_unregister(drm);
	drm_mode_config_cleanup(drm);

	drm_dev_put(drm);

	return 0;
}

static struct platform_driver pdriver = {
	.probe = _lg1kdrm_probe,
	.remove = lg1kdrm_remove,
	.driver = {
		   .name = "lg1k",
		   },
};

static struct platform_device pdevice = {
	.name = "lg1k",
	.id = PLATFORM_DEVID_NONE,
};

static int lg1kdrm_init(void)
{
	extern bool no_fbdev;
	int ret;

	if (no_fbdev) {
		noti("donot use drm driver\n");
		return 0;
	}

	ret = platform_device_register(&pdevice);
	if (ret) {
		error("device register failed. %d\n", ret);
		return ret;
	}

	ret = platform_driver_register(&pdriver);
	if (ret) {
		error("driver register failed. %d\n", ret);
		platform_device_unregister(&pdevice);
		return ret;
	}

	return 0;
}

static void lg1kdrm_exit(void)
{
	noti("unload..\n");
	platform_driver_unregister(&pdriver);
	platform_device_unregister(&pdevice);

	return;
}

module_init(lg1kdrm_init);
module_exit(lg1kdrm_exit);

MODULE_DESCRIPTION("LGElectronics SoC Graphics Display DRM driver");
MODULE_AUTHOR("LGE SIC");
MODULE_LICENSE("GPL");
