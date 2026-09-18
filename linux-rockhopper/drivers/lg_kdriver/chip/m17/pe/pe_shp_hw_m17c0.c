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

/** @file pe_shp_hw_m17c0.c
 *
 *  driver for picture enhance sharpness functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj,S(kanthiraj.s@lge.com) - for SWMD code restrcuturing
 *	@version	0.1
 *	@note
 *	@date		2011.04.12
  *	@modified date	2015.05.25
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
/* sr cg(clock gating) test tracing */
#undef PE_SHP_HW_M17C0_SR_PWD_TRACE

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/delay.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_hw_m17c0.h"
#include "pe_reg_m17.h"
#include "pe_fwi_m17c0.h"
#include "pe_cmn_hw_m17c0.h"
#include "pe_hst_hw_m17c0.h"
#include "pe_shp_hw_m17c0.h"
#include "pe_res_hw_param_m17c0.h"
#include "pe_cti_dnr_hw_param_m17c0.h"
#include "pe_pblur_dnr_hw_param_m17c0.h"
#include "cvd_module.h"

/* core hw param */
#include "pe_shp_scl256_def.h"

#ifdef PE_SHP_HW_M17C0_SR_PWD_TRACE
#include "../../sys/sys_regs.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_HW_M17C0_FHD_H_MAX					1920
#define PE_SHP_HW_M17C0_FHD_V_MAX					1080
#define PE_SHP_HW_M17C0_SCL_IN_H_MIN				160
#define PE_SHP_HW_M17C0_SCL_IN_V_MIN				120
#define PE_SHP_HW_M17C0_IDX_Y_DFLT				15
#define PE_SHP_HW_M17C0_IDX_C_DFLT				39

#define PE_SHP_HW_M17C0_SCL_SIZE_MIN				(10)
#define PE_SHP_HW_M17C0_SCL_SIZE_1K				(1024)
#define PE_SHP_HW_M17C0_SCL_SIZE_2K				(2048)
#define PE_SHP_HW_M17C0_SCL_VSC_MD_V12TAP			(12)
#define PE_SHP_HW_M17C0_SCL_VSC_MD_V06TAP			(6)
#define PE_SHP_HW_M17C0_SCL_VSC_MD_V02TAP			(2)
#define PE_SHP_HW_M17C0_SCL_VSC_MD_V08TAP			(8)
#define PE_SHP_HW_M17C0_SCL_VSC_MD_V04TAP			(4)
#define PE_SHP_HW_M17C0_SCL_ADAPTIVE_ON			(0x1)
#define PE_SHP_HW_M17C0_SCL_ADAPTIVE_OFF			(0x0)
#define PE_SHP_HW_M17C0_SCL_BILINEAR				(0x1)
#define PE_SHP_HW_M17C0_SCL_POLYPHASE				(0x0)
#define PE_SHP_HW_M17C0_SCL_C_FMT_444				(0x6)
#define PE_SHP_HW_M17C0_SCL_C_FMT_422				(0x5)
#define PE_SHP_HW_M17C0_SCL_C_FMT_420				(0x4)
#define PE_SHP_HW_M17C0_SCL_PXL_RP_OFF			(0x0)
#define PE_SHP_HW_M17C0_SCL_PXL_RP_RED			(0x1)
#define PE_SHP_HW_M17C0_SCL_PXL_RP_GRN			(0x2)
#define PE_SHP_HW_M17C0_SCL_PXL_RP_BLU			(0x3)
#define PE_SHP_HW_M17C0_SCL_CO_REG_INC_MAX		(128)
#define PE_SHP_HW_M17C0_SCL_G0Y					0
#define PE_SHP_HW_M17C0_SCL_G1Y					1
#define PE_SHP_HW_M17C0_SCL_G0C					2
#define PE_SHP_HW_M17C0_SCL_G1C					3
#define PE_SHP_HW_M17C0_SCL_P0Y					4
#define PE_SHP_HW_M17C0_SCL_DWN_LVL_NORM			(0)
#define PE_SHP_HW_M17C0_SCL_DWN_LVL_HALF			(1)
#define PE_SHP_HW_M17C0_SCL_DWN_LVL_QUAD			(2)
#define PE_SHP_HW_M17C0_SCL_DWN_LVL_OCTA			(3)

/* h,v only(define) vs. both(undef), Now we use both mode until getting c08t scl has no problem. */
#define PE_SHP_HW_M17C0_USE_V12TM_C08T_SEPARATE_HV

/* use MSR vs. SSC on venc mode, We are going to use SSC from M17C0A0. */
#undef PE_SHP_HW_M17C0_USE_MSR_FOR_VENC_ON

/* use define until shp f/w ready, M17C0A0 */
#define PE_SHP_HW_M17C0A_SET_FW_PARAM_TO_REG_DIRECTLY
#define PE_SHP_HW_M17C0_SET_FW_PARAM_TO_REG_DIRECTLY


/* 20140616, sj.youm, pe1_lap_h 1,2,4 not available because of rtl bug. set valid value(0,3,5) */
#undef PE_SHP_HW_M17C0_PROTECT_SP_LAP_H_MODE_BUG

/* 20141006, sj.youm, sre shp write only mode */
#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
#define PE_SHP_HW_M17C0_SRE_SHP_WR_ONLY_MD
#else
#undef PE_SHP_HW_M17C0_SRE_SHP_WR_ONLY_MD
#endif

/* 20141009, sj.youm, use sre shp write only mode */
#define PE_SHP_HW_M17C0_USE_SRE_SHP_WR_ONLY_MD

/* use internal scl filter coeff decision */
#define PE_SHP_HW_M17C0_SCL_CO_INTERNAL_DECISION

/* use shp L fw dummy reg for fw gsc ctrl write */
#undef PE_SHP_HW_M17C0_USE_FWS_REG_FOR_FW_GSC_WR

#define PE_SHP_HW_M17C0_SR_SHP_DONE

/* set motion shp enable by f/w */
#define PE_SHP_HW_M17C0_SHP_MOTION_ENABLE

#define PE_SHP_HW_M17C0_CROSS_PAT_DETECT

/*170823 inkyung.park, temporally block cti cme for chage DB */
#define PE_SHP_HW_M17C0_CTI_CMN_CHANGE

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#define PE_SHP_HW_M17C0_ERROR		PE_PRINT_ERROR

#ifdef PE_SHP_HW_M17C0_SR_PWD_TRACE
#define PE_SHP_HW_M17C0_DBG_SRPD_TRACE(fmt, args...)	\
	if(_g_shp_hw_m17c0_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

#define PE_SHP_HW_M17C0_DBG_PRINT(fmt, args...)
#else
#define PE_SHP_HW_M17C0_DBG_PRINT(fmt, args...)	\
	if(_g_shp_hw_m17c0_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}
#endif

#define PE_SHP_HW_M17C0_CHECK_CODE(_checker, _action, fmt, args...)	\
	{if(_checker){PE_SHP_HW_M17C0_ERROR(fmt, ##args);_action;}}

#define PE_SHP_HW_M17C0_DBG_CHECK_CODE(_cnt, _checker, _action, fmt, args...)	\
	{\
		if(_checker){\
			if(_g_shp_hw_m17c0_trace&&_cnt>PE_PRINT_COUNT_NUM)\
			{\
				PE_SHP_HW_M17C0_DBG_PRINT(fmt, ##args);\
			}\
			_action;\
		}\
	}

/* for M17C0*/
#define PE_SHP_HW_M17C0_DBG_PRINT_RES_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M17C0_RES_FMT_TO_STR(_pre), \
			PE_SHP_HW_M17C0_RES_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
#ifdef PE_SHP_HW_M17C0_SRE_SHP_WR_ONLY_MD
#define PE_SHP_HW_M17C0_DBG_PRINT_SRS_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M17C0_SRS_FMT_TO_STR(_pre), \
			PE_SHP_HW_M17C0_SRS_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
#endif
#define PE_SHP_HW_M17C0_DBG_PRINT_SRE_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M17C0_SRE_FMT_TO_STR(_pre), \
			PE_SHP_HW_M17C0_SRE_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_M17C0_DBG_PRINT_SRL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M17C0_SRL_FMT_TO_STR(_pre), \
			PE_SHP_HW_M17C0_SRL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_M17C0_DBG_PRINT_PBL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M17C0_PBL_FMT_TO_STR(_pre), \
			PE_SHP_HW_M17C0_PBL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_M17C0_DBG_PRINT_CTI_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M17C0_CTI_FMT_TO_STR(_pre), \
			PE_SHP_HW_M17C0_CTI_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}

#define PE_SHP_HW_M17C0_SET_SHDW_GSC_Y_TO_SHP(_dst, _src)	\
	(*((UINT32 *)&(gPE_SHP_M17C0.shdw.data->_dst))) = (*((UINT32 *)&(gPE_GSC_Y_M17C0.shdw.data->_src)))
#define PE_SHP_HW_M17C0_SET_SHDW_GSC_C_TO_SHP(_dst, _src)	\
	(*((UINT32 *)&(gPE_SHP_M17C0.shdw.data->_dst))) = (*((UINT32 *)&(gPE_GSC_C_M17C0.shdw.data->_src)))

#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
#define PE_SHP_HW_M17C0_RES_SET_USER(_r, _f, _d)	\
	{	_g_pe_res_hw_param_data_m17c0.reg_user.data->_r._f = (_d);\
		_g_pe_res_hw_param_data_m17c0.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_M17C0_RES_WR01(_r, _f1, _d1)	\
	{	PE_SHP_M17C0_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M17C0_RES_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_M17C0_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M17C0_RES_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_M17C0_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M17C0_RES_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_M17C0_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_M17C0_RES_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_M17C0_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_M17C0_RES_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SHP_M17C0_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_M17C0_RES_SET_USER(_r, _f6, _d6);}

#define PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f, _d)	\
	{	_g_pe_pbl_hw_param_data_m17c0.reg_user.data->_r._f = (_d);\
		_g_pe_pbl_hw_param_data_m17c0.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_M17C0_PBL_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_M17C0_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M17C0_PBL_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_M17C0_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M17C0_PBL_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_M17C0_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M17C0_PBL_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_M17C0_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_M17C0_PBL_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_M17C0_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M17C0_PBL_SET_USER(_r, _f5, _d5);}

#define PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f, _d)	\
	{	_g_pe_cti_hw_param_data_m17c0.reg_user.data->_r._f = (_d);\
		_g_pe_cti_hw_param_data_m17c0.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_M17C0_CTI_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SHP_M17C0_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M17C0_CTI_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_M17C0_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M17C0_CTI_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_M17C0_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M17C0_CTI_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_M17C0_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f4, _d4);}

#define PE_SHP_HW_M17C0_CTI_DNR0_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_M17C0_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M17C0_CTI_DNR0_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_M17C0_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M17C0_CTI_DNR0_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_M17C0_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M17C0_CTI_DNR0_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_M17C0_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_CTI_SET_USER(_r, _f4, _d4);}


/* sre shp(srs) */
#define PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f, _d)	\
	{	_g_pe_srs_hw_param_data_m17c0.reg_user.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_m17c0.reg_mask.data->_r._f = 0;}

#ifdef PE_SHP_HW_M17C0_USE_SRE_SHP_WR_ONLY_MD
/* for wr only mode */
#define PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f, _d)	\
	{	_g_pe_srs_hw_param_data_m17c0.reg_data.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_m17c0.reg_user.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_m17c0.reg_mask.data->_r._f = 0;}
#define PE_SHP_HW_M17C0_SRS_DATA_TO_U32(_r)	\
	(*((UINT32 *)&(_g_pe_srs_hw_param_data_m17c0.reg_data.data->_r)))

#define PE_SHP_HW_M17C0_SR_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SR_SHP_M17C0_Wr(_r,PE_SHP_HW_M17C0_SRS_DATA_TO_U32(_r));\
		PE_SR_SHP_M17C0_WrFL(_r);}
#define PE_SHP_HW_M17C0_SR_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SR_SHP_M17C0_Wr(_r,PE_SHP_HW_M17C0_SRS_DATA_TO_U32(_r));\
		PE_SR_SHP_M17C0_WrFL(_r);}
#define PE_SHP_HW_M17C0_SR_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SR_SHP_M17C0_Wr(_r,PE_SHP_HW_M17C0_SRS_DATA_TO_U32(_r));\
		PE_SR_SHP_M17C0_WrFL(_r);}
#define PE_SHP_HW_M17C0_SR_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SR_SHP_M17C0_Wr(_r,PE_SHP_HW_M17C0_SRS_DATA_TO_U32(_r));\
		PE_SR_SHP_M17C0_WrFL(_r);}
#define PE_SHP_HW_M17C0_SR_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f5, _d5);\
		PE_SR_SHP_M17C0_Wr(_r,PE_SHP_HW_M17C0_SRS_DATA_TO_U32(_r));\
		PE_SR_SHP_M17C0_WrFL(_r);}
#define PE_SHP_HW_M17C0_SR_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f5, _d5);\
		PE_SHP_HW_M17C0_SRS_SET_USER_DATA(_r, _f6, _d6);\
		PE_SR_SHP_M17C0_Wr(_r,PE_SHP_HW_M17C0_SRS_DATA_TO_U32(_r));\
		PE_SR_SHP_M17C0_WrFL(_r);}

#else	//#ifdef PE_SHP_HW_M17C0_USE_SRE_SHP_WR_ONLY_MD
#define PE_SHP_HW_M17C0_SR_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SR_SHP_M17C0_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M17C0_SR_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SR_SHP_M17C0_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M17C0_SR_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SR_SHP_M17C0_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M17C0_SR_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SR_SHP_M17C0_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_M17C0_SR_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SR_SHP_M17C0_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_M17C0_SR_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SR_SHP_M17C0_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_M17C0_SRS_SET_USER(_r, _f6, _d6);}

#endif	//#ifdef PE_SHP_HW_M17C0_USE_SRE_SHP_WR_ONLY_MD

/* set table */
#define PE_SHP_HW_M17C0_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_SHP_HW_M17C0_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_M17C0_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_M17C0_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_M17C0_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"[%s,%d] _data is null, not ready.\n", __F__, __L__);\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_M17C0_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			ret = PE_REG_M17_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_M17C0_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_SHP_HW_M17C0_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

