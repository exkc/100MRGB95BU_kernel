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
#undef  V_MIRROR_TEST   /* 임시 코드임. 테스트시에만 임시로 풀어서 사용할것. CCC 에는 지울것 */
#define FIXED_BASE_ADDR /* OSD header 증 미사용되는 base_addr 와 ptr_plte 를 고정함 */

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/seq_file.h>
#include <linux/fb.h>

#include "fbdev_impl.h"
#include "fbdev_drv.h"
#include "fbdev_hw.h"
#include "fbdev_hw_o26.h"

#include "hma_alloc.h"

#ifdef FBDEV_O26_USE_CTOP_REGS
#include "../sys/sys_regs.h"
#endif

#ifdef INCLUDE_KDRV_OVI
#include "be_kapi.h"
#include "ovi_hal.h"
#endif

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif

#include "afbc_sw_drv.h"
#include "fbdev_hw_o26.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#ifdef BUILD_FEATURE_fpga
#undef CONFIG_LX_BOOT_LOGO
#define CONFIG_LX_BOOT_LOGO 0
#endif

#define BOOT_LOGO_MEM_POOL  "debug0"
#define SURFACE_MEM_POOL    "surface"

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define CHECK_AFBC_FBDEV(id)        ((id)==LX_FBDEV_ID_OSD0 || (id)==LX_FBDEV_ID_OSD1)
#define CHECK_AFRC_FBDEV(id)        ((id)==LX_FBDEV_ID_OSD0 || (id)==LX_FBDEV_ID_OSD1)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern int g_fbdev_use_isr_mon;

/*----------------------------------------------------------------------------------------
    Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_O26_CMN_InitFBCEnv(void);
static void FBDEV_O26_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt);
static void FBDEV_O26_CMN_WriteAFBCHdrRegs(int fb_dev_id, FBDEV_PLT_OSD_HDR_T osd_hdr[2],
        FBDEV_PLT_OSD_EXHDR_T* osd_exhdr);

static void FBDEV_O26_CMN_InitMirrorEnv(void);

static void FBDEV_O26_CMN_SetupGLB(void);
static void FBDEV_O26_CMN_InitGLBEnv(void);
static void FBDEV_O26_CMN_InitOSDPost(void);

static void FBDEV_O26_CMN_SetupExternalRenderer(int fb_dev_id, struct fb_info* fbinfo);
static void FBDEV_O26_CMN_AllocExternalRendererFrameBuffer(void);
static void FBDEV_O26_CMN_DestroyExternalRendererFrameBuffer(void);
static void FBDEV_O26_CMN_SetOutputCropRegion(bool crop_en,
        int img_width, int img_height, int xoffset, int yoffset, LX_RECT_T* crop_pos);

static void FBDEV_O26_CMN_ReInitHW(void);

static FBDEV_VSYNC_CLK_T FBDEV_O26_CMN_DetectVSyncClk(void);

static int  FBDEV_O26_CMN_CheckPQEDriverInitialization(void);
static void FBDEV_O26_CMN_NotifyPQEDriver(void);
static void FBDEV_O26_CMN_WaitPQEDriverEstreamerSync(int checker);

static void FBDEV_O26_CMN_BootLogoClearScheduler(struct work_struct* work);
static void FBDEV_O26_CMN_ShutdownOSDPath(void);

static void FBDEV_O26_CMN_EnableOSDHdrFlush(ULONG data);
static void FBDEV_O26_CMN_SetMute(bool onoff);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_osd_hdr_spinlock);

static struct workqueue_struct* fbdev_o26_wq;
static DECLARE_DELAYED_WORK(boot_logo_clear_work, FBDEV_O26_CMN_BootLogoClearScheduler);

static int  osd_boot_freeze_timeout = 0;    /* see SICDTV-8491. set 0 by default */
static int  osd_resume_freeze_timeout = 0;  /* see SICDTV-8491. set 0 by default */
static int  osd_pqefw_osd0_out_ctrl = 1;    /* SICDTV-4359 */

static int  osd_enable_logo_clear = 0;    /* see SICDTV-8556 */
static int  osd_boot_logo_clear_timeout = 3000; /* see SICDTV-8556 */
static int  osd_resume_logo_clear_timeout = 2000; /* see SICDTV-8556 */

static bool osd_logo_migration_required = true;
static bool osd_pqefw_ipc_enabled = true; /* see SICDTV-12981 */

static int  osd_fbc_version = FBDEV_HW_AFBC_VER_1_1; /* 0x10:AFBC1.0, 0x11:AFBC 1.1, 0x20:AFRC see SICDTV-9405 */

module_param_named(fbdev_o26_boot_freeze_timeout, osd_boot_freeze_timeout, int, 0644);
module_param_named(fbdev_o26_resume_freeze_timeout, osd_resume_freeze_timeout, int, 0644);

module_param_named(fbdev_o26_pqefw_osd0_out_ctrl, osd_pqefw_osd0_out_ctrl, int, 0644);

module_param_named(fbdev_o26_enable_logo_clear, osd_enable_logo_clear, int, 0644);
module_param_named(fbdev_o26_boot_logo_clear_timeout, osd_boot_logo_clear_timeout, int, 0644);
module_param_named(fbdev_o26_resume_logo_clear_timeout, osd_resume_logo_clear_timeout, int, 0644);

module_param_named(fbdev_o26_afbc_version, osd_fbc_version, int, 0644);

static int osd_hw_pm_suspend_stage = 0;
static int osd_hw_pm_restore_stage = 0;

static int osd_use_shutdown_path_on_suspend = 1;  /* see SICDTV-9009, SICDTV-9992 */
module_param_named(fbdev_o26_use_shutdown_path_on_suspend, osd_use_shutdown_path_on_suspend, int, 0644);

static unsigned long osd_bootlogo_fbmem_addr = 0x0;

static int fbdev_afbc_estreamer = 1;
module_param_named(fbdev_o26_afbc_estreamer, fbdev_afbc_estreamer, int, 0644);

/*========================================================================================
    Implementation Group
========================================================================================*/
int FBDEV_O26_CMN_GetHWXList(int fb_dev_id, int xlst[2])
{
    int afbc_xlst[2];

    return FBDEV_O26_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
}

int FBDEV_O26_CMN_GetHWXListEx(int fb_dev_id, int xlst[2], int afbc_xlst[2])
{
    int num_xlst = 0;
    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

    switch (fb_dev_id)
    {
        case LX_FBDEV_ID_OSD0:
        {
            if (hw_ctx->b_support_4kosd)
            {
                num_xlst = 2;
                xlst[0] = OSD_IN_OSD0;
                xlst[1] = OSD_IN_OSD1;
                afbc_xlst[0] = OSD_IN_OSD0;
                afbc_xlst[1] = OSD_IN_OSD1;
            }
            else
            {
                num_xlst = 1;
                xlst[0] = OSD_IN_OSD0;
                xlst[1] = -1;
                afbc_xlst[0] = OSD_IN_OSD0;
                afbc_xlst[1] = -1;
            }
        }
        break;

        // (2021/07/05)
        // fb1 는 실제 존재 하지 않으며, E-Streamer 등의 특수 목적으로만 사용할 수 있다.
        // 따라서 fb0, fb1 은 동일한 HW 를 설정할 수 있도록 조치한다.
        // fb1 은 4K OSD 전용이다.
        //
        // (2023/03/28) see http://clm.lge.com/issue/browse/SCDCR-5906
        // 4K TV 에서 E-Streamer 를 지원하는 경우를 추가 고려한다.
        case LX_FBDEV_ID_OSD1:
        {
            num_xlst = 1;
            xlst[0] = OSD_IN_OSD0;
            xlst[1] = -1;
            afbc_xlst[0] = OSD_IN_OSD0;
            afbc_xlst[1] = -1;
        }
        break;

        case LX_FBDEV_ID_CSR0:
        {
            num_xlst = 1;
            xlst[0] = OSD_IN_CSR0;
            xlst[1] = -1;
            afbc_xlst[0] = -1;
            afbc_xlst[1] = -1;
        }
        break;

        default:
        {
            num_xlst = 1;
            xlst[0] = -1;
            xlst[1] = -1;
            afbc_xlst[0] = -1;
            afbc_xlst[1] = -1;
        }
        break;
    }

    return num_xlst;
}

