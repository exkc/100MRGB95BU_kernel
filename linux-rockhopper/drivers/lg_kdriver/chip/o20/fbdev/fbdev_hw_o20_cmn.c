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
#undef	V_MIRROR_TEST	/* 임시 코드임. 테스트시에만 임시로 풀어서 사용할것. CCC 에는 지울것 */

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_drv.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "fbdev_hw_o20.h"
#include "osd_reg_o20.h"
#include "osd_shp_reg_o20.h"
#include "osd_afbc_reg_o20.h"
#include "osd_top_reg_o20.h"
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/seq_file.h>
#include <linux/fb.h>

#include "hma_alloc.h"

#ifdef FBDEV_O20_USE_CTOP_REGS
#include "../sys/sys_regs.h"
#endif

#ifdef INCLUDE_KDRV_OVI
#include "be_kapi.h"
#endif

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
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
static void FBDEV_O20_CMN_InitFBCEnv	(void);
#ifdef FBDEV_O20_USE_FBC_CTRL
static void FBDEV_O20_CMN_SetupFBC		(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt);
#endif

static void FBDEV_O20_CMN_InitCropEnv	(void);
static void FBDEV_O20_CMN_SetupSRScaler	(BOOLEAN onoff, BOOLEAN bForce);

static void FBDEV_O20_CMN_OpenExternalRenderer(int fb_dev_id, struct fb_info* fbinfo);

static void	FBDEV_O20_CMN_ReInitHW		(void);
static void FBDEV_O20_CMN_InitMirrorEnv	(void);
static int FBDEV_O20_CMN_WriteOSDHeader (struct scanvas *pCanvas);
static FBDEV_VSYNC_CLK_T FBDEV_O20_CMN_DetectVSyncClk(void);

static void FBDEV_O20_CMN_NotifyToPQEDriver(void);
static int	FBDEV_O20_CMN_WaitForPQEDriverInitialization(void);

static void FBDEV_O20_CMN_BootLogoClearScheduler(struct work_struct *work);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_osd_hdr_spinlock);

static struct workqueue_struct *fbdev_o20_wq;
static DECLARE_DELAYED_WORK (boot_logo_clear_work, FBDEV_O20_CMN_BootLogoClearScheduler);

static int	fbdev_boot_freeze_timeout	= 0;	/* see SICDTV-8491. set 0 by default */
static int	fbdev_resume_freeze_timeout = 0;	/* see SICDTV-8491. set 0 by default */
static int	fbdev_pqefw_osd0_out_ctrl 	= 1;	/* SICDTV-4359 */
static int	fbdev_osd0_user_out_win 	= 0;	/* SICDTV-4359 */

static int	fbdev_enable_logo_clear			= 0;	/* see SICDTV-8556 */
static int	fbdev_boot_logo_clear_timeout	= 3000;	/* see SICDTV-8556 */
static int	fbdev_resume_logo_clear_timeout	= 2000;	/* see SICDTV-8556 */

static BOOLEAN fbdev_logo_migration_required = TRUE;

module_param_named( fbdev_o20_boot_freeze_timeout,	fbdev_boot_freeze_timeout, int, 0644 );
module_param_named( fbdev_o20_resume_freeze_timeout,fbdev_resume_freeze_timeout, int, 0644 );

module_param_named( fbdev_o20_pqefw_osd0_out_ctrl, 	fbdev_pqefw_osd0_out_ctrl, int, 0644 );
module_param_named( fbdev_o20_osd0_user_out_win, 	fbdev_osd0_user_out_win, int, 0644 );

module_param_named( fbdev_o20_enable_logo_clear, 		fbdev_enable_logo_clear, 		int, 0644 );
module_param_named( fbdev_o20_boot_logo_clear_timeout, 	fbdev_boot_logo_clear_timeout, 	int, 0644 );
module_param_named( fbdev_o20_resume_logo_clear_timeout,fbdev_resume_logo_clear_timeout,int, 0644 );

/* TEST */
#define	CHECK_REGS(id)	__check_regs(id, __FUNCTION__,__LINE__)

static void __check_regs(int id, const char* func, const int line)
{
	if (id == LX_FBDEV_ID_OSD0)
	{
		UINT32	shp_w, shp_h;
		UINT32	osd_w_out, osd_h_out;
		UINT32	crop_en, crop_w, crop_h;

		int	xidx = 0;
		FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

		SHP0_CTRL_RdFL(shp_core_ctrl_01);

		SHP0_CTRL_Rd01(shp_core_ctrl_01, reg_top_width, shp_w);
		SHP0_CTRL_Rd01(shp_core_ctrl_01, reg_top_height, shp_h);

		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_w_out, osd_w_out);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_h_out, osd_h_out);

		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_0);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_crop_en, crop_en);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_in_pic_width, crop_w);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_in_pic_height,crop_h);

		if(!(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL))
		{
			FBDEV_NOTI("@%s:%d shp_ctrl.w=%d,h=%d, osd_hdr2.w=%d,h=%d crop_ctrl.en=%d,w=%d,h=%d\n", func, line,
				shp_w, shp_h, osd_w_out, osd_h_out, crop_en, crop_w, crop_h);
		}
		else
		{
			FBDEV_HW_NOTI("@%s:%d shp_ctrl.w=%d,h=%d, osd_hdr2.w=%d,h=%d crop_ctrl.en=%d,w=%d,h=%d\n", func, line,
				shp_w, shp_h, osd_w_out, osd_h_out, crop_en, crop_w, crop_h);
		}
	}
}

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
int	FBDEV_O20_CMN_GetHWXList(int fb_dev_id, int xlst[2])
{
	int	afbc_xlst[2];

	return FBDEV_O20_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
}

int	FBDEV_O20_CMN_GetHWXListEx(int fb_dev_id, int xlst[2], int afbc_xlst[2])
{
	int	num_xlst = 0;
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	switch( fb_dev_id )
	{
		case LX_FBDEV_ID_OSD0:
		{
			if (hw_ctx->b_support_4kosd){num_xlst=2; xlst[0] = 0; xlst[1] = 1; afbc_xlst[0] = 0; afbc_xlst[1] = 1;}
			else 						{num_xlst=1; xlst[0] = 0; xlst[1] =-1; afbc_xlst[0] = 0; afbc_xlst[1] =-1;}
		}
		break;

		case LX_FBDEV_ID_OSD1:
		{
			if (hw_ctx->b_support_4kosd){num_xlst=0; xlst[0] = 2; xlst[1] =-1; afbc_xlst[0] =-1; afbc_xlst[1] =-1;}
			else						{num_xlst=1; xlst[0] = 2; xlst[1] =-1; afbc_xlst[0] = 1; afbc_xlst[1] =-1;}
		}
		break;

		case LX_FBDEV_ID_CSR0:  num_xlst=1; xlst[0] = 3; xlst[1] =-1; afbc_xlst[0] =-1; afbc_xlst[1] =-1; break;
		default:				num_xlst=0; xlst[0] =-1; xlst[1] =-1; afbc_xlst[0] =-1; afbc_xlst[1] =-1; break;
	}

	return num_xlst;
}

BOOLEAN  FBDEV_O20_CMN_IsUHDDispMode  (void)
{
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	return (hw_ctx->hw_disp_width > 2048)? TRUE:FALSE;
}

#ifdef FBDEV_O20_USE_FBC_CTRL
/* calculate AFBC headr size
 * this function is copied from GAL_TEST_AFBC_HEADER_SIZE() @ kadaptor/gal/gal_kadp_impl.h
 *
 */
#define AFBC_PREFERRED_BODY_ALIGN_BYTE	(1<<10)
#define AFBC_HEADER_CLUMP_SIZE_BYTE		(16)
#define AFBC_ALIGN(value, align) 		((value + (align -1))& ~(align-1))

static UINT32	FBDV_O20_CMN_GetAFBCHdrSize	(int w, int h)
{
    int number_block;
    int width;
    int height;

    width  = AFBC_ALIGN(w, AFBC_HEADER_CLUMP_SIZE_BYTE);
    height = AFBC_ALIGN(h, AFBC_HEADER_CLUMP_SIZE_BYTE);
    number_block = width * height / (AFBC_HEADER_CLUMP_SIZE_BYTE * AFBC_HEADER_CLUMP_SIZE_BYTE);

    return AFBC_ALIGN(number_block * AFBC_HEADER_CLUMP_SIZE_BYTE, AFBC_PREFERRED_BODY_ALIGN_BYTE);
}

static UINT32	FBDV_O20_CMN_GetAFBCImageSize	(int w, int h)
{
    int number_block;
    int width;
    int height;

    width  = AFBC_ALIGN(w, AFBC_HEADER_CLUMP_SIZE_BYTE);
    height = AFBC_ALIGN(h, AFBC_HEADER_CLUMP_SIZE_BYTE);
    number_block = width * height / (AFBC_HEADER_CLUMP_SIZE_BYTE * AFBC_HEADER_CLUMP_SIZE_BYTE);

    return width*height*4 + AFBC_ALIGN(number_block * AFBC_HEADER_CLUMP_SIZE_BYTE, AFBC_PREFERRED_BODY_ALIGN_BYTE);
}

#endif

#ifdef FBDEV_O20_USE_REVERSE_HW_CTRL
/** check if current OSD HW is set as the reverse mode
 *
 */
static BOOLEAN	FBDEV_O20_CMN_IsReverseMode	( int fb_dev_id )
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
static void FBDEV_O20_CMN_EnableOSDHdrFlush( ULONG data )
{
    int i;

 	FBDEV_NOTI("<!> enable osd_hdr_flush & exit OSD freeze stage. afbc=%d\n",
			 FBDEV_O20_CMN_GetHWStatus(FBDEV_O20_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0));

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

		FBDEV_NOTI("++ fb(%d) flip_cnt = %d, total_flip_cnt = %d\n",
					i, wctx->status.fb_flip_cnt, wctx->status.total_fb_flip_cnt);

		wctx->status.b_osd_hdr_flush = TRUE;

		/* (2020/06/11)
		 * 수정된 OSD 초기화 정책에 의하여 이 함수는 단순히 b_osd_hdr_flush 를 활성화 하는 역할로
		 * 축소한다. 향후 함수 목적을 수정하거나, 완전히 삭제할 수도 있음
		 */
		/* do nothing */
	}
}

/** override the default boot_freeze_timeout
 *
 */
void FBDEV_O20_CMN_SetBootFreezeTimeout(int val)
{
	if(fbdev_boot_freeze_timeout != val)
	{
		printk("+ boot_freeze_timeout %d -> %d\n", fbdev_boot_freeze_timeout, val);
		fbdev_boot_freeze_timeout = val;
	}
}

/** clear current logo screen after a few seconds after OSD initialization
 *
 */
static void FBDEV_O20_CMN_BootLogoClearScheduler(struct work_struct *work)
{
	FBDEV_NOTI("logo clear work started\n");
	fbdev_logo_migration_required = TRUE;
	FBDEV_O20_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_CLEAR);
}

/** move boot logo framebuffer to safe region (prototype implementation)
 *
 */
void		FBDEV_O20_CMN_MigrateBootLogo	(FBDEV_O20_BOOT_LOGO_MODE_T mode)
{
#define OSD_CTRL_BASE(layer)	((UINT32)(O20_CCO_BASE + 0x200 + (0x100*(layer))))

	int	i;
	int	rc;
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

	image_size = FBDV_O20_CMN_GetAFBCImageSize(1920,1080);
	image_size = AFBC_ALIGN(image_size, (1<<20));

	FBDEV_CHECK_CODE(0!=hma_pool_info("surface", &dst_rgn_base, &dst_rgn_size),
						return, "dst buffer not found");

	/* read OSD0 framebuffer */
	rc = OS_RdReg(O20_CCO_BASE+0x238, &fbmem_addr_src);
	FBDEV_CHECK_CODE(rc!=RET_OK, goto func_exit, "reg op fail\n");
	FBDEV_WARN("logo fbmem (old) = 0x%08x\n", fbmem_addr_src);

	/* move to last part of new region becuase this region isnot used at boot time */
	fbmem_addr_dst = (UINT32)(dst_rgn_base + dst_rgn_size - image_size);
	fbmem_addr_clr = (UINT32)(dst_rgn_base + dst_rgn_size - image_size*2);

	afbc_mode = (FBDEV_O20_CMN_GetHWStatus(FBDEV_O20_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0))? 1:0;

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
		rc = OS_WrReg(O20_CCO_AFBC0_BASE+0x004, fbmem_addr_dst);
		FBDEV_CHECK_CODE(rc!=RET_OK, goto func_exit, "reg op fail\n");

		AFBC_CTRL_Wr01(0, ctrl_afbc_1, hd_base, 	 fbmem_addr_dst);
		AFBC_CTRL_Wr01(0, ctrl_afbc_8, pl_data_base, fbmem_addr_dst);
		AFBC_CTRL_WrFL(0, ctrl_afbc_1);
		AFBC_CTRL_WrFL(0, ctrl_afbc_8);

		rc = OS_WrReg(O20_CCO_AFBC0_BASE+0x020, fbmem_addr_dst);
		FBDEV_CHECK_CODE(rc!=RET_OK, goto func_exit, "reg op fail\n");

		/* raxis.lim (2019/10/23)
		 * becuase hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
		 * we should set hdr_ready_flag=1 here to update real framebuffer address
		 */
		AFBC_CTRL_RdFL(0, ctrl_afbc_0);
		AFBC_CTRL_Wr01(0, ctrl_afbc_0, update_ready_flag, 0x1);
		AFBC_CTRL_WrFL(0, ctrl_afbc_0);
	}

	/* update OSD framebuffer */
	for (i=0; i<FBDEV_O20_MAX_OSD_BLK_NUM; i++)
	{
		OS_WrReg(OSD_CTRL_BASE(i)+0x004, fbmem_addr_dst);	// osd_base_addr
		OS_WrReg(OSD_CTRL_BASE(i)+0x034, fbmem_addr_dst);	// osd_ctrl_hdr5.ptr_plte
		OS_WrReg(OSD_CTRL_BASE(i)+0x038, fbmem_addr_dst);	// osd_ctrl_hdr6.ptr_bmp
	}

	/* raxis.lim (2019/10/23)
	 * becuase osd_hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
	 * we should set osd_hdr_ready_flagn=1 here to update real framebuffer address
	 */
	OSDX_O20_RdFL(osdx_ctrl[0], osd_ctrl_main);
	OSDX_O20_Wr01(osdx_ctrl[0], osd_ctrl_main, osd_hdr_ready_flag_en, 1);
	OSDX_O20_Wr01(osdx_ctrl[0], osd_ctrl_main, osd_hdr_ready_flag, 1);
	OSDX_O20_WrFL(osdx_ctrl[0], osd_ctrl_main);

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
}

