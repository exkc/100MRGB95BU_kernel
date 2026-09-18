/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file apr_reg_m16a0.c
 *
 *  driver for 3d format auto detection. ( used only within kdriver )
 *	- functional functions regardless of modules
 *
 *	@author		justine.jeong
 *	@version	0.1
 *	@note
 *	@date		2012.07.10
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "apr_def.h"
#include "apr_core.h"
#include "apr_reg_m17.h"
#include "apr_fd3_reg_m17.h"


/* external de module */
#ifndef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
#include "../de/de_ctr_reg_m17.h"
//#include "../de/de_smux_reg_m16.h"
#endif

/* external pe module */
#ifndef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
#include "pe_cfg.h"
#include "pe_reg_m17.h"
#include "pe_hst_hw_m17.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
//#define APR_FD3_REG_M17_BASE (M16_DE_BASE + 0x3800)
#define APR_FD3_REG_M17_BASE (0xC9000000 + 0x3800)
#undef APR_SETTING_FD3_REG
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define ROW2PHY(a) (a << 15)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32 v_sampling;
	UINT32 h_sampling;
	UINT32 vcnt_ratio;
	UINT32 src_dual_fd3;
	UINT32 src_sel_fd3;
} APR_SAMPLE_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#ifndef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
//extern DE_SMM_REG_M16_T gDE_SMM_M16;
extern DE_IMX_REG_M17_T gDE_IMX_M17;
#endif

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
//volatile UINT32 *gpTimerBase_m16 = NULL;
APR_FD3_REG_M17_T gAPR_FD3_M17;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void APR_M17_CollectSSCorrelationData(APR_DTA_T *i_pstData);
static void APR_M17_CollectSSMeanData(APR_DTA_T *i_pstData);
static void APR_M17_CollectTBCorrelationData(APR_DTA_T *i_pstData);
static void APR_M17_CollectTBMeanData(APR_DTA_T *i_pstData);
static void APR_M17_CollectHSVData(APR_DTA_T *i_pstData);
static void APR_M17_UpdateFd3Threshold(APR_CFG_T *i_pstAprCfg);
static void APR_M17_UpdateFd3ColSegmentNProjection(APR_CFG_T *i_pstAprCfg,APR_SAMPLE_T *io_pstSampleInfo);
static void APR_M17_UpdateSamplingInfo(APR_CFG_T *i_pstAprCfg,APR_SAMPLE_T *io_pstSampleInfo);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 g_in_x = 1920;
static UINT32 g_in_y = 1080;

/*========================================================================================
	Implementation Group
========================================================================================*/

static void APR_M17_CollectSSCorrelationData(APR_DTA_T *i_pstData)
{
#ifdef APR_SETTING_FD3_REG
	APR_FD3_M17_RdFL(corr_ss_blk_01);
	APR_FD3_M17_RdFL(corr_ss_blk_23);
	APR_FD3_M17_Rd01(corr_ss_blk_01, ss_corr0, i_pstData->fd3.corr.ss[0]);
	APR_FD3_M17_Rd01(corr_ss_blk_01, ss_corr1, i_pstData->fd3.corr.ss[1]);
	APR_FD3_M17_Rd01(corr_ss_blk_23, ss_corr2, i_pstData->fd3.corr.ss[2]);
	APR_FD3_M17_Rd01(corr_ss_blk_23, ss_corr3, i_pstData->fd3.corr.ss[3]);
	APR_FD3_M17_Rd01(corr_ss_blk_01, ss_wnd_info0, i_pstData->fd3.corr.ss_wnd_info[0]);
	APR_FD3_M17_Rd01(corr_ss_blk_01, ss_wnd_info1, i_pstData->fd3.corr.ss_wnd_info[1]);
	APR_FD3_M17_Rd01(corr_ss_blk_23, ss_wnd_info2, i_pstData->fd3.corr.ss_wnd_info[2]);
	APR_FD3_M17_Rd01(corr_ss_blk_23, ss_wnd_info3, i_pstData->fd3.corr.ss_wnd_info[3]);
#endif
}


