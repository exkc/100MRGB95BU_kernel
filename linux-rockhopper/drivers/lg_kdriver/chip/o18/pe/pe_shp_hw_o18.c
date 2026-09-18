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

/** @file pe_shp_hw_o18.c
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
#undef PE_SHP_HW_O18_SR_PWD_TRACE

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

#include "pe_hw_o18.h"
#include "pe_reg_o18.h"
#include "pe_fwi_o18.h"
#include "pe_cmn_hw_o18.h"
#include "pe_hst_hw_o18.h"
#include "pe_shp_hw_o18.h"
#include "pe_res_hw_param_o18.h"
#include "pe_cti_dnr_hw_param_o18.h"
#include "pe_pblur_dnr_hw_param_o18.h"
#include "cvd_module.h"

/* core hw param */
#include "pe_shp_scl256_def.h"

#ifdef PE_SHP_HW_O18_SR_PWD_TRACE
#include "../../sys/sys_regs.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_HW_O18_FHD_H_MAX					1920
#define PE_SHP_HW_O18_FHD_V_MAX					1080
#define PE_SHP_HW_O18_SCL_IN_H_MIN				160
#define PE_SHP_HW_O18_SCL_IN_V_MIN				120
#define PE_SHP_HW_O18_IDX_Y_DFLT				15
#define PE_SHP_HW_O18_IDX_C_DFLT				39

#define PE_SHP_HW_O18_SCL_SIZE_MIN				(10)
#define PE_SHP_HW_O18_SCL_SIZE_1K				(1024)
#define PE_SHP_HW_O18_SCL_SIZE_2K				(2048)
#define PE_SHP_HW_O18_SCL_VSC_MD_V12TAP			(12)
#define PE_SHP_HW_O18_SCL_VSC_MD_V06TAP			(6)
#define PE_SHP_HW_O18_SCL_VSC_MD_V02TAP			(2)
#define PE_SHP_HW_O18_SCL_VSC_MD_V08TAP			(8)
#define PE_SHP_HW_O18_SCL_VSC_MD_V04TAP			(4)
#define PE_SHP_HW_O18_SCL_ADAPTIVE_ON			(0x1)
#define PE_SHP_HW_O18_SCL_ADAPTIVE_OFF			(0x0)
#define PE_SHP_HW_O18_SCL_BILINEAR				(0x1)
#define PE_SHP_HW_O18_SCL_POLYPHASE				(0x0)
#define PE_SHP_HW_O18_SCL_C_FMT_444				(0x6)
#define PE_SHP_HW_O18_SCL_C_FMT_422				(0x5)
#define PE_SHP_HW_O18_SCL_C_FMT_420				(0x4)
#define PE_SHP_HW_O18_SCL_PXL_RP_OFF			(0x0)
#define PE_SHP_HW_O18_SCL_PXL_RP_RED			(0x1)
#define PE_SHP_HW_O18_SCL_PXL_RP_GRN			(0x2)
#define PE_SHP_HW_O18_SCL_PXL_RP_BLU			(0x3)
#define PE_SHP_HW_O18_SCL_CO_REG_INC_MAX		(128)
#define PE_SHP_HW_O18_SCL_G0Y					0
#define PE_SHP_HW_O18_SCL_G1Y					1
#define PE_SHP_HW_O18_SCL_G0C					2
#define PE_SHP_HW_O18_SCL_G1C					3
#define PE_SHP_HW_O18_SCL_P0Y					4
#define PE_SHP_HW_O18_SCL_DWN_LVL_NORM			(0)
#define PE_SHP_HW_O18_SCL_DWN_LVL_HALF			(1)
#define PE_SHP_HW_O18_SCL_DWN_LVL_QUAD			(2)
#define PE_SHP_HW_O18_SCL_DWN_LVL_OCTA			(3)

/* h,v only(define) vs. both(undef), Now we use both mode until getting c08t scl has no problem. */
#define PE_SHP_HW_O18_USE_V12TM_C08T_SEPARATE_HV

/* use MSR vs. SSC on venc mode, We are going to use SSC from O18A0. */
#undef PE_SHP_HW_O18_USE_MSR_FOR_VENC_ON

/* use define until shp f/w ready, O18A0 */
#define PE_SHP_HW_O18A_SET_FW_PARAM_TO_REG_DIRECTLY
#define PE_SHP_HW_O18_SET_FW_PARAM_TO_REG_DIRECTLY


/* 20140616, sj.youm, pe1_lap_h 1,2,4 not available because of rtl bug. set valid value(0,3,5) */
#undef PE_SHP_HW_O18_PROTECT_SP_LAP_H_MODE_BUG

/* 20141006, sj.youm, sre shp write only mode */
#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
#define PE_SHP_HW_O18_SRE_SHP_WR_ONLY_MD
#else
#undef PE_SHP_HW_O18_SRE_SHP_WR_ONLY_MD
#endif

/* 20141009, sj.youm, use sre shp write only mode */
#define PE_SHP_HW_O18_USE_SRE_SHP_WR_ONLY_MD

/* use internal scl filter coeff decision */
#define PE_SHP_HW_O18_SCL_CO_INTERNAL_DECISION

/* use shp L fw dummy reg for fw gsc ctrl write */
#undef PE_SHP_HW_O18_USE_FWS_REG_FOR_FW_GSC_WR

/* set motion shp enable by f/w */
#define PE_SHP_HW_O18_SHP_MOTION_ENABLE

#define PE_SHP_HW_O18_CROSS_PAT_DETECT


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#define PE_SHP_HW_O18_ERROR		PE_PRINT_ERROR

