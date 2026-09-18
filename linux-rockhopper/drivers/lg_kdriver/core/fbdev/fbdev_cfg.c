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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include <linux/mm.h>
#include <linux/kernel.h>

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define LCD_PANEL_CLOCK             180000  // not be used

#define MINIMUM_FB_XRES             1280    // when FB doesn't have internal FB memory, use this value
#define MINIMUM_FB_YRES             4   // when FB doesn't have internal FB memory, use this value

#if CONFIG_LX_GRAPHIC_RES>0
#define lx_chip_graphic_res()   CONFIG_LX_GRAPHIC_RES
#else
extern UINT32 lx_chip_graphic_res(void);
#endif

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
/** OSD header size
 *
 */
#define OSD_HEADER_SIZE             32  // same as sizeof(LG1150_OSDHEADER_T))

/** OSD header memory address
 *
 */
#define OSD_HDR_SIZE                LX_CALC_ALIGNED_VALUE(32,4)
#define OSD_PAL_SIZE                (sizeof(UINT32)*256)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
LX_FBDEV_DEV_MEM_CFG_T gMemCfgFBDev[4] =
{
    {
        .mem_palette_name = "fb0_palette", .mem_palette_base = 0x0, .mem_palette_size = 0x0,
        .mem_frame_name = "fb0_frame", .mem_frame_base = 0x0, .mem_frame_size = 0x0,
    },
    {
        .mem_palette_name = "fb1_palette", .mem_palette_base = 0x0, .mem_palette_size = 0x0,
        .mem_frame_name = "fb1_frame", .mem_frame_base = 0x0, .mem_frame_size = 0x0,
    },
    {
        .mem_palette_name = "fb2_palette", .mem_palette_base = 0x0, .mem_palette_size = 0x0,
        .mem_frame_name = "fb2_frame", .mem_frame_base = 0x0, .mem_frame_size = 0x0,
    },
    {
        .mem_palette_name = "fb3_palette", .mem_palette_base = 0x0, .mem_palette_size = 0x0,
        .mem_frame_name = "fb3_frame", .mem_frame_base = 0x0, .mem_frame_size = 0x0,
    }
};

LX_FBDEV_HDR_MEM_CFG_T gMemCfgFBHdr[4] =
{
    {.mem_header_name = "fb0_header", .mem_header_base = 0x0, .mem_header_size = 0x0,},
    {.mem_header_name = "fb1_header", .mem_header_base = 0x0, .mem_header_size = 0x0,},
    {.mem_header_name = "fb2_header", .mem_header_base = 0x0, .mem_header_size = 0x0,},
    {.mem_header_name = "fb3_header", .mem_header_base = 0x0, .mem_header_size = 0x0,}
};

/* 32KB sized FB device buffer for OSD header & plalette */
LX_MEMCFG_T gMemCfgFBBuf = {.name = "fbdev_buf", .base = 0x0, .size = 1 << 15 /* 32KB */  };

/** chip register configuration
 *
 */
