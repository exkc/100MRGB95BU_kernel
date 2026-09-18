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

/** @file pe_dnt_hw_o24.c
 *
 *  driver for picture enhance deinterlacer functions. ( used only within kdriver )
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

#include "pe_hw_o24.h"
#include "pe_reg_o24.h"
#include "pe_fwi_o24.h"
#include "pe_dnt_hw_o24.h"
#include "pe_ipc_hw_param_o24.h"
#include "pe_clc_hw_param_o24.h"
#include "pe_vflt_y_hw_param_o24.h"
#include "cvd_module.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* define num of default reg not to set by drv */
#define PE_DNT_HW_O24_NUM_OF_IPC00_IN_TABLE                (0)
/* define until film mode f/w ready, O24 */
#undef PE_DNT_HW_O24_SET_FMD_REG
#undef PE_DNT_HW_O24_SET_FMD_AUTO

/* undef until clc_en f/w ready */
#undef PE_HW_O24_USE_FSW_CLC_ENABLE

/* use pre processing for setting ipc reg table */
#define PE_DNT_HW_O24_USE_PRE_PROC_IPC_REG_TABLE

/* apply vfilter y on dtv 1080p  */
#define PE_DNT_HW_O24_APPLY_VFLT_Y_ON_DTV_1080P

/* define for using clc default or not (to fix warning) */
#define PE_DNT_HW_O24_USE_CLC_DEFAULT

#undef PE_DNR_HW_O24_PAT_DETECT

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DNT_HW_O24_ERROR		PE_PRINT_ERROR

#define PE_DNT_HW_O24_DBG_PRINT(fmt, args...)	\
	if(_g_dnt_hw_o24_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}
#define PE_DNT_HW_O24_DBG_PRINT_IPC_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_DNT_HW_O24_IPC_FMT_TO_STR(_pre), \
			PE_DNT_HW_O24_IPC_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DNT_HW_O24_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O24_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_DNT_HW_O24_DBG_PRINT_CLC_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,  "%s(%s)->(%s):%s", #_cur, \
			PE_DNT_HW_O24_CLC_FMT_TO_STR(_pre), \
			PE_DNT_HW_O24_CLC_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DNT_HW_O24_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O24_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_DNT_HW_O24_DBG_PRINT_VFY_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,  "%s(%s)->(%s):%s", #_cur, \
			PE_DNT_HW_O24_VFY_FMT_TO_STR(_pre), \
			PE_DNT_HW_O24_VFY_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DNT_HW_O24_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O24_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_DNT_HW_O24_CHECK_CODE(_checker, _action, fmt, args...)	\
	{if(_checker){PE_DNT_HW_O24_ERROR(fmt, ##args);_action;}}

#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
#define PE_DNT0_HW_O24_IPC_SET_USER(_r, _f, _d)	\
	{	_g_pe_ipc0_hw_param_data_o24.reg_user.data->_r._f = (_d);\
		_g_pe_ipc0_hw_param_data_o24.reg_mask.data->_r._f = 0;}

#define PE_DNT1_HW_O24_IPC_SET_USER(_r, _f, _d)	\
	{	_g_pe_ipc1_hw_param_data_o24.reg_user.data->_r._f = (_d);\
		_g_pe_ipc1_hw_param_data_o24.reg_mask.data->_r._f = 0;}

#define PE_DNT_HW_O24_IPC_WR01(_r, _f1, _d1)	\
	{	PE_ND0_O24_QWr01(_r, _f1, _d1);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f1, _d1);}
#define PE_DNT_HW_O24_IPC_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND0_O24_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f1, _d1);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f2, _d2);}
#define PE_DNT_HW_O24_IPC_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND0_O24_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f1, _d1);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f2, _d2);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f3, _d3);}
#define PE_DNT_HW_O24_IPC_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND0_O24_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f1, _d1);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f2, _d2);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f3, _d3);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f4, _d4);}
#define PE_DNT_HW_O24_IPC_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND0_O24_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f1, _d1);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f2, _d2);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f3, _d3);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f4, _d4);\
		PE_DNT0_HW_O24_IPC_SET_USER(_r, _f5, _d5);}

#define PE_DNT1_HW_O24_IPC_WR01(_r, _f1, _d1)	\
	{	PE_ND1_O24_QWr01(_r, _f1, _d1);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f1, _d1);}
#define PE_DNT1_HW_O24_IPC_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND1_O24_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f1, _d1);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f2, _d2);}
#define PE_DNT1_HW_O24_IPC_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND1_O24_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f1, _d1);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f2, _d2);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f3, _d3);}
#define PE_DNT1_HW_O24_IPC_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND1_O24_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f1, _d1);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f2, _d2);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f3, _d3);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f4, _d4);}
#define PE_DNT1_HW_O24_IPC_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND1_O24_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f1, _d1);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f2, _d2);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f3, _d3);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f4, _d4);\
		PE_DNT1_HW_O24_IPC_SET_USER(_r, _f5, _d5);}

#define PE_DNT_HW_O24_CLC_SET_USER(_r, _f, _d)	\
	{	_g_pe_clc0_hw_param_data_o24.reg_user.data->_r._f = (_d);\
		_g_pe_clc0_hw_param_data_o24.reg_mask.data->_r._f = 0;}
#define PE_DNT1_HW_O24_CLC_SET_USER(_r, _f, _d)	\
	{	_g_pe_clc1_hw_param_data_o24.reg_user.data->_r._f = (_d);\
		_g_pe_clc1_hw_param_data_o24.reg_mask.data->_r._f = 0;}


#define PE_DNT_HW_O24_CLC_WR01(_r, _f1, _d1)	\
	{	PE_ND0_O24_QWr01(_r, _f1, _d1);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f1, _d1);}
#define PE_DNT_HW_O24_CLC_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND0_O24_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f1, _d1);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f2, _d2);}
#define PE_DNT_HW_O24_CLC_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND0_O24_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f1, _d1);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f2, _d2);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f3, _d3);}
#define PE_DNT_HW_O24_CLC_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND0_O24_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f1, _d1);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f2, _d2);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f3, _d3);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f4, _d4);}
#define PE_DNT_HW_O24_CLC_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND0_O24_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f1, _d1);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f2, _d2);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f3, _d3);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f4, _d4);\
		PE_DNT_HW_O24_CLC_SET_USER(_r, _f5, _d5);}

#define PE_DNT_HW_O24_VFY_SET_USER(_r, _f, _d)	\
	{	_g_pe_vfy0_hw_param_data_o24.reg_user.data->_r._f = (_d);\
		_g_pe_vfy0_hw_param_data_o24.reg_mask.data->_r._f = 0;}

#define PE_DNT1_HW_O24_VFY_SET_USER(_r, _f, _d)	\
	{	_g_pe_vfy1_hw_param_data_o24.reg_user.data->_r._f = (_d);\
		_g_pe_vfy1_hw_param_data_o24.reg_mask.data->_r._f = 0;}

#define PE_DNT_HW_O24_VFY_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_O24_QWr01(_r, _f1, _d1);\
		PE_DNT_HW_O24_VFY_SET_USER(_r, _f1, _d1);}
#define PE_DNT_HW_O24_VFY_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_O24_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_DNT_HW_O24_VFY_SET_USER(_r, _f1, _d1);\
		PE_DNT_HW_O24_VFY_SET_USER(_r, _f2, _d2);}
#define PE_DNT_HW_O24_VFY_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_O24_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_DNT_HW_O24_VFY_SET_USER(_r, _f1, _d1);\
		PE_DNT_HW_O24_VFY_SET_USER(_r, _f2, _d2);\
		PE_DNT_HW_O24_VFY_SET_USER(_r, _f3, _d3);}

/* set table */
#define PE_DNT_IPC_HW_O24_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_DNT_HW_O24_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_DNT_HW_O24_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_DNT_HW_O24_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_DNT_HW_O24_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"[%s,%d] _data is null, not ready.\n", __F__, __L__);\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_O24_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			if(_i == PE_DNT_HW_O24_NUM_OF_IPC00_IN_TABLE)\
				continue;\
			ret = PE_REG_O24_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_O24_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_DNT_HW_O24_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_DNT_HW_O24_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_DNT_HW_O24_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_DNT_HW_O24_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_DNT_HW_O24_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_DNT_HW_O24_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"[%s,%d] _data is null, not ready.\n", __F__, __L__);\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_O24_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			ret = PE_REG_O24_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_O24_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_DNT_HW_O24_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

/* pre proc ipc table, not to write some reg,bit */
#ifdef PE_DNT_HW_O24_USE_PRE_PROC_IPC_REG_TABLE
#define PE_DNT_HW_O24_PRE_PROC_IPC_REG_TABLE(__base)	\
	do{\
		UINT32 _rd_data[5];\
		if ((__base) == PE_O24_REG_WRITE_BASE)\
		{\
			PE_ND0_O24_RdFL(ipc_ctrl_00);\
			PE_ND0_O24_RdFL(ipc_ctrl_01);\
			PE_ND0_O24_RdFL(ipc_ctrl_06);\
			PE_ND0_O24_RdFL(ipc_ctrl_30);\
			PE_ND0_O24_Rd01(ipc_ctrl_00, cr_luma_mode, _rd_data[0]);\
			PE_ND0_O24_Rd01(ipc_ctrl_00, cr_chroma_mode, _rd_data[1]);\
			PE_ND0_O24_Rd01(ipc_ctrl_00, cr_film_mode_enable, _rd_data[2]);\
			PE_ND0_O24_Rd01(ipc_ctrl_01, cr_game_mode, _rd_data[3]);\
			PE_ND0_O24_Rd01(ipc_ctrl_06, cr_motion_iir_en, _rd_data[4]);\
			PE_DNT0_HW_O24_IPC_SET_USER(ipc_ctrl_00, cr_luma_mode, _rd_data[0]);\
			PE_DNT0_HW_O24_IPC_SET_USER(ipc_ctrl_00, cr_chroma_mode, _rd_data[1]);\
			PE_DNT0_HW_O24_IPC_SET_USER(ipc_ctrl_00, cr_film_mode_enable, _rd_data[2]);\
			PE_DNT0_HW_O24_IPC_SET_USER(ipc_ctrl_01, cr_game_mode, _rd_data[3]);\
			PE_DNT0_HW_O24_IPC_SET_USER(ipc_ctrl_06, cr_motion_iir_en, _rd_data[4]);\
		}\
	}while(0)
#define PE_DNT1_HW_O24_PRE_PROC_IPC_REG_TABLE(__base)	\
	do{\
		UINT32 _rd_data[5];\
		if ((__base) == PE_O24_REG_WRITE_BASE)\
		{\
			PE_ND1_O24_RdFL(ipc_ctrl_00);\
			PE_ND1_O24_RdFL(ipc_ctrl_01);\
			PE_ND1_O24_RdFL(ipc_ctrl_06);\
			PE_ND1_O24_RdFL(ipc_ctrl_30);\
			PE_ND1_O24_Rd01(ipc_ctrl_00, cr_luma_mode, _rd_data[0]);\
			PE_ND1_O24_Rd01(ipc_ctrl_00, cr_chroma_mode, _rd_data[1]);\
			PE_ND1_O24_Rd01(ipc_ctrl_00, cr_film_mode_enable, _rd_data[2]);\
			PE_ND1_O24_Rd01(ipc_ctrl_01, cr_game_mode, _rd_data[3]);\
			PE_ND1_O24_Rd01(ipc_ctrl_06, cr_motion_iir_en, _rd_data[4]);\
			PE_DNT1_HW_O24_IPC_SET_USER(ipc_ctrl_00, cr_luma_mode, _rd_data[0]);\
			PE_DNT1_HW_O24_IPC_SET_USER(ipc_ctrl_00, cr_chroma_mode, _rd_data[1]);\
			PE_DNT1_HW_O24_IPC_SET_USER(ipc_ctrl_00, cr_film_mode_enable, _rd_data[2]);\
			PE_DNT1_HW_O24_IPC_SET_USER(ipc_ctrl_01, cr_game_mode, _rd_data[3]);\
			PE_DNT1_HW_O24_IPC_SET_USER(ipc_ctrl_06, cr_motion_iir_en, _rd_data[4]);\
		}\
	}while(0)

#else
#define PE_DNT_HW_O24_PRE_PROC_IPC_REG_TABLE(__base)
#define PE_DNT1_HW_O24_PRE_PROC_IPC_REG_TABLE(__base)
#endif


/* ipc 0*/
#define PE_DNT_HW_O24_IPC_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_ipc0_hw_param_data_o24.reg_dflt.addr;\
		UINT32 *_user = _g_pe_ipc0_hw_param_data_o24.reg_user.addr;\
		UINT32 *_mask = _g_pe_ipc0_hw_param_data_o24.reg_mask.addr;\
		UINT32 *_data = _g_pe_ipc0_hw_param_data_o24.reg_data.addr;\
		PE_DNT_HW_O24_PRE_PROC_IPC_REG_TABLE(__base);\
		PE_DNT_IPC_HW_O24_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* ipc 1*/
