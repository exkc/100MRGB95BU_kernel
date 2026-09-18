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
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_m23.h"
#include "osd_reg_m23.h"
#include "osd_afbc_reg_m23.h"
#include "osd_top_reg_m23.h"
#include "osd_mif_reg_m23.h"
#include <linux/workqueue.h>    /**< For working queue */
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
#ifdef INCLUDE_KDRV_OVI
extern int OVI_HAL_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T* pstParams);
#endif

void FBDEV_M23_InitHWCtx(FBDEV_HW_CTX_T* hal_obj);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern FBDEV_M23_HW_FUNC_T g_fbdev_m23_cmn_hw_func;    /* O20 HW common func */

/*----------------------------------------------------------------------------------------
    global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_M23_InitOSDZOrder(void);
LX_FBDEV_CFG_T* FBDEV_M23_GetCfg(void);

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
volatile OSD_M23_REG_T* g_osd_m23_reg = NULL;
OSD_M23_REG_T* g_osd_m23_reg_shadow = NULL;

volatile OSD_AFBC_M23_REG_T* g_osd_afbc_m23_reg[1] = {NULL};
OSD_AFBC_M23_REG_T* g_osd_afbc_m23_reg_shadow[1] = {NULL};

volatile OSD_MIF_M23_REG_T* g_osd_mif_m23_reg[1] = {NULL};
OSD_MIF_M23_REG_T* g_osd_mif_m23_reg_shadow[1] = {NULL};

volatile OSD_TOP_M23_REG_T* g_osd_top_m23_reg = NULL;
OSD_TOP_M23_REG_T* g_osd_top_m23_reg_shadow = NULL;

static FBDEV_M23_HW_CTX_T g_fbdev_m23_hw_ctx;         /* O20 OSD H/W ctrl */

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_M23_AutoDetectOSDHWValue(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static  FBDEV_HW_CTX_T  _g_fbdev_hw_ctx =
{
    .GetCfg             = FBDEV_M23_GetCfg,
    .RunSuspend         = FBDEV_M23_CMN_RunSuspend,
    .RunResume          = FBDEV_M23_CMN_RunResume,

    .InitHW             = FBDEV_M23_InitHW,
    .ShutdownHW         = FBDEV_M23_ShutdownHW,
    .ExecHWCommand      = FBDEV_M23_CMN_ExecHWCommand,

    .SetOSDEnable       = FBDEV_M23_CMN_SetOSDEnable,
    .GetOSDEnable       = FBDEV_M23_CMN_GetOSDEnable,

    .InitOSDLayer       = FBDEV_M23_CMN_InitOSDLayer,
    .WriteOSDHeader     = FBDEV_M23_CMN_WriteOSDHeader,

    .GetZList           = FBDEV_M23_GetZList,
    .SetZList           = FBDEV_M23_SetZList,

    .WriteOSDEndian     = FBDEV_M23_WriteOSDEndian,
    .WriteOSDCSC        = FBDEV_M23_WriteOSDCSC,

    .GetInterruptStatus = FBDEV_M23_CMN_GetInterruptStatus,
    .SetInterruptClear  = FBDEV_M23_CMN_SetInterruptClear,
    .SetInterruptEnable = FBDEV_M23_CMN_SetInterruptEnable,

    .SetViewCtrl        = FBDEV_M23_CMN_SetViewCtrl,
    .SetConnCtrl        = FBDEV_M23_CMN_SetConnCtrl,

    .CreateProc         = FBDEV_M23_CreateProc,
    .ProcHandler        = FBDEV_M23_CMN_ProcHandler,
};

/*========================================================================================
    Implementation Group
========================================================================================*/
// get O20 specific configuration. return LX_FBDEV_CFG_T
LX_FBDEV_CFG_T*   FBDEV_M23_GetCfg(void)
{
    return NULL;
}

// initialize O20 specific HW context variables.
// this function is called before at M23 configure stage NOT at HW initialization stage.
void    FBDEV_M23_InitHWCtx(FBDEV_HW_CTX_T* hal_obj)
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
    memcpy(&g_fbdev_m23_hw_ctx.func, &g_fbdev_m23_cmn_hw_func, sizeof(FBDEV_M23_HW_FUNC_T));

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        g_fbdev_m23_hw_ctx.conn_ctrl[i].conn_type = g_fbdev_m23_hw_ctx.hw_conn_type;
        g_fbdev_m23_hw_ctx.fbc_ctrl[i].status     = FBDEV_M23_FBC_STATUS_NONE;
    }

    g_fbdev_m23_hw_ctx.mirror_ctrl.status = FBDEV_M23_MIRROR_NONE;

    memset(&g_fbdev_m23_hw_ctx.ext_render_ctrl, 0x0, sizeof(FBDEV_M23_EXT_RENDER_CTRL_T));

    /* auto detect the default OSD connection and display size etc */
    FBDEV_M23_AutoDetectOSDHWValue();

    /* initialize hal object
     * after this function, all fbdev kdriver can get g_fbdev_m23_hw_ctx via g_fbdev_hw_ctx->chip_priv_ctx
     */
    memcpy(hal_obj, &_g_fbdev_hw_ctx, sizeof(FBDEV_HW_CTX_T));
    hal_obj->chip_priv_ctx = &g_fbdev_m23_hw_ctx;
}

