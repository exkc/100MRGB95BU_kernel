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
#include "fbdev_drv.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "fbdev_hw_o18.h"
#include "osd_reg_o18.h"
#include "osd_shp_reg_o18.h"
#include "osd_scan_reg_o18.h"
#include "osd_afbc_reg_o18.h"
#include "top_ctrl_osd_reg_o18.h"
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/freezer.h>

#include <linux/seq_file.h>

#ifdef FBDEV_O18_USE_CTOP_REGS
#include "../sys/sys_regs.h"
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

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern	int							g_fbdev_use_isr_mon;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_O18_CMN_InitFBCEnv	(void);
#ifdef FBDEV_O18_USE_FBC_CTRL
static void FBDEV_O18_CMN_SetupFBC		(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt);
#endif

static void FBDEV_O18_CMN_InitCropEnv	(void);
static void FBDEV_O18_CMN_InitMirrorEnv	(void);
static void FBDEV_O18_CMN_SetupSRScaler	(BOOLEAN onoff, BOOLEAN bForce);

static void	FBDEV_O18_CMN_ReInitHW		(void);
static int FBDEV_O18_CMN_WriteOSDHeader (struct scanvas *pCanvas);
static FBDEV_VSYNC_CLK_T FBDEV_O18_CMN_DetectVSyncClk(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_osd_hdr_spinlock);

static int	fbdev_boot_freeze_timeout = FBDEV_O18_BOOT_FREEZE_TIME;
static int	fbdev_resume_freeze_timeout = FBDEV_O18_RESUME_FREEZE_TIME;
static int	fbdev_pqefw_osd0_out_ctrl 	= 1;	/* SICDTV-4359 */
static int	fbdev_osd0_user_out_win 	= 0;	/* SICDTV-4359 */

module_param_named( fbdev_o18_boot_freeze_timeout,	fbdev_boot_freeze_timeout, int, 0644 );
module_param_named( fbdev_o18_resume_freeze_timeout,fbdev_resume_freeze_timeout, int, 0644 );

module_param_named( fbdev_o18_pqefw_osd0_out_ctrl,	fbdev_pqefw_osd0_out_ctrl, int, 0644 );
module_param_named( fbdev_o18_osd0_user_out_win, 	fbdev_osd0_user_out_win, int, 0644 );

/*----------------------------------------------------------------------------------------
	Static Functions
----------------------------------------------------------------------------------------*/

/** query FB mapping information
 *
 *	fb_dev_id is the virtual indentifier for application, this functions returns the real OSD HW layer
 *
 *	@param fb_dev_id [IN] user ID
 *	@param xlst [IN] arrary to hold two OSD HW layer connected to user ID
 *	@return num of xlst
 *
 */
int	FBDEV_O18_CMN_GetHWXList(int fb_dev_id, int xlst[2])
{
	int	num_xlst = 0;

	switch( fb_dev_id )
	{
		case LX_FBDEV_ID_OSD0:	num_xlst=1; xlst[0] = 0; xlst[1] =-1; break;
		case LX_FBDEV_ID_CSR0:  num_xlst=1; xlst[0] = 4; xlst[1] =-1; break;
		default:				num_xlst=0; xlst[0] =-1; xlst[1] =-1; break;
	}

	return num_xlst;
}

BOOLEAN  FBDEV_O18_CMN_IsUHDDispMode  (void)
{
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();
	return (lx_chip_plt()==LX_CHIP_PLT_UHD && hw_ctx->hw_disp_width > 2048)? TRUE:FALSE;
}

#ifdef FBDEV_O18_USE_REVERSE_HW_CTRL
/** check if current OSD HW is set as the reverse mode
 *
 */
static BOOLEAN	FBDEV_O18_CMN_IsReverseMode	( int fb_dev_id )
{
	/* @note how to check reverse OSD mode ? */
	return FALSE;
}
#endif

/** enable OSD HW update
 *
 *	if OSD header flag is not set, OSD is not updated !
 *
 */
static void FBDEV_O18_CMN_EnableOSDHdrFlush( ULONG data )
{
    int i;
#if (CONFIG_LX_BOOT_LOGO==1)
	int	xidx;
	int xnum, xlst[2];

	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

    FBDEV_WARN("<!> enable osd_hdr_flush & exit OSD freeze stage. afbc=%d\n",
			 FBDEV_O18_CMN_GetHWStatus(FBDEV_O18_HW_STATUS_AFBC, NULL));

	/* enable osd_hdr_flush to unfreeze OSD */
    for (i=0; i<FBDEV_MAX_DEVICE; i++)
    {
        FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(i);
		struct scanvas*  hCanvas = FBDEV_GetWinCanvas(i);

		FBDEV_CHECK_CODE(NULL==wctx, continue, "invalid fb(%d) ctx\n", i );
		FBDEV_CHECK_CODE(NULL==hCanvas, continue, "invalid fb(%d) canvas\n", i );

		//FBDEV_CHECK_CODE(!g_fbdev_cfg->fb[i].b_active, continue, "inactive fb(%d)\n", i);

		/* if freeize is already disabled, ignore osd hdr flush */
		if(wctx->status.b_osd_hdr_flush)
		{
			FBDEV_HW_DEBUG("fb(%d) osd_hdr_flush is already enabled\n", i);
			continue;
		}

		FBDEV_BOOT_DEBUG("++ fb(%d) flip_cnt = %d, total_flip_cnt = %d\n",
					i, wctx->status.fb_flip_cnt, wctx->status.total_fb_flip_cnt);

		wctx->status.b_osd_hdr_flush = TRUE;

#ifdef FBDEV_O18_KEEP_LOGO_LAYER
		/* raxis.lim (2016/08/29)
		 * Because O18+ supports AFBC image format, I should consider state transition from NON-AFBC to AFBC.
		 * when stage change detected, I call WritOSDHeader() function to sync all OSD/AFBC related register values.
		 *
		 * exceptional case:
		 * if there is no any user screen update, OSD keeps the current state (NON-AFBC state)
		 * -> DO NOT write any OSD/AFBC registers
		 *
		 * for debug purpose, I can see some OSD garbage by setting fbdev_force_flush_on_freeze_exit
		 *
		 */
		if (i==CONFIG_LX_BOOT_LOGO_FBDEV && (wctx->status.fb_flip_cnt>0 || g_fbdev_use_force_flush_on_freeze_exit) )
		{
			FBDEV_BOOT_DEBUG("fb(%d) rewrite the last requested OSD header \n", i);
			FBDEV_O18_CMN_WriteOSDHeader(hCanvas);
		}
		else
#endif
		{
			FBDEV_BOOT_DEBUG("fb(%d) flush OSD header\n", i);

			/* write OSD header again to update the real screen */
			xnum = FBDEV_O18_CMN_GetHWXList(i, xlst);
			if(INVALID_XNUM(xnum)) continue;

			xidx = xlst[0];
			if(INVALID_XIDX(xlst[0])) continue;

		#ifdef FBDEV_O18_USE_HDR_RDY_REG
			/* if there is any sync-required OSD registers, do it */
			g_osd_o18_reg->osdx_ctrl[xidx].osd_ctrl_main.osd_hdr_ready_flag = 0x1;
		#endif
		}
    }
#endif /* CONFIG_LX_BOOT_LOGO */

	if(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		/* (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume */
		hw_ctx->hw_wa_flag |= FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL;
		FBDEV_WARN("PQEFW_OSD0_OUT_CTRL enabled\n");
	}
	else
	{
		/* S.OSD doesn't support any PQE orbit control */
		hw_ctx->hw_wa_flag &= ~FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL;
		fbdev_pqefw_osd0_out_ctrl = 0;
		FBDEV_WARN("PQEFW_OSD0_OUT_CTRL always disabled\n");
	}
}

/**
 *
 */
void FBDEV_O18_CMN_RunBootLogoTimer(UINT32 ms, BOOLEAN bForce)
{
#if (CONFIG_LX_BOOT_LOGO==1)
	static BOOLEAN		b_timer_req = TRUE;
	static OS_TIMER_T	osd_en_timer;

	if ( b_timer_req || bForce )
	{
		b_timer_req = FALSE;
		FBDEV_BOOT_DEBUG("start boot timer %d ms (%d)\n", ms, bForce);

		OS_InitTimer ( &osd_en_timer );
		OS_StartTimer( &osd_en_timer, FBDEV_O18_CMN_EnableOSDHdrFlush, OS_TIMER_TIMEOUT, ms, 0x0 );
	}
#else
	FBDEV_O18_CMN_EnableOSDHdrFlush(0x0);
#endif
}

/** query tcon clk information & detect vsync clk interval
 *
 *  @note this function should be called after SYS kdriver initialization
 */
static FBDEV_VSYNC_CLK_T FBDEV_O18_CMN_DetectVSyncClk(void)
{
#ifdef FBDEV_O18_USE_CTOP_REGS
	UINT32 tcon_pix2_clk;
	CTOP_CTRL_O18A0_RdFL(CTRL_TCON, crg_tcon01);
	CTOP_CTRL_O18A0_Rd01(CTRL_TCON, crg_tcon01, tcon_pix2_clk_sel, tcon_pix2_clk);

	return (tcon_pix2_clk == 0x0 || tcon_pix2_clk == 0x2)? FBDEV_VSYNC_CLK_120HZ: FBDEV_VSYNC_CLK_60HZ;
#else
	return FBDEV_VSYNC_CLK_60HZ;
#endif
}

/*========================================================================================
    Implementation Group (OSD HW Initialization)
========================================================================================*/

/** initialize HW SOC
 *
 *
 */
int	FBDEV_O18_CMN_InitHW ( void )
{
	int	i;
	FBDEV_O18_HW_CTX_T*	hw_ctx = FBDEV_O18_GET_HW_CTX();

	/* fetch the current HW disp size */
	UINT32	disp_width = hw_ctx->hw_disp_width;
	UINT32	disp_height= hw_ctx->hw_disp_height;

	FBDEV_HW_DEBUG("(Re)Init OSD(O18) HW.. disp_size %dx%d\n", disp_width, disp_height);

	/* initialize S.OSD & B.OSD mixer disp size */
	OSDX_O18_RdFL(osdx_sep_osd_mixer[0], ctrl_sosd_mixer_disp_size);
	OSDX_O18_Wr02(osdx_sep_osd_mixer[0], ctrl_sosd_mixer_disp_size,	reg_sosd_disp_size_w, hw_ctx->sosd_disp.out_width,
																	reg_sosd_disp_size_h, hw_ctx->sosd_disp.out_height);
	OSDX_O18_WrFL(osdx_sep_osd_mixer[0], ctrl_sosd_mixer_disp_size);

	OSDX_O18_RdFL(osdx_blend_osd_mixer[0], ctrl_bosd_mixer_disp_size);
	OSDX_O18_Wr02(osdx_blend_osd_mixer[0], ctrl_bosd_mixer_disp_size,	reg_bosd_disp_size_w, hw_ctx->bosd_disp.out_width,
																		reg_bosd_disp_size_h, hw_ctx->bosd_disp.out_height);
	OSDX_O18_WrFL(osdx_blend_osd_mixer[0], ctrl_bosd_mixer_disp_size);

	/* setup all OSD common disp size */
	for (i=0; i< FBDEV_O18_MAX_OSD_BLK_NUM; i++)
	{
		OSD_O18_RdFL(osdx_common_disp_size[i]);
		OSD_O18_Wr02(osdx_common_disp_size[i],	reg_common_disp_size_w, disp_width,
								  				reg_common_disp_size_h, disp_height );
		OSD_O18_WrFL(osdx_common_disp_size[i]);
	}

	/* O18 has the fixed mux value. DO NOT change */
	{
		UINT32 mixer_mux_value = 0x76543210;
		FBDEV_WARN("(Re)Init OSD(O18) mixer mux order = 0x%08x\n", mixer_mux_value );

		OSDX_O18_Wr(osdx_sep_osd_mixer[0], 		ctrl_sosd_mixer_mux1, mixer_mux_value);
		OSDX_O18_WrFL(osdx_sep_osd_mixer[0],	ctrl_sosd_mixer_mux1);

	    OSDX_O18_Wr(osdx_blend_osd_mixer[0],	ctrl_bosd_mixer_mux1, mixer_mux_value);
		OSDX_O18_WrFL(osdx_blend_osd_mixer[0],	ctrl_bosd_mixer_mux1);
	}

	/* raxis.lim (2014/11/11) tune osd sync pulse timer
	 * CCO_CTRL.CTRL_SOSD_PLUS.reg_disp_sosd_timer controls the delay the OSD mix start time in cycle unit.
	 * OSD HW engineer recommend to use 0x3000 (almost 10 line delay) can fix OSD sync & isr mismatch issue.
	 *
	 * value 0x3000 has been determinted at H15 development
	 *
	 * raxis.lim (2016/03/28) set bosd_pulse as 0x3000 (used at O18 for the first time)
	 *
	 */
	OSD_TOP_O18_RdFL(ctrl_sosd_pulse);
	OSD_TOP_O18_Wr01(ctrl_sosd_pulse, reg_disp_pulse_timer, hw_ctx->sosd_disp.pulse_timer_dly );
	OSD_TOP_O18_WrFL(ctrl_sosd_pulse);

	OSD_TOP_O18_RdFL(ctrl_bosd_pulse);
    OSD_TOP_O18_Wr01(ctrl_bosd_pulse, reg_disp_pulse_timer, hw_ctx->bosd_disp.pulse_timer_dly );
	OSD_TOP_O18_WrFL(ctrl_bosd_pulse);

	FBDEV_O18_CMN_SetupSRScaler(FBDEV_O18_CMN_IsUHDDispMode()? TRUE:FALSE, TRUE);
	FBDEV_O18_CMN_InitMirrorEnv();
	FBDEV_O18_CMN_InitCropEnv();
	FBDEV_O18_CMN_InitFBCEnv();

	return RET_OK;
}