#define PE_DNT1_HW_O24_IPC_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_ipc1_hw_param_data_o24.reg_dflt.addr;\
		UINT32 *_user = _g_pe_ipc1_hw_param_data_o24.reg_user.addr;\
		UINT32 *_mask = _g_pe_ipc1_hw_param_data_o24.reg_mask.addr;\
		UINT32 *_data = _g_pe_ipc1_hw_param_data_o24.reg_data.addr;\
		PE_DNT1_HW_O24_PRE_PROC_IPC_REG_TABLE(__base);\
		PE_DNT_IPC_HW_O24_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* pre proc clc table, not to write some reg,bit */
#define PE_DNT_HW_O24_PRE_PROC_CLC_REG_TABLE(__base)	\
	do{\
		UINT32 _rd_data[2];\
		if ((__base) == PE_O24_REG_WRITE_BASE)\
		{\
			PE_ND0_O24_RdFL(clc_ctrl_00);\
			PE_ND0_O24_Rd01(clc_ctrl_00, cl_filter_enable, _rd_data[0]);\
			PE_ND0_O24_Rd01(clc_ctrl_00, clc_detection_enable, _rd_data[1]);\
			PE_DNT_HW_O24_CLC_SET_USER(clc_ctrl_00, cl_filter_enable, _rd_data[0]);\
			PE_DNT_HW_O24_CLC_SET_USER(clc_ctrl_00, clc_detection_enable, _rd_data[1]);\
		}\
	}while(0)
#define PE_DNT1_HW_O24_PRE_PROC_CLC_REG_TABLE(__base)	\
	do{\
		UINT32 _rd_data[2];\
		if ((__base) == PE_O24_REG_WRITE_BASE)\
		{\
			PE_ND1_O24_RdFL(clc_ctrl_00);\
			PE_ND1_O24_Rd01(clc_ctrl_00, cl_filter_enable, _rd_data[0]);\
			PE_ND1_O24_Rd01(clc_ctrl_00, clc_detection_enable, _rd_data[1]);\
			PE_DNT1_HW_O24_CLC_SET_USER(clc_ctrl_00, cl_filter_enable, _rd_data[0]);\
			PE_DNT1_HW_O24_CLC_SET_USER(clc_ctrl_00, clc_detection_enable, _rd_data[1]);\
		}\
	}while(0)


/* clc */
#define PE_DNT_HW_O24_CLC_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_clc0_hw_param_data_o24.reg_dflt.addr;\
		UINT32 *_user = _g_pe_clc0_hw_param_data_o24.reg_user.addr;\
		UINT32 *_mask = _g_pe_clc0_hw_param_data_o24.reg_mask.addr;\
		UINT32 *_data = _g_pe_clc0_hw_param_data_o24.reg_data.addr;\
		PE_DNT_HW_O24_PRE_PROC_CLC_REG_TABLE(__base);\
		PE_DNT_HW_O24_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* clc 1 */
#define PE_DNT1_HW_O24_CLC_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_clc1_hw_param_data_o24.reg_dflt.addr;\
		UINT32 *_user = _g_pe_clc1_hw_param_data_o24.reg_user.addr;\
		UINT32 *_mask = _g_pe_clc1_hw_param_data_o24.reg_mask.addr;\
		UINT32 *_data = _g_pe_clc1_hw_param_data_o24.reg_data.addr;\
		PE_DNT1_HW_O24_PRE_PROC_CLC_REG_TABLE(__base);\
		PE_DNT_HW_O24_SET_REG_TABLE(__tbl, __base);\
	}while (0)


/* vfy */
#define PE_DNT_HW_O24_VFY_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_vfy0_hw_param_data_o24.reg_dflt.addr;\
		UINT32 *_user = _g_pe_vfy0_hw_param_data_o24.reg_user.addr;\
		UINT32 *_mask = _g_pe_vfy0_hw_param_data_o24.reg_mask.addr;\
		UINT32 *_data = _g_pe_vfy0_hw_param_data_o24.reg_data.addr;\
		PE_DNT_HW_O24_SET_REG_TABLE(__tbl, __base);\
	}while (0)
/* vfy 1*/
#define PE_DNT1_HW_O24_VFY_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_vfy1_hw_param_data_o24.reg_dflt.addr;\
		UINT32 *_user = _g_pe_vfy1_hw_param_data_o24.reg_user.addr;\
		UINT32 *_mask = _g_pe_vfy1_hw_param_data_o24.reg_mask.addr;\
		UINT32 *_data = _g_pe_vfy1_hw_param_data_o24.reg_data.addr;\
		PE_DNT_HW_O24_SET_REG_TABLE(__tbl, __base);\
	}while (0)

#endif

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

