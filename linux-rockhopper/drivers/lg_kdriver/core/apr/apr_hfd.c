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
 *  measure hardware format detection
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.07.10
 *  note		Additional information.
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
#include <linux/kernel.h>
#include <asm/uaccess.h>

#include "base_types.h"
#include "apr_def.h"
#include "apr_core.h"
#include "apr_hal.h"
#include "apr_hfd.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define APR_DIFF(a,b) (a>=b)?abs(a-b):abs(b-a)
#define FD3MSG	if(pCfg->fd3.enb == LX_APR_FD3_FMT)printk
#define FD3DBG	if(pCfg->hidden_cmd == LX_APR_HCMD_DUMP_FD3 && g_msg_cnt & 1)printk
#define FD3ALG  if(pCfg->fd3.enb == LX_APR_FD3_LOG)printk
#define FD3PRT  if(pCfg->hidden_cmd == LX_APR_HCMD_DUMP_FD3 && g_msg_cnt & 1)printk

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern APR_INFO_T apr_info;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
UINT32 g_msg_cnt = 0;

 /* corr_th, third_cor_th,final_corr_th,mean_tolerance_th,var_th,var_valid_blk,candi_blk_thaw,cross_corr_en,
     cross_corr_th0,cross_corr_th1,dom_seg_chk_en,dom_seg_chk_th0,dom_seg_chk_th1,blk_mean_chk_en*/
