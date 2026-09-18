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

/** @file pe_kwrap_csc.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- master pe kwrap file includes init & misc functions
 *
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
#include "pe_drv.h"
#include "pe_kwrap.h"
#include "pe_csc.h"
#include "pe_kwrap_def.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/
/* input(cvi) csc */
const UINT16 g_pe_kwrap_p_input_mtrx_bypass[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0x0000, 0x0000,		//  1.0000, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const UINT16 g_pe_kwrap_p_input_mtrx_limit[PE_NUM_OF_CSC_COEF]= {
	0x0db0, 0x0000, 0x0000,		//  0.8555, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const UINT16 g_pe_kwrap_p_input_mtrx_expend[PE_NUM_OF_CSC_COEF]= {
	0x1166, 0x0000, 0x0000,		//  1.0874, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const UINT16 g_pe_kwrap_p_input_mtrx_expend_cvd[PE_NUM_OF_CSC_COEF]= {
	0x1142, 0x0000, 0x0000,		//  1.0786, 0.0000, 0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000, 1.0000, 0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000, 0.0000, 1.0000
const UINT16 g_pe_kwrap_p_input_rgb_y709_linear[PE_NUM_OF_CSC_COEF]= {
	0x0b70, 0x0126, 0x0368,		//  0.7148, 0.0718, 0.2129
	0xf9b3, 0x082d, 0xfe22,		// -0.3938, 0.5110,-0.1167
	0xf894, 0xff40, 0x082d};	// -0.4639,-0.0469, 0.5110
const UINT16 g_pe_kwrap_p_input_rgb_y709_limit[PE_NUM_OF_CSC_COEF]= {
	0x09d2, 0x00fd, 0x02ed,		//  0.6138, 0.0618, 0.1829
	0xfa98, 0x0706, 0xfe62,		// -0.3379, 0.4390,-0.1011
	0xf99e, 0xff5d, 0x0706};	// -0.3989,-0.0398, 0.4390
const UINT16 g_pe_kwrap_p_input_rgb_y601_linear[PE_NUM_OF_CSC_COEF]= {
	0x0964, 0x01d2, 0x04c8,		//  0.5869, 0.1138, 0.2988
	0xfa94, 0x082d, 0xfd40,		// -0.3389, 0.5110,-0.1719
	0xf927, 0xfead, 0x082d};	// -0.4280,-0.0828, 0.5110
const UINT16 g_pe_kwrap_p_input_rgb_y601_limit[PE_NUM_OF_CSC_COEF]= {
	0x0810, 0x0191, 0x041c,		//  0.5039, 0.0979, 0.2568
	0xfb59, 0x0706, 0xfda2,		// -0.2908, 0.4390,-0.1479
	0xfa1d, 0xfede, 0x0706};	// -0.3679,-0.0708, 0.4390
const UINT16 g_pe_kwrap_p_input_rgb_y601_secam[PE_NUM_OF_CSC_COEF]= {
	0x1000, 0x0000, 0x0000,		//  1.0000, 0.0000, 0.0000
	0x0000, 0x0de4, 0x0000,		//  0.0000, 0.8682, 0.0000
	0x0000, 0x0000, 0x131f};	//  0.0000, 0.0000, 1.1951
const UINT16 g_pe_kwrap_p_input_ofst_bypass[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0000, 0x0000, 0x0000};	//   0,   0,   0
const UINT16 g_pe_kwrap_p_input_ofst_limit[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0040, 0x0000, 0x0000};	//  64,   0,   0
const UINT16 g_pe_kwrap_p_input_ofst_expend[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0xffae, 0x0000, 0x0000};	// -82,   0,   0
const UINT16 g_pe_kwrap_p_input_ofst_expend_cvd[PE_NUM_OF_CSC_OFST] = {
	0x0780, 0x0000, 0x0000,		//-128,   0,   0
	0x0040, 0x0000, 0x0000};	//  64,   0,   0
const UINT16 g_pe_kwrap_p_input_ofst_rgb_y_linear[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0000, 0x0200, 0x0200};	//   0, 512, 512
const UINT16 g_pe_kwrap_p_input_ofst_rgb_y_limit[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0040, 0x0200, 0x0200};	//  64, 512, 512
const UINT16 g_pe_kwrap_p_input_ofst_rgb_y_secam[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0xfe00, 0xfe00,		//   0,-512,-512
	0x0000, 0x0200, 0x0200};	//   0, 512, 512
/* gamut(pcc) csc */
const UINT16 g_pe_kwrap_p_gamut_bypass[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0x0000, 0x0000,		//  1.0000  0.0000  0.0000
	0x0000, 0x1000, 0x0000,		//  0.0000  1.0000  0.0000
	0x0000, 0x0000, 0x1000};	//  0.0000  0.0000  1.0000
const UINT16 g_pe_kwrap_p_gamut_ebu[PE_NUM_OF_CSC_COEF] = {
	0x0eb1, 0x0108, 0x0045,		//  1.0619 -0.0798  0.0179
	0x000b, 0x0ff3, 0x0000,		//  0.0048  1.0088 -0.0136
	0x7ff3, 0x0052, 0x0fbb};	//  0.0109  0.0148  0.9742
const UINT16 g_pe_kwrap_p_gamut_smpte[PE_NUM_OF_CSC_COEF] = {
	0x0d40, 0x024c, 0x0072,		//  0.9550  0.0169  0.0281
	0x0053, 0x0f69, 0x0043,		//  0.0222  0.9749  0.0028
	0x7fee, 0x000e, 0x1004};	//  0.0083 -0.0002  0.9919
const UINT16 g_pe_kwrap_p_gamut_bt709[PE_NUM_OF_CSC_COEF] = {
	0x0e12, 0x01a6, 0x0046,		//  1.0171 -0.0352  0.0181
	0x000b, 0x0ff4, 0x0000,		//  0.0046  1.0092 -0.0137
	0x7ff3, 0x0021, 0x0feb};	//  0.0105  0.0037  0.9859
/* post(output) csc */
const UINT16 g_pe_kwrap_p_post_mtrx_bypass[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0x0000, 0x0000,		//  1.000, 0.000, 0.000
	0x0000, 0x1000, 0x0000,		//  0.000, 1.000, 0.000
	0x0000, 0x0000, 0x1000};	//  0.000, 0.000, 1.000
const UINT16 g_pe_kwrap_p_post_y709_expend[PE_NUM_OF_CSC_COEF] = {
	0x129F, 0xFC98, 0xF775,		//  1.164,-0.213,-0.534
	0x129F, 0x21D7, 0x0000,   	//  1.164, 2.115, 0.000
	0x129F, 0x0000, 0x1CB0};  	//  1.164, 0.000, 1.793
const UINT16 g_pe_kwrap_p_post_y709_linear[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFD13, 0xF8A8,		//  1.000,-0.183,-0.459
	0x1000, 0x1D0E, 0x0000,   	//  1.000, 1.816, 0.000
	0x1000, 0x0000, 0x18A3};  	//  1.000, 0.000, 1.540
const UINT16 g_pe_kwrap_p_post_y601_expend[PE_NUM_OF_CSC_COEF] = {
	0x129F, 0xF9BF, 0xF2FE,		//  1.164,-0.391,-0.813
	0x129F, 0x2049, 0x0000,  	//  1.164, 2.018, 0.000
	0x129F, 0x0000, 0x1989};  	//  1.164, 0.000, 1.596
const UINT16 g_pe_kwrap_p_post_y601_linear[PE_NUM_OF_CSC_COEF] = {
	0x1000, 0xFAA0, 0xF4D5,		//  1.000,-0.336,-0.698
	0x1000, 0x1BB6, 0x0000,   	//  1.000, 1.732, 0.000
	0x1000, 0x0000, 0x15EF};  	//  1.000, 0.000, 1.371
const UINT16 g_pe_kwrap_p_post_ofst_bypass[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0x0000, 0x0000,		//   0,   0,   0
	0x0000, 0x0000, 0x0000};	//   0,   0,   0
const UINT16 g_pe_kwrap_p_post_ofst_expend[PE_NUM_OF_CSC_OFST] = {
	0xFFC0, 0xFE00, 0xFE00,		// -64,-512,-512
	0x0000, 0x0000, 0x0000};	//   0,   0,   0
const UINT16 g_pe_kwrap_p_post_ofst_linear[PE_NUM_OF_CSC_OFST] = {
	0x0000, 0xFE00, 0xFE00,		//   0,-512,-512
	0x0000, 0x0000, 0x0000};	//   0,   0,   0

/*============================================================================
	Implementation Group
============================================================================*/

/**
 * get post csc default settings
 *	- input data : see PE_KWRAP_POST_CSC_TYPE
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetPostCscDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	const UINT16 *p_mtrx=NULL;
	const UINT16 *p_ofst=NULL;
	LX_PE_CSC_POST_T *pp = NULL;
	do {
		CHECK_KNULL(ret, param);
		CHECK_KNULL(ret, param->st_data);
		pp = (LX_PE_CSC_POST_T *)param->st_data;
		switch (param->data)
		{
			case LX_PE_POST_CSC_Y709_EXPEND:
				p_mtrx=g_pe_kwrap_p_post_y709_expend;
				p_ofst=g_pe_kwrap_p_post_ofst_expend;
				break;
			case LX_PE_POST_CSC_Y709_LINEAR:
				p_mtrx=g_pe_kwrap_p_post_y709_linear;
				p_ofst=g_pe_kwrap_p_post_ofst_linear;
				break;
			case LX_PE_POST_CSC_Y601_EXPEND:
				p_mtrx=g_pe_kwrap_p_post_y601_expend;
				p_ofst=g_pe_kwrap_p_post_ofst_expend;
				break;
			case LX_PE_POST_CSC_Y601_LINEAR:
				p_mtrx=g_pe_kwrap_p_post_y601_linear;
				p_ofst=g_pe_kwrap_p_post_ofst_linear;
				break;
			case LX_PE_POST_CSC_BYPASS:
			default:
				p_mtrx=g_pe_kwrap_p_post_mtrx_bypass;
				p_ofst=g_pe_kwrap_p_post_ofst_bypass;
				break;
		}
		memcpy(pp->matrix, p_mtrx, sizeof(UINT16)*PE_NUM_OF_CSC_COEF);
		memcpy(pp->offset, p_ofst, sizeof(UINT16)*PE_NUM_OF_CSC_OFST);
	}while (0);
	return ret;
}

/**
 * set post csc by specific value
 *	- input data : see PE_KWRAP_POST_CSC_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetPostCscCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	LX_PE_CSC_POST_T ctrl;
	do {
		CHECK_KNULL(ret, param);
		param->st_data = (void *)&ctrl;
		ret = KWRAP_PE_GetPostCscDefaultSettings(param);
		PE_CHECK_CODE(ret, break, "KWRAP_PE_GetPostCscDefaultSettings() error.\n");
		ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
		ctrl.type = param->data;
		ret = KWRAP_PE_SetPostCscParam((void *)&ctrl);
		PE_CHECK_CODE(ret, break, "KWRAP_PE_SetPostCscParam() error.\n");
	}while (0);
	return ret;
}

/**
 * set post csc parameter
 * - use input struct LX_PE_CSC_POST_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetPostCscParam(void *param)
{
	int ret = RET_OK;
	LX_PE_CSC_POST_T *pp = NULL;
	do {
		CHECK_KNULL(ret, param);
		pp = (LX_PE_CSC_POST_T *)param;
		ret = PE_CSC_SetPostCsc(pp);
		PE_CHECK_CODE(ret, break, "PE_CSC_SetPostCsc() error.\n");
	}while (0);
	return ret;
}

/**
 * get post csc parameter
 * - use input struct LX_PE_CSC_POST_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetPostCscParam(void *param)
{
	int ret = RET_OK;
	LX_PE_CSC_POST_T *pp = NULL;
	do {
		CHECK_KNULL(ret, param);
		pp = (LX_PE_CSC_POST_T *)param;
		ret = PE_CSC_GetPostCsc(pp);
		PE_CHECK_CODE(ret, break, "PE_CSC_GetPostCsc() error.\n");
	}while (0);
	return ret;
}

/**
 * get input csc default settings
 *	- input data : see PE_KWRAP_INPUT_CSC_TYPE
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetInputCscDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	const UINT16 *p_mtrx=NULL;
	const UINT16 *p_ofst=NULL;
	LX_PE_CSC_INPUT_T *pp = NULL;
	do {
		CHECK_KNULL(ret, param);
		CHECK_KNULL(ret, param->st_data);
		pp = (LX_PE_CSC_INPUT_T *)param->st_data;
		switch (param->data)
		{
			case PE_KWRAP_INPUT_CSC_BYPASS:
				p_mtrx=g_pe_kwrap_p_input_mtrx_bypass;
				p_ofst=g_pe_kwrap_p_input_ofst_bypass;
				break;
			case PE_KWRAP_INPUT_CSC_LIMIT:
				p_mtrx=g_pe_kwrap_p_input_mtrx_limit;
				p_ofst=g_pe_kwrap_p_input_ofst_limit;
				break;
			case PE_KWRAP_INPUT_CSC_EXPEND:
				p_mtrx=g_pe_kwrap_p_input_mtrx_expend;
				p_ofst=g_pe_kwrap_p_input_ofst_expend;
				break;
			case PE_KWRAP_INPUT_CSC_EXPEND_CVD:
				p_mtrx=g_pe_kwrap_p_input_mtrx_expend_cvd;
				p_ofst=g_pe_kwrap_p_input_ofst_expend_cvd;
				break;
			case PE_KWRAP_INPUT_CSC_RGB_Y709_LINEAR:
				p_mtrx=g_pe_kwrap_p_input_rgb_y709_linear;
				p_ofst=g_pe_kwrap_p_input_ofst_rgb_y_linear;
				break;
			case PE_KWRAP_INPUT_CSC_RGB_Y709_LIMIT:
				p_mtrx=g_pe_kwrap_p_input_rgb_y709_limit;
				p_ofst=g_pe_kwrap_p_input_ofst_rgb_y_limit;
				break;
			case PE_KWRAP_INPUT_CSC_RGB_Y601_LINEAR:
				p_mtrx=g_pe_kwrap_p_input_rgb_y601_linear;
				p_ofst=g_pe_kwrap_p_input_ofst_rgb_y_linear;
				break;
			case PE_KWRAP_INPUT_CSC_RGB_Y601_LIMIT:
				p_mtrx=g_pe_kwrap_p_input_rgb_y601_limit;
				p_ofst=g_pe_kwrap_p_input_ofst_rgb_y_limit;
				break;
			case PE_KWRAP_INPUT_CSC_RGB_Y601_SECAM:
				p_mtrx=g_pe_kwrap_p_input_rgb_y601_secam;
				p_ofst=g_pe_kwrap_p_input_ofst_rgb_y_secam;
				break;
			default:
				p_mtrx=g_pe_kwrap_p_input_mtrx_bypass;
				p_ofst=g_pe_kwrap_p_input_ofst_bypass;
				break;
		}
		memcpy(pp->matrix, p_mtrx, sizeof(UINT16)*PE_NUM_OF_CSC_COEF);
		memcpy(pp->offset, p_ofst, sizeof(UINT16)*PE_NUM_OF_CSC_OFST);
	}while (0);
	return ret;
}

/**
 * set input csc by specific value(legacy)
 *	- input data : see PE_KWRAP_INPUT_CSC_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetInputCscCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	LX_PE_CSC_INPUT_T ctrl;
	do {
		CHECK_KNULL(ret, param);
		param->st_data = (void *)&ctrl;
		ret = KWRAP_PE_GetInputCscDefaultSettings(param);
		PE_CHECK_CODE(ret, break, "KWRAP_PE_GetInputCscDefaultSettings() error.\n");
		ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
		ctrl.enable = 0x1;
		ret = KWRAP_PE_SetInputCscParam((void *)&ctrl);
		PE_CHECK_CODE(ret, break, "KWRAP_PE_SetInputCscParam() error.\n");
	}while (0);
	return ret;
}

/**
 * set input csc parameter
 * - use input struct LX_PE_CSC_INPUT_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetInputCscParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_KWRAP_FUNC_ON(CSC);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60||PE_KDRV_VER_O20||PE_KDRV_VER_O22||PE_KDRV_VER_M23)
	{
		LX_PE_CSC_INPUT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		UINT32 size=0, wid=0;
		static UINT32 chk = 0x0;
		__attribute__((unused)) static LX_PE_CSC_INPUT_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_CSC_INPUT_T *)param;
			PE_KWRAP_DBG_PRINT(CSC, \
				"wid:%d:en:%d, coef:%x,%x,%x,%x,%x,%x,%x,%x,%x\n"\
				"ofs:%x,%x,%x,%x,%x,%x\n", pp->win_id, pp->enable, \
				pp->matrix[0], pp->matrix[1], pp->matrix[2], pp->matrix[3], \
				pp->matrix[4], pp->matrix[5], pp->matrix[6], pp->matrix[7], \
				pp->matrix[8], pp->offset[0], pp->offset[1], pp->offset[2], \
				pp->offset[3], pp->offset[4], pp->offset[5]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			KWRAP_PE_UpdateCheckState(pp->win_id, &chk, __F__, __L__);
			size = sizeof(LX_PE_CSC_INPUT_T);
			/* not apply all win setting for input csc ctrl */
			if (pp->win_id==LX_PE_WIN_ALL)	pp->win_id=LX_PE_WIN_0;
			//wid = KWRAP_PE_CheckDoubleSetting(pp->win_id, &chk, (void *)prev, (void *)pp, size);
			PE_KWRAP_SHOW_CHK(CSC, wid, chk);
			PE_CHECK_ACTION(wid>LX_PE_WIN_ALL, ret=RET_OK;break);
			#endif
			ret = PE_CSC_SetInputCsc(pp);
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
 * get input csc parameter
 * - use input struct LX_PE_CSC_INPUT_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetInputCscParam(void *param)
{
	int ret = RET_OK;
	LX_PE_CSC_INPUT_T *pp = NULL;
	do {
		CHECK_KNULL(ret, param);
		pp = (LX_PE_CSC_INPUT_T *)param;
		ret = PE_CSC_GetInputCsc(pp);
		PE_CHECK_CODE(ret, break, "PE_CSC_GetInputCsc() error.\n");
	}while (0);
	return ret;
}

