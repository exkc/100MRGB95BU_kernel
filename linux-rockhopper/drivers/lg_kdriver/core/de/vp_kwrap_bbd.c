/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file vp_kwrap.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author	sh.myoung (sh.myoung@lge.com)
 *  @version	1.0
 *  @date		2012-05-01
 *  @note		Additional information.
 *  @note		Moved to kernel for SEETV (harish.singh@lge.com)
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "sys_io.h"
#include "de_def.h"
#include "de_kwrap.h"
#include "afe_kwrap.h"
#include "vp_kwrap.h"
#include "pe_kapi.h"
#include "vp_kwrap_bbd.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_bbd_en                         : 1 ;  //     0
	UINT32 reg_hys_mode                       : 5 ;  //  5: 1	frame count for temporal smoothing of BBD result
	UINT32 reg_op_mode                        : 1 ;  //     6	BBD operation mode 0 : auto detection, 1 : manual setting
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_cnt_th                         : 8 ;  // 15: 8	continuous Black pixel's count threshold for recognizing Black Boundary
	UINT32 reg_diff_th                        : 8 ;  // 23:16	threshold for Black decision
	UINT32 reg_bbd_mux                        : 3 ;  // 26:24	data select for BBD, 0 : Max(RGB), 1 : Y, 2 : G, 3 : B, 4 : R, others : Y
} vp_ipp_bbd_ctrl_00_t;

typedef struct {
	UINT32 x0                                 : 13;  // 12: 0
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 y0                                 : 13;  // 28:16
} vp_ipp_bbd_stat_00_t;

typedef struct {
	UINT32 x1                                 : 13;  // 11: 0
	UINT32                                    : 3 ;  // 15:12     reserved
	UINT32 y1                                 : 13;  // 27:16
} vp_ipp_bbd_stat_01_t;

typedef struct {
	UINT32 offset_h                           : 13;  // 12: 0
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 offset_v                           : 13;  // 28:16
} vp_de_cvi_offset_ctrl_t;

#ifdef V4L2_VSC_BBD_USE_PRIV
#else
typedef struct {
	UINT32 hsize_i                            : 13;  // 12: 0
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 vsize_i                            : 13;  // 28:16
} vp_ipp_size_i_t;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_DE_CVI_SRC_TYPE_T prev_cviInfo;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
#ifdef V4L2_VSC_BBD_USE_PRIV
#else
kwrap_vp_active_video_window_t g_kwrap_vp_act_win[2] = {{{0,0,0,0},{0,0,0,0}},{{0,0,0,0},{0,0,0,0}}};
UINT32 g_kwrap_vp_act_th[2][5] = {{0,0,0,0,0},{0,0,0,0,0}};//frame_cnt,cnt_th,diff_th,rsvd,rsvd
UINT32 g_kwrap_vp_act_pos[2] = {0,0};//bbd_pos(dbg), 0:normal, 1:input, 2:middle
UINT32 _g_kwrap_vp_act_mask = 0x7;//diff(t-2),same(t-1),same(t) : should be bigger than 0
kwrap_vp_active_info_t _g_kwrap_vp_act_info[2];
void (*gpfnCallBackActiveVideoWindowMain)(UINT32 vpSrcId, kwrap_vp_active_video_window_t *win_inf);
void (*gpfnCallBackActiveVideoWindowSub)(UINT32 vpSrcId, kwrap_vp_active_video_window_t *win_inf);
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int vp_kwrap_getbbdstatus(UINT32 vpSrcId, UINT32 *pStat, UINT32 pos);
static int vp_kwrap_setbbdconfig(UINT32 vpSrcId, UINT32 uEnable, UINT32 uFrameCnt, UINT32 cnt_th, UINT32 diff_th, UINT32 e_o_sel, UINT32 pos);
#ifdef V4L2_VSC_BBD_USE_PRIV
#else
static int vp_kwrap_getcurinputactivewindow(UINT32 vpSrcId, kwrap_vp_active_info_t *pInf);
static int vp_kwrap_printactiveinfo(UINT32 vpSrcId, kwrap_vp_active_info_t *pInf);
static int vp_kwrap_getinputsize(UINT32 vpSrcId, kwrap_vp_timing_info_t *pTiming, kwrap_vp_active_info_t *pInf);
#endif
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#ifdef V4L2_VSC_BBD_USE_PRIV
#else
static UINT32	_g_vp_kwrap_active_win_init = 0;
static int _g_vp_kwrap_active_win_dbg = 0;
#endif

