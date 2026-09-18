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
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include "fbdev_drm.h"

bool no_fbdev;
module_param(no_fbdev, bool, 0644);
EXPORT_SYMBOL(no_fbdev);

int osd_drm_flip_image(osd_drm_id id, struct osd_drm_framebuffer* in_fb, unsigned int x, unsigned int y)
{
    return 0;
}

EXPORT_SYMBOL(osd_drm_flip_image);

int osd_drm_enable(osd_drm_id id, bool en)
{
    return 0;
}

EXPORT_SYMBOL(osd_drm_enable);

int osd_drm_set_cursor_region(unsigned int w, unsigned int h)
{
    return 0;
}

EXPORT_SYMBOL(osd_drm_set_cursor_region);

int osd_drm_move_cursor(int x, int y)
{
    return 0;
}

EXPORT_SYMBOL(osd_drm_move_cursor);

void osd_drm_register_vsync_handler(void (*handler)(void))
{

}

EXPORT_SYMBOL(osd_drm_register_vsync_handler);

int osd_drm_initialize(struct platform_device* pdev)
{
    return 0;
}
EXPORT_SYMBOL(osd_drm_initialize);

bool osd_drm_check_mode(int hdisplay, int vdisplay)
{
    return true;
}
EXPORT_SYMBOL(osd_drm_check_mode);


void FBDEV_PreInit(void)
{

}

int FBDEV_Init(void)
{
    return 0;
}

void FBDEV_Cleanup(void)
{

}