// OSD 입력 관점에서의 header 속성의 값을 read 한다.
// 참고로 cursor 는 POST 임
void FBDEV_O26_CMN_ReadOSDXDesc(int xidx, OSDX_DESC_T* desc, OSDX_DESC_FLAG flag)
{
    switch (xidx)
    {
        case OSD_IN_OSD0: // osd pre #0

            if (flag & OSDX_DESC_FLAG_CTRL_MAIN)
            {
                OSD_PRE_RdFL(osd0_ctrl_main);
                OSD_PRE_RdBlk(osd0_ctrl_main, desc->osd_ctrl_main);
            }

            if (flag & OSDX_DESC_FLAG_ADDR)
            {
                OSD_PRE_RdFL(osd0_base_addr);
                OSD_PRE_RdBlk(osd0_base_addr, desc->osd_base_addr);
            }

            if (flag & OSDX_DESC_FLAG_SWAP)
            {
                OSD_PRE_RdFL(osd0_ctrl_swap);
                OSD_PRE_RdBlk(osd0_ctrl_swap, desc->osd_ctrl_swap);
            }

            if (flag & OSDX_DESC_FLAG_PDEC)
            {
                OSD_PRE_RdFL(osd0_ctrl_pdec);
                OSD_PRE_RdBlk(osd0_ctrl_pdec, desc->osd_ctrl_pdec);
            }

            if (flag & OSDX_DESC_FLAG_HDR_ALL)
            {
                OSD_PRE_RdFL(osd0_ctrl_hdr0);
                OSD_PRE_RdFL(osd0_ctrl_hdr1);
                OSD_PRE_RdFL(osd0_ctrl_hdr2);
                OSD_PRE_RdFL(osd0_ctrl_hdr3);
                OSD_PRE_RdFL(osd0_ctrl_hdr4);
                OSD_PRE_RdFL(osd0_ctrl_hdr5);
                OSD_PRE_RdFL(osd0_ctrl_hdr6);

                OSD_PRE_RdBlk(osd0_ctrl_hdr0, desc->osd_ctrl_hdr0);
                OSD_PRE_RdBlk(osd0_ctrl_hdr1, desc->osd_ctrl_hdr1);
                OSD_PRE_RdBlk(osd0_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_PRE_RdBlk(osd0_ctrl_hdr3, desc->osd_ctrl_hdr3);
                OSD_PRE_RdBlk(osd0_ctrl_hdr4, desc->osd_ctrl_hdr4);
                OSD_PRE_RdBlk(osd0_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_PRE_RdBlk(osd0_ctrl_hdr6, desc->osd_ctrl_hdr6);
            }

            if (flag & OSDX_DESC_FLAG_HDR_2)
            {
                OSD_PRE_RdFL(osd0_ctrl_hdr2);
                OSD_PRE_RdBlk(osd0_ctrl_hdr2, desc->osd_ctrl_hdr2);
            }

            if (flag & OSDX_DESC_FLAG_HDR_5)
            {
                OSD_PRE_RdFL(osd0_ctrl_hdr5);
                OSD_PRE_RdBlk(osd0_ctrl_hdr2, desc->osd_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_0)
            {
                OSD_POST_RdFL(osd0_ctrl_sync0);
                OSD_POST_RdBlk(osd0_ctrl_sync0, desc->osd_ctrl_sync0);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_1)
            {
                OSD_POST_RdFL(osd0_ctrl_sync1);
                OSD_POST_RdBlk(osd0_ctrl_sync1, desc->osd_ctrl_sync1);
            }

            if (flag & OSDX_DESC_FLAG_SCALER)
            {
                OSD_POST_RdFL(osd0_ctrl_scaler);
                OSD_POST_RdBlk(osd0_ctrl_scaler, desc->osd_ctrl_scaler);
            }

            break;

        case OSD_IN_OSD1: // osd pre #1

            if (flag & OSDX_DESC_FLAG_CTRL_MAIN)
            {
                OSD_PRE_RdFL(osd1_ctrl_main);
                OSD_PRE_RdBlk(osd1_ctrl_main, desc->osd_ctrl_main);
            }

            if (flag & OSDX_DESC_FLAG_ADDR)
            {
                OSD_PRE_RdFL(osd1_base_addr);
                OSD_PRE_RdBlk(osd1_base_addr, desc->osd_base_addr);
            }

            if (flag & OSDX_DESC_FLAG_SWAP)
            {
                OSD_PRE_RdFL(osd1_ctrl_swap);
                OSD_PRE_RdBlk(osd1_ctrl_swap, desc->osd_ctrl_swap);
            }

            if (flag & OSDX_DESC_FLAG_PDEC)
            {
                OSD_PRE_RdFL(osd1_ctrl_pdec);
                OSD_PRE_RdBlk(osd1_ctrl_pdec, desc->osd_ctrl_pdec);
            }

            if (flag & OSDX_DESC_FLAG_HDR_ALL)
            {
                OSD_PRE_RdFL(osd1_ctrl_hdr0);
                OSD_PRE_RdFL(osd1_ctrl_hdr1);
                OSD_PRE_RdFL(osd1_ctrl_hdr2);
                OSD_PRE_RdFL(osd1_ctrl_hdr3);
                OSD_PRE_RdFL(osd1_ctrl_hdr4);
                OSD_PRE_RdFL(osd1_ctrl_hdr5);
                OSD_PRE_RdFL(osd1_ctrl_hdr6);

                OSD_PRE_RdBlk(osd1_ctrl_hdr0, desc->osd_ctrl_hdr0);
                OSD_PRE_RdBlk(osd1_ctrl_hdr1, desc->osd_ctrl_hdr1);
                OSD_PRE_RdBlk(osd1_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_PRE_RdBlk(osd1_ctrl_hdr3, desc->osd_ctrl_hdr3);
                OSD_PRE_RdBlk(osd1_ctrl_hdr4, desc->osd_ctrl_hdr4);
                OSD_PRE_RdBlk(osd1_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_PRE_RdBlk(osd1_ctrl_hdr6, desc->osd_ctrl_hdr6);
            }

            if (flag & OSDX_DESC_FLAG_HDR_2)
            {
                OSD_PRE_RdFL(osd1_ctrl_hdr2);
                OSD_PRE_RdBlk(osd1_ctrl_hdr2, desc->osd_ctrl_hdr2);
            }

            if (flag & OSDX_DESC_FLAG_HDR_5)
            {
                OSD_PRE_RdFL(osd1_ctrl_hdr5);
                OSD_PRE_RdBlk(osd1_ctrl_hdr5, desc->osd_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_0)
            {
                OSD_POST_RdFL(osd0_ctrl_sync0);
                OSD_POST_RdBlk(osd0_ctrl_sync0, desc->osd_ctrl_sync0);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_1)
            {
                OSD_POST_RdFL(osd0_ctrl_sync1);
                OSD_POST_RdBlk(osd0_ctrl_sync1, desc->osd_ctrl_sync1);
            }

            if (flag & OSDX_DESC_FLAG_SCALER)
            {
                OSD_POST_RdFL(osd0_ctrl_scaler);
                OSD_POST_RdBlk(osd0_ctrl_scaler, desc->osd_ctrl_scaler);
            }

            break;

        case OSD_IN_CSR0: // csr0

            if (flag & OSDX_DESC_FLAG_CTRL_MAIN)
            {
                OSD_POST_RdFL(csr0_ctrl_main);
                OSD_POST_RdBlk(csr0_ctrl_main, desc->osd_ctrl_main);
            }

            if (flag & OSDX_DESC_FLAG_ADDR)
            {
                OSD_POST_RdFL(csr0_base_addr);
                OSD_POST_RdBlk(csr0_base_addr, desc->osd_base_addr);
            }

            if (flag & OSDX_DESC_FLAG_SWAP)
            {
                OSD_POST_RdFL(csr0_ctrl_swap);
                OSD_POST_RdBlk(csr0_ctrl_swap, desc->osd_ctrl_swap);
            }

            if (flag & OSDX_DESC_FLAG_PDEC)
            {
                OSD_POST_RdFL(csr0_ctrl_pdec);
                OSD_POST_RdBlk(csr0_ctrl_pdec, desc->osd_ctrl_pdec);
            }

            if (flag & OSDX_DESC_FLAG_HDR_ALL)
            {
                OSD_POST_RdFL(csr0_ctrl_hdr0);
                OSD_POST_RdFL(csr0_ctrl_hdr1);
                OSD_POST_RdFL(csr0_ctrl_hdr2);
                OSD_POST_RdFL(csr0_ctrl_hdr3);
                OSD_POST_RdFL(csr0_ctrl_hdr4);
                OSD_POST_RdFL(csr0_ctrl_hdr5);
                OSD_POST_RdFL(csr0_ctrl_hdr6);

                OSD_POST_RdBlk(csr0_ctrl_hdr0, desc->osd_ctrl_hdr0);
                OSD_POST_RdBlk(csr0_ctrl_hdr1, desc->osd_ctrl_hdr1);
                OSD_POST_RdBlk(csr0_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_POST_RdBlk(csr0_ctrl_hdr3, desc->osd_ctrl_hdr3);
                OSD_POST_RdBlk(csr0_ctrl_hdr4, desc->osd_ctrl_hdr4);
                OSD_POST_RdBlk(csr0_ctrl_hdr4, desc->osd_ctrl_hdr5);
                OSD_POST_RdBlk(csr0_ctrl_hdr4, desc->osd_ctrl_hdr6);
            }

            if (flag & OSDX_DESC_FLAG_HDR_2)
            {
                OSD_POST_RdFL(csr0_ctrl_hdr2);
                OSD_POST_RdBlk(csr0_ctrl_hdr2, desc->osd_ctrl_hdr2);
            }

            if (flag & OSDX_DESC_FLAG_HDR_5)
            {
                OSD_POST_RdFL(csr0_ctrl_hdr5);
                OSD_POST_RdBlk(csr0_ctrl_hdr5, desc->osd_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_0)
            {
                OSD_POST_RdFL(csr0_ctrl_sync0);
                OSD_POST_RdBlk(csr0_ctrl_sync0, desc->osd_ctrl_sync0);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_1)
            {
                OSD_POST_RdFL(csr0_ctrl_sync1);
                OSD_POST_RdBlk(csr0_ctrl_sync1, desc->osd_ctrl_sync1);
            }

            if (flag & OSDX_DESC_FLAG_SCALER)
            {
                OSD_POST_RdFL(csr0_ctrl_scaler);
                OSD_POST_RdBlk(csr0_ctrl_scaler, desc->csr_ctrl_scaler);
            }

            break;

        default:
            FBDEV_ERROR("invalid xidx=%d\n", xidx);
            break;
    }
}

// OSD 입력 관점에서의 header 속성의 값을 write 한다.
// 참고로 cursor 는 POST 임
void FBDEV_O26_CMN_WriteOSDXDesc(int xidx, OSDX_DESC_T* desc, OSDX_DESC_FLAG flag)
{
    switch (xidx)
    {
        case OSD_IN_OSD0: // osd pre #0

            if (flag & OSDX_DESC_FLAG_CTRL_MAIN)
            {
                OSD_PRE_WrBlk(osd0_ctrl_main, desc->osd_ctrl_main);
                OSD_PRE_WrFL(osd0_ctrl_main);
            }

            if (flag & OSDX_DESC_FLAG_ADDR)
            {
                OSD_PRE_WrBlk(osd0_base_addr, desc->osd_base_addr);
                OSD_PRE_WrFL(osd0_base_addr);

                OSD_PRE_WrBlk(osd0_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_PRE_WrFL(osd0_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SWAP)
            {
                OSD_PRE_WrBlk(osd0_ctrl_swap, desc->osd_ctrl_swap);
                OSD_PRE_WrFL(osd0_ctrl_swap);
            }

            if (flag & OSDX_DESC_FLAG_PDEC)
            {
                OSD_PRE_WrBlk(osd0_ctrl_pdec, desc->osd_ctrl_pdec);
                OSD_PRE_WrFL(osd0_ctrl_pdec);
            }

            if (flag & OSDX_DESC_FLAG_HDR_ALL)
            {
                OSD_PRE_WrBlk(osd0_ctrl_hdr0, desc->osd_ctrl_hdr0);
                OSD_PRE_WrBlk(osd0_ctrl_hdr1, desc->osd_ctrl_hdr1);
                OSD_PRE_WrBlk(osd0_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_PRE_WrBlk(osd0_ctrl_hdr3, desc->osd_ctrl_hdr3);
                OSD_PRE_WrBlk(osd0_ctrl_hdr4, desc->osd_ctrl_hdr4);
                OSD_PRE_WrBlk(osd0_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_PRE_WrBlk(osd0_ctrl_hdr6, desc->osd_ctrl_hdr6);

                OSD_PRE_WrFL(osd0_ctrl_hdr0);
                OSD_PRE_WrFL(osd0_ctrl_hdr1);
                OSD_PRE_WrFL(osd0_ctrl_hdr2);
                OSD_PRE_WrFL(osd0_ctrl_hdr3);
                OSD_PRE_WrFL(osd0_ctrl_hdr4);
                OSD_PRE_WrFL(osd0_ctrl_hdr5);
                OSD_PRE_WrFL(osd0_ctrl_hdr6);
            }

            if (flag & OSDX_DESC_FLAG_HDR_2)
            {
                OSD_PRE_WrBlk(osd0_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_PRE_WrFL(osd0_ctrl_hdr2);
            }

            if (flag & OSDX_DESC_FLAG_HDR_5)
            {
                OSD_PRE_WrBlk(osd0_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_PRE_WrFL(osd0_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_0)
            {
                OSD_POST_WrBlk(osd0_ctrl_sync0, desc->osd_ctrl_sync0);
                OSD_POST_WrFL(osd0_ctrl_sync0);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_1)
            {
                OSD_POST_WrBlk(osd0_ctrl_sync1, desc->osd_ctrl_sync1);
                OSD_POST_WrFL(osd0_ctrl_sync1);
            }

            if (flag & OSDX_DESC_FLAG_SCALER)
            {
                OSD_POST_WrBlk(osd0_ctrl_scaler, desc->osd_ctrl_scaler);
                OSD_POST_WrFL(osd0_ctrl_scaler);
            }

            break;

        case OSD_IN_OSD1: // osd pre #1

            if (flag & OSDX_DESC_FLAG_CTRL_MAIN)
            {
                OSD_PRE_WrBlk(osd1_ctrl_main, desc->osd_ctrl_main);
                OSD_PRE_WrFL(osd1_ctrl_main);
            }

            if (flag & OSDX_DESC_FLAG_ADDR)
            {
                OSD_PRE_WrBlk(osd1_base_addr, desc->osd_base_addr);
                OSD_PRE_WrFL(osd1_base_addr);

                OSD_PRE_WrBlk(osd1_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_PRE_WrFL(osd1_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SWAP)
            {
                OSD_PRE_WrBlk(osd1_ctrl_swap, desc->osd_ctrl_swap);
                OSD_PRE_WrFL(osd1_ctrl_swap);
            }

            if (flag & OSDX_DESC_FLAG_PDEC)
            {
                OSD_PRE_WrBlk(osd1_ctrl_pdec, desc->osd_ctrl_pdec);
                OSD_PRE_WrFL(osd1_ctrl_pdec);
            }

            if (flag & OSDX_DESC_FLAG_HDR_ALL)
            {
                OSD_PRE_WrBlk(osd1_ctrl_hdr0, desc->osd_ctrl_hdr0);
                OSD_PRE_WrBlk(osd1_ctrl_hdr1, desc->osd_ctrl_hdr1);
                OSD_PRE_WrBlk(osd1_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_PRE_WrBlk(osd1_ctrl_hdr3, desc->osd_ctrl_hdr3);
                OSD_PRE_WrBlk(osd1_ctrl_hdr4, desc->osd_ctrl_hdr4);
                OSD_PRE_WrBlk(osd1_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_PRE_WrBlk(osd1_ctrl_hdr6, desc->osd_ctrl_hdr6);

                OSD_PRE_WrFL(osd1_ctrl_hdr0);
                OSD_PRE_WrFL(osd1_ctrl_hdr1);
                OSD_PRE_WrFL(osd1_ctrl_hdr2);
                OSD_PRE_WrFL(osd1_ctrl_hdr3);
                OSD_PRE_WrFL(osd1_ctrl_hdr4);
                OSD_PRE_WrFL(osd1_ctrl_hdr5);
                OSD_PRE_WrFL(osd1_ctrl_hdr6);
            }

            if (flag & OSDX_DESC_FLAG_HDR_2)
            {
                OSD_PRE_WrBlk(osd1_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_PRE_WrFL(osd1_ctrl_hdr2);
            }

            if (flag & OSDX_DESC_FLAG_HDR_5)
            {
                OSD_PRE_WrBlk(osd1_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_PRE_WrFL(osd1_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_0)
            {
                OSD_POST_WrBlk(osd0_ctrl_sync0, desc->osd_ctrl_sync0);
                OSD_POST_WrFL(osd0_ctrl_sync0);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_1)
            {
                OSD_POST_WrBlk(osd0_ctrl_sync1, desc->osd_ctrl_sync1);
                OSD_POST_WrFL(osd0_ctrl_sync1);
            }

            if (flag & OSDX_DESC_FLAG_SCALER)
            {
                OSD_POST_WrBlk(osd0_ctrl_scaler, desc->osd_ctrl_scaler);
                OSD_POST_WrFL(osd0_ctrl_scaler);
            }

            break;

        case OSD_IN_CSR0: // csr0

            if (flag & OSDX_DESC_FLAG_CTRL_MAIN)
            {
                OSD_POST_WrBlk(csr0_ctrl_main, desc->osd_ctrl_main);
                OSD_POST_WrFL(csr0_ctrl_main);
            }

            if (flag & OSDX_DESC_FLAG_ADDR)
            {
                OSD_POST_WrBlk(csr0_base_addr, desc->osd_base_addr);
                OSD_POST_WrFL(csr0_base_addr);

                OSD_POST_WrBlk(csr0_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_POST_WrFL(csr0_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SWAP)
            {
                OSD_POST_WrBlk(csr0_ctrl_swap, desc->osd_ctrl_swap);
                OSD_POST_WrFL(csr0_ctrl_swap);
            }

            if (flag & OSDX_DESC_FLAG_PDEC)
            {
                OSD_POST_WrBlk(csr0_ctrl_pdec, desc->osd_ctrl_pdec);
                OSD_POST_WrFL(csr0_ctrl_pdec);
            }

            if (flag & OSDX_DESC_FLAG_HDR_ALL)
            {
                OSD_POST_WrBlk(csr0_ctrl_hdr0, desc->osd_ctrl_hdr0);
                OSD_POST_WrBlk(csr0_ctrl_hdr1, desc->osd_ctrl_hdr1);
                OSD_POST_WrBlk(csr0_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_POST_WrBlk(csr0_ctrl_hdr3, desc->osd_ctrl_hdr3);
                OSD_POST_WrBlk(csr0_ctrl_hdr4, desc->osd_ctrl_hdr4);
                OSD_POST_WrBlk(csr0_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_POST_WrBlk(csr0_ctrl_hdr6, desc->osd_ctrl_hdr6);

                OSD_POST_WrFL(csr0_ctrl_hdr0);
                OSD_POST_WrFL(csr0_ctrl_hdr1);
                OSD_POST_WrFL(csr0_ctrl_hdr2);
                OSD_POST_WrFL(csr0_ctrl_hdr3);
                OSD_POST_WrFL(csr0_ctrl_hdr4);
                OSD_POST_WrFL(csr0_ctrl_hdr5);
                OSD_POST_WrFL(csr0_ctrl_hdr6);
            }

            if (flag & OSDX_DESC_FLAG_HDR_2)
            {
                OSD_POST_WrBlk(csr0_ctrl_hdr2, desc->osd_ctrl_hdr2);
                OSD_POST_WrFL(csr0_ctrl_hdr2);
            }

            if (flag & OSDX_DESC_FLAG_HDR_5)
            {
                OSD_POST_WrBlk(csr0_ctrl_hdr5, desc->osd_ctrl_hdr5);
                OSD_POST_WrFL(csr0_ctrl_hdr5);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_0)
            {
                OSD_POST_WrBlk(csr0_ctrl_sync0, desc->osd_ctrl_sync0);
                OSD_POST_WrFL(csr0_ctrl_sync0);
            }

            if (flag & OSDX_DESC_FLAG_SYNC_1)
            {
                OSD_POST_WrBlk(csr0_ctrl_sync1, desc->osd_ctrl_sync1);
                OSD_POST_WrFL(csr0_ctrl_sync1);
            }

            if (flag & OSDX_DESC_FLAG_SCALER)
            {
                OSD_POST_WrBlk(csr0_ctrl_scaler, desc->csr_ctrl_scaler);
                OSD_POST_WrFL(csr0_ctrl_scaler);
            }

            break;

        default:
            FBDEV_ERROR("invalid xidx=%d\n", xidx);
            break;
    }
}
// check if 4K output is enabled
bool FBDEV_O26_CMN_IsUHDDispMode(void)
{
    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    return (hw_ctx->hw_disp_width > 2048) ? true : false;
}

// enable OSD HW update
// if OSD heaer flag is not set, OSD is not updated
static void FBDEV_O26_CMN_EnableOSDHdrFlush(ULONG data)
{
    int i;

    FBDEV_NOTI("<!> enable osd_hdr_flush & exit OSD freeze stage. afbc=%d, afrc=%d\n",
               FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_AFBC, LX_FBDEV_ID_OSD0),
               FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_AFRC, LX_FBDEV_ID_OSD0));

    /* enable osd_hdr_flush to unfreeze OSD */
    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        FBDEV_WIN_CTX_T* wctx = FBDEV_GetWinCtx(i);
        struct scanvas* canvas = FBDEV_GetWinCanvas(i);

        FBDEV_CHECK_CODE(NULL == wctx, continue, "invalid fb(%d) wctx\n", i);
        FBDEV_CHECK_CODE(NULL == canvas, continue, "invalid fb(%d) canvas\n", i);

        /* if freeize is already disabled, ignore osd hdr flush */
        if (wctx->status.b_osd_hdr_flush)
        {
            FBDEV_HW_DEBUG("fb(%d) osd_hdr_flush is already enabled\n", i);
            continue;
        }

        FBDEV_NOTI("++ fb(%d) flip_cnt=%d, total_flip_cnt=%d\n",
                   i, wctx->status.fb_flip_cnt, wctx->status.total_fb_flip_cnt);

        wctx->status.b_osd_hdr_flush = true;

        /* (2020/06/11)
         * 수정된 OSD 초기화 정책에 의하여 이 함수는 단순히 b_osd_hdr_flush 를 활성화 하는 역할로
         * 축소한다. 향후 함수 목적을 수정하거나, 완전히 삭제할 수도 있음
         */
        /* do nothing */
    }
}

// clear current logo screen after OSD initialization
static void FBDEV_O26_CMN_BootLogoClearScheduler(struct work_struct* work)
{
    FBDEV_NOTI("+ logo clear work started\n");

    osd_logo_migration_required = true;
    FBDEV_O26_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_CLEAR);
}

// move boot logo framebuffer to safe region
void FBDEV_O26_CMN_MigrateBootLogo(FBDEV_PLT_BOOT_LOGO_MODE_T mode)
{
#ifdef FBDEV_M23_USE_MIXER_MUTE
    FBDEV_NOTI("osd mixer_mute used, ignore logo migration\n");
#else
    int rc;
    OS_CACHE_MAP_T cmap_src, cmap_dst;
    OSDX_DESC_T osdx_desc;

    UINT32 fbmem_size;
    UINT32 fbmem_src = 0;
    UINT32 fbmem_dst = 0;

    int xidx = OSD_IN_OSD0; // OSD0 fixed

    /* allow this function to run once at cold boot regardless of result */
    if (osd_logo_migration_required == false)
    {
        FBDEV_NOTI("ignore boot logo migration request\n");
        return;
    }

    osd_logo_migration_required = false;

    memset(&cmap_src, 0x0, sizeof(OS_CACHE_MAP_T));
    memset(&cmap_dst, 0x0, sizeof(OS_CACHE_MAP_T));

    // boot logo 이미지는 2K 로 가정한다.
    // 추후 크기 변경시 해당 코드 변경 할것.
    fbmem_size = afbc_sw_get_image_size(NULL, 1920, 1080);
    fbmem_size = ALIGN(fbmem_size, (1 << 20));

    // 기존 방식은 surface 메모리풀의 특정 고정된 영역에 일방적으로 백업 이미지를 복사하는 것으로 CMA 속성에 대응이 불가하다.
    // 신규 방식에서는 debug0 에서 임시 메모리를 할당 받도록 한다.
    // 할당된 메모리는 osd_bootlogo_fbmem_addr 에 저장되며, FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE 에서 해제된다.
    //
    fbmem_dst = hma_alloc(BOOT_LOGO_MEM_POOL, fbmem_size, PAGE_SIZE);
    FBDEV_CHECK_ERROR(!fbmem_dst, return, "%s not found or alloc error\n", BOOT_LOGO_MEM_POOL);

    FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_ALL);
    fbmem_src = osdx_desc.osd_ctrl_hdr6.osd_hdr_ptr_bmp;

    FBDEV_WARN("logo fbmem src=0x%08x, dst=0x%08x\n", fbmem_src, fbmem_dst);

    // dst 버퍼로 logo 이미지를 그대로 복사한다.
    if (mode == BOOT_LOGO_MODE_IMAGE_KEEP)
    {
        FBDEV_WARN("++ BOOT_LOGO_MODE_KEEP\n");

        rc = OS_OpenCacheMap(&cmap_src, (ULONG)fbmem_src, fbmem_size);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "cache op fail\n");

        rc = OS_OpenCacheMap(&cmap_dst, (ULONG)fbmem_dst, fbmem_size);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "cache op fail\n");

        rc = OS_InvalCacheMap(&cmap_src, 0, fbmem_size);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "cache op fail\n");

        memcpy(cmap_dst.virt_addr, cmap_src.virt_addr, fbmem_size);

        rc = OS_CleanCacheMap(&cmap_dst, 0, fbmem_size);
        FBDEV_CHECK_CODE(rc != RET_OK, goto func_exit, "cache op fail\n");
    }
    // dst 버퍼의 내용을 0x0000000 으로 칠한다.
    else if (mode == BOOT_LOGO_MODE_IMAGE_CLEAR)
    {
        struct afbc_framebuffer* afbc_fb;

        FBDEV_WARN("++ BOOT_LOGO_MODE_CLEAR\n");

        afbc_fb = afbc_sw_alloc_framebuffer(NULL, fbmem_dst, 1920, 1080, 0, 0, 0);

        if (afbc_fb)
        {
            afbc_sw_fill(NULL, afbc_fb, 0x00000000);
            afbc_sw_free_framebuffer(NULL, afbc_fb);
        }
        else
        {
            FBDEV_WARN("afbc_fb NULL. can't alloc\n");
        }
    }
    else /* NONE */
    {
        FBDEV_WARN("++ BOOT_LOGO_MODE_IMAGE_NONE: do nothing ++ \n");
    }

    // boot 에서 구성된 AFBC 설정을 그대로 유지하며, fbmem 값만 업데이트한다
    {
        AFBC_Wr01(xidx, ctrl_afbc_1, hd_base,      fbmem_dst);
        AFBC_Wr01(xidx, ctrl_afbc_8, pl_data_base, fbmem_dst);
        AFBC_WrFL(xidx, ctrl_afbc_1);
        AFBC_WrFL(xidx, ctrl_afbc_8);

        AFBC_RdFL(xidx, ctrl_afbc_0);
        AFBC_Wr01(xidx, ctrl_afbc_0, update_ready_flag, 0x1);
        AFBC_WrFL(xidx, ctrl_afbc_0);
    }

    /* raxis.lim (2019/10/23)
     * becuase osd_hdr_ready_flag_en flag is enabled by subsequent InitOSDLayer() calls,
     * we should set osd_hdr_ready_flagn=1 here to update real framebuffer address
     */
    osdx_desc.osd_ctrl_hdr6.osd_hdr_ptr_bmp = fbmem_dst;
    osdx_desc.osd_ctrl_main.osd_hdr_ready_flag_en = 1;
    osdx_desc.osd_ctrl_main.osd_hdr_ready_flag = 1;

    FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_HDR_ALL);

    FIXME_NOTE("Boot Logo 에서 설정된 GLB 는 그대로 유지할것")

    FBDEV_NOTI("logo fbmem old=0x%08x new=0x%08x\n", fbmem_src, fbmem_dst);

    osd_bootlogo_fbmem_addr = fbmem_dst;

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

void FBDEV_O26_CMN_FreeBootLogoFrameBuffer(void)
{
    if (osd_bootlogo_fbmem_addr)
    {
        hma_free(BOOT_LOGO_MEM_POOL, osd_bootlogo_fbmem_addr);
        osd_bootlogo_fbmem_addr = 0x0;
    }
}

void FBDEV_O26_CMN_SetMixerMute(BOOLEAN en, UINT32 color)
{
    UINT8 r = (color >> 16) & 0xff;
    UINT8 g = (color >> 8) & 0xff;
    UINT8 b = color & 0xff;

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

    FBDEV_NOTI("mixer_mute=%s, color=0x%06x\n", en ? "on" : "off", color);

    if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
    {
        OSDX_RdFL(osdx_blend_osd_mixer[1], ctrl_bosd_mixer_output);
        OSDX_Wr01(osdx_blend_osd_mixer[1], ctrl_bosd_mixer_output, reg_mixer_out_en, en);
        OSDX_Wr01(osdx_blend_osd_mixer[1], ctrl_bosd_mixer_output, reg_mixer_out_r, r);
        OSDX_Wr01(osdx_blend_osd_mixer[1], ctrl_bosd_mixer_output, reg_mixer_out_g, g);
        OSDX_Wr01(osdx_blend_osd_mixer[1], ctrl_bosd_mixer_output, reg_mixer_out_b, b);
        OSDX_WrFL(osdx_blend_osd_mixer[1], ctrl_bosd_mixer_output);
    }
    else
    {
        FBDEV_ERROR("not supported\n");
    }
}

void FBDEV_O26_CMN_RunBootLogoTimer(UINT32 ms, bool bForce)
{
#if (CONFIG_LX_BOOT_LOGO==1)
    static bool b_timer_req = true;
    static OS_TIMER_T osd_en_timer;

    FBDEV_NOTI("start bootlogo timer %d ms whth force=%d, bootlogo=%d\n", ms, bForce, CONFIG_LX_BOOT_LOGO);

    if (b_timer_req || bForce)
    {
        b_timer_req = false;
        FBDEV_BOOT_DEBUG("start boot timer %d ms (%d)\n", ms, bForce);

        if (ms > 0)
        {
            OS_InitTimer(&osd_en_timer);
            OS_StartTimer(&osd_en_timer, FBDEV_O26_CMN_EnableOSDHdrFlush, OS_TIMER_TIMEOUT, ms, 0x0);
        }
        else
        {
            FBDEV_O26_CMN_EnableOSDHdrFlush(0x0);
        }
    }

#else
    FBDEV_NOTI("bootlogo disbaled, enable OSD header flush now\n");
    FBDEV_O26_CMN_EnableOSDHdrFlush(0x0);
#endif
}

static FBDEV_VSYNC_CLK_T FBDEV_O26_CMN_DetectVSyncClk(void)
{
#if (defined FBDEV_O26_USE_CTOP_REGS && defined INCLUDE_KDRV_SYS)

    FIXME_NOTE("미구현")

    FBDEV_WARN("not implemeted yet\n");
    return FBDEV_VSYNC_CLK_60HZ;

#else
    FBDEV_NOTI("SYNC detector not ready.. default vsync = 60Hz\n");
    return FBDEV_VSYNC_CLK_60HZ;
#endif
}

static void FBDEV_O26_CMN_NotifyPQEDriver(void)
{
#if (defined INCLUDE_KDRV_OVI && !defined BUILD_FEATURE_fpga)
    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

    /* see be/top/be_top_hal.h */
    extern int BE_TOP_HAL_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T * pstParams);
    LX_BE_FBDEV_STATUS_T osd2pqe_status;

    osd2pqe_status.bFbdevInitDone = hw_ctx->user_initcall_ctrl.status.osd_init_done;
    osd2pqe_status.bOsdVReverseOn = hw_ctx->user_initcall_ctrl.status.osd_v_mirror;
    osd2pqe_status.bEStreamerOn   = hw_ctx->user_initcall_ctrl.status.osd_estreamer;
    osd2pqe_status.b4kOSDResolution = (hw_ctx->b_support_4kosd) ? true : false;
    osd2pqe_status.bOsdSharpnessWAOn = false;

    FBDEV_NOTI("+ notify PQE FW to setup : inited=%d, 4kosd=%d, vmirror=%d, est=%d, shpwa=%d\n",
               osd2pqe_status.bFbdevInitDone,
               osd2pqe_status.b4kOSDResolution,
               osd2pqe_status.bOsdVReverseOn,
               osd2pqe_status.bEStreamerOn,
               osd2pqe_status.bOsdSharpnessWAOn);

    FBDEV_CHECK_ERROR(RET_OK != BE_TOP_HAL_InformFBDEVStatus(&osd2pqe_status), /* nop */,
                      "BE_TOP_HAL_InformFBDEVStatus error\n");
#else
    FBDEV_NOTI("+ notify PQE FW to setup : dummy\n");
#endif
}

static int  FBDEV_O26_CMN_CheckPQEDriverInitialization(void)
{
#if (defined INCLUDE_KDRV_OVI && !defined BUILD_FEATURE_fpga)
    /* see be/top/be_top_hal.h */
    extern int BE_TOP_HAL_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T * pstParams);
    LX_BE_FW_OSD_STATUS_T pqe2osd_status;

    FBDEV_CHECK_ERROR(RET_OK != BE_TOP_HAL_GetFWOSDStatus(&pqe2osd_status), return RET_ERROR,
                      "BE_TOP_HAL_GetFWOSDStatus error\n");

    FBDEV_NOTI("+ wait for PQE FW to setup : %d/%d\n",
               pqe2osd_status.bFwOsdOrbitInitDone, pqe2osd_status.bFwOsdSrInitDone);

    if (pqe2osd_status.bFwOsdOrbitInitDone && pqe2osd_status.bFwOsdSrInitDone)
        return RET_OK;
    else
        return RET_TIMEOUT;

#else
    FBDEV_NOTI("+ wait for PQE FW to setup : dummy\n");
    return RET_OK;
#endif
}

// PQE (혹은 F22) 에게 전달되는 정보가 반영되었는지 확인이 필요할때, 최소 2개의 vsync wait 를 보장해야 한다.
// 이 함수는 B.OSD path 에서만 의미가 있으며, S.OSD path 에서는 F22 에서 필요시 처리를 해주기 때문에, 최소
// usleep 으로 대응하도록 한다.
//
// (2023/10/12) OSD kdriver 와 PQE FW 간의 estreamer 상태 동기화를 추가한다.
// 67.2 ms ( 60Hz 기준으로 약 4 vsync ) 정도 충분히 wait 하도록 한다.
// see http://clm.lge.com/issue/browse/SICDTV-13258
//
// (2023/11/06) 동기화를 위한 polling 주기와 max timeout 값을 조정한다.
// SoCTS 기준인 최대 50ms 가 넘어가지 않도록 45ms(5ms x 9회) wait 하도록 한다.
//
static void FBDEV_O26_CMN_WaitPQEDriverEstreamerSync(int checker)
{
#if (defined INCLUDE_KDRV_OVI && !defined BUILD_FEATURE_fpga)

    /* see be/top/be_top_hal.h */
    extern int BE_TOP_HAL_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T * pstParams);
    LX_BE_FW_OSD_STATUS_T pqe2osd_status;

#define PQE_VSYNC_CNT 9 // 5.0 ms * 9 = 45 ms

    int i;
    UINT64 base_tick = OS_GetMsecTicks();

    if (osd_hw_pm_suspend_stage)
    {
        FBDEV_NOTI("+ wait for PQE FW to sync estreamer. skip by the suspending stage\n");
        return;
    }

    if (!osd_pqefw_ipc_enabled)
    {
        FBDEV_NOTI("+ wait for PQE FW to sync estreamer. skip by the disabled pqe ipc\n");
        return;
    }

    for (i = PQE_VSYNC_CNT; i > 0; i--)
    {
        usleep_range(5000, 5000); // fixed 50ms

        if (RET_OK == BE_TOP_HAL_GetFWOSDStatus(&pqe2osd_status))
        {
            FBDEV_NOTI("+ wait for PQE FW to sync estreamer. req=%d, ack=%d, time=%dms\n",
                       checker,
                       pqe2osd_status.bFwEstreamerOn,
                       (int)(OS_GetMsecTicks() - base_tick));

            if (pqe2osd_status.bFwEstreamerOn == checker)
            {
                return;
            }
        }
    }

    FBDEV_ERROR("+ wait for PQE FW to sync estreamer. timeout!! \n");
#endif
}

// GLB 를 기본 설정으로 초기화한다.
// OSC2/3 은 사용하지 않으며, OSD0/1 은 상황에 맞게 설정한다.
static void FBDEV_O26_CMN_InitGLBEnv(void)
{
    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_GLB_CTRL_T* glb_ctrl = FBDEV_PLT_GET_GLB_CTRL(hw_ctx);

    int fb_w = hw_ctx->hw_fb0_width;
    int fb_h = hw_ctx->hw_fb0_height;

    glb_ctrl->mux[OSD_IN_OSD0].osd_en = 1;
    glb_ctrl->mux[OSD_IN_OSC2].osd_en = 0;
    glb_ctrl->mux[OSD_IN_OSC3].osd_en = 0;

    // 4K OSD 를 지원하는 경우 2K L/R 을 지원하도록 한다.
    if (hw_ctx->b_support_4kosd)
    {
        glb_ctrl->mux[OSD_IN_OSD1].osd_en = 1;

        glb_ctrl->mux[OSD_IN_OSD0].coord = LX_MAKE_RECT(0, 0, fb_w / 2, fb_h);
        glb_ctrl->mux[OSD_IN_OSD1].coord = LX_MAKE_RECT(fb_w / 2, 0, fb_w / 2, fb_h);
    }
    else
    {
        glb_ctrl->mux[OSD_IN_OSD1].osd_en = 0;

        glb_ctrl->mux[OSD_IN_OSD0].coord = LX_MAKE_RECT(0, 0, fb_w, fb_h);
    }

    glb_ctrl->mux[OSD_IN_OSC2].galpha_en = 0;
    glb_ctrl->mux[OSD_IN_OSC2].galpha_en = 0;
    glb_ctrl->mux[OSD_IN_OSD0].galpha_en = 0;
    glb_ctrl->mux[OSD_IN_OSD1].galpha_en = 0;

    glb_ctrl->mux[OSD_IN_OSC2].galpha = 0x3ff; // 1023
    glb_ctrl->mux[OSD_IN_OSC3].galpha = 0x3ff; // 1023
    glb_ctrl->mux[OSD_IN_OSD0].galpha = 0x3ff; // 1023
    glb_ctrl->mux[OSD_IN_OSD1].galpha = 0x3ff; // 1023

    FIXME_NOTE("zroder 는 추후 처리하도록 함")
    glb_ctrl->mux[OSD_IN_OSC2].zorder = 0;
    glb_ctrl->mux[OSD_IN_OSC3].zorder = 1;
    glb_ctrl->mux[OSD_IN_OSD0].zorder = 2;
    glb_ctrl->mux[OSD_IN_OSD1].zorder = 3;

    glb_ctrl->canvas_w = fb_w;
    glb_ctrl->canvas_h = fb_h;

    FBDEV_O26_CMN_SetupGLB();
}

//
//
// FIXME: GLB 에서 입력 4개에 대하여 mux 설정에 따라, 출력 대상으로 순서가 바뀐다.
// 현재는 기본값 설정, 즉 mux 순서를 바꾸지 않기 때문에, 동일하게 처리할 수 있다.
// 추후 해당 부분 query 하는 함수로 바꾸도록 한다.
// 본 함수는 외부에서 설정한 glb_ctrl 구조체 값에 기반하여 GLB 라우팅 및 설정을
// 한번에 하는것이 목적이다.
void FBDEV_O26_CMN_SetupGLB(void)
{
    int  i;

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_GLB_CTRL_T* glb_ctrl = FBDEV_PLT_GET_GLB_CTRL(hw_ctx);

    GLB_RdFL(glb_ctrl_00);
    GLB_RdFL(glb_ctrl_01);
    GLB_RdFL(glb_ctrl_03);
    GLB_RdFL(glb_ctrl_04);
    //GLB_RdFL(glb_ctrl_05);

    GLB_Wr01(glb_ctrl_00, rv_merg_0_en, 0x1); // 0x1 fixed
    GLB_Wr01(glb_ctrl_00, rv_merg_1_en, 0x1); // 0x1 fixed
    GLB_Wr01(glb_ctrl_00, rv_merg_2_en, 0x1); // 0x1 fixed
    GLB_Wr01(glb_ctrl_00, rv_merg_3_en, 0x1); // 0x1 fixed
    GLB_Wr01(glb_ctrl_00, rv_merg_4_en, 0x1); // 0x1 fixed

    GLB_Wr01(glb_ctrl_00, ga_l0_en, glb_ctrl->mux[OSD_IN_OSC2].galpha_en);
    GLB_Wr01(glb_ctrl_00, pa_l0_en, !glb_ctrl->mux[OSD_IN_OSC2].galpha_en);

    GLB_Wr01(glb_ctrl_00, ga_l1_en, glb_ctrl->mux[OSD_IN_OSC3].galpha_en);
    GLB_Wr01(glb_ctrl_00, pa_l1_en, !glb_ctrl->mux[OSD_IN_OSC3].galpha_en);

    GLB_Wr01(glb_ctrl_00, ga_l2_en, glb_ctrl->mux[OSD_IN_OSD0].galpha_en);
    GLB_Wr01(glb_ctrl_00, pa_l2_en, !glb_ctrl->mux[OSD_IN_OSD0].galpha_en);

    GLB_Wr01(glb_ctrl_00, ga_l3_en, glb_ctrl->mux[OSD_IN_OSD1].galpha_en);
    GLB_Wr01(glb_ctrl_00, pa_l3_en, !glb_ctrl->mux[OSD_IN_OSD1].galpha_en);

    GLB_Wr01(glb_ctrl_00, imux_sel, 0x0); // 0x0 fixed

    GLB_Wr01(glb_ctrl_03, ga_l0, glb_ctrl->mux[OSD_IN_OSC2].galpha);
    GLB_Wr01(glb_ctrl_04, ga_l1, glb_ctrl->mux[OSD_IN_OSC3].galpha);
    GLB_Wr01(glb_ctrl_04, ga_l2, glb_ctrl->mux[OSD_IN_OSD0].galpha);
    GLB_Wr01(glb_ctrl_04, ga_l3, glb_ctrl->mux[OSD_IN_OSD1].galpha);

    GLB_Wr01(glb_ctrl_00, l0_en, glb_ctrl->mux[OSD_IN_OSC2].osd_en);
    GLB_Wr01(glb_ctrl_00, l1_en, glb_ctrl->mux[OSD_IN_OSC3].osd_en);
    GLB_Wr01(glb_ctrl_00, l2_en, glb_ctrl->mux[OSD_IN_OSD0].osd_en);
    GLB_Wr01(glb_ctrl_00, l3_en, glb_ctrl->mux[OSD_IN_OSD1].osd_en);

    FBDEV_HW_NOTI("glb_ctrl.osd_en=%d,%d,%d,%d\n",
                  glb_ctrl->mux[OSD_IN_OSC2].osd_en, glb_ctrl->mux[OSD_IN_OSC3].osd_en,
                  glb_ctrl->mux[OSD_IN_OSD0].osd_en, glb_ctrl->mux[OSD_IN_OSD1].osd_en);

    GLB_Wr01(glb_ctrl_01, cs_type, 0x0); // 444 fixed
    GLB_Wr01(glb_ctrl_01, img_width, glb_ctrl->canvas_w);
    GLB_Wr01(glb_ctrl_01, img_height, glb_ctrl->canvas_h);

    FBDEV_HW_NOTI("glb_ctrl.img_size=%dx%d\n", glb_ctrl->canvas_w, glb_ctrl->canvas_h);

    //GLB_Wr01(glb_ctrl_05, rbuf_width_y, glb_ctrl->canvas_w);
    //GLB_Wr01(glb_ctrl_05, rbuf_width_c, glb_ctrl->canvas_w);

    GLB_WrFL(glb_ctrl_00);
    GLB_WrFL(glb_ctrl_01);
    GLB_WrFL(glb_ctrl_03);
    GLB_WrFL(glb_ctrl_04);
    //GLB_RdFL(glb_ctrl_05);

#ifdef USE_GLBX_REG

    for (i = 0; i < GLB_LAYER_MAX; i++)
    {
        // zroder 값은 GLB 의 출력 좌표값 4개 레지스터중 하나를 선택하게 한다.
        // zroder 에 맞게 coord 값도 미리 잘 설정되어 있어야 한다.
        int zorder = glb_ctrl->mux[i].zorder;
        LX_RECT_T coord = glb_ctrl->mux[i].coord;

        GLBX_RdFL(glb_out_pos[zorder], xpos);
        GLBX_RdFL(glb_out_pos[zorder], ypos);

        GLBX_Wr01(glb_out_pos[zorder], xpos, sp_x, coord.x);
        GLBX_Wr01(glb_out_pos[zorder], xpos, ep_x, coord.x + coord.w - 1);
        GLBX_Wr01(glb_out_pos[zorder], ypos, sp_y, coord.y);
        GLBX_Wr01(glb_out_pos[zorder], ypos, ep_y, coord.y + coord.h - 1);

        GLBX_WrFL(glb_out_pos[zorder], xpos);
        GLBX_WrFL(glb_out_pos[zorder], ypos);

        FBDEV_HW_NOTI("glb in[%d] -> out[%d], pos=(%4d,%4d,%4d,%4d)\n",
                      i, zorder, coord.x, coord.y, coord.w, coord.h);
    }

#else

    if (glb_ctrl->mux[OSD_IN_OSD0].osd_en)
    {
        LX_RECT_T coord = glb_ctrl->mux[OSD_IN_OSD0].coord;

        GLB_RdFL(glb_ctrl_11);
        GLB_RdFL(glb_ctrl_12);

        GLB_Wr01(glb_ctrl_11, l2_sp_x, coord.x);
        GLB_Wr01(glb_ctrl_11, l2_ep_x, coord.x + coord.w - 1);
        GLB_Wr01(glb_ctrl_12, l2_sp_y, coord.y);
        GLB_Wr01(glb_ctrl_12, l2_ep_y, coord.y + coord.h - 1);

        GLB_WrFL(glb_ctrl_11);
        GLB_WrFL(glb_ctrl_12);
    }

    if (glb_ctrl->mux[OSD_IN_OSD1].osd_en)
    {
        LX_RECT_T coord = glb_ctrl->mux[OSD_IN_OSD1].coord;

        GLB_RdFL(glb_ctrl_13);
        GLB_RdFL(glb_ctrl_14);

        GLB_Wr01(glb_ctrl_13, l3_sp_x, coord.x);
        GLB_Wr01(glb_ctrl_13, l3_ep_x, coord.x + coord.w - 1);
        GLB_Wr01(glb_ctrl_14, l3_sp_y,  coord.y);
        GLB_Wr01(glb_ctrl_14, l3_ep_y,  coord.y + coord.h - 1);

        GLB_WrFL(glb_ctrl_13);
        GLB_WrFL(glb_ctrl_14);
    }

    if (glb_ctrl->mux[OSD_IN_OSC2].osd_en)
    {
        LX_RECT_T coord = glb_ctrl->mux[OSD_IN_OSC2].coord;

        GLB_RdFL(glb_ctrl_07);
        GLB_RdFL(glb_ctrl_08);

        GLB_Wr01(glb_ctrl_07, l0_sp_x, coord.x);
        GLB_Wr01(glb_ctrl_07, l0_ep_x, coord.x + coord.w - 1);
        GLB_Wr01(glb_ctrl_08, l0_sp_y, coord.y);
        GLB_Wr01(glb_ctrl_08, l0_ep_y, coord.y + coord.h - 1);

        GLB_WrFL(glb_ctrl_07);
        GLB_WrFL(glb_ctrl_08);
    }

    if (glb_ctrl->mux[OSD_IN_OSC3].osd_en)
    {
        LX_RECT_T coord = glb_ctrl->mux[OSD_IN_OSC3].coord;

        GLB_RdFL(glb_ctrl_09);
        GLB_RdFL(glb_ctrl_10);

        GLB_Wr01(glb_ctrl_09, l1_sp_x, coord.x);
        GLB_Wr01(glb_ctrl_09, l1_ep_x, coord.x + coord.w - 1);
        GLB_Wr01(glb_ctrl_10, l1_sp_y, coord.y);
        GLB_Wr01(glb_ctrl_10, l1_ep_y, coord.y + coord.h - 1);

        GLB_WrFL(glb_ctrl_09);
        GLB_WrFL(glb_ctrl_10);
    }

#endif
}

/*========================================================================================
    Implementation Group (OSD HW Initialization)
========================================================================================*/
int FBDEV_O26_CMN_InitHW(void)
{
    int i;
    UINT32 mixer_mux_value;

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    UINT32 disp_width = hw_ctx->hw_disp_width;
    UINT32 disp_height = hw_ctx->hw_disp_height;

    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK,
                     "-warn- user_initcall not ready +++. ignore HW Init\n");

    FBDEV_NOTI("init/reinit OSD HW. disp_size=%dx%d\n", disp_width, disp_height);

    /* setup top */
    FIXME_NOTE("ctrl_auto_init 의 경우 기존 0x55555555 을 사용하였다. 검증 FW 기준은 0x76472277 인데.. 해석안됨")
    CCO_CTRL_RdFL(ctrl_auto_init);
    CCO_CTRL_RdFL(ctrl_intr_pulse);
    CCO_CTRL_RdFL(pic_init);
    //CCO_CTRL_RdFL(pic_start);
    CCO_CTRL_RdFL(pic_init_g0_timer);
    CCO_CTRL_RdFL(pic_init_g1_timer);
    CCO_CTRL_RdFL(pic_init_g4_timer);

    FIXME_NOTE("검증 FW 는 auto init Idx 를 7 로 설정하고 있음")
    FIXME_NOTE("이게 5이든 7 이든.. 동작에 문제 없는듯?")
#if 0
    CCO_CTRL_Wr(ctrl_auto_init, 0x55555555); //0x76472277); //0x55555555);
#else
    CCO_CTRL_Wr01(ctrl_auto_init, idx_src_g0_auto_init, 0x7);
    CCO_CTRL_Wr01(ctrl_auto_init, idx_src_g1_auto_init, 0x7);
    CCO_CTRL_Wr01(ctrl_auto_init, idx_src_g4_auto_init, 0x7);
#endif

    FIXME_NOTE("지금까지는 그냥 HW 기본값을 사용하였음. 검증 FW 결과값을 참고")
#if 1
    CCO_CTRL_Wr(ctrl_intr_pulse, 0x8A876420);
#else
    CCO_CTRL_Wr01(ctrl_intr_pulse, sel_src_i7_intr_pulse, 0x1);
    CCO_CTRL_Wr01(ctrl_intr_pulse, idx_src_i7_intr_pulse, 0x0); // B.OSD pulse
#endif

    CCO_CTRL_Wr01(pic_init, g0_auto_init, 0x1); // osd in #0
    CCO_CTRL_Wr01(pic_init, g1_auto_init, 0x1); // osd in #1
    CCO_CTRL_Wr01(pic_init, g4_auto_init, 0x1); // csr0

    FIXME_NOTE("pic_init_gx_timer = 0x7500_0000 로 설정 필요")
#if 1
    CCO_CTRL_Wr(pic_init_g0_timer, 0x75000000);
    CCO_CTRL_Wr(pic_init_g1_timer, 0x75000000);
    CCO_CTRL_Wr(pic_init_g4_timer, 0x75000000);
#else
    CCO_CTRL_Wr01(pic_init_g0_timer, start_interval_mode_en, 0x1);
    CCO_CTRL_Wr01(pic_init_g0_timer, start_interval_mode, 0x2);
    CCO_CTRL_Wr01(pic_init_g1_timer, start_interval_mode_en, 0x1);
    CCO_CTRL_Wr01(pic_init_g1_timer, start_interval_mode, 0x2);
    CCO_CTRL_Wr01(pic_init_g4_timer, start_interval_mode_en, 0x1);
    CCO_CTRL_Wr01(pic_init_g4_timer, start_interval_mode, 0x2);
#endif

    FIXME_NOTE("pic_start 는 설정 필요 없음")
    //CCO_CTRL_Wr01(pic_start, g0_pic_start, 0x1);
    //CCO_CTRL_Wr01(pic_start, g1_pic_start, 0x1);
    //CCO_CTRL_Wr01(pic_start, g4_pic_start, 0x1);

    CCO_CTRL_WrFL(ctrl_auto_init);
    CCO_CTRL_WrFL(ctrl_intr_pulse);
    CCO_CTRL_WrFL(pic_init);
    //CCO_CTRL_WrFL(pic_start);
    CCO_CTRL_WrFL(pic_init_g0_timer);
    CCO_CTRL_WrFL(pic_init_g1_timer);
    CCO_CTRL_WrFL(pic_init_g4_timer);

    GSC_CTRL_RdFL(pic_init);
    //GSC_CTRL_RdFL(pic_start);

    GSC_CTRL_Wr01(pic_init, g0_pic_init, 0x1);  // osd path
    GSC_CTRL_Wr01(pic_init, g4_pic_init, 0x1);  // GLB

    //GSC_CTRL_Wr01(pic_start, g0_pic_start, 0x1 );
    //GSC_CTRL_Wr01(pic_start, g4_pic_start, 0x1 );

    GSC_CTRL_WrFL(pic_init);

    /* enable AFBC 2/3 by default */
    GSC_CTRL_RdFL(ctrl_auto_init_afbc1);
    GSC_CTRL_Wr01(ctrl_auto_init_afbc1, reg_afbc2_init_en, 0x1);
    GSC_CTRL_Wr01(ctrl_auto_init_afbc1, reg_afbc2_auto_init_en, 0x1);

    if (hw_ctx->b_support_4kosd)
    {
        GSC_CTRL_Wr01(ctrl_auto_init_afbc1, reg_afbc3_init_en, 0x1);
        GSC_CTRL_Wr01(ctrl_auto_init_afbc1, reg_afbc3_auto_init_en, 0x1);
        GSC_CTRL_WrFL(ctrl_auto_init_afbc1);
    }

    mixer_mux_value = 0x76543210;

    /* initialize B.OSD mixer configuration */
    for (i = 0; i < MAX_BOSD; i++)
    {
        OSDX_RdFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size);
        OSDX_Wr01(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size, reg_bosd_disp_size_w, hw_ctx->bosd_disp.out_width);
        OSDX_Wr01(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size, reg_bosd_disp_size_h, hw_ctx->bosd_disp.out_height);
        OSDX_WrFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_disp_size);

        OSDX_Wr(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_mux1, mixer_mux_value);
        OSDX_WrFL(osdx_blend_osd_mixer[i], ctrl_bosd_mixer_mux1);
    }

    /* setup all OSD common disp size */
    for (i = 0; i < MAX_PLT_OSD_NUM /*8*/; i++)
    {
        OSD_POST_RdFL(osdx_common_disp_size[i]);
        OSD_POST_Wr01(osdx_common_disp_size[i], reg_common_disp_size_w, disp_width);
        OSD_POST_Wr01(osdx_common_disp_size[i], reg_common_disp_size_h, disp_height);
        OSD_POST_WrFL(osdx_common_disp_size[i]);
    }

    //CCO_CTRL_RdFL(ctrl_dpath);
    //CCO_CTRL_Wr(ctrl_dpath, 0x00000000);
    //CCO_CTRL_WrFL(ctrl_dpath);

    FIXME_NOTE("검증 FW 값 참고. 4K sync gen 값인듯. 0x0000_0D80 이 모범 답안")
    CCO_CTRL_RdFL(ctrl_spath);
    CCO_CTRL_Wr(ctrl_spath, 0x00000D80);
    CCO_CTRL_WrFL(ctrl_spath);

    FIXME_NOTE("sync_gen 설정이 필요한가")
    //
    // HW 기본값은 아래와 같으며, 기본값으로도 동작에 문제 없어 보임
    // CC8800A0   00040005 00240438 0058002C 00940780    ....8.$.,.X.....
    // CC8800B0   00040005 00240438 00010058 00040058    ....8.$.X...X...
#if 0
    CCO_CTRL_Wr(osd_sync_gen_ctrl0, 0x0008000A); // OSD_SYNC_GEN_CTRL0
    CCO_CTRL_Wr(osd_sync_gen_ctrl1, 0x00480870); // OSD_SYNC_GEN_CTRL1
    CCO_CTRL_Wr(osd_sync_gen_ctrl2, 0x00B00058); // OSD_SYNC_GEN_CTRL2
    CCO_CTRL_Wr(osd_sync_gen_ctrl3, 0x01280F00); // OSD_SYNC_GEN_CTRL3
    CCO_CTRL_Wr(osd_sync_gen_ctrl4, 0x0008000A); // OSD_SYNC_GEN_CTRL4
    CCO_CTRL_Wr(osd_sync_gen_ctrl5, 0x00480870); // OSD_SYNC_GEN_CTRL5
    CCO_CTRL_Wr(osd_sync_gen_ctrl6, 0x0001006F); // OSD_SYNC_GEN_CTRL6

    CCO_CTRL_WrFL(osd_sync_gen_ctrl0);
    CCO_CTRL_WrFL(osd_sync_gen_ctrl1);
    CCO_CTRL_WrFL(osd_sync_gen_ctrl2);
    CCO_CTRL_WrFL(osd_sync_gen_ctrl3);
    CCO_CTRL_WrFL(osd_sync_gen_ctrl4);
    CCO_CTRL_WrFL(osd_sync_gen_ctrl5);
    CCO_CTRL_WrFL(osd_sync_gen_ctrl6);
#endif

    FIXME_NOTE("검증 FW 값 참고")
    CCO_CTRL_RdFL(ctrl_bosd_pulse);
    CCO_CTRL_Wr01(ctrl_bosd_pulse, reg_disp_pulse_timer, hw_ctx->bosd_disp.pulse_timer_dly);
    CCO_CTRL_Wr01(ctrl_bosd_pulse, reg_disp_pulse_src_sel, 0x1);
    CCO_CTRL_WrFL(ctrl_bosd_pulse);

    FIXME_NOTE("검증 FW 값 참고. bit 24 는 0 이어야 함.")
    // enable cursor MIF
    // REG_WRF1(CCO_MIF0, r_csr0_mb_req, req_msk_f_on, 0);
    OS_WrReg(0xCC880C60, 0x000000FB);

    FBDEV_NOTI("initial support_4k_osd=%d, ext_frc=%d, 4k_disp=%d\n",
               hw_ctx->b_support_4kosd, hw_ctx->b_support_ext_frc, FBDEV_O26_CMN_IsUHDDispMode());

    FBDEV_O26_CMN_InitMirrorEnv();
    FBDEV_O26_CMN_InitFBCEnv();

    return RET_OK;
}

// OSD_PRE 에 해당하는 설정을 초기화한다.
// 기존 칩과 많이 틀리다.
// FBDEV_O26_CMN_InitOSDPost() 도 같이 참고해야 한다.
int FBDEV_O26_CMN_InitOSDLayer(int fb_dev_id)
{
    int i;
    int xidx;
    int xnum, xlst[2];
    int ret = RET_ERROR;

    phys_addr_t surf_base = 0;
    int         surf_size = 0;

    /* please refer to OSD manual OSD<x>_CFG field */
    UINT32  hdr_src_sel = 1;    /* HDR_OP_REG by default */
    bool osd_en = 0x0;          /* off by default */
    bool hdr_rdy_flag = 0x1;    /* On by fixed */

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_MIRROR_CTRL_T* mirror_ctrl = FBDEV_PLT_GET_MIRROR_CTRL(hw_ctx);

    UINT32 vmirror_en = (mirror_ctrl->status & FBDEV_O26_V_MIRROR_ON) ? 0x1 : 0x0;

    xnum = FBDEV_O26_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_NOTI("fb(%d) configure osd layer\n", fb_dev_id);

    /* if user_initcall not ready, DO NOT write any OSD reigisters (keep the current configuration)  */
    if (!hw_ctx->user_initcall_ctrl.ready)
    {
        FBDEV_NOTI("<i> fb(%d) user_initcall not ready +++. ignore layer init\n", fb_dev_id);
        return RET_OK;
    }

    hma_pool_info(SURFACE_MEM_POOL, &surf_base, &surf_size);

    /* choose the initial osd visibility based on boot logo configuration */
    switch (fb_dev_id)
    {
        case LX_FBDEV_ID_OSD0:  osd_en = 0x1; break;

        default:                osd_en = 0x0; break;
    }

    for (i = 0; i < xnum; i++)
    {
        OSDX_DESC_T osdx_desc;

        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), goto func_exit, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

        // osd_ctrl_main, pdec, swap 등을 읽는다.
        // sync0, sync1, 및 scaler 설정은 FBDEV_O26_CMN_InitOSDPost() 으로 이동하였다.
        FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_ALL);

        // mem prot error 방지용
        osdx_desc.osd_base_addr.base_addr = (UINT32)surf_base;
        osdx_desc.osd_ctrl_hdr5.osd_hdr_ptr_plte = (UINT32)surf_base;

        osdx_desc.osd_ctrl_main.osd_hdr_ready_flag_en = hdr_rdy_flag;
        osdx_desc.osd_ctrl_main.osd_hdr_src_sel = hdr_src_sel;
        osdx_desc.osd_ctrl_main.osd_v_reverse_en = vmirror_en;
        osdx_desc.osd_ctrl_main.osd_manual_dlr = 0x2;

        // pdec=0xe4000000, swap=0x000 equals pdec=0x1b000000, swap=0x333
        // osd_ctrl_pdec = 0x1B00_0000. ARGB by default
        osdx_desc.osd_ctrl_pdec.osd_ch_alpha = 0x0;
        osdx_desc.osd_ctrl_pdec.osd_ch_red = 0x1;
        osdx_desc.osd_ctrl_pdec.osd_ch_green = 0x2;
        osdx_desc.osd_ctrl_pdec.osd_ch_blue = 0x3;
        osdx_desc.osd_ctrl_pdec.osd_round = 0x0;
        osdx_desc.osd_ctrl_pdec.osd_pure_ck = 0x0;
        osdx_desc.osd_ctrl_pdec.osd_lfsr_seed = 0x0;

        // osd_ctrl_swap = 0x0000_0333
        osdx_desc.osd_ctrl_swap.osd_hbs = 0x1;
        osdx_desc.osd_ctrl_swap.osd_hqws = 0x1;
        osdx_desc.osd_ctrl_swap.osd_hhws = 0x0;
        osdx_desc.osd_ctrl_swap.osd_pbs = 0x1;
        osdx_desc.osd_ctrl_swap.osd_pqws = 0x1;
        osdx_desc.osd_ctrl_swap.osd_phws = 0x0;
        osdx_desc.osd_ctrl_swap.osd_bbs = 0x1;
        osdx_desc.osd_ctrl_swap.osd_bqws = 0x1;
        osdx_desc.osd_ctrl_swap.osd_bhws = 0x0;

        FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_ADDR | OSDX_DESC_FLAG_HDR_5);
        FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_CTRL_MAIN | OSDX_DESC_FLAG_SWAP | OSDX_DESC_FLAG_PDEC);

        // TODO: add more initialization if necessary

        FIXME_NOTE("기존 설정중 일부는 OSDPost 쪽으로 이동함")
    }

    ret = RET_OK;   /* all work done */
func_exit:
    return ret;
}

// OSD POST 를 설정한다.
// OSD0/1 에 대한 GLB 설정 포함하여 sync, scaler 설정을 해야 한다.
// cursor 에 대한 sync 설정등을 해야 한다.
static void FBDEV_O26_CMN_InitOSDPost(void)
{
    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_MIRROR_CTRL_T* mirror_ctrl = FBDEV_PLT_GET_MIRROR_CTRL(hw_ctx);

    UINT32 fb_width = hw_ctx->hw_fb0_width;
    UINT32 fb_height = hw_ctx->hw_fb0_height;
    UINT32 disp_width = hw_ctx->hw_disp_width;
    UINT32 disp_height = hw_ctx->hw_disp_height;

    UINT32 vmirror_en = (mirror_ctrl->status & FBDEV_O26_V_MIRROR_ON) ? 0x1 : 0x0;
    UINT32 buf_mode_en = (FBDEV_O26_CMN_IsUHDDispMode()) ? 0x0 : 0x1;

    // OSD_PRE 의 출력 설정
    // 4K OSD 지원시 osd in 0/1 이 각각 L/R 을 담당하도록 disp size 설정을 한다.
    // 2K OSD 지원시 POST 의 disp_size 와 동일하게 설정한다.
    OSD_PRE_RdFL(osd0_common_disp_size);
    OSD_PRE_RdFL(osd1_common_disp_size);

    OSD_PRE_Wr01(osd0_common_disp_size, reg_common_disp_size_h, disp_height);
    OSD_PRE_Wr01(osd1_common_disp_size, reg_common_disp_size_h, disp_height);

    if (hw_ctx->b_support_4kosd)
    {
        OSD_PRE_Wr01(osd0_common_disp_size, reg_common_disp_size_w, disp_width / 2);
        OSD_PRE_Wr01(osd1_common_disp_size, reg_common_disp_size_w, disp_width / 2);
    }
    else
    {
        OSD_PRE_Wr01(osd0_common_disp_size, reg_common_disp_size_w, disp_width);
        OSD_PRE_Wr01(osd1_common_disp_size, reg_common_disp_size_w, disp_width);
    }

    OSD_PRE_WrFL(osd0_common_disp_size);
    OSD_PRE_WrFL(osd1_common_disp_size);

    // OSD0 출력 패스에 대한 설정
    OSD_POST_RdFL(osd0_ctrl_scaler);
    OSD_POST_RdFL(osd0_ctrl_path);
    OSD_POST_RdFL(osd0_ctrl_sync0);
    OSD_POST_RdFL(osd0_ctrl_sync1);
    OSD_POST_RdFL(osd0_bitmap_ctrl0);
    OSD_POST_RdFL(osd0_vsp_bosd_ctrl0);
    OSD_POST_RdFL(osd0_vsp_bosd_ctrl1);

    OSD_POST_Wr01(osd0_ctrl_scaler, reg_osd_buf_mode_en_n, buf_mode_en);

    OSD_POST_Wr01(osd0_ctrl_path, osd_ctrl_direc, 0x0);  // B.OSD fixed
    OSD_POST_Wr01(osd0_ctrl_path, osd_ctrl_eo2s, 0x0);   // B.OSD fixed
    OSD_POST_Wr01(osd0_ctrl_path, osd_ctrl_bosd_pos, 0x0); // BOSD1 fixed
    OSD_POST_Wr01(osd0_ctrl_path, reg_ctrl_path_width, disp_width); // disp_height

    OSD_POST_Wr01(osd0_ctrl_sync0, osd_sync_v_reverse, vmirror_en);
    OSD_POST_Wr01(osd0_ctrl_sync1, osd_sync_disp_w, disp_width / 2); // disp_width/2
    OSD_POST_Wr01(osd0_ctrl_sync1, osd_sync_disp_h, disp_height); // disp_height

    FIXME_NOTE("OSD SR 끄는 설정인가?")
    OSD_POST_Wr01(osd0_bitmap_ctrl0, reg_osd_shp_detour_en, 0x1); // 0xD040_0001
    OSD_POST_Wr01(osd0_bitmap_ctrl0, reg_pcc_detour_en, 0x1);

    OSD_POST_Wr01(osd0_vsp_bosd_ctrl0, r_contrast, 0x200);  // HW default
    OSD_POST_Wr01(osd0_vsp_bosd_ctrl1, r_offset, 0x200); // HW default
    OSD_POST_Wr01(osd0_vsp_bosd_ctrl1, r_saturation, 0x80);  // HW default

    OSD_POST_WrFL(osd0_ctrl_scaler);
    OSD_POST_WrFL(osd0_ctrl_path);
    OSD_POST_WrFL(osd0_ctrl_sync0);
    OSD_POST_WrFL(osd0_ctrl_sync1);
    OSD_POST_WrFL(osd0_bitmap_ctrl0);
    OSD_POST_WrFL(osd0_vsp_bosd_ctrl0);
    OSD_POST_WrFL(osd0_vsp_bosd_ctrl1);

    // see the below cmm if necessary
    // wr cc880480 08088000 # REG_OSD0_ORD_CTRL00
    // wr cc880768 00000000 # REG_PCC_CTRL00
    // wr cc88079C 0f0000d8 # REG_OSD_HDRUI_SIZE
    // wr cc8807A0 00001000 # REG_OSD_HDRUI_DITHER_CTRL0
    // wr cc8807A8 00000000 # REG_OSD_HDRUI_DITHER_CTRL2

    // OSD 패스 출력에 대한 초기화 설정 설정 (OSD to 4K scaler)
    // PQE orbit 제어 되는 부분이므로, 초기화 및 EST 변경시에만 제어를 해야 한다.
    OSD_POST_RdFL(osd0_ctrl_main);
    //OSD_POST_RdFL(osd0_ctrl_hdr0);
    //OSD_POST_RdFL(osd0_ctrl_hdr1);
    //OSD_POST_RdFL(osd0_ctrl_hdr2);

    OSD_POST_Wr01(osd0_ctrl_hdr0, osd_hdr_xpos, 0);
    OSD_POST_Wr01(osd0_ctrl_hdr0, osd_hdr_ypos, 0);
    OSD_POST_Wr01(osd0_ctrl_hdr1, osd_hdr_w_mem, fb_width);
    OSD_POST_Wr01(osd0_ctrl_hdr1, osd_hdr_h_mem, fb_height);
    OSD_POST_Wr01(osd0_ctrl_hdr2, osd_hdr_w_out, disp_width);
    OSD_POST_Wr01(osd0_ctrl_hdr2, osd_hdr_h_out, disp_height);

    OSD_POST_Wr01(osd0_ctrl_main, osd_hdr_ready_flag_en, 0x1);
    OSD_POST_Wr01(osd0_ctrl_main, osd_hdr_ready_flag, 0x1);
    OSD_POST_WrFL(osd0_ctrl_hdr0);
    OSD_POST_WrFL(osd0_ctrl_hdr1);
    OSD_POST_WrFL(osd0_ctrl_hdr2);
    OSD_POST_WrFL(osd0_ctrl_main);

    // CSR0 (출력) 패스에 대한 설정
    OSD_POST_RdFL(csr0_ctrl_sync0);
    //OSD_POST_RdFL(csr0_ctrl_scaler);
    OSD_POST_RdFL(csr0_ctrl_path);
    OSD_POST_RdFL(csr0_ctrl_sync1);
    //OSD_POST_Wr01(csr0_ctrl_scaler, reg_osd_buf_mode_en_n, buf_mode_en);

    OSD_POST_Wr01(csr0_ctrl_path, osd_ctrl_direc, 0x0);  // B.OSD fixed
    OSD_POST_Wr01(csr0_ctrl_path, osd_ctrl_4to1, 0x0);   // B.OSD fixed
    OSD_POST_Wr01(csr0_ctrl_path, osd_ctrl_bosd_pos, 0x0); // BOSD1 fixed
    OSD_POST_Wr01(csr0_ctrl_path, reg_ctrl_path_width, disp_width); // disp_height

    OSD_POST_Wr01(csr0_ctrl_sync0, osd_sync_v_reverse, vmirror_en);
    OSD_POST_Wr01(csr0_ctrl_sync1, osd_sync_disp_w, disp_width / 2); // disp_width/2
    OSD_POST_Wr01(csr0_ctrl_sync1, osd_sync_disp_h, disp_height); // disp_height

    OSD_POST_WrFL(csr0_ctrl_sync0);
    //OSD_POST_WrFL(csr0_ctrl_scaler);
    OSD_POST_WrFL(csr0_ctrl_path);
    OSD_POST_WrFL(csr0_ctrl_sync1);
}

static void FBDEV_O26_CMN_ReInitHW(void)
{
    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return, "<i> user_initcall not ready +++\n");

    FBDEV_O26_InitHW();
    FBDEV_SetInterruptEnable(MIXER_INTR, 1);

    // O26 OSD supports only OSD0, OSD1 & OSD3
    FBDEV_O26_CMN_InitOSDLayer(LX_FBDEV_ID_OSD0);
    FBDEV_O26_CMN_InitOSDLayer(LX_FBDEV_ID_OSD1);
    FBDEV_O26_CMN_InitOSDLayer(LX_FBDEV_ID_OSD3);

    FBDEV_O26_CMN_InitOSDPost();
    FBDEV_O26_CMN_InitGLBEnv();

    FIXME_NOTE("pic init 부분은 FBDEV_O26_InitHW() 로 옮김")
#if 0

    // refer to SICDTV-4209 if you have troube to enable OSD during I-BOOT
    if (hw_ctx->hw_wa_flag & FBDEV_O26_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR)
    {
        FBDEV_O26_CMN_SafeSyncEnable();
    }

#endif
}

// AR 모드에서 PQE PM 에 의해 다시 OSD 가 활성화 될때 호출된다.
static void FBDEV_O26_CMN_ResumeOSDPath(void)
{
    // PQE_PM_DEVICE_SUSPEND_PREPARE 에서 shutdown 된 OSD_POST 의 sync on 을 보장한다.
    OSD_POST_RdFL(osd0_ctrl_sync0);
    OSD_POST_Wr01(osd0_ctrl_sync0, osd_sync_enable, 0x1);
    OSD_POST_WrFL(osd0_ctrl_sync0);

    FBDEV_O26_CMN_SetInterruptEnable(MIXER_INTR, true);
}

// QSM+ 혹은 runtim_pm 에 의한 suspend 진입시 OSD 의 DDR access 가 없도록 보장한다.
// - OSD hide 를 통해 buffer read 동작이 없도록 한다.
// - osd sync off 를 통해 OSD path 상의 데이터 흐름이 없도록 한다.
//
static void FBDEV_O26_CMN_ShutdownOSDPath(void)
{
    int i;

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        if (g_fbdev_cfg->fb[i].b_active)
        {
            FBDEV_NOTI("shutdown fb(%d)\n", i);
            FBDEV_O26_CMN_SetOSDEnable(i, false);
        }
    }

    // OSD_POST 와 커서 sync off 를 보장한다.
    OSD_POST_RdFL(osd0_ctrl_sync0);
    OSD_POST_Wr01(osd0_ctrl_sync0, osd_sync_enable, 0x0);
    OSD_POST_WrFL(osd0_ctrl_sync0);

    OSD_POST_RdFL(csr0_ctrl_sync0);
    OSD_POST_Wr01(csr0_ctrl_sync0, osd_sync_enable, 0x0);
    OSD_POST_WrFL(csr0_ctrl_sync0);

    FBDEV_NOTI("completed\n");
}

int FBDEV_O26_CMN_ExecHWCommand(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data)
{
    int ret = RET_NOT_SUPPORTED;
    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

    switch (cmd)
    {
        case FBDEV_HW_CMD_IO_POST_HW_INIT:
        {
            fbdev_o26_wq = alloc_workqueue("fbdev_o26_events", 0, 0);

            if (osd_enable_logo_clear)
            {
                FBDEV_NOTI("start logo clear work after %dms\n", osd_boot_logo_clear_timeout);
                queue_delayed_work(fbdev_o26_wq, &boot_logo_clear_work, msecs_to_jiffies(osd_boot_logo_clear_timeout));
            }

#ifdef BUILD_FEATURE_pioneer
            FBDEV_O26_CMN_SetMixerMute(FALSE, 0x000000);
            FBDEV_O26_CMN_SetMute(false);
#endif
        }
        break;

        case FBDEV_HW_CMD_IO_POSD_OPEN:
        {
            int fbdev_id = data->gen[0];
            struct fb_info* fbinfo = (struct fb_info*)data->genex[0];

            FBDEV_HW_DEBUG("fb(%d) POSD_OPEN..\n", fbdev_id);
            FBDEV_O26_CMN_RunBootLogoTimer(osd_boot_freeze_timeout, false);

            FBDEV_O26_CMN_SetupExternalRenderer(fbdev_id, fbinfo);

            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_IO_USER_POSD_RESOL_CHANGED:
        {
            // int fbdev_id = data->gen[0];
            // add code if necesssary
            FBDEV_NOTI("FBDEV_HW_CMD_IO_USER_POSD_RESOL_CHANGED not supported\n");
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_IO_VSYNC:
        {
            FBDEV_O26_CMN_ISRHook();
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_RD_VSYNC_CLK:
        {
            /* raxis.lim (2019/11/21)
             *
             * I should check if S.OSD is active becuase S.OSD is set to fixed 60Hz display
             * regardless of OVI check value.
             * remember that I can call FBDEV_O26_CMN_DetectVSyncClk() only when B.OSD is active.
             */
            if (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND)
            {
                data->gen[0] = FBDEV_O26_CMN_DetectVSyncClk();
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

            if (fbdev_id == LX_FBDEV_ID_OSD0)
            {
                data->gen[0] = LX_MAKE_RES(hw_ctx->hw_fb0_width, hw_ctx->hw_fb0_height);
                data->gen[1] = 2; /*afbc*/
                data->gen[2] = 0; /*system default*/
            }
            else if (fbdev_id == LX_FBDEV_ID_OSD1)
            {
                data->gen[0] = LX_MAKE_RES(hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height);
                data->gen[1] = (fbdev_afbc_estreamer) ? 2/*afbc*/ : 1 /*argb*/;
                data->gen[2] = (hw_ctx->b_support_ext_render) ? 1 : 2; /* single buffer when ext_render_mode */
            }
            else
            {
                data->gen[0] = 0x0;
                data->gen[1] = 0x0;
                data->gen[2] = 0x0;
            }

            if (data->gen[0] != 0x0) ret = RET_OK;

            //printk("fb(%d) ret=%d, 0x%x, 0x%0x, 0x%0x, 0x%0x\n", fbdev_id, ret, data->gen[0], data->gen[1], data->gen[2], data->gen[3]);
        }
        break;

        case FBDEV_HW_CMD_RD_AFBC_CAPS:
        {
            data->gen[0] = osd_fbc_version;
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_FREEZE:
        {
            /* raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL. ORBIT control will be re-enabled at THAW & RESTORE */
            hw_ctx->hw_wa_flag &= ~FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL;
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_SUSPEND:
        {
            osd_hw_pm_suspend_stage = 1;

            if (osd_use_shutdown_path_on_suspend)
            {
                FBDEV_O26_CMN_ShutdownOSDPath();
            }

            // raxis.lim (2017/09/18) -- disable PQEFW_OSD0_OUT_CTRL to re-enable at FBDEV_O26_CMN_EnableOSDHdrFlush() during RESUME
            hw_ctx->hw_wa_flag &= ~FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL;
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_THAW:
        {
            // raxis.lim (2017/09/18) -- enable PQEFW_OSD0_OUT_CTRL here becuase THAW stage doesn't configure any HW registers
            hw_ctx->hw_wa_flag |= FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL;
            FBDEV_NOTI("OSD0_PQEFW_OSD0_OUT_CTRL enabled\n");
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_RESTORE:
        {
            osd_hw_pm_restore_stage = 1;

            // boot logo migration is also required during snapshot boot
            osd_logo_migration_required = true;
            FBDEV_O26_CMN_MigrateBootLogo(BOOT_LOGO_MODE_IMAGE_KEEP);

            if (osd_enable_logo_clear)
            {
                FBDEV_NOTI("start logo clear work after %dms (resume mode)\n", osd_resume_logo_clear_timeout);
                queue_delayed_work(fbdev_o26_wq, &boot_logo_clear_work, msecs_to_jiffies(osd_resume_logo_clear_timeout));
            }

            // (2010/06/11) re-activate lazy-init at snapshot boot
            hw_ctx->user_initcall_ctrl.ready = false;
            hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

            // (2024/05/13) see https://alm-lge.singlex.com/polarion/#/project/IDWebOSSWRelProjMgmt/workitem?id=IDWOSWBS-11241
            FBDEV_NOTI("osd.restore - invalidate mirror ctrl\n");
            hw_ctx->mirror_ctrl.status = FBDEV_O26_MIRROR_NONE;

            // (2023/09/8) fast interrupt enable to prevent drm vsync timeout
            FBDEV_NOTI("osd.restore - fast enable OSD vsync\n");
            FBDEV_SetInterruptEnable(MIXER_INTR, 1);

            // raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute
            // it will be enabled at FBDEV_O26_CMN_EnableOSDHdrFlush()

            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_PREPARE_RESUME:
        {
#if 0
            // raxis.lim (2017/08/22) -- fix for async behavior of OSD0_SYNC group
            hw_ctx->hw_wa_flag |= FBDEV_O26_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
            FBDEV_WARN("OSD0_SYNC_ASYNC_WR enabled\n");
#endif

            // (2010/06/11) re-activate lazy-init at QSM+ resume
            hw_ctx->user_initcall_ctrl.ready = false;
            hw_ctx->user_initcall_ctrl.status.data32 = 0x0;

            // raxis.lim (2017/09/18) -- DO NOT set any PQEFW_OSD0_OUT_CTRL attribute.
            // it will be enabled at FBDEV_O26_CMN_EnableOSDHdrFlush()
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_PM_COMPLETE:
        {
            osd_hw_pm_suspend_stage = 0;
            osd_hw_pm_restore_stage = 0;

#if 0
            hw_ctx->hw_wa_flag &= ~FBDEV_O26_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR;
#endif
            ret = RET_OK;
        }
        break;

        case FBDEV_HW_CMD_WR_USER_INITCALL_PREPARE:
        {
            int  fbdev_id = data->gen[0];

            FBDEV_NOTI("fb(%d) INITCALL_PREPARE\n", fbdev_id);

            // raxis.lim (2010/06/11)
            // (re)initialize OSD HW at user frame update not at kdriver initialization !!
            //
            // (2023/01/19) DRM cursor 단독 테스트에서도 OSD 초기화 진행이 되어야 함
            // 따라서 OSD0 체커 삭제하고, 초기화 중복 여부 코드만 살림
            // see http://clm.lge.com/issue/browse/SCDCR-5652
            // if (fbdev_id == LX_FBDEV_ID_OSD0 && !hw_ctx->user_initcall_ctrl.ready)
            //
            // (2023/05/19) OSD open 이란 동작이 없어도, 이미지 업데이트가 가능하다.
            // 따라서 FBDEV_O26_CMN_RunBootLogoTimer() 함수를 호출하여 osd_hdr_update 플래그를
            // 정상화할 수 있도록 보강이 필요하다.
            //
            if (!hw_ctx->user_initcall_ctrl.ready)
            {
                hw_ctx->user_initcall_ctrl.ready = true;

                FBDEV_O26_CMN_RunBootLogoTimer(osd_boot_freeze_timeout, false);

                FBDEV_O26_CMN_ReInitHW();
            }
        }
        break;

        // USER_INITCALL_COMPLETE 는 모든 OSD 설정의 완료를 의미하므로, 반드시 PQE FW 쪽으로 제어권을 넘겨야 한다.
        // 즉 FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL 플래그 설정이 가장 중요
        case FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE:
        {
            int i;
            int fbdev_id = data->gen[0];

            FBDEV_NOTI("fb(%d) INITCALL_COMPLETE\n", fbdev_id);

            // (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume
            if (fbdev_id == LX_FBDEV_ID_OSD0)
            {
                UINT64 base_tick;
                FBDEV_PLT_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

                // disable OSD reigster control by PQE_FW when S.OSD path is selected or FHD model
                if (hw_ctx->b_support_ext_frc || hw_ctx->hw_disp_width <= 2048)
                {
                    osd_pqefw_osd0_out_ctrl = 0;
                    hw_ctx->hw_wa_flag &= ~FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL;
                    FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL disabled\n");
                }
                else
                {
                    hw_ctx->hw_wa_flag |= FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL;
                    FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
                }

                hw_ctx->user_initcall_ctrl.status.osd_init_done = 1;
                hw_ctx->user_initcall_ctrl.status.osd_v_mirror = (mirror_ctrl->status == FBDEV_O26_V_MIRROR_ON) ? 1 : 0;
                hw_ctx->user_initcall_ctrl.status.osd_estreamer = 0;

                FBDEV_O26_CMN_NotifyPQEDriver();

                base_tick = OS_GetMsecTicks();

                for (i = 0; i < 10; i++)
                {
                    // if (FW done) break;
                    FBDEV_CHECK_NOTI((int)(OS_GetMsecTicks() - base_tick) > 100 /*100ms*/,
                                     break, "+ wait timeout\n");

                    if (RET_OK == FBDEV_O26_CMN_CheckPQEDriverInitialization()) break;

                    msleep_interruptible(10);
                }

                FBDEV_O26_CMN_SetOSDEnable(fbdev_id, true);

                // destroy temporary boot logo framebuffer
                FBDEV_O26_CMN_FreeBootLogoFrameBuffer();

                // disable osd mixer mute
                FBDEV_O26_CMN_SetMixerMute(FALSE, 0x000000);
            }
        }
        break;

        case FBDEV_HW_CMD_RD_EXTERNAL_RENDERER_INFO:
        {
            data->gen[0] = LX_FBDEV_ID_OSD1;
        }
        break;

        case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_CONFIGURE_CROP_REGION:
        {
            int max_cw;
            int max_ch;

            int  fbdev_id = data->gen[0];
            int cx = LX_RES_GET_WIDTH(data->gen[1]);
            int cy = LX_RES_GET_HEIGHT(data->gen[1]);
            int cw = LX_RES_GET_WIDTH(data->gen[2]);
            int ch = LX_RES_GET_HEIGHT(data->gen[2]);

            FBDEV_PLT_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_PLT_GET_EXT_RENDER_CTRL(hw_ctx);

            FBDEV_CHECK_CODE(fbdev_id != LX_FBDEV_ID_OSD1, break, "++ fb(%d) invalid ext_render fbdev\n", fbdev_id);

            if (hw_ctx->b_support_ext_render)
            {
                max_cw = hw_ctx->hw_ext_render_width / 2; /* 960 */
                max_ch = hw_ctx->hw_ext_render_height * 2; /* 4320 */
            }
            else
            {
                max_cw = hw_ctx->hw_fb1_width;
                max_ch = hw_ctx->hw_fb1_height;
            }

            if (cw > max_cw) cw = max_cw;

            if (ch > max_ch) ch = max_ch;

            ext_render_ctrl->hwparam.crop_x = cx;
            ext_render_ctrl->hwparam.crop_y = cy;
            ext_render_ctrl->hwparam.crop_w = cw;
            ext_render_ctrl->hwparam.crop_h = ch;

            FBDEV_NOTI("++ configure external render crop %d,%d,%d,%d\n", cx, cy, cw, ch);
        }
        break;

        // (2021/07/08) O268K, E608K 의 경우는 fbdev_drv.c 에서 호출이 되었으나, O26 8K 의 경우는
        // 일반 OSD 처럼 입력되어 처리되어야 하므로, fbdev_drv.c 에서 호출되지 않는다.
        // SW 구조를 유지하기 위하여 fbdev_hw_o26_cmn.c 에서 호출하도록 조치한다.
        // 수정된 IPC 에서는 crop_x,y,w,h 정보와 xoffset, enable 정보만 전달된다.
        case FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE:
        {
            int    fbdev_id = data->gen[0];
            UINT32 phys_y   = data->gen[1];
            int    xoffset  = data->gen[2];
            int    yoffset  = data->gen[3];

            FBDEV_PLT_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_PLT_GET_EXT_RENDER_CTRL(hw_ctx);

            FBDEV_CHECK_CODE(fbdev_id != LX_FBDEV_ID_OSD1, break, "++ fb(%d) invalid ext_render fbdev\n", fbdev_id);

            ext_render_ctrl->hwparam.phys_y = phys_y;
            ext_render_ctrl->hwparam.size = ((hw_ctx->hw_ext_render_width / 2) << 16) | (hw_ctx->hw_ext_render_height * 2);
            ext_render_ctrl->hwparam.xoffset = xoffset;
            ext_render_ctrl->hwparam.yoffset = yoffset;

            // fake vsync 는 현재 체제 그대로 사용한다.
            {
                UINT64 sleep_tick_us = 0;
                UINT64 curr_tick_us = OS_GetUsecTicks();
                UINT64 diff_tick_us = curr_tick_us - ext_render_ctrl->swsync.request_tick_us;

                if (diff_tick_us < ext_render_ctrl->swsync.interval_tick_us)
                {
                    sleep_tick_us = ext_render_ctrl->swsync.interval_tick_us - diff_tick_us;
                    //FBDEV_NOTI("++ usleep %d us\n", (int)sleep_tick_us);
                    usleep_range(sleep_tick_us, sleep_tick_us);
                }

                FBDEV_HW_NOTI("++ write external render phy:s0x%08x cmd:0x%08x crop:%d,%d,%d,%d xy:%d,%d en:%d - sleep: %dus tx_count: %d\n",
                              ext_render_ctrl->hwparam.phys_y,
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

#ifdef FBDEV_O26_USE_EXT_RENDERER_IPC

            if (hw_ctx->b_support_ext_render)
            {
                if (FBDEV_OSD_EXT_RENDER_REG_BASE)
                {
                    FBDEV_HW_NOTI("++ write external render 0x%08x=0x%08x, 0x%08x=0x%08x, 0x%08x=0x%08x\n",
                                  FBDEV_OSD_EXT_RENDER_REG_BASE + 0x0, ext_render_ctrl->hwparam.command,
                                  FBDEV_OSD_EXT_RENDER_REG_BASE + 0x4, ext_render_ctrl->hwparam.crop_xy,
                                  FBDEV_OSD_EXT_RENDER_REG_BASE + 0x8, ext_render_ctrl->hwparam.crop_wh);

                    OS_WrReg(FBDEV_OSD_EXT_RENDER_REG_BASE + 0x4, ext_render_ctrl->hwparam.crop_xy);
                    OS_WrReg(FBDEV_OSD_EXT_RENDER_REG_BASE + 0x8, ext_render_ctrl->hwparam.crop_wh);
                    OS_WrReg(FBDEV_OSD_EXT_RENDER_REG_BASE + 0x0, ext_render_ctrl->hwparam.command);
                }
            }

#endif
            else
            {
                LX_RECT_T crop_rgn;

                crop_rgn.x = ext_render_ctrl->hwparam.crop_x;
                crop_rgn.y = ext_render_ctrl->hwparam.crop_y;
                crop_rgn.w = ext_render_ctrl->hwparam.crop_w;
                crop_rgn.h = ext_render_ctrl->hwparam.crop_h;

                // 여러 프로세스가 혼재되어 동작하게 되므로, osd0 의 소유권을 반드시 확인할것
                FBDEV_CHECK_CODE(hw_ctx->hw_osd0_owner != fbdev_id, break,
                                 "++ fb(%d) ignore. not hw_osd0_owner\n", fbdev_id);

                FBDEV_O26_CMN_SetOutputCropRegion(true, hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height, xoffset, yoffset, &crop_rgn);
            }

            ext_render_ctrl->swsync.request_tick_us = OS_GetUsecTicks();
        }
        break;

        // PQE PM framework callback
        case FBDEV_HW_CMD_WR_PQE_PM_RUNTIME_ACTION:
        {
#ifdef INCLUDE_KDRV_PQE_PM
            int pqe_pm_action = data->gen[0];

            if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_PREPARE)
            {
                // (2023/11/06) suspend 에 준하는 동작 필요 (불필요한 PQE IPC 무시 등)
                // see FBDEV_O26_CMN_WaitPQEDriverEstreamerSync()
                osd_hw_pm_suspend_stage = 1;

                FBDEV_PM_DEBUG("hide all OSD layer for safe operation\n");
                FBDEV_O26_CMN_ShutdownOSDPath();

                FBDEV_O26_CMN_SetInterruptEnable(MIXER_INTR, false);

                // PQE 에서 1/64 freq down 정책으로 사용하기 때문에, pic_init 에 대한 제어를 하지 않아도 됨
                // 추후 필요하다 판단시 아래 코드를 사용할것
                // 참고 http://clm.lge.com/issue/browse/SICDTV-10087?focusedCommentId=3185554&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3185554
                // 필요시 이전 패치셋을 확인할것

                // TODO: 필요시 추가할것

            }
            else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND)
            {
                // TODO: 필요시 추가할것

                // (2023/11/06) PQE FW 가 suspend 되었으므로, PQE 와의 IPC 동작을 할 수 없음을 표시한다.
                // see FBDEV_O26_CMN_WaitPQEDriverEstreamerSync()
                osd_pqefw_ipc_enabled = false;
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_COMPLETED)
            {
                // TODO: 필요시 추가할것
                osd_hw_pm_suspend_stage = 0;
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_PREPARE)
            {
                // TODO: 필요시 추가할것
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_RESUME)
            {
                // PQE 에서 1/64 freq down 정책으로 사용하기 때문에, pic_init 에 대한 제어를 하지 않아도 됨
                // 추후 필요하다 판단시 아래 코드를 사용할것
                // 참고 http://clm.lge.com/issue/browse/SICDTV-10087?focusedCommentId=3185554&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3185554
                // 필요시 이전 패치셋을 확인할것

                // TODO: 필요시 추가할것
            }
            else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_COMPLETED)
            {
                // TODO: 필요시 추가할것

                // (2023/11/06) PQE FW 가 resume 되었으므로, PQE 와의 IPC 동작을 할 수 있다.
                osd_pqefw_ipc_enabled = true;

                FBDEV_O26_CMN_ResumeOSDPath();
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

// HW 상태를 질의한다. 실제 레지스터를 읽어야 한다.
//
int      FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_T status, UINT32 opt)
{
    int val = 0;

    switch (status)
    {
        // AFBC 설정 상태인지 확인한다.
        case FBDEV_O26_HW_STATUS_AFBC:
        {
            int afrc_en = 0;

            GSC_CTRL_RdFL(ctrl_block1);

            if (opt == LX_FBDEV_ID_OSD0)
            {
                GSC_CTRL_Rd01(ctrl_block1, reg_afbc_afrc_2_sel, afrc_en);
            }
            else if (opt == LX_FBDEV_ID_OSD1)
            {
                GSC_CTRL_Rd01(ctrl_block1, reg_afbc_afrc_3_sel, afrc_en);
            }

            val = (afrc_en) ? 0 : 1;
        }
        break;

        // AFRC 설정 상태인지 확인한다.
        case FBDEV_O26_HW_STATUS_AFRC:
        {
            int afrc_en = 0;

            GSC_CTRL_RdFL(ctrl_block1);

            if (opt == LX_FBDEV_ID_OSD0)
            {
                GSC_CTRL_Rd01(ctrl_block1, reg_afbc_afrc_2_sel, afrc_en);
            }
            else if (opt == LX_FBDEV_ID_OSD1)
            {
                GSC_CTRL_Rd01(ctrl_block1, reg_afbc_afrc_3_sel, afrc_en);
            }

            val = (afrc_en) ? 1 : 0;
        }
        break;

        // AFBC/AFRC 설정 상태인지 확인한다.
        case FBDEV_O26_HW_STATUS_FBC:
        {
            int afrc_status = FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_AFRC, opt);

            val = (afrc_status) ? LX_FBDEV_FBC_FORMAT_AFRC : LX_FBDEV_FBC_FORMAT_AFBC;
        }
        break;

        // OSD 가 visible 상태인지 확인한다.
        case FBDEV_O26_HW_STATUS_VISIBLE:
        {
            val = FBDEV_O26_CMN_GetOSDEnable(opt);
        }
        break;

        // V mirror 상태인지 확인한다.
        case FBDEV_O26_HW_STATUS_VMIRROR:
        {

            // https://harmony.lge.com:8443/issue/browse/SICBIT-9024
            // OSD0 의 mirror 정보 참조(OSD_PRE)와 lxboot 의 기록 위치(OSD_POST)가 틀림.
            // 기존과 동일한 위치인 CSR0 로 참조 위치를 수정함. 추후 필요시 OSD0 로 다시 재수정할것
#if 0
            OSD_PRE_RdFL(osd0_ctrl_main);
            OSD_PRE_Rd01(osd0_ctrl_main, osd_v_reverse_en, val);
#else
            UINT32 reg;

            OSD_POST_RdFL(csr0_ctrl_main);
            OSD_POST_Rd01(csr0_ctrl_main, osd_v_reverse_en, val);

            reg = OSD_POST_Rd(csr0_ctrl_main);
            FBDEV_HW_NOTI("csr0.main = 0x%08x, mirror_mode=%d\n", reg, val);
#endif
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

// enable interrupt
int FBDEV_O26_CMN_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable)
{
    switch (intr)
    {
        default:
        case MIXER_INTR:
        {
            int curr_status;

            OSD_POST_RdFL(osd_common_ctrl_irq);

            OSD_POST_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bosd, curr_status);

            if (curr_status != enable)
            {
                OSD_POST_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_bosd, enable);
            }

            OSD_POST_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_en_mixer_sosd, 0x0);
            OSD_POST_WrFL(osd_common_ctrl_irq);

            FBDEV_NOTI("++ osd_intr <%s>\n", enable ? "enabled" : "disabled");
        }
        break;
    }

    return RET_OK;
}

// get interrupt status
int FBDEV_O26_CMN_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
    UINT32 intr_status = 0;
    UINT32 intr_clear;

    OSD_POST_RdFL(osd_common_ctrl_irq);
    OSD_POST_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, intr_clear);

    if (intr_clear)  intr_status |= (1 << MIXER_INTR);
    else             FBDEV_ERROR("OSD ISR - BOSD MIXER INTR error\n");

    FBDEV_ISR_DEBUG("intr_status = 0x%08x\n", intr_status);

    return intr_status;
}

// clear interrupt status
int FBDEV_O26_CMN_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
    OSD_POST_RdFL(osd_common_ctrl_irq);

    // clear both bosd and sosd intrrupt for the safe operation
    OSD_POST_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_bosd, 0x1);
    OSD_POST_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_sosd, 0x1);

    OSD_POST_WrFL(osd_common_ctrl_irq);

    return RET_OK;
}


static void FBDEV_O26_CMN_SetMute(bool onoff)
{
#if 0
    // tcon_mute off
    // see http://clm.lge.com/issue/browse/SICDTV-12974
    FBDEV_NOTI("tcon_mute off\n");
    OVI_HAL_SetDispOutMute(0);
#endif
}

int FBDEV_O26_CMN_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl)
{
    int i;
    //ULONG flags;

    // we can't do spinlock when pivot mode is enabled because sleep ocurrs during GFX merge
    // (2023/04/11) osd on/off 처리중 sleep 가능성이 크므로, spin lock 제거함.
    // spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

    for (i = 0; i < LX_FBDEV_ID_MAX; i++)
    {
        if (ctrl->view_status[i] == 0x0 || ctrl->view_status[i] == 0x1)
        {
            FBDEV_O26_CMN_SetOSDEnable(i, ctrl->view_status[i]);
        }
    }

    // spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);

    return RET_OK;
}

// set OSD out connection ctrl
//
//  param pConnCtrl [IN] connection control data
//  @return RET_OK if success, RET_ERROR otherwise
//
//
int     FBDEV_O26_CMN_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* conn_ctrl)
{
    PARAM_UNUSED(conn_ctrl);

    return RET_OK;
}

/** detect current mirror mode configuration set by boot loader
 *
 */
static void FBDEV_O26_CMN_InitMirrorEnv(void)
{
    UINT32  hw_status;

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_MIRROR_CTRL_T* mirror_ctrl = FBDEV_PLT_GET_MIRROR_CTRL(hw_ctx);

    hw_status = FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_VMIRROR, 0x0);

    if (mirror_ctrl->status == FBDEV_O26_MIRROR_NONE)
    {
        FBDEV_NOTI("osd v_mirror detected (%d)\n", hw_status);

        FBDEV_O26_CMN_MirrorCtrl(hw_status);
    }
}

// debug only
//
int FBDEV_O26_CMN_MirrorCtrl(bool vmirror_en)
{
    FBDEV_WIN_CTX_T* wctx;

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_MIRROR_CTRL_T* mirror_ctrl = FBDEV_PLT_GET_MIRROR_CTRL(hw_ctx);

    int hw_status = FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_VMIRROR, 0x0);

    FBDEV_NOTI("request mirror_ctrl. req_val=%d, hw_status=%d\n", vmirror_en, hw_status);


    // https://harmony.lge.com:8443/issue/browse/SICBIT-9024
    // OSD 의 mirror 상태값 정보를 csr0 에서 획득하기 때문에, 실제 osd0,1 등의 상태값과
    // 다를수 있음. 이 함수는 OSD 관련된 모든 layer 의 설정을 진행하게 되므로, 만약
    // 중복 체크를 하고 싶다면, 단순 대표 상태값이 아닌 실제 HW 설정 여부를 확인하도록 한다.
#if 0

    if (hw_status == vmirror_en)
    {
        FBDEV_NOTI("ignore vmirror change. hw_status=%d\n", hw_status);
        return RET_OK;
    }

#endif

    /* change mirror configuratin */
    mirror_ctrl->status = (vmirror_en) ? FBDEV_O26_V_MIRROR_ON : 0x0;

    // setup OSD_PRE 0/1 & OSD POST
    OSD_PRE_RdFL(osd0_ctrl_main);
    OSD_PRE_RdFL(osd1_ctrl_main);
    OSD_POST_RdFL(osd0_ctrl_sync0);

    OSD_PRE_Wr01(osd0_ctrl_main, osd_v_reverse_en, vmirror_en);
    OSD_PRE_Wr01(osd1_ctrl_main, osd_v_reverse_en, vmirror_en);
    OSD_POST_Wr01(osd0_ctrl_sync0, osd_sync_v_reverse, vmirror_en);

    OSD_PRE_WrFL(osd0_ctrl_main);
    OSD_PRE_WrFL(osd1_ctrl_main);
    OSD_POST_WrFL(osd0_ctrl_sync0);

    // setup CSR0
    OSD_POST_RdFL(csr0_ctrl_main);
    OSD_POST_RdFL(csr0_ctrl_sync0);

    OSD_POST_Wr01(csr0_ctrl_main, osd_v_reverse_en, vmirror_en);
    OSD_POST_Wr01(csr0_ctrl_sync0, osd_sync_v_reverse, vmirror_en);

    OSD_POST_WrFL(csr0_ctrl_main);
    OSD_POST_WrFL(csr0_ctrl_sync0);

    // setup AFBC/AFRC
    AFBC_RdFL(2, ctrl_afbc_0);
    AFBC_RdFL(3, ctrl_afbc_0);
    AFBC_Wr01(2, ctrl_afbc_0, flip_mode, vmirror_en);
    AFBC_Wr01(2, ctrl_afbc_0, flip_mode, vmirror_en);
    AFBC_WrFL(2, ctrl_afbc_0);
    AFBC_WrFL(3, ctrl_afbc_0);

    AFRC_RdFL(2, ctrl_afrc_0);
    AFRC_RdFL(3, ctrl_afrc_0);
    AFRC_Wr01(2, ctrl_afrc_0, flip_mode, vmirror_en);
    AFRC_Wr01(2, ctrl_afrc_0, flip_mode, vmirror_en);
    AFRC_WrFL(2, ctrl_afrc_0);
    AFRC_WrFL(3, ctrl_afrc_0);

    // refresh OSD framebuffer again now
    wctx = FBDEV_GetWinCtx(LX_FBDEV_ID_OSD0);

    if (wctx)
    {
        FBDEV_O26_CMN_WriteOSDHeader(&wctx->pixel);
    }

    return RET_OK;
}

// VOSD ISR handler
void     FBDEV_O26_CMN_ISRHook(void)
{
    // monitor afbc line_wait_cnt change by PQE FW
    // see http://clm.lge.com/issue/browse/SICDTV-13236
    // O24 정책을 일단 그대로 차용한다. 추후 정리하도록 할것
    {
        int afbc_xidx = OSD_IN_OSD0;
        UINT32 img_width;
        UINT32 line_wait_cnt;
        static UINT32 line_wait_cnt_sav = 0x0;

        AFBC_RdFL(afbc_xidx, ctrl_afbc_4);
        AFBC_Rd01(afbc_xidx, ctrl_afbc_4, line_wait_cnt, line_wait_cnt);
        AFBC_Rd01(afbc_xidx, ctrl_afbc_4, img_width, img_width);

        if (line_wait_cnt_sav != line_wait_cnt)
        {
            FBDEV_NOTI("afbc%d.line_wait_cnt changed from 0x%03x to 0x%03x, img_width=%d\n", afbc_xidx, line_wait_cnt_sav,
                       line_wait_cnt, img_width);

            line_wait_cnt_sav = line_wait_cnt;
        }
    }

    /* do nothing */
}

/*========================================================================================
    Implementation Group (OSD HDR releated function)
========================================================================================*/
static void FBDEV_O26_CMN_SetupExternalRenderer(int fb_dev_id, struct fb_info* fbinfo)
{
    // do nothing...
}

static void FBDEV_O26_CMN_AllocExternalRendererFrameBuffer(void)
{
    // do nothing...
}

static void FBDEV_O26_CMN_DestroyExternalRendererFrameBuffer(void)
{
    // do nothing...
}

// O26 OSD 에서 제공하는 output crop 기능을 E-Streamer 에서 사용하도록 한다.
// 통상적인 잘라내기 기능 외에 출력 지점도 지정할 수 있다.
// 4K E-streamer 에서 사용된다.
//
// O24 에서 구현한 내용과 거의 동일할 것으로 판단한다.
static void FBDEV_O26_CMN_SetOutputCropRegion(bool crop_en, int img_width, int img_height, int xoffset, int yoffset,
        LX_RECT_T* crop_rgn)
{
    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_GLB_CTRL_T* glb_ctrl = FBDEV_PLT_GET_GLB_CTRL(hw_ctx);

    // OSD_POST 설정시 필요한 값을 사전에 계산한다.
    int fb_width = img_width;
    int fb_height = img_height;
#ifdef FBDEV_O26_USE_CROP_CTRL
    int fb_xoffset = 0;
    int fb_yoffset = 0;
#else
    int fb_xoffset = (crop_en) ? xoffset : 0;
    int fb_yoffset = (crop_en) ? yoffset : 0;
#endif
    int disp_width = (crop_en) ? img_width : hw_ctx->hw_disp_width;
    int disp_height = (crop_en) ? img_height : hw_ctx->hw_disp_height;

    FBDEV_CHECK_ERROR(!crop_rgn, return, "null param\n");

    FBDEV_HW_NOTI("crop/GLB/OSD_POST configure begin\n");
    FBDEV_NOTI("setup crop en=%s image=%dx%d, x=%d, y=%d, crop_rgn=%d,%d,%d,%d\n",
               crop_en ? "on" : "off",
               img_width, img_height,
               xoffset, yoffset, crop_rgn->x, crop_rgn->y, crop_rgn->w, crop_rgn->h);

#ifdef FBDEV_O26_USE_CROP_CTRL
    OSD_POST_RdFL(osd0_post_crop_ctrl_0);
    OSD_POST_RdFL(osd0_post_crop_ctrl_1);
    OSD_POST_RdFL(osd0_post_crop_ctrl_2);
    OSD_POST_RdFL(osd0_post_crop_ctrl_3);

    OSD_POST_Wr01(osd0_post_crop_ctrl_0, reg_crop_en, crop_en);

    OSD_POST_Wr01(osd0_post_crop_ctrl_0, reg_in_pic_width, img_width);
    OSD_POST_Wr01(osd0_post_crop_ctrl_0, reg_in_pic_height, img_height);
    OSD_POST_Wr01(osd0_post_crop_ctrl_1, hoffset, crop_rgn->x);
    OSD_POST_Wr01(osd0_post_crop_ctrl_1, hactive, crop_rgn->w);
    OSD_POST_Wr01(osd0_post_crop_ctrl_2, voffset, crop_rgn->y);
    OSD_POST_Wr01(osd0_post_crop_ctrl_2, vactive, crop_rgn->h);
    OSD_POST_Wr01(osd0_post_crop_ctrl_3, crop_mixer_xpos, xoffset);
    OSD_POST_Wr01(osd0_post_crop_ctrl_3, crop_mixer_ypos, yoffset);

    OSD_POST_WrFL(osd0_post_crop_ctrl_0);
    OSD_POST_WrFL(osd0_post_crop_ctrl_1);
    OSD_POST_WrFL(osd0_post_crop_ctrl_2);
    OSD_POST_WrFL(osd0_post_crop_ctrl_3);
#endif

    // setup GLB
    // crop_en = 1 일 때는 E-Streamer 의 크기(ex, 768x2160)가 입력된다.
    // crop_en = 0 일 때는 UI 의 크기 (ex, 1920x1080)가 입력된다.

#if 1  // not ready
    FIXME_NOTE("아래 부분 맍는지 확인 필요. 4K OSD full screen 아니므로, E-Streamer 표현이 좀 이상한듯")

    if (hw_ctx->b_support_4kosd)
    {
        glb_ctrl->mux[OSD_IN_OSD0].osd_en = 1;
        glb_ctrl->mux[OSD_IN_OSD1].osd_en = 1;

        glb_ctrl->mux[OSD_IN_OSD0].coord = LX_MAKE_RECT(0, 0, fb_width / 2, fb_height);
        glb_ctrl->mux[OSD_IN_OSD1].coord = LX_MAKE_RECT(fb_width / 2, 0, fb_width / 2, fb_height);
    }
    else
    {
        glb_ctrl->mux[OSD_IN_OSD0].osd_en = 1;
        glb_ctrl->mux[OSD_IN_OSD1].osd_en = 0;

        glb_ctrl->mux[OSD_IN_OSD0].coord = LX_MAKE_RECT(0, 0, fb_width, fb_height);
    }

    glb_ctrl->canvas_w = fb_width;
    glb_ctrl->canvas_h = fb_height;

    FBDEV_HW_NOTI("setup GLB. canvas=%dx%d\n", glb_ctrl->canvas_w, glb_ctrl->canvas_h);
    FBDEV_O26_CMN_SetupGLB();
#endif

    // setup OSD_POST
    // E-Streamer 상태 진입, 해제시 OSD_POST 기본 설정을 하도록 한다.
    OSD_POST_RdFL(osd0_ctrl_main);
    //OSD_POST_RdFL(osd0_ctrl_hdr0);
    //OSD_POST_RdFL(osd0_ctrl_hdr1);
    //OSD_POST_RdFL(osd0_ctrl_hdr2);

    OSD_POST_Wr01(osd0_ctrl_hdr0, osd_hdr_xpos, fb_xoffset);
    OSD_POST_Wr01(osd0_ctrl_hdr0, osd_hdr_ypos, fb_yoffset);

    OSD_POST_Wr01(osd0_ctrl_hdr1, osd_hdr_w_mem, fb_width);
    OSD_POST_Wr01(osd0_ctrl_hdr1, osd_hdr_h_mem, fb_height);

    OSD_POST_Wr01(osd0_ctrl_hdr2, osd_hdr_w_out, disp_width);
    OSD_POST_Wr01(osd0_ctrl_hdr2, osd_hdr_h_out, disp_height);

    OSD_POST_Wr01(osd0_ctrl_main, osd_hdr_ready_flag, 0x1);
    OSD_POST_WrFL(osd0_ctrl_hdr0);
    OSD_POST_WrFL(osd0_ctrl_hdr1);
    OSD_POST_WrFL(osd0_ctrl_hdr2);
    OSD_POST_WrFL(osd0_ctrl_main);

    FBDEV_HW_NOTI("setup OSD_POST. in: %dx%d, out: %d,%d %dx%d\n",
                  fb_width, fb_height, xoffset, yoffset, disp_width, disp_height);

    FBDEV_HW_NOTI("crop/GLB/OSD_POST configure completed\n");
}

// initialize FBC variable to the default state.
// The real HW register will be set inside FBDEV_O26_CMN_WriteOSDHeader()
// This function is also called during instant boot resume to setup AFBC register again.
//
static void FBDEV_O26_CMN_InitFBCEnv(void)
{
    int i;

    for (i = 0; i <= LX_FBDEV_ID_OSD1; i++)
    {
        FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
        FBDEV_PLT_FBC_CTRL_T* fbc_ctrl = FBDEV_PLT_GET_FBC_CTRL(hw_ctx, i);

        fbc_ctrl->fbc_fmt = LX_FBDEV_FBC_FORMAT_RAW;
        fbc_ctrl->status  = FBDEV_O26_FBC_STATUS_NONE;

        FBDEV_O26_FBC_DEBUG("fb(%d) initialize fbc env\n", i);

        // UI 기본 설정은 항상 AFBC 가 되도록 조치한다.
        FBDEV_O26_CMN_SetupFBC(i, LX_FBDEV_FBC_FORMAT_AFBC);
    }
}

// create or destory FBC envrionment
//
// O26 의 경우 RAW 모드 지원을 하지 않으므로, 항상 AFBC/AFRC 모드이다.
// 따라서 이 함수에서는 압축 모드 지원을 위한 최소한의 코드를 구현하도록 한다.
//
static void FBDEV_O26_CMN_SetupFBC(int fb_dev_id, LX_FBDEV_FBC_FORMAT_T fbc_fmt)
{
    int i;
    int xidx;
    int xnum, xlst[2], afbc_xlst[2];

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_FBC_CTRL_T* fbc_ctrl = FBDEV_PLT_GET_FBC_CTRL(hw_ctx, fb_dev_id);

    FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_HW_NOTI("fb(%d) curr fbc_fmt=0x%x(%s), new fbc_fmt=0x%x(%s)\n",
                  fb_dev_id,
                  fbc_ctrl->fbc_fmt,
                  fbdev_util_get_fbc_string(fbc_ctrl->fbc_fmt),
                  fbc_fmt,
                  fbdev_util_get_fbc_string(fbc_fmt));

    // check HW status
    if (fbc_ctrl->fbc_fmt == fbc_fmt)
    {
        int hw_fbc_fmt = FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_FBC, fb_dev_id);

        FBDEV_CHECK_CODE(fbc_ctrl->fbc_fmt != hw_fbc_fmt,
                         goto afbc_config,
                         "<!> fb(%d) sw/hw status mismatch (hw:%d, sw:%d)\n", fb_dev_id, hw_fbc_fmt, fbc_ctrl->fbc_fmt);

        return; /* same value. do nothing */
    }

afbc_config:

    // FBC 포맷 변환, 즉 AFBC <=> AFRC 는 중요한 상태 변화이므로, 무조건 출력이 나와야 한다.
    FBDEV_NOTI("fb(%d) setup fbc_fmt old=%s, new=%s\n",
               fb_dev_id, fbdev_util_get_fbc_string(fbc_ctrl->fbc_fmt), fbdev_util_get_fbc_string(fbc_fmt));

    xnum = FBDEV_O26_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);

    // setup AFBC/AFRC basic registers
    {
        UINT32 enable = FBDEV_O26_CMN_GetOSDEnable(fb_dev_id);
        UINT32 afrc_sel = (fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC) ? 1 : 0;

        GSC_CTRL_RdFL(ctrl_block1);
        AFBC_RdFL(OSD_IN_OSD0, ctrl_afbc_0);
        AFBC_RdFL(OSD_IN_OSD1, ctrl_afbc_0);
        AFRC_RdFL(OSD_IN_OSD0, ctrl_afrc_0);
        AFRC_RdFL(OSD_IN_OSD1, ctrl_afrc_0);

        if (afbc_xlst[0] == OSD_IN_OSD0 || afbc_xlst[1] == OSD_IN_OSD0)
        {
            GSC_CTRL_Wr01(ctrl_block1, reg_afbc_afrc_2_sel, afrc_sel);
            AFBC_Wr01(OSD_IN_OSD0, ctrl_afbc_0, update_ready_flag_en, 0x1);
            AFRC_Wr01(OSD_IN_OSD0, ctrl_afrc_0, update_ready_flag_en, 0x1);

            FBDEV_HW_NOTI("fb(%d) %s enabled. xlst=%d,%d view=%d\n",
                          fb_dev_id, fbdev_util_get_fbc_string(fbc_fmt), afbc_xlst[0], afbc_xlst[1], enable);
        }

        if (afbc_xlst[0] == OSD_IN_OSD1 || afbc_xlst[1] == OSD_IN_OSD1)
        {
            GSC_CTRL_Wr01(ctrl_block1, reg_afbc_afrc_3_sel, afrc_sel);
            AFBC_Wr01(OSD_IN_OSD1, ctrl_afbc_0, update_ready_flag_en, 0x1);
            AFRC_Wr01(OSD_IN_OSD1, ctrl_afrc_0, update_ready_flag_en, 0x1);

            FBDEV_HW_NOTI("fb(%d) %s enabled. xlst=%d,%d view=%d\n",
                          fb_dev_id, fbdev_util_get_fbc_string(fbc_fmt), afbc_xlst[0], afbc_xlst[1], enable);
        }

        GSC_CTRL_WrFL(ctrl_block1);
        AFBC_WrFL(OSD_IN_OSD0, ctrl_afbc_0);
        AFBC_WrFL(OSD_IN_OSD1, ctrl_afbc_0);
        AFRC_WrFL(OSD_IN_OSD0, ctrl_afrc_0);
        AFRC_WrFL(OSD_IN_OSD1, ctrl_afrc_0);
    }

    // setup OSD_PRE registers
    for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
    {
        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xidx), return, "fb(%d) invalid xidx %d\n", fb_dev_id, xidx);

        if (xlst[0] == OSD_IN_OSD0 || xlst[1] == OSD_IN_OSD0)
        {
            OSD_PRE_RdFL(osd0_ctrl_main);
            OSD_PRE_Wr01(osd0_ctrl_main, osd_bitmap_only_mode_en, 0x1);
            OSD_PRE_WrFL(osd0_ctrl_main);
        }

        if (xlst[0] == OSD_IN_OSD1 || xlst[1] == OSD_IN_OSD1)
        {
            OSD_PRE_RdFL(osd1_ctrl_main);
            OSD_PRE_Wr01(osd1_ctrl_main, osd_bitmap_only_mode_en, 0x1);
            OSD_PRE_WrFL(osd1_ctrl_main);
        }

        fbc_ctrl->status |=  FBDEV_O26_FBC_STATUS_PATH_CHANGE;;
    }

    FBDEV_O26_FBC_DEBUG("fb(%d) fbc_mode=0x%x(%s) setup completed\n",
                        fb_dev_id, fbc_fmt, fbdev_util_get_fbc_string(fbc_fmt));

    fbc_ctrl->fbc_fmt = fbc_fmt;
}

// setup AFBC HW register for OSD input
//
// 최대 2개의 AFBC decoder 를 처리할 수 있다.
// 하나의 AFBC decoder 는 최대 width 1920 까지의 AFBC 이미지를 처리할 수 있다.
// 하나의 AFBC decdoer 는 최대 height 2160 까지의 AFBC 이미지를 처리할 수 있다.
//
// 통상적인 2K OSD (1920x1080) 은 하나의 AFBC decoder 로 처리 가능하다.
// 통상적인 4K OSD (3840x2160) 은 AFBC0 를 통해 L 1920 을, AFBC1 를 통해 R 1920을 읽도록 설정한다.
// (AFBC0 은 x=0~1919 영역을, AFBC1 은 x=1920~3839 영역을 읽도록 설정된다)
//
// 각 AFBC decoder 의 stride 정보를 통해 통 이미지인지 여부를 알 수 있게 된다.
//
// 예)
// image[0] = size=1920x2160, x_pos=0, stride=3840x4
// image[1] = size=1920x2160, x_pos=1920, stride=3840x4
//
// 이 함수는 AFBC register 기록에 집중한다.
// UI 인지 E-Streamer 인지에 따른 이미지 특성은 이 함수를 호출하는 측에서 조치가 되어야 한다.
//
// 제약사항)
// SW 복잡도 감소를 위하여 2개의 AFBC decoder 가 사용되는 경우,
// 동일한 afbc image 를 처리하게 되며, 기본적인 좌표 정보도 동일하다.
// L/R 표현을 위한 x_pos 값만 별도로 처리하도록 하겠다.
//
static void FBDEV_O26_CMN_WriteAFBCHdrRegs(int fb_dev_id,
        FBDEV_PLT_OSD_HDR_T osd_hdr[2], FBDEV_PLT_OSD_EXHDR_T* osd_exhdr)
{
    UINT32 img_addr;
    int img_x;
    int img_y;
    int img_w;
    int img_h;
    int img_bpp;
    int img_stride;

    int i;
    int afbc_xidx;
    int xnum, xlst[2], afbc_xlst[2];

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];
    FBDEV_PLT_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

    FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);
    FBDEV_CHECK_DEBUG(fbc_ctrl->fbc_fmt != LX_FBDEV_FBC_FORMAT_AFBC, return, "fb(%d) non-afbc image\n", fb_dev_id);

    xnum = FBDEV_O26_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);

    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d. fb(%d)\n", fb_dev_id, xnum, fb_dev_id);

    // osd_hdr 로 넘어오는 img_w, img_h 는 L/R 이 같은 값이므로 osd_hdr[1] 을
    // 굳이 참조할 필요는 없다.
    img_x = osd_hdr[0].osd_hdr_xpos;
    img_y = osd_hdr[0].osd_hdr_ypos;
    img_w = osd_hdr[0].osd_hdr_w_mem;
    img_h = osd_hdr[0].osd_hdr_h_mem;
    img_addr = osd_hdr[0].osd_hdr_ptr_bmp;
    img_stride = osd_exhdr->img_stride;
    img_bpp = FBDEV_O26_BITS_2_BYTES(osd_exhdr->bits_per_pixel);

    for (i = 0; i < xnum; i++)
    {
        UINT32 line_wait_cnt;
        UINT32 img_width;
        UINT32 new_img_width;

        afbc_xidx = afbc_xlst[i];

        // current fb_dev_id is not attached to afbc
        if (INVALID_FBC_XIDX(afbc_xidx)) continue;

        if (i > 0) img_x += img_w;

        FBDEV_O26_FBC_DEBUG("fb(%d) afbc.xidx(%d) paddr=0x%08x pos=%d,%d dim=%dx%d, stride=%d\n",
                            fb_dev_id, afbc_xidx, img_addr,
                            img_x, img_y, img_w, img_h, img_stride);

        // once the whole AFBC registers are set, I will just update the minimal registers
        AFBC_RdFL(afbc_xidx, ctrl_afbc_1);
        AFBC_RdFL(afbc_xidx, ctrl_afbc_2);
        AFBC_RdFL(afbc_xidx, ctrl_afbc_3);
        AFBC_RdFL(afbc_xidx, ctrl_afbc_8);

        AFBC_Wr01(afbc_xidx, ctrl_afbc_1, hd_base, img_addr);
        AFBC_Wr01(afbc_xidx, ctrl_afbc_8, pl_data_base, img_addr);

        // AFBC data size description
        AFBC_Wr01(afbc_xidx, ctrl_afbc_2, start_x, img_x);
        AFBC_Wr01(afbc_xidx, ctrl_afbc_2, start_y, img_y);
        AFBC_Wr01(afbc_xidx, ctrl_afbc_3, end_x, LX_CALC_ALIGNED_VALUE(img_x + img_w - 2, 1));
        AFBC_Wr01(afbc_xidx, ctrl_afbc_3, end_y, img_y + img_h - 1);

        AFBC_WrFL(afbc_xidx, ctrl_afbc_1);
        AFBC_WrFL(afbc_xidx, ctrl_afbc_2);
        AFBC_WrFL(afbc_xidx, ctrl_afbc_3);
        AFBC_WrFL(afbc_xidx, ctrl_afbc_8);

        // see http://clm.lge.com/issue/browse/SICDTV-13236
        // afbc img_width 의 변경 발생시 로그와 함께 설정을 진행할것
        new_img_width = img_stride / img_bpp;

        AFBC_RdFL(afbc_xidx, ctrl_afbc_4);
        AFBC_Rd01(afbc_xidx, ctrl_afbc_4, img_width,  img_width);
        AFBC_Rd01(afbc_xidx, ctrl_afbc_4, line_wait_cnt, line_wait_cnt);

        if (img_width != new_img_width)
        {
            FBDEV_NOTI("afbc%d.img_width changed from %d to %d, line_wait_cnt=0x%03x\n",
                       afbc_xidx, img_width, new_img_width, line_wait_cnt);

            AFBC_Wr01(afbc_xidx, ctrl_afbc_4, img_width,  new_img_width);
            AFBC_WrFL(afbc_xidx, ctrl_afbc_4);
        }

        // AFBC general setup only
        // below configurations will be called when the first AFBC image is feeded
        if (!(fbc_ctrl->status & FBDEV_O26_FBC_STATUS_HDR_SETUP))
        {
            // see http://clm.lge.com/issue/browse/SICDTV-12366 김민c 가이드
            FIXME_NOTE("O26 검증 FW 에서 7, 6 으로 설정하고 있음")
            int pl_gmau_id = 7;
            int hd_gmau_txid = 6;

            AFBC_RdFL(afbc_xidx, ctrl_afbc_0);
            AFBC_RdFL(afbc_xidx, ctrl_afbc_5);
            AFBC_RdFL(afbc_xidx, ctrl_afbc_9);
            AFBC_RdFL(afbc_xidx, ctrl_afbc_c);
            AFBC_RdFL(afbc_xidx, ctrl_afbc_10);

            // HW guy said that I should set the same value to AFBC hdr & data :(
            // I think it's enough to change only below two value (hd_base, pl_data_base)
            //
            AFBC_Wr01(afbc_xidx, ctrl_afbc_9, pl_data_end,  0xffffffff);

            // raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
            // HW guy fixed dec_buf_depth value to 959 and pl_buf_depth value to 255.
            AFBC_Wr01(afbc_xidx, ctrl_afbc_5, dec_buf_depth_m1, 959);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_5, pl_buf_depth_m1,  255);

            // raxis.lim (2015/10/12) -- nobody knows this register (woonhyeon.kim is out of office for 3yrs)
            // HW test value : 0x0000_FF76
            //
            FIXME_NOTE("레지스터 메뉴얼 기준 endian_arb 값은 1 이어야 할듯함")
            AFBC_Wr01(afbc_xidx, ctrl_afbc_c, hd_endian_arb, 1);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_c, pl_endian_arb, 1);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_c, hd_endian_sw,  0xf);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_c, pl_endian_sw,  0xf);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_c, pl_gmau_id,    pl_gmau_id);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_c, hd_gmau_txid,  hd_gmau_txid);

            // raxis.lim (2015/10/12) -- nobody knows this register
            //
            // 0xff80_80ff @RGBA (*)
            // 0xffff_8080 @ARGB
