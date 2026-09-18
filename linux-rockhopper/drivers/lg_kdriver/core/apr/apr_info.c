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


/** @file
 *
 *  Display information about APR for debug purpose
 *  [Refactored code]
 *  author		harish.singh
 *  version		1.0
 *  date		2015.06.10
 *  note		Debug related functions are moved to this file from apr_core.c
 *
 *  @addtogroup apr
 *	@{
 */
/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "os_util.h"

#include "apr_def.h"
#include "apr_core.h"
#include "apr_hal.h"
#include "apr_osd.h"
#include "apr_ldf.h"
#include "apr_hfd.h"
#include "apr_cmn.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define APR_MSG			if(_g_apr_trace==LX_APR_CMD_LOG)APR_PRINT

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_APR_CMD _g_apr_trace ;
extern APR_THREAD_CB_T apr_thread_cb;
/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void APR_DumpLRCorrectionHistModeOne(APR_DTA_T *i_pstAprData);
static void APR_DumpLRCorrectionHistModeTwo(APR_DTA_T *i_pstAprData);
static int APR_DumpLrcHistData(APR_INFO_T *i_pstAprInfo,APR_THR_TMP_T *i_pstAprTmpThr);
static int APR_DumpHistogram(APR_INFO_T *i_pstAprInfo);
static int APR_DumpData4Simulation(APR_INFO_T *i_pstAprInfo);
static int APR_DisplayGraph(APR_INFO_T *i_pstAprInfo);
static int APR_DisplayInfo(APR_INFO_T *i_pstAprInfo);
static int DrawGraph(UINT32 val, UINT32 thr, UINT32 norm, UINT32 max, int *line);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

static int DrawGraph(UINT32 val, UINT32 thr, UINT32 norm, UINT32 max, int *line)
{
	char str[STRING_MAX_SIZE];
	UINT32 pos1, pos2;

	pos1 = (UINT32)(val*norm/max);
	pos2 = (UINT32)(thr*norm/max);
	pos1 = pos1 & 0x3F;
	pos2 = pos2 & 0x3F;
	pos1++;
	pos2++;

	memset(str, 0, STRING_MAX_SIZE);
	if(val > thr)
	{
		memset(str, 0x3E/*>*/, pos1);
		memset(str, 0x2E/*.*/, pos2);
	}
	else
	{
		memset(str, 0x2E/*.*/, pos1);
	}

	return APR_OSD_DrawString(str, 0, (*line)++);
}


static void APR_DumpLRCorrectionHistModeOne(APR_DTA_T *i_pstAprData)
{
	UINT32 itr = 0;
	APR_DTA_T *pData = i_pstAprData;
	UINT32 lr_g_diff, lr_b_diff, lr_r_diff, tb_g_diff, tb_b_diff, tb_r_diff;
	UINT32 lr_g_sum = 0, lr_b_sum = 0, lr_r_sum = 0, tb_g_sum = 0, tb_b_sum = 0, tb_r_sum = 0;
	UINT32 rb_bin_apr = 32;

	for(itr=0;itr<rb_bin_apr;itr++)
	{

		lr_g_diff = APR_DIFF(pData->hist_l_g[itr], pData->hist_r_g[itr]);
		lr_b_diff = APR_DIFF(pData->hist_l_b[itr], pData->hist_r_b[itr]);
		lr_r_diff = APR_DIFF(pData->hist_l_r[itr], pData->hist_r_r[itr]);
		lr_g_sum += lr_g_diff;
		lr_b_sum += lr_b_diff;
		lr_r_sum += lr_r_diff;
		APR_MSG("%02d) [%07d][%07d] [%07d][%07d] [%07d][%07d]",itr,\
			pData->hist_l_g[itr], pData->hist_r_g[itr], pData->hist_l_b[itr], pData->hist_r_b[itr], pData->hist_l_r[itr], pData->hist_r_r[itr]);
		tb_g_diff = APR_DIFF(pData->hist_t_g[itr], pData->hist_b_g[itr]);
		tb_b_diff = APR_DIFF(pData->hist_t_b[itr], pData->hist_b_b[itr]);
		tb_r_diff = APR_DIFF(pData->hist_t_r[itr], pData->hist_b_r[itr]);
		tb_g_sum += tb_g_diff;
		tb_b_sum += tb_b_diff;
		tb_r_sum += tb_r_diff;
		APR_MSG(": [%07d][%07d] [%07d][%07d] [%07d][%07d]\n",\
			pData->hist_t_g[itr], pData->hist_b_g[itr], pData->hist_t_b[itr], pData->hist_b_b[itr], pData->hist_t_r[itr], pData->hist_b_r[itr]);
	}

	APR_MSG("    Total diff\n");
	APR_MSG("     %07d            %07d            %07d          :  %07d            %07d            %07d\n", lr_g_sum, lr_b_sum, lr_r_sum, tb_g_sum, tb_b_sum, tb_r_sum);
}

