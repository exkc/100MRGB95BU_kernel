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

/** @file pe_nrd_hw_m17c0.c
 *
 *  driver for picture enhance noise reduction functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.12
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
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_hw_m17c0.h"
#include "pe_reg_m17.h"
#include "pe_fwi_m17c0.h"
#include "pe_cmn_hw_m17c0.h"
#include "pe_nrd_hw_m17c0.h"
#include "pe_hst_hw_m17c0.h"

#include "pe_tnr_hw_param_m17c0.h"
#include "pe_dnr_hw_param_m17c0.h"
#include "pe_ifc_hw_param_m17c0.h"
#include "cvd_module.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 352,288 = 704/2,576/2 */
#define PE_NRD_HW_M17C0_H_MIN                (352)
#define PE_NRD_HW_M17C0_V_MIN                (288)
#define PE_NRD_HW_M17C0_TNR_SRC_H_HD_BASE    (800)
#define PE_NRD_HW_M17C0_TNR_SRC_V_3K_BASE    (1600)
#define PE_NRD_HW_M17C0_C_FMT_444            (0x6)
#define PE_NRD_HW_M17C0_C_FMT_422            (0x5)
#define PE_NRD_HW_M17C0_C_FMT_420            (0x4)

#define PE_NRD_HW_M17C0_SDR					(0)
#define PE_NRD_HW_M17C0_HDR2K					(1)
#define PE_NRD_HW_M17C0_HDR4K					(2)


/* use pre processing for setting tnr reg table */
#define PE_NRD_HW_M17C0_USE_PRE_PROC_TNR_REG_TABLE

#define PE_NRD_HW_M17C0_USE_SIZE_FR_FW

#define PE_NRD_HW_M17C0_CVD_PAT_DETECT
/*170823 inkyung.park, temporally block TNR_MAE for chage DB */
#define PE_NRD_HW_M17C0_TNR_MAE_CHANGE

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_HW_M17C0_ERROR		PE_PRINT_ERROR

#define PE_NRD_HW_M17C0_DBG_PRINT(fmt,args...)	\
	if(_g_nrd_hw_m17c0_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

#define PE_NRD_HW_M17C0_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_NRD_HW_M17C0_ERROR(fmt,##args);_action;}}

#define PE_NRD_HW_M17C0_DBG_PRINT_TNR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M17C0_TNR_FMT_TO_STR(_pre), \
			PE_NRD_HW_M17C0_TNR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_NRD_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
/* tnr lut (tnl) */
#define PE_NRD_HW_M17C0_DBG_PRINT_TNL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M17C0_TNL_FMT_TO_STR(_pre), \
			PE_NRD_HW_M17C0_TNL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_NRD_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_NRD_HW_M17C0_DBG_PRINT_DNR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M17C0_DNR_FMT_TO_STR(_pre), \
			PE_NRD_HW_M17C0_DNR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_NRD_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_NRD_HW_M17C0_DBG_PRINT_IFC_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		sprintf(_str_buf, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M17C0_IFC_FMT_TO_STR(_pre), \
			PE_NRD_HW_M17C0_IFC_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_NRD_HW_M17C0_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_M17C0_SetTraceDataBuf(_str_buf);\
		}\
	}
#define PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f, _d)	\
	{	_g_pe_tnr_hw_param_data_m17c0.nd1_user.data->_r._f = (_d);\
		_g_pe_tnr_hw_param_data_m17c0.nd1_mask.data->_r._f = 0;}

#define PE_NRD_HW_M17C0_TNR1_WR01(_r, _f1, _d1)	\
	{	PE_ND0_M17C0_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_M17C0_TNR1_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND0_M17C0_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_M17C0_TNR1_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND0_M17C0_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_M17C0_TNR1_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND0_M17C0_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_M17C0_TNR1_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND0_M17C0_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(_r, _f5, _d5);}

/* tnr lut (tnl) */
#define PE_NRD_HW_M17C0_TNL_SET_USER32(_r, _d)	\
	{	*((UINT32 *)&(_g_pe_tnl_hw_param_data_m17c0.reg_user.data->_r)) = (_d);\
		*((UINT32 *)&(_g_pe_tnl_hw_param_data_m17c0.reg_mask.data->_r)) = 0;}

#define PE_NRD_HW_M17C0_TNL_WR32(_num, _d1)	\
	{	PE_ND0_M17C0_QWr(tnr_main_lut_01, _d1);\
		PE_NRD_HW_M17C0_TNL_SET_USER32(tnr_lut_##_num, _d1);}
/* dnr */
#define PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f, _d)	\
	{	_g_pe_dnr_hw_param_data_m17c0.reg_user.data->_r._f = (_d);\
		_g_pe_dnr_hw_param_data_m17c0.reg_mask.data->_r._f = 0;}

#define PE_NRD_HW_M17C0_DNR_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_M17C0_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_M17C0_DNR_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_M17C0_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_M17C0_DNR_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_M17C0_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_M17C0_DNR_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_M17C0_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_M17C0_DNR_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_M17C0_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M17C0_DNR_SET_USER(_r, _f5, _d5);}

#define PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f, _d)	\
	{	_g_pe_ifc_hw_param_data_m17c0.reg_user.data->_r._f = (_d);\
		_g_pe_ifc_hw_param_data_m17c0.reg_mask.data->_r._f = 0;}

#define PE_NRD_HW_M17C0_IFC_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_M17C0_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_M17C0_IFC_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_M17C0_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_M17C0_IFC_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_M17C0_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_M17C0_IFC_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_M17C0_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_M17C0_IFC_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_M17C0_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M17C0_IFC_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_M17C0_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_NRD_HW_M17C0_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_M17C0_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_M17C0_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_M17C0_CHECK_CODE(!_data, ret=RET_ERROR;break, \
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
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_M16_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_NRD_HW_M17C0_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#ifdef PE_NRD_HW_M17C0_USE_PRE_PROC_TNR_REG_TABLE
#define PE_NRD_HW_M17C0_PRE_PROC_TNR_REG_TABLE(__base)	\
	do{\
		UINT32 _rd_data[3];\
		PE_ND0_M17C0_RdFL(tnr_ctrl_00);\
		PE_ND0_M17C0_RdFL(tnr_ctrl_02);\
		PE_ND0_M17C0_Rd01(tnr_ctrl_00, reg_tnr_en, _rd_data[0]);\
		PE_ND0_M17C0_Rd01(tnr_ctrl_00, reg_tnr_half_rate, _rd_data[1]);\
		PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_en,  _rd_data[2]);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_00, reg_tnr_en, _rd_data[0]);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_00, reg_tnr_half_rate, _rd_data[1]);\
		PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_en,  _rd_data[2]);\
	}while(0)
#else
#define PE_NRD_HW_M17C0_PRE_PROC_TNR_REG_TABLE(__base)
#endif