APR_IMG_CLASS_VAR_T g_sImgFormatToVarMap[]= \
{
	{248,179,220,20,0,1,0,0,0,0,1,0,0,1},//APR_IMG_CLASS_TPD [0]
	{248,200,220,20,64,1,0,1,30,50,1,0,0,1},//APR_IMG_CLASS_2D_HARD
	{248,179,220,20,0,1,0,1,30,50,1,0,0,1},//APR_IMG_CLASS_2D_WEAK_SS
	{248,179,220,20,0,1,0,1,30,50,1,0,0,1},//APR_IMG_CLASS_2D_WEAK_TB
	{248,160,200,20,64,2,1,0,0,0,0,0,0,0},//APR_IMG_CLASS_SS_HARD
	{248,179,220,20,0,1,0,1,30,50,1,0,0,1},//APR_IMG_CLASS_SS_WEAK
	{248,160,200,20,0,2,1,0,0,0,0,0,0,0},//APR_IMG_CLASS_TB_HARD
	{248,179,220,20,0,1,0,1,30,50,1,0,0,1} //APR_IMG_CLASS_TB_WEAK
};
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int APR_FD3_ChangeThreshold(UINT32 i_nParam);
static void APR_FD3_SortArrayMax(int i_nElements,int *io_pArr1 , int *io_pArr2);
static void APR_FD3_UpdateThreshold(int change_segment);
static void APR_FD3_ExceptionHandling(LX_APR_FORMAT *io_peDetectFormat , APR_IMG_CLASS_T m1_img_class);
static void APR_FD3_CrossCorrCheck(LX_APR_FORMAT *io_peDetectFormat, APR_IMG_CLASS_VAR_T *i_pstImgClassVar);
static void APR_FD3_GetFinalCorr(LX_APR_FORMAT *io_peDetectFormat , APR_IMG_CLASS_VAR_T *i_pstImgClassVar , APR_BASIC_ALGOPARAM_T *io_pstBasicAlgoParam);
static void APR_FD3_VideoModeFirstDecision(LX_APR_FORMAT *io_peDetectFormat,APR_IMG_CLASS_VAR_T *i_pstImgClassVar,APR_BASIC_ALGOPARAM_T *io_pstBasicAlgoParam);
static void APR_FD3_VideoModeThirdDecision(LX_APR_FORMAT *io_peDetectFormat,APR_IMG_CLASS_VAR_T *i_pstImgClassVar , APR_BASIC_ALGOPARAM_T *i_pstBasicAlgoParam, int *i_pnScan3d );
static void APR_FD3_Verify3DSSFormat(LX_APR_FORMAT *io_peDetectFormat,int *i_pArrSegMax , int *i_pArrSegIdx);
static void APR_FD3_3DFmtDetectAlgo1(LX_APR_FORMAT *io_peDetectFormat , APR_IMG_CLASS_VAR_T *i_pstImgClassVar);
static void APR_FD3_3DFmtDetectAlgo2(LX_APR_FORMAT *io_pe3DFormat,APR_BASIC_ALGOPARAM_T *io_pstBasicAlgoParam);
static void APR_FD3_VideoModeCorrValue(LX_APR_FORMAT *io_peDetectFormat , int *i_pArrScan3d);
static int APR_FD3_SubtitleMode(LX_APR_FORMAT *result);
static int APR_FD3_VideoMode(LX_APR_FORMAT *result);
static void APR_FD3_UpdateLCensus(int *io_pArrLCensus,int *io_pArrMeanBlock,int i_nRefMean ,int i_nflag);
static void APR_FD3_UpdateRCensus(int *io_pArrRCensus,int *io_pArrMeanBlock,int i_nRefMean ,int i_nflag);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static int APR_FD3_ChangeThreshold(UINT32 param)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_CFG_T *pCfg  = &apr_info.cfg;

	int seg_idx = pData->fd3.hsv_picture.pic_seg_hsv_max;
	int margin_th_p[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	int margin_th_m[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

	if(seg_idx < 12)
	{
		if (seg_idx == 10)
		{
			margin_th_p[11] = 4;
			margin_th_m[0]       = 4;
		}
		if (seg_idx == 11)
		{
			margin_th_p[0] = 4;
			margin_th_m[1]       = 4;
		}
		else if (seg_idx < 10)
		{
			margin_th_p[seg_idx+1]   = 4;
			margin_th_m[seg_idx+2] = 4;
		}
	}

	// 0 : default, 1 :
	if (param == 0)
	{
		pCfg->fd3.seg_thr.seg_red         = 173;
		pCfg->fd3.seg_thr.seg_re_ye       =   8;
		pCfg->fd3.seg_thr.seg_yellow      =  23;
		pCfg->fd3.seg_thr.seg_ye_gr       =  38;
		pCfg->fd3.seg_thr.seg_green       =  53;
		pCfg->fd3.seg_thr.seg_gr_cy       =  68;
		pCfg->fd3.seg_thr.seg_cyan        =  83;
		pCfg->fd3.seg_thr.seg_cy_bl       =  98;
		pCfg->fd3.seg_thr.seg_blue        =  113;
		pCfg->fd3.seg_thr.seg_bl_ma       =  128;
		pCfg->fd3.seg_thr.seg_magenta     =  143;
		pCfg->fd3.seg_thr.seg_ma_re       =  158;

		pCfg->fd3.seg_thr.seg_value_black =  32;
		pCfg->fd3.seg_thr.seg_saturate    =  61;
		pCfg->fd3.seg_thr.seg_sdelta      =  30;
	}
	else
	{
		pCfg->fd3.seg_thr.seg_red         = (173 + margin_th_p[0]  -  margin_th_m[0] );
		pCfg->fd3.seg_thr.seg_re_ye       = (  8 + margin_th_p[1]  -  margin_th_m[1] );
		pCfg->fd3.seg_thr.seg_yellow      = ( 23 + margin_th_p[2]  -  margin_th_m[2] );
		pCfg->fd3.seg_thr.seg_ye_gr       = ( 38 + margin_th_p[3]  -  margin_th_m[3] );
		pCfg->fd3.seg_thr.seg_green       = ( 53 + margin_th_p[4]  -  margin_th_m[4] );
		pCfg->fd3.seg_thr.seg_gr_cy       = ( 68 + margin_th_p[5]  -  margin_th_m[5] );
		pCfg->fd3.seg_thr.seg_cyan        = ( 83 + margin_th_p[6]  -  margin_th_m[6] );
		pCfg->fd3.seg_thr.seg_cy_bl       = ( 98 + margin_th_p[7]  -  margin_th_m[7] );
		pCfg->fd3.seg_thr.seg_blue        = (113 + margin_th_p[8]  -  margin_th_m[8] );
		pCfg->fd3.seg_thr.seg_bl_ma       = (128 + margin_th_p[9]  -  margin_th_m[9] );
		pCfg->fd3.seg_thr.seg_magenta     = (143 + margin_th_p[10] -  margin_th_m[10]);
		pCfg->fd3.seg_thr.seg_ma_re       = (158 + margin_th_p[11] -  margin_th_m[11]);

		pCfg->fd3.seg_thr.seg_value_black =  32;
		pCfg->fd3.seg_thr.seg_saturate    =  61;
		pCfg->fd3.seg_thr.seg_sdelta      =  30;
	}

	APR_HAL_SetFd3Config(pCfg);

	return RET_OK;
}

static void APR_FD3_UpdateLCensus(int *io_pArrLCensus,int *io_pArrMeanBlock,int i_nRefMean , int i_nflag)
{
	if(i_nflag == 1)
	{
			io_pArrLCensus[0] = (io_pArrMeanBlock[0] > i_nRefMean ) ? 1 : 0;
			io_pArrLCensus[1] = (io_pArrMeanBlock[1] > i_nRefMean ) ? 1 : 0;
			io_pArrLCensus[2] = (io_pArrMeanBlock[4] > i_nRefMean ) ? 1 : 0;
			io_pArrLCensus[3] = (io_pArrMeanBlock[5] > i_nRefMean ) ? 1 : 0;
	}
	else if(i_nflag == 2)
	{
			io_pArrLCensus[0] = (io_pArrMeanBlock[0] > i_nRefMean ) ? 1 : 0;
			io_pArrLCensus[1] = (io_pArrMeanBlock[1] > i_nRefMean ) ? 1 : 0;
			io_pArrLCensus[2] = (io_pArrMeanBlock[2] > i_nRefMean ) ? 1 : 0;
			io_pArrLCensus[3] = (io_pArrMeanBlock[3] > i_nRefMean ) ? 1 : 0;

	}
}

static void APR_FD3_UpdateRCensus(int *io_pArrRCensus,int *io_pArrMeanBlock,int i_nRefMean , int i_nflag)
{
	if(i_nflag == 1)
	{
		io_pArrRCensus[0] = (io_pArrMeanBlock[2] > i_nRefMean ) ? 1 : 0;
		io_pArrRCensus[1] = (io_pArrMeanBlock[3] > i_nRefMean ) ? 1 : 0;
		io_pArrRCensus[2] = (io_pArrMeanBlock[6] > i_nRefMean ) ? 1 : 0;
		io_pArrRCensus[3] = (io_pArrMeanBlock[7] > i_nRefMean ) ? 1 : 0;
	}
	else if(i_nflag == 2)
	{
		io_pArrRCensus[0] = (io_pArrMeanBlock[4] > i_nRefMean ) ? 1 : 0;
		io_pArrRCensus[1] = (io_pArrMeanBlock[5] > i_nRefMean ) ? 1 : 0;
		io_pArrRCensus[2] = (io_pArrMeanBlock[6] > i_nRefMean ) ? 1 : 0;
		io_pArrRCensus[3] = (io_pArrMeanBlock[7] > i_nRefMean ) ? 1 : 0;
	}
}


static void APR_FD3_SortArrayMax(int i_nElements,int *io_pArr1 , int *io_pArr2)
{
	int iter,i,swi_val,swi_idx;

	for(iter=0; iter<i_nElements-1; iter++)
	{
		for(i=iter+1; i<i_nElements; i++)
		{
			if(io_pArr1[iter] < io_pArr1[i])
			{
				swi_val      	= io_pArr1[iter];
				io_pArr1[iter]  = io_pArr1[i];
				io_pArr1[i] 	= swi_val;

				swi_idx      = io_pArr2[iter];
				io_pArr2[iter]   = io_pArr2[i];
				io_pArr2[i] = swi_idx;
			}
		}
	}
}

static void APR_FD3_UpdateThreshold(int change_segment)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_CFG_T *pCfg  = &apr_info.cfg;
	static int seg_flag = 0;
	static int seg_hsv_max_p = 0;
	static int seg_hsv_cnt_p = 0;
	static int seg_count = 0;
	int seg_di;

	int seg_hsv_max = pData->fd3.hsv_picture.pic_seg_hsv_max;
	int seg_hsv_cnt = pData->fd3.hsv_picture.pic_seg_hsv_count;
	int bMask = pData->fd3.bMask;

	FD3ALG("seg_flag, seg_hsv_max = %d / %d\n",seg_flag,seg_hsv_max);


	// seg[0] : current, seg[1] : current
	if (seg_flag == 0) seg_count = 0;
	else seg_count ++;

	seg_di = seg_hsv_max - seg_hsv_max_p;
	seg_di = (seg_di < 0) ? -seg_di : seg_di;
	seg_di = (seg_di == 11) ? 1 : seg_di;

	if (( seg_hsv_max < 12 ) && (seg_hsv_max_p < 12))
	{
		if (seg_flag == 0)
		{
			if (change_segment)
			{
				APR_FD3_ChangeThreshold(0);
				APR_FD3_ChangeThreshold(1);
				seg_flag = 1;
				seg_hsv_max_p = seg_hsv_max;
				seg_hsv_cnt_p = seg_hsv_cnt;
				FD3ALG("change_segment, seg_hsv_max = %d\n",seg_hsv_max);
			}
		}
		else if (seg_di > 1)
		{
			APR_FD3_ChangeThreshold(0);
			seg_flag = 0;
			FD3ALG("thaw0, seg_hsv_max = %d\n",seg_hsv_max);
		}
		else if ( (seg_di==1) && (change_segment==1))
		{
			seg_flag = 0;
			APR_FD3_ChangeThreshold(0);
			FD3ALG("thaw1, seg_hsv_max = %d\n",seg_hsv_max);
		}
	}
	else if ( (seg_flag==1) && (( seg_hsv_max > 12 ) || (seg_hsv_max_p > 12)) )
	{
		APR_FD3_ChangeThreshold(0);
		seg_flag = 0;
		FD3ALG("thaw2, seg_hsv_max = %d\n",seg_hsv_max);
	}

	if ( (seg_flag==1) && (bMask ==31) )
	{
		APR_FD3_ChangeThreshold(0);
		seg_flag = 0;
		FD3ALG("tha32, seg_hsv_max = %d\n",seg_hsv_max);
	}
}