static void APR_DumpLRCorrectionHistModeTwo(APR_DTA_T *i_pstAprData)
{
	UINT32 itr = 0;
	UINT32 sum = 0;
	APR_DTA_T *pData = i_pstAprData;
	UINT32 rb_bin_apr = 32;

	for(itr=0;itr<rb_bin_apr;itr++)
	{
		APR_MSG("%02d) [%07d]	: [%07d]", itr, pData->dce_l[itr], pData->dce_r[itr]);
		sum += APR_DIFF(pData->dce_l[itr], pData->dce_r[itr]);
	}

	APR_MSG("    Total diff %d\n", sum);
}

static int APR_DumpLrcHistData(APR_INFO_T *i_pstAprInfo,APR_THR_TMP_T *i_pstAprTmpThr)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg = &i_pstAprInfo->cfg;
	APR_DTA_T *pData = &i_pstAprInfo->dta;
	APR_THR_T *pThr = &i_pstAprInfo->thr;
	APR_STM_T *pStm = &i_pstAprInfo->stm;
	UINT32 max_pd = 0;
	UINT32 win_half_size = 0;

	do {
		if(pStm->win_pos != APR_WIN_LRTB_FULL)
			win_half_size = APR_WIN_RATIO;
		else
			win_half_size = 1;

		APR_GetMax3(&pData->cb, &pData->cc, &pData->ll, &max_pd);

		printk("LRC : == value	/  threshold  ====	[outtype %d  %dx%d] \n", pCfg->out_type, pCfg->out_win_x, pCfg->out_win_y);
		printk("tpd[%d] / %d	 ,	 motion_l[%d] / 2d-%d 3d-%d , motion_r[%d]\n", pData->tpd, pThr->tpd_thr, pData->motion_l, pThr->mtn_thr_2d, pThr->mtn_thr_3d, pData->motion_r);
		printk("cb[%d] cc[%d] ll[%d] -> max_pd[%d] / %d\n", pData->cb, pData->cc, pData->ll, max_pd, pThr->ptn_thr);
		printk("ssr[%d] tbr[%d] / 2D->3D[%d] , 3D->2D[%d]\n", pData->ssr, pData->tbr, pThr->fmt_th2, pThr->fmt_th1);
		printk("ssh[%d] ssv[%d] tbh[%d] tbv[%d] \n", pData->ssh, pData->ssv, pData->tbh, pData->tbv);
		printk("LRCR win_pos[%d] (0:LRTB_FULL,1:LRTB_HAF1,2:LRTB_HAF2) \n", pStm->win_pos);

		printk("thr_adj[%d] lr_diff[%d] tb_diff[%d] / fmt_th3[%d] ,  lr-tb[%d] / fmt_th4[%d] \n", \
		i_pstAprTmpThr->thr_adj, pData->hist_lrc.lr_diff, pData->hist_lrc.tb_diff, i_pstAprTmpThr->tmp_thr3, (int)abs(pData->hist_lrc.lr_diff - pData->hist_lrc.tb_diff), i_pstAprTmpThr->tmp_thr4);
		printk("fmt_th6[%d] fmt_th7[%d] fmt_th8[%d] fmt_th9[%d] fmt_th10[%d]\n", i_pstAprTmpThr->tmp_thr6, i_pstAprTmpThr->tmp_thr7, pThr->fmt_th8, pThr->fmt_th9, pThr->fmt_th10);
		printk("vld_thr[%d] \n", pThr->vld_thr);
		printk("motion[%d/%d], spatial[%d/%d], apl[%d/%d], noise[%d/%d],  dual_screen_fmt[%d](0:2D,8:SS,9:TB)\n", pData->motion_l, pData->motion_r, pData->spatial_l, pData->spatial_r, pData->apl_l, pData->apl_r, pData->nt_l, pData->nt_r, pData->hw_fmt);
		printk("APR : ==>> Format tmp[%d] final[%d]	(0:2D,1:CB,2:LL,3:CC,4:SS,5:TB,6:UNKNOWN)  Test pattern(%d)\n", pCfg->tmp_fmt, pCfg->apr_fmt, pCfg->tpd_flag);
	} while(0);

	return ret;
}