/**
 *
 */
void FBDEV_O20_CMN_RunBootLogoTimer(UINT32 ms, BOOLEAN bForce)
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
			OS_StartTimer( &osd_en_timer, FBDEV_O20_CMN_EnableOSDHdrFlush, OS_TIMER_TIMEOUT, ms, 0x0 );
		}
		else
		{
			FBDEV_O20_CMN_EnableOSDHdrFlush(0x0);
		}
	}
#else
	FBDEV_O20_CMN_EnableOSDHdrFlush(0x0);
#endif
}

/** query tcon clk information & detect vsync clk interval
 *
 *  @note this function should be called after SYS kdriver initialization
 */
static FBDEV_VSYNC_CLK_T FBDEV_O20_CMN_DetectVSyncClk(void)
{
#ifdef FBDEV_O20_USE_CTOP_REGS
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

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

	/* 2K display mode */
	if(hw_ctx->hw_disp_width <= 2048)
	{
		FBDEV_NOTI("<temp> FHD display mode.. default vsync = 60Hz \n");
		return FBDEV_VSYNC_CLK_60HZ;
	}
	/* 4K display mode */
	else
	{
		FBDEV_NOTI("VSYNC detection = %d (%dHz)\n", tcon_pix2_clk, (tcon_pix2_clk==0 || tcon_pix2_clk==2)? 120:60);
		return (tcon_pix2_clk == 0x0 || tcon_pix2_clk == 0x2) ? FBDEV_VSYNC_CLK_120HZ: FBDEV_VSYNC_CLK_60HZ;
	}
#else
	FBDEV_NOTI("SYNC detector not ready.. default vsync = 60Hz \n");
	return FBDEV_VSYNC_CLK_60HZ;
#endif
}

static void FBDEV_O20_CMN_NotifyToPQEDriver(void)
{
#ifdef INCLUDE_KDRV_OVI
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	/* see be/top/be_top_hal.h */
	extern int BE_TOP_HAL_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T *pstParams);
	LX_BE_FBDEV_STATUS_T osd2pqe_status;

	osd2pqe_status.bFbdevInitDone = hw_ctx->user_initcall_ctrl.status.osd_init_done;
	osd2pqe_status.bOsdVReverseOn = hw_ctx->user_initcall_ctrl.status.osd_v_mirror;
	osd2pqe_status.bEStreamerOn   = hw_ctx->user_initcall_ctrl.status.osd_estreamer;
	osd2pqe_status.b4kOSDResolution = (hw_ctx->b_support_4kosd)? TRUE:FALSE;
	osd2pqe_status.bOsdSharpnessWAOn = (hw_ctx->hw_fb0_ex_height>0)? TRUE:FALSE;

	FBDEV_NOTI("+ notify PQE FW to setup : inited=%d, 4kosd=%d, vmirror=%d, est=%d, shpwa=%d\n",
		osd2pqe_status.bFbdevInitDone,
		osd2pqe_status.b4kOSDResolution,
		osd2pqe_status.bOsdVReverseOn,
		osd2pqe_status.bEStreamerOn,
		osd2pqe_status.bOsdSharpnessWAOn);

	FBDEV_CHECK_ERROR(RET_OK!=BE_TOP_HAL_InformFBDEVStatus(&osd2pqe_status), /* nop */, "BE_TOP_HAL_InformFBDEVStatus error\n");
#endif
}

static int	FBDEV_O20_CMN_WaitForPQEDriverInitialization(void)
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

/** initialize HW SOC
 *
 *
 */
int	FBDEV_O20_CMN_InitHW ( void )
{
	int	i;
	UINT32 disp_width, disp_height;
	FBDEV_O20_HW_CTX_T*	hw_ctx = FBDEV_O20_GET_HW_CTX();

	int	sosd_num = 1;
	int	bosd_num = 2;
	BOOLEAN	osd_shp_en = TRUE; /* turn on OSD_SR by default */

	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> user_initcall not ready +++\n");

	disp_width = hw_ctx->hw_disp_width;
	disp_height= hw_ctx->hw_disp_height;

	FBDEV_HW_DEBUG("(Re)Init OSD(O20) HW.. disp_size %dx%d\n", disp_width, disp_height);

	/* initialize S.OSD & B.OSD mixer disp size */
	for (i=0; i<sosd_num; i++)
	{
		OSDX_O20_RdFL(osdx_sep_osd_mixer[i], ctrl_sosd_mixer_disp_size);
		OSDX_O20_Wr02(osdx_sep_osd_mixer[i], ctrl_sosd_mixer_disp_size,	reg_sosd_disp_size_w, hw_ctx->sosd_disp.out_width,
																		reg_sosd_disp_size_h, hw_ctx->sosd_disp.out_height);
		OSDX_O20_WrFL(osdx_sep_osd_mixer[i], ctrl_sosd_mixer_disp_size);
	}

	for (i=0; i<bosd_num; i++)
	{
		OSDX_O20_RdFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size);
		OSDX_O20_Wr02(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size,	reg_bosd_disp_size_w, hw_ctx->bosd_disp.out_width,
																			reg_bosd_disp_size_h, hw_ctx->bosd_disp.out_height);
		OSDX_O20_WrFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size);
	}

	/* setup all OSD common disp size */
	for (i=0; i< FBDEV_O20_MAX_OSD_DISP_NUM /*8*/; i++)
	{
		OSD_O20_RdFL(osdx_common_disp_size[i]);
		OSD_O20_Wr02(osdx_common_disp_size[i],	reg_common_disp_size_w, disp_width,
								  				reg_common_disp_size_h, disp_height);
		OSD_O20_WrFL(osdx_common_disp_size[i]);
	}


	/* O20 has the fixed mux value. DO NOT change */
	{
		UINT32 mixer_mux_value = 0x76543210;
		FBDEV_NOTI("(Re)Init OSD(O20) mixer mux order = 0x%08x\n", mixer_mux_value );

		OSDX_O20_Wr(osdx_sep_osd_mixer[0], 		ctrl_sosd_mixer_mux1, mixer_mux_value);
		OSDX_O20_WrFL(osdx_sep_osd_mixer[0],	ctrl_sosd_mixer_mux1);

	    OSDX_O20_Wr(osdx_blend_osd_mixer[0],	ctrl_bosd_mixer_mux1, mixer_mux_value);
		OSDX_O20_WrFL(osdx_blend_osd_mixer[0],	ctrl_bosd_mixer_mux1);

	    OSDX_O20_Wr(osdx_blend_osd_mixer[1],	ctrl_bosd_mixer_mux1, mixer_mux_value);
		OSDX_O20_WrFL(osdx_blend_osd_mixer[1],	ctrl_bosd_mixer_mux1);
	}

	/* raxis.lim (2014/11/11) tune osd sync pulse timer
	 * CCO_CTRL.CTRL_SOSD_PLUS.reg_disp_sosd_timer controls the delay the OSD mix start time in cycle unit.
	 * OSD HW engineer recommend to use 0x3000 (almost 10 line delay) can fix OSD sync & isr mismatch issue.
	 *
	 * value 0x3000 has been determinted at H15 development
	 *
	 * raxis.lim (2016/03/28) set bosd_pulse as 0x3000 (used at O20 for the first time)
	 *
	 */
	OSD_TOP_O20_RdFL(ctrl_sosd_pulse);
	OSD_TOP_O20_Wr01(ctrl_sosd_pulse, reg_disp_pulse_timer, hw_ctx->sosd_disp.pulse_timer_dly );
	OSD_TOP_O20_WrFL(ctrl_sosd_pulse);

	OSD_TOP_O20_RdFL(ctrl_bosd_pulse);
    OSD_TOP_O20_Wr01(ctrl_bosd_pulse, reg_disp_pulse_timer, hw_ctx->bosd_disp.pulse_timer_dly );
	OSD_TOP_O20_WrFL(ctrl_bosd_pulse);

	/* raxis.lim (2020/04/20)
	 * when 4K OSD is enabled, turn off OSD_SR because HW is specialized for 2K to 4K upscaling
	 * when Non UHD display mode, turn off OSD_SR
	 */
	if(hw_ctx->b_support_4kosd || !FBDEV_O20_CMN_IsUHDDispMode() )
	{
		osd_shp_en = FALSE;
	}

	FBDEV_NOTI("initial OSD_SR=%d (4k_osd=%d,uhd_disp=%d)\n", osd_shp_en, hw_ctx->b_support_4kosd, FBDEV_O20_CMN_IsUHDDispMode());
	FBDEV_O20_CMN_SetupSRScaler(osd_shp_en, TRUE);

	FBDEV_O20_CMN_InitMirrorEnv();
	FBDEV_O20_CMN_InitCropEnv();
	FBDEV_O20_CMN_InitFBCEnv();

	return RET_OK;
}

/** make OSD to be initial state
 *	make the basic configuration for each OSD layer.
 *
 *	@param layerId
 */
int FBDEV_O20_CMN_InitOSDLayer ( int fb_dev_id )
{
	int	i;
	int	xidx;
	int xnum, xlst[2];
	int ret = RET_ERROR;

	/* please refer to OSD manual OSD<x>_CFG field */
	UINT32  hdr_src_sel;
	UINT32  osd_memhdr_addr;
	BOOLEAN	osd_en = 0x0;			/* off by default */
	BOOLEAN	hdr_rdy_flag = 0x0;		/* OFF by default */
	BOOLEAN v_mirror_en = 0x0;		/* OFF by default */

	FBDEV_O20_HW_CTX_T*	hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_O20_MIRROR_CTRL_T* mirror_ctrl = FBDEV_O20_GET_MIRROR_CTRL(hw_ctx);

	/* fetch the current output disp size */
	UINT32	disp_width = hw_ctx->hw_disp_width;
	UINT32	disp_height= hw_ctx->hw_disp_height;

	/* if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration)  */
	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> fb(%d) user_initcall not ready +++\n", fb_dev_id);

	FBDEV_NOTI("fb(%d) configure osd layer\n", fb_dev_id);

	xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id );

	/* hdr_src_sel 0x0: DDR, 0x1: REG */
	hdr_src_sel	= (g_fbdev_hwio_cfg->hdr_op_method == FBDEV_HDR_OP_MMIO)? 0x0: 0x1;
	osd_memhdr_addr = (gMemCfgFBHdr[fb_dev_id].mem_header_base);

	v_mirror_en = (mirror_ctrl->status & FBDEV_O20_V_MIRROR_ON)? 0x1: 0x0;

	/* choose the initial osd visibility based on boot logo configuration */
	switch(fb_dev_id)
	{
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==0)
		case LX_FBDEV_ID_OSD0:	osd_en = 0x1; break;
#endif
		default:				osd_en = 0x0; break;
	}
#ifdef FBDEV_O20_USE_HDR_RDY_REG
	hdr_rdy_flag = 0x1;
#endif

	for (i=0; i<xnum; i++)
	{
		UINT32	sync_disp_width;
		UINT32	sync_hdouble_en;
		UINT32	ctrl_direc;

		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), goto func_exit, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

		/* raxis.lim (2016/03/28)
		 * if BLEND mode, each OSD layer should have a half of real disp size. (it's HW spec)
		 * this restruction is also applied to the cursor layer.
		 *
		 */
		sync_disp_width = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? disp_width/2 : disp_width;

		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_pdec);
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_swap);
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_base_addr);
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_sync1);
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_scaler);


		/* (2020/12/15) remove the early osd_en control
		 * osd will be enabled after the frist image update is completed
		 * see FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE handler
		 * see http://clm.lge.com/issue/browse/SICDTV-9043
		 * see http://hlm.lge.com/qi/browse/INQAISSUE-81
		 */
#if 0
		/* OSD HW requests to write both osd_en & osd_sync_enable to control osd visibility */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main, 	osd_en,			osd_en);
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0,	osd_sync_enable,osd_en);
#endif

		/* raxis.lim (2014/06)
		 * if BLEND mode, each OSD layer should have a half of real display size (it's HW spec)
		 * this restruction is also applied to the cursor layer.
		 */
		sync_hdouble_en = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0x0: 0x1;

		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_hdouble_en, sync_hdouble_en);

		/* use osd_hdr_flag to avoid the possible OSD mis-configuration when OSD header is set across vsync */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_ready_flag_en, hdr_rdy_flag );

		/* normally osd_hdr_src_sel is fixed to "read from hw register" not "DDR contains osd_hdr data" */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_hdr_src_sel,		hdr_src_sel );

		/* configure mirror mode every layer initialization */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en,		v_mirror_en );

		/* configure CSR0 sync for mirror mode to support virtically reversed position */
		if(fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_CSR0)
		{
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_v_reverse, v_mirror_en );
		}

		/* we should set DDR memory to hold osd_hdr data, but NOT used in normal case
		 * remember that OSD always fetch header data from DDR regardless of hdr_src_sel value
		 * it's safe that I set the same address as the frame buffer
		 */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_base_addr, 	osd_base_addr, osd_memhdr_addr);

		#if 0 /* KEEP HW DEFAULT */
		/* set scaler sample mode to the same behavior as that of GFX */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler,osd_sc_sampling_mode,	0x1 );
		#endif

		/* initialize cursor attribute (OSD4 only) */
		if(fb_dev_id == LX_FBDEV_ID_CSR0)
		{
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler,reg_crsr_h_x2_en,	0x0 );
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler,reg_crsr_v_x2_en,	0x0 );
		}

		/* MIF feeder cfg : "10 (0x2)" L to R (HW default value)
		 * this value has ben fixed to "10" inside OSD HW since older chip.
		 * In O20/O20, this value can be configurable by SW But I keep this value as 0x2 forever
		 *
		 * HW default value = 0x2
		 */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main,	osd_manual_dlr,		0x2 );

		/* raxis.lim (2019/10/17) -- fix pdec & swap configuration. re-write HW default again.
		 *
		 * pdec=0xe4000000, swap=0x000 equals pdec=0x1b000000, swap=0x333
		 *
		 */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_alpha,			0x0 );
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_red,				0x1 );
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_green,			0x2 );
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_ch_blue,			0x3 );
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_round,				0x0 );
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_pure_ck,			0x0 );
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_pdec,	osd_lfsr_seed,			0x0 );

		OSDX_O20_Wr  (osdx_ctrl[xidx], osd_ctrl_swap, 	0x00000333);