FBDEV_HW_IO_CFG_T g_fbdev_reg_cfg[] =
{
    [0] = {
        .chip_name = "FBDEV-unknown",
    },

    // for M17(M16+)
    [1] = {
        .chip_name = "FBDEV-M16P",
#ifdef INCLUDE_M16P_CHIP_KDRV
        .reg_base_addr = 0xc9024100, /* NA */
        .reg_size = 0x600,
        .irq_num = M16P_IRQ_INTR_OSD,    /* IRQS[61] = intr_osd, confirmed by woonghyeon.kim */
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },

    // for O18
    [2] = {
        .chip_name = "FBDEV-O18",
#ifdef INCLUDE_O18_CHIP_KDRV
        .reg_base_addr = 0x0,    /* NA */
        .reg_size = 0,
        .irq_num = O18_IRQ_INTR_OSD, /* IRQS[61] = intr_osd, confirmed by woonghyeon.kim */
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },
    // for M19
    [3] = {
        .chip_name = "FBDEV-M19",
#ifdef INCLUDE_M19_CHIP_KDRV
        .reg_base_addr = 0x0,    /* NA */
        .reg_size = 0,
        .irq_num = M19_IRQ_INTR_OSD, /* IRQS[72] */
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },

    // for O20
    [4] = {
        .chip_name = "FBDEV-O20",
#ifdef INCLUDE_O20_CHIP_KDRV
        .reg_base_addr = 0x0,    /* NA */
        .reg_size = 0,
        .irq_num = 32 + 72,  /* IRQS[72] */
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },

    // for E60
    [5] = {
        .chip_name = "FBDEV-E60",
#ifdef INCLUDE_E60_CHIP_KDRV
        .reg_base_addr = 0x0,    /* NA */
        .reg_size = 0,
        .irq_num = 32 + 72,  /* IRQS[72] */
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },

    // for O22
    [6] = {
        .chip_name = "FBDEV-O22",
#ifdef INCLUDE_O22_CHIP_KDRV
        .reg_base_addr = 0x0,    /* NA */
        .reg_size = 0,
        .irq_num = 32 + 72,  /* IRQS[72] */
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },

    // for M23
    [7] = {
        .chip_name = "FBDEV-M23",
#ifdef INCLUDE_M23_CHIP_KDRV
        .reg_base_addr = 0x0,    /* NA */
        .reg_size = 0,
        .irq_num = 32 + 108, /* IRQS[108] */
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },

    // for O24
    [8] = {
        .chip_name = "FBDEV-M23",
#ifdef INCLUDE_O24_CHIP_KDRV
        .reg_base_addr = 0x0,    /* NA */
        .reg_size = 0,
        .irq_num = 32 + 82,
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },

    // for O26
    [9] = {
        .chip_name = "FBDEV-O26",
#ifdef INCLUDE_O26_CHIP_KDRV
        .reg_base_addr = 0x0,    /* NA */
        .reg_size = 0,
        .irq_num = 32 + 84,
        .hdr_op_method = FBDEV_HDR_OP_REG,   /* hdr operation */
#endif
    },
};