static int APR_DumpHistogram(APR_INFO_T *i_pstAprInfo)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg = &i_pstAprInfo->cfg;
	APR_DTA_T *pData = &i_pstAprInfo->dta;

	do {
		switch(pCfg->out_type)
		{
			case LX_PE_OUT_2D :
			case LX_PE_OUT_UD :
			case LX_PE_OUT_PIP :
				APR_MSG("\nAPR : LR Correction HISTOGRAM\n");
				APR_MSG("     G [L][R]           B [L][R]           R [L][R]         :  G [T][B]           B [T][B]           R [T][B]\n");
				APR_DumpLRCorrectionHistModeOne(pData);
				break;
			case LX_PE_OUT_3D_2D :
			case LX_PE_OUT_TB :
			case LX_PE_OUT_SS :
			case LX_PE_OUT_FS :
			case LX_PE_OUT_LA :
			case LX_PE_OUT_DUAL_TB :
			case LX_PE_OUT_DUAL_SS :
			case LX_PE_OUT_DUAL_FULL :
				APR_MSG("\nAPR : DCE HISTOGRAM\n");
				APR_MSG("L		: R\n");
				APR_DumpLRCorrectionHistModeTwo(pData);
				break;
			default :
				break;
		}
	} while(0);

	return ret;
}