/*========================================================================================
	Implementation Group
========================================================================================*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
int vp_kwrap_getcvioffset(UINT32 *pXOffset, UINT32 *pYOffset)
{
	int ret = RET_OK;

	if (lx_chip_rev() > LX_CHIP_REV(M16, A0))
	{
#if 0
		UINT32 val;
		vp_de_cvi_offset_ctrl_t *de_cvi_offset_ctrl = (vp_de_cvi_offset_ctrl_t *)&val;

		KADP_SYS_RegReadSimple(0xc8000204, &val);

		*pXOffset = de_cvi_offset_ctrl->offset_h;
		*pYOffset = de_cvi_offset_ctrl->offset_v;
#else
		*pXOffset = prev_cviInfo.size_offset.hoffset;
		*pYOffset = prev_cviInfo.size_offset.voffset;
#endif

		DE_NOTI("=== Get CVI Offset [0x%x][0x%x] === \n", *pXOffset, *pYOffset);
	}
	else
		ret = RET_ERROR;

	return ret;
}

int vp_kwrap_setcvioffset(UINT32 XOffset, UINT32 YOffset)
{
	int ret = RET_OK;

	if (lx_chip_rev() > LX_CHIP_REV(M16, A0))
	{
#if 0
		UINT32 val;
		vp_de_cvi_offset_ctrl_t *de_cvi_offset_ctrl = (vp_de_cvi_offset_ctrl_t *)&val;

		KADP_SYS_RegReadSimple(0xc8000204, &val);

		de_cvi_offset_ctrl->offset_h = XOffset;
		de_cvi_offset_ctrl->offset_v = YOffset;

		KADP_SYS_RegWriteSimple(0xc8000204, val);

		DE_NOTI("=== Set CVI Offset [0x%x][0x%x] === \n", de_cvi_offset_ctrl->offset_h, de_cvi_offset_ctrl->offset_v);
#else
		DE_NOTI("=== Set CVI H Offset [0x%x]=> [0x%x] === \n", prev_cviInfo.size_offset.hoffset, XOffset);
		DE_NOTI("=== Set CVI V Offset [0x%x]=> [0x%x] === \n", prev_cviInfo.size_offset.voffset, YOffset);

		prev_cviInfo.size_offset.hoffset = XOffset;
		prev_cviInfo.size_offset.voffset = YOffset;

		//de_kwrap_setcvisrc(&prev_cviInfo);
#endif
	}
	else
		ret = RET_ERROR;

	return ret;
}

int vp_kwrap_setcvioffset_csample(UINT32 XOffset, UINT32 YOffset, LX_DE_SCALER_CSAMPLE_T c_sample)
{
	int ret = RET_OK;

	if (lx_chip_rev() > LX_CHIP_REV(M16, A0))
	{
#if 0
		UINT32 val;
		vp_de_cvi_offset_ctrl_t *de_cvi_offset_ctrl = (vp_de_cvi_offset_ctrl_t *)&val;

		KADP_SYS_RegReadSimple(0xc8000204, &val);

		de_cvi_offset_ctrl->offset_h = XOffset;
		de_cvi_offset_ctrl->offset_v = YOffset;

		KADP_SYS_RegWriteSimple(0xc8000204, val);

		DE_NOTI("=== Set CVI Offset [0x%x][0x%x] === \n", de_cvi_offset_ctrl->offset_h, de_cvi_offset_ctrl->offset_v);
#else
		DE_NOTI("=== Set CVI H Offset [0x%x]=> [0x%x] === \n", prev_cviInfo.size_offset.hoffset, XOffset);
		DE_NOTI("=== Set CVI V Offset [0x%x]=> [0x%x] === \n", prev_cviInfo.size_offset.voffset, YOffset);

		prev_cviInfo.size_offset.hoffset = XOffset;
		prev_cviInfo.size_offset.voffset = YOffset;
		prev_cviInfo.sc_c_sample = c_sample;

		//de_kwrap_setcvisrc(&prev_cviInfo);
#endif
	}
	else
		ret = RET_ERROR;

	return ret;
}

int vp_kwrap_adjustpcauto_hsize(LX_AFE_ADJ_PC_T *pPCAdjust_Hsize_t)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_AFE
	pPCAdjust_Hsize_t->adjust_mode = LX_AFE_PC_Auto_HSize;
	//Freeze On
	ret = afe_kwrap_pc_auto_adjust(pPCAdjust_Hsize_t);
	//Freeze Off
#endif

	return ret;
}

int vp_kwrap_adjustpcauto_phase(LX_AFE_ADJ_PC_T *pPCAdjust_Phase_t)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_AFE
	pPCAdjust_Phase_t->adjust_mode = LX_AFE_PC_AUTO_PHASE;
	//Freeze On
	ret = afe_kwrap_pc_auto_adjust(pPCAdjust_Phase_t);
	//Freeze Off
#endif
	return ret;
}

int vp_kwrap_adjustpcauto_position(LX_AFE_ADJ_PC_T *pPCAdjust_Position_t)
{
	int ret = RET_OK;
	UINT32 init_x_pos = 20;
	UINT32 init_y_pos = 0xc;
	UINT32 prev_x_pos, prev_y_pos;
	UINT32 bbd_status_even[4] = { 0 }, bbd_status_odd[4] = { 0 };

	if (lx_chip_rev() > LX_CHIP_REV(M17, C0))	//M16++ bbd even only
	{
		pPCAdjust_Position_t->adjust_mode = LX_AFE_PC_AUTO_POSITION;

		vp_kwrap_getcvioffset(&prev_x_pos, &prev_y_pos);

		if(prev_y_pos < init_y_pos)
		{
			DE_NOTI("=== Y position is small [0x%x] < Y init pos[%x] === \n", prev_y_pos, init_y_pos);
			init_y_pos = prev_y_pos >> 1;
		}

		/* Step 1 : horizontal offset to init_x */
		//KADP_VP_SetCVIOffset_CSample(init_x_pos, init_y_pos, LX_DE_SCALER_422);
		vp_kwrap_setcvioffset(init_x_pos, prev_y_pos);

		/* Step 1.5 : Disable Horizontal Scaline in IPP */
		//vp_kwrap_hsc_enable(0);

		vp_kwrap_setbbdconfig(0, 1, 0, 1, 0x40, 0, 1);

		OS_MsecSleep(300);

		ret = vp_kwrap_getbbdstatus(0, bbd_status_even, 1);
		DE_NOTI("=== BBD Status X [0x%x][0x%x][0x%x][0x%x] === \n", \
			bbd_status_even[0], bbd_status_even[1], bbd_status_even[2], bbd_status_even[3]);
		if( (bbd_status_even[0] > 0) && (bbd_status_even[0] < 0x7ff) )
			ret |= RET_OK;
		else
			ret |= RET_ERROR;

		/* Step 2 : horizontal offset to init_x + 1 */
		vp_kwrap_setcvioffset(init_x_pos + 1, prev_y_pos);

		//vp_kwrap_hsc_enable(0);

//		vp_kwrap_setbbdconfig(0, 1, 0, 1, 0x40, 1, 1);

		OS_MsecSleep(100);

		ret |= vp_kwrap_getbbdstatus(0, bbd_status_odd, 1);
		DE_NOTI("=== BBD Status x+1 [0x%x][0x%x][0x%x][0x%x] === \n", \
			bbd_status_odd[0], bbd_status_odd[1], bbd_status_odd[2], bbd_status_odd[3]);
		if( (bbd_status_odd[0] > 0) && (bbd_status_odd[0] < 0x7ff)  )
			ret |= RET_OK;
		else
			ret |= RET_ERROR;

		pPCAdjust_Position_t->s16_PC_HDelay = bbd_status_odd[0] + bbd_status_even[0] + init_x_pos;
		/*
		if( bbd_status_odd[0] != bbd_status_even[0] )
			pPCAdjust_Position_t->s16_PC_HDelay = bbd_status_odd[0] + bbd_status_even[0] + init_x_pos;
		else
			pPCAdjust_Position_t->s16_PC_HDelay = bbd_status_even[0] *2 + init_x_pos ;
			*/

		/* Step 3 : horizontal offset to adjusted position, vertical position to init_y */
		vp_kwrap_setcvioffset(pPCAdjust_Position_t->s16_PC_HDelay, init_y_pos);

		//vp_kwrap_hsc_enable(0);

//		vp_kwrap_setbbdconfig(0, 1, 0, 1, 0x40, 1, 1);

		OS_MsecSleep(300);

		ret |= vp_kwrap_getbbdstatus(0, bbd_status_odd, 1);
		DE_NOTI("=== BBD Status vertical [0x%x][0x%x][0x%x][0x%x] === \n", \
			bbd_status_odd[0], bbd_status_odd[1], bbd_status_odd[2], bbd_status_odd[3]);
		if( (bbd_status_odd[1] < 0x7ff) )
			ret |= RET_OK;
		else
			ret |= RET_ERROR;

		pPCAdjust_Position_t->s16_PC_VDelay = bbd_status_odd[1] + init_y_pos;

		vp_kwrap_setcvioffset(pPCAdjust_Position_t->s16_PC_HDelay, pPCAdjust_Position_t->s16_PC_VDelay);

		//vp_kwrap_hsc_enable(0);