FBDEV_HW_IO_CFG_T* g_fbdev_hwio_cfg = NULL;
LX_FBDEV_CFG_T* g_fbdev_cfg = NULL;

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static LX_FBDEV_CFG_T g_fbdev_cfg_default =
{
    .b_use_irq = 0x1,
    .b_gpu_clock_enable = 0x1,  // GP platform donesn't use GPU !!
    .cursor_layer = 0x3,
    .uhd_disp_mode = 0, // disable UHD display mode by default

    .fb[0] = {
        .b_active = 0x1,
        .b_cursor = 0x0,
        .b_little_endian = 0x1,   // OSD endian is fixed to the littlen. DO NOT try big endian. it's never tested.
        .b_show_on_startup = 0x0,
        .b_use_vsync = 0x1,
        .b_use_global_alpha = 0x0,
        .max_buf_num = 2,
        .bits_per_pixel = 32,
        .pixel_format = LX_FBDEV_PIXEL_FORMAT_RGB_8888,
        .max_xres = CONFIG_LX_FB0_WIDTH,
        .max_yres = CONFIG_LX_FB0_HEIGHT,

        .b_gfx_lock_req = 0x0,
        .b_use_trid_hw = 0x0,
        .b_use_builtin_fbmem = 0x0,   // FALSE by default
        .b_use_afbc = 0x0,
    },

    /* FB[2] may be virtual layer */
    .fb[1] = {
        .b_active = 0x0,
        .b_cursor = 0x0,
        .b_little_endian = 0x1,   // OSD endian is fixed to the littlen. DO NOT try big endian. it's never tested.
        .b_show_on_startup = 0x0,
        .b_use_vsync = 0x1,
        .b_use_global_alpha = 0x0,
        .max_buf_num = 2,
        .bits_per_pixel = 32,
        .pixel_format = LX_FBDEV_PIXEL_FORMAT_RGB_8888,
        .max_xres = CONFIG_LX_FB1_WIDTH,
        .max_yres = CONFIG_LX_FB1_HEIGHT,
        .b_gfx_lock_req = 0x0,
        .b_use_trid_hw = 0x0,
        .b_use_builtin_fbmem = 0x0,   // FALSE by default
        .b_use_afbc = 0x0,
    },

    /* FB[2] is not used anymore or future use */
    .fb[2] = {
        .b_active = 0x0,
        .b_cursor = 0x0,
        .b_little_endian = 0x1,   // OSD endian is fixed to the littlen. DO NOT try big endian. it's never tested.
        .b_show_on_startup = 0x0,
        .b_use_vsync = 0x1,   // UI screen sometimes needs animation synced with vsync isr.

        .b_use_global_alpha = 0x0,
        .max_buf_num = 2,
        .bits_per_pixel = 32,
        .pixel_format = LX_FBDEV_PIXEL_FORMAT_RGB_8888,
        .max_xres = 128,
        .max_yres = 2,

        .b_gfx_lock_req = 0x0,
        .b_use_trid_hw = 0x0,
        .b_use_builtin_fbmem = 0x0,   // FALSE by default
        .b_use_afbc = 0x0,
    },

    /* FB[3] is cursor layer */
    .fb[3] = {
        .b_active = 0x1,
        .b_cursor = 0x1,
        .b_little_endian = 0x1,   // OSD endian is fixed to the littlen. DO NOT try big endian. it's never tested.
        .b_show_on_startup = 0x0,
        .b_use_vsync = 0x1,

        .b_use_global_alpha = 0x0,
        .max_buf_num = 2,
        .bits_per_pixel = 32,
        .pixel_format = LX_FBDEV_PIXEL_FORMAT_RGB_8888,
        .max_xres = CONFIG_LX_FB3_WIDTH,
        .max_yres = CONFIG_LX_FB3_HEIGHT,

        .b_gfx_lock_req = 0x0,
        .b_use_trid_hw = 0x0,
        .b_use_builtin_fbmem = 0x0,   // FALSE by default
        .b_use_afbc = 0x0,
    },
};

static struct fb_var_screeninfo default_fb_var_screeninfo[LX_FBDEV_ID_MAX] =
{
    /* fb(0) default value */
    {
        /* xres, yres, xres_virtual, yres_virtual is initialized at FBDEV_InitCfg */
        /* bits_per_pixel, red, green, blue, transp is initialized at FBDEV_InitCfg */
        /* hsync_len ( pixel format ), vsync_len ( pixel depth ) is initialized at FBDEV_InitCfg */
        .xoffset = 0,
        .yoffset = 0,
        .grayscale = 0,

        .nonstd = 0,
        .activate = FB_ACTIVATE_FORCE,
        .height = -1,
        .width = -1,
        .accel_flags = 0,
        .pixclock = LCD_PANEL_CLOCK,   /* picoseconds */
        .left_margin = 40, /* pixclocks */
        .right_margin = 4, /* pixclocks */
        .upper_margin = 8, /* line clocks */
        .lower_margin = 2, /* line clocks */

        .sync = 0,
        .vmode = FB_VMODE_NONINTERLACED,
    },

    /* fb(1) default value */
    {
        /* xres, yres, xres_virtual, yres_virtual is initialized at FBDEV_InitCfg */
        /* bits_per_pixel, red, green, blue, transp is initialized at FBDEV_InitCfg */
        /* hsync_len ( pixel format ), vsync_len ( pixel depth ) is initialized at FBDEV_InitCfg */

        .xoffset = 0,
        .yoffset = 0,
        .grayscale = 0,

        .nonstd = 0,
        .activate = FB_ACTIVATE_FORCE,
        .height = -1,
        .width = -1,
        .accel_flags = 0,
        .pixclock = LCD_PANEL_CLOCK,   /* picoseconds */
        .left_margin = 40, /* pixclocks */
        .right_margin = 4, /* pixclocks */
        .upper_margin = 8, /* line clocks */
        .lower_margin = 2, /* line clocks */

        .sync = 0,
        .vmode = FB_VMODE_NONINTERLACED,
    },