#if 1
            AFBC_Wr(afbc_xidx, ctrl_afbc_10, 0xFF8080FF);  /* +0xD0 : 0xff8080ff for RGBA case */
#else
            AFBC_Wr(afbc_xidx, ctrl_afbc_10, 0xFFFFFFFF);  /* +0xD0 : 0xffffffff for argb case */
#endif
            // (2020/04/29) see http://clm.lge.com/issue/browse/SICDTV-9405
            //
            // ctrl_afbc_0.run_mode = 0x1 if AFBC 1.0
            //                      = 0x0 if AFBC 1.1
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, start,        0);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, ready,        0);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset,     0);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset_fifo, 0);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, run_mode,     1);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, pl_addr_mode, 1);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, sw_reset_ack, 0);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, gmau_arb_sw_reset, 0);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, flip_mode, (mirror_ctrl->status & FBDEV_O26_V_MIRROR_ON) ? 1 : 0);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, ignore_q_full, 0);
            AFBC_Wr01(afbc_xidx, ctrl_afbc_0, wrap_en,      1);

            // flush data
            AFBC_WrFL(afbc_xidx, ctrl_afbc_5);
            AFBC_WrFL(afbc_xidx, ctrl_afbc_9);
            AFBC_WrFL(afbc_xidx, ctrl_afbc_c);
            AFBC_WrFL(afbc_xidx, ctrl_afbc_10);
            AFBC_WrFL(afbc_xidx, ctrl_afbc_0);
        }
    }

    fbc_ctrl->status |= FBDEV_O26_FBC_STATUS_HDR_SETUP;
}

