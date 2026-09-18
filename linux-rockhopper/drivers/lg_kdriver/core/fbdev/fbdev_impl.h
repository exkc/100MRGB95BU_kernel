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
 *  driver interface header for fbdev device. ( used only within kdriver )
 *
 *  @author     raxis
 *  @version    1.0
 *  @date       2009.11.15
 *
 *  @addtogroup lg1150_fbdev
 *  @{
 */

#ifndef _FBDEV_IMPL_H_
#define _FBDEV_IMPL_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/fb.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "fbdev_kapi.h"
#include "fbdev_cfg.h"

#include "afbc_sw_drv.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define MODULE_NAME             "lg1k-fb"
#define OSD0_FBNAME             "osd0_fb"
#define OSD1_FBNAME             "osd1_fb"
#define OSD2_FBNAME             "osd2_fb"
#define OSD3_FBNAME             "crsr_fb"
#define OSD_CURSOR_FBNAME       OSD3_FBNAME

#define is_win(name, x)         ((strcmp(name, x ## _FBNAME) == 0) ? 1 : 0)

#define BYTES_PER_WORD          8       /* 1 bitmap word =  8 byte */
#define BITS_PER_WORD           64      /* 1 bitmap word = 64 bit  */

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define FBDEV_FIXME(msg)

#define FBDEV_ERROR(format,args...)         DBG_PRINT( g_fbdev_debug_fd, LX_LOGM_LEVEL_ERROR, format ,##args)
#define FBDEV_WARN(format, args...)         DBG_PRINT( g_fbdev_debug_fd, LX_LOGM_LEVEL_WARNING, format ,##args)
#define FBDEV_NOTI(format, args...)         DBG_PRINT( g_fbdev_debug_fd, LX_LOGM_LEVEL_NOTI, format ,##args)
#define FBDEV_INFO(format, args...)         DBG_PRINT( g_fbdev_debug_fd, LX_LOGM_LEVEL_INFO, format ,##args)
#define FBDEV_DEBUG(format,args...)         DBG_PRINT( g_fbdev_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define FBDEV_PRINT(format,args...)         DBG_PRINT( g_fbdev_debug_fd, LX_LOGM_LEVEL_DEBUG, format, ##args)
#define FBDEV_TRACE(format,args...)         DBG_PRINT( g_fbdev_debug_fd, LX_LOGM_LEVEL_TRACE, format, ##args)

#define FBDEV_CFG_DEBUG(format,args...)     DBG_PRINT( g_fbdev_debug_fd,  7 /* bit[07] */, format, ##args)
#define FBDEV_IOCTL_DEBUG(format,args...)   DBG_PRINT( g_fbdev_debug_fd,  8 /* bit[08] */, format, ##args)
#define FBDEV_ISR_DEBUG(format,args...)     DBG_PRINT( g_fbdev_debug_fd,  9 /* bit[09] */, format, ##args)
#define FBDEV_BOOT_DEBUG(format,args...)    DBG_PRINT( g_fbdev_debug_fd, 10 /* bit[10] */, format, ##args)

#define FBDEV_HW_DEBUG(format,args...)      DBG_PRINT( g_fbdev_debug_fd, 11 /* bit[11] */, format, ##args)  // for chip kdriver
#define FBDEV_HW0_DEBUG(format,args...)     DBG_PRINT( g_fbdev_debug_fd, 12 /* bit[12] */, format, ##args)  // for chip kdriver
#define FBDEV_HW1_DEBUG(format,args...)     DBG_PRINT( g_fbdev_debug_fd, 13 /* bit[13] */, format, ##args)  // for chip kdriver
#define FBDEV_HW2_DEBUG(format,args...)     DBG_PRINT( g_fbdev_debug_fd, 14 /* bit[14] */, format, ##args)  // for chip kdriver
#define FBDEV_HW3_DEBUG(format,args...)     DBG_PRINT( g_fbdev_debug_fd, 15 /* bit[15] */, format, ##args)  // for chip kdriver
#define FBDEV_HW_NOTI(format,args...)       DBG_PRINT( g_fbdev_debug_fd, 16 /* bit[16] */, format, ##args)  // import noti for chip kdriver

#define FBDEV_LINUXFB_DEBUG(format,args...) DBG_PRINT( g_fbdev_debug_fd, 20 /* bit[20] */, format, ##args)
#define FBDEV_ETC_DEBUG(format,args...)     DBG_PRINT( g_fbdev_debug_fd, 21 /* bit[21] */, format, ##args)
#define FBDEV_VSYNC_DEBUG(format,args...)   DBG_PRINT( g_fbdev_debug_fd, 22 /* bit[22] */, format, ##args)
#define FBDEV_DRM_DEBUG(format,args...)     DBG_PRINT( g_fbdev_debug_fd, 23 /* bit[23] */, format, ##args)

#define FBDEV_PM_DEBUG(format,args...)      DBG_PRINT( g_fbdev_debug_fd, 30 /* bit[31] */, format, ##args)
#define FBDEV_USER_FLIP_DEBUG(format,args...)   DBG_PRINT( g_fbdev_debug_fd, 31 /* bit[31] */, format, ##args)

#define FBDEV_TRACE_BEGIN()
#define FBDEV_TRACE_END()
#define FBDEV_TRACE_MARK()

#define FBDEV_CHECK_DEBUG(__checker,__if_action,fmt,args...)        \
             __CHECK_IF_ERROR(__checker, FBDEV_DEBUG, __if_action , fmt, ##args )

#define FBDEV_CHECK_NOTI(__checker,__if_action,fmt,args...)     \
             __CHECK_IF_ERROR(__checker, FBDEV_NOTI, __if_action , fmt, ##args )

#define FBDEV_CHECK_CODE(__checker,__if_action,fmt,args...)     \
             __CHECK_IF_ERROR(__checker, FBDEV_WARN, __if_action , fmt, ##args )

#define FBDEV_CHECK_ERROR(__checker,__if_action,fmt,args...)    \
             __CHECK_IF_ERROR(__checker, FBDEV_ERROR, __if_action , fmt, ##args )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct fb_var_screeninfo    FBDEV_VAR_SCREEN_T;
typedef struct fb_fix_screeninfo    FBDEV_FIX_SCREEN_T;

typedef struct fbdev_ctx            FBDEV_CTX_T;
typedef struct fbdev_win_ctx        FBDEV_WIN_CTX_T;

struct scanvas
{
    UINT8           fb_dev_id;

    LX_FBDEV_FBC_FORMAT_T   fbc_fmt;    /* AFBC info of current displaying surface */
    LX_FBDEV_PIXEL_FORMAT_T pixel_format;
    LX_FBDEV_PIXEL_FORMAT_T pixel_format_current;

    UINT32          osd_bm_paddr;       /* physical address of current bitmap data.
                                           WORD(64 bit) Pointer to Image (Y Component) allocated in SDRAM  */
    UINT32          prev_osd_bm_paddr;  /* previous bitmap data.
                                           osd_bmp_paddr is stored every new frame is requested */

    UINT8           bits_per_pixel;     /* pixel depth, 1,2,8,16,32... */
    UINT32          stride;             /* byte size of single line. it is human reable value of usWordsPerLine */

    UINT32          color_key_en: 1,    /* color key enable */
                    pixel_order_en: 1,  /* pixel order enable */
                    global_alpha_en: 1, /* global alpha enable */
                    user_global_alpha_en: 1, /* user-debug global alpha enable */
                    blend_alpha_en: 1,  /* global alpha enable */
                    reserver_screen_en: 1,  /* v_mirror enable */
                    user_win_ctrl_en: 1;   /* application-controlled output win enable */

    LX_RECT_T       input_win;          /* input window is used to determine area within OSD bitmap data.
                                         * when updating screen, driver finds the start address of real base
                                         * address to be displayed with input_win.
                                         * input_win shoule be area inside of the real OSD bitmap data.
                                         * for example, if OSD bitmap data is 1366x768, input_win area should
                                         * be located within (0,0,1366,768).
                                         * kdriver also uses xoffset and yoffset for pan_display requet.
                                         * simple equation to calucate the base address is :
                                         *
                                         * base_address = ( bitmap_addr + (input_win.y + yoffset) * bitmap_stride
                                         *                  + ( input_win.x + xoffset )
                                         */

    LX_RECT_T       output_win;         /* output window is used to determine area within display region.
                                         * output window is mapped to the real display ( normally 1920x1080 )
                                         * by customizing both input_win and output_win, we can display any area
                                         * of bitmap data onto any area of display region.
                                         *
                                         * output_win data is direactly written to the L8 OSD register.
                                         */

    LX_RECT_T       test_output_win;    /* output window for debug/test purpose.
                                         * this param overrides all output configuration.
                                         * valid for only graphic plane NOT cursor
                                         */

    UINT32*         palette;            /* palette is allocated at initialiation time */
    UINT32          color_key;          /* 32bit colorkey */
    UINT8           global_alpha;       /* 8bit global alpha */
    UINT8           user_global_alpha;  /* 8bit user-debug global alpha */
    UINT8           blend_alpha;        /* 8Bit blend alpha  */

    LX_DIMENSION_T  csr_size;           /* valid only for cursor layer. user defined cursor size */
    LX_POSITION_T   csr_hotspot;        /* valid only for cursor layer. user defined hotspot position */

    FBDEV_WIN_CTX_T* dm;                /* link to image memory info (not used) */
};

/** context strucutre for each FBDEV(OSD) device
 *  this strut contains HW side OSD parameters.
 *
 */
struct fbdev_win_ctx
{
    UINT8           fb_dev_id;              /* FB Id */
    SINT16          users;                  /* number of requests to open fb device */

    UINT8           linux_fb_mode;          /* if set, linux fb interface will work well */
    struct fb_info  linux_fb_info;          /* linux fb info */
    struct scanvas  pixel;                  /* image description info */

    /* framebuffer area */
    UINT32
    fb_base_phys;           /* physical address of OSD bitmap data. valid when linux framebuffer is active */
    void*           fb_base;                /* ioremapped address */
    UINT32          fb_size;                /* byte size of OSD bitmap data. valid when linux framebuffer is active */

    /*osd header info*/
    UINT32          osd_hdr_base_phys;      /* physical address of indirect OSD header data. not used anymore */
    void*           osd_hdr_base;           /* ioremapped address */
    UINT32          osd_hdr_size;           /* byte size of OSD header (register) . not used anymore*/

    /*palette header info*/
    UINT32          osd_plte_base_phys;     /* physical address of palette data . not used anymore*/
    void*           osd_plte_base;          /* ioremapped address. Not used */
    UINT32          osd_plte_size;          /* number of color in palette, fixed ad 256 . not used anymore*/

    UINT32          pseudo_palette[17];     /* linux fb: fake palette of 16 colors. not used ? */

    OS_SEM_T        fb_dev_mtx;             /* mutex for each FB device */

    struct
    {
        UINT8       b_use_vsync;            /* current FB should wait for vsync for every flip operaration or not */
        UINT8
        b_osd_hdr_write;        /* enable osd header handler or not. if not enabled, OSD header handler is not called */
        UINT8
        b_osd_hdr_flush;        /* enable osd header flush or not. if not enabled, OSD header regs are not updated */

        UINT32      fb_pan_disp_cnt;        /* count of pan_display. count is reset during snapshot boot, instant boot */
        UINT32
        fb_flip_cnt;            /* count of frame buffer update. count is reset during snapshot boot, instant boot */
        UINT32      total_fb_flip_cnt;      /* total count of frame buffer update */
    }
    status;

    int
    vsync_cnt_on_flip;      /* vsync count that will be used to wait on flipping. <0 will not care the vsync. */
    int             vsync_cnt;

    FBDEV_CTX_T*    dm;                     /* pointer to parent context */
};

/** main context structure for FBDEV controller
 *
 *
 */
struct fbdev_ctx
{
    FBDEV_WIN_CTX_T*    wctx[FBDEV_MAX_DEVICE]; /* each layer context */

    struct
    {
        UINT16          pivot_mode;             /* pivot angle. refoer LX_FBDEV_PIVOT_MODE_XXX  */
        UINT8           b_freeze;               /* global osd freeze */

    } global;

    struct device*       dev;                   /* handle for the linux platform device */
};

typedef struct
{
    bool            is_suspend;                 /* QSM+ suspended or not */
    bool            is_runtime_active;          /* runtime active or not */

    UINT32          visible_status;

    struct
    {
        UINT32      visible_status_backup;
    }
    hybernation;
}
FBDEV_PDEV_CTX_T;

/** data struct to support OSD vsync event.
 *  OSD vsync event is supported based on Linux uevent method.
 */
typedef struct
{
    int                 vsync_irq_enabled;
    int                 wait_vsync_cnt;

    struct device*      dev;
    ktime_t             vsync_time;

    struct completion   event;
    spinlock_t          spinlock;
}
FBDEV_VSYNC_EVENT_T;

/** data structure to support user-level flip post hanndler
 *
 */
typedef struct
{
    struct device*      dev;

    int                 enabled;        /* is user flip service active */
    LX_FBDEV_USER_FLIP_T fbmem;         /* current user flip info */
    pid_t               user_pid;       /* connected user process */
    int                 opt;            /* 4 byte key generated from opt string */

    struct completion   user_event;
    struct completion   ack_event;
    spinlock_t          spinlock;
}
FBDEV_USER_FLIP_EVENT_T;

/** data struct to send the image change event to application
 */
typedef struct
{
    int                 wait_cnt;       /* client count to wait event */
    struct completion   event;          /* kernel api to implement event notification */
    spinlock_t          spinlock;       /* not used */
}
FBDEV_RENDER_EVENT_T;

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
struct fb_var_screeninfo* FBDEV_GetVarScreenObject(int idx);

void            FBDEV_InitCfg(void);
void            FBDEV_PostInitCfg(void);

void            FBDEV_GetDefaultPalData(UINT32* pPal);
void            FBDEV_InitCanvas(FBDEV_WIN_CTX_T* w);
int             FBDEV_CleanupLayer(FBDEV_WIN_CTX_T* w);

int             FBDEV_GetConfig(FBDEV_WIN_CTX_T* w, LX_FBDEV_CONFIG_T* config);
int             FBDEV_SetConfig(FBDEV_WIN_CTX_T* w, LX_FBDEV_CONFIG_T* config, BOOLEAN bFlush);

void            FBDEV_SetPalette(FBDEV_WIN_CTX_T* w, UINT32* palette, int num_pal);
void            FBDEV_SetOSDImageEndian(int layer, int bpp);

int             FBDEV_FlipFBImage(int fb_dev_id, LX_FBDEV_FB_IMAGE_T* fb_screen, BOOLEAN b_free_run);
int             FBDEV_UpdateFBScreen(int fb_dev_id, LX_FBDEV_FB_SCREEN_T* fb_screen, BOOLEAN b_free_run);

void            FBDEV_BackupFBList(void);
void            FBDEV_RestoreFBList(const char* snap_boot_mode);

void            FBDEV_PMTest(const char* cmd);

void            FBDEV_MON_Init(void);
void            FBDEV_MON_SetFPSMon(BOOLEAN onoff);
void            FBDEV_MON_NotiRefresh(int fb_dev_id);
void            FBDEV_MON_ISRTick(void);

void            FBDEV_SetInterruptHandler(BOOLEAN enable);
int             FBDEV_WaitForRenderEvent(UINT32 timeout);

int             fbdev_fbc_initialize(void);
UINT32          fbdev_fbc_get_afbc_header_size(UINT32 w, UINT32 h);
UINT32          fbdev_fbc_get_afbc_image_size(UINT32 w, UINT32 h);
int             fbdev_fbc_clear_afbc_image(LX_FBDEV_FBC_FORMAT_T fbc_fmt, UINT32 fbmem_addr, UINT32 width,
        UINT32 height);

void            osd_drm_vsync_tick(void);

/** get FB main context
 *
 * @return pointer to FB device driver
 */
FBDEV_CTX_T*    FBDEV_GetCtx(void);

/** get windows context based on OSD layer
 *
 *
 * @return pointer to dm_win_info if valid layer, NULL otherwise
 */
FBDEV_WIN_CTX_T* FBDEV_GetWinCtx(int layer);

/** get window canvas based on OSD layer
 *
 *
 * @return pointer to scanvas if valid layer, NULL otherwise
 */
struct scanvas* FBDEV_GetWinCanvas(int layer);

void        FBDEV_OpenDRMContext(struct platform_device* pdev, int fb_dev_id);
void        FBDEV_CloseDRMContext(int fb_dev_id);

/** wait vsync for N vsync
 *
 */
int         FBDEV_WaitVSync(int fb_dev_id, int vsync_cnt_on_flip);

// fbdev_utility
const char* fbdev_util_get_fbc_string(LX_FBDEV_FBC_FORMAT_T fmt);

/*----------------------------------------------------------------------------------------
    Extern Variables (module param)
----------------------------------------------------------------------------------------*/
extern  int g_fbdev_use_boot_debug;                 /* if enabled, print booting stage debug msg */
extern  int g_fbdev_use_force_flush_on_freeze_exit; /* if enabled, flush osd screen on freeze exit (experimental) */

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/
extern  int                     g_fbdev_debug_fd;       /** debug id */

#define FBDEV_GET_CFG()         g_fbdev_cfg
extern  LX_FBDEV_CFG_T*         g_fbdev_cfg;            /** FBDEV config */

#define FBDEV_GET_CTX()         g_dm_ctx
extern  FBDEV_CTX_T*            g_dm_ctx;               /** FBDEV main context */

/* FBDEV config access macro */
#define LX_FBDEV_CFG(_fld)      g_fbdev_cfg->_fld

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _FBDEV_DRV_H_ */

/** @} */