static void APR_M17_CollectSSMeanData(APR_DTA_T *i_pstData)
{
#ifdef APR_SETTING_FD3_REG

	APR_FD3_M17_RdFL(blk0_ss_stat);
	APR_FD3_M17_RdFL(blk1_ss_stat);
	APR_FD3_M17_RdFL(blk2_ss_stat);
	APR_FD3_M17_RdFL(blk3_ss_stat);
	APR_FD3_M17_RdFL(blk4_ss_stat);
	APR_FD3_M17_RdFL(blk5_ss_stat);
	APR_FD3_M17_RdFL(blk6_ss_stat);
	APR_FD3_M17_RdFL(blk7_ss_stat);
	APR_FD3_M17_Rd01(blk0_ss_stat, mean, i_pstData->fd3.blk_stat.mean[0]);
	APR_FD3_M17_Rd01(blk1_ss_stat, mean, i_pstData->fd3.blk_stat.mean[1]);
	APR_FD3_M17_Rd01(blk2_ss_stat, mean, i_pstData->fd3.blk_stat.mean[2]);
	APR_FD3_M17_Rd01(blk3_ss_stat, mean, i_pstData->fd3.blk_stat.mean[3]);
	APR_FD3_M17_Rd01(blk4_ss_stat, mean, i_pstData->fd3.blk_stat.mean[4]);
	APR_FD3_M17_Rd01(blk5_ss_stat, mean, i_pstData->fd3.blk_stat.mean[5]);
	APR_FD3_M17_Rd01(blk6_ss_stat, mean, i_pstData->fd3.blk_stat.mean[6]);
	APR_FD3_M17_Rd01(blk7_ss_stat, mean, i_pstData->fd3.blk_stat.mean[7]);
	APR_FD3_M17_Rd01(blk0_ss_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[0]);
	APR_FD3_M17_Rd01(blk1_ss_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[1]);
	APR_FD3_M17_Rd01(blk2_ss_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[2]);
	APR_FD3_M17_Rd01(blk3_ss_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[3]);
	APR_FD3_M17_Rd01(blk4_ss_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[4]);
	APR_FD3_M17_Rd01(blk5_ss_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[5]);
	APR_FD3_M17_Rd01(blk6_ss_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[6]);
	APR_FD3_M17_Rd01(blk7_ss_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[7]);
#endif
}

static void APR_M17_CollectTBCorrelationData(APR_DTA_T *i_pstData)
{
#ifdef APR_SETTING_FD3_REG
	APR_FD3_M17_RdFL(corr_tb_blk_01);
	APR_FD3_M17_RdFL(corr_tb_blk_23);
	APR_FD3_M17_Rd01(corr_tb_blk_01, tb_corr0, i_pstData->fd3.corr.tb[0]);
	APR_FD3_M17_Rd01(corr_tb_blk_01, tb_corr1, i_pstData->fd3.corr.tb[1]);
	APR_FD3_M17_Rd01(corr_tb_blk_23, tb_corr2, i_pstData->fd3.corr.tb[2]);
	APR_FD3_M17_Rd01(corr_tb_blk_23, tb_corr3, i_pstData->fd3.corr.tb[3]);
	APR_FD3_M17_Rd01(corr_tb_blk_01, tb_wnd_info0, i_pstData->fd3.corr.tb_wnd_info[0]);
	APR_FD3_M17_Rd01(corr_tb_blk_01, tb_wnd_info1, i_pstData->fd3.corr.tb_wnd_info[1]);
	APR_FD3_M17_Rd01(corr_tb_blk_23, tb_wnd_info2, i_pstData->fd3.corr.tb_wnd_info[2]);
	APR_FD3_M17_Rd01(corr_tb_blk_23, tb_wnd_info3, i_pstData->fd3.corr.tb_wnd_info[3]);
#endif
}

static void APR_M17_CollectTBMeanData(APR_DTA_T *i_pstData)
{
#ifdef APR_SETTING_FD3_REG
	APR_FD3_M17_RdFL(blk0_tb_stat);
	APR_FD3_M17_RdFL(blk1_tb_stat);
	APR_FD3_M17_RdFL(blk2_tb_stat);
	APR_FD3_M17_RdFL(blk3_tb_stat);
	APR_FD3_M17_RdFL(blk4_tb_stat);
	APR_FD3_M17_RdFL(blk5_tb_stat);
	APR_FD3_M17_RdFL(blk6_tb_stat);
	APR_FD3_M17_RdFL(blk7_tb_stat);
	APR_FD3_M17_Rd01(blk0_tb_stat, mean, i_pstData->fd3.blk_stat.mean[8]);
	APR_FD3_M17_Rd01(blk1_tb_stat, mean, i_pstData->fd3.blk_stat.mean[9]);
	APR_FD3_M17_Rd01(blk2_tb_stat, mean, i_pstData->fd3.blk_stat.mean[10]);
	APR_FD3_M17_Rd01(blk3_tb_stat, mean, i_pstData->fd3.blk_stat.mean[11]);
	APR_FD3_M17_Rd01(blk4_tb_stat, mean, i_pstData->fd3.blk_stat.mean[12]);
	APR_FD3_M17_Rd01(blk5_tb_stat, mean, i_pstData->fd3.blk_stat.mean[13]);
	APR_FD3_M17_Rd01(blk6_tb_stat, mean, i_pstData->fd3.blk_stat.mean[14]);
	APR_FD3_M17_Rd01(blk7_tb_stat, mean, i_pstData->fd3.blk_stat.mean[15]);
	APR_FD3_M17_Rd01(blk0_tb_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[0]);
	APR_FD3_M17_Rd01(blk1_tb_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[1]);
	APR_FD3_M17_Rd01(blk2_tb_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[2]);
	APR_FD3_M17_Rd01(blk3_tb_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[3]);
	APR_FD3_M17_Rd01(blk4_tb_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[4]);
	APR_FD3_M17_Rd01(blk5_tb_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[5]);
	APR_FD3_M17_Rd01(blk6_tb_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[6]);
	APR_FD3_M17_Rd01(blk7_tb_stat, standard_dev, i_pstData->fd3.blk_stat.s_dev[7]);
#endif
}