#ifdef PE_SHP_HW_O18_SR_PWD_TRACE
#define PE_SHP_HW_O18_DBG_SRPD_TRACE(fmt, args...)	\
	if(_g_shp_hw_o18_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

#define PE_SHP_HW_O18_DBG_PRINT(fmt, args...)
#else
#define PE_SHP_HW_O18_DBG_PRINT(fmt, args...)	\
	if(_g_shp_hw_o18_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}
#endif

#define PE_SHP_HW_O18_CHECK_CODE(_checker, _action, fmt, args...)	\
	{if(_checker){PE_SHP_HW_O18_ERROR(fmt, ##args);_action;}}

#define PE_SHP_HW_O18_DBG_CHECK_CODE(_cnt, _checker, _action, fmt, args...)	\
	{\
		if(_checker){\
			if(_g_shp_hw_o18_trace&&_cnt>PE_PRINT_COUNT_NUM)\
			{\
				PE_SHP_HW_O18_DBG_PRINT(fmt, ##args);\
			}\
			_action;\
		}\
	}

/* for O18*/
#define PE_SHP_HW_O18_DBG_PRINT_RES_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_RES_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_RES_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}
#ifdef PE_SHP_HW_O18_SRE_SHP_WR_ONLY_MD
#define PE_SHP_HW_O18_DBG_PRINT_SRS_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_SRS_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_SRS_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_O18_DBG_PRINT_2KS_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_2KS_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_2KS_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}
#endif
#define PE_SHP_HW_O18_DBG_PRINT_CHR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_CHR_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_CHR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}

#define PE_SHP_HW_O18_DBG_PRINT_SRE_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_SRE_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_SRE_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_O18_DBG_PRINT_SRL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_SRL_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_SRL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_O18_DBG_PRINT_PBL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_PBL_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_PBL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_O18_DBG_PRINT_CTI_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_CTI_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_CTI_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_O18_DBG_PRINT_PST_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_PST_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_PST_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_SHP_HW_O18_DBG_PRINT_PSG_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O18_PSG_FMT_TO_STR(_pre), \
			PE_SHP_HW_O18_PSG_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O18_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_O18_SetTraceDataBuf(_str_buf);\
		}\
	}

#define PE_SHP_HW_O18_SET_SHDW_GSC_Y_TO_SHP(_dst, _src)	\
	(*((UINT32 *)&(gPE_SHP_O18.shdw.data->_dst))) = (*((UINT32 *)&(gPE_GSC_Y_O18.shdw.data->_src)))
#define PE_SHP_HW_O18_SET_SHDW_GSC_C_TO_SHP(_dst, _src)	\
	(*((UINT32 *)&(gPE_SHP_O18.shdw.data->_dst))) = (*((UINT32 *)&(gPE_GSC_C_O18.shdw.data->_src)))

#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
#define PE_SHP_HW_O18_RES_SET_USER(_r, _f, _d)	\
	{	_g_pe_res_hw_param_data_o18.reg_user.data->_r._f = (_d);\
		_g_pe_res_hw_param_data_o18.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O18_RES_WR01(_r, _f1, _d1)	\
	{	PE_SHP_O18_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O18_RES_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_O18_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O18_RES_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_O18_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O18_RES_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_O18_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O18_RES_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_O18_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_O18_RES_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SHP_O18_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_O18_RES_SET_USER(_r, _f6, _d6);}

#define PE_SHP_HW_O18_PBL_SET_USER(_r, _f, _d)	\
	{	_g_pe_pbl_hw_param_data_o18.reg_user.data->_r._f = (_d);\
		_g_pe_pbl_hw_param_data_o18.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O18_PBL_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_O18_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O18_PBL_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_O18_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O18_PBL_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_O18_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O18_PBL_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_O18_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O18_PBL_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_O18_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_PBL_SET_USER(_r, _f5, _d5);}

#define PE_SHP_HW_O18_CTI_SET_USER(_r, _f, _d)	\
	{	_g_pe_cti_hw_param_data_o18.reg_user.data->_r._f = (_d);\
		_g_pe_cti_hw_param_data_o18.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O18_DNR_CTI_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_O18_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O18_DNR_CTI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_O18_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O18_DNR_CTI_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_O18_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O18_DNR_CTI_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_O18_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O18_DNR_CTI_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_O18_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f5, _d5);}

#define PE_SHP_HW_O18_SHP_CTI_WR01(_r, _f1, _d1)	\
	{	PE_SHP_O18_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O18_SHP_CTI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_O18_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O18_SHP_CTI_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_O18_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O18_SHP_CTI_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_O18_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O18_SHP_CTI_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_O18_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_CTI_SET_USER(_r, _f5, _d5);}


/* sre shp(srs) */
#define PE_SHP_HW_O18_SRS_SET_USER(_r, _f, _d)	\
	{	_g_pe_srs_hw_param_data_o18.reg_user.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_o18.reg_mask.data->_r._f = 0;}

#ifndef PE_SHP_HW_O18_USE_SRE_SHP_WR_ONLY_MD
/* for wr only mode */
#define PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f, _d)	\
	{	_g_pe_srs_hw_param_data_o18.reg_data.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_o18.reg_user.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_o18.reg_mask.data->_r._f = 0;}
#define PE_SHP_HW_O18_SRS_DATA_TO_U32(_r)	\
	(*((UINT32 *)&(_g_pe_srs_hw_param_data_o18.reg_data.data->_r)))

#define PE_SHP_HW_O18_SR_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SR_4K_SHP_O18_Wr(_r,PE_SHP_HW_O18_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O18_WrFL(_r);}
#define PE_SHP_HW_O18_SR_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SR_4K_SHP_O18_Wr(_r,PE_SHP_HW_O18_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O18_WrFL(_r);}
#define PE_SHP_HW_O18_SR_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SR_4K_SHP_O18_Wr(_r,PE_SHP_HW_O18_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O18_WrFL(_r);}
#define PE_SHP_HW_O18_SR_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SR_4K_SHP_O18_Wr(_r,PE_SHP_HW_O18_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O18_WrFL(_r);}
#define PE_SHP_HW_O18_SR_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f5, _d5);\
		PE_SR_4K_SHP_O18_Wr(_r,PE_SHP_HW_O18_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O18_WrFL(_r);}
#define PE_SHP_HW_O18_SR_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f5, _d5);\
		PE_SHP_HW_O18_SRS_SET_USER_DATA(_r, _f6, _d6);\
		PE_SR_4K_SHP_O18_Wr(_r,PE_SHP_HW_O18_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O18_WrFL(_r);}

#else	//#ifdef PE_SHP_HW_O18_USE_SRE_SHP_WR_ONLY_MD
#define PE_SHP_HW_O18_SR_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SR_4K_SHP_O18_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O18_SR_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SR_4K_SHP_O18_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O18_SR_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SR_4K_SHP_O18_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O18_SR_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SR_4K_SHP_O18_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O18_SR_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SR_4K_SHP_O18_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_O18_SR_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SR_4K_SHP_O18_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_O18_SRS_SET_USER(_r, _f6, _d6);}

#endif	//#ifdef PE_SHP_HW_O18_USE_SRE_SHP_WR_ONLY_MD

/* sre shp(srs) */
#define PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f, _d)	\
	{	_g_pe_srs_2k_hw_param_data_o18.reg_user.data->_r._f = (_d);\
		_g_pe_srs_2k_hw_param_data_o18.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O18_SR_2K_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SR_2K_SHP_O18_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O18_SR_2K_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SR_2K_SHP_O18_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O18_SR_2K_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SR_2K_SHP_O18_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O18_SR_2K_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SR_2K_SHP_O18_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O18_SR_2K_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SR_2K_SHP_O18_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_O18_SR_2K_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SR_2K_SHP_O18_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_O18_SRS_2K_SET_USER(_r, _f6, _d6);}

#define PE_SHP_HW_O18_PSP_SET_USER(_r, _f, _d)	\
	{	_g_pe_pst_hw_param_data_o18.reg_user.data->_r._f = (_d);\
		_g_pe_pst_hw_param_data_o18.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O18_PSP_WR01(_r, _f1, _d1)	\
	{	PE_SHP_PSP_O18_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O18_PSP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_PSP_O18_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O18_PSP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_PSP_O18_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O18_PSP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_PSP_O18_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O18_PSP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_PSP_O18_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O18_PSP_SET_USER(_r, _f5, _d5);}


/* set table */
#define PE_SHP_HW_O18_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_SHP_HW_O18_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_O18_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_O18_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_O18_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"[%s,%d] _data is null, not ready.\n", __F__, __L__);\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_O18_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			ret = PE_REG_O18_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_O18_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_SHP_HW_O18_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

/* shp */
#define PE_SHP_HW_O18_RES_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_res_hw_param_data_o18.reg_dflt.addr;\
		UINT32 *_user = _g_pe_res_hw_param_data_o18.reg_user.addr;\
		UINT32 *_mask = _g_pe_res_hw_param_data_o18.reg_mask.addr;\
		UINT32 *_data = _g_pe_res_hw_param_data_o18.reg_data.addr;\
		PE_SHP_HW_O18_CHECK_CODE(\
		(sizeof(PE_RES_HW_PARAM_REG_O18_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]res tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O18_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* sre shp(srs) */
#define PE_SHP_HW_O18_SRS_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_srs_hw_param_data_o18.reg_dflt.addr;\
		UINT32 *_user = _g_pe_srs_hw_param_data_o18.reg_user.addr;\
		UINT32 *_mask = _g_pe_srs_hw_param_data_o18.reg_mask.addr;\
		UINT32 *_data = _g_pe_srs_hw_param_data_o18.reg_data.addr;\
		PE_SHP_HW_O18_CHECK_CODE(\
		(sizeof(PE_SRS_HW_PARAM_REG_O18_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]srs tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O18_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* sre shp(srs) */
#define PE_SHP_HW_O18_SRS_2K_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_srs_2k_hw_param_data_o18.reg_dflt.addr;\
		UINT32 *_user = _g_pe_srs_2k_hw_param_data_o18.reg_user.addr;\
		UINT32 *_mask = _g_pe_srs_2k_hw_param_data_o18.reg_mask.addr;\
		UINT32 *_data = _g_pe_srs_2k_hw_param_data_o18.reg_data.addr;\
		PE_SHP_HW_O18_CHECK_CODE(\
		(sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]srs tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O18_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* cti */
#define PE_SHP_HW_O18_CTI_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_cti_hw_param_data_o18.reg_dflt.addr;\
		UINT32 *_user = _g_pe_cti_hw_param_data_o18.reg_user.addr;\
		UINT32 *_mask = _g_pe_cti_hw_param_data_o18.reg_mask.addr;\
		UINT32 *_data = _g_pe_cti_hw_param_data_o18.reg_data.addr;\
		PE_SHP_HW_O18_CHECK_CODE(\
		(sizeof(PE_CTI_HW_PARAM_REG_O18_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]cti tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O18_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* pbl */
#define PE_SHP_HW_O18_PBL_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_pbl_hw_param_data_o18.reg_dflt.addr;\
		UINT32 *_user = _g_pe_pbl_hw_param_data_o18.reg_user.addr;\
		UINT32 *_mask = _g_pe_pbl_hw_param_data_o18.reg_mask.addr;\
		UINT32 *_data = _g_pe_pbl_hw_param_data_o18.reg_data.addr;\
		PE_SHP_HW_O18_CHECK_CODE(\
		(sizeof(PE_PBL_HW_PARAM_REG_O18_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]pbl tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O18_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* sre shp(srs) */
#define PE_SHP_HW_O18_PST_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_pst_hw_param_data_o18.reg_dflt.addr;\
		UINT32 *_user = _g_pe_pst_hw_param_data_o18.reg_user.addr;\
		UINT32 *_mask = _g_pe_pst_hw_param_data_o18.reg_mask.addr;\
		UINT32 *_data = _g_pe_pst_hw_param_data_o18.reg_data.addr;\
		PE_SHP_HW_O18_CHECK_CODE(\
		(sizeof(PE_VSD_PST_HW_PARAM_O18_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]pst tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O18_SET_REG_TABLE(__tbl, __base);\
	}while (0)
#endif

/* set gsc filter */
#define PE_SHP_HW_O18_SET_GSC_FLT(__tbl, __base, __size)	\
	do{\
		UINT32 _i;\
		for (_i=0; _i<(__size); _i++)\
		{\
			ret = PE_REG_O18_WrAllocatedAddr((__tbl[_i].addr+(__base)), (__tbl[_i].data));\
			PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_O18_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_SHP_HW_O18_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_SHP_HW_O18_CASE_SET_FLT(__ms, __tap, __idx, __ofst, __size)		\
	case PE_SHP_SCL256_CO_NUM_##__tap##T_##__idx:\
		PE_SHP_HW_O18_SET_GSC_FLT(scl_p256_##__tap##t_##__ms##_flt_##__idx,(__ofst),(__size));\
		break

#define PE_SHP_HW_O18_WR_SCL_COEFF(_wid, _ctrl, _coeff, _id)	\
{\
	char _str_buf[PE_TRACE_STR_SIZE];\
	snprintf(_str_buf, PE_TRACE_STR_SIZE,"[wid:%d][idx:%3d]%s", _wid, (_id), #_coeff);\
	PE_SHP_HW_O18_DBG_PRINT("set %s\n", _str_buf);\
	PE_INF_O18_SetTraceDataBuf(_str_buf);\
	PE_SHP_HW_O18_WrSclCoeff((_ctrl),&(_coeff));\
}

/* hex(8bit) to dec : eg. 0xAC -> 1012 */
#define PE_SHP_HW_O18_IDX_HEX_TO_DEC(_x)	(GET_BITS((_x),4,4)*100+GET_BITS((_x),0,4))
/* dec to hex(8bit) : eg. 1012 -> 0xAC */
#define PE_SHP_HW_O18_IDX_DEC_TO_HEX(_x)	(((((_x)/100)&0xf)<<4)+(((_x)%100)&0xf))

#define PE_SHP_HW_O18_CONV_VTAP_TO_VSC_MD(_x)		\
	((_x)==PE_SHP_HW_O18_SCL_VSC_MD_V12TAP||(_x)==PE_SHP_HW_O18_SCL_VSC_MD_V08TAP)? 0x0:\
	((_x)==PE_SHP_HW_O18_SCL_VSC_MD_V02TAP)? 0x3:0x1

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
extern UINT32 g_pe_inf_o18_vr360_mode;
/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
//static int PE_SHP_HW_O18_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static PE_SHP_HW_O18_RES_FMT PE_SHP_HW_O18_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O18_SRS_FMT PE_SHP_HW_O18_ConvDispInfoToSrsFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O18_2KS_FMT PE_SHP_HW_O18_ConvDispInfoTo2ksFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O18_CHR_FMT PE_SHP_HW_O18_ConvDispInfoToChrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O18_CTI_FMT PE_SHP_HW_O18_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf);
#if 0
static PE_SHP_HW_O18_PBL_FMT PE_SHP_HW_O18_ConvDispInfoToPblFmt(LX_PE_INF_DISPLAY_T *disp_inf);
#endif
static PE_SHP_HW_O18_PST_FMT PE_SHP_HW_O18_ConvDispInfoToPstFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O18_PSG_FMT PE_SHP_HW_O18_ConvDispInfoToPsgFmt(LX_PE_INF_DISPLAY_T *disp_inf);
#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
static int PE_SHP_HW_O18_CreateDataTable(UINT32 index);
#endif /* !PE_HW_O18_PROTECT_OVERLAP_SETTINGS */
static int PE_SHP_HW_O18_SetResDefault(PE_SHP_HW_O18_RES_FMT cur0_res_fmt);
static int PE_SHP_HW_O18_SetSrsDefault(PE_SHP_HW_O18_SRS_FMT cur0_srs_fmt);
static int PE_SHP_HW_O18_Set2ksDefault(PE_SHP_HW_O18_2KS_FMT cur0_2ks_fmt);
static int PE_SHP_HW_O18_SetChrDefault(PE_SHP_HW_O18_CHR_FMT cur0_chr_fmt);
#if 0
static int PE_SHP_HW_O18_SetPblDefault(PE_SHP_HW_O18_PBL_FMT cur0_pbl_fmt);
#endif
static int PE_SHP_HW_O18_SetCtiDefault(PE_SHP_HW_O18_CTI_FMT cur0_cti_fmt);
static int PE_SHP_HW_O18_SetPstDefault(PE_SHP_HW_O18_PST_FMT cur0_pst_fmt);
static int PE_SHP_HW_O18_SetPsgDefault(PE_SHP_HW_O18_PSG_FMT cur0_psg_fmt);

static int PE_SHP_HW_O18_DownloadScl12tMainDb(void);
static int PE_SHP_HW_O18_DownloadScl08tMainDb(void);
static int PE_SHP_HW_O18_DownloadScl04tMainDb(void);
static int PE_SHP_HW_O18_DownloadShp2KSqmCmnUserDb(void *pstParams);
static int PE_SHP_HW_O18_DownloadShp2KSqmDetailUserDb(void *pstParams);
static int PE_SHP_HW_O18_DownloadShpSqmCmnUserDb(void *pstParams);
static int PE_SHP_HW_O18_DownloadShpSqmDetailUserDb(void *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#ifdef PE_SHP_HW_O18_SR_PWD_TRACE
static UINT8 _g_shp_hw_o18_trace=0x1;	//default should be off.
#else
static UINT8 _g_shp_hw_o18_trace=0x0;	//default should be off.
#endif
static PE_SHP_HW_O18_SETTINGS_T _g_pe_shp_hw_o18_info;
#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
static PE_RES_HW_PARAM_DATA_O18_T _g_pe_res_hw_param_data_o18 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_SRS_HW_PARAM_DATA_O18_T _g_pe_srs_hw_param_data_o18 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_SRS_2K_HW_PARAM_DATA_O18_T _g_pe_srs_2k_hw_param_data_o18 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_PBL_HW_PARAM_DATA_O18_T _g_pe_pbl_hw_param_data_o18 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_CTI_HW_PARAM_DATA_O18_T _g_pe_cti_hw_param_data_o18 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_PST_HW_PARAM_DATA_O18_T _g_pe_pst_hw_param_data_o18 = {{NULL}, {NULL}, {NULL}, {NULL}};
//static PE_PSG_HW_PARAM_DATA_O18_T _g_pe_psg_hw_param_data_o18 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif

#ifdef PE_SHP_HW_O18_CROSS_PAT_DETECT
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
int PE_SHP_HW_O18_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			memset(&(_g_pe_shp_hw_o18_info), -1, sizeof(PE_SHP_HW_O18_SETTINGS_T));
			_g_pe_shp_hw_o18_info.res0a_fmt = PE_SHP_O18_RES_NUM;
			_g_pe_shp_hw_o18_info.cti0a_fmt = PE_SHP_O18_CTI_NUM;
			_g_pe_shp_hw_o18_info.pbl0a_fmt = PE_SHP_O18_PBL_NUM;
			_g_pe_shp_hw_o18_info.sre0a_fmt = PE_SHP_O18_RES_NUM;
			_g_pe_shp_hw_o18_info.srs0a_fmt = PE_SHP_O18_SRS_NUM;
			_g_pe_shp_hw_o18_info.k2s0a_fmt = PE_SHP_O18_2KS_NUM;
			PE_SHP_HW_O18_DBG_PRINT("init cti.\n");
			PE_SR_CHR_SHP_O18_QWr01(shp_core_ctrl_00,   reg_top_core_bypass, 0x0);
			PE_SR_2K_SHP_O18_QWr01(shp_core_ctrl_00,   reg_top_core_bypass, 0x0);
			PE_SR_4K_SHP_O18_QWr01(shp_core_ctrl_00,   reg_top_core_bypass, 0x0);
			PE_SHP_O18_QWr01(shp_core_ctrl_00,   reg_top_core_bypass, 0x0);
			#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
			/* res(pe1 shp l,r) : resolution enhance */
			ret = PE_SHP_HW_O18_CreateDataTable(PE_SHP_HW_O18_TBL_IDX_RES);
			PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O18_CreateDataTable() error.\n");
			PE_SHP_HW_O18_RES_REG_TABLE(shp_l_hd_default_o18,PE_O18_REG_WRITE_BASE);
			/* sre shp(srs) */
			ret = PE_SHP_HW_O18_CreateDataTable(PE_SHP_HW_O18_TBL_IDX_SRS);
			PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O18_CreateDataTable() error.\n");
			PE_SHP_HW_O18_SRS_REG_TABLE(sre_4k_res_hd_default_o18,PE_O18_REG_WRITE_BASE);
			ret = PE_SHP_HW_O18_CreateDataTable(PE_SHP_HW_O18_TBL_IDX_SRS_2K);
			PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O18_CreateDataTable() error.\n");
			PE_SHP_HW_O18_SRS_2K_REG_TABLE(sre_2k_res_hd_default_o18,PE_O18_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_O18,sre_chr_res_hd_default_o18,PE_O18_REG_WRITE_BASE);
			#if 0
			/* pbl(pre blur dnr1,2) */
			ret = PE_SHP_HW_O18_CreateDataTable(PE_SHP_HW_O18_TBL_IDX_PBL);
			PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O18_CreateDataTable() error.\n");
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_hd_default_o18,PE_O18_REG_WRITE_BASE);
			#endif
			/* cti */
			ret = PE_SHP_HW_O18_CreateDataTable(PE_SHP_HW_O18_TBL_IDX_CTI);
			PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O18_CreateDataTable() error.\n");
			PE_SHP_HW_O18_CTI_REG_TABLE(cti_y_l_hd_default_o18,PE_O18_REG_WRITE_BASE);
			/* psp */
			ret = PE_SHP_HW_O18_CreateDataTable(PE_SHP_HW_O18_TBL_IDX_PST);
			PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O18_CreateDataTable() error.\n");
			PE_SHP_HW_O18_PST_REG_TABLE(vsdpsptop_hd_default_o18,PE_O18_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_O18,vsdpspgain_hd_default_o18,PE_O18_REG_WRITE_BASE);
			/*OSD shp*/
			PE_SET_REG_TABLE(SHP_HW_O18,osdsr_default_o18,PE_O18_REG_WRITE_BASE);
			#else
			/* shp */
			PE_SET_REG_TABLE(SHP_HW_O18,shp_l_hd_default_o18,PE_O18_REG_WRITE_BASE);
			/* cti(dnr1,2) */
			//PE_SET_REG_TABLE(SHP_HW_O18,cti_dnr_l_hd_default_o18,PE_O18_REG_WRITE_BASE);
			/* pbl(pre blur dnr1,2) */
			//PE_SET_REG_TABLE(SHP_HW_O18,pblur_dnr_l_hd_default_o18,PE_O18_REG_WRITE_BASE);
			/* sre */
			PE_SET_REG_TABLE(SHP_HW_O18,sre_2k_res_hd_default_o18,PE_O18_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_O18,sre_4k_res_hd_default_o18,PE_O18_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_O18,sre_chr_res_hd_default_o18,PE_O18_REG_WRITE_BASE);
			#endif
			PE_GSC_Y_O18_RdFL(gsc_g0_y_ctrl);
			PE_GSC_Y_O18_Wr01(gsc_g0_y_ctrl,reg_mode_32p_g0,0x0);		//phase 0x0:256,0x1:32
			//PE_GSC_Y_O18_Wr01(gsc_g0_y_ctrl,reg_min_max_on_g0,0x1);
			PE_GSC_Y_O18_Wr01(gsc_g0_y_ctrl,blending_range_g0,0x1);
			//PE_GSC_Y_O18_Wr01(gsc_g0_y_ctrl,reg_min_max_th_g0,0x21);
			PE_GSC_Y_O18_Wr01(gsc_g0_y_ctrl,reg_th_g0,0x6);
			PE_GSC_Y_O18_WrFL(gsc_g0_y_ctrl);
			PE_GSC_Y_O18_RdFL(gsc_g1_y_ctrl);
			PE_GSC_Y_O18_Wr01(gsc_g1_y_ctrl,reg_mode_32p_g1,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_Y_O18_WrFL(gsc_g1_y_ctrl);

			PE_GSC_Y_O18_RdFL(gsc_g0_y_min_max_ctrl);
			PE_GSC_Y_O18_Wr(gsc_g0_y_min_max_ctrl, 0x21012101);
			PE_GSC_Y_O18_WrFL(gsc_g0_y_min_max_ctrl);

			/* gsc_c */
			PE_GSC_C_O18_RdFL(gsc_g0_c_ctrl);
			PE_GSC_C_O18_Wr01(gsc_g0_c_ctrl,reg_mode_32p_g0,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_C_O18_Wr01(gsc_g0_c_ctrl,reg_min_max_on_g0,0x1);
			PE_GSC_C_O18_Wr01(gsc_g0_c_ctrl,reg_min_max_th_g0,0x1C);
			PE_GSC_C_O18_Wr01(gsc_g0_c_ctrl,reg_min_max_on_h_g0,0x1);
			PE_GSC_C_O18_WrFL(gsc_g0_c_ctrl);
			PE_GSC_C_O18_RdFL(gsc_g1_c_ctrl);
			PE_GSC_C_O18_Wr01(gsc_g1_c_ctrl,reg_mode_32p_g1,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_C_O18_WrFL(gsc_g1_c_ctrl);
#ifdef PE_SHP_HW_O18_CROSS_PAT_DETECT
			_g_pre_data_shp=0xff;
			_g_pre_shp_bypass=0xff;
#endif
			
			return ret;
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * create data table
 *
 * @param   index [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_SHP_HW_O18A_TBL_INDX
 * @author
 */
static int PE_SHP_HW_O18_CreateDataTable(UINT32 index)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	PE_RES_HW_PARAM_DATA_O18_T *p_res_o18 = &_g_pe_res_hw_param_data_o18;
	PE_PBL_HW_PARAM_DATA_O18_T *p_pbl_o18 = &_g_pe_pbl_hw_param_data_o18;
	PE_SRS_HW_PARAM_DATA_O18_T *p_srs_o18 = &_g_pe_srs_hw_param_data_o18;
	PE_SRS_2K_HW_PARAM_DATA_O18_T *p_srs_2k_o18 = &_g_pe_srs_2k_hw_param_data_o18;
	PE_CTI_HW_PARAM_DATA_O18_T *p_cti_o18 = &_g_pe_cti_hw_param_data_o18;
	PE_PST_HW_PARAM_DATA_O18_T *p_pst_o18 = &_g_pe_pst_hw_param_data_o18;
	PE_SHP_HW_O18_CHECK_CODE(index>=PE_SHP_HW_O18_TBL_IDX_NUM, return RET_ERROR, \
		"[%s,%d] index(%d) invalid.\n", __F__, __L__, index);
	if (index == PE_SHP_HW_O18_TBL_IDX_RES)
	{
		/* create dflt table */
		if (p_res_o18->reg_dflt.addr == NULL)
		{
			p_res_o18->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O18_T));
		}
		/* create user table */
		if (p_res_o18->reg_user.addr == NULL)
		{
			p_res_o18->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O18_T));
			memset((p_res_o18->reg_user.addr), 0, sizeof(PE_RES_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* create mask table */
		if (p_res_o18->reg_mask.addr == NULL)
		{
			p_res_o18->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O18_T));
			memset((p_res_o18->reg_mask.addr), -1, sizeof(PE_RES_HW_PARAM_REG_O18_T));// 0xffffffff
		}
		/* create data table */
		if (p_res_o18->reg_data.addr == NULL)
		{
			p_res_o18->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O18_T));
			memset((p_res_o18->reg_data.addr), 0, sizeof(PE_RES_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* report result */
		if (p_res_o18->reg_dflt.addr != NULL && p_res_o18->reg_user.addr != NULL && \
			p_res_o18->reg_mask.addr != NULL && p_res_o18->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O18_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O18_TBL_IDX_TO_STR(index), \
				(p_res_o18->reg_dflt.addr == NULL)? "x":"o", \
				(p_res_o18->reg_user.addr == NULL)? "x":"o", \
				(p_res_o18->reg_mask.addr == NULL)? "x":"o", \
				(p_res_o18->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O18_TBL_IDX_PBL)
	{
		/* create dflt table */
		if (p_pbl_o18->reg_dflt.addr == NULL)
		{
			p_pbl_o18->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_O18_T));
		}
		/* create user table */
		if (p_pbl_o18->reg_user.addr == NULL)
		{
			p_pbl_o18->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_O18_T));
			memset((p_pbl_o18->reg_user.addr), 0, sizeof(PE_PBL_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* create mask table */
		if (p_pbl_o18->reg_mask.addr == NULL)
		{
			p_pbl_o18->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_O18_T));
			memset((p_pbl_o18->reg_mask.addr), -1, sizeof(PE_PBL_HW_PARAM_REG_O18_T));// 0xffffffff
		}
		/* create data table */
		if (p_pbl_o18->reg_data.addr == NULL)
		{
			p_pbl_o18->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_O18_T));
			memset((p_pbl_o18->reg_data.addr), 0, sizeof(PE_PBL_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* report result */
		if (p_pbl_o18->reg_dflt.addr != NULL && p_pbl_o18->reg_user.addr != NULL && \
			p_pbl_o18->reg_mask.addr != NULL && p_pbl_o18->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O18_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O18_TBL_IDX_TO_STR(index), \
				(p_pbl_o18->reg_dflt.addr == NULL)? "x":"o", \
				(p_pbl_o18->reg_user.addr == NULL)? "x":"o", \
				(p_pbl_o18->reg_mask.addr == NULL)? "x":"o", \
				(p_pbl_o18->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O18_TBL_IDX_CTI)
	{
		/* create dflt table */
		if (p_cti_o18->reg_dflt.addr == NULL)
		{
			p_cti_o18->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O18_T));
		}
		/* create user table */
		if (p_cti_o18->reg_user.addr == NULL)
		{
			p_cti_o18->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O18_T));
			memset((p_cti_o18->reg_user.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* create mask table */
		if (p_cti_o18->reg_mask.addr == NULL)
		{
			p_cti_o18->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O18_T));
			memset((p_cti_o18->reg_mask.addr), -1, sizeof(PE_CTI_HW_PARAM_REG_O18_T));// 0xffffffff
		}
		/* create data table */
		if (p_cti_o18->reg_data.addr == NULL)
		{
			p_cti_o18->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O18_T));
			memset((p_cti_o18->reg_data.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* report result */
		if (p_cti_o18->reg_dflt.addr != NULL && p_cti_o18->reg_user.addr != NULL && \
			p_cti_o18->reg_mask.addr != NULL && p_cti_o18->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O18_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O18_TBL_IDX_TO_STR(index), \
				(p_cti_o18->reg_dflt.addr == NULL)? "x":"o", \
				(p_cti_o18->reg_user.addr == NULL)? "x":"o", \
				(p_cti_o18->reg_mask.addr == NULL)? "x":"o", \
				(p_cti_o18->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	#ifdef PE_SHP_HW_O18_SRE_SHP_WR_ONLY_MD
	else if (index == PE_SHP_HW_O18_TBL_IDX_SRS)
	{
		/* create dflt table */
		if (p_srs_o18->reg_dflt.addr == NULL)
		{
			p_srs_o18->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_O18_T));
		}
		/* create user table */
		if (p_srs_o18->reg_user.addr == NULL)
		{
			p_srs_o18->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_O18_T));
			memset((p_srs_o18->reg_user.addr), 0, sizeof(PE_SRS_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* create mask table */
		if (p_srs_o18->reg_mask.addr == NULL)
		{
			p_srs_o18->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_O18_T));
			memset((p_srs_o18->reg_mask.addr), -1, sizeof(PE_SRS_HW_PARAM_REG_O18_T));// 0xffffffff
		}
		/* create data table */
		if (p_srs_o18->reg_data.addr == NULL)
		{
			p_srs_o18->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_O18_T));
			memset((p_srs_o18->reg_data.addr), 0, sizeof(PE_SRS_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* report srsult */
		if (p_srs_o18->reg_dflt.addr != NULL && p_srs_o18->reg_user.addr != NULL && \
			p_srs_o18->reg_mask.addr != NULL && p_srs_o18->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O18_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O18_TBL_IDX_TO_STR(index), \
				(p_srs_o18->reg_dflt.addr == NULL)? "x":"o", \
				(p_srs_o18->reg_user.addr == NULL)? "x":"o", \
				(p_srs_o18->reg_mask.addr == NULL)? "x":"o", \
				(p_srs_o18->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O18_TBL_IDX_SRS_2K)
	{
		/* create dflt table */
		if (p_srs_2k_o18->reg_dflt.addr == NULL)
		{
			p_srs_2k_o18->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T));
		}
		/* create user table */
		if (p_srs_2k_o18->reg_user.addr == NULL)
		{
			p_srs_2k_o18->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T));
			memset((p_srs_2k_o18->reg_user.addr), 0, sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* create mask table */
		if (p_srs_2k_o18->reg_mask.addr == NULL)
		{
			p_srs_2k_o18->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T));
			memset((p_srs_2k_o18->reg_mask.addr), -1, sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T));// 0xffffffff
		}
		/* create data table */
		if (p_srs_2k_o18->reg_data.addr == NULL)
		{
			p_srs_2k_o18->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T));
			memset((p_srs_2k_o18->reg_data.addr), 0, sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T));	// 0x0
		}
		/* report srsult */
		if (p_srs_2k_o18->reg_dflt.addr != NULL && p_srs_2k_o18->reg_user.addr != NULL && \
			p_srs_2k_o18->reg_mask.addr != NULL && p_srs_2k_o18->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O18_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O18_TBL_IDX_TO_STR(index), \
				(p_srs_2k_o18->reg_dflt.addr == NULL)? "x":"o", \
				(p_srs_2k_o18->reg_user.addr == NULL)? "x":"o", \
				(p_srs_2k_o18->reg_mask.addr == NULL)? "x":"o", \
				(p_srs_2k_o18->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	#endif	//#ifdef PE_SHP_HW_O18_SRE_SHP_WR_ONLY_MD
	else if (index == PE_SHP_HW_O18_TBL_IDX_PST)
	{
		/* create dflt table */
		if (p_pst_o18->reg_dflt.addr == NULL)
		{
			p_pst_o18->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_PST_HW_PARAM_O18_T));
		}
		/* create user table */
		if (p_pst_o18->reg_user.addr == NULL)
		{
			p_pst_o18->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_PST_HW_PARAM_O18_T));
			memset((p_pst_o18->reg_user.addr), 0, sizeof(PE_VSD_PST_HW_PARAM_O18_T));	// 0x0
		}
		/* create mask table */
		if (p_pst_o18->reg_mask.addr == NULL)
		{
			p_pst_o18->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_PST_HW_PARAM_O18_T));
			memset((p_pst_o18->reg_mask.addr), -1, sizeof(PE_VSD_PST_HW_PARAM_O18_T));// 0xffffffff
		}
		/* create data table */
		if (p_pst_o18->reg_data.addr == NULL)
		{
			p_pst_o18->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VSD_PST_HW_PARAM_O18_T));
			memset((p_pst_o18->reg_data.addr), 0, sizeof(PE_VSD_PST_HW_PARAM_O18_T));	// 0x0
		}
		/* report result */
		if (p_pst_o18->reg_dflt.addr != NULL && p_pst_o18->reg_user.addr != NULL && \
			p_pst_o18->reg_mask.addr != NULL && p_pst_o18->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O18_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O18_TBL_IDX_TO_STR(index), \
				(p_pst_o18->reg_dflt.addr == NULL)? "x":"o", \
				(p_pst_o18->reg_user.addr == NULL)? "x":"o", \
				(p_pst_o18->reg_mask.addr == NULL)? "x":"o", \
				(p_pst_o18->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else
	{
		PE_SHP_HW_O18_DBG_PRINT("nothing to do\n");	ret = RET_OK;
	}
	#endif /*PE_HW_O18_BRINGUP*/
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
int PE_SHP_HW_O18_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_SHP_HW_O18_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(SHP)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_shp_hw_o18_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(SHP)))? 0x1:0x0;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * default shp setting(for O18AX)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	PE_INF_O18_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	LX_PE_INF_DISPLAY_T *disp1_inf = NULL;
	PE_SHP_HW_O18_RES_FMT cur0_res_fmt;
	//PE_SHP_HW_O18_PBL_FMT cur0_pbl_fmt;
	PE_SHP_HW_O18_CTI_FMT cur0_cti_fmt;
	PE_SHP_HW_O18_SRS_FMT cur0_srs_fmt;
	PE_SHP_HW_O18_2KS_FMT cur0_2ks_fmt;
	PE_SHP_HW_O18_CHR_FMT cur0_chr_fmt;
	PE_SHP_HW_O18_PST_FMT cur0_pst_fmt;
	PE_SHP_HW_O18_PSG_FMT cur0_psg_fmt;
	PE_SHP_HW_O18_SETTINGS_T *pInfo=&_g_pe_shp_hw_o18_info;
	#ifdef PE_SHP_HW_O18_SR_PWD_TRACE
	UINT32 r_data[2];
	#endif
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_O18_GetCurInfSettings(&inf_set);
		PE_SHP_HW_O18_CHECK_CODE(ret, break, \
			"[%s,%d] PE_INF_O18_GetCurInfSettings() error.\n", __F__, __L__);
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		disp1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(disp0_inf);
		CHECK_KNULL(disp1_inf);
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			//*gpe_vsd_ctrl_block_o18 = 0x01200000;
			/* res(pe1 shp l,r) */
			cur0_res_fmt = PE_SHP_HW_O18_ConvDispInfoToResFmt(disp0_inf);
			PE_SHP_HW_O18_DBG_PRINT_RES_FMT_STATE(pInfo->res0a_fmt,cur0_res_fmt);
			if(pInfo->res0a_fmt!=cur0_res_fmt)
			{
				ret = PE_SHP_HW_O18_SetResDefault(cur0_res_fmt);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O18_SetResDefault() error.\n", __F__, __L__);
				pInfo->res0a_fmt=cur0_res_fmt;
			}
			/* sre shp(srs) */
			cur0_srs_fmt = PE_SHP_HW_O18_ConvDispInfoToSrsFmt(disp0_inf);
			PE_SHP_HW_O18_DBG_PRINT_SRS_FMT_STATE(pInfo->srs0a_fmt,cur0_srs_fmt);
			if(pInfo->srs0a_fmt!=cur0_srs_fmt)
			{
				ret = PE_SHP_HW_O18_SetSrsDefault(cur0_srs_fmt);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O18_SetSrsDefault() error.\n", __F__, __L__);
				#ifdef PE_SHP_HW_O18_CROSS_PAT_DETECT
				//_g_pre_data_shp = _g_pe_srs_hw_param_data_o18.reg_dflt.data->shp_derh_ctrl_05.reg_derh_th_gain_edge;
				//PE_SHP_HW_O18_DBG_PRINT("defualt pre :%d\n", _g_pre_data_shp );
				#endif
				pInfo->srs0a_fmt=cur0_srs_fmt;
			}
			/* sre 2k shp(srs) */
			cur0_2ks_fmt = PE_SHP_HW_O18_ConvDispInfoTo2ksFmt(disp0_inf);
			PE_SHP_HW_O18_DBG_PRINT_2KS_FMT_STATE(pInfo->k2s0a_fmt,cur0_2ks_fmt);
			if(pInfo->k2s0a_fmt!=cur0_2ks_fmt)
			{
				ret = PE_SHP_HW_O18_Set2ksDefault(cur0_2ks_fmt);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O18_Set2ksDefault() error.\n", __F__, __L__);
				#ifdef PE_SHP_HW_O18_CROSS_PAT_DETECT
				#endif
				pInfo->k2s0a_fmt=cur0_2ks_fmt;
			}
			/* sre shp(srs) */
			cur0_chr_fmt = PE_SHP_HW_O18_ConvDispInfoToChrFmt(disp0_inf);
			PE_SHP_HW_O18_DBG_PRINT_CHR_FMT_STATE(pInfo->chr0a_fmt,cur0_chr_fmt);
			if(pInfo->chr0a_fmt!=cur0_chr_fmt)
			{
				ret = PE_SHP_HW_O18_SetChrDefault(cur0_chr_fmt);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O18_SetChrDefault() error.\n", __F__, __L__);
				#ifdef PE_SHP_HW_O18_CROSS_PAT_DETECT
				#endif
				pInfo->chr0a_fmt=cur0_chr_fmt;
			}
			#if 0
			/* pbl(pre_blur_dnr) */
			cur0_pbl_fmt = PE_SHP_HW_O18_ConvDispInfoToPblFmt(disp0_inf);
			PE_SHP_HW_O18_DBG_PRINT_PBL_FMT_STATE(pInfo->pbl0a_fmt,cur0_pbl_fmt);
			if(pInfo->pbl0a_fmt!=cur0_pbl_fmt)
			{
				ret = PE_SHP_HW_O18_SetPblDefault(cur0_pbl_fmt);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O18_SetPblDefault() error.\n", __F__, __L__);
				pInfo->pbl0a_fmt=cur0_pbl_fmt;
			}
			#endif
			/*cti(cti_dnr) */
			cur0_cti_fmt = PE_SHP_HW_O18_ConvDispInfoToCtiFmt(disp0_inf);
			PE_SHP_HW_O18_DBG_PRINT_CTI_FMT_STATE(pInfo->cti0a_fmt,cur0_cti_fmt);
			if(pInfo->cti0a_fmt!=cur0_cti_fmt)
			{
				ret = PE_SHP_HW_O18_SetCtiDefault(cur0_cti_fmt);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O18_SetCtiDefault() error.\n", __F__, __L__);
				pInfo->cti0a_fmt=cur0_cti_fmt;
			}
			#if 1
			/* PSP */
			cur0_pst_fmt = PE_SHP_HW_O18_ConvDispInfoToPstFmt(disp0_inf);
			PE_SHP_HW_O18_DBG_PRINT_PST_FMT_STATE(pInfo->psptp_fmt,cur0_pst_fmt);
			if(pInfo->psptp_fmt!=cur0_pst_fmt)
			{
				ret = PE_SHP_HW_O18_SetPstDefault(cur0_pst_fmt);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O18_SetPstDefault() error.\n", __F__, __L__);
				pInfo->psptp_fmt=cur0_pst_fmt;
			}
			cur0_psg_fmt = PE_SHP_HW_O18_ConvDispInfoToPsgFmt(disp0_inf);
			PE_SHP_HW_O18_DBG_PRINT_PSG_FMT_STATE(pInfo->pspgn_fmt,cur0_psg_fmt);
			if(pInfo->pspgn_fmt!=cur0_psg_fmt)
			{
				ret = PE_SHP_HW_O18_SetPsgDefault(cur0_psg_fmt);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O18_SetPsgDefault() error.\n", __F__, __L__);
				pInfo->pspgn_fmt=cur0_psg_fmt;
			}
			#endif
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * default Res setting(for O18X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_O18_RES_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_O18_SetResDefault(PE_SHP_HW_O18_RES_FMT cur0_res_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
	switch(cur0_res_fmt)
	{
		case PE_SHP_O18_RES_SD:
			PE_SHP_HW_O18_RES_REG_TABLE(shp_l_sd_default_o18,   	PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_HD:
			PE_SHP_HW_O18_RES_REG_TABLE(shp_l_hd_default_o18,   	PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_UHD:
			PE_SHP_HW_O18_RES_REG_TABLE(shp_l_ud_default_o18,   	PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_DTV_SD:
			PE_SHP_HW_O18_RES_REG_TABLE(shp_l_sd_dtv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_DTV_HD:
			PE_SHP_HW_O18_RES_REG_TABLE(shp_l_hd_dtv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_SEEMLESS:
			PE_SHP_HW_O18_RES_REG_TABLE(shp_l_cp_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_res_fmt)
	{
		case PE_SHP_O18_RES_SD:
			PE_SET_REG_TABLE(SHP_HW_O18,shp_l_sd_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_HD:
			PE_SET_REG_TABLE(SHP_HW_O18,shp_l_hd_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_UHD:
			PE_SET_REG_TABLE(SHP_HW_O18,shp_l_ud_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_DTV_SD:
			PE_SET_REG_TABLE(SHP_HW_O18,shp_l_sd_dtv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_RES_DTV_SD:
			PE_SET_REG_TABLE(SHP_HW_O18,shp_l_hd_dtv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
static int PE_SHP_HW_O18_SetSrsDefault(PE_SHP_HW_O18_SRS_FMT cur0_srs_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
	switch(cur0_srs_fmt)
	{
		case PE_SHP_O18_SRS_SD:
			PE_SHP_HW_O18_SRS_REG_TABLE(sre_4k_res_sd_default_o18,       PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_SRS_HD:
			PE_SHP_HW_O18_SRS_REG_TABLE(sre_4k_res_hd_default_o18,       PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_SRS_UHD:
			PE_SHP_HW_O18_SRS_REG_TABLE(sre_4k_res_ud_default_o18,      PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_SRS_DTV_SD:
			PE_SHP_HW_O18_SRS_REG_TABLE(sre_4k_res_sd_dtv_default_o18,       PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_SRS_SEEMLESS:
			PE_SHP_HW_O18_SRS_REG_TABLE(sre_4k_res_cp_default_o18,       PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_srs_fmt)
	{
		case PE_SHP_O18_SRS_SD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_4k_res_sd_default_o18,       PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_SRS_HD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_4k_res_hd_default_o18,       PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_SRS_UHD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_4k_res_ud_default_o18,      PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * default Res setting(for O18X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_O18_2KS_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_O18_Set2ksDefault(PE_SHP_HW_O18_2KS_FMT cur0_2ks_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
	switch(cur0_2ks_fmt)
	{
		case PE_SHP_O18_2KS_SD:
			PE_SHP_HW_O18_SRS_2K_REG_TABLE(sre_2k_res_sd_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_HD:
			PE_SHP_HW_O18_SRS_2K_REG_TABLE(sre_2k_res_hd_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_UHD:
			PE_SHP_HW_O18_SRS_2K_REG_TABLE(sre_2k_res_ud_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_DTV_SD:
			PE_SHP_HW_O18_SRS_2K_REG_TABLE(sre_2k_res_sd_dtv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_ATV:
			PE_SHP_HW_O18_SRS_2K_REG_TABLE(sre_2k_res_atv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_DTV_HD:
			PE_SHP_HW_O18_SRS_2K_REG_TABLE(sre_2k_res_hd_dtv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_SEEMLESS:
			PE_SHP_HW_O18_SRS_2K_REG_TABLE(sre_2k_res_cp_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_2ks_fmt)
	{
		case PE_SHP_O18_2KS_SD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_2k_res_sd_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_HD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_2k_res_hd_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_UHD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_2k_res_ud_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_DTV_SD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_2k_res_sd_dtv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_ATV:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_2k_res_atv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_2KS_DTV_HD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_2k_res_hd_dtv_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}


/**
 * default Res setting(for O18X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_O18_CHR_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_O18_SetChrDefault(PE_SHP_HW_O18_CHR_FMT cur0_chr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	switch(cur0_chr_fmt)
	{
		case PE_SHP_O18_CHR_SD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_chr_res_sd_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_CHR_HD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_chr_res_hd_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_CHR_UHD:
			PE_SET_REG_TABLE(SHP_HW_O18,sre_chr_res_ud_default_o18,   PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
#if 0
static int PE_SHP_HW_O18_SetPblDefault(PE_SHP_HW_O18_PBL_FMT cur0_pbl_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O18_BRINGUP
	#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
	switch(cur0_pbl_fmt)
	{
		case PE_SHP_O18_PBL_ATV_NT:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_atv_nt_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_ATV_PAL:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_atv_pal_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_AV:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_av_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_SECAM:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_secam_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_COMP_SD:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_comp_sd_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_DTV_SD:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_dtv_sd_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_HDMI_SD:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_hdmi_sd_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_PC:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_pc_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_HD:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_hd_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_UD:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_ud_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_VR_360:
			PE_SHP_HW_O18_PBL_REG_TABLE(pblur_dnr_l_vr_360_default_o18, PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_pbl_fmt)
	{
		case PE_SHP_O18_PBL_SD:
			PE_SET_REG_TABLE(SHP_HW_O18,pblur_dnr_l_sd_default_o18,PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_PBL_HD:
			PE_SET_REG_TABLE(SHP_HW_O18,pblur_dnr_l_hd_default_o18,PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
#endif
static int PE_SHP_HW_O18_SetCtiDefault(PE_SHP_HW_O18_CTI_FMT cur0_cti_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	switch(cur0_cti_fmt)
	{
		case PE_SHP_O18_CTI_SD:
			PE_SHP_HW_O18_CTI_REG_TABLE(cti_y_l_sd_default_o18,    PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_CTI_HD:
			PE_SHP_HW_O18_CTI_REG_TABLE(cti_y_l_hd_default_o18,    PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_CTI_VR_360:
			PE_SHP_HW_O18_CTI_REG_TABLE(cti_y_l_vr_360_default_o18,    PE_O18_REG_WRITE_BASE);
			break;
		case PE_SHP_O18_CTI_ATV:
			PE_SHP_HW_O18_CTI_REG_TABLE(cti_y_l_atv_default_o18,    PE_O18_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

static int PE_SHP_HW_O18_SetPstDefault(PE_SHP_HW_O18_PST_FMT cur0_pst_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	switch(cur0_pst_fmt)
	{
		case PE_SHP_O18_PST_SD:
			{
				PE_SHP_HW_O18_PST_REG_TABLE(vsdpsptop_sd_default_o18,    PE_O18_REG_WRITE_BASE);
			}
			break;
		case PE_SHP_O18_PST_HD:
			{
				PE_SHP_HW_O18_PST_REG_TABLE(vsdpsptop_hd_default_o18,    PE_O18_REG_WRITE_BASE);
			}
			break;
		case PE_SHP_O18_PST_UD:
			{
				PE_SHP_HW_O18_PST_REG_TABLE(vsdpsptop_ud_default_o18,    PE_O18_REG_WRITE_BASE);
			}
			break;
		default:
			break;
	}
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
static int PE_SHP_HW_O18_SetPsgDefault(PE_SHP_HW_O18_PSG_FMT cur0_psg_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	switch(cur0_psg_fmt)
	{
		case PE_SHP_O18_PSG_SD:
			{
				PE_SET_REG_TABLE(SHP_HW_O18,vsdpspgain_sd_default_o18,    PE_O18_REG_WRITE_BASE);
			}
			break;
		case PE_SHP_O18_PSG_HD:
			{
				PE_SET_REG_TABLE(SHP_HW_O18,vsdpspgain_hd_default_o18,    PE_O18_REG_WRITE_BASE);
			}
			break;
		case PE_SHP_O18_PSG_UD:
			{
				PE_SET_REG_TABLE(SHP_HW_O18,vsdpspgain_ud_default_o18,    PE_O18_REG_WRITE_BASE);
			}
			break;
		default:
			break;
	}
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}


/**
 * get resolution fmt using display info(for O18X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O18_RES_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O18_RES_FMT PE_SHP_HW_O18_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O18_RES_FMT res_fmt = PE_SHP_O18_RES_NUM;
	PE_SHP_HW_O18_DBG_PRINT("ResFmt seemless mode :%d.\n", disp_inf->act_fmt );
	if(disp_inf->act_fmt !=0)
	{
		res_fmt = PE_SHP_O18_RES_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					res_fmt = PE_SHP_O18_RES_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_O18_RES_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_SHP_O18_RES_DTV_HD;
				}
				else
				{
					res_fmt = PE_SHP_O18_RES_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_O18_RES_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_SHP_O18_RES_HD;
				}
				else
				{
					res_fmt = PE_SHP_O18_RES_UHD;
				}
				break;
		}
	}
	return res_fmt;
}
/**
 * get sre shp(srs) fmt using display info(for O18X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O18_SRS_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O18_SRS_FMT PE_SHP_HW_O18_ConvDispInfoToSrsFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O18_SRS_FMT srs_fmt = PE_SHP_O18_SRS_NUM;
	if(disp_inf->act_fmt !=0)
	{
		srs_fmt = PE_SHP_O18_SRS_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					srs_fmt = PE_SHP_O18_SRS_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_O18_SRS_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_O18_SRS_HD;
				}
				else
				{
					srs_fmt = PE_SHP_O18_SRS_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_O18_SRS_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_O18_SRS_HD;
				}
				else
				{
					srs_fmt = PE_SHP_O18_SRS_UHD;
				}
				break;
		}
	}
	return srs_fmt;
}
/**
 * get sre 2k shp(srs) fmt using display info(for O18X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O18_2KS_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O18_2KS_FMT PE_SHP_HW_O18_ConvDispInfoTo2ksFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O18_2KS_FMT srs_fmt = PE_SHP_O18_2KS_NUM;
	if(disp_inf->act_fmt !=0)
	{
		srs_fmt = PE_SHP_O18_2KS_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					srs_fmt = PE_SHP_O18_2KS_ATV;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					srs_fmt = PE_SHP_O18_2KS_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_O18_2KS_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_O18_2KS_DTV_HD;
				}
				else
				{
					srs_fmt = PE_SHP_O18_2KS_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_O18_2KS_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_O18_2KS_HD;
				}
				else
				{
					srs_fmt = PE_SHP_O18_2KS_UHD;
				}
				break;
		}
	}
	return srs_fmt;
}
/**
 * get sre chr shp(srs) fmt using display info(for O18X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O18_CHR_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O18_CHR_FMT PE_SHP_HW_O18_ConvDispInfoToChrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O18_CHR_FMT srs_fmt = PE_SHP_O18_CHR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			srs_fmt = PE_SHP_O18_CHR_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				srs_fmt = PE_SHP_O18_CHR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				srs_fmt = PE_SHP_O18_CHR_HD;
			}
			else
			{
				srs_fmt = PE_SHP_O18_CHR_UHD;
			}
			break;
	}
	return srs_fmt;
}
#if 0
/**
 * get pbl(pre blur dnr) fmt using display info(for O18X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O18_CTI_FMT
 * @see
 * @author
 */
static PE_SHP_HW_O18_PBL_FMT PE_SHP_HW_O18_ConvDispInfoToPblFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O18_PBL_FMT pbl_fmt = PE_SHP_O18_PBL_NUM;
	PE_SHP_HW_O18_DBG_PRINT("PblFmt g_pe_inf_o18_vr360_mode: %d.\n", g_pe_inf_o18_vr360_mode);
	if(disp_inf->mode.is_vr)
	{
			pbl_fmt = PE_SHP_O18_PBL_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				if(disp_inf->cstd_type==LX_PE_CSTD_SECAM)
				{
					pbl_fmt = PE_SHP_O18_PBL_SECAM;
				}
				else if(disp_inf->cstd_type==LX_PE_CSTD_PAL)
				{
					pbl_fmt = PE_SHP_O18_PBL_ATV_PAL;
				}
				else
				{
					pbl_fmt = PE_SHP_O18_PBL_ATV_NT;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				if(disp_inf->cstd_type==LX_PE_CSTD_SECAM)
				{
					pbl_fmt = PE_SHP_O18_PBL_SECAM;
				}
				else
				{
					pbl_fmt = PE_SHP_O18_PBL_AV;
				}
				break;
			case LX_PE_SRC_RGBPC:
				{
					pbl_fmt = PE_SHP_O18_PBL_PC;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->dtv_type==LX_PE_DTV_HDDPLAY)
				{
					if(disp_inf->hdd_type==LX_PE_HDD_SRC_ATV60)
					{
						pbl_fmt = PE_SHP_O18_PBL_ATV_NT;
					}
					else if(disp_inf->hdd_type==LX_PE_HDD_SRC_ATV50)
					{
						pbl_fmt = PE_SHP_O18_PBL_ATV_PAL;
					}
					else if(disp_inf->hdd_type==LX_PE_HDD_SRC_AV60 || \
						disp_inf->hdd_type==LX_PE_HDD_SRC_AV50 || \
						disp_inf->hdd_type==LX_PE_HDD_SRC_SCARTRGB)
					{
						pbl_fmt = PE_SHP_O18_PBL_AV;
					}
					else	//LX_PE_HDD_SRC_DTV
					{
						if(disp_inf->fmt_type==LX_PE_FMT_SD)
						{
							pbl_fmt = PE_SHP_O18_PBL_DTV_SD;
						}
						else if(disp_inf->fmt_type==LX_PE_FMT_HD)
						{
							pbl_fmt = PE_SHP_O18_PBL_HD;
						}
						else
						{
						 	if(g_pe_inf_o18_vr360_mode)
						 	{
								pbl_fmt = PE_SHP_O18_PBL_HD;
						 	}
							else
							{
								pbl_fmt = PE_SHP_O18_PBL_UD;
							}
						}
					}
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_O18_PBL_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					pbl_fmt = PE_SHP_O18_PBL_HD;
				}
				else
				{
					if(g_pe_inf_o18_vr360_mode)
				 	{
						pbl_fmt = PE_SHP_O18_PBL_HD;
				 	}
					else
					{
						pbl_fmt = PE_SHP_O18_PBL_UD;
					}
				}
				break;
			case LX_PE_SRC_COMP:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_O18_PBL_COMP_SD;
				}
				else
				{
					pbl_fmt = PE_SHP_O18_PBL_HD;
				}
				break;
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->hdmi_type==LX_PE_HDMI_PC)
				{
					pbl_fmt = PE_SHP_O18_PBL_PC;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_O18_PBL_HDMI_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					pbl_fmt = PE_SHP_O18_PBL_HD;
				}
				else
				{
					if(g_pe_inf_o18_vr360_mode)
				 	{
						pbl_fmt = PE_SHP_O18_PBL_HD;
				 	}
					else
					{
						pbl_fmt = PE_SHP_O18_PBL_UD;
					}
				}
				break;
		}
	}
	return pbl_fmt;
}
#endif
/**
 * get cti(dnr) fmt using display info(for O18X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O18_CTI_FMT
 * @see
 * @author
 */
static PE_SHP_HW_O18_CTI_FMT PE_SHP_HW_O18_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O18_CTI_FMT cti_fmt = PE_SHP_O18_CTI_NUM;
	if(disp_inf->mode.is_vr)
	{
			cti_fmt = PE_SHP_O18_CTI_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					cti_fmt = PE_SHP_O18_CTI_ATV;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
			case LX_PE_SRC_RGBPC:
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					cti_fmt = PE_SHP_O18_CTI_SD;
				}
				else
				{
					cti_fmt = PE_SHP_O18_CTI_HD;
				}
				break;
		}
	}
	return cti_fmt;
}

/**
 * get vsdpsp top fmt using display info(for O18X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O18_PST_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O18_PST_FMT PE_SHP_HW_O18_ConvDispInfoToPstFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O18_PST_FMT pst_fmt = PE_SHP_O18_PST_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				pst_fmt = PE_SHP_O18_PST_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				pst_fmt = PE_SHP_O18_PST_HD;
			}
			else
			{
				pst_fmt = PE_SHP_O18_PST_UD;
			}
			break;
	}
	return pst_fmt;
}
/**
 * get vsdpsp gain fmt using display info(for O18X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O18_PSG_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O18_PSG_FMT PE_SHP_HW_O18_ConvDispInfoToPsgFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O18_PSG_FMT psg_fmt = PE_SHP_O18_PSG_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				psg_fmt = PE_SHP_O18_PSG_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				psg_fmt = PE_SHP_O18_PSG_HD;
			}
			else
			{
				psg_fmt = PE_SHP_O18_PSG_UD;
			}
			break;
	}
	return psg_fmt;
}

/**
 * read default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_SHP_HW_O18_RdDefault(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 param_size=0, table_size=0, is_valid=0;
	UINT32 rd_cnt=0;
	PE_REG_PARAM_T param;
	PE_SHP_HW_O18_SETTINGS_T *pInfo=&_g_pe_shp_hw_o18_info;

#define PE_SHP_O18_NO_PRINT			0
#define PE_SHP_O18_RD_N_HEX_PRINT	1
#define PE_SHP_O18_HEX_PRINT_ONLY	2
#define PE_SHP_O18_PRINT_START		"START_OF_PRINT"
#define PE_SHP_O18_PRINT_END		"END_OF_PRINT"
#define PE_SHP_O18_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_SHP_O18_PRINT_RESRV		"RESERVED"
#define PE_SHP_O18_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE,"   [0x%02X] %s\n", (_item), #_item);_action;break
#define PE_SHP_O18_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE,fmt, ##args);_action;break
#define PE_SHP_O18_DFLT_SPRINT(_action, _buf, fmt, args...)		\
	default:snprintf(_buf, PE_TRACE_STR_SIZE,fmt, ##args);_action;break

	do{
		if (PE_KDRV_VER_O18)
		{
			UINT32 *p_res_dflt = _g_pe_res_hw_param_data_o18.reg_dflt.addr;
			UINT32 *p_res_user = _g_pe_res_hw_param_data_o18.reg_user.addr;
			UINT32 *p_res_mask = _g_pe_res_hw_param_data_o18.reg_mask.addr;
			UINT32 *p_res_data = _g_pe_res_hw_param_data_o18.reg_data.addr;
			#if 0
			UINT32 *p_pbl_dflt = _g_pe_pbl_hw_param_data_o18.reg_dflt.addr;
			UINT32 *p_pbl_user = _g_pe_pbl_hw_param_data_o18.reg_user.addr;
			UINT32 *p_pbl_mask = _g_pe_pbl_hw_param_data_o18.reg_mask.addr;
			UINT32 *p_pbl_data = _g_pe_pbl_hw_param_data_o18.reg_data.addr;
			#endif
			UINT32 *p_cti_dflt = _g_pe_cti_hw_param_data_o18.reg_dflt.addr;
			UINT32 *p_cti_user = _g_pe_cti_hw_param_data_o18.reg_user.addr;
			UINT32 *p_cti_mask = _g_pe_cti_hw_param_data_o18.reg_mask.addr;
			UINT32 *p_cti_data = _g_pe_cti_hw_param_data_o18.reg_data.addr;
			#ifdef PE_SHP_HW_O18_SRE_SHP_WR_ONLY_MD
			UINT32 *p_srs_dflt = _g_pe_srs_hw_param_data_o18.reg_dflt.addr;
			UINT32 *p_srs_user = _g_pe_srs_hw_param_data_o18.reg_user.addr;
			UINT32 *p_srs_mask = _g_pe_srs_hw_param_data_o18.reg_mask.addr;
			UINT32 *p_srs_data = _g_pe_srs_hw_param_data_o18.reg_data.addr;
			UINT32 *p_srs_2k_dflt = _g_pe_srs_2k_hw_param_data_o18.reg_dflt.addr;
			UINT32 *p_srs_2k_user = _g_pe_srs_2k_hw_param_data_o18.reg_user.addr;
			UINT32 *p_srs_2k_mask = _g_pe_srs_2k_hw_param_data_o18.reg_mask.addr;
			UINT32 *p_srs_2k_data = _g_pe_srs_2k_hw_param_data_o18.reg_data.addr;
			UINT32 *p_pst_dflt = _g_pe_pst_hw_param_data_o18.reg_dflt.addr;
			UINT32 *p_pst_user = _g_pe_pst_hw_param_data_o18.reg_user.addr;
			UINT32 *p_pst_mask = _g_pe_pst_hw_param_data_o18.reg_mask.addr;
			UINT32 *p_pst_data = _g_pe_pst_hw_param_data_o18.reg_data.addr;
			#endif

			CHECK_KNULL(pstParams);
			CHECK_KNULL(pstParams->data);
			CHECK_KNULL(p_res_dflt);
			CHECK_KNULL(p_res_user);
			CHECK_KNULL(p_res_mask);
			CHECK_KNULL(p_res_data);
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]>=PE_SHP_HW_O18_RD_MENU_MAX)
			{
				snprintf(buffer, PE_TRACE_STR_SIZE,PE_SHP_O18_PRINT_EXIT);
				rd_cnt=0;
			}
			else if (pstParams->data[0]==PE_SHP_HW_O18_RD_MENU_DISP)
			{
				switch (rd_cnt)
				{
					PE_SHP_O18_CASE_SPRINT( 0, rd_cnt++, buffer, PE_SHP_O18_PRINT_START);
					PE_SHP_O18_CASE_SPRINT( 1, rd_cnt++, buffer, "   ** current default **\n");
					PE_SHP_O18_CASE_SPRINT( 2, rd_cnt++, buffer, \
						"   res0a_fmt : %s\n", PE_SHP_HW_O18_RES_FMT_TO_STR(pInfo->res0a_fmt));
					PE_SHP_O18_CASE_SPRINT( 3, rd_cnt++, buffer, \
						"   cti0a_fmt : %s\n", PE_SHP_HW_O18_CTI_FMT_TO_STR(pInfo->cti0a_fmt));
					PE_SHP_O18_CASE_SPRINT( 4, rd_cnt++, buffer, \
						"   pbl0a_fmt : %s\n", PE_SHP_HW_O18_PBL_FMT_TO_STR(pInfo->pbl0a_fmt));
					PE_SHP_O18_CASE_SPRINT( 5, rd_cnt++, buffer, \
						"   sre0a_fmt : %s\n", PE_SHP_HW_O18_SRE_FMT_TO_STR(pInfo->sre0a_fmt));
					PE_SHP_O18_CASE_SPRINT( 6, rd_cnt++, buffer, \
						"   srs0a_fmt : %s\n", PE_SHP_HW_O18_SRS_FMT_TO_STR(pInfo->srs0a_fmt));
					PE_SHP_O18_CASE_SPRINT( 7, rd_cnt++, buffer, \
						"   k2s0a_fmt : %s\n", PE_SHP_HW_O18_2KS_FMT_TO_STR(pInfo->k2s0a_fmt));
					PE_SHP_O18_CASE_SPRINT( 8, rd_cnt++, buffer, \
						"   pst0a_fmt : %s\n", PE_SHP_HW_O18_PST_FMT_TO_STR(pInfo->psptp_fmt));
					PE_SHP_O18_CASE_SPRINT( 9, rd_cnt++, buffer, PE_SHP_O18_PRINT_RESRV);
					PE_SHP_O18_CASE_SPRINT(10, rd_cnt++, buffer, "   *********************\n");
					PE_SHP_O18_CASE_PRMENU(11, rd_cnt++, buffer, PE_SHP_HW_O18_RD_RES1_DISP);
					PE_SHP_O18_CASE_PRMENU(12, rd_cnt++, buffer, PE_SHP_HW_O18_RD_RES2_DISP);
					PE_SHP_O18_CASE_PRMENU(13, rd_cnt++, buffer, PE_SHP_HW_O18_RD_RES1_DFLT);
					PE_SHP_O18_CASE_PRMENU(14, rd_cnt++, buffer, PE_SHP_HW_O18_RD_RES1_USER);
					PE_SHP_O18_CASE_PRMENU(15, rd_cnt++, buffer, PE_SHP_HW_O18_RD_RES1_MASK);
					PE_SHP_O18_CASE_PRMENU(16, rd_cnt++, buffer, PE_SHP_HW_O18_RD_RES1_DATA);
					PE_SHP_O18_CASE_PRMENU(17, rd_cnt++, buffer, PE_SHP_HW_O18_RD_CTI1_DISP);
					PE_SHP_O18_CASE_PRMENU(18, rd_cnt++, buffer, PE_SHP_HW_O18_RD_CTI2_DISP);
					PE_SHP_O18_CASE_PRMENU(19, rd_cnt++, buffer, PE_SHP_HW_O18_RD_CTI1_DFLT);
					PE_SHP_O18_CASE_PRMENU(20, rd_cnt++, buffer, PE_SHP_HW_O18_RD_CTI1_USER);
					PE_SHP_O18_CASE_PRMENU(21, rd_cnt++, buffer, PE_SHP_HW_O18_RD_CTI1_MASK);
					PE_SHP_O18_CASE_PRMENU(22, rd_cnt++, buffer, PE_SHP_HW_O18_RD_CTI1_DATA);
					PE_SHP_O18_CASE_PRMENU(23, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PBL1_DISP);
					PE_SHP_O18_CASE_PRMENU(24, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PBL2_DISP);
					PE_SHP_O18_CASE_PRMENU(25, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PBL1_DFLT);
					PE_SHP_O18_CASE_PRMENU(26, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PBL1_USER);
					PE_SHP_O18_CASE_PRMENU(27, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PBL1_MASK);
					PE_SHP_O18_CASE_PRMENU(28, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PBL1_DATA);
					#ifdef PE_SHP_HW_O18_SRE_SHP_WR_ONLY_MD
					PE_SHP_O18_CASE_SPRINT(29, rd_cnt++, buffer, PE_SHP_O18_PRINT_RESRV);
					PE_SHP_O18_CASE_SPRINT(30, rd_cnt++, buffer, PE_SHP_O18_PRINT_RESRV);
					PE_SHP_O18_CASE_PRMENU(31, rd_cnt++, buffer, PE_SHP_HW_O18_RD_SRS1_DISP);
					PE_SHP_O18_CASE_PRMENU(32, rd_cnt++, buffer, PE_SHP_HW_O18_RD_SRS1_DFLT);
					PE_SHP_O18_CASE_PRMENU(33, rd_cnt++, buffer, PE_SHP_HW_O18_RD_SRS1_USER);
					PE_SHP_O18_CASE_PRMENU(34, rd_cnt++, buffer, PE_SHP_HW_O18_RD_SRS1_MASK);
					PE_SHP_O18_CASE_PRMENU(35, rd_cnt++, buffer, PE_SHP_HW_O18_RD_SRS1_DATA);
					PE_SHP_O18_CASE_PRMENU(36, rd_cnt++, buffer, PE_SHP_HW_O18_RD_2KS1_DISP);
					PE_SHP_O18_CASE_PRMENU(37, rd_cnt++, buffer, PE_SHP_HW_O18_RD_2KS1_DFLT);
					PE_SHP_O18_CASE_PRMENU(38, rd_cnt++, buffer, PE_SHP_HW_O18_RD_2KS1_USER);
					PE_SHP_O18_CASE_PRMENU(39, rd_cnt++, buffer, PE_SHP_HW_O18_RD_2KS1_MASK);
					PE_SHP_O18_CASE_PRMENU(40, rd_cnt++, buffer, PE_SHP_HW_O18_RD_2KS1_DATA);
					PE_SHP_O18_CASE_PRMENU(41, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PST1_DISP);
					PE_SHP_O18_CASE_PRMENU(42, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PST1_DFLT);
					PE_SHP_O18_CASE_PRMENU(43, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PST1_USER);
					PE_SHP_O18_CASE_PRMENU(44, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PST1_MASK);
					PE_SHP_O18_CASE_PRMENU(45, rd_cnt++, buffer, PE_SHP_HW_O18_RD_PST1_DATA);
					#endif	//#ifdef PE_SHP_HW_O18_SRE_SHP_WR_ONLY_MD
					PE_SHP_O18_DFLT_SPRINT(rd_cnt=0, buffer, PE_SHP_O18_PRINT_END);
				}
			}
			else
			{
				is_valid = PE_SHP_O18_NO_PRINT;
				switch (pstParams->data[0])
				{
					case PE_SHP_HW_O18_RD_RES1_DISP:
					case PE_SHP_HW_O18_RD_RES2_DISP:
						table_size = sizeof(shp_l_hd_default_o18);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o18[rd_cnt].addr;
							is_valid = PE_SHP_O18_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O18_RD_RES1_DFLT:
						table_size = sizeof(PE_RES_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o18[rd_cnt].addr;
							param.data = p_res_dflt[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_RES1_USER:
						table_size = sizeof(PE_RES_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o18[rd_cnt].addr;
							param.data = p_res_user[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_RES1_MASK:
						table_size = sizeof(PE_RES_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o18[rd_cnt].addr;
							param.data = p_res_mask[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_RES1_DATA:
						table_size = sizeof(PE_RES_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o18[rd_cnt].addr;
							param.data = p_res_data[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_CTI1_DISP:
					case PE_SHP_HW_O18_RD_CTI2_DISP:
						table_size = sizeof(cti_y_l_hd_default_o18);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o18[rd_cnt].addr;
							is_valid = PE_SHP_O18_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O18_RD_CTI1_DFLT:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o18[rd_cnt].addr;
							param.data = p_cti_dflt[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_CTI1_USER:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o18[rd_cnt].addr;
							param.data = p_cti_user[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_CTI1_MASK:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o18[rd_cnt].addr;
							param.data = p_cti_mask[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_CTI1_DATA:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o18[rd_cnt].addr;
							param.data = p_cti_data[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					#if 0
					case PE_SHP_HW_O18_RD_PBL1_DISP:
					case PE_SHP_HW_O18_RD_PBL2_DISP:
						table_size = sizeof(pblur_dnr_l_hd_default_o18);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o18[rd_cnt].addr;
							is_valid = PE_SHP_O18_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O18_RD_PBL1_DFLT:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o18[rd_cnt].addr;
							param.data = p_pbl_dflt[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_PBL1_USER:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o18[rd_cnt].addr;
							param.data = p_pbl_user[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_PBL1_MASK:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o18[rd_cnt].addr;
							param.data = p_pbl_mask[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_PBL1_DATA:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o18[rd_cnt].addr;
							param.data = p_pbl_data[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					#endif
					case PE_SHP_HW_O18_RD_SRS1_DISP:
						table_size = sizeof(sre_4k_res_hd_default_o18);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o18[rd_cnt].addr;
							is_valid = PE_SHP_O18_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O18_RD_SRS1_DFLT:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o18[rd_cnt].addr;
							param.data = p_srs_dflt[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_SRS1_USER:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o18[rd_cnt].addr;
							param.data = p_srs_user[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_SRS1_MASK:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o18[rd_cnt].addr;
							param.data = p_srs_mask[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_SRS1_DATA:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o18[rd_cnt].addr;
							param.data = p_srs_data[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_2KS1_DISP:
						table_size = sizeof(sre_2k_res_hd_default_o18);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o18[rd_cnt].addr;
							is_valid = PE_SHP_O18_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O18_RD_2KS1_DFLT:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o18[rd_cnt].addr;
							param.data = p_srs_2k_dflt[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_2KS1_USER:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o18[rd_cnt].addr;
							param.data = p_srs_2k_user[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_2KS1_MASK:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o18[rd_cnt].addr;
							param.data = p_srs_2k_mask[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_2KS1_DATA:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o18[rd_cnt].addr;
							param.data = p_srs_2k_data[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_PST1_DFLT:
						table_size = sizeof(PE_VSD_PST_HW_PARAM_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vsdpsptop_hd_default_o18[rd_cnt].addr;
							param.data = p_pst_dflt[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_PST1_USER:
						table_size = sizeof(PE_VSD_PST_HW_PARAM_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vsdpsptop_hd_default_o18[rd_cnt].addr;
							param.data = p_pst_user[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_PST1_MASK:
						table_size = sizeof(PE_VSD_PST_HW_PARAM_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vsdpsptop_hd_default_o18[rd_cnt].addr;
							param.data = p_pst_mask[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O18_RD_PST1_DATA:
						table_size = sizeof(PE_VSD_PST_HW_PARAM_O18_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vsdpsptop_hd_default_o18[rd_cnt].addr;
							param.data = p_pst_data[rd_cnt];
							is_valid = PE_SHP_O18_HEX_PRINT_ONLY;
						}
						break;
					default:
						break;
				}
				if (is_valid == PE_SHP_O18_RD_N_HEX_PRINT)
				{
					param.data = PE_REG_O18_RD(param.addr);
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else if (is_valid == PE_SHP_O18_HEX_PRINT_ONLY)
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, PE_SHP_O18_PRINT_END);
					rd_cnt = 0;
				}
			}
			memcpy(pstParams->data, buffer, sizeof(char)*PE_TRACE_STR_SIZE);
		}
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_RE6_CMN_T *pp = (LX_PE_SHP_RE6_CMN_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ui_main_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_main_vsd\n"
			"shp_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);
			pd = pp->shp_ti_ui_main_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ti_ui_main_vsd\n"
			"shp_ti_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			pd = pp->shp_cti_ui_main_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_cti_ui_main_vsd\n"
			"shp_cti_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_RES_WR01(shp_esf_ctrl_01,		reg_esf_master_gain,	GET_BITS(pp->shp_ui_main_vsd[0],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_dctp_ctrl_1d,	reg_dctp_gain,	GET_BITS(pp->shp_ui_main_vsd[1],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_vsd[2],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_lc_ctrl_02,		reg_lc_lap_weight,	GET_BITS(pp->shp_ui_main_vsd[3],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_mp_ctrl_02,		reg_mp_lap_weight,	GET_BITS(pp->shp_ui_main_vsd[4],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_sp_ctrl_02,		reg_sp_lap_weight,	GET_BITS(pp->shp_ui_main_vsd[5],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_der_ctrl_06,		reg_der_a_lut_y0,	GET_BITS(pp->shp_ui_main_vsd[6],0,8),\
															reg_der_a_lut_y1,	GET_BITS(pp->shp_ui_main_vsd[7],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_der_ctrl_07,		reg_der_a_lut_y2,	GET_BITS(pp->shp_ui_main_vsd[8],0,8),\
																reg_der_a_lut_y3,	GET_BITS(pp->shp_ui_main_vsd[9],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_dir_blur_ctrl_01,	reg_dir_blur_gain,	GET_BITS(pp->shp_ui_main_vsd[10],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_dj_ctrl_1d,			reg_dj_soft_g0_mul,	GET_BITS(pp->shp_ui_main_vsd[11],0,6));
				PE_SHP_HW_O18_RES_WR01(shp_dj_ctrl_1e,			reg_dj_soft_g1_mul,	GET_BITS(pp->shp_ui_main_vsd[12],0,6));
				PE_SHP_HW_O18_RES_WR01(shp_dj_ctrl_1f,			reg_dj_soft_g2_mul,	GET_BITS(pp->shp_ui_main_vsd[13],0,6));
				PE_SHP_HW_O18_RES_WR01(shp_nntg_ctrl_0e,		reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_vsd[14],0,8));

				PE_SHP_HW_O18_RES_WR03(shp_sti_ctrl_00,			reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_vsd[0],0,8),\
																reg_sti_edge_gain,	GET_BITS(pp->shp_ti_ui_main_vsd[1],0,8),\
																reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_vsd[2],0,8));
				PE_SHP_HW_O18_DNR_CTI_WR01(reg_cti_ctrl_0,	cti_gain,	GET_BITS(pp->shp_cti_ui_main_vsd[0],0,8));
				PE_SHP_HW_O18_DNR_CTI_WR01(reg_cti_ctrl_2,	reg_ycm_band_sel,	GET_BITS(pp->shp_cti_ui_main_vsd[1],0,3));
				PE_SHP_HW_O18_SHP_CTI_WR01(shp_cti_ctrl_00,	reg_cti_gain,	GET_BITS(pp->shp_cti_ui_main_vsd[2],0,8));
				PE_SHP_HW_O18_SHP_CTI_WR01(shp_cti_ctrl_02,	reg_cti_ycm_band_sel,	GET_BITS(pp->shp_cti_ui_main_vsd[3],0,3));
				#else
				PE_SHP_O18_QWr01(shp_esf_ctrl_01,		reg_esf_master_gain,	GET_BITS(pp->shp_ui_main_vsd[0],0,8));
				PE_SHP_O18_QWr01(shp_dctp_ctrl_1d,		reg_dctp_gain,	GET_BITS(pp->shp_ui_main_vsd[1],0,8));
				PE_SHP_O18_QWr01(shp_tgen_ctrl_00,		reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_vsd[2],0,8));
				PE_SHP_O18_QWr01(shp_lc_ctrl_02,		reg_lc_lap_weight,	GET_BITS(pp->shp_ui_main_vsd[3],0,8));
				PE_SHP_O18_QWr01(shp_mp_ctrl_02,		reg_mp_lap_weight,	GET_BITS(pp->shp_ui_main_vsd[4],0,8));
				PE_SHP_O18_QWr01(shp_sp_ctrl_02,		reg_sp_lap_weight,	GET_BITS(pp->shp_ui_main_vsd[5],0,8));
				PE_SHP_O18_QWr02(shp_der_ctrl_06,		reg_der_a_lut_y0,	GET_BITS(pp->shp_ui_main_vsd[6],0,8),\
														reg_der_a_lut_y1,	GET_BITS(pp->shp_ui_main_vsd[7],0,8));
				PE_SHP_O18_QWr02(shp_der_ctrl_07,		reg_der_a_lut_y2,	GET_BITS(pp->shp_ui_main_vsd[8],0,8),\
														reg_der_a_lut_y3,	GET_BITS(pp->shp_ui_main_vsd[9],0,8));
				PE_SHP_O18_QWr01(shp_dir_blur_ctrl_01,	reg_dir_blur_gain,	GET_BITS(pp->shp_ui_main_vsd[10],0,8));
				PE_SHP_O18_QWr01(shp_dj_ctrl_1d,		reg_dj_soft_g0_mul,	GET_BITS(pp->shp_ui_main_vsd[11],0,6));
				PE_SHP_O18_QWr01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul,	GET_BITS(pp->shp_ui_main_vsd[12],0,6));
				PE_SHP_O18_QWr01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul,	GET_BITS(pp->shp_ui_main_vsd[13],0,6));
				PE_SHP_O18_QWr01(shp_nntg_ctrl_0e,		reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_vsd[14],0,8));

				PE_SHP_O18_QWr03(shp_sti_ctrl_00,		reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_vsd[0],0,8),\
														reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_vsd[1],0,8),\
														reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_vsd[2],0,8));
				PE_DNR0_O18_QWr01(reg_cti_ctrl_0,		cti_gain,				GET_BITS(pp->shp_cti_ui_main_vsd[0],0,8));
				PE_DNR0_O18_QWr01(reg_cti_ctrl_2,		reg_ycm_band_sel,		GET_BITS(pp->shp_cti_ui_main_vsd[1],0,3));
				PE_SHP_O18_QWr01(shp_cti_ctrl_00,		reg_cti_gain,			GET_BITS(pp->shp_cti_ui_main_vsd[2],0,8));
				PE_SHP_O18_QWr01(shp_cti_ctrl_02,		reg_cti_ycm_band_sel,	GET_BITS(pp->shp_cti_ui_main_vsd[3],0,3));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_RE6_CMN_T *pp = (LX_PE_SHP_RE6_CMN_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ui_main_vsd;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O18_QRd01(shp_esf_ctrl_01,	reg_esf_master_gain,	pp->shp_ui_main_vsd[0]);
				PE_SHP_O18_QRd01(shp_dctp_ctrl_1d,	reg_dctp_gain,			pp->shp_ui_main_vsd[1]);
				PE_SHP_O18_QRd01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	pp->shp_ui_main_vsd[2]);
				PE_SHP_O18_QRd01(shp_lc_ctrl_02,	reg_lc_lap_weight,	pp->shp_ui_main_vsd[3]);
				PE_SHP_O18_QRd01(shp_mp_ctrl_02,	reg_mp_lap_weight,	pp->shp_ui_main_vsd[4]);
				PE_SHP_O18_QRd01(shp_sp_ctrl_02,	reg_sp_lap_weight,	pp->shp_ui_main_vsd[5]);
				PE_SHP_O18_QRd02(shp_der_ctrl_06,	reg_der_a_lut_y0,	pp->shp_ui_main_vsd[6],\
													reg_der_a_lut_y1,	pp->shp_ui_main_vsd[7]);
				PE_SHP_O18_QRd02(shp_der_ctrl_07,	reg_der_a_lut_y2,	pp->shp_ui_main_vsd[8],\
													reg_der_a_lut_y3,	pp->shp_ui_main_vsd[9]);
				PE_SHP_O18_QRd01(shp_dir_blur_ctrl_01,	reg_dir_blur_gain,	pp->shp_ui_main_vsd[10]);
				PE_SHP_O18_QRd01(shp_dj_ctrl_1d,	reg_dj_soft_g0_mul,	pp->shp_ui_main_vsd[11]);
				PE_SHP_O18_QRd01(shp_dj_ctrl_1e,	reg_dj_soft_g1_mul,	pp->shp_ui_main_vsd[12]);
				PE_SHP_O18_QRd01(shp_dj_ctrl_1f,	reg_dj_soft_g2_mul,	pp->shp_ui_main_vsd[13]);
				PE_SHP_O18_QRd01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	pp->shp_ui_main_vsd[14]);
				PE_SHP_O18_QRd03(shp_sti_ctrl_00,	reg_sti_master_gain,	pp->shp_ti_ui_main_vsd[0],\
												reg_sti_edge_gain,	pp->shp_ti_ui_main_vsd[1],\
												reg_sti_texture_gain,	pp->shp_ti_ui_main_vsd[2]);
				PE_DNR0_O18_QRd01(reg_cti_ctrl_0,	cti_gain,	pp->shp_cti_ui_main_vsd[0]);
				PE_DNR0_O18_QRd01(reg_cti_ctrl_2,	reg_ycm_band_sel,	pp->shp_cti_ui_main_vsd[1]);
				PE_SHP_O18_QRd01(shp_cti_ctrl_00,	reg_cti_gain,	pp->shp_cti_ui_main_vsd[2]);
				PE_SHP_O18_QRd01(shp_cti_ctrl_02,	reg_cti_ycm_band_sel,	pp->shp_cti_ui_main_vsd[3]);
			}

			pd = pp->shp_ui_main_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_main_vsd\n"
			"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);
			pd = pp->shp_ti_ui_main_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ti_ui_main_vsd\n"
			"shp_ti_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			pd = pp->shp_cti_ui_main_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_cti_ui_main_vsd\n"
			"shp_cti_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set resolution horizontal control
 * - use input struct LX_PE_SHP_RE2_HOR_T for O18X
 * - use input struct LX_PE_SHP_RE1_HOR_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_HOR_T *pp=(LX_PE_SHP_RE5_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_h_main_vsd\n"
			"shp_ui_h_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_M17_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_RES_WR01(shp_der_ctrl_00,	reg_derh_csft_gain,			GET_BITS(pp->shp_ui_h_main_vsd[0],0,6));
				PE_SHP_HW_O18_RES_WR02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_vsd[1],0,6),\
														reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_vsd[2],0,6));
				PE_SHP_HW_O18_RES_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_vsd[3],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_vsd[4],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_pti_ctrl_01,	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_vsd[5],0,8));
				#else
				PE_SHP_M17_QWr01(shp_der_ctrl_00,	reg_derh_csft_gain,			GET_BITS(pp->shp_ui_h_main_vsd[0],0,6));
				PE_SHP_M17_QWr02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_vsd[1],0,6),\
													reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_vsd[2],0,6));
				PE_SHP_M17_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_vsd[3],0,8));
				PE_SHP_M17_QWr01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_vsd[4],0,8));
				PE_SHP_M17_QWr01(shp_pti_ctrl_01,	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_vsd[5],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get resolution horizontal control
 * - use input struct LX_PE_SHP_RE2_HOR_T for O18X
 * - use input struct LX_PE_SHP_RE1_HOR_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_HOR_T *pp = (LX_PE_SHP_RE5_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_vsd;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O18_QRd01(shp_der_ctrl_00,	reg_derh_csft_gain,			pp->shp_ui_h_main_vsd[0]);
				PE_SHP_O18_QRd02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,pp->shp_ui_h_main_vsd[1],\
													reg_derh_edge_filter_gain_b,pp->shp_ui_h_main_vsd[2]);
				PE_SHP_O18_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			pp->shp_ui_h_main_vsd[3]);
				PE_SHP_O18_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			pp->shp_ui_h_main_vsd[4]);
				PE_SHP_O18_QRd01(shp_pti_ctrl_01,	reg_ptih_master_gain,		pp->shp_ui_h_main_vsd[5]);
			}

			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_h_main_vsd\n"
				"shp_ui_h_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for O18X
 * - use input struct LX_PE_SHP_RE1_VER_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_VER_T *pp=(LX_PE_SHP_RE5_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_v_main_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_v_main_post\n"\
			"shp_ui_v_main_post[00]0x%02X,0x%02X\n",\
			pp->win_id,	pd[0],  pd[1]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_RES_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v ,	GET_BITS(pp->shp_ui_v_main_vsd[0],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_vsd[1],0,8));
				#else
				PE_SHP_O18_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_v ,	GET_BITS(pp->shp_ui_v_main_vsd[0],0,8));
				PE_SHP_O18_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_vsd[1],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for O18X
 * - use input struct LX_PE_SHP_RE1_VER_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_VER_T *pp = (LX_PE_SHP_RE5_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_v_main_vsd;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O18_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v ,		pp->shp_ui_v_main_vsd[0]);
				PE_SHP_O18_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	pp->shp_ui_v_main_vsd[1]);
			}
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_v_main_vsd\n"
			"shp_ui_v_main_vsd    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for O18X
 * - use input struct LX_PE_SHP_RE1_MISC_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{ 
			UINT8 *pd;
			LX_PE_SHP_RE7_MISC_T *pp=(LX_PE_SHP_RE7_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_cmn_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_cmn_vsd\n"
			"shp_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd    [20]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22]);

			pd = pp->shp_djg_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_djg_vsd\n"
			"shp_djg_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_map_cmn_vsd\n"
			"shp_map_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);

			pd = pp->shp_balance_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_balance_vsd\n"
			"shp_balance_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ti_cmn_vsd\n"
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);

			pd = pp->shp_simple_snr_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_simple_snr_vsd\n"
			"shp_simple_snr_vsd    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);

			pd = pp->shp_cti_cmn_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_cti_cmn_vsd\n"
			"shp_cti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_motion_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_motion_vsd\n"
			"shp_motion_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8]);

			pd = pp->shp_chroma_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_chroma_vsd\n"
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				/*shp_cmn_vsd*/
				PE_SHP_HW_O18_RES_WR02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_vsd[0],0,1),\
														reg_derh_bflt_tap_size,	GET_BITS(pp->shp_cmn_vsd[1],0,3));
				PE_SHP_HW_O18_RES_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,	GET_BITS(pp->shp_cmn_vsd[2],0,1));
				PE_SHP_HW_O18_RES_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,	GET_BITS(pp->shp_cmn_vsd[3],0,1));
				PE_SHP_HW_O18_RES_WR02(shp_mp_ctrl_01,	reg_mp_im_os_gain  ,	GET_BITS(pp->shp_cmn_vsd[4],0,7),\
														reg_mp_im_us_gain   ,	GET_BITS(pp->shp_cmn_vsd[5],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_cmn_vsd[6],0,7),\
														reg_sp_im_us_gain,	GET_BITS(pp->shp_cmn_vsd[7],0,7));
				PE_SHP_HW_O18_RES_WR01(shp_esf_ctrl_00,	reg_esf_en,	GET_BITS(pp->shp_cmn_vsd[8],0,1));
				PE_SHP_HW_O18_RES_WR03(shp_esf_ctrl_01,	reg_esf_min_ratio,	GET_BITS(pp->shp_cmn_vsd[9],0,8),\
														reg_esf_base,	GET_BITS(pp->shp_cmn_vsd[10],0,8),\
														reg_esf_max_clip,	GET_BITS(pp->shp_cmn_vsd[11],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_dctp_ctrl_00,reg_dctp_en,	GET_BITS(pp->shp_cmn_vsd[12],0,1));
				PE_SHP_HW_O18_RES_WR02(shp_dctp_ctrl_1e,reg_dctp_coring_en,	GET_BITS(pp->shp_cmn_vsd[13],0,1),\
														reg_dctp_coring_mode,	GET_BITS(pp->shp_cmn_vsd[14],0,2));
				PE_SHP_HW_O18_RES_WR01(shp_tgen_ctrl_00,reg_tgen_on_off,	GET_BITS(pp->shp_cmn_vsd[15],0,1));
				PE_SHP_HW_O18_RES_WR02(shp_tgen_ctrl_0a,reg_tgen_coring_en,	GET_BITS(pp->shp_cmn_vsd[16],0,1),\
														reg_tgen_coring_mode,	GET_BITS(pp->shp_cmn_vsd[17],0,2));
				PE_SHP_HW_O18_RES_WR01(shp_nntg_ctrl_00,reg_nntg_en,	GET_BITS(pp->shp_cmn_vsd[18],0,1));
				PE_SHP_HW_O18_RES_WR02(shp_nntg_ctrl_0f,reg_nntg_coring_en,	GET_BITS(pp->shp_cmn_vsd[19],0,1),\
																reg_nntg_coring_mode,	GET_BITS(pp->shp_cmn_vsd[20],0,2));
				PE_SHP_HW_O18_RES_WR01(shp_dir_blur_ctrl_00,	reg_dir_blur_en,	GET_BITS(pp->shp_cmn_vsd[21],0,1));
				PE_SHP_HW_O18_RES_WR01(shp_dir_blur_ctrl_01,	reg_dir_blur_base,	GET_BITS(pp->shp_cmn_vsd[22],0,8));

				/*shp_djg_vsd*/
				PE_SHP_HW_O18_RES_WR03(shp_dj_ctrl_00,	reg_dj_edf_en,	GET_BITS(pp->shp_djg_vsd[0],0,1),\
														reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_vsd[1],0,1),\
														reg_dj_soft_en, GET_BITS(pp->shp_djg_vsd[2],0,1));
				PE_SHP_HW_O18_RES_WR02(shp_dj_ctrl_03,	reg_dj_edge_min,	GET_BITS(pp->shp_djg_vsd[3],0,8),\
														reg_dj_edge_mul,	GET_BITS(pp->shp_djg_vsd[4],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_dj_ctrl_00,	reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_vsd[5],0,2),\
														reg_dj_n_avg_mode,	GET_BITS(pp->shp_djg_vsd[6],0,1));
				PE_SHP_HW_O18_RES_WR01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,	GET_BITS(pp->shp_djg_vsd[7],0,8));

				/*shp_map_cmn_vsd */
				PE_SHP_HW_O18_RES_WR02(shp_fd_ctrl_09,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[0],0,1),\
														reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
				PE_SHP_HW_O18_RES_WR04(shp_fd_ctrl_0b,	reg_fd_mnr_gain_x0,	GET_BITS(pp->shp_map_cmn_vsd[2],0,8),\
														reg_fd_mnr_gain_x1,	GET_BITS(pp->shp_map_cmn_vsd[3],0,8),\
														reg_fd_mnr_gain_y0,	GET_BITS(pp->shp_map_cmn_vsd[4],0,8),\
														reg_fd_mnr_gain_y1,	GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
				PE_SHP_HW_O18_RES_WR04(shp_fd_ctrl_07,	reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_vsd[6],0,8),\
														reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_vsd[7],0,8),\
														reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_vsd[8],0,8),\
														reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_vsd[9],0,8));
				PE_SHP_HW_O18_RES_WR04(shp_fd_ctrl_08,	reg_fd_detail_minmax_x0,	GET_BITS(pp->shp_map_cmn_vsd[10],0,8),\
														reg_fd_detail_minmax_y0,	GET_BITS(pp->shp_map_cmn_vsd[11],0,8),\
														reg_fd_detail_minmax_x1,	GET_BITS(pp->shp_map_cmn_vsd[12],0,8),\
														reg_fd_detail_minmax_y1,	GET_BITS(pp->shp_map_cmn_vsd[13],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_fd_ctrl_0f,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[14],0,1),\
														reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[15],0,1));
				PE_SHP_HW_O18_RES_WR04(shp_fd_ctrl_12,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_vsd[16],0,6),\
														reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_vsd[17],0,6),\
														reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_vsd[18],0,6),\
														reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_vsd[19],0,6));

				/*shp_balance_vsd*/
				PE_SHP_HW_O18_RES_WR03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_vsd[0],0,1),\
														reg_mp_gb_mode, GET_BITS(pp->shp_balance_vsd[1],0,1),\
														reg_mp_gb_y1,	GET_BITS(pp->shp_balance_vsd[2],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_vsd[3],0,8),\
														reg_mp_gb_y3,	GET_BITS(pp->shp_balance_vsd[4],0,8));
				PE_SHP_HW_O18_RES_WR03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_vsd[5],0,1),\
														reg_sp_gb_mode, GET_BITS(pp->shp_balance_vsd[6],0,1),\
														reg_sp_gb_y1,	GET_BITS(pp->shp_balance_vsd[7],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_vsd[8],0,8),\
														reg_sp_gb_y3,	GET_BITS(pp->shp_balance_vsd[9],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_vsd[10],0,1),\
														reg_lc_gb_en,	GET_BITS(pp->shp_balance_vsd[11],0,1));
				PE_SHP_HW_O18_RES_WR02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_vsd[12],0,8),\
														reg_lc_gb_y2,	GET_BITS(pp->shp_balance_vsd[13],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_vsd[14],0,8));
				PE_SHP_HW_O18_RES_WR03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_vsd[15],0,8),\
														reg_lc_center_gain, GET_BITS(pp->shp_balance_vsd[16],0,8),\
														reg_lc_local_gain,	GET_BITS(pp->shp_balance_vsd[17],0,8));
				PE_SHP_HW_O18_RES_WR03(shp_mp_ctrl_08,	reg_mp_lum1_y0, GET_BITS(pp->shp_balance_vsd[18],0,8),\
														reg_mp_lum1_y1, GET_BITS(pp->shp_balance_vsd[19],0,8),\
														reg_mp_lum1_y2, GET_BITS(pp->shp_balance_vsd[20],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_mp_ctrl_09,	reg_mp_lum2_y0, GET_BITS(pp->shp_balance_vsd[21],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, GET_BITS(pp->shp_balance_vsd[22],0,8),\
														reg_mp_lum2_y2, GET_BITS(pp->shp_balance_vsd[23],0,8));
				PE_SHP_HW_O18_RES_WR03(shp_sp_ctrl_08,	reg_sp_lum1_y0, GET_BITS(pp->shp_balance_vsd[24],0,8),\
														reg_sp_lum1_y1, GET_BITS(pp->shp_balance_vsd[25],0,8),\
														reg_sp_lum1_y2, GET_BITS(pp->shp_balance_vsd[26],0,8));
				PE_SHP_HW_O18_RES_WR01(shp_sp_ctrl_09,	reg_sp_lum2_y0, GET_BITS(pp->shp_balance_vsd[27],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, GET_BITS(pp->shp_balance_vsd[28],0,8),\
														reg_sp_lum2_y2, GET_BITS(pp->shp_balance_vsd[29],0,8));
				/*shp_ti_cmn_vsd*/
				PE_SHP_HW_O18_RES_WR04(shp_pti_ctrl_00,	reg_ptiv_enable,	GET_BITS(pp->shp_ti_cmn_vsd[0],0,1),\
														reg_ptiv_ti_mode,	GET_BITS(pp->shp_ti_cmn_vsd[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
				PE_SHP_HW_O18_RES_WR04(shp_pti_ctrl_01,	reg_ptih_enable,	GET_BITS(pp->shp_ti_cmn_vsd[4],0,1),\
														reg_ptih_ti_mode,	GET_BITS(pp->shp_ti_cmn_vsd[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
				PE_SHP_HW_O18_RES_WR04(shp_sti_ctrl_00,	reg_sti_enable,	GET_BITS(pp->shp_ti_cmn_vsd[8],0,1),\
														reg_sti_ti_mode,	GET_BITS(pp->shp_ti_cmn_vsd[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
				/*shp_simple_snr_vsd*/
				PE_SHP_HW_O18_RES_WR03(shp_snr_ctrl_00,	reg_snr_blur_en,	GET_BITS(pp->shp_simple_snr_vsd[0],0,1),\
														reg_snr_blur_sel,	GET_BITS(pp->shp_simple_snr_vsd[1],0,2),\
														reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_vsd[2],0,8));
				/*shp_cti_cmn_vsd*/
				PE_SHP_HW_O18_DNR_CTI_WR04(reg_cti_ctrl_0,	cti_en,	GET_BITS(pp->shp_cti_cmn_vsd[0],0,1),\
													cti_tap,	GET_BITS(pp->shp_cti_cmn_vsd[2],0,2),\
													cti_pre_flt_mode,	GET_BITS(pp->shp_cti_cmn_vsd[3],0,1),\
													cti_clipping_mode,	GET_BITS(pp->shp_cti_cmn_vsd[4],0,1));
				PE_SHP_HW_O18_DNR_CTI_WR01(reg_cti_ctrl_2,	reg_ycm_en,	GET_BITS(pp->shp_cti_cmn_vsd[1],0,1));
				PE_SHP_HW_O18_SHP_CTI_WR02(shp_cti_ctrl_00,	reg_cti_en,	GET_BITS(pp->shp_cti_cmn_vsd[5],0,1),\
													reg_cti_filter_tap_size,	GET_BITS(pp->shp_cti_cmn_vsd[7],0,3));
				PE_SHP_HW_O18_SHP_CTI_WR01(shp_cti_ctrl_02,	reg_cti_ycm_en,	GET_BITS(pp->shp_cti_cmn_vsd[6],0,1));

				/*shp_motion_vsd*/
				PE_SHP_HW_O18_RES_WR01(shp_motion_prot_ctrl_00,	reg_motion_prot_adaptive_en,	GET_BITS(pp->shp_motion_vsd[0],0,1));
				PE_SHP_HW_O18_RES_WR02(shp_motion_prot_ctrl_01,	reg_motion_prot_lut_a_y0,	GET_BITS(pp->shp_motion_vsd[1],0,8),\
																reg_motion_prot_lut_a_y1,	GET_BITS(pp->shp_motion_vsd[2],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_motion_prot_ctrl_02,	reg_motion_prot_lut_a_y2,	GET_BITS(pp->shp_motion_vsd[3],0,8),\
																reg_motion_prot_lut_a_y3,	GET_BITS(pp->shp_motion_vsd[4],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_motion_prot_ctrl_03,	reg_motion_prot_lut_t_y0,	GET_BITS(pp->shp_motion_vsd[5],0,8),\
																reg_motion_prot_lut_t_y1,	GET_BITS(pp->shp_motion_vsd[6],0,8));
				PE_SHP_HW_O18_RES_WR02(shp_motion_prot_ctrl_04,	reg_motion_prot_lut_t_y2,	GET_BITS(pp->shp_motion_vsd[7],0,8),\
																reg_motion_prot_lut_t_y3,	GET_BITS(pp->shp_motion_vsd[8],0,8));
				/*shp_chroma_vsd*/
				PE_SHP_HW_O18_RES_WR03(shp_chroma_ctrl_00,	reg_color_region_en,	GET_BITS(pp->shp_chroma_vsd[0],0,1),\
															reg_chr_protection_en,	GET_BITS(pp->shp_chroma_vsd[1],0,1),\
															reg_chr_compensation_en,	GET_BITS(pp->shp_chroma_vsd[2],0,1));
				PE_SHP_HW_O18_RES_WR02(shp_chroma_ctrl_0d,	reg_chr_gain_r0_gain,	GET_BITS(pp->shp_chroma_vsd[3],0,8),\
															reg_chr_gain_r1_gain,	GET_BITS(pp->shp_chroma_vsd[4],0,8));
				#if 0
				#ifdef PE_SHP_HW_O18_SHP_MOTION_ENABLE
				PE_SHP_O18_QWr01(shp_fsw_ctrl_00,			dnr_decont,		GET_BITS(pp->shp_motion_post[0],0,1));
				PE_SHP_HW_O18_RES_SET_USER(shp_motion_ctrl_00, reg_motion_adaptive_en, GET_BITS(pp->shp_motion_post[0],0,1));
				#else
				PE_SHP_HW_O18_RES_WR01(shp_motion_ctrl_00,	reg_motion_adaptive_en,	GET_BITS(pp->shp_motion_post[0],0,1));
				#endif
				#endif
				#else
				/*shp_cmn_vsd*/
				PE_SHP_O18_QWr02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_vsd[0],0,1),\
													reg_derh_bflt_tap_size,	GET_BITS(pp->shp_cmn_vsd[1],0,3));
				PE_SHP_O18_QWr01(shp_mp_ctrl_00,	reg_mp_shp_en,	GET_BITS(pp->shp_cmn_vsd[2],0,1));
				PE_SHP_O18_QWr01(shp_sp_ctrl_00,	reg_sp_shp_en,	GET_BITS(pp->shp_cmn_vsd[3],0,1));
				PE_SHP_O18_QWr02(shp_mp_ctrl_01,	reg_mp_im_os_gain  ,	GET_BITS(pp->shp_cmn_vsd[4],0,7),\
													reg_mp_im_us_gain   ,	GET_BITS(pp->shp_cmn_vsd[5],0,7));
				PE_SHP_O18_QWr02(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_cmn_vsd[6],0,7),\
													reg_sp_im_us_gain,	GET_BITS(pp->shp_cmn_vsd[7],0,7));
				PE_SHP_O18_QWr01(shp_esf_ctrl_00,	reg_esf_en,	GET_BITS(pp->shp_cmn_vsd[8],0,1));
				PE_SHP_O18_QWr03(shp_esf_ctrl_01,	reg_esf_min_ratio,	GET_BITS(pp->shp_cmn_vsd[9],0,8),\
													reg_esf_base,	GET_BITS(pp->shp_cmn_vsd[10],0,8),\
													reg_esf_max_clip,	GET_BITS(pp->shp_cmn_vsd[11],0,8));
				PE_SHP_O18_QWr01(shp_dctp_ctrl_00,	reg_dctp_en,	GET_BITS(pp->shp_cmn_vsd[12],0,1));
				PE_SHP_O18_QWr02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,	GET_BITS(pp->shp_cmn_vsd[13],0,1),\
													reg_dctp_coring_mode,	GET_BITS(pp->shp_cmn_vsd[14],0,2));
				PE_SHP_O18_QWr01(shp_tgen_ctrl_00,	reg_tgen_on_off,	GET_BITS(pp->shp_cmn_vsd[15],0,1));
				PE_SHP_O18_QWr02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,	GET_BITS(pp->shp_cmn_vsd[16],0,1),\
													reg_tgen_coring_mode,	GET_BITS(pp->shp_cmn_vsd[17],0,2));
				PE_SHP_O18_QWr01(shp_nntg_ctrl_00,	reg_nntg_en,	GET_BITS(pp->shp_cmn_vsd[18],0,1));
				PE_SHP_O18_QWr02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,	GET_BITS(pp->shp_cmn_vsd[19],0,1),\
													reg_nntg_coring_mode,	GET_BITS(pp->shp_cmn_vsd[20],0,2));
				PE_SHP_O18_QWr01(shp_dir_blur_ctrl_00,	reg_dir_blur_en,	GET_BITS(pp->shp_cmn_vsd[21],0,1));
				PE_SHP_O18_QWr01(shp_dir_blur_ctrl_01,	reg_dir_blur_base,	GET_BITS(pp->shp_cmn_vsd[22],0,8));

				/*shp_djg_vsd*/
				PE_SHP_O18_QWr03(shp_dj_ctrl_00,	reg_dj_edf_en,	GET_BITS(pp->shp_djg_vsd[0],0,1),\
													reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_vsd[1],0,1),\
													reg_dj_soft_en, GET_BITS(pp->shp_djg_vsd[2],0,1));
				PE_SHP_O18_QWr02(shp_dj_ctrl_03,	reg_dj_edge_min,	GET_BITS(pp->shp_djg_vsd[3],0,8),\
													reg_dj_edge_mul,	GET_BITS(pp->shp_djg_vsd[4],0,8));
				PE_SHP_O18_QWr02(shp_dj_ctrl_00,	reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_vsd[5],0,2),\
													reg_dj_n_avg_mode,			GET_BITS(pp->shp_djg_vsd[6],0,1));
				PE_SHP_O18_QWr01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			GET_BITS(pp->shp_djg_vsd[7],0,8));

				/*shp_map_cmn_vsd */
				PE_SHP_O18_QWr02(shp_fd_ctrl_09,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[0],0,1),\
													reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
				PE_SHP_O18_QWr04(shp_fd_ctrl_0b,	reg_fd_mnr_gain_x0,	GET_BITS(pp->shp_map_cmn_vsd[2],0,8),\
													reg_fd_mnr_gain_x1,	GET_BITS(pp->shp_map_cmn_vsd[3],0,8),\
													reg_fd_mnr_gain_y0,	GET_BITS(pp->shp_map_cmn_vsd[4],0,8),\
													reg_fd_mnr_gain_y1,	GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
				PE_SHP_O18_QWr04(shp_fd_ctrl_07,	reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_vsd[6],0,8),\
													reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_vsd[7],0,8),\
													reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_vsd[8],0,8),\
													reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_vsd[9],0,8));
				PE_SHP_O18_QWr04(shp_fd_ctrl_08,	reg_fd_detail_minmax_x0,	GET_BITS(pp->shp_map_cmn_vsd[10],0,8),\
													reg_fd_detail_minmax_y0,	GET_BITS(pp->shp_map_cmn_vsd[11],0,8),\
													reg_fd_detail_minmax_x1,	GET_BITS(pp->shp_map_cmn_vsd[12],0,8),\
													reg_fd_detail_minmax_y1,	GET_BITS(pp->shp_map_cmn_vsd[13],0,8));
				PE_SHP_O18_QWr02(shp_fd_ctrl_0f,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[14],0,1),\
													reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[15],0,1));
				PE_SHP_O18_QWr04(shp_fd_ctrl_12,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_vsd[16],0,6),\
													reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_vsd[17],0,6),\
													reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_vsd[18],0,6),\
													reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_vsd[19],0,6));

				/*shp_balance_vsd*/
				PE_SHP_O18_QWr03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_vsd[0],0,1),\
													reg_mp_gb_mode, GET_BITS(pp->shp_balance_vsd[1],0,1),\
													reg_mp_gb_y1,	GET_BITS(pp->shp_balance_vsd[2],0,8));
				PE_SHP_O18_QWr02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_vsd[3],0,8),\
													reg_mp_gb_y3,	GET_BITS(pp->shp_balance_vsd[4],0,8));
				PE_SHP_O18_QWr03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_vsd[5],0,1),\
													reg_sp_gb_mode, GET_BITS(pp->shp_balance_vsd[6],0,1),\
													reg_sp_gb_y1,	GET_BITS(pp->shp_balance_vsd[7],0,8));
				PE_SHP_O18_QWr02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_vsd[8],0,8),\
													reg_sp_gb_y3,	GET_BITS(pp->shp_balance_vsd[9],0,8));
				PE_SHP_O18_QWr02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_vsd[10],0,1),\
													reg_lc_gb_en,	GET_BITS(pp->shp_balance_vsd[11],0,1));
				PE_SHP_O18_QWr02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_vsd[12],0,8),\
													reg_lc_gb_y2,	GET_BITS(pp->shp_balance_vsd[13],0,8));
				PE_SHP_O18_QWr01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_vsd[14],0,8));
				PE_SHP_O18_QWr03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_vsd[15],0,8),\
													reg_lc_center_gain, GET_BITS(pp->shp_balance_vsd[16],0,8),\
													reg_lc_local_gain,	GET_BITS(pp->shp_balance_vsd[17],0,8));
				PE_SHP_O18_QWr03(shp_mp_ctrl_08,	reg_mp_lum1_y0, GET_BITS(pp->shp_balance_vsd[18],0,8),\
													reg_mp_lum1_y1, GET_BITS(pp->shp_balance_vsd[19],0,8),\
													reg_mp_lum1_y2, GET_BITS(pp->shp_balance_vsd[20],0,8));
				PE_SHP_O18_QWr01(shp_mp_ctrl_09,	reg_mp_lum2_y0, GET_BITS(pp->shp_balance_vsd[21],0,8));
				PE_SHP_O18_QWr02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, GET_BITS(pp->shp_balance_vsd[22],0,8),\
													reg_mp_lum2_y2, GET_BITS(pp->shp_balance_vsd[23],0,8));
				PE_SHP_O18_QWr03(shp_sp_ctrl_08,	reg_sp_lum1_y0, GET_BITS(pp->shp_balance_vsd[24],0,8),\
													reg_sp_lum1_y1, GET_BITS(pp->shp_balance_vsd[25],0,8),\
													reg_sp_lum1_y2, GET_BITS(pp->shp_balance_vsd[26],0,8));
				PE_SHP_O18_QWr01(shp_sp_ctrl_09,	reg_sp_lum2_y0, GET_BITS(pp->shp_balance_vsd[27],0,8));
				PE_SHP_O18_QWr02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, GET_BITS(pp->shp_balance_vsd[28],0,8),\
													reg_sp_lum2_y2, GET_BITS(pp->shp_balance_vsd[29],0,8));
				/*shp_ti_cmn_vsd*/
				PE_SHP_O18_QWr04(shp_pti_ctrl_00,	reg_ptiv_enable,	GET_BITS(pp->shp_ti_cmn_vsd[0],0,1),\
													reg_ptiv_ti_mode,	GET_BITS(pp->shp_ti_cmn_vsd[1],0,1),\
													reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[2],0,2),\
													reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
				PE_SHP_O18_QWr04(shp_pti_ctrl_01,	reg_ptih_enable,	GET_BITS(pp->shp_ti_cmn_vsd[4],0,1),\
													reg_ptih_ti_mode,	GET_BITS(pp->shp_ti_cmn_vsd[5],0,1),\
													reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[6],0,2),\
													reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
				PE_SHP_O18_QWr04(shp_sti_ctrl_00,	reg_sti_enable,	GET_BITS(pp->shp_ti_cmn_vsd[8],0,1),\
													reg_sti_ti_mode,	GET_BITS(pp->shp_ti_cmn_vsd[9],0,1),\
													reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[10],0,2),\
													reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
				/*shp_simple_snr_vsd*/
				PE_SHP_O18_QWr03(shp_snr_ctrl_00,	reg_snr_blur_en,	GET_BITS(pp->shp_simple_snr_vsd[0],0,1),\
													reg_snr_blur_sel,	GET_BITS(pp->shp_simple_snr_vsd[1],0,2),\
													reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_vsd[2],0,8));
				/*shp_cti_cmn_vsd*/
				PE_DNR0_O18_QWr04(reg_cti_ctrl_0,	cti_en,	GET_BITS(pp->shp_cti_cmn_vsd[0],0,1),\
													cti_tap,	GET_BITS(pp->shp_cti_cmn_vsd[2],0,2),\
													cti_pre_flt_mode,	GET_BITS(pp->shp_cti_cmn_vsd[3],0,1),\
													cti_clipping_mode,	GET_BITS(pp->shp_cti_cmn_vsd[4],0,1));
				PE_DNR0_O18_QWr01(reg_cti_ctrl_2,	reg_ycm_en,	GET_BITS(pp->shp_cti_cmn_vsd[1],0,1));
				PE_SHP_O18_QWr02(shp_cti_ctrl_00,	reg_cti_en,					GET_BITS(pp->shp_cti_cmn_vsd[5],0,1),\
													reg_cti_filter_tap_size,	GET_BITS(pp->shp_cti_cmn_vsd[7],0,3));
				PE_SHP_O18_QWr01(shp_cti_ctrl_02,	reg_cti_ycm_en,	GET_BITS(pp->shp_cti_cmn_vsd[6],0,1));

				/*shp_motion_vsd*/
				PE_SHP_O18_QWr01(shp_motion_prot_ctrl_00,	reg_motion_prot_adaptive_en,	GET_BITS(pp->shp_motion_vsd[0],0,1));
				PE_SHP_O18_QWr02(shp_motion_prot_ctrl_01,	reg_motion_prot_lut_a_y0,	GET_BITS(pp->shp_motion_vsd[1],0,8),\
															reg_motion_prot_lut_a_y1,	GET_BITS(pp->shp_motion_vsd[2],0,8));
				PE_SHP_O18_QWr02(shp_motion_prot_ctrl_02,	reg_motion_prot_lut_a_y2,	GET_BITS(pp->shp_motion_vsd[3],0,8),\
															reg_motion_prot_lut_a_y3,	GET_BITS(pp->shp_motion_vsd[4],0,8));
				PE_SHP_O18_QWr02(shp_motion_prot_ctrl_03,	reg_motion_prot_lut_t_y0,	GET_BITS(pp->shp_motion_vsd[5],0,8),\
															reg_motion_prot_lut_t_y1,	GET_BITS(pp->shp_motion_vsd[6],0,8));
				PE_SHP_O18_QWr02(shp_motion_prot_ctrl_04,	reg_motion_prot_lut_t_y2,	GET_BITS(pp->shp_motion_vsd[7],0,8),\
															reg_motion_prot_lut_t_y3,	GET_BITS(pp->shp_motion_vsd[8],0,8));
				/*shp_chroma_vsd*/
				PE_SHP_O18_QWr03(shp_chroma_ctrl_00,	reg_color_region_en,	GET_BITS(pp->shp_chroma_vsd[0],0,1),\
														reg_chr_protection_en,	GET_BITS(pp->shp_chroma_vsd[1],0,1),\
														reg_chr_compensation_en,	GET_BITS(pp->shp_chroma_vsd[2],0,1));
				PE_SHP_O18_QWr02(shp_chroma_ctrl_0d,	reg_chr_gain_r0_gain,	GET_BITS(pp->shp_chroma_vsd[3],0,8),\
														reg_chr_gain_r1_gain,	GET_BITS(pp->shp_chroma_vsd[4],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		
	} while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for O18X
 * - use input struct LX_PE_SHP_RE1_MISC_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_RE7_MISC_T *pp=(LX_PE_SHP_RE7_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				
 				/*shp_cmn_vsd*/
				PE_SHP_O18_QRd02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	pp->shp_cmn_vsd[0],\
													reg_derh_bflt_tap_size,		pp->shp_cmn_vsd[1]);
				PE_SHP_O18_QRd01(shp_mp_ctrl_00,	reg_mp_shp_en,				pp->shp_cmn_vsd[2]);
				PE_SHP_O18_QRd01(shp_sp_ctrl_00,	reg_sp_shp_en,				pp->shp_cmn_vsd[3]);
				PE_SHP_O18_QRd02(shp_mp_ctrl_01,	reg_mp_im_os_gain  ,		pp->shp_cmn_vsd[4],\
													reg_mp_im_us_gain   ,		pp->shp_cmn_vsd[5]);
				PE_SHP_O18_QRd02(shp_sp_ctrl_01,	reg_sp_im_os_gain,			pp->shp_cmn_vsd[6],\
													reg_sp_im_us_gain,			pp->shp_cmn_vsd[7]);
				PE_SHP_O18_QRd01(shp_esf_ctrl_00,	reg_esf_en,					pp->shp_cmn_vsd[8]);
				PE_SHP_O18_QRd03(shp_esf_ctrl_01,	reg_esf_min_ratio,			pp->shp_cmn_vsd[9],\
													reg_esf_base,				pp->shp_cmn_vsd[10],\
													reg_esf_max_clip,			pp->shp_cmn_vsd[11]);
				PE_SHP_O18_QRd01(shp_dctp_ctrl_00,	reg_dctp_en,				pp->shp_cmn_vsd[12]);
				PE_SHP_O18_QRd02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,			pp->shp_cmn_vsd[13],\
													reg_dctp_coring_mode,		pp->shp_cmn_vsd[14]);
				PE_SHP_O18_QRd01(shp_tgen_ctrl_00,	reg_tgen_on_off,			pp->shp_cmn_vsd[15]);
				PE_SHP_O18_QRd02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,			pp->shp_cmn_vsd[16],\
													reg_tgen_coring_mode,		pp->shp_cmn_vsd[17]);
				PE_SHP_O18_QRd01(shp_nntg_ctrl_00,	reg_nntg_en,				pp->shp_cmn_vsd[18]);
				PE_SHP_O18_QRd02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,			pp->shp_cmn_vsd[19],\
													reg_nntg_coring_mode,		pp->shp_cmn_vsd[20]);
				PE_SHP_O18_QRd01(shp_dir_blur_ctrl_00,	reg_dir_blur_en,		pp->shp_cmn_vsd[21]);
				PE_SHP_O18_QRd01(shp_dir_blur_ctrl_01,	reg_dir_blur_base,		pp->shp_cmn_vsd[22]);

				/*shp_djg_vsd*/
				PE_SHP_O18_QRd03(shp_dj_ctrl_00,	reg_dj_edf_en,				pp->shp_djg_vsd[0],\
													reg_dj_edge_adaptive_en,	pp->shp_djg_vsd[1],\
													reg_dj_soft_en, 			pp->shp_djg_vsd[2]);
				PE_SHP_O18_QRd02(shp_dj_ctrl_03,	reg_dj_edge_min,			pp->shp_djg_vsd[3],\
													reg_dj_edge_mul,			pp->shp_djg_vsd[4]);
				PE_SHP_O18_QRd02(shp_dj_ctrl_00,	reg_dj_center_blur_mode,	pp->shp_djg_vsd[5],\
													reg_dj_n_avg_mode,			pp->shp_djg_vsd[6]);
				PE_SHP_O18_QRd01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			pp->shp_djg_vsd[7]);

				/*shp_map_cmn_vsd */
				PE_SHP_O18_QRd02(shp_fd_ctrl_09,	reg_fd_mnr_gain_e_en,		pp->shp_map_cmn_vsd[0],\
													reg_fd_mnr_gain_t_en,		pp->shp_map_cmn_vsd[1]);
				PE_SHP_O18_QRd04(shp_fd_ctrl_0b,	reg_fd_mnr_gain_x0,			pp->shp_map_cmn_vsd[2],\
													reg_fd_mnr_gain_x1,			pp->shp_map_cmn_vsd[3],\
													reg_fd_mnr_gain_y0,			pp->shp_map_cmn_vsd[4],\
													reg_fd_mnr_gain_y1,			pp->shp_map_cmn_vsd[5]);
				PE_SHP_O18_QRd04(shp_fd_ctrl_07,	reg_fd_edge_minmax_x0,		pp->shp_map_cmn_vsd[6],\
													reg_fd_edge_minmax_y0,		pp->shp_map_cmn_vsd[7],\
													reg_fd_edge_minmax_x1,		pp->shp_map_cmn_vsd[8],\
													reg_fd_edge_minmax_y1,		pp->shp_map_cmn_vsd[9]);
				PE_SHP_O18_QRd04(shp_fd_ctrl_08,	reg_fd_detail_minmax_x0,	pp->shp_map_cmn_vsd[10],\
													reg_fd_detail_minmax_y0,	pp->shp_map_cmn_vsd[11],\
													reg_fd_detail_minmax_x1,	pp->shp_map_cmn_vsd[12],\
													reg_fd_detail_minmax_y1,	pp->shp_map_cmn_vsd[13]);
				PE_SHP_O18_QRd02(shp_fd_ctrl_0f,	reg_fd_soft_gain_t_en,		pp->shp_map_cmn_vsd[14],\
													reg_fd_soft_gain_e_en,		pp->shp_map_cmn_vsd[15]);
				PE_SHP_O18_QRd04(shp_fd_ctrl_12,	reg_fd_soft_score_y3,		pp->shp_map_cmn_vsd[16],\
													reg_fd_soft_score_y2,		pp->shp_map_cmn_vsd[17],\
													reg_fd_soft_score_y1,		pp->shp_map_cmn_vsd[18],\
													reg_fd_soft_score_y0,		pp->shp_map_cmn_vsd[19]);

				/*shp_balance_vsd*/
				PE_SHP_O18_QRd03(shp_mp_ctrl_05,	reg_mp_gb_en,	pp->shp_balance_vsd[0],\
													reg_mp_gb_mode, pp->shp_balance_vsd[1],\
													reg_mp_gb_y1,	pp->shp_balance_vsd[2]);
				PE_SHP_O18_QRd02(shp_mp_ctrl_06,	reg_mp_gb_y2,	pp->shp_balance_vsd[3],\
													reg_mp_gb_y3,	pp->shp_balance_vsd[4]);
				PE_SHP_O18_QRd03(shp_sp_ctrl_05,	reg_sp_gb_en,	pp->shp_balance_vsd[5],\
													reg_sp_gb_mode, pp->shp_balance_vsd[6],\
													reg_sp_gb_y1,	pp->shp_balance_vsd[7]);
				PE_SHP_O18_QRd02(shp_sp_ctrl_06,	reg_sp_gb_y2,	pp->shp_balance_vsd[8],\
													reg_sp_gb_y3,	pp->shp_balance_vsd[9]);
				PE_SHP_O18_QRd02(shp_lc_ctrl_00,	reg_lc_shp_en,	pp->shp_balance_vsd[10],\
													reg_lc_gb_en,	pp->shp_balance_vsd[11]);
				PE_SHP_O18_QRd02(shp_lc_ctrl_01,	reg_lc_gb_y1,	pp->shp_balance_vsd[12],\
													reg_lc_gb_y2,	pp->shp_balance_vsd[13]);
				PE_SHP_O18_QRd01(shp_lc_ctrl_02,	reg_lc_gb_y3,	pp->shp_balance_vsd[14]);
				PE_SHP_O18_QRd03(shp_lc_ctrl_00,	reg_lc_center_target,	pp->shp_balance_vsd[15],\
													reg_lc_center_gain, 	pp->shp_balance_vsd[16],\
													reg_lc_local_gain,		pp->shp_balance_vsd[17]);
				PE_SHP_O18_QRd03(shp_mp_ctrl_08,	reg_mp_lum1_y0, pp->shp_balance_vsd[18],\
													reg_mp_lum1_y1, pp->shp_balance_vsd[19],\
													reg_mp_lum1_y2, pp->shp_balance_vsd[20]);
				PE_SHP_O18_QRd01(shp_mp_ctrl_09,	reg_mp_lum2_y0, pp->shp_balance_vsd[21]);
				PE_SHP_O18_QRd02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, pp->shp_balance_vsd[22],\
													reg_mp_lum2_y2, pp->shp_balance_vsd[23]);
				PE_SHP_O18_QRd03(shp_sp_ctrl_08,	reg_sp_lum1_y0, pp->shp_balance_vsd[24],\
													reg_sp_lum1_y1, pp->shp_balance_vsd[25],\
													reg_sp_lum1_y2, pp->shp_balance_vsd[26]);
				PE_SHP_O18_QRd01(shp_sp_ctrl_09,	reg_sp_lum2_y0, pp->shp_balance_vsd[27]);
				PE_SHP_O18_QRd02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, pp->shp_balance_vsd[28],\
													reg_sp_lum2_y2, pp->shp_balance_vsd[29]);
				/*shp_ti_cmn_vsd*/
				PE_SHP_O18_QRd04(shp_pti_ctrl_00,	reg_ptiv_enable,		pp->shp_ti_cmn_vsd[0],\
													reg_ptiv_ti_mode,		pp->shp_ti_cmn_vsd[1],\
													reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_vsd[2],\
													reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_vsd[3]);
				PE_SHP_O18_QRd04(shp_pti_ctrl_01,	reg_ptih_enable,		pp->shp_ti_cmn_vsd[4],\
													reg_ptih_ti_mode,		pp->shp_ti_cmn_vsd[5],\
													reg_ptih_mm_tap_size,	pp->shp_ti_cmn_vsd[6],\
													reg_ptih_avg_tap_size,	pp->shp_ti_cmn_vsd[7]);
				PE_SHP_O18_QRd04(shp_sti_ctrl_00,	reg_sti_enable,			pp->shp_ti_cmn_vsd[8],\
													reg_sti_ti_mode,		pp->shp_ti_cmn_vsd[9],\
													reg_sti_mm_tap_size,	pp->shp_ti_cmn_vsd[10],\
													reg_sti_avg_tap_size,	pp->shp_ti_cmn_vsd[11]);
				/*shp_simple_snr_vsd*/
				PE_SHP_O18_QRd03(shp_snr_ctrl_00,	reg_snr_blur_en,		pp->shp_simple_snr_vsd[0],\
													reg_snr_blur_sel,		pp->shp_simple_snr_vsd[1],\
													reg_snr_bilateral_th,	pp->shp_simple_snr_vsd[2]);
				/*shp_cti_cmn_vsd*/
				PE_DNR0_O18_QRd04(reg_cti_ctrl_0,	cti_en,	pp->shp_cti_cmn_vsd[0],\
													cti_tap,			pp->shp_cti_cmn_vsd[2],\
													cti_pre_flt_mode,	pp->shp_cti_cmn_vsd[3],\
													cti_clipping_mode,	pp->shp_cti_cmn_vsd[4]);
				PE_DNR0_O18_QRd01(reg_cti_ctrl_2,	reg_ycm_en,	pp->shp_cti_cmn_vsd[1]);
				PE_SHP_O18_QRd02(shp_cti_ctrl_00,	reg_cti_en,			pp->shp_cti_cmn_vsd[5],\
													reg_cti_filter_tap_size,	pp->shp_cti_cmn_vsd[7]);
				PE_SHP_O18_QRd01(shp_cti_ctrl_02,	reg_cti_ycm_en,		pp->shp_cti_cmn_vsd[6]);

				/*shp_motion_vsd*/
				PE_SHP_O18_QRd01(shp_motion_prot_ctrl_00,	reg_motion_prot_adaptive_en,pp->shp_motion_vsd[0]);
				PE_SHP_O18_QRd02(shp_motion_prot_ctrl_01,	reg_motion_prot_lut_a_y0,	pp->shp_motion_vsd[1],\
															reg_motion_prot_lut_a_y1,	pp->shp_motion_vsd[2]);
				PE_SHP_O18_QRd02(shp_motion_prot_ctrl_02,	reg_motion_prot_lut_a_y2,	pp->shp_motion_vsd[3],\
															reg_motion_prot_lut_a_y3,	pp->shp_motion_vsd[4]);
				PE_SHP_O18_QRd02(shp_motion_prot_ctrl_03,	reg_motion_prot_lut_t_y0,	pp->shp_motion_vsd[5],\
															reg_motion_prot_lut_t_y1,	pp->shp_motion_vsd[6]);
				PE_SHP_O18_QRd02(shp_motion_prot_ctrl_04,	reg_motion_prot_lut_t_y2,	pp->shp_motion_vsd[7],\
															reg_motion_prot_lut_t_y3,	pp->shp_motion_vsd[8]);
				/*shp_chroma_vsd*/
				PE_SHP_O18_QRd03(shp_chroma_ctrl_00,	reg_color_region_en,	pp->shp_chroma_vsd[0],\
														reg_chr_protection_en,	pp->shp_chroma_vsd[1],\
														reg_chr_compensation_en,pp->shp_chroma_vsd[2]);
				PE_SHP_O18_QRd02(shp_chroma_ctrl_0d,	reg_chr_gain_r0_gain,	pp->shp_chroma_vsd[3],\
														reg_chr_gain_r1_gain,	pp->shp_chroma_vsd[4]);
 			}
			pd = pp->shp_cmn_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_cmn_vsd\n"
			"shp_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd    [20]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22]);

			pd = pp->shp_djg_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_djg_vsd\n"
			"shp_djg_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_map_cmn_vsd\n"
			"shp_map_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);

			pd = pp->shp_balance_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_balance_vsd\n"
			"shp_balance_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ti_cmn_vsd\n"
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);

			pd = pp->shp_simple_snr_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_simple_snr_vsd\n"
			"shp_simple_snr_vsd    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);

			pd = pp->shp_cti_cmn_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_cti_cmn_vsd\n"
			"shp_cti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_motion_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_motion_vsd\n"
			"shp_motion_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8]);

			pd = pp->shp_chroma_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_chroma_vsd\n"
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for O18
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_EE4_T *pp = (LX_PE_SHP_EE4_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ee_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ee_vsd\n"
			"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_RES_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b,		GET_BITS(pp->shp_ee_vsd[0],0,7),\
														reg_mp_coring_gain_e_w,		GET_BITS(pp->shp_ee_vsd[1],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b,		GET_BITS(pp->shp_ee_vsd[2],0,7),\
														reg_sp_coring_gain_e_w,		GET_BITS(pp->shp_ee_vsd[3],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[4],0,7),\
														reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[5],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b,		GET_BITS(pp->shp_ee_vsd[6],0,7),\
														reg_lc_coring_gain_e_w,		GET_BITS(pp->shp_ee_vsd[7],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[8],0,7),\
														reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[9],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[10],0,7),\
														reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[11],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_nntg_ctrl_10,reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[12],0,7),\
														reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[13],0,7));
				#else
				PE_SHP_O18_QWr02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b,		GET_BITS(pp->shp_ee_vsd[0],0,7),\
													reg_mp_coring_gain_e_w,		GET_BITS(pp->shp_ee_vsd[1],0,7));
				PE_SHP_O18_QWr02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b,		GET_BITS(pp->shp_ee_vsd[2],0,7),\
													reg_sp_coring_gain_e_w,		GET_BITS(pp->shp_ee_vsd[3],0,7));
				PE_SHP_O18_QWr02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[4],0,7),\
													reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[5],0,7));
				PE_SHP_O18_QWr02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b,		GET_BITS(pp->shp_ee_vsd[6],0,7),\
													reg_lc_coring_gain_e_w,		GET_BITS(pp->shp_ee_vsd[7],0,7));
				PE_SHP_O18_QWr02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[8],0,7),\
													reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[9],0,7));
				PE_SHP_O18_QWr02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[10],0,7),\
													reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[11],0,7));
				PE_SHP_O18_QWr02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[12],0,7),\
													reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for O18
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_EE4_T *pp = (LX_PE_SHP_EE4_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ee_vsd;

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O18_QRd02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b,	pp->shp_ee_vsd[0],\
													reg_mp_coring_gain_e_w,	pp->shp_ee_vsd[1]);
				PE_SHP_O18_QRd02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b,	pp->shp_ee_vsd[2],\
													reg_sp_coring_gain_e_w,	pp->shp_ee_vsd[3]);
				PE_SHP_O18_QRd02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,	pp->shp_ee_vsd[4],\
													reg_pti_coring_gain_e_w,	pp->shp_ee_vsd[5]);
				PE_SHP_O18_QRd02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b,	pp->shp_ee_vsd[6],\
													reg_lc_coring_gain_e_w,	pp->shp_ee_vsd[7]);
				PE_SHP_O18_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	pp->shp_ee_vsd[8],\
													reg_dctp_coring_gain_e_w,	pp->shp_ee_vsd[9]);
				PE_SHP_O18_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	pp->shp_ee_vsd[10],\
													reg_tgen_coring_gain_e_w,	pp->shp_ee_vsd[11]);
				PE_SHP_O18_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	pp->shp_ee_vsd[12],\
													reg_nntg_coring_gain_e_w,	pp->shp_ee_vsd[13]);
			}

			pd = pp->shp_ee_vsd;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ee_vsd\n"
			"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for O18
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_DE4_T *pp = (LX_PE_SHP_DE4_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_de_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_de_vsd\n"
			"shp_de_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_RES_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[0],0,7),\
														reg_mp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[1],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[2],0,7),\
														reg_sp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[3],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[4],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[5],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[6],0,7),\
														reg_lc_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[7],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[8],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[9],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[10],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[11],0,7));
				PE_SHP_HW_O18_RES_WR02(shp_nntg_ctrl_10,reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[12],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[13],0,7));
				#else
				PE_SHP_O18_QWr02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[0],0,7),\
														reg_mp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[1],0,7));
				PE_SHP_O18_QWr02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[2],0,7),\
														reg_sp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[3],0,7));
				PE_SHP_O18_QWr02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[4],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[5],0,7));
				PE_SHP_O18_QWr02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[6],0,7),\
														reg_lc_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[7],0,7));
				PE_SHP_O18_QWr02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[8],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[9],0,7));
				PE_SHP_O18_QWr02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[10],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[11],0,7));
				PE_SHP_O18_QWr02(shp_nntg_ctrl_10,reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[12],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for O18
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_DE4_T *pp = (LX_PE_SHP_DE4_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O18_QRd02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, 	pp->shp_de_vsd[0],\
													reg_mp_coring_gain_t_w, 	pp->shp_de_vsd[1]);
				PE_SHP_O18_QRd02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, 	pp->shp_de_vsd[2],\
													reg_sp_coring_gain_t_w, 	pp->shp_de_vsd[3]);
				PE_SHP_O18_QRd02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	pp->shp_de_vsd[4],\
													reg_pti_coring_gain_t_w,	pp->shp_de_vsd[5]);
				PE_SHP_O18_QRd02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, 	pp->shp_de_vsd[6],\
													reg_lc_coring_gain_t_w, 	pp->shp_de_vsd[7]);
				PE_SHP_O18_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	pp->shp_de_vsd[8],\
													reg_dctp_coring_gain_t_w,	pp->shp_de_vsd[9]);
				PE_SHP_O18_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	pp->shp_de_vsd[10],\
													reg_tgen_coring_gain_t_w,	pp->shp_de_vsd[11]);
				PE_SHP_O18_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	pp->shp_de_vsd[12],\
													reg_nntg_coring_gain_t_w,	pp->shp_de_vsd[13]);
			}
			pd = pp->shp_de_vsd;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_de_vsd\n"
			"shp_de_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}


