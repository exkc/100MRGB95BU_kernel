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

/** @file pe_shp_hw_m23.c
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

#include "pe_hw_m23.h"
#include "pe_reg_m23.h"
#include "pe_fwi_m23.h"
#include "pe_cmn_hw_m23.h"
#include "pe_hst_hw_m23.h"
#include "pe_shp_hw_m23.h"
#include "pe_res_hw_param_m23.h"
#include "pe_cti_dnr_hw_param_m23.h"
#include "pe_pblur_dnr_hw_param_m23.h"
#ifdef INCLUDE_KDRV_AFE
#include "cvd_module.h"
#endif
#include "pe_shp_scl256_def.h"

#include "pe_shp_l_sd_default_m23.h"
#include "pe_shp_l_hd_default_m23.h"
#include "pe_shp_l_ud_default_m23.h"
#include "pe_shp_l_cp_default_m23.h"
#include "pe_sre_2k_res_sd_default_m23.h"
#include "pe_sre_2k_res_hd_default_m23.h"
#include "pe_sre_2k_res_ud_default_m23.h"
#include "pe_sre_2k_res_720p_default_m23.h"
#include "pe_sre_chr_res_sd_default_m23.h"
#include "pe_sre_chr_res_hd_default_m23.h"
#include "pe_sre_chr_res_ud_default_m23.h"
#include "pe_shp_l_sd_default_m23_8k.h"
#include "pe_shp_l_hd_default_m23_8k.h"
#include "pe_shp_l_ud_default_m23_8k.h"

#include "pe_cti_y_l_hd_default_m23.h"
#include "pe_cti_y_l_sd_default_m23.h"
#include "pe_cti_y_l_vr_360_default_m23.h"
#include "pe_cti_y_l_atv_default_m23.h"
#include "pe_cti_y_l_ud_default_m23.h"

#include "pe_sqm_shp_2k_cmn_init_m23.h"
#include "pe_sqm_shp_2k_dtl_init_m23.h"
#include "pe_sqm_shp_vsd_cmn_init_m23.h"
#include "pe_sqm_shp_vsd_dtl_init_m23.h"


#include "pe_ord_default_m23.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_HW_M23_FHD_H_MAX					1920
#define PE_SHP_HW_M23_FHD_V_MAX					1080
#define PE_SHP_HW_M23_SCL_IN_H_MIN				160
#define PE_SHP_HW_M23_SCL_IN_V_MIN				120
#define PE_SHP_HW_M23_IDX_Y_DFLT				15
#define PE_SHP_HW_M23_IDX_C_DFLT				39

#define PE_SHP_HW_M23_SCL_SIZE_MIN				(10)
#define PE_SHP_HW_M23_SCL_SIZE_1K				(1024)
#define PE_SHP_HW_M23_SCL_SIZE_2K				(2048)
#define PE_SHP_HW_M23_SCL_VSC_MD_V12TAP			(12)
#define PE_SHP_HW_M23_SCL_VSC_MD_V06TAP			(6)
#define PE_SHP_HW_M23_SCL_VSC_MD_V02TAP			(2)
#define PE_SHP_HW_M23_SCL_VSC_MD_V08TAP			(8)
#define PE_SHP_HW_M23_SCL_VSC_MD_V04TAP			(4)
#define PE_SHP_HW_M23_SCL_ADAPTIVE_ON			(0x1)
#define PE_SHP_HW_M23_SCL_ADAPTIVE_OFF			(0x0)
#define PE_SHP_HW_M23_SCL_BILINEAR				(0x1)
#define PE_SHP_HW_M23_SCL_POLYPHASE				(0x0)
#define PE_SHP_HW_M23_SCL_C_FMT_444				(0x6)
#define PE_SHP_HW_M23_SCL_C_FMT_422				(0x5)
#define PE_SHP_HW_M23_SCL_C_FMT_420				(0x4)
#define PE_SHP_HW_M23_SCL_PXL_RP_OFF			(0x0)
#define PE_SHP_HW_M23_SCL_PXL_RP_RED			(0x1)
#define PE_SHP_HW_M23_SCL_PXL_RP_GRN			(0x2)
#define PE_SHP_HW_M23_SCL_PXL_RP_BLU			(0x3)
#define PE_SHP_HW_M23_SCL_CO_REG_INC_MAX		(128)
#define PE_SHP_HW_M23_SCL_G0Y					0
#define PE_SHP_HW_M23_SCL_G1Y					1
#define PE_SHP_HW_M23_SCL_G0C					2
#define PE_SHP_HW_M23_SCL_G1C					3
#define PE_SHP_HW_M23_SCL_P0Y					4
#define PE_SHP_HW_M23_SCL_DWN_LVL_NORM			(0)
#define PE_SHP_HW_M23_SCL_DWN_LVL_HALF			(1)
#define PE_SHP_HW_M23_SCL_DWN_LVL_QUAD			(2)
#define PE_SHP_HW_M23_SCL_DWN_LVL_OCTA			(3)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_HW_M23_CHECK_CODE(_checker, _action, fmt, args...)	\
	{if(_checker){PE_PRINT_ERROR(fmt, ##args);_action;}}

#define PE_SHP_HW_M23_DBG_CHECK_CODE(_cnt, _checker, _action, fmt, args...)	\
	{\
		if(_checker){\
			if(_g_shp_hw_m23_trace&&_cnt>PE_PRINT_COUNT_NUM)\
			{\
				printk(fmt, ##args);\
			}\
			_action;\
		}\
	}

/* for M23*/
#define PE_SHP_HW_M23_DBG_PRINT_RES_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M23_RES_FMT_TO_STR(_pre), \
			PE_SHP_HW_M23_RES_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_SHP("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_M23_DBG_PRINT_SRS_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M23_SRS_FMT_TO_STR(_pre), \
			PE_SHP_HW_M23_SRS_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_SHP("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_M23_DBG_PRINT_2KS_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M23_2KS_FMT_TO_STR(_pre), \
			PE_SHP_HW_M23_2KS_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_SHP("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_M23_DBG_PRINT_CHR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M23_CHR_FMT_TO_STR(_pre), \
			PE_SHP_HW_M23_CHR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_SHP("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_SHP_HW_M23_DBG_PRINT_SRE_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M23_SRE_FMT_TO_STR(_pre), \
			PE_SHP_HW_M23_SRE_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_SHP("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_M23_DBG_PRINT_SRL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M23_SRL_FMT_TO_STR(_pre), \
			PE_SHP_HW_M23_SRL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_SHP("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_M23_DBG_PRINT_PBL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M23_PBL_FMT_TO_STR(_pre), \
			PE_SHP_HW_M23_PBL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_SHP("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_M23_DBG_PRINT_CTI_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_M23_CTI_FMT_TO_STR(_pre), \
			PE_SHP_HW_M23_CTI_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_SHP("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}


#define PE_SHP_HW_M23_SET_SHDW_GSC_Y_TO_SHP(_dst, _src)	\
	(*((UINT32 *)&(gPE_SHP_M23.shdw.data->_dst))) = (*((UINT32 *)&(gPE_GSC_Y_M23.shdw.data->_src)))
#define PE_SHP_HW_M23_SET_SHDW_GSC_C_TO_SHP(_dst, _src)	\
	(*((UINT32 *)&(gPE_SHP_M23.shdw.data->_dst))) = (*((UINT32 *)&(gPE_GSC_C_M23.shdw.data->_src)))

#define PE_SHP_HW_M23_RES_SET_USER(_r, _f, _d)	\
	{	_g_pe_res_hw_param_data_m23.reg_user.data->_r._f = (_d);\
		_g_pe_res_hw_param_data_m23.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_M23_RES_WR01(_r, _f1, _d1)	\
	{	PE_SHP_M23_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M23_RES_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M23_RES_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_M23_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M23_RES_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_M23_RES_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_M23_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_M23_RES_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SHP_M23_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f6, _d6);}
#define PE_SHP_HW_M23_RES_WR08(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6, _f7, _d7, _f8, _d8)	\
	{	PE_SHP_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6, _f7, _d7, _f8, _d8);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f5, _d5);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f6, _d6);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f7, _d7);\
		PE_SHP_HW_M23_RES_SET_USER(_r, _f8, _d8);}

#define PE_SHP_HW_M23_PBL_SET_USER(_r, _f, _d)	\
	{	_g_pe_pbl_hw_param_data_m23.reg_user.data->_r._f = (_d);\
		_g_pe_pbl_hw_param_data_m23.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_M23_PBL_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_M23_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M23_PBL_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M23_PBL_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_M23_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M23_PBL_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_M23_PBL_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_M23_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M23_PBL_SET_USER(_r, _f5, _d5);}

#define PE_SHP_HW_M23_CTI_SET_USER(_r, _f, _d)	\
	{	_g_pe_cti_hw_param_data_m23.reg_user.data->_r._f = (_d);\
		_g_pe_cti_hw_param_data_m23.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_M23_DNR_CTI_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_M23_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M23_DNR_CTI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M23_DNR_CTI_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_M23_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M23_DNR_CTI_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_M23_DNR_CTI_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_M23_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f5, _d5);}

#define PE_SHP_HW_M23_SHP_CTI_WR01(_r, _f1, _d1)	\
	{	PE_SHP_M23_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M23_SHP_CTI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M23_SHP_CTI_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_M23_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M23_SHP_CTI_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_M23_SHP_CTI_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_M23_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M23_CTI_SET_USER(_r, _f5, _d5);}

/* sre shp(srs) */
#define PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f, _d)	\
	{	_g_pe_srs_2k_hw_param_data_m23.reg_user.data->_r._f = (_d);\
		_g_pe_srs_2k_hw_param_data_m23.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_M23_SR_2K_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SR_2K_SHP_M23_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_M23_SR_2K_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SR_2K_SHP_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_M23_SR_2K_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SR_2K_SHP_M23_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_M23_SR_2K_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SR_2K_SHP_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_M23_SR_2K_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SR_2K_SHP_M23_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_M23_SR_2K_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SR_2K_SHP_M23_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_M23_SRS_2K_SET_USER(_r, _f6, _d6);}