static void APR_M17_CollectHSVData(APR_DTA_T *i_pstData)
{
#ifdef APR_SETTING_FD3_REG
	APR_FD3_M17_RdFL(hsv_picture);
	APR_FD3_M17_Rd01(hsv_picture, pic_seg_hsv_max, i_pstData->fd3.hsv_picture.pic_seg_hsv_max);
	APR_FD3_M17_Rd01(hsv_picture, pic_seg_hsv_count, i_pstData->fd3.hsv_picture.pic_seg_hsv_count);
	APR_FD3_M17_RdFL(hsv_blk0);
	APR_FD3_M17_RdFL(hsv_blk1);
	APR_FD3_M17_RdFL(hsv_blk2);
	APR_FD3_M17_RdFL(hsv_blk3);
	APR_FD3_M17_Rd01(hsv_blk0, blk0_seg_hsv_count, i_pstData->fd3.hsv_blk.seg_hsv_count[0]);
	APR_FD3_M17_Rd01(hsv_blk0, blk0_seg_hsv_max,   i_pstData->fd3.hsv_blk.seg_hsv_max[0]);
	APR_FD3_M17_Rd01(hsv_blk1, blk1_seg_hsv_count, i_pstData->fd3.hsv_blk.seg_hsv_count[1]);
	APR_FD3_M17_Rd01(hsv_blk1, blk1_seg_hsv_max,   i_pstData->fd3.hsv_blk.seg_hsv_max[1]);
	APR_FD3_M17_Rd01(hsv_blk2, blk2_seg_hsv_count, i_pstData->fd3.hsv_blk.seg_hsv_count[2]);
	APR_FD3_M17_Rd01(hsv_blk2, blk2_seg_hsv_max,   i_pstData->fd3.hsv_blk.seg_hsv_max[2]);
	APR_FD3_M17_Rd01(hsv_blk3, blk3_seg_hsv_count, i_pstData->fd3.hsv_blk.seg_hsv_count[3]);
	APR_FD3_M17_Rd01(hsv_blk3, blk3_seg_hsv_max,   i_pstData->fd3.hsv_blk.seg_hsv_max[3]);
#endif
}

static void APR_M17_UpdateFd3Threshold(APR_CFG_T *i_pstAprCfg)
{
#ifdef APR_SETTING_FD3_REG
	APR_CFG_T *pCfg=i_pstAprCfg;

	APR_FD3_M17_RdFL(subtitle_threshold);
	APR_FD3_M17_Wr01(subtitle_threshold, subtitle_th,0xD1/*192*/);
	APR_FD3_M17_WrFL(subtitle_threshold);

	APR_FD3_M17_RdFL(segmentation_threshold_0);
	APR_FD3_M17_RdFL(segmentation_threshold_1);
	APR_FD3_M17_RdFL(segmentation_threshold_2);
	APR_FD3_M17_RdFL(segmentation_threshold_3);
	APR_FD3_M17_Wr01(segmentation_threshold_0, seg_red,         pCfg->fd3.seg_thr.seg_red);
	APR_FD3_M17_Wr01(segmentation_threshold_0, seg_re_ye,       pCfg->fd3.seg_thr.seg_re_ye);
	APR_FD3_M17_Wr01(segmentation_threshold_0, seg_yellow,      pCfg->fd3.seg_thr.seg_yellow);
	APR_FD3_M17_Wr01(segmentation_threshold_0, seg_ye_gr,       pCfg->fd3.seg_thr.seg_ye_gr);
	APR_FD3_M17_Wr01(segmentation_threshold_1, seg_green,       pCfg->fd3.seg_thr.seg_green);
	APR_FD3_M17_Wr01(segmentation_threshold_1, seg_gr_cy,       pCfg->fd3.seg_thr.seg_gr_cy);
	APR_FD3_M17_Wr01(segmentation_threshold_1, seg_cyan,        pCfg->fd3.seg_thr.seg_cyan);
	APR_FD3_M17_Wr01(segmentation_threshold_1, seg_cy_bl,       pCfg->fd3.seg_thr.seg_cy_bl);
	APR_FD3_M17_Wr01(segmentation_threshold_2, seg_blue,        pCfg->fd3.seg_thr.seg_blue);
	APR_FD3_M17_Wr01(segmentation_threshold_2, seg_bl_ma,       pCfg->fd3.seg_thr.seg_bl_ma);
	APR_FD3_M17_Wr01(segmentation_threshold_2, seg_magenta,     pCfg->fd3.seg_thr.seg_magenta);
	APR_FD3_M17_Wr01(segmentation_threshold_2, seg_ma_re,       pCfg->fd3.seg_thr.seg_ma_re);
	APR_FD3_M17_Wr01(segmentation_threshold_3, seg_th_sdelta,   pCfg->fd3.seg_thr.seg_value_black);
	APR_FD3_M17_Wr01(segmentation_threshold_3, seg_th_saturate, pCfg->fd3.seg_thr.seg_saturate);
	APR_FD3_M17_Wr01(segmentation_threshold_3, seg_th_sdelta,   pCfg->fd3.seg_thr.seg_sdelta);
	APR_FD3_M17_WrFL(segmentation_threshold_0);
	APR_FD3_M17_WrFL(segmentation_threshold_1);
	APR_FD3_M17_WrFL(segmentation_threshold_2);
	APR_FD3_M17_WrFL(segmentation_threshold_3);
#endif
}