// FIXME: 기본 동작은 AFBC 랑 거의 같다.  검증하면서 다시 정리할것
//
static void FBDEV_O26_CMN_WriteAFRCHdrRegs(int fb_dev_id,
        FBDEV_PLT_OSD_HDR_T osd_hdr[2], FBDEV_PLT_OSD_EXHDR_T* osd_exhdr)
{
    UINT32 img_addr;
    int img_x;
    int img_y;
    int img_w;
    int img_h;
    int img_bpp;
    int img_stride;

    int i;
    int afrc_xidx;
    int xnum, xlst[2], afrc_xlst[2];

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_FBC_CTRL_T* fbc_ctrl = &hw_ctx->fbc_ctrl[fb_dev_id];
    FBDEV_PLT_MIRROR_CTRL_T* mirror_ctrl = &hw_ctx->mirror_ctrl;

    FBDEV_CHECK_CODE(!CHECK_AFRC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);
    FBDEV_CHECK_DEBUG(fbc_ctrl->fbc_fmt != LX_FBDEV_FBC_FORMAT_AFRC, return, "fb(%d) non-afrc image\n", fb_dev_id);

    xnum = FBDEV_O26_CMN_GetHWXListEx(fb_dev_id, xlst, afrc_xlst);

    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d. fb(%d)\n", fb_dev_id, xnum, fb_dev_id);

    // osd_hdr 로 넘어오는 img_w, img_h 는 L/R 이 같은 값이므로 osd_hdr[1] 을
    // 굳이 참조할 필요는 없다.
    img_x = osd_hdr[0].osd_hdr_xpos;
    img_y = osd_hdr[0].osd_hdr_ypos;
    img_w = osd_hdr[0].osd_hdr_w_mem;
    img_h = osd_hdr[0].osd_hdr_h_mem;
    img_addr = osd_hdr[0].osd_hdr_ptr_bmp;
    img_stride = osd_exhdr->img_stride;
    img_bpp = FBDEV_O26_BITS_2_BYTES(osd_exhdr->bits_per_pixel);

    for (i = 0; i < xnum; i++)
    {
        afrc_xidx = afrc_xlst[i];

        // current fb_dev_id is not attached to afrc
        if (INVALID_FBC_XIDX(afrc_xidx)) continue;

        if (i > 0) img_x += img_w;

        FBDEV_O26_FBC_DEBUG("fb(%d) afrc.xidx(%d) paddr=0x%08x pos=%d,%d dim=%dx%d, stride=%d\n",
                            fb_dev_id, afrc_xidx, img_addr,
                            img_x, img_y, img_w, img_h, img_stride);

        // once the whole AFRC registers are set, I will just update the minimal registers
        if (fbc_ctrl->status & FBDEV_O26_FBC_STATUS_HDR_SETUP)
        {
            AFRC_RdFL(afrc_xidx, ctrl_afrc_4);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_5);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_6);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_7);

            AFRC_Wr01(afrc_xidx, ctrl_afrc_4, pl_data_base, img_addr);

            AFRC_Wr01(afrc_xidx, ctrl_afrc_5, start_x,     img_x);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_5, start_y,     img_y);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_6, end_x,       ALIGN(img_x + img_w, 2) - 1);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_6, end_y,       img_y + img_h - 1);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_7, img_width,   img_stride / img_bpp);

            AFRC_WrFL(afrc_xidx, ctrl_afrc_4);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_5);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_6);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_7);
        }
        // below configurations will be called when the first AFRC image is feeded
        else
        {
            // see http://clm.lge.com/issue/browse/SICDTV-12366 김민c 가이드
            int pl_gmau_txid = 7;

            AFRC_RdFL(afrc_xidx, ctrl_afrc_0);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_2);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_4);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_5);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_6);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_7);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_c);
            AFRC_RdFL(afrc_xidx, ctrl_afrc_14);

            // AFRC control block description
            FIXME_NOTE("아래 항목 동적으로 설정가능하게 코드 준비할것")
            AFRC_Wr01(afrc_xidx, ctrl_afrc_2, comp_size, 32);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_2, bit_depth, 8);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_2, col_format, 1);

            // HW guy said that I should set the same value to AFRC hdr & data :(
            // I think it's enough to change only below two value (hd_base, pl_data_base)
            //
            AFRC_Wr01(afrc_xidx, ctrl_afrc_4, pl_data_base, img_addr);

            // AFRC data size description
            // end_x:
            //  "horizontal end pixel position in full frame.
            //  decoding end horizontal pixel position of the ROI in the frame.
            //  - argb : 4 pixel unit (4 픽셀 배수)
            //  - y : 16 pixel unit
            //  - uv : 8 pixel unit
            //
            // (ex) ARGB 4K case: left.end_x = 1919, right.end_x = 3939
            //
            // end_y:
            // "vertical end pixel position in full frame.
            // decoding end vertical pixel position of the ROI in the frame.
            //
            // (ex) ARGB 4K case: end_y = 2159
            AFRC_Wr01(afrc_xidx, ctrl_afrc_5, start_x,     img_x);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_5, start_y,     img_y);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_6, end_x,       ALIGN(img_x + img_w, 2) - 1);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_6, end_y,       img_y + img_h - 1);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_7, img_width,   img_stride / img_bpp);

            AFRC_Wr01(afrc_xidx, ctrl_afrc_14, pl_data_end,  0xffffffff);

            // use HW guide value.
            // pl_endian_arb = 1, pl_endian_sw = 0, pl_gmau_txid = 7
            AFRC_Wr01(afrc_xidx, ctrl_afrc_c, pl_endian_arb, 1);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_c, pl_endian_sw,  0);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_c, pl_gmau_txid,  pl_gmau_txid);

            AFRC_Wr01(afrc_xidx, ctrl_afrc_0, start,        0);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_0, ready,        0);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_0, sw_reset,     0);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_0, sw_reset_fifo, 0);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_0, sw_reset_ack, 0);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_0, gmau_arb_sw_reset, 0);
            AFRC_Wr01(afrc_xidx, ctrl_afrc_0, flip_mode, (mirror_ctrl->status & FBDEV_O26_V_MIRROR_ON) ? 1 : 0);

            AFRC_WrFL(afrc_xidx, ctrl_afrc_2);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_4);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_5);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_6);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_7);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_c);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_14);
            AFRC_WrFL(afrc_xidx, ctrl_afrc_0);
        }
    }

    fbc_ctrl->status |= FBDEV_O26_FBC_STATUS_HDR_SETUP;
}