    /* fb(2) default value */
    {
        /* xres, yres, xres_virtual, yres_virtual is initialized at FBDEV_InitCfg */
        /* bits_per_pixel, red, green, blue, transp is initialized at FBDEV_InitCfg */
        /* hsync_len ( pixel format ), vsync_len ( pixel depth ) is initialized at FBDEV_InitCfg */

        .xoffset = 0,
        .yoffset = 0,
        .grayscale = 0,

        .nonstd = 0,
        .activate = FB_ACTIVATE_FORCE,
        .height = -1,
        .width = -1,
        .accel_flags = 0,
        .pixclock = LCD_PANEL_CLOCK,   /* picoseconds */
        .left_margin = 40, /* pixclocks */
        .right_margin = 4, /* pixclocks */
        .upper_margin = 8, /* line clocks */
        .lower_margin = 2, /* line clocks */

        .sync = 0,
        .vmode = FB_VMODE_NONINTERLACED,
    },

    /* fb(3) default value */
    {
        /* xres, yres, xres_virtual, yres_virtual is initialized at FBDEV_InitCfg */
        /* bits_per_pixel, red, green, blue, transp is initialized at FBDEV_InitCfg */
        /* hsync_len ( pixel format ), vsync_len ( pixel depth ) is initialized at FBDEV_InitCfg */

        .xoffset = 0,
        .yoffset = 0,
        .grayscale = 0,

        .nonstd = 0,
        .activate = FB_ACTIVATE_FORCE,
        .height = -1,
        .width = -1,
        .accel_flags = 0,
        .pixclock = LCD_PANEL_CLOCK,   /* picoseconds */
        .left_margin = 40, /* pixclocks */
        .right_margin = 4, /* pixclocks */
        .upper_margin = 8, /* line clocks */
        .lower_margin = 2, /* line clocks */

        .sync = 0,
        .vmode = FB_VMODE_NONINTERLACED,
    },
};

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
    Implementation Group
========================================================================================*/
/** get preinitialized fb_var_screeninfo object
 *
 *
 */
struct fb_var_screeninfo* FBDEV_GetVarScreenObject(int idx)
{
    FBDEV_CHECK_ERROR(idx >= LX_FBDEV_ID_MAX, return NULL, "out of range (%d)\n", idx);

    return &default_fb_var_screeninfo[idx];
}

/** initialize FBDEV configuration
 *
 *
 */
void FBDEV_InitCfg(void)
{
    int i;
    UINT16 gfx_res_width;
    UINT16 gfx_res_height;

    /* select active chip configuration */
    g_fbdev_cfg = &g_fbdev_cfg_default;

    switch (lx_chip())
    {
        case LX_CHIP_M17:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[1];
        }
        break;

        case LX_CHIP_O18:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[2];
        }
        break;

        case LX_CHIP_M19:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[3];
        }
        break;

        case LX_CHIP_O20:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[4];
        }
        break;

        case LX_CHIP_E60:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[5];
        }
        break;

        case LX_CHIP_O22:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[6];
        }
        break;

        case LX_CHIP_M23:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[7];
        }
        break;

        case LX_CHIP_O24:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[8];
        }
        break;

        case LX_CHIP_O26:
        {
            g_fbdev_hwio_cfg = &g_fbdev_reg_cfg[9];
        }
        break;

        default:
        {
            DBG_PRINT_ERROR("not supported chip 0x%x\n", lx_chip_rev());
        }
        break;
    }

    /* determin framebuffer size
     *
     * raxis.lim (2019/05/22)
     * Some SoC such as O20 supports another graphic lyaer fb(1), we should check whether fb(1) is active or not
     * by asking FBDEV_HW_CMD_RD_POSD_MAX_RES_CAPS to chip kdriver
     *
     */
    gfx_res_width = LX_RES_GET_WIDTH(lx_chip_graphic_res());
    gfx_res_height = LX_RES_GET_HEIGHT(lx_chip_graphic_res());

    g_fbdev_cfg->uhd_disp_mode = (gfx_res_width > 1920) ? TRUE : FALSE;

    printk("fb default_res=%dx%d, uhd_disp_mode=%s\n",
           gfx_res_width, gfx_res_height, g_fbdev_cfg->uhd_disp_mode ? "on" : "off");