int APR_M17_Init(void)
{
	int ret = RET_OK;

//	gpTimerBase_m16 = (volatile UINT32 *)ioremap(M16_TIMER_BASE + 0x24, 4);
	gAPR_FD3_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(APR_FD3_REG_M17A0_T));
	gAPR_FD3_M17.phys.addr = (volatile UINT32 *)ioremap(APR_FD3_REG_M17_BASE, sizeof(APR_FD3_REG_M17A0_T));

	return ret;
}

int APR_M17_Uninit(void)
{
	int ret = RET_OK;

//	if (gpTimerBase_m16) iounmap((void *)gpTimerBase_m16);
	if(gAPR_FD3_M17.shdw.addr) OS_Free((void *)gAPR_FD3_M17.shdw.addr);
	if(gAPR_FD3_M17.phys.addr) iounmap((void *)gAPR_FD3_M17.phys.addr);

	return ret;
}

int APR_M17_InitHardware(void)
{
	int ret = RET_OK;
#ifdef APR_SETTING_FD3_REG
#ifndef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
	do {
		if(lx_chip_rev() >= LX_CHIP_REV(M17,A0))
		{
			PE_DNR0_M17_RdFL(pe0_3dfd_ctrl_00);
			PE_DNR0_M17_RdFL(pe0_3dfd_ctrl_01);
			PE_DNR0_M17_RdFL(pe0_3dfd_ctrl_02);
			PE_DNR0_M17_RdFL(pe0_3dfd_ctrl_03);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_00, aw_offset_x, 0);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_00, aw_offset_y, 0);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_00, cb_th1, 0x3C);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_00, cb_th2, 0x14);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_01, cc_th1, 0x3C);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_01, cc_th2, 0x14);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_01, ll_th1, 0x3C);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_01, ll_th2, 0x14);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_02, pt_th, 0x80);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_02, sstb_th, 0x07);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_02, div_mode, 0);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_03, small_delta_en, 0);
			PE_DNR0_M17_Wr01(pe0_3dfd_ctrl_03, small_delta_th, 0xFF);
			PE_DNR0_M17_WrFL(pe0_3dfd_ctrl_00);
			PE_DNR0_M17_WrFL(pe0_3dfd_ctrl_01);
			PE_DNR0_M17_WrFL(pe0_3dfd_ctrl_02);
			PE_DNR0_M17_WrFL(pe0_3dfd_ctrl_03);
		}
	} while(0);
#endif
#endif
	return ret;
}

int APR_M17_GetMaxFromBuffer(UINT32 *pBuf, UINT32 count, UINT32 *pElect)
{
    int ret = RET_OK;
	UINT32 i=0, j=0;
	UINT32 temp=0;

	do {
		for(i=0;i<count;i++)
		{
			for(j=0;j<count;j++)
			{
				if(pBuf[j] >= temp)
				{
					temp = pBuf[j];
				}
			}
		}
		*pElect = temp;
	} while(0);
	return ret;
}