extern UINT32	g_pe_inf_o24_vr360_mode;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static PE_DNT_HW_O24_IPC_FMT PE_DNT_HW_O24_ConvDispInfoToIpcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_DNT_HW_O24_VFY_FMT PE_DNT_HW_O24_ConvDispInfoToVfyFmt(LX_PE_INF_DISPLAY_T *disp_inf);
#ifdef PE_DNT_HW_O24_USE_CLC_DEFAULT
static PE_DNT_HW_O24_CLC_FMT PE_DNT_HW_O24_ConvDispInfoToClcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static int PE_DNT_HW_O24_SetClcDefault(PE_DNT_HW_O24_CLC_FMT cur0_clc_fmt);
static int PE_DNT1_HW_O24_SetClcDefault(PE_DNT_HW_O24_CLC_FMT cur1_clc_fmt);
#endif
//static int PE_DNT_HW_O24_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_DNT_HW_O24_SetIpcDefault(PE_DNT_HW_O24_IPC_FMT cur0_ipc_fmt);
static int PE_DNT1_HW_O24_SetIpcDefault(PE_DNT_HW_O24_IPC_FMT cur1_ipc_fmt);
static int PE_DNT_HW_O24_SetVfyDefault(PE_DNT_HW_O24_VFY_FMT cur0_vfy_fmt);
static int PE_DNT1_HW_O24_SetVfyDefault(PE_DNT_HW_O24_VFY_FMT cur1_vfy_fmt);
#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
static int PE_DNT_HW_O24_CreateDataTable(UINT32 index);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_dnt_hw_o24_trace=0x0;		//default should be off.
static PE_DNT_HW_O24_SETTINGS_T _g_pe_dnt_hw_o24_info;
#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
static PE_IPC_HW_PARAM_DATA_O24_T _g_pe_ipc0_hw_param_data_o24 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_CLC_HW_PARAM_DATA_O24_T _g_pe_clc0_hw_param_data_o24 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_VFY_HW_PARAM_DATA_O24_T _g_pe_vfy0_hw_param_data_o24 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_IPC_HW_PARAM_DATA_O24_T _g_pe_ipc1_hw_param_data_o24 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_CLC_HW_PARAM_DATA_O24_T _g_pe_clc1_hw_param_data_o24 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_VFY_HW_PARAM_DATA_O24_T _g_pe_vfy1_hw_param_data_o24 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif
static UINT32 _g_pre_vft_12=0xff;
static UINT32 _g_pre_vfy_flt_en0 = 0xff;		//pre vfy_en0


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init dnt
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		_g_pe_dnt_hw_o24_info.ipc0a_fmt = PE_DNT_O24_IPC_NUM;
		_g_pe_dnt_hw_o24_info.clc0a_fmt = PE_DNT_O24_CLC_NUM;
		_g_pe_dnt_hw_o24_info.vfy0a_fmt = PE_DNT_O24_VFY_NUM;
		_g_pe_dnt_hw_o24_info.ipc1a_fmt = PE_DNT_O24_IPC_NUM;
		_g_pe_dnt_hw_o24_info.clc1a_fmt = PE_DNT_O24_CLC_NUM;
		_g_pe_dnt_hw_o24_info.vfy1a_fmt = PE_DNT_O24_VFY_NUM;
		_g_pe_dnt_hw_o24_info.force_cbcr_enb_nd0 = 0x0;
		_g_pe_dnt_hw_o24_info.force_y_max_th_nd0 = 0x5f;
		_g_pe_dnt_hw_o24_info.force_cbcr_enb_nd1 = 0x0;
		_g_pe_dnt_hw_o24_info.force_y_max_th_nd1 = 0x5f;
		_g_pre_vft_12=0xff;
		_g_pre_vfy_flt_en0=0xff;
		if(PE_KDRV_VER_O24)
		{
			PE_DNT_HW_O24_DBG_PRINT("init ipc, tpd.\n");
			#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
			/* init ipc(nd1,2) */
			ret = PE_DNT_HW_O24_CreateDataTable(PE_DNT_HW_O24_TBL_IDX_IPC);
			PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"PE_DNT_HW_O24_CreateDataTable() error.\n");
			PE_DNT_HW_O24_IPC_REG_TABLE(ipc_l_hd_default_o24,PE_O24_REG_WRITE_BASE);
			/* init clc(nd1 only) */
			ret = PE_DNT_HW_O24_CreateDataTable(PE_DNT_HW_O24_TBL_IDX_CLC);
			PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"PE_DNT_HW_O24_CreateDataTable() error.\n");
			//PE_DNT_HW_O24_CLC_REG_TABLE(clc_l_init_o24,PE_O24_REG_WRITE_BASE);
			/* init vfy(dnr1,2 only) */
			ret = PE_DNT_HW_O24_CreateDataTable(PE_DNT_HW_O24_TBL_IDX_VFY);
			PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"PE_DNT_HW_O24_CreateDataTable() error.\n");
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_hd_p_default_o24,PE_O24_REG_WRITE_BASE);
			#else
			/* init ipc(nd1,2) */
			PE_SET_REG_TABLE(DNT_HW_O24,ipc_l_hd_default_o24,PE_O24_REG_WRITE_BASE);
			/* init clc(nd1 only) */
			PE_SET_REG_TABLE(DNT_HW_O24,clc_l_init_o24,PE_O24_REG_WRITE_BASE);
			/* init vflt y */
			PE_SET_REG_TABLE(DNT_HW_O24,vflt_y_l_hd_p_default_o24,PE_O24_REG_WRITE_BASE);
			#endif
			/* init nd0 tpd force ycbcr */
			PE_ND0_O24_RdFL(tpd_ctrl_07);
			PE_ND0_O24_RdFL(tpd_ctrl_08);
			PE_ND0_O24_RdFL(tpd_ctrl_09);
			PE_ND0_O24_Wr01(tpd_ctrl_07, reg_force_y,         0x0);
			PE_ND0_O24_Wr01(tpd_ctrl_07, reg_force_y_max_th,  _g_pe_dnt_hw_o24_info.force_y_max_th_nd0);
			PE_ND0_O24_Wr01(tpd_ctrl_07, reg_force_y_min_th,  0x0);
			PE_ND0_O24_Wr01(tpd_ctrl_07, reg_force_y_enable,  0x0);
			PE_ND0_O24_Wr01(tpd_ctrl_08, reg_force_cb,        0x200);
			PE_ND0_O24_Wr01(tpd_ctrl_08, reg_force_cb_max_th, 0x205);
			PE_ND0_O24_Wr01(tpd_ctrl_08, reg_force_cb_min_th, 0x1e0);
			PE_ND0_O24_Wr01(tpd_ctrl_08, reg_force_cb_enable, _g_pe_dnt_hw_o24_info.force_cbcr_enb_nd0);
			PE_ND0_O24_Wr01(tpd_ctrl_09, reg_force_cr,        0x200);
			PE_ND0_O24_Wr01(tpd_ctrl_09, reg_force_cr_max_th, 0x205);
			PE_ND0_O24_Wr01(tpd_ctrl_09, reg_force_cr_min_th, 0x1e0);
			PE_ND0_O24_Wr01(tpd_ctrl_09, reg_force_cr_enable, _g_pe_dnt_hw_o24_info.force_cbcr_enb_nd0);
			PE_ND0_O24_WrFL(tpd_ctrl_07);
			PE_ND0_O24_WrFL(tpd_ctrl_08);
			PE_ND0_O24_WrFL(tpd_ctrl_09);
		}
		else
		{
			PE_DNT_HW_O24_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
/**
 * create data table
 *
 * @param   index [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_DNT_HW_O24_TBL_INDX
 * @author
 */
static int PE_DNT_HW_O24_CreateDataTable(UINT32 index)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	PE_IPC_HW_PARAM_DATA_O24_T *p_ipc0_o24 = &_g_pe_ipc0_hw_param_data_o24;
	PE_CLC_HW_PARAM_DATA_O24_T *p_clc0_o24 = &_g_pe_clc0_hw_param_data_o24;
	PE_VFY_HW_PARAM_DATA_O24_T *p_vfy0_o24 = &_g_pe_vfy0_hw_param_data_o24;
	PE_IPC_HW_PARAM_DATA_O24_T *p_ipc1_o24 = &_g_pe_ipc1_hw_param_data_o24;
	PE_CLC_HW_PARAM_DATA_O24_T *p_clc1_o24 = &_g_pe_clc1_hw_param_data_o24;
	PE_VFY_HW_PARAM_DATA_O24_T *p_vfy1_o24 = &_g_pe_vfy1_hw_param_data_o24;

	PE_DNT_HW_O24_CHECK_CODE(index>=PE_DNT_HW_O24_TBL_IDX_NUM, return RET_ERROR, \
		"[%s,%d] index(%d) invalid.\n", __F__, __L__, index);

	if (index == PE_DNT_HW_O24_TBL_IDX_IPC)
	{
		/* ipc 0 */
		/* create dflt table */
		if (p_ipc0_o24->reg_dflt.addr == NULL)
		{
			p_ipc0_o24->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IPC_HW_PARAM_REG_O24_T));
		}
		/* create user table */
		if (p_ipc0_o24->reg_user.addr == NULL)
		{
			p_ipc0_o24->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IPC_HW_PARAM_REG_O24_T));
			memset((p_ipc0_o24->reg_user.addr), 0, sizeof(PE_IPC_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* create mask table */
		if (p_ipc0_o24->reg_mask.addr == NULL)
		{
			p_ipc0_o24->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IPC_HW_PARAM_REG_O24_T));
			memset((p_ipc0_o24->reg_mask.addr), -1, sizeof(PE_IPC_HW_PARAM_REG_O24_T));// 0xffffffff
		}
		/* create data table */
		if (p_ipc0_o24->reg_data.addr == NULL)
		{
			p_ipc0_o24->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IPC_HW_PARAM_REG_O24_T));
			memset((p_ipc0_o24->reg_data.addr), 0, sizeof(PE_IPC_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* ipc 1 */
		/* create dflt table */
		if (p_ipc1_o24->reg_dflt.addr == NULL)
		{
			p_ipc1_o24->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IPC_HW_PARAM_REG_O24_T));
		}
		/* create user table */
		if (p_ipc1_o24->reg_user.addr == NULL)
		{
			p_ipc1_o24->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IPC_HW_PARAM_REG_O24_T));
			memset((p_ipc1_o24->reg_user.addr), 0, sizeof(PE_IPC_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* create mask table */
		if (p_ipc1_o24->reg_mask.addr == NULL)
		{
			p_ipc1_o24->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IPC_HW_PARAM_REG_O24_T));
			memset((p_ipc1_o24->reg_mask.addr), -1, sizeof(PE_IPC_HW_PARAM_REG_O24_T));// 0xffffffff
		}
		/* create data table */
		if (p_ipc1_o24->reg_data.addr == NULL)
		{
			p_ipc1_o24->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IPC_HW_PARAM_REG_O24_T));
			memset((p_ipc1_o24->reg_data.addr), 0, sizeof(PE_IPC_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* report result */
		if (p_ipc0_o24->reg_dflt.addr != NULL && p_ipc0_o24->reg_user.addr != NULL && \
			p_ipc0_o24->reg_mask.addr != NULL && p_ipc0_o24->reg_data.addr != NULL && \
			p_ipc1_o24->reg_dflt.addr != NULL && p_ipc1_o24->reg_user.addr != NULL && \
			p_ipc1_o24->reg_mask.addr != NULL && p_ipc1_o24->reg_data.addr != NULL )
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_DNT_HW_O24_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s,%s,%s,%s,%s\n", \
				PE_DNT_HW_O24_TBL_IDX_TO_STR(index), \
				(p_ipc0_o24->reg_dflt.addr == NULL)? "x":"o", \
				(p_ipc0_o24->reg_user.addr == NULL)? "x":"o", \
				(p_ipc0_o24->reg_mask.addr == NULL)? "x":"o", \
				(p_ipc0_o24->reg_data.addr == NULL)? "x":"o", \
				(p_ipc1_o24->reg_dflt.addr == NULL)? "x":"o", \
				(p_ipc1_o24->reg_user.addr == NULL)? "x":"o", \
				(p_ipc1_o24->reg_mask.addr == NULL)? "x":"o", \
				(p_ipc1_o24->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_DNT_HW_O24_TBL_IDX_CLC)
	{
		/* clc 0 */
		/* create dflt table */
		if (p_clc0_o24->reg_dflt.addr == NULL)
		{
			p_clc0_o24->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CLC_HW_PARAM_REG_O24_T));
		}
		/* create user table */
		if (p_clc0_o24->reg_user.addr == NULL)
		{
			p_clc0_o24->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CLC_HW_PARAM_REG_O24_T));
			memset((p_clc0_o24->reg_user.addr), 0, sizeof(PE_CLC_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* create mask table */
		if (p_clc0_o24->reg_mask.addr == NULL)
		{
			p_clc0_o24->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CLC_HW_PARAM_REG_O24_T));
			memset((p_clc0_o24->reg_mask.addr), -1, sizeof(PE_CLC_HW_PARAM_REG_O24_T));// 0xffffffff
		}
		/* create data table */
		if (p_clc0_o24->reg_data.addr == NULL)
		{
			p_clc0_o24->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CLC_HW_PARAM_REG_O24_T));
			memset((p_clc0_o24->reg_data.addr), 0, sizeof(PE_CLC_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* clc 1 */
		/* create dflt table */
		if (p_clc1_o24->reg_dflt.addr == NULL)
		{
			p_clc1_o24->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CLC_HW_PARAM_REG_O24_T));
		}
		/* create user table */
		if (p_clc1_o24->reg_user.addr == NULL)
		{
			p_clc1_o24->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CLC_HW_PARAM_REG_O24_T));
			memset((p_clc1_o24->reg_user.addr), 0, sizeof(PE_CLC_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* create mask table */
		if (p_clc1_o24->reg_mask.addr == NULL)
		{
			p_clc1_o24->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CLC_HW_PARAM_REG_O24_T));
			memset((p_clc1_o24->reg_mask.addr), -1, sizeof(PE_CLC_HW_PARAM_REG_O24_T));// 0xffffffff
		}
		/* create data table */
		if (p_clc1_o24->reg_data.addr == NULL)
		{
			p_clc1_o24->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CLC_HW_PARAM_REG_O24_T));
			memset((p_clc1_o24->reg_data.addr), 0, sizeof(PE_CLC_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* report result */
		if (p_clc0_o24->reg_dflt.addr != NULL && p_clc0_o24->reg_user.addr != NULL && \
			p_clc0_o24->reg_mask.addr != NULL && p_clc0_o24->reg_data.addr != NULL && \
			p_clc1_o24->reg_dflt.addr != NULL && p_clc1_o24->reg_user.addr != NULL && \
			p_clc1_o24->reg_mask.addr != NULL && p_clc1_o24->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_DNT_HW_O24_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s,%s,%s,%s,%s\n", \
				PE_DNT_HW_O24_TBL_IDX_TO_STR(index), \
				(p_clc0_o24->reg_dflt.addr == NULL)? "x":"o", \
				(p_clc0_o24->reg_user.addr == NULL)? "x":"o", \
				(p_clc0_o24->reg_mask.addr == NULL)? "x":"o", \
				(p_clc0_o24->reg_data.addr == NULL)? "x":"o", \
				(p_clc1_o24->reg_dflt.addr == NULL)? "x":"o", \
				(p_clc1_o24->reg_user.addr == NULL)? "x":"o", \
				(p_clc1_o24->reg_mask.addr == NULL)? "x":"o", \
				(p_clc1_o24->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_DNT_HW_O24_TBL_IDX_VFY)
	{
		/* vflt 0 */
		/* create dflt table */
		if (p_vfy0_o24->reg_dflt.addr == NULL)
		{
			p_vfy0_o24->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VFY_HW_PARAM_REG_O24_T));
		}
		/* create user table */
		if (p_vfy0_o24->reg_user.addr == NULL)
		{
			p_vfy0_o24->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VFY_HW_PARAM_REG_O24_T));
			memset((p_vfy0_o24->reg_user.addr), 0, sizeof(PE_VFY_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* create mask table */
		if (p_vfy0_o24->reg_mask.addr == NULL)
		{
			p_vfy0_o24->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VFY_HW_PARAM_REG_O24_T));
			memset((p_vfy0_o24->reg_mask.addr), -1, sizeof(PE_VFY_HW_PARAM_REG_O24_T));// 0xffffffff
		}
		/* create data table */
		if (p_vfy0_o24->reg_data.addr == NULL)
		{
			p_vfy0_o24->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VFY_HW_PARAM_REG_O24_T));
			memset((p_vfy0_o24->reg_data.addr), 0, sizeof(PE_VFY_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* vflt 1 */
		/* create dflt table */
		if (p_vfy1_o24->reg_dflt.addr == NULL)
		{
			p_vfy1_o24->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VFY_HW_PARAM_REG_O24_T));
		}
		/* create user table */
		if (p_vfy1_o24->reg_user.addr == NULL)
		{
			p_vfy1_o24->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VFY_HW_PARAM_REG_O24_T));
			memset((p_vfy1_o24->reg_user.addr), 0, sizeof(PE_VFY_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* create mask table */
		if (p_vfy1_o24->reg_mask.addr == NULL)
		{
			p_vfy1_o24->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VFY_HW_PARAM_REG_O24_T));
			memset((p_vfy1_o24->reg_mask.addr), -1, sizeof(PE_VFY_HW_PARAM_REG_O24_T));// 0xffffffff
		}
		/* create data table */
		if (p_vfy1_o24->reg_data.addr == NULL)
		{
			p_vfy1_o24->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_VFY_HW_PARAM_REG_O24_T));
			memset((p_vfy1_o24->reg_data.addr), 0, sizeof(PE_VFY_HW_PARAM_REG_O24_T));	// 0x0
		}
		/* report result */
		if (p_vfy0_o24->reg_dflt.addr != NULL && p_vfy0_o24->reg_user.addr != NULL && \
			p_vfy0_o24->reg_mask.addr != NULL && p_vfy0_o24->reg_data.addr != NULL && \
			p_vfy1_o24->reg_dflt.addr != NULL && p_vfy1_o24->reg_user.addr != NULL && \
			p_vfy1_o24->reg_mask.addr != NULL && p_vfy1_o24->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_DNT_HW_O24_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s,%s,%s,%s,%s\n", \
				PE_DNT_HW_O24_TBL_IDX_TO_STR(index), \
				(p_vfy0_o24->reg_dflt.addr == NULL)? "x":"o", \
				(p_vfy0_o24->reg_user.addr == NULL)? "x":"o", \
				(p_vfy0_o24->reg_mask.addr == NULL)? "x":"o", \
				(p_vfy0_o24->reg_data.addr == NULL)? "x":"o", \
				(p_vfy1_o24->reg_dflt.addr == NULL)? "x":"o", \
				(p_vfy1_o24->reg_user.addr == NULL)? "x":"o", \
				(p_vfy1_o24->reg_mask.addr == NULL)? "x":"o", \
				(p_vfy1_o24->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else
	{
		PE_DNT_HW_O24_DBG_PRINT("nothing to do\n");	ret = RET_OK;
	}
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}

