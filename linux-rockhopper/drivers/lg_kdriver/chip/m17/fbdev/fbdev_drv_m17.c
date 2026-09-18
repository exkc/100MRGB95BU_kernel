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
#include "fbdev_hw_m17.h"
#include "fbdev_hal.h"
#include "osd_reg_m17.h"
#include "osd_shp_reg_m17.h"
#include "osd_afbc_reg_m17.h"
#include "top_ctrl_osd_reg_m17.h"
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	CCO_CTRL_BASE			M17_PQE_TOP_CCO_CTRL_BASE 	//0xc9024000
#define CCO_MIF_BASE			M17_PQE_CCO_MIF_BASE		//0xc9024c00
#define CCO_OSD_BASE			M17_CCO_BASE				//0xc9024100
#define CCO_OSD_AFBC_BASE		M17_CCO_AFBC_BASE			//0xc9024700
#define	CCO_OSD_SHP_BASE		M17_CCO_SHP_BASE			//0xc9025c00

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
extern FBDEV_M17_HW_FUNC_T		g_fbdev_m17_cmn_hw_func;	/* M16 HW common func */

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_M17_InitOSDZOrder (void);
LX_FBDEV_CFG_T*	FBDEV_M17_GetCfg(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile OSD_AFBC_M17_REG_T* 	g_osd_afbc_m17_reg = NULL;
		 OSD_AFBC_M17_REG_T* 	g_osd_afbc_m17_reg_shadow = NULL;

volatile OSD_M17_REG_T*			g_osd_m17_reg = NULL;
		 OSD_M17_REG_T*			g_osd_m17_reg_shadow = NULL;

volatile OSD_TOP_M17_REG_T*		g_osd_top_m17_reg = NULL;
		 OSD_TOP_M17_REG_T*		g_osd_top_m17_reg_shadow = NULL;

volatile OSD_SHP_M17_REG_T*		g_osd_shp_m17_reg = NULL;
		 OSD_SHP_M17_REG_T*		g_osd_shp_m17_reg_shadow = NULL;

static FBDEV_M17_HW_CTX_T		g_fbdev_m17_hw_ctx;			/* M16 OSD H/W ctrl */

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_M17_AutoDetectOSDHWValue (void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static	FBDEV_HW_CTX_T	_g_fbdev_hw_ctx =
{
	.GetCfg				= FBDEV_M17_GetCfg,
	.RunSuspend			= FBDEV_M17_CMN_RunSuspend,
	.RunResume			= FBDEV_M17_CMN_RunResume,

	.InitHW				= FBDEV_M17_InitHW,
	.ShutdownHW			= FBDEV_M17_ShutdownHW,
	.ExecHWCommand      = FBDEV_M17_CMN_ExecHWCommand,

	.SetOSDEnable		= FBDEV_M17_SetOSDEnable,
	.GetOSDEnable		= FBDEV_M17_GetOSDEnable,

	.InitOSDLayer		= FBDEV_M17_InitOSDLayer,
	.WriteOSDHeader		= FBDEV_M17_WriteOSDHeader,

	.GetZList			= FBDEV_M17_GetZList,
	.SetZList			= FBDEV_M17_SetZList,

	.WriteOSDEndian		= FBDEV_M17_WriteOSDEndian,
	.WriteOSDCSC		= FBDEV_M17_WriteOSDCSC,

	.GetInterruptStatus	= FBDEV_M17_GetInterruptStatus,
	.SetInterruptClear	= FBDEV_M17_SetInterruptClear,
	.SetInterruptEnable	= FBDEV_M17_SetInterruptEnable,

	.SetViewCtrl		= FBDEV_M17_SetViewCtrl,
	.SetConnCtrl		= FBDEV_M17_SetConnCtrl,

	.CreateProc			= FBDEV_M17_CreateProc,
	.ProcHandler		= FBDEV_M17_CMN_ProcHandler,
};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get M16 specific configuration
 *
 *  @return LX_FBDEV_CFG_T
 */
LX_FBDEV_CFG_T*   FBDEV_M17_GetCfg(void)
{
    return NULL;
}

/** initialize M16 specific HW context variables.
 *
 *	@note this function is called before at M16 configure stage NOT at HW initialization stage.
 */
void	FBDEV_M17_InitHWCtx( FBDEV_HW_CTX_T* hal_obj )
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

	/* select the active M16 HW function handler */
	memcpy( &g_fbdev_m17_hw_ctx.func, &g_fbdev_m17_cmn_hw_func, sizeof(FBDEV_M17_HW_FUNC_T));

    for( i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
		g_fbdev_m17_hw_ctx.conn_ctrl[i].conn_type	= g_fbdev_m17_hw_ctx.hw_conn_type;
		g_fbdev_m17_hw_ctx.fbc_ctrl[i].status		= FBDEV_M17_FBC_STATUS_NONE;
		g_fbdev_m17_hw_ctx.sr_ctrl[i].auto_mode		= FALSE;
		g_fbdev_m17_hw_ctx.sr_ctrl[i].status		= FBDEV_M17_SR_STATUS_OFF;
		g_fbdev_m17_hw_ctx.sr_ctrl[i].coeff[0]		= 0x3FD;
		g_fbdev_m17_hw_ctx.sr_ctrl[i].coeff[1]		= 0x83;
		g_fbdev_m17_hw_ctx.sr_ctrl[i].coeff[2]		= 0x83;
		g_fbdev_m17_hw_ctx.sr_ctrl[i].coeff[3]		= 0x3FD;

		g_fbdev_m17_hw_ctx.sr_ctrl[i].ti_gain		= -1;
	}

	/* auto detect the default OSD connection and display size etc */
	FBDEV_M17_AutoDetectOSDHWValue( );

	/* initialize hal object
	 * after this function, all fbdev kdriver can get g_fbdev_m17_hw_ctx via g_fbdev_hw_ctx->chip_priv_ctx
	 */
	memcpy(hal_obj, &_g_fbdev_hw_ctx, sizeof(FBDEV_HW_CTX_T));
	hal_obj->chip_priv_ctx = &g_fbdev_m17_hw_ctx;
}

/** detect the default OSD connection
 *	This function will return the default(best) OSD connection setup based on SW, HW info
 *
 *	@note In M16, video path is fixed to UHD display. OSD will use this HW assumption.
 */
static void FBDEV_M17_AutoDetectOSDHWValue (void)
{
	UINT32	osd_disp_img_val	= LX_MAKE_RES(1920,1080);		/* defualt input image. default 2K resolution */
	UINT32	osd_disp_bosd_val	= LX_MAKE_RES(3840,2160);		/* default 4K resolution */
	UINT32	osd_disp_sosd_val	= LX_MAKE_RES(1920,1080);		/* default 2K resolution */
	UINT32 	osd_conn_val		= FBDEV_M17_DEFAULT_OSD_PATH; 	/* default path */
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
#ifdef FBDEV_M17_USE_HD_DISP_HANDLER
				osd_disp_fhd_val = LX_MAKE_RES(1376, 768); osd_disp_img_val = LX_MAKE_RES(1376, 768);
#else
				osd_disp_fhd_val = LX_MAKE_RES(1920, 768); osd_disp_img_val = LX_MAKE_RES(1920, 768);
#endif
			}
		}

		g_fbdev_m17_hw_ctx.hw_conn_type = osd_conn_val;

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

	g_fbdev_m17_hw_ctx.b_support_3dosd = b_support_3dosd;	/* support 3D OSD if there is no backend chip */

	g_fbdev_m17_hw_ctx.sosd_disp.in_width  = LX_RES_GET_WIDTH(osd_disp_img_val);
	g_fbdev_m17_hw_ctx.sosd_disp.in_height = LX_RES_GET_HEIGHT(osd_disp_img_val);
	g_fbdev_m17_hw_ctx.sosd_disp.out_width = LX_RES_GET_WIDTH(osd_disp_sosd_val);	/* S.OSD size is fixed to 1920x1080 */
	g_fbdev_m17_hw_ctx.sosd_disp.out_height= LX_RES_GET_HEIGHT(osd_disp_sosd_val);
	g_fbdev_m17_hw_ctx.sosd_disp.pulse_timer_dly = osd_pulse_sosd_val;

	g_fbdev_m17_hw_ctx.bosd_disp.in_width  = LX_RES_GET_WIDTH(osd_disp_img_val);
	g_fbdev_m17_hw_ctx.bosd_disp.in_height = LX_RES_GET_HEIGHT(osd_disp_img_val);
	g_fbdev_m17_hw_ctx.bosd_disp.out_width = LX_RES_GET_WIDTH(osd_disp_bosd_val);	/* B.OSD size might be changed based on DTV config */
	g_fbdev_m17_hw_ctx.bosd_disp.out_height= LX_RES_GET_HEIGHT(osd_disp_bosd_val);
	g_fbdev_m17_hw_ctx.bosd_disp.pulse_timer_dly = osd_pulse_bosd_val;