/** make OSD to be initial state
 *	make the basic configuration for each OSD layer.
 *
 *	@param layerId
 */
int FBDEV_O18_CMN_InitOSDLayer ( int fb_dev_id )
{
	int	xidx;
	int xnum, xlst[2];
	int ret = RET_ERROR;

	/* please refer to OSD manual OSD<x>_CFG field */
	UINT32  hdr_src_sel;
	UINT32  osd_memhdr_addr;
	BOOLEAN	osd_en = 0x0;			/* off by default */
	BOOLEAN	hdr_rdy_flag = 0x0;		/* OFF by default */
	BOOLEAN v_mirror_en = 0x0;		/* OFF by default */

	FBDEV_O18_HW_CTX_T*	hw_ctx = FBDEV_O18_GET_HW_CTX();

	/* fetch the current output disp size */
	UINT32	disp_width = hw_ctx->hw_disp_width;
	UINT32	disp_height= hw_ctx->hw_disp_height;

	xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id );

	/* hdr_src_sel 0x0: DDR, 0x1: REG */
	hdr_src_sel	= (g_fbdev_hwio_cfg->hdr_op_method == FBDEV_HDR_OP_MMIO)? 0x0: 0x1;
	osd_memhdr_addr = (gMemCfgFBHdr[fb_dev_id].mem_header_base);

	v_mirror_en = (hw_ctx->mirror_ctrl.status & FBDEV_O18_V_MIRROR_ON)? 0x1: 0x0;

	/* choose the initial osd visibility based on boot logo configuration */
	switch(fb_dev_id)
	{
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==0)
		case LX_FBDEV_ID_OSD0:	osd_en = 0x1; break;
#endif
		default:				osd_en = 0x0; break;
	}
#ifdef FBDEV_O18_USE_HDR_RDY_REG
	hdr_rdy_flag = 0x1;
#endif

	{
		UINT32	sync_disp_width;
		UINT32	sync_hdouble_en;
		UINT32	ctrl_direc;

		xidx = xlst[0];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), goto func_exit, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

		/* raxis.lim (2016/03/28)
		 * if BLEND mode, each OSD layer should have a half of real disp size. (it's HW spec)
		 * this restruction is also applied to the cursor layer.
		 *
		 */
		sync_disp_width = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? disp_width/2 : disp_width;

		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_pdec);
		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_base_addr);
		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);
		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_sync1);
		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_scaler);

		/* OSD HW requests to write both osd_en & osd_sync_enable to control osd visibility */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_main, 	osd_en,			osd_en);
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0,	osd_sync_enable,osd_en);

		/* raxis.lim (2014/06)
		 * if BLEND mode, each OSD layer should have a half of real display size (it's HW spec)
		 * this restruction is also applied to the cursor layer.
		 */
		sync_hdouble_en = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0x0: 0x1;

		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_hdouble_en, sync_hdouble_en);

		/* use osd_hdr_flag to avoid the possible OSD mis-configuration when OSD header is set across vsync */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_ready_flag_en, hdr_rdy_flag );

		/* normally osd_hdr_src_sel is fixed to "read from hw register" not "DDR contains osd_hdr data" */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_src_sel,		hdr_src_sel );

		/* configure mirror mode every layer initialization */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en,		v_mirror_en );

		/* configure CSR0 sync for mirror mode to support virtical reversed position */
		if(fb_dev_id == LX_FBDEV_ID_CSR0)
		{
			OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_v_reverse, v_mirror_en );
		}

		/* we should set DDR memory to hold osd_hdr data, but NOT used in normal case
		 * remember that OSD always fetch header data from DDR regardless of hdr_src_sel value
		 * it's safe that I set the same address as the frame buffer
		 */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_base_addr, 	osd_base_addr, osd_memhdr_addr);

		#if 0 /* KEEP HW DEFAULT */
		/* set scaler sample mode to the same behavior as that of GFX */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler,osd_sc_sampling_mode,	0x1 );
		#endif

		/* initialize cursor attribute (OSD4 only) */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler,reg_crsr_h_x2_en,	0x0 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler,reg_crsr_v_x2_en,	0x0 );

		/* MIF feeder cfg : "10 (0x2)" L to R (HW default value)
		 * this value has ben fixed to "10" inside OSD HW since older chip.
		 * In O18/O18, this value can be configurable by SW But I keep this value as 0x2 forever
		 *
		 * HW default value = 0x2
		 */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_main,	osd_manual_dlr,		0x2 );

		/* setup PDEC (each pixel component (A,R,G,B) can be configured to make any pixel order combination.
		 * for example, ARGB can be BGRA :)
		 * by default, input pixel order is bypassed to output.
		 *
		 * HW deault value = 0x1B000000
		 */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_alpha,			0x0 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_red,				0x1 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_green,			0x2 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_blue,			0x3 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_round,				0x0 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_pure_ck,			0x0 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_lfsr_seed,			0x0 );

#ifdef FBDEV_O18_USE_EXPERIMENTAL_CONFIG
		/* raxis.lim (2018/04/09)
		 * according to register manual, reg_osd_buf_mode_en enables for OSD to use scaler memory as extra line memory
		 * during 1:1 non-scaler mode.
		 * when UHD display mode, FHD image is always scaled to UHD-sized output image. so it's good to set osd_buf_mode_en as 0x0.
		 * when FHD display mode, FHD image is not scaled, so it's good to set osd_buf_mode_en as 0x1
		 *
		 * @note refer to SICDTV-4852
		 *
		 */
		if (xidx == 0x0)
		{
			UINT32 buf_mode_en = (FBDEV_O18_CMN_IsUHDDispMode())? 0x0: 0x1;
			OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler,reg_osd_buf_mode_en,	buf_mode_en);
		}
#endif

		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_main );
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_pdec );
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_base_addr );
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_scaler );
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0 );

		/* TODO: add more initialization if necessary */

		/* setup basic path */

		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_path );

		ctrl_direc = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0x0: 0x1;

		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_direc, ctrl_direc);
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_eo2s,  ctrl_direc);

		/* setup each display size(?).
		 * keep in mind that width value osd_ctrl_path, osd_ctrl_sync1 is NOT real disp_width.
	 	 * they should be set a half when B.OSD is activated.
		 * these field is used to control how OSD fetch & process OSD frame data.
		 */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_path, reg_ctrl_path_width,		sync_disp_width);
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_bosd_pos,		0x0 );	/* fixed to 0x0(BOSD1) */
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_path );

		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_sync1 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_sync1, osd_sync_disp_w,	sync_disp_width);
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_sync1, osd_sync_disp_h,	disp_height);
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_sync1 );

		FBDEV_WARN("OSD(%d) Init HW done\n", fb_dev_id);
	}

    ret = RET_OK;   /* all work done */
func_exit:
	return ret;
}

#ifdef FBDEV_O18_SICDTV_4209_FIX
/* enable OSD0 sync with safe */
static void FBDEV_O18_CMN_SafeSyncEnable(void)
{
	int	i;
	int xidx;
	int xnum, xlst[2];

	UINT32 osd0_sync4_regs[2] = { 0xFFFFFFFF, 0x00000000 };

	xnum = FBDEV_O18_CMN_GetHWXList(LX_FBDEV_ID_OSD0, xlst);
	xidx = xlst[0];

	for (i=0; i<100; i++)
	{
		OSDX_O18_Wr(osdx_ctrl[xidx], osd_ctrl_sync4, osd0_sync4_regs[i%2]);
       	OSD_TOP_O18_Wr(pic_init, 0x000000FF);

		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_sync4);
		OSD_TOP_O18_WrFL(pic_init);

		if(!((i+1)%10))	udelay(1);
	}
	FBDEV_WARN("++ PIC_INIT ++ (I-BOOT)\n");

	OSD_TOP_O18_Wr(pic_init, 0x00FF0000);
	OSD_TOP_O18_WrFL(pic_init);
}

static int FBDEV_O18_CMN_CheckSyncStatus(void)
{
#define OSD_STUCK_VALUE 0x40000 /* 0x4000x */

	int	i;
	int xidx;
	int xnum, xlst[2];

	UINT32	osd_status;
	int		stuck_cnt = 0;

	xnum = FBDEV_O18_CMN_GetHWXList(LX_FBDEV_ID_OSD0, xlst);
	xidx = xlst[0];

	for (i=0; i<20; i++)
	{
		OSDX_O18_RdFL(osd_status_mon_data[xidx], reg_status_mon_data);
		osd_status = OSDX_O18_Rd(osd_status_mon_data[xidx], reg_status_mon_data);

		osd_status &= 0xfffffff0;

		if(osd_status == OSD_STUCK_VALUE) stuck_cnt++;
		if((osd_status != 0x0 && osd_status != OSD_STUCK_VALUE ) || stuck_cnt >= 10 ) break;
	}

	FBDEV_WARN("osd0_sync status : %s (%d)\n", (stuck_cnt<10)? "ok":"fail", stuck_cnt);

	return (stuck_cnt<10)? RET_OK: RET_ERROR;
}

static int FBDEV_O18_CMN_SyncCheckTask(void* args)
{
	bool frozen;
	int	retry = 0;

	FBDEV_WARN("osd0_sync checking ..\n");

	set_freezable();

	while(!kthread_freezable_should_stop(&frozen))
	{
		/* if osd0 sync works, stop checker */
		if(RET_OK==FBDEV_O18_CMN_CheckSyncStatus())
		{
			break;
		}

		if(++retry > FBDEV_O18_SICDTV_4209_RETRY_MAX)
		{
			break;
		}

		/* retry the sync recovery */
		FBDEV_O18_CMN_SafeSyncEnable();

		/* sleep 8.3 ms (1 vsync for 120Hz) */
		usleep_range(8400, 8400*2);
	}

	return 0;
}

static void	FBDEV_O18_CMN_RunSyncChecker(void)
{
#ifdef FBDEV_O18_SICDTV_4209_STAGE2_FIX
	struct task_struct *tsk = NULL;

	tsk = kthread_create(FBDEV_O18_CMN_SyncCheckTask, NULL, "osd_sync_checker");
	FBDEV_CHECK_CODE(NULL==tsk, return, "can't ceate thread\n");

	wake_up_process(tsk);
#endif
}
#endif /* FBDEV_O18_SICDTV_4209_FIX */

static void FBDEV_O18_CMN_ReInitHW (void)
{
	FBDEV_O18_HW_CTX_T*	hw_ctx = FBDEV_O18_GET_HW_CTX();

	FBDEV_O18_InitHW();
	FBDEV_SetInterruptEnable(MIXER_INTR,1);

	/* O18 OSD supports only OSD0 & OSD3 */
	FBDEV_O18_InitOSDLayer(LX_FBDEV_ID_OSD0);
	FBDEV_O18_InitOSDLayer(LX_FBDEV_ID_OSD3);

	FBDEV_SetOSDImageEndian(LX_FBDEV_ID_OSD0, g_dm_ctx->wctx[LX_FBDEV_ID_OSD0]->pixel.bits_per_pixel);
	FBDEV_SetOSDImageEndian(LX_FBDEV_ID_OSD3, g_dm_ctx->wctx[LX_FBDEV_ID_OSD3]->pixel.bits_per_pixel);

    /* raxis.lim (2018/08/22)
	 * PIC_INIT should be set after initialzing all OSD layer if current booting mode is I-BOOT resume
	 * remember that FBDEV_O18_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR is set only when I-BOOT resume stage.
	 * refer to SICDTV-4209
	 */
    if (hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)
    {
#ifdef FBDEV_O18_SICDTV_4209_FIX
		FBDEV_O18_CMN_SafeSyncEnable();
		FBDEV_O18_CMN_RunSyncChecker();
#endif
    }
}