static int APR_DumpData4Simulation(APR_INFO_T *i_pstAprInfo)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg = &i_pstAprInfo->cfg;
	APR_DTA_T *pData= &i_pstAprInfo->dta;
	APR_THR_T *pThr = &i_pstAprInfo->thr;

	if(pCfg->hidden_cmd == LX_APR_HCMD_DUMP_SCRIPT_DATA) {
		printk("MESSAGE_B= %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",\
		pCfg->cur_lrc_fmt,pCfg->fmt_before_vote[APR_METHOD_3],pCfg->apr_fmt,pData->tpd,pData->ssr,pData->tbr,pThr->fd3.subtitle,pThr->fd3.variation,pThr->fd3.correlation,pThr->fd3.corr_3rd,pCfg->cur_src_fmt,\
		pData->fd3.blk_stat.mean[0],pData->fd3.blk_stat.mean[1],pData->fd3.blk_stat.mean[2],pData->fd3.blk_stat.mean[3],\
		pData->fd3.blk_stat.mean[4],pData->fd3.blk_stat.mean[5],pData->fd3.blk_stat.mean[6],pData->fd3.blk_stat.mean[7],\
		pData->fd3.blk_stat.s_dev[0],pData->fd3.blk_stat.s_dev[1],pData->fd3.blk_stat.s_dev[2],pData->fd3.blk_stat.s_dev[3],\
		pData->fd3.blk_stat.s_dev[4],pData->fd3.blk_stat.s_dev[5],pData->fd3.blk_stat.s_dev[6],pData->fd3.blk_stat.s_dev[7],\
		pData->fd3.scene_type,pData->fd3.bMask,\
		pData->fd3.corr.ss[0],pData->fd3.corr.ss[1],pData->fd3.corr.ss[2],pData->fd3.corr.ss[3],\
		pData->fd3.corr.tb[0],pData->fd3.corr.tb[1],pData->fd3.corr.tb[2],pData->fd3.corr.tb[3],\
		pData->fd3.corr.ss_wnd_info[0],pData->fd3.corr.ss_wnd_info[1],pData->fd3.corr.ss_wnd_info[2],pData->fd3.corr.ss_wnd_info[3],\
		pData->fd3.corr.tb_wnd_info[0],pData->fd3.corr.tb_wnd_info[1],pData->fd3.corr.tb_wnd_info[2],pData->fd3.corr.tb_wnd_info[3]);
#if 0
		printk("\n");
#else
		printk(" %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d \n",\
		pData->ssr,pData->tbr,pData->hist_lrc.lr_diff,pData->hist_lrc.tb_diff,\
		pData->hist_src.tb_diff[0],pData->hist_src.tb_diff[1],pData->hist_src.tb_diff[2],pData->hist_src.tb_diff[3],\
		pData->hist_src.tb_diff[4],pData->hist_src.tb_diff[5],pData->hist_src.tb_diff[6],pData->hist_src.tb_diff[7],\
		pData->hist_src.tb_diff[8],\
		pData->hist_src.lr_diff[0],pData->hist_src.lr_diff[1],pData->hist_src.lr_diff[2],pData->hist_src.lr_diff[3],\
		pData->hist_src.lr_diff[4],pData->hist_src.lr_diff[5],pData->hist_src.lr_diff[6],pData->hist_src.lr_diff[7],\
		pData->hist_src.lr_diff[8],\
		pData->hist_src.tb_ratio[0],pData->hist_src.ss_ratio[0],\
		pCfg->img_class, pData->fd3.hsv_picture.pic_seg_hsv_max,	pData->fd3.hsv_picture.pic_seg_hsv_count,\
		pData->hist_lrc.tb_ratio, pData->hist_lrc.ss_ratio,\
		pData->fd3.hsv_blk.seg_hsv_count[0], pData->fd3.hsv_blk.seg_hsv_count[1],\
		pData->fd3.hsv_blk.seg_hsv_count[2], pData->fd3.hsv_blk.seg_hsv_count[3],\
		pData->fd3.hsv_blk.seg_hsv_max[0], pData->fd3.hsv_blk.seg_hsv_max[1],\
		pData->fd3.hsv_blk.seg_hsv_max[2], pData->fd3.hsv_blk.seg_hsv_max[3],\
		pData->motion_l, pCfg->hfd_1_fmt, pCfg->hfd_2_fmt, pCfg->hfd_3_fmt, pCfg->hfd_3_1_fmt, pCfg->in_win_x, pCfg->in_win_y);
#endif
	}
	if(pCfg->hidden_cmd == LX_APR_HCMD_DUMP_EXCEL_DATA) {
		printk("MESSAGE_A= %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",\
			pCfg->out_type,pCfg->out_win_x,pCfg->out_win_y,pData->tpd,pThr->tpd_thr,pData->motion_l,pThr->mtn_thr_2d,pThr->mtn_thr_3d,pData->motion_r,pData->cb,pData->cc,pData->ll,pThr->ptn_thr,pData->ssr,pData->tbr,\
			pThr->fmt_th2,pThr->fmt_th1,pData->ssh,pData->ssv,pData->tbh,pData->tbv,pData->hist_lrc.lr_diff,pData->hist_lrc.tb_diff,pThr->fmt_th3,pThr->fmt_th4,pThr->fmt_th6,pThr->fmt_th7,pThr->fmt_th8, pThr->fmt_th9, pThr->fmt_th10,\
			pData->fd3.blk_stat.mean[0],pData->fd3.blk_stat.mean[1],pData->fd3.blk_stat.mean[2],pData->fd3.blk_stat.mean[3],\
			pData->fd3.blk_stat.mean[4],pData->fd3.blk_stat.mean[5],pData->fd3.blk_stat.mean[6],pData->fd3.blk_stat.mean[7]);
		printk("MESSAGE_B= %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",\
			pThr->fmt_th5,pThr->vld_thr,pData->motion_l,pData->motion_r,pData->spatial_l,pData->spatial_r,pData->apl_l,pData->apl_r,pData->nt_l,\
			pData->nt_r,pData->hw_fmt,\
			pCfg->fd3.sampling,pCfg->fd3.scan,pCfg->fd3.color,\
			pCfg->fd3.win.seg_l,pCfg->fd3.win.seg_r,pCfg->fd3.win.seg_t,pCfg->fd3.win.seg_b,\
			pCfg->fd3.win.prj_l,pCfg->fd3.win.prj_r,pCfg->fd3.win.prj_t,pCfg->fd3.win.prj_b,\
			pThr->fd3.subtitle,pThr->fd3.variation,pThr->fd3.correlation,pThr->fd3.corr_3rd,pCfg->cur_src_fmt,\
			pData->fd3.blk_stat.s_dev[0],pData->fd3.blk_stat.s_dev[1],pData->fd3.blk_stat.s_dev[2],pData->fd3.blk_stat.s_dev[3],\
			pData->fd3.blk_stat.s_dev[4],pData->fd3.blk_stat.s_dev[5],pData->fd3.blk_stat.s_dev[6],pData->fd3.blk_stat.s_dev[7],\
			pCfg->fmt_before_vote[APR_METHOD_3]);
		printk("MESSAGE_C= %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d \n\n",\
			pCfg->cur_lrc_fmt, pCfg->apr_fmt,
			pData->hist_src.tb_diff[0],pData->hist_src.tb_diff[1],pData->hist_src.tb_diff[2],pData->hist_src.tb_diff[3],\
			pData->hist_src.tb_diff[4],pData->hist_src.tb_diff[5],pData->hist_src.tb_diff[6],pData->hist_src.tb_diff[7],\
			pData->hist_src.tb_diff[8],\
			pData->hist_src.lr_diff[0],pData->hist_src.lr_diff[1],pData->hist_src.lr_diff[2],pData->hist_src.lr_diff[3],\
			pData->hist_src.lr_diff[4],pData->hist_src.lr_diff[5],pData->hist_src.lr_diff[6],pData->hist_src.lr_diff[7],\
			pData->hist_src.lr_diff[8],\
			pData->hist_src.tb_ratio[0],pData->hist_src.ss_ratio[0],\
			pData->fd3.scene_type,pData->fd3.bMask,\
			pData->fd3.corr.ss[0],pData->fd3.corr.ss[1],pData->fd3.corr.ss[2],pData->fd3.corr.ss[3],\
			pData->fd3.corr.tb[0],pData->fd3.corr.tb[1],pData->fd3.corr.tb[2],pData->fd3.corr.tb[3],\
			pData->fd3.corr.ss_wnd_info[0],pData->fd3.corr.ss_wnd_info[1],pData->fd3.corr.ss_wnd_info[2],pData->fd3.corr.ss_wnd_info[3],\
			pData->fd3.corr.tb_wnd_info[0],pData->fd3.corr.tb_wnd_info[1],pData->fd3.corr.tb_wnd_info[2],pData->fd3.corr.tb_wnd_info[3]\
				);
	}

	return ret;
}