/* shp */
#define PE_SHP_HW_M17C0_RES_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_res_hw_param_data_m17c0.reg_dflt.addr;\
		UINT32 *_user = _g_pe_res_hw_param_data_m17c0.reg_user.addr;\
		UINT32 *_mask = _g_pe_res_hw_param_data_m17c0.reg_mask.addr;\
		UINT32 *_data = _g_pe_res_hw_param_data_m17c0.reg_data.addr;\
		PE_SHP_HW_M17C0_CHECK_CODE(\
		(sizeof(PE_RES_HW_PARAM_REG_M17C0_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]res tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_M17C0_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* sre shp(srs) */
#define PE_SHP_HW_M17C0_SRS_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_srs_hw_param_data_m17c0.reg_dflt.addr;\
		UINT32 *_user = _g_pe_srs_hw_param_data_m17c0.reg_user.addr;\
		UINT32 *_mask = _g_pe_srs_hw_param_data_m17c0.reg_mask.addr;\
		UINT32 *_data = _g_pe_srs_hw_param_data_m17c0.reg_data.addr;\
		PE_SHP_HW_M17C0_CHECK_CODE(\
		(sizeof(PE_SRS_HW_PARAM_REG_M17C0_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]srs tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_M17C0_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* cti */
#define PE_SHP_HW_M17C0_CTI_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_cti_hw_param_data_m17c0.reg_dflt.addr;\
		UINT32 *_user = _g_pe_cti_hw_param_data_m17c0.reg_user.addr;\
		UINT32 *_mask = _g_pe_cti_hw_param_data_m17c0.reg_mask.addr;\
		UINT32 *_data = _g_pe_cti_hw_param_data_m17c0.reg_data.addr;\
		PE_SHP_HW_M17C0_CHECK_CODE(\
		(sizeof(PE_CTI_HW_PARAM_REG_M17C0_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]cti tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_M17C0_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* pbl */
#define PE_SHP_HW_M17C0_PBL_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_pbl_hw_param_data_m17c0.reg_dflt.addr;\
		UINT32 *_user = _g_pe_pbl_hw_param_data_m17c0.reg_user.addr;\
		UINT32 *_mask = _g_pe_pbl_hw_param_data_m17c0.reg_mask.addr;\
		UINT32 *_data = _g_pe_pbl_hw_param_data_m17c0.reg_data.addr;\
		PE_SHP_HW_M17C0_CHECK_CODE(\
		(sizeof(PE_PBL_HW_PARAM_REG_M17C0_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]pbl tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_M17C0_SET_REG_TABLE(__tbl, __base);\
	}while (0)

#endif

/* set gsc filter */
#define PE_SHP_HW_M17C0_SET_GSC_FLT(__tbl, __base, __size)	\
	do{\
		UINT32 _i;\
		for (_i=0; _i<(__size); _i++)\
		{\
			ret = PE_REG_M17C0_WrAllocatedAddr((__tbl[_i].addr+(__base)), (__tbl[_i].data));\
			PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_M17C0_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_SHP_HW_M17C0_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_SHP_HW_M17C0_CASE_SET_FLT(__ms, __tap, __idx, __ofst, __size)		\
	case PE_SHP_SCL256_CO_NUM_##__tap##T_##__idx:\
		PE_SHP_HW_M17C0_SET_GSC_FLT(scl_p256_##__tap##t_##__ms##_flt_##__idx,(__ofst),(__size));\
		break

#define PE_SHP_HW_M17C0_WR_SCL_COEFF(_wid, _ctrl, _coeff, _id)	\
{\
	char _str_buf[PE_TRACE_STR_SIZE];\
	sprintf(_str_buf, "[wid:%d][idx:%3d]%s", _wid, (_id), #_coeff);\
	PE_SHP_HW_M17C0_DBG_PRINT("set %s\n", _str_buf);\
	PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
	PE_SHP_HW_M17C0_WrSclCoeff((_ctrl),&(_coeff));\
}

/* hex(8bit) to dec : eg. 0xAC -> 1012 */
#define PE_SHP_HW_M17C0_IDX_HEX_TO_DEC(_x)	(GET_BITS((_x),4,4)*100+GET_BITS((_x),0,4))
/* dec to hex(8bit) : eg. 1012 -> 0xAC */
#define PE_SHP_HW_M17C0_IDX_DEC_TO_HEX(_x)	(((((_x)/100)&0xf)<<4)+(((_x)%100)&0xf))

#define PE_SHP_HW_M17C0_CONV_VTAP_TO_VSC_MD(_x)		\
	((_x)==PE_SHP_HW_M17C0_SCL_VSC_MD_V12TAP||(_x)==PE_SHP_HW_M17C0_SCL_VSC_MD_V08TAP)? 0x0:\
	((_x)==PE_SHP_HW_M17C0_SCL_VSC_MD_V02TAP)? 0x3:0x1

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_AFE
extern CVD_PATTERN_DETECTION_T g_CVD_Pattern_Detection_t ;
#endif
extern UINT32 g_pe_inf_m17c0_vr360_mode;
/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
//static int PE_SHP_HW_M17C0_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static PE_SHP_HW_M17C0_RES_FMT PE_SHP_HW_M17C0_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_M17C0_SRS_FMT PE_SHP_HW_M17C0_ConvDispInfoToSrsFmt(LX_PE_INF_DISPLAY_T *disp_inf);
//static PE_SHP_HW_M17C0_SRE_FMT PE_SHP_HW_M17C0_ConvDispInfoToSreFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_M17C0_CTI_FMT PE_SHP_HW_M17C0_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_M17C0_PBL_FMT PE_SHP_HW_M17C0_ConvDispInfoToPblFmt(LX_PE_INF_DISPLAY_T *disp_inf);
#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
static int PE_SHP_HW_M17C0_CreateDataTable(UINT32 index);
#endif /* !PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS */
static int PE_SHP_HW_M17C0_SetResDefault(PE_SHP_HW_M17C0_RES_FMT cur0_res_fmt);
static int PE_SHP_HW_M17C0_SetSrsDefault(PE_SHP_HW_M17C0_SRS_FMT cur0_srs_fmt);
//static int PE_SHP_HW_M17C0_SetSreDefault(PE_SHP_HW_M17C0_SRE_FMT cur0_sre_fmt);
static int PE_SHP_HW_M17C0_SetPblDefault(PE_SHP_HW_M17C0_PBL_FMT cur0_pbl_fmt);
static int PE_SHP_HW_M17C0_SetCtiDefault(PE_SHP_HW_M17C0_CTI_FMT cur0_cti_fmt);

//static UINT32 PE_SHP_HW_M17C0_GetSclDwnLvl(UINT32 i_size, UINT32 o_size);
static int PE_SHP_HW_M17C0_DownloadScl12tMainDb(void);
static int PE_SHP_HW_M17C0_DownloadScl08tMainDb(void);
static int PE_SHP_HW_M17C0_DownloadScl04tMainDb(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#ifdef PE_SHP_HW_M17C0_SR_PWD_TRACE
static UINT8 _g_shp_hw_m17c0_trace=0x1;	//default should be off.
#else
static UINT8 _g_shp_hw_m17c0_trace=0x0;	//default should be off.
#endif
static PE_SHP_HW_M17C0_SETTINGS_T _g_pe_shp_hw_m17c0_info;
#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
static PE_RES_HW_PARAM_DATA_M17C0_T _g_pe_res_hw_param_data_m17c0 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_SRS_HW_PARAM_DATA_M17C0_T _g_pe_srs_hw_param_data_m17c0 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_PBL_HW_PARAM_DATA_M17C0_T _g_pe_pbl_hw_param_data_m17c0 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_CTI_HW_PARAM_DATA_M17C0_T _g_pe_cti_hw_param_data_m17c0 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif

#ifdef PE_SHP_HW_M17C0_CROSS_PAT_DETECT
static UINT32 _g_pre_data_shp=0xff;
static UINT32 _g_pre_shp_bypass=0xff;
#endif


/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
/**
 * init shp
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M17C0_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			memset(&(_g_pe_shp_hw_m17c0_info), -1, sizeof(PE_SHP_HW_M17C0_SETTINGS_T));
			_g_pe_shp_hw_m17c0_info.res0a_fmt = PE_SHP_M17C0_RES_NUM;
			_g_pe_shp_hw_m17c0_info.cti0a_fmt = PE_SHP_M17C0_CTI_NUM;
			_g_pe_shp_hw_m17c0_info.pbl0a_fmt = PE_SHP_M17C0_PBL_NUM;
			_g_pe_shp_hw_m17c0_info.sre0a_fmt = PE_SHP_M17C0_RES_NUM;
			_g_pe_shp_hw_m17c0_info.srs0a_fmt = PE_SHP_M17C0_SRS_NUM;
			PE_SHP_HW_M17C0_DBG_PRINT("init cti.\n");
			#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
			/* res(pe1 shp l,r) : resolution enhance */
			ret = PE_SHP_HW_M17C0_CreateDataTable(PE_SHP_HW_M17C0_TBL_IDX_RES);
			PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M17C0_CreateDataTable() error.\n");
			PE_SHP_HW_M17C0_RES_REG_TABLE(shp_l_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			/* sre shp(srs) */
			ret = PE_SHP_HW_M17C0_CreateDataTable(PE_SHP_HW_M17C0_TBL_IDX_SRS);
			PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M17C0_CreateDataTable() error.\n");
			PE_SHP_HW_M17C0_SRS_REG_TABLE(sre_res_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			/* pbl(pre blur dnr1,2) */
			ret = PE_SHP_HW_M17C0_CreateDataTable(PE_SHP_HW_M17C0_TBL_IDX_PBL);
			PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M17C0_CreateDataTable() error.\n");
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			/* cti */
			ret = PE_SHP_HW_M17C0_CreateDataTable(PE_SHP_HW_M17C0_TBL_IDX_CTI);
			PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M17C0_CreateDataTable() error.\n");
			PE_SHP_HW_M17C0_CTI_REG_TABLE(cti_y_l_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			#else
			#if 0
			/* shp */
			PE_SET_REG_TABLE(SHP_HW_M17C0,shp_l_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_M17C0,shp_l_sqm_init_m17c0,PE_M17C0_REG_WRITE_BASE);
			/* cti(dnr1,2) */
			PE_SET_REG_TABLE(SHP_HW_M17C0,cti_dnr_l_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			/* pbl(pre blur dnr1,2) */
			PE_SET_REG_TABLE(SHP_HW_M17C0,pblur_dnr_l_init_m17c0,PE_M17C0_REG_WRITE_BASE);
			/* sre */
			PE_SET_REG_TABLE(SHP_HW_M17C0,sre_res_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_M17C0,sre_sqm_init_m17c0,PE_M17C0_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_M17C0,sre_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			#endif
			#endif
			PE_GSC_Y_M17C0_RdFL(gsc_g0_y_ctrl);
			PE_GSC_Y_M17C0_Wr01(gsc_g0_y_ctrl,reg_mode_32p_g0,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_Y_M17C0_Wr01(gsc_g0_y_ctrl,reg_min_max_on_g0,0x1);
			PE_GSC_Y_M17C0_Wr01(gsc_g0_y_ctrl,blending_range,0x1);
			PE_GSC_Y_M17C0_Wr01(gsc_g0_y_ctrl,reg_min_max_th_g0,0x21);
			PE_GSC_Y_M17C0_Wr01(gsc_g0_y_ctrl,reg_th,0x6);
			PE_GSC_Y_M17C0_WrFL(gsc_g0_y_ctrl);
			PE_GSC_Y_M17C0_RdFL(gsc_g1_y_ctrl);
			PE_GSC_Y_M17C0_Wr01(gsc_g1_y_ctrl,reg_mode_32p_g1,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_Y_M17C0_WrFL(gsc_g1_y_ctrl);
			/* gsc_c */
			PE_GSC_C_M17C0_RdFL(gsc_g0_c_ctrl);
			PE_GSC_C_M17C0_Wr01(gsc_g0_c_ctrl,reg_mode_32p_g0,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_C_M17C0_Wr01(gsc_g0_c_ctrl,reg_min_max_on_g0,0x1);
			PE_GSC_C_M17C0_Wr01(gsc_g0_c_ctrl,reg_min_max_th_g0,0x1C);
			PE_GSC_C_M17C0_Wr01(gsc_g0_c_ctrl,reg_min_max_on_h_g0,0x1);
			PE_GSC_C_M17C0_WrFL(gsc_g0_c_ctrl);
			PE_GSC_C_M17C0_RdFL(gsc_g1_c_ctrl);
			PE_GSC_C_M17C0_Wr01(gsc_g1_c_ctrl,reg_mode_32p_g1,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_C_M17C0_WrFL(gsc_g1_c_ctrl);
#ifdef PE_SHP_HW_M17C0_CROSS_PAT_DETECT
			_g_pre_data_shp=0xff;
			_g_pre_shp_bypass=0xff;
#endif
			
			return ret;
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * create data table
 *
 * @param   index [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_SHP_HW_M17C0A_TBL_INDX
 * @author
 */
static int PE_SHP_HW_M17C0_CreateDataTable(UINT32 index)
{
	int ret = RET_OK;
	PE_RES_HW_PARAM_DATA_M17C0_T *p_res_m17c0 = &_g_pe_res_hw_param_data_m17c0;
	PE_PBL_HW_PARAM_DATA_M17C0_T *p_pbl_m17c0 = &_g_pe_pbl_hw_param_data_m17c0;
	PE_SRS_HW_PARAM_DATA_M17C0_T *p_srs_m17c0 = &_g_pe_srs_hw_param_data_m17c0;
	PE_CTI_HW_PARAM_DATA_M17C0_T *p_cti_m17c0 = &_g_pe_cti_hw_param_data_m17c0;
	PE_SHP_HW_M17C0_CHECK_CODE(index>=PE_SHP_HW_M17C0_TBL_IDX_NUM, return RET_ERROR, \
		"[%s,%d] index(%d) invalid.\n", __F__, __L__, index);
	if (index == PE_SHP_HW_M17C0_TBL_IDX_RES)
	{
		/* create dflt table */
		if (p_res_m17c0->reg_dflt.addr == NULL)
		{
			p_res_m17c0->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_M17C0_T));
		}
		/* create user table */
		if (p_res_m17c0->reg_user.addr == NULL)
		{
			p_res_m17c0->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_M17C0_T));
			memset((p_res_m17c0->reg_user.addr), 0, sizeof(PE_RES_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* create mask table */
		if (p_res_m17c0->reg_mask.addr == NULL)
		{
			p_res_m17c0->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_M17C0_T));
			memset((p_res_m17c0->reg_mask.addr), -1, sizeof(PE_RES_HW_PARAM_REG_M17C0_T));// 0xffffffff
		}
		/* create data table */
		if (p_res_m17c0->reg_data.addr == NULL)
		{
			p_res_m17c0->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_M17C0_T));
			memset((p_res_m17c0->reg_data.addr), 0, sizeof(PE_RES_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* report result */
		if (p_res_m17c0->reg_dflt.addr != NULL && p_res_m17c0->reg_user.addr != NULL && \
			p_res_m17c0->reg_mask.addr != NULL && p_res_m17c0->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_M17C0_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_M17C0_TBL_IDX_TO_STR(index), \
				(p_res_m17c0->reg_dflt.addr == NULL)? "x":"o", \
				(p_res_m17c0->reg_user.addr == NULL)? "x":"o", \
				(p_res_m17c0->reg_mask.addr == NULL)? "x":"o", \
				(p_res_m17c0->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_M17C0_TBL_IDX_PBL)
	{
		/* create dflt table */
		if (p_pbl_m17c0->reg_dflt.addr == NULL)
		{
			p_pbl_m17c0->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_M17C0_T));
		}
		/* create user table */
		if (p_pbl_m17c0->reg_user.addr == NULL)
		{
			p_pbl_m17c0->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_M17C0_T));
			memset((p_pbl_m17c0->reg_user.addr), 0, sizeof(PE_PBL_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* create mask table */
		if (p_pbl_m17c0->reg_mask.addr == NULL)
		{
			p_pbl_m17c0->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_M17C0_T));
			memset((p_pbl_m17c0->reg_mask.addr), -1, sizeof(PE_PBL_HW_PARAM_REG_M17C0_T));// 0xffffffff
		}
		/* create data table */
		if (p_pbl_m17c0->reg_data.addr == NULL)
		{
			p_pbl_m17c0->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_M17C0_T));
			memset((p_pbl_m17c0->reg_data.addr), 0, sizeof(PE_PBL_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* report result */
		if (p_pbl_m17c0->reg_dflt.addr != NULL && p_pbl_m17c0->reg_user.addr != NULL && \
			p_pbl_m17c0->reg_mask.addr != NULL && p_pbl_m17c0->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_M17C0_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_M17C0_TBL_IDX_TO_STR(index), \
				(p_pbl_m17c0->reg_dflt.addr == NULL)? "x":"o", \
				(p_pbl_m17c0->reg_user.addr == NULL)? "x":"o", \
				(p_pbl_m17c0->reg_mask.addr == NULL)? "x":"o", \
				(p_pbl_m17c0->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_M17C0_TBL_IDX_CTI)
	{
		/* create dflt table */
		if (p_cti_m17c0->reg_dflt.addr == NULL)
		{
			p_cti_m17c0->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_M17C0_T));
		}
		/* create user table */
		if (p_cti_m17c0->reg_user.addr == NULL)
		{
			p_cti_m17c0->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_M17C0_T));
			memset((p_cti_m17c0->reg_user.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* create mask table */
		if (p_cti_m17c0->reg_mask.addr == NULL)
		{
			p_cti_m17c0->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_M17C0_T));
			memset((p_cti_m17c0->reg_mask.addr), -1, sizeof(PE_CTI_HW_PARAM_REG_M17C0_T));// 0xffffffff
		}
		/* create data table */
		if (p_cti_m17c0->reg_data.addr == NULL)
		{
			p_cti_m17c0->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_M17C0_T));
			memset((p_cti_m17c0->reg_data.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* report result */
		if (p_cti_m17c0->reg_dflt.addr != NULL && p_cti_m17c0->reg_user.addr != NULL && \
			p_cti_m17c0->reg_mask.addr != NULL && p_cti_m17c0->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_M17C0_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_M17C0_TBL_IDX_TO_STR(index), \
				(p_cti_m17c0->reg_dflt.addr == NULL)? "x":"o", \
				(p_cti_m17c0->reg_user.addr == NULL)? "x":"o", \
				(p_cti_m17c0->reg_mask.addr == NULL)? "x":"o", \
				(p_cti_m17c0->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	#ifdef PE_SHP_HW_M17C0_SRE_SHP_WR_ONLY_MD
	else if (index == PE_SHP_HW_M17C0_TBL_IDX_SRS)
	{
		/* create dflt table */
		if (p_srs_m17c0->reg_dflt.addr == NULL)
		{
			p_srs_m17c0->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_M17C0_T));
		}
		/* create user table */
		if (p_srs_m17c0->reg_user.addr == NULL)
		{
			p_srs_m17c0->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_M17C0_T));
			memset((p_srs_m17c0->reg_user.addr), 0, sizeof(PE_SRS_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* create mask table */
		if (p_srs_m17c0->reg_mask.addr == NULL)
		{
			p_srs_m17c0->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_M17C0_T));
			memset((p_srs_m17c0->reg_mask.addr), -1, sizeof(PE_SRS_HW_PARAM_REG_M17C0_T));// 0xffffffff
		}
		/* create data table */
		if (p_srs_m17c0->reg_data.addr == NULL)
		{
			p_srs_m17c0->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_M17C0_T));
			memset((p_srs_m17c0->reg_data.addr), 0, sizeof(PE_SRS_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* report srsult */
		if (p_srs_m17c0->reg_dflt.addr != NULL && p_srs_m17c0->reg_user.addr != NULL && \
			p_srs_m17c0->reg_mask.addr != NULL && p_srs_m17c0->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_M17C0_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_M17C0_TBL_IDX_TO_STR(index), \
				(p_srs_m17c0->reg_dflt.addr == NULL)? "x":"o", \
				(p_srs_m17c0->reg_user.addr == NULL)? "x":"o", \
				(p_srs_m17c0->reg_mask.addr == NULL)? "x":"o", \
				(p_srs_m17c0->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	#endif	//#ifdef PE_SHP_HW_M17C0_SRE_SHP_WR_ONLY_MD
	else
	{
		PE_SHP_HW_M17C0_DBG_PRINT("nothing to do\n");	ret = RET_OK;
	}
	return ret;
}

/**
 * set debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M17C0_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_SHP_HW_M17C0_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(SHP)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_shp_hw_m17c0_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(SHP)))? 0x1:0x0;
		}
	}while(0);
	return ret;
}

#ifdef PE_HW_M17C0_BRINGUP
/**
 * default shp setting
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M17C0_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			ret = PE_SHP_HW_M17C0_SetDefault(pstParams);
			PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_M17C0_SetDefault() error.\n", __F__, __L__);
		}
		else if(PE_KDRV_VER_M17C0AX)
		{
			ret = PE_SHP_HW_M17C0A_SetDefault(pstParams);
			PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_M17C0A_SetDefault() error.\n", __F__, __L__);
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
#endif /*PE_HW_M17C0_BRINGUP*/

/**
 * default shp setting(for M17C0AX)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M17C0_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_INF_M17C0_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	LX_PE_INF_DISPLAY_T *disp1_inf = NULL;
	PE_SHP_HW_M17C0_RES_FMT cur0_res_fmt;
	PE_SHP_HW_M17C0_PBL_FMT cur0_pbl_fmt;
	PE_SHP_HW_M17C0_CTI_FMT cur0_cti_fmt;
	PE_SHP_HW_M17C0_SRS_FMT cur0_srs_fmt;
	PE_SHP_HW_M17C0_SETTINGS_T *pInfo=&_g_pe_shp_hw_m17c0_info;
	#ifdef PE_SHP_HW_M17C0_SR_PWD_TRACE
	UINT32 r_data[2];
	#endif
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_M17C0_GetCurInfSettings(&inf_set);
		PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
			"[%s,%d] PE_INF_M17C0_GetCurInfSettings() error.\n", __F__, __L__);
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		disp1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(disp0_inf);
		CHECK_KNULL(disp1_inf);
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
#ifdef USE_SIGNAGE_FHD
			*gpe_vsd_ctrl_block_m17c0 = 0x01210000;
#else
			*gpe_vsd_ctrl_block_m17c0 = 0x01200000;
#endif
			/* res(pe1 shp l,r) */
			cur0_res_fmt = PE_SHP_HW_M17C0_ConvDispInfoToResFmt(disp0_inf);
			PE_SHP_HW_M17C0_DBG_PRINT_RES_FMT_STATE(pInfo->res0a_fmt,cur0_res_fmt);
			if(pInfo->res0a_fmt!=cur0_res_fmt)
			{
				ret = PE_SHP_HW_M17C0_SetResDefault(cur0_res_fmt);
				PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_M17C0_SetResDefault() error.\n", __F__, __L__);
				pInfo->res0a_fmt=cur0_res_fmt;
			}
			/* sre shp(srs) */
			cur0_srs_fmt = PE_SHP_HW_M17C0_ConvDispInfoToSrsFmt(disp0_inf);
			PE_SHP_HW_M17C0_DBG_PRINT_SRS_FMT_STATE(pInfo->srs0a_fmt,cur0_srs_fmt);
			if(pInfo->srs0a_fmt!=cur0_srs_fmt)
			{
				ret = PE_SHP_HW_M17C0_SetSrsDefault(cur0_srs_fmt);
				PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_M17C0_SetSrsDefault() error.\n", __F__, __L__);
				#ifdef PE_SHP_HW_M17C0_CROSS_PAT_DETECT
				//_g_pre_data_shp = _g_pe_srs_hw_param_data_m17c0.reg_dflt.data->shp_derh_ctrl_05.reg_derh_th_gain_edge;
				//PE_SHP_HW_M17C0_DBG_PRINT("defualt pre :%d\n", _g_pre_data_shp );
				#endif
				pInfo->srs0a_fmt=cur0_srs_fmt;
			}
			/* pbl(pre_blur_dnr) */
			cur0_pbl_fmt = PE_SHP_HW_M17C0_ConvDispInfoToPblFmt(disp0_inf);
			PE_SHP_HW_M17C0_DBG_PRINT_PBL_FMT_STATE(pInfo->pbl0a_fmt,cur0_pbl_fmt);
			if(pInfo->pbl0a_fmt!=cur0_pbl_fmt)
			{
				ret = PE_SHP_HW_M17C0_SetPblDefault(cur0_pbl_fmt);
				PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_M17C0_SetPblDefault() error.\n", __F__, __L__);
				pInfo->pbl0a_fmt=cur0_pbl_fmt;
			}
			/*cti(cti_dnr) */
			cur0_cti_fmt = PE_SHP_HW_M17C0_ConvDispInfoToCtiFmt(disp0_inf);
			PE_SHP_HW_M17C0_DBG_PRINT_CTI_FMT_STATE(pInfo->cti0a_fmt,cur0_cti_fmt);
			if(pInfo->cti0a_fmt!=cur0_cti_fmt)
			{
				ret = PE_SHP_HW_M17C0_SetCtiDefault(cur0_cti_fmt);
				PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_M17C0_SetCtiDefault() error.\n", __F__, __L__);
				pInfo->cti0a_fmt=cur0_cti_fmt;
			}
		}
	}while(0);
	return ret;
}
/**
 * default Res setting(for M17C0X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_M17C0_RES_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_M17C0_SetResDefault(PE_SHP_HW_M17C0_RES_FMT cur0_res_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	switch(cur0_res_fmt)
	{
		case PE_SHP_M17C0_RES_SD:
			PE_SHP_HW_M17C0_RES_REG_TABLE(shp_l_sd_default_m17c0,   	PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_RES_HD:
			PE_SHP_HW_M17C0_RES_REG_TABLE(shp_l_hd_default_m17c0,   	PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_RES_UHD:
			PE_SHP_HW_M17C0_RES_REG_TABLE(shp_l_ud_default_m17c0,   	PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_RES_VR_360:
			PE_SHP_HW_M17C0_RES_REG_TABLE(shp_l_vr_360_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_RES_DTV_SD:
			PE_SHP_HW_M17C0_RES_REG_TABLE(shp_l_sd_dtv_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_RES_DTV_HD:
			PE_SHP_HW_M17C0_RES_REG_TABLE(shp_l_hd_dtv_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_res_fmt)
	{
		case PE_SHP_M17C0_RES_SD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,shp_l_sd_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_RES_HD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,shp_l_hd_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_RES_UHD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,shp_l_ud_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_RES_VR_360:
			PE_SET_REG_TABLE(shp_l_vr_360_default_m17c0,   		PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	return ret;
}

static int PE_SHP_HW_M17C0_SetSrsDefault(PE_SHP_HW_M17C0_SRS_FMT cur0_srs_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	switch(cur0_srs_fmt)
	{
		case PE_SHP_M17C0_SRS_SD:
			PE_SHP_HW_M17C0_SRS_REG_TABLE(sre_res_sd_default_m17c0,       PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_SRS_HD:
			PE_SHP_HW_M17C0_SRS_REG_TABLE(sre_res_hd_default_m17c0,       PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_SRS_ATV:
			PE_SHP_HW_M17C0_SRS_REG_TABLE(sre_res_atv_default_m17c0,      PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_SRS_VR_360:
			PE_SHP_HW_M17C0_SRS_REG_TABLE(sre_res_vr_360_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_SRS_DTV_SD:
			PE_SHP_HW_M17C0_SRS_REG_TABLE(sre_res_sd_dtv_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_srs_fmt)
	{
		case PE_SHP_M17C0_SRS_SD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,sre_res_sd_default_m17c0,       PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_SRS_HD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,sre_res_hd_default_m17c0,       PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_SRS_ATV:
			PE_SET_REG_TABLE(sre_res_atv_default_m17c0,      PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_SRS_VR_360:
			PE_SET_REG_TABLE(sre_res_vr_360_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	return ret;
}
#if 0
static int PE_SHP_HW_M17C0_SetSreDefault(PE_SHP_HW_M17C0_SRE_FMT cur0_sre_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_M17C0_BRINGUP
	switch(cur0_sre_fmt)
	{
		case PE_SHP_M17C0_SRE_SD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,sre_sd_default_m17c0,    PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_SRE_HD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,sre_hd_default_m17c0,    PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_M17C0_BRINGUP*/
	return ret;
}
#endif
static int PE_SHP_HW_M17C0_SetPblDefault(PE_SHP_HW_M17C0_PBL_FMT cur0_pbl_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	switch(cur0_pbl_fmt)
	{
		case PE_SHP_M17C0_PBL_ATV_NT:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_atv_nt_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_ATV_PAL:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_atv_pal_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_AV:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_av_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_SECAM:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_secam_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_COMP_SD:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_comp_sd_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_DTV_SD:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_dtv_sd_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_HDMI_SD:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_hdmi_sd_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_PC:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_pc_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_HD:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_hd_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_UD:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_ud_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_VR_360:
			PE_SHP_HW_M17C0_PBL_REG_TABLE(pblur_dnr_l_vr_360_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_pbl_fmt)
	{
		case PE_SHP_M17C0_PBL_SD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,pblur_dnr_l_sd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_PBL_HD:
			PE_SET_REG_TABLE(SHP_HW_M17C0,pblur_dnr_l_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	return ret;
}
static int PE_SHP_HW_M17C0_SetCtiDefault(PE_SHP_HW_M17C0_CTI_FMT cur0_cti_fmt)
{
	int ret = RET_OK;
	switch(cur0_cti_fmt)
	{
		case PE_SHP_M17C0_CTI_SD:
			PE_SHP_HW_M17C0_CTI_REG_TABLE(cti_y_l_sd_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_CTI_HD:
			PE_SHP_HW_M17C0_CTI_REG_TABLE(cti_y_l_hd_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_CTI_VR_360:
			PE_SHP_HW_M17C0_CTI_REG_TABLE(cti_y_l_vr_360_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_CTI_ATV:
			PE_SHP_HW_M17C0_CTI_REG_TABLE(cti_y_l_atv_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_SHP_M17C0_CTI_DTV_480_I:
			PE_SHP_HW_M17C0_CTI_REG_TABLE(cti_y_l_dtv_480i_default_m17c0, PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	return ret;
}

/**
 * get resolution fmt using display info(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M17C0_RES_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_M17C0_RES_FMT PE_SHP_HW_M17C0_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M17C0_RES_FMT res_fmt = PE_SHP_M17C0_RES_NUM;
	PE_SHP_HW_M17C0_DBG_PRINT("ResFmt g_pe_inf_m17c0_vr360_mode: %d.\n", g_pe_inf_m17c0_vr360_mode);
	if(disp_inf->mode.is_vr)
	{
		res_fmt = PE_SHP_M17C0_RES_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					res_fmt = PE_SHP_M17C0_RES_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_M17C0_RES_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_SHP_M17C0_RES_DTV_HD;
				}
				else
				{
					res_fmt = PE_SHP_M17C0_RES_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_M17C0_RES_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_SHP_M17C0_RES_HD;
				}
				else
				{
				 	if(g_pe_inf_m17c0_vr360_mode)
				 	{
						res_fmt = PE_SHP_M17C0_RES_HD;
				 	}
					else
					{
						res_fmt = PE_SHP_M17C0_RES_UHD;
					}
				}
				break;
		}
	}
	return res_fmt;
}
/**
 * get sre shp(srs) fmt using display info(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M17C0_SRS_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_M17C0_SRS_FMT PE_SHP_HW_M17C0_ConvDispInfoToSrsFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M17C0_SRS_FMT srs_fmt = PE_SHP_M17C0_SRS_NUM;
	if(disp_inf->mode.is_vr)
	{
			srs_fmt = PE_SHP_M17C0_SRS_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			{
				srs_fmt = PE_SHP_M17C0_SRS_ATV;
			}
			break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_M17C0_SRS_SD;
				}
				else
				{
					srs_fmt = PE_SHP_M17C0_SRS_HD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_M17C0_SRS_DTV_SD;
				}
				else
				{
					srs_fmt = PE_SHP_M17C0_SRS_HD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_M17C0_SRS_SD;
				}
				else
				{
					srs_fmt = PE_SHP_M17C0_SRS_HD;
				}
				break;
		}
	}
	return srs_fmt;
}
#if 0
/**
 * get resolution fmt using display info(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M17C0_SRE_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_M17C0_SRE_FMT PE_SHP_HW_M17C0_ConvDispInfoToSreFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M17C0_SRE_FMT res_fmt = PE_SHP_M17C0_SRE_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			{
					res_fmt = PE_SHP_M17C0_SRE_ATV;
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_RGBPC:
		default:
			{
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_M17C0_SRE_SD;
				}
				else
				{
					res_fmt = PE_SHP_M17C0_SRE_HD;
				}
			}
			break;
	}
	return res_fmt;
}
#endif
/**
 * get pbl(pre blur dnr) fmt using display info(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M17C0_CTI_FMT
 * @see
 * @author
 */
static PE_SHP_HW_M17C0_PBL_FMT PE_SHP_HW_M17C0_ConvDispInfoToPblFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M17C0_PBL_FMT pbl_fmt = PE_SHP_M17C0_PBL_NUM;
	PE_SHP_HW_M17C0_DBG_PRINT("PblFmt g_pe_inf_m17c0_vr360_mode: %d.\n", g_pe_inf_m17c0_vr360_mode);
	if(disp_inf->mode.is_vr)
	{
			pbl_fmt = PE_SHP_M17C0_PBL_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				if(disp_inf->cstd_type==LX_PE_CSTD_SECAM)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_SECAM;
				}
				else if(disp_inf->cstd_type==LX_PE_CSTD_PAL)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_ATV_PAL;
				}
				else
				{
					pbl_fmt = PE_SHP_M17C0_PBL_ATV_NT;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				if(disp_inf->cstd_type==LX_PE_CSTD_SECAM)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_SECAM;
				}
				else
				{
					pbl_fmt = PE_SHP_M17C0_PBL_AV;
				}
				break;
			case LX_PE_SRC_RGBPC:
				{
					pbl_fmt = PE_SHP_M17C0_PBL_PC;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->dtv_type==LX_PE_DTV_HDDPLAY)
				{
					if(disp_inf->hdd_type==LX_PE_HDD_SRC_ATV60)
					{
						pbl_fmt = PE_SHP_M17C0_PBL_ATV_NT;
					}
					else if(disp_inf->hdd_type==LX_PE_HDD_SRC_ATV50)
					{
						pbl_fmt = PE_SHP_M17C0_PBL_ATV_PAL;
					}
					else if(disp_inf->hdd_type==LX_PE_HDD_SRC_AV60 || \
						disp_inf->hdd_type==LX_PE_HDD_SRC_AV50 || \
						disp_inf->hdd_type==LX_PE_HDD_SRC_SCARTRGB)
					{
						pbl_fmt = PE_SHP_M17C0_PBL_AV;
					}
					else	//LX_PE_HDD_SRC_DTV
					{
						if(disp_inf->fmt_type==LX_PE_FMT_SD)
						{
							pbl_fmt = PE_SHP_M17C0_PBL_DTV_SD;
						}
						else if(disp_inf->fmt_type==LX_PE_FMT_HD)
						{
							pbl_fmt = PE_SHP_M17C0_PBL_HD;
						}
						else
						{
						 	if(g_pe_inf_m17c0_vr360_mode)
						 	{
								pbl_fmt = PE_SHP_M17C0_PBL_HD;
						 	}
							else
							{
								pbl_fmt = PE_SHP_M17C0_PBL_UD;
							}
						}
					}
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_HD;
				}
				else
				{
					if(g_pe_inf_m17c0_vr360_mode)
				 	{
						pbl_fmt = PE_SHP_M17C0_PBL_HD;
				 	}
					else
					{
						pbl_fmt = PE_SHP_M17C0_PBL_UD;
					}
				}
				break;
			case LX_PE_SRC_COMP:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_COMP_SD;
				}
				else
				{
					pbl_fmt = PE_SHP_M17C0_PBL_HD;
				}
				break;
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->hdmi_type==LX_PE_HDMI_PC)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_PC;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_HDMI_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					pbl_fmt = PE_SHP_M17C0_PBL_HD;
				}
				else
				{
					if(g_pe_inf_m17c0_vr360_mode)
				 	{
						pbl_fmt = PE_SHP_M17C0_PBL_HD;
				 	}
					else
					{
						pbl_fmt = PE_SHP_M17C0_PBL_UD;
					}
				}
				break;
		}
	}
	return pbl_fmt;
}
/**
 * get cti(dnr) fmt using display info(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M17C0_CTI_FMT
 * @see
 * @author
 */
static PE_SHP_HW_M17C0_CTI_FMT PE_SHP_HW_M17C0_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M17C0_CTI_FMT cti_fmt = PE_SHP_M17C0_CTI_NUM;
	if(disp_inf->mode.is_vr)
	{
			cti_fmt = PE_SHP_M17C0_CTI_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				cti_fmt = PE_SHP_M17C0_CTI_ATV;
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
			case LX_PE_SRC_RGBPC:
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if (disp_inf->fmt_type == LX_PE_FMT_SD)
				{
					if ((disp_inf->src_type == LX_PE_SRC_DTV) &&
						(disp_inf->scan_type == LX_PE_SCAN_INTERLACE) &&
						(disp_inf->cstd_type == LX_PE_CSTD_NTSC))
					{
						cti_fmt = PE_SHP_M17C0_CTI_DTV_480_I;
					}
					else
					{
						cti_fmt = PE_SHP_M17C0_CTI_SD;
					}
				}
				else
				{
					cti_fmt = PE_SHP_M17C0_CTI_HD;
				}
				break;
		}
	}
	return cti_fmt;
}

#if 0
/**
 * get scl down level
 * - under 19% (1024 normalized : under 204) : 1/8
 * - under 39% (1024 normalized : under 408) : 1/4
 * - under 69% (1024 normalized : under 717) : 1/2
 * - over  70% (1024 normalized : over  716) : normal
 *
 * @param   i_size [in] UINT32
 * @param   o_size [in] UINT32
 * @return  dwn_lvl UINT32
 * @see
 * @author
 */
static UINT32 PE_SHP_HW_M17C0_GetSclDwnLvl(UINT32 i_size, UINT32 o_size)
{
	UINT32 o_size_by_10bit;
	UINT32 dwn_lvl = PE_SHP_HW_M17C0_SCL_DWN_LVL_NORM;
	do {
		if (!i_size || i_size>5000)		break;
		if (!o_size || o_size>5000)		break;
		o_size_by_10bit = (o_size<<10);
		if (o_size_by_10bit < (i_size*204))	{dwn_lvl=PE_SHP_HW_M17C0_SCL_DWN_LVL_OCTA;break;}
		if (o_size_by_10bit < (i_size*408))	{dwn_lvl=PE_SHP_HW_M17C0_SCL_DWN_LVL_QUAD;break;}
		if (o_size_by_10bit < (i_size*717))	{dwn_lvl=PE_SHP_HW_M17C0_SCL_DWN_LVL_HALF;break;}
	} while(0);
	return dwn_lvl;
}
#endif

/**
 * read default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_SHP_HW_M17C0_RdDefault(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 param_size=0, table_size=0, is_valid=0;
	UINT32 rd_cnt=0;
	PE_REG_PARAM_T param;
	PE_SHP_HW_M17C0_SETTINGS_T *pInfo=&_g_pe_shp_hw_m17c0_info;

#define PE_SHP_M17C0_NO_PRINT			0
#define PE_SHP_M17C0_RD_N_HEX_PRINT	1
#define PE_SHP_M17C0_HEX_PRINT_ONLY	2
#define PE_SHP_M17C0_PRINT_START		"START_OF_PRINT"
#define PE_SHP_M17C0_PRINT_END		"END_OF_PRINT"
#define PE_SHP_M17C0_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_SHP_M17C0_PRINT_RESRV		"RESERVED"
#define PE_SHP_M17C0_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):sprintf(_buf, "   [0x%02X] %s\n", (_item), #_item);_action;break
#define PE_SHP_M17C0_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):sprintf(_buf, fmt, ##args);_action;break
#define PE_SHP_M17C0_DFLT_SPRINT(_action, _buf, fmt, args...)		\
	default:sprintf(_buf, fmt, ##args);_action;break

	do{
		if (PE_KDRV_VER_M17CX)
		{
			UINT32 *p_res_dflt = _g_pe_res_hw_param_data_m17c0.reg_dflt.addr;
			UINT32 *p_res_user = _g_pe_res_hw_param_data_m17c0.reg_user.addr;
			UINT32 *p_res_mask = _g_pe_res_hw_param_data_m17c0.reg_mask.addr;
			UINT32 *p_res_data = _g_pe_res_hw_param_data_m17c0.reg_data.addr;
			UINT32 *p_pbl_dflt = _g_pe_pbl_hw_param_data_m17c0.reg_dflt.addr;
			UINT32 *p_pbl_user = _g_pe_pbl_hw_param_data_m17c0.reg_user.addr;
			UINT32 *p_pbl_mask = _g_pe_pbl_hw_param_data_m17c0.reg_mask.addr;
			UINT32 *p_pbl_data = _g_pe_pbl_hw_param_data_m17c0.reg_data.addr;
			UINT32 *p_cti_dflt = _g_pe_cti_hw_param_data_m17c0.reg_dflt.addr;
			UINT32 *p_cti_user = _g_pe_cti_hw_param_data_m17c0.reg_user.addr;
			UINT32 *p_cti_mask = _g_pe_cti_hw_param_data_m17c0.reg_mask.addr;
			UINT32 *p_cti_data = _g_pe_cti_hw_param_data_m17c0.reg_data.addr;
			#ifdef PE_SHP_HW_M17C0_SRE_SHP_WR_ONLY_MD
			UINT32 *p_srs_dflt = _g_pe_srs_hw_param_data_m17c0.reg_dflt.addr;
			UINT32 *p_srs_user = _g_pe_srs_hw_param_data_m17c0.reg_user.addr;
			UINT32 *p_srs_mask = _g_pe_srs_hw_param_data_m17c0.reg_mask.addr;
			UINT32 *p_srs_data = _g_pe_srs_hw_param_data_m17c0.reg_data.addr;
			#endif

			CHECK_KNULL(pstParams);
			CHECK_KNULL(pstParams->data);
			CHECK_KNULL(p_res_dflt);
			CHECK_KNULL(p_res_user);
			CHECK_KNULL(p_res_mask);
			CHECK_KNULL(p_res_data);
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]>=PE_SHP_HW_M17C0_RD_MENU_MAX)
			{
				sprintf(buffer, PE_SHP_M17C0_PRINT_EXIT);
				rd_cnt=0;
			}
			else if (pstParams->data[0]==PE_SHP_HW_M17C0_RD_MENU_DISP)
			{
				switch (rd_cnt)
				{
					PE_SHP_M17C0_CASE_SPRINT( 0, rd_cnt++, buffer, PE_SHP_M17C0_PRINT_START);
					PE_SHP_M17C0_CASE_SPRINT( 1, rd_cnt++, buffer, "   ** current default **\n");
					PE_SHP_M17C0_CASE_SPRINT( 2, rd_cnt++, buffer, \
						"   res0a_fmt : %s\n", PE_SHP_HW_M17C0_RES_FMT_TO_STR(pInfo->res0a_fmt));
					PE_SHP_M17C0_CASE_SPRINT( 3, rd_cnt++, buffer, \
						"   cti0a_fmt : %s\n", PE_SHP_HW_M17C0_CTI_FMT_TO_STR(pInfo->cti0a_fmt));
					PE_SHP_M17C0_CASE_SPRINT( 4, rd_cnt++, buffer, \
						"   pbl0a_fmt : %s\n", PE_SHP_HW_M17C0_PBL_FMT_TO_STR(pInfo->pbl0a_fmt));
					PE_SHP_M17C0_CASE_SPRINT( 5, rd_cnt++, buffer, \
						"   sre0a_fmt : %s\n", PE_SHP_HW_M17C0_SRE_FMT_TO_STR(pInfo->sre0a_fmt));
					PE_SHP_M17C0_CASE_SPRINT( 6, rd_cnt++, buffer, \
						"   srs0a_fmt : %s\n", PE_SHP_HW_M17C0_SRS_FMT_TO_STR(pInfo->srs0a_fmt));
					PE_SHP_M17C0_CASE_SPRINT( 7, rd_cnt++, buffer, PE_SHP_M17C0_PRINT_RESRV);
					PE_SHP_M17C0_CASE_SPRINT( 8, rd_cnt++, buffer, PE_SHP_M17C0_PRINT_RESRV);
					PE_SHP_M17C0_CASE_SPRINT( 9, rd_cnt++, buffer, PE_SHP_M17C0_PRINT_RESRV);
					PE_SHP_M17C0_CASE_SPRINT(10, rd_cnt++, buffer, "   *********************\n");
					PE_SHP_M17C0_CASE_PRMENU(11, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_RES1_DISP);
					PE_SHP_M17C0_CASE_PRMENU(12, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_RES2_DISP);
					PE_SHP_M17C0_CASE_PRMENU(13, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_RES1_DFLT);
					PE_SHP_M17C0_CASE_PRMENU(14, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_RES1_USER);
					PE_SHP_M17C0_CASE_PRMENU(15, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_RES1_MASK);
					PE_SHP_M17C0_CASE_PRMENU(16, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_RES1_DATA);
					PE_SHP_M17C0_CASE_PRMENU(17, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_CTI1_DISP);
					PE_SHP_M17C0_CASE_PRMENU(18, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_CTI2_DISP);
					PE_SHP_M17C0_CASE_PRMENU(19, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_CTI1_DFLT);
					PE_SHP_M17C0_CASE_PRMENU(20, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_CTI1_USER);
					PE_SHP_M17C0_CASE_PRMENU(21, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_CTI1_MASK);
					PE_SHP_M17C0_CASE_PRMENU(22, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_CTI1_DATA);
					PE_SHP_M17C0_CASE_PRMENU(23, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_PBL1_DISP);
					PE_SHP_M17C0_CASE_PRMENU(24, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_PBL2_DISP);
					PE_SHP_M17C0_CASE_PRMENU(25, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_PBL1_DFLT);
					PE_SHP_M17C0_CASE_PRMENU(26, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_PBL1_USER);
					PE_SHP_M17C0_CASE_PRMENU(27, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_PBL1_MASK);
					PE_SHP_M17C0_CASE_PRMENU(28, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_PBL1_DATA);
					#ifdef PE_SHP_HW_M17C0_SRE_SHP_WR_ONLY_MD
					PE_SHP_M17C0_CASE_SPRINT(29, rd_cnt++, buffer, PE_SHP_M17C0_PRINT_RESRV);
					PE_SHP_M17C0_CASE_SPRINT(30, rd_cnt++, buffer, PE_SHP_M17C0_PRINT_RESRV);
					PE_SHP_M17C0_CASE_PRMENU(31, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_SRS1_DISP);
					PE_SHP_M17C0_CASE_PRMENU(32, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_SRS1_DFLT);
					PE_SHP_M17C0_CASE_PRMENU(33, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_SRS1_USER);
					PE_SHP_M17C0_CASE_PRMENU(34, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_SRS1_MASK);
					PE_SHP_M17C0_CASE_PRMENU(35, rd_cnt++, buffer, PE_SHP_HW_M17C0_RD_SRS1_DATA);
					#endif	//#ifdef PE_SHP_HW_M17C0_SRE_SHP_WR_ONLY_MD
					PE_SHP_M17C0_DFLT_SPRINT(rd_cnt=0, buffer, PE_SHP_M17C0_PRINT_END);
				}
			}
			else
			{
				is_valid = PE_SHP_M17C0_NO_PRINT;
				switch (pstParams->data[0])
				{
					case PE_SHP_HW_M17C0_RD_RES1_DISP:
					case PE_SHP_HW_M17C0_RD_RES2_DISP:
						table_size = sizeof(shp_l_hd_default_m17c0);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m17c0[rd_cnt].addr;
							is_valid = PE_SHP_M17C0_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_M17C0_RD_RES1_DFLT:
						table_size = sizeof(PE_RES_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_res_dflt[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_RES1_USER:
						table_size = sizeof(PE_RES_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_res_user[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_RES1_MASK:
						table_size = sizeof(PE_RES_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_res_mask[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_RES1_DATA:
						table_size = sizeof(PE_RES_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_res_data[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					#if 1
					case PE_SHP_HW_M17C0_RD_CTI1_DISP:
					case PE_SHP_HW_M17C0_RD_CTI2_DISP:
						table_size = sizeof(cti_y_l_hd_default_m17c0);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m17c0[rd_cnt].addr;
							is_valid = PE_SHP_M17C0_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_M17C0_RD_CTI1_DFLT:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_cti_dflt[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_CTI1_USER:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_cti_user[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_CTI1_MASK:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_cti_mask[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_CTI1_DATA:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_cti_data[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					#endif
					case PE_SHP_HW_M17C0_RD_PBL1_DISP:
					case PE_SHP_HW_M17C0_RD_PBL2_DISP:
						table_size = sizeof(pblur_dnr_l_hd_default_m17c0);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_m17c0[rd_cnt].addr;
							is_valid = PE_SHP_M17C0_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_M17C0_RD_PBL1_DFLT:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_pbl_dflt[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_PBL1_USER:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_pbl_user[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_PBL1_MASK:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_pbl_mask[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_PBL1_DATA:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_m17c0[rd_cnt].addr;
							param.data = p_pbl_data[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_SRS1_DISP:
						table_size = sizeof(sre_res_hd_default_m17c0);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = sre_res_hd_default_m17c0[rd_cnt].addr;
							is_valid = PE_SHP_M17C0_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_M17C0_RD_SRS1_DFLT:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_res_hd_default_m17c0[rd_cnt].addr;
							param.data = p_srs_dflt[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_SRS1_USER:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_res_hd_default_m17c0[rd_cnt].addr;
							param.data = p_srs_user[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_SRS1_MASK:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_res_hd_default_m17c0[rd_cnt].addr;
							param.data = p_srs_mask[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M17C0_RD_SRS1_DATA:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_res_hd_default_m17c0[rd_cnt].addr;
							param.data = p_srs_data[rd_cnt];
							is_valid = PE_SHP_M17C0_HEX_PRINT_ONLY;
						}
						break;
					default:
						break;
				}
				if (is_valid == PE_SHP_M17C0_RD_N_HEX_PRINT)
				{
					param.data = PE_REG_M17_RD(param.addr);
					sprintf(buffer, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else if (is_valid == PE_SHP_M17C0_HEX_PRINT_ONLY)
				{
					sprintf(buffer, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else
				{
					sprintf(buffer, PE_SHP_M17C0_PRINT_END);
					rd_cnt = 0;
				}
			}
			memcpy(pstParams->data, buffer, sizeof(char)*PE_TRACE_STR_SIZE);
		}
	}while (0);
	return ret;
}

/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_CMN_T *pp=(LX_PE_SHP_RE5_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_main_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_main_post\n"\
			"shp_ui_main_post     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_post     [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_ti_ui_main_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ti_ui_main_post\n"\
			"shp_ti_ui_main_post  [00]0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2]);
			pd = pp->shp_cti_ui_main_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_cti_ui_main_post\n"\
			"shp_cti_ui_main_post [00]0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id,	pd[0],  pd[1],  pd[2],  pd[3]);

			if (PE_CHECK_WIN0(pp->win_id))
			{
#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_RES_WR01(shp_contrast_ctrl_02,	reg_lc_lap_weight,		GET_BITS(pp->shp_ui_main_post[0],0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_mp_ctrl_01,		reg_mp_im_os_gain,		GET_BITS(pp->shp_ui_main_post[1],0,7),\
																reg_mp_im_us_gain,		GET_BITS(pp->shp_ui_main_post[2],0,7));
				PE_SHP_HW_M17C0_RES_WR06(shp_mp_ctrl_03,		reg_mp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_post[3],0,4),\
																reg_mp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_post[4],0,4),\
																reg_mp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_post[5],0,4),\
																reg_mp_lap_gain_v_7,	GET_BITS(pp->shp_ui_main_post[6],0,4),\
																reg_mp_lap_gain_v_5,	GET_BITS(pp->shp_ui_main_post[7],0,4),\
																reg_mp_lap_gain_v_3,	GET_BITS(pp->shp_ui_main_post[8],0,4));
				PE_SHP_HW_M17C0_RES_WR02(shp_sp_ctrl_01,		reg_sp_im_os_gain,		GET_BITS(pp->shp_ui_main_post[9],0,8),\
																reg_sp_im_us_gain,		GET_BITS(pp->shp_ui_main_post[10],0,8));
				PE_SHP_HW_M17C0_RES_WR03(shp_sp_ctrl_03,		reg_sp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_post[11],0,4),\
																reg_sp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_post[12],0,4),\
																reg_sp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_post[13],0,4));

				PE_SHP_HW_M17C0_RES_WR03(shp_sti_ctrl_00,		reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_post[0],0,8),\
																reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_post[1],0,8),\
																reg_sti_texture_gain,   GET_BITS(pp->shp_ti_ui_main_post[2],0,8));
#ifdef PE_SHP_HW_M17C0_CTI_CMN_CHANGE
				PE_SHP_HW_M17C0_CTI_DNR0_WR01(cti_ctrl_0,		cti_gain,				GET_BITS(pp->shp_cti_ui_main_post[0],0,8));
				PE_SHP_HW_M17C0_CTI_DNR0_WR01(reg_cti_ctrl_2,	reg_ycm_band_sel,		GET_BITS(pp->shp_cti_ui_main_post[1],0,3));
				PE_SHP_HW_M17C0_CTI_SHP_WR01(shp_cti_ctrl_00,	reg_cti_gain,			GET_BITS(pp->shp_cti_ui_main_post[2],0,8));
				PE_SHP_HW_M17C0_CTI_SHP_WR01(shp_cti_ctrl_02,	reg_cti_ycm_band_sel,	GET_BITS(pp->shp_cti_ui_main_post[3],0,3));
#endif
#else
				PE_SHP_M17C0_QWr01(shp_contrast_ctrl_02,		reg_lc_lap_weight,		GET_BITS(pp->shp_ui_main_post[0],0,8));
				PE_SHP_M17C0_QWr02(shp_mp_ctrl_01,				reg_mp_im_os_gain,		GET_BITS(pp->shp_ui_main_post[1],0,7),\
																reg_mp_im_us_gain,		GET_BITS(pp->shp_ui_main_post[2],0,7));
				PE_SHP_M17C0_QWr06(shp_mp_ctrl_03,				reg_mp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_post[3],0,4),\
																reg_mp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_post[4],0,4),\
																reg_mp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_post[5],0,4),\
																reg_mp_lap_gain_v_7,	GET_BITS(pp->shp_ui_main_post[6],0,4),\
																reg_mp_lap_gain_v_5,	GET_BITS(pp->shp_ui_main_post[7],0,4),\
																reg_mp_lap_gain_v_3,	GET_BITS(pp->shp_ui_main_post[8],0,4));
				PE_SHP_M17C0_QWr02(shp_sp_ctrl_01,				reg_sp_im_os_gain,		GET_BITS(pp->shp_ui_main_post[9],0,8),\
																reg_sp_im_us_gain,		GET_BITS(pp->shp_ui_main_post[10],0,8));
				PE_SHP_M17C0_QWr03(shp_sp_ctrl_03,				reg_sp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_post[11],0,4),\
																reg_sp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_post[12],0,4),\
																reg_sp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_post[13],0,4));
				
				PE_SHP_M17C0_QWr03(shp_sti_ctrl_00, 			reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_post[0],0,8),\
																reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_post[1],0,8),\
																reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_post[2],0,8));
				PE_SHP_HW_M17C0_CTI_DNR0_WR01(cti_ctrl_0,		cti_gain,				GET_BITS(pp->shp_cti_ui_main_post[0],0,8));
#endif
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_CMN_T *pp=(LX_PE_SHP_RE5_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_M17C0_QRd01(shp_contrast_ctrl_02,		reg_lc_lap_weight,		pp->shp_ui_main_post[0]);
				PE_SHP_M17C0_QRd02(shp_mp_ctrl_01,				reg_mp_im_os_gain,		pp->shp_ui_main_post[1],\
																reg_mp_im_us_gain,		pp->shp_ui_main_post[2]);
				PE_SHP_M17C0_QRd06(shp_mp_ctrl_03,				reg_mp_lap_gain_h_7,	pp->shp_ui_main_post[3],\
																reg_mp_lap_gain_h_5,	pp->shp_ui_main_post[4],\
																reg_mp_lap_gain_h_3,	pp->shp_ui_main_post[5],\
																reg_mp_lap_gain_v_7,	pp->shp_ui_main_post[6],\
																reg_mp_lap_gain_v_5,	pp->shp_ui_main_post[7],\
																reg_mp_lap_gain_v_3,	pp->shp_ui_main_post[8]);
				PE_SHP_M17C0_QRd02(shp_sp_ctrl_01,				reg_sp_im_os_gain,		pp->shp_ui_main_post[9],\
																reg_sp_im_us_gain,		pp->shp_ui_main_post[10]);
				PE_SHP_M17C0_QRd03(shp_sp_ctrl_03,				reg_sp_lap_gain_h_7,	pp->shp_ui_main_post[11],\
																reg_sp_lap_gain_h_5,	pp->shp_ui_main_post[12],\
																reg_sp_lap_gain_h_3,	pp->shp_ui_main_post[13]);
				
				PE_SHP_M17C0_QRd03(shp_sti_ctrl_00,				reg_sti_master_gain,	pp->shp_ti_ui_main_post[0],\
																reg_sti_edge_gain,		pp->shp_ti_ui_main_post[1],\
																reg_sti_texture_gain,	pp->shp_ti_ui_main_post[2]);
				#ifdef PE_SHP_HW_M17C0_CTI_CMN_CHANGE
				PE_DNR0_M17C0_QRd01(cti_ctrl_0,					cti_gain,				pp->shp_cti_ui_main_post[0]);
				PE_DNR0_M17C0_QRd01(reg_cti_ctrl_2,					reg_ycm_band_sel,		pp->shp_cti_ui_main_post[1]);
				PE_SHP_M17C0_QRd01(shp_cti_ctrl_00,				reg_cti_gain,			pp->shp_cti_ui_main_post[2]);
				PE_SHP_M17C0_QRd01(shp_cti_ctrl_02,				reg_cti_ycm_band_sel,	pp->shp_cti_ui_main_post[3]);
				#endif
				pd = pp->shp_ui_main_post;
				PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_ui_main_post\n"\
				"shp_ui_main_post	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_post	  [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],	pd[1],	pd[2],	pd[3],	pd[4],	pd[5],	pd[6],	pd[7],	pd[8],	pd[9], \
				pd[10], pd[11], pd[12], pd[13]);
				pd = pp->shp_ti_ui_main_post;
				PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ti_ui_main_post\n"\
				"shp_ti_ui_main_post  [00]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],	pd[1],	pd[2]);
				pd = pp->shp_cti_ui_main_post;
				PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_cti_ui_main_post\n"\
				"shp_cti_ui_main_post [00]0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id,	pd[0],  pd[1],  pd[2],  pd[3]);
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set resolution horizontal control
 * - use input struct LX_PE_SHP_RE2_HOR_T for M17C0X
 * - use input struct LX_PE_SHP_RE1_HOR_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			UINT8 *pd;
			LX_PE_SHP_RE4_HOR_T *pp=(LX_PE_SHP_RE4_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_h_main_post\n"\
			"shp_ui_h_main_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_RES_WR01(shp_derh_ctrl_05,reg_derh_csft_gain,				GET_BITS(pp->shp_ui_h_main_post[0],0,6));
				PE_SHP_HW_M17C0_RES_WR03(shp_derh_ctrl_06,reg_derh_bflt_tap_size,			GET_BITS(pp->shp_ui_h_main_post[1],0,3),\
														reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main_post[2],0,6),\
														reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main_post[3],0,6));
				PE_SHP_HW_M17C0_RES_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_post[4],0,8));
				PE_SHP_HW_M17C0_RES_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_post[5],0,8));
				PE_SHP_HW_M17C0_RES_WR01(shp_pti_ctrl_01, reg_ptih_master_gain,			GET_BITS(pp->shp_ui_h_main_post[6],0,8));
				#else
				PE_SHP_M17C0_QWr01(shp_derh_ctrl_05,	reg_derh_csft_gain,				GET_BITS(pp->shp_ui_h_main_post[0],0,6));
				PE_SHP_M17C0_QWr03(shp_derh_ctrl_06,	reg_derh_bflt_tap_size,			GET_BITS(pp->shp_ui_h_main_post[1],0,3),\
													reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main_post[2],0,6),\
													reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main_post[3],0,6));
				PE_SHP_M17C0_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_post[4],0,8));
				PE_SHP_M17C0_QWr01(shp_sp_ctrl_01,	reg_sp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_post[5],0,8));
				PE_SHP_M17C0_QWr01(shp_pti_ctrl_01,	reg_ptih_master_gain,			GET_BITS(pp->shp_ui_h_main_post[6],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get resolution horizontal control
 * - use input struct LX_PE_SHP_RE2_HOR_T for M17C0X
 * - use input struct LX_PE_SHP_RE1_HOR_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_SHP_RE4_HOR_T *pp=(LX_PE_SHP_RE4_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			PE_SHP_M17C0_QRd01(shp_derh_ctrl_05,	reg_derh_csft_gain, 			pp->shp_ui_h_main_post[0]);
			PE_SHP_M17C0_QRd03(shp_derh_ctrl_06,	reg_derh_bflt_tap_size, 		pp->shp_ui_h_main_post[1],\
												reg_derh_edge_filter_gain_w,	pp->shp_ui_h_main_post[2],\
												reg_derh_edge_filter_gain_b,	pp->shp_ui_h_main_post[3]);
			PE_SHP_M17C0_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,				pp->shp_ui_h_main_post[4]);
			PE_SHP_M17C0_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,				pp->shp_ui_h_main_post[5]);
			PE_SHP_M17C0_QRd01(shp_pti_ctrl_01,	reg_ptih_master_gain,			pp->shp_ui_h_main_post[6]);
			
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for M17C0X
 * - use input struct LX_PE_SHP_RE1_VER_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_SHP_RE4_VER_T *pp=(LX_PE_SHP_RE4_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_ui_v_main_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_v_main_post\n"\
			"shp_ui_v_main_post[00]0x%02X,0x%02X\n",\
			pp->win_id,	pd[0],  pd[1]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_RES_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_post[0],0,8));
				PE_SHP_HW_M17C0_RES_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_post[1],0,8));
				#else
				PE_SHP_M17C0_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_v,			GET_BITS(pp->shp_ui_v_main_post[0],0,8));
				PE_SHP_M17C0_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,		GET_BITS(pp->shp_ui_v_main_post[1],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for M17C0X
 * - use input struct LX_PE_SHP_RE1_VER_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_SHP_RE4_VER_T *pp=(LX_PE_SHP_RE4_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			UINT8 *pd = pp->shp_ui_v_main_post;
			
			PE_SHP_M17C0_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v,			pp->shp_ui_v_main_post[0]);
			PE_SHP_M17C0_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,		pp->shp_ui_v_main_post[1]);
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_ui_v_main_post\n"\
			"shp_ui_v_main_post[00]0x%02X,0x%02X\n",\
			pp->win_id,	pd[0],  pd[1]);
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for M17C0X
 * - use input struct LX_PE_SHP_RE1_MISC_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{ 
			UINT8 *pd;
			LX_PE_SHP_RE6_MISC_T *pp=(LX_PE_SHP_RE6_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_cmn_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : resolution misc ctrl\n"\
			"shp_cmn_post     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_post     [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_post     [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29]);
			pd = pp->shp_map_cmn_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_post [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_post [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_post [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_post [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48]);
			pd = pp->shp_balance_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_balance_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [50]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],   pd[4],   pd[5],   pd[6],   pd[7],   pd[8],   pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48],  pd[49], \
				pd[50], pd[51], pd[52]);
			pd = pp->shp_ti_cmn_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_post  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_post  [10]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11]);
			pd = pp->shp_simple_snr_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_simple_snr_post [00]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2]);
			pd = pp->shp_cti_cmn_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_cti_cmn_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7]);
			
			pd = pp->shp_motion_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :	resolution misc ctrl\n"\
			"shp_motion_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],	pd[1],	pd[2],	pd[3],	pd[4],	pd[5],	pd[6],	pd[7],	pd[8]);
			pd = pp->shp_chroma_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_chroma_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_RES_WR01(shp_derh_ctrl_06,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_post[0],0,1));
				PE_SHP_HW_M17C0_RES_WR04(shp_dp_ctrl_05,		reg_der_x0,					GET_BITS(pp->shp_cmn_post[1],0,8),\
															reg_der_x1,		 			GET_BITS(pp->shp_cmn_post[2],0,8),\
															reg_der_y0,					GET_BITS(pp->shp_cmn_post[5],0,8),\
															reg_der_y1,		 			GET_BITS(pp->shp_cmn_post[6],0,8));
				PE_SHP_HW_M17C0_RES_WR04(shp_dp_ctrl_06,		reg_der_x2,					GET_BITS(pp->shp_cmn_post[3],0,8),\
															reg_der_x3,		 			GET_BITS(pp->shp_cmn_post[4],0,8),\
															reg_der_y2,					GET_BITS(pp->shp_cmn_post[7],0,8),\
															reg_der_y3,		 			GET_BITS(pp->shp_cmn_post[8],0,8));
				PE_SHP_HW_M17C0_RES_WR01(shp_mp_ctrl_00,		reg_mp_shp_en,				GET_BITS(pp->shp_cmn_post[9],0,1));
				PE_SHP_HW_M17C0_RES_WR01(shp_sp_ctrl_00,		reg_sp_shp_en,				GET_BITS(pp->shp_cmn_post[10],0,1));
				PE_SHP_HW_M17C0_RES_WR01(shp_mp_ctrl_02,		reg_mp_lap_weight,			GET_BITS(pp->shp_cmn_post[11],0,8));
				PE_SHP_HW_M17C0_RES_WR01(shp_sp_ctrl_02,		reg_sp_lap_weight,			GET_BITS(pp->shp_cmn_post[12],0,8));\
				PE_SHP_HW_M17C0_RES_WR03(shp_derh_ctrl_07,	reg_derh_flat_filter_en,	GET_BITS(pp->shp_cmn_post[13],0,1),\
															reg_derh_flat_filter_type,	GET_BITS(pp->shp_cmn_post[14],0,1),\
															reg_derh_flat_filter_gain,	GET_BITS(pp->shp_cmn_post[15],0,6));
				PE_SHP_HW_M17C0_RES_WR06(shp_dj_ctrl_00,		reg_dj_edf_en,				GET_BITS(pp->shp_cmn_post[16],0,1),\
															reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_cmn_post[17],0,1),\
															reg_dj_center_blur_mode,	GET_BITS(pp->shp_cmn_post[20],0,2),\
															reg_dj_count_diff_th,		GET_BITS(pp->shp_cmn_post[21],0,5),\
															reg_dj_n_avg_mode,		 	GET_BITS(pp->shp_cmn_post[22],0,1),\
														reg_dj_line_variation_diff_th,	GET_BITS(pp->shp_cmn_post[23],0,8));
				PE_SHP_HW_M17C0_RES_WR04(shp_dj_ctrl_03,		reg_dj_edge_min,			GET_BITS(pp->shp_cmn_post[18],0,8),\
															reg_dj_edge_mul,			GET_BITS(pp->shp_cmn_post[19],0,8),\
															reg_dj_g1_protect_min,		GET_BITS(pp->shp_cmn_post[28],0,8),\
															reg_dj_g1_mul,				GET_BITS(pp->shp_cmn_post[29],0,7));
				
				PE_SHP_HW_M17C0_RES_WR02(shp_dj_ctrl_01,		reg_dj_level_th,			GET_BITS(pp->shp_cmn_post[24],0,8),\
															reg_dj_n_avg_gain,			GET_BITS(pp->shp_cmn_post[25],0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_dj_ctrl_02,		reg_dj_g0_cnt_min,			GET_BITS(pp->shp_cmn_post[26],0,5),\
															reg_dj_g0_mul,				GET_BITS(pp->shp_cmn_post[27],0,5));

				
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_00,	reg_fd_cross_th,			GET_BITS(pp->shp_map_cmn_post[0],0,8),\
															reg_fd_pre_a_map_h_size,	GET_BITS(pp->shp_map_cmn_post[14],0,3),\
															reg_fd_pre_a_map_v_size,	GET_BITS(pp->shp_map_cmn_post[15],0,2),\
															reg_fd_pre_a_cut_resolution,GET_BITS(pp->shp_map_cmn_post[16],0,3));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_00,	reg_fd_a_map_h_size,		GET_BITS(pp->shp_map_cmn_post[17],0,2),\
															reg_fd_a_nomalize_en,		GET_BITS(pp->shp_map_cmn_post[18],0,1),\
															reg_fd_t_cut_resolution,	GET_BITS(pp->shp_map_cmn_post[33],0,2),\
															reg_fd_t_nomalize_en,		GET_BITS(pp->shp_map_cmn_post[34],0,1));
				PE_SHP_HW_M17C0_RES_WR02(shp_coring_ctrl_08,	reg_fd_mul_base_t,			GET_BITS(pp->shp_map_cmn_post[1],0,8),\
															reg_fd_mul_base_e,			GET_BITS(pp->shp_map_cmn_post[2],0,8));			
				PE_SHP_HW_M17C0_RES_WR03(shp_mnr_ctrl_00,		reg_fd_mnr_gain_e_en,		GET_BITS(pp->shp_map_cmn_post[3],0,1),\
															reg_fd_mnr_gain_t_en,		GET_BITS(pp->shp_map_cmn_post[4],0,1),\
															reg_fd_mnr_s1_h_expand,		GET_BITS(pp->shp_map_cmn_post[5],0,2));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_mnr_ctrl_01,		reg_fd_mnr_s1_mmd_min  ,GET_BITS(pp->shp_map_cmn_post[6],0,8),\
															reg_fd_mnr_s2_ratio_min,GET_BITS(pp->shp_map_cmn_post[7],0,8),\
															reg_fd_mnr_s2_ratio_max,GET_BITS(pp->shp_map_cmn_post[8],0,8),\
															reg_fd_mnr_s2_mmd_min,  GET_BITS(pp->shp_map_cmn_post[9],0,8));
				PE_SHP_HW_M17C0_RES_WR04(shp_mnr_ctrl_02,		reg_fd_gain_x0,			GET_BITS(pp->shp_map_cmn_post[10],0,8),\
															reg_fd_gain_x1,			GET_BITS(pp->shp_map_cmn_post[11],0,8),\
															reg_fd_gain_y0,			GET_BITS(pp->shp_map_cmn_post[12],0,8),\
															reg_fd_gain_y1,			GET_BITS(pp->shp_map_cmn_post[13],0,8));
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_01,	reg_fd_detail_beta_mul, GET_BITS(pp->shp_map_cmn_post[36],0,8),\
															reg_fd_detail_alpha_mul,GET_BITS(pp->shp_map_cmn_post[35],0,8),\
															reg_fd_edge_beta_mul,   GET_BITS(pp->shp_map_cmn_post[20],0,8),\
															reg_fd_edge_alpha_mul,  GET_BITS(pp->shp_map_cmn_post[19],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_02,	reg_fd_a_lut_edge_x0,	GET_BITS(pp->shp_map_cmn_post[21],0,8),\
															reg_fd_a_lut_edge_y0,	GET_BITS(pp->shp_map_cmn_post[22],0,8),\
															reg_fd_a_lut_edge_x1,	GET_BITS(pp->shp_map_cmn_post[23],0,8),\
															reg_fd_a_lut_edge_y1,	GET_BITS(pp->shp_map_cmn_post[24],0,8));
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_03,	reg_fd_a_lut_detail_x0,	GET_BITS(pp->shp_map_cmn_post[25],0,8),\
															reg_fd_a_lut_detail_y0,	GET_BITS(pp->shp_map_cmn_post[26],0,8),\
															reg_fd_a_lut_detail_x1,	GET_BITS(pp->shp_map_cmn_post[27],0,8),\
															reg_fd_a_lut_detail_y1,	GET_BITS(pp->shp_map_cmn_post[28],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_06,	reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_post[29],0,8),\
															reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_post[30],0,8),\
															reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_post[31],0,8),\
															reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_post[32],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_04,	reg_fd_t_lut_edge_x0,	GET_BITS(pp->shp_map_cmn_post[37],0,8),\
															reg_fd_t_lut_edge_y0,	GET_BITS(pp->shp_map_cmn_post[38],0,8),\
															reg_fd_t_lut_edge_x1,	GET_BITS(pp->shp_map_cmn_post[39],0,8),\
															reg_fd_t_lut_edge_y1,	GET_BITS(pp->shp_map_cmn_post[40],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_05,	reg_fd_t_lut_detail_x0,	GET_BITS(pp->shp_map_cmn_post[41],0,8),\
															reg_fd_t_lut_detail_y0,	GET_BITS(pp->shp_map_cmn_post[42],0,8),\
															reg_fd_t_lut_detail_x1,	GET_BITS(pp->shp_map_cmn_post[43],0,8),\
															reg_fd_t_lut_detail_y1,	GET_BITS(pp->shp_map_cmn_post[44],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_coring_ctrl_07,	reg_fd_detail_minmax_x0,GET_BITS(pp->shp_map_cmn_post[45],0,8),\
															reg_fd_detail_minmax_y0,GET_BITS(pp->shp_map_cmn_post[46],0,8),\
															reg_fd_detail_minmax_x1,GET_BITS(pp->shp_map_cmn_post[47],0,8),\
															reg_fd_detail_minmax_y1,GET_BITS(pp->shp_map_cmn_post[48],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_mp_ctrl_07,		reg_mp_gb_en,			GET_BITS(pp->shp_balance_post[0],0,1),\
															reg_mp_gb_mode,			GET_BITS(pp->shp_balance_post[1],0,1),\
															reg_mp_gb_x1,			GET_BITS(pp->shp_balance_post[2],0,8),\
															reg_mp_gb_y1,			GET_BITS(pp->shp_balance_post[4],0,8));
				PE_SHP_HW_M17C0_RES_WR03(shp_mp_ctrl_08,		reg_mp_gb_x2,			GET_BITS(pp->shp_balance_post[3],0,8),\
															reg_mp_gb_y2,			GET_BITS(pp->shp_balance_post[5],0,8),\
															reg_mp_gb_y3,			GET_BITS(pp->shp_balance_post[6],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_sp_ctrl_07,		reg_sp_gb_en,			GET_BITS(pp->shp_balance_post[7],0,1),\
															reg_sp_gb_mode,			GET_BITS(pp->shp_balance_post[8],0,1),\
															reg_sp_gb_x1,			GET_BITS(pp->shp_balance_post[9],0,8),\
															reg_sp_gb_y1,			GET_BITS(pp->shp_balance_post[11],0,8));
				PE_SHP_HW_M17C0_RES_WR03(shp_sp_ctrl_08,		reg_sp_gb_x2,			GET_BITS(pp->shp_balance_post[10],0,8),\
															reg_sp_gb_y2,			GET_BITS(pp->shp_balance_post[12],0,8),\
															reg_sp_gb_y3,			GET_BITS(pp->shp_balance_post[13],0,8));
				
				PE_SHP_HW_M17C0_RES_WR05(shp_contrast_ctrl_00,reg_lc_shp_en,			GET_BITS(pp->shp_balance_post[14],0,1),\
															reg_lc_gb_en,			GET_BITS(pp->shp_balance_post[15],0,8),\
															reg_lc_center_target,	GET_BITS(pp->shp_balance_post[22],0,8),\
															reg_lc_center_gain,  	GET_BITS(pp->shp_balance_post[23],0,8),\
															reg_lc_local_gain,   	GET_BITS(pp->shp_balance_post[24],0,8));
				PE_SHP_HW_M17C0_RES_WR04(shp_contrast_ctrl_01,reg_lc_gb_x1,			GET_BITS(pp->shp_balance_post[16],0,8),\
															reg_lc_gb_x2,			GET_BITS(pp->shp_balance_post[17],0,8),\
															reg_lc_gb_y1,			GET_BITS(pp->shp_balance_post[19],0,8),\
															reg_lc_gb_y2,			GET_BITS(pp->shp_balance_post[20],0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_contrast_ctrl_02,reg_lc_gb_x3,			GET_BITS(pp->shp_balance_post[18],0,8),\
															reg_lc_gb_y3,			GET_BITS(pp->shp_balance_post[21],0,8));


				
				PE_SHP_HW_M17C0_RES_WR04(shp_mp_ctrl_09,		reg_mp_lum1_x_l0,	GET_BITS(pp->shp_balance_post[25],0,8),\
															reg_mp_lum1_x_l1,	GET_BITS(pp->shp_balance_post[26],0,8),\
															reg_mp_lum1_x_h0,	GET_BITS(pp->shp_balance_post[27],0,8),\
															reg_mp_lum1_x_h1,	GET_BITS(pp->shp_balance_post[28],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_mp_ctrl_0a,		reg_mp_lum1_y0,		GET_BITS(pp->shp_balance_post[29],0,8),\
															reg_mp_lum1_y1,		GET_BITS(pp->shp_balance_post[30],0,8),\
															reg_mp_lum1_y2,		GET_BITS(pp->shp_balance_post[31],0,8),\
															reg_mp_lum2_x_l0,	GET_BITS(pp->shp_balance_post[32],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_mp_ctrl_0b,		reg_mp_lum2_x_l1,	GET_BITS(pp->shp_balance_post[33],0,8),\
															reg_mp_lum2_x_h0,	GET_BITS(pp->shp_balance_post[34],0,8),\
															reg_mp_lum2_x_h1,	GET_BITS(pp->shp_balance_post[35],0,8),\
															reg_mp_lum2_y0,  	GET_BITS(pp->shp_balance_post[36],0,8));
				
				PE_SHP_HW_M17C0_RES_WR02(shp_mp_ctrl_0c,		reg_mp_lum2_y1,		GET_BITS(pp->shp_balance_post[37],0,8),\
															reg_mp_lum2_y2,		GET_BITS(pp->shp_balance_post[38],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_sp_ctrl_09,		reg_sp_lum1_x_l0,	GET_BITS(pp->shp_balance_post[39],0,8),\
															reg_sp_lum1_x_l1,	GET_BITS(pp->shp_balance_post[40],0,8),\
															reg_sp_lum1_x_h0,	GET_BITS(pp->shp_balance_post[41],0,8),\
															reg_sp_lum1_x_h1,	GET_BITS(pp->shp_balance_post[42],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_sp_ctrl_0a,		reg_sp_lum1_y0,		GET_BITS(pp->shp_balance_post[43],0,8),\
															reg_sp_lum1_y1,		GET_BITS(pp->shp_balance_post[44],0,8),\
															reg_sp_lum1_y2,		GET_BITS(pp->shp_balance_post[45],0,8),\
															reg_sp_lum2_x_l0,	GET_BITS(pp->shp_balance_post[46],0,8));
				
				PE_SHP_HW_M17C0_RES_WR04(shp_sp_ctrl_0b,		reg_sp_lum2_x_l1,	GET_BITS(pp->shp_balance_post[47],0,8),\
															reg_sp_lum2_x_h0,	GET_BITS(pp->shp_balance_post[48],0,8),\
															reg_sp_lum2_x_h1,	GET_BITS(pp->shp_balance_post[49],0,8),\
															reg_sp_lum2_y0, 	GET_BITS(pp->shp_balance_post[50],0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_sp_ctrl_0c,		reg_sp_lum2_y1,		GET_BITS(pp->shp_balance_post[51],0,8),\
															reg_sp_lum2_y2,		GET_BITS(pp->shp_balance_post[52],0,8));


				
				
				PE_SHP_HW_M17C0_RES_WR04(shp_pti_ctrl_00,	reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_post[0],0,1),\
														reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_post[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_post[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_post[3],0,2));
				PE_SHP_HW_M17C0_RES_WR04(shp_pti_ctrl_01,	reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_post[4],0,1),\
														reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_post[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_post[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_post[7],0,2));
				PE_SHP_HW_M17C0_RES_WR04(shp_sti_ctrl_00,	reg_sti_enable,			GET_BITS(pp->shp_ti_cmn_post[8],0,1),\
														reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_post[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_post[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_post[11],0,2));
				PE_SHP_HW_M17C0_RES_WR03(shp_dp_ctrl_04,	reg_snr_blur_en,		GET_BITS(pp->shp_simple_snr_post[0],0,1),\
														reg_snr_blur_sel,		GET_BITS(pp->shp_simple_snr_post[1],0,2),\
														reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_post[2],0,8));
#ifdef PE_SHP_HW_M17C0_CTI_CMN_CHANGE
				PE_SHP_HW_M17C0_CTI_DNR0_WR04(cti_ctrl_0,		cti_en,				GET_BITS(pp->shp_cti_cmn_post[0],0,1),\
																cti_clipping_mode,	GET_BITS(pp->shp_cti_cmn_post[2],0,1),\
																cti_pre_flt_mode,	GET_BITS(pp->shp_cti_cmn_post[3],0,2),\
																cti_tap,			GET_BITS(pp->shp_cti_cmn_post[4],0,1));
				PE_SHP_HW_M17C0_CTI_SHP_WR02(shp_cti_ctrl_00,	reg_cti_en,			GET_BITS(pp->shp_cti_cmn_post[5],0,8),\
																reg_cti_filter_tap_size,	GET_BITS(pp->shp_cti_cmn_post[7],0,2));
				PE_SHP_HW_M17C0_CTI_SHP_WR01(shp_cti_ctrl_02,	reg_cti_ycm_en,		GET_BITS(pp->shp_cti_cmn_post[6],0,8));
				PE_SHP_HW_M17C0_CTI_DNR0_WR01(reg_cti_ctrl_2,	reg_ycm_en,			GET_BITS(pp->shp_cti_cmn_post[1],0,1));
#endif

				#ifdef PE_SHP_HW_M17C0_SHP_MOTION_ENABLE
				PE_SHP_M17C0_QWr01(shp_fsw_ctrl_00,			dnr_decont,		GET_BITS(pp->shp_motion_post[0],0,1));
				PE_SHP_HW_M17C0_RES_SET_USER(shp_motion_ctrl_00, reg_motion_adaptive_en, GET_BITS(pp->shp_motion_post[0],0,1));
				#else
				PE_SHP_HW_M17C0_RES_WR01(shp_motion_ctrl_00,	reg_motion_adaptive_en,	GET_BITS(pp->shp_motion_post[0],0,1));
				#endif
				#ifdef PE_SHP_HW_M17C0_CTI_CMN_CHANGE
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_01,	reg_motion_lut_a_y0,	GET_BITS(pp->shp_motion_post[1],0,8),\
																reg_motion_lut_a_y1,	GET_BITS(pp->shp_motion_post[2],0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_02,	reg_motion_lut_a_y2,	GET_BITS(pp->shp_motion_post[3],0,8),\
																reg_motion_lut_a_y3,	GET_BITS(pp->shp_motion_post[4],0,8));
				/*inkyung.park 20170801,temporally setting for super resolution menu until new DB determined*/
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_03,	reg_motion_lut_t_y0,	GET_BITS(pp->shp_motion_post[5],0,8),\
																reg_motion_lut_t_y1,	GET_BITS(pp->shp_motion_post[6],0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_04,	reg_motion_lut_t_y2,	GET_BITS(pp->shp_motion_post[7],0,8),\
																reg_motion_lut_t_y3,	GET_BITS(pp->shp_motion_post[8],0,8));
				
				#else
				PE_SHP_HW_M17C0_RES_WR04(shp_motion_ctrl_01,	reg_motion_lut_a_y0,	GET_BITS(0xff,0,8),\
																reg_motion_lut_a_x0,	GET_BITS(0x0 ,0,8),\
																reg_motion_lut_a_y1,	GET_BITS(0xc0,0,8),\
																reg_motion_lut_a_x1,	GET_BITS(0x40,0,8));
				PE_SHP_HW_M17C0_RES_WR04(shp_motion_ctrl_02,	reg_motion_lut_a_y2,	GET_BITS(0x80,0,8),\
																reg_motion_lut_a_x2,	GET_BITS(0x6e,0,8),\
																reg_motion_lut_a_y3,	GET_BITS(0x40,0,8),\
																reg_motion_lut_a_x3,	GET_BITS(0xff,0,8));
				/*inkyung.park 20170801,temporally setting for super resolution menu until new DB determined*/
				PE_SHP_HW_M17C0_RES_WR04(shp_motion_ctrl_03,	reg_motion_lut_t_y0,	GET_BITS(0xff,0,8),\
																reg_motion_lut_t_x0,	GET_BITS(0x0 ,0,8),\
																reg_motion_lut_t_y1,	GET_BITS(0xc0,0,8),\
																reg_motion_lut_t_x1,	GET_BITS(0x40,0,8));
				PE_SHP_HW_M17C0_RES_WR04(shp_motion_ctrl_04,	reg_motion_lut_t_y2,	GET_BITS(0x80,0,8),\
																reg_motion_lut_t_x2,	GET_BITS(0x6e,0,8),\
																reg_motion_lut_t_y3,	GET_BITS(0x40,0,8),\
																reg_motion_lut_t_x3,	GET_BITS(0xff,0,8));
				#endif
				
				
				PE_SHP_HW_M17C0_RES_WR03(shp_chroma_ctrl_00,	reg_chr_color_region_en,GET_BITS(pp->shp_chroma_post[0],0,1),\
															reg_chr_protection_en,	GET_BITS(pp->shp_chroma_post[1],0,1),\
															reg_chr_compensation_en,GET_BITS(pp->shp_chroma_post[2],0,1));
				PE_SHP_HW_M17C0_RES_WR02(shp_chroma_ctrl_0d,	reg_chr_r0_gain,		GET_BITS(pp->shp_chroma_post[3],0,8),\
															reg_chr_r1_gain,		GET_BITS(pp->shp_chroma_post[4],0,8));

			
				#else
				PE_SHP_M17C0_QWr01(shp_derh_ctrl_06,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_post[0],0,1));
				PE_SHP_M17C0_QWr04(shp_dp_ctrl_05,	reg_der_x0,					GET_BITS(pp->shp_cmn_post[1],0,8),\
													reg_der_x1,		 			GET_BITS(pp->shp_cmn_post[2],0,8),\
													reg_der_y0,					GET_BITS(pp->shp_cmn_post[5],0,8),\
													reg_der_y1,		 			GET_BITS(pp->shp_cmn_post[6],0,8));
				PE_SHP_M17C0_QWr04(shp_dp_ctrl_06,	reg_der_x2,					GET_BITS(pp->shp_cmn_post[3],0,8),\
													reg_der_x3,		 			GET_BITS(pp->shp_cmn_post[4],0,8),\
													reg_der_y2,					GET_BITS(pp->shp_cmn_post[7],0,8),\
													reg_der_y3,		 			GET_BITS(pp->shp_cmn_post[8],0,8));
				PE_SHP_M17C0_QWr01(shp_mp_ctrl_00,	reg_mp_shp_en,				GET_BITS(pp->shp_cmn_post[9],0,1));
				PE_SHP_M17C0_QWr01(shp_sp_ctrl_00,	reg_sp_shp_en,				GET_BITS(pp->shp_cmn_post[10],0,1));
				PE_SHP_M17C0_QWr01(shp_mp_ctrl_02,	reg_mp_lap_weight,			GET_BITS(pp->shp_cmn_post[11],0,8));
				PE_SHP_M17C0_QWr01(shp_sp_ctrl_02,	reg_sp_lap_weight,			GET_BITS(pp->shp_cmn_post[12],0,8));\
				PE_SHP_M17C0_QWr03(shp_derh_ctrl_07,	reg_derh_flat_filter_en,	GET_BITS(pp->shp_cmn_post[13],0,1),\
													reg_derh_flat_filter_type,	GET_BITS(pp->shp_cmn_post[14],0,1),\
													reg_derh_flat_filter_gain,	GET_BITS(pp->shp_cmn_post[15],0,6));
				PE_SHP_M17C0_QWr06(shp_dj_ctrl_00,	reg_dj_edf_en,				GET_BITS(pp->shp_cmn_post[16],0,1),\
													reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_cmn_post[17],0,1),\
													reg_dj_center_blur_mode,	GET_BITS(pp->shp_cmn_post[20],0,2),\
													reg_dj_count_diff_th,		GET_BITS(pp->shp_cmn_post[21],0,5),\
													reg_dj_n_avg_mode,		 	GET_BITS(pp->shp_cmn_post[22],0,1),\
													reg_dj_line_variation_diff_th,	GET_BITS(pp->shp_cmn_post[23],0,8));
				PE_SHP_M17C0_QWr04(shp_dj_ctrl_03,	reg_dj_edge_min,			GET_BITS(pp->shp_cmn_post[18],0,8),\
													reg_dj_edge_mul,			GET_BITS(pp->shp_cmn_post[19],0,8),\
													reg_dj_g1_protect_min,		GET_BITS(pp->shp_cmn_post[28],0,8),\
													reg_dj_g1_mul,				GET_BITS(pp->shp_cmn_post[29],0,7));
				
				PE_SHP_M17C0_QWr02(shp_dj_ctrl_01,	reg_dj_level_th,			GET_BITS(pp->shp_cmn_post[24],0,8),\
													reg_dj_n_avg_gain,			GET_BITS(pp->shp_cmn_post[25],0,8));
				PE_SHP_M17C0_QWr02(shp_dj_ctrl_02,	reg_dj_g0_cnt_min,			GET_BITS(pp->shp_cmn_post[26],0,5),\
													reg_dj_g0_mul,				GET_BITS(pp->shp_cmn_post[27],0,5));

				
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_00,reg_fd_cross_th,			GET_BITS(pp->shp_map_cmn_post[0],0,8),\
													reg_fd_pre_a_map_h_size,	GET_BITS(pp->shp_map_cmn_post[14],0,3),\
													reg_fd_pre_a_map_v_size,	GET_BITS(pp->shp_map_cmn_post[15],0,2),\
													reg_fd_pre_a_cut_resolution,GET_BITS(pp->shp_map_cmn_post[16],0,3));
				
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_00,reg_fd_a_map_h_size,		GET_BITS(pp->shp_map_cmn_post[17],0,2),\
													reg_fd_a_nomalize_en,		GET_BITS(pp->shp_map_cmn_post[18],0,1),\
													reg_fd_t_cut_resolution,	GET_BITS(pp->shp_map_cmn_post[33],0,2),\
													reg_fd_t_nomalize_en,		GET_BITS(pp->shp_map_cmn_post[34],0,1));
				PE_SHP_M17C0_QWr02(shp_coring_ctrl_08,reg_fd_mul_base_t,			GET_BITS(pp->shp_map_cmn_post[1],0,8),\
													reg_fd_mul_base_e,			GET_BITS(pp->shp_map_cmn_post[2],0,8));			
				PE_SHP_M17C0_QWr03(shp_mnr_ctrl_00,	reg_fd_mnr_gain_e_en,		GET_BITS(pp->shp_map_cmn_post[3],0,1),\
													reg_fd_mnr_gain_t_en,		GET_BITS(pp->shp_map_cmn_post[4],0,1),\
													reg_fd_mnr_s1_h_expand,		GET_BITS(pp->shp_map_cmn_post[5],0,2));
				PE_SHP_M17C0_QWr04(shp_mnr_ctrl_01,	reg_fd_mnr_s1_mmd_min  ,GET_BITS(pp->shp_map_cmn_post[6],0,8),\
													reg_fd_mnr_s2_ratio_min,GET_BITS(pp->shp_map_cmn_post[7],0,8),\
													reg_fd_mnr_s2_ratio_max,GET_BITS(pp->shp_map_cmn_post[8],0,8),\
													reg_fd_mnr_s2_mmd_min,  GET_BITS(pp->shp_map_cmn_post[9],0,8));
				PE_SHP_M17C0_QWr04(shp_mnr_ctrl_02,	reg_fd_gain_x0,			GET_BITS(pp->shp_map_cmn_post[10],0,8),\
													reg_fd_gain_x1,			GET_BITS(pp->shp_map_cmn_post[11],0,8),\
													reg_fd_gain_y0,			GET_BITS(pp->shp_map_cmn_post[12],0,8),\
													reg_fd_gain_y1,			GET_BITS(pp->shp_map_cmn_post[13],0,8));
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_01,reg_fd_detail_beta_mul, GET_BITS(pp->shp_map_cmn_post[36],0,8),\
													reg_fd_detail_alpha_mul,GET_BITS(pp->shp_map_cmn_post[35],0,8),\
													reg_fd_edge_beta_mul,   GET_BITS(pp->shp_map_cmn_post[20],0,8),\
													reg_fd_edge_alpha_mul,  GET_BITS(pp->shp_map_cmn_post[19],0,8));
				
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_02,reg_fd_a_lut_edge_x0,	GET_BITS(pp->shp_map_cmn_post[21],0,8),\
													reg_fd_a_lut_edge_y0,	GET_BITS(pp->shp_map_cmn_post[22],0,8),\
													reg_fd_a_lut_edge_x1,	GET_BITS(pp->shp_map_cmn_post[23],0,8),\
													reg_fd_a_lut_edge_y1,	GET_BITS(pp->shp_map_cmn_post[24],0,8));
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_03,reg_fd_a_lut_detail_x0,	GET_BITS(pp->shp_map_cmn_post[25],0,8),\
													reg_fd_a_lut_detail_y0,	GET_BITS(pp->shp_map_cmn_post[26],0,8),\
													reg_fd_a_lut_detail_x1,	GET_BITS(pp->shp_map_cmn_post[27],0,8),\
													reg_fd_a_lut_detail_y1,	GET_BITS(pp->shp_map_cmn_post[28],0,8));
				
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_06,reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_post[29],0,8),\
													reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_post[30],0,8),\
													reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_post[31],0,8),\
													reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_post[32],0,8));
				
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_04,reg_fd_t_lut_edge_x0,	GET_BITS(pp->shp_map_cmn_post[37],0,8),\
													reg_fd_t_lut_edge_y0,	GET_BITS(pp->shp_map_cmn_post[38],0,8),\
													reg_fd_t_lut_edge_x1,	GET_BITS(pp->shp_map_cmn_post[39],0,8),\
													reg_fd_t_lut_edge_y1,	GET_BITS(pp->shp_map_cmn_post[40],0,8));
				
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_05,reg_fd_t_lut_detail_x0,	GET_BITS(pp->shp_map_cmn_post[41],0,8),\
													reg_fd_t_lut_detail_y0,	GET_BITS(pp->shp_map_cmn_post[42],0,8),\
													reg_fd_t_lut_detail_x1,	GET_BITS(pp->shp_map_cmn_post[43],0,8),\
													reg_fd_t_lut_detail_y1,	GET_BITS(pp->shp_map_cmn_post[44],0,8));
				
				PE_SHP_M17C0_QWr04(shp_coring_ctrl_07,reg_fd_detail_minmax_x0,GET_BITS(pp->shp_map_cmn_post[45],0,8),\
													reg_fd_detail_minmax_y0,GET_BITS(pp->shp_map_cmn_post[46],0,8),\
													reg_fd_detail_minmax_x1,GET_BITS(pp->shp_map_cmn_post[47],0,8),\
													reg_fd_detail_minmax_y1,GET_BITS(pp->shp_map_cmn_post[48],0,8));
				
				PE_SHP_M17C0_QWr04(shp_mp_ctrl_07,	reg_mp_gb_en,			GET_BITS(pp->shp_balance_post[0],0,1),\
													reg_mp_gb_mode,			GET_BITS(pp->shp_balance_post[1],0,1),\
													reg_mp_gb_x1,			GET_BITS(pp->shp_balance_post[2],0,8),\
													reg_mp_gb_y1,			GET_BITS(pp->shp_balance_post[4],0,8));
				PE_SHP_M17C0_QWr03(shp_mp_ctrl_08,	reg_mp_gb_x2,			GET_BITS(pp->shp_balance_post[3],0,8),\
													reg_mp_gb_y2,			GET_BITS(pp->shp_balance_post[5],0,8),\
													reg_mp_gb_y3,			GET_BITS(pp->shp_balance_post[6],0,8));
				
				PE_SHP_M17C0_QWr04(shp_sp_ctrl_07,	reg_sp_gb_en,			GET_BITS(pp->shp_balance_post[7],0,1),\
													reg_sp_gb_mode,			GET_BITS(pp->shp_balance_post[8],0,1),\
													reg_sp_gb_x1,			GET_BITS(pp->shp_balance_post[9],0,8),\
													reg_sp_gb_y1,			GET_BITS(pp->shp_balance_post[11],0,8));
				PE_SHP_M17C0_QWr03(shp_sp_ctrl_08,	reg_sp_gb_x2,			GET_BITS(pp->shp_balance_post[10],0,8),\
													reg_sp_gb_y2,			GET_BITS(pp->shp_balance_post[12],0,8),\
													reg_sp_gb_y3,			GET_BITS(pp->shp_balance_post[13],0,8));
				
				PE_SHP_M17C0_QWr05(shp_contrast_ctrl_00,reg_lc_shp_en,			GET_BITS(pp->shp_balance_post[14],0,1),\
													reg_lc_gb_en,			GET_BITS(pp->shp_balance_post[15],0,8),\
													reg_lc_center_target,	GET_BITS(pp->shp_balance_post[22],0,8),\
													reg_lc_center_gain,  	GET_BITS(pp->shp_balance_post[23],0,8),\
													reg_lc_local_gain,  	GET_BITS(pp->shp_balance_post[24],0,8));
				PE_SHP_M17C0_QWr04(shp_contrast_ctrl_01,reg_lc_gb_x1,			GET_BITS(pp->shp_balance_post[16],0,8),\
													reg_lc_gb_x2,			GET_BITS(pp->shp_balance_post[17],0,8),\
													reg_lc_gb_y1,			GET_BITS(pp->shp_balance_post[19],0,8),\
													reg_lc_gb_y2,			GET_BITS(pp->shp_balance_post[20],0,8));
				PE_SHP_M17C0_QWr02(shp_contrast_ctrl_02,reg_lc_gb_x3,			GET_BITS(pp->shp_balance_post[18],0,8),\
													reg_lc_gb_y3,			GET_BITS(pp->shp_balance_post[21],0,8));
				PE_SHP_M17C0_QWr04(shp_mp_ctrl_09,	reg_mp_lum1_x_l0,	GET_BITS(pp->shp_balance_post[25],0,8),\
													reg_mp_lum1_x_l1,	GET_BITS(pp->shp_balance_post[26],0,8),\
													reg_mp_lum1_x_h0,	GET_BITS(pp->shp_balance_post[27],0,8),\
													reg_mp_lum1_x_h1,	GET_BITS(pp->shp_balance_post[28],0,8));
				
				PE_SHP_M17C0_QWr04(shp_mp_ctrl_0a,	reg_mp_lum1_y0,		GET_BITS(pp->shp_balance_post[29],0,8),\
													reg_mp_lum1_y1,		GET_BITS(pp->shp_balance_post[30],0,8),\
													reg_mp_lum1_y2,		GET_BITS(pp->shp_balance_post[31],0,8),\
													reg_mp_lum2_x_l0,	GET_BITS(pp->shp_balance_post[32],0,8));
				
				PE_SHP_M17C0_QWr04(shp_mp_ctrl_0b,	reg_mp_lum2_x_l1,	GET_BITS(pp->shp_balance_post[33],0,8),\
													reg_mp_lum2_x_h0,	GET_BITS(pp->shp_balance_post[34],0,8),\
													reg_mp_lum2_x_h1,	GET_BITS(pp->shp_balance_post[35],0,8),\
													reg_mp_lum2_y0,  	GET_BITS(pp->shp_balance_post[36],0,8));
				
				PE_SHP_M17C0_QWr02(shp_mp_ctrl_0c,	reg_mp_lum2_y1,		GET_BITS(pp->shp_balance_post[37],0,8),\
													reg_mp_lum2_y2,		GET_BITS(pp->shp_balance_post[38],0,8));
				
				PE_SHP_M17C0_QWr04(shp_sp_ctrl_09,	reg_sp_lum1_x_l0,	GET_BITS(pp->shp_balance_post[39],0,8),\
													reg_sp_lum1_x_l1,	GET_BITS(pp->shp_balance_post[40],0,8),\
													reg_sp_lum1_x_h0,	GET_BITS(pp->shp_balance_post[41],0,8),\
													reg_sp_lum1_x_h1,	GET_BITS(pp->shp_balance_post[42],0,8));
				
				PE_SHP_M17C0_QWr04(shp_sp_ctrl_0a,	reg_sp_lum1_y0,		GET_BITS(pp->shp_balance_post[43],0,8),\
													reg_sp_lum1_y1,		GET_BITS(pp->shp_balance_post[44],0,8),\
													reg_sp_lum1_y2,		GET_BITS(pp->shp_balance_post[45],0,8),\
													reg_sp_lum2_x_l0,	GET_BITS(pp->shp_balance_post[46],0,8));
				
				PE_SHP_M17C0_QWr04(shp_sp_ctrl_0b,	reg_sp_lum2_x_l1,	GET_BITS(pp->shp_balance_post[47],0,8),\
													reg_sp_lum2_x_h0,	GET_BITS(pp->shp_balance_post[48],0,8),\
													reg_sp_lum2_x_h1,	GET_BITS(pp->shp_balance_post[49],0,8),\
													reg_sp_lum2_y0, 	GET_BITS(pp->shp_balance_post[50],0,8));
				PE_SHP_M17C0_QWr02(shp_sp_ctrl_0c,	reg_sp_lum2_y1,		GET_BITS(pp->shp_balance_post[51],0,8),\
													reg_sp_lum2_y2,		GET_BITS(pp->shp_balance_post[52],0,8));


				
				
				PE_SHP_M17C0_QWr04(shp_pti_ctrl_00,		reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_post[0],0,1),\
														reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_post[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_post[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_post[3],0,2));
				PE_SHP_M17C0_QWr04(shp_pti_ctrl_01,		reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_post[4],0,1),\
														reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_post[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_post[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_post[7],0,2));
				PE_SHP_M17C0_QWr04(shp_sti_ctrl_00,		reg_sti_enable,			GET_BITS(pp->shp_ti_cmn_post[8],0,1),\
														reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_post[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_post[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_post[11],0,2));
				PE_SHP_M17C0_QWr03(shp_dp_ctrl_04,		reg_snr_blur_en,		GET_BITS(pp->shp_simple_snr_post[0],0,1),\
														reg_snr_blur_sel,		GET_BITS(pp->shp_simple_snr_post[1],0,2),\
														reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_post[2],0,8));
#ifdef PE_SHP_HW_M17C0_CTI_CMN_CHANGE
				PE_SHP_HW_M17C0_CTI_DNR0_WR04(cti_ctrl_0,		cti_en,				GET_BITS(pp->shp_cti_cmn_post[0],0,1),\
																cti_clipping_mode,	GET_BITS(pp->shp_cti_cmn_post[2],0,1),\
																cti_pre_flt_mode,	GET_BITS(pp->shp_cti_cmn_post[3],0,2),\
																cti_tap,			GET_BITS(pp->shp_cti_cmn_post[4],0,1));
				PE_SHP_HW_M17C0_CTI_SHP_WR02(shp_cti_ctrl_00,	reg_cti_en,			GET_BITS(pp->shp_cti_cmn_post[5],0,8),\
																reg_cti_filter_tap_size,	GET_BITS(pp->shp_cti_cmn_post[7],0,2));
				PE_SHP_HW_M17C0_CTI_SHP_WR01(shp_cti_ctrl_02,	reg_cti_ycm_en,		GET_BITS(pp->shp_cti_cmn_post[6],0,8));
				PE_SHP_HW_M17C0_CTI_DNR0_WR02(reg_cti_ctrl_2,	reg_ycm_en,			GET_BITS(pp->shp_cti_cmn_post[1],0,1));
#endif
				
				PE_SHP_M17C0_QWr01(shp_motion_ctrl_00,	reg_motion_adaptive_en,	GET_BITS(pp->shp_motion_post[0],0,1));
				#ifdef PE_SHP_HW_M17C0_CTI_CMN_CHANGE
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_01,	reg_motion_lut_a_y0,	GET_BITS(pp->shp_motion_post[1],0,8),\
																reg_motion_lut_a_y1,	GET_BITS(pp->shp_motion_post[2],0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_02,	reg_motion_lut_a_y2,	GET_BITS(pp->shp_motion_post[3],0,8),\
																reg_motion_lut_a_y3,	GET_BITS(pp->shp_motion_post[4],0,8));
				/*inkyung.park 20170801,temporally setting for super resolution menu until new DB determined*/
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_03,			reg_motion_lut_t_y0,	GET_BITS(pp->shp_motion_post[5],0,8),\
																reg_motion_lut_t_y1,	GET_BITS(pp->shp_motion_post[6],0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_04,			reg_motion_lut_t_y2,	GET_BITS(pp->shp_motion_post[7],0,8),\
																reg_motion_lut_t_y3,	GET_BITS(pp->shp_motion_post[8],0,8));
				#else
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_01,	reg_motion_lut_a_y0,	GET_BITS(0xff,0,8),\
																reg_motion_lut_a_x0,	GET_BITS(0x0 ,0,8),\
																reg_motion_lut_a_y1,	GET_BITS(0xc0,0,8),\
																reg_motion_lut_a_x1,	GET_BITS(0x40,0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_02,	reg_motion_lut_a_y2,	GET_BITS(0x80,0,8),\
																reg_motion_lut_a_x2,	GET_BITS(0x6e,0,8),\
																reg_motion_lut_a_y3,	GET_BITS(0x40,0,8),\
																reg_motion_lut_a_x3,	GET_BITS(0xff,0,8));
				/*inkyung.park 20170801,temporally setting for super resolution menu until new DB determined*/
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_03,	reg_motion_lut_t_y0,	GET_BITS(0xff,0,8),\
																reg_motion_lut_t_x0,	GET_BITS(0x0 ,0,8),\
																reg_motion_lut_t_y1,	GET_BITS(0xc0,0,8),\
																reg_motion_lut_t_x1,	GET_BITS(0x40,0,8));
				PE_SHP_HW_M17C0_RES_WR02(shp_motion_ctrl_04,	reg_motion_lut_t_y2,	GET_BITS(0x80,0,8),\
																reg_motion_lut_t_x2,	GET_BITS(0x6e,0,8),\
																reg_motion_lut_t_y3,	GET_BITS(0x40,0,8),\
																reg_motion_lut_t_x3,	GET_BITS(0xff,0,8));
				#endif
				PE_SHP_M17C0_QWr03(shp_chroma_ctrl_00,	reg_chr_color_region_en,GET_BITS(pp->shp_chroma_post[0],0,1),\
														reg_chr_protection_en,	GET_BITS(pp->shp_chroma_post[1],0,1),\
														reg_chr_compensation_en,GET_BITS(pp->shp_chroma_post[2],0,1));
				PE_SHP_M17C0_QWr02(shp_chroma_ctrl_0d,	reg_chr_r0_gain,		GET_BITS(pp->shp_chroma_post[3],0,8),\
														reg_chr_r1_gain,		GET_BITS(pp->shp_chroma_post[4],0,8));
				
				#endif
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		
	} while(0);
	return ret;
}
/**
 * get resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for M17C0X
 * - use input struct LX_PE_SHP_RE1_MISC_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			UINT8 *pd;
			LX_PE_SHP_RE6_MISC_T *pp=(LX_PE_SHP_RE6_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SHP_M17C0_QRd01(shp_derh_ctrl_06,	reg_derh_edge_y_filter_en,	pp->shp_cmn_post[0]);
				PE_SHP_M17C0_QRd04(shp_dp_ctrl_05,	reg_der_x0,					pp->shp_cmn_post[1],\
													reg_der_x1,		 			pp->shp_cmn_post[2],\
													reg_der_y0,					pp->shp_cmn_post[5],\
													reg_der_y1,		 			pp->shp_cmn_post[6]);
				PE_SHP_M17C0_QRd04(shp_dp_ctrl_06,	reg_der_x2,					pp->shp_cmn_post[3],\
													reg_der_x3,		 			pp->shp_cmn_post[4],\
													reg_der_y2,					pp->shp_cmn_post[7],\
													reg_der_y3,		 			pp->shp_cmn_post[8]);
				PE_SHP_M17C0_QRd01(shp_mp_ctrl_00,	reg_mp_shp_en,				pp->shp_cmn_post[9]);
				PE_SHP_M17C0_QRd01(shp_sp_ctrl_00,	reg_sp_shp_en,				pp->shp_cmn_post[10]);
				PE_SHP_M17C0_QRd01(shp_mp_ctrl_02,	reg_mp_lap_weight,			pp->shp_cmn_post[11]);
				PE_SHP_M17C0_QRd01(shp_sp_ctrl_02,	reg_sp_lap_weight,			pp->shp_cmn_post[12]);\
				PE_SHP_M17C0_QRd03(shp_derh_ctrl_07,	reg_derh_flat_filter_en,	pp->shp_cmn_post[13],\
													reg_derh_flat_filter_type,	pp->shp_cmn_post[14],\
													reg_derh_flat_filter_gain,	pp->shp_cmn_post[15]);
				PE_SHP_M17C0_QRd06(shp_dj_ctrl_00,	reg_dj_edf_en,				pp->shp_cmn_post[16],\
													reg_dj_edge_adaptive_en,	pp->shp_cmn_post[17],\
													reg_dj_center_blur_mode,	pp->shp_cmn_post[20],\
													reg_dj_count_diff_th,		pp->shp_cmn_post[21],\
													reg_dj_n_avg_mode,		 	pp->shp_cmn_post[22],\
													reg_dj_line_variation_diff_th,pp->shp_cmn_post[23]);
				PE_SHP_M17C0_QRd04(shp_dj_ctrl_03,	reg_dj_edge_min,			pp->shp_cmn_post[18],\
													reg_dj_edge_mul,			pp->shp_cmn_post[19],\
													reg_dj_g1_protect_min,		pp->shp_cmn_post[28],\
													reg_dj_g1_mul,				pp->shp_cmn_post[29]);
				
				PE_SHP_M17C0_QRd02(shp_dj_ctrl_01,	reg_dj_level_th,			pp->shp_cmn_post[24],\
													reg_dj_n_avg_gain,			pp->shp_cmn_post[25]);
				PE_SHP_M17C0_QRd02(shp_dj_ctrl_02,	reg_dj_g0_cnt_min,			pp->shp_cmn_post[26],\
													reg_dj_g0_mul,				pp->shp_cmn_post[27]);

				
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_00,reg_fd_cross_th,			pp->shp_map_cmn_post[0],\
													reg_fd_pre_a_map_h_size,	pp->shp_map_cmn_post[14],\
													reg_fd_pre_a_map_v_size,	pp->shp_map_cmn_post[15],\
													reg_fd_pre_a_cut_resolution,pp->shp_map_cmn_post[16]);
				
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_00,reg_fd_a_map_h_size,		pp->shp_map_cmn_post[17],\
													reg_fd_a_nomalize_en,		pp->shp_map_cmn_post[18],\
													reg_fd_t_cut_resolution,	pp->shp_map_cmn_post[33],\
													reg_fd_t_nomalize_en,		pp->shp_map_cmn_post[34]);
				PE_SHP_M17C0_QRd02(shp_coring_ctrl_08,reg_fd_mul_base_t,			pp->shp_map_cmn_post[1],\
													reg_fd_mul_base_e,			pp->shp_map_cmn_post[2]);			
				PE_SHP_M17C0_QRd03(shp_mnr_ctrl_00,	reg_fd_mnr_gain_e_en,		pp->shp_map_cmn_post[3],\
													reg_fd_mnr_gain_t_en,		pp->shp_map_cmn_post[4],\
													reg_fd_mnr_s1_h_expand,		pp->shp_map_cmn_post[5]);
				PE_SHP_M17C0_QRd04(shp_mnr_ctrl_01,	reg_fd_mnr_s1_mmd_min  ,pp->shp_map_cmn_post[6],\
													reg_fd_mnr_s2_ratio_min,pp->shp_map_cmn_post[7],\
													reg_fd_mnr_s2_ratio_max,pp->shp_map_cmn_post[8],\
													reg_fd_mnr_s2_mmd_min,  pp->shp_map_cmn_post[9]);
				PE_SHP_M17C0_QRd04(shp_mnr_ctrl_02,	reg_fd_gain_x0,			pp->shp_map_cmn_post[10],\
													reg_fd_gain_x1,			pp->shp_map_cmn_post[11],\
													reg_fd_gain_y0,			pp->shp_map_cmn_post[12],\
													reg_fd_gain_y1,			pp->shp_map_cmn_post[13]);
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_01,reg_fd_detail_beta_mul, pp->shp_map_cmn_post[36],\
													reg_fd_detail_alpha_mul,pp->shp_map_cmn_post[35],\
													reg_fd_edge_beta_mul,   pp->shp_map_cmn_post[20],\
													reg_fd_edge_alpha_mul,  pp->shp_map_cmn_post[19]);
				
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_02,reg_fd_a_lut_edge_x0,	pp->shp_map_cmn_post[21],\
													reg_fd_a_lut_edge_y0,	pp->shp_map_cmn_post[22],\
													reg_fd_a_lut_edge_x1,	pp->shp_map_cmn_post[23],\
													reg_fd_a_lut_edge_y1,	pp->shp_map_cmn_post[24]);
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_03,reg_fd_a_lut_detail_x0,	pp->shp_map_cmn_post[25],\
													reg_fd_a_lut_detail_y0,	pp->shp_map_cmn_post[26],\
													reg_fd_a_lut_detail_x1,	pp->shp_map_cmn_post[27],\
													reg_fd_a_lut_detail_y1,	pp->shp_map_cmn_post[28]);
				
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_06,reg_fd_edge_minmax_x0,	pp->shp_map_cmn_post[29],\
													reg_fd_edge_minmax_y0,	pp->shp_map_cmn_post[30],\
													reg_fd_edge_minmax_x1,	pp->shp_map_cmn_post[31],\
													reg_fd_edge_minmax_y1,	pp->shp_map_cmn_post[32]);
				
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_04,reg_fd_t_lut_edge_x0,	pp->shp_map_cmn_post[37],\
													reg_fd_t_lut_edge_y0,	pp->shp_map_cmn_post[38],\
													reg_fd_t_lut_edge_x1,	pp->shp_map_cmn_post[39],\
													reg_fd_t_lut_edge_y1,	pp->shp_map_cmn_post[40]);
				
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_05,reg_fd_t_lut_detail_x0,	pp->shp_map_cmn_post[41],\
													reg_fd_t_lut_detail_y0,	pp->shp_map_cmn_post[42],\
													reg_fd_t_lut_detail_x1,	pp->shp_map_cmn_post[43],\
													reg_fd_t_lut_detail_y1,	pp->shp_map_cmn_post[44]);
				
				PE_SHP_M17C0_QRd04(shp_coring_ctrl_07,reg_fd_detail_minmax_x0,pp->shp_map_cmn_post[45],\
													reg_fd_detail_minmax_y0,pp->shp_map_cmn_post[46],\
													reg_fd_detail_minmax_x1,pp->shp_map_cmn_post[47],\
													reg_fd_detail_minmax_y1,pp->shp_map_cmn_post[48]);
				
				PE_SHP_M17C0_QRd04(shp_mp_ctrl_07,	reg_mp_gb_en,			pp->shp_balance_post[0],\
													reg_mp_gb_mode,			pp->shp_balance_post[1],\
													reg_mp_gb_x1,			pp->shp_balance_post[2],\
													reg_mp_gb_y1,			pp->shp_balance_post[4]);
				PE_SHP_M17C0_QRd03(shp_mp_ctrl_08,	reg_mp_gb_x2,			pp->shp_balance_post[3],\
													reg_mp_gb_y2,			pp->shp_balance_post[5],\
													reg_mp_gb_y3,			pp->shp_balance_post[6]);
				
				PE_SHP_M17C0_QRd04(shp_sp_ctrl_07,	reg_sp_gb_en,			pp->shp_balance_post[7],\
													reg_sp_gb_mode,			pp->shp_balance_post[8],\
													reg_sp_gb_x1,			pp->shp_balance_post[9],\
													reg_sp_gb_y1,			pp->shp_balance_post[11]);
				PE_SHP_M17C0_QRd03(shp_sp_ctrl_08,	reg_sp_gb_x2,			pp->shp_balance_post[10],\
													reg_sp_gb_y2,			pp->shp_balance_post[12],\
													reg_sp_gb_y3,			pp->shp_balance_post[13]);
				
				PE_SHP_M17C0_QRd05(shp_contrast_ctrl_00,reg_lc_shp_en,		pp->shp_balance_post[14],\
													reg_lc_gb_en,			pp->shp_balance_post[15],\
													reg_lc_center_target,	pp->shp_balance_post[22],\
													reg_lc_center_gain,  	pp->shp_balance_post[23],\
													reg_lc_local_gain,  	pp->shp_balance_post[24]);
				PE_SHP_M17C0_QRd04(shp_contrast_ctrl_01,reg_lc_gb_x1,			pp->shp_balance_post[16],\
													reg_lc_gb_x2,			pp->shp_balance_post[17],\
													reg_lc_gb_y1,			pp->shp_balance_post[19],\
													reg_lc_gb_y2,			pp->shp_balance_post[20]);
				PE_SHP_M17C0_QRd02(shp_contrast_ctrl_02,reg_lc_gb_x3,			pp->shp_balance_post[18],\
													reg_lc_gb_y3,			pp->shp_balance_post[21]);
				PE_SHP_M17C0_QRd04(shp_mp_ctrl_09,	reg_mp_lum1_x_l0,	pp->shp_balance_post[25],\
													reg_mp_lum1_x_l1,	pp->shp_balance_post[26],\
													reg_mp_lum1_x_h0,	pp->shp_balance_post[27],\
													reg_mp_lum1_x_h1,	pp->shp_balance_post[28]);
				
				PE_SHP_M17C0_QRd04(shp_mp_ctrl_0a,	reg_mp_lum1_y0,		pp->shp_balance_post[29],\
													reg_mp_lum1_y1,		pp->shp_balance_post[30],\
													reg_mp_lum1_y2,		pp->shp_balance_post[31],\
													reg_mp_lum2_x_l0,	pp->shp_balance_post[32]);
				
				PE_SHP_M17C0_QRd04(shp_mp_ctrl_0b,	reg_mp_lum2_x_l1,	pp->shp_balance_post[33],\
													reg_mp_lum2_x_h0,	pp->shp_balance_post[34],\
													reg_mp_lum2_x_h1,	pp->shp_balance_post[35],\
													reg_mp_lum2_y0,  	pp->shp_balance_post[36]);
				
				PE_SHP_M17C0_QRd02(shp_mp_ctrl_0c,	reg_mp_lum2_y1,		pp->shp_balance_post[37],\
													reg_mp_lum2_y2,		pp->shp_balance_post[38]);
				
				PE_SHP_M17C0_QRd04(shp_sp_ctrl_09,	reg_sp_lum1_x_l0,	pp->shp_balance_post[39],\
													reg_sp_lum1_x_l1,	pp->shp_balance_post[40],\
													reg_sp_lum1_x_h0,	pp->shp_balance_post[41],\
													reg_sp_lum1_x_h1,	pp->shp_balance_post[42]);
				
				PE_SHP_M17C0_QRd04(shp_sp_ctrl_0a,	reg_sp_lum1_y0,		pp->shp_balance_post[43],\
													reg_sp_lum1_y1,		pp->shp_balance_post[44],\
													reg_sp_lum1_y2,		pp->shp_balance_post[45],\
													reg_sp_lum2_x_l0,	pp->shp_balance_post[46]);
				
				PE_SHP_M17C0_QRd04(shp_sp_ctrl_0b,	reg_sp_lum2_x_l1,	pp->shp_balance_post[47],\
													reg_sp_lum2_x_h0,	pp->shp_balance_post[48],\
													reg_sp_lum2_x_h1,	pp->shp_balance_post[49],\
													reg_sp_lum2_y0, 	pp->shp_balance_post[50]);
				PE_SHP_M17C0_QRd02(shp_sp_ctrl_0c,	reg_sp_lum2_y1,		pp->shp_balance_post[51],\
													reg_sp_lum2_y2,		pp->shp_balance_post[52]);


				
				
				PE_SHP_M17C0_QRd04(shp_pti_ctrl_00,		reg_ptiv_enable,		pp->shp_ti_cmn_post[0],\
														reg_ptiv_ti_mode,		pp->shp_ti_cmn_post[1],\
														reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_post[2],\
														reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_post[3]);
				PE_SHP_M17C0_QRd04(shp_pti_ctrl_01,		reg_ptih_enable,		pp->shp_ti_cmn_post[4],\
														reg_ptih_ti_mode,		pp->shp_ti_cmn_post[5],\
														reg_ptih_mm_tap_size,	pp->shp_ti_cmn_post[6],\
														reg_ptih_avg_tap_size,	pp->shp_ti_cmn_post[7]);
				PE_SHP_M17C0_QRd04(shp_sti_ctrl_00,		reg_sti_enable,			pp->shp_ti_cmn_post[8],\
														reg_sti_ti_mode,		pp->shp_ti_cmn_post[9],\
														reg_sti_mm_tap_size,	pp->shp_ti_cmn_post[10],\
														reg_sti_avg_tap_size,	pp->shp_ti_cmn_post[11]);
				PE_SHP_M17C0_QRd03(shp_dp_ctrl_04,		reg_snr_blur_en,		pp->shp_simple_snr_post[0],\
														reg_snr_blur_sel,		pp->shp_simple_snr_post[1],\
														reg_snr_bilateral_th,	pp->shp_simple_snr_post[2]);
				#ifdef PE_SHP_HW_M17C0_CTI_CMN_CHANGE
				PE_DNR0_M17C0_QRd04(cti_ctrl_0,			cti_en,				pp->shp_cti_cmn_post[0],\
														cti_clipping_mode,	pp->shp_cti_cmn_post[2],\
														cti_pre_flt_mode,	pp->shp_cti_cmn_post[3],\
														cti_tap,			pp->shp_cti_cmn_post[4]);
				PE_SHP_M17C0_QRd02(shp_cti_ctrl_00,		reg_cti_en,			pp->shp_cti_cmn_post[5],\
														reg_cti_filter_tap_size,	pp->shp_cti_cmn_post[7]);
				PE_SHP_M17C0_QRd01(shp_cti_ctrl_02,		reg_cti_ycm_en,		pp->shp_cti_cmn_post[6]);
				PE_DNR0_M17C0_QRd01(reg_cti_ctrl_2,	reg_ycm_en,				pp->shp_cti_cmn_post[1]);
				#endif
				PE_SHP_M17C0_QRd01(shp_motion_ctrl_00,	reg_motion_adaptive_en,	pp->shp_motion_post[0]);

				#ifdef PE_SHP_HW_M17C0_CTI_CMN_CHANGE
				PE_SHP_M17C0_QRd02(shp_motion_ctrl_01,	reg_motion_lut_a_y0,	pp->shp_motion_post[1],\
														reg_motion_lut_a_y1,	pp->shp_motion_post[2]);
				PE_SHP_M17C0_QRd02(shp_motion_ctrl_02,	reg_motion_lut_a_y2,	pp->shp_motion_post[3],\
														reg_motion_lut_a_y3,	pp->shp_motion_post[4]);
				/*inkyung.park 20170801,temporally setting for super resolution menu until new DB determined*/
				PE_SHP_M17C0_QRd02(shp_motion_ctrl_03,			reg_motion_lut_t_y0,	pp->shp_motion_post[5],\
																reg_motion_lut_t_y1,	pp->shp_motion_post[6]);
				PE_SHP_M17C0_QRd02(shp_motion_ctrl_04,			reg_motion_lut_t_y2,	pp->shp_motion_post[7],\
																reg_motion_lut_t_y3,	pp->shp_motion_post[8]);
				#else
				PE_SHP_M17C0_QRd04(shp_motion_ctrl_01,	reg_motion_lut_a_y0,	pp->shp_motion_post[5],\
														reg_motion_lut_a_x0,	pp->shp_motion_post[1],\
														reg_motion_lut_a_y1,	pp->shp_motion_post[6],\
														reg_motion_lut_a_x1,	pp->shp_motion_post[2]);
				PE_SHP_M17C0_QRd04(shp_motion_ctrl_02,	reg_motion_lut_a_y2,	pp->shp_motion_post[7],\
														reg_motion_lut_a_x2,	pp->shp_motion_post[3],\
														reg_motion_lut_a_y3,	pp->shp_motion_post[8],\
														reg_motion_lut_a_x3,	pp->shp_motion_post[4]);
				
				PE_SHP_M17C0_QRd03(shp_chroma_ctrl_00,	reg_chr_color_region_en,pp->shp_chroma_post[0],\
														reg_chr_protection_en,	pp->shp_chroma_post[1],\
														reg_chr_compensation_en,pp->shp_chroma_post[2]);
				PE_SHP_M17C0_QRd02(shp_chroma_ctrl_0d,	reg_chr_r0_gain,		pp->shp_chroma_post[3],\
														reg_chr_r1_gain,		pp->shp_chroma_post[4]);
				#endif
			}
			pd = pp->shp_cmn_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : resolution misc ctrl\n"\
			"shp_cmn_post     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_post     [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_post     [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29]);
			pd = pp->shp_map_cmn_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_post [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_post [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_post [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_post [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48]);
			pd = pp->shp_balance_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_balance_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_post [50]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],   pd[4],   pd[5],   pd[6],   pd[7],   pd[8],   pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48],  pd[49], \
				pd[50], pd[51], pd[52]);
			pd = pp->shp_ti_cmn_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_post  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_post  [10]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11]);
			pd = pp->shp_simple_snr_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_simple_snr_post [00]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2]);
			pd = pp->shp_cti_cmn_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_cti_cmn_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[6]);
			
			pd = pp->shp_motion_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :	resolution misc ctrl\n"\
			"shp_motion_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],	pd[1],	pd[2],	pd[3],	pd[4],	pd[5],	pd[6],	pd[7],	pd[8]);
			pd = pp->shp_chroma_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_chroma_post [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4]);
						}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for M17C0
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			UINT8 *pd;
			LX_PE_SHP_EE3_T *pp=(LX_PE_SHP_EE3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ee_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ee_post\n"\
			"shp_ee_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_RES_WR02(shp_coring_ctrl_09,	reg_mpc_gain_e_b,	GET_BITS(pp->shp_ee_post[0],0,7), \
															reg_mpc_gain_e_w,	GET_BITS(pp->shp_ee_post[1],0,7));
				PE_SHP_HW_M17C0_RES_WR02(shp_dp_ctrl_01,		reg_spc_gain_e_b,	GET_BITS(pp->shp_ee_post[2],0,7), \
															reg_spc_gain_e_w,	GET_BITS(pp->shp_ee_post[3],0,7));
				PE_SHP_HW_M17C0_RES_WR02(shp_dp_ctrl_02,		reg_ptic_gain_e_b,	GET_BITS(pp->shp_ee_post[4],0,7), \
															reg_ptic_gain_e_w,	GET_BITS(pp->shp_ee_post[5],0,7));
				PE_SHP_HW_M17C0_RES_WR02(shp_contrast_ctrl_03,reg_lc_gain_e_b,	GET_BITS(pp->shp_ee_post[6],0,7), \
															reg_lc_gain_e_w,	GET_BITS(pp->shp_ee_post[7],0,7));

				#else
				PE_SHP_M17C0_QWr02(shp_coring_ctrl_09,	reg_mpc_gain_e_b,	GET_BITS(pp->shp_ee_post[0],0,7), \
														reg_mpc_gain_e_w,	GET_BITS(pp->shp_ee_post[1],0,7));
				PE_SHP_M17C0_QWr02(shp_dp_ctrl_01,		reg_spc_gain_e_b,	GET_BITS(pp->shp_ee_post[2],0,7), \
														reg_spc_gain_e_w,	GET_BITS(pp->shp_ee_post[3],0,7));
				PE_SHP_M17C0_QWr02(shp_dp_ctrl_02,		reg_ptic_gain_e_b,	GET_BITS(pp->shp_ee_post[4],0,7), \
														reg_ptic_gain_e_w,	GET_BITS(pp->shp_ee_post[5],0,7));
				PE_SHP_M17C0_QWr02(shp_contrast_ctrl_03,reg_lc_gain_e_b,		GET_BITS(pp->shp_ee_post[6],0,7), \
														reg_lc_gain_e_w,	GET_BITS(pp->shp_ee_post[7],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for M17C0
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_SHP_EE3_T *pp=(LX_PE_SHP_EE3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SHP_M17C0_QRd02(shp_coring_ctrl_09,	reg_mpc_gain_e_b,	pp->shp_ee_post[0], \
														reg_mpc_gain_e_w,	pp->shp_ee_post[1]);
				PE_SHP_M17C0_QRd02(shp_dp_ctrl_01,		reg_spc_gain_e_b,	pp->shp_ee_post[2], \
														reg_spc_gain_e_w,	pp->shp_ee_post[3]);
				PE_SHP_M17C0_QRd02(shp_dp_ctrl_02,		reg_ptic_gain_e_b,	pp->shp_ee_post[4], \
														reg_ptic_gain_e_w,	pp->shp_ee_post[5]);
				PE_SHP_M17C0_QRd02(shp_contrast_ctrl_03,	reg_lc_gain_e_b,	pp->shp_ee_post[6], \
														reg_lc_gain_e_w,	pp->shp_ee_post[7]);
			}

			UINT8 *pd = pp->shp_ee_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_ee_post\n"\
			"shp_ee_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7]);
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for M17C0
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_SHP_DE3_T *pp=(LX_PE_SHP_DE3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_de_post;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_de_post\n"\
			"shp_de_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_RES_WR02(shp_coring_ctrl_09,	reg_mpc_gain_t_b,	GET_BITS(pp->shp_de_post[0],0,7), \
															reg_mpc_gain_t_w,	GET_BITS(pp->shp_de_post[1],0,7));
				PE_SHP_HW_M17C0_RES_WR02(shp_dp_ctrl_01,		reg_spc_gain_t_b,	GET_BITS(pp->shp_de_post[2],0,7), \
															reg_spc_gain_t_w,	GET_BITS(pp->shp_de_post[3],0,7));
				PE_SHP_HW_M17C0_RES_WR02(shp_dp_ctrl_02,		reg_ptic_gain_t_b,	GET_BITS(pp->shp_de_post[4],0,7), \
															reg_ptic_gain_t_w,	GET_BITS(pp->shp_de_post[5],0,7));
				PE_SHP_HW_M17C0_RES_WR02(shp_contrast_ctrl_03,reg_lc_gain_t_b,	GET_BITS(pp->shp_de_post[6],0,7), \
															reg_lc_gain_t_w,	GET_BITS(pp->shp_de_post[7],0,7));

				#else
				PE_SHP_M17C0_QWr02(shp_coring_ctrl_09,	reg_mpc_gain_t_b,	GET_BITS(pp->shp_de_post[0],0,7), \
														reg_mpc_gain_t_w,	GET_BITS(pp->shp_de_post[1],0,7));
				PE_SHP_M17C0_QWr02(shp_dp_ctrl_01,		reg_spc_gain_t_b,	GET_BITS(pp->shp_de_post[2],0,7), \
														reg_spc_gain_t_w,	GET_BITS(pp->shp_de_post[3],0,7));
				PE_SHP_M17C0_QWr02(shp_dp_ctrl_02,		reg_ptic_gain_t_b,	GET_BITS(pp->shp_de_post[4],0,7), \
														reg_ptic_gain_t_w,	GET_BITS(pp->shp_de_post[5],0,7));
				PE_SHP_M17C0_QWr02(shp_contrast_ctrl_03,reg_lc_gain_t_b,	GET_BITS(pp->shp_de_post[6],0,7), \
														reg_lc_gain_t_w,	GET_BITS(pp->shp_de_post[7],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for M17C0
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_SHP_DE3_T *pp=(LX_PE_SHP_DE3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SHP_M17C0_QRd02(shp_coring_ctrl_09,	reg_mpc_gain_t_b,	pp->shp_de_post[0], \
														reg_mpc_gain_t_w,	pp->shp_de_post[1]);
				PE_SHP_M17C0_QRd02(shp_dp_ctrl_01,		reg_spc_gain_t_b,	pp->shp_de_post[2], \
														reg_spc_gain_t_w,	pp->shp_de_post[3]);
				PE_SHP_M17C0_QRd02(shp_dp_ctrl_02,		reg_ptic_gain_t_b,	pp->shp_de_post[4], \
														reg_ptic_gain_t_w,	pp->shp_de_post[5]);
				PE_SHP_M17C0_QRd02(shp_contrast_ctrl_03,reg_lc_gain_t_b,	pp->shp_de_post[6], \
														reg_lc_gain_t_w,	pp->shp_de_post[7]);
			
			}
			UINT8 *pd = pp->shp_de_post;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_de_post\n"\
			"shp_de_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7]);
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * set sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetSreReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE3_CMN_T *pp=(LX_PE_SHP_SR_RE3_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_main_pre\n"\
			"shp_ui_main_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_pre     [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_ti_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ti_ui_main_pre\n"\
			"shp_ti_ui_main_pre  [00]0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2]);
			pd = pp->shp_tgen_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_main_pre\n"\
			"shp_tgen_ui_main_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7]);
			

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_contrast_ctrl_02,	reg_lc_lap_weight,		GET_BITS(pp->shp_ui_main_pre[0],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_mp_ctrl_01,		reg_mp_im_os_gain,		GET_BITS(pp->shp_ui_main_pre[1],0,7),\
																reg_mp_im_us_gain,		GET_BITS(pp->shp_ui_main_pre[2],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR06(shp_mp_ctrl_03,		reg_mp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_pre[3],0,4),\
																reg_mp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_pre[4],0,4),\
																reg_mp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_pre[5],0,4),\
																reg_mp_lap_gain_v_7,	GET_BITS(pp->shp_ui_main_pre[6],0,4),\
																reg_mp_lap_gain_v_5,	GET_BITS(pp->shp_ui_main_pre[7],0,4),\
																reg_mp_lap_gain_v_3,	GET_BITS(pp->shp_ui_main_pre[8],0,4));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_sp_ctrl_01,		reg_sp_im_os_gain,		GET_BITS(pp->shp_ui_main_pre[9],0,8),\
																reg_sp_im_us_gain,		GET_BITS(pp->shp_ui_main_pre[10],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_sp_ctrl_03,		reg_sp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_pre[11],0,4),\
																reg_sp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_pre[12],0,4),\
																reg_sp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_pre[13],0,4));

				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_sti_ctrl_00,		reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_pre[0],0,8),\
																reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_pre[1],0,8),\
																reg_sti_texture_gain,   GET_BITS(pp->shp_ti_ui_main_pre[2],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_tgen_ctrl_00,		reg_tgen_master_gain,	GET_BITS(pp->shp_tgen_ui_main_pre[0],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_tgen_ctrl_08,		reg_tgen_gs_noise,		GET_BITS(pp->shp_tgen_ui_main_pre[1],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_tgen_ctrl_06,		reg_tgen_blur_coef_x0,	GET_BITS(pp->shp_tgen_ui_main_pre[2],0,6),\
																reg_tgen_blur_coef_x1,	GET_BITS(pp->shp_tgen_ui_main_pre[3],0,6),\
																reg_tgen_blur_coef_x2,  GET_BITS(pp->shp_tgen_ui_main_pre[4],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_tgen_ctrl_07,		reg_tgen_blur_coef_y0,	GET_BITS(pp->shp_tgen_ui_main_pre[5],0,6),\
																reg_tgen_blur_coef_y1,	GET_BITS(pp->shp_tgen_ui_main_pre[6],0,6),\
																reg_tgen_blur_coef_y2,  GET_BITS(pp->shp_tgen_ui_main_pre[7],0,6));
				

				#else
				PE_SR_SHP_M17C0_QWr01(shp_contrast_ctrl_02,		reg_lc_lap_weight,		GET_BITS(pp->shp_ui_main_pre[0],0,8));
				PE_SR_SHP_M17C0_QWr02(shp_mp_ctrl_01,				reg_mp_im_os_gain,		GET_BITS(pp->shp_ui_main_pre[1],0,7),\
																reg_mp_im_us_gain,		GET_BITS(pp->shp_ui_main_pre[2],0,7));
				PE_SR_SHP_M17C0_QWr06(shp_mp_ctrl_03,				reg_mp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_pre[3],0,4),\
																reg_mp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_pre[4],0,4),\
																reg_mp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_pre[5],0,4),\
																reg_mp_lap_gain_v_7,	GET_BITS(pp->shp_ui_main_pre[6],0,4),\
																reg_mp_lap_gain_v_5,	GET_BITS(pp->shp_ui_main_pre[7],0,4),\
																reg_mp_lap_gain_v_3,	GET_BITS(pp->shp_ui_main_pre[8],0,4));
				PE_SR_SHP_M17C0_QWr02(shp_sp_ctrl_01,				reg_sp_im_os_gain,		GET_BITS(pp->shp_ui_main_pre[9],0,8),\
																reg_sp_im_us_gain,		GET_BITS(pp->shp_ui_main_pre[10],0,8));
				PE_SR_SHP_M17C0_QWr03(shp_sp_ctrl_03,				reg_sp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_pre[11],0,4),\
																reg_sp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_pre[12],0,4),\
																reg_sp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_pre[13],0,4));
				
				PE_SR_SHP_M17C0_QWr03(shp_sti_ctrl_00, 			reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_pre[0],0,8),\
																reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_pre[1],0,8),\
																reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_pre[2],0,8));
				
				PE_SR_SHP_M17C0_QWr01(shp_tgen_ctrl_00,			reg_tgen_master_gain,	GET_BITS(pp->shp_tgen_ui_main_pre[0],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_tgen_ctrl_08,			reg_tgen_gs_noise,		GET_BITS(pp->shp_tgen_ui_main_pre[1],0,6));
				PE_SR_SHP_M17C0_QWr03(shp_tgen_ctrl_06,			reg_tgen_blur_coef_x0,	GET_BITS(pp->shp_tgen_ui_main_pre[2],0,6),\
																reg_tgen_blur_coef_x1,	GET_BITS(pp->shp_tgen_ui_main_pre[3],0,6),\
																reg_tgen_blur_coef_x2,  GET_BITS(pp->shp_tgen_ui_main_pre[4],0,6));
				PE_SR_SHP_M17C0_QWr03(shp_tgen_ctrl_07,			reg_tgen_blur_coef_y0,	GET_BITS(pp->shp_tgen_ui_main_pre[5],0,6),\
																reg_tgen_blur_coef_y1,	GET_BITS(pp->shp_tgen_ui_main_pre[6],0,6),\
																reg_tgen_blur_coef_y2,  GET_BITS(pp->shp_tgen_ui_main_pre[7],0,6));
				#endif
			}
		}
		#else
		{
			LX_PE_SHP_SR_RE2_CMN_T *pp=(LX_PE_SHP_SR_RE2_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_main_pre\n"\
			"shp_ui_main_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_pre     [10]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
			pd[10], pd[11], pd[12]);
			pd = pp->shp_ti_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ti_ui_main_pre\n"\
			"shp_ti_ui_main_pre  [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2]);
			pd = pp->shp_tgen_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_tgen_ui_main_pre\n"\
			"shp_tgen_ui_main_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SR_SHP_M17C0_QWr02(shp_mp_ctrl_01,reg_mp_im_os_gain,		GET_BITS(pp->shp_ui_main_pre[0],0,7),\
                                                   reg_mp_im_us_gain,		GET_BITS(pp->shp_ui_main_pre[1],0,7));
				PE_SR_SHP_M17C0_QWr03(shp_mp_ctrl_03,reg_mp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_pre[2],0,4),\
                                                   reg_mp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_pre[3],0,4),\
													reg_mp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_pre[4],0,4));
				PE_SR_SHP_M17C0_QWr03(shp_mp_ctrl_03,reg_mp_lap_gain_v_7,	GET_BITS(pp->shp_ui_main_pre[5],0,4),\
                                                    reg_mp_lap_gain_v_5,	GET_BITS(pp->shp_ui_main_pre[6],0,4),\
													reg_mp_lap_gain_v_3,	GET_BITS(pp->shp_ui_main_pre[7],0,4));
				PE_SR_SHP_M17C0_QWr02(shp_sp_ctrl_01,reg_sp_im_os_gain,		GET_BITS(pp->shp_ui_main_pre[8],0,7),\
                                                    reg_sp_im_us_gain,		GET_BITS(pp->shp_ui_main_pre[9],0,7));
				PE_SR_SHP_M17C0_QWr03(shp_sp_ctrl_03,reg_sp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_pre[10],0,4),\
                                                    reg_sp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_pre[11],0,4),\
													reg_sp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_pre[12],0,4));

				PE_SR_SHP_M17C0_QWr03(shp_sti_ctrl_00,reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_pre[0],0,8),\
                                                     reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_pre[1],0,8),\
													 reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_pre[2],0,8));
				
				PE_SR_SHP_M17C0_QWr04(shp_tgen_ctrl_08,reg_tgen_map_edge_gain,		GET_BITS(pp->shp_tgen_ui_main_pre[0],0,5),\
                                                      reg_tgen_map_detail_gain,	GET_BITS(pp->shp_tgen_ui_main_pre[1],0,5),\
                                                      reg_tgen_map_offset,		GET_BITS(pp->shp_tgen_ui_main_pre[2],0,8),\
													  reg_tgen_gs_noise,			GET_BITS(pp->shp_tgen_ui_main_pre[3],0,6));
				PE_SR_SHP_M17C0_QWr03(shp_tgen_ctrl_06,reg_tgen_blur_coef_x0,		GET_BITS(pp->shp_tgen_ui_main_pre[4],0,6),\
                                                      reg_tgen_blur_coef_x1,		GET_BITS(pp->shp_tgen_ui_main_pre[5],0,6),\
													  reg_tgen_blur_coef_x2,		GET_BITS(pp->shp_tgen_ui_main_pre[6],0,6));
				PE_SR_SHP_M17C0_QWr03(shp_tgen_ctrl_07,reg_tgen_blur_coef_y0,		GET_BITS(pp->shp_tgen_ui_main_pre[7],0,6),\
                                                      reg_tgen_blur_coef_y1,		GET_BITS(pp->shp_tgen_ui_main_pre[8],0,6),\
													  reg_tgen_blur_coef_y2,		GET_BITS(pp->shp_tgen_ui_main_pre[9],0,6));
				#else
				
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_mp_ctrl_01,reg_mp_im_os_gain,		GET_BITS(pp->shp_ui_main_pre[0],0,7),\
                                                    	 reg_mp_im_us_gain,		GET_BITS(pp->shp_ui_main_pre[1],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_mp_ctrl_03,reg_mp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_pre[2],0,4),\
                                                    	 reg_mp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_pre[3],0,4),\
														 reg_lap_mp_gain_h_3,	GET_BITS(pp->shp_ui_main_pre[4],0,4));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_mp_ctrl_03,reg_mp_lap_gain_v_7,	GET_BITS(pp->shp_ui_main_pre[5],0,4),\
                                                    	 reg_mp_lap_gain_v_5,	GET_BITS(pp->shp_ui_main_pre[6],0,4),\
														 reg_mp_lap_gain_v_3,	GET_BITS(pp->shp_ui_main_pre[7],0,4));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_sp_ctrl_01,reg_sp_im_os_gain,		GET_BITS(pp->shp_ui_main_pre[8],0,7),\
                                                    reg_sp_im_us_gain,		GET_BITS(pp->shp_ui_main_pre[9],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_sp_ctrl_03,reg_sp_lap_gain_h_7,	GET_BITS(pp->shp_ui_main_pre[10],0,4),\
                                                    reg_sp_lap_gain_h_5,	GET_BITS(pp->shp_ui_main_pre[11],0,4),\
													reg_sp_lap_gain_h_3,	GET_BITS(pp->shp_ui_main_pre[12],0,4));

				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_sti_ctrl_00,reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_pre[0],0,8),\
                                                     reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_pre[1],0,8),\
													 reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_pre[2],0,8));
				
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_tgen_ctrl_08,reg_tgen_map_edge_gain,		GET_BITS(pp->shp_tgen_ui_main_pre[0],0,5),\
                                                      reg_tgen_map_detail_gain,	GET_BITS(pp->shp_tgen_ui_main_pre[1],0,5),\
                                                      reg_tgen_map_offset,		GET_BITS(pp->shp_tgen_ui_main_pre[2],0,8),\
													  reg_tgen_gs_noise,			GET_BITS(pp->shp_tgen_ui_main_pre[3],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_tgen_ctrl_06,reg_tgen_blur_coef_x0,		GET_BITS(pp->shp_tgen_ui_main_pre[4],0,6),\
                                                      reg_tgen_blur_coef_x1,		GET_BITS(pp->shp_tgen_ui_main_pre[5],0,6),\
													  reg_tgen_blur_coef_x2,		GET_BITS(pp->shp_tgen_ui_main_pre[6],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_tgen_ctrl_07,tg_blur_coef_y0,		GET_BITS(pp->shp_tgen_ui_main_pre[7],0,6),\
                                                      reg_tgen_blur_coef_y1,		GET_BITS(pp->shp_tgen_ui_main_pre[8],0,6),\
													  reg_tgen_blur_coef_y2,		GET_BITS(pp->shp_tgen_ui_main_pre[9],0,6));
				#endif
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetSreReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE3_CMN_T *pp=(LX_PE_SHP_SR_RE3_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_SHP_M17C0_QRd01(shp_contrast_ctrl_02,		reg_lc_lap_weight,		pp->shp_ui_main_pre[0]);
				PE_SR_SHP_M17C0_QRd02(shp_mp_ctrl_01,				reg_mp_im_os_gain,		pp->shp_ui_main_pre[1],\
																reg_mp_im_us_gain,		pp->shp_ui_main_pre[2]);
				PE_SR_SHP_M17C0_QRd06(shp_mp_ctrl_03,				reg_mp_lap_gain_h_7,	pp->shp_ui_main_pre[3],\
																reg_mp_lap_gain_h_5,	pp->shp_ui_main_pre[4],\
																reg_mp_lap_gain_h_3,	pp->shp_ui_main_pre[5],\
																reg_mp_lap_gain_v_7,	pp->shp_ui_main_pre[6],\
																reg_mp_lap_gain_v_5,	pp->shp_ui_main_pre[7],\
																reg_mp_lap_gain_v_3,	pp->shp_ui_main_pre[8]);
				PE_SR_SHP_M17C0_QRd02(shp_sp_ctrl_01,				reg_sp_im_os_gain,		pp->shp_ui_main_pre[9],\
																reg_sp_im_us_gain,		pp->shp_ui_main_pre[10]);
				PE_SR_SHP_M17C0_QRd03(shp_sp_ctrl_03,				reg_sp_lap_gain_h_7,	pp->shp_ui_main_pre[11],\
																reg_sp_lap_gain_h_5,	pp->shp_ui_main_pre[12],\
																reg_sp_lap_gain_h_3,	pp->shp_ui_main_pre[13]);
				
				PE_SR_SHP_M17C0_QRd03(shp_sti_ctrl_00, 			reg_sti_master_gain,	pp->shp_ti_ui_main_pre[0],\
																reg_sti_edge_gain,		pp->shp_ti_ui_main_pre[1],\
																reg_sti_texture_gain,	pp->shp_ti_ui_main_pre[2]);
				
				PE_SR_SHP_M17C0_QRd01(shp_tgen_ctrl_00,			reg_tgen_master_gain,	pp->shp_tgen_ui_main_pre[0]);
				PE_SR_SHP_M17C0_QRd01(shp_tgen_ctrl_08,			reg_tgen_gs_noise,		pp->shp_tgen_ui_main_pre[1]);
				PE_SR_SHP_M17C0_QRd03(shp_tgen_ctrl_06,			reg_tgen_blur_coef_x0,	pp->shp_tgen_ui_main_pre[2],\
																reg_tgen_blur_coef_x1,	pp->shp_tgen_ui_main_pre[3],\
																reg_tgen_blur_coef_x2,  pp->shp_tgen_ui_main_pre[4]);
				PE_SR_SHP_M17C0_QRd03(shp_tgen_ctrl_07,			reg_tgen_blur_coef_y0,	pp->shp_tgen_ui_main_pre[5],\
																reg_tgen_blur_coef_y1,	pp->shp_tgen_ui_main_pre[6],\
																reg_tgen_blur_coef_y2,  pp->shp_tgen_ui_main_pre[7]);
				pd = pp->shp_ui_main_pre;
				PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_ui_main_pre\n"\
				"shp_ui_main_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_pre     [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12], pd[13]);
				pd = pp->shp_ti_ui_main_pre;
				PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_ti_ui_main_pre\n"\
				"shp_ti_ui_main_pre  [00]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2]);
				pd = pp->shp_tgen_ui_main_pre;
				PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_ui_main_pre\n"\
				"shp_ui_main_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7]);
			}
		}
		#else
		{
			LX_PE_SHP_SR_RE2_CMN_T *pp=(LX_PE_SHP_SR_RE2_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_SHP_M17C0_QRd02(shp_mp_ctrl_01,		reg_mp_im_os_gain,		pp->shp_ui_main_pre[0],\
                                                    	reg_mp_im_us_gain,		pp->shp_ui_main_pre[1]);
				PE_SR_SHP_M17C0_QRd03(shp_mp_ctrl_03,		reg_mp_lap_gain_h_7,	pp->shp_ui_main_pre[2],\
                                                    	reg_mp_lap_gain_h_5,	pp->shp_ui_main_pre[3],\
														reg_mp_lap_gain_h_3,	pp->shp_ui_main_pre[4]);
				PE_SR_SHP_M17C0_QRd03(shp_mp_ctrl_03,		reg_mp_lap_gain_v_7,	pp->shp_ui_main_pre[5],\
                                                    	reg_mp_lap_gain_v_5,	pp->shp_ui_main_pre[6],\
														reg_mp_lap_gain_v_3,	pp->shp_ui_main_pre[7]);
				PE_SR_SHP_M17C0_QRd02(shp_sp_ctrl_01,		reg_sp_im_os_gain,		pp->shp_ui_main_pre[8],\
                                                    	reg_sp_im_us_gain,		pp->shp_ui_main_pre[9]);
				PE_SR_SHP_M17C0_QRd03(shp_sp_ctrl_03,		reg_sp_lap_gain_h_7,	pp->shp_ui_main_pre[10],\
                                                    	reg_sp_lap_gain_h_5,	pp->shp_ui_main_pre[11],\
														reg_sp_lap_gain_h_3,	pp->shp_ui_main_pre[12]);

				PE_SR_SHP_M17C0_QRd03(shp_sti_ctrl_00,	reg_sti_master_gain,	pp->shp_ti_ui_main_pre[0],\
                                                     	reg_sti_edge_gain,		pp->shp_ti_ui_main_pre[1],\
													 	reg_sti_texture_gain,	pp->shp_ti_ui_main_pre[2]);
				
				PE_SR_SHP_M17C0_QRd04(shp_tgen_ctrl_08,	reg_tgen_map_edge_gain,	pp->shp_tgen_ui_main_pre[0],\
                                                      	reg_tgen_map_detail_gain,	pp->shp_tgen_ui_main_pre[1],\
                                                      	reg_tgen_map_offset,		pp->shp_tgen_ui_main_pre[2],\
													  	reg_tgen_gs_noise,		pp->shp_tgen_ui_main_pre[3]);
				PE_SR_SHP_M17C0_QRd03(shp_tgen_ctrl_06,	reg_tgen_blur_coef_x0,	pp->shp_tgen_ui_main_pre[4],\
                                                      	reg_tgen_blur_coef_x1,	pp->shp_tgen_ui_main_pre[5],\
													  	reg_tgen_blur_coef_x2,	pp->shp_tgen_ui_main_pre[6]);
				PE_SR_SHP_M17C0_QRd03(shp_tgen_ctrl_07,	reg_tgen_blur_coef_y0,	pp->shp_tgen_ui_main_pre[7],\
                                                      	reg_tgen_blur_coef_y1,	pp->shp_tgen_ui_main_pre[8],\
													  	reg_tgen_blur_coef_y2,	pp->shp_tgen_ui_main_pre[9]);
			}
			{
			UINT8 *pd = pp->shp_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_main_pre\n"\
			"shp_ui_main_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_pre     [10]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
			pd[10], pd[11], pd[12]);
			pd = pp->shp_ti_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ti_ui_main_pre\n"\
			"shp_ti_ui_main_pre  [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2]);
			pd = pp->shp_tgen_ui_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_tgen_ui_main_pre\n"\
			"shp_tgen_ui_main_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9]);
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetSreReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE3_HOR_T *pp=(LX_PE_SHP_SR_RE3_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_h_main_pre\n"\
			"shp_ui_h_main_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_derh_ctrl_05,	reg_derh_csft_gain,			GET_BITS(pp->shp_ui_h_main_pre[0],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_derh_ctrl_06,	reg_derh_bflt_tap_size,		GET_BITS(pp->shp_ui_h_main_pre[1],0,3),\
															reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_pre[2],0,6),\
															reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_pre[3],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_pre[4],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_pre[5],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_pti_ctrl_01, 	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_pre[6],0,8));
				#else
				PE_SR_SHP_M17C0_QWr01(shp_derh_ctrl_05,	reg_derh_csft_gain,				GET_BITS(pp->shp_ui_h_main_pre[0],0,6));
				PE_SR_SHP_M17C0_QWr03(shp_derh_ctrl_06,	reg_derh_bflt_tap_size,			GET_BITS(pp->shp_ui_h_main_pre[1],0,3),\
														reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main_pre[2],0,6),\
														reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main_pre[3],0,6));
				PE_SR_SHP_M17C0_QWr01(shp_mp_ctrl_01,		reg_mp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_pre[4],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_sp_ctrl_01,		reg_sp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_pre[5],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_pti_ctrl_01,	reg_ptih_master_gain,			GET_BITS(pp->shp_ui_h_main_pre[6],0,8));
				#endif
			}
		}
		#else 
		{
			LX_PE_SHP_SR_RE2_HOR_T *pp=(LX_PE_SHP_SR_RE2_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_ui_h_main;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_h_main_post\n"\
			"shp_ui_h_main_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_h_main_post[10]0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
			pd[10], pd[11]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SR_SHP_M17C0_QWr01(shp_derh_ctrl_05,	reg_derh_csft_gain,		GET_BITS(pp->shp_ui_h_main[0],0,6));
				PE_SR_SHP_M17C0_QWr03(shp_derh_ctrl_06,	reg_derh_bflt_tap_size,		GET_BITS(pp->shp_ui_h_main[1],0,3),\
														reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main[2],0,6),\
														reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main[3],0,6));
				PE_SR_SHP_M17C0_QWr01(shp_mp_ctrl_01, reg_mp_im_gain_h,GET_BITS(pp->shp_ui_h_main[5],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_sp_ctrl_01, reg_sp_im_gain_h,GET_BITS(pp->shp_ui_h_main[6],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_pti_ctrl_01,reg_ptih_master_gain,GET_BITS(pp->shp_ui_h_main[7],0,8));
				#else
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_derh_ctrl_05,	reg_derh_csft_gain,		GET_BITS(pp->shp_ui_h_main[0],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_derh_ctrl_06,	reg_derh_bflt_tap_size,		GET_BITS(pp->shp_ui_h_main[1],0,3),\
															reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main[2],0,6),\
															reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main[3],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,GET_BITS(pp->shp_ui_h_main[5],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,GET_BITS(pp->shp_ui_h_main[6],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_pti_ctrl_01,	reg_ptih_master_gain,GET_BITS(pp->shp_ui_h_main[7],0,8));
				#endif
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetSreReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;

	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			LX_PE_SHP_RE4_HOR_T *pp = (LX_PE_SHP_RE4_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			PE_SR_SHP_M17C0_QRd01(shp_derh_ctrl_05,	reg_derh_csft_gain, 			pp->shp_ui_h_main_post[0]);
			PE_SR_SHP_M17C0_QRd03(shp_derh_ctrl_06,	reg_derh_bflt_tap_size, 		pp->shp_ui_h_main_post[1],\
													reg_derh_edge_filter_gain_w,	pp->shp_ui_h_main_post[2],\
													reg_derh_edge_filter_gain_b,	pp->shp_ui_h_main_post[3]);
			PE_SR_SHP_M17C0_QRd01(shp_mp_ctrl_01,		reg_mp_im_gain_h,				pp->shp_ui_h_main_post[4]);
			PE_SR_SHP_M17C0_QRd01(shp_sp_ctrl_01,		reg_sp_im_gain_h,				pp->shp_ui_h_main_post[5]);
			PE_SR_SHP_M17C0_QRd01(shp_pti_ctrl_01,	reg_ptih_master_gain,			pp->shp_ui_h_main_post[6]);
			
		}
		#else 
		{
			LX_PE_SHP_SR_RE2_HOR_T *pp=(LX_PE_SHP_SR_RE2_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_SHP_M17C0_QRd01(shp_derh_ctrl_05,	reg_derh_csft_gain,			pp->shp_ui_h_main[0]);
				PE_SR_SHP_M17C0_QRd03(shp_derh_ctrl_06,	reg_derh_bflt_tap_size,			pp->shp_ui_h_main[1],\
														reg_derh_edge_filter_gain_w,	pp->shp_ui_h_main[2],\
														reg_derh_edge_filter_gain_b,	pp->shp_ui_h_main[3]);
				PE_SR_SHP_M17C0_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			pp->shp_ui_h_main[5]);
				PE_SR_SHP_M17C0_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			pp->shp_ui_h_main[6]);
				PE_SR_SHP_M17C0_QRd01(shp_pti_ctrl_01,	reg_ptih_master_gain,		pp->shp_ui_h_main[7]);
			}
			{
			UINT8 *pd = pp->shp_ui_h_main;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_h_main_post\n"\
			"shp_ui_h_main_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_h_main_post[10]0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
			pd[10], pd[11]);
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetSreReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			LX_PE_SHP_SR_RE3_VER_T *pp=(LX_PE_SHP_SR_RE3_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_ui_v_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_v_main_pre\n"\
			"shp_ui_v_main_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id,	pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_derv_ctrl_0,	reg_derv_en,			GET_BITS(pp->shp_ui_v_main_pre[0],0,1));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_derv_ctrl_1,	reg_derv_csft_gain,		GET_BITS(pp->shp_ui_v_main_pre[1],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_derv_ctrl_3,	reg_derv_gain_b,		GET_BITS(pp->shp_ui_v_main_pre[2],0,7),\
															reg_derv_gain_w,		GET_BITS(pp->shp_ui_v_main_pre[3],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_pre[4],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_pre[5],0,8));
				#else
				PE_SR_SHP_M17C0_QWr01(shp_derv_ctrl_0,	reg_derv_en,			GET_BITS(pp->shp_ui_v_main_pre[0],0,1));
				PE_SR_SHP_M17C0_QWr01(shp_derv_ctrl_1,	reg_derv_csft_gain,		GET_BITS(pp->shp_ui_v_main_pre[1],0,6));
				PE_SR_SHP_M17C0_QWr02(shp_derv_ctrl_3,	reg_derv_gain_b,		GET_BITS(pp->shp_ui_v_main_pre[2],0,7),\
														reg_derv_gain_w,		GET_BITS(pp->shp_ui_v_main_pre[3],0,7));
				PE_SR_SHP_M17C0_QWr01(shp_mp_ctrl_01,		reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_pre[4],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_pre[5],0,8));
				#endif
			}
		}
		#else
		{
			LX_PE_SHP_SR_RE2_VER_T *pp=(LX_PE_SHP_SR_RE2_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_ui_v_main;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_v_main_post\n"\
			"shp_ui_v_main_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
			#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SR_SHP_M17C0_QWr01(shp_derv_ctrl_1,	reg_derv_csft_gain,		GET_BITS(pp->shp_ui_v_main[0],0,6));
				PE_SR_SHP_M17C0_QWr02(shp_derv_ctrl_3,	reg_derv_gain_b,			GET_BITS(pp->shp_ui_v_main[1],0,7),\
														reg_derv_gain_w,		 	GET_BITS(pp->shp_ui_v_main[2],0,7));
				PE_SR_SHP_M17C0_QWr01(shp_mp_ctrl_01,		reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_v_main[4],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,GET_BITS(pp->shp_ui_v_main[5],0,8));
			#else
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_derv_ctrl_1,	reg_derv_csft_gain,		GET_BITS(pp->shp_ui_v_main[0],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_derv_ctrl_3,	reg_derv_gain_b,		GET_BITS(pp->shp_ui_v_main[1],0,7),\
															reg_derv_gain_w,		 GET_BITS(pp->shp_ui_v_main[2],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_v_main[4],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,GET_BITS(pp->shp_ui_v_main[5],0,8));
			#endif
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetSreReVerCtrl(void *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			LX_PE_SHP_SR_RE3_VER_T *pp=(LX_PE_SHP_SR_RE3_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_SHP_M17C0_QRd01(shp_derv_ctrl_0,	reg_derv_en,			pp->shp_ui_v_main_pre[0]);
				PE_SR_SHP_M17C0_QRd01(shp_derv_ctrl_1,	reg_derv_csft_gain,		pp->shp_ui_v_main_pre[1]);
				PE_SR_SHP_M17C0_QRd02(shp_derv_ctrl_3,	reg_derv_gain_b,		pp->shp_ui_v_main_pre[2],\
													reg_derv_gain_w,		pp->shp_ui_v_main_pre[3]);
				PE_SR_SHP_M17C0_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		pp->shp_ui_v_main_pre[4]);
				PE_SR_SHP_M17C0_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	pp->shp_ui_v_main_pre[5]);
			}
			UINT8 *pd = pp->shp_ui_v_main_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_v_main_pre\n"\
			"shp_ui_v_main_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id,	pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
		}
		#else
		{
			LX_PE_SHP_SR_RE2_VER_T *pp=(LX_PE_SHP_SR_RE2_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{

				PE_SR_SHP_M17C0_QRd01(shp_derv_ctrl_1,	reg_derv_csft_gain,		pp->shp_ui_v_main[0]);
				PE_SR_SHP_M17C0_QRd02(shp_derv_ctrl_3,	reg_derv_gain_b,			pp->shp_ui_v_main[1],\
														reg_derv_gain_w,		 	pp->shp_ui_v_main[2]);
				PE_SR_SHP_M17C0_QRd01(shp_mp_ctrl_01,		reg_mp_im_gain_v,	pp->shp_ui_v_main[4]);
				PE_SR_SHP_M17C0_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,pp->shp_ui_v_main[5]);
			}
			{
			UINT8 *pd = pp->shp_ui_v_main;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ui_v_main_post\n"\
			"shp_ui_v_main_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetSreReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{ 
			UINT8 *pd;
			LX_PE_SHP_SR_RE3_MISC_T *pp=(LX_PE_SHP_SR_RE3_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_cmn_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : resolution misc ctrl\n"\
			"shp_cmn_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_pre     [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_pre     [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29]);
			pd = pp->shp_map_cmn_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48]);
			pd = pp->shp_balance_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_balance_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [50]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],   pd[4],   pd[5],   pd[6],   pd[7],   pd[8],   pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48],  pd[49], \
				pd[50], pd[51], pd[52]);
			pd = pp->shp_ti_cmn_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_pre  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_pre  [10]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11]);
			pd = pp->shp_tgen_cmn_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : resolution misc ctrl\n"\
			"shp_tgen_cmn_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_tgen_cmn_pre[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_tgen_cmn_pre[20]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_derh_ctrl_06,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_pre[0],0,1));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_dp_ctrl_05,	reg_der_x0,					GET_BITS(pp->shp_cmn_pre[1],0,8),\
															reg_der_x1,		 			GET_BITS(pp->shp_cmn_pre[2],0,8),\
															reg_der_y0,					GET_BITS(pp->shp_cmn_pre[5],0,8),\
															reg_der_y1,		 			GET_BITS(pp->shp_cmn_pre[6],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_dp_ctrl_06,	reg_der_x2,					GET_BITS(pp->shp_cmn_pre[3],0,8),\
															reg_der_x3,		 			GET_BITS(pp->shp_cmn_pre[4],0,8),\
															reg_der_y2,					GET_BITS(pp->shp_cmn_pre[7],0,8),\
															reg_der_y3,		 			GET_BITS(pp->shp_cmn_pre[8],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,				GET_BITS(pp->shp_cmn_pre[9],0,1));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,				GET_BITS(pp->shp_cmn_pre[10],0,1));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_mp_ctrl_02,	reg_mp_lap_weight,			GET_BITS(pp->shp_cmn_pre[11],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_sp_ctrl_02,	reg_sp_lap_weight,			GET_BITS(pp->shp_cmn_pre[12],0,8));\
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_derh_ctrl_07,	reg_derh_flat_filter_en,	GET_BITS(pp->shp_cmn_pre[13],0,1),\
															reg_derh_flat_filter_type,	GET_BITS(pp->shp_cmn_pre[14],0,1),\
															reg_derh_flat_filter_gain,	GET_BITS(pp->shp_cmn_pre[15],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR06(shp_dj_ctrl_00,	reg_dj_edf_en,				GET_BITS(pp->shp_cmn_pre[16],0,1),\
															reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_cmn_pre[17],0,1),\
															reg_dj_center_blur_mode,	GET_BITS(pp->shp_cmn_pre[20],0,2),\
															reg_dj_count_diff_th,		GET_BITS(pp->shp_cmn_pre[21],0,5),\
															reg_dj_n_avg_mode,		 	GET_BITS(pp->shp_cmn_pre[22],0,1),\
														reg_dj_line_variation_diff_th,	GET_BITS(pp->shp_cmn_pre[23],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_dj_ctrl_03,	reg_dj_edge_min,			GET_BITS(pp->shp_cmn_pre[18],0,8),\
															reg_dj_edge_mul,			GET_BITS(pp->shp_cmn_pre[19],0,8),\
															reg_dj_g1_protect_min,		GET_BITS(pp->shp_cmn_pre[28],0,8),\
															reg_dj_g1_mul,				GET_BITS(pp->shp_cmn_pre[29],0,7));

				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dj_ctrl_01,	reg_dj_level_th,			GET_BITS(pp->shp_cmn_pre[24],0,8),\
															reg_dj_n_avg_gain,			GET_BITS(pp->shp_cmn_pre[25],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dj_ctrl_02,	reg_dj_g0_cnt_min,			GET_BITS(pp->shp_cmn_pre[26],0,5),\
															reg_dj_g0_mul,				GET_BITS(pp->shp_cmn_pre[27],0,5));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_00,reg_fd_cross_th,			GET_BITS(pp->shp_map_cmn_pre[0],0,8),\
															reg_fd_pre_a_map_h_size,	GET_BITS(pp->shp_map_cmn_pre[14],0,3),\
															reg_fd_pre_a_map_v_size,	GET_BITS(pp->shp_map_cmn_pre[15],0,2),\
															reg_fd_pre_a_cut_resolution,GET_BITS(pp->shp_map_cmn_pre[16],0,3));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_00,reg_fd_a_map_h_size,		GET_BITS(pp->shp_map_cmn_pre[17],0,2),\
															reg_fd_a_nomalize_en,		GET_BITS(pp->shp_map_cmn_pre[18],0,1),\
															reg_fd_t_cut_resolution,	GET_BITS(pp->shp_map_cmn_pre[33],0,2),\
															reg_fd_t_nomalize_en,		GET_BITS(pp->shp_map_cmn_pre[34],0,1));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_coring_ctrl_08,reg_fd_mul_base_t,			GET_BITS(pp->shp_map_cmn_pre[1],0,8),\
															reg_fd_mul_base_e,			GET_BITS(pp->shp_map_cmn_pre[2],0,8));			
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_mnr_ctrl_00,	reg_fd_mnr_gain_e_en,		GET_BITS(pp->shp_map_cmn_pre[3],0,1),\
															reg_fd_mnr_gain_t_en,		GET_BITS(pp->shp_map_cmn_pre[4],0,1),\
															reg_fd_mnr_s1_h_expand,		GET_BITS(pp->shp_map_cmn_pre[5],0,2));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_mnr_ctrl_01,	reg_fd_mnr_s1_mmd_min  ,GET_BITS(pp->shp_map_cmn_pre[6],0,8),\
															reg_fd_mnr_s2_ratio_min,GET_BITS(pp->shp_map_cmn_pre[7],0,8),\
															reg_fd_mnr_s2_ratio_max,GET_BITS(pp->shp_map_cmn_pre[8],0,8),\
															reg_fd_mnr_s2_mmd_min,  GET_BITS(pp->shp_map_cmn_pre[9],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_mnr_ctrl_02,	reg_fd_gain_x0,			GET_BITS(pp->shp_map_cmn_pre[10],0,8),\
															reg_fd_gain_x1,			GET_BITS(pp->shp_map_cmn_pre[11],0,8),\
															reg_fd_gain_y0,			GET_BITS(pp->shp_map_cmn_pre[12],0,8),\
															reg_fd_gain_y1,			GET_BITS(pp->shp_map_cmn_pre[13],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_01,reg_fd_detail_beta_mul,GET_BITS(pp->shp_map_cmn_pre[36],0,8),\
															reg_fd_detail_alpha_mul,GET_BITS(pp->shp_map_cmn_pre[35],0,8),\
															reg_fd_edge_beta_mul,   GET_BITS(pp->shp_map_cmn_pre[20],0,8),\
															reg_fd_edge_alpha_mul,  GET_BITS(pp->shp_map_cmn_pre[19],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_02,reg_fd_a_lut_edge_x0,	GET_BITS(pp->shp_map_cmn_pre[21],0,8),\
															reg_fd_a_lut_edge_y0,	GET_BITS(pp->shp_map_cmn_pre[22],0,8),\
															reg_fd_a_lut_edge_x1,	GET_BITS(pp->shp_map_cmn_pre[23],0,8),\
															reg_fd_a_lut_edge_y1,	GET_BITS(pp->shp_map_cmn_pre[24],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_03,reg_fd_a_lut_detail_x0,GET_BITS(pp->shp_map_cmn_pre[25],0,8),\
															reg_fd_a_lut_detail_y0,	GET_BITS(pp->shp_map_cmn_pre[26],0,8),\
															reg_fd_a_lut_detail_x1,	GET_BITS(pp->shp_map_cmn_pre[27],0,8),\
															reg_fd_a_lut_detail_y1,	GET_BITS(pp->shp_map_cmn_pre[28],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_06,reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_pre[29],0,8),\
															reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_pre[30],0,8),\
															reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_pre[31],0,8),\
															reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_pre[32],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_04,reg_fd_t_lut_edge_x0,	GET_BITS(pp->shp_map_cmn_pre[37],0,8),\
															reg_fd_t_lut_edge_y0,	GET_BITS(pp->shp_map_cmn_pre[38],0,8),\
															reg_fd_t_lut_edge_x1,	GET_BITS(pp->shp_map_cmn_pre[39],0,8),\
															reg_fd_t_lut_edge_y1,	GET_BITS(pp->shp_map_cmn_pre[40],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_05,reg_fd_t_lut_detail_x0,GET_BITS(pp->shp_map_cmn_pre[41],0,8),\
															reg_fd_t_lut_detail_y0,	GET_BITS(pp->shp_map_cmn_pre[42],0,8),\
															reg_fd_t_lut_detail_x1,	GET_BITS(pp->shp_map_cmn_pre[43],0,8),\
															reg_fd_t_lut_detail_y1,	GET_BITS(pp->shp_map_cmn_pre[44],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_coring_ctrl_07,reg_fd_detail_minmax_x0,GET_BITS(pp->shp_map_cmn_pre[45],0,8),\
															reg_fd_detail_minmax_y0,GET_BITS(pp->shp_map_cmn_pre[46],0,8),\
															reg_fd_detail_minmax_x1,GET_BITS(pp->shp_map_cmn_pre[47],0,8),\
															reg_fd_detail_minmax_y1,GET_BITS(pp->shp_map_cmn_pre[48],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_mp_ctrl_07,	reg_mp_gb_en,			GET_BITS(pp->shp_balance_pre[0],0,1),\
															reg_mp_gb_mode,			GET_BITS(pp->shp_balance_pre[1],0,1),\
															reg_mp_gb_x1,			GET_BITS(pp->shp_balance_pre[2],0,8),\
															reg_mp_gb_y1,			GET_BITS(pp->shp_balance_pre[4],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_mp_ctrl_08,	reg_mp_gb_x2,			GET_BITS(pp->shp_balance_pre[3],0,8),\
															reg_mp_gb_y2,			GET_BITS(pp->shp_balance_pre[5],0,8),\
															reg_mp_gb_y3,			GET_BITS(pp->shp_balance_pre[6],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_sp_ctrl_07,	reg_sp_gb_en,			GET_BITS(pp->shp_balance_pre[7],0,1),\
															reg_sp_gb_mode,			GET_BITS(pp->shp_balance_pre[8],0,1),\
															reg_sp_gb_x1,			GET_BITS(pp->shp_balance_pre[9],0,8),\
															reg_sp_gb_y1,			GET_BITS(pp->shp_balance_pre[11],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_sp_ctrl_08,	reg_sp_gb_x2,			GET_BITS(pp->shp_balance_pre[10],0,8),\
															reg_sp_gb_y2,			GET_BITS(pp->shp_balance_pre[12],0,8),\
															reg_sp_gb_y3,			GET_BITS(pp->shp_balance_pre[13],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR05(shp_contrast_ctrl_00,reg_lc_shp_en,			GET_BITS(pp->shp_balance_pre[14],0,1),\
															reg_lc_gb_en,			GET_BITS(pp->shp_balance_pre[15],0,8),\
															reg_lc_center_target,	GET_BITS(pp->shp_balance_pre[22],0,8),\
															reg_lc_center_gain,  	GET_BITS(pp->shp_balance_pre[23],0,8),\
															reg_lc_local_gain,   	GET_BITS(pp->shp_balance_pre[24],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_contrast_ctrl_01,reg_lc_gb_x1,			GET_BITS(pp->shp_balance_pre[16],0,8),\
															reg_lc_gb_x2,			GET_BITS(pp->shp_balance_pre[17],0,8),\
															reg_lc_gb_y1,			GET_BITS(pp->shp_balance_pre[19],0,8),\
															reg_lc_gb_y2,			GET_BITS(pp->shp_balance_pre[20],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_contrast_ctrl_02,reg_lc_gb_x3,			GET_BITS(pp->shp_balance_pre[18],0,8),\
															reg_lc_gb_y3,			GET_BITS(pp->shp_balance_pre[21],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_mp_ctrl_09,	reg_mp_lum1_x_l0,	GET_BITS(pp->shp_balance_pre[25],0,8),\
															reg_mp_lum1_x_l1,	GET_BITS(pp->shp_balance_pre[26],0,8),\
															reg_mp_lum1_x_h0,	GET_BITS(pp->shp_balance_pre[27],0,8),\
															reg_mp_lum1_x_h1,	GET_BITS(pp->shp_balance_pre[28],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_mp_ctrl_0a,	reg_mp_lum1_y0,		GET_BITS(pp->shp_balance_pre[29],0,8),\
															reg_mp_lum1_y1,		GET_BITS(pp->shp_balance_pre[30],0,8),\
															reg_mp_lum1_y2,		GET_BITS(pp->shp_balance_pre[31],0,8),\
															reg_mp_lum2_x_l0,	GET_BITS(pp->shp_balance_pre[32],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_mp_ctrl_0b,	reg_mp_lum2_x_l1,	GET_BITS(pp->shp_balance_pre[33],0,8),\
															reg_mp_lum2_x_h0,	GET_BITS(pp->shp_balance_pre[34],0,8),\
															reg_mp_lum2_x_h1,	GET_BITS(pp->shp_balance_pre[35],0,8),\
															reg_mp_lum2_y0,  	GET_BITS(pp->shp_balance_pre[36],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_lum2_y1,		GET_BITS(pp->shp_balance_pre[37],0,8),\
															reg_mp_lum2_y2,		GET_BITS(pp->shp_balance_pre[38],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_sp_ctrl_09,	reg_sp_lum1_x_l0,	GET_BITS(pp->shp_balance_pre[39],0,8),\
															reg_sp_lum1_x_l1,	GET_BITS(pp->shp_balance_pre[40],0,8),\
															reg_sp_lum1_x_h0,	GET_BITS(pp->shp_balance_pre[41],0,8),\
															reg_sp_lum1_x_h1,	GET_BITS(pp->shp_balance_pre[42],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_sp_ctrl_0a,	reg_sp_lum1_y0,		GET_BITS(pp->shp_balance_pre[43],0,8),\
															reg_sp_lum1_y1,		GET_BITS(pp->shp_balance_pre[44],0,8),\
															reg_sp_lum1_y2,		GET_BITS(pp->shp_balance_pre[45],0,8),\
															reg_sp_lum2_x_l0,	GET_BITS(pp->shp_balance_pre[46],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_sp_ctrl_0b,	reg_sp_lum2_x_l1,	GET_BITS(pp->shp_balance_pre[47],0,8),\
															reg_sp_lum2_x_h0,	GET_BITS(pp->shp_balance_pre[48],0,8),\
															reg_sp_lum2_x_h1,	GET_BITS(pp->shp_balance_pre[49],0,8),\
															reg_sp_lum2_y0, 	GET_BITS(pp->shp_balance_pre[50],0,8));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_lum2_y1,		GET_BITS(pp->shp_balance_pre[51],0,8),\
															reg_sp_lum2_y2,		GET_BITS(pp->shp_balance_pre[52],0,8));

				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_pti_ctrl_00,reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_pre[0],0,1),\
														reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_pre[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[3],0,2));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_pti_ctrl_01,reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_pre[4],0,1),\
														reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_pre[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[7],0,2));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_sti_ctrl_00,reg_sti_enable,		GET_BITS(pp->shp_ti_cmn_pre[8],0,1),\
														reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_pre[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[11],0,2));

				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_tgen_ctrl_00,reg_tgen_on_off,		GET_BITS(pp->shp_tgen_cmn_pre[0],0,1));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_tgen_ctrl_01,reg_tgen_delta_h_bound,	GET_BITS(pp->shp_tgen_cmn_pre[1],0,5),\
														reg_tgen_delta_l_bound,	GET_BITS(pp->shp_tgen_cmn_pre[2],0,5),\
														reg_tgen_delta_max,		GET_BITS(pp->shp_tgen_cmn_pre[3],0,7),\
														reg_tgen_delta_scale,	GET_BITS(pp->shp_tgen_cmn_pre[4],0,3));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_tgen_ctrl_02,reg_tgen_rnd_th,		GET_BITS(pp->shp_tgen_cmn_pre[5],0,8),\
														reg_tgen_delta_wcurr,	GET_BITS(pp->shp_tgen_cmn_pre[6],0,4),\
														reg_tgen_lc_ldr_th,		GET_BITS(pp->shp_tgen_cmn_pre[7],0,6));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_tgen_ctrl_04,reg_tgen_dr_ratio,	GET_BITS(pp->shp_tgen_cmn_pre[8],0,3),\
														reg_tgen_dr_th,			GET_BITS(pp->shp_tgen_cmn_pre[9],0,6),\
														reg_tgen_mm_offset,		GET_BITS(pp->shp_tgen_cmn_pre[10],0,5),\
														reg_tgen_mm_sel_mode,	GET_BITS(pp->shp_tgen_cmn_pre[11],0,2));
				PE_SHP_HW_M17C0_SR_SHP_WR03(shp_tgen_ctrl_05,reg_tgen_lavg_th,	GET_BITS(pp->shp_tgen_cmn_pre[12],0,8),\
														reg_tgen_gs_rnd,		GET_BITS(pp->shp_tgen_cmn_pre[13],0,5),\
														reg_tgen_gs_mm,			GET_BITS(pp->shp_tgen_cmn_pre[14],0,5));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_tgen_ctrl_09,reg_tgen_gain0,		GET_BITS(pp->shp_tgen_cmn_pre[15],0,4),\
														reg_tgen_gain1,			GET_BITS(pp->shp_tgen_cmn_pre[16],0,4),\
														reg_tgen_gain2,			GET_BITS(pp->shp_tgen_cmn_pre[17],0,4),\
														reg_tgen_gain3,			GET_BITS(pp->shp_tgen_cmn_pre[18],0,4));
				PE_SHP_HW_M17C0_SR_SHP_WR04(shp_tgen_ctrl_09,reg_tgen_gain4,		GET_BITS(pp->shp_tgen_cmn_pre[19],0,4),\
														reg_tgen_gain5,			GET_BITS(pp->shp_tgen_cmn_pre[20],0,4),\
														reg_tgen_gain6,			GET_BITS(pp->shp_tgen_cmn_pre[21],0,4),\
														reg_tgen_gain7,			GET_BITS(pp->shp_tgen_cmn_pre[22],0,4));
				#else
				PE_SR_SHP_M17C0_QWr01(shp_derh_ctrl_06,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_pre[0],0,1));
				PE_SR_SHP_M17C0_QWr04(shp_dp_ctrl_05,	reg_der_x0,					GET_BITS(pp->shp_cmn_pre[1],0,8),\
													reg_der_x1,		 			GET_BITS(pp->shp_cmn_pre[2],0,8),\
													reg_der_y0,					GET_BITS(pp->shp_cmn_pre[5],0,8),\
													reg_der_y1,		 			GET_BITS(pp->shp_cmn_pre[6],0,8));
				PE_SR_SHP_M17C0_QWr04(shp_dp_ctrl_06,	reg_der_x2,					GET_BITS(pp->shp_cmn_pre[3],0,8),\
													reg_der_x3,		 			GET_BITS(pp->shp_cmn_pre[4],0,8),\
													reg_der_y2,					GET_BITS(pp->shp_cmn_pre[7],0,8),\
													reg_der_y3,		 			GET_BITS(pp->shp_cmn_pre[8],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_mp_ctrl_00,	reg_mp_shp_en,				GET_BITS(pp->shp_cmn_pre[9],0,1));
				PE_SR_SHP_M17C0_QWr01(shp_sp_ctrl_00,	reg_sp_shp_en,				GET_BITS(pp->shp_cmn_pre[10],0,1));
				PE_SR_SHP_M17C0_QWr01(shp_mp_ctrl_02,	reg_mp_lap_weight,			GET_BITS(pp->shp_cmn_pre[11],0,8));
				PE_SR_SHP_M17C0_QWr01(shp_sp_ctrl_02,	reg_sp_lap_weight,			GET_BITS(pp->shp_cmn_pre[12],0,8));\
				PE_SR_SHP_M17C0_QWr03(shp_derh_ctrl_07,	reg_derh_flat_filter_en,	GET_BITS(pp->shp_cmn_pre[13],0,1),\
													reg_derh_flat_filter_type,	GET_BITS(pp->shp_cmn_pre[14],0,1),\
													reg_derh_flat_filter_gain,	GET_BITS(pp->shp_cmn_pre[15],0,6));
				PE_SR_SHP_M17C0_QWr06(shp_dj_ctrl_00,	reg_dj_edf_en,				GET_BITS(pp->shp_cmn_pre[16],0,1),\
													reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_cmn_pre[17],0,1),\
													reg_dj_center_blur_mode,	GET_BITS(pp->shp_cmn_pre[20],0,2),\
													reg_dj_count_diff_th,		GET_BITS(pp->shp_cmn_pre[21],0,5),\
													reg_dj_n_avg_mode,		 	GET_BITS(pp->shp_cmn_pre[22],0,1),\
													reg_dj_line_variation_diff_th,	GET_BITS(pp->shp_cmn_pre[23],0,8));
				PE_SR_SHP_M17C0_QWr04(shp_dj_ctrl_03,	reg_dj_edge_min,			GET_BITS(pp->shp_cmn_pre[18],0,8),\
													reg_dj_edge_mul,			GET_BITS(pp->shp_cmn_pre[19],0,8),\
													reg_dj_g1_protect_min,		GET_BITS(pp->shp_cmn_pre[28],0,8),\
													reg_dj_g1_mul,				GET_BITS(pp->shp_cmn_pre[29],0,7));

				PE_SR_SHP_M17C0_QWr02(shp_dj_ctrl_01,	reg_dj_level_th,			GET_BITS(pp->shp_cmn_pre[24],0,8),\
													reg_dj_n_avg_gain,			GET_BITS(pp->shp_cmn_pre[25],0,8));
				PE_SR_SHP_M17C0_QWr02(shp_dj_ctrl_02,	reg_dj_g0_cnt_min,			GET_BITS(pp->shp_cmn_pre[26],0,5),\
													reg_dj_g0_mul,				GET_BITS(pp->shp_cmn_pre[27],0,5));

				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_00,reg_fd_cross_th,			GET_BITS(pp->shp_map_cmn_pre[0],0,8),\
													reg_fd_pre_a_map_h_size,	GET_BITS(pp->shp_map_cmn_pre[14],0,3),\
													reg_fd_pre_a_map_v_size,	GET_BITS(pp->shp_map_cmn_pre[15],0,2),\
													reg_fd_pre_a_cut_resolution,GET_BITS(pp->shp_map_cmn_pre[16],0,3));

				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_00,reg_fd_a_map_h_size,		GET_BITS(pp->shp_map_cmn_pre[17],0,2),\
													reg_fd_a_nomalize_en,		GET_BITS(pp->shp_map_cmn_pre[18],0,1),\
													reg_fd_t_cut_resolution,	GET_BITS(pp->shp_map_cmn_pre[33],0,2),\
													reg_fd_t_nomalize_en,		GET_BITS(pp->shp_map_cmn_pre[34],0,1));
				PE_SR_SHP_M17C0_QWr02(shp_coring_ctrl_08,reg_fd_mul_base_t,			GET_BITS(pp->shp_map_cmn_pre[1],0,8),\
													reg_fd_mul_base_e,			GET_BITS(pp->shp_map_cmn_pre[2],0,8));			
				PE_SR_SHP_M17C0_QWr03(shp_mnr_ctrl_00,	reg_fd_mnr_gain_e_en,		GET_BITS(pp->shp_map_cmn_pre[3],0,1),\
													reg_fd_mnr_gain_t_en,		GET_BITS(pp->shp_map_cmn_pre[4],0,1),\
													reg_fd_mnr_s1_h_expand,		GET_BITS(pp->shp_map_cmn_pre[5],0,2));
				PE_SR_SHP_M17C0_QWr04(shp_mnr_ctrl_01,	reg_fd_mnr_s1_mmd_min  ,GET_BITS(pp->shp_map_cmn_pre[6],0,8),\
													reg_fd_mnr_s2_ratio_min,GET_BITS(pp->shp_map_cmn_pre[7],0,8),\
													reg_fd_mnr_s2_ratio_max,GET_BITS(pp->shp_map_cmn_pre[8],0,8),\
													reg_fd_mnr_s2_mmd_min,  GET_BITS(pp->shp_map_cmn_pre[9],0,8));
				PE_SR_SHP_M17C0_QWr04(shp_mnr_ctrl_02,	reg_fd_gain_x0,			GET_BITS(pp->shp_map_cmn_pre[10],0,8),\
													reg_fd_gain_x1,			GET_BITS(pp->shp_map_cmn_pre[11],0,8),\
													reg_fd_gain_y0,			GET_BITS(pp->shp_map_cmn_pre[12],0,8),\
													reg_fd_gain_y1,			GET_BITS(pp->shp_map_cmn_pre[13],0,8));
				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_01,reg_fd_detail_beta_mul, GET_BITS(pp->shp_map_cmn_pre[36],0,8),\
													reg_fd_detail_alpha_mul,GET_BITS(pp->shp_map_cmn_pre[35],0,8),\
													reg_fd_edge_beta_mul,   GET_BITS(pp->shp_map_cmn_pre[20],0,8),\
													reg_fd_edge_alpha_mul,  GET_BITS(pp->shp_map_cmn_pre[19],0,8));

				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_02,reg_fd_a_lut_edge_x0,	GET_BITS(pp->shp_map_cmn_pre[21],0,8),\
													reg_fd_a_lut_edge_y0,	GET_BITS(pp->shp_map_cmn_pre[22],0,8),\
													reg_fd_a_lut_edge_x1,	GET_BITS(pp->shp_map_cmn_pre[23],0,8),\
													reg_fd_a_lut_edge_y1,	GET_BITS(pp->shp_map_cmn_pre[24],0,8));
				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_03,reg_fd_a_lut_detail_x0,	GET_BITS(pp->shp_map_cmn_pre[25],0,8),\
													reg_fd_a_lut_detail_y0,	GET_BITS(pp->shp_map_cmn_pre[26],0,8),\
													reg_fd_a_lut_detail_x1,	GET_BITS(pp->shp_map_cmn_pre[27],0,8),\
													reg_fd_a_lut_detail_y1,	GET_BITS(pp->shp_map_cmn_pre[28],0,8));

				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_06,reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_pre[29],0,8),\
													reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_pre[30],0,8),\
													reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_pre[31],0,8),\
													reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_pre[32],0,8));

				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_04,reg_fd_t_lut_edge_x0,	GET_BITS(pp->shp_map_cmn_pre[37],0,8),\
													reg_fd_t_lut_edge_y0,	GET_BITS(pp->shp_map_cmn_pre[38],0,8),\
													reg_fd_t_lut_edge_x1,	GET_BITS(pp->shp_map_cmn_pre[39],0,8),\
													reg_fd_t_lut_edge_y1,	GET_BITS(pp->shp_map_cmn_pre[40],0,8));

				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_05,reg_fd_t_lut_detail_x0,	GET_BITS(pp->shp_map_cmn_pre[41],0,8),\
													reg_fd_t_lut_detail_y0,	GET_BITS(pp->shp_map_cmn_pre[42],0,8),\
													reg_fd_t_lut_detail_x1,	GET_BITS(pp->shp_map_cmn_pre[43],0,8),\
													reg_fd_t_lut_detail_y1,	GET_BITS(pp->shp_map_cmn_pre[44],0,8));

				PE_SR_SHP_M17C0_QWr04(shp_coring_ctrl_07,reg_fd_detail_minmax_x0,GET_BITS(pp->shp_map_cmn_pre[45],0,8),\
													reg_fd_detail_minmax_y0,GET_BITS(pp->shp_map_cmn_pre[46],0,8),\
													reg_fd_detail_minmax_x1,GET_BITS(pp->shp_map_cmn_pre[47],0,8),\
													reg_fd_detail_minmax_y1,GET_BITS(pp->shp_map_cmn_pre[48],0,8));

				PE_SR_SHP_M17C0_QWr04(shp_mp_ctrl_07,	reg_mp_gb_en,			GET_BITS(pp->shp_balance_pre[0],0,1),\
													reg_mp_gb_mode,			GET_BITS(pp->shp_balance_pre[1],0,1),\
													reg_mp_gb_x1,			GET_BITS(pp->shp_balance_pre[2],0,8),\
													reg_mp_gb_y1,			GET_BITS(pp->shp_balance_pre[4],0,8));
				PE_SR_SHP_M17C0_QWr03(shp_mp_ctrl_08,	reg_mp_gb_x2,			GET_BITS(pp->shp_balance_pre[3],0,8),\
													reg_mp_gb_y2,			GET_BITS(pp->shp_balance_pre[5],0,8),\
													reg_mp_gb_y3,			GET_BITS(pp->shp_balance_pre[6],0,8));

				PE_SR_SHP_M17C0_QWr04(shp_sp_ctrl_07,	reg_sp_gb_en,			GET_BITS(pp->shp_balance_pre[7],0,1),\
													reg_sp_gb_mode,			GET_BITS(pp->shp_balance_pre[8],0,1),\
													reg_sp_gb_x1,			GET_BITS(pp->shp_balance_pre[9],0,8),\
													reg_sp_gb_y1,			GET_BITS(pp->shp_balance_pre[11],0,8));
				PE_SR_SHP_M17C0_QWr03(shp_sp_ctrl_08,	reg_sp_gb_x2,			GET_BITS(pp->shp_balance_pre[10],0,8),\
													reg_sp_gb_y2,			GET_BITS(pp->shp_balance_pre[12],0,8),\
													reg_sp_gb_y3,			GET_BITS(pp->shp_balance_pre[13],0,8));

				PE_SR_SHP_M17C0_QWr05(shp_contrast_ctrl_00,reg_lc_shp_en,		GET_BITS(pp->shp_balance_pre[14],0,1),\
													reg_lc_gb_en,			GET_BITS(pp->shp_balance_pre[15],0,8),\
													reg_lc_center_target,	GET_BITS(pp->shp_balance_pre[22],0,8),\
													reg_lc_center_gain,  	GET_BITS(pp->shp_balance_pre[23],0,8),\
													reg_lc_local_gain,  	GET_BITS(pp->shp_balance_pre[24],0,8));
				PE_SR_SHP_M17C0_QWr04(shp_contrast_ctrl_01,reg_lc_gb_x1,			GET_BITS(pp->shp_balance_pre[16],0,8),\
													reg_lc_gb_x2,			GET_BITS(pp->shp_balance_pre[17],0,8),\
													reg_lc_gb_y1,			GET_BITS(pp->shp_balance_pre[19],0,8),\
													reg_lc_gb_y2,			GET_BITS(pp->shp_balance_pre[20],0,8));
				PE_SR_SHP_M17C0_QWr02(shp_contrast_ctrl_02,reg_lc_gb_x3,			GET_BITS(pp->shp_balance_pre[18],0,8),\
													reg_lc_gb_y3,			GET_BITS(pp->shp_balance_pre[21],0,8));
				PE_SR_SHP_M17C0_QWr04(shp_mp_ctrl_09,	reg_mp_lum1_x_l0,		GET_BITS(pp->shp_balance_pre[25],0,8),\
													reg_mp_lum1_x_l1,		GET_BITS(pp->shp_balance_pre[26],0,8),\
													reg_mp_lum1_x_h0,		GET_BITS(pp->shp_balance_pre[27],0,8),\
													reg_mp_lum1_x_h1,		GET_BITS(pp->shp_balance_pre[28],0,8));
				
				PE_SR_SHP_M17C0_QWr04(shp_mp_ctrl_0a,	reg_mp_lum1_y0,			GET_BITS(pp->shp_balance_pre[29],0,8),\
													reg_mp_lum1_y1,			GET_BITS(pp->shp_balance_pre[30],0,8),\
													reg_mp_lum1_y2,			GET_BITS(pp->shp_balance_pre[31],0,8),\
													reg_mp_lum2_x_l0,		GET_BITS(pp->shp_balance_pre[32],0,8));
					
				PE_SR_SHP_M17C0_QWr04(shp_mp_ctrl_0b,	reg_mp_lum2_x_l1,		GET_BITS(pp->shp_balance_pre[33],0,8),\
													reg_mp_lum2_x_h0,		GET_BITS(pp->shp_balance_pre[34],0,8),\
													reg_mp_lum2_x_h1,		GET_BITS(pp->shp_balance_pre[35],0,8),\
													reg_mp_lum2_y0,  		GET_BITS(pp->shp_balance_pre[36],0,8));
					
				PE_SR_SHP_M17C0_QWr02(shp_mp_ctrl_0c,	reg_mp_lum2_y1,			GET_BITS(pp->shp_balance_pre[37],0,8),\
													reg_mp_lum2_y2,			GET_BITS(pp->shp_balance_pre[38],0,8));
					
				PE_SR_SHP_M17C0_QWr04(shp_sp_ctrl_09,	reg_sp_lum1_x_l0,		GET_BITS(pp->shp_balance_pre[39],0,8),\
													reg_sp_lum1_x_l1,		GET_BITS(pp->shp_balance_pre[40],0,8),\
													reg_sp_lum1_x_h0,		GET_BITS(pp->shp_balance_pre[41],0,8),\
													reg_sp_lum1_x_h1,		GET_BITS(pp->shp_balance_pre[42],0,8));
				PE_SR_SHP_M17C0_QWr04(shp_sp_ctrl_0a,	reg_sp_lum1_y0,			GET_BITS(pp->shp_balance_pre[43],0,8),\
													reg_sp_lum1_y1,			GET_BITS(pp->shp_balance_pre[44],0,8),\
													reg_sp_lum1_y2,			GET_BITS(pp->shp_balance_pre[45],0,8),\
													reg_sp_lum2_x_l0,		GET_BITS(pp->shp_balance_pre[46],0,8));
					
				PE_SR_SHP_M17C0_QWr04(shp_sp_ctrl_0b,	reg_sp_lum2_x_l1,		GET_BITS(pp->shp_balance_pre[47],0,8),\
													reg_sp_lum2_x_h0,		GET_BITS(pp->shp_balance_pre[48],0,8),\
													reg_sp_lum2_x_h1,		GET_BITS(pp->shp_balance_pre[49],0,8),\
													reg_sp_lum2_y0, 		GET_BITS(pp->shp_balance_pre[50],0,8));
				PE_SR_SHP_M17C0_QWr02(shp_sp_ctrl_0c,	reg_sp_lum2_y1,			GET_BITS(pp->shp_balance_pre[51],0,8),\
													reg_sp_lum2_y2,			GET_BITS(pp->shp_balance_pre[52],0,8));

				PE_SR_SHP_M17C0_QWr04(shp_pti_ctrl_00,		reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_pre[0],0,1),\
														reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_pre[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[3],0,2));
				PE_SR_SHP_M17C0_QWr04(shp_pti_ctrl_01,		reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_pre[4],0,1),\
														reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_pre[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[7],0,2));
				PE_SR_SHP_M17C0_QWr04(shp_sti_ctrl_00,		reg_sti_enable,			GET_BITS(pp->shp_ti_cmn_pre[8],0,1),\
														reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_pre[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_pre[11],0,2));
				PE_SR_SHP_M17C0_QWr01(shp_tgen_ctrl_00,		reg_tgen_on_off,		GET_BITS(pp->shp_tgen_cmn_pre[0],0,1));
				PE_SR_SHP_M17C0_QWr04(shp_tgen_ctrl_01,		reg_tgen_delta_h_bound,	GET_BITS(pp->shp_tgen_cmn_pre[1],0,5),\
														reg_tgen_delta_l_bound,	GET_BITS(pp->shp_tgen_cmn_pre[2],0,5),\
														reg_tgen_delta_max,		GET_BITS(pp->shp_tgen_cmn_pre[3],0,7),\
														reg_tgen_delta_scale,	GET_BITS(pp->shp_tgen_cmn_pre[4],0,3));
				PE_SR_SHP_M17C0_QWr03(shp_tgen_ctrl_02,		reg_tgen_rnd_th,		GET_BITS(pp->shp_tgen_cmn_pre[5],0,8),\
														reg_tgen_delta_wcurr,	GET_BITS(pp->shp_tgen_cmn_pre[6],0,4),\
														reg_tgen_lc_ldr_th,		GET_BITS(pp->shp_tgen_cmn_pre[7],0,6));
				PE_SR_SHP_M17C0_QWr04(shp_tgen_ctrl_04,		reg_tgen_dr_ratio,		GET_BITS(pp->shp_tgen_cmn_pre[8],0,3),\
														reg_tgen_dr_th,			GET_BITS(pp->shp_tgen_cmn_pre[9],0,6),\
														reg_tgen_mm_offset,		GET_BITS(pp->shp_tgen_cmn_pre[10],0,5),\
														reg_tgen_mm_sel_mode,	GET_BITS(pp->shp_tgen_cmn_pre[11],0,2));
				PE_SR_SHP_M17C0_QWr03(shp_tgen_ctrl_05,		reg_tgen_lavg_th,		GET_BITS(pp->shp_tgen_cmn_pre[12],0,8),\
														reg_tgen_gs_rnd,		GET_BITS(pp->shp_tgen_cmn_pre[13],0,5),\
														reg_tgen_gs_mm,			GET_BITS(pp->shp_tgen_cmn_pre[14],0,5));
				PE_SR_SHP_M17C0_QWr04(shp_tgen_ctrl_09,		reg_tgen_gain0,			GET_BITS(pp->shp_tgen_cmn_pre[15],0,4),\
														reg_tgen_gain1,			GET_BITS(pp->shp_tgen_cmn_pre[16],0,4),\
														reg_tgen_gain2,			GET_BITS(pp->shp_tgen_cmn_pre[17],0,4),\
														reg_tgen_gain3,			GET_BITS(pp->shp_tgen_cmn_pre[18],0,4));
				PE_SR_SHP_M17C0_QWr04(shp_tgen_ctrl_09,		reg_tgen_gain4,			GET_BITS(pp->shp_tgen_cmn_pre[19],0,4),\
														reg_tgen_gain5,			GET_BITS(pp->shp_tgen_cmn_pre[20],0,4),\
														reg_tgen_gain6,			GET_BITS(pp->shp_tgen_cmn_pre[21],0,4),\
														reg_tgen_gain7,			GET_BITS(pp->shp_tgen_cmn_pre[22],0,4));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif
	return ret;
}
/**
 * get sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetSreReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE3_MISC_T *pp=(LX_PE_SHP_SR_RE3_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_SHP_M17C0_QRd01(shp_derh_ctrl_06,	reg_derh_edge_y_filter_en,	pp->shp_cmn_pre[0]);
				PE_SR_SHP_M17C0_QRd04(shp_dp_ctrl_05,	reg_der_x0,					pp->shp_cmn_pre[1],\
													reg_der_x1,		 			pp->shp_cmn_pre[2],\
													reg_der_y0,					pp->shp_cmn_pre[5],\
													reg_der_y1,		 			pp->shp_cmn_pre[6]);
				PE_SR_SHP_M17C0_QRd04(shp_dp_ctrl_06,	reg_der_x2,					pp->shp_cmn_pre[3],\
													reg_der_x3,		 			pp->shp_cmn_pre[4],\
													reg_der_y2,					pp->shp_cmn_pre[7],\
													reg_der_y3,		 			pp->shp_cmn_pre[8]);
				PE_SR_SHP_M17C0_QRd01(shp_mp_ctrl_00,	reg_mp_shp_en,				pp->shp_cmn_pre[9]);
				PE_SR_SHP_M17C0_QRd01(shp_sp_ctrl_00,	reg_sp_shp_en,				pp->shp_cmn_pre[10]);
				PE_SR_SHP_M17C0_QRd01(shp_mp_ctrl_02,	reg_mp_lap_weight,			pp->shp_cmn_pre[11]);
				PE_SR_SHP_M17C0_QRd01(shp_sp_ctrl_02,	reg_sp_lap_weight,			pp->shp_cmn_pre[12]);\
				PE_SR_SHP_M17C0_QRd03(shp_derh_ctrl_07,	reg_derh_flat_filter_en,	pp->shp_cmn_pre[13],\
													reg_derh_flat_filter_type,	pp->shp_cmn_pre[14],\
													reg_derh_flat_filter_gain,	pp->shp_cmn_pre[15]);
				PE_SR_SHP_M17C0_QRd06(shp_dj_ctrl_00,	reg_dj_edf_en,				pp->shp_cmn_pre[16],\
													reg_dj_edge_adaptive_en,	pp->shp_cmn_pre[17],\
													reg_dj_center_blur_mode,	pp->shp_cmn_pre[20],\
													reg_dj_count_diff_th,		pp->shp_cmn_pre[21],\
													reg_dj_n_avg_mode,		 	pp->shp_cmn_pre[22],\
													reg_dj_line_variation_diff_th,pp->shp_cmn_pre[23]);
				PE_SR_SHP_M17C0_QRd04(shp_dj_ctrl_03,	reg_dj_edge_min,			pp->shp_cmn_pre[18],\
													reg_dj_edge_mul,			pp->shp_cmn_pre[19],\
													reg_dj_g1_protect_min,		pp->shp_cmn_pre[28],\
													reg_dj_g1_mul,				pp->shp_cmn_pre[29]);

				PE_SR_SHP_M17C0_QRd02(shp_dj_ctrl_01,	reg_dj_level_th,			pp->shp_cmn_pre[24],\
													reg_dj_n_avg_gain,			pp->shp_cmn_pre[25]);
				PE_SR_SHP_M17C0_QRd02(shp_dj_ctrl_02,	reg_dj_g0_cnt_min,			pp->shp_cmn_pre[26],\
													reg_dj_g0_mul,				pp->shp_cmn_pre[27]);

				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_00,reg_fd_cross_th,			pp->shp_map_cmn_pre[0],\
													reg_fd_pre_a_map_h_size,	pp->shp_map_cmn_pre[14],\
													reg_fd_pre_a_map_v_size,	pp->shp_map_cmn_pre[15],\
													reg_fd_pre_a_cut_resolution,pp->shp_map_cmn_pre[16]);

				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_00,reg_fd_a_map_h_size,		pp->shp_map_cmn_pre[17],\
													reg_fd_a_nomalize_en,		pp->shp_map_cmn_pre[18],\
													reg_fd_t_cut_resolution,	pp->shp_map_cmn_pre[33],\
													reg_fd_t_nomalize_en,		pp->shp_map_cmn_pre[34]);
				PE_SR_SHP_M17C0_QRd02(shp_coring_ctrl_08,reg_fd_mul_base_t,			pp->shp_map_cmn_pre[1],\
													reg_fd_mul_base_e,			pp->shp_map_cmn_pre[2]);			
				PE_SR_SHP_M17C0_QRd03(shp_mnr_ctrl_00,	reg_fd_mnr_gain_e_en,		pp->shp_map_cmn_pre[3],\
													reg_fd_mnr_gain_t_en,		pp->shp_map_cmn_pre[4],\
													reg_fd_mnr_s1_h_expand,		pp->shp_map_cmn_pre[5]);
				PE_SR_SHP_M17C0_QRd04(shp_mnr_ctrl_01,	reg_fd_mnr_s1_mmd_min  ,pp->shp_map_cmn_pre[6],\
													reg_fd_mnr_s2_ratio_min,pp->shp_map_cmn_pre[7],\
													reg_fd_mnr_s2_ratio_max,pp->shp_map_cmn_pre[8],\
													reg_fd_mnr_s2_mmd_min,  pp->shp_map_cmn_pre[9]);
				PE_SR_SHP_M17C0_QRd04(shp_mnr_ctrl_02,	reg_fd_gain_x0,			pp->shp_map_cmn_pre[10],\
													reg_fd_gain_x1,			pp->shp_map_cmn_pre[11],\
													reg_fd_gain_y0,			pp->shp_map_cmn_pre[12],\
													reg_fd_gain_y1,			pp->shp_map_cmn_pre[13]);
				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_01,reg_fd_detail_beta_mul, pp->shp_map_cmn_pre[36],\
													reg_fd_detail_alpha_mul,pp->shp_map_cmn_pre[35],\
													reg_fd_edge_beta_mul,   pp->shp_map_cmn_pre[20],\
													reg_fd_edge_alpha_mul,  pp->shp_map_cmn_pre[19]);

				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_02,reg_fd_a_lut_edge_x0,	pp->shp_map_cmn_pre[21],\
													reg_fd_a_lut_edge_y0,	pp->shp_map_cmn_pre[22],\
													reg_fd_a_lut_edge_x1,	pp->shp_map_cmn_pre[23],\
													reg_fd_a_lut_edge_y1,	pp->shp_map_cmn_pre[24]);
				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_03,reg_fd_a_lut_detail_x0,	pp->shp_map_cmn_pre[25],\
													reg_fd_a_lut_detail_y0,	pp->shp_map_cmn_pre[26],\
													reg_fd_a_lut_detail_x1,	pp->shp_map_cmn_pre[27],\
													reg_fd_a_lut_detail_y1,	pp->shp_map_cmn_pre[28]);

				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_06,reg_fd_edge_minmax_x0,	pp->shp_map_cmn_pre[29],\
													reg_fd_edge_minmax_y0,	pp->shp_map_cmn_pre[30],\
													reg_fd_edge_minmax_x1,	pp->shp_map_cmn_pre[31],\
													reg_fd_edge_minmax_y1,	pp->shp_map_cmn_pre[32]);

				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_04,reg_fd_t_lut_edge_x0,	pp->shp_map_cmn_pre[37],\
													reg_fd_t_lut_edge_y0,	pp->shp_map_cmn_pre[38],\
													reg_fd_t_lut_edge_x1,	pp->shp_map_cmn_pre[39],\
													reg_fd_t_lut_edge_y1,	pp->shp_map_cmn_pre[40]);

				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_05,reg_fd_t_lut_detail_x0,	pp->shp_map_cmn_pre[41],\
													reg_fd_t_lut_detail_y0,	pp->shp_map_cmn_pre[42],\
													reg_fd_t_lut_detail_x1,	pp->shp_map_cmn_pre[43],\
													reg_fd_t_lut_detail_y1,	pp->shp_map_cmn_pre[44]);

				PE_SR_SHP_M17C0_QRd04(shp_coring_ctrl_07,reg_fd_detail_minmax_x0,pp->shp_map_cmn_pre[45],\
													reg_fd_detail_minmax_y0,pp->shp_map_cmn_pre[46],\
													reg_fd_detail_minmax_x1,pp->shp_map_cmn_pre[47],\
													reg_fd_detail_minmax_y1,pp->shp_map_cmn_pre[48]);

				PE_SR_SHP_M17C0_QRd04(shp_mp_ctrl_07,	reg_mp_gb_en,			pp->shp_balance_pre[0],\
													reg_mp_gb_mode,			pp->shp_balance_pre[1],\
													reg_mp_gb_x1,			pp->shp_balance_pre[2],\
													reg_mp_gb_y1,			pp->shp_balance_pre[4]);
				PE_SR_SHP_M17C0_QRd03(shp_mp_ctrl_08,	reg_mp_gb_x2,			pp->shp_balance_pre[3],\
													reg_mp_gb_y2,			pp->shp_balance_pre[5],\
													reg_mp_gb_y3,			pp->shp_balance_pre[6]);

				PE_SR_SHP_M17C0_QRd04(shp_sp_ctrl_07,	reg_sp_gb_en,			pp->shp_balance_pre[7],\
													reg_sp_gb_mode,			pp->shp_balance_pre[8],\
													reg_sp_gb_x1,			pp->shp_balance_pre[9],\
													reg_sp_gb_y1,			pp->shp_balance_pre[11]);
				PE_SR_SHP_M17C0_QRd03(shp_sp_ctrl_08,	reg_sp_gb_x2,			pp->shp_balance_pre[10],\
													reg_sp_gb_y2,			pp->shp_balance_pre[12],\
													reg_sp_gb_y3,			pp->shp_balance_pre[13]);

				PE_SR_SHP_M17C0_QRd05(shp_contrast_ctrl_00,reg_lc_shp_en,		pp->shp_balance_pre[14],\
													reg_lc_gb_en,			pp->shp_balance_pre[15],\
													reg_lc_center_target,	pp->shp_balance_pre[22],\
													reg_lc_center_gain,  	pp->shp_balance_pre[23],\
													reg_lc_local_gain,  	pp->shp_balance_pre[24]);
				PE_SR_SHP_M17C0_QRd04(shp_contrast_ctrl_01,reg_lc_gb_x1,			pp->shp_balance_pre[16],\
													reg_lc_gb_x2,			pp->shp_balance_pre[17],\
													reg_lc_gb_y1,			pp->shp_balance_pre[19],\
													reg_lc_gb_y2,			pp->shp_balance_pre[20]);
				PE_SR_SHP_M17C0_QRd02(shp_contrast_ctrl_02,reg_lc_gb_x3,			pp->shp_balance_pre[18],\
													reg_lc_gb_y3,			pp->shp_balance_pre[21]);
				PE_SR_SHP_M17C0_QRd04(shp_mp_ctrl_09,	reg_mp_lum1_x_l0,	pp->shp_balance_pre[25],\
													reg_mp_lum1_x_l1,	pp->shp_balance_pre[26],\
													reg_mp_lum1_x_h0,	pp->shp_balance_pre[27],\
													reg_mp_lum1_x_h1,	pp->shp_balance_pre[28]);

				PE_SR_SHP_M17C0_QRd04(shp_mp_ctrl_0a,	reg_mp_lum1_y0,		pp->shp_balance_pre[29],\
													reg_mp_lum1_y1,		pp->shp_balance_pre[30],\
													reg_mp_lum1_y2,		pp->shp_balance_pre[31],\
													reg_mp_lum2_x_l0,	pp->shp_balance_pre[32]);

				PE_SR_SHP_M17C0_QRd04(shp_mp_ctrl_0b,	reg_mp_lum2_x_l1,	pp->shp_balance_pre[33],\
													reg_mp_lum2_x_h0,	pp->shp_balance_pre[34],\
													reg_mp_lum2_x_h1,	pp->shp_balance_pre[35],\
													reg_mp_lum2_y0,  	pp->shp_balance_pre[36]);

				PE_SR_SHP_M17C0_QRd02(shp_mp_ctrl_0c,	reg_mp_lum2_y1,		pp->shp_balance_pre[37],\
													reg_mp_lum2_y2,		pp->shp_balance_pre[38]);

				PE_SR_SHP_M17C0_QRd04(shp_sp_ctrl_09,	reg_sp_lum1_x_l0,	pp->shp_balance_pre[39],\
													reg_sp_lum1_x_l1,	pp->shp_balance_pre[40],\
													reg_sp_lum1_x_h0,	pp->shp_balance_pre[41],\
													reg_sp_lum1_x_h1,	pp->shp_balance_pre[42]);

				PE_SR_SHP_M17C0_QRd04(shp_sp_ctrl_0a,	reg_sp_lum1_y0,		pp->shp_balance_pre[43],\
													reg_sp_lum1_y1,		pp->shp_balance_pre[44],\
													reg_sp_lum1_y2,		pp->shp_balance_pre[45],\
													reg_sp_lum2_x_l0,	pp->shp_balance_pre[46]);

				PE_SR_SHP_M17C0_QRd04(shp_sp_ctrl_0b,	reg_sp_lum2_x_l1,	pp->shp_balance_pre[47],\
													reg_sp_lum2_x_h0,	pp->shp_balance_pre[48],\
													reg_sp_lum2_x_h1,	pp->shp_balance_pre[49],\
													reg_sp_lum2_y0, 	pp->shp_balance_pre[50]);
				PE_SR_SHP_M17C0_QRd02(shp_sp_ctrl_0c,	reg_sp_lum2_y1,		pp->shp_balance_pre[51],\
													reg_sp_lum2_y2,		pp->shp_balance_pre[52]);

				PE_SR_SHP_M17C0_QRd04(shp_pti_ctrl_00,	reg_ptiv_enable,		pp->shp_ti_cmn_pre[0],\
													reg_ptiv_ti_mode,		pp->shp_ti_cmn_pre[1],\
													reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_pre[2],\
													reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_pre[3]);
				PE_SR_SHP_M17C0_QRd04(shp_pti_ctrl_01,	reg_ptih_enable,		pp->shp_ti_cmn_pre[4],\
													reg_ptih_ti_mode,		pp->shp_ti_cmn_pre[5],\
													reg_ptih_mm_tap_size,	pp->shp_ti_cmn_pre[6],\
													reg_ptih_avg_tap_size,	pp->shp_ti_cmn_pre[7]);
				PE_SR_SHP_M17C0_QRd04(shp_sti_ctrl_00,	reg_sti_enable,			pp->shp_ti_cmn_pre[8],\
													reg_sti_ti_mode,		pp->shp_ti_cmn_pre[9],\
													reg_sti_mm_tap_size,	pp->shp_ti_cmn_pre[10],\
													reg_sti_avg_tap_size,	pp->shp_ti_cmn_pre[11]);

				PE_SR_SHP_M17C0_QRd01(shp_tgen_ctrl_00,	reg_tgen_on_off,		pp->shp_tgen_cmn_pre[0]);
				PE_SR_SHP_M17C0_QRd04(shp_tgen_ctrl_01,	reg_tgen_delta_h_bound,	pp->shp_tgen_cmn_pre[1],\
													reg_tgen_delta_l_bound,	pp->shp_tgen_cmn_pre[2],\
													reg_tgen_delta_max,		pp->shp_tgen_cmn_pre[3],\
													reg_tgen_delta_scale,	pp->shp_tgen_cmn_pre[4]);
				PE_SR_SHP_M17C0_QRd03(shp_tgen_ctrl_02,	reg_tgen_rnd_th,		pp->shp_tgen_cmn_pre[5],\
													reg_tgen_delta_wcurr,	pp->shp_tgen_cmn_pre[6],\
													reg_tgen_lc_ldr_th,		pp->shp_tgen_cmn_pre[7]);
				PE_SR_SHP_M17C0_QRd04(shp_tgen_ctrl_04,	reg_tgen_dr_ratio,		pp->shp_tgen_cmn_pre[8],\
													reg_tgen_dr_th,			pp->shp_tgen_cmn_pre[9],\
													reg_tgen_mm_offset,		pp->shp_tgen_cmn_pre[10],\
													reg_tgen_mm_sel_mode,	pp->shp_tgen_cmn_pre[11]);
				PE_SR_SHP_M17C0_QRd03(shp_tgen_ctrl_05,	reg_tgen_lavg_th,		pp->shp_tgen_cmn_pre[12],\
													reg_tgen_gs_rnd,		pp->shp_tgen_cmn_pre[13],\
													reg_tgen_gs_mm,			pp->shp_tgen_cmn_pre[14]);
				PE_SR_SHP_M17C0_QRd04(shp_tgen_ctrl_09,	reg_tgen_gain0,			pp->shp_tgen_cmn_pre[15],\
													reg_tgen_gain1,			pp->shp_tgen_cmn_pre[16],\
													reg_tgen_gain2,			pp->shp_tgen_cmn_pre[17],\
													reg_tgen_gain3,			pp->shp_tgen_cmn_pre[18]);
				PE_SR_SHP_M17C0_QRd04(shp_tgen_ctrl_09,	reg_tgen_gain4,			pp->shp_tgen_cmn_pre[19],\
													reg_tgen_gain5,			pp->shp_tgen_cmn_pre[20],\
													reg_tgen_gain6,			pp->shp_tgen_cmn_pre[21],\
													reg_tgen_gain7,			pp->shp_tgen_cmn_pre[22]);
			}
			pd = pp->shp_cmn_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : resolution misc ctrl\n"\
			"shp_cmn_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_pre     [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_pre     [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29]);
			pd = pp->shp_map_cmn_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48]);
			pd = pp->shp_balance_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_balance_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [50]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],   pd[4],   pd[5],   pd[6],   pd[7],   pd[8],   pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48],  pd[49], \
				pd[50], pd[51], pd[52]);
			pd = pp->shp_ti_cmn_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_pre  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_pre  [10]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11]);
			pd = pp->shp_tgen_cmn_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : resolution misc ctrl\n"\
			"shp_tgen_cmn_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_tgen_cmn_pre[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_tgen_cmn_pre[20]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22]);
		}
		
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	return ret;
}
/**
 * set sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetSreEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			UINT8 *pd;
			LX_PE_SHP_SR_EE3_T *pp=(LX_PE_SHP_SR_EE3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ee_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ee_pre\n"\
			"shp_ee_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_coring_ctrl_09,	reg_mpc_gain_e_b,	GET_BITS(pp->shp_ee_pre[0],0,7), \
																reg_mpc_gain_e_w,	GET_BITS(pp->shp_ee_pre[1],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_01,		reg_spc_gain_e_b,	GET_BITS(pp->shp_ee_pre[2],0,7), \
																reg_spc_gain_e_w,	GET_BITS(pp->shp_ee_pre[3],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_02,		reg_ptic_gain_e_b,	GET_BITS(pp->shp_ee_pre[4],0,7), \
																reg_ptic_gain_e_w,	GET_BITS(pp->shp_ee_pre[5],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_contrast_ctrl_03,	reg_lc_gain_e_b,	GET_BITS(pp->shp_ee_pre[6],0,7), \
																reg_lc_gain_e_w,	GET_BITS(pp->shp_ee_pre[7],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_03,		reg_tgenc_gain_e_b,	GET_BITS(pp->shp_ee_pre[8],0,7), \
																reg_tgenc_gain_e_w,	GET_BITS(pp->shp_ee_pre[9],0,7));
				

				#else
				PE_SR_SHP_M17C0_QWr02(shp_coring_ctrl_09,		reg_mpc_gain_e_b,	GET_BITS(pp->shp_ee_pre[0],0,7), \
															reg_mpc_gain_e_w,	GET_BITS(pp->shp_ee_pre[1],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_01,			reg_spc_gain_e_b,	GET_BITS(pp->shp_ee_pre[2],0,7), \
															reg_spc_gain_e_w,	GET_BITS(pp->shp_ee_pre[3],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_02,			reg_ptic_gain_e_b,	GET_BITS(pp->shp_ee_pre[4],0,7), \
															reg_ptic_gain_e_w,	GET_BITS(pp->shp_ee_pre[5],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_contrast_ctrl_03,	reg_lc_gain_e_b,	GET_BITS(pp->shp_ee_pre[6],0,7), \
															reg_lc_gain_e_w,	GET_BITS(pp->shp_ee_pre[7],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_03,			reg_tgenc_gain_e_b,	GET_BITS(pp->shp_ee_pre[8],0,7), \
															reg_tgenc_gain_e_w,	GET_BITS(pp->shp_ee_pre[9],0,7));
				#endif
			}
		}
		#else
		{
			LX_PE_SHP_SR_EE2_T *pp=(LX_PE_SHP_SR_EE2_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_ee;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_ee_pre\n"\
			"shp_ee_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
			#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SR_SHP_M17C0_QWr02(shp_coring_ctrl_09,	reg_mpc_gain_e_b,	GET_BITS(pp->shp_ee[0],0,7), \
														reg_mpc_gain_e_w,	GET_BITS(pp->shp_ee[1],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_01,		reg_spc_gain_e_b,		GET_BITS(pp->shp_ee[2],0,7), \
														reg_spc_gain_e_w,	GET_BITS(pp->shp_ee[3],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_02,		reg_ptic_gain_e_b,	GET_BITS(pp->shp_ee[4],0,7), \
														reg_ptic_gain_e_w,	GET_BITS(pp->shp_ee[5],0,7));
			#else
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_coring_ctrl_09,	reg_mpc_gain_e_b,	GET_BITS(pp->shp_ee[0],0,7), \
																reg_mpc_gain_e_w,	GET_BITS(pp->shp_ee[1],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_01,		reg_spc_gain_e_b,		GET_BITS(pp->shp_ee[2],0,7), \
																reg_spc_gain_e_w,		GET_BITS(pp->shp_ee[3],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_02,		reg_ptic_gain_e_b,	GET_BITS(pp->shp_ee[4],0,7), \
																reg_ptic_gain_e_w,	GET_BITS(pp->shp_ee[5],0,7));
			#endif
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get sr edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for M17C0
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetSreEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			UINT8 *pd;
			LX_PE_SHP_SR_EE3_T *pp=(LX_PE_SHP_SR_EE3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_SHP_M17C0_QRd02(shp_coring_ctrl_09,		reg_mpc_gain_e_b,	pp->shp_ee_pre[0], \
															reg_mpc_gain_e_w,	pp->shp_ee_pre[1]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_01,			reg_spc_gain_e_b,	pp->shp_ee_pre[2], \
															reg_spc_gain_e_w,	pp->shp_ee_pre[3]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_02,			reg_ptic_gain_e_b,	pp->shp_ee_pre[4], \
															reg_ptic_gain_e_w,	pp->shp_ee_pre[5]);
				PE_SR_SHP_M17C0_QRd02(shp_contrast_ctrl_03,	reg_lc_gain_e_b,	pp->shp_ee_pre[6], \
															reg_lc_gain_e_w,	pp->shp_ee_pre[7]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_03,			reg_tgenc_gain_e_b,	pp->shp_ee_pre[8], \
															reg_tgenc_gain_e_w,	pp->shp_ee_pre[9]);
				pd = pp->shp_ee_pre;
				PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_ee_pre\n"\
				"shp_ee_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9]);
			}
			
		}
		#else
		{
			LX_PE_SHP_SR_EE2_T *pp=(LX_PE_SHP_SR_EE2_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_SHP_M17C0_QRd02(shp_coring_ctrl_09,	reg_mpc_gain_e_b,	pp->shp_ee[0], \
														reg_mpc_gain_e_w,	pp->shp_ee[1]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_01,		reg_spc_gain_e_b,		pp->shp_ee[2], \
														reg_spc_gain_e_w,		pp->shp_ee[3]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_02,		reg_ptic_gain_e_b,	pp->shp_ee[4], \
														reg_ptic_gain_e_w,	pp->shp_ee[5]);
			}
			{
			UINT8 *pd = pp->shp_ee;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_ee_pre\n"\
			"shp_ee_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetSreDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			LX_PE_SHP_SR_DE3_T *pp=(LX_PE_SHP_SR_DE3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_de_pre;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_de_pre\n"\
			"shp_de_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_coring_ctrl_09,	reg_mpc_gain_t_b,	GET_BITS(pp->shp_de_pre[0],0,7), \
																reg_mpc_gain_t_w,	GET_BITS(pp->shp_de_pre[1],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_01,		reg_spc_gain_t_b,	GET_BITS(pp->shp_de_pre[2],0,7), \
																reg_spc_gain_t_w,	GET_BITS(pp->shp_de_pre[3],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_02,		reg_ptic_gain_t_b,	GET_BITS(pp->shp_de_pre[4],0,7), \
																reg_ptic_gain_t_w,	GET_BITS(pp->shp_de_pre[5],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_contrast_ctrl_03,	reg_lc_gain_t_b,	GET_BITS(pp->shp_de_pre[6],0,7), \
																reg_lc_gain_t_w,	GET_BITS(pp->shp_de_pre[7],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_03,		reg_tgenc_gain_t_b,	GET_BITS(pp->shp_de_pre[8],0,7), \
																reg_tgenc_gain_t_w,	GET_BITS(pp->shp_de_pre[9],0,7));

				#else
				PE_SR_SHP_M17C0_QWr02(shp_coring_ctrl_09,		reg_mpc_gain_t_b,	GET_BITS(pp->shp_de_pre[0],0,7), \
															reg_mpc_gain_t_w,	GET_BITS(pp->shp_de_pre[1],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_01,			reg_spc_gain_t_b,	GET_BITS(pp->shp_de_pre[2],0,7), \
															reg_spc_gain_t_w,	GET_BITS(pp->shp_de_pre[3],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_02,			reg_ptic_gain_t_b,	GET_BITS(pp->shp_de_pre[4],0,7), \
															reg_ptic_gain_t_w,	GET_BITS(pp->shp_de_pre[5],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_contrast_ctrl_03,	reg_lc_gain_t_b,	GET_BITS(pp->shp_de_pre[6],0,7), \
															reg_lc_gain_t_w,	GET_BITS(pp->shp_de_pre[7],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_03,			reg_tgenc_gain_t_b,	GET_BITS(pp->shp_de_pre[8],0,7), \
															reg_tgenc_gain_t_w,	GET_BITS(pp->shp_de_pre[9],0,7));
				#endif
			}
		}
		#else
		{
			LX_PE_SHP_SR_DE2_T *pp=(LX_PE_SHP_SR_DE2_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			{
			UINT8 *pd = pp->shp_de;
			PE_SHP_HW_M17C0_DBG_PRINT("set[%d] : shp_de_pre\n"\
			"shp_de_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
			#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				PE_SR_SHP_M17C0_QWr02(shp_coring_ctrl_09,	reg_mpc_gain_t_b,	GET_BITS(pp->shp_de[0],0,7), \
														reg_mpc_gain_t_w,	GET_BITS(pp->shp_de[1],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_01,		reg_spc_gain_t_b,		GET_BITS(pp->shp_de[2],0,7), \
														reg_spc_gain_t_w,		GET_BITS(pp->shp_de[3],0,7));
				PE_SR_SHP_M17C0_QWr02(shp_dp_ctrl_02,		reg_ptic_gain_t_b,	GET_BITS(pp->shp_de[4],0,7), \
														reg_ptic_gain_t_w,	GET_BITS(pp->shp_de[5],0,7));
			#else
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_coring_ctrl_09,	reg_mpc_gain_t_b,	GET_BITS(pp->shp_de[0],0,7), \
																reg_mpc_gain_t_w,	GET_BITS(pp->shp_de[1],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_01,		reg_spc_gain_t_b,	GET_BITS(pp->shp_de[2],0,7), \
																reg_spc_gain_t_w,	GET_BITS(pp->shp_de[3],0,7));
				PE_SHP_HW_M17C0_SR_SHP_WR02(shp_dp_ctrl_02,		reg_ptic_gain_t_b,	GET_BITS(pp->shp_de[4],0,7), \
																reg_ptic_gain_t_w,	GET_BITS(pp->shp_de[5],0,7));
			#endif
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for M17C0X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetSreDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		#ifdef PE_SHP_HW_M17C0_SR_SHP_DONE
		{
			LX_PE_SHP_SR_DE3_T *pp=(LX_PE_SHP_SR_DE3_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			UINT8 *pd = pp->shp_de_pre;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_SHP_M17C0_QRd02(shp_coring_ctrl_09,		reg_mpc_gain_t_b,	pp->shp_de_pre[0], \
															reg_mpc_gain_t_w,	pp->shp_de_pre[1]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_01,			reg_spc_gain_t_b,	pp->shp_de_pre[2], \
															reg_spc_gain_t_w,	pp->shp_de_pre[3]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_02,			reg_ptic_gain_t_b,	pp->shp_de_pre[4], \
															reg_ptic_gain_t_w,	pp->shp_de_pre[5]);
				PE_SR_SHP_M17C0_QRd02(shp_contrast_ctrl_03,	reg_lc_gain_t_b,	pp->shp_de_pre[6], \
															reg_lc_gain_t_w,	pp->shp_de_pre[7]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_03,			reg_tgenc_gain_t_b,	pp->shp_de_pre[8], \
															reg_tgenc_gain_t_w,	pp->shp_de_pre[9]);

				PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_de_pre\n"\
				"shp_de_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9]);
			}
		}
		#else
		{
			LX_PE_SHP_SR_DE2_T *pp=(LX_PE_SHP_SR_DE2_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_SHP_M17C0_QRd02(shp_coring_ctrl_09,	reg_mpc_gain_t_b,	pp->shp_de[0], \
														reg_mpc_gain_t_w,	pp->shp_de[1]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_01,		reg_spc_gain_t_b,	pp->shp_de[2], \
														reg_spc_gain_t_w,	pp->shp_de[3]);
				PE_SR_SHP_M17C0_QRd02(shp_dp_ctrl_02,		reg_ptic_gain_t_b,	pp->shp_de[4], \
														reg_ptic_gain_t_w,	pp->shp_de[5]);
			}
			{
			UINT8 *pd = pp->shp_de;
			PE_SHP_HW_M17C0_DBG_PRINT("get[%d] : shp_de_pre\n"\
			"shp_de_post[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
			}
		}
		#endif
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set pbl(pre blur dnr) apply
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M17C0_SetPblApply(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_SHP_HW_M17C0_CROSS_PAT_DETECT
	UINT32 is_pattern;
	LX_PE_INF_DISPLAY_T cur0_inf;
	UINT32 shp_bypass;
	UINT32 data_shp;
	UINT32 histo_bin[32];
	UINT32 s_bin[32];
	static UINT32 f_cross_hat_pattern;
	static UINT32 f_cross_hat_pattern_inv;
	static UINT32 f_cross_pattern;
	static UINT32 f_cross_pattern_inv;
	UINT32 hist_low, hist_mid, hist_high;
	static UINT32 count = 0;
	
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_M17CX)
		{
			if(g_pe_inf_m17c0_vr360_mode)
			{
				is_pattern =0;
			}
			else
			{
#ifdef INCLUDE_KDRV_AFE
				is_pattern = (g_CVD_Pattern_Detection_t.static_pattern_found ||\
							g_CVD_Pattern_Detection_t.pattern_found);
#endif
			}
			ret = PE_INF_M17C0_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
			ret = PE_HST_HW_M17C0_GetSrcHistoBin(0, histo_bin, 0);//Y
			ret = PE_HST_HW_M17C0_GetSrcHistoBin(0, s_bin, 7);//S
			hist_low = histo_bin[0]+histo_bin[1]+histo_bin[2]+histo_bin[3]+histo_bin[4]+histo_bin[5]+histo_bin[6]+histo_bin[7];
			hist_mid = histo_bin[8]+histo_bin[9]+histo_bin[10]+histo_bin[11]+histo_bin[12]+histo_bin[13]+histo_bin[13]+histo_bin[14]\
				   +histo_bin[15]+histo_bin[16]+histo_bin[17]+histo_bin[18]+histo_bin[19]+histo_bin[20]+histo_bin[21]+histo_bin[22];
			hist_high = histo_bin[23]+histo_bin[24]+histo_bin[25]+histo_bin[26]+histo_bin[27]+histo_bin[28]+histo_bin[29]+histo_bin[30];
#if 0
			//3. cross hatch
			if((s_bin[0]+s_bin[1])>160000 && \
				((histo_bin[1]+histo_bin[2]+histo_bin[3])>160000 ||(histo_bin[0]+histo_bin[1]+histo_bin[2])>130000) &&\
				((histo_bin[28]+histo_bin[29]+histo_bin[30])>8000 ||(histo_bin[24]+histo_bin[25]+histo_bin[26]+histo_bin[27])>8000))
			{
				f_cross_hat_pattern = 1;
			}
			else
			{
				f_cross_hat_pattern = 0;
			}
#else
			if((s_bin[0]+s_bin[1])>130000 && (hist_low > 120000) && (hist_high > 8000) && (hist_mid < 30000) )
			{
				f_cross_hat_pattern = 1;
			}
			else if( (f_cross_hat_pattern == 1) && ((s_bin[0]+s_bin[1]) < 100000 || (hist_low < 100000) || (hist_high < 6000)) )
			{
				f_cross_hat_pattern = 0;
			}
			else
			{
				f_cross_hat_pattern = 0;
			}

			if((s_bin[0]+s_bin[1])>130000 && (hist_high > 120000) && (hist_low > 8000) && (hist_mid < 30000) )
			{
				f_cross_hat_pattern_inv = 1;
			}
			else if( (f_cross_hat_pattern_inv == 1) && ((s_bin[0]+s_bin[1]) < 100000 || (hist_high < 100000) || (hist_low < 6000)) )
			{
				f_cross_hat_pattern_inv = 0;
			}
			else
			{
				f_cross_hat_pattern_inv = 0;
			}

			if((s_bin[0]+s_bin[1])>130000 && (hist_low > 150000) && (hist_high < 4000) && (hist_mid < 4000) )
			{
				f_cross_pattern = 1;
			}
			else if( (f_cross_pattern == 1) && ((s_bin[0]+s_bin[1]) < 100000 || (hist_low < 120000) || (hist_high > 6000)) )
			{
				f_cross_pattern = 0;
			}
			else
			{
				f_cross_pattern = 0;
			}

			if((s_bin[0]+s_bin[1])>130000 && (hist_high > 150000) && (hist_low < 4000) && (hist_mid < 4000) )
			{
				f_cross_pattern_inv = 1;
			}
			else if( (f_cross_pattern_inv == 1) && ((s_bin[0]+s_bin[1]) < 100000 || (hist_high < 120000) || (hist_low > 6000)) )
			{
				f_cross_pattern_inv = 0;
			}
			else
			{
				f_cross_pattern_inv = 0;
			}

#endif
			if((cur0_inf.src_type == LX_PE_SRC_ATV) && is_pattern)
			{
				//cross hatch
				if( (f_cross_hat_pattern == 0x1) || (f_cross_hat_pattern_inv == 0x1) || (f_cross_pattern == 0x1) || (f_cross_pattern_inv == 0x1))
				{
				 	data_shp = 0x10;
				}
				else
				{
					data_shp = 0x8;
				}
				shp_bypass = 0x1;
			}
			else
			{
				data_shp = _g_pe_srs_hw_param_data_m17c0.reg_dflt.data->shp_derh_ctrl_05.reg_derh_th_gain_edge;
				shp_bypass = 0x0;
			}
			if(_g_shp_hw_m17c0_trace)
			{
				if(count>32)
				{
					PE_SHP_HW_M17C0_DBG_PRINT("s: %d\n",(s_bin[0]+s_bin[1]) );
#ifdef INCLUDE_KDRV_AFE
					PE_SHP_HW_M17C0_DBG_PRINT("pattern :%d, static :%d, colorbar : %d\n", \
							is_pattern, g_CVD_Pattern_Detection_t.static_pattern_found,g_CVD_Pattern_Detection_t.pattern_found );
#endif
					PE_SHP_HW_M17C0_DBG_PRINT("low :%d, mid :%d, high : %d\n",hist_low, hist_mid,hist_high );
					PE_SHP_HW_M17C0_DBG_PRINT("cross_hat :%d, cross_hat_inv :%d, cross : %d, cross_inv : %d\n"\
							,f_cross_hat_pattern, f_cross_hat_pattern_inv,f_cross_pattern, f_cross_pattern_inv);
					PE_SHP_HW_M17C0_DBG_PRINT("pre :%d, curr :%d\n", data_shp,_g_pre_data_shp );
					PE_SHP_HW_M17C0_DBG_PRINT("bypass pre :%d, curr :%d\n", shp_bypass,_g_pre_shp_bypass );
					count=0;
				}
				count++;
			}
			if(data_shp != _g_pre_data_shp)
			{
				PE_SHP_HW_M17C0_SR_SHP_WR01(shp_derh_ctrl_05, reg_derh_th_gain_edge, GET_BITS(data_shp, 0,6));
				_g_pre_data_shp = data_shp;
			}
			if(shp_bypass !=GET_BITS(_g_pre_shp_bypass,0,1) )
			{
				PE_SHP_M17C0_QWr01(shp_core_ctrl_00,	reg_top_bypass,		GET_BITS(shp_bypass,0,1));
				_g_pre_shp_bypass = shp_bypass;
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	return ret;
}

/**
 * download scl db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M17C0_DownloadSclDb(void)
{
	int ret = RET_OK;
 	do{
		/* t12_m **************************************************************/
		ret = PE_SHP_HW_M17C0_DownloadScl12tMainDb();
		PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_M17C0_DownloadScl12tMainDb() error.\n",__F__,__L__);
		/* t08_m **************************************************************/
		ret = PE_SHP_HW_M17C0_DownloadScl08tMainDb();
		PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_M17C0_DownloadScl08tMainDb() error.\n",__F__,__L__);
		/* t04_m **************************************************************/
		ret = PE_SHP_HW_M17C0_DownloadScl04tMainDb();
		PE_SHP_HW_M17C0_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_M17C0_DownloadScl04tMainDb() error.\n",__F__,__L__);
	}while (0);
 	return ret;
}