int	FBDEV_O18_CMN_ExecHWCommand	(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data)
{
	int	ret = RET_NOT_SUPPORTED;
	FBDEV_O18_HW_CTX_T*	hw_ctx = FBDEV_O18_GET_HW_CTX();

	switch(cmd)
	{
		case FBDEV_HW_CMD_IO_POSD_OPEN:
		{
			int fbdev_id = data->gen[0];	/* not used */

			FBDEV_HW_DEBUG("fb(%d) POSD_OPEN..\n", fbdev_id);
			FBDEV_O18_CMN_RunBootLogoTimer(fbdev_boot_freeze_timeout, FALSE);
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_IO_USER_POSD_RESOL_CHANGED:
		{
			int fbdev_id = data->gen[0];

			/* raxis.lim (2018/05/15) - EXPERIMENTAL
			 *
			 * if user changes current OSD output resolution (SCDCR-1459) when current OSD output is fully controlly by PQEFW (SICDTV-4359),
			 * it's necessary how to fix (or decide) this scensario conflict.
			 * I'll let the user control OSD output temporariliy !!
			 *
			 */
			if (fbdev_id == LX_FBDEV_ID_OSD0 && fbdev_osd0_user_out_win)
			{
				FBDEV_WARN("PAUSE_PQEFW_OSD0_OUT_CTRL enabled\n");
				hw_ctx->hw_wa_flag |= FBDEV_O18_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL;
			}
		}
		break;

		case FBDEV_HW_CMD_IO_VSYNC:
		{
			if ( hw_ctx->func.O18_ISRTickHandler )
			{
				hw_ctx->func.O18_ISRTickHandler();
			}
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_RD_VSYNC_CLK:
		{
			data->gen[0] = FBDEV_O18_CMN_DetectVSyncClk();
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_RD_DISP_SIZE:
		{
			data->gen[0] = hw_ctx->hw_disp_width;
			data->gen[1] = hw_ctx->hw_disp_height;
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_FREEZE:
		{
			/* raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL. ORBIT control will be re-enabled at THAW & RESTORE */
			hw_ctx->hw_wa_flag &= ~FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL;
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_SUSPEND:
		{
			/* raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL to re-enable at FBDEV_O18_CMN_EnableOSDHdrFlush() during RESUME */
			hw_ctx->hw_wa_flag &= ~FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL;
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_THAW:
		{
			/* raxis.lim (2017/09/18) -- enable PQEFW_OSD0_OUT_CTRL here becuase THAW stage doesn't configure any HW registers */
			hw_ctx->hw_wa_flag |= FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL;
			FBDEV_WARN("OSD0_PQEFW_OSD0_OUT_CTRL enabled\n");
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_RESTORE:
		{
			/* raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute. it will be enabled at FBDEV_O18_CMN_EnableOSDHdrFlush() */
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_RESUME:
		{
			/* raxis.lim (2017/08/22) -- fix for async behavior of OSD0_SYNC group */
			hw_ctx->hw_wa_flag |= FBDEV_O18_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
			FBDEV_WARN("OSD0_SYNC_ASYNC_WR enabled\n");

			/* raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute. it will be enabled at FBDEV_O18_CMN_EnableOSDHdrFlush() */
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_COMPLETE:
		{
			hw_ctx->hw_wa_flag &= ~FBDEV_O18_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
			ret = RET_OK;
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return ret;
}

/*========================================================================================
    Implementation Group (OSD Hdr Processing)
========================================================================================*/
static void	FBDEV_O18_CMN_WriteHdrRegsPostHandler ( int fb_dev_id, FBDEV_O18_OSD_HDR_T* osd_hdr, FBDEV_O18_OSD_EXHDR_T* osd_exhdr )
{
#ifdef FBDEV_O18_USE_3DOSD_HW_CTRL
	FBDEV_O18_HW_CTX_T*	hw_ctx = FBDEV_O18_GET_HW_CTX();

	if (!hw_ctx->b_support_3dosd)
	{
		FBDEV_HW_DEBUG("fb(%d) 3D not supported.\n", fb_dev_id ); return;
	}

	/* 3D HANDLER */
	{
		FBDEV_HW_CTX_T* hw_cmn_ctx = FBDEV_GET_HW_CTX();
		LX_FBDEV_TRID_CTRL_T* trid_ctrl = &(hw_cmn_ctx->fb[fb_dev_id].trid_ctrl);

		UINT32	disp_val_l	= 0x100;
		UINT32	disp_val_r	= 0x100;
		UINT32	disparity	= trid_ctrl->disparity;

#ifdef FBDEV_O18_USE_3DOSD_S3D
		UINT32	b_s3d_en	= (trid_ctrl->mode & (LX_FBDEV_TRID_MODE_SS|LX_FBDEV_TRID_MODE_TB))? 0x1: 0x0;
#endif
#ifdef FBDEV_O18_USE_3DOSD_2D3D
		UINT32  b_2d3d_en	= (trid_ctrl->mode & LX_FBDEV_TRID_MODE_2D_3D)? 0x1: 0x0;
#endif
#ifdef FBDEV_O18_USE_REVERSE_HW_CTRL
		BOOLEAN b_reverse_en= FBDEV_O18_CMN_IsReverseMode(fb_dev_id);
#else
		//BOOLEAN b_reverse_en= FALSE;
#endif

		UINT32	l_bmp_addr	= osd_hdr->osd_hdr_ptr_bmp;
		UINT32	r_bmp_addr	= l_bmp_addr;

		if ( trid_ctrl->mode != LX_FBDEV_TRID_MODE_2D )
		{
			if ( disparity > 0x40 ) disparity = 0x40;

			if ( trid_ctrl->mode & LX_FBDEV_TRID_MODE_EXT_DOWN )
			{
				disp_val_l	= 0x100 + disparity;	/* move L to right direction */
				disp_val_r	= 0x100 - disparity;	/* move R to left  direction */
			}
			else
			{
				disp_val_l	= 0x100 - disparity;	/* move L to left  direction */
				disp_val_r	= 0x100 + disparity;	/* move R to right direction */
			}
		}

		if (b_s3d_en)
		{
			if (trid_ctrl->mode & LX_FBDEV_TRID_MODE_SS ) /* S/S */
			{
				r_bmp_addr += ((osd_hdr->osd_hdr_w_mem * osd_exhdr->bits_per_pixel)>>3);
				//r_bmp_addr += (((osd_hdr->osd_hdr_w_mem>>1) * osd_exhdr->bits_per_pixel)>>3);

				//if ( b_reverse_en )
				//{
				//	UINT32 bmp_len = (osd_hdr->osd_hdr_wpl<<3) * osd_hdr->osd_hdr_h_mem;
				//	l_bmp_addr -= (bmp_len>>1); r_bmp_addr -= (bmp_len>>1);
				//}

				FBDEV_HW_DEBUG("fb(%d) s3d L:0x%08x, R:0x%08x\n", fb_dev_id, l_bmp_addr, r_bmp_addr );

			}
			else /* T/B */
			{
				r_bmp_addr += ((osd_hdr->osd_hdr_w_mem * (osd_hdr->osd_hdr_h_mem>>1) * osd_exhdr->bits_per_pixel)>>3);

				//if ( b_reverse_en )
				//{
				//	UINT32 bmp_len = (osd_hdr->osd_hdr_wpl<<3) * osd_hdr->osd_hdr_h_mem;
				//	l_bmp_addr -= (bmp_len); r_bmp_addr -= (bmp_len);
				//}
			}
		}

		/* FIXME: only single POSD per fb_dev_id is supported */
		switch (fb_dev_id)
		{
			case LX_FBDEV_ID_OSD0: /* OSD0 */
			{
				/* implement disparity config if needed */

#ifdef FBDEV_O18_USE_3DOSD_2D3D
				/* process 2Dto3D */
				OSDX_O18_RdFL(osdx_ctrl[0], osd_ctrl_scaler);

				if ( b_2d3d_en != OSDX_O18_Rd00(osdx_ctrl[0], osd_ctrl_scaler,osd_sc_vdouble) )
				{
					FBDEV_HW_DEBUG("fb(%d), 2d3d status change -> %d\n", fb_dev_id, b_2d3d_en );

					OSDX_O18_Wr01(osdx_ctrl[0], osd_ctrl_scaler, osd_sc_vdouble, b_2d3d_en);
					OSDX_O18_WrFL(osdx_ctrl[0], osd_ctrl_scaler);
				}
#endif

#ifdef FBDEV_O18_USE_3DOSD_S3D
				/* process S3D */
				OSDX_O18_RdFL(osdx_ctrl[0], osd_ctrl_main);

				if ( b_s3d_en != OSDX_O18_Rd00(osdx_ctrl[0], osd_ctrl_main, osd_s3d_en) )
				{
					FBDEV_HW_DEBUG("fb(%d), s3d status change -> %d\n", fb_dev_id, b_s3d_en );

					OSDX_O18_Wr01(osdx_ctrl[0], osd_ctrl_main, osd_s3d_en, b_s3d_en);
					OSDX_O18_WrFL(osdx_ctrl[0], osd_ctrl_main );
				}

				if (b_s3d_en)
				{
					OS_WrReg(0xc8024c00 + 0x2c, l_bmp_addr );
					OS_WrReg(0xc8024c00 + 0x34, r_bmp_addr );

					//hw_ctx->sw_hdr_rdy_ctrl[0].mif_hdr[0] = l_bmp_addr;
					//hw_ctx->sw_hdr_rdy_ctrl[0].mif_hdr[1] = r_bmp_addr;
					//atomic_set(&hw_ctx->sw_hdr_rdy_ctrl[0].mif_hdr_ready, 0x1);
				}
#endif
			}
			break;

			default:
			{
				/* O18 has only OSD0 layer for graphic plane */
			}
			break;
		}
	}
#endif // FBDEV_O18_USE_3DOSD_HW_CTRL
}

static void FBDEV_O18_CMN_InitMirrorEnv(void)
{
	int	xidx;
	int xnum, xlst[2];
	int	fb_dev_id = LX_FBDEV_ID_OSD0;

	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

	xidx = xlst[0];
	FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

	/* raxis.lim (2018/07/02) -- read mirror mode configuration set from boot loader */
	if(hw_ctx->mirror_ctrl.status == FBDEV_O18_MIRROR_NONE)
	{
		UINT32 hw_val;

		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
		OSDX_O18_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, hw_val);

		hw_ctx->mirror_ctrl.status = (hw_val)? FBDEV_O18_V_MIRROR_ON: 0x0;

		FBDEV_WARN("OSD v_mirror detected (%d)\n", hw_val);
	}
}

static void FBDEV_O18_CMN_SetupSRScaler(BOOLEAN onoff, BOOLEAN bForce)
{
	int	xidx;
	int xnum, xlst[2];
	UINT32 hw_onoff;
	int	fb_dev_id = LX_FBDEV_ID_OSD0;

	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();
	FBDEV_O18_SR_CTRL_T* sr_ctrl = &hw_ctx->sr_ctrl[fb_dev_id];

	PARAM_UNUSED(bForce);

	xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

	xidx = xlst[0];
	FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
	OSDX_O18_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, hw_onoff);
	hw_onoff ^= 1;
	FBDEV_HW_DEBUG("OSD SR(HW) = %d\n", hw_onoff);

	sr_ctrl->status   = (onoff)? FBDEV_O18_SR_STATUS_ON:FBDEV_O18_SR_STATUS_OFF;

#ifdef FBDEV_O18_USE_SR_CTRL
	/* configure OSD SR detour (= enable/disable OSD SR control)
	 *
	 * HOW TO enable OSD_SR
	 *
	 * 1. OSD SHP.core_ctrl.reg_top_bypass 		   -> 0x0
	 * 2. OSD.OSD0_BITMAP_CTRL0.reg_shp_detouor_en -> 0x0
	 * 3. OSD.OSD0_BITMAP_CTRL0.reg_rgb2yc_csc_en  -> 0x1
	 * 4. OSD.OSD0_BITMAP_CTRL0.reg_yc2rgb_csc_en  -> 0x1
	 */
	OSD_SHP_RdFL(shp_core_ctrl_00);
	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

	OSD_SHP_Wr01(shp_core_ctrl_00, reg_top_bypass, (onoff)? 0x0: 0x1);

	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, (onoff)?0x0:0x1);
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en, (onoff)?0x1:0x0);
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, (onoff)?0x1:0x0);	/* for B.OSD */
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_sosd_csc_en, (onoff)?0x1:0x0);	/* for S.OSD */
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_scaler_status_sel, 0x1);	/* FIXME: why ?? */
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_cubic_coeff_0, 0x0);		/* not used */

	OSD_SHP_WrFL(shp_core_ctrl_00);
	OSDX_O18_WrFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

	FBDEV_HW_DEBUG("OSD SR (%s)\n", (onoff)? "on":"off");
#else
	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, 0x1);
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en, 0x0);
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, 0x0);
	OSDX_O18_WrFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

	FBDEV_HW_DEBUG("OSD SR disabled (%s)\n", "off");
#endif

	/* if user ti_gain is defined, initialize HW configuration using the last user ti_gain.
	 * otherwise, initialize ti_gain using HW default value
	 */
#if 0 /* use the below code if GAIN should be restored automatically */
    if(hw_ctx->sr_ctrl[fb_dev_id].ti_gain>=0)
    {
		UINT32 gain = hw_ctx->sr_ctrl[fb_dev_id].ti_gain;

		OSD_SHP_RdFL(shp_lti_ctrl_00);
		OSD_SHP_Wr01(shp_lti_ctrl_00, reg_lti_2d_gain, gain);
		OSD_SHP_WrFL(shp_lti_ctrl_00);
    }
    else
#endif
    {
		UINT32 gain;

		OSD_SHP_RdFL(shp_lti_ctrl_00);
		OSD_SHP_Rd01(shp_lti_ctrl_00, reg_lti_2d_gain, gain);

		hw_ctx->sr_ctrl[fb_dev_id].ti_gain = gain;
	}
	FBDEV_HW_DEBUG("fb(0) sr_gain=0x%08x\n", hw_ctx->sr_ctrl[fb_dev_id].ti_gain);
}