int APR_M17_CollectBasicData(APR_CFG_T *apr_cfg, APR_DTA_T *apr_data)
{
    int ret = RET_OK;
#ifndef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
	APR_CFG_T *pCfg  = apr_cfg;
	APR_DTA_T *pData = apr_data;
	UINT32 scan_info  = 0;
	UINT32 color_info = 0;

	do {
		if(lx_chip_rev() >= LX_CHIP_REV(M17,A0))
		{
			PE_DNR0_M17_RdFL(pe0_3dfd_stat_00);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_00, cb_count, pData->cb);
			PE_DNR0_M17_RdFL(pe0_3dfd_stat_00);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_00, cc_count, pData->cc);
			PE_DNR0_M17_RdFL(pe0_3dfd_stat_01);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_01, ll_count, pData->ll);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_01, trid_format, pData->hw_fmt);
			/*WR APR detect 0150519, inkyung.park*/
			pData->cb = pData->cc = pData->ll = 0x0;

			PE_DNR0_M17_RdFL(pe0_3dfd_stat_02);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_02, delta_ss_h, pData->ssh);
			PE_DNR0_M17_RdFL(pe0_3dfd_stat_03);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_03, delta_ss_v, pData->ssv);
			PE_DNR0_M17_RdFL(pe0_3dfd_stat_04);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_04, delta_tb_v, pData->tbv);
			PE_DNR0_M17_RdFL(pe0_3dfd_stat_05);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_05, delta_tb_h, pData->tbh);

			PE_DNR0_M17_RdFL(pe0_3dfd_stat_06);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_06, ss_ratio, pData->ssr);
			PE_DNR0_M17_RdFL(pe0_3dfd_stat_07);
			PE_DNR0_M17_Rd01(pe0_3dfd_stat_07, tb_ratio, pData->tbr);

			PE_VCP_DE_M17_RdFL(vcp_mifu0_win_i_size);
			PE_VCP_DE_M17_Rd01(vcp_mifu0_win_i_size, mif_win_i_size_x, pCfg->out_win_x);
			PE_VCP_DE_M17_Rd01(vcp_mifu0_win_i_size, mif_win_i_size_y, pCfg->out_win_y);

			PE_IPP_M17_RdFL(ipp_size_i);
			PE_IPP_M17_RdFL(ipp_ctrl0);
			PE_IPP_M17_Rd01(ipp_size_i, hsize_i, pCfg->in_win_x);
			PE_IPP_M17_Rd01(ipp_size_i, vsize_i, pCfg->in_win_y);
			PE_IPP_M17_Rd01(ipp_ctrl0, pr_sq, scan_info);
			PE_IPP_M17_Rd01(ipp_ctrl0, i_c_fmt, color_info);
			if(pCfg->in_win_y > 1080) // 4k case
			{
				UINT32 r_size;
				PE_GSC_Y_M17_RdFL(gsc_g0_y_crop_param3);
				PE_GSC_Y_M17_Rd01(gsc_g0_y_crop_param3, reg_hisize_g0, r_size);
				if(pCfg->in_win_x == r_size)
					pCfg->in_win_x = r_size * 2;
				else
					pCfg->in_win_x = (pCfg->in_win_x + r_size) >> 1;
			}
			g_in_x = pCfg->in_win_x;
			g_in_y = pCfg->in_win_y;

			pCfg->scan      = scan_info;
			pCfg->fd3.scan  = (scan_info==0)?1:0;
			switch(color_info)
			{
				case 6: // 444
					pCfg->fd3.color = 2;
					break;
				case 5: // 422
					pCfg->fd3.color = 1;
					break;
				case 4: // 420
				default:
					pCfg->fd3.color = 0;
					break;
			}

			PE_CO_PE1_M17_RdFL(pe1_mute_ctrl_00);
			PE_CO_PE1_M17_Rd01(pe1_mute_ctrl_00, pxl_rep_in, pCfg->mute_status);
		}
	}while(0);

#endif
	return ret;
}

int APR_M17_GetOVInfo(APR_CFG_T *apr_cfg, APR_CAP_SRC_T ov_src, APR_OV_INFO_T *ov_info)
{
	int ret = RET_OK;

	printk("%s : not support\n", __F__);

	return ret;
}

int APR_M17_GetHistInfo(APR_HST_INFO_T *hist_info)
{
	int ret = RET_OK;
#ifndef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
	PE_HST_HW_M17_INFO_T histo_info;

	do {
		switch(hist_info->cur_fmt)
		{
			case LX_APR_FMT_2D_2D :
				histo_info.det_3df = PE_HST_HW_M17_DET_3D_FMT_2D_2D;
				break;
			case LX_APR_FMT_3D_CB :
				histo_info.det_3df = PE_HST_HW_M17_DET_3D_FMT_3D_CB;
				break;
			case LX_APR_FMT_3D_CC :
				histo_info.det_3df = PE_HST_HW_M17_DET_3D_FMT_3D_CC;
				break;
			case LX_APR_FMT_3D_LL :
				histo_info.det_3df = PE_HST_HW_M17_DET_3D_FMT_3D_LL;
				break;
			case LX_APR_FMT_3D_SS :
				histo_info.det_3df = PE_HST_HW_M17_DET_3D_FMT_3D_SS;
				break;
			case LX_APR_FMT_3D_TB :
				histo_info.det_3df = PE_HST_HW_M17_DET_3D_FMT_3D_TB;
				break;
			case LX_APR_FMT_UNKNOWN :
				histo_info.det_3df = PE_HST_HW_M17_DET_3D_FMT_UNKNOWN;
				break;
			default :
				histo_info.det_3df = PE_HST_HW_M17_DET_3D_FMT_2D_2D;
				break;
		}
		ret = PE_HST_HW_M17_GetHistoInfo(&histo_info);
		if(ret != RET_OK) break;
		hist_info->src_type = histo_info.dis_inf.src_type;
		hist_info->out_type = histo_info.dis_inf.out_type;
		memcpy(hist_info->lrc.dif_max, histo_info.lrc_inf.dif_max, sizeof(UINT32)*4);
		memcpy(hist_info->lrc.pxl_cnt, histo_info.lrc_inf.pxl_cnt, sizeof(UINT32)*4);
		memcpy(hist_info->lrc.set_cnt, histo_info.lrc_inf.set_cnt, sizeof(UINT32)*4);

		memcpy(hist_info->src.s_state, histo_info.src_inf.s_state, sizeof(UINT32)*2);
		memcpy(hist_info->src.dif_max, histo_info.src_inf.dif_cnt, sizeof(UINT32)*18);
		memcpy(hist_info->src.pxl_cnt, histo_info.src_inf.pxl_cnt, sizeof(UINT32)*18);
		memcpy(hist_info->src.set_cnt, histo_info.src_inf.set_cnt, sizeof(UINT32)*18);
	} while(0);
#endif
	return ret;
}