static int APR_DisplayGraph(APR_INFO_T *i_pstAprInfo)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg  = &i_pstAprInfo->cfg;
	APR_DTA_T *pData = &i_pstAprInfo->dta;
	APR_THR_T *pThr  = &i_pstAprInfo->thr;
	APR_OSD_PATTERN pattern_rect = APR_OSD_MAX;
	char *tmp_str = NULL;
	char *pattern_str = NULL;
	char str[STRING_MAX_SIZE];
	static LX_APR_FORMAT prev_fmt = LX_APR_FMT_MAX;
	static int display_skip_count = 0;
	int line_idx = 0;
	UINT32 pos;
	UINT32 normalize = 60;
	UINT32 i = 0;

	do {
		if(display_skip_count++ != 1) break;
		display_skip_count = 0;
//		if(pCfg->ldf_fmt == prev_fmt) break;
		prev_fmt = pCfg->ldf_fmt;

		APR_CheckTime("Draw  result",i_pstAprInfo, APR_GET_TIME_DRW, APR_GET_START);

		APR_OSD_SetFlip(APR_OSD_SET_BASE);

		APR_FormatPatternToString(pCfg->ldf_fmt, &pattern_rect, &pattern_str, &tmp_str); // result of method 2

		ret = APR_OSD_DrawString(pattern_str, 0, line_idx++);
		memset(str, 0, STRING_MAX_SIZE);

		for(i=0;i<32;i++)
		{
			char ch;
			sprintf(&ch, "%X", pData->d2d.state_num[i]);
			//strcat(str, &ch);
			str[i] = ch;
			if(pData->d2d.state_num[i] == 0) break;
			sprintf(&ch, ">");
			//strcat(str, &ch);
			str[i] = ch;
		}

		ret = APR_OSD_DrawString(	str, 0, line_idx++);

		line_idx++;
		APR_ConvertOutToString(pCfg->out_type, &tmp_str);
		memset(str, 0, STRING_MAX_SIZE);
		strcat(str, "Output type : ");
		strcat(str, tmp_str);
		ret = APR_OSD_DrawString(	str, 0, line_idx++);
		ret = APR_OSD_PrintParam(	"cap/mes/drw (usec) ", pCfg->time.capture,\
									"/", pCfg->time.measure,            \
									"/", pCfg->time.draw,               \
									NULL, 0,                            \
									0, line_idx++);
		line_idx++;
		ret = APR_OSD_DrawString(	"Differential info of 2 windows(L/R)", 0, line_idx++);
		ret = APR_OSD_PrintParam(	"tpd    : ", pData->tpd,            \
									" / ", pThr->tpd_thr,               \
									NULL, 0,                            \
									NULL, 0,                            \
								   	0, line_idx++);
#if 1
		ret = APR_OSD_PrintParam(	"APL    : ", pData->d2d.apl_diff_2d,\
									"  L/R ", pData->d2d.apl_l,         \
									"/",     pData->d2d.apl_r,          \
									NULL, 0,                            \
								   	0, line_idx++);
#endif
		ret = APR_OSD_PrintParam(	"Pixel  : ", pData->d2d.pixel_diff, \
									" THR3 ", pThr->d2d.thr_3,          \
									NULL, 0,                            \
									NULL, 0,                            \
								   	0, line_idx++);
		ret = DrawGraph(pData->d2d.pixel_diff, pThr->d2d.thr_3, normalize, 40*1760*127, &line_idx);

		memset(str, 0, STRING_MAX_SIZE);
		pos = pData->d2d.pixel_dinv*normalize/(40*1760*127);
		pos = pos & 0x3F;
		pos++;
		ret = APR_OSD_PrintParam(	"Pixinv : ", pData->d2d.pixel_dinv, \
									NULL, 0,                            \
									NULL, 0,                            \
									NULL, 0,                            \
								   	0, line_idx++);
		memset(str, 0x2E, pos);
		ret = APR_OSD_DrawString(	str, 0, line_idx++);

		ret = APR_OSD_PrintParam(	"Histo  : ", pData->d2d.histo_diff, \
									" THR1/2 ", pThr->d2d.thr_1,        \
									" / ", pThr->d2d.thr_2,             \
									NULL, 0,                            \
								   	0, line_idx++);
		ret = DrawGraph(pData->d2d.histo_diff, pThr->d2d.thr_1, normalize, 40*(1920-160)*32, &line_idx);
		ret = DrawGraph(pData->d2d.histo_diff, pThr->d2d.thr_2, normalize, 40*(1920-160)*32, &line_idx);

		ret = APR_OSD_PrintParam(	"Adjct  : ", pData->d2d.adjct_diff, \
									" THR4/5/6 ", pThr->d2d.thr_4,      \
									" / ", pThr->d2d.thr_5,             \
									" / ", pThr->d2d.thr_6,             \
								   	0, line_idx++);
		ret = DrawGraph(pData->d2d.adjct_diff, pThr->d2d.thr_4, normalize, 40*(1920-160)*16, &line_idx);
		ret = DrawGraph(pData->d2d.adjct_diff, pThr->d2d.thr_5, normalize, 40*(1920-160)*16, &line_idx);
		ret = DrawGraph(pData->d2d.adjct_diff, pThr->d2d.thr_6, normalize, 40*(1920-160)*16, &line_idx);

		APR_CheckTime("Draw  result",i_pstAprInfo,APR_GET_TIME_DRW, APR_GET_END);

		APR_OSD_SetFlip(APR_OSD_SET_FLIP);
	} while(0);

	return ret;
}