#ifdef FBDEV_O20_USE_EXPERIMENTAL_CONFIG
		/* raxis.lim (2018/04/09)
		 * according to register manual, reg_osd_buf_mode_en enables for OSD to use scaler memory as extra line memory
		 * during 1:1 non-scaler mode.
		 * when UHD display mode, FHD image is always scaled to UHD-sized output image. so it's good to set osd_buf_mode_en as 0x0.
		 * when FHD display mode, FHD image is not scaled, so it's good to set osd_buf_mode_en as 0x1
		 *
		 * @note refer to SICDTV-4852
		 *
		 */
		if (fb_dev_id == LX_FBDEV_ID_OSD0 && xidx == 0x0)
		{
			UINT32 buf_mode_en = (FBDEV_O20_CMN_IsUHDDispMode())? 0x0: 0x1;
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_scaler,reg_osd_buf_mode_en_n, buf_mode_en);
		}
#endif


		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_main );
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_pdec );
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_swap );
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_base_addr );
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_scaler );
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0 );

		/* TODO: add more initialization if necessary */

		/* setup OSD basic path & sync. primary osd only.
		 *
		 * raxis.lim (2019/05/21)
	 	 * OSD_IMAGE0_1 doesn't have osd_ctrl_path, osd_ctrl_sync etc
		 */
		if(i==0x0)
		{
			OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_path );
			ctrl_direc = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0x0: 0x1;
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_direc, ctrl_direc);
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_eo2s,  ctrl_direc);

			/* setup each display size(?).
			 * keep in mind that width value osd_ctrl_path, osd_ctrl_sync1 is NOT real disp_width.
	 		 * they should be set a half when B.OSD is activated.
			 * these field is used to control how OSD fetch & process OSD frame data.
			 */
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_path, reg_ctrl_path_width,		sync_disp_width);
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_path, osd_ctrl_bosd_pos,		0x0 );	/* fixed to 0x0(BOSD1) */
			OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_path );

			OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_sync1 );
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_sync1, osd_sync_disp_w,	sync_disp_width);
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_sync1, osd_sync_disp_h,	disp_height);
			OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_sync1 );
		}

		/* setup 4K osd configuration. OSD_IMAGE0_1 only */
		if(hw_ctx->b_support_4kosd && fb_dev_id == LX_FBDEV_ID_OSD0 && i == 0x1 /* second posd */)
		{
			OSDX_O20_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0);
			OSDX_O20_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_1);
			OSDX_O20_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
			OSDX_O20_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3);

			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0, reg_4k_mode_en, 1);
			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_w, hw_ctx->hw_fb0_width);
			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_h, hw_ctx->hw_fb0_height);
			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3, reg_sc_o_w, disp_width);
			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3, reg_sc_o_h, disp_height);

			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_1, reg_4k_xpos, 0);
			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_1, reg_4k_ypos, 0);

			OSDX_O20_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0);
			OSDX_O20_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_1);
			OSDX_O20_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
			OSDX_O20_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_3);
		}

#if 1
		/* see SICDTV-7971 */
		if(fb_dev_id == LX_FBDEV_ID_OSD0)
		{
			int	disp_width = hw_ctx->hw_disp_width;
			int	disp_height= hw_ctx->hw_disp_height;
			int	osd_ex_h = hw_ctx->hw_fb0_ex_height;
			int	osd_ex_out_h = hw_ctx->hw_fb0_ex_out_height;

			if (osd_ex_h>0 && osd_ex_out_h>0)
			{
				FBDEV_NOTI("fb(%d) setup osd_post_crop_ctrl_0~3 \n", fb_dev_id);

				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_0);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_1);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_2);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_post_crop_ctrl_3);

				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_crop_en, 1);
				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_in_pic_width, disp_width);
				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_0, reg_in_pic_height,disp_height+osd_ex_out_h);

				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_1, hoffset, 0);
				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_1, hactive, disp_width);

				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_2, voffset, 0);
				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_2, vactive, disp_height);

				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_3, crop_mixer_xpos, 0);
				OSDX_O20_Wr01(osdx_ctrl[xidx], osd_post_crop_ctrl_3, crop_mixer_ypos, 0);

				OSDX_O20_WrFL(osdx_ctrl[xidx], osd_post_crop_ctrl_0);
				OSDX_O20_WrFL(osdx_ctrl[xidx], osd_post_crop_ctrl_1);
				OSDX_O20_WrFL(osdx_ctrl[xidx], osd_post_crop_ctrl_2);
				OSDX_O20_WrFL(osdx_ctrl[xidx], osd_post_crop_ctrl_3);
			}
		}
#endif
	}

	CHECK_REGS(fb_dev_id);

    ret = RET_OK;   /* all work done */
func_exit:
	return ret;
}

static void FBDEV_O20_CMN_SafeSyncEnable(void)
{
	FBDEV_O20_HW_CTX_T*	hw_ctx = FBDEV_O20_GET_HW_CTX();

	/* if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration) */
	FBDEV_CHECK_ERROR(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");

	FBDEV_WARN("++ PIC_INIT ++ (I-BOOT)\n");

	/* raxis.lim (2019/08/07) -- DO NOT full value to pic_init. refer to http://clm.lge.com/issue/browse/AVTASK-386?focusedCommentId=1964037&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-1964037
	*/
	OSD_TOP_O20_RdFL(pic_init);
	OSD_TOP_O20_Wr01(pic_init, g0_auto_init, 0x1);
	OSD_TOP_O20_Wr01(pic_init, g1_auto_init, 0x1);
	OSD_TOP_O20_Wr01(pic_init, g4_auto_init, 0x1);
	OSD_TOP_O20_WrFL(pic_init);
}

static void FBDEV_O20_CMN_ReInitHW (void)
{
	FBDEV_O20_HW_CTX_T*	hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");

	FBDEV_O20_InitHW();
	FBDEV_SetInterruptEnable(MIXER_INTR,1);

	/* O20 OSD supports only OSD0, OSD1 & OSD3 */
	FBDEV_O20_InitOSDLayer(LX_FBDEV_ID_OSD0);
	FBDEV_O20_InitOSDLayer(LX_FBDEV_ID_OSD1);
	FBDEV_O20_InitOSDLayer(LX_FBDEV_ID_OSD3);

    /* refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT */
    if (hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)
    {
		FBDEV_O20_CMN_SafeSyncEnable();
    }
}

int	FBDEV_O20_CMN_ExecHWCommand	(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data)
{
	int	ret = RET_NOT_SUPPORTED;
	FBDEV_O20_HW_CTX_T*	hw_ctx = FBDEV_O20_GET_HW_CTX();

	switch(cmd)
	{
		case FBDEV_HW_CMD_IO_POST_HW_INIT:
		{
			fbdev_o20_wq = alloc_workqueue("fbdev_o20_events", 0, 0);

			if (fbdev_enable_logo_clear)
			{
				FBDEV_NOTI("start logo clear work after %dms\n", fbdev_boot_logo_clear_timeout);
				queue_delayed_work(fbdev_o20_wq, &boot_logo_clear_work, msecs_to_jiffies(fbdev_boot_logo_clear_timeout));
			}
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_IO_POSD_OPEN:
		{
			int fbdev_id = data->gen[0];
			struct fb_info* fbinfo = (struct fb_info*)data->genex[0];

			FBDEV_HW_DEBUG("fb(%d) POSD_OPEN..\n", fbdev_id);
			FBDEV_O20_CMN_RunBootLogoTimer(fbdev_boot_freeze_timeout, FALSE);

			FBDEV_O20_CMN_OpenExternalRenderer(fbdev_id, fbinfo);

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
				hw_ctx->hw_wa_flag |= FBDEV_O20_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL;
			}
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_IO_VSYNC:
		{
			FBDEV_O20_CMN_ISRHook();
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_RD_VSYNC_CLK:
		{
			/* raxis.lim (2019/11/21)
			 *
			 * I should check if S.OSD is active becuase S.OSD is set to fixed 60Hz display
			 * regardless of OVI check value.
			 * remember that I can call FBDEV_O20_CMN_DetectVSyncClk() only when B.OSD is active.
			 */
			if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
			{
				data->gen[0] = FBDEV_O20_CMN_DetectVSyncClk();
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
				data->gen[1]=(hw_ctx->b_support_ext_fb1_renderer)? 1/*ARGB*/ : 2/*AFBC*/;
				data->gen[2]=(hw_ctx->b_support_ext_fb1_renderer)? FBDEV_O20_EXT_RENDER_EGL_FBDEV_NUM : 0 /*system default*/;

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
			hw_ctx->hw_wa_flag &= ~FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL;
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_SUSPEND:
		{
			/* raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL to re-enable at FBDEV_O20_CMN_EnableOSDHdrFlush() during RESUME */
			hw_ctx->hw_wa_flag &= ~FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL;
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_THAW:
		{
			/* raxis.lim (2017/09/18) -- enable PQEFW_OSD0_OUT_CTRL here becuase THAW stage doesn't configure any HW registers */
			hw_ctx->hw_wa_flag |= FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL;
			FBDEV_WARN("OSD0_PQEFW_OSD0_OUT_CTRL enabled\n");
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_RESTORE:
		{
			/* boot logo migration is also required during snapshot boot */
			fbdev_logo_migration_required = TRUE;
			FBDEV_O20_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_KEEP);

			if (fbdev_enable_logo_clear)
			{
				FBDEV_NOTI("start logo clear work after %dms (resume mode)\n", fbdev_resume_logo_clear_timeout);
				queue_delayed_work(fbdev_o20_wq, &boot_logo_clear_work, msecs_to_jiffies(fbdev_resume_logo_clear_timeout));
			}

			/* (2010/06/11) re-activate lazy-init at snapshot boot */
			hw_ctx->user_initcall_ctrl.ready = FALSE;
			hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

			/* raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute. it will be enabled at FBDEV_O20_CMN_EnableOSDHdrFlush() */

			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_PREPARE_RESUME:
		{
			/* raxis.lim (2017/08/22) -- fix for async behavior of OSD0_SYNC group */
			hw_ctx->hw_wa_flag |= FBDEV_O20_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
			FBDEV_WARN("OSD0_SYNC_ASYNC_WR enabled\n");

			/* (2010/06/11) re-activate lazy-init at QSM+ resume */
			hw_ctx->user_initcall_ctrl.ready = FALSE;
			hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

			/* raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute. it will be enabled at FBDEV_O20_CMN_EnableOSDHdrFlush() */
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_PM_COMPLETE:
		{
			hw_ctx->hw_wa_flag &= ~FBDEV_O20_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
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
				FBDEV_O20_CMN_ReInitHW();
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
				FBDEV_O20_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

				if (hw_ctx->b_support_ext_frc || hw_ctx->hw_disp_width <= 2048)
				{
					fbdev_pqefw_osd0_out_ctrl = 0;
					hw_ctx->hw_wa_flag &= ~FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL;
					FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL disabled\n");
				}
				else
				{
					hw_ctx->hw_wa_flag |= FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL;
					FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
				}

				hw_ctx->user_initcall_ctrl.status.osd_init_done= 1;
				hw_ctx->user_initcall_ctrl.status.osd_v_mirror = (mirror_ctrl->status==FBDEV_O20_V_MIRROR_ON)? 1:0;
				hw_ctx->user_initcall_ctrl.status.osd_estreamer= 0;

				CHECK_REGS(fbdev_id);
				FBDEV_O20_CMN_NotifyToPQEDriver();

				base_tick = OS_GetMsecTicks();
				for (i=0; i<10; i++)
				{
					// if (FW done) break;
					FBDEV_CHECK_NOTI( (int)(OS_GetMsecTicks()-base_tick) > 100 /*100ms*/,
						break, "+ wait timeout\n");

					if(RET_OK==FBDEV_O20_CMN_WaitForPQEDriverInitialization()) break;
					CHECK_REGS(fbdev_id);
					msleep_interruptible(10);
				}

				CHECK_REGS(fbdev_id);
				FBDEV_O20_CMN_SetOSDEnable(fbdev_id, TRUE);
			}
			ret = RET_OK;
		}
		break;


		case FBDEV_HW_CMD_RD_EXTERNAL_RENDERER_INFO:
		{
			if(hw_ctx->b_support_ext_fb1_renderer)
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

			FBDEV_O20_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O20_GET_EXT_RENDER_CTRL(hw_ctx);

			FBDEV_CHECK_CODE(fbdev_id != LX_FBDEV_ID_OSD1, break, "fb(%d) ext_renderer not supported\n", fbdev_id);
			FBDEV_CHECK_CODE(hw_ctx->b_support_ext_fb1_renderer == FALSE,  break, "fb(%d) ext_renderer not supported\n", fbdev_id);

			ext_render_ctrl->hwparam.crop_x	= cx;
			ext_render_ctrl->hwparam.crop_y	= cy;
			ext_render_ctrl->hwparam.crop_w	= cw;
			ext_render_ctrl->hwparam.crop_h	= ch;

			FBDEV_NOTI("++ configure external renderer crop %d,%d,%d,%d\n", cx, cy, cw, ch);
			ret = RET_OK;
		}
		break;

		case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE:
		{
			int	   fbdev_id	= data->gen[0];
			UINT32 phys_y 	= data->gen[1];
			int    xoffset	= data->gen[2];

			FBDEV_O20_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O20_GET_EXT_RENDER_CTRL(hw_ctx);

			FBDEV_CHECK_CODE(fbdev_id != LX_FBDEV_ID_OSD1, break, "fb(%d) ext_renderer not supported\n", fbdev_id);
			FBDEV_CHECK_CODE(hw_ctx->b_support_ext_fb1_renderer == FALSE,  break, "fb(%d) ext_renderer not supported\n", fbdev_id);

			ext_render_ctrl->hwparam.phys_y	= phys_y;
			ext_render_ctrl->hwparam.size	= (hw_ctx->hw_ext_render_width <<16) | (hw_ctx->hw_ext_render_height);
			ext_render_ctrl->hwparam.xoffset= xoffset;

			/* raxis.lim (2019/09/27) fake vsync */
			{
				UINT64 sleep_tick_us= 0;
				UINT64 curr_tick_us = OS_GetUsecTicks();
				UINT64 diff_tick_us = curr_tick_us - ext_render_ctrl->swsync.request_tick_us;

				if (diff_tick_us < ext_render_ctrl->swsync.interval_tick_us)
				{
					sleep_tick_us = ext_render_ctrl->swsync.interval_tick_us - diff_tick_us;
					//FBDEV_NOTI("++ usleep %d us\n", (int)sleep_tick_us);
					usleep_range(sleep_tick_us, sleep_tick_us);
				}

				OS_RdReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x0c, &ext_render_ctrl->hwparam.tx_count);

				FBDEV_NOTI("++ write external renderer y:0x%08x sz:0x%08x cmd:0x%08x crop:%d,%d,%d,%d (xoff:%d, en:%d) - sleep: %dus tx_count: %d\n",
					ext_render_ctrl->hwparam.phys_y,
					ext_render_ctrl->hwparam.size,
					ext_render_ctrl->hwparam.command,
					ext_render_ctrl->hwparam.crop_x,
					ext_render_ctrl->hwparam.crop_y,
					ext_render_ctrl->hwparam.crop_w,
					ext_render_ctrl->hwparam.crop_h,
					ext_render_ctrl->hwparam.xoffset,
					ext_render_ctrl->hwparam.enable,
					(int)sleep_tick_us,
					ext_render_ctrl->hwparam.tx_count);
			}

            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x00, ext_render_ctrl->hwparam.phys_y);
            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x04, ext_render_ctrl->hwparam.size);

            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0xce0, ext_render_ctrl->hwparam.crop_xy);
            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0xce4, ext_render_ctrl->hwparam.crop_wh);

            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x08, ext_render_ctrl->hwparam.command);

			ext_render_ctrl->swsync.request_tick_us = OS_GetUsecTicks();
			ret = RET_OK;
		}
		break;

		/* PQE PM framework callback */
		case FBDEV_HW_CMD_WR_PQE_PM_RUNTIME_ACTION:
		{
#ifdef INCLUDE_KDRV_PQE_PM
			int pqe_pm_action =  data->gen[0];

			if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_PREPARE)
			{
				/* TODO: 테스트 하기에 OSD 를 끄는게 도움이 될 수도 있음 */
				FBDEV_O20_CMN_SetOSDEnable(LX_FBDEV_ID_OSD3, FALSE);
				FBDEV_O20_CMN_SetOSDEnable(LX_FBDEV_ID_OSD1, FALSE);
				FBDEV_O20_CMN_SetOSDEnable(LX_FBDEV_ID_OSD0, FALSE);
				FBDEV_PM_DEBUG("hide all OSD layer for safe operation\n");

				OS_WrReg(0xC9010000,0x0); //CCO_CTRL - PIC_INIT
			}
			else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND)
			{

			}
			else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_COMPLETED)
			{

			}
			else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_PREPARE)
			{

			}
			else if (pqe_pm_action == PQE_PM_DEVICE_RESUME)
			{
				OS_WrReg(0xC9010000,0x00FF0000); //CCO_CTRL - PIC_INIT//move to each module
			}
			else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_COMPLETED)
			{
				/* TODO: 필요시 OSD0 에 대하여 enable 시킬 수도 있음 */

			}
			else
			{
				// not supported action
			}