#ifdef FBDEV_M17_2X_CURSOR_ON_BLEND_PATH
	g_fbdev_m17_hw_ctx.bosd_disp.b_2x_cursor_disp = TRUE;
#else
	g_fbdev_m17_hw_ctx.bosd_disp.b_2x_cursor_disp = FALSE;
#endif

	if (osd_conn_val & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		g_fbdev_m17_hw_ctx.b_keep_hw_conn_type 	= TRUE;
		g_fbdev_m17_hw_ctx.hw_disp_width		= g_fbdev_m17_hw_ctx.bosd_disp.out_width;
		g_fbdev_m17_hw_ctx.hw_disp_height		= g_fbdev_m17_hw_ctx.bosd_disp.out_height;
		g_fbdev_m17_hw_ctx.hw_gfx_width			= g_fbdev_m17_hw_ctx.bosd_disp.in_width;
		g_fbdev_m17_hw_ctx.hw_gfx_height		= g_fbdev_m17_hw_ctx.bosd_disp.in_height;
	}
	else
	{
		g_fbdev_m17_hw_ctx.b_keep_hw_conn_type	= FALSE;
		g_fbdev_m17_hw_ctx.hw_disp_width 		= g_fbdev_m17_hw_ctx.sosd_disp.out_width;
		g_fbdev_m17_hw_ctx.hw_disp_height		= g_fbdev_m17_hw_ctx.sosd_disp.out_height;
		g_fbdev_m17_hw_ctx.hw_gfx_width 		= g_fbdev_m17_hw_ctx.sosd_disp.in_width;
		g_fbdev_m17_hw_ctx.hw_gfx_height		= g_fbdev_m17_hw_ctx.sosd_disp.in_height;
	}

	g_fbdev_m17_hw_ctx.hw_wa_flag				|= FBDEV_M17_HW_WA_1X_CSR_DISP_ON_BLEND_PATH;

	printk("OSD HW default osd_conn = 0x%x, disp_size = %dx%d, wa = 0x%08x\n",
			g_fbdev_m17_hw_ctx.hw_conn_type,
			g_fbdev_m17_hw_ctx.hw_disp_width, g_fbdev_m17_hw_ctx.hw_disp_height,
			g_fbdev_m17_hw_ctx.hw_wa_flag );
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
int FBDEV_M17_InitHW (void)
{
	int ret = RET_ERROR;

	FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();

	/* ioremap TOP regs */
	if (NULL==g_osd_top_m17_reg)
	{
		g_osd_top_m17_reg =(OSD_TOP_M17_REG_T*)ioremap(CCO_CTRL_BASE, sizeof(OSD_TOP_M17_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_top_m17_reg, goto func_exit, "out of memory\n");

	if (NULL==g_osd_top_m17_reg_shadow)
	{
		g_osd_top_m17_reg_shadow =(OSD_TOP_M17_REG_T*)OS_Malloc(sizeof(OSD_TOP_M17_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_top_m17_reg_shadow, goto func_exit, "out of memory\n");

	/* ioremap OSD regs */
	if (NULL==g_osd_m17_reg)
	{
		g_osd_m17_reg =(OSD_M17_REG_T*)ioremap(CCO_OSD_BASE, sizeof(OSD_M17_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_m17_reg, goto func_exit, "out of memory\n");

	if (NULL==g_osd_m17_reg_shadow)
	{
		g_osd_m17_reg_shadow = (OSD_M17_REG_T*)OS_Malloc(sizeof(OSD_M17_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_m17_reg_shadow, return RET_ERROR, "out of memory\n");

	/* ioremap OSD_AFGC regs */
	if (NULL==g_osd_afbc_m17_reg)
	{
		g_osd_afbc_m17_reg =(OSD_AFBC_M17_REG_T*)ioremap(CCO_OSD_AFBC_BASE, sizeof(OSD_AFBC_M17_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_m17_reg, goto func_exit, "out of memory\n");

	if (NULL==g_osd_afbc_m17_reg_shadow)
	{
		g_osd_afbc_m17_reg_shadow = (OSD_AFBC_M17_REG_T*)OS_Malloc(sizeof(OSD_AFBC_M17_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_afbc_m17_reg_shadow, return RET_ERROR, "out of memory\n");

	/* ioremap OSD_SHP regs */
	if (NULL==g_osd_shp_m17_reg)
	{
		g_osd_shp_m17_reg =(OSD_SHP_M17_REG_T*)ioremap(CCO_OSD_SHP_BASE, sizeof(OSD_SHP_M17_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_m17_reg, goto func_exit, "out of memory\n");

	if (NULL==g_osd_shp_m17_reg_shadow)
	{
		g_osd_shp_m17_reg_shadow = (OSD_SHP_M17_REG_T*)OS_Malloc(sizeof(OSD_SHP_M17_REG_T));
	}
	FBDEV_CHECK_CODE( NULL==g_osd_shp_m17_reg_shadow, return RET_ERROR, "out of memory\n");


	OSD_TOP_M17_Wr(pic_init, 0x00FF0000);

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
		OSD_TOP_M17_Wr(ctrl_auto_init, 0x55555555);
	}
	else /* SEP */
	{
		OSD_TOP_M17_Wr(ctrl_auto_init, 0x77777777);
	}

	/* raxis.lim (2016/03/28) -- ctrl_intr_pulse, ctrl_dpath, ctrl_spath is set by HW default value
	 * raxis.lim (2016/10/05) -- keep AFBC status becuase boot loader can display AFBC logo image
	 */
	OSD_TOP_M17_Wr(ctrl_intr_pulse, 0xCA876420);
	OSD_TOP_M17_Wr(ctrl_spath, 0x00000D80);

	if(FBDEV_M17_CMN_GetHWStatus(FBDEV_M17_HW_STATUS_AFBC,NULL))
	{
		OSD_TOP_M17_Wr(ctrl_dpath, 0x00100000);
	}
	else
	{
		OSD_TOP_M17_Wr(ctrl_dpath, 0x00000000);
	}

	OSD_TOP_M17_WrFL(pic_init);
	OSD_TOP_M17_WrFL(ctrl_auto_init);
	OSD_TOP_M17_WrFL(ctrl_intr_pulse);

	OSD_TOP_M17_WrFL(ctrl_dpath);
	OSD_TOP_M17_WrFL(ctrl_spath);

	/* raxis.lim (2016/03/28) -- configure MIF to show OSD
	 * OSD0: MIF_OSD0_MB_REQ (+0x20) <= 0x0001_00FA
	 * OSD4: MIF_CSR0_MB_REQ (+0x60) <= 0x4000_00FB
	 *
	 * TODO: MIF register should be used with shadow access
	 */
	OS_WrReg(CCO_MIF_BASE+0x20, 0x000100FA);	/* 0xC902_4C20 <= 0x0001_00FA */
	OS_WrReg(CCO_MIF_BASE+0x60, 0x400000FB);	/* 0xC902_4C60 <= 0x4000_00FB */

	/* HW revision specific initialization */
	FBDEV_M17_InitOSDZOrder();

	hw_ctx->func.M16_InitHW();

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
int FBDEV_M17_ShutdownHW	(void)
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
void FBDEV_M17_InitOSDZOrder ( void )
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
int FBDEV_M17_SetZList ( LX_FBDEV_ZLIST_T* zList )
{

	return RET_OK;
}

/** Get OSD ZList
 *
 * @param zList [OUT] pointer to POSD List config.
 * @return RET_OK
 *
 * @note layer id definition is 00: video, 01: OSD0, 02: OSD1, 03: OSD2
 * @note M16 doesn't support L&R zlist.
 * @note I will not use osd_mixer_ctrl_mux0.layer_mux_3 ( it's default value is POSD2 )
 *
 * @note somewhat obsolete function !
 */
int FBDEV_M17_GetZList( LX_FBDEV_ZLIST_T* zList )
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
int FBDEV_M17_WriteOSDEndian(int fb_dev_id, ENDIAN_INFORM_T *endian)
{
	int	i;
	int xidx;
	int xnum, xlst[2];
    UINT32 val;

	xnum = FBDEV_M17_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id );

#if FBDEV_M17_FIXME("I should use swap value 0x3 to swap 8bit/16bit in M17"\
					"TODO: swap value should be selected based on each SOC spec")
	val = 0x333;
#else
    val = (UINT32)((endian->header << 8) | (endian->palette << 4) | (endian->image << 0) );
#endif

    for (i=0;i<xnum;i++)
    {
		if (INVALID_XIDX(xlst[i])) continue;
		xidx = xlst[i];

		OSDX_M17_RdFL(osdx_ctrl[xidx], osd_ctrl_swap);
		OSDX_M17_Wr  (osdx_ctrl[xidx], osd_ctrl_swap, val);
		OSDX_M17_WrFL(osdx_ctrl[xidx], osd_ctrl_swap);
	}

    return RET_OK;
}

/** set color space conversion on each layer
 *
 *	@note M16 doesn't support CSC for each layer
 *
 */
int FBDEV_M17_WriteOSDCSC(int layer , CSC_INFORM_T *csc)
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
int FBDEV_M17_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
	UINT32	status = 0;

	FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();

	OSD_M17_RdFL(osd_common_ctrl_irq);

	if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
	{
		UINT32 bosd_mixer;
		OSD_M17_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, bosd_mixer );

		if(bosd_mixer)	status |= (1<<MIXER_INTR);
		else			printk("OSD ISR - BOSD MIXER INTR error\n");
	}
	else
	{
		UINT32 sosd_mixer;
		OSD_M17_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, sosd_mixer );

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
int FBDEV_M17_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
	OSD_M17_RdFL(osd_common_ctrl_irq);

	/* clear both bosd, sosd mixer intr for the safe operation */
	OSD_M17_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, 0x1 );
	OSD_M17_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, 0x1 );

	OSD_M17_WrFL(osd_common_ctrl_irq);

	return RET_OK;
}

/** Set interrupt enable/disable
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T , int : enable/disable
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_M17_SetInterruptEnable(INTERRUPT_INFORM_T intr , int enable)
{
	FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();

    switch(intr)
    {
		default:
        case MIXER_INTR:
		{
			OSD_M17_RdFL(osd_common_ctrl_irq);
			if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
			{
				FBDEV_DEBUG("INTR <%s> for B.OSD\n", enable? "ON":"OFF" );
				OSD_M17_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bos, enable );
				OSD_M17_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sos, 0x0 );
			}
			else
			{
				FBDEV_DEBUG("INTR <%s> for S.OSD\n", enable? "ON":"OFF" );
				OSD_M17_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bos, 0x0 );
				OSD_M17_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sos, enable );
			}
			OSD_M17_WrFL(osd_common_ctrl_irq);
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
int	FBDEV_M17_InitOSDLayer	(int layer)
{
	return FBDEV_M17_CMN_InitOSDLayer(layer);
}

/*========================================================================================
	Implementation Group (REV dependent)
========================================================================================*/
int		FBDEV_M17_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl)
{
	int	ret = RET_ERROR;
	FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();

	FBDEV_CHECK_CODE(NULL==hw_ctx->func.M16_SetViewCtrl, return RET_ERROR, "null handler\n");

	ret = hw_ctx->func.M16_SetViewCtrl(ctrl);

	/* TODO: if you should merge OSD inside kernel driver, add your code here */

	return ret;
}

/** set OSD output ctrl
 *
 */
int     FBDEV_M17_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl)
{
	FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.M16_SetConnCtrl, return RET_ERROR, "null handler\n");

	return hw_ctx->func.M16_SetConnCtrl(ctrl);
}

/** Set Header information
 *
 */
int FBDEV_M17_WriteOSDHeader(struct scanvas *hCanvas)
{
	FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.M16_WriteOSDHeader, return RET_ERROR, "null handler\n");

	return hw_ctx->func.M16_WriteOSDHeader(hCanvas);
}

/** OSD HW Layer enable/disable
 *
 */
int FBDEV_M17_SetOSDEnable(int layer, int enable)
{
	int	ret = RET_ERROR;
	FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();

	FBDEV_CHECK_CODE(NULL==hw_ctx->func.M16_SetOSDEnable, return RET_ERROR, "null handler\n");

	ret = hw_ctx->func.M16_SetOSDEnable(layer, enable);

	/* TODO: if you should merge OSD inside kernel driver, add your code here */

	return ret;
}

/** OSD HW Layer status
 *
 */
int FBDEV_M17_GetOSDEnable(int layer)
{
	FBDEV_M17_HW_CTX_T* hw_ctx = FBDEV_M17_GET_HW_CTX();
	FBDEV_CHECK_CODE(NULL==hw_ctx->func.M16_GetOSDEnable, return RET_ERROR, "null handler\n");

	return hw_ctx->func.M16_GetOSDEnable( layer );
}