/**
 * set sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSreReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_CMN_T *pp=(LX_PE_SHP_SR_RE4_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_main_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_main_4k\n"
			"shp_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_4k    [10]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10]);
			pd = pp->shp_ti_ui_main_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ti_ui_main_4k\n"
			"shp_ti_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				/*shp_ui_main_4k*/
				PE_SHP_HW_O18_SR_SHP_WR01(shp_esf_ctrl_01,	reg_esf_master_gain,	GET_BITS(pp->shp_ui_main_4k[0],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_4k[1],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_4k[2],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_lc_ctrl_02,	reg_lc_lap_weight,		GET_BITS(pp->shp_ui_main_4k[3],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_mp_ctrl_02,	reg_mp_lap_weight,		GET_BITS(pp->shp_ui_main_4k[4],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_sp_ctrl_02,	reg_sp_lap_weight,		GET_BITS(pp->shp_ui_main_4k[5],0,8));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_der_ctrl_06,	reg_der_a_lut_y0,		GET_BITS(pp->shp_ui_main_4k[6],0,8),\
															reg_der_a_lut_y1,		GET_BITS(pp->shp_ui_main_4k[7],0,8));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_der_ctrl_07,	reg_der_a_lut_y2,		GET_BITS(pp->shp_ui_main_4k[8],0,8),\
															reg_der_a_lut_y3,		GET_BITS(pp->shp_ui_main_4k[9],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_4k[10],0,8));
				/*shp_ti_ui_main_4k*/
				PE_SHP_HW_O18_SR_SHP_WR03(shp_sti_ctrl_00,	reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_4k[0],0,8),\
															reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_4k[1],0,8),\
															reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_4k[2],0,8));
				#else
				PE_SR_4K_SHP_O18_QWr01(shp_esf_ctrl_01,		reg_esf_master_gain,	GET_BITS(pp->shp_ui_main_4k[0],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_4k[1],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_4k[2],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_lc_ctrl_02,		reg_lc_lap_weight,		GET_BITS(pp->shp_ui_main_4k[3],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_mp_ctrl_02,		reg_mp_lap_weight,		GET_BITS(pp->shp_ui_main_4k[4],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_sp_ctrl_02,		reg_sp_lap_weight,		GET_BITS(pp->shp_ui_main_4k[5],0,8));
				PE_SR_4K_SHP_O18_QWr02(shp_der_ctrl_06,		reg_der_a_lut_y0,		GET_BITS(pp->shp_ui_main_4k[6],0,8),\
															reg_der_a_lut_y1,		GET_BITS(pp->shp_ui_main_4k[7],0,8));
				PE_SR_4K_SHP_O18_QWr02(shp_der_ctrl_07,		reg_der_a_lut_y2,		GET_BITS(pp->shp_ui_main_4k[8],0,8),\
															reg_der_a_lut_y3,		GET_BITS(pp->shp_ui_main_4k[9],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_4k[10],0,8));
				/*shp_ti_ui_main_4k*/
				PE_SR_4K_SHP_O18_QWr03(shp_sti_ctrl_00,		reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_4k[0],0,8),\
															reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_4k[1],0,8),\
															reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_4k[2],0,8));
				
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSreReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_CMN_T *pp=(LX_PE_SHP_SR_RE4_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_4K_SHP_O18_QRd01(shp_esf_ctrl_01,	reg_esf_master_gain,	pp->shp_ui_main_4k[0]);
				PE_SR_4K_SHP_O18_QRd01(shp_dctp_ctrl_1d,	reg_dctp_gain,	pp->shp_ui_main_4k[1]);
				PE_SR_4K_SHP_O18_QRd01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	pp->shp_ui_main_4k[2]);
				PE_SR_4K_SHP_O18_QRd01(shp_lc_ctrl_02,	reg_lc_lap_weight,	pp->shp_ui_main_4k[3]);
				PE_SR_4K_SHP_O18_QRd01(shp_mp_ctrl_02,	reg_mp_lap_weight,	pp->shp_ui_main_4k[4]);
				PE_SR_4K_SHP_O18_QRd01(shp_sp_ctrl_02,	reg_sp_lap_weight,	pp->shp_ui_main_4k[5]);
				PE_SR_4K_SHP_O18_QRd02(shp_der_ctrl_06,	reg_der_a_lut_y0,	pp->shp_ui_main_4k[6],\
																reg_der_a_lut_y1,	pp->shp_ui_main_4k[7]);
				PE_SR_4K_SHP_O18_QRd02(shp_der_ctrl_07,	reg_der_a_lut_y2,	pp->shp_ui_main_4k[8],\
																reg_der_a_lut_y3,	pp->shp_ui_main_4k[9]);
				PE_SR_4K_SHP_O18_QRd01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	pp->shp_ui_main_4k[10]);
				PE_SR_4K_SHP_O18_QRd03(shp_sti_ctrl_00,	reg_sti_master_gain,	pp->shp_ti_ui_main_4k[0],\
												reg_sti_edge_gain,	pp->shp_ti_ui_main_4k[1],\
												reg_sti_texture_gain,	pp->shp_ti_ui_main_4k[2]);
				pd = pp->shp_ui_main_4k;
				PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_main_4k\n"
				"shp_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_4k    [10]0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10]);
				pd = pp->shp_ti_ui_main_4k;
				PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ti_ui_main_4k\n"
				"shp_ti_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2]);
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSreReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_HOR_T *pp=(LX_PE_SHP_SR_RE4_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_h_main_4k\n"
			"shp_ui_h_main_4k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_SHP_WR01(shp_der_ctrl_00,	reg_derh_csft_gain, 		GET_BITS(pp->shp_ui_h_main_4k[0],0,6));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_4k[1],0,6),\
															reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_4k[2],0,6));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_4k[3],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_4k[4],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_pti_ctrl_01,	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_4k[5],0,8));
				#else
				PE_SR_4K_SHP_O18_QWr01(shp_der_ctrl_00,	reg_derh_csft_gain, 			GET_BITS(pp->shp_ui_h_main_4k[0],0,6));
				PE_SR_4K_SHP_O18_QWr02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main_4k[1],0,6),\
														reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main_4k[2],0,6));
				PE_SR_4K_SHP_O18_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_4k[3],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_sp_ctrl_01,	reg_sp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_4k[4],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_pti_ctrl_01,	reg_ptih_master_gain,			GET_BITS(pp->shp_ui_h_main_4k[5],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSreReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_HOR_T *pp=(LX_PE_SHP_SR_RE4_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			PE_SR_4K_SHP_O18_QRd01(shp_der_ctrl_00, reg_derh_csft_gain, 			pp->shp_ui_h_main_4k[0]);
			PE_SR_4K_SHP_O18_QRd02(shp_der_ctrl_02, reg_derh_edge_filter_gain_w,	pp->shp_ui_h_main_4k[1],\
													reg_derh_edge_filter_gain_b,	pp->shp_ui_h_main_4k[2]);
			PE_SR_4K_SHP_O18_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,				pp->shp_ui_h_main_4k[3]);
			PE_SR_4K_SHP_O18_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,				pp->shp_ui_h_main_4k[4]);
			PE_SR_4K_SHP_O18_QRd01(shp_pti_ctrl_01, reg_ptih_master_gain,			pp->shp_ui_h_main_4k[5]);

			pd = pp->shp_ui_h_main_4k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_h_main_4k\n"
			"shp_ui_h_main_4k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSreReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT8 *pd;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			LX_PE_SHP_SR_RE4_VER_T *pp=(LX_PE_SHP_SR_RE4_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_v_main_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_v_main_4k\n"
			"shp_ui_v_main_4k    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_4k[0],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_4k[1],0,8));
				#else
				PE_SR_4K_SHP_O18_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_4k[0],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_4k[1],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSreReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT8 *pd;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			LX_PE_SHP_SR_RE4_VER_T *pp=(LX_PE_SHP_SR_RE4_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_4K_SHP_O18_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		pp->shp_ui_v_main_4k[0]);
				PE_SR_4K_SHP_O18_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	pp->shp_ui_v_main_4k[1]);
			}
			pd = pp->shp_ui_v_main_4k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_v_main_4k\n"
			"shp_ui_v_main_4k	 [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSreReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{ 
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_MISC_T *pp=(LX_PE_SHP_SR_RE4_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_cmn_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_cmn_4k\n"
			"shp_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [20]0x%02X,",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);
			pd = pp->shp_map_cmn_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_map_cmn_4k\n"
			"shp_map_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_balance_4k\n"
			"shp_balance_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ti_cmn_4k\n"
			"shp_ti_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_4k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_simple_snr_4k\n"
			"shp_simple_snr_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_SHP_WR02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_4k[0],0,1),\
															reg_derh_bflt_tap_size,		GET_BITS(pp->shp_cmn_4k[1],0,3));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,				GET_BITS(pp->shp_cmn_4k[2],0,1));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,				GET_BITS(pp->shp_cmn_4k[3],0,1));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_mp_ctrl_01,	reg_mp_im_os_gain,			GET_BITS(pp->shp_cmn_4k[4],0,7),\
															reg_mp_im_us_gain,			GET_BITS(pp->shp_cmn_4k[5],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_sp_ctrl_01,	reg_sp_im_os_gain,			GET_BITS(pp->shp_cmn_4k[6],0,7),\
															reg_sp_im_us_gain,			GET_BITS(pp->shp_cmn_4k[7],0,7));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_esf_ctrl_00,	reg_esf_en,					GET_BITS(pp->shp_cmn_4k[8],0,1));
				PE_SHP_HW_O18_SR_SHP_WR03(shp_esf_ctrl_01,	reg_esf_min_ratio,			GET_BITS(pp->shp_cmn_4k[9],0,8),\
															reg_esf_base,				GET_BITS(pp->shp_cmn_4k[10],0,8),\
															reg_esf_max_clip,			GET_BITS(pp->shp_cmn_4k[11],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_dctp_ctrl_00,	reg_dctp_en,				GET_BITS(pp->shp_cmn_4k[12],0,1));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,			GET_BITS(pp->shp_cmn_4k[13],0,1),\
															reg_dctp_coring_mode,		GET_BITS(pp->shp_cmn_4k[14],0,2));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_on_off,			GET_BITS(pp->shp_cmn_4k[15],0,1));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,			GET_BITS(pp->shp_cmn_4k[16],0,1),\
															reg_tgen_coring_mode,		GET_BITS(pp->shp_cmn_4k[17],0,2));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_nntg_ctrl_00,	reg_nntg_en,				GET_BITS(pp->shp_cmn_4k[18],0,1));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,			GET_BITS(pp->shp_cmn_4k[19],0,1),\
															reg_nntg_coring_mode,		GET_BITS(pp->shp_cmn_4k[20],0,2));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_fd_ctrl_09,	reg_fd_mnr_gain_e_en,		GET_BITS(pp->shp_map_cmn_4k[0],0,1),\
															reg_fd_mnr_gain_t_en,		GET_BITS(pp->shp_map_cmn_4k[1],0,1));
				PE_SHP_HW_O18_SR_SHP_WR04(shp_fd_ctrl_0b,	reg_fd_mnr_gain_x0,			GET_BITS(pp->shp_map_cmn_4k[2],0,8),\
															reg_fd_mnr_gain_x1,			GET_BITS(pp->shp_map_cmn_4k[3],0,8),\
															reg_fd_mnr_gain_y0,			GET_BITS(pp->shp_map_cmn_4k[4],0,8),\
															reg_fd_mnr_gain_y1,			GET_BITS(pp->shp_map_cmn_4k[5],0,8));
				PE_SHP_HW_O18_SR_SHP_WR04(shp_fd_ctrl_07,	reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_4k[6],0,8),\
															reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_4k[7],0,8),\
															reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_4k[8],0,8),\
															reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_4k[9],0,8));
				PE_SHP_HW_O18_SR_SHP_WR04(shp_fd_ctrl_08,	reg_fd_detail_minmax_x0,	GET_BITS(pp->shp_map_cmn_4k[10],0,8),\
															reg_fd_detail_minmax_y0,	GET_BITS(pp->shp_map_cmn_4k[11],0,8),\
															reg_fd_detail_minmax_x1,	GET_BITS(pp->shp_map_cmn_4k[12],0,8),\
															reg_fd_detail_minmax_y1,	GET_BITS(pp->shp_map_cmn_4k[13],0,8));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_fd_ctrl_0f,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_4k[14],0,1),\
															reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_4k[15],0,1));
				PE_SHP_HW_O18_SR_SHP_WR04(shp_fd_ctrl_12,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_4k[16],0,6),\
															reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_4k[17],0,6),\
															reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_4k[18],0,6),\
															reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_4k[19],0,6));
				PE_SHP_HW_O18_SR_SHP_WR03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_4k[0],0,1),\
															reg_mp_gb_mode,	GET_BITS(pp->shp_balance_4k[1],0,1),\
															reg_mp_gb_y1,	GET_BITS(pp->shp_balance_4k[2],0,8));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_4k[3],0,8),\
															reg_mp_gb_y3,	GET_BITS(pp->shp_balance_4k[4],0,8));
				PE_SHP_HW_O18_SR_SHP_WR03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_4k[5],0,1),\
															reg_sp_gb_mode,	GET_BITS(pp->shp_balance_4k[6],0,1),\
															reg_sp_gb_y1,	GET_BITS(pp->shp_balance_4k[7],0,8));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_4k[8],0,8),\
															reg_sp_gb_y3,	GET_BITS(pp->shp_balance_4k[9],0,8));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_4k[10],0,1),\
															reg_lc_gb_en,	GET_BITS(pp->shp_balance_4k[11],0,1));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_4k[12],0,8),\
															reg_lc_gb_y2,	GET_BITS(pp->shp_balance_4k[13],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_4k[14],0,8));
				PE_SHP_HW_O18_SR_SHP_WR03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_4k[15],0,8),\
															reg_lc_center_gain,	GET_BITS(pp->shp_balance_4k[16],0,8),\
															reg_lc_local_gain,	GET_BITS(pp->shp_balance_4k[17],0,8));
				PE_SHP_HW_O18_SR_SHP_WR03(shp_mp_ctrl_08,	reg_mp_lum1_y0,	GET_BITS(pp->shp_balance_4k[18],0,8),\
															reg_mp_lum1_y1,	GET_BITS(pp->shp_balance_4k[19],0,8),\
															reg_mp_lum1_y2,	GET_BITS(pp->shp_balance_4k[20],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_mp_ctrl_09,	reg_mp_lum2_y0,	GET_BITS(pp->shp_balance_4k[21],0,8));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_mp_ctrl_0a,	reg_mp_lum2_y1,	GET_BITS(pp->shp_balance_4k[22],0,8),\
															reg_mp_lum2_y2,	GET_BITS(pp->shp_balance_4k[23],0,8));
				PE_SHP_HW_O18_SR_SHP_WR03(shp_sp_ctrl_08,	reg_sp_lum1_y0,	GET_BITS(pp->shp_balance_4k[24],0,8),\
															reg_sp_lum1_y1,	GET_BITS(pp->shp_balance_4k[25],0,8),\
															reg_sp_lum1_y2,	GET_BITS(pp->shp_balance_4k[26],0,8));
				PE_SHP_HW_O18_SR_SHP_WR01(shp_sp_ctrl_09,	reg_sp_lum2_y0,	GET_BITS(pp->shp_balance_4k[27],0,8));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_sp_ctrl_0a,	reg_sp_lum2_y1,	GET_BITS(pp->shp_balance_4k[28],0,8),\
															reg_sp_lum2_y2,	GET_BITS(pp->shp_balance_4k[29],0,8));
				PE_SHP_HW_O18_SR_SHP_WR04(shp_pti_ctrl_00,	reg_ptiv_enable,	GET_BITS(pp->shp_ti_cmn_4k[0],0,1),\
															reg_ptiv_ti_mode,	GET_BITS(pp->shp_ti_cmn_4k[1],0,1),\
															reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[2],0,2),\
															reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[3],0,2));
				PE_SHP_HW_O18_SR_SHP_WR04(shp_pti_ctrl_01,	reg_ptih_enable,	GET_BITS(pp->shp_ti_cmn_4k[4],0,1),\
															reg_ptih_ti_mode,	GET_BITS(pp->shp_ti_cmn_4k[5],0,1),\
															reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[6],0,2),\
															reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[7],0,2));
				PE_SHP_HW_O18_SR_SHP_WR04(shp_sti_ctrl_00,	reg_sti_enable,	GET_BITS(pp->shp_ti_cmn_4k[8],0,1),\
															reg_sti_ti_mode,	GET_BITS(pp->shp_ti_cmn_4k[9],0,1),\
															reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[10],0,2),\
															reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[11],0,2));
				PE_SHP_HW_O18_SR_SHP_WR03(shp_snr_ctrl_00,	reg_snr_blur_en,	GET_BITS(pp->shp_simple_snr_4k[0],0,1),\
															reg_snr_blur_sel,	GET_BITS(pp->shp_simple_snr_4k[1],0,2),\
															reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_4k[2],0,8));
				#else
				PE_SR_4K_SHP_O18_QWr02(shp_der_ctrl_01,		reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_4k[0],0,1),\
															reg_derh_bflt_tap_size,		GET_BITS(pp->shp_cmn_4k[1],0,3));
				PE_SR_4K_SHP_O18_QWr01(shp_mp_ctrl_00,		reg_mp_shp_en,				GET_BITS(pp->shp_cmn_4k[2],0,1));
				PE_SR_4K_SHP_O18_QWr01(shp_sp_ctrl_00,		reg_sp_shp_en,				GET_BITS(pp->shp_cmn_4k[3],0,1));
				PE_SR_4K_SHP_O18_QWr02(shp_mp_ctrl_01,		reg_mp_im_os_gain,			GET_BITS(pp->shp_cmn_4k[4],0,7),\
															reg_mp_im_us_gain,			GET_BITS(pp->shp_cmn_4k[5],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_sp_ctrl_01,		reg_sp_im_os_gain,			GET_BITS(pp->shp_cmn_4k[6],0,7),\
															reg_sp_im_us_gain,			GET_BITS(pp->shp_cmn_4k[7],0,7));
				PE_SR_4K_SHP_O18_QWr01(shp_esf_ctrl_00,		reg_esf_en,					GET_BITS(pp->shp_cmn_4k[8],0,1));
				PE_SR_4K_SHP_O18_QWr03(shp_esf_ctrl_01,		reg_esf_min_ratio,			GET_BITS(pp->shp_cmn_4k[9],0,8),\
															reg_esf_base,				GET_BITS(pp->shp_cmn_4k[10],0,8),\
															reg_esf_max_clip,			GET_BITS(pp->shp_cmn_4k[11],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_dctp_ctrl_00,	reg_dctp_en,				GET_BITS(pp->shp_cmn_4k[12],0,1));
				PE_SR_4K_SHP_O18_QWr02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,			GET_BITS(pp->shp_cmn_4k[13],0,1),\
															reg_dctp_coring_mode,		GET_BITS(pp->shp_cmn_4k[14],0,2));
				PE_SR_4K_SHP_O18_QWr01(shp_tgen_ctrl_00,	reg_tgen_on_off,			GET_BITS(pp->shp_cmn_4k[15],0,1));
				PE_SR_4K_SHP_O18_QWr02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,			GET_BITS(pp->shp_cmn_4k[16],0,1),\
															reg_tgen_coring_mode,		GET_BITS(pp->shp_cmn_4k[17],0,2));
				PE_SR_4K_SHP_O18_QWr01(shp_nntg_ctrl_00,	reg_nntg_en,				GET_BITS(pp->shp_cmn_4k[18],0,1));
				PE_SR_4K_SHP_O18_QWr02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,			GET_BITS(pp->shp_cmn_4k[19],0,1),\
															reg_nntg_coring_mode,		GET_BITS(pp->shp_cmn_4k[20],0,2));
				PE_SR_4K_SHP_O18_QWr02(shp_fd_ctrl_09,		reg_fd_mnr_gain_e_en,		GET_BITS(pp->shp_map_cmn_4k[0],0,1),\
															reg_fd_mnr_gain_t_en,		GET_BITS(pp->shp_map_cmn_4k[1],0,1));
				PE_SR_4K_SHP_O18_QWr04(shp_fd_ctrl_0b,		reg_fd_mnr_gain_x0,			GET_BITS(pp->shp_map_cmn_4k[2],0,8),\
															reg_fd_mnr_gain_x1,			GET_BITS(pp->shp_map_cmn_4k[3],0,8),\
															reg_fd_mnr_gain_y0,			GET_BITS(pp->shp_map_cmn_4k[4],0,8),\
															reg_fd_mnr_gain_y1,			GET_BITS(pp->shp_map_cmn_4k[5],0,8));
				PE_SR_4K_SHP_O18_QWr04(shp_fd_ctrl_07,		reg_fd_edge_minmax_x0,		GET_BITS(pp->shp_map_cmn_4k[6],0,8),\
															reg_fd_edge_minmax_y0,		GET_BITS(pp->shp_map_cmn_4k[7],0,8),\
															reg_fd_edge_minmax_x1,		GET_BITS(pp->shp_map_cmn_4k[8],0,8),\
															reg_fd_edge_minmax_y1,		GET_BITS(pp->shp_map_cmn_4k[9],0,8));
				PE_SR_4K_SHP_O18_QWr04(shp_fd_ctrl_08,		reg_fd_detail_minmax_x0,	GET_BITS(pp->shp_map_cmn_4k[10],0,8),\
															reg_fd_detail_minmax_y0,	GET_BITS(pp->shp_map_cmn_4k[11],0,8),\
															reg_fd_detail_minmax_x1,	GET_BITS(pp->shp_map_cmn_4k[12],0,8),\
															reg_fd_detail_minmax_y1,	GET_BITS(pp->shp_map_cmn_4k[13],0,8));
				PE_SR_4K_SHP_O18_QWr02(shp_fd_ctrl_0f,		reg_fd_soft_gain_t_en,		GET_BITS(pp->shp_map_cmn_4k[14],0,1),\
															reg_fd_soft_gain_e_en,		GET_BITS(pp->shp_map_cmn_4k[15],0,1));
				PE_SR_4K_SHP_O18_QWr04(shp_fd_ctrl_12,		reg_fd_soft_score_y3,		GET_BITS(pp->shp_map_cmn_4k[16],0,6),\
															reg_fd_soft_score_y2,		GET_BITS(pp->shp_map_cmn_4k[17],0,6),\
															reg_fd_soft_score_y1,		GET_BITS(pp->shp_map_cmn_4k[18],0,6),\
															reg_fd_soft_score_y0,		GET_BITS(pp->shp_map_cmn_4k[19],0,6));
				PE_SR_4K_SHP_O18_QWr03(shp_mp_ctrl_05,		reg_mp_gb_en,	GET_BITS(pp->shp_balance_4k[0],0,1),\
															reg_mp_gb_mode,	GET_BITS(pp->shp_balance_4k[1],0,1),\
															reg_mp_gb_y1,	GET_BITS(pp->shp_balance_4k[2],0,8));
				PE_SR_4K_SHP_O18_QWr02(shp_mp_ctrl_06,		reg_mp_gb_y2,	GET_BITS(pp->shp_balance_4k[3],0,8),\
															reg_mp_gb_y3,	GET_BITS(pp->shp_balance_4k[4],0,8));
				PE_SR_4K_SHP_O18_QWr03(shp_sp_ctrl_05,		reg_sp_gb_en,	GET_BITS(pp->shp_balance_4k[5],0,1),\
															reg_sp_gb_mode,	GET_BITS(pp->shp_balance_4k[6],0,1),\
															reg_sp_gb_y1,	GET_BITS(pp->shp_balance_4k[7],0,8));
				PE_SR_4K_SHP_O18_QWr02(shp_sp_ctrl_06,		reg_sp_gb_y2,	GET_BITS(pp->shp_balance_4k[8],0,8),\
															reg_sp_gb_y3,	GET_BITS(pp->shp_balance_4k[9],0,8));
				PE_SR_4K_SHP_O18_QWr02(shp_lc_ctrl_00,		reg_lc_shp_en,	GET_BITS(pp->shp_balance_4k[10],0,1),\
															reg_lc_gb_en,	GET_BITS(pp->shp_balance_4k[11],0,1));
				PE_SR_4K_SHP_O18_QWr02(shp_lc_ctrl_01,		reg_lc_gb_y1,	GET_BITS(pp->shp_balance_4k[12],0,8),\
															reg_lc_gb_y2,	GET_BITS(pp->shp_balance_4k[13],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_lc_ctrl_02,		reg_lc_gb_y3,	GET_BITS(pp->shp_balance_4k[14],0,8));
				PE_SR_4K_SHP_O18_QWr03(shp_lc_ctrl_00,		reg_lc_center_target,	GET_BITS(pp->shp_balance_4k[15],0,8),\
															reg_lc_center_gain,		GET_BITS(pp->shp_balance_4k[16],0,8),\
															reg_lc_local_gain,		GET_BITS(pp->shp_balance_4k[17],0,8));
				PE_SR_4K_SHP_O18_QWr03(shp_mp_ctrl_08,		reg_mp_lum1_y0,	GET_BITS(pp->shp_balance_4k[18],0,8),\
															reg_mp_lum1_y1,	GET_BITS(pp->shp_balance_4k[19],0,8),\
															reg_mp_lum1_y2,	GET_BITS(pp->shp_balance_4k[20],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_mp_ctrl_09,		reg_mp_lum2_y0,	GET_BITS(pp->shp_balance_4k[21],0,8));
				PE_SR_4K_SHP_O18_QWr02(shp_mp_ctrl_0a,		reg_mp_lum2_y1,	GET_BITS(pp->shp_balance_4k[22],0,8),\
															reg_mp_lum2_y2,	GET_BITS(pp->shp_balance_4k[23],0,8));
				PE_SR_4K_SHP_O18_QWr03(shp_sp_ctrl_08,		reg_sp_lum1_y0,	GET_BITS(pp->shp_balance_4k[24],0,8),\
															reg_sp_lum1_y1,	GET_BITS(pp->shp_balance_4k[25],0,8),\
															reg_sp_lum1_y2,	GET_BITS(pp->shp_balance_4k[26],0,8));
				PE_SR_4K_SHP_O18_QWr01(shp_sp_ctrl_09,		reg_sp_lum2_y0,	GET_BITS(pp->shp_balance_4k[27],0,8));
				PE_SR_4K_SHP_O18_QWr02(shp_sp_ctrl_0a,		reg_sp_lum2_y1,	GET_BITS(pp->shp_balance_4k[28],0,8),\
															reg_sp_lum2_y2,	GET_BITS(pp->shp_balance_4k[29],0,8));
				PE_SR_4K_SHP_O18_QWr04(shp_pti_ctrl_00,		reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_4k[0],0,1),\
															reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_4k[1],0,1),\
															reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[2],0,2),\
															reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[3],0,2));
				PE_SR_4K_SHP_O18_QWr04(shp_pti_ctrl_01,		reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_4k[4],0,1),\
															reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_4k[5],0,1),\
															reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[6],0,2),\
															reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[7],0,2));
				PE_SR_4K_SHP_O18_QWr04(shp_sti_ctrl_00,		reg_sti_enable,			GET_BITS(pp->shp_ti_cmn_4k[8],0,1),\
															reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_4k[9],0,1),\
															reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[10],0,2),\
															reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[11],0,2));
				PE_SR_4K_SHP_O18_QWr03(shp_snr_ctrl_00,		reg_snr_blur_en,		GET_BITS(pp->shp_simple_snr_4k[0],0,1),\
															reg_snr_blur_sel,		GET_BITS(pp->shp_simple_snr_4k[1],0,2),\
															reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_4k[2],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSreReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_MISC_T *pp=(LX_PE_SHP_SR_RE4_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_4K_SHP_O18_QRd02(shp_der_ctrl_01,		reg_derh_edge_y_filter_en,	pp->shp_cmn_4k[0],\
															reg_derh_bflt_tap_size,		pp->shp_cmn_4k[1]);
				PE_SR_4K_SHP_O18_QRd01(shp_mp_ctrl_00,		reg_mp_shp_en,				pp->shp_cmn_4k[2]);
				PE_SR_4K_SHP_O18_QRd01(shp_sp_ctrl_00,		reg_sp_shp_en,				pp->shp_cmn_4k[3]);
				PE_SR_4K_SHP_O18_QRd02(shp_mp_ctrl_01,		reg_mp_im_os_gain,			pp->shp_cmn_4k[4],\
															reg_mp_im_us_gain,			pp->shp_cmn_4k[5]);
				PE_SR_4K_SHP_O18_QRd02(shp_sp_ctrl_01,		reg_sp_im_os_gain,			pp->shp_cmn_4k[6],\
															reg_sp_im_us_gain,			pp->shp_cmn_4k[7]);
				PE_SR_4K_SHP_O18_QRd01(shp_esf_ctrl_00,		reg_esf_en,					pp->shp_cmn_4k[8]);
				PE_SR_4K_SHP_O18_QRd03(shp_esf_ctrl_01,		reg_esf_min_ratio,			pp->shp_cmn_4k[9],\
															reg_esf_base,				pp->shp_cmn_4k[10],\
															reg_esf_max_clip,			pp->shp_cmn_4k[11]);
				PE_SR_4K_SHP_O18_QRd01(shp_dctp_ctrl_00,	reg_dctp_en,				pp->shp_cmn_4k[12]);
				PE_SR_4K_SHP_O18_QRd02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,			pp->shp_cmn_4k[13],\
															reg_dctp_coring_mode,		pp->shp_cmn_4k[14]);
				PE_SR_4K_SHP_O18_QRd01(shp_tgen_ctrl_00,	reg_tgen_on_off,			pp->shp_cmn_4k[15]);
				PE_SR_4K_SHP_O18_QRd02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,			pp->shp_cmn_4k[16],\
															reg_tgen_coring_mode,		pp->shp_cmn_4k[17]);
				PE_SR_4K_SHP_O18_QRd01(shp_nntg_ctrl_00,	reg_nntg_en,				pp->shp_cmn_4k[18]);
				PE_SR_4K_SHP_O18_QRd02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,			pp->shp_cmn_4k[19],\
															reg_nntg_coring_mode,		pp->shp_cmn_4k[20]);
				PE_SR_4K_SHP_O18_QRd02(shp_fd_ctrl_09,		reg_fd_mnr_gain_e_en,		pp->shp_map_cmn_4k[0],\
															reg_fd_mnr_gain_t_en,		pp->shp_map_cmn_4k[1]);
				PE_SR_4K_SHP_O18_QRd04(shp_fd_ctrl_0b,		reg_fd_mnr_gain_x0,			pp->shp_map_cmn_4k[2],\
															reg_fd_mnr_gain_x1,			pp->shp_map_cmn_4k[3],\
															reg_fd_mnr_gain_y0,			pp->shp_map_cmn_4k[4],\
															reg_fd_mnr_gain_y1,			pp->shp_map_cmn_4k[5]);
				PE_SR_4K_SHP_O18_QRd04(shp_fd_ctrl_07,		reg_fd_edge_minmax_x0,		pp->shp_map_cmn_4k[6],\
															reg_fd_edge_minmax_y0,		pp->shp_map_cmn_4k[7],\
															reg_fd_edge_minmax_x1,		pp->shp_map_cmn_4k[8],\
															reg_fd_edge_minmax_y1,		pp->shp_map_cmn_4k[9]);
				PE_SR_4K_SHP_O18_QRd04(shp_fd_ctrl_08,		reg_fd_detail_minmax_x0,	pp->shp_map_cmn_4k[10],\
															reg_fd_detail_minmax_y0,	pp->shp_map_cmn_4k[11],\
															reg_fd_detail_minmax_x1,	pp->shp_map_cmn_4k[12],\
															reg_fd_detail_minmax_y1,	pp->shp_map_cmn_4k[13]);
				PE_SR_4K_SHP_O18_QRd02(shp_fd_ctrl_0f,		reg_fd_soft_gain_t_en,		pp->shp_map_cmn_4k[14],\
															reg_fd_soft_gain_e_en,		pp->shp_map_cmn_4k[15]);
				PE_SR_4K_SHP_O18_QRd04(shp_fd_ctrl_12,		reg_fd_soft_score_y3,		pp->shp_map_cmn_4k[16],\
															reg_fd_soft_score_y2,		pp->shp_map_cmn_4k[17],\
															reg_fd_soft_score_y1,		pp->shp_map_cmn_4k[18],\
															reg_fd_soft_score_y0,		pp->shp_map_cmn_4k[19]);
				PE_SR_4K_SHP_O18_QRd03(shp_mp_ctrl_05,		reg_mp_gb_en,	pp->shp_balance_4k[0],\
															reg_mp_gb_mode,	pp->shp_balance_4k[1],\
															reg_mp_gb_y1,	pp->shp_balance_4k[2]);
				PE_SR_4K_SHP_O18_QRd02(shp_mp_ctrl_06,		reg_mp_gb_y2,	pp->shp_balance_4k[3],\
															reg_mp_gb_y3,	pp->shp_balance_4k[4]);
				PE_SR_4K_SHP_O18_QRd03(shp_sp_ctrl_05,		reg_sp_gb_en,	pp->shp_balance_4k[5],\
															reg_sp_gb_mode,	pp->shp_balance_4k[6],\
															reg_sp_gb_y1,	pp->shp_balance_4k[7]);
				PE_SR_4K_SHP_O18_QRd02(shp_sp_ctrl_06,		reg_sp_gb_y2,	pp->shp_balance_4k[8],\
															reg_sp_gb_y3,	pp->shp_balance_4k[9]);
				PE_SR_4K_SHP_O18_QRd02(shp_lc_ctrl_00,		reg_lc_shp_en,	pp->shp_balance_4k[10],\
															reg_lc_gb_en,	pp->shp_balance_4k[11]);
				PE_SR_4K_SHP_O18_QRd02(shp_lc_ctrl_01,		reg_lc_gb_y1,	pp->shp_balance_4k[12],\
															reg_lc_gb_y2,	pp->shp_balance_4k[13]);
				PE_SR_4K_SHP_O18_QRd01(shp_lc_ctrl_02,		reg_lc_gb_y3,	pp->shp_balance_4k[14]);
				PE_SR_4K_SHP_O18_QRd03(shp_lc_ctrl_00,		reg_lc_center_target,	pp->shp_balance_4k[15],\
															reg_lc_center_gain,		pp->shp_balance_4k[16],\
															reg_lc_local_gain,		pp->shp_balance_4k[17]);
				PE_SR_4K_SHP_O18_QRd03(shp_mp_ctrl_08,		reg_mp_lum1_y0,	pp->shp_balance_4k[18],\
															reg_mp_lum1_y1,	pp->shp_balance_4k[19],\
															reg_mp_lum1_y2,	pp->shp_balance_4k[20]);
				PE_SR_4K_SHP_O18_QRd01(shp_mp_ctrl_09,		reg_mp_lum2_y0,	pp->shp_balance_4k[21]);
				PE_SR_4K_SHP_O18_QRd02(shp_mp_ctrl_0a,		reg_mp_lum2_y1,	pp->shp_balance_4k[22],\
															reg_mp_lum2_y2,	pp->shp_balance_4k[23]);
				PE_SR_4K_SHP_O18_QRd03(shp_sp_ctrl_08,		reg_sp_lum1_y0,	pp->shp_balance_4k[24],\
															reg_sp_lum1_y1,	pp->shp_balance_4k[25],\
															reg_sp_lum1_y2,	pp->shp_balance_4k[26]);
				PE_SR_4K_SHP_O18_QRd01(shp_sp_ctrl_09,		reg_sp_lum2_y0,	pp->shp_balance_4k[27]);
				PE_SR_4K_SHP_O18_QRd02(shp_sp_ctrl_0a,		reg_sp_lum2_y1,	pp->shp_balance_4k[28],\
															reg_sp_lum2_y2,	pp->shp_balance_4k[29]);
				PE_SR_4K_SHP_O18_QRd04(shp_pti_ctrl_00,		reg_ptiv_enable,		pp->shp_ti_cmn_4k[0],\
															reg_ptiv_ti_mode,		pp->shp_ti_cmn_4k[1],\
															reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_4k[2],\
															reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_4k[3]);
				PE_SR_4K_SHP_O18_QRd04(shp_pti_ctrl_01,		reg_ptih_enable,		pp->shp_ti_cmn_4k[4],\
															reg_ptih_ti_mode,		pp->shp_ti_cmn_4k[5],\
															reg_ptih_mm_tap_size,	pp->shp_ti_cmn_4k[6],\
															reg_ptih_avg_tap_size,	pp->shp_ti_cmn_4k[7]);
				PE_SR_4K_SHP_O18_QRd04(shp_sti_ctrl_00,		reg_sti_enable,			pp->shp_ti_cmn_4k[8],\
															reg_sti_ti_mode,		pp->shp_ti_cmn_4k[9],\
															reg_sti_mm_tap_size,	pp->shp_ti_cmn_4k[10],\
															reg_sti_avg_tap_size,	pp->shp_ti_cmn_4k[11]);
				PE_SR_4K_SHP_O18_QRd03(shp_snr_ctrl_00,		reg_snr_blur_en,		pp->shp_simple_snr_4k[0],\
															reg_snr_blur_sel,		pp->shp_simple_snr_4k[1],\
															reg_snr_bilateral_th,	pp->shp_simple_snr_4k[2]);
			}
			pd = pp->shp_cmn_4k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_cmn_4k\n"
			"shp_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [20]0x%02X,",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);
			pd = pp->shp_map_cmn_4k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_map_cmn_4k\n"
			"shp_map_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_4k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_balance_4k\n"
			"shp_balance_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_4k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ti_cmn_4k\n"
			"shp_ti_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_4k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_4k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_simple_snr_4k\n"
			"shp_simple_snr_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSreEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_EE4_T *pp = (LX_PE_SHP_SR_EE4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ee_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ee_4k\n"
			"shp_ee_4k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[0],0,7),\
															reg_mp_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[1],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[2],0,7),\
															reg_sp_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[3],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[4],0,7),\
															reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[5],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[6],0,7),\
															reg_lc_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[7],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[8],0,7),\
															reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[9],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[10],0,7),\
															reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[11],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[12],0,7),\
															reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[13],0,7));
				#else
				PE_SR_4K_SHP_O18_QWr02(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[0],0,7),\
															reg_mp_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[1],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[2],0,7),\
															reg_sp_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[3],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_pti_ctrl_03,		reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[4],0,7),\
															reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[5],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[6],0,7),\
															reg_lc_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[7],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[8],0,7),\
															reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[9],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[10],0,7),\
															reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[11],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[12],0,7),\
															reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for O18
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSreEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_EE4_T *pp = (LX_PE_SHP_SR_EE4_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_4K_SHP_O18_QRd02(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b,		pp->shp_ee_4k[0],\
															reg_mp_coring_gain_e_w,		pp->shp_ee_4k[1]);
				PE_SR_4K_SHP_O18_QRd02(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b,		pp->shp_ee_4k[2],\
															reg_sp_coring_gain_e_w,		pp->shp_ee_4k[3]);
				PE_SR_4K_SHP_O18_QRd02(shp_pti_ctrl_03,		reg_pti_coring_gain_e_b,	pp->shp_ee_4k[4],\
															reg_pti_coring_gain_e_w,	pp->shp_ee_4k[5]);
				PE_SR_4K_SHP_O18_QRd02(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b,		pp->shp_ee_4k[6],\
															reg_lc_coring_gain_e_w,		pp->shp_ee_4k[7]);
				PE_SR_4K_SHP_O18_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	pp->shp_ee_4k[8],\
															reg_dctp_coring_gain_e_w,	pp->shp_ee_4k[9]);
				PE_SR_4K_SHP_O18_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	pp->shp_ee_4k[10],\
															reg_tgen_coring_gain_e_w,	pp->shp_ee_4k[11]);
				PE_SR_4K_SHP_O18_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	pp->shp_ee_4k[12],\
															reg_nntg_coring_gain_e_w,	pp->shp_ee_4k[13]);
			}
			pd = pp->shp_ee_4k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ee_4k\n"
			"shp_ee_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSreDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_DE4_T *pp=(LX_PE_SHP_SR_DE4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_de_4k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_de_4k\n"
			"shp_de_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[0],0,7),\
															reg_mp_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[1],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[2],0,7),\
															reg_sp_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[3],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[4],0,7),\
															reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[5],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[6],0,7),\
															reg_lc_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[7],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[8],0,7),\
															reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[9],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[10],0,7),\
															reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[11],0,7));
				PE_SHP_HW_O18_SR_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[12],0,7),\
															reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[13],0,7));
				#else
				PE_SR_4K_SHP_O18_QWr02(shp_mp_ctrl_0c,		reg_mp_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[0],0,7),\
															reg_mp_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[1],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_sp_ctrl_0c,		reg_sp_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[2],0,7),\
															reg_sp_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[3],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_pti_ctrl_03,		reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[4],0,7),\
															reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[5],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_lc_ctrl_04,		reg_lc_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[6],0,7),\
															reg_lc_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[7],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[8],0,7),\
															reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[9],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[10],0,7),\
															reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[11],0,7));
				PE_SR_4K_SHP_O18_QWr02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[12],0,7),\
															reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSreDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_DE4_T *pp=(LX_PE_SHP_SR_DE4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_de_4k;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_4K_SHP_O18_QRd02(shp_mp_ctrl_0c,		reg_mp_coring_gain_t_b,		pp->shp_de_4k[0],\
															reg_mp_coring_gain_t_w,		pp->shp_de_4k[1]);
				PE_SR_4K_SHP_O18_QRd02(shp_sp_ctrl_0c,		reg_sp_coring_gain_t_b,		pp->shp_de_4k[2],\
															reg_sp_coring_gain_t_w,		pp->shp_de_4k[3]);
				PE_SR_4K_SHP_O18_QRd02(shp_pti_ctrl_03,		reg_pti_coring_gain_t_b,	pp->shp_de_4k[4],\
															reg_pti_coring_gain_t_w,	pp->shp_de_4k[5]);
				PE_SR_4K_SHP_O18_QRd02(shp_lc_ctrl_04,		reg_lc_coring_gain_t_b,		pp->shp_de_4k[6],\
															reg_lc_coring_gain_t_w,		pp->shp_de_4k[7]);
				PE_SR_4K_SHP_O18_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	pp->shp_de_4k[8],\
															reg_dctp_coring_gain_t_w,	pp->shp_de_4k[9]);
				PE_SR_4K_SHP_O18_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	pp->shp_de_4k[10],\
															reg_tgen_coring_gain_t_w,	pp->shp_de_4k[11]);
				PE_SR_4K_SHP_O18_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	pp->shp_de_4k[12],\
															reg_nntg_coring_gain_t_w,	pp->shp_de_4k[13]);

				PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_de_4k\n"
				"shp_de_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_de_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13]);
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * set sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSre2KReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_CMN_T *pp=(LX_PE_SHP_SR2K_RE_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_main_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_main_2k\n"
			"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_ti_ui_main_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ti_ui_main_2k\n"
			"shp_ti_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				/*shp_ui_main_2k*/
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_2k[0],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_2k[1],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_lc_ctrl_02,	reg_lc_lap_weight,	GET_BITS(pp->shp_ui_main_2k[2],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_mp_ctrl_02,	reg_mp_lap_weight,	GET_BITS(pp->shp_ui_main_2k[3],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_sp_ctrl_02,	reg_sp_lap_weight,	GET_BITS(pp->shp_ui_main_2k[4],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_der_ctrl_06,	reg_der_a_lut_y0,	GET_BITS(pp->shp_ui_main_2k[5],0,8),\
																reg_der_a_lut_y1,	GET_BITS(pp->shp_ui_main_2k[6],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_der_ctrl_07,	reg_der_a_lut_y2,	GET_BITS(pp->shp_ui_main_2k[7],0,8),\
																reg_der_a_lut_y3,	GET_BITS(pp->shp_ui_main_2k[8],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dir_blur_ctrl_01,	reg_dir_blur_gain,	GET_BITS(pp->shp_ui_main_2k[9],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dj_ctrl_1d,		reg_dj_soft_g0_mul,	GET_BITS(pp->shp_ui_main_2k[10],0,6));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul,	GET_BITS(pp->shp_ui_main_2k[11],0,6));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul,	GET_BITS(pp->shp_ui_main_2k[12],0,6));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_nntg_ctrl_0e,		reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_2k[13],0,8));
				/*shp_ti_ui_main_2k*/
				PE_SHP_HW_O18_SR_2K_SHP_WR03(shp_sti_ctrl_00,	reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_2k[0],0,8),\
																reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_2k[1],0,8),\
																reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_2k[2],0,8));
				#else
				PE_SR_2K_SHP_O18_QWr01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_2k[0],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_2k[1],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_lc_ctrl_02,		reg_lc_lap_weight,	GET_BITS(pp->shp_ui_main_2k[2],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_mp_ctrl_02,		reg_mp_lap_weight,	GET_BITS(pp->shp_ui_main_2k[3],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_sp_ctrl_02,		reg_sp_lap_weight,	GET_BITS(pp->shp_ui_main_2k[4],0,8));
				PE_SR_2K_SHP_O18_QWr02(shp_der_ctrl_06,		reg_der_a_lut_y0,	GET_BITS(pp->shp_ui_main_2k[5],0,8),\
															reg_der_a_lut_y1,	GET_BITS(pp->shp_ui_main_2k[6],0,8));
				PE_SR_2K_SHP_O18_QWr02(shp_der_ctrl_07,		reg_der_a_lut_y2,	GET_BITS(pp->shp_ui_main_2k[7],0,8),\
															reg_der_a_lut_y3,	GET_BITS(pp->shp_ui_main_2k[8],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_dir_blur_ctrl_01,reg_dir_blur_gain,	GET_BITS(pp->shp_ui_main_2k[9],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_dj_ctrl_1d,		reg_dj_soft_g0_mul,	GET_BITS(pp->shp_ui_main_2k[10],0,6));
				PE_SR_2K_SHP_O18_QWr01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul,	GET_BITS(pp->shp_ui_main_2k[11],0,6));
				PE_SR_2K_SHP_O18_QWr01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul,	GET_BITS(pp->shp_ui_main_2k[12],0,6));
				PE_SR_2K_SHP_O18_QWr01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_2k[13],0,8));
				/*shp_ti_ui_main_2k*/
				PE_SR_2K_SHP_O18_QWr03(shp_sti_ctrl_00,		reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_2k[0],0,8),\
															reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_2k[1],0,8),\
															reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_2k[2],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSre2KReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_CMN_T *pp=(LX_PE_SHP_SR2K_RE_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_O18_QRd01(shp_dctp_ctrl_1d,	reg_dctp_gain,			pp->shp_ui_main_2k[0]);
				PE_SR_2K_SHP_O18_QRd01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	pp->shp_ui_main_2k[1]);
				PE_SR_2K_SHP_O18_QRd01(shp_lc_ctrl_02,		reg_lc_lap_weight,	pp->shp_ui_main_2k[2]);
				PE_SR_2K_SHP_O18_QRd01(shp_mp_ctrl_02,		reg_mp_lap_weight,	pp->shp_ui_main_2k[3]);
				PE_SR_2K_SHP_O18_QRd01(shp_sp_ctrl_02,		reg_sp_lap_weight,	pp->shp_ui_main_2k[4]);
				PE_SR_2K_SHP_O18_QRd02(shp_der_ctrl_06,		reg_der_a_lut_y0,	pp->shp_ui_main_2k[5],\
															reg_der_a_lut_y1,	pp->shp_ui_main_2k[6]);
				PE_SR_2K_SHP_O18_QRd02(shp_der_ctrl_07,		reg_der_a_lut_y2,	pp->shp_ui_main_2k[7],\
															reg_der_a_lut_y3,	pp->shp_ui_main_2k[8]);
				PE_SR_2K_SHP_O18_QRd01(shp_dir_blur_ctrl_01,reg_dir_blur_gain,	pp->shp_ui_main_2k[9]);
				PE_SR_2K_SHP_O18_QRd01(shp_dj_ctrl_1d,		reg_dj_soft_g0_mul,	pp->shp_ui_main_2k[10]);
				PE_SR_2K_SHP_O18_QRd01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul,	pp->shp_ui_main_2k[11]);
				PE_SR_2K_SHP_O18_QRd01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul,	pp->shp_ui_main_2k[12]);
				PE_SR_2K_SHP_O18_QRd01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	pp->shp_ui_main_2k[13]);
				/*shp_ti_ui_main_2k*/
				PE_SR_2K_SHP_O18_QRd03(shp_sti_ctrl_00,		reg_sti_master_gain,	pp->shp_ti_ui_main_2k[0],\
															reg_sti_edge_gain,		pp->shp_ti_ui_main_2k[1],\
															reg_sti_texture_gain,	pp->shp_ti_ui_main_2k[2]);
				pd = pp->shp_ui_main_2k;
				PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_main_2k\n"
				"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13]);
				pd = pp->shp_ti_ui_main_2k;
				PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ti_ui_main_2k\n"
				"shp_ti_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2]);
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSre2KReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_HOR_T *pp=(LX_PE_SHP_SR2K_RE_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_h_main_2k\n"
			"shp_ui_h_main_2k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_der_ctrl_00,	reg_derh_csft_gain,	GET_BITS(pp->shp_ui_h_main_2k[0],0,6));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main_2k[1],0,6),\
																reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main_2k[2],0,6));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_h_main_2k[3],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_h_main_2k[4],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_pti_ctrl_01,	reg_ptih_master_gain,	GET_BITS(pp->shp_ui_h_main_2k[5],0,8));
				#else
				PE_SR_2K_SHP_O18_QWr01(shp_der_ctrl_00,	reg_derh_csft_gain,			GET_BITS(pp->shp_ui_h_main_2k[0],0,6));
				PE_SR_2K_SHP_O18_QWr02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_2k[1],0,6),\
														reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_2k[2],0,6));
				PE_SR_2K_SHP_O18_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_2k[3],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_2k[4],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_pti_ctrl_01,	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_2k[5],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSre2KReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_HOR_T *pp=(LX_PE_SHP_SR2K_RE_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SR_2K_SHP_O18_QRd01(shp_der_ctrl_00, reg_derh_csft_gain, 		pp->shp_ui_h_main_2k[0]);
			PE_SR_2K_SHP_O18_QRd02(shp_der_ctrl_02, reg_derh_edge_filter_gain_w,pp->shp_ui_h_main_2k[1],\
													reg_derh_edge_filter_gain_b,pp->shp_ui_h_main_2k[2]);
			PE_SR_2K_SHP_O18_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			pp->shp_ui_h_main_2k[3]);
			PE_SR_2K_SHP_O18_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			pp->shp_ui_h_main_2k[4]);
			PE_SR_2K_SHP_O18_QRd01(shp_pti_ctrl_01, reg_ptih_master_gain,		pp->shp_ui_h_main_2k[5]);
			pd = pp->shp_ui_h_main_2k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_h_main_2k\n"
			"shp_ui_h_main_2k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSre2KReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_VER_T *pp=(LX_PE_SHP_SR2K_RE_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_v_main_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ui_v_main_2k\n"
			"shp_ui_v_main_2k    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_v_main_2k[0],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_2k[1],0,8));
				#else
				PE_SR_2K_SHP_O18_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_2k[0],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_2k[1],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSre2KReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_VER_T *pp=(LX_PE_SHP_SR2K_RE_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_O18_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		pp->shp_ui_v_main_2k[0]);
				PE_SR_2K_SHP_O18_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	pp->shp_ui_v_main_2k[1]);
			}
			pd = pp->shp_ui_v_main_2k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ui_v_main_2k\n"
			"shp_ui_v_main_2k    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSre2KReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{ 
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_MISC_T *pp=(LX_PE_SHP_SR2K_RE_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_cmn_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_cmn_2k\n"
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18]);
			pd = pp->shp_djg_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_djg_2k\n"
			"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
			pd = pp->shp_map_cmn_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_map_cmn_2k\n"
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_balance_2k\n"
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ti_cmn_2k\n"
			"shp_ti_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_simple_snr_2k\n"
			"shp_simple_snr_2k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				/*shp_cmn_2k*/
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_2k[0],0,1),\
																reg_derh_bflt_tap_size,		GET_BITS(pp->shp_cmn_2k[1],0,3));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,				GET_BITS(pp->shp_cmn_2k[2],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,				GET_BITS(pp->shp_cmn_2k[3],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_mp_ctrl_01,	reg_mp_im_os_gain,			GET_BITS(pp->shp_cmn_2k[4],0,7),\
																reg_mp_im_us_gain,			GET_BITS(pp->shp_cmn_2k[5],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_sp_ctrl_01,	reg_sp_im_os_gain,			GET_BITS(pp->shp_cmn_2k[6],0,7),\
																reg_sp_im_us_gain,			GET_BITS(pp->shp_cmn_2k[7],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dctp_ctrl_00,	reg_dctp_en,				GET_BITS(pp->shp_cmn_2k[8],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,			GET_BITS(pp->shp_cmn_2k[9],0,1),\
																reg_dctp_coring_mode,		GET_BITS(pp->shp_cmn_2k[10],0,2));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_on_off,			GET_BITS(pp->shp_cmn_2k[11],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,			GET_BITS(pp->shp_cmn_2k[12],0,1),\
																reg_tgen_coring_mode,		GET_BITS(pp->shp_cmn_2k[13],0,2));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_nntg_ctrl_00,	reg_nntg_en,				GET_BITS(pp->shp_cmn_2k[14],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,			GET_BITS(pp->shp_cmn_2k[15],0,1),\
																reg_nntg_coring_mode,		GET_BITS(pp->shp_cmn_2k[16],0,2));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dir_blur_ctrl_00,	reg_dir_blur_en,		GET_BITS(pp->shp_cmn_2k[17],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dir_blur_ctrl_01,	reg_dir_blur_base,		GET_BITS(pp->shp_cmn_2k[18],0,8));
				/*shp_djg_2k*/
				PE_SHP_HW_O18_SR_2K_SHP_WR05(shp_dj_ctrl_00,	reg_dj_edf_en,				GET_BITS(pp->shp_djg_2k[0],0,1),\
																reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_2k[1],0,1),\
																reg_dj_soft_en,				GET_BITS(pp->shp_djg_2k[2],0,1),\
																reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_2k[5],0,2),\
																reg_dj_n_avg_mode,			GET_BITS(pp->shp_djg_2k[6],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_dj_ctrl_03,	reg_dj_edge_min,			GET_BITS(pp->shp_djg_2k[3],0,8),\
																reg_dj_edge_mul,			GET_BITS(pp->shp_djg_2k[4],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			GET_BITS(pp->shp_djg_2k[7],0,8));
				/*shp_map_cmn_2k*/
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_fd_ctrl_09,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_2k[0],0,1),\
																reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_2k[1],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR04(shp_fd_ctrl_0b,	reg_fd_mnr_gain_x0,	GET_BITS(pp->shp_map_cmn_2k[2],0,8),\
																reg_fd_mnr_gain_x1,	GET_BITS(pp->shp_map_cmn_2k[3],0,8),\
																reg_fd_mnr_gain_y0,	GET_BITS(pp->shp_map_cmn_2k[4],0,8),\
																reg_fd_mnr_gain_y1,	GET_BITS(pp->shp_map_cmn_2k[5],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR04(shp_fd_ctrl_07,	reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_2k[6],0,8),\
																reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_2k[7],0,8),\
																reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_2k[8],0,8),\
																reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_2k[9],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR04(shp_fd_ctrl_08,	reg_fd_detail_minmax_x0,	GET_BITS(pp->shp_map_cmn_2k[10],0,8),\
																reg_fd_detail_minmax_y0,	GET_BITS(pp->shp_map_cmn_2k[11],0,8),\
																reg_fd_detail_minmax_x1,	GET_BITS(pp->shp_map_cmn_2k[12],0,8),\
																reg_fd_detail_minmax_y1,	GET_BITS(pp->shp_map_cmn_2k[13],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_fd_ctrl_0f,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_2k[14],0,1),\
																reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_2k[15],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR04(shp_fd_ctrl_12,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_2k[16],0,6),\
																reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_2k[17],0,6),\
																reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_2k[18],0,6),\
																reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_2k[19],0,6));
				/*shp_balance_2k*/
				PE_SHP_HW_O18_SR_2K_SHP_WR03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_2k[0],0,1),\
																reg_mp_gb_mode,	GET_BITS(pp->shp_balance_2k[1],0,1),\
																reg_mp_gb_y1,	GET_BITS(pp->shp_balance_2k[2],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_2k[3],0,8),\
																reg_mp_gb_y3,	GET_BITS(pp->shp_balance_2k[4],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_2k[5],0,1),\
																reg_sp_gb_mode,	GET_BITS(pp->shp_balance_2k[6],0,1),\
																reg_sp_gb_y1,	GET_BITS(pp->shp_balance_2k[7],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_2k[8],0,8),\
																reg_sp_gb_y3,	GET_BITS(pp->shp_balance_2k[9],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_2k[10],0,1),\
																reg_lc_gb_en,	GET_BITS(pp->shp_balance_2k[11],0,1));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_2k[12],0,8),\
																reg_lc_gb_y2,	GET_BITS(pp->shp_balance_2k[13],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_2k[14],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_2k[15],0,8),\
																reg_lc_center_gain,	GET_BITS(pp->shp_balance_2k[16],0,8),\
																reg_lc_local_gain,	GET_BITS(pp->shp_balance_2k[17],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR03(shp_mp_ctrl_08,	reg_mp_lum1_y0,	GET_BITS(pp->shp_balance_2k[18],0,8),\
																reg_mp_lum1_y1,	GET_BITS(pp->shp_balance_2k[19],0,8),\
																reg_mp_lum1_y2,	GET_BITS(pp->shp_balance_2k[20],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_mp_ctrl_09,	reg_mp_lum2_y0,	GET_BITS(pp->shp_balance_2k[21],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_mp_ctrl_0a,	reg_mp_lum2_y1,	GET_BITS(pp->shp_balance_2k[22],0,8),\
																reg_mp_lum2_y2,	GET_BITS(pp->shp_balance_2k[23],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR03(shp_sp_ctrl_08,	reg_sp_lum1_y0,	GET_BITS(pp->shp_balance_2k[24],0,8),\
																reg_sp_lum1_y1,	GET_BITS(pp->shp_balance_2k[25],0,8),\
																reg_sp_lum1_y2,	GET_BITS(pp->shp_balance_2k[26],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR01(shp_sp_ctrl_09,	reg_sp_lum2_y0,	GET_BITS(pp->shp_balance_2k[27],0,8));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_sp_ctrl_0a,	reg_sp_lum2_y1,	GET_BITS(pp->shp_balance_2k[28],0,8),\
																reg_sp_lum2_y2,	GET_BITS(pp->shp_balance_2k[29],0,8));
				/*shp_ti_cmn_2k*/
				PE_SHP_HW_O18_SR_2K_SHP_WR04(shp_pti_ctrl_00,	reg_ptiv_enable,	GET_BITS(pp->shp_ti_cmn_2k[0],0,1),\
																reg_ptiv_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[1],0,1),\
																reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[2],0,2),\
																reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[3],0,2));
				PE_SHP_HW_O18_SR_2K_SHP_WR04(shp_pti_ctrl_01,	reg_ptih_enable,	GET_BITS(pp->shp_ti_cmn_2k[4],0,1),\
																reg_ptih_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[5],0,1),\
																reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[6],0,2),\
																reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[7],0,2));
				PE_SHP_HW_O18_SR_2K_SHP_WR04(shp_sti_ctrl_00,	reg_sti_enable,	GET_BITS(pp->shp_ti_cmn_2k[8],0,1),\
																reg_sti_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[9],0,1),\
																reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[10],0,2),\
																reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[11],0,2));
				/*shp_simple_snr_2k*/
				PE_SHP_HW_O18_SR_2K_SHP_WR03(shp_snr_ctrl_00,	reg_snr_blur_en,	GET_BITS(pp->shp_simple_snr_2k[0],0,1),\
																reg_snr_blur_sel,	GET_BITS(pp->shp_simple_snr_2k[1],0,2),\
																reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_2k[2],0,8));
				
				#else
				PE_SR_2K_SHP_O18_QWr02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_2k[0],0,1),\
														reg_derh_bflt_tap_size,		GET_BITS(pp->shp_cmn_2k[1],0,3));
				PE_SR_2K_SHP_O18_QWr01(shp_mp_ctrl_00,	reg_mp_shp_en,				GET_BITS(pp->shp_cmn_2k[2],0,1));
				PE_SR_2K_SHP_O18_QWr01(shp_sp_ctrl_00,	reg_sp_shp_en,				GET_BITS(pp->shp_cmn_2k[3],0,1));
				PE_SR_2K_SHP_O18_QWr02(shp_mp_ctrl_01,	reg_mp_im_os_gain,			GET_BITS(pp->shp_cmn_2k[4],0,7),\
														reg_mp_im_us_gain,			GET_BITS(pp->shp_cmn_2k[5],0,7));
				PE_SR_2K_SHP_O18_QWr02(shp_sp_ctrl_01,	reg_sp_im_os_gain,			GET_BITS(pp->shp_cmn_2k[6],0,7),\
														reg_sp_im_us_gain,			GET_BITS(pp->shp_cmn_2k[7],0,7));
				PE_SR_2K_SHP_O18_QWr01(shp_dctp_ctrl_00,reg_dctp_en,				GET_BITS(pp->shp_cmn_2k[8],0,1));
				PE_SR_2K_SHP_O18_QWr02(shp_dctp_ctrl_1e,reg_dctp_coring_en,			GET_BITS(pp->shp_cmn_2k[9],0,1),\
														reg_dctp_coring_mode,		GET_BITS(pp->shp_cmn_2k[10],0,2));
				PE_SR_2K_SHP_O18_QWr01(shp_tgen_ctrl_00,reg_tgen_on_off,			GET_BITS(pp->shp_cmn_2k[11],0,1));
				PE_SR_2K_SHP_O18_QWr02(shp_tgen_ctrl_0a,reg_tgen_coring_en,			GET_BITS(pp->shp_cmn_2k[12],0,1),\
														reg_tgen_coring_mode,		GET_BITS(pp->shp_cmn_2k[13],0,2));
				PE_SR_2K_SHP_O18_QWr01(shp_nntg_ctrl_00,reg_nntg_en,				GET_BITS(pp->shp_cmn_2k[14],0,1));
				PE_SR_2K_SHP_O18_QWr02(shp_nntg_ctrl_0f,reg_nntg_coring_en,			GET_BITS(pp->shp_cmn_2k[15],0,1),\
														reg_nntg_coring_mode,		GET_BITS(pp->shp_cmn_2k[16],0,2));
				PE_SR_2K_SHP_O18_QWr01(shp_dir_blur_ctrl_00,	reg_dir_blur_en,	GET_BITS(pp->shp_cmn_2k[17],0,1));
				PE_SR_2K_SHP_O18_QWr01(shp_dir_blur_ctrl_01,	reg_dir_blur_base,	GET_BITS(pp->shp_cmn_2k[18],0,8));
				/*shp_djg_2k*/
				PE_SR_2K_SHP_O18_QWr05(shp_dj_ctrl_00,	reg_dj_edf_en,				GET_BITS(pp->shp_djg_2k[0],0,1),\
														reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_2k[1],0,1),\
														reg_dj_soft_en,				GET_BITS(pp->shp_djg_2k[2],0,1),\
														reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_2k[5],0,2),\
														reg_dj_n_avg_mode,			GET_BITS(pp->shp_djg_2k[6],0,1));
				PE_SR_2K_SHP_O18_QWr02(shp_dj_ctrl_03,	reg_dj_edge_min,			GET_BITS(pp->shp_djg_2k[3],0,8),\
														reg_dj_edge_mul,			GET_BITS(pp->shp_djg_2k[4],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			GET_BITS(pp->shp_djg_2k[7],0,8));
				/*shp_map_cmn_2k*/
				PE_SR_2K_SHP_O18_QWr02(shp_fd_ctrl_09,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_2k[0],0,1),\
														reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_2k[1],0,1));
				PE_SR_2K_SHP_O18_QWr04(shp_fd_ctrl_0b,	reg_fd_mnr_gain_x0,		GET_BITS(pp->shp_map_cmn_2k[2],0,8),\
														reg_fd_mnr_gain_x1,		GET_BITS(pp->shp_map_cmn_2k[3],0,8),\
														reg_fd_mnr_gain_y0,		GET_BITS(pp->shp_map_cmn_2k[4],0,8),\
														reg_fd_mnr_gain_y1,		GET_BITS(pp->shp_map_cmn_2k[5],0,8));
				PE_SR_2K_SHP_O18_QWr04(shp_fd_ctrl_07,	reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_2k[6],0,8),\
														reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_2k[7],0,8),\
														reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_2k[8],0,8),\
														reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_2k[9],0,8));
				PE_SR_2K_SHP_O18_QWr04(shp_fd_ctrl_08,	reg_fd_detail_minmax_x0,GET_BITS(pp->shp_map_cmn_2k[10],0,8),\
														reg_fd_detail_minmax_y0,GET_BITS(pp->shp_map_cmn_2k[11],0,8),\
														reg_fd_detail_minmax_x1,GET_BITS(pp->shp_map_cmn_2k[12],0,8),\
														reg_fd_detail_minmax_y1,GET_BITS(pp->shp_map_cmn_2k[13],0,8));
				PE_SR_2K_SHP_O18_QWr02(shp_fd_ctrl_0f,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_2k[14],0,1),\
														reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_2k[15],0,1));
				PE_SR_2K_SHP_O18_QWr04(shp_fd_ctrl_12,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_2k[16],0,6),\
														reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_2k[17],0,6),\
														reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_2k[18],0,6),\
														reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_2k[19],0,6));
				/*shp_balance_2k*/
				PE_SR_2K_SHP_O18_QWr03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_2k[0],0,1),\
														reg_mp_gb_mode,	GET_BITS(pp->shp_balance_2k[1],0,1),\
														reg_mp_gb_y1,	GET_BITS(pp->shp_balance_2k[2],0,8));
				PE_SR_2K_SHP_O18_QWr02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_2k[3],0,8),\
														reg_mp_gb_y3,	GET_BITS(pp->shp_balance_2k[4],0,8));
				PE_SR_2K_SHP_O18_QWr03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_2k[5],0,1),\
														reg_sp_gb_mode,	GET_BITS(pp->shp_balance_2k[6],0,1),\
														reg_sp_gb_y1,	GET_BITS(pp->shp_balance_2k[7],0,8));
				PE_SR_2K_SHP_O18_QWr02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_2k[8],0,8),\
														reg_sp_gb_y3,	GET_BITS(pp->shp_balance_2k[9],0,8));
				PE_SR_2K_SHP_O18_QWr02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_2k[10],0,1),\
														reg_lc_gb_en,	GET_BITS(pp->shp_balance_2k[11],0,1));
				PE_SR_2K_SHP_O18_QWr02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_2k[12],0,8),\
														reg_lc_gb_y2,	GET_BITS(pp->shp_balance_2k[13],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_2k[14],0,8));
				PE_SR_2K_SHP_O18_QWr03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_2k[15],0,8),\
														reg_lc_center_gain,		GET_BITS(pp->shp_balance_2k[16],0,8),\
														reg_lc_local_gain,		GET_BITS(pp->shp_balance_2k[17],0,8));
				PE_SR_2K_SHP_O18_QWr03(shp_mp_ctrl_08,	reg_mp_lum1_y0,	GET_BITS(pp->shp_balance_2k[18],0,8),\
														reg_mp_lum1_y1,	GET_BITS(pp->shp_balance_2k[19],0,8),\
														reg_mp_lum1_y2,	GET_BITS(pp->shp_balance_2k[20],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_mp_ctrl_09,	reg_mp_lum2_y0,	GET_BITS(pp->shp_balance_2k[21],0,8));
				PE_SR_2K_SHP_O18_QWr02(shp_mp_ctrl_0a,	reg_mp_lum2_y1,	GET_BITS(pp->shp_balance_2k[22],0,8),\
														reg_mp_lum2_y2,	GET_BITS(pp->shp_balance_2k[23],0,8));
				PE_SR_2K_SHP_O18_QWr03(shp_sp_ctrl_08,	reg_sp_lum1_y0,	GET_BITS(pp->shp_balance_2k[24],0,8),\
														reg_sp_lum1_y1,	GET_BITS(pp->shp_balance_2k[25],0,8),\
														reg_sp_lum1_y2,	GET_BITS(pp->shp_balance_2k[26],0,8));
				PE_SR_2K_SHP_O18_QWr01(shp_sp_ctrl_09,	reg_sp_lum2_y0,	GET_BITS(pp->shp_balance_2k[27],0,8));
				PE_SR_2K_SHP_O18_QWr02(shp_sp_ctrl_0a,	reg_sp_lum2_y1,	GET_BITS(pp->shp_balance_2k[28],0,8),\
														reg_sp_lum2_y2,	GET_BITS(pp->shp_balance_2k[29],0,8));
				/*shp_ti_cmn_2k*/
				PE_SR_2K_SHP_O18_QWr04(shp_pti_ctrl_00,	reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_2k[0],0,1),\
														reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_2k[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[3],0,2));
				PE_SR_2K_SHP_O18_QWr04(shp_pti_ctrl_01,	reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_2k[4],0,1),\
														reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_2k[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[7],0,2));
				PE_SR_2K_SHP_O18_QWr04(shp_sti_ctrl_00,	reg_sti_enable,			GET_BITS(pp->shp_ti_cmn_2k[8],0,1),\
														reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_2k[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[11],0,2));
				/*shp_simple_snr_2k*/
				PE_SR_2K_SHP_O18_QWr03(shp_snr_ctrl_00,	reg_snr_blur_en,		GET_BITS(pp->shp_simple_snr_2k[0],0,1),\
														reg_snr_blur_sel,		GET_BITS(pp->shp_simple_snr_2k[1],0,2),\
														reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_2k[2],0,8));


				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSre2KReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_MISC_T *pp=(LX_PE_SHP_SR2K_RE_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_2K_SHP_O18_QRd02(shp_der_ctrl_01, reg_derh_edge_y_filter_en,	pp->shp_cmn_2k[0],\
														reg_derh_bflt_tap_size, 	pp->shp_cmn_2k[1]);
				PE_SR_2K_SHP_O18_QRd01(shp_mp_ctrl_00,	reg_mp_shp_en,				pp->shp_cmn_2k[2]);
				PE_SR_2K_SHP_O18_QRd01(shp_sp_ctrl_00,	reg_sp_shp_en,				pp->shp_cmn_2k[3]);
				PE_SR_2K_SHP_O18_QRd02(shp_mp_ctrl_01,	reg_mp_im_os_gain,			pp->shp_cmn_2k[4],\
														reg_mp_im_us_gain,			pp->shp_cmn_2k[5]);
				PE_SR_2K_SHP_O18_QRd02(shp_sp_ctrl_01,	reg_sp_im_os_gain,			pp->shp_cmn_2k[6],\
														reg_sp_im_us_gain,			pp->shp_cmn_2k[7]);
				PE_SR_2K_SHP_O18_QRd01(shp_dctp_ctrl_00,reg_dctp_en,				pp->shp_cmn_2k[8]);
				PE_SR_2K_SHP_O18_QRd02(shp_dctp_ctrl_1e,reg_dctp_coring_en, 		pp->shp_cmn_2k[9],\
														reg_dctp_coring_mode,		pp->shp_cmn_2k[10]);
				PE_SR_2K_SHP_O18_QRd01(shp_tgen_ctrl_00,reg_tgen_on_off,			pp->shp_cmn_2k[11]);
				PE_SR_2K_SHP_O18_QRd02(shp_tgen_ctrl_0a,reg_tgen_coring_en, 		pp->shp_cmn_2k[12],\
														reg_tgen_coring_mode,		pp->shp_cmn_2k[13]);
				PE_SR_2K_SHP_O18_QRd01(shp_nntg_ctrl_00,reg_nntg_en,				pp->shp_cmn_2k[14]);
				PE_SR_2K_SHP_O18_QRd02(shp_nntg_ctrl_0f,reg_nntg_coring_en, 		pp->shp_cmn_2k[15],\
														reg_nntg_coring_mode,		pp->shp_cmn_2k[16]);
				PE_SR_2K_SHP_O18_QRd01(shp_dir_blur_ctrl_00,	reg_dir_blur_en,	pp->shp_cmn_2k[17]);
				PE_SR_2K_SHP_O18_QRd01(shp_dir_blur_ctrl_01,	reg_dir_blur_base,	pp->shp_cmn_2k[18]);
				/*shp_djg_2k*/
				PE_SR_2K_SHP_O18_QRd05(shp_dj_ctrl_00,	reg_dj_edf_en,				pp->shp_djg_2k[0],\
														reg_dj_edge_adaptive_en,	pp->shp_djg_2k[1],\
														reg_dj_soft_en,				pp->shp_djg_2k[2],\
														reg_dj_center_blur_mode,	pp->shp_djg_2k[5],\
														reg_dj_n_avg_mode,			pp->shp_djg_2k[6]);
				PE_SR_2K_SHP_O18_QRd02(shp_dj_ctrl_03,	reg_dj_edge_min,			pp->shp_djg_2k[3],\
														reg_dj_edge_mul,			pp->shp_djg_2k[4]);
				PE_SR_2K_SHP_O18_QRd01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			pp->shp_djg_2k[7]);
				/*shp_map_cmn_2k*/
				PE_SR_2K_SHP_O18_QRd02(shp_fd_ctrl_09,	reg_fd_mnr_gain_e_en,	pp->shp_map_cmn_2k[0],\
														reg_fd_mnr_gain_t_en,	pp->shp_map_cmn_2k[1]);
				PE_SR_2K_SHP_O18_QRd04(shp_fd_ctrl_0b,	reg_fd_mnr_gain_x0, 	pp->shp_map_cmn_2k[2],\
														reg_fd_mnr_gain_x1, 	pp->shp_map_cmn_2k[3],\
														reg_fd_mnr_gain_y0, 	pp->shp_map_cmn_2k[4],\
														reg_fd_mnr_gain_y1, 	pp->shp_map_cmn_2k[5]);
				PE_SR_2K_SHP_O18_QRd04(shp_fd_ctrl_07,	reg_fd_edge_minmax_x0,	pp->shp_map_cmn_2k[6],\
														reg_fd_edge_minmax_y0,	pp->shp_map_cmn_2k[7],\
														reg_fd_edge_minmax_x1,	pp->shp_map_cmn_2k[8],\
														reg_fd_edge_minmax_y1,	pp->shp_map_cmn_2k[9]);
				PE_SR_2K_SHP_O18_QRd04(shp_fd_ctrl_08,	reg_fd_detail_minmax_x0,pp->shp_map_cmn_2k[10],\
														reg_fd_detail_minmax_y0,pp->shp_map_cmn_2k[11],\
														reg_fd_detail_minmax_x1,pp->shp_map_cmn_2k[12],\
														reg_fd_detail_minmax_y1,pp->shp_map_cmn_2k[13]);
				PE_SR_2K_SHP_O18_QRd02(shp_fd_ctrl_0f,	reg_fd_soft_gain_t_en,	pp->shp_map_cmn_2k[14],\
														reg_fd_soft_gain_e_en,	pp->shp_map_cmn_2k[15]);
				PE_SR_2K_SHP_O18_QRd04(shp_fd_ctrl_12,	reg_fd_soft_score_y3,	pp->shp_map_cmn_2k[16],\
														reg_fd_soft_score_y2,	pp->shp_map_cmn_2k[17],\
														reg_fd_soft_score_y1,	pp->shp_map_cmn_2k[18],\
														reg_fd_soft_score_y0,	pp->shp_map_cmn_2k[19]);
				/*shp_balance_2k*/
				PE_SR_2K_SHP_O18_QRd03(shp_mp_ctrl_05,	reg_mp_gb_en,	pp->shp_balance_2k[0],\
														reg_mp_gb_mode, pp->shp_balance_2k[1],\
														reg_mp_gb_y1,	pp->shp_balance_2k[2]);
				PE_SR_2K_SHP_O18_QRd02(shp_mp_ctrl_06,	reg_mp_gb_y2,	pp->shp_balance_2k[3],\
														reg_mp_gb_y3,	pp->shp_balance_2k[4]);
				PE_SR_2K_SHP_O18_QRd03(shp_sp_ctrl_05,	reg_sp_gb_en,	pp->shp_balance_2k[5],\
														reg_sp_gb_mode, pp->shp_balance_2k[6],\
														reg_sp_gb_y1,	pp->shp_balance_2k[7]);
				PE_SR_2K_SHP_O18_QRd02(shp_sp_ctrl_06,	reg_sp_gb_y2,	pp->shp_balance_2k[8],\
														reg_sp_gb_y3,	pp->shp_balance_2k[9]);
				PE_SR_2K_SHP_O18_QRd02(shp_lc_ctrl_00,	reg_lc_shp_en,	pp->shp_balance_2k[10],\
														reg_lc_gb_en,	pp->shp_balance_2k[11]);
				PE_SR_2K_SHP_O18_QRd02(shp_lc_ctrl_01,	reg_lc_gb_y1,	pp->shp_balance_2k[12],\
														reg_lc_gb_y2,	pp->shp_balance_2k[13]);
				PE_SR_2K_SHP_O18_QRd01(shp_lc_ctrl_02,	reg_lc_gb_y3,	pp->shp_balance_2k[14]);
				PE_SR_2K_SHP_O18_QRd03(shp_lc_ctrl_00,	reg_lc_center_target,	pp->shp_balance_2k[15],\
														reg_lc_center_gain, 	pp->shp_balance_2k[16],\
														reg_lc_local_gain,		pp->shp_balance_2k[17]);
				PE_SR_2K_SHP_O18_QRd03(shp_mp_ctrl_08,	reg_mp_lum1_y0, pp->shp_balance_2k[18],\
														reg_mp_lum1_y1, pp->shp_balance_2k[19],\
														reg_mp_lum1_y2, pp->shp_balance_2k[20]);
				PE_SR_2K_SHP_O18_QRd01(shp_mp_ctrl_09,	reg_mp_lum2_y0, pp->shp_balance_2k[21]);
				PE_SR_2K_SHP_O18_QRd02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, pp->shp_balance_2k[22],\
														reg_mp_lum2_y2, pp->shp_balance_2k[23]);
				PE_SR_2K_SHP_O18_QRd03(shp_sp_ctrl_08,	reg_sp_lum1_y0, pp->shp_balance_2k[24],\
														reg_sp_lum1_y1, pp->shp_balance_2k[25],\
														reg_sp_lum1_y2, pp->shp_balance_2k[26]);
				PE_SR_2K_SHP_O18_QRd01(shp_sp_ctrl_09,	reg_sp_lum2_y0, pp->shp_balance_2k[27]);
				PE_SR_2K_SHP_O18_QRd02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, pp->shp_balance_2k[28],\
														reg_sp_lum2_y2, pp->shp_balance_2k[29]);
				/*shp_ti_cmn_2k*/
				PE_SR_2K_SHP_O18_QRd04(shp_pti_ctrl_00, reg_ptiv_enable,		pp->shp_ti_cmn_2k[0],\
														reg_ptiv_ti_mode,		pp->shp_ti_cmn_2k[1],\
														reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_2k[2],\
														reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_2k[3]);
				PE_SR_2K_SHP_O18_QRd04(shp_pti_ctrl_01, reg_ptih_enable,		pp->shp_ti_cmn_2k[4],\
														reg_ptih_ti_mode,		pp->shp_ti_cmn_2k[5],\
														reg_ptih_mm_tap_size,	pp->shp_ti_cmn_2k[6],\
														reg_ptih_avg_tap_size,	pp->shp_ti_cmn_2k[7]);
				PE_SR_2K_SHP_O18_QRd04(shp_sti_ctrl_00, reg_sti_enable, 		pp->shp_ti_cmn_2k[8],\
														reg_sti_ti_mode,		pp->shp_ti_cmn_2k[9],\
														reg_sti_mm_tap_size,	pp->shp_ti_cmn_2k[10],\
														reg_sti_avg_tap_size,	pp->shp_ti_cmn_2k[11]);
				/*shp_simple_snr_2k*/
				PE_SR_2K_SHP_O18_QRd03(shp_snr_ctrl_00, reg_snr_blur_en,		pp->shp_simple_snr_2k[0],\
														reg_snr_blur_sel,		pp->shp_simple_snr_2k[1],\
														reg_snr_bilateral_th,	pp->shp_simple_snr_2k[2]);

			}
			pd = pp->shp_cmn_2k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_cmn_2k\n"
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18]);
			pd = pp->shp_djg_2k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_djg_2k\n"
			"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
			pd = pp->shp_map_cmn_2k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_map_cmn_2k\n"
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_2k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_balance_2k\n"
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_2k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ti_cmn_2k\n"
			"shp_ti_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_2k;
			PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_simple_snr_2k\n"
			"shp_simple_snr_2k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
		}
		
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSre2KEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_EE_T *pp = (LX_PE_SHP_SR2K_EE_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ee_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_ee_2k\n"
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[0],0,7),\
																reg_mp_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[1],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[2],0,7),\
																reg_sp_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[3],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[4],0,7),\
																reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[5],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[6],0,7),\
																reg_lc_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[7],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[8],0,7),\
																reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[9],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[10],0,7),\
																reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[11],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[12],0,7),\
																reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[13],0,7));
				#else
				PE_SR_2K_SHP_O18_QWr02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b, 	pp->shp_ee_2k[0],\
														reg_mp_coring_gain_e_w, 	pp->shp_ee_2k[1]);
				PE_SR_2K_SHP_O18_QWr02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b, 	pp->shp_ee_2k[2],\
														reg_sp_coring_gain_e_w, 	pp->shp_ee_2k[3]);
				PE_SR_2K_SHP_O18_QWr02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,	pp->shp_ee_2k[4],\
														reg_pti_coring_gain_e_w,	pp->shp_ee_2k[5]);
				PE_SR_2K_SHP_O18_QWr02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b, 	pp->shp_ee_2k[6],\
														reg_lc_coring_gain_e_w, 	pp->shp_ee_2k[7]);
				PE_SR_2K_SHP_O18_QWr02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_e_b,	pp->shp_ee_2k[8],\
														reg_dctp_coring_gain_e_w,	pp->shp_ee_2k[9]);
				PE_SR_2K_SHP_O18_QWr02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_e_b,	pp->shp_ee_2k[10],\
														reg_tgen_coring_gain_e_w,	pp->shp_ee_2k[11]);
				PE_SR_2K_SHP_O18_QWr02(shp_nntg_ctrl_10,reg_nntg_coring_gain_e_b,	pp->shp_ee_2k[12],\
														reg_nntg_coring_gain_e_w,	pp->shp_ee_2k[13]);
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for O18
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSre2KEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_EE_T *pp = (LX_PE_SHP_SR2K_EE_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_O18_QRd02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b, 	pp->shp_ee_2k[0],\
														reg_mp_coring_gain_e_w, 	pp->shp_ee_2k[1]);
				PE_SR_2K_SHP_O18_QRd02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b, 	pp->shp_ee_2k[2],\
														reg_sp_coring_gain_e_w, 	pp->shp_ee_2k[3]);
				PE_SR_2K_SHP_O18_QRd02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,	pp->shp_ee_2k[4],\
														reg_pti_coring_gain_e_w,	pp->shp_ee_2k[5]);
				PE_SR_2K_SHP_O18_QRd02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b, 	pp->shp_ee_2k[6],\
														reg_lc_coring_gain_e_w, 	pp->shp_ee_2k[7]);
				PE_SR_2K_SHP_O18_QRd02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_e_b,	pp->shp_ee_2k[8],\
														reg_dctp_coring_gain_e_w,	pp->shp_ee_2k[9]);
				PE_SR_2K_SHP_O18_QRd02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_e_b,	pp->shp_ee_2k[10],\
														reg_tgen_coring_gain_e_w,	pp->shp_ee_2k[11]);
				PE_SR_2K_SHP_O18_QRd02(shp_nntg_ctrl_10,reg_nntg_coring_gain_e_b,	pp->shp_ee_2k[12],\
														reg_nntg_coring_gain_e_w,	pp->shp_ee_2k[13]);
				pd = pp->shp_ee_2k;
				PE_SHP_HW_O18_DBG_PRINT("get[%d] : shp_ee_2k\n"
				"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13]);
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetSre2KDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_DE_T *pp=(LX_PE_SHP_SR2K_DE_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_de_2k;
			PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_de_2k\n"
			"shp_de_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, GET_BITS(pp->shp_de_2k[0],0,7),\
																reg_mp_coring_gain_t_w, GET_BITS(pp->shp_de_2k[1],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, GET_BITS(pp->shp_de_2k[2],0,7),\
																reg_sp_coring_gain_t_w, GET_BITS(pp->shp_de_2k[3],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[4],0,7),\
																reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[5],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, GET_BITS(pp->shp_de_2k[6],0,7),\
																reg_lc_coring_gain_t_w, GET_BITS(pp->shp_de_2k[7],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[8],0,7),\
																reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[9],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[10],0,7),\
																reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[11],0,7));
				PE_SHP_HW_O18_SR_2K_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[12],0,7),\
																reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[13],0,7));
				#else
				PE_SR_2K_SHP_O18_QWr02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, 	GET_BITS(pp->shp_de_2k[0],0,7),\
														reg_mp_coring_gain_t_w, 	GET_BITS(pp->shp_de_2k[1],0,7));
				PE_SR_2K_SHP_O18_QWr02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, 	GET_BITS(pp->shp_de_2k[2],0,7),\
														reg_sp_coring_gain_t_w, 	GET_BITS(pp->shp_de_2k[3],0,7));
				PE_SR_2K_SHP_O18_QWr02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[4],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[5],0,7));
				PE_SR_2K_SHP_O18_QWr02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, 	GET_BITS(pp->shp_de_2k[6],0,7),\
														reg_lc_coring_gain_t_w, 	GET_BITS(pp->shp_de_2k[7],0,7));
				PE_SR_2K_SHP_O18_QWr02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[8],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[9],0,7));
				PE_SR_2K_SHP_O18_QWr02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[10],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[11],0,7));
				PE_SR_2K_SHP_O18_QWr02(shp_nntg_ctrl_10,reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[12],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for O18X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetSre2KDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_DE_T *pp=(LX_PE_SHP_SR2K_DE_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_de_2k;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_O18_QRd02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, 	pp->shp_de_2k[0],\
														reg_mp_coring_gain_t_w, 	pp->shp_de_2k[1]);
				PE_SR_2K_SHP_O18_QRd02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, 	pp->shp_de_2k[2],\
														reg_sp_coring_gain_t_w, 	pp->shp_de_2k[3]);
				PE_SR_2K_SHP_O18_QRd02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	pp->shp_de_2k[4],\
														reg_pti_coring_gain_t_w,	pp->shp_de_2k[5]);
				PE_SR_2K_SHP_O18_QRd02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, 	pp->shp_de_2k[6],\
														reg_lc_coring_gain_t_w, 	pp->shp_de_2k[7]);
				PE_SR_2K_SHP_O18_QRd02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	pp->shp_de_2k[8],\
														reg_dctp_coring_gain_t_w,	pp->shp_de_2k[9]);
				PE_SR_2K_SHP_O18_QRd02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_t_b,	pp->shp_de_2k[10],\
														reg_tgen_coring_gain_t_w,	pp->shp_de_2k[11]);
				PE_SR_2K_SHP_O18_QRd02(shp_nntg_ctrl_10,reg_nntg_coring_gain_t_b,	pp->shp_de_2k[12],\
														reg_nntg_coring_gain_t_w,	pp->shp_de_2k[13]);
				PE_SHP_HW_O18_DBG_PRINT("set[%d] : shp_de_2k\n"
				"shp_de_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_de_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13]);
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_O18_SetSre2KSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			LX_PE_SHP_SR2K_SQM_CMN_T *ctrl_param =(LX_PE_SHP_SR2K_SQM_CMN_T *)pstParams;
			LX_PE_SHP_SR2K_SQM1_CMN_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o18_trace)
			{
				UINT32 *pd = pp->shp_ui_sqm_2k;
				PE_SHP_HW_O18_DBG_PRINT("[%d]shp_ui_sqm_2k:%d\n", pp->win_id, pp->shp_sqm___val);
				PE_SHP_HW_O18_DBG_PRINT( \
				"shp_ui_sqm_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_2k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_2k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
				pd[10],pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19], \
				pd[20],pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26],  pd[27], pd[28]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_O18_DownloadShp2KSqmCmnUserDb((void *)pp);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
					"[%s,%d] PE_SHP_HW_O18_DownloadShp2KSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_O18_SetSre2KSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			LX_PE_SHP_SR2K_SQM_DETAIL_T *ctrl_param =(LX_PE_SHP_SR2K_SQM_DETAIL_T *)pstParams;
			LX_PE_SHP_SR2K_SQM1_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o18_trace)
			{
				UINT32 *pd = pp->shp_sqm_cmn_2k;
				PE_SHP_HW_O18_DBG_PRINT("[%d]shp_sqm_cmn_2k:%d\n", pp->win_id, pp->shp_sqm____val);
				PE_SHP_HW_O18_DBG_PRINT( \
				"shp_sqm_cmn_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_sqm_cmn_2k[10]0x%08X\n", \
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
				pd[8],  pd[9],  pd[10]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_O18_DownloadShp2KSqmDetailUserDb((void *)pp);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
					"[%s,%d] PE_SHP_HW_O18_DownloadShp2KSqmDetailUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_O18_SetSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			LX_PE_SHP_RE_SQM_CMN_T *ctrl_param =(LX_PE_SHP_RE_SQM_CMN_T *)pstParams;
			LX_PE_SHP_RE_SQM1_CMN_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o18_trace)
			{
				UINT32 *pd = pp->shp_ui_sqm_vsd;
				PE_SHP_HW_O18_DBG_PRINT("[%d]shp_ui_sqm_2k:%d\n", pp->win_id, pp->shp_sqm____val);
				PE_SHP_HW_O18_DBG_PRINT( \
				"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
				pd[10],pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19], \
				pd[20],pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26],  pd[27], pd[28],  pd[29]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_O18_DownloadShpSqmCmnUserDb((void *)pp);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
					"[%s,%d] PE_SHP_HW_O18_DownloadShpSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_O18_SetSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			LX_PE_SHP_RE_SQM_DETAIL_T *ctrl_param =(LX_PE_SHP_RE_SQM_DETAIL_T *)pstParams;
			LX_PE_SHP_RE_SQM1_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o18_trace)
			{
				UINT32 *pd = pp->shp_sqm_cmn_vsd;
				PE_SHP_HW_O18_DBG_PRINT("[%d]shp_sqm_cmn_vsd:%d\n", pp->win_id, pp->shp_sqm_____val);
				PE_SHP_HW_O18_DBG_PRINT( \
				"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_sqm_cmn_vsd[10]0x%08X\n", \
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
				pd[8],  pd[9],  pd[10]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_O18_DownloadShpSqmDetailUserDb((void *)pp);
				PE_SHP_HW_O18_CHECK_CODE(ret, break, \
					"[%s,%d] PE_SHP_HW_O18_DownloadShpSqmDetailUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}



/**
 * set pbl(pre blur dnr) apply
 *
 * @param   *pCfg [in] PE_TSK_O18_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_SetPblApply(PE_TSK_O18_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	#ifdef PE_SHP_HW_O18_CROSS_PAT_DETECT
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
		if(PE_KDRV_VER_O18)
		{
			if(g_pe_inf_o18_vr360_mode)
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
			ret = PE_INF_O18_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
			ret = PE_HST_HW_O18_GetSrcHistoBin(0, histo_bin, 0);//Y
			ret = PE_HST_HW_O18_GetSrcHistoBin(0, s_bin, 7);//S
			hist_low = histo_bin[0]+histo_bin[1]+histo_bin[2]+histo_bin[3]+histo_bin[4]+histo_bin[5]+histo_bin[6]+histo_bin[7];
			hist_mid = histo_bin[8]+histo_bin[9]+histo_bin[10]+histo_bin[11]+histo_bin[12]+histo_bin[13]+histo_bin[13]+histo_bin[14]\
				   +histo_bin[15]+histo_bin[16]+histo_bin[17]+histo_bin[18]+histo_bin[19]+histo_bin[20]+histo_bin[21]+histo_bin[22];
			hist_high = histo_bin[23]+histo_bin[24]+histo_bin[25]+histo_bin[26]+histo_bin[27]+histo_bin[28]+histo_bin[29]+histo_bin[30]+histo_bin[31];
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

			if((s_bin[0]+s_bin[1])>130000 && (hist_high > 120000) && (hist_low > 8000) && (hist_mid < 30000) && (hist_low <19000))
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
				data_shp = _g_pe_srs_hw_param_data_o18.reg_dflt.data->shp_der_ctrl_00.reg_derh_th_gain_edge;
				shp_bypass = 0x0;
			}
			if(_g_shp_hw_o18_trace)
			{
				if(count>32)
				{
					PE_SHP_HW_O18_DBG_PRINT("s: %d\n",(s_bin[0]+s_bin[1]) );
#ifdef INCLUDE_KDRV_AFE
					PE_SHP_HW_O18_DBG_PRINT("pattern :%d, static :%d, colorbar : %d\n", \
							is_pattern, g_CVD_Pattern_Detection_t.static_pattern_found,g_CVD_Pattern_Detection_t.pattern_found );
#endif
					PE_SHP_HW_O18_DBG_PRINT("low :%d, mid :%d, high : %d\n",hist_low, hist_mid,hist_high );
					PE_SHP_HW_O18_DBG_PRINT("cross_hat :%d, cross_hat_inv :%d, cross : %d, cross_inv : %d\n"\
							,f_cross_hat_pattern, f_cross_hat_pattern_inv,f_cross_pattern, f_cross_pattern_inv);
					PE_SHP_HW_O18_DBG_PRINT("pre :%d, curr :%d\n", data_shp,_g_pre_data_shp );
					PE_SHP_HW_O18_DBG_PRINT("bypass pre :%d, curr :%d\n", shp_bypass,_g_pre_shp_bypass );
					count=0;
				}
				count++;
			}
			if(data_shp != _g_pre_data_shp)
			{
				PE_SHP_HW_O18_SR_SHP_WR01(shp_der_ctrl_00, reg_derh_th_gain_edge, GET_BITS(data_shp, 0,6));
				_g_pre_data_shp = data_shp;
			}
			if(shp_bypass !=GET_BITS(_g_pre_shp_bypass,0,1) )
			{
				PE_SHP_O18_QWr01(shp_core_ctrl_00,	reg_top_core_bypass,		GET_BITS(shp_bypass,0,1));
				_g_pre_shp_bypass = shp_bypass;
			}
			
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif /*PE_HW_O18_BRINGUP*/
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
int PE_SHP_HW_O18_DownloadSclDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		/* t12_m **************************************************************/
		ret = PE_SHP_HW_O18_DownloadScl12tMainDb();
		PE_SHP_HW_O18_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_O18_DownloadScl12tMainDb() error.\n",__F__,__L__);
		/* t08_m **************************************************************/
		ret = PE_SHP_HW_O18_DownloadScl08tMainDb();
		PE_SHP_HW_O18_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_O18_DownloadScl08tMainDb() error.\n",__F__,__L__);
		/* t04_m **************************************************************/
		ret = PE_SHP_HW_O18_DownloadScl04tMainDb();
		PE_SHP_HW_O18_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_O18_DownloadScl04tMainDb() error.\n",__F__,__L__);
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
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
static int PE_SHP_HW_O18_DownloadScl12tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 size = 0, i = 0;
	UINT32 sec_typ_1212 = 0, sec_typ_1206 = 0,sec_typ_1204 = 0, sec_typ_1202 = 0;
	UINT32 base_line_1212[PE_DDR_O18_1212T_FLT_NUM];
	UINT32 base_line_1206[PE_DDR_O18_1206T_FLT_NUM];
	UINT32 base_line_1204[PE_DDR_O18_1204T_FLT_NUM];
	UINT32 base_line_1202[PE_DDR_O18_1202T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O18_T *p_phys_db = gPE_DDR_DB_O18.phys.data;
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
		if (PE_KDRV_VER_O18)
		{
			/*1. 1212  */
			sec_typ_1212 = PE_DDR_O18_SEC_SCL_1212T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1212].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1212].header.sec_type  = sec_typ_1212;
			p_shdw_db->sec_d[sec_typ_1212].header.item_num  = PE_DDR_O18_1212T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1212].header.item_size = PE_DDR_O18_SCL_12T_FLT_SIZE;
			p_phys_db->t1212.header.version   = p_shdw_db->sec_d[sec_typ_1212].header.version;
			p_phys_db->t1212.header.sec_type  = p_shdw_db->sec_d[sec_typ_1212].header.sec_type;
			p_phys_db->t1212.header.item_num  = p_shdw_db->sec_d[sec_typ_1212].header.item_num;
			p_phys_db->t1212.header.item_size = p_shdw_db->sec_d[sec_typ_1212].header.item_size;

			/* data */
			size = (PE_DDR_O18_1212T_FLT_NUM * PE_DDR_O18_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1212] = \
				p_shdw_db->top_h.sec_base[sec_typ_1212-1]+p_shdw_db->top_h.sec_size[sec_typ_1212-1];
			p_shdw_db->top_h.sec_size[sec_typ_1212] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1212] = p_shdw_db->top_h.sec_base[sec_typ_1212];
			p_phys_db->top_h.sec_size[sec_typ_1212] = p_shdw_db->top_h.sec_size[sec_typ_1212];
			p_shdw_db->sec_d[sec_typ_1212].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1212] + sizeof(PE_DDR_O18_HEADER_T);


			/*2. 1206*/
			sec_typ_1206 = PE_DDR_O18_SEC_SCL_1206T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1206].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1206].header.sec_type  = sec_typ_1206;
			p_shdw_db->sec_d[sec_typ_1206].header.item_num  = PE_DDR_O18_1206T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1206].header.item_size = PE_DDR_O18_SCL_12T_FLT_SIZE;
			p_phys_db->t1206.header.version   = p_shdw_db->sec_d[sec_typ_1206].header.version;
			p_phys_db->t1206.header.sec_type  = p_shdw_db->sec_d[sec_typ_1206].header.sec_type;
			p_phys_db->t1206.header.item_num  = p_shdw_db->sec_d[sec_typ_1206].header.item_num;
			p_phys_db->t1206.header.item_size = p_shdw_db->sec_d[sec_typ_1206].header.item_size;
			/* data */
			size = (PE_DDR_O18_1206T_FLT_NUM * PE_DDR_O18_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1206] = \
				p_shdw_db->top_h.sec_base[sec_typ_1206-1]+p_shdw_db->top_h.sec_size[sec_typ_1206-1];
			p_shdw_db->top_h.sec_size[sec_typ_1206] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1206] = p_shdw_db->top_h.sec_base[sec_typ_1206];
			p_phys_db->top_h.sec_size[sec_typ_1206] = p_shdw_db->top_h.sec_size[sec_typ_1206];
			p_shdw_db->sec_d[sec_typ_1206].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1206] + sizeof(PE_DDR_O18_HEADER_T);

			/*3. 1204*/
			sec_typ_1204 = PE_DDR_O18_SEC_SCL_1204T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1204].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1204].header.sec_type  = sec_typ_1204;
			p_shdw_db->sec_d[sec_typ_1204].header.item_num  = PE_DDR_O18_1204T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1204].header.item_size = PE_DDR_O18_SCL_12T_FLT_SIZE;
			p_phys_db->t1204.header.version   = p_shdw_db->sec_d[sec_typ_1204].header.version;
			p_phys_db->t1204.header.sec_type  = p_shdw_db->sec_d[sec_typ_1204].header.sec_type;
			p_phys_db->t1204.header.item_num  = p_shdw_db->sec_d[sec_typ_1204].header.item_num;
			p_phys_db->t1204.header.item_size = p_shdw_db->sec_d[sec_typ_1204].header.item_size;
			/* data */
			size = (PE_DDR_O18_1204T_FLT_NUM * PE_DDR_O18_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1204] = \
				p_shdw_db->top_h.sec_base[sec_typ_1204-1]+p_shdw_db->top_h.sec_size[sec_typ_1204-1];
			p_shdw_db->top_h.sec_size[sec_typ_1204] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1204] = p_shdw_db->top_h.sec_base[sec_typ_1204];
			p_phys_db->top_h.sec_size[sec_typ_1204] = p_shdw_db->top_h.sec_size[sec_typ_1204];
			p_shdw_db->sec_d[sec_typ_1204].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1204] + sizeof(PE_DDR_O18_HEADER_T);

			/*4. 1202*/
			sec_typ_1202 = PE_DDR_O18_SEC_SCL_1202T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1202].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1202].header.sec_type  = sec_typ_1202;
			p_shdw_db->sec_d[sec_typ_1202].header.item_num  = PE_DDR_O18_1202T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1202].header.item_size = PE_DDR_O18_SCL_12T_FLT_SIZE;
			p_phys_db->t1202.header.version   = p_shdw_db->sec_d[sec_typ_1202].header.version;
			p_phys_db->t1202.header.sec_type  = p_shdw_db->sec_d[sec_typ_1202].header.sec_type;
			p_phys_db->t1202.header.item_num  = p_shdw_db->sec_d[sec_typ_1202].header.item_num;
			p_phys_db->t1202.header.item_size = p_shdw_db->sec_d[sec_typ_1202].header.item_size;
			/* data */
			size = (PE_DDR_O18_1202T_FLT_NUM * PE_DDR_O18_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1202] = \
				p_shdw_db->top_h.sec_base[sec_typ_1202-1]+p_shdw_db->top_h.sec_size[sec_typ_1202-1];
			p_shdw_db->top_h.sec_size[sec_typ_1202] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1202] = p_shdw_db->top_h.sec_base[sec_typ_1202];
			p_phys_db->top_h.sec_size[sec_typ_1202] = p_shdw_db->top_h.sec_size[sec_typ_1202];
			p_shdw_db->sec_d[sec_typ_1202].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1202] + sizeof(PE_DDR_O18_HEADER_T);

			/* wr ddr */
			base_line_1212[0] = 0;
			base_line_1206[0] = 0;
			base_line_1204[0] = 0;
			base_line_1202[0] = 0;
			for (i=1; i<PE_DDR_O18_1212T_FLT_NUM; i++)
			{
				base_line_1212[i] = base_line_1212[i-1]+PE_DDR_O18_SCL_12T_FLT_SIZE;
			}
			for (i=1; i<PE_DDR_O18_1206T_FLT_NUM; i++)
			{
				base_line_1206[i] = base_line_1206[i-1]+PE_DDR_O18_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_O18_1204T_FLT_NUM; i++)
			{
				base_line_1204[i] = base_line_1204[i-1]+PE_DDR_O18_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_O18_1202T_FLT_NUM; i++)
			{
				base_line_1202[i] = base_line_1202[i-1]+PE_DDR_O18_SCL_12T_FLT_SIZE;;
			}
			for (i=0; i<PE_DDR_O18_SCL_12T_FLT_SIZE; i++)
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
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ_1212), p_shdw_db->top_h.sec_base[sec_typ_1212]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ_1206), p_shdw_db->top_h.sec_base[sec_typ_1206]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ_1204), p_shdw_db->top_h.sec_base[sec_typ_1204]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ_1202), p_shdw_db->top_h.sec_base[sec_typ_1202]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
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
static int PE_SHP_HW_O18_DownloadScl08tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 size = 0, i = 0, sec_typ_0804 = 0;
	UINT32 base_line_0804[PE_DDR_O18_0804T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O18_T *p_phys_db = gPE_DDR_DB_O18.phys.data;
	volatile UINT32 *p_t08_f_data = p_phys_db->t0804.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t08_f_data);
		if (PE_KDRV_VER_O18)
		{
			/*1. 8t full */
			sec_typ_0804 = PE_DDR_O18_SEC_SCL_0804T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0804].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0804].header.sec_type  = sec_typ_0804;
			p_shdw_db->sec_d[sec_typ_0804].header.item_num  = PE_DDR_O18_0804T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0804].header.item_size = PE_DDR_O18_SCL_08T_FLT_SIZE;
			p_phys_db->t0804.header.version   = p_shdw_db->sec_d[sec_typ_0804].header.version;
			p_phys_db->t0804.header.sec_type  = p_shdw_db->sec_d[sec_typ_0804].header.sec_type;
			p_phys_db->t0804.header.item_num  = p_shdw_db->sec_d[sec_typ_0804].header.item_num;
			p_phys_db->t0804.header.item_size = p_shdw_db->sec_d[sec_typ_0804].header.item_size;
			/* data */
			size = (PE_DDR_O18_0804T_FLT_NUM * PE_DDR_O18_SCL_08T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0804] = \
				p_shdw_db->top_h.sec_base[sec_typ_0804-1]+p_shdw_db->top_h.sec_size[sec_typ_0804-1];
			p_shdw_db->top_h.sec_size[sec_typ_0804] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0804] = p_shdw_db->top_h.sec_base[sec_typ_0804];
			p_phys_db->top_h.sec_size[sec_typ_0804] = p_shdw_db->top_h.sec_size[sec_typ_0804];
			p_shdw_db->sec_d[sec_typ_0804].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0804] + sizeof(PE_DDR_O18_HEADER_T);

			/* wr ddr */
			base_line_0804[0] = 0;
			for (i=1; i<PE_DDR_O18_0804T_FLT_NUM; i++)
			{
				base_line_0804[i] = base_line_0804[i-1]+PE_DDR_O18_SCL_08T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_O18_SCL_08T_FLT_SIZE; i++)
			{
				p_t08_f_data[base_line_0804[0]+i]  = scl_p256_0804t_flt_0008[i].data;
				p_t08_f_data[base_line_0804[1]+i]  = scl_p256_0804t_flt_0308[i].data;
				p_t08_f_data[base_line_0804[2]+i]  = scl_p256_0804t_flt_0910[i].data;
				p_t08_f_data[base_line_0804[3]+i]  = scl_p256_0804t_flt_1410[i].data;
				p_t08_f_data[base_line_0804[4]+i]  = scl_p256_0804t_flt_1510[i].data;
				p_t08_f_data[base_line_0804[5]+i]  = scl_p256_0804t_flt_0610[i].data;//dummy
				p_t08_f_data[base_line_0804[6]+i]  = scl_p256_0804t_flt_1510[i].data;//dummy
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ_0804), p_shdw_db->top_h.sec_base[sec_typ_0804]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
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
static int PE_SHP_HW_O18_DownloadScl04tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 size = 0, i = 0;
	UINT32 sec_typ_0404 = 0, sec_typ_0402 = 0;
	UINT32 base_line_0404[PE_DDR_O18_0404T_FLT_NUM];
	UINT32 base_line_0402[PE_DDR_O18_0402T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O18_T *p_phys_db = gPE_DDR_DB_O18.phys.data;
	volatile UINT32 *p_t0404_data = p_phys_db->t0404.data;
	volatile UINT32 *p_t0402_data = p_phys_db->t0402.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t0404_data);
		CHECK_KNULL(p_t0402_data);
		if (PE_KDRV_VER_O18)
		{
			/*1. 404t */
			sec_typ_0404 = PE_DDR_O18_SEC_SCL_0404T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0404].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0404].header.sec_type  = sec_typ_0404;
			p_shdw_db->sec_d[sec_typ_0404].header.item_num  = PE_DDR_O18_0404T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0404].header.item_size = PE_DDR_O18_SCL_04T_FLT_SIZE;
			p_phys_db->t0404.header.version   = p_shdw_db->sec_d[sec_typ_0404].header.version;
			p_phys_db->t0404.header.sec_type  = p_shdw_db->sec_d[sec_typ_0404].header.sec_type;
			p_phys_db->t0404.header.item_num  = p_shdw_db->sec_d[sec_typ_0404].header.item_num;
			p_phys_db->t0404.header.item_size = p_shdw_db->sec_d[sec_typ_0404].header.item_size;
			/* data */
			size = (PE_DDR_O18_0404T_FLT_NUM * PE_DDR_O18_SCL_04T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0404] = \
				p_shdw_db->top_h.sec_base[sec_typ_0404-1]+p_shdw_db->top_h.sec_size[sec_typ_0404-1];
			p_shdw_db->top_h.sec_size[sec_typ_0404] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0404] = p_shdw_db->top_h.sec_base[sec_typ_0404];
			p_phys_db->top_h.sec_size[sec_typ_0404] = p_shdw_db->top_h.sec_size[sec_typ_0404];
			p_shdw_db->sec_d[sec_typ_0404].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0404] + sizeof(PE_DDR_O18_HEADER_T);

			/*2. 402t  */
			sec_typ_0402 = PE_DDR_O18_SEC_SCL_0402T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0402].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0402].header.sec_type  = sec_typ_0402;
			p_shdw_db->sec_d[sec_typ_0402].header.item_num  = PE_DDR_O18_0402T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0402].header.item_size = PE_DDR_O18_SCL_04T_FLT_SIZE;
			p_phys_db->t0402.header.version   = p_shdw_db->sec_d[sec_typ_0402].header.version;
			p_phys_db->t0402.header.sec_type  = p_shdw_db->sec_d[sec_typ_0402].header.sec_type;
			p_phys_db->t0402.header.item_num  = p_shdw_db->sec_d[sec_typ_0402].header.item_num;
			p_phys_db->t0402.header.item_size = p_shdw_db->sec_d[sec_typ_0402].header.item_size;
			/* data */
			size = (PE_DDR_O18_0402T_FLT_NUM * PE_DDR_O18_SCL_04T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0402] = \
				p_shdw_db->top_h.sec_base[sec_typ_0402-1]+p_shdw_db->top_h.sec_size[sec_typ_0402-1];
			p_shdw_db->top_h.sec_size[sec_typ_0402] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0402] = p_shdw_db->top_h.sec_base[sec_typ_0402];
			p_phys_db->top_h.sec_size[sec_typ_0402] = p_shdw_db->top_h.sec_size[sec_typ_0402];
			p_shdw_db->sec_d[sec_typ_0402].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0402] + sizeof(PE_DDR_O18_HEADER_T);
			/* wr ddr */
			base_line_0404[0] = 0;
			for (i=1; i<PE_DDR_O18_0404T_FLT_NUM; i++)
			{
				base_line_0404[i] = base_line_0404[i-1]+PE_DDR_O18_SCL_04T_FLT_SIZE;
			}
			base_line_0402[0] = 0;
			for (i=1; i<PE_DDR_O18_0402T_FLT_NUM; i++)
			{
				base_line_0402[i] = base_line_0402[i-1]+PE_DDR_O18_SCL_04T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_O18_SCL_04T_FLT_SIZE; i++)
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
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ_0404), p_shdw_db->top_h.sec_base[sec_typ_0404]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ_0402), p_shdw_db->top_h.sec_base[sec_typ_0402]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * set Psp
 * - use input struct LX_PE_SHP_PSP_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_SetPspCtrl(LX_PE_SHP_PSP_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			LX_PE_SHP_PSP_T *pp = pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_HW_O18_DBG_PRINT("PSP ctrl: iir_en:%d, psp_en:%d, chrm_protect_en:%d\n"\
			"map_master_gain:%d,iir_gain:%d, cb\cr_offset_gain:%d,%d\n"\
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
				PE_SHP_PSP_O18_QWr02(reg_perspect_gain_ctrl_0, 	iir_en, GET_BITS(pp->iir_en,0,1),\
																iir_gain, GET_BITS(pp->iir_gain,0,8));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_00, 		reg_psp_en, 				GET_BITS(pp->psp_en,0,1),\
															reg_chroma_protection_en, 	GET_BITS(pp->chroma_protection_en,0,1));
				PE_SHP_PSP_O18_QWr01(reg_psp_ctrl_01, 		reg_psp_map_master_gain, 	GET_BITS(pp->map_master_gain,0,8));
																
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_02, 		reg_cb_offset_gain, GET_BITS(pp->cb_offset_gain,0,10),\
															reg_cr_offset_gain, GET_BITS(pp->cr_offset_gain,0,10));
				PE_SHP_PSP_O18_QWr04(reg_perspect_lut_x_3, 	reg_position_lut_x_0, GET_BITS(pp->position_lut_x[0],0,8),\
															reg_position_lut_x_1, GET_BITS(pp->position_lut_x[1],0,8),\
															reg_position_lut_x_2, GET_BITS(pp->position_lut_x[2],0,8),\
															reg_position_lut_x_3, GET_BITS(pp->position_lut_x[3],0,8));
				PE_SHP_PSP_O18_QWr04(reg_perspect_lut_x_2, 	reg_position_lut_x_4, GET_BITS(pp->position_lut_x[4],0,8),\
															reg_position_lut_x_5, GET_BITS(pp->position_lut_x[5],0,8),\
															reg_position_lut_x_6, GET_BITS(pp->position_lut_x[6],0,8),\
															reg_position_lut_x_7, GET_BITS(pp->position_lut_x[7],0,8));
				PE_SHP_PSP_O18_QWr04(reg_perspect_lut_x_1, 	reg_position_lut_x_8, GET_BITS(pp->position_lut_x[8],0,8),\
															reg_position_lut_x_9, GET_BITS(pp->position_lut_x[9],0,8),\
															reg_position_lut_x_10, GET_BITS(pp->position_lut_x[10],0,8),\
															reg_position_lut_x_11, GET_BITS(pp->position_lut_x[11],0,8));
				PE_SHP_PSP_O18_QWr04(reg_perspect_lut_x_0, 	reg_position_lut_x_12, GET_BITS(pp->position_lut_x[12],0,8),\
															reg_position_lut_x_13, GET_BITS(pp->position_lut_x[13],0,8),\
															reg_position_lut_x_14, GET_BITS(pp->position_lut_x[14],0,8),\
															reg_position_lut_x_15, GET_BITS(pp->position_lut_x[15],0,8));
				
				PE_SHP_PSP_O18_QWr04(reg_perspect_lut_y_3, 	reg_position_lut_y_0, GET_BITS(pp->position_lut_y[0],0,8),\
															reg_position_lut_y_1, GET_BITS(pp->position_lut_y[1],0,8),\
															reg_position_lut_y_2, GET_BITS(pp->position_lut_y[2],0,8),\
															reg_position_lut_y_3, GET_BITS(pp->position_lut_y[3],0,8));
				PE_SHP_PSP_O18_QWr04(reg_perspect_lut_y_2, 	reg_position_lut_y_4, GET_BITS(pp->position_lut_y[4],0,8),\
															reg_position_lut_y_5, GET_BITS(pp->position_lut_y[5],0,8),\
															reg_position_lut_y_6, GET_BITS(pp->position_lut_y[6],0,8),\
															reg_position_lut_y_7, GET_BITS(pp->position_lut_y[7],0,8));
				PE_SHP_PSP_O18_QWr04(reg_perspect_lut_y_1, 	reg_position_lut_y_8,  GET_BITS(pp->position_lut_y[8],0,8),\
															reg_position_lut_y_9,  GET_BITS(pp->position_lut_y[9],0,8),\
															reg_position_lut_y_10, GET_BITS(pp->position_lut_y[10],0,8),\
															reg_position_lut_y_11, GET_BITS(pp->position_lut_y[11],0,8));
				PE_SHP_PSP_O18_QWr04(reg_perspect_lut_y_0, 	reg_position_lut_y_12, GET_BITS(pp->position_lut_y[12],0,8),\
															reg_position_lut_y_13, GET_BITS(pp->position_lut_y[13],0,8),\
															reg_position_lut_y_14, GET_BITS(pp->position_lut_y[14],0,8),\
															reg_position_lut_y_15, GET_BITS(pp->position_lut_y[15],0,8));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_05, 	reg_psp_lut_x0, GET_BITS(pp->psp_lut_x[0],0,10),\
														reg_psp_lut_y0, GET_BITS(pp->psp_lut_y[0],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_06, 	reg_psp_lut_x1, GET_BITS(pp->psp_lut_x[1],0,10),\
														reg_psp_lut_y1, GET_BITS(pp->psp_lut_y[1],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_07, 	reg_psp_lut_x2, GET_BITS(pp->psp_lut_x[2],0,10),\
														reg_psp_lut_y2, GET_BITS(pp->psp_lut_y[2],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_08, 	reg_psp_lut_x3, GET_BITS(pp->psp_lut_x[3],0,10),\
														reg_psp_lut_y3, GET_BITS(pp->psp_lut_y[3],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_09, 	reg_psp_lut_x4, GET_BITS(pp->psp_lut_x[4],0,10),\
														reg_psp_lut_y4, GET_BITS(pp->psp_lut_y[4],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_10, 	reg_psp_lut_x5, GET_BITS(pp->psp_lut_x[5],0,10),\
														reg_psp_lut_y5, GET_BITS(pp->psp_lut_y[5],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_11, 	reg_psp_lut_x6, GET_BITS(pp->psp_lut_x[6],0,10),\
														reg_psp_lut_y6, GET_BITS(pp->psp_lut_y[6],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_12, 	reg_psp_lut_x7, GET_BITS(pp->psp_lut_x[7],0,10),\
														reg_psp_lut_y7, GET_BITS(pp->psp_lut_y[7],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_13, 	reg_psp_lut_x8,  GET_BITS(pp->psp_lut_x[8],0,10),\
														reg_psp_lut_y8,  GET_BITS(pp->psp_lut_y[8],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_14, 	reg_psp_lut_x9,  GET_BITS(pp->psp_lut_x[9],0,10),\
														reg_psp_lut_y9,  GET_BITS(pp->psp_lut_y[9],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_15, 	reg_psp_lut_x10, GET_BITS(pp->psp_lut_x[10],0,10),\
														reg_psp_lut_y10, GET_BITS(pp->psp_lut_y[10],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_16, 	reg_psp_lut_x11, GET_BITS(pp->psp_lut_x[11],0,10),\
														reg_psp_lut_y11, GET_BITS(pp->psp_lut_y[11],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_17, 	reg_psp_lut_x12, GET_BITS(pp->psp_lut_x[12],0,10),\
														reg_psp_lut_y12, GET_BITS(pp->psp_lut_y[12],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_18, 	reg_psp_lut_x13, GET_BITS(pp->psp_lut_x[13],0,10),\
														reg_psp_lut_y13, GET_BITS(pp->psp_lut_y[13],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_19, 	reg_psp_lut_x14, GET_BITS(pp->psp_lut_x[14],0,10),\
														reg_psp_lut_y14, GET_BITS(pp->psp_lut_y[14],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_20, 	reg_psp_lut_x15, GET_BITS(pp->psp_lut_x[15],0,10),\
														reg_psp_lut_y15, GET_BITS(pp->psp_lut_y[15],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_21, 	reg_psp_lut_x16, GET_BITS(pp->psp_lut_x[16],0,10),\
														reg_psp_lut_y16, GET_BITS(pp->psp_lut_y[16],0,10));
			}
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * get Psp
 * - use input struct LX_PE_SHP_PSP_T for O18X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O18_GetPspCtrl(LX_PE_SHP_PSP_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O18_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
			LX_PE_SHP_PSP_T *pp = pstParams;
			PE_CHECK_WINID(pp->win_id);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_O18_QRd02(reg_perspect_gain_ctrl_0, 	iir_en, 	pp->iir_en,\
																iir_gain, 	pp->iir_gain);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_00, 		reg_psp_en, 				pp->psp_en,\
															reg_chroma_protection_en, 	pp->chroma_protection_en);
				PE_SHP_PSP_O18_QRd01(reg_psp_ctrl_01, 		reg_psp_map_master_gain, 	pp->map_master_gain);
																
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_02, 		reg_cb_offset_gain, 	pp->cb_offset_gain,\
															reg_cr_offset_gain, 	pp->cr_offset_gain);
				PE_SHP_PSP_O18_QRd04(reg_perspect_lut_x_3, 	reg_position_lut_x_0, pp->position_lut_x[0],\
															reg_position_lut_x_1, pp->position_lut_x[1],\
															reg_position_lut_x_2, pp->position_lut_x[2],\
															reg_position_lut_x_3, pp->position_lut_x[3]);
				PE_SHP_PSP_O18_QRd04(reg_perspect_lut_x_2, 	reg_position_lut_x_4, pp->position_lut_x[4],\
															reg_position_lut_x_5, pp->position_lut_x[5],\
															reg_position_lut_x_6, pp->position_lut_x[6],\
															reg_position_lut_x_7, pp->position_lut_x[7]);
				PE_SHP_PSP_O18_QRd04(reg_perspect_lut_x_1, 	reg_position_lut_x_8,  pp->position_lut_x[8],\
															reg_position_lut_x_9,  pp->position_lut_x[9],\
															reg_position_lut_x_10, pp->position_lut_x[10],\
															reg_position_lut_x_11, pp->position_lut_x[11]);
				PE_SHP_PSP_O18_QRd04(reg_perspect_lut_x_0, 	reg_position_lut_x_12, pp->position_lut_x[12],\
															reg_position_lut_x_13, pp->position_lut_x[13],\
															reg_position_lut_x_14, pp->position_lut_x[14],\
															reg_position_lut_x_15, pp->position_lut_x[15]);
				
				PE_SHP_PSP_O18_QRd04(reg_perspect_lut_y_3, 	reg_position_lut_y_0, pp->position_lut_y[0],\
															reg_position_lut_y_1, pp->position_lut_y[1],\
															reg_position_lut_y_2, pp->position_lut_y[2],\
															reg_position_lut_y_3, pp->position_lut_y[3]);
				PE_SHP_PSP_O18_QRd04(reg_perspect_lut_y_2, 	reg_position_lut_y_4, pp->position_lut_y[4],\
															reg_position_lut_y_5, pp->position_lut_y[5],\
															reg_position_lut_y_6, pp->position_lut_y[6],\
															reg_position_lut_y_7, pp->position_lut_y[7]);
				PE_SHP_PSP_O18_QRd04(reg_perspect_lut_y_1, 	reg_position_lut_y_8,  pp->position_lut_y[8],\
															reg_position_lut_y_9,  pp->position_lut_y[9],\
															reg_position_lut_y_10, pp->position_lut_y[10],\
															reg_position_lut_y_11, pp->position_lut_y[11]);
				PE_SHP_PSP_O18_QRd04(reg_perspect_lut_y_0, 	reg_position_lut_y_12, pp->position_lut_y[12],\
															reg_position_lut_y_13, pp->position_lut_y[13],\
															reg_position_lut_y_14, pp->position_lut_y[14],\
															reg_position_lut_y_15, pp->position_lut_y[15]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_05, 	reg_psp_lut_x0, pp->psp_lut_x[0],\
														reg_psp_lut_y0, pp->psp_lut_y[0]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_06, 	reg_psp_lut_x1, pp->psp_lut_x[1],\
														reg_psp_lut_y1, pp->psp_lut_y[1]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_07, 	reg_psp_lut_x2, pp->psp_lut_x[2],\
														reg_psp_lut_y2, pp->psp_lut_y[2]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_08, 	reg_psp_lut_x3, pp->psp_lut_x[3],\
														reg_psp_lut_y3, pp->psp_lut_y[3]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_09, 	reg_psp_lut_x4, pp->psp_lut_x[4],\
														reg_psp_lut_y4, pp->psp_lut_y[4]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_10, 	reg_psp_lut_x5, pp->psp_lut_x[5],\
														reg_psp_lut_y5, pp->psp_lut_y[5]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_11, 	reg_psp_lut_x6, pp->psp_lut_x[6],\
														reg_psp_lut_y6, pp->psp_lut_y[6]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_12, 	reg_psp_lut_x7, pp->psp_lut_x[7],\
														reg_psp_lut_y7, pp->psp_lut_y[7]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_13, 	reg_psp_lut_x8, pp->psp_lut_x[8],\
														reg_psp_lut_y8, pp->psp_lut_y[8]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_14, 	reg_psp_lut_x9, pp->psp_lut_x[9],\
														reg_psp_lut_y9, pp->psp_lut_y[9]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_15, 	reg_psp_lut_x10, pp->psp_lut_x[10],\
														reg_psp_lut_y10, pp->psp_lut_y[10]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_16, 	reg_psp_lut_x11, pp->psp_lut_x[11],\
														reg_psp_lut_y11, pp->psp_lut_y[11]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_17, 	reg_psp_lut_x12, pp->psp_lut_x[12],\
														reg_psp_lut_y12, pp->psp_lut_y[12]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_18, 	reg_psp_lut_x13, pp->psp_lut_x[13],\
														reg_psp_lut_y13, pp->psp_lut_y[13]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_19, 	reg_psp_lut_x14, pp->psp_lut_x[14],\
														reg_psp_lut_y14, pp->psp_lut_y[14]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_20, 	reg_psp_lut_x15, pp->psp_lut_x[15],\
														reg_psp_lut_y15, pp->psp_lut_y[15]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_21, 	reg_psp_lut_x16, pp->psp_lut_x[16],\
														reg_psp_lut_y16, pp->psp_lut_y[16]);
				PE_SHP_HW_O18_DBG_PRINT("PSP ctrl: iir_en:%d, psp_en:%d, chrm_protect_en:%d\n"\
				"map_master_gain:%d,iir_gain:%d, cb\cr_offset_gain:%d,%d\n"\
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
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * set obc control
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_SetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
 			LX_PE_VSD_OBC_CONT_T *pp=(LX_PE_VSD_OBC_CONT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o18_trace)
			{
				PE_SHP_HW_O18_DBG_PRINT("[wid:%d] set: n"\
				"bOBC_enable:0x%02X\n"\
				"fg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"fg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"bg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"bg_gain_y0,y1: 0x%02X,0x%02X\n",\
				pp->win_id,\
				pp->bOBC_enable, \
				pp->fg_gain_x0,pp->fg_gain_x1,pp->fg_gain_y0,pp->fg_gain_y1, \
				pp->bg_gain_x0,pp->bg_gain_x1,pp->bg_gain_y0,pp->bg_gain_y1);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_HW_O18_PSP_WR01(reg_psp_ctrl_00,	reg_psp_en,  	 GET_BITS(pp->bOBC_enable,0,1));
				PE_SHP_HW_O18_PSP_WR04(reg_psp_ctrl_21, reg_psp_gain_lut0_y0, GET_BITS(pp->fg_gain_y0,0,8),\
														reg_psp_gain_lut0_x0, GET_BITS(pp->fg_gain_x0,0,8),\
														reg_psp_gain_lut0_y1, GET_BITS(pp->fg_gain_y1,0,8),\
														reg_psp_gain_lut0_x1, GET_BITS(pp->fg_gain_x1,0,8));
				PE_SHP_HW_O18_PSP_WR04(reg_psp_ctrl_22, reg_psp_gain_lut0_y0, GET_BITS(pp->bg_gain_y0,0,8),\
														reg_psp_gain_lut0_x0, GET_BITS(pp->bg_gain_x0,0,8),\
														reg_psp_gain_lut0_y1, GET_BITS(pp->bg_gain_y1,0,8),\
														reg_psp_gain_lut0_x1, GET_BITS(pp->bg_gain_x1,0,8));
			}
 		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * get obc control
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_GetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
 			LX_PE_VSD_OBC_CONT_T *pp=(LX_PE_VSD_OBC_CONT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_O18_QRd01(reg_psp_ctrl_00,	reg_psp_en,  	 pp->bOBC_enable);
				PE_SHP_PSP_O18_QRd04(reg_psp_ctrl_21, 	reg_psp_gain_lut0_y0, pp->fg_gain_y0,\
														reg_psp_gain_lut0_x0, pp->fg_gain_x0,\
														reg_psp_gain_lut0_y1, pp->fg_gain_y1,\
														reg_psp_gain_lut0_x1, pp->fg_gain_x1);
				PE_SHP_PSP_O18_QRd04(reg_psp_ctrl_22, 	reg_psp_gain_lut0_y0, pp->bg_gain_y0,\
														reg_psp_gain_lut0_x0, pp->bg_gain_x0,\
														reg_psp_gain_lut0_y1, pp->bg_gain_y1,\
														reg_psp_gain_lut0_x1, pp->bg_gain_x1);
			}
			if (_g_shp_hw_o18_trace)
			{
				PE_SHP_HW_O18_DBG_PRINT("[wid:%d] get: n"\
				"bOBC_enable:0x%02X\n"\
				"fg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"fg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"bg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"bg_gain_y0,y1: 0x%02X,0x%02X\n",\
				pp->win_id,\
				pp->bOBC_enable, \
				pp->fg_gain_x0,pp->fg_gain_x1,pp->fg_gain_y0,pp->fg_gain_y1, \
				pp->bg_gain_x0,pp->bg_gain_x1,pp->bg_gain_y0,pp->bg_gain_y1);
			}
 		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * set obc lut
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_SetObcLUT(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
 			LX_PE_VSD_OBC_LUT_T *pp=(LX_PE_VSD_OBC_LUT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o18_trace)
			{
				PE_SHP_HW_O18_DBG_PRINT("[wid:%d] set: n"\
				"object_fg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"object_fg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"object_bg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"object_bg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id,\
				pp->object_fg_x[0],pp->object_fg_x[1],pp->object_fg_x[2],pp->object_fg_x[3], \
				pp->object_fg_x[4],pp->object_fg_x[5],pp->object_fg_x[6],pp->object_fg_x[7], \
				pp->object_fg_y[0],pp->object_fg_y[1],pp->object_fg_y[2],pp->object_fg_y[3], \
				pp->object_fg_y[4],pp->object_fg_y[5],pp->object_fg_y[6],pp->object_fg_y[7], \
				pp->object_bg_x[0],pp->object_bg_x[1],pp->object_bg_x[2],pp->object_bg_x[3], \
				pp->object_bg_x[4],pp->object_bg_x[5],pp->object_bg_x[6],pp->object_bg_x[7], \
				pp->object_bg_y[0],pp->object_bg_y[1],pp->object_bg_y[2],pp->object_bg_y[3], \
				pp->object_bg_y[4],pp->object_bg_y[5],pp->object_bg_y[6],pp->object_bg_y[7]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_05, 	reg_psp_lut_x0,  GET_BITS(pp->object_fg_x[0],0,10),\
														reg_psp_lut_y0,  GET_BITS(pp->object_fg_y[0],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_06, 	reg_psp_lut0_x1, GET_BITS(pp->object_fg_x[1],0,10),\
														reg_psp_lut0_y1, GET_BITS(pp->object_fg_y[1],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_07, 	reg_psp_lut0_x2, GET_BITS(pp->object_fg_x[2],0,10),\
														reg_psp_lut0_y2, GET_BITS(pp->object_fg_y[2],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_08, 	reg_psp_lut0_x3, GET_BITS(pp->object_fg_x[3],0,10),\
														reg_psp_lut0_y3, GET_BITS(pp->object_fg_y[3],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_09, 	reg_psp_lut0_x4, GET_BITS(pp->object_fg_x[4],0,10),\
														reg_psp_lut0_y4, GET_BITS(pp->object_fg_y[4],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_10, 	reg_psp_lut0_x5, GET_BITS(pp->object_fg_x[5],0,10),\
														reg_psp_lut0_y5, GET_BITS(pp->object_fg_y[5],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_11, 	reg_psp_lut0_x6, GET_BITS(pp->object_fg_x[6],0,10),\
														reg_psp_lut0_y6, GET_BITS(pp->object_fg_y[6],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_12, 	reg_psp_lut0_x7, GET_BITS(pp->object_fg_x[7],0,10),\
														reg_psp_lut0_y7, GET_BITS(pp->object_fg_y[7],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_13, 	reg_psp_lut1_x0, GET_BITS(pp->object_bg_x[0],0,10),\
														reg_psp_lut1_y0, GET_BITS(pp->object_bg_y[0],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_14, 	reg_psp_lut1_x1, GET_BITS(pp->object_bg_x[1],0,10),\
														reg_psp_lut1_y1, GET_BITS(pp->object_bg_y[1],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_15, 	reg_psp_lut1_x2, GET_BITS(pp->object_bg_x[2],0,10),\
														reg_psp_lut1_y2, GET_BITS(pp->object_bg_y[2],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_16, 	reg_psp_lut1_x3, GET_BITS(pp->object_bg_x[3],0,10),\
														reg_psp_lut1_y3, GET_BITS(pp->object_bg_y[3],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_17, 	reg_psp_lut1_x4, GET_BITS(pp->object_bg_x[4],0,10),\
														reg_psp_lut1_y4, GET_BITS(pp->object_bg_y[4],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_18, 	reg_psp_lut1_x5, GET_BITS(pp->object_bg_x[5],0,10),\
														reg_psp_lut1_y5, GET_BITS(pp->object_bg_y[5],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_19, 	reg_psp_lut1_x6, GET_BITS(pp->object_bg_x[6],0,10),\
														reg_psp_lut1_y6, GET_BITS(pp->object_bg_y[6],0,10));
				PE_SHP_PSP_O18_QWr02(reg_psp_ctrl_20, 	reg_psp_lut1_x7, GET_BITS(pp->object_bg_x[7],0,10),\
														reg_psp_lut1_y7, GET_BITS(pp->object_bg_y[7],0,10));
			}
 		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * get obc lut
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_GetObcLUT(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O18)
		{
 			LX_PE_VSD_OBC_LUT_T *pp=(LX_PE_VSD_OBC_LUT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_05, 	reg_psp_lut_x0,  pp->object_fg_x[0],\
														reg_psp_lut_y0,  pp->object_fg_y[0]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_06, 	reg_psp_lut0_x1, pp->object_fg_x[1],\
														reg_psp_lut0_y1, pp->object_fg_y[1]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_07, 	reg_psp_lut0_x2, pp->object_fg_x[2],\
														reg_psp_lut0_y2, pp->object_fg_y[2]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_08, 	reg_psp_lut0_x3, pp->object_fg_x[3],\
														reg_psp_lut0_y3, pp->object_fg_y[3]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_09, 	reg_psp_lut0_x4, pp->object_fg_x[4],\
														reg_psp_lut0_y4, pp->object_fg_y[4]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_10, 	reg_psp_lut0_x5, pp->object_fg_x[5],\
														reg_psp_lut0_y5, pp->object_fg_y[5]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_11, 	reg_psp_lut0_x6, pp->object_fg_x[6],\
														reg_psp_lut0_y6, pp->object_fg_y[6]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_12, 	reg_psp_lut0_x7, pp->object_fg_x[7],\
														reg_psp_lut0_y7, pp->object_fg_y[7]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_13, 	reg_psp_lut1_x0, pp->object_bg_x[0],\
														reg_psp_lut1_y0, pp->object_bg_y[0]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_14, 	reg_psp_lut1_x1, pp->object_bg_x[1],\
														reg_psp_lut1_y1, pp->object_bg_y[1]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_15, 	reg_psp_lut1_x2, pp->object_bg_x[2],\
														reg_psp_lut1_y2, pp->object_bg_y[2]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_16, 	reg_psp_lut1_x3, pp->object_bg_x[3],\
														reg_psp_lut1_y3, pp->object_bg_y[3]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_17, 	reg_psp_lut1_x4, pp->object_bg_x[4],\
														reg_psp_lut1_y4, pp->object_bg_y[4]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_18, 	reg_psp_lut1_x5, pp->object_bg_x[5],\
														reg_psp_lut1_y5, pp->object_bg_y[5]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_19, 	reg_psp_lut1_x6, pp->object_bg_x[6],\
														reg_psp_lut1_y6, pp->object_bg_y[6]);
				PE_SHP_PSP_O18_QRd02(reg_psp_ctrl_20, 	reg_psp_lut1_x7, pp->object_bg_x[7],\
														reg_psp_lut1_y7, pp->object_bg_y[7]);
			}
			if (_g_shp_hw_o18_trace)
			{
				PE_SHP_HW_O18_DBG_PRINT("[wid:%d] set: n"\
				"object_fg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_fg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_bg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"object_bg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n",\
				pp->win_id,\
				pp->object_fg_x[0],pp->object_fg_x[1],pp->object_fg_x[2],pp->object_fg_x[3], \
				pp->object_fg_x[4],pp->object_fg_x[5],pp->object_fg_x[6],pp->object_fg_x[7], \
				pp->object_fg_y[0],pp->object_fg_y[1],pp->object_fg_y[2],pp->object_fg_y[3], \
				pp->object_fg_y[4],pp->object_fg_y[5],pp->object_fg_y[6],pp->object_fg_y[7], \
				pp->object_bg_x[0],pp->object_bg_x[1],pp->object_bg_x[2],pp->object_bg_x[3], \
				pp->object_bg_x[4],pp->object_bg_x[5],pp->object_bg_x[6],pp->object_bg_x[7], \
				pp->object_bg_y[0],pp->object_bg_y[1],pp->object_bg_y[2],pp->object_bg_y[3], \
				pp->object_bg_y[4],pp->object_bg_y[5],pp->object_bg_y[6],pp->object_bg_y[7]);
			}
 		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * download shp 2k ui sqm db init
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_DownloadShp2KSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O18_T *p_phys_db = gPE_DDR_DB_O18.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_ui_sqm_2k.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O18)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O18_SEC_SHP_UI_SQM_2K;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O18_SHP_UI_SQM_2K_SIZE;
			p_phys_db->shp_ui_sqm_2k.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_ui_sqm_2k.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_ui_sqm_2k.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_ui_sqm_2k.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O18_SHP_UI_SQM_2K_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O18_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O18_SHP_UI_SQM_2K_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_2k_cmn_init_o18[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * download sre 2k shp sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_HW_O18_DownloadShp2KSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_O18_SHP_UI_SQM_2K_T *p_phys_shp_sqm_db = NULL;
	volatile UINT32 *p_db_data = NULL;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O18)
		{
			sec_typ = PE_DDR_O18_SEC_SHP_UI_SQM_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O18_SHP_UI_SQM_2K_T);
			p_phys_shp_sqm_db  = (volatile PE_DDR_O18_SHP_UI_SQM_2K_T *)vmap_phys(base, size);
			CHECK_KNULL(p_phys_shp_sqm_db);
			p_db_data = p_phys_shp_sqm_db->data;
			pp = (LX_PE_SHP_SR2K_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm___val;
			base = 2;
			for (i=0; i<PE_DDR_O18_SHP_UI_SQM_2K_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_ui_sqm_2k[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_SHP_HW_O18_DBG_PRINT("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * download shp 2k cmn sqm db init
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_DownloadShp2KSqmDetailInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O18_T *p_phys_db = gPE_DDR_DB_O18.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_sqmcmn__2k.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O18)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O18_SEC_SHP_SQM_CMN_2K;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O18_SHP_SQM_CMN_2K_SIZE;
			p_phys_db->shp_sqmcmn__2k.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_sqmcmn__2k.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_sqmcmn__2k.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_sqmcmn__2k.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O18_SHP_SQM_CMN_2K_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O18_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O18_SHP_SQM_CMN_2K_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_2k_dtl_init_o18[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}


/**
 * download sre 2k shp sqm detail db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_HW_O18_DownloadShp2KSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM1_DETAIL_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_O18_SHP_SQM_CMN_2K_T *p_phys_shp_sqm_db = NULL;
	volatile UINT32 *p_db_data = NULL;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O18)
		{
			sec_typ = PE_DDR_O18_SEC_SHP_SQM_CMN_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O18_SHP_SQM_CMN_2K_T);
			p_phys_shp_sqm_db  = (volatile PE_DDR_O18_SHP_SQM_CMN_2K_T *)vmap_phys(base, size);
			CHECK_KNULL(p_phys_shp_sqm_db);
			p_db_data = p_phys_shp_sqm_db->data;
			pp = (LX_PE_SHP_SR2K_SQM1_DETAIL_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm____val;
			base = 2;
			for (i=0; i<PE_DDR_O18_SHP_SQM_CMN_2K_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_sqm_cmn_2k[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_SHP_HW_O18_DBG_PRINT("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * download shp vsd ui sqm db init
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_DownloadShpSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O18_T *p_phys_db = gPE_DDR_DB_O18.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_ui_sqm_vsd.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O18)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O18_SEC_SHP_UI_SQM_VSD;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O18_SHP_UI_SQM_VSD_SIZE;
			p_phys_db->shp_ui_sqm_vsd.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_ui_sqm_vsd.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_ui_sqm_vsd.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_ui_sqm_vsd.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O18_SHP_UI_SQM_VSD_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O18_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O18_SHP_UI_SQM_VSD_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_vsd_cmn_init_o18[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * download  shp sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_HW_O18_DownloadShpSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_O18_SHP_UI_SQM_VSD_T *p_phys_shp_sqm_db = NULL;
	volatile UINT32 *p_db_data = NULL;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O18)
		{
			sec_typ = PE_DDR_O18_SEC_SHP_UI_SQM_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O18_SHP_UI_SQM_VSD_T);
			p_phys_shp_sqm_db  = (volatile PE_DDR_O18_SHP_UI_SQM_VSD_T *)vmap_phys(base, size);
			CHECK_KNULL(p_phys_shp_sqm_db);
			p_db_data = p_phys_shp_sqm_db->data;
			pp = (LX_PE_SHP_SR2K_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm____val;
			base = 2;
			for (i=0; i<PE_DDR_O18_SHP_UI_SQM_VSD_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_ui_sqm_vsd[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_SHP_HW_O18_DBG_PRINT("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}

/**
 * download shp vsd ui sqm db init
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O18_DownloadShpSqmDetailInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O18_T *p_phys_db = gPE_DDR_DB_O18.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_sqmcmn__vsd.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O18)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O18_SEC_SHP_SQM_CMN_VSD;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O18_SHP_SQM_CMN_VSD_SIZE;
			p_phys_db->shp_sqmcmn__vsd.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_sqmcmn__vsd.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_sqmcmn__vsd.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_sqmcmn__vsd.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O18_SHP_SQM_CMN_VSD_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O18_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O18_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O18_SHP_SQM_CMN_VSD_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_vsd_dtl_init_o18[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}
/**
 * download shp sqm detail db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_HW_O18_DownloadShpSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O18_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM1_DETAIL_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O18_T *p_shdw_db = gPE_DDR_DB_O18.shdw.data;
	volatile PE_DDR_O18_SHP_SQM_CMN_VSD_T *p_phys_shp_sqm_db = NULL;
	volatile UINT32 *p_db_data = NULL;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_O18)
		{
			sec_typ = PE_DDR_O18_SEC_SHP_SQM_CMN_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O18_SHP_SQM_CMN_VSD_T);
			p_phys_shp_sqm_db  = (volatile PE_DDR_O18_SHP_SQM_CMN_VSD_T *)vmap_phys(base, size);
			CHECK_KNULL(p_phys_shp_sqm_db);
			p_db_data = p_phys_shp_sqm_db->data;
			pp = (LX_PE_SHP_RE_SQM1_DETAIL_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm_____val;
			base = 2;
			for (i=0; i<PE_DDR_O18_SHP_SQM_CMN_VSD_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_sqm_cmn_vsd[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_SHP_HW_O18_DBG_PRINT("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O18_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_SHP_HW_O18_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_O18_BRINGUP*/
	return ret;
}