/**
 * download scl 12t main db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_HW_M17C0_DownloadScl12tMainDb(void)
{
	int ret = RET_OK;
 	UINT32 size = 0, i = 0;
	UINT32 sec_typ_1212 = 0, sec_typ_1206 = 0,sec_typ_1204 = 0, sec_typ_1202 = 0;
	UINT32 base_line_1212[PE_DDR_M17C0_1212T_FLT_NUM];
	UINT32 base_line_1206[PE_DDR_M17C0_1206T_FLT_NUM];
	UINT32 base_line_1204[PE_DDR_M17C0_1204T_FLT_NUM];
	UINT32 base_line_1202[PE_DDR_M17C0_1202T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_M17C0_T *p_phys_db = gPE_DDR_DB_M17C0.phys.data;
	volatile UINT32 *p_t1212_data = p_phys_db->t1212.data;
	volatile UINT32 *p_t1206_data = p_phys_db->t1206.data;
	volatile UINT32 *p_t1204_data = p_phys_db->t1204.data;
	volatile UINT32 *p_t1202_data = p_phys_db->t1202.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t1212_data);
		CHECK_KNULL(p_t1206_data);
		CHECK_KNULL(p_t1204_data);
		CHECK_KNULL(p_t1202_data);
		if (PE_KDRV_VER_M17CX)
		{
			/*1. 1212  */
			sec_typ_1212 = PE_DDR_M17C0_SEC_SCL_1212T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1212].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1212].header.sec_type  = sec_typ_1212;
			p_shdw_db->sec_d[sec_typ_1212].header.item_num  = PE_DDR_M17C0_1212T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1212].header.item_size = PE_DDR_M17C0_SCL_12T_FLT_SIZE;
			p_phys_db->t1212.header.version   = p_shdw_db->sec_d[sec_typ_1212].header.version;
			p_phys_db->t1212.header.sec_type  = p_shdw_db->sec_d[sec_typ_1212].header.sec_type;
			p_phys_db->t1212.header.item_num  = p_shdw_db->sec_d[sec_typ_1212].header.item_num;
			p_phys_db->t1212.header.item_size = p_shdw_db->sec_d[sec_typ_1212].header.item_size;

			/* data */
			size = (PE_DDR_M17C0_1212T_FLT_NUM * PE_DDR_M17C0_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1212] = \
				p_shdw_db->top_h.sec_base[sec_typ_1212-1]+p_shdw_db->top_h.sec_size[sec_typ_1212-1];
			p_shdw_db->top_h.sec_size[sec_typ_1212] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1212] = p_shdw_db->top_h.sec_base[sec_typ_1212];
			p_phys_db->top_h.sec_size[sec_typ_1212] = p_shdw_db->top_h.sec_size[sec_typ_1212];
			p_shdw_db->sec_d[sec_typ_1212].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1212] + sizeof(PE_DDR_M17C0_HEADER_T);


			/*2. 1206*/
			sec_typ_1206 = PE_DDR_M17C0_SEC_SCL_1206T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1206].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1206].header.sec_type  = sec_typ_1206;
			p_shdw_db->sec_d[sec_typ_1206].header.item_num  = PE_DDR_M17C0_1206T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1206].header.item_size = PE_DDR_M17C0_SCL_12T_FLT_SIZE;
			p_phys_db->t1206.header.version   = p_shdw_db->sec_d[sec_typ_1206].header.version;
			p_phys_db->t1206.header.sec_type  = p_shdw_db->sec_d[sec_typ_1206].header.sec_type;
			p_phys_db->t1206.header.item_num  = p_shdw_db->sec_d[sec_typ_1206].header.item_num;
			p_phys_db->t1206.header.item_size = p_shdw_db->sec_d[sec_typ_1206].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_1206T_FLT_NUM * PE_DDR_M17C0_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1206] = \
				p_shdw_db->top_h.sec_base[sec_typ_1206-1]+p_shdw_db->top_h.sec_size[sec_typ_1206-1];
			p_shdw_db->top_h.sec_size[sec_typ_1206] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1206] = p_shdw_db->top_h.sec_base[sec_typ_1206];
			p_phys_db->top_h.sec_size[sec_typ_1206] = p_shdw_db->top_h.sec_size[sec_typ_1206];
			p_shdw_db->sec_d[sec_typ_1206].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1206] + sizeof(PE_DDR_M17C0_HEADER_T);

			/*3. 1204*/
			sec_typ_1204 = PE_DDR_M17C0_SEC_SCL_1204T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1204].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1204].header.sec_type  = sec_typ_1204;
			p_shdw_db->sec_d[sec_typ_1204].header.item_num  = PE_DDR_M17C0_1204T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1204].header.item_size = PE_DDR_M17C0_SCL_12T_FLT_SIZE;
			p_phys_db->t1204.header.version   = p_shdw_db->sec_d[sec_typ_1204].header.version;
			p_phys_db->t1204.header.sec_type  = p_shdw_db->sec_d[sec_typ_1204].header.sec_type;
			p_phys_db->t1204.header.item_num  = p_shdw_db->sec_d[sec_typ_1204].header.item_num;
			p_phys_db->t1204.header.item_size = p_shdw_db->sec_d[sec_typ_1204].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_1204T_FLT_NUM * PE_DDR_M17C0_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1204] = \
				p_shdw_db->top_h.sec_base[sec_typ_1204-1]+p_shdw_db->top_h.sec_size[sec_typ_1204-1];
			p_shdw_db->top_h.sec_size[sec_typ_1204] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1204] = p_shdw_db->top_h.sec_base[sec_typ_1204];
			p_phys_db->top_h.sec_size[sec_typ_1204] = p_shdw_db->top_h.sec_size[sec_typ_1204];
			p_shdw_db->sec_d[sec_typ_1204].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1204] + sizeof(PE_DDR_M17C0_HEADER_T);

			/*4. 1202*/
			sec_typ_1202 = PE_DDR_M17C0_SEC_SCL_1202T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1202].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1202].header.sec_type  = sec_typ_1202;
			p_shdw_db->sec_d[sec_typ_1202].header.item_num  = PE_DDR_M17C0_1202T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1202].header.item_size = PE_DDR_M17C0_SCL_12T_FLT_SIZE;
			p_phys_db->t1202.header.version   = p_shdw_db->sec_d[sec_typ_1202].header.version;
			p_phys_db->t1202.header.sec_type  = p_shdw_db->sec_d[sec_typ_1202].header.sec_type;
			p_phys_db->t1202.header.item_num  = p_shdw_db->sec_d[sec_typ_1202].header.item_num;
			p_phys_db->t1202.header.item_size = p_shdw_db->sec_d[sec_typ_1202].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_1202T_FLT_NUM * PE_DDR_M17C0_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1202] = \
				p_shdw_db->top_h.sec_base[sec_typ_1202-1]+p_shdw_db->top_h.sec_size[sec_typ_1202-1];
			p_shdw_db->top_h.sec_size[sec_typ_1202] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1202] = p_shdw_db->top_h.sec_base[sec_typ_1202];
			p_phys_db->top_h.sec_size[sec_typ_1202] = p_shdw_db->top_h.sec_size[sec_typ_1202];
			p_shdw_db->sec_d[sec_typ_1202].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1202] + sizeof(PE_DDR_M17C0_HEADER_T);

			/* wr ddr */
			base_line_1212[0] = 0;
			base_line_1206[0] = 0;
			base_line_1204[0] = 0;
			base_line_1202[0] = 0;
			for (i=1; i<PE_DDR_M17C0_1212T_FLT_NUM; i++)
			{
				base_line_1212[i] = base_line_1212[i-1]+PE_DDR_M17C0_SCL_12T_FLT_SIZE;
			}
			for (i=1; i<PE_DDR_M17C0_1206T_FLT_NUM; i++)
			{
				base_line_1206[i] = base_line_1206[i-1]+PE_DDR_M17C0_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_M17C0_1204T_FLT_NUM; i++)
			{
				base_line_1204[i] = base_line_1204[i-1]+PE_DDR_M17C0_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_M17C0_1202T_FLT_NUM; i++)
			{
				base_line_1202[i] = base_line_1202[i-1]+PE_DDR_M17C0_SCL_12T_FLT_SIZE;;
			}
			for (i=0; i<PE_DDR_M17C0_SCL_12T_FLT_SIZE; i++)
			{
				//1212
				p_t1212_data[base_line_1212[0]+i]  = scl_p256_1212t_flt_0004[i].data;
				p_t1212_data[base_line_1212[1]+i]  = scl_p256_1212t_flt_0006[i].data;
				p_t1212_data[base_line_1212[2]+i]  = scl_p256_1212t_flt_0104[i].data;
				p_t1212_data[base_line_1212[3]+i]  = scl_p256_1212t_flt_0304[i].data;
				p_t1212_data[base_line_1212[4]+i]  = scl_p256_1212t_flt_0306[i].data;
				p_t1212_data[base_line_1212[5]+i]  = scl_p256_1212t_flt_0404[i].data;
				p_t1212_data[base_line_1212[6]+i]  = scl_p256_1212t_flt_0406[i].data;
				p_t1212_data[base_line_1212[7]+i]  = scl_p256_1212t_flt_0606[i].data;
				p_t1212_data[base_line_1212[8]+i]  = scl_p256_1212t_flt_0806[i].data;
				p_t1212_data[base_line_1212[9]+i]  = scl_p256_1212t_flt_0808[i].data;
				p_t1212_data[base_line_1212[10]+i] = scl_p256_1212t_flt_1006[i].data;
				p_t1212_data[base_line_1212[11]+i] = scl_p256_1212t_flt_1410[i].data;
				p_t1212_data[base_line_1212[12]+i] = scl_p256_1212t_flt_1410[i].data;//dummy
				p_t1212_data[base_line_1212[13]+i] = scl_p256_1212t_flt_1410[i].data;//dummy
				//1206
				p_t1206_data[base_line_1206[0]+i]  = scl_p256_1206t_flt_0006[i].data;
				p_t1206_data[base_line_1206[1]+i]  = scl_p256_1206t_flt_0306[i].data;
				p_t1206_data[base_line_1206[2]+i]  = scl_p256_1206t_flt_0610[i].data;
				p_t1206_data[base_line_1206[3]+i]  = scl_p256_1206t_flt_0306[i].data;//dummy
				//1204
				p_t1204_data[base_line_1204[0]+i]  = scl_p256_1204t_flt_0006[i].data;
				p_t1204_data[base_line_1204[1]+i]  = scl_p256_1204t_flt_0008[i].data;
				p_t1204_data[base_line_1204[2]+i]  = scl_p256_1204t_flt_0308[i].data;
				p_t1204_data[base_line_1204[3]+i]  = scl_p256_1204t_flt_0406[i].data;
				p_t1204_data[base_line_1204[4]+i]  = scl_p256_1204t_flt_0606[i].data;
				p_t1204_data[base_line_1204[5]+i]  = scl_p256_1204t_flt_0808[i].data;
				p_t1204_data[base_line_1204[6]+i]  = scl_p256_1204t_flt_0910[i].data;
				p_t1204_data[base_line_1204[7]+i]  = scl_p256_1204t_flt_1410[i].data;
				p_t1204_data[base_line_1204[8]+i]  = scl_p256_1204t_flt_1510[i].data;
				p_t1204_data[base_line_1204[9]+i]  = scl_p256_1204t_flt_1510[i].data;//dummy
				p_t1204_data[base_line_1204[10]+i] = scl_p256_1204t_flt_1510[i].data;//dummy
				//1202
				p_t1202_data[base_line_1202[0]+i]  = scl_p256_1202t_flt_0308[i].data;
				p_t1202_data[base_line_1202[1]+i]  = scl_p256_1202t_flt_0308[i].data;//dummy
				p_t1202_data[base_line_1202[2]+i]  = scl_p256_1202t_flt_0308[i].data;//dummy
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ_1212), p_shdw_db->top_h.sec_base[sec_typ_1212]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ_1206), p_shdw_db->top_h.sec_base[sec_typ_1206]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ_1204), p_shdw_db->top_h.sec_base[sec_typ_1204]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ_1202), p_shdw_db->top_h.sec_base[sec_typ_1202]);
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
 	return ret;
}