/* tnr */
#define PE_NRD_HW_M17C0_TNR_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnr_hw_param_data_m17c0.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnr_hw_param_data_m17c0.nd1_user.addr;\
		UINT32 *_mask = _g_pe_tnr_hw_param_data_m17c0.nd1_mask.addr;\
		UINT32 *_data = _g_pe_tnr_hw_param_data_m17c0.nd1_data.addr;\
		PE_NRD_HW_M17C0_CHECK_CODE(\
		(sizeof(PE_TNR_HW_PARAM_REG_M17C0_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]tnr tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_M17C0_PRE_PROC_TNR_REG_TABLE(__base);\
		PE_NRD_HW_M17C0_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* tnr lut (tnl) */
#define PE_NRD_HW_M17C0_TNL_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnl_hw_param_data_m17c0.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnl_hw_param_data_m17c0.reg_user.addr;\
		UINT32 *_mask = _g_pe_tnl_hw_param_data_m17c0.reg_mask.addr;\
		UINT32 *_data = _g_pe_tnl_hw_param_data_m17c0.reg_data.addr;\
		PE_NRD_HW_M17C0_CHECK_CODE(\
		(sizeof(PE_TNL_HW_PARAM_REG_M17C0_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]tnl tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_M17C0_SET_REG_TABLE(__tbl, __base);\
	}while (0)

	/* dnr */
#define PE_NRD_HW_M17C0_DNR_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.addr;\
		UINT32 *_user = _g_pe_dnr_hw_param_data_m17c0.reg_user.addr;\
		UINT32 *_mask = _g_pe_dnr_hw_param_data_m17c0.reg_mask.addr;\
		UINT32 *_data = _g_pe_dnr_hw_param_data_m17c0.reg_data.addr;\
		PE_NRD_HW_M17C0_CHECK_CODE(\
		(sizeof(PE_DNR_HW_PARAM_REG_M17C0_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]dnr dnr size violation.\n", __F__, __L__);\
		PE_NRD_HW_M17C0_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* ifc */
#define PE_NRD_HW_M17C0_IFC_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_ifc_hw_param_data_m17c0.reg_dflt.addr;\
		UINT32 *_user = _g_pe_ifc_hw_param_data_m17c0.reg_user.addr;\
		UINT32 *_mask = _g_pe_ifc_hw_param_data_m17c0.reg_mask.addr;\
		UINT32 *_data = _g_pe_ifc_hw_param_data_m17c0.reg_data.addr;\
		PE_NRD_HW_M17C0_CHECK_CODE(\
		(sizeof(PE_IFC_HW_PARAM_REG_M17C0_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]ifc tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_M17C0_SET_REG_TABLE(__tbl, __base);\
	}while (0)


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
static PE_NRD_HW_M17C0_TNR_FMT PE_NRD_HW_M17C0_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_M17C0_TNL_FMT PE_NRD_HW_M17C0_ConvDispInfoToTnlFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_M17C0_IFC_FMT PE_NRD_HW_M17C0_ConvDispInfoToIfcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_M17C0_DNR_FMT PE_NRD_HW_M17C0_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
//static int PE_NRD_HW_M17C0_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);

static int PE_NRD_HW_M17C0_CreateDataTable(UINT32 index);
static int PE_NRD_HW_M17C0_SetTnrDefault(PE_NRD_HW_M17C0_TNR_FMT cur0_tnr_fmt);
static int PE_NRD_HW_M17C0_SetTnlDefault(PE_NRD_HW_M17C0_TNL_FMT cur0_tnl_fmt);
static int PE_NRD_HW_M17C0_SetDnrDefault(PE_NRD_HW_M17C0_DNR_FMT cur0_dnr_fmt);
static int PE_NRD_HW_M17C0_SetIfcDefault(PE_NRD_HW_M17C0_IFC_FMT cur0_ifc_fmt);

static int PE_NRD_HW_M17C0_SetTnrLbMode(PE_TSK_M17C0_CFG_T *pCfg);
static int PE_NRD_HW_M17C0_SetTnrSmoothMode(PE_TSK_M17C0_CFG_T *pCfg);
#if 0
static int PE_NRD_HW_M17C0_SetTnrScMode(PE_TSK_M17C0_CFG_T *pCfg);
static int PE_NRD_HW_M17C0_SetDnrMaxMode(PE_TSK_M17C0_CFG_T *pCfg);
static int PE_NRD_HW_M17C0_SetBnrMode(PE_TSK_M17C0_CFG_T *pCfg);
#endif
static int PE_NRD_HW_M17C0_DownloadTnrUserDb(void *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT8 _g_nrd_hw_m17c0_trace=0x0;	//default should be off.
static PE_NRD_HW_M17C0_SETTINGS_T _g_pe_nrd_hw_m17c0_info;
#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
static PE_TNR_HW_PARAM_DATA_M17C0_T _g_pe_tnr_hw_param_data_m17c0 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_TNL_HW_PARAM_DATA_M17C0_T _g_pe_tnl_hw_param_data_m17c0 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_DNR_HW_PARAM_DATA_M17C0_T _g_pe_dnr_hw_param_data_m17c0 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_IFC_HW_PARAM_DATA_M17C0_T _g_pe_ifc_hw_param_data_m17c0 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif
//static UINT32 _g_pre_sc_en = 0xff;
#ifdef PE_NRD_HW_M17C0_CVD_PAT_DETECT
static  UINT32 _g_pre_pattern_fw = 0xff;
static PE_M17C0_DC_BNR_CTRL_0_T _g_pre_data0 ={0};
static PE_M17C0_DC_BNR_CTRL_1_T _g_pre_data1 ={0};
static PE_M17C0_DC_BNR_CTRL_2_T _g_pre_data2 ={0};
static PE_M17C0_DC_BNR_CTRL_7_T _g_pre_data7 ={0};
static UINT32 _g_pre_data_tnr_sad_cut=0xff;
static UINT32 _g_pre_data_tnr_7=0xff;
static UINT32 _g_pre_data_tnr_2=0xff;
#endif

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
/**
 * init nrd
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M17C0_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		_g_pe_nrd_hw_m17c0_info.use_manual_sc = 1;
		_g_pe_nrd_hw_m17c0_info.tnr_sc_en_user = 0;
		_g_pe_nrd_hw_m17c0_info.tnr_sc_en_mask = 0;
		_g_pe_nrd_hw_m17c0_info.tnr_pv_smooth_en_user = 0;
		_g_pe_nrd_hw_m17c0_info.tnr_pv_smooth_en_mask = 0;
		_g_pe_nrd_hw_m17c0_info.dnr_max_en0_user = 0;
		_g_pe_nrd_hw_m17c0_info.dnr_max_en0_mask = 0;
		_g_pe_nrd_hw_m17c0_info.bnr_ac_h_en0_user = 0;
		_g_pe_nrd_hw_m17c0_info.bnr_ac_h_en0_mask = 0;
		_g_pe_nrd_hw_m17c0_info.cur_tnr_auto_enable = 0;
		_g_pe_nrd_hw_m17c0_info.cur_tnr_master_gain = 0xc0;	// sync with dflt
		_g_pe_nrd_hw_m17c0_info.tnr0a_fmt = PE_NRD_M17C0_TNR_NUM;
		_g_pe_nrd_hw_m17c0_info.tnl0a_fmt = PE_NRD_M17C0_TNL_NUM;
		_g_pe_nrd_hw_m17c0_info.dnr0a_fmt = PE_NRD_M17C0_DNR_NUM;
		_g_pe_nrd_hw_m17c0_info.ifc0a_fmt = PE_NRD_M17C0_IFC_NUM;
		//_g_pre_sc_en = 0xff;
		if (PE_KDRV_VER_M17CX)
		{
			#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
			/* init tnr(nd1,2) */
			ret = PE_NRD_HW_M17C0_CreateDataTable(PE_NRD_HW_M17C0_TBL_IDX_TNR);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M17C0_CreateDataTable() error.\n");
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_hd_i_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			/* init tnr lut (nd1,2) */
			ret = PE_NRD_HW_M17C0_CreateDataTable(PE_NRD_HW_M17C0_TBL_IDX_TNL);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M17C0_CreateDataTable() error.\n");
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M17C0_TNL_REG_TABLE(tnr_l_lut_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00008000);
			/* init dnr(nd1,2) */
			ret = PE_NRD_HW_M17C0_CreateDataTable(PE_NRD_HW_M17C0_TBL_IDX_DNR);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M17C0_CreateDataTable() error.\n");
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_hd_i_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			/* init ifc(nd1) */
			ret = PE_NRD_HW_M17C0_CreateDataTable(PE_NRD_HW_M17C0_TBL_IDX_IFC);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M17C0_CreateDataTable() error.\n");
			PE_NRD_HW_M17C0_IFC_REG_TABLE(ifc_l_init_m17c0,PE_M17C0_REG_WRITE_BASE);
			#else
			//PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_hd_i_default_m17c00,PE_M17C0_REG_WRITE_BASE);
			ret = PE_NRD_HW_M17C0_CreateDataTable(PE_NRD_HW_M17C0_TBL_IDX_TNR);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M17C0_CreateDataTable() error.\n");
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			//PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_lut_hd_default_m17c00,PE_M17C0_REG_WRITE_BASE);
			/* init tnr lut (nd1,2) */
			ret = PE_NRD_HW_M17C0_CreateDataTable(PE_NRD_HW_M17C0_TBL_IDX_TNL);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M17C0_CreateDataTable() error.\n");
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M17C0_TNL_REG_TABLE(tnr_l_lut_hd_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00008000);
			PE_SET_REG_TABLE(NRD_HW_M17C0,dnr_l_hd_i_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			PE_SET_REG_TABLE(NRD_HW_M17C0,ifc_l_init_m17c0,PE_M17C0_REG_WRITE_BASE);
			#endif
			/* tnr sc enable, threshold */
			PE_CE_PE1_M17C0_RdFL(pe1_fsw_ctrl_01);
			PE_CE_PE1_M17C0_Wr01(pe1_fsw_ctrl_01,tnr_sc_measure_en, _g_pe_nrd_hw_m17c0_info.use_manual_sc? 1:0);
			PE_CE_PE1_M17C0_Wr01(pe1_fsw_ctrl_01,tnr_sc_measure_th, 0x170);//368
			PE_CE_PE1_M17C0_WrFL(pe1_fsw_ctrl_01);
			/* tnr enable */
			ret = PE_FWI_M17C0_SetFwTnrEnable(TRUE);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_FWI_M17C0_SetFwTnrEnable() error.\n",__F__,__L__);

			#ifdef PE_NRD_HW_M17C0_CVD_PAT_DETECT
			_g_pre_pattern_fw = 0xff;

			memset(&_g_pre_data0, 0, sizeof(PE_M17C0_DC_BNR_CTRL_0_T));	// 0x0
			memset(&_g_pre_data1, 0, sizeof(PE_M17C0_DC_BNR_CTRL_1_T));	// 0x0
			memset(&_g_pre_data2, 0, sizeof(PE_M17C0_DC_BNR_CTRL_2_T));	// 0x0
			memset(&_g_pre_data7, 0, sizeof(PE_M17C0_DC_BNR_CTRL_7_T));	// 0x0

			_g_pre_data_tnr_sad_cut=0xff;
			_g_pre_data_tnr_7=0xff;
			_g_pre_data_tnr_2=0xff;
			#endif
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do\n");
		}
	}while(0);
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
int PE_NRD_HW_M17C0_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_NRD_HW_M17C0_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(NRD)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_nrd_hw_m17c0_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(NRD)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if (PE_KDRV_VER_M17CX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(NRD)))
				{
					PE_NRD_HW_M17C0_DBG_PRINT("tnr,dnr : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_ND0_M17C0_QWr01(tnr_ctrl_00,reg_tnr_en,0x0);
						PE_DNR0_M17C0_QWr01(dnr_max_ctrl,reg_dnr_max_enable,0x0);
					}
				}
				else
				{
					PE_NRD_HW_M17C0_DBG_PRINT("tnr,dnr : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_ND0_M17C0_QWr01(tnr_ctrl_00,reg_tnr_en,0x1);
						PE_DNR0_M17C0_QWr01(dnr_max_ctrl,reg_dnr_max_enable,0x1);
					}
				}
			}
			else
			{
				PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
/**
 * create data table
 *
 * @param   index [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_NRD_HW_M17C0_TBL_INDX
 * @author
 */
static int PE_NRD_HW_M17C0_CreateDataTable(UINT32 index)
{
	int ret = RET_OK;
	PE_TNR_HW_PARAM_DATA_M17C0_T *p_tnr_m17c0 = &_g_pe_tnr_hw_param_data_m17c0;
	PE_TNL_HW_PARAM_DATA_M17C0_T *p_tnl_m17c0 = &_g_pe_tnl_hw_param_data_m17c0;
	PE_DNR_HW_PARAM_DATA_M17C0_T *p_dnr_m17c0 = &_g_pe_dnr_hw_param_data_m17c0;
	PE_IFC_HW_PARAM_DATA_M17C0_T *p_ifc_m17c0 = &_g_pe_ifc_hw_param_data_m17c0;

	PE_NRD_HW_M17C0_CHECK_CODE(index>=PE_NRD_HW_M17C0_TBL_IDX_NUM, return RET_ERROR, \
		"[%s,%d] index(%d) invalid.\n", __F__, __L__, index);

	if (index == PE_NRD_HW_M17C0_TBL_IDX_TNR)
	{
		/* create dflt table */
		if (p_tnr_m17c0->reg_dflt.addr == NULL)
		{
			p_tnr_m17c0->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_M17C0_T));
		}
		/* create user table */
		if (p_tnr_m17c0->nd1_user.addr == NULL)
		{
			p_tnr_m17c0->nd1_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_M17C0_T));
			memset((p_tnr_m17c0->nd1_user.addr), 0, sizeof(PE_TNR_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* create mask table */
		if (p_tnr_m17c0->nd1_mask.addr == NULL)
		{
			p_tnr_m17c0->nd1_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_M17C0_T));
			memset((p_tnr_m17c0->nd1_mask.addr), -1, sizeof(PE_TNR_HW_PARAM_REG_M17C0_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnr_m17c0->nd1_data.addr == NULL)
		{
			p_tnr_m17c0->nd1_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_M17C0_T));
			memset((p_tnr_m17c0->nd1_data.addr), 0, sizeof(PE_TNR_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* report result */
		if (p_tnr_m17c0->reg_dflt.addr != NULL && p_tnr_m17c0->nd1_user.addr != NULL && \
			p_tnr_m17c0->nd1_mask.addr != NULL && p_tnr_m17c0->nd1_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M17C0_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M17C0_TBL_IDX_TO_STR(index), \
				(p_tnr_m17c0->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnr_m17c0->nd1_user.addr == NULL)? "x":"o", \
				(p_tnr_m17c0->nd1_mask.addr == NULL)? "x":"o", \
				(p_tnr_m17c0->nd1_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_NRD_HW_M17C0_TBL_IDX_TNL)
	{
		/* create dflt table */
		if (p_tnl_m17c0->reg_dflt.addr == NULL)
		{
			p_tnl_m17c0->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_M17C0_T));
		}
		/* create user table */
		if (p_tnl_m17c0->reg_user.addr == NULL)
		{
			p_tnl_m17c0->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_M17C0_T));
			memset((p_tnl_m17c0->reg_user.addr), 0, sizeof(PE_TNL_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* create mask table */
		if (p_tnl_m17c0->reg_mask.addr == NULL)
		{
			p_tnl_m17c0->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_M17C0_T));
			memset((p_tnl_m17c0->reg_mask.addr), -1, sizeof(PE_TNL_HW_PARAM_REG_M17C0_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnl_m17c0->reg_data.addr == NULL)
		{
			p_tnl_m17c0->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_M17C0_T));
			memset((p_tnl_m17c0->reg_data.addr), 0, sizeof(PE_TNL_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* report result */
		if (p_tnl_m17c0->reg_dflt.addr != NULL && p_tnl_m17c0->reg_user.addr != NULL && \
			p_tnl_m17c0->reg_mask.addr != NULL && p_tnl_m17c0->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M17C0_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M17C0_TBL_IDX_TO_STR(index), \
				(p_tnl_m17c0->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnl_m17c0->reg_user.addr == NULL)? "x":"o", \
				(p_tnl_m17c0->reg_mask.addr == NULL)? "x":"o", \
				(p_tnl_m17c0->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_NRD_HW_M17C0_TBL_IDX_DNR)
	{
		/* create dflt table */
		if (p_dnr_m17c0->reg_dflt.addr == NULL)
		{
			p_dnr_m17c0->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_M17C0_T));
		}
		/* create user table */
		if (p_dnr_m17c0->reg_user.addr == NULL)
		{
			p_dnr_m17c0->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_M17C0_T));
			memset((p_dnr_m17c0->reg_user.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* create mask table */
		if (p_dnr_m17c0->reg_mask.addr == NULL)
		{
			p_dnr_m17c0->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_M17C0_T));
			memset((p_dnr_m17c0->reg_mask.addr), -1, sizeof(PE_DNR_HW_PARAM_REG_M17C0_T));// 0xffffffff
		}
		/* create data table */
		if (p_dnr_m17c0->reg_data.addr == NULL)
		{
			p_dnr_m17c0->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_M17C0_T));
			memset((p_dnr_m17c0->reg_data.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* report result */
		if (p_dnr_m17c0->reg_dflt.addr != NULL && p_dnr_m17c0->reg_user.addr != NULL && \
			p_dnr_m17c0->reg_mask.addr != NULL && p_dnr_m17c0->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M17C0_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M17C0_TBL_IDX_TO_STR(index), \
				(p_dnr_m17c0->reg_dflt.addr == NULL)? "x":"o", \
				(p_dnr_m17c0->reg_user.addr == NULL)? "x":"o", \
				(p_dnr_m17c0->reg_mask.addr == NULL)? "x":"o", \
				(p_dnr_m17c0->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_NRD_HW_M17C0_TBL_IDX_IFC)
	{
		/* create dflt table */
		if (p_ifc_m17c0->reg_dflt.addr == NULL)
		{
			p_ifc_m17c0->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IFC_HW_PARAM_REG_M17C0_T));
		}
		/* create user table */
		if (p_ifc_m17c0->reg_user.addr == NULL)
		{
			p_ifc_m17c0->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IFC_HW_PARAM_REG_M17C0_T));
			memset((p_ifc_m17c0->reg_user.addr), 0, sizeof(PE_IFC_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* create mask table */
		if (p_ifc_m17c0->reg_mask.addr == NULL)
		{
			p_ifc_m17c0->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IFC_HW_PARAM_REG_M17C0_T));
			memset((p_ifc_m17c0->reg_mask.addr), -1, sizeof(PE_IFC_HW_PARAM_REG_M17C0_T));// 0xffffffff
		}
		/* create data table */
		if (p_ifc_m17c0->reg_data.addr == NULL)
		{
			p_ifc_m17c0->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IFC_HW_PARAM_REG_M17C0_T));
			memset((p_ifc_m17c0->reg_data.addr), 0, sizeof(PE_IFC_HW_PARAM_REG_M17C0_T));	// 0x0
		}
		/* report result */
		if (p_ifc_m17c0->reg_dflt.addr != NULL && p_ifc_m17c0->reg_user.addr != NULL && \
			p_ifc_m17c0->reg_mask.addr != NULL && p_ifc_m17c0->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M17C0_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M17C0_TBL_IDX_TO_STR(index), \
				(p_ifc_m17c0->reg_dflt.addr == NULL)? "x":"o", \
				(p_ifc_m17c0->reg_user.addr == NULL)? "x":"o", \
				(p_ifc_m17c0->reg_mask.addr == NULL)? "x":"o", \
				(p_ifc_m17c0->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else
	{
		PE_NRD_HW_M17C0_DBG_PRINT("nothing to do\n");	ret = RET_OK;
	}
	return ret;
}
#endif

#ifdef PE_HW_M17C0_BRINGUP
/**
 * set nr default setting
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M17C0_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			ret = PE_NRD_HW_M17C0_SetDefault(pstParams);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_M17C0_SetDefault() error.\n", __F__, __L__);
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
#endif /*PE_HW_M17C0_BRINGUP*/
/**
 * set nr default setting(for M17C0X)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M17C0_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T cur0_inf;
	PE_NRD_HW_M17C0_TNR_FMT cur0_tnr_fmt;
	PE_NRD_HW_M17C0_TNL_FMT cur0_tnl_fmt;
	PE_NRD_HW_M17C0_DNR_FMT cur0_dnr_fmt;
	PE_NRD_HW_M17C0_IFC_FMT cur0_ifc_fmt;
	PE_NRD_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m17c0_info;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_M17C0_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
		PE_NRD_HW_M17C0_CHECK_CODE(ret,break,"[%s,%d] PE_INF_M17C0_GetCurInfSettings() error.\n",__F__,__L__);
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			/* tnr(nd1,2) */
			cur0_tnr_fmt = PE_NRD_HW_M17C0_ConvDispInfoToTnrFmt(&cur0_inf);
			PE_NRD_HW_M17C0_DBG_PRINT_TNR_FMT_STATE(pInfo->tnr0a_fmt,cur0_tnr_fmt);
			if(pInfo->tnr0a_fmt!=cur0_tnr_fmt)
			{
				ret = PE_NRD_HW_M17C0_SetTnrDefault(cur0_tnr_fmt);
				PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_M17C0_SetTnrDefault() error.\n", __F__, __L__);
					pInfo->tnr0a_fmt=cur0_tnr_fmt;
			}
			/* tnr(nds) */
			/* tnr lut (tnl) */
			cur0_tnl_fmt = PE_NRD_HW_M17C0_ConvDispInfoToTnlFmt(&cur0_inf);
			PE_NRD_HW_M17C0_DBG_PRINT_TNL_FMT_STATE(pInfo->tnl0a_fmt,cur0_tnl_fmt);
			if(pInfo->tnl0a_fmt!=cur0_tnl_fmt)
			{
				ret = PE_NRD_HW_M17C0_SetTnlDefault(cur0_tnl_fmt);
				PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_M17C0_SetTnlDefault() error.\n", __F__, __L__);
				pInfo->tnl0a_fmt=cur0_tnl_fmt;
			}
			/* dnr(dnr1,2) */
			cur0_dnr_fmt = PE_NRD_HW_M17C0_ConvDispInfoToDnrFmt(&cur0_inf);
			PE_NRD_HW_M17C0_DBG_PRINT_DNR_FMT_STATE(pInfo->dnr0a_fmt,cur0_dnr_fmt);
			if(pInfo->dnr0a_fmt!=cur0_dnr_fmt)
			{
				ret = PE_NRD_HW_M17C0_SetDnrDefault(cur0_dnr_fmt);
				PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_M17C0_SetDnrDefault() error.\n", __F__, __L__);
				pInfo->dnr0a_fmt=cur0_dnr_fmt;
			}
			/* ifc(dnr1 only) */
			cur0_ifc_fmt = PE_NRD_HW_M17C0_ConvDispInfoToIfcFmt(&cur0_inf);
			PE_NRD_HW_M17C0_DBG_PRINT_IFC_FMT_STATE(pInfo->ifc0a_fmt,cur0_ifc_fmt);
			if(pInfo->ifc0a_fmt!=cur0_ifc_fmt)
			{
				ret = PE_NRD_HW_M17C0_SetIfcDefault(cur0_ifc_fmt);
				PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_M17C0_SetIfcDefault() error.\n", __F__, __L__);
				pInfo->ifc0a_fmt=cur0_ifc_fmt;
			}
		}
	}while(0);
	return ret;
}
/**
 * set tnr default setting(for M17C0X)
 *
 * @param   cur0_tnr_fmt [in] PE_NRD_HW_M17C0_TNR_FMT
 * @return
 * @see
 * @author
 */
static int PE_NRD_HW_M17C0_SetTnrDefault(PE_NRD_HW_M17C0_TNR_FMT cur0_tnr_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	switch(cur0_tnr_fmt)
	{
		case PE_NRD_M17C0_TNR_SD_I:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_sd_i_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_SD_P:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_sd_p_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_HD_I:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_hd_i_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_HD_P:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_hd_p_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_UD:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_ud_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_SECAM:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_secam_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_ATV:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_atv_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_HD_FILE:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_hd_file_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_VR_360:
			PE_NRD_HW_M17C0_TNR_REG_TABLE(tnr_l_vr_360_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_tnr_fmt)
	{
		case PE_NRD_M17C0_TNR_SD_I:
			PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_sd_i_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_SD_P:
			PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_sd_p_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_HD_I:
			PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_hd_i_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_HD_P:
			PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_hd_p_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_TNR_UD:
			PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_ud_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	return ret;
}
static int PE_NRD_HW_M17C0_SetTnlDefault(PE_NRD_HW_M17C0_TNL_FMT cur0_tnl_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	switch(cur0_tnl_fmt)
	{
		case PE_NRD_M17C0_TNL_HD:
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M17C0_TNL_REG_TABLE(tnr_l_lut_hd_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_M17C0_TNL_SD:
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M17C0_TNL_REG_TABLE(tnr_l_lut_sd_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_M17C0_TNL_UHD:
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M17C0_TNL_REG_TABLE(tnr_l_lut_ud_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00008000);
			break;
		default:
			break;
	}
	#else
	switch(cur0_tnl_fmt)
	{
		
		case PE_NRD_M17C0_TNL_HD:
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
			PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_lut_hd_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_M17C0_TNL_SD:
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
			PE_SET_REG_TABLE(NRD_HW_M17C0,tnr_l_lut_sd_default_m17c0,   PE_M17C0_REG_WRITE_BASE);
			PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00008000);
			break;
		default:
			break;
	}
	#endif
	return ret;
}
static int PE_NRD_HW_M17C0_SetDnrDefault(PE_NRD_HW_M17C0_DNR_FMT cur0_dnr_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	switch(cur0_dnr_fmt)
	{
		case PE_NRD_M17C0_DNR_SD_I:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_sd_i_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_SD_P:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_sd_p_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_HD_I:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_hd_i_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_HD_P:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_hd_p_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_UD:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_ud_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_ATV:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_atv_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_SD_DTV:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_sd_dtv_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_HD_DTV:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_hd_dtv_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_AV:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_av_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_VR_360:
			PE_NRD_HW_M17C0_DNR_REG_TABLE(dnr_l_vr_360_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_dnr_fmt)
	{
		case PE_NRD_M17C0_DNR_SD:
			PE_SET_REG_TABLE(NRD_HW_M17C0,dnr_l_sd_default_m17c0, 	PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_HD_I:
			PE_SET_REG_TABLE(NRD_HW_M17C0,dnr_l_hd_i_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_DNR_HD_P:
			PE_SET_REG_TABLE(NRD_HW_M17C0,dnr_l_hd_p_default_m17c0,	 PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	return ret;
}
static int PE_NRD_HW_M17C0_SetIfcDefault(PE_NRD_HW_M17C0_IFC_FMT cur0_ifc_fmt)
{
	int ret = RET_OK;
 	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	switch(cur0_ifc_fmt)
	{
		case PE_NRD_M17C0_IFC_ATV_NTSC:
			PE_NRD_HW_M17C0_IFC_REG_TABLE(ifc_l_atv_ntsc_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_IFC_PC:
			PE_NRD_HW_M17C0_IFC_REG_TABLE(ifc_l_pc_default_m17c0,	  PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_IFC_VR_360:
			PE_NRD_HW_M17C0_IFC_REG_TABLE(ifc_l_vr_360_default_m17c0,	  PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_ifc_fmt)
	{
		case PE_NRD_M17C0_IFC_ATV_NTSC:
			PE_SET_REG_TABLE(NRD_HW_M17C0,ifc_l_atv_ntsc_default_m17c0,PE_M17C0_REG_WRITE_BASE);
			break;
		case PE_NRD_M17C0_IFC_PC:
			PE_SET_REG_TABLE(NRD_HW_M17C0,ifc_l_pc_default_m17c0, 	 PE_M17C0_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	return ret;
}
/**
 * get tnr fmt from display info.(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_M17C0_TNR_FMT
 * @see
 * @author
 */
static PE_NRD_HW_M17C0_TNR_FMT PE_NRD_HW_M17C0_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_M17C0_TNR_FMT tnr_fmt = PE_NRD_M17C0_TNR_NUM;
	PE_NRD_HW_M17C0_DBG_PRINT("TnrFmt g_pe_inf_m17c0_vr360_mode: %d.\n", g_pe_inf_m17c0_vr360_mode);
	if(disp_inf->mode.is_vr)
	{
		tnr_fmt = PE_NRD_M17C0_TNR_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					tnr_fmt = PE_NRD_M17C0_TNR_ATV;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				if(disp_inf->cstd_type==LX_PE_CSTD_SECAM)
				{
					tnr_fmt = PE_NRD_M17C0_TNR_SECAM;
				}
				else
				{
					tnr_fmt = PE_NRD_M17C0_TNR_SD_I;
				}
				break;
			case LX_PE_SRC_RGBPC:
				{
					tnr_fmt = PE_NRD_M17C0_TNR_SD_I;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						tnr_fmt = PE_NRD_M17C0_TNR_SD_I;
					else
						tnr_fmt = PE_NRD_M17C0_TNR_SD_P;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					if(disp_inf->dtv_type==LX_PE_DTV_FILEPLAY)
					{
						tnr_fmt = PE_NRD_M17C0_TNR_HD_FILE;
					}
					else
					{
						if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
							tnr_fmt = PE_NRD_M17C0_TNR_HD_I;
						else
							tnr_fmt = PE_NRD_M17C0_TNR_HD_P;
					}
				}
				else
				{
					tnr_fmt = PE_NRD_M17C0_TNR_UD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						tnr_fmt = PE_NRD_M17C0_TNR_SD_I;
					else
						tnr_fmt = PE_NRD_M17C0_TNR_SD_P;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						tnr_fmt = PE_NRD_M17C0_TNR_HD_I;
					else
						tnr_fmt = PE_NRD_M17C0_TNR_HD_P;
				}
				else
				{
					if(g_pe_inf_m17c0_vr360_mode)
					{
						if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
							tnr_fmt = PE_NRD_M17C0_TNR_HD_I;
						else
							tnr_fmt = PE_NRD_M17C0_TNR_HD_P;
					}
					else
					{
						tnr_fmt = PE_NRD_M17C0_TNR_UD;
					}
				}
				break;
		}
	}
	
	return tnr_fmt;
}
/**
 * get tnr lut (tnl) fmt from display info.(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_M17C0_TNL_FMT
 * @see
 * @author
 */
static PE_NRD_HW_M17C0_TNL_FMT PE_NRD_HW_M17C0_ConvDispInfoToTnlFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_M17C0_TNL_FMT tnl_fmt = PE_NRD_M17C0_TNL_NUM;
	/* skip drv tnr ctrl, if fw tnr on. */
	if (PE_CMN_HW_M17C0_GetDbInfo(PE_CMN_HW_M17C0_DB_INF_MD0_TNR_FW_EN, 0))
	{
		tnl_fmt = PE_NRD_M17C0_TNL_NUM;	//NA
 	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
			case LX_PE_SRC_RGBPC:
				{
					tnl_fmt = PE_NRD_M17C0_TNL_SD;
				}
				break;
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					tnl_fmt = PE_NRD_M17C0_TNL_SD;
				}
				else 
				{
					tnl_fmt = PE_NRD_M17C0_TNL_HD;
				}
				break;
		}
	}
	return tnl_fmt;
}
/**
 * get dnr fmt from display info.(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_M17C0_DNR_FMT
 * @see
 * @author
 */
static PE_NRD_HW_M17C0_DNR_FMT PE_NRD_HW_M17C0_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_M17C0_DNR_FMT dnr_fmt = PE_NRD_M17C0_DNR_NUM;
	PE_NRD_HW_M17C0_DBG_PRINT("DnrFmt g_pe_inf_m17c0_vr360_mode: %d.\n", g_pe_inf_m17c0_vr360_mode);
	if(disp_inf->mode.is_vr)
	{
		dnr_fmt = PE_NRD_M17C0_DNR_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					dnr_fmt = PE_NRD_M17C0_DNR_ATV;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					dnr_fmt = PE_NRD_M17C0_DNR_AV;
				}
				break;
			case LX_PE_SRC_RGBPC:
				{
					dnr_fmt = PE_NRD_M17C0_DNR_SD_I;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					dnr_fmt = PE_NRD_M17C0_DNR_SD_DTV;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					dnr_fmt = PE_NRD_M17C0_DNR_HD_DTV;
				}
				else
				{
					if(g_pe_inf_m17c0_vr360_mode)
					{
						dnr_fmt = PE_NRD_M17C0_DNR_HD_DTV;
					}
					else
					{
						dnr_fmt = PE_NRD_M17C0_DNR_UD;
					}
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						dnr_fmt = PE_NRD_M17C0_DNR_SD_I;
					else
						dnr_fmt = PE_NRD_M17C0_DNR_SD_P;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						dnr_fmt = PE_NRD_M17C0_DNR_HD_I;
					else
						dnr_fmt = PE_NRD_M17C0_DNR_HD_P;
				}
				else
				{
					if(g_pe_inf_m17c0_vr360_mode)
					{
						if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
							dnr_fmt = PE_NRD_M17C0_DNR_HD_I;
						else
							dnr_fmt = PE_NRD_M17C0_DNR_HD_P;
					}
					else
					{
						dnr_fmt = PE_NRD_M17C0_DNR_UD;
					}
				}
				break;
		}
	}
	return dnr_fmt;
}
/**
 * get ifc fmt from display info.(for M17C0X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_M17C0_IFC_FMT
 * @see
 * @author
 */
static PE_NRD_HW_M17C0_IFC_FMT PE_NRD_HW_M17C0_ConvDispInfoToIfcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_M17C0_IFC_FMT ifc_fmt = PE_NRD_M17C0_IFC_NUM;
	if(disp_inf->mode.is_vr)
	{
		ifc_fmt = PE_NRD_M17C0_IFC_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				if(disp_inf->cstd_type==LX_PE_CSTD_NTSC)
				{
					ifc_fmt = PE_NRD_M17C0_IFC_ATV_NTSC;
				}
				else
				{
					ifc_fmt = PE_NRD_M17C0_IFC_PC;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
			case LX_PE_SRC_RGBPC:
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				{
					ifc_fmt = PE_NRD_M17C0_IFC_PC;
				}
				break;
		}
	}
	return ifc_fmt;
}

/**
 * read default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M17C0_RdDefault(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 param_size=0, table_size=0, is_valid=0;
	UINT32 rd_cnt=0;
	PE_REG_PARAM_T param;
	PE_NRD_HW_M17C0_SETTINGS_T *pInfo=&_g_pe_nrd_hw_m17c0_info;

#define PE_NRD_M17C0_NO_PRINT			0
#define PE_NRD_M17C0_RD_N_HEX_PRINT	1
#define PE_NRD_M17C0_HEX_PRINT_ONLY	2
#define PE_NRD_M17C0_PRINT_START		"START_OF_PRINT"
#define PE_NRD_M17C0_PRINT_END		"END_OF_PRINT"
#define PE_NRD_M17C0_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_NRD_M17C0_PRINT_RESRV		"RESERVED"
#define PE_NRD_M17C0_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):sprintf(_buf, "   [0x%02x] %s\n", (_item), #_item);_action;break
#define PE_NRD_M17C0_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):sprintf(_buf, fmt, ##args);_action;break
#define PE_NRD_M17C0_DFLT_SPRINT(_action, _buf, fmt, args...)		\
	default:sprintf(_buf, fmt, ##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		
		if (PE_KDRV_VER_M17CX)
		{
			UINT32 *p_tnr1b_dflt = _g_pe_tnr_hw_param_data_m17c0.reg_dflt.addr;
			UINT32 *p_tnr1b_user = _g_pe_tnr_hw_param_data_m17c0.nd1_user.addr;
			UINT32 *p_tnr1b_mask = _g_pe_tnr_hw_param_data_m17c0.nd1_mask.addr;
			UINT32 *p_tnr1b_data = _g_pe_tnr_hw_param_data_m17c0.nd1_data.addr;
			UINT32 *p_dnr1b_dflt = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.addr;
			UINT32 *p_dnr1b_user = _g_pe_dnr_hw_param_data_m17c0.reg_user.addr;
			UINT32 *p_dnr1b_mask = _g_pe_dnr_hw_param_data_m17c0.reg_mask.addr;
			UINT32 *p_dnr1b_data = _g_pe_dnr_hw_param_data_m17c0.reg_data.addr;
			UINT32 *p_ifc1b_dflt = _g_pe_ifc_hw_param_data_m17c0.reg_dflt.addr;
			UINT32 *p_ifc1b_user = _g_pe_ifc_hw_param_data_m17c0.reg_user.addr;
			UINT32 *p_ifc1b_mask = _g_pe_ifc_hw_param_data_m17c0.reg_mask.addr;
			UINT32 *p_ifc1b_data = _g_pe_ifc_hw_param_data_m17c0.reg_data.addr;
			UINT32 *p_tnl1b_dflt = _g_pe_tnl_hw_param_data_m17c0.reg_dflt.addr;
			UINT32 *p_tnl1b_user = _g_pe_tnl_hw_param_data_m17c0.reg_user.addr;
			UINT32 *p_tnl1b_mask = _g_pe_tnl_hw_param_data_m17c0.reg_mask.addr;
			UINT32 *p_tnl1b_data = _g_pe_tnl_hw_param_data_m17c0.reg_data.addr;
			CHECK_KNULL(p_tnr1b_dflt);
			CHECK_KNULL(p_tnr1b_user);
			CHECK_KNULL(p_tnr1b_mask);
			CHECK_KNULL(p_tnr1b_data);
			CHECK_KNULL(p_dnr1b_dflt);
			CHECK_KNULL(p_dnr1b_user);
			CHECK_KNULL(p_dnr1b_mask);
			CHECK_KNULL(p_dnr1b_data);
			CHECK_KNULL(p_ifc1b_dflt);
			CHECK_KNULL(p_ifc1b_user);
			CHECK_KNULL(p_ifc1b_mask);
			CHECK_KNULL(p_ifc1b_data);
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]>=PE_NRD_HW_M17C0_RD_MENU_MAX)
			{
				sprintf(buffer, "%s", PE_NRD_M17C0_PRINT_EXIT);
				rd_cnt=0;
			}
			else if (pstParams->data[0]==PE_NRD_HW_M17C0_RD_MENU_DISP)
			{
				switch (rd_cnt)
				{
					PE_NRD_M17C0_CASE_SPRINT( 0, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_START);
					PE_NRD_M17C0_CASE_SPRINT( 1, rd_cnt++, buffer, "   ** current default **\n");
					PE_NRD_M17C0_CASE_SPRINT( 2, rd_cnt++, buffer, \
						"   tnr0a_fmt : %s\n", PE_NRD_HW_M17C0_TNR_FMT_TO_STR(pInfo->tnr0a_fmt));
					PE_NRD_M17C0_CASE_SPRINT( 3, rd_cnt++, buffer, \
						"   dnr0a_fmt : %s\n", PE_NRD_HW_M17C0_DNR_FMT_TO_STR(pInfo->dnr0a_fmt));
					PE_NRD_M17C0_CASE_SPRINT( 4, rd_cnt++, buffer, \
						"   ifc0a_fmt : %s\n", PE_NRD_HW_M17C0_IFC_FMT_TO_STR(pInfo->ifc0a_fmt));
					PE_NRD_M17C0_CASE_SPRINT( 5, rd_cnt++, buffer, \
						"   tnl0a_fmt : %s\n", PE_NRD_HW_M17C0_TNL_FMT_TO_STR(pInfo->tnl0a_fmt));
					PE_NRD_M17C0_CASE_SPRINT( 6, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT( 7, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT( 8, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT( 9, rd_cnt++, buffer, "   *********************\n");
					PE_NRD_M17C0_CASE_PRMENU(10, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNR1_DISP);
					PE_NRD_M17C0_CASE_PRMENU(11, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNR1_DFLT);
					PE_NRD_M17C0_CASE_PRMENU(12, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNR1_USER);
					PE_NRD_M17C0_CASE_PRMENU(13, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNR1_MASK);
					PE_NRD_M17C0_CASE_PRMENU(14, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNR1_DATA);
					PE_NRD_M17C0_CASE_SPRINT(15, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_PRMENU(16, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_DNR1_DISP);
					PE_NRD_M17C0_CASE_PRMENU(17, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_DNR1_DFLT);
					PE_NRD_M17C0_CASE_PRMENU(18, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_DNR1_USER);
					PE_NRD_M17C0_CASE_PRMENU(19, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_DNR1_MASK);
					PE_NRD_M17C0_CASE_PRMENU(20, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_DNR1_DATA);
					PE_NRD_M17C0_CASE_SPRINT(21, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(22, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(23, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(24, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_PRMENU(25, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_IFC1_DISP);
					PE_NRD_M17C0_CASE_PRMENU(26, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_IFC1_DFLT);
					PE_NRD_M17C0_CASE_PRMENU(27, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_IFC1_USER);
					PE_NRD_M17C0_CASE_PRMENU(28, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_IFC1_MASK);
					PE_NRD_M17C0_CASE_PRMENU(29, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_IFC1_DATA);
					PE_NRD_M17C0_CASE_SPRINT(30, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(31, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(32, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(33, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(34, rd_cnt++, buffer, "   *********************\n");
					PE_NRD_M17C0_CASE_PRMENU(35, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNR1_MLUT);
					PE_NRD_M17C0_CASE_PRMENU(36, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNL1_DFLT);
					PE_NRD_M17C0_CASE_PRMENU(37, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNL1_USER);
					PE_NRD_M17C0_CASE_PRMENU(38, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNL1_MASK);
					PE_NRD_M17C0_CASE_PRMENU(39, rd_cnt++, buffer, PE_NRD_HW_M17C0_RD_TNL1_DATA);
					PE_NRD_M17C0_CASE_SPRINT(40, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(41, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(42, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_CASE_SPRINT(43, rd_cnt++, buffer, PE_NRD_M17C0_PRINT_RESRV);
					PE_NRD_M17C0_DFLT_SPRINT(rd_cnt=0, buffer, PE_NRD_M17C0_PRINT_END);
				}
			}
			else
			{
				is_valid = PE_NRD_M17C0_NO_PRINT;
				switch (pstParams->data[0])
				{
					case PE_NRD_HW_M17C0_RD_TNR1_DISP:
						table_size = sizeof(tnr_l_hd_i_default_m17c0);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m17c0[rd_cnt].addr;
							is_valid = PE_NRD_M17C0_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNR1_DFLT:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m17c0[rd_cnt].addr;
							param.data = p_tnr1b_dflt[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNR1_USER:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m17c0[rd_cnt].addr;
							param.data = p_tnr1b_user[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNR1_MASK:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m17c0[rd_cnt].addr;
							param.data = p_tnr1b_mask[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNR1_DATA:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m17c0[rd_cnt].addr;
							param.data = p_tnr1b_data[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_DNR1_DISP:
						table_size = sizeof(dnr_l_hd_i_default_m17c0);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m17c0[rd_cnt].addr;
							is_valid = PE_NRD_M17C0_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M17C0_RD_DNR1_DFLT:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m17c0[rd_cnt].addr;
							param.data = p_dnr1b_dflt[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_DNR1_USER:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m17c0[rd_cnt].addr;
							param.data = p_dnr1b_user[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_DNR1_MASK:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m17c0[rd_cnt].addr;
							param.data = p_dnr1b_mask[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_DNR1_DATA:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m17c0[rd_cnt].addr;
							param.data = p_dnr1b_data[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_IFC1_DISP:
						table_size = sizeof(ifc_l_init_m17c0);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m17c0[rd_cnt].addr;
							is_valid = PE_NRD_M17C0_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M17C0_RD_IFC1_DFLT:
						table_size = sizeof(PE_IFC_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m17c0[rd_cnt].addr;
							param.data = p_ifc1b_dflt[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_IFC1_USER:
						table_size = sizeof(PE_IFC_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m17c0[rd_cnt].addr;
							param.data = p_ifc1b_user[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_IFC1_MASK:
						table_size = sizeof(PE_IFC_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m17c0[rd_cnt].addr;
							param.data = p_ifc1b_mask[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_IFC1_DATA:
						table_size = sizeof(PE_IFC_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m17c0[rd_cnt].addr;
							param.data = p_ifc1b_data[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNR1_MLUT:
						table_size = sizeof(tnr_l_lut_hd_default_m17c0);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							if (rd_cnt==0)
							{
								if (pstParams->data[0]==PE_NRD_HW_M17C0_RD_TNR1_MLUT)
									PE_REG_M17_WD(0x41D0, 0x00001000);
							}
							param.addr = tnr_l_lut_hd_default_m17c0[rd_cnt].addr;
							is_valid = PE_NRD_M17C0_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNL1_DFLT:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_m17c0[rd_cnt].addr;
							param.data = p_tnl1b_dflt[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNL1_USER:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_m17c0[rd_cnt].addr;
							param.data = p_tnl1b_user[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNL1_MASK:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_m17c0[rd_cnt].addr;
							param.data = p_tnl1b_mask[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M17C0_RD_TNL1_DATA:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_M17C0_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_m17c0[rd_cnt].addr;
							param.data = p_tnl1b_data[rd_cnt];
							is_valid = PE_NRD_M17C0_HEX_PRINT_ONLY;
						}
						break;
					default:
						break;
				}
				if (is_valid == PE_NRD_M17C0_RD_N_HEX_PRINT)
				{
					param.data = PE_REG_M17_RD(param.addr);
					sprintf(buffer, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else if (is_valid == PE_NRD_M17C0_HEX_PRINT_ONLY)
				{
					sprintf(buffer, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else
				{
					sprintf(buffer, "%s", PE_NRD_M17C0_PRINT_END);
					rd_cnt = 0;
				}
			}
			memcpy(pstParams->data, buffer, sizeof(char)*PE_TRACE_STR_SIZE);
		}
	}while (0);
	#endif
	return ret;
}

/**
 * set dnr common ctrl
 * - use input struct LX_PE_NRD_DNR6_CMN_T
 *  001._[MAX_CTRL]_0xC8007194_[0____]_1_UINT8__common[00]:_dnr_max_ctrl,__reg_dnr_max_enable,
 *  002._[DC_BNR__]_0xC80071BC_[0____]_1_UINT8__common[01]:_dc_bnr_ctrl_0,_reg_dc_bnr_enable,
 *  003._[DC_BNR__]_0xC80071C4_[15:10]_6_UINT8__common[02]:_dc_bnr_ctrl_2,_reg_dc_bnr_mastergain,
 *  004._[DC_BNR__]_0xC80071C4_[23:16]_8_UINT8__common[03]:_dc_bnr_ctrl_2,_reg_dc_bnr_chromagain,
 *  005._[AC_BNR__]_0xC80071D4_[0____]_1_UINT8__common[04]:_ac_bnr_ctrl_0,_reg_bnr_ac_h_en,
 *  006._[AC_BNR__]_0xC80071D4_[1____]_1_UINT8__common[05]:_ac_bnr_ctrl_0,_reg_bnr_ac_v_en,
 *  007._[AC_BNR__]_0xC80071D4_[2____]_1_UINT8__common[06]:_ac_bnr_ctrl_0,_reg_bnr_ac_h_chroma_en,
 *  008._[AC_BNR__]_0xC80071D4_[3____]_1_UINT8__common[07]:_ac_bnr_ctrl_0,_reg_bnr_ac_v_chroma_en,
 *  009._[AC_BNR__]_0xC80071D4_[5:4__]_2_UINT8__common[08]:_ac_bnr_ctrl_0,_reg_bnr_ac_acness_resol_h,
 *  010._[AC_BNR__]_0xC8007204_[15:10]_6_UINT8__common[09]:_ac_bnr_ctrl_9,_reg_ac_master_gain,
 *  011._[MNR_____]_0xC80071A0_[0____]_1_UINT8__common[10]:_mnr_ctrl_0,____reg_mnr_enable,
 *  012._[MNR_____]_0xC80071A0_[15:8_]_8_UINT8__common[11]:_mnr_ctrl_0,____reg_mnr_master_gain,
 *  013._[MNR_____]_0xC80071A0_[23:16]_8_UINT8__common[12]:_mnr_ctrl_0,____reg_chroma_master_gain,
 *  014._[MNR_____]_0xC80071A8_[23:16]_8_UINT8__common[13]:_mnr_ctrl_2,____reg_mnr_v_gain,
 *  015._[MNR_____]_0xC80071A8_[31:24]_8_UINT8__common[14]:_mnr_ctrl_2,____reg_mnr_h_gain,
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M17C0_SetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	PE_FWI_M17C0_DNR_COMMON fw_param;
	PE_NRD_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m17c0_info;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			#ifndef PE_FOR_M17C0_KDRV_BRINGUP
			LX_PE_NRD_DNR8_CMN_T *pp=(LX_PE_NRD_DNR8_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_nrd_hw_m17c0_trace)
			{
				UINT8 *pd = pp->data;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"data[00]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"data[10]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"data[20]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"data[30]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"data[40]%3d,%3d,%3d,%3d,%3d,%3d\n",\
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39], \
					pd[40], pd[41], pd[42], pd[43], pd[44], pd[45]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_DNR0_M17C0_RdFL(dnr_max_ctrl);
				PE_DNR0_M17C0_RdFL(mnr_ctrl_0);
				#ifndef PE_NRD_HW_M17C0_CVD_PAT_DETECT
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_2);
				#endif
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_8);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_9);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_0);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_2);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_3);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_4);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_5);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_6);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_7);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_8);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_9);

				PE_DNR0_M17C0_Wr01(dnr_max_ctrl,  reg_dnr_max_enable,		GET_BITS(pp->data[0], 0, 1));

				PE_DNR0_M17C0_Wr01(mnr_ctrl_0,  reg_mnr_master_gain,		GET_BITS(pp->data[1], 0, 8));
				PE_DNR0_M17C0_Wr01(mnr_ctrl_0,  reg_mnr_chroma_en,		GET_BITS(pp->data[2], 0, 1));
				PE_DNR0_M17C0_Wr01(mnr_ctrl_0,  reg_mnr_enable,			GET_BITS(pp->data[3], 0, 1));

				#ifndef PE_NRD_HW_M17C0_CVD_PAT_DETECT
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_0,  reg_dc_bnr_enable,		GET_BITS(pp->data[4], 0, 1));

				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2,  reg_dc_bnr_chromagain,	GET_BITS(pp->data[5], 0, 8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2,  reg_dc_bnr_mastergain,	GET_BITS(pp->data[6], 0, 6));
				#endif

				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_0,  reg_bnr_ac_v_chroma_en,GET_BITS(pp->data[7], 0, 1));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_0,  reg_bnr_ac_h_chroma_en,GET_BITS(pp->data[8], 0, 1));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_0,  reg_bnr_ac_v_en,		GET_BITS(pp->data[9], 0, 1));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_0,  reg_bnr_ac_h_en,		GET_BITS(pp->data[10], 0, 1));

				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_8,  reg_ac_master_c_gain,	GET_BITS(pp->data[11], 0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_9,  reg_ac_master_y_gain,	GET_BITS(pp->data[12], 0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_0, reg_decon_en,			GET_BITS(pp->data[13],  0, 1));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_2, reg_decon_diff_x_th3,	GET_BITS(pp->data[14],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_2, reg_decon_diff_x_th2,	GET_BITS(pp->data[15],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_2, reg_decon_diff_x_th1,	GET_BITS(pp->data[16],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_2, reg_decon_diff_x_th0,	GET_BITS(pp->data[17],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_3, reg_decon_diff_y_th3,	GET_BITS(pp->data[18],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_3, reg_decon_diff_y_th2,	GET_BITS(pp->data[19],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_3, reg_decon_diff_y_th1,	GET_BITS(pp->data[20],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_3, reg_decon_diff_y_th0,	GET_BITS(pp->data[21],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_4, reg_decon_var_x_th3,		GET_BITS(pp->data[22],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_4, reg_decon_var_x_th2,		GET_BITS(pp->data[23],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_4, reg_decon_var_x_th1,		GET_BITS(pp->data[24],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_4, reg_decon_var_x_th0,		GET_BITS(pp->data[25],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_5, reg_decon_var_y_th3,		GET_BITS(pp->data[26],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_5, reg_decon_var_y_th2,		GET_BITS(pp->data[27],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_5, reg_decon_var_y_th1,		GET_BITS(pp->data[28],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_5, reg_decon_var_y_th0,		GET_BITS(pp->data[29],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_6, reg_decon_luma_x_th3,	GET_BITS(pp->data[30],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_6, reg_decon_luma_x_th2,	GET_BITS(pp->data[31],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_6, reg_decon_luma_x_th1,	GET_BITS(pp->data[32],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_6, reg_decon_luma_x_th0,	GET_BITS(pp->data[33],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_7, reg_decon_luma_x_th7,	GET_BITS(pp->data[34],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_7, reg_decon_luma_x_th6,	GET_BITS(pp->data[35],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_7, reg_decon_luma_x_th5,	GET_BITS(pp->data[36],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_7, reg_decon_luma_x_th4,	GET_BITS(pp->data[37],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_8, reg_decon_luma_y_th3,	GET_BITS(pp->data[38],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_8, reg_decon_luma_y_th2,	GET_BITS(pp->data[39],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_8, reg_decon_luma_y_th1,	GET_BITS(pp->data[40],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_8, reg_decon_luma_y_th0,	GET_BITS(pp->data[41],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_9, reg_decon_luma_y_th7,	GET_BITS(pp->data[42],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_9, reg_decon_luma_y_th6,	GET_BITS(pp->data[43],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_9, reg_decon_luma_y_th5,	GET_BITS(pp->data[44],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_9, reg_decon_luma_y_th4,	GET_BITS(pp->data[45],  0, 8));

				PE_DNR0_M17C0_WrFL(dnr_max_ctrl);
				PE_DNR0_M17C0_WrFL(mnr_ctrl_0);
				#ifndef PE_NRD_HW_M17C0_CVD_PAT_DETECT
				PE_DNR0_M17C0_WrFL(dc_bnr_ctrl_0);
				PE_DNR0_M17C0_WrFL(dc_bnr_ctrl_2);
				#endif
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_0);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_8);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_9);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_0);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_2);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_3);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_4);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_5);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_6);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_7);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_8);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_9);

				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				/* update user data */
				PE_NRD_HW_M17C0_DNR_SET_USER(dnr_max_ctrl,  reg_dnr_max_enable,		GET_BITS(pp->data[0], 0, 1));
				pInfo->dnr_max_en0_user = GET_BITS(pp->data[0], 0, 1);
				pInfo->dnr_max_en0_mask = 1;				
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_0,  reg_mnr_master_gain,		GET_BITS(pp->data[1], 0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_0,  reg_mnr_chroma_en,			GET_BITS(pp->data[2], 0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_0,  reg_mnr_enable,				GET_BITS(pp->data[3], 0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_0,  reg_dc_bnr_enable,		GET_BITS(pp->data[4], 0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_2,  reg_dc_bnr_chromagain,	GET_BITS(pp->data[5], 0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_2,  reg_dc_bnr_mastergain,	GET_BITS(pp->data[6], 0, 6));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_0,  reg_bnr_ac_v_chroma_en,GET_BITS(pp->data[7], 0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_0,  reg_bnr_ac_h_chroma_en,GET_BITS(pp->data[8], 0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_0,  reg_bnr_ac_v_en,		GET_BITS(pp->data[9], 0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_0,  reg_bnr_ac_h_en,		GET_BITS(pp->data[10], 0, 1));
				pInfo->bnr_ac_h_en0_user = GET_BITS(pp->data[4], 0, 1);
				pInfo->bnr_ac_h_en0_mask = 1;
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_8,  reg_ac_master_c_gain,	GET_BITS(pp->data[11], 0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_9,  reg_ac_master_y_gain,	GET_BITS(pp->data[12], 0, 8));
				#if 1
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_0, reg_decon_en,			GET_BITS(pp->data[13],  0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_2, reg_decon_diff_x_th3,	GET_BITS(pp->data[14],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_2, reg_decon_diff_x_th2,	GET_BITS(pp->data[15],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_2, reg_decon_diff_x_th1,	GET_BITS(pp->data[16],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_2, reg_decon_diff_x_th0,	GET_BITS(pp->data[17],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_3, reg_decon_diff_y_th3,	GET_BITS(pp->data[18],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_3, reg_decon_diff_y_th2,	GET_BITS(pp->data[19],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_3, reg_decon_diff_y_th1,	GET_BITS(pp->data[20],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_3, reg_decon_diff_y_th0,	GET_BITS(pp->data[21],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_4, reg_decon_var_x_th3,	GET_BITS(pp->data[22],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_4, reg_decon_var_x_th2,	GET_BITS(pp->data[23],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_4, reg_decon_var_x_th1,	GET_BITS(pp->data[24],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_4, reg_decon_var_x_th0,	GET_BITS(pp->data[25],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_5, reg_decon_var_y_th3,	GET_BITS(pp->data[26],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_5, reg_decon_var_y_th2,	GET_BITS(pp->data[27],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_5, reg_decon_var_y_th1,	GET_BITS(pp->data[28],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_5, reg_decon_var_y_th0,	GET_BITS(pp->data[29],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_6, reg_decon_luma_x_th3,	GET_BITS(pp->data[30],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_6, reg_decon_luma_x_th2,	GET_BITS(pp->data[31],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_6, reg_decon_luma_x_th1,	GET_BITS(pp->data[32],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_6, reg_decon_luma_x_th0,	GET_BITS(pp->data[33],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_7, reg_decon_luma_x_th7,	GET_BITS(pp->data[34],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_7, reg_decon_luma_x_th6,	GET_BITS(pp->data[35],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_7, reg_decon_luma_x_th5,	GET_BITS(pp->data[36],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_7, reg_decon_luma_x_th4,	GET_BITS(pp->data[37],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_8, reg_decon_luma_y_th3,	GET_BITS(pp->data[38],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_8, reg_decon_luma_y_th2,	GET_BITS(pp->data[39],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_8, reg_decon_luma_y_th1,	GET_BITS(pp->data[40],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_8, reg_decon_luma_y_th0,	GET_BITS(pp->data[41],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_9, reg_decon_luma_y_th7,	GET_BITS(pp->data[42],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_9, reg_decon_luma_y_th6,	GET_BITS(pp->data[43],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_9, reg_decon_luma_y_th5,	GET_BITS(pp->data[44],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(reg_decon_ctrl_9, reg_decon_luma_y_th4,	GET_BITS(pp->data[45],  0, 8));
				#endif

				#endif
				if (PE_CMN_HW_M17C0_GetDbInfo(PE_CMN_HW_M17C0_DB_INF_MD0_DNR_FW_EN, 0))
				{
					memcpy(fw_param.data, pp->data, sizeof(UINT8)*PE_FWI_M17C0_DNR_CMN_SIZE);
					ret = PE_FWI_M17C0_SetDnrCommon(&fw_param);
					PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_FWI_M17C0_SetDnrCommon() error.\n", __F__, __L__);
				}
			}
			#endif
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get dnr common ctrl
 * - use input struct LX_PE_NRD_DNR6_CMN_T
 *  001._[MAX_CTRL]_0xC8007194_[0____]_1_UINT8__common[00]:_dnr_max_ctrl,__reg_dnr_max_enable,
 *  002._[DC_BNR__]_0xC80071BC_[0____]_1_UINT8__common[01]:_dc_bnr_ctrl_0,_reg_dc_bnr_enable,
 *  003._[DC_BNR__]_0xC80071C4_[15:10]_6_UINT8__common[02]:_dc_bnr_ctrl_2,_reg_dc_bnr_mastergain,
 *  004._[DC_BNR__]_0xC80071C4_[23:16]_8_UINT8__common[03]:_dc_bnr_ctrl_2,_reg_dc_bnr_chromagain,
 *  005._[AC_BNR__]_0xC80071D4_[0____]_1_UINT8__common[04]:_ac_bnr_ctrl_0,_reg_bnr_ac_h_en,
 *  006._[AC_BNR__]_0xC80071D4_[1____]_1_UINT8__common[05]:_ac_bnr_ctrl_0,_reg_bnr_ac_v_en,
 *  007._[AC_BNR__]_0xC80071D4_[2____]_1_UINT8__common[06]:_ac_bnr_ctrl_0,_reg_bnr_ac_h_chroma_en,
 *  008._[AC_BNR__]_0xC80071D4_[3____]_1_UINT8__common[07]:_ac_bnr_ctrl_0,_reg_bnr_ac_v_chroma_en,
 *  009._[AC_BNR__]_0xC80071D4_[5:4__]_2_UINT8__common[08]:_ac_bnr_ctrl_0,_reg_bnr_ac_acness_resol_h,
 *  010._[AC_BNR__]_0xC8007204_[15:10]_6_UINT8__common[09]:_ac_bnr_ctrl_9,_reg_ac_master_gain,
 *  011._[MNR_____]_0xC80071A0_[0____]_1_UINT8__common[10]:_mnr_ctrl_0,____reg_mnr_enable,
 *  012._[MNR_____]_0xC80071A0_[15:8_]_8_UINT8__common[11]:_mnr_ctrl_0,____reg_mnr_master_gain,
 *  013._[MNR_____]_0xC80071A0_[23:16]_8_UINT8__common[12]:_mnr_ctrl_0,____reg_chroma_master_gain,
 *  014._[MNR_____]_0xC80071A8_[23:16]_8_UINT8__common[13]:_mnr_ctrl_2,____reg_mnr_v_gain,
 *  015._[MNR_____]_0xC80071A8_[31:24]_8_UINT8__common[14]:_mnr_ctrl_2,____reg_mnr_h_gain,
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M17C0_GetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			#ifndef PE_FOR_M17C0_KDRV_BRINGUP
			LX_PE_NRD_DNR8_CMN_T *pp = (LX_PE_NRD_DNR8_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_DNR0_M17C0_RdFL(dnr_max_ctrl);
				PE_DNR0_M17C0_RdFL(mnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_2);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_8);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_9);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_0);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_2);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_3);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_4);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_5);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_6);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_7);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_8);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_9);

				PE_DNR0_M17C0_Rd01(dnr_max_ctrl,  reg_dnr_max_enable,		pp->data[0]);
				PE_DNR0_M17C0_Rd01(mnr_ctrl_0,  reg_mnr_master_gain,		pp->data[1]);
				PE_DNR0_M17C0_Rd01(mnr_ctrl_0,  reg_mnr_chroma_en,		pp->data[2]);
				PE_DNR0_M17C0_Rd01(mnr_ctrl_0,  reg_mnr_enable,			pp->data[3]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_0,  reg_dc_bnr_enable,		pp->data[4]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_2,  reg_dc_bnr_chromagain,	pp->data[5]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_2,  reg_dc_bnr_mastergain,	pp->data[6]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_0,  reg_bnr_ac_v_chroma_en,pp->data[7]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_0,  reg_bnr_ac_h_chroma_en,pp->data[8]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_0,  reg_bnr_ac_v_en,		pp->data[9]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_0,  reg_bnr_ac_h_en,		pp->data[10]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_8,  reg_ac_master_c_gain,	pp->data[11]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_9,  reg_ac_master_y_gain,	pp->data[12]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_0, reg_decon_en,			pp->data[13]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_2, reg_decon_diff_x_th3,	pp->data[14]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_2, reg_decon_diff_x_th2,	pp->data[15]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_2, reg_decon_diff_x_th1,	pp->data[16]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_2, reg_decon_diff_x_th0,	pp->data[17]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_3, reg_decon_diff_y_th3,	pp->data[18]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_3, reg_decon_diff_y_th2,	pp->data[19]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_3, reg_decon_diff_y_th1,	pp->data[20]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_3, reg_decon_diff_y_th0,	pp->data[21]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_4, reg_decon_var_x_th3,		pp->data[22]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_4, reg_decon_var_x_th2,		pp->data[23]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_4, reg_decon_var_x_th1,		pp->data[24]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_4, reg_decon_var_x_th0,		pp->data[25]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_5, reg_decon_var_y_th3,		pp->data[26]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_5, reg_decon_var_y_th2,		pp->data[27]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_5, reg_decon_var_y_th1,		pp->data[28]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_5, reg_decon_var_y_th0,		pp->data[29]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_6, reg_decon_luma_x_th3,	pp->data[30]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_6, reg_decon_luma_x_th2,	pp->data[31]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_6, reg_decon_luma_x_th1,	pp->data[32]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_6, reg_decon_luma_x_th0,	pp->data[33]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_7, reg_decon_luma_x_th7,	pp->data[34]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_7, reg_decon_luma_x_th6,	pp->data[35]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_7, reg_decon_luma_x_th5,	pp->data[36]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_7, reg_decon_luma_x_th4,	pp->data[37]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_8, reg_decon_luma_y_th3,	pp->data[38]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_8, reg_decon_luma_y_th2,	pp->data[39]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_8, reg_decon_luma_y_th1,	pp->data[40]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_8, reg_decon_luma_y_th0,	pp->data[41]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_9, reg_decon_luma_y_th7,	pp->data[42]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_9, reg_decon_luma_y_th6,	pp->data[43]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_9, reg_decon_luma_y_th5,	pp->data[44]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_9, reg_decon_luma_y_th4,	pp->data[45]);

			}
			if (_g_nrd_hw_m17c0_trace)
			{
				UINT8 *pd = pp->data;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"data[00]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"data[10]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"data[20]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"data[30]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"data[40]%3d,%3d,%3d,%3d,%3d,%3d\n",\
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39], \
					pd[40], pd[41], pd[42], pd[43], pd[44], pd[45]);
			}
			#endif
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * set dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T
 *  016._[DC_BNR__]_0xC80071C4_[0____]_1_UINT8__dc_bnr[00]:_dc_bnr_ctrl_2,_reg_dc_var_en,
 *  017._[DC_BNR__]_0xC80071C4_[1____]_1_UINT8__dc_bnr[01]:_dc_bnr_ctrl_2,_reg_dc_motion_en,
 *  018._[DC_BNR__]_0xC80071C4_[2____]_1_UINT8__dc_bnr[02]:_dc_bnr_ctrl_2,_reg_dc_protection_en,
 *  019._[DC_BNR__]_0xC80071C4_[3____]_1_UINT8__dc_bnr[03]:_dc_bnr_ctrl_2,_reg_dc_detail_en,
 *  020._[DC_BNR__]_0xC80071BC_[3:2__]_2_UINT8__dc_bnr[04]:_dc_bnr_ctrl_0,_reg_dc_blur_sel,
 *  021._[DC_BNR__]_0xC80071BC_[23:16]_8_UINT8__dc_bnr[05]:_dc_bnr_ctrl_0,_reg_dc_motion_max,
 *  022._[DC_BNR__]_0xC80071BC_[31:24]_8_UINT8__dc_bnr[06]:_dc_bnr_ctrl_0,_reg_dc_motion_min,
 *  023._[DC_BNR__]_0xC80071C0_[7:0__]_8_UINT8__dc_bnr[07]:_dc_bnr_ctrl_1,_reg_dc_detail_max,
 *  024._[DC_BNR__]_0xC80071C0_[15:8_]_8_UINT8__dc_bnr[08]:_dc_bnr_ctrl_1,_reg_dc_detail_min,
 *  025._[DC_BNR__]_0xC80071C0_[23:20]_4_UINT8__dc_bnr[09]:_dc_bnr_ctrl_1,_reg_var_v_gain,
 *  026._[DC_BNR__]_0xC80071C0_[27:24]_4_UINT8__dc_bnr[10]:_dc_bnr_ctrl_1,_reg_var_h_gain,
 *  027._[DC_BNR__]_0xC80071C0_[31:28]_4_UINT8__dc_bnr[11]:_dc_bnr_ctrl_1,_reg_var_cut_resolution,
 *  028._[DC_BNR__]_0xC80071C4_[7:4__]_4_UINT8__dc_bnr[12]:_dc_bnr_ctrl_2,_reg_dc_global_motion_th,
 *  029._[DC_BNR__]_0xC80071C4_[31:24]_8_UINT8__dc_bnr[13]:_dc_bnr_ctrl_2,_reg_dc_protection_th,
 *  030._[DC_BNR__]_0xC80071C8_[7:0__]_8_UINT8__dc_bnr[14]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th3,
 *  031._[DC_BNR__]_0xC80071C8_[15:8_]_8_UINT8__dc_bnr[15]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th2,
 *  032._[DC_BNR__]_0xC80071C8_[23:16]_8_UINT8__dc_bnr[16]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th1,
 *  033._[DC_BNR__]_0xC80071C8_[31:24]_8_UINT8__dc_bnr[17]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th0,
 *  034._[DC_BNR__]_0xC80071C4_[8____]_1_UINT8__dc_bnr[18]:_dc_bnr_ctrl_2,_reg_detail_sel,
 *  035._[DETAIL__]_0xC80071B8_[7:0__]_8_UINT8__dc_bnr[19]:_detail_ctrl,___reg_bnr_ac_detail_max,
 *  036._[DETAIL__]_0xC80071B8_[15:8_]_8_UINT8__dc_bnr[20]:_detail_ctrl,___reg_bnr_ac_detail_min,
 *  037._[DETAIL__]_0xC80071B8_[23:16]_8_UINT8__dc_bnr[21]:_detail_ctrl,___reg_bnr_diff_l,
 *  038._[DETAIL__]_0xC80071B8_[31:24]_8_UINT8__dc_bnr[22]:_detail_ctrl,___reg_bnr_diff_p,
 *  039._[SC_BNR__]_0xC800726C_[0____]_1_UINT8__dc_bnr[23]:_sc_bnr_ctrl_0,_reg_sc_bnr_en,
 *  040._[SC_BNR__]_0xC8007280_[7:0__]_8_UINT8__dc_bnr[24]:_sc_bnr_ctrl_5,_reg_pos_gain_3,
 *  041._[SC_BNR__]_0xC8007280_[15:8_]_8_UINT8__dc_bnr[25]:_sc_bnr_ctrl_5,_reg_pos_gain_2,
 *  042._[SC_BNR__]_0xC8007280_[23:16]_8_UINT8__dc_bnr[26]:_sc_bnr_ctrl_5,_reg_pos_gain_1,
 *  043._[TEXTURE_]_0xC800728C_[2:0__]_3_UINT8__dc_bnr[27]:_texture_ctrl_0,reg_texture_cnt_div,
 *  044._[TEXTURE_]_0xC800728C_[15:8_]_8_UINT8__dc_bnr[28]:_texture_ctrl_0,reg_texture_cnt_mul,
 *  045._[TEXTURE_]_0xC800728C_[31:24]_8_UINT8__dc_bnr[29]:_texture_ctrl_0,reg_cross_th,
 *  046._[AC_BNR__]_0xC80071D4_[15:8_]_8_UINT8__ac_bnr[00]:_ac_bnr_ctrl_0,_reg_bnr_ac_diff_min_v_th,
 *  047._[AC_BNR__]_0xC80071D4_[23:16]_8_UINT8__ac_bnr[01]:_ac_bnr_ctrl_0,_reg_bnr_ac_diff_min_h_th,
 *  048._[AC_BNR__]_0xC80071D8_[7:0__]_8_UINT8__ac_bnr[02]:_ac_bnr_ctrl_1,_reg_bnr_ac_global_motion_th,
 *  049._[AC_BNR__]_0xC80071D8_[15:8_]_8_UINT8__ac_bnr[03]:_ac_bnr_ctrl_1,_reg_bnr_ac_h_acness_max,
 *  050._[AC_BNR__]_0xC80071E8_[23:16]_8_UINT8__ac_bnr[04]:_ac_bnr_ctrl_4,_reg_bnr_ac_v_acness_max,
 *  051._[AC_BNR__]_0xC80071D8_[23:16]_8_UINT8__ac_bnr[05]:_ac_bnr_ctrl_1,_reg_bnr_ac_h_acness_min,
 *  052._[AC_BNR__]_0xC80071E8_[31:24]_8_UINT8__ac_bnr[06]:_ac_bnr_ctrl_4,_reg_bnr_ac_v_acness_min,
 *  053._[AC_BNR__]_0xC80071E8_[7:6__]_2_UINT8__ac_bnr[07]:_ac_bnr_ctrl_4,_reg_bnr_ac_acness_resol_v,
 *  054._[AC_BNR__]_0xC80071DC_[7:0__]_8_UINT8__ac_bnr[08]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_3,
 *  055._[AC_BNR__]_0xC80071DC_[15:8_]_8_UINT8__ac_bnr[09]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_2,
 *  056._[AC_BNR__]_0xC80071DC_[23:16]_8_UINT8__ac_bnr[10]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_1,
 *  057._[AC_BNR__]_0xC80071DC_[31:24]_8_UINT8__ac_bnr[11]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_0,
 *  058._[AC_BNR__]_0xC80071E4_[7:0__]_8_UINT8__ac_bnr[12]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_3,
 *  059._[AC_BNR__]_0xC80071E4_[15:8_]_8_UINT8__ac_bnr[13]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_2,
 *  060._[AC_BNR__]_0xC80071E4_[23:16]_8_UINT8__ac_bnr[14]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_1,
 *  061._[AC_BNR__]_0xC80071E4_[31:24]_8_UINT8__ac_bnr[15]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_0,
 *  062._[AC_BNR__]_0xC80071F4_[31:24]_8_UINT8__ac_bnr[16]:_ac_bnr_ctrl_6,_reg_bnr_ac_detail_gain_th,
 *  063._[AC_BNR__]_0xC80071F0_[7:0__]_8_UINT8__ac_bnr[17]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th4,
 *  064._[AC_BNR__]_0xC80071F0_[15:8_]_8_UINT8__ac_bnr[18]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th3,
 *  065._[AC_BNR__]_0xC80071F0_[23:16]_8_UINT8__ac_bnr[19]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th2,
 *  066._[AC_BNR__]_0xC80071F0_[31:24]_8_UINT8__ac_bnr[20]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th1,
 *  067._[AC_BNR__]_0xC80071F8_[31:24]_8_UINT8__ac_bnr[21]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_h3,
 *  068._[AC_BNR__]_0xC80071F4_[7:0__]_8_UINT8__ac_bnr[22]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h2,
 *  069._[AC_BNR__]_0xC80071F4_[15:8_]_8_UINT8__ac_bnr[23]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h1,
 *  070._[AC_BNR__]_0xC80071F4_[23:16]_8_UINT8__ac_bnr[24]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h0,
 *  071._[AC_BNR__]_0xC80071F8_[7:0__]_8_UINT8__ac_bnr[25]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l2,
 *  072._[AC_BNR__]_0xC80071F8_[15:8_]_8_UINT8__ac_bnr[26]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l1,
 *  073._[AC_BNR__]_0xC80071F8_[23:16]_8_UINT8__ac_bnr[27]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l0,
 *  074._[MNR_____]_0xC80071A0_[5:4__]_2_UINT8__mosqnr[00]:_mnr_ctrl_0,____reg_h_expand,
 *  075._[MNR_____]_0xC80071A0_[6____]_1_UINT8__mosqnr[01]:_mnr_ctrl_0,____reg_gain_flt_size,
 *  076._[MNR_____]_0xC80071A4_[7:0__]_8_UINT8__mosqnr[02]:_mnr_ctrl_1,____reg_mnr_s1_mmd_min,
 *  077._[MNR_____]_0xC80071A4_[15:8_]_8_UINT8__mosqnr[03]:_mnr_ctrl_1,____reg_mnr_s2_ratio_min,
 *  078._[MNR_____]_0xC80071A4_[23:16]_8_UINT8__mosqnr[04]:_mnr_ctrl_1,____reg_mnr_s2_ratio_max,
 *  079._[MNR_____]_0xC80071A4_[31:24]_8_UINT8__mosqnr[05]:_mnr_ctrl_1,____reg_mnr_s2_mmd_min,
 *  080._[MNR_____]_0xC80071AC_[7:0__]_8_UINT8__mosqnr[06]:_mnr_ctrl_3,____reg_filter_x0,
 *  081._[MNR_____]_0xC80071AC_[15:8_]_8_UINT8__mosqnr[07]:_mnr_ctrl_3,____reg_filter_x1,
 *  082._[MNR_____]_0xC80071AC_[23:16]_8_UINT8__mosqnr[08]:_mnr_ctrl_3,____reg_filter_y0,
 *  083._[MNR_____]_0xC80071AC_[31:24]_8_UINT8__mosqnr[09]:_mnr_ctrl_3,____reg_filter_y1,
 *  084._[MNR_____]_0xC80071B0_[0____]_1_UINT8__mosqnr[10]:_mnr_ctrl_4,____reg_motion_mnr_en,
 *  085._[MNR_____]_0xC80071B0_[2:1__]_2_UINT8__mosqnr[11]:_mnr_ctrl_4,____reg_motion_mnr_filter,
 *  086._[MNR_____]_0xC80071B0_[4:3__]_2_UINT8__mosqnr[12]:_mnr_ctrl_4,____reg_motion_mnr_filter_c,
 *  087._[MNR_____]_0xC80071B0_[6:5__]_2_UINT8__mosqnr[13]:_mnr_ctrl_4,____reg_mnr_filter,
 *  088._[MNR_____]_0xC80071B0_[8:7__]_2_UINT8__mosqnr[14]:_mnr_ctrl_4,____reg_mnr_filter_c,
 *  089._[MNR_____]_0xC80071B0_[23:16]_8_UINT8__mosqnr[15]:_mnr_ctrl_4,____reg_mnr_motion_min,
 *  090._[MNR_____]_0xC80071B0_[31:24]_8_UINT8__mosqnr[16]:_mnr_ctrl_4,____reg_mnr_motion_max,
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M17C0_SetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_BRINGUP
	PE_FWI_M17C0_DNR_DETAIL fw_param;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			#ifndef PE_FOR_M17C0_KDRV_BRINGUP
			LX_PE_NRD_DNR8_DETAIL_T *pp=(LX_PE_NRD_DNR8_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_nrd_hw_m17c0_trace)
			{
				UINT8 *pd = pp->dc_bnr;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"dc_bnr[00]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"dc_bnr[10]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"dc_bnr[20]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"dc_bnr[30]%3d,%3d,%3d,%3d,%3d,%3d,%3d\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36]);
				pd = pp->ac_bnr;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"ac_bnr[00]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"ac_bnr[10]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"ac_bnr[20]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"ac_bnr[30]%3d\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
					pd[30]);
				pd = pp->mosqnr;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"mosqnr[00]%3d,%3d,%3d,%3d,%3d,%3d\n",\
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
				pd = pp->decont;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"decont[00]%3d,%3d,%3d,%3d,%3d\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_DNR0_M17C0_RdFL(mnr_ctrl_1);
				PE_DNR0_M17C0_RdFL(mnr_ctrl_3);
				PE_DNR0_M17C0_RdFL(detail_ctrl);
				#ifndef PE_NRD_HW_M17C0_CVD_PAT_DETECT
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_1);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_2);
				#endif
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_3);
				PE_DNR0_M17C0_RdFL(sc_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(texture_ctrl_0);
				PE_DNR0_M17C0_RdFL(reg_dc_bnr_ctrl_8);
				PE_DNR0_M17C0_RdFL(reg_dc_bnr_ctrl_9);
				PE_DNR0_M17C0_RdFL(reg_dc_bnr_ctrl_10);
				PE_DNR0_M17C0_RdFL(reg_dc_bnr_ctrl_11);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_12);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_1);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_2);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_3);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_4);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_5);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_6);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_7);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_0);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_1);
				/*mosqnr*/
				PE_DNR0_M17C0_Wr01(mnr_ctrl_1, reg_mmd_x_min,				GET_BITS(pp->mosqnr[0],  0, 8));
				PE_DNR0_M17C0_Wr01(mnr_ctrl_1, reg_mmd_x_max,				GET_BITS(pp->mosqnr[1],  0, 8));
				PE_DNR0_M17C0_Wr01(mnr_ctrl_1, reg_mmd_y_min,				GET_BITS(pp->mosqnr[2],  0, 8));
				PE_DNR0_M17C0_Wr01(mnr_ctrl_1, reg_mmd_y_max,				GET_BITS(pp->mosqnr[3],  0, 8));
				PE_DNR0_M17C0_Wr01(mnr_ctrl_3, reg_mmd_scale,				GET_BITS(pp->mosqnr[4],  0, 8));
				PE_DNR0_M17C0_Wr01(mnr_ctrl_3, reg_blur_sel,				GET_BITS(pp->mosqnr[5],  0, 1));

				/*dc_bnr*/
				PE_DNR0_M17C0_Wr01(detail_ctrl, reg_bnr_diff_p,			GET_BITS(pp->dc_bnr[0],  0, 8));
				PE_DNR0_M17C0_Wr01(detail_ctrl, reg_bnr_diff_l,			GET_BITS(pp->dc_bnr[1],  0, 8));

				#ifndef PE_NRD_HW_M17C0_CVD_PAT_DETECT
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_0, reg_dc_motion_min,		GET_BITS(pp->dc_bnr[2],  0, 8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_0, reg_dc_motion_max,		GET_BITS(pp->dc_bnr[3],  0, 8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_0, reg_dc_blur_sel,		GET_BITS(pp->dc_bnr[4],  0, 2));

				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_1, reg_var_cut_resolution, GET_BITS(pp->dc_bnr[5],  0, 4));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_1, reg_var_h_gain,			GET_BITS(pp->dc_bnr[6],  0, 4));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_1, reg_var_v_gain,			GET_BITS(pp->dc_bnr[7],  0, 4));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_1, reg_luma_gain_en,		GET_BITS(pp->dc_bnr[8],  0, 1));
				
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2, reg_dc_protection_th,	GET_BITS(pp->dc_bnr[9],  0, 8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2, reg_dc_protection_en,	GET_BITS(pp->dc_bnr[10],  0, 1));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2, reg_dc_motion_en,		GET_BITS(pp->dc_bnr[11],  0, 1));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2, reg_dc_var_en,			GET_BITS(pp->dc_bnr[12],  0, 1));
				#endif
				
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_3, reg_dc_bnr_var_th0,		GET_BITS(pp->dc_bnr[13],  0, 8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_3, reg_dc_bnr_var_th1,		GET_BITS(pp->dc_bnr[14],  0, 8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_3, reg_dc_bnr_var_th2,		GET_BITS(pp->dc_bnr[15],  0, 8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_3, reg_dc_bnr_var_th3,		GET_BITS(pp->dc_bnr[16],  0, 8));
				
				PE_DNR0_M17C0_Wr01(sc_bnr_ctrl_0, reg_sc_bnr_en,			GET_BITS(pp->dc_bnr[17],  0, 1));

				PE_DNR0_M17C0_Wr01(texture_ctrl_0, reg_cross_th,			GET_BITS(pp->dc_bnr[18],  0, 8));
				PE_DNR0_M17C0_Wr01(texture_ctrl_0, reg_texture_cnt_mul,	GET_BITS(pp->dc_bnr[19],  0, 8));
				PE_DNR0_M17C0_Wr01(texture_ctrl_0, reg_texture_cnt_div,	GET_BITS(pp->dc_bnr[20],  0, 8));

				
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_8, reg_gain_x0,			GET_BITS(pp->dc_bnr[21],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_8, reg_gain_x1,			GET_BITS(pp->dc_bnr[22],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_8, reg_gain_x2,			GET_BITS(pp->dc_bnr[23],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_8, reg_gain_x3,			GET_BITS(pp->dc_bnr[24],  0, 8));

				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_9, reg_gain_x4,			GET_BITS(pp->dc_bnr[25],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_9, reg_gain_x5,			GET_BITS(pp->dc_bnr[26],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_9, reg_gain_x6,			GET_BITS(pp->dc_bnr[27],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_9, reg_gain_x7,			GET_BITS(pp->dc_bnr[28],  0, 8));
				
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_10, reg_gain_y0,			GET_BITS(pp->dc_bnr[29],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_10, reg_gain_y1,			GET_BITS(pp->dc_bnr[30],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_10, reg_gain_y2,			GET_BITS(pp->dc_bnr[31],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_10, reg_gain_y3,			GET_BITS(pp->dc_bnr[32],  0, 8));

				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_11, reg_gain_y4,			GET_BITS(pp->dc_bnr[33],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_11, reg_gain_y5,			GET_BITS(pp->dc_bnr[34],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_11, reg_gain_y6,			GET_BITS(pp->dc_bnr[35],  0, 8));
				PE_DNR0_M17C0_Wr01(reg_dc_bnr_ctrl_11, reg_gain_y7,			GET_BITS(pp->dc_bnr[36],  0, 8));

				/*ac_bnr*/
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_12, reg_bnr_ac_detail_min,		GET_BITS(pp->ac_bnr[0],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_12, reg_bnr_ac_detail_max,		GET_BITS(pp->ac_bnr[1],  0, 8));
				
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_0, reg_bnr_ac_diff_min_h_th,	GET_BITS(pp->ac_bnr[2],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_0, reg_bnr_ac_diff_min_v_th,	GET_BITS(pp->ac_bnr[3],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_0, reg_bnr_ac_acness_resol_h,	GET_BITS(pp->ac_bnr[4],  0, 2));

				
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_1, reg_bnr_ac_h_acness_min, 	GET_BITS(pp->ac_bnr[5],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_1, reg_bnr_ac_h_acness_max,	GET_BITS(pp->ac_bnr[6],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_1, reg_bnr_ac_global_motion_th,GET_BITS(pp->ac_bnr[7],  0, 8));


				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_2, reg_bnr_ac_motion_0,		GET_BITS(pp->ac_bnr[8],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_2, reg_bnr_ac_motion_1,		GET_BITS(pp->ac_bnr[9],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_2, reg_bnr_ac_motion_2,		GET_BITS(pp->ac_bnr[10],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_2, reg_bnr_ac_motion_3,		GET_BITS(pp->ac_bnr[11],  0, 8));

				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_0,		GET_BITS(pp->ac_bnr[12],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_1,		GET_BITS(pp->ac_bnr[13],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_2,		GET_BITS(pp->ac_bnr[14],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_3,		GET_BITS(pp->ac_bnr[15],  0, 8));

				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_4, reg_bnr_ac_v_acness_min,	GET_BITS(pp->ac_bnr[16],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_4, reg_bnr_ac_v_acness_max,	GET_BITS(pp->ac_bnr[17],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_4, reg_bnr_ac_acness_resol_v,	GET_BITS(pp->ac_bnr[18],  0, 8));

				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_5, reg_bnr_ac_detail_th1,		GET_BITS(pp->ac_bnr[19],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_5, reg_bnr_ac_detail_th2,		GET_BITS(pp->ac_bnr[20],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_5, reg_bnr_ac_detail_th3,		GET_BITS(pp->ac_bnr[21],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_5, reg_bnr_ac_detail_th4,		GET_BITS(pp->ac_bnr[22],  0, 8));

				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_6, reg_bnr_ac_detail_gain_th,	GET_BITS(pp->ac_bnr[23],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h0,		GET_BITS(pp->ac_bnr[24],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h1,		GET_BITS(pp->ac_bnr[25],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h2,		GET_BITS(pp->ac_bnr[26],  0, 8));

				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_h3,		GET_BITS(pp->ac_bnr[27],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l0,		GET_BITS(pp->ac_bnr[28],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l1,		GET_BITS(pp->ac_bnr[29],  0, 8));
				PE_DNR0_M17C0_Wr01(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l2,		GET_BITS(pp->ac_bnr[30],  0, 8));

				/*decont*/
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_0, reg_diff_mul,			GET_BITS(pp->decont[0],  0, 8));
				
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_1, reg_var_cut_resolution,	GET_BITS(pp->decont[1],  0, 4));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_1, reg_var_h_gain,			GET_BITS(pp->decont[2],  0, 4));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_1, reg_var_v_gain,			GET_BITS(pp->decont[3],  0, 4));
				PE_DNR0_M17C0_Wr01(reg_decon_ctrl_1, reg_var_chroma_en,		GET_BITS(pp->decont[4],  0, 1));

				PE_DNR0_M17C0_WrFL(mnr_ctrl_1);
				PE_DNR0_M17C0_WrFL(mnr_ctrl_3);
				PE_DNR0_M17C0_WrFL(detail_ctrl);
				#ifndef PE_NRD_HW_M17C0_CVD_PAT_DETECT
				PE_DNR0_M17C0_WrFL(dc_bnr_ctrl_0);
				PE_DNR0_M17C0_WrFL(dc_bnr_ctrl_1);
				PE_DNR0_M17C0_WrFL(dc_bnr_ctrl_2);
				#endif
				PE_DNR0_M17C0_WrFL(dc_bnr_ctrl_3);
				PE_DNR0_M17C0_WrFL(sc_bnr_ctrl_0);
				PE_DNR0_M17C0_WrFL(texture_ctrl_0);
				PE_DNR0_M17C0_WrFL(reg_dc_bnr_ctrl_8);
				PE_DNR0_M17C0_WrFL(reg_dc_bnr_ctrl_9);
				PE_DNR0_M17C0_WrFL(reg_dc_bnr_ctrl_10);
				PE_DNR0_M17C0_WrFL(reg_dc_bnr_ctrl_11);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_12);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_0);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_1);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_2);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_3);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_4);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_5);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_6);
				PE_DNR0_M17C0_WrFL(ac_bnr_ctrl_7);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_0);
				PE_DNR0_M17C0_WrFL(reg_decon_ctrl_1);


				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				/* set user data */
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_1, reg_mmd_x_min,				GET_BITS(pp->mosqnr[0],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_1, reg_mmd_x_max,				GET_BITS(pp->mosqnr[1],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_1, reg_mmd_y_min,				GET_BITS(pp->mosqnr[2],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_1, reg_mmd_y_max,				GET_BITS(pp->mosqnr[3],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_3, reg_mmd_scale,				GET_BITS(pp->mosqnr[4],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(mnr_ctrl_3, reg_blur_sel,				GET_BITS(pp->mosqnr[5],  0, 1));

				/*dc_bnr*/
				//PE_NRD_HW_M17C0_DNR_SET_USER(detail_ctrl, reg_bnr_diff_p,				GET_BITS(pp->dc_bnr[0],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(detail_ctrl, reg_bnr_diff_l,				GET_BITS(pp->dc_bnr[1],  0, 8));

				
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_0, reg_dc_motion_min,		GET_BITS(pp->dc_bnr[2],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_0, reg_dc_motion_max,		GET_BITS(pp->dc_bnr[3],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_0, reg_dc_blur_sel,			GET_BITS(pp->dc_bnr[4],  0, 2));

				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_1, reg_var_cut_resolution, 	GET_BITS(pp->dc_bnr[5],  0, 4));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_1, reg_var_h_gain,			GET_BITS(pp->dc_bnr[6],  0, 4));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_1, reg_var_v_gain,			GET_BITS(pp->dc_bnr[7],  0, 4));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_1, reg_luma_gain_en,			GET_BITS(pp->dc_bnr[8],  0, 1));
				
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_2, reg_dc_protection_th,		GET_BITS(pp->dc_bnr[9],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_2, reg_dc_protection_en,		GET_BITS(pp->dc_bnr[10],  0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_2, reg_dc_motion_en,			GET_BITS(pp->dc_bnr[11],  0, 1));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_2, reg_dc_var_en,			GET_BITS(pp->dc_bnr[12],  0, 1));
				
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_3, reg_dc_bnr_var_th0,		GET_BITS(pp->dc_bnr[13],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_3, reg_dc_bnr_var_th1,		GET_BITS(pp->dc_bnr[14],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_3, reg_dc_bnr_var_th2,		GET_BITS(pp->dc_bnr[15],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_3, reg_dc_bnr_var_th3,		GET_BITS(pp->dc_bnr[16],  0, 8));
				
				PE_NRD_HW_M17C0_DNR_SET_USER(sc_bnr_ctrl_0, reg_sc_bnr_en,			GET_BITS(pp->dc_bnr[17],  0, 1));
				//PE_NRD_HW_M17C0_DNR_SET_USER(texture_ctrl_0, reg_cross_th,				GET_BITS(pp->dc_bnr[18],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(texture_ctrl_0, reg_texture_cnt_mul,		GET_BITS(pp->dc_bnr[19],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(texture_ctrl_0, reg_texture_cnt_div,		GET_BITS(pp->dc_bnr[20],  0, 8));

				
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_8,  reg_gain_x0,				GET_BITS(pp->dc_bnr[21],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_8,  reg_gain_x1,				GET_BITS(pp->dc_bnr[22],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_8,  reg_gain_x2,				GET_BITS(pp->dc_bnr[23],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_8,  reg_gain_x3,				GET_BITS(pp->dc_bnr[24],  0, 8));

				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_9,  reg_gain_x4,				GET_BITS(pp->dc_bnr[25],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_9,  reg_gain_x5,				GET_BITS(pp->dc_bnr[26],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_9,  reg_gain_x6,				GET_BITS(pp->dc_bnr[27],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_9,  reg_gain_x7,				GET_BITS(pp->dc_bnr[28],  0, 8));
				
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_10, reg_gain_y0,				GET_BITS(pp->dc_bnr[29],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_10, reg_gain_y1,				GET_BITS(pp->dc_bnr[30],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_10, reg_gain_y2,				GET_BITS(pp->dc_bnr[31],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_10, reg_gain_y3,				GET_BITS(pp->dc_bnr[32],  0, 8));

				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_11, reg_gain_y4,				GET_BITS(pp->dc_bnr[33],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_11, reg_gain_y5,				GET_BITS(pp->dc_bnr[34],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_11, reg_gain_y6,				GET_BITS(pp->dc_bnr[35],  0, 8));
				//PE_NRD_HW_M17C0_DNR_SET_USER(reg_dc_bnr_ctrl_11, reg_gain_y7,				GET_BITS(pp->dc_bnr[36],  0, 8));

				/*ac_bnr*/
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_12, reg_bnr_ac_detail_min,	GET_BITS(pp->ac_bnr[0],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_12, reg_bnr_ac_detail_max,	GET_BITS(pp->ac_bnr[1],  0, 8));
				
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_0, reg_bnr_ac_diff_min_h_th,	GET_BITS(pp->ac_bnr[2],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_0, reg_bnr_ac_diff_min_v_th,	GET_BITS(pp->ac_bnr[3],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_0, reg_bnr_ac_acness_resol_h,GET_BITS(pp->ac_bnr[4],  0, 2));


				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_1, reg_bnr_ac_h_acness_min, 		GET_BITS(pp->ac_bnr[5],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_1, reg_bnr_ac_h_acness_max,		GET_BITS(pp->ac_bnr[6],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_1, reg_bnr_ac_global_motion_th,	GET_BITS(pp->ac_bnr[7],  0, 8));


				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_2, reg_bnr_ac_motion_0,		GET_BITS(pp->ac_bnr[8],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_2, reg_bnr_ac_motion_1,		GET_BITS(pp->ac_bnr[9],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_2, reg_bnr_ac_motion_2,		GET_BITS(pp->ac_bnr[10],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_2, reg_bnr_ac_motion_3,		GET_BITS(pp->ac_bnr[11],  0, 8));

				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_0,	GET_BITS(pp->ac_bnr[12],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_1,	GET_BITS(pp->ac_bnr[13],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_2,	GET_BITS(pp->ac_bnr[14],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_3,	GET_BITS(pp->ac_bnr[15],  0, 8));

				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_4, reg_bnr_ac_v_acness_min,	GET_BITS(pp->ac_bnr[16],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_4, reg_bnr_ac_v_acness_max,	GET_BITS(pp->ac_bnr[17],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_4, reg_bnr_ac_acness_resol_v,	GET_BITS(pp->ac_bnr[18],  0, 8));

				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_5, reg_bnr_ac_detail_th1,	GET_BITS(pp->ac_bnr[19],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_5, reg_bnr_ac_detail_th2,	GET_BITS(pp->ac_bnr[20],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_5, reg_bnr_ac_detail_th3,	GET_BITS(pp->ac_bnr[21],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_5, reg_bnr_ac_detail_th4,	GET_BITS(pp->ac_bnr[22],  0, 8));

				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_6, reg_bnr_ac_detail_gain_th,GET_BITS(pp->ac_bnr[23],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h0,	GET_BITS(pp->ac_bnr[24],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h1,	GET_BITS(pp->ac_bnr[25],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h2,	GET_BITS(pp->ac_bnr[26],  0, 8));

				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_h3,	GET_BITS(pp->ac_bnr[27],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l0,	GET_BITS(pp->ac_bnr[28],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l1,	GET_BITS(pp->ac_bnr[29],  0, 8));
				PE_NRD_HW_M17C0_DNR_SET_USER(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l2,	GET_BITS(pp->ac_bnr[30],  0, 8));

				#endif //PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				if (PE_CMN_HW_M17C0_GetDbInfo(PE_CMN_HW_M17C0_DB_INF_MD0_DNR_FW_EN, 0))
				{
					memcpy(fw_param.dc_bnr, pp->dc_bnr, sizeof(UINT8)*PE_FWI_M17C0_DNR_DCB_SIZE);
					memcpy(fw_param.ac_bnr, pp->ac_bnr, sizeof(UINT8)*PE_FWI_M17C0_DNR_ACB_SIZE);
					ret = PE_FWI_M17C0_SetDnrDetail(&fw_param);
					PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_FWI_M17C0_SetDnrDetail() error.\n", __F__, __L__);
				}
			}
			#endif
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M17C0_BRINGUP*/
	return ret;
}
/**
 * get dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T
 *  016._[DC_BNR__]_0xC80071C4_[0____]_1_UINT8__dc_bnr[00]:_dc_bnr_ctrl_2,_reg_dc_var_en,
 *  017._[DC_BNR__]_0xC80071C4_[1____]_1_UINT8__dc_bnr[01]:_dc_bnr_ctrl_2,_reg_dc_motion_en,
 *  018._[DC_BNR__]_0xC80071C4_[2____]_1_UINT8__dc_bnr[02]:_dc_bnr_ctrl_2,_reg_dc_protection_en,
 *  019._[DC_BNR__]_0xC80071C4_[3____]_1_UINT8__dc_bnr[03]:_dc_bnr_ctrl_2,_reg_dc_detail_en,
 *  020._[DC_BNR__]_0xC80071BC_[3:2__]_2_UINT8__dc_bnr[04]:_dc_bnr_ctrl_0,_reg_dc_blur_sel,
 *  021._[DC_BNR__]_0xC80071BC_[23:16]_8_UINT8__dc_bnr[05]:_dc_bnr_ctrl_0,_reg_dc_motion_max,
 *  022._[DC_BNR__]_0xC80071BC_[31:24]_8_UINT8__dc_bnr[06]:_dc_bnr_ctrl_0,_reg_dc_motion_min,
 *  023._[DC_BNR__]_0xC80071C0_[7:0__]_8_UINT8__dc_bnr[07]:_dc_bnr_ctrl_1,_reg_dc_detail_max,
 *  024._[DC_BNR__]_0xC80071C0_[15:8_]_8_UINT8__dc_bnr[08]:_dc_bnr_ctrl_1,_reg_dc_detail_min,
 *  025._[DC_BNR__]_0xC80071C0_[23:20]_4_UINT8__dc_bnr[09]:_dc_bnr_ctrl_1,_reg_var_v_gain,
 *  026._[DC_BNR__]_0xC80071C0_[27:24]_4_UINT8__dc_bnr[10]:_dc_bnr_ctrl_1,_reg_var_h_gain,
 *  027._[DC_BNR__]_0xC80071C0_[31:28]_4_UINT8__dc_bnr[11]:_dc_bnr_ctrl_1,_reg_var_cut_resolution,
 *  028._[DC_BNR__]_0xC80071C4_[7:4__]_4_UINT8__dc_bnr[12]:_dc_bnr_ctrl_2,_reg_dc_global_motion_th,
 *  029._[DC_BNR__]_0xC80071C4_[31:24]_8_UINT8__dc_bnr[13]:_dc_bnr_ctrl_2,_reg_dc_protection_th,
 *  030._[DC_BNR__]_0xC80071C8_[7:0__]_8_UINT8__dc_bnr[14]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th3,
 *  031._[DC_BNR__]_0xC80071C8_[15:8_]_8_UINT8__dc_bnr[15]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th2,
 *  032._[DC_BNR__]_0xC80071C8_[23:16]_8_UINT8__dc_bnr[16]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th1,
 *  033._[DC_BNR__]_0xC80071C8_[31:24]_8_UINT8__dc_bnr[17]:_dc_bnr_ctrl_3,_reg_dc_bnr_var_th0,
 *  034._[DC_BNR__]_0xC80071C4_[8____]_1_UINT8__dc_bnr[18]:_dc_bnr_ctrl_2,_reg_detail_sel,
 *  035._[DETAIL__]_0xC80071B8_[7:0__]_8_UINT8__dc_bnr[19]:_detail_ctrl,___reg_bnr_ac_detail_max,
 *  036._[DETAIL__]_0xC80071B8_[15:8_]_8_UINT8__dc_bnr[20]:_detail_ctrl,___reg_bnr_ac_detail_min,
 *  037._[DETAIL__]_0xC80071B8_[23:16]_8_UINT8__dc_bnr[21]:_detail_ctrl,___reg_bnr_diff_l,
 *  038._[DETAIL__]_0xC80071B8_[31:24]_8_UINT8__dc_bnr[22]:_detail_ctrl,___reg_bnr_diff_p,
 *  039._[SC_BNR__]_0xC800726C_[0____]_1_UINT8__dc_bnr[23]:_sc_bnr_ctrl_0,_reg_sc_bnr_en,
 *  040._[SC_BNR__]_0xC8007280_[7:0__]_8_UINT8__dc_bnr[24]:_sc_bnr_ctrl_5,_reg_pos_gain_3,
 *  041._[SC_BNR__]_0xC8007280_[15:8_]_8_UINT8__dc_bnr[25]:_sc_bnr_ctrl_5,_reg_pos_gain_2,
 *  042._[SC_BNR__]_0xC8007280_[23:16]_8_UINT8__dc_bnr[26]:_sc_bnr_ctrl_5,_reg_pos_gain_1,
 *  043._[TEXTURE_]_0xC800728C_[2:0__]_3_UINT8__dc_bnr[27]:_texture_ctrl_0,reg_texture_cnt_div,
 *  044._[TEXTURE_]_0xC800728C_[15:8_]_8_UINT8__dc_bnr[28]:_texture_ctrl_0,reg_texture_cnt_mul,
 *  045._[TEXTURE_]_0xC800728C_[31:24]_8_UINT8__dc_bnr[29]:_texture_ctrl_0,reg_cross_th,
 *  046._[AC_BNR__]_0xC80071D4_[15:8_]_8_UINT8__ac_bnr[00]:_ac_bnr_ctrl_0,_reg_bnr_ac_diff_min_v_th,
 *  047._[AC_BNR__]_0xC80071D4_[23:16]_8_UINT8__ac_bnr[01]:_ac_bnr_ctrl_0,_reg_bnr_ac_diff_min_h_th,
 *  048._[AC_BNR__]_0xC80071D8_[7:0__]_8_UINT8__ac_bnr[02]:_ac_bnr_ctrl_1,_reg_bnr_ac_global_motion_th,
 *  049._[AC_BNR__]_0xC80071D8_[15:8_]_8_UINT8__ac_bnr[03]:_ac_bnr_ctrl_1,_reg_bnr_ac_h_acness_max,
 *  050._[AC_BNR__]_0xC80071E8_[23:16]_8_UINT8__ac_bnr[04]:_ac_bnr_ctrl_4,_reg_bnr_ac_v_acness_max,
 *  051._[AC_BNR__]_0xC80071D8_[23:16]_8_UINT8__ac_bnr[05]:_ac_bnr_ctrl_1,_reg_bnr_ac_h_acness_min,
 *  052._[AC_BNR__]_0xC80071E8_[31:24]_8_UINT8__ac_bnr[06]:_ac_bnr_ctrl_4,_reg_bnr_ac_v_acness_min,
 *  053._[AC_BNR__]_0xC80071E8_[7:6__]_2_UINT8__ac_bnr[07]:_ac_bnr_ctrl_4,_reg_bnr_ac_acness_resol_v,
 *  054._[AC_BNR__]_0xC80071DC_[7:0__]_8_UINT8__ac_bnr[08]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_3,
 *  055._[AC_BNR__]_0xC80071DC_[15:8_]_8_UINT8__ac_bnr[09]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_2,
 *  056._[AC_BNR__]_0xC80071DC_[23:16]_8_UINT8__ac_bnr[10]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_1,
 *  057._[AC_BNR__]_0xC80071DC_[31:24]_8_UINT8__ac_bnr[11]:_ac_bnr_ctrl_2,_reg_bnr_ac_motion_0,
 *  058._[AC_BNR__]_0xC80071E4_[7:0__]_8_UINT8__ac_bnr[12]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_3,
 *  059._[AC_BNR__]_0xC80071E4_[15:8_]_8_UINT8__ac_bnr[13]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_2,
 *  060._[AC_BNR__]_0xC80071E4_[23:16]_8_UINT8__ac_bnr[14]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_1,
 *  061._[AC_BNR__]_0xC80071E4_[31:24]_8_UINT8__ac_bnr[15]:_ac_bnr_ctrl_3,_reg_bnr_ac_motion_y_0,
 *  062._[AC_BNR__]_0xC80071F4_[31:24]_8_UINT8__ac_bnr[16]:_ac_bnr_ctrl_6,_reg_bnr_ac_detail_gain_th,
 *  063._[AC_BNR__]_0xC80071F0_[7:0__]_8_UINT8__ac_bnr[17]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th4,
 *  064._[AC_BNR__]_0xC80071F0_[15:8_]_8_UINT8__ac_bnr[18]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th3,
 *  065._[AC_BNR__]_0xC80071F0_[23:16]_8_UINT8__ac_bnr[19]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th2,
 *  066._[AC_BNR__]_0xC80071F0_[31:24]_8_UINT8__ac_bnr[20]:_ac_bnr_ctrl_5,_reg_bnr_ac_detail_th1,
 *  067._[AC_BNR__]_0xC80071F8_[31:24]_8_UINT8__ac_bnr[21]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_h3,
 *  068._[AC_BNR__]_0xC80071F4_[7:0__]_8_UINT8__ac_bnr[22]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h2,
 *  069._[AC_BNR__]_0xC80071F4_[15:8_]_8_UINT8__ac_bnr[23]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h1,
 *  070._[AC_BNR__]_0xC80071F4_[23:16]_8_UINT8__ac_bnr[24]:_ac_bnr_ctrl_6,_reg_bnr_ac_pos_gain_h0,
 *  071._[AC_BNR__]_0xC80071F8_[7:0__]_8_UINT8__ac_bnr[25]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l2,
 *  072._[AC_BNR__]_0xC80071F8_[15:8_]_8_UINT8__ac_bnr[26]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l1,
 *  073._[AC_BNR__]_0xC80071F8_[23:16]_8_UINT8__ac_bnr[27]:_ac_bnr_ctrl_7,_reg_bnr_ac_pos_gain_l0,
 *  074._[MNR_____]_0xC80071A0_[5:4__]_2_UINT8__mosqnr[00]:_mnr_ctrl_0,____reg_h_expand,
 *  075._[MNR_____]_0xC80071A0_[6____]_1_UINT8__mosqnr[01]:_mnr_ctrl_0,____reg_gain_flt_size,
 *  076._[MNR_____]_0xC80071A4_[7:0__]_8_UINT8__mosqnr[02]:_mnr_ctrl_1,____reg_mnr_s1_mmd_min,
 *  077._[MNR_____]_0xC80071A4_[15:8_]_8_UINT8__mosqnr[03]:_mnr_ctrl_1,____reg_mnr_s2_ratio_min,
 *  078._[MNR_____]_0xC80071A4_[23:16]_8_UINT8__mosqnr[04]:_mnr_ctrl_1,____reg_mnr_s2_ratio_max,
 *  079._[MNR_____]_0xC80071A4_[31:24]_8_UINT8__mosqnr[05]:_mnr_ctrl_1,____reg_mnr_s2_mmd_min,
 *  080._[MNR_____]_0xC80071AC_[7:0__]_8_UINT8__mosqnr[06]:_mnr_ctrl_3,____reg_filter_x0,
 *  081._[MNR_____]_0xC80071AC_[15:8_]_8_UINT8__mosqnr[07]:_mnr_ctrl_3,____reg_filter_x1,
 *  082._[MNR_____]_0xC80071AC_[23:16]_8_UINT8__mosqnr[08]:_mnr_ctrl_3,____reg_filter_y0,
 *  083._[MNR_____]_0xC80071AC_[31:24]_8_UINT8__mosqnr[09]:_mnr_ctrl_3,____reg_filter_y1,
 *  084._[MNR_____]_0xC80071B0_[0____]_1_UINT8__mosqnr[10]:_mnr_ctrl_4,____reg_motion_mnr_en,
 *  085._[MNR_____]_0xC80071B0_[2:1__]_2_UINT8__mosqnr[11]:_mnr_ctrl_4,____reg_motion_mnr_filter,
 *  086._[MNR_____]_0xC80071B0_[4:3__]_2_UINT8__mosqnr[12]:_mnr_ctrl_4,____reg_motion_mnr_filter_c,
 *  087._[MNR_____]_0xC80071B0_[6:5__]_2_UINT8__mosqnr[13]:_mnr_ctrl_4,____reg_mnr_filter,
 *  088._[MNR_____]_0xC80071B0_[8:7__]_2_UINT8__mosqnr[14]:_mnr_ctrl_4,____reg_mnr_filter_c,
 *  089._[MNR_____]_0xC80071B0_[23:16]_8_UINT8__mosqnr[15]:_mnr_ctrl_4,____reg_mnr_motion_min,
 *  090._[MNR_____]_0xC80071B0_[31:24]_8_UINT8__mosqnr[16]:_mnr_ctrl_4,____reg_mnr_motion_max,
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M17C0_GetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_NRD_DNR8_DETAIL_T *pp=(LX_PE_NRD_DNR8_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_DNR0_M17C0_RdFL(mnr_ctrl_1);
				PE_DNR0_M17C0_RdFL(mnr_ctrl_3);
				PE_DNR0_M17C0_RdFL(detail_ctrl);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_1);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_2);
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_3);
				PE_DNR0_M17C0_RdFL(sc_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(texture_ctrl_0);
				PE_DNR0_M17C0_RdFL(reg_dc_bnr_ctrl_8);
				PE_DNR0_M17C0_RdFL(reg_dc_bnr_ctrl_9);
				PE_DNR0_M17C0_RdFL(reg_dc_bnr_ctrl_10);
				PE_DNR0_M17C0_RdFL(reg_dc_bnr_ctrl_11);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_12);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_0);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_1);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_2);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_3);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_4);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_5);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_6);
				PE_DNR0_M17C0_RdFL(ac_bnr_ctrl_7);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_0);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_1);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_2);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_3);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_4);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_5);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_6);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_7);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_8);
				PE_DNR0_M17C0_RdFL(reg_decon_ctrl_9);
				/*mosqnr*/
				PE_DNR0_M17C0_Rd01(mnr_ctrl_1, reg_mmd_x_min,				pp->mosqnr[0]);
				PE_DNR0_M17C0_Rd01(mnr_ctrl_1, reg_mmd_x_max,				pp->mosqnr[1]);
				PE_DNR0_M17C0_Rd01(mnr_ctrl_1, reg_mmd_y_min,				pp->mosqnr[2]);
				PE_DNR0_M17C0_Rd01(mnr_ctrl_1, reg_mmd_y_max,				pp->mosqnr[3]);
				PE_DNR0_M17C0_Rd01(mnr_ctrl_3, reg_mmd_scale,				pp->mosqnr[4]);
				PE_DNR0_M17C0_Rd01(mnr_ctrl_3, reg_blur_sel,				pp->mosqnr[5]);

				/*dc_bnr*/
				PE_DNR0_M17C0_Rd01(detail_ctrl, reg_bnr_diff_p,			pp->dc_bnr[0]);
				PE_DNR0_M17C0_Rd01(detail_ctrl, reg_bnr_diff_l,			pp->dc_bnr[1]);

				
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_0, reg_dc_motion_min,		pp->dc_bnr[2]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_0, reg_dc_motion_max,		pp->dc_bnr[3]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_0, reg_dc_blur_sel,		pp->dc_bnr[4]);

				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_1, reg_var_cut_resolution, pp->dc_bnr[5]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_1, reg_var_h_gain,			pp->dc_bnr[6]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_1, reg_var_v_gain,			pp->dc_bnr[7]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_1, reg_luma_gain_en,		pp->dc_bnr[8]);
				
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_2, reg_dc_protection_th,	pp->dc_bnr[9]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_2, reg_dc_protection_en,	pp->dc_bnr[10]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_2, reg_dc_motion_en,		pp->dc_bnr[11]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_2, reg_dc_var_en,			pp->dc_bnr[12]);
				
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_3, reg_dc_bnr_var_th0,		pp->dc_bnr[13]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_3, reg_dc_bnr_var_th1,		pp->dc_bnr[14]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_3, reg_dc_bnr_var_th2,		pp->dc_bnr[15]);
				PE_DNR0_M17C0_Rd01(dc_bnr_ctrl_3, reg_dc_bnr_var_th3,		pp->dc_bnr[16]);
				
				PE_DNR0_M17C0_Rd01(sc_bnr_ctrl_0, reg_sc_bnr_en,			pp->dc_bnr[17]);
				PE_DNR0_M17C0_Rd01(texture_ctrl_0, reg_cross_th,			pp->dc_bnr[18]);
				PE_DNR0_M17C0_Rd01(texture_ctrl_0, reg_texture_cnt_mul,	pp->dc_bnr[19]);
				PE_DNR0_M17C0_Rd01(texture_ctrl_0, reg_texture_cnt_div,	pp->dc_bnr[20]);

				
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_8,  reg_gain_x0,			pp->dc_bnr[21]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_8,  reg_gain_x1,			pp->dc_bnr[22]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_8,  reg_gain_x2,			pp->dc_bnr[23]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_8,  reg_gain_x3,			pp->dc_bnr[24]);

				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_9,  reg_gain_x4,			pp->dc_bnr[25]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_9,  reg_gain_x5,			pp->dc_bnr[26]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_9,  reg_gain_x6,			pp->dc_bnr[27]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_9,  reg_gain_x7,			pp->dc_bnr[28]);
				
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_10, reg_gain_y0,			pp->dc_bnr[29]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_10, reg_gain_y1,			pp->dc_bnr[30]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_10, reg_gain_y2,			pp->dc_bnr[31]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_10, reg_gain_y3,			pp->dc_bnr[32]);

				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_11, reg_gain_y4,			pp->dc_bnr[33]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_11, reg_gain_y5,			pp->dc_bnr[34]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_11, reg_gain_y6,			pp->dc_bnr[35]);
				PE_DNR0_M17C0_Rd01(reg_dc_bnr_ctrl_11, reg_gain_y7,			pp->dc_bnr[36]);

				/*ac_bnr*/
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_12, reg_bnr_ac_detail_min,		pp->ac_bnr[0]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_12, reg_bnr_ac_detail_max,		pp->ac_bnr[1]);
				
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_0, reg_bnr_ac_diff_min_h_th,	pp->ac_bnr[2]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_0, reg_bnr_ac_diff_min_v_th,	pp->ac_bnr[3]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_0, reg_bnr_ac_acness_resol_h,	pp->ac_bnr[4]);

				
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_1, reg_bnr_ac_h_acness_min, 	pp->ac_bnr[5]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_1, reg_bnr_ac_h_acness_max,	pp->ac_bnr[6]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_1, reg_bnr_ac_global_motion_th,pp->ac_bnr[7]);


				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_2, reg_bnr_ac_motion_0,		pp->ac_bnr[8]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_2, reg_bnr_ac_motion_1,		pp->ac_bnr[9]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_2, reg_bnr_ac_motion_2,		pp->ac_bnr[10]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_2, reg_bnr_ac_motion_3,		pp->ac_bnr[11]);

				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_0,		pp->ac_bnr[12]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_1,		pp->ac_bnr[13]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_2,		pp->ac_bnr[14]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_3, reg_bnr_ac_motion_y_3,		pp->ac_bnr[15]);

				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_4, reg_bnr_ac_v_acness_min,	pp->ac_bnr[16]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_4, reg_bnr_ac_v_acness_max,	pp->ac_bnr[17]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_4, reg_bnr_ac_acness_resol_v,	pp->ac_bnr[18]);

				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_5, reg_bnr_ac_detail_th1,		pp->ac_bnr[19]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_5, reg_bnr_ac_detail_th2,		pp->ac_bnr[20]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_5, reg_bnr_ac_detail_th3,		pp->ac_bnr[21]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_5, reg_bnr_ac_detail_th4,		pp->ac_bnr[22]);

				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_6, reg_bnr_ac_detail_gain_th,	pp->ac_bnr[23]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h0,		pp->ac_bnr[24]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h1,		pp->ac_bnr[25]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_6, reg_bnr_ac_pos_gain_h2,		pp->ac_bnr[26]);

				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_h3,		pp->ac_bnr[27]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l0,		pp->ac_bnr[28]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l1,		pp->ac_bnr[29]);
				PE_DNR0_M17C0_Rd01(ac_bnr_ctrl_7, reg_bnr_ac_pos_gain_l2,		pp->ac_bnr[30]);

				/*decont*/
				
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_0, reg_diff_mul,			pp->decont[0]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_1, reg_var_cut_resolution,	pp->decont[1]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_1, reg_var_h_gain,			pp->decont[2]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_1, reg_var_v_gain,			pp->decont[3]);
				PE_DNR0_M17C0_Rd01(reg_decon_ctrl_1, reg_var_chroma_en,		pp->decont[4]);
			}
			if (_g_nrd_hw_m17c0_trace)
			{
				UINT8 *pd = pp->dc_bnr;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"dc_bnr[00]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"dc_bnr[10]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"dc_bnr[20]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"dc_bnr[30]%3d,%3d,%3d,%3d,%3d,%3d,%3d\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36]);
				pd = pp->ac_bnr;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"ac_bnr[00]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"ac_bnr[10]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"ac_bnr[20]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
					"ac_bnr[30]%3d\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
					pd[30]);
				pd = pp->mosqnr;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"mosqnr[00]%3d,%3d,%3d,%3d,%3d,%3d\n",\
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
				pd = pp->decont;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"decont[00]%3d,%3d,%3d,%3d,%3d\n",\
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4]);
			}
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M17C0_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * - use input struct LX_PE_NRD_TNR5_CMN_T
 *  001._[TNR_MC__]_0xC8004140_[0____]_UINT8__tnr_en_____:__________________reg_tnr_en
 *  002._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[00]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_76,
 *  003._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[01]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_54,
 *  004._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[02]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_32,
 *  005._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[03]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_10,
 *  006._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[04]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_76,
 *  007._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[05]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_54,
 *  008._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[06]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_32,
 *  009._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[07]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_10,
 *  010._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  011._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  012._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  013._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  014._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  015._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  016._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  017._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *  018._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[00]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_76,
 *  019._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[01]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_54,
 *  020._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[02]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_32,
 *  021._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[03]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_10,
 *  022._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[04]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_76,
 *  023._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[05]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_54,
 *  024._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[06]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_32,
 *  025._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[07]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_10,
 *  026._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  027._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  028._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  029._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  030._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  031._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  032._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  033._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *  034._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[00]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_76,
 *  035._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[01]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_54,
 *  036._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[02]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_32,
 *  037._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[03]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_10,
 *  038._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[04]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_76,
 *  039._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[05]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_54,
 *  040._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[06]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_32,
 *  041._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[07]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_10,
 *  042._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  043._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  044._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  045._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  046._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  047._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  048._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  049._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M17C0_SetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	const PE_REG_PARAM_T *p_db = NULL;
	PE_INF_M17C0_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	PE_NRD_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m17c0_info;
	PE_TNL_HW_PARAM_REG_M17C0_T *p_tnl_dflt_b = _g_pe_tnl_hw_param_data_m17c0.reg_dflt.data;
	#define M17C0_TNL_DFT_B(_num)	(p_tnl_dflt_b->tnr_lut_##_num.main_lut_indir_data0)
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
 			LX_PE_NRD_TNR7_CMN_T *pp=(LX_PE_NRD_TNR7_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_nrd_hw_m17c0_trace)
			{
				UINT32 *pd = pp->tnr_lut;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]tnr_en:%d\n", pp->win_id, pp->tnr_en);
				PE_NRD_HW_M17C0_DBG_PRINT( \
				"tnr_lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_lut[08]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
				pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
				pd = pp->tnr_lut_gain;
				PE_NRD_HW_M17C0_DBG_PRINT(\
				"tnr_lut_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
				pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
				pd = pp->tnr_lut_buff;
				PE_NRD_HW_M17C0_DBG_PRINT(\
				"tnr_lut_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_lut_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_lut_buff[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_lut_buff[30]0x%08X,0x%08X\n",\
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
				pd[8],  pd[9],  pd[10], pd[11],	pd[12], pd[13], pd[14], pd[15], \
				pd[16],  pd[17],  pd[18],  pd[19], pd[20],  pd[21],  pd[22],  pd[23], \
				pd[24],  pd[25],  pd[26],  pd[27], pd[28],  pd[29],  pd[30],  pd[31]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* skip drv tnr ctrl, if fw tnr on. */
				if (PE_CMN_HW_M17C0_GetDbInfo(PE_CMN_HW_M17C0_DB_INF_MD0_TNR_FW_EN, 0))
				{
					/* save prev values */
					memcpy(&(pInfo->tnr_cmn), pp, sizeof(LX_PE_NRD_TNR7_CMN_T));
					/* download tnr user db */
					ret = PE_NRD_HW_M17C0_DownloadTnrUserDb((void *)pp);
					PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_M17C0_DownloadTnrUserDb() error.\n",__F__,__L__);
					PE_NRD_HW_M17C0_DBG_PRINT("set tnr lut by firmware\n");
				}
				else
				{
					UINT32 *p_lut = pp->tnr_lut;
					if (pp->tnr_en == 3)					//high
					{
						p_db = tnr_l_lut_user_high_m17c0;
					}
					else if (pp->tnr_en == 2 || pp->tnr_en == 4)//medium, auto
					{
						p_db = tnr_l_lut_user_med_m17c0;
					}
					else if (pp->tnr_en == 1)				//low
					{
						p_db = tnr_l_lut_user_low_m17c0;
					}
					else									//off
					{
						p_db = tnr_l_lut_user_off_m17c0;
					}
					CHECK_KNULL(p_db);
					ret = PE_INF_M17C0_GetCurInfSettings(&inf_set);
					PE_NRD_HW_M17C0_CHECK_CODE(ret,break,"[%s,%d] PE_INF_M17C0_GetCurInfSettings() error.\n",__F__,__L__);
					disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
					PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
					if (pp->tnr_en==0)	//off
					{
						#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
						PE_NRD_HW_M17C0_TNL_WR32(00, p_db[0].data );// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
						PE_NRD_HW_M17C0_TNL_WR32(01, p_db[1].data );// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
						PE_NRD_HW_M17C0_TNL_WR32(02, p_db[2].data );// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
						PE_NRD_HW_M17C0_TNL_WR32(03, p_db[3].data );// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
						PE_NRD_HW_M17C0_TNL_WR32(04, p_db[4].data );// 04. x5y5 x4y4 reg_p2_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(05, p_db[5].data );// 05. x3y3 x2y2 reg_p2_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(06, p_db[6].data );// 06. x1y1 x0y0 reg_p2_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(07, p_lut[0]     );// 07. x7y7 x6y6 reg_detail_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(08, p_lut[1]     );// 08. x5y5 x4y4 reg_detail_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(09, p_lut[2]     );// 09. x3y3 x2y2 reg_detail_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(10, p_lut[3]     );// 10. x1y1 x0y0 reg_detail_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(11, p_lut[4]     );// 11. x7y7 x6y6 reg_detail_cir_pt
						PE_NRD_HW_M17C0_TNL_WR32(12, p_lut[5]     );// 12. x5y5 x4y4 reg_detail_cir_pt
						PE_NRD_HW_M17C0_TNL_WR32(13, p_lut[6]     );// 13. x3y3 x2y2 reg_detail_cir_pt
						PE_NRD_HW_M17C0_TNL_WR32(14, p_lut[7]     );// 14. x1y1 x0y0 reg_detail_cir_pt
						PE_NRD_HW_M17C0_TNL_WR32(15, p_lut[8]     );// 15. x7y7 x6y6 reg_flat_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(16, p_lut[9]     );// 16. x5y5 x4y4 reg_flat_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(17, p_lut[10]    );// 17. x3y3 x2y2 reg_flat_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(18, p_lut[11]    );// 18. x1y1 x0y0 reg_flat_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(19, p_lut[12]    );// 19. x7y7 x6y6 reg_flat_cir_pt
						PE_NRD_HW_M17C0_TNL_WR32(20, p_lut[13]    );// 20. x5y5 x4y4 reg_flat_cir_pt
						PE_NRD_HW_M17C0_TNL_WR32(21, p_lut[14]    );// 21. x3y3 x2y2 reg_flat_cir_pt
						PE_NRD_HW_M17C0_TNL_WR32(22, p_lut[15]    );// 22. x1y1 x0y0 reg_flat_cir_pt
						PE_NRD_HW_M17C0_TNL_WR32(23, p_db[23].data);// 23. x1y1 x0y0 reg_luma_gain_ctrl
						PE_NRD_HW_M17C0_TNL_WR32(24, p_db[24].data);// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
						PE_NRD_HW_M17C0_TNL_WR32(25, p_db[25].data);// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
						PE_NRD_HW_M17C0_TNL_WR32(26, p_db[26].data);// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
						PE_NRD_HW_M17C0_TNL_WR32(27, p_db[27].data);// 27. x1y1 x0y0 reg_skin_motion_ctrl
						PE_NRD_HW_M17C0_TNL_WR32(28, p_db[28].data);// 28. reg_detail_luma_ctrl
						PE_NRD_HW_M17C0_TNL_WR32(29, p_db[29].data);// 29. x3y3 x2y2 reg_NLM_Protect
						PE_NRD_HW_M17C0_TNL_WR32(30, p_db[30].data);// 30. x1y1 x0y0 reg_NLM_Protect
						PE_NRD_HW_M17C0_TNL_WR32(31, p_db[31].data);// 31. x5y5 x4y4 reg_cc_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(32, p_db[32].data);// 32. x3y3 x2y2 reg_cc_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(33, p_db[33].data);// 33. x1y1 x0y0 reg_cc_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(34, p_db[34].data);// 34. x5y5 x4y4 reg_ne_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(35, p_db[35].data);// 35. x3y3 x2y2 reg_ne_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(36, p_db[36].data);// 36. x1y1 x0y0 reg_ne_dist_max_pt
						PE_NRD_HW_M17C0_TNL_WR32(37, p_db[37].data);// 37. eg_skin_gain_ctrl_yy
						PE_NRD_HW_M17C0_TNL_WR32(38, p_db[38].data);// 38. eg_skin_gain_ctrl_cb
						PE_NRD_HW_M17C0_TNL_WR32(39, p_db[39].data);// 39. eg_skin_gain_ctrl_cr
						PE_NRD_HW_M17C0_TNL_WR32(40, p_db[40].data);// 40. eg_skin_motion_ctrl
						PE_NRD_HW_M17C0_TNL_WR32(41, p_db[41].data);// 41. x7y7 x6y6 reg_simple_ma_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(42, p_db[42].data);// 42. x5y5 x4y4 reg_simple_ma_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(43, p_db[43].data);// 43. x3y3 x2y2 reg_simple_ma_iir_pt
						PE_NRD_HW_M17C0_TNL_WR32(44, p_db[44].data);// 44. x1y1 x0y0 reg_simple_ma_iir_pt
						#else						
						PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001000);
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[0].data );// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[1].data );// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[2].data );// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[3].data );// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[4].data );// 04. x5y5 x4y4 reg_p2_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[5].data );// 05. x3y3 x2y2 reg_p2_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[6].data );// 06. x1y1 x0y0 reg_p2_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[0]     );// 07. x7y7 x6y6 reg_detail_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[1]     );// 08. x5y5 x4y4 reg_detail_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[2]     );// 09. x3y3 x2y2 reg_detail_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[3]     );// 10. x1y1 x0y0 reg_detail_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[4]     );// 11. x7y7 x6y6 reg_detail_cir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[5]     );// 12. x5y5 x4y4 reg_detail_cir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[6]     );// 13. x3y3 x2y2 reg_detail_cir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[7]     );// 14. x1y1 x0y0 reg_detail_cir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[8]     );// 15. x7y7 x6y6 reg_flat_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[9]     );// 16. x5y5 x4y4 reg_flat_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[10]    );// 17. x3y3 x2y2 reg_flat_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[11]    );// 18. x1y1 x0y0 reg_flat_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[12]    );// 19. x7y7 x6y6 reg_flat_cir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[13]    );// 20. x5y5 x4y4 reg_flat_cir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[14]    );// 21. x3y3 x2y2 reg_flat_cir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[15]    );// 22. x1y1 x0y0 reg_flat_cir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[23].data);// 23. x1y1 x0y0 reg_luma_gain_ctrl
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[24].data);// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[25].data);// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[26].data);// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[27].data);// 27. x1y1 x0y0 reg_skin_motion_ctrl
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[28].data);// 28. reg_detail_luma_ctrl
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[29].data);// 29. x3y3 x2y2 reg_NLM_Protect
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[30].data);// 30. x1y1 x0y0 reg_NLM_Protect
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[31].data);// 31. x5y5 x4y4 reg_cc_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[32].data);// 32. x3y3 x2y2 reg_cc_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[33].data);// 33. x1y1 x0y0 reg_cc_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[34].data);// 34. x5y5 x4y4 reg_ne_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[35].data);// 35. x3y3 x2y2 reg_ne_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[36].data);// 36. x1y1 x0y0 reg_ne_dist_max_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[37].data);// 37. eg_skin_gain_ctrl_yy
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[38].data);// 38. eg_skin_gain_ctrl_cb
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[39].data);// 39. eg_skin_gain_ctrl_cr
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[40].data);// 40. eg_skin_motion_ctrl
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[41].data);// 41. x7y7 x6y6 reg_simple_ma_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[42].data);// 42. x5y5 x4y4 reg_simple_ma_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[43].data);// 43. x3y3 x2y2 reg_simple_ma_iir_pt
						PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[44].data);// 44. x1y1 x0y0 reg_simple_ma_iir_pt
						#endif
					}
					else
					{
						if(disp0_inf->src_type==LX_PE_SRC_DTV && \
							disp0_inf->fmt_type==LX_PE_FMT_HD && \
							disp0_inf->dtv_type==LX_PE_DTV_CAMERA)
						{
							#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
							PE_NRD_HW_M17C0_TNL_WR32(00, M17C0_TNL_DFT_B(00));// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M17C0_TNL_WR32(01, M17C0_TNL_DFT_B(01));// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M17C0_TNL_WR32(02, M17C0_TNL_DFT_B(02));// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M17C0_TNL_WR32(03, M17C0_TNL_DFT_B(03));// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M17C0_TNL_WR32(04, M17C0_TNL_DFT_B(04));// 04. x5y5 x4y4 reg_p2_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(05, M17C0_TNL_DFT_B(05));// 05. x3y3 x2y2 reg_p2_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(06, M17C0_TNL_DFT_B(06));// 06. x1y1 x0y0 reg_p2_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(07, M17C0_TNL_DFT_B(07));// 07. x7y7 x6y6 reg_detail_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(08, M17C0_TNL_DFT_B(08));// 08. x5y5 x4y4 reg_detail_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(09, M17C0_TNL_DFT_B(09));// 09. x3y3 x2y2 reg_detail_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(10, M17C0_TNL_DFT_B(10));// 10. x1y1 x0y0 reg_detail_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(11, M17C0_TNL_DFT_B(11));// 11. x7y7 x6y6 reg_detail_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(12, M17C0_TNL_DFT_B(12));// 12. x5y5 x4y4 reg_detail_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(13, M17C0_TNL_DFT_B(13));// 13. x3y3 x2y2 reg_detail_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(14, M17C0_TNL_DFT_B(14));// 14. x1y1 x0y0 reg_detail_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(15, M17C0_TNL_DFT_B(15));// 15. x7y7 x6y6 reg_flat_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(16, M17C0_TNL_DFT_B(16));// 16. x5y5 x4y4 reg_flat_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(17, M17C0_TNL_DFT_B(17));// 17. x3y3 x2y2 reg_flat_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(18, M17C0_TNL_DFT_B(18));// 18. x1y1 x0y0 reg_flat_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(19, M17C0_TNL_DFT_B(19));// 19. x7y7 x6y6 reg_flat_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(20, M17C0_TNL_DFT_B(20));// 20. x5y5 x4y4 reg_flat_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(21, M17C0_TNL_DFT_B(21));// 21. x3y3 x2y2 reg_flat_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(22, M17C0_TNL_DFT_B(22));// 22. x1y1 x0y0 reg_flat_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(23, M17C0_TNL_DFT_B(23));// 23. x1y1 x0y0 reg_luma_gain_ctrl
							PE_NRD_HW_M17C0_TNL_WR32(24, M17C0_TNL_DFT_B(24));// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
							PE_NRD_HW_M17C0_TNL_WR32(25, M17C0_TNL_DFT_B(25));// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
							PE_NRD_HW_M17C0_TNL_WR32(26, M17C0_TNL_DFT_B(26));// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
							PE_NRD_HW_M17C0_TNL_WR32(27, M17C0_TNL_DFT_B(27));// 27. x1y1 x0y0 reg_skin_motion_ctrl
							PE_NRD_HW_M17C0_TNL_WR32(28, M17C0_TNL_DFT_B(28));// 28. reg_detail_luma_ctrl
							PE_NRD_HW_M17C0_TNL_WR32(29, M17C0_TNL_DFT_B(29));// 29. x3y3 x2y2 reg_NLM_Protect
							PE_NRD_HW_M17C0_TNL_WR32(30, M17C0_TNL_DFT_B(30));// 30. x1y1 x0y0 reg_NLM_Protect
							PE_NRD_HW_M17C0_TNL_WR32(31, M17C0_TNL_DFT_B(31));// 31. x5y5 x4y4 reg_cc_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(32, M17C0_TNL_DFT_B(32));// 32. x3y3 x2y2 reg_cc_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(33, M17C0_TNL_DFT_B(33));// 33. x1y1 x0y0 reg_cc_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(34, M17C0_TNL_DFT_B(34));// 34. x5y5 x4y4 reg_ne_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(35, M17C0_TNL_DFT_B(35));// 35. x3y3 x2y2 reg_ne_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(36, M17C0_TNL_DFT_B(36));// 36. x1y1 x0y0 reg_ne_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(37, M17C0_TNL_DFT_B(37));// 37. eg_skin_gain_ctrl_yy
							PE_NRD_HW_M17C0_TNL_WR32(38, M17C0_TNL_DFT_B(38));// 38. eg_skin_gain_ctrl_cb
							PE_NRD_HW_M17C0_TNL_WR32(39, M17C0_TNL_DFT_B(39));// 39. eg_skin_gain_ctrl_cr
							PE_NRD_HW_M17C0_TNL_WR32(40, M17C0_TNL_DFT_B(40));// 40. eg_skin_motion_ctrl
							PE_NRD_HW_M17C0_TNL_WR32(41, p_db[41].data  );// 41. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(42, p_db[42].data  );// 42. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(43, p_db[43].data  );// 43. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(44, p_db[44].data  );// 44. x1y1 x0y0 reg_simple_ma_iir_pt
							#else
							//PE_ND0_M17C0_QWr01(tnr_main_lut_00, main_lut_indir_addr, 0x29  );//41
							PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001029);
							PE_ND0_M17C0_QWr(tnr_main_lut_01, p_db[41].data  );// 39. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01, p_db[42].data  );// 40. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01, p_db[43].data  );// 41. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01, p_db[44].data  );// 42. x1y1 x0y0 reg_simple_ma_iir_pt
							#endif
						}
						else
						{
							
							#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
							PE_NRD_HW_M17C0_TNL_WR32(00, M17C0_TNL_DFT_B(00));// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M17C0_TNL_WR32(01, M17C0_TNL_DFT_B(01));// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M17C0_TNL_WR32(02, M17C0_TNL_DFT_B(02));// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M17C0_TNL_WR32(03, M17C0_TNL_DFT_B(03));// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M17C0_TNL_WR32(04, M17C0_TNL_DFT_B(04));// 04. x5y5 x4y4 reg_p2_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(05, M17C0_TNL_DFT_B(05));// 05. x3y3 x2y2 reg_p2_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(06, M17C0_TNL_DFT_B(06));// 06. x1y1 x0y0 reg_p2_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(07, p_lut[0]       );// 07. x7y7 x6y6 reg_detail_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(08, p_lut[1]       );// 08. x5y5 x4y4 reg_detail_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(09, p_lut[2]       );// 09. x3y3 x2y2 reg_detail_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(10, p_lut[3]       );// 10. x1y1 x0y0 reg_detail_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(11, p_lut[4]       );// 11. x7y7 x6y6 reg_detail_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(12, p_lut[5]       );// 12. x5y5 x4y4 reg_detail_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(13, p_lut[6]       );// 13. x3y3 x2y2 reg_detail_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(14, p_lut[7]       );// 14. x1y1 x0y0 reg_detail_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(15, p_lut[8]       );// 15. x7y7 x6y6 reg_flat_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(16, p_lut[9]       );// 16. x5y5 x4y4 reg_flat_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(17, p_lut[10]      );// 17. x3y3 x2y2 reg_flat_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(18, p_lut[11]      );// 18. x1y1 x0y0 reg_flat_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(19, p_lut[12]      );// 19. x7y7 x6y6 reg_flat_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(20, p_lut[13]      );// 20. x5y5 x4y4 reg_flat_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(21, p_lut[14]      );// 21. x3y3 x2y2 reg_flat_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(22, p_lut[15]      );// 22. x1y1 x0y0 reg_flat_cir_pt
							PE_NRD_HW_M17C0_TNL_WR32(23, M17C0_TNL_DFT_B(23));// 23. x1y1 x0y0 reg_luma_gain_ctrl
							PE_NRD_HW_M17C0_TNL_WR32(24, M17C0_TNL_DFT_B(24));// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
							PE_NRD_HW_M17C0_TNL_WR32(25, M17C0_TNL_DFT_B(25));// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
							PE_NRD_HW_M17C0_TNL_WR32(26, M17C0_TNL_DFT_B(26));// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
							PE_NRD_HW_M17C0_TNL_WR32(27, M17C0_TNL_DFT_B(27));// 27. x1y1 x0y0 reg_skin_motion_ctrl
							PE_NRD_HW_M17C0_TNL_WR32(28, M17C0_TNL_DFT_B(28));// 28. reg_detail_luma_ctrl
							PE_NRD_HW_M17C0_TNL_WR32(29, M17C0_TNL_DFT_B(29));// 29. x3y3 x2y2 reg_NLM_Protect
							PE_NRD_HW_M17C0_TNL_WR32(30, M17C0_TNL_DFT_B(30));// 30. x1y1 x0y0 reg_NLM_Protect
							PE_NRD_HW_M17C0_TNL_WR32(31, M17C0_TNL_DFT_B(31));// 31. x5y5 x4y4 reg_cc_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(32, M17C0_TNL_DFT_B(32));// 32. x3y3 x2y2 reg_cc_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(33, M17C0_TNL_DFT_B(33));// 33. x1y1 x0y0 reg_cc_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(34, M17C0_TNL_DFT_B(34));// 34. x5y5 x4y4 reg_ne_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(35, M17C0_TNL_DFT_B(35));// 35. x3y3 x2y2 reg_ne_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(36, M17C0_TNL_DFT_B(36));// 36. x1y1 x0y0 reg_ne_dist_max_pt
							PE_NRD_HW_M17C0_TNL_WR32(37, M17C0_TNL_DFT_B(37));// 37. eg_skin_gain_ctrl_yy
							PE_NRD_HW_M17C0_TNL_WR32(38, M17C0_TNL_DFT_B(38));// 38. eg_skin_gain_ctrl_cb
							PE_NRD_HW_M17C0_TNL_WR32(39, M17C0_TNL_DFT_B(39));// 39. eg_skin_gain_ctrl_cr
							PE_NRD_HW_M17C0_TNL_WR32(40, M17C0_TNL_DFT_B(40));// 40. eg_skin_motion_ctrl
							PE_NRD_HW_M17C0_TNL_WR32(41, p_db[41].data  );// 41. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(42, p_db[42].data  );// 42. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(43, p_db[43].data  );// 43. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_NRD_HW_M17C0_TNL_WR32(44, p_db[44].data  );// 44. x1y1 x0y0 reg_simple_ma_iir_pt
							#else
							//PE_ND0_M17C0_QWr01(tnr_main_lut_00, main_lut_indir_addr, 0x7  );//0x7
							PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001007);
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[0]       );// 07. x7y7 x6y6 reg_detail_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[1]       );// 08. x5y5 x4y4 reg_detail_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[2]       );// 09. x3y3 x2y2 reg_detail_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[3]       );// 10. x1y1 x0y0 reg_detail_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[4]       );// 11. x7y7 x6y6 reg_detail_cir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[5]       );// 12. x5y5 x4y4 reg_detail_cir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[6]       );// 13. x3y3 x2y2 reg_detail_cir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[7]       );// 14. x1y1 x0y0 reg_detail_cir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[8]       );// 15. x7y7 x6y6 reg_flat_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[9]       );// 16. x5y5 x4y4 reg_flat_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[10]      );// 17. x3y3 x2y2 reg_flat_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[11]      );// 18. x1y1 x0y0 reg_flat_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[12]      );// 19. x7y7 x6y6 reg_flat_cir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[13]      );// 20. x5y5 x4y4 reg_flat_cir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[14]      );// 21. x3y3 x2y2 reg_flat_cir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_lut[15]      );// 22. x1y1 x0y0 reg_flat_cir_pt
							//PE_ND0_M17C0_QWr01(tnr_main_lut_00, main_lut_indir_addr, 0x29  );//41
							PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00001029);
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[41].data  );// 39. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[42].data  );// 40. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[43].data  );// 41. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_ND0_M17C0_QWr(tnr_main_lut_01,  p_db[44].data  );// 42. x1y1 x0y0 reg_simple_ma_iir_pt
							#endif
						}
					}
					PE_ND0_M17C0_QWr(tnr_main_lut_00, 0x00008000);
					/* save prev values */
					memcpy(&(pInfo->tnr_cmn), pp, sizeof(LX_PE_NRD_TNR7_CMN_T));
					/* download tnr user db */
					ret = PE_NRD_HW_M17C0_DownloadTnrUserDb((void *)pp);
					PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_M17C0_DownloadTnrUserDb() error.\n",__F__,__L__);
					PE_NRD_HW_M17C0_DBG_PRINT("set tnr lut by driver\n");
				}
			}
 		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get tnr common ctrl
 * - use input struct LX_PE_NRD_TNR5_CMN_T
 *  001._[TNR_MC__]_0xC8004140_[0____]_UINT8__tnr_en_____:__________________reg_tnr_en
 *  002._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[00]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_76,
 *  003._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[01]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_54,
 *  004._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[02]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_32,
 *  005._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[03]_:_tnr_main_lut_01,_eg_detail_iir_pt_luma_10,
 *  006._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[04]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_76,
 *  007._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[05]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_54,
 *  008._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[06]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_32,
 *  009._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[07]_:_tnr_main_lut_01,_eg_detail_iir_pt_chroma_10,
 *  010._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  011._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  012._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  013._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  014._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  015._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  016._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  017._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_lm[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *  018._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[00]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_76,
 *  019._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[01]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_54,
 *  020._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[02]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_32,
 *  021._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[03]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_10,
 *  022._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[04]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_76,
 *  023._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[05]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_54,
 *  024._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[06]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_32,
 *  025._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[07]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_10,
 *  026._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  027._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  028._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  029._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  030._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  031._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  032._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  033._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_ui[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *  034._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[00]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_76,
 *  035._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[01]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_54,
 *  036._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[02]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_32,
 *  037._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[03]_:_tnr_main_lut_01,_reg_detail_iir_pt_luma_10,
 *  038._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[04]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_76,
 *  039._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[05]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_54,
 *  040._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[06]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_32,
 *  041._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[07]_:_tnr_main_lut_01,_reg_detail_iir_pt_chroma_10,
 *  042._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[08]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_76,
 *  043._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[09]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_54,
 *  044._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[10]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_32,
 *  045._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[11]_:_tnr_main_lut_01,_reg_flat_iir_pt_luma_10,
 *  046._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[12]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_76,
 *  047._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[13]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_54,
 *  048._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[14]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_32,
 *  049._[TNR_MC__]_0xc80041d4_[31:0_]_UINT32_lut_hm[15]_:_tnr_main_lut_01,_reg_flat_iir_pt_chroma_10,
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M17C0_GetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_NRD_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m17c0_info;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_NRD_TNR7_CMN_T *pp=(LX_PE_NRD_TNR7_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				memcpy(pp, &(pInfo->tnr_cmn), sizeof(LX_PE_NRD_TNR7_CMN_T));
			}
			if (_g_nrd_hw_m17c0_trace)
			{
				UINT32 *pd = pp->tnr_lut;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]tnr_en:%d\n", pp->win_id, pp->tnr_en);
				PE_NRD_HW_M17C0_DBG_PRINT( \
				"tnr_lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_lut[08]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
				pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
				pd = pp->tnr_lut_gain;
				PE_NRD_HW_M17C0_DBG_PRINT(\
				"tnr_lut_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
				pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
				pd = pp->tnr_lut_buff;
				PE_NRD_HW_M17C0_DBG_PRINT(\
				"tnr_lut_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_lut_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_lut_buff[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_lut_buff[30]0x%08X,0x%08X\n",\
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
				pd[8],  pd[9],  pd[10], pd[11],	pd[12], pd[13], pd[14], pd[15], \
				pd[16],  pd[17],  pd[18],  pd[19], pd[20],  pd[21],  pd[22],  pd[23], \
				pd[24],  pd[25],  pd[26],  pd[27], pd[28],  pd[29],  pd[30],  pd[31]);
			}
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR6_DETAIL_T M17C0
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M17C0_SetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_BRINGUP
	PE_NRD_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m17c0_info;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_NRD_TNR6_DETAIL_T *pp=(LX_PE_NRD_TNR6_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_nrd_hw_m17c0_trace)
			{
				
				UINT8 *pd = pp->tnr_ctl;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"tnr_ctl[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"tnr_ctl[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"tnr_ctl[20]%3d\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20]);
				#ifdef PE_NRD_HW_M17C0_TNR_MAE_CHANGE
				pd = pp->tnr_mae;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"tnr_mae[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"tnr_mae[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"tnr_mae[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
				#endif
				pd = pp->tnr__mc;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"m_c[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"m_c[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"m_c[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"m_c[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"m_c[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"m_c[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39], \
					pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49], \
					pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57]);
				pd = pp->tnr_edf;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"edf[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"edf[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"edf[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"edf[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35]);
				pd = pp->tnr_bld;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
					"bld[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"bld[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"bld[20]0x%08X,0x%08X,0x%08X,0x%08X\n", \
					pp->win_id, \
					pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
					pd[20], pd[21], pd[22], pd[23]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* set reg */
				PE_ND0_M17C0_RdFL(tnr_ctrl_00);
				PE_ND0_M17C0_RdFL(tnr_ctrl_02);
				PE_ND0_M17C0_RdFL(tnr_ctrl_05);
				PE_ND0_M17C0_RdFL(tnr_ctrl_06);
				PE_ND0_M17C0_RdFL(tnr_ctrl_21);
				
				#ifdef PE_NRD_HW_M17C0_TNR_MAE_CHANGE
				PE_ND0_M17C0_RdFL(tnr_ctrl_07);
				PE_ND0_M17C0_RdFL(tnr_ctrl_09);
				PE_ND0_M17C0_RdFL(tnr_ctrl_11);
				PE_ND0_M17C0_RdFL(tnr_ctrl_16);
				PE_ND0_M17C0_RdFL(tnr_ctrl_18);
				PE_ND0_M17C0_RdFL(tnr_ctrl_19);
				#endif
				
				PE_ND0_M17C0_RdFL(tnr_ctrl_24);
				PE_ND0_M17C0_RdFL(tnr_ctrl_25);
				PE_ND0_M17C0_RdFL(tnr_ctrl_26);
				PE_ND0_M17C0_RdFL(tnr_ctrl_28);
				PE_ND0_M17C0_RdFL(tnr_ctrl_29);
				PE_ND0_M17C0_RdFL(tnr_ctrl_30);
				PE_ND0_M17C0_RdFL(tnr_ctrl_31);
				PE_ND0_M17C0_RdFL(tnr_ctrl_32);
				PE_ND0_M17C0_RdFL(tnr_ctrl_33);
				PE_ND0_M17C0_RdFL(tnr_ctrl_40);
				PE_ND0_M17C0_RdFL(tnr_ctrl_41);
				PE_ND0_M17C0_RdFL(tnr_ctrl_42);
				PE_ND0_M17C0_RdFL(tnr_ctrl_43);
				PE_ND0_M17C0_RdFL(tnr_ctrl_44);
				PE_ND0_M17C0_RdFL(tnr_ctrl_45);
				PE_ND0_M17C0_RdFL(tnr_ctrl_46);
				PE_ND0_M17C0_RdFL(tnr_ctrl_47);
				
				PE_ND0_M17C0_RdFL(tnr_ctrl_20);
				PE_ND0_M17C0_RdFL(tnr_ctrl_56);
				PE_ND0_M17C0_RdFL(tnr_ctrl_57);
				PE_ND0_M17C0_RdFL(tnr_ctrl_58);
				PE_ND0_M17C0_RdFL(tnr_ctrl_59);
				PE_ND0_M17C0_RdFL(tnr_ctrl_60);
				PE_ND0_M17C0_RdFL(tnr_ctrl_61);

				/*tnr_ctl*/
				PE_ND0_M17C0_Wr01(tnr_ctrl_00, reg_sad_8x3_iir_alpha,      GET_BITS(pp->tnr_ctl[0],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_00, reg_sad_8x3_chroma_en,      GET_BITS(pp->tnr_ctl[1],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_00, reg_sad_8x3_iir_en,         GET_BITS(pp->tnr_ctl[2],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_00, reg_sad_8x3_res,            GET_BITS(pp->tnr_ctl[3],  0, 2));
				
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_th_memc,                 GET_BITS(pp->tnr_ctl[4],  0, 8));
				#ifndef PE_NRD_HW_M17C0_CVD_PAT_DETECT
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_th_ma,                   GET_BITS(pp->tnr_ctl[5],  0, 8));
				#endif
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_out_mode,                GET_BITS(pp->tnr_ctl[6],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_chroma_gain,             GET_BITS(pp->tnr_ctl[7],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_max_flt_tap,             GET_BITS(pp->tnr_ctl[8],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_scale,                   GET_BITS(pp->tnr_ctl[9],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_chroma_en,               GET_BITS(pp->tnr_ctl[10],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_calc_prev_hist,          GET_BITS(pp->tnr_ctl[11],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_max_flt_en,              GET_BITS(pp->tnr_ctl[12],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_02, sc_en,              		   GET_BITS(pp->tnr_ctl[13],  0, 1));

				PE_ND0_M17C0_Wr01(tnr_ctrl_05, reg_mamc_mc_sad_cut,              GET_BITS(pp->tnr_ctl[14],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_05, reg_mamc_ma_sad_cut,              GET_BITS(pp->tnr_ctl[15],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_05, reg_mamc_blend_mv_max_or_sum,     GET_BITS(pp->tnr_ctl[16],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_05, reg_mamc_blend_mode,              GET_BITS(pp->tnr_ctl[17],  0, 2));

				PE_ND0_M17C0_Wr01(tnr_ctrl_06, reg_me_pv_base,              GET_BITS(pp->tnr_ctl[18],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_06, reg_me_lb_base,              GET_BITS(pp->tnr_ctl[19],  0, 8));
				
				PE_ND0_M17C0_Wr01(tnr_ctrl_21, reg_svar_scale,              GET_BITS(pp->tnr_ctl[20],  0, 3));

				/*tnr_mae*/
				#ifdef PE_NRD_HW_M17C0_TNR_MAE_CHANGE
				#ifndef PE_NRD_HW_M17C0_CVD_PAT_DETECT
				PE_ND0_M17C0_Wr01(tnr_ctrl_07, reg_5x5_sad_cut,         GET_BITS(pp->tnr_mae[1],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_07, reg_sc_en,              	GET_BITS(pp->tnr_mae[0],  0, 1));
				#endif

				PE_ND0_M17C0_Wr01(tnr_ctrl_09, reg_pv_smooth_clip,      GET_BITS(pp->tnr_mae[2],  0, 6));
				PE_ND0_M17C0_Wr01(tnr_ctrl_09, reg_lb_smooth_clip,      GET_BITS(pp->tnr_mae[3],  0, 6));
				PE_ND0_M17C0_Wr01(tnr_ctrl_09, reg_sad_base,           	GET_BITS(pp->tnr_mae[4],  0, 7));

				PE_ND0_M17C0_Wr01(tnr_ctrl_11, reg_me_n15_protection,	GET_BITS(pp->tnr_mae[5],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, reg_zero_sad_adv,		GET_BITS(pp->tnr_mae[6],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, reg_zero_sad_ratio,		GET_BITS(pp->tnr_mae[7],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, reg_mv_fb_reverse,		GET_BITS(pp->tnr_mae[8],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, pv_mv_v_off,				GET_BITS(pp->tnr_mae[9],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, pv_mv_h_off,				GET_BITS(pp->tnr_mae[10],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, lb_mv_v_off,				GET_BITS(pp->tnr_mae[11],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, lb_mv_h_off,				GET_BITS(pp->tnr_mae[12],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, pv_smooth_en,			GET_BITS(pp->tnr_mae[13],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_11, lb_smooth_en,			GET_BITS(pp->tnr_mae[14],  0, 1));

				PE_ND0_M17C0_Wr01(tnr_ctrl_16, reg_sad_acc_mode,		GET_BITS(pp->tnr_mae[15],  0, 2));

				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_bmv_pmv_tl_en,		GET_BITS(pp->tnr_mae[16],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_bmv_pmv_tl,			GET_BITS(pp->tnr_mae[17],  0, 7));
				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_bmv_gmv_tl_en,		GET_BITS(pp->tnr_mae[18],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_bmv_gmv_tl,			GET_BITS(pp->tnr_mae[19],  0, 7));
				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_gmv_gmv_tl_en,		GET_BITS(pp->tnr_mae[20],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_gmv_gmv_tl,			GET_BITS(pp->tnr_mae[21],  0, 7));
				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_gsad_scale,			GET_BITS(pp->tnr_mae[22],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_bmv_rst_mode,		GET_BITS(pp->tnr_mae[23],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_18, reg_bsad_scale,			GET_BITS(pp->tnr_mae[24],  0, 3));

				PE_ND0_M17C0_Wr01(tnr_ctrl_19, bmv_0mv_tl_en,			GET_BITS(pp->tnr_mae[25],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_19, bmv_0mv_tl,				GET_BITS(pp->tnr_mae[26],  0, 7));
				PE_ND0_M17C0_Wr01(tnr_ctrl_19, gmv_0mv_tl_en,			GET_BITS(pp->tnr_mae[27],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_19, gmv_0mv_tl,				GET_BITS(pp->tnr_mae[28],  0, 7));
				PE_ND0_M17C0_Wr01(tnr_ctrl_19, bmv_coring_th,			GET_BITS(pp->tnr_mae[29],  0, 8));
				#endif

				/*tnr_mc*/
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_chroma_sad_en,			GET_BITS(pp->tnr__mc[0],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_cnt_mode,				GET_BITS(pp->tnr__mc[1],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_avg_cmp_res,			GET_BITS(pp->tnr__mc[2],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_avg_cmp_en,			GET_BITS(pp->tnr__mc[3],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_5x5_sad_cut,			GET_BITS(pp->tnr__mc[4],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_sad_sum_cut,			GET_BITS(pp->tnr__mc[5],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_chroma_sad_res,		GET_BITS(pp->tnr__mc[6],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_crgn_gain_en,			GET_BITS(pp->tnr__mc[7],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_luma_gain_en,			GET_BITS(pp->tnr__mc[8],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_ombc_en,				GET_BITS(pp->tnr__mc[9],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_24, reg_p2f_mode,				GET_BITS(pp->tnr__mc[10],  0, 1));

				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g22,			GET_BITS(pp->tnr__mc[11],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g21,			GET_BITS(pp->tnr__mc[12],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g20,			GET_BITS(pp->tnr__mc[13],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g12,			GET_BITS(pp->tnr__mc[14],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g11,			GET_BITS(pp->tnr__mc[15],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g10,			GET_BITS(pp->tnr__mc[16],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g02,			GET_BITS(pp->tnr__mc[17],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g01,			GET_BITS(pp->tnr__mc[18],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, reg_pre_blur_g00,			GET_BITS(pp->tnr__mc[19],  0, 4));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, cut_resolution,			GET_BITS(pp->tnr__mc[20],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_25, pre_blur_en,				GET_BITS(pp->tnr__mc[21],  0, 1));

				
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g22,			GET_BITS(pp->tnr__mc[22],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g21,			GET_BITS(pp->tnr__mc[23],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g20,			GET_BITS(pp->tnr__mc[24],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g12,			GET_BITS(pp->tnr__mc[25],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g11,			GET_BITS(pp->tnr__mc[26],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g10,			GET_BITS(pp->tnr__mc[27],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g02,			GET_BITS(pp->tnr__mc[28],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g01,			GET_BITS(pp->tnr__mc[29],  0, 3));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, reg_pre_blur_g00,			GET_BITS(pp->tnr__mc[30],  0, 4));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, cut_resolution,			GET_BITS(pp->tnr__mc[31],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_26, pre_blur_en,				GET_BITS(pp->tnr__mc[32],  0, 1));

				PE_ND0_M17C0_Wr01(tnr_ctrl_28, reg_pre_detail_cttl_g1,	GET_BITS(pp->tnr__mc[33],  0, 5));
				PE_ND0_M17C0_Wr01(tnr_ctrl_28, reg_pre_detail_cttl_g2,	GET_BITS(pp->tnr__mc[34],  0, 5));
				PE_ND0_M17C0_Wr01(tnr_ctrl_28, reg_pre_detail_cttl_g3,	GET_BITS(pp->tnr__mc[35],  0, 5));
				PE_ND0_M17C0_Wr01(tnr_ctrl_28, reg_pre_detail_cttl_g4,	GET_BITS(pp->tnr__mc[36],  0, 5));
				PE_ND0_M17C0_Wr01(tnr_ctrl_28, reg_pre_detail_cttl_g0,	GET_BITS(pp->tnr__mc[37],  0, 7));
				PE_ND0_M17C0_Wr01(tnr_ctrl_28, cut_resolution,			GET_BITS(pp->tnr__mc[38],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_28, luma_gain_en,				GET_BITS(pp->tnr__mc[39],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_28, pre_filtered_en,			GET_BITS(pp->tnr__mc[40],  0, 1));


				PE_ND0_M17C0_Wr01(tnr_ctrl_29, r_diff_limit,				GET_BITS(pp->tnr__mc[41],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_29, r_master_gain,				GET_BITS(pp->tnr__mc[42],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_29, r_master_en,				GET_BITS(pp->tnr__mc[43],  0, 1));


				PE_ND0_M17C0_Wr01(tnr_ctrl_30, reg_denoise_ctrl_g0,		GET_BITS(pp->tnr__mc[44],  0, 7));
				PE_ND0_M17C0_Wr01(tnr_ctrl_30, reg_denoise_gain,			GET_BITS(pp->tnr__mc[45],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_30, reg_cut_resolution,		GET_BITS(pp->tnr__mc[46],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_30, reg_pre_filtered_en,		GET_BITS(pp->tnr__mc[47],  0, 1));


				PE_ND0_M17C0_Wr01(tnr_ctrl_31, reg_denoise_ctrl_g1,		GET_BITS(pp->tnr__mc[48],  0, 5));
				PE_ND0_M17C0_Wr01(tnr_ctrl_31, reg_denoise_ctrl_g2,		GET_BITS(pp->tnr__mc[49],  0, 5));
				PE_ND0_M17C0_Wr01(tnr_ctrl_31, reg_denoise_ctrl_g3,		GET_BITS(pp->tnr__mc[50],  0, 5));
				PE_ND0_M17C0_Wr01(tnr_ctrl_31, reg_denoise_ctrl_g4,		GET_BITS(pp->tnr__mc[51],  0, 5));



				PE_ND0_M17C0_Wr01(tnr_ctrl_32, reg_blur_coef,		GET_BITS(pp->tnr__mc[52],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_32, reg_gf_gain,		GET_BITS(pp->tnr__mc[53],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_33, same_sad_th,		GET_BITS(pp->tnr__mc[54],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_33, move_step,			GET_BITS(pp->tnr__mc[55],  0, 4));
				PE_ND0_M17C0_Wr01(tnr_ctrl_33, p_mv0_only,		GET_BITS(pp->tnr__mc[56],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_33, same_protection_en,GET_BITS(pp->tnr__mc[57],  0, 1));



				/*tnr_edf*/

				PE_ND0_M17C0_Wr01(tnr_ctrl_40, reg_cross_th,			GET_BITS(pp->tnr_edf[0],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_40, reg_cross_th_ne,		GET_BITS(pp->tnr_edf[1],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_40, reg_ne_normalize_en,	GET_BITS(pp->tnr_edf[2],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_40, reg_t_cut_resolution,	GET_BITS(pp->tnr_edf[3],  0, 2));
				PE_ND0_M17C0_Wr01(tnr_ctrl_40, reg_t_normalize_en,	GET_BITS(pp->tnr_edf[4],  0, 1));
				PE_ND0_M17C0_Wr01(tnr_ctrl_40, reg_a_normalize_en,	GET_BITS(pp->tnr_edf[5],  0, 1));

				PE_ND0_M17C0_Wr01(tnr_ctrl_41, reg_mul_base_e,	GET_BITS(pp->tnr_edf[6],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_41, reg_mul_base_t,	GET_BITS(pp->tnr_edf[7],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_42, reg_a_lut_edge_x1,	GET_BITS(pp->tnr_edf[8],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_42, reg_a_lut_edge_y1,	GET_BITS(pp->tnr_edf[9],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_42, reg_a_lut_edge_x0,	GET_BITS(pp->tnr_edf[10],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_42, reg_a_lut_edge_y0,	GET_BITS(pp->tnr_edf[11],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_43, reg_a_lut_detail_x1, GET_BITS(pp->tnr_edf[12],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_43, reg_a_lut_detail_y1, GET_BITS(pp->tnr_edf[13],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_43, reg_a_lut_detail_x0, GET_BITS(pp->tnr_edf[14],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_43, reg_a_lut_detail_y0, GET_BITS(pp->tnr_edf[15],  0, 8));

				
				PE_ND0_M17C0_Wr01(tnr_ctrl_44, reg_t_lut_edge_x1, GET_BITS(pp->tnr_edf[16],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_44, reg_t_lut_edge_y1, GET_BITS(pp->tnr_edf[17],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_44, reg_t_lut_edge_x0, GET_BITS(pp->tnr_edf[18],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_44, reg_t_lut_edge_y0, GET_BITS(pp->tnr_edf[19],  0, 8));

				
				PE_ND0_M17C0_Wr01(tnr_ctrl_45, reg_t_lut_detail_x1, GET_BITS(pp->tnr_edf[20],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_45, reg_t_lut_detail_y1, GET_BITS(pp->tnr_edf[21],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_45, reg_t_lut_detail_x0, GET_BITS(pp->tnr_edf[22],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_45, reg_t_lut_detail_y0, GET_BITS(pp->tnr_edf[23],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_46, reg_edge_minmax_x1, GET_BITS(pp->tnr_edf[24],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_46, reg_edge_minmax_y1, GET_BITS(pp->tnr_edf[25],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_46, reg_edge_minmax_x0, GET_BITS(pp->tnr_edf[26],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_46, reg_edge_minmax_y0, GET_BITS(pp->tnr_edf[27],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_47, reg_detail_minmax_x1, GET_BITS(pp->tnr_edf[28],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_47, reg_detail_minmax_y1, GET_BITS(pp->tnr_edf[29],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_47, reg_detail_minmax_x0, GET_BITS(pp->tnr_edf[30],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_47, reg_detail_minmax_y0, GET_BITS(pp->tnr_edf[31],  0, 8));


				PE_ND0_M17C0_Wr01(tnr_ctrl_20, reg_edge_alpha_mul,	GET_BITS(pp->tnr_edf[32],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_20, reg_edge_beta_mul,		GET_BITS(pp->tnr_edf[33],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_20, reg_detail_alpha_mul,	GET_BITS(pp->tnr_edf[34],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_20, reg_detail_beta_mul,	GET_BITS(pp->tnr_edf[35],  0, 8));



				/*tnr_bld*/
				
				PE_ND0_M17C0_Wr01(tnr_ctrl_56, reg_sad_mc_ctrl_pt_x1,	GET_BITS(pp->tnr_bld[0],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_56, reg_sad_mc_ctrl_pt_y1,	GET_BITS(pp->tnr_bld[1],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_56, reg_sad_mc_ctrl_pt_x0,	GET_BITS(pp->tnr_bld[2],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_56, reg_sad_mc_ctrl_pt_y0,	GET_BITS(pp->tnr_bld[3],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_57, reg_sad_mc_ctrl_pt_x3,	GET_BITS(pp->tnr_bld[4],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_57, reg_sad_mc_ctrl_pt_y3,	GET_BITS(pp->tnr_bld[5],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_57, reg_sad_mc_ctrl_pt_x2,	GET_BITS(pp->tnr_bld[6],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_57, reg_sad_mc_ctrl_pt_y2,	GET_BITS(pp->tnr_bld[7],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_58, reg_abs_mv_ctrl_pt_x1,	GET_BITS(pp->tnr_bld[8],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_58, reg_abs_mv_ctrl_pt_y1,	GET_BITS(pp->tnr_bld[9],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_58, reg_abs_mv_ctrl_pt_x0,	GET_BITS(pp->tnr_bld[10],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_58, reg_abs_mv_ctrl_pt_y0,	GET_BITS(pp->tnr_bld[11],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_59, reg_abs_mv_ctrl_pt_x3,	GET_BITS(pp->tnr_bld[12],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_59, reg_abs_mv_ctrl_pt_y3,	GET_BITS(pp->tnr_bld[13],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_59, reg_abs_mv_ctrl_pt_x2,	GET_BITS(pp->tnr_bld[14],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_59, reg_abs_mv_ctrl_pt_y2,	GET_BITS(pp->tnr_bld[15],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_60, reg_sad_ma_ctrl_pt_x1,	GET_BITS(pp->tnr_bld[16],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_60, reg_sad_ma_ctrl_pt_y1,	GET_BITS(pp->tnr_bld[17],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_60, reg_sad_ma_ctrl_pt_x0,	GET_BITS(pp->tnr_bld[18],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_60, reg_sad_ma_ctrl_pt_y0,	GET_BITS(pp->tnr_bld[19],  0, 8));

				PE_ND0_M17C0_Wr01(tnr_ctrl_61, reg_sad_ma_ctrl_pt_x3,	GET_BITS(pp->tnr_bld[20],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_61, reg_sad_ma_ctrl_pt_y3,	GET_BITS(pp->tnr_bld[21],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_61, reg_sad_ma_ctrl_pt_x2,	GET_BITS(pp->tnr_bld[22],  0, 8));
				PE_ND0_M17C0_Wr01(tnr_ctrl_61, reg_sad_ma_ctrl_pt_y2,	GET_BITS(pp->tnr_bld[23],  0, 8));

				PE_ND0_M17C0_WrFL(tnr_ctrl_00);
				PE_ND0_M17C0_WrFL(tnr_ctrl_02);
				PE_ND0_M17C0_WrFL(tnr_ctrl_05);
				PE_ND0_M17C0_WrFL(tnr_ctrl_06);
				PE_ND0_M17C0_WrFL(tnr_ctrl_21);

				#ifdef PE_NRD_HW_M17C0_TNR_MAE_CHANGE
				PE_ND0_M17C0_WrFL(tnr_ctrl_07);
				PE_ND0_M17C0_WrFL(tnr_ctrl_09);
				PE_ND0_M17C0_WrFL(tnr_ctrl_11);
				PE_ND0_M17C0_WrFL(tnr_ctrl_16);
				PE_ND0_M17C0_WrFL(tnr_ctrl_18);
				PE_ND0_M17C0_WrFL(tnr_ctrl_19);
				#endif
				PE_ND0_M17C0_WrFL(tnr_ctrl_24);

				PE_ND0_M17C0_WrFL(tnr_ctrl_25);
				PE_ND0_M17C0_WrFL(tnr_ctrl_26);
				PE_ND0_M17C0_WrFL(tnr_ctrl_28);
				PE_ND0_M17C0_WrFL(tnr_ctrl_29);
				PE_ND0_M17C0_WrFL(tnr_ctrl_30);
				PE_ND0_M17C0_WrFL(tnr_ctrl_31);
				PE_ND0_M17C0_WrFL(tnr_ctrl_32);
				PE_ND0_M17C0_WrFL(tnr_ctrl_33);
				PE_ND0_M17C0_WrFL(tnr_ctrl_40);
				PE_ND0_M17C0_WrFL(tnr_ctrl_41);
				PE_ND0_M17C0_WrFL(tnr_ctrl_42);
				PE_ND0_M17C0_WrFL(tnr_ctrl_43);
				PE_ND0_M17C0_WrFL(tnr_ctrl_44);
				PE_ND0_M17C0_WrFL(tnr_ctrl_45);
				PE_ND0_M17C0_WrFL(tnr_ctrl_46);
				PE_ND0_M17C0_WrFL(tnr_ctrl_47);

				PE_ND0_M17C0_WrFL(tnr_ctrl_20);
				PE_ND0_M17C0_WrFL(tnr_ctrl_56);
				PE_ND0_M17C0_WrFL(tnr_ctrl_57);
				PE_ND0_M17C0_WrFL(tnr_ctrl_58);
				PE_ND0_M17C0_WrFL(tnr_ctrl_59);
				PE_ND0_M17C0_WrFL(tnr_ctrl_60);
				PE_ND0_M17C0_WrFL(tnr_ctrl_61);

				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				/*tnr_ctl*/
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_00, reg_sad_8x3_res,            GET_BITS(pp->tnr_ctl[3],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_00, reg_sad_8x3_iir_en,         GET_BITS(pp->tnr_ctl[2],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_00, reg_sad_8x3_chroma_en,      GET_BITS(pp->tnr_ctl[1],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_00, reg_sad_8x3_iir_alpha,      GET_BITS(pp->tnr_ctl[0],  0, 2));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_th_memc,                 GET_BITS(pp->tnr_ctl[4],  0, 4));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_th_ma,                   GET_BITS(pp->tnr_ctl[5],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_out_mode,                GET_BITS(pp->tnr_ctl[6],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_chroma_gain,             GET_BITS(pp->tnr_ctl[7],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_max_flt_tap,             GET_BITS(pp->tnr_ctl[8],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_scale,                   GET_BITS(pp->tnr_ctl[9],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_chroma_en,               GET_BITS(pp->tnr_ctl[10],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_calc_prev_hist,          GET_BITS(pp->tnr_ctl[11],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_max_flt_en,              GET_BITS(pp->tnr_ctl[12],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_02, sc_en,              		 GET_BITS(pp->tnr_ctl[13],  0, 1));
				pInfo->tnr_sc_en_user = GET_BITS(pp->tnr_ctl[13], 0, 1);
				pInfo->tnr_sc_en_mask = 1;

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_05, reg_mamc_mc_sad_cut,              GET_BITS(pp->tnr_ctl[14],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_05, reg_mamc_ma_sad_cut,              GET_BITS(pp->tnr_ctl[15],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_05, reg_mamc_blend_mv_max_or_sum,     GET_BITS(pp->tnr_ctl[16],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_05, reg_mamc_blend_mode,              GET_BITS(pp->tnr_ctl[17],  0, 2));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_06, reg_me_pv_base,              GET_BITS(pp->tnr_ctl[18],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_06, reg_me_lb_base,              GET_BITS(pp->tnr_ctl[19],  0, 8));
				
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_21, reg_svar_scale,              GET_BITS(pp->tnr_ctl[20],  0, 3));

				/*tnr_mae*/
				#ifdef PE_NRD_HW_M17C0_TNR_MAE_CHANGE
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_07, reg_5x5_sad_cut,         GET_BITS(pp->tnr_mae[1],  0, 2));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_07, reg_sc_en,              	GET_BITS(pp->tnr_mae[0],  0, 1));
				
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_09, reg_pv_smooth_clip,      GET_BITS(pp->tnr_mae[2],  0, 6));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_09, reg_lb_smooth_clip,      GET_BITS(pp->tnr_mae[3],  0, 6));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_09, reg_sad_base,           	GET_BITS(pp->tnr_mae[4],  0, 7));

				
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, reg_me_n15_protection,	GET_BITS(pp->tnr_mae[5],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, reg_zero_sad_adv,		GET_BITS(pp->tnr_mae[6],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, reg_zero_sad_ratio,		GET_BITS(pp->tnr_mae[7],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, reg_mv_fb_reverse,		GET_BITS(pp->tnr_mae[8],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, pv_mv_v_off,				GET_BITS(pp->tnr_mae[9],  0, 2));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, pv_mv_h_off,				GET_BITS(pp->tnr_mae[10],  0, 2));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, lb_mv_v_off,				GET_BITS(pp->tnr_mae[11],  0, 2));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, lb_mv_h_off,				GET_BITS(pp->tnr_mae[12],  0, 2));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, pv_smooth_en,			GET_BITS(pp->tnr_mae[13],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_11, lb_smooth_en,			GET_BITS(pp->tnr_mae[14],  0, 1));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_16, reg_sad_acc_mode,		GET_BITS(pp->tnr_mae[15],  0, 2));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_bmv_pmv_tl_en,		GET_BITS(pp->tnr_mae[16],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_bmv_pmv_tl,			GET_BITS(pp->tnr_mae[17],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_bmv_gmv_tl_en,		GET_BITS(pp->tnr_mae[18],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_bmv_gmv_tl,			GET_BITS(pp->tnr_mae[19],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_gmv_gmv_tl_en,		GET_BITS(pp->tnr_mae[20],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_gmv_gmv_tl,			GET_BITS(pp->tnr_mae[21],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_gsad_scale,			GET_BITS(pp->tnr_mae[22],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_bmv_rst_mode,		GET_BITS(pp->tnr_mae[23],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_18, reg_bsad_scale,			GET_BITS(pp->tnr_mae[24],  0, 3));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_19, bmv_0mv_tl_en,			GET_BITS(pp->tnr_mae[25],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_19, bmv_0mv_tl,				GET_BITS(pp->tnr_mae[26],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_19, gmv_0mv_tl_en,			GET_BITS(pp->tnr_mae[27],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_19, gmv_0mv_tl,				GET_BITS(pp->tnr_mae[28],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_19, bmv_coring_th,			GET_BITS(pp->tnr_mae[29],  0, 8));
				#endif

				/*tnr_mc*/
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_chroma_sad_en,			GET_BITS(pp->tnr__mc[0],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_cnt_mode,				GET_BITS(pp->tnr__mc[1],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_avg_cmp_res,			GET_BITS(pp->tnr__mc[2],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_avg_cmp_en,			GET_BITS(pp->tnr__mc[3],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_5x5_sad_cut,			GET_BITS(pp->tnr__mc[4],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_sad_sum_cut,			GET_BITS(pp->tnr__mc[5],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_chroma_sad_res,		GET_BITS(pp->tnr__mc[6],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_crgn_gain_en,			GET_BITS(pp->tnr__mc[7],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_luma_gain_en,			GET_BITS(pp->tnr__mc[8],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_ombc_en,				GET_BITS(pp->tnr__mc[9],  0, 7));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_24, reg_p2f_mode,				GET_BITS(pp->tnr__mc[10],  0, 7));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g22,			GET_BITS(pp->tnr__mc[11],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g21,			GET_BITS(pp->tnr__mc[12],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g20,			GET_BITS(pp->tnr__mc[13],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g12,			GET_BITS(pp->tnr__mc[14],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g11,			GET_BITS(pp->tnr__mc[15],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g10,			GET_BITS(pp->tnr__mc[16],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g02,			GET_BITS(pp->tnr__mc[17],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g01,			GET_BITS(pp->tnr__mc[18],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, reg_pre_blur_g00,			GET_BITS(pp->tnr__mc[19],  0, 4));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, cut_resolution,			GET_BITS(pp->tnr__mc[20],  0, 2));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_25, pre_blur_en,				GET_BITS(pp->tnr__mc[21],  0, 1));

				
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g22,			GET_BITS(pp->tnr__mc[22],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g21,			GET_BITS(pp->tnr__mc[23],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g20,			GET_BITS(pp->tnr__mc[24],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g12,			GET_BITS(pp->tnr__mc[25],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g11,			GET_BITS(pp->tnr__mc[26],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g10,			GET_BITS(pp->tnr__mc[27],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g02,			GET_BITS(pp->tnr__mc[28],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g01,			GET_BITS(pp->tnr__mc[29],  0, 3));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, reg_pre_blur_g00,			GET_BITS(pp->tnr__mc[30],  0, 4));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, cut_resolution,			GET_BITS(pp->tnr__mc[31],  0, 2));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_26, pre_blur_en,				GET_BITS(pp->tnr__mc[32],  0, 1));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_28, reg_pre_detail_cttl_g1,	GET_BITS(pp->tnr__mc[33],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_28, reg_pre_detail_cttl_g2,	GET_BITS(pp->tnr__mc[34],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_28, reg_pre_detail_cttl_g3,	GET_BITS(pp->tnr__mc[35],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_28, reg_pre_detail_cttl_g4,	GET_BITS(pp->tnr__mc[36],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_28, reg_pre_detail_cttl_g0,	GET_BITS(pp->tnr__mc[37],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_28, cut_resolution,			GET_BITS(pp->tnr__mc[38],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_28, luma_gain_en,				GET_BITS(pp->tnr__mc[39],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_28, pre_filtered_en,			GET_BITS(pp->tnr__mc[40],  0, 1));


				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_29, r_diff_limit,				GET_BITS(pp->tnr__mc[41],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_29, r_master_gain,				GET_BITS(pp->tnr__mc[42],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_29, r_master_en,				GET_BITS(pp->tnr__mc[43],  0, 8));


				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_30, reg_denoise_ctrl_g0,		GET_BITS(pp->tnr__mc[44],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_30, reg_denoise_gain,			GET_BITS(pp->tnr__mc[45],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_30, reg_cut_resolution,		GET_BITS(pp->tnr__mc[46],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_30, reg_pre_filtered_en,		GET_BITS(pp->tnr__mc[47],  0, 8));


				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_31, reg_denoise_ctrl_g1,		GET_BITS(pp->tnr__mc[48],  0, 5));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_31, reg_denoise_ctrl_g2,		GET_BITS(pp->tnr__mc[49],  0, 5));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_31, reg_denoise_ctrl_g3,		GET_BITS(pp->tnr__mc[50],  0, 5));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_31, reg_denoise_ctrl_g4,		GET_BITS(pp->tnr__mc[51],  0, 5));



				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_32, reg_blur_coef,		GET_BITS(pp->tnr__mc[52],  0, 5));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_32, reg_gf_gain,		GET_BITS(pp->tnr__mc[53],  0, 5));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_33, same_sad_th,		GET_BITS(pp->tnr__mc[54],  0, 5));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_33, move_step,			GET_BITS(pp->tnr__mc[55],  0, 5));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_33, p_mv0_only,		GET_BITS(pp->tnr__mc[56],  0, 5));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_33, same_protection_en,GET_BITS(pp->tnr__mc[57],  0, 5));



				/*tnr_edf*/

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_40, reg_cross_th,			GET_BITS(pp->tnr_edf[0],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_40, reg_cross_th_ne,		GET_BITS(pp->tnr_edf[1],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_40, reg_ne_normalize_en,	GET_BITS(pp->tnr_edf[2],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_40, reg_t_cut_resolution,	GET_BITS(pp->tnr_edf[3],  0, 2));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_40, reg_t_normalize_en,	GET_BITS(pp->tnr_edf[4],  0, 1));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_40, reg_a_normalize_en,	GET_BITS(pp->tnr_edf[5],  0, 1));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_41, reg_mul_base_e,	GET_BITS(pp->tnr_edf[6],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_41, reg_mul_base_t,	GET_BITS(pp->tnr_edf[7],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_42, reg_a_lut_edge_x1,	GET_BITS(pp->tnr_edf[8],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_42, reg_a_lut_edge_y1,	GET_BITS(pp->tnr_edf[9],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_42, reg_a_lut_edge_x0,	GET_BITS(pp->tnr_edf[10],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_42, reg_a_lut_edge_y0,	GET_BITS(pp->tnr_edf[11],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_43, reg_a_lut_detail_x1, GET_BITS(pp->tnr_edf[12],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_43, reg_a_lut_detail_y1, GET_BITS(pp->tnr_edf[13],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_43, reg_a_lut_detail_x0, GET_BITS(pp->tnr_edf[14],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_43, reg_a_lut_detail_y0, GET_BITS(pp->tnr_edf[15],  0, 8));

				
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_44, reg_t_lut_edge_x1, GET_BITS(pp->tnr_edf[16],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_44, reg_t_lut_edge_y1, GET_BITS(pp->tnr_edf[17],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_44, reg_t_lut_edge_x0, GET_BITS(pp->tnr_edf[18],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_44, reg_t_lut_edge_y0, GET_BITS(pp->tnr_edf[19],  0, 8));

				
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_45, reg_t_lut_detail_x1, GET_BITS(pp->tnr_edf[20],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_45, reg_t_lut_detail_y1, GET_BITS(pp->tnr_edf[21],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_45, reg_t_lut_detail_x0, GET_BITS(pp->tnr_edf[22],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_45, reg_t_lut_detail_y0, GET_BITS(pp->tnr_edf[23],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_46, reg_edge_minmax_x1, GET_BITS(pp->tnr_edf[24],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_46, reg_edge_minmax_y1, GET_BITS(pp->tnr_edf[25],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_46, reg_edge_minmax_x0, GET_BITS(pp->tnr_edf[26],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_46, reg_edge_minmax_y0, GET_BITS(pp->tnr_edf[27],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_47, reg_detail_minmax_x1, GET_BITS(pp->tnr_edf[28],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_47, reg_detail_minmax_y1, GET_BITS(pp->tnr_edf[29],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_47, reg_detail_minmax_x0, GET_BITS(pp->tnr_edf[30],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_47, reg_detail_minmax_y0, GET_BITS(pp->tnr_edf[31],  0, 8));


				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_20, reg_edge_alpha_mul,	GET_BITS(pp->tnr_edf[32],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_20, reg_edge_beta_mul,		GET_BITS(pp->tnr_edf[33],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_20, reg_detail_alpha_mul,	GET_BITS(pp->tnr_edf[34],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_20, reg_detail_beta_mul,	GET_BITS(pp->tnr_edf[35],  0, 8));



				/*tnr_bld*/
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_56, reg_sad_mc_ctrl_pt_x1,	GET_BITS(pp->tnr_bld[0],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_56, reg_sad_mc_ctrl_pt_y1,	GET_BITS(pp->tnr_bld[1],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_56, reg_sad_mc_ctrl_pt_x0,	GET_BITS(pp->tnr_bld[2],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_56, reg_sad_mc_ctrl_pt_y0,	GET_BITS(pp->tnr_bld[3],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_57, reg_sad_mc_ctrl_pt_x3,	GET_BITS(pp->tnr_bld[4],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_57, reg_sad_mc_ctrl_pt_y3,	GET_BITS(pp->tnr_bld[5],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_57, reg_sad_mc_ctrl_pt_x2,	GET_BITS(pp->tnr_bld[6],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_57, reg_sad_mc_ctrl_pt_y2,	GET_BITS(pp->tnr_bld[7],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_58, reg_abs_mv_ctrl_pt_x1,	GET_BITS(pp->tnr_bld[8],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_58, reg_abs_mv_ctrl_pt_y1,	GET_BITS(pp->tnr_bld[9],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_58, reg_abs_mv_ctrl_pt_x0,	GET_BITS(pp->tnr_bld[10],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_58, reg_abs_mv_ctrl_pt_y0,	GET_BITS(pp->tnr_bld[11],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_59, reg_abs_mv_ctrl_pt_x3,	GET_BITS(pp->tnr_bld[12],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_59, reg_abs_mv_ctrl_pt_y3,	GET_BITS(pp->tnr_bld[13],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_59, reg_abs_mv_ctrl_pt_x2,	GET_BITS(pp->tnr_bld[14],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_59, reg_abs_mv_ctrl_pt_y2,	GET_BITS(pp->tnr_bld[15],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_60, reg_sad_ma_ctrl_pt_x1,	GET_BITS(pp->tnr_bld[16],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_60, reg_sad_ma_ctrl_pt_y1,	GET_BITS(pp->tnr_bld[17],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_60, reg_sad_ma_ctrl_pt_x0,	GET_BITS(pp->tnr_bld[18],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_60, reg_sad_ma_ctrl_pt_y0,	GET_BITS(pp->tnr_bld[19],  0, 8));

				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_61, reg_sad_ma_ctrl_pt_x3,	GET_BITS(pp->tnr_bld[20],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_61, reg_sad_ma_ctrl_pt_y3,	GET_BITS(pp->tnr_bld[21],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_61, reg_sad_ma_ctrl_pt_x2,	GET_BITS(pp->tnr_bld[22],  0, 8));
				PE_NRD_HW_M17C0_TNR1_SET_USER(tnr_ctrl_61, reg_sad_ma_ctrl_pt_y2,	GET_BITS(pp->tnr_bld[23],  0, 8));

				#endif
			}
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M17C0_BRINGUP*/
	return ret;
}
/**
 * get tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR6_DETAIL_T
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M17C0_GetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M17C0_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			LX_PE_NRD_TNR6_DETAIL_T *pp=(LX_PE_NRD_TNR6_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				/* get reg */
				PE_ND0_M17C0_RdFL(tnr_ctrl_00);
				PE_ND0_M17C0_RdFL(tnr_ctrl_02);
				PE_ND0_M17C0_RdFL(tnr_ctrl_05);
				PE_ND0_M17C0_RdFL(tnr_ctrl_06);
				PE_ND0_M17C0_RdFL(tnr_ctrl_21);
				
				PE_ND0_M17C0_RdFL(tnr_ctrl_07);
				PE_ND0_M17C0_RdFL(tnr_ctrl_09);
				PE_ND0_M17C0_RdFL(tnr_ctrl_11);
				PE_ND0_M17C0_RdFL(tnr_ctrl_16);
				PE_ND0_M17C0_RdFL(tnr_ctrl_18);
				PE_ND0_M17C0_RdFL(tnr_ctrl_19);
				PE_ND0_M17C0_RdFL(tnr_ctrl_24);
				
				PE_ND0_M17C0_RdFL(tnr_ctrl_25);
				PE_ND0_M17C0_RdFL(tnr_ctrl_26);
				PE_ND0_M17C0_RdFL(tnr_ctrl_28);
				PE_ND0_M17C0_RdFL(tnr_ctrl_29);
				PE_ND0_M17C0_RdFL(tnr_ctrl_30);
				PE_ND0_M17C0_RdFL(tnr_ctrl_31);
				PE_ND0_M17C0_RdFL(tnr_ctrl_32);
				PE_ND0_M17C0_RdFL(tnr_ctrl_33);
				PE_ND0_M17C0_RdFL(tnr_ctrl_40);
				PE_ND0_M17C0_RdFL(tnr_ctrl_41);
				PE_ND0_M17C0_RdFL(tnr_ctrl_42);
				PE_ND0_M17C0_RdFL(tnr_ctrl_43);
				PE_ND0_M17C0_RdFL(tnr_ctrl_44);
				PE_ND0_M17C0_RdFL(tnr_ctrl_45);
				PE_ND0_M17C0_RdFL(tnr_ctrl_46);
				PE_ND0_M17C0_RdFL(tnr_ctrl_47);
				
				PE_ND0_M17C0_RdFL(tnr_ctrl_20);
				PE_ND0_M17C0_RdFL(tnr_ctrl_56);
				PE_ND0_M17C0_RdFL(tnr_ctrl_57);
				PE_ND0_M17C0_RdFL(tnr_ctrl_58);
				PE_ND0_M17C0_RdFL(tnr_ctrl_59);
				PE_ND0_M17C0_RdFL(tnr_ctrl_60);
				PE_ND0_M17C0_RdFL(tnr_ctrl_61);

				/*tnr_ctl*/
				PE_ND0_M17C0_Rd01(tnr_ctrl_00, reg_sad_8x3_res,            pp->tnr_ctl[0]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_00, reg_sad_8x3_iir_en,         pp->tnr_ctl[1]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_00, reg_sad_8x3_chroma_en,      pp->tnr_ctl[2]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_00, reg_sad_8x3_iir_alpha,      pp->tnr_ctl[3]);
				
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_th_memc,                 pp->tnr_ctl[4]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_th_ma,                   pp->tnr_ctl[5]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_out_mode,                pp->tnr_ctl[6]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_chroma_gain,             pp->tnr_ctl[7]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_max_flt_tap,             pp->tnr_ctl[8]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_scale,                   pp->tnr_ctl[9]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_chroma_en,               pp->tnr_ctl[10]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_calc_prev_hist,          pp->tnr_ctl[11]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_max_flt_en,              pp->tnr_ctl[12]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_02, sc_en,              		 pp->tnr_ctl[13]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_05, reg_mamc_mc_sad_cut,              pp->tnr_ctl[14]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_05, reg_mamc_ma_sad_cut,              pp->tnr_ctl[15]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_05, reg_mamc_blend_mv_max_or_sum,     pp->tnr_ctl[16]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_05, reg_mamc_blend_mode,              pp->tnr_ctl[17]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_06, reg_me_pv_base,              pp->tnr_ctl[18]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_06, reg_me_lb_base,              pp->tnr_ctl[19]);
				
				PE_ND0_M17C0_Rd01(tnr_ctrl_21, reg_svar_scale,              pp->tnr_ctl[20]);

				/*tnr_mae*/
				PE_ND0_M17C0_Rd01(tnr_ctrl_07, reg_5x5_sad_cut,           pp->tnr_mae[1]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_07, reg_sc_en,              	pp->tnr_mae[0]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_09, reg_pv_smooth_clip,        pp->tnr_mae[2]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_09, reg_lb_smooth_clip,        pp->tnr_mae[3]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_09, reg_sad_base,           	pp->tnr_mae[4]);

				
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, reg_me_n15_protection,		pp->tnr_mae[5]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, reg_zero_sad_adv,			pp->tnr_mae[6]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, reg_zero_sad_ratio,		pp->tnr_mae[7]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, reg_mv_fb_reverse,			pp->tnr_mae[8]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, pv_mv_v_off,				pp->tnr_mae[9]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, pv_mv_h_off,				pp->tnr_mae[10]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, lb_mv_v_off,				pp->tnr_mae[11]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, lb_mv_h_off,				pp->tnr_mae[12]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, pv_smooth_en,				pp->tnr_mae[13]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_11, lb_smooth_en,				pp->tnr_mae[14]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_16, reg_sad_acc_mode,			pp->tnr_mae[15]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_bmv_pmv_tl_en,		pp->tnr_mae[16]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_bmv_pmv_tl,			pp->tnr_mae[17]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_bmv_gmv_tl_en,		pp->tnr_mae[18]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_bmv_gmv_tl,			pp->tnr_mae[19]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_gmv_gmv_tl_en,		pp->tnr_mae[20]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_gmv_gmv_tl,			pp->tnr_mae[21]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_gsad_scale,			pp->tnr_mae[22]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_bmv_rst_mode,		pp->tnr_mae[23]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_18, reg_bsad_scale,			pp->tnr_mae[24]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_19, bmv_0mv_tl_en,			pp->tnr_mae[25]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_19, bmv_0mv_tl,				pp->tnr_mae[26]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_19, gmv_0mv_tl_en,			pp->tnr_mae[27]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_19, gmv_0mv_tl,				pp->tnr_mae[28]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_19, bmv_coring_th,			pp->tnr_mae[29]);


				/*tnr_mc*/
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_chroma_sad_en,			pp->tnr__mc[0]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_cnt_mode,				pp->tnr__mc[1]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_avg_cmp_res,			pp->tnr__mc[2]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_avg_cmp_en,			pp->tnr__mc[3]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_5x5_sad_cut,			pp->tnr__mc[4]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_sad_sum_cut,			pp->tnr__mc[5]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_chroma_sad_res,		pp->tnr__mc[6]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_crgn_gain_en,			pp->tnr__mc[7]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_luma_gain_en,			pp->tnr__mc[8]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_ombc_en,				pp->tnr__mc[9]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_24, reg_p2f_mode,				pp->tnr__mc[10]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g22,			pp->tnr__mc[11]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g21,			pp->tnr__mc[12]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g20,			pp->tnr__mc[13]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g12,			pp->tnr__mc[14]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g11,			pp->tnr__mc[15]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g10,			pp->tnr__mc[16]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g02,			pp->tnr__mc[17]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g01,			pp->tnr__mc[18]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, reg_pre_blur_g00,			pp->tnr__mc[19]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, cut_resolution,			pp->tnr__mc[20]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_25, pre_blur_en,				pp->tnr__mc[21]);

				
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g22,			pp->tnr__mc[22]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g21,			pp->tnr__mc[23]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g20,			pp->tnr__mc[24]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g12,			pp->tnr__mc[25]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g11,			pp->tnr__mc[26]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g10,			pp->tnr__mc[27]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g02,			pp->tnr__mc[28]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g01,			pp->tnr__mc[29]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, reg_pre_blur_g00,			pp->tnr__mc[30]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, cut_resolution,			pp->tnr__mc[31]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_26, pre_blur_en,				pp->tnr__mc[32]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_28, reg_pre_detail_cttl_g1,	pp->tnr__mc[33]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_28, reg_pre_detail_cttl_g2,	pp->tnr__mc[34]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_28, reg_pre_detail_cttl_g3,	pp->tnr__mc[35]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_28, reg_pre_detail_cttl_g4,	pp->tnr__mc[36]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_28, reg_pre_detail_cttl_g0,	pp->tnr__mc[37]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_28, cut_resolution,			pp->tnr__mc[38]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_28, luma_gain_en,				pp->tnr__mc[39]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_28, pre_filtered_en,			pp->tnr__mc[40]);


				PE_ND0_M17C0_Rd01(tnr_ctrl_29, r_diff_limit,				pp->tnr__mc[41]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_29, r_master_gain,				pp->tnr__mc[42]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_29, r_master_en,				pp->tnr__mc[43]);


				PE_ND0_M17C0_Rd01(tnr_ctrl_30, reg_denoise_ctrl_g0,		pp->tnr__mc[44]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_30, reg_denoise_gain,			pp->tnr__mc[45]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_30, reg_cut_resolution,		pp->tnr__mc[46]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_30, reg_pre_filtered_en,		pp->tnr__mc[47]);


				PE_ND0_M17C0_Rd01(tnr_ctrl_31, reg_denoise_ctrl_g1,		pp->tnr__mc[48]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_31, reg_denoise_ctrl_g2,		pp->tnr__mc[49]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_31, reg_denoise_ctrl_g3,		pp->tnr__mc[50]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_31, reg_denoise_ctrl_g4,		pp->tnr__mc[51]);



				PE_ND0_M17C0_Rd01(tnr_ctrl_32, reg_blur_coef,		pp->tnr__mc[52]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_32, reg_gf_gain,		pp->tnr__mc[53]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_33, same_sad_th,		pp->tnr__mc[54]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_33, move_step,			pp->tnr__mc[55]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_33, p_mv0_only,		pp->tnr__mc[56]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_33, same_protection_en,pp->tnr__mc[57]);



				/*tnr_edf*/

				PE_ND0_M17C0_Rd01(tnr_ctrl_40, reg_cross_th,			pp->tnr_edf[0]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_40, reg_cross_th_ne,		pp->tnr_edf[1]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_40, reg_ne_normalize_en,	pp->tnr_edf[2]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_40, reg_t_cut_resolution,	pp->tnr_edf[3]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_40, reg_t_normalize_en,	pp->tnr_edf[4]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_40, reg_a_normalize_en,	pp->tnr_edf[5]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_41, reg_mul_base_e,		pp->tnr_edf[6]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_41, reg_mul_base_t,		pp->tnr_edf[7]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_42, reg_a_lut_edge_x1,		pp->tnr_edf[8]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_42, reg_a_lut_edge_y1,		pp->tnr_edf[9]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_42, reg_a_lut_edge_x0,		pp->tnr_edf[10]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_42, reg_a_lut_edge_y0,		pp->tnr_edf[11]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_43, reg_a_lut_detail_x1, 	pp->tnr_edf[12]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_43, reg_a_lut_detail_y1, 	pp->tnr_edf[13]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_43, reg_a_lut_detail_x0, 	pp->tnr_edf[14]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_43, reg_a_lut_detail_y0, 	pp->tnr_edf[15]);

				
				PE_ND0_M17C0_Rd01(tnr_ctrl_44, reg_t_lut_edge_x1, 	pp->tnr_edf[16]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_44, reg_t_lut_edge_y1, 	pp->tnr_edf[17]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_44, reg_t_lut_edge_x0, 	pp->tnr_edf[18]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_44, reg_t_lut_edge_y0, 	pp->tnr_edf[19]);

				
				PE_ND0_M17C0_Rd01(tnr_ctrl_45, reg_t_lut_detail_x1, 	pp->tnr_edf[20]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_45, reg_t_lut_detail_y1, 	pp->tnr_edf[21]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_45, reg_t_lut_detail_x0, 	pp->tnr_edf[22]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_45, reg_t_lut_detail_y0, 	pp->tnr_edf[23]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_46, reg_edge_minmax_x1, 	pp->tnr_edf[24]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_46, reg_edge_minmax_y1, 	pp->tnr_edf[25]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_46, reg_edge_minmax_x0, 	pp->tnr_edf[26]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_46, reg_edge_minmax_y0, 	pp->tnr_edf[27]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_47, reg_detail_minmax_x1, 	pp->tnr_edf[28]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_47, reg_detail_minmax_y1, 	pp->tnr_edf[29]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_47, reg_detail_minmax_x0, 	pp->tnr_edf[30]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_47, reg_detail_minmax_y0, 	pp->tnr_edf[31]);


				PE_ND0_M17C0_Rd01(tnr_ctrl_20, reg_edge_alpha_mul,	pp->tnr_edf[32]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_20, reg_edge_beta_mul,		pp->tnr_edf[33]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_20, reg_detail_alpha_mul,	pp->tnr_edf[34]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_20, reg_detail_beta_mul,	pp->tnr_edf[35]);

				/*tnr_bld*/
				PE_ND0_M17C0_Rd01(tnr_ctrl_56, reg_sad_mc_ctrl_pt_x1,	pp->tnr_bld[0]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_56, reg_sad_mc_ctrl_pt_y1,	pp->tnr_bld[1]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_56, reg_sad_mc_ctrl_pt_x0,	pp->tnr_bld[2]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_56, reg_sad_mc_ctrl_pt_y0,	pp->tnr_bld[3]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_57, reg_sad_mc_ctrl_pt_x3,	pp->tnr_bld[4]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_57, reg_sad_mc_ctrl_pt_y3,	pp->tnr_bld[5]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_57, reg_sad_mc_ctrl_pt_x2,	pp->tnr_bld[6]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_57, reg_sad_mc_ctrl_pt_y2,	pp->tnr_bld[7]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_58, reg_abs_mv_ctrl_pt_x1,	pp->tnr_bld[8]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_58, reg_abs_mv_ctrl_pt_y1,	pp->tnr_bld[9]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_58, reg_abs_mv_ctrl_pt_x0,	pp->tnr_bld[10]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_58, reg_abs_mv_ctrl_pt_y0,	pp->tnr_bld[11]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_59, reg_abs_mv_ctrl_pt_x3,	pp->tnr_bld[12]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_59, reg_abs_mv_ctrl_pt_y3,	pp->tnr_bld[13]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_59, reg_abs_mv_ctrl_pt_x2,	pp->tnr_bld[14]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_59, reg_abs_mv_ctrl_pt_y2,	pp->tnr_bld[15]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_60, reg_sad_ma_ctrl_pt_x1,	pp->tnr_bld[16]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_60, reg_sad_ma_ctrl_pt_y1,	pp->tnr_bld[17]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_60, reg_sad_ma_ctrl_pt_x0,	pp->tnr_bld[18]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_60, reg_sad_ma_ctrl_pt_y0,	pp->tnr_bld[19]);

				PE_ND0_M17C0_Rd01(tnr_ctrl_61, reg_sad_ma_ctrl_pt_x3,	pp->tnr_bld[20]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_61, reg_sad_ma_ctrl_pt_y3,	pp->tnr_bld[21]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_61, reg_sad_ma_ctrl_pt_x2,	pp->tnr_bld[22]);
				PE_ND0_M17C0_Rd01(tnr_ctrl_61, reg_sad_ma_ctrl_pt_y2,	pp->tnr_bld[23]);

			}
			if (_g_nrd_hw_m17c0_trace)
			{
				UINT8 *pd = pp->tnr_ctl;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
				"tnr_ctl[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_ctl[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_ctl[20]%3d\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
				pd[20]);
				#ifdef PE_NRD_HW_M17C0_TNR_MAE_CHANGE
				pd = pp->tnr_mae;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
				"tnr_mae[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_mae[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr_mae[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
				pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
				#endif
				pd = pp->tnr__mc;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
				"m_c[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"m_c[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"m_c[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"m_c[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"m_c[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"m_c[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
				pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
				pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39], \
				pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49], \
				pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57]);
				pd = pp->tnr_edf;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
				"edf[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"edf[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"edf[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"edf[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
				pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
				pd[30], pd[31], pd[32], pd[33], pd[34], pd[35]);
				pd = pp->tnr_bld;
				PE_NRD_HW_M17C0_DBG_PRINT("[%d]:\n"\
				"bld[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"bld[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"bld[20]0x%08X,0x%08X,0x%08X,0x%08X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
				pd[20], pd[21], pd[22], pd[23]);
			}
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M17C0_BRINGUP*/
	return ret;
}
/**
 * set tnr lb ctrl
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M17C0_SetTnrLbMode(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_INF_M17C0_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	//PE_INF_M17C0_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_M17CX)
		{
			static PE_M17C0_PE0_TNR_SRC_SIZE_T pre_nd1_pe0_src_size = {
				.hsize = 0,
				.vsize = 0,
				.scan_type = 0,
				};
			static PE_M17C0_TNR_CTRL_16_T pre_nd1_tnr_ctrl_16 = {
				.reg_n_hblk = 0,
				.reg_n_vblk = 0,
				};
			static PE_M17C0_TNR_CTRL_17_T pre_nd1_tnr_ctrl_17 = {
				.reg_blk_vsize = 0,
				.reg_blk_hsize = 0,
				};
			PE_M17C0_TNR_CTRL_16_T cur_nd1_tnr_ctrl_16;
			PE_M17C0_TNR_CTRL_17_T cur_nd1_tnr_ctrl_17;
			#ifndef PE_NRD_HW_M17C0_USE_SIZE_FR_FW
			UINT32 pe0_src_h;
			UINT32 pe0_src_v;
			UINT32 pe0_scan_type;
			LX_PE_SCAN_TYPE scan_type;
			PE_ND0_M17C0_QRd03(tnr_fsw_ctrl_00, pe0_src_h, pe0_src_h,\
											    pe0_src_v, pe0_src_v,\
											    pe0_scan_type, pe0_scan_type);
			scan_type = pe0_scan_type == 0x0 ? LX_PE_SCAN_INTERLACE : LX_PE_SCAN_PROGRESS;
			/* nd1 nblk setting *****************************************/
			if (pre_nd1_pe0_src_size.hsize != pe0_src_h || \
				pre_nd1_pe0_src_size.vsize != pe0_src_v || \
				pre_nd1_pe0_src_size.scan_type != scan_type)
			{
				PE_NRD_HW_M17C0_DBG_PRINT("[inf] nd1 tnr src h:%d->%d, v:%d->%d, sc:%d->%d\n",\
					pre_nd1_pe0_src_size.hsize, pe0_src_h, \
					pre_nd1_pe0_src_size.vsize, pe0_src_v, \
					pre_nd1_pe0_src_size.scan_type, scan_type);
				/*hblk*/
				if (pe0_src_h >= PE_NRD_HW_M17C0_TNR_SRC_H_HD_BASE)
				{
					/*2048(4k),1568(3k),1920,1360,1280,1024,800*/
					cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x8;// h%8==0:
					cur_nd1_tnr_ctrl_17.reg_blk_hsize = pe0_src_h>>3;// h/8
				}
				else//720,704,640
				{
					if (pe0_src_h == 704 || \
						pe0_src_h <= 640)
					{
						cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x4;// h%4==0
						cur_nd1_tnr_ctrl_17.reg_blk_hsize = pe0_src_h>>2;// h/4
					}
					else//720
					{
						cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x6;// h%6==0
						cur_nd1_tnr_ctrl_17.reg_blk_hsize = pe0_src_h/6;// h/6
					}
				}
				/*vblk*/
				if (pe0_src_v >= PE_NRD_HW_M17C0_TNR_SRC_V_3K_BASE)
				{
					/*2160(4k),1620(3k)*/
					cur_nd1_tnr_ctrl_16.reg_n_vblk = 0xc;// h%12==0
					if (scan_type == LX_PE_SCAN_PROGRESS)//progressive
					{
						cur_nd1_tnr_ctrl_17.reg_blk_vsize = pe0_src_v/12;
					}
					else//interlace
					{
						cur_nd1_tnr_ctrl_17.reg_blk_vsize = pe0_src_v/24;
					}
				}
				else//1080,720,480
				{
					cur_nd1_tnr_ctrl_16.reg_n_vblk = 0x6;// h%6==0
					if (scan_type == LX_PE_SCAN_PROGRESS)//progressive
					{
						cur_nd1_tnr_ctrl_17.reg_blk_vsize = pe0_src_v/6;
					}
					else//interlace
					{
						cur_nd1_tnr_ctrl_17.reg_blk_vsize = pe0_src_v/12;
					}
				}
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				if (pre_nd1_tnr_ctrl_16.reg_n_hblk != cur_nd1_tnr_ctrl_16.reg_n_hblk || \
					pre_nd1_tnr_ctrl_16.reg_n_vblk != cur_nd1_tnr_ctrl_16.reg_n_vblk)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[set] nd1 tnr n_blk h:0x%x->0x%x, v:0x%x->0x%x\n",\
						pre_nd1_tnr_ctrl_16.reg_n_hblk, cur_nd1_tnr_ctrl_16.reg_n_hblk, \
						pre_nd1_tnr_ctrl_16.reg_n_vblk, cur_nd1_tnr_ctrl_16.reg_n_vblk);
					PE_NRD_HW_M17C0_TNR1_WR02(tnr_ctrl_16,reg_n_hblk,cur_nd1_tnr_ctrl_16.reg_n_hblk, \
					                                     reg_n_vblk,cur_nd1_tnr_ctrl_16.reg_n_vblk);
					pre_nd1_tnr_ctrl_16.reg_n_hblk = cur_nd1_tnr_ctrl_16.reg_n_hblk;
					pre_nd1_tnr_ctrl_16.reg_n_vblk = cur_nd1_tnr_ctrl_16.reg_n_vblk;
				}
				if (pre_nd1_tnr_ctrl_17.reg_blk_vsize != cur_nd1_tnr_ctrl_17.reg_blk_vsize || \
					pre_nd1_tnr_ctrl_17.reg_blk_hsize != cur_nd1_tnr_ctrl_17.reg_blk_hsize)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[set] nd1 tnr blk_size h:%d->%d, v:%d->%d\n",\
						pre_nd1_tnr_ctrl_17.reg_blk_hsize, cur_nd1_tnr_ctrl_17.reg_blk_hsize, \
						pre_nd1_tnr_ctrl_17.reg_blk_vsize, cur_nd1_tnr_ctrl_17.reg_blk_vsize);
					PE_NRD_HW_M17C0_TNR1_WR02(tnr_ctrl_17,reg_blk_vsize,cur_nd1_tnr_ctrl_17.reg_blk_vsize, \
					                                     reg_blk_hsize,cur_nd1_tnr_ctrl_17.reg_blk_hsize);
					pre_nd1_tnr_ctrl_17.reg_blk_vsize = cur_nd1_tnr_ctrl_17.reg_blk_vsize;
					pre_nd1_tnr_ctrl_17.reg_blk_hsize = cur_nd1_tnr_ctrl_17.reg_blk_hsize;
				}
				#else
				if (pre_nd1_tnr_ctrl_16.reg_n_hblk != cur_nd1_tnr_ctrl_16.reg_n_hblk || \
					pre_nd1_tnr_ctrl_16.reg_n_vblk != cur_nd1_tnr_ctrl_16.reg_n_vblk)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[set] nd1 tnr n_blk h:0x%x->0x%x, v:0x%x->0x%x\n",\
						pre_nd1_tnr_ctrl_16.reg_n_hblk, cur_nd1_tnr_ctrl_16.reg_n_hblk, \
						pre_nd1_tnr_ctrl_16.reg_n_vblk, cur_nd1_tnr_ctrl_16.reg_n_vblk);
					PE_ND0_M17C0_QWr02(tnr_ctrl_16,reg_n_hblk,cur_nd1_tnr_ctrl_16.reg_n_hblk, \
					                                     reg_n_vblk,cur_nd1_tnr_ctrl_16.reg_n_vblk);
					pre_nd1_tnr_ctrl_16.reg_n_hblk = cur_nd1_tnr_ctrl_16.reg_n_hblk;
					pre_nd1_tnr_ctrl_16.reg_n_vblk = cur_nd1_tnr_ctrl_16.reg_n_vblk;
				}
				if (pre_nd1_tnr_ctrl_17.reg_blk_vsize != cur_nd1_tnr_ctrl_17.reg_blk_vsize || \
					pre_nd1_tnr_ctrl_17.reg_blk_hsize != cur_nd1_tnr_ctrl_17.reg_blk_hsize)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[set] nd1 tnr blk_size h:%d->%d, v:%d->%d\n",\
						pre_nd1_tnr_ctrl_17.reg_blk_hsize, cur_nd1_tnr_ctrl_17.reg_blk_hsize, \
						pre_nd1_tnr_ctrl_17.reg_blk_vsize, cur_nd1_tnr_ctrl_17.reg_blk_vsize);
					PE_ND0_M17C0_QWr02(tnr_ctrl_17,reg_blk_vsize,cur_nd1_tnr_ctrl_17.reg_blk_vsize, \
					                                     reg_blk_hsize,cur_nd1_tnr_ctrl_17.reg_blk_hsize);
					pre_nd1_tnr_ctrl_17.reg_blk_vsize = cur_nd1_tnr_ctrl_17.reg_blk_vsize;
					pre_nd1_tnr_ctrl_17.reg_blk_hsize = cur_nd1_tnr_ctrl_17.reg_blk_hsize;
				}
				#endif
				pre_nd1_pe0_src_size.hsize = pe0_src_h;
				pre_nd1_pe0_src_size.vsize = pe0_src_v;
				pre_nd1_pe0_src_size.scan_type = scan_type;
			}
			#else
			/* nd1 nblk setting *****************************************/
			if (pre_nd1_pe0_src_size.hsize != ctrl0_info->pe0_src_h || \
				pre_nd1_pe0_src_size.vsize != ctrl0_info->pe0_src_v || \
				pre_nd1_pe0_src_size.scan_type != disp0_info->scan_type)
			{
				PE_NRD_HW_M17C0_DBG_PRINT("[inf] nd1 tnr src h:%d->%d, v:%d->%d, sc:%d->%d\n",\
					pre_nd1_pe0_src_size.hsize, ctrl0_info->pe0_src_h, \
					pre_nd1_pe0_src_size.vsize, ctrl0_info->pe0_src_v, \
					pre_nd1_pe0_src_size.scan_type, disp0_info->scan_type);
				/*hblk*/
				if (ctrl0_info->pe0_src_h >= PE_NRD_HW_M17C0_TNR_SRC_H_HD_BASE)
				{
					/*2048(4k),1568(3k),1920,1360,1280,1024,800*/
					cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x8;// h%8==0:
					cur_nd1_tnr_ctrl_17.reg_blk_hsize = ctrl0_info->pe0_src_h>>3;// h/8
				}
				else//720,704,640
				{
					if (ctrl0_info->pe0_src_h == 704 || \
						ctrl0_info->pe0_src_h <= 640)
					{
						cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x4;// h%4==0
						cur_nd1_tnr_ctrl_17.reg_blk_hsize = ctrl0_info->pe0_src_h>>2;// h/4
					}
					else//720
					{
						cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x6;// h%6==0
						cur_nd1_tnr_ctrl_17.reg_blk_hsize = ctrl0_info->pe0_src_h/6;// h/6
					}
				}
				/*vblk*/
				if (ctrl0_info->pe0_src_v >= PE_NRD_HW_M17C0_TNR_SRC_V_3K_BASE)
				{
					/*2160(4k),1620(3k)*/
					cur_nd1_tnr_ctrl_16.reg_n_vblk = 0xc;// h%12==0
					if (disp0_info->scan_type == LX_PE_SCAN_PROGRESS)//progressive
					{
						cur_nd1_tnr_ctrl_17.reg_blk_vsize = ctrl0_info->pe0_src_v/12;
					}
					else//interlace
					{
						cur_nd1_tnr_ctrl_17.reg_blk_vsize = ctrl0_info->pe0_src_v/24;
					}
				}
				else//1080,720,480
				{
					cur_nd1_tnr_ctrl_16.reg_n_vblk = 0x6;// h%6==0
					if (disp0_info->scan_type == LX_PE_SCAN_PROGRESS)//progressive
					{
						cur_nd1_tnr_ctrl_17.reg_blk_vsize = ctrl0_info->pe0_src_v/6;
					}
					else//interlace
					{
						cur_nd1_tnr_ctrl_17.reg_blk_vsize = ctrl0_info->pe0_src_v/12;
					}
				}
				#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
				if (pre_nd1_tnr_ctrl_16.reg_n_hblk != cur_nd1_tnr_ctrl_16.reg_n_hblk || \
					pre_nd1_tnr_ctrl_16.reg_n_vblk != cur_nd1_tnr_ctrl_16.reg_n_vblk)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[set] nd1 tnr n_blk h:0x%x->0x%x, v:0x%x->0x%x\n",\
						pre_nd1_tnr_ctrl_16.reg_n_hblk, cur_nd1_tnr_ctrl_16.reg_n_hblk, \
						pre_nd1_tnr_ctrl_16.reg_n_vblk, cur_nd1_tnr_ctrl_16.reg_n_vblk);
					PE_NRD_HW_M17C0_TNR1_WR02(tnr_ctrl_16,reg_n_hblk,cur_nd1_tnr_ctrl_16.reg_n_hblk, \
					                                     reg_n_vblk,cur_nd1_tnr_ctrl_16.reg_n_vblk);
					pre_nd1_tnr_ctrl_16.reg_n_hblk = cur_nd1_tnr_ctrl_16.reg_n_hblk;
					pre_nd1_tnr_ctrl_16.reg_n_vblk = cur_nd1_tnr_ctrl_16.reg_n_vblk;
				}
				if (pre_nd1_tnr_ctrl_17.reg_blk_vsize != cur_nd1_tnr_ctrl_17.reg_blk_vsize || \
					pre_nd1_tnr_ctrl_17.reg_blk_hsize != cur_nd1_tnr_ctrl_17.reg_blk_hsize)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[set] nd1 tnr blk_size h:%d->%d, v:%d->%d\n",\
						pre_nd1_tnr_ctrl_17.reg_blk_hsize, cur_nd1_tnr_ctrl_17.reg_blk_hsize, \
						pre_nd1_tnr_ctrl_17.reg_blk_vsize, cur_nd1_tnr_ctrl_17.reg_blk_vsize);
					PE_NRD_HW_M17C0_TNR1_WR02(tnr_ctrl_17,reg_blk_vsize,cur_nd1_tnr_ctrl_17.reg_blk_vsize, \
					                                     reg_blk_hsize,cur_nd1_tnr_ctrl_17.reg_blk_hsize);
					pre_nd1_tnr_ctrl_17.reg_blk_vsize = cur_nd1_tnr_ctrl_17.reg_blk_vsize;
					pre_nd1_tnr_ctrl_17.reg_blk_hsize = cur_nd1_tnr_ctrl_17.reg_blk_hsize;
				}
				#else
				if (pre_nd1_tnr_ctrl_16.reg_n_hblk != cur_nd1_tnr_ctrl_16.reg_n_hblk || \
					pre_nd1_tnr_ctrl_16.reg_n_vblk != cur_nd1_tnr_ctrl_16.reg_n_vblk)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[set] nd1 tnr n_blk h:0x%x->0x%x, v:0x%x->0x%x\n",\
						pre_nd1_tnr_ctrl_16.reg_n_hblk, cur_nd1_tnr_ctrl_16.reg_n_hblk, \
						pre_nd1_tnr_ctrl_16.reg_n_vblk, cur_nd1_tnr_ctrl_16.reg_n_vblk);
					PE_ND0_M17C0_QWr02(tnr_ctrl_16,reg_n_hblk,cur_nd1_tnr_ctrl_16.reg_n_hblk, \
					                                     reg_n_vblk,cur_nd1_tnr_ctrl_16.reg_n_vblk);
					pre_nd1_tnr_ctrl_16.reg_n_hblk = cur_nd1_tnr_ctrl_16.reg_n_hblk;
					pre_nd1_tnr_ctrl_16.reg_n_vblk = cur_nd1_tnr_ctrl_16.reg_n_vblk;
				}
				if (pre_nd1_tnr_ctrl_17.reg_blk_vsize != cur_nd1_tnr_ctrl_17.reg_blk_vsize || \
					pre_nd1_tnr_ctrl_17.reg_blk_hsize != cur_nd1_tnr_ctrl_17.reg_blk_hsize)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[set] nd1 tnr blk_size h:%d->%d, v:%d->%d\n",\
						pre_nd1_tnr_ctrl_17.reg_blk_hsize, cur_nd1_tnr_ctrl_17.reg_blk_hsize, \
						pre_nd1_tnr_ctrl_17.reg_blk_vsize, cur_nd1_tnr_ctrl_17.reg_blk_vsize);
					PE_ND0_M17C0_QWr02(tnr_ctrl_17,reg_blk_vsize,cur_nd1_tnr_ctrl_17.reg_blk_vsize, \
					                                     reg_blk_hsize,cur_nd1_tnr_ctrl_17.reg_blk_hsize);
					pre_nd1_tnr_ctrl_17.reg_blk_vsize = cur_nd1_tnr_ctrl_17.reg_blk_vsize;
					pre_nd1_tnr_ctrl_17.reg_blk_hsize = cur_nd1_tnr_ctrl_17.reg_blk_hsize;
				}
				#endif
				pre_nd1_pe0_src_size.hsize = ctrl0_info->pe0_src_h;
				pre_nd1_pe0_src_size.vsize = ctrl0_info->pe0_src_v;
				pre_nd1_pe0_src_size.scan_type = disp0_info->scan_type;
			}
			#endif
			/* **********************************************************/
			if(_g_nrd_hw_m17c0_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[state] nd1 tnr src h:%d, v:%d, sc:%d\n",\
						pre_nd1_pe0_src_size.hsize, pre_nd1_pe0_src_size.vsize, \
						pre_nd1_pe0_src_size.scan_type);
					PE_NRD_HW_M17C0_DBG_PRINT("[state] nd1 tnr n_blk h:0x%x, v:0x%x\n",\
						pre_nd1_tnr_ctrl_16.reg_n_hblk, pre_nd1_tnr_ctrl_16.reg_n_vblk);
					PE_NRD_HW_M17C0_DBG_PRINT("[state] nd1 tnr blk_size h:%d, v:%d\n",\
						pre_nd1_tnr_ctrl_17.reg_blk_hsize, pre_nd1_tnr_ctrl_17.reg_blk_vsize);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set tnr pv smooth en mode
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M17C0_SetTnrSmoothMode(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_M17C0_BRINGUP
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	static UINT32 count = 0;
	static UINT32 pre_pv_smooth_en = 0xff;
	UINT32 cur_pv_smooth_en, cur_m_en;
	PE_TNR_HW_PARAM_REG_M17C0_T *p_tnr_dflt = _g_pe_tnr_hw_param_data_m17c0a.reg_dflt.data;
	PE_TNR_HW_PARAM_REG_M17C0_T *p_tnr_dflt_b = _g_pe_tnr_hw_param_data_m17c0.reg_dflt.data;
	PE_NRD_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m17c0_info;
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_M17CX)
		{
			/* if m_en off, pv_smooth_en off, otherwise, refer default or user */
			PE_ND0_M17C0_QRd01(pe0_opmode,tnr_m_en,cur_m_en);
			cur_pv_smooth_en = (cur_m_en==0)? 0x0:\
				(pInfo->tnr_pv_smooth_en_mask)? \
				pInfo->tnr_pv_smooth_en_user:\
				p_tnr_dflt_b->tnr_ctrl_11.pv_smooth_en;
			/* compare pre vs. cur */
			if (pre_pv_smooth_en != cur_pv_smooth_en)
			{
				PE_NRD_HW_M17C0_DBG_PRINT("[inf] tnr_m_en:%d\n", cur_m_en);
				PE_NRD_HW_M17C0_DBG_PRINT("[set] u,m,d:%d,%d,%d, pv_smooth_en:%d -> %d\n", \
					pInfo->tnr_pv_smooth_en_user, pInfo->tnr_pv_smooth_en_mask, \
					p_tnr_dflt_b->tnr_ctrl_11.pv_smooth_en, \
					pre_pv_smooth_en, cur_pv_smooth_en);
				PE_NRD_HW_M17C0_TNR1_WR01(tnr_ctrl_11,pv_smooth_en,cur_pv_smooth_en);
				pre_pv_smooth_en = cur_pv_smooth_en;
			}
			if(_g_nrd_hw_m17c0_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[state] tnr_m_en:%d, u,m,d:%d,%d,%d, pv_smooth_en:%d\n",\
						cur_m_en, pInfo->tnr_pv_smooth_en_user, pInfo->tnr_pv_smooth_en_mask, \
						p_tnr_dflt_b->tnr_ctrl_11.pv_smooth_en, cur_pv_smooth_en);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif /*PE_HW_M17C0_BRINGUP*/
	return ret;
}
#if 0
/**
 * set tnr sc en mode
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M17C0_SetTnrScMode(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
	#if 0
	#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	static UINT32 count = 0;
	UINT32 cur_sc_en;
	PE_TNR_HW_PARAM_REG_M17C0_T *p_tnr_dflt = _g_pe_tnr_hw_param_data_m17c0.nd1_user.data;
	PE_TNR_HW_PARAM_REG_M17C0_T *p_tnr_dflt_b = _g_pe_tnr_hw_param_data_m17c0.nd1_user.data;
	PE_NRD_HW_M17C0_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m17c0_info;
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_M17CX)
		{
			/* if ud & use_manual_sc on, sc_en off, otherwise, refer default or user */
			cur_sc_en = (pInfo->use_manual_sc==1&&pInfo->tnr0a_fmt==PE_NRD_M17C0_TNR_UD)? 0x0:\
				(pInfo->tnr_sc_en_mask)? pInfo->tnr_sc_en_user:p_tnr_dflt_b->tnr_ctrl_02.sc_en;
			/* compare pre vs. cur */
			if (_g_pre_sc_en != cur_sc_en)
			{
				PE_NRD_HW_M17C0_DBG_PRINT("[inf] man_sc,tnr0a:%d,%d\n", \
					pInfo->use_manual_sc, pInfo->tnr0a_fmt);
				PE_NRD_HW_M17C0_DBG_PRINT("[set] u,m,d:%d,%d,%d, sc_en:%d -> %d\n", \
					pInfo->tnr_sc_en_user, pInfo->tnr_sc_en_mask, \
					p_tnr_dflt_b->tnr_ctrl_02.sc_en, _g_pre_sc_en, cur_sc_en);
				PE_NRD_HW_M17C0_TNR1_WR01(tnr_ctrl_02,sc_en,cur_sc_en);
				_g_pre_sc_en = cur_sc_en;
			}
			if(_g_nrd_hw_m17c0_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[state] man_sc,tnr0a:%d,%d, u,m,d:%d,%d,%d, sc_en:%d\n",\
						pInfo->use_manual_sc, pInfo->tnr0a_fmt, pInfo->tnr_sc_en_user, \
						pInfo->tnr_sc_en_mask, p_tnr_dflt_b->tnr_ctrl_02.sc_en, cur_sc_en);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif
	return ret;
}
#endif
/**
 * set tnr mode
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M17C0_SetTnrMode(PE_TSK_M17C0_CFG_T *pCfg)
{
    int ret = RET_OK;
	#ifdef PE_NRD_HW_M17C0_CVD_PAT_DETECT
	UINT32 is_pattern;
	UINT32 cur_pattern_fw;
	LX_PE_INF_DISPLAY_T cur0_inf;
	PE_M17C0_DC_BNR_CTRL_0_T data0={0};
	PE_M17C0_DC_BNR_CTRL_1_T data1={0};
	PE_M17C0_DC_BNR_CTRL_2_T data2={0};
	PE_M17C0_DC_BNR_CTRL_7_T data7={0};
	UINT32 data_tnr_sad_cut;
	UINT32 data_tnr_7;
	UINT32 data_tnr_2;
	UINT32 histo_bin[32];
	UINT32 hue_bin[32];
	UINT32 s_status;
	UINT32 f_one_color_pattern, f_16_step_pattern;
	static UINT32 pat_count=0;
	#endif
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_M17CX)
		{
			ret = PE_NRD_HW_M17C0_SetTnrLbMode(pCfg);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_M17C0_SetTnrLbMode() error.\n",__F__,__L__);
			ret = PE_NRD_HW_M17C0_SetTnrSmoothMode(pCfg);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_M17C0_SetTnrSmoothMode() error.\n",__F__,__L__);
			//ret = PE_NRD_HW_M17C0_SetTnrScMode(pCfg);
			//PE_NRD_HW_M17C0_CHECK_CODE(ret, break,
			//	"[%s,%d] PE_NRD_HW_M17C0_SetTnrScMode() error.\n",__F__,__L__);
			#ifdef PE_NRD_HW_M17C0_CVD_PAT_DETECT
			PE_CE_PE1_M17C0_QRd01(pe1_fsw_ctrl_00,reg_s_status_0,s_status);
			ret = PE_INF_M17C0_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
			if(g_pe_inf_m17c0_vr360_mode)
			{
				is_pattern = 0;
				cur_pattern_fw = 0;
			}
			else
			{
#ifdef INCLUDE_KDRV_AFE
				if(g_CVD_Pattern_Detection_t.pattern_found ||\
					g_CVD_Pattern_Detection_t.static_pattern_found)
				{
					if(pat_count<5)
					{
						pat_count++;
						is_pattern = 0;
					}
					else
					{
						is_pattern = 1;
					}
				}
				else
				{
					is_pattern = 0;
					pat_count =0;
				}
				if((cur0_inf.src_type == LX_PE_SRC_ATV) && g_CVD_Pattern_Detection_t.pattern_found && (cur0_inf.cstd_type != LX_PE_CSTD_SECAM))
				{
					cur_pattern_fw = 1;
				}
				else
				{
					cur_pattern_fw = 0;
				}
#endif
			}
			ret = PE_HST_HW_M17C0_GetSrcHistoBin(0, histo_bin, 0);//Y
			ret = PE_HST_HW_M17C0_GetSrcHistoBin(0, hue_bin, 6);//H
			//1. 16step grey pattern detect
			f_16_step_pattern =1;
			if((histo_bin[4]+histo_bin[5]+histo_bin[6]+histo_bin[7])<18500)
			{
				f_16_step_pattern =0;
			}
			if((histo_bin[8]+histo_bin[9]+histo_bin[10]+histo_bin[11])<18500)
			{
				f_16_step_pattern =0;
			}
			if((histo_bin[12]+histo_bin[13]+histo_bin[14]+histo_bin[15])<18500)
			{
				f_16_step_pattern =0;
			}
			if((histo_bin[16]+histo_bin[17]+histo_bin[18]+histo_bin[19])<18500)
			{
				f_16_step_pattern =0;
			}
			if((histo_bin[20]+histo_bin[21]+histo_bin[22]+histo_bin[23])<18500)
			{
				f_16_step_pattern =0;
			}
			if((histo_bin[24]+histo_bin[25]+histo_bin[26]+histo_bin[27])<18500)
			{
				f_16_step_pattern =0;
			}
			//2. red pattern detect
			if((((hue_bin[0]+hue_bin[1]+hue_bin[31])*100)/168960)>93 ||
				(((hue_bin[9]+hue_bin[10]+hue_bin[11])*100)/168960)>93 ||
				(((hue_bin[20]+hue_bin[21]+hue_bin[22])*100)/168960)>93 ||
				(((histo_bin[28]+histo_bin[29]+histo_bin[30])*100)/168960)>93||
				(((histo_bin[0]+histo_bin[1]+histo_bin[2]+histo_bin[3])*100)/168960)>93)
			{
				f_one_color_pattern = 1;
			}
			else
			{
				f_one_color_pattern = 0;
			}
			if((cur0_inf.src_type == LX_PE_SRC_ATV) && is_pattern && (cur0_inf.cstd_type != LX_PE_CSTD_SECAM))
			{
				if((f_one_color_pattern ==0)&&(f_16_step_pattern ==0))
				{
					//cur_pattern = 0x1;
					data0.reg_dc_bnr_enable      = GET_BITS(0x1,0,1);
					data0.reg_dc_blur_sel        = GET_BITS(0x0,0,2);
					data0.reg_dc_motion_max      = GET_BITS(0x30,0,8);
					data0.reg_dc_motion_min      = GET_BITS(0x10,0,8);

					data1.reg_var_cut_resolution = GET_BITS(0x4,0,4);
					data1.reg_var_h_gain         = GET_BITS(0xd,0,4);
					data1.reg_var_v_gain         = GET_BITS(0x7,0,4);
					data1.reg_luma_gain_en       = GET_BITS(0x0,0,1);

					data2.reg_dc_protection_th   = GET_BITS(0x15,0,8);
					data2.reg_dc_bnr_chromagain  = GET_BITS(0x20,0,8);
					data2.reg_dc_bnr_mastergain  = GET_BITS(0x18,0,6);
					data2.reg_dc_protection_en   = GET_BITS(0x0,0,1);
					data2.reg_dc_motion_en       = GET_BITS(0x0,0,1);
					data2.reg_dc_var_en          = GET_BITS(0x1,0,1);
					
					data7.reg_fil_motion_y_th0   = GET_BITS(0x20,0,8);
					data7.reg_fil_motion_y_th1   = GET_BITS(0x20,0,8);
					data7.reg_fil_motion_y_th2   = GET_BITS(0x20,0,8);
					data7.reg_fil_motion_y_th3   = GET_BITS(0x20,0,8);
					data_tnr_7			 			= _g_pe_tnr_hw_param_data_m17c0.nd1_user.data->tnr_ctrl_07.reg_sc_en;
					data_tnr_sad_cut				= _g_pe_tnr_hw_param_data_m17c0.nd1_user.data->tnr_ctrl_07.reg_5x5_sad_cut;
					data_tnr_2					 	= _g_pe_tnr_hw_param_data_m17c0.nd1_user.data->tnr_ctrl_02.sc_th_ma;
				}
				else
				{
					//cur_pattern = 0x0;
					data0.reg_dc_bnr_enable      =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_0.reg_dc_bnr_enable;
					data0.reg_dc_blur_sel        =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_0.reg_dc_blur_sel;
					data0.reg_dc_motion_max      =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_0.reg_dc_motion_max;
					data0.reg_dc_motion_min      =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_0.reg_dc_motion_min;

					data1.reg_var_cut_resolution =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_1.reg_var_cut_resolution;
					data1.reg_var_h_gain         =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_1.reg_var_h_gain;
					data1.reg_var_v_gain         =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_1.reg_var_v_gain;
					data1.reg_luma_gain_en       =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_1.reg_luma_gain_en;

					data2.reg_dc_protection_th   =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_protection_th;
					data2.reg_dc_bnr_chromagain  =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_bnr_chromagain;
					data2.reg_dc_bnr_mastergain  =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_bnr_mastergain;
					data2.reg_dc_protection_en   =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_protection_en;
					data2.reg_dc_motion_en       =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_motion_en;
					data2.reg_dc_var_en          =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_var_en;

					data7.reg_fil_motion_y_th0   = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data->dc_bnr_ctrl_7.reg_fil_motion_y_th0;
					data7.reg_fil_motion_y_th1   = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data->dc_bnr_ctrl_7.reg_fil_motion_y_th1;
					data7.reg_fil_motion_y_th2   = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data->dc_bnr_ctrl_7.reg_fil_motion_y_th2;
					data7.reg_fil_motion_y_th3   = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data->dc_bnr_ctrl_7.reg_fil_motion_y_th3;
					data_tnr_sad_cut			 = GET_BITS(0x3,0,2);
					data_tnr_7					 = GET_BITS(0x1,0,1);
					data_tnr_2					 = GET_BITS(0x3,0,8);
				}
			}
			else
			{
				//cur_pattern = 0x0;
				data0.reg_dc_bnr_enable      =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_0.reg_dc_bnr_enable;
				data0.reg_dc_blur_sel        =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_0.reg_dc_blur_sel;
				data0.reg_dc_motion_max      =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_0.reg_dc_motion_max;
				data0.reg_dc_motion_min      =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_0.reg_dc_motion_min;

				data1.reg_var_cut_resolution =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_1.reg_var_cut_resolution;
				data1.reg_var_h_gain         =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_1.reg_var_h_gain;
				data1.reg_var_v_gain         =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_1.reg_var_v_gain;
				data1.reg_luma_gain_en       =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_1.reg_luma_gain_en;

				data2.reg_dc_protection_th   =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_protection_th;
				data2.reg_dc_bnr_chromagain  =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_bnr_chromagain;
				data2.reg_dc_bnr_mastergain  =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_bnr_mastergain;
				data2.reg_dc_protection_en   =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_protection_en;
				data2.reg_dc_motion_en       =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_motion_en;
				data2.reg_dc_var_en          =_g_pe_dnr_hw_param_data_m17c0.reg_user.data->dc_bnr_ctrl_2.reg_dc_var_en;

				data7.reg_fil_motion_y_th0   = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data->dc_bnr_ctrl_7.reg_fil_motion_y_th0;
				data7.reg_fil_motion_y_th1   = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data->dc_bnr_ctrl_7.reg_fil_motion_y_th1;
				data7.reg_fil_motion_y_th2   = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data->dc_bnr_ctrl_7.reg_fil_motion_y_th2;
				data7.reg_fil_motion_y_th3   = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data->dc_bnr_ctrl_7.reg_fil_motion_y_th3;
				
				if((cur0_inf.src_type == LX_PE_SRC_ATV)&&(f_one_color_pattern ==1||f_16_step_pattern ==1))
				{
					data_tnr_sad_cut			 = GET_BITS(0x3,0,2);
					data_tnr_7					 = GET_BITS(0x1,0,1);
					data_tnr_2					 = GET_BITS(0x3,0,8);
				}
				else 
				{
					data_tnr_7			 	= _g_pe_tnr_hw_param_data_m17c0.nd1_user.data->tnr_ctrl_07.reg_sc_en;
					data_tnr_sad_cut		= _g_pe_tnr_hw_param_data_m17c0.nd1_user.data->tnr_ctrl_07.reg_5x5_sad_cut;
					data_tnr_2				= _g_pe_tnr_hw_param_data_m17c0.nd1_user.data->tnr_ctrl_02.sc_th_ma;
				}
			}
			
			//sc on @ pattern change
			if(_g_pre_pattern_fw !=cur_pattern_fw)
			{
				PE_SR_SHP_M17C0_QWr01(shp_fsw_ctrl_00, cvd_pattern_detect, GET_BITS(cur_pattern_fw,0,1));
				data_tnr_sad_cut			 = GET_BITS(0x3,0,2);
				data_tnr_7					 = GET_BITS(0x1,0,1);
				data_tnr_2					 = GET_BITS(0x3,0,8);
#ifdef INCLUDE_KDRV_AFE
				PE_NRD_HW_M17C0_DBG_PRINT("pattern status changed!! pre %d->cur %d, s:%d, md: %d\n",_g_pre_pattern_fw,cur_pattern_fw,\
					s_status,g_CVD_Pattern_Detection_t.global_motion_diff);
#endif
				_g_pre_pattern_fw =cur_pattern_fw;
			}
			if(memcmp(&data0, &_g_pre_data0,sizeof(PE_M17C0_DC_BNR_CTRL_0_T))!=0)
			{
				PE_DNR0_M17C0_QWr04(dc_bnr_ctrl_0, reg_dc_bnr_enable, GET_BITS(data0.reg_dc_bnr_enable,0,1),\
												 reg_dc_blur_sel, 	GET_BITS(data0.reg_dc_blur_sel  ,0,2),\
												 reg_dc_motion_max, GET_BITS(data0.reg_dc_motion_max,0,8),\
												 reg_dc_motion_min, GET_BITS(data0.reg_dc_motion_min,0,8));
				_g_pre_data0.reg_dc_bnr_enable =data0.reg_dc_bnr_enable;
				_g_pre_data0.reg_dc_blur_sel   =data0.reg_dc_blur_sel; 
				_g_pre_data0.reg_dc_motion_max =data0.reg_dc_motion_max;
				_g_pre_data0.reg_dc_motion_min =data0.reg_dc_motion_min;
			}
			if(memcmp(&data1, &_g_pre_data1,sizeof(PE_M17C0_DC_BNR_CTRL_1_T))!=0)
			{
				PE_DNR0_M17C0_QWr04(dc_bnr_ctrl_1, reg_var_cut_resolution, GET_BITS(data1.reg_var_cut_resolution,0,4),\
												 reg_var_h_gain, 		 GET_BITS(data1.reg_var_h_gain        ,0,4),\
												 reg_var_v_gain, 		 GET_BITS(data1.reg_var_v_gain        ,0,4),\
												 reg_luma_gain_en, 		 GET_BITS(data1.reg_luma_gain_en      ,0,1));
				_g_pre_data1.reg_var_cut_resolution = data1.reg_var_cut_resolution;
				_g_pre_data1.reg_var_h_gain         = data1.reg_var_h_gain        ;
				_g_pre_data1.reg_var_v_gain         = data1.reg_var_v_gain        ;
				_g_pre_data1.reg_luma_gain_en       = data1.reg_luma_gain_en      ;
			}
			if(memcmp(&data2, &_g_pre_data2,sizeof(PE_M17C0_DC_BNR_CTRL_2_T))!=0)
			{
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_2);
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2,  reg_dc_protection_th, 	GET_BITS(data2.reg_dc_protection_th ,0,8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2,  reg_dc_bnr_chromagain, GET_BITS(data2.reg_dc_bnr_chromagain,0,8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2,  reg_dc_bnr_mastergain, GET_BITS(data2.reg_dc_bnr_mastergain,0,6));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2,  reg_dc_protection_en, 	GET_BITS(data2.reg_dc_protection_en ,0,1));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2,  reg_dc_motion_en, 		GET_BITS(data2.reg_dc_motion_en     ,0,1));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_2,  reg_dc_var_en, 		GET_BITS(data2.reg_dc_var_en        ,0,1));				
				PE_DNR0_M17C0_WrFL(dc_bnr_ctrl_2);
				_g_pre_data2.reg_dc_protection_th  =data2.reg_dc_protection_th ;
				_g_pre_data2.reg_dc_bnr_chromagain =data2.reg_dc_bnr_chromagain;
				_g_pre_data2.reg_dc_bnr_mastergain =data2.reg_dc_bnr_mastergain;
				_g_pre_data2.reg_dc_protection_en  =data2.reg_dc_protection_en ;
				_g_pre_data2.reg_dc_motion_en      =data2.reg_dc_motion_en     ;
				_g_pre_data2.reg_dc_var_en         =data2.reg_dc_var_en       ;
			}
			if(memcmp(&data7, &_g_pre_data7,sizeof(PE_M17C0_DC_BNR_CTRL_7_T))!=0)
			{
				PE_DNR0_M17C0_RdFL(dc_bnr_ctrl_7);
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_7,  reg_fil_motion_y_th0, GET_BITS(data7.reg_fil_motion_y_th0,0,8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_7,  reg_fil_motion_y_th1, GET_BITS(data7.reg_fil_motion_y_th1,0,8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_7,  reg_fil_motion_y_th2, GET_BITS(data7.reg_fil_motion_y_th2,0,8));
				PE_DNR0_M17C0_Wr01(dc_bnr_ctrl_7,  reg_fil_motion_y_th3, GET_BITS(data7.reg_fil_motion_y_th3,0,8));				
				PE_DNR0_M17C0_WrFL(dc_bnr_ctrl_7);
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_7,  reg_fil_motion_y_th0, GET_BITS(data7.reg_fil_motion_y_th0,0,8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_7,  reg_fil_motion_y_th1, GET_BITS(data7.reg_fil_motion_y_th1,0,8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_7,  reg_fil_motion_y_th2, GET_BITS(data7.reg_fil_motion_y_th2,0,8));
				PE_NRD_HW_M17C0_DNR_SET_USER(dc_bnr_ctrl_7,  reg_fil_motion_y_th3, GET_BITS(data7.reg_fil_motion_y_th3,0,8));
				_g_pre_data7.reg_fil_motion_y_th0 =data7.reg_fil_motion_y_th0;
				_g_pre_data7.reg_fil_motion_y_th1 =data7.reg_fil_motion_y_th1;
				_g_pre_data7.reg_fil_motion_y_th2 =data7.reg_fil_motion_y_th2;
				_g_pre_data7.reg_fil_motion_y_th3 =data7.reg_fil_motion_y_th3;
			}
			if(data_tnr_2 != _g_pre_data_tnr_2)
			{
				PE_ND0_M17C0_QWr01(tnr_ctrl_02,	sc_th_ma, GET_BITS(data_tnr_2,0,8));
				_g_pre_data_tnr_2 = data_tnr_2;
			}
			if(data_tnr_7 != _g_pre_data_tnr_7)
			{
				PE_ND0_M17C0_QWr01(tnr_ctrl_07,	reg_sc_en, GET_BITS(data_tnr_7,0,1));
				_g_pre_data_tnr_7 = data_tnr_7;
			}if(data_tnr_sad_cut != _g_pre_data_tnr_sad_cut)
			{
				PE_ND0_M17C0_QWr01(tnr_ctrl_07,	reg_5x5_sad_cut, GET_BITS(data_tnr_sad_cut,0,2));
				_g_pre_data_tnr_sad_cut = data_tnr_sad_cut;
			}
			#endif
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
#if 0
/**
 * set dnr max mode
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M17C0_SetDnrMaxMode(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set bnr mode
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M17C0_SetBnrMode(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
	return ret;
}
#endif
/**
 * set dnr mode
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M17C0_SetDnrMode(PE_TSK_M17C0_CFG_T *pCfg)
{
    int ret = RET_OK;
	#ifdef PE_HW_M17C0_BRINGUP
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_M17CX)
		{
			ret = PE_NRD_HW_M17C0_SetDnrMaxMode(pCfg);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_M17C0_SetDnrMaxMode() error.\n",__F__,__L__);
			ret = PE_NRD_HW_M17C0_SetBnrMode(pCfg);
			PE_NRD_HW_M17C0_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_M17C0_SetBnrMode() error.\n",__F__,__L__);
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M17C0_BRINGUP*/
	return ret;
}
/**
 * set ifc mode
 *
 * @param   *pCfg [in] PE_TSK_M17C0_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M17C0_SetIfcMode(PE_TSK_M17C0_CFG_T *pCfg)
{
	int ret = RET_OK;
#ifndef PE_HW_M17C0_PROTECT_OVERLAP_SETTINGS
	static UINT32 count = 0;
	static UINT32 pre_ifc_max_en0 = 0xff;		//pre ifc_en0
	UINT32 cur_ifc_max_en0 = 0;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_DNR_HW_PARAM_REG_M17C0_T *p_dnr_dflt = _g_pe_dnr_hw_param_data_m17c0.reg_dflt.data;
	do{
		CHECK_KNULL(pCfg);
		if (PE_KDRV_VER_M17CX)
		{
			/* if mask on, refer default, otherwise, user data */
			cur_ifc_max_en0 = (PE_HW_M17C0_CHK_MULTI_PATH_FMT(disp0_info->fmt_type) || \
				(disp0_info->sub_mode == LX_DE_SUB_MODE_PBP) ? 0x0:\
				p_dnr_dflt->dnr_max_ctrl.reg_ifc_max_enable);
			/* compare pre vs. cur */
			if (pre_ifc_max_en0 != cur_ifc_max_en0)
			{
				PE_NRD_HW_M17C0_DBG_PRINT("[inf] sub_mode:%d, dflt:%d\n",\
					disp0_info->sub_mode, p_dnr_dflt->dnr_max_ctrl.reg_ifc_max_enable);
				PE_NRD_HW_M17C0_DBG_PRINT("[set] ifc_max_en : %d -> %d\n",\
					pre_ifc_max_en0, cur_ifc_max_en0);
				PE_DNR0_M17C0_QWr01(dnr_max_ctrl,reg_ifc_max_enable,cur_ifc_max_en0);
				PE_NRD_HW_M17C0_DNR_SET_USER(dnr_max_ctrl,reg_ifc_max_enable,cur_ifc_max_en0);
				pre_ifc_max_en0 = cur_ifc_max_en0;
			}
			if(_g_nrd_hw_m17c0_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_NRD_HW_M17C0_DBG_PRINT("[state] submode:%d, dflt:%d, ifc_en:%d\n",\
						disp0_info->sub_mode, p_dnr_dflt->dnr_max_ctrl.reg_ifc_max_enable, \
						cur_ifc_max_en0);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
#endif
	return ret;
}

/**
 * download tnr db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M17C0_DownloadTnrDb(void)
{
	int ret = RET_OK;
	UINT32 i, size, sec_typ;
	UINT32 base_lut[PE_NRD_M17C0_TNL_NUM];
	UINT32 base_user_lut, base_gain, base_buff, base_init;
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_M17C0_T *p_phys_db = gPE_DDR_DB_M17C0.phys.data;
	volatile UINT32 *p_tnr_lut_data  = p_phys_db->tnr_lut.data;
	volatile UINT32 *p_tnr_user_data = p_phys_db->tnr_user.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_tnr_lut_data );
		CHECK_KNULL(p_tnr_user_data);
		if (PE_KDRV_VER_M17CX)
		{
			/* tnr_lut **************************************************************/
			sec_typ = PE_DDR_M17C0_SEC_TNR_LUT;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M17C0_TNR_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M17C0_TNR_LUT_SIZE;
			p_phys_db->tnr_lut.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_lut.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_lut.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_TNR_LUT_ITEM_NUM * PE_DDR_M17C0_TNR_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M17C0_HEADER_T);
			/* wr ddr */
			base_lut[0] = 0;									//PE_NRD_M17C0_TNL_HD
			base_lut[1] = base_lut[0]+PE_DDR_M17C0_TNR_LUT_SIZE;	//PE_NRD_M17C0_TNL_SD
			base_lut[2] = base_lut[1]+PE_DDR_M17C0_TNR_LUT_SIZE;	//PE_NRD_M17C0_TNL_UD
			base_lut[3] = base_lut[2]+PE_DDR_M17C0_TNR_LUT_SIZE;	//PE_NRD_M17C0_TNL_CAM_HD
			for (i=0; i<PE_DDR_M17C0_TNR_LUT_SIZE; i++)
			{
				p_tnr_lut_data[base_lut[0]+i] = tnr_l_lut_hd_default_m17c0[i].data;
				p_tnr_lut_data[base_lut[1]+i] = tnr_l_lut_sd_default_m17c0[i].data;
				p_tnr_lut_data[base_lut[2]+i] = tnr_l_lut_ud_default_m17c0[i].data;
				p_tnr_lut_data[base_lut[3]+i] = tnr_l_lut_cam_hd_default_m17c0[i].data;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
			/* tnr_user **************************************************************/
			sec_typ = PE_DDR_M17C0_SEC_TNR_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M17C0_TNR_USER_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M17C0_TNR_USER_SIZE;
			p_phys_db->tnr_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M17C0_TNR_USER_ITEM_NUM * PE_DDR_M17C0_TNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M17C0_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M17C0_HEADER_T);
			/* wr ddr */
			p_tnr_user_data[0]  = 0x0;
			p_tnr_user_data[1]  = 0x0;
			base_user_lut = 2;
			base_gain = base_user_lut+LX_PE_NRD_TNR7_CMN_LUT__SIZE;
			base_buff = base_gain+LX_PE_NRD_TNR7_CMN_GAIN_SIZE;
			base_init = 7;
			for (i=0; i<LX_PE_NRD_TNR5_CMN_LUT_SIZE; i++)
			{
				p_tnr_user_data[base_user_lut+i] = tnr_l_lut_hd_default_m17c0[base_init+i].data;
			}
			p_tnr_user_data[base_gain]=p_tnr_user_data[base_gain+1]=p_tnr_user_data[base_gain+2]= \
				p_tnr_user_data[base_gain+3] =p_tnr_user_data[base_gain+4]=0x0;
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	return ret;
}

/**
 * download tnr user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M17C0_DownloadTnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR7_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M17C0_T *p_shdw_db = gPE_DDR_DB_M17C0.shdw.data;
	volatile PE_DDR_M17C0_TNR_USER_T *p_phys_tnr_user_db = NULL;
	volatile UINT32 *p_db_data = NULL;
	do{
		CHECK_KNULL(pstParams);
		if (PE_KDRV_VER_M17CX)
		{
			sec_typ = PE_DDR_M17C0_SEC_TNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M17C0_TNR_USER_T);
			p_phys_tnr_user_db  = (volatile PE_DDR_M17C0_TNR_USER_T *)vmap_phys(base, size);
			CHECK_KNULL(p_phys_tnr_user_db);
			p_db_data = p_phys_tnr_user_db->data;
			pp = (LX_PE_NRD_TNR7_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->tnr_en;
			base = 2;
			for (i=0; i<LX_PE_NRD_TNR7_CMN_LUT__SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr_lut[i];
			}
			base += LX_PE_NRD_TNR7_CMN_LUT__SIZE;
			for (i=0; i<LX_PE_NRD_TNR7_CMN_GAIN_SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr_lut_gain[i];
			}
			base += LX_PE_NRD_TNR7_CMN_GAIN_SIZE;
			for (i=0; i<LX_PE_NRD_TNR7_CMN_BUFF_SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr_lut_buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_NRD_HW_M17C0_DBG_PRINT("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M17C0_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_NRD_HW_M17C0_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	if (p_phys_tnr_user_db) vunmap_phys((void *)p_phys_tnr_user_db);
	return ret;
}

