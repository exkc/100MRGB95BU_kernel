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
#include "fbdev_hw_e60.h"
#include "osd_reg_e60.h"
#include "osd_shp_reg_e60.h"
#include "osd_merg_reg_e60.h"
#include "osd_afbc_reg_e60.h"
#include "osd_cco_top_reg_e60.h"
#include "osd_cco_top1_reg_e60.h"
#include "osd_merg_reg_e60.h"
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/seq_file.h>
#include <linux/fb.h>

#include "hma_alloc.h"

#ifdef FBDEV_E60_USE_CTOP_REGS
#include "../sys/sys_regs.h"
#endif

#ifdef INCLUDE_KDRV_OVI
#include "be_kapi.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	CHECK_AFBC_FBDEV(id)		((id)==LX_FBDEV_ID_OSD0 || (id)==LX_FBDEV_ID_OSD1)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern int g_fbdev_use_isr_mon;

static int fbdev_chip_vsync_cnt = 0;
static DECLARE_WAIT_QUEUE_HEAD(fbdev_chip_vsync_wq);
static DEFINE_SPINLOCK(fbev_chip_vsync_spinlock);       // spinlock for check vsync state

static void	FBDEV_E60_CMN_WaitForVsync(int wait_cnt);

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_E60_CMN_InitFBCEnv	(void);
#ifdef FBDEV_E60_USE_FBC_CTRL
static void FBDEV_E60_CMN_SetupFBC		(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt);
#endif
static void FBDEV_E60_CMN_SetupSRScaler	(BOOLEAN onoff, BOOLEAN bForce);

static void FBDEV_E60_CMN_OpenExternalRenderer(int fb_dev_id, struct fb_info* fbinfo);

static void	FBDEV_E60_CMN_ReInitHW		(void);
static void FBDEV_E60_CMN_InitMirrorEnv	(void);
static int 	FBDEV_E60_CMN_WriteOSDHeader(struct scanvas *pCanvas);
static FBDEV_VSYNC_CLK_T FBDEV_E60_CMN_DetectVSyncClk(void);

static void FBDEV_E60_CMN_NotifyToPQEDriver(void);
static int	FBDEV_E60_CMN_WaitForPQEDriverInitialization(void);

static void FBDEV_E60_CMN_BootLogoClearScheduler(struct work_struct *work);

static void FBDEV_E60_CMN_ShutdownOSDPath (void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_osd_hdr_spinlock);

static struct workqueue_struct *fbdev_e60_wq;
static DECLARE_DELAYED_WORK (boot_logo_clear_work, FBDEV_E60_CMN_BootLogoClearScheduler);

static int	fbdev_boot_freeze_timeout	= 0;	/* see SICDTV-8491. set 0 by default */
static int	fbdev_resume_freeze_timeout = 0;	/* see SICDTV-8491. set 0 by default */
static int	fbdev_pqefw_osd0_out_ctrl 	= 1;	/* SICDTV-4359 */
static int	fbdev_osd0_user_out_win 	= 0;	/* SICDTV-4359 */

static int	fbdev_enable_logo_clear			= 0;	/* see SICDTV-8556 */
static int	fbdev_boot_logo_clear_timeout	= 3000;	/* see SICDTV-8556 */
static int	fbdev_resume_logo_clear_timeout	= 2000;	/* see SICDTV-8556 */

static BOOLEAN fbdev_logo_migration_required = TRUE;

module_param_named( fbdev_e60_boot_freeze_timeout,	fbdev_boot_freeze_timeout, 	int, 0644 );
module_param_named( fbdev_e60_resume_freeze_timeout,fbdev_resume_freeze_timeout,int, 0644 );

module_param_named( fbdev_e60_pqefw_osd0_out_ctrl, 	fbdev_pqefw_osd0_out_ctrl, 	int, 0644 );
module_param_named( fbdev_e60_osd0_user_out_win, 	fbdev_osd0_user_out_win, 	int, 0644 );

module_param_named( fbdev_e60_enable_logo_clear, 		fbdev_enable_logo_clear, 		int, 0644 );
module_param_named( fbdev_e60_boot_logo_clear_timeout, 	fbdev_boot_logo_clear_timeout, 	int, 0644 );
module_param_named( fbdev_e60_resume_logo_clear_timeout,fbdev_resume_logo_clear_timeout,int, 0644 );

static int fbdev_hw_pm_suspend_stage = 0;
static int fbdev_hw_pm_restore_stage = 0;

static int fbdev_use_shutdown_path_on_suspend = 1;	/* see SICDTV-9009 */
module_param_named( fbdev_e60_use_shutdown_path_on_suspend, fbdev_use_shutdown_path_on_suspend ,int, 0644 );

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
int	FBDEV_E60_CMN_GetHWXList(int fb_dev_id, int xlst[2])
{
	int	afbc_xlst[2];

	return FBDEV_E60_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
}

/** return the current mapped physical OSD block id
 *
 *	blk0 = IMG0 (osdx_prep_img0, 2K or 4K left)
 *	blk1 = IMG1 (osdx_prep_img1, 4K right)
 *	blk2 = EST (osdx_prep_est, 2K Estreamer not used)
 *	blk3 = CSR (osdx_prep_csr, cursor)
 *
 */
int	FBDEV_E60_CMN_GetHWXListEx(int fb_dev_id, int xlst[2], int afbc_xlst[2])
{
	int	num_xlst = 0;
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	switch( fb_dev_id )
	{
		case LX_FBDEV_ID_OSD0:
		{
			if (hw_ctx->b_support_4kosd)	{num_xlst=2; xlst[0] = 0; xlst[1] = 1; afbc_xlst[0] = 0; afbc_xlst[1] = 1;}
			else 							{num_xlst=1; xlst[0] = 0; xlst[1] =-1; afbc_xlst[0] = 0; afbc_xlst[1] =-1;}
		}
		break;

		case LX_FBDEV_ID_OSD1:
		{
            if (hw_ctx->b_support_4kosd){num_xlst=1; xlst[0] = 2; xlst[1] =-1; afbc_xlst[0] =-1; afbc_xlst[1] =-1;}
            else                        {num_xlst=1; xlst[0] = 2; xlst[1] =-1; afbc_xlst[0] =-1; afbc_xlst[1] =-1;}
		}
		break;

		case LX_FBDEV_ID_CSR0:
		{
			num_xlst=1; xlst[0] = 3; xlst[1] =-1; afbc_xlst[0] =-1; afbc_xlst[1] =-1;
		} break;

		default:
		{
			num_xlst=0; xlst[0] =-1; xlst[1] =-1; afbc_xlst[0] =-1; afbc_xlst[1] =-1;
		} break;
	}

	return num_xlst;
}

BOOLEAN  FBDEV_E60_CMN_IsUHDDispMode  (void)
{
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	return (hw_ctx->hw_disp_width > 2048)? TRUE:FALSE;
}

#ifdef FBDEV_E60_USE_REVERSE_HW_CTRL
/** check if current OSD HW is set as the reverse mode
 *
 */
static BOOLEAN	FBDEV_E60_CMN_IsReverseMode	( int fb_dev_id )
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
static void FBDEV_E60_CMN_EnableOSDHdrFlush( ULONG data )
{
    int i;

 	FBDEV_NOTI("<!> enable osd_hdr_flush & exit OSD freeze stage. afbc=%d\n",
			 FBDEV_E60_CMN_GetHWStatus(FBDEV_E60_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0));

	/* enable osd_hdr_flush to unfreeze OSD */
    for (i=0; i<LX_FBDEV_ID_MAX; i++)
    {
        FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(i);
		struct scanvas*  canvas = FBDEV_GetWinCanvas(i);

		FBDEV_BOOT_DEBUG("++ fb(%d)\n", i);

		FBDEV_CHECK_CODE(NULL==wctx, continue, "invalid fb(%d) ctx\n", i );
		FBDEV_CHECK_CODE(NULL==canvas, continue, "invalid fb(%d) canvas\n", i );

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

		/* raxis.lim (2020/06/11)
		 * 수정된 OSD 초기화 정책에 의하여 이 함수는 단순히 b_osd_hdr_flush 를 활성화 하는 역할로
		 * 축소한다. 향후 함수 목적을 수정하거나, 완전히 삭제할 수도 있음
		 */
		/* do nothing */
	}
}

/** clear current logo screen after a few seconds after OSD initialization
 *
 */
static void FBDEV_E60_CMN_BootLogoClearScheduler(struct work_struct *work)
{
	FBDEV_NOTI("logo clear work started\n");
	fbdev_logo_migration_required = TRUE;
	FBDEV_E60_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_CLEAR);
}

/** move boot logo framebuffer to safe region (prototype implementation)
 *
 */
void FBDEV_E60_CMN_MigrateBootLogo(FBDEV_E60_BOOT_LOGO_MODE_T mode)
{
#if (CONFIG_LX_BOOT_LOGO==1)

	int	rc;
	int xidx;
	UINT32	fbmem_addr_src, fbmem_addr_dst, fbmem_addr_clr;
	OS_CACHE_MAP_T cmap_src, cmap_dst;

	UINT32		image_size;
	phys_addr_t dst_rgn_base = 0;
	int			dst_rgn_size = 0;
	int			afbc_mode 	= 0;

	/* allow this function to run once at cold boot regardless of result */
	if (fbdev_logo_migration_required==FALSE)
	{
		FBDEV_WARN("ignore request\n");
		return;
	}

	fbdev_logo_migration_required = FALSE;

	memset(&cmap_src, 0x0, sizeof(OS_CACHE_MAP_T));
	memset(&cmap_dst, 0x0, sizeof(OS_CACHE_MAP_T));

	image_size = afbc_sw_get_image_size(NULL, 1920, 1080); /* fixed size */
	image_size = ALIGN(image_size, (1<<20));

	FBDEV_CHECK_CODE(0!=hma_pool_info("surface", &dst_rgn_base, &dst_rgn_size),
						return, "dst buffer not found");

	/* read OSD0 framebuffer */
	OSDX_CTRL_E60_RdFL(0, osd_ctrl_hdr6);
	OSDX_CTRL_E60_Rd01(0, osd_ctrl_hdr6, osd_hdr_ptr_bmp, fbmem_addr_src);
	FBDEV_HW_NOTI("logo fbmem (old) = 0x%08x\n", fbmem_addr_src);

	/* move to last part of new region becuase this region isnot used at boot time */
	fbmem_addr_dst = (UINT32)(dst_rgn_base + dst_rgn_size - image_size);
	fbmem_addr_clr = (UINT32)(dst_rgn_base + dst_rgn_size - image_size*2);

	afbc_mode = (FBDEV_E60_CMN_GetHWStatus(FBDEV_E60_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0))? 1:0;

	if (mode == BOOT_LOGO_MODE_IMAGE_KEEP)
	{
		rc = OS_OpenCacheMap(&cmap_src, (ULONG)fbmem_addr_src, image_size);
		FBDEV_CHECK_CODE(rc!=RET_OK, goto func_exit, "cache op fail\n");
		rc = OS_OpenCacheMap(&cmap_dst, (ULONG)fbmem_addr_dst, image_size);
		FBDEV_CHECK_CODE(rc!=RET_OK, goto func_exit, "cache op fail\n");

		rc = OS_InvalCacheMap(&cmap_src, 0, image_size);
		FBDEV_CHECK_CODE(rc!=RET_OK, goto func_exit, "cache op fail\n");

		memcpy(cmap_dst.virt_addr, cmap_src.virt_addr, image_size);

		rc = OS_CleanCacheMap(&cmap_dst, 0, image_size);
		FBDEV_CHECK_CODE(rc!=RET_OK, goto func_exit, "cache op fail\n");
	}
	else /* see SICDTV-8556 */
	{
		if (afbc_mode)
		{
			struct afbc_framebuffer* afbc_fb = afbc_sw_alloc_framebuffer(NULL,
													fbmem_addr_clr, 1920, 1080, 0, 0, 0);
			if (afbc_fb)
			{
				afbc_sw_fill(NULL, afbc_fb, 0x00000000);
				afbc_sw_free_framebuffer(NULL, afbc_fb);
			}
		}
		// ARGB raw 기반의 Logo 는 더이상 없으므로 대응하지 않겠음.
		else
		{
			FBDEV_WARN("ARGB mode - do nothing\n");
		}

		fbmem_addr_dst = fbmem_addr_clr;
	}

	/* update AFBC0 framebuffer */
	if(afbc_mode)
	{
		rc = OS_WrReg(E60_CCO_AFBC0_BASE+0x004, fbmem_addr_dst);
		FBDEV_CHECK_CODE(rc!=RET_OK, goto func_exit, "reg op fail\n");

		AFBC_CTRL_Wr01(0, ctrl_afbc_1, hd_base, 	 fbmem_addr_dst);
		AFBC_CTRL_Wr01(0, ctrl_afbc_8, pl_data_base, fbmem_addr_dst);
		AFBC_CTRL_WrFL(0, ctrl_afbc_1);
		AFBC_CTRL_WrFL(0, ctrl_afbc_8);

		/* raxis.lim (2019/10/23)
		 * becuase hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
		 * we should set hdr_ready_flag=1 here to update real framebuffer address
		 */
		AFBC_CTRL_RdFL(0, ctrl_afbc_0);
		AFBC_CTRL_Wr01(0, ctrl_afbc_0, update_ready_flag, 0x1);
		AFBC_CTRL_WrFL(0, ctrl_afbc_0);
	}

	/* update OSD framebuffer */
	for (xidx=0; xidx<4; xidx++)
	{
		OSDX_CTRL_E60_Wr01(xidx, osd_ctrl_hdr6, osd_hdr_ptr_bmp,	fbmem_addr_dst);
		OSDX_CTRL_E60_Wr01(xidx, osd_ctrl_hdr5, osd_hdr_ptr_plte,	fbmem_addr_dst);
		OSDX_CTRL_E60_Wr01(xidx, osd_base_addr, osd_base_addr,		fbmem_addr_dst);

		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr6);
		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr5);
		OSDX_CTRL_E60_WrFL(xidx, osd_base_addr);
	}

	/* raxis.lim (2019/10/23)
	 * becuase osd_hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
	 * we should set osd_hdr_ready_flagn=1 here to update real framebuffer address
	 */
	OSDX_CTRL_E60_RdFL(0, osd_ctrl_main);
	OSDX_CTRL_E60_Wr01(0, osd_ctrl_main, osd_hdr_ready_flag_en, 0x1);
	OSDX_CTRL_E60_Wr01(0, osd_ctrl_main, osd_hdr_ready_flag, 0x1);
	OSDX_CTRL_E60_WrFL(0, osd_ctrl_main);

	FBDEV_NOTI("logo fbmem old=0x%08x new=0x%08x\n", fbmem_addr_src, fbmem_addr_dst);
func_exit:
	if (cmap_src.virt_addr)
	{
		OS_CloseCacheMap(&cmap_src);
	}
	if (cmap_dst.virt_addr)
	{
		OS_CloseCacheMap(&cmap_dst);
	}
#endif
}

/**
 *
 */
void FBDEV_E60_CMN_RunBootLogoTimer(UINT32 ms, BOOLEAN bForce)
{
#if (CONFIG_LX_BOOT_LOGO==1)
	static BOOLEAN		b_timer_req = TRUE;
	static OS_TIMER_T	osd_en_timer;

	if ( b_timer_req || bForce )
	{
		b_timer_req = FALSE;
		FBDEV_BOOT_DEBUG("start boot timer %d ms (%d)\n", ms, bForce);

		if (ms>0)
		{
			OS_InitTimer ( &osd_en_timer );
			OS_StartTimer( &osd_en_timer, FBDEV_E60_CMN_EnableOSDHdrFlush, OS_TIMER_TIMEOUT, ms, 0x0 );
		}
		else
		{
			FBDEV_E60_CMN_EnableOSDHdrFlush(0x0);
		}
	}
#else
	FBDEV_E60_CMN_EnableOSDHdrFlush(0x0);
#endif
}

/** query tcon clk information & detect vsync clk interval
 *  @note this function should be called after SYS kdriver initialization
 */
static FBDEV_VSYNC_CLK_T FBDEV_E60_CMN_DetectVSyncClk(void)
{
#ifdef FBDEV_E60_USE_CTOP_REGS
	typedef struct
	{
		UINT32	:11,
				reg_tcon_tcon_pix2_clk_sel : 2;	/* 0: 4K120, 1:4K60, 2:2K120, 3:2K60 */
	}
	CRG_TCON02_REG;

	UINT32 val;
	CRG_TCON02_REG* crg_tcon02_reg;
	UINT32 tcon_pix2_clk;

	OS_RdReg(0xC930F008, &val);
	crg_tcon02_reg = (CRG_TCON02_REG*)&val;
	tcon_pix2_clk = crg_tcon02_reg->reg_tcon_tcon_pix2_clk_sel;

	// raxis.lim
	//
	// 위 ctop regs 의 값은 현재 출력 해상도에 따라 다른 의미를 가질 수 있음을 잊지 말것
	// 즉 아래 구현된 코드는 4K (이상의) 출력기준, 0 or 2 이면 120Hz 의 의미일 뿐이다.
	// 만약 FHD 해상도를 지원하는 경우라면, 아래 값은 120Hz 의 의미가 아닐 지도 모른다.
	// 결론은 알고 사용하자
	//
	FBDEV_NOTI("VSYNC detection = %d (%dHz)\n", tcon_pix2_clk, (tcon_pix2_clk==0 || tcon_pix2_clk==2)? 120:60);
	return (tcon_pix2_clk == 0x0 || tcon_pix2_clk == 0x2) ? FBDEV_VSYNC_CLK_120HZ: FBDEV_VSYNC_CLK_60HZ;
#else
	FBDEV_WARN("(!) SYNC detector not ready.. default vsync = 60Hz \n");
	return FBDEV_VSYNC_CLK_60HZ;
#endif
}

static void FBDEV_E60_CMN_NotifyToPQEDriver(void)
{
#ifdef INCLUDE_KDRV_OVI
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	/* see be/top/be_top_hal.h */
	extern int BE_TOP_HAL_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T *pstParams);
	LX_BE_FBDEV_STATUS_T osd2pqe_status;

	FBDEV_NOTI("+ notify PQE FW to setup : %d/%d/%d/%d\n",
			hw_ctx->b_support_4kosd,
			hw_ctx->user_initcall_ctrl.status.osd_init_done,
			hw_ctx->user_initcall_ctrl.status.osd_v_mirror,
			hw_ctx->user_initcall_ctrl.status.osd_estreamer);

	osd2pqe_status.bFbdevInitDone = hw_ctx->user_initcall_ctrl.status.osd_init_done;
	osd2pqe_status.bOsdVReverseOn = hw_ctx->user_initcall_ctrl.status.osd_v_mirror;
	osd2pqe_status.bEStreamerOn   = hw_ctx->user_initcall_ctrl.status.osd_estreamer;
	osd2pqe_status.b4kOSDResolution = (hw_ctx->b_support_4kosd)? TRUE:FALSE;

	FBDEV_CHECK_ERROR(RET_OK!=BE_TOP_HAL_InformFBDEVStatus(&osd2pqe_status), /* nop */, "BE_TOP_HAL_InformFBDEVStatus error\n");
#endif
}

static int	FBDEV_E60_CMN_WaitForPQEDriverInitialization(void)
{
#ifdef INCLUDE_KDRV_OVI
	/* see be/top/be_top_hal.h */
	extern int BE_TOP_HAL_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T *pstParams);
	LX_BE_FW_OSD_STATUS_T pqe2osd_status;

	FBDEV_CHECK_ERROR(RET_OK!=BE_TOP_HAL_GetFWOSDStatus(&pqe2osd_status), return RET_ERROR, "BE_TOP_HAL_GetFWOSDStatus error\n");

	FBDEV_NOTI("+ wait for PQE FW to setup : %d/%d\n",
		pqe2osd_status.bFwOsdOrbitInitDone, pqe2osd_status.bFwOsdSrInitDone);

	if (pqe2osd_status.bFwOsdOrbitInitDone && pqe2osd_status.bFwOsdSrInitDone)
		return RET_OK;
	else
		return RET_TIMEOUT;
#else
	return RET_OK;
#endif
}

/*========================================================================================
    Implementation Group (OSD HW Initialization)
========================================================================================*/