#endif
/**
 * debug setting
 *
 * @param   *pstParams [in]LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_DNT_HW_O24_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(DNT)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_dnt_hw_o24_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(DNT)))? 0x1:0x0;
		}
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}

/**
 * set dnt default(for O24X)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	PE_INF_O24_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	LX_PE_INF_DISPLAY_T *cur1_inf = NULL;
	PE_DNT_HW_O24_IPC_FMT cur0_ipc_fmt;
	PE_DNT_HW_O24_IPC_FMT cur1_ipc_fmt;
	#ifdef PE_DNT_HW_O24_USE_CLC_DEFAULT
	PE_DNT_HW_O24_CLC_FMT cur0_clc_fmt;
	PE_DNT_HW_O24_CLC_FMT cur1_clc_fmt;
	#endif
	PE_DNT_HW_O24_VFY_FMT cur0_vfy_fmt;
	PE_DNT_HW_O24_VFY_FMT cur1_vfy_fmt;
	UINT32 cur0_force_cbcr_enb = 0, cur0_force_y_max_th = 0;
	UINT32 cur1_force_cbcr_enb = 0, cur1_force_y_max_th = 0;
	PE_DNT_HW_O24_SETTINGS_T *pInfo = &_g_pe_dnt_hw_o24_info;
	PE_O24_ND_IPC_CTRL_27_T data_ipc_27;
	PE_O24_ND_IPC_CTRL_04_T data_ipc_04;
	//PE_O24_ND_IPC_CTRL_00_T data_ipc_00;
	PE_IPC_HW_PARAM_REG_O24_T *p_ipc0_dflt = _g_pe_ipc0_hw_param_data_o24.reg_dflt.data;
	PE_IPC_HW_PARAM_REG_O24_T *p_ipc1_dflt = _g_pe_ipc1_hw_param_data_o24.reg_dflt.data;
	
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_O24_GetCurInfSettings(&inf_set);
		PE_DNT_HW_O24_CHECK_CODE(ret, break, \
			"[%s,%d] PE_INF_O24_GetCurInfSettings() error.\n", __F__, __L__);
		cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		cur1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(cur0_inf);
		CHECK_KNULL(cur1_inf);
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			/* nd12 tpd */
			if((cur0_inf->src_type==LX_PE_SRC_DTV && \
				cur0_inf->fmt_type==LX_PE_FMT_HD && \
				cur0_inf->scan_type==LX_PE_SCAN_INTERLACE) || \
				cur0_inf->src_type==LX_PE_SRC_ATV || \
				cur0_inf->src_type==LX_PE_SRC_CVBS || \
				cur0_inf->src_type==LX_PE_SRC_SCART || \
				cur0_inf->src_type==LX_PE_SRC_COMP)
			{
				cur0_force_cbcr_enb = 0x1;
				cur0_force_y_max_th = 0x5f;
			}
			else if (cur0_inf->src_type==LX_PE_SRC_HDMI && cur0_inf->hdmi_type==LX_PE_HDMI_TV)
			{
				cur0_force_cbcr_enb = 0x1;
				cur0_force_y_max_th = 0x48;
			}
			else
			{
				cur0_force_cbcr_enb = 0x0;
				cur0_force_y_max_th = 0x5f;
			}
			if ((pInfo->force_cbcr_enb_nd0!= cur0_force_cbcr_enb) || \
				(pInfo->force_y_max_th_nd0!= cur0_force_y_max_th))
			{
				PE_ND0_O24_QWr01(tpd_ctrl_08,reg_force_cb_enable,cur0_force_cbcr_enb);
				PE_ND0_O24_QWr01(tpd_ctrl_09,reg_force_cr_enable,cur0_force_cbcr_enb);
				PE_ND0_O24_QWr01(tpd_ctrl_07,reg_force_y_max_th, cur0_force_y_max_th);
				PE_INF_HW_O24_BACKUP_TRACE("[DNT]force,th:%d,%d -> %d,%d(sr,fmt,sc:%d,%d,%d)",\
					pInfo->force_cbcr_enb_nd0,pInfo->force_y_max_th_nd0,cur0_force_cbcr_enb,cur0_force_y_max_th,\
					cur0_inf->src_type,cur0_inf->fmt_type,cur0_inf->scan_type);
				pInfo->force_cbcr_enb_nd0 = cur0_force_cbcr_enb;
				pInfo->force_y_max_th_nd0 = cur0_force_y_max_th;
			}
			/* nd12 ipc */
			cur0_ipc_fmt = PE_DNT_HW_O24_ConvDispInfoToIpcFmt(cur0_inf);
			PE_DNT_HW_O24_DBG_PRINT_IPC_FMT_STATE(pInfo->ipc0a_fmt,cur0_ipc_fmt);
			PE_DNT_HW_O24_DBG_PRINT("pre src:%d, cur src:%d\n",pInfo->ipc0a_fmt,cur0_ipc_fmt);
			if(pInfo->ipc0a_fmt!=cur0_ipc_fmt)
			{
				ret = PE_DNT_HW_O24_SetIpcDefault(cur0_ipc_fmt);
				PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DNT_HW_O24_SetIpcDefault() error.\n", __F__, __L__);
				pInfo->ipc0a_fmt=cur0_ipc_fmt;
				data_ipc_27 = _g_pe_ipc0_hw_param_data_o24.reg_dflt.data->ipc_ctrl_27;
				data_ipc_04 = _g_pe_ipc0_hw_param_data_o24.reg_dflt.data->ipc_ctrl_04;
				PE_ND0_O24_QWr04(nd_fsw_ctrl_00,chroma_st_flt_ctrl_x0, data_ipc_27.chroma_st_flt_ctrl_x0,\
													chroma_st_flt_ctrl_x1, data_ipc_27.chroma_st_flt_ctrl_x1,\
													luma_st_flt_ctrl_x0, data_ipc_27.luma_st_flt_ctrl_x0,\
													luma_st_flt_ctrl_x1, data_ipc_27.luma_st_flt_ctrl_x1);
				PE_ND0_O24_QWr02(nd_fsw_ctrl_01, motion_x_tearing_gain, data_ipc_04.motion_x_tearing_gain,\
												   motion_gain,			  data_ipc_04.motion_gain);
				PE_ND0_O24_RdFL(nd_fsw_ctrl_02);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_luma_mode		  ,p_ipc0_dflt->ipc_ctrl_00.cr_luma_mode);
				//PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_n1_cc_blend_en	  ,p_ipc0_dflt->ipc_ctrl_00.cr_n1_cc_blend_en);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_chroma_mode 	  ,p_ipc0_dflt->ipc_ctrl_00.cr_chroma_mode);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_integer_edi 	  ,p_ipc0_dflt->ipc_ctrl_00.cr_integer_edi);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_chroma_edi		  ,p_ipc0_dflt->ipc_ctrl_00.cr_chroma_edi);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_st_2d_v_flt_range2,p_ipc0_dflt->ipc_ctrl_00.cr_st_2d_v_flt_range2);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_st_2d_v_flt_range ,p_ipc0_dflt->ipc_ctrl_00.cr_st_2d_v_flt_range);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_ori_3d_blur_y	  ,p_ipc0_dflt->ipc_ctrl_00.cr_ori_3d_blur_y);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_ori_3d_blur_c	  ,p_ipc0_dflt->ipc_ctrl_00.cr_ori_3d_blur_c);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_tava_v_edge_adap  ,p_ipc0_dflt->ipc_ctrl_00.cr_tava_v_edge_adap);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_tava_debug_mode   ,p_ipc0_dflt->ipc_ctrl_00.cr_tava_debug_mode);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_tava_st_adap	  ,p_ipc0_dflt->ipc_ctrl_00.cr_tava_st_adap);
				//PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_tava_en 		  ,p_ipc0_dflt->ipc_ctrl_00.cr_tava_en);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_hmc_force_fmd	  ,p_ipc0_dflt->ipc_ctrl_00.cr_hmc_force_fmd);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_st_2d_v_flt_en	  ,p_ipc0_dflt->ipc_ctrl_00.cr_st_2d_v_flt_en);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_clc_fmd_off 	  ,p_ipc0_dflt->ipc_ctrl_00.cr_clc_fmd_off);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_chroma_tava_only  ,p_ipc0_dflt->ipc_ctrl_00.cr_chroma_tava_only);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_film_auto_gain	  ,p_ipc0_dflt->ipc_ctrl_00.cr_film_auto_gain);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_film_apply_c	  ,p_ipc0_dflt->ipc_ctrl_00.cr_film_apply_c);
				PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_film_apply_y	  ,p_ipc0_dflt->ipc_ctrl_00.cr_film_apply_y);
				//PE_ND0_O24_Wr01(nd_fsw_ctrl_02,cr_film_mode_enable  ,p_ipc_dflt->ipc_ctrl_00.cr_film_mode_enable);
				PE_ND0_O24_WrFL(nd_fsw_ctrl_02);
			}
			#ifdef PE_DNT_HW_O24_USE_CLC_DEFAULT
			/* nd1 clc */
			cur0_clc_fmt = PE_DNT_HW_O24_ConvDispInfoToClcFmt(cur0_inf);
			PE_DNT_HW_O24_DBG_PRINT_CLC_FMT_STATE(pInfo->clc0a_fmt,cur0_clc_fmt);
			if(pInfo->clc0a_fmt!=cur0_clc_fmt)
			{
				ret = PE_DNT_HW_O24_SetClcDefault(cur0_clc_fmt);
				PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DNT_HW_O24_SetClcDefault() error.\n", __F__, __L__);
				pInfo->clc0a_fmt=cur0_clc_fmt;
			}
			#else
			PE_ND0_O24_QWr01(clc_ctrl_07, cl_lcount_enable, 0x0);
			#endif
			/* dnr1 vfy */
			#if 1
			cur0_vfy_fmt = PE_DNT_HW_O24_ConvDispInfoToVfyFmt(cur0_inf);
			PE_DNT_HW_O24_DBG_PRINT_VFY_FMT_STATE(pInfo->vfy0a_fmt,cur0_vfy_fmt);
			if(pInfo->vfy0a_fmt!=cur0_vfy_fmt)
			{
				ret = PE_DNT_HW_O24_SetVfyDefault(cur0_vfy_fmt);
				PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DNT_HW_O24_SetVfyDefault() error.\n", __F__, __L__);
				pInfo->vfy0a_fmt=cur0_vfy_fmt;
			}
			#endif
		}
		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			/* nd12 tpd */
			if((cur1_inf->src_type==LX_PE_SRC_DTV && \
				cur1_inf->fmt_type==LX_PE_FMT_HD && \
				cur1_inf->scan_type==LX_PE_SCAN_INTERLACE) || \
				cur1_inf->src_type==LX_PE_SRC_ATV || \
				cur1_inf->src_type==LX_PE_SRC_CVBS || \
				cur1_inf->src_type==LX_PE_SRC_SCART || \
				cur1_inf->src_type==LX_PE_SRC_COMP)
			{
				cur1_force_cbcr_enb = 0x1;
				cur1_force_y_max_th = 0x5f;
			}
			else if (cur1_inf->src_type==LX_PE_SRC_HDMI && cur1_inf->hdmi_type==LX_PE_HDMI_TV)
			{
				cur1_force_cbcr_enb = 0x1;
				cur1_force_y_max_th = 0x48;
			}
			else
			{
				cur1_force_cbcr_enb = 0x0;
				cur1_force_y_max_th = 0x5f;
			}
			if ((pInfo->force_cbcr_enb_nd1!= cur1_force_cbcr_enb) || \
				(pInfo->force_y_max_th_nd1 != cur1_force_y_max_th))
			{
				PE_ND1_O24_QWr01(tpd_ctrl_08,reg_force_cb_enable,cur1_force_cbcr_enb);
				PE_ND1_O24_QWr01(tpd_ctrl_09,reg_force_cr_enable,cur1_force_cbcr_enb);
				PE_ND1_O24_QWr01(tpd_ctrl_07,reg_force_y_max_th, cur1_force_y_max_th);
				PE_INF_HW_O24_BACKUP_TRACE("[DNT]force,th:%d,%d -> %d,%d(sr,fmt,sc:%d,%d,%d)",\
					pInfo->force_cbcr_enb_nd1,pInfo->force_y_max_th_nd1,cur1_force_cbcr_enb,cur1_force_y_max_th,\
					cur1_inf->src_type,cur1_inf->fmt_type,cur1_inf->scan_type);
				pInfo->force_cbcr_enb_nd1 = cur1_force_cbcr_enb;
				pInfo->force_y_max_th_nd1 = cur1_force_y_max_th;
			}
			/* nd12 ipc */
			cur1_ipc_fmt = PE_DNT_HW_O24_ConvDispInfoToIpcFmt(cur1_inf);
			PE_DNT_HW_O24_DBG_PRINT_IPC_FMT_STATE(pInfo->ipc1a_fmt,cur1_ipc_fmt);
			PE_DNT_HW_O24_DBG_PRINT("pre src:%d, cur src:%d\n",pInfo->ipc1a_fmt,cur1_ipc_fmt);
			if(pInfo->ipc1a_fmt!=cur1_ipc_fmt)
			{
				ret = PE_DNT1_HW_O24_SetIpcDefault(cur1_ipc_fmt);
				PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DNT1_HW_O24_SetIpcDefault() error.\n", __F__, __L__);
				pInfo->ipc1a_fmt=cur1_ipc_fmt;
				data_ipc_27 = _g_pe_ipc1_hw_param_data_o24.reg_dflt.data->ipc_ctrl_27;
				data_ipc_04 = _g_pe_ipc1_hw_param_data_o24.reg_dflt.data->ipc_ctrl_04;
				PE_ND1_O24_QWr04(nd_fsw_ctrl_00,chroma_st_flt_ctrl_x0, 	data_ipc_27.chroma_st_flt_ctrl_x0,\
												chroma_st_flt_ctrl_x1, 	data_ipc_27.chroma_st_flt_ctrl_x1,\
												luma_st_flt_ctrl_x0, 	data_ipc_27.luma_st_flt_ctrl_x0,\
												luma_st_flt_ctrl_x1, 	data_ipc_27.luma_st_flt_ctrl_x1);
				PE_ND1_O24_QWr02(nd_fsw_ctrl_01, motion_x_tearing_gain, 	data_ipc_04.motion_x_tearing_gain,\
												   motion_gain,			  	data_ipc_04.motion_gain);
				PE_ND1_O24_RdFL(nd_fsw_ctrl_02);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_luma_mode		  ,p_ipc1_dflt->ipc_ctrl_00.cr_luma_mode);
				//PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_n1_cc_blend_en	  ,p_ipc1_dflt->ipc_ctrl_00.cr_n1_cc_blend_en);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_chroma_mode 	  ,p_ipc1_dflt->ipc_ctrl_00.cr_chroma_mode);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_integer_edi 	  ,p_ipc1_dflt->ipc_ctrl_00.cr_integer_edi);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_chroma_edi		  ,p_ipc1_dflt->ipc_ctrl_00.cr_chroma_edi);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_st_2d_v_flt_range2,p_ipc1_dflt->ipc_ctrl_00.cr_st_2d_v_flt_range2);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_st_2d_v_flt_range ,p_ipc1_dflt->ipc_ctrl_00.cr_st_2d_v_flt_range);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_ori_3d_blur_y	  ,p_ipc1_dflt->ipc_ctrl_00.cr_ori_3d_blur_y);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_ori_3d_blur_c	  ,p_ipc1_dflt->ipc_ctrl_00.cr_ori_3d_blur_c);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_tava_v_edge_adap  ,p_ipc1_dflt->ipc_ctrl_00.cr_tava_v_edge_adap);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_tava_debug_mode   ,p_ipc1_dflt->ipc_ctrl_00.cr_tava_debug_mode);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_tava_st_adap	  ,p_ipc1_dflt->ipc_ctrl_00.cr_tava_st_adap);
				//PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_tava_en 		  ,p_ipc1_dflt->ipc_ctrl_00.cr_tava_en);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_hmc_force_fmd	  ,p_ipc1_dflt->ipc_ctrl_00.cr_hmc_force_fmd);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_st_2d_v_flt_en	  ,p_ipc1_dflt->ipc_ctrl_00.cr_st_2d_v_flt_en);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_clc_fmd_off 	  ,p_ipc1_dflt->ipc_ctrl_00.cr_clc_fmd_off);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_chroma_tava_only  ,p_ipc1_dflt->ipc_ctrl_00.cr_chroma_tava_only);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_film_auto_gain	  ,p_ipc1_dflt->ipc_ctrl_00.cr_film_auto_gain);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_film_apply_c	  ,p_ipc1_dflt->ipc_ctrl_00.cr_film_apply_c);
				PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_film_apply_y	  ,p_ipc1_dflt->ipc_ctrl_00.cr_film_apply_y);
				//PE_ND1_O24_Wr01(nd_fsw_ctrl_02,cr_film_mode_enable  ,p_ipc1_dflt->ipc_ctrl_00.cr_film_mode_enable);
				PE_ND1_O24_WrFL(nd_fsw_ctrl_02);
			}
			#if 1
			#ifdef PE_DNT_HW_O24_USE_CLC_DEFAULT
			/* nd1 clc */
			cur1_clc_fmt = PE_DNT_HW_O24_ConvDispInfoToClcFmt(cur1_inf);
			PE_DNT_HW_O24_DBG_PRINT_CLC_FMT_STATE(pInfo->clc1a_fmt,cur1_clc_fmt);
			if(pInfo->clc1a_fmt!=cur1_clc_fmt)
			{
				ret = PE_DNT1_HW_O24_SetClcDefault(cur1_clc_fmt);
				PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DNT1_HW_O24_SetClcDefault() error.\n", __F__, __L__);
				pInfo->clc1a_fmt=cur1_clc_fmt;
			}
			#else
			PE_ND1_O24_QWr01(clc_ctrl_07, cl_lcount_enable, 0x0);
			#endif
			/* dnr1 vfy */
			#if 1
			cur1_vfy_fmt = PE_DNT_HW_O24_ConvDispInfoToVfyFmt(cur1_inf);
			PE_DNT_HW_O24_DBG_PRINT_VFY_FMT_STATE(pInfo->vfy1a_fmt,cur1_vfy_fmt);
			if(pInfo->vfy1a_fmt!=cur1_vfy_fmt)
			{
				ret = PE_DNT1_HW_O24_SetVfyDefault(cur1_vfy_fmt);
				PE_DNT_HW_O24_CHECK_CODE(ret, break, \
				"[%s,%d] PE_DNT1_HW_O24_SetVfyDefault() error.\n", __F__, __L__);
				pInfo->vfy1a_fmt=cur1_vfy_fmt;
			}
			#endif
			#endif
		}
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
static int PE_DNT_HW_O24_SetIpcDefault(PE_DNT_HW_O24_IPC_FMT cur0_ipc_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
	switch(cur0_ipc_fmt)
	{
		case PE_DNT_O24_IPC_SD:
			PE_DNT_HW_O24_IPC_REG_TABLE(ipc_l_sd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_HD:
			PE_DNT_HW_O24_IPC_REG_TABLE(ipc_l_hd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_ATV:
			PE_DNT_HW_O24_IPC_REG_TABLE(ipc_l_atv_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_DTV_SD:
			PE_DNT_HW_O24_IPC_REG_TABLE(ipc_l_dtv_sd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_DTV_HD:
			PE_DNT_HW_O24_IPC_REG_TABLE(ipc_l_dtv_hd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_VR_360:
			PE_DNT_HW_O24_IPC_REG_TABLE(ipc_l_vr_360_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_AV:
			PE_DNT_HW_O24_IPC_REG_TABLE(ipc_l_av_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_ipc_fmt)
	{
		case PE_DNT_O24_IPC_SD:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc_l_sd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_HD:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc_l_hd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_ATV:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc_l_atv_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_DTV_SD:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc_l_dtv_sd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_DTV_HD:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc_l_dtv_hd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_VR_360:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc_l_vr_360_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_AV:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc_l_av_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
static int PE_DNT1_HW_O24_SetIpcDefault(PE_DNT_HW_O24_IPC_FMT cur1_ipc_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
	switch(cur1_ipc_fmt)
	{
		case PE_DNT_O24_IPC_SD:
			PE_DNT1_HW_O24_IPC_REG_TABLE(ipc1_l_sd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_HD:
			PE_DNT1_HW_O24_IPC_REG_TABLE(ipc1_l_hd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_ATV:
			PE_DNT1_HW_O24_IPC_REG_TABLE(ipc1_l_atv_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_DTV_SD:
			PE_DNT1_HW_O24_IPC_REG_TABLE(ipc1_l_dtv_sd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_DTV_HD:
			PE_DNT1_HW_O24_IPC_REG_TABLE(ipc1_l_dtv_hd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_VR_360:
			PE_DNT1_HW_O24_IPC_REG_TABLE(ipc1_l_vr_360_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_AV:
			PE_DNT1_HW_O24_IPC_REG_TABLE(ipc1_l_av_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur1_ipc_fmt)
	{
		case PE_DNT_O24_IPC_SD:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc1_l_sd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_HD:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc1_l_hd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_ATV:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc1_l_atv_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_DTV_SD:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc1_l_dtv_sd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_DTV_HD:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc1_l_dtv_hd_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_VR_360:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc1_l_vr_360_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_IPC_AV:
			PE_SET_REG_TABLE(DNT_HW_O24,ipc1_l_av_default_o24,	   PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
#ifdef PE_DNT_HW_O24_USE_CLC_DEFAULT
static int PE_DNT_HW_O24_SetClcDefault(PE_DNT_HW_O24_CLC_FMT cur0_clc_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
	switch(cur0_clc_fmt)
	{
		case PE_DNT_O24_CLC_HD:
			PE_DNT_HW_O24_CLC_REG_TABLE(clc_l_hd_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_SD_50:
			PE_DNT_HW_O24_CLC_REG_TABLE(clc_l_sd_50_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_SD_60:
			PE_DNT_HW_O24_CLC_REG_TABLE(clc_l_sd_60_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_PC:
			PE_DNT_HW_O24_CLC_REG_TABLE(clc_l_pc_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_VR_360:
			PE_DNT_HW_O24_CLC_REG_TABLE(clc_l_vr_360_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_clc_fmt)
	{
		case PE_DNT_O24_CLC_SD_50:
			PE_SET_REG_TABLE(DNT_HW_O24,clc_l_sd_50_default_o24,	PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_SD_60:
			PE_SET_REG_TABLE(DNT_HW_O24,clc_l_sd_60_default_o24,	PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_HD:
			PE_SET_REG_TABLE(DNT_HW_O24,clc_l_hd_default_o24,   	PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_PC:
			PE_SET_REG_TABLE(DNT_HW_O24,clc_l_pc_default_o24,   	PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_VR_360:
			PE_SET_REG_TABLE(DNT_HW_O24,clc_l_vr_360_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
static int PE_DNT1_HW_O24_SetClcDefault(PE_DNT_HW_O24_CLC_FMT cur1_clc_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
	switch(cur1_clc_fmt)
	{
		case PE_DNT_O24_CLC_HD:
			PE_DNT1_HW_O24_CLC_REG_TABLE(clc1_l_hd_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_SD_50:
			PE_DNT1_HW_O24_CLC_REG_TABLE(clc1_l_sd_50_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_SD_60:
			PE_DNT1_HW_O24_CLC_REG_TABLE(clc1_l_sd_60_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_PC:
			PE_DNT1_HW_O24_CLC_REG_TABLE(clc1_l_pc_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_VR_360:
			PE_DNT1_HW_O24_CLC_REG_TABLE(clc1_l_vr_360_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_clc_fmt)
	{
		case PE_DNT_O24_CLC_SD_50:
			PE_SET_REG_TABLE(DNT_HW_O24,clc1_l_sd_50_default_o24,	PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_SD_60:
			PE_SET_REG_TABLE(DNT_HW_O24,clc1_l_sd_60_default_o24,	PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_HD:
			PE_SET_REG_TABLE(DNT_HW_O24,clc1_l_hd_default_o24,   	PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_PC:
			PE_SET_REG_TABLE(DNT_HW_O24,clc1_l_pc_default_o24,   	PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_CLC_VR_360:
			PE_SET_REG_TABLE(DNT_HW_O24,clc1_l_vr_360_default_o24,   PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}

#endif
static int PE_DNT_HW_O24_SetVfyDefault(PE_DNT_HW_O24_VFY_FMT cur0_vfy_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
	switch(cur0_vfy_fmt)
	{
		case PE_DNT_O24_VFY_SD:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_sd_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_HD_I:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_hd_i_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_HD_P:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_hd_p_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_UHD:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_ud_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_DTV_HD_I:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_hd_i_dtv_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_VR_360:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_vr_360_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_DTV_SD:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_sd_dtv_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_DTV_SD_I_576:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_sd_i_dtv_576_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_DTV_SD_I:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_sd_i_dtv_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_SD_I:
			PE_DNT_HW_O24_VFY_REG_TABLE(vflt_y_l_sd_i_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_vfy_fmt)
	{
		case PE_DNT_O24_VFY_SD:
			PE_SET_REG_TABLE(DNT_HW_O24,vflt_y_l_sd_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_HD_I:
			PE_SET_REG_TABLE(DNT_HW_O24,vflt_y_l_hd_i_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_HD_P:
			PE_SET_REG_TABLE(DNT_HW_O24,vflt_y_l_hd_p_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
static int PE_DNT1_HW_O24_SetVfyDefault(PE_DNT_HW_O24_VFY_FMT cur1_vfy_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
	switch(cur1_vfy_fmt)
	{
		case PE_DNT_O24_VFY_SD:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_sd_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_HD_I:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_hd_i_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_HD_P:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_hd_p_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_UHD:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_ud_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_DTV_HD_I:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_hd_i_dtv_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_VR_360:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_vr_360_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_DTV_SD:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_sd_dtv_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_DTV_SD_I_576:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_sd_i_dtv_576_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_DTV_SD_I:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_sd_i_dtv_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_SD_I:
			PE_DNT1_HW_O24_VFY_REG_TABLE(vflt1_y_l_sd_i_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur1_vfy_fmt)
	{
		case PE_DNT_O24_VFY_SD:
			PE_SET_REG_TABLE(DNT_HW_O24,vflt1_y_l_sd_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_HD_I:
			PE_SET_REG_TABLE(DNT_HW_O24,vflt1_y_l_hd_i_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		case PE_DNT_O24_VFY_HD_P:
			PE_SET_REG_TABLE(DNT_HW_O24,vflt1_y_l_hd_p_default_o24,    PE_O24_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}

/**
 * get ipc fmt using display info(for O24X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_DNT_HW_O24_IPC_FMT
 * @see
 * @author
 */
static PE_DNT_HW_O24_IPC_FMT PE_DNT_HW_O24_ConvDispInfoToIpcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_O24_IPC_FMT ipc_fmt = PE_DNT_O24_IPC_NUM;
	if(disp_inf->mode.is_vr)
	{
		ipc_fmt = PE_DNT_O24_IPC_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			{
				ipc_fmt = PE_DNT_O24_IPC_ATV;
			}
			break;
			case LX_PE_SRC_DTV:
			{
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					ipc_fmt = PE_DNT_O24_IPC_DTV_SD;
				}
				else
				{
					ipc_fmt = PE_DNT_O24_IPC_DTV_HD;
				}
			}
			break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
			{
				ipc_fmt = PE_DNT_O24_IPC_AV;
			}
			break;
			case LX_PE_SRC_RGBPC:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_COMP:
			default:
			{
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
					ipc_fmt = PE_DNT_O24_IPC_SD;
				else
					ipc_fmt = PE_DNT_O24_IPC_HD;
			}
			break;
		}
	}
	return ipc_fmt;
}
#ifdef PE_DNT_HW_O24_USE_CLC_DEFAULT
/**
 * get clc fmt using display info(for O24X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_DNT_HW_O24_CLC_FMT
 * @see
 * @author
 */
static PE_DNT_HW_O24_CLC_FMT PE_DNT_HW_O24_ConvDispInfoToClcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_O24_CLC_FMT clc_fmt = PE_DNT_O24_CLC_NUM;
	if(disp_inf->mode.is_vr)
	{
		clc_fmt = PE_DNT_O24_CLC_VR_360;
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
					clc_fmt = PE_DNT_O24_CLC_PC;
				}
				break;
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->src_type==LX_PE_SRC_HDMI && \
					disp_inf->hdmi_type==LX_PE_HDMI_PC)
				{
					clc_fmt = PE_DNT_O24_CLC_PC;
				}
				else if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					if(disp_inf->fmt_type==LX_PE_FMT_SD)
					{
						if(disp_inf->fr_type==LX_PE_FR_60HZ)
						{
							clc_fmt = PE_DNT_O24_CLC_SD_60;
						}
						else
						{
							clc_fmt = PE_DNT_O24_CLC_SD_50;
						}
					}
					else
					{
						clc_fmt = PE_DNT_O24_CLC_HD;
					}
				}
				else
				{
					clc_fmt = PE_DNT_O24_CLC_PC;
				}
				break;
		}
	}
	
	return clc_fmt;
}
#endif
/**
 * get vfy fmt using display info(for O24X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_DNT_HW_O24_VFY_FMT
 * @see
 * @author
 */
static PE_DNT_HW_O24_VFY_FMT PE_DNT_HW_O24_ConvDispInfoToVfyFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_O24_VFY_FMT vfy_fmt = PE_DNT_O24_VFY_NUM;
	PE_DNT_HW_O24_DBG_PRINT("VfyFmt g_pe_inf_o24_vr360_mode: %d.\n", g_pe_inf_o24_vr360_mode);
	if(disp_inf->mode.is_vr)
	{
		vfy_fmt = PE_DNT_O24_VFY_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					{
						if(disp_inf->in_v_size==576)
						{
							vfy_fmt = PE_DNT_O24_VFY_DTV_SD_I_576;
						}
						else
						{
							vfy_fmt = PE_DNT_O24_VFY_DTV_SD_I;
						}
					}
					else
					{
						vfy_fmt = PE_DNT_O24_VFY_DTV_SD;
					}
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						vfy_fmt = PE_DNT_O24_VFY_DTV_HD_I;
					else
						vfy_fmt = PE_DNT_O24_VFY_HD_P;
				}
				else
				{
					if(g_pe_inf_o24_vr360_mode)
					{
						if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
							vfy_fmt = PE_DNT_O24_VFY_HD_I;
						else
							vfy_fmt = PE_DNT_O24_VFY_HD_P;
					}
					else
					{
						vfy_fmt = PE_DNT_O24_VFY_UHD;
					}
				}
				break;
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
			case LX_PE_SRC_RGBPC:
			case LX_PE_SRC_COMP:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						vfy_fmt = PE_DNT_O24_VFY_SD_I;
					else
						vfy_fmt = PE_DNT_O24_VFY_SD;
				}
				else
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						vfy_fmt = PE_DNT_O24_VFY_HD_I;
					else
						vfy_fmt = PE_DNT_O24_VFY_HD_P;
				}
				break;
			case LX_PE_SRC_HDMI:
				if(disp_inf->fmt_type==LX_PE_FMT_UHD)
				{
					
					vfy_fmt = PE_DNT_O24_VFY_UHD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						vfy_fmt = PE_DNT_O24_VFY_SD_I;
					else
						vfy_fmt = PE_DNT_O24_VFY_SD;
				}
				else
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						vfy_fmt = PE_DNT_O24_VFY_HD_I;
					else
						vfy_fmt = PE_DNT_O24_VFY_HD_P;
				}
				break;
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						vfy_fmt = PE_DNT_O24_VFY_SD_I;
					else
						vfy_fmt = PE_DNT_O24_VFY_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						vfy_fmt = PE_DNT_O24_VFY_HD_I;
					else
						vfy_fmt = PE_DNT_O24_VFY_HD_P;
				}
				else
				{
					vfy_fmt = PE_DNT_O24_VFY_UHD;
				}
				break;
		}
	}
	return vfy_fmt;
}


/**
 * set film mode
 *
 * @param   *pstParams [in]LX_PE_DNT_FILMMODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_SetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do {
		LX_PE_DNT_FILMMODE_T *pp = pstParams;
		static LX_PE_DNT_FILMMODE_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_DNT_FILMMODE_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DNT_HW_O24_DBG_PRINT("duplicated DB : LX_PE_DNT_FILMMODE_T\n");
			ret=RET_OK;
			break;
		}
		PE_DNT_HW_O24_DBG_PRINT("set pstParams[%d] : en:%d\n", \
			pstParams->win_id, pstParams->enable);
		if(PE_KDRV_VER_O24)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_O24_QWr01(pe1_fsw_ctrl_00,reg_fmd_en_0,(pstParams->enable)? 0x1:0x0);
				#ifdef PE_DNT_HW_O24_SET_FMD_REG
				PE_ND0_O24_QWr01(ipc_ctrl_00, cr_film_mode_enable,(pstParams->enable)? 0x1:0x0);
				#else // pass the setting value to f/w
				PE_ND0_O24_QWr01(nd_fsw_ctrl_02,cr_film_mode_enable,(pstParams->enable)? 0x1:0x0);
				PE_ND1_O24_QWr01(nd_fsw_ctrl_02,cr_film_mode_enable,(pstParams->enable)? 0x1:0x0);
				#endif
				#ifdef PE_DNT_HW_O24_SET_FMD_AUTO
				PE_ND0_O24_QWr01(ipc_ctrl_35, reg_manual_en,0x0);
				#endif
			}
		}
		else
		{
			PE_DNT_HW_O24_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
/**
 * get film mode
 *
 * @param   *pstParams [in/out]LX_PE_DNT_FILMMODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_GetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O24)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_ND0_O24_QRd01(ipc_ctrl_00,cr_film_mode_enable,pstParams->enable);
			}
		}
		else
		{
			PE_DNT_HW_O24_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_DNT_HW_O24_DBG_PRINT("get pstParams[%d] : en:%d\n",pstParams->win_id,pstParams->enable);
	} while (0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
/**
 * set low delay mode : control game_en,clc_en
 *
 * @param   *pstParams [in] LX_PE_DNT_LD_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_SetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	UINT32 dyn_bypass[16] = {0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960};
	int count=0;
	int print_co=0;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DNT_HW_O24_DBG_PRINT("set[%d]:en:%d\n", \
			pstParams->win_id, pstParams->enable);
		if(PE_KDRV_VER_O24)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				if(pstParams->enable)
				{
					while(1)
					{
						PE_CEO_PE1_O24_RdFL(pe1_dce_ia_ctrl);
						PE_CEO_PE1_O24_RdFL(pe1_dce_ia_data);
						PE_CEO_PE1_O24_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
						PE_CEO_PE1_O24_Wr01(pe1_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
						PE_CEO_PE1_O24_Wr01(pe1_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
						PE_CEO_PE1_O24_WrFL(pe1_dce_ia_ctrl);
						for(count=0;count<16;count++)
						{
							PE_CEO_PE1_O24_Wr01(pe1_dce_ia_data,hif_dyc_wdata_y,GET_BITS(dyn_bypass[count],0,10));	//y data
							PE_CEO_PE1_O24_Wr01(pe1_dce_ia_data,hif_dyc_wdata_x,GET_BITS(dyn_bypass[count],0,10));//x data
							PE_CEO_PE1_O24_WrFL(pe1_dce_ia_data);
						}
						/* 20160601, read register on addr0 to avoid white flash */
						//PE_CEO_PE1_O24_WrFL(pe1_dce_ia_ctrl);
						//PE_CEO_PE1_O24_RdFL(pe1_dce_ia_data);
						PE_CEO_PE1_O24_Wr01(pe1_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
						PE_CEO_PE1_O24_Wr01(pe1_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
						PE_CEO_PE1_O24_WrFL(pe1_dce_ia_ctrl);
						if(print_co == 256)
						{
							printk("keep setting DCE");
							print_co =0;
						}
						print_co++;
					}
				}
				//PE_DNT_HW_O24_DBG_PRINT("set vr360 mode: %d\n", g_pe_inf_m17c_vr360_mode);
			}
		}
		else
		{
			PE_DNT_HW_O24_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}

/**
 * get low delay mode : game_en
 *
 * @param   *pstParams [in] LX_PE_DNT_LD_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_GetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_O24)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_ND0_O24_QRd01(ipc_ctrl_01, cr_game_mode, pstParams->enable);
			}
		}
		else
		{
			PE_DNT_HW_O24_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_DNT_HW_O24_DBG_PRINT("get[%d]:en:%d\n", \
			pstParams->win_id, pstParams->enable);
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}

/**
 * set clc mode
 *
 * @param   *pCfg [in] PE_TSK_O24_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_SetClcMode(PE_TSK_O24_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
	static UINT32 frz_history = 0;
	static UINT32 count = 0;
	static UINT32 pre_flt_en0 = 0xff;		//pre clc_en0
	static UINT32 pre_det_en0 = 0xff;		//pre clc_en0
	UINT32 cur_flt_en0 = 0;
	UINT32 cur_det_en0 = 0;
	UINT32 game_md = 0;
	__attribute__((unused)) PE_INF_O24_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_O24)
		{
			PE_CLC_HW_PARAM_REG_O24_T *p_clc_dflt = _g_pe_clc0_hw_param_data_o24.reg_dflt.data;
			/* update frz_history */
			frz_history = (frz_history<<1)|(ctrl0_info->is_src_frz? 1:0);
			/* check clc off case */
			if ((frz_history&0x7) && !ctrl0_info->mute_on && \
				disp0_info->src_type==LX_PE_SRC_DTV && \
				(disp0_info->dtv_type==LX_PE_DTV_FILEPLAY || \
				disp0_info->dtv_type==LX_PE_DTV_HDDPLAY) && \
				disp0_info->fmt_type==LX_PE_FMT_HD && \
				disp0_info->scan_type==LX_PE_SCAN_INTERLACE)
			{
				cur_flt_en0 = PE_DNT_HW_O24_CLC_OFF;
				cur_det_en0 = PE_DNT_HW_O24_CLC_OFF;
			}
			else
			{
				PE_ND0_O24_QRd01(ipc_ctrl_01, cr_game_mode, game_md);
				/* clc off when game mode on */
				if (game_md)
				{
					cur_flt_en0 = PE_DNT_HW_O24_CLC_OFF;
					cur_det_en0 = PE_DNT_HW_O24_CLC_OFF;
				}
				else
				{
					cur_flt_en0 = p_clc_dflt->clc_ctrl_00.cl_filter_enable;
					cur_det_en0 = p_clc_dflt->clc_ctrl_00.clc_detection_enable;
				}
			}
			/* compare pre vs. cur */
			if (pre_flt_en0 != cur_flt_en0 || \
				pre_det_en0 != cur_det_en0)
			{
				PE_DNT_HW_O24_DBG_PRINT("[inf] fz:%d(0x%08x),mt:%d,sr,dt,fm,sc:%d,%d,%d,%d \n",\
					ctrl0_info->is_src_frz, frz_history, ctrl0_info->mute_on, disp0_info->src_type, \
					disp0_info->dtv_type, disp0_info->fmt_type, disp0_info->scan_type );
				PE_DNT_HW_O24_DBG_PRINT("[set] dflt:%d, flt_en0 : %d -> %d\n",\
					p_clc_dflt->clc_ctrl_00.cl_filter_enable, pre_flt_en0, cur_flt_en0);
				PE_DNT_HW_O24_DBG_PRINT("[set] dflt:%d, det_en0 : %d -> %d\n",\
					p_clc_dflt->clc_ctrl_00.clc_detection_enable, pre_det_en0, cur_det_en0);
				PE_CC_PE1_O24_QWr02(pe1_fsw_ctrl_00,cl_filter_en_stat,cur_flt_en0,clc_detection_en_stat,cur_det_en0);
				pre_flt_en0 = cur_flt_en0;
				pre_det_en0 = cur_det_en0;
			}
			if(_g_dnt_hw_o24_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_DNT_HW_O24_DBG_PRINT("[state] fz:%d(0x%08x),dflt:%d,flt_en0:%d, dflt:%d,det_en0:%d\n",\
						ctrl0_info->is_src_frz, frz_history, \
						p_clc_dflt->clc_ctrl_00.cl_filter_enable, cur_flt_en0, \
						p_clc_dflt->clc_ctrl_00.clc_detection_enable, cur_det_en0);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_DNT_HW_O24_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
/**
 * set vfy mode
 *
 * @param   *pCfg [in] PE_TSK_O24_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_SetVfyMode(PE_TSK_O24_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	static UINT32 count = 0;
	UINT32 cur_flt_en0 = 0;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_VFY_HW_PARAM_REG_O24_T *p_vfy_dflt = _g_pe_vfy0_hw_param_data_o24.reg_dflt.data;
	#ifdef PE_DNR_HW_O24_PAT_DETECT
	UINT32 is_pattern;
	LX_PE_INF_DISPLAY_T cur0_inf;	
	UINT32 vft_12;
	#endif
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_O24)
		{
			/* check vfy off case */
			if (disp0_info->sub_mode == LX_DE_SUB_MODE_PBP || disp0_info->sub_mode == LX_DE_SUB_MODE_DUALMON || \
				disp0_info->src_type== LX_PE_SRC_ATV) // pbp mode or ATV 
			{
				cur_flt_en0 = PE_DNT_HW_O24_VFY_OFF;
			}
			else
			{
				cur_flt_en0 = p_vfy_dflt->vfilter_ctrl_01.reg_glb_vflt_en;
			}
			/* compare pre vs. cur */
			if (_g_pre_vfy_flt_en0 != cur_flt_en0)
			{
				PE_DNT_HW_O24_DBG_PRINT("[set] vfy_en0 : %d -> %d\n",\
					_g_pre_vfy_flt_en0, cur_flt_en0);
				//PE_DNT_HW_O24_VFY_WR01(vfilter_ctrl_01,reg_glb_vflt_en,cur_flt_en0);
				PE_SR_2K_SHP0_O24_QWr01(shp_fsw_ctrl_00, vfy_glb_en, GET_BITS(cur_flt_en0,0,1));
				//PE_DNT_HW_O24_VFY_SET_USER(vfilter_ctrl_01,reg_glb_vflt_en,cur_flt_en0);
				PE_DNT_HW_O24_VFY_WR01(vfilter_ctrl_01,reg_glb_vflt_en,GET_BITS(cur_flt_en0,0,1));
				_g_pre_vfy_flt_en0 = cur_flt_en0;
			}
			if(_g_dnt_hw_o24_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_DNT_HW_O24_DBG_PRINT("[state] vfy_en0 : %d\n",cur_flt_en0);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_DNT_HW_O24_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}
/**
 * set etc mode - tava, hmc, n1 blending
 *
 * @param   *pCfg [in] PE_TSK_O24_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_SetIpcMode(PE_TSK_O24_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	UINT32 game_md = 0;
	static UINT32 count = 0;
	static UINT32 pre_n1_blend_en = 0xff;
	static UINT32 pre_tava_en = 0xff;
	static UINT32 pre_hmc_flt_en = 0xff;
	static UINT32 pre_n1_blend_en_nd1 = 0xff;
	static UINT32 pre_tava_en_nd1 = 0xff;
	static UINT32 pre_hmc_flt_en_nd1 = 0xff;
	UINT32 cur_n1_blend_en = 0x0;
	UINT32 cur_tava_en = 0x0;
	UINT32 cur_hmc_flt_en = 0x0;
	PE_IPC_HW_PARAM_REG_O24_T *p_ipc0_dflt = _g_pe_ipc0_hw_param_data_o24.reg_dflt.data;
	PE_IPC_HW_PARAM_REG_O24_T *p_ipc1_dflt = _g_pe_ipc1_hw_param_data_o24.reg_dflt.data;

	/* TAVA off when game mode on */
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_O24)
		{
			/* nd 0 */
			PE_ND0_O24_QRd01(ipc_ctrl_01, cr_game_mode, game_md);
			if (game_md)
			{
				cur_n1_blend_en = 0x0;
				cur_tava_en 	= 0x0;
				cur_hmc_flt_en 	= 0x0;
			}
			else
			{
				cur_n1_blend_en = p_ipc0_dflt->ipc_ctrl_00.cr_n1_cc_blend_en;
				cur_tava_en 	= p_ipc0_dflt->ipc_ctrl_00.cr_tava_en;
				cur_hmc_flt_en 	= p_ipc0_dflt->ipc_ctrl_01.cr_hmc_flt_enable;
			}
			//PE_DNT_HW_O24_DBG_PRINT("[info] game: %d\n",game_md);
			if (cur_n1_blend_en != pre_n1_blend_en || cur_tava_en != pre_tava_en ||\
				cur_hmc_flt_en != pre_hmc_flt_en)
			{
				PE_DNT_HW_O24_DBG_PRINT("[set] win 0: dflt:%d, cr_n1_cc_blend_en : %d -> %d\n",\
					p_ipc0_dflt->ipc_ctrl_00.cr_n1_cc_blend_en, pre_n1_blend_en, cur_n1_blend_en);
				PE_DNT_HW_O24_DBG_PRINT("[set] win 0: dflt:%d, cr_tava_en : %d -> %d\n",\
					p_ipc0_dflt->ipc_ctrl_00.cr_tava_en, pre_tava_en, cur_tava_en);
				PE_DNT_HW_O24_DBG_PRINT("[set] win 0: dflt:%d, cr_n1_cc_blend_en : %d -> %d\n",\
					p_ipc0_dflt->ipc_ctrl_01.cr_hmc_flt_enable, pre_hmc_flt_en, cur_hmc_flt_en);

				PE_ND0_O24_QWr02(nd_fsw_ctrl_02,	cr_n1_cc_blend_en,	cur_n1_blend_en, \
														cr_tava_en,			cur_tava_en);
				PE_DNT_HW_O24_IPC_WR01(ipc_ctrl_01,	cr_hmc_flt_enable,	cur_hmc_flt_en);
				pre_n1_blend_en = cur_n1_blend_en;
				pre_tava_en		= cur_tava_en;
				pre_hmc_flt_en	= cur_hmc_flt_en;
			}
			if(_g_dnt_hw_o24_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_DNT_HW_O24_DBG_PRINT("[state]win 0: cr_n1_cc_blend_en : %d, cr_tava_en : %d, cr_n1_cc_blend_en : %d\n",\
						cur_n1_blend_en,cur_tava_en, cur_hmc_flt_en);
					//count=0;
				}
				//count++; // added print after nd1 setting so count increased below
			}
			/* nd 1 */
			PE_ND1_O24_QRd01(ipc_ctrl_01, cr_game_mode, game_md);
			if (game_md)
			{
				cur_n1_blend_en = 0x0;
				cur_tava_en 	= 0x0;
				cur_hmc_flt_en 	= 0x0;
			}
			else
			{
				cur_n1_blend_en = p_ipc1_dflt->ipc_ctrl_00.cr_n1_cc_blend_en;
				cur_tava_en 	= p_ipc1_dflt->ipc_ctrl_00.cr_tava_en;
				cur_hmc_flt_en 	= p_ipc1_dflt->ipc_ctrl_01.cr_hmc_flt_enable;
			}
			//PE_DNT_HW_O24_DBG_PRINT("[info] game: %d\n",game_md);
			if (cur_n1_blend_en != pre_n1_blend_en_nd1 || cur_tava_en != pre_tava_en_nd1 ||\
				cur_hmc_flt_en != pre_hmc_flt_en_nd1)
			{
				PE_DNT_HW_O24_DBG_PRINT("[set] win 1: dflt:%d, cr_n1_cc_blend_en : %d -> %d\n",\
					p_ipc1_dflt->ipc_ctrl_00.cr_n1_cc_blend_en, pre_n1_blend_en_nd1, cur_n1_blend_en);
				PE_DNT_HW_O24_DBG_PRINT("[set] win 1: dflt:%d, cr_tava_en : %d -> %d\n",\
					p_ipc1_dflt->ipc_ctrl_00.cr_tava_en, pre_tava_en_nd1, cur_tava_en);
				PE_DNT_HW_O24_DBG_PRINT("[set] win 1: dflt:%d, cr_n1_cc_blend_en : %d -> %d\n",\
					p_ipc1_dflt->ipc_ctrl_01.cr_hmc_flt_enable, pre_hmc_flt_en_nd1, cur_hmc_flt_en);

				PE_ND1_O24_QWr02(nd_fsw_ctrl_02,	cr_n1_cc_blend_en,	cur_n1_blend_en, \
														cr_tava_en,			cur_tava_en);
				PE_DNT1_HW_O24_IPC_WR01(ipc_ctrl_01,	cr_hmc_flt_enable,	cur_hmc_flt_en);
				pre_n1_blend_en_nd1 = cur_n1_blend_en;
				pre_tava_en_nd1		= cur_tava_en;
				pre_hmc_flt_en_nd1	= cur_hmc_flt_en;
			}
			if(_g_dnt_hw_o24_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_DNT_HW_O24_DBG_PRINT("[state]cr_n1_cc_blend_en : %d, cr_tava_en : %d, cr_n1_cc_blend_en : %d\n",\
						cur_n1_blend_en,cur_tava_en, cur_hmc_flt_en);
					count=0;
				}
				count++;
			}
		}
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}


/**
 * get current dnt settings
 *
 * @param   *pstParams [in/out] PE_DNT_HW_O24_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_O24_GetCurDntSettings(PE_DNT_HW_O24_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	PE_DNT_HW_O24_SETTINGS_T *pInfo = &_g_pe_dnt_hw_o24_info;
	do{

		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O24)
		{
			memcpy(pstParams,pInfo,sizeof(PE_DNT_HW_O24_SETTINGS_T));
			PE_DNT_HW_O24_DBG_PRINT("get force en,y_th:%d,%d\n", \
				pInfo->force_cbcr_enb_nd0,	pInfo->force_y_max_th_nd0);
		}
		else
		{
			PE_DNT_HW_O24_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * read default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_DNT_HW_O24_RdDefault(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#ifndef PE_HW_O24_PROTECT_OVERLAP_SETTINGS
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 param_size=0, table_size=0, is_valid=0;
	UINT32 rd_cnt=0;
	PE_REG_PARAM_T param;
	PE_DNT_HW_O24_SETTINGS_T *pInfo=&_g_pe_dnt_hw_o24_info;

#define PE_DNT_O24_NO_PRINT			0
#define PE_DNT_O24_RD_N_HEX_PRINT	1
#define PE_DNT_O24_HEX_PRINT_ONLY	2
#define PE_DNT_O24_PRINT_START		"START_OF_PRINT"
#define PE_DNT_O24_PRINT_END		"END_OF_PRINT"
#define PE_DNT_O24_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_DNT_O24_PRINT_RESRV		"RESERVED"
#define PE_DNT_O24_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, "   [0x%02x] %s\n", (_item), #_item);_action;break
#define PE_DNT_O24_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break
#define PE_DNT_O24_DFLT_SPRINT(_action, _buf, fmt, args...)		\
	default:snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		if (PE_KDRV_VER_O24)
		{
			UINT32 *p_ipc_dflt = _g_pe_ipc0_hw_param_data_o24.reg_dflt.addr;
			UINT32 *p_ipc_user = _g_pe_ipc0_hw_param_data_o24.reg_user.addr;
			UINT32 *p_ipc_mask = _g_pe_ipc0_hw_param_data_o24.reg_mask.addr;
			UINT32 *p_ipc_data = _g_pe_ipc0_hw_param_data_o24.reg_data.addr;
			UINT32 *p_clc_dflt = _g_pe_clc0_hw_param_data_o24.reg_dflt.addr;
			UINT32 *p_clc_user = _g_pe_clc0_hw_param_data_o24.reg_user.addr;
			UINT32 *p_clc_mask = _g_pe_clc0_hw_param_data_o24.reg_mask.addr;
			UINT32 *p_clc_data = _g_pe_clc0_hw_param_data_o24.reg_data.addr;
			UINT32 *p_vfy_dflt = _g_pe_vfy0_hw_param_data_o24.reg_dflt.addr;
			UINT32 *p_vfy_user = _g_pe_vfy0_hw_param_data_o24.reg_user.addr;
			UINT32 *p_vfy_mask = _g_pe_vfy0_hw_param_data_o24.reg_mask.addr;
			UINT32 *p_vfy_data = _g_pe_vfy0_hw_param_data_o24.reg_data.addr;

			UINT32 *p_ipc1_dflt = _g_pe_ipc1_hw_param_data_o24.reg_dflt.addr;
			UINT32 *p_ipc1_user = _g_pe_ipc1_hw_param_data_o24.reg_user.addr;
			UINT32 *p_ipc1_mask = _g_pe_ipc1_hw_param_data_o24.reg_mask.addr;
			UINT32 *p_ipc1_data = _g_pe_ipc1_hw_param_data_o24.reg_data.addr;
			UINT32 *p_clc1_dflt = _g_pe_clc1_hw_param_data_o24.reg_dflt.addr;
			UINT32 *p_clc1_user = _g_pe_clc1_hw_param_data_o24.reg_user.addr;
			UINT32 *p_clc1_mask = _g_pe_clc1_hw_param_data_o24.reg_mask.addr;
			UINT32 *p_clc1_data = _g_pe_clc1_hw_param_data_o24.reg_data.addr;
			UINT32 *p_vfy1_dflt = _g_pe_vfy1_hw_param_data_o24.reg_dflt.addr;
			UINT32 *p_vfy1_user = _g_pe_vfy1_hw_param_data_o24.reg_user.addr;
			UINT32 *p_vfy1_mask = _g_pe_vfy1_hw_param_data_o24.reg_mask.addr;
			UINT32 *p_vfy1_data = _g_pe_vfy1_hw_param_data_o24.reg_data.addr;
			
			CHECK_KNULL(p_ipc_dflt);
			CHECK_KNULL(p_ipc_user);
			CHECK_KNULL(p_ipc_mask);
			CHECK_KNULL(p_ipc_data);
			CHECK_KNULL(p_clc_dflt);
			CHECK_KNULL(p_clc_user);
			CHECK_KNULL(p_clc_mask);
			CHECK_KNULL(p_clc_data);
			CHECK_KNULL(p_vfy_dflt);
			CHECK_KNULL(p_vfy_user);
			CHECK_KNULL(p_vfy_mask);
			CHECK_KNULL(p_vfy_data);
			CHECK_KNULL(p_ipc1_dflt);
			CHECK_KNULL(p_ipc1_user);
			CHECK_KNULL(p_ipc1_mask);
			CHECK_KNULL(p_ipc1_data);
			CHECK_KNULL(p_clc1_dflt);
			CHECK_KNULL(p_clc1_user);
			CHECK_KNULL(p_clc1_mask);
			CHECK_KNULL(p_clc1_data);
			CHECK_KNULL(p_vfy1_dflt);
			CHECK_KNULL(p_vfy1_user);
			CHECK_KNULL(p_vfy1_mask);
			CHECK_KNULL(p_vfy1_data);
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]>=PE_DNT_HW_O24_RD_MENU_MAX)
			{
				snprintf(buffer, PE_TRACE_STR_SIZE, "%s", PE_DNT_O24_PRINT_EXIT);
				rd_cnt=0;
			}
			else if (pstParams->data[0]==PE_DNT_HW_O24_RD_MENU_DISP)
			{
				switch (rd_cnt)
				{
					PE_DNT_O24_CASE_SPRINT( 0, rd_cnt++, buffer, "%s", PE_DNT_O24_PRINT_START);
					PE_DNT_O24_CASE_SPRINT( 1, rd_cnt++, buffer, "   ** current default **\n");
					PE_DNT_O24_CASE_SPRINT( 2, rd_cnt++, buffer, \
						"   ipc0a_fmt : %s\n", PE_DNT_HW_O24_IPC_FMT_TO_STR(pInfo->ipc0a_fmt));
					PE_DNT_O24_CASE_SPRINT( 3, rd_cnt++, buffer, \
						"   clc0a_fmt : %s\n", PE_DNT_HW_O24_CLC_FMT_TO_STR(pInfo->clc0a_fmt));
					PE_DNT_O24_CASE_SPRINT( 4, rd_cnt++, buffer, \
						"   vfy0a_fmt : %s\n", PE_DNT_HW_O24_VFY_FMT_TO_STR(pInfo->vfy0a_fmt));
					PE_DNT_O24_CASE_SPRINT( 5, rd_cnt++, buffer, PE_DNT_O24_PRINT_RESRV);
					PE_DNT_O24_CASE_SPRINT( 6, rd_cnt++, buffer, PE_DNT_O24_PRINT_RESRV);
					PE_DNT_O24_CASE_SPRINT( 7, rd_cnt++, buffer, PE_DNT_O24_PRINT_RESRV);
					PE_DNT_O24_CASE_SPRINT( 8, rd_cnt++, buffer, PE_DNT_O24_PRINT_RESRV);
					PE_DNT_O24_CASE_SPRINT( 9, rd_cnt++, buffer, "   *********************\n");
					PE_DNT_O24_CASE_PRMENU(10, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC1_DISP);
					PE_DNT_O24_CASE_PRMENU(11, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC1_DFLT);
					PE_DNT_O24_CASE_PRMENU(12, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC1_USER);
					PE_DNT_O24_CASE_PRMENU(13, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC1_MASK);
					PE_DNT_O24_CASE_PRMENU(14, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC1_DATA);
					PE_DNT_O24_CASE_PRMENU(15, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC2_DISP);
					PE_DNT_O24_CASE_PRMENU(16, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC2_DFLT);
					PE_DNT_O24_CASE_PRMENU(17, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC2_USER);
					PE_DNT_O24_CASE_PRMENU(18, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC2_MASK);
					PE_DNT_O24_CASE_PRMENU(19, rd_cnt++, buffer, PE_DNT_HW_O24_RD_IPC2_DATA);
					PE_DNT_O24_CASE_PRMENU(20, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC1_DISP);
					PE_DNT_O24_CASE_PRMENU(21, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC1_DFLT);
					PE_DNT_O24_CASE_PRMENU(22, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC1_USER);
					PE_DNT_O24_CASE_PRMENU(23, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC1_MASK);
					PE_DNT_O24_CASE_PRMENU(24, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC1_DATA);
					PE_DNT_O24_CASE_PRMENU(25, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC2_DISP);
					PE_DNT_O24_CASE_PRMENU(26, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC2_DFLT);
					PE_DNT_O24_CASE_PRMENU(27, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC2_USER);
					PE_DNT_O24_CASE_PRMENU(28, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC2_MASK);
					PE_DNT_O24_CASE_PRMENU(29, rd_cnt++, buffer, PE_DNT_HW_O24_RD_CLC2_DATA);
					PE_DNT_O24_CASE_PRMENU(30, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY1_DISP);
					PE_DNT_O24_CASE_PRMENU(31, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY1_DFLT);
					PE_DNT_O24_CASE_PRMENU(32, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY1_USER);
					PE_DNT_O24_CASE_PRMENU(33, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY1_MASK);
					PE_DNT_O24_CASE_PRMENU(34, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY1_DATA);
					PE_DNT_O24_CASE_PRMENU(35, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY2_DISP);
					PE_DNT_O24_CASE_PRMENU(36, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY2_DFLT);
					PE_DNT_O24_CASE_PRMENU(37, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY2_USER);
					PE_DNT_O24_CASE_PRMENU(38, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY2_MASK);
					PE_DNT_O24_CASE_PRMENU(39, rd_cnt++, buffer, PE_DNT_HW_O24_RD_VFY2_DATA);
					PE_DNT_O24_DFLT_SPRINT(rd_cnt=0, buffer, "%s", PE_DNT_O24_PRINT_END);
				}
			}
			else
			{
				is_valid = PE_DNT_O24_NO_PRINT;
				switch (pstParams->data[0])
				{
					case PE_DNT_HW_O24_RD_IPC1_DISP:
						table_size = sizeof(ipc_l_hd_default_o24);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = ipc_l_hd_default_o24[rd_cnt].addr;
							is_valid = PE_DNT_O24_RD_N_HEX_PRINT;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC1_DFLT:
						table_size = sizeof(PE_IPC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ipc_l_hd_default_o24[rd_cnt].addr;
							param.data = p_ipc_dflt[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC1_USER:
						table_size = sizeof(PE_IPC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ipc_l_hd_default_o24[rd_cnt].addr;
							param.data = p_ipc_user[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC1_MASK:
						table_size = sizeof(PE_IPC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ipc_l_hd_default_o24[rd_cnt].addr;
							param.data = p_ipc_mask[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC1_DATA:
						table_size = sizeof(PE_IPC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ipc_l_hd_default_o24[rd_cnt].addr;
							param.data = p_ipc_data[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC2_DISP:
						table_size = sizeof(ipc1_l_hd_default_o24);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = ipc1_l_hd_default_o24[rd_cnt].addr;
							is_valid = PE_DNT_O24_RD_N_HEX_PRINT;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC2_DFLT:
						table_size = sizeof(PE_IPC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ipc1_l_hd_default_o24[rd_cnt].addr;
							param.data = p_ipc1_dflt[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC2_USER:
						table_size = sizeof(PE_IPC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ipc1_l_hd_default_o24[rd_cnt].addr;
							param.data = p_ipc1_user[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC2_MASK:
						table_size = sizeof(PE_IPC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ipc1_l_hd_default_o24[rd_cnt].addr;
							param.data = p_ipc1_mask[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_IPC2_DATA:
						table_size = sizeof(PE_IPC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ipc1_l_hd_default_o24[rd_cnt].addr;
							param.data = p_ipc1_data[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC1_DISP:
						table_size = sizeof(clc_l_init_o24);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = clc_l_init_o24[rd_cnt].addr;
							is_valid = PE_DNT_O24_RD_N_HEX_PRINT;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC1_DFLT:
						table_size = sizeof(PE_CLC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = clc_l_init_o24[rd_cnt].addr;
							param.data = p_clc_dflt[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC1_USER:
						table_size = sizeof(PE_CLC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = clc_l_init_o24[rd_cnt].addr;
							param.data = p_clc_user[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC1_MASK:
						table_size = sizeof(PE_CLC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = clc_l_init_o24[rd_cnt].addr;
							param.data = p_clc_mask[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC1_DATA:
						table_size = sizeof(PE_CLC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = clc_l_init_o24[rd_cnt].addr;
							param.data = p_clc_data[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC2_DISP:
						table_size = sizeof(clc1_l_init_o24);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = clc1_l_init_o24[rd_cnt].addr;
							is_valid = PE_DNT_O24_RD_N_HEX_PRINT;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC2_DFLT:
						table_size = sizeof(PE_CLC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = clc1_l_init_o24[rd_cnt].addr;
							param.data = p_clc1_dflt[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC2_USER:
						table_size = sizeof(PE_CLC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = clc1_l_init_o24[rd_cnt].addr;
							param.data = p_clc1_user[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC2_MASK:
						table_size = sizeof(PE_CLC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = clc1_l_init_o24[rd_cnt].addr;
							param.data = p_clc1_mask[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_CLC2_DATA:
						table_size = sizeof(PE_CLC_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = clc1_l_init_o24[rd_cnt].addr;
							param.data = p_clc1_data[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY1_DISP:
						table_size = sizeof(vflt_y_l_hd_p_default_o24);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = vflt_y_l_hd_p_default_o24[rd_cnt].addr;
							is_valid = PE_DNT_O24_RD_N_HEX_PRINT;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY1_DFLT:
						table_size = sizeof(PE_VFY_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vflt_y_l_hd_p_default_o24[rd_cnt].addr;
							param.data = p_vfy_dflt[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY1_USER:
						table_size = sizeof(PE_VFY_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vflt_y_l_hd_p_default_o24[rd_cnt].addr;
							param.data = p_vfy_user[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY1_MASK:
						table_size = sizeof(PE_VFY_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vflt_y_l_hd_p_default_o24[rd_cnt].addr;
							param.data = p_vfy_mask[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY1_DATA:
						table_size = sizeof(PE_VFY_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vflt_y_l_hd_p_default_o24[rd_cnt].addr;
							param.data = p_vfy_data[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY2_DISP:
						table_size = sizeof(vflt1_y_l_hd_p_default_o24);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = vflt1_y_l_hd_p_default_o24[rd_cnt].addr;
							is_valid = PE_DNT_O24_RD_N_HEX_PRINT;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY2_DFLT:
						table_size = sizeof(PE_VFY_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vflt1_y_l_hd_p_default_o24[rd_cnt].addr;
							param.data = p_vfy_dflt[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY2_USER:
						table_size = sizeof(PE_VFY_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vflt1_y_l_hd_p_default_o24[rd_cnt].addr;
							param.data = p_vfy_user[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY2_MASK:
						table_size = sizeof(PE_VFY_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vflt1_y_l_hd_p_default_o24[rd_cnt].addr;
							param.data = p_vfy_mask[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					case PE_DNT_HW_O24_RD_VFY2_DATA:
						table_size = sizeof(PE_VFY_HW_PARAM_REG_O24_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = vflt1_y_l_hd_p_default_o24[rd_cnt].addr;
							param.data = p_vfy_data[rd_cnt];
							is_valid = PE_DNT_O24_HEX_PRINT_ONLY;
						}
						break;
					default:
						break;
				}
				if (is_valid == PE_DNT_O24_RD_N_HEX_PRINT)
				{
					//param.data = PE_REG_O24_RD(param.addr);
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else if (is_valid == PE_DNT_O24_HEX_PRINT_ONLY)
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "%s", PE_DNT_O24_PRINT_END);
					rd_cnt = 0;
				}
			}
			memcpy(pstParams->data, buffer, sizeof(char)*PE_TRACE_STR_SIZE);
		}
	}while (0);
	#endif
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;

}

