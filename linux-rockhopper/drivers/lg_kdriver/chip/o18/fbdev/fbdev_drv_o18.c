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
#include "fbdev_hw_o18.h"
#include "fbdev_hal.h"
#include "osd_reg_o18.h"
#include "osd_shp_reg_o18.h"
#include "osd_scan_reg_o18.h"
#include "osd_afbc_reg_o18.h"
#include "top_ctrl_osd_reg_o18.h"
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

#include "../sys/ctop_regs.h"

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

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern FBDEV_O18_HW_FUNC_T		g_fbdev_o18_cmn_hw_func;	/* O18 HW common func */

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_O18_InitOSDZOrder (void);
LX_FBDEV_CFG_T*	FBDEV_O18_GetCfg(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile OSD_AFBC_O18_REG_T* 	g_osd_afbc_o18_reg = NULL;
		 OSD_AFBC_O18_REG_T* 	g_osd_afbc_o18_reg_shadow = NULL;

volatile OSD_O18_REG_T*			g_osd_o18_reg = NULL;
		 OSD_O18_REG_T*			g_osd_o18_reg_shadow = NULL;

volatile OSD_SHP_O18_REG_T*		g_osd_shp_o18_reg = NULL;
		 OSD_SHP_O18_REG_T*		g_osd_shp_o18_reg_shadow = NULL;

volatile OSD_SCAN_O18_REG_T*	g_osd_scan_o18_reg = NULL;
		 OSD_SCAN_O18_REG_T*	g_osd_scan_o18_reg_shadow = NULL;

volatile OSD_TOP_O18_REG_T*		g_osd_top_o18_reg = NULL;
		 OSD_TOP_O18_REG_T*		g_osd_top_o18_reg_shadow = NULL;

static FBDEV_O18_HW_CTX_T		g_fbdev_o18_hw_ctx;			/* O18 OSD H/W ctrl */

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_O18_AutoDetectOSDHWValue (void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static	FBDEV_HW_CTX_T	_g_fbdev_hw_ctx =
{
	.GetCfg				= FBDEV_O18_GetCfg,
	.RunSuspend			= FBDEV_O18_CMN_RunSuspend,
	.RunResume			= FBDEV_O18_CMN_RunResume,

	.InitHW				= FBDEV_O18_InitHW,
	.ShutdownHW			= FBDEV_O18_ShutdownHW,
	.ExecHWCommand      = FBDEV_O18_CMN_ExecHWCommand,

	.SetOSDEnable		= FBDEV_O18_SetOSDEnable,
	.GetOSDEnable		= FBDEV_O18_GetOSDEnable,

	.InitOSDLayer		= FBDEV_O18_InitOSDLayer,
	.WriteOSDHeader		= FBDEV_O18_WriteOSDHeader,

	.GetZList			= FBDEV_O18_GetZList,
	.SetZList			= FBDEV_O18_SetZList,

	.WriteOSDEndian		= FBDEV_O18_WriteOSDEndian,
	.WriteOSDCSC		= FBDEV_O18_WriteOSDCSC,

	.GetInterruptStatus	= FBDEV_O18_GetInterruptStatus,
	.SetInterruptClear	= FBDEV_O18_SetInterruptClear,
	.SetInterruptEnable	= FBDEV_O18_SetInterruptEnable,

	.SetViewCtrl		= FBDEV_O18_SetViewCtrl,
	.SetConnCtrl		= FBDEV_O18_SetConnCtrl,

	.CreateProc			= FBDEV_O18_CreateProc,
	.ProcHandler		= FBDEV_O18_CMN_ProcHandler,
};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get O18 specific configuration
 *
 *  @return LX_FBDEV_CFG_T
 */
LX_FBDEV_CFG_T*   FBDEV_O18_GetCfg(void)
{
    return NULL;
}

/** initialize O18 specific HW context variables.
 *
 *	@note this function is called before at O18 configure stage NOT at HW initialization stage.
 */
void	FBDEV_O18_InitHWCtx( FBDEV_HW_CTX_T* hal_obj )
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

	/* select the active O18 HW function handler */
	memcpy( &g_fbdev_o18_hw_ctx.func, &g_fbdev_o18_cmn_hw_func, sizeof(FBDEV_O18_HW_FUNC_T));

    for( i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
		g_fbdev_o18_hw_ctx.conn_ctrl[i].conn_type	= g_fbdev_o18_hw_ctx.hw_conn_type;
		g_fbdev_o18_hw_ctx.fbc_ctrl[i].status		= FBDEV_O18_FBC_STATUS_NONE;
		g_fbdev_o18_hw_ctx.sr_ctrl[i].status		= FBDEV_O18_SR_STATUS_OFF;
		g_fbdev_o18_hw_ctx.sr_ctrl[i].coeff[0]		= 0x3FD;
		g_fbdev_o18_hw_ctx.sr_ctrl[i].coeff[1]		= 0x83;
		g_fbdev_o18_hw_ctx.sr_ctrl[i].coeff[2]		= 0x83;
		g_fbdev_o18_hw_ctx.sr_ctrl[i].coeff[3]		= 0x3FD;

		g_fbdev_o18_hw_ctx.sr_ctrl[i].ti_gain		= -1;
	}

	g_fbdev_o18_hw_ctx.mirror_ctrl.status	= FBDEV_O18_MIRROR_NONE;

	/* auto detect the default OSD connection and display size etc */
	FBDEV_O18_AutoDetectOSDHWValue( );

	/* initialize hal object
	 * after this function, all fbdev kdriver can get g_fbdev_o18_hw_ctx via g_fbdev_hw_ctx->chip_priv_ctx
	 */
	memcpy(hal_obj, &_g_fbdev_hw_ctx, sizeof(FBDEV_HW_CTX_T));
	hal_obj->chip_priv_ctx = &g_fbdev_o18_hw_ctx;
}

/** detect the default OSD connection
 *	This function will return the default(best) OSD connection setup based on SW, HW info
 *
 *	@note In O18, video path is fixed to UHD display. OSD will use this HW assumption.
 */
static void FBDEV_O18_AutoDetectOSDHWValue (void)
{
	UINT32	osd_disp_img_val	= LX_MAKE_RES(1920,1080);		/* defualt input image. default 2K resolution */
	UINT32	osd_disp_bosd_val	= LX_MAKE_RES(3840,2160);		/* default 4K resolution */
	UINT32	osd_disp_sosd_val	= LX_MAKE_RES(1920,1080);		/* default 2K resolution */
	UINT32 	osd_conn_val		= FBDEV_O18_DEFAULT_OSD_PATH; 	/* default path */
	UINT32	osd_pulse_bosd_val	= 0x3000;						/* default pulse timer delay. default 0x3000 */
	UINT32	osd_pulse_sosd_val	= 0x3000;						/* default pulse timer delay. default 0x3000 */
	BOOLEAN	b_support_3dosd 	= TRUE; 						/* support 3DOSD by default */

	UINT32	osd_disp_fhd_val	= LX_MAKE_RES(1920,1080);		/* HD/FHD display resolution */

	/* read HW configuration by parsing some kernel parameters */
	{
		char	opt[32];

		/* osd.path == b.osd/s.osd (internal test only) */
		if(RET_OK==OS_ScanKernelCmdline("osd.path=%s", opt))
		{
			if(!strncmp(opt,"b.osd",5))			/* UHD panel, UHD scaled out */
			{
				osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_BLEND;
				b_support_3dosd = TRUE;
			}
			else if(!strncmp(opt,"s.osd",5))	/* UHD panel ? FHD out */
			{
				osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE;
				b_support_3dosd = FALSE;
			}
		}
		else if(RET_OK==OS_ScanKernelCmdline("hwopt=%s", opt))
		{
			/* hwopt[17] == 0 : OSD is set to B.OSD due to NO_FRC */
			switch(opt[17])
			{
				case '0':
				case '1': osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_BLEND; 	b_support_3dosd = TRUE;  break;
				default:  osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_SEPARATE; 	b_support_3dosd = FALSE; break;
			}

			/* hwopt[3] == 0 : HD specific resolution handler */
			if(opt[3] == '0')
			{
#ifdef FBDEV_O18_USE_HD_DISP_HANDLER
				osd_disp_fhd_val = LX_MAKE_RES(1376, 768); osd_disp_img_val = LX_MAKE_RES(1376, 768);
#else
				osd_disp_fhd_val = LX_MAKE_RES(1920, 768); osd_disp_img_val = LX_MAKE_RES(1920, 768);
#endif
			}
		}

		g_fbdev_o18_hw_ctx.hw_conn_type = osd_conn_val;

#if 0
		/* test image resolution */
		if(RET_OK==OS_ScanKernelCmdline("osd.imgres=%s", opt))
		{
			UINT32	img_w, img_h;
			sscanf(opt, "%dx%d", &img_w, &img_h);

			osd_disp_img_val = LX_MAKE_RES(img_w, img_h);
		}
#endif
		/* support HD/FHD model such as signage, hoteltv */
		if(lx_chip_plt() == LX_CHIP_PLT_FHD)
		{
			osd_disp_bosd_val = osd_disp_fhd_val;
			osd_disp_sosd_val = osd_disp_fhd_val;
		}
	}

	/* support settbox mode. scan settop output resolution */
	{
		char	opt[32];

		int		stb_w, stb_h;
		UINT32	stb_disp_val = LX_MAKE_RES(1920,1080);	/* default 2K resolution */

		/* osd.disp == 4kbosd, 2kbosd, 2ksosd (internal test only) */
		/* osd.path == b.osd/s.osd (internal test only) */
		if(RET_OK==OS_ScanKernelCmdline("stbopts=%s", opt) ||
		   RET_OK==OS_ScanKernelCmdline("osd.res=%s", opt))
		{
			sscanf(opt, "%dx%d@", &stb_w, &stb_h);

			stb_disp_val = LX_MAKE_RES(stb_w, stb_h);
			osd_conn_val = LX_FBDEV_CONN_OSD_VIDEO_BLEND;
			b_support_3dosd = FALSE;

			switch(stb_disp_val)
			{
				case LX_MAKE_RES(1920,1080):
				{
					osd_disp_bosd_val = LX_MAKE_RES(1920,1080);
				}
				break;

				case LX_MAKE_RES(1366,768):
				{
					osd_disp_bosd_val = LX_MAKE_RES(1376,768);
				}
				break;

				case LX_MAKE_RES(1280,720):
				{
					osd_disp_bosd_val = LX_MAKE_RES(1280,720);
					osd_pulse_bosd_val = 0x14000;
				}
				break;


				default:
				{
					osd_disp_bosd_val = LX_MAKE_RES(3840,2160);
				}
				break;
			}
		}
	}

	g_fbdev_o18_hw_ctx.b_support_3dosd = b_support_3dosd;	/* support 3D OSD if there is no backend chip */

	g_fbdev_o18_hw_ctx.sosd_disp.in_width  = LX_RES_GET_WIDTH(osd_disp_img_val);
	g_fbdev_o18_hw_ctx.sosd_disp.in_height = LX_RES_GET_HEIGHT(osd_disp_img_val);
	g_fbdev_o18_hw_ctx.sosd_disp.out_width = LX_RES_GET_WIDTH(osd_disp_sosd_val);	/* S.OSD size is fixed to 1920x1080 */
	g_fbdev_o18_hw_ctx.sosd_disp.out_height= LX_RES_GET_HEIGHT(osd_disp_sosd_val);
	g_fbdev_o18_hw_ctx.sosd_disp.pulse_timer_dly = osd_pulse_sosd_val;

	g_fbdev_o18_hw_ctx.bosd_disp.in_width  = LX_RES_GET_WIDTH(osd_disp_img_val);
	g_fbdev_o18_hw_ctx.bosd_disp.in_height = LX_RES_GET_HEIGHT(osd_disp_img_val);
	g_fbdev_o18_hw_ctx.bosd_disp.out_width = LX_RES_GET_WIDTH(osd_disp_bosd_val);	/* B.OSD size might be changed based on DTV config */
	g_fbdev_o18_hw_ctx.bosd_disp.out_height= LX_RES_GET_HEIGHT(osd_disp_bosd_val);
	g_fbdev_o18_hw_ctx.bosd_disp.pulse_timer_dly = osd_pulse_bosd_val;

#ifdef FBDEV_O18_2X_CURSOR_ON_BLEND_PATH
	g_fbdev_o18_hw_ctx.bosd_disp.b_2x_cursor_disp = TRUE;
#else
	g_fbdev_o18_hw_ctx.bosd_disp.b_2x_cursor_disp = FALSE;
#endif

	if (osd_conn_val & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		g_fbdev_o18_hw_ctx.b_keep_hw_conn_type 	= TRUE;
		g_fbdev_o18_hw_ctx.hw_disp_width		= g_fbdev_o18_hw_ctx.bosd_disp.out_width;
		g_fbdev_o18_hw_ctx.hw_disp_height		= g_fbdev_o18_hw_ctx.bosd_disp.out_height;
		g_fbdev_o18_hw_ctx.hw_gfx_width			= g_fbdev_o18_hw_ctx.bosd_disp.in_width;
		g_fbdev_o18_hw_ctx.hw_gfx_height		= g_fbdev_o18_hw_ctx.bosd_disp.in_height;
	}
	else
	{
		g_fbdev_o18_hw_ctx.b_keep_hw_conn_type	= FALSE;
		g_fbdev_o18_hw_ctx.hw_disp_width 		= g_fbdev_o18_hw_ctx.sosd_disp.out_width;
		g_fbdev_o18_hw_ctx.hw_disp_height		= g_fbdev_o18_hw_ctx.sosd_disp.out_height;
		g_fbdev_o18_hw_ctx.hw_gfx_width 		= g_fbdev_o18_hw_ctx.sosd_disp.in_width;
		g_fbdev_o18_hw_ctx.hw_gfx_height		= g_fbdev_o18_hw_ctx.sosd_disp.in_height;
	}

	/* initialize hw_wa flag */
	g_fbdev_o18_hw_ctx.hw_wa_flag				= 0x0;
	g_fbdev_o18_hw_ctx.hw_wa_flag				|= FBDEV_O18_HW_WA_1X_CSR_DISP_ON_BLEND_PATH;

	printk("OSD HW default osd_conn = 0x%x, disp_size = %dx%d, wa = 0x%08x\n",
			g_fbdev_o18_hw_ctx.hw_conn_type,
			g_fbdev_o18_hw_ctx.hw_disp_width, g_fbdev_o18_hw_ctx.hw_disp_height,
			g_fbdev_o18_hw_ctx.hw_wa_flag );
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
int FBDEV_O18_InitHW (void)
{
	int ret = RET_ERROR;

	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	/* ioremap TOP regs */
	if (NULL==g_osd_top_o18_reg)
	{
		g_osd_top_o18_reg =(OSD_TOP_O18_REG_T*)ioremap(CCO_CTRL_BASE, sizeof(OSD_TOP_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_top_o18_reg, goto func_exit, "out of mem\n");

	if (NULL==g_osd_top_o18_reg_shadow)
	{
		g_osd_top_o18_reg_shadow =(OSD_TOP_O18_REG_T*)OS_Malloc(sizeof(OSD_TOP_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_top_o18_reg_shadow, goto func_exit, "out of mem\n");

	/* ioremap OSD regs */
	if (NULL==g_osd_o18_reg)
	{
		g_osd_o18_reg =(OSD_O18_REG_T*)ioremap(CCO_OSD_BASE, sizeof(OSD_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_o18_reg, goto func_exit, "out of mem\n");

	if (NULL==g_osd_o18_reg_shadow)
	{
		g_osd_o18_reg_shadow = (OSD_O18_REG_T*)OS_Malloc(sizeof(OSD_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_o18_reg_shadow, return RET_ERROR, "out of mem\n");

	/* ioremap OSD_SCAN regs */
	if (NULL==g_osd_scan_o18_reg)
	{
		g_osd_scan_o18_reg =(OSD_SCAN_O18_REG_T*)ioremap(CCO_OSD_SCAN_BASE, sizeof(OSD_SCAN_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_scan_o18_reg, goto func_exit, "out of mem\n");

	if (NULL==g_osd_scan_o18_reg_shadow)
	{
		g_osd_scan_o18_reg_shadow = (OSD_SCAN_O18_REG_T*)OS_Malloc(sizeof(OSD_SCAN_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_scan_o18_reg_shadow, return RET_ERROR, "out of mem\n");

	/* ioremap OSD_SHp regs */
	if (NULL==g_osd_shp_o18_reg)
	{
		g_osd_shp_o18_reg =(OSD_SHP_O18_REG_T*)ioremap(CCO_OSD_SHP_BASE, sizeof(OSD_SHP_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_o18_reg, goto func_exit, "out of mem\n");

	if (NULL==g_osd_shp_o18_reg_shadow)
	{
		g_osd_shp_o18_reg_shadow = (OSD_SHP_O18_REG_T*)OS_Malloc(sizeof(OSD_SHP_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_o18_reg_shadow, return RET_ERROR, "out of mem\n");

	/* ioremap OSD_AFBC regs */
	if (NULL==g_osd_afbc_o18_reg)
	{
		g_osd_afbc_o18_reg =(OSD_AFBC_O18_REG_T*)ioremap(CCO_OSD_AFBC_BASE, sizeof(OSD_AFBC_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_o18_reg, goto func_exit, "out of mem\n");

	if (NULL==g_osd_afbc_o18_reg_shadow)
	{
		g_osd_afbc_o18_reg_shadow = (OSD_AFBC_O18_REG_T*)OS_Malloc(sizeof(OSD_AFBC_O18_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_o18_reg_shadow, return RET_ERROR, "out of mem\n");

	/* raxis.lim (2014/06/18)
	 * CCO init param is too difficult to understand :(
	 * ask woonghyun.kim if you have any question. he knows everything !!
	 *
	 * let's summarize all that I know
	 * CCO_CTRL_BASE+0x08 controls osd pluse source selections
	 * 0x5 : used for BLEND path (non-compressed)
	 * 0x7 : used for SEP path   (non-compressed)
	 */
	if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
	{
		OSD_TOP_O18_Wr(ctrl_auto_init, 0x55555555);

		/* raxis.lim (2016/03/28) -- ctrl_intr_pulse, ctrl_dpath, ctrl_spath is set by HW default value */
		OSD_TOP_O18_Wr(ctrl_intr_pulse, 0xCA876420);

		/* raxis.lim (2016/10/05) -- keep AFBC status becuase boot loader can display AFBC logo image */
		OSD_TOP_O18_Wr(ctrl_spath, 0x00000D80);
	}
	else /* SEP */
	{
		OSD_TOP_O18_Wr(ctrl_auto_init, 0x55555555);

		/* raxis.lim (2019/01/07)
		 * use HW recommendeed value (SICDTV-5942)
		 * change ctrl_intr_pulse value based on AVTASK-327
	 	 */
		OSD_TOP_O18_Wr(ctrl_intr_pulse, 0xCAC76420);
		OSD_TOP_O18_Wr(ctrl_spath, 0x00100D80);

		/* raxis.lim (2019/01/07) -- use HW recommendeed value (SICDTV-5942)
		 * sync_gen_ctrl 파라미터를 PQE FW 에서 설정하고 있지 않다고 함. (AVTASK-327)
	  	 */
		OSD_TOP_O18_Wr(osd_sync_gen_ctrl0, 0x00040005);
		OSD_TOP_O18_Wr(osd_sync_gen_ctrl1, 0x00240438);
		OSD_TOP_O18_Wr(osd_sync_gen_ctrl2, 0x0058002C);
		OSD_TOP_O18_Wr(osd_sync_gen_ctrl3, 0x00940780);
		OSD_TOP_O18_Wr(osd_sync_gen_ctrl4, 0x00040005);
		OSD_TOP_O18_Wr(osd_sync_gen_ctrl5, 0x00240438);
		OSD_TOP_O18_Wr(osd_sync_gen_ctrl6, 0x0001006F);
		OSD_TOP_O18_Wr(osd_sync_gen_ctrl7, 0x00080058);
	}


	if(FBDEV_O18_CMN_GetHWStatus(FBDEV_O18_HW_STATUS_AFBC,NULL))
	{
		OSD_TOP_O18_Wr(ctrl_dpath, 0x00100000);
	}
	else
	{
		OSD_TOP_O18_Wr(ctrl_dpath, 0x00000000);
	}

	OSD_TOP_O18_WrFL(ctrl_auto_init);
	OSD_TOP_O18_WrFL(ctrl_intr_pulse);

	OSD_TOP_O18_WrFL(ctrl_dpath);
	OSD_TOP_O18_WrFL(ctrl_spath);

	if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
	{
		/* do nothing
		 * I confirmed that OSD display works well even when OSD path is changed from S.OSD to B.OSD.
		 * It means that osd_sync_gen registers don't affect OSD path.
		 */
	}
	else
	{
		OSD_TOP_O18_WrFL(osd_sync_gen_ctrl0);
		OSD_TOP_O18_WrFL(osd_sync_gen_ctrl1);
		OSD_TOP_O18_WrFL(osd_sync_gen_ctrl2);
		OSD_TOP_O18_WrFL(osd_sync_gen_ctrl3);
		OSD_TOP_O18_WrFL(osd_sync_gen_ctrl4);
		OSD_TOP_O18_WrFL(osd_sync_gen_ctrl5);
		OSD_TOP_O18_WrFL(osd_sync_gen_ctrl6);
		OSD_TOP_O18_WrFL(osd_sync_gen_ctrl7);
	}

	/* raxis.lim (2016/03/28) -- configure MIF to show OSD
	 * OSD0: MIF_OSD0_MB_REQ (+0x20) <= 0x0001_00FA
	 * OSD4: MIF_CSR0_MB_REQ (+0x60) <= 0x4000_00FB
	 *
	 * TODO: MIF register should be used with shadow access
	 */
	OS_WrReg(CCO_MIF_BASE+0x20, 0x000100FA);	/* 0xC902_4C20 <= 0x0001_00FA */
	OS_WrReg(CCO_MIF_BASE+0x60, 0x400000FB);	/* 0xC902_4C60 <= 0x4000_00FB */

	/* HW revision specific initialization */
	FBDEV_O18_InitOSDZOrder();

	FBDEV_O18_CMN_InitHW();

	/* normal PIC_INIT should be set only when current booting mode is normal or snapshot
	 * in other words, PIC_INIT should be set laster if current booting mode is I-BOOT resume
	 * refer to SICDTV-4209
	 */
	if (!(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR))
	{
		FBDEV_WARN("++ PIC_INIT ++ (NORMAL)\n");
		OSD_TOP_O18_Wr(pic_init, 0x00FF0000);
		OSD_TOP_O18_WrFL(pic_init);
	}

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
int FBDEV_O18_ShutdownHW	(void)
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
void FBDEV_O18_InitOSDZOrder ( void )
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
int FBDEV_O18_SetZList ( LX_FBDEV_ZLIST_T* zList )
{

	return RET_OK;
}

/** Get OSD ZList
 *
 * @param zList [OUT] pointer to POSD List config.
 * @return RET_OK
 *
 * @note layer id definition is 00: video, 01: OSD0, 02: OSD1, 03: OSD2
 * @note O18 doesn't support L&R zlist.
 * @note I will not use osd_mixer_ctrl_mux0.layer_mux_3 ( it's default value is POSD2 )
 *
 * @note somewhat obsolete function !
 */
int FBDEV_O18_GetZList( LX_FBDEV_ZLIST_T* zList )
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
int FBDEV_O18_WriteOSDEndian(int fb_dev_id, ENDIAN_INFORM_T *endian)
{
	int	i;
	int xidx;
	int xnum, xlst[2];
    UINT32 val;

	xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id );

#if FBDEV_O18_FIXME("I should use swap value 0x3 to swap 8bit/16bit in O18"\
					"TODO: swap value should be selected based on each SOC spec")
	val = 0x333;
#else
    val = (UINT32)((endian->header << 8) | (endian->palette << 4) | (endian->image << 0) );
#endif

    for (i=0;i<xnum;i++)
    {
		if (INVALID_XIDX(xlst[i])) continue;
		xidx = xlst[i];

		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_swap);
		OSDX_O18_Wr  (osdx_ctrl[xidx], osd_ctrl_swap, val);
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_swap);
	}

    return RET_OK;
}

/** set color space conversion on each layer
 *
 *	@note O18 doesn't support CSC for each layer
 *
 */
int FBDEV_O18_WriteOSDCSC(int layer , CSC_INFORM_T *csc)
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
int FBDEV_O18_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
	UINT32	status = 0;

	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	OSD_O18_RdFL(osd_common_ctrl_irq);

	if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
	{
		UINT32 bosd_mixer;
		OSD_O18_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, bosd_mixer );

		if(bosd_mixer)	status |= (1<<MIXER_INTR);
		else			printk("OSD ISR - BOSD MIXER INTR error\n");
	}
	else
	{
		UINT32 sosd_mixer;
		OSD_O18_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, sosd_mixer );

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
int FBDEV_O18_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
	OSD_O18_RdFL(osd_common_ctrl_irq);

	/* clear both bosd, sosd mixer intr for the safe operation */
	OSD_O18_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, 0x1 );
	OSD_O18_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, 0x1 );

	OSD_O18_WrFL(osd_common_ctrl_irq);

	return RET_OK;
}

/** Set interrupt enable/disable
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T , int : enable/disable
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_O18_SetInterruptEnable(INTERRUPT_INFORM_T intr , int enable)
{
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

    switch(intr)
    {
		default:
        case MIXER_INTR:
		{
			OSD_O18_RdFL(osd_common_ctrl_irq);
			if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
			{
				FBDEV_DEBUG("INTR <%s> for B.OSD\n", enable? "ON":"OFF" );
				OSD_O18_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bos, enable );
				OSD_O18_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sos, 0x0 );
			}
			else
			{
				FBDEV_DEBUG("INTR <%s> for S.OSD\n", enable? "ON":"OFF" );
				OSD_O18_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bos, 0x0 );
				OSD_O18_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sos, enable );
			}
			OSD_O18_WrFL(osd_common_ctrl_irq);
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
int	FBDEV_O18_InitOSDLayer	(int layer)
{
	return FBDEV_O18_CMN_InitOSDLayer(layer);
}

/*========================================================================================
	Implementation Group (REV dependent)
========================================================================================*/
int		FBDEV_O18_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl)
{
	int	ret = RET_ERROR;
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O18_SetViewCtrl, return RET_ERROR, "null handler\n");

	ret = hw_ctx->func.O18_SetViewCtrl(ctrl);

	/* TODO: if you should merge OSD inside kernel driver, add your code here */

	return ret;
}

/** set OSD output ctrl
 *
 */
int     FBDEV_O18_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl)
{
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O18_SetConnCtrl, return RET_ERROR, "null handler\n");

	return hw_ctx->func.O18_SetConnCtrl(ctrl);
}

/** Set Header information
 *
 */
int FBDEV_O18_WriteOSDHeader(struct scanvas *hCanvas)
{
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O18_WriteOSDHeader, return RET_ERROR, "null handler\n");

	return hw_ctx->func.O18_WriteOSDHeader(hCanvas);
}

/** OSD HW Layer enable/disable
 *
 */
int FBDEV_O18_SetOSDEnable(int layer, int enable)
{
	int	ret = RET_ERROR;
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O18_SetOSDEnable, return RET_ERROR, "null handler\n");

	ret = hw_ctx->func.O18_SetOSDEnable(layer, enable);

	/* TODO: if you should merge OSD inside kernel driver, add your code here */

	return ret;
}

/** OSD HW Layer status
 *
 */
int FBDEV_O18_GetOSDEnable(int layer)
{
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.O18_GetOSDEnable, return RET_ERROR, "null handler\n");

	return hw_ctx->func.O18_GetOSDEnable( layer );
}

