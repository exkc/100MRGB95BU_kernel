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

/** @file pe_nrd_hw_m23.c
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

#include "pe_hw_m23.h"
#include "pe_reg_m23.h"
#include "pe_fwi_m23.h"
#include "pe_cmn_hw_m23.h"
#include "pe_nrd_hw_m23.h"
#include "pe_hst_hw_m23.h"

#include "pe_tnr_hw_param_m23.h"
#include "pe_dnr_hw_param_m23.h"
#include "pe_ifc_hw_param_m23.h"
#include "pe_dnr_psp_hw_param_m23.h"
#ifdef INCLUDE_KDRV_AFE
#include "cvd_module.h"
#endif

#include "pe_tnr_l_lut_user_off_m23.h"
#include "pe_tnr_l_lut_user_low_m23.h"
#include "pe_tnr_l_lut_user_med_m23.h"
#include "pe_tnr_l_lut_user_high_m23.h"

#include "pe_tnr_l_lut_hd_default_m23.h"
#include "pe_tnr_l_lut_sd_default_m23.h"
#include "pe_tnr_l_lut_ud_default_m23.h"
#include "pe_tnr_l_lut_cam_hd_default_m23.h"

#include "pe_tnr_l_sd_default_m23.h"
#include "pe_tnr_l_hd_i_default_m23.h"
#include "pe_tnr_l_hd_p_default_m23.h"
#include "pe_tnr_l_ud_default_m23.h"
#include "pe_tnr_l_8k_default_m23.h"


#include "pe_dnr_l_hd_i_default_m23.h"
#include "pe_dnr_l_hd_p_default_m23.h"
#include "pe_dnr_l_sd_default_m23.h"
#include "pe_dnr_l_ud_default_m23.h"
#include "pe_dnr_l_dtv_sd_default_m23.h"
#include "pe_dnr_l_8k_default_m23.h"

#include "pe_led_dnr_l_ud_default_m23.h"
#include "pe_led_dnr_l_hd_default_m23.h"
#include "pe_led_dnr_l_sd_default_m23.h"
#include "pe_led_dnr_l_8k_default_m23.h"

#include "pe_sqm_tnr_init_m23.h"
#include "pe_sqm_dnr_init_m23.h"
#include "pe_sqm_dct_init_m23.h"

//m23f22

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 352,288 = 704/2,576/2 */
#define PE_NRD_HW_M23_H_MIN                (352)
#define PE_NRD_HW_M23_V_MIN                (288)
#define PE_NRD_HW_M23_TNR_SRC_H_HD_BASE    (800)
#define PE_NRD_HW_M23_TNR_SRC_V_3K_BASE    (1600)
#define PE_NRD_HW_M23_C_FMT_444            (0x6)
#define PE_NRD_HW_M23_C_FMT_422            (0x5)
#define PE_NRD_HW_M23_C_FMT_420            (0x4)

#define PE_NRD_HW_M23_SDR					(0)
#define PE_NRD_HW_M23_HDR2K					(1)
#define PE_NRD_HW_M23_HDR4K					(2)
#define PE_NRD_HW_M23_NUM_OF_TNR_CTRL_00_IN_TABLE (0)
#define PE_NRD_HW_M23_NUM_OF_DNR_MAX_CTRL_IN_TABLE (0)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_HW_M23_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_PRINT_ERROR(fmt,##args);_action;}}

#define PE_NRD_HW_M23_DBG_PRINT_TNR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M23_TNR_FMT_TO_STR(_pre), \
			PE_NRD_HW_M23_TNR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_NRD_HW_M23_DBG_PRINT_TNR2ND_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M23_TNR2ND_FMT_TO_STR(_pre), \
			PE_NRD_HW_M23_TNR2ND_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

/* tnr lut (tnl) */
#define PE_NRD_HW_M23_DBG_PRINT_TNL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M23_TNL_FMT_TO_STR(_pre), \
			PE_NRD_HW_M23_TNL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_NRD_HW_M23_DBG_PRINT_DNR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M23_DNR_FMT_TO_STR(_pre), \
			PE_NRD_HW_M23_DNR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_NRD_HW_M23_DBG_PRINT_PSP_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M23_PSP_FMT_TO_STR(_pre), \
			PE_NRD_HW_M23_PSP_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_NRD_HW_M23_DBG_PRINT_IFC_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M23_IFC_FMT_TO_STR(_pre), \
			PE_NRD_HW_M23_IFC_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_NRD_HW_M23_DBG_PRINT_LED_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_M23_LED_FMT_TO_STR(_pre), \
			PE_NRD_HW_M23_LED_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_M23_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_NRD_HW_M23_TNR0_SET_USER(_r, _f, _d)	\
	{	_g_pe_tnr_hw_param_data_m23.nd1_user.data->_r._f = (_d);\
		_g_pe_tnr_hw_param_data_m23.nd1_mask.data->_r._f = 0;}

#define PE_NRD_HW_M23_TNR0_WR01(_r, _f1, _d1)	\
	{	PE_ND0_M23_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_M23_TNR0_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND0_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_M23_TNR0_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND0_M23_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_M23_TNR0_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND0_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_M23_TNR0_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND0_M23_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_M23_TNR0_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_ND0_M23_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f6, _d6);}
#define PE_NRD_HW_M23_TNR0_WR07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7)	\
	{	PE_ND0_M23_QWr07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f7, _d7);}

#define PE_NRD_HW_M23_TNR0_WR09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_ND0_M23_QWr09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f9, _d9);}

#define PE_NRD_HW_M23_TNR0_WR10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_ND0_M23_QWr10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f9, _d9);\
		PE_NRD_HW_M23_TNR0_SET_USER(_r, _f10, _d10);}

#if 0
#define PE_NRD_HW_M23_TNR1_SET_USER(_r, _f, _d)	\
	{	_g_pe_tnr2nd_hw_param_data_m23.nd1_user.data->_r._f = (_d);\
		_g_pe_tnr2nd_hw_param_data_m23.nd1_mask.data->_r._f = 0;}

#define PE_NRD_HW_M23_TNR1_WR01(_r, _f1, _d1)	\
	{	PE_ND1_M23_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_M23_TNR1_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND1_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_M23_TNR1_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND1_M23_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_M23_TNR1_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND1_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_M23_TNR1_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND1_M23_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_M23_TNR1_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_ND1_M23_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f6, _d6);}
#define PE_NRD_HW_M23_TNR1_WR07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7)	\
	{	PE_ND1_M23_QWr07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f7, _d7);}
#define PE_NRD_HW_M23_TNR1_WR09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_ND1_M23_QWr09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f9, _d9);}
#define PE_NRD_HW_M23_TNR1_WR10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_ND1_M23_QWr10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f9, _d9);\
		PE_NRD_HW_M23_TNR1_SET_USER(_r, _f10, _d10);}

#endif

/* tnr lut (tnl) */
#define PE_NRD_HW_M23_TNL_SET_USER32(_r, _d)	\
	{	*((UINT32 *)&(_g_pe_tnl_hw_param_data_m23.reg_user.data->_r)) = (_d);\
		*((UINT32 *)&(_g_pe_tnl_hw_param_data_m23.reg_mask.data->_r)) = 0;}

#define PE_NRD_HW_M23_TNL_WR32(_num, _d1)	\
	{	PE_ND0_M23_QWr(tnr_main_lut_01, _d1);\
		PE_NRD_HW_M23_TNL_SET_USER32(tnr_lut_##_num, _d1);}
/* dnr */
#define PE_NRD_HW_M23_DNR_SET_USER(_r, _f, _d)	\
	{	_g_pe_dnr_hw_param_data_m23.reg_user.data->_r._f = (_d);\
		_g_pe_dnr_hw_param_data_m23.reg_mask.data->_r._f = 0;}

#define PE_NRD_HW_M23_DNR_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_M23_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_M23_DNR_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_M23_DNR_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_M23_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_M23_DNR_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_M23_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_M23_DNR_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_M23_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_M23_DNR_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_DNR0_M23_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f6, _d6);}

#define PE_NRD_HW_M23_NR0_VERI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND0_VERI_M23_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_M23_DNR_SET_USER(_r, _f2, _d2);}


#define PE_NRD_HW_M23_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_NRD_HW_M23_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"_dflt is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"_user is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"_mask is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"_data is null, not ready.\n");\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_M23_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			ret = PE_REG_M23_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_REG_M16_WrAllocatedAddr() error.\n");\
		}\
		if (ret == RET_OK)\
		{\
			PE_DBG_NRD("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_NRD_HW_M23_SET_TNR_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_NRD_HW_M23_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"_dflt is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"_user is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"_mask is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"_data is null, not ready.\n");\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_M23_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			if(_i == PE_NRD_HW_M23_NUM_OF_TNR_CTRL_00_IN_TABLE)\
				continue;\
			ret = PE_REG_M23_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_REG_M16_WrAllocatedAddr() error.\n");\
		}\
		if (ret == RET_OK)\
		{\
			PE_DBG_NRD("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_NRD_HW_M23_SET_DNR_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_NRD_HW_M23_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"_dflt is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"_user is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"_mask is null, not ready.\n");\
		PE_NRD_HW_M23_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"_data is null, not ready.\n");\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_M23_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			if(_i == PE_NRD_HW_M23_NUM_OF_DNR_MAX_CTRL_IN_TABLE)\
				continue;\
			ret = PE_REG_M23_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_REG_M16_WrAllocatedAddr() error.\n");\
		}\
		if (ret == RET_OK)\
		{\
			PE_DBG_NRD("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)
		

#define PE_NRD_HW_M23_PRE_PROC_TNR_REG_TABLE(__base)
#define PE_NRD_HW_M23_PRE_PROC_TNR2ND_REG_TABLE(__base)