static int APR_DisplayInfo(APR_INFO_T *i_pstAprInfo)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg  = &i_pstAprInfo->cfg;
	APR_DTA_T *pData = &i_pstAprInfo->dta;
	APR_OSD_PATTERN m1_pattern_rect = APR_OSD_MAX;
	APR_OSD_PATTERN m2_pattern_rect = APR_OSD_MAX;
	APR_OSD_PATTERN m3_pattern_rect = APR_OSD_MAX;
	APR_OSD_PATTERN final_pattern_rect = APR_OSD_MAX;
	char *tmp_str = NULL;
	char *m1_pattern_str = NULL, *m2_pattern_str = NULL, *m3_pattern_str = NULL, *final_pattern_str = NULL;
	char *m1_tmp_str = NULL, *m2_tmp_str = NULL, *m3_tmp_str = NULL, *final_tmp_str = NULL;
	char str[STRING_MAX_SIZE];
	static LX_APR_FORMAT prev_fmt = LX_APR_FMT_MAX;
	static int display_skip_count = 0;
	int line_idx = 0;

	do {
		if(pCfg->enable < LX_APR_CMD_PATTERN) break;
//		if(pCfg->apr_fmt == LX_APR_FMT_UNKNOWN) break;
//		if(display_skip_count++ != 1) break;
		display_skip_count = 0;
//		if(pCfg->apr_fmt == prev_fmt) break;
		prev_fmt = pCfg->apr_fmt;
		memset(str, 0, STRING_MAX_SIZE);

		APR_FormatPatternToString(pCfg->fmt_after_vote[APR_METHOD_1], &m1_pattern_rect, &m1_pattern_str, &m1_tmp_str); // result of method 1
		APR_FormatPatternToString(pCfg->fmt_after_vote[APR_METHOD_2], &m2_pattern_rect, &m2_pattern_str, &m2_tmp_str); // result of method 2
		APR_FormatPatternToString(pCfg->fmt_after_vote[APR_METHOD_3], &m3_pattern_rect, &m3_pattern_str, &m3_tmp_str); // result of method 3(final)
		APR_FormatPatternToString(pCfg->apr_fmt, &final_pattern_rect, &final_pattern_str, &final_tmp_str); // result of final negotiation

		APR_ConvertOutToString(pCfg->out_type, &tmp_str);

		APR_CheckTime("Draw  result",i_pstAprInfo, APR_GET_TIME_DRW, APR_GET_START);

		APR_OSD_SetFlip(APR_OSD_SET_BASE);

		if(pCfg->out_type==LX_PE_OUT_2D)
		{
			if(pCfg->fd3.enb)      ret = APR_OSD_DrawPattern(final_pattern_rect/*m3_pattern_rect*/);
			else if(pCfg->cap.enb) ret = APR_OSD_DrawPattern(m2_pattern_rect);
			else                   ret = APR_OSD_DrawPattern(m1_pattern_rect);
		}

		if(pCfg->enable < LX_APR_CMD_OSD_LOG)
		{
			APR_OSD_SetFlip(APR_OSD_SET_FLIP);
			APR_CheckTime("Draw  result",i_pstAprInfo, APR_GET_TIME_DRW, APR_GET_END);
			break;
		}

		ret = APR_OSD_DrawString(final_pattern_str, 0, line_idx++);

		strcat(str, "  M1:");
		strcat(str, m1_tmp_str);
		strcat(str, "  M2:");
		strcat(str, (pCfg->cap.enb)?m2_tmp_str:"?");
		strcat(str, "  M3:");
		strcat(str, (pCfg->fd3.enb)?m3_tmp_str:"?");
		ret = APR_OSD_DrawString(   str, 0, line_idx++);
		memset(str, 0, STRING_MAX_SIZE);
		strcat(str, "Operation mode : ");
		strcat(str, (apr_thread_cb.func==NULL)?"INTERRUPT":"THREAD");
		ret = APR_OSD_DrawString(	str, 0, line_idx++);
		memset(str, 0, STRING_MAX_SIZE);
		strcat(str, "Source    type : ");
		strcat(str, ((pCfg->src_type >= LX_PE_SRC_ATV) && (pCfg->src_type <= LX_PE_SRC_RGBPC))?"ANALOG":"DIGITAL");
		ret = APR_OSD_DrawString(	str, 0, line_idx++);
		memset(str, 0, STRING_MAX_SIZE);
		strcat(str, "Scan      type : ");
		strcat(str, (pCfg->scan == 0)?"INTERLACED":"PROGRESSIVE");
		ret = APR_OSD_DrawString(	str, 0, line_idx++);
		memset(str, 0, STRING_MAX_SIZE);
		strcat(str, "Output    type : ");
		strcat(str, tmp_str);
		ret = APR_OSD_DrawString(	str, 0, line_idx++);
		ret = APR_OSD_PrintParam(	"Mem usage : ", (pCfg->mem_usage>>10),\
									" KB  ", 0,                    \
									NULL, 0,                       \
									NULL, 0,                       \
									0, line_idx++);
		ret = APR_OSD_DrawString(	"Time info (usec)", 0, line_idx++);
		ret = APR_OSD_PrintParam(	" M2 : ", pCfg->time.capture,  \
									"  M3 : ", pCfg->time.fd3,      \
									"  drw : ", pCfg->time.draw,    \
									NULL, 0,                       \
									0, line_idx++);
		ret = APR_OSD_DrawString(	"Window info", 0, line_idx++);
		ret = APR_OSD_PrintParam(	" in_w  : ", pCfg->in_win_x,       \
									" in_h  : ", pCfg->in_win_y,       \
									NULL, 0,                           \
									NULL, 0,                           \
								   	0, line_idx++);
		ret = APR_OSD_PrintParam(	" out_w : ", pCfg->out_win_x,      \
									" out_h : ", pCfg->out_win_y,      \
									NULL, 0,                           \
									NULL, 0,                           \
								   	0, line_idx++);

		ret = APR_OSD_DrawString(	"Data info", 0, line_idx++);

		ret = APR_OSD_PrintParam(	" tpd : ", pData->tpd,\
									" ssr : ", pData->ssr,\
									" tbr : ", pData->tbr,\
									NULL, 0,              \
								   	0, line_idx++);
		ret = APR_OSD_PrintParam(	" scene_type : ", pData->fd3.scene_type,\
									" bMask : ", pData->fd3.bMask,      \
									NULL, 0,                            \
									NULL, 0,                            \
								   	0, line_idx++);
		ret = APR_OSD_PrintParamHex(" init_count : ", pData->fd3.status.init_count,\
									NULL, 0,                            \
									NULL, 0,                            \
									NULL, 0,                            \
								   	0, line_idx++);
		ret = APR_OSD_PrintParamHex(" suc_fail_history : ", pData->fd3.status.suc_fail_history,\
									NULL, 0,                            \
									NULL, 0,                            \
									NULL, 0,                            \
								   	0, line_idx++);
		ret = APR_OSD_DrawString(	" Correlation", 0, line_idx++);
		ret = APR_OSD_DrawString(	" SS", 0, line_idx++);
		ret = APR_OSD_PrintParam(	" ",   pData->fd3.corr.ss[0],       \
									" / ", pData->fd3.corr.ss[1],       \
									" / ", pData->fd3.corr.ss[2],       \
									" / ", pData->fd3.corr.ss[3],       \
								   	0, line_idx++);
		ret = APR_OSD_DrawString(	" TB", 0, line_idx++);
		ret = APR_OSD_PrintParam(	" ",   pData->fd3.corr.tb[0],       \
									" / ", pData->fd3.corr.tb[1],       \
									" / ", pData->fd3.corr.tb[2],       \
									" / ", pData->fd3.corr.tb[3],       \
								   	0, line_idx++);
		ret = APR_OSD_DrawString(	" SS_WND", 0, line_idx++);
		ret = APR_OSD_PrintParam(	" ",   pData->fd3.corr.ss_wnd_info[0],\
									" / ", pData->fd3.corr.ss_wnd_info[1],\
									" / ", pData->fd3.corr.ss_wnd_info[2],\
									" / ", pData->fd3.corr.ss_wnd_info[3],\
								   	0, line_idx++);
		ret = APR_OSD_DrawString(	" TB_WND", 0, line_idx++);
		ret = APR_OSD_PrintParam(	" ",   pData->fd3.corr.tb_wnd_info[0],\
									" / ", pData->fd3.corr.tb_wnd_info[1],\
									" / ", pData->fd3.corr.tb_wnd_info[2],\
									" / ", pData->fd3.corr.tb_wnd_info[3],\
								   	0, line_idx++);

		APR_CheckTime("Draw  result",i_pstAprInfo, APR_GET_TIME_DRW, APR_GET_END);

		APR_OSD_SetFlip(APR_OSD_SET_FLIP);
	} while(0);

	return ret;
}