/* set table */
#define PE_SHP_HW_M23_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_SHP_HW_M23_CHECK_CODE(!_dflt, ret=RET_ERROR;break,"_dflt is null, not ready.\n");\
		PE_SHP_HW_M23_CHECK_CODE(!_user, ret=RET_ERROR;break,"_user is null, not ready.\n");\
		PE_SHP_HW_M23_CHECK_CODE(!_mask, ret=RET_ERROR;break,"_mask is null, not ready.\n");\
		PE_SHP_HW_M23_CHECK_CODE(!_data, ret=RET_ERROR;break,"_data is null, not ready.\n");\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_M23_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			ret = PE_REG_M23_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_SHP_HW_M23_CHECK_CODE(ret,break,"PE_REG_M23_WrAllocatedAddr() error.\n");\
		}\
		if (ret == RET_OK)\
		{\
			PE_DBG_SHP("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

/* shp */
#define PE_SHP_HW_M23_RES_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_res_hw_param_data_m23.reg_dflt.addr;\
		UINT32 *_user = _g_pe_res_hw_param_data_m23.reg_user.addr;\
		UINT32 *_mask = _g_pe_res_hw_param_data_m23.reg_mask.addr;\
		UINT32 *_data = _g_pe_res_hw_param_data_m23.reg_data.addr;\
		PE_SHP_HW_M23_CHECK_CODE(\
		(sizeof(PE_RES_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "res tbl size violation.\n");\
		PE_SHP_HW_M23_SET_REG_TABLE(__tbl, __base);\
	}while (0)
/* sre shp(srs) */
#define PE_SHP_HW_M23_SRS_2K_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_srs_2k_hw_param_data_m23.reg_dflt.addr;\
		UINT32 *_user = _g_pe_srs_2k_hw_param_data_m23.reg_user.addr;\
		UINT32 *_mask = _g_pe_srs_2k_hw_param_data_m23.reg_mask.addr;\
		UINT32 *_data = _g_pe_srs_2k_hw_param_data_m23.reg_data.addr;\
		PE_SHP_HW_M23_CHECK_CODE(\
		(sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "srs tbl size violation.\n");\
		PE_SHP_HW_M23_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* cti */
#define PE_SHP_HW_M23_CTI_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_cti_hw_param_data_m23.reg_dflt.addr;\
		UINT32 *_user = _g_pe_cti_hw_param_data_m23.reg_user.addr;\
		UINT32 *_mask = _g_pe_cti_hw_param_data_m23.reg_mask.addr;\
		UINT32 *_data = _g_pe_cti_hw_param_data_m23.reg_data.addr;\
		PE_SHP_HW_M23_CHECK_CODE(\
		(sizeof(PE_CTI_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "cti tbl size violation.\n");\
		PE_SHP_HW_M23_SET_REG_TABLE(__tbl, __base);\
	}while (0)
/* obe objt */
	

#define PE_SHP_HW_M23_WR_SCL_COEFF(_wid, _ctrl, _coeff, _id)	\
{\
	char _str_buf[PE_TRACE_STR_SIZE];\
	snprintf(_str_buf,PE_TRACE_STR_SIZE,"[wid:%d][idx:%3d]%s", _wid, (_id), #_coeff);\
	PE_DBG_SHP("set %s\n", _str_buf);\
	PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
	PE_SHP_HW_M23_WrSclCoeff((_ctrl),&(_coeff));\
}

/* hex(8bit) to dec : eg. 0xAC -> 1012 */
#define PE_SHP_HW_M23_IDX_HEX_TO_DEC(_x)	(GET_BITS((_x),4,4)*100+GET_BITS((_x),0,4))
/* dec to hex(8bit) : eg. 1012 -> 0xAC */
#define PE_SHP_HW_M23_IDX_DEC_TO_HEX(_x)	(((((_x)/100)&0xf)<<4)+(((_x)%100)&0xf))

#define PE_SHP_HW_M23_CONV_VTAP_TO_VSC_MD(_x)		\
	((_x)==PE_SHP_HW_M23_SCL_VSC_MD_V12TAP||(_x)==PE_SHP_HW_M23_SCL_VSC_MD_V08TAP)? 0x0:\
	((_x)==PE_SHP_HW_M23_SCL_VSC_MD_V02TAP)? 0x3:0x1

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
/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
//static int PE_SHP_HW_M23_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static PE_SHP_HW_M23_RES_FMT PE_SHP_HW_M23_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_M23_2KS_FMT PE_SHP_HW_M23_ConvDispInfoTo2ksFmt(LX_PE_INF_DISPLAY_T *disp_inf);
__attribute__((unused)) static PE_SHP_HW_M23_CHR_FMT PE_SHP_HW_M23_ConvDispInfoToChrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_M23_CTI_FMT PE_SHP_HW_M23_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf);

static int PE_SHP_HW_M23_CreateDataTable(UINT32 index);
static int PE_SHP_HW_M23_SetResDefault(PE_SHP_HW_M23_RES_FMT cur0_res_fmt);
static int PE_SHP_HW_M23_Set2ksDefault(PE_SHP_HW_M23_2KS_FMT cur0_2ks_fmt);
__attribute__((unused)) static int PE_SHP_HW_M23_SetChrDefault(PE_SHP_HW_M23_CHR_FMT cur0_chr_fmt);

static int PE_SHP_HW_M23_SetCtiDefault(PE_SHP_HW_M23_CTI_FMT cur0_cti_fmt);

static int PE_SHP_HW_M23_DownloadScl12tMainDb(void);
static int PE_SHP_HW_M23_DownloadScl08tMainDb(void);
// static int PE_SHP_HW_M23_DownloadScl04tMainDb(void);
static int PE_SHP_HW_M23_DownloadShp2KSqmCmnUserDb(void *pstParams);
static int PE_SHP_HW_M23_DownloadShp2KSqmDetailUserDb(void *pstParams);
static int PE_SHP_HW_M23_DownloadShpSqmCmnUserDb(void *pstParams);
static int PE_SHP_HW_M23_DownloadShpSqmDetailUserDb(void *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT8 _g_shp_hw_m23_trace=0x0;	//default should be off.
static PE_SHP_HW_M23_SETTINGS_T _g_pe_shp_hw_m23_info;
static PE_RES_HW_PARAM_DATA_M23_T _g_pe_res_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_SRS_2K_HW_PARAM_DATA_M23_T _g_pe_srs_2k_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_PBL_HW_PARAM_DATA_M23_T _g_pe_pbl_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_CTI_HW_PARAM_DATA_M23_T _g_pe_cti_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};

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
int PE_SHP_HW_M23_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_REG_M23_HW_OPT_T hw_opt = PE_REG_M23_GetDispOpt();
	// int i, dflt_size;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			memset(&(_g_pe_shp_hw_m23_info), -1, sizeof(PE_SHP_HW_M23_SETTINGS_T));
			_g_pe_shp_hw_m23_info.res0a_fmt = PE_SHP_M23_RES_NUM;
			_g_pe_shp_hw_m23_info.cti0a_fmt = PE_SHP_M23_CTI_NUM;
			_g_pe_shp_hw_m23_info.k2s0a_fmt = PE_SHP_M23_2KS_NUM;
			PE_DBG_SHP("init cti.\n");
			//PE_SR_CHR_SHP_M23_QWr01(shp_core_ctrl_00,	reg_top_core_bypass, 0x0);
			PE_SR_2K_SHP_M23_QWr01(shp_core_ctrl_00,   reg_top_core_bypass, 0x0);
			PE_SHP_M23_QWr03(shp_core_ctrl_00,	reg_top_core_bypass, 0x0,\
												reg_top_mode_3d,0x0,\
												reg_top_lsb_copy_mode,0x0);
			/* res(pe1 shp l,r) : resolution enhance */
			ret = PE_SHP_HW_M23_CreateDataTable(PE_SHP_HW_M23_TBL_IDX_RES);
			PE_SHP_HW_M23_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M23_CreateDataTable() error.\n");
			//PE_SHP_HW_M23_RES_REG_TABLE(shp_l_hd_default_m23,PE_M23_REG_WRITE_BASE);
			/* sre shp(srs) */
			ret = PE_SHP_HW_M23_CreateDataTable(PE_SHP_HW_M23_TBL_IDX_SRS_2K);
			PE_SHP_HW_M23_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M23_CreateDataTable() error.\n");
			//PE_SHP_HW_M23_SRS_2K_REG_TABLE(sre_2k_res_hd_default_m23,PE_M23_REG_WRITE_BASE);
			/* cti */
			ret = PE_SHP_HW_M23_CreateDataTable(PE_SHP_HW_M23_TBL_IDX_CTI);
			PE_SHP_HW_M23_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M23_CreateDataTable() error.\n");
			//PE_SHP_HW_M23_CTI_REG_TABLE(cti_y_l_hd_default_m23,PE_M23_REG_WRITE_BASE);
			/* ord */
			//PE_SET_REG_TABLE(SHP_HW_M23,ord_default_m23,   PE_M23_REG_WRITE_BASE);
			PE_GSC_Y_M23_RdFL(gsc_g0_y_ctrl);
			PE_GSC_Y_M23_Wr01(gsc_g0_y_ctrl,reg_mode_32p_g0,0x0);		//phase 0x0:256,0x1:32
			//PE_GSC_Y_M23_Wr01(gsc_g0_y_ctrl,blending_range_g0,0x1);
			//PE_GSC_Y_M23_Wr01(gsc_g0_y_ctrl,reg_th0_g0,0x6);
			//PE_GSC_Y_M23_Wr01(gsc_g0_y_ctrl,reg_th1_g0,0x6);
			PE_GSC_Y_M23_WrFL(gsc_g0_y_ctrl);

			/* gsc_c */
			PE_GSC_C_M23_RdFL(gsc_g0_c_ctrl);
			PE_GSC_C_M23_Wr01(gsc_g0_c_ctrl,reg_mode_32p_g0,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_C_M23_WrFL(gsc_g0_c_ctrl);
			if (hw_opt.external_chip ==0) //4k model
			{
				_g_pe_shp_hw_m23_info.is_external_chip = 0;
			}
			else //8k model
			{
				_g_pe_shp_hw_m23_info.is_external_chip = 1;
			}
			#if 0
			// obc data dummy reg init
			PE_CCO_VERI_M23_QWr02(sys_veri_6,	head_apl, 0x200,\
												body_apl, 0x200);
			PE_CCO_VERI_M23_QWr02(sys_veri_7,	head_map,  0x200,\
												depth_map, 0x200);
			#endif
		}
		else
		{
			PE_DBG_SHP("nothing to do\n"); ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * create data table
 *
 * @param   index [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_SHP_HW_M23A_TBL_INDX
 * @author
 */
static int PE_SHP_HW_M23_CreateDataTable(UINT32 index)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_RES_HW_PARAM_DATA_M23_T *p_res_m23 = &_g_pe_res_hw_param_data_m23;
	PE_PBL_HW_PARAM_DATA_M23_T *p_pbl_m23 = &_g_pe_pbl_hw_param_data_m23;
	PE_SRS_2K_HW_PARAM_DATA_M23_T *p_srs_2k_m23 = &_g_pe_srs_2k_hw_param_data_m23;
	PE_CTI_HW_PARAM_DATA_M23_T *p_cti_m23 = &_g_pe_cti_hw_param_data_m23;
	PE_SHP_HW_M23_CHECK_CODE(index>=PE_SHP_HW_M23_TBL_IDX_NUM, return RET_ERROR, \
		"index(%d) invalid.\n", index);
	if (index == PE_SHP_HW_M23_TBL_IDX_RES)
	{
		/* create dflt table */
		if (p_res_m23->reg_dflt.addr == NULL)
		{
			p_res_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_res_m23->reg_user.addr == NULL)
		{
			p_res_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_M23_T));
			memset((p_res_m23->reg_user.addr), 0, sizeof(PE_RES_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_res_m23->reg_mask.addr == NULL)
		{
			p_res_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_M23_T));
			memset((p_res_m23->reg_mask.addr), -1, sizeof(PE_RES_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_res_m23->reg_data.addr == NULL)
		{
			p_res_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_M23_T));
			memset((p_res_m23->reg_data.addr), 0, sizeof(PE_RES_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_res_m23->reg_dflt.addr != NULL && p_res_m23->reg_user.addr != NULL && \
			p_res_m23->reg_mask.addr != NULL && p_res_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_M23_TBL_IDX_TO_STR(index), \
				(p_res_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_res_m23->reg_user.addr == NULL)? "x":"o", \
				(p_res_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_res_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_M23_TBL_IDX_PBL)
	{
		/* create dflt table */
		if (p_pbl_m23->reg_dflt.addr == NULL)
		{
			p_pbl_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_pbl_m23->reg_user.addr == NULL)
		{
			p_pbl_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_M23_T));
			memset((p_pbl_m23->reg_user.addr), 0, sizeof(PE_PBL_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_pbl_m23->reg_mask.addr == NULL)
		{
			p_pbl_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_M23_T));
			memset((p_pbl_m23->reg_mask.addr), -1, sizeof(PE_PBL_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_pbl_m23->reg_data.addr == NULL)
		{
			p_pbl_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_M23_T));
			memset((p_pbl_m23->reg_data.addr), 0, sizeof(PE_PBL_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_pbl_m23->reg_dflt.addr != NULL && p_pbl_m23->reg_user.addr != NULL && \
			p_pbl_m23->reg_mask.addr != NULL && p_pbl_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_M23_TBL_IDX_TO_STR(index), \
				(p_pbl_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_pbl_m23->reg_user.addr == NULL)? "x":"o", \
				(p_pbl_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_pbl_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_M23_TBL_IDX_CTI)
	{
		/* create dflt table */
		if (p_cti_m23->reg_dflt.addr == NULL)
		{
			p_cti_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_cti_m23->reg_user.addr == NULL)
		{
			p_cti_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_M23_T));
			memset((p_cti_m23->reg_user.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_cti_m23->reg_mask.addr == NULL)
		{
			p_cti_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_M23_T));
			memset((p_cti_m23->reg_mask.addr), -1, sizeof(PE_CTI_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_cti_m23->reg_data.addr == NULL)
		{
			p_cti_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_M23_T));
			memset((p_cti_m23->reg_data.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_cti_m23->reg_dflt.addr != NULL && p_cti_m23->reg_user.addr != NULL && \
			p_cti_m23->reg_mask.addr != NULL && p_cti_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_M23_TBL_IDX_TO_STR(index), \
				(p_cti_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_cti_m23->reg_user.addr == NULL)? "x":"o", \
				(p_cti_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_cti_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_M23_TBL_IDX_SRS_2K)
	{
		/* create dflt table */
		if (p_srs_2k_m23->reg_dflt.addr == NULL)
		{
			p_srs_2k_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_srs_2k_m23->reg_user.addr == NULL)
		{
			p_srs_2k_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T));
			memset((p_srs_2k_m23->reg_user.addr), 0, sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_srs_2k_m23->reg_mask.addr == NULL)
		{
			p_srs_2k_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T));
			memset((p_srs_2k_m23->reg_mask.addr), -1, sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_srs_2k_m23->reg_data.addr == NULL)
		{
			p_srs_2k_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T));
			memset((p_srs_2k_m23->reg_data.addr), 0, sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report srsult */
		if (p_srs_2k_m23->reg_dflt.addr != NULL && p_srs_2k_m23->reg_user.addr != NULL && \
			p_srs_2k_m23->reg_mask.addr != NULL && p_srs_2k_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_M23_TBL_IDX_TO_STR(index), \
				(p_srs_2k_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_srs_2k_m23->reg_user.addr == NULL)? "x":"o", \
				(p_srs_2k_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_srs_2k_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else
	{
		PE_DBG_SHP("nothing to do\n");	ret = RET_OK;
	}
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_SHP_HW_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_shp_hw_m23_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(SHP)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(SHP)),\
			pstParams->print_lvl,_g_shp_hw_m23_trace,pstParams->bypass);
	}while(0);
	return ret;
}

/**
 * default shp setting(for M23AX)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	__attribute__((unused)) PE_INF_M23_SETTINGS_T inf_set;
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *disp1_inf = NULL;
	__attribute__((unused)) PE_SHP_HW_M23_RES_FMT cur0_res_fmt;
	__attribute__((unused)) PE_SHP_HW_M23_CTI_FMT cur0_cti_fmt;
	__attribute__((unused)) PE_SHP_HW_M23_2KS_FMT cur0_2ks_fmt;
	__attribute__((unused)) PE_SHP_HW_M23_CHR_FMT cur0_chr_fmt;
	__attribute__((unused)) PE_SHP_HW_M23_OBC_FMT cur0_obc_fmt;
	__attribute__((unused)) PE_SHP_HW_M23_AMG_FMT cur0_amg_fmt;
	__attribute__((unused)) PE_SHP_HW_M23_OBE_FMT cur0_obe_fmt;
	__attribute__((unused)) PE_SHP_HW_M23_SETTINGS_T *pInfo=&_g_pe_shp_hw_m23_info;
	#ifdef PE_SHP_HW_M23_SR_PWD_TRACE
	UINT32 r_data[2];
	#endif
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_M23_GetCurInfSettings(&inf_set);
		PE_SHP_HW_M23_CHECK_CODE(ret,break,"PE_INF_M23_GetCurInfSettings() error.\n");
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		disp1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(disp0_inf);
		CHECK_KNULL(disp1_inf);
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			//*gpe_vsd_ctrl_block_m23 = 0x01200000;
			/* res(pe1 shp l,r) */
			cur0_res_fmt = PE_SHP_HW_M23_ConvDispInfoToResFmt(disp0_inf);
			PE_SHP_HW_M23_DBG_PRINT_RES_FMT_STATE(pInfo->res0a_fmt,cur0_res_fmt);
			if(pInfo->res0a_fmt!=cur0_res_fmt)
			{
				ret = PE_SHP_HW_M23_SetResDefault(cur0_res_fmt);
				PE_SHP_HW_M23_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M23_SetResDefault() error.\n");
				pInfo->res0a_fmt=cur0_res_fmt;
			}
			/* sre 2k shp(srs) */
			cur0_2ks_fmt = PE_SHP_HW_M23_ConvDispInfoTo2ksFmt(disp0_inf);
			PE_SHP_HW_M23_DBG_PRINT_2KS_FMT_STATE(pInfo->k2s0a_fmt,cur0_2ks_fmt);
			if(pInfo->k2s0a_fmt!=cur0_2ks_fmt)
			{
				ret = PE_SHP_HW_M23_Set2ksDefault(cur0_2ks_fmt);
				PE_SHP_HW_M23_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M23_Set2ksDefault() error.\n");
				pInfo->k2s0a_fmt=cur0_2ks_fmt;
			}
			/*cti(cti_dnr) */
			cur0_cti_fmt = PE_SHP_HW_M23_ConvDispInfoToCtiFmt(disp0_inf);
			PE_SHP_HW_M23_DBG_PRINT_CTI_FMT_STATE(pInfo->cti0a_fmt,cur0_cti_fmt);
			if(pInfo->cti0a_fmt!=cur0_cti_fmt)
			{
				ret = PE_SHP_HW_M23_SetCtiDefault(cur0_cti_fmt);
				PE_SHP_HW_M23_CHECK_CODE(ret, break, \
				"PE_SHP_HW_M23_SetCtiDefault() error.\n");
				pInfo->cti0a_fmt=cur0_cti_fmt;
			}
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * default Res setting(for M23X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_M23_RES_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_M23_SetResDefault(PE_SHP_HW_M23_RES_FMT cur0_res_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	switch(cur0_res_fmt)
	{
		case PE_SHP_M23_RES_SD:
		case PE_SHP_M23_RES_DTV_SD:
			PE_SHP_HW_M23_RES_REG_TABLE(shp_l_sd_default_m23,		PE_M23_REG_WRITE_BASE);
			break;
		case PE_SHP_M23_RES_HD:
		case PE_SHP_M23_RES_DTV_HD:
			PE_SHP_HW_M23_RES_REG_TABLE(shp_l_hd_default_m23,	PE_M23_REG_WRITE_BASE);
			break;
		case PE_SHP_M23_RES_UHD:
			PE_SHP_HW_M23_RES_REG_TABLE(shp_l_ud_default_m23,		PE_M23_REG_WRITE_BASE);
			break;
		case PE_SHP_M23_RES_SEEMLESS:
			PE_SHP_HW_M23_RES_REG_TABLE(shp_l_cp_default_m23,	PE_M23_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}


/**
 * default Res setting(for M23X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_M23_2KS_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_M23_Set2ksDefault(PE_SHP_HW_M23_2KS_FMT cur0_2ks_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	switch(cur0_2ks_fmt)
	{
		case PE_SHP_M23_2KS_SD:
			PE_SHP_HW_M23_SRS_2K_REG_TABLE(sre_2k_res_sd_default_m23,   PE_M23_REG_WRITE_BASE);
			break;
		case PE_SHP_M23_2KS_HD:
		case PE_SHP_M23_2KS_UHD:
			PE_SHP_HW_M23_SRS_2K_REG_TABLE(sre_2k_res_hd_default_m23,   PE_M23_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}


/**
 * default Res setting(for M23X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_M23_CHR_FMT
 * @return  
 * @see
 * @author
 */
__attribute__((unused)) static int PE_SHP_HW_M23_SetChrDefault(PE_SHP_HW_M23_CHR_FMT cur0_chr_fmt)
{
	int ret = RET_OK;
	return ret;
}
static int PE_SHP_HW_M23_SetCtiDefault(PE_SHP_HW_M23_CTI_FMT cur0_cti_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	switch(cur0_cti_fmt)
	{
		case PE_SHP_M23_CTI_SD:
			PE_SHP_HW_M23_CTI_REG_TABLE(cti_y_l_sd_default_m23,    PE_M23_REG_WRITE_BASE);
			break;
		case PE_SHP_M23_CTI_HD:
			PE_SHP_HW_M23_CTI_REG_TABLE(cti_y_l_hd_default_m23,    PE_M23_REG_WRITE_BASE);
			break;
		case PE_SHP_M23_CTI_VR_360:
			PE_SHP_HW_M23_CTI_REG_TABLE(cti_y_l_vr_360_default_m23,    PE_M23_REG_WRITE_BASE);
			break;
		case PE_SHP_M23_CTI_ATV:
			PE_SHP_HW_M23_CTI_REG_TABLE(cti_y_l_atv_default_m23,    PE_M23_REG_WRITE_BASE);
			break;
		case PE_SHP_M23_CTI_UD:
			PE_SHP_HW_M23_CTI_REG_TABLE(cti_y_l_ud_default_m23,    PE_M23_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get resolution fmt using display info(for M23X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M23_RES_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_M23_RES_FMT PE_SHP_HW_M23_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M23_RES_FMT res_fmt = PE_SHP_M23_RES_NUM;
	PE_DBG_SHP("ResFmt seemless mode :%d.\n", disp_inf->act_fmt );
	if(disp_inf->act_fmt !=0)
	{
		res_fmt = PE_SHP_M23_RES_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					res_fmt = PE_SHP_M23_RES_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_M23_RES_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_SHP_M23_RES_DTV_HD;
				}
				else
				{
					res_fmt = PE_SHP_M23_RES_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_M23_RES_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_SHP_M23_RES_HD;
				}
				else
				{
					res_fmt = PE_SHP_M23_RES_UHD;
				}
				break;
		}
	}
	return res_fmt;
}


/**
 * get sre 2k shp(srs) fmt using display info(for M23X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M23_2KS_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_M23_2KS_FMT PE_SHP_HW_M23_ConvDispInfoTo2ksFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M23_2KS_FMT srs_fmt = PE_SHP_M23_2KS_NUM;
	if(disp_inf->act_fmt !=0)
	{
		srs_fmt = PE_SHP_M23_2KS_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					srs_fmt = PE_SHP_M23_2KS_ATV;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					srs_fmt = PE_SHP_M23_2KS_SD;
				}
				break;
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_M23_2KS_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_M23_2KS_HD;
				}
				else
				{
					srs_fmt = PE_SHP_M23_2KS_UHD;
				}
				break;
		}
	}
	return srs_fmt;
}


/**
 * get sre chr shp(srs) fmt using display info(for M23X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M23_CHR_FMT.
 * @see
 * @author
 */
__attribute__((unused)) static PE_SHP_HW_M23_CHR_FMT PE_SHP_HW_M23_ConvDispInfoToChrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M23_CHR_FMT srs_fmt = PE_SHP_M23_CHR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			srs_fmt = PE_SHP_M23_CHR_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				srs_fmt = PE_SHP_M23_CHR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				srs_fmt = PE_SHP_M23_CHR_HD;
			}
			else
			{
				srs_fmt = PE_SHP_M23_CHR_UHD;
			}
			break;
	}
	return srs_fmt;
}
/**
 * get cti(dnr) fmt using display info(for M23X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_M23_CTI_FMT
 * @see
 * @author
 */
static PE_SHP_HW_M23_CTI_FMT PE_SHP_HW_M23_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_M23_CTI_FMT cti_fmt = PE_SHP_M23_CTI_NUM;
	if(disp_inf->mode.is_vr)
	{
			cti_fmt = PE_SHP_M23_CTI_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					cti_fmt = PE_SHP_M23_CTI_ATV;
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
					cti_fmt = PE_SHP_M23_CTI_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					cti_fmt = PE_SHP_M23_CTI_HD;
				}
				else
				{
					cti_fmt = PE_SHP_M23_CTI_UD;
				}
				break;
		}
	}
	return cti_fmt;
}

/**
 * read default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_SHP_HW_M23_RdDefault(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 param_size=0, table_size=0, is_valid=0;
	UINT32 rd_cnt=0;
	PE_REG_PARAM_T param;
	PE_SHP_HW_M23_SETTINGS_T *pInfo=&_g_pe_shp_hw_m23_info;

#define PE_SHP_M23_NO_PRINT			0
#define PE_SHP_M23_RD_N_HEX_PRINT	1
#define PE_SHP_M23_HEX_PRINT_ONLY	2
#define PE_SHP_M23_PRINT_START		"START_OF_PRINT"
#define PE_SHP_M23_PRINT_END		"END_OF_PRINT"
#define PE_SHP_M23_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_SHP_M23_PRINT_RESRV		"RESERVED"
#define PE_SHP_M23_PRINT_OBC		"RESERVED"
#define PE_SHP_M23_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, "   [0x%02X] %s\n", (_item), #_item);_action;break
#define PE_SHP_M23_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break
#define PE_SHP_M23_DFLT_SPRINT(_action, _buf, fmt, args...)		\
	default:snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break

	do{
		if (PE_KDRV_VER_M23)
		{
			UINT32 *p_res_dflt = _g_pe_res_hw_param_data_m23.reg_dflt.addr;
			UINT32 *p_res_user = _g_pe_res_hw_param_data_m23.reg_user.addr;
			UINT32 *p_res_mask = _g_pe_res_hw_param_data_m23.reg_mask.addr;
			UINT32 *p_res_data = _g_pe_res_hw_param_data_m23.reg_data.addr;
			UINT32 *p_cti_dflt = _g_pe_cti_hw_param_data_m23.reg_dflt.addr;
			UINT32 *p_cti_user = _g_pe_cti_hw_param_data_m23.reg_user.addr;
			UINT32 *p_cti_mask = _g_pe_cti_hw_param_data_m23.reg_mask.addr;
			UINT32 *p_cti_data = _g_pe_cti_hw_param_data_m23.reg_data.addr;
			UINT32 *p_srs_2k_dflt = _g_pe_srs_2k_hw_param_data_m23.reg_dflt.addr;
			UINT32 *p_srs_2k_user = _g_pe_srs_2k_hw_param_data_m23.reg_user.addr;
			UINT32 *p_srs_2k_mask = _g_pe_srs_2k_hw_param_data_m23.reg_mask.addr;
			UINT32 *p_srs_2k_data = _g_pe_srs_2k_hw_param_data_m23.reg_data.addr;
			CHECK_KNULL(pstParams);
			CHECK_KNULL(pstParams->data);
			CHECK_KNULL(p_res_dflt);
			CHECK_KNULL(p_res_user);
			CHECK_KNULL(p_res_mask);
			CHECK_KNULL(p_res_data);
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]>=PE_SHP_HW_M23_RD_MENU_MAX)
			{
				snprintf(buffer, PE_TRACE_STR_SIZE, PE_SHP_M23_PRINT_EXIT);
				rd_cnt=0;
			}
			else if (pstParams->data[0]==PE_SHP_HW_M23_RD_MENU_DISP)
			{
				switch (rd_cnt)
				{
					PE_SHP_M23_CASE_SPRINT( 0, rd_cnt++, buffer, PE_SHP_M23_PRINT_START);
					PE_SHP_M23_CASE_SPRINT( 1, rd_cnt++, buffer, "   ** current default **\n");
					PE_SHP_M23_CASE_SPRINT( 2, rd_cnt++, buffer, \
						"   res0a_fmt : %s\n", PE_SHP_HW_M23_RES_FMT_TO_STR(pInfo->res0a_fmt));
					PE_SHP_M23_CASE_SPRINT( 3, rd_cnt++, buffer, \
						"   cti0a_fmt : %s\n", PE_SHP_HW_M23_CTI_FMT_TO_STR(pInfo->cti0a_fmt));
					PE_SHP_M23_CASE_SPRINT( 4, rd_cnt++, buffer, \
						"   sre0a_fmt : %s\n", PE_SHP_HW_M23_SRE_FMT_TO_STR(pInfo->sre0a_fmt));
					PE_SHP_M23_CASE_SPRINT( 5, rd_cnt++, buffer, \
						"   k2s0a_fmt : %s\n", PE_SHP_HW_M23_2KS_FMT_TO_STR(pInfo->k2s0a_fmt));
					PE_SHP_M23_CASE_SPRINT( 6, rd_cnt++, buffer, \
						"   obe0a_fmt : %s\n", PE_SHP_HW_M23_OBE_FMT_TO_STR(pInfo->obe0a_fmt));
					PE_SHP_M23_CASE_SPRINT( 7, rd_cnt++, buffer, \
						"   obc0a_fmt : %s\n", PE_SHP_HW_M23_OBC_FMT_TO_STR(pInfo->obc0a_fmt));
					PE_SHP_M23_CASE_SPRINT( 8, rd_cnt++, buffer, \
						"   amg0a_fmt : %s\n", PE_SHP_HW_M23_AMG_FMT_TO_STR(pInfo->amg0a_fmt));
					PE_SHP_M23_CASE_SPRINT(9 , rd_cnt++, buffer, "   *********************\n");
					PE_SHP_M23_CASE_PRMENU(10, rd_cnt++, buffer, PE_SHP_HW_M23_RD_RES1_DISP);
					PE_SHP_M23_CASE_PRMENU(11, rd_cnt++, buffer, PE_SHP_HW_M23_RD_RES2_DISP);
					PE_SHP_M23_CASE_PRMENU(12, rd_cnt++, buffer, PE_SHP_HW_M23_RD_RES1_DFLT);
					PE_SHP_M23_CASE_PRMENU(13, rd_cnt++, buffer, PE_SHP_HW_M23_RD_RES1_USER);
					PE_SHP_M23_CASE_PRMENU(14, rd_cnt++, buffer, PE_SHP_HW_M23_RD_RES1_MASK);
					PE_SHP_M23_CASE_PRMENU(15, rd_cnt++, buffer, PE_SHP_HW_M23_RD_RES1_DATA);
					PE_SHP_M23_CASE_PRMENU(16, rd_cnt++, buffer, PE_SHP_HW_M23_RD_CTI1_DISP);
					PE_SHP_M23_CASE_PRMENU(17, rd_cnt++, buffer, PE_SHP_HW_M23_RD_CTI2_DISP);
					PE_SHP_M23_CASE_PRMENU(18, rd_cnt++, buffer, PE_SHP_HW_M23_RD_CTI1_DFLT);
					PE_SHP_M23_CASE_PRMENU(19, rd_cnt++, buffer, PE_SHP_HW_M23_RD_CTI1_USER);
					PE_SHP_M23_CASE_PRMENU(20, rd_cnt++, buffer, PE_SHP_HW_M23_RD_CTI1_MASK);
					PE_SHP_M23_CASE_PRMENU(21, rd_cnt++, buffer, PE_SHP_HW_M23_RD_CTI1_DATA);
					PE_SHP_M23_CASE_PRMENU(22, rd_cnt++, buffer, PE_SHP_HW_M23_RD_PBL1_DISP);
					PE_SHP_M23_CASE_PRMENU(23, rd_cnt++, buffer, PE_SHP_HW_M23_RD_PBL2_DISP);
					PE_SHP_M23_CASE_PRMENU(24, rd_cnt++, buffer, PE_SHP_HW_M23_RD_PBL1_DFLT);
					PE_SHP_M23_CASE_PRMENU(25, rd_cnt++, buffer, PE_SHP_HW_M23_RD_PBL1_USER);
					PE_SHP_M23_CASE_PRMENU(26, rd_cnt++, buffer, PE_SHP_HW_M23_RD_PBL1_MASK);
					PE_SHP_M23_CASE_PRMENU(27, rd_cnt++, buffer, PE_SHP_HW_M23_RD_PBL1_DATA);
					PE_SHP_M23_CASE_SPRINT(28, rd_cnt++, buffer, PE_SHP_M23_PRINT_RESRV);
					PE_SHP_M23_CASE_SPRINT(29, rd_cnt++, buffer, PE_SHP_M23_PRINT_RESRV);
					PE_SHP_M23_CASE_PRMENU(30, rd_cnt++, buffer, PE_SHP_HW_M23_RD_2KS1_DISP);
					PE_SHP_M23_CASE_PRMENU(31, rd_cnt++, buffer, PE_SHP_HW_M23_RD_2KS1_DFLT);
					PE_SHP_M23_CASE_PRMENU(32, rd_cnt++, buffer, PE_SHP_HW_M23_RD_2KS1_USER);
					PE_SHP_M23_CASE_PRMENU(33, rd_cnt++, buffer, PE_SHP_HW_M23_RD_2KS1_MASK);
					PE_SHP_M23_CASE_PRMENU(34, rd_cnt++, buffer, PE_SHP_HW_M23_RD_2KS1_DATA);
					PE_SHP_M23_CASE_PRMENU(35, rd_cnt++, buffer, PE_SHP_HW_M23_RD_OBE1_DISP);
					PE_SHP_M23_CASE_PRMENU(36, rd_cnt++, buffer, PE_SHP_HW_M23_RD_OBE1_DFLT);
					PE_SHP_M23_CASE_PRMENU(37, rd_cnt++, buffer, PE_SHP_HW_M23_RD_OBE1_USER);
					PE_SHP_M23_CASE_PRMENU(38, rd_cnt++, buffer, PE_SHP_HW_M23_RD_OBE1_MASK);
					PE_SHP_M23_CASE_PRMENU(39, rd_cnt++, buffer, PE_SHP_HW_M23_RD_OBE1_DATA);
					PE_SHP_M23_DFLT_SPRINT(rd_cnt=0, buffer, PE_SHP_M23_PRINT_END);
				}
			}
			else
			{
				is_valid = PE_SHP_M23_NO_PRINT;
				switch (pstParams->data[0])
				{
					case PE_SHP_HW_M23_RD_RES1_DISP:
					case PE_SHP_HW_M23_RD_RES2_DISP:
						table_size = sizeof(shp_l_hd_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m23[rd_cnt].addr;
							is_valid = PE_SHP_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_M23_RD_RES1_DFLT:
						table_size = sizeof(PE_RES_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m23[rd_cnt].addr;
							param.data = p_res_dflt[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_RES1_USER:
						table_size = sizeof(PE_RES_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m23[rd_cnt].addr;
							param.data = p_res_user[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_RES1_MASK:
						table_size = sizeof(PE_RES_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m23[rd_cnt].addr;
							param.data = p_res_mask[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_RES1_DATA:
						table_size = sizeof(PE_RES_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_m23[rd_cnt].addr;
							param.data = p_res_data[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_CTI1_DISP:
					case PE_SHP_HW_M23_RD_CTI2_DISP:
						table_size = sizeof(cti_y_l_hd_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m23[rd_cnt].addr;
							is_valid = PE_SHP_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_M23_RD_CTI1_DFLT:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m23[rd_cnt].addr;
							param.data = p_cti_dflt[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_CTI1_USER:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m23[rd_cnt].addr;
							param.data = p_cti_user[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_CTI1_MASK:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m23[rd_cnt].addr;
							param.data = p_cti_mask[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_CTI1_DATA:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_m23[rd_cnt].addr;
							param.data = p_cti_data[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_2KS1_DISP:
						table_size = sizeof(sre_2k_res_hd_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_m23[rd_cnt].addr;
							is_valid = PE_SHP_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_M23_RD_2KS1_DFLT:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_m23[rd_cnt].addr;
							param.data = p_srs_2k_dflt[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_2KS1_USER:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_m23[rd_cnt].addr;
							param.data = p_srs_2k_user[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_2KS1_MASK:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_m23[rd_cnt].addr;
							param.data = p_srs_2k_mask[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_M23_RD_2KS1_DATA:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_m23[rd_cnt].addr;
							param.data = p_srs_2k_data[rd_cnt];
							is_valid = PE_SHP_M23_HEX_PRINT_ONLY;
						}
						break;
					default:
						break;
				}
				if (is_valid == PE_SHP_M23_RD_N_HEX_PRINT)
				{
					#if 0	//not support PE_REG_M23_RD, use SYS_IO_ReadRegArray
					param.data = PE_REG_M23_RD(param.addr);
					#endif
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else if (is_valid == PE_SHP_M23_HEX_PRINT_ONLY)
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, PE_SHP_M23_PRINT_END);
					rd_cnt = 0;
				}
			}
			memcpy(pstParams->data, buffer, sizeof(char)*PE_TRACE_STR_SIZE);
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for M23X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetReEasyCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_RE_EASY_CMN_T *pp = (LX_PE_SHP_RE_EASY_CMN_T *)pstParams;
			static LX_PE_SHP_RE_EASY_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_RE_EASY_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_RE_EASY_CMN_T\n");
				ret=RET_OK;
				break;
			}
			pd = pp->shp_ui_vsd;
			PE_DBG_SHP("set[%d] : shp_ui_vsd\n"
			"shp_ui_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_HW_M23_RES_WR04(shp_mp_ctrl_01,	reg_mp_im_os_gain,		GET_BITS(pp->shp_ui_vsd[0],0,8),\
														reg_mp_im_us_gain,		GET_BITS(pp->shp_ui_vsd[1],0,8),\
														reg_mp_im_gain_h,		GET_BITS(pp->shp_ui_vsd[2],0,8),\
														reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_vsd[3],0,8));
				PE_SHP_HW_M23_RES_WR03(shp_sp_ctrl_01,	reg_sp_im_os_gain,		GET_BITS(pp->shp_ui_vsd[4],0,8),\
														reg_sp_im_us_gain,		GET_BITS(pp->shp_ui_vsd[5],0,8),\
														reg_sp_im_gain_h,		GET_BITS(pp->shp_ui_vsd[6],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_sti_ctrl_00, reg_sti_master_gain,	GET_BITS(pp->shp_ui_vsd[11],0,8));
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for M23X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_RE2_CMN_T *pp = (LX_PE_SHP_RE2_CMN_T *)pstParams;
			static LX_PE_SHP_RE2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_RE2_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_RE2_CMN_T\n");
				ret=RET_OK;
				break;
			}

			pd = pp->shp_ui_main_vsd;
			PE_DBG_SHP("set[%d] : shp_ui_main_vsd\n"
			"shp_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);
			pd = pp->shp_face_obj_vsd;
			PE_DBG_SHP("set[%d] : shp_face_obj_vsd\n"
			"shp_face_obj_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_face_obj_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_face_obj_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], \
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
			pd[20], pd[21], pd[22], pd[23], pd[24]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_HW_M23_RES_WR01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_vsd[0],0,8));
				//_SHP_HW_M23_RES_WR01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_vsd[1],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul, 	GET_BITS(pp->shp_ui_main_vsd[2],0,6));
				PE_SHP_HW_M23_RES_WR01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul, 	GET_BITS(pp->shp_ui_main_vsd[3],0,6));
				//PE_SHP_HW_M23_RES_WR01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_vsd[4],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_der_ctrl_00, 	reg_derh_csft_gain, 	GET_BITS(pp->shp_ui_main_vsd[5],0,6));
				PE_SHP_HW_M23_RES_WR02(shp_der_ctrl_02, 	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_main_vsd[6],0,6),\
															reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_main_vsd[7],0,6));
				PE_SHP_HW_M23_RES_WR01(shp_mp_ctrl_01,		reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_main_vsd[8],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_sp_ctrl_01,		reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_main_vsd[9],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_mp_ctrl_01,		reg_mp_im_gain_v ,	GET_BITS(pp->shp_ui_main_vsd[10],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_sti_ctrl_00, 	reg_sti_master_gain,GET_BITS(pp->shp_ui_main_vsd[11],0,8));
				#if 0 // nonexistent
				PE_SHP_HW_M23_SHP_CTI_WR01(shp_cti_ctrl_00, 	reg_cti_gain,		GET_BITS(pp->shp_ui_main_vsd[12],0,8));
				PE_SHP_HW_M23_SHP_CTI_WR02(shp_cti_ctrl_02, 	reg_cti_ycm_y_gain, GET_BITS(pp->shp_ui_main_vsd[13],0,4),\
													reg_cti_ycm_c_gain, GET_BITS(pp->shp_ui_main_vsd[14],0,4));
				PE_SHP_HW_M23_RES_WR01(shp_obj_ctrl_00,	reg_obj_sel_bit,					GET_BITS(pp->shp_face_obj_vsd[0],0,1));
				PE_SHP_HW_M23_RES_WR04(shp_obj_ctrl_09,	reg_obj_master_gain_a_map_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[1],0,8),\
														reg_obj_master_gain_a_map_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[2],0,8),\
														reg_obj_master_gain_a_map_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[3],0,8),\
														reg_obj_master_gain_a_map_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[4],0,8));
				PE_SHP_HW_M23_RES_WR04(shp_obj_ctrl_0a,	reg_obj_master_gain_a_map_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[5],0,8),\
														reg_obj_master_gain_a_map_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[6],0,8),\
														reg_obj_master_gain_a_map_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[7],0,8),\
														reg_obj_master_gain_a_map_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[8],0,8));

				PE_SHP_HW_M23_RES_WR04(shp_obj_ctrl_0b,	reg_obj_master_gain_t_map_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[9],0,8),\
														reg_obj_master_gain_t_map_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[10],0,8),\
														reg_obj_master_gain_t_map_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[11],0,8),\
														reg_obj_master_gain_t_map_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[12],0,8));
				PE_SHP_HW_M23_RES_WR04(shp_obj_ctrl_0c,	reg_obj_master_gain_t_map_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[13],0,8),\
														reg_obj_master_gain_t_map_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[14],0,8),\
														reg_obj_master_gain_t_map_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[15],0,8),\
														reg_obj_master_gain_t_map_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[16],0,8));
				#endif
				PE_SHP_HW_M23_RES_WR04(shp_dp_sum_ctrl_09,	reg_dp_sum_cg_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[17],0,8),\
															reg_dp_sum_cg_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[18],0,8),\
															reg_dp_sum_cg_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[19],0,8),\
															reg_dp_sum_cg_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[20],0,8));
				PE_SHP_HW_M23_RES_WR04(shp_dp_sum_ctrl_0a,	reg_dp_sum_cg_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[21],0,8),\
															reg_dp_sum_cg_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[22],0,8),\
															reg_dp_sum_cg_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[23],0,8),\
															reg_dp_sum_cg_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[24],0,8));
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for M23X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_GetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_RE2_CMN_T *pp = (LX_PE_SHP_RE2_CMN_T *)pstParams;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_M23_QWr01(shp_dctp_ctrl_1d,	reg_dctp_gain,			pp->shp_ui_main_vsd[0]);
				PE_SHP_M23_QWr01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul, pp->shp_ui_main_vsd[2]);
				PE_SHP_M23_QWr01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul, pp->shp_ui_main_vsd[3]);
				PE_SHP_M23_QWr01(shp_der_ctrl_00, 	reg_derh_csft_gain, 	pp->shp_ui_main_vsd[5]);
				PE_SHP_M23_QWr02(shp_der_ctrl_02, 	reg_derh_edge_filter_gain_w,pp->shp_ui_main_vsd[6],\
													reg_derh_edge_filter_gain_b,pp->shp_ui_main_vsd[7]);
				PE_SHP_M23_QWr01(shp_mp_ctrl_01,		reg_mp_im_gain_h,	pp->shp_ui_main_vsd[8]);
				PE_SHP_M23_QWr01(shp_sp_ctrl_01,		reg_sp_im_gain_h,	pp->shp_ui_main_vsd[9]);
				PE_SHP_M23_QWr01(shp_mp_ctrl_01,		reg_mp_im_gain_v ,	pp->shp_ui_main_vsd[10]);
				PE_SHP_M23_QWr01(shp_sti_ctrl_00, 	reg_sti_master_gain,    pp->shp_ui_main_vsd[11]);
			#if 0 // nonexistent
				PE_SHP_HW_M23_SHP_CTI_WR01(shp_cti_ctrl_00, 	reg_cti_gain,		GET_BITS(pp->shp_ui_main_vsd[12],0,8));
				PE_SHP_HW_M23_SHP_CTI_WR02(shp_cti_ctrl_02, 	reg_cti_ycm_y_gain, GET_BITS(pp->shp_ui_main_vsd[13],0,4),\
													reg_cti_ycm_c_gain, GET_BITS(pp->shp_ui_main_vsd[14],0,4));
				PE_SHP_HW_M23_RES_WR01(shp_obj_ctrl_00, reg_obj_sel_bit,					GET_BITS(pp->shp_face_obj_vsd[0],0,1));
				PE_SHP_HW_M23_RES_WR04(shp_obj_ctrl_09, reg_obj_master_gain_a_map_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[1],0,8),\
														reg_obj_master_gain_a_map_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[2],0,8),\
														reg_obj_master_gain_a_map_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[3],0,8),\
														reg_obj_master_gain_a_map_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[4],0,8));
				PE_SHP_HW_M23_RES_WR04(shp_obj_ctrl_0a, reg_obj_master_gain_a_map_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[5],0,8),\
														reg_obj_master_gain_a_map_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[6],0,8),\
														reg_obj_master_gain_a_map_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[7],0,8),\
														reg_obj_master_gain_a_map_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[8],0,8));

				PE_SHP_HW_M23_RES_WR04(shp_obj_ctrl_0b, reg_obj_master_gain_t_map_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[9],0,8),\
														reg_obj_master_gain_t_map_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[10],0,8),\
														reg_obj_master_gain_t_map_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[11],0,8),\
														reg_obj_master_gain_t_map_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[12],0,8));
				PE_SHP_HW_M23_RES_WR04(shp_obj_ctrl_0c, reg_obj_master_gain_t_map_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[13],0,8),\
														reg_obj_master_gain_t_map_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[14],0,8),\
														reg_obj_master_gain_t_map_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[15],0,8),\
														reg_obj_master_gain_t_map_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[16],0,8));
			#endif
				PE_SHP_M23_QWr04(shp_dp_sum_ctrl_09,	reg_dp_sum_cg_lut_x1,	pp->shp_face_obj_vsd[17],\
														reg_dp_sum_cg_lut_y1,	pp->shp_face_obj_vsd[18],\
														reg_dp_sum_cg_lut_x0,	pp->shp_face_obj_vsd[19],\
														reg_dp_sum_cg_lut_y0,	pp->shp_face_obj_vsd[20]);
				PE_SHP_M23_QWr04(shp_dp_sum_ctrl_0a,	reg_dp_sum_cg_lut_x3,	pp->shp_face_obj_vsd[21],\
														reg_dp_sum_cg_lut_y3,	pp->shp_face_obj_vsd[22],\
														reg_dp_sum_cg_lut_x2,	pp->shp_face_obj_vsd[23],\
														reg_dp_sum_cg_lut_y2,	pp->shp_face_obj_vsd[24]);
				pd = pp->shp_ui_main_vsd;
				printk("set[%d] : shp_ui_main_vsd\n"
				"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13], pd[14]);
				pd = pp->shp_face_obj_vsd;
				printk("set[%d] : shp_face_obj_vsd\n"
				"shp_face_obj_vsd	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_face_obj_vsd	 [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_face_obj_vsd	 [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], \
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
				pd[20], pd[21], pd[22], pd[23], pd[24]);
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n"); ret = RET_OK;
		}
	} while (0);
#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}


/**
 * set resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for M23X
 * - use input struct LX_PE_SHP_RE1_MISC_T for M23X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{ 
			UINT8 *pd;
			LX_PE_SHP_RE1_MISC_T *pp = (LX_PE_SHP_RE1_MISC_T *)pstParams;
			static LX_PE_SHP_RE1_MISC_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_RE1_MISC_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_RE1_MISC_T\n");
				ret=RET_OK;
				break;
			}
			pd = pp->shp_cmn_vsd;
			PE_DBG_SHP("set[%d] : shp_cmn_vsd\n"
			"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24]);
			pd = pp->shp_djg_vsd;
			PE_DBG_SHP("set[%d] : shp_djg_vsd\n"
			"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
			pd = pp->shp_map_cmn_vsd;
			PE_DBG_SHP("set[%d] : shp_map_cmn_vsd\n"
			"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_vsd;
			PE_DBG_SHP("set[%d] : shp_balance_vsd\n"
			"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_vsd;
			PE_DBG_SHP("set[%d] : shp_ti_cmn_vsd\n"
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_chroma_vsd;
			PE_DBG_SHP("set[%d] : shp_chroma_vsd\n"
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/*shp_cmn_vsd*/
				PE_SHP_HW_M23_RES_WR02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_vsd[0],0,1),\
														reg_derh_bflt_tap_size,		GET_BITS(pp->shp_cmn_vsd[1],0,3));
				PE_SHP_HW_M23_RES_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,		GET_BITS(pp->shp_cmn_vsd[2],0,1));
				PE_SHP_HW_M23_RES_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,		GET_BITS(pp->shp_cmn_vsd[3],0,1));
				PE_SHP_HW_M23_RES_WR02(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_cmn_vsd[4],0,7),\
														reg_mp_im_us_gain,	GET_BITS(pp->shp_cmn_vsd[5],0,7));
				PE_SHP_HW_M23_RES_WR02(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_cmn_vsd[6],0,7),\
														reg_sp_im_us_gain,	GET_BITS(pp->shp_cmn_vsd[7],0,7));
				#if 0
				PE_SHP_HW_M23_RES_WR01(shp_esf_ctrl_00, reg_esf_en, 		GET_BITS(pp->shp_cmn_vsd[8],0,1));
				PE_SHP_HW_M23_RES_WR03(shp_esf_ctrl_01, reg_esf_min_ratio,	GET_BITS(pp->shp_cmn_vsd[9],0,8),\
														reg_esf_base,		GET_BITS(pp->shp_cmn_vsd[10],0,8),\
														reg_esf_max_clip,	GET_BITS(pp->shp_cmn_vsd[11],0,8));
				#endif
				PE_SHP_HW_M23_RES_WR01(shp_dctp_ctrl_00,reg_dctp_en,		GET_BITS(pp->shp_cmn_vsd[12],0,1));
				PE_SHP_HW_M23_RES_WR02(shp_dctp_ctrl_1e,reg_dctp_coring_en, GET_BITS(pp->shp_cmn_vsd[13],0,1),\
														reg_dctp_coring_mode,	GET_BITS(pp->shp_cmn_vsd[14],0,2));
				#if 0
				PE_SHP_HW_M23_RES_WR01(shp_tgen_ctrl_00,reg_tgen_on_off,		GET_BITS(pp->shp_cmn_vsd[15],0,1));
				PE_SHP_HW_M23_RES_WR02(shp_tgen_ctrl_0a,reg_tgen_coring_en, 	GET_BITS(pp->shp_cmn_vsd[16],0,1),\
														reg_tgen_coring_mode,	GET_BITS(pp->shp_cmn_vsd[17],0,2));
				PE_SHP_HW_M23_RES_WR01(shp_nntg_ctrl_00,reg_nntg_en,			GET_BITS(pp->shp_cmn_vsd[18],0,1));
				PE_SHP_HW_M23_RES_WR02(shp_nntg_ctrl_0f,reg_nntg_coring_en, 	GET_BITS(pp->shp_cmn_vsd[19],0,1),\
														reg_nntg_coring_mode,	GET_BITS(pp->shp_cmn_vsd[20],0,2));
				PE_SHP_HW_M23_RES_WR01(shp_motion_prot_ctrl_00, reg_motion_prot_adaptive_en,	GET_BITS(pp->shp_cmn_vsd[21],0,1));
				PE_SHP_HW_M23_SHP_CTI_WR01(shp_cti_ctrl_00, reg_cti_en, 			GET_BITS(pp->shp_cmn_vsd[22],0,1));
				PE_SHP_HW_M23_SHP_CTI_WR01(shp_cti_ctrl_02, reg_cti_ycm_en, 		GET_BITS(pp->shp_cmn_vsd[23],0,1));
				PE_SHP_HW_M23_SHP_CTI_WR01(shp_cti_ctrl_00, reg_cti_filter_tap_size,GET_BITS(pp->shp_cmn_vsd[24],0,3));
				#endif
				/*shp_djg_vsd*/
				PE_SHP_HW_M23_RES_WR05(shp_dj_ctrl_00,	reg_dj_edf_en,				GET_BITS(pp->shp_djg_vsd[0],0,1),\
														reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_vsd[1],0,1),\
														reg_dj_soft_en, 			GET_BITS(pp->shp_djg_vsd[2],0,1),\
														reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_vsd[5],0,2),\
														reg_dj_n_avg_mode,			GET_BITS(pp->shp_djg_vsd[6],0,1));
				PE_SHP_HW_M23_RES_WR02(shp_dj_ctrl_03,	reg_dj_edge_min,			GET_BITS(pp->shp_djg_vsd[3],0,8),\
														reg_dj_edge_mul,			GET_BITS(pp->shp_djg_vsd[4],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			GET_BITS(pp->shp_djg_vsd[7],0,8));

				/*shp_map_cmn_vsd */
				PE_SHP_HW_M23_RES_WR02(shp_fd_ctrl_0b,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[0],0,1),\
														reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
				PE_SHP_HW_M23_RES_WR04(shp_fd_ctrl_0d,	reg_fd_mnr_gain_x0, GET_BITS(pp->shp_map_cmn_vsd[2],0,8),\
														reg_fd_mnr_gain_x1, GET_BITS(pp->shp_map_cmn_vsd[3],0,8),\
														reg_fd_mnr_gain_y0, GET_BITS(pp->shp_map_cmn_vsd[4],0,8),\
														reg_fd_mnr_gain_y1, GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
				PE_SHP_HW_M23_RES_WR02(shp_fd_ctrl_11,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[6],0,1),\
														reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[7],0,1));
				PE_SHP_HW_M23_RES_WR04(shp_fd_ctrl_14,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_vsd[8],0,6),\
														reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_vsd[9],0,6),\
														reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_vsd[10],0,6),\
														reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_vsd[11],0,6));

				/*shp_balance_vsd*/
				PE_SHP_HW_M23_RES_WR03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_vsd[0],0,1),\
														reg_mp_gb_mode, GET_BITS(pp->shp_balance_vsd[1],0,1),\
														reg_mp_gb_y1,	GET_BITS(pp->shp_balance_vsd[2],0,8));
				PE_SHP_HW_M23_RES_WR02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_vsd[3],0,8),\
														reg_mp_gb_y3,	GET_BITS(pp->shp_balance_vsd[4],0,8));
				PE_SHP_HW_M23_RES_WR03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_vsd[5],0,1),\
														reg_sp_gb_mode, GET_BITS(pp->shp_balance_vsd[6],0,1),\
														reg_sp_gb_y1,	GET_BITS(pp->shp_balance_vsd[7],0,8));
				PE_SHP_HW_M23_RES_WR02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_vsd[8],0,8),\
														reg_sp_gb_y3,	GET_BITS(pp->shp_balance_vsd[9],0,8));
				#if 0
				PE_SHP_HW_M23_RES_WR02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_vsd[10],0,1),\
														reg_lc_gb_en,	GET_BITS(pp->shp_balance_vsd[11],0,1));
				#else
				PE_SHP_HW_M23_RES_WR01(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_vsd[10],0,1));
				#endif
				PE_SHP_HW_M23_RES_WR02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_vsd[12],0,8),\
														reg_lc_gb_y2,	GET_BITS(pp->shp_balance_vsd[13],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_vsd[14],0,8));
				PE_SHP_HW_M23_RES_WR03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_vsd[15],0,8),\
														reg_lc_center_gain, GET_BITS(pp->shp_balance_vsd[16],0,8),\
														reg_lc_local_gain,	GET_BITS(pp->shp_balance_vsd[17],0,8));
				PE_SHP_HW_M23_RES_WR03(shp_mp_ctrl_08,	reg_mp_lum1_y0, GET_BITS(pp->shp_balance_vsd[18],0,8),\
														reg_mp_lum1_y1, GET_BITS(pp->shp_balance_vsd[19],0,8),\
														reg_mp_lum1_y2, GET_BITS(pp->shp_balance_vsd[20],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_mp_ctrl_09,	reg_mp_lum2_y0, GET_BITS(pp->shp_balance_vsd[21],0,8));
				PE_SHP_HW_M23_RES_WR02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, GET_BITS(pp->shp_balance_vsd[22],0,8),\
														reg_mp_lum2_y2, GET_BITS(pp->shp_balance_vsd[23],0,8));
				PE_SHP_HW_M23_RES_WR03(shp_sp_ctrl_08,	reg_sp_lum1_y0, GET_BITS(pp->shp_balance_vsd[24],0,8),\
														reg_sp_lum1_y1, GET_BITS(pp->shp_balance_vsd[25],0,8),\
														reg_sp_lum1_y2, GET_BITS(pp->shp_balance_vsd[26],0,8));
				PE_SHP_HW_M23_RES_WR01(shp_sp_ctrl_09,	reg_sp_lum2_y0, GET_BITS(pp->shp_balance_vsd[27],0,8));
				PE_SHP_HW_M23_RES_WR02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, GET_BITS(pp->shp_balance_vsd[28],0,8),\
														reg_sp_lum2_y2, GET_BITS(pp->shp_balance_vsd[29],0,8));
				/*shp_ti_cmn_vsd*/
				PE_SHP_HW_M23_RES_WR04(shp_pti_ctrl_00, reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_vsd[0],0,1),\
														reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
				PE_SHP_HW_M23_RES_WR04(shp_pti_ctrl_01, reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_vsd[4],0,1),\
														reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
				PE_SHP_HW_M23_RES_WR04(shp_sti_ctrl_00, reg_sti_enable, 		GET_BITS(pp->shp_ti_cmn_vsd[8],0,1),\
														reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
				/*shp_chroma_vsd*/
				#if 0 
				PE_SHP_HW_M23_RES_WR03(shp_chroma_ctrl_00,	reg_color_region_en,	GET_BITS(pp->shp_chroma_vsd[0],0,1),\
															reg_chr_protection_en,	GET_BITS(pp->shp_chroma_vsd[1],0,1),\
															reg_chr_compensation_en,	GET_BITS(pp->shp_chroma_vsd[2],0,1));
				PE_SHP_HW_M23_RES_WR02(shp_chroma_ctrl_0d,	reg_chr_gain_r0_gain,	GET_BITS(pp->shp_chroma_vsd[3],0,8),\
															reg_chr_gain_r1_gain,	GET_BITS(pp->shp_chroma_vsd[4],0,8));
				#endif
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
		
	} while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for M23X
 * - use input struct LX_PE_SHP_RE1_MISC_T for M23X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_GetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for M23
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_EE1_T *pp = (LX_PE_SHP_EE1_T *)pstParams;
			static LX_PE_SHP_EE1_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_EE1_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_EE1_T\n");
				ret=RET_OK;
				break;
			}
			pd = pp->shp_ee_vsd;
			PE_DBG_SHP("set[%d] : shp_ee_vsd\n"
			"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_HW_M23_RES_WR04(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[0],0,7),\
														reg_mp_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[1],0,7),\
														reg_mp_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[14],0,7),\
														reg_mp_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[15],0,7));
				PE_SHP_HW_M23_RES_WR04(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[2],0,7),\
														reg_sp_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[3],0,7),\
														reg_sp_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[16],0,7),\
														reg_sp_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[17],0,7));
				PE_SHP_HW_M23_RES_WR04(shp_pti_ctrl_03, reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[4],0,7),\
														reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[5],0,7),\
														reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[18],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[19],0,7));
				#if 0 // nonexistent
				PE_SHP_HW_M23_RES_WR04(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[6],0,7),\
														reg_lc_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[7],0,7),\
														reg_lc_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[20],0,7),\
														reg_lc_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[21],0,7));
				#endif
				PE_SHP_HW_M23_RES_WR04(shp_dctp_ctrl_1f,reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[8],0,7),\
														reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[9],0,7),\
														reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[22],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[23],0,7));
				#if 0 // nonexistent
				PE_SHP_HW_M23_RES_WR04(shp_tgen_ctrl_0b,reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[10],0,7),\
														reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[11],0,7),\
														reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[24],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[25],0,7));
				PE_SHP_HW_M23_RES_WR04(shp_nntg_ctrl_10,reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[12],0,7),\
														reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[13],0,7),\
														reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[26],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[27],0,7));
				#endif
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for M23
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_GetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_M23_SetSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_SHP_RE_SQM_CMN_T *ctrl_param =(LX_PE_SHP_RE_SQM_CMN_T *)pstParams;
			LX_PE_SHP_RE_SQM2_CMN_T *pp = (LX_PE_SHP_RE_SQM2_CMN_T *)ctrl_param->data;
			static LX_PE_SHP_RE_SQM2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_RE_SQM2_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_RE_SQM2_CMN_T\n");
				ret=RET_OK;
				break;
			}
			{
				__attribute__((unused)) UINT32 *pd = pp->shp_ui_sqm_vsd;
				PE_DBG_SHP("[%d]shp_ui_sqm_vsd:%d\n", pp->win_id, pp->shp_sqm____val);
				PE_DBG_SHP( \
				"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
				pd[10],pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19], \
				pd[20],pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26],  pd[27], pd[28],  pd[29],\
				pd[30],pd[31],  pd[32],  pd[33], pd[34],  pd[35],  pd[36],  pd[37], pd[38],  pd[39]);
			}
 			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_M23_DownloadShpSqmCmnUserDb((void *)pp);
				PE_SHP_HW_M23_CHECK_CODE(ret, break, \
					"PE_SHP_HW_M23_DownloadShpSqmCmnUserDb() error.\n");
			}
 		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_M23_SetSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_SHP_RE_SQM_DETAIL_T *ctrl_param =(LX_PE_SHP_RE_SQM_DETAIL_T *)pstParams;
			LX_PE_SHP_RE_SQM4_DETAIL_T *pp = (LX_PE_SHP_RE_SQM4_DETAIL_T *)ctrl_param->data;
			static LX_PE_SHP_RE_SQM4_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_RE_SQM4_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_RE_SQM3_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			{
			__attribute__((unused)) UINT32 *pd = pp->shp_sqm_cmn_vsd;
			PE_DBG_SHP("[%d]shp_sqm_cmn_vsd:%d\n", pp->win_id, pp->shp_sqm_____val);
			PE_DBG_SHP( \
			"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[70]0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
			pd[10],pd[11],	pd[12],  pd[13], pd[14],  pd[15],  pd[16],	pd[17], pd[18],  pd[19], \
			pd[20],pd[21],	pd[22],  pd[23], pd[24],  pd[25],  pd[26],	pd[27], pd[28],  pd[29],\
			pd[30],pd[31],	pd[32],  pd[33], pd[34],  pd[35],  pd[36],	pd[37], pd[38],  pd[39],\
			pd[40],pd[41],	pd[42],  pd[43], pd[34],  pd[45],  pd[46],	pd[47], pd[48],  pd[49],\
			pd[50],pd[51],	pd[52],  pd[53], pd[34],  pd[55],  pd[56],	pd[57], pd[58],  pd[59],\
			pd[60],pd[61],	pd[62],  pd[63], pd[34],  pd[65],  pd[66],	pd[67], pd[68],  pd[69],\
			pd[70]);
			}
 			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_M23_DownloadShpSqmDetailUserDb((void *)pp);
				PE_SHP_HW_M23_CHECK_CODE(ret, break, \
					"PE_SHP_HW_M23_DownloadShpSqmDetailUserDb() error.\n");
			}
 		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}