static void APR_FD3_ExceptionHandling(LX_APR_FORMAT *io_peDetectFormat , APR_IMG_CLASS_T i_eImgClass)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_CFG_T *pCfg  = &apr_info.cfg;

	if(*io_peDetectFormat == LX_APR_FMT_3D_SS)
	{
		if((pData->tbr > 20) || (pData->tbr > pData->ssr))
		{
			*io_peDetectFormat = LX_APR_FMT_2D_2D;
			FD3PRT("### m1+hfd exception 1 ###\n");
			goto func_exit;
		}
		else if( (i_eImgClass == APR_IMG_CLASS_2D_WEAK_TB) || \
			(i_eImgClass == APR_IMG_CLASS_TB_HARD) || \
			(i_eImgClass == APR_IMG_CLASS_TB_WEAK))
		{
			*io_peDetectFormat = LX_APR_FMT_2D_2D;
			FD3PRT("### m1+hfd exception 4 ###\n");
		}
		else if(i_eImgClass == APR_IMG_CLASS_2D_HARD)
		{
			*io_peDetectFormat = LX_APR_FMT_UNKNOWN;
			FD3PRT("### m1+hfd exception 4 -- 1  ###\n");
		}
	}
	else if(*io_peDetectFormat == LX_APR_FMT_3D_TB)
	{
		if((pData->ssr > 20) || (pData->ssr > pData->tbr))
		{
			*io_peDetectFormat = LX_APR_FMT_2D_2D;
			FD3PRT("### m1+hfd exception 2 ###\n");
			goto func_exit;
		}
		else if( (i_eImgClass == APR_IMG_CLASS_2D_WEAK_SS) || \
				(i_eImgClass == APR_IMG_CLASS_SS_HARD) || \
				(i_eImgClass == APR_IMG_CLASS_SS_WEAK))
		{
			*io_peDetectFormat = LX_APR_FMT_2D_2D;
			FD3PRT("### m1+hfd exception 3 ###\n");
		}
		else if(i_eImgClass == APR_IMG_CLASS_2D_HARD)
		{
			*io_peDetectFormat = LX_APR_FMT_UNKNOWN;
			FD3PRT("### m1+hfd exception 3 -- 1  ###\n");
		}
	}

func_exit:
	return ;
}

static void APR_FD3_CrossCorrCheck(LX_APR_FORMAT *io_peDetectFormat, APR_IMG_CLASS_VAR_T *i_pstImgClassVar)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_CFG_T *pCfg  = &apr_info.cfg;
	int diff_corr_tb[2];
	int diff_corr_ss[2];

	int cross_corr_th[2];

	int large_corr_tb[2] = {0,};
	int large_corr_ss[2] = {0,};

	diff_corr_tb[0] = ( (int)pData->fd3.corr.tb[0] - (int)pData->fd3.corr.tb[2]);
	diff_corr_tb[1] = ( (int)pData->fd3.corr.tb[1] - (int)pData->fd3.corr.tb[3]);

	diff_corr_ss[0] = ( (int)pData->fd3.corr.ss[0] - (int)pData->fd3.corr.ss[2]);
	diff_corr_ss[1] = ( (int)pData->fd3.corr.ss[1] - (int)pData->fd3.corr.ss[3]);

	diff_corr_tb[0] = (diff_corr_tb[0] < 0) ? -diff_corr_tb[0] : diff_corr_tb[0];
	diff_corr_tb[1] = (diff_corr_tb[1] < 0) ? -diff_corr_tb[1] : diff_corr_tb[1];
	diff_corr_ss[0] = (diff_corr_ss[0] < 0) ? -diff_corr_ss[0] : diff_corr_ss[0];
	diff_corr_ss[1] = (diff_corr_ss[1] < 0) ? -diff_corr_ss[1] : diff_corr_ss[1];

	large_corr_tb[0] = (pData->fd3.corr.tb[0] >  pData->fd3.corr.tb[2]) ? pData->fd3.corr.tb[0] : pData->fd3.corr.tb[1];
	large_corr_ss[0] = (pData->fd3.corr.ss[0] >  pData->fd3.corr.ss[2]) ? pData->fd3.corr.ss[0] : pData->fd3.corr.ss[1];

	FD3DBG("diff_tb[0..1] : %d   %d\n",diff_corr_tb[0],diff_corr_tb[1]);
	FD3DBG("diff_ss[0..1] : %d   %d\n",diff_corr_ss[0],diff_corr_ss[1]);


	if (i_pstImgClassVar->cross_corr_en == 1)
	{
		if (*io_peDetectFormat == LX_APR_FMT_3D_SS)
		{
			cross_corr_th[0] = large_corr_tb[0] < 100 ? i_pstImgClassVar->cross_corr_th0 : i_pstImgClassVar->cross_corr_th1;
			cross_corr_th[1] = large_corr_tb[1] < 100 ? i_pstImgClassVar->cross_corr_th0 : i_pstImgClassVar->cross_corr_th1;

			if (diff_corr_tb[0] > cross_corr_th[0] || diff_corr_tb[1] > cross_corr_th[1])
			{
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
			}
		}
		else if (*io_peDetectFormat == LX_APR_FMT_3D_TB)
		{
			cross_corr_th[0] = large_corr_ss[0] < 100 ? i_pstImgClassVar->cross_corr_th0 : i_pstImgClassVar->cross_corr_th1;
			cross_corr_th[1] = large_corr_ss[1] < 100 ? i_pstImgClassVar->cross_corr_th0 : i_pstImgClassVar->cross_corr_th1;

			if (diff_corr_ss[0] > cross_corr_th[0] || diff_corr_ss[1] > cross_corr_th[1])
			{
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
			}
		}
	}
}