/** initialize CROP to the default state.
 *
 */
static void FBDEV_O18_CMN_InitCropEnv	(void)
{
#ifdef FBDEV_O18_USE_FBC_CTRL

#else
	OSD_O18_RdFL(osd_cdc_crop_ctrl_0);
	OSD_O18_Wr(osd_cdc_crop_ctrl_0, 0x00000000);
	OSD_O18_WrFL(osd_cdc_crop_ctrl_0);

	FBDEV_HW_DEBUG("OSD CROP disabled (%s)\n", "off");
#endif
}

/** initialize FBC variable to the default state.
 *	The real HW register will be set inside FBDEV_O18_CMN_WriteOSDHeader()
 *	This function is also called during instant boot resume to setup AFBC register again.
 *
 */
static void FBDEV_O18_CMN_InitFBCEnv(void)
{
#ifdef FBDEV_O18_USE_FBC_CTRL
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();
	FBDEV_O18_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[LX_FBDEV_ID_OSD0];

	fbc_ctrl->fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW;
	fbc_ctrl->status  = FBDEV_O18_FBC_STATUS_NONE;
	FBDEV_O18_FBC_DEBUG("fb(%d) initialize fbc env\n", LX_FBDEV_ID_OSD0);

	/* raxis.lim (2016/10/05) -- try to initialize OSD to AFBC graphic path if possible
 	 * boot loader can display both non-AFBC and AFBC logo image, so I should keep the current
	 * graphic configuration.
	 * below codes will be active if cold boot or snapshot boot (not instant boot)
	 *
	 */
	{
		int hw_afbc_status = FBDEV_O18_CMN_GetHWStatus(FBDEV_O18_HW_STATUS_AFBC, NULL);

		FBDEV_O18_FBC_DEBUG("fb(%d) initial FBC mode = %d\n", LX_FBDEV_ID_OSD0, hw_afbc_status);

		/* recover FBC if AFBC display is used at boot loader */
		if (hw_afbc_status)
		{
			FBDEV_O18_FBC_DEBUG("fb(%d) recover FBC HW config\n", LX_FBDEV_ID_OSD0);
			FBDEV_O18_CMN_SetupFBC(LX_FBDEV_ID_OSD0, LX_FBDEV_FBC_FORMAT_AFBC);
		}
	}
#else
	/* TODO: do someting if nessary */
#endif
}

#ifdef FBDEV_O18_USE_FBC_CTRL
/** create or destory FBC envrionment
 *
 *
 *
 */
static void FBDEV_O18_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt)
{
	int	xidx;
	int xnum, xlst[2];

	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();
	FBDEV_O18_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];

	FBDEV_CHECK_CODE(fb_dev_id != LX_FBDEV_ID_OSD0, return, "invalid fb(%d)\n", fb_dev_id);

	/* check HW status */
	if (fbc_ctrl->fbc_fmt == fbc_fmt)
	{
#ifdef FBDEV_O18_SW_RECOVERY_AFBC_FLAG_CORRUPTION
		int hw_afbc_status = FBDEV_O18_CMN_GetHWStatus(FBDEV_O18_HW_STATUS_AFBC, NULL);

		hw_afbc_status = (hw_afbc_status)? LX_FBDEV_FBC_FORMAT_AFBC: LX_FBDEV_FBC_FORMAT_RAW;
		FBDEV_CHECK_CODE(fbc_ctrl->fbc_fmt != hw_afbc_status, goto afbc_config,
						"<!> sw/hw status mismatch (sw:%d, hw:%d)\n", fbc_ctrl->fbc_fmt, hw_afbc_status);
#endif
		return; /* same value. do nothing */
	}

#ifdef FBDEV_O18_SW_RECOVERY_AFBC_FLAG_CORRUPTION
afbc_config:
#endif
	xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );
	xidx = xlst[0];

#ifndef FBDEV_O18_USE_AFBC_DATA_PATH_CHANGE_ISR_HANDLER
	OSD_TOP_O18_RdFL(ctrl_dpath);
#endif
	OSD_TOP_O18_RdFL(ctrl_auto_init_afbc);

	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_swap);
	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_pdec);

	AFBC0_CTRL_RdFL(ctrl_afbc_0);

	if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
	{
		FBDEV_O18_FBC_DEBUG("setup fbc_fmt = 0x1 (enable AFBC mode)\n");

#ifndef FBDEV_O18_USE_AFBC_DATA_PATH_CHANGE_ISR_HANDLER
		OSD_TOP_O18_Wr01(ctrl_dpath, osd0_afbc_en, 0x1 );
#endif

		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,		0x1 );
		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en, 	0x1 );

		/* raxis.lim (2019/01/08) select pulse source. B.OSD=0, S.OSD=1 */
		if(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
		{
			OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_src, 	0x0 );
		}
		else
		{
			OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_src, 	0x1 );
		}

		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, idx_afbc0_pic_init_src,   0x0 );

		if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
		{
			OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_src, 	0x0 );
		}
		else
		{
			/* prevent OSD distortion when S.OSD path is used. refer to AVTASK-327 */
			OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_src, 	0x1 );
		}

		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en, 		0x0 );
		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en, 	0x0 );
		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, idx_afbc1_pic_init_src,   0x1 );

		/* setup PDEC - swap pixel byte order from GBRA to ARGB to read data from GFX and GPU
		 *
		 * NOTE : O18/O18 test cmm uses 0x3900_0000 but I won't use this value
		 *		  sungmin.hong said that 0x3900_0000 is used for the OSD stand-alone test
 		 *
		 * refer to SICDTV-649
		 *
		 */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_alpha,	0x3 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_red,		0x2 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_green,	0x1 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_blue,	0x0 );

		/* disable bitmap swap
		 *
		 * NOTE :
		 * in O18,  osd_ctrl_swap value is set to 0x0000_0000 (it means the bitmap swap disable)
		 * in O18 test cmm uses 0x000_0443.. hmm...
		 * In O18  test cmm uses 0x000_0443...hmm
		 *
		 * I will use 0x000_0000
		 *
		 **/
#if 0
        OSDX_O18_Wr  (osdx_ctrl[xidx], osd_ctrl_swap, 	0x00000443);
#else
        OSDX_O18_Wr  (osdx_ctrl[xidx], osd_ctrl_swap, 	0x00000000);
#endif
		/* enable BITMAP mode */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_main,	osd_bitmap_only_mode_en, 0x1 );

		/* enable update_flag to prevent SW,HW sync mismatch. DON'T turn off */
		AFBC0_CTRL_Wr01(ctrl_afbc_0, update_ready_flag_en,				0x1 );

		fbc_ctrl->status |=  FBDEV_O18_FBC_STATUS_PATH_CHANGE;;
	}
	else
	{
		FBDEV_O18_FBC_DEBUG("setup fbc_fmt = 0x0 (disable AFBC mode)\n");

#ifndef FBDEV_O18_USE_AFBC_DATA_PATH_CHANGE_ISR_HANDLER
		OSD_TOP_O18_Wr01(ctrl_dpath, osd0_afbc_en, 0x0 );
#endif

		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,		0x0 );
		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en, 	0x0 );
		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en, 		0x0 );
		OSD_TOP_O18_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en, 	0x0 );

		/* setup PDEC - ARGB bypass (default in raw mode) */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_alpha,	0x0 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_red,		0x1 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_green,	0x2 );
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_blue,	0x3 );

		/* enable bitmap swap - default in raw mode) */
        OSDX_O18_Wr  (osdx_ctrl[xidx], osd_ctrl_swap, 	0x00000333);

		/* disable BITMAP mode (default in raw mode) */
		OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_main,	osd_bitmap_only_mode_en, 0x0 );

		fbc_ctrl->status &= ~FBDEV_O18_FBC_STATUS_HDR_SETUP;
		fbc_ctrl->status |=  FBDEV_O18_FBC_STATUS_PATH_CHANGE;
	}

	FBDEV_O18_FBC_DEBUG("fb(%d) fbc_mode=0x%x setup %d.pdec=0x%08x\n", fb_dev_id,
			fbc_fmt, xidx, OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_pdec));

	OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
	OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_swap);
	OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_pdec);

#ifndef FBDEV_O18_USE_AFBC_DATA_PATH_CHANGE_ISR_HANDLER
	OSD_TOP_O18_WrFL(ctrl_dpath);
#endif
	OSD_TOP_O18_WrFL(ctrl_auto_init_afbc);

	AFBC0_CTRL_WrFL(ctrl_afbc_0);

	fbc_ctrl->fbc_fmt = fbc_fmt;
}

