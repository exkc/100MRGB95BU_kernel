/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file pe_kwrap_dcm.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- dynamic contrast management
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj, S(kanthiraj.s@lge.com)
 *	@version	0.1
 *	@note
 *	@date			2011.06.11
 *	@modified date	2015.05.20
 *	@see
 */

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
		
#include "pe_def.h"

#include "pe_dcm.h"

#include "pe_kwrap.h"
#include "pe_kwrap_def.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
/* for 15 points y lut control(fix 64,940) */
#define KWRAP_PE_PARAM_USE_15P_Y_LUT_CTRL

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/
extern UINT32 g_pe_kwrap_ver_mask;

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/
extern PE_KWRAP_INFO_T _g_pe_info;

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
/** dce lut curve
* y level : 64 ~ 940 (16 ~ 235)
* see PE_KWRAP_DCM_DCE_LUT_NUM
*/

#ifdef KWRAP_PE_PARAM_USE_15P_Y_LUT_CTRL
const UINT32 g_pe_kwrap_p_dce_lut_curve[PE_KWRAP_DCM_DCE_LUT_NUM][PE_KWRAP_DCM_LUT_STEP+1] = {
{0, 64, 122, 181, 239, 298, 356, 415, 473, 532, 590, 649, 707, 766, 824, 882, 940},
{0, 64, 106, 149, 191, 234, 308, 383, 457, 548, 622, 697, 771, 814, 856, 898, 940},
{0, 32,  61,  91, 120, 149, 178, 208, 237, 266, 295, 325, 354, 383, 412, 441, 940},
{0, 64, 528, 557, 586, 615, 645, 674, 703, 732, 762, 791, 820, 849, 879, 908, 940}};
#else
const UINT32 g_pe_kwrap_p_dce_lut_curve[PE_KWRAP_DCM_DCE_LUT_NUM][PE_KWRAP_DCM_LUT_STEP+1] = {
{0, 64,  128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 940, 1023},
{0, 64,  90,  140, 200, 270, 351, 497, 615, 701, 755, 798, 830, 870, 920, 940, 1023},
{0, 64,  70,  75,  102, 132, 157, 188, 219, 250, 282, 315, 355, 390, 435, 480, 1023},
{0, 544, 589, 634, 669, 709, 742, 774, 805, 836, 867, 892, 922, 927, 934, 940, 1023}};
#endif
const UINT32 g_pe_kwrap_p_dse_lut_curve[PE_KWRAP_DCM_DSE_LUT_NUM][PE_KWRAP_DCM_LUT_STEP+1] = {
{0,  64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960, 1023},
{0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 1023},
{0,  51,  77, 102, 128, 154, 179, 205, 230, 256, 282, 307, 333, 358, 384, 409, 1023},
{0,  77, 115, 154, 192, 230, 269, 307, 346, 384, 422, 461, 499, 538, 576, 614, 1023},
{0,  80, 154, 230, 307, 384, 461, 538, 614, 691, 768, 845, 922, 947, 973, 998, 1023},
{0,  90, 192, 288, 384, 480, 576, 672, 768, 864, 887, 909, 932, 955, 978, 998, 1023},
{0, 120, 256, 384, 512, 640, 768, 794, 819, 845, 870, 899, 921, 947, 972, 998, 1023}};
const UINT32 g_pe_kwrap_p_hdr_lut_curve[PE_KWRAP_DCM_DCE_LUT_NUM][PE_KWRAP_HDR_TLUT_MAX] = {
{ 0,  32,  64,  96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512, \
544, 576, 608, 640, 672, 704, 736, 768, 800, 832, 864, 896, 928, 940, 972, 1023, \
 0,  32,  64,  96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512, \
544, 576, 608, 640, 672, 704, 736, 768, 800, 832, 864, 896, 928, 940, 972, 1023, \
 0,  32,  64,  96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512, \
544, 576, 608, 640, 672, 704, 736, 768, 800, 832, 864, 896, 928, 940, 972, 1023},
{ 0,  32,  64,  74,  90, 115, 140, 170, 200, 235, 270, 310, 351, 376, 497, 556, 615, \
660, 701, 727, 755, 777, 798, 814, 830, 850, 870, 895, 920, 930, 940, 980, 1023, \
 0,  32,  64,  74,  90, 115, 140, 170, 200, 235, 270, 310, 351, 376, 497, 556, 615, \
660, 701, 727, 755, 777, 798, 814, 830, 850, 870, 895, 920, 930, 940, 980, 1023, \
 0,  32,  64,  74,  90, 115, 140, 170, 200, 235, 270, 310, 351, 376, 497, 556, 615, \
660, 701, 727, 755, 777, 798, 814, 830, 850, 870, 895, 920, 930, 940, 980, 1023},
{ 0,  32,  64,  67,  70,  72,  75,  88, 102, 116, 132, 145, 157, 172, 188, 205, 219, \
235, 250, 265, 282, 298, 315, 335, 355, 372, 390, 412, 435, 458, 480, 512, 1023, \
 0,  32,  64,  67,  70,  72,  75,  88, 102, 116, 132, 145, 157, 172, 188, 205, 219, \
235, 250, 265, 282, 298, 315, 335, 355, 372, 390, 412, 435, 458, 480, 512, 1023, \
 0,  32,  64,  67,  70,  72,  75,  88, 102, 116, 132, 145, 157, 172, 188, 205, 219, \
235, 250, 265, 282, 298, 315, 335, 355, 372, 390, 412, 435, 458, 480, 512, 1023},
{ 0, 512, 544, 569, 589, 612, 634, 654, 669, 689, 709, 725, 742, 755, 774, 790, 805, \
820, 836, 850, 867, 880, 892, 907, 922, 925, 927, 931, 934, 937, 940, 970, 1023, \
 0, 512, 544, 569, 589, 612, 634, 654, 669, 689, 709, 725, 742, 755, 774, 790, 805, \
820, 836, 850, 867, 880, 892, 907, 922, 925, 927, 931, 934, 937, 940, 970, 1023, \
 0, 512, 544, 569, 589, 612, 634, 654, 669, 689, 709, 725, 742, 755, 774, 790, 805, \
820, 836, 850, 867, 880, 892, 907, 922, 925, 927, 931, 934, 937, 940, 970, 1023}};

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/