static void APR_FD3_GetFinalCorr(LX_APR_FORMAT *io_peDetectFormat , APR_IMG_CLASS_VAR_T *i_pstImgClassVar , APR_BASIC_ALGOPARAM_T *io_pstBasicAlgoParam)
{
	int case_flag = 0;

	if((io_pstBasicAlgoParam->cnt_tb == 0) && (io_pstBasicAlgoParam->cnt_ss ==0)) case_flag = 0;
	else if ((io_pstBasicAlgoParam->cnt_tb == 0)) case_flag = 1;
	else if ((io_pstBasicAlgoParam->cnt_ss == 0)) case_flag = 2;
	else case_flag = 3;

	switch (case_flag)//15
	{
		case 0:
		{
			if (io_pstBasicAlgoParam->cnt2_ss > i_pstImgClassVar->var_valid_blk)
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
			else if(io_pstBasicAlgoParam->sum_tb > i_pstImgClassVar->corr_th * io_pstBasicAlgoParam->cnt_tb)
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
			else
				*io_peDetectFormat = LX_APR_FMT_2D_2D;

			io_pstBasicAlgoParam->cnt_idx    = io_pstBasicAlgoParam->cnt_ss;
			io_pstBasicAlgoParam->final_corr = io_pstBasicAlgoParam->sum_ss;
		}
		break;
		case 1:
		{
			if (io_pstBasicAlgoParam->cnt2_ss > i_pstImgClassVar->var_valid_blk){
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
				io_pstBasicAlgoParam->change_segment = 1;
			}
			else if (io_pstBasicAlgoParam->sum_tb > i_pstImgClassVar->corr_th* io_pstBasicAlgoParam->cnt_tb)
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
			else
				*io_peDetectFormat = LX_APR_FMT_3D_SS;

			io_pstBasicAlgoParam->cnt_idx	= io_pstBasicAlgoParam->cnt_ss;
			io_pstBasicAlgoParam->final_corr	= io_pstBasicAlgoParam->sum_ss;
		}
		break;
		case 2:
		{
			if (io_pstBasicAlgoParam->cnt2_tb > i_pstImgClassVar->var_valid_blk ) {
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
				io_pstBasicAlgoParam->change_segment = 1;
			}
			else if (io_pstBasicAlgoParam->sum_ss > i_pstImgClassVar->corr_th * io_pstBasicAlgoParam->cnt_ss)
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
			else *io_peDetectFormat = LX_APR_FMT_3D_TB;

			io_pstBasicAlgoParam->cnt_idx    = io_pstBasicAlgoParam->cnt_tb;
			io_pstBasicAlgoParam->final_corr = io_pstBasicAlgoParam->sum_tb;
		}
		break;
		default :
		{
			if (io_pstBasicAlgoParam->sum_tb * io_pstBasicAlgoParam->cnt_ss > io_pstBasicAlgoParam->sum_ss * io_pstBasicAlgoParam->cnt_tb)
			{
				if (io_pstBasicAlgoParam->cnt2_tb > i_pstImgClassVar->var_valid_blk ) {
					*io_peDetectFormat = LX_APR_FMT_2D_2D;
					io_pstBasicAlgoParam->change_segment = 1;
				}
				else if (io_pstBasicAlgoParam->sum_ss > i_pstImgClassVar->corr_th * io_pstBasicAlgoParam->cnt_ss)
					*io_peDetectFormat = LX_APR_FMT_2D_2D;
				else *io_peDetectFormat = LX_APR_FMT_3D_TB;

				io_pstBasicAlgoParam->cnt_idx    = io_pstBasicAlgoParam->cnt_tb;
				io_pstBasicAlgoParam->final_corr = io_pstBasicAlgoParam->sum_tb;
			}
			else
			{
				if (io_pstBasicAlgoParam->cnt2_ss > i_pstImgClassVar->var_valid_blk) {
					*io_peDetectFormat = LX_APR_FMT_2D_2D;
					io_pstBasicAlgoParam->change_segment = 1;
				}
				else if (io_pstBasicAlgoParam->sum_tb > i_pstImgClassVar->corr_th * io_pstBasicAlgoParam->cnt_tb)
					*io_peDetectFormat = LX_APR_FMT_2D_2D;
				else *io_peDetectFormat = LX_APR_FMT_3D_SS;

				io_pstBasicAlgoParam->cnt_idx    = io_pstBasicAlgoParam->cnt_ss;
				io_pstBasicAlgoParam->final_corr = io_pstBasicAlgoParam->sum_ss;
			}
		}
		break;
	}
}

static void APR_FD3_VideoModeFirstDecision(LX_APR_FORMAT *io_peDetectFormat,APR_IMG_CLASS_VAR_T *i_pstImgClassVar,APR_BASIC_ALGOPARAM_T *io_pstBasicAlgoParam)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_CFG_T *pCfg  = &apr_info.cfg;
	int bMask = pData->fd3.bMask;
	int tmp_idx;
	int i=0;

	// condition check (SS)
	for (i=0; i<4; i++)
	{
		tmp_idx = (i<2) ? i : i+2;

		if (pData->fd3.corr.ss_wnd_info[i] == 0)
		{
			io_pstBasicAlgoParam->cnt1_ss++;
			if ( (int)pData->fd3.blk_stat.s_dev[tmp_idx]   >= i_pstImgClassVar->var_th && \
				 ((int)pData->fd3.blk_stat.s_dev[tmp_idx+2] >= i_pstImgClassVar->var_th) )
			{
				io_pstBasicAlgoParam->cnt_ss++;
				io_pstBasicAlgoParam->sum_ss += (int)pData->fd3.corr.ss[i];
			}
		}

		if (pData->fd3.corr.ss_wnd_info[i] == 2) io_pstBasicAlgoParam->cnt2_ss++;
	}

	// condition check (TB)
	for (i=0; i<4; i++)
	{
		tmp_idx = i;

		if (pData->fd3.corr.tb_wnd_info[i] == 0)
		{
			io_pstBasicAlgoParam->cnt1_tb++;

#if 0
			if ( ((int)pData->fd3.blk_stat.s_dev[tmp_idx]   >= pCheck->var_th) && \
				 ((int)pData->fd3.blk_stat.s_dev[tmp_idx+4] >= pCheck->var_th) )
			{
				io_pstBasicAlgoParam->cnt_tb++;
				io_pstBasicAlgoParam->sum_tb += (int)pData->fd3.corr.tb[i];
			}
#else

			io_pstBasicAlgoParam->cnt_tb++;
			io_pstBasicAlgoParam->sum_tb += (int)pData->fd3.corr.tb[i];
#endif

		}

		if (pData->fd3.corr.tb_wnd_info[i] == 2) io_pstBasicAlgoParam->cnt2_tb++;
	}

	io_pstBasicAlgoParam->sum_ss = (io_pstBasicAlgoParam->cnt_ss == 0) ? 0 : io_pstBasicAlgoParam->sum_ss;
	io_pstBasicAlgoParam->sum_tb = (io_pstBasicAlgoParam->cnt_tb == 0) ? 0 : io_pstBasicAlgoParam->sum_tb;


	FD3DBG("sum_ss : %d sum_tb : %d\n",io_pstBasicAlgoParam->sum_ss,io_pstBasicAlgoParam->sum_tb );

	// format decision based on correlation
	if((io_pstBasicAlgoParam->cnt1_tb < 2) && (io_pstBasicAlgoParam->cnt1_ss < 2)) {
		*io_peDetectFormat = LX_APR_FMT_2D_2D;
		if (i_pstImgClassVar->candi_blk_thaw) io_pstBasicAlgoParam->change_segment = 1;
		FD3ALG("SEG_ALT[0] : cnt1_tb, cnt1_ss = %d,%d\n",io_pstBasicAlgoParam->cnt1_tb,io_pstBasicAlgoParam->cnt1_ss);
	}
	else if ((bMask == 31) && (io_pstBasicAlgoParam->cnt_tb  < 2) && (io_pstBasicAlgoParam->cnt_ss  < 2)) *io_peDetectFormat = LX_APR_FMT_UNKNOWN;
	else if ((io_pstBasicAlgoParam->cnt_tb == 0) && (io_pstBasicAlgoParam->cnt_ss == 0)) *io_peDetectFormat = LX_APR_FMT_2D_2D;
	else{
		APR_FD3_GetFinalCorr(io_peDetectFormat , i_pstImgClassVar ,io_pstBasicAlgoParam);
		APR_FD3_CrossCorrCheck(io_peDetectFormat , i_pstImgClassVar);
	}

	pCfg->hfd_1_fmt = *io_peDetectFormat;

	FD3DBG("1st : cnt_ss/cnt1_ss/cnt2_ss - cnt_tb/cnt1_tb/cnt2_tb  %d/%d/%d - %d/%d/%d , result %d\n",\
			io_pstBasicAlgoParam->cnt_ss,io_pstBasicAlgoParam->cnt1_ss,io_pstBasicAlgoParam->cnt2_ss,io_pstBasicAlgoParam->cnt_tb,io_pstBasicAlgoParam->cnt1_tb,io_pstBasicAlgoParam->cnt2_tb,*io_peDetectFormat);
	if (io_pstBasicAlgoParam->final_corr != io_pstBasicAlgoParam->sum_tb) FD3DBG("Error : 1st Step\n");
}