/**
 * download scl 08t main db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_HW_M17C0_DownloadScl08tMainDb(void)
{
	int ret = RET_OK;
 	UINT32 size = 0, i = 0, sec_typ_0804 = 0;
	UINT32 base_line_0804[PE_DDR_M17C0_0804T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_M17C0_T *p_phys_db = gPE_DDR_DB_M17C0.phys.data;
	volatile UINT32 *p_t08_f_data = p_phys_db->t0804.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t08_f_data);
		if (PE_KDRV_VER_M17CX)
		{
			/*1. 8t full */
			sec_typ_0804 = PE_DDR_M17C0_SEC_SCL_0804T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0804].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0804].header.sec_type  = sec_typ_0804;
			p_shdw_db->sec_d[sec_typ_0804].header.item_num  = PE_DDR_M17C0_0804T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0804].header.item_size = PE_DDR_M17C0_SCL_08T_FLT_SIZE;
			p_phys_db->t0804.header.version   = p_shdw_db->sec_d[sec_typ_0804].header.version;
			p_phys_db->t0804.header.sec_type  = p_shdw_db->sec_d[sec_typ_0804].header.sec_type;
			p_phys_db->t0804.header.item_num  = p_shdw_db->sec_d[sec_typ_0804].header.item_num;
			p_phys_db->t0804.header.item_size = p_shdw_db->sec_d[sec_typ_0804].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_0804T_FLT_NUM * PE_DDR_M17C0_SCL_08T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0804] = \
				p_shdw_db->top_h.sec_base[sec_typ_0804-1]+p_shdw_db->top_h.sec_size[sec_typ_0804-1];
			p_shdw_db->top_h.sec_size[sec_typ_0804] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0804] = p_shdw_db->top_h.sec_base[sec_typ_0804];
			p_phys_db->top_h.sec_size[sec_typ_0804] = p_shdw_db->top_h.sec_size[sec_typ_0804];
			p_shdw_db->sec_d[sec_typ_0804].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0804] + sizeof(PE_DDR_M17C0_HEADER_T);

			/* wr ddr */
			base_line_0804[0] = 0;
			for (i=1; i<PE_DDR_M17C0_0804T_FLT_NUM; i++)
			{
				base_line_0804[i] = base_line_0804[i-1]+PE_DDR_M17C0_SCL_08T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_M17C0_SCL_08T_FLT_SIZE; i++)
			{
				p_t08_f_data[base_line_0804[0]+i]  = scl_p256_0804t_flt_0008[i].data;
				p_t08_f_data[base_line_0804[1]+i]  = scl_p256_0804t_flt_0308[i].data;
				p_t08_f_data[base_line_0804[2]+i]  = scl_p256_0804t_flt_0910[i].data;
				p_t08_f_data[base_line_0804[3]+i]  = scl_p256_0804t_flt_1410[i].data;
				p_t08_f_data[base_line_0804[4]+i]  = scl_p256_0804t_flt_1510[i].data;
				p_t08_f_data[base_line_0804[5]+i]  = scl_p256_0804t_flt_0610[i].data;
				p_t08_f_data[base_line_0804[6]+i]  = scl_p256_0804t_flt_1510[i].data;//dummy
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ_0804), p_shdw_db->top_h.sec_base[sec_typ_0804]);
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
 	return ret;
}