void FBDEV_E60_CMN_SetupHWFunc(int cfgId, UINT32 param, UINT32 paramex[4])
{
	FBDEV_E60_HW_CTX_T*	hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_E60_MIRROR_CTRL_T* mirror_ctrl = FBDEV_E60_GET_MIRROR_CTRL(hw_ctx);

	UINT32 out_w = hw_ctx->hw_disp_width;
	UINT32 out_h = hw_ctx->hw_disp_height;
	UINT32 sosd_mode = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0:1;	// 0:BOSD, 1:SOSD
	UINT32 _4k_osd = hw_ctx->b_support_4kosd;
	UINT32 fb_scale_mode = hw_ctx->hw_fb_scale_mode;
	UINT32 mirror_mode = (mirror_ctrl->status & FBDEV_E60_V_MIRROR_ON)? 0x1: 0x0; //0:OFF, 1:ON

	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");
	FBDEV_HW_NOTI("+ hwsetup cfg=0x%04x, param=%d\n", cfgId, param);

	switch(cfgId)
	{
		// setup PIC_INIT
		// setup PIC_START
		// setup CTRL_INTR_PULSE
		// setup CTRL_D(S)PATH
		// setup CTRL_BLOCK
		// setup CTRL_B(S)OSD_PULsE
		// setup CTRL_SYNC_GEN_CTRL0~7
		// (note) CTRL_AUTO_INIT_AFBC is not set here
		case HWSETUP_PIC_INIT:
		{
			FBDEV_HW_NOTI("HWSETUP_PIC_INIT\n");

			// raxis.lim (2020/03/05)
			// CCO1 의 auto pic init 에서는 OSD 연관된 것만 있는 것이 아님.
			// F20 과 연동을 위한 chipinfo 관련 pic init sequence 에 따라 이상 동작을 할 수 있음
			// 따라서 OSD 관련된 g0~g4 까지만 설정하고, g5~g7 은 건드리지 말것
			// 이지훈s 에게 문의
			OSD_CCO1_TOP_E60_RdFL(pic_init);
			OSD_CCO1_TOP_E60_RdFL(pic_start);
			OSD_CCO1_TOP_E60_Wr01(pic_init, g0_auto_init, 0x1);
			OSD_CCO1_TOP_E60_Wr01(pic_init, g1_auto_init, 0x1);
			OSD_CCO1_TOP_E60_Wr01(pic_init, g2_auto_init, 0x1);
			OSD_CCO1_TOP_E60_Wr01(pic_init, g4_auto_init, 0x1);
			//OSD_CCO1_TOP_E60_Wr01(pic_init,g5_auto_init,0x1);
			//OSD_CCO1_TOP_E60_Wr01(pic_init,g7_auto_init,0x1);
			OSD_CCO1_TOP_E60_Wr(pic_start, 0x00000000);

			OSD_CCO2_TOP_E60_RdFL(pic_init);
			OSD_CCO2_TOP_E60_RdFL(pic_start);
			OSD_CCO2_TOP_E60_Wr01(pic_init, g0_auto_init, 0x1);
			OSD_CCO2_TOP_E60_Wr01(pic_init, g1_auto_init, 0x1);
			OSD_CCO2_TOP_E60_Wr01(pic_init, g2_auto_init, 0x1);
			OSD_CCO2_TOP_E60_Wr01(pic_init, g4_auto_init, 0x1);
			//OSD_CCO2_TOP_E60_Wr01(pic_init,g5_auto_init,0x1);
			//OSD_CCO2_TOP_E60_Wr01(pic_init,g7_auto_init,0x1);
			OSD_CCO2_TOP_E60_Wr(pic_start, 0x00000000);

			OSD_CCO1_TOP_E60_WrFL(pic_init);
			OSD_CCO1_TOP_E60_WrFL(pic_start);
			OSD_CCO2_TOP_E60_WrFL(pic_init);
			OSD_CCO2_TOP_E60_WrFL(pic_start);
		}
		break;

		// setup OSD sync
		case HWSETUP_OSD_SYNC:
		{
			// raxis.lim (2019/12/26)
			// OSD 화면이 전체적으로 우->좌로 흐르는 문제가 있어,아래와 같은 가이드를 받음
			// 발현조건) 50Hz 입력 + AFBC 사용시
			//
			// TopCtrl_D >> CCO1_CTRL >> CTRL_INTR_PULSE >> idx_src_i7_intr_pulse (0xc903000c [30:28]) : 0으로 설정
			// > 0xba876420 -> 0x8a876420
			// TopCtrl_D >> CCO2_CTRL >> CTRL_INTR_PULSE >> idx_src_i7_intr_pulse (0xc903300c [30:28]) : 0으로 설정
			// > 0xba876420 -> 0x8a876420
			//
			// raxis.lim (2020/03/13)
			// S.OSD 와 B.OSD 에 따라 상이한 설정이 필요한 경우가 많으므로 주의할것
			// - intr_pulse 의 값은 B.OSD 와 S.OSD 각각 틀린 값이므로 주의할것. 값이 틀리면 OSD 안나옴.
			// - bosd_pulse 값과 sosd_pulse 값이 동일함. 이것은 테스트 결과의 차이일 뿐이므로 값을 각각 관리할것
			//
			// raxis.lim (2020/07/20)
			// S.OSD 4K 를 위한 sync_gen_ctrl 파라미터 수정 (SICDTV-8491)
			//
			// raxis.lim (2020/07/29)
			// http://clm.lge.com/issue/browse/SICDTV-8491?focusedCommentId=2501919&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2501919
			//
			// E60+F20 조합에서 OSD, AFBC pic init 설정 변경 필요
			// cco1_ctrl.ctrl_intr_pulse : 0xFA87_6420 -> 0xCA87_6420
			// cco1_ctrl.ctrl_sosd_pulse : 0x0000_D000 -> 0x1000_D000
			//
			// cco2_ctrl 은 기존값 유지할것
			//
			UINT32 cco1_intr_pulse_val = (sosd_mode)? 0xCA876420: 0x8A876420;
			UINT32 cco2_intr_pulse_val = (sosd_mode)? 0xFA876420: 0x8A876420;
			UINT32 cco1_sosd_pulse_val = (sosd_mode)? 0x1000D000: 0x0000D000;
			UINT32 cco2_sosd_pulse_val = 0x00000000;

			static const UINT32 sync_gen_param_list[3][8] = {
				{0x00040005, 0x00240438, 0x002C0016, 0x004A03C0, 0x00040005, 0x00240438, 0x0001002C, 0x0001002C},	// B.OSD 2K/4K
				{0x0008000A, 0x00480870, 0x00B00058, 0x01280F00, 0x0008000A, 0x00480870, 0x0001006F, 0x00080058},	// S.OSD 4K
				{0x00040005, 0x00240438, 0x0058002C, 0x00940780, 0x00040005, 0x00240438, 0x0001006F, 0x00080058},	// S.OSD 2K
			};

			const UINT32* sync_gen_param = 	(!sosd_mode)? 	 sync_gen_param_list[0]:
											(out_w >= 2048)? sync_gen_param_list[1]:sync_gen_param_list[2];

			FBDEV_HW_NOTI("HWSETUP_OSD_SYNC. sosd=%d, 4kosd=%d\n", sosd_mode, _4k_osd);

			OSD_CCO1_TOP_E60_Wr(ctrl_intr_pulse, cco1_intr_pulse_val);
			OSD_CCO1_TOP_E60_Wr(ctrl_bosd_pulse, 0x0000D000);
			OSD_CCO1_TOP_E60_Wr(ctrl_sosd_pulse, cco1_sosd_pulse_val);
			OSD_CCO1_TOP_E60_Wr(ctrl_block, 	 0x00000307);

			OSD_CCO2_TOP_E60_Wr(ctrl_intr_pulse, cco2_intr_pulse_val);
			OSD_CCO2_TOP_E60_Wr(ctrl_bosd_pulse, 0x00000000);
			OSD_CCO2_TOP_E60_Wr(ctrl_sosd_pulse, cco2_sosd_pulse_val);
			OSD_CCO2_TOP_E60_Wr(ctrl_block, 	 0x00000007);

			OSD_CCO2_TOP_E60_Wr(osd_sync_gen_ctrl0, sync_gen_param[0]);
			OSD_CCO2_TOP_E60_Wr(osd_sync_gen_ctrl1, sync_gen_param[1]);
			OSD_CCO2_TOP_E60_Wr(osd_sync_gen_ctrl2, sync_gen_param[2]);
			OSD_CCO2_TOP_E60_Wr(osd_sync_gen_ctrl3, sync_gen_param[3]);
			OSD_CCO2_TOP_E60_Wr(osd_sync_gen_ctrl4, sync_gen_param[4]);
			OSD_CCO2_TOP_E60_Wr(osd_sync_gen_ctrl5, sync_gen_param[5]);
			OSD_CCO2_TOP_E60_Wr(osd_sync_gen_ctrl6, sync_gen_param[6]);
			OSD_CCO2_TOP_E60_Wr(osd_sync_gen_ctrl7, sync_gen_param[7]);

			OSD_CCO1_TOP_E60_WrFL(ctrl_intr_pulse);
			OSD_CCO1_TOP_E60_WrFL(ctrl_bosd_pulse);
			OSD_CCO1_TOP_E60_WrFL(ctrl_sosd_pulse);
			OSD_CCO1_TOP_E60_WrFL(ctrl_block);

			OSD_CCO2_TOP_E60_WrFL(ctrl_intr_pulse);
			OSD_CCO2_TOP_E60_WrFL(ctrl_bosd_pulse);
			OSD_CCO2_TOP_E60_WrFL(ctrl_sosd_pulse);
			OSD_CCO2_TOP_E60_WrFL(ctrl_block);

			OSD_CCO2_TOP_E60_WrFL(osd_sync_gen_ctrl0);
			OSD_CCO2_TOP_E60_WrFL(osd_sync_gen_ctrl1);
			OSD_CCO2_TOP_E60_WrFL(osd_sync_gen_ctrl2);
			OSD_CCO2_TOP_E60_WrFL(osd_sync_gen_ctrl3);
			OSD_CCO2_TOP_E60_WrFL(osd_sync_gen_ctrl4);
			OSD_CCO2_TOP_E60_WrFL(osd_sync_gen_ctrl5);
			OSD_CCO2_TOP_E60_WrFL(osd_sync_gen_ctrl6);
			OSD_CCO2_TOP_E60_WrFL(osd_sync_gen_ctrl7);
		}
		break;

		/* configure MIF to show OSD with ARGB color */
		case HWSETUP_OSD_MIF:
		{
			FBDEV_HW_NOTI("HWSETUP_OSD_MIF\n");

			// raxis.lim (2019/12/14)
			// MIF 는 아래 3개 외에는 사용할 일도 없어, 굳이 register 변환하지 않겠음.
			//
			//WR C9031620 F00000FA    # R_OSD0_MB_REQ (MIF0+0x20)
			//WR C9031660 F00000FB    # R_CSR0_MB_REQ (MIF0+0x60)
			//WR C9031820 F00000FA    # R_OSD1_MB_REQ (MIF1+0x20)

			//혹시 동작 이상있을시, O20 경우 참조하여 디버깅하세요.
			//wr 0XC9010C20 0x400000FB     # R_OSD0_MB_REQ.req_msk_f_on=0 (for UI)
			//wr 0XC9010C60 0x400000FB     # R_CSR0_MB_REQ.req_msk_f_on=0 (for CURSOR)
			//wr 0XC9012820 0x400000FB     # R_OSD1_MB_REQ.req_msk_f_on=0 (for E-Streamer)
			//
			//MIF1req_msk_f_on=1 설정시 IMAGE1 ARGB 출력시 화면이 보이지 않음. (SICDTV-6809 참조)
			//
			OS_WrReg(CCO_MIF0_BASE+0x20, 0xF00000FA);
			OS_WrReg(CCO_MIF0_BASE+0x60, 0xF00000FB);
			OS_WrReg(CCO_MIF1_BASE+0x20, 0xF00000FA);
		}
		break;

		case HWSETUP_IMG_OSDSR:
		{
#ifdef FBDEV_E60_USE_SR_CTRL
			FBDEV_E60_SR_CTRL_T* sr_ctrl = FBDEV_E60_GET_SR_CTRL(hw_ctx, LX_FBDEV_ID_OSD0);
    		UINT32 detour_en = (sr_ctrl->status==FBDEV_E60_SR_STATUS_OFF)? 1:0;
#else
    		UINT32 detour_en = 1;
#endif
			FBDEV_HW_NOTI("HWSETUP_IMG_OSDSR /w detour_en=1 (always)\n");

			OSDX_E60_RdFL(osdx_prep_img1, osd0_sr_merge_a_ctrl);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_sr_merge_y_ctrl);

			MERG_E60_RdFL(osdx_merg_a, sr_merge_ctrl_00);
			MERG_E60_RdFL(osdx_merg_y, sr_merge_ctrl_00);

			OSDX_E60_Wr03(osdx_prep_img1, osd0_sr_merge_a_ctrl, osdsra_ready_force_val, detour_en, osdsra_ready_force_en, detour_en, osdsra_merge_detour_en, detour_en);
			MERG_E60_Wr01(osdx_merg_a, sr_merge_ctrl_00, reg_sr_merge_en, 0x0);

			OSDX_E60_Wr03(osdx_prep_img1, osd0_sr_merge_y_ctrl, osdsry_ready_force_val, detour_en, osdsry_ready_force_en, detour_en, osdsry_merge_detour_en, detour_en);
			MERG_E60_Wr01(osdx_merg_y, sr_merge_ctrl_00, reg_sr_merge_en, 0x0);

			FBDEV_HW_NOTI("osd0_sr_merge_a_ctrl=0x%08x\n", OSDX_E60_Rd(osdx_prep_img1,osd0_sr_merge_a_ctrl));
			FBDEV_HW_NOTI("osd0_sr_merge_y_ctrl=0x%08x\n", OSDX_E60_Rd(osdx_prep_img1,osd0_sr_merge_y_ctrl));

			OSDX_E60_WrFL(osdx_prep_img1, osd0_sr_merge_a_ctrl);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_sr_merge_y_ctrl);

			MERG_E60_WrFL(osdx_merg_a, sr_merge_ctrl_00);
			MERG_E60_WrFL(osdx_merg_y, sr_merge_ctrl_00);
		}
		break;

		case HWSETUP_IMG_OSDSHP:
		{
			UINT32 gb           = 48;
			UINT32 hsize        = out_w/2;
			UINT32 s_p_mode_in  = 2;
			UINT32 s_p_mode_out = 1;

			UINT32 m_p_mode_in  = 1;
			UINT32 m_p_mode_out = 2;

			UINT32 shp_w   = out_w;
			UINT32 shp_h   = out_h;
			UINT32 shp_s_w = out_w/2 + 2*gb;

			FBDEV_HW_NOTI("HWSETUP_IMG_OSDSHP\n");

			SHP_CTRL_RdFL(osd_shp_y, shp_split_ctrl_00);
			SHP_CTRL_RdFL(osd_shp_y, shp_split_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_y, shp_merge_ctrl_00);
			SHP_CTRL_RdFL(osd_shp_y, shp_merge_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_a, shp_split_ctrl_00);
			SHP_CTRL_RdFL(osd_shp_a, shp_split_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_a, shp_merge_ctrl_00);
			SHP_CTRL_RdFL(osd_shp_a, shp_merge_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_y, shp_core_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_y, shp_core0_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_y, shp_core1_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_a, shp_core_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_a, shp_core0_ctrl_01);
			SHP_CTRL_RdFL(osd_shp_a, shp_core1_ctrl_01);

			// split/merge
			SHP_CTRL_Wr03(osd_shp_y, shp_split_ctrl_00, reg_split_hsize, out_w, reg_split_pmode_in, s_p_mode_in, reg_split_pmode_out, s_p_mode_out);
			SHP_CTRL_Wr02(osd_shp_y, shp_split_ctrl_01, reg_split_guardband, gb, reg_split_split_size, hsize);
			SHP_CTRL_Wr03(osd_shp_y, shp_merge_ctrl_00, reg_merge_hsize, out_w, reg_merge_pmode_in, m_p_mode_in, reg_merge_pmode_out, m_p_mode_out);
			SHP_CTRL_Wr02(osd_shp_y, shp_merge_ctrl_01, reg_merge_guardband, gb, reg_merge_split_size, hsize);

			SHP_CTRL_Wr03(osd_shp_a, shp_split_ctrl_00, reg_split_hsize, out_w, reg_split_pmode_in, s_p_mode_in, reg_split_pmode_out, s_p_mode_out);
			SHP_CTRL_Wr02(osd_shp_a, shp_split_ctrl_01, reg_split_guardband, gb, reg_split_split_size, hsize);
			SHP_CTRL_Wr03(osd_shp_a, shp_merge_ctrl_00, reg_merge_hsize, out_w, reg_merge_pmode_in, m_p_mode_in, reg_merge_pmode_out, m_p_mode_out);
			SHP_CTRL_Wr02(osd_shp_a, shp_merge_ctrl_01, reg_merge_guardband, gb, reg_merge_split_size, hsize);

			SHP_CTRL_Wr02(osd_shp_y, shp_core_ctrl_01 , reg_core_height , shp_h, reg_core_width , shp_w);
			SHP_CTRL_Wr02(osd_shp_y, shp_core0_ctrl_01, reg_core0_height, shp_h, reg_core0_width, shp_s_w);
			SHP_CTRL_Wr02(osd_shp_y, shp_core1_ctrl_01, reg_core1_height, shp_h, reg_core1_width, shp_s_w);

			SHP_CTRL_Wr02(osd_shp_a, shp_core_ctrl_01 , reg_core_height , shp_h, reg_core_width , shp_w);
			SHP_CTRL_Wr02(osd_shp_a, shp_core0_ctrl_01, reg_core0_height, shp_h, reg_core0_width, shp_s_w);
			SHP_CTRL_Wr02(osd_shp_a, shp_core1_ctrl_01, reg_core1_height, shp_h, reg_core1_width, shp_s_w);

			SHP_CTRL_WrFL(osd_shp_y, shp_split_ctrl_00);
			SHP_CTRL_WrFL(osd_shp_y, shp_split_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_y, shp_merge_ctrl_00);
			SHP_CTRL_WrFL(osd_shp_y, shp_merge_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_a, shp_split_ctrl_00);
			SHP_CTRL_WrFL(osd_shp_a, shp_split_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_a, shp_merge_ctrl_00);
			SHP_CTRL_WrFL(osd_shp_a, shp_merge_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_y, shp_core_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_y, shp_core0_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_y, shp_core1_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_a, shp_core_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_a, shp_core0_ctrl_01);
			SHP_CTRL_WrFL(osd_shp_a, shp_core1_ctrl_01);
		}
		break;

		// setup display size
		// @note called at initialization
		case HWSETUP_OSD_PREP_TOP:
		{
			int i;
			FBDEV_HW_NOTI("HWSETUP_OSD_PREP_TOP\n");

			for (i=0;i<8;i++)
			{
				OSDX_E60_RdFL(osdx_prep_top, osd_prep_top_disp_size[i]);
				OSDX_E60_Wr02(osdx_prep_top, osd_prep_top_disp_size[i], reg_top_disp_size_w, out_w, reg_top_disp_size_h, out_h);
				OSDX_E60_WrFL(osdx_prep_top, osd_prep_top_disp_size[i]);
			}
		}
		break;

		// setup display size
		// @note called at initialization
		case HWSETUP_OSD_POST_TOP:
		{
			FBDEV_HW_NOTI("HWSETUP_OSD_POST_TOP\n");

		    OSDX_E60_RdFL(osdx_post_top, osd_post_top_disp_size);
		    OSDX_E60_Wr02(osdx_post_top, osd_post_top_disp_size, reg_top_disp_size_w, out_w, reg_top_disp_size_h, out_h);
		    OSDX_E60_WrFL(osdx_post_top, osd_post_top_disp_size);
		}
		break;

		// setup bosd, sosd size
		// @note called at initialization
		case HWSETUP_OSD_MIXER:
		{
			UINT32 bosd_out_w = hw_ctx->bosd_disp.out_width;
			UINT32 bosd_out_h = hw_ctx->bosd_disp.out_height;
			UINT32 sosd_out_w = hw_ctx->sosd_disp.out_width;
			UINT32 sosd_out_h = hw_ctx->sosd_disp.out_width;

			FBDEV_HW_NOTI("HWSETUP_OSD_MIXER\n");

			// setup S.OSD & B.OSD mixer disp size
			OSDX_E60_RdFL(osdx_bosd_mixer, osd_mixer_disp_size);
			OSDX_E60_Wr02(osdx_bosd_mixer, osd_mixer_disp_size,	reg_osd_disp_size_w, bosd_out_w, reg_osd_disp_size_h, bosd_out_h);
			OSDX_E60_WrFL(osdx_bosd_mixer, osd_mixer_disp_size);

			OSDX_E60_RdFL(osdx_sosd_mixer, osd_mixer_disp_size);
			OSDX_E60_Wr02(osdx_sosd_mixer, osd_mixer_disp_size,	reg_osd_disp_size_w, sosd_out_w, reg_osd_disp_size_h, sosd_out_h);
			OSDX_E60_WrFL(osdx_sosd_mixer, osd_mixer_disp_size);
		}
		break;

		// setup common part of each layer
		case HWSETUP_OSD_LAYER:
		{
			UINT32 sync_hdouble_en;
			UINT32 hdr_src_sel;
			UINT32 osd_manual_dlr_val;

			int hdr_rdy_flag = 0x0;
			int	xidx = param;
			UINT32 osd_en = paramex[0];

			/* raxis.lim (2014/06)
			 * if BLEND mode, each OSD layer should have a half of real display size (it's HW spec)
			 * this restruction is also applied to the cursor layer.
			 */
			sync_hdouble_en = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0x0: 0x1;

#ifdef FBDEV_E60_USE_HDR_RDY_REG
			hdr_rdy_flag = 0x1;
#endif
			hdr_src_sel = 0x1;

			/* MIF feeder cfg : "10 (0x2)" L to R (HW default value)
			 * this value has ben fixed to "10" inside OSD HW since older chip.
			 * In E60/E60, this value can be configurable by SW But I keep this value as 0x2 forever
			 *
			 * HW default value = 0x2
			 */
			osd_manual_dlr_val = 0x2;

			FBDEV_HW_NOTI("HWSETUP_OSD_LAYER\n");

			//WR C9030600 00000011    # OSD0_0_CTRL_MAIN
			//WR C9030608 00008000    # OSD0_0_LOADER_CTRL0  (use my custom config)
			//WR C903060C 1B000000    # OSD0_0_LOADER_CTRL1
			//WR C9030610 00000000    # OSD0_0_LOADER_CTRL2  (not used)
			//WR C9030614 00000000    # OSD0_0_LOADER_CTRL3  (not used)
			OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_main);
			OSDX_CTRL_E60_RdFL(xidx, osd_ctrl0);
			OSDX_CTRL_E60_RdFL(xidx, osd_ctrl1);

			/* (2020/12/15) remove the early osd_en control
			* osd will be enabled after the frist image update is completed
			* 특히 초기에 수행되는 osd(0) 에 대한 osd_en 과 sync_enable 을 동시에 제거 필요
			* see FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE handler
			* see http://clm.lge.com/issue/browse/SICDTV-9043
			* see http://hlm.lge.com/qi/browse/INQAISSUE-81
			*/
#if 0
			OSDX_CTRL_E60_Wr05(xidx, osd_ctrl_main,
					osd_en, osd_en,
					osd_hdr_ready_flag_en, hdr_rdy_flag,
					osd_v_reverse_en, mirror_mode,
					osd_hdr_src_sel, hdr_src_sel,
					osd_manual_dlr, osd_manual_dlr_val);
#else
			PARAM_UNUSED(osd_en);
			OSDX_CTRL_E60_Wr04(xidx, osd_ctrl_main,
					osd_hdr_ready_flag_en, hdr_rdy_flag,
					osd_v_reverse_en, mirror_mode,
					osd_hdr_src_sel, hdr_src_sel,
					osd_manual_dlr, osd_manual_dlr_val);