static void FBDEV_O18_CMN_WriteFBCHdrRegs(int fb_dev_id, FBDEV_O18_OSD_HDR_T* osd_hdr, FBDEV_O18_OSD_EXHDR_T* osd_exhdr)
{
	FBDEV_O18_HW_CTX_T*   hw_ctx = FBDEV_O18_GET_HW_CTX();
	FBDEV_O18_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];
	FBDEV_O18_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

	int	osd_img_w	= osd_hdr->osd_hdr_w_mem;
	int	osd_img_h	= osd_hdr->osd_hdr_h_mem;
	int	osd_img_stride = osd_exhdr->img_stride;
	int osd_img_bytes_per_pixel = FBDEV_O18_BITS_2_BYTES(osd_exhdr->bits_per_pixel);

	if (fb_dev_id == LX_FBDEV_ID_OSD0 && fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC )
	{
		/* FIXME: What's AFBC dimension FBDEV_O18_BITS_2_BYTES(canvas.bits_per_pixel);> */
		UINT32 fbc_hdr_size = afbc_sw_get_header_size(NULL, osd_img_w, osd_img_h);
		UINT32 fbc_hdr_addr = osd_hdr->osd_hdr_ptr_bmp;

		FBDEV_O18_FBC_DEBUG("fbc_hdr_addr=0x%08x (sz=0x%x) fbc_body_addr=0x%08x\n",
			fbc_hdr_addr,  fbc_hdr_size, fbc_hdr_addr+fbc_hdr_size);

		/* raxis.lim (2015/10/12)
		 * according to the board test, during AFBC mode, OSD HW doesn't look at frame buffer set by osd_hdr.
		 * So we DON'T need the below offset change of frame buffer.
		 * I'll keep the current framebuffer rather than changing offset.
		 */
#if 1
		osd_hdr->osd_hdr_ptr_bmp += fbc_hdr_size;
		FBDEV_O18_FBC_DEBUG("afbc - osd_hdr_ptr_bmp : 0x%08x\n", osd_hdr->osd_hdr_ptr_bmp );
#endif

		if(fbc_ctrl->status & FBDEV_O18_FBC_STATUS_HDR_SETUP)
		{
			AFBC0_CTRL_RdFL(ctrl_afbc_1);
			AFBC0_CTRL_RdFL(ctrl_afbc_3);
			AFBC0_CTRL_RdFL(ctrl_afbc_4);
			AFBC0_CTRL_RdFL(ctrl_afbc_8);

			AFBC0_CTRL_Wr01(ctrl_afbc_1, hd_base, 	   fbc_hdr_addr);
			AFBC0_CTRL_Wr01(ctrl_afbc_8, pl_data_base, fbc_hdr_addr);

			AFBC0_CTRL_Wr01(ctrl_afbc_3, end_x,			LX_CALC_ALIGNED_VALUE(osd_img_w-2,1));
			AFBC0_CTRL_Wr01(ctrl_afbc_3, end_y,			osd_img_h-1);

			AFBC0_CTRL_Wr01(ctrl_afbc_4, img_width,		osd_img_stride/osd_img_bytes_per_pixel);

			AFBC0_CTRL_WrFL(ctrl_afbc_1);
			AFBC0_CTRL_WrFL(ctrl_afbc_3);
			AFBC0_CTRL_WrFL(ctrl_afbc_4);
			AFBC0_CTRL_WrFL(ctrl_afbc_8);
		}
		else
		{
			AFBC0_CTRL_RdFL(ctrl_afbc_0);
			AFBC0_CTRL_RdFL(ctrl_afbc_1);
			AFBC0_CTRL_RdFL(ctrl_afbc_2);
			AFBC0_CTRL_RdFL(ctrl_afbc_3);
			AFBC0_CTRL_RdFL(ctrl_afbc_4);
			AFBC0_CTRL_RdFL(ctrl_afbc_5);
//			AFBC0_CTRL_RdFL(ctrl_afbc_6);
//			AFBC0_CTRL_RdFL(ctrl_afbc_7);
			AFBC0_CTRL_RdFL(ctrl_afbc_8);
			AFBC0_CTRL_RdFL(ctrl_afbc_9);
//			AFBC0_CTRL_RdFL(ctrl_afbc_a);
//			AFBC0_CTRL_RdFL(ctrl_afbc_b);
			AFBC0_CTRL_RdFL(ctrl_afbc_c);
//			AFBC0_CTRL_RdFL(ctrl_afbc_d);
//			AFBC0_CTRL_RdFL(ctrl_afbc_e);
//			AFBC0_CTRL_RdFL(ctrl_afbc_f);
			AFBC0_CTRL_RdFL(ctrl_afbc_10);

			/* HW guy said that I should set the same value to AFBC hdr & data :(
			 * I think it's enough to change only below two value (hd_base, pl_data_base)
			 */
			AFBC0_CTRL_Wr01(ctrl_afbc_1, hd_base, 	   fbc_hdr_addr);
			AFBC0_CTRL_Wr01(ctrl_afbc_8, pl_data_base, fbc_hdr_addr);
			AFBC0_CTRL_Wr01(ctrl_afbc_9, pl_data_end,  0xffffffff);

			/* AFBC data size description
			 *
		 	 */
			AFBC0_CTRL_Wr01(ctrl_afbc_2, start_x, 	0);
			AFBC0_CTRL_Wr01(ctrl_afbc_2, start_y, 	0);

			AFBC0_CTRL_Wr01(ctrl_afbc_3, end_x, 	LX_CALC_ALIGNED_VALUE(osd_img_w-2,1));
			AFBC0_CTRL_Wr01(ctrl_afbc_3, end_y, 	osd_img_h-1);

			AFBC0_CTRL_Wr01(ctrl_afbc_4, img_width,		osd_img_stride/osd_img_bytes_per_pixel);

			/* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
			 *
			 * HW guy fixed dec_buf_depth value to 959 and pl_buf_depth value to 255.
			 */
			AFBC0_CTRL_Wr01(ctrl_afbc_5, dec_buf_depth_m1, 959);
			AFBC0_CTRL_Wr01(ctrl_afbc_5, pl_buf_depth_m1,  255);

			//AFBC0_CTRL_Wr(ctrl_afbc_6, 0x00000000);	/* dummy */
			//AFBC0_CTRL_Wr(ctrl_afbc_7, 0x00000000);	/* dummy */
			//AFBC0_CTRL_Wr(ctrl_afbc_a, 0x00000000);	/* dummy */
			//AFBC0_CTRL_Wr(ctrl_afbc_b, 0x00000000);	/* dummy */

			/* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
			 *
			 * HW test value : 0x0011_FF54
			 */
			AFBC0_CTRL_Wr01(ctrl_afbc_c, hd_endian_arb, 1);		/* no description :( */
			AFBC0_CTRL_Wr01(ctrl_afbc_c, pl_endian_arb, 1);		/* no description :( */
			AFBC0_CTRL_Wr01(ctrl_afbc_c, hd_endian_sw,	0xf);	/* ambiguous description :( */
			AFBC0_CTRL_Wr01(ctrl_afbc_c, pl_endian_sw,	0xf);	/* ambiguous description :( */
			AFBC0_CTRL_Wr01(ctrl_afbc_c, pl_gmau_id, 	5);		/* difficult to understand description :( */
			AFBC0_CTRL_Wr01(ctrl_afbc_c, hd_gmau_txid, 	4);		/* difficult to understand description :( */

			//AFBC0_CTRL_Wr(ctrl_afbc_d, 0x00000000);	/* dummy */
			//AFBC0_CTRL_Wr(ctrl_afbc_e, 0x00000000);	/* dummy */

			//AFBC0_CTRL_Wr(ctrl_afbc_f, 0x00000000);

			/* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
			 *
			 * 0xff80_80ff @RGBA
			 * 0xffff_8080 @ARGB (*)
			 *
			 * I 've used 0xffff_fffff since O18 AFBC integration
			 */
			#if 0
			AFBC0_CTRL_Wr(ctrl_afbc_10, 0xffff8080);	/* +0xD0 : 0xffff8080 for argb case */
			#else
			AFBC0_CTRL_Wr(ctrl_afbc_10, 0xFFFFFFFF);	/* +0xD0 : 0xffffffff for argb case */
			#endif

			AFBC0_CTRL_Wr01(ctrl_afbc_0, start, 		0);
			AFBC0_CTRL_Wr01(ctrl_afbc_0, ready, 		0);
			AFBC0_CTRL_Wr01(ctrl_afbc_0, sw_reset, 		0);
			AFBC0_CTRL_Wr01(ctrl_afbc_0, sw_reset_fifo, 0);
			AFBC0_CTRL_Wr01(ctrl_afbc_0, run_mode, 		1);
			AFBC0_CTRL_Wr01(ctrl_afbc_0, pl_addr_mode,	1);
			AFBC0_CTRL_Wr01(ctrl_afbc_0, sw_reset_ack,	0);
			AFBC0_CTRL_Wr01(ctrl_afbc_0, gmau_arb_sw_reset, 0);

			AFBC0_CTRL_Wr01(ctrl_afbc_0, flip_mode, 	(mirror_ctrl->status & FBDEV_O18_V_MIRROR_ON)? 1:0);

			AFBC0_CTRL_Wr01(ctrl_afbc_0, ignore_q_full, 0);
			AFBC0_CTRL_Wr01(ctrl_afbc_0, wrap_en, 		1);

			/* flush data */
			AFBC0_CTRL_WrFL(ctrl_afbc_1);
			AFBC0_CTRL_WrFL(ctrl_afbc_2);
			AFBC0_CTRL_WrFL(ctrl_afbc_3);
			AFBC0_CTRL_WrFL(ctrl_afbc_4);
			AFBC0_CTRL_WrFL(ctrl_afbc_5);
			//AFBC0_CTRL_WrFL(ctrl_afbc_6);
			//AFBC0_CTRL_WrFL(ctrl_afbc_7);
			AFBC0_CTRL_WrFL(ctrl_afbc_8);
			AFBC0_CTRL_WrFL(ctrl_afbc_9);
			//AFBC0_CTRL_WrFL(ctrl_afbc_a);
			//AFBC0_CTRL_WrFL(ctrl_afbc_b);
			AFBC0_CTRL_WrFL(ctrl_afbc_c);
			//AFBC0_CTRL_WrFL(ctrl_afbc_d);
			//AFBC0_CTRL_WrFL(ctrl_afbc_e);
			//AFBC0_CTRL_WrFL(ctrl_afbc_f);
			AFBC0_CTRL_WrFL(ctrl_afbc_10);
			AFBC0_CTRL_WrFL(ctrl_afbc_0);
		}

		fbc_ctrl->status |= FBDEV_O18_FBC_STATUS_HDR_SETUP;
	}
}

static void FBDEV_O18_CMN_FlushFBCHdrRegs(int fb_dev_id)
{
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();
	FBDEV_O18_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];

	if (fb_dev_id == LX_FBDEV_ID_OSD0 && fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC )
	{
		AFBC0_CTRL_Wr01(ctrl_afbc_0, update_ready_flag, 0x1);

		FBDEV_O18_FBC_DEBUG("fb(%d) flush AFBC regs\n", fb_dev_id);
		AFBC0_CTRL_WrFL(ctrl_afbc_0);
	}
}
#endif

/** write real header data to register
 *
 *
 *
 */
void	FBDEV_O18_CMN_WriteHdrRegs	(int fb_dev_id, FBDEV_O18_OSD_HDR_T* osd_hdr, FBDEV_O18_OSD_EXHDR_T* osd_exhdr)
{
	int		xidx;
	int		xnum;
	int		xlst[2];
	UINT32* hdr;

	ULONG   flags;
	struct scanvas* hCanvas = NULL;
	FBDEV_WIN_CTX_T* wctx	= NULL;
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	hCanvas = FBDEV_GetWinCanvas( fb_dev_id );
	FBDEV_CHECK_CODE(NULL==hCanvas, return, "invalid canvas. fb(%d)\n", fb_dev_id );

	wctx = FBDEV_GetWinCtx(fb_dev_id);
	FBDEV_CHECK_CODE(NULL==wctx, return, "invalid winctx. fb(%d)\n", fb_dev_id );

	xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
	/* ignore noisy warning msg becase some OSD layer is not supported by HW */
	FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "invalid xnum %d. fb(%d)\n", xnum, fb_dev_id );

	FBDEV_O18_HDR_DEBUG("fb(%d) xidx = %d\n", fb_dev_id, xlst[0]);

	spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

	xidx = xlst[0];

	/* notify osd freeze for debug */
	if ( !wctx->status.b_osd_hdr_flush )
	{
        UINT32 disp_fbmem;
        OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);
        disp_fbmem = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);

		FBDEV_WARN("fb(%d) freezed. osd_hdr_flush deferred. keep 0x%08x\n", fb_dev_id, disp_fbmem );
	}

	if (wctx->status.b_osd_hdr_flush)
	{
		hdr= (UINT32*)osd_hdr;

		OSDX_O18_Wr(osdx_ctrl[xidx], osd_ctrl_hdr0, hdr[0]);
		OSDX_O18_Wr(osdx_ctrl[xidx], osd_ctrl_hdr1, hdr[1]);
		OSDX_O18_Wr(osdx_ctrl[xidx], osd_ctrl_hdr2, hdr[2]);
		OSDX_O18_Wr(osdx_ctrl[xidx], osd_ctrl_hdr3, hdr[3]);
		OSDX_O18_Wr(osdx_ctrl[xidx], osd_ctrl_hdr4, hdr[4]);
		OSDX_O18_Wr(osdx_ctrl[xidx], osd_ctrl_hdr5, hdr[5]);
		OSDX_O18_Wr(osdx_ctrl[xidx], osd_ctrl_hdr6, hdr[6]);

		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr1);

		/* raxis.lim (2017/09/15) -- DO NOT write OSD out_win only
		   when OSD0_PQEFW_OSD0_OUT_CTRL is enabled and TEMP_PAUSE is not enabled

		   raxis.lim (2018/05/15)
		   Remember that FBDEV_O18_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL is enabled temporarily when user changes OSD output resolution
		*/
    	if(fb_dev_id == LX_FBDEV_ID_OSD0)
		{
			if(fbdev_pqefw_osd0_out_ctrl &&
			   (hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL) &&
			   !(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL))
			{
				/* do nothing */
			}
			else
			{
				FBDEV_WARN("fb(%d) flush OSD0_CTRL_HDR2\n", fb_dev_id);
				OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
			}
		}
		else
		{
			OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
		}

		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr3);
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr4);
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr5);
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr6);


	#ifdef FBDEV_O18_USE_FBC_CTRL
		if (fb_dev_id == LX_FBDEV_ID_OSD0)
		{
			FBDEV_O18_CMN_SetupFBC(fb_dev_id, hCanvas->fbc_fmt);

			if( hCanvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC )
			{
				FBDEV_O18_CMN_WriteFBCHdrRegs(fb_dev_id, osd_hdr, osd_exhdr);
			}
		}
	#endif
	#ifdef FBDEV_O18_USE_FBC_CTRL
		FBDEV_O18_CMN_FlushFBCHdrRegs(fb_dev_id);
	#endif

	#ifdef FBDEV_O18_FIX_INVALID_OSD_HDR_ADDR_REG_ACCESS
		OSDX_O18_Wr(osdx_ctrl[xidx], osd_base_addr, hdr[6]);
		OSDX_O18_WrFL(osdx_ctrl[xidx], osd_base_addr);
	#endif

		/* raxis.lim (2018/04/09) -- sync between OSD_SHP (OSD_SR) and OSD out info
		 * O18 doesn't have any limitation regarding OSD_SR size.
	 	 * but core_ctrl_01's width, height should have the same value with output_win to prevent image corruption.
		 * refer to SICDTV-4853
		 */
		if (fb_dev_id == LX_FBDEV_ID_OSD0)
		{
			UINT32	osd_shp_width, osd_shp_height;

			OSD_SHP_RdFL(shp_core_ctrl_01);
			OSD_SHP_Rd01(shp_core_ctrl_01, reg_top_width, osd_shp_width );
			OSD_SHP_Rd01(shp_core_ctrl_01, reg_top_height,osd_shp_height);

			if(osd_shp_width != osd_hdr->osd_hdr_w_out || osd_shp_height != osd_hdr->osd_hdr_h_out)
			{
				/* raxis.lim (2018/11/01) -- DO NOT write OSD_SHP
				   when OSD0_PQEFW_OSD0_OUT_CTRL is enabled and TEMP_PAUSE is not enabled
				 */
				if(fbdev_pqefw_osd0_out_ctrl &&
				   (hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL) &&
				   !(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL))
				{
					/* do nothing */
				}
				else
				{
					FBDEV_WARN("osd_shp's size changed (%d,%d) -> (%d,%d)\n",
							osd_shp_width, osd_shp_height, osd_hdr->osd_hdr_w_out, osd_hdr->osd_hdr_h_out);

					OSD_SHP_Wr01(shp_core_ctrl_01, reg_top_width, osd_hdr->osd_hdr_w_out);
					OSD_SHP_Wr01(shp_core_ctrl_01, reg_top_height,osd_hdr->osd_hdr_h_out);
					OSD_SHP_WrFL(shp_core_ctrl_01);
				}
			}
		}

		/* turn off TEMP_PAUSE because OSD update is completed */
		if(fb_dev_id == LX_FBDEV_ID_OSD0 && fbdev_pqefw_osd0_out_ctrl)
		{
			if(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)
			{
				FBDEV_WARN("PAUSE_PQEFW_OSD0_OUT_CTRL disabled (%d,%d)\n",
					(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL)? 1:0,
					(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)? 1:0);
				hw_ctx->hw_wa_flag &= ~FBDEV_O18_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL;
			}
		}

		g_osd_o18_reg->osdx_ctrl[xidx].osd_ctrl_main.osd_hdr_ready_flag = 0x1;

		FBDEV_O18_HDR_DEBUG("fb(%d) flush osd_hdr regs/data\n", fb_dev_id);

		FBDEV_O18_CMN_WriteHdrRegsPostHandler( fb_dev_id, osd_hdr, osd_exhdr );
	}

	spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);
}