int APR_M17_GetUSecTimerVal(UINT32 *tv)
{
	int ret = RET_OK;
//	*tv = (UINT32)((0xFFFFFFFF - *gpTimerBase_m16)/198);
	return ret;
}

int APR_M17_SetFd3SubtConfig(APR_CFG_T *apr_cfg, int alt_seg)
{
	int ret = RET_OK;
//	APR_CFG_T *pCfg  = apr_cfg;

	do {
		APR_FD3_M17_RdFL(subtitle_threshold);
		APR_FD3_M17_Wr01(subtitle_threshold, subtitle_alt_seg, alt_seg);
		APR_FD3_M17_WrFL(subtitle_threshold);
	} while(0);

	return ret;
}

static void APR_M17_UpdateSamplingInfo(APR_CFG_T *i_pstAprCfg,APR_SAMPLE_T *io_pstSampleInfo)
{
	APR_CFG_T *pCfg  = i_pstAprCfg;
	UINT32 color = pCfg->fd3.color;

	if(pCfg->in_win_y < 720){ //SD
		io_pstSampleInfo->v_sampling = 0;
		io_pstSampleInfo->h_sampling = 0;
		io_pstSampleInfo->vcnt_ratio = 1;
	}
	else if((pCfg->in_win_y >= 720) && (pCfg->in_win_y < 1080)){ //HD
		io_pstSampleInfo->v_sampling = (pCfg->fd3.scan==0) ? 1 : 0;
		io_pstSampleInfo->h_sampling = 0;
		io_pstSampleInfo->vcnt_ratio = 2;
	}
	else if(pCfg->in_win_y == 1080){ //FHD
		io_pstSampleInfo->v_sampling = (pCfg->fd3.scan==0) ? 1 : 0;
		io_pstSampleInfo->h_sampling = 1; // in case of 2k, h sampling is not working
		io_pstSampleInfo->vcnt_ratio = 1;
	}

	if((pCfg->fd3.color == 0/*420:color fmt*/) && (pCfg->fd3.scan == 0/*progressive*/)){
		io_pstSampleInfo->v_sampling = 0;
	}

	if(pCfg->in_win_y > 1080 || pCfg->in_win_x > 1920){ // 4k case
		if(pCfg->src_type == LX_PE_SRC_DTV)
		{
			io_pstSampleInfo->v_sampling = 2;
		}
		else
		{
			if(color >= 2)
				io_pstSampleInfo->v_sampling = 2;
			else
				io_pstSampleInfo->v_sampling = color;
		}

		io_pstSampleInfo->h_sampling = 1;
		io_pstSampleInfo->vcnt_ratio = 1;
		io_pstSampleInfo->src_dual_fd3 = 1;
		io_pstSampleInfo->src_sel_fd3 = 0;
	}
	else
	{
		io_pstSampleInfo->src_dual_fd3 = 0;
		io_pstSampleInfo->src_sel_fd3 = 0;
	}
}

static void APR_M17_UpdateFd3ColSegmentNProjection(APR_CFG_T *i_pstAprCfg,APR_SAMPLE_T *io_pstSampleInfo)
{
	#ifdef APR_SETTING_FD3_REG
	UINT32 vcnt_ratio = io_pstSampleInfo->vcnt_ratio;

	APR_FD3_M17_RdFL(fd3_mode);
	APR_FD3_M17_RdFL(segmentation_window);
	APR_FD3_M17_RdFL(projection_window);
	APR_FD3_M17_RdFL(projection_parameter_1);
	APR_FD3_M17_Wr01(fd3_mode, fd3_color_format,  i_pstAprCfg->fd3.color);
	APR_FD3_M17_Wr01(fd3_mode, interlaced, i_pstAprCfg->fd3.scan);// 0:progressive, 1:interlaced
	APR_FD3_M17_Wr01(fd3_mode, vertical_sampling, io_pstSampleInfo->v_sampling); // 0:all line, 1:every two line
	APR_FD3_M17_Wr01(fd3_mode, horizontal_sampling, io_pstSampleInfo->h_sampling); // 0:all line, 1:every two line
	APR_FD3_M17_Wr01(segmentation_window, seg_wnd_loffset, i_pstAprCfg->fd3.win.seg_l);
	APR_FD3_M17_Wr01(segmentation_window, seg_wnd_roffset, i_pstAprCfg->fd3.win.seg_r);
	APR_FD3_M17_Wr01(segmentation_window, seg_wnd_toffset, i_pstAprCfg->fd3.win.seg_t);
	APR_FD3_M17_Wr01(segmentation_window, seg_wnd_boffset, i_pstAprCfg->fd3.win.seg_b);
	APR_FD3_M17_Wr01(projection_window, proj_wnd_lroffset, i_pstAprCfg->fd3.win.prj_l);
	APR_FD3_M17_Wr01(projection_window, proj_wnd_toffset, i_pstAprCfg->fd3.win.prj_t);
	APR_FD3_M17_Wr01(projection_window, proj_wnd_boffset, i_pstAprCfg->fd3.win.prj_b);
	APR_FD3_M17_Wr01(projection_parameter_1, vcnt_ratio, vcnt_ratio);
	APR_FD3_M17_WrFL(fd3_mode);
	APR_FD3_M17_WrFL(segmentation_window);
	APR_FD3_M17_WrFL(projection_window);
	APR_FD3_M17_WrFL(projection_parameter_1);
	#endif
}

