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
#include "fbdev_hw_o20.h"
#include "fbdev_hal.h"
#include "osd_reg_o20.h"
#include "osd_shp_reg_o20.h"
#include "osd_afbc_reg_o20.h"
#include "osd_top_reg_o20.h"
#include <linux/workqueue.h>		/**< For working queue */
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
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int OVI_HAL_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern FBDEV_O20_HW_FUNC_T		g_fbdev_o20_cmn_hw_func;	/* O20 HW common func */

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_O20_InitOSDZOrder (void);
LX_FBDEV_CFG_T*	FBDEV_O20_GetCfg(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile OSD_O20_REG_T*			g_osd_o20_reg = NULL;
		 OSD_O20_REG_T*			g_osd_o20_reg_shadow = NULL;

volatile OSD_AFBC_O20_REG_T* 	g_osd_afbc_o20_reg[2] = {NULL,NULL};
		 OSD_AFBC_O20_REG_T* 	g_osd_afbc_o20_reg_shadow[2] = {NULL,NULL};

volatile OSD_SHP_O20_REG_T*		g_osd_shp_o20_reg[2] = {NULL, NULL};
		 OSD_SHP_O20_REG_T*		g_osd_shp_o20_reg_shadow[2] = {NULL, NULL};

volatile OSD_TOP_O20_REG_T*		g_osd_top_o20_reg = NULL;
		 OSD_TOP_O20_REG_T*		g_osd_top_o20_reg_shadow = NULL;

static FBDEV_O20_HW_CTX_T		g_fbdev_o20_hw_ctx;			/* O20 OSD H/W ctrl */

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_O20_AutoDetectOSDHWValue (void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static	FBDEV_HW_CTX_T	_g_fbdev_hw_ctx =
{
	.GetCfg				= FBDEV_O20_GetCfg,
	.RunSuspend			= FBDEV_O20_CMN_RunSuspend,
	.RunResume			= FBDEV_O20_CMN_RunResume,

	.InitHW				= FBDEV_O20_InitHW,
	.ShutdownHW			= FBDEV_O20_ShutdownHW,
	.ExecHWCommand      = FBDEV_O20_CMN_ExecHWCommand,

	.SetOSDEnable		= FBDEV_O20_SetOSDEnable,
	.GetOSDEnable		= FBDEV_O20_GetOSDEnable,

	.InitOSDLayer		= FBDEV_O20_InitOSDLayer,
	.WriteOSDHeader		= FBDEV_O20_WriteOSDHeader,

	.GetZList			= FBDEV_O20_GetZList,
	.SetZList			= FBDEV_O20_SetZList,

	.WriteOSDEndian		= FBDEV_O20_WriteOSDEndian,
	.WriteOSDCSC		= FBDEV_O20_WriteOSDCSC,

	.GetInterruptStatus	= FBDEV_O20_GetInterruptStatus,
	.SetInterruptClear	= FBDEV_O20_SetInterruptClear,
	.SetInterruptEnable	= FBDEV_O20_SetInterruptEnable,

	.SetViewCtrl		= FBDEV_O20_SetViewCtrl,
	.SetConnCtrl		= FBDEV_O20_SetConnCtrl,

	.CreateProc			= FBDEV_O20_CreateProc,
	.ProcHandler		= FBDEV_O20_CMN_ProcHandler,
};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get O20 specific configuration
 *
 *  @return LX_FBDEV_CFG_T
 */
LX_FBDEV_CFG_T*   FBDEV_O20_GetCfg(void)
{
    return NULL;
}

/** initialize O20 specific HW context variables.
 *
 *	@note this function is called before at O20 configure stage NOT at HW initialization stage.
 */
void	FBDEV_O20_InitHWCtx( FBDEV_HW_CTX_T* hal_obj )
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

	/* select the active O20 HW function handler */
	memcpy( &g_fbdev_o20_hw_ctx.func, &g_fbdev_o20_cmn_hw_func, sizeof(FBDEV_O20_HW_FUNC_T));

    for( i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
		g_fbdev_o20_hw_ctx.conn_ctrl[i].conn_type	= g_fbdev_o20_hw_ctx.hw_conn_type;
		g_fbdev_o20_hw_ctx.fbc_ctrl[i].status		= FBDEV_O20_FBC_STATUS_NONE;
		g_fbdev_o20_hw_ctx.sr_ctrl[i].status		= FBDEV_O20_SR_STATUS_OFF;
		g_fbdev_o20_hw_ctx.sr_ctrl[i].coeff[0]		= 0x3FD;
		g_fbdev_o20_hw_ctx.sr_ctrl[i].coeff[1]		= 0x83;
		g_fbdev_o20_hw_ctx.sr_ctrl[i].coeff[2]		= 0x83;
		g_fbdev_o20_hw_ctx.sr_ctrl[i].coeff[3]		= 0x3FD;

		g_fbdev_o20_hw_ctx.sr_ctrl[i].ti_gain		= -1;
	}

	g_fbdev_o20_hw_ctx.mirror_ctrl.status		= FBDEV_O20_MIRROR_NONE;

	memset(&g_fbdev_o20_hw_ctx.ext_render_ctrl, 0x0, sizeof(FBDEV_O20_EXT_RENDER_CTRL_T));

	/* auto detect the default OSD connection and display size etc */
	FBDEV_O20_AutoDetectOSDHWValue( );

	/* initialize hal object
	 * after this function, all fbdev kdriver can get g_fbdev_o20_hw_ctx via g_fbdev_hw_ctx->chip_priv_ctx
	 */
	memcpy(hal_obj, &_g_fbdev_hw_ctx, sizeof(FBDEV_HW_CTX_T));
	hal_obj->chip_priv_ctx = &g_fbdev_o20_hw_ctx;
}

/** detect the default OSD connection
 *	This function will return the default(best) OSD connection setup based on SW, HW info
 *
 *	@note In O20, video path is fixed to UHD display. OSD will use this HW assumption.
 */
static void FBDEV_O20_AutoDetectOSDHWValue (void)
{
	UINT32	osd_fb0_img_val		= LX_MAKE_RES(1920,1080);		/* defualt input image. default 2K resolution */
	UINT32	osd_fb1_img_val		= LX_MAKE_RES(512,2160);		/* defualt input image. as small as possible */
	UINT32	osd_disp_bosd_val	= LX_MAKE_RES(3840,2160);		/* default 4K resolution */
	UINT32	osd_disp_sosd_val	= LX_MAKE_RES(1920,1080);		/* default 2K resolution */
	UINT32 	osd_conn_val		= LX_FBDEV_CONN_OSD_VIDEO_BLEND;/* default path */
	UINT32	osd_pulse_bosd_val	= 0xA000;						/* default pulse timer delay. default 0xA000. see SICDTV-7971 */
	UINT32	osd_pulse_sosd_val	= 0xA000;						/* default pulse timer delay. default 0xA000 */

	UINT32	osd_fb1_8k_img_val	= LX_MAKE_RES(1024,4320);		/* defualt 8k fb1 framebuffer. default 1K*4K */
	UINT32	osd_ext_render_val	= LX_MAKE_RES(1024,4320);		/* default 8k ext framebuffer. default 1K*4K */
	UINT32	osd_ext_render_swsync_hz_val = 15;					/* default 8k ext swsync interval. default 15Hz=66.666 ms */

#ifdef FBDEV_O20_SUPPORT_SW_WA_SICDTV_7971
	UINT32	osd_bosd_fb0_ex_height 		= 2;					/* default fb0 ex height in 2K OSD. default +2 */
	UINT32	osd_bosd_fb0_ex_out_height	= 4;					/* default fb0 ex out height in 2K OSD, default +4 */
#else
	UINT32	osd_bosd_fb0_ex_height		= 0;
	UINT32	osd_bosd_fb0_ex_out_height	= 0;
#endif

	UINT32	osd_disp_path_test_mode	= FALSE;

	/* raxis.lim (2019/10/08)
	 *
	 * 8K Estreamer 가 검증되기 전까지 external render 는 지원하지 않도록 조치함.
	 * 테스트를 위해서는 bootopts 에서 "osd.fb.ext_frc=1" 이 설정되어야 함.
	 *
	 * 향후 공식 지원이 되는 경우에는 아래 변수 사용 부분을 삭제할것
	 */
	int		osd_ext_rennder_official_support = 0;

	FBDEV_O20_HW_CTX_T* hw_ctx = &g_fbdev_o20_hw_ctx;

	/* make the initial HW WA config */
	hw_ctx->hw_wa_flag= 0x0;

	/* read HW configuration by parsing some kernel parameters */
	{
		if(lx_board_opt() & LX_BOARD_OPT_EXT_FRC)
		{
			printk("<!> fbdev S.OSD detected\n");
			osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE;
		}

		if(lx_board_opt() & LX_BOARD_OPT_4K_GRAPHIC)
		{
			printk("<!> fbdev 4KOSD detected\n");
			osd_fb0_img_val	= LX_MAKE_RES(3840,2160);

			osd_bosd_fb0_ex_height = 0;
			osd_bosd_fb0_ex_out_height = 0;
		}
	}

	/* setup fb(1) based on the default configuration.
	   it's webOS TV specific feature. if B.OSD path, disable fb(1) by configuring the minimal size */
	if(FBDEV_O20_POSD_NUM>=2)
	{
		hw_ctx->b_support_fb1 = TRUE;
		osd_fb1_img_val = LX_MAKE_RES(FBDEV_O20_POSD1_WIDTH, FBDEV_O20_POSD1_HEIGHT);
	}
	else if(FBDEV_O20_POSD_NUM==1)
	{
		hw_ctx->b_support_fb1 = FALSE;
	}

	/* get HW display option from OVI */
	hw_ctx->b_support_ext_frc = FALSE;
	hw_ctx->b_support_ext_fb1_renderer = FALSE;

	{
		LX_OVI_HW_DISPLAY_INFO_T disp_info;

		if(OVI_HAL_GetHWDisplayOption(&disp_info) == RET_OK)
		{
			if(disp_info.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F20)
			{
				hw_ctx->b_support_ext_frc = TRUE;

				printk("+ osd_ext_rennder_official_support=1, official version\n");
				osd_ext_rennder_official_support = 1;
			}
			else if( disp_info.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
			{
				printk("+ FHD display support\n");
				osd_disp_bosd_val = LX_MAKE_RES(1920,1080);
				osd_fb1_img_val = LX_MAKE_RES(256, 1080);
			}
		}
	}

	/* scan test options for internal use only */
	{
		char	opt[32];
		UINT32	fbnum, val, res_w, res_h;

		if(RET_OK==OS_ScanKernelCmdline("osd.disp.path=%s", opt))
		{
			if(!strncmp(opt,"sosd",4))
			{
				osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE;
				hw_ctx->b_support_ext_frc = TRUE;
			}
			else if(!strncmp(opt,"bosd",4))
			{
				osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_BLEND;
			}

			osd_disp_path_test_mode = TRUE; /* keep current osd path regardless of the real HW config */
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
			else if (fbnum==1)
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
				hw_ctx->b_support_ext_fb1_renderer = TRUE;
			}
		}

		if(RET_OK==OS_ScanKernelCmdline("osd.fb.fbext=%s", opt))
		{
			sscanf(opt, "%dx%d@%d", &res_w, &res_h, &val);
			osd_ext_render_val = LX_MAKE_RES(res_w, res_h);
			osd_ext_render_swsync_hz_val = val;
		}

		/* support F20 ext_frc emulation regardless of F20 */
		if(RET_OK==OS_ScanKernelCmdline("osd.ext_frc=%s", opt))
		{
			sscanf(opt, "%d", &val);

			if (val==1)
			{
				hw_ctx->b_support_ext_frc = 1;

				FBDEV_NOTI("<!> osd_ext_rennder_official_support=1, test version\n");
				osd_ext_rennder_official_support = 1;
			}
			else if (val==0)
			{
				hw_ctx->b_support_ext_frc = 0;

				FBDEV_NOTI("<!> osd_ext_rennder_official_support=0, test version\n");
				osd_ext_rennder_official_support = 0;
			}
		}
	}

	if(hw_ctx->b_support_ext_frc)
	{
		printk("+ osd.conn_val = EXT_FRC(F20) detected. enable 8k ext_renderer\n");

		/* if path test mode is enabled, keep the current osd_conn_val */
		if(osd_disp_path_test_mode)
		{
			printk("+ osd_disp_path_test_mode = 0x%x\n", osd_conn_val);
		}
		else
		{
			osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE;
		}

		hw_ctx->b_support_fb1 = TRUE;

		if(osd_ext_rennder_official_support)
		{
			hw_ctx->b_support_ext_fb1_renderer = TRUE;
			osd_fb1_img_val = osd_fb1_8k_img_val;
		}
	}
	else
	{
		printk("+ osd.conn_val = EXT_FRC(F20) not detected. disable 8k ext_renderer\n");
		osd_ext_render_val = 0x0;
	}

	hw_ctx->sosd_disp.fb0_width  = LX_RES_GET_WIDTH(osd_fb0_img_val);
	hw_ctx->sosd_disp.fb0_height = LX_RES_GET_HEIGHT(osd_fb0_img_val);
	hw_ctx->sosd_disp.fb1_width  = LX_RES_GET_WIDTH(osd_fb1_img_val);
	hw_ctx->sosd_disp.fb1_height = LX_RES_GET_HEIGHT(osd_fb1_img_val);
	hw_ctx->sosd_disp.out_width	 = LX_RES_GET_WIDTH(osd_disp_sosd_val);	/* S.OSD size is fixed to 1920x1080 */
	hw_ctx->sosd_disp.out_height = LX_RES_GET_HEIGHT(osd_disp_sosd_val);
	hw_ctx->sosd_disp.pulse_timer_dly = osd_pulse_sosd_val;

	hw_ctx->sosd_disp.fb0_ex_height 	= 0;
	hw_ctx->sosd_disp.fb0_ex_out_height = 0;

	hw_ctx->bosd_disp.fb0_width  = LX_RES_GET_WIDTH(osd_fb0_img_val);
	hw_ctx->bosd_disp.fb0_height = LX_RES_GET_HEIGHT(osd_fb0_img_val);
	hw_ctx->bosd_disp.fb1_width  = LX_RES_GET_WIDTH(osd_fb1_img_val);
	hw_ctx->bosd_disp.fb1_height = LX_RES_GET_HEIGHT(osd_fb1_img_val);
	hw_ctx->bosd_disp.out_width  = LX_RES_GET_WIDTH(osd_disp_bosd_val);	/* B.OSD size might be changed based on DTV config */
	hw_ctx->bosd_disp.out_height = LX_RES_GET_HEIGHT(osd_disp_bosd_val);
	hw_ctx->bosd_disp.pulse_timer_dly = osd_pulse_bosd_val;

	hw_ctx->bosd_disp.fb0_ex_height 	= osd_bosd_fb0_ex_height;
	hw_ctx->bosd_disp.fb0_ex_out_height = osd_bosd_fb0_ex_out_height;

#ifdef FBDEV_O20_2X_CURSOR_ON_BLEND_PATH
	hw_ctx->bosd_disp.b_2x_cursor_disp = TRUE;
#else
	hw_ctx->bosd_disp.b_2x_cursor_disp = FALSE;
#endif

#ifdef FBDEV_O20_SUPPORT_4KOSD
	/* raxis.lim (2019/05/21) -- we should support 4K OSD display !! */
	if (LX_RES_GET_WIDTH(osd_fb0_img_val) >= 2048)
	{
		hw_ctx->b_support_4kosd = TRUE;
		hw_ctx->bosd_disp.fb0_ex_height = 0;
		hw_ctx->bosd_disp.fb0_ex_out_height = 0;
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

		hw_ctx->hw_fb0_ex_height	= hw_ctx->bosd_disp.fb0_ex_height;
		hw_ctx->hw_fb0_ex_out_height= hw_ctx->bosd_disp.fb0_ex_out_height;
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

		hw_ctx->hw_fb0_ex_height	= hw_ctx->sosd_disp.fb0_ex_height;
		hw_ctx->hw_fb0_ex_out_height= hw_ctx->sosd_disp.fb0_ex_out_height;
	}

	hw_ctx->hw_ext_render_width		= LX_RES_GET_WIDTH(osd_ext_render_val);
	hw_ctx->hw_ext_render_height	= LX_RES_GET_HEIGHT(osd_ext_render_val);
	hw_ctx->hw_ext_render_swsync_hz = osd_ext_render_swsync_hz_val;

	hw_ctx->hw_conn_type 			= osd_conn_val;
	hw_ctx->hw_wa_flag				|= FBDEV_O20_HW_WA_1X_CSR_DISP_ON_BLEND_PATH;

	printk("OSD HW conn=0x%x, fb0=%dx%d fb1=%dx%d disp=%dx%d ext_render=%d,%dx%d@%dHz wa_flag=0x%08x\n",
			hw_ctx->hw_conn_type,
			hw_ctx->hw_fb0_width, hw_ctx->hw_fb0_height,
			hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height,
			hw_ctx->hw_disp_width, hw_ctx->hw_disp_height,
			hw_ctx->b_support_ext_fb1_renderer,
			hw_ctx->hw_ext_render_width, hw_ctx->hw_ext_render_height, hw_ctx->hw_ext_render_swsync_hz,
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
int FBDEV_O20_InitHW (void)
{
	int ret = RET_ERROR;

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	/* ioremap TOP regs */
	if (NULL==g_osd_top_o20_reg)
	{
		g_osd_top_o20_reg =(OSD_TOP_O20_REG_T*)ioremap(O20_CCO_TOP_CTRL_BASE, sizeof(OSD_TOP_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_top_o20_reg, goto func_exit, "out of mem\n");

	if (NULL==g_osd_top_o20_reg_shadow)
	{
		g_osd_top_o20_reg_shadow =(OSD_TOP_O20_REG_T*)OS_Malloc(sizeof(OSD_TOP_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_top_o20_reg_shadow, goto func_exit, "out of mem\n");

	/* ioremap OSD regs */
	if (NULL==g_osd_o20_reg)
	{
		g_osd_o20_reg =(OSD_O20_REG_T*)ioremap(O20_CCO_BASE, sizeof(OSD_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_o20_reg, goto func_exit, "out of mem\n");

	if (NULL==g_osd_o20_reg_shadow)
	{
		g_osd_o20_reg_shadow = (OSD_O20_REG_T*)OS_Malloc(sizeof(OSD_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_o20_reg_shadow, return RET_ERROR, "out of mem\n");

	/* ioremap OSD_SHP(0) regs */
	if (NULL==g_osd_shp_o20_reg[0])
	{
		g_osd_shp_o20_reg[0] =(OSD_SHP_O20_REG_T*)ioremap(O20_CCO_SHP0_BASE, sizeof(OSD_SHP_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_o20_reg[0], goto func_exit, "out of mem\n");

	if (NULL==g_osd_shp_o20_reg_shadow[0])
	{
		g_osd_shp_o20_reg_shadow[0] = (OSD_SHP_O20_REG_T*)OS_Malloc(sizeof(OSD_SHP_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_o20_reg_shadow[0], return RET_ERROR, "out of mem\n");

	/* ioremap OSD_SHP(1) regs */
	if (NULL==g_osd_shp_o20_reg[1])
	{
		g_osd_shp_o20_reg[1] =(OSD_SHP_O20_REG_T*)ioremap(O20_CCO_SHP1_BASE, sizeof(OSD_SHP_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_o20_reg[1], goto func_exit, "out of mem\n");

	if (NULL==g_osd_shp_o20_reg_shadow[1])
	{
		g_osd_shp_o20_reg_shadow[1] = (OSD_SHP_O20_REG_T*)OS_Malloc(sizeof(OSD_SHP_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_o20_reg_shadow[1], return RET_ERROR, "out of mem\n");

	/* ioremap OSD_AFBC(0) regs */
	if (NULL==g_osd_afbc_o20_reg[0])
	{
		g_osd_afbc_o20_reg[0]=(OSD_AFBC_O20_REG_T*)ioremap(O20_CCO_AFBC0_BASE, sizeof(OSD_AFBC_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_o20_reg[0], goto func_exit, "out of mem\n");

	if (NULL==g_osd_afbc_o20_reg_shadow[0])
	{
		g_osd_afbc_o20_reg_shadow[0] = (OSD_AFBC_O20_REG_T*)OS_Malloc(sizeof(OSD_AFBC_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_o20_reg_shadow[0], return RET_ERROR, "out of mem\n");

	/* ioremap OSD_AFBC(1) regs */
	if (NULL==g_osd_afbc_o20_reg[1])
	{
		g_osd_afbc_o20_reg[1]=(OSD_AFBC_O20_REG_T*)ioremap(O20_CCO_AFBC1_BASE, sizeof(OSD_AFBC_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_o20_reg[1], goto func_exit, "out of mem\n");

	if (NULL==g_osd_afbc_o20_reg_shadow[1])
	{
		g_osd_afbc_o20_reg_shadow[1] = (OSD_AFBC_O20_REG_T*)OS_Malloc(sizeof(OSD_AFBC_O20_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_o20_reg_shadow[1], return RET_ERROR, "out of mem\n");

	/* raxis.lim (2014/06/18)
	 * CCO init param is too difficult to understand :(
	 * ask woonghyun.kim if you have any question. he knows everything !!
	 *
	 * let's summarize all that I know
	 * CCO_CTRL_BASE+0x08 controls osd pluse source selections
	 * 0x5 : used for BLEND path (non-compressed)
	 * 0x7 : used for SEP path   (non-compressed)
	 */
	if(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		OSD_TOP_O20_Wr(ctrl_auto_init, 0x55555555);
		OSD_TOP_O20_Wr(ctrl_intr_pulse, 0xCA876420);

		OSD_TOP_O20_Wr(ctrl_spath, 0x00000D80);
	}
	else /* SEP */
	{
		OSD_TOP_O20_Wr(ctrl_auto_init, 0x55555555);

		OSD_TOP_O20_Wr(ctrl_intr_pulse, 0xCAC76420);
		OSD_TOP_O20_Wr(ctrl_spath, 0x00380D80);

		/* raxis.lim (2019/07/12)
	 	 * 2K sync. refer to http://clm.lge.com/issue/browse/SICDTV-7090 */
		FBDEV_WARN("++ 2k s.osd sync_gen\n");
        OSD_TOP_O20_Wr(osd_sync_gen_ctrl0, 0x00040005);
        OSD_TOP_O20_Wr(osd_sync_gen_ctrl1, 0x00240438);
        OSD_TOP_O20_Wr(osd_sync_gen_ctrl2, 0x0058002C);
        OSD_TOP_O20_Wr(osd_sync_gen_ctrl3, 0x00940780);
        OSD_TOP_O20_Wr(osd_sync_gen_ctrl4, 0x00040005);
        OSD_TOP_O20_Wr(osd_sync_gen_ctrl5, 0x00240438);
        OSD_TOP_O20_Wr(osd_sync_gen_ctrl6, 0x0001006F);
        OSD_TOP_O20_Wr(osd_sync_gen_ctrl7, 0x00080058);
	}

	/* raxis.lim (2016/03/28) -- ctrl_intr_pulse, ctrl_dpath, ctrl_spath is set by HW default value
	 * raxis.lim (2016/10/05) -- keep AFBC status becuase boot loader can display AFBC logo image
	 * raxis.lim (2019/08/06) -- DO NOT full value to ctrl_dpath. refer to http://clm.lge.com/issue/browse/AVTASK-386?focusedCommentId=1964037&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-1964037
	 * raxis.lim (2019/10/15) -- setup fb(1) based on hw_ctx->b_support_ext_fb1_renderer
	 */
	OSD_TOP_O20_RdFL(ctrl_dpath);

	if(FBDEV_O20_CMN_GetHWStatus(FBDEV_O20_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0))
	{
		OSD_TOP_O20_Wr01(ctrl_dpath, osd0_afbc_en, 0x1);
	}
	else
	{
		OSD_TOP_O20_Wr01(ctrl_dpath, osd0_afbc_en, 0x0);
	}

	if(FBDEV_O20_CMN_GetHWStatus(FBDEV_O20_HW_STATUS_AFBC, LX_FBDEV_ID_OSD1) && 
	   hw_ctx->b_support_ext_fb1_renderer == FALSE)
	{
		OSD_TOP_O20_Wr01(ctrl_dpath, osd1_afbc_en, 0x1);
	}
	else
	{
		OSD_TOP_O20_Wr01(ctrl_dpath, osd1_afbc_en, 0x0);
	}

	OSD_TOP_O20_WrFL(ctrl_auto_init);
	OSD_TOP_O20_WrFL(ctrl_intr_pulse);

	OSD_TOP_O20_WrFL(ctrl_dpath);
	OSD_TOP_O20_WrFL(ctrl_spath);

	if(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{

	}
	else
	{
        OSD_TOP_O20_WrFL(osd_sync_gen_ctrl0);
        OSD_TOP_O20_WrFL(osd_sync_gen_ctrl1);
        OSD_TOP_O20_WrFL(osd_sync_gen_ctrl2);
        OSD_TOP_O20_WrFL(osd_sync_gen_ctrl3);
        OSD_TOP_O20_WrFL(osd_sync_gen_ctrl4);
        OSD_TOP_O20_WrFL(osd_sync_gen_ctrl5);
        OSD_TOP_O20_WrFL(osd_sync_gen_ctrl6);
        OSD_TOP_O20_WrFL(osd_sync_gen_ctrl7);
	}

	if(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		/* do nothing
		 * I confirmed that OSD display works well even when OSD path is changed from S.OSD to B.OSD.
		 * It means that osd_sync_gen registers don't affect OSD path.
		 */
	}
	else
	{
		/* O18 참고해 봅시다 */

	}

 	if (FBDEV_O20_CMN_IsUHDDispMode())
	{
		FBDEV_WARN("++ UHD mode : pic_init_timer config\n");

		/* raxis.lim (2019/05/23)
	 	 * OSD_IMAGE1 (E-Stremaer) 에서는 pic_init 0 값 설정 중요함. (SICDTV-6809 참조)
		 * 만약 0xa000 값을 사용하게 되면, E-Streamer OSD 의 오프셋이 틀어지거나, OSD 가 흐름.
		 *
		 * 결론은 use the default configuration 0x7000_0000
		 */
		OSD_TOP_O20_Wr(pic_init_g0_timer, 0x70000000);
		OSD_TOP_O20_Wr(pic_init_g1_timer, 0x70000000);
		OSD_TOP_O20_Wr(pic_init_g2_timer, 0x70000000);
		OSD_TOP_O20_Wr(pic_init_g3_timer, 0x70000000);
		OSD_TOP_O20_Wr(pic_init_g4_timer, 0x70000000);
		OSD_TOP_O20_Wr(pic_init_g5_timer, 0x70000000);
		OSD_TOP_O20_Wr(pic_init_g6_timer, 0x70000000);
		OSD_TOP_O20_Wr(pic_init_g7_timer, 0x70000000);

		OSD_TOP_O20_WrFL(pic_init_g0_timer);
		OSD_TOP_O20_WrFL(pic_init_g1_timer);
		OSD_TOP_O20_WrFL(pic_init_g2_timer);
		OSD_TOP_O20_WrFL(pic_init_g3_timer);
		OSD_TOP_O20_WrFL(pic_init_g4_timer);
		OSD_TOP_O20_WrFL(pic_init_g5_timer);
		OSD_TOP_O20_WrFL(pic_init_g6_timer);
		OSD_TOP_O20_WrFL(pic_init_g7_timer);
	}
	else
	{
		FBDEV_WARN("++ non-UHD mode : pic_init_timer config (not tested yet)\n");
		OSD_TOP_O20_Wr(pic_init_g0_timer, 0x00000000);
		OSD_TOP_O20_Wr(pic_init_g1_timer, 0x00000000);
		OSD_TOP_O20_Wr(pic_init_g2_timer, 0x00000000);
		OSD_TOP_O20_Wr(pic_init_g3_timer, 0x00000000);
		OSD_TOP_O20_Wr(pic_init_g4_timer, 0x00000000);
		OSD_TOP_O20_Wr(pic_init_g5_timer, 0x00000000);
		OSD_TOP_O20_Wr(pic_init_g6_timer, 0x00000000);
		OSD_TOP_O20_Wr(pic_init_g7_timer, 0x00000000);

		OSD_TOP_O20_WrFL(pic_init_g0_timer);
		OSD_TOP_O20_WrFL(pic_init_g1_timer);
		OSD_TOP_O20_WrFL(pic_init_g2_timer);
		OSD_TOP_O20_WrFL(pic_init_g3_timer);
		OSD_TOP_O20_WrFL(pic_init_g4_timer);
		OSD_TOP_O20_WrFL(pic_init_g5_timer);
		OSD_TOP_O20_WrFL(pic_init_g6_timer);
		OSD_TOP_O20_WrFL(pic_init_g7_timer);
	}

	/* configure MIF to show OSD with ARGB color
	 *
	 * raxis.lim (2019/05/24)
	 *
	 * wr 0XC9010C20 0x400000FB 	# R_OSD0_MB_REQ.req_msk_f_on=0 (for UI)
	 * wr 0XC9010C60 0x400000FB 	# R_CSR0_MB_REQ.req_msk_f_on=0 (for CURSOR)
	 * wr 0XC9012820 0x400000FB 	# R_OSD1_MB_REQ.req_msk_f_on=0 (for E-Streamer)
	 *
	 * MIF1req_msk_f_on=1 설정시 IMAGE1 ARGB 출력시 화면이 보이지 않음. (SICDTV-6809 참조)
	 */
	OS_WrReg(O20_CCO_MIF0_BASE+0x20, 0x400000FB);
	OS_WrReg(O20_CCO_MIF0_BASE+0x60, 0x400000FA);
	OS_WrReg(O20_CCO_MIF1_BASE+0x20, 0x400000FB);

	/* HW revision specific initialization */
	FBDEV_O20_InitOSDZOrder();

	FBDEV_O20_CMN_InitHW();

	/* refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT */
	if (!(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR))
	{
		if(hw_ctx->user_initcall_ctrl.ready)
		{
			FBDEV_NOTI("++ PIC_INIT ++ (NORMAL)\n");
			OSD_TOP_O20_RdFL(pic_init);
			OSD_TOP_O20_Wr01(pic_init, g0_auto_init, 0x1);
			OSD_TOP_O20_Wr01(pic_init, g1_auto_init, 0x1);
			OSD_TOP_O20_Wr01(pic_init, g4_auto_init, 0x1);
			OSD_TOP_O20_WrFL(pic_init);
		}
	}

	/* migrate LG Logo Image at kdriver initialization */
	FBDEV_O20_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_KEEP);

	ret = RET_OK; /* all work done */
func_exit:
	return ret;
}

/** de-initial OSD IP HW and register
 *
 * @param
 * @return	int 0 : OK , -1 : NOT OK
 *
 * [OK]
 */
int FBDEV_O20_ShutdownHW	(void)
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
void FBDEV_O20_InitOSDZOrder ( void )
{
	/* do nothing */
}

/** Update OSD zorder
 *
 * @param zList [IN] pointer to POSD List config.
 * @return RET_OK
 *
 * @note layer id definition is 03: video, 00: OSD0, 01: OSD1, 02: OSD2 ( refer to OSD register manual )
 * @note I will not use osd_mixer_ctrl_mux0.layer_mux_3 ( it's default value is POSD2 )
 *
 * @note somewhat obsolete function !
 */
int FBDEV_O20_SetZList ( LX_FBDEV_ZLIST_T* zList )
{

	return RET_OK;
}

/** Get OSD ZList
 *
 * @param zList [OUT] pointer to POSD List config.
 * @return RET_OK
 *
 * @note layer id definition is 00: video, 01: OSD0, 02: OSD1, 03: OSD2
 * @note O20 doesn't support L&R zlist.
 * @note I will not use osd_mixer_ctrl_mux0.layer_mux_3 ( it's default value is POSD2 )
 *
 * @note somewhat obsolete function !
 */
int FBDEV_O20_GetZList( LX_FBDEV_ZLIST_T* zList )
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
 */
int FBDEV_O20_WriteOSDEndian(int fb_dev_id, ENDIAN_INFORM_T *endian)
{
    return RET_OK;
}

/** set color space conversion on each layer
 *
 *	@note O20 doesn't support CSC for each layer
 *
 */
int FBDEV_O20_WriteOSDCSC(int layer , CSC_INFORM_T *csc)
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
int FBDEV_O20_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
	UINT32	status = 0;

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	OSD_O20_RdFL(osd_common_ctrl_irq);

	if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
	{
		UINT32 bosd_mixer;
		OSD_O20_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, bosd_mixer );

		if(bosd_mixer)	status |= (1<<MIXER_INTR);
		else			printk("OSD ISR - BOSD MIXER INTR error\n");
	}
	else
	{
		UINT32 sosd_mixer;
		OSD_O20_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, sosd_mixer );

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
int FBDEV_O20_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
	OSD_O20_RdFL(osd_common_ctrl_irq);

	/* clear both bosd, sosd mixer intr for the safe operation */
	OSD_O20_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, 0x1 );
	OSD_O20_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, 0x1 );

	OSD_O20_WrFL(osd_common_ctrl_irq);

	return RET_OK;
}

/** Set interrupt enable/disable
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T , int : enable/disable
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_O20_SetInterruptEnable(INTERRUPT_INFORM_T intr , int enable)
{
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

    switch(intr)
    {
		default:
        case MIXER_INTR:
		{
			OSD_O20_RdFL(osd_common_ctrl_irq);
			if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
			{
				FBDEV_DEBUG("INTR <%s> for B.OSD\n", enable? "ON":"OFF" );
				OSD_O20_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bos, enable );
				OSD_O20_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sos, 0x0 );
			}
			else
			{
				FBDEV_DEBUG("INTR <%s> for S.OSD\n", enable? "ON":"OFF" );
				OSD_O20_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bos, 0x0 );
				OSD_O20_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sos, enable );
			}
			OSD_O20_WrFL(osd_common_ctrl_irq);
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
int	FBDEV_O20_InitOSDLayer	(int layer)
{
	return FBDEV_O20_CMN_InitOSDLayer(layer);
}

/*========================================================================================
	Implementation Group (REV dependent)
========================================================================================*/
int		FBDEV_O20_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl)
{
	int	ret = RET_ERROR;
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O20_SetViewCtrl, return RET_ERROR, "null handler\n");

	ret = hw_ctx->func.O20_SetViewCtrl(ctrl);

	/* TODO: if you should merge OSD inside kernel driver, add your code here */

	return ret;
}

/** set OSD output ctrl
 *
 */
int     FBDEV_O20_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl)
{
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O20_SetConnCtrl, return RET_ERROR, "null handler\n");

	return hw_ctx->func.O20_SetConnCtrl(ctrl);
}

/** Set Header information
 *
 */
int FBDEV_O20_WriteOSDHeader(struct scanvas *hCanvas)
{
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O20_WriteOSDHeader, return RET_ERROR, "null handler\n");

	return hw_ctx->func.O20_WriteOSDHeader(hCanvas);
}

/** OSD HW Layer enable/disable
 *
 */
int FBDEV_O20_SetOSDEnable(int layer, int enable)
{
	int	ret = RET_ERROR;
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O20_SetOSDEnable, return RET_ERROR, "null handler\n");

	ret = hw_ctx->func.O20_SetOSDEnable(layer, enable);

	/* TODO: if you should merge OSD inside kernel driver, add your code here */

	return ret;
}

/** OSD HW Layer status
 *
 */
int FBDEV_O20_GetOSDEnable(int layer)
{
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O20_GetOSDEnable, return RET_ERROR, "null handler\n");

	return hw_ctx->func.O20_GetOSDEnable( layer );
}

