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

/** @file pe_nrd_hw_o26.c
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
#ifdef INCLUDE_KDRV_SYS
#include "sys_io.h"
#endif

#include "pe_hw_o26.h"
#include "pe_reg_o26.h"
#include "pe_fwi_o26.h"
#include "pe_cmn_hw_o26.h"
#include "pe_nrd_hw_o26.h"
#include "pe_hst_hw_o26.h"
#include "pe_chpi_tnr_hw_o26f22.h"
#include "pe_chpi_dnr_hw_o26f22.h"

#include "pe_tnr_hw_param_o26.h"
#include "pe_dnr_hw_param_o26.h"
#include "cvd_module.h"

#include "pe_tnr_l_lut_user_off_o26.h"
#include "pe_tnr_l_lut_user_low_o26.h"
#include "pe_tnr_l_lut_user_med_o26.h"
#include "pe_tnr_l_lut_user_high_o26.h"

#include "pe_tnr_l_lut_hd_default_o26.h"
#include "pe_tnr_l_lut_sd_default_o26.h"
#include "pe_tnr_l_lut_ud_default_o26.h"
#include "pe_tnr_l_lut_cam_hd_default_o26.h"
#include "pe_tnr_l_sd_default_o26.h"
#include "pe_tnr_l_hd_i_default_o26.h"
#include "pe_tnr_l_hd_p_default_o26.h"
#include "pe_tnr_l_ud_default_o26.h"
#include "pe_tnr_l_8k_default_o26.h"

#include "pe_tnr2nd_l_lut_hd_default_o26.h"
#include "pe_tnr2nd_l_lut_sd_default_o26.h"
#include "pe_tnr2nd_l_lut_ud_default_o26.h"
#include "pe_tnr2nd_l_lut_cam_hd_default_o26.h"
#include "pe_tnr2nd_l_sd_default_o26.h"
#include "pe_tnr2nd_l_hd_i_default_o26.h"
#include "pe_tnr2nd_l_hd_p_default_o26.h"
#include "pe_tnr2nd_l_ud_default_o26.h"

#include "pe_tnr3rd_l_hd_p_default_o26.h"
#include "pe_tnr3rd_l_sd_default_o26.h"
#include "pe_tnr3rd_l_lut_hd_default_o26.h"
#include "pe_tnr3rd_l_lut_sd_default_o26.h"

#include "pe_sqm_tnr_init_o26.h"
#include "pe_sqm_tnr2nd_init_o26.h"

#include "pe_dnr_l_hd_i_default_o26.h"
#include "pe_dnr_l_hd_p_default_o26.h"
#include "pe_dnr_l_sd_default_o26.h"
#include "pe_dnr_l_ud_default_o26.h"
#include "pe_dnr_l_dtv_sd_default_o26.h"

#include "pe_dnr2nd_l_hd_i_default_o26.h"
#include "pe_dnr2nd_l_hd_p_default_o26.h"
#include "pe_dnr2nd_l_sd_default_o26.h"
#include "pe_dnr2nd_l_ud_default_o26.h"
#include "pe_dnr2nd_l_dtv_sd_default_o26.h"

#include "pe_cco_dec_l_ud_default_o26.h"


#include "pe_sqm_dnr_init_o26.h"
#include "pe_sqm_dct_init_o26.h"

#if 0
//o26f22
#include "pe_tnr_l_lut_hd_default_o26f22.h"
#include "pe_tnr_l_lut_sd_default_o26f22.h"
#include "pe_tnr_l_lut_ud_default_o26f22.h"
#include "pe_tnr_l_lut_cam_hd_default_o26f22.h"
#include "pe_tnr_l_sd_default_o26f22.h"
#include "pe_tnr_l_hd_i_default_o26f22.h"
#include "pe_tnr_l_hd_p_default_o26f22.h"
#include "pe_tnr_l_ud_default_o26f22.h"
#include "pe_tnr_l_8k_default_o26f22.h"

#include "pe_dnr_l_hd_i_default_o26f22.h"
#include "pe_dnr_l_hd_p_default_o26f22.h"
#include "pe_dnr_l_sd_default_o26f22.h"
#include "pe_dnr_l_ud_default_o26f22.h"
#include "pe_dnr_l_8k_default_o26f22.h"

//#include "pe_led_dnr_l_ud_default_o26f22.h"
//#include "pe_led_dnr_l_hd_default_o26f22.h"
//#include "pe_led_dnr_l_sd_default_o26f22.h"

//#include "pe_dnrpsp_l_hd_default_o26f22.h"
//#include "pe_dnrpsp_l_sd_default_o26f22.h"
//#include "pe_dnrpsp_l_ud_default_o26f22.h"
#include "pe_osd_dec_default_o26f22.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 352,288 = 704/2,576/2 */
#define PE_NRD_HW_O26_H_MIN                (352)
#define PE_NRD_HW_O26_V_MIN                (288)
#define PE_NRD_HW_O26_TNR_SRC_H_HD_BASE    (800)
#define PE_NRD_HW_O26_TNR_SRC_V_3K_BASE    (1600)
#define PE_NRD_HW_O26_C_FMT_444            (0x6)
#define PE_NRD_HW_O26_C_FMT_422            (0x5)
#define PE_NRD_HW_O26_C_FMT_420            (0x4)

#define PE_NRD_HW_O26_SDR					(0)
#define PE_NRD_HW_O26_HDR2K					(1)
#define PE_NRD_HW_O26_HDR4K					(2)
#define PE_NRD_HW_O26_NUM_OF_TNR_CTRL_02_IN_TABLE (2)
#define PE_NRD_HW_O26_NUM_OF_TNR_CTRL_22_IN_TABLE (22)


#define PE_NRD_HW_O26_USE_SIZE_FR_FW

#undef PE_NRD_HW_O26_CVD_PAT_DETECT

#undef PE_NRD_HW_O26_MOVE_TO_SQM

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_HW_O26_ERROR		PE_PRINT_ERROR

#define PE_NRD_HW_O26_DBG_PRINT(fmt,args...)	\
	if(_g_nrd_hw_o26_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

#define PE_NRD_HW_O26_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_NRD_HW_O26_ERROR(fmt,##args);_action;}}

#define PE_NRD_HW_O26_DBG_PRINT_TNR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_O26_TNR_FMT_TO_STR(_pre), \
			PE_NRD_HW_O26_TNR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O26_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_NRD_HW_O26_DBG_PRINT_TNR2ND_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_O26_TNR2ND_FMT_TO_STR(_pre), \
			PE_NRD_HW_O26_TNR2ND_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O26_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

/* tnr lut (tnl) */
#define PE_NRD_HW_O26_DBG_PRINT_TNL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_O26_TNL_FMT_TO_STR(_pre), \
			PE_NRD_HW_O26_TNL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O26_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

/* tnr2nd lut (tnl) */
#define PE_NRD_HW_O26_DBG_PRINT_TNL2ND_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_O26_TNL2ND_FMT_TO_STR(_pre), \
			PE_NRD_HW_O26_TNL2ND_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O26_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_NRD_HW_O26_DBG_PRINT_DNR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_O26_DNR_FMT_TO_STR(_pre), \
			PE_NRD_HW_O26_DNR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O26_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_NRD_HW_O26_DBG_PRINT_PSP_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_O26_PSP_FMT_TO_STR(_pre), \
			PE_NRD_HW_O26_PSP_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O26_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_NRD_HW_O26_DBG_PRINT_IFC_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_O26_IFC_FMT_TO_STR(_pre), \
			PE_NRD_HW_O26_IFC_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O26_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_NRD_HW_O26_DBG_PRINT_CCO_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_NRD_HW_O26_CCO_FMT_TO_STR(_pre), \
			PE_NRD_HW_O26_CCO_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_DBG_NRD("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O26_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_NRD_HW_O26_TNR0_SET_USER(_r, _f, _d)	\
	{	_g_pe_tnr_hw_param_data_o26.nd1_user.data->_r._f = (_d);\
		_g_pe_tnr_hw_param_data_o26.nd1_mask.data->_r._f = 0;}

#define PE_NRD_HW_O26_TNR0_WR01(_r, _f1, _d1)	\
	{	PE_ND0_O26_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_O26_TNR0_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND0_O26_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_O26_TNR0_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND0_O26_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_O26_TNR0_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND0_O26_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_O26_TNR0_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND0_O26_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_O26_TNR0_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_ND0_O26_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f6, _d6);}
#define PE_NRD_HW_O26_TNR0_WR07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7)	\
	{	PE_ND0_O26_QWr07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f7, _d7);}

#define PE_NRD_HW_O26_TNR0_WR09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_ND0_O26_QWr09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f9, _d9);}

#define PE_NRD_HW_O26_TNR0_WR10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_ND0_O26_QWr10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f9, _d9);\
		PE_NRD_HW_O26_TNR0_SET_USER(_r, _f10, _d10);}


#define PE_NRD_HW_O26_TNR1_SET_USER(_r, _f, _d)	\
	{	_g_pe_tnr2nd_hw_param_data_o26.nd1_user.data->_r._f = (_d);\
		_g_pe_tnr2nd_hw_param_data_o26.nd1_mask.data->_r._f = 0;}

#define PE_NRD_HW_O26_TNR1_WR01(_r, _f1, _d1)	\
	{	PE_ND1_O26_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_O26_TNR1_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND1_O26_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_O26_TNR1_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND1_O26_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_O26_TNR1_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND1_O26_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_O26_TNR1_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND1_O26_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_O26_TNR1_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_ND1_O26_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f6, _d6);}
#define PE_NRD_HW_O26_TNR1_WR07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7)	\
	{	PE_ND1_O26_QWr07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f7, _d7);}
#define PE_NRD_HW_O26_TNR1_WR09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_ND1_O26_QWr09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f9, _d9);}
#define PE_NRD_HW_O26_TNR1_WR10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_ND1_O26_QWr10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f9, _d9);\
		PE_NRD_HW_O26_TNR1_SET_USER(_r, _f10, _d10);}


#define PE_NRD_HW_O26_TNR2_SET_USER(_r, _f, _d)	\
	{	_g_pe_tnr3rd_hw_param_data_o26.nd1_user.data->_r._f = (_d);\
		_g_pe_tnr3rd_hw_param_data_o26.nd1_mask.data->_r._f = 0;}

#define PE_NRD_HW_O26_TNR2_WR01(_r, _f1, _d1)	\
	{	PE_ND2_O26_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_O26_TNR2_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND2_O26_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_O26_TNR2_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_ND2_O26_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_O26_TNR2_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_ND2_O26_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_O26_TNR2_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_ND2_O26_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_O26_TNR2_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_ND2_O26_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f6, _d6);}
#define PE_NRD_HW_O26_TNR2_WR07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7)	\
	{	PE_ND2_O26_QWr07(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f7, _d7);}
#define PE_NRD_HW_O26_TNR2_WR09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_ND2_O26_QWr09(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f9, _d9);}
#define PE_NRD_HW_O26_TNR2_WR10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_ND2_O26_QWr10(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f6, _d6);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f7, _d7);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f8, _d8);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f9, _d9);\
		PE_NRD_HW_O26_TNR2_SET_USER(_r, _f10, _d10);}


/* tnr lut (tnl) */
#define PE_NRD_HW_O26_TNL_SET_USER32(_r, _d)	\
	{	*((UINT32 *)&(_g_pe_tnl_hw_param_data_o26.reg_user.data->_r)) = (_d);\
		*((UINT32 *)&(_g_pe_tnl_hw_param_data_o26.reg_mask.data->_r)) = 0;}

#define PE_NRD_HW_O26_TNL_WR32(_num, _d1)	\
	{	PE_ND0_O26_QWr(tnr_main_lut_01, _d1);\
		PE_NRD_HW_O26_TNL_SET_USER32(tnr_lut_##_num, _d1);}
/* dnr */
#define PE_NRD_HW_O26_DNR_SET_USER(_r, _f, _d)	\
	{	_g_pe_dnr_hw_param_data_o26.reg_user.data->_r._f = (_d);\
		_g_pe_dnr_hw_param_data_o26.reg_mask.data->_r._f = 0;}

#define PE_NRD_HW_O26_DNR_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_O26_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_O26_DNR_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_O26_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_O26_DNR_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_O26_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_O26_DNR_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_O26_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_O26_DNR_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_O26_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_O26_DNR_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_DNR0_O26_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f6, _d6);}

#define PE_NRD_HW_O26_NR0_VERI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND0_VERI_O26_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR_SET_USER(_r, _f2, _d2);}

/* dnr2nd */
#define PE_NRD_HW_O26_DNR1_SET_USER(_r, _f, _d)	\
	{	_g_pe_dnr2nd_hw_param_data_o26.reg_user.data->_r._f = (_d);\
		_g_pe_dnr2nd_hw_param_data_o26.reg_mask.data->_r._f = 0;}

#define PE_NRD_HW_O26_DNR1_WR01(_r, _f1, _d1)	\
	{	PE_DNR1_O26_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_O26_DNR1_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR1_O26_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_O26_DNR1_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR1_O26_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_O26_DNR1_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR1_O26_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_O26_DNR1_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR1_O26_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_O26_DNR1_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_DNR1_O26_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f6, _d6);}

#define PE_NRD_HW_O26_NR1_VERI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_ND1_VERI_O26_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_DNR1_SET_USER(_r, _f2, _d2);}


/* cco dnr */
#define PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f, _d)	\
	{	_g_pe_cco_dnr_hw_param_data_o26.reg_user.data->_r._f = (_d);\
		_g_pe_cco_dnr_hw_param_data_o26.reg_mask.data->_r._f = 0;}

#define PE_NRD_HW_O26_CCO_DNR_WR01(_r, _f1, _d1)	\
	{	PE_CCO_DECON_O26_QWr01(_r, _f1, _d1);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f1, _d1);}
#define PE_NRD_HW_O26_CCO_DNR_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_CCO_DECON_O26_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f2, _d2);}
#define PE_NRD_HW_O26_CCO_DNR_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_CCO_DECON_O26_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f3, _d3);}
#define PE_NRD_HW_O26_CCO_DNR_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_CCO_DECON_O26_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f4, _d4);}
#define PE_NRD_HW_O26_CCO_DNR_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_CCO_DECON_O26_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f5, _d5);}
#define PE_NRD_HW_O26_CCO_DNR_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_CCO_DECON_O26_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f1, _d1);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f2, _d2);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f3, _d3);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f4, _d4);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f5, _d5);\
		PE_NRD_HW_O26_CCO_DNR_SET_USER(_r, _f6, _d6);}

#define PE_NRD_HW_O26_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_NRD_HW_O26_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"[%s,%d] _data is null, not ready.\n", __F__, __L__);\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_O26_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			ret = PE_REG_O26_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_M16_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_DBG_NRD("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_NRD_HW_O26_SET_TNR_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_NRD_HW_O26_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"[%s,%d] _data is null, not ready.\n", __F__, __L__);\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_O26_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			if(_i == (PE_NRD_HW_O26_NUM_OF_TNR_CTRL_22_IN_TABLE-1))\
				continue;\
			ret = PE_REG_O26_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_O26_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_DBG_NRD("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_NRD_HW_O26_SET_TNR3RD_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_NRD_HW_O26_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_NRD_HW_O26_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"[%s,%d] _data is null, not ready.\n", __F__, __L__);\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_O26_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			if(_i == (PE_NRD_HW_O26_NUM_OF_TNR_CTRL_22_IN_TABLE-1)|| _i == (PE_NRD_HW_O26_NUM_OF_TNR_CTRL_02_IN_TABLE-1))\
				continue;\
			ret = PE_REG_O26_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_O26_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_DBG_NRD("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)


/* tnr */
#define PE_NRD_HW_O26_TNR_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnr_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnr_hw_param_data_o26.nd1_user.addr;\
		UINT32 *_mask = _g_pe_tnr_hw_param_data_o26.nd1_mask.addr;\
		UINT32 *_data = _g_pe_tnr_hw_param_data_o26.nd1_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_TNR_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]tnr tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_TNR_REG_TABLE(__tbl, __base);\
	}while (0)
/* tnr2nd */
#define PE_NRD_HW_O26_TNR2ND_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnr2nd_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnr2nd_hw_param_data_o26.nd1_user.addr;\
		UINT32 *_mask = _g_pe_tnr2nd_hw_param_data_o26.nd1_mask.addr;\
		UINT32 *_data = _g_pe_tnr2nd_hw_param_data_o26.nd1_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]tnr2nd tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_TNR_REG_TABLE(__tbl, __base);\
	}while (0)
/* tnr3rd */
#define PE_NRD_HW_O26_TNR3RD_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnr3rd_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnr3rd_hw_param_data_o26.nd1_user.addr;\
		UINT32 *_mask = _g_pe_tnr3rd_hw_param_data_o26.nd1_mask.addr;\
		UINT32 *_data = _g_pe_tnr3rd_hw_param_data_o26.nd1_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]tnr3rd tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_TNR3RD_REG_TABLE(__tbl, __base);\
	}while (0)

/* tnr lut (tnl) */
#define PE_NRD_HW_O26_TNL_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnl_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnl_hw_param_data_o26.reg_user.addr;\
		UINT32 *_mask = _g_pe_tnl_hw_param_data_o26.reg_mask.addr;\
		UINT32 *_data = _g_pe_tnl_hw_param_data_o26.reg_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_TNL_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]tnl tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* tnr2nd lut (tnl2nd) */
#define PE_NRD_HW_O26_TNL2ND_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnl2nd_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnl2nd_hw_param_data_o26.reg_user.addr;\
		UINT32 *_mask = _g_pe_tnl2nd_hw_param_data_o26.reg_mask.addr;\
		UINT32 *_data = _g_pe_tnl2nd_hw_param_data_o26.reg_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]tnl2nd tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* tnr2nd lut (tnl2nd) */
#define PE_NRD_HW_O26_TNL3RD_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_tnl3rd_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_tnl3rd_hw_param_data_o26.reg_user.addr;\
		UINT32 *_mask = _g_pe_tnl3rd_hw_param_data_o26.reg_mask.addr;\
		UINT32 *_data = _g_pe_tnl3rd_hw_param_data_o26.reg_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]tnl3rd tbl size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* dnr */
#define PE_NRD_HW_O26_DNR_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_dnr_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_dnr_hw_param_data_o26.reg_user.addr;\
		UINT32 *_mask = _g_pe_dnr_hw_param_data_o26.reg_mask.addr;\
		UINT32 *_data = _g_pe_dnr_hw_param_data_o26.reg_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_DNR_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]dnr table size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_REG_TABLE(__tbl, __base);\
	}while (0)
		/* dnr */
#define PE_NRD_HW_O26_DNR2ND_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_dnr2nd_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_dnr2nd_hw_param_data_o26.reg_user.addr;\
		UINT32 *_mask = _g_pe_dnr2nd_hw_param_data_o26.reg_mask.addr;\
		UINT32 *_data = _g_pe_dnr2nd_hw_param_data_o26.reg_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]dnr2nd table size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_REG_TABLE(__tbl, __base);\
	}while (0)
		

/*led dnr */
#define PE_NRD_HW_O26_CCO_DNR_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_cco_dnr_hw_param_data_o26.reg_dflt.addr;\
		UINT32 *_user = _g_pe_cco_dnr_hw_param_data_o26.reg_user.addr;\
		UINT32 *_mask = _g_pe_cco_dnr_hw_param_data_o26.reg_mask.addr;\
		UINT32 *_data = _g_pe_cco_dnr_hw_param_data_o26.reg_data.addr;\
		PE_NRD_HW_O26_CHECK_CODE(\
		(sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]led dnr table size violation.\n", __F__, __L__);\
		PE_NRD_HW_O26_SET_REG_TABLE(__tbl, __base);\
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
extern UINT32 g_pe_inf_o26_vr360_mode;


/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static PE_NRD_HW_O26_TNR_FMT PE_NRD_HW_O26_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
__attribute__((unused)) static PE_NRD_HW_O26_TNR2ND_FMT PE_NRD_HW_O26_ConvDispInfoToTnr2ndFmt(LX_PE_INF_DISPLAY_T *disp_inf);
__attribute__((unused)) static PE_NRD_HW_O26_TNL_FMT PE_NRD_HW_O26_ConvDispInfoToTnlFmt(LX_PE_INF_DISPLAY_T *disp_inf);
__attribute__((unused)) static PE_NRD_HW_O26_TNL2ND_FMT PE_NRD_HW_O26_ConvDispInfoToTnl2ndFmt(LX_PE_INF_DISPLAY_T *disp_inf);
//static PE_NRD_HW_O26_IFC_FMT PE_NRD_HW_O26_ConvDispInfoToIfcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
__attribute__((unused)) static PE_NRD_HW_O26_DNR_FMT PE_NRD_HW_O26_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
__attribute__((unused)) static PE_NRD_HW_O26_CCO_FMT PE_NRD_HW_O26_ConvDispInfoToCCOFmt(LX_PE_INF_DISPLAY_T *disp_inf);
//static int PE_NRD_HW_O26_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);

__attribute__((unused)) static int PE_NRD_HW_O26_CreateDataTable(UINT32 index);
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnrDefault(PE_NRD_HW_O26_TNR_FMT cur0_tnr_fmt);
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnr2ndDefault(PE_NRD_HW_O26_TNR2ND_FMT cur1_tnr_fmt);
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnlDefault(PE_NRD_HW_O26_TNL_FMT cur0_tnl_fmt);
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnl2ndDefault(PE_NRD_HW_O26_TNL2ND_FMT cur1_tnl_fmt);
__attribute__((unused)) static int PE_NRD_HW_O26_SetDnrDefault(PE_NRD_HW_O26_DNR_FMT cur0_dnr_fmt);
__attribute__((unused)) static int PE_NRD_HW_O26_SetDnr2ndDefault(PE_NRD_HW_O26_DNR_FMT cur0_dnr_fmt);
__attribute__((unused)) static int PE_NRD_HW_O26_SetCCODefault(PE_NRD_HW_O26_CCO_FMT cur0_cco_fmt);

__attribute__((unused)) static int PE_NRD_HW_O26_SetTnrLbMode(PE_TSK_O26_CFG_T *pCfg);
//static int PE_NRD_HW_O26_SetTnrScMode(PE_TSK_O26_CFG_T *pCfg);
//static int PE_NRD_HW_O26_SetDnrMaxMode(PE_TSK_O26_CFG_T *pCfg);
//static int PE_NRD_HW_O26_SetBnrMode(PE_TSK_O26_CFG_T *pCfg);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnrUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnr2ndUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnr3rdUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnr2ndUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrDcntUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrDcnt2ndUserDb(void *pstParams);
//static int PE_NRD_HW_O26_DownloadLedDcntUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadCCODcntUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnrSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnr2ndSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnr3rdSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnr2ndSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrDcntSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrDcnt2ndSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadCCODcntSqmCmnUserDb(void *pstParams);
//static int PE_NRD_HW_O26_DownloadLedDcntSqmCmnUserDb(void *pstParams);
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnrPBPMode(PE_TSK_O26_CFG_T *pCfg);
__attribute__((unused)) static int PE_NRD_HW_O26_SetDnrSMRMode(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
__attribute__((unused)) static UINT8 _g_nrd_hw_o26_trace=0x0;	//default should be off.
__attribute__((unused)) static PE_NRD_HW_O26_SETTINGS_T _g_pe_nrd_hw_o26_info;
#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
__attribute__((unused)) static PE_TNR_HW_PARAM_DATA_O26_T _g_pe_tnr_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
__attribute__((unused)) static PE_TNR2ND_HW_PARAM_DATA_O26_T _g_pe_tnr2nd_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
__attribute__((unused)) static PE_TNR2ND_HW_PARAM_DATA_O26_T _g_pe_tnr3rd_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
__attribute__((unused)) static PE_TNL_HW_PARAM_DATA_O26_T _g_pe_tnl_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
__attribute__((unused)) static PE_TNL2ND_HW_PARAM_DATA_O26_T _g_pe_tnl2nd_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
__attribute__((unused)) static PE_TNL2ND_HW_PARAM_DATA_O26_T _g_pe_tnl3rd_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
__attribute__((unused)) static PE_DNR_HW_PARAM_DATA_O26_T _g_pe_dnr_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
__attribute__((unused)) static PE_DNR2ND_HW_PARAM_DATA_O26_T _g_pe_dnr2nd_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
__attribute__((unused)) static PE_CCO_DNR_HW_PARAM_DATA_O26_T _g_pe_cco_dnr_hw_param_data_o26 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif
//static UINT32 _g_pre_sc_en = 0xff;

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
int PE_NRD_HW_O26_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	PE_REG_O26_HW_OPT_T hw_opt = PE_REG_O26_GetDispOpt();
	do{
		CHECK_KNULL(pstParams);
		_g_pe_nrd_hw_o26_info.use_manual_sc = 1;
		_g_pe_nrd_hw_o26_info.tnr_sc_en_user = 0;
		_g_pe_nrd_hw_o26_info.tnr_sc_en_mask = 0;
		_g_pe_nrd_hw_o26_info.tnr_pv_smooth_en_user = 0;
		_g_pe_nrd_hw_o26_info.tnr_pv_smooth_en_mask = 0;
		_g_pe_nrd_hw_o26_info.dnr_max_en0_user = 0;
		_g_pe_nrd_hw_o26_info.dnr_max_en0_mask = 0;
		_g_pe_nrd_hw_o26_info.bnr_ac_h_en0_user = 0;
		_g_pe_nrd_hw_o26_info.bnr_ac_h_en0_mask = 0;
		_g_pe_nrd_hw_o26_info.cur_tnr_auto_enable = 0;
		_g_pe_nrd_hw_o26_info.cur_tnr_master_gain = 0xc0;	// sync with dflt
		_g_pe_nrd_hw_o26_info.tnr0a_fmt = PE_NRD_O26_TNR_NUM;
		_g_pe_nrd_hw_o26_info.tnr1a_fmt = PE_NRD_O26_TNR2ND_NUM;
		_g_pe_nrd_hw_o26_info.tnr2a_fmt = PE_NRD_O26_TNR2ND_NUM;
		_g_pe_nrd_hw_o26_info.tnl0a_fmt = PE_NRD_O26_TNL_NUM;
		_g_pe_nrd_hw_o26_info.tnl1a_fmt = PE_NRD_O26_TNL2ND_NUM;
		_g_pe_nrd_hw_o26_info.tnl2a_fmt = PE_NRD_O26_TNL2ND_NUM;
		_g_pe_nrd_hw_o26_info.dnr0a_fmt = PE_NRD_O26_DNR_NUM;
		_g_pe_nrd_hw_o26_info.dnr1a_fmt = PE_NRD_O26_DNR_NUM;
		_g_pe_nrd_hw_o26_info.pre_forcing_decon_only = 0xff;
		_g_pe_nrd_hw_o26_info.pre_smr_master_en_yy = 0xff;
		_g_pe_nrd_hw_o26_info.pre_smr_master_en_cc = 0xff;
		//_g_pre_sc_en = 0xff;
		if(PE_KDRV_VER_O26)
		{
			#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
			/* init tnr(nd0,1,2) */
			ret = PE_NRD_HW_O26_CreateDataTable(PE_NRD_HW_O26_TBL_IDX_TNR);
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"PE_NRD_HW_O26_CreateDataTable() error.\n");
			PE_NRD_HW_O26_TNR_REG_TABLE(tnr_l_hd_i_default_o26,PE_O26_REG_WRITE_BASE);
			PE_NRD_HW_O26_TNR2ND_REG_TABLE(tnr2nd_l_hd_i_default_o26,PE_O26_REG_WRITE_BASE);
			PE_NRD_HW_O26_TNR3RD_REG_TABLE(tnr3rd_l_hd_p_default_o26,PE_O26_REG_WRITE_BASE);
			/* init tnr lut (nd0,1,2) */
			ret = PE_NRD_HW_O26_CreateDataTable(PE_NRD_HW_O26_TBL_IDX_TNL);
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"PE_NRD_HW_O26_CreateDataTable() error.\n");
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL_REG_TABLE(tnr_l_lut_hd_default_o26,PE_O26_REG_WRITE_BASE);
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00008000);
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL2ND_REG_TABLE(tnr2nd_l_lut_hd_default_o26,PE_O26_REG_WRITE_BASE);
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00008000);
			PE_ND2_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL3RD_REG_TABLE(tnr3rd_l_lut_hd_default_o26,PE_O26_REG_WRITE_BASE);
			PE_ND2_O26_QWr(tnr_main_lut_00, 0x00008000);
			/* init dnr(nd1,2) */
			ret = PE_NRD_HW_O26_CreateDataTable(PE_NRD_HW_O26_TBL_IDX_DNR);
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"PE_NRD_HW_O26_CreateDataTable() error.\n");
			PE_NRD_HW_O26_DNR_REG_TABLE(dnr_l_hd_i_default_o26,PE_O26_REG_WRITE_BASE);
			PE_NRD_HW_O26_DNR2ND_REG_TABLE(dnr2nd_l_hd_i_default_o26,PE_O26_REG_WRITE_BASE);
			/* init cco dnr */
			ret = PE_NRD_HW_O26_CreateDataTable(PE_NRD_HW_O26_TBL_IDX_CCO);
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"PE_NRD_HW_O26_CreateDataTable() error.\n");
			PE_NRD_HW_O26_CCO_DNR_REG_TABLE(cco_dec_l_ud_default_o26,PE_O26_REG_WRITE_BASE);
			#endif
			/* tnr sc enable, threshold */
			PE_CC_PE1_O26_RdFL(pe1_fsw_ctrl_01);
			PE_CC_PE1_O26_Wr01(pe1_fsw_ctrl_01,tnr_sc_measure_en, _g_pe_nrd_hw_o26_info.use_manual_sc? 1:0);
			PE_CC_PE1_O26_Wr01(pe1_fsw_ctrl_01,tnr_sc_measure_th, 0x170);//368
			PE_CC_PE1_O26_WrFL(pe1_fsw_ctrl_01);
			#ifdef PE_HW_O26_CHIPINFO_TABLE	/* O26F22_TBL */
			PE_CHPI_TNR_HW_O26F22_Init(pstParams);
			PE_CHPI_DNR_HW_O26F22_Init(pstParams);
			#endif
			
			if (hw_opt.external_chip ==0 || hw_opt.external_chip==2) //one chip model(0) or KDL model(2)
			{
				_g_pe_nrd_hw_o26_info.is_external_chip = 0;
			}
			else //8k model
			{
				_g_pe_nrd_hw_o26_info.is_external_chip = 1;
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do\n");
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DBG_NRD("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(NRD)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_nrd_hw_o26_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(NRD)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if(PE_KDRV_VER_O26)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(NRD)))
				{
					PE_DBG_NRD("tnr,dnr : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_ND0_O26_QWr01(tnr_ctrl_00,reg_tnr_en,0x0);
						PE_DNR0_O26_QWr01(dnr_max_ctrl,reg_dnr_max_enable,0x0);
					}
				}
				else
				{
					PE_DBG_NRD("tnr,dnr : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_ND0_O26_QWr01(tnr_ctrl_00,reg_tnr_en,0x1);
						PE_DNR0_O26_QWr01(dnr_max_ctrl,reg_dnr_max_enable,0x1);
					}
				}
			}
			else
			{
				PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
/**
 * create data table
 *
 * @param   index [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_NRD_HW_O26_TBL_INDX
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_CreateDataTable(UINT32 index)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	PE_TNR_HW_PARAM_DATA_O26_T *p_tnr_o26 = &_g_pe_tnr_hw_param_data_o26;
	PE_TNR2ND_HW_PARAM_DATA_O26_T *p_tnr2nd_o26 = &_g_pe_tnr2nd_hw_param_data_o26;
	PE_TNR2ND_HW_PARAM_DATA_O26_T *p_tnr3rd_o26 = &_g_pe_tnr3rd_hw_param_data_o26;
	PE_TNL_HW_PARAM_DATA_O26_T *p_tnl_o26 = &_g_pe_tnl_hw_param_data_o26;
	PE_TNL2ND_HW_PARAM_DATA_O26_T *p_tnl2nd_o26 = &_g_pe_tnl2nd_hw_param_data_o26;
	PE_TNL2ND_HW_PARAM_DATA_O26_T *p_tnl3rd_o26 = &_g_pe_tnl3rd_hw_param_data_o26;
	PE_DNR_HW_PARAM_DATA_O26_T *p_dnr_o26 = &_g_pe_dnr_hw_param_data_o26;
	PE_DNR2ND_HW_PARAM_DATA_O26_T *p_dnr2nd_o26 = &_g_pe_dnr2nd_hw_param_data_o26;
	PE_CCO_DNR_HW_PARAM_DATA_O26_T *p_led_o26 = &_g_pe_cco_dnr_hw_param_data_o26;

	PE_NRD_HW_O26_CHECK_CODE(index>=PE_NRD_HW_O26_TBL_IDX_NUM, return RET_ERROR, \
		"[%s,%d] index(%d) invalid.\n", __F__, __L__, index);

	if (index == PE_NRD_HW_O26_TBL_IDX_TNR)
	{
		/* create dflt table nd0*/
		if (p_tnr_o26->reg_dflt.addr == NULL)
		{
			p_tnr_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_tnr_o26->nd1_user.addr == NULL)
		{
			p_tnr_o26->nd1_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_O26_T));
			memset((p_tnr_o26->nd1_user.addr), 0, sizeof(PE_TNR_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_tnr_o26->nd1_mask.addr == NULL)
		{
			p_tnr_o26->nd1_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_O26_T));
			memset((p_tnr_o26->nd1_mask.addr), -1, sizeof(PE_TNR_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnr_o26->nd1_data.addr == NULL)
		{
			p_tnr_o26->nd1_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR_HW_PARAM_REG_O26_T));
			memset((p_tnr_o26->nd1_data.addr), 0, sizeof(PE_TNR_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_tnr_o26->reg_dflt.addr != NULL && p_tnr_o26->nd1_user.addr != NULL && \
			p_tnr_o26->nd1_mask.addr != NULL && p_tnr_o26->nd1_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]nd0 table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]nd0 table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_tnr_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnr_o26->nd1_user.addr == NULL)? "x":"o", \
				(p_tnr_o26->nd1_mask.addr == NULL)? "x":"o", \
				(p_tnr_o26->nd1_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
		/* create dflt table nd1*/
		if (p_tnr2nd_o26->reg_dflt.addr == NULL)
		{
			p_tnr2nd_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_tnr2nd_o26->nd1_user.addr == NULL)
		{
			p_tnr2nd_o26->nd1_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));
			memset((p_tnr2nd_o26->nd1_user.addr), 0, sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_tnr2nd_o26->nd1_mask.addr == NULL)
		{
			p_tnr2nd_o26->nd1_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));
			memset((p_tnr2nd_o26->nd1_mask.addr), -1, sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnr2nd_o26->nd1_data.addr == NULL)
		{
			p_tnr2nd_o26->nd1_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));
			memset((p_tnr2nd_o26->nd1_data.addr), 0, sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_tnr2nd_o26->reg_dflt.addr != NULL && p_tnr2nd_o26->nd1_user.addr != NULL && \
			p_tnr2nd_o26->nd1_mask.addr != NULL && p_tnr2nd_o26->nd1_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]nd1 table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]nd1 table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_tnr2nd_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnr2nd_o26->nd1_user.addr == NULL)? "x":"o", \
				(p_tnr2nd_o26->nd1_mask.addr == NULL)? "x":"o", \
				(p_tnr2nd_o26->nd1_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
		/* create dflt table nd2 same as nd1*/
		if (p_tnr3rd_o26->reg_dflt.addr == NULL)
		{
			p_tnr3rd_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_tnr3rd_o26->nd1_user.addr == NULL)
		{
			p_tnr3rd_o26->nd1_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));
			memset((p_tnr3rd_o26->nd1_user.addr), 0, sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_tnr3rd_o26->nd1_mask.addr == NULL)
		{
			p_tnr3rd_o26->nd1_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));
			memset((p_tnr3rd_o26->nd1_mask.addr), -1, sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnr3rd_o26->nd1_data.addr == NULL)
		{
			p_tnr3rd_o26->nd1_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));
			memset((p_tnr3rd_o26->nd1_data.addr), 0, sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_tnr3rd_o26->reg_dflt.addr != NULL && p_tnr3rd_o26->nd1_user.addr != NULL && \
			p_tnr3rd_o26->nd1_mask.addr != NULL && p_tnr3rd_o26->nd1_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]nd2 table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_tnr3rd_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnr3rd_o26->nd1_user.addr == NULL)? "x":"o", \
				(p_tnr3rd_o26->nd1_mask.addr == NULL)? "x":"o", \
				(p_tnr3rd_o26->nd1_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_NRD_HW_O26_TBL_IDX_TNL)
	{
		/* create dflt table nd0*/
		if (p_tnl_o26->reg_dflt.addr == NULL)
		{
			p_tnl_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_tnl_o26->reg_user.addr == NULL)
		{
			p_tnl_o26->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_O26_T));
			memset((p_tnl_o26->reg_user.addr), 0, sizeof(PE_TNL_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_tnl_o26->reg_mask.addr == NULL)
		{
			p_tnl_o26->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_O26_T));
			memset((p_tnl_o26->reg_mask.addr), -1, sizeof(PE_TNL_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnl_o26->reg_data.addr == NULL)
		{
			p_tnl_o26->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL_HW_PARAM_REG_O26_T));
			memset((p_tnl_o26->reg_data.addr), 0, sizeof(PE_TNL_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_tnl_o26->reg_dflt.addr != NULL && p_tnl_o26->reg_user.addr != NULL && \
			p_tnl_o26->reg_mask.addr != NULL && p_tnl_o26->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]nd0 table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]nd0 table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_tnl_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnl_o26->reg_user.addr == NULL)? "x":"o", \
				(p_tnl_o26->reg_mask.addr == NULL)? "x":"o", \
				(p_tnl_o26->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
		/* create dflt table nd1*/
		if (p_tnl2nd_o26->reg_dflt.addr == NULL)
		{
			p_tnl2nd_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_tnl2nd_o26->reg_user.addr == NULL)
		{
			p_tnl2nd_o26->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));
			memset((p_tnl2nd_o26->reg_user.addr), 0, sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_tnl2nd_o26->reg_mask.addr == NULL)
		{
			p_tnl2nd_o26->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));
			memset((p_tnl2nd_o26->reg_mask.addr), -1, sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnl2nd_o26->reg_data.addr == NULL)
		{
			p_tnl2nd_o26->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));
			memset((p_tnl2nd_o26->reg_data.addr), 0, sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_tnl2nd_o26->reg_dflt.addr != NULL && p_tnl2nd_o26->reg_user.addr != NULL && \
			p_tnl2nd_o26->reg_mask.addr != NULL && p_tnl2nd_o26->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]nd1 table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]nd1 table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_tnl2nd_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnl2nd_o26->reg_user.addr == NULL)? "x":"o", \
				(p_tnl2nd_o26->reg_mask.addr == NULL)? "x":"o", \
				(p_tnl2nd_o26->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
		/* create dflt table nd2 same as nd2*/
		if (p_tnl3rd_o26->reg_dflt.addr == NULL)
		{
			p_tnl3rd_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_tnl3rd_o26->reg_user.addr == NULL)
		{
			p_tnl3rd_o26->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));
			memset((p_tnl3rd_o26->reg_user.addr), 0, sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_tnl3rd_o26->reg_mask.addr == NULL)
		{
			p_tnl3rd_o26->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));
			memset((p_tnl3rd_o26->reg_mask.addr), -1, sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_tnl3rd_o26->reg_data.addr == NULL)
		{
			p_tnl3rd_o26->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));
			memset((p_tnl3rd_o26->reg_data.addr), 0, sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_tnl3rd_o26->reg_dflt.addr != NULL && p_tnl3rd_o26->reg_user.addr != NULL && \
			p_tnl3rd_o26->reg_mask.addr != NULL && p_tnl3rd_o26->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]nd2 table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]nd2 table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_tnl3rd_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_tnl3rd_o26->reg_user.addr == NULL)? "x":"o", \
				(p_tnl3rd_o26->reg_mask.addr == NULL)? "x":"o", \
				(p_tnl3rd_o26->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}

	}
	else if (index == PE_NRD_HW_O26_TBL_IDX_DNR)
	{
		/* create dflt table nd0*/
		if (p_dnr_o26->reg_dflt.addr == NULL)
		{
			p_dnr_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_dnr_o26->reg_user.addr == NULL)
		{
			p_dnr_o26->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O26_T));
			memset((p_dnr_o26->reg_user.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_dnr_o26->reg_mask.addr == NULL)
		{
			p_dnr_o26->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O26_T));
			memset((p_dnr_o26->reg_mask.addr), -1, sizeof(PE_DNR_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_dnr_o26->reg_data.addr == NULL)
		{
			p_dnr_o26->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR_HW_PARAM_REG_O26_T));
			memset((p_dnr_o26->reg_data.addr), 0, sizeof(PE_DNR_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_dnr_o26->reg_dflt.addr != NULL && p_dnr_o26->reg_user.addr != NULL && \
			p_dnr_o26->reg_mask.addr != NULL && p_dnr_o26->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]nd0 table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]nd0 table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_dnr_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_dnr_o26->reg_user.addr == NULL)? "x":"o", \
				(p_dnr_o26->reg_mask.addr == NULL)? "x":"o", \
				(p_dnr_o26->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
		/* create dflt table nd1*/
		if (p_dnr2nd_o26->reg_dflt.addr == NULL)
		{
			p_dnr2nd_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_dnr2nd_o26->reg_user.addr == NULL)
		{
			p_dnr2nd_o26->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T));
			memset((p_dnr2nd_o26->reg_user.addr), 0, sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_dnr2nd_o26->reg_mask.addr == NULL)
		{
			p_dnr2nd_o26->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T));
			memset((p_dnr2nd_o26->reg_mask.addr), -1, sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_dnr2nd_o26->reg_data.addr == NULL)
		{
			p_dnr2nd_o26->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T));
			memset((p_dnr2nd_o26->reg_data.addr), 0, sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_dnr2nd_o26->reg_dflt.addr != NULL && p_dnr2nd_o26->reg_user.addr != NULL && \
			p_dnr2nd_o26->reg_mask.addr != NULL && p_dnr2nd_o26->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]nd1 table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]nd1 table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_dnr2nd_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_dnr2nd_o26->reg_user.addr == NULL)? "x":"o", \
				(p_dnr2nd_o26->reg_mask.addr == NULL)? "x":"o", \
				(p_dnr2nd_o26->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_NRD_HW_O26_TBL_IDX_CCO)
	{
		/* create dflt table */
		if (p_led_o26->reg_dflt.addr == NULL)
		{
			p_led_o26->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T));
		}
		/* create user table */
		if (p_led_o26->reg_user.addr == NULL)
		{
			p_led_o26->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T));
			memset((p_led_o26->reg_user.addr), 0, sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* create mask table */
		if (p_led_o26->reg_mask.addr == NULL)
		{
			p_led_o26->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T));
			memset((p_led_o26->reg_mask.addr), -1, sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T));// 0xffffffff
		}
		/* create data table */
		if (p_led_o26->reg_data.addr == NULL)
		{
			p_led_o26->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T));
			memset((p_led_o26->reg_data.addr), 0, sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T));	// 0x0
		}
		/* report result */
		if (p_led_o26->reg_dflt.addr != NULL && p_led_o26->reg_user.addr != NULL && \
			p_led_o26->reg_mask.addr != NULL && p_led_o26->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_NRD_HW_O26_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_NRD_HW_O26_TBL_IDX_TO_STR(index), \
				(p_led_o26->reg_dflt.addr == NULL)? "x":"o", \
				(p_led_o26->reg_user.addr == NULL)? "x":"o", \
				(p_led_o26->reg_mask.addr == NULL)? "x":"o", \
				(p_led_o26->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else
	{
		PE_DBG_NRD("nothing to do\n");	ret = RET_OK;
	}
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
#endif

/**
 * set nr default setting(for O26X)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	LX_PE_INF_DISPLAY_T cur0_inf;
	LX_PE_INF_DISPLAY_T cur1_inf;
	PE_NRD_HW_O26_TNR_FMT cur0_tnr_fmt;
	PE_NRD_HW_O26_TNR2ND_FMT cur1_tnr_fmt;
	PE_NRD_HW_O26_TNL_FMT cur0_tnl_fmt;
	PE_NRD_HW_O26_TNL2ND_FMT cur1_tnl_fmt;
	__attribute__((unused)) PE_NRD_HW_O26_TNL2ND_FMT cur2_tnl_fmt;
	PE_NRD_HW_O26_DNR_FMT cur0_dnr_fmt;
	PE_NRD_HW_O26_DNR_FMT cur1_dnr_fmt;
	//PE_NRD_HW_O26_CCO_FMT cur0_cco_fmt;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	PE_TNR_HW_PARAM_REG_O26_T *p_tnr_dflt = _g_pe_tnr_hw_param_data_o26.reg_dflt.data;
	PE_TNR2ND_HW_PARAM_REG_O26_T *p_tnr2nd_dflt = _g_pe_tnr2nd_hw_param_data_o26.reg_dflt.data;
	__attribute__((unused)) LX_PE_INF_DISPLAY_T *pp;
	UINT32 is_hfr = 0;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_O26_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
		ret = PE_INF_O26_GetCurDispInfSettings(LX_PE_WIN_1, &cur1_inf);
		PE_NRD_HW_O26_CHECK_CODE(ret,break,"[%s,%d] PE_INF_O26_GetCurInfSettings() error.\n",__F__,__L__);
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			is_hfr = (cur0_inf.in_f_rate>= 610) \
					&& ((cur0_inf.in_h_size > 1920) || (cur0_inf.in_v_size > 1440))?1:0;
			/* tnr lut (tnl) */
			cur0_tnl_fmt = PE_NRD_HW_O26_ConvDispInfoToTnlFmt(&cur0_inf);
			PE_NRD_HW_O26_DBG_PRINT_TNL_FMT_STATE(pInfo->tnl0a_fmt,cur0_tnl_fmt);
			if(pInfo->tnl0a_fmt!=cur0_tnl_fmt)
			{
				ret = PE_NRD_HW_O26_SetTnlDefault(cur0_tnl_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetTnlDefault() error.\n", __F__, __L__);
				pInfo->tnl0a_fmt=cur0_tnl_fmt;
			}
			/* tnr(nd1,2) */
			cur0_tnr_fmt = PE_NRD_HW_O26_ConvDispInfoToTnrFmt(&cur0_inf);
			PE_NRD_HW_O26_DBG_PRINT_TNR_FMT_STATE(pInfo->tnr0a_fmt,cur0_tnr_fmt);
			if(pInfo->tnr0a_fmt!=cur0_tnr_fmt)
			{
				ret = PE_NRD_HW_O26_SetTnrDefault(cur0_tnr_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_SetTnrDefault() error.\n", __F__, __L__);
					pInfo->tnr0a_fmt=cur0_tnr_fmt;
				/* to avoid racing ctrl fw<->driver, use dummy register */
				PE_ND0_O26_RdFL(nd_fsw_ctrl_03);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_nlvl_input_sel			  ,p_tnr_dflt->tnr_ctrl_22.reg_nlvl_input_sel	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_sc_detect_hres			  ,p_tnr_dflt->tnr_ctrl_22.reg_sc_detect_hres	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_clc_nt_pal				  ,p_tnr_dflt->tnr_ctrl_22.reg_clc_nt_pal		);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_clc_mem_wr_mode			  ,p_tnr_dflt->tnr_ctrl_22.reg_clc_mem_wr_mode	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_res				  ,p_tnr_dflt->tnr_ctrl_22.reg_sad_8x3_res		);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_iir_en			  ,p_tnr_dflt->tnr_ctrl_22.reg_sad_8x3_iir_en	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_chroma_en		  ,p_tnr_dflt->tnr_ctrl_22.reg_sad_8x3_chroma_en);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_sw 				  ,p_tnr_dflt->tnr_ctrl_22.reg_minfo_sw 		);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode10 			  ,p_tnr_dflt->tnr_ctrl_22.reg_minfo_mode10 	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_flt				  ,p_tnr_dflt->tnr_ctrl_22.reg_minfo_flt		);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_hfr_mask_en			  	  ,p_tnr_dflt->tnr_ctrl_22.reg_hfr_mask_en	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_decon_blend_en			  ,p_tnr_dflt->tnr_ctrl_22.reg_decon_blend_en	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode32 			  ,p_tnr_dflt->tnr_ctrl_22.reg_minfo_mode32 	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode74 			  ,p_tnr_dflt->tnr_ctrl_22.reg_minfo_mode74 	);
				PE_ND0_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_iir_alpha		  ,p_tnr_dflt->tnr_ctrl_22.reg_sad_8x3_iir_alpha);
				PE_ND0_O26_WrFL(nd_fsw_ctrl_03); 
				
			}
			/* dnr(dnr1,2) */
			cur0_dnr_fmt = PE_NRD_HW_O26_ConvDispInfoToDnrFmt(&cur0_inf);
			PE_NRD_HW_O26_DBG_PRINT_DNR_FMT_STATE(pInfo->dnr0a_fmt,cur0_dnr_fmt);
			if(pInfo->dnr0a_fmt!=cur0_dnr_fmt)
			{
				ret = PE_NRD_HW_O26_SetDnrDefault(cur0_dnr_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetDnrDefault() error.\n", __F__, __L__);
				pInfo->dnr0a_fmt=cur0_dnr_fmt;
			}
			/* cco dnr */
			#if 0
			cur0_cco_fmt = PE_NRD_HW_O26_ConvDispInfoToCCOFmt(&cur0_inf);
			PE_NRD_HW_O26_DBG_PRINT_CCO_FMT_STATE(pInfo->cco0a_fmt,cur0_cco_fmt);
			if(pInfo->cco0a_fmt!=cur0_cco_fmt)
			{
				ret = PE_NRD_HW_O26_SetCCODefault(cur0_cco_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetCCODefault() error.\n", __F__, __L__);
				pInfo->cco0a_fmt=cur0_cco_fmt;
			}
			#endif
			#ifdef PE_HW_O26_CHIPINFO_TABLE	/* O26F22_TBL */
			PE_CHPI_TNR_HW_O26F22_SetDefault();
			PE_CHPI_DNR_HW_O26F22_SetDefault();
			#endif
		}
		else if(PE_CHECK_WIN1(pstParams->win_id))
		{
			/* tnr lut (tnl) */
			cur1_tnl_fmt = PE_NRD_HW_O26_ConvDispInfoToTnl2ndFmt(&cur1_inf);
			PE_NRD_HW_O26_DBG_PRINT_TNL2ND_FMT_STATE(pInfo->tnl1a_fmt,cur1_tnl_fmt);
			if(pInfo->tnl1a_fmt!=cur1_tnl_fmt)
			{
				ret = PE_NRD_HW_O26_SetTnl2ndDefault(cur1_tnl_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetTnl2ndDefault() error.\n", __F__, __L__);
				pInfo->tnl1a_fmt=cur1_tnl_fmt;
			}
			/* tnr 2nd */
			cur1_tnr_fmt = PE_NRD_HW_O26_ConvDispInfoToTnr2ndFmt(&cur1_inf);
			PE_NRD_HW_O26_DBG_PRINT_TNR2ND_FMT_STATE(pInfo->tnr1a_fmt,cur1_tnr_fmt);
			if(pInfo->tnr1a_fmt!=cur1_tnr_fmt)
			{
				ret = PE_NRD_HW_O26_SetTnr2ndDefault(cur1_tnr_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_SetTnr2ndDefault() error.\n", __F__, __L__);
					pInfo->tnr1a_fmt=cur1_tnr_fmt;
				/* to avoid racing ctrl fw<->driver, use dummy register */
				PE_ND1_O26_RdFL(nd_fsw_ctrl_03);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_nlvl_input_sel			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_nlvl_input_sel	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sc_detect_hres			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sc_detect_hres	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_clc_nt_pal				  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_clc_nt_pal		);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_clc_mem_wr_mode			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_clc_mem_wr_mode	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_res				  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sad_8x3_res		);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_iir_en			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sad_8x3_iir_en	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_chroma_en		  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sad_8x3_chroma_en);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_sw 				  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_sw 		);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode10 			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_mode10 	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_flt				  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_flt		);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_hfr_mask_en			  	  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_hfr_mask_en	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_decon_blend_en			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_decon_blend_en	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode32 			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_mode32 	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode74 			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_mode74 	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_iir_alpha		  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sad_8x3_iir_alpha);
				PE_ND1_O26_WrFL(nd_fsw_ctrl_03);
			}
			/* dnr(dnr1,2) */
			#if 1
			cur1_dnr_fmt = PE_NRD_HW_O26_ConvDispInfoToDnrFmt(&cur1_inf);
			PE_NRD_HW_O26_DBG_PRINT_DNR_FMT_STATE(pInfo->dnr1a_fmt,cur1_dnr_fmt);
			if(pInfo->dnr1a_fmt!=cur1_dnr_fmt)
			{
				ret = PE_NRD_HW_O26_SetDnr2ndDefault(cur1_dnr_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetDnr2ndDefault() error.\n", __F__, __L__);
				pInfo->dnr1a_fmt=cur1_dnr_fmt;
			}
			#endif
		}
		else
		{
			/* do not setting tnr defulat setting. it is fixed as hd format cause multirun */
		}
		if(is_hfr) // 4k HFR input
		{
			/* tnr lut (tnl) */
			cur1_tnl_fmt = PE_NRD_O26_TNL2ND_HFR;
			PE_NRD_HW_O26_DBG_PRINT_TNL2ND_FMT_STATE(pInfo->tnl1a_fmt,cur1_tnl_fmt);
			if(pInfo->tnl1a_fmt!=cur1_tnl_fmt)
			{
				ret = PE_NRD_HW_O26_SetTnl2ndDefault(cur1_tnl_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetTnl2ndDefault() error.\n", __F__, __L__);
				pInfo->tnl1a_fmt=cur1_tnl_fmt;
			}
			/* tnr 2nd */
			cur1_tnr_fmt = PE_NRD_O26_TNR2ND_HFR;
			PE_NRD_HW_O26_DBG_PRINT_TNR2ND_FMT_STATE(pInfo->tnr1a_fmt,cur1_tnr_fmt);
			if(pInfo->tnr1a_fmt!=cur1_tnr_fmt)
			{
				ret = PE_NRD_HW_O26_SetTnr2ndDefault(cur1_tnr_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_SetTnr2ndDefault() error.\n", __F__, __L__);
					pInfo->tnr1a_fmt=cur1_tnr_fmt;
				/* to avoid racing ctrl fw<->driver, use dummy register */
				p_tnr2nd_dflt->tnr_ctrl_22.reg_decon_blend_en = 0;
				PE_ND1_O26_RdFL(nd_fsw_ctrl_03);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_nlvl_input_sel			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_nlvl_input_sel	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sc_detect_hres			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sc_detect_hres	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_clc_nt_pal				  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_clc_nt_pal		);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_clc_mem_wr_mode			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_clc_mem_wr_mode	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_res				  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sad_8x3_res		);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_iir_en			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sad_8x3_iir_en	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_chroma_en		  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sad_8x3_chroma_en);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_sw 				  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_sw 		);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode10 			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_mode10 	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_flt				  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_flt		);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_hfr_mask_en			  	  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_hfr_mask_en	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_decon_blend_en			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_decon_blend_en	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode32 			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_mode32 	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_minfo_mode74 			  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_minfo_mode74 	);
				PE_ND1_O26_Wr01(nd_fsw_ctrl_03, reg_sad_8x3_iir_alpha		  ,p_tnr2nd_dflt->tnr_ctrl_22.reg_sad_8x3_iir_alpha);
				PE_ND1_O26_WrFL(nd_fsw_ctrl_03);
			}
			/* dnr2nd */
			cur1_dnr_fmt = PE_NRD_O26_DNR_HFR;
			PE_NRD_HW_O26_DBG_PRINT_DNR_FMT_STATE(pInfo->dnr1a_fmt,cur1_dnr_fmt);
			if(pInfo->dnr1a_fmt!=cur1_dnr_fmt)
			{
				ret = PE_NRD_HW_O26_SetDnr2ndDefault(cur1_dnr_fmt);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetDnr2ndDefault() error.\n", __F__, __L__);
				pInfo->dnr1a_fmt=cur1_dnr_fmt;
			}
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set tnr default setting(for O26X)
 *
 * @param   cur0_tnr_fmt [in] PE_NRD_HW_O26_TNR_FMT
 * @return
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnrDefault(PE_NRD_HW_O26_TNR_FMT cur0_tnr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	switch(cur0_tnr_fmt)
	{
		case PE_NRD_O26_TNR_SD:
			PE_NRD_HW_O26_TNR_REG_TABLE(tnr_l_sd_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR_HD_I:
			PE_NRD_HW_O26_TNR_REG_TABLE(tnr_l_hd_i_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR_HD_P:
			PE_NRD_HW_O26_TNR_REG_TABLE(tnr_l_hd_p_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR_UD:
			PE_NRD_HW_O26_TNR_REG_TABLE(tnr_l_ud_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR_8K:
			PE_NRD_HW_O26_TNR_REG_TABLE(tnr_l_8k_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_tnr_fmt)
	{
		case PE_NRD_O26_TNR_SD:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr_l_sd_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR_HD_I:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr_l_hd_i_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR_HD_P:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr_l_hd_p_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR_UD:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr_l_ud_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR_8K:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr_l_8k_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set tnr default setting(for O26X)
 *
 * @param   cur0_tnr_fmt [in] PE_NRD_HW_O26_TNR_FMT
 * @return
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnr2ndDefault(PE_NRD_HW_O26_TNR2ND_FMT cur1_tnr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	switch(cur1_tnr_fmt)
	{
		case PE_NRD_O26_TNR2ND_SD:
			PE_NRD_HW_O26_TNR2ND_REG_TABLE(tnr2nd_l_sd_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR2ND_HD_I:
			PE_NRD_HW_O26_TNR2ND_REG_TABLE(tnr2nd_l_hd_i_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR2ND_HD_P:
			PE_NRD_HW_O26_TNR2ND_REG_TABLE(tnr2nd_l_hd_p_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR2ND_UD:
		case PE_NRD_O26_TNR2ND_HFR:
			PE_NRD_HW_O26_TNR2ND_REG_TABLE(tnr2nd_l_ud_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur1_tnr_fmt)
	{
		case PE_NRD_O26_TNR2ND_SD:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr2nd_l_sd_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR2ND_HD_I:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr2nd_l_hd_i_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR2ND_HD_P:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr2nd_l_hd_p_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_TNR2ND_UD:
			PE_SET_REG_TABLE(NRD_HW_O26,tnr2nd_l_ud_default_o26,   PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

__attribute__((unused)) static int PE_NRD_HW_O26_SetTnlDefault(PE_NRD_HW_O26_TNL_FMT cur0_tnl_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	switch(cur0_tnl_fmt)
	{
		case PE_NRD_O26_TNL_HD:
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL_REG_TABLE(tnr_l_lut_hd_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_O26_TNL_SD:
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL_REG_TABLE(tnr_l_lut_sd_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_O26_TNL_UHD:
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL_REG_TABLE(tnr_l_lut_ud_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		default:
			break;
	}
	#else
	switch(cur0_tnl_fmt)
	{
		case PE_NRD_O26_TNL_HD:
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_SET_REG_TABLE(NRD_HW_O26,tnr_l_lut_hd_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_O26_TNL_SD:
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_SET_REG_TABLE(NRD_HW_O26,tnr_l_lut_sd_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_O26_TNL_UHD:
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_SET_REG_TABLE(NRD_HW_O26,tnr_l_lut_ud_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND0_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnl2ndDefault(PE_NRD_HW_O26_TNL2ND_FMT cur1_tnl_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	switch(cur1_tnl_fmt)
	{
		case PE_NRD_O26_TNL_HD:
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL2ND_REG_TABLE(tnr2nd_l_lut_hd_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_O26_TNL_SD:
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL2ND_REG_TABLE(tnr2nd_l_lut_sd_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_O26_TNL_UHD:
		case PE_NRD_O26_TNL2ND_HFR:
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_NRD_HW_O26_TNL2ND_REG_TABLE(tnr2nd_l_lut_ud_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		default:
			break;
	}
	#else
	switch(cur1_tnl_fmt)
	{
		case PE_NRD_O26_TNL_HD:
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_SET_REG_TABLE(NRD_HW_O26,tnr2nd_l_lut_hd_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_O26_TNL_SD:
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_SET_REG_TABLE(NRD_HW_O26,tnr2nd_l_lut_sd_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		case PE_NRD_O26_TNL_UHD:
		case PE_NRD_O26_TNL2ND_HFR:
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00001000);
			PE_SET_REG_TABLE(NRD_HW_O26,tnr2nd_l_lut_ud_default_o26,   PE_O26_REG_WRITE_BASE);
			PE_ND1_O26_QWr(tnr_main_lut_00, 0x00008000);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

__attribute__((unused)) static int PE_NRD_HW_O26_SetDnrDefault(PE_NRD_HW_O26_DNR_FMT cur0_dnr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	switch(cur0_dnr_fmt)
	{
		case PE_NRD_O26_DNR_SD:
			PE_NRD_HW_O26_DNR_REG_TABLE(dnr_l_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_HD_I:
			PE_NRD_HW_O26_DNR_REG_TABLE(dnr_l_hd_i_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_HD_P:
			PE_NRD_HW_O26_DNR_REG_TABLE(dnr_l_hd_p_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_UD:
			PE_NRD_HW_O26_DNR_REG_TABLE(dnr_l_ud_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_SD_DTV:
			PE_NRD_HW_O26_DNR_REG_TABLE(dnr_l_dtv_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_dnr_fmt)
	{
		case PE_NRD_O26_DNR_SD:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr_l_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_HD_I:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr_l_hd_i_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_HD_P:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr_l_hd_p_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_UD:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr_l_ud_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_SD_DTV:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr_l_dtv_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
__attribute__((unused)) static int PE_NRD_HW_O26_SetDnr2ndDefault(PE_NRD_HW_O26_DNR_FMT cur1_dnr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	switch(cur1_dnr_fmt)
	{
		case PE_NRD_O26_DNR_SD:
			PE_NRD_HW_O26_DNR2ND_REG_TABLE(dnr2nd_l_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_HD_I:
			PE_NRD_HW_O26_DNR2ND_REG_TABLE(dnr2nd_l_hd_i_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_HD_P:
			PE_NRD_HW_O26_DNR2ND_REG_TABLE(dnr2nd_l_hd_p_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_UD:
		case PE_NRD_O26_DNR_HFR:
			PE_NRD_HW_O26_DNR2ND_REG_TABLE(dnr2nd_l_ud_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_SD_DTV:
			PE_NRD_HW_O26_DNR2ND_REG_TABLE(dnr2nd_l_dtv_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_dnr_fmt)
	{
		case PE_NRD_O26_DNR_SD:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr2nd_l_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_HD_I:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr2nd_l_hd_i_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_HD_P:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr2nd_l_hd_p_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_UD:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr2nd_l_ud_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_DNR_SD_DTV:
			PE_SET_REG_TABLE(NRD_HW_O26,dnr2nd_l_dtv_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
__attribute__((unused)) static int PE_NRD_HW_O26_SetCCODefault(PE_NRD_HW_O26_CCO_FMT cur0_cco_fmt)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	switch(cur0_cco_fmt)
	{
		case PE_NRD_O26_CCO_SD:
			PE_NRD_HW_O26_CCO_DNR_REG_TABLE(led_dnr_l_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_CCO_HD:
			PE_NRD_HW_O26_CCO_DNR_REG_TABLE(led_dnr_l_hd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_CCO_UD:
			PE_NRD_HW_O26_CCO_DNR_REG_TABLE(led_dnr_l_ud_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_CCO_8K:
			PE_NRD_HW_O26_CCO_DNR_REG_TABLE(led_dnr_l_8k_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_cco_fmt)
	{
		case PE_NRD_O26_LED_SD:
			PE_SET_REG_TABLE(NRD_HW_O26,led_dnr_l_sd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_LED_HD:
			PE_SET_REG_TABLE(NRD_HW_O26,led_dnr_l_hd_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_LED_UD:
			PE_SET_REG_TABLE(NRD_HW_O26,led_dnr_l_ud_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		case PE_NRD_O26_LED_8K:
			PE_SET_REG_TABLE(NRD_HW_O26,led_dnr_l_8k_default_o26,	 PE_O26_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * get tnr fmt from display info.(for O26X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_O26_TNR_FMT
 * @see
 * @author
 */
__attribute__((unused)) static PE_NRD_HW_O26_TNR_FMT PE_NRD_HW_O26_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_O26_TNR_FMT tnr_fmt = PE_NRD_O26_TNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			tnr_fmt = PE_NRD_O26_TNR_SD;
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_NRD_O26_TNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					tnr_fmt = PE_NRD_O26_TNR_HD_I;
				else
					tnr_fmt = PE_NRD_O26_TNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				if(disp_inf->sub_mode == LX_DE_SUB_MODE_PBP || disp_inf->sub_mode == LX_DE_SUB_MODE_DUALMON)//pbp mode
					tnr_fmt = PE_NRD_O26_TNR_HD_P;
				else
					tnr_fmt = PE_NRD_O26_TNR_UD;
			}
			else
			{
				if(disp_inf->sub_mode == LX_DE_SUB_MODE_PBP || disp_inf->sub_mode == LX_DE_SUB_MODE_DUALMON)//pbp mode
					tnr_fmt = PE_NRD_O26_TNR_HD_P;
				else
					tnr_fmt = PE_NRD_O26_TNR_8K;
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_NRD_O26_TNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					tnr_fmt = PE_NRD_O26_TNR_HD_I;
				else
					tnr_fmt = PE_NRD_O26_TNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				if(disp_inf->sub_mode == LX_DE_SUB_MODE_PBP || disp_inf->sub_mode == LX_DE_SUB_MODE_DUALMON)//pbp mode
					tnr_fmt = PE_NRD_O26_TNR_HD_P;
				else
					tnr_fmt = PE_NRD_O26_TNR_UD;
			}
			else
			{
				if(disp_inf->sub_mode == LX_DE_SUB_MODE_PBP || disp_inf->sub_mode == LX_DE_SUB_MODE_DUALMON)//pbp mode
					tnr_fmt = PE_NRD_O26_TNR_HD_P;
				else
					tnr_fmt = PE_NRD_O26_TNR_8K;
			}
			break;
	}
	return tnr_fmt;
}
/**
 * get tnr fmt from display info.(for O26X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_O26_TNR_FMT
 * @see
 * @author
 */
__attribute__((unused)) static PE_NRD_HW_O26_TNR2ND_FMT PE_NRD_HW_O26_ConvDispInfoToTnr2ndFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_O26_TNR2ND_FMT tnr_fmt = PE_NRD_O26_TNR2ND_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			tnr_fmt = PE_NRD_O26_TNR2ND_SD;
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_NRD_O26_TNR2ND_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					tnr_fmt = PE_NRD_O26_TNR2ND_HD_I;
				else
					tnr_fmt = PE_NRD_O26_TNR2ND_HD_P;
			}
			else
			{
				if(disp_inf->sub_mode == LX_DE_SUB_MODE_PBP || disp_inf->sub_mode == LX_DE_SUB_MODE_DUALMON)//pbp mode
					tnr_fmt = PE_NRD_O26_TNR2ND_HD_P;
				else
					tnr_fmt = PE_NRD_O26_TNR2ND_UD;
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_NRD_O26_TNR2ND_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					tnr_fmt = PE_NRD_O26_TNR2ND_HD_I;
				else
					tnr_fmt = PE_NRD_O26_TNR2ND_HD_P;
			}
			else
			{
				if(disp_inf->sub_mode == LX_DE_SUB_MODE_PBP || disp_inf->sub_mode == LX_DE_SUB_MODE_DUALMON)//pbp mode
					tnr_fmt = PE_NRD_O26_TNR2ND_HD_P;
				else
					tnr_fmt = PE_NRD_O26_TNR2ND_UD;
			}
			break;
	}
	return tnr_fmt;
}

/**
 * get tnr lut (tnl) fmt from display info.(for O26X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_O26_TNL_FMT
 * @see
 * @author
 */
__attribute__((unused)) static PE_NRD_HW_O26_TNL_FMT PE_NRD_HW_O26_ConvDispInfoToTnlFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_O26_TNL_FMT tnl_fmt = PE_NRD_O26_TNL_NUM;
	/* skip drv tnr ctrl, if fw tnr on. */
	if (PE_CMN_HW_O26_GetDbInfo(PE_CMN_HW_O26_DB_INF_MD0_TNR_FW_EN, 0))
	{
		tnl_fmt = PE_NRD_O26_TNL_NUM;	//NA
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
					tnl_fmt = PE_NRD_O26_TNL_SD;
				}
				break;
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					tnl_fmt = PE_NRD_O26_TNL_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					tnl_fmt = PE_NRD_O26_TNL_HD;
				}
				else 
				{
					tnl_fmt = PE_NRD_O26_TNL_UHD;
				}
				break;
		}
	}
	return tnl_fmt;
}

/**
 * get tnr2nd lut (tnl) fmt from display info.(for O26X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_O26_TNL_FMT
 * @see
 * @author
 */
__attribute__((unused)) static PE_NRD_HW_O26_TNL2ND_FMT PE_NRD_HW_O26_ConvDispInfoToTnl2ndFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_O26_TNL2ND_FMT tnl_fmt = PE_NRD_O26_TNL2ND_NUM;
	/* skip drv tnr ctrl, if fw tnr on. */
	if (PE_CMN_HW_O26_GetDbInfo(PE_CMN_HW_O26_DB_INF_MD0_TNR_FW_EN, 0))
	{
		tnl_fmt = PE_NRD_O26_TNL2ND_NUM;	//NA
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
					tnl_fmt = PE_NRD_O26_TNL2ND_SD;
				}
				break;
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					tnl_fmt = PE_NRD_O26_TNL2ND_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					tnl_fmt = PE_NRD_O26_TNL2ND_HD;
				}
				else 
				{
					tnl_fmt = PE_NRD_O26_TNL2ND_UHD;
				}
				break;
		}
	}
	return tnl_fmt;
}

/**
 * get dnr fmt from display info.(for O26X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_O26_DNR_FMT
 * @see
 * @author
 */
__attribute__((unused)) static PE_NRD_HW_O26_DNR_FMT PE_NRD_HW_O26_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_O26_DNR_FMT dnr_fmt = PE_NRD_O26_DNR_NUM;
	PE_DBG_NRD("DnrFmt g_pe_inf_o26_vr360_mode: %d.\n", g_pe_inf_o26_vr360_mode);
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			{
				dnr_fmt = PE_NRD_O26_DNR_SD;
			}
			break;
		case LX_PE_SRC_DTV:
			{
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					dnr_fmt = PE_NRD_O26_DNR_SD_DTV;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
						dnr_fmt = PE_NRD_O26_DNR_HD_I;
					else
						dnr_fmt = PE_NRD_O26_DNR_HD_P;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
				{
					if(disp_inf->sub_mode == LX_DE_SUB_MODE_PBP || disp_inf->sub_mode == LX_DE_SUB_MODE_DUALMON)//pbp mode
						dnr_fmt = PE_NRD_O26_DNR_HD_P;
					else
						dnr_fmt = PE_NRD_O26_DNR_UD;
				}
				else
				{
					dnr_fmt = PE_NRD_O26_DNR_8K;
				}
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				dnr_fmt = PE_NRD_O26_DNR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
					dnr_fmt = PE_NRD_O26_DNR_HD_I;
				else
					dnr_fmt = PE_NRD_O26_DNR_HD_P;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				if(disp_inf->sub_mode == LX_DE_SUB_MODE_PBP || disp_inf->sub_mode == LX_DE_SUB_MODE_DUALMON)//pbp mode
					dnr_fmt = PE_NRD_O26_DNR_HD_P;
				else
					dnr_fmt = PE_NRD_O26_DNR_UD;
			}
			else
			{
				dnr_fmt = PE_NRD_O26_DNR_8K;
			}
			break;
	}
	return dnr_fmt;
}
#if 0
/**
 * get psp fmt from display info.(for O26X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_O26_PSP_FMT
 * @see
 * @author
 */
__attribute__((unused)) static PE_NRD_HW_O26_PSP_FMT PE_NRD_HW_O26_ConvDispInfoToPspFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_O26_PSP_FMT psp_fmt = PE_NRD_O26_PSP_NUM;
	PE_DBG_NRD("DnrFmt g_pe_inf_o26_vr360_mode: %d.\n", g_pe_inf_o26_vr360_mode);
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
		case LX_PE_SRC_RGBPC:
			{
				psp_fmt = PE_NRD_O26_PSP_SD;
			}
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				psp_fmt = PE_NRD_O26_PSP_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				psp_fmt = PE_NRD_O26_PSP_HD;
			}
			else
			{
				psp_fmt = PE_NRD_O26_PSP_UD;
			}
			break;
	}
	return psp_fmt;
}
/**
 * get ifc fmt from display info.(for O26X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_O26_IFC_FMT
 * @see
 * @author
 */
static PE_NRD_HW_O26_IFC_FMT PE_NRD_HW_O26_ConvDispInfoToIfcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_O26_IFC_FMT ifc_fmt = PE_NRD_O26_IFC_NUM;
	if(disp_inf->mode.is_vr)
	{
		ifc_fmt = PE_NRD_O26_IFC_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				if(disp_inf->cstd_type==LX_PE_CSTD_NTSC)
				{
					ifc_fmt = PE_NRD_O26_IFC_ATV_NTSC;
				}
				else
				{
					ifc_fmt = PE_NRD_O26_IFC_PC;
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
					ifc_fmt = PE_NRD_O26_IFC_PC;
				}
				break;
		}
	}
	return ifc_fmt;
}
#endif
/**
 * get led fmt from display info.(for O26X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_O26_LED_FMT
 * @see
 * @author
 */
__attribute__((unused)) static PE_NRD_HW_O26_CCO_FMT PE_NRD_HW_O26_ConvDispInfoToCCOFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_O26_CCO_FMT led_fmt = PE_NRD_O26_CCO_NUM;
	//PE_DBG_NRD("DnrFmt g_pe_inf_o26_vr360_mode: %d.\n", g_pe_inf_o26_vr360_mode);
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
				led_fmt = PE_NRD_O26_CCO_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				led_fmt = PE_NRD_O26_CCO_HD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_UHD)
			{
				led_fmt = PE_NRD_O26_CCO_UD;
			}
			else
			{
				led_fmt = PE_NRD_O26_CCO_8K;
			}
			break;
	}
	return led_fmt;
}


/**
 * read default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_RdDefault(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 param_size=0, table_size=0, is_valid=0;
	UINT32 rd_cnt=0;
	PE_REG_PARAM_T param;
	PE_NRD_HW_O26_SETTINGS_T *pInfo=&_g_pe_nrd_hw_o26_info;

#define PE_NRD_O26_NO_PRINT			0
#define PE_NRD_O26_RD_N_HEX_PRINT	1
#define PE_NRD_O26_HEX_PRINT_ONLY	2
#define PE_NRD_O26_PRINT_START		"START_OF_PRINT"
#define PE_NRD_O26_PRINT_END		"END_OF_PRINT"
#define PE_NRD_O26_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_NRD_O26_PRINT_RESRV		"RESERVED"
#define PE_NRD_O26_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, "   [0x%02x] %s\n", (_item), #_item);_action;break
#define PE_NRD_O26_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break
#define PE_NRD_O26_DFLT_SPRINT(_action, _buf, fmt, args...)		\
	default:snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		
		if (PE_KDRV_VER_O26)
		{
			__attribute__((unused)) UINT32 *p_tnr1b_dflt = _g_pe_tnr_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnr1b_user = _g_pe_tnr_hw_param_data_o26.nd1_user.addr;
			__attribute__((unused)) UINT32 *p_tnr1b_mask = _g_pe_tnr_hw_param_data_o26.nd1_mask.addr;
			__attribute__((unused)) UINT32 *p_tnr1b_data = _g_pe_tnr_hw_param_data_o26.nd1_data.addr;
			__attribute__((unused)) UINT32 *p_tnr2b_dflt = _g_pe_tnr2nd_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnr2b_user = _g_pe_tnr2nd_hw_param_data_o26.nd1_user.addr;
			__attribute__((unused)) UINT32 *p_tnr2b_mask = _g_pe_tnr2nd_hw_param_data_o26.nd1_mask.addr;
			__attribute__((unused)) UINT32 *p_tnr2b_data = _g_pe_tnr2nd_hw_param_data_o26.nd1_data.addr;
			__attribute__((unused)) UINT32 *p_tnr3b_dflt = _g_pe_tnr3rd_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnr3b_user = _g_pe_tnr3rd_hw_param_data_o26.nd1_user.addr;
			__attribute__((unused)) UINT32 *p_tnr3b_mask = _g_pe_tnr3rd_hw_param_data_o26.nd1_mask.addr;
			__attribute__((unused)) UINT32 *p_tnr3b_data = _g_pe_tnr3rd_hw_param_data_o26.nd1_data.addr;
			__attribute__((unused)) UINT32 *p_dnr1b_dflt = _g_pe_dnr_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_dnr1b_user = _g_pe_dnr_hw_param_data_o26.reg_user.addr;
			__attribute__((unused)) UINT32 *p_dnr1b_mask = _g_pe_dnr_hw_param_data_o26.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_dnr1b_data = _g_pe_dnr_hw_param_data_o26.reg_data.addr;
			__attribute__((unused)) UINT32 *p_dnr2b_dflt = _g_pe_dnr2nd_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_dnr2b_user = _g_pe_dnr2nd_hw_param_data_o26.reg_user.addr;
			__attribute__((unused)) UINT32 *p_dnr2b_mask = _g_pe_dnr2nd_hw_param_data_o26.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_dnr2b_data = _g_pe_dnr2nd_hw_param_data_o26.reg_data.addr;
			__attribute__((unused)) UINT32 *p_tnl1b_dflt = _g_pe_tnl_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnl1b_user = _g_pe_tnl_hw_param_data_o26.reg_user.addr;
			__attribute__((unused)) UINT32 *p_tnl1b_mask = _g_pe_tnl_hw_param_data_o26.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_tnl1b_data = _g_pe_tnl_hw_param_data_o26.reg_data.addr;
			__attribute__((unused)) UINT32 *p_tnl2b_dflt = _g_pe_tnl2nd_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnl2b_user = _g_pe_tnl2nd_hw_param_data_o26.reg_user.addr;
			__attribute__((unused)) UINT32 *p_tnl2b_mask = _g_pe_tnl2nd_hw_param_data_o26.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_tnl2b_data = _g_pe_tnl2nd_hw_param_data_o26.reg_data.addr;
			__attribute__((unused)) UINT32 *p_tnl3b_dflt = _g_pe_tnl3rd_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_tnl3b_user = _g_pe_tnl3rd_hw_param_data_o26.reg_user.addr;
			__attribute__((unused)) UINT32 *p_tnl3b_mask = _g_pe_tnl3rd_hw_param_data_o26.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_tnl3b_data = _g_pe_tnl3rd_hw_param_data_o26.reg_data.addr;
			__attribute__((unused)) UINT32 *p_cco1b_dflt = _g_pe_cco_dnr_hw_param_data_o26.reg_dflt.addr;
			__attribute__((unused)) UINT32 *p_cco1b_user = _g_pe_cco_dnr_hw_param_data_o26.reg_user.addr;
			__attribute__((unused)) UINT32 *p_cco1b_mask = _g_pe_cco_dnr_hw_param_data_o26.reg_mask.addr;
			__attribute__((unused)) UINT32 *p_cco1b_data = _g_pe_cco_dnr_hw_param_data_o26.reg_data.addr;
			CHECK_KNULL(p_tnr1b_dflt);
			CHECK_KNULL(p_tnr1b_user);
			CHECK_KNULL(p_tnr1b_mask);
			CHECK_KNULL(p_tnr1b_data);
			CHECK_KNULL(p_dnr1b_dflt);
			CHECK_KNULL(p_dnr1b_user);
			CHECK_KNULL(p_dnr1b_mask);
			CHECK_KNULL(p_dnr1b_data);
			CHECK_KNULL(p_cco1b_dflt);
			CHECK_KNULL(p_cco1b_user);
			CHECK_KNULL(p_cco1b_mask);
			CHECK_KNULL(p_cco1b_data);
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]>=PE_NRD_HW_O26_RD_MENU_MAX)
			{
				snprintf(buffer, PE_TRACE_STR_SIZE, "%s", PE_NRD_O26_PRINT_EXIT);
				rd_cnt=0;
			}
			else if (pstParams->data[0]==PE_NRD_HW_O26_RD_MENU_DISP)
			{
				switch (rd_cnt)
				{
					PE_NRD_O26_CASE_SPRINT( 0, rd_cnt++, buffer, PE_NRD_O26_PRINT_START);
					PE_NRD_O26_CASE_SPRINT( 1, rd_cnt++, buffer, "   ** current default **\n");
					PE_NRD_O26_CASE_SPRINT( 2, rd_cnt++, buffer, \
						"   tnr0a_fmt : %s\n", PE_NRD_HW_O26_TNR_FMT_TO_STR(pInfo->tnr0a_fmt));
					PE_NRD_O26_CASE_SPRINT( 3, rd_cnt++, buffer, \
						"   tnr1a_fmt : %s\n", PE_NRD_HW_O26_TNR2ND_FMT_TO_STR(pInfo->tnr1a_fmt));
					PE_NRD_O26_CASE_SPRINT( 4, rd_cnt++, buffer, \
						"   tnr2a_fmt : %s\n", PE_NRD_HW_O26_TNR2ND_FMT_TO_STR(pInfo->tnr2a_fmt));
					PE_NRD_O26_CASE_SPRINT( 5, rd_cnt++, buffer, \
						"   dnr0a_fmt : %s\n", PE_NRD_HW_O26_DNR_FMT_TO_STR(pInfo->dnr0a_fmt));
					PE_NRD_O26_CASE_SPRINT( 6, rd_cnt++, buffer, \
						"   dnr1a_fmt : %s\n", PE_NRD_HW_O26_DNR_FMT_TO_STR(pInfo->dnr1a_fmt));
					PE_NRD_O26_CASE_SPRINT( 7, rd_cnt++, buffer, \
						"   tnl0a_fmt : %s\n", PE_NRD_HW_O26_TNL_FMT_TO_STR(pInfo->tnl0a_fmt));
					PE_NRD_O26_CASE_SPRINT( 8, rd_cnt++, buffer, \
						"   tnl1a_fmt : %s\n", PE_NRD_HW_O26_TNL2ND_FMT_TO_STR(pInfo->tnl1a_fmt));
					PE_NRD_O26_CASE_SPRINT( 9, rd_cnt++, buffer, \
						"   tnl2a_fmt : %s\n", PE_NRD_HW_O26_TNL2ND_FMT_TO_STR(pInfo->tnl2a_fmt));
					PE_NRD_O26_CASE_SPRINT(10, rd_cnt++, buffer, \
						"   cco0a_fmt : %s\n", PE_NRD_HW_O26_CCO_FMT_TO_STR(pInfo->cco0a_fmt));
					PE_NRD_O26_CASE_SPRINT(11, rd_cnt++, buffer, PE_NRD_O26_PRINT_RESRV);
					PE_NRD_O26_CASE_SPRINT(12, rd_cnt++, buffer, "   *********************\n");
					PE_NRD_O26_CASE_PRMENU(13, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR1_DISP);
					PE_NRD_O26_CASE_PRMENU(14, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR1_DFLT);
					PE_NRD_O26_CASE_PRMENU(15, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR1_USER);
					PE_NRD_O26_CASE_PRMENU(16, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR1_MASK);
					PE_NRD_O26_CASE_PRMENU(17, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR1_DATA);
					PE_NRD_O26_CASE_PRMENU(18, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR2_DISP);
					PE_NRD_O26_CASE_PRMENU(19, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR2_DFLT);
					PE_NRD_O26_CASE_PRMENU(20, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR2_USER);
					PE_NRD_O26_CASE_PRMENU(21, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR2_MASK);
					PE_NRD_O26_CASE_PRMENU(22, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR2_DATA);
					PE_NRD_O26_CASE_PRMENU(23, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR3_DISP);
					PE_NRD_O26_CASE_PRMENU(24, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR3_DFLT);
					PE_NRD_O26_CASE_PRMENU(25, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR3_USER);
					PE_NRD_O26_CASE_PRMENU(26, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR3_MASK);
					PE_NRD_O26_CASE_PRMENU(27, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR3_DATA);
					PE_NRD_O26_CASE_PRMENU(28, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR1_DISP);
					PE_NRD_O26_CASE_PRMENU(29, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR1_DFLT);
					PE_NRD_O26_CASE_PRMENU(30, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR1_USER);
					PE_NRD_O26_CASE_PRMENU(31, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR1_MASK);
					PE_NRD_O26_CASE_PRMENU(32, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR1_DATA);
					PE_NRD_O26_CASE_PRMENU(33, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR2_DISP);
					PE_NRD_O26_CASE_PRMENU(34, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR2_DFLT);
					PE_NRD_O26_CASE_PRMENU(35, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR2_USER);
					PE_NRD_O26_CASE_PRMENU(36, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR2_MASK);
					PE_NRD_O26_CASE_PRMENU(37, rd_cnt++, buffer, PE_NRD_HW_O26_RD_DNR2_DATA);
					PE_NRD_O26_CASE_PRMENU(38, rd_cnt++, buffer, PE_NRD_HW_O26_RD_CCO1_DISP);
					PE_NRD_O26_CASE_PRMENU(39, rd_cnt++, buffer, PE_NRD_HW_O26_RD_CCO1_DFLT);
					PE_NRD_O26_CASE_PRMENU(40, rd_cnt++, buffer, PE_NRD_HW_O26_RD_CCO1_USER);
					PE_NRD_O26_CASE_PRMENU(41, rd_cnt++, buffer, PE_NRD_HW_O26_RD_CCO1_MASK);
					PE_NRD_O26_CASE_PRMENU(42, rd_cnt++, buffer, PE_NRD_HW_O26_RD_CCO1_DATA);
					PE_NRD_O26_CASE_SPRINT(43, rd_cnt++, buffer, "   *********************\n");
					PE_NRD_O26_CASE_PRMENU(44, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR1_MLUT);
					PE_NRD_O26_CASE_PRMENU(45, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL1_DFLT);
					PE_NRD_O26_CASE_PRMENU(46, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL1_USER);
					PE_NRD_O26_CASE_PRMENU(47, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL1_MASK);
					PE_NRD_O26_CASE_PRMENU(48, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL1_DATA);
					PE_NRD_O26_CASE_PRMENU(49, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR2_MLUT);
					PE_NRD_O26_CASE_PRMENU(50, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL2_DFLT);
					PE_NRD_O26_CASE_PRMENU(51, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL2_USER);
					PE_NRD_O26_CASE_PRMENU(52, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL2_MASK);
					PE_NRD_O26_CASE_PRMENU(53, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL2_DATA);
					PE_NRD_O26_CASE_PRMENU(54, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNR3_MLUT);
					PE_NRD_O26_CASE_PRMENU(55, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL3_DFLT);
					PE_NRD_O26_CASE_PRMENU(56, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL3_USER);
					PE_NRD_O26_CASE_PRMENU(57, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL3_MASK);
					PE_NRD_O26_CASE_PRMENU(58, rd_cnt++, buffer, PE_NRD_HW_O26_RD_TNL3_DATA);
					PE_NRD_O26_CASE_SPRINT(59, rd_cnt++, buffer, PE_NRD_O26_PRINT_RESRV);
					PE_NRD_O26_CASE_SPRINT(60, rd_cnt++, buffer, PE_NRD_O26_PRINT_RESRV);
					PE_NRD_O26_CASE_SPRINT(61, rd_cnt++, buffer, PE_NRD_O26_PRINT_RESRV);
					PE_NRD_O26_CASE_SPRINT(62, rd_cnt++, buffer, PE_NRD_O26_PRINT_RESRV);
					PE_NRD_O26_DFLT_SPRINT(rd_cnt=0, buffer, PE_NRD_O26_PRINT_END);
				}
			}
			else
			{
				is_valid = PE_NRD_O26_NO_PRINT;
				switch (pstParams->data[0])
				{
					case PE_NRD_HW_O26_RD_TNR1_DISP:
						table_size = sizeof(tnr_l_hd_i_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR1_DFLT:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_tnr1b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR1_USER:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_tnr1b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR1_MASK:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_tnr1b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR1_DATA:
						table_size = sizeof(PE_TNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_tnr1b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR2_DISP:
						table_size = sizeof(tnr2nd_l_hd_i_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR2_DFLT:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_tnr2b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR2_USER:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_tnr2b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR2_MASK:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_tnr2b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR2_DATA:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_tnr2b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR3_DISP:
						table_size = sizeof(tnr3rd_l_hd_p_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_hd_p_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR3_DFLT:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_hd_p_default_o26[rd_cnt].addr;
							param.data = p_tnr2b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR3_USER:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_hd_p_default_o26[rd_cnt].addr;
							param.data = p_tnr2b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR3_MASK:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_hd_p_default_o26[rd_cnt].addr;
							param.data = p_tnr2b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR3_DATA:
						table_size = sizeof(PE_TNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_hd_p_default_o26[rd_cnt].addr;
							param.data = p_tnr2b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR1_DISP:
						table_size = sizeof(dnr_l_hd_i_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR1_DFLT:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_dnr1b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR1_USER:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_dnr1b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR1_MASK:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_dnr1b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR1_DATA:
						table_size = sizeof(PE_DNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_dnr1b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR2_DISP:
						table_size = sizeof(dnr2nd_l_hd_i_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = dnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR2_DFLT:
						table_size = sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_dnr1b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR2_USER:
						table_size = sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_dnr1b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR2_MASK:
						table_size = sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_dnr1b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_DNR2_DATA:
						table_size = sizeof(PE_DNR2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = dnr2nd_l_hd_i_default_o26[rd_cnt].addr;
							param.data = p_dnr1b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_CCO1_DISP:
						table_size = sizeof(cco_dec_l_ud_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = cco_dec_l_ud_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_CCO1_DFLT:
						table_size = sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cco_dec_l_ud_default_o26[rd_cnt].addr;
							param.data = p_cco1b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_CCO1_USER:
						table_size = sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cco_dec_l_ud_default_o26[rd_cnt].addr;
							param.data = p_cco1b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_CCO1_MASK:
						table_size = sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cco_dec_l_ud_default_o26[rd_cnt].addr;
							param.data = p_cco1b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_CCO1_DATA:
						table_size = sizeof(PE_CCO_DNR_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cco_dec_l_ud_default_o26[rd_cnt].addr;
							param.data = p_cco1b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR1_MLUT:
						table_size = sizeof(tnr_l_lut_hd_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL1_DFLT:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl1b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL1_USER:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl1b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL1_MASK:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl1b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL1_DATA:
						table_size = sizeof(PE_TNL_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl1b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR2_MLUT:
						table_size = sizeof(tnr2nd_l_lut_hd_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_lut_hd_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL2_DFLT:
						table_size = sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl2b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL2_USER:
						table_size = sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl2b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL2_MASK:
						table_size = sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl2b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL2_DATA:
						table_size = sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr2nd_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl2b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNR3_MLUT:
						table_size = sizeof(tnr3rd_l_lut_hd_default_o26);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_lut_hd_default_o26[rd_cnt].addr;
							is_valid = PE_NRD_O26_RD_N_HEX_PRINT;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL3_DFLT:
						table_size = sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl3b_dflt[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL3_USER:
						table_size = sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl3b_user[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL3_MASK:
						table_size = sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl3b_mask[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					case PE_NRD_HW_O26_RD_TNL3_DATA:
						table_size = sizeof(PE_TNL2ND_HW_PARAM_REG_O26_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = tnr3rd_l_lut_hd_default_o26[rd_cnt].addr;
							param.data = p_tnl3b_data[rd_cnt];
							is_valid = PE_NRD_O26_HEX_PRINT_ONLY;
						}
						break;
					default:
						break;
				}
				if (is_valid == PE_NRD_O26_RD_N_HEX_PRINT)
				{
					#ifdef INCLUDE_KDRV_SYS
					//param.data = SYS_IO_WriteRegArray(param.addr);
					SYS_IO_WriteRegArray(param.addr, 4, &param.data);
					#else
					param.data = 0;
					#endif
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else if (is_valid == PE_NRD_O26_HEX_PRINT_ONLY)
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "%s", PE_NRD_O26_PRINT_END);
					rd_cnt = 0;
				}
			}
			memcpy(pstParams->data, buffer, sizeof(char)*PE_TRACE_STR_SIZE);
		}
	}while (0);
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set dnr common ctrl
 * - use input struct LX_PE_NRD_DNR6_CMN_T
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT8 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_CMN_T *ctrl_param =(LX_PE_NRD_DNR_CMN_T *)pstParams;
			LX_PE_NRD_DNR4_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			LX_PE_NRD_EASY_DNR_CMN_T *epp = (typeof(*epp) *)ctrl_param->data;
			static LX_PE_NRD_DNR4_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DNR4_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DNR("duplicated DB : LX_PE_NRD_DNR3_CMN_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DNR("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd32 =  pp->dnr______ui;
					PE_DBG_DNR("set[%d] : dnr______ui\n"
					"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
					pd32[10], pd32[11], pd32[12]);
					pd32 = pp->dnr____buff;
					PE_DBG_DNR("set[%d] : dnr____buff\n"\
					"dnr____buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
					#if 1
					#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
					PE_NRD_HW_O26_DNR_WR01(dnr_max_ctrl,	reg_dnr_max_enable, GET_BITS(pp->dnr______ui[0],0,1));
					#if 0
					PE_NRD_HW_O26_DNR_WR02(mnr_ctrl_0,		reg_mnr_chroma_en,	GET_BITS(pp->dnr______ui[1],0,1),\
																reg_mnr_enable, GET_BITS(pp->dnr______ui[2],0,1));
					#else
					PE_NRD_HW_O26_NR0_VERI_WR02(mnr_ctrl_0, reg_mnr_chroma_en,	GET_BITS(pp->dnr______ui[1],0,1),\
																	 reg_mnr_enable, GET_BITS(pp->dnr______ui[2],0,1));
					#endif
					PE_NRD_HW_O26_DNR_WR02(dc_bnr_ctrl_0,	reg_dc_bnr_enable,	GET_BITS(pp->dnr______ui[3],0,1),\
															reg_obj_gain_mul,	GET_BITS(pp->dnr______ui[4],0,2));
					PE_NRD_HW_O26_DNR_WR04(ac_bnr_ctrl_0,	reg_bnr_ac_v_chroma_en, GET_BITS(pp->dnr______ui[5],0,1),\
															reg_bnr_ac_h_chroma_en, GET_BITS(pp->dnr______ui[6],0,1),\
															reg_bnr_ac_v_en,		GET_BITS(pp->dnr______ui[7],0,1),\
															reg_bnr_ac_h_en,		GET_BITS(pp->dnr______ui[8],0,1));
					#ifdef PE_HW_O26_REG_SMR_CTRL_00
					#if 0
					PE_NRD_HW_O26_DNR_WR02(reg_smr_ctrl_00,	reg_smr_master_en_yy,	GET_BITS(pp->dnr______ui[9],0,1),\
															reg_smr_master_en_cc,	GET_BITS(pp->dnr______ui[10],0,1));
					#endif
					PE_NRD_HW_O26_DNR_SET_USER(reg_smr_ctrl_00,	reg_smr_master_en_yy,	GET_BITS(pp->dnr______ui[9],0,1));
					PE_NRD_HW_O26_DNR_SET_USER(reg_smr_ctrl_00,	reg_smr_master_en_cc,	GET_BITS(pp->dnr______ui[10],0,1));
					#endif

					#endif
					/* download dnr user db */
					ret = PE_NRD_HW_O26_DownloadDnrUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadDnrUserDb() error.\n",__F__,__L__);
					#endif
				}
				else
				{
					PE_DBG_DNR("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					epp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = epp->data;
					PE_DBG_DNR("set[%d] : data\n"
					"data    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"data    [10]0x%02X,0x%02X,\n",\
					epp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11]);
					#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
					PE_NRD_HW_O26_DNR_WR01(dnr_max_ctrl,    reg_dnr_max_enable,     GET_BITS(epp->data[0], 0, 1));
					PE_DNR0_O26_QWr03(mnr_ctrl_0,      reg_mnr_master_gain,    GET_BITS(epp->data[1], 0, 8),\
					                                        reg_mnr_chroma_en,      GET_BITS(epp->data[2], 0, 1),\
					                                        reg_mnr_enable,         GET_BITS(epp->data[3], 0, 1));
					PE_NRD_HW_O26_DNR_WR01(dc_bnr_ctrl_0,   reg_dc_bnr_enable,      GET_BITS(epp->data[4], 0, 1));
					PE_NRD_HW_O26_DNR_WR02(dc_bnr_ctrl_2,   reg_dc_bnr_chromagain,  GET_BITS(epp->data[5], 0, 8),\
					                                        reg_dc_bnr_mastergain,  GET_BITS(epp->data[6], 0, 6));
					PE_NRD_HW_O26_DNR_WR04(ac_bnr_ctrl_0,   reg_bnr_ac_v_chroma_en, GET_BITS(epp->data[7], 0, 1),\
					                                        reg_bnr_ac_h_chroma_en, GET_BITS(epp->data[8], 0, 1),\
					                                        reg_bnr_ac_v_en,        GET_BITS(epp->data[9], 0, 1),\
					                                        reg_bnr_ac_h_en,        GET_BITS(epp->data[10], 0, 1));
					PE_NRD_HW_O26_DNR_WR01(ac_bnr_ctrl_9,   reg_ac_master_y_gain,   GET_BITS(epp->data[11], 0, 8));
					#else
					PE_DNR0_O26_QWr01(dnr_max_ctrl,    		reg_dnr_max_enable,     GET_BITS(epp->data[0], 0, 1));
					PE_DNR0_O26_QWr03(mnr_ctrl_0,      		reg_mnr_master_gain,    GET_BITS(epp->data[1], 0, 8),\
					                                        reg_mnr_chroma_en,      GET_BITS(epp->data[2], 0, 1),\
					                                        reg_mnr_enable,         GET_BITS(epp->data[3], 0, 1));
					PE_DNR0_O26_QWr01(dc_bnr_ctrl_0,   		reg_dc_bnr_enable,      GET_BITS(epp->data[4], 0, 1));
					PE_DNR0_O26_QWr02(dc_bnr_ctrl_2,   		reg_dc_bnr_chromagain,  GET_BITS(epp->data[5], 0, 8),\
					                                        reg_dc_bnr_mastergain,  GET_BITS(epp->data[6], 0, 6));
					PE_DNR0_O26_QWr04(ac_bnr_ctrl_0,   		reg_bnr_ac_v_chroma_en, GET_BITS(epp->data[7], 0, 1),\
					                                        reg_bnr_ac_h_chroma_en, GET_BITS(epp->data[8], 0, 1),\
					                                        reg_bnr_ac_v_en,        GET_BITS(epp->data[9], 0, 1),\
					                                        reg_bnr_ac_h_en,        GET_BITS(epp->data[10], 0, 1));
					PE_DNR0_O26_QWr01(ac_bnr_ctrl_9,   		reg_ac_master_y_gain,   GET_BITS(epp->data[11], 0, 8));
					#endif
				}
			}
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get dnr common ctrl
 * - use input struct LX_PE_NRD_DNR6_CMN_T
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_GetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT8 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_CMN_T *ctrl_param =(LX_PE_NRD_DNR_CMN_T *)pstParams;
			LX_PE_NRD_DNR3_CMN_T *pp = ctrl_param->data;
			LX_PE_NRD_EASY_DNR_CMN_T *epp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DNR0_O26_QRd01(dnr_max_ctrl,		reg_dnr_max_enable, pp->dnr______ui[0]);
					PE_DNR0_O26_QRd02(mnr_ctrl_0,		reg_mnr_chroma_en,	pp->dnr______ui[1],\
														reg_mnr_enable, pp->dnr______ui[2]);
					PE_DNR0_O26_QRd02(dc_bnr_ctrl_0,	reg_dc_bnr_enable,	pp->dnr______ui[3],\
														reg_obj_gain_mul,	pp->dnr______ui[4]);
					PE_DNR0_O26_QRd04(ac_bnr_ctrl_0,	reg_bnr_ac_v_chroma_en, pp->dnr______ui[5],\
														reg_bnr_ac_h_chroma_en, pp->dnr______ui[6],\
														reg_bnr_ac_v_en,	pp->dnr______ui[7],\
														reg_bnr_ac_h_en,	pp->dnr______ui[8]);
					#if 0
					PE_DNR0_O26_QRd04(reg_dc_bnr_ctrl_12,	reg_psp_blur_x_min, pp->dnr______ui[9],\
															reg_psp_blur_x_max, pp->dnr______ui[10],\
															reg_psp_blur_y_min, pp->dnr______ui[11],\
															reg_psp_blur_y_max, pp->dnr______ui[12]);
					#endif
					pd = pp->dnr______ui;
					printk("get[%d] : dnr______ui\n"
					"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12]);
				}
				else
				{
					PE_DNR0_O26_QRd01(dnr_max_ctrl,    		reg_dnr_max_enable,     epp->data[0]);
					PE_DNR0_O26_QRd03(mnr_ctrl_0,      		reg_mnr_master_gain,    epp->data[1],\
					                                        reg_mnr_chroma_en,      epp->data[2],\
					                                        reg_mnr_enable,         epp->data[3]);
					PE_DNR0_O26_QRd01(dc_bnr_ctrl_0,   		reg_dc_bnr_enable,      epp->data[4]);
					PE_DNR0_O26_QRd02(dc_bnr_ctrl_2,   		reg_dc_bnr_chromagain,  epp->data[5],\
					                                        reg_dc_bnr_mastergain,  epp->data[6]);
					PE_DNR0_O26_QRd04(ac_bnr_ctrl_0,   		reg_bnr_ac_v_chroma_en, epp->data[7],\
					                                        reg_bnr_ac_h_chroma_en, epp->data[8],\
					                                        reg_bnr_ac_v_en,        epp->data[9],\
					                                        reg_bnr_ac_h_en,        epp->data[10]);
					PE_DNR0_O26_QRd01(ac_bnr_ctrl_9,   		reg_ac_master_y_gain,   epp->data[11]);
					pd = epp->data;
					printk("get[%d] : dnr______ui\n"
					"dnr______ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr______ui    [10]0x%02X,0x%02X\n",\
					epp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11]);
				}
			}
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set dnr common ctrl
 * - use input struct LX_PE_NRD_DNR4_CMN_T same as PE_NRD_HW_O26_SetDnrCmnCtrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT8 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_CMN_T *ctrl_param =(LX_PE_NRD_DNR_CMN_T *)pstParams;
			LX_PE_NRD_DNR4_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			LX_PE_NRD_EASY_DNR_CMN_T *epp = (typeof(*epp) *)ctrl_param->data;
			static LX_PE_NRD_DNR4_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DNR4_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DNR("duplicated DB : LX_PE_NRD_DNR3_CMN_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DNR("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd32 =  pp->dnr______ui;
					PE_DBG_DNR("set[%d] : dnr______ui\n"
					"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr______ui	[10]0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
					pd32[10], pd32[11], pd32[12]);
					pd32 = pp->dnr____buff;
					PQ_PRINT_DNR("PE_NRD_HW_O26_SetDnr2ndCmnCtrl set[%d] : dnr____buff\n"\
					"dnr____buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
					#if 1
					#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
					PE_NRD_HW_O26_DNR1_WR01(dnr_max_ctrl,	reg_dnr_max_enable, GET_BITS(pp->dnr______ui[0],0,1));
					#if 1
					PE_NRD_HW_O26_DNR1_WR02(mnr_ctrl_0,		reg_mnr_chroma_en,	GET_BITS(pp->dnr______ui[1],0,1),\
																reg_mnr_enable, GET_BITS(pp->dnr______ui[2],0,1));
					#else
					PE_NRD_HW_O26_NR1_VERI_WR02(mnr_ctrl_0, reg_mnr_chroma_en,	GET_BITS(pp->dnr______ui[1],0,1),\
															reg_mnr_enable, GET_BITS(pp->dnr______ui[2],0,1));
					#endif
					PE_NRD_HW_O26_DNR1_WR02(dc_bnr_ctrl_0,	reg_dc_bnr_enable,	GET_BITS(pp->dnr______ui[3],0,1),\
															reg_obj_gain_mul,	GET_BITS(pp->dnr______ui[4],0,2));
					PE_NRD_HW_O26_DNR1_WR04(ac_bnr_ctrl_0,	reg_bnr_ac_v_chroma_en, GET_BITS(pp->dnr______ui[5],0,1),\
															reg_bnr_ac_h_chroma_en, GET_BITS(pp->dnr______ui[6],0,1),\
															reg_bnr_ac_v_en,	GET_BITS(pp->dnr______ui[7],0,1),\
															reg_bnr_ac_h_en,	GET_BITS(pp->dnr______ui[8],0,1));

					#endif
					/* download dnr2nd user db */
					ret = PE_NRD_HW_O26_DownloadDnr2ndUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadDnr2ndUserDb() error.\n",__F__,__L__);
					#endif
				}
				else
				{
					PE_DBG_DNR("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					epp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = epp->data;
					PE_DBG_DNR("set[%d] : data\n"
					"data    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"data    [10]0x%02X,0x%02X,\n",\
					epp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11]);
					#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
					PE_NRD_HW_O26_DNR1_WR01(dnr_max_ctrl,    reg_dnr_max_enable,     GET_BITS(epp->data[0], 0, 1));
					PE_DNR0_O26_QWr03(mnr_ctrl_0,      reg_mnr_master_gain,    GET_BITS(epp->data[1], 0, 8),\
					                                        reg_mnr_chroma_en,      GET_BITS(epp->data[2], 0, 1),\
					                                        reg_mnr_enable,         GET_BITS(epp->data[3], 0, 1));
					PE_NRD_HW_O26_DNR1_WR01(dc_bnr_ctrl_0,   reg_dc_bnr_enable,      GET_BITS(epp->data[4], 0, 1));
					PE_NRD_HW_O26_DNR1_WR02(dc_bnr_ctrl_2,   reg_dc_bnr_chromagain,  GET_BITS(epp->data[5], 0, 8),\
					                                        reg_dc_bnr_mastergain,  GET_BITS(epp->data[6], 0, 6));
					PE_NRD_HW_O26_DNR1_WR04(ac_bnr_ctrl_0,   reg_bnr_ac_v_chroma_en, GET_BITS(epp->data[7], 0, 1),\
					                                        reg_bnr_ac_h_chroma_en, GET_BITS(epp->data[8], 0, 1),\
					                                        reg_bnr_ac_v_en,        GET_BITS(epp->data[9], 0, 1),\
					                                        reg_bnr_ac_h_en,        GET_BITS(epp->data[10], 0, 1));
					PE_NRD_HW_O26_DNR1_WR01(ac_bnr_ctrl_9,   reg_ac_master_y_gain,   GET_BITS(epp->data[11], 0, 8));
					#else
					PE_DNR0_O26_QWr01(dnr_max_ctrl,    		reg_dnr_max_enable,     GET_BITS(epp->data[0], 0, 1));
					PE_DNR0_O26_QWr03(mnr_ctrl_0,      		reg_mnr_master_gain,    GET_BITS(epp->data[1], 0, 8),\
					                                        reg_mnr_chroma_en,      GET_BITS(epp->data[2], 0, 1),\
					                                        reg_mnr_enable,         GET_BITS(epp->data[3], 0, 1));
					PE_DNR0_O26_QWr01(dc_bnr_ctrl_0,   		reg_dc_bnr_enable,      GET_BITS(epp->data[4], 0, 1));
					PE_DNR0_O26_QWr02(dc_bnr_ctrl_2,   		reg_dc_bnr_chromagain,  GET_BITS(epp->data[5], 0, 8),\
					                                        reg_dc_bnr_mastergain,  GET_BITS(epp->data[6], 0, 6));
					PE_DNR0_O26_QWr04(ac_bnr_ctrl_0,   		reg_bnr_ac_v_chroma_en, GET_BITS(epp->data[7], 0, 1),\
					                                        reg_bnr_ac_h_chroma_en, GET_BITS(epp->data[8], 0, 1),\
					                                        reg_bnr_ac_v_en,        GET_BITS(epp->data[9], 0, 1),\
					                                        reg_bnr_ac_h_en,        GET_BITS(epp->data[10], 0, 1));
					PE_DNR0_O26_QWr01(ac_bnr_ctrl_9,   		reg_ac_master_y_gain,   GET_BITS(epp->data[11], 0, 8));
					#endif
				}
			}
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_SetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT8 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_DETAIL_T *ctrl_param =(LX_PE_NRD_DNR_DETAIL_T *)pstParams;
			LX_PE_NRD_DNR4_DETAIL_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_NRD_DNR4_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DNR4_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DNR("duplicated DB : LX_PE_NRD_DNR3_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DNR("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd32 = pp->dnr_____mnr;
					PE_DBG_DNR("set[%d] : dnr_____mnr\n"
					"dnr0____mnr	[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
					"dnr0____mnr	[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
					pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);

					pd = pp->dnr___dcbnr;
					PE_DBG_DNR("set[%d] : dnr___dcbnr\n"
					"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32]);

					pd = pp->dnr___acbnr;
					PE_DBG_DNR("set[%d] : dnr___acbnr\n"
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
					PE_NRD_HW_O26_DNR_WR04(mnr_ctrl_1,	reg_mmd_x_min,	GET_BITS(pp->dnr_____mnr[0],0,8),\
																reg_mmd_x_max,	GET_BITS(pp->dnr_____mnr[1],0,8),\
																reg_mmd_y_min,	GET_BITS(pp->dnr_____mnr[2],0,8),\
																reg_mmd_y_max,	GET_BITS(pp->dnr_____mnr[3],0,8));
					#if 0
					PE_NRD_HW_O26_DNR_WR02(mnr_ctrl_3,	reg_mmd_scale,	GET_BITS(pp->dnr_____mnr[4],0,8),\
																reg_blur_sel,	GET_BITS(pp->dnr_____mnr[5],0,1));
					#else
					PE_NRD_HW_O26_NR0_VERI_WR02(mnr_ctrl_3,	reg_mmd_scale,	GET_BITS(pp->dnr_____mnr[4],0,8),\
															reg_blur_sel,	GET_BITS(pp->dnr_____mnr[5],0,1));
					#endif
					PE_NRD_HW_O26_DNR_WR01(reg_smr_ctrl_01,	reg_flat_th,	GET_BITS(pp->dnr_____mnr[6],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_smr_ctrl_12,	reg_mmd_blur_x3,	GET_BITS(pp->dnr_____mnr[7], 0,8),\
															reg_mmd_blur_x2,	GET_BITS(pp->dnr_____mnr[7], 8,8),\
															reg_mmd_blur_x1,	GET_BITS(pp->dnr_____mnr[7],16,8),\
															reg_mmd_blur_x0,	GET_BITS(pp->dnr_____mnr[7],24,8));
					PE_NRD_HW_O26_DNR_WR04(reg_smr_ctrl_13,	reg_mmd_blur_y1,	GET_BITS(pp->dnr_____mnr[8], 0,8),\
															reg_mmd_blur_y0,	GET_BITS(pp->dnr_____mnr[8], 8,8),\
															reg_mmd_blur_x5,	GET_BITS(pp->dnr_____mnr[8],16,8),\
															reg_mmd_blur_x4,	GET_BITS(pp->dnr_____mnr[8],24,8));
					PE_NRD_HW_O26_DNR_WR04(reg_smr_ctrl_14,	reg_mmd_blur_y5,	GET_BITS(pp->dnr_____mnr[9], 0,8),\
															reg_mmd_blur_y4,	GET_BITS(pp->dnr_____mnr[9], 8,8),\
															reg_mmd_blur_y3,	GET_BITS(pp->dnr_____mnr[9],16,8),\
															reg_mmd_blur_y2,	GET_BITS(pp->dnr_____mnr[9],24,8));
					PE_NRD_HW_O26_DNR_WR04(reg_smr_ctrl_15,	reg_blur_gain_by_flat_x3,	GET_BITS(pp->dnr_____mnr[10], 0,8),\
															reg_blur_gain_by_flat_x2,	GET_BITS(pp->dnr_____mnr[10], 8,8),\
															reg_blur_gain_by_flat_x1,	GET_BITS(pp->dnr_____mnr[10],16,8),\
															reg_blur_gain_by_flat_x0,	GET_BITS(pp->dnr_____mnr[10],24,8));
					PE_NRD_HW_O26_DNR_WR04(reg_smr_ctrl_16,	reg_blur_gain_by_flat_y3,	GET_BITS(pp->dnr_____mnr[11], 0,8),\
															reg_blur_gain_by_flat_y2,	GET_BITS(pp->dnr_____mnr[11], 8,8),\
															reg_blur_gain_by_flat_y1,	GET_BITS(pp->dnr_____mnr[11],16,8),\
															reg_blur_gain_by_flat_y0,	GET_BITS(pp->dnr_____mnr[11],24,8));
					PE_NRD_HW_O26_DNR_WR04(reg_smr_ctrl_17,	reg_blur_gain_by_diff_x3,	GET_BITS(pp->dnr_____mnr[12], 0,8),\
															reg_blur_gain_by_diff_x2,	GET_BITS(pp->dnr_____mnr[12], 8,8),\
															reg_blur_gain_by_diff_x1,	GET_BITS(pp->dnr_____mnr[12],16,8),\
															reg_blur_gain_by_diff_x0,	GET_BITS(pp->dnr_____mnr[12],24,8));
					PE_NRD_HW_O26_DNR_WR04(reg_smr_ctrl_18,	reg_blur_gain_by_diff_y1,	GET_BITS(pp->dnr_____mnr[13], 0,8),\
															reg_blur_gain_by_diff_y0,	GET_BITS(pp->dnr_____mnr[13], 8,8),\
															reg_blur_gain_by_diff_x5,	GET_BITS(pp->dnr_____mnr[13],16,8),\
															reg_blur_gain_by_diff_x4,	GET_BITS(pp->dnr_____mnr[13],24,8));
					PE_NRD_HW_O26_DNR_WR04(reg_smr_ctrl_19,	reg_blur_gain_by_diff_y5,	GET_BITS(pp->dnr_____mnr[14], 0,8),\
															reg_blur_gain_by_diff_y4,	GET_BITS(pp->dnr_____mnr[14], 8,8),\
															reg_blur_gain_by_diff_y3,	GET_BITS(pp->dnr_____mnr[14],16,8),\
															reg_blur_gain_by_diff_y2,	GET_BITS(pp->dnr_____mnr[14],24,8));
					/*dnr___dcbnr*/
					PE_NRD_HW_O26_DNR_WR02(detail_ctrl, reg_bnr_diff_p, GET_BITS(pp->dnr___dcbnr[0],0,8),\
																reg_bnr_diff_l, GET_BITS(pp->dnr___dcbnr[1],0,8));
					PE_NRD_HW_O26_DNR_WR03(dc_bnr_ctrl_0,	reg_dc_motion_min,	GET_BITS(pp->dnr___dcbnr[2],0,8),\
																reg_dc_motion_max,	GET_BITS(pp->dnr___dcbnr[3],0,8),\
																reg_dc_blur_sel,	GET_BITS(pp->dnr___dcbnr[4],0,2));
					PE_NRD_HW_O26_DNR_WR04(dc_bnr_ctrl_1,	reg_var_cut_resolution, GET_BITS(pp->dnr___dcbnr[5],0,4),\
																reg_var_h_gain, GET_BITS(pp->dnr___dcbnr[6],0,4),\
																reg_var_v_gain, GET_BITS(pp->dnr___dcbnr[7],0,4),\
																reg_luma_gain_en,	GET_BITS(pp->dnr___dcbnr[8],0,1));
					PE_NRD_HW_O26_DNR_WR04(dc_bnr_ctrl_2,	reg_dc_protection_th,	GET_BITS(pp->dnr___dcbnr[9],0,8),\
																reg_dc_protection_en,	GET_BITS(pp->dnr___dcbnr[10],0,1),\
																reg_dc_motion_en,	GET_BITS(pp->dnr___dcbnr[11],0,1),\
																reg_dc_var_en,	GET_BITS(pp->dnr___dcbnr[12],0,1));
					PE_NRD_HW_O26_DNR_WR04(dc_bnr_ctrl_3,	reg_dc_bnr_var_th0, GET_BITS(pp->dnr___dcbnr[13],0,8),\
																reg_dc_bnr_var_th1, GET_BITS(pp->dnr___dcbnr[14],0,8),\
																reg_dc_bnr_var_th2, GET_BITS(pp->dnr___dcbnr[15],0,8),\
																reg_dc_bnr_var_th3, GET_BITS(pp->dnr___dcbnr[16],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_dc_bnr_ctrl_8,	reg_gain_x0,	GET_BITS(pp->dnr___dcbnr[17],0,8),\
																reg_gain_x1,	GET_BITS(pp->dnr___dcbnr[18],0,8),\
																reg_gain_x2,	GET_BITS(pp->dnr___dcbnr[19],0,8),\
																reg_gain_x3,	GET_BITS(pp->dnr___dcbnr[20],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_dc_bnr_ctrl_9,	reg_gain_x4,	GET_BITS(pp->dnr___dcbnr[21],0,8),\
																reg_gain_x5,	GET_BITS(pp->dnr___dcbnr[22],0,8),\
																reg_gain_x6,	GET_BITS(pp->dnr___dcbnr[23],0,8),\
																reg_gain_x7,	GET_BITS(pp->dnr___dcbnr[24],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_dc_bnr_ctrl_10,	reg_gain_y0,	GET_BITS(pp->dnr___dcbnr[25],0,8),\
																reg_gain_y1,	GET_BITS(pp->dnr___dcbnr[26],0,8),\
																reg_gain_y2,	GET_BITS(pp->dnr___dcbnr[27],0,8),\
																reg_gain_y3,	GET_BITS(pp->dnr___dcbnr[28],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_dc_bnr_ctrl_11,	reg_gain_y4,	GET_BITS(pp->dnr___dcbnr[29],0,8),\
																reg_gain_y5,	GET_BITS(pp->dnr___dcbnr[30],0,8),\
																reg_gain_y6,	GET_BITS(pp->dnr___dcbnr[31],0,8),\
																reg_gain_y7,	GET_BITS(pp->dnr___dcbnr[32],0,8));
					/*dnr___acbnr*/
					PE_NRD_HW_O26_DNR_WR02(detail_ctrl, reg_bnr_ac_detail_min,	GET_BITS(pp->dnr___acbnr[0],0,8),\
																reg_bnr_ac_detail_max,	GET_BITS(pp->dnr___acbnr[1],0,8));
					PE_NRD_HW_O26_DNR_WR03(ac_bnr_ctrl_0,	reg_bnr_ac_diff_min_h_th,	GET_BITS(pp->dnr___acbnr[2],0,8),\
																reg_bnr_ac_diff_min_v_th,	GET_BITS(pp->dnr___acbnr[3],0,8),\
																reg_bnr_ac_acness_resol_h,	GET_BITS(pp->dnr___acbnr[4],0,2));
					PE_NRD_HW_O26_DNR_WR03(ac_bnr_ctrl_1,	reg_bnr_ac_h_acness_min,	GET_BITS(pp->dnr___acbnr[5],0,8),\
																reg_bnr_ac_h_acness_max,	GET_BITS(pp->dnr___acbnr[6],0,8),\
																reg_bnr_ac_global_motion_th,	GET_BITS(pp->dnr___acbnr[7],0,8));
					PE_NRD_HW_O26_DNR_WR04(ac_bnr_ctrl_2,	reg_bnr_ac_motion_0,	GET_BITS(pp->dnr___acbnr[8],0,8),\
																reg_bnr_ac_motion_1,	GET_BITS(pp->dnr___acbnr[9],0,8),\
																reg_bnr_ac_motion_2,	GET_BITS(pp->dnr___acbnr[10],0,8),\
																reg_bnr_ac_motion_3,	GET_BITS(pp->dnr___acbnr[11],0,8));
					PE_NRD_HW_O26_DNR_WR04(ac_bnr_ctrl_3,	reg_bnr_ac_motion_y_0,	GET_BITS(pp->dnr___acbnr[12],0,8),\
																reg_bnr_ac_motion_y_1,	GET_BITS(pp->dnr___acbnr[13],0,8),\
																reg_bnr_ac_motion_y_2,	GET_BITS(pp->dnr___acbnr[14],0,8),\
																reg_bnr_ac_motion_y_3,	GET_BITS(pp->dnr___acbnr[15],0,8));
					PE_NRD_HW_O26_DNR_WR03(ac_bnr_ctrl_4,	reg_bnr_ac_v_acness_min,	GET_BITS(pp->dnr___acbnr[16],0,8),\
																reg_bnr_ac_v_acness_max,	GET_BITS(pp->dnr___acbnr[17],0,8),\
																reg_bnr_ac_acness_resol_v,	GET_BITS(pp->dnr___acbnr[18],0,2));
					PE_NRD_HW_O26_DNR_WR04(ac_bnr_ctrl_5,	reg_bnr_ac_detail_th1,	GET_BITS(pp->dnr___acbnr[19],0,8),\
																reg_bnr_ac_detail_th2,	GET_BITS(pp->dnr___acbnr[20],0,8),\
																reg_bnr_ac_detail_th3,	GET_BITS(pp->dnr___acbnr[21],0,8),\
																reg_bnr_ac_detail_th4,	GET_BITS(pp->dnr___acbnr[22],0,8));
					PE_NRD_HW_O26_DNR_WR04(ac_bnr_ctrl_6,	reg_bnr_ac_detail_gain_th,	GET_BITS(pp->dnr___acbnr[23],0,8),\
																reg_bnr_ac_pos_gain_h0, GET_BITS(pp->dnr___acbnr[24],0,8),\
																reg_bnr_ac_pos_gain_h1, GET_BITS(pp->dnr___acbnr[25],0,8),\
																reg_bnr_ac_pos_gain_h2, GET_BITS(pp->dnr___acbnr[26],0,8));
					PE_NRD_HW_O26_DNR_WR04(ac_bnr_ctrl_7,	reg_bnr_ac_pos_gain_h3, GET_BITS(pp->dnr___acbnr[27],0,8),\
																reg_bnr_ac_pos_gain_l0, GET_BITS(pp->dnr___acbnr[28],0,8),\
																reg_bnr_ac_pos_gain_l1, GET_BITS(pp->dnr___acbnr[29],0,8),\
																reg_bnr_ac_pos_gain_l2, GET_BITS(pp->dnr___acbnr[30],0,8));
				}
			}
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set dnr2nd detail ctrl
 * - use input struct LX_PE_NRD_DNR4_DETAIL_T same as PE_NRD_HW_O26_SetDnrDetailCtrl
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnr2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT8 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_DETAIL_T *ctrl_param =(LX_PE_NRD_DNR_DETAIL_T *)pstParams;
			LX_PE_NRD_DNR3_DETAIL_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_NRD_DNR3_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DNR3_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DNR("duplicated DB : LX_PE_NRD_DNR3_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DNR("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = pp->dnr_____mnr; // unsigned char dnr1_mnr[6]; ///< dc bnr 
					PE_DBG_DNR("set[%d] : dnr_____mnr\n"
					"dnr_____mnr	[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

					pd = pp->dnr___dcbnr;
					PE_DBG_DNR("set[%d] : dnr___dcbnr\n"
					"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32]);

					pd = pp->dnr___acbnr;
					PE_DBG_DNR("set[%d] : dnr___acbnr\n"
					"dnr___acbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___acbnr	[30]0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30]);
					/*dnr_____mnr[6]*/
					PE_NRD_HW_O26_DNR1_WR04(mnr_ctrl_1,	reg_mmd_x_min,	GET_BITS(pp->dnr_____mnr[0],0,8),\
																reg_mmd_x_max,	GET_BITS(pp->dnr_____mnr[1],0,8),\
																reg_mmd_y_min,	GET_BITS(pp->dnr_____mnr[2],0,8),\
																reg_mmd_y_max,	GET_BITS(pp->dnr_____mnr[3],0,8));
					#if 1
					PE_NRD_HW_O26_DNR1_WR02(mnr_ctrl_3,	reg_mmd_scale,	GET_BITS(pp->dnr_____mnr[4],0,8),\
																reg_blur_sel,	GET_BITS(pp->dnr_____mnr[5],0,1));
					#else
					PE_NRD_HW_O26_NR1_VERI_WR02(mnr_ctrl_3,	reg_mmd_scale,	GET_BITS(pp->dnr_____mnr[4],0,8),\
															reg_blur_sel,	GET_BITS(pp->dnr_____mnr[5],0,1));
					#endif
					/*dnr___dcbn[33]r*/
					PE_NRD_HW_O26_DNR1_WR02(detail_ctrl, reg_bnr_diff_p, GET_BITS(pp->dnr___dcbnr[0],0,8),\
																reg_bnr_diff_l, GET_BITS(pp->dnr___dcbnr[1],0,8));
					PE_NRD_HW_O26_DNR1_WR03(dc_bnr_ctrl_0,	reg_dc_motion_min,	GET_BITS(pp->dnr___dcbnr[2],0,8),\
																reg_dc_motion_max,	GET_BITS(pp->dnr___dcbnr[3],0,8),\
																reg_dc_blur_sel,	GET_BITS(pp->dnr___dcbnr[4],0,2));
					PE_NRD_HW_O26_DNR1_WR04(dc_bnr_ctrl_1,	reg_var_cut_resolution, GET_BITS(pp->dnr___dcbnr[5],0,4),\
																reg_var_h_gain, GET_BITS(pp->dnr___dcbnr[6],0,4),\
																reg_var_v_gain, GET_BITS(pp->dnr___dcbnr[7],0,4),\
																reg_luma_gain_en,	GET_BITS(pp->dnr___dcbnr[8],0,1));
					PE_NRD_HW_O26_DNR1_WR04(dc_bnr_ctrl_2,	reg_dc_protection_th,	GET_BITS(pp->dnr___dcbnr[9],0,8),\
																reg_dc_protection_en,	GET_BITS(pp->dnr___dcbnr[10],0,1),\
																reg_dc_motion_en,	GET_BITS(pp->dnr___dcbnr[11],0,1),\
																reg_dc_var_en,	GET_BITS(pp->dnr___dcbnr[12],0,1));
					PE_NRD_HW_O26_DNR1_WR04(dc_bnr_ctrl_3,	reg_dc_bnr_var_th0, GET_BITS(pp->dnr___dcbnr[13],0,8),\
																reg_dc_bnr_var_th1, GET_BITS(pp->dnr___dcbnr[14],0,8),\
																reg_dc_bnr_var_th2, GET_BITS(pp->dnr___dcbnr[15],0,8),\
																reg_dc_bnr_var_th3, GET_BITS(pp->dnr___dcbnr[16],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_dc_bnr_ctrl_8,	reg_gain_x0,	GET_BITS(pp->dnr___dcbnr[17],0,8),\
																reg_gain_x1,	GET_BITS(pp->dnr___dcbnr[18],0,8),\
																reg_gain_x2,	GET_BITS(pp->dnr___dcbnr[19],0,8),\
																reg_gain_x3,	GET_BITS(pp->dnr___dcbnr[20],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_dc_bnr_ctrl_9,	reg_gain_x4,	GET_BITS(pp->dnr___dcbnr[21],0,8),\
																reg_gain_x5,	GET_BITS(pp->dnr___dcbnr[22],0,8),\
																reg_gain_x6,	GET_BITS(pp->dnr___dcbnr[23],0,8),\
																reg_gain_x7,	GET_BITS(pp->dnr___dcbnr[24],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_dc_bnr_ctrl_10,	reg_gain_y0,	GET_BITS(pp->dnr___dcbnr[25],0,8),\
																reg_gain_y1,	GET_BITS(pp->dnr___dcbnr[26],0,8),\
																reg_gain_y2,	GET_BITS(pp->dnr___dcbnr[27],0,8),\
																reg_gain_y3,	GET_BITS(pp->dnr___dcbnr[28],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_dc_bnr_ctrl_11,	reg_gain_y4,	GET_BITS(pp->dnr___dcbnr[29],0,8),\
																reg_gain_y5,	GET_BITS(pp->dnr___dcbnr[30],0,8),\
																reg_gain_y6,	GET_BITS(pp->dnr___dcbnr[31],0,8),\
																reg_gain_y7,	GET_BITS(pp->dnr___dcbnr[32],0,8));
					/*dnr___acbnr[31]*/
					PE_NRD_HW_O26_DNR1_WR02(detail_ctrl, reg_bnr_ac_detail_min,	GET_BITS(pp->dnr___acbnr[0],0,8),\
																reg_bnr_ac_detail_max,	GET_BITS(pp->dnr___acbnr[1],0,8));
					PE_NRD_HW_O26_DNR1_WR03(ac_bnr_ctrl_0,	reg_bnr_ac_diff_min_h_th,	GET_BITS(pp->dnr___acbnr[2],0,8),\
																reg_bnr_ac_diff_min_v_th,	GET_BITS(pp->dnr___acbnr[3],0,8),\
																reg_bnr_ac_acness_resol_h,	GET_BITS(pp->dnr___acbnr[4],0,2));
					PE_NRD_HW_O26_DNR1_WR03(ac_bnr_ctrl_1,	reg_bnr_ac_h_acness_min,	GET_BITS(pp->dnr___acbnr[5],0,8),\
																reg_bnr_ac_h_acness_max,	GET_BITS(pp->dnr___acbnr[6],0,8),\
																reg_bnr_ac_global_motion_th,	GET_BITS(pp->dnr___acbnr[7],0,8));
					PE_NRD_HW_O26_DNR1_WR04(ac_bnr_ctrl_2,	reg_bnr_ac_motion_0,	GET_BITS(pp->dnr___acbnr[8],0,8),\
																reg_bnr_ac_motion_1,	GET_BITS(pp->dnr___acbnr[9],0,8),\
																reg_bnr_ac_motion_2,	GET_BITS(pp->dnr___acbnr[10],0,8),\
																reg_bnr_ac_motion_3,	GET_BITS(pp->dnr___acbnr[11],0,8));
					PE_NRD_HW_O26_DNR1_WR04(ac_bnr_ctrl_3,	reg_bnr_ac_motion_y_0,	GET_BITS(pp->dnr___acbnr[12],0,8),\
																reg_bnr_ac_motion_y_1,	GET_BITS(pp->dnr___acbnr[13],0,8),\
																reg_bnr_ac_motion_y_2,	GET_BITS(pp->dnr___acbnr[14],0,8),\
																reg_bnr_ac_motion_y_3,	GET_BITS(pp->dnr___acbnr[15],0,8));
					PE_NRD_HW_O26_DNR1_WR03(ac_bnr_ctrl_4,	reg_bnr_ac_v_acness_min,	GET_BITS(pp->dnr___acbnr[16],0,8),\
																reg_bnr_ac_v_acness_max,	GET_BITS(pp->dnr___acbnr[17],0,8),\
																reg_bnr_ac_acness_resol_v,	GET_BITS(pp->dnr___acbnr[18],0,2));
					PE_NRD_HW_O26_DNR1_WR04(ac_bnr_ctrl_5,	reg_bnr_ac_detail_th1,	GET_BITS(pp->dnr___acbnr[19],0,8),\
																reg_bnr_ac_detail_th2,	GET_BITS(pp->dnr___acbnr[20],0,8),\
																reg_bnr_ac_detail_th3,	GET_BITS(pp->dnr___acbnr[21],0,8),\
																reg_bnr_ac_detail_th4,	GET_BITS(pp->dnr___acbnr[22],0,8));
					PE_NRD_HW_O26_DNR1_WR04(ac_bnr_ctrl_6,	reg_bnr_ac_detail_gain_th,	GET_BITS(pp->dnr___acbnr[23],0,8),\
																reg_bnr_ac_pos_gain_h0, GET_BITS(pp->dnr___acbnr[24],0,8),\
																reg_bnr_ac_pos_gain_h1, GET_BITS(pp->dnr___acbnr[25],0,8),\
																reg_bnr_ac_pos_gain_h2, GET_BITS(pp->dnr___acbnr[26],0,8));
					PE_NRD_HW_O26_DNR1_WR04(ac_bnr_ctrl_7,	reg_bnr_ac_pos_gain_h3, GET_BITS(pp->dnr___acbnr[27],0,8),\
																reg_bnr_ac_pos_gain_l0, GET_BITS(pp->dnr___acbnr[28],0,8),\
																reg_bnr_ac_pos_gain_l1, GET_BITS(pp->dnr___acbnr[29],0,8),\
																reg_bnr_ac_pos_gain_l2, GET_BITS(pp->dnr___acbnr[30],0,8));
				}
			}
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT8 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_DETAIL_T *ctrl_param =(LX_PE_NRD_DNR_DETAIL_T *)pstParams;
			LX_PE_NRD_DNR3_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					/*dnr_____mnr*/
					PE_DNR0_O26_QRd04(mnr_ctrl_1,			reg_mmd_x_min,		pp->dnr_____mnr[0],\
															reg_mmd_x_max,		pp->dnr_____mnr[1],\
															reg_mmd_y_min,		pp->dnr_____mnr[2],\
															reg_mmd_y_max,		pp->dnr_____mnr[3]);
					PE_DNR0_O26_QRd02(mnr_ctrl_3,			reg_mmd_scale,		pp->dnr_____mnr[4],\
															reg_blur_sel,		pp->dnr_____mnr[5]);
					/*dnr___dcbnr*/
					PE_DNR0_O26_QRd02(detail_ctrl, 			reg_bnr_diff_p, 	pp->dnr___dcbnr[0],\
															reg_bnr_diff_l, 	pp->dnr___dcbnr[1]);
					PE_DNR0_O26_QRd03(dc_bnr_ctrl_0,		reg_dc_motion_min,	pp->dnr___dcbnr[2],\
															reg_dc_motion_max,	pp->dnr___dcbnr[3],\
															reg_dc_blur_sel,	pp->dnr___dcbnr[4]);
					PE_DNR0_O26_QRd04(dc_bnr_ctrl_1,		reg_var_cut_resolution, pp->dnr___dcbnr[5],\
															reg_var_h_gain, 		pp->dnr___dcbnr[6],\
															reg_var_v_gain, 		pp->dnr___dcbnr[7],\
															reg_luma_gain_en,		pp->dnr___dcbnr[8]);
					PE_DNR0_O26_QRd04(dc_bnr_ctrl_2,		reg_dc_protection_th,	pp->dnr___dcbnr[9],\
															reg_dc_protection_en,	pp->dnr___dcbnr[10],\
															reg_dc_motion_en,		pp->dnr___dcbnr[11],\
															reg_dc_var_en,			pp->dnr___dcbnr[12]);
					PE_DNR0_O26_QRd04(dc_bnr_ctrl_3,		reg_dc_bnr_var_th0, 	pp->dnr___dcbnr[13],\
															reg_dc_bnr_var_th1, 	pp->dnr___dcbnr[14],\
															reg_dc_bnr_var_th2, 	pp->dnr___dcbnr[15],\
															reg_dc_bnr_var_th3, 	pp->dnr___dcbnr[16]);
					//PE_DNR0_O26_QRd01(sc_bnr_ctrl_0,		reg_sc_bnr_en,	pp->dnr___dcbnr[17]);
					PE_DNR0_O26_QRd04(reg_dc_bnr_ctrl_8,	reg_gain_x0,	pp->dnr___dcbnr[18],\
															reg_gain_x1,	pp->dnr___dcbnr[19],\
															reg_gain_x2,	pp->dnr___dcbnr[20],\
															reg_gain_x3,	pp->dnr___dcbnr[21]);
					PE_DNR0_O26_QRd04(reg_dc_bnr_ctrl_9,	reg_gain_x4,	pp->dnr___dcbnr[22],\
															reg_gain_x5,	pp->dnr___dcbnr[23],\
															reg_gain_x6,	pp->dnr___dcbnr[24],\
															reg_gain_x7,	pp->dnr___dcbnr[25]);
					PE_DNR0_O26_QRd04(reg_dc_bnr_ctrl_10,	reg_gain_y0,	pp->dnr___dcbnr[26],\
															reg_gain_y1,	pp->dnr___dcbnr[27],\
															reg_gain_y2,	pp->dnr___dcbnr[28],\
															reg_gain_y3,	pp->dnr___dcbnr[29]);
					PE_DNR0_O26_QRd04(reg_dc_bnr_ctrl_11,	reg_gain_y4,	pp->dnr___dcbnr[30],\
															reg_gain_y5,	pp->dnr___dcbnr[31],\
															reg_gain_y6,	pp->dnr___dcbnr[32],\
															reg_gain_y7,	pp->dnr___dcbnr[33]);
					/*dnr___acbnr*/
					PE_DNR0_O26_QRd02(detail_ctrl, 			reg_bnr_ac_detail_min,		pp->dnr___acbnr[0],\
															reg_bnr_ac_detail_max,		pp->dnr___acbnr[1]);
					PE_DNR0_O26_QRd03(ac_bnr_ctrl_0,		reg_bnr_ac_diff_min_h_th,	pp->dnr___acbnr[2],\
															reg_bnr_ac_diff_min_v_th,	pp->dnr___acbnr[3],\
															reg_bnr_ac_acness_resol_h,	pp->dnr___acbnr[4]);
					PE_DNR0_O26_QRd03(ac_bnr_ctrl_1,		reg_bnr_ac_h_acness_min,	pp->dnr___acbnr[5],\
															reg_bnr_ac_h_acness_max,	pp->dnr___acbnr[6],\
															reg_bnr_ac_global_motion_th,	pp->dnr___acbnr[7]);
					PE_DNR0_O26_QRd04(ac_bnr_ctrl_2,		reg_bnr_ac_motion_0,	pp->dnr___acbnr[8],\
															reg_bnr_ac_motion_1,	pp->dnr___acbnr[9],\
															reg_bnr_ac_motion_2,	pp->dnr___acbnr[10],\
															reg_bnr_ac_motion_3,	pp->dnr___acbnr[11]);
					PE_DNR0_O26_QRd04(ac_bnr_ctrl_3,		reg_bnr_ac_motion_y_0,	pp->dnr___acbnr[12],\
															reg_bnr_ac_motion_y_1,	pp->dnr___acbnr[13],\
															reg_bnr_ac_motion_y_2,	pp->dnr___acbnr[14],\
															reg_bnr_ac_motion_y_3,	pp->dnr___acbnr[15]);
					PE_DNR0_O26_QRd03(ac_bnr_ctrl_4,		reg_bnr_ac_v_acness_min,	pp->dnr___acbnr[16],\
															reg_bnr_ac_v_acness_max,	pp->dnr___acbnr[17],\
															reg_bnr_ac_acness_resol_v,	pp->dnr___acbnr[18]);
					PE_DNR0_O26_QRd04(ac_bnr_ctrl_5,		reg_bnr_ac_detail_th1,		pp->dnr___acbnr[19],\
															reg_bnr_ac_detail_th2,		pp->dnr___acbnr[20],\
															reg_bnr_ac_detail_th3,		pp->dnr___acbnr[21],\
															reg_bnr_ac_detail_th4,		pp->dnr___acbnr[22]);
					PE_DNR0_O26_QRd04(ac_bnr_ctrl_6,		reg_bnr_ac_detail_gain_th,	pp->dnr___acbnr[23],\
															reg_bnr_ac_pos_gain_h0, pp->dnr___acbnr[24],\
															reg_bnr_ac_pos_gain_h1, pp->dnr___acbnr[25],\
															reg_bnr_ac_pos_gain_h2, pp->dnr___acbnr[26]);
					PE_DNR0_O26_QRd04(ac_bnr_ctrl_7,		reg_bnr_ac_pos_gain_h3, pp->dnr___acbnr[27],\
															reg_bnr_ac_pos_gain_l0, pp->dnr___acbnr[28],\
															reg_bnr_ac_pos_gain_l1, pp->dnr___acbnr[29],\
															reg_bnr_ac_pos_gain_l2, pp->dnr___acbnr[30]);
					pd = pp->dnr_____mnr;
					printk("get[%d] : dnr_____mnr\n"
					"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

					pd = pp->dnr___dcbnr;
					printk("get[%d] : dnr___dcbnr\n"
					"dnr___dcbnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr___dcbnr	[30]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32], pd[33]);

					pd = pp->dnr___acbnr;
					printk("get[%d] : dnr___acbnr\n"
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
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_SetDnrDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT16 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DCNT_CMN_T *ctrl_param =(LX_PE_NRD_DCNT_CMN_T *)pstParams;
			LX_PE_NRD_DCNT3_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			LX_PE_NRD_EASY_DCNT_CMN_T *epp = (typeof(*epp) *)ctrl_param->data;
			static LX_PE_NRD_DCNT3_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT3_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DEC("duplicated DB : LX_PE_NRD_DCNT2_CMN_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd32 = pp->deconnd_____ui;
					PE_DBG_DEC("set[%d] : deconnd_____ui\n"
					"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
					pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
					pd32 = pp->deconnd___buff;
					PE_DBG_DEC("set[%d] : deconnd___buff\n"\
					"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_0,	reg_1st_out_rd_on,	GET_BITS(pp->deconnd_____ui[0],0,1),\
																reg_1st_out_rd_bit, GET_BITS(pp->deconnd_____ui[1],0,3));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_7,	reg_2nd_out_rd_on,	GET_BITS(pp->deconnd_____ui[2],0,1),\
																reg_2nd_out_rd_bit, GET_BITS(pp->deconnd_____ui[3],0,4));
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,	GET_BITS(pp->deconnd_____ui[4],0,1));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_19,	reg_decon_diff_x_th3,	GET_BITS(pp->deconnd_____ui[5],0,8),\
																reg_decon_diff_x_th2,	GET_BITS(pp->deconnd_____ui[6],0,8),\
																reg_decon_diff_x_th1,	GET_BITS(pp->deconnd_____ui[7],0,8),\
																reg_decon_diff_x_th0,	GET_BITS(pp->deconnd_____ui[8],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_20,	reg_decon_diff_y_th3,	GET_BITS(pp->deconnd_____ui[9],0,8),\
																reg_decon_diff_y_th2,	GET_BITS(pp->deconnd_____ui[10],0,8),\
																reg_decon_diff_y_th1,	GET_BITS(pp->deconnd_____ui[11],0,8),\
																reg_decon_diff_y_th0,	GET_BITS(pp->deconnd_____ui[12],0,8));
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_56,	reg_face_master_gain,	GET_BITS(pp->deconnd_____ui[13],0,8));
					/* download dnr user db */
					ret = PE_NRD_HW_O26_DownloadDnrDcntUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadDnrDcntUserDb() error.\n",__F__,__L__);
				}
				else
				{
					//epp = (typeof(*epp) *)ctrl_param->data;
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					epp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = epp->data;
					PE_DBG_DEC("set[%d] : dnr____ui\n"\
					"dnr____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr____ui    [10]0x%02X,0x%02X\n",\
					epp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], pd[10], pd[11]);
					#if 0
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_0,	reg_1st_out_rd_on,		GET_BITS(epp->data[0],0,1));
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_7,	reg_2nd_out_rd_on,		GET_BITS(epp->data[1],0,1));
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,		GET_BITS(epp->data[2],0,1));
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_69,	reg_decon_2nd_en,		GET_BITS(epp->data[3],0,1));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_19,	reg_decon_diff_x_th3,	GET_BITS(epp->data[4],0,8),\
																reg_decon_diff_x_th2,	GET_BITS(epp->data[5],0,8),\
																reg_decon_diff_x_th1,	GET_BITS(epp->data[6],0,8),\
																reg_decon_diff_x_th0,	GET_BITS(epp->data[7],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_20,	reg_decon_diff_y_th3,	GET_BITS(epp->data[8],0,8),\
																reg_decon_diff_y_th2,	GET_BITS(epp->data[9],0,8),\
																reg_decon_diff_y_th1,	GET_BITS(epp->data[10],0,8),\
																reg_decon_diff_y_th0,	GET_BITS(epp->data[11],0,8));
					#else
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_0,	reg_1st_out_rd_on,	GET_BITS(epp->data[0],0,1));
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_7,	reg_2nd_out_rd_on,	GET_BITS(epp->data[1],0,1));
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,	GET_BITS(epp->data[2],0,1));
					//PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_69,	reg_decon_2nd_en,	GET_BITS(epp->data[3],0,1));
					PE_NRD_HW_O26_DNR_WR01(reg_decon_ctrl_31,	reg_master_gain,	GET_BITS(epp->data[4],0,8));
					#endif
				}
			}
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnrDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT16 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DCNT_CMN_T *ctrl_param =(LX_PE_NRD_DCNT_CMN_T *)pstParams;
			LX_PE_NRD_DCNT3_CMN_T *pp = ctrl_param->data;
			LX_PE_NRD_EASY_DCNT_CMN_T *epp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DNR0_O26_QRd02(reg_decon_ctrl_0,			reg_1st_out_rd_on,	pp->deconnd_____ui[0],\
																reg_1st_out_rd_bit, pp->deconnd_____ui[1]);
					PE_DNR0_O26_QRd02(reg_decon_ctrl_7,			reg_2nd_out_rd_on,	pp->deconnd_____ui[2],\
																reg_2nd_out_rd_bit, pp->deconnd_____ui[3]);
					PE_DNR0_O26_QRd01(reg_decon_ctrl_17,		reg_decon_1st_en,	pp->deconnd_____ui[4]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_19,		reg_decon_diff_x_th3,	pp->deconnd_____ui[5],\
																reg_decon_diff_x_th2,	pp->deconnd_____ui[6 ],\
																reg_decon_diff_x_th1,	pp->deconnd_____ui[7 ],\
																reg_decon_diff_x_th0,	pp->deconnd_____ui[8 ]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_20,		reg_decon_diff_y_th3,	pp->deconnd_____ui[9 ],\
																reg_decon_diff_y_th2,	pp->deconnd_____ui[10],\
																reg_decon_diff_y_th1,	pp->deconnd_____ui[11],\
																reg_decon_diff_y_th0,	pp->deconnd_____ui[12]);
					PE_DNR0_O26_QRd01(reg_decon_ctrl_56,	reg_face_master_gain,	pp->deconnd_____ui[13]);
					
					pd = pp->deconnd_____ui;
					printk("get[%d] : dnr______ui\n"
						"deconnd_____ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"deconnd_____ui [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
						pp->win_id, \
						pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], pd[10],\
						pd[11], pd[12], pd[13], pd[14]);
				}
				else
				{
					//epp = ctrl_param->data;
					PE_DNR0_O26_QRd01(reg_decon_ctrl_0,		reg_1st_out_rd_on,	pp->deconnd_____ui[0]);
					PE_DNR0_O26_QRd01(reg_decon_ctrl_7,		reg_2nd_out_rd_on,	pp->deconnd_____ui[1]);
					PE_DNR0_O26_QRd01(reg_decon_ctrl_17,	reg_decon_1st_en,	pp->deconnd_____ui[2]);
					//PE_DNR0_O26_QRd01(reg_decon_ctrl_69,	reg_decon_2nd_en,	pp->deconnd_____ui[3]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_19,	reg_decon_diff_x_th3,	pp->deconnd_____ui[4],\
															reg_decon_diff_x_th2,	pp->deconnd_____ui[5],\
															reg_decon_diff_x_th1,	pp->deconnd_____ui[6],\
															reg_decon_diff_x_th0,	pp->deconnd_____ui[7]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_20,	reg_decon_diff_y_th3,	pp->deconnd_____ui[8],\
															reg_decon_diff_y_th2,	pp->deconnd_____ui[9],\
															reg_decon_diff_y_th1,	pp->deconnd_____ui[10],\
															reg_decon_diff_y_th0,	pp->deconnd_____ui[11]);
					pd = epp->data;
					printk("get[%d] : dnr______ui\n"
						"dnr______ui	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"0x%02X,0x%02X,\n",\
						epp->win_id, \
						pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], pd[10], pd[11]);
				}
			}
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set dnr dnr common ctrl 
 *- use input struct LX_PE_NRD_DCNT3_CMN_T same as PE_NRD_HW_O26_SetDnrDcntCmnCtrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnrDcnt2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT16 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DCNT_CMN_T *ctrl_param =(LX_PE_NRD_DCNT_CMN_T *)pstParams;
			LX_PE_NRD_DCNT3_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			LX_PE_NRD_EASY_DCNT_CMN_T *epp = (typeof(*epp) *)ctrl_param->data;
			static LX_PE_NRD_DCNT3_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT3_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DEC("duplicated DB : LX_PE_NRD_DCNT3_CMN_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd32 = pp->deconnd_____ui;
					PE_DBG_DEC("set[%d] : deconnd_____ui\n"
					"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
					pd32[10], pd32[11], pd32[12], pd32[13], pd32[14]);
					pd32 = pp->deconnd___buff;
					PE_DBG_DEC("set[%d] : deconnd___buff\n"\
					"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_0,	reg_1st_out_rd_on,	GET_BITS(pp->deconnd_____ui[0],0,1),\
																reg_1st_out_rd_bit, GET_BITS(pp->deconnd_____ui[1],0,3));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_7,	reg_2nd_out_rd_on,	GET_BITS(pp->deconnd_____ui[2],0,1),\
																reg_2nd_out_rd_bit, GET_BITS(pp->deconnd_____ui[3],0,4));
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,	GET_BITS(pp->deconnd_____ui[4],0,1));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_19,	reg_decon_diff_x_th3,	GET_BITS(pp->deconnd_____ui[5],0,8),\
																reg_decon_diff_x_th2,	GET_BITS(pp->deconnd_____ui[6],0,8),\
																reg_decon_diff_x_th1,	GET_BITS(pp->deconnd_____ui[7],0,8),\
																reg_decon_diff_x_th0,	GET_BITS(pp->deconnd_____ui[8],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_20,	reg_decon_diff_y_th3,	GET_BITS(pp->deconnd_____ui[9],0,8),\
																reg_decon_diff_y_th2,	GET_BITS(pp->deconnd_____ui[10],0,8),\
																reg_decon_diff_y_th1,	GET_BITS(pp->deconnd_____ui[11],0,8),\
																reg_decon_diff_y_th0,	GET_BITS(pp->deconnd_____ui[12],0,8));
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_56,	reg_face_master_gain,	GET_BITS(pp->deconnd_____ui[13],0,8));
					/* download dnr user db */
					ret = PE_NRD_HW_O26_DownloadDnrDcnt2ndUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadDnrDcntUserDb() error.\n",__F__,__L__);
				}
				else
				{
					//epp = (typeof(*epp) *)ctrl_param->data;
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					epp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = epp->data;
					PE_DBG_DEC("set[%d] : dnr____ui\n"\
					"dnr____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"dnr____ui    [10]0x%02X,0x%02X\n",\
					epp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9], pd[10], pd[11]);
					#if 0
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_0,	reg_1st_out_rd_on,		GET_BITS(epp->data[0],0,1));
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_7,	reg_2nd_out_rd_on,		GET_BITS(epp->data[1],0,1));
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,		GET_BITS(epp->data[2],0,1));
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_69,	reg_decon_2nd_en,		GET_BITS(epp->data[3],0,1));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_19,	reg_decon_diff_x_th3,	GET_BITS(epp->data[4],0,8),\
																reg_decon_diff_x_th2,	GET_BITS(epp->data[5],0,8),\
																reg_decon_diff_x_th1,	GET_BITS(epp->data[6],0,8),\
																reg_decon_diff_x_th0,	GET_BITS(epp->data[7],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_20,	reg_decon_diff_y_th3,	GET_BITS(epp->data[8],0,8),\
																reg_decon_diff_y_th2,	GET_BITS(epp->data[9],0,8),\
																reg_decon_diff_y_th1,	GET_BITS(epp->data[10],0,8),\
																reg_decon_diff_y_th0,	GET_BITS(epp->data[11],0,8));
					#else
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_0,	reg_1st_out_rd_on,	GET_BITS(epp->data[0],0,1));
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_7,	reg_2nd_out_rd_on,	GET_BITS(epp->data[1],0,1));
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,	GET_BITS(epp->data[2],0,1));
					//PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_69,	reg_decon_2nd_en,	GET_BITS(epp->data[3],0,1));
					PE_NRD_HW_O26_DNR1_WR01(reg_decon_ctrl_31,	reg_master_gain,	GET_BITS(epp->data[4],0,8));
					#endif
				}
			}
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set dnr detail ctrl
 * - use input struct LX_PE_NRD_DCNT5_DETAIL_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnrDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT16 *pd;
	UINT8 *pd8;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DCNT_DETAIL_T *ctrl_param =(LX_PE_NRD_DCNT_DETAIL_T *)pstParams;
			LX_PE_NRD_DCNT5_DETAIL_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_NRD_DCNT5_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT5_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DEC("duplicated DB : LX_PE_NRD_DCNT4_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = pp->deconnd____cmn;
					PE_DBG_DEC("set[%d] : deconnd____cmn\n"
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
					PE_DBG_DEC("set[%d] : deconnd___face\n"
					"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd8[0], pd8[1], pd8[2], pd8[3], pd8[4], pd8[5], pd8[6], pd8[7], pd8[8], pd8[9],\
					pd8[10], pd8[11], pd8[12], pd8[13], pd8[14], pd8[15], pd8[16], pd8[17], pd8[18], pd8[19],\
					pd8[20], pd8[21], pd8[22], pd8[23], pd8[24], pd8[25], pd8[26], pd8[27]);	
					/*dnr_dcnt*/
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_18,	reg_var_cut_resolution,	GET_BITS(pp->deconnd____cmn[0],0,4),\
																reg_var_h_gain,			GET_BITS(pp->deconnd____cmn[1],0,4),\
																reg_var_chroma_en,		GET_BITS(pp->deconnd____cmn[2],0,1));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_21,	reg_decon_var_x_th0,	GET_BITS(pp->deconnd____cmn[3],0,10),\
																reg_decon_var_x_th1,	GET_BITS(pp->deconnd____cmn[4],0,10),\
																reg_decon_var_x_th2,	GET_BITS(pp->deconnd____cmn[5],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_22,	reg_decon_var_x_th3,	GET_BITS(pp->deconnd____cmn[6],0,10),\
																reg_decon_var_y_th0,	GET_BITS(pp->deconnd____cmn[7],0,10),\
																reg_decon_var_y_th1,	GET_BITS(pp->deconnd____cmn[8],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_23,	reg_decon_var_y_th2,	GET_BITS(pp->deconnd____cmn[9],0,10),\
																reg_decon_var_y_th3,	GET_BITS(pp->deconnd____cmn[10],0,10),\
																reg_decon_luma_x_th0,	GET_BITS(pp->deconnd____cmn[11],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_24,	reg_decon_luma_x_th1,	GET_BITS(pp->deconnd____cmn[12],0,10),\
																reg_decon_luma_x_th2,	GET_BITS(pp->deconnd____cmn[13],0,10),\
																reg_decon_luma_x_th3,	GET_BITS(pp->deconnd____cmn[14],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_25,	reg_decon_luma_x_th4,	GET_BITS(pp->deconnd____cmn[15],0,10),\
																reg_decon_luma_x_th5,	GET_BITS(pp->deconnd____cmn[16],0,10),\
																reg_decon_luma_x_th6,	GET_BITS(pp->deconnd____cmn[17],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_26,	reg_decon_luma_x_th7,	GET_BITS(pp->deconnd____cmn[18],0,10),\
																reg_decon_luma_y_th0,	GET_BITS(pp->deconnd____cmn[19],0,10),\
																reg_decon_luma_y_th1,	GET_BITS(pp->deconnd____cmn[20],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_27,	reg_decon_luma_y_th2,	GET_BITS(pp->deconnd____cmn[21],0,10),\
																reg_decon_luma_y_th3,	GET_BITS(pp->deconnd____cmn[22],0,10),\
																reg_decon_luma_y_th4,	GET_BITS(pp->deconnd____cmn[23],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_28,	reg_decon_luma_y_th5,	GET_BITS(pp->deconnd____cmn[24],0,10),\
																reg_decon_luma_y_th6,	GET_BITS(pp->deconnd____cmn[25],0,10),\
																reg_decon_luma_y_th7,	GET_BITS(pp->deconnd____cmn[26],0,10));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_44,	reg_motion_gain_x0,		GET_BITS(pp->deconnd____cmn[27],0,8),\
																reg_motion_gain_x1,		GET_BITS(pp->deconnd____cmn[28],0,8),\
																reg_motion_gain_x2,		GET_BITS(pp->deconnd____cmn[29],0,8),\
																reg_motion_gain_x3,		GET_BITS(pp->deconnd____cmn[30],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_45,	reg_motion_gain_y0,		GET_BITS(pp->deconnd____cmn[31],0,8),\
																reg_motion_gain_y1,		GET_BITS(pp->deconnd____cmn[32],0,8),\
																reg_motion_gain_y2,		GET_BITS(pp->deconnd____cmn[33],0,8),\
																reg_motion_gain_y3,		GET_BITS(pp->deconnd____cmn[34],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_48,	reg_lut_blur_sim_x0,	GET_BITS(pp->deconnd____cmn[35],0,8),\
																reg_lut_blur_sim_x1,	GET_BITS(pp->deconnd____cmn[36],0,8),\
																reg_lut_blur_sim_x2,	GET_BITS(pp->deconnd____cmn[37],0,8),\
																reg_lut_blur_sim_x3,	GET_BITS(pp->deconnd____cmn[38],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_49,	reg_lut_blur_sim_y0,	GET_BITS(pp->deconnd____cmn[39],0,8),\
																reg_lut_blur_sim_y1,	GET_BITS(pp->deconnd____cmn[40],0,8),\
																reg_lut_blur_sim_y2,	GET_BITS(pp->deconnd____cmn[41],0,8),\
																reg_lut_blur_sim_y3,	GET_BITS(pp->deconnd____cmn[42],0,8));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_69,	reg_var_lowapl_lut_x0,	GET_BITS(pp->deconnd____cmn[43],0,10),\
																reg_var_lowapl_lut_x1,	GET_BITS(pp->deconnd____cmn[44],0,10),\
																reg_var_lowapl_lut_x2,	GET_BITS(pp->deconnd____cmn[45],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_70,	reg_var_lowapl_lut_x3,	GET_BITS(pp->deconnd____cmn[46],0,10),\
																reg_var_lowapl_lut_y0,	GET_BITS(pp->deconnd____cmn[47],0,10),\
																reg_var_lowapl_lut_y1,	GET_BITS(pp->deconnd____cmn[48],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_71,	reg_var_lowapl_lut_y2,	GET_BITS(pp->deconnd____cmn[49],0,10),\
																reg_var_lowapl_lut_y3,	GET_BITS(pp->deconnd____cmn[50],0,10),\
																reg_var_lowapl_blend_x0,GET_BITS(pp->deconnd____cmn[51],0,10));
					PE_NRD_HW_O26_DNR_WR03(reg_decon_ctrl_72,	reg_var_lowapl_blend_x1,GET_BITS(pp->deconnd____cmn[52],0,10),\
																reg_var_lowapl_blend_x2,GET_BITS(pp->deconnd____cmn[53],0,10),\
																reg_var_lowapl_blend_x3,GET_BITS(pp->deconnd____cmn[54],0,10));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_73,	reg_var_lowapl_blend_y0,GET_BITS(pp->deconnd____cmn[55],0,8),\
																reg_var_lowapl_blend_y1,GET_BITS(pp->deconnd____cmn[56],0,8),\
																reg_var_lowapl_blend_y2,GET_BITS(pp->deconnd____cmn[57],0,8),\
																reg_var_lowapl_blend_y3,GET_BITS(pp->deconnd____cmn[58],0,8));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_84,	reg_1st_rd_luma_en,		GET_BITS(pp->deconnd____cmn[59],0,1),\
																reg_2nd_rd_luma_en,		GET_BITS(pp->deconnd____cmn[60],0,1));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_87,	reg_1st_rd_luma_x0,		GET_BITS(pp->deconnd____cmn[61],0,10),\
																reg_1st_rd_luma_x1,		GET_BITS(pp->deconnd____cmn[62],0,10));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_88,	reg_1st_rd_luma_x2,		GET_BITS(pp->deconnd____cmn[63],0,10),\
																reg_1st_rd_luma_x3,		GET_BITS(pp->deconnd____cmn[64],0,10));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_89,	reg_1st_rd_luma_x4,		GET_BITS(pp->deconnd____cmn[65],0,10),\
																reg_1st_rd_luma_x5,		GET_BITS(pp->deconnd____cmn[66],0,10));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_90,	reg_1st_rd_luma_x6,		GET_BITS(pp->deconnd____cmn[67],0,10),\
																reg_1st_rd_luma_x7,		GET_BITS(pp->deconnd____cmn[68],0,10));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_91,	reg_1st_rd_luma_y0,		GET_BITS(pp->deconnd____cmn[69],0,10),\
																reg_1st_rd_luma_y1,		GET_BITS(pp->deconnd____cmn[70],0,10));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_92,	reg_1st_rd_luma_y2,		GET_BITS(pp->deconnd____cmn[71],0,10),\
																reg_1st_rd_luma_y3,		GET_BITS(pp->deconnd____cmn[72],0,10));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_93,	reg_1st_rd_luma_y4,		GET_BITS(pp->deconnd____cmn[73],0,10),\
																reg_1st_rd_luma_y5,		GET_BITS(pp->deconnd____cmn[74],0,10));
					PE_NRD_HW_O26_DNR_WR02(reg_decon_ctrl_94,	reg_1st_rd_luma_y6,		GET_BITS(pp->deconnd____cmn[75],0,10),\
																reg_1st_rd_luma_y7,		GET_BITS(pp->deconnd____cmn[76],0,10));
					/* face obj*/
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_50,	reg_lut_skin_yy_x0,	GET_BITS(pp->deconnd___face[0],0,8),\
																reg_lut_skin_yy_x1,	GET_BITS(pp->deconnd___face[1],0,8),\
																reg_lut_skin_yy_x2,	GET_BITS(pp->deconnd___face[2],0,8),\
																reg_lut_skin_yy_x3,	GET_BITS(pp->deconnd___face[3],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_51,	reg_lut_skin_cb_x0,	GET_BITS(pp->deconnd___face[4],0,8),\
																reg_lut_skin_cb_x1,	GET_BITS(pp->deconnd___face[5],0,8),\
																reg_lut_skin_cb_x2,	GET_BITS(pp->deconnd___face[6],0,8),\
																reg_lut_skin_cb_x3,	GET_BITS(pp->deconnd___face[7],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_52,	reg_lut_skin_cr_x0,	GET_BITS(pp->deconnd___face[8],0,8),\
																reg_lut_skin_cr_x1,	GET_BITS(pp->deconnd___face[9],0,8),\
																reg_lut_skin_cr_x2,	GET_BITS(pp->deconnd___face[10],0,8),\
																reg_lut_skin_cr_x3,	GET_BITS(pp->deconnd___face[11],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_53,	reg_lut_skin_y0,	GET_BITS(pp->deconnd___face[12],0,8),\
																reg_lut_skin_y1,	GET_BITS(pp->deconnd___face[13],0,8),\
																reg_lut_skin_y2,	GET_BITS(pp->deconnd___face[14],0,8),\
																reg_lut_skin_y3,	GET_BITS(pp->deconnd___face[15],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_54,	reg_lut_face_x0,	GET_BITS(pp->deconnd___face[16],0,8),\
																reg_lut_face_x1,	GET_BITS(pp->deconnd___face[17],0,8),\
																reg_lut_face_x2,	GET_BITS(pp->deconnd___face[18],0,8),\
																reg_lut_face_x3,	GET_BITS(pp->deconnd___face[19],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_97,	reg_ref_mmd_gain_x3,	GET_BITS(pp->deconnd___face[20],0,8),\
																reg_ref_mmd_gain_x2,	GET_BITS(pp->deconnd___face[21],0,8),\
																reg_ref_mmd_gain_x1,	GET_BITS(pp->deconnd___face[22],0,8),\
																reg_ref_mmd_gain_x0,	GET_BITS(pp->deconnd___face[23],0,8));
					PE_NRD_HW_O26_DNR_WR04(reg_decon_ctrl_98,	reg_ref_mmd_gain_y3,	GET_BITS(pp->deconnd___face[24],0,8),\
																reg_ref_mmd_gain_y2,	GET_BITS(pp->deconnd___face[25],0,8),\
																reg_ref_mmd_gain_y1,	GET_BITS(pp->deconnd___face[26],0,8),\
																reg_ref_mmd_gain_y0,	GET_BITS(pp->deconnd___face[27],0,8));
					}
			}
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnrDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT16 *pd;
	UINT8 *pd8;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DCNT_DETAIL_T *ctrl_param =(LX_PE_NRD_DCNT_DETAIL_T *)pstParams;
			LX_PE_NRD_DCNT3_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					/*dnr_dcnt*/
					PE_DNR0_O26_QRd03(reg_decon_ctrl_18,	reg_var_cut_resolution,	pp->deconnd____cmn[0],\
																reg_var_h_gain,			pp->deconnd____cmn[1],\
																reg_var_chroma_en,		pp->deconnd____cmn[2]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_21,	reg_decon_var_x_th0,	pp->deconnd____cmn[3],\
																reg_decon_var_x_th1,	pp->deconnd____cmn[4],\
																reg_decon_var_x_th2,	pp->deconnd____cmn[5]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_22,	reg_decon_var_x_th3,	pp->deconnd____cmn[6],\
																reg_decon_var_y_th0,	pp->deconnd____cmn[7],\
																reg_decon_var_y_th1,	pp->deconnd____cmn[8]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_23,	reg_decon_var_y_th2,	pp->deconnd____cmn[9],\
																reg_decon_var_y_th3,	pp->deconnd____cmn[10],\
																reg_decon_luma_x_th0,	pp->deconnd____cmn[11]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_24,	reg_decon_luma_x_th1,	pp->deconnd____cmn[12],\
																reg_decon_luma_x_th2,	pp->deconnd____cmn[13],\
																reg_decon_luma_x_th3,	pp->deconnd____cmn[14]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_25,	reg_decon_luma_x_th4,	pp->deconnd____cmn[15],\
																reg_decon_luma_x_th5,	pp->deconnd____cmn[16],\
																reg_decon_luma_x_th6,	pp->deconnd____cmn[17]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_26,	reg_decon_luma_x_th7,	pp->deconnd____cmn[18],\
																reg_decon_luma_y_th0,	pp->deconnd____cmn[19],\
																reg_decon_luma_y_th1,	pp->deconnd____cmn[20]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_27,	reg_decon_luma_y_th2,	pp->deconnd____cmn[21],\
																reg_decon_luma_y_th3,	pp->deconnd____cmn[22],\
																reg_decon_luma_y_th4,	pp->deconnd____cmn[23]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_28,	reg_decon_luma_y_th5,	pp->deconnd____cmn[24],\
																reg_decon_luma_y_th6,	pp->deconnd____cmn[25],\
																reg_decon_luma_y_th7,	pp->deconnd____cmn[26]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_69,	reg_2nd_var_chroma_en,	pp->deconnd____cmn[27],\
																reg_2nd_var_cut_resolution,	pp->deconnd____cmn[28],\
																reg_2nd_var_h_gain,	pp->deconnd____cmn[29],\
																reg_2nd_var_v_gain,	pp->deconnd____cmn[30]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_70,	reg_2nd_luma_x_th0,	pp->deconnd____cmn[31],\
																reg_2nd_luma_x_th1,	pp->deconnd____cmn[32],\
																reg_2nd_luma_x_th2,	pp->deconnd____cmn[33]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_71,	reg_2nd_luma_x_th3,	pp->deconnd____cmn[34],\
																reg_2nd_luma_x_th4,	pp->deconnd____cmn[35],\
																reg_2nd_luma_x_th5,	pp->deconnd____cmn[36]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_72,	reg_2nd_luma_x_th6,	pp->deconnd____cmn[37],\
																reg_2nd_luma_x_th7,	pp->deconnd____cmn[38],\
																reg_2nd_luma_y_th0,	pp->deconnd____cmn[39]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_73,	reg_2nd_luma_y_th1,	pp->deconnd____cmn[40],\
																reg_2nd_luma_y_th2,	pp->deconnd____cmn[41],\
																reg_2nd_luma_y_th3,	pp->deconnd____cmn[42]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_74,	reg_2nd_luma_y_th4,	pp->deconnd____cmn[43],\
																reg_2nd_luma_y_th5,	pp->deconnd____cmn[44],\
																reg_2nd_luma_y_th6,	pp->deconnd____cmn[45]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_75,	reg_2nd_luma_y_th7,	pp->deconnd____cmn[46],\
																reg_2nd_var_x_th0,	pp->deconnd____cmn[47],\
																reg_2nd_var_x_th1,	pp->deconnd____cmn[48]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_76,	reg_2nd_var_x_th2,	pp->deconnd____cmn[49],\
																reg_2nd_var_x_th3,	pp->deconnd____cmn[50],\
																reg_2nd_var_y_th0,	pp->deconnd____cmn[51]);
					PE_DNR0_O26_QRd03(reg_decon_ctrl_77,	reg_2nd_var_y_th1,	pp->deconnd____cmn[52],\
																reg_2nd_var_y_th2,	pp->deconnd____cmn[53],\
																reg_2nd_var_y_th3,	pp->deconnd____cmn[54]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_78,	reg_2nd_diff_x_th3,	pp->deconnd____cmn[55],\
																reg_2nd_diff_x_th2,	pp->deconnd____cmn[56],\
																reg_2nd_diff_x_th1,	pp->deconnd____cmn[57],\
																reg_2nd_diff_x_th0,	pp->deconnd____cmn[58]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_79,	reg_2nd_diff_y_th3,	pp->deconnd____cmn[59],\
																reg_2nd_diff_y_th2,	pp->deconnd____cmn[60],\
																reg_2nd_diff_y_th1,	pp->deconnd____cmn[61],\
																reg_2nd_diff_y_th0,	pp->deconnd____cmn[62]);
					/* face obj*/
					PE_DNR0_O26_QRd04(reg_decon_ctrl_50,	reg_lut_skin_yy_x0,	pp->deconnd___face[0],\
																reg_lut_skin_yy_x1,	pp->deconnd___face[1],\
																reg_lut_skin_yy_x2,	pp->deconnd___face[2],\
																reg_lut_skin_yy_x3,	pp->deconnd___face[3]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_51,	reg_lut_skin_cb_x0,	pp->deconnd___face[4],\
																reg_lut_skin_cb_x1,	pp->deconnd___face[5],\
																reg_lut_skin_cb_x2,	pp->deconnd___face[6],\
																reg_lut_skin_cb_x3,	pp->deconnd___face[7]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_52,	reg_lut_skin_cr_x0,	pp->deconnd___face[8],\
																reg_lut_skin_cr_x1,	pp->deconnd___face[9],\
																reg_lut_skin_cr_x2,	pp->deconnd___face[10],\
																reg_lut_skin_cr_x3,	pp->deconnd___face[11]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_53,	reg_lut_skin_y0,	pp->deconnd___face[12],\
																reg_lut_skin_y1,	pp->deconnd___face[13],\
																reg_lut_skin_y2,	pp->deconnd___face[14],\
																reg_lut_skin_y3,	pp->deconnd___face[15]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_54,	reg_lut_face_x0,	pp->deconnd___face[16],\
																reg_lut_face_x1,	pp->deconnd___face[17],\
																reg_lut_face_x2,	pp->deconnd___face[18],\
																reg_lut_face_x3,	pp->deconnd___face[19]);
					PE_DNR0_O26_QRd04(reg_decon_ctrl_55,	reg_lut_face_y0,	pp->deconnd___face[20],\
																reg_lut_face_y1,	pp->deconnd___face[21],\
																reg_lut_face_y2,	pp->deconnd___face[22],\
																reg_lut_face_y3,	pp->deconnd___face[23]);

					printk("get[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = pp->deconnd____cmn;
					printk("set[%d] : deconnd____cmn\n"
					"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
					pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
					pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57], pd[58], pd[59],\
					pd[60], pd[61], pd[62]);
					pd8 = pp->deconnd___face;
					printk("get[%d] : deconnd___face\n"
					"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd___face    [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd8[0], pd8[1], pd8[2], pd8[3], pd8[4], pd8[5], pd8[6], pd8[7], pd8[8], pd8[9],\
					pd8[10], pd8[11], pd8[12], pd8[13], pd8[14], pd8[15], pd8[16], pd8[17], pd8[18], pd8[19],\
					pd8[20], pd8[21], pd8[22], pd8[23]);	
				}
			}
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set dnr detail ctrl
 * - use input struct LX_PE_NRD_DCNT5_DETAIL_T same as PE_NRD_HW_O26_SetDnrDcntDetailCtrl
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnrDcnt2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT16 *pd;
	UINT8 *pd8;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DCNT_DETAIL_T *ctrl_param =(LX_PE_NRD_DCNT_DETAIL_T *)pstParams;
			LX_PE_NRD_DCNT5_DETAIL_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_NRD_DCNT5_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT5_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DEC("duplicated DB : LX_PE_NRD_DCNT5_DETAIL_T 2nd\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = pp->deconnd____cmn;
					PE_DBG_DEC("set[%d] : deconnd____cmn\n"
					"deconnd____cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd____cmn    [60]0x%02X\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
					pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
					pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57], pd[58], pd[59],\
					pd[60]);
					pd8 = pp->deconnd___face;
					PE_DBG_DEC("set[%d] : deconnd___face\n"
					"deconnd___face    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconnd___face    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd8[0], pd8[1], pd8[2], pd8[3], pd8[4], pd8[5], pd8[6], pd8[7], pd8[8], pd8[9],\
					pd8[10], pd8[11], pd8[12], pd8[13], pd8[14], pd8[15], pd8[16], pd8[17], pd8[18], pd8[19]);	
					/*dnr_dcnt*/
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_18,	reg_var_cut_resolution,	GET_BITS(pp->deconnd____cmn[0],0,4),\
																reg_var_h_gain,			GET_BITS(pp->deconnd____cmn[1],0,4),\
																reg_var_chroma_en,		GET_BITS(pp->deconnd____cmn[2],0,1));
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_21,	reg_decon_var_x_th0,	GET_BITS(pp->deconnd____cmn[3],0,10),\
																reg_decon_var_x_th1,	GET_BITS(pp->deconnd____cmn[4],0,10),\
																reg_decon_var_x_th2,	GET_BITS(pp->deconnd____cmn[5],0,10));
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_22,	reg_decon_var_x_th3,	GET_BITS(pp->deconnd____cmn[6],0,10),\
																reg_decon_var_y_th0,	GET_BITS(pp->deconnd____cmn[7],0,10),\
																reg_decon_var_y_th1,	GET_BITS(pp->deconnd____cmn[8],0,10));
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_23,	reg_decon_var_y_th2,	GET_BITS(pp->deconnd____cmn[9],0,10),\
																reg_decon_var_y_th3,	GET_BITS(pp->deconnd____cmn[10],0,10),\
																reg_decon_luma_x_th0,	GET_BITS(pp->deconnd____cmn[11],0,10));
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_24,	reg_decon_luma_x_th1,	GET_BITS(pp->deconnd____cmn[12],0,10),\
																reg_decon_luma_x_th2,	GET_BITS(pp->deconnd____cmn[13],0,10),\
																reg_decon_luma_x_th3,	GET_BITS(pp->deconnd____cmn[14],0,10));
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_25,	reg_decon_luma_x_th4,	GET_BITS(pp->deconnd____cmn[15],0,10),\
																reg_decon_luma_x_th5,	GET_BITS(pp->deconnd____cmn[16],0,10),\
																reg_decon_luma_x_th6,	GET_BITS(pp->deconnd____cmn[17],0,10));
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_26,	reg_decon_luma_x_th7,	GET_BITS(pp->deconnd____cmn[18],0,10),\
																reg_decon_luma_y_th0,	GET_BITS(pp->deconnd____cmn[19],0,10),\
																reg_decon_luma_y_th1,	GET_BITS(pp->deconnd____cmn[20],0,10));
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_27,	reg_decon_luma_y_th2,	GET_BITS(pp->deconnd____cmn[21],0,10),\
																reg_decon_luma_y_th3,	GET_BITS(pp->deconnd____cmn[22],0,10),\
																reg_decon_luma_y_th4,	GET_BITS(pp->deconnd____cmn[23],0,10));
					PE_NRD_HW_O26_DNR1_WR03(reg_decon_ctrl_28,	reg_decon_luma_y_th5,	GET_BITS(pp->deconnd____cmn[24],0,10),\
																reg_decon_luma_y_th6,	GET_BITS(pp->deconnd____cmn[25],0,10),\
																reg_decon_luma_y_th7,	GET_BITS(pp->deconnd____cmn[26],0,10));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_44,	reg_motion_gain_x0,		GET_BITS(pp->deconnd____cmn[27],0,8),\
																reg_motion_gain_x1,		GET_BITS(pp->deconnd____cmn[28],0,8),\
																reg_motion_gain_x2,		GET_BITS(pp->deconnd____cmn[29],0,8),\
																reg_motion_gain_x3,		GET_BITS(pp->deconnd____cmn[30],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_45,	reg_motion_gain_y0,		GET_BITS(pp->deconnd____cmn[31],0,8),\
																reg_motion_gain_y1,		GET_BITS(pp->deconnd____cmn[32],0,8),\
																reg_motion_gain_y2,		GET_BITS(pp->deconnd____cmn[33],0,8),\
																reg_motion_gain_y3,		GET_BITS(pp->deconnd____cmn[34],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_48,	reg_lut_blur_sim_x0,	GET_BITS(pp->deconnd____cmn[35],0,8),\
																reg_lut_blur_sim_x1,	GET_BITS(pp->deconnd____cmn[36],0,8),\
																reg_lut_blur_sim_x2,	GET_BITS(pp->deconnd____cmn[37],0,8),\
																reg_lut_blur_sim_x3,	GET_BITS(pp->deconnd____cmn[38],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_49,	reg_lut_blur_sim_y0,	GET_BITS(pp->deconnd____cmn[39],0,8),\
																reg_lut_blur_sim_y1,	GET_BITS(pp->deconnd____cmn[40],0,8),\
																reg_lut_blur_sim_y2,	GET_BITS(pp->deconnd____cmn[41],0,8),\
																reg_lut_blur_sim_y3,	GET_BITS(pp->deconnd____cmn[42],0,8));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_69,	reg_1st_rd_luma_en,		GET_BITS(pp->deconnd____cmn[43],0,1),\
																reg_2nd_rd_luma_en,		GET_BITS(pp->deconnd____cmn[44],0,1));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_72,	reg_1st_rd_luma_x0,		GET_BITS(pp->deconnd____cmn[45],0,10),\
																reg_1st_rd_luma_x1,		GET_BITS(pp->deconnd____cmn[46],0,10));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_73,	reg_1st_rd_luma_x2,		GET_BITS(pp->deconnd____cmn[47],0,10),\
																reg_1st_rd_luma_x3,		GET_BITS(pp->deconnd____cmn[48],0,10));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_74,	reg_1st_rd_luma_x4,		GET_BITS(pp->deconnd____cmn[49],0,10),\
																reg_1st_rd_luma_x5,		GET_BITS(pp->deconnd____cmn[50],0,10));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_75,	reg_1st_rd_luma_x6,		GET_BITS(pp->deconnd____cmn[51],0,10),\
																reg_1st_rd_luma_x7,		GET_BITS(pp->deconnd____cmn[52],0,10));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_76,	reg_1st_rd_luma_y0,		GET_BITS(pp->deconnd____cmn[53],0,10),\
																reg_1st_rd_luma_y1,		GET_BITS(pp->deconnd____cmn[54],0,10));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_77,	reg_1st_rd_luma_y2,		GET_BITS(pp->deconnd____cmn[55],0,10),\
																reg_1st_rd_luma_y3,		GET_BITS(pp->deconnd____cmn[56],0,10));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_78,	reg_1st_rd_luma_y4,		GET_BITS(pp->deconnd____cmn[57],0,10),\
																reg_1st_rd_luma_y5,		GET_BITS(pp->deconnd____cmn[58],0,10));
					PE_NRD_HW_O26_DNR1_WR02(reg_decon_ctrl_79,	reg_1st_rd_luma_y6,		GET_BITS(pp->deconnd____cmn[59],0,10),\
																reg_1st_rd_luma_y7,		GET_BITS(pp->deconnd____cmn[60],0,10));
					/* face obj*/
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_50,	reg_lut_skin_yy_x0,	GET_BITS(pp->deconnd___face[0],0,8),\
																reg_lut_skin_yy_x1,	GET_BITS(pp->deconnd___face[1],0,8),\
																reg_lut_skin_yy_x2,	GET_BITS(pp->deconnd___face[2],0,8),\
																reg_lut_skin_yy_x3,	GET_BITS(pp->deconnd___face[3],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_51,	reg_lut_skin_cb_x0,	GET_BITS(pp->deconnd___face[4],0,8),\
																reg_lut_skin_cb_x1,	GET_BITS(pp->deconnd___face[5],0,8),\
																reg_lut_skin_cb_x2,	GET_BITS(pp->deconnd___face[6],0,8),\
																reg_lut_skin_cb_x3,	GET_BITS(pp->deconnd___face[7],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_52,	reg_lut_skin_cr_x0,	GET_BITS(pp->deconnd___face[8],0,8),\
																reg_lut_skin_cr_x1,	GET_BITS(pp->deconnd___face[9],0,8),\
																reg_lut_skin_cr_x2,	GET_BITS(pp->deconnd___face[10],0,8),\
																reg_lut_skin_cr_x3,	GET_BITS(pp->deconnd___face[11],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_53,	reg_lut_skin_y0,	GET_BITS(pp->deconnd___face[12],0,8),\
																reg_lut_skin_y1,	GET_BITS(pp->deconnd___face[13],0,8),\
																reg_lut_skin_y2,	GET_BITS(pp->deconnd___face[14],0,8),\
																reg_lut_skin_y3,	GET_BITS(pp->deconnd___face[15],0,8));
					PE_NRD_HW_O26_DNR1_WR04(reg_decon_ctrl_54,	reg_lut_face_x0,	GET_BITS(pp->deconnd___face[16],0,8),\
																reg_lut_face_x1,	GET_BITS(pp->deconnd___face[17],0,8),\
																reg_lut_face_x2,	GET_BITS(pp->deconnd___face[18],0,8),\
																reg_lut_face_x3,	GET_BITS(pp->deconnd___face[19],0,8));
					}
			}
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set cco decontour common ctrl 
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetCCODcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_CCO_DCNT_CMN_T *ctrl_param =(LX_PE_CCO_DCNT_CMN_T *)pstParams;
			LX_PE_CCO_DCNT1_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			//LX_PE_LED_EASY_DCNT_CMN_T *epp = (typeof(*epp) *)ctrl_param->data;
			static LX_PE_CCO_DCNT1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_CCO_DCNT1_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DEC("duplicated DB : LX_PE_CCO_DCNT1_CMN_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					//pp = ctrl_param->data;
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd32 = pp->deconcco____ui;
					PE_DBG_DEC("set[%d] : deconcco____ui\n"
					"deconcco____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"deconcco____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"deconcco____ui    [20]0x%02X,0x%02X\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9], \
					pd32[10], pd32[11], pd32[12], pd32[13], pd32[14], pd32[15], pd32[16], pd32[17], pd32[18], pd32[19], \
					pd32[20], pd32[21]);
					pd32 = pp->deconcco__buff;
					PE_DBG_DEC("set[%d] : deconcco__buff\n"
					"deconcco__buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
					PE_NRD_HW_O26_CCO_DNR_WR02(reg_decon_ctrl_0,	reg_1st_out_rd_on,	GET_BITS(pp->deconcco____ui[0],0,1),\
																	reg_1st_out_rd_bit, GET_BITS(pp->deconcco____ui[1],0,3));
					PE_NRD_HW_O26_CCO_DNR_WR02(reg_decon_ctrl_7,	reg_2nd_out_rd_on,	GET_BITS(pp->deconcco____ui[2],0,1),\
																	reg_2nd_out_rd_bit, GET_BITS(pp->deconcco____ui[3],0,4));
					PE_NRD_HW_O26_CCO_DNR_WR01(reg_decon_ctrl_17,	reg_decon_1st_en,   GET_BITS(pp->deconcco____ui[4],0,1));
					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_19,	reg_decon_diff_x_th0, GET_BITS(pp->deconcco____ui[8],0,8),\
																	reg_decon_diff_x_th1, GET_BITS(pp->deconcco____ui[7],0,8),\
																	reg_decon_diff_x_th2, GET_BITS(pp->deconcco____ui[6],0,8),\
																	reg_decon_diff_x_th3, GET_BITS(pp->deconcco____ui[5],0,8));
					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_20,	reg_decon_diff_y_th0, GET_BITS(pp->deconcco____ui[12],0,8),\
																	reg_decon_diff_y_th1, GET_BITS(pp->deconcco____ui[11],0,8),\
																	reg_decon_diff_y_th2, GET_BITS(pp->deconcco____ui[10],0,8),\
																	reg_decon_diff_y_th3, GET_BITS(pp->deconcco____ui[9],0,8));
					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_84,	reg_decon_low_diff_x_th0, GET_BITS(pp->deconcco____ui[16],0,8),\
																	reg_decon_low_diff_x_th1, GET_BITS(pp->deconcco____ui[15],0,8),\
																	reg_decon_low_diff_x_th2, GET_BITS(pp->deconcco____ui[14],0,8),\
																	reg_decon_low_diff_x_th3, GET_BITS(pp->deconcco____ui[13],0,8));
					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_85,	reg_decon_low_diff_y_th0, GET_BITS(pp->deconcco____ui[20],0,8),\
																	reg_decon_low_diff_y_th1, GET_BITS(pp->deconcco____ui[19],0,8),\
																	reg_decon_low_diff_y_th2, GET_BITS(pp->deconcco____ui[18],0,8),\
																	reg_decon_low_diff_y_th3, GET_BITS(pp->deconcco____ui[17],0,8));
					PE_NRD_HW_O26_CCO_DNR_WR01(reg_decon_ctrl_56,	reg_face_master_gain,     GET_BITS(pp->deconcco____ui[21],0,8));

					
					/* download dnr user db */
					ret = PE_NRD_HW_O26_DownloadCCODcntUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadCCODcntUserDb() error.\n",__F__,__L__);
				}
				else
				{
					#if 0
					//epp = ctrl_param->data;
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					epp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = epp->data;
					PE_DBG_DEC("set[%d] : dnrled____ui\n"
					"dnrled____ui    [00]0x%02X,0x%02X\n",\
					epp->win_id, \
					pd[0], pd[1]);
					PE_NRD_HW_O26_CCO_DNR_WR01(reg_decon_ctrl_0,	reg_1st_out_rd_on,		GET_BITS(epp->data[0],0,1));
					#endif
				}
			}
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get dnr common ctrl - not used @O26
 * - use input struct LX_PE_NRD_DNR6_CMN_T
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_GetCCODcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT16 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_LED_DCNT_CMN_T *ctrl_param =(LX_PE_LED_DCNT_CMN_T *)pstParams;
			LX_PE_LED_DCNT2_CMN_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_LED_DCNT_O26_QRd02(reg_decon_ctrl_0,	reg_1st_out_rd_on,	pp->deconled____ui[0],\
																	reg_1st_out_rd_bit, pp->deconled____ui[1]);
					PE_LED_DCNT_O26_QRd02(reg_decon_ctrl_7,	reg_2nd_out_rd_on,	pp->deconled____ui[2],\
																	reg_2nd_out_rd_bit, pp->deconled____ui[3]);
					PE_LED_DCNT_O26_QRd01(reg_decon_ctrl_17,	reg_decon_1st_en,	pp->deconled____ui[4]);
					PE_LED_DCNT_O26_QRd01(reg_decon_ctrl_69,	reg_decon_2nd_en,	pp->deconled____ui[5]);
					PE_LED_DCNT_O26_QRd04(reg_decon_ctrl_19,reg_decon_diff_x_th3,	pp->deconled____ui[6],\
																reg_decon_diff_x_th2,	pp->deconled____ui[7],\
																reg_decon_diff_x_th1,	pp->deconled____ui[8],\
																reg_decon_diff_x_th0,	pp->deconled____ui[9]);
					PE_LED_DCNT_O26_QRd04(reg_decon_ctrl_20,reg_decon_diff_y_th3,	pp->deconled____ui[10],\
																reg_decon_diff_y_th2,	pp->deconled____ui[11],\
																reg_decon_diff_y_th1,	pp->deconled____ui[12],\
																reg_decon_diff_y_th0,	pp->deconled____ui[13]);

					pd = pp->deconled____ui;
					printk("set[%d] : deconled____ui\n"
					"deconled____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconled____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13]);
				}
			}
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set dnr detail ctrl  - not used @O26
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetCCODcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT16 *pd;
	UINT8  *pd8;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_CCO_DCNT_DETAIL_T *ctrl_param =(LX_PE_CCO_DCNT_DETAIL_T *)pstParams;
			LX_PE_CCO_DCNT1_DETAIL_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_CCO_DCNT1_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_CCO_DCNT1_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DEC("duplicated DB : LX_PE_CCO_DCNT1_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_DBG_DEC("set[%d] : oper:0x%02X, size: 0x%02X\n",\
					pp->win_id, \
					ctrl_param->oper, ctrl_param->size);
					pd = pp->deconcco___cmn;
					PE_DBG_DEC("set[%d] : deconnd____cmn\n"
					"deconled___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconled___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconled___cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconled___cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconled___cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconled___cmn    [50]0x%02X\n",\
					pp->win_id, \
					pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
					pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
					pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
					pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
					pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
					pd[50]);
					pd8 = pp->deconcco__face;
					PE_DBG_DEC("set[%d] : deconcco__face\n"
					"deconled___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"deconled___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id, \
					pd8[0], pd8[1], pd8[2], pd8[3], pd8[4], pd8[5], pd8[6], pd8[7], pd8[8], pd8[9],\
					pd8[10], pd8[11], pd8[12], pd8[13], pd8[14], pd8[15], pd8[16], pd8[17], pd8[18], pd8[19]);
					/*dnrcco_dcnt*/
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_18,	reg_var_cut_resolution, GET_BITS(pp->deconcco___cmn[0],0,4),\
																	reg_var_h_gain, 		GET_BITS(pp->deconcco___cmn[1],0,4),\
																	reg_var_chroma_en, 		GET_BITS(pp->deconcco___cmn[2],0,1));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_21,	reg_decon_var_x_th2, GET_BITS(pp->deconcco___cmn[5],0,10),\
																	reg_decon_var_x_th1, GET_BITS(pp->deconcco___cmn[4],0,10),\
																	reg_decon_var_x_th0, GET_BITS(pp->deconcco___cmn[3],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_22,	reg_decon_var_x_th3, GET_BITS(pp->deconcco___cmn[6],0,10),\
																	reg_decon_var_y_th0, GET_BITS(pp->deconcco___cmn[7],0,10),\
																	reg_decon_var_y_th1, GET_BITS(pp->deconcco___cmn[8],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_23,	reg_decon_var_y_th2, GET_BITS(pp->deconcco___cmn[9],0,10),\
																	reg_decon_var_y_th3, GET_BITS(pp->deconcco___cmn[10],0,10),\
																	reg_decon_luma_x_th0,GET_BITS(pp->deconcco___cmn[11],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_24,	reg_decon_luma_x_th1, GET_BITS(pp->deconcco___cmn[12],0,10),\
																	reg_decon_luma_x_th2, GET_BITS(pp->deconcco___cmn[13],0,10),\
																	reg_decon_luma_x_th3, GET_BITS(pp->deconcco___cmn[14],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_25,	reg_decon_luma_x_th4, GET_BITS(pp->deconcco___cmn[15],0,10),\
																	reg_decon_luma_x_th5, GET_BITS(pp->deconcco___cmn[16],0,10),\
																	reg_decon_luma_x_th6, GET_BITS(pp->deconcco___cmn[17],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_26,	reg_decon_luma_x_th7, GET_BITS(pp->deconcco___cmn[18],0,10),\
																	reg_decon_luma_y_th0, GET_BITS(pp->deconcco___cmn[19],0,10),\
																	reg_decon_luma_y_th1, GET_BITS(pp->deconcco___cmn[20],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_27,	reg_decon_luma_y_th2, GET_BITS(pp->deconcco___cmn[21],0,10),\
																	reg_decon_luma_y_th3, GET_BITS(pp->deconcco___cmn[22],0,10),\
																	reg_decon_luma_y_th4, GET_BITS(pp->deconcco___cmn[23],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_28,	reg_decon_luma_y_th5, GET_BITS(pp->deconcco___cmn[24],0,10),\
																	reg_decon_luma_y_th6, GET_BITS(pp->deconcco___cmn[25],0,10),\
																	reg_decon_luma_y_th7, GET_BITS(pp->deconcco___cmn[26],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_86,	reg_decon_low_var_x_th0, GET_BITS(pp->deconcco___cmn[27],0,10),\
																	reg_decon_low_var_x_th1, GET_BITS(pp->deconcco___cmn[28],0,10),\
																	reg_decon_low_var_x_th2, GET_BITS(pp->deconcco___cmn[29],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_87,	reg_decon_low_var_x_th3, GET_BITS(pp->deconcco___cmn[30],0,10),\
																	reg_decon_low_var_y_th0, GET_BITS(pp->deconcco___cmn[31],0,10),\
																	reg_decon_low_var_y_th1, GET_BITS(pp->deconcco___cmn[32],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_88,	reg_decon_low_var_y_th2 , GET_BITS(pp->deconcco___cmn[33],0,10),\
																	reg_decon_low_var_y_th3 , GET_BITS(pp->deconcco___cmn[34],0,10),\
																	reg_decon_low_luma_x_th0, GET_BITS(pp->deconcco___cmn[35],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_89,	reg_decon_low_luma_x_th1, GET_BITS(pp->deconcco___cmn[36],0,10),\
																	reg_decon_low_luma_x_th2, GET_BITS(pp->deconcco___cmn[37],0,10),\
																	reg_decon_low_luma_x_th3, GET_BITS(pp->deconcco___cmn[38],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_90,	reg_decon_low_luma_x_th4, GET_BITS(pp->deconcco___cmn[39],0,10),\
																	reg_decon_low_luma_x_th5, GET_BITS(pp->deconcco___cmn[40],0,10),\
																	reg_decon_low_luma_x_th6, GET_BITS(pp->deconcco___cmn[41],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_91,	reg_decon_low_luma_x_th7, GET_BITS(pp->deconcco___cmn[42],0,10),\
																	reg_decon_low_luma_y_th0, GET_BITS(pp->deconcco___cmn[43],0,10),\
																	reg_decon_low_luma_y_th1, GET_BITS(pp->deconcco___cmn[44],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_92,	reg_decon_low_luma_y_th2, GET_BITS(pp->deconcco___cmn[45],0,10),\
																	reg_decon_low_luma_y_th3, GET_BITS(pp->deconcco___cmn[46],0,10),\
																	reg_decon_low_luma_y_th4, GET_BITS(pp->deconcco___cmn[47],0,10));
					PE_NRD_HW_O26_CCO_DNR_WR03(reg_decon_ctrl_93,	reg_decon_low_luma_y_th5, GET_BITS(pp->deconcco___cmn[48],0,10),\
																	reg_decon_low_luma_y_th6, GET_BITS(pp->deconcco___cmn[49],0,10),\
																	reg_decon_low_luma_y_th7, GET_BITS(pp->deconcco___cmn[50],0,10));

					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_50,	reg_lut_skin_yy_x0, GET_BITS(pp->deconcco__face[0],0,8),\
																	reg_lut_skin_yy_x1, GET_BITS(pp->deconcco__face[1],0,8),\
																	reg_lut_skin_yy_x2, GET_BITS(pp->deconcco__face[2],0,8),\
																	reg_lut_skin_yy_x3, GET_BITS(pp->deconcco__face[3],0,8));
					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_51,	reg_lut_skin_cb_x0, GET_BITS(pp->deconcco__face[4],0,8),\
																	reg_lut_skin_cb_x1, GET_BITS(pp->deconcco__face[5],0,8),\
																	reg_lut_skin_cb_x2, GET_BITS(pp->deconcco__face[6],0,8),\
																	reg_lut_skin_cb_x3, GET_BITS(pp->deconcco__face[7],0,8));
					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_52,	reg_lut_skin_cr_x0, GET_BITS(pp->deconcco__face[8],0,8),\
																	reg_lut_skin_cr_x1, GET_BITS(pp->deconcco__face[9],0,8),\
																	reg_lut_skin_cr_x2, GET_BITS(pp->deconcco__face[10],0,8),\
																	reg_lut_skin_cr_x3, GET_BITS(pp->deconcco__face[11],0,8));
					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_53,	reg_lut_skin_y0, GET_BITS(pp->deconcco__face[12],0,8),\
																	reg_lut_skin_y1, GET_BITS(pp->deconcco__face[13],0,8),\
																	reg_lut_skin_y2, GET_BITS(pp->deconcco__face[14],0,8),\
																	reg_lut_skin_y3, GET_BITS(pp->deconcco__face[15],0,8));
					PE_NRD_HW_O26_CCO_DNR_WR04(reg_decon_ctrl_54,	reg_lut_face_x0, GET_BITS(pp->deconcco__face[16],0,8),\
																	reg_lut_face_x1, GET_BITS(pp->deconcco__face[17],0,8),\
																	reg_lut_face_x2, GET_BITS(pp->deconcco__face[18],0,8),\
																	reg_lut_face_x3, GET_BITS(pp->deconcco__face[19],0,8));
					
				}
			}
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * get dnr detail ctrl  - not used @O26
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_GetCCODcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT16 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_LED_DCNT_DETAIL_T *ctrl_param =(LX_PE_LED_DCNT_DETAIL_T *)pstParams;
			LX_PE_LED_DCNT2_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				if(ctrl_param->oper == LX_PE_PLATFORM_WEBOS)
				{
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_18,	reg_var_cut_resolution, pp->deconled___cmn[0],\
																reg_var_h_gain, 		pp->deconled___cmn[1],\
																reg_var_chroma_en,		pp->deconled___cmn[2]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_21,	reg_decon_var_x_th0,	pp->deconled___cmn[3],\
																reg_decon_var_x_th1,	pp->deconled___cmn[4],\
																reg_decon_var_x_th2,	pp->deconled___cmn[5]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_22,	reg_decon_var_x_th3,	pp->deconled___cmn[6],\
																reg_decon_var_y_th0,	pp->deconled___cmn[7],\
																reg_decon_var_y_th1,	pp->deconled___cmn[8]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_23,	reg_decon_var_y_th2,	pp->deconled___cmn[9],\
																reg_decon_var_y_th3,	pp->deconled___cmn[10],\
																reg_decon_luma_x_th0,	pp->deconled___cmn[11]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_24,	reg_decon_luma_x_th1,	pp->deconled___cmn[12],\
																reg_decon_luma_x_th2,	pp->deconled___cmn[13],\
																reg_decon_luma_x_th3,	pp->deconled___cmn[14]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_25,	reg_decon_luma_x_th4,	pp->deconled___cmn[15],\
																reg_decon_luma_x_th5,	pp->deconled___cmn[16],\
																reg_decon_luma_x_th6,	pp->deconled___cmn[17]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_26,	reg_decon_luma_x_th7,	pp->deconled___cmn[18],\
																reg_decon_luma_y_th0,	pp->deconled___cmn[19],\
																reg_decon_luma_y_th1,	pp->deconled___cmn[20]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_27,	reg_decon_luma_y_th2,	pp->deconled___cmn[21],\
																reg_decon_luma_y_th3,	pp->deconled___cmn[22],\
																reg_decon_luma_y_th4,	pp->deconled___cmn[23]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_28,	reg_decon_luma_y_th5,	pp->deconled___cmn[24],\
																reg_decon_luma_y_th6,	pp->deconled___cmn[25],\
																reg_decon_luma_y_th7,	pp->deconled___cmn[26]);
					PE_LED_DCNT_O26_QRd04(reg_decon_ctrl_69,	reg_2nd_var_chroma_en,	pp->deconled___cmn[27],\
																reg_2nd_var_cut_resolution, pp->deconled___cmn[28],\
																reg_2nd_var_h_gain, pp->deconled___cmn[29],\
																reg_2nd_var_v_gain, pp->deconled___cmn[30]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_70,	reg_2nd_luma_x_th0, pp->deconled___cmn[31],\
																reg_2nd_luma_x_th1, pp->deconled___cmn[32],\
																reg_2nd_luma_x_th2, pp->deconled___cmn[33]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_71,	reg_2nd_luma_x_th3, pp->deconled___cmn[34],\
																reg_2nd_luma_x_th4, pp->deconled___cmn[35],\
																reg_2nd_luma_x_th5, pp->deconled___cmn[36]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_72,	reg_2nd_luma_x_th6, pp->deconled___cmn[37],\
																reg_2nd_luma_x_th7, pp->deconled___cmn[38],\
																reg_2nd_luma_y_th0, pp->deconled___cmn[39]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_73,	reg_2nd_luma_y_th1, pp->deconled___cmn[40],\
																reg_2nd_luma_y_th2, pp->deconled___cmn[41],\
																reg_2nd_luma_y_th3, pp->deconled___cmn[42]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_74,	reg_2nd_luma_y_th4, pp->deconled___cmn[43],\
																reg_2nd_luma_y_th5, pp->deconled___cmn[44],\
																reg_2nd_luma_y_th6, pp->deconled___cmn[45]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_75,	reg_2nd_luma_y_th7, pp->deconled___cmn[46],\
																reg_2nd_var_x_th0,	pp->deconled___cmn[47],\
																reg_2nd_var_x_th1,	pp->deconled___cmn[48]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_76,	reg_2nd_var_x_th2,	pp->deconled___cmn[49],\
																reg_2nd_var_x_th3,	pp->deconled___cmn[50],\
																reg_2nd_var_y_th0,	pp->deconled___cmn[51]);
					PE_LED_DCNT_O26_QRd03(reg_decon_ctrl_77,	reg_2nd_var_y_th1,	pp->deconled___cmn[52],\
																reg_2nd_var_y_th2,	pp->deconled___cmn[53],\
																reg_2nd_var_y_th3,	pp->deconled___cmn[54]);
					PE_LED_DCNT_O26_QRd04(reg_decon_ctrl_78,	reg_2nd_diff_x_th3, pp->deconled___cmn[55],\
																reg_2nd_diff_x_th2, pp->deconled___cmn[56],\
																reg_2nd_diff_x_th1, pp->deconled___cmn[57],\
																reg_2nd_diff_x_th0, pp->deconled___cmn[58]);
					PE_LED_DCNT_O26_QRd04(reg_decon_ctrl_79,	reg_2nd_diff_y_th3, pp->deconled___cmn[59],\
																reg_2nd_diff_y_th2, pp->deconled___cmn[60],\
																reg_2nd_diff_y_th1, pp->deconled___cmn[61],\
																reg_2nd_diff_y_th0, pp->deconled___cmn[62]);
					pd = pp->deconled___cmn;
					printk("set[%d] : deconled___cmn\n"
						"deconled___cmn    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"deconled___cmn    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"deconled___cmn    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"deconled___cmn    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"deconled___cmn    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"deconled___cmn    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
						"deconled___cmn    [60]0x%02X,0x%02X,0x%02X,\n",\
						pp->win_id, \
						pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
						pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
						pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
						pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
						pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
						pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57], pd[58], pd[59],\
						pd[60], pd[61], pd[62]);
				}
			}
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl - this is temporal func. it will be changed PE_NRD_HW_O26_SetTnrCmnCtrl()
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnrFaceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 *pd = NULL;
	LX_PE_NRD_TNR_FACE_T *pp = NULL;
	static LX_PE_NRD_TNR_FACE_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			pp =(LX_PE_NRD_TNR_FACE_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR_FACE_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR_FACE_T\n");
				ret=RET_OK;
				break;
			}
			pd = pp->tnr0_face_gain;
			PE_DBG_NRD(\
			"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_66,		reg_face_gain_c_en,	GET_BITS(pp->tnr0_face_gain[0],0,1),\
															reg_face_gain_y_en,	GET_BITS(pp->tnr0_face_gain[1],0,1));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_67,		reg_face_gain_pts_y2,	GET_BITS(pp->tnr0_face_gain[2], 0,8),\
															reg_face_gain_pts_x2,	GET_BITS(pp->tnr0_face_gain[2], 8,8),\
															reg_face_gain_pts_y3,	GET_BITS(pp->tnr0_face_gain[2],16,8),\
															reg_face_gain_pts_x3,	GET_BITS(pp->tnr0_face_gain[2],24,8));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_68,		reg_face_gain_pts_y0,	GET_BITS(pp->tnr0_face_gain[3], 0,8),\
															reg_face_gain_pts_x0,	GET_BITS(pp->tnr0_face_gain[3], 8,8),\
															reg_face_gain_pts_y1,	GET_BITS(pp->tnr0_face_gain[3],16,8),\
															reg_face_gain_pts_x1,	GET_BITS(pp->tnr0_face_gain[3],24,8));
				
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set tnr common ctrl - will be removed after DB combined
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	const PE_REG_PARAM_T *p_db = NULL;
	PE_INF_O26_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	LX_PE_NRD_TNR_CMN_T *ctrl_param = NULL;
	LX_PE_NRD_TNR1_CMN_T *pp = NULL;
	UINT32 *pd = NULL;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	PE_TNL_HW_PARAM_REG_O26_T *p_tnl_dflt_b = _g_pe_tnl_hw_param_data_o26.reg_dflt.data;
	#define O26_TNL_DFT_B(_num)	(p_tnl_dflt_b->tnr_lut_##_num.main_lut_indir_data0)
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			ctrl_param =(LX_PE_NRD_TNR_CMN_T *)pstParams;
			pp = (typeof(*pp) *)ctrl_param->data;
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
			pd = pp->tnr0__lut;
			PE_DBG_NRD("[%d]tnr0___en:%d\n", pp->win_id, pp->tnr0___en);
			PE_DBG_NRD( \
			"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = pp->tnr0_gain;
			PE_DBG_NRD(\
			"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = pp->tnr0_buff;
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
					ret = PE_NRD_HW_O26_DownloadTnrUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadTnrUserDb() error.\n",__F__,__L__);
					PE_DBG_NRD("set tnr lut by firmware\n");
				}
				else
				{
					UINT32 *p_lut = pp->tnr0__lut;
					if (pp->tnr0___en == 3)					//high
					{
						p_db = tnr_l_lut_user_high_o26;
					}
					else if (pp->tnr0___en == 2 || pp->tnr0___en == 4)//medium, auto
					{
						p_db = tnr_l_lut_user_med_o26;
					}
					else if (pp->tnr0___en == 1)				//low
					{
						p_db = tnr_l_lut_user_low_o26;
					}
					else									//off
					{
						p_db = tnr_l_lut_user_off_o26;
					}
					CHECK_KNULL(p_db);
					ret = PE_INF_O26_GetCurInfSettings(&inf_set);
					PE_NRD_HW_O26_CHECK_CODE(ret,break,"[%s,%d] PE_INF_O26_GetCurInfSettings() error.\n",__F__,__L__);
					disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
					PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
					if (pp->tnr0___en==0)	//off
					{
						#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
						PE_NRD_HW_O26_TNL_WR32(00, p_db[0].data );// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
						PE_NRD_HW_O26_TNL_WR32(01, p_db[1].data );// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
						PE_NRD_HW_O26_TNL_WR32(02, p_db[2].data );// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
						PE_NRD_HW_O26_TNL_WR32(03, p_db[3].data );// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
						PE_NRD_HW_O26_TNL_WR32(04, p_db[4].data );// 04. x5y5 x4y4 reg_p2_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(05, p_db[5].data );// 05. x3y3 x2y2 reg_p2_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(06, p_db[6].data );// 06. x1y1 x0y0 reg_p2_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(07, p_lut[0]     );// 07. x7y7 x6y6 reg_detail_iir_pt
						PE_NRD_HW_O26_TNL_WR32(08, p_lut[1]     );// 08. x5y5 x4y4 reg_detail_iir_pt
						PE_NRD_HW_O26_TNL_WR32(09, p_lut[2]     );// 09. x3y3 x2y2 reg_detail_iir_pt
						PE_NRD_HW_O26_TNL_WR32(10, p_lut[3]     );// 10. x1y1 x0y0 reg_detail_iir_pt
						PE_NRD_HW_O26_TNL_WR32(11, p_lut[4]     );// 11. x7y7 x6y6 reg_detail_cir_pt
						PE_NRD_HW_O26_TNL_WR32(12, p_lut[5]     );// 12. x5y5 x4y4 reg_detail_cir_pt
						PE_NRD_HW_O26_TNL_WR32(13, p_lut[6]     );// 13. x3y3 x2y2 reg_detail_cir_pt
						PE_NRD_HW_O26_TNL_WR32(14, p_lut[7]     );// 14. x1y1 x0y0 reg_detail_cir_pt
						PE_NRD_HW_O26_TNL_WR32(15, p_lut[8]     );// 15. x7y7 x6y6 reg_flat_iir_pt
						PE_NRD_HW_O26_TNL_WR32(16, p_lut[9]     );// 16. x5y5 x4y4 reg_flat_iir_pt
						PE_NRD_HW_O26_TNL_WR32(17, p_lut[10]    );// 17. x3y3 x2y2 reg_flat_iir_pt
						PE_NRD_HW_O26_TNL_WR32(18, p_lut[11]    );// 18. x1y1 x0y0 reg_flat_iir_pt
						PE_NRD_HW_O26_TNL_WR32(19, p_lut[12]    );// 19. x7y7 x6y6 reg_flat_cir_pt
						PE_NRD_HW_O26_TNL_WR32(20, p_lut[13]    );// 20. x5y5 x4y4 reg_flat_cir_pt
						PE_NRD_HW_O26_TNL_WR32(21, p_lut[14]    );// 21. x3y3 x2y2 reg_flat_cir_pt
						PE_NRD_HW_O26_TNL_WR32(22, p_lut[15]    );// 22. x1y1 x0y0 reg_flat_cir_pt
						PE_NRD_HW_O26_TNL_WR32(23, p_db[23].data);// 23. x1y1 x0y0 reg_luma_gain_ctrl
						PE_NRD_HW_O26_TNL_WR32(24, p_db[24].data);// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
						PE_NRD_HW_O26_TNL_WR32(25, p_db[25].data);// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
						PE_NRD_HW_O26_TNL_WR32(26, p_db[26].data);// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
						PE_NRD_HW_O26_TNL_WR32(27, p_db[27].data);// 27. x1y1 x0y0 reg_skin_motion_ctrl
						PE_NRD_HW_O26_TNL_WR32(28, p_db[28].data);// 28. reg_detail_luma_ctrl
						PE_NRD_HW_O26_TNL_WR32(29, p_db[29].data);// 29. x3y3 x2y2 reg_NLM_Protect
						PE_NRD_HW_O26_TNL_WR32(30, p_db[30].data);// 30. x1y1 x0y0 reg_NLM_Protect
						PE_NRD_HW_O26_TNL_WR32(31, p_db[31].data);// 31. x5y5 x4y4 reg_cc_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(32, p_db[32].data);// 32. x3y3 x2y2 reg_cc_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(33, p_db[33].data);// 33. x1y1 x0y0 reg_cc_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(34, p_db[34].data);// 34. x5y5 x4y4 reg_ne_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(35, p_db[35].data);// 35. x3y3 x2y2 reg_ne_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(36, p_db[36].data);// 36. x1y1 x0y0 reg_ne_dist_max_pt
						PE_NRD_HW_O26_TNL_WR32(37, p_db[37].data);// 37. eg_skin_gain_ctrl_yy
						PE_NRD_HW_O26_TNL_WR32(38, p_db[38].data);// 38. eg_skin_gain_ctrl_cb
						PE_NRD_HW_O26_TNL_WR32(39, p_db[39].data);// 39. eg_skin_gain_ctrl_cr
						PE_NRD_HW_O26_TNL_WR32(40, p_db[40].data);// 40. eg_skin_motion_ctrl
						PE_NRD_HW_O26_TNL_WR32(41, p_db[41].data);// 41. x7y7 x6y6 reg_simple_ma_iir_pt
						PE_NRD_HW_O26_TNL_WR32(42, p_db[42].data);// 42. x5y5 x4y4 reg_simple_ma_iir_pt
						PE_NRD_HW_O26_TNL_WR32(43, p_db[43].data);// 43. x3y3 x2y2 reg_simple_ma_iir_pt
						PE_NRD_HW_O26_TNL_WR32(44, p_db[44].data);// 44. x1y1 x0y0 reg_simple_ma_iir_pt
						#else						
						PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001000);
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[0].data );// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[1].data );// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[2].data );// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[3].data );// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[4].data );// 04. x5y5 x4y4 reg_p2_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[5].data );// 05. x3y3 x2y2 reg_p2_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[6].data );// 06. x1y1 x0y0 reg_p2_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[0]     );// 07. x7y7 x6y6 reg_detail_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[1]     );// 08. x5y5 x4y4 reg_detail_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[2]     );// 09. x3y3 x2y2 reg_detail_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[3]     );// 10. x1y1 x0y0 reg_detail_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[4]     );// 11. x7y7 x6y6 reg_detail_cir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[5]     );// 12. x5y5 x4y4 reg_detail_cir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[6]     );// 13. x3y3 x2y2 reg_detail_cir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[7]     );// 14. x1y1 x0y0 reg_detail_cir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[8]     );// 15. x7y7 x6y6 reg_flat_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[9]     );// 16. x5y5 x4y4 reg_flat_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[10]    );// 17. x3y3 x2y2 reg_flat_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[11]    );// 18. x1y1 x0y0 reg_flat_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[12]    );// 19. x7y7 x6y6 reg_flat_cir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[13]    );// 20. x5y5 x4y4 reg_flat_cir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[14]    );// 21. x3y3 x2y2 reg_flat_cir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[15]    );// 22. x1y1 x0y0 reg_flat_cir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[23].data);// 23. x1y1 x0y0 reg_luma_gain_ctrl
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[24].data);// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[25].data);// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[26].data);// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[27].data);// 27. x1y1 x0y0 reg_skin_motion_ctrl
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[28].data);// 28. reg_detail_luma_ctrl
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[29].data);// 29. x3y3 x2y2 reg_NLM_Protect
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[30].data);// 30. x1y1 x0y0 reg_NLM_Protect
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[31].data);// 31. x5y5 x4y4 reg_cc_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[32].data);// 32. x3y3 x2y2 reg_cc_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[33].data);// 33. x1y1 x0y0 reg_cc_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[34].data);// 34. x5y5 x4y4 reg_ne_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[35].data);// 35. x3y3 x2y2 reg_ne_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[36].data);// 36. x1y1 x0y0 reg_ne_dist_max_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[37].data);// 37. eg_skin_gain_ctrl_yy
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[38].data);// 38. eg_skin_gain_ctrl_cb
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[39].data);// 39. eg_skin_gain_ctrl_cr
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[40].data);// 40. eg_skin_motion_ctrl
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[41].data);// 41. x7y7 x6y6 reg_simple_ma_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[42].data);// 42. x5y5 x4y4 reg_simple_ma_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[43].data);// 43. x3y3 x2y2 reg_simple_ma_iir_pt
						PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[44].data);// 44. x1y1 x0y0 reg_simple_ma_iir_pt
						#endif
					}
					else
					{
						if(disp0_inf->src_type==LX_PE_SRC_DTV && \
							disp0_inf->fmt_type==LX_PE_FMT_HD && \
							disp0_inf->dtv_type==LX_PE_DTV_CAMERA)
						{
							#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
							PE_NRD_HW_O26_TNL_WR32(00, O26_TNL_DFT_B(00));// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
							PE_NRD_HW_O26_TNL_WR32(01, O26_TNL_DFT_B(01));// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
							PE_NRD_HW_O26_TNL_WR32(02, O26_TNL_DFT_B(02));// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
							PE_NRD_HW_O26_TNL_WR32(03, O26_TNL_DFT_B(03));// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
							PE_NRD_HW_O26_TNL_WR32(04, O26_TNL_DFT_B(04));// 04. x5y5 x4y4 reg_p2_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(05, O26_TNL_DFT_B(05));// 05. x3y3 x2y2 reg_p2_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(06, O26_TNL_DFT_B(06));// 06. x1y1 x0y0 reg_p2_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(07, O26_TNL_DFT_B(07));// 07. x7y7 x6y6 reg_detail_iir_pt
							PE_NRD_HW_O26_TNL_WR32(08, O26_TNL_DFT_B(08));// 08. x5y5 x4y4 reg_detail_iir_pt
							PE_NRD_HW_O26_TNL_WR32(09, O26_TNL_DFT_B(09));// 09. x3y3 x2y2 reg_detail_iir_pt
							PE_NRD_HW_O26_TNL_WR32(10, O26_TNL_DFT_B(10));// 10. x1y1 x0y0 reg_detail_iir_pt
							PE_NRD_HW_O26_TNL_WR32(11, O26_TNL_DFT_B(11));// 11. x7y7 x6y6 reg_detail_cir_pt
							PE_NRD_HW_O26_TNL_WR32(12, O26_TNL_DFT_B(12));// 12. x5y5 x4y4 reg_detail_cir_pt
							PE_NRD_HW_O26_TNL_WR32(13, O26_TNL_DFT_B(13));// 13. x3y3 x2y2 reg_detail_cir_pt
							PE_NRD_HW_O26_TNL_WR32(14, O26_TNL_DFT_B(14));// 14. x1y1 x0y0 reg_detail_cir_pt
							PE_NRD_HW_O26_TNL_WR32(15, O26_TNL_DFT_B(15));// 15. x7y7 x6y6 reg_flat_iir_pt
							PE_NRD_HW_O26_TNL_WR32(16, O26_TNL_DFT_B(16));// 16. x5y5 x4y4 reg_flat_iir_pt
							PE_NRD_HW_O26_TNL_WR32(17, O26_TNL_DFT_B(17));// 17. x3y3 x2y2 reg_flat_iir_pt
							PE_NRD_HW_O26_TNL_WR32(18, O26_TNL_DFT_B(18));// 18. x1y1 x0y0 reg_flat_iir_pt
							PE_NRD_HW_O26_TNL_WR32(19, O26_TNL_DFT_B(19));// 19. x7y7 x6y6 reg_flat_cir_pt
							PE_NRD_HW_O26_TNL_WR32(20, O26_TNL_DFT_B(20));// 20. x5y5 x4y4 reg_flat_cir_pt
							PE_NRD_HW_O26_TNL_WR32(21, O26_TNL_DFT_B(21));// 21. x3y3 x2y2 reg_flat_cir_pt
							PE_NRD_HW_O26_TNL_WR32(22, O26_TNL_DFT_B(22));// 22. x1y1 x0y0 reg_flat_cir_pt
							PE_NRD_HW_O26_TNL_WR32(23, O26_TNL_DFT_B(23));// 23. x1y1 x0y0 reg_luma_gain_ctrl
							PE_NRD_HW_O26_TNL_WR32(24, O26_TNL_DFT_B(24));// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
							PE_NRD_HW_O26_TNL_WR32(25, O26_TNL_DFT_B(25));// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
							PE_NRD_HW_O26_TNL_WR32(26, O26_TNL_DFT_B(26));// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
							PE_NRD_HW_O26_TNL_WR32(27, O26_TNL_DFT_B(27));// 27. x1y1 x0y0 reg_skin_motion_ctrl
							PE_NRD_HW_O26_TNL_WR32(28, O26_TNL_DFT_B(28));// 28. reg_detail_luma_ctrl
							PE_NRD_HW_O26_TNL_WR32(29, O26_TNL_DFT_B(29));// 29. x3y3 x2y2 reg_NLM_Protect
							PE_NRD_HW_O26_TNL_WR32(30, O26_TNL_DFT_B(30));// 30. x1y1 x0y0 reg_NLM_Protect
							PE_NRD_HW_O26_TNL_WR32(31, O26_TNL_DFT_B(31));// 31. x5y5 x4y4 reg_cc_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(32, O26_TNL_DFT_B(32));// 32. x3y3 x2y2 reg_cc_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(33, O26_TNL_DFT_B(33));// 33. x1y1 x0y0 reg_cc_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(34, O26_TNL_DFT_B(34));// 34. x5y5 x4y4 reg_ne_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(35, O26_TNL_DFT_B(35));// 35. x3y3 x2y2 reg_ne_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(36, O26_TNL_DFT_B(36));// 36. x1y1 x0y0 reg_ne_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(37, O26_TNL_DFT_B(37));// 37. eg_skin_gain_ctrl_yy
							PE_NRD_HW_O26_TNL_WR32(38, O26_TNL_DFT_B(38));// 38. eg_skin_gain_ctrl_cb
							PE_NRD_HW_O26_TNL_WR32(39, O26_TNL_DFT_B(39));// 39. eg_skin_gain_ctrl_cr
							PE_NRD_HW_O26_TNL_WR32(40, O26_TNL_DFT_B(40));// 40. eg_skin_motion_ctrl
							PE_NRD_HW_O26_TNL_WR32(41, p_db[41].data  );// 41. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_NRD_HW_O26_TNL_WR32(42, p_db[42].data  );// 42. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_NRD_HW_O26_TNL_WR32(43, p_db[43].data  );// 43. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_NRD_HW_O26_TNL_WR32(44, p_db[44].data  );// 44. x1y1 x0y0 reg_simple_ma_iir_pt
							#else
							//PE_ND0_O26_QWr01(tnr_main_lut_00, main_lut_indir_addr, 0x29  );//41
							PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001029);
							PE_ND0_O26_QWr(tnr_main_lut_01, p_db[41].data  );// 39. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01, p_db[42].data  );// 40. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01, p_db[43].data  );// 41. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01, p_db[44].data  );// 42. x1y1 x0y0 reg_simple_ma_iir_pt
							#endif
						}
						else
						{
							#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
							PE_NRD_HW_O26_TNL_WR32(00, O26_TNL_DFT_B(00));// 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
							PE_NRD_HW_O26_TNL_WR32(01, O26_TNL_DFT_B(01));// 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
							PE_NRD_HW_O26_TNL_WR32(02, O26_TNL_DFT_B(02));// 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
							PE_NRD_HW_O26_TNL_WR32(03, O26_TNL_DFT_B(03));// 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
							PE_NRD_HW_O26_TNL_WR32(04, O26_TNL_DFT_B(04));// 04. x5y5 x4y4 reg_p2_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(05, O26_TNL_DFT_B(05));// 05. x3y3 x2y2 reg_p2_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(06, O26_TNL_DFT_B(06));// 06. x1y1 x0y0 reg_p2_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(07, p_lut[0]       );// 07. x7y7 x6y6 reg_detail_iir_pt
							PE_NRD_HW_O26_TNL_WR32(08, p_lut[1]       );// 08. x5y5 x4y4 reg_detail_iir_pt
							PE_NRD_HW_O26_TNL_WR32(09, p_lut[2]       );// 09. x3y3 x2y2 reg_detail_iir_pt
							PE_NRD_HW_O26_TNL_WR32(10, p_lut[3]       );// 10. x1y1 x0y0 reg_detail_iir_pt
							PE_NRD_HW_O26_TNL_WR32(11, p_lut[4]       );// 11. x7y7 x6y6 reg_detail_cir_pt
							PE_NRD_HW_O26_TNL_WR32(12, p_lut[5]       );// 12. x5y5 x4y4 reg_detail_cir_pt
							PE_NRD_HW_O26_TNL_WR32(13, p_lut[6]       );// 13. x3y3 x2y2 reg_detail_cir_pt
							PE_NRD_HW_O26_TNL_WR32(14, p_lut[7]       );// 14. x1y1 x0y0 reg_detail_cir_pt
							PE_NRD_HW_O26_TNL_WR32(15, p_lut[8]       );// 15. x7y7 x6y6 reg_flat_iir_pt
							PE_NRD_HW_O26_TNL_WR32(16, p_lut[9]       );// 16. x5y5 x4y4 reg_flat_iir_pt
							PE_NRD_HW_O26_TNL_WR32(17, p_lut[10]      );// 17. x3y3 x2y2 reg_flat_iir_pt
							PE_NRD_HW_O26_TNL_WR32(18, p_lut[11]      );// 18. x1y1 x0y0 reg_flat_iir_pt
							PE_NRD_HW_O26_TNL_WR32(19, p_lut[12]      );// 19. x7y7 x6y6 reg_flat_cir_pt
							PE_NRD_HW_O26_TNL_WR32(20, p_lut[13]      );// 20. x5y5 x4y4 reg_flat_cir_pt
							PE_NRD_HW_O26_TNL_WR32(21, p_lut[14]      );// 21. x3y3 x2y2 reg_flat_cir_pt
							PE_NRD_HW_O26_TNL_WR32(22, p_lut[15]      );// 22. x1y1 x0y0 reg_flat_cir_pt
							PE_NRD_HW_O26_TNL_WR32(23, O26_TNL_DFT_B(23));// 23. x1y1 x0y0 reg_luma_gain_ctrl
							PE_NRD_HW_O26_TNL_WR32(24, O26_TNL_DFT_B(24));// 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
							PE_NRD_HW_O26_TNL_WR32(25, O26_TNL_DFT_B(25));// 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
							PE_NRD_HW_O26_TNL_WR32(26, O26_TNL_DFT_B(26));// 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
							PE_NRD_HW_O26_TNL_WR32(27, O26_TNL_DFT_B(27));// 27. x1y1 x0y0 reg_skin_motion_ctrl
							PE_NRD_HW_O26_TNL_WR32(28, O26_TNL_DFT_B(28));// 28. reg_detail_luma_ctrl
							PE_NRD_HW_O26_TNL_WR32(29, O26_TNL_DFT_B(29));// 29. x3y3 x2y2 reg_NLM_Protect
							PE_NRD_HW_O26_TNL_WR32(30, O26_TNL_DFT_B(30));// 30. x1y1 x0y0 reg_NLM_Protect
							PE_NRD_HW_O26_TNL_WR32(31, O26_TNL_DFT_B(31));// 31. x5y5 x4y4 reg_cc_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(32, O26_TNL_DFT_B(32));// 32. x3y3 x2y2 reg_cc_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(33, O26_TNL_DFT_B(33));// 33. x1y1 x0y0 reg_cc_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(34, O26_TNL_DFT_B(34));// 34. x5y5 x4y4 reg_ne_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(35, O26_TNL_DFT_B(35));// 35. x3y3 x2y2 reg_ne_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(36, O26_TNL_DFT_B(36));// 36. x1y1 x0y0 reg_ne_dist_max_pt
							PE_NRD_HW_O26_TNL_WR32(37, O26_TNL_DFT_B(37));// 37. eg_skin_gain_ctrl_yy
							PE_NRD_HW_O26_TNL_WR32(38, O26_TNL_DFT_B(38));// 38. eg_skin_gain_ctrl_cb
							PE_NRD_HW_O26_TNL_WR32(39, O26_TNL_DFT_B(39));// 39. eg_skin_gain_ctrl_cr
							PE_NRD_HW_O26_TNL_WR32(40, O26_TNL_DFT_B(40));// 40. eg_skin_motion_ctrl
							PE_NRD_HW_O26_TNL_WR32(41, p_db[41].data  );// 41. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_NRD_HW_O26_TNL_WR32(42, p_db[42].data  );// 42. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_NRD_HW_O26_TNL_WR32(43, p_db[43].data  );// 43. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_NRD_HW_O26_TNL_WR32(44, p_db[44].data  );// 44. x1y1 x0y0 reg_simple_ma_iir_pt
							#else
							//PE_ND0_O26_QWr01(tnr_main_lut_00, main_lut_indir_addr, 0x7  );//0x7
							PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001007);
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[0]       );// 07. x7y7 x6y6 reg_detail_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[1]       );// 08. x5y5 x4y4 reg_detail_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[2]       );// 09. x3y3 x2y2 reg_detail_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[3]       );// 10. x1y1 x0y0 reg_detail_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[4]       );// 11. x7y7 x6y6 reg_detail_cir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[5]       );// 12. x5y5 x4y4 reg_detail_cir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[6]       );// 13. x3y3 x2y2 reg_detail_cir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[7]       );// 14. x1y1 x0y0 reg_detail_cir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[8]       );// 15. x7y7 x6y6 reg_flat_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[9]       );// 16. x5y5 x4y4 reg_flat_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[10]      );// 17. x3y3 x2y2 reg_flat_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[11]      );// 18. x1y1 x0y0 reg_flat_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[12]      );// 19. x7y7 x6y6 reg_flat_cir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[13]      );// 20. x5y5 x4y4 reg_flat_cir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[14]      );// 21. x3y3 x2y2 reg_flat_cir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_lut[15]      );// 22. x1y1 x0y0 reg_flat_cir_pt
							//PE_ND0_O26_QWr01(tnr_main_lut_00, main_lut_indir_addr, 0x29  );//41
							PE_ND0_O26_QWr(tnr_main_lut_00, 0x00001029);
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[41].data  );// 39. x7y7 x6y6 reg_simple_ma_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[42].data  );// 40. x5y5 x4y4 reg_simple_ma_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[43].data  );// 41. x3y3 x2y2 reg_simple_ma_iir_pt
							PE_ND0_O26_QWr(tnr_main_lut_01,  p_db[44].data  );// 42. x1y1 x0y0 reg_simple_ma_iir_pt
							#endif
						}
					}
					PE_ND0_O26_QWr(tnr_main_lut_00, 0x00008000);
					/* save prev values */
					memcpy(&(pInfo->tnr0_cmn), pp, sizeof(LX_PE_NRD_TNR1_CMN_T));
					/* download tnr user db */
					ret = PE_NRD_HW_O26_DownloadTnrUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadTnrUserDb() error.\n",__F__,__L__);
					PE_DBG_NRD("set tnr lut by driver\n");
				}
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR_CMN_T *ctrl_param =(LX_PE_NRD_TNR_CMN_T *)pstParams;
			LX_PE_NRD_TNR1_CMN_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				memcpy(pp, &(pInfo->tnr0_cmn), sizeof(LX_PE_NRD_TNR1_CMN_T));
			}
			UINT32 *pd = pp->tnr0__lut;
			printk("[%d]tnr0___en:%d\n", pp->win_id, pp->tnr0___en);
			printk( \
			"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = pp->tnr0_gain;
			printk(\
			"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = pp->tnr0_buff;
			printk(\
			"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],	pd[12], pd[13], pd[14]);
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR7_DETAIL_T O26
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	LX_PE_NRD_TNR_DETAIL_T *ctrl_param;
	LX_PE_NRD_TNR2_DETAIL_T *pp;
	static LX_PE_NRD_TNR2_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			ctrl_param =(LX_PE_NRD_TNR_DETAIL_T *)pstParams;
			pp = (typeof(*pp) *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR2_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR2_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			pd = pp->tnr0__ctl;
			PE_DBG_NRD("set[%d] : tnr0__ctl\n"
			"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__ctl	  [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);

			pd = pp->tnr0___ma;
			PE_DBG_NRD("set[%d] : tnr0___ma\n"
			"tnr0___ma    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			
			pd = pp->tnr0___me;
			PE_DBG_NRD("set[%d] : tnr0___me\n"
			"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->tnr0__mlb;
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

			pd = pp->tnr0_blnd;
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
				PE_ND0_O26_QWr04(nd_fsw_ctrl_03,			reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr0__ctl[0],0,8),\
															reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr0__ctl[1],0,1),\
															reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr0__ctl[2],0,1),\
															reg_sad_8x3_res,		GET_BITS(pp->tnr0__ctl[3],0,2));
				PE_NRD_HW_O26_TNR0_SET_USER(tnr_ctrl_22,	reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr0__ctl[0],0,8));
				PE_NRD_HW_O26_TNR0_SET_USER(tnr_ctrl_22,	reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr0__ctl[1],0,1));
				PE_NRD_HW_O26_TNR0_SET_USER(tnr_ctrl_22,	reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr0__ctl[2],0,1));
				PE_NRD_HW_O26_TNR0_SET_USER(tnr_ctrl_22,	reg_sad_8x3_res,		GET_BITS(pp->tnr0__ctl[3],0,2));
				PE_NRD_HW_O26_TNR0_WR10(tnr_ctrl_02,		sc_th_memc, GET_BITS(pp->tnr0__ctl[4],0,8),\
															sc_th_ma,	GET_BITS(pp->tnr0__ctl[5],0,8),\
															sc_out_mode,	GET_BITS(pp->tnr0__ctl[6],0,1),\
															sc_chroma_gain, GET_BITS(pp->tnr0__ctl[7],0,3),\
															sc_max_flt_tap, GET_BITS(pp->tnr0__ctl[8],0,3),\
															sc_scale,	GET_BITS(pp->tnr0__ctl[9],0,3),\
															sc_chroma_en,	GET_BITS(pp->tnr0__ctl[10],0,1),\
															sc_calc_prev_hist,	GET_BITS(pp->tnr0__ctl[11],0,1),\
															sc_max_flt_en,	GET_BITS(pp->tnr0__ctl[12],0,1),\
															sc_en,	GET_BITS(pp->tnr0__ctl[13],0,1));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_05,		reg_mamc_mc_sad_cut,	GET_BITS(pp->tnr0__ctl[14],0,1),\
															reg_mamc_ma_sad_cut,	GET_BITS(pp->tnr0__ctl[15],0,1),\
															reg_mamc_blend_mv_max_or_sum,	GET_BITS(pp->tnr0__ctl[16],0,1),\
															reg_mamc_blend_mode,	GET_BITS(pp->tnr0__ctl[17],0,2));
				PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_06,		reg_me_pv_base, GET_BITS(pp->tnr0__ctl[18],0,8),\
															reg_me_lb_base, GET_BITS(pp->tnr0__ctl[19],0,8));
				PE_NRD_HW_O26_TNR0_WR01(tnr_ctrl_21,		reg_svar_scale, GET_BITS(pp->tnr0__ctl[20],0,3));
				/*tnr0___ma*/
				PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_07,		reg_sc_en,	GET_BITS(pp->tnr0___ma[0],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr0___ma[1],0,2));
				/*tnr0___me*/
				PE_NRD_HW_O26_TNR0_WR03(tnr_ctrl_09,		reg_pv_smooth_clip, GET_BITS(pp->tnr0___me[0],0,6),\
															reg_lb_smooth_clip, GET_BITS(pp->tnr0___me[1],0,6),\
															reg_sad_base,	GET_BITS(pp->tnr0___me[2],0,7));
				PE_NRD_HW_O26_TNR0_WR03(tnr_ctrl_11,		reg_me_n15_protection,	GET_BITS(pp->tnr0___me[3],0,1),\
															pv_smooth_en,	GET_BITS(pp->tnr0___me[4],0,1),\
															lb_smooth_en,	GET_BITS(pp->tnr0___me[5],0,1));
				PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_13,		reg_zero_sad_adv,	GET_BITS(pp->tnr0___me[6],0,1),\
															reg_zero_sad_ratio, GET_BITS(pp->tnr0___me[7],0,8));

				/*tnr0__mlb*/
				PE_NRD_HW_O26_TNR0_WR01(tnr_ctrl_16,	reg_sad_acc_mode,	GET_BITS(pp->tnr0__mlb[0],0,2));
				PE_NRD_HW_O26_TNR0_WR09(tnr_ctrl_18,	reg_bmv_pmv_tl_en,	GET_BITS(pp->tnr0__mlb[1],0,1),\
														reg_bmv_pmv_tl, 	GET_BITS(pp->tnr0__mlb[2],0,7),\
														reg_bmv_gmv_tl_en,	GET_BITS(pp->tnr0__mlb[3],0,1),\
														reg_bmv_gmv_tl, 	GET_BITS(pp->tnr0__mlb[4],0,7),\
														reg_gmv_gmv_tl_en,	GET_BITS(pp->tnr0__mlb[5],0,1),\
														reg_gmv_gmv_tl,		GET_BITS(pp->tnr0__mlb[6],0,7),\
														reg_gsad_scale,		GET_BITS(pp->tnr0__mlb[7],0,3),\
														reg_bmv_rst_mode,   GET_BITS(pp->tnr0__mlb[8],0,1),\
														reg_bsad_scale,		GET_BITS(pp->tnr0__mlb[9],0,3));
				PE_NRD_HW_O26_TNR0_WR05(tnr_ctrl_19,	bmv_0mv_tl_en,		GET_BITS(pp->tnr0__mlb[10],0,1),\
														bmv_0mv_tl,			GET_BITS(pp->tnr0__mlb[11],0,7),\
														gmv_0mv_tl_en,		GET_BITS(pp->tnr0__mlb[12],0,1),\
														gmv_0mv_tl,			GET_BITS(pp->tnr0__mlb[13],0,7),\
														bmv_coring_th,		GET_BITS(pp->tnr0__mlb[14],0,8));

				/*tnr0__mc*/
				PE_NRD_HW_O26_TNR0_WR09(tnr_ctrl_24,		reg_chroma_sad_en,	GET_BITS(pp->tnr0___mc[0],0,1),\
															reg_cnt_mode,	GET_BITS(pp->tnr0___mc[1],0,3),\
															reg_avg_cmp_res,	GET_BITS(pp->tnr0___mc[2],0,3),\
															reg_avg_cmp_en, GET_BITS(pp->tnr0___mc[3],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr0___mc[4],0,2),\
															reg_chroma_sad_res, GET_BITS(pp->tnr0___mc[5],0,2),\
															reg_crgn_gain_en,	GET_BITS(pp->tnr0___mc[6],0,1),\
															reg_luma_gain_en,	GET_BITS(pp->tnr0___mc[7],0,1),\
															reg_ombc_en,	GET_BITS(pp->tnr0___mc[8],0,1));
				PE_NRD_HW_O26_TNR0_WR03(tnr_ctrl_26,		reg_tnr_final_lut_yy_x3,	GET_BITS(pp->tnr0___mc[9],0,10),\
															reg_tnr_final_lut_yy_y3,	GET_BITS(pp->tnr0___mc[10],0,10),\
															reg_tnr_final_lut_yy_x2,	GET_BITS(pp->tnr0___mc[11],0,10));
				PE_NRD_HW_O26_TNR0_WR03(tnr_ctrl_27,		reg_tnr_final_lut_yy_y2,	GET_BITS(pp->tnr0___mc[12],0,10),\
															reg_tnr_final_lut_yy_x1,	GET_BITS(pp->tnr0___mc[13],0,10),\
															reg_tnr_final_lut_yy_y1,	GET_BITS(pp->tnr0___mc[14],0,10));
				PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_28,		reg_tnr_final_lut_yy_x0,	GET_BITS(pp->tnr0___mc[15],0,10),\
															reg_tnr_final_lut_yy_y0,	GET_BITS(pp->tnr0___mc[16],0,10));
				PE_NRD_HW_O26_TNR0_WR03(tnr_ctrl_29,		reg_tnr_final_lut_cb_x3,	GET_BITS(pp->tnr0___mc[17],0,10),\
															reg_tnr_final_lut_cb_y3,	GET_BITS(pp->tnr0___mc[18],0,10),\
															reg_tnr_final_lut_cb_x2,	GET_BITS(pp->tnr0___mc[19],0,10));
				PE_NRD_HW_O26_TNR0_WR03(tnr_ctrl_30,		reg_tnr_final_lut_cb_y2,	GET_BITS(pp->tnr0___mc[20],0,10),\
															reg_tnr_final_lut_cb_x1,	GET_BITS(pp->tnr0___mc[21],0,10),\
															reg_tnr_final_lut_cb_y1,	GET_BITS(pp->tnr0___mc[22],0,10));
				PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_31,		reg_tnr_final_lut_cb_x0,	GET_BITS(pp->tnr0___mc[23],0,10),\
															reg_tnr_final_lut_cb_y0,	GET_BITS(pp->tnr0___mc[24],0,10));
				PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_32,		reg_blur_coef,	GET_BITS(pp->tnr0___mc[25],0,8),\
															reg_gf_gain,	GET_BITS(pp->tnr0___mc[26],0,8));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_33,		reg_move_step,	GET_BITS(pp->tnr0___mc[27],0,8),\
															reg_same_sad_th,	GET_BITS(pp->tnr0___mc[28],0,8),\
															reg_p_mv0_only, GET_BITS(pp->tnr0___mc[29],0,1),\
															same_protection_en, GET_BITS(pp->tnr0___mc[30],0,1));

				/*tnr0_blnd*/

				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_56,		reg_sad_mc_ctrl_pt_x1,	GET_BITS(pp->tnr0_blnd[0],0,8),\
															reg_sad_mc_ctrl_pt_y1,	GET_BITS(pp->tnr0_blnd[1],0,8),\
															reg_sad_mc_ctrl_pt_x0,	GET_BITS(pp->tnr0_blnd[2],0,8),\
															reg_sad_mc_ctrl_pt_y0,	GET_BITS(pp->tnr0_blnd[3],0,8));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_57,		reg_sad_mc_ctrl_pt_x3,	GET_BITS(pp->tnr0_blnd[4],0,8),\
															reg_sad_mc_ctrl_pt_y3,	GET_BITS(pp->tnr0_blnd[5],0,8),\
															reg_sad_mc_ctrl_pt_x2,	GET_BITS(pp->tnr0_blnd[6],0,8),\
															reg_sad_mc_ctrl_pt_y2,	GET_BITS(pp->tnr0_blnd[7],0,8));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_58,		reg_abs_mv_ctrl_pt_x1,	GET_BITS(pp->tnr0_blnd[8],0,8),\
															reg_abs_mv_ctrl_pt_y1,	GET_BITS(pp->tnr0_blnd[9],0,8),\
															reg_abs_mv_ctrl_pt_x0,	GET_BITS(pp->tnr0_blnd[10],0,8),\
															reg_abs_mv_ctrl_pt_y0,	GET_BITS(pp->tnr0_blnd[11],0,8));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_59,		reg_abs_mv_ctrl_pt_x3,	GET_BITS(pp->tnr0_blnd[12],0,8),\
															reg_abs_mv_ctrl_pt_y3,	GET_BITS(pp->tnr0_blnd[13],0,8),\
															reg_abs_mv_ctrl_pt_x2,	GET_BITS(pp->tnr0_blnd[14],0,8),\
															reg_abs_mv_ctrl_pt_y2,	GET_BITS(pp->tnr0_blnd[15],0,8));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_60,		reg_sad_ma_ctrl_pt_x1,	GET_BITS(pp->tnr0_blnd[16],0,8),\
															reg_sad_ma_ctrl_pt_y1,	GET_BITS(pp->tnr0_blnd[17],0,8),\
															reg_sad_ma_ctrl_pt_x0,	GET_BITS(pp->tnr0_blnd[18],0,8),\
															reg_sad_ma_ctrl_pt_y0,	GET_BITS(pp->tnr0_blnd[19],0,8));
				PE_NRD_HW_O26_TNR0_WR04(tnr_ctrl_61,		reg_sad_ma_ctrl_pt_x3,	GET_BITS(pp->tnr0_blnd[20],0,8),\
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
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT8 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR_DETAIL_T *ctrl_param =(LX_PE_NRD_TNR_DETAIL_T *)pstParams;
			LX_PE_NRD_TNR7_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_ND0_O26_QRd04(tnr_ctrl_00,				reg_sad_8x3_iir_alpha,	pp->tnr0__ctl[0],\
															reg_sad_8x3_chroma_en,	pp->tnr0__ctl[1],\
															reg_sad_8x3_iir_en, 	pp->tnr0__ctl[2],\
															reg_sad_8x3_res,		pp->tnr0__ctl[3]);
				PE_ND0_O26_QRd10(tnr_ctrl_02,				sc_th_memc, 			pp->tnr0__ctl[4],\
															sc_th_ma,				pp->tnr0__ctl[5],\
															sc_out_mode,			pp->tnr0__ctl[6],\
															sc_chroma_gain, 		pp->tnr0__ctl[7],\
															sc_max_flt_tap, 		pp->tnr0__ctl[8],\
															sc_scale,				pp->tnr0__ctl[9],\
															sc_chroma_en,			pp->tnr0__ctl[10],\
															sc_calc_prev_hist,		pp->tnr0__ctl[11],\
															sc_max_flt_en,			pp->tnr0__ctl[12],\
															sc_en,					pp->tnr0__ctl[13]);
				PE_ND0_O26_QRd04(tnr_ctrl_05,				reg_mamc_mc_sad_cut,	pp->tnr0__ctl[14],\
															reg_mamc_ma_sad_cut,	pp->tnr0__ctl[15],\
															reg_mamc_blend_mv_max_or_sum,	pp->tnr0__ctl[16],\
															reg_mamc_blend_mode,	pp->tnr0__ctl[17]);
				PE_ND0_O26_QRd02(tnr_ctrl_06,				reg_me_pv_base, pp->tnr0__ctl[18],\
															reg_me_lb_base, pp->tnr0__ctl[19]);
				PE_ND0_O26_QRd01(tnr_ctrl_21,				reg_svar_scale, pp->tnr0__ctl[20]);
				/*tnr0___ma*/
				PE_ND0_O26_QRd02(tnr_ctrl_07,				reg_sc_en,			pp->tnr0___ma[0],\
															reg_5x5_sad_cut,	pp->tnr0___ma[1]);
				/*tnr0___me*/
				PE_ND0_O26_QRd03(tnr_ctrl_09,				reg_pv_smooth_clip, pp->tnr0___me[0],\
															reg_lb_smooth_clip, pp->tnr0___me[1],\
															reg_sad_base,		pp->tnr0___me[2]);
				PE_ND0_O26_QRd03(tnr_ctrl_11,				reg_me_n15_protection,	pp->tnr0___me[3],\
															pv_smooth_en,		pp->tnr0___me[4],\
															lb_smooth_en,		pp->tnr0___me[5]);
				PE_ND0_O26_QRd02(tnr_ctrl_13,				reg_zero_sad_adv,	pp->tnr0___me[6],\
															reg_zero_sad_ratio, pp->tnr0___me[7]);

				/*tnr0__mlb*/
				PE_ND0_O26_QRd01(tnr_ctrl_16,		reg_sad_acc_mode,	pp->tnr0__mlb[0]);
				PE_ND0_O26_QRd09(tnr_ctrl_18,		reg_bmv_pmv_tl_en,	pp->tnr0__mlb[1],\
													reg_bmv_pmv_tl, 	pp->tnr0__mlb[2],\
													reg_bmv_gmv_tl_en,	pp->tnr0__mlb[3],\
													reg_bmv_gmv_tl, 	pp->tnr0__mlb[4],\
													reg_gmv_gmv_tl_en,	pp->tnr0__mlb[5],\
													reg_gmv_gmv_tl,		pp->tnr0__mlb[6],\
													reg_gsad_scale,		pp->tnr0__mlb[7],\
													reg_bmv_rst_mode,   pp->tnr0__mlb[8],\
													reg_bsad_scale,		pp->tnr0__mlb[9]);
				PE_ND0_O26_QRd05(tnr_ctrl_19,		bmv_0mv_tl_en,		pp->tnr0__mlb[10],\
													bmv_0mv_tl,			pp->tnr0__mlb[11],\
													gmv_0mv_tl_en,		pp->tnr0__mlb[12],\
													gmv_0mv_tl,			pp->tnr0__mlb[13],\
													bmv_coring_th,		pp->tnr0__mlb[14]);

				/*tnr0__mc*/
				PE_ND0_O26_QRd09(tnr_ctrl_24,			reg_chroma_sad_en,	pp->tnr0___mc[0],\
														reg_cnt_mode,		pp->tnr0___mc[1],\
														reg_avg_cmp_res,	pp->tnr0___mc[2],\
														reg_avg_cmp_en, 	pp->tnr0___mc[3],\
														reg_5x5_sad_cut,	pp->tnr0___mc[4],\
														reg_chroma_sad_res, pp->tnr0___mc[5],\
														reg_crgn_gain_en,	pp->tnr0___mc[6],\
														reg_luma_gain_en,	pp->tnr0___mc[7],\
														reg_ombc_en,		pp->tnr0___mc[8]);
				PE_ND0_O26_QRd03(tnr_ctrl_26,			reg_tnr_final_lut_yy_x3,	pp->tnr0___mc[9],\
														reg_tnr_final_lut_yy_y3,	pp->tnr0___mc[10],\
														reg_tnr_final_lut_yy_x2,	pp->tnr0___mc[11]);
				PE_ND0_O26_QRd03(tnr_ctrl_27,			reg_tnr_final_lut_yy_y2,	pp->tnr0___mc[12],\
														reg_tnr_final_lut_yy_x1,	pp->tnr0___mc[13],\
														reg_tnr_final_lut_yy_y1,	pp->tnr0___mc[14]);
				PE_ND0_O26_QRd02(tnr_ctrl_28,			reg_tnr_final_lut_yy_x0,	pp->tnr0___mc[15],\
														reg_tnr_final_lut_yy_y0,	pp->tnr0___mc[16]);
				PE_ND0_O26_QRd03(tnr_ctrl_29,			reg_tnr_final_lut_cb_x3,	pp->tnr0___mc[17],\
														reg_tnr_final_lut_cb_y3,	pp->tnr0___mc[18],\
														reg_tnr_final_lut_cb_x2,	pp->tnr0___mc[19]);
				PE_ND0_O26_QRd03(tnr_ctrl_30,			reg_tnr_final_lut_cb_y2,	pp->tnr0___mc[20],\
														reg_tnr_final_lut_cb_x1,	pp->tnr0___mc[21],\
														reg_tnr_final_lut_cb_y1,	pp->tnr0___mc[22]);
				PE_ND0_O26_QRd02(tnr_ctrl_31,			reg_tnr_final_lut_cb_x0,	pp->tnr0___mc[23],\
														reg_tnr_final_lut_cb_y0,	pp->tnr0___mc[24]);
				PE_ND0_O26_QRd02(tnr_ctrl_32,			reg_blur_coef,		pp->tnr0___mc[25],\
														reg_gf_gain,		pp->tnr0___mc[26]);
				PE_ND0_O26_QRd04(tnr_ctrl_33,			reg_move_step,		pp->tnr0___mc[27],\
														reg_same_sad_th,	pp->tnr0___mc[28],\
														reg_p_mv0_only, 	pp->tnr0___mc[29],\
														same_protection_en, pp->tnr0___mc[30]);

				/*tnr0_blnd*/

				PE_ND0_O26_QRd04(tnr_ctrl_56,			reg_sad_mc_ctrl_pt_x1,	pp->tnr0_blnd[0],\
														reg_sad_mc_ctrl_pt_y1,	pp->tnr0_blnd[1],\
														reg_sad_mc_ctrl_pt_x0,	pp->tnr0_blnd[2],\
														reg_sad_mc_ctrl_pt_y0,	pp->tnr0_blnd[3]);
				PE_ND0_O26_QRd04(tnr_ctrl_57,			reg_sad_mc_ctrl_pt_x3,	pp->tnr0_blnd[4],\
														reg_sad_mc_ctrl_pt_y3,	pp->tnr0_blnd[5],\
														reg_sad_mc_ctrl_pt_x2,	pp->tnr0_blnd[6],\
														reg_sad_mc_ctrl_pt_y2,	pp->tnr0_blnd[7]);
				PE_ND0_O26_QRd04(tnr_ctrl_58,			reg_abs_mv_ctrl_pt_x1,	pp->tnr0_blnd[8],\
														reg_abs_mv_ctrl_pt_y1,	pp->tnr0_blnd[9],\
														reg_abs_mv_ctrl_pt_x0,	pp->tnr0_blnd[10],\
														reg_abs_mv_ctrl_pt_y0,	pp->tnr0_blnd[11]);
				PE_ND0_O26_QRd04(tnr_ctrl_59,			reg_abs_mv_ctrl_pt_x3,	pp->tnr0_blnd[12],\
														reg_abs_mv_ctrl_pt_y3,	pp->tnr0_blnd[13],\
														reg_abs_mv_ctrl_pt_x2,	pp->tnr0_blnd[14],\
														reg_abs_mv_ctrl_pt_y2,	pp->tnr0_blnd[15]);
				PE_ND0_O26_QRd04(tnr_ctrl_60,			reg_sad_ma_ctrl_pt_x1,	pp->tnr0_blnd[16],\
														reg_sad_ma_ctrl_pt_y1,	pp->tnr0_blnd[17],\
														reg_sad_ma_ctrl_pt_x0,	pp->tnr0_blnd[18],\
														reg_sad_ma_ctrl_pt_y0,	pp->tnr0_blnd[19]);
				PE_ND0_O26_QRd04(tnr_ctrl_61,			reg_sad_ma_ctrl_pt_x3,	pp->tnr0_blnd[20],\
														reg_sad_ma_ctrl_pt_y3,	pp->tnr0_blnd[21],\
														reg_sad_ma_ctrl_pt_x2,	pp->tnr0_blnd[22],\
														reg_sad_ma_ctrl_pt_y2,	pp->tnr0_blnd[23]);

			}
			pd = pp->tnr0__ctl;
			printk("get[%d] : tnr0__ctl\n"
			"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__ctl	  [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);

			pd = pp->tnr0___ma;
			printk("get[%d] : tnr0___ma\n"
			"tnr0___ma    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			
			pd = pp->tnr0___me;
			printk("get[%d] : tnr0___me\n"
			"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->tnr0__mlb;
			printk("get[%d] : tnr0__mlb\n"
			"tnr0__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);

			pd = pp->tnr0___mc;
			printk("get[%d] : tnr0___mc\n"
			"tnr0___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0___mc	  [30]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
			pd[30]);

			pd = pp->tnr0_blnd;
			printk("get[%d] : tnr0_blnd\n"
			"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23]);
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	//const PE_REG_PARAM_T *p_db = NULL;
	//PE_INF_O26_SETTINGS_T inf_set;
	//LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	//PE_TNL_HW_PARAM_REG_O26_T *p_tnl_dflt = _g_pe_tnl_hw_param_data_o26.reg_dflt.data;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	//#define O26_TNL_DFT(_num)	(p_tnl_dflt->tnr_lut_##_num.main_lut_indir_data0)
	//PE_TNL_HW_PARAM_REG_O26_T *p_tnl_dflt_b = _g_pe_tnl_hw_param_data_o26.reg_dflt.data;
	//#define O26_TNL_DFT_B(_num)	(p_tnl_dflt_b->tnr_lut_##_num.main_lut_indir_data0)
	LX_PE_NRD_TNR2ND_CMN_T *ctrl_param;
	LX_PE_NRD_TNR2ND2_CMN_T *pp;
	static LX_PE_NRD_TNR2ND2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			ctrl_param =(LX_PE_NRD_TNR2ND_CMN_T *)pstParams;
			pp = (typeof(*pp) *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR2ND2_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR2ND2_CMN_T\n");
				ret=RET_OK;
				break;
			}
			UINT32 *pd = pp->tnr1__lut;
			PE_DBG_NRD("[%d]tnr1___en:%d\n", pp->win_id, pp->tnr1___en);
			PE_DBG_NRD( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = pp->tnr1_gain;
			PE_DBG_NRD(\
			"tnr_lut_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = pp->tnr1_buff;
			PE_DBG_NRD(\
			"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],	pd[12], pd[13], pd[14]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* skip drv tnr ctrl, if fw tnr on. */
				if (1)//PE_CMN_HW_O26_GetDbInfo(PE_CMN_HW_O26_DB_INF_MD0_TNR_FW_EN, 0))
				{
					/* save prev values */
					memcpy(&(pInfo->tnr1_cmn), pp, sizeof(LX_PE_NRD_TNR2ND2_CMN_T));
					/* download tnr user db */
					ret = PE_NRD_HW_O26_DownloadTnr2ndUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadTnr2ndUserDb() error.\n",__F__,__L__);
					PE_DBG_NRD("set tnr lut by firmware\n");
				}
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR2ND_CMN_T *ctrl_param =(LX_PE_NRD_TNR_DETAIL_T *)pstParams;
			LX_PE_NRD_TNR2ND2_CMN_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				memcpy(pp, &(pInfo->tnr1_cmn), sizeof(LX_PE_NRD_TNR2ND2_CMN_T));
			}
			UINT32 *pd = pp->tnr1__lut;
			printk("[%d]tnr1___en:%d\n", pp->win_id, pp->tnr1___en);
			printk( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = pp->tnr1_gain;
			printk(\
			"tnr1_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = pp->tnr1_buff;
			printk(\
			"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11], pd[12], pd[13], pd[14]);
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR7_DETAIL_T O26
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnr2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;

	LX_PE_NRD_TNR2ND_DETAIL_T *ctrl_param;
	LX_PE_NRD_TNR2ND3_DETAIL_T *pp;
	static LX_PE_NRD_TNR2ND3_DETAIL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	__attribute__((unused)) static UINT32 chk = 0x0;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			ctrl_param =(LX_PE_NRD_TNR2ND_DETAIL_T *)pstParams;
			pp = (typeof(*pp) *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR2ND3_DETAIL_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR2ND3_DETAIL_T\n");
				ret=RET_OK;
				break;
			}
			pd = pp->tnr1__ctl;
			PE_DBG_NRD("set[%d] : tnr1__ctl\n"
			"tnr1__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1__ctl	  [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);

			pd = pp->tnr1___ma;
			PE_DBG_NRD("set[%d] : tnr1___ma\n"
			"tnr1___ma    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			
			pd = pp->tnr1___me;
			PE_DBG_NRD("set[%d] : tnr1___me\n"
			"tnr1___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->tnr1__mlb;
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

			pd = pp->tnr1_blnd;
			PE_DBG_NRD("set[%d] : tnr1_blnd\n"
			"tnr1_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23]);
			#if 1
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/*tnr1__ctl*/
				#if 0
				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_00,		reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8),\
															reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1),\
															reg_sad_8x3_iir_en, GET_BITS(pp->tnr1__ctl[2],0,1),\
															reg_sad_8x3_res,	GET_BITS(pp->tnr1__ctl[3],0,2));
				#endif
				
				/*set tnr_ctrl_00 @ dummy reg(nd_fsw_ctrl_03) bc racing issue with f/w */
				PE_ND1_O26_QWr04(nd_fsw_ctrl_03,			reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8),\
															reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1),\
															reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr1__ctl[2],0,1),\
															reg_sad_8x3_res,		GET_BITS(pp->tnr1__ctl[3],0,2));
				PE_NRD_HW_O26_TNR1_SET_USER(tnr_ctrl_22,	reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8));
				PE_NRD_HW_O26_TNR1_SET_USER(tnr_ctrl_22,	reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1));
				PE_NRD_HW_O26_TNR1_SET_USER(tnr_ctrl_22,	reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr1__ctl[2],0,1));
				PE_NRD_HW_O26_TNR1_SET_USER(tnr_ctrl_22,	reg_sad_8x3_res,		GET_BITS(pp->tnr1__ctl[3],0,2));
				PE_NRD_HW_O26_TNR1_WR10(tnr_ctrl_02,		sc_th_memc, GET_BITS(pp->tnr1__ctl[4],0,8),\
															sc_th_ma,	GET_BITS(pp->tnr1__ctl[5],0,8),\
															sc_out_mode,	GET_BITS(pp->tnr1__ctl[6],0,1),\
															sc_chroma_gain, GET_BITS(pp->tnr1__ctl[7],0,3),\
															sc_max_flt_tap, GET_BITS(pp->tnr1__ctl[8],0,3),\
															sc_scale,	GET_BITS(pp->tnr1__ctl[9],0,3),\
															sc_chroma_en,	GET_BITS(pp->tnr1__ctl[10],0,1),\
															sc_calc_prev_hist,	GET_BITS(pp->tnr1__ctl[11],0,1),\
															sc_max_flt_en,	GET_BITS(pp->tnr1__ctl[12],0,1),\
															sc_en,	GET_BITS(pp->tnr1__ctl[13],0,1));
				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_05,		reg_mamc_mc_sad_cut,	GET_BITS(pp->tnr1__ctl[14],0,1),\
															reg_mamc_ma_sad_cut,	GET_BITS(pp->tnr1__ctl[15],0,1),\
															reg_mamc_blend_mv_max_or_sum,	GET_BITS(pp->tnr1__ctl[16],0,1),\
															reg_mamc_blend_mode,	GET_BITS(pp->tnr1__ctl[17],0,2));
				PE_NRD_HW_O26_TNR1_WR02(tnr_ctrl_06,		reg_me_pv_base, GET_BITS(pp->tnr1__ctl[18],0,8),\
															reg_me_lb_base, GET_BITS(pp->tnr1__ctl[19],0,8));
				PE_NRD_HW_O26_TNR1_WR01(tnr_ctrl_21,		reg_svar_scale, GET_BITS(pp->tnr1__ctl[20],0,3));
				/*tnr1___ma*/
				PE_NRD_HW_O26_TNR1_WR02(tnr_ctrl_07,		reg_sc_en,	GET_BITS(pp->tnr1___ma[0],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr1___ma[1],0,2));
				/*tnr1___me*/
				PE_NRD_HW_O26_TNR1_WR03(tnr_ctrl_09,		reg_pv_smooth_clip, GET_BITS(pp->tnr1___me[0],0,6),\
															reg_lb_smooth_clip, GET_BITS(pp->tnr1___me[1],0,6),\
															reg_sad_base,	GET_BITS(pp->tnr1___me[2],0,7));
				PE_NRD_HW_O26_TNR1_WR03(tnr_ctrl_11,		reg_me_n15_protection,	GET_BITS(pp->tnr1___me[3],0,1),\
															pv_smooth_en,	GET_BITS(pp->tnr1___me[4],0,1),\
															lb_smooth_en,	GET_BITS(pp->tnr1___me[5],0,1));
				PE_NRD_HW_O26_TNR1_WR02(tnr_ctrl_13,		reg_zero_sad_adv,	GET_BITS(pp->tnr1___me[6],0,1),\
															reg_zero_sad_ratio, GET_BITS(pp->tnr1___me[7],0,8));

				/*tnr1__mlb*/
				PE_NRD_HW_O26_TNR1_WR01(tnr_ctrl_16,	reg_sad_acc_mode,	GET_BITS(pp->tnr1__mlb[0],0,2));
				PE_NRD_HW_O26_TNR1_WR09(tnr_ctrl_18,	reg_bmv_pmv_tl_en,	GET_BITS(pp->tnr1__mlb[1],0,1),\
														reg_bmv_pmv_tl, 	GET_BITS(pp->tnr1__mlb[2],0,7),\
														reg_bmv_gmv_tl_en,	GET_BITS(pp->tnr1__mlb[3],0,1),\
														reg_bmv_gmv_tl, 	GET_BITS(pp->tnr1__mlb[4],0,7),\
														reg_gmv_gmv_tl_en,	GET_BITS(pp->tnr1__mlb[5],0,1),\
														reg_gmv_gmv_tl,		GET_BITS(pp->tnr1__mlb[6],0,7),\
														reg_gsad_scale,		GET_BITS(pp->tnr1__mlb[7],0,3),\
														reg_bmv_rst_mode,   GET_BITS(pp->tnr1__mlb[8],0,1),\
														reg_bsad_scale,		GET_BITS(pp->tnr1__mlb[9],0,3));
				PE_NRD_HW_O26_TNR1_WR05(tnr_ctrl_19,	bmv_0mv_tl_en,		GET_BITS(pp->tnr1__mlb[10],0,1),\
														bmv_0mv_tl,			GET_BITS(pp->tnr1__mlb[11],0,7),\
														gmv_0mv_tl_en,		GET_BITS(pp->tnr1__mlb[12],0,1),\
														gmv_0mv_tl,			GET_BITS(pp->tnr1__mlb[13],0,7),\
														bmv_coring_th,		GET_BITS(pp->tnr1__mlb[14],0,8));

				/*tnr1__mc*/
				PE_NRD_HW_O26_TNR1_WR09(tnr_ctrl_24,		reg_chroma_sad_en,	GET_BITS(pp->tnr1___mc[0],0,1),\
															reg_cnt_mode,	GET_BITS(pp->tnr1___mc[1],0,3),\
															reg_avg_cmp_res,	GET_BITS(pp->tnr1___mc[2],0,3),\
															reg_avg_cmp_en, GET_BITS(pp->tnr1___mc[3],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr1___mc[4],0,2),\
															reg_chroma_sad_res, GET_BITS(pp->tnr1___mc[5],0,2),\
															reg_crgn_gain_en,	GET_BITS(pp->tnr1___mc[6],0,1),\
															reg_luma_gain_en,	GET_BITS(pp->tnr1___mc[7],0,1),\
															reg_ombc_en,	GET_BITS(pp->tnr1___mc[8],0,1));
				PE_NRD_HW_O26_TNR1_WR03(tnr_ctrl_26,		reg_tnr_final_lut_yy_x3,	GET_BITS(pp->tnr1___mc[9],0,10),\
															reg_tnr_final_lut_yy_y3,	GET_BITS(pp->tnr1___mc[10],0,10),\
															reg_tnr_final_lut_yy_x2,	GET_BITS(pp->tnr1___mc[11],0,10));
				PE_NRD_HW_O26_TNR1_WR03(tnr_ctrl_27,		reg_tnr_final_lut_yy_y2,	GET_BITS(pp->tnr1___mc[12],0,10),\
															reg_tnr_final_lut_yy_x1,	GET_BITS(pp->tnr1___mc[13],0,10),\
															reg_tnr_final_lut_yy_y1,	GET_BITS(pp->tnr1___mc[14],0,10));
				PE_NRD_HW_O26_TNR1_WR02(tnr_ctrl_28,		reg_tnr_final_lut_yy_x0,	GET_BITS(pp->tnr1___mc[15],0,10),\
															reg_tnr_final_lut_yy_y0,	GET_BITS(pp->tnr1___mc[16],0,10));
				PE_NRD_HW_O26_TNR1_WR03(tnr_ctrl_29,		reg_tnr_final_lut_cb_x3,	GET_BITS(pp->tnr1___mc[17],0,10),\
															reg_tnr_final_lut_cb_y3,	GET_BITS(pp->tnr1___mc[18],0,10),\
															reg_tnr_final_lut_cb_x2,	GET_BITS(pp->tnr1___mc[19],0,10));
				PE_NRD_HW_O26_TNR1_WR03(tnr_ctrl_30,		reg_tnr_final_lut_cb_y2,	GET_BITS(pp->tnr1___mc[20],0,10),\
															reg_tnr_final_lut_cb_x1,	GET_BITS(pp->tnr1___mc[21],0,10),\
															reg_tnr_final_lut_cb_y1,	GET_BITS(pp->tnr1___mc[22],0,10));
				PE_NRD_HW_O26_TNR1_WR02(tnr_ctrl_31,		reg_tnr_final_lut_cb_x0,	GET_BITS(pp->tnr1___mc[23],0,10),\
															reg_tnr_final_lut_cb_y0,	GET_BITS(pp->tnr1___mc[24],0,10));
				PE_NRD_HW_O26_TNR1_WR02(tnr_ctrl_32,		reg_blur_coef,	GET_BITS(pp->tnr1___mc[25],0,8),\
															reg_gf_gain,	GET_BITS(pp->tnr1___mc[26],0,8));
				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_33,		reg_move_step,	GET_BITS(pp->tnr1___mc[27],0,8),\
															reg_same_sad_th,	GET_BITS(pp->tnr1___mc[28],0,8),\
															reg_p_mv0_only, GET_BITS(pp->tnr1___mc[29],0,1),\
															same_protection_en, GET_BITS(pp->tnr1___mc[30],0,1));

				/*tnr1_blnd*/

				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_56,		reg_sad_mc_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[0],0,8),\
															reg_sad_mc_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[1],0,8),\
															reg_sad_mc_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[2],0,8),\
															reg_sad_mc_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[3],0,8));
				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_57,		reg_sad_mc_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[4],0,8),\
															reg_sad_mc_ctrl_pt_y3,	GET_BITS(pp->tnr1_blnd[5],0,8),\
															reg_sad_mc_ctrl_pt_x2,	GET_BITS(pp->tnr1_blnd[6],0,8),\
															reg_sad_mc_ctrl_pt_y2,	GET_BITS(pp->tnr1_blnd[7],0,8));
				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_58,		reg_abs_mv_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[8],0,8),\
															reg_abs_mv_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[9],0,8),\
															reg_abs_mv_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[10],0,8),\
															reg_abs_mv_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[11],0,8));
				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_59,		reg_abs_mv_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[12],0,8),\
															reg_abs_mv_ctrl_pt_y3,	GET_BITS(pp->tnr1_blnd[13],0,8),\
															reg_abs_mv_ctrl_pt_x2,	GET_BITS(pp->tnr1_blnd[14],0,8),\
															reg_abs_mv_ctrl_pt_y2,	GET_BITS(pp->tnr1_blnd[15],0,8));
				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_60,		reg_sad_ma_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[16],0,8),\
															reg_sad_ma_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[17],0,8),\
															reg_sad_ma_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[18],0,8),\
															reg_sad_ma_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[19],0,8));
				PE_NRD_HW_O26_TNR1_WR04(tnr_ctrl_61,		reg_sad_ma_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[20],0,8),\
															reg_sad_ma_ctrl_pt_y3,	GET_BITS(pp->tnr1_blnd[21],0,8),\
															reg_sad_ma_ctrl_pt_x2,	GET_BITS(pp->tnr1_blnd[22],0,8),\
															reg_sad_ma_ctrl_pt_y2,	GET_BITS(pp->tnr1_blnd[23],0,8));

			}
			#endif
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnr2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	LX_PE_WIN_ID win_id;
	UINT8 *pd;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR2ND_DETAIL_T *ctrl_param =(LX_PE_NRD_TNR2ND_DETAIL_T *)pstParams;
			LX_PE_NRD_TNR2ND3_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_ND1_O26_QRd04(tnr_ctrl_00,				reg_sad_8x3_iir_alpha,	pp->tnr1__ctl[0],\
															reg_sad_8x3_chroma_en,	pp->tnr1__ctl[1],\
															reg_sad_8x3_iir_en, 	pp->tnr1__ctl[2],\
															reg_sad_8x3_res,		pp->tnr1__ctl[3]);
				PE_ND1_O26_QRd10(tnr_ctrl_02,				sc_th_memc, 			pp->tnr1__ctl[4],\
															sc_th_ma,				pp->tnr1__ctl[5],\
															sc_out_mode,			pp->tnr1__ctl[6],\
															sc_chroma_gain, 		pp->tnr1__ctl[7],\
															sc_max_flt_tap, 		pp->tnr1__ctl[8],\
															sc_scale,				pp->tnr1__ctl[9],\
															sc_chroma_en,			pp->tnr1__ctl[10],\
															sc_calc_prev_hist,		pp->tnr1__ctl[11],\
															sc_max_flt_en,			pp->tnr1__ctl[12],\
															sc_en,					pp->tnr1__ctl[13]);
				PE_ND1_O26_QRd04(tnr_ctrl_05,				reg_mamc_mc_sad_cut,	pp->tnr1__ctl[14],\
															reg_mamc_ma_sad_cut,	pp->tnr1__ctl[15],\
															reg_mamc_blend_mv_max_or_sum,	pp->tnr1__ctl[16],\
															reg_mamc_blend_mode,	pp->tnr1__ctl[17]);
				PE_ND1_O26_QRd02(tnr_ctrl_06,				reg_me_pv_base, pp->tnr1__ctl[18],\
															reg_me_lb_base, pp->tnr1__ctl[19]);
				PE_ND1_O26_QRd01(tnr_ctrl_21,				reg_svar_scale, pp->tnr1__ctl[20]);
				/*tnr1___ma*/
				PE_ND1_O26_QRd02(tnr_ctrl_07,				reg_sc_en,			pp->tnr1___ma[0],\
															reg_5x5_sad_cut,	pp->tnr1___ma[1]);
				/*tnr1___me*/
				PE_ND1_O26_QRd03(tnr_ctrl_09,				reg_pv_smooth_clip, pp->tnr1___me[0],\
															reg_lb_smooth_clip, pp->tnr1___me[1],\
															reg_sad_base,		pp->tnr1___me[2]);
				PE_ND1_O26_QRd03(tnr_ctrl_11,				reg_me_n15_protection,	pp->tnr1___me[3],\
															pv_smooth_en,		pp->tnr1___me[4],\
															lb_smooth_en,		pp->tnr1___me[5]);
				PE_ND1_O26_QRd02(tnr_ctrl_13,				reg_zero_sad_adv,	pp->tnr1___me[6],\
															reg_zero_sad_ratio, pp->tnr1___me[7]);

				/*tnr1__mlb*/
				PE_ND1_O26_QRd01(tnr_ctrl_16,		reg_sad_acc_mode,	pp->tnr1__mlb[0]);
				PE_ND1_O26_QRd09(tnr_ctrl_18,		reg_bmv_pmv_tl_en,	pp->tnr1__mlb[1],\
													reg_bmv_pmv_tl, 	pp->tnr1__mlb[2],\
													reg_bmv_gmv_tl_en,	pp->tnr1__mlb[3],\
													reg_bmv_gmv_tl, 	pp->tnr1__mlb[4],\
													reg_gmv_gmv_tl_en,	pp->tnr1__mlb[5],\
													reg_gmv_gmv_tl,		pp->tnr1__mlb[6],\
													reg_gsad_scale,		pp->tnr1__mlb[7],\
													reg_bmv_rst_mode,   pp->tnr1__mlb[8],\
													reg_bsad_scale,		pp->tnr1__mlb[9]);
				PE_ND1_O26_QRd05(tnr_ctrl_19,		bmv_0mv_tl_en,		pp->tnr1__mlb[10],\
													bmv_0mv_tl,			pp->tnr1__mlb[11],\
													gmv_0mv_tl_en,		pp->tnr1__mlb[12],\
													gmv_0mv_tl,			pp->tnr1__mlb[13],\
													bmv_coring_th,		pp->tnr1__mlb[14]);

				/*tnr1__mc*/
				PE_ND1_O26_QRd09(tnr_ctrl_24,			reg_chroma_sad_en,	pp->tnr1___mc[0],\
														reg_cnt_mode,		pp->tnr1___mc[1],\
														reg_avg_cmp_res,	pp->tnr1___mc[2],\
														reg_avg_cmp_en, 	pp->tnr1___mc[3],\
														reg_5x5_sad_cut,	pp->tnr1___mc[4],\
														reg_chroma_sad_res, pp->tnr1___mc[5],\
														reg_crgn_gain_en,	pp->tnr1___mc[6],\
														reg_luma_gain_en,	pp->tnr1___mc[7],\
														reg_ombc_en,		pp->tnr1___mc[8]);
				PE_ND1_O26_QRd03(tnr_ctrl_26,			reg_tnr_final_lut_yy_x3,	pp->tnr1___mc[9],\
														reg_tnr_final_lut_yy_y3,	pp->tnr1___mc[10],\
														reg_tnr_final_lut_yy_x2,	pp->tnr1___mc[11]);
				PE_ND1_O26_QRd03(tnr_ctrl_27,			reg_tnr_final_lut_yy_y2,	pp->tnr1___mc[12],\
														reg_tnr_final_lut_yy_x1,	pp->tnr1___mc[13],\
														reg_tnr_final_lut_yy_y1,	pp->tnr1___mc[14]);
				PE_ND1_O26_QRd02(tnr_ctrl_28,			reg_tnr_final_lut_yy_x0,	pp->tnr1___mc[15],\
														reg_tnr_final_lut_yy_y0,	pp->tnr1___mc[16]);
				PE_ND1_O26_QRd03(tnr_ctrl_29,			reg_tnr_final_lut_cb_x3,	pp->tnr1___mc[17],\
														reg_tnr_final_lut_cb_y3,	pp->tnr1___mc[18],\
														reg_tnr_final_lut_cb_x2,	pp->tnr1___mc[19]);
				PE_ND1_O26_QRd03(tnr_ctrl_30,			reg_tnr_final_lut_cb_y2,	pp->tnr1___mc[20],\
														reg_tnr_final_lut_cb_x1,	pp->tnr1___mc[21],\
														reg_tnr_final_lut_cb_y1,	pp->tnr1___mc[22]);
				PE_ND1_O26_QRd02(tnr_ctrl_31,			reg_tnr_final_lut_cb_x0,	pp->tnr1___mc[23],\
														reg_tnr_final_lut_cb_y0,	pp->tnr1___mc[24]);
				PE_ND1_O26_QRd02(tnr_ctrl_32,			reg_blur_coef,		pp->tnr1___mc[25],\
														reg_gf_gain,		pp->tnr1___mc[26]);
				PE_ND1_O26_QRd04(tnr_ctrl_33,			reg_move_step,		pp->tnr1___mc[27],\
														reg_same_sad_th,	pp->tnr1___mc[28],\
														reg_p_mv0_only, 	pp->tnr1___mc[29],\
														same_protection_en, pp->tnr1___mc[30]);

				/*tnr1_blnd*/

				PE_ND1_O26_QRd04(tnr_ctrl_56,			reg_sad_mc_ctrl_pt_x1,	pp->tnr1_blnd[0],\
														reg_sad_mc_ctrl_pt_y1,	pp->tnr1_blnd[1],\
														reg_sad_mc_ctrl_pt_x0,	pp->tnr1_blnd[2],\
														reg_sad_mc_ctrl_pt_y0,	pp->tnr1_blnd[3]);
				PE_ND1_O26_QRd04(tnr_ctrl_57,			reg_sad_mc_ctrl_pt_x3,	pp->tnr1_blnd[4],\
														reg_sad_mc_ctrl_pt_y3,	pp->tnr1_blnd[5],\
														reg_sad_mc_ctrl_pt_x2,	pp->tnr1_blnd[6],\
														reg_sad_mc_ctrl_pt_y2,	pp->tnr1_blnd[7]);
				PE_ND1_O26_QRd04(tnr_ctrl_58,			reg_abs_mv_ctrl_pt_x1,	pp->tnr1_blnd[8],\
														reg_abs_mv_ctrl_pt_y1,	pp->tnr1_blnd[9],\
														reg_abs_mv_ctrl_pt_x0,	pp->tnr1_blnd[10],\
														reg_abs_mv_ctrl_pt_y0,	pp->tnr1_blnd[11]);
				PE_ND1_O26_QRd04(tnr_ctrl_59,			reg_abs_mv_ctrl_pt_x3,	pp->tnr1_blnd[12],\
														reg_abs_mv_ctrl_pt_y3,	pp->tnr1_blnd[13],\
														reg_abs_mv_ctrl_pt_x2,	pp->tnr1_blnd[14],\
														reg_abs_mv_ctrl_pt_y2,	pp->tnr1_blnd[15]);
				PE_ND1_O26_QRd04(tnr_ctrl_60,			reg_sad_ma_ctrl_pt_x1,	pp->tnr1_blnd[16],\
														reg_sad_ma_ctrl_pt_y1,	pp->tnr1_blnd[17],\
														reg_sad_ma_ctrl_pt_x0,	pp->tnr1_blnd[18],\
														reg_sad_ma_ctrl_pt_y0,	pp->tnr1_blnd[19]);
				PE_ND1_O26_QRd04(tnr_ctrl_61,			reg_sad_ma_ctrl_pt_x3,	pp->tnr1_blnd[20],\
														reg_sad_ma_ctrl_pt_y3,	pp->tnr1_blnd[21],\
														reg_sad_ma_ctrl_pt_x2,	pp->tnr1_blnd[22],\
														reg_sad_ma_ctrl_pt_y2,	pp->tnr1_blnd[23]);

			}
			pd = pp->tnr1__ctl;
			printk("get[%d] : tnr1__ctl\n"
			"tnr1__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1__ctl	  [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);

			pd = pp->tnr1___ma;
			printk("get[%d] : tnr1___ma\n"
			"tnr1___ma    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			
			pd = pp->tnr1___me;
			printk("get[%d] : tnr1___me\n"
			"tnr1___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->tnr1__mlb;
			printk("get[%d] : tnr1__mlb\n"
			"tnr1__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);

			pd = pp->tnr1___mc;
			printk("get[%d] : tnr1___mc\n"
			"tnr1___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1___mc	  [30]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
			pd[30]);

			pd = pp->tnr1_blnd;
			printk("get[%d] : tnr1_blnd\n"
			"tnr1_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr1_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23]);
		}
		else
		{
			printk("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_NRD_HW_O26_SetTnr3rdCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR2ND_CMN_T *ctrl_param =(LX_PE_NRD_TNR2ND_CMN_T *)pstParams;
			LX_PE_NRD_TNR2ND2_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
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
			UINT32 *pd = pp->tnr1__lut;
			PE_DBG_NRD("[%d]tnr2___en:%d\n", pp->win_id, pp->tnr1___en);
			PE_DBG_NRD( \
			"tnr2__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr2__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = pp->tnr1_gain;
			PE_DBG_NRD(\
			"tnr2_lut_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4]);
			pd = pp->tnr1_buff;
			PE_DBG_NRD(\
			"tnr2_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr2_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10], pd[11],	pd[12], pd[13], pd[14]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* skip drv tnr ctrl, if fw tnr on. */
				if (1)//PE_CMN_HW_O26_GetDbInfo(PE_CMN_HW_O26_DB_INF_MD0_TNR_FW_EN, 0))
				{
					/* save prev values */
					memcpy(&(pInfo->tnr2_cmn), pp, sizeof(LX_PE_NRD_TNR2ND2_CMN_T));
					/* download tnr user db */
					ret = PE_NRD_HW_O26_DownloadTnr3rdUserDb((void *)pp);
					PE_NRD_HW_O26_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_O26_DownloadTnr3rdUserDb() error.\n",__F__,__L__);
					PE_DBG_NRD("set tnr3rd lut by firmware\n");
				}
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR2ND3_DETAIL_T O26
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnr3rdDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR2ND_DETAIL_T *ctrl_param =(LX_PE_NRD_TNR2ND_DETAIL_T *)pstParams;
			LX_PE_NRD_TNR2ND3_DETAIL_T *pp = (typeof(*pp) *)ctrl_param->data;
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
			pd = pp->tnr1__ctl;
			PE_DBG_NRD("set[%d] : tnr2__ctl\n"
			"tnr2__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr2__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr2__ctl	  [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);

			pd = pp->tnr1___ma;
			PE_DBG_NRD("set[%d] : tnr2___ma\n"
			"tnr2___ma    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			
			pd = pp->tnr1___me;
			PE_DBG_NRD("set[%d] : tnr2___me\n"
			"tnr2___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->tnr1__mlb;
			PE_DBG_NRD("set[%d] : tnr2__mlb\n"
			"tnr2__mlb	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr2__mlb	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);

			pd16 = pp->tnr1___mc;
			PE_DBG_NRD("set[%d] : tnr2___mc\n"
			"tnr2___mc	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr2___mc	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr2___mc	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr2___mc	  [30]0x%02X,\n",\
			pp->win_id, \
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8], pd16[9],\
			pd16[10], pd16[11], pd16[12], pd16[13], pd16[14], pd16[15], pd16[16], pd16[17], pd16[18], pd16[19],\
			pd16[20], pd16[21], pd16[22], pd16[23], pd16[24], pd16[25], pd16[26], pd16[27], pd16[28], pd16[29],\
			pd16[30]);

			pd = pp->tnr1_blnd;
			PE_DBG_NRD("set[%d] : tnr2_blnd\n"
			"tnr2_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr2_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr2_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/*tnr1__ctl*/
				#if 0
				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_00,		reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8),\
															reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1),\
															reg_sad_8x3_iir_en, GET_BITS(pp->tnr1__ctl[2],0,1),\
															reg_sad_8x3_res,	GET_BITS(pp->tnr1__ctl[3],0,2));
				#endif
				
				/*set tnr_ctrl_00 @ dummy reg(nd_fsw_ctrl_03) bc racing issue with f/w */
				PE_ND2_O26_QWr04(nd_fsw_ctrl_03,			reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8),\
															reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1),\
															reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr1__ctl[2],0,1),\
															reg_sad_8x3_res,		GET_BITS(pp->tnr1__ctl[3],0,2));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_22,	reg_sad_8x3_iir_alpha,	GET_BITS(pp->tnr1__ctl[0],0,8));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_22,	reg_sad_8x3_chroma_en,	GET_BITS(pp->tnr1__ctl[1],0,1));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_22,	reg_sad_8x3_iir_en, 	GET_BITS(pp->tnr1__ctl[2],0,1));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_22,	reg_sad_8x3_res,		GET_BITS(pp->tnr1__ctl[3],0,2));
				#if 0 // let set by firmware, SICDTV-15981
				PE_NRD_HW_O26_TNR2_WR10(tnr_ctrl_02,		sc_th_memc, GET_BITS(pp->tnr1__ctl[4],0,8),\
															sc_th_ma,	GET_BITS(pp->tnr1__ctl[5],0,8),\
															sc_out_mode,	GET_BITS(pp->tnr1__ctl[6],0,1),\
															sc_chroma_gain, GET_BITS(pp->tnr1__ctl[7],0,3),\
															sc_max_flt_tap, GET_BITS(pp->tnr1__ctl[8],0,3),\
															sc_scale,	GET_BITS(pp->tnr1__ctl[9],0,3),\
															sc_chroma_en,	GET_BITS(pp->tnr1__ctl[10],0,1),\
															sc_calc_prev_hist,	GET_BITS(pp->tnr1__ctl[11],0,1),\
															sc_max_flt_en,	GET_BITS(pp->tnr1__ctl[12],0,1),\
															sc_en,	GET_BITS(pp->tnr1__ctl[13],0,1));
				#else
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_th_memc, GET_BITS(pp->tnr1__ctl[4],0,8));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_th_ma,	GET_BITS(pp->tnr1__ctl[5],0,8));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_out_mode,	GET_BITS(pp->tnr1__ctl[6],0,1));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_chroma_gain, GET_BITS(pp->tnr1__ctl[7],0,3));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_max_flt_tap, GET_BITS(pp->tnr1__ctl[8],0,3));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_scale,	GET_BITS(pp->tnr1__ctl[9],0,3));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_chroma_en,	GET_BITS(pp->tnr1__ctl[10],0,1));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_calc_prev_hist,	GET_BITS(pp->tnr1__ctl[11],0,1));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_max_flt_en,	GET_BITS(pp->tnr1__ctl[12],0,1));
				PE_NRD_HW_O26_TNR2_SET_USER(tnr_ctrl_02,		sc_en,	GET_BITS(pp->tnr1__ctl[13],0,1));
				#endif
				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_05,		reg_mamc_mc_sad_cut,	GET_BITS(pp->tnr1__ctl[14],0,1),\
															reg_mamc_ma_sad_cut,	GET_BITS(pp->tnr1__ctl[15],0,1),\
															reg_mamc_blend_mv_max_or_sum,	GET_BITS(pp->tnr1__ctl[16],0,1),\
															reg_mamc_blend_mode,	GET_BITS(pp->tnr1__ctl[17],0,2));
				PE_NRD_HW_O26_TNR2_WR02(tnr_ctrl_06,		reg_me_pv_base, GET_BITS(pp->tnr1__ctl[18],0,8),\
															reg_me_lb_base, GET_BITS(pp->tnr1__ctl[19],0,8));
				PE_NRD_HW_O26_TNR2_WR01(tnr_ctrl_21,		reg_svar_scale, GET_BITS(pp->tnr1__ctl[20],0,3));
				/*tnr1___ma*/
				PE_NRD_HW_O26_TNR2_WR02(tnr_ctrl_07,		reg_sc_en,	GET_BITS(pp->tnr1___ma[0],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr1___ma[1],0,2));
				/*tnr1___me*/
				PE_NRD_HW_O26_TNR2_WR03(tnr_ctrl_09,		reg_pv_smooth_clip, GET_BITS(pp->tnr1___me[0],0,6),\
															reg_lb_smooth_clip, GET_BITS(pp->tnr1___me[1],0,6),\
															reg_sad_base,	GET_BITS(pp->tnr1___me[2],0,7));
				PE_NRD_HW_O26_TNR2_WR03(tnr_ctrl_11,		reg_me_n15_protection,	GET_BITS(pp->tnr1___me[3],0,1),\
															pv_smooth_en,	GET_BITS(pp->tnr1___me[4],0,1),\
															lb_smooth_en,	GET_BITS(pp->tnr1___me[5],0,1));
				PE_NRD_HW_O26_TNR2_WR02(tnr_ctrl_13,		reg_zero_sad_adv,	GET_BITS(pp->tnr1___me[6],0,1),\
															reg_zero_sad_ratio, GET_BITS(pp->tnr1___me[7],0,8));

				/*tnr1__mlb*/
				PE_NRD_HW_O26_TNR2_WR01(tnr_ctrl_16,	reg_sad_acc_mode,	GET_BITS(pp->tnr1__mlb[0],0,2));
				PE_NRD_HW_O26_TNR2_WR09(tnr_ctrl_18,	reg_bmv_pmv_tl_en,	GET_BITS(pp->tnr1__mlb[1],0,1),\
														reg_bmv_pmv_tl, 	GET_BITS(pp->tnr1__mlb[2],0,7),\
														reg_bmv_gmv_tl_en,	GET_BITS(pp->tnr1__mlb[3],0,1),\
														reg_bmv_gmv_tl, 	GET_BITS(pp->tnr1__mlb[4],0,7),\
														reg_gmv_gmv_tl_en,	GET_BITS(pp->tnr1__mlb[5],0,1),\
														reg_gmv_gmv_tl,		GET_BITS(pp->tnr1__mlb[6],0,7),\
														reg_gsad_scale,		GET_BITS(pp->tnr1__mlb[7],0,3),\
														reg_bmv_rst_mode,   GET_BITS(pp->tnr1__mlb[8],0,1),\
														reg_bsad_scale,		GET_BITS(pp->tnr1__mlb[9],0,3));
				PE_NRD_HW_O26_TNR2_WR05(tnr_ctrl_19,	bmv_0mv_tl_en,		GET_BITS(pp->tnr1__mlb[10],0,1),\
														bmv_0mv_tl,			GET_BITS(pp->tnr1__mlb[11],0,7),\
														gmv_0mv_tl_en,		GET_BITS(pp->tnr1__mlb[12],0,1),\
														gmv_0mv_tl,			GET_BITS(pp->tnr1__mlb[13],0,7),\
														bmv_coring_th,		GET_BITS(pp->tnr1__mlb[14],0,8));

				/*tnr1__mc*/
				PE_NRD_HW_O26_TNR2_WR09(tnr_ctrl_24,		reg_chroma_sad_en,	GET_BITS(pp->tnr1___mc[0],0,1),\
															reg_cnt_mode,	GET_BITS(pp->tnr1___mc[1],0,3),\
															reg_avg_cmp_res,	GET_BITS(pp->tnr1___mc[2],0,3),\
															reg_avg_cmp_en, GET_BITS(pp->tnr1___mc[3],0,1),\
															reg_5x5_sad_cut,	GET_BITS(pp->tnr1___mc[4],0,2),\
															reg_chroma_sad_res, GET_BITS(pp->tnr1___mc[5],0,2),\
															reg_crgn_gain_en,	GET_BITS(pp->tnr1___mc[6],0,1),\
															reg_luma_gain_en,	GET_BITS(pp->tnr1___mc[7],0,1),\
															reg_ombc_en,	GET_BITS(pp->tnr1___mc[8],0,1));
				PE_NRD_HW_O26_TNR2_WR03(tnr_ctrl_26,		reg_tnr_final_lut_yy_x3,	GET_BITS(pp->tnr1___mc[9],0,10),\
															reg_tnr_final_lut_yy_y3,	GET_BITS(pp->tnr1___mc[10],0,10),\
															reg_tnr_final_lut_yy_x2,	GET_BITS(pp->tnr1___mc[11],0,10));
				PE_NRD_HW_O26_TNR2_WR03(tnr_ctrl_27,		reg_tnr_final_lut_yy_y2,	GET_BITS(pp->tnr1___mc[12],0,10),\
															reg_tnr_final_lut_yy_x1,	GET_BITS(pp->tnr1___mc[13],0,10),\
															reg_tnr_final_lut_yy_y1,	GET_BITS(pp->tnr1___mc[14],0,10));
				PE_NRD_HW_O26_TNR2_WR02(tnr_ctrl_28,		reg_tnr_final_lut_yy_x0,	GET_BITS(pp->tnr1___mc[15],0,10),\
															reg_tnr_final_lut_yy_y0,	GET_BITS(pp->tnr1___mc[16],0,10));
				PE_NRD_HW_O26_TNR2_WR03(tnr_ctrl_29,		reg_tnr_final_lut_cb_x3,	GET_BITS(pp->tnr1___mc[17],0,10),\
															reg_tnr_final_lut_cb_y3,	GET_BITS(pp->tnr1___mc[18],0,10),\
															reg_tnr_final_lut_cb_x2,	GET_BITS(pp->tnr1___mc[19],0,10));
				PE_NRD_HW_O26_TNR2_WR03(tnr_ctrl_30,		reg_tnr_final_lut_cb_y2,	GET_BITS(pp->tnr1___mc[20],0,10),\
															reg_tnr_final_lut_cb_x1,	GET_BITS(pp->tnr1___mc[21],0,10),\
															reg_tnr_final_lut_cb_y1,	GET_BITS(pp->tnr1___mc[22],0,10));
				PE_NRD_HW_O26_TNR2_WR02(tnr_ctrl_31,		reg_tnr_final_lut_cb_x0,	GET_BITS(pp->tnr1___mc[23],0,10),\
															reg_tnr_final_lut_cb_y0,	GET_BITS(pp->tnr1___mc[24],0,10));
				PE_NRD_HW_O26_TNR2_WR02(tnr_ctrl_32,		reg_blur_coef,	GET_BITS(pp->tnr1___mc[25],0,8),\
															reg_gf_gain,	GET_BITS(pp->tnr1___mc[26],0,8));
				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_33,		reg_move_step,	GET_BITS(pp->tnr1___mc[27],0,8),\
															reg_same_sad_th,	GET_BITS(pp->tnr1___mc[28],0,8),\
															reg_p_mv0_only, GET_BITS(pp->tnr1___mc[29],0,1),\
															same_protection_en, GET_BITS(pp->tnr1___mc[30],0,1));

				/*tnr1_blnd*/

				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_56,		reg_sad_mc_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[0],0,8),\
															reg_sad_mc_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[1],0,8),\
															reg_sad_mc_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[2],0,8),\
															reg_sad_mc_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[3],0,8));
				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_57,		reg_sad_mc_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[4],0,8),\
															reg_sad_mc_ctrl_pt_y3,	GET_BITS(pp->tnr1_blnd[5],0,8),\
															reg_sad_mc_ctrl_pt_x2,	GET_BITS(pp->tnr1_blnd[6],0,8),\
															reg_sad_mc_ctrl_pt_y2,	GET_BITS(pp->tnr1_blnd[7],0,8));
				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_58,		reg_abs_mv_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[8],0,8),\
															reg_abs_mv_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[9],0,8),\
															reg_abs_mv_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[10],0,8),\
															reg_abs_mv_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[11],0,8));
				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_59,		reg_abs_mv_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[12],0,8),\
															reg_abs_mv_ctrl_pt_y3,	GET_BITS(pp->tnr1_blnd[13],0,8),\
															reg_abs_mv_ctrl_pt_x2,	GET_BITS(pp->tnr1_blnd[14],0,8),\
															reg_abs_mv_ctrl_pt_y2,	GET_BITS(pp->tnr1_blnd[15],0,8));
				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_60,		reg_sad_ma_ctrl_pt_x1,	GET_BITS(pp->tnr1_blnd[16],0,8),\
															reg_sad_ma_ctrl_pt_y1,	GET_BITS(pp->tnr1_blnd[17],0,8),\
															reg_sad_ma_ctrl_pt_x0,	GET_BITS(pp->tnr1_blnd[18],0,8),\
															reg_sad_ma_ctrl_pt_y0,	GET_BITS(pp->tnr1_blnd[19],0,8));
				PE_NRD_HW_O26_TNR2_WR04(tnr_ctrl_61,		reg_sad_ma_ctrl_pt_x3,	GET_BITS(pp->tnr1_blnd[20],0,8),\
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
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnrSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR_SQM_CMN_T *ctrl_param =(LX_PE_NRD_TNR_SQM_CMN_T *)pstParams;
			LX_PE_NRD_TNR_SQM1_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
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
			UINT32 *pd = pp->tnr0__sqm;
			PE_DBG_NRD("[%d]tnr0__sqm:%d\n", pp->win_id, pp->tnr___val);
			PE_DBG_NRD( \
			"tnr0__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__sqm[10]0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_O26_DownloadTnrSqmCmnUserDb((void *)pp);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_DownloadTnrSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set tnr 2nd sqm ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnr2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR2ND_SQM_CMN_T *ctrl_param =(LX_PE_NRD_TNR2ND_SQM_CMN_T *)pstParams;
			LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
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
			UINT32 *pd = pp->tnr1__sqm;
			PE_DBG_NRD("[%d]tnr1__sqm:%d\n", pp->win_id, pp->tnr___val);
			PE_DBG_NRD( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_O26_DownloadTnr2ndSqmCmnUserDb((void *)pp);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_DownloadTnr2ndSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set tnr 3rd sqm ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetTnr3rdSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR2ND_SQM_CMN_T *ctrl_param =(LX_PE_NRD_TNR2ND_SQM_CMN_T *)pstParams;
			LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_NRD_TNR2ND_SQM1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_TNR2ND_SQM1_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_TNR2ND_SQM1_CMN_T 3RD\n");
				ret=RET_OK;
				break;
			}
			UINT32 *pd = pp->tnr1__sqm;
			PE_DBG_NRD("[%d]tnr1__sqm:%d\n", pp->win_id, pp->tnr___val);
			PE_DBG_NRD( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],  pd[9],  pd[10]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_O26_DownloadTnr3rdSqmCmnUserDb((void *)pp);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_DownloadTnr3rdSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnrSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_SQM_CMN_T *ctrl_param =(LX_PE_NRD_DNR_SQM_CMN_T *)pstParams;
			LX_PE_NRD_DNR_SQM3_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_NRD_DNR_SQM3_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DNR_SQM3_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DNR_SQM2_CMN_T\n");
				ret=RET_OK;
				break;
			}
			UINT32 *pd = pp->dnr___sqmui;
			PE_DBG_NRD("[%d]dnr___sqmui:%d\n", pp->win_id, pp->dnr_____val);
			PE_DBG_NRD( \
			"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_O26_DownloadDnrSqmCmnUserDb((void *)pp);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_DownloadDnrSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set dnr2nd sqm  ctrl use LX_PE_NRD_DNR_SQM2_CMN_T
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnr2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_SQM_CMN_T *ctrl_param =(LX_PE_NRD_DNR_SQM_CMN_T *)pstParams;
			LX_PE_NRD_DNR_SQM2_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
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
			UINT32 *pd = pp->dnr___sqmui;
			PE_DBG_NRD("[%d]dnr___sqmui:%d\n", pp->win_id, pp->dnr_____val);
			PE_DBG_NRD( \
			"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download dnr2nd user db */
				ret = PE_NRD_HW_O26_DownloadDnr2ndSqmCmnUserDb((void *)pp);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_DownloadDnr2ndSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set dcnt sqm ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnrDcntSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DCNT_SQM_CMN_T *ctrl_param =(LX_PE_NRD_DCNT_SQM_CMN_T *)pstParams;
			LX_PE_NRD_DCNT_SQM2_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_NRD_DCNT_SQM2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT_SQM2_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_DEC("duplicated DB : LX_PE_NRD_DCNT_SQM1_CMN_T\n");
				ret=RET_OK;
				break;
			}
			UINT32 *pd = pp->deconnd__sqmui;
			PE_DBG_DEC("[%d]deconnd__sqmui:%d\n", pp->win_id, pp->deconnd____val);
			PE_DBG_DEC( "\n"\
			"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19],\
			pd[20],  pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_O26_DownloadDnrDcntSqmCmnUserDb((void *)pp);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_DownloadDnrDcntSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * set dcnt2nd sqm ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetDnrDcnt2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		LX_PE_NRD_DCNT_SQM_CMN_T *ctrl_param ;
		LX_PE_NRD_DCNT_SQM2_CMN_T *pp ;
		static LX_PE_NRD_DCNT_SQM2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		UINT32 *pd;
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			ctrl_param =(LX_PE_NRD_DCNT_SQM_CMN_T *)pstParams;
			pp = (typeof(*pp) *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT_SQM2_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DCNT_SQM2_CMN_T 2nd\n");
				ret=RET_OK;
				break;
			}
			pd = pp->deconnd__sqmui;
			PQ_PRINT_DEC("[%d]deconnd__sqmui:%d\n", pp->win_id, pp->deconnd____val);
			PQ_PRINT_DEC( "\n"\
			"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19],\
			pd[20],  pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download dcnt user db */
				ret = PE_NRD_HW_O26_DownloadDnrDcnt2ndSqmCmnUserDb((void *)pp);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_DownloadDnrDcnt2ndSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set cco decontour sqm ctrl 
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26_SetCCODcntSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_CCO_DCNT_SQM_CMN_T *ctrl_param =(LX_PE_CCO_DCNT_SQM_CMN_T *)pstParams;
			LX_PE_CCO_DCNT_SQM1_CMN_T *pp = (typeof(*pp) *)ctrl_param->data;
			static LX_PE_CCO_DCNT_SQM1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_CCO_DCNT_SQM1_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_CCO_DCNT_SQM1_CMN_T\n");
				ret=RET_OK;
				break;
			}
			UINT32 *pd = pp->deconcco_sqmui;
			PE_DBG_NRD("[%d]deconnd__sqmui:%d\n", pp->win_id, pp->deconnd____val);
			PE_DBG_NRD( \
			"deconled_sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconled_sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconled_sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconled_sqmui[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19],\
			pd[20],  pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26],  pd[27], pd[28],  pd[29],\
			pd[30],  pd[31],  pd[32],  pd[33], pd[34]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_NRD_HW_O26_DownloadCCODcntSqmCmnUserDb((void *)pp);
				PE_NRD_HW_O26_CHECK_CODE(ret, break, \
					"[%s,%d] PE_NRD_HW_O26_DownloadCCODcntSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set tnr lb ctrl
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnrLbMode(PE_TSK_O26_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	static UINT32 count = 0;
	__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	//__attribute__((unused)) PE_INF_O26_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	static LX_PE_FMT_TYPE pre_fmt_type = LX_PE_FMT_NUM;
	UINT32 is_hfr;
	static UINT32 pre_is_hfr=0xff;
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_O26)
		{
			static PE_O26_ND_PE0_SRC_SIZE_T pre_nd1_pe0_src_size = {
				.hsize = 0,
				.vsize = 0,
				.scan_type = 0,
				};
			static PE_O26_ND_TNR_CTRL_16_T pre_nd1_tnr_ctrl_16 = {
				.reg_n_hblk = 0,
				.reg_n_vblk = 0,
				};
			static PE_O26_ND_TNR_CTRL_17_T pre_nd1_tnr_ctrl_17 = {
				.reg_blk_vsize = 0,
				.reg_blk_hsize = 0,
				};
			PE_O26_ND_TNR_CTRL_16_T cur_nd1_tnr_ctrl_16;
			PE_O26_ND_TNR_CTRL_17_T cur_nd1_tnr_ctrl_17;
			/* nd1 nblk setting *****************************************/
			if(_g_pe_nrd_hw_o26_info.is_external_chip) //O26+f20
			{
				is_hfr = (disp0_info->in_f_rate>= 610) \
					&& ((disp0_info->in_h_size > 1920) || (disp0_info->in_v_size > 1440))?1:0;
			}
			else //O26 only
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
				else if (ctrl0_info->pe0_src_h >= PE_NRD_HW_O26_TNR_SRC_H_HD_BASE)
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
				if (ctrl0_info->pe0_src_v >= PE_NRD_HW_O26_TNR_SRC_V_3K_BASE)
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
				#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
				if (pre_nd1_tnr_ctrl_16.reg_n_hblk != cur_nd1_tnr_ctrl_16.reg_n_hblk || \
					pre_nd1_tnr_ctrl_16.reg_n_vblk != cur_nd1_tnr_ctrl_16.reg_n_vblk)
				{
					PE_DBG_NRD("[set] nd1 tnr n_blk h:0x%x->0x%x, v:0x%x->0x%x\n",\
						pre_nd1_tnr_ctrl_16.reg_n_hblk, cur_nd1_tnr_ctrl_16.reg_n_hblk, \
						pre_nd1_tnr_ctrl_16.reg_n_vblk, cur_nd1_tnr_ctrl_16.reg_n_vblk);
					PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_16,reg_n_hblk,cur_nd1_tnr_ctrl_16.reg_n_hblk, \
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
					PE_NRD_HW_O26_TNR0_WR02(tnr_ctrl_17,reg_blk_vsize,cur_nd1_tnr_ctrl_17.reg_blk_vsize, \
					                                     reg_blk_hsize,cur_nd1_tnr_ctrl_17.reg_blk_hsize);
					pre_nd1_tnr_ctrl_17.reg_blk_vsize = cur_nd1_tnr_ctrl_17.reg_blk_vsize;
					pre_nd1_tnr_ctrl_17.reg_blk_hsize = cur_nd1_tnr_ctrl_17.reg_blk_hsize;
				}
				#else
				if (pre_nd1_tnr_ctrl_16.reg_n_hblk != cur_nd1_tnr_ctrl_16.reg_n_hblk || \
					pre_nd1_tnr_ctrl_16.reg_n_vblk != cur_nd1_tnr_ctrl_16.reg_n_vblk)
				{
					PE_DBG_NRD("[set] nd1 tnr n_blk h:0x%x->0x%x, v:0x%x->0x%x\n",\
						pre_nd1_tnr_ctrl_16.reg_n_hblk, cur_nd1_tnr_ctrl_16.reg_n_hblk, \
						pre_nd1_tnr_ctrl_16.reg_n_vblk, cur_nd1_tnr_ctrl_16.reg_n_vblk);
					PE_ND0_O26_QWr02(tnr_ctrl_16,reg_n_hblk,cur_nd1_tnr_ctrl_16.reg_n_hblk, \
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
					PE_ND0_O26_QWr02(tnr_ctrl_17,reg_blk_vsize,cur_nd1_tnr_ctrl_17.reg_blk_vsize, \
					                                     reg_blk_hsize,cur_nd1_tnr_ctrl_17.reg_blk_hsize);
					pre_nd1_tnr_ctrl_17.reg_blk_vsize = cur_nd1_tnr_ctrl_17.reg_blk_vsize;
					pre_nd1_tnr_ctrl_17.reg_blk_hsize = cur_nd1_tnr_ctrl_17.reg_blk_hsize;
				}
				#endif
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
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set tnr pv smooth en mode
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_SetTnrPBPMode(PE_TSK_O26_CFG_T *pCfg)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	//static UINT32 count = 0;
	static UINT32 pre_decon_blend_en = 0xff;
	UINT32 cur_decon_blend_en_0, reg_decon_blend_en;
	PE_TNR_HW_PARAM_REG_O26_T *p_tnr_dflt = _g_pe_tnr_hw_param_data_o26.reg_dflt.data;
	LX_PE_INF_DISPLAY_T cur0_inf;
	do{
		CHECK_KNULL(pCfg);
		ret = PE_INF_O26_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
		PE_NRD_HW_O26_CHECK_CODE(ret,break,"[%s,%d] PE_INF_O26_GetCurInfSettings() error.\n",__F__,__L__);
		if(PE_KDRV_VER_O26)
		{
			PE_ND0_O26_QRd01(nd_fsw_ctrl_03,reg_decon_blend_en,reg_decon_blend_en);
			//4k pbp WA
			if(cur0_inf.sub_mode == LX_DE_SUB_MODE_PBP || cur0_inf.sub_mode == LX_DE_SUB_MODE_DUALMON)
			{
				cur_decon_blend_en_0 = 0x0;
			}
			else
			{
				cur_decon_blend_en_0 = p_tnr_dflt->tnr_ctrl_22.reg_decon_blend_en;
			}
			/* compare pre vs. cur */
			if (pre_decon_blend_en != cur_decon_blend_en_0)
			{
				PE_DBG_NRD("[inf] submode:%d, read decon_blend_en:%d\n", cur0_inf.sub_mode,reg_decon_blend_en);
				PE_DBG_NRD("[set] decon_blend_en:%d -> %d\n", \
					pre_decon_blend_en,cur_decon_blend_en_0);
				PE_ND0_O26_QWr01(nd_fsw_ctrl_03, reg_decon_blend_en,GET_BITS(cur_decon_blend_en_0,0,1));
				PE_ND1_O26_QWr01(nd_fsw_ctrl_03, reg_decon_blend_en,GET_BITS(cur_decon_blend_en,0,1));
				pre_decon_blend_en = cur_decon_blend_en_0;
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

#if 0
/**
 * set tnr sc en mode
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_O26_SetTnrScMode(PE_TSK_O26_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	#if 0
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	static UINT32 count = 0;
	UINT32 cur_sc_en;
	PE_TNR_HW_PARAM_REG_O26_T *p_tnr_dflt = _g_pe_tnr_hw_param_data_o26.nd1_user.data;
	PE_TNR_HW_PARAM_REG_O26_T *p_tnr_dflt_b = _g_pe_tnr_hw_param_data_o26.nd1_user.data;
	__attribute__((unused)) PE_NRD_HW_O26_SETTINGS_T *pInfo = &_g_pe_nrd_hw_o26_info;
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_O26)
		{
			/* if ud & use_manual_sc on, sc_en off, otherwise, refer default or user */
			cur_sc_en = (pInfo->use_manual_sc==1&&pInfo->tnr0a_fmt==PE_NRD_O26_TNR_UD)? 0x0:\
				(pInfo->tnr_sc_en_mask)? pInfo->tnr_sc_en_user:p_tnr_dflt_b->tnr_ctrl_02.sc_en;
			/* compare pre vs. cur */
			if (_g_pre_sc_en != cur_sc_en)
			{
				PE_DBG_NRD("[inf] man_sc,tnr0a:%d,%d\n", \
					pInfo->use_manual_sc, pInfo->tnr0a_fmt);
				PE_DBG_NRD("[set] u,m,d:%d,%d,%d, sc_en:%d -> %d\n", \
					pInfo->tnr_sc_en_user, pInfo->tnr_sc_en_mask, \
					p_tnr_dflt_b->tnr_ctrl_02.sc_en, _g_pre_sc_en, cur_sc_en);
				PE_NRD_HW_O26_TNR0_WR01(tnr_ctrl_02,sc_en,cur_sc_en);
				_g_pre_sc_en = cur_sc_en;
			}
			if(count>PE_PRINT_COUNT_NUM)
			{
				PE_DBG_NRD("[state] man_sc,tnr0a:%d,%d, u,m,d:%d,%d,%d, sc_en:%d\n",\
					pInfo->use_manual_sc, pInfo->tnr0a_fmt, pInfo->tnr_sc_en_user, \
					pInfo->tnr_sc_en_mask, p_tnr_dflt_b->tnr_ctrl_02.sc_en, cur_sc_en);
				count=0;
			}
			count++;
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
#endif

/**
 * set dnr REG_SMR_CTRL_00
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_SetDnrSMRMode(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	//static UINT32 count = 0;
	UINT32 cur_forcing_decon_only, pre_forcing_decon_only, dnr_hsize;
	UINT32 cur_smr_master_en_yy, cur_smr_master_en_cc;
	UINT32 pre_smr_master_en_yy, pre_smr_master_en_cc;
	PE_DNR_HW_PARAM_REG_O26_T *p_dnr_usr = _g_pe_dnr_hw_param_data_o26.reg_user.data;
	LX_PE_INF_DISPLAY_T cur0_inf;
	pre_forcing_decon_only = _g_pe_nrd_hw_o26_info.pre_forcing_decon_only;
	pre_smr_master_en_yy =   _g_pe_nrd_hw_o26_info.pre_smr_master_en_yy;
	pre_smr_master_en_cc =   _g_pe_nrd_hw_o26_info.pre_smr_master_en_cc;
	cur_smr_master_en_yy = p_dnr_usr->reg_smr_ctrl_00.reg_smr_master_en_yy;
	cur_smr_master_en_cc = p_dnr_usr->reg_smr_ctrl_00.reg_smr_master_en_cc;
	do{
		ret = PE_INF_O26_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
		PE_NRD_HW_O26_CHECK_CODE(ret,break,"[%s,%d] PE_INF_O26_GetCurInfSettings() error.\n",__F__,__L__);
		if(PE_KDRV_VER_O26)
		{
			PE_DNR0_O26_QRd01(pe0_out_size, hsize, dnr_hsize);
			//4k pbp WA
			if(dnr_hsize > 1920)
			{
				cur_forcing_decon_only = 0x1;
			}
			else
			{
				cur_forcing_decon_only = 0x0;
			}
			/* compare pre vs. cur */
			if (pre_forcing_decon_only != cur_forcing_decon_only || \
				pre_smr_master_en_yy != cur_smr_master_en_yy || \
				pre_smr_master_en_cc != cur_smr_master_en_cc)
			{
				PE_NRD_HW_O26_DNR_WR03(reg_smr_ctrl_00,	reg_forcing_decon_only,	GET_BITS(cur_forcing_decon_only,0,1),\
														reg_smr_master_en_yy,	GET_BITS(cur_smr_master_en_yy,0,1),\
														reg_smr_master_en_cc,	GET_BITS(cur_smr_master_en_cc,0,1));
				_g_pe_nrd_hw_o26_info.pre_forcing_decon_only = cur_forcing_decon_only;
				_g_pe_nrd_hw_o26_info.pre_smr_master_en_yy   = cur_smr_master_en_yy;
				_g_pe_nrd_hw_o26_info.pre_smr_master_en_cc   = cur_smr_master_en_cc;
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * set tnr mode
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_SetTnrMode(PE_TSK_O26_CFG_T *pCfg)
{
    int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_O26)
		{
			ret = PE_NRD_HW_O26_SetTnrLbMode(pCfg);
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetTnrLbMode() error.\n",__F__,__L__);
			#ifdef PE_HW_O26_REG_SMR_CTRL_00
			ret = PE_NRD_HW_O26_SetDnrSMRMode();
			PE_NRD_HW_O26_CHECK_CODE(ret, break,"[%s,%d] PE_NRD_HW_O26_SetDnrSMRMode() error.\n",__F__,__L__);
			#endif
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

#if 0
/**
 * set dnr max mode
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_O26_SetDnrMaxMode(PE_TSK_O26_CFG_T *pCfg)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set bnr mode
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_O26_SetBnrMode(PE_TSK_O26_CFG_T *pCfg)
{
	int ret = RET_OK;
	return ret;
}
/**
 * set dnr mode
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_SetDnrMode(PE_TSK_O26_CFG_T *pCfg)
{
    int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_O26)
		{
			ret = PE_NRD_HW_O26_SetDnrMaxMode(pCfg);
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetDnrMaxMode() error.\n",__F__,__L__);
			ret = PE_NRD_HW_O26_SetBnrMode(pCfg);
			PE_NRD_HW_O26_CHECK_CODE(ret, break, \
				"[%s,%d] PE_NRD_HW_O26_SetBnrMode() error.\n",__F__,__L__);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set ifc mode
 *
 * @param   *pCfg [in] PE_TSK_O26_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_SetIfcMode(PE_TSK_O26_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_O26_BRINGUP
#ifndef PE_HW_O26_PROTECT_OVERLAP_SETTINGS
	static UINT32 count = 0;
	static UINT32 pre_ifc_max_en0 = 0xff;		//pre ifc_en0
	UINT32 cur_ifc_max_en0 = 0;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_DNR_HW_PARAM_REG_O26_T *p_dnr_dflt = _g_pe_dnr_hw_param_data_o26.reg_dflt.data;
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_O26)
		{
			/* if mask on, refer default, otherwise, user data */
			cur_ifc_max_en0 = (PE_HW_O26_CHK_MULTI_PATH_FMT(disp0_info->fmt_type) || \
				(disp0_info->sub_mode == LX_DE_SUB_MODE_PBP) ? 0x0:\
				p_dnr_dflt->dnr_max_ctrl.reg_ifc_max_enable);
			/* compare pre vs. cur */
			if (pre_ifc_max_en0 != cur_ifc_max_en0)
			{
				PE_DBG_NRD("[inf] sub_mode:%d, dflt:%d\n",\
					disp0_info->sub_mode, p_dnr_dflt->dnr_max_ctrl.reg_ifc_max_enable);
				PE_DBG_NRD("[set] ifc_max_en : %d -> %d\n",\
					pre_ifc_max_en0, cur_ifc_max_en0);
				PE_DNR0_O26_QWr01(dnr_max_ctrl,reg_ifc_max_enable,cur_ifc_max_en0);
				PE_NRD_HW_O26_DNR_SET_USER(dnr_max_ctrl,reg_ifc_max_enable,cur_ifc_max_en0);
				pre_ifc_max_en0 = cur_ifc_max_en0;
			}
			if(count>PE_PRINT_COUNT_NUM)
			{
				PE_DBG_NRD("[state] submode:%d, dflt:%d, ifc_en:%d\n",\
					disp0_info->sub_mode, p_dnr_dflt->dnr_max_ctrl.reg_ifc_max_enable, \
					cur_ifc_max_en0);
				count=0;
			}
			count++;
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
#endif
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
#endif
/**
 * download tnr db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_DownloadTnrDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_lut[PE_NRD_O26_TNL_NUM];
	UINT32 base_user_lut, base_gain, base_buff, base_init;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_tnr_lut_data  = NULL;
	volatile UINT32 *p_tnr_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_tnr_lut_data  = p_phys_db->tnr_lut.data;
		CHECK_KNULL(p_tnr_lut_data );
		p_tnr_user_data = p_phys_db->tnr_user.data;
		CHECK_KNULL(p_tnr_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* tnr_lut **************************************************************/
			sec_typ = PE_DDR_O26_SEC_TNR_LUT;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O26_TNR_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_TNR_LUT_SIZE;
			p_phys_db->tnr_lut.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_lut.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_lut.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_O26_TNR_LUT_ITEM_NUM * PE_DDR_O26_TNR_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			base_lut[0] = 0;									//PE_NRD_O26_TNL_HD
			base_lut[1] = base_lut[0]+PE_DDR_O26_TNR_LUT_SIZE;	//PE_NRD_O26_TNL_SD
			base_lut[2] = base_lut[1]+PE_DDR_O26_TNR_LUT_SIZE;	//PE_NRD_O26_TNL_UD
			base_lut[3] = base_lut[2]+PE_DDR_O26_TNR_LUT_SIZE;	//PE_NRD_O26_TNL_CAM_HD
			for (i=0; i<PE_DDR_O26_TNR_LUT_SIZE; i++)
			{
				p_tnr_lut_data[base_lut[0]+i] = tnr_l_lut_hd_default_o26[i].data;
				p_tnr_lut_data[base_lut[1]+i] = tnr_l_lut_sd_default_o26[i].data;
				p_tnr_lut_data[base_lut[2]+i] = tnr_l_lut_ud_default_o26[i].data;
				p_tnr_lut_data[base_lut[3]+i] = tnr_l_lut_cam_hd_default_o26[i].data;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
			/* tnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_TNR_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O26_TNR_USER_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_TNR_USER_SIZE;
			p_phys_db->tnr_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_O26_TNR_USER_ITEM_NUM * PE_DDR_O26_TNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_tnr_user_data[0]  = 0x0;
			p_tnr_user_data[1]  = 0x0;
			base_user_lut = 2;
			base_gain = base_user_lut+LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			base_buff = base_gain+LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			base_init = 7;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				p_tnr_user_data[base_user_lut+i] = tnr_l_lut_hd_default_o26[base_init+i].data;
			}
			p_tnr_user_data[base_gain]=p_tnr_user_data[base_gain+1]=p_tnr_user_data[base_gain+2]= \
				p_tnr_user_data[base_gain+3] =p_tnr_user_data[base_gain+4]=0x0;
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadTnr2ndDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	//UINT32 base_lut[PE_NRD_O26_TNL_NUM];
	UINT32 base_user_lut, base_gain, base_buff, base_init;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_tnr2nd_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_tnr2nd_user_data = p_phys_db->tnr2nd_user.data;
		CHECK_KNULL(p_tnr2nd_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* tnr2nd_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_TNR2ND_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O26_TNR_USER_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_TNR_USER_SIZE;
			p_phys_db->tnr2nd_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr2nd_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr2nd_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr2nd_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_O26_TNR_USER_ITEM_NUM * PE_DDR_O26_TNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_tnr2nd_user_data[0]  = 0x0;
			p_tnr2nd_user_data[1]  = 0x0;
			base_user_lut = 2;
			base_gain = base_user_lut+LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			base_buff = base_gain+LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			base_init = 7;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				p_tnr2nd_user_data[base_user_lut+i] = tnr_l_lut_hd_default_o26[base_init+i].data;
			}
			p_tnr2nd_user_data[base_gain]=p_tnr2nd_user_data[base_gain+1]=p_tnr2nd_user_data[base_gain+2]= \
				p_tnr2nd_user_data[base_gain+3] =p_tnr2nd_user_data[base_gain+4]=0x0;
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_USER_T);
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
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_USER_T);
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
			pd = pp->tnr0__lut;
			printk("tnr0___en:%d\n", pp->tnr0___en);
			printk( \
			"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = pp->tnr0_gain;
			printk(\
			"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4]);
			pd = pp->tnr0_buff;
			printk(\
			"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11], pd[12], pd[13], pd[14]);
			
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnr2ndUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr2nd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR2ND_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_USER_T);
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
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnr2ndUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND2_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr2nd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR2ND_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_USER_T);
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
			pd = pp->tnr1__lut;
			printk("tnr1___en:%d\n", pp->tnr1___en);
			printk( \
			"tnr1__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = pp->tnr1_gain;
			printk(\
			"tnr1_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4]);
			pd = pp->tnr1_buff;
			printk(\
			"tnr1_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr1_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11], pd[12], pd[13], pd[14]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadTnr3rdDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	//UINT32 base_lut[PE_NRD_O26_TNL_NUM];
	UINT32 base_user_lut, base_gain, base_buff, base_init;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_tnr3rd_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_tnr3rd_user_data = p_phys_db->tnr3rd_user.data;
		CHECK_KNULL(p_tnr3rd_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* tnr3rd_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_TNR3RD_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O26_TNR_USER_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_TNR_USER_SIZE;
			p_phys_db->tnr3rd_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr3rd_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr3rd_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr3rd_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_O26_TNR_USER_ITEM_NUM * PE_DDR_O26_TNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_tnr3rd_user_data[0]  = 0x0;
			p_tnr3rd_user_data[1]  = 0x0;
			base_user_lut = 2;
			base_gain = base_user_lut+LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			base_buff = base_gain+LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			base_init = 7;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				p_tnr3rd_user_data[base_user_lut+i] = tnr_l_lut_hd_default_o26[base_init+i].data;
			}
			p_tnr3rd_user_data[base_gain]=p_tnr3rd_user_data[base_gain+1]=p_tnr3rd_user_data[base_gain+2]= \
				p_tnr3rd_user_data[base_gain+3] =p_tnr3rd_user_data[base_gain+4]=0x0;
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnr3rdUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr3rd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR3RD_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_USER_T);
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
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnr3rdUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND2_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr3rd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR3RD_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_USER_T);
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
			pd = pp->tnr1__lut;
			printk("tnr2___en:%d\n", pp->tnr1___en);
			printk( \
			"tnr2__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr2__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11],pd[12], pd[13], pd[14], pd[15]);
			pd = pp->tnr1_gain;
			printk(\
			"tnr2_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4]);
			pd = pp->tnr1_buff;
			printk(\
			"tnr2_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr2_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10], pd[11], pd[12], pd[13], pd[14]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadDnrInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dnr_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr_user_data = p_phys_db->dnr_user.data;
		CHECK_KNULL(p_dnr_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_DNR_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DNR_USER_SIZE;
			p_phys_db->dnr_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dnr_user_data[0]  = 0x0;
			p_dnr_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_DNR_USER_SIZE-base_user_lut; i++)
			{
				p_dnr_user_data[i+base_user_lut] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadDnr2ndInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dnr2nd_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr2nd_user_data = p_phys_db->dnr2nd_user.data;
		CHECK_KNULL(p_dnr2nd_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_DNR2ND_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DNR_USER_SIZE;
			p_phys_db->dnr2nd_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr2nd_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr2nd_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr2nd_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dnr2nd_user_data[0]  = 0x0;
			p_dnr2nd_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_DNR_USER_SIZE-base_user_lut; i++)
			{
				p_dnr2nd_user_data[i+base_user_lut] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR3_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->dnr_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		//CHECK_KNULL(p_phys_dnr_user_db);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DNR_USER_T);
			pp = (LX_PE_NRD_DNR3_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->dnr__ui_val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DNR_USER_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->dnr____buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DNR("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnrUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR3_CMN_T *pp = NULL;
	UINT32* pd32;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->dnr_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		//CHECK_KNULL(p_phys_dnr_user_db);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DNR_USER_T);
			pp = (LX_PE_NRD_DNR3_CMN_T *)pstParams;
			//p_db_data[1] = (UINT32)pp->dnr__ui_val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DNR_USER_SIZE-base; i++)
			{
				pp->dnr____buff[i] = p_db_data[base+i];
			}
			pd32 = pp->dnr____buff;
			printk(\
			"dnr0___buff[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * download dnr2nd user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnr2ndUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR3_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->dnr2nd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		//CHECK_KNULL(p_phys_dnr_user_db);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR2ND_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DNR_USER_T);
			pp = (LX_PE_NRD_DNR3_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->dnr__ui_val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DNR_USER_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->dnr____buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DNR("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * get dnr2nd user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_GetDnr2ndUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR3_CMN_T *pp = NULL;
	UINT32* pd32;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->dnr2nd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		//CHECK_KNULL(p_phys_dnr_user_db);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR2ND_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DNR_USER_T);
			pp = (LX_PE_NRD_DNR3_CMN_T *)pstParams;
			//p_db_data[1] = (UINT32)pp->dnr__ui_val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DNR_USER_SIZE-base; i++)
			{
				pp->dnr____buff[i] = p_db_data[base+i];
			}
			pd32 = pp->dnr____buff;
			printk(\
			"dnr1___buff[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadDnrDcntInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dcnt_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dcnt_user_data = p_phys_db->nrd_dcnt_user.data;
		CHECK_KNULL(p_dcnt_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DCNT_USER_SIZE;
			p_phys_db->nrd_dcnt_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->nrd_dcnt_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->nrd_dcnt_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->nrd_dcnt_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DCNT_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dcnt_user_data[0]  = 0x0;
			p_dcnt_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_DCNT_USER_SIZE-base_user_lut; i++)
			{
				p_dcnt_user_data[i+base_user_lut] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadDnrDcnt2ndInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dcnt2nd_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dcnt2nd_user_data = p_phys_db->nrd_dcnt2nd_user.data;
		CHECK_KNULL(p_dcnt2nd_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT2ND_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DCNT_USER_SIZE;
			p_phys_db->nrd_dcnt2nd_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->nrd_dcnt2nd_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->nrd_dcnt2nd_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->nrd_dcnt2nd_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DCNT_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dcnt2nd_user_data[0]  = 0x0;
			p_dcnt2nd_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_DCNT_USER_SIZE-base_user_lut; i++)
			{
				p_dcnt2nd_user_data[i+base_user_lut] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrDcntUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT3_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->nrd_dcnt_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DCNT_USER_T);
			pp = (LX_PE_NRD_DCNT3_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->deconnd_ui_val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_USER_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->deconnd___buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DNR("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnrDcntUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT3_CMN_T *pp = NULL;
	UINT32* pd32;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->nrd_dcnt_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DCNT_USER_T);
			pp = (LX_PE_NRD_DCNT3_CMN_T *)pstParams;
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_USER_SIZE-base; i++)
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
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * download dcnt2nd user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrDcnt2ndUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT3_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->nrd_dcnt2nd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT2ND_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DCNT_USER_T);
			pp = (LX_PE_NRD_DCNT3_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->deconnd_ui_val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_USER_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->deconnd___buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DEC("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * get dcnt2nd user db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_GetDnrDcnt2ndUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT3_CMN_T *pp = NULL;
	UINT32* pd32;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->nrd_dcnt2nd_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT2ND_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DCNT_USER_T);
			pp = (LX_PE_NRD_DCNT3_CMN_T *)pstParams;
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_USER_SIZE-base; i++)
			{
				pp->deconnd___buff[i] = p_db_data[base+i];
			}
			pd32 = pp->deconnd___buff;
			printk(\
			"2nd deconnd___buff[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadCCODcntInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dcnt_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dcnt_user_data = p_phys_db->led_dcnt_user.data;
		CHECK_KNULL(p_dcnt_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_LED_DCNT_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DCNT_LED_USER_SIZE;
			p_phys_db->led_dcnt_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->led_dcnt_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->led_dcnt_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->led_dcnt_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DCNT_LED_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dcnt_user_data[0]  = 0x0;
			p_dcnt_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i=2; i<PE_DDR_O26_DCNT_LED_USER_SIZE; i++)
			{
				p_dcnt_user_data[i] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
static int PE_NRD_HW_O26_DownloadCCODcntUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_CCO_DCNT1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->led_dcnt_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_LED_DCNT_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DCNT_LED_USER_T);
			pp = (LX_PE_CCO_DCNT1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->deconnd_ui_val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_LED_USER_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->deconcco__buff[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DEC("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetCCODcntUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_CCO_DCNT1_CMN_T *pp = NULL;
	UINT32* pd32;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->led_dcnt_user.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_LED_DCNT_USER;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DCNT_LED_USER_T);
			pp = (LX_PE_CCO_DCNT1_CMN_T *)pstParams;
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_LED_USER_SIZE-base; i++)
			{
				pp->deconcco__buff[i] = p_db_data[base+i];
			}
			pd32 = pp->deconcco__buff;
			printk(\
			"deconled__buff[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadTnrSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_tnr_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_tnr_sqm_data = p_phys_db->tnr_sqm.data;
		CHECK_KNULL(p_tnr_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_TNR_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_TNR_SQM_SIZE;
			p_phys_db->tnr_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_TNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_tnr_sqm_data[0]  = 0x0;
			p_tnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_TNR_SQM_SIZE-base_user_lut; i++)
			{
				p_tnr_sqm_data[i+base_user_lut] = sqm_tnr_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnrSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->tnr___val;
			base = 2;
			for (i=0; i<PE_DDR_O26_TNR_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->tnr0__sqm[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnrSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR_SQM1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR_SQM1_CMN_T *)pstParams;
			pp->tnr___val = (UINT8)p_db_data[1] ;
			base = 2;
			for (i=0; i<PE_DDR_O26_TNR_SQM_SIZE-base; i++)
			{
				pp->tnr0__sqm[i] = p_db_data[base+i];
			}
			pd = pp->tnr0__sqm;
			printk("tnr0__sqm:%d\n", pp->tnr___val);
			printk( \
			"tnr0__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__sqm[10]0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * download tnr 2nd db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_DownloadTnr2ndSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_tnr_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_tnr_sqm_data = p_phys_db->tnr2nd_sqm.data;
		CHECK_KNULL(p_tnr_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_TNR2ND_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_TNR_SQM_SIZE;
			p_phys_db->tnr2nd_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr2nd_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr2nd_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr2nd_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_TNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_tnr_sqm_data[0]  = 0x0;
			p_tnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_TNR_SQM_SIZE-base_user_lut; i++)
			{
				p_tnr_sqm_data[i+base_user_lut] = sqm_tnr2nd_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnr2ndSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr2nd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR2ND_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR2ND_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->tnr___val;
			base = 2;
			for (i=0; i<PE_DDR_O26_TNR_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->tnr1__sqm[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnr2ndSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr2nd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR2ND_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR2ND_SQM1_CMN_T *)pstParams;
			pp->tnr___val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O26_TNR_SQM_SIZE-base; i++)
			{
				pp->tnr1__sqm[i] = p_db_data[base+i];
			}
			pd = pp->tnr1__sqm;
			printk("2nd tnr1__sqm:%d\n", pp->tnr___val);
			printk( \
			"2nd tnr1__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"2nd tnr1__sqm[10]0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadTnr3rdSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr3rd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR3RD_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR2ND_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->tnr___val;
			base = 2;
			for (i=0; i<PE_DDR_O26_TNR_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->tnr1__sqm[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_NRD("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetTnr3rdSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_TNR2ND_SQM1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->tnr3rd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_TNR3RD_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_TNR_SQM_T);
			pp = (LX_PE_NRD_TNR2ND_SQM1_CMN_T *)pstParams;
			pp->tnr___val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O26_TNR_SQM_SIZE-base; i++)
			{
				pp->tnr1__sqm[i] = p_db_data[base+i];
			}
			pd = pp->tnr1__sqm;
			printk("3rd tnr2__sqm:%d\n", pp->tnr___val);
			printk( \
			"3rd tnr2__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"3rd tnr2__sqm[10]0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], \
			pd[8],	pd[9],	pd[10]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * download tnr 3rd db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_DownloadTnr3rdSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_tnr3rd_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_tnr3rd_sqm_data = p_phys_db->tnr3rd_sqm.data;
		CHECK_KNULL(p_tnr3rd_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_TNR3RD_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_TNR_SQM_SIZE;
			p_phys_db->tnr3rd_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr3rd_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr3rd_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr3rd_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_TNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_tnr3rd_sqm_data[0]  = 0x0;
			p_tnr3rd_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_TNR_SQM_SIZE-base_user_lut; i++)
			{
				p_tnr3rd_sqm_data[i+base_user_lut] = sqm_tnr2nd_init_o26[i]; //use same DB tnr 2nd
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * download dnr sqm db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_DownloadDnrSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dnr_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr_sqm_data = p_phys_db->dnr_sqm.data;
		CHECK_KNULL(p_dnr_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_DNR_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DNR_SQM_SIZE;
			p_phys_db->dnr_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dnr_sqm_data[0]  = 0x0;
			p_dnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_DNR_SQM_SIZE-base_user_lut; i++)
			{
				p_dnr_sqm_data[i+base_user_lut] = sqm_dnr_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR_SQM3_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_SQM;
			pp = (LX_PE_NRD_DNR_SQM3_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->dnr_____val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DNR_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->dnr___sqmui[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DNR("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnrSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i;
	UINT32 base;
	LX_PE_NRD_DNR_SQM3_CMN_T *pp = NULL;
	UINT32 *pd;
	__attribute__((unused)) PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			pp = (LX_PE_NRD_DNR_SQM3_CMN_T *)pstParams;
			pp->dnr_____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O26_DNR_SQM_SIZE-base; i++)
			{
				pp->dnr___sqmui[i] = p_db_data[base+i];
			}
			pd = pp->dnr___sqmui;
			printk("dnr___sqmui:%d\n", pp->dnr_____val);
			printk( \
			"dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * download dnr2nd sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnr2ndSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, sec_typ;
	UINT32 base;
	LX_PE_NRD_DNR_SQM2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr2nd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR2ND_SQM;
			pp = (LX_PE_NRD_DNR_SQM2_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->dnr_____val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DNR2ND_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->dnr___sqmui[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DNR("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DNR("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnr2ndSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i;
	UINT32 base;
	LX_PE_NRD_DNR_SQM2_CMN_T *pp = NULL;
	UINT32 *pd;
	__attribute__((unused)) PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr2nd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			pp = (LX_PE_NRD_DNR_SQM2_CMN_T *)pstParams;
			pp->dnr_____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O26_DNR2ND_SQM_SIZE-base; i++)
			{
				pp->dnr___sqmui[i] = p_db_data[base+i];
			}
			pd = pp->dnr___sqmui;
			printk("2nd dnr___sqmui:%d\n", pp->dnr_____val);
			printk( \
			"2nd dnr___sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"2nd dnr___sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * download dnr2nd sqm db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_DownloadDnr2ndSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dnr2nd_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr2nd_sqm_data = p_phys_db->dnr2nd_sqm.data;
		CHECK_KNULL(p_dnr2nd_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_DNR2ND_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DNR_SQM_SIZE;
			p_phys_db->dnr2nd_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr2nd_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr2nd_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr2nd_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dnr2nd_sqm_data[0]  = 0x0;
			p_dnr2nd_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_DNR_SQM_SIZE-base_user_lut; i++)
			{
				p_dnr2nd_sqm_data[i+base_user_lut] = sqm_dnr_init_o26[i]; // use same db as dnr 1
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_DownloadDnrDcntSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dnr_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr_sqm_data = p_phys_db->dnr_dcnt_sqm.data;
		CHECK_KNULL(p_dnr_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DCNT_SQM_SIZE;
			p_phys_db->dnr_dcnt_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_dcnt_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_dcnt_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_dcnt_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DCNT_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dnr_sqm_data[0]  = 0x0;
			p_dnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_DCNT_SQM_SIZE-base_user_lut; i++)
			{
				p_dnr_sqm_data[i+base_user_lut] = sqm_dct_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrDcntSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT_SQM2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_dcnt_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			pp = (LX_PE_NRD_DCNT_SQM2_CMN_T *)pstParams;
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT_SQM;
			p_db_data[1] = (UINT32)pp->deconnd____val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->deconnd__sqmui[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DEC("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnrDcntSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT_SQM2_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_dcnt_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_DCNT_SQM_T);
			pp = (LX_PE_NRD_DCNT_SQM2_CMN_T *)pstParams;
			pp->deconnd____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_SQM_SIZE-base; i++)
			{
				pp->deconnd__sqmui[i] = p_db_data[base+i];
			}
			pd = pp->deconnd__sqmui;
			printk("deconnd__sqmui:%d\n", pp->deconnd____val);
			printk( \
			"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14],	pd[15],  pd[16],  pd[17], pd[18],  pd[19],\
			pd[20],  pd[21],  pd[22],  pd[23], pd[24],	pd[25],  pd[26]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * download nrd dcnt2nd sqm db
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadDnrDcnt2ndSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT_SQM2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_dcnt2nd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			pp = (LX_PE_NRD_DCNT_SQM2_CMN_T *)pstParams;
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT2ND_SQM;
			p_db_data[1] = (UINT32)pp->deconnd____val;
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->deconnd__sqmui[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DEC("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26_GetDnrDcnt2ndSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, sec_typ;
	UINT32 base;
	LX_PE_NRD_DCNT_SQM2_CMN_T *pp = NULL;
	UINT32 *pd;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->dnr_dcnt2nd_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT2ND_SQM;
			pp = (LX_PE_NRD_DCNT_SQM2_CMN_T *)pstParams;
			pp->deconnd____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O26_DCNT_SQM_SIZE-base; i++)
			{
				pp->deconnd__sqmui[i] = p_db_data[base+i];
			}
			pd = pp->deconnd__sqmui;
			printk("2nd deconnd__sqmui:%d\n", pp->deconnd____val);
			printk( \
			"2nd deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"2nd deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"2nd deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
			pd[10],  pd[11],  pd[12],  pd[13], pd[14],	pd[15],  pd[16],  pd[17], pd[18],  pd[19],\
			pd[20],  pd[21],  pd[22],  pd[23], pd[24],	pd[25],  pd[26]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * download dnr dcnt 2md db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_DownloadDnrDcnt2ndSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_dcnt2nd_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dcnt2nd_sqm_data = p_phys_db->dnr_dcnt2nd_sqm.data;
		CHECK_KNULL(p_dcnt2nd_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_DNR_DCNT2ND_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_DCNT_SQM_SIZE;
			p_phys_db->dnr_dcnt2nd_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_dcnt2nd_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_dcnt2nd_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_dcnt2nd_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_DCNT_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_dcnt2nd_sqm_data[0]  = 0x0;
			p_dcnt2nd_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_DCNT_SQM_SIZE-base_user_lut; i++)
			{
				p_dcnt2nd_sqm_data[i+base_user_lut] = sqm_dct_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

/**
 * download cco dcnt db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_DownloadCCODcntSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_cco_dcnt_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_cco_dcnt_sqm_data = p_phys_db->cco_dcnt_sqm.data;
		CHECK_KNULL(p_cco_dcnt_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26_SEC_CCO_DCNT_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26_CCODCNT_SQM_SIZE;
			p_phys_db->cco_dcnt_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->cco_dcnt_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->cco_dcnt_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->cco_dcnt_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26_CCODCNT_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26_HEADER_T);
			/* wr ddr */
			p_cco_dcnt_sqm_data[0]  = 0x0;
			p_cco_dcnt_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26_CCODCNT_SQM_SIZE-base_user_lut; i++)
			{
				p_cco_dcnt_sqm_data[i+base_user_lut] = 0;//sqm_dct_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
__attribute__((unused)) static int PE_NRD_HW_O26_DownloadCCODcntSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_CCO_DCNT_SQM1_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->cco_dcnt_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_CCO_DCNT_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_CCODCNT_SQM_T);
			pp = (LX_PE_CCO_DCNT_SQM1_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->deconnd____val;
			base = 2;
			for (i=0; i<PE_DDR_O26_CCODCNT_SQM_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->deconcco_sqmui[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_DBG_DEC("%s: DL done.(base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O26_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ], count);
		}
		else
		{
			PE_DBG_DEC("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}


/**
 * get led dcnt sqm db 
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_O26_GetCCODcntSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_CCO_DCNT_SQM1_CMN_T *pp = NULL;
	UINT32 *pd;
	PE_DDR_DB_SHDW_REG_O26_T *p_shdw_db = gPE_DDR_DB_O26.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26_T *p_phys_db = gPE_DDR_DB_O26.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->cco_dcnt_sqm.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O26)
		{
			sec_typ = PE_DDR_O26_SEC_CCO_DCNT_SQM;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O26_CCODCNT_SQM_T);
			pp = (LX_PE_CCO_DCNT_SQM1_CMN_T *)pstParams;
			pp->deconnd____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O26_CCODCNT_SQM_SIZE-base; i++)
			{
				pp->deconcco_sqmui[i] = p_db_data[base+i];
			}
			pd = pp->deconcco_sqmui;
			printk("deconcco_sqmui:%d\n", pp->deconnd____val);
			printk( \
				"deconcco_sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"deconcco_sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"deconcco_sqmui[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"deconcco_sqmui[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n", \
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7],pd[8],  pd[9],\
				pd[10],  pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19],\
				pd[20],  pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26],  pd[27], pd[28],  pd[29],\
				pd[30],  pd[31],  pd[32],  pd[33], pd[34]);
		}
		else
		{
			printk("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_DownloadTnrDb(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_lut[PE_NRD_O26_TNL_NUM];
	UINT32 base_user_lut, base_gain, base_buff, base_init;
	PE_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_DDR_DB_O26F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_tnr_lut_data  = NULL;
	volatile UINT32 *p_tnr_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_tnr_lut_data  = p_phys_db->tnr_lut.data;
		CHECK_KNULL(p_tnr_lut_data );
		p_tnr_user_data = p_phys_db->tnr_user.data;
		CHECK_KNULL(p_tnr_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* tnr_lut **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_TNR_LUT;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O26F22_TNR_LUT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_TNR_LUT_SIZE;
			p_phys_db->tnr_lut.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_lut.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_lut.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_lut.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_O26F22_TNR_LUT_ITEM_NUM * PE_DDR_O26F22_TNR_LUT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			base_lut[0] = 0;									//PE_NRD_O26F22_TNL_HD
			base_lut[1] = base_lut[0]+PE_DDR_O26F22_TNR_LUT_SIZE;	//PE_NRD_O26F22_TNL_SD
			base_lut[2] = base_lut[1]+PE_DDR_O26F22_TNR_LUT_SIZE;	//PE_NRD_O26F22_TNL_UD
			base_lut[3] = base_lut[2]+PE_DDR_O26F22_TNR_LUT_SIZE;	//PE_NRD_O26F22_TNL_CAM_HD
			for (i=0; i<PE_DDR_O26F22_TNR_LUT_SIZE; i++)
			{
				p_tnr_lut_data[base_lut[0]+i] = tnr_l_lut_hd_default_o26[i].data;
				p_tnr_lut_data[base_lut[1]+i] = tnr_l_lut_sd_default_o26[i].data;
				p_tnr_lut_data[base_lut[2]+i] = tnr_l_lut_ud_default_o26[i].data;
				p_tnr_lut_data[base_lut[3]+i] = tnr_l_lut_cam_hd_default_o26[i].data;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
			#if 1
			/* tnr_user **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_TNR_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O26F22_TNR_USER_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_TNR_USER_SIZE;
			p_phys_db->tnr_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_O26F22_TNR_USER_ITEM_NUM * PE_DDR_O26F22_TNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			p_tnr_user_data[0]  = 0x0;
			p_tnr_user_data[1]  = 0x0;
			base_user_lut = 2;
			base_gain = base_user_lut+LX_PE_NRD_TNR1_CMN_LUT__SIZE;
			base_buff = base_gain+LX_PE_NRD_TNR1_CMN_GAIN_SIZE;
			base_init = 7;
			for (i=0; i<LX_PE_NRD_TNR1_CMN_LUT__SIZE; i++)
			{
				p_tnr_user_data[base_user_lut+i] = tnr_l_lut_hd_default_o26[base_init+i].data;
			}
			p_tnr_user_data[base_gain]=p_tnr_user_data[base_gain+1]=p_tnr_user_data[base_gain+2]= \
				p_tnr_user_data[base_gain+3] =p_tnr_user_data[base_gain+4]=0x0;
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
			#endif
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_DownloadTnrSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_DDR_DB_O26F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_tnr_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_tnr_sqm_data = p_phys_db->tnr_sqm.data;
		CHECK_KNULL(p_tnr_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_TNR_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_TNR_SQM_SIZE;
			p_phys_db->tnr_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->tnr_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->tnr_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->tnr_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26F22_TNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			p_tnr_sqm_data[0]  = 0x0;
			p_tnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26F22_TNR_SQM_SIZE-base_user_lut; i++)
			{
				p_tnr_sqm_data[i+base_user_lut] = sqm_tnr_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_DownloadDnrInitDb(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_DDR_DB_O26F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_dnr_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr_user_data = p_phys_db->dnr_user.data;
		CHECK_KNULL(p_dnr_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_DNR_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_DNR_USER_SIZE;
			p_phys_db->dnr_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26F22_DNR_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			p_dnr_user_data[0]  = 0x0;
			p_dnr_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26F22_DNR_USER_SIZE-base_user_lut; i++)
			{
				p_dnr_user_data[i+base_user_lut] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_DownloadDnrSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_DDR_DB_O26F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_dnr_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr_sqm_data = p_phys_db->dnr_sqm.data;
		CHECK_KNULL(p_dnr_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_DNR_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_DNR_SQM_SIZE;
			p_phys_db->dnr_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26F22_DNR_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			p_dnr_sqm_data[0]  = 0x0;
			p_dnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26F22_DNR_SQM_SIZE-base_user_lut; i++)
			{
				p_dnr_sqm_data[i+base_user_lut] = sqm_dnr_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_DownloadDnrDcntInitDb(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_DDR_DB_O26F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_dcnt_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dcnt_user_data = p_phys_db->nrd_dcnt_user.data;
		CHECK_KNULL(p_dcnt_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_DNR_DCNT_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_DCNT_USER_SIZE;
			p_phys_db->nrd_dcnt_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->nrd_dcnt_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->nrd_dcnt_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->nrd_dcnt_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26F22_DCNT_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			p_dcnt_user_data[0]  = 0x0;
			p_dcnt_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26F22_DCNT_USER_SIZE-base_user_lut; i++)
			{
				p_dcnt_user_data[i+base_user_lut] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_DownloadDnrDcntSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_DDR_DB_O26F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_dnr_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr_sqm_data = p_phys_db->dnr_dcnt_sqm.data;
		CHECK_KNULL(p_dnr_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_DNR_DCNT_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_DCNT_SQM_SIZE;
			p_phys_db->dnr_dcnt_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->dnr_dcnt_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->dnr_dcnt_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->dnr_dcnt_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26F22_DCNT_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			p_dnr_sqm_data[0]  = 0x0;
			p_dnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O26F22_DCNT_SQM_SIZE-base_user_lut; i++)
			{
				p_dnr_sqm_data[i+base_user_lut] = sqm_dct_init_o26[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_DownloadLedDcntInitDb(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_DDR_DB_O26F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_dcnt_user_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dcnt_user_data = p_phys_db->led_dcnt_user.data;
		CHECK_KNULL(p_dcnt_user_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_LED_DCNT_USER;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_DCNT_LED_USER_SIZE;
			p_phys_db->led_dcnt_user.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->led_dcnt_user.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->led_dcnt_user.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->led_dcnt_user.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26F22_DCNT_LED_USER_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			p_dcnt_user_data[0]  = 0x0;
			p_dcnt_user_data[1]  = 0x0;
			base_user_lut = 2;
			for (i=2; i<PE_DDR_O26F22_DCNT_LED_USER_SIZE; i++)
			{
				p_dcnt_user_data[i] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_DownloadLedDcntSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O26F22_T *p_shdw_db = gPE_DDR_DB_O26F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O26F22_T *p_phys_db = gPE_DDR_DB_O26F22.phys.data;
	volatile UINT32 *p_dnr_sqm_data = NULL;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_dnr_sqm_data = p_phys_db->led_dcnt_sqm.data;
		CHECK_KNULL(p_dnr_sqm_data);
		if (PE_KDRV_VER_O26)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O26F22_SEC_LED_DCNT_SQM;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O26F22_DCNT_SQM_SIZE;
			p_phys_db->led_dcnt_sqm.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->led_dcnt_sqm.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->led_dcnt_sqm.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->led_dcnt_sqm.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O26F22_DCNT_SQM_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O26F22_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O26F22_HEADER_T);
			/* wr ddr */
			p_dnr_sqm_data[0]  = 0x0;
			p_dnr_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i=2; i<PE_DDR_O26F22_DCNT_SQM_SIZE; i++)
			{
				p_dnr_sqm_data[i] = 0x0;
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O26F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}
/**
 * set dnr common all ctrl
 * - use input struct LX_PE_NRD_DNR_ALL_CMN_T for O26F22
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_HW_O26F22_SetDnrCmnAllCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT8 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DNR_CMN_T *ctrl_param =(LX_PE_NRD_DNR_CMN_T *)pstParams;
			LX_PE_NRD_DNR_ALL_CMN_T *pp = (LX_PE_NRD_DNR_ALL_CMN_T *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			PE_DBG_NRD("win : %d,check_win : %d\n",pp->win_id, PE_CHECK_WIN2(pp->win_id));
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
			pd = pp->dnr_____mnr;
			PE_DBG_NRD("set[%d] : dnr_____mnr\n"
			"dnr_____mnr	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

			pd = pp->dnr___dcbnr;
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

			pd = pp->dnr___acbnr;
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
			if(PE_CHECK_WIN2(pp->win_id))
			{
				#ifdef PE_HW_O26_CHIPINFO_TABLE	/* O26F22_TBL */
				PE_CHPI_DNR_HW_O26F22_SetCtrl(pstParams);
				#endif
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

int PE_NRD_HW_O26F22_SetTnrCmnAllCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT8 *pd;
	__attribute__((unused)) UINT16 *pd16;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_TNR_CMN_T *ctrl_param =(LX_PE_NRD_TNR_CMN_T *)pstParams;
			LX_PE_NRD_TNR_ALL_CMN_T *pp = (LX_PE_NRD_TNR_ALL_CMN_T *)ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			pd32 = pp->tnr0__lut;
			PE_DBG_NRD("[%d]tnr0___en:%d\n", pp->win_id, pp->tnr0___en);
			PE_DBG_NRD( \
			"tnr0__lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__lut[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pd32[0],  pd32[1],  pd32[2],  pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
			pd32[8],  pd32[9],  pd32[10], pd32[11],pd32[12], pd32[13], pd32[14], pd32[15]);
			pd32 = pp->tnr0_gain;
			PE_DBG_NRD(\
			"tnr0_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd32[0],  pd32[1],  pd32[2],  pd32[3], pd32[4]);
			pd32 = pp->tnr0_buff;
			PE_DBG_NRD(\
			"tnr0_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd32[0],  pd32[1],  pd32[2],  pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
			pd32[8],  pd32[9],  pd32[10], pd32[11],	pd32[12], pd32[13], pd32[14]);

			pd = pp->tnr0__ctl;
			PE_DBG_NRD("set[%d] : tnr0__ctl\n"
			"tnr0__ctl	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__ctl	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0__ctl	  [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);

			pd = pp->tnr0___ma;
			PE_DBG_NRD("set[%d] : tnr0___ma\n"
			"tnr0___ma    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			
			pd = pp->tnr0___me;
			PE_DBG_NRD("set[%d] : tnr0___me\n"
			"tnr0___me	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->tnr0__mlb;
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

			pd = pp->tnr0_blnd;
			PE_DBG_NRD("set[%d] : tnr0_blnd\n"
			"tnr0_blnd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0_blnd	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"tnr0_blnd	  [20]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23]);
			
			pd32 = pp->tnr0__sqm;
			PE_DBG_NRD("[%d]tnr0__sqm:%d\n", pp->win_id, pp->tnr___val);
			PE_DBG_NRD( \
			"tnr0__sqm[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr0__sqm[10]0x%08X\n", \
			pd32[0],  pd32[1],  pd32[2],  pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], \
			pd32[8],  pd32[9],  pd32[10]);
			if(PE_CHECK_WIN2(pp->win_id))
			{
				#ifdef PE_HW_O26_CHIPINFO_TABLE	/* O26F22_TBL */
				PE_CHPI_TNR_HW_O26F22_SetCtrl(pstParams);
				#endif
			}
 		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
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
int PE_NRD_HW_O26F22_SetDnrDcntCmnAllCtrl(void *pstParams)
{
	int ret = RET_OK;
	#if 0 //def PE_HW_O26_BRINGUP
	UINT8  *pd8;
	UINT16 *pd;
	UINT32 *pd32;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O26)
		{
			LX_PE_NRD_DCNT_CMN_T *ctrl_param =(LX_PE_NRD_DCNT_CMN_T *)pstParams;
			LX_PE_NRD_DCNT1_ALL_CMN_T *pp = (LX_PE_NRD_DCNT1_ALL_CMN_T *)ctrl_param->data;
			static LX_PE_NRD_DCNT1_ALL_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
			__attribute__((unused)) static UINT32 chk = 0x0;
			PE_CHECK_WINID(pp->win_id);
			PE_CHECK_DUPLICATE(LX_PE_NRD_DCNT1_ALL_CMN_T);
			if(pp->win_id > LX_PE_WIN_ALL)
			{
				PE_DBG_NRD("duplicated DB : LX_PE_NRD_DCNT1_ALL_CMN_T\n");
				ret=RET_OK;
				break;
			}
			PE_DBG_NRD("win : %d,check_win : %d\n",pp->win_id, PE_CHECK_WIN2(pp->win_id));
			PE_DBG_NRD("set[%d] : oper:0x%02X, size: 0x%02X\n",\
			pp->win_id, \
			ctrl_param->oper, ctrl_param->size);
			pd32 = pp->deconnd_____ui;
			PE_DBG_NRD("set[%d] : deconnd_____ui\n"
			"deconnd_____ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"deconnd_____ui    [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7], pd32[8], pd32[9],\
			pd32[10], pd32[11], pd32[12], pd32[13]);
			pd32 = pp->deconnd___buff;
			PE_DBG_NRD("set[%d] : deconnd___buff\n"\
			"deconnd___buff    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd32[0], pd32[1], pd32[2], pd32[3], pd32[4], pd32[5], pd32[6], pd32[7]);
			pd = pp->deconnd____cmn;
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
			pd32 = pp->deconnd__sqmui;
			PE_DBG_NRD("set[%d]deconnd__sqmui:%d\n", pp->win_id, pp->deconnd_ui_val);
			PE_DBG_NRD( "\n"\
			"deconnd__sqmui[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"deconnd__sqmui[20]0x%08X,0x%08X,0x%08X,\n", \
			pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7],pd32[8],  pd32[9],\
			pd32[10],  pd32[11],  pd32[12],  pd32[13], pd32[14],	pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19],\
			pd32[20],  pd32[21],  pd32[22]);
			if(PE_CHECK_WIN2(pp->win_id))
			{
				#ifdef PE_HW_O26_CHIPINFO_TABLE	/* O26F22_TBL */
				PE_CHPI_DNR_HW_O26F22_SetDcntCtrl(pstParams);
				#endif
			}
		}
		else
		{
			PE_DBG_NRD("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O26_BRINGUP*/
	return ret;
}