/*============================================================================
	Implementation Group
============================================================================*/

#define _KWRAP_PE_DCM_
/**
 * set dyn cont enhance config
 * - use input struct LX_PE_DCM_DCE_CONF_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDceConfig(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_KWRAP_INFO_T *p_inf = &_g_pe_info;
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20 || PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		UINT32 i=0;
		LX_PE_DCM_DCE_CONF_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_DCM_DCE_CONF_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_DCE_CONF_T *)param;
			PE_KWRAP_DBG_PRINT(DCM, \
				"wid:%d, domain:%d, min, max:%d, %d\n", \
				pp->win_id, pp->domain, pp->min_pos, pp->max_pos);
			/* update dce config */
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				if (pp->win_id==i||pp->win_id==LX_PE_WIN_ALL)
					memcpy(&p_inf->dce_cfg[i], pp, sizeof(LX_PE_DCM_DCE_CONF_T));
			}
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_DCM_DCE_CONF_T, DCM);
			#endif
			ret = PE_DCM_SetDceConfig(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get current dyn cont enhance config from stored value
 * - use input struct LX_PE_DCM_DCE_CONF_T for M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCurDceConfig(void *param)
{
	int ret = RET_OK;
	PE_KWRAP_INFO_T *p_inf = &_g_pe_info;
	LX_PE_DCM_DCE_CONF_T *pp = NULL;
	do {
		CHECK_KNULL(ret, param);
		pp = (LX_PE_DCM_DCE_CONF_T *)param;
		if (pp->win_id>=LX_PE_WIN_ALL)
		{
			p_inf->dce_cfg[LX_PE_WIN_0].win_id = pp->win_id;
			memcpy(pp, &p_inf->dce_cfg[LX_PE_WIN_0], sizeof(LX_PE_DCM_DCE_CONF_T));
		}
		else
		{
			p_inf->dce_cfg[pp->win_id].win_id = pp->win_id;
			memcpy(pp, &p_inf->dce_cfg[pp->win_id], sizeof(LX_PE_DCM_DCE_CONF_T));
		}
		PE_KWRAP_DBG_PRINT(DCM, \
			"wid:%d, domain:%d, min, max:%d, %d\n", \
			pp->win_id, pp->domain, pp->min_pos, pp->max_pos);
	}while (0);
	return ret;
}
/**
 * get dyn cont enhance config
 * - use input struct LX_PE_DCM_DCE_CONF_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDceConfig(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_DCM_GetDceConfig((LX_PE_DCM_DCE_CONF_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set dyn cont enhance lut by specific value
 *	- input data : see PE_KWRAP_DCM_DCE_LUT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDceLutCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 i=0, x_data=0, y_data=0;
	UINT32 param_data=0;
	const UINT32 *p_val=NULL;
	LX_PE_DCM_DCE_LUT_T ctrl;
	ctrl.data = NULL;
	do {
		CHECK_KNULL(ret, param);
		PE_KWRAP_DBG_PRINT(DCM, \
			"wid:%d, data:%d\n", param->wid, param->data);
		ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
			LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
		ctrl.size = PE_KWRAP_DCM_LUT_STEP;
		ctrl.data = (UINT32 *)malloc(sizeof(UINT32)*ctrl.size);
		PE_CHECK_CODE(!ctrl.data, break, \
			"[%s,%d]malloc fail.\n", __F__, __L__);
		param_data = (param->data<PE_KWRAP_DCM_DCE_LUT_NUM)? \
			param->data:PE_KWRAP_DCM_DCE_LUT_BYPASS;
		p_val = &(g_pe_kwrap_p_dce_lut_curve[param_data][0]);
		for (i=0;i<ctrl.size;i++)
		{
			x_data = (g_pe_kwrap_p_dce_lut_curve[0][i])<<16;
			y_data = p_val[i];
			if (y_data>0x3ff)	y_data=0x3ff;
			ctrl.data[i] = x_data + y_data;
		}
		ret = KWRAP_PE_SetDceLutParam((void *)&ctrl);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]KWRAP_PE_SetDceLutParam.\n", __F__, __L__);
	}while (0);
	if (ctrl.data)	free(ctrl.data);
	return ret;
}
/**
 * set dyn cont enhance lut
 * - use input struct LX_PE_DCM_DCE_LUT_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDceLutParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TASK_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 ||PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_DCM_DCE_LUT_T *pp = NULL;
		#ifdef PE_KWRAP_SIMPLE_CHK_VALID_WIN_ID
		UINT32 set_cnt, i;
		static UINT32 pre_data[PE_KWRAP_DCM_LUT_STEP] = \
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		#else
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0;
		static UINT32 chk = 0x0;
		static UINT32 prev[LX_PE_WIN_NUM][PE_KWRAP_DCM_LUT_STEP];
		#endif
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_DCE_LUT_T *)param;
			#ifdef PE_KWRAP_SIMPLE_CHK_VALID_WIN_ID
			/* null check */
			CHECK_KNULL(ret, pp->data);
			/* support win0 only */
			PE_CHECK_ACTION(pp->win_id!=LX_PE_WIN_0, ret=RET_OK;break);
			/* support 16step only */
			PE_CHECK_ACTION(pp->size!=PE_KWRAP_DCM_LUT_STEP, ret=RET_OK;break);
			/* simple compare */
			set_cnt = 0;
			for (i=0; i<PE_KWRAP_DCM_LUT_STEP; i++)
			{
				if (pre_data[i] != pp->data[i])
				{
					pre_data[i] = pp->data[i];
					set_cnt++;
				}
			}
			/* if set_cnt==0, do nothing */
			PE_CHECK_ACTION(set_cnt==0, ret=RET_OK;break);
			#else
			/* too many print */
			//PE_KWRAP_DBG_PRINT(DCM, "wid:%d, size:%d\n", pp->win_id, pp->size);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			/* dont need to check */
			//KWRAP_PE_UpdateCheckState(pp->win_id, &chk, __F__, __L__);
			size = sizeof(UINT32)*PE_KWRAP_DCM_LUT_STEP;
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk, (void *)prev, (void *)(pp->data), size);
			/* too many print */
			//PE_KWRAP_SHOW_CHK(DCM, wid, chk);
			PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			pp->win_id = (LX_PE_WIN_ID)wid;
			#endif
			#endif
			ret = PE_DCM_SetDceLut(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TASK_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get dyn cont enhance lut
 * - use input struct LX_PE_DCM_DCE_LUT_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDceLutParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_DCM_GetDceLut((LX_PE_DCM_DCE_LUT_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set dyn saturation enhance lut by specific value
 *	- input data : see PE_KWRAP_DCM_DSE_LUT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDseLutCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 i=0, x_data=0, y_data=0;
	UINT32 param_data=0;
	const UINT32 *p_val=NULL;
	LX_PE_DCM_DSE_LUT_T ctrl;
	ctrl.data = NULL;
	do {
		CHECK_KNULL(ret, param);
		PE_KWRAP_DBG_PRINT(DCM, \
			"wid:%d, data:%d\n", param->wid, param->data);
		ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
			LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
		ctrl.size = PE_KWRAP_DCM_LUT_STEP;
		ctrl.data = (UINT32 *)malloc(sizeof(UINT32)*ctrl.size);
		PE_CHECK_CODE(!ctrl.data, break, \
			"[%s,%d]malloc fail.\n", __F__, __L__);
		param_data = (param->data<PE_KWRAP_DCM_DSE_LUT_NUM)? \
			param->data:PE_KWRAP_DCM_DSE_LUT_BYPASS;
		p_val = &(g_pe_kwrap_p_dse_lut_curve[param_data][0]);
		for (i=0;i<ctrl.size;i++)
		{
			x_data = (g_pe_kwrap_p_dse_lut_curve[0][i])<<16;
			y_data = p_val[i];
			if (y_data>0x3ff)	y_data=0x3ff;
			ctrl.data[i] = x_data + y_data;
		}
		ret = KWRAP_PE_SetDseLutParam((void *)&ctrl);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]KWRAP_PE_SetDseLutParam.\n", __F__, __L__);
	}while (0);
	if (ctrl.data)	free(ctrl.data);
	return ret;
}
/**
 * set dyn saturation enhance lut
 * - use input struct LX_PE_DCM_DSE_LUT_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDseLutParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TASK_BEGIN();
	if (PE_KDRV_VER_O20 ||PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_DCM_DSE_LUT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0;
		static UINT32 chk = 0x0;
		static UINT32 prev[LX_PE_WIN_NUM][PE_KWRAP_DCM_LUT_STEP];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_DSE_LUT_T *)param;
			/* too many print */
			PE_KWRAP_DBG_PRINT(DCM, "wid:%d, size:%d\n", pp->win_id, pp->size);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			/* dont need to check */
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk, __F__, __L__);
			size = sizeof(UINT32)*PE_KWRAP_DCM_LUT_STEP;
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk, (void *)prev, (void *)(pp->data), size);
			/* too many print */
			PE_KWRAP_SHOW_CHK(DCM, wid, chk);
			PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			pp->win_id = (LX_PE_WIN_ID)wid;
			#endif
			ret = PE_DCM_SetDseLut(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TASK_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get dyn saturation enhance lut
 * - use input struct LX_PE_DCM_DSE_LUT_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDseLutParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_DCM_GetDseLut((LX_PE_DCM_DSE_LUT_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set hdr lut by specific value
 *	- input data : see PE_KWRAP_DCM_DCE_LUT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetHdrLutCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 i=0, x_data=0, y_data=0;
	UINT32 param_data=0, lut_step=0;
	const UINT32 *p_val=NULL;
	LX_PE_DCM_HDR_LUT_T ctrl;
	ctrl.data = NULL;
	do {
		CHECK_KNULL(ret, param);
		PE_KWRAP_DBG_PRINT(DCM, \
			"wid:%d, data:%d\n", param->wid, param->data);
		ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
			LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
		ctrl.size=lut_step=PE_KWRAP_HDR_TLUT_STEP;
		ctrl.data = (UINT32 *)malloc(sizeof(UINT32)*ctrl.size);
		PE_CHECK_CODE(!ctrl.data, break, \
			"[%s,%d]malloc fail.\n", __F__, __L__);
		param_data = (param->data<PE_KWRAP_DCM_DCE_LUT_NUM)? \
			param->data:PE_KWRAP_DCM_DCE_LUT_BYPASS;
		p_val = &(g_pe_kwrap_p_hdr_lut_curve[param_data][0]);
		for (i=0;i<ctrl.size;i++)
		{
			x_data = (g_pe_kwrap_p_hdr_lut_curve[0][i])<<16;
			y_data = p_val[i];
			if (y_data>0x3ff)	y_data=0x3ff;
			ctrl.data[i]=x_data+y_data;
		}
		ret = KWRAP_PE_SetHdrLutParam((void *)&ctrl);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]KWRAP_PE_SetHdrLutParam.\n", __F__, __L__);
	}while (0);
	if (ctrl.data)	free(ctrl.data);
	return ret;
}
/**
 * set hdr lut
 * - use input struct LX_PE_DCM_HDR_LUT_T
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetHdrLutParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TASK_BEGIN();

	PE_KWRAP_NOTI_NOT_SUPPORTED();

	PE_TASK_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get hdr lut
 * - use input struct LX_PE_DCM_HDR_LUT_T
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetHdrLutParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	PE_KWRAP_NOTI_NOT_SUPPORTED();

	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set hdr mode
 * - use input struct LX_PE_DCM_HDR_MODE_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetHdrMode(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	PE_KWRAP_NOTI_NOT_SUPPORTED();

	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get hdr mode
 * - use input struct LX_PE_DCM_HDR_MODE_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetHdrMode(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	PE_KWRAP_NOTI_NOT_SUPPORTED();

	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set dyn cont blending
 * - use input struct LX_PE_DCM_BLENDING_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDceBlending(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20|| PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_DCM_BLENDING_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_DCM_BLENDING_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_BLENDING_T *)param;
			PE_KWRAP_DBG_PRINT(DCM, \
				"wid:%d, out_g:%d, rgn_sel:0x%x\n", \
				pp->win_id, pp->color_out_gain, pp->region_sel);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_DCM_BLENDING_T, DCM);
			#endif
			ret = PE_DCM_SetDceBlendingCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get dyn cont blending
 * - use input struct LX_PE_DCM_BLENDING_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDceBlending(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_DCM_GetDceBlendingCtrl((LX_PE_DCM_BLENDING_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set drc mode
 * - use input struct LX_PE_DCM_DRC_MODE_T for H15
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDceDrcMode(void *param)
{
	int ret = RET_OK;
	UINT32 i=0;
	PE_KWRAP_INFO_T *p_inf = &_g_pe_info;
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TASK_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20||PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_DCM_DRC_MODE_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0;
		static UINT32 chk = 0x0;
		static LX_PE_DCM_DRC_MODE_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_DRC_MODE_T *)param;
			/* too many print */
			/*PE_KWRAP_DBG_PRINT(DCM, \
				"set[wid:%d] dc_md,byps,sc_cnt:%d,%d,%d,%d\n", \
				pp->win_id, pp->dc_mode, pp->dc_bypass, pp->dc_sc_cnt, pp->picture_mode);*/
			/* update disp info */
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				if (pp->win_id==i||pp->win_id==LX_PE_WIN_ALL)
					memcpy(&p_inf->drc_mode[i], pp, sizeof(LX_PE_DCM_DRC_MODE_T));
			}
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			for (i=0;i<LX_PE_WIN_ALL;i++)
			{
				prev[i].win_id=pp->win_id;
			}
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk, __F__, __L__);
			size = sizeof(LX_PE_DCM_DRC_MODE_T);
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk, (void *)prev, (void *)pp, size);
			/* too many print */
			/*PE_KWRAP_SHOW_CHK(DCM, wid, chk);*/
			PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			pp->win_id = (LX_PE_WIN_ID)wid;
			#endif
			ret = PE_DCM_SetDceDrcMode(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TASK_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get current drc mode from stored value
 * - use input struct LX_PE_DCM_DRC_MODE_T for H15
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetCurDceDrcMode(void *param)
{
	int ret = RET_OK;
	PE_KWRAP_INFO_T *p_inf = &_g_pe_info;
	LX_PE_DCM_DRC_MODE_T *pp = NULL;
	do {
		CHECK_KNULL(ret, param);
		pp = (LX_PE_DCM_DRC_MODE_T *)param;
		if (pp->win_id>=LX_PE_WIN_ALL)
		{
			p_inf->drc_mode[LX_PE_WIN_0].win_id = pp->win_id;
			memcpy(pp, &p_inf->drc_mode[LX_PE_WIN_0], sizeof(LX_PE_DCM_DRC_MODE_T));
		}
		else
		{
			p_inf->drc_mode[pp->win_id].win_id = pp->win_id;
			memcpy(pp, &p_inf->drc_mode[pp->win_id], sizeof(LX_PE_DCM_DRC_MODE_T));
		}
	}while (0);
	return ret;
}
/**
 * get current drc mode from drv
 * - use input struct LX_PE_DCM_DRC_MODE_T for H15
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDceDrcMode(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_DCM_GetDceDrcMode((LX_PE_DCM_DRC_MODE_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set dyn dse ctrl
 * - use input struct LX_PE_DCM_DSE_CTRL_T for M16
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDseCtrl(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20 ||PE_KDRV_VER_E60)
	{
		LX_PE_DCM_DSE_CTRL3_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_DCM_DSE_CTRL3_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_DSE_CTRL3_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_DCM_DSE_CTRL3_T, DCM);
			#endif
			ret = PE_DCM_SetDseCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if(PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		LX_PE_DCM_DSE_CTRL2_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_DCM_DSE_CTRL2_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_DSE_CTRL2_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_DCM_DSE_CTRL2_T, DCM);
			#endif
			ret = PE_DCM_SetDseCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get dyn cont blending
 * - use input struct LX_PE_DCM_DSE_CTRL_T for M16
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDseCtrl(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_DCM_GetDseCtrl((LX_PE_DCM_DSE_CTRL2_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set dyn dse ctrl
 * - use input struct LX_PE_DCM_DSE_CTRL_T for M16
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDrcCurv(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 ||PE_KDRV_VER_O20 ||PE_KDRV_VER_M19)
	{
		do {
			CHECK_KNULL(ret, param);
			ret = PE_DCM_SetDrcCurv((LX_PE_DCM_DRC_CUV_T *)param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set dyn dse ctrl
 * - use input struct LX_PE_DCM_DSE_CTRL_T for M16
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDrcCtrl(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 ||PE_KDRV_VER_M19)
	{
		LX_PE_DCM_DRC_CONT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_DCM_DRC_CONT_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_DRC_CONT_T *)param;
			PE_KWRAP_DBG_PRINT(DCM, \
				"DRC table:\n"\
				"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
				"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n",\
				pp->pre_norm,pp->cur_norm,pp->pre_sc,pp->cur_sc,
				pp->ui_gain_w,pp->ui_gain_b,pp->vy_mode);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_DCM_DRC_CONT_T, DCM);
			#endif
			ret = PE_DCM_SetDrcCtrl(pp);
			PE_KWRAP_DBG_PRINT(DCM, \
				"DRC table:\n"\
				"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
				"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n",\
				pp->pre_norm,pp->cur_norm,pp->pre_sc,pp->cur_sc,
				pp->ui_gain_w,pp->ui_gain_b,pp->vy_mode);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get dyn cont blending
 * - use input struct LX_PE_DCM_DSE_CTRL_T for M16
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDrcCtrl(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18 || PE_KDRV_VER_M17)
	{
		ret = PE_DCM_GetDrcCtrl((LX_PE_DCM_DRC_CONT_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set dyn dse ctrl
 * - use input struct LX_PE_DCM_OBC_CTRL_T for O18
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetObcCtrl(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18)
	{
		LX_PE_DCM_OBC_CTRL_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_DCM_OBC_CTRL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_OBC_CTRL_T *)param;
			PE_KWRAP_DBG_PRINT(DCM, \
			"object_fg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"object_fg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"object_bg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"object_bg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"fg_gain_x0,x1: %d, %d,\n"\
			"fg_gain_y0,y1: %d, %d,\n"\
			"bg_gain_x0,x1: %d, %d,\n"\
			"bg_gain_y0,y1: %d, %d,\n",\
			pp->object_fg_x[0],pp->object_fg_x[1],pp->object_fg_x[2],pp->object_fg_x[3], \
			pp->object_fg_x[4],pp->object_fg_x[5],pp->object_fg_x[6],pp->object_fg_x[7], \
			pp->object_fg_y[0],pp->object_fg_y[1],pp->object_fg_y[2],pp->object_fg_y[3], \
			pp->object_fg_y[4],pp->object_fg_y[5],pp->object_fg_y[6],pp->object_fg_y[7], \
			pp->object_bg_x[0],pp->object_bg_x[1],pp->object_bg_x[2],pp->object_bg_x[3], \
			pp->object_bg_x[4],pp->object_bg_x[5],pp->object_bg_x[6],pp->object_bg_x[7], \
			pp->object_bg_y[0],pp->object_bg_y[1],pp->object_bg_y[2],pp->object_bg_y[3], \
			pp->object_bg_y[4],pp->object_bg_y[5],pp->object_bg_y[6],pp->object_bg_y[7], \
			pp->fg_gain_x0,pp->fg_gain_x1,pp->fg_gain_y0,pp->fg_gain_y1, \
			pp->bg_gain_x0,pp->bg_gain_x1,pp->bg_gain_y0,pp->bg_gain_y1);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_DCM_OBC_CTRL_T, DCM);
			#endif
			ret = PE_DCM_SetObcCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get dyn cont blending
 * - use input struct LX_PE_DCM_OBC_CTRL_T for O18
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetObcCtrl(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18)
	{
		ret = PE_DCM_GetObcCtrl((LX_PE_DCM_OBC_CTRL_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * get 
 * - use input struct LX_PE_DCM_OBC_DATA_T for O18
 *
 * @param	*param [in/out] void
 * @return	OK if success, ERROR otherwise.
 * @see 	func. description
 * @author
 */
int KWRAP_PE_GetObcData(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20)
	{
		LX_PE_DCM_OBC1_DATA_T *pp = NULL;
		pp = (LX_PE_DCM_OBC1_DATA_T *)param;
		ret = PE_DCM_GetObcData(pp);
		PE_KWRAP_DBG_PRINT(DCM, \
		"object_relibility: %d\n"\
		"object_fg_pel_num: %d\n"\
		"object_fg_apl: 	%d\n"\
		"object_bg_pel_num: %d\n"\
		"object_bg_apl: 	%d\n"\
		"object_boxh1:		%d\n"\
		"object_boxh2:		%d\n"\
		"object_boxw1:		%d\n"\
		"object_boxw2:		%d\n",\
		pp->object_relibility, \
		pp->object_fg_pel_num, \
		pp->object_fg_apl, \
		pp->object_bg_pel_num, \
		pp->object_bg_apl, \
		pp->object_boxh1, \
		pp->object_boxh2, \
		pp->object_boxw1, \
		pp->object_boxw2);
	}
	else if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_DCM_OBC_DATA_T *pp = NULL;
		pp = (LX_PE_DCM_OBC_DATA_T *)param;
		ret = PE_DCM_GetObcData(pp);
		PE_KWRAP_DBG_PRINT(DCM, \
		"object_relibility: %d\n"\
		"object_fg_pel_num: %d\n"\
		"object_fg_apl: 	%d\n"\
		"object_bg_pel_num: %d\n"\
		"object_bg_apl: 	%d\n"\
		"object_boxh1:		%d\n"\
		"object_boxh2:		%d\n"\
		"object_boxw1:		%d\n"\
		"object_boxw2:		%d\n",\
		pp->object_relibility, \
		pp->object_fg_pel_num, \
		pp->object_fg_apl, \
		pp->object_bg_pel_num, \
		pp->object_bg_apl, \
		pp->object_boxh1, \
		pp->object_boxh2, \
		pp->object_boxw1, \
		pp->object_boxw2);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set dyn tone mapping lut
 * - use input struct LX_PE_DCM_DTM_LUT_T 
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDtmLutParam(void *param)
{
#define PE_KWRAP_DTM_LUT_STEP 33
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(DCM);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TASK_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_DCM_DTM_LUT_T *pp = NULL;
		#ifdef PE_KWRAP_SIMPLE_CHK_VALID_WIN_ID
		UINT32 set_cnt, i;
		static UINT32 pre_data[PE_KWRAP_DTM_LUT_STEP] = \
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
			 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
			 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
			 0, 0, 0};
		#else
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0;
		static UINT32 chk = 0x0;
		static UINT32 prev[LX_PE_WIN_NUM][PE_KWRAP_DTM_LUT_STEP];
		#endif
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_DCM_DTM_LUT_T *)param;
			#ifdef PE_KWRAP_SIMPLE_CHK_VALID_WIN_ID
			/* null check */
			CHECK_KNULL(ret, pp->data);
			/* support win0 only */
			PE_CHECK_ACTION(pp->win_id!=LX_PE_WIN_0, ret=RET_OK;break);
			/* support 16step only */
			PE_CHECK_ACTION(pp->size!=PE_KWRAP_DTM_LUT_STEP, ret=RET_OK;break);
			/* simple compare */
			set_cnt = 0;
			for (i=0; i<PE_KWRAP_DTM_LUT_STEP; i++)
			{
				if (pre_data[i] != pp->data[i])
				{
					pre_data[i] = pp->data[i];
					set_cnt++;
				}
			}
			/* if set_cnt==0, do nothing */
			PE_CHECK_ACTION(set_cnt==0, ret=RET_OK;break);
			#else
			/* too many print */
			//PE_KWRAP_DBG_PRINT(DCM, "wid:%d, size:%d\n", pp->win_id, pp->size);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			/* dont need to check */
			//KWRAP_PE_UpdateCheckState(pp->win_id, &chk, __F__, __L__);
			size = sizeof(UINT32)*PE_KWRAP_DTM_LUT_STEP;
			wid = KWRAP_PE_CheckValidWinId(pp->win_id, \
				&chk, (void *)prev, (void *)(pp->data), size);
			/* too many print */
			//PE_KWRAP_SHOW_CHK(DCM, wid, chk);
			PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			pp->win_id = (LX_PE_WIN_ID)wid;
			#endif
			#endif
			ret = PE_DCM_SetDtmLut(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TASK_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get dyn tone mapping lut
 * - use input struct LX_PE_DCM_DTM_LUT_T 
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDtmLutParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20)
	{
		ret = PE_DCM_GetDtmLut((LX_PE_DCM_DTM_LUT_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