int APR_M17_SetFd3Config(APR_CFG_T *apr_cfg)
{
	int ret = RET_OK;
	#ifdef APR_SETTING_FD3_REG
	APR_CFG_T *pCfg  = apr_cfg;
	APR_SAMPLE_T stAprSampleInfo = {0,0,0,0,0};
	UINT32 color = pCfg->fd3.color;
	UINT32 reg = 0;
	UINT32 count = 10;

	do {
		//Update V/H sampling, cnt_ratio and src related info
		APR_M17_UpdateSamplingInfo(apr_cfg,&stAprSampleInfo);
		//Update color format and window info for color segmentation and projection
		APR_M17_UpdateFd3ColSegmentNProjection(apr_cfg,&stAprSampleInfo);
		//Update threshold values
		APR_M17_UpdateFd3Threshold(apr_cfg);

#ifndef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
		DE_IMX_M17_RdFL(ctrl_block_mux);
		//DE_IMX_M17_Wr01(ctrl_block_mux, reg_src_dual_fd3, src_dual_fd3);
		DE_IMX_M17_Wr01(ctrl_block_mux, reg_src_sel_fd3, stAprSampleInfo.src_sel_fd3);
		DE_IMX_M17_WrFL(ctrl_block_mux);
#endif
		// w/o code for 4k progressive v sampling
		if((g_in_x > 1920) && (g_in_y > 1080))
		{
			do {
				APR_FD3_M17_RdFL(fd3_mode);
				APR_FD3_M17_Rd01(fd3_mode, horizontal_sampling, reg);
				if(stAprSampleInfo.h_sampling != reg)
				{
					msleep(1);
					APR_FD3_M17_Wr01(fd3_mode, horizontal_sampling, stAprSampleInfo.h_sampling?0:1);
					APR_FD3_M17_WrFL(fd3_mode);
					APR_FD3_M17_Wr01(fd3_mode, horizontal_sampling, stAprSampleInfo.h_sampling);
					APR_FD3_M17_WrFL(fd3_mode);
				}
			}while(count--);
		}
	} while(0);
	#endif
	return ret;
}

int APR_M17_CollectFd3Data(APR_DTA_T *apr_data)
{
	int ret = RET_OK;
	#ifdef APR_SETTING_FD3_REG
	APR_DTA_T *pData  = apr_data;
	UINT32 h_sampling = 1;
	UINT32 reg = 0;
	UINT32 count = 10;

	do {
		// scene
		APR_FD3_M17_RdFL(status_dominant_1);
		APR_FD3_M17_Rd01(status_dominant_1, scene_type, pData->fd3.scene_type);
		// bMask
		APR_FD3_M17_Rd01(status_dominant_1, dominant_hsv_idx0, pData->fd3.bMask);
		APR_M17_CollectSSCorrelationData(pData);
		APR_M17_CollectTBCorrelationData(pData);
		APR_M17_CollectSSMeanData(pData);
		APR_M17_CollectTBMeanData(pData);
		APR_M17_CollectHSVData(pData);

		APR_FD3_M17_RdFL(fd3_status_1);
		APR_FD3_M17_Rd01(fd3_status_1, init_count, pData->fd3.status.init_count);
		APR_FD3_M17_Rd01(fd3_status_1, suc_fail_history, pData->fd3.status.suc_fail_history);

		// w/o code for 2k progressive h sampling
		if((g_in_x == 1920) && (g_in_y == 1080))
		{
			do {
				APR_FD3_M17_RdFL(fd3_mode);
				APR_FD3_M17_Rd01(fd3_mode, horizontal_sampling, h_sampling);
				APR_FD3_M17_Wr01(fd3_mode, horizontal_sampling, h_sampling?0:1);
				APR_FD3_M17_WrFL(fd3_mode);

				APR_FD3_M17_RdFL(fd3_mode);
				APR_FD3_M17_Rd01(fd3_mode, horizontal_sampling, reg);
				if(h_sampling == reg)
				{
					msleep(1);
					APR_FD3_M17_Wr01(fd3_mode, horizontal_sampling, h_sampling?0:1);
					APR_FD3_M17_WrFL(fd3_mode);
					APR_FD3_M17_Wr01(fd3_mode, horizontal_sampling, h_sampling);
					APR_FD3_M17_WrFL(fd3_mode);
				}
			}while(count--);
		}
	} while(0);
	#endif
	return ret;
}