static void  APR_FD3_VideoModeThirdDecision(LX_APR_FORMAT *io_peDetectFormat,APR_IMG_CLASS_VAR_T *i_pstImgClassVar , APR_BASIC_ALGOPARAM_T *i_pstBasicAlgoParam, int *i_pArrScan3d )
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_CFG_T *pCfg  = &apr_info.cfg;
	int bMask = pData->fd3.bMask;
	int tmp_idx;
	int mean_d[4], mean_d1[4];
	int tmp_mean_a, tmp_mean_b;
	int match_cor_mean = 1;
	int match_max_d    = 0;
	int di, di_a;
	int i=0;

	if (*io_peDetectFormat == LX_APR_FMT_3D_TB)
	{
		for (i=0; i<4; i++)
		{
			tmp_idx = i;
			tmp_mean_a = pData->fd3.blk_stat.mean[tmp_idx  ];
			tmp_mean_b = pData->fd3.blk_stat.mean[tmp_idx+4];

			mean_d[i] = (tmp_mean_a > tmp_mean_b) ? (tmp_mean_a - tmp_mean_b) : (tmp_mean_b - tmp_mean_a);
		}

		for (i=0; i<4; i++) mean_d1[i] = mean_d[i_pArrScan3d[i]];
	}
	else if (*io_peDetectFormat == LX_APR_FMT_3D_SS)
	{
		for (i=0; i<4; i++)
		{
			tmp_idx = (i<2) ? i : i+2;
			tmp_mean_a = pData->fd3.blk_stat.mean[tmp_idx  ];
			tmp_mean_b = pData->fd3.blk_stat.mean[tmp_idx+2];

			mean_d[i] = (tmp_mean_a > tmp_mean_b) ? (tmp_mean_a - tmp_mean_b) : (tmp_mean_b - tmp_mean_a);
		}

		for (i=0; i<4; i++) mean_d1[i] = mean_d[i_pArrScan3d[i]];
	}
	else
	{
		for (i=0; i<4; i++) mean_d1[i] = 0;
	}

	match_cor_mean = 1;
	match_max_d    = 0;

	FD3DBG("\nmean_d1[0..3] : %d/%d/%d/%d \n",mean_d1[0],mean_d1[1],mean_d1[2],mean_d1[3]);


	for (i=3; i>0; i--)
	{
		di   = mean_d1[i] - mean_d1[i-1];
		di_a = (di<0) ? -di : di;

		if (di_a > match_max_d) match_max_d = di_a;
		if (di < -20*16) match_cor_mean = 0;
	}

	if ( (*io_peDetectFormat != LX_APR_FMT_2D_2D) && (i_pstBasicAlgoParam->final_corr < i_pstImgClassVar->corr_th * i_pstBasicAlgoParam->cnt_idx) && (bMask == 31) )
	{
		if (!match_cor_mean)
			*io_peDetectFormat = LX_APR_FMT_2D_2D;
		else if ( (i_pstBasicAlgoParam->final_corr > i_pstImgClassVar->final_corr_th* i_pstBasicAlgoParam->cnt_idx) && (match_max_d < i_pstImgClassVar->mean_tolerance_th * 16) )
			*io_peDetectFormat = *io_peDetectFormat;
		else
			*io_peDetectFormat += 16;
		FD3DBG("3rd : match_cor_mean/final_corr/match_max_d  %d/%d/%d ,  result %d\n",\
				match_cor_mean, i_pstBasicAlgoParam->final_corr, match_max_d, *io_peDetectFormat);
	}

	pCfg->hfd_3_1_fmt = *io_peDetectFormat;
}