// flush AFRC/AFBC header in register space and make HW to fetch registers from the next OSD frame
//
static void FBDEV_O26_CMN_FlushFBCHdrRegs(int fb_dev_id)
{
    int i;
    int fbc_xidx;
    int xnum, xlst[2], fbc_xlst[2];

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    FBDEV_PLT_FBC_CTRL_T* fbc_ctrl = FBDEV_PLT_GET_FBC_CTRL(hw_ctx, fb_dev_id);

    //FBDEV_CHECK_CODE(!CHECK_AFBC_FBDEV(fb_dev_id), return, "invalid fb(%d)\n", fb_dev_id);

    FBDEV_HW_NOTI("fb(%d) fbc_fmt=%s\n", fb_dev_id, fbdev_util_get_fbc_string(fbc_ctrl->fbc_fmt));

    xnum = FBDEV_O26_CMN_GetHWXListEx(fb_dev_id, xlst, fbc_xlst);
    FBDEV_O26_FBC_DEBUG("fb(%d) xnum=%d, fbc_xlst=%d,%d\n", fb_dev_id, xnum, fbc_xlst[0], fbc_xlst[1]);

    // current fb_dev_id is not attached to fbc
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "fb(%d) invalid xnum %d\n", fb_dev_id, xnum);

    for (i = 0; i < xnum ; i++)
    {
        fbc_xidx = fbc_xlst[i];

        if (INVALID_FBC_XIDX(fbc_xidx)) continue;

        if (fbc_ctrl->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC)
        {
            AFRC_RdFL(fbc_xidx, ctrl_afrc_0);
            AFRC_Wr01(fbc_xidx, ctrl_afrc_0, update_ready_flag, 0x1);
            AFRC_WrFL(fbc_xidx, ctrl_afrc_0);
        }
        else
        {
            AFBC_RdFL(fbc_xidx, ctrl_afbc_0);
            AFBC_Wr01(fbc_xidx, ctrl_afbc_0, update_ready_flag, 0x1);
            AFBC_WrFL(fbc_xidx, ctrl_afbc_0);
        }

        FBDEV_HW_NOTI("fb(%d) fbc_xidx(%d) flush done\n", fb_dev_id, fbc_xidx);
    }
}

