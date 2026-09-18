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
 *  GFX drawing utilites for other module
 *
 *  author  raxis.lim    (raxis.lim@lge.com)
 *
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/memory.h>
#include <asm/uaccess.h>            /* to verify pointers from user space */
#include <asm/cacheflush.h>
#include <linux/dma-mapping.h>

#include "gfx_impl.h"
#include "gfx_drv.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
void gfx_export_lock_device(void);
void gfx_export_unlock_device(void);
int  gfx_export_get_surface_info(int dst_fd, LX_GFX_SURFACE_SETTING_T* surface_info);
int  gfx_export_get_surface_list(int* surf_list, int max_surf, int* num_surf);
int  gfx_export_alloc_surface(phys_addr_t paddr, unsigned int stride, unsigned int w, unsigned int h);
void gfx_export_free_surface(int fd);
int  gfx_export_fill_simple(int fd, LX_RECT_T rect, unsigned int color);
int  gfx_export_blit_simple(int src_fd, LX_RECT_T src_rect, int dst_fd, LX_RECT_T dst_rect);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int gfx_draw_manual_blend(LX_GFX_MANUAL_BLEND_CTRL_PARAM_T* blend_ctrl);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
    Implementation Group
========================================================================================*/
void    gfx_export_lock_device(void)
{
    GFX_LockDevice();
}

void    gfx_export_unlock_device(void)
{
    GFX_UnlockDevice();
}

int     gfx_export_get_surface_info(int dst_fd, LX_GFX_SURFACE_SETTING_T* surface_info)
{
    return GFX_GetSurfaceInfo(dst_fd, surface_info);
}

int     gfx_export_get_surface_list(int* surf_list, int max_surf, int* num_surf)
{
    return GFX_GetSurfaceFdList(surf_list, max_surf, num_surf);
}

int     gfx_export_alloc_surface(phys_addr_t paddr, unsigned int stride, unsigned int w, unsigned int h)
{
    LX_GFX_SURFACE_SETTING_T            surface_settings;
    LX_GFX_SURFACE_SETTING_PARAM_T      surface_param;

    memset(&surface_settings, 0x0, sizeof(LX_GFX_SURFACE_SETTING_T));

    surface_settings.type           = LX_GFX_SURFACE_TYPE_EXTERN_MEM_BUFFER;
    surface_settings.phys_addr      = paddr;
    surface_settings.pixel_format   = LX_GFX_PIXEL_FORMAT_ARGB8888;
    surface_settings.width          = w;
    surface_settings.height         = h;
    surface_settings.alignment      = 4;
    surface_settings.stride         = stride;

    memcpy(&surface_param.surface_setting, &surface_settings, sizeof(LX_GFX_SURFACE_SETTING_T));

    GFX_AllocSurface(&surface_param);

    GFX_NOTI("surface fd=0x%x, addr=0x%llx, stride=%d, size=%dx%d allocated\n",
             surface_param.surface_fd, paddr, stride, w, h);

    return surface_param.surface_fd;
}

void    gfx_export_free_surface(int fd)
{
    int ret;
    ret = GFX_FreeSurface(fd);

    if (ret != RET_OK)
    {
        GFX_ERROR("free surface error. fd=%d\n", fd);
    }

    GFX_NOTI("surface fd=0x%x freed\n", fd);
}

static int gfx_draw_manual_blend(LX_GFX_MANUAL_BLEND_CTRL_PARAM_T* blend_ctrl)
{
    int ret;

    ret = GFX_RunBlendOp(blend_ctrl, g_gfx_cfg.surface_blit_cmd_delay);

    if (ret != RET_OK)
    {
        GFX_ERROR("manual blend op error\n");
        return ret;
    }

    GFX_DEBUG("blend_op begin\n");

    GFX_RunFlushCommand();

    if (GFX_GetGraphicSyncMode() == LX_GFX_GRAPHIC_SYNC_MODE_AUTO)
    {
        unsigned int timeout = GFX_CalcSyncTimeout(blend_ctrl, g_gfx_cfg.sync_wait_timeout);
        ret = GFX_WaitSyncCommand(timeout);

        if (ret != RET_OK)
        {
            GFX_ERROR("wait gfx sync error\n");
            return ret;
        }
    }

    GFX_DEBUG("blend_op completed\n");

    return RET_OK;
}