/**
 * download scl 04t main db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_HW_M17C0_DownloadScl04tMainDb(void)
{
	int ret = RET_OK;
 	UINT32 size = 0, i = 0;
	UINT32 sec_typ_0404 = 0, sec_typ_0402 = 0;
	UINT32 base_line_0404[PE_DDR_M17C0_0404T_FLT_NUM];
	UINT32 base_line_0402[PE_DDR_M17C0_0402T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_M17C0_T *p_phys_db = gPE_DDR_DB_M17C0.phys.data;
	volatile UINT32 *p_t0404_data = p_phys_db->t0404.data;
	volatile UINT32 *p_t0402_data = p_phys_db->t0402.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t0404_data);
		CHECK_KNULL(p_t0402_data);
		if (PE_KDRV_VER_M17CX)
		{
			/*1. 404t */
			sec_typ_0404 = PE_DDR_M17C0_SEC_SCL_0404T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0404].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0404].header.sec_type  = sec_typ_0404;
			p_shdw_db->sec_d[sec_typ_0404].header.item_num  = PE_DDR_M17C0_0404T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0404].header.item_size = PE_DDR_M17C0_SCL_04T_FLT_SIZE;
			p_phys_db->t0404.header.version   = p_shdw_db->sec_d[sec_typ_0404].header.version;
			p_phys_db->t0404.header.sec_type  = p_shdw_db->sec_d[sec_typ_0404].header.sec_type;
			p_phys_db->t0404.header.item_num  = p_shdw_db->sec_d[sec_typ_0404].header.item_num;
			p_phys_db->t0404.header.item_size = p_shdw_db->sec_d[sec_typ_0404].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_0404T_FLT_NUM * PE_DDR_M17C0_SCL_04T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0404] = \
				p_shdw_db->top_h.sec_base[sec_typ_0404-1]+p_shdw_db->top_h.sec_size[sec_typ_0404-1];
			p_shdw_db->top_h.sec_size[sec_typ_0404] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0404] = p_shdw_db->top_h.sec_base[sec_typ_0404];
			p_phys_db->top_h.sec_size[sec_typ_0404] = p_shdw_db->top_h.sec_size[sec_typ_0404];
			p_shdw_db->sec_d[sec_typ_0404].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0404] + sizeof(PE_DDR_M17C0_HEADER_T);

			/*2. 402t  */
			sec_typ_0402 = PE_DDR_M17C0_SEC_SCL_0402T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0402].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0402].header.sec_type  = sec_typ_0402;
			p_shdw_db->sec_d[sec_typ_0402].header.item_num  = PE_DDR_M17C0_0402T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0402].header.item_size = PE_DDR_M17C0_SCL_04T_FLT_SIZE;
			p_phys_db->t0402.header.version   = p_shdw_db->sec_d[sec_typ_0402].header.version;
			p_phys_db->t0402.header.sec_type  = p_shdw_db->sec_d[sec_typ_0402].header.sec_type;
			p_phys_db->t0402.header.item_num  = p_shdw_db->sec_d[sec_typ_0402].header.item_num;
			p_phys_db->t0402.header.item_size = p_shdw_db->sec_d[sec_typ_0402].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_0402T_FLT_NUM * PE_DDR_M17C0_SCL_04T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0402] = \
				p_shdw_db->top_h.sec_base[sec_typ_0402-1]+p_shdw_db->top_h.sec_size[sec_typ_0402-1];
			p_shdw_db->top_h.sec_size[sec_typ_0402] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0402] = p_shdw_db->top_h.sec_base[sec_typ_0402];
			p_phys_db->top_h.sec_size[sec_typ_0402] = p_shdw_db->top_h.sec_size[sec_typ_0402];
			p_shdw_db->sec_d[sec_typ_0402].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0402] + sizeof(PE_DDR_M17C0_HEADER_T);
			/* wr ddr */
			base_line_0404[0] = 0;
			for (i=1; i<PE_DDR_M17C0_0404T_FLT_NUM; i++)
			{
				base_line_0404[i] = base_line_0404[i-1]+PE_DDR_M17C0_SCL_04T_FLT_SIZE;
			}
			base_line_0402[0] = 0;
			for (i=1; i<PE_DDR_M17C0_0402T_FLT_NUM; i++)
			{
				base_line_0402[i] = base_line_0402[i-1]+PE_DDR_M17C0_SCL_04T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_M17C0_SCL_04T_FLT_SIZE; i++)
			{
				p_t0404_data[base_line_0404[0]+i] = scl_p256_0404t_flt_0308[i].data;
				p_t0404_data[base_line_0404[1]+i] = scl_p256_0404t_flt_0910[i].data;
				p_t0404_data[base_line_0404[2]+i] = scl_p256_0404t_flt_1410[i].data;
				p_t0404_data[base_line_0404[3]+i] = scl_p256_0404t_flt_1510[i].data;
				p_t0404_data[base_line_0404[4]+i] = scl_p256_0404t_flt_0610[i].data;
				p_t0404_data[base_line_0404[5]+i] = scl_p256_0404t_flt_1510[i].data;//dummy
				p_t0402_data[base_line_0402[0]+i] = scl_p256_0402t_flt_0308[i].data;
				p_t0402_data[base_line_0402[1]+i] = scl_p256_0402t_flt_0308[i].data;//dummy
				p_t0402_data[base_line_0402[2]+i] = scl_p256_0402t_flt_0308[i].data;//dummy
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ_0404), p_shdw_db->top_h.sec_base[sec_typ_0404]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ_0402), p_shdw_db->top_h.sec_base[sec_typ_0402]);
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
 	return ret;
}