//		vp_kwrap_setbbdconfig(0, 1, 0, 1, 0x40, 1, 1);

		OS_MsecSleep(100);

		ret |= vp_kwrap_getbbdstatus(0, bbd_status_odd, 1);
		DE_NOTI("=== BBD Status vertical 2nd [0x%x][0x%x][0x%x][0x%x] === \n", \
			bbd_status_odd[0], bbd_status_odd[1], bbd_status_odd[2], bbd_status_odd[3]);
		if( (bbd_status_odd[1] < 0x7ff) )
			ret |= RET_OK;
		else
			ret |= RET_ERROR;

		if(bbd_status_odd[1] > 0)
			pPCAdjust_Position_t->s16_PC_VDelay += bbd_status_odd[1];

		if(ret == RET_OK)
			pPCAdjust_Position_t->result = 0;
		else
			pPCAdjust_Position_t->result = -1;

		DE_NOTI("=== Auto Position [0x%x][0x%x] === \n", pPCAdjust_Position_t->s16_PC_HDelay, pPCAdjust_Position_t->s16_PC_VDelay);

		vp_kwrap_setcvioffset(pPCAdjust_Position_t->s16_PC_HDelay, pPCAdjust_Position_t->s16_PC_VDelay);

		/* Step 4 : Enable Horizontal Scaline in IPP(Default Setting) */
		//vp_kwrap_hsc_enable(1);

		vp_kwrap_setbbdconfig(0, 1, 0, 1, 0x40, 0, 1);
	}
	
	else
		ret = RET_ERROR;

	return ret;
}

int vp_kwrap_adjustpcauto_all(LX_AFE_ADJ_PC_T *pPCAdjust_t)
{
	int ret = RET_OK;

	ret = vp_kwrap_adjustpcauto_hsize(pPCAdjust_t);
	ret |=	vp_kwrap_adjustpcauto_phase(pPCAdjust_t);
	ret |=	vp_kwrap_adjustpcauto_position(pPCAdjust_t);

	return ret;
}

/**
 * get black boundary detection status
 * - UINT32 *pStat :
 *  [0]:x0, [1]:y0, [2]:x1, [3]:y1
 *
 * @param vpSrcId [in] UINT32
 * @param *pStat [in] UINT32
 * @param pos [in] UINT32
 * @return DTV_STATUS_T.
 */
static int vp_kwrap_getbbdstatus(UINT32 vpSrcId, UINT32 *pStat, UINT32 pos)
{
	int ret = RET_OK;
	UINT32 addr0 = 0, addr1 = 0;
	UINT32 val[4]={1,1,1,1};

	vp_ipp_bbd_stat_00_t *bbd0_stat_00 = (vp_ipp_bbd_stat_00_t *)&val[0];
	vp_ipp_bbd_stat_01_t *bbd0_stat_01 = (vp_ipp_bbd_stat_01_t *)&val[1];

	if (!pStat)		return RET_ERROR;

	if (lx_chip_rev() >= LX_CHIP_REV( E60, A0))
	{
		if (vpSrcId == 0)		{	addr0 = 0xc900e37c;	addr1 = 0xc900e380;	}//ND0 BBD_STAT_00,BBD_STAT_01
		else if (vpSrcId == 1)	{	addr0 = 0xc9008830;	addr1 = 0xc9008834;	}//IPP M1 BBD_STAT_00,BBD_STAT_01
		else if (vpSrcId == 2)	{	addr0 = 0xc9007730;	addr1 = 0xc9007734;	}//IPP S0 BBD_STAT_00,BBD_STAT_01
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O20, A0))
	{
		if (vpSrcId == 0)
		{
			if (pos == 0)		{	addr0 = 0xc9014530;	addr1 = 0xc9014534;	}//IPP M0 BBD_STAT_00,BBD_STAT_01
			else				{	addr0 = 0xc901837c;	addr1 = 0xc9018380;	}//ND0 BBD_STAT_00,BBD_STAT_01
		}
		else if (vpSrcId == 1)	{	addr0 = 0xc9014730;	addr1 = 0xc9014734;	}//IPP M1 BBD_STAT_00,BBD_STAT_01
		else if (vpSrcId == 2)	{	addr0 = 0xc9014930;	addr1 = 0xc9014934;	}//IPP S0 BBD_STAT_00,BBD_STAT_01
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( M19, A0))
	{
		if (vpSrcId == 0)
		{
			if (pos == 0)		{	addr0 = 0xc9014530;	addr1 = 0xc9014534;	}//IPP M0 BBD_STAT_00,BBD_STAT_01
			else				{	addr0 = 0xc900337c;	addr1 = 0xc9003380;	}//ND0 BBD_STAT_00,BBD_STAT_01
		}
		else if (vpSrcId == 1)	{	addr0 = 0xc9014730;	addr1 = 0xc9014734;	}//IPP M1 BBD_STAT_00,BBD_STAT_01
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))
	{
		if (vpSrcId == 0)
		{
			if (pos == 0)		{	addr0 = 0xc9014530;	addr1 = 0xc9014534;	}//IPP M0 BBD_STAT_00,BBD_STAT_01
			else				{	addr0 = 0xc900337c;	addr1 = 0xc9003380;	}//ND0 BBD_STAT_00,BBD_STAT_01
		}
		else if (vpSrcId == 1)	{	addr0 = 0xc9014730;	addr1 = 0xc9014734;	}//IPP M1 BBD_STAT_00,BBD_STAT_01
		else if (vpSrcId == 2)	{	addr0 = 0xc9014930;	addr1 = 0xc9014934;	}//IPP S0 BBD_STAT_00,BBD_STAT_01
	}

	if (addr0>0 && addr1>0)
	{
		ret = SYS_IO_ReadRegArray(addr0,4,&val[0]);
		ret = SYS_IO_ReadRegArray(addr1,4,&val[1]);
		pStat[0] = bbd0_stat_00->x0;
		pStat[1] = bbd0_stat_00->y0;
		pStat[2] = bbd0_stat_01->x1;
		pStat[3] = bbd0_stat_01->y1;
	}

	return ret;
}

/**
 ** set black boundary detection config
 ** - UINT32 uEnable :
 **  0:disable, 1:enable
 ** - UINT32 uFrameCnt :
 **  0 ~ 31
 **
 ** @param uEnable [in] UINT32
 ** @param uFrameCnt [in] UINT32
 ** @return int.
 **/