/**
 * set detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for M23
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_DE4_T *pp = (LX_PE_SHP_DE4_T *)pstParams;

			static LX_PE_SHP_DE4_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_DE4_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_DE4_T\n");
				ret=RET_OK;
				break;
			}

			pd = pp->shp_de_vsd;
			PE_DBG_SHP("set[%d] : shp_de_vsd\n"
			"shp_de_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_HW_M23_RES_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b, GET_BITS(pp->shp_de_vsd[0],0,7),\
														reg_mp_coring_gain_e_w, GET_BITS(pp->shp_de_vsd[1],0,7));
				PE_SHP_HW_M23_RES_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b, GET_BITS(pp->shp_de_vsd[2],0,7),\
														reg_sp_coring_gain_e_w, GET_BITS(pp->shp_de_vsd[3],0,7));
				PE_SHP_HW_M23_RES_WR02(shp_pti_ctrl_03, reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[4],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[5],0,7));
				PE_SHP_HW_M23_RES_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b, GET_BITS(pp->shp_de_vsd[6],0,7),\
														reg_lc_coring_gain_e_w, GET_BITS(pp->shp_de_vsd[7],0,7));
				PE_SHP_HW_M23_RES_WR02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[8],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[9],0,7));
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
#endif /*PE_HW_M23_BRINGUP*/
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
int PE_SHP_HW_M23_DownloadShpSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_ui_sqm_vsd.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_SHP_UI_SQM_VSD;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_SHP_UI_SQM_VSD_SIZE;
			p_phys_db->shp_ui_sqm_vsd.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_ui_sqm_vsd.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_ui_sqm_vsd.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_ui_sqm_vsd.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_SHP_UI_SQM_VSD_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_SHP_UI_SQM_VSD_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_vsd_cmn_init_m23[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
static int PE_SHP_HW_M23_DownloadShpSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_ui_sqm_vsd.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_SHP_UI_SQM_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_SHP_UI_SQM_VSD_T);
			pp = (LX_PE_SHP_RE_SQM2_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm____val;
			base = 2;
			for (i=0; i<PE_DDR_M23_SHP_UI_SQM_VSD_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_ui_sqm_vsd[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_SHP("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get  shp sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_GetShpSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM2_CMN_T *pp = NULL;
	//static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_ui_sqm_vsd.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_SHP_UI_SQM_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_SHP_UI_SQM_VSD_T);
			pp = (LX_PE_SHP_RE_SQM2_CMN_T *)pstParams;
			pp->shp_sqm____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_M23_SHP_UI_SQM_VSD_SIZE-base; i++)
			{
				pp->shp_ui_sqm_vsd[i] = p_db_data[base+i];
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			{
				__attribute__((unused)) UINT32 *pd = pp->shp_ui_sqm_vsd;
				printk("[%d]shp_ui_sqm_vsd:%d\n", pp->win_id, pp->shp_sqm____val);
				printk( \
				"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
				pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
				pd[10],pd[11],	pd[12],  pd[13], pd[14],  pd[15],  pd[16],	pd[17], pd[18],  pd[19], \
				pd[20],pd[21],	pd[22],  pd[23], pd[24],  pd[25],  pd[26],	pd[27], pd[28],  pd[29],\
				pd[30],pd[31],	pd[32],  pd[33], pd[34],  pd[35],  pd[36],	pd[37], pd[38],  pd[39]);
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_SHP_HW_M23_DownloadShpSqmDetailInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_sqmcmn__vsd.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_SHP_SQM_CMN_VSD;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_SHP_SQM_CMN_VSD_SIZE;
			p_phys_db->shp_sqmcmn__vsd.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_sqmcmn__vsd.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_sqmcmn__vsd.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_sqmcmn__vsd.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_SHP_SQM_CMN_VSD_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_SHP_SQM_CMN_VSD_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_vsd_dtl_init_m23[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
static int PE_SHP_HW_M23_DownloadShpSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM4_DETAIL_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_sqmcmn__vsd.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_SHP_SQM_CMN_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_SHP_SQM_CMN_VSD_T);
			pp = (LX_PE_SHP_RE_SQM4_DETAIL_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm_____val;
			base = 2;
			for (i=0; i<PE_DDR_M23_SHP_SQM_CMN_VSD_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_sqm_cmn_vsd[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_SHP("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get shp sqm detail db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_GetShpSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM4_DETAIL_T *pp = NULL;
	//static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_sqmcmn__vsd.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_SHP_SQM_CMN_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_SHP_SQM_CMN_VSD_T);
			pp = (LX_PE_SHP_RE_SQM4_DETAIL_T *)pstParams;
			pp->shp_sqm_____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_M23_SHP_SQM_CMN_VSD_SIZE-base; i++)
			{
				pp->shp_sqm_cmn_vsd[i] = p_db_data[base+i];
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			{
			__attribute__((unused)) UINT32 *pd32 = pp->shp_sqm_cmn_vsd;
			printk("[%d]shp_sqm_cmn_vsd:%d\n", pp->win_id, pp->shp_sqm_____val);
			printk( \
			"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[50]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[60]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[70]0x%08X\n",\
			pd32[0], pd32[1],	pd32[2], pd32[3], pd32[4], pd32[5], pd32[6],  pd32[7],pd32[8], pd32[9], \
			pd32[10],pd32[11],	pd32[12],pd32[13],pd32[14],pd32[15],pd32[16],	pd32[17],pd32[18],pd32[19], \
			pd32[20],pd32[21],	pd32[22],pd32[23],pd32[24],pd32[25],pd32[26],	pd32[27],pd32[28],pd32[29],\
			pd32[30],pd32[31],	pd32[32],pd32[33],pd32[34],pd32[35],pd32[36],	pd32[37],pd32[38],pd32[39],\
			pd32[40],pd32[41],	pd32[42],pd32[43],pd32[44],pd32[45],pd32[46],	pd32[47],pd32[48],pd32[49],\
			pd32[50],pd32[51],	pd32[52],pd32[53],pd32[54],pd32[55],pd32[56],	pd32[57],pd32[58],pd32[59],\
			pd32[60],pd32[61],	pd32[62],pd32[63],pd32[64],pd32[65],pd32[66],	pd32[67],pd32[68],pd32[69],\
			pd32[70]);
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for M23
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_GetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}

/**
 * set sr resolution common control - easy DB
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for M23X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetSre2KReEasyCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_RE_EASY_CMN_T *pp=(LX_PE_SHP_RE_EASY_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_vsd;
			PE_DBG_SHP("set[%d] : shp_ui_vsd\n"
			"shp_ui_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_HW_M23_SR_2K_SHP_WR04(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[0],0,8),\
													reg_mp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[1],0,8),\
													reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[2],0,8),\
													reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_vsd[3],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR03(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[4],0,8),\
													reg_sp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[5],0,8),\
													reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[6],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[7],0,8),\
													reg_mp_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[8],0,8));
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for M23X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetSre2KReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			__attribute__((unused)) UINT16 *pd16;
			LX_PE_SHP_SR2K_RE1_CMN_T *pp=(LX_PE_SHP_SR2K_RE1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_main_2k;
			PE_DBG_SHP("set[%d] : shp_ui_main_2k\n"
			"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_2k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd16 = pp->shp_dnn_sr_vsd;
			PE_DBG_SHP("set[%d] : shp_dnn_sr_vsd\n"
			"shp_dnn_sr_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				/*shp_ui_main_2k*/
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_dctp_ctrl_1d,	reg_dctp_gain,	GET_BITS(pp->shp_ui_main_2k[0],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_2k[1],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_dj_ctrl_1e,	reg_dj_soft_g1_mul, GET_BITS(pp->shp_ui_main_2k[2],0,6));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_dj_ctrl_1f,	reg_dj_soft_g2_mul, GET_BITS(pp->shp_ui_main_2k[3],0,6));
				//PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_2k[4],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_der_ctrl_00,	reg_derh_csft_gain, GET_BITS(pp->shp_ui_main_2k[5],0,6));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_main_2k[6],0,6),\
																	reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_main_2k[7],0,6));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_main_2k[8],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_main_2k[9],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_main_2k[10],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_sti_ctrl_00,	reg_sti_master_gain,	GET_BITS(pp->shp_ui_main_2k[11],0,8));
				#if 0
				/*shp_dnn_sr_vsd*/
				PE_SHP_HW_M23_SR_MERG_WR01(sr_merge_blend_00,	reg_blend_amp_weight,	GET_BITS(pp->shp_dnn_sr_vsd[0],0,12));
				PE_SHP_HW_M23_SR_MERG_WR04(sr_merge_mmd_05, 		reg_ti_gain_lut_x0, GET_BITS(pp->shp_dnn_sr_vsd[1],0,8),\
																	reg_ti_gain_lut_y0, GET_BITS(pp->shp_dnn_sr_vsd[2],0,8),\
																	reg_ti_gain_lut_x1, GET_BITS(pp->shp_dnn_sr_vsd[3],0,8),\
																	reg_ti_gain_lut_y1, GET_BITS(pp->shp_dnn_sr_vsd[4],0,8));
				PE_SHP_HW_M23_SR_MERG_WR04(sr_merge_mmd_06, 		reg_ti_gain_lut_x2, GET_BITS(pp->shp_dnn_sr_vsd[5],0,8),\
																	reg_ti_gain_lut_y2, GET_BITS(pp->shp_dnn_sr_vsd[6],0,8),\
																	reg_ti_gain_lut_x3, GET_BITS(pp->shp_dnn_sr_vsd[7],0,8),\
																	reg_ti_gain_lut_y3, GET_BITS(pp->shp_dnn_sr_vsd[8],0,8));
				#endif
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for M23X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_GetSre2KReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			__attribute__((unused)) UINT16 *pd16;
			LX_PE_SHP_SR2K_RE2_CMN_T *pp=(LX_PE_SHP_SR2K_RE2_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_M23_QRd01(shp_dctp_ctrl_1d,	reg_dctp_gain,			pp->shp_ui_main_2k[0]);
				//PE_SR_2K_SHP_M23_QRd01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	pp->shp_ui_main_2k[1]);
				PE_SR_2K_SHP_M23_QRd01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul, 	pp->shp_ui_main_2k[2]);
				PE_SR_2K_SHP_M23_QRd01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul, 	pp->shp_ui_main_2k[3]);
				//PE_SR_2K_SHP_M23_QRd01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	pp->shp_ui_main_2k[4]);
				PE_SR_2K_SHP_M23_QRd01(shp_der_ctrl_00,		reg_derh_csft_gain, 	pp->shp_ui_main_2k[5]);
				PE_SR_2K_SHP_M23_QRd02(shp_der_ctrl_02,		reg_derh_edge_filter_gain_w,	pp->shp_ui_main_2k[6],\
															reg_derh_edge_filter_gain_b,	pp->shp_ui_main_2k[7]);
				PE_SR_2K_SHP_M23_QRd01(shp_mp_ctrl_01,		reg_mp_im_gain_h,	pp->shp_ui_main_2k[8]);
				PE_SR_2K_SHP_M23_QRd01(shp_sp_ctrl_01,		reg_sp_im_gain_h,	pp->shp_ui_main_2k[9]);
				PE_SR_2K_SHP_M23_QRd01(shp_mp_ctrl_01,		reg_mp_im_gain_v,	pp->shp_ui_main_2k[10]);
				PE_SR_2K_SHP_M23_QRd01(shp_sti_ctrl_00,		reg_sti_master_gain,pp->shp_ui_main_2k[11]);
				#if 0
				/*shp_dnn_sr_vsd*/
				PE_SR_MERG_M23_QRd01(sr_merge_blend_00,		reg_blend_amp_weight,	pp->shp_dnn_sr_vsd[0]);
				PE_SR_MERG_M23_QRd04(sr_merge_mmd_05, 		reg_ti_gain_lut_x0, 	pp->shp_dnn_sr_vsd[1],\
																reg_ti_gain_lut_y0, pp->shp_dnn_sr_vsd[2],\
																reg_ti_gain_lut_x1, pp->shp_dnn_sr_vsd[3],\
																reg_ti_gain_lut_y1, pp->shp_dnn_sr_vsd[4]);
				PE_SR_MERG_M23_QRd04(sr_merge_mmd_06, 		reg_ti_gain_lut_x2, 	pp->shp_dnn_sr_vsd[5],\
																reg_ti_gain_lut_y2, pp->shp_dnn_sr_vsd[6],\
																reg_ti_gain_lut_x3, pp->shp_dnn_sr_vsd[7],\
																reg_ti_gain_lut_y3, pp->shp_dnn_sr_vsd[8]);
				#endif
				pd = pp->shp_ui_main_2k;
				PE_DBG_SHP("get[%d] : shp_ui_main_2k\n"
				"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_2k    [10]0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11]);
				#if 0
				pd16 = pp->shp_dnn_sr_vsd;
				PE_DBG_SHP("set[%d] : shp_dnn_sr_vsd\n"
				"shp_dnn_sr_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8]);
				#endif
				
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for M23X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetSre2KReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{ 
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE1_MISC_T *pp=(LX_PE_SHP_SR2K_RE1_MISC_T *)pstParams;
			static LX_PE_SHP_SR2K_RE1_MISC_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_SR2K_RE1_MISC_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_SR2K_RE1_MISC_T\n");
				ret=RET_OK;
				break;
			}

			pd = pp->shp_cmn_2k;
			PE_DBG_SHP("set[%d] : shp_cmn_2k\n"
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);
			pd = pp->shp_djg_2k;

			PE_DBG_SHP("set[%d] : shp_djg_2k\n"
			"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_2k;
			PE_DBG_SHP("set[%d] : shp_map_cmn_2k\n"
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_2k;

			PE_DBG_SHP("set[%d] : shp_balance_2k\n"
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_2k;
			PE_DBG_SHP("set[%d] : shp_ti_cmn_2k\n"
			"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				/*shp_cmn_2k*/
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_2k[0],0,1),\
																reg_derh_bflt_tap_size, GET_BITS(pp->shp_cmn_2k[1],0,3));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,	GET_BITS(pp->shp_cmn_2k[2],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,	GET_BITS(pp->shp_cmn_2k[3],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_cmn_2k[4],0,7),\
																reg_mp_im_us_gain,	GET_BITS(pp->shp_cmn_2k[5],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_cmn_2k[6],0,7),\
																reg_sp_im_us_gain,	GET_BITS(pp->shp_cmn_2k[7],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_dctp_ctrl_00,	reg_dctp_en,	GET_BITS(pp->shp_cmn_2k[8],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_dctp_ctrl_1e,	reg_dctp_coring_en, GET_BITS(pp->shp_cmn_2k[9],0,1),\
																reg_dctp_coring_mode,	GET_BITS(pp->shp_cmn_2k[10],0,2));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_on_off,	GET_BITS(pp->shp_cmn_2k[11],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_tgen_ctrl_0a,	reg_tgen_coring_en, GET_BITS(pp->shp_cmn_2k[12],0,1),\
																reg_tgen_coring_mode,	GET_BITS(pp->shp_cmn_2k[13],0,2));
				#if 0
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_nntg_ctrl_00,	reg_nntg_en,	GET_BITS(pp->shp_cmn_2k[14],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_nntg_ctrl_0f,	reg_nntg_coring_en, GET_BITS(pp->shp_cmn_2k[15],0,1),\
																reg_nntg_coring_mode,	GET_BITS(pp->shp_cmn_2k[16],0,2));
				#endif
				/*shp_djg_2k*/
				PE_SHP_HW_M23_SR_2K_SHP_WR05(shp_dj_ctrl_00,	reg_dj_edf_en,	GET_BITS(pp->shp_djg_2k[0],0,1),\
																reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_2k[1],0,1),\
																reg_dj_soft_en, GET_BITS(pp->shp_djg_2k[2],0,1),\
																reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_2k[5],0,2),\
																reg_dj_n_avg_mode,	GET_BITS(pp->shp_djg_2k[6],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_dj_ctrl_03,	reg_dj_edge_min, GET_BITS(pp->shp_djg_2k[3],0,8),\
																reg_dj_edge_mul,	GET_BITS(pp->shp_djg_2k[4],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,	GET_BITS(pp->shp_djg_2k[7],0,8));
				/*shp_map_cmn_2k*/
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_fd_ctrl_0b,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_2k[0],0,1),\
																reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_2k[1],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR04(shp_fd_ctrl_0d,	reg_fd_mnr_gain_x0,	GET_BITS(pp->shp_map_cmn_2k[2],0,8),\
																reg_fd_mnr_gain_x1,	GET_BITS(pp->shp_map_cmn_2k[3],0,8),\
																reg_fd_mnr_gain_y0,	GET_BITS(pp->shp_map_cmn_2k[4],0,8),\
																reg_fd_mnr_gain_y1,	GET_BITS(pp->shp_map_cmn_2k[5],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_fd_ctrl_11,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_2k[6],0,1),\
																reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_2k[7],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR04(shp_fd_ctrl_14,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_2k[8],0,6),\
																reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_2k[9],0,6),\
																reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_2k[10],0,6),\
																reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_2k[11],0,6));
				
				/*shp_balance_2k*/
				PE_SHP_HW_M23_SR_2K_SHP_WR03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_2k[0],0,1),\
																reg_mp_gb_mode, GET_BITS(pp->shp_balance_2k[1],0,1),\
																reg_mp_gb_y1,	GET_BITS(pp->shp_balance_2k[2],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_2k[3],0,8),\
																reg_mp_gb_y3,	GET_BITS(pp->shp_balance_2k[4],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_2k[5],0,1),\
																reg_sp_gb_mode, GET_BITS(pp->shp_balance_2k[6],0,1),\
																reg_sp_gb_y1,	GET_BITS(pp->shp_balance_2k[7],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_2k[8],0,8),\
																reg_sp_gb_y3,	GET_BITS(pp->shp_balance_2k[9],0,8));
				#if 0
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_2k[10],0,1),\
																reg_lc_gb_en,	GET_BITS(pp->shp_balance_2k[11],0,1));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_2k[12],0,8),\
																reg_lc_gb_y2,	GET_BITS(pp->shp_balance_2k[13],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_2k[14],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR03(shp_lc_ctrl_00,	reg_lc_center_target, GET_BITS(pp->shp_balance_2k[15],0,8),\
																reg_lc_center_gain, GET_BITS(pp->shp_balance_2k[16],0,8),\
																reg_lc_local_gain,	GET_BITS(pp->shp_balance_2k[17],0,8));
				#endif
				PE_SHP_HW_M23_SR_2K_SHP_WR03(shp_mp_ctrl_08,	reg_mp_lum1_y0, GET_BITS(pp->shp_balance_2k[18],0,8),\
																reg_mp_lum1_y1, GET_BITS(pp->shp_balance_2k[19],0,8),\
																reg_mp_lum1_y2, GET_BITS(pp->shp_balance_2k[20],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_mp_ctrl_09,	reg_mp_lum2_y0, GET_BITS(pp->shp_balance_2k[21],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, GET_BITS(pp->shp_balance_2k[22],0,8),\
																reg_mp_lum2_y2, GET_BITS(pp->shp_balance_2k[23],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR03(shp_sp_ctrl_08,	reg_sp_lum1_y0, GET_BITS(pp->shp_balance_2k[24],0,8),\
																reg_sp_lum1_y1, GET_BITS(pp->shp_balance_2k[25],0,8),\
																reg_sp_lum1_y2, GET_BITS(pp->shp_balance_2k[26],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR01(shp_sp_ctrl_09,	reg_sp_lum2_y0, GET_BITS(pp->shp_balance_2k[27],0,8));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, GET_BITS(pp->shp_balance_2k[28],0,8),\
																reg_sp_lum2_y2, GET_BITS(pp->shp_balance_2k[29],0,8));
				/*shp_ti_cmn_2k*/
				PE_SHP_HW_M23_SR_2K_SHP_WR04(shp_pti_ctrl_00,	reg_ptiv_enable,	GET_BITS(pp->shp_ti_cmn_2k[0],0,1),\
																reg_ptiv_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[1],0,1),\
																reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[2],0,2),\
																reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[3],0,2));
				PE_SHP_HW_M23_SR_2K_SHP_WR04(shp_pti_ctrl_01,	reg_ptih_enable,	GET_BITS(pp->shp_ti_cmn_2k[4],0,1),\
																reg_ptih_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[5],0,1),\
																reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[6],0,2),\
																reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[7],0,2));
				PE_SHP_HW_M23_SR_2K_SHP_WR04(shp_sti_ctrl_00,	reg_sti_enable, GET_BITS(pp->shp_ti_cmn_2k[8],0,1),\
																reg_sti_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[9],0,1),\
																reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[10],0,2),\
																reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[11],0,2));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_snr_ctrl_00,	reg_snr_blur_en,	GET_BITS(pp->shp_ti_cmn_2k[12],0,1),\
																reg_snr_blur_sel,	GET_BITS(pp->shp_ti_cmn_2k[13],0,2));
				
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for M23X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_GetSre2KReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE1_MISC_T *pp=(LX_PE_SHP_SR2K_RE1_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_2K_SHP_M23_QRd02(shp_der_ctrl_01,		reg_derh_edge_y_filter_en,	pp->shp_cmn_2k[0],\
															reg_derh_bflt_tap_size, pp->shp_cmn_2k[1]);
				PE_SR_2K_SHP_M23_QRd01(shp_mp_ctrl_00,		reg_mp_shp_en,			pp->shp_cmn_2k[2]);
				PE_SR_2K_SHP_M23_QRd01(shp_sp_ctrl_00,		reg_sp_shp_en,			pp->shp_cmn_2k[3]);
				PE_SR_2K_SHP_M23_QRd02(shp_mp_ctrl_01,		reg_mp_im_os_gain,		pp->shp_cmn_2k[4],\
															reg_mp_im_us_gain,		pp->shp_cmn_2k[5]);
				PE_SR_2K_SHP_M23_QRd02(shp_sp_ctrl_01,		reg_sp_im_os_gain,		pp->shp_cmn_2k[6],\
															reg_sp_im_us_gain,		pp->shp_cmn_2k[7]);
				PE_SR_2K_SHP_M23_QRd01(shp_dctp_ctrl_00,	reg_dctp_en,			pp->shp_cmn_2k[8]);
				PE_SR_2K_SHP_M23_QRd02(shp_dctp_ctrl_1e,	reg_dctp_coring_en, 	pp->shp_cmn_2k[9],\
															reg_dctp_coring_mode,	pp->shp_cmn_2k[10]);
				#if 0
				PE_SR_2K_SHP_M23_QRd01(shp_tgen_ctrl_00,	reg_tgen_on_off,		pp->shp_cmn_2k[11]);
				PE_SR_2K_SHP_M23_QRd02(shp_tgen_ctrl_0a,	reg_tgen_coring_en, 	pp->shp_cmn_2k[12],\
															reg_tgen_coring_mode,	pp->shp_cmn_2k[13]);
				PE_SR_2K_SHP_M23_QRd01(shp_nntg_ctrl_00,	reg_nntg_en,			pp->shp_cmn_2k[14]);
				PE_SR_2K_SHP_M23_QRd02(shp_nntg_ctrl_0f,	reg_nntg_coring_en, 	pp->shp_cmn_2k[15],\
															reg_nntg_coring_mode,	pp->shp_cmn_2k[16]);
				#endif
				/*shp_djg_2k*/
				PE_SR_2K_SHP_M23_QRd03(shp_dj_ctrl_00,		reg_dj_edf_en,			pp->shp_djg_2k[0],\
															reg_dj_edge_adaptive_en,pp->shp_djg_2k[1],\
															reg_dj_soft_en, 		pp->shp_djg_2k[2]);
				PE_SR_2K_SHP_M23_QRd02(shp_dj_ctrl_03,		reg_dj_edge_min, 		pp->shp_djg_2k[3],\
															reg_dj_edge_mul,		pp->shp_djg_2k[4]);
				PE_SR_2K_SHP_M23_QRd02(shp_dj_ctrl_00,		reg_dj_center_blur_mode,pp->shp_djg_2k[5],\
															reg_dj_n_avg_mode,		pp->shp_djg_2k[6]);
				PE_SR_2K_SHP_M23_QRd01(shp_dj_ctrl_01,		reg_dj_n_avg_gain,		pp->shp_djg_2k[7]);
				/*shp_map_cmn_2k*/
				PE_SR_2K_SHP_M23_QRd02(shp_fd_ctrl_0b,		reg_fd_mnr_gain_e_en,	pp->shp_map_cmn_2k[0],\
															reg_fd_mnr_gain_t_en,	pp->shp_map_cmn_2k[1]);
				PE_SR_2K_SHP_M23_QRd04(shp_fd_ctrl_0d,		reg_fd_mnr_gain_x0,		pp->shp_map_cmn_2k[2],\
															reg_fd_mnr_gain_x1,		pp->shp_map_cmn_2k[3],\
															reg_fd_mnr_gain_y0,		pp->shp_map_cmn_2k[4],\
															reg_fd_mnr_gain_y1,		pp->shp_map_cmn_2k[5]);
				PE_SR_2K_SHP_M23_QRd02(shp_fd_ctrl_11,		reg_fd_soft_gain_t_en,	pp->shp_map_cmn_2k[6],\
															reg_fd_soft_gain_e_en,	pp->shp_map_cmn_2k[7]);
				PE_SR_2K_SHP_M23_QRd04(shp_fd_ctrl_14,		reg_fd_soft_score_y3,	pp->shp_map_cmn_2k[8],\
															reg_fd_soft_score_y2,	pp->shp_map_cmn_2k[9],\
															reg_fd_soft_score_y1,	pp->shp_map_cmn_2k[10],\
															reg_fd_soft_score_y0,	pp->shp_map_cmn_2k[11]);
				
				/*shp_balance_2k*/
				PE_SR_2K_SHP_M23_QRd03(shp_mp_ctrl_05,		reg_mp_gb_en,	pp->shp_balance_2k[0],\
															reg_mp_gb_mode, pp->shp_balance_2k[1],\
															reg_mp_gb_y1,	pp->shp_balance_2k[2]);
				PE_SR_2K_SHP_M23_QRd02(shp_mp_ctrl_06,		reg_mp_gb_y2,	pp->shp_balance_2k[3],\
															reg_mp_gb_y3,	pp->shp_balance_2k[4]);
				PE_SR_2K_SHP_M23_QRd03(shp_sp_ctrl_05,		reg_sp_gb_en,	pp->shp_balance_2k[5],\
															reg_sp_gb_mode, pp->shp_balance_2k[6],\
															reg_sp_gb_y1,	pp->shp_balance_2k[7]);
				PE_SR_2K_SHP_M23_QRd02(shp_sp_ctrl_06,		reg_sp_gb_y2,	pp->shp_balance_2k[8],\
															reg_sp_gb_y3,	pp->shp_balance_2k[9]);
				#if 0
				PE_SR_2K_SHP_M23_QRd02(shp_lc_ctrl_00,		reg_lc_shp_en,	pp->shp_balance_2k[10],\
															reg_lc_gb_en,	pp->shp_balance_2k[11]);
				PE_SR_2K_SHP_M23_QRd02(shp_lc_ctrl_01,		reg_lc_gb_y1,	pp->shp_balance_2k[12],\
															reg_lc_gb_y2,	pp->shp_balance_2k[13]);
				PE_SR_2K_SHP_M23_QRd01(shp_lc_ctrl_02,		reg_lc_gb_y3,	pp->shp_balance_2k[14]);
				PE_SR_2K_SHP_M23_QRd03(shp_lc_ctrl_00,		reg_lc_center_target, pp->shp_balance_2k[15],\
															reg_lc_center_gain, pp->shp_balance_2k[16],\
															reg_lc_local_gain,	pp->shp_balance_2k[17]);
				#endif
				PE_SR_2K_SHP_M23_QRd03(shp_mp_ctrl_08,		reg_mp_lum1_y0, pp->shp_balance_2k[18],\
															reg_mp_lum1_y1, pp->shp_balance_2k[19],\
															reg_mp_lum1_y2, pp->shp_balance_2k[20]);
				PE_SR_2K_SHP_M23_QRd01(shp_mp_ctrl_09,		reg_mp_lum2_y0, pp->shp_balance_2k[21]);
				PE_SR_2K_SHP_M23_QRd02(shp_mp_ctrl_0a,		reg_mp_lum2_y1, pp->shp_balance_2k[22],\
															reg_mp_lum2_y2, pp->shp_balance_2k[23]);
				PE_SR_2K_SHP_M23_QRd03(shp_sp_ctrl_08,		reg_sp_lum1_y0, pp->shp_balance_2k[24],\
															reg_sp_lum1_y1, pp->shp_balance_2k[25],\
															reg_sp_lum1_y2, pp->shp_balance_2k[26]);
				PE_SR_2K_SHP_M23_QRd01(shp_sp_ctrl_09,		reg_sp_lum2_y0, pp->shp_balance_2k[27]);
				PE_SR_2K_SHP_M23_QRd02(shp_sp_ctrl_0a,		reg_sp_lum2_y1, pp->shp_balance_2k[28],\
															reg_sp_lum2_y2, pp->shp_balance_2k[29]);
				/*shp_ti_cmn_2k*/
				PE_SR_2K_SHP_M23_QRd04(shp_pti_ctrl_00,		reg_ptiv_enable,		pp->shp_ti_cmn_2k[0],\
															reg_ptiv_ti_mode,		pp->shp_ti_cmn_2k[1],\
															reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_2k[2],\
															reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_2k[3]);
				PE_SR_2K_SHP_M23_QRd04(shp_pti_ctrl_01,		reg_ptih_enable,		pp->shp_ti_cmn_2k[4],\
															reg_ptih_ti_mode,		pp->shp_ti_cmn_2k[5],\
															reg_ptih_mm_tap_size,	pp->shp_ti_cmn_2k[6],\
															reg_ptih_avg_tap_size,	pp->shp_ti_cmn_2k[7]);
				PE_SR_2K_SHP_M23_QRd04(shp_sti_ctrl_00,		reg_sti_enable, 		pp->shp_ti_cmn_2k[8],\
															reg_sti_ti_mode,		pp->shp_ti_cmn_2k[9],\
															reg_sti_mm_tap_size,	pp->shp_ti_cmn_2k[10],\
															reg_sti_avg_tap_size,	pp->shp_ti_cmn_2k[11]);
				PE_SR_2K_SHP_M23_QRd02(shp_snr_ctrl_00,		reg_snr_blur_en,		pp->shp_ti_cmn_2k[12],\
															reg_snr_blur_sel,		pp->shp_ti_cmn_2k[13]);


			}
			pd = pp->shp_cmn_2k;
			PE_DBG_SHP("get[%d] : shp_cmn_2k\n"
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);
			pd = pp->shp_djg_2k;

			PE_DBG_SHP("get[%d] : shp_djg_2k\n"
			"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_2k;
			PE_DBG_SHP("get[%d] : shp_map_cmn_2k\n"
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_2k;

			PE_DBG_SHP("get[%d] : shp_balance_2k\n"
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_2k;
			PE_DBG_SHP("get[%d] : shp_ti_cmn_2k\n"
			"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

		}
		
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for M23X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetSre2KEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_EE1_T *pp = (LX_PE_SHP_SR2K_EE1_T *)pstParams;
			static LX_PE_SHP_SR2K_EE1_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_SR2K_EE1_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_SR2K_EE1_T\n");
				ret=RET_OK;
				break;
			}
			pd = pp->shp_ee_2k;
			PE_DBG_SHP("set[%d] : shp_ee_2k\n"
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[0],0,7),\
																reg_mp_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[1],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[2],0,7),\
																reg_sp_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[3],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,GET_BITS(pp->shp_ee_2k[4],0,7),\
																reg_pti_coring_gain_e_w,GET_BITS(pp->shp_ee_2k[5],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[8],0,7),\
																reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[9],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[10],0,7),\
																reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[11],0,7));
				#if 0
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[6],0,7),\
																reg_lc_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[7],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[12],0,7),\
																reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[13],0,7));
				#endif
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[14],0,7),\
																reg_mp_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[15],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[16],0,7),\
																reg_sp_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[17],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,GET_BITS(pp->shp_ee_2k[18],0,7),\
																reg_pti_coring_gain_t_w,GET_BITS(pp->shp_ee_2k[19],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[22],0,7),\
																reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[23],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[24],0,7),\
																reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[25],0,7));
				#if 0
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[20],0,7),\
																reg_lc_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[21],0,7));
				PE_SHP_HW_M23_SR_2K_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[26],0,7),\
																reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[27],0,7));
				#endif
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get sr edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for M23
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_GetSre2KEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_EE1_T *pp = (LX_PE_SHP_SR2K_EE1_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_M23_QRd02(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b, pp->shp_ee_2k[0],\
															reg_mp_coring_gain_e_w, pp->shp_ee_2k[1]);
				PE_SR_2K_SHP_M23_QRd02(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b, pp->shp_ee_2k[2],\
															reg_sp_coring_gain_e_w, pp->shp_ee_2k[3]);
				PE_SR_2K_SHP_M23_QRd02(shp_pti_ctrl_03,		reg_pti_coring_gain_e_b,pp->shp_ee_2k[4],\
															reg_pti_coring_gain_e_w,pp->shp_ee_2k[5]);
				PE_SR_2K_SHP_M23_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	pp->shp_ee_2k[8],\
															reg_dctp_coring_gain_e_w,	pp->shp_ee_2k[9]);
				#if 0
				PE_SR_2K_SHP_M23_QRd02(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b, pp->shp_ee_2k[6],\
															reg_lc_coring_gain_e_w, pp->shp_ee_2k[7]);
				PE_SR_2K_SHP_M23_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	pp->shp_ee_2k[10],\
															reg_tgen_coring_gain_e_w,	pp->shp_ee_2k[11]);
				PE_SR_2K_SHP_M23_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	pp->shp_ee_2k[12],\
															reg_nntg_coring_gain_e_w,	pp->shp_ee_2k[13]);
				#endif
				PE_SR_2K_SHP_M23_QRd02(shp_mp_ctrl_0c,		reg_mp_coring_gain_t_b, pp->shp_ee_2k[14],\
															reg_mp_coring_gain_t_w, pp->shp_ee_2k[15]);
				PE_SR_2K_SHP_M23_QRd02(shp_sp_ctrl_0c,		reg_sp_coring_gain_t_b, pp->shp_ee_2k[16],\
															reg_sp_coring_gain_t_w, pp->shp_ee_2k[17]);
				PE_SR_2K_SHP_M23_QRd02(shp_pti_ctrl_03,		reg_pti_coring_gain_t_b,pp->shp_ee_2k[18],\
															reg_pti_coring_gain_t_w,pp->shp_ee_2k[19]);
				PE_SR_2K_SHP_M23_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	pp->shp_ee_2k[22],\
															reg_dctp_coring_gain_t_w,	pp->shp_ee_2k[23]);
				#if 0
				PE_SR_2K_SHP_M23_QRd02(shp_lc_ctrl_04,		reg_lc_coring_gain_t_b, pp->shp_ee_2k[20],\
															reg_lc_coring_gain_t_w, pp->shp_ee_2k[21]);
				PE_SR_2K_SHP_M23_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	pp->shp_ee_2k[24],\
															reg_tgen_coring_gain_t_w,	pp->shp_ee_2k[25]);
				PE_SR_2K_SHP_M23_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	pp->shp_ee_2k[26],\
															reg_nntg_coring_gain_t_w,	pp->shp_ee_2k[27]);
				#endif
				pd = pp->shp_ee_2k;
				PE_DBG_SHP("get[%d] : shp_ee_2k\n"
				"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
				pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for M23X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_SetSre2KDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * get sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for M23X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_M23_GetSre2KDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_M23_SetSre2KSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_SHP_SR2K_SQM_CMN_T *ctrl_param =(LX_PE_SHP_SR2K_SQM_CMN_T *)pstParams;
			LX_PE_SHP_SR2K_SQM2_CMN_T *pp = (LX_PE_SHP_SR2K_SQM2_CMN_T *)ctrl_param->data;
			static LX_PE_SHP_SR2K_SQM2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_SR2K_SQM2_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_SR2K_SQM2_CMN_T\n");
				ret=RET_OK;
				break;
			}
			{
			UINT32 *pd = pp->shp_ui_sqm_2k;
			PE_DBG_SHP("set[%d] : shp_ui_sqm_2k\n"
			"shp_ui_sqm_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
			pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_M23_DownloadShp2KSqmCmnUserDb((void *)pp);
				PE_SHP_HW_M23_CHECK_CODE(ret, break, \
					"PE_SHP_HW_M23_DownloadShp2KSqmCmnUserDb() error.\n");
			}
 		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_M23_SetSre2KSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_SHP_SR2K_SQM_DETAIL_T *ctrl_param =(LX_PE_SHP_SR2K_SQM_DETAIL_T *)pstParams;
			LX_PE_SHP_SR2K_SQM2_DETAIL_T *pp = (LX_PE_SHP_SR2K_SQM2_DETAIL_T *)ctrl_param->data;
			static LX_PE_SHP_SR2K_SQM2_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_SHP_SR2K_SQM2_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_SHP_SR2K_SQM2_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			{
			UINT32 *pd = pp->shp_sqm_cmn_2k;
			PE_DBG_SHP("[%d]shp_sqm_cmn_2k:%d\n", pp->win_id, pp->shp_sqm____val);
			PE_DBG_SHP( \
			"shp_sqm_cmn_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_2k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_2k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_2k[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_2k[40]0x%08X,0x%08X,0x%08X,\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19],\
			pd[20],  pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29],\
			pd[30],  pd[31],  pd[32],  pd[33], pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39],\
			pd[40],  pd[41],  pd[42]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_M23_DownloadShp2KSqmDetailUserDb((void *)pp);
				PE_SHP_HW_M23_CHECK_CODE(ret, break, \
					"PE_SHP_HW_M23_DownloadShp2KSqmDetailUserDb() error.\n");
			}
 		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_SHP_HW_M23_DownloadShp2KSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_ui_sqm_2k.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_SHP_UI_SQM_2K;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_SHP_UI_SQM_2K_SIZE;
			p_phys_db->shp_ui_sqm_2k.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_ui_sqm_2k.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_ui_sqm_2k.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_ui_sqm_2k.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_SHP_UI_SQM_2K_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_SHP_UI_SQM_2K_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_2k_cmn_init_m23[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
static int PE_SHP_HW_M23_DownloadShp2KSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_ui_sqm_2k.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_SHP_UI_SQM_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_SHP_UI_SQM_2K_T);
			pp = (LX_PE_SHP_SR2K_SQM2_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm___val;
			base = 2;
			for (i=0; i<PE_DDR_M23_SHP_UI_SQM_2K_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_ui_sqm_2k[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_SHP("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	//if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get sre 2k shp sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_GetShp2KSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM2_CMN_T *pp = NULL;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_ui_sqm_2k.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_SHP_UI_SQM_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_SHP_UI_SQM_2K_T);
			pp = (LX_PE_SHP_SR2K_SQM2_CMN_T *)pstParams;
			pp->shp_sqm___val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_M23_SHP_UI_SQM_2K_SIZE-base; i++)
			{
				pp->shp_ui_sqm_2k[i] = p_db_data[base+i] ;
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			{
			UINT32 *pd = pp->shp_ui_sqm_2k;
			printk("set[%d] : shp_ui_sqm_2k\n"
			"shp_ui_sqm_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_sqm_2k	  [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
			pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38]);
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	//if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_SHP_HW_M23_DownloadShp2KSqmDetailInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_sqmcmn__2k.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_SHP_SQM_CMN_2K;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_SHP_SQM_CMN_2K_SIZE;
			p_phys_db->shp_sqmcmn__2k.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_sqmcmn__2k.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_sqmcmn__2k.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_sqmcmn__2k.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_SHP_SQM_CMN_2K_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_SHP_SQM_CMN_2K_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_2k_dtl_init_m23[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
static int PE_SHP_HW_M23_DownloadShp2KSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM2_DETAIL_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->shp_sqmcmn__2k.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_SHP_SQM_CMN_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_SHP_SQM_CMN_2K_T);
			pp = (LX_PE_SHP_SR2K_SQM2_DETAIL_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm____val;
			base = 2;
			for (i=0; i<PE_DDR_M23_SHP_SQM_CMN_2K_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_sqm_cmn_2k[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_SHP("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	//if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get sre 2k shp sqm detail db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_GetShp2KSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM2_DETAIL_T *pp = NULL;
	//static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->shp_sqmcmn__2k.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_SHP_SQM_CMN_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_SHP_SQM_CMN_2K_T);
			pp = (LX_PE_SHP_SR2K_SQM2_DETAIL_T *)pstParams;
			pp->shp_sqm____val = (UINT8)p_db_data[1] ;
			base = 2;
			for (i=0; i<PE_DDR_M23_SHP_SQM_CMN_2K_SIZE-base; i++)
			{
				pp->shp_sqm_cmn_2k[i] = p_db_data[base+i];
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			{
			UINT32 *pd = pp->shp_sqm_cmn_2k;
			printk("[%d]shp_sqm_cmn_2k:%d\n", pp->win_id, pp->shp_sqm____val);
			printk( \
			"shp_sqm_cmn_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_2k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_2k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_2k[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_2k[40]0x%08X,0x%08X,0x%08X,\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14],	pd[15],  pd[16],  pd[17],  pd[18],	pd[19],\
			pd[20],  pd[21],  pd[22],  pd[23], pd[24],	pd[25],  pd[26],  pd[27],  pd[28],	pd[29],\
			pd[30],  pd[31],  pd[32],  pd[33], pd[34],	pd[35],  pd[36],  pd[37],  pd[38],	pd[39],\
			pd[40],  pd[41],  pd[42]);
			}
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	//if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}




/**
 * set pbl(pre blur dnr) apply
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_SetPblApply(PE_TSK_M23_CFG_T *pCfg)
{
	int ret = RET_OK;
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
int PE_SHP_HW_M23_DownloadSclDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		/* t12_m **************************************************************/
		ret = PE_SHP_HW_M23_DownloadScl12tMainDb();
		PE_SHP_HW_M23_CHECK_CODE(ret,break,"PE_SHP_HW_M23_DownloadScl12tMainDb() error.\n");
		/* t08_m **************************************************************/
		ret = PE_SHP_HW_M23_DownloadScl08tMainDb();
		PE_SHP_HW_M23_CHECK_CODE(ret,break,"PE_SHP_HW_M23_DownloadScl08tMainDb() error.\n");
		/* t04_m **************************************************************/
		//ret = PE_SHP_HW_M23_DownloadScl04tMainDb();
		//PE_SHP_HW_M23_CHECK_CODE(ret,break,"PE_SHP_HW_M23_DownloadScl04tMainDb() error.\n");
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
static int PE_SHP_HW_M23_DownloadScl12tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 size = 0, i = 0;
	UINT32 sec_typ_1212 = 0, sec_typ_1208 = 0, sec_typ_1206 = 0,sec_typ_1204 = 0, sec_typ_1202 = 0;
	UINT32 base_line_1212[PE_DDR_M23_1212T_FLT_NUM];
	UINT32 base_line_1208[PE_DDR_M23_1208T_FLT_NUM];
	UINT32 base_line_1206[PE_DDR_M23_1206T_FLT_NUM];
	UINT32 base_line_1204[PE_DDR_M23_1204T_FLT_NUM];
	UINT32 base_line_1202[PE_DDR_M23_1202T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_t1212_data = p_phys_db->t1212.data;
	volatile UINT32 *p_t1208_data = p_phys_db->t1208.data;
	volatile UINT32 *p_t1206_data = p_phys_db->t1206.data;
	volatile UINT32 *p_t1204_data = p_phys_db->t1204.data;
	volatile UINT32 *p_t1202_data = p_phys_db->t1202.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t1212_data);
		CHECK_KNULL(p_t1208_data);
		CHECK_KNULL(p_t1206_data);
		CHECK_KNULL(p_t1204_data);
		CHECK_KNULL(p_t1202_data);
		if (PE_KDRV_VER_M23)
		{
			/*1. 1212  */
			sec_typ_1212 = PE_DDR_M23_SEC_SCL_1212T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1212].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1212].header.sec_type  = sec_typ_1212;
			p_shdw_db->sec_d[sec_typ_1212].header.item_num  = PE_DDR_M23_1212T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1212].header.item_size = PE_DDR_M23_SCL_12T_FLT_SIZE;
			p_phys_db->t1212.header.version   = p_shdw_db->sec_d[sec_typ_1212].header.version;
			p_phys_db->t1212.header.sec_type  = p_shdw_db->sec_d[sec_typ_1212].header.sec_type;
			p_phys_db->t1212.header.item_num  = p_shdw_db->sec_d[sec_typ_1212].header.item_num;
			p_phys_db->t1212.header.item_size = p_shdw_db->sec_d[sec_typ_1212].header.item_size;

			/* data */
			size = (PE_DDR_M23_1212T_FLT_NUM * PE_DDR_M23_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1212] = \
				p_shdw_db->top_h.sec_base[sec_typ_1212-1]+p_shdw_db->top_h.sec_size[sec_typ_1212-1];
			p_shdw_db->top_h.sec_size[sec_typ_1212] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1212] = p_shdw_db->top_h.sec_base[sec_typ_1212];
			p_phys_db->top_h.sec_size[sec_typ_1212] = p_shdw_db->top_h.sec_size[sec_typ_1212];
			p_shdw_db->sec_d[sec_typ_1212].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1212] + sizeof(PE_DDR_M23_HEADER_T);

			/*2. 1208*/
			sec_typ_1208 = PE_DDR_M23_SEC_SCL_1208T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1208].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1208].header.sec_type  = sec_typ_1208;
			p_shdw_db->sec_d[sec_typ_1208].header.item_num  = PE_DDR_M23_1208T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1208].header.item_size = PE_DDR_M23_SCL_12T_FLT_SIZE;
			p_phys_db->t1208.header.version   = p_shdw_db->sec_d[sec_typ_1208].header.version;
			p_phys_db->t1208.header.sec_type  = p_shdw_db->sec_d[sec_typ_1208].header.sec_type;
			p_phys_db->t1208.header.item_num  = p_shdw_db->sec_d[sec_typ_1208].header.item_num;
			p_phys_db->t1208.header.item_size = p_shdw_db->sec_d[sec_typ_1208].header.item_size;
			/* data */
			size = (PE_DDR_M23_1208T_FLT_NUM * PE_DDR_M23_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1208] = \
				p_shdw_db->top_h.sec_base[sec_typ_1208-1]+p_shdw_db->top_h.sec_size[sec_typ_1208-1];
			p_shdw_db->top_h.sec_size[sec_typ_1208] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1208] = p_shdw_db->top_h.sec_base[sec_typ_1208];
			p_phys_db->top_h.sec_size[sec_typ_1208] = p_shdw_db->top_h.sec_size[sec_typ_1208];
			p_shdw_db->sec_d[sec_typ_1208].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1208] + sizeof(PE_DDR_M23_HEADER_T);

			/*3. 1206*/
			sec_typ_1206 = PE_DDR_M23_SEC_SCL_1206T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1206].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1206].header.sec_type  = sec_typ_1206;
			p_shdw_db->sec_d[sec_typ_1206].header.item_num  = PE_DDR_M23_1206T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1206].header.item_size = PE_DDR_M23_SCL_12T_FLT_SIZE;
			p_phys_db->t1206.header.version   = p_shdw_db->sec_d[sec_typ_1206].header.version;
			p_phys_db->t1206.header.sec_type  = p_shdw_db->sec_d[sec_typ_1206].header.sec_type;
			p_phys_db->t1206.header.item_num  = p_shdw_db->sec_d[sec_typ_1206].header.item_num;
			p_phys_db->t1206.header.item_size = p_shdw_db->sec_d[sec_typ_1206].header.item_size;
			/* data */
			size = (PE_DDR_M23_1206T_FLT_NUM * PE_DDR_M23_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1206] = \
				p_shdw_db->top_h.sec_base[sec_typ_1206-1]+p_shdw_db->top_h.sec_size[sec_typ_1206-1];
			p_shdw_db->top_h.sec_size[sec_typ_1206] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1206] = p_shdw_db->top_h.sec_base[sec_typ_1206];
			p_phys_db->top_h.sec_size[sec_typ_1206] = p_shdw_db->top_h.sec_size[sec_typ_1206];
			p_shdw_db->sec_d[sec_typ_1206].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1206] + sizeof(PE_DDR_M23_HEADER_T);

			/*4. 1204*/
			sec_typ_1204 = PE_DDR_M23_SEC_SCL_1204T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1204].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1204].header.sec_type  = sec_typ_1204;
			p_shdw_db->sec_d[sec_typ_1204].header.item_num  = PE_DDR_M23_1204T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1204].header.item_size = PE_DDR_M23_SCL_12T_FLT_SIZE;
			p_phys_db->t1204.header.version   = p_shdw_db->sec_d[sec_typ_1204].header.version;
			p_phys_db->t1204.header.sec_type  = p_shdw_db->sec_d[sec_typ_1204].header.sec_type;
			p_phys_db->t1204.header.item_num  = p_shdw_db->sec_d[sec_typ_1204].header.item_num;
			p_phys_db->t1204.header.item_size = p_shdw_db->sec_d[sec_typ_1204].header.item_size;
			/* data */
			size = (PE_DDR_M23_1204T_FLT_NUM * PE_DDR_M23_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1204] = \
				p_shdw_db->top_h.sec_base[sec_typ_1204-1]+p_shdw_db->top_h.sec_size[sec_typ_1204-1];
			p_shdw_db->top_h.sec_size[sec_typ_1204] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1204] = p_shdw_db->top_h.sec_base[sec_typ_1204];
			p_phys_db->top_h.sec_size[sec_typ_1204] = p_shdw_db->top_h.sec_size[sec_typ_1204];
			p_shdw_db->sec_d[sec_typ_1204].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1204] + sizeof(PE_DDR_M23_HEADER_T);

			/*5. 1202*/
			sec_typ_1202 = PE_DDR_M23_SEC_SCL_1202T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1202].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1202].header.sec_type  = sec_typ_1202;
			p_shdw_db->sec_d[sec_typ_1202].header.item_num  = PE_DDR_M23_1202T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1202].header.item_size = PE_DDR_M23_SCL_12T_FLT_SIZE;
			p_phys_db->t1202.header.version   = p_shdw_db->sec_d[sec_typ_1202].header.version;
			p_phys_db->t1202.header.sec_type  = p_shdw_db->sec_d[sec_typ_1202].header.sec_type;
			p_phys_db->t1202.header.item_num  = p_shdw_db->sec_d[sec_typ_1202].header.item_num;
			p_phys_db->t1202.header.item_size = p_shdw_db->sec_d[sec_typ_1202].header.item_size;
			/* data */
			size = (PE_DDR_M23_1202T_FLT_NUM * PE_DDR_M23_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1202] = \
				p_shdw_db->top_h.sec_base[sec_typ_1202-1]+p_shdw_db->top_h.sec_size[sec_typ_1202-1];
			p_shdw_db->top_h.sec_size[sec_typ_1202] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1202] = p_shdw_db->top_h.sec_base[sec_typ_1202];
			p_phys_db->top_h.sec_size[sec_typ_1202] = p_shdw_db->top_h.sec_size[sec_typ_1202];
			p_shdw_db->sec_d[sec_typ_1202].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1202] + sizeof(PE_DDR_M23_HEADER_T);

			/* wr ddr */
			base_line_1212[0] = 0;
			base_line_1208[0] = 0;
			base_line_1206[0] = 0;
			base_line_1204[0] = 0;
			base_line_1202[0] = 0;
			for (i=1; i<PE_DDR_M23_1212T_FLT_NUM; i++)
			{
				base_line_1212[i] = base_line_1212[i-1]+PE_DDR_M23_SCL_12T_FLT_SIZE;
			}
			for (i=1; i<PE_DDR_M23_1208T_FLT_NUM; i++)
			{
				base_line_1208[i] = base_line_1208[i-1]+PE_DDR_M23_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_M23_1206T_FLT_NUM; i++)
			{
				base_line_1206[i] = base_line_1206[i-1]+PE_DDR_M23_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_M23_1204T_FLT_NUM; i++)
			{
				base_line_1204[i] = base_line_1204[i-1]+PE_DDR_M23_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_M23_1202T_FLT_NUM; i++)
			{
				base_line_1202[i] = base_line_1202[i-1]+PE_DDR_M23_SCL_12T_FLT_SIZE;;
			}
			for (i=0; i<PE_DDR_M23_SCL_12T_FLT_SIZE; i++)
			{
				//1212
				p_t1212_data[base_line_1212[0]+i]  = scl_p256_1212t_flt_0004[i].data;
				p_t1212_data[base_line_1212[1]+i]  = scl_p256_1212t_flt_0006[i].data;
				p_t1212_data[base_line_1212[2]+i]  = scl_p256_1212t_flt_0104[i].data;
				p_t1212_data[base_line_1212[3]+i]  = scl_p256_1212t_flt_0304[i].data;
				p_t1212_data[base_line_1212[4]+i]  = scl_p256_1212t_flt_0306[i].data;
				p_t1212_data[base_line_1212[5]+i]  = scl_p256_1212t_flt_0404[i].data;
				p_t1212_data[base_line_1212[6]+i]  = scl_p256_1212t_flt_0606[i].data;
				p_t1212_data[base_line_1212[7]+i] = scl_p256_1212t_flt_1006[i].data;
				p_t1212_data[base_line_1212[8]+i] = scl_p256_1212t_flt_1006[i].data;//dummy
				p_t1212_data[base_line_1212[9]+i] = scl_p256_1212t_flt_1006[i].data;//dummy
				//1208
				p_t1208_data[base_line_1208[0]+i]  = scl_p256_1208t_flt_0004[i].data;
				p_t1208_data[base_line_1208[1]+i]  = scl_p256_1208t_flt_0006[i].data;
				p_t1208_data[base_line_1208[2]+i]  = scl_p256_1208t_flt_0104[i].data;
				p_t1208_data[base_line_1208[3]+i]  = scl_p256_1208t_flt_0304[i].data;
				p_t1208_data[base_line_1208[4]+i]  = scl_p256_1208t_flt_0306[i].data;
				p_t1208_data[base_line_1208[5]+i]  = scl_p256_1208t_flt_0606[i].data;
				p_t1208_data[base_line_1208[6]+i]  = scl_p256_1208t_flt_0806[i].data;
				p_t1208_data[base_line_1208[7]+i]  = scl_p256_1208t_flt_1410[i].data;
				p_t1208_data[base_line_1208[8]+i]  = scl_p256_1208t_flt_1410[i].data;//dummy
				p_t1208_data[base_line_1208[9]+i]  = scl_p256_1208t_flt_1410[i].data;//dummy
				//1206
				p_t1206_data[base_line_1206[0]+i]  = scl_p256_1206t_flt_0306[i].data;
				p_t1206_data[base_line_1206[1]+i]  = scl_p256_1206t_flt_0610[i].data;
				p_t1206_data[base_line_1206[2]+i]  = scl_p256_1206t_flt_0610[i].data;//dummy
				p_t1206_data[base_line_1206[3]+i]  = scl_p256_1206t_flt_0610[i].data;//dummy
				//1204
				p_t1204_data[base_line_1204[0]+i]  = scl_p256_1204t_flt_0008[i].data;
				p_t1204_data[base_line_1204[1]+i]  = scl_p256_1204t_flt_0308[i].data;
				p_t1204_data[base_line_1204[2]+i]  = scl_p256_1204t_flt_0910[i].data;
				p_t1204_data[base_line_1204[3]+i]  = scl_p256_1204t_flt_1410[i].data;
				p_t1204_data[base_line_1204[4]+i]  = scl_p256_1204t_flt_1510[i].data;
				p_t1204_data[base_line_1204[5]+i]  = scl_p256_1204t_flt_0306[i].data;//dummy
				p_t1204_data[base_line_1204[6]+i] = scl_p256_1204t_flt_1510[i].data;//dummy
				//1202
				p_t1202_data[base_line_1202[0]+i]  = scl_p256_1202t_flt_0308[i].data;
				p_t1202_data[base_line_1202[1]+i]  = scl_p256_1202t_flt_0308[i].data;//dummy
				p_t1202_data[base_line_1202[2]+i]  = scl_p256_1202t_flt_0308[i].data;//dummy
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ_1212), p_shdw_db->top_h.sec_base[sec_typ_1212]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ_1208), p_shdw_db->top_h.sec_base[sec_typ_1208]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ_1206), p_shdw_db->top_h.sec_base[sec_typ_1206]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ_1204), p_shdw_db->top_h.sec_base[sec_typ_1204]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ_1202), p_shdw_db->top_h.sec_base[sec_typ_1202]);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
static int PE_SHP_HW_M23_DownloadScl08tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 size = 0, i = 0, sec_typ_0804 = 0;
	UINT32 base_line_0804[PE_DDR_M23_0804T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_t0804_f_data = p_phys_db->t0804.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t0804_f_data);
		if (PE_KDRV_VER_M23)
		{

			/*1. 0804t */
			sec_typ_0804 = PE_DDR_M23_SEC_SCL_0804T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0804].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0804].header.sec_type  = sec_typ_0804;
			p_shdw_db->sec_d[sec_typ_0804].header.item_num  = PE_DDR_M23_0804T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0804].header.item_size = PE_DDR_M23_SCL_08T_FLT_SIZE;
			p_phys_db->t0804.header.version   = p_shdw_db->sec_d[sec_typ_0804].header.version;
			p_phys_db->t0804.header.sec_type  = p_shdw_db->sec_d[sec_typ_0804].header.sec_type;
			p_phys_db->t0804.header.item_num  = p_shdw_db->sec_d[sec_typ_0804].header.item_num;
			p_phys_db->t0804.header.item_size = p_shdw_db->sec_d[sec_typ_0804].header.item_size;
			/* data */
			size = (PE_DDR_M23_0804T_FLT_NUM * PE_DDR_M23_SCL_08T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0804] = \
				p_shdw_db->top_h.sec_base[sec_typ_0804-1]+p_shdw_db->top_h.sec_size[sec_typ_0804-1];
			p_shdw_db->top_h.sec_size[sec_typ_0804] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0804] = p_shdw_db->top_h.sec_base[sec_typ_0804];
			p_phys_db->top_h.sec_size[sec_typ_0804] = p_shdw_db->top_h.sec_size[sec_typ_0804];
			p_shdw_db->sec_d[sec_typ_0804].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0804] + sizeof(PE_DDR_M23_HEADER_T);

			/* wr ddr */
			base_line_0804[0] = 0;

			for (i=1; i<PE_DDR_M23_0804T_FLT_NUM; i++)
			{
				base_line_0804[i] = base_line_0804[i-1]+PE_DDR_M23_SCL_08T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_M23_SCL_08T_FLT_SIZE; i++)
			{
				//0804
				p_t0804_f_data[base_line_0804[0]+i]  = scl_p256_0804t_flt_0610[i].data;
				p_t0804_f_data[base_line_0804[1]+i]  = scl_p256_0804t_flt_0610[i].data;//dummy
				//p_t0804_f_data[base_line_0804[2]+i]  = scl_p256_0804t_flt_0610[i].data;//dumm
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ_0804), p_shdw_db->top_h.sec_base[sec_typ_0804]);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
#if 0
/**
 * download scl 04t main db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_HW_M23_DownloadScl04tMainDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 size = 0, i = 0;
	UINT32 sec_typ_0404 = 0, sec_typ_0402 = 0;
	UINT32 base_line_0404[PE_DDR_M23_0404T_FLT_NUM];
	UINT32 base_line_0402[PE_DDR_M23_0402T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_t0404_data = p_phys_db->t0404.data;
	volatile UINT32 *p_t0402_data = p_phys_db->t0402.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t0404_data);
		CHECK_KNULL(p_t0402_data);
		if (PE_KDRV_VER_M23)
		{
			/*1. 404t */
			sec_typ_0404 = PE_DDR_M23_SEC_SCL_0404T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0404].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0404].header.sec_type  = sec_typ_0404;
			p_shdw_db->sec_d[sec_typ_0404].header.item_num  = PE_DDR_M23_0404T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0404].header.item_size = PE_DDR_M23_SCL_04T_FLT_SIZE;
			p_phys_db->t0404.header.version   = p_shdw_db->sec_d[sec_typ_0404].header.version;
			p_phys_db->t0404.header.sec_type  = p_shdw_db->sec_d[sec_typ_0404].header.sec_type;
			p_phys_db->t0404.header.item_num  = p_shdw_db->sec_d[sec_typ_0404].header.item_num;
			p_phys_db->t0404.header.item_size = p_shdw_db->sec_d[sec_typ_0404].header.item_size;
			/* data */
			size = (PE_DDR_M23_0404T_FLT_NUM * PE_DDR_M23_SCL_04T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0404] = \
				p_shdw_db->top_h.sec_base[sec_typ_0404-1]+p_shdw_db->top_h.sec_size[sec_typ_0404-1];
			p_shdw_db->top_h.sec_size[sec_typ_0404] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0404] = p_shdw_db->top_h.sec_base[sec_typ_0404];
			p_phys_db->top_h.sec_size[sec_typ_0404] = p_shdw_db->top_h.sec_size[sec_typ_0404];
			p_shdw_db->sec_d[sec_typ_0404].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0404] + sizeof(PE_DDR_M23_HEADER_T);

			/*2. 402t  */
			sec_typ_0402 = PE_DDR_M23_SEC_SCL_0402T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0402].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0402].header.sec_type  = sec_typ_0402;
			p_shdw_db->sec_d[sec_typ_0402].header.item_num  = PE_DDR_M23_0402T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0402].header.item_size = PE_DDR_M23_SCL_04T_FLT_SIZE;
			p_phys_db->t0402.header.version   = p_shdw_db->sec_d[sec_typ_0402].header.version;
			p_phys_db->t0402.header.sec_type  = p_shdw_db->sec_d[sec_typ_0402].header.sec_type;
			p_phys_db->t0402.header.item_num  = p_shdw_db->sec_d[sec_typ_0402].header.item_num;
			p_phys_db->t0402.header.item_size = p_shdw_db->sec_d[sec_typ_0402].header.item_size;
			/* data */
			size = (PE_DDR_M23_0402T_FLT_NUM * PE_DDR_M23_SCL_04T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0402] = \
				p_shdw_db->top_h.sec_base[sec_typ_0402-1]+p_shdw_db->top_h.sec_size[sec_typ_0402-1];
			p_shdw_db->top_h.sec_size[sec_typ_0402] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0402] = p_shdw_db->top_h.sec_base[sec_typ_0402];
			p_phys_db->top_h.sec_size[sec_typ_0402] = p_shdw_db->top_h.sec_size[sec_typ_0402];
			p_shdw_db->sec_d[sec_typ_0402].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0402] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			base_line_0404[0] = 0;
			for (i=1; i<PE_DDR_M23_0404T_FLT_NUM; i++)
			{
				base_line_0404[i] = base_line_0404[i-1]+PE_DDR_M23_SCL_04T_FLT_SIZE;
			}
			base_line_0402[0] = 0;
			for (i=1; i<PE_DDR_M23_0402T_FLT_NUM; i++)
			{
				base_line_0402[i] = base_line_0402[i-1]+PE_DDR_M23_SCL_04T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_M23_SCL_04T_FLT_SIZE; i++)
			{
				//0404
				p_t0404_data[base_line_0404[0]+i] = scl_p256_0404t_flt_0308[i].data;
				p_t0404_data[base_line_0404[1]+i] = scl_p256_0404t_flt_0910[i].data;
				p_t0404_data[base_line_0404[2]+i] = scl_p256_0404t_flt_1410[i].data;
				p_t0404_data[base_line_0404[3]+i] = scl_p256_0404t_flt_1510[i].data;
				p_t0404_data[base_line_0404[4]+i] = scl_p256_0404t_flt_0610[i].data;
				p_t0404_data[base_line_0404[5]+i] = scl_p256_0404t_flt_0008[i].data;//added 211015
				p_t0404_data[base_line_0404[6]+i] = scl_p256_0404t_flt_1510[i].data;//dummy
				//0402
				p_t0402_data[base_line_0402[0]+i] = scl_p256_0402t_flt_0308[i].data;
				p_t0402_data[base_line_0402[1]+i] = scl_p256_0402t_flt_0308[i].data;//dummy
				p_t0402_data[base_line_0402[2]+i] = scl_p256_0402t_flt_0308[i].data;//dummy
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ_0404), p_shdw_db->top_h.sec_base[sec_typ_0404]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ_0402), p_shdw_db->top_h.sec_base[sec_typ_0402]);
		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