#endif

			// raxis.lim (2019/12/14)
			// re-configure HW default value 0x1b000000 (do not change~~)
			// (CHECK) big endian 으로 설정하는 이유를 모르겠다. 만약 OSD 가 안나오거나, 색이 이상하다면 의심해 볼것
			//
			// raxis.lim (2019/12/16)
			//
			// 이지훈s 이 ctrl0(예전 swap_ctrl) 의 복잡한 swap 대신 사용하라고, endian 을 추가하였다고 함
			// 일단 믿고 사용할것
			OSDX_CTRL_E60_Wr(xidx, osd_ctrl0, 0x00000000);
			OSDX_CTRL_E60_Wr01(xidx, osd_ctrl0, osd_endian_sel, 0x1);

			OSDX_CTRL_E60_Wr07(xidx, osd_ctrl1, osd_ch_alpha, 0x0, osd_ch_red, 0x1, osd_ch_green, 0x2, osd_ch_blue, 0x3,
							osd_round,0x0, osd_pure_ck, 0x0, osd_lfsr_seed, 0x0);

			OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_main);
			OSDX_CTRL_E60_WrFL(xidx, osd_ctrl0);
			OSDX_CTRL_E60_WrFL(xidx, osd_ctrl1);
		}
		break;

		case HWSETUP_OSD_VIEW_CTRL:
		{
			UINT32 xidx = param;
			UINT32 osd_en = paramex[0];
			UINT32 afbc0_xidx = paramex[1];
			UINT32 afbc1_xidx = paramex[2];

			FBDEV_HW_NOTI("HWSETUP_OSD_VIEW_CTRL (%d,%d)\n", xidx, osd_en);

			OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_main);
			OSDX_CTRL_E60_Wr01(xidx, osd_ctrl_main, osd_en, osd_en);
			OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_main);

			switch(xidx)	/* fb_dev_id 아님. 헷갈리지 말것 */
			{
				case 0:
				{
					int afbc_status = FBDEV_E60_CMN_GetHWStatus(FBDEV_E60_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0);

					OSDX_E60_RdFL(osdx_post_img, osd0_img_sync_ctrl0);
					OSDX_E60_Wr01(osdx_post_img, osd0_img_sync_ctrl0, osd_sync_enable, osd_en);
					OSDX_E60_WrFL(osdx_post_img, osd0_img_sync_ctrl0);

					// (2020/11/17) http://clm.lge.com/issue/browse/SICDTV-8986, QEVENTTWON-8969
					// OSD off 과정에서 20% 의 확률로 화면 우측에서의 과도 (가비지) 출력 현상 있음
					// OSD off 과정에서 실제 OSD 출력을 끊고, 후속 조치(AFBC 중지 등)이 진행되도록 함
					if (!osd_en)
					{
						if(fbdev_hw_pm_suspend_stage)
						{
							udelay(16700);
						}
						else
						{
							usleep_range(16700, 16700);
						}
					}

				#ifdef FBDEV_E60_USE_FBC_CTRL
					OSD_CCO1_TOP_E60_RdFL(ctrl_auto_init_afbc);

					if(afbc_status)
					{
						if(afbc0_xidx==0 || afbc1_xidx==0)	/* AFBC(0) */
						{
							OSD_CCO1_TOP_E60_Wr02(ctrl_auto_init_afbc, reg_afbc0_init_en, osd_en, reg_afbc0_auto_init_en, osd_en);
						}

						if(afbc0_xidx==1 || afbc1_xidx==1)	/* AFBC(1) */
						{
							OSD_CCO1_TOP_E60_Wr02(ctrl_auto_init_afbc, reg_afbc1_init_en, osd_en, reg_afbc1_auto_init_en, osd_en);

							// (2020/08/06)
							// 4K OSD 모드 + AFBC 모드에서는 afbc(1) 도 사용되게 되는데,
							// EST 가 MIF (ARGB) 에서 데이터를 읽을 수 있도록, afbc(1)을 on/off 해주어야 한다.
							// OSD 의 내부 mux 상에서 EST 레이어의 MIF 와 AFBC 선택은 osd1_afbc_en 으로 제어된다.
							// see SICDTV-8669
							OSD_CCO1_TOP_E60_RdFL(ctrl_dpath);
							OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd1_afbc_en, osd_en);
							OSD_CCO1_TOP_E60_WrFL(ctrl_dpath);
						}
					}
					else
					{
						if(afbc0_xidx==0 || afbc1_xidx==0)	/* AFBC(0) */
						{
							OSD_CCO1_TOP_E60_Wr02(ctrl_auto_init_afbc, reg_afbc0_init_en, 0x0, reg_afbc0_auto_init_en, 0x0);
						}

						if(afbc0_xidx==1 || afbc1_xidx==1)	/* AFBC(1) */
						{
							OSD_CCO1_TOP_E60_Wr02(ctrl_auto_init_afbc, reg_afbc1_init_en, 0x0, reg_afbc1_auto_init_en, 0x0);
						}
					}

					OSD_CCO1_TOP_E60_WrFL(ctrl_auto_init_afbc);
				#endif

					// (2020/08/06)
					// 4KOSD 모드 환경에서, 4k_mode 를 off 해주어야 IMG 대신 EST 가 데이터를 읽을 수 있다
					// OSD 의 내부 mux 상에서 IMG1 과 EST 는 4k_mode 으로 제어된다.
					// see SICDTV-8669
					if (hw_ctx->b_support_4kosd)
					{
 						if(!fbdev_hw_pm_suspend_stage)
						{
							OSDX_E60_RdFL(osdx_prep_img0, osd0_4k_ctrl0);
							OSDX_E60_Wr01(osdx_prep_img0, osd0_4k_ctrl0, reg_4k_mode_en, osd_en);
							OSDX_E60_WrFL(osdx_prep_img0, osd0_4k_ctrl0);
						}
					}

					FBDEV_NOTI("UI(IMG0:%s) - %s\n", (hw_ctx->b_support_4kosd)? "4K":"2K", (osd_en)? "on":"off");
				}
				break;

				case 1:
				{
					/* second UI layer if 4K OSD enabeld, do nothing */
				}
				break;

				case 2:
				{
					OSDX_E60_RdFL(osdx_post_est, osd1_est_sync_ctrl0);
					OSDX_E60_Wr01(osdx_post_est, osd1_est_sync_ctrl0, osd_sync_enable, osd_en);
					OSDX_E60_WrFL(osdx_post_est, osd1_est_sync_ctrl0);

					// (2020/08/06)
					// EST 레이어가 사용되면, clock gating 을 해제 조치한다. 추후 FW 와 논의하도록 함
					// see SICDTV-8669
					//
					// (2020/10/16)
					// 현재 최신 코드 기준으로 FW 의 clock gating 코드는 삭제되었음을 확인. 하지만 아래 코드를 삭제하진 않도록 하겠음
					if (osd_en)
					{
						UINT32 reg_val;

						OS_RdReg(0xc9030190, &reg_val);
						((CTRL_CG_ON*)&reg_val)->reg_osd_est_layer_cg = 0;
						OS_WrReg(0xc9030190, reg_val);
						FBDEV_NOTI("<!> ctrl_cg_on=0x%08x reg_osd_est_layer_cg=0\n", reg_val);
					}
					FBDEV_NOTI("EST(EST) - %s\n", (osd_en)? "on":"off");
				}
				break;

				case 3:
				{
					// (2020/10/16)
					// Estreamer 동작과 같이 cursor 를 on 할 수 없는 경우에는 sync_en 를 강제로 off 토록 조치한다.
					// see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
					FBDEV_E60_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_E60_GET_EXT_RENDER_CTRL(hw_ctx);
					if(ext_render_ctrl->hwparam.enable)
					{
						FBDEV_NOTI("++ set cursor invisible when EXT_RENDER is running. req_status=%d\n", osd_en);
						osd_en = 0;
					}

					OSDX_E60_RdFL(osdx_post_csr, osd4_csr_sync_ctrl0);
					OSDX_E60_Wr01(osdx_post_csr, osd4_csr_sync_ctrl0, osd_sync_enable, osd_en);
					OSDX_E60_WrFL(osdx_post_csr, osd4_csr_sync_ctrl0);
				}
				break;
			}
		}
		break;

		// setup IMG loader
		case HWSETUP_IMG_LOADER:
		{
			FBDEV_HW_NOTI("HWSETUP_IMG_LOADER\n");

			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_PRE_TOP, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_OSDSR, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_OSDSHP, 0x0, NULL);

			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_4KOSD, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_SCALER, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_SCALER_COEF, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_SR_MERGE_BUF, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_POST_SCALER, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_POST_TOP, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_POST_CORE, 0x0, NULL);
		}
		break;

		// setup EST loader
		case HWSETUP_EST_LOADER:
		{
			FBDEV_HW_NOTI("HWSETUP_EST_LOADER\n");

			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_EST_PRE_TOP, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_EST_POST_CORE, 0x0, NULL);
		}
		break;

		// setup CSR loader
		case HWSETUP_CSR_LOADER:
		{
			FBDEV_HW_NOTI("HWSETUP_CSR_LOADER\n");
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_CSR_SCALER, 0x0, NULL);
			FBDEV_E60_CMN_SetupHWFunc(HWSETUP_CSR_POST_CORE, 0x0, NULL);
		}
		break;

		case HWSETUP_IMG_4KOSD:
		{
			UINT32 inp_w = hw_ctx->hw_fb0_width;
			UINT32 inp_h = hw_ctx->hw_fb0_height;

			FBDEV_HW_NOTI("HWSETUP_IMG_4KOSD (%d)\n", hw_ctx->b_support_4kosd);

		TODO_NOTE("4KOSD 즉 2K -> 4K 는 default off 함. default 는 2K -> 8K 임")

			 OSDX_E60_RdFL(osdx_prep_img0, osd0_4k_ctrl0);
			 OSDX_E60_RdFL(osdx_prep_img0, osd0_4k_ctrl2);
			 OSDX_E60_RdFL(osdx_prep_img0, osd0_4k_ctrl3);

			/* raxis.lim (2020/02/04) setup 4K OSD only configuration (3840x2160) -> (out_w, out_h)
			 *
			 * 이지훈s 이 4K OSD 모드에서는 개별 OSD header 정보를 보지 않고, 아래 값을 본다고 함.
			 */
			if(hw_ctx->b_support_4kosd)
			{
				OSDX_E60_Wr01(osdx_prep_img0, osd0_4k_ctrl0, reg_4k_mode_en, 0x1);

				OSDX_E60_Wr02(osdx_prep_img0, osd0_4k_ctrl2, reg_inp_w, inp_w, reg_inp_h, inp_h);
				OSDX_E60_Wr02(osdx_prep_img0, osd0_4k_ctrl3, reg_out_w, out_w, reg_out_h, out_h);
			}
			else
			{
				OSDX_E60_Wr01(osdx_prep_img0, osd0_4k_ctrl0, reg_4k_mode_en, 0x0);
			}

			OSDX_E60_WrFL(osdx_prep_img0, osd0_4k_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img0, osd0_4k_ctrl2);
			OSDX_E60_WrFL(osdx_prep_img0, osd0_4k_ctrl3);
		}
		break;

		/* 아래 코드는 동작하지 않음. see FBDEV_E60_CMN_SetupFBC */
		case HWSETUP_IMG_AFBC:
		{
		TODO_NOTE("아래 코드는 AFBC0 만 설정하고 있음")
			UINT32 afbc0_en = param;
			UINT32 afbc1_en = 0;
			UINT32 pulse_sel = (sosd_mode) ? 0x1 : 0x0;

			FBDEV_HW_NOTI("HWSETUP_IMG_AFBC\n");

			OSD_CCO1_TOP_E60_RdFL(ctrl_dpath);
			OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd0_afbc_en, afbc0_en);
			OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd1_afbc_en, afbc1_en);
			OSD_CCO1_TOP_E60_WrFL(ctrl_dpath);

			AFBC_CTRL_RdFL(0,ctrl_afbc_0);
			AFBC_CTRL_RdFL(1,ctrl_afbc_0);
			AFBC_CTRL_Wr01(0,ctrl_afbc_0, update_ready_flag_en, 0x1);
			AFBC_CTRL_Wr01(1,ctrl_afbc_0, update_ready_flag_en, 0x1);
			AFBC_CTRL_WrFL(0,ctrl_afbc_0);
			AFBC_CTRL_WrFL(1,ctrl_afbc_0);

			if(afbc0_en || afbc1_en)
			{
				OSD_CCO1_TOP_E60_RdFL(ctrl_auto_init_afbc);
				OSD_CCO1_TOP_E60_Wr07(ctrl_auto_init_afbc,
							reg_afbc1_partial_ack_en, 0x0,
							reg_afbc0_init_en, afbc0_en,
							reg_afbc0_auto_init_en, afbc0_en,
							reg_afbc0_auto_init_src, pulse_sel,
							reg_afbc1_init_en, afbc1_en,
							reg_afbc1_auto_init_en, afbc1_en,
							reg_afbc1_auto_init_src, pulse_sel);
				OSD_CCO1_TOP_E60_WrFL(ctrl_auto_init_afbc);
			}

			OSDX_CTRL_E60_RdFL(0, osd_ctrl_main);
			OSDX_CTRL_E60_Wr01(0, osd_ctrl_main, osd_bitmap_only_mode_en, afbc0_en);
			OSDX_CTRL_E60_Wr01(1, osd_ctrl_main, osd_bitmap_only_mode_en, afbc1_en);
			OSDX_CTRL_E60_WrFL(0, osd_ctrl_main);
		}
		break;

		case HWSETUP_IMG_SCALER:
		{
			UINT32 inp_w = hw_ctx->hw_fb0_width;
			UINT32 inp_h = hw_ctx->hw_fb0_height;
    		UINT32 scale_detour_en = (fb_scale_mode == FB_E60_SCALE_MODE_NONE)? 1:0;
    		UINT32 osd_scl_mode = (fb_scale_mode == FB_E60_SCALE_MODE_X4)? 0:1;

			FBDEV_HW_NOTI("HWSETUP_IMG_SCALER /w fb_scale=%d, scale_detour=%d\n", fb_scale_mode, scale_detour_en);

	    	OSDX_E60_RdFL(osdx_prep_img1, osd0_scaler_ctrl0);
	    	OSDX_E60_RdFL(osdx_prep_img1, osd0_scaler_ctrl1);
	    	OSDX_E60_RdFL(osdx_prep_img1, osd0_scaler_ctrl2);
	    	OSDX_E60_RdFL(osdx_prep_img1, osd0_scaler_a_ctrl);
	    	OSDX_E60_RdFL(osdx_prep_img1, osd0_scaler_y_ctrl);

	    	OSDX_E60_Wr02(osdx_prep_img1, osd0_scaler_ctrl0, osd_scl_mode, osd_scl_mode, osd_scl_detour_en, scale_detour_en);
			OSDX_E60_Wr02(osdx_prep_img1, osd0_scaler_ctrl1, osd_scl_i_width, inp_w, osd_scl_i_height, inp_h);
			OSDX_E60_Wr02(osdx_prep_img1, osd0_scaler_ctrl2, osd_scl_o_width, out_w, osd_scl_o_height, out_h);
			OSDX_E60_Wr07(osdx_prep_img1, osd0_scaler_a_ctrl, osd_scl_v_min_max_extend, 0x0, osd_scl_blur_flag_bypass_en, 0x0,
				osd_scl_min_max_th, 0x10, osd_scl_min_max_on, 0x1, osd_scl_adaptive_on, 0x1, osd_scl_blend_range, 0x1, osd_scl_th, 0x6);
			OSDX_E60_Wr07(osdx_prep_img1, osd0_scaler_y_ctrl, osd_scl_v_min_max_extend, 0x0, osd_scl_blur_flag_bypass_en, 0x0,
				osd_scl_min_max_th, 0x10, osd_scl_min_max_on, 0x1, osd_scl_adaptive_on, 0x1, osd_scl_blend_range, 0x1, osd_scl_th, 0x6);

	    	OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_ctrl0);
	    	OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_ctrl1);
	    	OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_ctrl2);
	    	OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_ctrl);
	    	OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_ctrl);

			// setup osd sc coef values should be set by HWSETUP_IMG_SCALER_COEF
		}
		break;

		case HWSETUP_IMG_SCALER_COEF:
		{
			// raxis.note -- 일부 coef 의 경우 수식에는 있으나 실제 사용되지 않는 것 있음. 향후 확인할것
			int coef_main_1_8[8] = { -7, 30,  -93,  995, 129,  -40, 11,  -1};
			int coef_main_3_8[8] = {-12, 53, -167,  786, 459, -127, 39,  -7};
			int coef_main_5_8[8] = { -7, 39, -127,  459, 786, -167, 53, -12};
			int coef_main_7_8[8] = { -1, 11,  -40,  129, 995,  -93, 30,  -7};

			//int coef_main_0_4[8] = {  0,  0,   -1, 1024,   1,     0,   0,    0};
			int coef_main_1_4[8] = {-11, 47, -148,  913, 286,   -84,  25,   -4};
			//int coef_main_2_4[8] = {-10, 49, -156,  629, 629,  -156,  49,  -10};
			int coef_main_3_4[8] = { -4, 25,  -84,  286, 913,  -148,  47,  -11};

			int coef_sub_1_8 [4] = { 36,  818, 173,  -3};
			int coef_sub_3_8 [4] = { -9,  646, 398, -11};
			int coef_sub_5_8 [4] = {-11,  398, 646,  -9};
			int coef_sub_7_8 [4] = { -3,  173, 818,  36};

			//int coef_sub_0_4 [4] = {  0, 1024,   0,   0};
			int coef_sub_1_4 [4] = {-45,  879, 195,  -5};
			//int coef_sub_2_4 [4] = {-25,  537, 537, -25};
			int coef_sub_3_4 [4] = { -5,  195, 879, -45};

			int phase_off_2k_p0 = 0;
			int phase_off_2k_p1 = 0;
			int phase_off_2k_p2 = 1;
			int phase_off_2k_p3 = 1;

			int phase_off_4k_p0 = 0;
			int phase_off_4k_p1 = 1;

			unsigned int p0_main_coef0 = 0;
			unsigned int p0_main_coef1 = 0;
			unsigned int p0_main_coef2 = 0;
			unsigned int p0_main_coef3 = 0;
			unsigned int p1_main_coef0 = 0;
			unsigned int p1_main_coef1 = 0;
			unsigned int p1_main_coef2 = 0;
			unsigned int p1_main_coef3 = 0;
			unsigned int p2_main_coef0 = 0;
			unsigned int p2_main_coef1 = 0;
			unsigned int p2_main_coef2 = 0;
			unsigned int p2_main_coef3 = 0;
			unsigned int p3_main_coef0 = 0;
			unsigned int p3_main_coef1 = 0;
			unsigned int p3_main_coef2 = 0;
			unsigned int p3_main_coef3 = 0;

			unsigned int p0_sub_coef0  = 0;
			unsigned int p0_sub_coef1  = 0;
			unsigned int p1_sub_coef0  = 0;
			unsigned int p1_sub_coef1  = 0;
			unsigned int p2_sub_coef0  = 0;
			unsigned int p2_sub_coef1  = 0;
			unsigned int p3_sub_coef0  = 0;
			unsigned int p3_sub_coef1  = 0;

			FBDEV_HW_NOTI("HWSETUP_IMG_SCALER_COEF /w fb_scale_mode=%d\n", fb_scale_mode);

			if (fb_scale_mode == FB_E60_SCALE_MODE_X4)	/* 2K to 8K scale mode */
			{
				p0_main_coef0 |= ( (phase_off_2k_p0 &0x1  ) << 31 );
				p0_main_coef0 |= ( (coef_main_5_8[0]&0xfff) << 16 );
				p0_main_coef0 |= ( (coef_main_5_8[1]&0xfff) <<  0 );
				p0_main_coef1 |= ( (coef_main_5_8[2]&0xfff) << 16 );
				p0_main_coef1 |= ( (coef_main_5_8[3]&0xfff) <<  0 );
				p0_main_coef2 |= ( (coef_main_5_8[4]&0xfff) << 16 );
				p0_main_coef2 |= ( (coef_main_5_8[5]&0xfff) <<  0 );
				p0_main_coef3 |= ( (coef_main_5_8[6]&0xfff) << 16 );
				p0_main_coef3 |= ( (coef_main_5_8[7]&0xfff) <<  0 );

				p1_main_coef0 |= ( (phase_off_2k_p1 &0x1  ) << 31 );
				p1_main_coef0 |= ( (coef_main_7_8[0]&0xfff) << 16 );
				p1_main_coef0 |= ( (coef_main_7_8[1]&0xfff) <<  0 );
				p1_main_coef1 |= ( (coef_main_7_8[2]&0xfff) << 16 );
				p1_main_coef1 |= ( (coef_main_7_8[3]&0xfff) <<  0 );
				p1_main_coef2 |= ( (coef_main_7_8[4]&0xfff) << 16 );
				p1_main_coef2 |= ( (coef_main_7_8[5]&0xfff) <<  0 );
				p1_main_coef3 |= ( (coef_main_7_8[6]&0xfff) << 16 );
				p1_main_coef3 |= ( (coef_main_7_8[7]&0xfff) <<  0 );

				p2_main_coef0 |= ( (phase_off_2k_p2 &0x1  ) << 31 );
				p2_main_coef0 |= ( (coef_main_1_8[0]&0xfff) << 16 );
				p2_main_coef0 |= ( (coef_main_1_8[1]&0xfff) <<  0 );
				p2_main_coef1 |= ( (coef_main_1_8[2]&0xfff) << 16 );
				p2_main_coef1 |= ( (coef_main_1_8[3]&0xfff) <<  0 );
				p2_main_coef2 |= ( (coef_main_1_8[4]&0xfff) << 16 );
				p2_main_coef2 |= ( (coef_main_1_8[5]&0xfff) <<  0 );
				p2_main_coef3 |= ( (coef_main_1_8[6]&0xfff) << 16 );
				p2_main_coef3 |= ( (coef_main_1_8[7]&0xfff) <<  0 );

				p3_main_coef0 |= ( (phase_off_2k_p3 &0x1  ) << 31 );
				p3_main_coef0 |= ( (coef_main_3_8[0]&0xfff) << 16 );
				p3_main_coef0 |= ( (coef_main_3_8[1]&0xfff) <<  0 );
				p3_main_coef1 |= ( (coef_main_3_8[2]&0xfff) << 16 );
				p3_main_coef1 |= ( (coef_main_3_8[3]&0xfff) <<  0 );
				p3_main_coef2 |= ( (coef_main_3_8[4]&0xfff) << 16 );
				p3_main_coef2 |= ( (coef_main_3_8[5]&0xfff) <<  0 );
				p3_main_coef3 |= ( (coef_main_3_8[6]&0xfff) << 16 );
				p3_main_coef3 |= ( (coef_main_3_8[7]&0xfff) <<  0 );

				p0_sub_coef0  |= ( (coef_sub_5_8 [0]&0xfff) << 16 );
				p0_sub_coef0  |= ( (coef_sub_5_8 [1]&0xfff) <<  0 );
				p0_sub_coef1  |= ( (coef_sub_5_8 [2]&0xfff) << 16 );
				p0_sub_coef1  |= ( (coef_sub_5_8 [3]&0xfff) <<  0 );

				p1_sub_coef0  |= ( (coef_sub_7_8 [0]&0xfff) << 16 );
				p1_sub_coef0  |= ( (coef_sub_7_8 [1]&0xfff) <<  0 );
				p1_sub_coef1  |= ( (coef_sub_7_8 [2]&0xfff) << 16 );
				p1_sub_coef1  |= ( (coef_sub_7_8 [3]&0xfff) <<  0 );

				p2_sub_coef0  |= ( (coef_sub_1_8 [0]&0xfff) << 16 );
				p2_sub_coef0  |= ( (coef_sub_1_8 [1]&0xfff) <<  0 );
				p2_sub_coef1  |= ( (coef_sub_1_8 [2]&0xfff) << 16 );
				p2_sub_coef1  |= ( (coef_sub_1_8 [3]&0xfff) <<  0 );

				p3_sub_coef0  |= ( (coef_sub_3_8 [0]&0xfff) << 16 );
				p3_sub_coef0  |= ( (coef_sub_3_8 [1]&0xfff) <<  0 );
				p3_sub_coef1  |= ( (coef_sub_3_8 [2]&0xfff) << 16 );
				p3_sub_coef1  |= ( (coef_sub_3_8 [3]&0xfff) <<  0 );

				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef00, p2_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef01, p2_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef02, p2_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef03, p2_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef04, p2_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef05, p2_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef00, p2_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef01, p2_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef02, p2_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef03, p2_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef04, p2_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef05, p2_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef00, p3_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef01, p3_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef02, p3_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef03, p3_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef04, p3_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef05, p3_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef00, p3_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef01, p3_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef02, p3_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef03, p3_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef04, p3_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef05, p3_sub_coef1 );

				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef00, p2_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef01, p2_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef02, p2_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef03, p2_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef04, p2_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef05, p2_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef00, p2_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef01, p2_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef02, p2_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef03, p2_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef04, p2_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef05, p2_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef00, p3_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef01, p3_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef02, p3_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef03, p3_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef04, p3_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef05, p3_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef00, p3_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef01, p3_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef02, p3_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef03, p3_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef04, p3_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef05, p3_sub_coef1 );

				p0_sub_coef0 |= ( (phase_off_2k_p0 &0x1  ) << 31 );
				p1_sub_coef0 |= ( (phase_off_2k_p1 &0x1  ) << 31 );
				p2_sub_coef0 |= ( (phase_off_2k_p2 &0x1  ) << 31 );
				p3_sub_coef0 |= ( (phase_off_2k_p3 &0x1  ) << 31 );

				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p0_h_coef00, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p0_h_coef01, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p0_v_coef00, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p0_v_coef01, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p1_h_coef00, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p1_h_coef01, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p1_v_coef00, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p1_v_coef01, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p2_h_coef00, p2_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p2_h_coef01, p2_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p2_v_coef00, p2_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p2_v_coef01, p2_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p3_h_coef00, p3_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p3_h_coef01, p3_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p3_v_coef00, p3_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p3_v_coef01, p3_sub_coef1 );
			}
			else
			{
				p0_main_coef0 |= ( (phase_off_4k_p0 &0x1  ) << 31 );
				p0_main_coef0 |= ( (coef_main_3_4[0]&0xfff) << 16 );
				p0_main_coef0 |= ( (coef_main_3_4[1]&0xfff) <<  0 );
				p0_main_coef1 |= ( (coef_main_3_4[2]&0xfff) << 16 );
				p0_main_coef1 |= ( (coef_main_3_4[3]&0xfff) <<  0 );
				p0_main_coef2 |= ( (coef_main_3_4[4]&0xfff) << 16 );
				p0_main_coef2 |= ( (coef_main_3_4[5]&0xfff) <<  0 );
				p0_main_coef3 |= ( (coef_main_3_4[6]&0xfff) << 16 );
				p0_main_coef3 |= ( (coef_main_3_4[7]&0xfff) <<  0 );

				p1_main_coef0 |= ( (phase_off_4k_p1 &0x1  ) << 31 );
				p1_main_coef0 |= ( (coef_main_1_4[0]&0xfff) << 16 );
				p1_main_coef0 |= ( (coef_main_1_4[1]&0xfff) <<  0 );
				p1_main_coef1 |= ( (coef_main_1_4[2]&0xfff) << 16 );
				p1_main_coef1 |= ( (coef_main_1_4[3]&0xfff) <<  0 );
				p1_main_coef2 |= ( (coef_main_1_4[4]&0xfff) << 16 );
				p1_main_coef2 |= ( (coef_main_1_4[5]&0xfff) <<  0 );
				p1_main_coef3 |= ( (coef_main_1_4[6]&0xfff) << 16 );
				p1_main_coef3 |= ( (coef_main_1_4[7]&0xfff) <<  0 );

				p0_sub_coef0  |= ( (coef_sub_3_4 [0]&0xfff) << 16 );
				p0_sub_coef0  |= ( (coef_sub_3_4 [1]&0xfff) <<  0 );
				p0_sub_coef1  |= ( (coef_sub_3_4 [2]&0xfff) << 16 );
				p0_sub_coef1  |= ( (coef_sub_3_4 [3]&0xfff) <<  0 );

				p1_sub_coef0  |= ( (coef_sub_1_4 [0]&0xfff) << 16 );
				p1_sub_coef0  |= ( (coef_sub_1_4 [1]&0xfff) <<  0 );
				p1_sub_coef1  |= ( (coef_sub_1_4 [2]&0xfff) << 16 );
				p1_sub_coef1  |= ( (coef_sub_1_4 [3]&0xfff) <<  0 );

				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_h_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p0_v_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_h_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p1_v_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_h_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p2_v_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_h_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_a_p3_v_coef05, p1_sub_coef1 );

				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_h_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p0_v_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_h_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p1_v_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef00, p0_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef01, p0_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef02, p0_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef03, p0_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef04, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_h_coef05, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p2_v_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_h_coef05, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef00, p1_main_coef0);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef01, p1_main_coef1);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef02, p1_main_coef2);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef03, p1_main_coef3);
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef04, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_y_p3_v_coef05, p1_sub_coef1 );

				p0_sub_coef0 |= ( (phase_off_4k_p0 &0x1  ) << 31 );
				p1_sub_coef0 |= ( (phase_off_4k_p1 &0x1  ) << 31 );

				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p0_h_coef00, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p0_h_coef01, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p0_v_coef00, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p0_v_coef01, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p1_h_coef00, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p1_h_coef01, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p1_v_coef00, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p1_v_coef01, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p2_h_coef00, p0_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p2_h_coef01, p0_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p2_v_coef00, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p2_v_coef01, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p3_h_coef00, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p3_h_coef01, p1_sub_coef1 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p3_v_coef00, p1_sub_coef0 );
				OSDX_E60_Wr(osdx_prep_img1, osd0_scaler_c_p3_v_coef01, p1_sub_coef1 );
			}

			// flush too many registers :(
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_h_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_h_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_h_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_h_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_v_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_v_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_v_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p0_v_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_h_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_h_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_h_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_h_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_v_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_v_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_v_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p1_v_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_h_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_h_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_h_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_h_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_v_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_v_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_v_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p2_v_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_h_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_h_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_h_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_h_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_v_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_v_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_v_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_a_p3_v_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_h_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_h_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_h_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_h_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_v_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_v_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_v_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p0_v_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_h_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_h_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_h_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_h_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_v_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_v_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_v_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p1_v_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_h_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_h_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_h_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_h_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_v_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_v_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_v_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p2_v_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_h_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_h_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_h_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_h_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_v_coef02);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_v_coef03);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_v_coef04);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_y_p3_v_coef05);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p0_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p0_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p0_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p0_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p1_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p1_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p1_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p1_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p2_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p2_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p2_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p2_v_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p3_h_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p3_h_coef01);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p3_v_coef00);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_scaler_c_p3_v_coef01);
		}
		break;

		case HWSETUP_IMG_SR_MERGE_BUF:
		{
			FBDEV_HW_NOTI("HWSETUP_IMG_SR_MERGE_BUF\n");

			OSDX_E60_Wr02(osdx_prep_img1, osd0_osd_sr_merge_buf_ctrl0, pic_y_width,   out_w/8, pic_y_height  , out_h);
			OSDX_E60_Wr02(osdx_prep_img1, osd0_osd_sr_merge_buf_ctrl1, pic_res_width, out_w/8, pic_res_height, out_h);

			OSDX_E60_WrFL(osdx_prep_img1, osd0_osd_sr_merge_buf_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_osd_sr_merge_buf_ctrl1);
		}
		break;

		case HWSETUP_IMG_POST_SCALER:
		{
			int guardband = 0;

			int split_h0_w = out_w/2 + guardband;
			int split_h1_w = out_w/2 + guardband;

			int scl_h0_inp_w = split_h0_w;
			int scl_h0_inp_h = out_h ;
			int scl_h1_inp_w = split_h1_w;
			int scl_h1_inp_h = out_h ;

			int scl_h0_out_w = scl_h0_inp_w;
			int scl_h0_out_h = scl_h0_inp_h;
			int scl_h1_out_w = scl_h1_inp_w;
			int scl_h1_out_h = scl_h1_inp_h;

			int crop_h0_inp_w = scl_h0_out_w;
			int crop_h0_inp_h = scl_h0_out_h;
			int crop_h1_inp_w = scl_h1_out_w;
			int crop_h1_inp_h = scl_h1_out_h;

			int crop_h0_hoffset = 0  ;
			int crop_h0_hactive = out_w/2;
			int crop_h0_voffset = 0  ;
			int crop_h0_vactive = out_h  ;

			int crop_h1_hoffset =  0  ;
			int crop_h1_hactive =  out_w/2;
			int crop_h1_voffset =  0  ;
			int crop_h1_vactive =  out_h  ;

			FBDEV_HW_NOTI("HWSETUP_IMG_POST_SCALER\n");

			// split-merge
			OSDX_E60_RdFL(osdx_prep_img1, osd0_sc_split_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_sc_split_ctrl1);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_sc_merge_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_sc_merge_ctrl1);
			// filter
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_v0_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_v0_ctrl1);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_v0_ctrl2);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_v1_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_v1_ctrl1);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_v1_ctrl2);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_h0_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_h0_ctrl1);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_h0_ctrl2);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_h1_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_h1_ctrl1);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_post_scaler_h1_ctrl2);
			// crop
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_v_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_v_ctrl1);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_v_ctrl2);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_h0_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_h0_ctrl1);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_h0_ctrl2);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_h1_ctrl0);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_h1_ctrl1);
			OSDX_E60_RdFL(osdx_prep_img1, osd0_crop_h1_ctrl2);

			// split-merge
			OSDX_E60_Wr05 (osdx_prep_img1, osd0_sc_split_ctrl0, reg_hsize, out_w, reg_sync_mode, 0, reg_split_mode, 0, reg_pmode_in, 3,reg_pmode_out, 2);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_sc_split_ctrl1, reg_guardband, guardband, reg_split_size, out_w/2);
			OSDX_E60_Wr05 (osdx_prep_img1, osd0_sc_merge_ctrl0, reg_hsize, out_w, reg_sync_mode, 0, reg_split_mode, 0, reg_pmode_in, 2,reg_pmode_out, 3);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_sc_merge_ctrl1, reg_guardband, guardband, reg_split_size, out_w/2);

			// filter
			OSDX_E60_Wr  (osdx_prep_img1, osd0_post_scaler_v0_ctrl0, 0x00020000);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_post_scaler_v0_ctrl1, post_scaler_v0_out_pic_height, out_h, post_scaler_v0_in_pic_height, out_h);
			OSDX_E60_Wr  (osdx_prep_img1, osd0_post_scaler_v0_ctrl2, 0x00000000);
			OSDX_E60_Wr  (osdx_prep_img1, osd0_post_scaler_v1_ctrl0, 0x00020000);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_post_scaler_v1_ctrl1, post_scaler_v1_out_pic_height, out_h, post_scaler_v1_in_pic_height, out_h);
			OSDX_E60_Wr  (osdx_prep_img1, osd0_post_scaler_v1_ctrl2, 0x00000000);

			OSDX_E60_Wr  (osdx_prep_img1, osd0_post_scaler_h0_ctrl0, 0x00020000);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_post_scaler_h0_ctrl1, post_scaler_h0_out_pic_width ,scl_h0_out_w, post_scaler_h0_in_pic_width ,scl_h0_inp_w);
			OSDX_E60_Wr  (osdx_prep_img1, osd0_post_scaler_h0_ctrl2, 0x00000000);
			OSDX_E60_Wr  (osdx_prep_img1, osd0_post_scaler_h1_ctrl0, 0x00020000);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_post_scaler_h1_ctrl1, post_scaler_h1_out_pic_width ,scl_h1_out_w, post_scaler_h1_in_pic_width ,scl_h1_inp_w);
			OSDX_E60_Wr  (osdx_prep_img1, osd0_post_scaler_h1_ctrl2,0x00000000);

			// crop
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_v_ctrl0, crop_in_pic_width, out_w, crop_in_pic_height, out_h);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_v_ctrl1, crop_voffset, 0, crop_vactive, out_h);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_v_ctrl2, crop_hoffset, 0, crop_hactive, out_w);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_h0_ctrl0, crop_in_pic_width, crop_h0_inp_w, crop_in_pic_height, crop_h0_inp_h);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_h0_ctrl1, crop_voffset, crop_h0_hoffset, crop_vactive, crop_h0_vactive);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_h0_ctrl2, crop_hoffset, crop_h0_voffset, crop_hactive, crop_h0_hactive);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_h1_ctrl0, crop_in_pic_width, crop_h1_inp_w, crop_in_pic_height, crop_h1_inp_h);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_h1_ctrl1, crop_voffset, crop_h1_hoffset, crop_vactive, crop_h1_vactive);
			OSDX_E60_Wr02 (osdx_prep_img1, osd0_crop_h1_ctrl2, crop_hoffset, crop_h1_voffset, crop_hactive, crop_h1_hactive);

			// split-merge
			OSDX_E60_WrFL(osdx_prep_img1, osd0_sc_split_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_sc_split_ctrl1);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_sc_merge_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_sc_merge_ctrl1);
			// filter
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_v0_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_v0_ctrl1);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_v0_ctrl2);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_v1_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_v1_ctrl1);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_v1_ctrl2);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_h0_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_h0_ctrl1);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_h0_ctrl2);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_h1_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_h1_ctrl1);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_post_scaler_h1_ctrl2);
			// crop
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_v_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_v_ctrl1);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_v_ctrl2);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_h0_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_h0_ctrl1);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_h0_ctrl2);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_h1_ctrl0);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_h1_ctrl1);
			OSDX_E60_WrFL(osdx_prep_img1, osd0_crop_h1_ctrl2);

		}
		break;

		case HWSETUP_IMG_PRE_TOP:
		{
			FBDEV_HW_NOTI("HWSETUP_IMG_PRE_TOP\n");
			/* do nothing */
		}
		break;

		case HWSETUP_IMG_POST_TOP:
		{
			FBDEV_HW_NOTI("HWSETUP_IMG_POST_TOP\n");
			/* do nothing. refer to HWSETUP_OSD_POST_TOP */
		}
		break;

		case HWSETUP_IMG_POST_CORE:
		{
			UINT32 sync_w = (sosd_mode) ? out_w: out_w/4; // osd_mode 0: B.OSD, 1: S.OSD
			UINT32 aa_detour_en = 1;
			UINT32 yy_detour_en = (sosd_mode)? 1:0;

			UINT32 ofs_x = 0;	// ??
			UINT32 ofs_y = 0;	// ??

			FBDEV_HW_NOTI("HWSETUP_IMG_POST_CORE\n");

			OSDX_E60_RdFL(osdx_post_img, osd0_img_path_ctrl);
			OSDX_E60_RdFL(osdx_post_img, osd0_img_sync_ctrl0);

			OSDX_E60_RdFL(osdx_post_img, osd0_img_sync_ctrl1);
			OSDX_E60_RdFL(osdx_post_est, osd1_est_sync_ctrl1);
			OSDX_E60_RdFL(osdx_post_csr, osd4_csr_sync_ctrl1);

			OSDX_E60_RdFL(osdx_post_img, osd0_shp_ctrl);
			OSDX_E60_RdFL(osdx_post_img, osd0_cdc_disp_size);
			OSDX_E60_RdFL(osdx_post_img, osd0_ccv_img_ctrl0);
			OSDX_E60_RdFL(osdx_post_img, osd0_ccv_img_ctrl1);
			OSDX_E60_RdFL(osdx_post_img, osd0_crop_ctrl0);
			OSDX_E60_RdFL(osdx_post_img, osd0_crop_ctrl1);
			OSDX_E60_RdFL(osdx_post_img, osd0_crop_ctrl2);

			OSDX_E60_Wr01(osdx_post_img, osd0_img_path_ctrl, osd_ctrl_direc, sosd_mode);

			/* raxis.lim (2020/03/20)
			 * mirror mode 에서의 orbit 정상 동작을 위하여 osd_sync_v_reverse 설정 필요
			 */
			/* (2020/12/15) remove the early osd_en control
			* osd will be enabled after the frist image update is completed
			* 특히 초기에 수행되는 osd(0) 에 대한 osd_en 과 sync_enable 을 동시에 제거 필요
			* see FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE handler
			* see http://clm.lge.com/issue/browse/SICDTV-9043
			* see http://hlm.lge.com/qi/browse/INQAISSUE-81
			*/
#if 0
			OSDX_E60_Wr03(osdx_post_img, osd0_img_sync_ctrl0, osd_sync_enable, 0x1, osd_line_init_pos, 0x1, osd_sync_v_reverse, mirror_mode);
#else
			OSDX_E60_Wr02(osdx_post_img, osd0_img_sync_ctrl0, osd_line_init_pos, 0x1, osd_sync_v_reverse, mirror_mode);
#endif

			OSDX_E60_Wr02(osdx_post_img, osd0_img_sync_ctrl1, osd_sync_disp_w, sync_w, osd_sync_disp_h, out_h);
			OSDX_E60_Wr02(osdx_post_est, osd1_est_sync_ctrl1, osd_sync_disp_w, sync_w, osd_sync_disp_h, out_h); // estream
			OSDX_E60_Wr02(osdx_post_csr, osd4_csr_sync_ctrl1, osd_sync_disp_w, sync_w, osd_sync_disp_h, out_h); // cursor

			OSDX_E60_Wr02(osdx_post_img, osd0_cdc_disp_size, osd_cdc_disp_w, out_w, osd_cdc_disp_h, out_h);

			/* raxis.lim (2020/03/13)
			 * 메뉴얼 버그 있으므로 주의할것, alpha = bit0, Y = bit1 임
			 * S.OSD 에서는 둘다 detour 토록 하며, B.OSD 에서는 alpha 만 detour 하도록 할것
			 * 이지훈s 에게 문의할것
			 */
			OSDX_E60_Wr02(osdx_post_img, osd0_shp_ctrl, osd_shp_aa_detour_en, aa_detour_en, osd_shp_yy_detour_en, yy_detour_en);

			OSDX_E60_Wr02(osdx_post_img, osd0_ccv_img_ctrl0, osd_img_xpos  , ofs_x, osd_img_ypos  , ofs_y);
			OSDX_E60_Wr02(osdx_post_img, osd0_ccv_img_ctrl1, osd_img_disp_w, out_w, osd_img_disp_h, out_h);

			OSDX_E60_Wr02(osdx_post_img, osd0_crop_ctrl0, reg_in_pic_width, out_w, reg_in_pic_height, out_h);
			OSDX_E60_Wr02(osdx_post_img, osd0_crop_ctrl1, hoffset, ofs_x, hactive, out_w);
			OSDX_E60_Wr02(osdx_post_img, osd0_crop_ctrl2, voffset, ofs_y, vactive, out_h);


			OSDX_E60_WrFL(osdx_post_img, osd0_img_path_ctrl);
			OSDX_E60_WrFL(osdx_post_img, osd0_img_sync_ctrl0);

			OSDX_E60_WrFL(osdx_post_img, osd0_img_sync_ctrl1);
			OSDX_E60_WrFL(osdx_post_est, osd1_est_sync_ctrl1);
			OSDX_E60_WrFL(osdx_post_csr, osd4_csr_sync_ctrl1);

			OSDX_E60_WrFL(osdx_post_img, osd0_shp_ctrl);
			OSDX_E60_WrFL(osdx_post_img, osd0_cdc_disp_size);
			OSDX_E60_WrFL(osdx_post_img, osd0_ccv_img_ctrl0);
			OSDX_E60_WrFL(osdx_post_img, osd0_ccv_img_ctrl1);
			OSDX_E60_WrFL(osdx_post_img, osd0_crop_ctrl0);
			OSDX_E60_WrFL(osdx_post_img, osd0_crop_ctrl1);
			OSDX_E60_WrFL(osdx_post_img, osd0_crop_ctrl2);

			// (2020/09/03) : add CSC control
			// E60+F20 에서는 불필요한 CSC 기능이 동작하면서 OSD 품질을 저하시키는 출력을 낼 수 있어 off 처리함
			// see http://clm.lge.com/issue/browse/SICDTV-8775
			//
			// E60, E60+F20 에서 OSD sharpness off 상태에서는 CSC 기능도 같이 꺼야 OSD 품질이 좀 더 좋아짐
			// 추후 완전한 개선 or OSD sharpness on 되기 전까지 아래 상태 (강제 off) 를 유지토록 함
			// http://clm.lge.com/issue/browse/SICDTV-8775?focusedCommentId=2577632&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2577632
			//
			// (note) 아래 설정값을 어디에 위치 시킬지 좀 애매하여, 일단 여기 한곳에 모음
			//
			// (2020/10/08) re-enable CSC control to support OSD sharpness
			// UI 품질 향상을 위한 필터 적용시 E60n+F20 에서는 4K OSD sharpness 가 적용되어야 함 (CSC enable 필요)
			// http://clm.lge.com/issue/browse/SICDTV-8781?focusedCommentId=2600195&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2600195
			//
			// E60n, E60n+F20 모두 On 설정을 유지토록 조치함. 최종 설정 근거 이유는 아래 참조
			// http://clm.lge.com/issue/browse/SICDTV-8781?focusedCommentId=2643402&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2643402
			//
			OSDX_E60_RdFL(osdx_prep_img0, osd0_csc_ctrl);
			OSDX_E60_Wr01(osdx_prep_img0, osd0_csc_ctrl, reg_rgb2yc_en, 1);//(sosd_mode)? 0:1);
			OSDX_E60_WrFL(osdx_prep_img0, osd0_csc_ctrl);

			OSDX_E60_RdFL(osdx_post_img, osd0_csc_ctrl0);
			OSDX_E60_Wr01(osdx_post_img, osd0_csc_ctrl0, reg_yc2rgb_csc_en, 1); //(sosd_mode)? 0:1);
			OSDX_E60_WrFL(osdx_post_img, osd0_csc_ctrl0);
		}
		break;

		case HWSETUP_EST_PRE_TOP:
		{
			FBDEV_HW_NOTI("HWSETUP_EST_PRE_TOP\n");
			/* do nothing */

			//OSDX_E60_Wr02(osdx_prep_est, osd1_ctrl_main, osd_bitmap_only_mode_en, comp_mode, osd_hdr_src_sel, 0x1 );
		}
		break;

		case HWSETUP_EST_POST_CORE:
		{
			//UINT32 sync_w = (sosd_mode) ? out_w: out_w/4; // osd_mode 0: B.OSD, 1: S.OSD

			UINT32 ofs_x = 0;	// ??
			UINT32 ofs_y = 0;	// ??
			UINT32 est_out_w = hw_ctx->hw_fb1_width;
			UINT32 est_out_h = hw_ctx->hw_fb1_height;

			UINT32 osd_en = 0;

			FBDEV_HW_NOTI("HWSETUP_EST_POST_CORE\n");

			if (est_out_w > 1920) est_out_w = 1920;
			if (est_out_h > 2160) est_out_h = 2160;

			OSDX_E60_RdFL(osdx_post_est, osd1_est_path_ctrl);
			OSDX_E60_RdFL(osdx_post_est, osd1_est_sync_ctrl0);
			OSDX_E60_RdFL(osdx_post_est, osd1_cdc_disp_size);
			OSDX_E60_RdFL(osdx_post_est, osd1_ccv_est_ctrl0);
			OSDX_E60_RdFL(osdx_post_est, osd1_ccv_est_ctrl1);

			OSDX_E60_Wr01(osdx_post_est, osd1_est_path_ctrl, osd_ctrl_direc, sosd_mode);
			OSDX_E60_Wr03(osdx_post_est, osd1_est_sync_ctrl0, osd_sync_enable, osd_en, osd_line_init_pos, 0x1, osd_sync_v_reverse, mirror_mode);
			OSDX_E60_Wr02(osdx_post_est, osd1_cdc_disp_size, osd_cdc_disp_w, est_out_w, osd_cdc_disp_h, est_out_h);
    		OSDX_E60_Wr02(osdx_post_est, osd1_ccv_est_ctrl0, osd_img_xpos  , ofs_x, osd_img_ypos  , ofs_y);
		    OSDX_E60_Wr02(osdx_post_est, osd1_ccv_est_ctrl1, osd_img_disp_w, est_out_w, osd_img_disp_h, est_out_h);

			OSDX_E60_WrFL(osdx_post_est, osd1_est_path_ctrl);
			OSDX_E60_WrFL(osdx_post_est, osd1_est_sync_ctrl0);
			OSDX_E60_WrFL(osdx_post_est, osd1_cdc_disp_size);
			OSDX_E60_WrFL(osdx_post_est, osd1_ccv_est_ctrl0);
			OSDX_E60_WrFL(osdx_post_est, osd1_ccv_est_ctrl1);
		}
		break;

		case HWSETUP_CSR_SCALER:
		{
			UINT32 scale_mode = 0;

			FBDEV_HW_NOTI("HWSETUP_CSR_SCALER\n");

			OSDX_E60_RdFL(osdx_prep_csr, osd4_scaler_ctrl);
			OSDX_E60_Wr02(osdx_prep_csr, osd4_scaler_ctrl, reg_crsr_h_x2_en, scale_mode, reg_crsr_v_x2_en, scale_mode);
			OSDX_E60_WrFL(osdx_prep_csr, osd4_scaler_ctrl);
		}
		break;

		case HWSETUP_CSR_POST_CORE:
		{
			//int fb_dev_id = LX_FBDEV_ID_OSD3;
			int	xidx = OSD_CTRL_XIDX_CRSR;

			UINT32 ofs_x = 0;
			UINT32 ofs_y = 0;
			UINT32 csr_w = hw_ctx->hw_fb3_width;
			UINT32 csr_h = hw_ctx->hw_fb3_height;

			UINT32 osd_en = 0;


			FBDEV_HW_NOTI("HWSETUP_CSR_POST_CORE\n");

			// read osd enable
			OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_main);
			OSDX_CTRL_E60_Rd01(xidx, osd_ctrl_main, osd_en,	osd_en);

			OSDX_E60_RdFL(osdx_post_csr, osd4_csr_ctrl_path);
			OSDX_E60_RdFL(osdx_post_csr, osd4_csr_sync_ctrl0);
			OSDX_E60_RdFL(osdx_post_csr, osd4_ccv_csr_ctrl0);
			OSDX_E60_RdFL(osdx_post_csr, osd4_ccv_csr_ctrl1);

			//UINT32 sync_w = (sosd_mode == 0) ? out_w/4 : out_w; // 0 : B.OSD, 1 : S.OSD/*{{{*/
			OSDX_E60_Wr01(osdx_post_csr, osd4_csr_ctrl_path , osd_ctrl_direc, sosd_mode);

			// raxis.lim (2020/03/20)
			// mirror mode 에서 커서의 좌표 이동 동작을 위하여 osd_sync_v_reverse 설정 필요
			OSDX_E60_Wr03(osdx_post_csr, osd4_csr_sync_ctrl0, osd_sync_enable, osd_en, osd_line_init_pos, 0x1, osd_sync_v_reverse, mirror_mode);

		TODO_NOTE("csr_w, csr_h 는 그렇다치고, x,y 바뀔때도 아래 설정해 주어야 할듯 싶은데? -> 그렇고 하고 있음.")
			OSDX_E60_Wr02(osdx_post_csr, osd4_ccv_csr_ctrl0 , osd_csr_xpos  , ofs_x, osd_csr_ypos  , ofs_y);
			OSDX_E60_Wr02(osdx_post_csr, osd4_ccv_csr_ctrl1 , osd_csr_disp_w, csr_w, osd_csr_disp_h, csr_h);

			OSDX_E60_WrFL(osdx_post_csr, osd4_csr_ctrl_path);
			OSDX_E60_WrFL(osdx_post_csr, osd4_csr_sync_ctrl0);
			OSDX_E60_WrFL(osdx_post_csr, osd4_ccv_csr_ctrl0);
			OSDX_E60_WrFL(osdx_post_csr, osd4_ccv_csr_ctrl1);
		}
		break;
	}
}