static int vp_kwrap_setbbdconfig(UINT32 vpSrcId, UINT32 uEnable, UINT32 uFrameCnt, UINT32 cnt_th, UINT32 diff_th, UINT32 e_o_sel, UINT32 pos)
{
	int ret = RET_OK;
	UINT32 addr0=0, val0;
	vp_ipp_bbd_ctrl_00_t *bbd0_ctrl_00 = (vp_ipp_bbd_ctrl_00_t *)&val0;

	if (lx_chip_rev() >= LX_CHIP_REV( E60, A0))
	{
		if (vpSrcId == 0)		addr0 = 0xc900e370;//ND0 BBD_CTRL_00
		else if (vpSrcId == 1)	addr0 = 0xc9008820;//IPP M1 BBD_CTRL_00
		else if (vpSrcId == 2)	addr0 = 0xc9007720;//IPP S0 BBD_CTRL_00
		DE_NOTI("=== E60 BBD Config [%d][%d][0x%08x] === \n",vpSrcId, pos, addr0);
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O20, A0))
	{
		if (vpSrcId == 0)		addr0 = (pos==0)? 0xc9014520:0xc9018370;//IPP M0:ND0 BBD_CTRL_00
		else if (vpSrcId == 1)	addr0 = 0xc9014720;//IPP M1 BBD_CTRL_00
		else if (vpSrcId == 2)	addr0 = 0xc9014920;//IPP S0 BBD_CTRL_00
		DE_NOTI("=== O20 BBD Config [%d][%d][0x%08x] === \n",vpSrcId, pos, addr0);
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( M19, A0))
	{
		if (vpSrcId == 0)		addr0 = (pos==0)? 0xc9014520:0xc9003370;//IPP M0:ND0 BBD_CTRL_00
		else if (vpSrcId == 1)	addr0 = 0xc9014720;//IPP M1 BBD_CTRL_00
		DE_NOTI("=== M19 BBD Config [%d][%d][0x%08x] === \n",vpSrcId, pos, addr0);
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))
	{
		if (vpSrcId == 0)		addr0 = (pos==0)? 0xc9014520:0xc9003370;//IPP M0:ND0 BBD_CTRL_00
		else if (vpSrcId == 1)	addr0 = 0xc9014720;//IPP M1 BBD_CTRL_00
		else if (vpSrcId == 2)	addr0 = 0xc9014920;//IPP S0 BBD_CTRL_00
		DE_NOTI("=== O18 BBD Config [%d][%d][0x%08x] === \n",vpSrcId, pos, addr0);
	}

	if (addr0>0)
	{
		ret = SYS_IO_ReadRegArray(addr0,4,&val0);
		bbd0_ctrl_00->reg_bbd_en   = uEnable? 1:0;
		bbd0_ctrl_00->reg_hys_mode = (uFrameCnt>31)? 31:uFrameCnt;
		bbd0_ctrl_00->reg_op_mode  = 0x0;
		bbd0_ctrl_00->reg_cnt_th   = cnt_th;
		bbd0_ctrl_00->reg_diff_th  = diff_th;
		bbd0_ctrl_00->reg_bbd_mux  = 0x0;
		ret = SYS_IO_WriteRegArray(addr0,4,&val0);
		DE_NOTI("=== O20 BBD Config [0x%08x] === \n",val0);
	}

	return ret;
}

#ifdef V4L2_VSC_BBD_USE_PRIV
#else
int vp_kwrap_initactivewin(void)
{
	int	ret = RET_OK;
	if (!_g_vp_kwrap_active_win_init)
	{
		DE_NOTI("[VP] initactivewin\n");
		gpfnCallBackActiveVideoWindowMain = NULL;
		gpfnCallBackActiveVideoWindowSub  = NULL;
		_g_kwrap_vp_act_info[LX_PE_WIN_0].reg_cnt = 0;
		_g_kwrap_vp_act_info[LX_PE_WIN_1].reg_cnt = 0;
		_g_vp_kwrap_active_win_init = 1;
	}
	return ret;
}

int vp_kwrap_uninitactivewin(void)
{
	_g_vp_kwrap_active_win_init = 0;
	return RET_OK;
}

static int vp_kwrap_getinputsize(UINT32 vpSrcId, kwrap_vp_timing_info_t *pTiming, kwrap_vp_active_info_t *pInf)
{
	int ret = RET_OK;
	UINT32 addr0=0, val0;
	vp_ipp_size_i_t *ipp_size_i = (vp_ipp_size_i_t *)&val0;
	if (pTiming==NULL)	return RET_ERROR;

	if (lx_chip_rev() >= LX_CHIP_REV( E60, A0))
	{
		if (vpSrcId == 0)		addr0 = 0xc9003634;//IPP M0 IPP_SIZE_I
		else if (vpSrcId == 1)	addr0 = 0xc9008734;//IPP M1 IPP_SIZE_I
		else if (vpSrcId == 2)	addr0 = 0xc9007634;//IPP S0 IPP_SIZE_I
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))// same with M19,O20
	{
		if (vpSrcId == 0)		addr0 = 0xc9014434;//IPP M0 IPP_SIZE_I
		else if (vpSrcId == 1)	addr0 = 0xc9014634;//IPP M1 IPP_SIZE_I
		else if (vpSrcId == 2)	addr0 = 0xc9014834;//IPP S0 IPP_SIZE_I
	}

	if (addr0>0)
	{
		ret = SYS_IO_ReadRegArray(addr0,4,&val0);
		pTiming->hActive = ipp_size_i->hsize_i;
		pTiming->vActive = ipp_size_i->vsize_i;
	}
	else
	{
		pTiming->hActive = pTiming->vActive = 0;
	}

	/* for debug */
	if (vpSrcId<=LX_PE_WIN_1)
	{
		if ((g_kwrap_vp_act_win[vpSrcId].org.w+g_kwrap_vp_act_win[vpSrcId].org.h)!=0)
		{
			pTiming->hActive = g_kwrap_vp_act_win[vpSrcId].org.w;
			pTiming->vActive = g_kwrap_vp_act_win[vpSrcId].org.h;
		}
	}
	if (pInf!=NULL)
	{
		pInf->addr[0] = addr0;
		pInf->data[0] = val0;
	}
	return ret;
}
void vp_kwrap_setactivevideowindbg(int dbg_level)
{
	_g_vp_kwrap_active_win_dbg = dbg_level;
	return;
}
int vp_kwrap_getactivevideowindbg(void)
{
	return _g_vp_kwrap_active_win_dbg;
}
/**
 * 	KADP_VP_GetActiveVideoWindowCallback
 *
 *	@param vpSrcId
 *	@param callback
 * 	@return OK(0)
 * 	@return NOT_OK(-1) : any error
 * 	@return PARAMETER_ERROR(-2) : wId is not correct
 * 	@return NOT_SUPPORTED(-4)
 */
int vp_kwrap_getactivevideowindowcallback(void)
{
	int ret = RET_OK;
	if (!_g_vp_kwrap_active_win_init)
	{
		DE_NOTI("not initiealized\n");
		ret = RET_ERROR;
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(M17, A0))
	{
		DE_NOTI("	cb0 = %p, cb1 = %p\n", gpfnCallBackActiveVideoWindowMain, gpfnCallBackActiveVideoWindowSub);
	}
	else
	{
		DE_NOTI("not support\n");
		ret = -4;
	}
	return ret;
}
/**
 * 	KADP_VP_RegisterActiveVideoWindowCallback
 *
 *	@param vpSrcId
 *	@param callback
 * 	@return OK(0)
 * 	@return NOT_OK(-1) : any error
 * 	@return PARAMETER_ERROR(-2) : wId is not correct
 * 	@return NOT_SUPPORTED(-4)
 */