// write OSD HW register
//
// 2K OSD, 4K OSD 여부에 따라 POSD 갯수를 판단하다.
// 필요시 전달된 OSD 정보값을 조작할 수도 있다.
//
void    FBDEV_O26_CMN_WriteHdrRegs(int fb_dev_id, FBDEV_PLT_OSD_HDR_T* osd_hdr, FBDEV_PLT_OSD_EXHDR_T* osd_exhdr)
{
    int i;
    int xidx;
    int xnum, xlst[2];

    FBDEV_PLT_OSD_HDR_T osd_hw_hdr[2];  // 4K OSD 출력을 위하여 최대 2개 layer 필요
    UINT32* hdr_regs;

    ULONG flags;
    struct scanvas* canvas = NULL;
    FBDEV_WIN_CTX_T* wctx = NULL;
    //FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

    canvas = FBDEV_GetWinCanvas(fb_dev_id);
    FBDEV_CHECK_CODE(NULL == canvas, return, "invalid canvas. fb(%d)\n", fb_dev_id);

    wctx = FBDEV_GetWinCtx(fb_dev_id);
    FBDEV_CHECK_CODE(NULL == wctx, return, "invalid winctx. fb(%d)\n", fb_dev_id);

    xnum = FBDEV_O26_CMN_GetHWXList(fb_dev_id, xlst);

    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return, "invalid xnum %d. fb(%d)\n", xnum, fb_dev_id);

    spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

    // 디버깅 목적으로 OSD 업데이트를 막을 수 있다.
    if (!wctx->status.b_osd_hdr_flush)
    {
        UINT32 disp_fbmem;
        OSDX_DESC_T osdx_desc;

        for (i = 0; i < xnum; i++)
        {
            xidx = xlst[i];

            if (INVALID_XIDX(xidx)) continue;

            FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_ALL);
            disp_fbmem = osdx_desc.osd_ctrl_hdr6.osd_hdr_ptr_bmp;

            FBDEV_NOTI("fb(%d) idx=%d freezed. osd_hdr_flush deferred. keep fbmem=0x%08x\n",
                       fb_dev_id, xidx, disp_fbmem);
        }

        goto func_exit;
    }

    for (i = 0; i < xnum; i++)
    {
        OSDX_DESC_T osdx_desc;

        xidx = xlst[i];

        if (INVALID_XIDX(xidx)) continue;

        // 통으로 전달된 osd_hdr 를 기반으로 최대 2개의 HW osd_hdr를 생성한다.
        memcpy(&osd_hw_hdr[i], osd_hdr, sizeof(FBDEV_PLT_OSD_HDR_T));

        FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_HDR_ALL);

        // xnum = 2 (4K OSD 처리)
        //
        // fb(0) 은 3840x2160 통으로 이미지가 전달되어, 4K OSD 출력 기능을 사용하여 처리되어야 한다.
        // fb(1) 은 1920x2160 으로 리포맷팅된 이미지가, L/R 동일하게 복사되어 출력된다. (F22 인터페이스)
        //
        // 이를 정리하면 4K 통이미지로 전달되는 경우, L/R 를 분리하여 각각의 osd_hw_hdr 를 만든다.
        // 그 외의 경우는 이미 앞에서 조작된 header 정보를 그대로 이용한다.
        //
        // (노트) 4K 통이미지로 구성된 AFBC 이미지에 대한 데이터 해석은 FBDEV_O26_CMN_WriteFBCHdrRegs 참조할것
        //        여기서는 L/R 에 대한 오프셋/크기 정보만을 처리한다.
        // (노트) 4K UI OSD 에 대한 input/output scaler 설정은 REG_4K_OSD_MAIN_CTRL_2, REG_4K_OSD_MAIN_CTRL_3 을
        //        통해 설정된다.
        //
        // (2024/12/20 노트) O26 에서는 GLB 가 있으므로.. osd_hdr_xpos 로 L/R 를 구분할 수 없다.
        // 기존 칩의 경우에는 osd_hdr_xpos 가 OSD 출력 위치를 결정했지만, O26 의 경우에는
        // GLB 를 통해 합성이 되기 때문에, AFBC/AFRC 에서 읽은 데이터가 x,y 변경없이 그대로 통과해서 나가야 한다.
        // GLB 내의 start_x, y, end_x, y 에서 출력 좌표 위치를 결정한다.
        // 실제로 osd_hdr_xpos 설정값이 동작하기 때문에, 만약 의미있는 값을 주게 되면.. 일종의 offset 처럼 동작을
        // 하게 되는데, 의도와 상관없이 이상한 결과가 나오게 될것이다.
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0 && xnum == 2)
        {
            osd_hw_hdr[i].osd_hdr_ptr_bmp += (osd_exhdr->img_stride / 2) * i;

            osd_hw_hdr[i].osd_hdr_w_mem /= 2;
            osd_hw_hdr[i].osd_hdr_w_out /= 2;

            osd_hw_hdr[i].osd_hdr_xpos = 0;
            osd_hw_hdr[i].osd_hdr_ypos = 0;
        }

        FBDEV_HW_NOTI("fb(%d) xidx(%d), osd_hw_hdr in=%dx%d out=%dx%d\n",
                      fb_dev_id, xidx,
                      osd_hw_hdr[i].osd_hdr_w_mem,
                      osd_hw_hdr[i].osd_hdr_h_mem,
                      osd_hw_hdr[i].osd_hdr_w_out,
                      osd_hw_hdr[i].osd_hdr_h_out);

        hdr_regs = (UINT32*)&osd_hw_hdr[i];

        memcpy(&osdx_desc.osd_ctrl_hdr0, &hdr_regs[0], sizeof(UINT32));
        memcpy(&osdx_desc.osd_ctrl_hdr1, &hdr_regs[1], sizeof(UINT32));
        memcpy(&osdx_desc.osd_ctrl_hdr2, &hdr_regs[2], sizeof(UINT32));
        memcpy(&osdx_desc.osd_ctrl_hdr3, &hdr_regs[3], sizeof(UINT32));
        memcpy(&osdx_desc.osd_ctrl_hdr4, &hdr_regs[4], sizeof(UINT32));
#ifndef FIXED_BASE_ADDR
        memcpy(&osdx_desc.osd_ctrl_hdr5, &hdr_regs[5], sizeof(UINT32));
#endif
        memcpy(&osdx_desc.osd_ctrl_hdr6, &hdr_regs[6], sizeof(UINT32));

        FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_HDR_ALL);

        FIXME_NOTE("OSD0/1 PRE 에 대한 설정은 PQE 제어와 무관하다. 아래 코드 정리 필요하다")
#if 0

        // (2017/09/15)
        // raxis.lim (2017/09/15) -- DO NOT write OSD out_win only
        // when OSD0_PQEFW_OSD0_OUT_CTRL is enabled
        //
        // raxis.lim (2019/06/19)
        // support orbit control (http://clm.lge.com/issue/browse/SDOSTB-246)
        // (note) 4KOSD 테스트 모드에서는 orbit 활성화시 OSD 출력 정상아님. orbit 제어하는 FW 에서 추가 제어 필요할 듯 예상됨
        //
        // raxis.lim (2019/07/29)
        // EXT_FRC 가 붙었을 경우에는 orbit control 을 O26 에서 하지 않는다.
        // 향후에는 flag 를 좀 더 조정하자.
        //
        if (fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            if (osd_pqefw_osd0_out_ctrl && (hw_ctx->hw_wa_flag & FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL))
            {
                /* do nothing */
            }
            else
            {
                FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_HDR_2);

                FBDEV_HW_NOTI("fb(%d) xidx=%d flush OSD_HDR2. %dx%d\n",
                              fb_dev_id,
                              xidx,
                              osdx_desc.osd_ctrl_hdr2.osd_hdr_w_out,
                              osdx_desc.osd_ctrl_hdr2.osd_hdr_h_out);
            }
        }
        else
        {
            FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_HDR_2);
        }

#endif
    }

    /* flush afbc/afrc register */
    if (fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        FBDEV_O26_CMN_SetupFBC(fb_dev_id, canvas->fbc_fmt);

        if (canvas->fbc_fmt == LX_FBDEV_FBC_FORMAT_AFRC)
        {
            FBDEV_O26_CMN_WriteAFRCHdrRegs(fb_dev_id, osd_hw_hdr, osd_exhdr);
        }
        else
        {
            FBDEV_O26_CMN_WriteAFBCHdrRegs(fb_dev_id, osd_hw_hdr, osd_exhdr);
        }

        FBDEV_O26_CMN_FlushFBCHdrRegs(fb_dev_id);
    }

    // flush post header
    //
    // (2025/04/29) E-Streamer 동작시 OSD POST scaler 가 동적으로 업데이트 되어야 하므로,
    // fb(1) 한정으로 OSD_POST header 를 조치하도록 한다.
    // 단 fb(1) off 즉 E-Streamer 상태 해제시 원상 복귀를 해줘야 한다.
    // FBDEV_O26_CMN_SetOutputCropRegion() 참조
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        OSD_POST_RdFL(osd0_ctrl_main);
        //OSD_POST_RdFL(osd0_ctrl_hdr0);
        //OSD_POST_RdFL(osd0_ctrl_hdr1);
        //OSD_POST_RdFL(osd0_ctrl_hdr2);

        //OSD_POST_Wr01(osd0_ctrl_hdr0, osd_hdr_xpos, osd_hdr->osd_hdr_xpos);
        //OSD_POST_Wr01(osd0_ctrl_hdr0, osd_hdr_ypos, osd_hdr->osd_hdr_ypos);
        OSD_POST_Wr01(osd0_ctrl_hdr1, osd_hdr_w_mem, osd_hdr->osd_hdr_w_mem);
        OSD_POST_Wr01(osd0_ctrl_hdr1, osd_hdr_h_mem, osd_hdr->osd_hdr_h_mem);
        OSD_POST_Wr01(osd0_ctrl_hdr2, osd_hdr_w_out, osd_hdr->osd_hdr_w_mem);
        OSD_POST_Wr01(osd0_ctrl_hdr2, osd_hdr_h_out, osd_hdr->osd_hdr_h_mem);

        OSD_POST_Wr01(osd0_ctrl_main, osd_hdr_ready_flag, 0x1);
        //OSD_POST_WrFL(osd0_ctrl_hdr0);
        OSD_POST_WrFL(osd0_ctrl_hdr1);
        OSD_POST_WrFL(osd0_ctrl_hdr2);
        OSD_POST_WrFL(osd0_ctrl_main);
    }

    // flush OSD_PRE osd header
    for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
    {
        OSDX_DESC_T osdx_desc;

        xidx = xlst[i];

        FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_CTRL_MAIN);

        osdx_desc.osd_ctrl_main.osd_hdr_ready_flag = 1;

        FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_CTRL_MAIN);

        FBDEV_HW_NOTI("fb(%d) xidx=%d flush osd_hdr regs/data\n", fb_dev_id, xidx);
    }

func_exit:
    spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);
}