/** OSD HW common header generator
 *
 *  OSD HW header is made based on struct scanvas data and extra environment such as 3DOSD, reverse etc.
 *
 */
static int FBDEV_O18_CMN_WriteOSDHeader(struct scanvas *pCanvas)
{
	int						fb_dev_id;
	UINT32					bitmap_ptr;
	FBDEV_O18_OSD_HDR_T		osd_hdr;
	FBDEV_O18_OSD_EXHDR_T	osd_exhdr;
	struct scanvas			canvas;

	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	UINT32  disp_width = hw_ctx->hw_disp_width;
	UINT32  disp_height= hw_ctx->hw_disp_height;

	FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(pCanvas->fb_dev_id);
	FBDEV_CHECK_CODE(NULL==wctx, return RET_ERROR, "invalid winctx. fb(%d)\n", pCanvas->fb_dev_id);

	/* clear osd_hdr before writing */
	memset(&osd_hdr,   0x0, sizeof(FBDEV_O18_OSD_HDR_T));
	memset(&osd_exhdr, 0x0, sizeof(FBDEV_O18_OSD_EXHDR_T));
	memcpy(&canvas,	   pCanvas, sizeof(struct scanvas));

	fb_dev_id = canvas.fb_dev_id;

	/* raxis.lim (2016/08/08) - if OSD is freezed, DO NOT handle/write any registers
	 *
	 * This patch seems to prevent OSD garbage during transition from non AFBC (boot logo) to AFBC (mercury/webOS) screen.
	 * Originally, osd_hdr_flush is checked at FBDEV_O18_CMN_WriteHdrRegs().
	 * I don't know the below code really prevents OSD garbage rather than the original policy.
	 * <!> More tests are required.
	 *
	 */
	if ( !wctx->status.b_osd_hdr_flush )
	{
		int	xidx, xnum, xlst[2];
       	UINT32 disp_fbmem = 0x0;

		xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
		xidx = xlst[0];

		if(!INVALID_XNUM(xnum))
		{
			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);
			disp_fbmem = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);
		}

		FBDEV_WARN("fb(%d) freezed. osd_hdr_flush deferred & keep fbmem 0x%08x.", fb_dev_id, disp_fbmem);

		return RET_OK;
	}

	switch(fb_dev_id)
	{
		case LX_FBDEV_ID_CSR0:
		{
			int	csr_x_max;
			int csr_x_off, csr_y_off, csr_x_pos, csr_y_pos, csr_x_size, csr_y_size;
			int csr_disp_w, csr_disp_h;

#ifdef FBDEV_O18_USE_UNLIMITED_CURSOR_POSITION
			int left_min_pxl = FBDEV_O18_BYTES_2_PIXEL(FBDEV_O18_GMAU_WORD_BYTES);	/* 16 bytes -> 4 pixel */
#endif
			FBDEV_O18_HDR_DEBUG("cursor_pos req(%d,%d)\n", canvas.output_win.x, canvas.output_win.y );

			// csr_disp_w is used to check if cursor is located at the right corner.
			// this value is set to 3840 in UHD mode, 1920 in FHD mode
			csr_disp_w = hw_ctx->hw_disp_width;
			csr_disp_h = hw_ctx->hw_disp_height;

			// scale x,y value including hotspot according to the current OSD path and OSD output dimension.
			// note that this tune should be done for each SoC
			//
			// raxis.lim (2016/04/18)
			// - tune UHD B.OSD case based on FPGA
			// - FHD B.OSD is not tested !
			//
			if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
			{
				if( FBDEV_O18_CMN_IsUHDDispMode() )
				{
					canvas.output_win.x  *= 2;		// scale by 2 in X direction
					canvas.csr_hotspot.x *= 2;
					canvas.output_win.y  *= 2;		// scale by 2 in Y direction
					canvas.csr_hotspot.y *= 2;
				}
				else /* FHD resolution (signage or commercial TV) */
				{
					//csr_disp_w			/= 2;	// bypass x & w info in FHD (raxis.lim 2017/01/24)
					//canvas.output_win.x	/= 2;	// remember that each SoC shows different behavior (due to PQE implementation?)
					//canvas.csr_hotspot.x 	/= 2;	// So TEST IS THE KEY to confirm cursor behavior.
				}
			}
			else /* S.OSD will use FHD resolution. so don't modify cursor info */
			{
				/* do nothing */
			}

            // if cursor csr_hotspot is active then adjust (x,y) position of cursor layer.
            // if cursor position is negative, I should move the bitmap address ( H/W doesn't accept negative position )
            //
            // IMPORTATNT !! if you change the base address, its alignment should be multiplt of 16 byte ( not 8 byte )
            // woonghyeon just said that it may be H/W bug.
            // since we are using ARGB8888 pixel format for cursor OSD. cursor offset should be multiple of 4 !!
			//
			//
			// I prefer to use the right size of cursor region as csr_x_size and csr_y_size
			//
			csr_x_max = canvas.stride / FBDEV_O18_BITS_2_BYTES(canvas.bits_per_pixel);

			csr_x_off = 0;
			csr_y_off = 0;

			csr_x_pos = canvas.output_win.x - canvas.csr_hotspot.x;
			csr_y_pos = canvas.output_win.y - canvas.csr_hotspot.y;

			csr_x_size= (canvas.csr_size.w>0)? LX_CALC_ALIGNED_VALUE(canvas.csr_size.w,2): canvas.input_win.w;
			csr_y_size= (canvas.csr_size.h>0)? canvas.csr_size.h : canvas.input_win.h;

			FBDEV_O18_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d info( %dx%d h %d,%d ) max_x %d disp_x %d\n", fb_dev_id,
						csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
						canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y,
						csr_x_max, csr_disp_w );

#ifdef FBDEV_O18_USE_UNLIMITED_CURSOR_POSITION
			// raxis.lim (2015/07/24)
			// if cursor is located at far left corner, we should try to hide cursor.
			// implementation is very simple. just show the only right 4 pixel becuase their region is filled with empty color
			if (csr_x_pos < -(csr_x_size-left_min_pxl))
			{
				csr_x_off = (csr_x_max-left_min_pxl);
				csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,2);

				csr_x_size= left_min_pxl;
				csr_x_pos = 0;
			}
			else
#endif
			// if cursor is at the left side, we calculate csr_x_pos and to change the frame buffer address
			// cursor viewing area should be shrinked by changing csr_x_size
			if (csr_x_pos < 0)
			{
				csr_x_off = -csr_x_pos;
				csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,2);

				//csr_x_size -= csr_x_off;			// new csr_x_size becomes smaller values from app-defined cursor size
				csr_x_size = csr_x_max - csr_x_off;	// new csr_x_size becomes smaller values from csr_x_max
				csr_x_pos = 0;
			}

			// if cursor is at the top side, we calculate csr_y_pos to change the frame buffer address
			if (csr_y_pos < 0)
			{
				csr_y_off = -csr_y_pos;
				csr_y_pos = 0;
				csr_y_size -= csr_y_off;
			}

			// prevent OSD garbage. effective cursor width should be less than the real surface width
			if (csr_x_size > csr_x_max)	csr_x_size = csr_x_max;

			// if cursor is located at the right corner, I should gaurantee the minimal viewing area of cursor.
			// without it, cursor image will be broken :(
			// see the description for FBDEV_O18_CSR_MIN_WIDTH
			if (csr_x_pos + csr_x_size > csr_disp_w )
			{
#ifdef FBDEV_O18_USE_UNLIMITED_CURSOR_POSITION
				// raxis.lim (2015/07/24)
				// hide cursor will not be shown at the right corner
				// keep in mind that OSD garbage might be shown because I don't gaurantee the minimum viewing area
				if (csr_x_pos > csr_disp_w )
				{
					csr_x_pos = csr_disp_w;
				}
#else
				if (csr_x_pos > csr_disp_w-FBDEV_O18_CSR_MIN_WIDTH)
				{
					csr_x_pos = csr_disp_w-FBDEV_O18_CSR_MIN_WIDTH;
				}
#endif
				csr_x_pos	= LX_CALC_ALIGNED_VALUE(csr_x_pos,2);	/* make X pos is aligned by 4 */

				csr_x_size	= csr_disp_w-csr_x_pos;

				// software workaround for 1x cursor display on blend path
				// On blend path, cursor size should be displayed x2 automatically because OSD disp size is 3840x2160
				// and cursor region is set based on 1920x1080 area
				// if 2x scale up is not supported, I should multiply csr_x_size by double manually
				if ( hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_1X_CSR_DISP_ON_BLEND_PATH )
				{
					if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
					{
						csr_x_size *= 2;
						if ( csr_x_size > csr_x_max ) csr_x_size = csr_x_max;
					}
				}
   			}

			if (csr_y_pos > csr_disp_h-FBDEV_O18_CSR_MIN_HEIGHT)
			{
				csr_y_pos = csr_disp_h-FBDEV_O18_CSR_MIN_HEIGHT;
			}

			osd_hdr.osd_hdr_xpos	= csr_x_pos;	/* output x (csr x pos) */
			osd_hdr.osd_hdr_ypos	= csr_y_pos;	/* output y (csr y pos) */
			osd_hdr.osd_hdr_w_mem	= csr_x_size;	/* viewing cursor width */
			osd_hdr.osd_hdr_h_mem	= csr_y_size;	/* viewing cursor height */
			osd_hdr.osd_hdr_w_out	= csr_x_size;	/* output w */
			osd_hdr.osd_hdr_h_out	= csr_y_size;	/* output h */

			/* gMAU requests 16byte aligned address */
			bitmap_ptr = canvas.osd_bm_paddr;
            bitmap_ptr += ( csr_y_off * canvas.stride ) + FBDEV_O18_GMAU_ALIGNED_BYTES(csr_x_off * FBDEV_O18_BITS_2_BYTES(canvas.bits_per_pixel));

			osd_hdr.osd_hdr_pixel_order	= canvas.pixel_order_en;
			osd_hdr.osd_hdr_wpl 		= FBDEV_O18_BYTES_2_OSD_WORDS(canvas.stride);

			FBDEV_O18_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d <- req( %dx%d h %d,%d)\n", fb_dev_id,
						csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
						canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y );
			FBDEV_O18_HDR_DEBUG("fb(%d) cursor pre-processing done\n", fb_dev_id);
		}
		break;

		case LX_FBDEV_ID_OSD0:
		default:
		{
			if( FBDEV_O18_CMN_IsUHDDispMode() && (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) )
			{
				// raxis.lim (2018/08/18)
				//
				// some apps/platforms doesn't know the UHD display resolution and try to configure output
				// to FHD resolution as they did in FHD DTV. in that cases, I assume that apps set the
				// wrong output configuration and they want full-sized image display
				//
				// if output size is less than display size, I will treait it as wrong information, ignore user
				// value and use display resolution for input image to be displayed to the full screen.
				//
				if(fbdev_osd0_user_out_win &&canvas.user_win_ctrl_en)
				{
					// keep the user configuration. DO NOT modify output_win in kdriver
				}
				else
				{
					canvas.output_win.w = disp_width;
					canvas.output_win.h = disp_height;
				}
			}

			if (canvas.input_win.w > disp_width )	canvas.input_win.w = disp_width;
			if (canvas.input_win.h > disp_height)	canvas.input_win.h = disp_height;
			if (canvas.output_win.w > disp_width )	canvas.output_win.w = disp_width;
			if (canvas.output_win.h > disp_height)	canvas.output_win.h = disp_height;

			// raixs.lim (2017/08/25)
			// support user defined output win for debug. invalid config might make OSD corruption
			if (canvas.test_output_win.w && canvas.test_output_win.h)
			{

				FBDEV_O18_HDR_DEBUG("++ test output window (%d,%d,%d,%d)\n",
							canvas.test_output_win.x, canvas.test_output_win.y, canvas.test_output_win.w, canvas.test_output_win.h);
				memcpy(&canvas.output_win, &canvas.test_output_win, sizeof(LX_RECT_T));
			}

			// raxis.lim (2015/01/12) -- handle odd width
			// OSD doesn't support odd number as output width. so let's make it to even number
			if ( canvas.output_win.w & 0x1 )
			{
				FBDEV_O18_HDR_DEBUG("fb(%d) convert odd out_w %d to %d\n", fb_dev_id, canvas.output_win.w, canvas.output_win.w&0xfffffffe);
				canvas.output_win.w &= 0xfffffffe;
			}

			// NOTE - CLUT processing is not processed anymore inside kdriver
			osd_hdr.osd_hdr_color_key_en= canvas.color_key_en;

			osd_hdr.osd_hdr_w_out		= canvas.output_win.w;	/* output w */
			osd_hdr.osd_hdr_h_out		= canvas.output_win.h;	/* output h */
			osd_hdr.osd_hdr_xpos	 	= canvas.output_win.x;	/* output x */
			osd_hdr.osd_hdr_ypos 		= canvas.output_win.y;	/* output y */
			osd_hdr.osd_hdr_w_mem 		= canvas.input_win.w;	/* input w  */
			osd_hdr.osd_hdr_h_mem 		= canvas.input_win.h;	/* input h  */
			bitmap_ptr					= canvas.osd_bm_paddr;

			// modify bitmap ptr for input position is provided
			if (canvas.input_win.x > 0 || canvas.input_win.y > 0)
			{
				FBDEV_O18_HDR_DEBUG("fb(%d) bitmap based moved ! by %d,%d\n", fb_dev_id, canvas.input_win.x, canvas.input_win.y );

				/* gMAU requests 16byte aligned address */
				bitmap_ptr += canvas.input_win.y * canvas.stride;
				bitmap_ptr += FBDEV_O18_GMAU_ALIGNED_BYTES(FBDEV_O18_BITS_2_BYTES(canvas.input_win.x*canvas.bits_per_pixel));
			}
			FBDEV_O18_HDR_DEBUG("fb(%d) bitmap param (%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x\n", fb_dev_id,
					canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
					canvas.stride, bitmap_ptr, canvas.fbc_fmt );

			osd_hdr.osd_hdr_pixel_order	= canvas.pixel_order_en;
			osd_hdr.osd_hdr_wpl 		= FBDEV_O18_BYTES_2_OSD_WORDS(canvas.stride);
		}
		break;
	}

	/* copy common attribute */
    osd_hdr.osd_hdr_format          = FBDEV_GetOSDPxlFmt( canvas.bits_per_pixel );
    osd_hdr.osd_hdr_depth           = FBDEV_GetOSDPxlDepth( canvas.bits_per_pixel );

	osd_hdr.osd_hdr_global_alpha_en	= canvas.global_alpha_en;
	osd_hdr.osd_hdr_global_alpha	= (canvas.global_alpha_en)? canvas.global_alpha : 0xff;
	osd_hdr.osd_hdr_color_key		= canvas.color_key;

	osd_hdr.osd_hdr_ptr_bmp			= bitmap_ptr;
	osd_hdr.osd_hdr_ptr_plte		= wctx->osd_plte_base_phys;

	// NOTE - virtual OSD is not processed anymore inside kdriver */

	/* handle S3D if requested */
	FBDEV_O18_CMN_Handle3DOSD(fb_dev_id, &canvas, &osd_hdr);

	/* handle reverse OSD if requested */
	FBDEV_O18_CMN_HandleReverseOSD(fb_dev_id, &canvas, &osd_hdr);

	FBDEV_O18_HDR_DEBUG("fb(%d) bitmap param (%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x (final)\n", fb_dev_id,
			canvas.input_win.x, canvas.input_win.y,
			canvas.input_win.w, canvas.input_win.h,
			canvas.stride, bitmap_ptr, canvas.fbc_fmt );

	/* save osd header */
	memcpy( &hw_ctx->osd_hdr_sav[fb_dev_id], &osd_hdr, sizeof(FBDEV_O18_OSD_HDR_T));

	osd_exhdr.bits_per_pixel= canvas.bits_per_pixel;
	osd_exhdr.img_stride 	= canvas.stride;
	FBDEV_O18_CMN_WriteHdrRegs(fb_dev_id, &osd_hdr, &osd_exhdr);

	#if 0
	FBDEV_O18_CMN_WriteFRCHeader( ); /* update FRC header if externel FRC chip requires */
	#endif

	return RET_OK;
}