/** initialize HW SOC
 *
 *
 */
int	FBDEV_E60_CMN_InitHW ( void )
{
	UINT32 sosd_mode;
	UINT32 disp_width, disp_height;

	FBDEV_E60_HW_CTX_T*	hw_ctx = FBDEV_E60_GET_HW_CTX();
	/* if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration)  */
	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> user_initcall not ready +++\n");

	sosd_mode = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0:1;
	disp_width = hw_ctx->hw_disp_width;
	disp_height= hw_ctx->hw_disp_height;

	FBDEV_HW_DEBUG("(Re)Init OSD(E60) HW.. disp_size %dx%d\n", disp_width, disp_height);

	/* raxis.lim (2014/06/18)
	 * CCO init param is too difficult to understand :(
	 * ask woonghyun.kim if you have any question. he knows everything !!
	 *
	 * let's summarize all that I know
	 * CCO_CTRL_BASE+0x08 controls osd pluse source selections
	 * 0x5 : used for BLEND path (non-compressed)
	 * 0x7 : used for SEP path   (non-compressed)
	 */
	OSD_CCO1_TOP_E60_RdFL(ctrl_auto_init);
	OSD_CCO1_TOP_E60_RdFL(ctrl_dpath);
	OSD_CCO1_TOP_E60_RdFL(ctrl_spath);

	OSD_CCO2_TOP_E60_RdFL(ctrl_auto_init);
	OSD_CCO2_TOP_E60_RdFL(ctrl_dpath);
	OSD_CCO2_TOP_E60_RdFL(ctrl_spath);

	TODO_NOTE("osd_sync_gen_ctrl 이 사용되는 경우는 2K->2K, 2K->4K, 4K->4K 인 경우로 판단됨")
	if(sosd_mode)
	{
		OSD_CCO1_TOP_E60_Wr(ctrl_auto_init, 0x76772777);
		OSD_CCO1_TOP_E60_Wr(ctrl_spath, 	0x00000000);

		OSD_CCO2_TOP_E60_Wr(ctrl_auto_init, 0x76472277);
		OSD_CCO2_TOP_E60_Wr(ctrl_spath, 	0x00380D80);

		FBDEV_HW_NOTI("+ use default osd_sync_gen_ctrl (S.OSD)..\n");
	}
	else
	{
		OSD_CCO1_TOP_E60_Wr(ctrl_auto_init, 0x76772777);
		OSD_CCO1_TOP_E60_Wr(ctrl_spath, 	0x00000000);

		OSD_CCO2_TOP_E60_Wr(ctrl_auto_init, 0x76472277);
		OSD_CCO2_TOP_E60_Wr(ctrl_spath, 	0x00380D80);

		FBDEV_HW_NOTI("+ use default osd_sync_gen_ctrl (B.OSD)..\n");
	}

	/* raxis.lim (2016/03/28) -- ctrl_intr_pulse, ctrl_dpath, ctrl_spath is set by HW default value
	 * raxis.lim (2016/10/05) -- keep AFBC status becuase boot loader can display AFBC logo image
	 * raxis.lim (2019/08/06) -- DO NOT full value to ctrl_dpath. refer to http://clm.lge.com/issue/browse/AVTASK-386?focusedCommentId=1964037&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-1964037
	 * raxis.lim (2019/10/15) -- setup fb(1) based on hw_ctx->b_support_ext_render
	 */

#if 1
	if(FBDEV_E60_CMN_GetHWStatus(FBDEV_E60_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0))
	{
		OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd0_afbc_en, 0x1);
		OSD_CCO2_TOP_E60_Wr01(ctrl_dpath, osd0_afbc_en, 0x1);
	}
	else
	{
		OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd0_afbc_en, 0x0);
		OSD_CCO2_TOP_E60_Wr01(ctrl_dpath, osd0_afbc_en, 0x0);
	}

	if(FBDEV_E60_CMN_GetHWStatus(FBDEV_E60_HW_STATUS_AFBC, LX_FBDEV_ID_OSD1) &&
	   hw_ctx->b_support_ext_render == FALSE)
	{
		OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd1_afbc_en, 0x1);
		OSD_CCO2_TOP_E60_Wr01(ctrl_dpath, osd1_afbc_en, 0x1);
	}
	else
	{
		OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd1_afbc_en, 0x0);
		OSD_CCO2_TOP_E60_Wr01(ctrl_dpath, osd1_afbc_en, 0x0);
	}
#endif

	OSD_CCO1_TOP_E60_WrFL(ctrl_auto_init);
	OSD_CCO1_TOP_E60_WrFL(ctrl_dpath);
	OSD_CCO1_TOP_E60_WrFL(ctrl_spath);

	OSD_CCO2_TOP_E60_WrFL(ctrl_auto_init);
	OSD_CCO2_TOP_E60_WrFL(ctrl_dpath);
	OSD_CCO2_TOP_E60_WrFL(ctrl_spath);

	if(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		/* do nothing. not implemented */
	}
	else
	{
		/* do nothing. not implemented */
	}

 	if (FBDEV_E60_CMN_IsUHDDispMode())
	{
		FBDEV_NOTI("++ UHD mode : pic_init_timer config\n");

		/* raxis.lim (2019/05/23)
	 	 * OSD_IMAGE1 (E-Stremaer) 에서는 pic_init 0 값 설정 중요함. (SICDTV-6809 참조)
		 * 만약 0xa000 값을 사용하게 되면, E-Streamer OSD 의 오프셋이 틀어지거나, OSD 가 흐름.
		 *
		 * 결론은 use the default configuration 0x7000_0000
		 */

		// raxis.lim (2019/12/14) 과거 코드 삭제함. 필요하지 않을듯
	}
	else
	{
		FBDEV_NOTI("++ non-UHD mode : pic_init_timer config (not tested yet)\n");

		// raxis.lim (2019/12/14) 과거 코드 삭제함. 필요하지 않을듯
	}

    FBDEV_E60_CMN_SetupHWFunc(HWSETUP_OSD_SYNC, 0x0, NULL);
    FBDEV_E60_CMN_SetupHWFunc(HWSETUP_OSD_MIF, 0x0, NULL);

	FBDEV_E60_CMN_SetupHWFunc(HWSETUP_OSD_PREP_TOP, 0x0, NULL);
	FBDEV_E60_CMN_SetupHWFunc(HWSETUP_OSD_POST_TOP, 0x0, NULL);
	FBDEV_E60_CMN_SetupHWFunc(HWSETUP_OSD_MIXER, 0x0, NULL);

#ifdef FBDEV_USE_MIXER_MUX
	// E60 has the fixed mux value. DO NOT change
	{
		UINT32 mux_val = 0x76543210;
		FBDEV_NOTI("(Re)Init OSD(E60) mixer mux order = 0x%08x\n", mixer_mux_value );

		OSDX_E60_Wr(osdx_bosd_mixer, osd_mixer_mux1, mux_val);
		OSDX_E60_WrFL(osdx_bosd_mixer, osd_mixer_mux1);

		OSDX_E60_Wr(osdx_sosd_mixer, osd_mixer_mux1, mux_val);
		OSDX_E60_WrFL(osdx_sosd_mixer, osd_mixer_mux1);
	}
#endif

	// enable OSD_SR only when OSD is scaled to UHD size
	FBDEV_E60_CMN_SetupSRScaler(FBDEV_E60_CMN_IsUHDDispMode()? TRUE:FALSE, TRUE);

	// setup mirror, FBC etc. add more setup here if necessary...
	FBDEV_E60_CMN_InitMirrorEnv();
	FBDEV_E60_CMN_InitFBCEnv();

	return RET_OK;
}

/** make OSD to be initial state (make the basic configuration for each OSD layer)
 *
 */
int FBDEV_E60_CMN_InitOSDLayer ( int fb_dev_id )
{
	int	i;
	int	xidx;
	int xnum, xlst[2];
	int ret = RET_ERROR;
	FBDEV_E60_HW_CTX_T*	hw_ctx = FBDEV_E60_GET_HW_CTX();

	UINT32  hdr_src_sel;
	UINT32  osd_memhdr_addr;
	BOOLEAN	osd_en = 0x0;			/* off by default */
	BOOLEAN	hdr_rdy_flag = 0x0;		/* OFF by default */

	/* if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration)  */
	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> fb(%d) user_initcall not ready +++\n", fb_dev_id);

	/* fetch the current output disp size */
	//UINT32	disp_width = hw_ctx->hw_disp_width;
	//UINT32	disp_height= hw_ctx->hw_disp_height;

	FBDEV_HW_NOTI("fb(%d) configure osd layer\n", fb_dev_id);

	xnum = FBDEV_E60_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id );

	/* hdr_src_sel 0x0: DDR, 0x1: REG */
	hdr_src_sel	= (g_fbdev_hwio_cfg->hdr_op_method == FBDEV_HDR_OP_MMIO)? 0x0: 0x1;
	osd_memhdr_addr = (gMemCfgFBHdr[fb_dev_id].mem_header_base);

	/* choose the initial osd visibility based on boot logo configuration */
	switch(fb_dev_id)
	{
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==0)
		case LX_FBDEV_ID_OSD0:	osd_en = 0x1; break;
#endif
		default:				osd_en = 0x0; break;
	}
#ifdef FBDEV_E60_USE_HDR_RDY_REG
	hdr_rdy_flag = 0x1;