#endif
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
static void FBDEV_O20_CMN_OpenExternalRenderer(int fb_dev_id, struct fb_info* fbinfo)
{
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_O20_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O20_GET_EXT_RENDER_CTRL(hw_ctx);

	if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_fb1_renderer == TRUE)
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
			int fbmem_sz = hw_ctx->hw_ext_render_width * hw_ctx->hw_ext_render_height * FBDEV_O20_EXT_RENDER_CHANNEL;
			ext_render_ctrl->fbmem_phys[0] = (UINT32)hma_alloc("surface", fbmem_sz*2, PAGE_SIZE);

			#if 0
			if(ext_render_ctrl->fbmem_phys[0]==0x0)
			{
				ext_render_ctrl->fbmem_phys[0] = (UINT32)hma_alloc("photofb", fbmem_sz*2, PAGE_SIZE);
			}
			#endif

			FBDEV_CHECK_CODE(ext_render_ctrl->fbmem_phys==0x0, return, "can't alloc external render fbmem\n");

			ext_render_ctrl->fbmem_phys[1] = ext_render_ctrl->fbmem_phys[0] + fbmem_sz;
		}

		ext_render_ctrl->swsync.interval_tick_us = 1000000/hw_ctx->hw_ext_render_swsync_hz;

		ext_render_ctrl->hwparam.crop_x = 0;
		ext_render_ctrl->hwparam.crop_y = 0;
		ext_render_ctrl->hwparam.crop_w = hw_ctx->hw_ext_render_width;
		ext_render_ctrl->hwparam.crop_h = hw_ctx->hw_ext_render_height;


		FBDEV_NOTI("fb(%d) setup external fbmem=0x%08x,0x%08x sz=%dx%d swsync=%dus\n", fb_dev_id,
			ext_render_ctrl->fbmem_phys[0], ext_render_ctrl->fbmem_phys[1],
			hw_ctx->hw_ext_render_width, hw_ctx->hw_ext_render_height,
			(int)ext_render_ctrl->swsync.interval_tick_us);

		/* raxis.lim (2019/09/27)
		 * remember that struct fb_info* is passed via fbdev_open().
		 * by modifying fb_info, application can query the latest value with FBIOGET_VSCREENINFO ioctl.
		 */
		fbinfo->var.reserved[0] = ext_render_ctrl->fbmem_phys[0];
		fbinfo->var.reserved[1] = ext_render_ctrl->fbmem_phys[1];
		fbinfo->var.reserved[2] = LX_MAKE_RES(hw_ctx->hw_ext_render_width, hw_ctx->hw_ext_render_height);
		fbinfo->var.reserved[3] = 0x0;
	}

}

/** detect current mirror mode configuration set by boot loader
 *
 */
static void FBDEV_O20_CMN_InitMirrorEnv(void)
{
	int	xidx;
	int xnum, xlst[2];
	int	fb_dev_id = LX_FBDEV_ID_OSD0;

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_O20_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

	xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

	xidx = xlst[0];
	FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

	/* raxis.lim (2018/07/02) -- read mirror mode configuration set from boot loader */
	if(mirror_ctrl->status == FBDEV_O20_MIRROR_NONE)
	{
		UINT32 hw_val;

#ifdef V_MIRROR_TEST
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, 0x1);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
#endif
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, hw_val);

		mirror_ctrl->status = (hw_val)? FBDEV_O20_V_MIRROR_ON: 0x0;

		FBDEV_WARN("OSD v_mirror detected (%d)\n", hw_val);
	}
}

static void FBDEV_O20_CMN_SetupSRScaler(BOOLEAN onoff, BOOLEAN bForce)
{
	int	i;
	int	xidx;
	int xnum, xlst[2];
	UINT32 hw_onoff;
	int	fb_dev_id = LX_FBDEV_ID_OSD0;

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_O20_SR_CTRL_T* sr_ctrl = FBDEV_O20_GET_SR_CTRL(hw_ctx,fb_dev_id);

	PARAM_UNUSED(bForce);

	xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

	for (i=0; i<xnum; i++)
	{
		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

		/* raxis.lim (2019/05/21) -- osd_bitmap_ctrl is valid only for primary posd layer */
		if(i != 0x0) continue;

		/* check HW status for debug. hw_onoff is not used yet */
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, hw_onoff);
		hw_onoff ^= 1;
		FBDEV_HW_DEBUG("OSD SR(HW) = %d\n", hw_onoff);

		sr_ctrl->status   = (onoff)? FBDEV_O20_SR_STATUS_ON:FBDEV_O20_SR_STATUS_OFF;

#ifdef FBDEV_O20_USE_SR_CTRL
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
		SHP0_CTRL_RdFL(shp_core_ctrl_01);
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

		SHP0_CTRL_Wr01(shp_core_ctrl_00, reg_top_bypass, (onoff)? 0x0: 0x1);

		/* see SICDTV-7971 */
		if (hw_ctx->hw_fb0_ex_out_height>0)
		{
			FBDEV_NOTI("fb(%d) setup shp_core_ctrl_01\n", fb_dev_id);
			SHP0_CTRL_Wr01(shp_core_ctrl_01, reg_top_width, hw_ctx->hw_disp_width);
			SHP0_CTRL_Wr01(shp_core_ctrl_01, reg_top_height, hw_ctx->hw_disp_height + hw_ctx->hw_fb0_ex_out_height);
		}

		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, (onoff)?0x0:0x1);

		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en, (onoff)?0x1:0x0);
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, (onoff)?0x1:0x0);

		/* S.OSD 에서 OSD SR 사용할건지에 따라 아래 설정은 틀릴지도 모름 */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_sosd_csc_en, (onoff)?0x1:0x0);

		/* M16P3 don't support reg_scaler_status_sel & reg_cubic_coeff_0 */
		#if 0
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_scaler_status_sel, 0x1);	/* why ?? */
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_cubic_coeff_0, 0x0);		/* not used */
		#endif

		SHP0_CTRL_WrFL(shp_core_ctrl_00);
		SHP0_CTRL_WrFL(shp_core_ctrl_01);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

		FBDEV_WARN("OSD SR (%s)\n", (onoff)? "on":"off");
#else
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en, 0x1);
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_rgb2yc_csc_en, 0x0);
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, 0x0);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);

		FBDEV_WARN("OSD SR disabled (%s)\n", "off");
#endif

		CHECK_REGS(fb_dev_id);
	}

	/* if user ti_gain is defined, initialize HW configuration using the last user ti_gain.
	 * otherwise, initialize ti_gain based on HW default value.
	 */
	sr_ctrl->ti_gain = FBDEV_O20_CMN_GetHWStatus(FBDEV_O20_HW_STATUS_SR_GAIN, 0x0);

	FBDEV_HW_DEBUG("fb(0) sr_gain=0x%08x\n", sr_ctrl->ti_gain);
}

/** initialize CROP to the default state.
 *
 */
static void FBDEV_O20_CMN_InitCropEnv	(void)
{
	/* do nothing */
}

/** initialize FBC variable to the default state.
 *	The real HW register will be set inside FBDEV_O20_CMN_WriteOSDHeader()
 *	This function is also called during instant boot resume to setup AFBC register again.
 *
 */
static void FBDEV_O20_CMN_InitFBCEnv(void)
{
#ifdef FBDEV_O20_USE_FBC_CTRL
	int i;
	/* raxis.lim (2010/10/15) -- setup afbc for both fb(0) and fb(1)
	 */
	for (i=0; i<=LX_FBDEV_ID_OSD1; i++)
	{
		FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
		FBDEV_O20_FBC_CTRL_T* fbc_ctrl = FBDEV_O20_GET_FBC_CTRL(hw_ctx,i);
		int hw_afbc_status = 0;

		fbc_ctrl->fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW;
		fbc_ctrl->status  = FBDEV_O20_FBC_STATUS_NONE;
		FBDEV_O20_FBC_DEBUG("fb(%d) initialize fbc env\n", LX_FBDEV_ID_OSD0);

		/* raxis.lim (2016/10/05) -- try to initialize OSD to AFBC graphic path if possible
 		 * boot loader can display both non-AFBC and AFBC logo image, so I should keep the current
		 * graphic configuration.
		 * below codes will be active if cold boot or snapshot boot (not instant boot)
		 *
		 *
		 */
		hw_afbc_status = FBDEV_O20_CMN_GetHWStatus(FBDEV_O20_HW_STATUS_AFBC, i);

		FBDEV_NOTI("fb(%d) initial FBC mode = %d\n", i, hw_afbc_status);

		/* recover FBC if AFBC display is used at boot loader */
		if (hw_afbc_status)
		{
			FBDEV_O20_FBC_DEBUG("fb(%d) recover FBC HW config\n", i);
			FBDEV_O20_CMN_SetupFBC(i, LX_FBDEV_FBC_FORMAT_AFBC);
		}
	}
#else
	/* TODO: do someting if nessary */
#endif
}

#ifdef FBDEV_O20_USE_FBC_CTRL
/** create or destory FBC envrionment
 *
 *
 *
 */
