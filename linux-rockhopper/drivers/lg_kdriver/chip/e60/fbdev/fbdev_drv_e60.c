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
 *  @author		raxis.lim
 *  @version	1.0
 *  @date		2014-03-01
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_e60.h"
#include "fbdev_hal.h"
#include "osd_reg_e60.h"
#include "osd_shp_reg_e60.h"
#include "osd_merg_reg_e60.h"
#include "osd_afbc_reg_e60.h"
#include "osd_cco_top_reg_e60.h"
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

#include "../sys/ctop_regs.h"

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
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_OVI
extern int OVI_HAL_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);
#endif

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern FBDEV_E60_HW_FUNC_T		g_fbdev_e60_cmn_hw_func;	/* E60 HW common func */

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_E60_InitOSDZOrder (void);
LX_FBDEV_CFG_T*	FBDEV_E60_GetCfg(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile OSD_E60_REG_T*			g_osd_e60_reg = NULL;
		 OSD_E60_REG_T*			g_osd_e60_reg_shadow = NULL;

volatile OSD_CTRL_E60_REG_T*	g_osd_ctrl_e60_reg[4] = {NULL,NULL,NULL,NULL};
		 OSD_CTRL_E60_REG_T*	g_osd_ctrl_e60_reg_shadow[4] = {NULL,NULL,NULL,NULL};

volatile OSD_SHP_E60_REG_T*		g_osd_shp_e60_reg[2] = {NULL, NULL};
		 OSD_SHP_E60_REG_T*		g_osd_shp_e60_reg_shadow[2] = {NULL, NULL};

volatile OSD_MERG_E60_REG_T*	g_osd_merg_e60_reg[2] = {NULL, NULL};
		 OSD_MERG_E60_REG_T*	g_osd_merg_e60_reg_shadow[2] = {NULL, NULL};

volatile OSD_AFBC_E60_REG_T* 	g_osd_afbc_e60_reg[2] = {NULL,NULL};
		 OSD_AFBC_E60_REG_T* 	g_osd_afbc_e60_reg_shadow[2] = {NULL,NULL};

volatile OSD_CCO_TOP_E60_REG_T*	g_osd_cco_top_e60_reg[2] = {NULL,NULL};
		 OSD_CCO_TOP_E60_REG_T*	g_osd_cco_top_e60_reg_shadow[2] = {NULL,NULL};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_E60_AutoDetectOSDHWValue (void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static FBDEV_E60_HW_CTX_T g_fbdev_e60_hw_ctx;

static	FBDEV_HW_CTX_T	_g_fbdev_hw_ctx =
{
	.GetCfg				= FBDEV_E60_GetCfg,
	.RunSuspend			= FBDEV_E60_CMN_RunSuspend,
	.RunResume			= FBDEV_E60_CMN_RunResume,

	.InitHW				= FBDEV_E60_InitHW,
	.ShutdownHW			= FBDEV_E60_ShutdownHW,
	.ExecHWCommand      = FBDEV_E60_CMN_ExecHWCommand,

	.SetOSDEnable		= FBDEV_E60_SetOSDEnable,
	.GetOSDEnable		= FBDEV_E60_GetOSDEnable,

	.InitOSDLayer		= FBDEV_E60_InitOSDLayer,
	.WriteOSDHeader		= FBDEV_E60_WriteOSDHeader,

	.GetZList			= FBDEV_E60_GetZList,
	.SetZList			= FBDEV_E60_SetZList,

	.WriteOSDEndian		= FBDEV_E60_WriteOSDEndian,
	.WriteOSDCSC		= FBDEV_E60_WriteOSDCSC,

	.GetInterruptStatus	= FBDEV_E60_GetInterruptStatus,
	.SetInterruptClear	= FBDEV_E60_SetInterruptClear,
	.SetInterruptEnable	= FBDEV_E60_SetInterruptEnable,

	.SetViewCtrl		= FBDEV_E60_SetViewCtrl,
	.SetConnCtrl		= FBDEV_E60_SetConnCtrl,

	.CreateProc			= FBDEV_E60_CreateProc,
	.ProcHandler		= FBDEV_E60_CMN_ProcHandler,
};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get E60 specific configuration
 *
 *  @return LX_FBDEV_CFG_T
 */
LX_FBDEV_CFG_T*   FBDEV_E60_GetCfg(void)
{
    return NULL;
}

/** initialize E60 specific HW context variables.
 *
 *	@note this function is called before at E60 configure stage NOT at HW initialization stage.
 */
void	FBDEV_E60_InitHWCtx( FBDEV_HW_CTX_T* hal_obj )
{
	int	i;

	/* initialize chip dependent variable */
	{
        g_fbdev_frc_ctrl.b_frc_sep_enable   = FALSE;    /* Blending Mode by default */
        g_fbdev_frc_ctrl.b_frc_UD_enable    = FALSE;    /* Standard Mode by default */
        g_fbdev_frc_ctrl.b_frc_hdr_emul     = FALSE;    /* Disable FRC HDR emulation */
        g_fbdev_frc_ctrl.b_frc_osd_emul     = TRUE;
        g_fbdev_frc_ctrl.frc_hdr_emul_dev   = -1;
	}

	memset(&g_fbdev_e60_hw_ctx, 0x0, sizeof(FBDEV_E60_HW_CTX_T));

	/* select the active E60 HW function handler */
	memcpy( &g_fbdev_e60_hw_ctx.func, &g_fbdev_e60_cmn_hw_func, sizeof(FBDEV_E60_HW_FUNC_T));

    for( i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
		g_fbdev_e60_hw_ctx.conn_ctrl[i].conn_type	= g_fbdev_e60_hw_ctx.hw_conn_type;
		g_fbdev_e60_hw_ctx.fbc_ctrl[i].status		= FBDEV_E60_FBC_STATUS_NONE;
		g_fbdev_e60_hw_ctx.sr_ctrl[i].status		= FBDEV_E60_SR_STATUS_OFF;
		g_fbdev_e60_hw_ctx.sr_ctrl[i].ti_gain		= -1;
	}

	g_fbdev_e60_hw_ctx.mirror_ctrl.status = FBDEV_E60_MIRROR_NONE;

	/* auto detect the default OSD connection and display size etc */
	FBDEV_E60_AutoDetectOSDHWValue( );

	/* initialize hal object
	 * after this function, all fbdev kdriver can get g_fbdev_e60_hw_ctx via g_fbdev_hw_ctx->chip_priv_ctx
	 */
	memcpy(hal_obj, &_g_fbdev_hw_ctx, sizeof(FBDEV_HW_CTX_T));
	hal_obj->chip_priv_ctx = &g_fbdev_e60_hw_ctx;
}

/** detect the default OSD connection
 *	This function will return the default(best) OSD connection setup based on SW, HW info
 *
 *	@note In E60, video path is fixed to UHD display. OSD will use this HW assumption.
 */
static void FBDEV_E60_AutoDetectOSDHWValue (void)
{
	UINT32	osd_fb0_img_val		= LX_MAKE_RES(1920,1080);		/* defualt input image. default 2K resolution */
	UINT32	osd_fb1_img_val		= LX_MAKE_RES(512,2160);		/* defualt input image. as small as possible */
	UINT32	osd_fb3_img_val		= LX_MAKE_RES(512,512);			/* defualt input image. 512x512 */
	UINT32	osd_disp_bosd_val	= LX_MAKE_RES(7680,4320);		/* default 8K resolution */
	UINT32	osd_disp_sosd_val	= LX_MAKE_RES(1920,1080);		/* default 2K resolution */
	UINT32 	osd_conn_val		= LX_FBDEV_CONN_OSD_VIDEO_BLEND;/* default path */
	UINT32	osd_scale_bosd_val	= FB_E60_SCALE_MODE_X4;			/* default scale_mode = x4 */
	UINT32	osd_scale_sosd_val	= FB_E60_SCALE_MODE_NONE;		/* defualt scale_mode = x1 */
	UINT32	osd_pulse_bosd_val	= 0xD000;						/* default pulse timer delay. default 0xD000 */
	UINT32	osd_pulse_sosd_val	= 0xD000;						/* default pulse timer delay. default 0xD000 */

	UINT32	osd_fb1_8k_img_val	= LX_MAKE_RES(1024,4320);		/* defualt 8k fb1 framebuffer. default 1K*4K */
	UINT32	osd_ext_render_val	= LX_MAKE_RES(1024,4320);		/* default 8k ext framebuffer. default 1K*4K */
	UINT32	osd_ext_render_support = 1;							/* fb1 renderer is always supported by default (TV spec) */
	UINT32	osd_ext_render_swsync_hz_val = 15;					/* default 8k ext swsync interval. default 15Hz=16.666 ms */
	UINT32	osd_ext_render_bpp_val = 3;							/* default 8k ext bytes per pixel. default 3(RGB) */
	UINT32	osd_ext_render_output_path = FB_E60_EXT_RENDER_PQE_PATH; /* default 8k ext renderer is to use video out */
	UINT32	osd_ext_render_test_mode = 0;						/* disable test mode */
	UINT32	osd_ext_render_debug_xoffset = 0;					/* user defined xoffset. default 0 */
	UINT32	osd_ext_render_debug_osd_out= 0;					/* user defined xoffset. default 0 */

#if 0//def FBDEV_PIONEER_PLATFORM
	/* do nothing */
#else
	/* do nothing */
#endif

	FBDEV_E60_HW_CTX_T* hw_ctx = &g_fbdev_e60_hw_ctx;

	/* make the initial HW config to "disabled" state */
	hw_ctx->hw_wa_flag= 0x0;
	hw_ctx->b_support_ext_frc = FALSE;
	hw_ctx->b_support_ext_render = FALSE;
	hw_ctx->b_ext_fb1_renderer_test_mode = FALSE;

	/* setup fb(1) based on the default configuration */
	if(FBDEV_E60_POSD_NUM>=2)
	{
		hw_ctx->b_support_fb1 = TRUE;
		osd_fb1_img_val = LX_MAKE_RES(FBDEV_E60_POSD1_WIDTH, FBDEV_E60_POSD1_HEIGHT);
	}
	else if(FBDEV_E60_POSD_NUM==1)
	{
		hw_ctx->b_support_fb1 = FALSE;
	}

	/* read HW configuration by parsing some kernel parameters */
	{
		if(lx_board_opt() & LX_BOARD_OPT_EXT_FRC)
		{
			printk("<!> fbdev S.OSD detected\n");
			hw_ctx->b_support_ext_frc = TRUE;			/* support external FRC */
		}

		if(lx_board_opt() & LX_BOARD_OPT_4K_GRAPHIC)
		{
			printk("<!> fbdev 4KOSD detected\n");
			osd_fb0_img_val	= LX_MAKE_RES(3840,2160);	/* support 4K render */
			osd_disp_sosd_val = LX_MAKE_RES(3840,2160);	/* support 4K S.OSD display */
		}
	}

	/* read HW display option from OVI */
#ifdef INCLUDE_KDRV_OVI
	{
		LX_OVI_HW_DISPLAY_INFO_T disp_info;

		if(OVI_HAL_GetHWDisplayOption(&disp_info) == RET_OK)
		{
			if(disp_info.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F20)
			{
				hw_ctx->b_support_ext_frc = TRUE;		/* support external FRC */
			}
		}
		printk("<!> fbdev support_ext_frc=%d\n", hw_ctx->b_support_ext_frc);
	}
#else
	FBDEV_WARN("OVI_HAL_GetHWDisplayOption() not used\n");
#endif

	/* read test options for internal use only. it can overrides the previous HW configration */
	{
		char	opt[32];
		UINT32	fbnum, val, res_w, res_h;

		if(RET_OK==OS_ScanKernelCmdline("osd.disp.path=%s", opt))
		{
			if(!strncmp(opt,"sosd",4))
			{
				hw_ctx->b_support_ext_frc = TRUE;
			}
			else if(!strncmp(opt,"bosd",4))
			{
				osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_BLEND;
				hw_ctx->b_support_ext_frc = FALSE;
			}
		}

		if(RET_OK==OS_ScanKernelCmdline("osd.disp.bosd=%s", opt))
		{
			sscanf(opt, "%dx%d", &res_w, &res_h);
			osd_disp_bosd_val = LX_MAKE_RES(res_w, res_h);
		}

		if(RET_OK==OS_ScanKernelCmdline("osd.disp.sosd=%s", opt))
		{
			sscanf(opt, "%dx%d", &res_w, &res_h);
			osd_disp_sosd_val = LX_MAKE_RES(res_w, res_h);
		}

		if(RET_OK==OS_ScanKernelCmdline("osd.fb.num=%s", opt))
		{
			sscanf(opt, " %d", &fbnum);

			if(fbnum==2)
			{
				hw_ctx->b_support_fb1 = TRUE;
			}
			else
			{
				hw_ctx->b_support_fb1 = FALSE;
			}
		}

		if(RET_OK==OS_ScanKernelCmdline("osd.fb.fb0=%s", opt))
		{
			sscanf(opt, "%dx%d", &res_w, &res_h);
			osd_fb0_img_val = LX_MAKE_RES(res_w, res_h);
		}

		if(RET_OK==OS_ScanKernelCmdline("osd.fb.fb1=%s", opt))
		{
			sscanf(opt, "%dx%d", &res_w, &res_h);
			osd_fb1_img_val = LX_MAKE_RES(res_w, res_h);

			if (res_h > 2160)
			{
				osd_fb1_8k_img_val = LX_MAKE_RES(res_w, res_h);
			}
		}

		// raxis.lim (2020/03/31) - if defined, enable external renderer for debug purpose
		if(RET_OK==OS_ScanKernelCmdline("osd.fb.ext_render=%s", opt))
		{
			sscanf(opt, "%dx%d@%d", &res_w, &res_h, &val);
			osd_ext_render_val = LX_MAKE_RES(res_w, res_h);
			osd_ext_render_swsync_hz_val = val;

			osd_ext_render_support = 1;
		}

		// raxis.lim (2020/08/04) - osd_path, xoffset, bpp, osd_out are debug purpose only
		if(RET_OK==OS_ScanKernelCmdline("osd.fb.ext_render.osd_path=%s", opt))
		{
			sscanf(opt, "%d", &val);
			osd_ext_render_output_path |= FB_E60_EXT_RENDER_OSD_PATH;
			osd_ext_render_bpp_val = 4; /* ARGB */
		}

		if(RET_OK==OS_ScanKernelCmdline("osd.fb.ext_render.xoffset=%s", opt))
		{
			sscanf(opt, "%d", &val);
			osd_ext_render_debug_xoffset = val;
		}

		if(RET_OK==OS_ScanKernelCmdline("osd.fb.ext_render.osd_out=%s", opt))
		{
			sscanf(opt, "%d", &val);
			osd_ext_render_debug_osd_out= val;
		}

		/* support F20 ext_frc emulation regardless of F20 */
		if(RET_OK==OS_ScanKernelCmdline("osd.ext_frc=%s", opt))
		{
			sscanf(opt, "%d", &val);

			if (val==1)
			{
				hw_ctx->b_support_ext_frc = TRUE;
			}
			else
			{
				hw_ctx->b_support_ext_frc = FALSE;
			}
		}
	}

	/* enable S.OSD path when EXT_FRC connected */
	if(hw_ctx->b_support_ext_frc)
	{
		osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE;
	}

	printk("fbdev conn=EXT_FRC(F20)=%d. 8k_ext_renderer=%d (test=%d)\n",
		hw_ctx->b_support_ext_frc, osd_ext_render_support, osd_ext_render_test_mode);

	/* save external renderer configuration to hw_ctx */
	if(osd_ext_render_support)
	{
		hw_ctx->b_support_fb1 = TRUE;
		hw_ctx->b_support_ext_render = TRUE;

		osd_fb1_img_val = osd_fb1_8k_img_val;

		// (2020/08/11)
		// when F20 connected, enable 2nd method of 8K-Estreamer implemenation
		// it's not certain whether OSD_PATH control is necessary or not.
		// use osd.fb.ext_render.osd_path=1 for for test purpose.
		//
		// (2020/09/02)
		//
		// tune fps of E-streamer (15 -> 12 -> 10)
		// http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2542021&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2542021
		if (hw_ctx->b_support_ext_frc)
		{
			osd_ext_render_bpp_val = 4;
			osd_ext_render_swsync_hz_val = 10;

			#if 0
			osd_ext_render_output_path |= FB_E60_EXT_RENDER_OSD_PATH;
			#endif
		}
	}

	/* save all configurations to hw_ctx */
	hw_ctx->b_ext_fb1_renderer_test_mode = osd_ext_render_test_mode;

	hw_ctx->sosd_disp.fb0_width  = LX_RES_GET_WIDTH(osd_fb0_img_val);
	hw_ctx->sosd_disp.fb0_height = LX_RES_GET_HEIGHT(osd_fb0_img_val);
	hw_ctx->sosd_disp.fb1_width  = LX_RES_GET_WIDTH(osd_fb1_img_val);
	hw_ctx->sosd_disp.fb1_height = LX_RES_GET_HEIGHT(osd_fb1_img_val);
	hw_ctx->sosd_disp.fb3_width  = LX_RES_GET_WIDTH(osd_fb3_img_val);
	hw_ctx->sosd_disp.fb3_height = LX_RES_GET_HEIGHT(osd_fb3_img_val);
	hw_ctx->sosd_disp.out_width	 = LX_RES_GET_WIDTH(osd_disp_sosd_val);	/* S.OSD size is fixed to 1920x1080 */
	hw_ctx->sosd_disp.out_height = LX_RES_GET_HEIGHT(osd_disp_sosd_val);
	hw_ctx->sosd_disp.pulse_timer_dly = osd_pulse_sosd_val;
	hw_ctx->sosd_disp.fb_scale_mode = osd_scale_sosd_val;

	hw_ctx->bosd_disp.fb0_width  = LX_RES_GET_WIDTH(osd_fb0_img_val);
	hw_ctx->bosd_disp.fb0_height = LX_RES_GET_HEIGHT(osd_fb0_img_val);
	hw_ctx->bosd_disp.fb1_width  = LX_RES_GET_WIDTH(osd_fb1_img_val);
	hw_ctx->bosd_disp.fb1_height = LX_RES_GET_HEIGHT(osd_fb1_img_val);
	hw_ctx->bosd_disp.fb3_width  = LX_RES_GET_WIDTH(osd_fb3_img_val);
	hw_ctx->bosd_disp.fb3_height = LX_RES_GET_HEIGHT(osd_fb3_img_val);
	hw_ctx->bosd_disp.out_width  = LX_RES_GET_WIDTH(osd_disp_bosd_val);	/* B.OSD size might be changed based on DTV config */
	hw_ctx->bosd_disp.out_height = LX_RES_GET_HEIGHT(osd_disp_bosd_val);
	hw_ctx->bosd_disp.pulse_timer_dly = osd_pulse_bosd_val;
	hw_ctx->bosd_disp.fb_scale_mode = osd_scale_bosd_val;

#ifdef FBDEV_E60_SUPPORT_4KOSD
	/* raxis.lim (2019/05/21) -- we should support 4K OSD display !! */
	if (LX_RES_GET_WIDTH(osd_fb0_img_val) >= 2048)
	{
		hw_ctx->bosd_disp.fb_scale_mode = FB_E60_SCALE_MODE_X2;	/* 4K to 8K */
		hw_ctx->b_support_4kosd = TRUE;
	}
#endif

	if (osd_conn_val & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		hw_ctx->b_keep_hw_conn_type	= TRUE;
		hw_ctx->hw_disp_width		= hw_ctx->bosd_disp.out_width;
		hw_ctx->hw_disp_height		= hw_ctx->bosd_disp.out_height;
		hw_ctx->hw_fb0_width		= hw_ctx->bosd_disp.fb0_width;
		hw_ctx->hw_fb0_height		= hw_ctx->bosd_disp.fb0_height;
		hw_ctx->hw_fb1_width		= hw_ctx->bosd_disp.fb1_width;
		hw_ctx->hw_fb1_height		= hw_ctx->bosd_disp.fb1_height;
		hw_ctx->hw_fb3_width		= hw_ctx->bosd_disp.fb3_width;
		hw_ctx->hw_fb3_height		= hw_ctx->bosd_disp.fb3_height;
		hw_ctx->hw_fb_scale_mode	= hw_ctx->bosd_disp.fb_scale_mode;
	}
	else
	{
		hw_ctx->b_keep_hw_conn_type	= FALSE;
		hw_ctx->hw_disp_width 		= hw_ctx->sosd_disp.out_width;
		hw_ctx->hw_disp_height		= hw_ctx->sosd_disp.out_height;
		hw_ctx->hw_fb0_width 		= hw_ctx->sosd_disp.fb0_width;
		hw_ctx->hw_fb0_height		= hw_ctx->sosd_disp.fb0_height;
		hw_ctx->hw_fb1_width 		= hw_ctx->sosd_disp.fb1_width;
		hw_ctx->hw_fb1_height		= hw_ctx->sosd_disp.fb1_height;
		hw_ctx->hw_fb3_width 		= hw_ctx->sosd_disp.fb3_width;
		hw_ctx->hw_fb3_height		= hw_ctx->sosd_disp.fb3_height;
		hw_ctx->hw_fb_scale_mode	= hw_ctx->sosd_disp.fb_scale_mode;
	}

	hw_ctx->hw_ext_render_width		= LX_RES_GET_WIDTH(osd_ext_render_val);
	hw_ctx->hw_ext_render_height	= LX_RES_GET_HEIGHT(osd_ext_render_val);
	hw_ctx->hw_ext_render_swsync_hz = osd_ext_render_swsync_hz_val;
	hw_ctx->hw_ext_render_bpp		= osd_ext_render_bpp_val;
	hw_ctx->hw_ext_render_output_path = osd_ext_render_output_path;

	hw_ctx->hw_ext_render_debug_xoffset = osd_ext_render_debug_xoffset;
	hw_ctx->hw_ext_render_debug_osd_output = osd_ext_render_debug_osd_out;

	hw_ctx->hw_conn_type 			= osd_conn_val;
	hw_ctx->hw_wa_flag				|= FBDEV_E60_HW_WA_1X_CSR_DISP_ON_BLEND_PATH;

	printk("fbdev hw_conn=0x%x, fb0=%dx%d fb1=%dx%d disp=%dx%d ext_render=%d,%dx%d,%d,@%dHz flag=%d,%d wa_flag=0x%08x\n",
			hw_ctx->hw_conn_type,
			hw_ctx->hw_fb0_width, hw_ctx->hw_fb0_height,
			hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height,
			hw_ctx->hw_disp_width, hw_ctx->hw_disp_height,
			hw_ctx->b_support_ext_render,
			hw_ctx->hw_ext_render_width, hw_ctx->hw_ext_render_height,
			hw_ctx->hw_ext_render_bpp, hw_ctx->hw_ext_render_swsync_hz,
			hw_ctx->b_support_4kosd, hw_ctx->b_support_fb1,
			hw_ctx->hw_wa_flag);
}

/*========================================================================================
	Implementation Group (INIT/EXIT)
========================================================================================*/
/** initialize OSD IP HW and register
 *
 * @param
 * @return	int 0 : OK , -1 : NOT OK
 *
 * [OK]
 */
int FBDEV_E60_InitHW (void)
{
	int ret = RET_ERROR;
	int	osd_ctrl_off[4];
	int	i;

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	/* ioremap CCO1_TOP regs */
	if (NULL==g_osd_cco_top_e60_reg[0])
	{
		g_osd_cco_top_e60_reg[0] =(OSD_CCO1_TOP_E60_REG_T*)ioremap(E60_CCO1_TOP_CTRL_BASE, sizeof(OSD_CCO1_TOP_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_cco_top_e60_reg[0], goto func_exit, "out of mem\n");

	if (NULL==g_osd_cco_top_e60_reg_shadow[0])
	{
		g_osd_cco_top_e60_reg_shadow[0] =(OSD_CCO1_TOP_E60_REG_T*)OS_Malloc(sizeof(OSD_CCO1_TOP_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_cco_top_e60_reg_shadow[0], goto func_exit, "out of mem\n");

	/* ioremap CCO2_TOP regs */
	if (NULL==g_osd_cco_top_e60_reg[1])
	{
		g_osd_cco_top_e60_reg[1] =(OSD_CCO2_TOP_E60_REG_T*)ioremap(E60_CCO2_TOP_CTRL_BASE, sizeof(OSD_CCO2_TOP_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_cco_top_e60_reg[1], goto func_exit, "out of mem\n");

	if (NULL==g_osd_cco_top_e60_reg_shadow[1])
	{
		g_osd_cco_top_e60_reg_shadow[1] =(OSD_CCO2_TOP_E60_REG_T*)OS_Malloc(sizeof(OSD_CCO2_TOP_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_cco_top_e60_reg_shadow[1], goto func_exit, "out of mem\n");

	/* ioremap OSD regs */
	if (NULL==g_osd_e60_reg)
	{
		g_osd_e60_reg =(OSD_E60_REG_T*)ioremap(E60_CCO_BASE, sizeof(OSD_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_e60_reg, goto func_exit, "out of mem\n");

	if (NULL==g_osd_e60_reg_shadow)
	{
		g_osd_e60_reg_shadow = (OSD_E60_REG_T*)OS_Malloc(sizeof(OSD_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_e60_reg_shadow, return RET_ERROR, "out of mem\n");

	/* raxis.lim (2019/12/14)
	 * OSD 각 블럭의 공통 부분을 최대한 활용하기 위하여, 실제 real_reg, shadow_reg 에서 필요한 위치를 찾아,
	 * osd_ctrl_xxx 값들을 설정합니다.
	 *
	 */
	osd_ctrl_off[0] = OSDX_E60_Off(osdx_prep_img0, osd0_0_ctrl_main);
	osd_ctrl_off[1] = OSDX_E60_Off(osdx_prep_img0, osd0_1_ctrl_main);
	osd_ctrl_off[2] = OSDX_E60_Off(osdx_prep_est,  osd1_ctrl_main);
	osd_ctrl_off[3] = OSDX_E60_Off(osdx_prep_csr,  osd4_ctrl_main);

	//FBDEV_NOTI("osd_ctrl_off 0x%08x 0x%08x 0x%08x 0x%08x\n", osd_ctrl_off[0], osd_ctrl_off[1], osd_ctrl_off[2], osd_ctrl_off[3] );

	for (i=0; i<4; i++)
	{
		if(!g_osd_ctrl_e60_reg[i])
		{
			g_osd_ctrl_e60_reg[i] = (OSD_CTRL_E60_REG_T*)((UINT8*)g_osd_e60_reg+ osd_ctrl_off[i]);
			FBDEV_HW_NOTI("++ mapping osd_ctrl regs(real). off[%d]=0x%04x, reg_p= %p, vreg_p=%p\n",
				i, osd_ctrl_off[i], g_osd_e60_reg, g_osd_ctrl_e60_reg[i]);
		}

		if(!g_osd_ctrl_e60_reg_shadow[i])
		{
			g_osd_ctrl_e60_reg_shadow[i] = (OSD_CTRL_E60_REG_T*)((UINT8*)g_osd_e60_reg_shadow + osd_ctrl_off[i]);
			FBDEV_HW_NOTI("++ mapping osd_ctrl regs(shdw). off[%d]=0x%04x, reg_p=%p, vreg_p=%p\n",
				i, osd_ctrl_off[i], g_osd_e60_reg_shadow, g_osd_ctrl_e60_reg_shadow[i]);
		}
	}

	/* ioremap OSD_AFBC(0) regs */
	if (NULL==g_osd_afbc_e60_reg[0])
	{
		g_osd_afbc_e60_reg[0]=(OSD_AFBC_E60_REG_T*)ioremap(E60_CCO_AFBC0_BASE, sizeof(OSD_AFBC_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_e60_reg[0], goto func_exit, "out of mem\n");

	if (NULL==g_osd_afbc_e60_reg_shadow[0])
	{
		g_osd_afbc_e60_reg_shadow[0] = (OSD_AFBC_E60_REG_T*)OS_Malloc(sizeof(OSD_AFBC_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_e60_reg_shadow[0], return RET_ERROR, "out of mem\n");

	/* ioremap OSD_AFBC(1) regs */
	if (NULL==g_osd_afbc_e60_reg[1])
	{
		g_osd_afbc_e60_reg[1]=(OSD_AFBC_E60_REG_T*)ioremap(E60_CCO_AFBC1_BASE, sizeof(OSD_AFBC_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_e60_reg[1], goto func_exit, "out of mem\n");

	if (NULL==g_osd_afbc_e60_reg_shadow[1])
	{
		g_osd_afbc_e60_reg_shadow[1] = (OSD_AFBC_E60_REG_T*)OS_Malloc(sizeof(OSD_AFBC_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_e60_reg_shadow[1], return RET_ERROR, "out of mem\n");

	/* ioremap OSD_SHP(0) regs */
	if (NULL==g_osd_shp_e60_reg[0])
	{
		g_osd_shp_e60_reg[0] =(OSD_SHP_E60_REG_T*)ioremap(E60_CCO_SHP0_BASE, sizeof(OSD_SHP_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_e60_reg[0], goto func_exit, "out of mem\n");

	if (NULL==g_osd_shp_e60_reg_shadow[0])
	{
		g_osd_shp_e60_reg_shadow[0] = (OSD_SHP_E60_REG_T*)OS_Malloc(sizeof(OSD_SHP_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_e60_reg_shadow[0], return RET_ERROR, "out of mem\n");

	/* ioremap OSD_SHP(1) regs */
	if (NULL==g_osd_shp_e60_reg[1])
	{
		g_osd_shp_e60_reg[1] =(OSD_SHP_E60_REG_T*)ioremap(E60_CCO_SHP1_BASE, sizeof(OSD_SHP_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_e60_reg[1], goto func_exit, "out of mem\n");

	if (NULL==g_osd_shp_e60_reg_shadow[1])
	{
		g_osd_shp_e60_reg_shadow[1] = (OSD_SHP_E60_REG_T*)OS_Malloc(sizeof(OSD_SHP_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_e60_reg_shadow[1], return RET_ERROR, "out of mem\n");

	/* ioremap OSD_MERG(0) regs */
	if (NULL==g_osd_merg_e60_reg[0])
	{
		g_osd_merg_e60_reg[0] =(OSD_MERG_E60_REG_T*)ioremap(E60_CCO_MERG0_BASE, sizeof(OSD_MERG_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_merg_e60_reg[0], goto func_exit, "out of mem\n");

	if (NULL==g_osd_merg_e60_reg_shadow[0])
	{
		g_osd_merg_e60_reg_shadow[0] = (OSD_MERG_E60_REG_T*)OS_Malloc(sizeof(OSD_MERG_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_merg_e60_reg_shadow[0], return RET_ERROR, "out of mem\n");

	/* ioremap OSD_MERG(1) regs */
	if (NULL==g_osd_merg_e60_reg[1])
	{
		g_osd_merg_e60_reg[1] =(OSD_MERG_E60_REG_T*)ioremap(E60_CCO_MERG1_BASE, sizeof(OSD_MERG_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_merg_e60_reg[1], goto func_exit, "out of mem\n");

	if (NULL==g_osd_merg_e60_reg_shadow[1])
	{
		g_osd_merg_e60_reg_shadow[1] = (OSD_MERG_E60_REG_T*)OS_Malloc(sizeof(OSD_MERG_E60_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_merg_e60_reg_shadow[1], return RET_ERROR, "out of mem\n");


	/* initialize common HW attributes */
	FBDEV_E60_CMN_InitHW();

	/* refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT */
	if (!(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR))
	{
		FBDEV_WARN("++ PIC_INIT ++ (NORMAL)\n");
		FBDEV_E60_CMN_SetupHWFunc(HWSETUP_PIC_INIT, 0x0, NULL);
	}

	/* migrate LG Logo Image at kdriver initialization */
	FBDEV_E60_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_KEEP);

	ret = RET_OK; /* all work done */
func_exit:
	return ret;
}

/** de-initialize OSD IP HW and register
 *
 *
 */
int FBDEV_E60_ShutdownHW	(void)
{
	/* do nothing */
	return RET_OK;
}

/*========================================================================================
	Implementation Group
========================================================================================*/
/** make initial OSD zorder. this function controls osd_layer_mux register
 *
 * @note somewhat obsolete function !
 */
void FBDEV_E60_InitOSDZOrder ( void )
{
	/* do nothing */
}

/** Update OSD zorder
 *
 * @note somewhat obsolete function !
 */
int FBDEV_E60_SetZList ( LX_FBDEV_ZLIST_T* zList )
{
	return RET_OK;
}

/** Get OSD ZList
 *
 * @note somewhat obsolete function !
 */
int FBDEV_E60_GetZList( LX_FBDEV_ZLIST_T* zList )
{
	zList->order[0] = 0;
	zList->order[1] = 1;
	zList->order[2] = 2;

	return RET_OK;
}

/*========================================================================================
	Implementation Group
========================================================================================*/
/** set endianess on each layer
 *
 * @note somewhat obsolete function !
 */
int FBDEV_E60_WriteOSDEndian(int fb_dev_id, ENDIAN_INFORM_T *endian)
{
    return RET_OK;
}

/** set color space conversion on each layer
 *
 * @note somewhat obsolete function !
 */
int FBDEV_E60_WriteOSDCSC(int layer , CSC_INFORM_T *csc)
{
	return RET_OK;
}

/** Get interrupt status
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T
 * @return	int 0 : OK , -1 : NOT OK
 *
 * [OK?]
 */
int FBDEV_E60_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
	UINT32	status = 0;

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	OSDX_E60_RdFL(osdx_post_top, osd_post_top_ctrl_irq);

	if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
	{
		UINT32 bosd_mixer;
		OSDX_E60_Rd01(osdx_post_top, osd_post_top_ctrl_irq, reg_top_ctrl_irq_clear_bosd, bosd_mixer);

		if(bosd_mixer)	status |= (1<<MIXER_INTR);
		else			printk("OSD ISR - BOSD MIXER INTR error\n");
	}
	else
	{
		UINT32 sosd_mixer;
		OSDX_E60_Rd01(osdx_post_top, osd_post_top_ctrl_irq, reg_top_ctrl_irq_clear_sosd, sosd_mixer);

		if(sosd_mixer)	status |= (1<<MIXER_INTR);
		else			printk("OSD ISR - SOSD MIXER INTR error\n");
	}

	FBDEV_ISR_DEBUG("irq reg info = 0x%08x\n", status );

	return status;
}

/** Clear interrupt status
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_E60_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
	/* clear both bosd, sosd mixer intr for the safe operation */
	OSDX_E60_RdFL(osdx_post_top, osd_post_top_ctrl_irq);
	OSDX_E60_Wr01(osdx_post_top, osd_post_top_ctrl_irq, reg_top_ctrl_irq_clear_bosd, 0x1);
	OSDX_E60_Wr01(osdx_post_top, osd_post_top_ctrl_irq, reg_top_ctrl_irq_clear_sosd, 0x1);

	OSDX_E60_WrFL(osdx_post_top, osd_post_top_ctrl_irq);

	return RET_OK;
}

/** Set interrupt enable/disable
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T , int : enable/disable
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_E60_SetInterruptEnable(INTERRUPT_INFORM_T intr , int enable)
{
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

    switch(intr)
    {
        case MIXER_INTR:
		default:
		{
			OSDX_E60_RdFL(osdx_post_top, osd_post_top_ctrl_irq);
			if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
			{
				FBDEV_DEBUG("INTR <%s> for B.OSD\n", enable? "ON":"OFF" );
				OSDX_E60_Wr01(osdx_post_top, osd_post_top_ctrl_irq, reg_top_ctrl_irq_en_bosd, enable);
				OSDX_E60_Wr01(osdx_post_top, osd_post_top_ctrl_irq, reg_top_ctrl_irq_en_sosd, 0x0);
			}
			else
			{
				FBDEV_DEBUG("INTR <%s> for S.OSD\n", enable? "ON":"OFF" );
				OSDX_E60_Wr01(osdx_post_top, osd_post_top_ctrl_irq, reg_top_ctrl_irq_en_bosd, 0x0);
				OSDX_E60_Wr01(osdx_post_top, osd_post_top_ctrl_irq, reg_top_ctrl_irq_en_sosd, enable);
			}
			OSDX_E60_WrFL(osdx_post_top, osd_post_top_ctrl_irq);
		}
		break;
    }

    return RET_OK;
}

/*========================================================================================
	Implementation Group
========================================================================================*/
/** some layer depdendent HW initialization
 *
 */
int	FBDEV_E60_InitOSDLayer	(int layer)
{
	return FBDEV_E60_CMN_InitOSDLayer(layer);
}

/*========================================================================================
	Implementation Group (REV dependent)
========================================================================================*/
int		FBDEV_E60_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl)
{
	int	ret = RET_ERROR;
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	FBDEV_CHECK_CODE(NULL==hw_ctx->func.E60_SetViewCtrl, return RET_ERROR, "null handler\n");

	ret = hw_ctx->func.E60_SetViewCtrl(ctrl);

	/* TODO: if you should merge OSD inside kernel driver, add your code here */

	return ret;
}

/** set OSD output ctrl
 *
 */
int     FBDEV_E60_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl)
{
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.E60_SetConnCtrl, return RET_ERROR, "null handler\n");

	return hw_ctx->func.E60_SetConnCtrl(ctrl);
}

/** Set Header information
 *
 */
int FBDEV_E60_WriteOSDHeader(struct scanvas *hCanvas)
{
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.E60_WriteOSDHeader, return RET_ERROR, "null handler\n");

	return hw_ctx->func.E60_WriteOSDHeader(hCanvas);
}

/** OSD HW Layer enable/disable
 *
 */
int FBDEV_E60_SetOSDEnable(int layer, int enable)
{
	int	ret = RET_ERROR;
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	FBDEV_CHECK_CODE(NULL==hw_ctx->func.E60_SetOSDEnable, return RET_ERROR, "null handler\n");

	ret = hw_ctx->func.E60_SetOSDEnable(layer, enable);

	/* TODO: if you should merge OSD inside kernel driver, add your code here */

	return ret;
}

/** OSD HW Layer status
 *
 */
int FBDEV_E60_GetOSDEnable(int layer)
{
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.E60_GetOSDEnable, return RET_ERROR, "null handler\n");

	return hw_ctx->func.E60_GetOSDEnable( layer );
}

