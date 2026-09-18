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
 *  driver interface header for gfx device. ( used only within kdriver )
 *  this file lists exported function, types for the external modules.
 *
 *  @author     raxis.lim (raxis.lim@lge.com).lim (raxis.lim@lge.com)
 *  @version    1.0
 *  @date       2009.12.30
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */
#ifndef _GFX_EXPORT_H_
#define _GFX_EXPORT_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "gfx_kapi.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration ( GFX Basic Renderer )
----------------------------------------------------------------------------------------*/
void    gfx_export_lock_device(void);
void    gfx_export_unlock_device(void);

int     gfx_export_get_surface_info(int dst_fd, LX_GFX_SURFACE_SETTING_T* surface_info);
int     gfx_export_get_surface_list(int* surf_list, int max_surf, int* num_surf);

int     gfx_export_alloc_surface(phys_addr_t paddr, unsigned int stride, unsigned int w, unsigned int h);
void    gfx_export_free_surface(int fd);

int     gfx_export_fill_simple(int fd, LX_RECT_T rect, unsigned int color);
int     gfx_export_blit_simple(int src_fd, LX_RECT_T src_rect, int dst_fd, LX_RECT_T dst_rect);

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _GFX_DRV_H_ */

/** @} */