// OSD HW common header generator
//
// OSD HW header is made based on struct scanvas data and extra environment such as 3DOSD, reverse etc.
//
int FBDEV_O26_CMN_WriteOSDHeader(struct scanvas* pCanvas)
{
    int                     fb_dev_id;
    UINT32                  bitmap_ptr;
    FBDEV_PLT_OSD_HDR_T     osd_hdr;
    FBDEV_PLT_OSD_EXHDR_T   osd_exhdr;
    FBDEV_WIN_CTX_T*        wctx;
    struct scanvas          canvas;
    UINT32                  disp_width, disp_height;

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK,
                     "<i> fb(%d) user_initcall not ready +++\n", pCanvas->fb_dev_id);

    wctx = FBDEV_GetWinCtx(pCanvas->fb_dev_id);
    FBDEV_CHECK_CODE(NULL == wctx, return RET_ERROR,
                     "fb(%d) invalid winctx.\n", pCanvas->fb_dev_id);

    // fb(1) 이 소유권을 가지고 있는 경우에만 제어를 허용한다.
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        FBDEV_CHECK_CODE(hw_ctx->hw_osd0_owner != fb_dev_id,
                         return RET_ERROR,
                         "++ fb(%d) ignore. not hw_osd0_owner\n", fb_dev_id);
    }

    /* clear osd_hdr before writing */
    memset(&osd_hdr, 0x0, sizeof(FBDEV_PLT_OSD_HDR_T));
    memset(&osd_exhdr, 0x0, sizeof(FBDEV_PLT_OSD_EXHDR_T));
    memcpy(&canvas, pCanvas, sizeof(struct scanvas));

    fb_dev_id = canvas.fb_dev_id;
    disp_width = hw_ctx->hw_disp_width;
    disp_height = hw_ctx->hw_disp_height;

    // raxis.lim (2016/08/08) - if OSD is freezed, DO NOT handle/write any registers
    //
    // This patch seems to prevent OSD garbage during transition from non AFBC (boot logo) to AFBC (mercury/webOS) screen.
    // Originally, osd_hdr_flush is checked at FBDEV_O26_CMN_WriteHdrRegs().
    // I don't know the below code really prevents OSD garbage rather than the original policy.
    // <!> More tests are required.
    //
    if (!wctx->status.b_osd_hdr_flush)
    {
        int xidx, xnum, xlst[2];
        UINT32 disp_fbmem = 0x0;
        OSDX_DESC_T osdx_desc;

        xnum = FBDEV_O26_CMN_GetHWXList(fb_dev_id, xlst);
        xidx = xlst[0];

        if (!INVALID_XNUM(xnum))
        {
            FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_ALL);
            disp_fbmem = osdx_desc.osd_ctrl_hdr6.osd_hdr_ptr_bmp;

            FBDEV_WARN("fb(%d) freezed. osd_hdr_flush deferred & keep fbmem 0x%08x.", fb_dev_id, disp_fbmem);
        }

        return RET_OK;
    }

    switch (fb_dev_id)
    {
        case LX_FBDEV_ID_CSR0:
        {
            int csr_x_max;
            int csr_x_off, csr_y_off, csr_x_pos, csr_y_pos, csr_x_size, csr_y_size;
            int csr_disp_w, csr_disp_h;

#ifdef FBDEV_O26_USE_UNLIMITED_CURSOR_POSITION
            int csr_h_min_pxl = FBDEV_O26_BYTES_2_PIXEL(FBDEV_O26_GMAU_WORD_BYTES); /* 16 bytes -> 4 pixel */
#endif
            FBDEV_HW_NOTI("cursor_pos req(%d,%d)\n", canvas.output_win.x, canvas.output_win.y);

            // csr_disp_w is used to check if cursor is located at the right corner.
            // this value is set to 3840 in UHD mode, 1920 in FHD mode
            csr_disp_w = hw_ctx->hw_disp_width;
            csr_disp_h = hw_ctx->hw_disp_height;

            // if csr_hotspot is active, adjust (x,y) position of cursor layer.
            //
            // if cursor position is negative, I should move the bitmap address ( H/W doesn't accept negative position )
            //
            // IMPORTATNT !! if you change the base address, its alignment should be multiplt of 16 byte ( not 8 byte )
            // woonghyeon just said that it may be H/W bug (limitation?).
            // since we are using ARGB8888 pixel format for cursor OSD. cursor offset should be multiple of 4 pixel !!
            //
            csr_x_max = canvas.stride / FBDEV_O26_BITS_2_BYTES(canvas.bits_per_pixel);

            csr_x_off = 0;
            csr_y_off = 0;

            csr_x_pos = canvas.output_win.x - canvas.csr_hotspot.x;
            csr_y_pos = canvas.output_win.y - canvas.csr_hotspot.y;

            csr_x_size = canvas.input_win.w;
            csr_y_size = canvas.input_win.h;

            // HW 기준 커서 크기 x_size <= 2 인 조건이 되면 y_size 무관하게 mprotect error 발생함
            // (참고) y_size 값에 따라 mprotect error 발생 안할수도 있으나, 발생하는 것으로 처리하는것이 맞음
            // see http://hlm.lge.com/qi/browse/DITTEST-7421
            //
            // x_size 기준으로 최소값을 보장하여, mprotect error 회피하도록 조치함
            // 커서 크기는 짝수이므로, 최소 x_size 는 2 보다 큰 값이면 되므로 4 로 설정하면 됨
            //
            if (csr_x_size < 4)
            {
                FBDEV_WARN("fb(%d) too small cursor. csr_sz=%dx%d, hotspot=%dx%d, csr_pos=%d,%d\n",
                           fb_dev_id, csr_x_size, csr_y_size, canvas.csr_hotspot.x, canvas.csr_hotspot.y,
                           canvas.output_win.x, canvas.output_win.y);

                csr_x_size = 4;
            }

            FBDEV_HW_NOTI("fb(%d) pos %dx%d csr_sz %d,%d info( %dx%d h %d,%d ) max_x %d disp_x %d\n", fb_dev_id,
                          csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
                          canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y,
                          csr_x_max, csr_disp_w);

#ifdef FBDEV_O26_USE_UNLIMITED_CURSOR_POSITION

            // raxis.lim (2015/07/24)
            // if cursor is located at far left corner, we should try to show only minimum cursor viewing area.
            // as described above, minimum viewing area is 4 pixel.
            //
            // @note framebuffer address will be adjusted based on csr_x_off.
            if (csr_x_pos < -(csr_x_size - csr_h_min_pxl))
            {
                csr_x_off = (csr_x_max - csr_h_min_pxl);
                csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off, 2);

                csr_x_size = csr_h_min_pxl;
                csr_x_pos = 0;
            }
            else
#endif
            {

                // if cursor is at the left side, we calculate csr_x_pos and to change the frame buffer address
                // cursor viewing area should be shrinked by changing csr_x_size
                //
                // @note framebuffer address will be adjusted based on csr_x_off.
                if (csr_x_pos < 0)
                {
                    csr_x_off = -csr_x_pos;
                    csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off, 2);

                    csr_x_size -= csr_x_off;
                    csr_x_pos = 0;
                }
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
                csr_y_size -= csr_y_off;

                if (csr_y_size < FBDEV_O26_CSR_MIN_HEIGHT)
                {
                    csr_y_size = FBDEV_O26_CSR_MIN_HEIGHT;
                    csr_y_off  = csr_y_size - FBDEV_O26_CSR_MIN_HEIGHT;
                }
            }

            // prevent OSD garbage. effective cursor width should be less than the real surface width
            if (csr_x_size > csr_x_max) csr_x_size = csr_x_max;

            // if cursor is located at the right corner, I should gaurantee the minimal viewing area of cursor.
            // without it, cursor image will be broken :(
            // see the description for FBDEV_O26_CSR_MIN_WIDTH
            if (csr_x_pos + csr_x_size > csr_disp_w)
            {
                if (csr_x_pos > csr_disp_w - FBDEV_O26_CSR_MIN_WIDTH)
                {
                    csr_x_pos = csr_disp_w - FBDEV_O26_CSR_MIN_WIDTH;
                }

                csr_x_pos   = LX_CALC_ALIGNED_VALUE(csr_x_pos, 2);  /* make X pos is aligned by 4 */

                csr_x_size  = csr_disp_w - csr_x_pos;

                // software workaround for 1x cursor display on blend path
                // On blend path, cursor size should be displayed x2 automatically because OSD disp size is 3840x2160
                // and cursor region is set based on 1920x1080 area
                // if 2x scale up is not supported, I should multiply csr_x_size by double manually
                //
                // raxis.lim (2020/06/02)
                // DO NOT assume B.OSD path is always set to UHD display.
                // I should support FHD display on B.OSD path.
                // So I should check output display size regardless of osd path configuration.
                //if (hw_ctx->hw_wa_flag & FBDEV_O26_HW_WA_1X_CSR_DISP_ON_BLEND_PATH)
                {
                    if (FBDEV_O26_CMN_IsUHDDispMode())
                    {
                        csr_x_size *= 2;

                        if (csr_x_size > csr_x_max) csr_x_size = csr_x_max;
                    }
                }
            }

            // if cursor is located at the bottom corner, I should gaurantee the minimum viewing area, i.e 2 pixel
            if (csr_y_pos > csr_disp_h - FBDEV_O26_CSR_MIN_HEIGHT)
            {
                csr_y_pos = csr_disp_h - FBDEV_O26_CSR_MIN_HEIGHT;
            }

            // see http://clm.lge.com/issue/browse/SCDCR-6480
            csr_x_size &= 0xfffc;

            // NOTE that csr_x_pos, csr_y_pos, csr_x_size, csr_y_size is changed at the above corner checker.
            // if pos or size is set to wrong value, OSD HW will display the garbage screen.
            //
            osd_hdr.osd_hdr_xpos  = csr_x_pos;    /* output x (csr x pos) */
            osd_hdr.osd_hdr_ypos  = csr_y_pos;    /* output y (csr y pos) */
            osd_hdr.osd_hdr_w_mem = csr_x_size;   /* viewing cursor width */
            osd_hdr.osd_hdr_h_mem = csr_y_size;   /* viewing cursor height */
            osd_hdr.osd_hdr_w_out = csr_x_size;   /* output w */
            osd_hdr.osd_hdr_h_out = csr_y_size;   /* output h */

            // adjust framebuffer address if necessary
            // @note  gMAU requests 16byte aligned address
            bitmap_ptr = canvas.osd_bm_paddr;
            bitmap_ptr += (csr_y_off * canvas.stride) + FBDEV_O26_GMAU_ALIGNED_BYTES(csr_x_off * FBDEV_O26_BITS_2_BYTES(
                              canvas.bits_per_pixel));

            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl         = FBDEV_O26_BYTES_2_OSD_WORDS(canvas.stride);

            FBDEV_HW_NOTI("fb(%d) pos %dx%d csr_sz %d,%d <- req( %dx%d h %d,%d)\n", fb_dev_id,
                          csr_x_pos, csr_y_pos, csr_x_size, csr_y_size,
                          canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y);

            FBDEV_HW_NOTI("fb(%d) cursor pre-processing done\n", fb_dev_id);
        }
        break;

        // E-streamer 전용 가상 레이어
        //
        // 8K-Estreamer
        //  (1) 1024x4320 --> 960x2160 T/B 을 합성하여 1920x2160 생성함
        //  (2) 960x2160을 단순 복사하여 각각 L/R 이 되게하여 최종 3840x2160 4K OSD 만듦
        //  (3) 3840x2160 OSD 를 F22 OSD path 로 전송함
        //
        // (2021/10/01) http://clm.lge.com/issue/browse/SICDTV-10314
        // 과도한 OSD 의 DDR BW (2GB/s) 을 절감하고자 AFBC 포맷으로 변경함
        // 상세한 플로우는 SICDTV-10314 를 참조할것
        //
        //
        case LX_FBDEV_ID_OSD1:
        {
            //FBDEV_PLT_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_PLT_GET_EXT_RENDER_CTRL(hw_ctx);
            UINT32 fbmem_phys = canvas.osd_bm_paddr;

            // see http://jira.lge.com/issue/browse/SCDCR-7577
            if (hw_ctx->hw_fb1_width != canvas.input_win.w || hw_ctx->hw_fb1_height != canvas.input_win.h)
            {
                FBDEV_NOTI("fb(1) hw_fb1_width, hw_fb1_height changed %dx%d => %dx%d\n",
                           hw_ctx->hw_fb1_width, hw_ctx->hw_fb1_height,
                           canvas.input_win.w, canvas.input_win.h);

                hw_ctx->hw_fb1_width = canvas.input_win.w;
                hw_ctx->hw_fb1_height = canvas.input_win.h;
            }

            osd_hdr.osd_hdr_w_out = hw_ctx->hw_fb1_width;
            osd_hdr.osd_hdr_h_out = hw_ctx->hw_fb1_height;
            osd_hdr.osd_hdr_xpos = 0; //canvas.output_win.x;
            osd_hdr.osd_hdr_ypos = 0; //canvas.output_win.y;
            osd_hdr.osd_hdr_w_mem = canvas.input_win.w;
            osd_hdr.osd_hdr_h_mem = canvas.input_win.h;

            bitmap_ptr = fbmem_phys;
            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl = FBDEV_O26_BYTES_2_OSD_WORDS(canvas.stride);
        }
        break;

        case LX_FBDEV_ID_OSD0:
        default:
        {
            // 기본적으로 UI는 full screen 으로 설정되어야 함
            // PQE(orbit) 에 의항 제어되는 값이므로, 실제로 register 를 설정하진 않음
            canvas.output_win.w = disp_width;
            canvas.output_win.h = disp_height;

            if (canvas.input_win.w > disp_width)    canvas.input_win.w = disp_width;

            if (canvas.input_win.h > disp_height)   canvas.input_win.h = disp_height;

            if (canvas.output_win.w > disp_width)   canvas.output_win.w = disp_width;

            if (canvas.output_win.h > disp_height)  canvas.output_win.h = disp_height;


            // raixs.lim (2017/08/25)
            // support user defined output win for debug. invalid config might make OSD corruption
            if (canvas.test_output_win.w && canvas.test_output_win.h)
            {
                FBDEV_HW_NOTI("++ user output used (%d,%d)\n", canvas.test_output_win.w, canvas.test_output_win.h);
                memcpy(&canvas.output_win, &canvas.test_output_win, sizeof(LX_RECT_T));
            }

            // raxis.lim (2015/01/12) -- handle odd width
            // OSD doesn't support odd number as output width. so let's make it to even number
            if (canvas.output_win.w & 0x1)
            {
                FBDEV_HW_NOTI("fb(%d) convert odd out_w %d to %d\n", fb_dev_id, canvas.output_win.w,
                              canvas.output_win.w & 0xfffffffe);
                canvas.output_win.w &= 0xfffffffe;
            }

            // NOTE - CLUT processing is not processed anymore inside kdriver
            osd_hdr.osd_hdr_color_key_en = canvas.color_key_en;

            osd_hdr.osd_hdr_w_out = canvas.output_win.w;  /* output w */
            osd_hdr.osd_hdr_h_out = canvas.output_win.h;  /* output h */
            osd_hdr.osd_hdr_xpos  = canvas.output_win.x;  /* output x */
            osd_hdr.osd_hdr_ypos  = canvas.output_win.y;  /* output y */
            osd_hdr.osd_hdr_w_mem = canvas.input_win.w;   /* input w  */
            osd_hdr.osd_hdr_h_mem = canvas.input_win.h;   /* input h  */
            bitmap_ptr            = canvas.osd_bm_paddr;

            // modify bitmap ptr for input position is provided
            if (canvas.input_win.x > 0 || canvas.input_win.y > 0)
            {
                FBDEV_HW_NOTI("fb(%d) bitmap based moved ! by %d,%d\n", fb_dev_id, canvas.input_win.x, canvas.input_win.y);

                // gMAU requests 16byte aligned address
                bitmap_ptr += canvas.input_win.y * canvas.stride;
                bitmap_ptr += FBDEV_O26_GMAU_ALIGNED_BYTES(FBDEV_O26_BITS_2_BYTES(canvas.input_win.x * canvas.bits_per_pixel));
            }

            FBDEV_HW_NOTI("fb(%d) bitmap hwparam (%d,%d,%d,%d)(%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x, pixel_format=%d\n",
                          fb_dev_id,
                          canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
                          canvas.output_win.x, canvas.output_win.y, canvas.output_win.w, canvas.output_win.h,
                          canvas.stride, bitmap_ptr, canvas.fbc_fmt, canvas.pixel_format);

            osd_hdr.osd_hdr_pixel_order = canvas.pixel_order_en;
            osd_hdr.osd_hdr_wpl         = FBDEV_O26_BYTES_2_OSD_WORDS(canvas.stride);

            // pixel format changed
            if (canvas.pixel_format != LX_FBDEV_PIXEL_FORMAT_NOT_DEFINED &&
                    canvas.pixel_format != canvas.pixel_format_current)
            {
                OSDX_DESC_T osdx_desc;

                int xnum, xlst[2];
                int i;

                xnum = FBDEV_O26_CMN_GetHWXList(fb_dev_id, xlst);

                for (i = 0; i < xnum; i++)
                {
                    int xidx = xlst[i];

                    FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_PDEC);

                    if (canvas.pixel_format == LX_FBDEV_PIXEL_FORMAT_RGB_8888)
                    {
                        osdx_desc.osd_ctrl_pdec.osd_ch_alpha = 0x0;
                        osdx_desc.osd_ctrl_pdec.osd_ch_red = 0x1;
                        osdx_desc.osd_ctrl_pdec.osd_ch_green = 0x2;
                        osdx_desc.osd_ctrl_pdec.osd_ch_blue = 0x3;
                    }
                    else if (canvas.pixel_format == LX_FBDEV_PIXEL_FORMAT_BGR_8888)
                    {
                        osdx_desc.osd_ctrl_pdec.osd_ch_alpha = 0x0;
                        osdx_desc.osd_ctrl_pdec.osd_ch_red = 0x3;
                        osdx_desc.osd_ctrl_pdec.osd_ch_green = 0x2;
                        osdx_desc.osd_ctrl_pdec.osd_ch_blue = 0x1;
                    }

                    FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_PDEC);
                }

                canvas.pixel_format_current = canvas.pixel_format;
            }
        }
        break;
    }

    // copy common attribute
    osd_hdr.osd_hdr_format          = FBDEV_GetOSDPxlFmt(canvas.bits_per_pixel);
    osd_hdr.osd_hdr_depth           = FBDEV_GetOSDPxlDepth(canvas.bits_per_pixel);

    osd_hdr.osd_hdr_global_alpha_en = (canvas.user_global_alpha_en) ? 0x1 : canvas.global_alpha_en;
    osd_hdr.osd_hdr_global_alpha    = (canvas.user_global_alpha_en) ? canvas.user_global_alpha : canvas.global_alpha;
    osd_hdr.osd_hdr_color_key       = canvas.color_key;

    osd_hdr.osd_hdr_ptr_bmp         = bitmap_ptr;
#ifndef FIXED_BASE_ADDR
    osd_hdr.osd_hdr_ptr_plte        = wctx->osd_plte_base_phys;
#endif

    // NOTE - virtual OSD is not processed anymore inside kdriver

    // handle S3D if requested

    // TOOD: add extra handleer if necessary.

    FBDEV_HW_NOTI("fb(%d) bitmap hwparam (%d,%d,%d,%d)(%d,%d,%d,%d) stride=%d fbmem=0x%08x fbc=0x%x (final)\n",
                  fb_dev_id,
                  canvas.input_win.x, canvas.input_win.y, canvas.input_win.w, canvas.input_win.h,
                  canvas.output_win.x, canvas.output_win.y, canvas.output_win.w, canvas.output_win.h,
                  canvas.stride, bitmap_ptr, canvas.fbc_fmt);

    // save osd header
    memcpy(&hw_ctx->osd_hdr_sav[fb_dev_id], &osd_hdr, sizeof(FBDEV_PLT_OSD_HDR_T));

    // raxis.lim (2019/05/21)
    //
    // I don't care here whether two POSDs sare necessary or not. refer to FBDEV_O26_CMN_WriteHdrRegs()
    //
    osd_exhdr.bits_per_pixel = canvas.bits_per_pixel;
    osd_exhdr.img_stride    = canvas.stride;
    osd_exhdr.img_height    = osd_hdr.osd_hdr_h_mem;    /* 이 값이 맞나 몰라 */

    // fb(0) 과 fb(1) 이 같은 OSD HW 리소스를 사용하므로, owner만 레지스터를 쓰도록 조치함
    // 중요 상태이므로 noti 레벨로 출력함
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && hw_ctx->hw_osd0_owner != LX_FBDEV_ID_OSD0)
    {
        FBDEV_NOTI("fb(%d) is not osd0 owner, ignore\n", fb_dev_id);
        return RET_OK;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->hw_osd0_owner != LX_FBDEV_ID_OSD1)
    {
        FBDEV_NOTI("fb(%d) is not osd0 owner, ignore\n", fb_dev_id);
        return RET_OK;
    }

    FBDEV_O26_CMN_WriteHdrRegs(fb_dev_id, &osd_hdr, &osd_exhdr);

    // do somthing if necessary

    // (re)enable PQEFW_OSD0_OUT_CTRL. this is called during cold boot, snapshot boot & instant-boot resume
    if (fb_dev_id == LX_FBDEV_ID_OSD0)
    {
        // INT_FRC or NO_FRC
        if (!(hw_ctx->hw_wa_flag & FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL))
        {
            hw_ctx->hw_wa_flag |= FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL;
            FBDEV_NOTI("PQEFW_OSD0_OUT_CTRL enabled\n");
        }
    }

    // see http://clm.lge.com/issue/browse/AVTASK-640
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        FBDEV_HW_CMD_DATA_T hw_cmd;

        hw_cmd.gen[0] = fb_dev_id;
        hw_cmd.gen[1] = osd_hdr.osd_hdr_ptr_bmp;
        hw_cmd.gen[2] = wctx->pixel.output_win.x;
        hw_cmd.gen[3] = wctx->pixel.output_win.y;

        (void)FBDEV_ExecHWCommand(FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE, &hw_cmd);
    }

    return RET_OK;
}

/*========================================================================================
    Implementation Group
========================================================================================*/
// OSD HW Layer enable/disable
//
// @param   fb_dev_id [IN] fbdev ID
//
//          enable : 0 : display off , 1 : display on
// @return  int 0 : OK , -1 : NOT OK
//
//
int FBDEV_O26_CMN_SetOSDEnable(int fb_dev_id, int enable)
{
    int     i;
    int     xidx;
    int     xnum, xlst[2], afbc_xlst[2];
    int     hw_state;
    UINT32  val = 0x0;
    UINT32  hw_osd0_owner;

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();
    //FBDEV_PLT_GLB_CTRL_T* glb_ctrl = FBDEV_PLT_GET_GLB_CTRL(hw_ctx);
    FBDEV_PLT_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_PLT_GET_EXT_RENDER_CTRL(hw_ctx);

    FBDEV_CHECK_NOTI(!hw_ctx->user_initcall_ctrl.ready, return RET_OK, "<i> user_initcall not ready +++\n");

    // fb(0) 와 fb(1) 간의 hw owner 가 변경시 FRC(F22) 에서 특수 처리가 들어거야 하므로,
    // 이에 준하여 같이 동작할 수 있도록 한다.
    // EST 의 on/off 에 대하여 IPC 전송후 16.7 ms 의 수신 보장을 해주어야 한다.
    // http://clm.lge.com/issue/browse/AVTASK-640?focusedCommentId=3226339&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3226339
    hw_osd0_owner = hw_ctx->hw_osd0_owner;

    xnum = FBDEV_O26_CMN_GetHWXListEx(fb_dev_id, xlst, afbc_xlst);
    // ignore noisy warning msg becase some OSD layer is not supported by HW
    FBDEV_CHECK_DEBUG(INVALID_XNUM(xnum), return RET_ERROR, "invalid fb(%d)\n", fb_dev_id);

    val = (enable) ? 0x1 : 0x0;
    FBDEV_HW_DEBUG("fb(%d) xlst=(%d,%d) view = <%s>\n", fb_dev_id, xlst[0], xlst[1], (enable) ? "on" : "off");

    hw_state = FBDEV_O26_CMN_GetOSDEnable(fb_dev_id);
    FBDEV_NOTI("fb(%d) hw_state=%s, req=%s, action=%s\n", fb_dev_id,
               (hw_state) ? "on" : "off",
               (enable) ? "on" : "off",
               "continue");

    // 시스템 부팅 초기에는 HW on 상태일 수 있지만, 실제 OSD 셋업을 마무리 하기 위해서는 같은 상태라도
    // 이후 과정을 계속 진행하도록 하는것이 안전하다.
    // 참고로 O26 에서는 OSD off 상태로 시작하기 때문에 아래 체커 있는 것이 더 낫지만,
    // 기존 O26 과의 코드 싱크를 맞추기 위하여, O26 처럼 체커 삭제조치한다.
#if 0

    if (enable == hw_state)
    {
        return RET_OK;
    }

#endif

#if 0

    if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->b_support_ext_render == false)
    {
        FBDEV_NOTI("++ fb(%d) %s ignore. ext_render disabled\n", fb_dev_id, (enable) ? "on" : "off");
        return RET_OK;
    }

#endif

    // (2021/12/04) http://hlm.lge.com/qi/browse/QEVENTTWT-8589
    // LSM 에서 TV 시작시에  fb(0) 과 fb(1) 에 대한 XOR 동작성을 위배하고 있음
    // 드라이버에서는 fb(0) 에 우선 순위를 두고, fb(1) 에 대한 on/off 을 거부할 수 있음
    if (fb_dev_id == LX_FBDEV_ID_OSD1 && FBDEV_O26_CMN_GetOSDEnable(LX_FBDEV_ID_OSD0))
    {
        FBDEV_NOTI("++ fb(%d) %s ignore. fb(0) is already enabled\n", fb_dev_id, (enable) ? "on" : "off");
        return RET_OK;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        if (enable)
        {
            // (2021/08/04) see http://clm.lge.com/issue/browse/SICDTV-10200
            // 플랫폼에서 무의미한 fb(1) 렌더링이 존재하기 때문에, fbmem 의 동적 할당 위치를 변경한다.
            //
            // AS-IS: 렌더링 직전
            // TO_BE: OSD On 초기
            //
            // As-IS 상황에서는 fbmem 이 할당되기만 하고, 해제 조건(OSD off) 이 발동되지 않기 때문에,
            // 불필요하게 메모리를 할당받는 상태가 된다.
            //
            FBDEV_O26_CMN_AllocExternalRendererFrameBuffer();

            // (2020/10/16) Estreamer 동작전에 cursor 를 강제로 off 시킴
            // see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
            if (FBDEV_O26_CMN_GetOSDEnable(LX_FBDEV_ID_CSR0))
            {
                OSD_POST_RdFL(csr0_ctrl_sync0);
                OSD_POST_Wr01(csr0_ctrl_sync0, osd_sync_enable, 0x0);
                OSD_POST_WrFL(csr0_ctrl_sync0);

                FBDEV_NOTI("++ set cursor invisible (sync.en=0) when EXT_RENDER is shown\n");
            }
        }

        // (2021/07/05)
        // fb(1) 은 실제 FB(0) 과 동일한 HW 를 사용하고 있어, 기존 E60 과 다른 플로우를 타야 한다.
        // fb(1) 에 대한 on/off 는 F22 에 즉시 리포트가 되어야 한다.
        ext_render_ctrl->hwparam.enable = enable;
        FBDEV_NOTI("fb(%d) ext_render(e-streamer render) enable=%d\n", fb_dev_id, ext_render_ctrl->hwparam.enable);

#ifdef FBDEV_O26_USE_EXT_RENDERER_IPC

        if (FBDEV_OSD_EXT_RENDER_REG_BASE)
        {
            FBDEV_HW_NOTI("++ write external render 0x%08x=0x%08x enable=0x%x\n",
                          FBDEV_OSD_EXT_RENDER_REG_BASE + 0x0,
                          ext_render_ctrl->hwparam.command,
                          enable);

            OS_WrReg(FBDEV_OSD_EXT_RENDER_REG_BASE + 0x0, ext_render_ctrl->hwparam.command);
        }

#endif

        // (2023/11/06) OSD ON 시의 PQE notify 코드로 통합함. 아래 코드 블럭 참조
#if 0
        // see SICDTV-8491 : report estreamer visibility
        hw_ctx->user_initcall_ctrl.status.osd_estreamer = enable;
        FBDEV_O26_CMN_NotifyPQEDriver();
#endif

        // (2023/07/21)
        // F22 상태 변화 (가비지 제거) 등은 F22 에서 처리토록 하며, OSD kdriver 는 대기하지 않도록 한다.
        // OSD on/off 관련하여 불필요한 sleep 을 제거하기 위함이다.
#if 0

        // F22 이 상태 변경을 수신하기 까지 1 frame 정도 대기한다.
        if (!osd_hw_pm_suspend_stage)
        {
            usleep_range(16700, 16700);
        }

#endif
    }

    // see http://clm.lge.com/issue/browse/SCDCR-6376
    //
    // (추가) UI on/off 디버그 경우에 EST flag 가 제대로 전달되지 못하게 되므로, UI on 시에 EST flag
    // 가 켜져 있다면, 끌 수 있도록 조치한다.
    //
    // (2023/08/09) http://hlm.lge.com/qi/browse/DITTEST-3706 분석 과정에서 UI on/off 에 대한 처리는
    // 실제 OSD 가 on 되기 직전에 수행되어야 함. 이에 실행 위치를 이동함.
    //
    // (2023/11/06) PQE FW 와 E-streamer flag 동기화는 fb(1) ON 상태 한정으로 이동시킴.
    // 그외의 경우에는 E-Streamer flag off 상태로 리포트 하는것이 안정적이다.
    //
    if ((fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1) && enable)
    {
        int pqe_fw_estreamer_flag = 0;
        //LX_RECT_T crop_rgn;

        if (fb_dev_id == LX_FBDEV_ID_OSD0)
        {
            pqe_fw_estreamer_flag = 0;
        }
        else
        {
            pqe_fw_estreamer_flag = 1;
        }

        hw_ctx->user_initcall_ctrl.status.osd_estreamer = pqe_fw_estreamer_flag;
        FBDEV_O26_CMN_NotifyPQEDriver();

        FBDEV_NOTI("fb(%d) on. notify PQE to ready estreamer <%s>\n",
                   fb_dev_id, pqe_fw_estreamer_flag ? "on" : "off");

        FBDEV_O26_CMN_WaitPQEDriverEstreamerSync(pqe_fw_estreamer_flag);

        //crop_rgn.x = 0;
        //crop_rgn.y = 0;
        //crop_rgn.w = hw_ctx->hw_fb0_width;
        //crop_rgn.h = hw_ctx->hw_fb0_height;

        //FBDEV_O26_CMN_SetOutputCropRegion(false, hw_ctx->hw_fb0_width, hw_ctx->hw_fb0_height, 0, 0, &crop_rgn);
    }

    // 실제 OSD plane 에 대한 on/off 가 아래 코드 수행후 다음 vsync 이후에 반영이 될 것이다.
    // GLB 체제로 바뀐 일반 OSD path 의 경우:
    //
    // OSD0/1의 경우 OSD_PRE 의 osd_ctrl_mai.osd_en 을 설정한다.
    // 또한 GLB 의 각 layer 설정을 한후, FBDEV_O26_CMN_SetupGLB() 을 호출해 주어야 한다.
    //
    // 커서의 경우:
    // 기존 구현 동일 하게 osd_ctrl_main 와 osd_ctrl_sync 로 제어한다.
    for (i = 0; i < xnum; i++)
    {
        OSDX_DESC_T osdx_desc;
        xidx = xlst[i];
        FBDEV_CHECK_CODE(INVALID_XIDX(xlst[i]), return false, "fb(%d) invalid xidx %d\n", fb_dev_id, xlst[i]);

        FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_CTRL_MAIN | OSDX_DESC_FLAG_SYNC_0);

        osdx_desc.osd_ctrl_main.osd_en = val;
        osdx_desc.osd_ctrl_sync0.osd_sync_enable = val;

        // (2021/07/013)
        // 만약 E-streamer 동작중 cursor ON 요청이 온다고 가정하면, 실제 화면에 보이면 안된다.
        // 커서 클릭에 의하여 EST Off, UI On 상황이 된다고 해도 첫번째 요청인 CSR ON 요청은 잠시
        // ignore 처리해야 한다.
        //
        // (2022/04/21)
        // 4K E-streamer 제공 필요에 따라, E-stramer ON 체크시에 외부 FRC 여부는 보지 않도록 한다.
        if (fb_dev_id == LX_FBDEV_ID_CSR0 && enable)
        {
            if (FBDEV_O26_CMN_GetOSDEnable(LX_FBDEV_ID_OSD1))
            {
                osdx_desc.osd_ctrl_sync0.osd_sync_enable = val;
                FBDEV_NOTI("++ set cursor invisible (sync.en=0) when EXT_RENDER is shown\n");
            }
        }

        FBDEV_O26_CMN_WriteOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_CTRL_MAIN | OSDX_DESC_FLAG_SYNC_0);

#ifdef USE_GLB_PATH_CTRL

        // (2025/04/24) graphic layer 의 경우 GLB 에 의한 제어를 추가해 줘야 함
        if (fb_dev_id != LX_FBDEV_ID_CSR0)
        {
            glb_ctrl->mux[xidx].osd_en = val;

            FBDEV_NOTI("fb(%d) GLB, set_path_enable xidx=%d, en=%d\n", fb_dev_id, xidx, val);
            FBDEV_O26_CMN_SetupGLB();
        }

#endif
    }

    FBDEV_NOTI("fb(%d) osd_ctrl_main, osd_ctrl_sync configured\n", fb_dev_id);

    // 이하 코드는 OSD plane 에 대한 on/off 에 연속하거나, 그 이후에 수행되어야 하는 부가적인 SW WA 들의 연속이다.
    // 만약 OSD on 동작이라면 아래 코드에서 AFBC 설정 등 연속으로 이어져야 하는 부분이 있으므로, 절대로 sleep 이
    // 있어서는 안된다.
    // 단 OSD off 동작의 경우라면 그 이후의 상태 변화에 맞게 출력의 안정성 고려하여 sleep 동작을 추가할 수 있다.

    // (2023/07/21)
    // UI off 시의 sleep 부분은 4K E-streamer 지원 부분 코드와 통합한다.
    // 즉 EST off, UI off 시의 2 vsync sleep 코드가 추가되어, 아래 sleep 은 무의미하다.
    //
    // see http://clm.lge.com/issue/browse/SICDTV-13023
#if 0

    // raixs.lim (2021/06/01) E60 의 상황을 참조하여, O26+F22 의 경우를 미리 대비함.
    //
    // (2020/11/17) http://clm.lge.com/issue/browse/SICDTV-8986, QEVENTTWON-8969
    // OSD off 과정에서 20% 의 확률로 화면 우측에서의 과도 (가비지) 출력 현상 있음
    // OSD off 과정에서 실제 OSD 출력을 끊고, 후속 조치(AFBC 중지 등)이 진행되도록 함
    //
    // (NOTE) O26 에서 아래 코드가 반드시 필요할지에 대하여 검증이 필요하다.
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && !enable)
    {
        if (!osd_hw_pm_suspend_stage)
        {
            usleep_range(16700, 16700);
        }
    }