static void FBDEV_O20_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt)
{
	int	i;
	int	xidx;
	int xnum, xlst[2], afbc_xlst[2];

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_O20_FBC_CTRL_T* fbc_ctrl = FBDEV_O20_GET_FBC_CTRL(hw_ctx, fb_dev_id);

	FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

	/* check HW status */
	if (fbc_ctrl->fbc_fmt == fbc_fmt)
	{
#ifdef FBDEV_O20_SW_RECOVERY_AFBC_FLAG_CORRUPTION
		int hw_afbc_status = FBDEV_O20_CMN_GetHWStatus(FBDEV_O20_HW_STATUS_AFBC, fb_dev_id);

		hw_afbc_status = (hw_afbc_status)? LX_FBDEV_FBC_FORMAT_AFBC: LX_FBDEV_FBC_FORMAT_RAW;
		FBDEV_CHECK_CODE(fbc_ctrl->fbc_fmt != hw_afbc_status, goto afbc_config,
						"<!> fb(%d) sw/hw status mismatch (sw:%d, hw:%d)\n", fb_dev_id, fbc_ctrl->fbc_fmt, hw_afbc_status);
#endif
		return; /* same value. do nothing */
	}

#ifdef FBDEV_O20_SW_RECOVERY_AFBC_FLAG_CORRUPTION
afbc_config:
#endif
	xnum = FBDEV_O20_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
	FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

	FBDEV_NOTI("fb(%d) setup afbc_path=%d\n", fb_dev_id, fbc_fmt);

	OSD_TOP_O20_RdFL(ctrl_dpath);
	OSD_TOP_O20_RdFL(ctrl_auto_init_afbc);

	if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
	{
		UINT32 afbc_auto_init_src_val = (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? 0x0: 0x1;
#ifdef FBDEV_O20_USE_AFBC_READ_BW_SAVING
		UINT32 enable = FBDEV_O20_CMN_GetOSDEnable(fb_dev_id);
#else
		UINT32 enable = 1;
#endif

		FBDEV_O20_FBC_DEBUG("setup fbc_fmt = 0x1 (enable AFBC mode)\n");

		if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
		{
			OSD_TOP_O20_Wr01(ctrl_dpath, osd0_afbc_en, 0x1 );
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,		enable);
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en, 	enable);
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, idx_afbc0_pic_init_src,   0x0); /* g0_pic_init. 이건 고정 ? */

			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_src, 	afbc_auto_init_src_val);

			FBDEV_O20_FBC_DEBUG("fb(%d) afbc enabled. xlst=%d,%d view=%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1], enable);
		}

		if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
		{
			OSD_TOP_O20_Wr01(ctrl_dpath, osd1_afbc_en, 0x1 );
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en, 		enable);
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en, 	enable);
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, idx_afbc1_pic_init_src,   0x1); /* g1_pic_init. 이거 선택 가능 ? */

			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_src, 	afbc_auto_init_src_val );

			FBDEV_O20_FBC_DEBUG("fb(%d) afbc enabled. xlst=%d,%d view=%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1], enable);
		}
	}
	else
	{
		FBDEV_O20_FBC_DEBUG("setup fbc_fmt = 0x0 (disable AFBC mode)\n");

		if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
		{
			OSD_TOP_O20_Wr01(ctrl_dpath, osd0_afbc_en, 0x0 );
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,		0x0);
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en, 	0x0);

			FBDEV_O20_FBC_DEBUG("fb(%d) afbc disabled. xlst=%d,%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1]);
		}

		if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
		{
			OSD_TOP_O20_Wr01(ctrl_dpath, osd1_afbc_en, 0x0 );
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en, 		0x0);
			OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en, 	0x0);

			FBDEV_O20_FBC_DEBUG("fb(%d) afbc disabled. xlst=%d,%d\n", fb_dev_id, afbc_xlst[0], afbc_xlst[1]);
		}
	}


	/* setup OSD registers */
	for (i=0; i<xnum && VALID_XIDX(xlst[i]); i++)
	{
		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xidx), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xidx);

		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);

		if (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
		{
			/* enable BITMAP mode */
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main,	osd_bitmap_only_mode_en, 0x1 );

			fbc_ctrl->status |=  FBDEV_O20_FBC_STATUS_PATH_CHANGE;;
		}
		else
		{
			/* disable BITMAP mode (default in raw mode) */
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main,	osd_bitmap_only_mode_en, 0x0 );

			fbc_ctrl->status &= ~FBDEV_O20_FBC_STATUS_HDR_SETUP;
			fbc_ctrl->status |=  FBDEV_O20_FBC_STATUS_PATH_CHANGE;
		}

		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
	}

	/* flush top registers */
	OSD_TOP_O20_WrFL(ctrl_dpath);
	OSD_TOP_O20_WrFL(ctrl_auto_init_afbc);

	/* raxis.lim (2019/05/21) -- I will always configure AFBC to use ready_flag */
	AFBC_CTRL_RdFL(0,ctrl_afbc_0);
	AFBC_CTRL_RdFL(1,ctrl_afbc_0);

	AFBC_CTRL_Wr01(0, ctrl_afbc_0, update_ready_flag_en, 0x1);
	AFBC_CTRL_Wr01(1, ctrl_afbc_0, update_ready_flag_en, 0x1);

	AFBC_CTRL_WrFL(0,ctrl_afbc_0);
	AFBC_CTRL_WrFL(1,ctrl_afbc_0);

	FBDEV_O20_FBC_DEBUG("fb(%d) fbc_mode=0x%x setup\n", fb_dev_id, fbc_fmt);

	fbc_ctrl->fbc_fmt = fbc_fmt;
}

/** setup AFBC register for OSD display
 *
 *
 */
static void FBDEV_O20_CMN_WriteFBCHdrRegs(int fb_dev_id, FBDEV_O20_OSD_HDR_T osd_hdr[2], FBDEV_O20_OSD_EXHDR_T* osd_exhdr)
{
	int	i;
	int	afbc_xidx;
	int	xnum, xlst[2], afbc_xlst[2];

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_O20_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];
	FBDEV_O20_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

	FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

	FBDEV_CHECK_DEBUG(fbc_ctrl->fbc_fmt != LX_FBDEV_FBC_FORMAT_AFBC, return, "fb(%d) non-afbc image\n", fb_dev_id);

	xnum = FBDEV_O20_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
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

		osd_img_stride	= osd_exhdr->img_stride;
		osd_img_bpp 	= FBDEV_O20_BITS_2_BYTES(osd_exhdr->bits_per_pixel);

		afbc_xidx = afbc_xlst[i];

		/* current fb_dev_id is not attached to afbc */
		if(INVALID_AFBC_XIDX(afbc_xidx)) continue;

		/* for dbeug What's AFBC dimension FBDEV_O20_BITS_2_BYTES(canvas.bits_per_pixel);> */
		fbc_hdr_size = FBDV_O20_CMN_GetAFBCHdrSize(osd_img_stride/osd_img_bpp, osd_exhdr->img_height);
		fbc_hdr_addr = osd_hdr->osd_hdr_ptr_bmp;

		FBDEV_O20_FBC_DEBUG("fb(%d) afbc_xidx(%d) hdr.addr=0x%08x hdr.sz=0x%x body.addr=0x%08x xy=%d,%d size=%dx%d, stride=%d\n",
				fb_dev_id, afbc_xidx, fbc_hdr_addr,  fbc_hdr_size, fbc_hdr_addr+fbc_hdr_size,
				osd_img_x, osd_img_y, osd_img_w, osd_img_h, osd_img_stride);


		/* once the whole AFBC registers are set, I will just update the minimal registers */
		if(fbc_ctrl->status & FBDEV_O20_FBC_STATUS_HDR_SETUP)
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
			 * I 've used 0xffff_fffff since O20 AFBC integration
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

			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, flip_mode, 	(mirror_ctrl->status & FBDEV_O20_V_MIRROR_ON)? 1:0);
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
	fbc_ctrl->status |= FBDEV_O20_FBC_STATUS_HDR_SETUP;
}

static void FBDEV_O20_CMN_FlushFBCHdrRegs(int fb_dev_id)
{
	int	i;
	int	afbc_xidx;
	int	xnum, xlst[2], afbc_xlst[2];

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_O20_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];

	FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

	if(!(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL))
	{
		FBDEV_NOTI("fbc_fmt=%s\n", (fbc_ctrl->fbc_fmt==LX_FBDEV_FBC_FORMAT_AFBC)? "on":"off");
	}
	else
	{
		FBDEV_HW_NOTI("fbc_fmt=%s\n", (fbc_ctrl->fbc_fmt==LX_FBDEV_FBC_FORMAT_AFBC)? "on":"off");
	}

	if (fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
	{
		xnum = FBDEV_O20_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
		FBDEV_O20_FBC_DEBUG("fb(%d) xnum=%d, afbc_xlst=(%d,%d)\n", fb_dev_id, xnum, afbc_xlst[0], afbc_xlst[1]);

		/* current fb_dev_id is not attached to afbc */
		FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d\n", fb_dev_id, xnum);

		for (i=0; i<xnum; i++)
		{
			afbc_xidx = afbc_xlst[i];
			if(INVALID_AFBC_XIDX(afbc_xidx)) continue;

			AFBC_CTRL_Wr01(afbc_xidx, ctrl_afbc_0, update_ready_flag, 0x1);
			AFBC_CTRL_WrFL(afbc_xidx, ctrl_afbc_0);

			FBDEV_O20_FBC_DEBUG("fb(%d) afbc_xidx(%d) flush AFBC regs\n", fb_dev_id, afbc_xidx);
		}
	}
}
#endif

/** write real header data to register
 *
 *
 */
void	FBDEV_O20_CMN_WriteHdrRegs	(int fb_dev_id, FBDEV_O20_OSD_HDR_T* osd_hdr, FBDEV_O20_OSD_EXHDR_T* osd_exhdr)
{
	int		i;
	int		xidx;
	int		xnum, xlst[2];


	FBDEV_O20_OSD_HDR_T osd_hw_hdr[2];	/* O20 supports max 2 POSD for 4KOSD display */
	UINT32* hdr_regs;

	ULONG   flags;
	struct scanvas* hCanvas = NULL;
	FBDEV_WIN_CTX_T* wctx	= NULL;
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	hCanvas = FBDEV_GetWinCanvas(fb_dev_id);
	FBDEV_CHECK_CODE(NULL==hCanvas, return, "invalid canvas. fb(%d)\n", fb_dev_id );

	wctx = FBDEV_GetWinCtx(fb_dev_id);
	FBDEV_CHECK_CODE(NULL==wctx, return, "invalid winctx. fb(%d)\n", fb_dev_id );

	xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
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

			OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);
			disp_fbmem = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);

			FBDEV_WARN("fb(%d) xidx(%d) freezed. osd_hdr_flush deferred. keep 0x%08x\n", fb_dev_id, xidx, disp_fbmem );
		}
		goto func_exit;
	}

	/* flush OSD header registers itself */
	for (i=0; i<xnum; i++)
	{
		xidx = xlst[i];
		if (INVALID_XIDX(xidx)) continue;

		memcpy(&osd_hw_hdr[i], osd_hdr, sizeof(FBDEV_O20_OSD_HDR_T));

		/* xnum=2 즉 2개의 POSD가 필요한 경우. 각각 L/R 절반씩 처리토록 한다. */
		if (xnum==2)
		{
			if(hCanvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
			{
				/* two posd will share the same AFBC image base */
			}
			else
			{
				osd_hw_hdr[i].osd_hdr_ptr_bmp += (osd_exhdr->img_stride/2)*i;
			}
			osd_hw_hdr[i].osd_hdr_w_mem /= 2;
			osd_hw_hdr[i].osd_hdr_w_out /= 2;
			osd_hw_hdr[i].osd_hdr_xpos = (osd_hw_hdr[i].osd_hdr_w_mem)*i;
		}

		hdr_regs= (UINT32*)&osd_hw_hdr[i];

		if(fb_dev_id==LX_FBDEV_ID_OSD0)
		{
			FBDEV_O20_HDR_DEBUG("fb(0) osd_hw_hdr wxh = %dx%d -> %dx%d\n",
				osd_hw_hdr[i].osd_hdr_w_mem, osd_hw_hdr[i].osd_hdr_h_mem,
				osd_hw_hdr[i].osd_hdr_w_out, osd_hw_hdr[i].osd_hdr_h_out);
		}

		OSDX_O20_Wr(osdx_ctrl[xidx], osd_ctrl_hdr0, hdr_regs[0]);
		OSDX_O20_Wr(osdx_ctrl[xidx], osd_ctrl_hdr1, hdr_regs[1]);
		OSDX_O20_Wr(osdx_ctrl[xidx], osd_ctrl_hdr2, hdr_regs[2]);
		OSDX_O20_Wr(osdx_ctrl[xidx], osd_ctrl_hdr3, hdr_regs[3]);
		OSDX_O20_Wr(osdx_ctrl[xidx], osd_ctrl_hdr4, hdr_regs[4]);
		OSDX_O20_Wr(osdx_ctrl[xidx], osd_ctrl_hdr5, hdr_regs[5]);
		OSDX_O20_Wr(osdx_ctrl[xidx], osd_ctrl_hdr6, hdr_regs[6]);

		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr1);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr3);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr4);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr5);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr6);

		/* raxis.lim (2017/09/15) -- DO NOT write OSD out_win only
		   when OSD0_PQEFW_OSD0_OUT_CTRL is enabled and TEMP_PAUSE is not enabled

		   raxis.lim (2018/05/15)
		   Remember that FBDEV_O20_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL is enabled temporarily when user changes OSD output resolution

		   raxis.lim (2019/06/19)
		   support orbit control (http://clm.lge.com/issue/browse/SDOSTB-246)
		   (note) 4KOSD 테스트 모드에서는 orbit 활성화시 OSD 출력 정상아님. orbit 제어하는 FW 에서 추가 제어 필요할 듯 예상됨

		   raxis.lim (2019/07/29)
		   EXT_FRC 가 붙었을 경우에는 orbit control 을 O20 에서 하지 않는다.
		   향후에는 flag 를 좀 더 조정하자.
		*/
		if(fb_dev_id == LX_FBDEV_ID_OSD0)
		{
			if(  (fbdev_pqefw_osd0_out_ctrl) &&
		  	     (hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL) &&
			    !(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL))
			{
				/* do nothing */
			}
			else
			{
				UINT32 w, h;
				OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_w_out, w);
				OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_hdr2, osd_hdr_h_out, h);
				FBDEV_NOTI("fb(%d) xidx(%d) flush OSD_CTRL_HDR2. %dx%d\n", fb_dev_id, xidx, w, h);
				OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
			}
		}
		else
		{
			OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
		}

	}

	/* flush post header (AFBC,OSD_SHP etc ) */
	{
		/* flush AFBC register */
#ifdef FBDEV_O20_USE_FBC_CTRL
		if (fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1)
		{
			FBDEV_O20_CMN_SetupFBC(fb_dev_id, hCanvas->fbc_fmt);

			if(hCanvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFBC)
			{
				FBDEV_O20_CMN_WriteFBCHdrRegs(fb_dev_id, osd_hw_hdr, osd_exhdr);
			}

			FBDEV_O20_CMN_FlushFBCHdrRegs(fb_dev_id);
		}
#endif
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
					   (hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL) &&
				   !(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL))
				{
					/* do nothing */
				}
				else
				{
					FBDEV_WARN("osd_shp's size changed (%d,%d) -> (%d,%d)\n",
						osd_shp_width, osd_shp_height, osd_hdr->osd_hdr_w_out, osd_hdr->osd_hdr_h_out);

					SHP0_CTRL_Wr01(shp_core_ctrl_01, reg_top_width, osd_hdr->osd_hdr_w_out);
					SHP0_CTRL_Wr01(shp_core_ctrl_01, reg_top_height,osd_hdr->osd_hdr_h_out);
					SHP0_CTRL_WrFL(shp_core_ctrl_01);
				}
			}
		}

		/* TODO: PQE 관련 코드는 너무 복잡하다. 좀 정리 안되나 */
		/* turn off TEMP_PAUSE because OSD update is completed */
		if(fb_dev_id == LX_FBDEV_ID_OSD0 && fbdev_pqefw_osd0_out_ctrl)
		{
			if(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)
			{
				FBDEV_WARN("PAUSE_PQEFW_OSD0_OUT_CTRL disabled (%d,%d)\n",
				(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL)? 1:0,
					(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)? 1:0);
				hw_ctx->hw_wa_flag &= ~FBDEV_O20_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL;
			}
		}

		/* notify OSD HW to read osd header */
		for (i=0; i<xnum && VALID_XIDX(xlst[i]); i++)
		{
			xidx = xlst[i];
			g_osd_o20_reg->osdx_ctrl[xidx].osd_ctrl_main.osd_hdr_ready_flag = 0x1;
			FBDEV_O20_HDR_DEBUG("fb(%d) xidx(%d) flush osd_hdr regs/data\n", fb_dev_id, xidx);
		}