#define OSD_BUF_NUM(id)         g_fbdev_cfg->fb[(id)].max_buf_num
#define OSD0_XRES               g_fbdev_cfg->fb[0].max_xres
#define OSD0_YRES               g_fbdev_cfg->fb[0].max_yres
#define OSD0_BYTES_PER_PIXEL    ( g_fbdev_cfg->fb[0].bits_per_pixel >> 3 )
#define OSD1_XRES               g_fbdev_cfg->fb[1].max_xres
#define OSD1_YRES               g_fbdev_cfg->fb[1].max_yres
#define OSD1_BYTES_PER_PIXEL    ( g_fbdev_cfg->fb[1].bits_per_pixel >> 3 )
#define OSD2_XRES               g_fbdev_cfg->fb[2].max_xres
#define OSD2_YRES               g_fbdev_cfg->fb[2].max_yres
#define OSD2_BYTES_PER_PIXEL    ( g_fbdev_cfg->fb[2].bits_per_pixel >> 3 )
#define OSD3_XRES               g_fbdev_cfg->fb[3].max_xres
#define OSD3_YRES               g_fbdev_cfg->fb[3].max_yres
#define OSD3_BYTES_PER_PIXEL    ( g_fbdev_cfg->fb[3].bits_per_pixel >> 3 )

    /* raxis.lim (2019/05/24)
     *
     * after HW configuration at chip kdriver, I will try to fetch framebuffer size information
     */
    if (OSD0_XRES == 0 || OSD0_YRES == 0 /* auto detect */)
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;

        hw_cmd.gen[0] = LX_FBDEV_ID_OSD0;

        if (RET_OK == FBDEV_ExecHWCommand(FBDEV_HW_CMD_RD_POSD_MAX_RES_CAPS, &hw_cmd))
        {
            OSD0_XRES = LX_RES_GET_WIDTH(hw_cmd.gen[0]);
            OSD0_YRES = LX_RES_GET_HEIGHT(hw_cmd.gen[0]);

            printk("fb(0) size=%dx%d\n", OSD0_XRES, OSD0_YRES);

            if (hw_cmd.gen[1] > 0)
            {
                g_fbdev_cfg->fb[0].b_use_afbc = (hw_cmd.gen[1] == 2) ? TRUE : FALSE;
            }
            else
            {
                g_fbdev_cfg->fb[0].b_use_afbc = TRUE;   /* default */
            }

            if (hw_cmd.gen[2] > 0)
            {
                g_fbdev_cfg->fb[0].max_buf_num = hw_cmd.gen[2];
            }
        }
        else
        {
            OSD0_XRES = gfx_res_width;
            OSD0_YRES = gfx_res_height;

            printk("fb(0) size=%dx%d (fixed)\n", OSD0_XRES, OSD0_YRES);
        }
    }

    if (OSD1_XRES == 0 || OSD1_YRES == 0 /* auto detect */)
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;

        hw_cmd.gen[0] = LX_FBDEV_ID_OSD1;

        if (RET_OK == FBDEV_ExecHWCommand(FBDEV_HW_CMD_RD_POSD_MAX_RES_CAPS, &hw_cmd))
        {
            OSD1_XRES = LX_RES_GET_WIDTH(hw_cmd.gen[0]);
            OSD1_YRES = LX_RES_GET_HEIGHT(hw_cmd.gen[0]);

            printk("fb(1) size=%dx%d\n", OSD1_XRES, OSD1_YRES);

            g_fbdev_cfg->fb[1].b_active = TRUE;

            if (hw_cmd.gen[1] > 0)
            {
                g_fbdev_cfg->fb[1].b_use_afbc = (hw_cmd.gen[1] == 2) ? TRUE : FALSE;
            }
            else
            {
                g_fbdev_cfg->fb[1].b_use_afbc = FALSE;  /* default */
            }

            if (hw_cmd.gen[2] > 0)
            {
                g_fbdev_cfg->fb[1].max_buf_num = hw_cmd.gen[2];
            }
        }
        else
        {
            OSD1_XRES = gfx_res_width;
            OSD1_YRES = gfx_res_height;

            g_fbdev_cfg->fb[1].b_active = FALSE;

            printk("fb(1) size=%dx%d (disabled)\n", OSD1_XRES, OSD1_YRES);
        }
    }

    if (OSD3_XRES == 0 || OSD3_YRES == 0 /* auto detect */)
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;

        hw_cmd.gen[0] = LX_FBDEV_ID_OSD3;

        if (RET_OK == FBDEV_ExecHWCommand(FBDEV_HW_CMD_RD_POSD_MAX_RES_CAPS, &hw_cmd))
        {
            OSD3_XRES = LX_RES_GET_WIDTH(hw_cmd.gen[0]);
            OSD3_YRES = LX_RES_GET_HEIGHT(hw_cmd.gen[0]);

            printk("fb(3) size=%dx%d\n", OSD3_XRES, OSD3_YRES);

            g_fbdev_cfg->fb[3].b_active = TRUE;

            if (hw_cmd.gen[2] > 0)
            {
                g_fbdev_cfg->fb[3].max_buf_num = hw_cmd.gen[2];
            }
        }
        else
        {
            OSD3_XRES = 256;    /* set by standard default value */
            OSD3_YRES = 256;    /* set by standard default value */

            printk("fb(3) size=%dx%d (default)\n", OSD3_XRES, OSD3_YRES);
        }
    }

    /* scan command line for user-defined fbdev(osd) configuration */
    {
        char opt[8];
#ifdef FBDEV_USE_LINUX_FRAMEBUFFER
        int linux_fb_mode = 2;  /* default : support linux_fb & conditional afbc */
#else
        int linux_fb_mode = 0;
#endif

        if (RET_OK == OS_ScanKernelCmdline("fbdev.linux_fb.mode=%s", opt))
        {
            linux_fb_mode = opt[0] - '0';
        }

        switch (linux_fb_mode)
        {
            case 3:
            {
                printk("[fb] enable linux framebuffer with afbc mode (always enabled)\n");

                for (i = 0; i < LX_FBDEV_ID_MAX; i++)
                {
                    /* linux framebuffer is supported only for full-screen display NOT cursor */
                    if (g_fbdev_cfg->fb[i].b_active && !g_fbdev_cfg->fb[i].b_cursor)
                    {
                        g_fbdev_cfg->fb[i].b_use_builtin_fbmem = TRUE;
                        g_fbdev_cfg->fb[i].b_use_afbc = 1;
                    }
                }
            }
            break;

            case 2:
            {
                printk("[fb] enable linux framebuffer with afbc mode (conditionally enabeld)\n");

                for (i = 0; i < LX_FBDEV_ID_MAX; i++)
                {
                    /* linux framebuffer is supported only for full-screen display NOT cursor */
                    if (g_fbdev_cfg->fb[i].b_active && !g_fbdev_cfg->fb[i].b_cursor)
                    {
                        g_fbdev_cfg->fb[i].b_use_builtin_fbmem = TRUE;
                    }
                }
            }
            break;

            case 1:
            {
                printk("[fb] enable linux framebuffer without afbc mode\n");

                for (i = 0; i < LX_FBDEV_ID_MAX; i++)
                {
                    /* linux framebuffer is supported only for full-screen display NOT cursor */
                    if (g_fbdev_cfg->fb[i].b_active && !g_fbdev_cfg->fb[i].b_cursor)
                    {
                        g_fbdev_cfg->fb[i].b_use_builtin_fbmem = TRUE;
                        g_fbdev_cfg->fb[i].b_use_afbc = 0;
                    }
                }
            }
            break;

            default:
            {
                printk("[fb] disable linux framebuffer\n");

                for (i = 0; i < LX_FBDEV_ID_MAX; i++)
                {
                    g_fbdev_cfg->fb[i].b_use_builtin_fbmem = FALSE;
                }
            }
            break;
        }
    }

    /* construct default_fb_var_screeninfo array */
    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        struct fb_var_screeninfo* fb_info = &default_fb_var_screeninfo[i];

        fb_info->xres = g_fbdev_cfg->fb[i].max_xres;
        fb_info->yres = g_fbdev_cfg->fb[i].max_yres;
        fb_info->xres_virtual = g_fbdev_cfg->fb[i].max_xres;
        fb_info->yres_virtual = g_fbdev_cfg->fb[i].max_yres * OSD_BUF_NUM(i);
        fb_info->bits_per_pixel = g_fbdev_cfg->fb[i].bits_per_pixel;

        /* only 32bit supported */
        {
            struct fb_bitfield a = { 24, 8, 0 };
            struct fb_bitfield r = { 16, 8, 0 };
            struct fb_bitfield g = { 8, 8, 0 };
            struct fb_bitfield b = { 0, 8, 0 };

            fb_info->transp = a, fb_info->red = r, fb_info->green = g, fb_info->blue = b;
        }
    }

    /* raxis.lim (2016/06/01) -- below memory layout is obsolete
     * since 2016, I will allocate Linux framebuffer from GFX surface area.
     * so below codes will be removed soon.
     */
    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        gMemCfgFBDev[i].mem_frame_base = 0x00000000;
        gMemCfgFBDev[i].mem_frame_size = 0x1000;
        gMemCfgFBDev[i].mem_palette_base = 0x00000000;
        gMemCfgFBDev[i].mem_palette_size = OSD_PAL_SIZE;

        gMemCfgFBHdr[i].mem_header_base = 0x0000000;
        gMemCfgFBHdr[i].mem_header_size = OSD_HDR_SIZE;
    }
}

