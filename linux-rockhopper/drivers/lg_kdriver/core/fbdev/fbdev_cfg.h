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
 *  main configuration file for fbdev device
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

#ifndef _FBDEV_CFG_H_
#define _FBDEV_CFG_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif              /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define FBDEV_MODULE                "fbdev"
#define FBDEV_MAX_DEVICE            4

/* Common Configuration
 *
 */
#undef  FBDEV_USE_DEFAULT_PALETTE   /* if some default palette needed, define FBDEV_USE_DEFAULT_PALETTE */
#undef  FBDEV_DEBUG_VSYNC   /* when enabled, vsync timoeut is printed */
#undef  FBDEV_FLIP_LOCK     /* when enabled, flipping lock is enabled. low performance for multiple POSD update ? */
#define FBDEV_SUPPORT_8BPP_EMUL /* OSD support 8bpp emulation on 32bpp POSD */

#define FBDEV_USE_FBMEM_BKUP    /* backup/restore osd framebuffer during suspend/resume */

#define FBDEV_SUPPORT_OSD_BKUP  /* save/restore OSD plane during suspend/resume. re-enable due to http://hlm.lge.com/qi/browse/QEVENTSIT-846 */
#undef  FBDEV_SUPPORT_OSD_CLEAR_ON_BKUP /* clear OSD plane during OSD backup. disable due to QEVENTSIT-846 */
#undef  FBDEV_SUPPORT_OSD_CLEAR_ON_RESTORE  /* clear OSD framebuffer during resotre. disable due to QEVENTSIT-846 */
#define FBDEV_SUPPORT_CRSR_BKUP /* save/restore cursor image during suspend/resume */
#define FBDEV_SUPPORT_FBC_IMG_CLEAR_ON_RESTORE  /* clear AFBC surface image during restore */

#define FBDEV_USE_FIXED_60HZ_VSYNC  /* OSD supports max 60 FPS even though 120Hz display */

#define FBDEV_USE_LINUX_FRAMEBUFFER /* support linux framebuffer by default */

#ifdef GRAPHICS_DRM_BACKEND			/* do not allocated linuxfb framebuffer when DRM is activated */
#undef FBDEV_USE_LINUX_FRAMEBUFFER
#endif

#undef  FBDEV_USE_USER_INITCALL_ON_RESUME   /* call user_initcal on fbdev resume. disabled by default. see SICDTV-8491 */

/* L9 only Configuration (obsolete)
 *
 */
#undef  FBDEV_GP_USE_16BIT_CURSOR   /* when enabled, GP mode will use 16bit cursor */
#define FBDEV_USE_MMIO_REG  /* when enabled, FB device uses memory based IO. when disabled, FB device uses register based IO
                 * DO NOT modify this macro. register based IO is not working now
                 */
#undef  FBDEV_USE_BLEND_MEMC_SW_FIX /* when enabled, incorrect MEMC output is fixed by software. this workaround is chip specific */

#define USE_FBDEV_CAPTURE   /* when ebaled, support the realtime image capture frame by frmae */
#define USE_FBDEV_FBMEM_HOOK
#define USE_FBDEV_VSYNC_UEVENT  /* support vsync event notifier */
#define USE_FBDEV_USER_FLIP_HANDLER /* support flip event notifier for SW WA */
#undef  USE_FBDEV_ISR_TIME_CHK  /* support vsync ISR duration monitor */
#define FBDEV_USE_FPS_MON
#define FBDEV_USE_DRM_HELPER    /* support DRM helper */

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

typedef struct
{
    char* mem_frame_name;
    unsigned int mem_frame_base;
    unsigned int mem_frame_size;    /* osd frame buffer size */

    char* mem_palette_name;
    unsigned int mem_palette_base;
    unsigned int mem_palette_size;  /* osd palette size */
} LX_FBDEV_DEV_MEM_CFG_T;

typedef struct
{
    char* mem_header_name;
    unsigned int mem_header_base;
    unsigned int mem_header_size;   /* osd header size */
} LX_FBDEV_HDR_MEM_CFG_T;

extern LX_FBDEV_DEV_MEM_CFG_T gMemCfgFBDev[4];  /* obsolete */
extern LX_FBDEV_HDR_MEM_CFG_T gMemCfgFBHdr[4];  /* obsolete */

extern LX_MEMCFG_T gMemCfgFBBuf;    /* 64KB sized common memory buffer */

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif              /* __cplusplus */
#endif              /* _FBDEV_CFG_H_ */
/** @} */
