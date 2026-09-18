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

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/workqueue.h>        /**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_o26.h"

#ifdef INCLUDE_KDRV_SYS
#include "../sys/ctop_regs.h"
#endif

#ifdef INCLUDE_KDRV_OVI
#include "ovi_kapi.h"
#endif

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
void FBDEV_O26_InitHWCtx(FBDEV_HW_CTX_T* hal_obj);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern FBDEV_PLT_HW_FUNC_T g_fbdev_o26_cmn_hw_func;

/*----------------------------------------------------------------------------------------
    global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_O26_InitOSDZOrder(void);
LX_FBDEV_CFG_T* FBDEV_O26_GetCfg(void);

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
volatile AFBC_O26_REG_T* g_afbc_o26_reg[MAX_AFBC] = { NULL, NULL, NULL, NULL };
AFBC_O26_REG_T* g_afbc_o26_reg_shadow[MAX_AFBC] = { NULL, NULL, NULL, NULL };

volatile AFRC_O26_REG_T* g_afrc_o26_reg[MAX_AFRC] = { NULL, NULL, NULL, NULL };
AFRC_O26_REG_T* g_afrc_o26_reg_shadow[MAX_AFRC] = { NULL, NULL, NULL, NULL };

volatile OSD_PRE_O26_REG_T* g_osd_pre_o26_reg = NULL;
OSD_PRE_O26_REG_T* g_osd_pre_o26_reg_shadow = NULL;

volatile GLB_O26_REG_T* g_glb_o26_reg = NULL;
GLB_O26_REG_T* g_glb_o26_reg_shadow = NULL;

volatile OSD_O26_REG_T* g_osd_o26_reg = NULL;
OSD_O26_REG_T* g_osd_o26_reg_shadow = NULL;

volatile CCO_CTRL_O26_REG_T* g_cco_ctrl_o26_reg = NULL;
CCO_CTRL_O26_REG_T* g_cco_ctrl_o26_reg_shadow = NULL;

volatile CCO_CTRL1_O26_REG_T* g_cco_ctrl1_o26_reg = NULL;
CCO_CTRL1_O26_REG_T* g_cco_ctrl1_o26_reg_shadow = NULL;

volatile GSC_CTRL_O26_REG_T* g_gsc_ctrl_o26_reg = NULL;
GSC_CTRL_O26_REG_T* g_gsc_ctrl_o26_reg_shadow = NULL;

static FBDEV_O26_HW_CTX_T g_fbdev_o26_hw_ctx;         /* O20 OSD H/W ctrl */

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_O26_AutoDetectOSDHWValue(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static  FBDEV_HW_CTX_T  _g_fbdev_hw_ctx =
{
    .GetCfg             = FBDEV_O26_GetCfg,
    .RunSuspend         = FBDEV_O26_CMN_RunSuspend,
    .RunResume          = FBDEV_O26_CMN_RunResume,

    .InitHW             = FBDEV_O26_InitHW,
    .ShutdownHW         = FBDEV_O26_ShutdownHW,
    .ExecHWCommand      = FBDEV_O26_CMN_ExecHWCommand,

    .SetOSDEnable       = FBDEV_O26_CMN_SetOSDEnable,
    .GetOSDEnable       = FBDEV_O26_CMN_GetOSDEnable,

    .InitOSDLayer       = FBDEV_O26_CMN_InitOSDLayer,
    .WriteOSDHeader     = FBDEV_O26_CMN_WriteOSDHeader,

    .GetZList           = FBDEV_O26_GetZList,
    .SetZList           = FBDEV_O26_SetZList,

    .WriteOSDEndian     = FBDEV_O26_WriteOSDEndian,
    .WriteOSDCSC        = FBDEV_O26_WriteOSDCSC,

    .GetInterruptStatus = FBDEV_O26_CMN_GetInterruptStatus,
    .SetInterruptClear  = FBDEV_O26_CMN_SetInterruptClear,
    .SetInterruptEnable = FBDEV_O26_CMN_SetInterruptEnable,

    .SetViewCtrl        = FBDEV_O26_CMN_SetViewCtrl,
    .SetConnCtrl        = FBDEV_O26_CMN_SetConnCtrl,

    .CreateProc         = FBDEV_O26_CreateProc,
    .ProcHandler        = FBDEV_O26_CMN_ProcHandler,
};

/*========================================================================================
    Implementation Group
========================================================================================*/
// get O20 specific configuration. return LX_FBDEV_CFG_T
LX_FBDEV_CFG_T*   FBDEV_O26_GetCfg(void)
{
    return NULL;
}

// initialize O20 specific HW context variables.
// this function is called before at O26 configure stage NOT at HW initialization stage.
void    FBDEV_O26_InitHWCtx(FBDEV_HW_CTX_T* hal_obj)
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
    memcpy(&g_fbdev_o26_hw_ctx.func, &g_fbdev_o26_cmn_hw_func, sizeof(FBDEV_PLT_HW_FUNC_T));

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        g_fbdev_o26_hw_ctx.conn_ctrl[i].conn_type = g_fbdev_o26_hw_ctx.hw_conn_type;
        g_fbdev_o26_hw_ctx.fbc_ctrl[i].status = FBDEV_O26_FBC_STATUS_NONE;
    }

    g_fbdev_o26_hw_ctx.mirror_ctrl.status = FBDEV_O26_MIRROR_NONE;

    memset(&g_fbdev_o26_hw_ctx.ext_render_ctrl, 0x0, sizeof(FBDEV_PLT_EXT_RENDER_CTRL_T));

    /* auto detect the default OSD connection and display size etc */
    FBDEV_O26_AutoDetectOSDHWValue();

    /* initialize hal object
     * after this function, all fbdev kdriver can get g_fbdev_o26_hw_ctx via g_fbdev_hw_ctx->chip_priv_ctx
     */
    memcpy(hal_obj, &_g_fbdev_hw_ctx, sizeof(FBDEV_HW_CTX_T));

    hal_obj->chip_priv_ctx = &g_fbdev_o26_hw_ctx;
}