#endif

	for (i=0; i<xnum; i++)
	{
		UINT32 paramex[4];

		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), goto func_exit, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

		paramex[0] = osd_en;
		FBDEV_E60_CMN_SetupHWFunc(HWSETUP_OSD_LAYER, xidx, paramex);

		switch(xidx)
		{
			case OSD_CTRL_XIDX_IMG:		FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG_LOADER, 0x0, NULL); break;
			case OSD_CTRL_XIDX_IMG1:	FBDEV_E60_CMN_SetupHWFunc(HWSETUP_IMG1_LOADER, 0x0, NULL); break;
			case OSD_CTRL_XIDX_EST:		FBDEV_E60_CMN_SetupHWFunc(HWSETUP_EST_LOADER, 0x0, NULL); break;
			case OSD_CTRL_XIDX_CRSR:	FBDEV_E60_CMN_SetupHWFunc(HWSETUP_CSR_LOADER, 0x0, NULL); break;
			default:					/* do nothing */ break;
		}

TODO_NOTE("기존 삭제된 코드는 git 이력에서 찾아보고, 필요시 누락된 코드 반영토록 할것")
	}

    ret = RET_OK;   /* all work done */
func_exit:
	return ret;
}

static void FBDEV_E60_CMN_SafeSyncEnable(void)
{
	FBDEV_NOTI("++ PIC_INIT ++ (I-BOOT)\n");

	/* raxis.lim (2019/08/07) -- DO NOT full value to pic_init.
	 * refer to http://clm.lge.com/issue/browse/AVTASK-386?focusedCommentId=1964037&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-1964037
	 */
	FBDEV_E60_CMN_SetupHWFunc(HWSETUP_PIC_INIT, 0x0, NULL);
}

static void FBDEV_E60_CMN_ReInitHW (void)
{
	FBDEV_E60_HW_CTX_T*	hw_ctx = FBDEV_E60_GET_HW_CTX();

	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");

	FBDEV_E60_InitHW();
	FBDEV_SetInterruptEnable(MIXER_INTR,1);

	/* E60 OSD supports only OSD0, OSD1 & OSD3 */
	FBDEV_E60_InitOSDLayer(LX_FBDEV_ID_OSD0);
	FBDEV_E60_InitOSDLayer(LX_FBDEV_ID_OSD1);
	FBDEV_E60_InitOSDLayer(LX_FBDEV_ID_OSD3);

    /* refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT */
    if (hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)
    {
		FBDEV_E60_CMN_SafeSyncEnable();
    }
}

int	FBDEV_E60_CMN_ExecHWCommand	(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data)
{
	int	ret = RET_NOT_SUPPORTED;
	FBDEV_E60_HW_CTX_T*	hw_ctx = FBDEV_E60_GET_HW_CTX();

	switch(cmd)
	{
		case FBDEV_HW_CMD_IO_POST_HW_INIT:
		{
#ifdef FBDEV_E60_USE_DEFAULT_CMM_INIT
			extern void FBDEV_E60_SetDefaultCmmConfig(void);

			FBDEV_HW_NOTI("+ do post HW init...\n");
			FBDEV_E60_SetDefaultCmmConfig();
#endif

			fbdev_e60_wq = alloc_workqueue("fbdev_e60_events", 0, 0);

			if (fbdev_enable_logo_clear)
			{
				FBDEV_NOTI("start logo clear work after %dms (boot mode)\n", fbdev_boot_logo_clear_timeout);
				queue_delayed_work(fbdev_e60_wq, &boot_logo_clear_work, msecs_to_jiffies(fbdev_boot_logo_clear_timeout));
			}
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_IO_POSD_OPEN:
		{
			int fbdev_id = data->gen[0];
			struct fb_info* fbinfo = (struct fb_info*)data->genex[0];

			FBDEV_HW_DEBUG("fb(%d) POSD_OPEN..\n", fbdev_id);
			FBDEV_E60_CMN_RunBootLogoTimer(fbdev_boot_freeze_timeout, FALSE);

			FBDEV_E60_CMN_OpenExternalRenderer(fbdev_id, fbinfo);

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
				FBDEV_NOTI("PAUSE_PQEFW_OSD0_OUT_CTRL enabled\n");
				hw_ctx->hw_wa_flag |= FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL;
			}
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_IO_VSYNC:
		{
			FBDEV_E60_CMN_ISRHook();
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_RD_VSYNC_CLK:
		{
			/* raxis.lim (2019/11/21)
			 *
			 * I should check if S.OSD is active becuase S.OSD is set to fixed 60Hz display
			 * regardless of OVI check value.
			 * remember that I can call FBDEV_E60_CMN_DetectVSyncClk() only when B.OSD is active.
			 */
			if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
			{
				data->gen[0] = FBDEV_E60_CMN_DetectVSyncClk();
			}
			else /* S.OSD */
			{
				data->gen[0] = FBDEV_VSYNC_CLK_60HZ;
			}
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

		case FBDEV_HW_CMD_RD_POSD_MAX_RES_CAPS:
		{
			int fbdev_id = data->gen[0];

			if (fbdev_id==LX_FBDEV_ID_OSD0)
			{
				data->gen[0]=LX_MAKE_RES(hw_ctx->hw_fb0_width, hw_ctx->hw_fb0_height);
				data->gen[1]=2; /*afbc*/
				data->gen[2]=0; /*system default*/
			}
			else if (fbdev_id==LX_FBDEV_ID_OSD1)
			{
				data->gen[0]=LX_MAKE_RES(hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height);
				data->gen[1]=(hw_ctx->b_support_ext_render)? 1/*argb*/ : 2/*afbc*/;
				data->gen[2]=(hw_ctx->b_support_ext_render)? FBDEV_E60_EXT_RENDER_EGL_FBDEV_NUM : 0 /*system default*/;

                /* raxis.lim (2019/12/27)
                 * if 4KOSD is enabled, all AFBC is used for fb(0), so fb(1) should always use ARGB format.
                 */
                if(hw_ctx->b_support_4kosd)
                {
                    data->gen[1] = 1; /*ARGB fixed*/
                }

                /* raxis.lim (2019/12/27)
                 * if fb(1) is disabled by user or debug, notify fbdev common kdriver not to make any surface
                 * see FBDEV_InitCfg() at fbdev_cfg.c
                 */
                if(!hw_ctx->b_support_fb1)
                {
                    data->gen[0]=0x0;
                    data->gen[1]=0x0;
                    data->gen[2]=0x0;
                }
			}
			else if (fbdev_id==LX_FBDEV_ID_OSD3)
			{
				data->gen[0]=LX_MAKE_RES(hw_ctx->hw_fb3_width, hw_ctx->hw_fb3_height);
				data->gen[1]=1; /*argb*/
				data->gen[2]=0; /*system default*/
			}
			else
			{
				data->gen[0]=0x0;
				data->gen[1]=0x0;
				data->gen[2]=0x0;
			}

			if(data->gen[0] != 0x0) ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_RD_AFBC_CAPS:
		{
			data->gen[0] = FBDEV_HW_AFBC_VER_1_0;
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_FREEZE:
		{
			/* raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL. ORBIT control will be re-enabled at THAW & RESTORE */
			hw_ctx->hw_wa_flag &= ~FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL;
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_SUSPEND:
		{
			fbdev_hw_pm_suspend_stage = 1;

			// (2020/11/26) see http://clm.lge.com/issue/browse/SICDTV-9009
			if(fbdev_use_shutdown_path_on_suspend)
			{
				FBDEV_E60_CMN_ShutdownOSDPath();
			}

			/* raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL to re-enable at FBDEV_E60_CMN_EnableOSDHdrFlush() during RESUME */
			hw_ctx->hw_wa_flag &= ~FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL;

			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_THAW:
		{
			/* raxis.lim (2017/09/18) -- enable PQEFW_OSD0_OUT_CTRL here becuase THAW stage doesn't configure any HW registers */
			hw_ctx->hw_wa_flag |= FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL;
			FBDEV_NOTI("OSD0_PQEFW_OSD0_OUT_CTRL enabled\n");
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_RESTORE:
		{
			fbdev_hw_pm_restore_stage = 1;

			/* boot logo migration is also required during snapshot boot */
			fbdev_logo_migration_required = TRUE;
			FBDEV_E60_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_KEEP);

			if (fbdev_enable_logo_clear)
			{
				FBDEV_NOTI("start logo clear work after %dms (resume mode)\n", fbdev_resume_logo_clear_timeout);
				queue_delayed_work(fbdev_e60_wq, &boot_logo_clear_work, msecs_to_jiffies(fbdev_resume_logo_clear_timeout));
			}

			/* (2010/06/11) re-activate lazy-init at snapshot boot */
			hw_ctx->user_initcall_ctrl.ready = FALSE;
			hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

			/* (2020/09/18, SICDTV-8751) reset osd_shp_auto_ctrl */
			hw_ctx->osd_shp_auto_cfg_ctrl.hwparam.osd_res = 0;

			/* raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute. it will be enabled at FBDEV_E60_CMN_EnableOSDHdrFlush() */

			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_RESUME:
		{
			/* raxis.lim (2017/08/22) -- fix for async behavior of OSD0_SYNC group */
			hw_ctx->hw_wa_flag |= FBDEV_E60_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
			FBDEV_NOTI("OSD0_SYNC_ASYNC_WR enabled\n");

			/* (2010/06/11) re-activate lazy-init at QSM+ resume */
			hw_ctx->user_initcall_ctrl.ready = FALSE;
			hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

			/* (2020/09/18, SICDTV-8751) reset osd_shp_auto_ctrl */
			hw_ctx->osd_shp_auto_cfg_ctrl.hwparam.osd_res = 0;

			/* raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute. it will be enabled at FBDEV_E60_CMN_EnableOSDHdrFlush() */
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_COMPLETE:
		{
			fbdev_hw_pm_suspend_stage = 0;
			fbdev_hw_pm_restore_stage = 0;

			hw_ctx->hw_wa_flag &= ~FBDEV_E60_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;

			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_USER_INITCALL_PREPARE:
		{
			int  fbdev_id = data->gen[0];

			FBDEV_NOTI("fb(%d) INITCALL_PREPARE\n", fbdev_id);

			/* raxis.lim (2010/06/11) -- (re)initialize OSD HW at user frame update not at kdriver initialization !! */
			if (fbdev_id==LX_FBDEV_ID_OSD0)
			{
				hw_ctx->user_initcall_ctrl.ready = TRUE;
				FBDEV_E60_CMN_ReInitHW();
			}
			ret = RET_OK;
		}
		break;

		// USER_INITCALL_COMPLETE 는 모든 OSD 설정의 완료를 의미하므로, 반드시 PQE FW 쪽으로 제어권을 넘겨야 한다.
		// 즉 FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL 플래그 설정이 가장 중요
		case FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE:
		{
			int	i;
			int fbdev_id = data->gen[0];

			FBDEV_NOTI("fb(%d) INITCALL_COMPLETE\n", fbdev_id);

		    /* (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume */
			if (fbdev_id==LX_FBDEV_ID_OSD0)
			{
				UINT64 base_tick;
				FBDEV_E60_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

				if (hw_ctx->b_support_ext_frc)
				{
					fbdev_pqefw_osd0_out_ctrl = 0;
					hw_ctx->hw_wa_flag &= ~FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL;
					FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL disabled\n");
				}
				else
				{
					hw_ctx->hw_wa_flag |= FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL;
					FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
				}

				hw_ctx->user_initcall_ctrl.status.osd_init_done= 1;
				hw_ctx->user_initcall_ctrl.status.osd_v_mirror = (mirror_ctrl->status==FBDEV_E60_V_MIRROR_ON)? 1:0;
				hw_ctx->user_initcall_ctrl.status.osd_estreamer= 0;

				FBDEV_E60_CMN_NotifyToPQEDriver();

				base_tick = OS_GetMsecTicks();
				for (i=0; i<10; i++)
				{
					// if (FW done) break;
					FBDEV_CHECK_NOTI( (int)(OS_GetMsecTicks()-base_tick) > 100 /*100ms*/,
						break, "+ wait timeout\n");

					if(RET_OK==FBDEV_E60_CMN_WaitForPQEDriverInitialization()) break;
					msleep_interruptible(10);
				}

				FBDEV_E60_CMN_SetOSDEnable(fbdev_id, TRUE);
			}
		}
		break;

		case FBDEV_HW_CMD_RD_EXTERNAL_RENDERER_INFO:
		{
			if(hw_ctx->b_support_ext_render)
			{
				data->gen[0] = LX_FBDEV_ID_OSD1;
			}
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_CONFIGURE_CROP_REGION:
		{
			int  fbdev_id = data->gen[0];
			int cx = LX_RES_GET_WIDTH(data->gen[1]);
			int cy = LX_RES_GET_HEIGHT(data->gen[1]);
			int cw = LX_RES_GET_WIDTH(data->gen[2]);
			int ch = LX_RES_GET_HEIGHT(data->gen[2]);

			FBDEV_E60_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_E60_GET_EXT_RENDER_CTRL(hw_ctx);

			FBDEV_CHECK_CODE(fbdev_id != LX_FBDEV_ID_OSD1, break, "fb(%d) ext_renderer not supported\n", fbdev_id);
			FBDEV_CHECK_CODE(hw_ctx->b_support_ext_render == FALSE,  break, "fb(%d) ext_renderer not supported\n", fbdev_id);

			ext_render_ctrl->hwparam.crop_x	= cx;
			ext_render_ctrl->hwparam.crop_y	= cy;
			ext_render_ctrl->hwparam.crop_w	= cw;
			ext_render_ctrl->hwparam.crop_h	= ch;

			FBDEV_HW_NOTI("++ configure external renderer crop %d,%d,%d,%d\n", cx, cy, cw, ch);
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE:
		{
			int	   fbdev_id	= data->gen[0];
			UINT32 phys_y 	= data->gen[1];
			int    xoffset	= data->gen[2];
			int    yoffset	= data->gen[3];

			FBDEV_E60_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_E60_GET_EXT_RENDER_CTRL(hw_ctx);
			FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(fbdev_id);

			FBDEV_CHECK_CODE(fbdev_id != LX_FBDEV_ID_OSD1, break, "fb(%d) ext_renderer not supported\n", fbdev_id);
			FBDEV_CHECK_CODE(hw_ctx->b_support_ext_render == FALSE,  break, "fb(%d) ext_renderer not supported\n", fbdev_id);
			FBDEV_CHECK_CODE(!wctx, break, "fb(%d) invalid wctx\n", fbdev_id);

			/* DEBUG ONLY - if user defined xoffset is set, force the fixed xoffset */
			if(hw_ctx->hw_ext_render_debug_xoffset>0)
			{
				xoffset = hw_ctx->hw_ext_render_debug_xoffset;
			}

			// (2020/09/04)
			// add yofffset see http://hlm.lge.com/issue/browse/WEBOSHWBS-429
			ext_render_ctrl->hwparam.phys_y	= phys_y;
			ext_render_ctrl->hwparam.size	= (hw_ctx->hw_ext_render_width <<16) | (hw_ctx->hw_ext_render_height);
			ext_render_ctrl->hwparam.xoffset= xoffset;
			ext_render_ctrl->hwparam.yoffset= yoffset;

			// (2019/09/27)
			// if PQE path mode, make screen update interval slow up to maximum 15Hz
			if (hw_ctx->hw_ext_render_output_path & FB_E60_EXT_RENDER_PQE_PATH)
			{
				UINT64 sleep_tick_us= 0;
				UINT64 curr_tick_us = OS_GetUsecTicks();
				UINT64 diff_tick_us = curr_tick_us - ext_render_ctrl->swsync.request_tick_us;

				if (diff_tick_us < ext_render_ctrl->swsync.interval_tick_us)
				{
					sleep_tick_us = ext_render_ctrl->swsync.interval_tick_us - diff_tick_us;
					//FBDEV_HW_NOTI("++ usleep %d us\n", (int)sleep_tick_us);
					usleep_range(sleep_tick_us, sleep_tick_us);
				}

				OS_RdReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x0c, &ext_render_ctrl->hwparam.tx_count);

				FBDEV_HW_NOTI("++ (1) write external renderer y:0x%08x sz:0x%08x cmd:0x%08x crop:%d,%d,%d,%d (xoff:%d, yoff:%d, en:%d) - sleep: %dus tx_count: %d\n",
					ext_render_ctrl->hwparam.phys_y,
					ext_render_ctrl->hwparam.size,
					ext_render_ctrl->hwparam.command,
					ext_render_ctrl->hwparam.crop_x,
					ext_render_ctrl->hwparam.crop_y,
					ext_render_ctrl->hwparam.crop_w,
					ext_render_ctrl->hwparam.crop_h,
					ext_render_ctrl->hwparam.xoffset,
					ext_render_ctrl->hwparam.yoffset,
					ext_render_ctrl->hwparam.enable,
					(int)sleep_tick_us,
					ext_render_ctrl->hwparam.tx_count);
			}

            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x00, ext_render_ctrl->hwparam.phys_y);
            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x04, ext_render_ctrl->hwparam.size);
            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x10, ext_render_ctrl->hwparam.crop_xy);
            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x14, ext_render_ctrl->hwparam.crop_wh);
            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x08, ext_render_ctrl->hwparam.command);

			// (2020/08/04)
			// route E-streamer image to OSD path. F20 FW will reads OSD data as VIDEO data. see SICDTV-8669
			// http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2527527&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2527527
			//
			// (2020/08/11)
			// you can display fb(1) frame onto EST layer for debug purpose
			if ((hw_ctx->hw_ext_render_output_path & FB_E60_EXT_RENDER_OSD_PATH)/* normal case */
				|| hw_ctx->hw_ext_render_debug_osd_output) 						/* debug case */
			{
				UINT32 pqe_tick[3];
				struct scanvas	canvas;
				UINT32 image_size = hw_ctx->hw_ext_render_width * hw_ctx->hw_ext_render_height * hw_ctx->hw_ext_render_bpp;

				pqe_tick[0] = OS_GetUsecTicks();

				// http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2526545&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2526545
				FBDEV_E60_CMN_WaitForVsync(3);

				memcpy(&canvas, &wctx->pixel, sizeof(canvas));

				if(hw_ctx->hw_ext_render_debug_osd_output)
				{
					phys_y = canvas.osd_bm_paddr;
				}

				canvas.input_win.x = 0;
				canvas.input_win.y = 0;
				canvas.input_win.w = hw_ctx->hw_ext_render_width;
				canvas.input_win.h = hw_ctx->hw_ext_render_height/2;
				canvas.output_win.x = 0;
				canvas.output_win.y = 0;
				canvas.output_win.w = hw_ctx->hw_ext_render_width;
				canvas.output_win.h = hw_ctx->hw_ext_render_height/2;
				canvas.fbc_fmt 		= LX_FBDEV_FBC_FORMAT_RAW;

				canvas.osd_bm_paddr= phys_y;

				pqe_tick[1] = OS_GetUsecTicks();
				FBDEV_HW_NOTI("++ (2-1) write externl render to OSD output path (top=0x%08x, %dx%d) diff_tm=%d us\n",
					canvas.osd_bm_paddr, canvas.input_win.w, canvas.input_win.h,
					(int)(pqe_tick[1]-pqe_tick[0]));

				FBDEV_E60_CMN_WriteOSDHeader(&canvas);

				// http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2526545&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2526545
				FBDEV_E60_CMN_WaitForVsync(1);

				canvas.osd_bm_paddr= phys_y + (image_size>>1);
				FBDEV_E60_CMN_WriteOSDHeader(&canvas);

				pqe_tick[2] = OS_GetUsecTicks();
				FBDEV_HW_NOTI("++ (2-2) write externl render to OSD output path (bot=0x%08x, %dx%d) diff_tm=%d us\n",
					canvas.osd_bm_paddr, canvas.input_win.w, canvas.input_win.h,
					(int)(pqe_tick[2]-pqe_tick[1]));
			}

			ext_render_ctrl->swsync.request_tick_us = OS_GetUsecTicks();
			ret = RET_OK;
		}
		break;

		// see http://clm.lge.com/issue/browse/SICDTV-8781?focusedCommentId=2605561&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2605561
		case FBDEV_HW_CMD_WR_OSD_SHP_AUTO_CONFIG:
		{
			int	   fbdev_id	= data->gen[0];
			UINT32 osd_res = data->gen[1];

			FBDEV_E60_OSD_SHP_AUTO_CFG_CTRL_T* osd_shp_auto_cfg_ctrl = FBDEV_E60_GET_OSD_SHP_AUTO_CFG_CTRL(hw_ctx);

			// note osd_shp_auto_cfg is only valid after PQE FW init
			FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, break, "<i> fb(%d) user_initcall not ready +++\n", fbdev_id);

			// osd_shp_auto_cfg value is transfered only when value is changed to prevent unnecessary transmission overhead
			if (osd_shp_auto_cfg_ctrl->hwparam.osd_res != osd_res)
			{
				FBDEV_NOTI("++ configure auto osd sharpness. fb(%d) res=%d\n", fbdev_id, osd_res);

				osd_shp_auto_cfg_ctrl->hwparam.osd_res = osd_res;
				OS_WrReg(FBDEV_OS0_SHP_AUTO_CFG_REG_BASE+0x00, osd_shp_auto_cfg_ctrl->hwparam.command);
			}
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
/** setup external renderer if necessary
 *
 */
static void FBDEV_E60_CMN_OpenExternalRenderer(int fb_dev_id, struct fb_info* fbinfo)
{
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_E60_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_E60_GET_EXT_RENDER_CTRL(hw_ctx);

	if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_render == TRUE)
	{
		/* raxis.lim (2019/09/27) external framebuffers are NEVER freed !!!!!
		 *
		 * temporary allocation policy is as following:
	 	 * (1) try to alloc from "dpb"
		 * (2) if failed, try to alloc from "photofb"
		 *
		 * in near future, I will move memory pool from vdec to surface
		 */
		if(ext_render_ctrl->fbmem_phys[0]==0x0)
		{
			int fbmem_sz = hw_ctx->hw_ext_render_width * hw_ctx->hw_ext_render_height * hw_ctx->hw_ext_render_bpp;

			if(hw_ctx->b_ext_fb1_renderer_test_mode)	/* test mode alloc fbmem from photofb */
			{
				ext_render_ctrl->fbmem_phys[0] = (UINT32)hma_alloc("photofb", fbmem_sz*2, PAGE_SIZE);
			}
			else /* official mode alloc fbmem from surface */
			{
				ext_render_ctrl->fbmem_phys[0] = (UINT32)hma_alloc("surface", fbmem_sz*2, PAGE_SIZE);
			}

			FBDEV_CHECK_CODE(ext_render_ctrl->fbmem_phys==0x0, return, "can't alloc external render fbmem\n");

			ext_render_ctrl->fbmem_phys[1] = ext_render_ctrl->fbmem_phys[0] + fbmem_sz;
		}

		ext_render_ctrl->swsync.interval_tick_us = 1000000/hw_ctx->hw_ext_render_swsync_hz;

		ext_render_ctrl->hwparam.crop_x = 0;
		ext_render_ctrl->hwparam.crop_y = 0;
		ext_render_ctrl->hwparam.crop_w = hw_ctx->hw_ext_render_width;
		ext_render_ctrl->hwparam.crop_h = hw_ctx->hw_ext_render_height;


		FBDEV_NOTI("fb(%d) setup external fbmem=0x%08x,0x%08x sz=%dx%d swsync=%dus, ext_frc=%d, output=0x%x\n", fb_dev_id,
			ext_render_ctrl->fbmem_phys[0], ext_render_ctrl->fbmem_phys[1],
			hw_ctx->hw_ext_render_width, hw_ctx->hw_ext_render_height,
			(int)ext_render_ctrl->swsync.interval_tick_us,
			hw_ctx->b_support_ext_frc,
			hw_ctx->hw_ext_render_output_path);

		/* raxis.lim (2019/09/27)
		 * remember that struct fb_info* is passed via fbdev_open().
		 * by modifying fb_info, application can query the latest value with FBIOGET_VSCREENINFO ioctl.
		 *
		 * rsvd[0] : first framebuffer of ext. renderer
		 * rsvd[1] : second framebuffer of ext. renderer
		 * rsvd[2] : size information of ext. renderer
		 *
		 * (2020/08/14)
		 * rsvd[3] : byte ordering method (0: O208K,E60 only  1: E60+F20)
		 *           remember that byte ordering method is almost same as bpp info NOT output path
		 */
		fbinfo->var.reserved[0] = ext_render_ctrl->fbmem_phys[0];
		fbinfo->var.reserved[1] = ext_render_ctrl->fbmem_phys[1];
		fbinfo->var.reserved[2] = LX_MAKE_RES(hw_ctx->hw_ext_render_width, hw_ctx->hw_ext_render_height);
		#if 1
		fbinfo->var.reserved[3] = (hw_ctx->hw_ext_render_bpp==4)? 1:0;
		#else
		fbinfo->var.reserved[3] = (hw_ctx->hw_ext_render_output_path & FB_E60_EXT_RENDER_OSD_PATH)? 0x1:0x0;
		#endif
	}
}

/** detect current mirror mode configuration set by boot loader
 *
 */
static void FBDEV_E60_CMN_InitMirrorEnv(void)
{
	int	xidx;
	int xnum, xlst[2];
	int	fb_dev_id = LX_FBDEV_ID_OSD0;

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_E60_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

	xnum = FBDEV_E60_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

	xidx = xlst[0];
	FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

	/* raxis.lim (2018/07/02) -- read mirror mode configuration set from boot loader */
	if(mirror_ctrl->status == FBDEV_E60_MIRROR_NONE)
	{
		UINT32 hw_val;

		OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_main);
		OSDX_CTRL_E60_Rd01(xidx, osd_ctrl_main, osd_v_reverse_en, hw_val);

		mirror_ctrl->status = (hw_val)? FBDEV_E60_V_MIRROR_ON: 0x0;

		FBDEV_NOTI("OSD v_mirror detected (%d)\n", hw_val);
	}
}

/** setup OSD_SHP
 *
 *
 *
 */
static void FBDEV_E60_CMN_SetupSRScaler(BOOLEAN onoff, BOOLEAN bForce)
{
#if FBDEV_E60_NOT_IMPL("OSD_SHP 실체를 아직 알 수 없어, 막아 놓음")
	int	i;
	int	xidx;
	int xnum, xlst[2];
	UINT32 hw_onoff;
	int	fb_dev_id = LX_FBDEV_ID_OSD0;

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_E60_SR_CTRL_T* sr_ctrl = FBDEV_E60_GET_SR_CTRL(hw_ctx,fb_dev_id);

	PARAM_UNUSED(bForce);

	xnum = FBDEV_E60_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

	for (i=0; i<xnum; i++)
	{
		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

		/* raxis.lim (2019/05/21) -- osd_bitmap_ctrl is valid only for primary posd layer */
		if(i != 0x0) continue;

		/* check HW status for debug. hw_onoff is not used yet */
		OSDX_E60_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
		OSDX_E60_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, hw_onoff);
		hw_onoff ^= 1;
		FBDEV_HW_DEBUG("OSD SR(HW) = %d\n", hw_onoff);

		sr_ctrl->status   = (onoff)? FBDEV_E60_SR_STATUS_ON:FBDEV_E60_SR_STATUS_OFF;

#ifdef FBDEV_E60_USE_SR_CTRL
		/* configure OSD SR detour (= enable/disable OSD SR control)
		 *
		 * HOW TO enable OSD_SR
		 *
		 * 1. OSD SHP.core_ctrl.reg_top_bypass 		   -> 0x0
		 * 2. OSD.OSD0_BITMAP_CTRL0.reg_shp_detouor_en -> 0x0
		 * 3. OSD.OSD0_BITMAP_CTRL0.reg_rgb2yc_csc_en  -> 0x1
		 * 4. OSD.OSD0_BITMAP_CTRL0.reg_yc2rgb_csc_en  -> 0x1
		 *
		 */
		SHP0_CTRL_RdFL(shp_core_ctrl_00);
		OSDX_E60_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

		SHP0_CTRL_Wr01(shp_core_ctrl_00, reg_top_bypass, (onoff)? 0x0: 0x1);
		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, (onoff)?0x0:0x1);

		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en, (onoff)?0x1:0x0);
		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, (onoff)?0x1:0x0);

		/* S.OSD 에서 OSD SR 사용할건지에 따라 아래 설정은 틀릴지도 모름 */
		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_sosd_csc_en, (onoff)?0x1:0x0);

		/* M16P3 don't support reg_scaler_status_sel & reg_cubic_coeff_0 */
		#if 0
		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_scaler_status_sel, 0x1);	/* why ?? */
		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_cubic_coeff_0, 0x0);		/* not used */
		#endif

		SHP0_CTRL_WrFL(shp_core_ctrl_00);
		OSDX_E60_WrFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

		FBDEV_NOTI("OSD SR (%s)\n", (onoff)? "on":"off");
#else
		OSDX_E60_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, 0x1);
		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en, 0x0);
		OSDX_E60_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, 0x0);
		OSDX_E60_WrFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

		FBDEV_NOTI("OSD SR disabled (%s)\n", "off");