#ifdef FBDEV_O20_SUPPORT_4KOSD_UPSCALER
		/* raxis.lim (2019/05/22)
		 *
		 * if you want to support OSD smaller than 4K, reg_4k_osd_main_ctrl_2 register should be configured again
		 * to reduce screen corruption, I added this right after updating osd_hdr_ready_flag
		 */
		if (fb_dev_id==LX_FBDEV_ID_OSD0 && xnum==2)
		{
			xidx = xlst[1];
			OSDX_O20_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_w, osd_hdr->osd_hdr_w_mem);
			OSDX_O20_Wr01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2, reg_sc_i_h, osd_hdr->osd_hdr_h_mem);
			OSDX_O20_WrFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_2);
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
static int FBDEV_O20_CMN_WriteOSDHeader(struct scanvas *pCanvas)
{
	int						fb_dev_id;
	UINT32					bitmap_ptr;
	FBDEV_O20_OSD_HDR_T		osd_hdr;
	FBDEV_O20_OSD_EXHDR_T	osd_exhdr;
	FBDEV_WIN_CTX_T* 		wctx;
	struct scanvas			canvas;
	UINT32					disp_width, disp_height;

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> fb(%d) user_initcall not ready +++\n", pCanvas->fb_dev_id);

	wctx = FBDEV_GetWinCtx(pCanvas->fb_dev_id);
	FBDEV_CHECK_CODE(NULL==wctx, return RET_ERROR, "fb(%d) invalid winctx.\n", pCanvas->fb_dev_id);

	/* doesn't support fb(1) control when external renderer is enabled */
	FBDEV_CHECK_CODE(fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_fb1_renderer == TRUE, return RET_ERROR,
		"fb(%d) ext_renderer mode. ignore osd render\n", pCanvas->fb_dev_id);

	/* clear osd_hdr before writing */
	memset(&osd_hdr,   0x0, sizeof(FBDEV_O20_OSD_HDR_T));
	memset(&osd_exhdr, 0x0, sizeof(FBDEV_O20_OSD_EXHDR_T));
	memcpy(&canvas,	   pCanvas, sizeof(struct scanvas));

	fb_dev_id = canvas.fb_dev_id;
	disp_width = hw_ctx->hw_disp_width;
	disp_height= hw_ctx->hw_disp_height;

	CHECK_REGS(fb_dev_id);

	/* raxis.lim (2016/08/08) - if OSD is freezed, DO NOT handle/write any registers
	 *
	 * This patch seems to prevent OSD garbage during transition from non AFBC (boot logo) to AFBC (mercury/webOS) screen.
	 * Originally, osd_hdr_flush is checked at FBDEV_O20_CMN_WriteHdrRegs().
	 * I don't know the below code really prevents OSD garbage rather than the original policy.
	 * <!> More tests are required.
	 */
	if ( !wctx->status.b_osd_hdr_flush )
	{
		int	xidx, xnum, xlst[2];
       	UINT32 disp_fbmem = 0x0;

		xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
		xidx = xlst[0];

		if(!INVALID_XNUM(xnum))
		{
			OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);
			disp_fbmem = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);
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

#ifdef FBDEV_O20_USE_UNLIMITED_CURSOR_POSITION
			int csr_h_min_pxl = FBDEV_O20_BYTES_2_PIXEL(FBDEV_O20_GMAU_WORD_BYTES);	/* 16 bytes -> 4 pixel */
#endif
			FBDEV_O20_HDR_DEBUG("cursor_pos req(%d,%d)\n", canvas.output_win.x, canvas.output_win.y );

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
			// @note S.OSD is not tested
			//
			if( hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
			{
				if( FBDEV_O20_CMN_IsUHDDispMode() )
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
#endif

            // if csr_hotspot is active, adjust (x,y) position of cursor layer.
			//
            // if cursor position is negative, I should move the bitmap address ( H/W doesn't accept negative position )
            //
            // IMPORTATNT !! if you change the base address, its alignment should be multiplt of 16 byte ( not 8 byte )
            // woonghyeon just said that it may be H/W bug (limitation?).
            // since we are using ARGB8888 pixel format for cursor OSD. cursor offset should be multiple of 4 pixel !!
			//
			csr_x_max = canvas.stride / FBDEV_O20_BITS_2_BYTES(canvas.bits_per_pixel);

			csr_x_off = 0;
			csr_y_off = 0;

			csr_x_pos = canvas.output_win.x - canvas.csr_hotspot.x;
			csr_y_pos = canvas.output_win.y - canvas.csr_hotspot.y;

			csr_x_size= (canvas.csr_size.w>0)? LX_CALC_ALIGNED_VALUE(canvas.csr_size.w,2): canvas.input_win.w;
			csr_y_size= (canvas.csr_size.h>0)? canvas.csr_size.h : canvas.input_win.h;

			FBDEV_O20_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d info( %dx%d h %d,%d ) max_x %d disp_x %d\n", fb_dev_id,
						csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
						canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y,
						csr_x_max, csr_disp_w );

#ifdef FBDEV_O20_USE_UNLIMITED_CURSOR_POSITION
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

				if(csr_y_size < FBDEV_O20_CSR_MIN_HEIGHT)
				{
					csr_y_size = FBDEV_O20_CSR_MIN_HEIGHT;
					csr_y_off  = csr_y_size-FBDEV_O20_CSR_MIN_HEIGHT;
				}
			}

			// prevent OSD garbage. effective cursor width should be less than the real surface width
			if (csr_x_size > csr_x_max)	csr_x_size = csr_x_max;

			// if cursor is located at the right corner, I should gaurantee the minimal viewing area of cursor.
			// without it, cursor image will be broken :(
			// see the description for FBDEV_O20_CSR_MIN_WIDTH
			if (csr_x_pos + csr_x_size > csr_disp_w )
			{
#ifdef FBDEV_O20_USE_UNLIMITED_CURSOR_POSITION
				// raxis.lim (2015/07/24)
				// hide cursor will not be shown at the right corner
				// keep in mind that OSD garbage might be shown because I don't gaurantee the minimum viewing area
				if (csr_x_pos > csr_disp_w )
				{
					csr_x_pos = csr_disp_w;
				}
#else
				if (csr_x_pos > csr_disp_w-FBDEV_O20_CSR_MIN_WIDTH)
				{
					csr_x_pos = csr_disp_w-FBDEV_O20_CSR_MIN_WIDTH;
				}
#endif
				csr_x_pos	= LX_CALC_ALIGNED_VALUE(csr_x_pos,2);	/* make X pos is aligned by 4 */

				csr_x_size	= csr_disp_w-csr_x_pos;

				// software workaround for 1x cursor display on blend path
				// On blend path, cursor size should be displayed x2 automatically because OSD disp size is 3840x2160
				// and cursor region is set based on 1920x1080 area
				// if 2x scale up is not supported, I should multiply csr_x_size by double manually
				//
				// raxis.lim (2020/06/02)
				// DO NOT assume B.OSD path is always set to UHD display.
				// I should support FHD display on B.OSD path.
				// So I should check output display size regardless of osd path configuration.
				if ( hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_1X_CSR_DISP_ON_BLEND_PATH )
				{
					if(FBDEV_O20_CMN_IsUHDDispMode())
					{
						csr_x_size *= 2;
						if ( csr_x_size > csr_x_max ) csr_x_size = csr_x_max;
					}
				}
   			}

			// if cursor is located at the bottom corner, I should gaurantee the minimum viewing area, i.e 2 pixel
			if (csr_y_pos > csr_disp_h-FBDEV_O20_CSR_MIN_HEIGHT)
			{
				csr_y_pos = csr_disp_h-FBDEV_O20_CSR_MIN_HEIGHT;
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
            bitmap_ptr += ( csr_y_off * canvas.stride ) + FBDEV_O20_GMAU_ALIGNED_BYTES(csr_x_off * FBDEV_O20_BITS_2_BYTES(canvas.bits_per_pixel));

			osd_hdr.osd_hdr_pixel_order	= canvas.pixel_order_en;
			osd_hdr.osd_hdr_wpl 		= FBDEV_O20_BYTES_2_OSD_WORDS(canvas.stride);

			FBDEV_O20_HDR_DEBUG("fb(%d) pos %dx%d csr_sz %d,%d <- req( %dx%d h %d,%d)\n", fb_dev_id,
						csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
						canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y );
			FBDEV_O20_HDR_DEBUG("fb(%d) cursor pre-processing done\n", fb_dev_id);
		}
		break;

		case LX_FBDEV_ID_OSD0:
		default:
		{
			int	osd_ex_h = 0;
			int	osd_ex_out_h = 0;

			/* see SICDTV-7971 */
			if(fb_dev_id == LX_FBDEV_ID_OSD0)
			{
				osd_ex_h = hw_ctx->hw_fb0_ex_height;
				osd_ex_out_h = hw_ctx->hw_fb0_ex_out_height;

				//FBDEV_NOTI("osd_ex_h=%d, osd_ex_out_h=%d\n", osd_ex_h, osd_ex_out_h);
			}

			if( FBDEV_O20_CMN_IsUHDDispMode() ) // && (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) )
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
				canvas.stride		= FBDEV_O20_PIXEL_2_BYTES(canvas.input_win.w);
			}

			// E-streamer OSD 출력 테스트 코드
			if(fb_dev_id==LX_FBDEV_ID_OSD1)
			{
				canvas.output_win.w = canvas.input_win.w;
				canvas.output_win.h = canvas.input_win.h;

				//FBDEV_O20_HDR_DEBUG("fb(%d) pos=%d,%d\n", fb_dev_id, canvas.output_win.x, canvas.output_win.y);
			}

			if (canvas.input_win.w > disp_width )	canvas.input_win.w = disp_width;
			if (canvas.input_win.h > disp_height) 	canvas.input_win.h = disp_height;
			if (canvas.output_win.w > disp_width )	canvas.output_win.w = disp_width;
			if (canvas.output_win.h > disp_height)	canvas.output_win.h = disp_height;


			// raixs.lim (2017/08/25)
			// support user defined output win for debug. invalid config might make OSD corruption
			if (canvas.test_output_win.w && canvas.test_output_win.h)
			{
				FBDEV_O20_HDR_DEBUG("++ user output used (%d,%d)\n", canvas.test_output_win.w, canvas.test_output_win.h);
				memcpy(&canvas.output_win, &canvas.test_output_win, sizeof(LX_RECT_T));
			}

			// raxis.lim (2015/01/12) -- handle odd width
			// OSD doesn't support odd number as output width. so let's make it to even number
			if ( canvas.output_win.w & 0x1 )
			{
				FBDEV_O20_HDR_DEBUG("fb(%d) convert odd out_w %d to %d\n", fb_dev_id, canvas.output_win.w, canvas.output_win.w&0xfffffffe);
				canvas.output_win.w &= 0xfffffffe;
			}

			// NOTE - CLUT processing is not processed anymore inside kdriver
			osd_hdr.osd_hdr_color_key_en= canvas.color_key_en;

			osd_hdr.osd_hdr_w_out		= canvas.output_win.w;	/* output w */
			osd_hdr.osd_hdr_h_out		= canvas.output_win.h + osd_ex_out_h; /* output h */
			osd_hdr.osd_hdr_xpos	 	= canvas.output_win.x;	/* output x */
			osd_hdr.osd_hdr_ypos 		= canvas.output_win.y;	/* output y */
			osd_hdr.osd_hdr_w_mem 		= canvas.input_win.w;	/* input w  */
			osd_hdr.osd_hdr_h_mem 		= canvas.input_win.h + osd_ex_h; /* input h  */
			bitmap_ptr					= canvas.osd_bm_paddr;

			// modify bitmap ptr for input position is provided
			if (canvas.input_win.x > 0 || canvas.input_win.y > 0)
			{
				FBDEV_O20_HDR_DEBUG("fb(%d) bitmap based moved ! by %d,%d\n", fb_dev_id, canvas.input_win.x, canvas.input_win.y );

				/* gMAU requests 16byte aligned address */
				bitmap_ptr += canvas.input_win.y * canvas.stride;
				bitmap_ptr += FBDEV_O20_GMAU_ALIGNED_BYTES(FBDEV_O20_BITS_2_BYTES(canvas.input_win.x*canvas.bits_per_pixel));
			}
			FBDEV_O20_HDR_DEBUG("fb(%d) bitmap hwparam (%d,%d,%d,%d)(%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x\n", fb_dev_id,
					canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
					canvas.output_win.x, canvas.output_win.y, canvas.output_win.w, canvas.output_win.h,
					canvas.stride, bitmap_ptr, canvas.fbc_fmt );

			osd_hdr.osd_hdr_pixel_order	= canvas.pixel_order_en;
			osd_hdr.osd_hdr_wpl 		= FBDEV_O20_BYTES_2_OSD_WORDS(canvas.stride);
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
	FBDEV_O20_CMN_HandleReverseOSD(fb_dev_id, &canvas, &osd_hdr);

	FBDEV_O20_HDR_DEBUG("fb(%d) bitmap hwparam (%d,%d,%d,%d)(%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x (final)\n", fb_dev_id,
			canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
			canvas.output_win.x, canvas.output_win.y, canvas.output_win.w, canvas.output_win.h,
			canvas.stride, bitmap_ptr, canvas.fbc_fmt );

	/* save osd header */
	memcpy( &hw_ctx->osd_hdr_sav[fb_dev_id], &osd_hdr, sizeof(FBDEV_O20_OSD_HDR_T));

	/* raxis.lim (2019/05/21)
	 *
	 * I don't care here whether two POSDs sare necessary or not. refer to FBDEV_O20_CMN_WriteHdrRegs()
	 */
	osd_exhdr.bits_per_pixel= canvas.bits_per_pixel;
	osd_exhdr.img_stride 	= canvas.stride;
	osd_exhdr.img_height	= osd_hdr.osd_hdr_h_mem;	/* 이 값이 맞나 몰라 */

	FBDEV_O20_CMN_WriteHdrRegs(fb_dev_id, &osd_hdr, &osd_exhdr);

	/* do somthing if necessary */

	/* (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume */
	if (fb_dev_id == LX_FBDEV_ID_OSD0)
	{
		/* F20 이 존재하는 경우에는 orbit 동작이 F20 에서 벌어지므로, OSD kdriver 는 항상 OSD HDR 설정토록 조치한다. */
		if (hw_ctx->b_support_ext_frc)
		{
			if(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL)
			{
				fbdev_pqefw_osd0_out_ctrl = 0;
				hw_ctx->hw_wa_flag &= ~FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL;
				FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL disabled\n");
			}
		}
		else /* INT_FRC or NO_FRC */
		{
			if(!(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL))
			{
				hw_ctx->hw_wa_flag |= FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL;
				FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
			}
		}
	}

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
int FBDEV_O20_CMN_SetOSDEnable(int fb_dev_id, int enable)
{
	int		i;
	int		xidx;
	int		xnum, xlst[2], afbc_xlst[2];
	UINT32	val = 0x0;

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> user_initcall not ready +++\n");

	/* doesn't support fb(1) control when external renderer is enabled */
	if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_fb1_renderer == TRUE)
	{
		FBDEV_O20_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_O20_GET_EXT_RENDER_CTRL(hw_ctx);

		ext_render_ctrl->hwparam.enable = enable;
		FBDEV_NOTI("fb(%d) ext_renderer en=%d, cmd=0x%08x\n", fb_dev_id, ext_render_ctrl->hwparam.enable, ext_render_ctrl->hwparam.command);

		/* close external render path if osd is disabled */
		if(!enable)
		{
            OS_WrReg(FBDEV_OS0_EXT_RENDER_REG_BASE+0x08, ext_render_ctrl->hwparam.command);
		}

		FBDEV_NOTI("fb(%d) ext_renderer %s\n", fb_dev_id, (enable)? "enabeld":"disabled");

		/* see SICDTV-8491 : report estreamer visibility */
		hw_ctx->user_initcall_ctrl.status.osd_estreamer = enable;
		FBDEV_O20_CMN_NotifyToPQEDriver();

		return RET_OK;
	}

	xnum = FBDEV_O20_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
	/* ignore noisy warning msg becase some OSD layer is not supported by HW */
	FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

	val = (enable)? 0x1: 0x0;
	FBDEV_HW_DEBUG("fb(%d) xlst=(%d,%d) view = <%s>\n", fb_dev_id, xlst[0], xlst[1], (enable)? "on":"off");

	for (i=0; i<xnum; i++)
	{
		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, val);
		OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_enable, val);
	}

	/* flush registers */
	for (i=0; i<xnum; i++)
	{
		xidx = xlst[i];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
		OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);
	}

	/* raxis.lim (2019/10/08) -- enable/disable afbc reader if necessary
	 *
	 * OSD reader is configured to AFBC mode not MIF, CCO0/CCO1 will read something even though OSD is off state.
	 * So we should control afbc(x)_init_en, afbc(x)_auto_init_en flag
	 * refer to http://clm.lge.com/issue/browse/AVTASK-401
	 */