static void APR_FD3_Verify3DSSFormat(LX_APR_FORMAT *io_peDetectFormat,int *i_pArrSegMax , int *i_pArrSegIdx)
{
	APR_CFG_T *pCfg  = &apr_info.cfg;
	int seg_max_sum[2] = {0, 0};
	int seg_max_cnt2 = 0;
	int seg_max_cnt3 = 0;
	int tmp_b[2] = {0, 0};
	int tmp_b_sum[2] = {0,0};
	int img_width = pCfg->in_win_x;
	int img_height = pCfg->in_win_y;
	//int tmp_b_sum_th0, tmp_b_sum_th1;
	int tmp_b_th0 = 0, tmp_b_th1 = 0;
	int tmp_b_sum_th0 = 0, tmp_b_sum_th1 = 0;
	int i=0;
	for (i=0; i<4; i++)
	{
		if (i_pArrSegIdx[i] == 18) seg_max_cnt2++;
		else if (i_pArrSegIdx[i] == 0) seg_max_cnt3++;
	}

	if (i_pArrSegIdx[0] == 15) seg_max_cnt3++;
	if (i_pArrSegIdx[1] == 15) seg_max_cnt3++;

	if (seg_max_cnt2 == 4 || seg_max_cnt3 == 4 )
	{
		seg_max_sum[0] = i_pArrSegMax[0] + i_pArrSegMax[1];
		seg_max_sum[1] = i_pArrSegMax[2] + i_pArrSegMax[3];

		if (seg_max_cnt2 ==4)
		{
			tmp_b_sum_th0 = 133;
			tmp_b_sum_th1 = 141;
			tmp_b_th0 = 220;
			tmp_b_th1 = 250;
		}
		else if (seg_max_cnt3 ==4)
		{
			tmp_b_sum_th0 = 90;
			tmp_b_sum_th1 = 145;
			tmp_b_th0 = 208;
			tmp_b_th1 = 300;
		}

		tmp_b_sum[0] = (tmp_b_sum_th0*img_width*img_height)>>11;
		tmp_b_sum[1] = (tmp_b_sum_th1*img_width*img_height)>>11;



		tmp_b[0] = (tmp_b_th0*seg_max_sum[1]) >> 8;
		tmp_b[1] = (tmp_b_th1*seg_max_sum[1]) >> 8;

		FD3DBG("seg_max_sum[0] : %d  seg_max_sum[1] : %d\n",seg_max_sum[0],seg_max_sum[1]);
		FD3DBG("tmp_b[0]       : %d  tmp_b[1]       : %d\n",tmp_b[0],tmp_b[1]);
		FD3DBG("tmp_b_sum[0]   : %d  tmp_b_sum[1]   : %d\n",tmp_b_sum[0],tmp_b_sum[1]);

		if ( (seg_max_sum[1] > tmp_b_sum[0]) && (seg_max_sum[1] < tmp_b_sum[1]) )
		{
			FD3DBG("1st pass\n");
			if ( (seg_max_sum[0] > tmp_b[0]) && (seg_max_sum[0] < tmp_b[1]) )
			{
				FD3DBG("1st :  scene detect!!!\n");
				*io_peDetectFormat = LX_APR_FMT_2D_2D;
			}
		}
	}
}

static void APR_FD3_3DFmtDetectAlgo1(LX_APR_FORMAT *io_peDetectFormat , APR_IMG_CLASS_VAR_T *i_pstImgClassVar)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_CFG_T *pCfg  = &apr_info.cfg;
	int idx1=1,idx2=2;
	int seg_idx[4], seg_max[4];
	int seg_max_di[2];
	int seg_idx_flag[2] = {0,0}; // 0 : HSV, 1 : MONO
	int dom_seg_chk_th[2];
	int i;

	for (i=0; i<4; i++)
	{
		seg_idx[i] = pData->fd3.hsv_blk.seg_hsv_max[i];
		seg_max[i] = pData->fd3.hsv_blk.seg_hsv_count[i];
	}

	FD3DBG("seg_idx[0...3] : %d/%d/%d/%d\n",seg_idx[0],seg_idx[1],seg_idx[2],seg_idx[3]);

	if (*io_peDetectFormat == LX_APR_FMT_3D_SS || *io_peDetectFormat == LX_APR_FMT_3D_TB)
	{
		if(*io_peDetectFormat == LX_APR_FMT_3D_TB){
			idx1=2;idx2=1;
		}

		seg_idx_flag[0] = (seg_idx[0] < 12) ? 0 : 1;
		seg_idx_flag[1] = (seg_idx[idx2] < 12) ? 0 : 1;

		if (seg_idx[0]==seg_idx[idx1])
		{
			seg_max_di[0] = (seg_max[0]>seg_max[idx1]) ? (seg_max[0] - seg_max[idx1]) : (seg_max[idx1] - seg_max[0]);
		}
		else if (( seg_idx[0]>=12) || (seg_idx[idx1] >= 12))
			seg_max_di[0] = -2;
		else
			seg_max_di[0] = -1;

		if (seg_idx[idx2]==seg_idx[3])
			seg_max_di[1] = (seg_max[idx2]>seg_max[3]) ? (seg_max[idx2] - seg_max[3]) : (seg_max[3] - seg_max[idx2]);
		else if (( seg_idx[idx2]>=12) || (seg_idx[3] >= 12))
			seg_max_di[1] = -2;
		else
			seg_max_di[1] = -1;
	}

	else
		seg_max_di[0] = seg_max_di[1] = -100;

	FD3DBG("seg_di[0...1] : %d/%d\n",seg_max_di[0],seg_max_di[1]);

	dom_seg_chk_th[0] = (seg_idx_flag[0] == 0) ? i_pstImgClassVar->dom_seg_chk_th1 : i_pstImgClassVar->dom_seg_chk_th0;
	dom_seg_chk_th[1] = (seg_idx_flag[1] == 0) ? i_pstImgClassVar->dom_seg_chk_th1 : i_pstImgClassVar->dom_seg_chk_th0;

	if ( (seg_idx[0] != 0) && (seg_max_di[0] > dom_seg_chk_th[0]))
	{
		*io_peDetectFormat = LX_APR_FMT_2D_2D;
	}
	else if ( (seg_idx[1] != 0) && (seg_max_di[1] > dom_seg_chk_th[1]))
	{
		*io_peDetectFormat = LX_APR_FMT_2D_2D;
	}

#if 1
	if(*io_peDetectFormat == LX_APR_FMT_3D_SS) {
		 APR_FD3_Verify3DSSFormat(io_peDetectFormat,seg_max , seg_idx);
	}
#endif
}


static void APR_FD3_3DFmtDetectAlgo2(LX_APR_FORMAT *io_pe3DFormat,APR_BASIC_ALGOPARAM_T *io_pstBasicAlgoParam)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_THR_T *pThr  = &apr_info.thr;
	APR_CFG_T *pCfg  = &apr_info.cfg;
	UINT32 blk_mean[8];

	int L_census[4];
	int R_census[4];
	int ref_mean0,ref_mean1;

	int m=0,i=0;
	int blk_mean0[4], blk_mean1[4];
	int blk_idx0[4] = {0,1,2,3}, blk_idx1[4]={0,1,2,3};

	int Hamming_Distance = 0;
	int bMask = pData->fd3.bMask;
	BOOLEAN bSSCond = FALSE;
	BOOLEAN bTBCond = FALSE;
	int n3DFmtFlag = 0;

	memset(L_census, 0, sizeof(int)*4);
	memset(R_census, 0, sizeof(int)*4);

#if 0
	for (m=0; m<8; m++)
	{
		blk_mean[m] = pData->fd3.blk_stat.mean[m];
	}
#else
	memcpy(&blk_mean[0],&pData->fd3.blk_stat.mean[0],sizeof(blk_mean[0])*8);
