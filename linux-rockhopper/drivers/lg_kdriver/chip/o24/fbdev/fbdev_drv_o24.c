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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     raxis.lim
 *  @version    1.0
 *  @date       2021-04-01
 *  @note       Additional information.
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_o24.h"
#include "osd_reg_o24.h"
#include "osd_shp_reg_o24.h"
#include "osd_afbc_reg_o24.h"
#include "osd_afrc_reg_o24.h"
#include "osd_mif0_reg_o24.h"
#include "osd_mif1_reg_o24.h"
#include "osd_top_ctrl_reg_o24.h"
#include "osd_top_ctrl1_reg_o24.h"
#include <linux/workqueue.h>        /**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

#include "../sys/ctop_regs.h"
#include "ovi_kapi.h"

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
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int OVI_HAL_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T* pstParams);

void FBDEV_O24_InitHWCtx(FBDEV_HW_CTX_T* hal_obj);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern FBDEV_O24_HW_FUNC_T      g_fbdev_o24_cmn_hw_func;    /* O20 HW common func */

/*----------------------------------------------------------------------------------------
    global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_O24_InitOSDZOrder(void);
LX_FBDEV_CFG_T* FBDEV_O24_GetCfg(void);

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
volatile OSD_TOP_CTRL_O24_REG_T* g_osd_top_ctrl_o24_reg = NULL;
OSD_TOP_CTRL_O24_REG_T* g_osd_top_ctrl_o24_reg_shadow = NULL;

volatile OSD_TOP_CTRL1_O24_REG_T* g_osd_top_ctrl1_o24_reg = NULL;
OSD_TOP_CTRL1_O24_REG_T* g_osd_top_ctrl1_o24_reg_shadow = NULL;

volatile OSD_O24_REG_T* g_osd_o24_reg = NULL;
OSD_O24_REG_T* g_osd_o24_reg_shadow = NULL;

volatile OSD_SHP_O24_REG_T* g_osd_shp_o24_reg = NULL;
OSD_SHP_O24_REG_T* g_osd_shp_o24_reg_shadow = NULL;

volatile OSD_AFBC_O24_REG_T* g_osd_afbc_o24_reg[2] = {NULL, NULL};
OSD_AFBC_O24_REG_T* g_osd_afbc_o24_reg_shadow[2] = {NULL, NULL};

volatile OSD_AFRC_O24_REG_T* g_osd_afrc_o24_reg[2] = {NULL, NULL};
OSD_AFRC_O24_REG_T* g_osd_afrc_o24_reg_shadow[2] = {NULL, NULL};

volatile OSD_MIF0_CTRL_O24_REG_T* g_osd_mif0_o24_reg = NULL;
OSD_MIF0_CTRL_O24_REG_T* g_osd_mif0_o24_reg_shadow = NULL;

volatile OSD_MIF1_CTRL_O24_REG_T* g_osd_mif1_o24_reg = NULL;
OSD_MIF1_CTRL_O24_REG_T* g_osd_mif1_o24_reg_shadow = NULL;

static FBDEV_O24_HW_CTX_T       g_fbdev_o24_hw_ctx;         /* O20 OSD H/W ctrl */

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_O24_AutoDetectOSDHWValue(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static  FBDEV_HW_CTX_T  _g_fbdev_hw_ctx =
{
    .GetCfg             = FBDEV_O24_GetCfg,
    .RunSuspend         = FBDEV_O24_CMN_RunSuspend,
    .RunResume          = FBDEV_O24_CMN_RunResume,

    .InitHW             = FBDEV_O24_InitHW,
    .ShutdownHW         = FBDEV_O24_ShutdownHW,
    .ExecHWCommand      = FBDEV_O24_CMN_ExecHWCommand,

    .SetOSDEnable       = FBDEV_O24_CMN_SetOSDEnable,
    .GetOSDEnable       = FBDEV_O24_CMN_GetOSDEnable,

    .InitOSDLayer       = FBDEV_O24_CMN_InitOSDLayer,
    .WriteOSDHeader     = FBDEV_O24_CMN_WriteOSDHeader,

    .GetZList           = FBDEV_O24_GetZList,
    .SetZList           = FBDEV_O24_SetZList,

    .WriteOSDEndian     = FBDEV_O24_WriteOSDEndian,
    .WriteOSDCSC        = FBDEV_O24_WriteOSDCSC,

    .GetInterruptStatus = FBDEV_O24_CMN_GetInterruptStatus,
    .SetInterruptClear  = FBDEV_O24_CMN_SetInterruptClear,
    .SetInterruptEnable = FBDEV_O24_CMN_SetInterruptEnable,

    .SetViewCtrl        = FBDEV_O24_CMN_SetViewCtrl,
    .SetConnCtrl        = FBDEV_O24_CMN_SetConnCtrl,

    .CreateProc         = FBDEV_O24_CreateProc,
    .ProcHandler        = FBDEV_O24_CMN_ProcHandler,
};

/*========================================================================================
    Implementation Group
========================================================================================*/
// get O20 specific configuration. return LX_FBDEV_CFG_T
LX_FBDEV_CFG_T*   FBDEV_O24_GetCfg(void)
{
    return NULL;
}

// initialize O20 specific HW context variables.
// this function is called before at O24 configure stage NOT at HW initialization stage.
void    FBDEV_O24_InitHWCtx(FBDEV_HW_CTX_T* hal_obj)
{
    int i;

    /* initialize chip dependent variable */
    {
        g_fbdev_frc_ctrl.b_frc_sep_enable   = FALSE;    /* Blending Mode by default */
        g_fbdev_frc_ctrl.b_frc_UD_enable    = FALSE;    /* Standard Mode by default */
        g_fbdev_frc_ctrl.b_frc_hdr_emul     = FALSE;    /* Disable FRC HDR emulation */
        g_fbdev_frc_ctrl.b_frc_osd_emul     = TRUE;
        g_fbdev_frc_ctrl.frc_hdr_emul_dev   = -1;
    }

    /* select the active O20 HW function handler */
    memcpy(&g_fbdev_o24_hw_ctx.func, &g_fbdev_o24_cmn_hw_func, sizeof(FBDEV_O24_HW_FUNC_T));

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        g_fbdev_o24_hw_ctx.conn_ctrl[i].conn_type   = g_fbdev_o24_hw_ctx.hw_conn_type;
        g_fbdev_o24_hw_ctx.fbc_ctrl[i].status       = FBDEV_O24_FBC_STATUS_NONE;
        g_fbdev_o24_hw_ctx.sr_ctrl[i].status        = FBDEV_O24_SR_STATUS_OFF;
        g_fbdev_o24_hw_ctx.sr_ctrl[i].coeff[0]      = 0x3FD;
        g_fbdev_o24_hw_ctx.sr_ctrl[i].coeff[1]      = 0x83;
        g_fbdev_o24_hw_ctx.sr_ctrl[i].coeff[2]      = 0x83;
        g_fbdev_o24_hw_ctx.sr_ctrl[i].coeff[3]      = 0x3FD;

        g_fbdev_o24_hw_ctx.sr_ctrl[i].ti_gain       = -1;
    }

    g_fbdev_o24_hw_ctx.mirror_ctrl.status       = FBDEV_O24_MIRROR_NONE;

    memset(&g_fbdev_o24_hw_ctx.ext_render_ctrl, 0x0, sizeof(FBDEV_O24_EXT_RENDER_CTRL_T));

    /* auto detect the default OSD connection and display size etc */
    FBDEV_O24_AutoDetectOSDHWValue();

    /* initialize hal object
     * after this function, all fbdev kdriver can get g_fbdev_o24_hw_ctx via g_fbdev_hw_ctx->chip_priv_ctx
     */
    memcpy(hal_obj, &_g_fbdev_hw_ctx, sizeof(FBDEV_HW_CTX_T));

    hal_obj->chip_priv_ctx = &g_fbdev_o24_hw_ctx;
}