/**
 * set Psp
 * - use input struct LX_PE_SHP_PSP_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_SetPspCtrl(LX_PE_SHP_PSP_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_SHP_PSP_T *pp = pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_HW_M17C0_DBG_PRINT("PSP ctrl: iir_en:%d, psp_en:%d, chrm_protect_en:%d\n"\
			"map_master_gain:%d,iir_gain:%d, cb \\ cr_offset_gain:%d,%d\n"\
			"posi_lut_x: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
			"posi_lut_y: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
			"psp_lut_x: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
			"psp_lut_y: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
			pstParams->iir_en, pstParams->psp_en, pstParams->chroma_protection_en, \
			pstParams->map_master_gain, pstParams->iir_gain, pstParams->cb_offset_gain, pstParams->cr_offset_gain, \
			pstParams->position_lut_x[0],pstParams->position_lut_x[1],pstParams->position_lut_x[2],pstParams->position_lut_x[3], \
			pstParams->position_lut_x[4],pstParams->position_lut_x[5],pstParams->position_lut_x[6],pstParams->position_lut_x[7], \
			pstParams->position_lut_x[8],pstParams->position_lut_x[9],pstParams->position_lut_x[10],pstParams->position_lut_x[11], \
			pstParams->position_lut_x[12],pstParams->position_lut_x[13],pstParams->position_lut_x[14],pstParams->position_lut_x[15], \
			pstParams->position_lut_y[0],pstParams->position_lut_y[1],pstParams->position_lut_y[2],pstParams->position_lut_y[3], \
			pstParams->position_lut_y[4],pstParams->position_lut_y[5],pstParams->position_lut_y[6],pstParams->position_lut_y[7], \
			pstParams->position_lut_y[8],pstParams->position_lut_y[9],pstParams->position_lut_y[10],pstParams->position_lut_y[11], \
			pstParams->position_lut_y[12],pstParams->position_lut_y[13],pstParams->position_lut_y[14],pstParams->position_lut_y[15], \
			pstParams->psp_lut_x[0],pstParams->psp_lut_x[1],pstParams->psp_lut_x[2],pstParams->psp_lut_x[3], \
			pstParams->psp_lut_x[4],pstParams->psp_lut_x[5],pstParams->psp_lut_x[6],pstParams->psp_lut_x[7], \
			pstParams->psp_lut_x[8],pstParams->psp_lut_x[9],pstParams->psp_lut_x[10],pstParams->psp_lut_x[11], \
			pstParams->psp_lut_x[12],pstParams->psp_lut_x[13],pstParams->psp_lut_x[14],pstParams->psp_lut_x[15],pstParams->psp_lut_x[16], \
			pstParams->psp_lut_y[0],pstParams->psp_lut_y[1],pstParams->psp_lut_y[2],pstParams->psp_lut_y[3], \
			pstParams->psp_lut_y[4],pstParams->psp_lut_y[5],pstParams->psp_lut_y[6],pstParams->psp_lut_y[7],\
			pstParams->psp_lut_y[8],pstParams->psp_lut_y[9],pstParams->psp_lut_y[10],pstParams->psp_lut_y[11], \
			pstParams->psp_lut_y[12],pstParams->psp_lut_y[13],pstParams->psp_lut_y[14],pstParams->psp_lut_y[15],pstParams->psp_lut_y[16]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_M17C0_QWr02(reg_perspect_gain_ctrl_0, 	iir_en, GET_BITS(pp->iir_en,0,1),\
																iir_gain, GET_BITS(pp->iir_gain,0,8));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_00, 		reg_psp_en, 				GET_BITS(pp->psp_en,0,1),\
															reg_chroma_protection_en, 	GET_BITS(pp->chroma_protection_en,0,1));
				PE_SHP_PSP_M17C0_QWr01(reg_psp_ctrl_01, 		reg_psp_map_master_gain, 	GET_BITS(pp->map_master_gain,0,8));
																
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_02, 		reg_cb_offset_gain, GET_BITS(pp->cb_offset_gain,0,10),\
															reg_cr_offset_gain, GET_BITS(pp->cr_offset_gain,0,10));
				PE_SHP_PSP_M17C0_QWr04(reg_perspect_lut_x_3, 	reg_position_lut_x_0, GET_BITS(pp->position_lut_x[0],0,8),\
															reg_position_lut_x_1, GET_BITS(pp->position_lut_x[1],0,8),\
															reg_position_lut_x_2, GET_BITS(pp->position_lut_x[2],0,8),\
															reg_position_lut_x_3, GET_BITS(pp->position_lut_x[3],0,8));
				PE_SHP_PSP_M17C0_QWr04(reg_perspect_lut_x_2, 	reg_position_lut_x_4, GET_BITS(pp->position_lut_x[4],0,8),\
															reg_position_lut_x_5, GET_BITS(pp->position_lut_x[5],0,8),\
															reg_position_lut_x_6, GET_BITS(pp->position_lut_x[6],0,8),\
															reg_position_lut_x_7, GET_BITS(pp->position_lut_x[7],0,8));
				PE_SHP_PSP_M17C0_QWr04(reg_perspect_lut_x_1, 	reg_position_lut_x_8, GET_BITS(pp->position_lut_x[8],0,8),\
															reg_position_lut_x_9, GET_BITS(pp->position_lut_x[9],0,8),\
															reg_position_lut_x_10, GET_BITS(pp->position_lut_x[10],0,8),\
															reg_position_lut_x_11, GET_BITS(pp->position_lut_x[11],0,8));
				PE_SHP_PSP_M17C0_QWr04(reg_perspect_lut_x_0, 	reg_position_lut_x_12, GET_BITS(pp->position_lut_x[12],0,8),\
															reg_position_lut_x_13, GET_BITS(pp->position_lut_x[13],0,8),\
															reg_position_lut_x_14, GET_BITS(pp->position_lut_x[14],0,8),\
															reg_position_lut_x_15, GET_BITS(pp->position_lut_x[15],0,8));
				
				PE_SHP_PSP_M17C0_QWr04(reg_perspect_lut_y_3, 	reg_position_lut_y_0, GET_BITS(pp->position_lut_y[0],0,8),\
															reg_position_lut_y_1, GET_BITS(pp->position_lut_y[1],0,8),\
															reg_position_lut_y_2, GET_BITS(pp->position_lut_y[2],0,8),\
															reg_position_lut_y_3, GET_BITS(pp->position_lut_y[3],0,8));
				PE_SHP_PSP_M17C0_QWr04(reg_perspect_lut_y_2, 	reg_position_lut_y_4, GET_BITS(pp->position_lut_y[4],0,8),\
															reg_position_lut_y_5, GET_BITS(pp->position_lut_y[5],0,8),\
															reg_position_lut_y_6, GET_BITS(pp->position_lut_y[6],0,8),\
															reg_position_lut_y_7, GET_BITS(pp->position_lut_y[7],0,8));
				PE_SHP_PSP_M17C0_QWr04(reg_perspect_lut_y_1, 	reg_position_lut_y_8,  GET_BITS(pp->position_lut_y[8],0,8),\
															reg_position_lut_y_9,  GET_BITS(pp->position_lut_y[9],0,8),\
															reg_position_lut_y_10, GET_BITS(pp->position_lut_y[10],0,8),\
															reg_position_lut_y_11, GET_BITS(pp->position_lut_y[11],0,8));
				PE_SHP_PSP_M17C0_QWr04(reg_perspect_lut_y_0, 	reg_position_lut_y_12, GET_BITS(pp->position_lut_y[12],0,8),\
															reg_position_lut_y_13, GET_BITS(pp->position_lut_y[13],0,8),\
															reg_position_lut_y_14, GET_BITS(pp->position_lut_y[14],0,8),\
															reg_position_lut_y_15, GET_BITS(pp->position_lut_y[15],0,8));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_05, 	reg_psp_lut_x0, GET_BITS(pp->psp_lut_x[0],0,10),\
														reg_psp_lut_y0, GET_BITS(pp->psp_lut_y[0],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_06, 	reg_psp_lut_x1, GET_BITS(pp->psp_lut_x[1],0,10),\
														reg_psp_lut_y1, GET_BITS(pp->psp_lut_y[1],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_07, 	reg_psp_lut_x2, GET_BITS(pp->psp_lut_x[2],0,10),\
														reg_psp_lut_y2, GET_BITS(pp->psp_lut_y[2],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_08, 	reg_psp_lut_x3, GET_BITS(pp->psp_lut_x[3],0,10),\
														reg_psp_lut_y3, GET_BITS(pp->psp_lut_y[3],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_09, 	reg_psp_lut_x4, GET_BITS(pp->psp_lut_x[4],0,10),\
														reg_psp_lut_y4, GET_BITS(pp->psp_lut_y[4],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_10, 	reg_psp_lut_x5, GET_BITS(pp->psp_lut_x[5],0,10),\
														reg_psp_lut_y5, GET_BITS(pp->psp_lut_y[5],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_11, 	reg_psp_lut_x6, GET_BITS(pp->psp_lut_x[6],0,10),\
														reg_psp_lut_y6, GET_BITS(pp->psp_lut_y[6],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_12, 	reg_psp_lut_x7, GET_BITS(pp->psp_lut_x[7],0,10),\
														reg_psp_lut_y7, GET_BITS(pp->psp_lut_y[7],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_13, 	reg_psp_lut_x8,  GET_BITS(pp->psp_lut_x[8],0,10),\
														reg_psp_lut_y8,  GET_BITS(pp->psp_lut_y[8],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_14, 	reg_psp_lut_x9,  GET_BITS(pp->psp_lut_x[9],0,10),\
														reg_psp_lut_y9,  GET_BITS(pp->psp_lut_y[9],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_15, 	reg_psp_lut_x10, GET_BITS(pp->psp_lut_x[10],0,10),\
														reg_psp_lut_y10, GET_BITS(pp->psp_lut_y[10],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_16, 	reg_psp_lut_x11, GET_BITS(pp->psp_lut_x[11],0,10),\
														reg_psp_lut_y11, GET_BITS(pp->psp_lut_y[11],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_17, 	reg_psp_lut_x12, GET_BITS(pp->psp_lut_x[12],0,10),\
														reg_psp_lut_y12, GET_BITS(pp->psp_lut_y[12],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_18, 	reg_psp_lut_x13, GET_BITS(pp->psp_lut_x[13],0,10),\
														reg_psp_lut_y13, GET_BITS(pp->psp_lut_y[13],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_19, 	reg_psp_lut_x14, GET_BITS(pp->psp_lut_x[14],0,10),\
														reg_psp_lut_y14, GET_BITS(pp->psp_lut_y[14],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_20, 	reg_psp_lut_x15, GET_BITS(pp->psp_lut_x[15],0,10),\
														reg_psp_lut_y15, GET_BITS(pp->psp_lut_y[15],0,10));
				PE_SHP_PSP_M17C0_QWr02(reg_psp_ctrl_21, 	reg_psp_lut_x16, GET_BITS(pp->psp_lut_x[16],0,10),\
														reg_psp_lut_y16, GET_BITS(pp->psp_lut_y[16],0,10));
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * get Psp
 * - use input struct LX_PE_SHP_PSP_T for M17C0X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M17C0_GetPspCtrl(LX_PE_SHP_PSP_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_SHP_PSP_T *pp = pstParams;
			PE_CHECK_WINID(pp->win_id);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_M17C0_QRd02(reg_perspect_gain_ctrl_0, 	iir_en, 	pp->iir_en,\
																iir_gain, 	pp->iir_gain);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_00, 		reg_psp_en, 				pp->psp_en,\
															reg_chroma_protection_en, 	pp->chroma_protection_en);
				PE_SHP_PSP_M17C0_QRd01(reg_psp_ctrl_01, 		reg_psp_map_master_gain, 	pp->map_master_gain);
																
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_02, 		reg_cb_offset_gain, 	pp->cb_offset_gain,\
															reg_cr_offset_gain, 	pp->cr_offset_gain);
				PE_SHP_PSP_M17C0_QRd04(reg_perspect_lut_x_3, 	reg_position_lut_x_0, pp->position_lut_x[0],\
															reg_position_lut_x_1, pp->position_lut_x[1],\
															reg_position_lut_x_2, pp->position_lut_x[2],\
															reg_position_lut_x_3, pp->position_lut_x[3]);
				PE_SHP_PSP_M17C0_QRd04(reg_perspect_lut_x_2, 	reg_position_lut_x_4, pp->position_lut_x[4],\
															reg_position_lut_x_5, pp->position_lut_x[5],\
															reg_position_lut_x_6, pp->position_lut_x[6],\
															reg_position_lut_x_7, pp->position_lut_x[7]);
				PE_SHP_PSP_M17C0_QRd04(reg_perspect_lut_x_1, 	reg_position_lut_x_8,  pp->position_lut_x[8],\
															reg_position_lut_x_9,  pp->position_lut_x[9],\
															reg_position_lut_x_10, pp->position_lut_x[10],\
															reg_position_lut_x_11, pp->position_lut_x[11]);
				PE_SHP_PSP_M17C0_QRd04(reg_perspect_lut_x_0, 	reg_position_lut_x_12, pp->position_lut_x[12],\
															reg_position_lut_x_13, pp->position_lut_x[13],\
															reg_position_lut_x_14, pp->position_lut_x[14],\
															reg_position_lut_x_15, pp->position_lut_x[15]);
				
				PE_SHP_PSP_M17C0_QRd04(reg_perspect_lut_y_3, 	reg_position_lut_y_0, pp->position_lut_y[0],\
															reg_position_lut_y_1, pp->position_lut_y[1],\
															reg_position_lut_y_2, pp->position_lut_y[2],\
															reg_position_lut_y_3, pp->position_lut_y[3]);
				PE_SHP_PSP_M17C0_QRd04(reg_perspect_lut_y_2, 	reg_position_lut_y_4, pp->position_lut_y[4],\
															reg_position_lut_y_5, pp->position_lut_y[5],\
															reg_position_lut_y_6, pp->position_lut_y[6],\
															reg_position_lut_y_7, pp->position_lut_y[7]);
				PE_SHP_PSP_M17C0_QRd04(reg_perspect_lut_y_1, 	reg_position_lut_y_8,  pp->position_lut_y[8],\
															reg_position_lut_y_9,  pp->position_lut_y[9],\
															reg_position_lut_y_10, pp->position_lut_y[10],\
															reg_position_lut_y_11, pp->position_lut_y[11]);
				PE_SHP_PSP_M17C0_QRd04(reg_perspect_lut_y_0, 	reg_position_lut_y_12, pp->position_lut_y[12],\
															reg_position_lut_y_13, pp->position_lut_y[13],\
															reg_position_lut_y_14, pp->position_lut_y[14],\
															reg_position_lut_y_15, pp->position_lut_y[15]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_05, 	reg_psp_lut_x0, pp->psp_lut_x[0],\
														reg_psp_lut_y0, pp->psp_lut_y[0]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_06, 	reg_psp_lut_x1, pp->psp_lut_x[1],\
														reg_psp_lut_y1, pp->psp_lut_y[1]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_07, 	reg_psp_lut_x2, pp->psp_lut_x[2],\
														reg_psp_lut_y2, pp->psp_lut_y[2]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_08, 	reg_psp_lut_x3, pp->psp_lut_x[3],\
														reg_psp_lut_y3, pp->psp_lut_y[3]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_09, 	reg_psp_lut_x4, pp->psp_lut_x[4],\
														reg_psp_lut_y4, pp->psp_lut_y[4]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_10, 	reg_psp_lut_x5, pp->psp_lut_x[5],\
														reg_psp_lut_y5, pp->psp_lut_y[5]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_11, 	reg_psp_lut_x6, pp->psp_lut_x[6],\
														reg_psp_lut_y6, pp->psp_lut_y[6]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_12, 	reg_psp_lut_x7, pp->psp_lut_x[7],\
														reg_psp_lut_y7, pp->psp_lut_y[7]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_13, 	reg_psp_lut_x8, pp->psp_lut_x[8],\
														reg_psp_lut_y8, pp->psp_lut_y[8]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_14, 	reg_psp_lut_x9, pp->psp_lut_x[9],\
														reg_psp_lut_y9, pp->psp_lut_y[9]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_15, 	reg_psp_lut_x10, pp->psp_lut_x[10],\
														reg_psp_lut_y10, pp->psp_lut_y[10]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_16, 	reg_psp_lut_x11, pp->psp_lut_x[11],\
														reg_psp_lut_y11, pp->psp_lut_y[11]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_17, 	reg_psp_lut_x12, pp->psp_lut_x[12],\
														reg_psp_lut_y12, pp->psp_lut_y[12]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_18, 	reg_psp_lut_x13, pp->psp_lut_x[13],\
														reg_psp_lut_y13, pp->psp_lut_y[13]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_19, 	reg_psp_lut_x14, pp->psp_lut_x[14],\
														reg_psp_lut_y14, pp->psp_lut_y[14]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_20, 	reg_psp_lut_x15, pp->psp_lut_x[15],\
														reg_psp_lut_y15, pp->psp_lut_y[15]);
				PE_SHP_PSP_M17C0_QRd02(reg_psp_ctrl_21, 	reg_psp_lut_x16, pp->psp_lut_x[16],\
														reg_psp_lut_y16, pp->psp_lut_y[16]);
				PE_SHP_HW_M17C0_DBG_PRINT("PSP ctrl: iir_en:%d, psp_en:%d, chrm_protect_en:%d\n"\
				"map_master_gain:%d,iir_gain:%d, cb \\ cr_offset_gain:%d,%d\n"\
				"posi_lut_x: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
				"posi_lut_y: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
				"psp_lut_x: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"\
				"psp_lut_y: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",\
				pstParams->iir_en, pstParams->psp_en, pstParams->chroma_protection_en, \
				pstParams->map_master_gain, pstParams->iir_gain, pstParams->cb_offset_gain, pstParams->cr_offset_gain, \
				pstParams->position_lut_x[0],pstParams->position_lut_x[1],pstParams->position_lut_x[2],pstParams->position_lut_x[3], \
				pstParams->position_lut_x[4],pstParams->position_lut_x[5],pstParams->position_lut_x[6],pstParams->position_lut_x[7], \
				pstParams->position_lut_x[8],pstParams->position_lut_x[9],pstParams->position_lut_x[10],pstParams->position_lut_x[11], \
				pstParams->position_lut_x[12],pstParams->position_lut_x[13],pstParams->position_lut_x[14],pstParams->position_lut_x[15], \
				pstParams->position_lut_y[0],pstParams->position_lut_y[1],pstParams->position_lut_y[2],pstParams->position_lut_y[3], \
				pstParams->position_lut_y[4],pstParams->position_lut_y[5],pstParams->position_lut_y[6],pstParams->position_lut_y[7], \
				pstParams->position_lut_y[8],pstParams->position_lut_y[9],pstParams->position_lut_y[10],pstParams->position_lut_y[11], \
				pstParams->position_lut_y[12],pstParams->position_lut_y[13],pstParams->position_lut_y[14],pstParams->position_lut_y[15], \
				pstParams->psp_lut_x[0],pstParams->psp_lut_x[1],pstParams->psp_lut_x[2],pstParams->psp_lut_x[3], \
				pstParams->psp_lut_x[4],pstParams->psp_lut_x[5],pstParams->psp_lut_x[6],pstParams->psp_lut_x[7], \
				pstParams->psp_lut_x[8],pstParams->psp_lut_x[9],pstParams->psp_lut_x[10],pstParams->psp_lut_x[11], \
				pstParams->psp_lut_x[12],pstParams->psp_lut_x[13],pstParams->psp_lut_x[14],pstParams->psp_lut_x[15],pstParams->psp_lut_x[16], \
				pstParams->psp_lut_y[0],pstParams->psp_lut_y[1],pstParams->psp_lut_y[2],pstParams->psp_lut_y[3], \
				pstParams->psp_lut_y[4],pstParams->psp_lut_y[5],pstParams->psp_lut_y[6],pstParams->psp_lut_y[7],\
				pstParams->psp_lut_y[8],pstParams->psp_lut_y[9],pstParams->psp_lut_y[10],pstParams->psp_lut_y[11], \
				pstParams->psp_lut_y[12],pstParams->psp_lut_y[13],pstParams->psp_lut_y[14],pstParams->psp_lut_y[15],pstParams->psp_lut_y[16]);
			}
		}
		else
		{
			PE_SHP_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}