// detect the default OSD connection
// this function will return the default(best) OSD connection setup based on SW, HW info
static void FBDEV_M23_AutoDetectOSDHWValue(void)
{
    UINT32  osd_fb0_img_val   = LX_MAKE_RES(1920, 1080); /* defualt fb0 image. default 2K resolution */
    UINT32  osd_fb1_img_val   = LX_MAKE_RES(512, 2160); /* defualt fb1 image for 8KTV, default size=1K*4K */
    UINT32  osd_disp_bosd_val = LX_MAKE_RES(3840, 2160); /* default 4K resolution */
    UINT32  osd_conn_val      = LX_FBDEV_CONN_OSD_VIDEO_BLEND;/* default path */
    FBDEV_M23_TODO("FPGA 에서 0x4000 인데, 확인필요")
    UINT32  osd_pulse_bosd_val = 0xA000; /* default pulse timer delay. default 0xA000. see SICDTV-7971 */

    UINT32  osd_ext_render_swsync_hz_val = 15; /* default 8k ext swsync interval. default 15Hz=66.666 ms */

    FBDEV_M23_HW_CTX_T* hw_ctx = &g_fbdev_m23_hw_ctx;

    /* make the initial HW WA config */
    hw_ctx->hw_wa_flag = 0x0;
    hw_ctx->b_support_ext_frc = 0;
    hw_ctx->b_support_4kosd = FALSE;

    /* read HW configuration by parsing some kernel parameters */
    // HD 모델에서의 default OSD 해상도는 panel 에 맞추도록 한다.
    // 실제 동작중에는 1280x720 설정에 따라 이 값이 override 되도록 지원한다.
    // HD 모델에서 E-Streamer 는 해상도가 애매하여, 일단 적당한 값으로 조치만 하도록 함.
    if (lx_chip_plt() & LX_CHIP_PLT_HD)
    {
        osd_disp_bosd_val = LX_MAKE_RES(1366, 768);
        osd_fb0_img_val   = LX_MAKE_RES(1366, 768);
        osd_fb1_img_val   = LX_MAKE_RES(192, 768);
    }

    if (lx_board_opt() & LX_BOARD_OPT_HD_GRAPHIC)
    {
        osd_fb0_img_val = LX_MAKE_RES(1280, 720);
    }

    /* read HW configuration by querying OVI */
#if 0 // TBD #ifdef INCLUDE_KDRV_OVI
    {
        LX_OVI_HW_DISPLAY_INFO_T disp_info;

        if (OVI_HAL_GetHWDisplayOption(&disp_info) == RET_OK)
        {
            if (disp_info.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F20)
            {
                printk("<!> fbdev EXT_FRC(F22) detected from OVI\n");
                hw_ctx->b_support_ext_frc = 1;
            }
            else if (disp_info.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
            {
                printk("+ FHD display support\n");
                osd_disp_bosd_val = LX_MAKE_RES(1920, 1080);
                osd_fb1_img_val = LX_MAKE_RES(256, 1080);
            }
        }
    }
#endif

    /* scan test options for internal debug use only. override the default configuration */
    {
        // TBD
    }

    // select osd path and configure external render based on both support_ext_frc and support_fb1 flag
    // TBD

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

        // TBD
    }

    printk("+ osd_fb1_img=%dx%d\n",
           LX_RES_GET_WIDTH(osd_fb1_img_val), LX_RES_GET_HEIGHT(osd_fb1_img_val));

    hw_ctx->bosd_disp.fb0_width  = LX_RES_GET_WIDTH(osd_fb0_img_val);
    hw_ctx->bosd_disp.fb0_height = LX_RES_GET_HEIGHT(osd_fb0_img_val);
    hw_ctx->bosd_disp.fb1_width  = LX_RES_GET_WIDTH(osd_fb1_img_val);
    hw_ctx->bosd_disp.fb1_height = LX_RES_GET_HEIGHT(osd_fb1_img_val);
    hw_ctx->bosd_disp.out_width  = LX_RES_GET_WIDTH(osd_disp_bosd_val);
    hw_ctx->bosd_disp.out_height = LX_RES_GET_HEIGHT(osd_disp_bosd_val);
    hw_ctx->bosd_disp.pulse_timer_dly = osd_pulse_bosd_val;

#ifdef FBDEV_M23_2X_CURSOR_ON_BLEND_PATH
    hw_ctx->bosd_disp.b_2x_cursor_disp = TRUE;
#else
    hw_ctx->bosd_disp.b_2x_cursor_disp = FALSE;
#endif

    hw_ctx->b_keep_hw_conn_type = TRUE;
    hw_ctx->hw_disp_width       = hw_ctx->bosd_disp.out_width;
    hw_ctx->hw_disp_height      = hw_ctx->bosd_disp.out_height;
    hw_ctx->hw_fb0_width        = hw_ctx->bosd_disp.fb0_width;
    hw_ctx->hw_fb0_height       = hw_ctx->bosd_disp.fb0_height;
    hw_ctx->hw_fb1_width        = hw_ctx->bosd_disp.fb1_width;
    hw_ctx->hw_fb1_height       = hw_ctx->bosd_disp.fb1_height;

    hw_ctx->hw_osd0_owner       = LX_FBDEV_ID_OSD0;
    hw_ctx->hw_ext_render_swsync_hz = osd_ext_render_swsync_hz_val;

    hw_ctx->hw_conn_type    = osd_conn_val;
    hw_ctx->hw_wa_flag      |= FBDEV_M23_HW_WA_1X_CSR_DISP_ON_BLEND_PATH;

    printk("osd hw path=%s, fb0=%dx%d fb1=%dx%d(%s) disp=%dx%d wa_flag=0x%08x\n",
           (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? "B.OSD" : "S.OSD",
           hw_ctx->hw_fb0_width,
           hw_ctx->hw_fb0_height,
           hw_ctx->hw_fb1_width,
           hw_ctx->hw_fb1_height,
           (hw_ctx->b_support_fb1) ? "enabled" : "disabled",
           hw_ctx->hw_disp_width,
           hw_ctx->hw_disp_height,
           hw_ctx->hw_wa_flag);
}

// initialize OSD IP HW and register
int FBDEV_M23_InitHW(void)
{
    int ret = RET_ERROR;

    FBDEV_M23_HW_CTX_T* hw_ctx = FBDEV_M23_GET_HW_CTX();

    /* ioremap TOP regs */
    if (NULL == g_osd_top_m23_reg)
    {
        g_osd_top_m23_reg = (OSD_TOP_M23_REG_T*)ioremap(M23_CCO_TOP_CTRL_BASE, sizeof(OSD_TOP_M23_REG_T));
    }

    FBDEV_CHECK_CODE(NULL == g_osd_top_m23_reg, goto func_exit, "out of mem\n");

    if (NULL == g_osd_top_m23_reg_shadow)
    {
        g_osd_top_m23_reg_shadow = (OSD_TOP_M23_REG_T*)OS_Malloc(sizeof(OSD_TOP_M23_REG_T));
    }

    FBDEV_CHECK_CODE(NULL == g_osd_top_m23_reg_shadow, goto func_exit, "out of mem\n");

    /* ioremap OSD regs */
    if (NULL == g_osd_m23_reg)
    {
        g_osd_m23_reg = (OSD_M23_REG_T*)ioremap(M23_CCO_BASE, sizeof(OSD_M23_REG_T));
    }

    FBDEV_CHECK_CODE(NULL == g_osd_m23_reg, goto func_exit, "out of mem\n");

    if (NULL == g_osd_m23_reg_shadow)
    {
        g_osd_m23_reg_shadow = (OSD_M23_REG_T*)OS_Malloc(sizeof(OSD_M23_REG_T));
    }

    FBDEV_CHECK_CODE(NULL == g_osd_m23_reg_shadow, return RET_ERROR, "out of mem\n");

    /* ioremap OSD_AFBC(0) regs */
    if (NULL == g_osd_afbc_m23_reg[0])
    {
        g_osd_afbc_m23_reg[0] = (OSD_AFBC_M23_REG_T*)ioremap(M23_CCO_AFBC0_BASE, sizeof(OSD_AFBC_M23_REG_T));
    }

    FBDEV_CHECK_CODE(NULL == g_osd_afbc_m23_reg[0], goto func_exit, "out of mem\n");

    if (NULL == g_osd_afbc_m23_reg_shadow[0])
    {
        g_osd_afbc_m23_reg_shadow[0] = (OSD_AFBC_M23_REG_T*)OS_Malloc(sizeof(OSD_AFBC_M23_REG_T));
    }

    FBDEV_CHECK_CODE(NULL == g_osd_afbc_m23_reg_shadow[0], return RET_ERROR, "out of mem\n");

    /* ioermap MIF(0) regs */
    if (NULL == g_osd_mif_m23_reg[0])
    {
        g_osd_mif_m23_reg[0] = (OSD_MIF_M23_REG_T*)ioremap(M23_CCO_MIF0_BASE, sizeof(OSD_MIF_M23_REG_T));
    }

    FBDEV_CHECK_CODE(NULL == g_osd_mif_m23_reg[0], goto func_exit, "out of mem\n");

    if (NULL == g_osd_mif_m23_reg_shadow[0])
    {
        g_osd_mif_m23_reg_shadow[0] = (OSD_MIF_M23_REG_T*)OS_Malloc(sizeof(OSD_MIF_M23_REG_T));
    }

    FBDEV_CHECK_CODE(NULL == g_osd_mif_m23_reg_shadow[0], return RET_ERROR, "out of mem\n");


    // configure fixed B.OSD top ctrls
    // <FPGA> 값 틀림. cmm 확인 필요
    OSD_TOP_M23_Wr(ctrl_auto_init, 0x55555555);
    OSD_TOP_M23_Wr(ctrl_intr_pulse, 0xCA876420);

    // raxis.lim (2016/03/28) -- ctrl_intr_pulse, ctrl_dpath, ctrl_spath is set by HW default value
    // raxis.lim (2016/10/05) -- keep AFBC status becuase boot loader can display AFBC logo image
    // raxis.lim (2019/08/06) -- DO NOT full value to ctrl_dpath.
    // refer to http://clm.lge.com/issue/browse/AVTASK-386?focusedCommentId=1964037&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-1964037
    //
    if (FBDEV_M23_CMN_GetHWStatus(FBDEV_M23_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0))
    {
        OSD_TOP_M23_Wr01(ctrl_dpath, osd0_afbc_en, 0x1);
    }
    else
    {
        OSD_TOP_M23_Wr01(ctrl_dpath, osd0_afbc_en, 0x0);
    }

    OSD_TOP_M23_WrFL(ctrl_auto_init);
    OSD_TOP_M23_WrFL(ctrl_intr_pulse);

    OSD_TOP_M23_WrFL(ctrl_dpath);
    //OSD_TOP_M23_WrFL(ctrl_spath);

    if (FBDEV_M23_CMN_IsUHDDispMode())
    {
        FBDEV_WARN("++ UHD mode : pic_init_timer config\n");

        // raxis.lim (2019/05/23)
        // OSD_IMAGE1 (E-Stremaer) 에서는 pic_init 0 값 설정 중요함. (SICDTV-6809 참조)
        // 만약 0xa000 값을 사용하게 되면, E-Streamer OSD 의 오프셋이 틀어지거나, OSD 가 흐름.
        //
        // 결론은 use the default configuration 0x7000_0000
        //
        OSD_TOP_M23_Wr(pic_init_g0_timer, 0x70000000);
        OSD_TOP_M23_Wr(pic_init_g1_timer, 0x70000000);
        OSD_TOP_M23_Wr(pic_init_g2_timer, 0x70000000);
        OSD_TOP_M23_Wr(pic_init_g3_timer, 0x70000000);
        OSD_TOP_M23_Wr(pic_init_g4_timer, 0x70000000);
        OSD_TOP_M23_Wr(pic_init_g5_timer, 0x70000000);
        OSD_TOP_M23_Wr(pic_init_g6_timer, 0x70000000);
        OSD_TOP_M23_Wr(pic_init_g7_timer, 0x70000000);

        OSD_TOP_M23_WrFL(pic_init_g0_timer);
        OSD_TOP_M23_WrFL(pic_init_g1_timer);
        OSD_TOP_M23_WrFL(pic_init_g2_timer);
        OSD_TOP_M23_WrFL(pic_init_g3_timer);
        OSD_TOP_M23_WrFL(pic_init_g4_timer);
        OSD_TOP_M23_WrFL(pic_init_g5_timer);
        OSD_TOP_M23_WrFL(pic_init_g6_timer);
        OSD_TOP_M23_WrFL(pic_init_g7_timer);
    }
    else
    {
        // TBD
    }

    // configure MIF to show OSD with ARGB color
    //
    // raxis.lim (2019/05/24)
    //
    // wr 0XC9010C20 0x400000FB     # R_OSD0_MB_REQ.req_msk_f_on=0 (for UI)
    // wr 0XC9010C60 0x400000FB     # R_CSR0_MB_REQ.req_msk_f_on=0 (for CURSOR)
    // wr 0XC9012820 0x400000FB     # R_OSD1_MB_REQ.req_msk_f_on=0 (for E-Streamer)
    //
    // MIF1req_msk_f_on=1 설정시 IMAGE1 ARGB 출력시 화면이 보이지 않음. (SICDTV-6809 참조)
    FBDEV_M23_TODO("<FGPA> 값 틀림. 확인할것")
    OS_WrReg(M23_CCO_MIF0_BASE + 0x20, 0x400000FB);
    OS_WrReg(M23_CCO_MIF0_BASE + 0x60, 0x400000FA);

    FBDEV_M23_TODO("아래 코드는 지원도 될것 같은데")
#if 0
    // (2021/11/01) M23-to-F22 OSD change flag configuration
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
    OS_WrReg(M23_CCO_TOP_CTRL1_BASE + 0x18, 0xFF0101);
#endif

    /* HW revision specific initialization */
    FBDEV_M23_InitOSDZOrder();

    FBDEV_M23_CMN_InitHW();

    // refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT
    if (!(hw_ctx->hw_wa_flag & FBDEV_M23_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR))
    {
        if (hw_ctx->user_initcall_ctrl.ready)
        {
            FBDEV_NOTI("++ PIC_INIT ++ (NORMAL)\n");
            OSD_TOP_M23_RdFL(pic_init);
            OSD_TOP_M23_Wr01(pic_init, g0_auto_init, 0x1); // OSD(0)
            OSD_TOP_M23_Wr01(pic_init, g4_auto_init, 0x1); // OSD(4)
            OSD_TOP_M23_WrFL(pic_init);
        }
    }

    /* migrate LG Logo Image at kdriver initialization */
    FBDEV_M23_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_CLEAR);

    ret = RET_OK; /* all work done */
func_exit:
    return ret;
}

int FBDEV_M23_ShutdownHW(void)
{
    /* do nothing */
    return RET_OK;
}

/*========================================================================================
    Implementation group (legacy)
========================================================================================*/
void FBDEV_M23_InitOSDZOrder(void)
{
    /* do nothing */
}

int FBDEV_M23_SetZList(LX_FBDEV_ZLIST_T* zList)
{
    return RET_OK;
}

int FBDEV_M23_GetZList(LX_FBDEV_ZLIST_T* zList)
{
    zList->order[0] = 0;
    zList->order[1] = 1;
    zList->order[2] = 2;

    return RET_OK;
}

int FBDEV_M23_WriteOSDEndian(int fb_dev_id, ENDIAN_INFORM_T* endian)
{
    return RET_OK;
}

int FBDEV_M23_WriteOSDCSC(int layer, CSC_INFORM_T* csc)
{
    return RET_OK;
}