#endif
	}

	/* if user ti_gain is defined, initialize HW configuration using the last user ti_gain.
	 * otherwise, initialize ti_gain based on HW default value.
	 */
	sr_ctrl->ti_gain = FBDEV_E60_CMN_GetHWStatus(FBDEV_E60_HW_STATUS_SR_GAIN, 0x0);

	FBDEV_HW_DEBUG("fb(0) sr_gain=0x%08x\n", sr_ctrl->ti_gain);

#endif	/* if 0 */
}

/** initialize FBC variable to the default state.
 *	The real HW register will be set inside FBDEV_E60_CMN_WriteOSDHeader()
 *	This function is also called during instant boot resume to setup AFBC register again.
 *
 */
static void FBDEV_E60_CMN_InitFBCEnv(void)
{
#ifdef FBDEV_E60_USE_FBC_CTRL
	int i;
	/* raxis.lim (2010/10/15) -- setup afbc for both fb(0) and fb(1)
	 */
	for (i=0; i<=LX_FBDEV_ID_OSD1; i++)
	{
		FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
		FBDEV_E60_FBC_CTRL_T* fbc_ctrl = FBDEV_E60_GET_FBC_CTRL(hw_ctx,i);
		int hw_afbc_status = 0;

		fbc_ctrl->fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW;
		fbc_ctrl->status  = FBDEV_E60_FBC_STATUS_NONE;
		FBDEV_E60_FBC_DEBUG("fb(%d) initialize fbc env\n", LX_FBDEV_ID_OSD0);

		/* raxis.lim (2016/10/05) -- try to initialize OSD to AFBC graphic path if possible
 		 * boot loader can display both non-AFBC and AFBC logo image, so I should keep the current
		 * graphic configuration.
		 * below codes will be active if cold boot or snapshot boot (not instant boot)
		 *
		 *
		 */
		hw_afbc_status = FBDEV_E60_CMN_GetHWStatus(FBDEV_E60_HW_STATUS_AFBC, i);

		FBDEV_HW_NOTI("fb(%d) initial FBC mode = %d\n", i, hw_afbc_status);

		/* recover FBC if AFBC display is used at boot loader */
		if (hw_afbc_status)
		{
			FBDEV_E60_FBC_DEBUG("fb(%d) recover FBC HW config\n", i);
			FBDEV_E60_CMN_SetupFBC(i, LX_FBDEV_FBC_FORMAT_AFBC);
		}
	}
#endif
}

#ifdef FBDEV_E60_USE_FBC_CTRL
/** create or destory FBC envrionment
 *
 */
static void FBDEV_E60_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt)
{
	int	i;
	int	xidx;
	int xnum, xlst[2], afbc_xlst[2];

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_E60_FBC_CTRL_T* fbc_ctrl = FBDEV_E60_GET_FBC_CTRL(hw_ctx, fb_dev_id);

	FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

	/* check HW status */
	if (fbc_ctrl->fbc_fmt == fbc_fmt)
	{
#ifdef FBDEV_E60_SW_RECOVERY_AFBC_FLAG_CORRUPTION
		int hw_afbc_status = FBDEV_E60_CMN_GetHWStatus(FBDEV_E60_HW_STATUS_AFBC, fb_dev_id);

		hw_afbc_status = (hw_afbc_status)? LX_FBDEV_FBC_FORMAT_AFBC: LX_FBDEV_FBC_FORMAT_RAW;
		FBDEV_CHECK_CODE(fbc_ctrl->fbc_fmt != hw_afbc_status, goto afbc_config,
						"<!> fb(%d) sw/hw status mismatch (sw:%d, hw:%d)\n", fb_dev_id, fbc_ctrl->fbc_fmt, hw_afbc_status);
#endif
		return; /* same value. do nothing */
	}

#ifdef FBDEV_E60_SW_RECOVERY_AFBC_FLAG_CORRUPTION
afbc_config:
#endif
	xnum = FBDEV_E60_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

	FBDEV_NOTI("fb(%d) setup afbc_path=%d\n", fb_dev_id, fbc_fmt);

	OSD_CCO1_TOP_E60_RdFL(ctrl_dpath);
	OSD_CCO1_TOP_E60_RdFL(ctrl_auto_init_afbc);

	if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
	{
		UINT32 afbc_auto_init_src_val = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0x0: 0x1;
#ifdef FBDEV_E60_USE_AFBC_READ_BW_SAVING
		UINT32 enable = FBDEV_E60_CMN_GetOSDEnable(fb_dev_id);
#else
		UINT32 enable = 1;
#endif

		FBDEV_E60_FBC_DEBUG("setup fbc_fmt = 0x1 (enable AFBC mode)\n");

		if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
		{
			OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd0_afbc_en, 0x1 );
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,		enable);
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en, 	enable);
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, idx_afbc0_pic_init_src,  0x0); /* g0_pic_init. 이건 고정 ? */

			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_src, 	afbc_auto_init_src_val);

			FBDEV_E60_FBC_DEBUG("fb(%d) afbc enabled. xlst=%d,%d view=%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1], enable);
		}

		if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
		{
			OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd1_afbc_en, 0x1 );
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en, 		enable);
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en, 	enable);
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, idx_afbc1_pic_init_src,  0x1); /* g1_pic_init. 이거 선택 가능 ? */

			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_src, 	afbc_auto_init_src_val );

			FBDEV_E60_FBC_DEBUG("fb(%d) afbc enabled. xlst=%d,%d view=%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1], enable);
		}
	}
	else
	{
		FBDEV_E60_FBC_DEBUG("setup fbc_fmt = 0x0 (disable AFBC mode)\n");

		if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
		{
			OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd0_afbc_en, 0x0 );
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,		0x0);
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en, 	0x0);

			FBDEV_E60_FBC_DEBUG("fb(%d) afbc disabled. xlst=%d,%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1]);
		}

		if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
		{
			OSD_CCO1_TOP_E60_Wr01(ctrl_dpath, osd1_afbc_en, 0x0 );
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en, 		0x0);
			OSD_CCO1_TOP_E60_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en, 	0x0);

			FBDEV_E60_FBC_DEBUG("fb(%d) afbc disabled. xlst=%d,%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1]);
		}
	}

	/* setup OSD registers */
	for (i=0; i<xnum && VALID_XIDX(xlst[i]); i++)
	{
		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xidx), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xidx);

		OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_main);

		if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
		{
			/* enable BITMAP mode */
			OSDX_CTRL_E60_Wr01(xidx, osd_ctrl_main,	osd_bitmap_only_mode_en, 0x1 );

			fbc_ctrl->status |=  FBDEV_E60_FBC_STATUS_PATH_CHANGE;;
		}
		else
		{
			/* disable BITMAP mode (default in raw mode) */
			OSDX_CTRL_E60_Wr01(xidx, osd_ctrl_main,	osd_bitmap_only_mode_en, 0x0 );

			fbc_ctrl->status &= ~FBDEV_E60_FBC_STATUS_HDR_SETUP;
			fbc_ctrl->status |=  FBDEV_E60_FBC_STATUS_PATH_CHANGE;
		}

		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_main);
	}

	/* flush top registers */
	OSD_CCO1_TOP_E60_WrFL(ctrl_dpath);
	OSD_CCO1_TOP_E60_WrFL(ctrl_auto_init_afbc);

	/* raxis.lim (2019/05/21) -- I will always configure AFBC to use ready_flag */
	AFBC_CTRL_RdFL(0, ctrl_afbc_0);
	AFBC_CTRL_RdFL(1, ctrl_afbc_0);

	AFBC_CTRL_Wr01(0, ctrl_afbc_0, update_ready_flag_en, 0x1);
	AFBC_CTRL_Wr01(1, ctrl_afbc_0, update_ready_flag_en, 0x1);

	AFBC_CTRL_WrFL(0, ctrl_afbc_0);
	AFBC_CTRL_WrFL(1, ctrl_afbc_0);

	FBDEV_E60_FBC_DEBUG("fb(%d) fbc_mode=0x%x setup\n", fb_dev_id, fbc_fmt);

	fbc_ctrl->fbc_fmt = fbc_fmt;
}


/** setup AFBC register for OSD display
 *
 *
 */
static void FBDEV_E60_CMN_WriteFBCHdrRegs(int fb_dev_id, FBDEV_E60_OSD_HDR_T osd_hdr[2], FBDEV_E60_OSD_EXHDR_T* osd_exhdr)
{
	int	i;
	int	afbc_xidx;
	int	xnum, xlst[2], afbc_xlst[2];

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_E60_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];
	FBDEV_E60_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

	FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

	FBDEV_CHECK_DEBUG(fbc_ctrl->fbc_fmt != LX_FBDEV_FBC_FORMAT_AFBC, return, "fb(%d) non-afbc image\n", fb_dev_id);

	xnum = FBDEV_E60_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
	/* ignore noisy warning msg becase some OSD layer is not supported by HW */
	FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d. fb(%d)\n", fb_dev_id, xnum, fb_dev_id );

	for (i=0; i<xnum; i++)
	{
		UINT32 fbc_hdr_size;
		UINT32 fbc_hdr_addr;

		int	osd_img_x, osd_img_y, osd_img_w, osd_img_h;
		int osd_img_stride, osd_img_bpp;

		/* if two osd_hdr is passed, each OSD header represents left and right image
		 *
		 * osd_hdr[0] (Left)  .. hdr_mem_sz=1920,2160 out_pos=0,0
		 * osd_hdr[1] (Right) .. hdr_mem_sz=1920,2160 out_pos=1920,0
		 */
		osd_img_w	= osd_hdr[i].osd_hdr_w_mem;
		osd_img_h	= osd_hdr[i].osd_hdr_h_mem;

		/* raxis.lim (2019/07/23)
		 * if current fb_dev_id has 2 OSD layers, L/R image is represnted by x position.
		 * if current fb_dev_is has only 1 OSD layers, x,y position should not be changed.
		 */
		if(xnum>1)
		{
			osd_img_x	= osd_hdr[i].osd_hdr_xpos;
			osd_img_y	= osd_hdr[i].osd_hdr_ypos;
		}
		else
		{
			osd_img_x	= 0;
			osd_img_y	= 0;
		}

		FBDEV_E60_FBC_DEBUG("idx %d, img_xy %d,%d\n", i, osd_img_x, osd_img_y);

		osd_img_stride	= osd_exhdr->img_stride;
		osd_img_bpp 	= FBDEV_E60_BITS_2_BYTES(osd_exhdr->bits_per_pixel);

		afbc_xidx = afbc_xlst[i];

		/* current fb_dev_id is not attached to afbc */
		if(INVALID_AFBC_XIDX(afbc_xidx)) continue;

		/* for dbeug What's AFBC dimension FBDEV_E60_BITS_2_BYTES(canvas.bits_per_pixel);> */
		fbc_hdr_size = afbc_sw_get_header_size(NULL, osd_img_stride/osd_img_bpp, osd_exhdr->img_height);
		fbc_hdr_addr = osd_hdr->osd_hdr_ptr_bmp;

		FBDEV_E60_FBC_DEBUG("fb(%d) afbc_xidx(%d) hdr.addr=0x%08x hdr.sz=0x%x body.addr=0x%08x xy=%d,%d size=%dx%d\n",
				fb_dev_id, afbc_xidx, fbc_hdr_addr,  fbc_hdr_size, fbc_hdr_addr+fbc_hdr_size,
				osd_img_x, osd_img_y, osd_img_w, osd_img_h);


		/* once the whole AFBC registers are set, I will just update the minimal registers */
		if(fbc_ctrl->status & FBDEV_E60_FBC_STATUS_HDR_SETUP)
		{
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_1);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_2);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_3);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_4);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_8);

			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_1, hd_base, 	 fbc_hdr_addr);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_8, pl_data_base, fbc_hdr_addr);

			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_x,		osd_img_x);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_y,		osd_img_y);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_x, 		LX_CALC_ALIGNED_VALUE(osd_img_x+osd_img_w-2,1));
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_y, 		osd_img_y+osd_img_h-1);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_4, img_width,	osd_img_stride/osd_img_bpp);

			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_1);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_2);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_3);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_4);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_8);
		}
		/* below configurations will be called when the first AFBC image is feeded */
		else
		{
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_0);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_1);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_2);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_3);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_4);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_5);
//			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_6);
//			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_7);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_8);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_9);
//			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_a);
//			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_b);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_c);
//			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_d);
//			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_e);
//			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_f);
			AFBC_CTRL_RdFL(afbc_xidx, ctrl_afbc_10);

			/* HW guy said that I should set the same value to AFBC hdr & data :(
			 * I think it's enough to change only below two value (hd_base, pl_data_base)
			 */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_1, hd_base, 	 fbc_hdr_addr);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_8, pl_data_base, fbc_hdr_addr);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_9, pl_data_end,  0xffffffff);

			/* AFBC data size description
			 *
			 */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_x, 	osd_img_x);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_2, start_y, 	osd_img_y);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_x, 		LX_CALC_ALIGNED_VALUE(osd_img_x+osd_img_w-2,1));
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_3, end_y, 		osd_img_y+osd_img_h-1);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_4, img_width,	osd_img_stride/osd_img_bpp);

			/* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
			 *
			 * HW guy fixed dec_buf_depth value to 959 and pl_buf_depth value to 255.
			 */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_5, dec_buf_depth_m1, 959);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_5, pl_buf_depth_m1,  255);

			//AFBC0_CTRL_Wr(ctrl_afbc_6, 0x00000000);	/* dummy */
			//AFBC0_CTRL_Wr(ctrl_afbc_7, 0x00000000);	/* dummy */
			//AFBC0_CTRL_Wr(ctrl_afbc_a, 0x00000000);	/* dummy */
			//AFBC0_CTRL_Wr(ctrl_afbc_b, 0x00000000);	/* dummy */

			/* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
			 * HW test value : 0x0011_FF54
			 */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_endian_arb, 1);		/* no description :( */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_endian_arb, 1);		/* no description :( */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_endian_sw,  0xf);		/* ambiguous description :( */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_endian_sw,  0xf);		/* ambiguous description :( */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, pl_gmau_id, 	  5);		/* difficult to understand description :( */
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_c, hd_gmau_txid,  4);		/* difficult to understand description :( */

			//AFBC0_CTRL_Wr(ctrl_afbc_d, 0x00000000);	/* dummy */
			//AFBC0_CTRL_Wr(ctrl_afbc_e, 0x00000000);	/* dummy */

			//AFBC0_CTRL_Wr(ctrl_afbc_f, 0x00000000);

			/* raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
			 *
			 * 0xff80_80ff @RGBA
			 * 0xffff_8080 @ARGB (*)
			 *
			 * I 've used 0xffff_fffff since E60 AFBC integration
			 */
			#if 0
			AFBC_CTRL_Wr(afbc_xidx, ctrl_afbc_10, 0xffff8080);	/* +0xD0 : 0xffff8080 for argb case */
			#else
			AFBC_CTRL_Wr(afbc_xidx, ctrl_afbc_10, 0xFFFFFFFF);	/* +0xD0 : 0xffffffff for argb case */
			#endif

			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, start, 		 0);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, ready, 		 0);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset, 	 0);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset_fifo,0);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, run_mode, 	 1);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, pl_addr_mode, 1);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset_ack, 0);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, gmau_arb_sw_reset,0);

			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, flip_mode, 	(mirror_ctrl->status & FBDEV_E60_V_MIRROR_ON)? 1:0);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, ignore_q_full,0);
			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, wrap_en, 	 1);

			/* flush data */
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_1);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_2);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_3);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_4);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_5);
			//AFBC0_CTRL_WrFL(ctrl_afbc_6);
			//AFBC0_CTRL_WrFL(ctrl_afbc_7);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_8);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_9);
			//AFBC0_CTRL_WrFL(ctrl_afbc_a);
			//AFBC0_CTRL_WrFL(ctrl_afbc_b);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_c);
			//AFBC0_CTRL_WrFL(ctrl_afbc_d);
			//AFBC0_CTRL_WrFL(ctrl_afbc_e);
			//AFBC0_CTRL_WrFL(ctrl_afbc_f);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_10);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_0);
		}
	}
	fbc_ctrl->status |= FBDEV_E60_FBC_STATUS_HDR_SETUP;
}

static void FBDEV_E60_CMN_FlushFBCHdrRegs(int fb_dev_id)
{
	int	i;
	int	afbc_xidx;
	int	xnum, xlst[2], afbc_xlst[2];

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_E60_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];

	FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

	if (fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
	{
		xnum = FBDEV_E60_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
		FBDEV_E60_FBC_DEBUG("fb(%d) xnum=%d, afbc_xlst=(%d,%d)\n", fb_dev_id, xnum, afbc_xlst[0], afbc_xlst[1]);

		/* current fb_dev_id is not attached to afbc */
		FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d\n", fb_dev_id, xnum);

		for (i=0; i<xnum; i++)
		{
			afbc_xidx = afbc_xlst[i];
			if(INVALID_AFBC_XIDX(afbc_xidx)) continue;

			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, update_ready_flag, 0x1);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_0);

			FBDEV_E60_FBC_DEBUG("fb(%d) afbc_xidx(%d) flush AFBC regs\n", fb_dev_id, afbc_xidx);
		}
	}
}
#endif

/** write real header data to register
 *
 *
 */
void	FBDEV_E60_CMN_WriteHdrRegs	(int fb_dev_id, FBDEV_E60_OSD_HDR_T* osd_hdr, FBDEV_E60_OSD_EXHDR_T* osd_exhdr)
{
	int		i;
	int		xidx;
	int		xnum, xlst[2];

	FBDEV_E60_OSD_HDR_T osd_hw_hdr[2];	/* E60 supports max 2 POSD for 4KOSD display */
	UINT32* hdr_regs;

	ULONG   flags;
	struct scanvas* canvas = NULL;
	FBDEV_WIN_CTX_T* wctx	= NULL;
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	canvas = FBDEV_GetWinCanvas(fb_dev_id);
	FBDEV_CHECK_CODE(NULL==canvas, return, "invalid canvas. fb(%d)\n", fb_dev_id );

	wctx = FBDEV_GetWinCtx(fb_dev_id);
	FBDEV_CHECK_CODE(NULL==wctx, return, "invalid winctx. fb(%d)\n", fb_dev_id );

	xnum = FBDEV_E60_CMN_GetHWXList(fb_dev_id, xlst);
	/* ignore noisy warning msg becase some OSD layer is not supported by HW */
	FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "invalid xnum %d. fb(%d)\n", xnum, fb_dev_id );

	spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

	/* notify osd freeze for debug */
	if (!wctx->status.b_osd_hdr_flush)
	{
		UINT32 disp_fbmem;

		for (i=0; i<xnum; i++)
		{
			xidx = xlst[i];
			if (INVALID_XIDX(xidx)) continue;

			OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr6);
			disp_fbmem = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr6);

			FBDEV_NOTI("fb(%d) xidx(%d) freezed. osd_hdr_flush deferred. keep 0x%08x\n", fb_dev_id, xidx, disp_fbmem );
		}
		goto func_exit;
	}

	FBDEV_E60_HDR_DEBUG("in %dx%d -> out %dx%d\n", osd_hdr->osd_hdr_w_mem, osd_hdr->osd_hdr_h_mem, osd_hdr->osd_hdr_w_out, osd_hdr->osd_hdr_h_out);

	/* flush OSD header registers itself */
	for (i=0; i<xnum; i++)
	{
		xidx = xlst[i];
		if (INVALID_XIDX(xidx)) continue;

		memcpy(&osd_hw_hdr[i], osd_hdr, sizeof(FBDEV_E60_OSD_HDR_T));

		/* xnum=2 즉 2개의 POSD가 필요한 경우. 각각 L/R 절반씩 처리토록 한다. */
		if (xnum==2)
		{
			if(canvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
			{
				/* two posd will share the same AFBC image base */
			}
			else
			{
				osd_hw_hdr[i].osd_hdr_ptr_bmp += (osd_exhdr->img_stride/2)*i;
			}
			osd_hw_hdr[i].osd_hdr_w_mem /= 2;			/* 3840 = 1920 + 1920 */
			osd_hw_hdr[i].osd_hdr_w_out /= 2; 			/* 7680 = 3840 + 3480 ? */

			/* 4K OSD 모드인 경우 OSD header 를 구성하는 각 필드를 항상 참조하는것은 아니다. 정리하자
			 *
			 * (1) osd0_4k_ctrl 을 통하여 input size, output size 는 결정된다.
			 *     즉 osd_hdr_w_mem, osd_hdr_h_mem, osd_hdr_w_out, osd_hdr_h_out, osd_hdr_xposd, osd_hdr_ypos 값을 참조하지 않는다.
			 *
			 * (2) 하지만 위 값들은 이미 OSD kdriver 내에서 나름 의미있게 사용되기 때문에, 과거의 칩 동작성을 참고로 하여
			 *	   reasonable 한 값으로 관리되어야 한다.
			 *	   특히 L/R 의 osd_hdr_xpos 값은 AFBC 0/1 설정시에 중요한 값으로 사용된다.
			 *
		 	 * (3) wpl 의 경우 통 이미지로 구성된 ARGB 이미지의 경우에는 반드시 실제 img_w / 8 byte 로 정확하게 계산되어져야 한다.
			 *     AFBC 모드인 경우에는 wpl 값을 참조하지 않는듯 보임. 이미 위 정책에 맞게 계산되어 오므로, 여기서는 값 수정하지 않겠음.
			 */
			//osd_hw_hdr[i].osd_hdr_wpl = osd_hdr->osd_hdr_w_out/2;

			/* raxis.lim (2020/02/04)
			 * 4K OSD 모드에서는 HW 가 osd x/y, osd_out_w/h 등의 데이터를 참조하지 않음. HWSETUP_IMG_4KOSD 참조.
			 * 다만 아래 osd_hdr_xpos 는 AFBC 2장 제어시에 중요한 필드임.
			 */
			osd_hw_hdr[i].osd_hdr_xpos = (osd_hw_hdr[i].osd_hdr_w_mem)*i;
		}

		hdr_regs= (UINT32*)&osd_hw_hdr[i];

		FBDEV_E60_HDR_DEBUG("osd_hw_hdr wxh = %dx%d\n", osd_hw_hdr[i].osd_hdr_w_out, osd_hw_hdr[i].osd_hdr_h_out);

		OSDX_CTRL_E60_Wr(xidx, osd_ctrl_hdr0, hdr_regs[0]);
		OSDX_CTRL_E60_Wr(xidx, osd_ctrl_hdr1, hdr_regs[1]);
		OSDX_CTRL_E60_Wr(xidx, osd_ctrl_hdr2, hdr_regs[2]);
		OSDX_CTRL_E60_Wr(xidx, osd_ctrl_hdr3, hdr_regs[3]);
		OSDX_CTRL_E60_Wr(xidx, osd_ctrl_hdr4, hdr_regs[4]);
		OSDX_CTRL_E60_Wr(xidx, osd_ctrl_hdr5, hdr_regs[5]);
		OSDX_CTRL_E60_Wr(xidx, osd_ctrl_hdr6, hdr_regs[6]);

		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr0);
		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr1);
		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr3);
		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr4);
		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr5);
		OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr6);

		/* raxis.lim (2017/09/15) -- DO NOT write OSD out_win only
		   when OSD0_PQEFW_OSD0_OUT_CTRL is enabled and TEMP_PAUSE is not enabled

		   raxis.lim (2018/05/15)
		   Remember that FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL is enabled temporarily when user changes OSD output resolution

		   raxis.lim (2019/06/19)
		   support orbit control (http://clm.lge.com/issue/browse/SDOSTB-246)
		   (note) 4KOSD 테스트 모드에서는 orbit 활성화시 OSD 출력 정상아님. orbit 제어하는 FW 에서 추가 제어 필요할 듯 예상됨

		   raxis.lim (2019/07/29)
		   EXT_FRC 가 붙었을 경우에는 orbit control 을 E60 에서 하지 않는다.
		   향후에는 flag 를 좀 더 조정하자.
		*/
		if(fb_dev_id == LX_FBDEV_ID_OSD0)
		{
			if(  (fbdev_pqefw_osd0_out_ctrl) &&
		  	     (hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL) &&
			    !(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL))
			{
				/* do nothing */
			}
			else
			{
				UINT32 w, h;
				OSDX_CTRL_E60_Rd01(xidx, osd_ctrl_hdr2, osd_hdr_w_out, w);
				OSDX_CTRL_E60_Rd01(xidx, osd_ctrl_hdr2, osd_hdr_h_out, h);
				OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr2);

				FBDEV_E60_HDR_DEBUG("fb(%d) xidx(%d) flush OSD_CTRL_HDR2. %dx%d\n", fb_dev_id, xidx, w, h);
			}
		}
		else
		{
			OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_hdr2);
		}

	}

	/* flush post header (AFBC,OSD_SHP etc ) */
	{
		/* flush AFBC register */
#ifdef FBDEV_E60_USE_FBC_CTRL
		if (fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1)
		{
			FBDEV_E60_CMN_SetupFBC(fb_dev_id, canvas->fbc_fmt);

			if(canvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
			{
				FBDEV_E60_CMN_WriteFBCHdrRegs(fb_dev_id, osd_hw_hdr, osd_exhdr);
			}

			FBDEV_E60_CMN_FlushFBCHdrRegs(fb_dev_id);
		}
#endif


#ifdef FBDEV_E60_SUPPORT_SHP_CTRL
#error
		/* raxis.lim (2018/04/09) -- sync between OSD_SHP (OSD_SR) and OSD out info
		 * O18/M16P3 doesn't have any limitation regarding OSD_SR size.
		 * but core_ctrl_01's width, height should have the same value with output_win to prevent image corruption.
		 * refer to SICDTV-4853
		 *
		 * raxis.lim (2019/07/29) -- SHP control should be disabled at EXT_FRC mode.
		 */
		if (fb_dev_id == LX_FBDEV_ID_OSD0 && !hw_ctx->b_support_ext_frc) // && xnum==1)
		{
			UINT32	osd_shp_width, osd_shp_height;

			SHP0_CTRL_RdFL(shp_core_ctrl_01);
			SHP0_CTRL_Rd01(shp_core_ctrl_01, reg_top_width, osd_shp_width );
			SHP0_CTRL_Rd01(shp_core_ctrl_01, reg_top_height,osd_shp_height);

			if(osd_shp_width != osd_hdr->osd_hdr_w_out || osd_shp_height != osd_hdr->osd_hdr_h_out)
			{
				/* raxis.lim (2018/11/01) -- DO NOT write OSD_SHP
				   when OSD0_PQEFW_OSD0_OUT_CTRL is enabled and TEMP_PAUSE is not enabled
				*/
				if(fbdev_pqefw_osd0_out_ctrl &&
					   (hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL) &&
				   !(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL))
				{
					/* do nothing */
				}
				else
				{
					FBDEV_NOTI("osd_shp's size changed (%d,%d) -> (%d,%d)\n",
						osd_shp_width, osd_shp_height, osd_hdr->osd_hdr_w_out, osd_hdr->osd_hdr_h_out);

					SHP0_CTRL_Wr01(shp_core_ctrl_01, reg_top_width, osd_hdr->osd_hdr_w_out);
					SHP0_CTRL_Wr01(shp_core_ctrl_01, reg_top_height,osd_hdr->osd_hdr_h_out);
					SHP0_CTRL_WrFL(shp_core_ctrl_01);
				}
			}
		}
#endif

		/* TODO: PQE 관련 코드는 너무 복잡하다. 좀 정리 안되나 */
		/* turn off TEMP_PAUSE because OSD update is completed */
		if(fb_dev_id == LX_FBDEV_ID_OSD0 && fbdev_pqefw_osd0_out_ctrl)
		{
			if(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)
			{
				FBDEV_NOTI("PAUSE_PQEFW_OSD0_OUT_CTRL disabled (%d,%d)\n",
				(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL)? 1:0,
					(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)? 1:0);
				hw_ctx->hw_wa_flag &= ~FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL;
			}
		}

		/* if CSR layer, do something extra */
		if(fb_dev_id == LX_FBDEV_ID_OSD3)
		{
			UINT32	ofs_x = osd_hdr->osd_hdr_xpos;
			UINT32	ofs_y = osd_hdr->osd_hdr_ypos;
			UINT32	csr_w = osd_hdr->osd_hdr_w_mem;
			UINT32	csr_h = osd_hdr->osd_hdr_h_mem;

			OSDX_E60_RdFL(osdx_post_csr, osd4_ccv_csr_ctrl0);
			OSDX_E60_RdFL(osdx_post_csr, osd4_ccv_csr_ctrl1);

			OSDX_E60_Wr02(osdx_post_csr, osd4_ccv_csr_ctrl0 , osd_csr_xpos  , ofs_x, osd_csr_ypos  , ofs_y);
			OSDX_E60_Wr02(osdx_post_csr, osd4_ccv_csr_ctrl1 , osd_csr_disp_w, csr_w, osd_csr_disp_h, csr_h);

			OSDX_E60_WrFL(osdx_post_csr, osd4_ccv_csr_ctrl0);
			OSDX_E60_WrFL(osdx_post_csr, osd4_ccv_csr_ctrl1);
		}

		/* notify OSD HW to read osd header */
		for (i=0; i<xnum && VALID_XIDX(xlst[i]); i++)
		{
			xidx = xlst[i];

			OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_main);
			OSDX_CTRL_E60_Wr01(xidx, osd_ctrl_main, osd_hdr_ready_flag, 0x1);
			OSDX_CTRL_E60_WrFL(xidx, osd_ctrl_main);

			FBDEV_E60_HDR_DEBUG("fb(%d) xidx(%d) flush osd_hdr regs/data\n", fb_dev_id, xidx);
		}

#ifdef FBDEV_E60_SUPPORT_4KOSD_UPSCALER
		/* raxis.lim (2019/05/22)
		 *
		 * if you want to support OSD smaller than 4K, reg_4k_osd_main_ctrl_2 register should be configured again
		 * to reduce screen corruption, I added this right after updating osd_hdr_ready_flag
		 */
		if (fb_dev_id==LX_FBDEV_ID_OSD0 && xnum==2)
		{
			xidx = xlst[1];
			OSDX_E60_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
			OSDX_E60_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_w, osd_hdr->osd_hdr_w_mem);
			OSDX_E60_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_h, osd_hdr->osd_hdr_h_mem);
			OSDX_E60_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
		}
		/* TODO: add something if you want more OSD configuration after writing OSD header */