int     gfx_export_fill_simple(int fd, LX_RECT_T rect, unsigned int color)
{
    int ret;

    LX_GFX_MANUAL_BLEND_CTRL_PARAM_T    blend_ctrl;
    memset(&blend_ctrl, 0x0, sizeof(LX_GFX_MANUAL_BLEND_CTRL_PARAM_T));

    GFX_DEBUG("dst_fd=0x%x dst_rect=%d,%d,%d,%d, color=0x%08x\n",
              fd, rect.x, rect.y, rect.w, rect.h, color);

    blend_ctrl.src0.port_flag = LX_GFX_PORT_FLAG_NONE;
    blend_ctrl.src0.surface_type = LX_GFX_SURFACE_TYPE_COLOR;
    blend_ctrl.src0.surface_color.pixel_format = LX_GFX_PIXEL_FORMAT_INDEX_0;
    blend_ctrl.src0.surface_color.pixel_value  = color;
    blend_ctrl.src0.rect = rect;

    blend_ctrl.dst.port_flag = LX_GFX_PORT_FLAG_NONE;
    blend_ctrl.dst.surface_fd  = fd;
    blend_ctrl.dst.surface_type = LX_GFX_SURFACE_TYPE_EXTERN_MEM_BUFFER;   /* EXTERN_MEM_BUFFER works well */
    blend_ctrl.dst.rect = rect;

    blend_ctrl.op_mode = LX_GFX_OP_MODE_WRITE;
    blend_ctrl.out_sel = LX_GFX_OUT_SEL_CONST_COLOR;
    blend_ctrl.constant_color = 0x0;
    blend_ctrl.rop     = LX_GFX_ROP_NONE;

    ret = gfx_draw_manual_blend(&blend_ctrl);

    return ret;
}

int     gfx_export_blit_simple(int src_fd, LX_RECT_T src_rect, int dst_fd, LX_RECT_T dst_rect)
{
    int ret;
    LX_GFX_PORT_T   src0_port;
    LX_GFX_PORT_T   dst_port;

    LX_GFX_MANUAL_BLEND_CTRL_PARAM_T    blend_ctrl;
    memset(&blend_ctrl, 0x0, sizeof(LX_GFX_MANUAL_BLEND_CTRL_PARAM_T));

    memset(&src0_port, 0x0, sizeof(LX_GFX_PORT_T));
    memset(&dst_port,  0x0, sizeof(LX_GFX_PORT_T));

    GFX_DEBUG("src_fd=0x%x, src_rect=%d,%d,%d,%d, dst_fd=0x%x, dst_rect=%d,%d,%d,%d\n",
              src_fd,  src_rect.x,  src_rect.y,  src_rect.w,  src_rect.h,
              dst_fd,  dst_rect.x,  dst_rect.y,  dst_rect.w,  dst_rect.h);

    src0_port.port_flag     = LX_GFX_PORT_FLAG_NONE;
    src0_port.surface_type  = LX_GFX_SURFACE_TYPE_EXTERN_MEM_BUFFER;
    src0_port.surface_fd    = src_fd;
    src0_port.rect = src_rect;

    dst_port.port_flag      = LX_GFX_PORT_FLAG_NONE;
    dst_port.surface_type   = LX_GFX_SURFACE_TYPE_EXTERN_MEM_BUFFER;
    dst_port.surface_fd     = dst_fd;
    dst_port.rect = dst_rect;

    blend_ctrl.scaler.mode      = LX_GFX_SCALER_MODE_BILINEAR;
    blend_ctrl.scaler.input.w   = src_rect.w;
    blend_ctrl.scaler.input.h   = src_rect.h;
    blend_ctrl.scaler.output.w  = dst_rect.w;
    blend_ctrl.scaler.output.h  = dst_rect.h;

    blend_ctrl.op_mode          = LX_GFX_OP_MODE_ONE_SRC_PORT;
    blend_ctrl.out_sel          = LX_GFX_OUT_SEL_SRC0_PORT;
    blend_ctrl.rop              = LX_GFX_ROP_NONE;
    blend_ctrl.constant_color   = 0x0;

    memcpy(&blend_ctrl.src0, &src0_port, sizeof(LX_GFX_PORT_T));
    memcpy(&blend_ctrl.dst,  &dst_port, sizeof(LX_GFX_PORT_T));

    ret = gfx_draw_manual_blend(&blend_ctrl);

    return ret;
}