#endif

	memset(blk_mean0, 0, sizeof(int)*4);
	memset(blk_mean1, 0, sizeof(int)*4);
	memset(blk_idx0, 0, sizeof(int)*4);
	memset(blk_idx1, 0, sizeof(int)*4);

	if(*io_pe3DFormat == LX_APR_FMT_3D_SS && io_pstBasicAlgoParam->cnt2_ss == 0)
		bSSCond = TRUE;
	if(*io_pe3DFormat == LX_APR_FMT_3D_TB && io_pstBasicAlgoParam->cnt2_ss == 0)
		bTBCond = TRUE;

	if (bMask == 31){
		if (bSSCond	|| bTBCond){
			if(bSSCond){
				for(m=0;m<4;m++){
					blk_mean0[m] = (m>1) ? blk_mean[m+2] : blk_mean[m];
					blk_mean1[m] = (m>1) ? blk_mean[m+4] : blk_mean[m+2];
				}

				n3DFmtFlag = 1;
			}
			else if(bTBCond){
				for(m=0;m<4;m++){
					blk_mean0[m] = blk_mean[m];
					blk_mean1[m] = blk_mean[m+4];
				}

				n3DFmtFlag = 2;
			}

			// sorting
			APR_FD3_SortArrayMax(4,&blk_mean0[0],&blk_idx0[0]);
			APR_FD3_SortArrayMax(4,&blk_mean1[0],&blk_idx1[0]);

			FD3DBG("blk_idx = %d%d%d%d / %d%d%d%d \n",
					blk_idx0[0], blk_idx0[1], blk_idx0[2], blk_idx0[3],
					blk_idx1[0], blk_idx1[1], blk_idx1[2], blk_idx1[3]);

			ref_mean0 = blk_mean0[3];
			ref_mean0 += 320; // 20(integer)

			APR_FD3_UpdateLCensus(&L_census[0],&blk_mean[0],ref_mean0,n3DFmtFlag);

			ref_mean1 = blk_mean1[3];
			ref_mean1 += 320; // 20(integer)

			APR_FD3_UpdateRCensus(&R_census[0],&blk_mean[0],ref_mean1,n3DFmtFlag);

			FD3DBG("Hamming_Distance = ");
			for (m=0; m<4; m++)
			{
				if (L_census[m] == R_census[m]) Hamming_Distance += 1;
				FD3DBG("%d ",(L_census[m] == R_census[m])?1:0);
			}

			FD3DBG("\n");

			if (Hamming_Distance < 3) *io_pe3DFormat = LX_APR_FMT_2D_2D;
		}
	}
}


static void APR_FD3_VideoModeCorrValue(LX_APR_FORMAT *io_peDetectFormat , int *i_pArrScan3d)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_THR_T *pThr  = &apr_info.thr;
	APR_CFG_T *pCfg  = &apr_info.cfg;
	int i ;
	int corr_3d[4] = {0,};
	int third_cor_th      = pThr->fd3.corr_3rd;

	if ((*io_peDetectFormat == LX_APR_FMT_3D_TB) || (*io_peDetectFormat == LX_APR_FMT_3D_SS)){
		if (*io_peDetectFormat == LX_APR_FMT_3D_TB){
			for (i=0; i<4; i++) corr_3d[i] = (pData->fd3.corr.tb_wnd_info[i]==0) ? pData->fd3.corr.tb[i] : -1;
		}
		else{
			for (i=0; i<4; i++) corr_3d[i] = (pData->fd3.corr.ss_wnd_info[i]==0) ? pData->fd3.corr.ss[i] : -1;
		}

		FD3DBG("2nd : corr_3d[0..3] = %d %d %d %d \n",corr_3d[0],corr_3d[1],corr_3d[2],corr_3d[3]);

		APR_FD3_SortArrayMax(4,&corr_3d[0],&i_pArrScan3d[0]);

		FD3DBG("2nd(A) : corr_3d[0..3] = %d %d %d %d \n",corr_3d[0],corr_3d[1],corr_3d[2],corr_3d[3]);

		if (corr_3d[2] < 0){
			corr_3d[2] = (corr_3d[1] < 0) ? corr_3d[0] : corr_3d[1];
		}

		if (corr_3d[2] < third_cor_th){
			*io_peDetectFormat = LX_APR_FMT_2D_2D;
		}
	}

	pCfg->hfd_2_fmt = *io_peDetectFormat;

	FD3DBG("2nd : corr_3d[2]/third_cor_th  %d/%d , result %d\n", corr_3d[2],third_cor_th,*io_peDetectFormat);

	if (*io_peDetectFormat != LX_APR_FMT_3D_TB) FD3DBG("Error : 2nd step!\n");
}


static int APR_FD3_SubtitleMode(LX_APR_FORMAT *result)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_THR_T *pThr  = &apr_info.thr;
	APR_CFG_T *pCfg  = &apr_info.cfg;

	int i;

	int final_score_ss = 0; // score (SS) - sum of valid corr
	int final_score_tb = 0; // score (TB) - sum of valid corr

	int final_cnt_ss = 0;   // number of valid blk (SS)
	int final_cnt_tb = 0;   // number of valid blk (TB)

	int final_th_ss;        // decision threshold (SS)
	int final_th_tb;        // decision threshold (TB)

	for (i=0; i<4; i++)
	{
		if (!pData->fd3.corr.ss_wnd_info[i])
		{
			final_cnt_ss += 1;
			final_score_ss += pData->fd3.corr.ss[i];
		}

		if (!pData->fd3.corr.tb_wnd_info[i])
		{
			final_cnt_tb += 1;
			final_score_tb += pData->fd3.corr.tb[i];
		}
	}

	final_th_ss = pThr->fd3.subtitle * final_cnt_ss;
	final_th_tb = pThr->fd3.subtitle * final_cnt_tb;

	// No valid blk
	if (!final_cnt_ss) final_score_ss = -1;
	if (!final_cnt_tb) final_score_tb = -1;

	// format decision
	if ((!final_cnt_ss) && (!final_cnt_tb))
	{
		*result = LX_APR_FMT_UNKNOWN;
	}
	else
	{
		if((final_score_ss >= final_th_ss) && (final_score_tb >= final_th_tb))
			*result = LX_APR_FMT_UNKNOWN;
		else if (final_score_ss >= final_th_ss)
			*result = LX_APR_FMT_3D_SS;
		else if (final_score_tb >= final_th_tb)
			*result = LX_APR_FMT_3D_TB;
		else
			*result = LX_APR_FMT_2D_2D;

		// Exception for CG case
		if((*result == LX_APR_FMT_3D_SS) && (pData->tbr > 20))
		{
			FD3PRT("### m1+hfd  tbr[%d] subt exception ###\n", pData->tbr);
			*result = LX_APR_FMT_2D_2D;
		}
		else if((*result == LX_APR_FMT_3D_TB) && (pData->ssr > 20))
		{
			FD3PRT("### m1+hfd  ssr[%d] subt exception ###\n", pData->ssr);
			*result = LX_APR_FMT_2D_2D;
		}
	}

	FD3DBG("SubtitleMode\n");
	FD3DBG("final_cnt ss-tb[%d-%d] | final_score/th ss/th[%d/%d] tb/th[%d/%d] | result[%d]\n", \
	   final_cnt_ss, final_cnt_tb, final_score_ss, final_th_ss, final_score_tb, final_th_tb, *result);
	FD3MSG("SubtitleMode : result[%d]\n", *result);

	return RET_OK;
}