/*========================================================================================
	Implementation Group
========================================================================================*/

/** OSD HW Layer enable/disable
 *
 * @param	fb_dev_id [IN] fbdev ID
 *
 *			enable : 0 : display off , 1 : display on
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_O18_CMN_SetOSDEnable(int fb_dev_id, int enable)
{
	int		xidx;
	int		xnum, xlst[2];
	UINT32	val = 0x0;

	//FBDEV_O18_HW_CTX_T*	hw_ctx = FBDEV_O18_GET_HW_CTX();

	xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
	/* ignore noisy warning msg becase some OSD layer is not supported by HW */
	FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

	val = (enable)? 0x1: 0x0;
	FBDEV_HW_DEBUG("fb(%d) xlst[0] = %d, xlist[1] = %d, view = <%s>\n", fb_dev_id, xlst[0], xlst[1], (enable)? "on":"off");

	xidx = xlst[0];
	FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_main,  osd_en, 		 val);
	OSDX_O18_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_enable, val);

	//FBDEV_WARN("osd_ctrl_main  = 0x%08x\n", (UINT32)OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_main ));
	//FBDEV_WARN("osd_ctrl_sync0 = 0x%08x\n", (UINT32)OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_sync0));

	OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
	OSDX_O18_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);

	return RET_OK;
}

/** OSD HW Layer status
 *
 * @param	void
 * @return	int 1 : ON , 0 : OFF
 *
 */
int FBDEV_O18_CMN_GetOSDEnable(int fb_dev_id)
{
	UINT32 val;
	int	xidx;
	int	xnum, xlst[2];

	xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
	/* ignore noisy warning msg becase some OSD layer is not supported by HW */
	if(INVALID_XNUM(xnum)) return FALSE;

	xidx = xlst[0];
	FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

	OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
	OSDX_O18_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, val );

	return val;
}

int		FBDEV_O18_CMN_SetViewCtrl ( LX_FBDEV_VIEW_CTRL_T* ctrl )
{
	int i;
	ULONG flags;

	/* we can't do spinlock when pivot mode is enabled because sleep ocurrs during GFX merge */
	spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
		if ( ctrl->view_status[i] == 0x0 || ctrl->view_status[i] == 0x1 )
			FBDEV_O18_CMN_SetOSDEnable(i, ctrl->view_status[i]);
	}

	spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);

    return RET_OK;
}

/** set OSD out connection ctrl
 *
 *	@param pConnCtrl [IN] connection control data
 *	@return RET_OK if success, RET_ERROR otherwise
 *
 */
int     FBDEV_O18_CMN_SetConnCtrl           (LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
	int     i;
	BOOLEAN osd_view_status[LX_FBDEV_ID_MAX];

	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	FBDEV_WARN("OSD conn change. conn_type 0x%x (%s disp)\n", pConnCtrl->conn_type, (g_fbdev_cfg->uhd_disp_mode)? "UHD":"FHD" );

	FBDEV_CHECK_DEBUG( hw_ctx->hw_conn_type == pConnCtrl->conn_type, return RET_OK, "ignore the dup calls (0x%x)\n", pConnCtrl->conn_type );

	/* save current config. diable OSD before changing OSD config */
	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
		osd_view_status[i] = FBDEV_O18_GetOSDEnable(i);
		FBDEV_O18_SetOSDEnable(i, FALSE );

	}

	/* TODO: add some delay if you need to tune timing */


	/* disable ISR to change ISR source */
	FBDEV_O18_SetInterruptEnable(MIXER_INTR, FALSE);

	/* sleep until OSD stablized. not necessary to sleep in O18 */

	if (pConnCtrl->conn_type & LX_FBDEV_CONN_OSD_VIDEO_SEPARATE)
	{
		FBDEV_HW_DEBUG("O18::S.OSD\n");

		hw_ctx->hw_disp_width	= hw_ctx->sosd_disp.out_width;
		hw_ctx->hw_disp_height	= hw_ctx->sosd_disp.out_height;
	}
	else if(pConnCtrl->conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		FBDEV_HW_DEBUG("O18::B.OSD\n");

		hw_ctx->hw_disp_width	= hw_ctx->bosd_disp.out_width;
		hw_ctx->hw_disp_height	= hw_ctx->bosd_disp.out_height;
	}
	else
	{
		FBDEV_WARN("invalid connection 0x%x\n", pConnCtrl->conn_type );
		goto func_exit;
	}

	/* save the current connection */
	hw_ctx->hw_conn_type = pConnCtrl->conn_type;

	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
		hw_ctx->conn_ctrl[i].conn_type = hw_ctx->hw_conn_type;
	}

	/* reinit HW. OSD might be off during re-initialization */
	FBDEV_O18_CMN_ReInitHW();

	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
	    FBDEV_WriteOSDHeader(&g_dm_ctx->wctx[i]->pixel);
	}

	/* TODO: add some delay if you need to tune timing */

func_exit:
	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
		FBDEV_O18_SetOSDEnable(i, osd_view_status[i]);
	}

	return RET_OK;
}

/** control OSD SR (Picture Enhancement)
 *  - on/off
 *  - filter update
 *	- etc
 *
 */
int		FBDEV_O18_CMN_SRCtrl			(BOOLEAN onoff)
{
	FBDEV_O18_CMN_SetupSRScaler(onoff, TRUE);
	return RET_OK;
}

/*========================================================================================
    Implementation Group (VOSD emulation)
========================================================================================*/
/** handle 3D feature workaround
 *
 */
void	FBDEV_O18_CMN_Handle3DOSD ( int fb_dev_id, struct scanvas* hCanvas, FBDEV_O18_OSD_HDR_T* osd_hdr )
{
#ifdef FBDEV_O18_USE_3DOSD_HW_CTRL
	FBDEV_HW_CTX_T* 	hw_core_ctx = FBDEV_GET_HW_CTX();
	FBDEV_O18_HW_CTX_T*	hw_ctx = FBDEV_O18_GET_HW_CTX();

	UINT32	disp_width = hw_ctx->hw_gfx_width;
	UINT32	disp_height= hw_ctx->hw_gfx_height;

	LX_FBDEV_TRID_CTRL_T* trid_ctrl = &(hw_core_ctx->fb[fb_dev_id].trid_ctrl);

	if (hw_ctx->b_support_3dosd && (trid_ctrl->mode & LX_FBDEV_TRID_MODE_SS) )
	{
        /* raxis.lim (2015/04/30)
         * HW requires osd input/height should be less than half of output(display) height.
		 * Display height means that maximum region which OSD can read
		 * for example, O18 can read only FHD region as maximum input, but can display up to UHD size with scale up
		 * in above case, display size should be set as FHD not UHD.
		 * This rule might be somewhat embarassed because older HW has the same input & output size.
		 *
		 * OSD header should be modified when S/S S3D is requested
		 * HW makes FPR S3D screen using two half-heighted left & right screen.
         * So Application should knows this H/W restrtion.
		 *
		 * osd_hdr_h_mem = a half of osd_hdr_h_mem
		 * osd_hdr_w_mem = a double of (maximum a half of disp height)
		 *
		 * for example,
		 * 1) App draws S3D image to 1920x540 region if OSD HW max input region is 1920x1080.
		 * 2) OSD HW read 960x540 (Left) and 960x540 (Right) and produces 1920x1080 FPR screen
		 *
         */
		if (osd_hdr->osd_hdr_h_mem > (disp_height>>1) )
		{
			osd_hdr->osd_hdr_h_mem = (disp_height>>1);
		}

		osd_hdr->osd_hdr_w_mem >>= 1;   /* h/2 */
		osd_hdr->osd_hdr_h_mem <<= 1;   /* V*2 */

		FBDEV_HW_DEBUG("fb(%d) S3D(S/S) osd_hdr %d,%d gfx_rgn %d,%d\n", fb_dev_id,
			osd_hdr->osd_hdr_w_mem, osd_hdr->osd_hdr_h_mem, disp_width, disp_height );
	}
#endif /* FBDEV_O18_USE_3DOSD_HW_CTRL */
}

/** handle osd scaler workaround during reverse screen
 *
 *	this workaround makes OSD scaler output to be similar to GFX.
 *	so this workaround code should run only when framebuffer is scaled up !!
 *
 */