/**
 * APR_DumpCurrentConfig( ) - Current APR configuration information
 *
 * Print APR configuration information for debugging
 *
 * @param [in] No Parameter
 * @return int  function status
 * @remarks  No Remark
 * @see
*/
int APR_DumpCurrentConfig(APR_INFO_T *i_pstAprInfo)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg = &i_pstAprInfo->cfg;

	do {
		APR_PRINT("\n");
		APR_PRINT("src_type    [%d] (0:DTV,1:ATV,2:CVBS,3:SCART,4:COMP,5:PC,6:HDMI)\n", pCfg->src_type);
		APR_PRINT("out_type    [%d] (0:2D,1:3D-2D,2:2D-3D,3:UD,4:TB,5:SS,6:FS,7DUAL_TB,8:DUAL_SS,9:DUAL_FULL,10:PIP)\n", pCfg->out_type);
		APR_PRINT("in_type     [%d] (0:TB,1:SS,2:QC,3:CB,4:FP,5:FPI,6:FA,7:FS,8:LA,9:SSF,10:DUAL,11:CA,12:LAH)\n", pCfg->in_type);
		APR_PRINT("Image class [%d] (0:TP,1:2D_HARD,2:2D_WEAK_SS,3:2D_WEAK_TB,4:SS_HARD,5:SS_WEAK,6:TB_HARD,7:TB_WEAK)\n", pCfg->img_class);
		APR_PRINT("Enable     : apr[%d] hst[%d] cap[%d] fd3[%d]\n", pCfg->enable, pCfg->hst_enb, pCfg->cap.enb, pCfg->fd3.enb);
		APR_PRINT("Detect fmt : src_hst[%d],lrc_hst[%d],ldf[%d],fd3[%d],apr[%d] (0:2D,4:SS,5:TB,7:UN)\n", pCfg->cur_src_fmt,pCfg->cur_lrc_fmt,pCfg->ldf_fmt,pCfg->fd3_fmt,pCfg->apr_fmt);
		APR_PRINT("input  win : w[%d] h[%d]\n", pCfg->in_win_x, pCfg->in_win_y);
		APR_PRINT("output win : w[%d] h[%d]\n", pCfg->out_win_x, pCfg->out_win_y);
		APR_PRINT("scan       : [%d] (0:I,1:P)\n", pCfg->scan);
		APR_PRINT("\n");
		APR_PRINT("\n");
	} while(0);

	return ret;
}