// detect the default OSD connection
// this function will return the default(best) OSD connection setup based on SW, HW info
static void FBDEV_O24_AutoDetectOSDHWValue(void)
{
#ifdef BUILD_FEATURE_fpga
    UINT32  osd_fb0_img_val     = LX_MAKE_RES(3840, 2160);
#else
    UINT32  osd_fb0_img_val     = LX_MAKE_RES(1920, 1080);      /* defualt fb0 image. default 2K resolution */
#endif
    UINT32  osd_fb1_img_val     = LX_MAKE_RES(1024, 4320);      /* defualt fb1 image for 8KTV, default size=1K*4K */
    UINT32  osd_disp_bosd_val   = LX_MAKE_RES(3840, 2160);      /* default 4K resolution */
    UINT32  osd_disp_sosd_val   = LX_MAKE_RES(3840, 2160);      /* default 4K resolution */
    UINT32  osd_conn_val        = LX_FBDEV_CONN_OSD_VIDEO_BLEND;/* default path */
    UINT32  osd_pulse_bosd_val  = 0xA000;                       /* default pulse timer delay. default 0xA000 */
    UINT32  osd_pulse_sosd_val  = 0xA000;                       /* default pulse timer delay. default 0xA000 */

    UINT32  ext_render_sz_val   = LX_MAKE_RES(1920, 2160);      /* (960*2) x (4320/2) */
    UINT32  osd_ext_render_swsync_hz_val = 20;                  /* default 8k ext swsync interval. default 20Hz=30.00 ms */

    UINT32  osd_disp_path_test_mode = FALSE;

    FBDEV_O24_HW_CTX_T* hw_ctx = &g_fbdev_o24_hw_ctx;

    /* make the initial HW WA config */
    hw_ctx->hw_wa_flag = 0x0;

    /* get HW display option from both hwopts and OVI */
    hw_ctx->b_support_ext_frc = 0;
    hw_ctx->b_support_ext_render = 0;

    /* read HW configuration by parsing some kernel parameters */
    {
        if (lx_board_opt() & LX_BOARD_OPT_EXT_FRC)
        {
            printk("<!> fbdev EXT_FRC(F22) detected from hwopts\n");
            hw_ctx->b_support_ext_frc = 1;

            // enable (virtual) fb1 for e-streamer
            hw_ctx->b_support_fb1 = 1;
        }
        else
        {
            hw_ctx->b_support_ext_frc = 0;
#ifdef FBDEV_O24_SUPPORT_4K_ESTREAMER
            hw_ctx->b_support_fb1 = 1;
#else
            hw_ctx->b_support_fb1 = 0;
#endif
        }

        // 각 플랫폼에 맞게 기존에 알려진 기본 값으로 설정
        // 세부 설정에 따라 fb0, fb1 크기는 재설정됨
        // 특히 fb0 image size 의 경우에는 graphic resolution 값에 의하여 재설정됨
        if (lx_chip_plt() & LX_CHIP_PLT_QUHD)
        {
            printk("<!> fbdev 8K platform detected\n");
            osd_disp_sosd_val = LX_MAKE_RES(3840, 2160);
            osd_fb0_img_val   = LX_MAKE_RES(3840, 2160);
            osd_fb1_img_val   = LX_MAKE_RES(1024, 4320);
        }
        else if (lx_chip_plt() & LX_CHIP_PLT_UHD)
        {
            printk("<!> fbdev 4K platform detected\n");
            osd_disp_bosd_val = LX_MAKE_RES(3840, 2160);
            osd_fb0_img_val   = LX_MAKE_RES(1920, 1080);
            osd_fb1_img_val   = LX_MAKE_RES(512, 2160);
        }
        else if (lx_chip_plt() & LX_CHIP_PLT_FHD)
        {
            printk("<!> fbdev 2K platform detected\n");
            osd_disp_bosd_val = LX_MAKE_RES(1920, 1080);
            osd_fb0_img_val   = LX_MAKE_RES(1920, 1080);
            osd_fb1_img_val   = LX_MAKE_RES(256, 1080);
        }
        else if (lx_chip_plt() & LX_CHIP_PLT_HD)
        {
            printk("<!> fbdev HD platform detected\n");
            osd_disp_bosd_val = LX_MAKE_RES(1368, 768);
            osd_fb0_img_val   = LX_MAKE_RES(1368, 768);
            osd_fb1_img_val   = LX_MAKE_RES(192, 768);
        }
        else
        {
            printk("unknown platform. chip_plt=0x%x. default value will be used\n", lx_chip_plt());
        }

        if (lx_board_opt() & LX_BOARD_OPT_4K_GRAPHIC)
        {
            printk("<!> fbdev 4K OSD detected\n");
            osd_fb0_img_val = LX_MAKE_RES(3840, 2160);
        }
        else if (lx_board_opt() & LX_BOARD_OPT_2K_GRAPHIC)
        {
            printk("<!> fbdev 2K OSD detected\n");
            osd_fb0_img_val = LX_MAKE_RES(1920, 1080);
        }
        else if (lx_board_opt() & LX_BOARD_OPT_HD_GRAPHIC)
        {
            printk("<!> fbdev HD OSD detected\n");
            osd_fb0_img_val = LX_MAKE_RES(1280, 720);
        }
        else
        {
            printk("unknown graphic resolution. board_opt=0x%x. default value will be used\n", lx_board_opt());
        }
    }

    /* read HW configuration by querying OVI */
#ifdef INCLUDE_KDRV_OVI
    {
        LX_OVI_HW_DISPLAY_INFO_T disp_info;

        if (OVI_HAL_GetHWDisplayOption(&disp_info) == RET_OK)
        {
            if (disp_info.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F20)
            {
                printk("<!> fbdev EXT_FRC(F22) detected from OVI\n");
                hw_ctx->b_support_ext_frc = 1;
            }
        }
    }
#endif

    /* scan test options for internal debug use only. override the default configuration */
    {
        char    opt[32];
        UINT32  val;

        /* support F20 ext_frc emulation regardless of F20 */
        if (RET_OK == OS_ScanKernelCmdline("osd.ext_frc=%s", opt))
        {
            sscanf(opt, "%d", &val);

            if (val == 1)
            {
                hw_ctx->b_support_ext_frc = 1;
                hw_ctx->b_support_fb1 = 1;
            }
            else if (val == 0)
            {
                hw_ctx->b_support_ext_frc = 0;
#ifdef FBDEV_O24_SUPPORT_4K_ESTREAMER
                hw_ctx->b_support_fb1 = 0;;
#else
                hw_ctx->b_support_fb1 = 0;;
#endif
            }
        }
    }

    // select osd path and configure external render based on both support_ext_frc and support_fb1 flag
    if (hw_ctx->b_support_ext_frc)
    {
        osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE;
    }
    else
    {
        osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_BLEND;
    }

    if (hw_ctx->b_support_fb1 && hw_ctx->b_support_ext_frc)
    {
        hw_ctx->b_support_ext_render = 1;
    }
    else
    {
        hw_ctx->b_support_ext_render = 0;
        ext_render_sz_val = LX_MAKE_RES(16, 16); /* make size as small as possible */
    }

    // internal debug use only. override the auto configured values
    {
        char    opt[32];
        UINT32  val, res_w, res_h;

        if (RET_OK == OS_ScanKernelCmdline("osd.disp.path=%s", opt))
        {
            if (!strncmp(opt, "sosd", 4))
            {
                osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE;
            }
            else if (!strncmp(opt, "bosd", 4))
            {
                osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_BLEND;
            }

            osd_disp_path_test_mode = TRUE; /* keep current osd path regardless of the real HW config */
        }

        if (RET_OK == OS_ScanKernelCmdline("osd.disp.bosd=%s", opt))
        {
            sscanf(opt, "%dx%d", &res_w, &res_h);
            osd_disp_bosd_val = LX_MAKE_RES(res_w, res_h);
        }

        if (RET_OK == OS_ScanKernelCmdline("osd.disp.sosd=%s", opt))
        {
            sscanf(opt, "%dx%d", &res_w, &res_h);
            osd_disp_sosd_val = LX_MAKE_RES(res_w, res_h);
        }

        if (RET_OK == OS_ScanKernelCmdline("osd.fb.fb0=%s", opt))
        {
            sscanf(opt, "%dx%d", &res_w, &res_h);
            osd_fb0_img_val = LX_MAKE_RES(res_w, res_h);
        }

        if (RET_OK == OS_ScanKernelCmdline("osd.fb.fb1=%s", opt))
        {
            sscanf(opt, "%dx%d", &res_w, &res_h);

            hw_ctx->b_support_fb1 = TRUE;
            osd_fb1_img_val = LX_MAKE_RES(res_w, res_h);
        }

        if (RET_OK == OS_ScanKernelCmdline("osd.fb.fbext=%s", opt))
        {
            sscanf(opt, "%dx%d@%d", &res_w, &res_h, &val);
            ext_render_sz_val = LX_MAKE_RES(res_w, res_h);
            osd_ext_render_swsync_hz_val = val;
        }
    }

    printk("+ fbdev. support_ext_frc=%d, path=%s.OSD. \n",
           hw_ctx->b_support_ext_frc, (osd_conn_val == LX_FBDEV_CONN_OSD_VIDEO_SEPARATE) ? "S" : "B");

    printk("+ fbdev. support_fb1=%d, support_ext_render=%d, osd_fb1_img=%dx%d\n",
           hw_ctx->b_support_fb1,
           hw_ctx->b_support_ext_render,
           LX_RES_GET_WIDTH(osd_fb1_img_val),
           LX_RES_GET_HEIGHT(osd_fb1_img_val));

    hw_ctx->sosd_disp.fb0_width  = LX_RES_GET_WIDTH(osd_fb0_img_val);
    hw_ctx->sosd_disp.fb0_height = LX_RES_GET_HEIGHT(osd_fb0_img_val);
    hw_ctx->sosd_disp.fb1_width  = LX_RES_GET_WIDTH(osd_fb1_img_val);
    hw_ctx->sosd_disp.fb1_height = LX_RES_GET_HEIGHT(osd_fb1_img_val);
    hw_ctx->sosd_disp.out_width  = LX_RES_GET_WIDTH(osd_disp_sosd_val); /* S.OSD size is fixed to 1920x1080 */
    hw_ctx->sosd_disp.out_height = LX_RES_GET_HEIGHT(osd_disp_sosd_val);
    hw_ctx->sosd_disp.pulse_timer_dly = osd_pulse_sosd_val;

    hw_ctx->bosd_disp.fb0_width  = LX_RES_GET_WIDTH(osd_fb0_img_val);
    hw_ctx->bosd_disp.fb0_height = LX_RES_GET_HEIGHT(osd_fb0_img_val);
    hw_ctx->bosd_disp.fb1_width  = LX_RES_GET_WIDTH(osd_fb1_img_val);
    hw_ctx->bosd_disp.fb1_height = LX_RES_GET_HEIGHT(osd_fb1_img_val);
    hw_ctx->bosd_disp.out_width  = LX_RES_GET_WIDTH(
                                       osd_disp_bosd_val); /* B.OSD size might be changed based on DTV config */
    hw_ctx->bosd_disp.out_height = LX_RES_GET_HEIGHT(osd_disp_bosd_val);
    hw_ctx->bosd_disp.pulse_timer_dly = osd_pulse_bosd_val;

#ifdef FBDEV_O24_SUPPORT_4KOSD

    /* raxis.lim (2019/05/21) -- we should support 4K OSD display !! */
    if (LX_RES_GET_WIDTH(osd_fb0_img_val) >= 2048)
    {
        hw_ctx->b_support_4kosd = TRUE;
    }

#endif

    if (osd_conn_val & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
    {
        hw_ctx->b_keep_hw_conn_type = TRUE;
        hw_ctx->hw_disp_width       = hw_ctx->bosd_disp.out_width;
        hw_ctx->hw_disp_height      = hw_ctx->bosd_disp.out_height;
        hw_ctx->hw_fb0_width        = hw_ctx->bosd_disp.fb0_width;
        hw_ctx->hw_fb0_height       = hw_ctx->bosd_disp.fb0_height;
        hw_ctx->hw_fb1_width        = hw_ctx->bosd_disp.fb1_width;
        hw_ctx->hw_fb1_height       = hw_ctx->bosd_disp.fb1_height;
    }
    else
    {
        hw_ctx->b_keep_hw_conn_type = FALSE;
        hw_ctx->hw_disp_width       = hw_ctx->sosd_disp.out_width;
        hw_ctx->hw_disp_height      = hw_ctx->sosd_disp.out_height;
        hw_ctx->hw_fb0_width        = hw_ctx->sosd_disp.fb0_width;
        hw_ctx->hw_fb0_height       = hw_ctx->sosd_disp.fb0_height;
        hw_ctx->hw_fb1_width        = hw_ctx->sosd_disp.fb1_width;
        hw_ctx->hw_fb1_height       = hw_ctx->sosd_disp.fb1_height;
    }

    hw_ctx->hw_osd0_owner           = LX_FBDEV_ID_OSD0;
    hw_ctx->hw_ext_render_width     = LX_RES_GET_WIDTH(ext_render_sz_val);
    hw_ctx->hw_ext_render_height    = LX_RES_GET_HEIGHT(ext_render_sz_val);
    hw_ctx->hw_ext_render_swsync_hz = osd_ext_render_swsync_hz_val;

    hw_ctx->hw_conn_type            = osd_conn_val;
    hw_ctx->hw_wa_flag              |= FBDEV_O24_HW_WA_1X_CSR_DISP_ON_BLEND_PATH;

    printk("osd hw path=%s, fb0=%dx%d fb1=%dx%d(%s) disp=%dx%d ext_render=%dx%d@%dHz(%s) wa_flag=0x%08x\n",
           (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? "B.OSD" : "S.OSD",
           hw_ctx->hw_fb0_width,
           hw_ctx->hw_fb0_height,
           hw_ctx->hw_fb1_width,
           hw_ctx->hw_fb1_height,
           (hw_ctx->b_support_fb1) ? "enabled" : "disabled",
           hw_ctx->hw_disp_width,
           hw_ctx->hw_disp_height,
           hw_ctx->hw_ext_render_width,
           hw_ctx->hw_ext_render_height,
           hw_ctx->hw_ext_render_swsync_hz,
           (hw_ctx->b_support_ext_render) ? "enabled" : "disabled",
           hw_ctx->hw_wa_flag);
}

// initialize OSD IP HW and register
int FBDEV_O24_InitHW(void)
{
    int ret = RET_ERROR;

    FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

#define IOREMAP_REGS(reg_base, reg_type, reg_val, shadow_val) \
    do { \
        if (NULL == reg_val) \
        { \
            reg_val = (reg_type*)ioremap(reg_base, sizeof(reg_type)); \
        } \
        FBDEV_CHECK_CODE(NULL == reg_val, goto func_exit, "can't ioremap reg=0x%x, type=%s\n", reg_base, #reg_type); \
        \
        if(NULL == shadow_val) \
        { \
            shadow_val = (reg_type*)kmalloc(sizeof(reg_type), GFP_KERNEL); \
        } \
        FBDEV_CHECK_CODE(NULL == shadow_val, goto func_exit, "can't alloc size=%d, type=%s\n", (int)sizeof(reg_type), #reg_type); \
    } while(0)

    IOREMAP_REGS(O24_CCO_TOP_CTRL_BASE, OSD_TOP_CTRL_O24_REG_T, g_osd_top_ctrl_o24_reg, g_osd_top_ctrl_o24_reg_shadow);
    IOREMAP_REGS(O24_CCO_TOP_CTRL1_BASE, OSD_TOP_CTRL1_O24_REG_T, g_osd_top_ctrl1_o24_reg, g_osd_top_ctrl1_o24_reg_shadow);

    IOREMAP_REGS(O24_CCO_BASE, OSD_O24_REG_T, g_osd_o24_reg, g_osd_o24_reg_shadow);
    IOREMAP_REGS(O24_CCO_SHP0_BASE, OSD_SHP_O24_REG_T, g_osd_shp_o24_reg, g_osd_shp_o24_reg_shadow);

    IOREMAP_REGS(O24_CCO_AFBC0_BASE, OSD_AFBC_O24_REG_T, g_osd_afbc_o24_reg[0], g_osd_afbc_o24_reg_shadow[0]);
    IOREMAP_REGS(O24_CCO_AFBC1_BASE, OSD_AFBC_O24_REG_T, g_osd_afbc_o24_reg[1], g_osd_afbc_o24_reg_shadow[1]);

    IOREMAP_REGS(O24_CCO_AFRC0_BASE, OSD_AFRC_O24_REG_T, g_osd_afrc_o24_reg[0], g_osd_afrc_o24_reg_shadow[0]);
    IOREMAP_REGS(O24_CCO_AFRC1_BASE, OSD_AFRC_O24_REG_T, g_osd_afrc_o24_reg[1], g_osd_afrc_o24_reg_shadow[1]);

    IOREMAP_REGS(O24_CCO_MIF0_BASE, OSD_MIF0_CTRL_O24_REG_T, g_osd_mif0_o24_reg, g_osd_mif0_o24_reg_shadow);
    IOREMAP_REGS(O24_CCO_MIF1_BASE, OSD_MIF1_CTRL_O24_REG_T, g_osd_mif1_o24_reg, g_osd_mif1_o24_reg_shadow);

    OSD_TOP_CTRL_RdFL(ctrl_spath);
    OSD_TOP_CTRL_RdFL(ctrl_dpath);
    OSD_TOP_CTRL_RdFL(ctrl_block);

    /* raxis.lim (2014/06/18)
     * CCO init param is too difficult to understand :(
     * ask woonghyun.kim if you have any question. he knows everything !!
     *
     * let's summarize all that I know
     * CCO_CTRL_BASE+0x08 controls osd pluse source selections
     * 0x5 : used for BLEND path (non-compressed)
     * 0x7 : used for SEP path   (non-compressed)
     */
    if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
    {
        OSD_TOP_CTRL_Wr(ctrl_auto_init, 0x55555555);
        OSD_TOP_CTRL_Wr(ctrl_intr_pulse, 0xCA876420);

        OSD_TOP_CTRL_Wr(ctrl_spath, 0x00000D80);
    }
    else /* SEP */
    {
        OSD_TOP_CTRL_Wr(ctrl_auto_init, 0x55555555);

        OSD_TOP_CTRL_Wr(ctrl_intr_pulse, 0xCAC76420);

        /* (2021/05/27)
         * O24 S.OSD sync is fetched from VSD PIP.
         * sync_gen_ctrl configuration is obsoleted.
         *
         * see http://clm.lge.com/issue/browse/SICDTV-9974
         *
         * CTRL_SPATH.ctrl_sosd_src_de = 0  <- vsd_cco_pip_de
         * CTRL_SPATH.ctrl_sosd_src_va = 0  <- vsd_cco_pip_va
         * CTRL_SPATH.ctrl_sosd_src_vs = 0  <- vsd_cco_pip_vs
         *
         * CTRL_DPATH.sel_osd_src_sosd = 3  <- PIP_SYNC_GEN_OUTPUT
         *
         * O20 대비 O24 의 큰 차이점이므로 주의할것
         */
        OSD_TOP_CTRL_Wr(ctrl_spath, 0x00000D80);

        OSD_TOP_CTRL_Wr01(ctrl_dpath, sel_osd_src_sosd, 0x3);
    }

    /* raxis.lim (2016/03/28) -- ctrl_intr_pulse, ctrl_dpath, ctrl_spath is set by HW default value
     * raxis.lim (2016/10/05) -- keep AFBC status becuase boot loader can display AFBC logo image
     * raxis.lim (2019/08/06) -- DO NOT full value to ctrl_dpath. refer to http://clm.lge.com/issue/browse/AVTASK-386?focusedCommentId=1964037&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-1964037
     * raxis.lim (2019/10/15) -- setup fb(1) based on hw_ctx->b_support_ext_render
     */

    if (FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0))
    {
        OSD_TOP_CTRL_Wr01(ctrl_dpath, osd0_afbc_en, 0x1);
        OSD_TOP_CTRL_Wr01(ctrl_block, reg_afbc_afrc_sel, 0x0);
    }
    else
    {
        OSD_TOP_CTRL_Wr01(ctrl_dpath, osd0_afbc_en, 0x0);
    }

    if (FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFBC, LX_FBDEV_ID_OSD1) &&
            hw_ctx->b_support_ext_render == FALSE)
    {
        OSD_TOP_CTRL_Wr01(ctrl_dpath, osd1_afbc_en, 0x1);
        OSD_TOP_CTRL_Wr01(ctrl_block, reg_afbc_afrc_sel, 0x0);
    }
    else
    {
        OSD_TOP_CTRL_Wr01(ctrl_dpath, osd1_afbc_en, 0x0);
    }

    if (FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFRC, LX_FBDEV_ID_OSD0))
    {
        OSD_TOP_CTRL_Wr01(ctrl_dpath, osd0_afbc_en, 0x1);
        OSD_TOP_CTRL_Wr01(ctrl_block, reg_afbc_afrc_sel, 0x1);
    }
    else
    {
        OSD_TOP_CTRL_Wr01(ctrl_dpath, osd0_afbc_en, 0x0);
    }

    if (FBDEV_O24_CMN_GetHWStatus(FBDEV_O24_HW_STATUS_AFRC, LX_FBDEV_ID_OSD1) &&
            hw_ctx->b_support_ext_render == FALSE)
    {
        OSD_TOP_CTRL_Wr01(ctrl_dpath, osd1_afbc_en, 0x1);
        OSD_TOP_CTRL_Wr01(ctrl_block, reg_afbc_afrc_sel, 0x1);
    }
    else
    {
        OSD_TOP_CTRL_Wr01(ctrl_dpath, osd1_afbc_en, 0x0);
    }


    OSD_TOP_CTRL_WrFL(ctrl_auto_init);
    OSD_TOP_CTRL_WrFL(ctrl_intr_pulse);

    OSD_TOP_CTRL_WrFL(ctrl_block);
    OSD_TOP_CTRL_WrFL(ctrl_dpath);
    OSD_TOP_CTRL_WrFL(ctrl_spath);

    if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
    {
        // add somthing if necessary
    }
    else
    {
        // add somthing if necessary
    }

    if (FBDEV_O24_CMN_IsUHDDispMode())
    {
        FBDEV_WARN("++ UHD mode : pic_init_timer config\n");

        /* raxis.lim (2019/05/23)
         * OSD_IMAGE1 (E-Stremaer) 에서는 pic_init 0 값 설정 중요함. (SICDTV-6809 참조)
         * 만약 0xa000 값을 사용하게 되면, E-Streamer OSD 의 오프셋이 틀어지거나, OSD 가 흐름.
         *
         * 결론은 use the default configuration 0x7000_0000
         */
        OSD_TOP_CTRL_Wr(pic_init_g0_timer, 0x70000000);
        OSD_TOP_CTRL_Wr(pic_init_g1_timer, 0x70000000);
        OSD_TOP_CTRL_Wr(pic_init_g2_timer, 0x70000000);
        OSD_TOP_CTRL_Wr(pic_init_g3_timer, 0x70000000);
        OSD_TOP_CTRL_Wr(pic_init_g4_timer, 0x70000000);
        OSD_TOP_CTRL_Wr(pic_init_g5_timer, 0x70000000);
        OSD_TOP_CTRL_Wr(pic_init_g6_timer, 0x70000000);
        OSD_TOP_CTRL_Wr(pic_init_g7_timer, 0x70000000);

        OSD_TOP_CTRL_WrFL(pic_init_g0_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g1_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g2_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g3_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g4_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g5_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g6_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g7_timer);
    }
    else
    {
        FBDEV_WARN("++ non-UHD mode : pic_init_timer config (not tested yet)\n");
        OSD_TOP_CTRL_Wr(pic_init_g0_timer, 0x00000000);
        OSD_TOP_CTRL_Wr(pic_init_g1_timer, 0x00000000);
        OSD_TOP_CTRL_Wr(pic_init_g2_timer, 0x00000000);
        OSD_TOP_CTRL_Wr(pic_init_g3_timer, 0x00000000);
        OSD_TOP_CTRL_Wr(pic_init_g4_timer, 0x00000000);
        OSD_TOP_CTRL_Wr(pic_init_g5_timer, 0x00000000);
        OSD_TOP_CTRL_Wr(pic_init_g6_timer, 0x00000000);
        OSD_TOP_CTRL_Wr(pic_init_g7_timer, 0x00000000);

        OSD_TOP_CTRL_WrFL(pic_init_g0_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g1_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g2_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g3_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g4_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g5_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g6_timer);
        OSD_TOP_CTRL_WrFL(pic_init_g7_timer);
    }

    /* configure MIF to show OSD with ARGB color
     *
     * raxis.lim (2019/05/24)
     *
     * wr 0XC9010C20 0x400000FB     # R_OSD0_MB_REQ.req_msk_f_on=0 (for UI)
     * wr 0XC9010C60 0x400000FB     # R_CSR0_MB_REQ.req_msk_f_on=0 (for CURSOR)
     * wr 0XC9012820 0x400000FB     # R_OSD1_MB_REQ.req_msk_f_on=0 (for E-Streamer)
     *
     * MIF1req_msk_f_on=1 설정시 IMAGE1 ARGB 출력시 화면이 보이지 않음. (SICDTV-6809 참조)
     */
    OSD_MIF0_CTRL_Wr(r_osd0_mb_req, 0x400000FB);
    OSD_MIF0_CTRL_Wr(r_csr0_mb_req, 0x400000FA);
    OSD_MIF1_CTRL_Wr(r_osd1_mb_req, 0x400000FB);

    OSD_MIF0_CTRL_WrFL(r_osd0_mb_req);
    OSD_MIF0_CTRL_WrFL(r_csr0_mb_req);
    OSD_MIF1_CTRL_WrFL(r_osd1_mb_req);

    // (2021/11/01) O24-to-F22 OSD change flag configuration
    //
    // osd_change_flag 생성 방법을 재정리함.
    // ui 와 cursor 의 framebuffer 주소값은 사용하되, afbc framebuffer 는 삭제함
    // 삭제 이유는 osd off 시에 afbc decoder 가 같이 꺼지면서 afbc_pic_init 이 멈추며, 이런 이유로
    // F22 로 change flag 가 전송되지 않음
    //
    // 항상 afbc framebuffer 와 (normal) framebuffer 를 설정하기 때문에, afbc 기반의 change flag 삭제 가능
    //
    // ctrl_osd_change.reg_auto_reset_cnt = 0xff (default)
    //                 reg_use_osd4_en = 1 (default)
    //                 reg_use_afbc_en = 0 (changed)
    //                 reg_use_osd0_en = 1 (default)
    //
    // see http://clm.lge.com/issue/browse/SICDTV-10362
    //
    OSD_TOP_CTRL1_Wr01(ctrl_osd_change, reg_auto_reset_cnt, 0xff);
    OSD_TOP_CTRL1_Wr01(ctrl_osd_change, reg_use_osd0_en, 0x1);
    OSD_TOP_CTRL1_Wr01(ctrl_osd_change, reg_use_afbc_en, 0x0);
    OSD_TOP_CTRL1_Wr01(ctrl_osd_change, reg_use_osd4_en, 0x1);
    OSD_TOP_CTRL1_WrFL(ctrl_osd_change);


    /* HW revision specific initialization */
    FBDEV_O24_InitOSDZOrder();

    FBDEV_O24_CMN_InitHW();

    /* refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT */
    if (!(hw_ctx->hw_wa_flag & FBDEV_O24_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR))
    {
        if (hw_ctx->user_initcall_ctrl.ready)
        {
            FBDEV_NOTI("++ PIC_INIT ++ (NORMAL)\n");
            OSD_TOP_CTRL_RdFL(pic_init);
            OSD_TOP_CTRL_Wr01(pic_init, g0_auto_init, 0x1);
            OSD_TOP_CTRL_Wr01(pic_init, g1_auto_init, 0x1);
            OSD_TOP_CTRL_Wr01(pic_init, g4_auto_init, 0x1);
            OSD_TOP_CTRL_WrFL(pic_init);
        }
    }

    /* migrate LG Logo Image at kdriver initialization */
    FBDEV_O24_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_KEEP);

    ret = RET_OK; /* all work done */
func_exit:
    return ret;
}

int FBDEV_O24_ShutdownHW(void)
{
    /* do nothing */
    return RET_OK;
}

/*========================================================================================
    Implementation group (legacy)
========================================================================================*/
void FBDEV_O24_InitOSDZOrder(void)
{
    /* do nothing */
}

int FBDEV_O24_SetZList(LX_FBDEV_ZLIST_T* zList)
{

    return RET_OK;
}

int FBDEV_O24_GetZList(LX_FBDEV_ZLIST_T* zList)
{
    zList->order[0] = 0;
    zList->order[1] = 1;
    zList->order[2] = 2;

    return RET_OK;
}

int FBDEV_O24_WriteOSDEndian(int fb_dev_id, ENDIAN_INFORM_T* endian)
{
    return RET_OK;
}

int FBDEV_O24_WriteOSDCSC(int layer, CSC_INFORM_T* csc)
{
    return RET_OK;
}