#endif
	}

func_exit:
	spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);
}

/** OSD HW common header generator
 *
 *  OSD HW header is made based on struct scanvas data and extra environment such as 3DOSD, reverse etc.
 *
 */
static int FBDEV_E60_CMN_WriteOSDHeader(struct scanvas *pCanvas)
{
	int						fb_dev_id;
	UINT32					bitmap_ptr;
	FBDEV_E60_OSD_HDR_T		osd_hdr;
	FBDEV_E60_OSD_EXHDR_T	osd_exhdr;
	FBDEV_WIN_CTX_T* 		wctx;
	struct scanvas			canvas;
	UINT32					disp_width, disp_height;

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> fb(%d) user_initcall not ready +++\n", pCanvas->fb_dev_id);

	wctx = FBDEV_GetWinCtx(pCanvas->fb_dev_id);
	FBDEV_CHECK_CODE(NULL==wctx, return RET_ERROR, "fb(%d) invalid winctx.\n", pCanvas->fb_dev_id);

	/* doesn't support fb(1) control when external renderer is enabled */
	FBDEV_CHECK_CODE(fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_render == TRUE, return RET_ERROR,
		"fb(%d) ext_renderer mode. ignore osd render\n", pCanvas->fb_dev_id);

	/* clear osd_hdr before writing */
	memset(&osd_hdr,   0x0, sizeof(FBDEV_E60_OSD_HDR_T));
	memset(&osd_exhdr, 0x0, sizeof(FBDEV_E60_OSD_EXHDR_T));
	memcpy(&canvas,	   pCanvas, sizeof(struct scanvas));

	fb_dev_id = canvas.fb_dev_id;
	disp_width = hw_ctx->hw_disp_width;
	disp_height= hw_ctx->hw_disp_height;

	/* raxis.lim (2016/08/08) - if OSD is freezed, DO NOT handle/write any registers
	 *
	 * This patch seems to prevent OSD garbage during transition from non AFBC (boot logo) to AFBC (mercury/webOS) screen.
	 * Originally, osd_hdr_flush is checked at FBDEV_E60_CMN_WriteHdrRegs().
	 * I don't know the below code really prevents OSD garbage rather than the original policy.
	 * <!> More tests are required.
	 */
	if ( !wctx->status.b_osd_hdr_flush )
	{
		int	xidx, xnum, xlst[2];
       	UINT32 disp_fbmem = 0x0;

		xnum = FBDEV_E60_CMN_GetHWXList(fb_dev_id, xlst);
		xidx = xlst[0];

		if(!INVALID_XNUM(xnum))
		{
			OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr6);
			disp_fbmem = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr6);
		}

		FBDEV_NOTI("fb(%d) freezed. osd_hdr_flush deferred & keep fbmem 0x%08x.", fb_dev_id, disp_fbmem);

		return RET_OK;
	}

	switch(fb_dev_id)
	{
		case LX_FBDEV_ID_CSR0:
		{
			int	csr_x_max;
			int csr_x_off, csr_y_off, csr_x_pos, csr_y_pos, csr_x_size, csr_y_size;
			int csr_disp_w, csr_disp_h;

#ifdef FBDEV_E60_USE_UNLIMITED_CURSOR_POSITION
			int csr_h_min_pxl = FBDEV_E60_BYTES_2_PIXEL(FBDEV_E60_GMAU_WORD_BYTES);	/* 16 bytes -> 4 pixel */
#endif
			FBDEV_E60_HDR_DEBUG("cursor_pos req(%d,%d)\n", canvas.output_win.x, canvas.output_win.y );

			// csr_disp_w is used to check if cursor is located at the right corner.
			// this value is set to 3840 in UHD mode, 1920 in FHD mode
			csr_disp_w = hw_ctx->hw_disp_width;
			csr_disp_h = hw_ctx->hw_disp_height;

#if 0
			// scale up x,y value including hotspot based on the current OSD path and OSD output dimension.
			//
			// @note kdriver assumes that application passes the cursor position & size within FHD area.
			//		 so chip kdriver should scale up position information by 2 to make UHD-area value
			//
			// @note if FHD display is connected, we don't need any scale up.
			//
			// @note S.OSD 4K supported
			//
			if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
			{
				if( FBDEV_E60_CMN_IsUHDDispMode() )
				{
					canvas.output_win.x  *= 4;		// scale by 4 in X direction (x4 for 8K)
					canvas.csr_hotspot.x *= 4;

					canvas.output_win.y  *= 4;		// scale by 4 in Y direction (x4 for 8K)
					canvas.csr_hotspot.y *= 4;
				}
				else /* FHD resolution (signage or commercial TV) */
				{
					//csr_disp_w			/= 2;	// bypass x & w info in FHD (raxis.lim 2017/01/24)
					//canvas.output_win.x	/= 2;	// remember that each SoC shows different behavior (due to PQE implementation?)
					//canvas.csr_hotspot.x 	/= 2;	// So TEST IS THE KEY to confirm cursor behavior.
				}
			}
			else
			{
				if( FBDEV_E60_CMN_IsUHDDispMode() )
				{
					canvas.output_win.x  *= 2;		// scale by 2 in X direction (x2 for 4K)
					canvas.csr_hotspot.x *= 2;

					canvas.output_win.y  *= 2;		// scale by 2 in Y direction (x2 for 4K)
					canvas.csr_hotspot.y *= 2;
				}
				else /* FHD resolution. 2K S.OSD case */
				{
					/* do nothing */
				}
			}
#endif
            // if csr_hotspot is active, adjust (x,y) position of cursor layer.
			//
            // if cursor position is negative, I should move the bitmap address ( H/W doesn't accept negative position )
            //
            // IMPORTATNT !! if you change the base address, its alignment should be multiplt of 16 byte ( not 8 byte )
            // woonghyeon just said that it may be H/W bug (limitation?).
            // since we are using ARGB8888 pixel format for cursor OSD. cursor offset should be multiple of 4 pixel !!
			//
			csr_x_max = canvas.stride / FBDEV_E60_BITS_2_BYTES(canvas.bits_per_pixel);

			csr_x_off = 0;
			csr_y_off = 0;

			csr_x_pos = canvas.output_win.x - canvas.csr_hotspot.x;
			csr_y_pos = canvas.output_win.y - canvas.csr_hotspot.y;

			csr_x_size= (canvas.csr_size.w>0)? LX_CALC_ALIGNED_VALUE(canvas.csr_size.w,2): canvas.input_win.w;
			csr_y_size= (canvas.csr_size.h>0)? canvas.csr_size.h : canvas.input_win.h;

			FBDEV_E60_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d info( %dx%d h %d,%d ) max_x %d disp_x %d\n", fb_dev_id,
						csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
						canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y,
						csr_x_max, csr_disp_w );

#ifdef FBDEV_E60_USE_UNLIMITED_CURSOR_POSITION
			// raxis.lim (2015/07/24)
			// if cursor is located at far left corner, we should try to show only minimum cursor viewing area.
			// as described above, minimum viewing area is 4 pixel.
			//
			// @note framebuffer address will be adjusted based on csr_x_off.
			if (csr_x_pos < -(csr_x_size-csr_h_min_pxl))
			{
				csr_x_off = (csr_x_max-csr_h_min_pxl);
				csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,2);

				csr_x_size= csr_h_min_pxl;
				csr_x_pos = 0;
			}
			else
#endif
			// if cursor is at the left side, we calculate csr_x_pos and to change the frame buffer address
			// cursor viewing area should be shrinked by changing csr_x_size
			//
			// @note framebuffer address will be adjusted based on csr_x_off.
			if (csr_x_pos < 0)
			{
				csr_x_off = -csr_x_pos;
				csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,2);

				csr_x_size = csr_x_max - csr_x_off;	// new csr_x_size becomes smaller values from csr_x_max
				csr_x_pos = 0;
			}

			// if cursor is at the top side, we calculate csr_y_pos to adjust the frame buffer address
			// if csr_y_size becomes zero, OSD HW will display the garbage. so we should gaurantee the minimum OSD viewing
			// area in vertical direction.
			//
			// @note framebuffer address will be adjusted based on csr_y_off.
			if (csr_y_pos < 0)
			{
				csr_y_off =  -csr_y_pos;
				csr_y_pos =  0;
				csr_y_size-= csr_y_off;

				if(csr_y_size < FBDEV_E60_CSR_MIN_HEIGHT)
				{
					csr_y_size = FBDEV_E60_CSR_MIN_HEIGHT;
					csr_y_off  = csr_y_size-FBDEV_E60_CSR_MIN_HEIGHT;
				}
			}

			// prevent OSD garbage. effective cursor width should be less than the real surface width
			if (csr_x_size > csr_x_max)	csr_x_size = csr_x_max;

			// if cursor is located at the right corner, I should gaurantee the minimal viewing area of cursor.
			// without it, cursor image will be broken :(
			// see the description for FBDEV_E60_CSR_MIN_WIDTH
			if (csr_x_pos + csr_x_size > csr_disp_w )
			{
#ifdef FBDEV_E60_USE_UNLIMITED_CURSOR_POSITION
				// raxis.lim (2015/07/24)
				// hide cursor will not be shown at the right corner
				// keep in mind that OSD garbage might be shown because I don't gaurantee the minimum viewing area
				if (csr_x_pos > csr_disp_w )
				{
					csr_x_pos = csr_disp_w;
				}
#else
				if (csr_x_pos > csr_disp_w-FBDEV_E60_CSR_MIN_WIDTH)
				{
					csr_x_pos = csr_disp_w-FBDEV_E60_CSR_MIN_WIDTH;
				}
#endif
				csr_x_pos	= LX_CALC_ALIGNED_VALUE(csr_x_pos,2);	/* make X pos is aligned by 4 */

				csr_x_size	= csr_disp_w-csr_x_pos;

				// software workaround for 1x cursor display on blend path
				// On blend path, cursor size should be displayed x2 automatically because OSD disp size is 3840x2160
				// and cursor region is set based on 1920x1080 area
				// if 2x scale up is not supported, I should multiply csr_x_size by double manually
				if ( hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_1X_CSR_DISP_ON_BLEND_PATH )
				{
					if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND )
					{
						csr_x_size *= 2;
						if ( csr_x_size > csr_x_max ) csr_x_size = csr_x_max;
					}
				}
   			}

			// if cursor is located at the bottom corner, I should gaurantee the minimum viewing area, i.e 2 pixel
			if (csr_y_pos > csr_disp_h-FBDEV_E60_CSR_MIN_HEIGHT)
			{
				csr_y_pos = csr_disp_h-FBDEV_E60_CSR_MIN_HEIGHT;
			}

			// NOTE that csr_x_pos, csr_y_pos, csr_x_size, csr_y_size is changed at the above corner checker.
			// if pos or size is set to wrong value, OSD HW will display the garbage screen.
			//
			osd_hdr.osd_hdr_xpos	= csr_x_pos;	/* output x (csr x pos) */
			osd_hdr.osd_hdr_ypos	= csr_y_pos;	/* output y (csr y pos) */
			osd_hdr.osd_hdr_w_mem	= csr_x_size;	/* viewing cursor width */
			osd_hdr.osd_hdr_h_mem	= csr_y_size;	/* viewing cursor height */
			osd_hdr.osd_hdr_w_out	= csr_x_size;	/* output w */
			osd_hdr.osd_hdr_h_out	= csr_y_size;	/* output h */

			// adjust framebuffer address if necessary
			// @note  gMAU requests 16byte aligned address
			bitmap_ptr = canvas.osd_bm_paddr;
            bitmap_ptr += ( csr_y_off * canvas.stride ) + FBDEV_E60_GMAU_ALIGNED_BYTES(csr_x_off * FBDEV_E60_BITS_2_BYTES(canvas.bits_per_pixel));

			osd_hdr.osd_hdr_pixel_order	= canvas.pixel_order_en;
			osd_hdr.osd_hdr_wpl 		= FBDEV_E60_BYTES_2_OSD_WORDS(canvas.stride);

			FBDEV_E60_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d <- req( %dx%d h %d,%d)\n", fb_dev_id,
						csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
						canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y );
			FBDEV_E60_HDR_DEBUG("fb(%d) cursor pre-processing done\n", fb_dev_id);
		}
		break;

		case LX_FBDEV_ID_OSD0:
		default:
		{
			if( FBDEV_E60_CMN_IsUHDDispMode() ) // && (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) )
			{
				// raxis.lim (2017/08/18)
				//
				// some apps/platforms doesn't know the UHD display resolution and try to configure output
				// to FHD resolution as they did in FHD DTV. in that cases, I assume that apps set the
				// wrong output configuration and they want full-sized image display
				//
				// if output size is less than display size, I will treait it as wrong information, ignore user
				// value and use display resolution for input image to be displayed to the full screen.
				//
				if(fbdev_osd0_user_out_win && canvas.user_win_ctrl_en)
				{
					// keep the user configuration. DO NOT modify output_win in kdriver
				}
				else
				{
					canvas.output_win.w = disp_width;
					canvas.output_win.h = disp_height;
				}
			}
			else
			{
				// raxis.lim (2018/06/08)
				// when low-resolution mode, OSD image is shown onto display without any scale.
				// because the user supplied surface is scaled down at the HAL layer, we can't use
				// any in/out hwparamters by user not fix them as the display resolution.
				//
				canvas.input_win.w	= disp_width;
				canvas.input_win.h 	= disp_height;
				canvas.output_win.w = disp_width;
				canvas.output_win.h = disp_height;
				canvas.stride		= FBDEV_E60_PIXEL_2_BYTES(canvas.input_win.w);
			}

			/* 테스트 코드임 */
			if(fb_dev_id==LX_FBDEV_ID_OSD1)
			{
				canvas.output_win.w = canvas.input_win.w;
				canvas.output_win.h = canvas.input_win.h;

				//FBDEV_E60_HDR_DEBUG("fb(%d) pos=%d,%d\n", fb_dev_id, canvas.output_win.x, canvas.output_win.y);
			}

			if (canvas.input_win.w > disp_width )	canvas.input_win.w = disp_width;
			if (canvas.input_win.h > disp_height) 	canvas.input_win.h = disp_height;
			if (canvas.output_win.w > disp_width )	canvas.output_win.w = disp_width;
			if (canvas.output_win.h > disp_height)	canvas.output_win.h = disp_height;


			// raixs.lim (2017/08/25)
			// support user defined output win for debug. invalid config might make OSD corruption
			if (canvas.test_output_win.w && canvas.test_output_win.h)
			{
				FBDEV_E60_HDR_DEBUG("++ user output used (%d,%d)\n", canvas.test_output_win.w, canvas.test_output_win.h);
				memcpy(&canvas.output_win, &canvas.test_output_win, sizeof(LX_RECT_T));
			}

			// raxis.lim (2015/01/12) -- handle odd width
			// OSD doesn't support odd number as output width. so let's make it to even number
			if ( canvas.output_win.w & 0x1 )
			{
				FBDEV_E60_HDR_DEBUG("fb(%d) convert odd out_w %d to %d\n", fb_dev_id, canvas.output_win.w, canvas.output_win.w&0xfffffffe);
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
				FBDEV_E60_HDR_DEBUG("fb(%d) bitmap based moved ! by %d,%d\n", fb_dev_id, canvas.input_win.x, canvas.input_win.y );

				/* gMAU requests 16byte aligned address */
				bitmap_ptr += canvas.input_win.y * canvas.stride;
				bitmap_ptr += FBDEV_E60_GMAU_ALIGNED_BYTES(FBDEV_E60_BITS_2_BYTES(canvas.input_win.x*canvas.bits_per_pixel));
			}
			FBDEV_E60_HDR_DEBUG("fb(%d) bitmap hwparam (%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x out=%dx%d\n", fb_dev_id,
					canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
					canvas.stride, bitmap_ptr, canvas.fbc_fmt,
					canvas.output_win.w, canvas.output_win.h);

			osd_hdr.osd_hdr_pixel_order	= canvas.pixel_order_en;
			osd_hdr.osd_hdr_wpl 		= FBDEV_E60_BYTES_2_OSD_WORDS(canvas.stride);
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

	/* handle reverse OSD if requested */
	FBDEV_E60_CMN_HandleReverseOSD(fb_dev_id, &canvas, &osd_hdr);

	FBDEV_E60_HDR_DEBUG("fb(%d) bitmap hwparam (%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x (final)\n", fb_dev_id,
			canvas.input_win.x, canvas.input_win.y,
			canvas.input_win.w, canvas.input_win.h,
			canvas.stride, bitmap_ptr, canvas.fbc_fmt );

	/* save osd header */
	memcpy( &hw_ctx->osd_hdr_sav[fb_dev_id], &osd_hdr, sizeof(FBDEV_E60_OSD_HDR_T));

	/* raxis.lim (2019/05/21)
	 *
	 * I don't care here whether two POSDs sare necessary or not. refer to FBDEV_E60_CMN_WriteHdrRegs()
	 */
	osd_exhdr.bits_per_pixel= canvas.bits_per_pixel;
	osd_exhdr.img_stride 	= canvas.stride;
	osd_exhdr.img_height	= osd_hdr.osd_hdr_h_mem;	/* 이 값이 맞나 몰라 */

	FBDEV_E60_CMN_WriteHdrRegs(fb_dev_id, &osd_hdr, &osd_exhdr);

	/* do somthing if necessary */

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
int FBDEV_E60_CMN_SetOSDEnable(int fb_dev_id, int enable)
{
	int		i;
	int		xidx;
	int		xnum, xlst[2], afbc_xlst[2];
	UINT32	val = 0x0;

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	FBDEV_E60_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_E60_GET_EXT_RENDER_CTRL(hw_ctx);

	if (fb_dev_id == LX_FBDEV_ID_OSD0 && hw_ctx->b_support_ext_render)
	{
		// (2020/10/16)
		// Estreamer 동작 종료후, UI 가 켜질때 cursor 를 복구시킬 수 있도록 함
		// see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
		if (enable)
		{
			if(FBDEV_E60_CMN_GetOSDEnable(LX_FBDEV_ID_CSR0))
			{
				OSDX_E60_RdFL(osdx_post_csr, osd4_csr_sync_ctrl0);
				OSDX_E60_Wr01(osdx_post_csr, osd4_csr_sync_ctrl0, osd_sync_enable, 1);
				OSDX_E60_WrFL(osdx_post_csr, osd4_csr_sync_ctrl0);

				FBDEV_NOTI("++ set cursor visible when UI is shown\n");
			}
		}
	}

	/* doesn't support fb(1) control when external renderer is enabled */
	if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_render)
	{
		ext_render_ctrl->hwparam.enable = enable;
		FBDEV_HW_NOTI("fb(%d) ext_renderer en=%d, cmd=0x%08x\n", fb_dev_id, ext_render_ctrl->hwparam.enable, ext_render_ctrl->hwparam.command);

		if(enable)
		{
			// (2020/10/16)
			// Estreamer 동작전에 cursor 를 강제로 off 시킴
			// see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
			OSDX_E60_RdFL(osdx_post_csr, osd4_csr_sync_ctrl0);
			OSDX_E60_Wr01(osdx_post_csr, osd4_csr_sync_ctrl0, osd_sync_enable, 0);
			OSDX_E60_WrFL(osdx_post_csr, osd4_csr_sync_ctrl0);

			FBDEV_NOTI("++ set cursor invisible when EXT_RENDER is shown\n");

			//usleep_range(sleep_us, 16600); (2020/10/16) FW 오동작시 이 코드를 사용할것. 테스트결과 불필요함 확인
		}

		/* close external render path if osd is disabled */
		if(!enable)
		{
            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x08, ext_render_ctrl->hwparam.command);
		}

		FBDEV_HW_NOTI("fb(%d) ext_renderer %s\n", fb_dev_id, (enable)? "enabeld":"disabled");

		/* see SICDTV-8491 : report estreamer visibility */
		hw_ctx->user_initcall_ctrl.status.osd_estreamer = enable;
		FBDEV_E60_CMN_NotifyToPQEDriver();

		// see SICDTV_9891 : if PQE only output path, DO NOT control fb(1) visibility
		if(hw_ctx->hw_ext_render_output_path == FB_E60_EXT_RENDER_PQE_PATH
		   && !(hw_ctx->hw_ext_render_debug_osd_output)) return RET_OK;
	}

	xnum = FBDEV_E60_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
	/* ignore noisy warning msg becase some OSD layer is not supported by HW */
	FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

	val = (enable)? 0x1: 0x0;
	FBDEV_HW_DEBUG("fb(%d) xlst=(%d,%d) view = <%s>\n", fb_dev_id, xlst[0], xlst[1], (enable)? "on":"off");


	for (i=0; i<xnum; i++)
	{
		UINT32 paramex[4];

		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

		paramex[0] = val;
		paramex[1] = afbc_xlst[0];
		paramex[2] = afbc_xlst[1];

		FBDEV_E60_CMN_SetupHWFunc(HWSETUP_OSD_VIEW_CTRL, xidx, paramex);
	}

	return RET_OK;
}