#endif
/**
 * set obc control
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_SetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
 			LX_PE_VSD_OBC4_CONT_T *pp=(LX_PE_VSD_OBC4_CONT_T *)pstParams;
			static LX_PE_VSD_OBC4_CONT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_VSD_OBC4_CONT_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_VSD_OBC3_CONT_T\n");
				ret=RET_OK;
				break;
			}
			if (_g_shp_hw_m23_trace)
			{
				printk("[wid:%d] set: n"\
				"head_gain_x0,x1,x2,x3: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"head_gain_y0,y1,y2,y3: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"body_gain_x0,x1,x2,x3: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"body_gain_y0,y1,y2,y3: 0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id,\
				pp->head_gain_x[0],pp->head_gain_x[1],\
				pp->head_gain_x[2],pp->head_gain_x[3],\
				pp->head_gain_y[0],pp->head_gain_y[1],\
				pp->head_gain_y[2],pp->head_gain_y[3],\
				pp->body_gain_x[0],pp->body_gain_x[1],\
				pp->body_gain_x[2],pp->body_gain_x[3],\
				pp->body_gain_y[0],pp->body_gain_y[1],\
				pp->body_gain_y[2],pp->body_gain_y[3]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_HW_M23_OBE_WR04(reg_obe_ctrl_083,	reg_head_gain_lut_y0,	GET_BITS(pp->head_gain_y[0],0,8),\
															reg_head_gain_lut_x0,	GET_BITS(pp->head_gain_x[0],0,8),\
															reg_head_gain_lut_y1,	GET_BITS(pp->head_gain_y[1],0,8),\
															reg_head_gain_lut_x1,	GET_BITS(pp->head_gain_x[1],0,8));
				PE_VSD_HW_M23_OBE_WR04(reg_obe_ctrl_082,	reg_head_gain_lut_y2,	GET_BITS(pp->head_gain_y[2],0,8),\
															reg_head_gain_lut_x2,	GET_BITS(pp->head_gain_x[2],0,8),\
															reg_head_gain_lut_y3,	GET_BITS(pp->head_gain_y[3],0,8),\
															reg_head_gain_lut_x3,	GET_BITS(pp->head_gain_x[3],0,8));
				PE_VSD_HW_M23_OBE_WR04(reg_obe_ctrl_085,	reg_body_gain_lut_y0,	GET_BITS(pp->body_gain_y[0],0,8),\
															reg_body_gain_lut_x0,	GET_BITS(pp->body_gain_x[0],0,8),\
															reg_body_gain_lut_y1,	GET_BITS(pp->body_gain_y[1],0,8),\
															reg_body_gain_lut_x1,	GET_BITS(pp->body_gain_x[1],0,8));
				PE_VSD_HW_M23_OBE_WR04(reg_obe_ctrl_084,	reg_body_gain_lut_y2,	GET_BITS(pp->body_gain_y[2],0,8),\
															reg_body_gain_lut_x2,	GET_BITS(pp->body_gain_x[2],0,8),\
															reg_body_gain_lut_y3,	GET_BITS(pp->body_gain_y[3],0,8),\
															reg_body_gain_lut_x3,	GET_BITS(pp->body_gain_x[3],0,8));
			}
 		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_SHP_HW_M23_GetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
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
int PE_SHP_HW_M23_SetObcLUT(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
 			LX_PE_VSD_OBC2_LUT_T *pp=(LX_PE_VSD_OBC2_LUT_T *)pstParams;
			static LX_PE_VSD_OBC2_LUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_VSD_OBC2_LUT_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_SHP("duplicated DB : LX_PE_VSD_OBC2_LUT_T\n");
				ret=RET_OK;
				break;
			}
			if (_g_shp_hw_m23_trace)
			{
				printk("[wid:%d] set: n"\
				"head_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"head_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"head_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"head_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"head_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"head_r_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"body_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"body_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"body_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"body_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"body_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"body_r_lut_y: %d,%d,%d,%d,%d,%d\n",\
				pp->win_id,\
				pp->head_g_lut_x[0],pp->head_g_lut_x[1],pp->head_g_lut_x[2],\
				pp->head_g_lut_x[3],pp->head_g_lut_x[4],pp->head_g_lut_x[5],\
				pp->head_g_lut_y[0],pp->head_g_lut_y[1],pp->head_g_lut_y[2],\
				pp->head_g_lut_y[3],pp->head_g_lut_y[4],pp->head_g_lut_y[5],\
				pp->head_b_lut_x[0],pp->head_b_lut_x[1],pp->head_b_lut_x[2],\
				pp->head_b_lut_x[3],pp->head_b_lut_x[4],pp->head_b_lut_x[5],\
				pp->head_b_lut_y[0],pp->head_b_lut_y[1],pp->head_b_lut_y[2],\
				pp->head_b_lut_y[3],pp->head_b_lut_y[4],pp->head_b_lut_y[5],\
				pp->head_r_lut_x[0],pp->head_r_lut_x[1],pp->head_r_lut_x[2],\
				pp->head_r_lut_x[3],pp->head_r_lut_x[4],pp->head_r_lut_x[5],\
				pp->head_r_lut_y[0],pp->head_r_lut_y[1],pp->head_r_lut_y[2],\
				pp->head_r_lut_y[3],pp->head_r_lut_y[4],pp->head_r_lut_y[5],\
				pp->body_g_lut_x[0],pp->body_g_lut_x[1],pp->body_g_lut_x[2],\
				pp->body_g_lut_x[3],pp->body_g_lut_x[4],pp->body_g_lut_x[5],\
				pp->body_g_lut_y[0],pp->body_g_lut_y[1],pp->body_g_lut_y[2],\
				pp->body_g_lut_y[3],pp->body_g_lut_y[4],pp->body_g_lut_y[5],\
				pp->body_b_lut_x[0],pp->body_b_lut_x[1],pp->body_b_lut_x[2],\
				pp->body_b_lut_x[3],pp->body_b_lut_x[4],pp->body_b_lut_x[5],\
				pp->body_b_lut_y[0],pp->body_b_lut_y[1],pp->body_b_lut_y[2],\
				pp->body_b_lut_y[3],pp->body_b_lut_y[4],pp->body_b_lut_y[5],\
				pp->body_r_lut_x[0],pp->body_r_lut_x[1],pp->body_r_lut_x[2],\
				pp->body_r_lut_x[3],pp->body_r_lut_x[4],pp->body_r_lut_x[5],\
				pp->body_r_lut_y[0],pp->body_r_lut_y[1],pp->body_r_lut_y[2],\
				pp->body_r_lut_y[3],pp->body_r_lut_y[4],pp->body_r_lut_y[5]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_028,	reg_head_r_lut_x0, GET_BITS(pp->head_r_lut_x[0],0,10),\
															reg_head_r_lut_y0, GET_BITS(pp->head_r_lut_y[0],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_029,	reg_head_r_lut_x1, GET_BITS(pp->head_r_lut_x[1],0,10),\
															reg_head_r_lut_y1, GET_BITS(pp->head_r_lut_y[1],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_030,	reg_head_r_lut_x2, GET_BITS(pp->head_r_lut_x[2],0,10),\
															reg_head_r_lut_y2, GET_BITS(pp->head_r_lut_y[2],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_031,	reg_head_r_lut_x3, GET_BITS(pp->head_r_lut_x[3],0,10),\
															reg_head_r_lut_y3, GET_BITS(pp->head_r_lut_y[3],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_032,	reg_head_r_lut_x4, GET_BITS(pp->head_r_lut_x[4],0,10),\
															reg_head_r_lut_y4, GET_BITS(pp->head_r_lut_y[4],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_033,	reg_head_r_lut_x5, GET_BITS(pp->head_r_lut_x[5],0,10),\
															reg_head_r_lut_y5, GET_BITS(pp->head_r_lut_y[5],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_034,	reg_head_g_lut_x0, GET_BITS(pp->head_g_lut_x[0],0,10),\
															reg_head_g_lut_y0, GET_BITS(pp->head_g_lut_y[0],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_035,	reg_head_g_lut_x1, GET_BITS(pp->head_g_lut_x[1],0,10),\
															reg_head_g_lut_y1, GET_BITS(pp->head_g_lut_y[1],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_036,	reg_head_g_lut_x2, GET_BITS(pp->head_g_lut_x[2],0,10),\
															reg_head_g_lut_y2, GET_BITS(pp->head_g_lut_y[2],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_037,	reg_head_g_lut_x3, GET_BITS(pp->head_g_lut_x[3],0,10),\
															reg_head_g_lut_y3, GET_BITS(pp->head_g_lut_y[3],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_038,	reg_head_g_lut_x4, GET_BITS(pp->head_g_lut_x[4],0,10),\
															reg_head_g_lut_y4, GET_BITS(pp->head_g_lut_y[4],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_039,	reg_head_g_lut_x5, GET_BITS(pp->head_g_lut_x[5],0,10),\
															reg_head_g_lut_y5, GET_BITS(pp->head_g_lut_y[5],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_040,	reg_head_b_lut_x0, GET_BITS(pp->head_b_lut_x[0],0,10),\
															reg_head_b_lut_y0, GET_BITS(pp->head_b_lut_y[0],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_041,	reg_head_b_lut_x1, GET_BITS(pp->head_b_lut_x[1],0,10),\
															reg_head_b_lut_y1, GET_BITS(pp->head_b_lut_y[1],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_042,	reg_head_b_lut_x2, GET_BITS(pp->head_b_lut_x[2],0,10),\
															reg_head_b_lut_y2, GET_BITS(pp->head_b_lut_y[2],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_043,	reg_head_b_lut_x3, GET_BITS(pp->head_b_lut_x[3],0,10),\
															reg_head_b_lut_y3, GET_BITS(pp->head_b_lut_y[3],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_044,	reg_head_b_lut_x4, GET_BITS(pp->head_b_lut_x[4],0,10),\
															reg_head_b_lut_y4, GET_BITS(pp->head_b_lut_y[4],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_045,	reg_head_b_lut_x5, GET_BITS(pp->head_b_lut_x[5],0,10),\
															reg_head_b_lut_y5, GET_BITS(pp->head_b_lut_y[5],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_046,	reg_body_r_lut_x0, GET_BITS(pp->body_r_lut_x[0],0,10),\
															reg_body_r_lut_y0, GET_BITS(pp->body_r_lut_y[0],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_047,	reg_body_r_lut_x1, GET_BITS(pp->body_r_lut_x[1],0,10),\
															reg_body_r_lut_y1, GET_BITS(pp->body_r_lut_y[1],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_048,	reg_body_r_lut_x2, GET_BITS(pp->body_r_lut_x[2],0,10),\
															reg_body_r_lut_y2, GET_BITS(pp->body_r_lut_y[2],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_049,	reg_body_r_lut_x3, GET_BITS(pp->body_r_lut_x[3],0,10),\
															reg_body_r_lut_y3, GET_BITS(pp->body_r_lut_y[3],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_050,	reg_body_r_lut_x4, GET_BITS(pp->body_r_lut_x[4],0,10),\
															reg_body_r_lut_y4, GET_BITS(pp->body_r_lut_y[4],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_051,	reg_body_r_lut_x5, GET_BITS(pp->body_r_lut_x[5],0,10),\
															reg_body_r_lut_y5, GET_BITS(pp->body_r_lut_y[5],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_052,	reg_body_g_lut_x0, GET_BITS(pp->body_g_lut_x[0],0,10),\
															reg_body_g_lut_y0, GET_BITS(pp->body_g_lut_y[0],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_053,	reg_body_g_lut_x1, GET_BITS(pp->body_g_lut_x[1],0,10),\
															reg_body_g_lut_y1, GET_BITS(pp->body_g_lut_y[1],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_054,	reg_body_g_lut_x2, GET_BITS(pp->body_g_lut_x[2],0,10),\
															reg_body_g_lut_y2, GET_BITS(pp->body_g_lut_y[2],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_055,	reg_body_g_lut_x3, GET_BITS(pp->body_g_lut_x[3],0,10),\
															reg_body_g_lut_y3, GET_BITS(pp->body_g_lut_y[3],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_056,	reg_body_g_lut_x4, GET_BITS(pp->body_g_lut_x[4],0,10),\
															reg_body_g_lut_y4, GET_BITS(pp->body_g_lut_y[4],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_057,	reg_body_g_lut_x5, GET_BITS(pp->body_g_lut_x[5],0,10),\
															reg_body_g_lut_y5, GET_BITS(pp->body_g_lut_y[5],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_058,	reg_body_b_lut_x0, GET_BITS(pp->body_b_lut_x[0],0,10),\
															reg_body_b_lut_y0, GET_BITS(pp->body_b_lut_y[0],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_059,	reg_body_b_lut_x1, GET_BITS(pp->body_b_lut_x[1],0,10),\
															reg_body_b_lut_y1, GET_BITS(pp->body_b_lut_y[1],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_060,	reg_body_b_lut_x2, GET_BITS(pp->body_b_lut_x[2],0,10),\
															reg_body_b_lut_y2, GET_BITS(pp->body_b_lut_y[2],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_061,	reg_body_b_lut_x3, GET_BITS(pp->body_b_lut_x[3],0,10),\
															reg_body_b_lut_y3, GET_BITS(pp->body_b_lut_y[3],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_062,	reg_body_b_lut_x4, GET_BITS(pp->body_b_lut_x[4],0,10),\
															reg_body_b_lut_y4, GET_BITS(pp->body_b_lut_y[4],0,10));
				PE_VSD_HW_M23_OBE_WR02(reg_obe_ctrl_063,	reg_body_b_lut_x5, GET_BITS(pp->body_b_lut_x[5],0,10),\
															reg_body_b_lut_y5, GET_BITS(pp->body_b_lut_y[5],0,10));
			}
 		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_SHP_HW_M23_GetObcLUT(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * get obc data
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_GetObcData(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
 			LX_PE_VSD_OBC2_DATA_T *pp=(LX_PE_VSD_OBC2_DATA_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#if 0
				pp->head_apl = 512;
				pp->body_apl = 512;
				pp->head_map_apl  = 512;
				pp->depth_map_apl = 512;
				#else
				PE_CCO_VERI_M23_QRd02(sys_veri_6,	head_apl,  pp->head_apl,\
													body_apl, pp->body_apl);
				PE_CCO_VERI_M23_QRd02(sys_veri_7,	head_map,  pp->head_map_apl,\
													depth_map, pp->depth_map_apl);
				#endif
			}
			if (_g_shp_hw_m23_trace)
			{
				printk("[wid:%d] get: n"\
				"head_apl:      %d\n"\
				"body_apl:      %d\n"\
				"head_map_apl:  %d\n"\
				"depth_map_apl: %d\n",\
				pp->win_id,\
				pp->head_apl, \
				pp->body_apl,\
				pp->head_map_apl, \
				pp->depth_map_apl);
			}
 		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set obc demomode
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_SetObcStereoCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 reg_obj_shp_en,reg_face_en,reg_obj_gain_en,reg_psp_en,reg_obc_debug;
	UINT32 *onoff;
	PE_SHP_HW_M23_SETTINGS_T *pInfo=&_g_pe_shp_hw_m23_info;
	// PE_REG_M23_HW_OPT_T hw_opt = PE_REG_M23_GetDispOpt();
	char buffer[PE_TRACE_STR_SIZE];
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
 			onoff = (UINT32*)pstParams;
			PE_DBG_SHP("set OBC Stereo Demo : %d \n",*onoff);

			if (*onoff > 0x2)	{PE_DBG_SHP("skip\n");break;}

			if(*onoff == 0x0)
			{
				reg_obj_shp_en = 0; //200619 always on bc, controled by lut, asked by leem C
				reg_face_en = 0;
				reg_obj_gain_en = 0;
				reg_psp_en = 1; // reg_psp_en is always enable, controled by lut, asked by kyuri.kim
				reg_obc_debug = 0;
			}
			else if(*onoff == 0x1)
			{
				reg_obj_shp_en = 1;
				reg_face_en = 1;
				reg_obj_gain_en = 1;
				reg_psp_en = 1;
				reg_obc_debug = 0;
			}
			else//if(*onoff == 0x2)
			{
				reg_obj_shp_en = 1;
				reg_face_en = 1;
				reg_obj_gain_en = 1;
				reg_psp_en = 1;
				reg_obc_debug = 1;
			}

			/* sharpness */
			//PE_SHP_HW_M23_RES_WR01(shp_obj_ctrl_00,	reg_obj_shp_en,	reg_obj_shp_en);
			pInfo->obc_stereo_ui = *onoff;
			/* decontour */
			PE_DNR0_M23_QWr01(reg_decon_ctrl_56, reg_face_en, reg_face_en);
			//PE_DNR1_M23_QWr01(reg_decon_ctrl_56, reg_face_en, reg_face_en);
			/* dc bnr */
			PE_DNR0_M23_QWr01(dc_bnr_ctrl_0, reg_obj_gain_en, reg_obj_gain_en);
			//PE_DNR1_M23_QWr01(dc_bnr_ctrl_0, reg_obj_gain_en, reg_obj_gain_en);
			/* OBE */
			#if 0 // 200908, obe is alway on including f20 model execpt for DSC input
			if (hw_opt.external_chip==0) //4k model
			{
				PE_VSD_HW_M23_OBE_WR01(reg_obe_ctrl_000, reg_obe_en, reg_psp_en);
			}
			else //8k model
			{
				PE_VSD_HW_M23_OBE_WR01(reg_obe_ctrl_000, reg_obe_en, 0x0);
			}
			#endif
			snprintf(buffer, PE_TRACE_STR_SIZE, "SetObcStereoCtrl on/off:%d,shp:%d,face:%d,obj_gain:%d,psp:%d,obc_debug:%d",\
				*onoff,reg_obj_shp_en,reg_face_en,reg_obj_gain_en,reg_psp_en,reg_obc_debug);
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",buffer);
			ret = PE_FWI_HW_M23_ObcDemoMode(reg_obc_debug);
			PE_SHP_M23_QWr01(shp_fsw_ctrl_02, reg_obc_debug, reg_obc_debug);
 		}
		else
		{
			PE_DBG_SHP("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

int PE_SHP_HW_M23_SetBypassObc(int bypass)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set obj_gain_lut
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_M23_SetOBCGainLUT(void)
{
	int ret = RET_OK;
	return ret;
}

int PE_SHP_HW_M23_SetObcMode(void)
{
	int ret = RET_OK;
	return ret;
}