#endif

    // (2021/07/05) OSD0 HW 에 대한 소유권을 설정한다.
    // fb(0) 을 최우선으로 우대하는 정책을 사용할 것이며,fb(1) 의 소유권은 필요한 순간에만 설정한다.
    //
    // (2021/08/04) http://clm.lge.com/issue/browse/SICDTV-10200
    // owner 교체와 신규 owner 에대한 re-draw 과정을 실제 OSD HW on/off 전으로 이동시킨다.
    // 즉 새로운 OSD 가 ON 되었을때, 이전 owner 의 화면이 나가지 않도록 조치한다.
    //
    // 아래 코드 흐름은 fb(0) off 상태에서 fb(1) on 상태로 최대한 수무드하게 전환하는 것을 목적으로 한다.
    //
    // 참고로 fb(1) off 상태에서는 이미 F22 에서 OSD 출력을 끊어 버렸고, 최소 10 frame drop 모드에 있기 때문에
    // owner 변경에 의한 fb(0) 순간 화면이 나올 수 있나 관점에서는. 절대로 그럴 수 없다.
    //
    if (fb_dev_id == LX_FBDEV_ID_OSD1)
    {
        hw_ctx->hw_osd0_owner = (enable) ? LX_FBDEV_ID_OSD1 : LX_FBDEV_ID_OSD0;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD0 && enable)
    {
        hw_ctx->hw_osd0_owner = LX_FBDEV_ID_OSD0;
    }

    // osd0_hw_owner 변경시 추후 ON 상황에 대비하여, 이전 fb 의 사용 흔적을 지워져야 한다.
    // 즉 새로운 osd0_hw_owner 가 OSD path 를 흘러갈 수 있도록 조치한다.
    //
    // 다시 그림을 그린다고 해도, 이전 프레임 정보가 F22 쪽으로 흘러갈 수 있다.
    // 따라서 F22 에서는 OSD on/off 상태가 바뀌는 경우 일정 frame 을 ignore 처리하도록 설정해야 한다.
    // 현재는 약 10 frame 정보를 ignore 처리한다고 한다.
    // see http://clm.lge.com/issue/browse/AVTASK-640
    //
    // (2023/03/28) 4K-Estreamer 스펙에 따른 고려 사항
    // see http://clm.lge.com/issue/browse/SCDCR-5906
    //
    // (1) 4K-Estreamer 모드에서 UI 로 제어권이 넘어왔을때, 출력 해상도 값을 복원해야 한다.
    // 간단한 방법으로 PQEFW 제어를 1회 off 설정 + OSD header 강제 업데이트 요청 조치한다.
    //
    // (2) 4K-Estreamer 에서 hw_osd0 의 주인이 바뀌는 순간 crop 영역 정보를 초기화 해주어야 한다.
    // 특히 4K-Estreamer 모드에서 UI 로 전환시 crop 을 UI 에 맞도록 재설정 해주지 않으면,
    // crop 된 상태로 UI 가 출력되어 이상하게 보인다.
    //
    // 주인이 E-Streamer 로 바뀔때도 512x2160 기본 crop 모드를 먼저 활성화 조치한다. (nice to have)
    //
    // (2023/07/24) 4K OLED E-Streamer 지원에 따른 정책 수정
    // hw_osd0_owner 변경에 따라 필요시 화면 업데이트는 변함이 없으나,
    // crop region 업데이트는 osd off 에서만 진행하도록 수정한다.
    //
    if (hw_osd0_owner != hw_ctx->hw_osd0_owner)
    {
        struct scanvas* hw_osd0_owner_canvas = FBDEV_GetWinCanvas(hw_ctx->hw_osd0_owner);

        FBDEV_NOTI("++ hw_osd0_owner changed by fb(%d).%s\n", fb_dev_id, (enable) ? "enable" : "disable");

        if (hw_ctx->b_support_fb1 && !hw_ctx->b_support_ext_render)
        {
            int fb_width;
            int fb_height;
            LX_RECT_T crop_rgn;
            //FBDEV_PLT_EXT_RENDER_CTRL_T* ext_render_ctrl = FBDEV_PLT_GET_EXT_RENDER_CTRL(hw_ctx);

            FBDEV_NOTI("++ make fb(%d) default crop region by hw_osd0_owner change\n", hw_ctx->hw_osd0_owner);

            if (hw_ctx->hw_osd0_owner == LX_FBDEV_ID_OSD0)
            {
                fb_width = hw_ctx->hw_fb0_width;
                fb_height = hw_ctx->hw_fb0_height;
            }
            else
            {
                fb_width = hw_ctx->hw_fb1_width;
                fb_height = hw_ctx->hw_fb1_height;
            }

            crop_rgn.x = 0;
            crop_rgn.y = 0;
            crop_rgn.w = fb_width;
            crop_rgn.h = fb_height;

            ext_render_ctrl->hwparam.xoffset = 0;
            ext_render_ctrl->hwparam.yoffset = 0;
            ext_render_ctrl->hwparam.crop_x  = 0;
            ext_render_ctrl->hwparam.crop_y  = 0;
            ext_render_ctrl->hwparam.crop_w  = fb_width;
            ext_render_ctrl->hwparam.crop_h  = fb_height;

            FBDEV_O26_CMN_SetOutputCropRegion(false, fb_width, fb_height, 0, 0, &crop_rgn);
        }

        if (hw_osd0_owner_canvas)
        {
            if (hw_ctx->hw_osd0_owner == LX_FBDEV_ID_OSD0 && !hw_ctx->b_support_ext_render)
            {
                FBDEV_NOTI("++ disable PQEFW_OSD0_OUT_CTRL temporarily\n");
                hw_ctx->hw_wa_flag &= ~FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL;
            }

            FBDEV_NOTI("++ write fb(%d) header immediately\n", hw_ctx->hw_osd0_owner);
            FBDEV_O26_CMN_WriteOSDHeader(hw_osd0_owner_canvas);
        }
    }

    // raxis.lim (2019/10/08) -- enable/disable afbc reader if necessary
    //
    // OSD reader is configured to AFBC mode not MIF, CCO0/CCO1 will read something even though OSD is off state.
    // So we should control afbc(x)_init_en, afbc(x)_auto_init_en flag
    // refer to http://clm.lge.com/issue/browse/AVTASK-401
    //
#ifdef FBDEV_O26_USE_AFBC_READ_BW_SAVING
    {
        int afrc_status = FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_AFRC, fb_dev_id);

        GSC_CTRL_RdFL(ctrl_auto_init_afbc1);

        FBDEV_HW_NOTI("fb(%d) fbc=%s, enable=%d\n",
                      fb_dev_id, afrc_status ? "afrc" : "afbc", enable);

        if (afbc_xlst[0] == 2 || afbc_xlst[1] == 2)
        {
            GSC_CTRL_Wr01(ctrl_auto_init_afbc1, reg_afbc2_init_en, enable);
            GSC_CTRL_Wr01(ctrl_auto_init_afbc1, reg_afbc2_auto_init_en, enable);
        }

        if (afbc_xlst[0] == 3 || afbc_xlst[1] == 3)
        {
            GSC_CTRL_Wr01(ctrl_auto_init_afbc1, reg_afbc3_init_en, 0x1);
            GSC_CTRL_Wr01(ctrl_auto_init_afbc1, reg_afbc3_auto_init_en, 0x1);
        }

        GSC_CTRL_WrFL(ctrl_auto_init_afbc1);
    }
#endif

    // (2020/10/16)  Estreamer 동작 종료후, UI 가 켜질때 cursor 를 복구시킬 수 있도록 함
    // see http://clm.lge.com/issue/browse/SICDTV-8669?focusedCommentId=2657619&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2657619
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && enable && FBDEV_O26_CMN_GetOSDEnable(LX_FBDEV_ID_CSR0))
    {
        OSD_POST_RdFL(csr0_ctrl_sync0);
        OSD_POST_Wr01(csr0_ctrl_sync0, osd_sync_enable, 0x1);
        OSD_POST_WrFL(csr0_ctrl_sync0);

        FBDEV_NOTI("++ set cursor visible (sync.en=1) when UI is shown\n");
    }

#if 0

    // (2023/03/28) 4K-Estreamer 모드에서 UI 가 enable 될때, 원래 4K output_win 설정을 복원해 줘야 한다.
    // 간단한 방법으로 PQEFW 제어를 잠시 off 설정 + OSD 강제 업데이트 요청 조치한다.
    if (fb_dev_id == LX_FBDEV_ID_OSD0 && enable && !hw_ctx->b_support_ext_render)
    {
        struct scanvas* canvas = FBDEV_GetWinCanvas(fb_dev_id);

        if (canvas)
        {
            hw_ctx->hw_wa_flag &= ~FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL;

            FBDEV_O26_CMN_WriteOSDHeader(canvas);
        }
    }

#endif

    // (2023/07/21) 4k E-Streamer 제어 관련 추가
    //
    // UI off 시에 PQE FW 로 estreamer 시작을 준비할 수 있도록 한다.
    // EST off 시에 PQE Fw 로 estreamer 종료를 준비할 수 있도록 한다.
    // 2 vsync 만큼의 안정화 기간을 보장할 수 있도록 한다.
    //
    // (note) 8K 60Hz 까지 고려하여 2 vsync = 33.3 ms sleep 추가한다. 4K 120Hz 기준 4 vsync 에 해당하는
    // 긴 시간이지만 큰 값이 아니다. 추후 필요시 vsync 주기 고려하여 수정하도록 한다.
    //
    // see http://clm.lge.com/issue/browse/SCDCR-6376
    //
    // (추가) UI on/off 디버그 경우에 EST flag 가 제대로 전달되지 못하게 되므로, UI on 시에 EST flag
    // 가 켜져 있다면, 끌 수 있도록 조치한다.
    //
    // (2023/08/09) http://hlm.lge.com/qi/browse/DITTEST-3706 분석 과정에서 UI on/off 에 대한 처리는
    // 실제 OSD 가 on 되기 직전에 수행되어야 함. 이에 위치를 앞 부분으로 이동함.
    //
    // (2023/11/06) PQE FW 와 E-streamer flag 동기화는 fb(1) ON 상태 한정으로 이동시킴.
    // 그외의 경우에는 E-Streamer flag off 상태로 리포트 하는것이 안정적이다.
    //
    if ((fb_dev_id == LX_FBDEV_ID_OSD0 || fb_dev_id == LX_FBDEV_ID_OSD1) && !enable)
    {
        int pqe_fw_estreamer_flag = 0; // 고정값 0

        hw_ctx->user_initcall_ctrl.status.osd_estreamer = pqe_fw_estreamer_flag;
        FBDEV_O26_CMN_NotifyPQEDriver();

        FBDEV_NOTI("fb(%d) off. notify PQE to ready estreamer <%s>\n",
                   fb_dev_id, pqe_fw_estreamer_flag ? "on" : "off");

        FBDEV_O26_CMN_WaitPQEDriverEstreamerSync(pqe_fw_estreamer_flag);
    }


    // 메모리절감을 통해서 fb(1) 이 off 되면, 즉시 IPC용 framebuffer 를 제거하도록 하자.
    if (fb_dev_id == LX_FBDEV_ID_OSD1 && !enable)
    {
        FBDEV_O26_CMN_DestroyExternalRendererFrameBuffer();
    }

    return RET_OK;
}

// fb layer 의 visible 상태를 확인한다.
// 실제 레지스터를 확인한다.
// UI 와 E-Streamer 공용을 가정하고 있으므로, 소유자 유무에 따라 강제로 off 를 리턴할 수도 있다.
//
// 일반 OSD layer 의 경우 GLB 설정값을 읽어야 한다.
// 커서의 경우 기존 처럼 osd_ctrl_main 설정값을 읽어야 한다.
//
// visible 상태이면 1, 아니면 0 을 리턴한다.
//
int FBDEV_O26_CMN_GetOSDEnable(int fb_dev_id)
{
    OSDX_DESC_T osdx_desc;
    UINT32 val;
    int xidx;
    int xnum, xlst[2];

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

    xnum = FBDEV_O26_CMN_GetHWXList(fb_dev_id, xlst);

    // ignore noisy warning msg becase some OSD layer is not supported by HW
    if (INVALID_XNUM(xnum)) return false;

    // raxis.lim (2019/05/21) -- event though OSD requires two POSD for 4K display, we can just check the first POSD value
    xidx = xlst[0];
    FBDEV_CHECK_CODE(INVALID_XIDX(xidx), return false, "fb(%d) invalid xidx=%d\n", fb_dev_id, xidx);

    FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_CTRL_MAIN);
    val = osdx_desc.osd_ctrl_main.osd_en;

    if (fb_dev_id == LX_FBDEV_ID_OSD0 && hw_ctx->hw_osd0_owner != LX_FBDEV_ID_OSD0)
    {
        FBDEV_HW_NOTI("fb(%d) not osd0_ownwer. real=%d, ret=%d\n", fb_dev_id, val, 0);
        val = 0;
    }

    if (fb_dev_id == LX_FBDEV_ID_OSD1 && hw_ctx->hw_osd0_owner != LX_FBDEV_ID_OSD1)
    {
        FBDEV_HW_NOTI("fb(%d) not osd0_ownwer. real=%d, ret=%d\n", fb_dev_id, val, 0);
        val = 0;
    }

    return val;
}

/*========================================================================================
    Implementation Group (DIAG/PROC)
========================================================================================*/

// HW diagnostics
//
// dump important paramters and valiate settings. this function will help to view HW status
// (usage) cat /proc/lg/fbdev/chip/diag
//
void FBDEV_O26_CMN_DiagHW(struct seq_file* m)
{
    UINT32 val;

    int xidx;
    int xnum, xlst[2];
    OSDX_DESC_T osdx_desc;
    int fb_dev_id = LX_FBDEV_ID_OSD0;

    FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

    xnum = FBDEV_O26_CMN_GetHWXList(fb_dev_id, xlst);
    FBDEV_CHECK_CODE(INVALID_XNUM(xnum), return, "invalid fb(%d)\n", fb_dev_id);
    xidx = xlst[0];

    /* print HW core info */
    {
        seq_printf(m, "disp.path: %s\n", (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? "bosd" : "sosd");
        seq_printf(m, "disp.width: %d\n", hw_ctx->hw_disp_width);
        seq_printf(m, "disp.height: %d\n", hw_ctx->hw_disp_height);

        seq_printf(m, "\n");
        seq_printf(m, "disp.uhd_mode: %d\n", FBDEV_O26_CMN_IsUHDDispMode() ? 1 : 0);
        seq_printf(m, "fb0.width: %d\n", hw_ctx->hw_fb0_width);
        seq_printf(m, "fb0.height: %d\n", hw_ctx->hw_fb0_height);
        seq_printf(m, "fb1.width: %d\n",  hw_ctx->hw_fb1_width);
        seq_printf(m, "fb1.height: %d\n", hw_ctx->hw_fb1_height);
        seq_printf(m, "ext.width: %d\n", hw_ctx->hw_ext_render_width);
        seq_printf(m, "ext.height: %d\n", hw_ctx->hw_ext_render_height);
        seq_printf(m, "hw_osd0_owner: fb(%d)\n", hw_ctx->hw_osd0_owner);
        seq_printf(m, "\n");
        seq_printf(m, "vsync_clk: %dHz\n", (FBDEV_O26_CMN_DetectVSyncClk() == FBDEV_VSYNC_CLK_60HZ) ? 60 : 120);

        seq_printf(m, "support_ext_frc: %d\n", hw_ctx->b_support_ext_frc);
        seq_printf(m, "support_fb1: %d\n", hw_ctx->b_support_fb1);
        seq_printf(m, "support_4kosd: %d\n", hw_ctx->b_support_4kosd);
        seq_printf(m, "support_ext_render: %d\n", hw_ctx->b_support_ext_render);
        seq_printf(m, "\n");

        // (2020/01/18) read the real HW configuration NOT status value.
        // because application might refer this proc to make its reverse-mode config BEFORE kdriver initialization
        // see " user_initcall based HW initialization" policy.
        FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_CTRL_MAIN);
        val = osdx_desc.osd_ctrl_main.osd_v_reverse_en;

        seq_printf(m, "mirror.status: 0x%08x\n", val);
        seq_printf(m, "\n");

        seq_printf(m, "ext_rener.fbmem0: 0x%08x\n", hw_ctx->ext_render_ctrl.fbmem_phys[0]);
        seq_printf(m, "ext_rener.fbmem1: 0x%08x\n", hw_ctx->ext_render_ctrl.fbmem_phys[1]);
        seq_printf(m, "ext_rener.fbmem_idx: %d\n",  hw_ctx->ext_render_ctrl.fbmem_buf_idx);

        seq_printf(m, "ext_rener.hwparam.phys_y: 0x%08x\n", hw_ctx->ext_render_ctrl.hwparam.phys_y);
        seq_printf(m, "ext_rener.hwparam.size: 0x%08x\n", hw_ctx->ext_render_ctrl.hwparam.size);
        seq_printf(m, "ext_rener.hwparam.xoffset: %d\n", hw_ctx->ext_render_ctrl.hwparam.xoffset);
        seq_printf(m, "ext_rener.hwparam.yoffset: %d\n", hw_ctx->ext_render_ctrl.hwparam.yoffset);
        seq_printf(m, "ext_rener.hwparam.enable: %d\n", hw_ctx->ext_render_ctrl.hwparam.enable);
        seq_printf(m, "ext_rener.hwparam.crop_x: %d\n", hw_ctx->ext_render_ctrl.hwparam.crop_x);
        seq_printf(m, "ext_rener.hwparam.crop_y: %d\n", hw_ctx->ext_render_ctrl.hwparam.crop_y);
        seq_printf(m, "ext_rener.hwparam.crop_w: %d\n", hw_ctx->ext_render_ctrl.hwparam.crop_w);
        seq_printf(m, "ext_rener.hwparam.crop_h: %d\n", hw_ctx->ext_render_ctrl.hwparam.crop_h);
        seq_printf(m, "ext_rener.hwparam.tx_count: %d\n", hw_ctx->ext_render_ctrl.hwparam.tx_count);
    }

    /* print SW WA info */
    {
        seq_printf(m, "\n");
        seq_printf(m, "pqefw_osd0_out_ctrl: 0x%x\n", osd_pqefw_osd0_out_ctrl);
        //seq_printf(m, "hw_wa.1x_csr_disp_on_blend_path: 0x%x\n",
        //           (hw_ctx->hw_wa_flag & FBDEV_O26_HW_WA_1X_CSR_DISP_ON_BLEND_PATH) ? 1 : 0);
        //seq_printf(m, "hw_wa.osd0_async_wr_error:       0x%x\n",
        //           (hw_ctx->hw_wa_flag & FBDEV_O26_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR) ? 1 : 0);
        seq_printf(m, "hw_wa.pqwfw_osd0_out_ctrl:       0x%x\n",
                   (hw_ctx->hw_wa_flag & FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL) ? 1 : 0);
        seq_printf(m, "hw_wa_flag:                      0x%x\n", hw_ctx->hw_wa_flag);
        seq_printf(m, "\n");
    }

    /* print OSD_SHP info */
    {
        // N/A
    }

    /* print 4kosd */
    {

    }

    /* print HW_CTX status */

    /* TODO: add something */
}

/** chip specific proc handler
 *
 */
void FBDEV_O26_CMN_ProcHandler(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
    switch (proc_id)
    {
        case FBDEV_HW_PROC_ID_DETAIL_INFO:
        {
#if 0
            FBDEV_O26_HW_CTX_T* hw_ctx = FBDEV_PLT_GET_HW_CTX();

            seq_printf(m, "<HW INFO>\n");
            seq_printf(m, "path: %s\n", (hw_ctx->hw_conn_type & LX_FBDEV_CONN_OSD_VIDEO_BLEND) ? "bosd" : "sosd");
            seq_printf(m, "hw_disp_width: %d\n",    hw_ctx->hw_disp_width);
            seq_printf(m, "hw_disp_height: %d\n",   hw_ctx->hw_disp_height);
            seq_printf(m, "hw_fb0_width: %d\n",     hw_ctx->hw_fb0_width);
            seq_printf(m, "hw_fb0_height: %d\n",    hw_ctx->hw_fb0_height);
            seq_printf(m, "vsync_clk: %dHz\n", (FBDEV_O26_CMN_DetectVSyncClk() == FBDEV_VSYNC_CLK_60HZ) ? 60 : 120);

            seq_printf(m, "support_ext_frc: %d\n",  hw_ctx->b_support_ext_frc);
            seq_printf(m, "support_4kosd: %d\n",    hw_ctx->b_support_4kosd);
#endif
        }
        break;

        case FBDEV_HW_PROC_ID_OSD_HDR:
        {
            int i;
            int xidx;
            int xnum, xlst[2];

            OSDX_DESC_T osdx_desc;

            UINT32  osd_en, sync_en;
            UINT32  hdr_lst[7];
            FBDEV_PLT_OSD_HDR_T* osd_hdr = (FBDEV_PLT_OSD_HDR_T*)hdr_lst;
            LX_FBDEV_ID_T fb_dev_id = (LX_FBDEV_ID_T)data;

            xnum = FBDEV_O26_CMN_GetHWXList(fb_dev_id, xlst);
            seq_printf(m, "posd_num: %d\n", xnum);

            for (i = 0; i < xnum && VALID_XIDX(xlst[i]); i++)
            {
                xidx = xlst[i];

                FBDEV_O26_CMN_ReadOSDXDesc(xidx, &osdx_desc, OSDX_DESC_FLAG_HDR_ALL);

                osd_en = osdx_desc.osd_ctrl_main.osd_en;
                sync_en = osdx_desc.osd_ctrl_sync0.osd_sync_enable;

                memcpy(&hdr_lst[0], &osdx_desc.osd_ctrl_hdr0, sizeof(UINT32));
                memcpy(&hdr_lst[1], &osdx_desc.osd_ctrl_hdr1, sizeof(UINT32));
                memcpy(&hdr_lst[2], &osdx_desc.osd_ctrl_hdr2, sizeof(UINT32));
                memcpy(&hdr_lst[3], &osdx_desc.osd_ctrl_hdr3, sizeof(UINT32));
                memcpy(&hdr_lst[4], &osdx_desc.osd_ctrl_hdr4, sizeof(UINT32));
                memcpy(&hdr_lst[5], &osdx_desc.osd_ctrl_hdr5, sizeof(UINT32));
                memcpy(&hdr_lst[6], &osdx_desc.osd_ctrl_hdr6, sizeof(UINT32));

                seq_printf(m, "posd_idx: %d\n",             xidx);
                seq_printf(m, " visible: %s (osd:%d, sync:%d)\n", (osd_en && sync_en) ? "on" : "off", osd_en, sync_en);
                seq_printf(m, " hdr.xpos: %d\n",            osd_hdr->osd_hdr_xpos);
                seq_printf(m, " hdr.ypos: %d\n",            osd_hdr->osd_hdr_ypos);
                seq_printf(m, " hdr.w_mem: %d\n",           osd_hdr->osd_hdr_w_mem);
                seq_printf(m, " hdr.h_mem: %d\n",           osd_hdr->osd_hdr_h_mem);
                seq_printf(m, " hdr.w_out: %d\n",           osd_hdr->osd_hdr_w_out);
                seq_printf(m, " hdr.h_out: %d\n",           osd_hdr->osd_hdr_h_out);
                seq_printf(m, " hdr.pixel_order: 0x%x\n",   osd_hdr->osd_hdr_pixel_order);
                seq_printf(m, " hdr.wpl: %d\n",             osd_hdr->osd_hdr_wpl);
                seq_printf(m, " hdr.global_alpha_en: %d\n", osd_hdr->osd_hdr_global_alpha_en);
                seq_printf(m, " hdr.global_alpha: 0x%x\n",  osd_hdr->osd_hdr_global_alpha);
                seq_printf(m, " hdr.color_key_en: %d\n",    osd_hdr->osd_hdr_color_key_en);
                seq_printf(m, " hdr.color_key: 0x%x\n",     osd_hdr->osd_hdr_color_key);
                seq_printf(m, " hdr.ptr_plte: 0x%x\n",      osd_hdr->osd_hdr_ptr_plte);
                seq_printf(m, " hdr.ptr_bmp: 0x%x\n",       osd_hdr->osd_hdr_ptr_bmp);
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
            } reg_list[] =
            {
                { .desc = "GSC-.OSD_PRE",   .reg_base = OSD_PRE_REG_BASE, .reg_size = sizeof(OSD_PRE_O26_REG_T) },
                { .desc = "GSC-GLB",        .reg_base = GLB_REG_BASE, .reg_size = sizeof(GLB_O26_REG_T) },
                { .desc = "OSD-OSD_POST",   .reg_base = OSD_REG_BASE, .reg_size = sizeof(OSD_O26_REG_T) },

                { .desc = "TOP-CCO_CTRL",   .reg_base = CCO_CTRL_REG_BASE, .reg_size = sizeof(CCO_CTRL_O26_REG_T) },
                { .desc = "TOP-CCO_CTRL1",  .reg_base = CCO_CTRL1_REG_BASE, .reg_size = sizeof(CCO_CTRL1_O26_REG_T) },
                { .desc = "TOP-GSC_CTRL",   .reg_base = GSC_CTRL_REG_BASE, .reg_size = sizeof(GSC_CTRL_O26_REG_T) },

                { .desc = "AFBC-AFBC2",     .reg_base = AFBC_REG_BASE(2), .reg_size = sizeof(AFBC_O26_REG_T) },
                { .desc = "AFBC-AFBC3",     .reg_base = AFBC_REG_BASE(3), .reg_size = sizeof(AFBC_O26_REG_T) },
                { .desc = "AFRC-AFRC2",     .reg_base = AFRC_REG_BASE(2), .reg_size = sizeof(AFRC_O26_REG_T) },
                { .desc = "AFRC-AFRC3",     .reg_base = AFRC_REG_BASE(3), .reg_size = sizeof(AFRC_O26_REG_T) },
            };


            for (i = 0; i < NELEMENTS(reg_list); i++)
            {
                UINT32 reg_size;

                reg_size = reg_list[i].reg_size;
                reg_size = ALIGN(reg_size, 0x100);

                seq_printf(m, "\n\n");
                seq_printf(m, "FBDEV (%s) : 0x%08x (size=%d)\n", reg_list[i].desc, reg_list[i].reg_base, reg_size);

                for (off = 0; off < reg_size; off += 4)
                {
                    UINT32 reg_addr = reg_list[i].reg_base + off;

                    OS_RdReg(reg_addr, &val);
                    seq_printf(m, " 0x%08x (+0x%04x) = %08x\n", reg_addr, off, val);
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
int FBDEV_O26_CMN_RunResume(void)
{
    // OSD freeze will be stopped after 500 ms
    FBDEV_O26_CMN_RunBootLogoTimer(osd_resume_freeze_timeout, true);

    FBDEV_O26_CMN_ReInitHW();

    return RET_OK;
}

int FBDEV_O26_CMN_RunSuspend(void)
{
    // do nothing
    return RET_OK;
}

/*========================================================================================
    common OSD HW handler
========================================================================================*/
FBDEV_PLT_HW_FUNC_T  g_fbdev_o26_cmn_hw_func =
{
    /* variable is initialize at fbdev_drv_O26.c */

    .O26_InitHW          = FBDEV_O26_CMN_InitHW,
};