/* tnr */
#define PE_NRD_HW_M23_TNR_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnr_hw_param_data_m23.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnr_hw_param_data_m23.nd1_user.addr;\
		UINT32 *_mask = _g_pe_tnr_hw_param_data_m23.nd1_mask.addr;\
		UINT32 *_data = _g_pe_tnr_hw_param_data_m23.nd1_data.addr;\
		PE_NRD_HW_M23_CHECK_CODE(\
		(sizeof(PE_TNR_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "tnr tbl size violation.\n");\
		PE_NRD_HW_M23_PRE_PROC_TNR_REG_TABLE(__base);\
		PE_NRD_HW_M23_SET_TNR_REG_TABLE(__tbl, __base);\
	}while (0)

/* tnr lut (tnl) */
#define PE_NRD_HW_M23_TNL_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnl_hw_param_data_m23.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnl_hw_param_data_m23.reg_user.addr;\
		UINT32 *_mask = _g_pe_tnl_hw_param_data_m23.reg_mask.addr;\
		UINT32 *_data = _g_pe_tnl_hw_param_data_m23.reg_data.addr;\
		PE_NRD_HW_M23_CHECK_CODE(\
		(sizeof(PE_TNL_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "tnl tbl size violation.\n");\
		PE_NRD_HW_M23_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* dnr */
#define PE_NRD_HW_M23_DNR_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_dnr_hw_param_data_m23.reg_dflt.addr;\
		UINT32 *_user = _g_pe_dnr_hw_param_data_m23.reg_user.addr;\
		UINT32 *_mask = _g_pe_dnr_hw_param_data_m23.reg_mask.addr;\
		UINT32 *_data = _g_pe_dnr_hw_param_data_m23.reg_data.addr;\
		PE_NRD_HW_M23_CHECK_CODE(\
		(sizeof(PE_DNR_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "dnr table size violation.\n");\
		PE_NRD_HW_M23_SET_DNR_REG_TABLE(__tbl, __base);\
	}while (0)

/*led dnr */
#define PE_NRD_HW_M23_LED_DNR_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_led_dnr_hw_param_data_m23.reg_dflt.addr;\
		UINT32 *_user = _g_pe_led_dnr_hw_param_data_m23.reg_user.addr;\
		UINT32 *_mask = _g_pe_led_dnr_hw_param_data_m23.reg_mask.addr;\
		UINT32 *_data = _g_pe_led_dnr_hw_param_data_m23.reg_data.addr;\
		PE_NRD_HW_M23_CHECK_CODE(\
		(sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "led dnr table size violation.\n");\
		PE_NRD_HW_M23_SET_REG_TABLE(__tbl, __base);\
	}while (0)

#ifndef PE_HW_M23_BRINGUP
/* dnr psp */
#define PE_NRD_HW_M23_PSP_REG_TABLE(__tbl, __base)		\
			do{\
				UINT32 *_dflt = _g_pe_dnr_psp_hw_param_data_m23.reg_dflt.addr;\
				UINT32 *_user = _g_pe_dnr_psp_hw_param_data_m23.reg_user.addr;\
				UINT32 *_mask = _g_pe_dnr_psp_hw_param_data_m23.reg_mask.addr;\
				UINT32 *_data = _g_pe_dnr_psp_hw_param_data_m23.reg_data.addr;\
				PE_NRD_HW_M23_CHECK_CODE(\
				(sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
				ret=RET_ERROR;break, "dnr psp table size violation.\n");\
				PE_NRD_HW_M23_SET_REG_TABLE(__tbl, __base);\
			}while (0)
#endif

#if 0
/* ifc */
#define PE_NRD_HW_M23_IFC_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_ifc_hw_param_data_m23.reg_dflt.addr;\
		UINT32 *_user = _g_pe_ifc_hw_param_data_m23.reg_user.addr;\
		UINT32 *_mask = _g_pe_ifc_hw_param_data_m23.reg_mask.addr;\
		UINT32 *_data = _g_pe_ifc_hw_param_data_m23.reg_data.addr;\
		PE_NRD_HW_M23_CHECK_CODE(\
		(sizeof(PE_IFC_HW_PARAM_REG_M23_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "ifc tbl size violation.\n");\
		PE_NRD_HW_M23_SET_REG_TABLE(__tbl, __base);\
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


/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static PE_NRD_HW_M23_TNR_FMT PE_NRD_HW_M23_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
// static PE_NRD_HW_M23_TNR2ND_FMT PE_NRD_HW_M23_ConvDispInfoToTnr2ndFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_M23_TNL_FMT PE_NRD_HW_M23_ConvDispInfoToTnlFmt(LX_PE_INF_DISPLAY_T *disp_inf);
//static PE_NRD_HW_M23_IFC_FMT PE_NRD_HW_M23_ConvDispInfoToIfcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_M23_DNR_FMT PE_NRD_HW_M23_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
// static PE_NRD_HW_M23_PSP_FMT PE_NRD_HW_M23_ConvDispInfoToPspFmt(LX_PE_INF_DISPLAY_T *disp_inf);
// static PE_NRD_HW_M23_LED_FMT PE_NRD_HW_M23_ConvDispInfoToLedFmt(LX_PE_INF_DISPLAY_T *disp_inf);
//static int PE_NRD_HW_M23_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);

static int PE_NRD_HW_M23_CreateDataTable(UINT32 index);
static int PE_NRD_HW_M23_SetTnrDefault(PE_NRD_HW_M23_TNR_FMT cur0_tnr_fmt);
static int PE_NRD_HW_M23_SetTnlDefault(PE_NRD_HW_M23_TNL_FMT cur0_tnl_fmt);
static int PE_NRD_HW_M23_SetDnrDefault(PE_NRD_HW_M23_DNR_FMT cur0_dnr_fmt);
//static int PE_NRD_HW_M23_SetPspDefault(PE_NRD_HW_M23_PSP_FMT cur0_psp_fmt);
//static int PE_NRD_HW_M23_SetIfcDefault(PE_NRD_HW_M23_IFC_FMT cur0_ifc_fmt);
//static int PE_NRD_HW_M23_SetLedDefault(PE_NRD_HW_M23_LED_FMT cur0_led_fmt);

static int PE_NRD_HW_M23_SetTnrLbMode(PE_TSK_M23_CFG_T *pCfg);
static int PE_NRD_HW_M23_SetTnrSmoothMode(PE_TSK_M23_CFG_T *pCfg);
//static int PE_NRD_HW_M23_SetTnrScMode(PE_TSK_M23_CFG_T *pCfg);
//static int PE_NRD_HW_M23_SetDnrMaxMode(PE_TSK_M23_CFG_T *pCfg);
//static int PE_NRD_HW_M23_SetBnrMode(PE_TSK_M23_CFG_T *pCfg);
static int PE_NRD_HW_M23_DownloadTnrUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_M23_DownloadTnr2ndUserDb(void *pstParams);
static int PE_NRD_HW_M23_DownloadDnrUserDb(void *pstParams);
static int PE_NRD_HW_M23_DownloadDnrDcntUserDb(void *pstParams);
// static int PE_NRD_HW_M23_DownloadLedDcntUserDb(void *pstParams);
static int PE_NRD_HW_M23_DownloadTnrSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_M23_DownloadTnr2ndSqmCmnUserDb(void *pstParams);
static int PE_NRD_HW_M23_DownloadDnrSqmCmnUserDb(void *pstParams);
static int PE_NRD_HW_M23_DownloadDnrDcntSqmCmnUserDb(void *pstParams);
//static int PE_NRD_HW_M23_DownloadLedDcntSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_M23_SetTnrPBPMode(PE_TSK_M23_CFG_T *pCfg);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static UINT8 _g_nrd_hw_m23_trace=0x0;	//default should be off.
static PE_NRD_HW_M23_SETTINGS_T _g_pe_nrd_hw_m23_info;
static PE_TNR_HW_PARAM_DATA_M23_T _g_pe_tnr_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_TNR2ND_HW_PARAM_DATA_M23_T _g_pe_tnr2nd_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_TNL_HW_PARAM_DATA_M23_T _g_pe_tnl_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_DNR_HW_PARAM_DATA_M23_T _g_pe_dnr_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_LED_DNR_HW_PARAM_DATA_M23_T _g_pe_led_dnr_hw_param_data_m23 = {{NULL}, {NULL}, {NULL}, {NULL}};

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
int PE_NRD_HW_M23_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_REG_M23_HW_OPT_T hw_opt = PE_REG_M23_GetDispOpt();
	do{
		CHECK_KNULL(pstParams);
		_g_pe_nrd_hw_m23_info.use_manual_sc = 1;
		_g_pe_nrd_hw_m23_info.tnr_sc_en_user = 0;
		_g_pe_nrd_hw_m23_info.tnr_sc_en_mask = 0;
		_g_pe_nrd_hw_m23_info.tnr_pv_smooth_en_user = 0;
		_g_pe_nrd_hw_m23_info.tnr_pv_smooth_en_mask = 0;
		_g_pe_nrd_hw_m23_info.dnr_max_en0_user = 0;
		_g_pe_nrd_hw_m23_info.dnr_max_en0_mask = 0;
		_g_pe_nrd_hw_m23_info.bnr_ac_h_en0_user = 0;
		_g_pe_nrd_hw_m23_info.bnr_ac_h_en0_mask = 0;
		_g_pe_nrd_hw_m23_info.cur_tnr_auto_enable = 0;
		_g_pe_nrd_hw_m23_info.cur_tnr_master_gain = 0xc0;	// sync with dflt
		_g_pe_nrd_hw_m23_info.tnr0a_fmt = PE_NRD_M23_TNR_NUM;
		_g_pe_nrd_hw_m23_info.tnl0a_fmt = PE_NRD_M23_TNL_NUM;
		_g_pe_nrd_hw_m23_info.dnr0a_fmt = PE_NRD_M23_DNR_NUM;
		_g_pe_nrd_hw_m23_info.psp0a_fmt = PE_NRD_M23_PSP_NUM;
		//_g_pe_nrd_hw_m23_info.ifc0a_fmt = PE_NRD_M23_IFC_NUM;
		//_g_pre_sc_en = 0xff;
		if(PE_KDRV_VER_M23)
		{
			/* init tnr(nd1,2) */
			ret = PE_NRD_HW_M23_CreateDataTable(PE_NRD_HW_M23_TBL_IDX_TNR);
			PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M23_CreateDataTable() error.\n");
			PE_NRD_HW_M23_TNR_REG_TABLE(tnr_l_hd_i_default_m23,PE_M23_REG_WRITE_BASE);
			/* init tnr lut (nd1,2) */
			ret = PE_NRD_HW_M23_CreateDataTable(PE_NRD_HW_M23_TBL_IDX_TNL);
			PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M23_CreateDataTable() error.\n");
			PE_ND0_M23_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M23_TNL_REG_TABLE(tnr_l_lut_hd_default_m23,PE_M23_REG_WRITE_BASE);
			PE_ND0_M23_QWr(tnr_main_lut_00, 0x00008000);
			/* init dnr(nd1,2) */
			ret = PE_NRD_HW_M23_CreateDataTable(PE_NRD_HW_M23_TBL_IDX_DNR);
			PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M23_CreateDataTable() error.\n");
			PE_NRD_HW_M23_DNR_REG_TABLE(dnr_l_hd_i_default_m23,PE_M23_REG_WRITE_BASE);
			#if 0
			/* init dnr psp  */
			ret = PE_NRD_HW_M23_CreateDataTable(PE_NRD_HW_M23_TBL_IDX_PSP);
			PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M23_CreateDataTable() error.\n");
			PE_NRD_HW_M23_PSP_REG_TABLE(dnrpsp_l_hd_default_m23,PE_M23_REG_WRITE_BASE);
			/* init led dnr(nd1,2) */
			ret = PE_NRD_HW_M23_CreateDataTable(PE_NRD_HW_M23_TBL_IDX_LED);
			PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M23_CreateDataTable() error.\n");
			PE_NRD_HW_M23_LED_DNR_REG_TABLE(led_dnr_l_ud_default_m23,PE_M23_REG_WRITE_BASE);
			printk("[PIK]table addr %x, %x\n",led_dnr_l_ud_default_m23[0].addr,led_dnr_l_ud_default_m23[1].addr);
			#endif
			/* tnr sc enable, threshold */
			PE_CC_PE1_M23_RdFL(pe1_fsw_ctrl_01);
			PE_CC_PE1_M23_Wr01(pe1_fsw_ctrl_01,tnr_sc_measure_en, _g_pe_nrd_hw_m23_info.use_manual_sc? 1:0);
			PE_CC_PE1_M23_Wr01(pe1_fsw_ctrl_01,tnr_sc_measure_th, 0x170);//368
			PE_CC_PE1_M23_WrFL(pe1_fsw_ctrl_01);

			if (hw_opt.external_chip ==0) //60Hz model
			{
				_g_pe_nrd_hw_m23_info.is_external_chip = 0;
			}
			else //8k model
			{
				_g_pe_nrd_hw_m23_info.is_external_chip = 1;
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do\n");
		}
	}while(0);
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
int PE_NRD_HW_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_nrd_hw_m23_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(NRD)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(NRD)),\
			pstParams->print_lvl,_g_nrd_hw_m23_trace,pstParams->bypass);
	}while(0);
	return ret;
}

/**
 * create data table
 *
 * @param   index [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_NRD_HW_M23_TBL_INDX
 * @author
 */
static int PE_NRD_HW_M23_CreateDataTable(UINT32 index)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_TNR_HW_PARAM_DATA_M23_T *p_tnr_m23 = &_g_pe_tnr_hw_param_data_m23;
	PE_TNL_HW_PARAM_DATA_M23_T *p_tnl_m23 = &_g_pe_tnl_hw_param_data_m23;
	PE_DNR_HW_PARAM_DATA_M23_T *p_dnr_m23 = &_g_pe_dnr_hw_param_data_m23;
	//PE_DNR_PSP_HW_PARAM_DATA_M23_T *p_psp_m23 = &_g_pe_dnr_psp_hw_param_data_m23;
	//PE_IFC_HW_PARAM_DATA_M23_T *p_ifc_m23 = &_g_pe_ifc_hw_param_data_m23;
	PE_LED_DNR_HW_PARAM_DATA_M23_T *p_led_m23 = &_g_pe_led_dnr_hw_param_data_m23;

	PE_NRD_HW_M23_CHECK_CODE(index>=PE_NRD_HW_M23_TBL_IDX_NUM, return RET_ERROR, \
		"index(%d) invalid.\n", index);

	if (index == PE_NRD_HW_M23_TBL_IDX_TNR)
	{
		/* create dflt table */
		if (p_tnr_m23->reg_dflt.addr == NULL)
		{
			p_tnr_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_tnr_m23->nd1_user.addr == NULL)
		{
			p_tnr_m23->nd1_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_M23_T));
			memset((p_tnr_m23->nd1_user.addr), 0, sizeof(PE_TNR_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_tnr_m23->nd1_mask.addr == NULL)
		{
			p_tnr_m23->nd1_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_M23_T));
			memset((p_tnr_m23->nd1_mask.addr), -1, sizeof(PE_TNR_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnr_m23->nd1_data.addr == NULL)
		{
			p_tnr_m23->nd1_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_M23_T));
			memset((p_tnr_m23->nd1_data.addr), 0, sizeof(PE_TNR_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_tnr_m23->reg_dflt.addr != NULL && p_tnr_m23->nd1_user.addr != NULL && \
			p_tnr_m23->nd1_mask.addr != NULL && p_tnr_m23->nd1_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M23_TBL_IDX_TO_STR(index), \
				(p_tnr_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnr_m23->nd1_user.addr == NULL)? "x":"o", \
				(p_tnr_m23->nd1_mask.addr == NULL)? "x":"o", \
				(p_tnr_m23->nd1_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_NRD_HW_M23_TBL_IDX_TNL)
	{
		/* create dflt table */
		if (p_tnl_m23->reg_dflt.addr == NULL)
		{
			p_tnl_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_tnl_m23->reg_user.addr == NULL)
		{
			p_tnl_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_M23_T));
			memset((p_tnl_m23->reg_user.addr), 0, sizeof(PE_TNL_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_tnl_m23->reg_mask.addr == NULL)
		{
			p_tnl_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_M23_T));
			memset((p_tnl_m23->reg_mask.addr), -1, sizeof(PE_TNL_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnl_m23->reg_data.addr == NULL)
		{
			p_tnl_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_M23_T));
			memset((p_tnl_m23->reg_data.addr), 0, sizeof(PE_TNL_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_tnl_m23->reg_dflt.addr != NULL && p_tnl_m23->reg_user.addr != NULL && \
			p_tnl_m23->reg_mask.addr != NULL && p_tnl_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M23_TBL_IDX_TO_STR(index), \
				(p_tnl_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnl_m23->reg_user.addr == NULL)? "x":"o", \
				(p_tnl_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_tnl_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_NRD_HW_M23_TBL_IDX_DNR)
	{
		/* create dflt table */
		if (p_dnr_m23->reg_dflt.addr == NULL)
		{
			p_dnr_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_dnr_m23->reg_user.addr == NULL)
		{
			p_dnr_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_M23_T));
			memset((p_dnr_m23->reg_user.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_dnr_m23->reg_mask.addr == NULL)
		{
			p_dnr_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_M23_T));
			memset((p_dnr_m23->reg_mask.addr), -1, sizeof(PE_DNR_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_dnr_m23->reg_data.addr == NULL)
		{
			p_dnr_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_M23_T));
			memset((p_dnr_m23->reg_data.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_dnr_m23->reg_dflt.addr != NULL && p_dnr_m23->reg_user.addr != NULL && \
			p_dnr_m23->reg_mask.addr != NULL && p_dnr_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M23_TBL_IDX_TO_STR(index), \
				(p_dnr_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_dnr_m23->reg_user.addr == NULL)? "x":"o", \
				(p_dnr_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_dnr_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	#if 0
	else if (index == PE_NRD_HW_M23_TBL_IDX_PSP)
	{
		/* create dflt table */
		if (p_psp_m23->reg_dflt.addr == NULL)
		{
			p_psp_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_psp_m23->reg_user.addr == NULL)
		{
			p_psp_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T));
			memset((p_psp_m23->reg_user.addr), 0, sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_psp_m23->reg_mask.addr == NULL)
		{
			p_psp_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T));
			memset((p_psp_m23->reg_mask.addr), -1, sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_psp_m23->reg_data.addr == NULL)
		{
			p_psp_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T));
			memset((p_psp_m23->reg_data.addr), 0, sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_psp_m23->reg_dflt.addr != NULL && p_psp_m23->reg_user.addr != NULL && \
			p_psp_m23->reg_mask.addr != NULL && p_psp_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M23_TBL_IDX_TO_STR(index), \
				(p_psp_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_psp_m23->reg_user.addr == NULL)? "x":"o", \
				(p_psp_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_psp_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_NRD_HW_M23_TBL_IDX_IFC)
	{
		/* create dflt table */
		if (p_ifc_m23->reg_dflt.addr == NULL)
		{
			p_ifc_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IFC_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_ifc_m23->reg_user.addr == NULL)
		{
			p_ifc_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IFC_HW_PARAM_REG_M23_T));
			memset((p_ifc_m23->reg_user.addr), 0, sizeof(PE_IFC_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_ifc_m23->reg_mask.addr == NULL)
		{
			p_ifc_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IFC_HW_PARAM_REG_M23_T));
			memset((p_ifc_m23->reg_mask.addr), -1, sizeof(PE_IFC_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_ifc_m23->reg_data.addr == NULL)
		{
			p_ifc_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_IFC_HW_PARAM_REG_M23_T));
			memset((p_ifc_m23->reg_data.addr), 0, sizeof(PE_IFC_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_ifc_m23->reg_dflt.addr != NULL && p_ifc_m23->reg_user.addr != NULL && \
			p_ifc_m23->reg_mask.addr != NULL && p_ifc_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M23_TBL_IDX_TO_STR(index), \
				(p_ifc_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_ifc_m23->reg_user.addr == NULL)? "x":"o", \
				(p_ifc_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_ifc_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	#endif
	else if (index == PE_NRD_HW_M23_TBL_IDX_LED)
	{
		/* create dflt table */
		if (p_led_m23->reg_dflt.addr == NULL)
		{
			p_led_m23->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T));
		}
		/* create user table */
		if (p_led_m23->reg_user.addr == NULL)
		{
			p_led_m23->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T));
			memset((p_led_m23->reg_user.addr), 0, sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* create mask table */
		if (p_led_m23->reg_mask.addr == NULL)
		{
			p_led_m23->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T));
			memset((p_led_m23->reg_mask.addr), -1, sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T));// 0xffffffff
		}
		/* create data table */
		if (p_led_m23->reg_data.addr == NULL)
		{
			p_led_m23->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T));
			memset((p_led_m23->reg_data.addr), 0, sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T));	// 0x0
		}
		/* report result */
		if (p_led_m23->reg_dflt.addr != NULL && p_led_m23->reg_user.addr != NULL && \
			p_led_m23->reg_mask.addr != NULL && p_led_m23->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_M23_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_M23_TBL_IDX_TO_STR(index), \
				(p_led_m23->reg_dflt.addr == NULL)? "x":"o", \
				(p_led_m23->reg_user.addr == NULL)? "x":"o", \
				(p_led_m23->reg_mask.addr == NULL)? "x":"o", \
				(p_led_m23->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else
	{
		PE_DBG_NRD("nothing to do\n");	ret = RET_OK;
	}
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set nr default setting(for M23X)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_INF_DISPLAY_T cur0_inf;
	LX_PE_INF_DISPLAY_T cur1_inf;
	PE_NRD_HW_M23_TNR_FMT cur0_tnr_fmt;
	PE_NRD_HW_M23_TNL_FMT cur0_tnl_fmt;
	PE_NRD_HW_M23_DNR_FMT cur0_dnr_fmt;
	// PE_NRD_HW_M23_PSP_FMT cur0_psp_fmt;
	//PE_NRD_HW_M23_IFC_FMT cur0_ifc_fmt;
	// PE_NRD_HW_M23_LED_FMT cur0_led_fmt;
	__attribute__((unused)) PE_NRD_HW_M23_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m23_info;
	PE_TNR_HW_PARAM_REG_M23_T *p_tnr_dflt = _g_pe_tnr_hw_param_data_m23.reg_dflt.data;
	PE_DNR_HW_PARAM_REG_M23_T *p_dnr_dflt = _g_pe_dnr_hw_param_data_m23.reg_dflt.data;
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *pp;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_M23_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
		ret = PE_INF_M23_GetCurDispInfSettings(LX_PE_WIN_1, &cur1_inf);
		PE_NRD_HW_M23_CHECK_CODE(ret,break,"PE_INF_M23_GetCurInfSettings() error.\n");
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			/* tnr lut (tnl) */
			cur0_tnl_fmt = PE_NRD_HW_M23_ConvDispInfoToTnlFmt(&cur0_inf);
			PE_NRD_HW_M23_DBG_PRINT_TNL_FMT_STATE(pInfo->tnl0a_fmt,cur0_tnl_fmt);
			if(pInfo->tnl0a_fmt!=cur0_tnl_fmt)
			{
				ret = PE_NRD_HW_M23_SetTnlDefault(cur0_tnl_fmt);
				PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M23_SetTnlDefault() error.\n");
				pInfo->tnl0a_fmt=cur0_tnl_fmt;
			}
			/* tnr(nd1,2) */
			cur0_tnr_fmt = PE_NRD_HW_M23_ConvDispInfoToTnrFmt(&cur0_inf);
			PE_NRD_HW_M23_DBG_PRINT_TNR_FMT_STATE(pInfo->tnr0a_fmt,cur0_tnr_fmt);
			if(pInfo->tnr0a_fmt!=cur0_tnr_fmt)
			{
				ret = PE_NRD_HW_M23_SetTnrDefault(cur0_tnr_fmt);
				PE_NRD_HW_M23_CHECK_CODE(ret, break, \
					"PE_NRD_HW_M23_SetTnrDefault() error.\n");
					pInfo->tnr0a_fmt=cur0_tnr_fmt;
				/* to avoid racing ctrl fw<->driver, use dummy register */
				PE_ND0_M23_RdFL(nd_fsw_ctrl_03);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_tnr_en					  ,p_tnr_dflt->tnr_ctrl_00.reg_tnr_en			);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_nlvl_input_sel			  ,p_tnr_dflt->tnr_ctrl_00.reg_nlvl_input_sel	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_sc_detect_hres			  ,p_tnr_dflt->tnr_ctrl_00.reg_sc_detect_hres	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_clc_nt_pal				  ,p_tnr_dflt->tnr_ctrl_00.reg_clc_nt_pal		);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_clc_mem_wr_mode			  ,p_tnr_dflt->tnr_ctrl_00.reg_clc_mem_wr_mode	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_res				  ,p_tnr_dflt->tnr_ctrl_00.reg_sad_8x3_res		);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_iir_en			  ,p_tnr_dflt->tnr_ctrl_00.reg_sad_8x3_iir_en	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_chroma_en		  ,p_tnr_dflt->tnr_ctrl_00.reg_sad_8x3_chroma_en);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_minfo_sw 				  ,p_tnr_dflt->tnr_ctrl_00.reg_minfo_sw 		);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_minfo_mode10 			  ,p_tnr_dflt->tnr_ctrl_00.reg_minfo_mode10 	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_minfo_flt				  ,p_tnr_dflt->tnr_ctrl_00.reg_minfo_flt		);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_tnr_single_en			  ,p_tnr_dflt->tnr_ctrl_00.reg_tnr_single_en	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_decon_blend_en			  ,p_tnr_dflt->tnr_ctrl_00.reg_decon_blend_en	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_minfo_mode32 			  ,p_tnr_dflt->tnr_ctrl_00.reg_minfo_mode32 	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_minfo_mode74 			  ,p_tnr_dflt->tnr_ctrl_00.reg_minfo_mode74 	);
				PE_ND0_M23_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_iir_alpha		  ,p_tnr_dflt->tnr_ctrl_00.reg_sad_8x3_iir_alpha);
				PE_ND0_M23_WrFL(nd_fsw_ctrl_03);
			}
			/* dnr(dnr1,2) */
			cur0_dnr_fmt = PE_NRD_HW_M23_ConvDispInfoToDnrFmt(&cur0_inf);
			PE_NRD_HW_M23_DBG_PRINT_DNR_FMT_STATE(pInfo->dnr0a_fmt,cur0_dnr_fmt);
			if(pInfo->dnr0a_fmt!=cur0_dnr_fmt)
			{
				ret = PE_NRD_HW_M23_SetDnrDefault(cur0_dnr_fmt);
				PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M23_SetDnrDefault() error.\n");
				pInfo->dnr0a_fmt=cur0_dnr_fmt;
				/* to avoid racing ctrl fw<->driver, use dummy register */
				PE_SRE_VERI_M23_RdFL(sre_sys_veri_0);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_dnr_max_enable		  ,p_dnr_dflt->dnr_max_ctrl.reg_dnr_max_enable	);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_ifc_max_enable		  ,p_dnr_dflt->dnr_max_ctrl.reg_ifc_max_enable	);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_dnr_ifc_sel		  ,p_dnr_dflt->dnr_max_ctrl.reg_dnr_ifc_sel		);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_decon_max_sum_sel	  ,p_dnr_dflt->dnr_max_ctrl.reg_decon_max_sum_sel);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_decon_ori_sel		  ,p_dnr_dflt->dnr_max_ctrl.reg_decon_ori_sel	);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_decon_max_enable 	  ,p_dnr_dflt->dnr_max_ctrl.reg_decon_max_enable );
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_max_decon_dbg_en 	  ,p_dnr_dflt->dnr_max_ctrl.reg_max_decon_dbg_en );
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_half_rate_cg_n		  ,p_dnr_dflt->dnr_max_ctrl.reg_half_rate_cg_n	);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_max_dbg_en			  ,p_dnr_dflt->dnr_max_ctrl.reg_max_dbg_en		);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_dnr_motion_sel		  ,p_dnr_dflt->dnr_max_ctrl.reg_dnr_motion_sel	);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_tnr_decon_en 		  ,p_dnr_dflt->dnr_max_ctrl.reg_tnr_decon_en 	);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_face_obj_sel 		  ,p_dnr_dflt->dnr_max_ctrl.reg_face_obj_sel 	);
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_win_en		          ,p_dnr_dflt->dnr_max_ctrl.reg_win_en		    );
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_bdr_en		          ,p_dnr_dflt->dnr_max_ctrl.reg_bdr_en		    );
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_win_inout	          ,p_dnr_dflt->dnr_max_ctrl.reg_win_inout	    );
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_ipc_motion_en        ,p_dnr_dflt->dnr_max_ctrl.reg_ipc_motion_en    );
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_motion_bit_ctrl      ,p_dnr_dflt->dnr_max_ctrl.reg_motion_bit_ctrl  );
				PE_SRE_VERI_M23_Wr01(sre_sys_veri_0, reg_delta_ifc_th         ,p_dnr_dflt->dnr_max_ctrl.reg_delta_ifc_th     );
				PE_SRE_VERI_M23_WrFL(sre_sys_veri_0);
			}
			#if 0
			/* 20180111 additional setting for color blur issue TVPM-5600 */
			if((cur0_inf.in_v_size == 720 && cur0_inf.scan_type==LX_PE_SCAN_PROGRESS) ||\
				(cur0_inf.in_v_size == 1080 && cur0_inf.scan_type==LX_PE_SCAN_INTERLACE))
			{
				PE_DNR1_M23_QWr01(c_pre_blur_ctrl_0, pre_121_blur_en, 0x0);
			}
			else
			{
				PE_DNR1_M23_QWr01(c_pre_blur_ctrl_0, pre_121_blur_en, 0x1);
			}
			/* led dnr */
			cur0_led_fmt = PE_NRD_HW_M23_ConvDispInfoToLedFmt(&cur0_inf);
			PE_NRD_HW_M23_DBG_PRINT_LED_FMT_STATE(pInfo->led0a_fmt,cur0_led_fmt);
			if(pInfo->led0a_fmt!=cur0_led_fmt)
			{
				ret = PE_NRD_HW_M23_SetLedDefault(cur0_led_fmt);
				PE_NRD_HW_M23_CHECK_CODE(ret, break, \
				"PE_NRD_HW_M23_SetLedDefault() error.\n");
				pInfo->led0a_fmt=cur0_led_fmt;
			}
			#endif
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set tnr default setting(for M23X)
 *
 * @param   cur0_tnr_fmt [in] PE_NRD_HW_M23_TNR_FMT
 * @return
 * @see
 * @author
 */