int vp_kwrap_registeractivevideowindowcallback(UINT32 vpSrcId, PFN_VP_ACTIVE_VIDEO_WINDOW_T callback)
{
	int ret = RET_OK;
	UINT32 diff_th;
	kwrap_vp_active_info_t *p_inf0 = &_g_kwrap_vp_act_info[LX_PE_WIN_0];
	kwrap_vp_active_info_t *p_inf1 = &_g_kwrap_vp_act_info[LX_PE_WIN_1];
	if (vpSrcId>1)
	{
		DE_NOTI("vpSrcId(%d) invalid\n",vpSrcId);
		ret = -1;
	}
	else if (!_g_vp_kwrap_active_win_init)
	{
		DE_NOTI("not initiealized\n");
		ret = -2;
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0))// same with M19,O20
	{
		if(vpSrcId==0)
		{
			p_inf0->bbd_pos   = (g_kwrap_vp_act_pos[LX_PE_WIN_0]!=0)? (g_kwrap_vp_act_pos[LX_PE_WIN_0]-1):1;//default:middle
			p_inf0->frame_cnt = (g_kwrap_vp_act_th[LX_PE_WIN_0][0]!=0)? g_kwrap_vp_act_th[LX_PE_WIN_0][0]:0;
			p_inf0->cnt_th    = (g_kwrap_vp_act_th[LX_PE_WIN_0][1]!=0)? g_kwrap_vp_act_th[LX_PE_WIN_0][1]:1;
			diff_th = (p_inf0->bbd_pos==0)? 21:18;	//if input, 19+2, else 16+2
			p_inf0->diff_th   = (g_kwrap_vp_act_th[LX_PE_WIN_0][2]!=0)? g_kwrap_vp_act_th[LX_PE_WIN_0][2]:diff_th;
			if (callback==NULL)
			{
				if (p_inf0->reg_cnt==1)
				{
					/* unregister cb */
					gpfnCallBackActiveVideoWindowMain = NULL;
					/* bbd_en : off */
					p_inf0->enable = 0;
					vp_kwrap_setbbdconfig(LX_PE_WIN_0, p_inf0->enable, p_inf0->frame_cnt, p_inf0->cnt_th, p_inf0->diff_th, 0, p_inf0->bbd_pos);
					DE_NOTI("wId[%d](%d) unregister cb = %p, gpfnCBm = %p\n", vpSrcId, p_inf0->reg_cnt, callback, gpfnCallBackActiveVideoWindowMain);
					ret = RET_OK;
				}
				else
				{
					DE_NOTI("wId[%d](%d) ignore unregister cb = %p, gpfnCBm = %p\n", vpSrcId, p_inf0->reg_cnt, callback, gpfnCallBackActiveVideoWindowMain);
					ret = RET_OK;
				}
				if (p_inf0->reg_cnt>0)	p_inf0->reg_cnt--;
			}
			else
			{
				if (p_inf0->reg_cnt==0)
				{
					/* bbd_en : on */
					p_inf0->enable = 1;
					vp_kwrap_setbbdconfig(LX_PE_WIN_0, p_inf0->enable, p_inf0->frame_cnt, p_inf0->cnt_th, p_inf0->diff_th, 0, p_inf0->bbd_pos);
					p_inf0->update = 0;
					memset(&(p_inf0->pre),-1,sizeof(kwrap_vp_active_video_window_t));
					memset(&(p_inf0->pre_cb),-1,sizeof(kwrap_vp_video_rect_t));
					memset(&(p_inf0->pre_act),-1,sizeof(kwrap_vp_video_rect_t)*VP_PRE_ACT_NUM);
					memset(&(p_inf0->pre_bbd),-1,sizeof(kwrap_vp_video_rect_t));
					memset(&(p_inf0->ret_bbd),-1,sizeof(kwrap_vp_video_rect_t));
					memset(&(p_inf0->dif_bbd),0,sizeof(kwrap_vp_video_rect_t));
					/* register cb */
					gpfnCallBackActiveVideoWindowMain = callback;
					DE_NOTI("wId[%d](%d) register cb = %p, gpfnCBm = %p, set -1\n", vpSrcId, p_inf0->reg_cnt, callback, gpfnCallBackActiveVideoWindowMain);
					ret = RET_OK;
				}
				else
				{
					DE_NOTI("wId[%d](%d) ignore register cb = %p, gpfnCBm = %p\n", vpSrcId, p_inf0->reg_cnt, callback, gpfnCallBackActiveVideoWindowMain);
					ret = RET_OK;
				}
				p_inf0->reg_cnt++;
			}
		}
		else if (vpSrcId==1)
		{
			p_inf1->bbd_pos   = 0;//default:input
			p_inf1->frame_cnt = (g_kwrap_vp_act_th[LX_PE_WIN_1][0]!=0)? g_kwrap_vp_act_th[LX_PE_WIN_1][0]:0;
			p_inf1->cnt_th    = (g_kwrap_vp_act_th[LX_PE_WIN_1][1]!=0)? g_kwrap_vp_act_th[LX_PE_WIN_1][1]:1;
			p_inf1->diff_th   = (g_kwrap_vp_act_th[LX_PE_WIN_1][2]!=0)? g_kwrap_vp_act_th[LX_PE_WIN_1][2]:21;//19+2(black(Y=19)V10(MIRACAST-3173))
			if (callback==NULL)
			{
				if (p_inf1->reg_cnt==1)
				{
					/* unregister cb */
					gpfnCallBackActiveVideoWindowSub = NULL;
					/* bbd_en : off */
					p_inf1->enable = 0;
					vp_kwrap_setbbdconfig(LX_PE_WIN_1, p_inf1->enable, p_inf1->frame_cnt, p_inf1->cnt_th, p_inf1->diff_th, 0, p_inf1->bbd_pos);
					DE_NOTI("wId[%d](%d) unregister cb = %p, gpfnCBs = %p\n", vpSrcId, p_inf1->reg_cnt, callback, gpfnCallBackActiveVideoWindowSub);
					ret = RET_OK;
				}
				else
				{
					DE_NOTI("wId[%d](%d) ignore unregister cb = %p, gpfnCBm = %p\n", vpSrcId, p_inf1->reg_cnt, callback, gpfnCallBackActiveVideoWindowSub);
					ret = RET_OK;
				}
				if (p_inf1->reg_cnt>0)	p_inf1->reg_cnt--;
			}
			else
			{
				if (p_inf1->reg_cnt==0)
				{
					/* bbd_en : on */
					p_inf1->enable = 1;
					vp_kwrap_setbbdconfig(LX_PE_WIN_1, p_inf1->enable, p_inf1->frame_cnt, p_inf1->cnt_th, p_inf1->diff_th, 0, p_inf1->bbd_pos);
					p_inf1->update = 0;
					memset(&(p_inf1->pre),-1,sizeof(kwrap_vp_active_video_window_t));
					memset(&(p_inf1->pre_cb),-1,sizeof(kwrap_vp_video_rect_t));
					memset(&(p_inf1->pre_act),-1,sizeof(kwrap_vp_video_rect_t)*VP_PRE_ACT_NUM);
					memset(&(p_inf1->pre_bbd),-1,sizeof(kwrap_vp_video_rect_t));
					memset(&(p_inf1->ret_bbd),-1,sizeof(kwrap_vp_video_rect_t));
					memset(&(p_inf1->dif_bbd),0,sizeof(kwrap_vp_video_rect_t));
					/* register cb */
					gpfnCallBackActiveVideoWindowSub = callback;
					DE_NOTI("wId[%d](%d) register cb = %p, gpfnCBs = %p, set -1\n", vpSrcId, p_inf1->reg_cnt, callback, gpfnCallBackActiveVideoWindowSub);
					ret = RET_OK;
				}
				else
				{
					DE_NOTI("wId[%d](%d) ignore register cb = %p, gpfnCBm = %p\n", vpSrcId, p_inf1->reg_cnt, callback, gpfnCallBackActiveVideoWindowSub);
					ret = RET_OK;
				}
				p_inf1->reg_cnt++;
			}
		}
	}
	else
	{
		DE_NOTI("not support\n");
		ret = -5;
	}
	return ret;
}
static int vp_kwrap_printactiveinfo(UINT32 vpSrcId, kwrap_vp_active_info_t *pInf)
{
	if (pInf==NULL)	return RET_ERROR;
	DE_NOTI("%d)s:%x,%d/ad:%08x,%08x/ab:%x,%x/efcd:%d,%d,%d,%d/t:%d,%d,%d/%08x\n", \
		vpSrcId,pInf->step,pInf->skip,pInf->addr[0],pInf->data[0],pInf->abno[0],pInf->abno[1],\
		pInf->enable,pInf->frame_cnt,pInf->cnt_th,pInf->diff_th,\
		pInf->timing.hActive,pInf->timing.vActive,pInf->timing.vFreq,pInf->update);
	DE_NOTI("%d,%d,%d,%d -> %d,%d,%d,%d (%d,%d)\n",\
		pInf->cur_bbd.x,pInf->cur_bbd.y,pInf->cur_bbd.w,pInf->cur_bbd.h,\
		pInf->ret_bbd.x,pInf->ret_bbd.y,pInf->ret_bbd.w,pInf->ret_bbd.h,\
		pInf->dif_bbd.x,pInf->dif_bbd.w);
	DE_NOTI("%x,%x/ps:%d/p:%d,%d,%d,%d,%d,%d/%d,%d,%d,%d/c:%d,%d,%d,%d,%d,%d\n", \
		pInf->same_cnt,pInf->same_mask,pInf->bbd_pos,\
		pInf->pre.org.w,pInf->pre.org.h,pInf->pre.act.x,pInf->pre.act.y,pInf->pre.act.w,pInf->pre.act.h,\
		pInf->pre_cb.x,pInf->pre_cb.y,pInf->pre_cb.w,pInf->pre_cb.h,\
		pInf->cur.org.w,pInf->cur.org.h,pInf->cur.act.x,pInf->cur.act.y,pInf->cur.act.w,pInf->cur.act.h);
	return RET_OK;
}
static int vp_kwrap_getcurinputactivewindow(UINT32 vpSrcId, kwrap_vp_active_info_t *pInf)
{
	int ret = RET_OK;
	UINT32 pStat[4] = { 0 },x0=1,y0=1,x1=1,y1=1;
	UINT32 pre_x0,pre_x1,pre_y0,pre_y1,cur_x0,cur_y0,cur_x1,cur_y1,dif_x0,dif_x1;

	if (pInf==NULL)		return RET_ERROR;
	if (vpSrcId > 1)	return RET_ERROR;

	pInf->cur.org.x = pInf->cur.org.y = 0;
	pInf->cur.org.w = pInf->timing.hActive;
	pInf->cur.org.h = pInf->timing.vActive;

	ret = vp_kwrap_getbbdstatus(vpSrcId, pStat, pInf->bbd_pos);
	if(ret == RET_OK)
	{
		#if 1	//20200604, adj x0,x1 (QEVENTTWEN-25769)
		cur_x0 = pStat[0];
		cur_y0 = pStat[1];
		cur_x1 = pStat[2];
		cur_y1 = pStat[3];

		pInf->cur_bbd.x = (UINT16)cur_x0;
		pInf->cur_bbd.y = (UINT16)cur_y0;
		pInf->cur_bbd.w = (UINT16)cur_x1;
		pInf->cur_bbd.h = (UINT16)cur_y1;

		pre_x0 = pInf->pre_bbd.x;
		pre_x1 = pInf->pre_bbd.w;
		pre_y0 = pInf->pre_bbd.y;
		pre_y1 = pInf->pre_bbd.h;
		dif_x0 = (pre_x0>cur_x0)? (pre_x0-cur_x0):(cur_x0-pre_x0);
		dif_x1 = (pre_x1>cur_x1)? (pre_x1-cur_x1):(cur_x1-pre_x1);

		#if 1	//20200729, use prev coordinate result, if diff sum is 10 or less.(QEVENTSIT-3896)
		if ((dif_x0 + dif_x1) <= 10)
		#else
		if (dif_x0<=2 || dif_x1<=2)
		#endif
		{
			x0 = pInf->ret_bbd.x;
			x1 = pInf->ret_bbd.w;
		}
		else
		{
			x0 = cur_x0;
			x1 = cur_x1;
		}
		y0 = cur_y0;
		y1 = cur_y1;

		pInf->dif_bbd.x = (UINT16)dif_x0;
		pInf->dif_bbd.w = (UINT16)dif_x1;

		pInf->pre_bbd.x = (UINT16)cur_x0;
		pInf->pre_bbd.w = (UINT16)cur_x1;
		pInf->pre_bbd.y = (UINT16)cur_y0;
		pInf->pre_bbd.h = (UINT16)cur_y1;

		pInf->ret_bbd.x = (UINT16)x0;
		pInf->ret_bbd.w = (UINT16)x1;
		pInf->ret_bbd.y = (UINT16)y0;
		pInf->ret_bbd.h = (UINT16)y1;

		if (dif_x0>0 || dif_x1>0)
		{
			DE_NOTI("COORD]%d]:%d,%d,%d,%d|%d,%d,%d,%d -> %d,%d,%d,%d (%d,%d)\n",\
				vpSrcId,pre_x0,pre_y0,pre_x1,pre_y1,cur_x0,cur_y0,cur_x1,cur_y1,x0,y0,x1,y1,dif_x0,dif_x1);
		}
		#else	//legacy
		x0 = pInf->cur_bbd.x = (UINT16)pStat[0];
		y0 = pInf->cur_bbd.y = (UINT16)pStat[1];
		x1 = pInf->cur_bbd.w = (UINT16)pStat[2];
		y1 = pInf->cur_bbd.h = (UINT16)pStat[3];
		#endif
		pInf->abno[0] = 0;
		pInf->abno[1] = 0;
		// 20170719, add abnormal case:set org
		// 20170901, add abnormal case(eg. full black):set zero (MIRACAST-3208)
		if (x0>x1 || y0>y1)
		{
			pInf->cur.act.x = 0;
			pInf->cur.act.y = 0;
			pInf->cur.act.w = 0;
			pInf->cur.act.h = 0;
			pInf->abno[0] |= 0x1;
			pInf->abno[1] |= 0x1;
		}
		else
		{
			/* get act.x, act.w */
			pInf->cur.act.x = x0;
			pInf->cur.act.w = (x1>x0)? (x1-x0+1):0;
			pInf->cur.act.x <<= 1;
			pInf->cur.act.w <<= 1;
			/* get act.y, act.h */
			pInf->cur.act.y = y0;
			pInf->cur.act.h = (y1>y0)? (y1-y0+1):0;
		}
	}
	else
	{
		pInf->cur.act.x = pInf->cur.act.y = 0;
		pInf->cur.act.w = pInf->cur.org.w;
		pInf->cur.act.h = pInf->cur.org.h;
		pInf->abno[0] = pInf->abno[1] = 9;
	}
	/* for debug */
	if (vpSrcId<=LX_PE_WIN_1)
	{
		if ((g_kwrap_vp_act_win[vpSrcId].act.w+g_kwrap_vp_act_win[vpSrcId].act.h)!=0)
		{
			pInf->cur.act.x = g_kwrap_vp_act_win[vpSrcId].act.x;
			pInf->cur.act.y = g_kwrap_vp_act_win[vpSrcId].act.y;
			pInf->cur.act.w = g_kwrap_vp_act_win[vpSrcId].act.w;
			pInf->cur.act.h = g_kwrap_vp_act_win[vpSrcId].act.h;
		}
	}
	return RET_OK;
}
int vp_kwrap_checkactivevideowindowmain(UINT32 vpSrcId, kwrap_vp_timing_info_t *pBufTiming)
{
	int ret = RET_OK;
	UINT32 i;
	kwrap_vp_timing_info_t timing;
	kwrap_vp_active_info_t *p_inf = &_g_kwrap_vp_act_info[LX_PE_WIN_0];
	do {
		p_inf->step = 0;
		/* check skip conditions */
		do {
			if (gpfnCallBackActiveVideoWindowMain==NULL)	{p_inf->skip = 1;break;}
			if (vpSrcId!=0)									{p_inf->skip = 2;break;}
			if (pBufTiming==NULL)							{p_inf->skip = 3;break;}
			vp_kwrap_getinputsize(vpSrcId, &timing, p_inf);
			p_inf->timing.hActive = pBufTiming->hActive;
			p_inf->timing.vActive = pBufTiming->vActive;
			p_inf->timing.vFreq = pBufTiming->vFreq;
			if (timing.hActive == 0)						{p_inf->skip = 10;break;}
			if (timing.vActive == 0)						{p_inf->skip = 11;break;}
			if (pBufTiming->hActive == 0)					{p_inf->skip = 12;break;}
			if (pBufTiming->vActive == 0)					{p_inf->skip = 13;break;}
			if (pBufTiming->vFreq == 0)						{p_inf->skip = 14;break;}
			p_inf->skip = 0;
		} while(0);
		if (p_inf->skip>0)
		{
			p_inf->update = 0;
			memset(&(p_inf->pre),-1,sizeof(kwrap_vp_active_video_window_t));
			if (_g_vp_kwrap_active_win_dbg == 1)
			{
				if (p_inf->skip<=3)		DE_NOTI("[%d]skip:%d\n", vpSrcId, p_inf->skip);
				else					vp_kwrap_printactiveinfo(vpSrcId, p_inf);
			}
			break;
		}
		p_inf->step |= 0x1;
		/* get cur win */
		ret = vp_kwrap_getcurinputactivewindow(vpSrcId, p_inf);
		if (ret!=RET_OK)
		{
			p_inf->step |= 0x2;
			if (_g_vp_kwrap_active_win_dbg == 1)
			{
				vp_kwrap_printactiveinfo(vpSrcId, p_inf);
			}
			break;
		}
		/* check act_win valid */
		if (p_inf->cur.act.w>p_inf->cur.org.w || p_inf->cur.act.h>p_inf->cur.org.h)
		{
			p_inf->step |= 0x4;
			p_inf->cur.act.x = p_inf->cur.act.y = 0;
			p_inf->cur.act.w = p_inf->cur.org.w;
			p_inf->cur.act.h = p_inf->cur.org.h;
		}
		/* cmp pre vs cur */
		if (memcmp(&(p_inf->pre), &(p_inf->cur), sizeof(kwrap_vp_active_video_window_t))==0)
		{
			p_inf->step |= 0x10;
			p_inf->update = (p_inf->update<<1)|0x1;
		}
		else
		{
			p_inf->step |= 0x20;
			p_inf->update = (p_inf->update<<1)|0x0;
		}
		/* check same_cnt,same_mask(except for zero) : windowing from T to T-4 */
		p_inf->same_cnt = p_inf->same_mask = 0;
		if (p_inf->cur.act.w == 0 || p_inf->cur.act.h == 0)
		{
			p_inf->step |= 0x100;
		}
		else
		{
			p_inf->step |= 0x200;
			p_inf->same_cnt = 1;
			for (i=0; i<VP_PRE_ACT_NUM; i++)
			{
				if (memcmp(&(p_inf->pre_act[i]), &(p_inf->cur.act), sizeof(kwrap_vp_video_rect_t))==0)
				{
					p_inf->same_cnt = p_inf->same_cnt+1;
					p_inf->same_mask |= (0x1<<i);
				}
			}
		}
		/* 20171004, add same_cnt,same_mask for bad connection(QEVENTSEVT-15952,QEVENTSEVT-15801) */
		if ((p_inf->update&_g_kwrap_vp_act_mask)==(_g_kwrap_vp_act_mask>>1) || p_inf->same_cnt>=3)
		{
			if (memcmp(&(p_inf->pre_cb), &(p_inf->cur.act), sizeof(kwrap_vp_video_rect_t))==0)
			{
				p_inf->step |= 0x10000000;
			}
			else
			{
				p_inf->step |= 0x20000000;
				if (gpfnCallBackActiveVideoWindowMain==NULL)	{p_inf->skip = 100;break;}
				/* call fnCallBack*/
				gpfnCallBackActiveVideoWindowMain(vpSrcId,&(p_inf->cur));
				p_inf->pre_cb = p_inf->cur.act;
			}
		}
		if (_g_vp_kwrap_active_win_dbg == 1)		vp_kwrap_printactiveinfo(vpSrcId, p_inf);
		memcpy(&(p_inf->pre), &(p_inf->cur), sizeof(kwrap_vp_active_video_window_t));
		/* update pre_act, see VP_PRE_ACT_NUM (4) */
		p_inf->pre_act[3] = p_inf->pre_act[2];
		p_inf->pre_act[2] = p_inf->pre_act[1];
		p_inf->pre_act[1] = p_inf->pre_act[0];
		p_inf->pre_act[0] = p_inf->cur.act;
	} while(0);
	return ret;
}
int vp_kwrap_checkactivevideowindowsub(UINT32 vpSrcId, kwrap_vp_timing_info_t *pBufTiming)
{
	int ret = RET_OK;
	UINT32 i;
	kwrap_vp_timing_info_t timing;
	kwrap_vp_active_info_t *p_inf = &_g_kwrap_vp_act_info[LX_PE_WIN_1];
	do {
		p_inf->step = 0;
		/* check skip conditions */
		do {
			if (gpfnCallBackActiveVideoWindowSub==NULL)		{p_inf->skip = 1;break;}
			if (vpSrcId!=1)									{p_inf->skip = 2;break;}
			if (pBufTiming==NULL)							{p_inf->skip = 3;break;}
			vp_kwrap_getinputsize(vpSrcId, &timing, p_inf);
			p_inf->timing.hActive = pBufTiming->hActive;
			p_inf->timing.vActive = pBufTiming->vActive;
			p_inf->timing.vFreq = pBufTiming->vFreq;
			if (timing.hActive == 0)						{p_inf->skip = 10;break;}
			if (timing.vActive == 0)						{p_inf->skip = 11;break;}
			if (pBufTiming->hActive == 0)					{p_inf->skip = 12;break;}
			if (pBufTiming->vActive == 0)					{p_inf->skip = 13;break;}
			if (pBufTiming->vFreq == 0)						{p_inf->skip = 14;break;}
			p_inf->skip = 0;
		} while(0);
		if (p_inf->skip>0)
		{
			p_inf->update = 0;
			memset(&(p_inf->pre),-1,sizeof(kwrap_vp_active_video_window_t));
			if (_g_vp_kwrap_active_win_dbg == 2)
			{
				if (p_inf->skip<=3)		DE_NOTI("[%d]skip:%d\n", vpSrcId, p_inf->skip);
				else					vp_kwrap_printactiveinfo(vpSrcId, p_inf);
			}
			break;
		}
		p_inf->step |= 0x1;
		/* get cur win */
		ret = vp_kwrap_getcurinputactivewindow(vpSrcId, p_inf);
		if (ret!=RET_OK)
		{
			p_inf->step |= 0x2;
			if (_g_vp_kwrap_active_win_dbg == 2)
			{
				vp_kwrap_printactiveinfo(vpSrcId, p_inf);
			}
			break;
		}
		/* check act_win valid */
		if (p_inf->cur.act.w>p_inf->cur.org.w || p_inf->cur.act.h>p_inf->cur.org.h)
		{
			p_inf->step |= 0x4;
			p_inf->cur.act.x = p_inf->cur.act.y = 0;
			p_inf->cur.act.w = p_inf->cur.org.w;
			p_inf->cur.act.h = p_inf->cur.org.h;
		}
		/* cmp pre vs cur */
		if (memcmp(&(p_inf->pre), &(p_inf->cur), sizeof(kwrap_vp_active_video_window_t))==0)
		{
			p_inf->step |= 0x10;
			p_inf->update = (p_inf->update<<1)|0x1;
		}
		else
		{
			p_inf->step |= 0x20;
			p_inf->update = (p_inf->update<<1)|0x0;
		}
		/* check same_cnt,same_mask(except for zero) : windowing from T to T-4 */
		p_inf->same_cnt = p_inf->same_mask = 0;
		if (p_inf->cur.act.w == 0 || p_inf->cur.act.h == 0)
		{
			p_inf->step |= 0x100;
		}
		else
		{
			p_inf->step |= 0x200;
			p_inf->same_cnt = 1;
			for (i=0; i<VP_PRE_ACT_NUM; i++)
			{
				if (memcmp(&(p_inf->pre_act[i]), &(p_inf->cur.act), sizeof(kwrap_vp_video_rect_t))==0)
				{
					p_inf->same_cnt = p_inf->same_cnt+1;
					p_inf->same_mask |= (0x1<<i);
				}
			}
		}
		/* 20171004, add same_cnt,same_mask for bad connection(QEVENTSEVT-15952,QEVENTSEVT-15801) */
		if ((p_inf->update&_g_kwrap_vp_act_mask)==(_g_kwrap_vp_act_mask>>1) || p_inf->same_cnt>=3)
		{
			if (memcmp(&(p_inf->pre_cb), &(p_inf->cur.act), sizeof(kwrap_vp_video_rect_t))==0)
			{
				p_inf->step |= 0x10000000;
			}
			else
			{
				p_inf->step |= 0x20000000;
				if (gpfnCallBackActiveVideoWindowSub==NULL)	{p_inf->skip = 100;break;}
				/* call fnCallBack*/
				gpfnCallBackActiveVideoWindowSub(vpSrcId,&(p_inf->cur));
				DE_NOTI("S)%08x,%08x,%x,%x/%08x/%x,%x/%d,%d,%d/%d,%d/%d,%d,%d,%d\n",\
					p_inf->addr[0],p_inf->data[0],p_inf->abno[0],p_inf->abno[1],\
					p_inf->update,p_inf->same_cnt,p_inf->same_mask,\
					p_inf->timing.hActive,p_inf->timing.vActive,p_inf->timing.vFreq,\
					p_inf->pre.org.w,p_inf->pre.org.h,\
					p_inf->pre.act.x,p_inf->pre.act.y,p_inf->pre.act.w,p_inf->pre.act.h);
				DE_NOTI("%d,%d,%d,%d -> %d,%d,%d,%d (%d,%d)\n",\
					p_inf->cur_bbd.x,p_inf->cur_bbd.y,p_inf->cur_bbd.w,p_inf->cur_bbd.h,\
					p_inf->ret_bbd.x,p_inf->ret_bbd.y,p_inf->ret_bbd.w,p_inf->ret_bbd.h,\
					p_inf->dif_bbd.x,p_inf->dif_bbd.w);
				DE_NOTI("%d,%d,%d,%d -----> %d,%d/%d,%d,%d,%d\n",\
					p_inf->pre_cb.x,p_inf->pre_cb.y,p_inf->pre_cb.w,p_inf->pre_cb.h,\
					p_inf->cur.org.w,p_inf->cur.org.h,\
					p_inf->cur.act.x,p_inf->cur.act.y,p_inf->cur.act.w,p_inf->cur.act.h);
				p_inf->pre_cb = p_inf->cur.act;
			}
		}
		if (_g_vp_kwrap_active_win_dbg == 2)		vp_kwrap_printactiveinfo(vpSrcId, p_inf);
		memcpy(&(p_inf->pre), &(p_inf->cur), sizeof(kwrap_vp_active_video_window_t));
		/* update pre_act, see VP_PRE_ACT_NUM (4) */
		p_inf->pre_act[3] = p_inf->pre_act[2];
		p_inf->pre_act[2] = p_inf->pre_act[1];
		p_inf->pre_act[1] = p_inf->pre_act[0];
		p_inf->pre_act[0] = p_inf->cur.act;
	} while(0);
	return ret;
}
#endif