#ifdef FBDEV_O20_USE_FBC_CTRL
	#ifdef FBDEV_O20_USE_AFBC_READ_BW_SAVING
	{
		int afbc_status = FBDEV_O20_CMN_GetHWStatus(FBDEV_O20_HW_STATUS_AFBC, fb_dev_id);

		OSD_TOP_O20_RdFL(ctrl_auto_init_afbc);

		if (afbc_status)
		{
			if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
			{
				OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,		enable);
				OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en, 	enable);
			}

			if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
			{
				OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en, 		enable);
				OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en, 	enable);
			}
		}
		else
		{
			if (afbc_xlst[0] == 0 || afbc_xlst[1] == 0)
			{
				OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_init_en,		0x0);
				OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc0_auto_init_en, 	0x0);
			}
			if (afbc_xlst[0] == 1 || afbc_xlst[1] == 1)
			{
				OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_init_en, 		0x0);
				OSD_TOP_O20_Wr01(ctrl_auto_init_afbc, reg_afbc1_auto_init_en, 	0x0);
			}
		}
		FBDEV_O20_FBC_DEBUG("fb(%d) afbc=%d, view=%d\n", fb_dev_id, afbc_status, enable);

		OSD_TOP_O20_WrFL(ctrl_auto_init_afbc);
	}
	#endif
#endif

	return RET_OK;
}

/** OSD HW Layer status
 *
 * wparam	void
 * @return	int 1 : ON , 0 : OFF
 *
 */
int FBDEV_O20_CMN_GetOSDEnable(int fb_dev_id)
{
	UINT32 val;
	int	xidx;
	int	xnum, xlst[2];

	xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
	/* ignore noisy warning msg becase some OSD layer is not supported by HW */
	if(INVALID_XNUM(xnum)) return FALSE;

	/* raxis.lim (2019/05/21) -- event though OSD requires two POSD for 4K display, we can just check the first POSD value */
	xidx = xlst[0];
	FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return FALSE, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

	OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
	OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, val );

	return val;
}

int		FBDEV_O20_CMN_SetViewCtrl ( LX_FBDEV_VIEW_CTRL_T* ctrl )
{
	int i;
	ULONG flags;

	/* we can't do spinlock when pivot mode is enabled because sleep ocurrs during GFX merge */
	spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
		if (ctrl->view_status[i] == 0x0 || ctrl->view_status[i] == 0x1)
		{
			FBDEV_O20_CMN_SetOSDEnable(i, ctrl->view_status[i]);
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
int     FBDEV_O20_CMN_SetConnCtrl           (LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
	int     i;
	BOOLEAN osd_view_status[LX_FBDEV_ID_MAX];

	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	FBDEV_WARN("OSD conn change. conn_type 0x%x (%s disp)\n", pConnCtrl->conn_type, (g_fbdev_cfg->uhd_disp_mode)? "UHD":"FHD" );

	FBDEV_CHECK_DEBUG(hw_ctx->hw_conn_type == pConnCtrl->conn_type, return RET_OK, "ignore the dup calls (0x%x)\n", pConnCtrl->conn_type);

	/* save current config. diable OSD before changing OSD config */
	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
		osd_view_status[i] = FBDEV_O20_GetOSDEnable(i);
		FBDEV_O20_SetOSDEnable(i, FALSE );
	}

	/* disable ISR to change ISR source */
	FBDEV_O20_SetInterruptEnable(MIXER_INTR, FALSE);

	/* sleep until OSD stablized. not necessary to sleep in O20 */

	if (pConnCtrl->conn_type & LX_FBDEV_CONN_OSD_VIDEO_SEPARATE)
	{
		FBDEV_HW_DEBUG("O20::S.OSD\n");

		hw_ctx->hw_disp_width	= hw_ctx->sosd_disp.out_width;
		hw_ctx->hw_disp_height	= hw_ctx->sosd_disp.out_height;
	}
	else if(pConnCtrl->conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
	{
		FBDEV_HW_DEBUG("O20::B.OSD\n");

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
	FBDEV_O20_CMN_ReInitHW();

	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
	    FBDEV_WriteOSDHeader(&g_dm_ctx->wctx[i]->pixel);
	}

func_exit:
	for (i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
		FBDEV_O20_SetOSDEnable(i, osd_view_status[i]);
	}

	return RET_OK;
}

/** control OSD SR (Picture Enhancement)
 *  - on/off
 *  - filter update
 *	- etc
 *
 */
int		FBDEV_O20_CMN_SRCtrl			(BOOLEAN onoff)
{
	FBDEV_O20_CMN_SetupSRScaler(onoff, TRUE);
	return RET_OK;
}

/** debug only
 *
 */
int		FBDEV_O20_CMN_MirrorCtrl		(BOOLEAN v_mirror_en)
{
	int	i, j;
	int fb_list[] = {LX_FBDEV_ID_OSD0, LX_FBDEV_ID_OSD3};

	FBDEV_O20_HW_CTX_T*	hw_ctx = FBDEV_O20_GET_HW_CTX();
	FBDEV_O20_MIRROR_CTRL_T* mirror_ctrl = FBDEV_O20_GET_MIRROR_CTRL(hw_ctx);
	FBDEV_O20_FBC_CTRL_T* fbc_ctrl = FBDEV_O20_GET_FBC_CTRL(hw_ctx, LX_FBDEV_ID_OSD0);

	/* change mirror configuratin */
	mirror_ctrl->status = (v_mirror_en)? FBDEV_O20_V_MIRROR_ON: 0x0;

	for (j=0; j<NELEMENTS(fb_list); j++)
	{
		int	xidx;
		int xnum, xlst[2];

		xnum = FBDEV_O20_CMN_GetHWXList(fb_list[j], xlst);

		for (i=0; i<xnum; i++)
		{
			xidx = xlst[i];
			if(INVALID_XIDX(xlst[i])) continue;

			OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
			OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

			FBDEV_NOTI("fb(%d) before: 0x%08x 0x%08x\n", fb_list[j],
							OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_main),
							OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_sync0));

			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en,	v_mirror_en );
			OSDX_O20_Wr01(osdx_ctrl[xidx], osd_ctrl_sync0, osd_sync_v_reverse, v_mirror_en );

			OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_main);
			OSDX_O20_WrFL(osdx_ctrl[xidx], osd_ctrl_sync0);

			FBDEV_NOTI("fb(%d) after: 0x%08x 0x%08x\n", fb_list[j],
							OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_main),
							OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_sync0));
		}
	}

	/* make AFBC header to setup again when next framebuffer is updated */
	fbc_ctrl->status &= ~FBDEV_O20_FBC_STATUS_HDR_SETUP;

	{
 		FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(LX_FBDEV_ID_OSD0);

		if (wctx)
		{
			FBDEV_O20_CMN_WriteOSDHeader(&wctx->pixel);
		}
	}

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
void	FBDEV_O20_CMN_HandleReverseOSD ( int fb_dev_id, struct scanvas* hCanvas, FBDEV_O20_OSD_HDR_T* osd_hdr )
{
#ifdef FBDEV_O20_USE_REV_HW_CTRL
	// TODO: if reverse screen handler if needed
#endif
}

/** VOSD ISR handler
 *
 *
 */