static int APR_FD3_VideoMode(LX_APR_FORMAT *result)
{
	APR_DTA_T *pData = &apr_info.dta;
	APR_CFG_T *pCfg  = &apr_info.cfg;

	LX_APR_FORMAT 			detect_format;
	LX_APR_FORMAT 			current_format;
	APR_IMG_CLASS_T 		m1_img_class;
	APR_IMG_CLASS_VAR_T 	stImgClassVar = {0,};
	APR_BASIC_ALGOPARAM_T 	stBasicAlgoParam = {0,};

	int i;
	int scan_3d[4] = {0, 1, 2, 3};

	int tpd_flag = 0;

	if(pData->tpd >= 235)	tpd_flag = 1;

	//Harish: We are not using current_format [below 2 statement are not required]
	if(pCfg->cap.enb)
		current_format = pCfg->fmt_before_vote[APR_METHOD_2];
	else
		current_format = pCfg->fmt_before_vote[APR_METHOD_1];

	m1_img_class = pCfg->img_class;

	//Load the default Image Setting based on image type
	memcpy(&stImgClassVar,&g_sImgFormatToVarMap[m1_img_class],sizeof(APR_IMG_CLASS_VAR_T));

	stImgClassVar.dom_seg_chk_th0 = (pCfg->in_win_x * pCfg->in_win_y * 3)>>9; // 3/32 * blk_size
	stImgClassVar.dom_seg_chk_th1 = (pCfg->in_win_x * pCfg->in_win_y * 3)>>8; // 3/32 * blk_size

	stImgClassVar.cross_corr_en = 0; // set to '0'

	FD3DBG("VideoMode\n");
	FD3DBG("var_th/corr_th/third_cor_th  %d/%d/%d\n",stImgClassVar.var_th,stImgClassVar.corr_th,stImgClassVar.third_cor_th);

	for(i=0;i<4;i++)
	{
		FD3DBG("Corr[%d] : ss/ss_wnd tb/tb_wnd - 0x%02X/0x%02X  0x%02X/0x%02X\n",\
							i, pData->fd3.corr.ss[i], pData->fd3.corr.ss_wnd_info[i],\
							pData->fd3.corr.tb[i], pData->fd3.corr.tb_wnd_info[i]);
	}

	///////////////////////////////////////////////////////////////////////////
	// 1st decision - basic
	///////////////////////////////////////////////////////////////////////////
	APR_FD3_VideoModeFirstDecision(&detect_format, &stImgClassVar, &stBasicAlgoParam);

	///////////////////////////////////////////////////////////////////////////
	// 2nd decision - 3rd largest correlation value
	///////////////////////////////////////////////////////////////////////////
	APR_FD3_VideoModeCorrValue(&detect_format , &scan_3d[0]);

	///////////////////////////////////////////////////////////////////////////
	// 3rd decision - mean-diff order and corr order
	///////////////////////////////////////////////////////////////////////////
	APR_FD3_VideoModeThirdDecision(&detect_format, &stImgClassVar, &stBasicAlgoParam, &scan_3d[0]);

	//algorithm 1
	if (stImgClassVar.dom_seg_chk_en==1){
		APR_FD3_3DFmtDetectAlgo1(&detect_format, &stImgClassVar);
	}

	//algorithm 2 [Pass I/O parameter of Algo 1
	if (stImgClassVar.blk_mean_chk_en == 1)	{
		APR_FD3_3DFmtDetectAlgo2(&detect_format,&stBasicAlgoParam);
	}

	pCfg->hfd_3_fmt = detect_format;

	// Exception for CG case
	APR_FD3_ExceptionHandling(&detect_format , m1_img_class);

	// Exception end
	if(tpd_flag)
		*result = LX_APR_FMT_2D_2D;
	else
		*result = (detect_format >= 16) ? LX_APR_FMT_UNKNOWN : detect_format;

	//FD3MSG("VideoMode : result[%d]\n", *result);
	FD3DBG("VideoMode : result[%d] tpd_flag[%d]\n", *result, tpd_flag);

	APR_FD3_UpdateThreshold(stBasicAlgoParam.change_segment);

	return RET_OK;
}

int APR_FD3_Detect3D(void)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg  = &apr_info.cfg;
	APR_DTA_T *pData = &apr_info.dta;
	LX_APR_FORMAT m2_fmt = LX_APR_FMT_2D_2D;

	FD3DBG("\n\nStart]]] FD3 cfg : sampling[%d](0:all,1:2line) , scan[%d](0:P,1:I) , color[%d](0:420,1:422:2:444)\n",\
			pCfg->fd3.sampling, pCfg->fd3.scan, pCfg->fd3.color);
	FD3DBG("status  : init_count[0x%X] suc_fail_history[0x%X]\n", \
			pData->fd3.status.init_count, pData->fd3.status.suc_fail_history);
	FD3DBG("Image Class by method 1 :  %d\n", pCfg->img_class);
	FD3DBG("  (0:TP,1:2DHARD,2:2DWSS,3:2DWTB,4:SSHARD,5:SSWEAK,6:TBHARD,7:TBWEAK)\n");
	do {
		UINT32 alt_seg = 0;
		if ( pData->tpd < 210 )
	   	{
			alt_seg = 3;
			APR_HAL_SetFd3SubtConfig(pCfg, alt_seg);
		}

		if(pData->fd3.scene_type)
		{
			ret = APR_FD3_SubtitleMode(&m2_fmt);
		}
		else
		{
			if ( (pData->tpd > 210) && (pData->fd3.bMask != 31) )
			{
				alt_seg = pData->fd3.bMask;
				APR_HAL_SetFd3SubtConfig(pCfg, alt_seg);
			}

			ret = APR_FD3_VideoMode(&m2_fmt);
		}
		pCfg->fd3_fmt = m2_fmt;
		FD3DBG("SubtConfig : alt_seg [%d]\n", alt_seg);
	} while(0);

	FD3DBG("\nAlgorithm end] FD3 result : %d (0:2D,4:SS,5:TB)\n\n", m2_fmt);
	FD3DBG("###########################################################################\n");
	if(++g_msg_cnt==9) g_msg_cnt = 0;
	return ret;
}

// vim:fdm=marker