int APR_DisplayResult(APR_INFO_T *i_pstAprInfo,APR_THR_TMP_T *i_pstAprTmpThr)
{
	APR_CFG_T *pCfg  = &(i_pstAprInfo->cfg);

	switch(pCfg->enable)
	{
		case LX_APR_CMD_OSD_LOG :
			APR_DisplayInfo(i_pstAprInfo);
			break;
		case LX_APR_CMD_OSD_GRF :
			APR_DisplayGraph(i_pstAprInfo);
			break;
		default :
			break;
	}

	if(1)
	{
		static UINT32 count = 0;
		if(pCfg->hst_enb == LX_APR_HST_FMT) {
			if(++count%8== 0 && pCfg->out_type == LX_PE_OUT_2D)
			{
				APR_DumpLrcHistData(i_pstAprInfo,i_pstAprTmpThr);
				count = 0;
			}
		}

		if(pCfg->hidden_cmd == LX_APR_HCMD_DUMP_INFO) {
			printk("Format [%d] (0:2D,4:SS,5:TB,6:UNKNOWN)  Test pattern(%d)\n", pCfg->apr_fmt, pCfg->tpd_flag);
		}

		if(count==100)
			APR_DumpHistogram(i_pstAprInfo);

		APR_DumpData4Simulation(i_pstAprInfo);
	}

	return RET_OK;
}