void     FBDEV_O20_CMN_ISRHook ( void )
{
	/* do nothing */
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
int      FBDEV_O20_CMN_GetHWStatus       (FBDEV_O20_HW_STATUS_T status, UINT32 opt)
{
	int	val = 0;
	FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

	switch(status)
	{
		/* return 1 if HW is set to AFBC configuration. otherwise return 0 */
		case FBDEV_O20_HW_STATUS_AFBC:
		{
			OSD_TOP_O20_RdFL(ctrl_dpath);

			if (opt == LX_FBDEV_ID_OSD0)
			{
				OSD_TOP_O20_Rd01(ctrl_dpath, osd0_afbc_en, val);
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
					OSD_TOP_O20_Rd01(ctrl_dpath, osd1_afbc_en, val);
				}
			}
			else
			{
				val = 0;
			}
		}
		break;

		case FBDEV_O20_HW_STATUS_VISIBLE:
		{
			val = FBDEV_O20_CMN_GetOSDEnable(opt);
		}
		break;

		case FBDEV_O20_HW_STATUS_SR_GAIN:
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
void FBDEV_O20_CMN_DiagHW(struct seq_file* m)
{
#ifdef FBDEV_O20_USE_SR_CTRL
    UINT32 val;

    int xidx;
    int xnum, xlst[2];
    int fb_dev_id = LX_FBDEV_ID_OSD0;

    FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

    xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );
    xidx = xlst[0];

	/* print HW core info */
	{
		seq_printf(m, "disp.path: %s\n", 		(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? "bosd":"sosd");
		seq_printf(m, "disp.width: %d\n", 		hw_ctx->hw_disp_width );
		seq_printf(m, "disp.height: %d\n", 		hw_ctx->hw_disp_height);
		seq_printf(m, "disp.fb0_ex_h: %d\n", 	hw_ctx->hw_fb0_ex_height );
		seq_printf(m, "disp.fb0_ex_out_h: %d\n",hw_ctx->hw_fb0_ex_out_height);

		seq_printf(m, "\n");
		seq_printf(m, "disp.uhd_mode: %d\n", 	FBDEV_O20_CMN_IsUHDDispMode()? 1:0 );
		seq_printf(m, "fb0.width: %d\n", 		hw_ctx->hw_fb0_width);
		seq_printf(m, "fb0.height: %d\n", 		hw_ctx->hw_fb0_height);
		seq_printf(m, "fb1.width: %d\n", 		hw_ctx->hw_fb1_width);
		seq_printf(m, "fb1.height: %d\n", 		hw_ctx->hw_fb1_height);
		seq_printf(m, "ext.width: %d\n", 		hw_ctx->hw_ext_render_width);
		seq_printf(m, "ext.height: %d\n", 		hw_ctx->hw_ext_render_height);
		seq_printf(m, "\n");
		seq_printf(m, "vsync_clk: %dHz\n",		(FBDEV_O20_CMN_DetectVSyncClk()==FBDEV_VSYNC_CLK_60HZ)? 60: 120);

		seq_printf(m, "support_ext_frc: %d\n",	hw_ctx->b_support_ext_frc);
		seq_printf(m, "support_fb1: %d\n",		hw_ctx->b_support_fb1);
		seq_printf(m, "support_4kosd: %d\n",	hw_ctx->b_support_4kosd);
		seq_printf(m, "support_ext_fb1_renderer: %d\n",	hw_ctx->b_support_ext_fb1_renderer);
		seq_printf(m, "\n");

		seq_printf(m, "sr_ctrl[0].status: 0x%08x\n",	hw_ctx->sr_ctrl[0].status);
		seq_printf(m, "sr_ctrl[0].ti_gain: 0x%08x\n",	hw_ctx->sr_ctrl[0].ti_gain);
		seq_printf(m, "sr_ctrl[1].status: 0x%08x\n",	hw_ctx->sr_ctrl[1].status);
		seq_printf(m, "sr_ctrl[1].ti_gain: 0x%08x\n",	hw_ctx->sr_ctrl[1].ti_gain);
		seq_printf(m, "\n");

		// (2020/01/18) read the real HW configuration NOT status value.
		// because application might refer this proc to make its reverse-mode config BEFORE kdriver initialization
		// see " user_initcall based HW initialization" policy.
        OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
        OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_v_reverse_en, val);
		seq_printf(m, "mirror.status: 0x%08x\n",	val);
		seq_printf(m, "\n");

		seq_printf(m, "ext_rener.fbmem0: 0x%08x\n",	hw_ctx->ext_render_ctrl.fbmem_phys[0]);
		seq_printf(m, "ext_rener.fbmem1: 0x%08x\n",	hw_ctx->ext_render_ctrl.fbmem_phys[1]);

		seq_printf(m, "ext_rener.hwparam.phys_y: 0x%08x\n",	hw_ctx->ext_render_ctrl.hwparam.phys_y);
		seq_printf(m, "ext_rener.hwparam.size: 0x%08x\n",	hw_ctx->ext_render_ctrl.hwparam.size);
		seq_printf(m, "ext_rener.hwparam.xoffset: %d\n",	hw_ctx->ext_render_ctrl.hwparam.xoffset);
		seq_printf(m, "ext_rener.hwparam.enable: %d\n",		hw_ctx->ext_render_ctrl.hwparam.enable);
		seq_printf(m, "ext_rener.hwparam.crop_x: %d\n",		hw_ctx->ext_render_ctrl.hwparam.crop_x);
		seq_printf(m, "ext_rener.hwparam.crop_y: %d\n",		hw_ctx->ext_render_ctrl.hwparam.crop_y);
		seq_printf(m, "ext_rener.hwparam.crop_w: %d\n",		hw_ctx->ext_render_ctrl.hwparam.crop_w);
		seq_printf(m, "ext_rener.hwparam.crop_h: %d\n",		hw_ctx->ext_render_ctrl.hwparam.crop_h);
		seq_printf(m, "ext_rener.hwparam.tx_count: %d\n",	hw_ctx->ext_render_ctrl.hwparam.tx_count);

		seq_printf(m, "\n");
		seq_printf(m, "hw_wa.1x_csr_disp_on_blend_path: 0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_1X_CSR_DISP_ON_BLEND_PATH)? 1:0);
		seq_printf(m, "hw_wa.osd0_async_wr_error:       0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)? 1:0);
		seq_printf(m, "hw_wa.pqwfw_osd0_out_ctrl:       0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PQEFW_OSD0_OUT_CTRL)? 1:0);
		seq_printf(m, "hw_wa.pause_pqwfw_osd0_out_ctrl: 0x%x\n",(hw_ctx->hw_wa_flag & FBDEV_O20_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL)? 1:0);
		seq_printf(m, "hw_wa_flag:                      0x%x\n",hw_ctx->hw_wa_flag);
		seq_printf(m, "\n");
	}

	/* print OSD_SHP info */
	{
		int	xidx;
		int xnum, xlst[2];
		int	fb_dev_id = LX_FBDEV_ID_OSD0;

		UINT32 bypass_en, detour_en, rgb2yc_csc_en, yc2rgb_bosd_csc_en;
		FBDEV_O20_SR_CTRL_T* sr_ctrl = FBDEV_O20_GET_SR_CTRL(hw_ctx,fb_dev_id);

		xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
		FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id );

		xidx = xlst[0];
		FBDEV_CHECK_CODE(INVALID_XIDX(xlst[0]), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[0]);

		OSDX_O20_RdFL(osdx_ctrl[xidx], osd_bitmap_ctrl0);
		SHP0_CTRL_RdFL(shp_core_ctrl_00);

		SHP0_CTRL_Rd01(shp_core_ctrl_00, reg_top_bypass, bypass_en);

		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_osd_shp_detour_en,		detour_en);;
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, 	rgb2yc_csc_en);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, 	yc2rgb_bosd_csc_en);
		OSDX_O20_Rd01(osdx_ctrl[xidx], osd_bitmap_ctrl0, reg_yc2rgb_bosd_csc_en, 	rgb2yc_csc_en);

		seq_printf(m, "osd_sr.sw_status: 0x%x\n", sr_ctrl->status);
		seq_printf(m, "osd_sr.hw_status: 0x%x\n", (!bypass_en && !detour_en));
		seq_printf(m, "osd_sr.shp_ctrl0.bypass_en: 0x%x\n", bypass_en);
		seq_printf(m, "osd_sr.bmp_ctrl0.detour_en: 0x%x\n", detour_en);
		seq_printf(m, "osd_sr.bmp_ctrl0.rgb2yc_csc_en: 0x%x\n", yc2rgb_bosd_csc_en);
		seq_printf(m, "osd_sr.bmp_ctrl0.yc2rgb_bosd_csc_en: 0x%x\n", yc2rgb_bosd_csc_en);
		seq_printf(m, "\n");
	}

	/* afbc mux status */
	{
		int xidx = 1; /* OSD_IMAGE0_1 */

		UINT32 osd_4k_mux;

		OSDX_O20_RdFL(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0);
		OSDX_O20_Rd01(osdx_ctrl[xidx], reg_4k_osd_main_ctrl_0, reg_4k_mode_en, osd_4k_mux);

		seq_printf(m, "4kosd.muxcfg: 0x%x\n", osd_4k_mux);
	}

	/* print HW_CTX status */

	/* TODO: add something */
#endif
}

/** chip specific proc handler
 *
 */
void FBDEV_O20_CMN_ProcHandler(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case FBDEV_HW_PROC_ID_DETAIL_INFO:
		{
		#if 0
			FBDEV_O20_HW_CTX_T* hw_ctx = FBDEV_O20_GET_HW_CTX();

			seq_printf(m, "<HW INFO>\n");
			seq_printf(m, "path: %s\n", 			(hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)? "bosd":"sosd");
			seq_printf(m, "hw_disp_width: %d\n", 	hw_ctx->hw_disp_width );
			seq_printf(m, "hw_disp_height: %d\n", 	hw_ctx->hw_disp_height);
			seq_printf(m, "hw_fb0_width: %d\n", 	hw_ctx->hw_fb0_width);
			seq_printf(m, "hw_fb0_height: %d\n", 	hw_ctx->hw_fb0_height);
			seq_printf(m, "vsync_clk: %dHz\n",		(FBDEV_O20_CMN_DetectVSyncClk()==FBDEV_VSYNC_CLK_60HZ)? 60: 120);

			seq_printf(m, "support_ext_frc: %d\n",	hw_ctx->b_support_ext_frc);
			seq_printf(m, "support_4kosd: %d\n",	hw_ctx->b_support_4kosd);
		#endif
		}
		break;

		case FBDEV_HW_PROC_ID_OSD_HDR:
		{
			int	i;
			int xidx;
			int xnum, xlst[2];

			UINT32 	osd_en, sync_en;
			UINT32	hdr_lst[7];
			FBDEV_O20_OSD_HDR_T* osd_hdr = (FBDEV_O20_OSD_HDR_T*)hdr_lst;
			LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

			xnum = FBDEV_O20_CMN_GetHWXList(fb_dev_id, xlst);
			seq_printf(m, "posd_num: %d\n", xnum);
			for (i=0; i<xnum && VALID_XIDX(xlst[i]); i++)
			{
				xidx = xlst[i];

				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_main);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_sync0);

				OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_main, osd_en, osd_en);
				OSDX_O20_Rd01(osdx_ctrl[xidx], osd_ctrl_sync0,osd_sync_enable, sync_en);

				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr0);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr1);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr2);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr3);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr4);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr5);
				OSDX_O20_RdFL(osdx_ctrl[xidx], osd_ctrl_hdr6);

				hdr_lst[0] = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr0);
				hdr_lst[1] = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr1);
				hdr_lst[2] = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr2);
				hdr_lst[3] = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr3);
				hdr_lst[4] = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr4);
				hdr_lst[5] = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr5);
				hdr_lst[6] = OSDX_O20_Rd(osdx_ctrl[xidx], osd_ctrl_hdr6);

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
                { .desc = "OSD",  .reg_base = O20_CCO_BASE,					.reg_size = sizeof(OSD_O20_REG_T) }, //1536 }, //sizeof(OSD_O20_REG_T) },
                { .desc = "TOP",  .reg_base = O20_CCO_TOP_CTRL_BASE,		.reg_size = sizeof(OSD_TOP_O20_REG_T) }, //256 }, //sizeof(OSD_TOP_O20_REG_T) },
                { .desc = "AFBC0",.reg_base = O20_CCO_AFBC0_BASE,			.reg_size = sizeof(OSD_AFBC_O20_REG_T) }, //256 }, //sizeof(OSD_AFBC_O20_REG_T) },
                { .desc = "AFBC1",.reg_base = O20_CCO_AFBC1_BASE,			.reg_size = sizeof(OSD_AFBC_O20_REG_T) }, //256 }, //sizeof(OSD_AFBC_O20_REG_T) },
                { .desc = "SHP0", .reg_base = O20_CCO_SHP0_BASE,			.reg_size = sizeof(OSD_SHP_O20_REG_T) }, //768 }, //sizeof(OSD_SHP_O20_REG_T) },
                { .desc = "SHP1", .reg_base = O20_CCO_SHP1_BASE,			.reg_size = sizeof(OSD_SHP_O20_REG_T) }, //768 }, //sizeof(OSD_SHP_O20_REG_T) },
                { .desc = "MIF0", .reg_base = O20_CCO_MIF0_BASE,			.reg_size = 0xc0 },
                { .desc = "MIF1", .reg_base = O20_CCO_MIF1_BASE,			.reg_size = 0xc0 },
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
int	FBDEV_O20_CMN_RunResume	( void )
{
	/* OSD freeze will be stopped after 500 ms */
	FBDEV_O20_CMN_RunBootLogoTimer(fbdev_resume_freeze_timeout, TRUE);

	FBDEV_O20_CMN_ReInitHW( );

	return RET_OK;
}

int	FBDEV_O20_CMN_RunSuspend	( void )
{
	/* do nothing */
	return RET_OK;
}

/*========================================================================================
	common OSD HW handler
========================================================================================*/
FBDEV_O20_HW_FUNC_T  g_fbdev_o20_cmn_hw_func =
{
	/* variable is initialize at fbdev_drv_O20.c */

    .O20_InitHW			 = FBDEV_O20_CMN_InitHW,

	.O20_SetViewCtrl	 = FBDEV_O20_CMN_SetViewCtrl,
    .O20_SetConnCtrl     = FBDEV_O20_CMN_SetConnCtrl,

    .O20_WriteOSDHeader  = FBDEV_O20_CMN_WriteOSDHeader,
    .O20_SetOSDEnable    = FBDEV_O20_CMN_SetOSDEnable,
    .O20_GetOSDEnable    = FBDEV_O20_CMN_GetOSDEnable,
};