/** disable all active OSD path (hide all OSDs)
 *
 */
static void FBDEV_E60_CMN_ShutdownOSDPath (void)
{
	int		i;
	int		fb_dev_id;
	int		xidx;
	int		xnum, xlst[2], afbc_xlst[2];

	for (fb_dev_id=0; fb_dev_id<LX_FBDEV_ID_MAX; fb_dev_id++ )
	{
		if(g_fbdev_cfg->fb[fb_dev_id].b_active)
		{
			FBDEV_NOTI("shutdown fb(%d)\n", fb_dev_id);

			xnum = FBDEV_E60_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
			/* ignore noisy warning msg becase some OSD layer is not supported by HW */
			FBDEV_CHECK_CODE(INVALID_XNUM(xnum), continue, "invalid fb(%d)\n", fb_dev_id);

			for (i=0; i<xnum; i++)
			{
				UINT32 paramex[4];

				xidx = xlst[i];
				FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), continue, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

				paramex[0] = 0; /*off*/
				paramex[1] = afbc_xlst[0];
				paramex[2] = afbc_xlst[1];
				paramex[3] = 0x0;

				FBDEV_E60_CMN_SetupHWFunc(HWSETUP_OSD_VIEW_CTRL, xidx, paramex);
			}
		}
	}
}

/** OSD HW Layer status
 *
 * wparam	void
 * @return	int 1 : ON , 0 : OFF
 *
 */
int FBDEV_E60_CMN_GetOSDEnable(int fb_dev_id)
{
	UINT32 val;
	int	xidx;
	int	xnum, xlst[2];

	xnum = FBDEV_E60_CMN_GetHWXList(fb_dev_id, xlst);
	// ignore noisy warning msg becase some OSD layer is not supported by HW
	if(INVALID_XNUM(xnum)) return FALSE;

	// (2019/05/21) -- event though OSD requires two POSD for 4K display, we can just check the first POSD value
	xidx = xlst[0];
	FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

	// (주의) 임시로 sync_en 을 끌 수 있기 때문에, 이 함수는 osd_en 값만 참조토록 한다
	OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_main);
	OSDX_CTRL_E60_Rd01(xidx, osd_ctrl_main, osd_en, val);

	return val;
}

int		FBDEV_E60_CMN_SetViewCtrl ( LX_FBDEV_VIEW_CTRL_T* ctrl )
{
	int i;
	ULONG flags;

	/* we can't do spinlock when pivot mode is enabled because sleep ocurrs during GFX merge */
	spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
		if (ctrl->view_status[i] == 0x0 || ctrl->view_status[i] == 0x1)
		{
			FBDEV_E60_CMN_SetOSDEnable(i, ctrl->view_status[i]);
		}
	}

	spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);

    return RET_OK;
}

/** set OSD out connection ctrl
 *
 *	param pConnCtrl [IN] connection control data
 *	@return RET_OK if success, RET_ERROR otherwise
 *
 */
int     FBDEV_E60_CMN_SetConnCtrl           (LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
	int     i;
	BOOLEAN osd_view_status[LX_FBDEV_ID_MAX];

	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	FBDEV_NOTI("OSD conn change. conn_type 0x%x (%s disp)\n", pConnCtrl->conn_type, (g_fbdev_cfg->uhd_disp_mode)? "UHD":"FHD" );

	FBDEV_CHECK_DEBUG(hw_ctx->hw_conn_type == pConnCtrl->conn_type, return RET_OK, "ignore the dup calls (0x%x)\n", pConnCtrl->conn_type);

	/* save current config. diable OSD before changing OSD config */
	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
		osd_view_status[i] = FBDEV_E60_GetOSDEnable(i);
		FBDEV_E60_SetOSDEnable(i, FALSE );
	}

	/* disable ISR to change ISR source */
	FBDEV_E60_SetInterruptEnable(MIXER_INTR, FALSE);

	/* sleep until OSD stablized. not necessary to sleep in E60 */

	if (pConnCtrl->conn_type & LX_FBDEV_CONN_OSD_VIDEO_SEPARATE)
	{
		FBDEV_HW_DEBUG("E60::S.OSD\n");

		hw_ctx->hw_disp_width	= hw_ctx->sosd_disp.out_width;
		hw_ctx->hw_disp_height	= hw_ctx->sosd_disp.out_height;
	}
	else if(pConnCtrl->conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		FBDEV_HW_DEBUG("E60::B.OSD\n");

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
	FBDEV_E60_CMN_ReInitHW();

	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
	    FBDEV_WriteOSDHeader(&g_dm_ctx->wctx[i]->pixel);
	}

func_exit:
	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
		FBDEV_E60_SetOSDEnable(i, osd_view_status[i]);
	}

	return RET_OK;
}

/** control OSD SR (Picture Enhancement)
 *  - on/off
 *  - filter update
 *	- etc
 *
 */
int		FBDEV_E60_CMN_SRCtrl			(BOOLEAN onoff)
{
	FBDEV_E60_CMN_SetupSRScaler(onoff, TRUE);
	return RET_OK;
}

/*========================================================================================
    Implementation Group (VOSD emulation)
========================================================================================*/
/** handle osd scaler workaround during reverse screen
 *
 *	this workaround makes OSD scaler output to be similar to GFX.
 *	so this workaround code should run only when framebuffer is scaled up !!
 *
 */
void	FBDEV_E60_CMN_HandleReverseOSD ( int fb_dev_id, struct scanvas* canvas, FBDEV_E60_OSD_HDR_T* osd_hdr )
{
#ifdef FBDEV_E60_USE_REV_HW_CTRL
	// TODO: if reverse screen handler if needed
#endif
}

static void	FBDEV_E60_CMN_WaitForVsync(int wait_cnt)
{
#define	USE_EXT_RENDER_VSYNC_WAIT	/* I don't know which is better between vsync wait and sleep :( */

#ifdef USE_EXT_RENDER_VSYNC_WAIT
	int rc;
	ULONG flags;
	UINT32 vsync_usec_timeout;

#if CONFIG_LX_BOARD_FPGA
#define FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT    4000000 /* max 4M us = 4000 ms = 0.25 fps */
#else
#define FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT    50000   /* max 50,000 us = 50 ms = 20 fps */
#endif

	FBDEV_CHECK_ERROR(wait_cnt<=0, wait_cnt=1, "invalid wait_cnt=%d\n", wait_cnt);

	vsync_usec_timeout = FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT*wait_cnt;

	spin_lock_irqsave(&fbev_chip_vsync_spinlock, flags);
	fbdev_chip_vsync_cnt = wait_cnt;
	spin_unlock_irqrestore(&fbev_chip_vsync_spinlock, flags);

	rc = wait_event_interruptible_timeout (fbdev_chip_vsync_wq, fbdev_chip_vsync_cnt == 0, usecs_to_jiffies(vsync_usec_timeout));

	FBDEV_CHECK_ERROR(rc == 0 && fbdev_chip_vsync_cnt, /* nop */, "vsync timeout\n");
 	FBDEV_CHECK_ERROR(rc < 0, /* nop */, "vsync abort by signal\n");
#else
	UINT32 sleep_us;
	FBDEV_CHECK_ERROR(wait_cnt<=0, wait_cnt=1, "invalid wait_cnt=%d\n", wait_cnt);

	sleep_us = 16600*wait_cnt;
	usleep_range(sleep_us, sleep_us);
#endif
}

/** VOSD ISR handler
 *
 *
 */
void     FBDEV_E60_CMN_ISRHook ( void )
{
	ULONG flags;

	spin_lock_irqsave(&fbev_chip_vsync_spinlock, flags);
	if (fbdev_chip_vsync_cnt>0 && --fbdev_chip_vsync_cnt <=0)
	{
		wake_up_interruptible_all(&fbdev_chip_vsync_wq);
	}
	spin_unlock_irqrestore(&fbev_chip_vsync_spinlock, flags);

	/* do nothing */
}

/*========================================================================================
    Implementation Group (DIAG/PROC)
========================================================================================*/
void	FBDEV_E60_CMN_RegDebugTag (UINT32 base, UINT32 off, UINT32 val, const char* func, const int line)
{
	/* remove noisy print such as intr clear */
	if((base+off) == 0xc9034880) return;

	FBDEV_E60_REG_DEBUG("WR 0x%08x 0x%08x (0x%08x + 0x%08x) @ %s:%d\n", base+off, val, base, off, func, line);
}

/** HW status
 *
 *  read register(s) to get some HW status
 *	return value seems to be boolean value but there might be exceptions
 *	read comments before using the functioin
 *
 */
int      FBDEV_E60_CMN_GetHWStatus       (FBDEV_E60_HW_STATUS_T status, UINT32 opt)
{
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();
	int	val = 0;

	switch(status)
	{
		/* return 1 if HW is set to AFBC configuration. otherwise return 0 */
		case FBDEV_E60_HW_STATUS_AFBC:
		{
			OSD_CCO1_TOP_E60_RdFL(ctrl_dpath);

			if (opt == LX_FBDEV_ID_OSD0)
			{
				OSD_CCO1_TOP_E60_Rd01(ctrl_dpath, osd0_afbc_en, val);
			}
			else if (opt == LX_FBDEV_ID_OSD1)
			{
                /* raxis.lim (2019/12/27)
                 * if 4KOSD is enabled, both AFBC0 and AFBC1 is used for fb(0), so fb(1) should always use ARGB only
                 */
                if(hw_ctx->b_support_4kosd)
                {
                    val = 0; /* afbc not active */
                }
                else
				{
					OSD_CCO1_TOP_E60_Rd01(ctrl_dpath, osd1_afbc_en, val);
				}
			}
			else
			{
				val = 0;
			}
		}
		break;

		case FBDEV_E60_HW_STATUS_VISIBLE:
		{
			val = FBDEV_E60_CMN_GetOSDEnable(opt);
		}
		break;

		case FBDEV_E60_HW_STATUS_SR_GAIN:
		{
			SHP_CTRL_RdFL(0, shp_lti_ctrl_00);
			SHP_CTRL_Rd01(0, shp_lti_ctrl_00, reg_lti_2d_gain, val);
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
 *  dump important paramters and valiate settings. this function will help to view HW status
 *	(usage) cat /proc/lg/fbdev/chip/diag
 *
 */
void FBDEV_E60_CMN_DiagHW(struct seq_file* m)
{
	FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

	/* print HW core info */
	{
		seq_printf(m, "disp.path: %s\n", 		(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? "bosd":"sosd");
		seq_printf(m, "disp.width: %d\n", 		hw_ctx->hw_disp_width );
		seq_printf(m, "disp.height: %d\n", 		hw_ctx->hw_disp_height);
		seq_printf(m, "\n");
		seq_printf(m, "disp.uhd_mode: %d\n", 	FBDEV_E60_CMN_IsUHDDispMode()? 1:0 );
		seq_printf(m, "fb0.width: %d\n", 		hw_ctx->hw_fb0_width);
		seq_printf(m, "fb0.height: %d\n", 		hw_ctx->hw_fb0_height);
		seq_printf(m, "fb1.width: %d\n", 		hw_ctx->hw_fb1_width);
		seq_printf(m, "fb1.height: %d\n", 		hw_ctx->hw_fb1_height);
		seq_printf(m, "\n");
		seq_printf(m, "vsync_clk: %dHz\n",		(FBDEV_E60_CMN_DetectVSyncClk()==FBDEV_VSYNC_CLK_60HZ)? 60: 120);

		seq_printf(m, "support_ext_frc: %d\n",	hw_ctx->b_support_ext_frc);
		seq_printf(m, "support_fb1: %d\n",		hw_ctx->b_support_fb1);
		seq_printf(m, "support_4kosd: %d\n",	hw_ctx->b_support_4kosd);
		seq_printf(m, "support_ext_render: %d\n",	hw_ctx->b_support_ext_render);

#ifdef FBDEV_E60_USE_SR_CTRL
		seq_printf(m, "\n");
		seq_printf(m, "sr_ctrl[0].status: 0x%08x\n",	hw_ctx->sr_ctrl[0].status);
		seq_printf(m, "sr_ctrl[0].ti_gain: 0x%08x\n",	hw_ctx->sr_ctrl[0].ti_gain);
		seq_printf(m, "sr_ctrl[1].status: 0x%08x\n",	hw_ctx->sr_ctrl[1].status);
		seq_printf(m, "sr_ctrl[1].ti_gain: 0x%08x\n",	hw_ctx->sr_ctrl[1].ti_gain);
#endif
		seq_printf(m, "\n");
		seq_printf(m, "mirror.status: 0x%08x\n",	hw_ctx->mirror_ctrl.status);
		seq_printf(m, "\n");
		seq_printf(m, "ext_render.output_path: %s%s\n", (hw_ctx->hw_ext_render_output_path & FB_E60_EXT_RENDER_PQE_PATH)? "PQE":" ",
 														(hw_ctx->hw_ext_render_output_path & FB_E60_EXT_RENDER_OSD_PATH)? ",OSD":" ");
		seq_printf(m, "ext_render.width: %d\n", 		hw_ctx->hw_ext_render_width);
		seq_printf(m, "ext_render.height: %d\n", 		hw_ctx->hw_ext_render_height);
		seq_printf(m, "ext_render.bpp: %d\n", 			hw_ctx->hw_ext_render_bpp);
		seq_printf(m, "ext_render.debug.xoffset: %d\n",	hw_ctx->hw_ext_render_debug_xoffset);
		seq_printf(m, "ext_render.debug.osd_output: %d\n",	hw_ctx->hw_ext_render_debug_osd_output);
		seq_printf(m, "\n");
		seq_printf(m, "ext_render.regbase: 0x%08x\n",		FBDEV_OS0_EXT_RENDER_REG_BASE);
		seq_printf(m, "ext_render.fbmem: 0x%08x,0x%08x\n",	hw_ctx->ext_render_ctrl.fbmem_phys[0], hw_ctx->ext_render_ctrl.fbmem_phys[1]);
		seq_printf(m, "ext_render.hwparam.phys_y: 0x%08x\n",hw_ctx->ext_render_ctrl.hwparam.phys_y);
		seq_printf(m, "ext_render.hwparam.size: 0x%08x\n",	hw_ctx->ext_render_ctrl.hwparam.size);
		seq_printf(m, "ext_render.hwparam.xoffset: %d\n",	hw_ctx->ext_render_ctrl.hwparam.xoffset);
		seq_printf(m, "ext_render.hwparam.yoffset: %d\n",	hw_ctx->ext_render_ctrl.hwparam.yoffset);
		seq_printf(m, "ext_render.hwparam.enable: %d\n",	hw_ctx->ext_render_ctrl.hwparam.enable);
		seq_printf(m, "ext_render.hwparam.crop_x: %d\n",	hw_ctx->ext_render_ctrl.hwparam.crop_x);
		seq_printf(m, "ext_render.hwparam.crop_y: %d\n",	hw_ctx->ext_render_ctrl.hwparam.crop_y);
		seq_printf(m, "ext_render.hwparam.crop_w: %d\n",	hw_ctx->ext_render_ctrl.hwparam.crop_w);
		seq_printf(m, "ext_render.hwparam.crop_h: %d\n",	hw_ctx->ext_render_ctrl.hwparam.crop_h);
		seq_printf(m, "ext_render.hwparam.tx_count: %d\n",	hw_ctx->ext_render_ctrl.hwparam.tx_count);
		seq_printf(m, "ext_render.swsync.swsync.interval_tick_us: %d\n", (int)hw_ctx->ext_render_ctrl.swsync.interval_tick_us);

		seq_printf(m, "\n");
		seq_printf(m, "osd_shp_auto_cfg.osd_res: %d\n", (int)hw_ctx->osd_shp_auto_cfg_ctrl.hwparam.osd_res);

		seq_printf(m, "\n");
		seq_printf(m, "hw_wa.1x_csr_disp_on_blend_path: 0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_1X_CSR_DISP_ON_BLEND_PATH)? 1:0);
		seq_printf(m, "hw_wa.osd0_async_wr_error:       0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)? 1:0);
		seq_printf(m, "hw_wa.pqwfw_osd0_out_ctrl:       0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL)? 1:0);
		seq_printf(m, "hw_wa.pause_pqwfw_osd0_out_ctrl: 0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)? 1:0);
		seq_printf(m, "hw_wa_flag:                      0x%x\n",hw_ctx->hw_wa_flag);
		seq_printf(m, "\n");
	}

#if FBDEV_E60_NOT_IMPL("일단 막자")
	/* print OSD_SHP info */
	{
		int	xidx;
		int xnum, xlst[2];
		int	fb_dev_id = LX_FBDEV_ID_OSD0;

		UINT32 bypass_en, detour_en, rgb2yc_csc_en, yc2rgb_bosd_csc_en;
		FBDEV_E60_SR_CTRL_T* sr_ctrl = FBDEV_E60_GET_SR_CTRL(hw_ctx,fb_dev_id);

		xnum = FBDEV_E60_CMN_GetHWXList(fb_dev_id, xlst);
		FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

		xidx = xlst[0];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

		OSDX_CTRL_E60_RdFL(xidx, osd_bitmap_ctrl0);
		SHP0_CTRL_RdFL(shp_core_ctrl_00);

		SHP0_CTRL_Rd01(shp_core_ctrl_00, reg_top_bypass, bypass_en);

		seq_printf(m, "osd_sr.sw_status: 0x%x\n", sr_ctrl->status);
		seq_printf(m, "osd_sr.hw_status: 0x%x\n", (!bypass_en && !detour_en));
		seq_printf(m, "\n");
	}
#endif

#if FBDEV_E60_NOT_IMPL("일단 막자")
	/* afbc mux status */
	{
		int xidx = 1; /* OSD_IMAGE0_1 */

		UINT32 osd_4k_mux;

		OSDX_E60_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0);
		OSDX_E60_Rd01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0, reg_4k_mode_en, osd_4k_mux);

		seq_printf(m, "4kosd.muxcfg: 0x%x\n", osd_4k_mux);
	}
#endif

	/* print HW_CTX status */

	/* TODO: add something */
}

/** chip specific proc handler
 *
 */
void FBDEV_E60_CMN_ProcHandler(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case FBDEV_HW_PROC_ID_DETAIL_INFO:
		{
			FBDEV_E60_HW_CTX_T* hw_ctx = FBDEV_E60_GET_HW_CTX();

			seq_printf(m, "<HW INFO>\n");
			seq_printf(m, "path: %s\n", 			(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? "bosd":"sosd");
			seq_printf(m, "hw_disp_width: %d\n", 	hw_ctx->hw_disp_width );
			seq_printf(m, "hw_disp_height: %d\n", 	hw_ctx->hw_disp_height);
			seq_printf(m, "hw_fb0_width: %d\n", 	hw_ctx->hw_fb0_width);
			seq_printf(m, "hw_fb0_height: %d\n", 	hw_ctx->hw_fb0_height);
			seq_printf(m, "vsync_clk: %dHz\n",		(FBDEV_E60_CMN_DetectVSyncClk()==FBDEV_VSYNC_CLK_60HZ)? 60: 120);

			seq_printf(m, "support_ext_frc: %d\n",	hw_ctx->b_support_ext_frc);
			seq_printf(m, "support_4kosd: %d\n",	hw_ctx->b_support_4kosd);

			seq_printf(m, "fb_scale_mode: %d\n",	hw_ctx->hw_fb_scale_mode);
		}
		break;

		case FBDEV_HW_PROC_ID_OSD_HDR:
		{
			int	i;
			int xidx;
			int xnum, xlst[2];

			UINT32 	osd_en, sync_en;
			UINT32	hdr_lst[7];
			FBDEV_E60_OSD_HDR_T* osd_hdr = (FBDEV_E60_OSD_HDR_T*)hdr_lst;
			LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

			xnum = FBDEV_E60_CMN_GetHWXList(fb_dev_id, xlst);
			seq_printf(m, "posd_num: %d\n", xnum);
			for (i=0; i<xnum && VALID_XIDX(xlst[i]); i++)
			{
				xidx = xlst[i];

				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_main);

TODO_NOTE("sync_enable 은 각 layer 별로 서로 다른 이름으로, 쓰고 있어 차후에 다시 생각할것")
#if 0
				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_sync0);
#endif

				OSDX_CTRL_E60_Rd01(xidx, osd_ctrl_main, osd_en, osd_en);
#if 0
				OSDX_CTRL_E60_Rd01(xidx, osd_ctrl_sync0,osd_sync_enable, sync_en);
#endif
				sync_en = 1;

				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr0);
				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr1);
				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr2);
				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr3);
				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr4);
				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr5);
				OSDX_CTRL_E60_RdFL(xidx, osd_ctrl_hdr6);

				hdr_lst[0] = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr0);
				hdr_lst[1] = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr1);
				hdr_lst[2] = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr2);
				hdr_lst[3] = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr3);
				hdr_lst[4] = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr4);
				hdr_lst[5] = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr5);
				hdr_lst[6] = OSDX_CTRL_E60_Rd(xidx, osd_ctrl_hdr6);

				seq_printf(m, "posd_idx: %d\n",				xidx);
				seq_printf(m, " visible: %s (osd:%d, sync:%d)\n", (osd_en && sync_en)? "on":"off", osd_en, sync_en);
				seq_printf(m, " hdr.xpos: %d\n", 			osd_hdr->osd_hdr_xpos);
				seq_printf(m, " hdr.ypos: %d\n", 			osd_hdr->osd_hdr_ypos);
				seq_printf(m, " hdr.w_mem: %d\n", 			osd_hdr->osd_hdr_w_mem);
				seq_printf(m, " hdr.h_mem: %d\n", 			osd_hdr->osd_hdr_h_mem);
				seq_printf(m, " hdr.w_out: %d\n", 			osd_hdr->osd_hdr_w_out);
				seq_printf(m, " hdr.h_out: %d\n", 			osd_hdr->osd_hdr_h_out);
				seq_printf(m, " hdr.pixel_order: 0x%x\n", 	osd_hdr->osd_hdr_pixel_order);
				seq_printf(m, " hdr.wpl: %d\n",		 		osd_hdr->osd_hdr_wpl);
				seq_printf(m, " hdr.global_alpha_en: %d\n", osd_hdr->osd_hdr_global_alpha_en);
				seq_printf(m, " hdr.global_alpha: 0x%x\n", 	osd_hdr->osd_hdr_global_alpha);
				seq_printf(m, " hdr.color_key_en: %d\n", 	osd_hdr->osd_hdr_color_key_en);
				seq_printf(m, " hdr.color_key: 0x%x\n", 	osd_hdr->osd_hdr_color_key);
				seq_printf(m, " hdr.ptr_plte: 0x%x\n", 		osd_hdr->osd_hdr_ptr_plte);
				seq_printf(m, " hdr.ptr_bmp: 0x%x\n", 		osd_hdr->osd_hdr_ptr_bmp);
			}
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
                { .desc = "OSD", 		 .reg_base = E60_CCO_BASE,					.reg_size = sizeof(OSD_E60_REG_T) }, //1536 }, //sizeof(OSD_E60_REG_T) },
                { .desc = "CCO1_TOP",	.reg_base = E60_CCO1_TOP_CTRL_BASE,		.reg_size = sizeof(OSD_CCO1_TOP_E60_REG_T) }, //256 }, //sizeof(OSD_CCO1_TOP_E60_REG_T) },
                { .desc = "CCO2_TOP",	.reg_base = E60_CCO2_TOP_CTRL_BASE,		.reg_size = sizeof(OSD_CCO2_TOP_E60_REG_T) }, //256 }, //sizeof(OSD_CCO1_TOP_E60_REG_T) },
                { .desc = "AFBC0",		.reg_base = E60_CCO_AFBC0_BASE,			.reg_size = sizeof(OSD_AFBC_E60_REG_T) }, //256 }, //sizeof(OSD_AFBC_E60_REG_T) },
                { .desc = "AFBC1",		.reg_base = E60_CCO_AFBC1_BASE,			.reg_size = sizeof(OSD_AFBC_E60_REG_T) }, //256 }, //sizeof(OSD_AFBC_E60_REG_T) },
#ifdef FBDEV_E60_SUPPORT_SHP_CTRL
#error
                { .desc = "SHP0", .reg_base = E60_CCO_SHP0_BASE,			.reg_size = sizeof(OSD_SHP_E60_REG_T) }, //768 }, //sizeof(OSD_SHP_E60_REG_T) },
                { .desc = "SHP1", .reg_base = E60_CCO_SHP1_BASE,			.reg_size = sizeof(OSD_SHP_E60_REG_T) }, //768 }, //sizeof(OSD_SHP_E60_REG_T) },
#endif
                { .desc = "MIF0", .reg_base = E60_CCO_MIF0_BASE,			.reg_size = 0xc0 },
                { .desc = "MIF1", .reg_base = E60_CCO_MIF1_BASE,			.reg_size = 0xc0 },
			};

            for (i=0; i<NELEMENTS(reg_list); i++)
            {
                seq_printf(m, "\n\n");
                seq_printf(m, "FBDEV (%s) : 0x%08x (size=%d)\n", reg_list[i].desc, reg_list[i].reg_base, reg_list[i].reg_size);

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
int	FBDEV_E60_CMN_RunResume	( void )
{
	/* OSD freeze will be stopped after 500 ms */
	FBDEV_E60_CMN_RunBootLogoTimer(fbdev_resume_freeze_timeout, TRUE);

	FBDEV_E60_CMN_ReInitHW( );

	return RET_OK;
}

int	FBDEV_E60_CMN_RunSuspend	( void )
{
	/* do nothing */
	return RET_OK;
}

/*========================================================================================
	common OSD HW handler
========================================================================================*/
FBDEV_E60_HW_FUNC_T  g_fbdev_e60_cmn_hw_func =
{
	/* variable is initialize at fbdev_drv_E60.c */

    .E60_InitHW			 = FBDEV_E60_CMN_InitHW,

	.E60_SetViewCtrl	 = FBDEV_E60_CMN_SetViewCtrl,
    .E60_SetConnCtrl     = FBDEV_E60_CMN_SetConnCtrl,

    .E60_WriteOSDHeader  = FBDEV_E60_CMN_WriteOSDHeader,
    .E60_SetOSDEnable    = FBDEV_E60_CMN_SetOSDEnable,
    .E60_GetOSDEnable    = FBDEV_E60_CMN_GetOSDEnable,
};