void	FBDEV_O18_CMN_HandleReverseOSD ( int fb_dev_id, struct scanvas* hCanvas, FBDEV_O18_OSD_HDR_T* osd_hdr )
{
#ifdef FBDEV_O18_USE_REV_HW_CTRL
	// TODO: if reverse screen handler if needed
#endif
}

/** VOSD ISR handler
 *
 *
 */
void     FBDEV_O18_CMN_ISRHook ( void )
{
#ifdef FBDEV_O18_USE_AFBC_DATA_PATH_CHANGE_ISR_HANDLER
	ULONG flags;
	FBDEV_O18_HW_CTX_T*   hw_ctx = FBDEV_O18_GET_HW_CTX();

	spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

	if (hw_ctx)
	{
		FBDEV_O18_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[LX_FBDEV_ID_OSD0];

		if (fbc_ctrl->status & FBDEV_O18_FBC_STATUS_PATH_CHANGE)
		{
			//FBDEV_O18_FBC_DEBUG("sync cco_ctrl.ctrl_dpath fbc_fmt = %d\n", fbc_ctrl->fbc_fmt);
			FBDEV_WARN("<!> sync cco_ctrl.ctrl_dpath fbc_fmt = %d\n", fbc_ctrl->fbc_fmt);
			OSD_TOP_O18_RdFL(ctrl_dpath);

			if (fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
			{
				OSD_TOP_O18_Wr01(ctrl_dpath, osd0_afbc_en, 0x1 );
			}
			else
			{
				OSD_TOP_O18_Wr01(ctrl_dpath, osd0_afbc_en, 0x0 );
			}

			OSD_TOP_O18_WrFL(ctrl_dpath);
			fbc_ctrl->status &= ~FBDEV_O18_FBC_STATUS_PATH_CHANGE;
		}
	}
	spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);
#endif
}

/*========================================================================================
    Implementation Group (DIAG/PROC)
========================================================================================*/

/** HW status
 *
 *  read register(s) to get some HW status
 *	return value seems to be boolean value but there might be exceptions
 *	read comments before using the functioin
 *
 */
int      FBDEV_O18_CMN_GetHWStatus       (FBDEV_O18_HW_STATUS_T status, UINT32 opt[3])
{
	int	val = 0;

	switch(status)
	{
		/* return 1 if HW is set to AFBC configuration. otherwise return 0 */
		case FBDEV_O18_HW_STATUS_AFBC:
		{
			OSD_TOP_O18_RdFL(ctrl_dpath);
			OSD_TOP_O18_Rd01(ctrl_dpath, osd0_afbc_en, val);
		}
		break;

		default:
		{
			val = 0;
		}
		break;
	}

	return val;
}

/** HW diagnostics
 *
 *  dump important paramters and valiate settings
 *	this function will help to view HW status
 *
 */
void FBDEV_O18_CMN_DiagHW(struct seq_file* m)
{
#ifdef FBDEV_O18_USE_SR_CTRL
	FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

	/* diag OSD_SR HW status */
	{
		int	xidx;
		int xnum, xlst[2];
		int	fb_dev_id = LX_FBDEV_ID_OSD0;

		UINT32 bypass_en, detour_en, rgb2yc_csc_en, yc2rgb_bosd_csc_en, yc2rgb_sosd_csc_en;

		FBDEV_O18_SR_CTRL_T* sr_ctrl = &hw_ctx->sr_ctrl[fb_dev_id];

		xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);
		FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

		xidx = xlst[0];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

		OSDX_O18_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
		OSD_SHP_RdFL(shp_core_ctrl_00);

		OSD_SHP_Rd01(shp_core_ctrl_00, reg_top_bypass, bypass_en);

		OSDX_O18_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en,		detour_en);;
		OSDX_O18_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en, 		rgb2yc_csc_en);
		OSDX_O18_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, 	yc2rgb_bosd_csc_en);
		OSDX_O18_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_sosd_csc_en, 	yc2rgb_sosd_csc_en);
		seq_printf(m, "osd_sr.sw_status: 0x%x\n", sr_ctrl->status);
		seq_printf(m, "osd_sr.hw_status: 0x%x\n", (!bypass_en && !detour_en));
		seq_printf(m, "osd_sr.shp_ctrl0.bypass_en: 0x%x\n", bypass_en);
		seq_printf(m, "osd_sr.bmp_ctrl0.detour_en: 0x%x\n", detour_en);
		seq_printf(m, "osd_sr.bmp_ctrl0.rgb2yc_csc_en: 0x%x\n", yc2rgb_bosd_csc_en);
		seq_printf(m, "osd_sr.bmp_ctrl0.yc2rgb_bosd_csc_en: 0x%x\n", yc2rgb_bosd_csc_en);
		seq_printf(m, "osd_sr.bmp_ctrl0.yc2rgb_sosd_csc_en: 0x%x\n", yc2rgb_sosd_csc_en);
		seq_printf(m, "\n");

		seq_printf(m, "hw_wa.1x_csr_disp_on_blend_path: 0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_1X_CSR_DISP_ON_BLEND_PATH)? 1:0);
		seq_printf(m, "hw_wa.osd0_async_wr_error: 0x%x\n",		(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)? 1:0);
		seq_printf(m, "hw_wa.pqwfw_osd0_out_ctrl: 0x%x\n",		(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PQEFW_OSD0_OUT_CTRL)? 1:0);
		seq_printf(m, "hw_wa.pause_pqwfw_osd0_out_ctrl: 0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_O18_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)? 1:0);
	}

	/* TODO: add something */
#endif
}

/** chip specific proc handler
 *
 */
void FBDEV_O18_CMN_ProcHandler(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case FBDEV_HW_PROC_ID_DETAIL_INFO:
		{
			FBDEV_O18_HW_CTX_T* hw_ctx = FBDEV_O18_GET_HW_CTX();

			seq_printf(m, "<HW INFO>\n");
			seq_printf(m, "path: %s\n", 			(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? "bosd":"sosd");
			seq_printf(m, "hw_disp_width: %d\n", 	hw_ctx->hw_disp_width );
			seq_printf(m, "hw_disp_height: %d\n", 	hw_ctx->hw_disp_height);
			seq_printf(m, "hw_gfx_width: %d\n", 	hw_ctx->hw_gfx_width);
			seq_printf(m, "hw_gfx_height: %d\n", 	hw_ctx->hw_gfx_height);
			seq_printf(m, "support_3dosd: %s\n",	(hw_ctx->b_support_3dosd)? "on":"off");
			seq_printf(m, "vsync_clk: %dHz\n",		(FBDEV_O18_CMN_DetectVSyncClk()==FBDEV_VSYNC_CLK_60HZ)? 60: 120);
		}
		break;

		case FBDEV_HW_PROC_ID_OSD_HDR:
		{
			int xidx;
			int xnum, xlst[2];

			UINT32 	osd_en, sync_en;
			UINT32	hdr_lst[7];
			FBDEV_O18_OSD_HDR_T* osd_hdr = (FBDEV_O18_OSD_HDR_T*)hdr_lst;
			LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

			xnum = FBDEV_O18_CMN_GetHWXList(fb_dev_id, xlst);

			xidx = xlst[0];
			if(INVALID_XIDX(xlst[0])) break;

			seq_printf(m, "posd_num: %d\n",		xnum);

			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

			OSDX_O18_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, osd_en);
			OSDX_O18_Rd01(osdx_ctrl[xidx], osd_ctrl_sync0,osd_sync_enable, sync_en);

			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
			OSDX_O18_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);

			hdr_lst[0] = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr0);
			hdr_lst[1] = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr1);
			hdr_lst[2] = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr2);
			hdr_lst[3] = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr3);
			hdr_lst[4] = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr4);
			hdr_lst[5] = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr5);
			hdr_lst[6] = OSDX_O18_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);

			seq_printf(m, "posd_idx: %d\n",				xidx);
			seq_printf(m, "visible: %s (osd:%d, sync:%d)\n", (osd_en && sync_en)? "on":"off", osd_en, sync_en);
			seq_printf(m, "\n");
			seq_printf(m, "hdr.xpos: %d\n", 			osd_hdr->osd_hdr_xpos);
			seq_printf(m, "hdr.ypos: %d\n", 			osd_hdr->osd_hdr_ypos);
			seq_printf(m, "hdr.w_mem: %d\n", 			osd_hdr->osd_hdr_w_mem);
			seq_printf(m, "hdr.h_mem: %d\n", 			osd_hdr->osd_hdr_h_mem);
			seq_printf(m, "hdr.w_out: %d\n", 			osd_hdr->osd_hdr_w_out);
			seq_printf(m, "hdr.h_out: %d\n", 			osd_hdr->osd_hdr_h_out);
			seq_printf(m, "hdr.pixel_order: 0x%x\n", 	osd_hdr->osd_hdr_pixel_order);
			seq_printf(m, "hdr.wpl: %d\n",		 		osd_hdr->osd_hdr_wpl);
			seq_printf(m, "hdr.global_alpha_en: %d\n", 	osd_hdr->osd_hdr_global_alpha_en);
			seq_printf(m, "hdr.global_alpha: 0x%x\n", 	osd_hdr->osd_hdr_global_alpha);
			seq_printf(m, "hdr.color_key_en: %d\n", 	osd_hdr->osd_hdr_color_key_en);
			seq_printf(m, "hdr.color_key: 0x%x\n", 		osd_hdr->osd_hdr_color_key);
			seq_printf(m, "hdr.ptr_plte: 0x%x\n", 		osd_hdr->osd_hdr_ptr_plte);
			seq_printf(m, "hdr.ptr_bmp: 0x%x\n", 		osd_hdr->osd_hdr_ptr_bmp);

			/* TODO: add something */
		}
		break;

        case FBDEV_HW_PROC_ID_REG_DUMP:
        {
            int     i;
            UINT32  off;
            UINT32  val;

            struct
            {
                char*  desc;
                UINT32 reg_base;
                UINT32 reg_size;
            } reg_list[] = {
                { .desc = "OSD",  .reg_base = CCO_OSD_BASE,					.reg_size = sizeof(OSD_O18_REG_T) },
                { .desc = "TOP",  .reg_base = CCO_CTRL_BASE,				.reg_size = sizeof(OSD_TOP_O18_REG_T) },
                { .desc = "AFBC", .reg_base = CCO_OSD_AFBC_BASE,			.reg_size = sizeof(OSD_AFBC_O18_REG_T) },
                { .desc = "SHP",  .reg_base = CCO_OSD_SHP_BASE,				.reg_size = sizeof(OSD_SHP_O18_REG_T) },
                { .desc = "SCAN", .reg_base = CCO_OSD_SCAN_BASE,			.reg_size = sizeof(OSD_SCAN_O18_REG_T) },
                { .desc = "MIF",  .reg_base = CCO_MIF_BASE,					.reg_size = 0xA8 } };

            for (i=0; i<NELEMENTS(reg_list); i++)
            {
                seq_printf(m, "\n\n");
                seq_printf(m, "FBDEV (%s) : 0x%08x\n", reg_list[i].desc, reg_list[i].reg_base );

                for (off=0; off<reg_list[i].reg_size; off+=4 )
                {
                    UINT32 reg_addr = reg_list[i].reg_base + off;

                    OS_RdReg(reg_addr, &val);
                    seq_printf( m, " 0x%08x (+0x%04x) = %08x\n", reg_addr, off, val);
                }
            }
        }
        break;

		default:
		{
			/* do nothing */
		}
		break;
	}
}

/*========================================================================================
    Implementation Group (Suspend/Resume)
========================================================================================*/
/** common resume/suspend handler
 *
 */
int	FBDEV_O18_CMN_RunResume	( void )
{
	FBDEV_O18_CMN_ReInitHW( );

	/* OSD freeze will be stopped after 500 ms */
	FBDEV_O18_CMN_RunBootLogoTimer(fbdev_resume_freeze_timeout, TRUE);
	return RET_OK;
}

int	FBDEV_O18_CMN_RunSuspend	( void )
{
	/* do nothing */
	return RET_OK;
}

/*========================================================================================
	common OSD HW handler
========================================================================================*/
FBDEV_O18_HW_FUNC_T  g_fbdev_o18_cmn_hw_func =
{
	/* variable is initialize at fbdev_drv_O18.c */

    .O18_InitHW			 = FBDEV_O18_CMN_InitHW,

	.O18_SetViewCtrl	 = FBDEV_O18_CMN_SetViewCtrl,
    .O18_SetConnCtrl     = FBDEV_O18_CMN_SetConnCtrl,

    .O18_WriteOSDHeader  = FBDEV_O18_CMN_WriteOSDHeader,
    .O18_SetOSDEnable    = FBDEV_O18_CMN_SetOSDEnable,
    .O18_GetOSDEnable    = FBDEV_O18_CMN_GetOSDEnable,
    .O18_ISRTickHandler  = FBDEV_O18_CMN_ISRHook,
};