static int PE_NRD_HW_M23_SetTnrDefault(PE_NRD_HW_M23_TNR_FMT cur0_tnr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	switch(cur0_tnr_fmt)
	{
		case PE_NRD_M23_TNR_SD:
			PE_NRD_HW_M23_TNR_REG_TABLE(tnr_l_sd_default_m23,   PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_TNR_HD_I:
			PE_NRD_HW_M23_TNR_REG_TABLE(tnr_l_hd_i_default_m23,   PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_TNR_HD_P:
			PE_NRD_HW_M23_TNR_REG_TABLE(tnr_l_hd_p_default_m23,   PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_TNR_UD:
			PE_NRD_HW_M23_TNR_REG_TABLE(tnr_l_ud_default_m23,   PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_TNR_8K:
			PE_NRD_HW_M23_TNR_REG_TABLE(tnr_l_8k_default_m23,   PE_M23_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
static int PE_NRD_HW_M23_SetTnlDefault(PE_NRD_HW_M23_TNL_FMT cur0_tnl_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	switch(cur0_tnl_fmt)
	{
		case PE_NRD_M23_TNL_HD:
			PE_ND0_M23_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M23_TNL_REG_TABLE(tnr_l_lut_hd_default_m23,   PE_M23_REG_WRITE_BASE);
			PE_ND0_M23_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_M23_TNL_SD:
			PE_ND0_M23_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M23_TNL_REG_TABLE(tnr_l_lut_sd_default_m23,   PE_M23_REG_WRITE_BASE);
			PE_ND0_M23_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_M23_TNL_UHD:
			PE_ND0_M23_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_M23_TNL_REG_TABLE(tnr_l_lut_ud_default_m23,   PE_M23_REG_WRITE_BASE);
			PE_ND0_M23_QWr(tnr_main_lut_00, 0x00008000);
			break;
		default:
			break;
	}
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
static int PE_NRD_HW_M23_SetDnrDefault(PE_NRD_HW_M23_DNR_FMT cur0_dnr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	switch(cur0_dnr_fmt)
	{
		case PE_NRD_M23_DNR_SD:
			PE_NRD_HW_M23_DNR_REG_TABLE(dnr_l_sd_default_m23,	 PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_DNR_HD_I:
			PE_NRD_HW_M23_DNR_REG_TABLE(dnr_l_hd_i_default_m23,	 PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_DNR_HD_P:
			PE_NRD_HW_M23_DNR_REG_TABLE(dnr_l_hd_p_default_m23,	 PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_DNR_UD:
			PE_NRD_HW_M23_DNR_REG_TABLE(dnr_l_ud_default_m23,	 PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_DNR_SD_DTV:
			PE_NRD_HW_M23_DNR_REG_TABLE(dnr_l_dtv_sd_default_m23,	 PE_M23_REG_WRITE_BASE);
			break;
		case PE_NRD_M23_DNR_8K:
			PE_NRD_HW_M23_DNR_REG_TABLE(dnr_l_8k_default_m23,	 PE_M23_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}


/**
 * get tnr fmt from display info.(for M23X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_M23_TNR_FMT
 * @see
 * @author
 */
static PE_NRD_HW_M23_TNR_FMT PE_NRD_HW_M23_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_M23_TNR_FMT tnr_fmt = PE_NRD_M23_TNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			tnr_fmt = PE_NRD_M23_TNR_SD;
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_NRD_M23_TNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					tnr_fmt = PE_NRD_M23_TNR_HD_I;
				else
					tnr_fmt = PE_NRD_M23_TNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				if(disp_inf->sub_mode == 2)//pbp mode
					tnr_fmt = PE_NRD_M23_TNR_HD_P;
				else
					tnr_fmt = PE_NRD_M23_TNR_UD;
			}
			else
			{
				if(disp_inf->sub_mode == 2)//pbp mode
					tnr_fmt = PE_NRD_M23_TNR_HD_P;
				else
					tnr_fmt = PE_NRD_M23_TNR_8K;
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_NRD_M23_TNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					tnr_fmt = PE_NRD_M23_TNR_HD_I;
				else
					tnr_fmt = PE_NRD_M23_TNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				if(disp_inf->sub_mode == 2)//pbp mode
					tnr_fmt = PE_NRD_M23_TNR_HD_P;
				else
					tnr_fmt = PE_NRD_M23_TNR_UD;
			}
			else
			{
				if(disp_inf->sub_mode == 2)//pbp mode
					tnr_fmt = PE_NRD_M23_TNR_HD_P;
				else
					tnr_fmt = PE_NRD_M23_TNR_8K;
			}
			break;
	}
	return tnr_fmt;
}

/**
 * get tnr lut (tnl) fmt from display info.(for M23X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_M23_TNL_FMT
 * @see
 * @author
 */
static PE_NRD_HW_M23_TNL_FMT PE_NRD_HW_M23_ConvDispInfoToTnlFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_M23_TNL_FMT tnl_fmt = PE_NRD_M23_TNL_NUM;
	/* skip drv tnr ctrl, if fw tnr on. */
	if (PE_CMN_HW_M23_GetDbInfo(PE_CMN_HW_M23_DB_INF_MD0_TNR_FW_EN, 0))
	{
		tnl_fmt = PE_NRD_M23_TNL_NUM;	//NA
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
					tnl_fmt = PE_NRD_M23_TNL_SD;
				}
				break;
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					tnl_fmt = PE_NRD_M23_TNL_SD;
				}
				else 
				{
					tnl_fmt = PE_NRD_M23_TNL_HD;
				}
				break;
		}
	}
	return tnl_fmt;
}
/**
 * get dnr fmt from display info.(for M23X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_M23_DNR_FMT
 * @see
 * @author
 */
static PE_NRD_HW_M23_DNR_FMT PE_NRD_HW_M23_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_M23_DNR_FMT dnr_fmt = PE_NRD_M23_DNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			{
				dnr_fmt = PE_NRD_M23_DNR_SD;
			}
			break;
		case LX_PE_SRC_DTV:
			{
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					dnr_fmt = PE_NRD_M23_DNR_SD_DTV;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						dnr_fmt = PE_NRD_M23_DNR_HD_I;
					else
						dnr_fmt = PE_NRD_M23_DNR_HD_P;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
				{
					if(disp_inf->sub_mode == 2)//pbp mode
						dnr_fmt = PE_NRD_M23_DNR_HD_P;
					else
						dnr_fmt = PE_NRD_M23_DNR_UD;
				}
				else
				{
					dnr_fmt = PE_NRD_M23_DNR_8K;
				}
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				dnr_fmt = PE_NRD_M23_DNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					dnr_fmt = PE_NRD_M23_DNR_HD_I;
				else
					dnr_fmt = PE_NRD_M23_DNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				if(disp_inf->sub_mode == 2)//pbp mode
					dnr_fmt = PE_NRD_M23_DNR_HD_P;
				else
					dnr_fmt = PE_NRD_M23_DNR_UD;
			}
			else
			{
				dnr_fmt = PE_NRD_M23_DNR_8K;
			}
			break;
	}
	return dnr_fmt;
}
#if 0
/**
 * get led fmt from display info.(for M23X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_M23_LED_FMT
 * @see
 * @author
 */
static PE_NRD_HW_M23_LED_FMT PE_NRD_HW_M23_ConvDispInfoToLedFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_M23_LED_FMT led_fmt = PE_NRD_M23_LED_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				led_fmt = PE_NRD_M23_LED_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				led_fmt = PE_NRD_M23_LED_HD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				led_fmt = PE_NRD_M23_LED_UD;
			}
			else
			{
				led_fmt = PE_NRD_M23_LED_8K;
			}
			break;
	}
	return led_fmt;
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
int PE_NRD_HW_M23_RdDefault(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 param_size=0, table_size=0, is_valid=0;
	UINT32 rd_cnt=0;
	PE_REG_PARAM_T param;
	PE_NRD_HW_M23_SETTINGS_T *pInfo=&_g_pe_nrd_hw_m23_info;

#define PE_NRD_M23_NO_PRINT			0
#define PE_NRD_M23_RD_N_HEX_PRINT	1
#define PE_NRD_M23_HEX_PRINT_ONLY	2
#define PE_NRD_M23_PRINT_START		"START_OF_PRINT"
#define PE_NRD_M23_PRINT_END		"END_OF_PRINT"
#define PE_NRD_M23_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_NRD_M23_PRINT_RESRV		"RESERVED"
#define PE_NRD_M23_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, "   [0x%02x] %s\n", (_item), #_item);_action;break
#define PE_NRD_M23_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break
#define PE_NRD_M23_DFLT_SPRINT(_action, _buf, fmt, args...)		\
	default:snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		
		if (PE_KDRV_VER_M23)
		{
			__attribute__((unused)) UINT32 *p_tnr1b_dflt = _g_pe_tnr_hw_param_data_m23.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnr1b_user = _g_pe_tnr_hw_param_data_m23.nd1_user.addr;
			__attribute__((unused)) UINT32 *p_tnr1b_mask = _g_pe_tnr_hw_param_data_m23.nd1_mask.addr;
			__attribute__((unused)) UINT32 *p_tnr1b_data = _g_pe_tnr_hw_param_data_m23.nd1_data.addr;
			__attribute__((unused)) UINT32 *p_tnr2b_dflt = _g_pe_tnr2nd_hw_param_data_m23.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnr2b_user = _g_pe_tnr2nd_hw_param_data_m23.nd1_user.addr;
			__attribute__((unused)) UINT32 *p_tnr2b_mask = _g_pe_tnr2nd_hw_param_data_m23.nd1_mask.addr;
			__attribute__((unused)) UINT32 *p_tnr2b_data = _g_pe_tnr2nd_hw_param_data_m23.nd1_data.addr;
			__attribute__((unused)) UINT32 *p_dnr1b_dflt = _g_pe_dnr_hw_param_data_m23.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_dnr1b_user = _g_pe_dnr_hw_param_data_m23.reg_user.addr;
			__attribute__((unused)) UINT32 *p_dnr1b_mask = _g_pe_dnr_hw_param_data_m23.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_dnr1b_data = _g_pe_dnr_hw_param_data_m23.reg_data.addr;
			#if 0
			UINT32 *p_psp1b_dflt = _g_pe_dnr_psp_hw_param_data_m23.reg_dflt.addr;
			UINT32 *p_psp1b_user = _g_pe_dnr_psp_hw_param_data_m23.reg_user.addr;
			UINT32 *p_psp1b_mask = _g_pe_dnr_psp_hw_param_data_m23.reg_mask.addr;
			UINT32 *p_psp1b_data = _g_pe_dnr_psp_hw_param_data_m23.reg_data.addr;
			UINT32 *p_ifc1b_dflt = _g_pe_ifc_hw_param_data_m23.reg_dflt.addr;
			UINT32 *p_ifc1b_user = _g_pe_ifc_hw_param_data_m23.reg_user.addr;
			UINT32 *p_ifc1b_mask = _g_pe_ifc_hw_param_data_m23.reg_mask.addr;
			UINT32 *p_ifc1b_data = _g_pe_ifc_hw_param_data_m23.reg_data.addr;
			#endif
			__attribute__((unused)) UINT32 *p_tnl1b_dflt = _g_pe_tnl_hw_param_data_m23.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnl1b_user = _g_pe_tnl_hw_param_data_m23.reg_user.addr;
			__attribute__((unused)) UINT32 *p_tnl1b_mask = _g_pe_tnl_hw_param_data_m23.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_tnl1b_data = _g_pe_tnl_hw_param_data_m23.reg_data.addr;
			__attribute__((unused)) UINT32 *p_led1b_dflt = _g_pe_led_dnr_hw_param_data_m23.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_led1b_user = _g_pe_led_dnr_hw_param_data_m23.reg_user.addr;
			__attribute__((unused)) UINT32 *p_led1b_mask = _g_pe_led_dnr_hw_param_data_m23.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_led1b_data = _g_pe_led_dnr_hw_param_data_m23.reg_data.addr;
			CHECK_KNULL(p_tnr1b_dflt);
			CHECK_KNULL(p_tnr1b_user);
			CHECK_KNULL(p_tnr1b_mask);
			CHECK_KNULL(p_tnr1b_data);
			CHECK_KNULL(p_dnr1b_dflt);
			CHECK_KNULL(p_dnr1b_user);
			CHECK_KNULL(p_dnr1b_mask);
			CHECK_KNULL(p_dnr1b_data);
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]>=PE_NRD_HW_M23_RD_MENU_MAX)
			{
				snprintf(buffer, PE_TRACE_STR_SIZE, "%s", PE_NRD_M23_PRINT_EXIT);
				rd_cnt=0;
			}
			else if (pstParams->data[0]==PE_NRD_HW_M23_RD_MENU_DISP)
			{
				switch (rd_cnt)
				{
					PE_NRD_M23_CASE_SPRINT( 0, rd_cnt++, buffer, PE_NRD_M23_PRINT_START);
					PE_NRD_M23_CASE_SPRINT( 1, rd_cnt++, buffer, "   ** current default **\n");
					PE_NRD_M23_CASE_SPRINT( 2, rd_cnt++, buffer, \
						"   tnr0a_fmt : %s\n", PE_NRD_HW_M23_TNR_FMT_TO_STR(pInfo->tnr0a_fmt));
					PE_NRD_M23_CASE_SPRINT( 3, rd_cnt++, buffer, \
						"   tnr1a_fmt : %s\n", PE_NRD_HW_M23_TNR2ND_FMT_TO_STR(pInfo->tnr1a_fmt));
					PE_NRD_M23_CASE_SPRINT( 4, rd_cnt++, buffer, \
						"   dnr0a_fmt : %s\n", PE_NRD_HW_M23_DNR_FMT_TO_STR(pInfo->dnr0a_fmt));
					PE_NRD_M23_CASE_SPRINT( 5, rd_cnt++, buffer, \
						"   psp0a_fmt : %s\n", PE_NRD_HW_M23_PSP_FMT_TO_STR(pInfo->psp0a_fmt));
					#if 0
					PE_NRD_M23_CASE_SPRINT( 6, rd_cnt++, buffer, \
						"   ifc0a_fmt : %s\n", PE_NRD_HW_M23_IFC_FMT_TO_STR(pInfo->ifc0a_fmt));
					#else
					PE_NRD_M23_CASE_SPRINT(6, rd_cnt++, buffer, PE_NRD_M23_PRINT_RESRV);
					#endif
					PE_NRD_M23_CASE_SPRINT( 7, rd_cnt++, buffer, \
						"   tnl0a_fmt : %s\n", PE_NRD_HW_M23_TNL_FMT_TO_STR(pInfo->tnl0a_fmt));
					PE_NRD_M23_CASE_SPRINT( 8, rd_cnt++, buffer, \
						"   led0a_fmt : %s\n", PE_NRD_HW_M23_LED_FMT_TO_STR(pInfo->led0a_fmt));
					PE_NRD_M23_CASE_SPRINT( 9, rd_cnt++, buffer, PE_NRD_M23_PRINT_RESRV);
					PE_NRD_M23_CASE_SPRINT(10, rd_cnt++, buffer, "   *********************\n");
					PE_NRD_M23_CASE_PRMENU(11, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR1_DISP);
					PE_NRD_M23_CASE_PRMENU(12, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR1_DFLT);
					PE_NRD_M23_CASE_PRMENU(13, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR1_USER);
					PE_NRD_M23_CASE_PRMENU(14, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR1_MASK);
					PE_NRD_M23_CASE_PRMENU(15, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR1_DATA);
					PE_NRD_M23_CASE_PRMENU(16, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR2_DISP);
					PE_NRD_M23_CASE_PRMENU(17, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR2_DFLT);
					PE_NRD_M23_CASE_PRMENU(18, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR2_USER);
					PE_NRD_M23_CASE_PRMENU(19, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR2_MASK);
					PE_NRD_M23_CASE_PRMENU(20, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR2_DATA);
					PE_NRD_M23_CASE_PRMENU(21, rd_cnt++, buffer, PE_NRD_HW_M23_RD_DNR1_DISP);
					PE_NRD_M23_CASE_PRMENU(22, rd_cnt++, buffer, PE_NRD_HW_M23_RD_DNR1_DFLT);
					PE_NRD_M23_CASE_PRMENU(23, rd_cnt++, buffer, PE_NRD_HW_M23_RD_DNR1_USER);
					PE_NRD_M23_CASE_PRMENU(24, rd_cnt++, buffer, PE_NRD_HW_M23_RD_DNR1_MASK);
					PE_NRD_M23_CASE_PRMENU(25, rd_cnt++, buffer, PE_NRD_HW_M23_RD_DNR1_DATA);
					PE_NRD_M23_CASE_PRMENU(26, rd_cnt++, buffer, PE_NRD_HW_M23_RD_PSP1_DISP);
					PE_NRD_M23_CASE_PRMENU(27, rd_cnt++, buffer, PE_NRD_HW_M23_RD_PSP1_DFLT);
					PE_NRD_M23_CASE_PRMENU(28, rd_cnt++, buffer, PE_NRD_HW_M23_RD_PSP1_USER);
					PE_NRD_M23_CASE_PRMENU(29, rd_cnt++, buffer, PE_NRD_HW_M23_RD_PSP1_MASK);
					PE_NRD_M23_CASE_PRMENU(30, rd_cnt++, buffer, PE_NRD_HW_M23_RD_PSP1_DATA);
					PE_NRD_M23_CASE_PRMENU(31, rd_cnt++, buffer, PE_NRD_HW_M23_RD_LED1_DISP);
					PE_NRD_M23_CASE_PRMENU(32, rd_cnt++, buffer, PE_NRD_HW_M23_RD_LED1_DFLT);
					PE_NRD_M23_CASE_PRMENU(33, rd_cnt++, buffer, PE_NRD_HW_M23_RD_LED1_USER);
					PE_NRD_M23_CASE_PRMENU(34, rd_cnt++, buffer, PE_NRD_HW_M23_RD_LED1_MASK);
					PE_NRD_M23_CASE_PRMENU(35, rd_cnt++, buffer, PE_NRD_HW_M23_RD_LED1_DATA);
					PE_NRD_M23_CASE_SPRINT(36, rd_cnt++, buffer, "   *********************\n");
					PE_NRD_M23_CASE_PRMENU(37, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNR1_MLUT);
					PE_NRD_M23_CASE_PRMENU(38, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNL1_DFLT);
					PE_NRD_M23_CASE_PRMENU(39, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNL1_USER);
					PE_NRD_M23_CASE_PRMENU(40, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNL1_MASK);
					PE_NRD_M23_CASE_PRMENU(41, rd_cnt++, buffer, PE_NRD_HW_M23_RD_TNL1_DATA);
					PE_NRD_M23_CASE_SPRINT(42, rd_cnt++, buffer, PE_NRD_M23_PRINT_RESRV);
					PE_NRD_M23_CASE_SPRINT(43, rd_cnt++, buffer, PE_NRD_M23_PRINT_RESRV);
					PE_NRD_M23_CASE_SPRINT(44, rd_cnt++, buffer, PE_NRD_M23_PRINT_RESRV);
					PE_NRD_M23_CASE_SPRINT(45, rd_cnt++, buffer, PE_NRD_M23_PRINT_RESRV);
					PE_NRD_M23_DFLT_SPRINT(rd_cnt=0, buffer, PE_NRD_M23_PRINT_END);
				}
			}
			else
			{
				is_valid = PE_NRD_M23_NO_PRINT;
				switch (pstParams->data[0])
				{
					case PE_NRD_HW_M23_RD_TNR1_DISP:
						table_size = sizeof(tnr_l_hd_i_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m23[rd_cnt].addr;
							is_valid = PE_NRD_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR1_DFLT:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_tnr1b_dflt[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR1_USER:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_tnr1b_user[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR1_MASK:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_tnr1b_mask[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR1_DATA:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_tnr1b_data[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					#if 0
					case PE_NRD_HW_M23_RD_TNR2_DISP:
						table_size = sizeof(tnr2nd_l_hd_i_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_m23[rd_cnt].addr;
							is_valid = PE_NRD_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR2_DFLT:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_tnr2b_dflt[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR2_USER:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_tnr2b_user[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR2_MASK:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_tnr2b_mask[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR2_DATA:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_tnr2b_data[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					#endif
					case PE_NRD_HW_M23_RD_DNR1_DISP:
						table_size = sizeof(dnr_l_hd_i_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m23[rd_cnt].addr;
							is_valid = PE_NRD_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M23_RD_DNR1_DFLT:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_dnr1b_dflt[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_DNR1_USER:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_dnr1b_user[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_DNR1_MASK:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_dnr1b_mask[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_DNR1_DATA:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_m23[rd_cnt].addr;
							param.data = p_dnr1b_data[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					#if 0
					case PE_NRD_HW_M23_RD_PSP1_DISP:
						table_size = sizeof(dnrpsp_l_hd_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = dnrpsp_l_hd_default_m23[rd_cnt].addr;
							is_valid = PE_NRD_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M23_RD_PSP1_DFLT:
						table_size = sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnrpsp_l_hd_default_m23[rd_cnt].addr;
							param.data = p_psp1b_dflt[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_PSP1_USER:
						table_size = sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnrpsp_l_hd_default_m23[rd_cnt].addr;
							param.data = p_psp1b_user[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_PSP1_MASK:
						table_size = sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnrpsp_l_hd_default_m23[rd_cnt].addr;
							param.data = p_psp1b_mask[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_PSP1_DATA:
						table_size = sizeof(PE_DNR_PSP_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnrpsp_l_hd_default_m23[rd_cnt].addr;
							param.data = p_psp1b_data[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_IFC1_DISP:
						table_size = sizeof(ifc_l_init_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m23[rd_cnt].addr;
							is_valid = PE_NRD_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M23_RD_IFC1_DFLT:
						table_size = sizeof(PE_IFC_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m23[rd_cnt].addr;
							param.data = p_ifc1b_dflt[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_IFC1_USER:
						table_size = sizeof(PE_IFC_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m23[rd_cnt].addr;
							param.data = p_ifc1b_user[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_IFC1_MASK:
						table_size = sizeof(PE_IFC_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m23[rd_cnt].addr;
							param.data = p_ifc1b_mask[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_IFC1_DATA:
						table_size = sizeof(PE_IFC_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = ifc_l_init_m23[rd_cnt].addr;
							param.data = p_ifc1b_data[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					#endif
					case PE_NRD_HW_M23_RD_LED1_DISP:
						table_size = sizeof(led_dnr_l_ud_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = led_dnr_l_ud_default_m23[rd_cnt].addr;
							is_valid = PE_NRD_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M23_RD_LED1_DFLT:
						table_size = sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = led_dnr_l_ud_default_m23[rd_cnt].addr;
							param.data = p_led1b_dflt[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_LED1_USER:
						table_size = sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = led_dnr_l_ud_default_m23[rd_cnt].addr;
							param.data = p_led1b_user[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_LED1_MASK:
						table_size = sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = led_dnr_l_ud_default_m23[rd_cnt].addr;
							param.data = p_led1b_mask[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_LED1_DATA:
						table_size = sizeof(PE_LED_DNR_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = led_dnr_l_ud_default_m23[rd_cnt].addr;
							param.data = p_led1b_data[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNR1_MLUT:
						table_size = sizeof(tnr_l_lut_hd_default_m23);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							#if 0	//not support PE_REG_M23_WD, use SYS_IO_WriteRegArray
							if (rd_cnt==0)
							{
								if (pstParams->data[0]==PE_NRD_HW_M23_RD_TNR1_MLUT)
									PE_REG_M23_WD(0x41D0, 0x00001000);
							}
							#endif
							param.addr = tnr_l_lut_hd_default_m23[rd_cnt].addr;
							is_valid = PE_NRD_M23_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_M23_RD_TNL1_DFLT:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_m23[rd_cnt].addr;
							param.data = p_tnl1b_dflt[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNL1_USER:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_m23[rd_cnt].addr;
							param.data = p_tnl1b_user[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNL1_MASK:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_m23[rd_cnt].addr;
							param.data = p_tnl1b_mask[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_M23_RD_TNL1_DATA:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_M23_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_m23[rd_cnt].addr;
							param.data = p_tnl1b_data[rd_cnt];
							is_valid = PE_NRD_M23_HEX_PRINT_ONLY;
						}
						break;
					default:
						break;
				}
				if (is_valid == PE_NRD_M23_RD_N_HEX_PRINT)
				{
					#if 0	//not support PE_REG_M23_RD, use SYS_IO_ReadRegArray
					param.data = PE_REG_M23_RD(param.addr);
					#endif
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else if (is_valid == PE_NRD_M23_HEX_PRINT_ONLY)
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "%s", PE_NRD_M23_PRINT_END);
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
int PE_NRD_HW_M23_SetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT8 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_DNR_CMN_T *ctrl_param =(LX_PE_NRD_DNR_CMN_T *)pstParams;
			LX_PE_NRD_DNR3_CMN_T *pp = (LX_PE_NRD_DNR3_CMN_T *)ctrl_param->data;
			LX_PE_NRD_EASY_DNR_CMN_T *epp = (typeof(*epp) *)ctrl_param->data;
			static LX_PE_NRD_DNR3_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DNR3_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DNR3_CMN_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_NRD("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd32 =  pp->dnr______ui;
					PE_DBG_NRD("set[%d] : dnr______ui\n"
					"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
					pd32[10], pd32[11], pd32[12]);
					pd32 = pp->dnr____buff;
					PE_DBG_NRD("set[%d] : dnr____buff\n"\
					"dnr____buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
				    /*set dnr_max_ctrl @ dummy reg(sre_sys_veri_0) bc racing issue with f/w */
					PE_SRE_VERI_M23_QWr01(sre_sys_veri_0,		reg_dnr_max_enable, GET_BITS(pp->dnr______ui[0],0,1));
					PE_NRD_HW_M23_DNR_SET_USER(dnr_max_ctrl,	reg_dnr_max_enable, GET_BITS(pp->dnr______ui[0],0,1));

					PE_NRD_HW_M23_NR0_VERI_WR02(mnr_ctrl_0, reg_mnr_chroma_en,	GET_BITS(pp->dnr______ui[1],0,1),\
																reg_mnr_enable, GET_BITS(pp->dnr______ui[2],0,1));

					PE_NRD_HW_M23_DNR_WR02(dc_bnr_ctrl_0,	reg_dc_bnr_enable,	GET_BITS(pp->dnr______ui[3],0,1),\
																reg_obj_gain_mul,	GET_BITS(pp->dnr______ui[4],0,2));
					PE_NRD_HW_M23_DNR_WR04(ac_bnr_ctrl_0,	reg_bnr_ac_v_chroma_en, GET_BITS(pp->dnr______ui[5],0,1),\
																reg_bnr_ac_h_chroma_en, GET_BITS(pp->dnr______ui[6],0,1),\
																reg_bnr_ac_v_en,	GET_BITS(pp->dnr______ui[7],0,1),\
																reg_bnr_ac_h_en,	GET_BITS(pp->dnr______ui[8],0,1));

					/* download dnr user db */
					ret = PE_NRD_HW_M23_DownloadDnrUserDb((void *)pp);
					PE_NRD_HW_M23_CHECK_CODE(ret, break, \
						"PE_NRD_HW_M23_DownloadDnrUserDb() error.\n");

				}
				else
				{
					PE_DBG_NRD("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					epp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = epp->data;
					PE_DBG_NRD("set[%d] : data\n"
					"data    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"data    [10]0x%02X,0x%02X,\n",\
					epp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11]);

					PE_NRD_HW_M23_DNR_WR01(dnr_max_ctrl,    reg_dnr_max_enable,     GET_BITS(epp->data[0], 0, 1));
					PE_DNR0_M23_QWr03(mnr_ctrl_0,      reg_mnr_master_gain,    GET_BITS(epp->data[1], 0, 8),\
					                                        reg_mnr_chroma_en,      GET_BITS(epp->data[2], 0, 1),\
					                                        reg_mnr_enable,         GET_BITS(epp->data[3], 0, 1));
					PE_NRD_HW_M23_DNR_WR01(dc_bnr_ctrl_0,   reg_dc_bnr_enable,      GET_BITS(epp->data[4], 0, 1));
					PE_NRD_HW_M23_DNR_WR02(dc_bnr_ctrl_2,   reg_dc_bnr_chromagain,  GET_BITS(epp->data[5], 0, 8),\
					                                        reg_dc_bnr_mastergain,  GET_BITS(epp->data[6], 0, 6));
					PE_NRD_HW_M23_DNR_WR04(ac_bnr_ctrl_0,   reg_bnr_ac_v_chroma_en, GET_BITS(epp->data[7], 0, 1),\
					                                        reg_bnr_ac_h_chroma_en, GET_BITS(epp->data[8], 0, 1),\
					                                        reg_bnr_ac_v_en,        GET_BITS(epp->data[9], 0, 1),\
					                                        reg_bnr_ac_h_en,        GET_BITS(epp->data[10], 0, 1));
					PE_NRD_HW_M23_DNR_WR01(ac_bnr_ctrl_9,   reg_ac_master_y_gain,   GET_BITS(epp->data[11], 0, 8));
				}
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_NRD_HW_M23_GetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
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
int PE_NRD_HW_M23_SetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT8 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_DNR_DETAIL_T *ctrl_param =(LX_PE_NRD_DNR_DETAIL_T *)pstParams;
			LX_PE_NRD_DNR3_DETAIL_T *pp = (LX_PE_NRD_DNR3_DETAIL_T *)ctrl_param->data;
			static LX_PE_NRD_DNR3_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DNR3_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DNR3_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_NRD("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = (typeof(*pd) *)pp->dnr_____mnr;
					PE_DBG_NRD("set[%d] : dnr_____mnr\n"
					"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

					pd = (typeof(*pd) *)pp->dnr___dcbnr;
					PE_DBG_NRD("set[%d] : dnr___dcbnr\n"
					"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32], pd[33]);

					pd = (typeof(*pd) *)pp->dnr___acbnr;
					PE_DBG_NRD("set[%d] : dnr___acbnr\n"
					"dnr___acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[30]0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30]);

					/*dnr_____mnr*/
					PE_NRD_HW_M23_DNR_WR04(mnr_ctrl_1,	reg_mmd_x_min,	GET_BITS(pp->dnr_____mnr[0],0,8),\
																reg_mmd_x_max,	GET_BITS(pp->dnr_____mnr[1],0,8),\
																reg_mmd_y_min,	GET_BITS(pp->dnr_____mnr[2],0,8),\
																reg_mmd_y_max,	GET_BITS(pp->dnr_____mnr[3],0,8));
					#if 0
					PE_NRD_HW_M23_DNR_WR02(mnr_ctrl_3,	reg_mmd_scale,	GET_BITS(pp->dnr_____mnr[4],0,8),\
																reg_blur_sel,	GET_BITS(pp->dnr_____mnr[5],0,1));
					#else
					PE_NRD_HW_M23_NR0_VERI_WR02(mnr_ctrl_3,	reg_mmd_scale,	GET_BITS(pp->dnr_____mnr[4],0,8),\
																		reg_blur_sel,	GET_BITS(pp->dnr_____mnr[5],0,1));
					#endif
					/*dnr___dcbnr*/
					PE_NRD_HW_M23_DNR_WR02(detail_ctrl, reg_bnr_diff_p, GET_BITS(pp->dnr___dcbnr[0],0,8),\
																reg_bnr_diff_l, GET_BITS(pp->dnr___dcbnr[1],0,8));
					PE_NRD_HW_M23_DNR_WR03(dc_bnr_ctrl_0,	reg_dc_motion_min,	GET_BITS(pp->dnr___dcbnr[2],0,8),\
																reg_dc_motion_max,	GET_BITS(pp->dnr___dcbnr[3],0,8),\
																reg_dc_blur_sel,	GET_BITS(pp->dnr___dcbnr[4],0,2));
					PE_NRD_HW_M23_DNR_WR04(dc_bnr_ctrl_1,	reg_var_cut_resolution, GET_BITS(pp->dnr___dcbnr[5],0,4),\
																reg_var_h_gain, GET_BITS(pp->dnr___dcbnr[6],0,4),\
																reg_var_v_gain, GET_BITS(pp->dnr___dcbnr[7],0,4),\
																reg_luma_gain_en,	GET_BITS(pp->dnr___dcbnr[8],0,1));
					PE_NRD_HW_M23_DNR_WR04(dc_bnr_ctrl_2,	reg_dc_protection_th,	GET_BITS(pp->dnr___dcbnr[9],0,8),\
																reg_dc_protection_en,	GET_BITS(pp->dnr___dcbnr[10],0,1),\
																reg_dc_motion_en,	GET_BITS(pp->dnr___dcbnr[11],0,1),\
																reg_dc_var_en,	GET_BITS(pp->dnr___dcbnr[12],0,1));
					PE_NRD_HW_M23_DNR_WR04(dc_bnr_ctrl_3,	reg_dc_bnr_var_th0, GET_BITS(pp->dnr___dcbnr[13],0,8),\
																reg_dc_bnr_var_th1, GET_BITS(pp->dnr___dcbnr[14],0,8),\
																reg_dc_bnr_var_th2, GET_BITS(pp->dnr___dcbnr[15],0,8),\
																reg_dc_bnr_var_th3, GET_BITS(pp->dnr___dcbnr[16],0,8));
					//PE_NRD_HW_M23_DNR_WR01(sc_bnr_ctrl_0,	reg_sc_bnr_en,	GET_BITS(pp->dnr___dcbnr[17],0,1));
					PE_NRD_HW_M23_DNR_WR04(reg_dc_bnr_ctrl_8,	reg_gain_x0,	GET_BITS(pp->dnr___dcbnr[18],0,8),\
																reg_gain_x1,	GET_BITS(pp->dnr___dcbnr[19],0,8),\
																reg_gain_x2,	GET_BITS(pp->dnr___dcbnr[20],0,8),\
																reg_gain_x3,	GET_BITS(pp->dnr___dcbnr[21],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_dc_bnr_ctrl_9,	reg_gain_x4,	GET_BITS(pp->dnr___dcbnr[22],0,8),\
																reg_gain_x5,	GET_BITS(pp->dnr___dcbnr[23],0,8),\
																reg_gain_x6,	GET_BITS(pp->dnr___dcbnr[24],0,8),\
																reg_gain_x7,	GET_BITS(pp->dnr___dcbnr[25],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_dc_bnr_ctrl_10,	reg_gain_y0,	GET_BITS(pp->dnr___dcbnr[26],0,8),\
																reg_gain_y1,	GET_BITS(pp->dnr___dcbnr[27],0,8),\
																reg_gain_y2,	GET_BITS(pp->dnr___dcbnr[28],0,8),\
																reg_gain_y3,	GET_BITS(pp->dnr___dcbnr[29],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_dc_bnr_ctrl_11,	reg_gain_y4,	GET_BITS(pp->dnr___dcbnr[30],0,8),\
																reg_gain_y5,	GET_BITS(pp->dnr___dcbnr[31],0,8),\
																reg_gain_y6,	GET_BITS(pp->dnr___dcbnr[32],0,8),\
																reg_gain_y7,	GET_BITS(pp->dnr___dcbnr[33],0,8));
					/*dnr___acbnr*/
					PE_NRD_HW_M23_DNR_WR02(detail_ctrl, reg_bnr_ac_detail_min,	GET_BITS(pp->dnr___acbnr[0],0,8),\
																reg_bnr_ac_detail_max,	GET_BITS(pp->dnr___acbnr[1],0,8));
					PE_NRD_HW_M23_DNR_WR03(ac_bnr_ctrl_0,	reg_bnr_ac_diff_min_h_th,	GET_BITS(pp->dnr___acbnr[2],0,8),\
																reg_bnr_ac_diff_min_v_th,	GET_BITS(pp->dnr___acbnr[3],0,8),\
																reg_bnr_ac_acness_resol_h,	GET_BITS(pp->dnr___acbnr[4],0,2));
					PE_NRD_HW_M23_DNR_WR03(ac_bnr_ctrl_1,	reg_bnr_ac_h_acness_min,	GET_BITS(pp->dnr___acbnr[5],0,8),\
																reg_bnr_ac_h_acness_max,	GET_BITS(pp->dnr___acbnr[6],0,8),\
																reg_bnr_ac_global_motion_th,	GET_BITS(pp->dnr___acbnr[7],0,8));
					PE_NRD_HW_M23_DNR_WR04(ac_bnr_ctrl_2,	reg_bnr_ac_motion_0,	GET_BITS(pp->dnr___acbnr[8],0,8),\
																reg_bnr_ac_motion_1,	GET_BITS(pp->dnr___acbnr[9],0,8),\
																reg_bnr_ac_motion_2,	GET_BITS(pp->dnr___acbnr[10],0,8),\
																reg_bnr_ac_motion_3,	GET_BITS(pp->dnr___acbnr[11],0,8));
					PE_NRD_HW_M23_DNR_WR04(ac_bnr_ctrl_3,	reg_bnr_ac_motion_y_0,	GET_BITS(pp->dnr___acbnr[12],0,8),\
																reg_bnr_ac_motion_y_1,	GET_BITS(pp->dnr___acbnr[13],0,8),\
																reg_bnr_ac_motion_y_2,	GET_BITS(pp->dnr___acbnr[14],0,8),\
																reg_bnr_ac_motion_y_3,	GET_BITS(pp->dnr___acbnr[15],0,8));
					PE_NRD_HW_M23_DNR_WR03(ac_bnr_ctrl_4,	reg_bnr_ac_v_acness_min,	GET_BITS(pp->dnr___acbnr[16],0,8),\
																reg_bnr_ac_v_acness_max,	GET_BITS(pp->dnr___acbnr[17],0,8),\
																reg_bnr_ac_acness_resol_v,	GET_BITS(pp->dnr___acbnr[18],0,2));
					PE_NRD_HW_M23_DNR_WR04(ac_bnr_ctrl_5,	reg_bnr_ac_detail_th1,	GET_BITS(pp->dnr___acbnr[19],0,8),\
																reg_bnr_ac_detail_th2,	GET_BITS(pp->dnr___acbnr[20],0,8),\
																reg_bnr_ac_detail_th3,	GET_BITS(pp->dnr___acbnr[21],0,8),\
																reg_bnr_ac_detail_th4,	GET_BITS(pp->dnr___acbnr[22],0,8));
					PE_NRD_HW_M23_DNR_WR04(ac_bnr_ctrl_6,	reg_bnr_ac_detail_gain_th,	GET_BITS(pp->dnr___acbnr[23],0,8),\
																reg_bnr_ac_pos_gain_h0, GET_BITS(pp->dnr___acbnr[24],0,8),\
																reg_bnr_ac_pos_gain_h1, GET_BITS(pp->dnr___acbnr[25],0,8),\
																reg_bnr_ac_pos_gain_h2, GET_BITS(pp->dnr___acbnr[26],0,8));
					PE_NRD_HW_M23_DNR_WR04(ac_bnr_ctrl_7,	reg_bnr_ac_pos_gain_h3, GET_BITS(pp->dnr___acbnr[27],0,8),\
																reg_bnr_ac_pos_gain_l0, GET_BITS(pp->dnr___acbnr[28],0,8),\
																reg_bnr_ac_pos_gain_l1, GET_BITS(pp->dnr___acbnr[29],0,8),\
																reg_bnr_ac_pos_gain_l2, GET_BITS(pp->dnr___acbnr[30],0,8));
				}
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_NRD_HW_M23_GetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT8 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_DNR_DETAIL_T *ctrl_param =(LX_PE_NRD_DNR_DETAIL_T *)pstParams;
			LX_PE_NRD_DNR3_DETAIL_T *pp = (LX_PE_NRD_DNR3_DETAIL_T *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					/*dnr_____mnr*/
					PE_DNR0_M23_QRd04(mnr_ctrl_1,			reg_mmd_x_min,		pp->dnr_____mnr[0],\
															reg_mmd_x_max,		pp->dnr_____mnr[1],\
															reg_mmd_y_min,		pp->dnr_____mnr[2],\
															reg_mmd_y_max,		pp->dnr_____mnr[3]);
					PE_DNR0_M23_QRd02(mnr_ctrl_3,			reg_mmd_scale,		pp->dnr_____mnr[4],\
															reg_blur_sel,		pp->dnr_____mnr[5]);
					/*dnr___dcbnr*/
					PE_DNR0_M23_QRd02(detail_ctrl, 			reg_bnr_diff_p, 	pp->dnr___dcbnr[0],\
															reg_bnr_diff_l, 	pp->dnr___dcbnr[1]);
					PE_DNR0_M23_QRd03(dc_bnr_ctrl_0,		reg_dc_motion_min,	pp->dnr___dcbnr[2],\
															reg_dc_motion_max,	pp->dnr___dcbnr[3],\
															reg_dc_blur_sel,	pp->dnr___dcbnr[4]);
					PE_DNR0_M23_QRd04(dc_bnr_ctrl_1,		reg_var_cut_resolution, pp->dnr___dcbnr[5],\
															reg_var_h_gain, 		pp->dnr___dcbnr[6],\
															reg_var_v_gain, 		pp->dnr___dcbnr[7],\
															reg_luma_gain_en,		pp->dnr___dcbnr[8]);
					PE_DNR0_M23_QRd04(dc_bnr_ctrl_2,		reg_dc_protection_th,	pp->dnr___dcbnr[9],\
															reg_dc_protection_en,	pp->dnr___dcbnr[10],\
															reg_dc_motion_en,		pp->dnr___dcbnr[11],\
															reg_dc_var_en,			pp->dnr___dcbnr[12]);
					PE_DNR0_M23_QRd04(dc_bnr_ctrl_3,		reg_dc_bnr_var_th0, 	pp->dnr___dcbnr[13],\
															reg_dc_bnr_var_th1, 	pp->dnr___dcbnr[14],\
															reg_dc_bnr_var_th2, 	pp->dnr___dcbnr[15],\
															reg_dc_bnr_var_th3, 	pp->dnr___dcbnr[16]);
					//PE_DNR0_M23_QRd01(sc_bnr_ctrl_0,		reg_sc_bnr_en,	pp->dnr___dcbnr[17]);
					PE_DNR0_M23_QRd04(reg_dc_bnr_ctrl_8,	reg_gain_x0,	pp->dnr___dcbnr[18],\
															reg_gain_x1,	pp->dnr___dcbnr[19],\
															reg_gain_x2,	pp->dnr___dcbnr[20],\
															reg_gain_x3,	pp->dnr___dcbnr[21]);
					PE_DNR0_M23_QRd04(reg_dc_bnr_ctrl_9,	reg_gain_x4,	pp->dnr___dcbnr[22],\
															reg_gain_x5,	pp->dnr___dcbnr[23],\
															reg_gain_x6,	pp->dnr___dcbnr[24],\
															reg_gain_x7,	pp->dnr___dcbnr[25]);
					PE_DNR0_M23_QRd04(reg_dc_bnr_ctrl_10,	reg_gain_y0,	pp->dnr___dcbnr[26],\
															reg_gain_y1,	pp->dnr___dcbnr[27],\
															reg_gain_y2,	pp->dnr___dcbnr[28],\
															reg_gain_y3,	pp->dnr___dcbnr[29]);
					PE_DNR0_M23_QRd04(reg_dc_bnr_ctrl_11,	reg_gain_y4,	pp->dnr___dcbnr[30],\
															reg_gain_y5,	pp->dnr___dcbnr[31],\
															reg_gain_y6,	pp->dnr___dcbnr[32],\
															reg_gain_y7,	pp->dnr___dcbnr[33]);
					/*dnr___acbnr*/
					PE_DNR0_M23_QRd02(detail_ctrl, 			reg_bnr_ac_detail_min,		pp->dnr___acbnr[0],\
															reg_bnr_ac_detail_max,		pp->dnr___acbnr[1]);
					PE_DNR0_M23_QRd03(ac_bnr_ctrl_0,		reg_bnr_ac_diff_min_h_th,	pp->dnr___acbnr[2],\
															reg_bnr_ac_diff_min_v_th,	pp->dnr___acbnr[3],\
															reg_bnr_ac_acness_resol_h,	pp->dnr___acbnr[4]);
					PE_DNR0_M23_QRd03(ac_bnr_ctrl_1,		reg_bnr_ac_h_acness_min,	pp->dnr___acbnr[5],\
															reg_bnr_ac_h_acness_max,	pp->dnr___acbnr[6],\
															reg_bnr_ac_global_motion_th,	pp->dnr___acbnr[7]);
					PE_DNR0_M23_QRd04(ac_bnr_ctrl_2,		reg_bnr_ac_motion_0,	pp->dnr___acbnr[8],\
															reg_bnr_ac_motion_1,	pp->dnr___acbnr[9],\
															reg_bnr_ac_motion_2,	pp->dnr___acbnr[10],\
															reg_bnr_ac_motion_3,	pp->dnr___acbnr[11]);
					PE_DNR0_M23_QRd04(ac_bnr_ctrl_3,		reg_bnr_ac_motion_y_0,	pp->dnr___acbnr[12],\
															reg_bnr_ac_motion_y_1,	pp->dnr___acbnr[13],\
															reg_bnr_ac_motion_y_2,	pp->dnr___acbnr[14],\
															reg_bnr_ac_motion_y_3,	pp->dnr___acbnr[15]);
					PE_DNR0_M23_QRd03(ac_bnr_ctrl_4,		reg_bnr_ac_v_acness_min,	pp->dnr___acbnr[16],\
															reg_bnr_ac_v_acness_max,	pp->dnr___acbnr[17],\
															reg_bnr_ac_acness_resol_v,	pp->dnr___acbnr[18]);
					PE_DNR0_M23_QRd04(ac_bnr_ctrl_5,		reg_bnr_ac_detail_th1,		pp->dnr___acbnr[19],\
															reg_bnr_ac_detail_th2,		pp->dnr___acbnr[20],\
															reg_bnr_ac_detail_th3,		pp->dnr___acbnr[21],\
															reg_bnr_ac_detail_th4,		pp->dnr___acbnr[22]);
					PE_DNR0_M23_QRd04(ac_bnr_ctrl_6,		reg_bnr_ac_detail_gain_th,	pp->dnr___acbnr[23],\
															reg_bnr_ac_pos_gain_h0, pp->dnr___acbnr[24],\
															reg_bnr_ac_pos_gain_h1, pp->dnr___acbnr[25],\
															reg_bnr_ac_pos_gain_h2, pp->dnr___acbnr[26]);
					PE_DNR0_M23_QRd04(ac_bnr_ctrl_7,		reg_bnr_ac_pos_gain_h3, pp->dnr___acbnr[27],\
															reg_bnr_ac_pos_gain_l0, pp->dnr___acbnr[28],\
															reg_bnr_ac_pos_gain_l1, pp->dnr___acbnr[29],\
															reg_bnr_ac_pos_gain_l2, pp->dnr___acbnr[30]);
					pd = (typeof(*pd) *)pp->dnr_____mnr;
					PE_DBG_NRD("get[%d] : dnr_____mnr\n"
					"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

					pd = (typeof(*pd) *)pp->dnr___dcbnr;
					PE_DBG_NRD("get[%d] : dnr___dcbnr\n"
					"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32], pd[33]);

					pd = (typeof(*pd) *)pp->dnr___acbnr;
					PE_DBG_NRD("get[%d] : dnr___acbnr\n"
					"dnr___acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[30]0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30]);
				}
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set dnr dnr common ctrl
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_SetDnrDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT16 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_DCNT_CMN_T *ctrl_param =(LX_PE_NRD_DCNT_CMN_T *)pstParams;
			LX_PE_NRD_DCNT3_CMN_T *pp = (LX_PE_NRD_DCNT3_CMN_T *)ctrl_param->data;
			LX_PE_NRD_EASY_DCNT_CMN_T *epp = (typeof(*epp) *)ctrl_param->data;
			static LX_PE_NRD_DCNT3_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT3_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DCNT2_CMN_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_NRD("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd32 = pp->deconnd_____ui;
					PE_DBG_NRD("set[%d] : deconnd_____ui\n"
					"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
					pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
					pd32 = pp->deconnd___buff;
					PE_DBG_NRD("set[%d] : deconnd___buff\n"\
					"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_0,	reg_1st_out_rd_on,	GET_BITS(pp->deconnd_____ui[0],0,1),\
																reg_1st_out_rd_bit, GET_BITS(pp->deconnd_____ui[1],0,3));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_7,	reg_2nd_out_rd_on,	GET_BITS(pp->deconnd_____ui[2],0,1),\
																reg_2nd_out_rd_bit, GET_BITS(pp->deconnd_____ui[3],0,4));
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,	GET_BITS(pp->deconnd_____ui[4],0,1));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_19,	reg_decon_diff_x_th3,	GET_BITS(pp->deconnd_____ui[5],0,8),\
																reg_decon_diff_x_th2,	GET_BITS(pp->deconnd_____ui[6],0,8),\
																reg_decon_diff_x_th1,	GET_BITS(pp->deconnd_____ui[7],0,8),\
																reg_decon_diff_x_th0,	GET_BITS(pp->deconnd_____ui[8],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_20,	reg_decon_diff_y_th3,	GET_BITS(pp->deconnd_____ui[9],0,8),\
																reg_decon_diff_y_th2,	GET_BITS(pp->deconnd_____ui[10],0,8),\
																reg_decon_diff_y_th1,	GET_BITS(pp->deconnd_____ui[11],0,8),\
																reg_decon_diff_y_th0,	GET_BITS(pp->deconnd_____ui[12],0,8));
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_56,	reg_face_master_gain,	GET_BITS(pp->deconnd_____ui[13],0,8));
					/* download dnr user db */
					ret = PE_NRD_HW_M23_DownloadDnrDcntUserDb((void *)pp);
					PE_NRD_HW_M23_CHECK_CODE(ret, break, \
						"PE_NRD_HW_M23_DownloadDnrDcntUserDb() error.\n");
				}
				else
				{
					//epp = (typeof(*epp) *)ctrl_param->data;
					PE_DBG_NRD("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					epp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = epp->data;
					PE_DBG_NRD("set[%d] : dnrled____ui\n"\
					"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd_____ui    [10]0x%02X,0x%02X\n",\
					epp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], pd[10], pd[11]);
					#if 0
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_0,	reg_1st_out_rd_on,		GET_BITS(epp->data[0],0,1));
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_7,	reg_2nd_out_rd_on,		GET_BITS(epp->data[1],0,1));
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,		GET_BITS(epp->data[2],0,1));
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_69,	reg_decon_2nd_en,		GET_BITS(epp->data[3],0,1));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_19,	reg_decon_diff_x_th3,	GET_BITS(epp->data[4],0,8),\
																reg_decon_diff_x_th2,	GET_BITS(epp->data[5],0,8),\
																reg_decon_diff_x_th1,	GET_BITS(epp->data[6],0,8),\
																reg_decon_diff_x_th0,	GET_BITS(epp->data[7],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_20,	reg_decon_diff_y_th3,	GET_BITS(epp->data[8],0,8),\
																reg_decon_diff_y_th2,	GET_BITS(epp->data[9],0,8),\
																reg_decon_diff_y_th1,	GET_BITS(epp->data[10],0,8),\
																reg_decon_diff_y_th0,	GET_BITS(epp->data[11],0,8));
					#else
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_0,	reg_1st_out_rd_on,	GET_BITS(epp->data[0],0,1));
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_7,	reg_2nd_out_rd_on,	GET_BITS(epp->data[1],0,1));
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,	GET_BITS(epp->data[2],0,1));
					//PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_69,	reg_decon_2nd_en,	GET_BITS(epp->data[3],0,1));
					PE_NRD_HW_M23_DNR_WR01(reg_decon_ctrl_31,	reg_master_gain,	GET_BITS(epp->data[4],0,8));
					#endif
				}
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_NRD_HW_M23_GetDnrDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT16 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_DCNT_CMN_T *ctrl_param =(LX_PE_NRD_DCNT_CMN_T *)pstParams;
			LX_PE_NRD_DCNT3_CMN_T *pp = (LX_PE_NRD_DCNT3_CMN_T *)ctrl_param->data;
			LX_PE_NRD_EASY_DCNT_CMN_T *epp = (typeof(*epp) *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DNR0_M23_QRd02(reg_decon_ctrl_0,			reg_1st_out_rd_on,	pp->deconnd_____ui[0],\
																reg_1st_out_rd_bit, pp->deconnd_____ui[1]);
					PE_DNR0_M23_QRd02(reg_decon_ctrl_7,			reg_2nd_out_rd_on,	pp->deconnd_____ui[2],\
																reg_2nd_out_rd_bit, pp->deconnd_____ui[3]);
					PE_DNR0_M23_QRd01(reg_decon_ctrl_17,		reg_decon_1st_en,	pp->deconnd_____ui[4]);
					PE_DNR0_M23_QRd04(reg_decon_ctrl_19,		reg_decon_diff_x_th3,	pp->deconnd_____ui[5],\
																reg_decon_diff_x_th2,	pp->deconnd_____ui[6 ],\
																reg_decon_diff_x_th1,	pp->deconnd_____ui[7 ],\
																reg_decon_diff_x_th0,	pp->deconnd_____ui[8 ]);
					PE_DNR0_M23_QRd04(reg_decon_ctrl_20,		reg_decon_diff_y_th3,	pp->deconnd_____ui[9 ],\
																reg_decon_diff_y_th2,	pp->deconnd_____ui[10],\
																reg_decon_diff_y_th1,	pp->deconnd_____ui[11],\
																reg_decon_diff_y_th0,	pp->deconnd_____ui[12]);
					PE_DNR0_M23_QRd01(reg_decon_ctrl_56,	reg_face_master_gain,	pp->deconnd_____ui[13]);
					
					pd = (typeof(*pd) *)pp->deconnd_____ui;
					PE_DBG_NRD("get[%d] : dnr______ui\n"
						"deconnd_____ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"deconnd_____ui [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
						pp->win_id, \
						pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], pd[10],\
						pd[11], pd[12], pd[13], pd[14]);
				}
				else
				{
					//epp = (typeof(*epp) *)ctrl_param->data;
					PE_DNR0_M23_QRd01(reg_decon_ctrl_0,		reg_1st_out_rd_on,	pp->deconnd_____ui[0]);
					PE_DNR0_M23_QRd01(reg_decon_ctrl_7,		reg_2nd_out_rd_on,	pp->deconnd_____ui[1]);
					PE_DNR0_M23_QRd01(reg_decon_ctrl_17,	reg_decon_1st_en,	pp->deconnd_____ui[2]);
					//PE_DNR0_M23_QRd01(reg_decon_ctrl_69,	reg_decon_2nd_en,	pp->deconnd_____ui[3]);
					PE_DNR0_M23_QRd04(reg_decon_ctrl_19,	reg_decon_diff_x_th3,	pp->deconnd_____ui[4],\
															reg_decon_diff_x_th2,	pp->deconnd_____ui[5],\
															reg_decon_diff_x_th1,	pp->deconnd_____ui[6],\
															reg_decon_diff_x_th0,	pp->deconnd_____ui[7]);
					PE_DNR0_M23_QRd04(reg_decon_ctrl_20,	reg_decon_diff_y_th3,	pp->deconnd_____ui[8],\
															reg_decon_diff_y_th2,	pp->deconnd_____ui[9],\
															reg_decon_diff_y_th1,	pp->deconnd_____ui[10],\
															reg_decon_diff_y_th0,	pp->deconnd_____ui[11]);
					pd = epp->data;
					PE_DBG_NRD("get[%d] : dnr______ui\n"
						"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"0x%02X,0x%02X,\n",\
						epp->win_id, \
						pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], pd[10], pd[11]);
				}
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_SetDnrDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT16 *pd;
	UINT8 *pd8;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_DCNT_DETAIL_T *ctrl_param =(LX_PE_NRD_DCNT_DETAIL_T *)pstParams;
			LX_PE_NRD_DCNT4_DETAIL_T *pp = (LX_PE_NRD_DCNT4_DETAIL_T *)ctrl_param->data;
			static LX_PE_NRD_DCNT4_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT4_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DCNT4_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_NRD("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = (typeof(*pd) *)pp->deconnd____cmn;
					PE_DBG_NRD("set[%d] : deconnd____cmn\n"
					"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [70]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
					pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
					pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57], pd[58], pd[59],\
					pd[60], pd[61], pd[62], pd[63], pd[64], pd[65], pd[66], pd[67], pd[68], pd[69],\
					pd[70], pd[71], pd[72], pd[73], pd[74], pd[75], pd[76]);
					pd8 = pp->deconnd___face;
					PE_DBG_NRD("set[%d] : deconnd___face\n"
					"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd___face    [30]0x%02X,0x%02X\n",\
					pp->win_id, \
					pd8[0], pd8[1], pd8[2], pd8[3], pd8[4], pd8[5], pd8[6], pd8[7], pd8[8], pd8[9],\
					pd8[10], pd8[11], pd8[12], pd8[13], pd8[14], pd8[15], pd8[16], pd8[17], pd8[18], pd8[19],\
					pd8[20], pd8[21], pd8[22], pd8[23], pd8[24], pd8[25], pd8[26], pd8[27], pd8[28], pd8[29],\
					pd8[30], pd8[31]);	
					/*dnr_dcnt*/
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_18,	reg_var_cut_resolution,	GET_BITS(pp->deconnd____cmn[0],0,4),\
																reg_var_h_gain,			GET_BITS(pp->deconnd____cmn[1],0,4),\
																reg_var_chroma_en,		GET_BITS(pp->deconnd____cmn[2],0,1));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_21,	reg_decon_var_x_th0,	GET_BITS(pp->deconnd____cmn[3],0,10),\
																reg_decon_var_x_th1,	GET_BITS(pp->deconnd____cmn[4],0,10),\
																reg_decon_var_x_th2,	GET_BITS(pp->deconnd____cmn[5],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_22,	reg_decon_var_x_th3,	GET_BITS(pp->deconnd____cmn[6],0,10),\
																reg_decon_var_y_th0,	GET_BITS(pp->deconnd____cmn[7],0,10),\
																reg_decon_var_y_th1,	GET_BITS(pp->deconnd____cmn[8],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_23,	reg_decon_var_y_th2,	GET_BITS(pp->deconnd____cmn[9],0,10),\
																reg_decon_var_y_th3,	GET_BITS(pp->deconnd____cmn[10],0,10),\
																reg_decon_luma_x_th0,	GET_BITS(pp->deconnd____cmn[11],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_24,	reg_decon_luma_x_th1,	GET_BITS(pp->deconnd____cmn[12],0,10),\
																reg_decon_luma_x_th2,	GET_BITS(pp->deconnd____cmn[13],0,10),\
																reg_decon_luma_x_th3,	GET_BITS(pp->deconnd____cmn[14],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_25,	reg_decon_luma_x_th4,	GET_BITS(pp->deconnd____cmn[15],0,10),\
																reg_decon_luma_x_th5,	GET_BITS(pp->deconnd____cmn[16],0,10),\
																reg_decon_luma_x_th6,	GET_BITS(pp->deconnd____cmn[17],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_26,	reg_decon_luma_x_th7,	GET_BITS(pp->deconnd____cmn[18],0,10),\
																reg_decon_luma_y_th0,	GET_BITS(pp->deconnd____cmn[19],0,10),\
																reg_decon_luma_y_th1,	GET_BITS(pp->deconnd____cmn[20],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_27,	reg_decon_luma_y_th2,	GET_BITS(pp->deconnd____cmn[21],0,10),\
																reg_decon_luma_y_th3,	GET_BITS(pp->deconnd____cmn[22],0,10),\
																reg_decon_luma_y_th4,	GET_BITS(pp->deconnd____cmn[23],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_28,	reg_decon_luma_y_th5,	GET_BITS(pp->deconnd____cmn[24],0,10),\
																reg_decon_luma_y_th6,	GET_BITS(pp->deconnd____cmn[25],0,10),\
																reg_decon_luma_y_th7,	GET_BITS(pp->deconnd____cmn[26],0,10));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_44,	reg_motion_gain_x0,		GET_BITS(pp->deconnd____cmn[27],0,8),\
																reg_motion_gain_x1,		GET_BITS(pp->deconnd____cmn[28],0,8),\
																reg_motion_gain_x2,		GET_BITS(pp->deconnd____cmn[29],0,8),\
																reg_motion_gain_x3,		GET_BITS(pp->deconnd____cmn[30],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_45,	reg_motion_gain_y0,		GET_BITS(pp->deconnd____cmn[31],0,8),\
																reg_motion_gain_y1,		GET_BITS(pp->deconnd____cmn[32],0,8),\
																reg_motion_gain_y2,		GET_BITS(pp->deconnd____cmn[33],0,8),\
																reg_motion_gain_y3,		GET_BITS(pp->deconnd____cmn[34],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_48,	reg_lut_blur_sim_x0,	GET_BITS(pp->deconnd____cmn[35],0,8),\
																reg_lut_blur_sim_x1,	GET_BITS(pp->deconnd____cmn[36],0,8),\
																reg_lut_blur_sim_x2,	GET_BITS(pp->deconnd____cmn[37],0,8),\
																reg_lut_blur_sim_x3,	GET_BITS(pp->deconnd____cmn[38],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_49,	reg_lut_blur_sim_y0,	GET_BITS(pp->deconnd____cmn[39],0,8),\
																reg_lut_blur_sim_y1,	GET_BITS(pp->deconnd____cmn[40],0,8),\
																reg_lut_blur_sim_y2,	GET_BITS(pp->deconnd____cmn[41],0,8),\
																reg_lut_blur_sim_y3,	GET_BITS(pp->deconnd____cmn[42],0,8));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_69,	reg_var_lowapl_lut_x0,	GET_BITS(pp->deconnd____cmn[43],0,10),\
																reg_var_lowapl_lut_x1,	GET_BITS(pp->deconnd____cmn[44],0,10),\
																reg_var_lowapl_lut_x2,	GET_BITS(pp->deconnd____cmn[45],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_70,	reg_var_lowapl_lut_x3,	GET_BITS(pp->deconnd____cmn[46],0,10),\
																reg_var_lowapl_lut_y0,	GET_BITS(pp->deconnd____cmn[47],0,10),\
																reg_var_lowapl_lut_y1,	GET_BITS(pp->deconnd____cmn[48],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_71,	reg_var_lowapl_lut_y2,	GET_BITS(pp->deconnd____cmn[49],0,10),\
																reg_var_lowapl_lut_y3,	GET_BITS(pp->deconnd____cmn[50],0,10),\
																reg_var_lowapl_blend_x0,GET_BITS(pp->deconnd____cmn[51],0,10));
					PE_NRD_HW_M23_DNR_WR03(reg_decon_ctrl_72,	reg_var_lowapl_blend_x1,GET_BITS(pp->deconnd____cmn[52],0,10),\
																reg_var_lowapl_blend_x2,GET_BITS(pp->deconnd____cmn[53],0,10),\
																reg_var_lowapl_blend_x3,GET_BITS(pp->deconnd____cmn[54],0,10));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_73,	reg_var_lowapl_blend_y0,GET_BITS(pp->deconnd____cmn[55],0,8),\
																reg_var_lowapl_blend_y1,GET_BITS(pp->deconnd____cmn[56],0,8),\
																reg_var_lowapl_blend_y2,GET_BITS(pp->deconnd____cmn[57],0,8),\
																reg_var_lowapl_blend_y3,GET_BITS(pp->deconnd____cmn[58],0,8));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_84,	reg_1st_rd_luma_en,		GET_BITS(pp->deconnd____cmn[59],0,1),\
																reg_2nd_rd_luma_en,		GET_BITS(pp->deconnd____cmn[60],0,1));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_87,	reg_1st_rd_luma_x0,		GET_BITS(pp->deconnd____cmn[61],0,10),\
																reg_1st_rd_luma_x1,		GET_BITS(pp->deconnd____cmn[62],0,10));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_88,	reg_1st_rd_luma_x2,		GET_BITS(pp->deconnd____cmn[63],0,10),\
																reg_1st_rd_luma_x3,		GET_BITS(pp->deconnd____cmn[64],0,10));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_89,	reg_1st_rd_luma_x4,		GET_BITS(pp->deconnd____cmn[65],0,10),\
																reg_1st_rd_luma_x5,		GET_BITS(pp->deconnd____cmn[66],0,10));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_90,	reg_1st_rd_luma_x6,		GET_BITS(pp->deconnd____cmn[67],0,10),\
																reg_1st_rd_luma_x7,		GET_BITS(pp->deconnd____cmn[68],0,10));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_91,	reg_1st_rd_luma_y0,		GET_BITS(pp->deconnd____cmn[69],0,10),\
																reg_1st_rd_luma_y1,		GET_BITS(pp->deconnd____cmn[70],0,10));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_92,	reg_1st_rd_luma_y2,		GET_BITS(pp->deconnd____cmn[71],0,10),\
																reg_1st_rd_luma_y3,		GET_BITS(pp->deconnd____cmn[72],0,10));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_93,	reg_1st_rd_luma_y4,		GET_BITS(pp->deconnd____cmn[73],0,10),\
																reg_1st_rd_luma_y5,		GET_BITS(pp->deconnd____cmn[74],0,10));
					PE_NRD_HW_M23_DNR_WR02(reg_decon_ctrl_94,	reg_1st_rd_luma_y6,		GET_BITS(pp->deconnd____cmn[75],0,10),\
																reg_1st_rd_luma_y7,		GET_BITS(pp->deconnd____cmn[76],0,10));
					/* face obj*/
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_50,	reg_lut_skin_yy_x0,	GET_BITS(pp->deconnd___face[0],0,8),\
																reg_lut_skin_yy_x1,	GET_BITS(pp->deconnd___face[1],0,8),\
																reg_lut_skin_yy_x2,	GET_BITS(pp->deconnd___face[2],0,8),\
																reg_lut_skin_yy_x3,	GET_BITS(pp->deconnd___face[3],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_51,	reg_lut_skin_cb_x0,	GET_BITS(pp->deconnd___face[4],0,8),\
																reg_lut_skin_cb_x1,	GET_BITS(pp->deconnd___face[5],0,8),\
																reg_lut_skin_cb_x2,	GET_BITS(pp->deconnd___face[6],0,8),\
																reg_lut_skin_cb_x3,	GET_BITS(pp->deconnd___face[7],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_52,	reg_lut_skin_cr_x0,	GET_BITS(pp->deconnd___face[8],0,8),\
																reg_lut_skin_cr_x1,	GET_BITS(pp->deconnd___face[9],0,8),\
																reg_lut_skin_cr_x2,	GET_BITS(pp->deconnd___face[10],0,8),\
																reg_lut_skin_cr_x3,	GET_BITS(pp->deconnd___face[11],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_53,	reg_lut_skin_y0,	GET_BITS(pp->deconnd___face[12],0,8),\
																reg_lut_skin_y1,	GET_BITS(pp->deconnd___face[13],0,8),\
																reg_lut_skin_y2,	GET_BITS(pp->deconnd___face[14],0,8),\
																reg_lut_skin_y3,	GET_BITS(pp->deconnd___face[15],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_54,	reg_lut_face_x0,	GET_BITS(pp->deconnd___face[16],0,8),\
																reg_lut_face_x1,	GET_BITS(pp->deconnd___face[17],0,8),\
																reg_lut_face_x2,	GET_BITS(pp->deconnd___face[18],0,8),\
																reg_lut_face_x3,	GET_BITS(pp->deconnd___face[19],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_55,	reg_lut_face_y0,	GET_BITS(pp->deconnd___face[20],0,8),\
																reg_lut_face_y1,	GET_BITS(pp->deconnd___face[21],0,8),\
																reg_lut_face_y2,	GET_BITS(pp->deconnd___face[22],0,8),\
																reg_lut_face_y3,	GET_BITS(pp->deconnd___face[23],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_97,	reg_ref_mmd_gain_x3,	GET_BITS(pp->deconnd___face[24],0,8),\
																reg_ref_mmd_gain_x2,	GET_BITS(pp->deconnd___face[25],0,8),\
																reg_ref_mmd_gain_x1,	GET_BITS(pp->deconnd___face[26],0,8),\
																reg_ref_mmd_gain_x0,	GET_BITS(pp->deconnd___face[27],0,8));
					PE_NRD_HW_M23_DNR_WR04(reg_decon_ctrl_98,	reg_ref_mmd_gain_y3,	GET_BITS(pp->deconnd___face[28],0,8),\
																reg_ref_mmd_gain_y2,	GET_BITS(pp->deconnd___face[29],0,8),\
																reg_ref_mmd_gain_y1,	GET_BITS(pp->deconnd___face[30],0,8),\
																reg_ref_mmd_gain_y0,	GET_BITS(pp->deconnd___face[31],0,8));
					}
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_GetDnrDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}

/**
 * set led dnr common ctrl - not used @M23
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_SetLedDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * get dnr common ctrl - not used @M23
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
int PE_NRD_HW_M23_GetLedDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}

/**
 * set dnr detail ctrl  - not used @M23
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_SetLedDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}
/**
 * get dnr detail ctrl  - not used @M23
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_GetLedDcntDetailCtrl(void *pstParams)
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
int PE_NRD_HW_M23_SetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	const PE_REG_PARAM_T *p_db = NULL;
	PE_INF_M23_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	__attribute__((unused)) PE_NRD_HW_M23_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m23_info;
	PE_TNL_HW_PARAM_REG_M23_T *p_tnl_dflt_b = _g_pe_tnl_hw_param_data_m23.reg_dflt.data;
	#define M23_TNL_DFT_B(_num)	(p_tnl_dflt_b->tnr_lut_##_num.main_lut_indir_data0)
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT32 *pd;
			LX_PE_NRD_TNR_CMN_T *ctrl_param =(LX_PE_NRD_TNR_CMN_T *)pstParams;
			LX_PE_NRD_TNR1_CMN_T *pp = (LX_PE_NRD_TNR1_CMN_T *)ctrl_param->data;
			static LX_PE_NRD_TNR1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR1_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR1_CMN_T\n");
				ret=RET_OK;
				break;
			}
			pd = (typeof(*pd) *)pp->tnr0__lut;
			PE_DBG_NRD("[%d]tnr0___en:%d\n", pp->win_id, pp->tnr0___en);
			PE_DBG_NRD( \
			"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = (typeof(*pd) *)pp->tnr0_gain;
			PE_DBG_NRD(\
			"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = (typeof(*pd) *)pp->tnr0_buff;
			PE_DBG_NRD(\
			"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],	pd[12], pd[13], pd[14]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* skip drv tnr ctrl, if fw tnr on. */
				if (ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					/* save prev values */
					memcpy(&(pInfo->tnr0_cmn), pp, sizeof(LX_PE_NRD_TNR1_CMN_T));
					/* download tnr user db */
					ret = PE_NRD_HW_M23_DownloadTnrUserDb((void *)pp);
					PE_NRD_HW_M23_CHECK_CODE(ret, break, \
						"PE_NRD_HW_M23_DownloadTnrUserDb() error.\n");
					PE_DBG_NRD("set tnr lut by firmware\n");
				}
				else
				{
					UINT32 *p_lut = pp->tnr0__lut;
					if (pp->tnr0___en == 3)					//high
					{
						p_db = tnr_l_lut_user_high_m23;
					}
					else if (pp->tnr0___en == 2 || pp->tnr0___en == 4)//medium, auto
					{
						p_db = tnr_l_lut_user_med_m23;
					}
					else if (pp->tnr0___en == 1)				//low
					{
						p_db = tnr_l_lut_user_low_m23;
					}
					else									//off
					{
						p_db = tnr_l_lut_user_off_m23;
					}
					CHECK_KNULL(p_db);
					ret = PE_INF_M23_GetCurInfSettings(&inf_set);
					PE_NRD_HW_M23_CHECK_CODE(ret,break,"PE_INF_M23_GetCurInfSettings() error.\n");
					disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
					PE_ND0_M23_QWr(tnr_main_lut_00, 0x00001000);
					if (pp->tnr0___en==0)	//off
					{
						PE_NRD_HW_M23_TNL_WR32(00, p_db[0].data );// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
						PE_NRD_HW_M23_TNL_WR32(01, p_db[1].data );// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
						PE_NRD_HW_M23_TNL_WR32(02, p_db[2].data );// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
						PE_NRD_HW_M23_TNL_WR32(03, p_db[3].data );// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
						PE_NRD_HW_M23_TNL_WR32(04, p_db[4].data );// 04. x5y5 x4y4 reg_p2_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(05, p_db[5].data );// 05. x3y3 x2y2 reg_p2_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(06, p_db[6].data );// 06. x1y1 x0y0 reg_p2_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(07, p_lut[0]     );// 07. x7y7 x6y6 reg_detail_iir_pt
						PE_NRD_HW_M23_TNL_WR32(08, p_lut[1]     );// 08. x5y5 x4y4 reg_detail_iir_pt
						PE_NRD_HW_M23_TNL_WR32(09, p_lut[2]     );// 09. x3y3 x2y2 reg_detail_iir_pt
						PE_NRD_HW_M23_TNL_WR32(10, p_lut[3]     );// 10. x1y1 x0y0 reg_detail_iir_pt
						PE_NRD_HW_M23_TNL_WR32(11, p_lut[4]     );// 11. x7y7 x6y6 reg_detail_cir_pt
						PE_NRD_HW_M23_TNL_WR32(12, p_lut[5]     );// 12. x5y5 x4y4 reg_detail_cir_pt
						PE_NRD_HW_M23_TNL_WR32(13, p_lut[6]     );// 13. x3y3 x2y2 reg_detail_cir_pt
						PE_NRD_HW_M23_TNL_WR32(14, p_lut[7]     );// 14. x1y1 x0y0 reg_detail_cir_pt
						PE_NRD_HW_M23_TNL_WR32(15, p_lut[8]     );// 15. x7y7 x6y6 reg_flat_iir_pt
						PE_NRD_HW_M23_TNL_WR32(16, p_lut[9]     );// 16. x5y5 x4y4 reg_flat_iir_pt
						PE_NRD_HW_M23_TNL_WR32(17, p_lut[10]    );// 17. x3y3 x2y2 reg_flat_iir_pt
						PE_NRD_HW_M23_TNL_WR32(18, p_lut[11]    );// 18. x1y1 x0y0 reg_flat_iir_pt
						PE_NRD_HW_M23_TNL_WR32(19, p_lut[12]    );// 19. x7y7 x6y6 reg_flat_cir_pt
						PE_NRD_HW_M23_TNL_WR32(20, p_lut[13]    );// 20. x5y5 x4y4 reg_flat_cir_pt
						PE_NRD_HW_M23_TNL_WR32(21, p_lut[14]    );// 21. x3y3 x2y2 reg_flat_cir_pt
						PE_NRD_HW_M23_TNL_WR32(22, p_lut[15]    );// 22. x1y1 x0y0 reg_flat_cir_pt
						PE_NRD_HW_M23_TNL_WR32(23, p_db[23].data);// 23. x1y1 x0y0 reg_luma_gain_ctrl
						PE_NRD_HW_M23_TNL_WR32(24, p_db[24].data);// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
						PE_NRD_HW_M23_TNL_WR32(25, p_db[25].data);// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
						PE_NRD_HW_M23_TNL_WR32(26, p_db[26].data);// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
						PE_NRD_HW_M23_TNL_WR32(27, p_db[27].data);// 27. x1y1 x0y0 reg_skin_motion_ctrl
						PE_NRD_HW_M23_TNL_WR32(28, p_db[28].data);// 28. reg_detail_luma_ctrl
						PE_NRD_HW_M23_TNL_WR32(29, p_db[29].data);// 29. x3y3 x2y2 reg_NLM_Protect
						PE_NRD_HW_M23_TNL_WR32(30, p_db[30].data);// 30. x1y1 x0y0 reg_NLM_Protect
						PE_NRD_HW_M23_TNL_WR32(31, p_db[31].data);// 31. x5y5 x4y4 reg_cc_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(32, p_db[32].data);// 32. x3y3 x2y2 reg_cc_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(33, p_db[33].data);// 33. x1y1 x0y0 reg_cc_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(34, p_db[34].data);// 34. x5y5 x4y4 reg_ne_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(35, p_db[35].data);// 35. x3y3 x2y2 reg_ne_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(36, p_db[36].data);// 36. x1y1 x0y0 reg_ne_dist_max_pt
						PE_NRD_HW_M23_TNL_WR32(37, p_db[37].data);// 37. eg_skin_gain_ctrl_yy
						PE_NRD_HW_M23_TNL_WR32(38, p_db[38].data);// 38. eg_skin_gain_ctrl_cb
						PE_NRD_HW_M23_TNL_WR32(39, p_db[39].data);// 39. eg_skin_gain_ctrl_cr
						PE_NRD_HW_M23_TNL_WR32(40, p_db[40].data);// 40. eg_skin_motion_ctrl
						PE_NRD_HW_M23_TNL_WR32(41, p_db[41].data);// 41. x7y7 x6y6 reg_simple_ma_iir_pt
						PE_NRD_HW_M23_TNL_WR32(42, p_db[42].data);// 42. x5y5 x4y4 reg_simple_ma_iir_pt
						PE_NRD_HW_M23_TNL_WR32(43, p_db[43].data);// 43. x3y3 x2y2 reg_simple_ma_iir_pt
						PE_NRD_HW_M23_TNL_WR32(44, p_db[44].data);// 44. x1y1 x0y0 reg_simple_ma_iir_pt
					}
					else
					{
						if(disp0_inf->src_type==LX_PE_SRC_DTV && \
							disp0_inf->fmt_type==LX_PE_FMT_HD && \
							disp0_inf->dtv_type==LX_PE_DTV_CAMERA)
						{
							PE_NRD_HW_M23_TNL_WR32(00, M23_TNL_DFT_B(00));// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M23_TNL_WR32(01, M23_TNL_DFT_B(01));// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M23_TNL_WR32(02, M23_TNL_DFT_B(02));// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M23_TNL_WR32(03, M23_TNL_DFT_B(03));// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M23_TNL_WR32(04, M23_TNL_DFT_B(04));// 04. x5y5 x4y4 reg_p2_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(05, M23_TNL_DFT_B(05));// 05. x3y3 x2y2 reg_p2_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(06, M23_TNL_DFT_B(06));// 06. x1y1 x0y0 reg_p2_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(07, M23_TNL_DFT_B(07));// 07. x7y7 x6y6 reg_detail_iir_pt
							PE_NRD_HW_M23_TNL_WR32(08, M23_TNL_DFT_B(08));// 08. x5y5 x4y4 reg_detail_iir_pt
							PE_NRD_HW_M23_TNL_WR32(09, M23_TNL_DFT_B(09));// 09. x3y3 x2y2 reg_detail_iir_pt
							PE_NRD_HW_M23_TNL_WR32(10, M23_TNL_DFT_B(10));// 10. x1y1 x0y0 reg_detail_iir_pt
							PE_NRD_HW_M23_TNL_WR32(11, M23_TNL_DFT_B(11));// 11. x7y7 x6y6 reg_detail_cir_pt
							PE_NRD_HW_M23_TNL_WR32(12, M23_TNL_DFT_B(12));// 12. x5y5 x4y4 reg_detail_cir_pt
							PE_NRD_HW_M23_TNL_WR32(13, M23_TNL_DFT_B(13));// 13. x3y3 x2y2 reg_detail_cir_pt
							PE_NRD_HW_M23_TNL_WR32(14, M23_TNL_DFT_B(14));// 14. x1y1 x0y0 reg_detail_cir_pt
							PE_NRD_HW_M23_TNL_WR32(15, M23_TNL_DFT_B(15));// 15. x7y7 x6y6 reg_flat_iir_pt
							PE_NRD_HW_M23_TNL_WR32(16, M23_TNL_DFT_B(16));// 16. x5y5 x4y4 reg_flat_iir_pt
							PE_NRD_HW_M23_TNL_WR32(17, M23_TNL_DFT_B(17));// 17. x3y3 x2y2 reg_flat_iir_pt
							PE_NRD_HW_M23_TNL_WR32(18, M23_TNL_DFT_B(18));// 18. x1y1 x0y0 reg_flat_iir_pt
							PE_NRD_HW_M23_TNL_WR32(19, M23_TNL_DFT_B(19));// 19. x7y7 x6y6 reg_flat_cir_pt
							PE_NRD_HW_M23_TNL_WR32(20, M23_TNL_DFT_B(20));// 20. x5y5 x4y4 reg_flat_cir_pt
							PE_NRD_HW_M23_TNL_WR32(21, M23_TNL_DFT_B(21));// 21. x3y3 x2y2 reg_flat_cir_pt
							PE_NRD_HW_M23_TNL_WR32(22, M23_TNL_DFT_B(22));// 22. x1y1 x0y0 reg_flat_cir_pt
							PE_NRD_HW_M23_TNL_WR32(23, M23_TNL_DFT_B(23));// 23. x1y1 x0y0 reg_luma_gain_ctrl
							PE_NRD_HW_M23_TNL_WR32(24, M23_TNL_DFT_B(24));// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
							PE_NRD_HW_M23_TNL_WR32(25, M23_TNL_DFT_B(25));// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
							PE_NRD_HW_M23_TNL_WR32(26, M23_TNL_DFT_B(26));// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
							PE_NRD_HW_M23_TNL_WR32(27, M23_TNL_DFT_B(27));// 27. x1y1 x0y0 reg_skin_motion_ctrl
							PE_NRD_HW_M23_TNL_WR32(28, M23_TNL_DFT_B(28));// 28. reg_detail_luma_ctrl
							PE_NRD_HW_M23_TNL_WR32(29, M23_TNL_DFT_B(29));// 29. x3y3 x2y2 reg_NLM_Protect
							PE_NRD_HW_M23_TNL_WR32(30, M23_TNL_DFT_B(30));// 30. x1y1 x0y0 reg_NLM_Protect
							PE_NRD_HW_M23_TNL_WR32(31, M23_TNL_DFT_B(31));// 31. x5y5 x4y4 reg_cc_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(32, M23_TNL_DFT_B(32));// 32. x3y3 x2y2 reg_cc_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(33, M23_TNL_DFT_B(33));// 33. x1y1 x0y0 reg_cc_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(34, M23_TNL_DFT_B(34));// 34. x5y5 x4y4 reg_ne_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(35, M23_TNL_DFT_B(35));// 35. x3y3 x2y2 reg_ne_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(36, M23_TNL_DFT_B(36));// 36. x1y1 x0y0 reg_ne_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(37, M23_TNL_DFT_B(37));// 37. eg_skin_gain_ctrl_yy
							PE_NRD_HW_M23_TNL_WR32(38, M23_TNL_DFT_B(38));// 38. eg_skin_gain_ctrl_cb
							PE_NRD_HW_M23_TNL_WR32(39, M23_TNL_DFT_B(39));// 39. eg_skin_gain_ctrl_cr
							PE_NRD_HW_M23_TNL_WR32(40, M23_TNL_DFT_B(40));// 40. eg_skin_motion_ctrl
							PE_NRD_HW_M23_TNL_WR32(41, p_db[41].data  );// 41. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_NRD_HW_M23_TNL_WR32(42, p_db[42].data  );// 42. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_NRD_HW_M23_TNL_WR32(43, p_db[43].data  );// 43. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_NRD_HW_M23_TNL_WR32(44, p_db[44].data  );// 44. x1y1 x0y0 reg_simple_ma_iir_pt
						}
						else
						{
							PE_NRD_HW_M23_TNL_WR32(00, M23_TNL_DFT_B(00));// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M23_TNL_WR32(01, M23_TNL_DFT_B(01));// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M23_TNL_WR32(02, M23_TNL_DFT_B(02));// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M23_TNL_WR32(03, M23_TNL_DFT_B(03));// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
							PE_NRD_HW_M23_TNL_WR32(04, M23_TNL_DFT_B(04));// 04. x5y5 x4y4 reg_p2_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(05, M23_TNL_DFT_B(05));// 05. x3y3 x2y2 reg_p2_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(06, M23_TNL_DFT_B(06));// 06. x1y1 x0y0 reg_p2_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(07, p_lut[0]       );// 07. x7y7 x6y6 reg_detail_iir_pt
							PE_NRD_HW_M23_TNL_WR32(08, p_lut[1]       );// 08. x5y5 x4y4 reg_detail_iir_pt
							PE_NRD_HW_M23_TNL_WR32(09, p_lut[2]       );// 09. x3y3 x2y2 reg_detail_iir_pt
							PE_NRD_HW_M23_TNL_WR32(10, p_lut[3]       );// 10. x1y1 x0y0 reg_detail_iir_pt
							PE_NRD_HW_M23_TNL_WR32(11, p_lut[4]       );// 11. x7y7 x6y6 reg_detail_cir_pt
							PE_NRD_HW_M23_TNL_WR32(12, p_lut[5]       );// 12. x5y5 x4y4 reg_detail_cir_pt
							PE_NRD_HW_M23_TNL_WR32(13, p_lut[6]       );// 13. x3y3 x2y2 reg_detail_cir_pt
							PE_NRD_HW_M23_TNL_WR32(14, p_lut[7]       );// 14. x1y1 x0y0 reg_detail_cir_pt
							PE_NRD_HW_M23_TNL_WR32(15, p_lut[8]       );// 15. x7y7 x6y6 reg_flat_iir_pt
							PE_NRD_HW_M23_TNL_WR32(16, p_lut[9]       );// 16. x5y5 x4y4 reg_flat_iir_pt
							PE_NRD_HW_M23_TNL_WR32(17, p_lut[10]      );// 17. x3y3 x2y2 reg_flat_iir_pt
							PE_NRD_HW_M23_TNL_WR32(18, p_lut[11]      );// 18. x1y1 x0y0 reg_flat_iir_pt
							PE_NRD_HW_M23_TNL_WR32(19, p_lut[12]      );// 19. x7y7 x6y6 reg_flat_cir_pt
							PE_NRD_HW_M23_TNL_WR32(20, p_lut[13]      );// 20. x5y5 x4y4 reg_flat_cir_pt
							PE_NRD_HW_M23_TNL_WR32(21, p_lut[14]      );// 21. x3y3 x2y2 reg_flat_cir_pt
							PE_NRD_HW_M23_TNL_WR32(22, p_lut[15]      );// 22. x1y1 x0y0 reg_flat_cir_pt
							PE_NRD_HW_M23_TNL_WR32(23, M23_TNL_DFT_B(23));// 23. x1y1 x0y0 reg_luma_gain_ctrl
							PE_NRD_HW_M23_TNL_WR32(24, M23_TNL_DFT_B(24));// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
							PE_NRD_HW_M23_TNL_WR32(25, M23_TNL_DFT_B(25));// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
							PE_NRD_HW_M23_TNL_WR32(26, M23_TNL_DFT_B(26));// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
							PE_NRD_HW_M23_TNL_WR32(27, M23_TNL_DFT_B(27));// 27. x1y1 x0y0 reg_skin_motion_ctrl
							PE_NRD_HW_M23_TNL_WR32(28, M23_TNL_DFT_B(28));// 28. reg_detail_luma_ctrl
							PE_NRD_HW_M23_TNL_WR32(29, M23_TNL_DFT_B(29));// 29. x3y3 x2y2 reg_NLM_Protect
							PE_NRD_HW_M23_TNL_WR32(30, M23_TNL_DFT_B(30));// 30. x1y1 x0y0 reg_NLM_Protect
							PE_NRD_HW_M23_TNL_WR32(31, M23_TNL_DFT_B(31));// 31. x5y5 x4y4 reg_cc_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(32, M23_TNL_DFT_B(32));// 32. x3y3 x2y2 reg_cc_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(33, M23_TNL_DFT_B(33));// 33. x1y1 x0y0 reg_cc_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(34, M23_TNL_DFT_B(34));// 34. x5y5 x4y4 reg_ne_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(35, M23_TNL_DFT_B(35));// 35. x3y3 x2y2 reg_ne_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(36, M23_TNL_DFT_B(36));// 36. x1y1 x0y0 reg_ne_dist_max_pt
							PE_NRD_HW_M23_TNL_WR32(37, M23_TNL_DFT_B(37));// 37. eg_skin_gain_ctrl_yy
							PE_NRD_HW_M23_TNL_WR32(38, M23_TNL_DFT_B(38));// 38. eg_skin_gain_ctrl_cb
							PE_NRD_HW_M23_TNL_WR32(39, M23_TNL_DFT_B(39));// 39. eg_skin_gain_ctrl_cr
							PE_NRD_HW_M23_TNL_WR32(40, M23_TNL_DFT_B(40));// 40. eg_skin_motion_ctrl
							PE_NRD_HW_M23_TNL_WR32(41, p_db[41].data  );// 41. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_NRD_HW_M23_TNL_WR32(42, p_db[42].data  );// 42. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_NRD_HW_M23_TNL_WR32(43, p_db[43].data  );// 43. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_NRD_HW_M23_TNL_WR32(44, p_db[44].data  );// 44. x1y1 x0y0 reg_simple_ma_iir_pt
						}
					}
					PE_ND0_M23_QWr(tnr_main_lut_00, 0x00008000);
					/* save prev values */
					memcpy(&(pInfo->tnr0_cmn), pp, sizeof(LX_PE_NRD_TNR1_CMN_T));
					/* download tnr user db */
					ret = PE_NRD_HW_M23_DownloadTnrUserDb((void *)pp);
					PE_NRD_HW_M23_CHECK_CODE(ret, break, \
						"PE_NRD_HW_M23_DownloadTnrUserDb() error.\n");
					PE_DBG_NRD("set tnr lut by driver\n");
				}
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_NRD_HW_M23_GetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	__attribute__((unused)) PE_NRD_HW_M23_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m23_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			UINT32 *pd;
			LX_PE_NRD_TNR_CMN_T *ctrl_param =(LX_PE_NRD_TNR_CMN_T *)pstParams;
			LX_PE_NRD_TNR1_CMN_T *pp = (LX_PE_NRD_TNR1_CMN_T *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				memcpy(pp, &(pInfo->tnr0_cmn), sizeof(LX_PE_NRD_TNR1_CMN_T));
			}
			pd = (typeof(*pd) *)pp->tnr0__lut;
			PE_DBG_NRD("[%d]tnr0___en:%d\n", pp->win_id, pp->tnr0___en);
			PE_DBG_NRD( \
			"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = (typeof(*pd) *)pp->tnr0_gain;
			PE_DBG_NRD(\
			"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = (typeof(*pd) *)pp->tnr0_buff;
			PE_DBG_NRD(\
			"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],	pd[12], pd[13], pd[14]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR7_DETAIL_T M23
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_SetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	__attribute__((unused)) PE_NRD_HW_M23_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m23_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_TNR_DETAIL_T *ctrl_param =(LX_PE_NRD_TNR_DETAIL_T *)pstParams;
			LX_PE_NRD_TNR2_DETAIL_T *pp = (LX_PE_NRD_TNR2_DETAIL_T *)ctrl_param->data;
			static LX_PE_NRD_TNR2_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR2_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR2_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			pd = (typeof(*pd) *)pp->tnr0__ctl;
			PE_DBG_NRD("set[%d] : tnr0__ctl\n"
			"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__ctl	  [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);

			pd = (typeof(*pd) *)pp->tnr0___ma;
			PE_DBG_NRD("set[%d] : tnr0___ma\n"
			"tnr0___ma    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			
			pd = (typeof(*pd) *)pp->tnr0___me;
			PE_DBG_NRD("set[%d] : tnr0___me\n"
			"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = (typeof(*pd) *)pp->tnr0__mlb;
			PE_DBG_NRD("set[%d] : tnr0__mlb\n"
			"tnr0__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);

			pd16 = pp->tnr0___mc;
			PE_DBG_NRD("set[%d] : tnr0___mc\n"
			"tnr0___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0___mc	  [30]0x%02X,\n",\
			pp->win_id, \
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
			pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
			pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
			pd16[30]);

			pd = (typeof(*pd) *)pp->tnr0_blnd;
			PE_DBG_NRD("set[%d] : tnr0_blnd\n"
			"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/*tnr0__ctl*/
				/*set tnr_ctrl_00 @ dummy reg(nd_fsw_ctrl_03) bc racing issue with f/w */
				PE_ND0_M23_QWr04(nd_fsw_ctrl_03,			reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr0__ctl[0],0,8),\
															reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr0__ctl[1],0,1),\
															reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr0__ctl[2],0,1),\
															reg_sad_8x3_res,		GET_BITS(pp->tnr0__ctl[3],0,2));
				PE_NRD_HW_M23_TNR0_SET_USER(tnr_ctrl_00,	reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr0__ctl[0],0,8));
				PE_NRD_HW_M23_TNR0_SET_USER(tnr_ctrl_00,	reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr0__ctl[1],0,1));
				PE_NRD_HW_M23_TNR0_SET_USER(tnr_ctrl_00,	reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr0__ctl[2],0,1));
				PE_NRD_HW_M23_TNR0_SET_USER(tnr_ctrl_00,	reg_sad_8x3_res,		GET_BITS(pp->tnr0__ctl[3],0,2));
				PE_NRD_HW_M23_TNR0_WR10(tnr_ctrl_02,		sc_th_memc, GET_BITS(pp->tnr0__ctl[4],0,8),\
															sc_th_ma,	GET_BITS(pp->tnr0__ctl[5],0,8),\
															sc_out_mode,	GET_BITS(pp->tnr0__ctl[6],0,1),\
															sc_chroma_gain, GET_BITS(pp->tnr0__ctl[7],0,3),\
															sc_max_flt_tap, GET_BITS(pp->tnr0__ctl[8],0,3),\
															sc_scale,	GET_BITS(pp->tnr0__ctl[9],0,3),\
															sc_chroma_en,	GET_BITS(pp->tnr0__ctl[10],0,1),\
															sc_calc_prev_hist,	GET_BITS(pp->tnr0__ctl[11],0,1),\
															sc_max_flt_en,	GET_BITS(pp->tnr0__ctl[12],0,1),\
															sc_en,	GET_BITS(pp->tnr0__ctl[13],0,1));
				PE_NRD_HW_M23_TNR0_WR04(tnr_ctrl_05,		reg_mamc_mc_sad_cut,	GET_BITS(pp->tnr0__ctl[14],0,1),\
															reg_mamc_ma_sad_cut,	GET_BITS(pp->tnr0__ctl[15],0,1),\
															reg_mamc_blend_mv_max_or_sum,	GET_BITS(pp->tnr0__ctl[16],0,1),\
															reg_mamc_blend_mode,	GET_BITS(pp->tnr0__ctl[17],0,2));
				PE_NRD_HW_M23_TNR0_WR02(tnr_ctrl_06,		reg_me_pv_base, GET_BITS(pp->tnr0__ctl[18],0,8),\
															reg_me_lb_base, GET_BITS(pp->tnr0__ctl[19],0,8));
				PE_NRD_HW_M23_TNR0_WR01(tnr_ctrl_21,		reg_svar_scale, GET_BITS(pp->tnr0__ctl[20],0,3));
				/*tnr0___ma*/
				PE_NRD_HW_M23_TNR0_WR02(tnr_ctrl_07,		reg_sc_en,	GET_BITS(pp->tnr0___ma[0],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr0___ma[1],0,2));
				/*tnr0___me*/
				PE_NRD_HW_M23_TNR0_WR03(tnr_ctrl_09,		reg_pv_smooth_clip, GET_BITS(pp->tnr0___me[0],0,6),\
															reg_lb_smooth_clip, GET_BITS(pp->tnr0___me[1],0,6),\
															reg_sad_base,	GET_BITS(pp->tnr0___me[2],0,7));
				PE_NRD_HW_M23_TNR0_WR03(tnr_ctrl_11,		reg_me_n15_protection,	GET_BITS(pp->tnr0___me[3],0,1),\
															pv_smooth_en,	GET_BITS(pp->tnr0___me[4],0,1),\
															lb_smooth_en,	GET_BITS(pp->tnr0___me[5],0,1));
				PE_NRD_HW_M23_TNR0_WR02(tnr_ctrl_13,		reg_zero_sad_adv,	GET_BITS(pp->tnr0___me[6],0,1),\
															reg_zero_sad_ratio, GET_BITS(pp->tnr0___me[7],0,8));

				/*tnr0__mlb*/
				PE_NRD_HW_M23_TNR0_WR01(tnr_ctrl_16,	reg_sad_acc_mode,	GET_BITS(pp->tnr0__mlb[0],0,2));
				PE_NRD_HW_M23_TNR0_WR09(tnr_ctrl_18,	reg_bmv_pmv_tl_en,	GET_BITS(pp->tnr0__mlb[1],0,1),\
														reg_bmv_pmv_tl, 	GET_BITS(pp->tnr0__mlb[2],0,7),\
														reg_bmv_gmv_tl_en,	GET_BITS(pp->tnr0__mlb[3],0,1),\
														reg_bmv_gmv_tl, 	GET_BITS(pp->tnr0__mlb[4],0,7),\
														reg_gmv_gmv_tl_en,	GET_BITS(pp->tnr0__mlb[5],0,1),\
														reg_gmv_gmv_tl,		GET_BITS(pp->tnr0__mlb[6],0,7),\
														reg_gsad_scale,		GET_BITS(pp->tnr0__mlb[7],0,3),\
														reg_bmv_rst_mode,   GET_BITS(pp->tnr0__mlb[8],0,1),\
														reg_bsad_scale,		GET_BITS(pp->tnr0__mlb[9],0,3));
				PE_NRD_HW_M23_TNR0_WR05(tnr_ctrl_19,	bmv_0mv_tl_en,		GET_BITS(pp->tnr0__mlb[10],0,1),\
														bmv_0mv_tl,			GET_BITS(pp->tnr0__mlb[11],0,7),\
														gmv_0mv_tl_en,		GET_BITS(pp->tnr0__mlb[12],0,1),\
														gmv_0mv_tl,			GET_BITS(pp->tnr0__mlb[13],0,7),\
														bmv_coring_th,		GET_BITS(pp->tnr0__mlb[14],0,8));

				/*tnr0__mc*/
				PE_NRD_HW_M23_TNR0_WR09(tnr_ctrl_24,		reg_chroma_sad_en,	GET_BITS(pp->tnr0___mc[0],0,1),\
															reg_cnt_mode,	GET_BITS(pp->tnr0___mc[1],0,3),\
															reg_avg_cmp_res,	GET_BITS(pp->tnr0___mc[2],0,3),\
															reg_avg_cmp_en, GET_BITS(pp->tnr0___mc[3],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr0___mc[4],0,2),\
															reg_chroma_sad_res, GET_BITS(pp->tnr0___mc[5],0,2),\
															reg_crgn_gain_en,	GET_BITS(pp->tnr0___mc[6],0,1),\
															reg_luma_gain_en,	GET_BITS(pp->tnr0___mc[7],0,1),\
															reg_ombc_en,	GET_BITS(pp->tnr0___mc[8],0,1));
				PE_NRD_HW_M23_TNR0_WR03(tnr_ctrl_26,		reg_tnr_final_lut_yy_x3,	GET_BITS(pp->tnr0___mc[9],0,10),\
															reg_tnr_final_lut_yy_y3,	GET_BITS(pp->tnr0___mc[10],0,10),\
															reg_tnr_final_lut_yy_x2,	GET_BITS(pp->tnr0___mc[11],0,10));
				PE_NRD_HW_M23_TNR0_WR03(tnr_ctrl_27,		reg_tnr_final_lut_yy_y2,	GET_BITS(pp->tnr0___mc[12],0,10),\
															reg_tnr_final_lut_yy_x1,	GET_BITS(pp->tnr0___mc[13],0,10),\
															reg_tnr_final_lut_yy_y1,	GET_BITS(pp->tnr0___mc[14],0,10));
				PE_NRD_HW_M23_TNR0_WR02(tnr_ctrl_28,		reg_tnr_final_lut_yy_x0,	GET_BITS(pp->tnr0___mc[15],0,10),\
															reg_tnr_final_lut_yy_y0,	GET_BITS(pp->tnr0___mc[16],0,10));
				PE_NRD_HW_M23_TNR0_WR03(tnr_ctrl_29,		reg_tnr_final_lut_cb_x3,	GET_BITS(pp->tnr0___mc[17],0,10),\
															reg_tnr_final_lut_cb_y3,	GET_BITS(pp->tnr0___mc[18],0,10),\
															reg_tnr_final_lut_cb_x2,	GET_BITS(pp->tnr0___mc[19],0,10));
				PE_NRD_HW_M23_TNR0_WR03(tnr_ctrl_30,		reg_tnr_final_lut_cb_y2,	GET_BITS(pp->tnr0___mc[20],0,10),\
															reg_tnr_final_lut_cb_x1,	GET_BITS(pp->tnr0___mc[21],0,10),\
															reg_tnr_final_lut_cb_y1,	GET_BITS(pp->tnr0___mc[22],0,10));
				PE_NRD_HW_M23_TNR0_WR02(tnr_ctrl_31,		reg_tnr_final_lut_cb_x0,	GET_BITS(pp->tnr0___mc[23],0,10),\
															reg_tnr_final_lut_cb_y0,	GET_BITS(pp->tnr0___mc[24],0,10));
				PE_NRD_HW_M23_TNR0_WR02(tnr_ctrl_32,		reg_blur_coef,	GET_BITS(pp->tnr0___mc[25],0,8),\
															reg_gf_gain,	GET_BITS(pp->tnr0___mc[26],0,8));
				PE_NRD_HW_M23_TNR0_WR04(tnr_ctrl_33,		reg_move_step,	GET_BITS(pp->tnr0___mc[27],0,8),\
															reg_same_sad_th,	GET_BITS(pp->tnr0___mc[28],0,8),\
															reg_p_mv0_only, GET_BITS(pp->tnr0___mc[29],0,1),\
															same_protection_en, GET_BITS(pp->tnr0___mc[30],0,1));

				/*tnr0_blnd*/

				PE_NRD_HW_M23_TNR0_WR04(tnr_ctrl_56,		reg_sad_mc_ctrl_pt_x1,	GET_BITS(pp->tnr0_blnd[0],0,8),\
															reg_sad_mc_ctrl_pt_y1,	GET_BITS(pp->tnr0_blnd[1],0,8),\
															reg_sad_mc_ctrl_pt_x0,	GET_BITS(pp->tnr0_blnd[2],0,8),\
															reg_sad_mc_ctrl_pt_y0,	GET_BITS(pp->tnr0_blnd[3],0,8));
				PE_NRD_HW_M23_TNR0_WR04(tnr_ctrl_57,		reg_sad_mc_ctrl_pt_x3,	GET_BITS(pp->tnr0_blnd[4],0,8),\
															reg_sad_mc_ctrl_pt_y3,	GET_BITS(pp->tnr0_blnd[5],0,8),\
															reg_sad_mc_ctrl_pt_x2,	GET_BITS(pp->tnr0_blnd[6],0,8),\
															reg_sad_mc_ctrl_pt_y2,	GET_BITS(pp->tnr0_blnd[7],0,8));
				PE_NRD_HW_M23_TNR0_WR04(tnr_ctrl_58,		reg_abs_mv_ctrl_pt_x1,	GET_BITS(pp->tnr0_blnd[8],0,8),\
															reg_abs_mv_ctrl_pt_y1,	GET_BITS(pp->tnr0_blnd[9],0,8),\
															reg_abs_mv_ctrl_pt_x0,	GET_BITS(pp->tnr0_blnd[10],0,8),\
															reg_abs_mv_ctrl_pt_y0,	GET_BITS(pp->tnr0_blnd[11],0,8));
				PE_NRD_HW_M23_TNR0_WR04(tnr_ctrl_59,		reg_abs_mv_ctrl_pt_x3,	GET_BITS(pp->tnr0_blnd[12],0,8),\
															reg_abs_mv_ctrl_pt_y3,	GET_BITS(pp->tnr0_blnd[13],0,8),\
															reg_abs_mv_ctrl_pt_x2,	GET_BITS(pp->tnr0_blnd[14],0,8),\
															reg_abs_mv_ctrl_pt_y2,	GET_BITS(pp->tnr0_blnd[15],0,8));
				PE_NRD_HW_M23_TNR0_WR04(tnr_ctrl_60,		reg_sad_ma_ctrl_pt_x1,	GET_BITS(pp->tnr0_blnd[16],0,8),\
															reg_sad_ma_ctrl_pt_y1,	GET_BITS(pp->tnr0_blnd[17],0,8),\
															reg_sad_ma_ctrl_pt_x0,	GET_BITS(pp->tnr0_blnd[18],0,8),\
															reg_sad_ma_ctrl_pt_y0,	GET_BITS(pp->tnr0_blnd[19],0,8));
				PE_NRD_HW_M23_TNR0_WR04(tnr_ctrl_61,		reg_sad_ma_ctrl_pt_x3,	GET_BITS(pp->tnr0_blnd[20],0,8),\
															reg_sad_ma_ctrl_pt_y3,	GET_BITS(pp->tnr0_blnd[21],0,8),\
															reg_sad_ma_ctrl_pt_x2,	GET_BITS(pp->tnr0_blnd[22],0,8),\
															reg_sad_ma_ctrl_pt_y2,	GET_BITS(pp->tnr0_blnd[23],0,8));

			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR7_DETAIL_T
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_GetTnrDetailCtrl(void *pstParams)
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
int PE_NRD_HW_M23_SetTnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	//const PE_REG_PARAM_T *p_db = NULL;
	//PE_INF_M23_SETTINGS_T inf_set;
	//LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	//PE_TNL_HW_PARAM_REG_M23_T *p_tnl_dflt = _g_pe_tnl_hw_param_data_m23.reg_dflt.data;
	__attribute__((unused)) PE_NRD_HW_M23_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m23_info;
	//#define M23_TNL_DFT(_num)	(p_tnl_dflt->tnr_lut_##_num.main_lut_indir_data0)
	//PE_TNL_HW_PARAM_REG_M23_T *p_tnl_dflt_b = _g_pe_tnl_hw_param_data_m23.reg_dflt.data;
	//#define M23_TNL_DFT_B(_num)	(p_tnl_dflt_b->tnr_lut_##_num.main_lut_indir_data0)
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_TNR2ND_CMN_T *ctrl_param =(LX_PE_NRD_TNR2ND_CMN_T *)pstParams;
			LX_PE_NRD_TNR2ND2_CMN_T *pp = (LX_PE_NRD_TNR2ND2_CMN_T *)ctrl_param->data;
			static LX_PE_NRD_TNR2ND2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR2ND2_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR2ND2_CMN_T\n");
				ret=RET_OK;
				break;
			}
			{
			UINT32 *pd = (typeof(*pd) *)pp->tnr1__lut;
			PE_DBG_NRD("[%d]tnr1___en:%d\n", pp->win_id, pp->tnr1___en);
			PE_DBG_NRD( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = (typeof(*pd) *)pp->tnr1_gain;
			PE_DBG_NRD(\
			"tnr_lut_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = (typeof(*pd) *)pp->tnr1_buff;
			PE_DBG_NRD(\
			"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],	pd[12], pd[13], pd[14]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* skip drv tnr ctrl, if fw tnr on. */
				if (1)//PE_CMN_HW_M23_GetDbInfo(PE_CMN_HW_M23_DB_INF_MD0_TNR_FW_EN, 0))
				{
					/* save prev values */
					memcpy(&(pInfo->tnr1_cmn), pp, sizeof(LX_PE_NRD_TNR2ND2_CMN_T));
					/* download tnr user db */
					ret = PE_NRD_HW_M23_DownloadTnr2ndUserDb((void *)pp);
					PE_NRD_HW_M23_CHECK_CODE(ret, break, \
						"PE_NRD_HW_M23_DownloadTnr2ndUserDb() error.\n");
					PE_DBG_NRD("set tnr lut by firmware\n");
				}
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get tnr common ctrl
 * - use input struct LX_PE_NRD_TNR5_CMN_T
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_GetTnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	LX_PE_WIN_ID win_id;
	__attribute__((unused)) PE_NRD_HW_M23_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m23_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_TNR2ND_CMN_T *ctrl_param =(LX_PE_NRD_TNR_DETAIL_T *)pstParams;
			LX_PE_NRD_TNR2ND2_CMN_T *pp = (LX_PE_NRD_TNR2ND2_CMN_T *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				memcpy(pp, &(pInfo->tnr1_cmn), sizeof(LX_PE_NRD_TNR2ND2_CMN_T));
			}
			{
			UINT32 *pd = (typeof(*pd) *)pp->tnr1__lut;
			PE_DBG_NRD("[%d]tnr1___en:%d\n", pp->win_id, pp->tnr1___en);
			PE_DBG_NRD( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = (typeof(*pd) *)pp->tnr1_gain;
			PE_DBG_NRD(\
			"tnr1_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = (typeof(*pd) *)pp->tnr1_buff;
			PE_DBG_NRD(\
			"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11], pd[12], pd[13], pd[14]);
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR7_DETAIL_T M23
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_SetTnr2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	__attribute__((unused)) PE_NRD_HW_M23_SETTINGS_T *pInfo = &_g_pe_nrd_hw_m23_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_TNR2ND_DETAIL_T *ctrl_param =(LX_PE_NRD_TNR2ND_DETAIL_T *)pstParams;
			LX_PE_NRD_TNR2ND3_DETAIL_T *pp = (LX_PE_NRD_TNR2ND3_DETAIL_T *)ctrl_param->data;
			static LX_PE_NRD_TNR2ND3_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR2ND3_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR2ND3_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			pd = (typeof(*pd) *)pp->tnr1__ctl;
			PE_DBG_NRD("set[%d] : tnr1__ctl\n"
			"tnr1__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1__ctl	  [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);

			pd = (typeof(*pd) *)pp->tnr1___ma;
			PE_DBG_NRD("set[%d] : tnr1___ma\n"
			"tnr1___ma    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			
			pd = (typeof(*pd) *)pp->tnr1___me;
			PE_DBG_NRD("set[%d] : tnr1___me\n"
			"tnr1___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = (typeof(*pd) *)pp->tnr1__mlb;
			PE_DBG_NRD("set[%d] : tnr1__mlb\n"
			"tnr1__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);

			pd16 = pp->tnr1___mc;
			PE_DBG_NRD("set[%d] : tnr1___mc\n"
			"tnr1___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1___mc	  [30]0x%02X,\n",\
			pp->win_id, \
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
			pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
			pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
			pd16[30]);

			pd = (typeof(*pd) *)pp->tnr1_blnd;
			PE_DBG_NRD("set[%d] : tnr1_blnd\n"
			"tnr1_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/*tnr1__ctl*/
				#if 0
				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_00,		reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8),\
															reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1),\
															reg_sad_8x3_iir_en, GET_BITS(pp->tnr1__ctl[2],0,1),\
															reg_sad_8x3_res,	GET_BITS(pp->tnr1__ctl[3],0,2));
				#endif
				
				/*set tnr_ctrl_00 @ dummy reg(nd_fsw_ctrl_03) bc racing issue with f/w */
				PE_ND1_M23_QWr04(nd_fsw_ctrl_03,			reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8),\
															reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1),\
															reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr1__ctl[2],0,1),\
															reg_sad_8x3_res,		GET_BITS(pp->tnr1__ctl[3],0,2));
				PE_NRD_HW_M23_TNR1_SET_USER(tnr_ctrl_00,	reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8));
				PE_NRD_HW_M23_TNR1_SET_USER(tnr_ctrl_00,	reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1));
				PE_NRD_HW_M23_TNR1_SET_USER(tnr_ctrl_00,	reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr1__ctl[2],0,1));
				PE_NRD_HW_M23_TNR1_SET_USER(tnr_ctrl_00,	reg_sad_8x3_res,		GET_BITS(pp->tnr1__ctl[3],0,2));
				PE_NRD_HW_M23_TNR1_WR10(tnr_ctrl_02,		sc_th_memc, GET_BITS(pp->tnr1__ctl[4],0,8),\
															sc_th_ma,	GET_BITS(pp->tnr1__ctl[5],0,8),\
															sc_out_mode,	GET_BITS(pp->tnr1__ctl[6],0,1),\
															sc_chroma_gain, GET_BITS(pp->tnr1__ctl[7],0,3),\
															sc_max_flt_tap, GET_BITS(pp->tnr1__ctl[8],0,3),\
															sc_scale,	GET_BITS(pp->tnr1__ctl[9],0,3),\
															sc_chroma_en,	GET_BITS(pp->tnr1__ctl[10],0,1),\
															sc_calc_prev_hist,	GET_BITS(pp->tnr1__ctl[11],0,1),\
															sc_max_flt_en,	GET_BITS(pp->tnr1__ctl[12],0,1),\
															sc_en,	GET_BITS(pp->tnr1__ctl[13],0,1));
				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_05,		reg_mamc_mc_sad_cut,	GET_BITS(pp->tnr1__ctl[14],0,1),\
															reg_mamc_ma_sad_cut,	GET_BITS(pp->tnr1__ctl[15],0,1),\
															reg_mamc_blend_mv_max_or_sum,	GET_BITS(pp->tnr1__ctl[16],0,1),\
															reg_mamc_blend_mode,	GET_BITS(pp->tnr1__ctl[17],0,2));
				PE_NRD_HW_M23_TNR1_WR02(tnr_ctrl_06,		reg_me_pv_base, GET_BITS(pp->tnr1__ctl[18],0,8),\
															reg_me_lb_base, GET_BITS(pp->tnr1__ctl[19],0,8));
				PE_NRD_HW_M23_TNR1_WR01(tnr_ctrl_21,		reg_svar_scale, GET_BITS(pp->tnr1__ctl[20],0,3));
				/*tnr1___ma*/
				PE_NRD_HW_M23_TNR1_WR02(tnr_ctrl_07,		reg_sc_en,	GET_BITS(pp->tnr1___ma[0],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr1___ma[1],0,2));
				/*tnr1___me*/
				PE_NRD_HW_M23_TNR1_WR03(tnr_ctrl_09,		reg_pv_smooth_clip, GET_BITS(pp->tnr1___me[0],0,6),\
															reg_lb_smooth_clip, GET_BITS(pp->tnr1___me[1],0,6),\
															reg_sad_base,	GET_BITS(pp->tnr1___me[2],0,7));
				PE_NRD_HW_M23_TNR1_WR03(tnr_ctrl_11,		reg_me_n15_protection,	GET_BITS(pp->tnr1___me[3],0,1),\
															pv_smooth_en,	GET_BITS(pp->tnr1___me[4],0,1),\
															lb_smooth_en,	GET_BITS(pp->tnr1___me[5],0,1));
				PE_NRD_HW_M23_TNR1_WR02(tnr_ctrl_13,		reg_zero_sad_adv,	GET_BITS(pp->tnr1___me[6],0,1),\
															reg_zero_sad_ratio, GET_BITS(pp->tnr1___me[7],0,8));

				/*tnr1__mlb*/
				PE_NRD_HW_M23_TNR1_WR01(tnr_ctrl_16,	reg_sad_acc_mode,	GET_BITS(pp->tnr1__mlb[0],0,2));
				PE_NRD_HW_M23_TNR1_WR09(tnr_ctrl_18,	reg_bmv_pmv_tl_en,	GET_BITS(pp->tnr1__mlb[1],0,1),\
														reg_bmv_pmv_tl, 	GET_BITS(pp->tnr1__mlb[2],0,7),\
														reg_bmv_gmv_tl_en,	GET_BITS(pp->tnr1__mlb[3],0,1),\
														reg_bmv_gmv_tl, 	GET_BITS(pp->tnr1__mlb[4],0,7),\
														reg_gmv_gmv_tl_en,	GET_BITS(pp->tnr1__mlb[5],0,1),\
														reg_gmv_gmv_tl,		GET_BITS(pp->tnr1__mlb[6],0,7),\
														reg_gsad_scale,		GET_BITS(pp->tnr1__mlb[7],0,3),\
														reg_bmv_rst_mode,   GET_BITS(pp->tnr1__mlb[8],0,1),\
														reg_bsad_scale,		GET_BITS(pp->tnr1__mlb[9],0,3));
				PE_NRD_HW_M23_TNR1_WR05(tnr_ctrl_19,	bmv_0mv_tl_en,		GET_BITS(pp->tnr1__mlb[10],0,1),\
														bmv_0mv_tl,			GET_BITS(pp->tnr1__mlb[11],0,7),\
														gmv_0mv_tl_en,		GET_BITS(pp->tnr1__mlb[12],0,1),\
														gmv_0mv_tl,			GET_BITS(pp->tnr1__mlb[13],0,7),\
														bmv_coring_th,		GET_BITS(pp->tnr1__mlb[14],0,8));

				/*tnr1__mc*/
				PE_NRD_HW_M23_TNR1_WR09(tnr_ctrl_24,		reg_chroma_sad_en,	GET_BITS(pp->tnr1___mc[0],0,1),\
															reg_cnt_mode,	GET_BITS(pp->tnr1___mc[1],0,3),\
															reg_avg_cmp_res,	GET_BITS(pp->tnr1___mc[2],0,3),\
															reg_avg_cmp_en, GET_BITS(pp->tnr1___mc[3],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr1___mc[4],0,2),\
															reg_chroma_sad_res, GET_BITS(pp->tnr1___mc[5],0,2),\
															reg_crgn_gain_en,	GET_BITS(pp->tnr1___mc[6],0,1),\
															reg_luma_gain_en,	GET_BITS(pp->tnr1___mc[7],0,1),\
															reg_ombc_en,	GET_BITS(pp->tnr1___mc[8],0,1));
				PE_NRD_HW_M23_TNR1_WR03(tnr_ctrl_26,		reg_tnr_final_lut_yy_x3,	GET_BITS(pp->tnr1___mc[9],0,10),\
															reg_tnr_final_lut_yy_y3,	GET_BITS(pp->tnr1___mc[10],0,10),\
															reg_tnr_final_lut_yy_x2,	GET_BITS(pp->tnr1___mc[11],0,10));
				PE_NRD_HW_M23_TNR1_WR03(tnr_ctrl_27,		reg_tnr_final_lut_yy_y2,	GET_BITS(pp->tnr1___mc[12],0,10),\
															reg_tnr_final_lut_yy_x1,	GET_BITS(pp->tnr1___mc[13],0,10),\
															reg_tnr_final_lut_yy_y1,	GET_BITS(pp->tnr1___mc[14],0,10));
				PE_NRD_HW_M23_TNR1_WR02(tnr_ctrl_28,		reg_tnr_final_lut_yy_x0,	GET_BITS(pp->tnr1___mc[15],0,10),\
															reg_tnr_final_lut_yy_y0,	GET_BITS(pp->tnr1___mc[16],0,10));
				PE_NRD_HW_M23_TNR1_WR03(tnr_ctrl_29,		reg_tnr_final_lut_cb_x3,	GET_BITS(pp->tnr1___mc[17],0,10),\
															reg_tnr_final_lut_cb_y3,	GET_BITS(pp->tnr1___mc[18],0,10),\
															reg_tnr_final_lut_cb_x2,	GET_BITS(pp->tnr1___mc[19],0,10));
				PE_NRD_HW_M23_TNR1_WR03(tnr_ctrl_30,		reg_tnr_final_lut_cb_y2,	GET_BITS(pp->tnr1___mc[20],0,10),\
															reg_tnr_final_lut_cb_x1,	GET_BITS(pp->tnr1___mc[21],0,10),\
															reg_tnr_final_lut_cb_y1,	GET_BITS(pp->tnr1___mc[22],0,10));
				PE_NRD_HW_M23_TNR1_WR02(tnr_ctrl_31,		reg_tnr_final_lut_cb_x0,	GET_BITS(pp->tnr1___mc[23],0,10),\
															reg_tnr_final_lut_cb_y0,	GET_BITS(pp->tnr1___mc[24],0,10));
				PE_NRD_HW_M23_TNR1_WR02(tnr_ctrl_32,		reg_blur_coef,	GET_BITS(pp->tnr1___mc[25],0,8),\
															reg_gf_gain,	GET_BITS(pp->tnr1___mc[26],0,8));
				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_33,		reg_move_step,	GET_BITS(pp->tnr1___mc[27],0,8),\
															reg_same_sad_th,	GET_BITS(pp->tnr1___mc[28],0,8),\
															reg_p_mv0_only, GET_BITS(pp->tnr1___mc[29],0,1),\
															same_protection_en, GET_BITS(pp->tnr1___mc[30],0,1));

				/*tnr1_blnd*/

				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_56,		reg_sad_mc_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[0],0,8),\
															reg_sad_mc_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[1],0,8),\
															reg_sad_mc_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[2],0,8),\
															reg_sad_mc_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[3],0,8));
				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_57,		reg_sad_mc_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[4],0,8),\
															reg_sad_mc_ctrl_pt_y3,	GET_BITS(pp->tnr1_blnd[5],0,8),\
															reg_sad_mc_ctrl_pt_x2,	GET_BITS(pp->tnr1_blnd[6],0,8),\
															reg_sad_mc_ctrl_pt_y2,	GET_BITS(pp->tnr1_blnd[7],0,8));
				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_58,		reg_abs_mv_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[8],0,8),\
															reg_abs_mv_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[9],0,8),\
															reg_abs_mv_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[10],0,8),\
															reg_abs_mv_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[11],0,8));
				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_59,		reg_abs_mv_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[12],0,8),\
															reg_abs_mv_ctrl_pt_y3,	GET_BITS(pp->tnr1_blnd[13],0,8),\
															reg_abs_mv_ctrl_pt_x2,	GET_BITS(pp->tnr1_blnd[14],0,8),\
															reg_abs_mv_ctrl_pt_y2,	GET_BITS(pp->tnr1_blnd[15],0,8));
				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_60,		reg_sad_ma_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[16],0,8),\
															reg_sad_ma_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[17],0,8),\
															reg_sad_ma_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[18],0,8),\
															reg_sad_ma_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[19],0,8));
				PE_NRD_HW_M23_TNR1_WR04(tnr_ctrl_61,		reg_sad_ma_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[20],0,8),\
															reg_sad_ma_ctrl_pt_y3,	GET_BITS(pp->tnr1_blnd[21],0,8),\
															reg_sad_ma_ctrl_pt_x2,	GET_BITS(pp->tnr1_blnd[22],0,8),\
															reg_sad_ma_ctrl_pt_y2,	GET_BITS(pp->tnr1_blnd[23],0,8));

			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR7_DETAIL_T
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_GetTnr2ndDetailCtrl(void *pstParams)
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
int PE_NRD_HW_M23_SetTnrSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_TNR_SQM_CMN_T *ctrl_param =(LX_PE_NRD_TNR_SQM_CMN_T *)pstParams;
			LX_PE_NRD_TNR_SQM1_CMN_T *pp = (LX_PE_NRD_TNR_SQM1_CMN_T *)ctrl_param->data;
			static LX_PE_NRD_TNR_SQM1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR_SQM1_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR_SQM1_CMN_T\n");
				ret=RET_OK;
				break;
			}
			{
				UINT32 *pd = (typeof(*pd) *)pp->tnr0__sqm;
				PE_DBG_NRD("[%d]tnr0__sqm:%d\n", pp->win_id, pp->tnr___val);
				PE_DBG_NRD( \
				"tnr0__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"tnr0__sqm[10]0x%08X\n", \
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
				pd[8],  pd[9],  pd[10]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_M23_DownloadTnrSqmCmnUserDb((void *)pp);
				PE_NRD_HW_M23_CHECK_CODE(ret, break, \
					"PE_NRD_HW_M23_DownloadTnrSqmCmnUserDb() error.\n");
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
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
int PE_NRD_HW_M23_SetTnr2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_TNR2ND_SQM_CMN_T *ctrl_param =(LX_PE_NRD_TNR2ND_SQM_CMN_T *)pstParams;
			LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = (LX_PE_NRD_TNR2ND_SQM1_CMN_T *)ctrl_param->data;
			static LX_PE_NRD_TNR2ND_SQM1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR2ND_SQM1_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR2ND_SQM1_CMN_T\n");
				ret=RET_OK;
				break;
			}
			{
			UINT32 *pd = (typeof(*pd) *)pp->tnr1__sqm;
			PE_DBG_NRD("[%d]tnr1__sqm:%d\n", pp->win_id, pp->tnr___val);
			PE_DBG_NRD( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_M23_DownloadTnr2ndSqmCmnUserDb((void *)pp);
				PE_NRD_HW_M23_CHECK_CODE(ret, break, \
					"PE_NRD_HW_M23_DownloadTnr2ndSqmCmnUserDb() error.\n");
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
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
int PE_NRD_HW_M23_SetDnrSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_DNR_SQM_CMN_T *ctrl_param =(LX_PE_NRD_DNR_SQM_CMN_T *)pstParams;
			LX_PE_NRD_DNR_SQM2_CMN_T *pp = (LX_PE_NRD_DNR_SQM2_CMN_T *)ctrl_param->data;
			static LX_PE_NRD_DNR_SQM2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DNR_SQM2_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DNR_SQM2_CMN_T\n");
				ret=RET_OK;
				break;
			}
			{
				UINT32 *pd = (typeof(*pd) *)pp->dnr___sqmui;
				PE_DBG_NRD("[%d]dnr___sqmui:%d\n", pp->win_id, pp->dnr_____val);
				PE_DBG_NRD( \
				"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
				pd[10],  pd[11],  pd[12],  pd[13], pd[14]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_M23_DownloadDnrSqmCmnUserDb((void *)pp);
				PE_NRD_HW_M23_CHECK_CODE(ret, break, \
					"PE_NRD_HW_M23_DownloadDnrSqmCmnUserDb() error.\n");
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
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
int PE_NRD_HW_M23_SetDnrDcntSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_M23)
		{
			LX_PE_NRD_DCNT_SQM_CMN_T *ctrl_param =(LX_PE_NRD_DCNT_SQM_CMN_T *)pstParams;
			LX_PE_NRD_DCNT_SQM1_CMN_T *pp = (LX_PE_NRD_DCNT_SQM1_CMN_T *)ctrl_param->data;
			static LX_PE_NRD_DCNT_SQM1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT_SQM1_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DCNT_SQM1_CMN_T\n");
				ret=RET_OK;
				break;
			}
			{
				UINT32 *pd = (typeof(*pd) *)pp->deconnd__sqmui;
				PE_DBG_NRD("[%d]deconnd__sqmui:%d\n", pp->win_id, pp->deconnd____val);
				PE_DBG_NRD( "\n"\
				"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
				pd[10],  pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19],\
				pd[20],  pd[21],  pd[22]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_M23_DownloadDnrDcntSqmCmnUserDb((void *)pp);
				PE_NRD_HW_M23_CHECK_CODE(ret, break, \
					"PE_NRD_HW_M23_DownloadDnrDcntSqmCmnUserDb() error.\n");
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl - not used @M23
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_M23_SetLedDcntSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}

/**
 * set tnr lb ctrl
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M23_SetTnrLbMode(PE_TSK_M23_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	static UINT32 count = 0;
	__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	//__attribute__((unused)) PE_INF_M23_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	static LX_PE_FMT_TYPE pre_fmt_type = LX_PE_FMT_NUM;
	UINT32 is_hfr;
	static UINT32 pre_is_hfr=0xff;
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_M23)
		{
			static PE_M23_PE0_SRC_SIZE_T pre_nd1_pe0_src_size = {
				.hsize = 0,
				.vsize = 0,
				.scan_type = 0,
				};
			static PE_M23_TNR_CTRL_16_T pre_nd1_tnr_ctrl_16 = {
				.reg_n_hblk = 0,
				.reg_n_vblk = 0,
				};
			static PE_M23_TNR_CTRL_17_T pre_nd1_tnr_ctrl_17 = {
				.reg_blk_vsize = 0,
				.reg_blk_hsize = 0,
				};
			PE_M23_TNR_CTRL_16_T cur_nd1_tnr_ctrl_16;
			PE_M23_TNR_CTRL_17_T cur_nd1_tnr_ctrl_17;
			/* nd1 nblk setting *****************************************/
			if(_g_pe_nrd_hw_m23_info.is_external_chip) //M23+f20
			{
				is_hfr = (disp0_info->in_f_rate>= 610) \
					&& ((disp0_info->in_h_size > 1920) || (disp0_info->in_v_size > 1440))?1:0;
			}
			else //M23 only
			{
				is_hfr = 0;
			}
			if (pre_nd1_pe0_src_size.hsize != ctrl0_info->pe0_src_h || \
				pre_nd1_pe0_src_size.vsize != ctrl0_info->pe0_src_v || \
				pre_nd1_pe0_src_size.scan_type != disp0_info->scan_type || \
				pre_fmt_type != disp0_info->fmt_type || \
				pre_is_hfr != is_hfr)
			{
				PE_DBG_NRD("[inf] nd1 tnr src h:%d->%d, v:%d->%d, sc:%d->%d, fmt:%d->%d, is_hfr:%d->%d\n",\
					pre_nd1_pe0_src_size.hsize, ctrl0_info->pe0_src_h, \
					pre_nd1_pe0_src_size.vsize, ctrl0_info->pe0_src_v, \
					pre_nd1_pe0_src_size.scan_type, disp0_info->scan_type,\
					pre_fmt_type,disp0_info->fmt_type,pre_is_hfr, is_hfr);
				/*hblk*/
				if (disp0_info->fmt_type == LX_PE_FMT_UHD_8K)
				{
					cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x4;//
					cur_nd1_tnr_ctrl_17.reg_blk_hsize = 0x1E0;// h/8
				}
				else if (ctrl0_info->pe0_src_h >= PE_NRD_HW_M23_TNR_SRC_H_HD_BASE)
				{
					if(is_hfr) /* 4k hfr */
					{
						cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x8;// h%8==0:
						cur_nd1_tnr_ctrl_17.reg_blk_hsize = (ctrl0_info->pe0_src_h-256)>>2;// (2176-256)*2/8
					}
					else /*2048(4k),1568(3k),1920,1360,1280,1024,800*/
					{
						cur_nd1_tnr_ctrl_16.reg_n_hblk = 0x8;// h%8==0:
						cur_nd1_tnr_ctrl_17.reg_blk_hsize = ctrl0_info->pe0_src_h>>3;// h/8
					}
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
				if (ctrl0_info->pe0_src_v >= PE_NRD_HW_M23_TNR_SRC_V_3K_BASE)
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
				if (pre_nd1_tnr_ctrl_16.reg_n_hblk != cur_nd1_tnr_ctrl_16.reg_n_hblk || \
					pre_nd1_tnr_ctrl_16.reg_n_vblk != cur_nd1_tnr_ctrl_16.reg_n_vblk)
				{
					PE_DBG_NRD("[set] nd1 tnr n_blk h:0x%x->0x%x, v:0x%x->0x%x\n",\
						pre_nd1_tnr_ctrl_16.reg_n_hblk, cur_nd1_tnr_ctrl_16.reg_n_hblk, \
						pre_nd1_tnr_ctrl_16.reg_n_vblk, cur_nd1_tnr_ctrl_16.reg_n_vblk);
					PE_NRD_HW_M23_TNR0_WR02(tnr_ctrl_16,reg_n_hblk,cur_nd1_tnr_ctrl_16.reg_n_hblk, \
					                                     reg_n_vblk,cur_nd1_tnr_ctrl_16.reg_n_vblk);
					pre_nd1_tnr_ctrl_16.reg_n_hblk = cur_nd1_tnr_ctrl_16.reg_n_hblk;
					pre_nd1_tnr_ctrl_16.reg_n_vblk = cur_nd1_tnr_ctrl_16.reg_n_vblk;
				}
				if (pre_nd1_tnr_ctrl_17.reg_blk_vsize != cur_nd1_tnr_ctrl_17.reg_blk_vsize || \
					pre_nd1_tnr_ctrl_17.reg_blk_hsize != cur_nd1_tnr_ctrl_17.reg_blk_hsize)
				{
					PE_DBG_NRD("[set] nd1 tnr blk_size h:%d->%d, v:%d->%d\n",\
						pre_nd1_tnr_ctrl_17.reg_blk_hsize, cur_nd1_tnr_ctrl_17.reg_blk_hsize, \
						pre_nd1_tnr_ctrl_17.reg_blk_vsize, cur_nd1_tnr_ctrl_17.reg_blk_vsize);
					PE_NRD_HW_M23_TNR0_WR02(tnr_ctrl_17,reg_blk_vsize,cur_nd1_tnr_ctrl_17.reg_blk_vsize, \
					                                     reg_blk_hsize,cur_nd1_tnr_ctrl_17.reg_blk_hsize);
					pre_nd1_tnr_ctrl_17.reg_blk_vsize = cur_nd1_tnr_ctrl_17.reg_blk_vsize;
					pre_nd1_tnr_ctrl_17.reg_blk_hsize = cur_nd1_tnr_ctrl_17.reg_blk_hsize;
				}
				pre_nd1_pe0_src_size.hsize = ctrl0_info->pe0_src_h;
				pre_nd1_pe0_src_size.vsize = ctrl0_info->pe0_src_v;
				pre_nd1_pe0_src_size.scan_type = disp0_info->scan_type;
				pre_fmt_type = disp0_info->fmt_type;
				pre_is_hfr = is_hfr;
			}
			/* **********************************************************/
			if(count>PE_PRINT_COUNT_NUM)
			{
				PE_DBG_NRD("[state] nd1 tnr src h:%d, v:%d, sc:%d\n",\
					pre_nd1_pe0_src_size.hsize, pre_nd1_pe0_src_size.vsize, \
					pre_nd1_pe0_src_size.scan_type);
				PE_DBG_NRD("[state] nd1 tnr n_blk h:0x%x, v:0x%x\n",\
					pre_nd1_tnr_ctrl_16.reg_n_hblk, pre_nd1_tnr_ctrl_16.reg_n_vblk);
				PE_DBG_NRD("[state] nd1 tnr blk_size h:%d, v:%d\n",\
					pre_nd1_tnr_ctrl_17.reg_blk_hsize, pre_nd1_tnr_ctrl_17.reg_blk_vsize);
				count=0;
			}
			count++;
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * set tnr pv smooth en mode
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M23_SetTnrSmoothMode(PE_TSK_M23_CFG_T *pCfg)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set tnr pv smooth en mode
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_M23_SetTnrPBPMode(PE_TSK_M23_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	//static UINT32 count = 0;
	static UINT32 pre_decon_blend_en = 0xff;
	UINT32 cur_decon_blend_en, reg_decon_blend_en;
	PE_TNR_HW_PARAM_REG_M23_T *p_tnr_dflt = _g_pe_tnr_hw_param_data_m23.reg_dflt.data;
	LX_PE_INF_DISPLAY_T cur0_inf;
	do{
		CHECK_KNULL(pCfg);
		ret = PE_INF_M23_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
		PE_NRD_HW_M23_CHECK_CODE(ret,break,"PE_INF_M23_GetCurInfSettings() error.\n");
		if(PE_KDRV_VER_M23)
		{
			PE_ND0_M23_QRd01(nd_fsw_ctrl_03,reg_decon_blend_en,reg_decon_blend_en);
			//4k pbp WA
			if(cur0_inf.sub_mode == 0x2)
			{
				cur_decon_blend_en = 0x0;
			}
			else
			{
				cur_decon_blend_en = p_tnr_dflt->tnr_ctrl_00.reg_decon_blend_en;
			}
			/* compare pre vs. cur */
			if (pre_decon_blend_en != cur_decon_blend_en)
			{
				PE_DBG_NRD("[inf] submode:%d, read decon_blend_en:%d\n", cur0_inf.sub_mode,reg_decon_blend_en);
				PE_DBG_NRD("[set] decon_blend_en:%d -> %d\n", \
					pre_decon_blend_en,cur_decon_blend_en);
				PE_ND0_M23_QWr01(nd_fsw_ctrl_03, reg_decon_blend_en,GET_BITS(cur_decon_blend_en,0,1));
				pre_decon_blend_en = cur_decon_blend_en;
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * set tnr mode
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_SetTnrMode(PE_TSK_M23_CFG_T *pCfg)
{
    int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_M23)
		{
			ret = PE_NRD_HW_M23_SetTnrLbMode(pCfg);
			PE_NRD_HW_M23_CHECK_CODE(ret, break, "PE_NRD_HW_M23_SetTnrLbMode() error.\n");
			ret = PE_NRD_HW_M23_SetTnrSmoothMode(pCfg);
			PE_NRD_HW_M23_CHECK_CODE(ret, break, "PE_NRD_HW_M23_SetTnrSmoothMode() error.\n");
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_NRD_HW_M23_DownloadTnrDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_lut[PE_NRD_M23_TNL_NUM];
	UINT32 base_user_lut, base_gain, base_buff, base_init;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_tnr_lut_data  = p_phys_db->tnr_lut.data;
	volatile UINT32 *p_tnr_user_data = p_phys_db->tnr_user.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_tnr_lut_data );
		CHECK_KNULL(p_tnr_user_data);
		if (PE_KDRV_VER_M23)
		{
			/* tnr_lut **************************************************************/
			sec_typ = PE_DDR_M23_SEC_TNR_LUT;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M23_TNR_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_TNR_LUT_SIZE;
			p_phys_db->tnr_lut.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_lut.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_lut.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M23_TNR_LUT_ITEM_NUM * PE_DDR_M23_TNR_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			base_lut[0] = 0;									//PE_NRD_M23_TNL_HD
			base_lut[1] = base_lut[0]+PE_DDR_M23_TNR_LUT_SIZE;	//PE_NRD_M23_TNL_SD
			base_lut[2] = base_lut[1]+PE_DDR_M23_TNR_LUT_SIZE;	//PE_NRD_M23_TNL_UD
			base_lut[3] = base_lut[2]+PE_DDR_M23_TNR_LUT_SIZE;	//PE_NRD_M23_TNL_CAM_HD
			for (i=0; i<PE_DDR_M23_TNR_LUT_SIZE; i++)
			{
				p_tnr_lut_data[base_lut[0]+i] = tnr_l_lut_hd_default_m23[i].data;
				p_tnr_lut_data[base_lut[1]+i] = tnr_l_lut_sd_default_m23[i].data;
				p_tnr_lut_data[base_lut[2]+i] = tnr_l_lut_ud_default_m23[i].data;
				p_tnr_lut_data[base_lut[3]+i] = tnr_l_lut_cam_hd_default_m23[i].data;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
			/* tnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_TNR_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M23_TNR_USER_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_TNR_USER_SIZE;
			p_phys_db->tnr_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M23_TNR_USER_ITEM_NUM * PE_DDR_M23_TNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_tnr_user_data[0]  = 0x0;
			p_tnr_user_data[1]  = 0x0;
			base_user_lut = 2;
			base_gain = base_user_lut+LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			base_buff = base_gain+LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			base_init = 7;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				p_tnr_user_data[base_user_lut+i] = tnr_l_lut_hd_default_m23[base_init+i].data;
			}
			p_tnr_user_data[base_gain]=p_tnr_user_data[base_gain+1]=p_tnr_user_data[base_gain+2]= \
				p_tnr_user_data[base_gain+3] =p_tnr_user_data[base_gain+4]=0x0;
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
int PE_NRD_HW_M23_DownloadTnr2ndDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	//UINT32 base_lut[PE_NRD_M23_TNL_NUM];
	UINT32 base_user_lut, base_gain, base_buff, base_init;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_tnr2nd_user_data = p_phys_db->tnr2nd_user.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_tnr2nd_user_data);
		if (PE_KDRV_VER_M23)
		{
			/* tnr2nd_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_TNR2ND_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_M23_TNR_USER_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_TNR_USER_SIZE;
			p_phys_db->tnr2nd_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr2nd_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr2nd_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr2nd_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_M23_TNR_USER_ITEM_NUM * PE_DDR_M23_TNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_tnr2nd_user_data[0]  = 0x0;
			p_tnr2nd_user_data[1]  = 0x0;
			base_user_lut = 2;
			base_gain = base_user_lut+LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			base_buff = base_gain+LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			base_init = 7;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				p_tnr2nd_user_data[base_user_lut+i] = tnr_l_lut_hd_default_m23[base_init+i].data;
			}
			p_tnr2nd_user_data[base_gain]=p_tnr2nd_user_data[base_gain+1]=p_tnr2nd_user_data[base_gain+2]= \
				p_tnr2nd_user_data[base_gain+3] =p_tnr2nd_user_data[base_gain+4]=0x0;
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
static int PE_NRD_HW_M23_DownloadTnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_TNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_TNR_USER_T);
			pp = (LX_PE_NRD_TNR1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->tnr0___en;
			base = 2;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr0__lut[i];
			}
			base += LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_GAIN_SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr0_gain[i];
			}
			base += LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_BUFF_SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr0_buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get tnr user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetTnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_TNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_TNR_USER_T);
			pp = (LX_PE_NRD_TNR1_CMN_T *)pstParams;
			pp->tnr0___en = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				pp->tnr0__lut[i] = p_db_data[base+i];
			}
			base += LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_GAIN_SIZE; i++)
			{
				pp->tnr0_gain[i] = p_db_data[base+i];
			}
			base += LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_BUFF_SIZE; i++)
			{
				pp->tnr0_buff[i] = p_db_data[base+i] ;
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			pd = (typeof(*pd) *)pp->tnr0__lut;
			printk("tnr0___en:%d\n", pp->tnr0___en);
			PE_DBG_NRD( \
			"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = (typeof(*pd) *)pp->tnr0_gain;
			printk(\
			"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4]);
			pd = (typeof(*pd) *)pp->tnr0_buff;
			printk(\
			"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11], pd[12], pd[13], pd[14]);
			
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_M23_DownloadTnr2ndUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr2nd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_TNR2ND_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_TNR_USER_T);
			pp = (LX_PE_NRD_TNR2ND2_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->tnr1___en;
			base = 2;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr1__lut[i];
			}
			base += LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_GAIN_SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr1_gain[i];
			}
			base += LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_BUFF_SIZE; i++)
			{
				p_db_data[base+i] = pp->tnr1_buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get tnr user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetTnr2ndUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND2_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr2nd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_TNR2ND_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_TNR_USER_T);
			pp = (LX_PE_NRD_TNR2ND2_CMN_T *)pstParams;
			pp->tnr1___en = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				pp->tnr1__lut[i] = p_db_data[base+i];
			}
			base += LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_GAIN_SIZE; i++)
			{
				pp->tnr1_gain[i] = p_db_data[base+i];
			}
			base += LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_BUFF_SIZE; i++)
			{
				pp->tnr1_buff[i] = p_db_data[base+i];
			}
			pd = (typeof(*pd) *)pp->tnr1__lut;
			printk("tnr1___en:%d\n", pp->tnr1___en);
			printk( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = (typeof(*pd) *)pp->tnr1_gain;
			printk(\
			"tnr1_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4]);
			pd = (typeof(*pd) *)pp->tnr1_buff;
			printk(\
			"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11], pd[12], pd[13], pd[14]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download dnr db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_DownloadDnrInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_dnr_user_data = p_phys_db->dnr_user.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dnr_user_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_DNR_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_DNR_USER_SIZE;
			p_phys_db->dnr_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_DNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_dnr_user_data[0]  = 0x0;
			p_dnr_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_DNR_USER_SIZE-base_user_lut; i++)
			{
				p_dnr_user_data[i+base_user_lut] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download dnr user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M23_DownloadDnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR3_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->dnr_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		//CHECK_KNULL(p_phys_dnr_user_db);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_DNR_USER_T);
			pp = (LX_PE_NRD_DNR3_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->dnr__ui_val;
			base = 2;
			for (i=0; i<PE_DDR_M23_DNR_USER_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->dnr____buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get dnr user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetDnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR3_CMN_T *pp = NULL;
	UINT32* pd32;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->dnr_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		//CHECK_KNULL(p_phys_dnr_user_db);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_DNR_USER_T);
			pp = (LX_PE_NRD_DNR3_CMN_T *)pstParams;
			//p_db_data[1] = (UINT32)pp->dnr__ui_val;
			base = 2;
			for (i=0; i<PE_DDR_M23_DNR_USER_SIZE-base; i++)
			{
				pp->dnr____buff[i] = p_db_data[base+i];
			}
			pd32 = pp->dnr____buff;
			printk(\
			"dnr____buff[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}


/**
 * download dnr dcnt db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_DownloadDnrDcntInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_dcnt_user_data = p_phys_db->nrd_dcnt_user.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dcnt_user_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_DNR_DCNT_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_DCNT_USER_SIZE;
			p_phys_db->nrd_dcnt_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->nrd_dcnt_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->nrd_dcnt_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->nrd_dcnt_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_DCNT_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_dcnt_user_data[0]  = 0x0;
			p_dcnt_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_DCNT_USER_SIZE-base_user_lut; i++)
			{
				p_dcnt_user_data[i+base_user_lut] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download dnr user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M23_DownloadDnrDcntUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT3_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->nrd_dcnt_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DNR_DCNT_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_DCNT_USER_T);
			pp = (LX_PE_NRD_DCNT3_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->deconnd_ui_val;
			base = 2;
			for (i=0; i<PE_DDR_M23_DCNT_USER_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->deconnd___buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get dnr user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetDnrDcntUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT3_CMN_T *pp = NULL;
	UINT32* pd32;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->nrd_dcnt_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DNR_DCNT_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_DCNT_USER_T);
			pp = (LX_PE_NRD_DCNT3_CMN_T *)pstParams;
			base = 2;
			for (i=0; i<PE_DDR_M23_DCNT_USER_SIZE-base; i++)
			{
				pp->deconnd___buff[i] = p_db_data[base+i];
			}
			pd32 = pp->deconnd___buff;
			printk(\
			"deconnd___buff[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download led dcnt db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_DownloadLedDcntInitDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_dcnt_user_data = p_phys_db->led_dcnt_user.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dcnt_user_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_LED_DCNT_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_DCNT_LED_USER_SIZE;
			p_phys_db->led_dcnt_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->led_dcnt_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->led_dcnt_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->led_dcnt_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_DCNT_LED_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_dcnt_user_data[0]  = 0x0;
			p_dcnt_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i=2; i<PE_DDR_M23_DCNT_LED_USER_SIZE; i++)
			{
				p_dcnt_user_data[i] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download led user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
// static int PE_NRD_HW_M23_DownloadLedDcntUserDb(void *pstParams)
// {
// 	int ret = RET_OK;
// 	return ret;
// }
/**
 * get led user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetLedDcntUserDb(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}

/**
 * download tnr sqm db init
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_DownloadTnrSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_tnr_sqm_data = p_phys_db->tnr_sqm.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_tnr_sqm_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_TNR_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_TNR_SQM_SIZE;
			p_phys_db->tnr_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_TNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_tnr_sqm_data[0]  = 0x0;
			p_tnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_TNR_SQM_SIZE-base_user_lut; i++)
			{
				p_tnr_sqm_data[i+base_user_lut] = sqm_tnr_init_m23[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download tnr sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M23_DownloadTnrSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_TNR_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->tnr___val;
			base = 2;
			for (i=0; i<PE_DDR_M23_TNR_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->tnr0__sqm[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get tnr sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetTnrSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR_SQM1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_TNR_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR_SQM1_CMN_T *)pstParams;
			pp->tnr___val = (UINT8)p_db_data[1] ;
			base = 2;
			for (i=0; i<PE_DDR_M23_TNR_SQM_SIZE-base; i++)
			{
				pp->tnr0__sqm[i] = p_db_data[base+i];
			}
			pd = (typeof(*pd) *)pp->tnr0__sqm;
			printk("tnr0__sqm:%d\n", pp->tnr___val);
			printk( \
			"tnr0__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__sqm[10]0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download led dcnt db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_DownloadTnr2ndSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_tnr_sqm_data = p_phys_db->tnr2nd_sqm.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_tnr_sqm_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_TNR2ND_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_TNR_SQM_SIZE;
			p_phys_db->tnr2nd_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr2nd_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr2nd_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr2nd_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_TNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_tnr_sqm_data[0]  = 0x0;
			p_tnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_TNR_SQM_SIZE-base_user_lut; i++)
			{
				p_tnr_sqm_data[i+base_user_lut] = sqm_tnr2nd_init_m23[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download led user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_M23_DownloadTnr2ndSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr2nd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_TNR2ND_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR2ND_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->tnr___val;
			base = 2;
			for (i=0; i<PE_DDR_M23_TNR_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->tnr1__sqm[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get led user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetTnr2ndSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr2nd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_TNR2ND_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR2ND_SQM1_CMN_T *)pstParams;
			pp->tnr___val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_M23_TNR_SQM_SIZE-base; i++)
			{
				pp->tnr1__sqm[i] = p_db_data[base+i];
			}
			pd = (typeof(*pd) *)pp->tnr1__sqm;
			printk("tnr1__sqm:%d\n", pp->tnr___val);
			printk( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download led dcnt db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_DownloadDnrSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_dnr_sqm_data = p_phys_db->dnr_sqm.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dnr_sqm_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_DNR_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_DNR_SQM_SIZE;
			p_phys_db->dnr_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_DNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_dnr_sqm_data[0]  = 0x0;
			p_dnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_DNR_SQM_SIZE-base_user_lut; i++)
			{
				p_dnr_sqm_data[i+base_user_lut] = sqm_dnr_init_m23[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download dnr sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M23_DownloadDnrSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR_SQM2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DNR_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_DNR_SQM_T);
			pp = (LX_PE_NRD_DNR_SQM2_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->dnr_____val;
			base = 2;
			for (i=0; i<PE_DDR_M23_DNR_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->dnr___sqmui[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get dnr sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetDnrSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR_SQM2_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DNR_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_DNR_SQM_T);
			pp = (LX_PE_NRD_DNR_SQM2_CMN_T *)pstParams;
			pp->dnr_____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_M23_DNR_SQM_SIZE-base; i++)
			{
				pp->dnr___sqmui[i] = p_db_data[base+i];
			}
			pd = (typeof(*pd) *)pp->dnr___sqmui;
			printk("dnr___sqmui:%d\n", pp->dnr_____val);
			printk( \
			"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download led dcnt db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_DownloadDnrDcntSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_dnr_sqm_data = p_phys_db->dnr_dcnt_sqm.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_dnr_sqm_data);
		if (PE_KDRV_VER_M23)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_M23_SEC_DNR_DCNT_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_M23_DCNT_SQM_SIZE;
			p_phys_db->dnr_dcnt_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_dcnt_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_dcnt_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_dcnt_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_M23_DCNT_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_M23_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_M23_HEADER_T);
			/* wr ddr */
			p_dnr_sqm_data[0]  = 0x0;
			p_dnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_M23_DCNT_SQM_SIZE-base_user_lut; i++)
			{
				p_dnr_sqm_data[i+base_user_lut] = sqm_dct_init_m23[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * download nrd dcnt sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_M23_DownloadDnrDcntSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_dcnt_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DNR_DCNT_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_DCNT_SQM_T);
			pp = (LX_PE_NRD_DCNT_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->deconnd____val;
			base = 2;
			for (i=0; i<PE_DDR_M23_DCNT_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->deconnd__sqmui[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_M23_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * get nrd dcnt sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetDnrDcntSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT_SQM1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_M23_T *p_shdw_db = gPE_DDR_DB_M23.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_M23_T *p_phys_db = gPE_DDR_DB_M23.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_dcnt_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_M23)
		{
			sec_typ = PE_DDR_M23_SEC_DNR_DCNT_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_M23_DCNT_SQM_T);
			pp = (LX_PE_NRD_DCNT_SQM1_CMN_T *)pstParams;
			pp->deconnd____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_M23_DCNT_SQM_SIZE-base; i++)
			{
				pp->deconnd__sqmui[i] = p_db_data[base+i];
			}
			pd = (typeof(*pd) *)pp->deconnd__sqmui;
			printk("deconnd__sqmui:%d\n", pp->deconnd____val);
			printk( \
			"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14],	pd[15],  pd[16],  pd[17], pd[18],  pd[19],\
			pd[20],  pd[21],  pd[22]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
/**
 * get led dcnt sqm db - not used @M23
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_M23_GetLedDcntSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	return ret;
}