/* post configuration after memory layouot
 *
 *
 */
void FBDEV_PostInitCfg(void)
{
    int i;
    UINT32 base_addr = gMemCfgFBBuf.base;

    if (base_addr == 0x0)
    {
        return;    /* post configuration is activated only when FBBuf memory is valid */
    }

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        base_addr = PAGE_ALIGN(base_addr);  /* get 4K-aligned value */

        if (gMemCfgFBDev[i].mem_frame_base == 0x0)
        {
            gMemCfgFBDev[i].mem_frame_base = base_addr;
            base_addr += PAGE_ALIGN(gMemCfgFBDev[i].mem_frame_size);

            gMemCfgFBDev[i].mem_palette_base = base_addr;
            base_addr += PAGE_ALIGN(gMemCfgFBDev[i].mem_palette_size);

            gMemCfgFBHdr[i].mem_header_base = base_addr;
            base_addr += PAGE_ALIGN(gMemCfgFBHdr[i].mem_header_size);
        }

        FBDEV_BOOT_DEBUG("fb(%d) - frame: 0x%08x palette: 0x%08x header: 0x%08x\n", i,
                         gMemCfgFBDev[i].mem_frame_base, gMemCfgFBDev[i].mem_palette_base,
                         gMemCfgFBHdr[i].mem_header_base);
    }
}

/** @} */