// detect the default OSD connection
// this function will return the default(best) OSD connection setup based on SW, HW info
static void FBDEV_O26_AutoDetectOSDHWValue(void)
{
#if 0 //def BUILD_FEATURE_fpga
    UINT32  osd_fb0_img_val     = LX_MAKE_RES(3840, 2160);
#else
    UINT32  osd_fb0_img_val     = LX_MAKE_RES(1920, 1080);      /* defualt fb0 image. default 2K resolution */
#endif
    UINT32  osd_fb1_img_val     = LX_MAKE_RES(1024, 4320);      /* defualt fb1 image for 8KTV, default size=1K*4K */
    UINT32  osd_disp_bosd_val   = LX_MAKE_RES(3840, 2160);      /* default 4K resolution */
    UINT32  osd_disp_sosd_val   = LX_MAKE_RES(3840, 2160);      /* default 4K resolution */
    UINT32  osd_conn_val        = LX_FBDEV_CONN_OSD_VIDEO_BLEND;/* default path */

    FIXME_NOTE("O26 FPGA 값을 읽어보니 0x1000 이다. 원래 기존칩은 0xA000 이었다")
    UINT32  osd_pulse_bosd_val  = 0x1000;                       /* default pulse timer delay. default 0x1000 */

    UINT32  ext_render_sz_val   = LX_MAKE_RES(1920, 2160);      /* (960*2) x (4320/2) */
    UINT32  osd_ext_render_swsync_hz_val = 20;                  /* default 8k ext swsync interval. default 20Hz=30.00 ms */

    FBDEV_O26_HW_CTX_T* hw_ctx = &g_fbdev_o26_hw_ctx;

    /* make the initial HW WA config */
    hw_ctx->hw_wa_flag = 0x0;

    /* get HW display option from both hwopts and OVI */
    hw_ctx->b_support_ext_frc = 0;
    hw_ctx->b_support_ext_render = 0;

    /* support fb1 (E-Streamer) by default */
    hw_ctx->b_support_fb1 = 1;

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
        osd_fb1_img_val   = LX_MAKE_RES(768, 2160);
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

    /* scan test options for internal debug use only. override the default configuration */
    // N/A

    // select osd path and configure external render based on both support_ext_frc and support_fb1 flag
    osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_BLEND;

    hw_ctx->b_support_ext_render = 0;
    ext_render_sz_val = LX_MAKE_RES(16, 16); /* make size as small as possible */

    // internal debug use only. override the auto configured values
    {
        char    opt[32];
        UINT32  res_w, res_h;

        if (RET_OK == OS_ScanKernelCmdline("osd.disp.bosd=%s", opt))
        {
            sscanf(opt, "%dx%d", &res_w, &res_h);
            osd_disp_bosd_val = LX_MAKE_RES(res_w, res_h);
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
    }

    printk("+ fbdev. support_fb1=%d, support_ext_render=%d, osd_fb1_img=%dx%d\n",
           hw_ctx->b_support_fb1,
           hw_ctx->b_support_ext_render,
           LX_RES_GET_WIDTH(osd_fb1_img_val),
           LX_RES_GET_HEIGHT(osd_fb1_img_val));

    hw_ctx->bosd_disp.fb0_width  = LX_RES_GET_WIDTH(osd_fb0_img_val);
    hw_ctx->bosd_disp.fb0_height = LX_RES_GET_HEIGHT(osd_fb0_img_val);
    hw_ctx->bosd_disp.fb1_width  = LX_RES_GET_WIDTH(osd_fb1_img_val);
    hw_ctx->bosd_disp.fb1_height = LX_RES_GET_HEIGHT(osd_fb1_img_val);
    hw_ctx->bosd_disp.out_width  = LX_RES_GET_WIDTH(osd_disp_bosd_val);
    hw_ctx->bosd_disp.out_height = LX_RES_GET_HEIGHT(osd_disp_bosd_val);
    hw_ctx->bosd_disp.pulse_timer_dly = osd_pulse_bosd_val;

#ifdef FBDEV_O26_SUPPORT_4KOSD

    /* raxis.lim (2019/05/21) -- we should support 4K OSD display !! */
    if (LX_RES_GET_WIDTH(osd_fb0_img_val) >= 2048)
    {
        hw_ctx->b_support_4kosd = TRUE;
    }

#endif

    // B.OSD fixed
    hw_ctx->b_keep_hw_conn_type = TRUE;
    hw_ctx->hw_disp_width       = hw_ctx->bosd_disp.out_width;
    hw_ctx->hw_disp_height      = hw_ctx->bosd_disp.out_height;
    hw_ctx->hw_fb0_width        = hw_ctx->bosd_disp.fb0_width;
    hw_ctx->hw_fb0_height       = hw_ctx->bosd_disp.fb0_height;
    hw_ctx->hw_fb1_width        = hw_ctx->bosd_disp.fb1_width;
    hw_ctx->hw_fb1_height       = hw_ctx->bosd_disp.fb1_height;

    hw_ctx->hw_osd0_owner           = LX_FBDEV_ID_OSD0;
    hw_ctx->hw_ext_render_width     = LX_RES_GET_WIDTH(ext_render_sz_val);
    hw_ctx->hw_ext_render_height    = LX_RES_GET_HEIGHT(ext_render_sz_val);
    hw_ctx->hw_ext_render_swsync_hz = osd_ext_render_swsync_hz_val;

    hw_ctx->hw_conn_type            = osd_conn_val;
    //hw_ctx->hw_wa_flag              |= FBDEV_O26_HW_WA_1X_CSR_DISP_ON_BLEND_PATH;

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
int FBDEV_O26_InitHW(void)
{
    int i;
    int ret = RET_ERROR;

#define IOREMAP_REGS(reg_base, reg_type, reg_val, shadow_val) \
    do { \
        if (NULL == reg_val) \
        { \
            reg_val = (reg_type*)ioremap(reg_base, sizeof(reg_type)); \
        } \
        FBDEV_CHECK_CODE(NULL == reg_val, goto func_exit, "can't ioremap value=%s, reg=0x%x, type=%s\n", #reg_val, reg_base, #reg_type); \
        \
        if(NULL == shadow_val) \
        { \
            shadow_val = (reg_type*)kmalloc(sizeof(reg_type), GFP_KERNEL); \
        } \
        FBDEV_CHECK_CODE(NULL == shadow_val, goto func_exit, "can't alloc value=%s, size=%d, type=%s\n", #shadow_val, (int)sizeof(reg_type), #reg_type); \
    } while(0)

    for (i = 0; i < MAX_AFBC; i++)
    {
        IOREMAP_REGS(AFBC_REG_BASE(i), AFBC_O26_REG_T, g_afbc_o26_reg[i], g_afbc_o26_reg_shadow[i]);
    }

    for (i = 0; i < MAX_AFRC; i++)
    {
        IOREMAP_REGS(AFRC_REG_BASE(i), AFRC_O26_REG_T, g_afrc_o26_reg[i], g_afrc_o26_reg_shadow[i]);
    }

    IOREMAP_REGS(OSD_PRE_REG_BASE, OSD_PRE_O26_REG_T, g_osd_pre_o26_reg, g_osd_pre_o26_reg_shadow);
    IOREMAP_REGS(GLB_REG_BASE, GLB_O26_REG_T, g_glb_o26_reg, g_glb_o26_reg_shadow);
    IOREMAP_REGS(OSD_REG_BASE, OSD_O26_REG_T, g_osd_o26_reg, g_osd_o26_reg_shadow);

    IOREMAP_REGS(CCO_CTRL_REG_BASE, CCO_CTRL_O26_REG_T, g_cco_ctrl_o26_reg, g_cco_ctrl_o26_reg_shadow);
    IOREMAP_REGS(CCO_CTRL1_REG_BASE, CCO_CTRL1_O26_REG_T, g_cco_ctrl1_o26_reg, g_cco_ctrl1_o26_reg_shadow);
    IOREMAP_REGS(GSC_CTRL_REG_BASE, GSC_CTRL_O26_REG_T, g_gsc_ctrl_o26_reg, g_gsc_ctrl_o26_reg_shadow);

    FIXME_NOTE("pic init timer, sync gen 등의 모든 설정은 FBDEV_O26_CMN_InitHW() 함수로 이동함")

    /* HW revision specific initialization */
    FBDEV_O26_InitOSDZOrder();

    FBDEV_O26_CMN_InitHW();

    // (2025/05/13) boot 에서 설정한 내용, 즉 mixer mute 혹은 boot logo 의 유지가 필요함
    // migrate LG Logo image at kdriver initialization
    FBDEV_O26_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_KEEP);

    ret = RET_OK; /* all work done */
func_exit:
    return ret;
}

int FBDEV_O26_ShutdownHW(void)
{
    /* do nothing */
    return RET_OK;
}

/*========================================================================================
    Implementation group (legacy)
========================================================================================*/
void FBDEV_O26_InitOSDZOrder(void)
{
    /* do nothing */
}

int FBDEV_O26_SetZList(LX_FBDEV_ZLIST_T* zList)
{
    PARAM_UNUSED(zList);

    return RET_OK;
}

int FBDEV_O26_GetZList(LX_FBDEV_ZLIST_T* zList)
{
    zList->order[0] = 0;
    zList->order[1] = 1;
    zList->order[2] = 2;

    return RET_OK;
}

int FBDEV_O26_WriteOSDEndian(int fb_dev_id, ENDIAN_INFORM_T* endian)
{
    PARAM_UNUSED(fb_dev_id);
    PARAM_UNUSED(endian);
    return RET_OK;
}

int FBDEV_O26_WriteOSDCSC(int layer, CSC_INFORM_T* csc)
{
    PARAM_UNUSED(layer);
    PARAM_UNUSED(csc);
    return RET_OK;
}