int APR_M17_DetectBlackBar(APR_CFG_T *apr_cfg, APR_DTA_T *apr_data)
{
	int ret = RET_OK;
#ifdef APR_SETTING_FD3_REG
#ifndef _DISABLE_ACCESS_TO_EXT_REGISTER_M17_
	APR_CFG_T *pCfg  = apr_cfg;
	APR_DTA_T *pData = apr_data;

	int film_bar_th = ((pCfg->in_win_y/2)*3)>>4;
	int real_dom_seg = pData->fd3.bMask;
	int bbd_stat_x0 = 0;
	int bbd_stat_y0 = 0;

	do {
		// check black bar state
		if(lx_chip_rev() >= LX_CHIP_REV(M17,A0))
		{
			PE_ND0_M17_RdFL(bbd_stat_00);
			PE_ND0_M17_Rd01(bbd_stat_00, x0, bbd_stat_x0);
			PE_ND0_M17_Rd01(bbd_stat_00, y0, bbd_stat_y0);
		}
		if((bbd_stat_y0 > film_bar_th) && (pData->tpd < 200) )
		{
			// remove black color
			APR_FD3_M17_RdFL(force_mode);
			APR_FD3_M17_Wr01(force_mode, force_mode, 2);
			//				APR_FD3_M16Wr01(force_mode, force_scn_type, 0);
			APR_FD3_M17_Wr01(force_mode, force_hsv_idx0, real_dom_seg);
			APR_FD3_M17_Wr01(force_mode, force_hsv_idx1, 12);
			APR_FD3_M17_Wr01(force_mode, force_val_idx,  31);
			APR_FD3_M17_WrFL(force_mode);

			APR_FD3_M17_RdFL(dominant_threshold_0);
			APR_FD3_M17_Wr01(dominant_threshold_0, dom_pic_seg_th0, 0x30);
			APR_FD3_M17_Wr01(dominant_threshold_0, dom_pic_seg_th1, 0x86);
			APR_FD3_M17_WrFL(dominant_threshold_0);

			APR_FD3_M17_RdFL(dominant_threshold_1);
			APR_FD3_M17_Wr01(dominant_threshold_1, dom_blk_seg_hsv_th, 0x60);
			APR_FD3_M17_Wr01(dominant_threshold_1, dom_blk_seg_hsv_th_h, 0x90);
			APR_FD3_M17_WrFL(dominant_threshold_1);

			APR_FD3_M17_RdFL(projection_parameter_1);
			APR_FD3_M17_Wr01(projection_parameter_1, vdcnt_ratio, 0x3);
			APR_FD3_M17_WrFL(projection_parameter_1);
		}
		else // off force mode
		{
			APR_FD3_M17_RdFL(force_mode);
			APR_FD3_M17_Wr01(force_mode, force_mode, 0);
			APR_FD3_M17_WrFL(force_mode);

			APR_FD3_M17_RdFL(dominant_threshold_0);
			APR_FD3_M17_Wr01(dominant_threshold_0, dom_pic_seg_th0, 0x40);
			APR_FD3_M17_Wr01(dominant_threshold_0, dom_pic_seg_th1, 0xB3);
			APR_FD3_M17_WrFL(dominant_threshold_0);

			APR_FD3_M17_RdFL(dominant_threshold_1);
			APR_FD3_M17_Wr01(dominant_threshold_1, dom_blk_seg_hsv_th,   0x80);
			APR_FD3_M17_Wr01(dominant_threshold_1, dom_blk_seg_hsv_th_h, 0xC0);
			APR_FD3_M17_WrFL(dominant_threshold_1);

			APR_FD3_M17_RdFL(projection_parameter_1);
			APR_FD3_M17_Wr01(projection_parameter_1, vdcnt_ratio, 0x4);
			APR_FD3_M17_WrFL(projection_parameter_1);
		}

		if(pCfg->fd3.enb == LX_APR_FD3_BBD)
			printk("%s - y0 : %d,  th : %d\n", __F__, bbd_stat_y0,film_bar_th);
	} while(0);
#endif
#endif

	return ret;
}

int APR_M17_SetCurrentInfo(APR_CFG_T *apr_cfg, APR_DTA_T *apr_data)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg  = apr_cfg;
	APR_DTA_T *pData = apr_data;
	UINT32 reg = 0;

	do {
		if(!pCfg->fd3.enb) break;

		// [ 1: 0] detection info
		// [ 2   ] scene type
		// [30: 3] reserved
		// [31   ] 0:invalid, 1:valid
		switch(pCfg->apr_fmt)
		{
			case LX_APR_FMT_2D_2D :
				reg |= (0 << 0);
				break;
			case LX_APR_FMT_3D_SS :
				reg |= (1 << 0);
				break;
			case LX_APR_FMT_3D_TB :
				reg |= (2 << 0);
				break;
			default :
				reg |= (0 << 0);
				break;
		}
		reg |= (pData->fd3.scene_type << 2);
		reg |= (1 << 31);
	} while(0);

//		printk("%s : not support\n", __F__);

	return ret;
}

