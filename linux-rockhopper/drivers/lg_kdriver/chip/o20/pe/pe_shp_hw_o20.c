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

/** @file pe_shp_hw_o20.c
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
#undef PE_SHP_HW_O20_SR_PWD_TRACE

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

#include "pe_hw_o20.h"
#include "pe_reg_o20.h"
#include "pe_fwi_o20.h"
#include "pe_cmn_hw_o20.h"
#include "pe_hst_hw_o20.h"
#include "pe_shp_hw_o20.h"
#include "pe_chpi_shp_hw_f20.h"
#include "pe_chpi_dnr_hw_f20.h"
#include "pe_chpi_obc_hw_f20.h"
#include "pe_res_hw_param_o20.h"
#include "pe_cti_dnr_hw_param_o20.h"
#include "pe_pblur_dnr_hw_param_o20.h"
#include "cvd_module.h"

/* core hw param */
#include "pe_shp_scl256_def.h"

#ifdef PE_SHP_HW_O20_SR_PWD_TRACE
#include "../../sys/sys_regs.h"
#endif

#include "pe_shp_l_sd_default_o20.h"
#include "pe_shp_l_hd_default_o20.h"
#include "pe_shp_l_ud_default_o20.h"
#include "pe_sre_2k_res_sd_default_o20.h"
#include "pe_sre_2k_res_hd_default_o20.h"
#include "pe_sre_2k_res_ud_default_o20.h"
#include "pe_sre_chr_res_sd_default_o20.h"
#include "pe_sre_chr_res_hd_default_o20.h"
#include "pe_sre_chr_res_ud_default_o20.h"
#include "pe_vsdpspgain_sd_default_o20.h"
#include "pe_vsdpspgain_hd_default_o20.h"
#include "pe_vsdpspgain_ud_default_o20.h"
#include "pe_vsdpsptop_sd_default_o20.h"
#include "pe_vsdpsptop_hd_default_o20.h"
#include "pe_vsdpsptop_ud_default_o20.h"
#include "pe_osdsr_default_o20.h"

#include "pe_cti_y_l_hd_default_o20.h"
#include "pe_cti_y_l_sd_default_o20.h"
#include "pe_cti_y_l_vr_360_default_o20.h"
#include "pe_cti_y_l_atv_default_o20.h"
#include "pe_cti_y_l_ud_default_o20.h"

#include "pe_sqm_shp_2k_cmn_init_o20.h"
#include "pe_sqm_shp_2k_dtl_init_o20.h"
#include "pe_sqm_shp_vsd_cmn_init_o20.h"
#include "pe_sqm_shp_vsd_dtl_init_o20.h"

#include "pe_obc_face_l_sd_default_o20.h"
#include "pe_obc_face_l_hd_default_o20.h"
#include "pe_obc_face_l_ud_default_o20.h"

#include "pe_obc_objt_l_sd_default_o20.h"
#include "pe_obc_objt_l_hd_default_o20.h"
#include "pe_obc_objt_l_ud_default_o20.h"

#include "pe_rce_face_l_sd_default_o20.h"
#include "pe_rce_face_l_hd_default_o20.h"
#include "pe_rce_face_l_ud_default_o20.h"

#include "pe_rce_objt_l_sd_default_o20.h"
#include "pe_rce_objt_l_hd_default_o20.h"
#include "pe_rce_objt_l_ud_default_o20.h"

#include "pe_shp_l_sd_default_o20_8k.h"
#include "pe_shp_l_hd_default_o20_8k.h"
#include "pe_shp_l_ud_default_o20_8k.h"

//f20
#include "pe_shp_l_sd_default_f20.h"
#include "pe_shp_l_hd_default_f20.h"
#include "pe_shp_l_ud_default_f20.h"

#include "pe_cti_y_l_hd_default_f20.h"
#include "pe_cti_y_l_sd_default_f20.h"
#include "pe_cti_y_l_vr_360_default_f20.h"
#include "pe_cti_y_l_atv_default_f20.h"
#include "pe_cti_y_l_ud_default_f20.h"

#include "pe_obc_face_l_sd_default_f20.h"
#include "pe_obc_face_l_hd_default_f20.h"
#include "pe_obc_face_l_ud_default_f20.h"

#include "pe_obc_objt_l_sd_default_f20.h"
#include "pe_obc_objt_l_hd_default_f20.h"
#include "pe_obc_objt_l_ud_default_f20.h"

#include "pe_rce_face_l_sd_default_f20.h"
#include "pe_rce_face_l_hd_default_f20.h"
#include "pe_rce_face_l_ud_default_f20.h"

#include "pe_rce_objt_l_sd_default_f20.h"
#include "pe_rce_objt_l_hd_default_f20.h"
#include "pe_rce_objt_l_ud_default_f20.h"

#include "pe_sqm_shp_vsd_cmn_init_f20.h"
#include "pe_sqm_shp_vsd_dtl_init_f20.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_HW_O20_FHD_H_MAX					1920
#define PE_SHP_HW_O20_FHD_V_MAX					1080
#define PE_SHP_HW_O20_SCL_IN_H_MIN				160
#define PE_SHP_HW_O20_SCL_IN_V_MIN				120
#define PE_SHP_HW_O20_IDX_Y_DFLT				15
#define PE_SHP_HW_O20_IDX_C_DFLT				39

#define PE_SHP_HW_O20_SCL_SIZE_MIN				(10)
#define PE_SHP_HW_O20_SCL_SIZE_1K				(1024)
#define PE_SHP_HW_O20_SCL_SIZE_2K				(2048)
#define PE_SHP_HW_O20_SCL_VSC_MD_V12TAP			(12)
#define PE_SHP_HW_O20_SCL_VSC_MD_V06TAP			(6)
#define PE_SHP_HW_O20_SCL_VSC_MD_V02TAP			(2)
#define PE_SHP_HW_O20_SCL_VSC_MD_V08TAP			(8)
#define PE_SHP_HW_O20_SCL_VSC_MD_V04TAP			(4)
#define PE_SHP_HW_O20_SCL_ADAPTIVE_ON			(0x1)
#define PE_SHP_HW_O20_SCL_ADAPTIVE_OFF			(0x0)
#define PE_SHP_HW_O20_SCL_BILINEAR				(0x1)
#define PE_SHP_HW_O20_SCL_POLYPHASE				(0x0)
#define PE_SHP_HW_O20_SCL_C_FMT_444				(0x6)
#define PE_SHP_HW_O20_SCL_C_FMT_422				(0x5)
#define PE_SHP_HW_O20_SCL_C_FMT_420				(0x4)
#define PE_SHP_HW_O20_SCL_PXL_RP_OFF			(0x0)
#define PE_SHP_HW_O20_SCL_PXL_RP_RED			(0x1)
#define PE_SHP_HW_O20_SCL_PXL_RP_GRN			(0x2)
#define PE_SHP_HW_O20_SCL_PXL_RP_BLU			(0x3)
#define PE_SHP_HW_O20_SCL_CO_REG_INC_MAX		(128)
#define PE_SHP_HW_O20_SCL_G0Y					0
#define PE_SHP_HW_O20_SCL_G1Y					1
#define PE_SHP_HW_O20_SCL_G0C					2
#define PE_SHP_HW_O20_SCL_G1C					3
#define PE_SHP_HW_O20_SCL_P0Y					4
#define PE_SHP_HW_O20_SCL_DWN_LVL_NORM			(0)
#define PE_SHP_HW_O20_SCL_DWN_LVL_HALF			(1)
#define PE_SHP_HW_O20_SCL_DWN_LVL_QUAD			(2)
#define PE_SHP_HW_O20_SCL_DWN_LVL_OCTA			(3)

/* h,v only(define) vs. both(undef), Now we use both mode until getting c08t scl has no problem. */
#define PE_SHP_HW_O20_USE_V12TM_C08T_SEPARATE_HV

/* use MSR vs. SSC on venc mode, We are going to use SSC from O20A0. */
#undef PE_SHP_HW_O20_USE_MSR_FOR_VENC_ON

/* use define until shp f/w ready, O20A0 */
#define PE_SHP_HW_O20A_SET_FW_PARAM_TO_REG_DIRECTLY
#define PE_SHP_HW_O20_SET_FW_PARAM_TO_REG_DIRECTLY


/* 20140616, sj.youm, pe1_lap_h 1,2,4 not available because of rtl bug. set valid value(0,3,5) */
#undef PE_SHP_HW_O20_PROTECT_SP_LAP_H_MODE_BUG

/* 20141006, sj.youm, sre shp write only mode */
#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
#define PE_SHP_HW_O20_SRE_SHP_WR_ONLY_MD
#else
#undef PE_SHP_HW_O20_SRE_SHP_WR_ONLY_MD
#endif

/* 20141009, sj.youm, use sre shp write only mode */
#define PE_SHP_HW_O20_USE_SRE_SHP_WR_ONLY_MD

/* use internal scl filter coeff decision */
#define PE_SHP_HW_O20_SCL_CO_INTERNAL_DECISION

/* use shp L fw dummy reg for fw gsc ctrl write */
#undef PE_SHP_HW_O20_USE_FWS_REG_FOR_FW_GSC_WR

/* set motion shp enable by f/w */
#define PE_SHP_HW_O20_SHP_MOTION_ENABLE

#define PE_SHP_HW_O20_CROSS_PAT_DETECT

#undef PE_SHP_HW_O20_USE_EASY_DB
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#define PE_SHP_HW_O20_ERROR		PE_PRINT_ERROR

#ifdef PE_SHP_HW_O20_SR_PWD_TRACE
#define PE_SHP_HW_O20_DBG_SRPD_TRACE(fmt, args...)	\
	if(_g_shp_hw_o20_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

#define PE_SHP_HW_O20_DBG_PRINT(fmt, args...)
#else
#define PE_SHP_HW_O20_DBG_PRINT(fmt, args...)	\
	if(_g_shp_hw_o20_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}
#endif

#define PE_SHP_HW_O20_CHECK_CODE(_checker, _action, fmt, args...)	\
	{if(_checker){PE_SHP_HW_O20_ERROR(fmt, ##args);_action;}}

#define PE_SHP_HW_O20_DBG_CHECK_CODE(_cnt, _checker, _action, fmt, args...)	\
	{\
		if(_checker){\
			if(_g_shp_hw_o20_trace&&_cnt>PE_PRINT_COUNT_NUM)\
			{\
				PE_SHP_HW_O20_DBG_PRINT(fmt, ##args);\
			}\
			_action;\
		}\
	}

/* for O20*/
#define PE_SHP_HW_O20_DBG_PRINT_RES_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_RES_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_RES_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#ifdef PE_SHP_HW_O20_SRE_SHP_WR_ONLY_MD
#define PE_SHP_HW_O20_DBG_PRINT_SRS_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_SRS_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_SRS_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_O20_DBG_PRINT_2KS_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_2KS_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_2KS_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#endif
#define PE_SHP_HW_O20_DBG_PRINT_CHR_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf,PE_TRACE_STR_SIZE, "%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_CHR_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_CHR_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_SHP_HW_O20_DBG_PRINT_SRE_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_SRE_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_SRE_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_O20_DBG_PRINT_SRL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_SRL_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_SRL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_O20_DBG_PRINT_PBL_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_PBL_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_PBL_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_O20_DBG_PRINT_CTI_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_CTI_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_CTI_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_O20_DBG_PRINT_OBF_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_OBF_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_OBF_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_O20_DBG_PRINT_OBO_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_OBO_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_OBO_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_O20_DBG_PRINT_RCF_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_RCF_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_RCF_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}
#define PE_SHP_HW_O20_DBG_PRINT_RCO_FMT_STATE(_pre, _cur)	\
	{\
		char _str_buf[PE_TRACE_STR_SIZE];\
		snprintf(_str_buf, PE_TRACE_STR_SIZE,"%s(%s)->(%s):%s", #_cur, \
			PE_SHP_HW_O20_RCO_FMT_TO_STR(_pre), \
			PE_SHP_HW_O20_RCO_FMT_TO_STR(_cur), \
			((_pre)!=(_cur))? "different":"same");\
		PE_SHP_HW_O20_DBG_PRINT("%s\n", _str_buf);\
		if((_pre)!=(_cur))\
		{\
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
		}\
	}

#define PE_SHP_HW_O20_SET_SHDW_GSC_Y_TO_SHP(_dst, _src)	\
	(*((UINT32 *)&(gPE_SHP_O20.shdw.data->_dst))) = (*((UINT32 *)&(gPE_GSC_Y_O20.shdw.data->_src)))
#define PE_SHP_HW_O20_SET_SHDW_GSC_C_TO_SHP(_dst, _src)	\
	(*((UINT32 *)&(gPE_SHP_O20.shdw.data->_dst))) = (*((UINT32 *)&(gPE_GSC_C_O20.shdw.data->_src)))

#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
#define PE_SHP_HW_O20_RES_SET_USER(_r, _f, _d)	\
	{	_g_pe_res_hw_param_data_o20.reg_user.data->_r._f = (_d);\
		_g_pe_res_hw_param_data_o20.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O20_RES_WR01(_r, _f1, _d1)	\
	{	PE_SHP_O20_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O20_RES_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O20_RES_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O20_RES_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O20_RES_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_O20_RES_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SHP_O20_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f6, _d6);}
#define PE_SHP_HW_O20_RES_WR08(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6, _f7, _d7, _f8, _d8)	\
	{	PE_SHP_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6, _f7, _d7, _f8, _d8);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f5, _d5);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f6, _d6);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f7, _d7);\
		PE_SHP_HW_O20_RES_SET_USER(_r, _f8, _d8);}

#define PE_SHP_HW_O20_PBL_SET_USER(_r, _f, _d)	\
	{	_g_pe_pbl_hw_param_data_o20.reg_user.data->_r._f = (_d);\
		_g_pe_pbl_hw_param_data_o20.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O20_PBL_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_O20_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O20_PBL_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O20_PBL_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O20_PBL_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O20_PBL_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_PBL_SET_USER(_r, _f5, _d5);}

#define PE_SHP_HW_O20_CTI_SET_USER(_r, _f, _d)	\
	{	_g_pe_cti_hw_param_data_o20.reg_user.data->_r._f = (_d);\
		_g_pe_cti_hw_param_data_o20.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O20_DNR_CTI_WR01(_r, _f1, _d1)	\
	{	PE_DNR0_O20_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O20_DNR_CTI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_DNR0_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O20_DNR_CTI_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_DNR0_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O20_DNR_CTI_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_DNR0_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O20_DNR_CTI_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_DNR0_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f5, _d5);}

#define PE_SHP_HW_O20_SHP_CTI_WR01(_r, _f1, _d1)	\
	{	PE_SHP_O20_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O20_SHP_CTI_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O20_SHP_CTI_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O20_SHP_CTI_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O20_SHP_CTI_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_CTI_SET_USER(_r, _f5, _d5);}

#define PE_VSD_HW_O20_RCF_SET_USER(_r, _f, _d)	\
	{	_g_pe_rcf_hw_param_data_o20.reg_user.data->_r._f = (_d);\
		_g_pe_rcf_hw_param_data_o20.reg_mask.data->_r._f = 0;}

#define PE_VSD_HW_O20_RCE_F_WR01(_r, _f1, _d1)	\
	{	PE_VSD_RCE_F_O20_QWr01(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f1, _d1);}
#define PE_VSD_HW_O20_RCE_F_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_VSD_RCE_F_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f2, _d2);}
#define PE_VSD_HW_O20_RCE_F_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_VSD_RCE_F_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f2, _d2);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f3, _d3);}
#define PE_VSD_HW_O20_RCE_F_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_VSD_RCE_F_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f2, _d2);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f3, _d3);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f4, _d4);}
#define PE_VSD_HW_O20_RCE_F_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_VSD_RCE_F_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f2, _d2);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f3, _d3);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f4, _d4);\
		PE_VSD_HW_O20_RCF_SET_USER(_r, _f5, _d5);}

#define PE_VSD_HW_O20_RCO_SET_USER(_r, _f, _d)	\
	{	_g_pe_rco_hw_param_data_o20.reg_user.data->_r._f = (_d);\
		_g_pe_rco_hw_param_data_o20.reg_mask.data->_r._f = 0;}

#define PE_VSD_HW_O20_RCE_O_WR01(_r, _f1, _d1)	\
	{	PE_VSD_RCE_O_O20_QWr01(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f1, _d1);}
#define PE_VSD_HW_O20_RCE_O_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_VSD_RCE_O_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f2, _d2);}
#define PE_VSD_HW_O20_RCE_O_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_VSD_RCE_O_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f2, _d2);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f3, _d3);}
#define PE_VSD_HW_O20_RCE_O_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_VSD_RCE_O_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f2, _d2);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f3, _d3);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f4, _d4);}
#define PE_VSD_HW_O20_RCE_O_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_VSD_RCE_O_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f1, _d1);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f2, _d2);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f3, _d3);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f4, _d4);\
		PE_VSD_HW_O20_RCO_SET_USER(_r, _f5, _d5);}

/* sre shp(srs) */
#define PE_SHP_HW_O20_SRS_SET_USER(_r, _f, _d)	\
	{	_g_pe_srs_hw_param_data_o20.reg_user.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_o20.reg_mask.data->_r._f = 0;}

#ifndef PE_SHP_HW_O20_USE_SRE_SHP_WR_ONLY_MD
/* for wr only mode */
#define PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f, _d)	\
	{	_g_pe_srs_hw_param_data_o20.reg_data.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_o20.reg_user.data->_r._f = (_d);\
		_g_pe_srs_hw_param_data_o20.reg_mask.data->_r._f = 0;}
#define PE_SHP_HW_O20_SRS_DATA_TO_U32(_r)	\
	(*((UINT32 *)&(_g_pe_srs_hw_param_data_o20.reg_data.data->_r)))

#define PE_SHP_HW_O20_SR_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SR_4K_SHP_O20_Wr(_r,PE_SHP_HW_O20_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O20_WrFL(_r);}
#define PE_SHP_HW_O20_SR_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SR_4K_SHP_O20_Wr(_r,PE_SHP_HW_O20_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O20_WrFL(_r);}
#define PE_SHP_HW_O20_SR_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SR_4K_SHP_O20_Wr(_r,PE_SHP_HW_O20_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O20_WrFL(_r);}
#define PE_SHP_HW_O20_SR_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SR_4K_SHP_O20_Wr(_r,PE_SHP_HW_O20_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O20_WrFL(_r);}
#define PE_SHP_HW_O20_SR_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f5, _d5);\
		PE_SR_4K_SHP_O20_Wr(_r,PE_SHP_HW_O20_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O20_WrFL(_r);}
#define PE_SHP_HW_O20_SR_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f4, _d4);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f5, _d5);\
		PE_SHP_HW_O20_SRS_SET_USER_DATA(_r, _f6, _d6);\
		PE_SR_4K_SHP_O20_Wr(_r,PE_SHP_HW_O20_SRS_DATA_TO_U32(_r));\
		PE_SR_4K_SHP_O20_WrFL(_r);}

#else	//#ifdef PE_SHP_HW_O20_USE_SRE_SHP_WR_ONLY_MD
#define PE_SHP_HW_O20_SR_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SR_4K_SHP_O20_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O20_SR_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SR_4K_SHP_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O20_SR_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SR_4K_SHP_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O20_SR_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SR_4K_SHP_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O20_SR_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SR_4K_SHP_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_O20_SR_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SR_4K_SHP_O20_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_O20_SRS_SET_USER(_r, _f6, _d6);}

#endif	//#ifdef PE_SHP_HW_O20_USE_SRE_SHP_WR_ONLY_MD

/* sre shp(srs) */
#define PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f, _d)	\
	{	_g_pe_srs_2k_hw_param_data_o20.reg_user.data->_r._f = (_d);\
		_g_pe_srs_2k_hw_param_data_o20.reg_mask.data->_r._f = 0;}

#define PE_SHP_HW_O20_SR_2K_SHP_WR01(_r, _f1, _d1)	\
	{	PE_SR_2K_SHP_O20_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O20_SR_2K_SHP_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SR_2K_SHP_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O20_SR_2K_SHP_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SR_2K_SHP_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O20_SR_2K_SHP_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SR_2K_SHP_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O20_SR_2K_SHP_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SR_2K_SHP_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_O20_SR_2K_SHP_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SR_2K_SHP_O20_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f6, _d6);}

#define PE_SHP_HW_O20_SR_MERG_WR01(_r, _f1, _d1)	\
	{	PE_SR_MERG_O20_QWr01(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);}
#define PE_SHP_HW_O20_SR_MERG_WR02(_r, _f1, _d1, _f2, _d2)	\
	{	PE_SR_MERG_O20_QWr02(_r, _f1, _d1, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);}
#define PE_SHP_HW_O20_SR_MERG_WR03(_r, _f1, _d1, _f2, _d2, _f3, _d3)	\
	{	PE_SR_MERG_O20_QWr03(_r, _f1, _d1, _f2, _d2, _f3, _d3);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f3, _d3);}
#define PE_SHP_HW_O20_SR_MERG_WR04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4)	\
	{	PE_SR_MERG_O20_QWr04(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f4, _d4);}
#define PE_SHP_HW_O20_SR_MERG_WR05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5)	\
	{	PE_SR_MERG_O20_QWr05(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f5, _d5);}
#define PE_SHP_HW_O20_SR_MERG_WR06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6)	\
	{	PE_SR_MERG_O20_QWr06(_r, _f1, _d1, _f2, _d2, _f3, _d3, _f4, _d4, _f5, _d5, _f6, _d6);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f1, _d1);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f2, _d2);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f3, _d3);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f4, _d4);\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f5, _d5)\
		PE_SHP_HW_O20_SRS_2K_SET_USER(_r, _f6, _d6);}

/* set table */
#define PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base)	\
	do{\
		UINT32 _i, _size;\
		PE_SHP_HW_O20_CHECK_CODE(!_dflt, ret=RET_ERROR;break, \
			"[%s,%d] _dflt is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_O20_CHECK_CODE(!_user, ret=RET_ERROR;break, \
			"[%s,%d] _user is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_O20_CHECK_CODE(!_mask, ret=RET_ERROR;break, \
			"[%s,%d] _mask is null, not ready.\n", __F__, __L__);\
		PE_SHP_HW_O20_CHECK_CODE(!_data, ret=RET_ERROR;break, \
			"[%s,%d] _data is null, not ready.\n", __F__, __L__);\
		_size = sizeof(__tbl)/sizeof(PE_REG_PARAM_T);\
		for (_i=0; _i<_size; _i++)\
		{\
			if ((__base) == PE_O20_REG_WRITE_BASE)\
			{\
				_dflt[_i] = __tbl[_i].data;\
			}\
			_data[_i] = (__tbl[_i].data & _mask[_i])|(_user[_i]);\
			ret = PE_REG_O20_WrAllocatedAddr((__tbl[_i].addr+(__base)), _data[_i]);\
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_O20_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_SHP_HW_O20_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_SHP_HW_O20_PRE_PROC_SHP_REG_TABLE(__base)	\
	do{\
		PE_SHP_O20_QWr01(shp_apl_ctrl_00, reg_apl_iir_en, 0x0);\
		PE_SHP_O20_QWr01(shp_fd_tmap_temp_00, reg_tmap_temp_iir_en, 0x0);\
		PE_SHP_HW_O20_RES_SET_USER(shp_apl_ctrl_00, reg_apl_iir_en, 0x0);\
		PE_SHP_HW_O20_RES_SET_USER(shp_fd_tmap_temp_00, reg_tmap_temp_iir_en, 0x0);\
	}while(0)

/* shp */
#define PE_SHP_HW_O20_RES_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_res_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_res_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_res_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_res_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_RES_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]res tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* sre shp(srs) */
#define PE_SHP_HW_O20_SRS_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_srs_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_srs_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_srs_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_srs_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_SRS_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]srs tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* sre shp(srs) */
#define PE_SHP_HW_O20_SRS_2K_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_srs_2k_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_srs_2k_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_srs_2k_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_srs_2k_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]srs tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* cti */
#define PE_SHP_HW_O20_CTI_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_cti_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_cti_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_cti_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_cti_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_CTI_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]cti tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)

/* pbl */
#define PE_SHP_HW_O20_PBL_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_pbl_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_pbl_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_pbl_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_pbl_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_PBL_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]pbl tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)
/* obc face */
#define PE_SHP_HW_O20_OBF_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_obf_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_obf_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_obf_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_obf_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]res tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)
/* obc face */
#define PE_SHP_HW_O20_OBO_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_obo_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_obo_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_obo_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_obo_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]res tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)
/* obc face */
#define PE_SHP_HW_O20_RCF_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_rcf_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_rcf_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_rcf_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_rcf_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]res tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)
/* obc face */
#define PE_SHP_HW_O20_RCO_REG_TABLE(__tbl, __base)		\
	do{\
		UINT32 *_dflt = _g_pe_rco_hw_param_data_o20.reg_dflt.addr;\
		UINT32 *_user = _g_pe_rco_hw_param_data_o20.reg_user.addr;\
		UINT32 *_mask = _g_pe_rco_hw_param_data_o20.reg_mask.addr;\
		UINT32 *_data = _g_pe_rco_hw_param_data_o20.reg_data.addr;\
		PE_SHP_HW_O20_CHECK_CODE(\
		(sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T)/sizeof(UINT32))!=sizeof(__tbl)/sizeof(PE_REG_PARAM_T),\
		ret=RET_ERROR;break, "[%s,%d]res tbl size violation.\n", __F__, __L__);\
		PE_SHP_HW_O20_SET_REG_TABLE(__tbl, __base);\
	}while (0)

#endif

/* set gsc filter */
#define PE_SHP_HW_O20_SET_GSC_FLT(__tbl, __base, __size)	\
	do{\
		UINT32 _i;\
		for (_i=0; _i<(__size); _i++)\
		{\
			ret = PE_REG_O20_WrAllocatedAddr((__tbl[_i].addr+(__base)), (__tbl[_i].data));\
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_REG_O20_WrAllocatedAddr() error.\n", __F__, __L__);\
		}\
		if (ret == RET_OK)\
		{\
			PE_SHP_HW_O20_DBG_PRINT("write %s(+ 0x%08x).\n", #__tbl, (__base));\
			ret = PE_REG_SetTraceTable(__F__,__L__, #__tbl, (__base));\
		}\
	}while(0)

#define PE_SHP_HW_O20_CASE_SET_FLT(__ms, __tap, __idx, __ofst, __size)		\
	case PE_SHP_SCL256_CO_NUM_##__tap##T_##__idx:\
		PE_SHP_HW_O20_SET_GSC_FLT(scl_p256_##__tap##t_##__ms##_flt_##__idx,(__ofst),(__size));\
		break

#define PE_SHP_HW_O20_WR_SCL_COEFF(_wid, _ctrl, _coeff, _id)	\
{\
	char _str_buf[PE_TRACE_STR_SIZE];\
	snprintf(_str_buf,PE_TRACE_STR_SIZE,"[wid:%d][idx:%3d]%s", _wid, (_id), #_coeff);\
	PE_SHP_HW_O20_DBG_PRINT("set %s\n", _str_buf);\
	PE_INF_HW_O20_BACKUP_TRACE_DB("%s",_str_buf);\
	PE_SHP_HW_O20_WrSclCoeff((_ctrl),&(_coeff));\
}

/* hex(8bit) to dec : eg. 0xAC -> 1012 */
#define PE_SHP_HW_O20_IDX_HEX_TO_DEC(_x)	(GET_BITS((_x),4,4)*100+GET_BITS((_x),0,4))
/* dec to hex(8bit) : eg. 1012 -> 0xAC */
#define PE_SHP_HW_O20_IDX_DEC_TO_HEX(_x)	(((((_x)/100)&0xf)<<4)+(((_x)%100)&0xf))

#define PE_SHP_HW_O20_CONV_VTAP_TO_VSC_MD(_x)		\
	((_x)==PE_SHP_HW_O20_SCL_VSC_MD_V12TAP||(_x)==PE_SHP_HW_O20_SCL_VSC_MD_V08TAP)? 0x0:\
	((_x)==PE_SHP_HW_O20_SCL_VSC_MD_V02TAP)? 0x3:0x1

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
extern UINT32 g_pe_inf_o20_vr360_mode;
/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
//static int PE_SHP_HW_O20_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static PE_SHP_HW_O20_RES_FMT PE_SHP_HW_O20_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O20_SRS_FMT PE_SHP_HW_O20_ConvDispInfoToSrsFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O20_2KS_FMT PE_SHP_HW_O20_ConvDispInfoTo2ksFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O20_CHR_FMT PE_SHP_HW_O20_ConvDispInfoToChrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O20_CTI_FMT PE_SHP_HW_O20_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O20_OBF_FMT PE_SHP_HW_O20_ConvDispInfoToObfFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O20_OBO_FMT PE_SHP_HW_O20_ConvDispInfoToOboFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O20_RCF_FMT PE_SHP_HW_O20_ConvDispInfoToRcfFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_O20_RCO_FMT PE_SHP_HW_O20_ConvDispInfoToRcoFmt(LX_PE_INF_DISPLAY_T *disp_inf);
#if 0
static PE_SHP_HW_O20_PBL_FMT PE_SHP_HW_O20_ConvDispInfoToPblFmt(LX_PE_INF_DISPLAY_T *disp_inf);
#endif
#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
static int PE_SHP_HW_O20_CreateDataTable(UINT32 index);
#endif /* !PE_HW_O20_PROTECT_OVERLAP_SETTINGS */
static int PE_SHP_HW_O20_SetResDefault(PE_SHP_HW_O20_RES_FMT cur0_res_fmt);
static int PE_SHP_HW_O20_SetSrsDefault(PE_SHP_HW_O20_SRS_FMT cur0_srs_fmt);
static int PE_SHP_HW_O20_Set2ksDefault(PE_SHP_HW_O20_2KS_FMT cur0_2ks_fmt);
static int PE_SHP_HW_O20_SetChrDefault(PE_SHP_HW_O20_CHR_FMT cur0_chr_fmt);

static int PE_SHP_HW_O20_SetObfDefault(PE_SHP_HW_O20_OBF_FMT cur0_obf_fmt);
static int PE_SHP_HW_O20_SetOboDefault(PE_SHP_HW_O20_OBO_FMT cur0_obo_fmt);
static int PE_SHP_HW_O20_SetRcfDefault(PE_SHP_HW_O20_RCF_FMT cur0_rcf_fmt);
static int PE_SHP_HW_O20_SetRcoDefault(PE_SHP_HW_O20_RCO_FMT cur0_rco_fmt);

#if 0
static int PE_SHP_HW_O20_SetPblDefault(PE_SHP_HW_O20_PBL_FMT cur0_pbl_fmt);
#endif
static int PE_SHP_HW_O20_SetCtiDefault(PE_SHP_HW_O20_CTI_FMT cur0_cti_fmt);

static int PE_SHP_HW_O20_DownloadScl12tMainDb(void);
static int PE_SHP_HW_O20_DownloadScl08tMainDb(void);
static int PE_SHP_HW_O20_DownloadScl04tMainDb(void);
static int PE_SHP_HW_O20_DownloadShp2KSqmCmnUserDb(void *pstParams);
static int PE_SHP_HW_O20_DownloadShp2KSqmDetailUserDb(void *pstParams);
static int PE_SHP_HW_O20_DownloadShpSqmCmnUserDb(void *pstParams);
static int PE_SHP_HW_O20_DownloadShpSqmDetailUserDb(void *pstParams);

static int PE_SHP_HW_F20_DownloadScl08tMainDb(void);
static int PE_SHP_HW_F20_DownloadScl12tMainDb(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#ifdef PE_SHP_HW_O20_SR_PWD_TRACE
static UINT8 _g_shp_hw_o20_trace=0x1;	//default should be off.
#else
static UINT8 _g_shp_hw_o20_trace=0x0;	//default should be off.
#endif
static PE_SHP_HW_O20_SETTINGS_T _g_pe_shp_hw_o20_info;
#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
static PE_RES_HW_PARAM_DATA_O20_T _g_pe_res_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_SRS_HW_PARAM_DATA_O20_T _g_pe_srs_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_SRS_2K_HW_PARAM_DATA_O20_T _g_pe_srs_2k_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_PBL_HW_PARAM_DATA_O20_T _g_pe_pbl_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_CTI_HW_PARAM_DATA_O20_T _g_pe_cti_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_OBC_FACE_HW_PARAM_DATA_O20_T _g_pe_obf_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_OBC_OBJT_HW_PARAM_DATA_O20_T _g_pe_obo_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_RCE_FACE_HW_PARAM_DATA_O20_T _g_pe_rcf_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
static PE_RCE_OBJT_HW_PARAM_DATA_O20_T _g_pe_rco_hw_param_data_o20 = {{NULL}, {NULL}, {NULL}, {NULL}};
#endif

#ifdef PE_SHP_HW_O20_CROSS_PAT_DETECT
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
int PE_SHP_HW_O20_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	PE_REG_O20_HW_OPT_T hw_opt = PE_REG_O20_GetDispOpt();
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			memset(&(_g_pe_shp_hw_o20_info), -1, sizeof(PE_SHP_HW_O20_SETTINGS_T));
			_g_pe_shp_hw_o20_info.res0a_fmt = PE_SHP_O20_RES_NUM;
			_g_pe_shp_hw_o20_info.cti0a_fmt = PE_SHP_O20_CTI_NUM;
			_g_pe_shp_hw_o20_info.pbl0a_fmt = PE_SHP_O20_PBL_NUM;
			_g_pe_shp_hw_o20_info.sre0a_fmt = PE_SHP_O20_RES_NUM;
			_g_pe_shp_hw_o20_info.srs0a_fmt = PE_SHP_O20_SRS_NUM;
			_g_pe_shp_hw_o20_info.k2s0a_fmt = PE_SHP_O20_2KS_NUM;
			PE_SHP_HW_O20_DBG_PRINT("init cti.\n");
			PE_SR_CHR_SHP_O20_QWr01(shp_core_ctrl_00,   reg_top_core_bypass, 0x0);
			PE_SR_2K_SHP_O20_QWr01(shp_core_ctrl_00,   reg_top_core_bypass, 0x0);
			PE_SHP_O20_QWr01(shp_core_ctrl_00,   reg_top_core_bypass, 0x0);
			#if 1
			#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
			/* res(pe1 shp l,r) : resolution enhance */
			ret = PE_SHP_HW_O20_CreateDataTable(PE_SHP_HW_O20_TBL_IDX_RES);
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O20_CreateDataTable() error.\n");
			PE_SHP_HW_O20_RES_REG_TABLE(shp_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			/* sre shp(srs) */
			ret = PE_SHP_HW_O20_CreateDataTable(PE_SHP_HW_O20_TBL_IDX_SRS_2K);
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O20_CreateDataTable() error.\n");
			PE_SHP_HW_O20_SRS_2K_REG_TABLE(sre_2k_res_hd_default_o20,PE_O20_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_O20,sre_chr_res_hd_default_o20,PE_O20_REG_WRITE_BASE);
			#if 0
			/* pbl(pre blur dnr1,2) */
			ret = PE_SHP_HW_O20_CreateDataTable(PE_SHP_HW_O20_TBL_IDX_PBL);
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O20_CreateDataTable() error.\n");
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			#endif
			/* cti */
			ret = PE_SHP_HW_O20_CreateDataTable(PE_SHP_HW_O20_TBL_IDX_CTI);
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O20_CreateDataTable() error.\n");
			PE_SHP_HW_O20_CTI_REG_TABLE(cti_y_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			/* obc */
			ret = PE_SHP_HW_O20_CreateDataTable(PE_SHP_HW_O20_TBL_IDX_OBC_FACE);
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O20_CreateDataTable() error.\n");
			PE_SHP_HW_O20_OBF_REG_TABLE(obc_face_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			ret = PE_SHP_HW_O20_CreateDataTable(PE_SHP_HW_O20_TBL_IDX_OBC_OBJT);
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O20_CreateDataTable() error.\n");
			PE_SHP_HW_O20_OBO_REG_TABLE(obc_objt_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			/* rce */
			ret = PE_SHP_HW_O20_CreateDataTable(PE_SHP_HW_O20_TBL_IDX_RCE_FACE);
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O20_CreateDataTable() error.\n");
			PE_SHP_HW_O20_RCF_REG_TABLE(rce_face_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			ret = PE_SHP_HW_O20_CreateDataTable(PE_SHP_HW_O20_TBL_IDX_RCE_OBJT);
			PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"PE_SHP_HW_O20_CreateDataTable() error.\n");
			PE_SHP_HW_O20_RCO_REG_TABLE(rce_objt_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			/*OSD shp*/
			//PE_SET_REG_TABLE(SHP_HW_O20,osdsr_default_o20,PE_O20_REG_WRITE_BASE);
			#else
			/* shp */
			PE_SET_REG_TABLE(SHP_HW_O20,shp_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			/* cti(dnr1,2) */
			//PE_SET_REG_TABLE(SHP_HW_O20,cti_dnr_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			/* pbl(pre blur dnr1,2) */
			//PE_SET_REG_TABLE(SHP_HW_O20,pblur_dnr_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			/* sre */
			PE_SET_REG_TABLE(SHP_HW_O20,sre_2k_res_hd_default_o20,PE_O20_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_O20,sre_4k_res_hd_default_o20,PE_O20_REG_WRITE_BASE);
			PE_SET_REG_TABLE(SHP_HW_O20,sre_chr_res_hd_default_o20,PE_O20_REG_WRITE_BASE);
			#endif
			#endif
			PE_GSC_Y_O20_RdFL(gsc_g0_y_ctrl);
			PE_GSC_Y_O20_Wr01(gsc_g0_y_ctrl,reg_mode_32p_g0,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_Y_O20_Wr01(gsc_g0_y_ctrl,blending_range_g0,0x1);
			PE_GSC_Y_O20_Wr01(gsc_g0_y_ctrl,reg_th_g0,0x6);
			PE_GSC_Y_O20_WrFL(gsc_g0_y_ctrl);
			PE_GSC_Y_O20_RdFL(gsc_g1_y_ctrl);
			PE_GSC_Y_O20_Wr01(gsc_g1_y_ctrl,reg_mode_32p_g1,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_Y_O20_WrFL(gsc_g1_y_ctrl);

			PE_GSC_Y_O20_RdFL(gsc_g0_y_min_max_ctrl);
			PE_GSC_Y_O20_Wr(gsc_g0_y_min_max_ctrl, 0x21012101);
			PE_GSC_Y_O20_WrFL(gsc_g0_y_min_max_ctrl);

			/* gsc_c */
			PE_GSC_C_O20_RdFL(gsc_g0_c_ctrl);
			PE_GSC_C_O20_Wr01(gsc_g0_c_ctrl,reg_mode_32p_g0,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_C_O20_Wr01(gsc_g0_c_ctrl,reg_min_max_on_g0,0x1);
			PE_GSC_C_O20_Wr01(gsc_g0_c_ctrl,reg_min_max_th_g0,0x1C);
			PE_GSC_C_O20_Wr01(gsc_g0_c_ctrl,reg_min_max_on_h_g0,0x1);
			PE_GSC_C_O20_WrFL(gsc_g0_c_ctrl);
			PE_GSC_C_O20_RdFL(gsc_g1_c_ctrl);
			PE_GSC_C_O20_Wr01(gsc_g1_c_ctrl,reg_mode_32p_g1,0x0);		//phase 0x0:256,0x1:32
			PE_GSC_C_O20_WrFL(gsc_g1_c_ctrl);
			if (hw_opt.external_chip ==0) //4k model
			{
				_g_pe_shp_hw_o20_info.is_external_chip = 0;
			}
			else //8k model
			{
				_g_pe_shp_hw_o20_info.is_external_chip = 1;
			}
#ifdef PE_SHP_HW_O20_CROSS_PAT_DETECT
			_g_pre_data_shp=0xff;
			_g_pre_shp_bypass=0xff;
#endif
			#if 1	/* F20_TBL */
			PE_CHPI_SHP_HW_F20_Init(pstParams);
			PE_CHPI_OBC_HW_F20_Init(pstParams);
			#endif
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * create data table
 *
 * @param   index [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_SHP_HW_O20A_TBL_INDX
 * @author
 */
static int PE_SHP_HW_O20_CreateDataTable(UINT32 index)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	PE_RES_HW_PARAM_DATA_O20_T *p_res_o20 = &_g_pe_res_hw_param_data_o20;
	PE_PBL_HW_PARAM_DATA_O20_T *p_pbl_o20 = &_g_pe_pbl_hw_param_data_o20;
	PE_SRS_HW_PARAM_DATA_O20_T *p_srs_o20 = &_g_pe_srs_hw_param_data_o20;
	PE_SRS_2K_HW_PARAM_DATA_O20_T *p_srs_2k_o20 = &_g_pe_srs_2k_hw_param_data_o20;
	PE_CTI_HW_PARAM_DATA_O20_T *p_cti_o20 = &_g_pe_cti_hw_param_data_o20;
	PE_OBC_FACE_HW_PARAM_DATA_O20_T *p_obf_o20 = &_g_pe_obf_hw_param_data_o20;
	PE_OBC_OBJT_HW_PARAM_DATA_O20_T *p_obo_o20 = &_g_pe_obo_hw_param_data_o20;
	PE_RCE_FACE_HW_PARAM_DATA_O20_T *p_rcf_o20 = &_g_pe_rcf_hw_param_data_o20;
	PE_RCE_OBJT_HW_PARAM_DATA_O20_T *p_rco_o20 = &_g_pe_rco_hw_param_data_o20;
	PE_SHP_HW_O20_CHECK_CODE(index>=PE_SHP_HW_O20_TBL_IDX_NUM, return RET_ERROR, \
		"[%s,%d] index(%d) invalid.\n", __F__, __L__, index);
	if (index == PE_SHP_HW_O20_TBL_IDX_RES)
	{
		/* create dflt table */
		if (p_res_o20->reg_dflt.addr == NULL)
		{
			p_res_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_res_o20->reg_user.addr == NULL)
		{
			p_res_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O20_T));
			memset((p_res_o20->reg_user.addr), 0, sizeof(PE_RES_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_res_o20->reg_mask.addr == NULL)
		{
			p_res_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O20_T));
			memset((p_res_o20->reg_mask.addr), -1, sizeof(PE_RES_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_res_o20->reg_data.addr == NULL)
		{
			p_res_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RES_HW_PARAM_REG_O20_T));
			memset((p_res_o20->reg_data.addr), 0, sizeof(PE_RES_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report result */
		if (p_res_o20->reg_dflt.addr != NULL && p_res_o20->reg_user.addr != NULL && \
			p_res_o20->reg_mask.addr != NULL && p_res_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_res_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_res_o20->reg_user.addr == NULL)? "x":"o", \
				(p_res_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_res_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O20_TBL_IDX_PBL)
	{
		/* create dflt table */
		if (p_pbl_o20->reg_dflt.addr == NULL)
		{
			p_pbl_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_pbl_o20->reg_user.addr == NULL)
		{
			p_pbl_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_O20_T));
			memset((p_pbl_o20->reg_user.addr), 0, sizeof(PE_PBL_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_pbl_o20->reg_mask.addr == NULL)
		{
			p_pbl_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_O20_T));
			memset((p_pbl_o20->reg_mask.addr), -1, sizeof(PE_PBL_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_pbl_o20->reg_data.addr == NULL)
		{
			p_pbl_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_PBL_HW_PARAM_REG_O20_T));
			memset((p_pbl_o20->reg_data.addr), 0, sizeof(PE_PBL_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report result */
		if (p_pbl_o20->reg_dflt.addr != NULL && p_pbl_o20->reg_user.addr != NULL && \
			p_pbl_o20->reg_mask.addr != NULL && p_pbl_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_pbl_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_pbl_o20->reg_user.addr == NULL)? "x":"o", \
				(p_pbl_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_pbl_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O20_TBL_IDX_CTI)
	{
		/* create dflt table */
		if (p_cti_o20->reg_dflt.addr == NULL)
		{
			p_cti_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_cti_o20->reg_user.addr == NULL)
		{
			p_cti_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O20_T));
			memset((p_cti_o20->reg_user.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_cti_o20->reg_mask.addr == NULL)
		{
			p_cti_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O20_T));
			memset((p_cti_o20->reg_mask.addr), -1, sizeof(PE_CTI_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_cti_o20->reg_data.addr == NULL)
		{
			p_cti_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CTI_HW_PARAM_REG_O20_T));
			memset((p_cti_o20->reg_data.addr), 0, sizeof(PE_CTI_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report result */
		if (p_cti_o20->reg_dflt.addr != NULL && p_cti_o20->reg_user.addr != NULL && \
			p_cti_o20->reg_mask.addr != NULL && p_cti_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_cti_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_cti_o20->reg_user.addr == NULL)? "x":"o", \
				(p_cti_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_cti_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	#ifdef PE_SHP_HW_O20_SRE_SHP_WR_ONLY_MD
	else if (index == PE_SHP_HW_O20_TBL_IDX_SRS)
	{
		/* create dflt table */
		if (p_srs_o20->reg_dflt.addr == NULL)
		{
			p_srs_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_srs_o20->reg_user.addr == NULL)
		{
			p_srs_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_O20_T));
			memset((p_srs_o20->reg_user.addr), 0, sizeof(PE_SRS_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_srs_o20->reg_mask.addr == NULL)
		{
			p_srs_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_O20_T));
			memset((p_srs_o20->reg_mask.addr), -1, sizeof(PE_SRS_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_srs_o20->reg_data.addr == NULL)
		{
			p_srs_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_HW_PARAM_REG_O20_T));
			memset((p_srs_o20->reg_data.addr), 0, sizeof(PE_SRS_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report srsult */
		if (p_srs_o20->reg_dflt.addr != NULL && p_srs_o20->reg_user.addr != NULL && \
			p_srs_o20->reg_mask.addr != NULL && p_srs_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_srs_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_srs_o20->reg_user.addr == NULL)? "x":"o", \
				(p_srs_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_srs_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O20_TBL_IDX_SRS_2K)
	{
		/* create dflt table */
		if (p_srs_2k_o20->reg_dflt.addr == NULL)
		{
			p_srs_2k_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_srs_2k_o20->reg_user.addr == NULL)
		{
			p_srs_2k_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T));
			memset((p_srs_2k_o20->reg_user.addr), 0, sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_srs_2k_o20->reg_mask.addr == NULL)
		{
			p_srs_2k_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T));
			memset((p_srs_2k_o20->reg_mask.addr), -1, sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_srs_2k_o20->reg_data.addr == NULL)
		{
			p_srs_2k_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T));
			memset((p_srs_2k_o20->reg_data.addr), 0, sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report srsult */
		if (p_srs_2k_o20->reg_dflt.addr != NULL && p_srs_2k_o20->reg_user.addr != NULL && \
			p_srs_2k_o20->reg_mask.addr != NULL && p_srs_2k_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_srs_2k_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_srs_2k_o20->reg_user.addr == NULL)? "x":"o", \
				(p_srs_2k_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_srs_2k_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O20_TBL_IDX_OBC_FACE)
	{
		/* create dflt table */
		if (p_obf_o20->reg_dflt.addr == NULL)
		{
			p_obf_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_obf_o20->reg_user.addr == NULL)
		{
			p_obf_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T));
			memset((p_obf_o20->reg_user.addr), 0, sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_obf_o20->reg_mask.addr == NULL)
		{
			p_obf_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T));
			memset((p_obf_o20->reg_mask.addr), -1, sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_obf_o20->reg_data.addr == NULL)
		{
			p_obf_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T));
			memset((p_obf_o20->reg_data.addr), 0, sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report srsult */
		if (p_obf_o20->reg_dflt.addr != NULL && p_obf_o20->reg_user.addr != NULL && \
			p_obf_o20->reg_mask.addr != NULL && p_obf_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_obf_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_obf_o20->reg_user.addr == NULL)? "x":"o", \
				(p_obf_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_obf_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O20_TBL_IDX_OBC_OBJT)
	{
		/* create dflt table */
		if (p_obo_o20->reg_dflt.addr == NULL)
		{
			p_obo_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_obo_o20->reg_user.addr == NULL)
		{
			p_obo_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T));
			memset((p_obo_o20->reg_user.addr), 0, sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_obo_o20->reg_mask.addr == NULL)
		{
			p_obo_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T));
			memset((p_obo_o20->reg_mask.addr), -1, sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_obo_o20->reg_data.addr == NULL)
		{
			p_obo_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T));
			memset((p_obo_o20->reg_data.addr), 0, sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report srsult */
		if (p_obo_o20->reg_dflt.addr != NULL && p_obo_o20->reg_user.addr != NULL && \
			p_obo_o20->reg_mask.addr != NULL && p_obo_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_obo_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_obo_o20->reg_user.addr == NULL)? "x":"o", \
				(p_obo_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_obo_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O20_TBL_IDX_RCE_FACE)
	{
		/* create dflt table */
		if (p_rcf_o20->reg_dflt.addr == NULL)
		{
			p_rcf_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_rcf_o20->reg_user.addr == NULL)
		{
			p_rcf_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T));
			memset((p_rcf_o20->reg_user.addr), 0, sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_rcf_o20->reg_mask.addr == NULL)
		{
			p_rcf_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T));
			memset((p_rcf_o20->reg_mask.addr), -1, sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_rcf_o20->reg_data.addr == NULL)
		{
			p_rcf_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T));
			memset((p_rcf_o20->reg_data.addr), 0, sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report srsult */
		if (p_rcf_o20->reg_dflt.addr != NULL && p_rcf_o20->reg_user.addr != NULL && \
			p_rcf_o20->reg_mask.addr != NULL && p_rcf_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_rcf_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_rcf_o20->reg_user.addr == NULL)? "x":"o", \
				(p_rcf_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_rcf_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	else if (index == PE_SHP_HW_O20_TBL_IDX_RCE_OBJT)
	{
		/* create dflt table */
		if (p_rco_o20->reg_dflt.addr == NULL)
		{
			p_rco_o20->reg_dflt.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T));
		}
		/* create user table */
		if (p_rco_o20->reg_user.addr == NULL)
		{
			p_rco_o20->reg_user.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T));
			memset((p_rco_o20->reg_user.addr), 0, sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* create mask table */
		if (p_rco_o20->reg_mask.addr == NULL)
		{
			p_rco_o20->reg_mask.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T));
			memset((p_rco_o20->reg_mask.addr), -1, sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T));// 0xffffffff
		}
		/* create data table */
		if (p_rco_o20->reg_data.addr == NULL)
		{
			p_rco_o20->reg_data.addr = (UINT32 *)OS_KMalloc(sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T));
			memset((p_rco_o20->reg_data.addr), 0, sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T));	// 0x0
		}
		/* report srsult */
		if (p_rco_o20->reg_dflt.addr != NULL && p_rco_o20->reg_user.addr != NULL && \
			p_rco_o20->reg_mask.addr != NULL && p_rco_o20->reg_data.addr != NULL)
		{
			PE_PRINT_NOTI("[%s]table ready.\n", PE_SHP_HW_O20_TBL_IDX_TO_STR(index));
			ret = RET_OK;
		}
		else
		{
			PE_PRINT_NOTI("[%s]table not ready. dflt,user,mask,data:%s,%s,%s,%s\n", \
				PE_SHP_HW_O20_TBL_IDX_TO_STR(index), \
				(p_rco_o20->reg_dflt.addr == NULL)? "x":"o", \
				(p_rco_o20->reg_user.addr == NULL)? "x":"o", \
				(p_rco_o20->reg_mask.addr == NULL)? "x":"o", \
				(p_rco_o20->reg_data.addr == NULL)? "x":"o");
			ret = RET_ERROR;
		}
	}
	#endif	//#ifdef PE_SHP_HW_O20_SRE_SHP_WR_ONLY_MD
	else
	{
		PE_SHP_HW_O20_DBG_PRINT("nothing to do\n");	ret = RET_OK;
	}
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_SHP_HW_O20_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(SHP)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_shp_hw_o20_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(SHP)))? 0x1:0x0;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * default shp setting(for O20AX)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O20_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	PE_INF_O20_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *disp0_inf = NULL;
	LX_PE_INF_DISPLAY_T *disp1_inf = NULL;
	PE_SHP_HW_O20_RES_FMT cur0_res_fmt;
	//PE_SHP_HW_O20_PBL_FMT cur0_pbl_fmt;
	PE_SHP_HW_O20_CTI_FMT cur0_cti_fmt;
	PE_SHP_HW_O20_SRS_FMT cur0_srs_fmt;
	PE_SHP_HW_O20_2KS_FMT cur0_2ks_fmt;
	PE_SHP_HW_O20_CHR_FMT cur0_chr_fmt;
	PE_SHP_HW_O20_OBF_FMT cur0_obf_fmt;
	PE_SHP_HW_O20_OBO_FMT cur0_obo_fmt;
	PE_SHP_HW_O20_RCF_FMT cur0_rcf_fmt;
	PE_SHP_HW_O20_RCO_FMT cur0_rco_fmt;
	PE_SHP_HW_O20_SETTINGS_T *pInfo=&_g_pe_shp_hw_o20_info;
	#ifdef PE_SHP_HW_O20_SR_PWD_TRACE
	UINT32 r_data[2];
	#endif
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_O20_GetCurInfSettings(&inf_set);
		PE_SHP_HW_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_INF_O20_GetCurInfSettings() error.\n", __F__, __L__);
		disp0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		disp1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(disp0_inf);
		CHECK_KNULL(disp1_inf);
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			//*gpe_vsd_ctrl_block_o20 = 0x01200000;
			/* res(pe1 shp l,r) */
			cur0_res_fmt = PE_SHP_HW_O20_ConvDispInfoToResFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_RES_FMT_STATE(pInfo->res0a_fmt,cur0_res_fmt);
			if(pInfo->res0a_fmt!=cur0_res_fmt)
			{
				ret = PE_SHP_HW_O20_SetResDefault(cur0_res_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetResDefault() error.\n", __F__, __L__);
				pInfo->res0a_fmt=cur0_res_fmt;
			}
			/* sre shp(srs) */
			cur0_srs_fmt = PE_SHP_HW_O20_ConvDispInfoToSrsFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_SRS_FMT_STATE(pInfo->srs0a_fmt,cur0_srs_fmt);
			if(pInfo->srs0a_fmt!=cur0_srs_fmt)
			{
				ret = PE_SHP_HW_O20_SetSrsDefault(cur0_srs_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetSrsDefault() error.\n", __F__, __L__);
				#ifdef PE_SHP_HW_O20_CROSS_PAT_DETECT
				//_g_pre_data_shp = _g_pe_srs_hw_param_data_o20.reg_dflt.data->shp_derh_ctrl_05.reg_derh_th_gain_edge;
				//PE_SHP_HW_O20_DBG_PRINT("defualt pre :%d\n", _g_pre_data_shp );
				#endif
				pInfo->srs0a_fmt=cur0_srs_fmt;
			}
			/* sre 2k shp(srs) */
			cur0_2ks_fmt = PE_SHP_HW_O20_ConvDispInfoTo2ksFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_2KS_FMT_STATE(pInfo->k2s0a_fmt,cur0_2ks_fmt);
			if(pInfo->k2s0a_fmt!=cur0_2ks_fmt)
			{
				ret = PE_SHP_HW_O20_Set2ksDefault(cur0_2ks_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_Set2ksDefault() error.\n", __F__, __L__);
				#ifdef PE_SHP_HW_O20_CROSS_PAT_DETECT
				#endif
				pInfo->k2s0a_fmt=cur0_2ks_fmt;
			}
			/* sre shp(srs) */
			cur0_chr_fmt = PE_SHP_HW_O20_ConvDispInfoToChrFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_CHR_FMT_STATE(pInfo->chr0a_fmt,cur0_chr_fmt);
			if(pInfo->chr0a_fmt!=cur0_chr_fmt)
			{
				ret = PE_SHP_HW_O20_SetChrDefault(cur0_chr_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetChrDefault() error.\n", __F__, __L__);
				#ifdef PE_SHP_HW_O20_CROSS_PAT_DETECT
				#endif
				pInfo->chr0a_fmt=cur0_chr_fmt;
			}
			#if 0
			/* pbl(pre_blur_dnr) */
			cur0_pbl_fmt = PE_SHP_HW_O20_ConvDispInfoToPblFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_PBL_FMT_STATE(pInfo->pbl0a_fmt,cur0_pbl_fmt);
			if(pInfo->pbl0a_fmt!=cur0_pbl_fmt)
			{
				ret = PE_SHP_HW_O20_SetPblDefault(cur0_pbl_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetPblDefault() error.\n", __F__, __L__);
				pInfo->pbl0a_fmt=cur0_pbl_fmt;
			}
			#endif
			/*cti(cti_dnr) */
			cur0_cti_fmt = PE_SHP_HW_O20_ConvDispInfoToCtiFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_CTI_FMT_STATE(pInfo->cti0a_fmt,cur0_cti_fmt);
			if(pInfo->cti0a_fmt!=cur0_cti_fmt)
			{
				ret = PE_SHP_HW_O20_SetCtiDefault(cur0_cti_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetCtiDefault() error.\n", __F__, __L__);
				pInfo->cti0a_fmt=cur0_cti_fmt;
			}
			/* obc */
			cur0_obf_fmt = PE_SHP_HW_O20_ConvDispInfoToObfFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_OBF_FMT_STATE(pInfo->obf0a_fmt,cur0_obf_fmt);
			if(pInfo->obf0a_fmt!=cur0_obf_fmt)
			{
				ret = PE_SHP_HW_O20_SetObfDefault(cur0_obf_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetObfDefault() error.\n", __F__, __L__);
				pInfo->obf0a_fmt=cur0_obf_fmt;
			}
			cur0_obo_fmt = PE_SHP_HW_O20_ConvDispInfoToOboFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_OBO_FMT_STATE(pInfo->obo0a_fmt,cur0_obo_fmt);
			if(pInfo->obo0a_fmt!=cur0_obo_fmt)
			{
				ret = PE_SHP_HW_O20_SetOboDefault(cur0_obo_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetOboDefault() error.\n", __F__, __L__);
				pInfo->obo0a_fmt=cur0_obo_fmt;
			}
			/* rce*/
			cur0_rcf_fmt = PE_SHP_HW_O20_ConvDispInfoToRcfFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_RCF_FMT_STATE(pInfo->rcf0a_fmt,cur0_rcf_fmt);
			if(pInfo->rcf0a_fmt!=cur0_rcf_fmt)
			{
				ret = PE_SHP_HW_O20_SetRcfDefault(cur0_rcf_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetRcfDefault() error.\n", __F__, __L__);
				pInfo->rcf0a_fmt=cur0_rcf_fmt;
			}
			cur0_rco_fmt = PE_SHP_HW_O20_ConvDispInfoToRcoFmt(disp0_inf);
			PE_SHP_HW_O20_DBG_PRINT_RCO_FMT_STATE(pInfo->rco0a_fmt,cur0_rco_fmt);
			if(pInfo->rco0a_fmt!=cur0_rco_fmt)
			{
				ret = PE_SHP_HW_O20_SetRcoDefault(cur0_rco_fmt);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
				"[%s,%d] PE_SHP_HW_O20_SetRcoDefault() error.\n", __F__, __L__);
				pInfo->rco0a_fmt=cur0_rco_fmt;
			}
			#if 1	/* F20_TBL */
			PE_CHPI_SHP_HW_F20_SetDefault();
			PE_CHPI_OBC_HW_F20_SetDefault();
			#endif
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * default Res setting(for O20X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_O20_RES_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_O20_SetResDefault(PE_SHP_HW_O20_RES_FMT cur0_res_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
	switch(cur0_res_fmt)
	{
		case PE_SHP_O20_RES_SD:
		case PE_SHP_O20_RES_DTV_SD:
			if(_g_pe_shp_hw_o20_info.is_external_chip) //8k model
				PE_SHP_HW_O20_RES_REG_TABLE(shp_l_sd_default_o20_8k,   	PE_O20_REG_WRITE_BASE);
			else // 4k model
				PE_SHP_HW_O20_RES_REG_TABLE(shp_l_sd_default_o20,   	PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RES_HD:
		case PE_SHP_O20_RES_DTV_HD:
		case PE_SHP_O20_RES_SEEMLESS:
			if(_g_pe_shp_hw_o20_info.is_external_chip) //8k model
				PE_SHP_HW_O20_RES_REG_TABLE(shp_l_hd_default_o20_8k,   PE_O20_REG_WRITE_BASE);
			else // 4k model
				PE_SHP_HW_O20_RES_REG_TABLE(shp_l_hd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RES_UHD:
			if(_g_pe_shp_hw_o20_info.is_external_chip) //8k model
				PE_SHP_HW_O20_RES_REG_TABLE(shp_l_ud_default_o20_8k,   	PE_O20_REG_WRITE_BASE);
			else // 4k model
				PE_SHP_HW_O20_RES_REG_TABLE(shp_l_ud_default_o20,   	PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_res_fmt)
	{
		case PE_SHP_O20_RES_SD:
			PE_SET_REG_TABLE(SHP_HW_O20,shp_l_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RES_HD:
			PE_SET_REG_TABLE(SHP_HW_O20,shp_l_hd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RES_UHD:
			PE_SET_REG_TABLE(SHP_HW_O20,shp_l_ud_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RES_DTV_SD:
			PE_SET_REG_TABLE(SHP_HW_O20,shp_l_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RES_DTV_SD:
			PE_SET_REG_TABLE(SHP_HW_O20,shp_l_hd_dtv_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
static int PE_SHP_HW_O20_SetSrsDefault(PE_SHP_HW_O20_SRS_FMT cur0_srs_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
	switch(cur0_srs_fmt)
	{
		case PE_SHP_O20_SRS_SD:
			PE_SHP_HW_O20_SRS_REG_TABLE(sre_4k_res_sd_default_o20,       PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_SRS_HD:
			PE_SHP_HW_O20_SRS_REG_TABLE(sre_4k_res_hd_default_o20,       PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_SRS_UHD:
			PE_SHP_HW_O20_SRS_REG_TABLE(sre_4k_res_ud_default_o20,      PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_SRS_DTV_SD:
			PE_SHP_HW_O20_SRS_REG_TABLE(sre_4k_res_sd_dtv_default_o20,       PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_SRS_SEEMLESS:
			PE_SHP_HW_O20_SRS_REG_TABLE(sre_4k_res_cp_default_o20,       PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_srs_fmt)
	{
		case PE_SHP_O20_SRS_SD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_4k_res_sd_default_o20,       PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_SRS_HD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_4k_res_hd_default_o20,       PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_SRS_UHD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_4k_res_ud_default_o20,      PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * default Res setting(for O20X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_O20_2KS_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_O20_Set2ksDefault(PE_SHP_HW_O20_2KS_FMT cur0_2ks_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
	switch(cur0_2ks_fmt)
	{
		case PE_SHP_O20_2KS_SD:
			PE_SHP_HW_O20_SRS_2K_REG_TABLE(sre_2k_res_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_HD:
			PE_SHP_HW_O20_SRS_2K_REG_TABLE(sre_2k_res_hd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_UHD:
			PE_SHP_HW_O20_SRS_2K_REG_TABLE(sre_2k_res_ud_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_DTV_SD:
			PE_SHP_HW_O20_SRS_2K_REG_TABLE(sre_2k_res_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_ATV:
			PE_SHP_HW_O20_SRS_2K_REG_TABLE(sre_2k_res_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_DTV_HD:
			PE_SHP_HW_O20_SRS_2K_REG_TABLE(sre_2k_res_hd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_SEEMLESS:
			PE_SHP_HW_O20_SRS_2K_REG_TABLE(sre_2k_res_hd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_2ks_fmt)
	{
		case PE_SHP_O20_2KS_SD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_2k_res_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_HD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_2k_res_hd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_UHD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_2k_res_ud_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_DTV_SD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_2k_res_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_ATV:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_2k_res_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_2KS_DTV_HD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_2k_res_hd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}


/**
 * default Res setting(for O20X)
 *
 * @param   *cur0_res_fmt [in] PE_SHP_HW_O20_CHR_FMT
 * @return  
 * @see
 * @author
 */
static int PE_SHP_HW_O20_SetChrDefault(PE_SHP_HW_O20_CHR_FMT cur0_chr_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	switch(cur0_chr_fmt)
	{
		case PE_SHP_O20_CHR_SD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_chr_res_sd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_CHR_HD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_chr_res_hd_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_CHR_UHD:
			PE_SET_REG_TABLE(SHP_HW_O20,sre_chr_res_ud_default_o20,   PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
#if 0
static int PE_SHP_HW_O20_SetPblDefault(PE_SHP_HW_O20_PBL_FMT cur0_pbl_fmt)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
	switch(cur0_pbl_fmt)
	{
		case PE_SHP_O20_PBL_ATV_NT:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_atv_nt_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_ATV_PAL:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_atv_pal_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_AV:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_av_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_SECAM:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_secam_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_COMP_SD:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_comp_sd_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_DTV_SD:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_dtv_sd_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_HDMI_SD:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_hdmi_sd_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_PC:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_pc_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_HD:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_hd_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_UD:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_ud_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_VR_360:
			PE_SHP_HW_O20_PBL_REG_TABLE(pblur_dnr_l_vr_360_default_o20, PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#else
	switch(cur0_pbl_fmt)
	{
		case PE_SHP_O20_PBL_SD:
			PE_SET_REG_TABLE(SHP_HW_O20,pblur_dnr_l_sd_default_o20,PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_PBL_HD:
			PE_SET_REG_TABLE(SHP_HW_O20,pblur_dnr_l_hd_default_o20,PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
#endif
static int PE_SHP_HW_O20_SetCtiDefault(PE_SHP_HW_O20_CTI_FMT cur0_cti_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	switch(cur0_cti_fmt)
	{
		case PE_SHP_O20_CTI_SD:
			PE_SHP_HW_O20_CTI_REG_TABLE(cti_y_l_sd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_CTI_HD:
			PE_SHP_HW_O20_CTI_REG_TABLE(cti_y_l_hd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_CTI_VR_360:
			PE_SHP_HW_O20_CTI_REG_TABLE(cti_y_l_vr_360_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_CTI_ATV:
			PE_SHP_HW_O20_CTI_REG_TABLE(cti_y_l_atv_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_CTI_UD:
			PE_SHP_HW_O20_CTI_REG_TABLE(cti_y_l_ud_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
static int PE_SHP_HW_O20_SetObfDefault(PE_SHP_HW_O20_OBF_FMT cur0_obf_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	switch(cur0_obf_fmt)
	{
		case PE_SHP_O20_OBF_SD:
			PE_SHP_HW_O20_OBF_REG_TABLE(obc_face_l_sd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_OBF_HD:
			PE_SHP_HW_O20_OBF_REG_TABLE(obc_face_l_hd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_OBF_UD:
			PE_SHP_HW_O20_OBF_REG_TABLE(obc_face_l_ud_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
static int PE_SHP_HW_O20_SetOboDefault(PE_SHP_HW_O20_OBO_FMT cur0_obo_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	switch(cur0_obo_fmt)
	{
		case PE_SHP_O20_OBO_SD:
			PE_SHP_HW_O20_OBO_REG_TABLE(obc_objt_l_sd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_OBO_HD:
			PE_SHP_HW_O20_OBO_REG_TABLE(obc_objt_l_hd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_OBO_UD:
			PE_SHP_HW_O20_OBO_REG_TABLE(obc_objt_l_ud_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

static int PE_SHP_HW_O20_SetRcfDefault(PE_SHP_HW_O20_RCF_FMT cur0_rcf_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	switch(cur0_rcf_fmt)
	{
		case PE_SHP_O20_RCF_SD:
			PE_SHP_HW_O20_RCF_REG_TABLE(rce_face_l_sd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RCF_HD:
			PE_SHP_HW_O20_RCF_REG_TABLE(rce_face_l_hd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RCF_UD:
			PE_SHP_HW_O20_RCF_REG_TABLE(rce_face_l_ud_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

static int PE_SHP_HW_O20_SetRcoDefault(PE_SHP_HW_O20_RCO_FMT cur0_rco_fmt)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	switch(cur0_rco_fmt)
	{
		case PE_SHP_O20_RCO_SD:
			PE_SHP_HW_O20_RCO_REG_TABLE(rce_objt_l_sd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RCO_HD:
			PE_SHP_HW_O20_RCO_REG_TABLE(rce_objt_l_hd_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		case PE_SHP_O20_RCO_UD:
			PE_SHP_HW_O20_RCO_REG_TABLE(rce_objt_l_ud_default_o20,    PE_O20_REG_WRITE_BASE);
			break;
		default:
			break;
	}
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * get resolution fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_RES_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O20_RES_FMT PE_SHP_HW_O20_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_RES_FMT res_fmt = PE_SHP_O20_RES_NUM;
	PE_SHP_HW_O20_DBG_PRINT("ResFmt seemless mode :%d.\n", disp_inf->act_fmt );
	if(disp_inf->act_fmt !=0)
	{
		res_fmt = PE_SHP_O20_RES_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					res_fmt = PE_SHP_O20_RES_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_O20_RES_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_SHP_O20_RES_DTV_HD;
				}
				else
				{
					res_fmt = PE_SHP_O20_RES_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_O20_RES_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					res_fmt = PE_SHP_O20_RES_HD;
				}
				else
				{
					res_fmt = PE_SHP_O20_RES_UHD;
				}
				break;
		}
	}
	return res_fmt;
}
/**
 * get sre shp(srs) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_SRS_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O20_SRS_FMT PE_SHP_HW_O20_ConvDispInfoToSrsFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_SRS_FMT srs_fmt = PE_SHP_O20_SRS_NUM;
	if(disp_inf->act_fmt !=0)
	{
		srs_fmt = PE_SHP_O20_SRS_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					srs_fmt = PE_SHP_O20_SRS_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_O20_SRS_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_O20_SRS_HD;
				}
				else
				{
					srs_fmt = PE_SHP_O20_SRS_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_O20_SRS_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_O20_SRS_HD;
				}
				else
				{
					srs_fmt = PE_SHP_O20_SRS_UHD;
				}
				break;
		}
	}
	return srs_fmt;
}
/**
 * get sre 2k shp(srs) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_2KS_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O20_2KS_FMT PE_SHP_HW_O20_ConvDispInfoTo2ksFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_2KS_FMT srs_fmt = PE_SHP_O20_2KS_NUM;
	if(disp_inf->act_fmt !=0)
	{
		srs_fmt = PE_SHP_O20_2KS_SEEMLESS;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					srs_fmt = PE_SHP_O20_2KS_ATV;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				{
					srs_fmt = PE_SHP_O20_2KS_SD;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_O20_2KS_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_O20_2KS_DTV_HD;
				}
				else
				{
					srs_fmt = PE_SHP_O20_2KS_UHD;
				}
				break;
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			case LX_PE_SRC_RGBPC:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					srs_fmt = PE_SHP_O20_2KS_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					srs_fmt = PE_SHP_O20_2KS_HD;
				}
				else
				{
					srs_fmt = PE_SHP_O20_2KS_UHD;
				}
				break;
		}
	}
	return srs_fmt;
}
/**
 * get sre chr shp(srs) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_CHR_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O20_CHR_FMT PE_SHP_HW_O20_ConvDispInfoToChrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_CHR_FMT srs_fmt = PE_SHP_O20_CHR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			srs_fmt = PE_SHP_O20_CHR_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				srs_fmt = PE_SHP_O20_CHR_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				srs_fmt = PE_SHP_O20_CHR_HD;
			}
			else
			{
				srs_fmt = PE_SHP_O20_CHR_UHD;
			}
			break;
	}
	return srs_fmt;
}
#if 0
/**
 * get pbl(pre blur dnr) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_CTI_FMT
 * @see
 * @author
 */
static PE_SHP_HW_O20_PBL_FMT PE_SHP_HW_O20_ConvDispInfoToPblFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_PBL_FMT pbl_fmt = PE_SHP_O20_PBL_NUM;
	PE_SHP_HW_O20_DBG_PRINT("PblFmt g_pe_inf_o20_vr360_mode: %d.\n", g_pe_inf_o20_vr360_mode);
	if(disp_inf->mode.is_vr)
	{
			pbl_fmt = PE_SHP_O20_PBL_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				if(disp_inf->cstd_type==LX_PE_CSTD_SECAM)
				{
					pbl_fmt = PE_SHP_O20_PBL_SECAM;
				}
				else if(disp_inf->cstd_type==LX_PE_CSTD_PAL)
				{
					pbl_fmt = PE_SHP_O20_PBL_ATV_PAL;
				}
				else
				{
					pbl_fmt = PE_SHP_O20_PBL_ATV_NT;
				}
				break;
			case LX_PE_SRC_CVBS:
			case LX_PE_SRC_SCART:
				if(disp_inf->cstd_type==LX_PE_CSTD_SECAM)
				{
					pbl_fmt = PE_SHP_O20_PBL_SECAM;
				}
				else
				{
					pbl_fmt = PE_SHP_O20_PBL_AV;
				}
				break;
			case LX_PE_SRC_RGBPC:
				{
					pbl_fmt = PE_SHP_O20_PBL_PC;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->dtv_type==LX_PE_DTV_HDDPLAY)
				{
					if(disp_inf->hdd_type==LX_PE_HDD_SRC_ATV60)
					{
						pbl_fmt = PE_SHP_O20_PBL_ATV_NT;
					}
					else if(disp_inf->hdd_type==LX_PE_HDD_SRC_ATV50)
					{
						pbl_fmt = PE_SHP_O20_PBL_ATV_PAL;
					}
					else if(disp_inf->hdd_type==LX_PE_HDD_SRC_AV60 || \
						disp_inf->hdd_type==LX_PE_HDD_SRC_AV50 || \
						disp_inf->hdd_type==LX_PE_HDD_SRC_SCARTRGB)
					{
						pbl_fmt = PE_SHP_O20_PBL_AV;
					}
					else	//LX_PE_HDD_SRC_DTV
					{
						if(disp_inf->fmt_type==LX_PE_FMT_SD)
						{
							pbl_fmt = PE_SHP_O20_PBL_DTV_SD;
						}
						else if(disp_inf->fmt_type==LX_PE_FMT_HD)
						{
							pbl_fmt = PE_SHP_O20_PBL_HD;
						}
						else
						{
						 	if(g_pe_inf_o20_vr360_mode)
						 	{
								pbl_fmt = PE_SHP_O20_PBL_HD;
						 	}
							else
							{
								pbl_fmt = PE_SHP_O20_PBL_UD;
							}
						}
					}
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_O20_PBL_DTV_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					pbl_fmt = PE_SHP_O20_PBL_HD;
				}
				else
				{
					if(g_pe_inf_o20_vr360_mode)
				 	{
						pbl_fmt = PE_SHP_O20_PBL_HD;
				 	}
					else
					{
						pbl_fmt = PE_SHP_O20_PBL_UD;
					}
				}
				break;
			case LX_PE_SRC_COMP:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_O20_PBL_COMP_SD;
				}
				else
				{
					pbl_fmt = PE_SHP_O20_PBL_HD;
				}
				break;
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->hdmi_type==LX_PE_HDMI_PC)
				{
					pbl_fmt = PE_SHP_O20_PBL_PC;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					pbl_fmt = PE_SHP_O20_PBL_HDMI_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					pbl_fmt = PE_SHP_O20_PBL_HD;
				}
				else
				{
					if(g_pe_inf_o20_vr360_mode)
				 	{
						pbl_fmt = PE_SHP_O20_PBL_HD;
				 	}
					else
					{
						pbl_fmt = PE_SHP_O20_PBL_UD;
					}
				}
				break;
		}
	}
	return pbl_fmt;
}
#endif
/**
 * get cti(dnr) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_CTI_FMT
 * @see
 * @author
 */
static PE_SHP_HW_O20_CTI_FMT PE_SHP_HW_O20_ConvDispInfoToCtiFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_CTI_FMT cti_fmt = PE_SHP_O20_CTI_NUM;
	if(disp_inf->mode.is_vr)
	{
			cti_fmt = PE_SHP_O20_CTI_VR_360;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				{
					cti_fmt = PE_SHP_O20_CTI_ATV;
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
					cti_fmt = PE_SHP_O20_CTI_SD;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_HD)
				{
					cti_fmt = PE_SHP_O20_CTI_HD;
				}
				else
				{
					cti_fmt = PE_SHP_O20_CTI_UD;
				}
				break;
		}
	}
	return cti_fmt;
}

/**
 * get sre chr shp(srs) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_CHR_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O20_OBF_FMT PE_SHP_HW_O20_ConvDispInfoToObfFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_OBF_FMT srs_fmt = PE_SHP_O20_OBF_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			srs_fmt = PE_SHP_O20_OBF_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				srs_fmt = PE_SHP_O20_OBF_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				srs_fmt = PE_SHP_O20_OBF_HD;
			}
			else
			{
				srs_fmt = PE_SHP_O20_OBF_UD;
			}
			break;
	}
	return srs_fmt;
}

/**
 * get sre chr shp(srs) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_CHR_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O20_OBO_FMT PE_SHP_HW_O20_ConvDispInfoToOboFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_OBO_FMT srs_fmt = PE_SHP_O20_OBO_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			srs_fmt = PE_SHP_O20_OBO_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				srs_fmt = PE_SHP_O20_OBO_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				srs_fmt = PE_SHP_O20_OBO_HD;
			}
			else
			{
				srs_fmt = PE_SHP_O20_OBO_UD;
			}
			break;
	}
	return srs_fmt;
}
/**
 * get sre chr shp(srs) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_CHR_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O20_RCF_FMT PE_SHP_HW_O20_ConvDispInfoToRcfFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_RCF_FMT srs_fmt = PE_SHP_O20_RCF_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			srs_fmt = PE_SHP_O20_RCF_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				srs_fmt = PE_SHP_O20_RCF_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				srs_fmt = PE_SHP_O20_RCF_HD;
			}
			else
			{
				srs_fmt = PE_SHP_O20_RCF_UD;
			}
			break;
	}
	return srs_fmt;
}

/**
 * get sre chr shp(srs) fmt using display info(for O20X)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_SHP_HW_O20_CHR_FMT.
 * @see
 * @author
 */
static PE_SHP_HW_O20_RCO_FMT PE_SHP_HW_O20_ConvDispInfoToRcoFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_O20_RCO_FMT srs_fmt = PE_SHP_O20_RCO_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_SCART:
			srs_fmt = PE_SHP_O20_RCO_SD;
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		case LX_PE_SRC_RGBPC:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				srs_fmt = PE_SHP_O20_RCO_SD;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_HD)
			{
				srs_fmt = PE_SHP_O20_RCO_HD;
			}
			else
			{
				srs_fmt = PE_SHP_O20_RCO_UD;
			}
			break;
	}
	return srs_fmt;
}

/**
 * read default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_SHP_HW_O20_RdDefault(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 param_size=0, table_size=0, is_valid=0;
	UINT32 rd_cnt=0;
	PE_REG_PARAM_T param;
	PE_SHP_HW_O20_SETTINGS_T *pInfo=&_g_pe_shp_hw_o20_info;

#define PE_SHP_O20_NO_PRINT			0
#define PE_SHP_O20_RD_N_HEX_PRINT	1
#define PE_SHP_O20_HEX_PRINT_ONLY	2
#define PE_SHP_O20_PRINT_START		"START_OF_PRINT"
#define PE_SHP_O20_PRINT_END		"END_OF_PRINT"
#define PE_SHP_O20_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_SHP_O20_PRINT_RESRV		"RESERVED"
#define PE_SHP_O20_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, "   [0x%02X] %s\n", (_item), #_item);_action;break
#define PE_SHP_O20_CASE_SPRINT(_cnt, _action, _buf, fmt, args...)	\
	case (_cnt):snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break
#define PE_SHP_O20_DFLT_SPRINT(_action, _buf, fmt, args...)		\
	default:snprintf(_buf, PE_TRACE_STR_SIZE, fmt, ##args);_action;break

	do{
		if (PE_KDRV_VER_O20)
		{
			UINT32 *p_res_dflt = _g_pe_res_hw_param_data_o20.reg_dflt.addr;
			UINT32 *p_res_user = _g_pe_res_hw_param_data_o20.reg_user.addr;
			UINT32 *p_res_mask = _g_pe_res_hw_param_data_o20.reg_mask.addr;
			UINT32 *p_res_data = _g_pe_res_hw_param_data_o20.reg_data.addr;
			#if 0
			UINT32 *p_pbl_dflt = _g_pe_pbl_hw_param_data_o20.reg_dflt.addr;
			UINT32 *p_pbl_user = _g_pe_pbl_hw_param_data_o20.reg_user.addr;
			UINT32 *p_pbl_mask = _g_pe_pbl_hw_param_data_o20.reg_mask.addr;
			UINT32 *p_pbl_data = _g_pe_pbl_hw_param_data_o20.reg_data.addr;
			#endif
			UINT32 *p_cti_dflt = _g_pe_cti_hw_param_data_o20.reg_dflt.addr;
			UINT32 *p_cti_user = _g_pe_cti_hw_param_data_o20.reg_user.addr;
			UINT32 *p_cti_mask = _g_pe_cti_hw_param_data_o20.reg_mask.addr;
			UINT32 *p_cti_data = _g_pe_cti_hw_param_data_o20.reg_data.addr;
			#ifdef PE_SHP_HW_O20_SRE_SHP_WR_ONLY_MD
			//UINT32 *p_srs_dflt = _g_pe_srs_hw_param_data_o20.reg_dflt.addr;
			//UINT32 *p_srs_user = _g_pe_srs_hw_param_data_o20.reg_user.addr;
			//UINT32 *p_srs_mask = _g_pe_srs_hw_param_data_o20.reg_mask.addr;
			//UINT32 *p_srs_data = _g_pe_srs_hw_param_data_o20.reg_data.addr;
			UINT32 *p_srs_2k_dflt = _g_pe_srs_2k_hw_param_data_o20.reg_dflt.addr;
			UINT32 *p_srs_2k_user = _g_pe_srs_2k_hw_param_data_o20.reg_user.addr;
			UINT32 *p_srs_2k_mask = _g_pe_srs_2k_hw_param_data_o20.reg_mask.addr;
			UINT32 *p_srs_2k_data = _g_pe_srs_2k_hw_param_data_o20.reg_data.addr;
			#endif
			UINT32 *p_obf_dflt = _g_pe_obf_hw_param_data_o20.reg_dflt.addr;
			UINT32 *p_obf_user = _g_pe_obf_hw_param_data_o20.reg_user.addr;
			UINT32 *p_obf_mask = _g_pe_obf_hw_param_data_o20.reg_mask.addr;
			UINT32 *p_obf_data = _g_pe_obf_hw_param_data_o20.reg_data.addr;
			UINT32 *p_obo_dflt = _g_pe_obo_hw_param_data_o20.reg_dflt.addr;
			UINT32 *p_obo_user = _g_pe_obo_hw_param_data_o20.reg_user.addr;
			UINT32 *p_obo_mask = _g_pe_obo_hw_param_data_o20.reg_mask.addr;
			UINT32 *p_obo_data = _g_pe_obo_hw_param_data_o20.reg_data.addr;
			UINT32 *p_rcf_dflt = _g_pe_rcf_hw_param_data_o20.reg_dflt.addr;
			UINT32 *p_rcf_user = _g_pe_rcf_hw_param_data_o20.reg_user.addr;
			UINT32 *p_rcf_mask = _g_pe_rcf_hw_param_data_o20.reg_mask.addr;
			UINT32 *p_rcf_data = _g_pe_rcf_hw_param_data_o20.reg_data.addr;
			UINT32 *p_rco_dflt = _g_pe_rco_hw_param_data_o20.reg_dflt.addr;
			UINT32 *p_rco_user = _g_pe_rco_hw_param_data_o20.reg_user.addr;
			UINT32 *p_rco_mask = _g_pe_rco_hw_param_data_o20.reg_mask.addr;
			UINT32 *p_rco_data = _g_pe_rco_hw_param_data_o20.reg_data.addr;
			CHECK_KNULL(pstParams);
			CHECK_KNULL(pstParams->data);
			CHECK_KNULL(p_res_dflt);
			CHECK_KNULL(p_res_user);
			CHECK_KNULL(p_res_mask);
			CHECK_KNULL(p_res_data);
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]>=PE_SHP_HW_O20_RD_MENU_MAX)
			{
				snprintf(buffer, PE_TRACE_STR_SIZE, PE_SHP_O20_PRINT_EXIT);
				rd_cnt=0;
			}
			else if (pstParams->data[0]==PE_SHP_HW_O20_RD_MENU_DISP)
			{
				switch (rd_cnt)
				{
					PE_SHP_O20_CASE_SPRINT( 0, rd_cnt++, buffer, PE_SHP_O20_PRINT_START);
					PE_SHP_O20_CASE_SPRINT( 1, rd_cnt++, buffer, "   ** current default **\n");
					PE_SHP_O20_CASE_SPRINT( 2, rd_cnt++, buffer, \
						"   res0a_fmt : %s\n", PE_SHP_HW_O20_RES_FMT_TO_STR(pInfo->res0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 3, rd_cnt++, buffer, \
						"   cti0a_fmt : %s\n", PE_SHP_HW_O20_CTI_FMT_TO_STR(pInfo->cti0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 4, rd_cnt++, buffer, \
						"   pbl0a_fmt : %s\n", PE_SHP_HW_O20_PBL_FMT_TO_STR(pInfo->pbl0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 5, rd_cnt++, buffer, \
						"   sre0a_fmt : %s\n", PE_SHP_HW_O20_SRE_FMT_TO_STR(pInfo->sre0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 6, rd_cnt++, buffer, \
						"   srs0a_fmt : %s\n", PE_SHP_HW_O20_SRS_FMT_TO_STR(pInfo->srs0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 7, rd_cnt++, buffer, \
						"   k2s0a_fmt : %s\n", PE_SHP_HW_O20_2KS_FMT_TO_STR(pInfo->k2s0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 8, rd_cnt++, buffer, \
						"   obf0a_fmt : %s\n", PE_SHP_HW_O20_OBF_FMT_TO_STR(pInfo->obf0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 9, rd_cnt++, buffer, \
						"   obo0a_fmt : %s\n", PE_SHP_HW_O20_OBO_FMT_TO_STR(pInfo->obo0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 10, rd_cnt++, buffer, \
						"   rcf0a_fmt : %s\n", PE_SHP_HW_O20_RCF_FMT_TO_STR(pInfo->rcf0a_fmt));
					PE_SHP_O20_CASE_SPRINT( 11, rd_cnt++, buffer, \
						"   rco0a_fmt : %s\n", PE_SHP_HW_O20_RCO_FMT_TO_STR(pInfo->rco0a_fmt));
					PE_SHP_O20_CASE_SPRINT(12, rd_cnt++, buffer, "   *********************\n");
					PE_SHP_O20_CASE_PRMENU(13, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RES1_DISP);
					PE_SHP_O20_CASE_PRMENU(14, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RES2_DISP);
					PE_SHP_O20_CASE_PRMENU(15, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RES1_DFLT);
					PE_SHP_O20_CASE_PRMENU(16, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RES1_USER);
					PE_SHP_O20_CASE_PRMENU(17, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RES1_MASK);
					PE_SHP_O20_CASE_PRMENU(18, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RES1_DATA);
					PE_SHP_O20_CASE_PRMENU(19, rd_cnt++, buffer, PE_SHP_HW_O20_RD_CTI1_DISP);
					PE_SHP_O20_CASE_PRMENU(20, rd_cnt++, buffer, PE_SHP_HW_O20_RD_CTI2_DISP);
					PE_SHP_O20_CASE_PRMENU(21, rd_cnt++, buffer, PE_SHP_HW_O20_RD_CTI1_DFLT);
					PE_SHP_O20_CASE_PRMENU(22, rd_cnt++, buffer, PE_SHP_HW_O20_RD_CTI1_USER);
					PE_SHP_O20_CASE_PRMENU(23, rd_cnt++, buffer, PE_SHP_HW_O20_RD_CTI1_MASK);
					PE_SHP_O20_CASE_PRMENU(24, rd_cnt++, buffer, PE_SHP_HW_O20_RD_CTI1_DATA);
					PE_SHP_O20_CASE_PRMENU(25, rd_cnt++, buffer, PE_SHP_HW_O20_RD_PBL1_DISP);
					PE_SHP_O20_CASE_PRMENU(26, rd_cnt++, buffer, PE_SHP_HW_O20_RD_PBL2_DISP);
					PE_SHP_O20_CASE_PRMENU(27, rd_cnt++, buffer, PE_SHP_HW_O20_RD_PBL1_DFLT);
					PE_SHP_O20_CASE_PRMENU(28, rd_cnt++, buffer, PE_SHP_HW_O20_RD_PBL1_USER);
					PE_SHP_O20_CASE_PRMENU(29, rd_cnt++, buffer, PE_SHP_HW_O20_RD_PBL1_MASK);
					PE_SHP_O20_CASE_PRMENU(30, rd_cnt++, buffer, PE_SHP_HW_O20_RD_PBL1_DATA);
					#ifdef PE_SHP_HW_O20_SRE_SHP_WR_ONLY_MD
					PE_SHP_O20_CASE_SPRINT(31, rd_cnt++, buffer, PE_SHP_O20_PRINT_RESRV);
					PE_SHP_O20_CASE_SPRINT(32, rd_cnt++, buffer, PE_SHP_O20_PRINT_RESRV);
					PE_SHP_O20_CASE_PRMENU(33, rd_cnt++, buffer, PE_SHP_HW_O20_RD_SRS1_DISP);
					PE_SHP_O20_CASE_PRMENU(34, rd_cnt++, buffer, PE_SHP_HW_O20_RD_SRS1_DFLT);
					PE_SHP_O20_CASE_PRMENU(35, rd_cnt++, buffer, PE_SHP_HW_O20_RD_SRS1_USER);
					PE_SHP_O20_CASE_PRMENU(36, rd_cnt++, buffer, PE_SHP_HW_O20_RD_SRS1_MASK);
					PE_SHP_O20_CASE_PRMENU(37, rd_cnt++, buffer, PE_SHP_HW_O20_RD_SRS1_DATA);
					PE_SHP_O20_CASE_PRMENU(38, rd_cnt++, buffer, PE_SHP_HW_O20_RD_2KS1_DISP);
					PE_SHP_O20_CASE_PRMENU(39, rd_cnt++, buffer, PE_SHP_HW_O20_RD_2KS1_DFLT);
					PE_SHP_O20_CASE_PRMENU(40, rd_cnt++, buffer, PE_SHP_HW_O20_RD_2KS1_USER);
					PE_SHP_O20_CASE_PRMENU(41, rd_cnt++, buffer, PE_SHP_HW_O20_RD_2KS1_MASK);
					PE_SHP_O20_CASE_PRMENU(42, rd_cnt++, buffer, PE_SHP_HW_O20_RD_2KS1_DATA);
					PE_SHP_O20_CASE_PRMENU(43, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBF1_DISP);
					PE_SHP_O20_CASE_PRMENU(44, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBF1_DFLT);
					PE_SHP_O20_CASE_PRMENU(45, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBF1_USER);
					PE_SHP_O20_CASE_PRMENU(46, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBF1_MASK);
					PE_SHP_O20_CASE_PRMENU(47, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBO1_DATA);
					PE_SHP_O20_CASE_PRMENU(48, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBO1_DISP);
					PE_SHP_O20_CASE_PRMENU(49, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBO1_DFLT);
					PE_SHP_O20_CASE_PRMENU(50, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBO1_USER);
					PE_SHP_O20_CASE_PRMENU(51, rd_cnt++, buffer, PE_SHP_HW_O20_RD_OBO1_MASK);
					PE_SHP_O20_CASE_PRMENU(52, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCF1_DATA);
					PE_SHP_O20_CASE_PRMENU(53, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCF1_DISP);
					PE_SHP_O20_CASE_PRMENU(54, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCF1_DFLT);
					PE_SHP_O20_CASE_PRMENU(55, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCF1_USER);
					PE_SHP_O20_CASE_PRMENU(56, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCF1_MASK);
					PE_SHP_O20_CASE_PRMENU(57, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCF1_DATA);
					PE_SHP_O20_CASE_PRMENU(58, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCO1_DATA);
					PE_SHP_O20_CASE_PRMENU(59, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCO1_DISP);
					PE_SHP_O20_CASE_PRMENU(60, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCO1_DFLT);
					PE_SHP_O20_CASE_PRMENU(61, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCO1_USER);
					PE_SHP_O20_CASE_PRMENU(62, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCO1_MASK);
					PE_SHP_O20_CASE_PRMENU(63, rd_cnt++, buffer, PE_SHP_HW_O20_RD_RCO1_DATA);
					#endif	//#ifdef PE_SHP_HW_O20_SRE_SHP_WR_ONLY_MD
					PE_SHP_O20_DFLT_SPRINT(rd_cnt=0, buffer, PE_SHP_O20_PRINT_END);
				}
			}
			else
			{
				is_valid = PE_SHP_O20_NO_PRINT;
				switch (pstParams->data[0])
				{
					case PE_SHP_HW_O20_RD_RES1_DISP:
					case PE_SHP_HW_O20_RD_RES2_DISP:
						table_size = sizeof(shp_l_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_RES1_DFLT:
						table_size = sizeof(PE_RES_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o20[rd_cnt].addr;
							param.data = p_res_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RES1_USER:
						table_size = sizeof(PE_RES_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o20[rd_cnt].addr;
							param.data = p_res_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RES1_MASK:
						table_size = sizeof(PE_RES_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o20[rd_cnt].addr;
							param.data = p_res_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RES1_DATA:
						table_size = sizeof(PE_RES_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = shp_l_hd_default_o20[rd_cnt].addr;
							param.data = p_res_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_CTI1_DISP:
					case PE_SHP_HW_O20_RD_CTI2_DISP:
						table_size = sizeof(cti_y_l_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_CTI1_DFLT:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o20[rd_cnt].addr;
							param.data = p_cti_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_CTI1_USER:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o20[rd_cnt].addr;
							param.data = p_cti_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_CTI1_MASK:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o20[rd_cnt].addr;
							param.data = p_cti_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_CTI1_DATA:
						table_size = sizeof(PE_CTI_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = cti_y_l_hd_default_o20[rd_cnt].addr;
							param.data = p_cti_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					#if 0
					case PE_SHP_HW_O20_RD_PBL1_DISP:
					case PE_SHP_HW_O20_RD_PBL2_DISP:
						table_size = sizeof(pblur_dnr_l_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_PBL1_DFLT:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o20[rd_cnt].addr;
							param.data = p_pbl_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_PBL1_USER:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o20[rd_cnt].addr;
							param.data = p_pbl_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_PBL1_MASK:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o20[rd_cnt].addr;
							param.data = p_pbl_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_PBL1_DATA:
						table_size = sizeof(PE_PBL_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = pblur_dnr_l_hd_default_o20[rd_cnt].addr;
							param.data = p_pbl_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_SRS1_DISP:
						table_size = sizeof(sre_4k_res_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_SRS1_DFLT:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o20[rd_cnt].addr;
							param.data = p_srs_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_SRS1_USER:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o20[rd_cnt].addr;
							param.data = p_srs_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_SRS1_MASK:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o20[rd_cnt].addr;
							param.data = p_srs_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_SRS1_DATA:
						table_size = sizeof(PE_SRS_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_4k_res_hd_default_o20[rd_cnt].addr;
							param.data = p_srs_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					#endif
					case PE_SHP_HW_O20_RD_2KS1_DISP:
						table_size = sizeof(sre_2k_res_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_2KS1_DFLT:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o20[rd_cnt].addr;
							param.data = p_srs_2k_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_2KS1_USER:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o20[rd_cnt].addr;
							param.data = p_srs_2k_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_2KS1_MASK:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o20[rd_cnt].addr;
							param.data = p_srs_2k_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_2KS1_DATA:
						table_size = sizeof(PE_SRS_2K_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = sre_2k_res_hd_default_o20[rd_cnt].addr;
							param.data = p_srs_2k_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_OBF1_DISP:
						table_size = sizeof(obc_face_l_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = obc_face_l_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_OBF1_DFLT:
						table_size = sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = obc_face_l_hd_default_o20[rd_cnt].addr;
							param.data = p_obf_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_OBF1_USER:
						table_size = sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = obc_face_l_hd_default_o20[rd_cnt].addr;
							param.data = p_obf_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_OBF1_MASK:
						table_size = sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = obc_face_l_hd_default_o20[rd_cnt].addr;
							param.data = p_obf_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_OBF1_DATA:
						table_size = sizeof(PE_OBC_FACE_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = obc_face_l_hd_default_o20[rd_cnt].addr;
							param.data = p_obf_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_OBO1_DISP:
						table_size = sizeof(obc_objt_l_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = obc_objt_l_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_OBO1_DFLT:
						table_size = sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = obc_objt_l_hd_default_o20[rd_cnt].addr;
							param.data = p_obo_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_OBO1_USER:
						table_size = sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = obc_objt_l_hd_default_o20[rd_cnt].addr;
							param.data = p_obo_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_OBO1_MASK:
						table_size = sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = obc_objt_l_hd_default_o20[rd_cnt].addr;
							param.data = p_obo_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_OBO1_DATA:
						table_size = sizeof(PE_OBC_OBJT_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = obc_objt_l_hd_default_o20[rd_cnt].addr;
							param.data = p_obo_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RCF1_DISP:
						table_size = sizeof(rce_face_l_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = rce_face_l_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_RCF1_DFLT:
						table_size = sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = rce_face_l_hd_default_o20[rd_cnt].addr;
							param.data = p_rcf_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RCF1_USER:
						table_size = sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = rce_face_l_hd_default_o20[rd_cnt].addr;
							param.data = p_rcf_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RCF1_MASK:
						table_size = sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = rce_face_l_hd_default_o20[rd_cnt].addr;
							param.data = p_rcf_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RCF1_DATA:
						table_size = sizeof(PE_RCE_FACE_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = rce_face_l_hd_default_o20[rd_cnt].addr;
							param.data = p_rcf_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RCO1_DISP:
						table_size = sizeof(rce_objt_l_hd_default_o20);
						param_size = table_size/sizeof(PE_REG_PARAM_T);
						if (rd_cnt<param_size)
						{
							param.addr = rce_objt_l_hd_default_o20[rd_cnt].addr;
							is_valid = PE_SHP_O20_RD_N_HEX_PRINT;
						}
						break;
					case PE_SHP_HW_O20_RD_RCO1_DFLT:
						table_size = sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = rce_objt_l_hd_default_o20[rd_cnt].addr;
							param.data = p_rco_dflt[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RCO1_USER:
						table_size = sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = rce_objt_l_hd_default_o20[rd_cnt].addr;
							param.data = p_rco_user[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RCO1_MASK:
						table_size = sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = rce_objt_l_hd_default_o20[rd_cnt].addr;
							param.data = p_rco_mask[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					case PE_SHP_HW_O20_RD_RCO1_DATA:
						table_size = sizeof(PE_RCE_OBJT_HW_PARAM_REG_O20_T);
						param_size = table_size/sizeof(UINT32);
						if (rd_cnt<param_size)
						{
							param.addr = rce_objt_l_hd_default_o20[rd_cnt].addr;
							param.data = p_rco_data[rd_cnt];
							is_valid = PE_SHP_O20_HEX_PRINT_ONLY;
						}
						break;
					default:
						break;
				}
				if (is_valid == PE_SHP_O20_RD_N_HEX_PRINT)
				{
					param.data = PE_REG_O20_RD(param.addr);
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else if (is_valid == PE_SHP_O20_HEX_PRINT_ONLY)
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, "   [%04d] {0x%04X, 0x%08X},\n", \
						rd_cnt, param.addr, param.data);
					rd_cnt++;
				}
				else
				{
					snprintf(buffer, PE_TRACE_STR_SIZE, PE_SHP_O20_PRINT_END);
					rd_cnt = 0;
				}
			}
			memcpy(pstParams->data, buffer, sizeof(char)*PE_TRACE_STR_SIZE);
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetReEasyCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE_EASY_CMN_T *pp = (LX_PE_SHP_RE_EASY_CMN_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ui_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_vsd\n"
			"shp_ui_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_RES_WR04(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[0],0,8),\
													reg_mp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[1],0,8),\
													reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[2],0,8),\
													reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_vsd[3],0,8));
				PE_SHP_HW_O20_RES_WR03(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[4],0,8),\
													reg_sp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[5],0,8),\
													reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[6],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[7],0,8),\
													reg_mp_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[8],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[9],0,8),\
													reg_lc_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[10],0,8));

				#else
				PE_SHP_O20_QWr04(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[0],0,8),\
													reg_mp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[1],0,8),\
													reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[2],0,8),\
													reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_vsd[3],0,8));
				PE_SHP_O20_QWr03(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[4],0,8),\
													reg_sp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[5],0,8),\
													reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[6],0,8));
				PE_SHP_O20_QWr02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[7],0,8),\
													reg_mp_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[8],0,8));
				PE_SHP_O20_QWr02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[9],0,8),\
													reg_lc_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[10],0,8));
				#endif

			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE1_CMN_T *pp = (LX_PE_SHP_RE1_CMN_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ui_main_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_main_vsd\n"
			"shp_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);
			pd = pp->shp_face_obj_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_fobj_vsd\n"
			"shp_fobj_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
			#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
			
			PE_SHP_HW_O20_RES_WR01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_vsd[0],0,8));
			PE_SHP_HW_O20_RES_WR01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_vsd[1],0,8));
			PE_SHP_HW_O20_RES_WR01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul, 	GET_BITS(pp->shp_ui_main_vsd[2],0,6));
			PE_SHP_HW_O20_RES_WR01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul, 	GET_BITS(pp->shp_ui_main_vsd[3],0,6));
			PE_SHP_HW_O20_RES_WR01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_vsd[4],0,8));
			PE_SHP_HW_O20_RES_WR01(shp_der_ctrl_00, 	reg_derh_csft_gain, 	GET_BITS(pp->shp_ui_main_vsd[5],0,6));
			PE_SHP_HW_O20_RES_WR02(shp_der_ctrl_02, 	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_main_vsd[6],0,6),\
														reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_main_vsd[7],0,6));
			PE_SHP_HW_O20_RES_WR01(shp_mp_ctrl_01,		reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_main_vsd[8],0,8));
			PE_SHP_HW_O20_RES_WR01(shp_sp_ctrl_01,		reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_main_vsd[9],0,8));
			PE_SHP_HW_O20_RES_WR01(shp_mp_ctrl_01,		reg_mp_im_gain_v ,	GET_BITS(pp->shp_ui_main_vsd[10],0,8));
			PE_SHP_HW_O20_RES_WR01(shp_sti_ctrl_00, 	reg_sti_master_gain,GET_BITS(pp->shp_ui_main_vsd[11],0,8));
			PE_SHP_HW_O20_SHP_CTI_WR01(shp_cti_ctrl_00, 	reg_cti_gain,		GET_BITS(pp->shp_ui_main_vsd[12],0,8));
			PE_SHP_HW_O20_SHP_CTI_WR02(shp_cti_ctrl_02, 	reg_cti_ycm_y_gain, GET_BITS(pp->shp_ui_main_vsd[13],0,4),\
												reg_cti_ycm_c_gain, GET_BITS(pp->shp_ui_main_vsd[14],0,4));
			PE_SHP_HW_O20_RES_WR04(shp_obj_ctrl_09,	reg_obj_master_gain_lut_x0,	GET_BITS(pp->shp_face_obj_vsd[0],0,8),\
												reg_obj_master_gain_lut_y0,	GET_BITS(pp->shp_face_obj_vsd[1],0,8),\
												reg_obj_master_gain_lut_x1,	GET_BITS(pp->shp_face_obj_vsd[2],0,8),\
												reg_obj_master_gain_lut_y1,	GET_BITS(pp->shp_face_obj_vsd[3],0,8));
			PE_SHP_HW_O20_RES_WR04(shp_obj_ctrl_0a,	reg_obj_master_gain_lut_x2,	GET_BITS(pp->shp_face_obj_vsd[4],0,8),\
												reg_obj_master_gain_lut_y2,	GET_BITS(pp->shp_face_obj_vsd[5],0,8),\
												reg_obj_master_gain_lut_x3,	GET_BITS(pp->shp_face_obj_vsd[6],0,8),\
												reg_obj_master_gain_lut_y3,	GET_BITS(pp->shp_face_obj_vsd[7],0,8));
			#else
			PE_SHP_O20_QWr01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_vsd[0],0,8));
			PE_SHP_O20_QWr01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_vsd[1],0,8));
			PE_SHP_O20_QWr01(shp_dj_ctrl_1e,	reg_dj_soft_g1_mul, 	GET_BITS(pp->shp_ui_main_vsd[2],0,6));
			PE_SHP_O20_QWr01(shp_dj_ctrl_1f,	reg_dj_soft_g2_mul, 	GET_BITS(pp->shp_ui_main_vsd[3],0,6));
			PE_SHP_O20_QWr01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_vsd[4],0,8));
			PE_SHP_O20_QWr01(shp_der_ctrl_00, 	reg_derh_csft_gain, 	GET_BITS(pp->shp_ui_main_vsd[5],0,6));
			PE_SHP_O20_QWr02(shp_der_ctrl_02, 	reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_main_vsd[6],0,6),\
												reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_main_vsd[7],0,6));
			PE_SHP_O20_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_h,		GET_BITS(pp->shp_ui_main_vsd[8],0,8));
			PE_SHP_O20_QWr01(shp_sp_ctrl_01,	reg_sp_im_gain_h,		GET_BITS(pp->shp_ui_main_vsd[9],0,8));
			PE_SHP_O20_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_v ,		GET_BITS(pp->shp_ui_main_vsd[10],0,8));
			PE_SHP_O20_QWr01(shp_sti_ctrl_00, 	reg_sti_master_gain,	GET_BITS(pp->shp_ui_main_vsd[11],0,8));
			PE_SHP_O20_QWr01(shp_cti_ctrl_00, 	reg_cti_gain,			GET_BITS(pp->shp_ui_main_vsd[12],0,8));
			PE_SHP_O20_QWr02(shp_cti_ctrl_02, 	reg_cti_ycm_y_gain, 	GET_BITS(pp->shp_ui_main_vsd[13],0,4),\
												reg_cti_ycm_c_gain, 	GET_BITS(pp->shp_ui_main_vsd[14],0,4));
			#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE1_CMN_T *pp = (LX_PE_SHP_RE1_CMN_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ui_main_vsd;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O20_QRd01(shp_dctp_ctrl_1d,	reg_dctp_gain,			pp->shp_ui_main_vsd[0]);
				PE_SHP_O20_QRd01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	pp->shp_ui_main_vsd[1]);
				PE_SHP_O20_QRd01(shp_dj_ctrl_1e,	reg_dj_soft_g1_mul,		pp->shp_ui_main_vsd[2]);
				PE_SHP_O20_QRd01(shp_dj_ctrl_1f,	reg_dj_soft_g2_mul,		pp->shp_ui_main_vsd[3]);
				PE_SHP_O20_QRd01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	pp->shp_ui_main_vsd[4]);
				PE_SHP_O20_QRd01(shp_der_ctrl_00,	reg_derh_csft_gain,		pp->shp_ui_main_vsd[5]);
				PE_SHP_O20_QRd02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,	pp->shp_ui_main_vsd[6],\
													reg_derh_edge_filter_gain_b,	pp->shp_ui_main_vsd[7]);
				PE_SHP_O20_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,	pp->shp_ui_main_vsd[8]);
				PE_SHP_O20_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,	pp->shp_ui_main_vsd[9]);
				PE_SHP_O20_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v ,	pp->shp_ui_main_vsd[10]);
				PE_SHP_O20_QRd01(shp_sti_ctrl_00,	reg_sti_master_gain,pp->shp_ui_main_vsd[11]);
				PE_SHP_O20_QRd01(shp_cti_ctrl_00,	reg_cti_gain,		pp->shp_ui_main_vsd[12]);
				PE_SHP_O20_QRd01(shp_cti_ctrl_02,	reg_cti_ycm_y_gain,	pp->shp_ui_main_vsd[13]);
				PE_SHP_O20_QRd01(shp_cti_ctrl_02,	reg_cti_ycm_c_gain,	pp->shp_ui_main_vsd[14]);
			}

			pd = pp->shp_ui_main_vsd;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_main_vsd\n"
			"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set resolution horizontal control
 * - use input struct LX_PE_SHP_RE2_HOR_T for O20X
 * - use input struct LX_PE_SHP_RE1_HOR_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_HOR_T *pp=(LX_PE_SHP_RE5_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_h_main_vsd\n"
			"shp_ui_h_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_RES_WR01(shp_der_ctrl_00,	reg_derh_csft_gain,			GET_BITS(pp->shp_ui_h_main_vsd[0],0,6));
				PE_SHP_HW_O20_RES_WR02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_vsd[1],0,6),\
														reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_vsd[2],0,6));
				PE_SHP_HW_O20_RES_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_vsd[3],0,8));
				PE_SHP_HW_O20_RES_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_vsd[4],0,8));
				PE_SHP_HW_O20_RES_WR01(shp_pti_ctrl_01,	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_vsd[5],0,8));
				#else
				PE_SHP_O20_QWr01(shp_der_ctrl_00,	reg_derh_csft_gain,			GET_BITS(pp->shp_ui_h_main_vsd[0],0,6));
				PE_SHP_O20_QWr02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_vsd[1],0,6),\
													reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_vsd[2],0,6));
				PE_SHP_O20_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_vsd[3],0,8));
				PE_SHP_O20_QWr01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_vsd[4],0,8));
				PE_SHP_O20_QWr01(shp_pti_ctrl_01,	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_vsd[5],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get resolution horizontal control
 * - use input struct LX_PE_SHP_RE2_HOR_T for O20X
 * - use input struct LX_PE_SHP_RE1_HOR_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_HOR_T *pp = (LX_PE_SHP_RE5_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_vsd;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O20_QRd01(shp_der_ctrl_00,	reg_derh_csft_gain,			pp->shp_ui_h_main_vsd[0]);
				PE_SHP_O20_QRd02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,pp->shp_ui_h_main_vsd[1],\
													reg_derh_edge_filter_gain_b,pp->shp_ui_h_main_vsd[2]);
				PE_SHP_O20_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			pp->shp_ui_h_main_vsd[3]);
				PE_SHP_O20_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			pp->shp_ui_h_main_vsd[4]);
				PE_SHP_O20_QRd01(shp_pti_ctrl_01,	reg_ptih_master_gain,		pp->shp_ui_h_main_vsd[5]);
			}

			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_h_main_vsd\n"
				"shp_ui_h_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for O20X
 * - use input struct LX_PE_SHP_RE1_VER_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_VER_T *pp=(LX_PE_SHP_RE5_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_v_main_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_v_main_post\n"\
			"shp_ui_v_main_post[00]0x%02X,0x%02X\n",\
			pp->win_id,	pd[0],  pd[1]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_RES_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v ,	GET_BITS(pp->shp_ui_v_main_vsd[0],0,8));
				PE_SHP_HW_O20_RES_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_vsd[1],0,8));
				#else
				PE_SHP_O20_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_v ,	GET_BITS(pp->shp_ui_v_main_vsd[0],0,8));
				PE_SHP_O20_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_vsd[1],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for O20X
 * - use input struct LX_PE_SHP_RE1_VER_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE5_VER_T *pp = (LX_PE_SHP_RE5_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_v_main_vsd;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O20_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v ,		pp->shp_ui_v_main_vsd[0]);
				PE_SHP_O20_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	pp->shp_ui_v_main_vsd[1]);
			}
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_v_main_vsd\n"
			"shp_ui_v_main_vsd    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for O20X
 * - use input struct LX_PE_SHP_RE1_MISC_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{ 
			UINT8 *pd;
			LX_PE_SHP_RE1_MISC_T *pp=(LX_PE_SHP_RE1_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_cmn_vsd\n"
			"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24]);
			pd = pp->shp_djg_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_djg_vsd\n"
			"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
			pd = pp->shp_map_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_map_cmn_vsd\n"
			"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_balance_vsd\n"
			"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ti_cmn_vsd\n"
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_chroma_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_chroma_vsd\n"
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				/*shp_cmn_vsd*/
				PE_SHP_HW_O20_RES_WR02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_vsd[0],0,1),\
														reg_derh_bflt_tap_size,		GET_BITS(pp->shp_cmn_vsd[1],0,3));
				PE_SHP_HW_O20_RES_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,		GET_BITS(pp->shp_cmn_vsd[2],0,1));
				PE_SHP_HW_O20_RES_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,		GET_BITS(pp->shp_cmn_vsd[3],0,1));
				PE_SHP_HW_O20_RES_WR02(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_cmn_vsd[4],0,7),\
														reg_mp_im_us_gain,	GET_BITS(pp->shp_cmn_vsd[5],0,7));
				PE_SHP_HW_O20_RES_WR02(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_cmn_vsd[6],0,7),\
														reg_sp_im_us_gain,	GET_BITS(pp->shp_cmn_vsd[7],0,7));
				PE_SHP_HW_O20_RES_WR01(shp_esf_ctrl_00, reg_esf_en, 		GET_BITS(pp->shp_cmn_vsd[8],0,1));
				PE_SHP_HW_O20_RES_WR03(shp_esf_ctrl_01, reg_esf_min_ratio,	GET_BITS(pp->shp_cmn_vsd[9],0,8),\
														reg_esf_base,		GET_BITS(pp->shp_cmn_vsd[10],0,8),\
														reg_esf_max_clip,	GET_BITS(pp->shp_cmn_vsd[11],0,8));
				PE_SHP_HW_O20_RES_WR01(shp_dctp_ctrl_00,reg_dctp_en,		GET_BITS(pp->shp_cmn_vsd[12],0,1));
				PE_SHP_HW_O20_RES_WR02(shp_dctp_ctrl_1e,reg_dctp_coring_en, GET_BITS(pp->shp_cmn_vsd[13],0,1),\
														reg_dctp_coring_mode,	GET_BITS(pp->shp_cmn_vsd[14],0,2));
				PE_SHP_HW_O20_RES_WR01(shp_tgen_ctrl_00,reg_tgen_on_off,		GET_BITS(pp->shp_cmn_vsd[15],0,1));
				PE_SHP_HW_O20_RES_WR02(shp_tgen_ctrl_0a,reg_tgen_coring_en, 	GET_BITS(pp->shp_cmn_vsd[16],0,1),\
														reg_tgen_coring_mode,	GET_BITS(pp->shp_cmn_vsd[17],0,2));
				PE_SHP_HW_O20_RES_WR01(shp_nntg_ctrl_00,reg_nntg_en,			GET_BITS(pp->shp_cmn_vsd[18],0,1));
				PE_SHP_HW_O20_RES_WR02(shp_nntg_ctrl_0f,reg_nntg_coring_en, 	GET_BITS(pp->shp_cmn_vsd[19],0,1),\
														reg_nntg_coring_mode,	GET_BITS(pp->shp_cmn_vsd[20],0,2));
				PE_SHP_HW_O20_RES_WR01(shp_motion_prot_ctrl_00, reg_motion_prot_adaptive_en,	GET_BITS(pp->shp_cmn_vsd[21],0,1));
				PE_SHP_HW_O20_SHP_CTI_WR01(shp_cti_ctrl_00, reg_cti_en, 			GET_BITS(pp->shp_cmn_vsd[22],0,1));
				PE_SHP_HW_O20_SHP_CTI_WR01(shp_cti_ctrl_02, reg_cti_ycm_en, 		GET_BITS(pp->shp_cmn_vsd[23],0,1));
				PE_SHP_HW_O20_SHP_CTI_WR01(shp_cti_ctrl_00, reg_cti_filter_tap_size,GET_BITS(pp->shp_cmn_vsd[24],0,3));
				/*shp_djg_vsd*/
				PE_SHP_HW_O20_RES_WR03(shp_dj_ctrl_00,	reg_dj_edf_en,				GET_BITS(pp->shp_djg_vsd[0],0,1),\
														reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_vsd[1],0,1),\
														reg_dj_soft_en, 			GET_BITS(pp->shp_djg_vsd[2],0,1));
				PE_SHP_HW_O20_RES_WR02(shp_dj_ctrl_03,	reg_dj_edge_min,			GET_BITS(pp->shp_djg_vsd[3],0,8),\
														reg_dj_edge_mul,			GET_BITS(pp->shp_djg_vsd[4],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_dj_ctrl_00,	reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_vsd[5],0,2),\
														reg_dj_n_avg_mode,			GET_BITS(pp->shp_djg_vsd[6],0,1));
				PE_SHP_HW_O20_RES_WR01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			GET_BITS(pp->shp_djg_vsd[7],0,8));

				/*shp_map_cmn_vsd */
				PE_SHP_HW_O20_RES_WR02(shp_fd_ctrl_0b,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[0],0,1),\
														reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
				PE_SHP_HW_O20_RES_WR04(shp_fd_ctrl_0d,	reg_fd_mnr_gain_x0, GET_BITS(pp->shp_map_cmn_vsd[2],0,8),\
														reg_fd_mnr_gain_x1, GET_BITS(pp->shp_map_cmn_vsd[3],0,8),\
														reg_fd_mnr_gain_y0, GET_BITS(pp->shp_map_cmn_vsd[4],0,8),\
														reg_fd_mnr_gain_y1, GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_fd_ctrl_11,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[6],0,1),\
														reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[7],0,1));
				PE_SHP_HW_O20_RES_WR04(shp_fd_ctrl_14,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_vsd[8],0,6),\
														reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_vsd[9],0,6),\
														reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_vsd[10],0,6),\
														reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_vsd[11],0,6));

				/*shp_balance_vsd*/
				PE_SHP_HW_O20_RES_WR03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_vsd[0],0,1),\
														reg_mp_gb_mode, GET_BITS(pp->shp_balance_vsd[1],0,1),\
														reg_mp_gb_y1,	GET_BITS(pp->shp_balance_vsd[2],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_vsd[3],0,8),\
														reg_mp_gb_y3,	GET_BITS(pp->shp_balance_vsd[4],0,8));
				PE_SHP_HW_O20_RES_WR03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_vsd[5],0,1),\
														reg_sp_gb_mode, GET_BITS(pp->shp_balance_vsd[6],0,1),\
														reg_sp_gb_y1,	GET_BITS(pp->shp_balance_vsd[7],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_vsd[8],0,8),\
														reg_sp_gb_y3,	GET_BITS(pp->shp_balance_vsd[9],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_vsd[10],0,1),\
														reg_lc_gb_en,	GET_BITS(pp->shp_balance_vsd[11],0,1));
				PE_SHP_HW_O20_RES_WR02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_vsd[12],0,8),\
														reg_lc_gb_y2,	GET_BITS(pp->shp_balance_vsd[13],0,8));
				PE_SHP_HW_O20_RES_WR01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_vsd[14],0,8));
				PE_SHP_HW_O20_RES_WR03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_vsd[15],0,8),\
														reg_lc_center_gain, GET_BITS(pp->shp_balance_vsd[16],0,8),\
														reg_lc_local_gain,	GET_BITS(pp->shp_balance_vsd[17],0,8));
				PE_SHP_HW_O20_RES_WR03(shp_mp_ctrl_08,	reg_mp_lum1_y0, GET_BITS(pp->shp_balance_vsd[18],0,8),\
														reg_mp_lum1_y1, GET_BITS(pp->shp_balance_vsd[19],0,8),\
														reg_mp_lum1_y2, GET_BITS(pp->shp_balance_vsd[20],0,8));
				PE_SHP_HW_O20_RES_WR01(shp_mp_ctrl_09,	reg_mp_lum2_y0, GET_BITS(pp->shp_balance_vsd[21],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, GET_BITS(pp->shp_balance_vsd[22],0,8),\
														reg_mp_lum2_y2, GET_BITS(pp->shp_balance_vsd[23],0,8));
				PE_SHP_HW_O20_RES_WR03(shp_sp_ctrl_08,	reg_sp_lum1_y0, GET_BITS(pp->shp_balance_vsd[24],0,8),\
														reg_sp_lum1_y1, GET_BITS(pp->shp_balance_vsd[25],0,8),\
														reg_sp_lum1_y2, GET_BITS(pp->shp_balance_vsd[26],0,8));
				PE_SHP_HW_O20_RES_WR01(shp_sp_ctrl_09,	reg_sp_lum2_y0, GET_BITS(pp->shp_balance_vsd[27],0,8));
				PE_SHP_HW_O20_RES_WR02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, GET_BITS(pp->shp_balance_vsd[28],0,8),\
														reg_sp_lum2_y2, GET_BITS(pp->shp_balance_vsd[29],0,8));
				/*shp_ti_cmn_vsd*/
				PE_SHP_HW_O20_RES_WR04(shp_pti_ctrl_00, reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_vsd[0],0,1),\
														reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
				PE_SHP_HW_O20_RES_WR04(shp_pti_ctrl_01, reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_vsd[4],0,1),\
														reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
				PE_SHP_HW_O20_RES_WR04(shp_sti_ctrl_00, reg_sti_enable, 		GET_BITS(pp->shp_ti_cmn_vsd[8],0,1),\
														reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
				PE_SHP_HW_O20_RES_WR02(shp_snr_ctrl_00, reg_snr_blur_en,		GET_BITS(pp->shp_ti_cmn_vsd[12],0,1),\
														reg_snr_blur_sel,		GET_BITS(pp->shp_ti_cmn_vsd[13],0,2));
				/*shp_chroma_vsd*/
				PE_SHP_HW_O20_RES_WR03(shp_chroma_ctrl_00,	reg_color_region_en,	GET_BITS(pp->shp_chroma_vsd[0],0,1),\
															reg_chr_protection_en,	GET_BITS(pp->shp_chroma_vsd[1],0,1),\
															reg_chr_compensation_en,	GET_BITS(pp->shp_chroma_vsd[2],0,1));
				PE_SHP_HW_O20_RES_WR02(shp_chroma_ctrl_0d,	reg_chr_gain_r0_gain,	GET_BITS(pp->shp_chroma_vsd[3],0,8),\
															reg_chr_gain_r1_gain,	GET_BITS(pp->shp_chroma_vsd[4],0,8));
				#else
				PE_SHP_O20_QWr01(shp_mp_ctrl_00,	reg_mp_shp_en,		GET_BITS(pp->shp_cmn_vsd[2],0,1));
				PE_SHP_O20_QWr01(shp_sp_ctrl_00,	reg_sp_shp_en,		GET_BITS(pp->shp_cmn_vsd[3],0,1));
				PE_SHP_O20_QWr02(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_cmn_vsd[4],0,7),\
													reg_mp_im_us_gain,	GET_BITS(pp->shp_cmn_vsd[5],0,7));
				PE_SHP_O20_QWr02(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_cmn_vsd[6],0,7),\
													reg_sp_im_us_gain,	GET_BITS(pp->shp_cmn_vsd[7],0,7));
				PE_SHP_O20_QWr01(shp_esf_ctrl_00, 	reg_esf_en, 		GET_BITS(pp->shp_cmn_vsd[8],0,1));
				PE_SHP_O20_QWr03(shp_esf_ctrl_01, 	reg_esf_min_ratio,	GET_BITS(pp->shp_cmn_vsd[9],0,8),\
													reg_esf_base,		GET_BITS(pp->shp_cmn_vsd[10],0,8),\
													reg_esf_max_clip,	GET_BITS(pp->shp_cmn_vsd[11],0,8));
				PE_SHP_O20_QWr01(shp_dctp_ctrl_00,reg_dctp_en,		GET_BITS(pp->shp_cmn_vsd[12],0,1));
				PE_SHP_O20_QWr02(shp_dctp_ctrl_1e,reg_dctp_coring_en, GET_BITS(pp->shp_cmn_vsd[13],0,1),\
												  reg_dctp_coring_mode,	GET_BITS(pp->shp_cmn_vsd[14],0,2));
				PE_SHP_O20_QWr01(shp_tgen_ctrl_00,reg_tgen_on_off,		GET_BITS(pp->shp_cmn_vsd[15],0,1));
				PE_SHP_O20_QWr02(shp_tgen_ctrl_0a,reg_tgen_coring_en, 	GET_BITS(pp->shp_cmn_vsd[16],0,1),\
													reg_tgen_coring_mode,	GET_BITS(pp->shp_cmn_vsd[17],0,2));
				PE_SHP_O20_QWr01(shp_nntg_ctrl_00,reg_nntg_en,			GET_BITS(pp->shp_cmn_vsd[18],0,1));
				PE_SHP_O20_QWr02(shp_nntg_ctrl_0f,reg_nntg_coring_en, 	GET_BITS(pp->shp_cmn_vsd[19],0,1),\
														reg_nntg_coring_mode,	GET_BITS(pp->shp_cmn_vsd[20],0,2));
				PE_SHP_O20_QWr01(shp_motion_prot_ctrl_00, reg_motion_prot_adaptive_en,	GET_BITS(pp->shp_cmn_vsd[21],0,1));
				PE_SHP_O20_QWr01(shp_cti_ctrl_00, reg_cti_en, 			GET_BITS(pp->shp_cmn_vsd[22],0,1));
				PE_SHP_O20_QWr01(shp_cti_ctrl_02, reg_cti_ycm_en, 		GET_BITS(pp->shp_cmn_vsd[23],0,1));
				PE_SHP_O20_QWr01(shp_cti_ctrl_00, reg_cti_filter_tap_size,GET_BITS(pp->shp_cmn_vsd[24],0,3));
				/*shp_djg_vsd*/
				PE_SHP_O20_QWr03(shp_dj_ctrl_00,	reg_dj_edf_en,				GET_BITS(pp->shp_djg_vsd[0],0,1),\
														reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_vsd[1],0,1),\
														reg_dj_soft_en, 			GET_BITS(pp->shp_djg_vsd[2],0,1));
				PE_SHP_O20_QWr02(shp_dj_ctrl_03,	reg_dj_edge_min,			GET_BITS(pp->shp_djg_vsd[3],0,8),\
														reg_dj_edge_mul,			GET_BITS(pp->shp_djg_vsd[4],0,8));
				PE_SHP_O20_QWr02(shp_dj_ctrl_00,	reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_vsd[5],0,2),\
														reg_dj_n_avg_mode,			GET_BITS(pp->shp_djg_vsd[6],0,1));
				PE_SHP_O20_QWr01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			GET_BITS(pp->shp_djg_vsd[7],0,8));

				/*shp_map_cmn_vsd */
				PE_SHP_O20_QWr02(shp_fd_ctrl_0b,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[0],0,1),\
														reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[1],0,1));
				PE_SHP_O20_QWr04(shp_fd_ctrl_0d,	reg_fd_mnr_gain_x0, GET_BITS(pp->shp_map_cmn_vsd[2],0,8),\
														reg_fd_mnr_gain_x1, GET_BITS(pp->shp_map_cmn_vsd[3],0,8),\
														reg_fd_mnr_gain_y0, GET_BITS(pp->shp_map_cmn_vsd[4],0,8),\
														reg_fd_mnr_gain_y1, GET_BITS(pp->shp_map_cmn_vsd[5],0,8));
				PE_SHP_O20_QWr02(shp_fd_ctrl_11,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_vsd[6],0,1),\
														reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_vsd[7],0,1));
				PE_SHP_O20_QWr04(shp_fd_ctrl_14,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_vsd[8],0,6),\
														reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_vsd[9],0,6),\
														reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_vsd[10],0,6),\
														reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_vsd[11],0,6));

				/*shp_balance_vsd*/
				PE_SHP_O20_QWr03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_vsd[0],0,1),\
														reg_mp_gb_mode, GET_BITS(pp->shp_balance_vsd[1],0,1),\
														reg_mp_gb_y1,	GET_BITS(pp->shp_balance_vsd[2],0,8));
				PE_SHP_O20_QWr02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_vsd[3],0,8),\
														reg_mp_gb_y3,	GET_BITS(pp->shp_balance_vsd[4],0,8));
				PE_SHP_O20_QWr03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_vsd[5],0,1),\
														reg_sp_gb_mode, GET_BITS(pp->shp_balance_vsd[6],0,1),\
														reg_sp_gb_y1,	GET_BITS(pp->shp_balance_vsd[7],0,8));
				PE_SHP_O20_QWr02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_vsd[8],0,8),\
														reg_sp_gb_y3,	GET_BITS(pp->shp_balance_vsd[9],0,8));
				PE_SHP_O20_QWr02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_vsd[10],0,1),\
														reg_lc_gb_en,	GET_BITS(pp->shp_balance_vsd[11],0,1));
				PE_SHP_O20_QWr02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_vsd[12],0,8),\
														reg_lc_gb_y2,	GET_BITS(pp->shp_balance_vsd[13],0,8));
				PE_SHP_O20_QWr01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_vsd[14],0,8));
				PE_SHP_O20_QWr03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_vsd[15],0,8),\
														reg_lc_center_gain, GET_BITS(pp->shp_balance_vsd[16],0,8),\
														reg_lc_local_gain,	GET_BITS(pp->shp_balance_vsd[17],0,8));
				PE_SHP_O20_QWr03(shp_mp_ctrl_08,	reg_mp_lum1_y0, GET_BITS(pp->shp_balance_vsd[18],0,8),\
														reg_mp_lum1_y1, GET_BITS(pp->shp_balance_vsd[19],0,8),\
														reg_mp_lum1_y2, GET_BITS(pp->shp_balance_vsd[20],0,8));
				PE_SHP_O20_QWr01(shp_mp_ctrl_09,	reg_mp_lum2_y0, GET_BITS(pp->shp_balance_vsd[21],0,8));
				PE_SHP_O20_QWr02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, GET_BITS(pp->shp_balance_vsd[22],0,8),\
														reg_mp_lum2_y2, GET_BITS(pp->shp_balance_vsd[23],0,8));
				PE_SHP_O20_QWr03(shp_sp_ctrl_08,	reg_sp_lum1_y0, GET_BITS(pp->shp_balance_vsd[24],0,8),\
														reg_sp_lum1_y1, GET_BITS(pp->shp_balance_vsd[25],0,8),\
														reg_sp_lum1_y2, GET_BITS(pp->shp_balance_vsd[26],0,8));
				PE_SHP_O20_QWr01(shp_sp_ctrl_09,	reg_sp_lum2_y0, GET_BITS(pp->shp_balance_vsd[27],0,8));
				PE_SHP_O20_QWr02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, GET_BITS(pp->shp_balance_vsd[28],0,8),\
														reg_sp_lum2_y2, GET_BITS(pp->shp_balance_vsd[29],0,8));
				/*shp_ti_cmn_vsd*/
				PE_SHP_O20_QWr04(shp_pti_ctrl_00, reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_vsd[0],0,1),\
														reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[1],0,1),\
														reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[2],0,2),\
														reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[3],0,2));
				PE_SHP_O20_QWr04(shp_pti_ctrl_01, reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_vsd[4],0,1),\
														reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[5],0,1),\
														reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[6],0,2),\
														reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[7],0,2));
				PE_SHP_O20_QWr04(shp_sti_ctrl_00, reg_sti_enable, 		GET_BITS(pp->shp_ti_cmn_vsd[8],0,1),\
														reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_vsd[9],0,1),\
														reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[10],0,2),\
														reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_vsd[11],0,2));
				PE_SHP_O20_QWr02(shp_snr_ctrl_00, reg_snr_blur_en,		GET_BITS(pp->shp_ti_cmn_vsd[12],0,1),\
														reg_snr_blur_sel,		GET_BITS(pp->shp_ti_cmn_vsd[13],0,2));
				/*shp_chroma_vsd*/
				PE_SHP_O20_QWr03(shp_chroma_ctrl_00,	reg_color_region_en,	GET_BITS(pp->shp_chroma_vsd[0],0,1),\
															reg_chr_protection_en,	GET_BITS(pp->shp_chroma_vsd[1],0,1),\
															reg_chr_compensation_en,	GET_BITS(pp->shp_chroma_vsd[2],0,1));
				PE_SHP_O20_QWr02(shp_chroma_ctrl_0d,	reg_chr_gain_r0_gain,	GET_BITS(pp->shp_chroma_vsd[3],0,8),\
															reg_chr_gain_r1_gain,	GET_BITS(pp->shp_chroma_vsd[4],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		
	} while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for O20X
 * - use input struct LX_PE_SHP_RE1_MISC_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE1_MISC_T *pp=(LX_PE_SHP_RE1_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SHP_O20_QRd02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	pp->shp_cmn_vsd[0],\
													reg_derh_bflt_tap_size,		pp->shp_cmn_vsd[1]);
				PE_SHP_O20_QRd01(shp_mp_ctrl_00,	reg_mp_shp_en,		pp->shp_cmn_vsd[2]);
				PE_SHP_O20_QRd01(shp_sp_ctrl_00,	reg_sp_shp_en,		pp->shp_cmn_vsd[3]);
				PE_SHP_O20_QRd02(shp_mp_ctrl_01,	reg_mp_im_os_gain,	pp->shp_cmn_vsd[4],\
													reg_mp_im_us_gain,	pp->shp_cmn_vsd[5]);
				PE_SHP_O20_QRd02(shp_sp_ctrl_01,	reg_sp_im_os_gain,	pp->shp_cmn_vsd[6],\
													reg_sp_im_us_gain,	pp->shp_cmn_vsd[7]);
				PE_SHP_O20_QRd01(shp_esf_ctrl_00, 	reg_esf_en, 		pp->shp_cmn_vsd[8]);
				PE_SHP_O20_QRd03(shp_esf_ctrl_01, 	reg_esf_min_ratio,	pp->shp_cmn_vsd[9],\
													reg_esf_base,		pp->shp_cmn_vsd[10],\
													reg_esf_max_clip,	pp->shp_cmn_vsd[11]);
				PE_SHP_O20_QRd01(shp_dctp_ctrl_00,	reg_dctp_en,		pp->shp_cmn_vsd[12]);
				PE_SHP_O20_QRd02(shp_dctp_ctrl_1e,	reg_dctp_coring_en, pp->shp_cmn_vsd[13],\
												  	reg_dctp_coring_mode,	pp->shp_cmn_vsd[14]);
				PE_SHP_O20_QRd01(shp_tgen_ctrl_00,	reg_tgen_on_off,		pp->shp_cmn_vsd[15]);
				PE_SHP_O20_QRd02(shp_tgen_ctrl_0a,	reg_tgen_coring_en, 	pp->shp_cmn_vsd[16],\
													reg_tgen_coring_mode,	pp->shp_cmn_vsd[17]);
				PE_SHP_O20_QRd01(shp_nntg_ctrl_00,	reg_nntg_en,			pp->shp_cmn_vsd[18]);
				PE_SHP_O20_QRd02(shp_nntg_ctrl_0f,	reg_nntg_coring_en, 	pp->shp_cmn_vsd[19],\
													reg_nntg_coring_mode,	pp->shp_cmn_vsd[20]);
				PE_SHP_O20_QRd01(shp_motion_prot_ctrl_00, reg_motion_prot_adaptive_en,	pp->shp_cmn_vsd[21]);
				PE_SHP_O20_QRd01(shp_cti_ctrl_00, 	reg_cti_en, 			pp->shp_cmn_vsd[22]);
				PE_SHP_O20_QRd01(shp_cti_ctrl_02, 	reg_cti_ycm_en, 		pp->shp_cmn_vsd[23]);
				PE_SHP_O20_QRd01(shp_cti_ctrl_00, 	reg_cti_filter_tap_size,pp->shp_cmn_vsd[24]);
				/*shp_djg_vsd*/
				PE_SHP_O20_QRd03(shp_dj_ctrl_00,	reg_dj_edf_en,				pp->shp_djg_vsd[0],\
													reg_dj_edge_adaptive_en,	pp->shp_djg_vsd[1],\
													reg_dj_soft_en, 			pp->shp_djg_vsd[2]);
				PE_SHP_O20_QRd02(shp_dj_ctrl_03,	reg_dj_edge_min,			pp->shp_djg_vsd[3],\
													reg_dj_edge_mul,			pp->shp_djg_vsd[4]);
				PE_SHP_O20_QRd02(shp_dj_ctrl_00,	reg_dj_center_blur_mode,	pp->shp_djg_vsd[5],\
													reg_dj_n_avg_mode,			pp->shp_djg_vsd[6]);
				PE_SHP_O20_QRd01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,			pp->shp_djg_vsd[7]);

				/*shp_map_cmn_vsd */
				PE_SHP_O20_QRd02(shp_fd_ctrl_0b,	reg_fd_mnr_gain_e_en,	pp->shp_map_cmn_vsd[0],\
													reg_fd_mnr_gain_t_en,	pp->shp_map_cmn_vsd[1]);
				PE_SHP_O20_QRd04(shp_fd_ctrl_0d,	reg_fd_mnr_gain_x0, 	pp->shp_map_cmn_vsd[2],\
													reg_fd_mnr_gain_x1, 	pp->shp_map_cmn_vsd[3],\
													reg_fd_mnr_gain_y0, 	pp->shp_map_cmn_vsd[4],\
													reg_fd_mnr_gain_y1, 	pp->shp_map_cmn_vsd[5]);
				PE_SHP_O20_QRd02(shp_fd_ctrl_11,	reg_fd_soft_gain_t_en,	pp->shp_map_cmn_vsd[6],\
													reg_fd_soft_gain_e_en,	pp->shp_map_cmn_vsd[7]);
				PE_SHP_O20_QRd04(shp_fd_ctrl_14,	reg_fd_soft_score_y3,	pp->shp_map_cmn_vsd[8],\
													reg_fd_soft_score_y2,	pp->shp_map_cmn_vsd[9],\
													reg_fd_soft_score_y1,	pp->shp_map_cmn_vsd[10],\
													reg_fd_soft_score_y0,	pp->shp_map_cmn_vsd[11]);

				/*shp_balance_vsd*/
				PE_SHP_O20_QRd03(shp_mp_ctrl_05,	reg_mp_gb_en,	pp->shp_balance_vsd[0],\
													reg_mp_gb_mode, pp->shp_balance_vsd[1],\
													reg_mp_gb_y1,	pp->shp_balance_vsd[2]);
				PE_SHP_O20_QRd02(shp_mp_ctrl_06,	reg_mp_gb_y2,	pp->shp_balance_vsd[3],\
													reg_mp_gb_y3,	pp->shp_balance_vsd[4]);
				PE_SHP_O20_QRd03(shp_sp_ctrl_05,	reg_sp_gb_en,	pp->shp_balance_vsd[5],\
													reg_sp_gb_mode, pp->shp_balance_vsd[6],\
													reg_sp_gb_y1,	pp->shp_balance_vsd[7]);
				PE_SHP_O20_QRd02(shp_sp_ctrl_06,	reg_sp_gb_y2,	pp->shp_balance_vsd[8],\
													reg_sp_gb_y3,	pp->shp_balance_vsd[9]);
				PE_SHP_O20_QRd02(shp_lc_ctrl_00,	reg_lc_shp_en,	pp->shp_balance_vsd[10],\
													reg_lc_gb_en,	pp->shp_balance_vsd[11]);
				PE_SHP_O20_QRd02(shp_lc_ctrl_01,	reg_lc_gb_y1,	pp->shp_balance_vsd[12],\
													reg_lc_gb_y2,	pp->shp_balance_vsd[13]);
				PE_SHP_O20_QRd01(shp_lc_ctrl_02,	reg_lc_gb_y3,	pp->shp_balance_vsd[14]);
				PE_SHP_O20_QRd03(shp_lc_ctrl_00,	reg_lc_center_target,	pp->shp_balance_vsd[15],\
													reg_lc_center_gain, pp->shp_balance_vsd[16],\
													reg_lc_local_gain,	pp->shp_balance_vsd[17]);
				PE_SHP_O20_QRd03(shp_mp_ctrl_08,	reg_mp_lum1_y0, pp->shp_balance_vsd[18],\
													reg_mp_lum1_y1, pp->shp_balance_vsd[19],\
													reg_mp_lum1_y2, pp->shp_balance_vsd[20]);
				PE_SHP_O20_QRd01(shp_mp_ctrl_09,	reg_mp_lum2_y0, pp->shp_balance_vsd[21]);
				PE_SHP_O20_QRd02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, pp->shp_balance_vsd[22],\
													reg_mp_lum2_y2, pp->shp_balance_vsd[23]);
				PE_SHP_O20_QRd03(shp_sp_ctrl_08,	reg_sp_lum1_y0, pp->shp_balance_vsd[24],\
													reg_sp_lum1_y1, pp->shp_balance_vsd[25],\
													reg_sp_lum1_y2, pp->shp_balance_vsd[26]);
				PE_SHP_O20_QRd01(shp_sp_ctrl_09,	reg_sp_lum2_y0, pp->shp_balance_vsd[27]);
				PE_SHP_O20_QRd02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, pp->shp_balance_vsd[28],\
													reg_sp_lum2_y2, pp->shp_balance_vsd[29]);
				/*shp_ti_cmn_vsd*/
				PE_SHP_O20_QRd04(shp_pti_ctrl_00, 		reg_ptiv_enable,		pp->shp_ti_cmn_vsd[0],\
														reg_ptiv_ti_mode,		pp->shp_ti_cmn_vsd[1],\
														reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_vsd[2],\
														reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_vsd[3]);
				PE_SHP_O20_QRd04(shp_pti_ctrl_01, 		reg_ptih_enable,		pp->shp_ti_cmn_vsd[4],\
														reg_ptih_ti_mode,		pp->shp_ti_cmn_vsd[5],\
														reg_ptih_mm_tap_size,	pp->shp_ti_cmn_vsd[6],\
														reg_ptih_avg_tap_size,	pp->shp_ti_cmn_vsd[7]);
				PE_SHP_O20_QRd04(shp_sti_ctrl_00, 		reg_sti_enable, 		pp->shp_ti_cmn_vsd[8],\
														reg_sti_ti_mode,		pp->shp_ti_cmn_vsd[9],\
														reg_sti_mm_tap_size,	pp->shp_ti_cmn_vsd[10],\
														reg_sti_avg_tap_size,	pp->shp_ti_cmn_vsd[11]);
				PE_SHP_O20_QRd02(shp_snr_ctrl_00, 		reg_snr_blur_en,		pp->shp_ti_cmn_vsd[12],\
														reg_snr_blur_sel,		pp->shp_ti_cmn_vsd[13]);
				/*shp_chroma_vsd*/
				PE_SHP_O20_QRd03(shp_chroma_ctrl_00,		reg_color_region_en,	pp->shp_chroma_vsd[0],\
															reg_chr_protection_en,	pp->shp_chroma_vsd[1],\
															reg_chr_compensation_en,pp->shp_chroma_vsd[2]);
				PE_SHP_O20_QRd02(shp_chroma_ctrl_0d,		reg_chr_gain_r0_gain,	pp->shp_chroma_vsd[3],\
															reg_chr_gain_r1_gain,	pp->shp_chroma_vsd[4]);
 			}
			
			pd = pp->shp_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_cmn_vsd\n"
			"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24]);
			pd = pp->shp_djg_vsd;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_djg_vsd\n"
			"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
			pd = pp->shp_map_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_map_cmn_vsd\n"
			"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_vsd;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_balance_vsd\n"
			"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ti_cmn_vsd\n"
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_chroma_vsd;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_chroma_vsd\n"
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for O20
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_EE1_T *pp = (LX_PE_SHP_EE1_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ee_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ee_vsd\n"
			"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_RES_WR04(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[0],0,7),\
														reg_mp_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[1],0,7),\
														reg_mp_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[14],0,7),\
														reg_mp_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[15],0,7));
				PE_SHP_HW_O20_RES_WR04(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[2],0,7),\
														reg_sp_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[3],0,7),\
														reg_sp_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[16],0,7),\
														reg_sp_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[17],0,7));
				PE_SHP_HW_O20_RES_WR04(shp_pti_ctrl_03, reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[4],0,7),\
														reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[5],0,7),\
														reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[18],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[19],0,7));
				PE_SHP_HW_O20_RES_WR04(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[6],0,7),\
														reg_lc_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[7],0,7),\
														reg_lc_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[20],0,7),\
														reg_lc_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[21],0,7));
				PE_SHP_HW_O20_RES_WR04(shp_dctp_ctrl_1f,reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[8],0,7),\
														reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[9],0,7),\
														reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[22],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[23],0,7));
				PE_SHP_HW_O20_RES_WR04(shp_tgen_ctrl_0b,reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[10],0,7),\
														reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[11],0,7),\
														reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[24],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[25],0,7));
				PE_SHP_HW_O20_RES_WR04(shp_nntg_ctrl_10,reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[12],0,7),\
														reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[13],0,7),\
														reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[26],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[27],0,7));
				#else
				PE_SHP_O20_QWr04(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[0],0,7),\
														reg_mp_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[1],0,7),\
														reg_mp_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[14],0,7),\
														reg_mp_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[15],0,7));
				PE_SHP_O20_QWr04(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[2],0,7),\
														reg_sp_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[3],0,7),\
														reg_sp_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[16],0,7),\
														reg_sp_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[17],0,7));
				PE_SHP_O20_QWr04(shp_pti_ctrl_03, 		reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[4],0,7),\
														reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[5],0,7),\
														reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[18],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[19],0,7));
				PE_SHP_O20_QWr04(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b, GET_BITS(pp->shp_ee_vsd[6],0,7),\
														reg_lc_coring_gain_e_w, GET_BITS(pp->shp_ee_vsd[7],0,7),\
														reg_lc_coring_gain_t_b, GET_BITS(pp->shp_ee_vsd[20],0,7),\
														reg_lc_coring_gain_t_w, GET_BITS(pp->shp_ee_vsd[21],0,7));
				PE_SHP_O20_QWr04(shp_dctp_ctrl_1f,		reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[8],0,7),\
														reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[9],0,7),\
														reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[22],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[23],0,7));
				PE_SHP_O20_QWr04(shp_tgen_ctrl_0b,		reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[10],0,7),\
														reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[11],0,7),\
														reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[24],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[25],0,7));
				PE_SHP_O20_QWr04(shp_nntg_ctrl_10,		reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_vsd[12],0,7),\
														reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_vsd[13],0,7),\
														reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_ee_vsd[26],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_ee_vsd[27],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for O20
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_EE1_T *pp = (LX_PE_SHP_EE1_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ee_vsd;

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O20_QRd04(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b, 	pp->shp_ee_vsd[0],\
														reg_mp_coring_gain_e_w, 	pp->shp_ee_vsd[1],\
														reg_mp_coring_gain_t_b, 	pp->shp_ee_vsd[14],\
														reg_mp_coring_gain_t_w, 	pp->shp_ee_vsd[15]);
				PE_SHP_O20_QRd04(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b, 	pp->shp_ee_vsd[2],\
														reg_sp_coring_gain_e_w, 	pp->shp_ee_vsd[3],\
														reg_sp_coring_gain_t_b, 	pp->shp_ee_vsd[16],\
														reg_sp_coring_gain_t_w, 	pp->shp_ee_vsd[17]);
				PE_SHP_O20_QRd04(shp_pti_ctrl_03, 		reg_pti_coring_gain_e_b,	pp->shp_ee_vsd[4],\
														reg_pti_coring_gain_e_w,	pp->shp_ee_vsd[5],\
														reg_pti_coring_gain_t_b,	pp->shp_ee_vsd[18],\
														reg_pti_coring_gain_t_w,	pp->shp_ee_vsd[19]);
				PE_SHP_O20_QRd04(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b, 	pp->shp_ee_vsd[6],\
														reg_lc_coring_gain_e_w, 	pp->shp_ee_vsd[7],\
														reg_lc_coring_gain_t_b, 	pp->shp_ee_vsd[20],\
														reg_lc_coring_gain_t_w, 	pp->shp_ee_vsd[21]);
				PE_SHP_O20_QRd04(shp_dctp_ctrl_1f,		reg_dctp_coring_gain_e_b,	pp->shp_ee_vsd[8],\
														reg_dctp_coring_gain_e_w,	pp->shp_ee_vsd[9],\
														reg_dctp_coring_gain_t_b,	pp->shp_ee_vsd[22],\
														reg_dctp_coring_gain_t_w,	pp->shp_ee_vsd[23]);
				PE_SHP_O20_QRd04(shp_tgen_ctrl_0b,		reg_tgen_coring_gain_e_b,	pp->shp_ee_vsd[10],\
														reg_tgen_coring_gain_e_w,	pp->shp_ee_vsd[11],\
														reg_tgen_coring_gain_t_b,	pp->shp_ee_vsd[24],\
														reg_tgen_coring_gain_t_w,	pp->shp_ee_vsd[25]);
				PE_SHP_O20_QRd04(shp_nntg_ctrl_10,		reg_nntg_coring_gain_e_b,	pp->shp_ee_vsd[12],\
														reg_nntg_coring_gain_e_w,	pp->shp_ee_vsd[13],\
														reg_nntg_coring_gain_t_b,	pp->shp_ee_vsd[26],\
														reg_nntg_coring_gain_t_w,	pp->shp_ee_vsd[27]);
			}
			pd = pp->shp_ee_vsd;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ee_vsd\n"
			"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
			
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for O20
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_DE4_T *pp = (LX_PE_SHP_DE4_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_de_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_de_vsd\n"
			"shp_de_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifdef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_RES_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[0],0,7),\
														reg_mp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[1],0,7));
				PE_SHP_HW_O20_RES_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[2],0,7),\
														reg_sp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[3],0,7));
				PE_SHP_HW_O20_RES_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[4],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[5],0,7));
				PE_SHP_HW_O20_RES_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[6],0,7),\
														reg_lc_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[7],0,7));
				PE_SHP_HW_O20_RES_WR02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[8],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[9],0,7));
				PE_SHP_HW_O20_RES_WR02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[10],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[11],0,7));
				PE_SHP_HW_O20_RES_WR02(shp_nntg_ctrl_10,reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[12],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[13],0,7));
				#else
				PE_SHP_O20_QWr02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[0],0,7),\
														reg_mp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[1],0,7));
				PE_SHP_O20_QWr02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[2],0,7),\
														reg_sp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[3],0,7));
				PE_SHP_O20_QWr02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[4],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[5],0,7));
				PE_SHP_O20_QWr02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[6],0,7),\
														reg_lc_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[7],0,7));
				PE_SHP_O20_QWr02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[8],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[9],0,7));
				PE_SHP_O20_QWr02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[10],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[11],0,7));
				PE_SHP_O20_QWr02(shp_nntg_ctrl_10,reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_vsd[12],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_vsd[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for O20
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_DE4_T *pp = (LX_PE_SHP_DE4_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_O20_QRd02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, 	pp->shp_de_vsd[0],\
													reg_mp_coring_gain_t_w, 	pp->shp_de_vsd[1]);
				PE_SHP_O20_QRd02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, 	pp->shp_de_vsd[2],\
													reg_sp_coring_gain_t_w, 	pp->shp_de_vsd[3]);
				PE_SHP_O20_QRd02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	pp->shp_de_vsd[4],\
													reg_pti_coring_gain_t_w,	pp->shp_de_vsd[5]);
				PE_SHP_O20_QRd02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, 	pp->shp_de_vsd[6],\
													reg_lc_coring_gain_t_w, 	pp->shp_de_vsd[7]);
				PE_SHP_O20_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	pp->shp_de_vsd[8],\
													reg_dctp_coring_gain_t_w,	pp->shp_de_vsd[9]);
				PE_SHP_O20_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	pp->shp_de_vsd[10],\
													reg_tgen_coring_gain_t_w,	pp->shp_de_vsd[11]);
				PE_SHP_O20_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	pp->shp_de_vsd[12],\
													reg_nntg_coring_gain_t_w,	pp->shp_de_vsd[13]);
			}
			pd = pp->shp_de_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_de_vsd\n"
			"shp_de_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * set sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSreReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_CMN_T *pp=(LX_PE_SHP_SR_RE4_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_main_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_main_4k\n"
			"shp_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_4k    [10]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10]);
			pd = pp->shp_ti_ui_main_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ti_ui_main_4k\n"
			"shp_ti_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				/*shp_ui_main_4k*/
				PE_SHP_HW_O20_SR_SHP_WR01(shp_esf_ctrl_01,	reg_esf_master_gain,	GET_BITS(pp->shp_ui_main_4k[0],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_4k[1],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_4k[2],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_lc_ctrl_02,	reg_lc_lap_weight,		GET_BITS(pp->shp_ui_main_4k[3],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_mp_ctrl_02,	reg_mp_lap_weight,		GET_BITS(pp->shp_ui_main_4k[4],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_sp_ctrl_02,	reg_sp_lap_weight,		GET_BITS(pp->shp_ui_main_4k[5],0,8));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_der_ctrl_06,	reg_der_a_lut_y0,		GET_BITS(pp->shp_ui_main_4k[6],0,8),\
															reg_der_a_lut_y1,		GET_BITS(pp->shp_ui_main_4k[7],0,8));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_der_ctrl_07,	reg_der_a_lut_y2,		GET_BITS(pp->shp_ui_main_4k[8],0,8),\
															reg_der_a_lut_y3,		GET_BITS(pp->shp_ui_main_4k[9],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_4k[10],0,8));
				/*shp_ti_ui_main_4k*/
				PE_SHP_HW_O20_SR_SHP_WR03(shp_sti_ctrl_00,	reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_4k[0],0,8),\
															reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_4k[1],0,8),\
															reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_4k[2],0,8));
				#else
				PE_SR_4K_SHP_O20_QWr01(shp_esf_ctrl_01,		reg_esf_master_gain,	GET_BITS(pp->shp_ui_main_4k[0],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_dctp_ctrl_1d,	reg_dctp_gain,			GET_BITS(pp->shp_ui_main_4k[1],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_4k[2],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_lc_ctrl_02,		reg_lc_lap_weight,		GET_BITS(pp->shp_ui_main_4k[3],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_mp_ctrl_02,		reg_mp_lap_weight,		GET_BITS(pp->shp_ui_main_4k[4],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_sp_ctrl_02,		reg_sp_lap_weight,		GET_BITS(pp->shp_ui_main_4k[5],0,8));
				PE_SR_4K_SHP_O20_QWr02(shp_der_ctrl_06,		reg_der_a_lut_y0,		GET_BITS(pp->shp_ui_main_4k[6],0,8),\
															reg_der_a_lut_y1,		GET_BITS(pp->shp_ui_main_4k[7],0,8));
				PE_SR_4K_SHP_O20_QWr02(shp_der_ctrl_07,		reg_der_a_lut_y2,		GET_BITS(pp->shp_ui_main_4k[8],0,8),\
															reg_der_a_lut_y3,		GET_BITS(pp->shp_ui_main_4k[9],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_4k[10],0,8));
				/*shp_ti_ui_main_4k*/
				PE_SR_4K_SHP_O20_QWr03(shp_sti_ctrl_00,		reg_sti_master_gain,	GET_BITS(pp->shp_ti_ui_main_4k[0],0,8),\
															reg_sti_edge_gain,		GET_BITS(pp->shp_ti_ui_main_4k[1],0,8),\
															reg_sti_texture_gain,	GET_BITS(pp->shp_ti_ui_main_4k[2],0,8));
				
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSreReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_CMN_T *pp=(LX_PE_SHP_SR_RE4_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_4K_SHP_O20_QRd01(shp_esf_ctrl_01,	reg_esf_master_gain,	pp->shp_ui_main_4k[0]);
				PE_SR_4K_SHP_O20_QRd01(shp_dctp_ctrl_1d,	reg_dctp_gain,	pp->shp_ui_main_4k[1]);
				PE_SR_4K_SHP_O20_QRd01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	pp->shp_ui_main_4k[2]);
				PE_SR_4K_SHP_O20_QRd01(shp_lc_ctrl_02,	reg_lc_lap_weight,	pp->shp_ui_main_4k[3]);
				PE_SR_4K_SHP_O20_QRd01(shp_mp_ctrl_02,	reg_mp_lap_weight,	pp->shp_ui_main_4k[4]);
				PE_SR_4K_SHP_O20_QRd01(shp_sp_ctrl_02,	reg_sp_lap_weight,	pp->shp_ui_main_4k[5]);
				PE_SR_4K_SHP_O20_QRd02(shp_der_ctrl_06,	reg_der_a_lut_y0,	pp->shp_ui_main_4k[6],\
																reg_der_a_lut_y1,	pp->shp_ui_main_4k[7]);
				PE_SR_4K_SHP_O20_QRd02(shp_der_ctrl_07,	reg_der_a_lut_y2,	pp->shp_ui_main_4k[8],\
																reg_der_a_lut_y3,	pp->shp_ui_main_4k[9]);
				PE_SR_4K_SHP_O20_QRd01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	pp->shp_ui_main_4k[10]);
				PE_SR_4K_SHP_O20_QRd03(shp_sti_ctrl_00,	reg_sti_master_gain,	pp->shp_ti_ui_main_4k[0],\
												reg_sti_edge_gain,	pp->shp_ti_ui_main_4k[1],\
												reg_sti_texture_gain,	pp->shp_ti_ui_main_4k[2]);
				pd = pp->shp_ui_main_4k;
				PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_main_4k\n"
				"shp_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_4k    [10]0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10]);
				pd = pp->shp_ti_ui_main_4k;
				PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ti_ui_main_4k\n"
				"shp_ti_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2]);
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSreReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_HOR_T *pp=(LX_PE_SHP_SR_RE4_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_h_main_4k\n"
			"shp_ui_h_main_4k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_SHP_WR01(shp_der_ctrl_00,	reg_derh_csft_gain, 		GET_BITS(pp->shp_ui_h_main_4k[0],0,6));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_4k[1],0,6),\
															reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_4k[2],0,6));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_4k[3],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_4k[4],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_pti_ctrl_01,	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_4k[5],0,8));
				#else
				PE_SR_4K_SHP_O20_QWr01(shp_der_ctrl_00,	reg_derh_csft_gain, 			GET_BITS(pp->shp_ui_h_main_4k[0],0,6));
				PE_SR_4K_SHP_O20_QWr02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main_4k[1],0,6),\
														reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main_4k[2],0,6));
				PE_SR_4K_SHP_O20_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_4k[3],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_sp_ctrl_01,	reg_sp_im_gain_h,				GET_BITS(pp->shp_ui_h_main_4k[4],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_pti_ctrl_01,	reg_ptih_master_gain,			GET_BITS(pp->shp_ui_h_main_4k[5],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSreReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_HOR_T *pp=(LX_PE_SHP_SR_RE4_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			PE_SR_4K_SHP_O20_QRd01(shp_der_ctrl_00, reg_derh_csft_gain, 			pp->shp_ui_h_main_4k[0]);
			PE_SR_4K_SHP_O20_QRd02(shp_der_ctrl_02, reg_derh_edge_filter_gain_w,	pp->shp_ui_h_main_4k[1],\
													reg_derh_edge_filter_gain_b,	pp->shp_ui_h_main_4k[2]);
			PE_SR_4K_SHP_O20_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,				pp->shp_ui_h_main_4k[3]);
			PE_SR_4K_SHP_O20_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,				pp->shp_ui_h_main_4k[4]);
			PE_SR_4K_SHP_O20_QRd01(shp_pti_ctrl_01, reg_ptih_master_gain,			pp->shp_ui_h_main_4k[5]);

			pd = pp->shp_ui_h_main_4k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_h_main_4k\n"
			"shp_ui_h_main_4k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSreReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	UINT8 *pd;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_SR_RE4_VER_T *pp=(LX_PE_SHP_SR_RE4_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_v_main_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_v_main_4k\n"
			"shp_ui_v_main_4k    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_4k[0],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_4k[1],0,8));
				#else
				PE_SR_4K_SHP_O20_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_4k[0],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_4k[1],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSreReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	UINT8 *pd;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_SR_RE4_VER_T *pp=(LX_PE_SHP_SR_RE4_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_4K_SHP_O20_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		pp->shp_ui_v_main_4k[0]);
				PE_SR_4K_SHP_O20_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	pp->shp_ui_v_main_4k[1]);
			}
			pd = pp->shp_ui_v_main_4k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_v_main_4k\n"
			"shp_ui_v_main_4k	 [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSreReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{ 
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_MISC_T *pp=(LX_PE_SHP_SR_RE4_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_cmn_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_cmn_4k\n"
			"shp_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [20]0x%02X,",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);
			pd = pp->shp_map_cmn_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_map_cmn_4k\n"
			"shp_map_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_balance_4k\n"
			"shp_balance_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ti_cmn_4k\n"
			"shp_ti_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_4k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_simple_snr_4k\n"
			"shp_simple_snr_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_SHP_WR02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_4k[0],0,1),\
															reg_derh_bflt_tap_size,		GET_BITS(pp->shp_cmn_4k[1],0,3));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,				GET_BITS(pp->shp_cmn_4k[2],0,1));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,				GET_BITS(pp->shp_cmn_4k[3],0,1));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_mp_ctrl_01,	reg_mp_im_os_gain,			GET_BITS(pp->shp_cmn_4k[4],0,7),\
															reg_mp_im_us_gain,			GET_BITS(pp->shp_cmn_4k[5],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_sp_ctrl_01,	reg_sp_im_os_gain,			GET_BITS(pp->shp_cmn_4k[6],0,7),\
															reg_sp_im_us_gain,			GET_BITS(pp->shp_cmn_4k[7],0,7));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_esf_ctrl_00,	reg_esf_en,					GET_BITS(pp->shp_cmn_4k[8],0,1));
				PE_SHP_HW_O20_SR_SHP_WR03(shp_esf_ctrl_01,	reg_esf_min_ratio,			GET_BITS(pp->shp_cmn_4k[9],0,8),\
															reg_esf_base,				GET_BITS(pp->shp_cmn_4k[10],0,8),\
															reg_esf_max_clip,			GET_BITS(pp->shp_cmn_4k[11],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_dctp_ctrl_00,	reg_dctp_en,				GET_BITS(pp->shp_cmn_4k[12],0,1));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,			GET_BITS(pp->shp_cmn_4k[13],0,1),\
															reg_dctp_coring_mode,		GET_BITS(pp->shp_cmn_4k[14],0,2));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_on_off,			GET_BITS(pp->shp_cmn_4k[15],0,1));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,			GET_BITS(pp->shp_cmn_4k[16],0,1),\
															reg_tgen_coring_mode,		GET_BITS(pp->shp_cmn_4k[17],0,2));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_nntg_ctrl_00,	reg_nntg_en,				GET_BITS(pp->shp_cmn_4k[18],0,1));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,			GET_BITS(pp->shp_cmn_4k[19],0,1),\
															reg_nntg_coring_mode,		GET_BITS(pp->shp_cmn_4k[20],0,2));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_fd_ctrl_09,	reg_fd_mnr_gain_e_en,		GET_BITS(pp->shp_map_cmn_4k[0],0,1),\
															reg_fd_mnr_gain_t_en,		GET_BITS(pp->shp_map_cmn_4k[1],0,1));
				PE_SHP_HW_O20_SR_SHP_WR04(shp_fd_ctrl_0b,	reg_fd_mnr_gain_x0,			GET_BITS(pp->shp_map_cmn_4k[2],0,8),\
															reg_fd_mnr_gain_x1,			GET_BITS(pp->shp_map_cmn_4k[3],0,8),\
															reg_fd_mnr_gain_y0,			GET_BITS(pp->shp_map_cmn_4k[4],0,8),\
															reg_fd_mnr_gain_y1,			GET_BITS(pp->shp_map_cmn_4k[5],0,8));
				PE_SHP_HW_O20_SR_SHP_WR04(shp_fd_ctrl_07,	reg_fd_edge_minmax_x0,	GET_BITS(pp->shp_map_cmn_4k[6],0,8),\
															reg_fd_edge_minmax_y0,	GET_BITS(pp->shp_map_cmn_4k[7],0,8),\
															reg_fd_edge_minmax_x1,	GET_BITS(pp->shp_map_cmn_4k[8],0,8),\
															reg_fd_edge_minmax_y1,	GET_BITS(pp->shp_map_cmn_4k[9],0,8));
				PE_SHP_HW_O20_SR_SHP_WR04(shp_fd_ctrl_08,	reg_fd_detail_minmax_x0,	GET_BITS(pp->shp_map_cmn_4k[10],0,8),\
															reg_fd_detail_minmax_y0,	GET_BITS(pp->shp_map_cmn_4k[11],0,8),\
															reg_fd_detail_minmax_x1,	GET_BITS(pp->shp_map_cmn_4k[12],0,8),\
															reg_fd_detail_minmax_y1,	GET_BITS(pp->shp_map_cmn_4k[13],0,8));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_fd_ctrl_0f,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_4k[14],0,1),\
															reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_4k[15],0,1));
				PE_SHP_HW_O20_SR_SHP_WR04(shp_fd_ctrl_12,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_4k[16],0,6),\
															reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_4k[17],0,6),\
															reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_4k[18],0,6),\
															reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_4k[19],0,6));
				PE_SHP_HW_O20_SR_SHP_WR03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_4k[0],0,1),\
															reg_mp_gb_mode,	GET_BITS(pp->shp_balance_4k[1],0,1),\
															reg_mp_gb_y1,	GET_BITS(pp->shp_balance_4k[2],0,8));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_4k[3],0,8),\
															reg_mp_gb_y3,	GET_BITS(pp->shp_balance_4k[4],0,8));
				PE_SHP_HW_O20_SR_SHP_WR03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_4k[5],0,1),\
															reg_sp_gb_mode,	GET_BITS(pp->shp_balance_4k[6],0,1),\
															reg_sp_gb_y1,	GET_BITS(pp->shp_balance_4k[7],0,8));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_4k[8],0,8),\
															reg_sp_gb_y3,	GET_BITS(pp->shp_balance_4k[9],0,8));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_4k[10],0,1),\
															reg_lc_gb_en,	GET_BITS(pp->shp_balance_4k[11],0,1));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_4k[12],0,8),\
															reg_lc_gb_y2,	GET_BITS(pp->shp_balance_4k[13],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_4k[14],0,8));
				PE_SHP_HW_O20_SR_SHP_WR03(shp_lc_ctrl_00,	reg_lc_center_target,	GET_BITS(pp->shp_balance_4k[15],0,8),\
															reg_lc_center_gain,	GET_BITS(pp->shp_balance_4k[16],0,8),\
															reg_lc_local_gain,	GET_BITS(pp->shp_balance_4k[17],0,8));
				PE_SHP_HW_O20_SR_SHP_WR03(shp_mp_ctrl_08,	reg_mp_lum1_y0,	GET_BITS(pp->shp_balance_4k[18],0,8),\
															reg_mp_lum1_y1,	GET_BITS(pp->shp_balance_4k[19],0,8),\
															reg_mp_lum1_y2,	GET_BITS(pp->shp_balance_4k[20],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_mp_ctrl_09,	reg_mp_lum2_y0,	GET_BITS(pp->shp_balance_4k[21],0,8));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_mp_ctrl_0a,	reg_mp_lum2_y1,	GET_BITS(pp->shp_balance_4k[22],0,8),\
															reg_mp_lum2_y2,	GET_BITS(pp->shp_balance_4k[23],0,8));
				PE_SHP_HW_O20_SR_SHP_WR03(shp_sp_ctrl_08,	reg_sp_lum1_y0,	GET_BITS(pp->shp_balance_4k[24],0,8),\
															reg_sp_lum1_y1,	GET_BITS(pp->shp_balance_4k[25],0,8),\
															reg_sp_lum1_y2,	GET_BITS(pp->shp_balance_4k[26],0,8));
				PE_SHP_HW_O20_SR_SHP_WR01(shp_sp_ctrl_09,	reg_sp_lum2_y0,	GET_BITS(pp->shp_balance_4k[27],0,8));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_sp_ctrl_0a,	reg_sp_lum2_y1,	GET_BITS(pp->shp_balance_4k[28],0,8),\
															reg_sp_lum2_y2,	GET_BITS(pp->shp_balance_4k[29],0,8));
				PE_SHP_HW_O20_SR_SHP_WR04(shp_pti_ctrl_00,	reg_ptiv_enable,	GET_BITS(pp->shp_ti_cmn_4k[0],0,1),\
															reg_ptiv_ti_mode,	GET_BITS(pp->shp_ti_cmn_4k[1],0,1),\
															reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[2],0,2),\
															reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[3],0,2));
				PE_SHP_HW_O20_SR_SHP_WR04(shp_pti_ctrl_01,	reg_ptih_enable,	GET_BITS(pp->shp_ti_cmn_4k[4],0,1),\
															reg_ptih_ti_mode,	GET_BITS(pp->shp_ti_cmn_4k[5],0,1),\
															reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[6],0,2),\
															reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[7],0,2));
				PE_SHP_HW_O20_SR_SHP_WR04(shp_sti_ctrl_00,	reg_sti_enable,	GET_BITS(pp->shp_ti_cmn_4k[8],0,1),\
															reg_sti_ti_mode,	GET_BITS(pp->shp_ti_cmn_4k[9],0,1),\
															reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[10],0,2),\
															reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[11],0,2));
				PE_SHP_HW_O20_SR_SHP_WR03(shp_snr_ctrl_00,	reg_snr_blur_en,	GET_BITS(pp->shp_simple_snr_4k[0],0,1),\
															reg_snr_blur_sel,	GET_BITS(pp->shp_simple_snr_4k[1],0,2),\
															reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_4k[2],0,8));
				#else
				PE_SR_4K_SHP_O20_QWr02(shp_der_ctrl_01,		reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_4k[0],0,1),\
															reg_derh_bflt_tap_size,		GET_BITS(pp->shp_cmn_4k[1],0,3));
				PE_SR_4K_SHP_O20_QWr01(shp_mp_ctrl_00,		reg_mp_shp_en,				GET_BITS(pp->shp_cmn_4k[2],0,1));
				PE_SR_4K_SHP_O20_QWr01(shp_sp_ctrl_00,		reg_sp_shp_en,				GET_BITS(pp->shp_cmn_4k[3],0,1));
				PE_SR_4K_SHP_O20_QWr02(shp_mp_ctrl_01,		reg_mp_im_os_gain,			GET_BITS(pp->shp_cmn_4k[4],0,7),\
															reg_mp_im_us_gain,			GET_BITS(pp->shp_cmn_4k[5],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_sp_ctrl_01,		reg_sp_im_os_gain,			GET_BITS(pp->shp_cmn_4k[6],0,7),\
															reg_sp_im_us_gain,			GET_BITS(pp->shp_cmn_4k[7],0,7));
				PE_SR_4K_SHP_O20_QWr01(shp_esf_ctrl_00,		reg_esf_en,					GET_BITS(pp->shp_cmn_4k[8],0,1));
				PE_SR_4K_SHP_O20_QWr03(shp_esf_ctrl_01,		reg_esf_min_ratio,			GET_BITS(pp->shp_cmn_4k[9],0,8),\
															reg_esf_base,				GET_BITS(pp->shp_cmn_4k[10],0,8),\
															reg_esf_max_clip,			GET_BITS(pp->shp_cmn_4k[11],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_dctp_ctrl_00,	reg_dctp_en,				GET_BITS(pp->shp_cmn_4k[12],0,1));
				PE_SR_4K_SHP_O20_QWr02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,			GET_BITS(pp->shp_cmn_4k[13],0,1),\
															reg_dctp_coring_mode,		GET_BITS(pp->shp_cmn_4k[14],0,2));
				PE_SR_4K_SHP_O20_QWr01(shp_tgen_ctrl_00,	reg_tgen_on_off,			GET_BITS(pp->shp_cmn_4k[15],0,1));
				PE_SR_4K_SHP_O20_QWr02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,			GET_BITS(pp->shp_cmn_4k[16],0,1),\
															reg_tgen_coring_mode,		GET_BITS(pp->shp_cmn_4k[17],0,2));
				PE_SR_4K_SHP_O20_QWr01(shp_nntg_ctrl_00,	reg_nntg_en,				GET_BITS(pp->shp_cmn_4k[18],0,1));
				PE_SR_4K_SHP_O20_QWr02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,			GET_BITS(pp->shp_cmn_4k[19],0,1),\
															reg_nntg_coring_mode,		GET_BITS(pp->shp_cmn_4k[20],0,2));
				PE_SR_4K_SHP_O20_QWr02(shp_fd_ctrl_09,		reg_fd_mnr_gain_e_en,		GET_BITS(pp->shp_map_cmn_4k[0],0,1),\
															reg_fd_mnr_gain_t_en,		GET_BITS(pp->shp_map_cmn_4k[1],0,1));
				PE_SR_4K_SHP_O20_QWr04(shp_fd_ctrl_0b,		reg_fd_mnr_gain_x0,			GET_BITS(pp->shp_map_cmn_4k[2],0,8),\
															reg_fd_mnr_gain_x1,			GET_BITS(pp->shp_map_cmn_4k[3],0,8),\
															reg_fd_mnr_gain_y0,			GET_BITS(pp->shp_map_cmn_4k[4],0,8),\
															reg_fd_mnr_gain_y1,			GET_BITS(pp->shp_map_cmn_4k[5],0,8));
				PE_SR_4K_SHP_O20_QWr04(shp_fd_ctrl_07,		reg_fd_edge_minmax_x0,		GET_BITS(pp->shp_map_cmn_4k[6],0,8),\
															reg_fd_edge_minmax_y0,		GET_BITS(pp->shp_map_cmn_4k[7],0,8),\
															reg_fd_edge_minmax_x1,		GET_BITS(pp->shp_map_cmn_4k[8],0,8),\
															reg_fd_edge_minmax_y1,		GET_BITS(pp->shp_map_cmn_4k[9],0,8));
				PE_SR_4K_SHP_O20_QWr04(shp_fd_ctrl_08,		reg_fd_detail_minmax_x0,	GET_BITS(pp->shp_map_cmn_4k[10],0,8),\
															reg_fd_detail_minmax_y0,	GET_BITS(pp->shp_map_cmn_4k[11],0,8),\
															reg_fd_detail_minmax_x1,	GET_BITS(pp->shp_map_cmn_4k[12],0,8),\
															reg_fd_detail_minmax_y1,	GET_BITS(pp->shp_map_cmn_4k[13],0,8));
				PE_SR_4K_SHP_O20_QWr02(shp_fd_ctrl_0f,		reg_fd_soft_gain_t_en,		GET_BITS(pp->shp_map_cmn_4k[14],0,1),\
															reg_fd_soft_gain_e_en,		GET_BITS(pp->shp_map_cmn_4k[15],0,1));
				PE_SR_4K_SHP_O20_QWr04(shp_fd_ctrl_12,		reg_fd_soft_score_y3,		GET_BITS(pp->shp_map_cmn_4k[16],0,6),\
															reg_fd_soft_score_y2,		GET_BITS(pp->shp_map_cmn_4k[17],0,6),\
															reg_fd_soft_score_y1,		GET_BITS(pp->shp_map_cmn_4k[18],0,6),\
															reg_fd_soft_score_y0,		GET_BITS(pp->shp_map_cmn_4k[19],0,6));
				PE_SR_4K_SHP_O20_QWr03(shp_mp_ctrl_05,		reg_mp_gb_en,	GET_BITS(pp->shp_balance_4k[0],0,1),\
															reg_mp_gb_mode,	GET_BITS(pp->shp_balance_4k[1],0,1),\
															reg_mp_gb_y1,	GET_BITS(pp->shp_balance_4k[2],0,8));
				PE_SR_4K_SHP_O20_QWr02(shp_mp_ctrl_06,		reg_mp_gb_y2,	GET_BITS(pp->shp_balance_4k[3],0,8),\
															reg_mp_gb_y3,	GET_BITS(pp->shp_balance_4k[4],0,8));
				PE_SR_4K_SHP_O20_QWr03(shp_sp_ctrl_05,		reg_sp_gb_en,	GET_BITS(pp->shp_balance_4k[5],0,1),\
															reg_sp_gb_mode,	GET_BITS(pp->shp_balance_4k[6],0,1),\
															reg_sp_gb_y1,	GET_BITS(pp->shp_balance_4k[7],0,8));
				PE_SR_4K_SHP_O20_QWr02(shp_sp_ctrl_06,		reg_sp_gb_y2,	GET_BITS(pp->shp_balance_4k[8],0,8),\
															reg_sp_gb_y3,	GET_BITS(pp->shp_balance_4k[9],0,8));
				PE_SR_4K_SHP_O20_QWr02(shp_lc_ctrl_00,		reg_lc_shp_en,	GET_BITS(pp->shp_balance_4k[10],0,1),\
															reg_lc_gb_en,	GET_BITS(pp->shp_balance_4k[11],0,1));
				PE_SR_4K_SHP_O20_QWr02(shp_lc_ctrl_01,		reg_lc_gb_y1,	GET_BITS(pp->shp_balance_4k[12],0,8),\
															reg_lc_gb_y2,	GET_BITS(pp->shp_balance_4k[13],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_lc_ctrl_02,		reg_lc_gb_y3,	GET_BITS(pp->shp_balance_4k[14],0,8));
				PE_SR_4K_SHP_O20_QWr03(shp_lc_ctrl_00,		reg_lc_center_target,	GET_BITS(pp->shp_balance_4k[15],0,8),\
															reg_lc_center_gain,		GET_BITS(pp->shp_balance_4k[16],0,8),\
															reg_lc_local_gain,		GET_BITS(pp->shp_balance_4k[17],0,8));
				PE_SR_4K_SHP_O20_QWr03(shp_mp_ctrl_08,		reg_mp_lum1_y0,	GET_BITS(pp->shp_balance_4k[18],0,8),\
															reg_mp_lum1_y1,	GET_BITS(pp->shp_balance_4k[19],0,8),\
															reg_mp_lum1_y2,	GET_BITS(pp->shp_balance_4k[20],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_mp_ctrl_09,		reg_mp_lum2_y0,	GET_BITS(pp->shp_balance_4k[21],0,8));
				PE_SR_4K_SHP_O20_QWr02(shp_mp_ctrl_0a,		reg_mp_lum2_y1,	GET_BITS(pp->shp_balance_4k[22],0,8),\
															reg_mp_lum2_y2,	GET_BITS(pp->shp_balance_4k[23],0,8));
				PE_SR_4K_SHP_O20_QWr03(shp_sp_ctrl_08,		reg_sp_lum1_y0,	GET_BITS(pp->shp_balance_4k[24],0,8),\
															reg_sp_lum1_y1,	GET_BITS(pp->shp_balance_4k[25],0,8),\
															reg_sp_lum1_y2,	GET_BITS(pp->shp_balance_4k[26],0,8));
				PE_SR_4K_SHP_O20_QWr01(shp_sp_ctrl_09,		reg_sp_lum2_y0,	GET_BITS(pp->shp_balance_4k[27],0,8));
				PE_SR_4K_SHP_O20_QWr02(shp_sp_ctrl_0a,		reg_sp_lum2_y1,	GET_BITS(pp->shp_balance_4k[28],0,8),\
															reg_sp_lum2_y2,	GET_BITS(pp->shp_balance_4k[29],0,8));
				PE_SR_4K_SHP_O20_QWr04(shp_pti_ctrl_00,		reg_ptiv_enable,		GET_BITS(pp->shp_ti_cmn_4k[0],0,1),\
															reg_ptiv_ti_mode,		GET_BITS(pp->shp_ti_cmn_4k[1],0,1),\
															reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[2],0,2),\
															reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[3],0,2));
				PE_SR_4K_SHP_O20_QWr04(shp_pti_ctrl_01,		reg_ptih_enable,		GET_BITS(pp->shp_ti_cmn_4k[4],0,1),\
															reg_ptih_ti_mode,		GET_BITS(pp->shp_ti_cmn_4k[5],0,1),\
															reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[6],0,2),\
															reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[7],0,2));
				PE_SR_4K_SHP_O20_QWr04(shp_sti_ctrl_00,		reg_sti_enable,			GET_BITS(pp->shp_ti_cmn_4k[8],0,1),\
															reg_sti_ti_mode,		GET_BITS(pp->shp_ti_cmn_4k[9],0,1),\
															reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[10],0,2),\
															reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_4k[11],0,2));
				PE_SR_4K_SHP_O20_QWr03(shp_snr_ctrl_00,		reg_snr_blur_en,		GET_BITS(pp->shp_simple_snr_4k[0],0,1),\
															reg_snr_blur_sel,		GET_BITS(pp->shp_simple_snr_4k[1],0,2),\
															reg_snr_bilateral_th,	GET_BITS(pp->shp_simple_snr_4k[2],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSreReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_RE4_MISC_T *pp=(LX_PE_SHP_SR_RE4_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_4K_SHP_O20_QRd02(shp_der_ctrl_01,		reg_derh_edge_y_filter_en,	pp->shp_cmn_4k[0],\
															reg_derh_bflt_tap_size,		pp->shp_cmn_4k[1]);
				PE_SR_4K_SHP_O20_QRd01(shp_mp_ctrl_00,		reg_mp_shp_en,				pp->shp_cmn_4k[2]);
				PE_SR_4K_SHP_O20_QRd01(shp_sp_ctrl_00,		reg_sp_shp_en,				pp->shp_cmn_4k[3]);
				PE_SR_4K_SHP_O20_QRd02(shp_mp_ctrl_01,		reg_mp_im_os_gain,			pp->shp_cmn_4k[4],\
															reg_mp_im_us_gain,			pp->shp_cmn_4k[5]);
				PE_SR_4K_SHP_O20_QRd02(shp_sp_ctrl_01,		reg_sp_im_os_gain,			pp->shp_cmn_4k[6],\
															reg_sp_im_us_gain,			pp->shp_cmn_4k[7]);
				PE_SR_4K_SHP_O20_QRd01(shp_esf_ctrl_00,		reg_esf_en,					pp->shp_cmn_4k[8]);
				PE_SR_4K_SHP_O20_QRd03(shp_esf_ctrl_01,		reg_esf_min_ratio,			pp->shp_cmn_4k[9],\
															reg_esf_base,				pp->shp_cmn_4k[10],\
															reg_esf_max_clip,			pp->shp_cmn_4k[11]);
				PE_SR_4K_SHP_O20_QRd01(shp_dctp_ctrl_00,	reg_dctp_en,				pp->shp_cmn_4k[12]);
				PE_SR_4K_SHP_O20_QRd02(shp_dctp_ctrl_1e,	reg_dctp_coring_en,			pp->shp_cmn_4k[13],\
															reg_dctp_coring_mode,		pp->shp_cmn_4k[14]);
				PE_SR_4K_SHP_O20_QRd01(shp_tgen_ctrl_00,	reg_tgen_on_off,			pp->shp_cmn_4k[15]);
				PE_SR_4K_SHP_O20_QRd02(shp_tgen_ctrl_0a,	reg_tgen_coring_en,			pp->shp_cmn_4k[16],\
															reg_tgen_coring_mode,		pp->shp_cmn_4k[17]);
				PE_SR_4K_SHP_O20_QRd01(shp_nntg_ctrl_00,	reg_nntg_en,				pp->shp_cmn_4k[18]);
				PE_SR_4K_SHP_O20_QRd02(shp_nntg_ctrl_0f,	reg_nntg_coring_en,			pp->shp_cmn_4k[19],\
															reg_nntg_coring_mode,		pp->shp_cmn_4k[20]);
				PE_SR_4K_SHP_O20_QRd02(shp_fd_ctrl_09,		reg_fd_mnr_gain_e_en,		pp->shp_map_cmn_4k[0],\
															reg_fd_mnr_gain_t_en,		pp->shp_map_cmn_4k[1]);
				PE_SR_4K_SHP_O20_QRd04(shp_fd_ctrl_0b,		reg_fd_mnr_gain_x0,			pp->shp_map_cmn_4k[2],\
															reg_fd_mnr_gain_x1,			pp->shp_map_cmn_4k[3],\
															reg_fd_mnr_gain_y0,			pp->shp_map_cmn_4k[4],\
															reg_fd_mnr_gain_y1,			pp->shp_map_cmn_4k[5]);
				PE_SR_4K_SHP_O20_QRd04(shp_fd_ctrl_07,		reg_fd_edge_minmax_x0,		pp->shp_map_cmn_4k[6],\
															reg_fd_edge_minmax_y0,		pp->shp_map_cmn_4k[7],\
															reg_fd_edge_minmax_x1,		pp->shp_map_cmn_4k[8],\
															reg_fd_edge_minmax_y1,		pp->shp_map_cmn_4k[9]);
				PE_SR_4K_SHP_O20_QRd04(shp_fd_ctrl_08,		reg_fd_detail_minmax_x0,	pp->shp_map_cmn_4k[10],\
															reg_fd_detail_minmax_y0,	pp->shp_map_cmn_4k[11],\
															reg_fd_detail_minmax_x1,	pp->shp_map_cmn_4k[12],\
															reg_fd_detail_minmax_y1,	pp->shp_map_cmn_4k[13]);
				PE_SR_4K_SHP_O20_QRd02(shp_fd_ctrl_0f,		reg_fd_soft_gain_t_en,		pp->shp_map_cmn_4k[14],\
															reg_fd_soft_gain_e_en,		pp->shp_map_cmn_4k[15]);
				PE_SR_4K_SHP_O20_QRd04(shp_fd_ctrl_12,		reg_fd_soft_score_y3,		pp->shp_map_cmn_4k[16],\
															reg_fd_soft_score_y2,		pp->shp_map_cmn_4k[17],\
															reg_fd_soft_score_y1,		pp->shp_map_cmn_4k[18],\
															reg_fd_soft_score_y0,		pp->shp_map_cmn_4k[19]);
				PE_SR_4K_SHP_O20_QRd03(shp_mp_ctrl_05,		reg_mp_gb_en,	pp->shp_balance_4k[0],\
															reg_mp_gb_mode,	pp->shp_balance_4k[1],\
															reg_mp_gb_y1,	pp->shp_balance_4k[2]);
				PE_SR_4K_SHP_O20_QRd02(shp_mp_ctrl_06,		reg_mp_gb_y2,	pp->shp_balance_4k[3],\
															reg_mp_gb_y3,	pp->shp_balance_4k[4]);
				PE_SR_4K_SHP_O20_QRd03(shp_sp_ctrl_05,		reg_sp_gb_en,	pp->shp_balance_4k[5],\
															reg_sp_gb_mode,	pp->shp_balance_4k[6],\
															reg_sp_gb_y1,	pp->shp_balance_4k[7]);
				PE_SR_4K_SHP_O20_QRd02(shp_sp_ctrl_06,		reg_sp_gb_y2,	pp->shp_balance_4k[8],\
															reg_sp_gb_y3,	pp->shp_balance_4k[9]);
				PE_SR_4K_SHP_O20_QRd02(shp_lc_ctrl_00,		reg_lc_shp_en,	pp->shp_balance_4k[10],\
															reg_lc_gb_en,	pp->shp_balance_4k[11]);
				PE_SR_4K_SHP_O20_QRd02(shp_lc_ctrl_01,		reg_lc_gb_y1,	pp->shp_balance_4k[12],\
															reg_lc_gb_y2,	pp->shp_balance_4k[13]);
				PE_SR_4K_SHP_O20_QRd01(shp_lc_ctrl_02,		reg_lc_gb_y3,	pp->shp_balance_4k[14]);
				PE_SR_4K_SHP_O20_QRd03(shp_lc_ctrl_00,		reg_lc_center_target,	pp->shp_balance_4k[15],\
															reg_lc_center_gain,		pp->shp_balance_4k[16],\
															reg_lc_local_gain,		pp->shp_balance_4k[17]);
				PE_SR_4K_SHP_O20_QRd03(shp_mp_ctrl_08,		reg_mp_lum1_y0,	pp->shp_balance_4k[18],\
															reg_mp_lum1_y1,	pp->shp_balance_4k[19],\
															reg_mp_lum1_y2,	pp->shp_balance_4k[20]);
				PE_SR_4K_SHP_O20_QRd01(shp_mp_ctrl_09,		reg_mp_lum2_y0,	pp->shp_balance_4k[21]);
				PE_SR_4K_SHP_O20_QRd02(shp_mp_ctrl_0a,		reg_mp_lum2_y1,	pp->shp_balance_4k[22],\
															reg_mp_lum2_y2,	pp->shp_balance_4k[23]);
				PE_SR_4K_SHP_O20_QRd03(shp_sp_ctrl_08,		reg_sp_lum1_y0,	pp->shp_balance_4k[24],\
															reg_sp_lum1_y1,	pp->shp_balance_4k[25],\
															reg_sp_lum1_y2,	pp->shp_balance_4k[26]);
				PE_SR_4K_SHP_O20_QRd01(shp_sp_ctrl_09,		reg_sp_lum2_y0,	pp->shp_balance_4k[27]);
				PE_SR_4K_SHP_O20_QRd02(shp_sp_ctrl_0a,		reg_sp_lum2_y1,	pp->shp_balance_4k[28],\
															reg_sp_lum2_y2,	pp->shp_balance_4k[29]);
				PE_SR_4K_SHP_O20_QRd04(shp_pti_ctrl_00,		reg_ptiv_enable,		pp->shp_ti_cmn_4k[0],\
															reg_ptiv_ti_mode,		pp->shp_ti_cmn_4k[1],\
															reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_4k[2],\
															reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_4k[3]);
				PE_SR_4K_SHP_O20_QRd04(shp_pti_ctrl_01,		reg_ptih_enable,		pp->shp_ti_cmn_4k[4],\
															reg_ptih_ti_mode,		pp->shp_ti_cmn_4k[5],\
															reg_ptih_mm_tap_size,	pp->shp_ti_cmn_4k[6],\
															reg_ptih_avg_tap_size,	pp->shp_ti_cmn_4k[7]);
				PE_SR_4K_SHP_O20_QRd04(shp_sti_ctrl_00,		reg_sti_enable,			pp->shp_ti_cmn_4k[8],\
															reg_sti_ti_mode,		pp->shp_ti_cmn_4k[9],\
															reg_sti_mm_tap_size,	pp->shp_ti_cmn_4k[10],\
															reg_sti_avg_tap_size,	pp->shp_ti_cmn_4k[11]);
				PE_SR_4K_SHP_O20_QRd03(shp_snr_ctrl_00,		reg_snr_blur_en,		pp->shp_simple_snr_4k[0],\
															reg_snr_blur_sel,		pp->shp_simple_snr_4k[1],\
															reg_snr_bilateral_th,	pp->shp_simple_snr_4k[2]);
			}
			pd = pp->shp_cmn_4k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_cmn_4k\n"
			"shp_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [20]0x%02X,",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);
			pd = pp->shp_map_cmn_4k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_map_cmn_4k\n"
			"shp_map_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_4k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_balance_4k\n"
			"shp_balance_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_4k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ti_cmn_4k\n"
			"shp_ti_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_4k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_4k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_simple_snr_4k\n"
			"shp_simple_snr_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSreEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_EE4_T *pp = (LX_PE_SHP_SR_EE4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ee_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ee_4k\n"
			"shp_ee_4k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[0],0,7),\
															reg_mp_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[1],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[2],0,7),\
															reg_sp_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[3],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[4],0,7),\
															reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[5],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[6],0,7),\
															reg_lc_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[7],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[8],0,7),\
															reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[9],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[10],0,7),\
															reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[11],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[12],0,7),\
															reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[13],0,7));
				#else
				PE_SR_4K_SHP_O20_QWr02(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[0],0,7),\
															reg_mp_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[1],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[2],0,7),\
															reg_sp_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[3],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_pti_ctrl_03,		reg_pti_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[4],0,7),\
															reg_pti_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[5],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b,		GET_BITS(pp->shp_ee_4k[6],0,7),\
															reg_lc_coring_gain_e_w,		GET_BITS(pp->shp_ee_4k[7],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[8],0,7),\
															reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[9],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[10],0,7),\
															reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[11],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_4k[12],0,7),\
															reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_4k[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for O20
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSreEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_EE4_T *pp = (LX_PE_SHP_SR_EE4_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_4K_SHP_O20_QRd02(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b,		pp->shp_ee_4k[0],\
															reg_mp_coring_gain_e_w,		pp->shp_ee_4k[1]);
				PE_SR_4K_SHP_O20_QRd02(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b,		pp->shp_ee_4k[2],\
															reg_sp_coring_gain_e_w,		pp->shp_ee_4k[3]);
				PE_SR_4K_SHP_O20_QRd02(shp_pti_ctrl_03,		reg_pti_coring_gain_e_b,	pp->shp_ee_4k[4],\
															reg_pti_coring_gain_e_w,	pp->shp_ee_4k[5]);
				PE_SR_4K_SHP_O20_QRd02(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b,		pp->shp_ee_4k[6],\
															reg_lc_coring_gain_e_w,		pp->shp_ee_4k[7]);
				PE_SR_4K_SHP_O20_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	pp->shp_ee_4k[8],\
															reg_dctp_coring_gain_e_w,	pp->shp_ee_4k[9]);
				PE_SR_4K_SHP_O20_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	pp->shp_ee_4k[10],\
															reg_tgen_coring_gain_e_w,	pp->shp_ee_4k[11]);
				PE_SR_4K_SHP_O20_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	pp->shp_ee_4k[12],\
															reg_nntg_coring_gain_e_w,	pp->shp_ee_4k[13]);
			}
			pd = pp->shp_ee_4k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ee_4k\n"
			"shp_ee_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSreDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_DE4_T *pp=(LX_PE_SHP_SR_DE4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_de_4k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_de_4k\n"
			"shp_de_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[0],0,7),\
															reg_mp_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[1],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[2],0,7),\
															reg_sp_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[3],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[4],0,7),\
															reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[5],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[6],0,7),\
															reg_lc_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[7],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[8],0,7),\
															reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[9],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[10],0,7),\
															reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[11],0,7));
				PE_SHP_HW_O20_SR_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[12],0,7),\
															reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[13],0,7));
				#else
				PE_SR_4K_SHP_O20_QWr02(shp_mp_ctrl_0c,		reg_mp_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[0],0,7),\
															reg_mp_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[1],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_sp_ctrl_0c,		reg_sp_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[2],0,7),\
															reg_sp_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[3],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_pti_ctrl_03,		reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[4],0,7),\
															reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[5],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_lc_ctrl_04,		reg_lc_coring_gain_t_b,		GET_BITS(pp->shp_de_4k[6],0,7),\
															reg_lc_coring_gain_t_w,		GET_BITS(pp->shp_de_4k[7],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[8],0,7),\
															reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[9],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[10],0,7),\
															reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[11],0,7));
				PE_SR_4K_SHP_O20_QWr02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_4k[12],0,7),\
															reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_4k[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSreDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR_DE4_T *pp=(LX_PE_SHP_SR_DE4_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_de_4k;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_4K_SHP_O20_QRd02(shp_mp_ctrl_0c,		reg_mp_coring_gain_t_b,		pp->shp_de_4k[0],\
															reg_mp_coring_gain_t_w,		pp->shp_de_4k[1]);
				PE_SR_4K_SHP_O20_QRd02(shp_sp_ctrl_0c,		reg_sp_coring_gain_t_b,		pp->shp_de_4k[2],\
															reg_sp_coring_gain_t_w,		pp->shp_de_4k[3]);
				PE_SR_4K_SHP_O20_QRd02(shp_pti_ctrl_03,		reg_pti_coring_gain_t_b,	pp->shp_de_4k[4],\
															reg_pti_coring_gain_t_w,	pp->shp_de_4k[5]);
				PE_SR_4K_SHP_O20_QRd02(shp_lc_ctrl_04,		reg_lc_coring_gain_t_b,		pp->shp_de_4k[6],\
															reg_lc_coring_gain_t_w,		pp->shp_de_4k[7]);
				PE_SR_4K_SHP_O20_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	pp->shp_de_4k[8],\
															reg_dctp_coring_gain_t_w,	pp->shp_de_4k[9]);
				PE_SR_4K_SHP_O20_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	pp->shp_de_4k[10],\
															reg_tgen_coring_gain_t_w,	pp->shp_de_4k[11]);
				PE_SR_4K_SHP_O20_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	pp->shp_de_4k[12],\
															reg_nntg_coring_gain_t_w,	pp->shp_de_4k[13]);

				PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_de_4k\n"
				"shp_de_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_de_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13]);
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr resolution common control - easy DB
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSre2KReEasyCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_RE_EASY_CMN_T *pp=(LX_PE_SHP_RE_EASY_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_vsd\n"
			"shp_ui_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_2K_SHP_WR04(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[0],0,8),\
													reg_mp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[1],0,8),\
													reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[2],0,8),\
													reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_vsd[3],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR03(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[4],0,8),\
													reg_sp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[5],0,8),\
													reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[6],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[7],0,8),\
													reg_mp_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[8],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[9],0,8),\
													reg_lc_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[10],0,8));
				#else
				PE_SR_2K_SHP_O20_QWr04(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[0],0,8),\
													reg_mp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[1],0,8),\
													reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[2],0,8),\
													reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_vsd[3],0,8));
				PE_SR_2K_SHP_O20_QWr03(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_ui_vsd[4],0,8),\
													reg_sp_im_us_gain,	GET_BITS(pp->shp_ui_vsd[5],0,8),\
													reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_vsd[6],0,8));
				PE_SR_2K_SHP_O20_QWr02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[7],0,8),\
													reg_mp_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[8],0,8));
				PE_SR_2K_SHP_O20_QWr02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_w,	GET_BITS(pp->shp_ui_vsd[9],0,8),\
													reg_lc_coring_gain_e_b,	GET_BITS(pp->shp_ui_vsd[10],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * set sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSre2KReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			UINT16 *pd16;
			LX_PE_SHP_SR2K_RE1_CMN_T *pp=(LX_PE_SHP_SR2K_RE1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_main_2k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_main_2k\n"
			"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_2k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd16 = pp->shp_dnn_sr_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_dnn_sr_vsd\n"
			"shp_dnn_sr_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				/*shp_ui_main_2k*/
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_dctp_ctrl_1d,	reg_dctp_gain,	GET_BITS(pp->shp_ui_main_2k[0],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_2k[1],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_dj_ctrl_1e,	reg_dj_soft_g1_mul, GET_BITS(pp->shp_ui_main_2k[2],0,6));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_dj_ctrl_1f,	reg_dj_soft_g2_mul, GET_BITS(pp->shp_ui_main_2k[3],0,6));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_2k[4],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_der_ctrl_00,	reg_derh_csft_gain, GET_BITS(pp->shp_ui_main_2k[5],0,6));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_main_2k[6],0,6),\
																	reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_main_2k[7],0,6));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_main_2k[8],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_main_2k[9],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_main_2k[10],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_sti_ctrl_00,	reg_sti_master_gain,	GET_BITS(pp->shp_ui_main_2k[11],0,8));
				/*shp_dnn_sr_vsd*/
				PE_SHP_HW_O20_SR_MERG_WR01(sr_merge_blend_00,	reg_blend_amp_weight,	GET_BITS(pp->shp_dnn_sr_vsd[0],0,12));
				PE_SHP_HW_O20_SR_MERG_WR04(sr_merge_mmd_05, 		reg_ti_gain_lut_x0, GET_BITS(pp->shp_dnn_sr_vsd[1],0,8),\
																	reg_ti_gain_lut_y0, GET_BITS(pp->shp_dnn_sr_vsd[2],0,8),\
																	reg_ti_gain_lut_x1, GET_BITS(pp->shp_dnn_sr_vsd[3],0,8),\
																	reg_ti_gain_lut_y1, GET_BITS(pp->shp_dnn_sr_vsd[4],0,8));
				PE_SHP_HW_O20_SR_MERG_WR04(sr_merge_mmd_06, 		reg_ti_gain_lut_x2, GET_BITS(pp->shp_dnn_sr_vsd[5],0,8),\
																	reg_ti_gain_lut_y2, GET_BITS(pp->shp_dnn_sr_vsd[6],0,8),\
																	reg_ti_gain_lut_x3, GET_BITS(pp->shp_dnn_sr_vsd[7],0,8),\
																	reg_ti_gain_lut_y3, GET_BITS(pp->shp_dnn_sr_vsd[8],0,8));
				#else
				PE_SR_2K_SHP_O20_QWr01(shp_dctp_ctrl_1d,		reg_dctp_gain,	GET_BITS(pp->shp_ui_main_2k[0],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_tgen_ctrl_00,		reg_tgen_master_gain,	GET_BITS(pp->shp_ui_main_2k[1],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul, GET_BITS(pp->shp_ui_main_2k[2],0,6));
				PE_SR_2K_SHP_O20_QWr01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul, GET_BITS(pp->shp_ui_main_2k[3],0,6));
				PE_SR_2K_SHP_O20_QWr01(shp_nntg_ctrl_0e,		reg_nntg_denoise_gain,	GET_BITS(pp->shp_ui_main_2k[4],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_der_ctrl_00,		reg_derh_csft_gain, GET_BITS(pp->shp_ui_main_2k[5],0,6));
				PE_SR_2K_SHP_O20_QWr02(shp_der_ctrl_02,		reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_main_2k[6],0,6),\
																reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_main_2k[7],0,6));
				PE_SR_2K_SHP_O20_QWr01(shp_mp_ctrl_01,		reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_main_2k[8],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_sp_ctrl_01,		reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_main_2k[9],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_mp_ctrl_01,		reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_main_2k[10],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_sti_ctrl_00,		reg_sti_master_gain,	GET_BITS(pp->shp_ui_main_2k[11],0,8));
				/*shp_dnn_sr_vsd*/
				PE_SR_MERG_O20_QWr01(sr_merge_blend_00,		reg_blend_amp_weight,	GET_BITS(pp->shp_dnn_sr_vsd[0],0,12));
				PE_SR_MERG_O20_QWr04(sr_merge_mmd_05, 		reg_ti_gain_lut_x0, GET_BITS(pp->shp_dnn_sr_vsd[1],0,8),\
																reg_ti_gain_lut_y0, GET_BITS(pp->shp_dnn_sr_vsd[2],0,8),\
																reg_ti_gain_lut_x1, GET_BITS(pp->shp_dnn_sr_vsd[3],0,8),\
																reg_ti_gain_lut_y1, GET_BITS(pp->shp_dnn_sr_vsd[4],0,8));
				PE_SR_MERG_O20_QWr04(sr_merge_mmd_06, 		reg_ti_gain_lut_x2, GET_BITS(pp->shp_dnn_sr_vsd[5],0,8),\
																reg_ti_gain_lut_y2, GET_BITS(pp->shp_dnn_sr_vsd[6],0,8),\
																reg_ti_gain_lut_x3, GET_BITS(pp->shp_dnn_sr_vsd[7],0,8),\
																reg_ti_gain_lut_y3, GET_BITS(pp->shp_dnn_sr_vsd[8],0,8));

				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * get sr resolution common control
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSre2KReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			UINT16 *pd16;
			LX_PE_SHP_SR2K_RE1_CMN_T *pp=(LX_PE_SHP_SR2K_RE1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_O20_QRd01(shp_dctp_ctrl_1d,	reg_dctp_gain,			pp->shp_ui_main_2k[0]);
				PE_SR_2K_SHP_O20_QRd01(shp_tgen_ctrl_00,	reg_tgen_master_gain,	pp->shp_ui_main_2k[1]);
				PE_SR_2K_SHP_O20_QRd01(shp_dj_ctrl_1e,		reg_dj_soft_g1_mul, 	pp->shp_ui_main_2k[2]);
				PE_SR_2K_SHP_O20_QRd01(shp_dj_ctrl_1f,		reg_dj_soft_g2_mul, 	pp->shp_ui_main_2k[3]);
				PE_SR_2K_SHP_O20_QRd01(shp_nntg_ctrl_0e,	reg_nntg_denoise_gain,	pp->shp_ui_main_2k[4]);
				PE_SR_2K_SHP_O20_QRd01(shp_der_ctrl_00,		reg_derh_csft_gain, 	pp->shp_ui_main_2k[5]);
				PE_SR_2K_SHP_O20_QRd02(shp_der_ctrl_02,		reg_derh_edge_filter_gain_w,	pp->shp_ui_main_2k[6],\
															reg_derh_edge_filter_gain_b,	pp->shp_ui_main_2k[7]);
				PE_SR_2K_SHP_O20_QRd01(shp_mp_ctrl_01,		reg_mp_im_gain_h,	pp->shp_ui_main_2k[8]);
				PE_SR_2K_SHP_O20_QRd01(shp_sp_ctrl_01,		reg_sp_im_gain_h,	pp->shp_ui_main_2k[9]);
				PE_SR_2K_SHP_O20_QRd01(shp_mp_ctrl_01,		reg_mp_im_gain_v,	pp->shp_ui_main_2k[10]);
				PE_SR_2K_SHP_O20_QRd01(shp_sti_ctrl_00,		reg_sti_master_gain,pp->shp_ui_main_2k[11]);
				/*shp_dnn_sr_vsd*/
				PE_SR_MERG_O20_QRd01(sr_merge_blend_00,		reg_blend_amp_weight,	pp->shp_dnn_sr_vsd[0]);
				PE_SR_MERG_O20_QRd04(sr_merge_mmd_05, 		reg_ti_gain_lut_x0, 	pp->shp_dnn_sr_vsd[1],\
																reg_ti_gain_lut_y0, pp->shp_dnn_sr_vsd[2],\
																reg_ti_gain_lut_x1, pp->shp_dnn_sr_vsd[3],\
																reg_ti_gain_lut_y1, pp->shp_dnn_sr_vsd[4]);
				PE_SR_MERG_O20_QRd04(sr_merge_mmd_06, 		reg_ti_gain_lut_x2, 	pp->shp_dnn_sr_vsd[5],\
																reg_ti_gain_lut_y2, pp->shp_dnn_sr_vsd[6],\
																reg_ti_gain_lut_x3, pp->shp_dnn_sr_vsd[7],\
																reg_ti_gain_lut_y3, pp->shp_dnn_sr_vsd[8]);
				pd = pp->shp_ui_main_2k;
				PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_main_2k\n"
				"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_2k    [10]0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11]);
				pd16 = pp->shp_dnn_sr_vsd;
				PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_dnn_sr_vsd\n"
				"shp_dnn_sr_vsd	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd16[0], pd16[1], pd16[2], pd16[3], pd16[4], pd16[5], pd16[6], pd16[7], pd16[8]);
				
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSre2KReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_HOR_T *pp=(LX_PE_SHP_SR2K_RE_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_h_main_2k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_h_main_2k\n"
			"shp_ui_h_main_2k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_der_ctrl_00,	reg_derh_csft_gain,	GET_BITS(pp->shp_ui_h_main_2k[0],0,6));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,	GET_BITS(pp->shp_ui_h_main_2k[1],0,6),\
																reg_derh_edge_filter_gain_b,	GET_BITS(pp->shp_ui_h_main_2k[2],0,6));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_h,	GET_BITS(pp->shp_ui_h_main_2k[3],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_sp_ctrl_01,	reg_sp_im_gain_h,	GET_BITS(pp->shp_ui_h_main_2k[4],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_pti_ctrl_01,	reg_ptih_master_gain,	GET_BITS(pp->shp_ui_h_main_2k[5],0,8));
				#else
				PE_SR_2K_SHP_O20_QWr01(shp_der_ctrl_00,	reg_derh_csft_gain,			GET_BITS(pp->shp_ui_h_main_2k[0],0,6));
				PE_SR_2K_SHP_O20_QWr02(shp_der_ctrl_02,	reg_derh_edge_filter_gain_w,GET_BITS(pp->shp_ui_h_main_2k[1],0,6),\
														reg_derh_edge_filter_gain_b,GET_BITS(pp->shp_ui_h_main_2k[2],0,6));
				PE_SR_2K_SHP_O20_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_2k[3],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			GET_BITS(pp->shp_ui_h_main_2k[4],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_pti_ctrl_01,	reg_ptih_master_gain,		GET_BITS(pp->shp_ui_h_main_2k[5],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSre2KReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_HOR_T *pp=(LX_PE_SHP_SR2K_RE_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SR_2K_SHP_O20_QRd01(shp_der_ctrl_00, reg_derh_csft_gain, 		pp->shp_ui_h_main_2k[0]);
			PE_SR_2K_SHP_O20_QRd02(shp_der_ctrl_02, reg_derh_edge_filter_gain_w,pp->shp_ui_h_main_2k[1],\
													reg_derh_edge_filter_gain_b,pp->shp_ui_h_main_2k[2]);
			PE_SR_2K_SHP_O20_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_h,			pp->shp_ui_h_main_2k[3]);
			PE_SR_2K_SHP_O20_QRd01(shp_sp_ctrl_01,	reg_sp_im_gain_h,			pp->shp_ui_h_main_2k[4]);
			PE_SR_2K_SHP_O20_QRd01(shp_pti_ctrl_01, reg_ptih_master_gain,		pp->shp_ui_h_main_2k[5]);
			pd = pp->shp_ui_h_main_2k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_h_main_2k\n"
			"shp_ui_h_main_2k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);

		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSre2KReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_VER_T *pp=(LX_PE_SHP_SR2K_RE_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ui_v_main_2k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_v_main_2k\n"
			"shp_ui_v_main_2k    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_mp_ctrl_01,	reg_mp_im_gain_v,	GET_BITS(pp->shp_ui_v_main_2k[0],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_2k[1],0,8));
				#else
				PE_SR_2K_SHP_O20_QWr01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		GET_BITS(pp->shp_ui_v_main_2k[0],0,8));
				PE_SR_2K_SHP_O20_QWr01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	GET_BITS(pp->shp_ui_v_main_2k[1],0,8));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSre2KReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE_VER_T *pp=(LX_PE_SHP_SR2K_RE_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_O20_QRd01(shp_mp_ctrl_01,	reg_mp_im_gain_v,		pp->shp_ui_v_main_2k[0]);
				PE_SR_2K_SHP_O20_QRd01(shp_pti_ctrl_00,	reg_ptiv_master_gain,	pp->shp_ui_v_main_2k[1]);
			}
			pd = pp->shp_ui_v_main_2k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ui_v_main_2k\n"
			"shp_ui_v_main_2k    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSre2KReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{ 
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE1_MISC_T *pp=(LX_PE_SHP_SR2K_RE1_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_cmn_2k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_cmn_2k\n"
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);
			pd = pp->shp_djg_2k;

			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_djg_2k\n"
			"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_2k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_map_cmn_2k\n"
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_2k;

			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_balance_2k\n"
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_2k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ti_cmn_2k\n"
			"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				/*shp_cmn_2k*/
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_der_ctrl_01,	reg_derh_edge_y_filter_en,	GET_BITS(pp->shp_cmn_2k[0],0,1),\
																reg_derh_bflt_tap_size, GET_BITS(pp->shp_cmn_2k[1],0,3));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_mp_ctrl_00,	reg_mp_shp_en,	GET_BITS(pp->shp_cmn_2k[2],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_sp_ctrl_00,	reg_sp_shp_en,	GET_BITS(pp->shp_cmn_2k[3],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_mp_ctrl_01,	reg_mp_im_os_gain,	GET_BITS(pp->shp_cmn_2k[4],0,7),\
																reg_mp_im_us_gain,	GET_BITS(pp->shp_cmn_2k[5],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_sp_ctrl_01,	reg_sp_im_os_gain,	GET_BITS(pp->shp_cmn_2k[6],0,7),\
																reg_sp_im_us_gain,	GET_BITS(pp->shp_cmn_2k[7],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_dctp_ctrl_00,	reg_dctp_en,	GET_BITS(pp->shp_cmn_2k[8],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_dctp_ctrl_1e,	reg_dctp_coring_en, GET_BITS(pp->shp_cmn_2k[9],0,1),\
																reg_dctp_coring_mode,	GET_BITS(pp->shp_cmn_2k[10],0,2));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_tgen_ctrl_00,	reg_tgen_on_off,	GET_BITS(pp->shp_cmn_2k[11],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_tgen_ctrl_0a,	reg_tgen_coring_en, GET_BITS(pp->shp_cmn_2k[12],0,1),\
																reg_tgen_coring_mode,	GET_BITS(pp->shp_cmn_2k[13],0,2));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_nntg_ctrl_00,	reg_nntg_en,	GET_BITS(pp->shp_cmn_2k[14],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_nntg_ctrl_0f,	reg_nntg_coring_en, GET_BITS(pp->shp_cmn_2k[15],0,1),\
																reg_nntg_coring_mode,	GET_BITS(pp->shp_cmn_2k[16],0,2));
				/*shp_djg_2k*/
				PE_SHP_HW_O20_SR_2K_SHP_WR03(shp_dj_ctrl_00,	reg_dj_edf_en,	GET_BITS(pp->shp_djg_2k[0],0,1),\
																reg_dj_edge_adaptive_en,	GET_BITS(pp->shp_djg_2k[1],0,1),\
																reg_dj_soft_en, GET_BITS(pp->shp_djg_2k[2],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_dj_ctrl_03,	reg_dj_edge_min, GET_BITS(pp->shp_djg_2k[3],0,8),\
																reg_dj_edge_mul,	GET_BITS(pp->shp_djg_2k[4],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_dj_ctrl_00,	reg_dj_center_blur_mode,	GET_BITS(pp->shp_djg_2k[5],0,2),\
																reg_dj_n_avg_mode,	GET_BITS(pp->shp_djg_2k[6],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_dj_ctrl_01,	reg_dj_n_avg_gain,	GET_BITS(pp->shp_djg_2k[7],0,8));
				/*shp_map_cmn_2k*/
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_fd_ctrl_0b,	reg_fd_mnr_gain_e_en,	GET_BITS(pp->shp_map_cmn_2k[0],0,1),\
																reg_fd_mnr_gain_t_en,	GET_BITS(pp->shp_map_cmn_2k[1],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR04(shp_fd_ctrl_0d,	reg_fd_mnr_gain_x0,	GET_BITS(pp->shp_map_cmn_2k[2],0,8),\
																reg_fd_mnr_gain_x1,	GET_BITS(pp->shp_map_cmn_2k[3],0,8),\
																reg_fd_mnr_gain_y0,	GET_BITS(pp->shp_map_cmn_2k[4],0,8),\
																reg_fd_mnr_gain_y1,	GET_BITS(pp->shp_map_cmn_2k[5],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_fd_ctrl_11,	reg_fd_soft_gain_t_en,	GET_BITS(pp->shp_map_cmn_2k[6],0,1),\
																reg_fd_soft_gain_e_en,	GET_BITS(pp->shp_map_cmn_2k[7],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR04(shp_fd_ctrl_14,	reg_fd_soft_score_y3,	GET_BITS(pp->shp_map_cmn_2k[8],0,6),\
																reg_fd_soft_score_y2,	GET_BITS(pp->shp_map_cmn_2k[9],0,6),\
																reg_fd_soft_score_y1,	GET_BITS(pp->shp_map_cmn_2k[10],0,6),\
																reg_fd_soft_score_y0,	GET_BITS(pp->shp_map_cmn_2k[11],0,6));
				
				/*shp_balance_2k*/
				PE_SHP_HW_O20_SR_2K_SHP_WR03(shp_mp_ctrl_05,	reg_mp_gb_en,	GET_BITS(pp->shp_balance_2k[0],0,1),\
																reg_mp_gb_mode, GET_BITS(pp->shp_balance_2k[1],0,1),\
																reg_mp_gb_y1,	GET_BITS(pp->shp_balance_2k[2],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_mp_ctrl_06,	reg_mp_gb_y2,	GET_BITS(pp->shp_balance_2k[3],0,8),\
																reg_mp_gb_y3,	GET_BITS(pp->shp_balance_2k[4],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR03(shp_sp_ctrl_05,	reg_sp_gb_en,	GET_BITS(pp->shp_balance_2k[5],0,1),\
																reg_sp_gb_mode, GET_BITS(pp->shp_balance_2k[6],0,1),\
																reg_sp_gb_y1,	GET_BITS(pp->shp_balance_2k[7],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_sp_ctrl_06,	reg_sp_gb_y2,	GET_BITS(pp->shp_balance_2k[8],0,8),\
																reg_sp_gb_y3,	GET_BITS(pp->shp_balance_2k[9],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_lc_ctrl_00,	reg_lc_shp_en,	GET_BITS(pp->shp_balance_2k[10],0,1),\
																reg_lc_gb_en,	GET_BITS(pp->shp_balance_2k[11],0,1));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_lc_ctrl_01,	reg_lc_gb_y1,	GET_BITS(pp->shp_balance_2k[12],0,8),\
																reg_lc_gb_y2,	GET_BITS(pp->shp_balance_2k[13],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_lc_ctrl_02,	reg_lc_gb_y3,	GET_BITS(pp->shp_balance_2k[14],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR03(shp_lc_ctrl_00,	reg_lc_center_target, GET_BITS(pp->shp_balance_2k[15],0,8),\
																reg_lc_center_gain, GET_BITS(pp->shp_balance_2k[16],0,8),\
																reg_lc_local_gain,	GET_BITS(pp->shp_balance_2k[17],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR03(shp_mp_ctrl_08,	reg_mp_lum1_y0, GET_BITS(pp->shp_balance_2k[18],0,8),\
																reg_mp_lum1_y1, GET_BITS(pp->shp_balance_2k[19],0,8),\
																reg_mp_lum1_y2, GET_BITS(pp->shp_balance_2k[20],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_mp_ctrl_09,	reg_mp_lum2_y0, GET_BITS(pp->shp_balance_2k[21],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_mp_ctrl_0a,	reg_mp_lum2_y1, GET_BITS(pp->shp_balance_2k[22],0,8),\
																reg_mp_lum2_y2, GET_BITS(pp->shp_balance_2k[23],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR03(shp_sp_ctrl_08,	reg_sp_lum1_y0, GET_BITS(pp->shp_balance_2k[24],0,8),\
																reg_sp_lum1_y1, GET_BITS(pp->shp_balance_2k[25],0,8),\
																reg_sp_lum1_y2, GET_BITS(pp->shp_balance_2k[26],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR01(shp_sp_ctrl_09,	reg_sp_lum2_y0, GET_BITS(pp->shp_balance_2k[27],0,8));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_sp_ctrl_0a,	reg_sp_lum2_y1, GET_BITS(pp->shp_balance_2k[28],0,8),\
																reg_sp_lum2_y2, GET_BITS(pp->shp_balance_2k[29],0,8));
				/*shp_ti_cmn_2k*/
				PE_SHP_HW_O20_SR_2K_SHP_WR04(shp_pti_ctrl_00,	reg_ptiv_enable,	GET_BITS(pp->shp_ti_cmn_2k[0],0,1),\
																reg_ptiv_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[1],0,1),\
																reg_ptiv_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[2],0,2),\
																reg_ptiv_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[3],0,2));
				PE_SHP_HW_O20_SR_2K_SHP_WR04(shp_pti_ctrl_01,	reg_ptih_enable,	GET_BITS(pp->shp_ti_cmn_2k[4],0,1),\
																reg_ptih_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[5],0,1),\
																reg_ptih_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[6],0,2),\
																reg_ptih_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[7],0,2));
				PE_SHP_HW_O20_SR_2K_SHP_WR04(shp_sti_ctrl_00,	reg_sti_enable, GET_BITS(pp->shp_ti_cmn_2k[8],0,1),\
																reg_sti_ti_mode,	GET_BITS(pp->shp_ti_cmn_2k[9],0,1),\
																reg_sti_mm_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[10],0,2),\
																reg_sti_avg_tap_size,	GET_BITS(pp->shp_ti_cmn_2k[11],0,2));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_snr_ctrl_00,	reg_snr_blur_en,	GET_BITS(pp->shp_ti_cmn_2k[12],0,1),\
																reg_snr_blur_sel,	GET_BITS(pp->shp_ti_cmn_2k[13],0,2));
				
				#else
				PE_SR_2K_SHP_O20_QWr02(shp_der_ctrl_01,		reg_derh_edge_y_filter_en,	pp->shp_cmn_2k[0],\
															reg_derh_bflt_tap_size, pp->shp_cmn_2k[1]);
				PE_SR_2K_SHP_O20_QWr01(shp_mp_ctrl_00,		reg_mp_shp_en,			pp->shp_cmn_2k[2]);
				PE_SR_2K_SHP_O20_QWr01(shp_sp_ctrl_00,		reg_sp_shp_en,			pp->shp_cmn_2k[3]);
				PE_SR_2K_SHP_O20_QWr02(shp_mp_ctrl_01,		reg_mp_im_os_gain,		pp->shp_cmn_2k[4],\
															reg_mp_im_us_gain,		pp->shp_cmn_2k[5]);
				PE_SR_2K_SHP_O20_QWr02(shp_sp_ctrl_01,		reg_sp_im_os_gain,		pp->shp_cmn_2k[6],\
															reg_sp_im_us_gain,		pp->shp_cmn_2k[7]);
				PE_SR_2K_SHP_O20_QWr01(shp_dctp_ctrl_00,	reg_dctp_en,			pp->shp_cmn_2k[8]);
				PE_SR_2K_SHP_O20_QWr02(shp_dctp_ctrl_1e,	reg_dctp_coring_en, 	pp->shp_cmn_2k[9],\
															reg_dctp_coring_mode,	pp->shp_cmn_2k[10]);
				PE_SR_2K_SHP_O20_QWr01(shp_tgen_ctrl_00,	reg_tgen_on_off,		pp->shp_cmn_2k[11]);
				PE_SR_2K_SHP_O20_QWr02(shp_tgen_ctrl_0a,	reg_tgen_coring_en, 	pp->shp_cmn_2k[12],\
															reg_tgen_coring_mode,	pp->shp_cmn_2k[13]);
				PE_SR_2K_SHP_O20_QWr01(shp_nntg_ctrl_00,	reg_nntg_en,			pp->shp_cmn_2k[14]);
				PE_SR_2K_SHP_O20_QWr02(shp_nntg_ctrl_0f,	reg_nntg_coring_en, 	pp->shp_cmn_2k[15],\
															reg_nntg_coring_mode,	pp->shp_cmn_2k[16]);
				/*shp_djg_2k*/
				PE_SR_2K_SHP_O20_QWr03(shp_dj_ctrl_00,		reg_dj_edf_en,			pp->shp_djg_2k[0],\
															reg_dj_edge_adaptive_en,pp->shp_djg_2k[1],\
															reg_dj_soft_en, 		pp->shp_djg_2k[2]);
				PE_SR_2K_SHP_O20_QWr02(shp_dj_ctrl_03,		reg_dj_edge_min, 		pp->shp_djg_2k[3],\
															reg_dj_edge_mul,		pp->shp_djg_2k[4]);
				PE_SR_2K_SHP_O20_QWr02(shp_dj_ctrl_00,		reg_dj_center_blur_mode,pp->shp_djg_2k[5],\
															reg_dj_n_avg_mode,		pp->shp_djg_2k[6]);
				PE_SR_2K_SHP_O20_QWr01(shp_dj_ctrl_01,		reg_dj_n_avg_gain,		pp->shp_djg_2k[7]);
				/*shp_map_cmn_2k*/
				PE_SR_2K_SHP_O20_QWr02(shp_fd_ctrl_0b,		reg_fd_mnr_gain_e_en,	pp->shp_map_cmn_2k[0],\
															reg_fd_mnr_gain_t_en,	pp->shp_map_cmn_2k[1]);
				PE_SR_2K_SHP_O20_QWr04(shp_fd_ctrl_0d,		reg_fd_mnr_gain_x0,		pp->shp_map_cmn_2k[2],\
															reg_fd_mnr_gain_x1,		pp->shp_map_cmn_2k[3],\
															reg_fd_mnr_gain_y0,		pp->shp_map_cmn_2k[4],\
															reg_fd_mnr_gain_y1,		pp->shp_map_cmn_2k[5]);
				PE_SR_2K_SHP_O20_QWr02(shp_fd_ctrl_11,		reg_fd_soft_gain_t_en,	pp->shp_map_cmn_2k[6],\
															reg_fd_soft_gain_e_en,	pp->shp_map_cmn_2k[7]);
				PE_SR_2K_SHP_O20_QWr04(shp_fd_ctrl_14,		reg_fd_soft_score_y3,	pp->shp_map_cmn_2k[8],\
															reg_fd_soft_score_y2,	pp->shp_map_cmn_2k[9],\
															reg_fd_soft_score_y1,	pp->shp_map_cmn_2k[10],\
															reg_fd_soft_score_y0,	pp->shp_map_cmn_2k[11]);
				
				/*shp_balance_2k*/
				PE_SR_2K_SHP_O20_QWr03(shp_mp_ctrl_05,		reg_mp_gb_en,	pp->shp_balance_2k[0],\
															reg_mp_gb_mode, pp->shp_balance_2k[1],\
															reg_mp_gb_y1,	pp->shp_balance_2k[2]);
				PE_SR_2K_SHP_O20_QWr02(shp_mp_ctrl_06,		reg_mp_gb_y2,	pp->shp_balance_2k[3],\
															reg_mp_gb_y3,	pp->shp_balance_2k[4]);
				PE_SR_2K_SHP_O20_QWr03(shp_sp_ctrl_05,		reg_sp_gb_en,	pp->shp_balance_2k[5],\
															reg_sp_gb_mode, pp->shp_balance_2k[6],\
															reg_sp_gb_y1,	pp->shp_balance_2k[7]);
				PE_SR_2K_SHP_O20_QWr02(shp_sp_ctrl_06,		reg_sp_gb_y2,	pp->shp_balance_2k[8],\
															reg_sp_gb_y3,	pp->shp_balance_2k[9]);
				PE_SR_2K_SHP_O20_QWr02(shp_lc_ctrl_00,		reg_lc_shp_en,	pp->shp_balance_2k[10],\
															reg_lc_gb_en,	pp->shp_balance_2k[11]);
				PE_SR_2K_SHP_O20_QWr02(shp_lc_ctrl_01,		reg_lc_gb_y1,	pp->shp_balance_2k[12],\
															reg_lc_gb_y2,	pp->shp_balance_2k[13]);
				PE_SR_2K_SHP_O20_QWr01(shp_lc_ctrl_02,		reg_lc_gb_y3,	pp->shp_balance_2k[14]);
				PE_SR_2K_SHP_O20_QWr03(shp_lc_ctrl_00,		reg_lc_center_target, pp->shp_balance_2k[15],\
															reg_lc_center_gain, pp->shp_balance_2k[16],\
															reg_lc_local_gain,	pp->shp_balance_2k[17]);
				PE_SR_2K_SHP_O20_QWr03(shp_mp_ctrl_08,		reg_mp_lum1_y0, pp->shp_balance_2k[18],\
															reg_mp_lum1_y1, pp->shp_balance_2k[19],\
															reg_mp_lum1_y2, pp->shp_balance_2k[20]);
				PE_SR_2K_SHP_O20_QWr01(shp_mp_ctrl_09,		reg_mp_lum2_y0, pp->shp_balance_2k[21]);
				PE_SR_2K_SHP_O20_QWr02(shp_mp_ctrl_0a,		reg_mp_lum2_y1, pp->shp_balance_2k[22],\
															reg_mp_lum2_y2, pp->shp_balance_2k[23]);
				PE_SR_2K_SHP_O20_QWr03(shp_sp_ctrl_08,		reg_sp_lum1_y0, pp->shp_balance_2k[24],\
															reg_sp_lum1_y1, pp->shp_balance_2k[25],\
															reg_sp_lum1_y2, pp->shp_balance_2k[26]);
				PE_SR_2K_SHP_O20_QWr01(shp_sp_ctrl_09,		reg_sp_lum2_y0, pp->shp_balance_2k[27]);
				PE_SR_2K_SHP_O20_QWr02(shp_sp_ctrl_0a,		reg_sp_lum2_y1, pp->shp_balance_2k[28],\
															reg_sp_lum2_y2, pp->shp_balance_2k[29]);
				/*shp_ti_cmn_2k*/
				PE_SR_2K_SHP_O20_QWr04(shp_pti_ctrl_00,		reg_ptiv_enable,		pp->shp_ti_cmn_2k[0],\
															reg_ptiv_ti_mode,		pp->shp_ti_cmn_2k[1],\
															reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_2k[2],\
															reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_2k[3]);
				PE_SR_2K_SHP_O20_QWr04(shp_pti_ctrl_01,		reg_ptih_enable,		pp->shp_ti_cmn_2k[4],\
															reg_ptih_ti_mode,		pp->shp_ti_cmn_2k[5],\
															reg_ptih_mm_tap_size,	pp->shp_ti_cmn_2k[6],\
															reg_ptih_avg_tap_size,	pp->shp_ti_cmn_2k[7]);
				PE_SR_2K_SHP_O20_QWr04(shp_sti_ctrl_00,		reg_sti_enable, 		pp->shp_ti_cmn_2k[8],\
															reg_sti_ti_mode,		pp->shp_ti_cmn_2k[9],\
															reg_sti_mm_tap_size,	pp->shp_ti_cmn_2k[10],\
															reg_sti_avg_tap_size,	pp->shp_ti_cmn_2k[11]);
				PE_SR_2K_SHP_O20_QWr02(shp_snr_ctrl_00,		reg_snr_blur_en,		pp->shp_ti_cmn_2k[12],\
															reg_snr_blur_sel,		pp->shp_ti_cmn_2k[13]);
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSre2KReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_RE1_MISC_T *pp=(LX_PE_SHP_SR2K_RE1_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_SR_2K_SHP_O20_QRd02(shp_der_ctrl_01,		reg_derh_edge_y_filter_en,	pp->shp_cmn_2k[0],\
															reg_derh_bflt_tap_size, pp->shp_cmn_2k[1]);
				PE_SR_2K_SHP_O20_QRd01(shp_mp_ctrl_00,		reg_mp_shp_en,			pp->shp_cmn_2k[2]);
				PE_SR_2K_SHP_O20_QRd01(shp_sp_ctrl_00,		reg_sp_shp_en,			pp->shp_cmn_2k[3]);
				PE_SR_2K_SHP_O20_QRd02(shp_mp_ctrl_01,		reg_mp_im_os_gain,		pp->shp_cmn_2k[4],\
															reg_mp_im_us_gain,		pp->shp_cmn_2k[5]);
				PE_SR_2K_SHP_O20_QRd02(shp_sp_ctrl_01,		reg_sp_im_os_gain,		pp->shp_cmn_2k[6],\
															reg_sp_im_us_gain,		pp->shp_cmn_2k[7]);
				PE_SR_2K_SHP_O20_QRd01(shp_dctp_ctrl_00,	reg_dctp_en,			pp->shp_cmn_2k[8]);
				PE_SR_2K_SHP_O20_QRd02(shp_dctp_ctrl_1e,	reg_dctp_coring_en, 	pp->shp_cmn_2k[9],\
															reg_dctp_coring_mode,	pp->shp_cmn_2k[10]);
				PE_SR_2K_SHP_O20_QRd01(shp_tgen_ctrl_00,	reg_tgen_on_off,		pp->shp_cmn_2k[11]);
				PE_SR_2K_SHP_O20_QRd02(shp_tgen_ctrl_0a,	reg_tgen_coring_en, 	pp->shp_cmn_2k[12],\
															reg_tgen_coring_mode,	pp->shp_cmn_2k[13]);
				PE_SR_2K_SHP_O20_QRd01(shp_nntg_ctrl_00,	reg_nntg_en,			pp->shp_cmn_2k[14]);
				PE_SR_2K_SHP_O20_QRd02(shp_nntg_ctrl_0f,	reg_nntg_coring_en, 	pp->shp_cmn_2k[15],\
															reg_nntg_coring_mode,	pp->shp_cmn_2k[16]);
				/*shp_djg_2k*/
				PE_SR_2K_SHP_O20_QRd03(shp_dj_ctrl_00,		reg_dj_edf_en,			pp->shp_djg_2k[0],\
															reg_dj_edge_adaptive_en,pp->shp_djg_2k[1],\
															reg_dj_soft_en, 		pp->shp_djg_2k[2]);
				PE_SR_2K_SHP_O20_QRd02(shp_dj_ctrl_03,		reg_dj_edge_min, 		pp->shp_djg_2k[3],\
															reg_dj_edge_mul,		pp->shp_djg_2k[4]);
				PE_SR_2K_SHP_O20_QRd02(shp_dj_ctrl_00,		reg_dj_center_blur_mode,pp->shp_djg_2k[5],\
															reg_dj_n_avg_mode,		pp->shp_djg_2k[6]);
				PE_SR_2K_SHP_O20_QRd01(shp_dj_ctrl_01,		reg_dj_n_avg_gain,		pp->shp_djg_2k[7]);
				/*shp_map_cmn_2k*/
				PE_SR_2K_SHP_O20_QRd02(shp_fd_ctrl_0b,		reg_fd_mnr_gain_e_en,	pp->shp_map_cmn_2k[0],\
															reg_fd_mnr_gain_t_en,	pp->shp_map_cmn_2k[1]);
				PE_SR_2K_SHP_O20_QRd04(shp_fd_ctrl_0d,		reg_fd_mnr_gain_x0,		pp->shp_map_cmn_2k[2],\
															reg_fd_mnr_gain_x1,		pp->shp_map_cmn_2k[3],\
															reg_fd_mnr_gain_y0,		pp->shp_map_cmn_2k[4],\
															reg_fd_mnr_gain_y1,		pp->shp_map_cmn_2k[5]);
				PE_SR_2K_SHP_O20_QRd02(shp_fd_ctrl_11,		reg_fd_soft_gain_t_en,	pp->shp_map_cmn_2k[6],\
															reg_fd_soft_gain_e_en,	pp->shp_map_cmn_2k[7]);
				PE_SR_2K_SHP_O20_QRd04(shp_fd_ctrl_14,		reg_fd_soft_score_y3,	pp->shp_map_cmn_2k[8],\
															reg_fd_soft_score_y2,	pp->shp_map_cmn_2k[9],\
															reg_fd_soft_score_y1,	pp->shp_map_cmn_2k[10],\
															reg_fd_soft_score_y0,	pp->shp_map_cmn_2k[11]);
				
				/*shp_balance_2k*/
				PE_SR_2K_SHP_O20_QRd03(shp_mp_ctrl_05,		reg_mp_gb_en,	pp->shp_balance_2k[0],\
															reg_mp_gb_mode, pp->shp_balance_2k[1],\
															reg_mp_gb_y1,	pp->shp_balance_2k[2]);
				PE_SR_2K_SHP_O20_QRd02(shp_mp_ctrl_06,		reg_mp_gb_y2,	pp->shp_balance_2k[3],\
															reg_mp_gb_y3,	pp->shp_balance_2k[4]);
				PE_SR_2K_SHP_O20_QRd03(shp_sp_ctrl_05,		reg_sp_gb_en,	pp->shp_balance_2k[5],\
															reg_sp_gb_mode, pp->shp_balance_2k[6],\
															reg_sp_gb_y1,	pp->shp_balance_2k[7]);
				PE_SR_2K_SHP_O20_QRd02(shp_sp_ctrl_06,		reg_sp_gb_y2,	pp->shp_balance_2k[8],\
															reg_sp_gb_y3,	pp->shp_balance_2k[9]);
				PE_SR_2K_SHP_O20_QRd02(shp_lc_ctrl_00,		reg_lc_shp_en,	pp->shp_balance_2k[10],\
															reg_lc_gb_en,	pp->shp_balance_2k[11]);
				PE_SR_2K_SHP_O20_QRd02(shp_lc_ctrl_01,		reg_lc_gb_y1,	pp->shp_balance_2k[12],\
															reg_lc_gb_y2,	pp->shp_balance_2k[13]);
				PE_SR_2K_SHP_O20_QRd01(shp_lc_ctrl_02,		reg_lc_gb_y3,	pp->shp_balance_2k[14]);
				PE_SR_2K_SHP_O20_QRd03(shp_lc_ctrl_00,		reg_lc_center_target, pp->shp_balance_2k[15],\
															reg_lc_center_gain, pp->shp_balance_2k[16],\
															reg_lc_local_gain,	pp->shp_balance_2k[17]);
				PE_SR_2K_SHP_O20_QRd03(shp_mp_ctrl_08,		reg_mp_lum1_y0, pp->shp_balance_2k[18],\
															reg_mp_lum1_y1, pp->shp_balance_2k[19],\
															reg_mp_lum1_y2, pp->shp_balance_2k[20]);
				PE_SR_2K_SHP_O20_QRd01(shp_mp_ctrl_09,		reg_mp_lum2_y0, pp->shp_balance_2k[21]);
				PE_SR_2K_SHP_O20_QRd02(shp_mp_ctrl_0a,		reg_mp_lum2_y1, pp->shp_balance_2k[22],\
															reg_mp_lum2_y2, pp->shp_balance_2k[23]);
				PE_SR_2K_SHP_O20_QRd03(shp_sp_ctrl_08,		reg_sp_lum1_y0, pp->shp_balance_2k[24],\
															reg_sp_lum1_y1, pp->shp_balance_2k[25],\
															reg_sp_lum1_y2, pp->shp_balance_2k[26]);
				PE_SR_2K_SHP_O20_QRd01(shp_sp_ctrl_09,		reg_sp_lum2_y0, pp->shp_balance_2k[27]);
				PE_SR_2K_SHP_O20_QRd02(shp_sp_ctrl_0a,		reg_sp_lum2_y1, pp->shp_balance_2k[28],\
															reg_sp_lum2_y2, pp->shp_balance_2k[29]);
				/*shp_ti_cmn_2k*/
				PE_SR_2K_SHP_O20_QRd04(shp_pti_ctrl_00,		reg_ptiv_enable,		pp->shp_ti_cmn_2k[0],\
															reg_ptiv_ti_mode,		pp->shp_ti_cmn_2k[1],\
															reg_ptiv_mm_tap_size,	pp->shp_ti_cmn_2k[2],\
															reg_ptiv_avg_tap_size,	pp->shp_ti_cmn_2k[3]);
				PE_SR_2K_SHP_O20_QRd04(shp_pti_ctrl_01,		reg_ptih_enable,		pp->shp_ti_cmn_2k[4],\
															reg_ptih_ti_mode,		pp->shp_ti_cmn_2k[5],\
															reg_ptih_mm_tap_size,	pp->shp_ti_cmn_2k[6],\
															reg_ptih_avg_tap_size,	pp->shp_ti_cmn_2k[7]);
				PE_SR_2K_SHP_O20_QRd04(shp_sti_ctrl_00,		reg_sti_enable, 		pp->shp_ti_cmn_2k[8],\
															reg_sti_ti_mode,		pp->shp_ti_cmn_2k[9],\
															reg_sti_mm_tap_size,	pp->shp_ti_cmn_2k[10],\
															reg_sti_avg_tap_size,	pp->shp_ti_cmn_2k[11]);
				PE_SR_2K_SHP_O20_QRd02(shp_snr_ctrl_00,		reg_snr_blur_en,		pp->shp_ti_cmn_2k[12],\
															reg_snr_blur_sel,		pp->shp_ti_cmn_2k[13]);


			}
			pd = pp->shp_cmn_2k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_cmn_2k\n"
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16]);
			pd = pp->shp_djg_2k;

			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_djg_2k\n"
			"shp_djg_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_2k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_map_cmn_2k\n"
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_2k;

			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_balance_2k\n"
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_2k;
			PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ti_cmn_2k\n"
			"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

		}
		
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSre2KEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_EE1_T *pp = (LX_PE_SHP_SR2K_EE1_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_ee_2k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ee_2k\n"
			"shp_ee_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_2k	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[0],0,7),\
																reg_mp_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[1],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[2],0,7),\
																reg_sp_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[3],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_e_b,GET_BITS(pp->shp_ee_2k[4],0,7),\
																reg_pti_coring_gain_e_w,GET_BITS(pp->shp_ee_2k[5],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[6],0,7),\
																reg_lc_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[7],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[8],0,7),\
																reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[9],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[10],0,7),\
																reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[11],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[12],0,7),\
																reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[13],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[14],0,7),\
																reg_mp_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[15],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[16],0,7),\
																reg_sp_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[17],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,GET_BITS(pp->shp_ee_2k[18],0,7),\
																reg_pti_coring_gain_t_w,GET_BITS(pp->shp_ee_2k[19],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[20],0,7),\
																reg_lc_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[21],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[22],0,7),\
																reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[23],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[24],0,7),\
																reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[25],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[26],0,7),\
																reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[27],0,7));
				#else
				PE_SR_2K_SHP_O20_QWr02(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[0],0,7),\
															reg_mp_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[1],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[2],0,7),\
															reg_sp_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[3],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_pti_ctrl_03,		reg_pti_coring_gain_e_b,GET_BITS(pp->shp_ee_2k[4],0,7),\
															reg_pti_coring_gain_e_w,GET_BITS(pp->shp_ee_2k[5],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b, GET_BITS(pp->shp_ee_2k[6],0,7),\
															reg_lc_coring_gain_e_w, GET_BITS(pp->shp_ee_2k[7],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[8],0,7),\
															reg_dctp_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[9],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[10],0,7),\
															reg_tgen_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[11],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	GET_BITS(pp->shp_ee_2k[12],0,7),\
															reg_nntg_coring_gain_e_w,	GET_BITS(pp->shp_ee_2k[13],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_mp_ctrl_0c,		reg_mp_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[14],0,7),\
															reg_mp_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[15],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_sp_ctrl_0c,		reg_sp_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[16],0,7),\
															reg_sp_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[17],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_pti_ctrl_03,		reg_pti_coring_gain_t_b,GET_BITS(pp->shp_ee_2k[18],0,7),\
															reg_pti_coring_gain_t_w,GET_BITS(pp->shp_ee_2k[19],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_lc_ctrl_04,		reg_lc_coring_gain_t_b, GET_BITS(pp->shp_ee_2k[20],0,7),\
															reg_lc_coring_gain_t_w, GET_BITS(pp->shp_ee_2k[21],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[22],0,7),\
															reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[23],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[24],0,7),\
															reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[25],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_ee_2k[26],0,7),\
															reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_ee_2k[27],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for O20
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSre2KEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_EE1_T *pp = (LX_PE_SHP_SR2K_EE1_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_O20_QRd02(shp_mp_ctrl_0c,		reg_mp_coring_gain_e_b, pp->shp_ee_2k[0],\
															reg_mp_coring_gain_e_w, pp->shp_ee_2k[1]);
				PE_SR_2K_SHP_O20_QRd02(shp_sp_ctrl_0c,		reg_sp_coring_gain_e_b, pp->shp_ee_2k[2],\
															reg_sp_coring_gain_e_w, pp->shp_ee_2k[3]);
				PE_SR_2K_SHP_O20_QRd02(shp_pti_ctrl_03,		reg_pti_coring_gain_e_b,pp->shp_ee_2k[4],\
															reg_pti_coring_gain_e_w,pp->shp_ee_2k[5]);
				PE_SR_2K_SHP_O20_QRd02(shp_lc_ctrl_04,		reg_lc_coring_gain_e_b, pp->shp_ee_2k[6],\
															reg_lc_coring_gain_e_w, pp->shp_ee_2k[7]);
				PE_SR_2K_SHP_O20_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_e_b,	pp->shp_ee_2k[8],\
															reg_dctp_coring_gain_e_w,	pp->shp_ee_2k[9]);
				PE_SR_2K_SHP_O20_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_e_b,	pp->shp_ee_2k[10],\
															reg_tgen_coring_gain_e_w,	pp->shp_ee_2k[11]);
				PE_SR_2K_SHP_O20_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_e_b,	pp->shp_ee_2k[12],\
															reg_nntg_coring_gain_e_w,	pp->shp_ee_2k[13]);
				PE_SR_2K_SHP_O20_QRd02(shp_mp_ctrl_0c,		reg_mp_coring_gain_t_b, pp->shp_ee_2k[14],\
															reg_mp_coring_gain_t_w, pp->shp_ee_2k[15]);
				PE_SR_2K_SHP_O20_QRd02(shp_sp_ctrl_0c,		reg_sp_coring_gain_t_b, pp->shp_ee_2k[16],\
															reg_sp_coring_gain_t_w, pp->shp_ee_2k[17]);
				PE_SR_2K_SHP_O20_QRd02(shp_pti_ctrl_03,		reg_pti_coring_gain_t_b,pp->shp_ee_2k[18],\
															reg_pti_coring_gain_t_w,pp->shp_ee_2k[19]);
				PE_SR_2K_SHP_O20_QRd02(shp_lc_ctrl_04,		reg_lc_coring_gain_t_b, pp->shp_ee_2k[20],\
															reg_lc_coring_gain_t_w, pp->shp_ee_2k[21]);
				PE_SR_2K_SHP_O20_QRd02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	pp->shp_ee_2k[22],\
															reg_dctp_coring_gain_t_w,	pp->shp_ee_2k[23]);
				PE_SR_2K_SHP_O20_QRd02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	pp->shp_ee_2k[24],\
															reg_tgen_coring_gain_t_w,	pp->shp_ee_2k[25]);
				PE_SR_2K_SHP_O20_QRd02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	pp->shp_ee_2k[26],\
															reg_nntg_coring_gain_t_w,	pp->shp_ee_2k[27]);
				pd = pp->shp_ee_2k;
				PE_SHP_HW_O20_DBG_PRINT("get[%d] : shp_ee_2k\n"
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
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetSre2KDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_DE_T *pp=(LX_PE_SHP_SR2K_DE_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_de_2k;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_de_2k\n"
			"shp_de_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				#ifndef PE_HW_O20_PROTECT_OVERLAP_SETTINGS
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, GET_BITS(pp->shp_de_2k[0],0,7),\
																reg_mp_coring_gain_t_w, GET_BITS(pp->shp_de_2k[1],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, GET_BITS(pp->shp_de_2k[2],0,7),\
																reg_sp_coring_gain_t_w, GET_BITS(pp->shp_de_2k[3],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[4],0,7),\
																reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[5],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, GET_BITS(pp->shp_de_2k[6],0,7),\
																reg_lc_coring_gain_t_w, GET_BITS(pp->shp_de_2k[7],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_dctp_ctrl_1f,	reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[8],0,7),\
																reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[9],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_tgen_ctrl_0b,	reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[10],0,7),\
																reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[11],0,7));
				PE_SHP_HW_O20_SR_2K_SHP_WR02(shp_nntg_ctrl_10,	reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[12],0,7),\
																reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[13],0,7));
				#else
				PE_SR_2K_SHP_O20_QWr02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, 	GET_BITS(pp->shp_de_2k[0],0,7),\
														reg_mp_coring_gain_t_w, 	GET_BITS(pp->shp_de_2k[1],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, 	GET_BITS(pp->shp_de_2k[2],0,7),\
														reg_sp_coring_gain_t_w, 	GET_BITS(pp->shp_de_2k[3],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[4],0,7),\
														reg_pti_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[5],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, 	GET_BITS(pp->shp_de_2k[6],0,7),\
														reg_lc_coring_gain_t_w, 	GET_BITS(pp->shp_de_2k[7],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[8],0,7),\
														reg_dctp_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[9],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[10],0,7),\
														reg_tgen_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[11],0,7));
				PE_SR_2K_SHP_O20_QWr02(shp_nntg_ctrl_10,reg_nntg_coring_gain_t_b,	GET_BITS(pp->shp_de_2k[12],0,7),\
														reg_nntg_coring_gain_t_w,	GET_BITS(pp->shp_de_2k[13],0,7));
				#endif
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * get sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for O20X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetSre2KDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			UINT8 *pd;
			LX_PE_SHP_SR2K_DE_T *pp=(LX_PE_SHP_SR2K_DE_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			pd = pp->shp_de_2k;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SR_2K_SHP_O20_QRd02(shp_mp_ctrl_0c,	reg_mp_coring_gain_t_b, 	pp->shp_de_2k[0],\
														reg_mp_coring_gain_t_w, 	pp->shp_de_2k[1]);
				PE_SR_2K_SHP_O20_QRd02(shp_sp_ctrl_0c,	reg_sp_coring_gain_t_b, 	pp->shp_de_2k[2],\
														reg_sp_coring_gain_t_w, 	pp->shp_de_2k[3]);
				PE_SR_2K_SHP_O20_QRd02(shp_pti_ctrl_03,	reg_pti_coring_gain_t_b,	pp->shp_de_2k[4],\
														reg_pti_coring_gain_t_w,	pp->shp_de_2k[5]);
				PE_SR_2K_SHP_O20_QRd02(shp_lc_ctrl_04,	reg_lc_coring_gain_t_b, 	pp->shp_de_2k[6],\
														reg_lc_coring_gain_t_w, 	pp->shp_de_2k[7]);
				PE_SR_2K_SHP_O20_QRd02(shp_dctp_ctrl_1f,reg_dctp_coring_gain_t_b,	pp->shp_de_2k[8],\
														reg_dctp_coring_gain_t_w,	pp->shp_de_2k[9]);
				PE_SR_2K_SHP_O20_QRd02(shp_tgen_ctrl_0b,reg_tgen_coring_gain_t_b,	pp->shp_de_2k[10],\
														reg_tgen_coring_gain_t_w,	pp->shp_de_2k[11]);
				PE_SR_2K_SHP_O20_QRd02(shp_nntg_ctrl_10,reg_nntg_coring_gain_t_b,	pp->shp_de_2k[12],\
														reg_nntg_coring_gain_t_w,	pp->shp_de_2k[13]);
				PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_de_2k\n"
				"shp_de_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_de_2k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13]);
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}
/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_O20_SetSre2KSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_SR2K_SQM_CMN_T *ctrl_param =(LX_PE_SHP_SR2K_SQM_CMN_T *)pstParams;
			LX_PE_SHP_SR2K_SQM2_CMN_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o20_trace)
			{
				UINT32 *pd = pp->shp_ui_sqm_2k;
				PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_sqm_2k\n"
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
				ret = PE_SHP_HW_O20_DownloadShp2KSqmCmnUserDb((void *)pp);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_SHP_HW_O20_DownloadShp2KSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_O20_SetSre2KSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_SR2K_SQM_DETAIL_T *ctrl_param =(LX_PE_SHP_SR2K_SQM_DETAIL_T *)pstParams;
			LX_PE_SHP_SR2K_SQM2_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o20_trace)
			{
				UINT32 *pd = pp->shp_sqm_cmn_2k;
				PE_SHP_HW_O20_DBG_PRINT("[%d]shp_sqm_cmn_2k:%d\n", pp->win_id, pp->shp_sqm____val);
				PE_SHP_HW_O20_DBG_PRINT( \
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
				ret = PE_SHP_HW_O20_DownloadShp2KSqmDetailUserDb((void *)pp);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_SHP_HW_O20_DownloadShp2KSqmDetailUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_O20_SetSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_RE_SQM_CMN_T *ctrl_param =(LX_PE_SHP_RE_SQM_CMN_T *)pstParams;
			LX_PE_SHP_RE_SQM2_CMN_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o20_trace)
			{
				UINT32 *pd = pp->shp_ui_sqm_vsd;
				PE_SHP_HW_O20_DBG_PRINT("[%d]shp_ui_sqm_2k:%d\n", pp->win_id, pp->shp_sqm____val);
				PE_SHP_HW_O20_DBG_PRINT( \
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
				ret = PE_SHP_HW_O20_DownloadShpSqmCmnUserDb((void *)pp);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_SHP_HW_O20_DownloadShpSqmCmnUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * set tnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_SHP_HW_O20_SetSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_RE_SQM_DETAIL_T *ctrl_param =(LX_PE_SHP_RE_SQM_DETAIL_T *)pstParams;
			LX_PE_SHP_RE_SQM2_DETAIL_T *pp = ctrl_param->data;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o20_trace)
			{
				UINT32 *pd = pp->shp_sqm_cmn_vsd;
				PE_SHP_HW_O20_DBG_PRINT("[%d]shp_sqm_cmn_vsd:%d\n", pp->win_id, pp->shp_sqm_____val);
				PE_SHP_HW_O20_DBG_PRINT( \
				"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
				"shp_sqm_cmn_vsd[50]0x%08X\n",\
				pd[0],  pd[1],  pd[2],  pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
				pd[10],pd[11],  pd[12],  pd[13], pd[14],  pd[15],  pd[16],  pd[17], pd[18],  pd[19], \
				pd[20],pd[21],  pd[22],  pd[23], pd[24],  pd[25],  pd[26],  pd[27], pd[28],  pd[29],\
				pd[30],pd[31],  pd[32],  pd[33], pd[34],  pd[35],  pd[36],  pd[37], pd[38],  pd[39],\
				pd[40],pd[41],  pd[42],  pd[43], pd[34],  pd[45],  pd[46],  pd[47], pd[48],  pd[49],\
				pd[50]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* download tnr user db */
				ret = PE_SHP_HW_O20_DownloadShpSqmDetailUserDb((void *)pp);
				PE_SHP_HW_O20_CHECK_CODE(ret, break, \
					"[%s,%d] PE_SHP_HW_O20_DownloadShpSqmDetailUserDb() error.\n",__F__,__L__);
			}
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}



/**
 * set pbl(pre blur dnr) apply
 *
 * @param   *pCfg [in] PE_TSK_O20_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_O20_SetPblApply(PE_TSK_O20_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	#ifdef PE_SHP_HW_O20_CROSS_PAT_DETECT
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
		if(PE_KDRV_VER_O20)
		{
			if(g_pe_inf_o20_vr360_mode)
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
			ret = PE_INF_O20_GetCurDispInfSettings(LX_PE_WIN_0, &cur0_inf);
			ret = PE_HST_HW_O20_GetSrcHistoBin(0, histo_bin, 0);//Y
			ret = PE_HST_HW_O20_GetSrcHistoBin(0, s_bin, 7);//S
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
				data_shp = _g_pe_srs_hw_param_data_o20.reg_dflt.data->shp_der_ctrl_00.reg_derh_th_gain_edge;
				shp_bypass = 0x0;
			}
			if(_g_shp_hw_o20_trace)
			{
				if(count>32)
				{
					PE_SHP_HW_O20_DBG_PRINT("s: %d\n",(s_bin[0]+s_bin[1]) );
#ifdef INCLUDE_KDRV_AFE
					PE_SHP_HW_O20_DBG_PRINT("pattern :%d, static :%d, colorbar : %d\n", \
							is_pattern, g_CVD_Pattern_Detection_t.static_pattern_found,g_CVD_Pattern_Detection_t.pattern_found );
#endif
					PE_SHP_HW_O20_DBG_PRINT("low :%d, mid :%d, high : %d\n",hist_low, hist_mid,hist_high );
					PE_SHP_HW_O20_DBG_PRINT("cross_hat :%d, cross_hat_inv :%d, cross : %d, cross_inv : %d\n"\
							,f_cross_hat_pattern, f_cross_hat_pattern_inv,f_cross_pattern, f_cross_pattern_inv);
					PE_SHP_HW_O20_DBG_PRINT("pre :%d, curr :%d\n", data_shp,_g_pre_data_shp );
					PE_SHP_HW_O20_DBG_PRINT("bypass pre :%d, curr :%d\n", shp_bypass,_g_pre_shp_bypass );
					count=0;
				}
				count++;
			}
			if(data_shp != _g_pre_data_shp)
			{
				PE_SHP_HW_O20_SR_SHP_WR01(shp_der_ctrl_00, reg_derh_th_gain_edge, GET_BITS(data_shp, 0,6));
				_g_pre_data_shp = data_shp;
			}
			if(shp_bypass !=GET_BITS(_g_pre_shp_bypass,0,1) )
			{
				PE_SHP_O20_QWr01(shp_core_ctrl_00,	reg_top_core_bypass,		GET_BITS(shp_bypass,0,1));
				_g_pre_shp_bypass = shp_bypass;
			}
			
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_DownloadSclDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		/* t12_m **************************************************************/
		ret = PE_SHP_HW_O20_DownloadScl12tMainDb();
		PE_SHP_HW_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_O20_DownloadScl12tMainDb() error.\n",__F__,__L__);
		/* t08_m **************************************************************/
		ret = PE_SHP_HW_O20_DownloadScl08tMainDb();
		PE_SHP_HW_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_O20_DownloadScl08tMainDb() error.\n",__F__,__L__);
		/* t04_m **************************************************************/
		ret = PE_SHP_HW_O20_DownloadScl04tMainDb();
		PE_SHP_HW_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_O20_DownloadScl04tMainDb() error.\n",__F__,__L__);
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_O20_DownloadScl12tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, i = 0;
	UINT32 sec_typ_1212 = 0, sec_typ_1206 = 0,sec_typ_1204 = 0, sec_typ_1202 = 0;
	UINT32 base_line_1212[PE_DDR_O20_1212T_FLT_NUM];
	UINT32 base_line_1206[PE_DDR_O20_1206T_FLT_NUM];
	UINT32 base_line_1204[PE_DDR_O20_1204T_FLT_NUM];
	UINT32 base_line_1202[PE_DDR_O20_1202T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
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
		if (PE_KDRV_VER_O20)
		{
			/*1. 1212  */
			sec_typ_1212 = PE_DDR_O20_SEC_SCL_1212T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1212].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1212].header.sec_type  = sec_typ_1212;
			p_shdw_db->sec_d[sec_typ_1212].header.item_num  = PE_DDR_O20_1212T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1212].header.item_size = PE_DDR_O20_SCL_12T_FLT_SIZE;
			p_phys_db->t1212.header.version   = p_shdw_db->sec_d[sec_typ_1212].header.version;
			p_phys_db->t1212.header.sec_type  = p_shdw_db->sec_d[sec_typ_1212].header.sec_type;
			p_phys_db->t1212.header.item_num  = p_shdw_db->sec_d[sec_typ_1212].header.item_num;
			p_phys_db->t1212.header.item_size = p_shdw_db->sec_d[sec_typ_1212].header.item_size;

			/* data */
			size = (PE_DDR_O20_1212T_FLT_NUM * PE_DDR_O20_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1212] = \
				p_shdw_db->top_h.sec_base[sec_typ_1212-1]+p_shdw_db->top_h.sec_size[sec_typ_1212-1];
			p_shdw_db->top_h.sec_size[sec_typ_1212] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1212] = p_shdw_db->top_h.sec_base[sec_typ_1212];
			p_phys_db->top_h.sec_size[sec_typ_1212] = p_shdw_db->top_h.sec_size[sec_typ_1212];
			p_shdw_db->sec_d[sec_typ_1212].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1212] + sizeof(PE_DDR_O20_HEADER_T);


			/*2. 1206*/
			sec_typ_1206 = PE_DDR_O20_SEC_SCL_1206T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1206].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1206].header.sec_type  = sec_typ_1206;
			p_shdw_db->sec_d[sec_typ_1206].header.item_num  = PE_DDR_O20_1206T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1206].header.item_size = PE_DDR_O20_SCL_12T_FLT_SIZE;
			p_phys_db->t1206.header.version   = p_shdw_db->sec_d[sec_typ_1206].header.version;
			p_phys_db->t1206.header.sec_type  = p_shdw_db->sec_d[sec_typ_1206].header.sec_type;
			p_phys_db->t1206.header.item_num  = p_shdw_db->sec_d[sec_typ_1206].header.item_num;
			p_phys_db->t1206.header.item_size = p_shdw_db->sec_d[sec_typ_1206].header.item_size;
			/* data */
			size = (PE_DDR_O20_1206T_FLT_NUM * PE_DDR_O20_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1206] = \
				p_shdw_db->top_h.sec_base[sec_typ_1206-1]+p_shdw_db->top_h.sec_size[sec_typ_1206-1];
			p_shdw_db->top_h.sec_size[sec_typ_1206] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1206] = p_shdw_db->top_h.sec_base[sec_typ_1206];
			p_phys_db->top_h.sec_size[sec_typ_1206] = p_shdw_db->top_h.sec_size[sec_typ_1206];
			p_shdw_db->sec_d[sec_typ_1206].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1206] + sizeof(PE_DDR_O20_HEADER_T);

			/*3. 1204*/
			sec_typ_1204 = PE_DDR_O20_SEC_SCL_1204T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1204].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1204].header.sec_type  = sec_typ_1204;
			p_shdw_db->sec_d[sec_typ_1204].header.item_num  = PE_DDR_O20_1204T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1204].header.item_size = PE_DDR_O20_SCL_12T_FLT_SIZE;
			p_phys_db->t1204.header.version   = p_shdw_db->sec_d[sec_typ_1204].header.version;
			p_phys_db->t1204.header.sec_type  = p_shdw_db->sec_d[sec_typ_1204].header.sec_type;
			p_phys_db->t1204.header.item_num  = p_shdw_db->sec_d[sec_typ_1204].header.item_num;
			p_phys_db->t1204.header.item_size = p_shdw_db->sec_d[sec_typ_1204].header.item_size;
			/* data */
			size = (PE_DDR_O20_1204T_FLT_NUM * PE_DDR_O20_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1204] = \
				p_shdw_db->top_h.sec_base[sec_typ_1204-1]+p_shdw_db->top_h.sec_size[sec_typ_1204-1];
			p_shdw_db->top_h.sec_size[sec_typ_1204] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1204] = p_shdw_db->top_h.sec_base[sec_typ_1204];
			p_phys_db->top_h.sec_size[sec_typ_1204] = p_shdw_db->top_h.sec_size[sec_typ_1204];
			p_shdw_db->sec_d[sec_typ_1204].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1204] + sizeof(PE_DDR_O20_HEADER_T);

			/*4. 1202*/
			sec_typ_1202 = PE_DDR_O20_SEC_SCL_1202T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1202].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1202].header.sec_type  = sec_typ_1202;
			p_shdw_db->sec_d[sec_typ_1202].header.item_num  = PE_DDR_O20_1202T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1202].header.item_size = PE_DDR_O20_SCL_12T_FLT_SIZE;
			p_phys_db->t1202.header.version   = p_shdw_db->sec_d[sec_typ_1202].header.version;
			p_phys_db->t1202.header.sec_type  = p_shdw_db->sec_d[sec_typ_1202].header.sec_type;
			p_phys_db->t1202.header.item_num  = p_shdw_db->sec_d[sec_typ_1202].header.item_num;
			p_phys_db->t1202.header.item_size = p_shdw_db->sec_d[sec_typ_1202].header.item_size;
			/* data */
			size = (PE_DDR_O20_1202T_FLT_NUM * PE_DDR_O20_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1202] = \
				p_shdw_db->top_h.sec_base[sec_typ_1202-1]+p_shdw_db->top_h.sec_size[sec_typ_1202-1];
			p_shdw_db->top_h.sec_size[sec_typ_1202] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1202] = p_shdw_db->top_h.sec_base[sec_typ_1202];
			p_phys_db->top_h.sec_size[sec_typ_1202] = p_shdw_db->top_h.sec_size[sec_typ_1202];
			p_shdw_db->sec_d[sec_typ_1202].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1202] + sizeof(PE_DDR_O20_HEADER_T);

			/* wr ddr */
			base_line_1212[0] = 0;
			base_line_1206[0] = 0;
			base_line_1204[0] = 0;
			base_line_1202[0] = 0;
			for (i=1; i<PE_DDR_O20_1212T_FLT_NUM; i++)
			{
				base_line_1212[i] = base_line_1212[i-1]+PE_DDR_O20_SCL_12T_FLT_SIZE;
			}
			for (i=1; i<PE_DDR_O20_1206T_FLT_NUM; i++)
			{
				base_line_1206[i] = base_line_1206[i-1]+PE_DDR_O20_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_O20_1204T_FLT_NUM; i++)
			{
				base_line_1204[i] = base_line_1204[i-1]+PE_DDR_O20_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_O20_1202T_FLT_NUM; i++)
			{
				base_line_1202[i] = base_line_1202[i-1]+PE_DDR_O20_SCL_12T_FLT_SIZE;;
			}
			for (i=0; i<PE_DDR_O20_SCL_12T_FLT_SIZE; i++)
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
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ_1212), p_shdw_db->top_h.sec_base[sec_typ_1212]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ_1206), p_shdw_db->top_h.sec_base[sec_typ_1206]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ_1204), p_shdw_db->top_h.sec_base[sec_typ_1204]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ_1202), p_shdw_db->top_h.sec_base[sec_typ_1202]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_O20_DownloadScl08tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, i = 0, sec_typ_0804 = 0;
	UINT32 base_line_0804[PE_DDR_O20_0804T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_t08_f_data = p_phys_db->t0804.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t08_f_data);
		if (PE_KDRV_VER_O20)
		{
			/*1. 8t full */
			sec_typ_0804 = PE_DDR_O20_SEC_SCL_0804T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0804].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0804].header.sec_type  = sec_typ_0804;
			p_shdw_db->sec_d[sec_typ_0804].header.item_num  = PE_DDR_O20_0804T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0804].header.item_size = PE_DDR_O20_SCL_08T_FLT_SIZE;
			p_phys_db->t0804.header.version   = p_shdw_db->sec_d[sec_typ_0804].header.version;
			p_phys_db->t0804.header.sec_type  = p_shdw_db->sec_d[sec_typ_0804].header.sec_type;
			p_phys_db->t0804.header.item_num  = p_shdw_db->sec_d[sec_typ_0804].header.item_num;
			p_phys_db->t0804.header.item_size = p_shdw_db->sec_d[sec_typ_0804].header.item_size;
			/* data */
			size = (PE_DDR_O20_0804T_FLT_NUM * PE_DDR_O20_SCL_08T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0804] = \
				p_shdw_db->top_h.sec_base[sec_typ_0804-1]+p_shdw_db->top_h.sec_size[sec_typ_0804-1];
			p_shdw_db->top_h.sec_size[sec_typ_0804] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0804] = p_shdw_db->top_h.sec_base[sec_typ_0804];
			p_phys_db->top_h.sec_size[sec_typ_0804] = p_shdw_db->top_h.sec_size[sec_typ_0804];
			p_shdw_db->sec_d[sec_typ_0804].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0804] + sizeof(PE_DDR_O20_HEADER_T);

			/* wr ddr */
			base_line_0804[0] = 0;
			for (i=1; i<PE_DDR_O20_0804T_FLT_NUM; i++)
			{
				base_line_0804[i] = base_line_0804[i-1]+PE_DDR_O20_SCL_08T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_O20_SCL_08T_FLT_SIZE; i++)
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
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ_0804), p_shdw_db->top_h.sec_base[sec_typ_0804]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_O20_DownloadScl04tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, i = 0;
	UINT32 sec_typ_0404 = 0, sec_typ_0402 = 0;
	UINT32 base_line_0404[PE_DDR_O20_0404T_FLT_NUM];
	UINT32 base_line_0402[PE_DDR_O20_0402T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_t0404_data = p_phys_db->t0404.data;
	volatile UINT32 *p_t0402_data = p_phys_db->t0402.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t0404_data);
		CHECK_KNULL(p_t0402_data);
		if (PE_KDRV_VER_O20)
		{
			/*1. 404t */
			sec_typ_0404 = PE_DDR_O20_SEC_SCL_0404T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0404].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0404].header.sec_type  = sec_typ_0404;
			p_shdw_db->sec_d[sec_typ_0404].header.item_num  = PE_DDR_O20_0404T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0404].header.item_size = PE_DDR_O20_SCL_04T_FLT_SIZE;
			p_phys_db->t0404.header.version   = p_shdw_db->sec_d[sec_typ_0404].header.version;
			p_phys_db->t0404.header.sec_type  = p_shdw_db->sec_d[sec_typ_0404].header.sec_type;
			p_phys_db->t0404.header.item_num  = p_shdw_db->sec_d[sec_typ_0404].header.item_num;
			p_phys_db->t0404.header.item_size = p_shdw_db->sec_d[sec_typ_0404].header.item_size;
			/* data */
			size = (PE_DDR_O20_0404T_FLT_NUM * PE_DDR_O20_SCL_04T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0404] = \
				p_shdw_db->top_h.sec_base[sec_typ_0404-1]+p_shdw_db->top_h.sec_size[sec_typ_0404-1];
			p_shdw_db->top_h.sec_size[sec_typ_0404] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0404] = p_shdw_db->top_h.sec_base[sec_typ_0404];
			p_phys_db->top_h.sec_size[sec_typ_0404] = p_shdw_db->top_h.sec_size[sec_typ_0404];
			p_shdw_db->sec_d[sec_typ_0404].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0404] + sizeof(PE_DDR_O20_HEADER_T);

			/*2. 402t  */
			sec_typ_0402 = PE_DDR_O20_SEC_SCL_0402T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0402].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0402].header.sec_type  = sec_typ_0402;
			p_shdw_db->sec_d[sec_typ_0402].header.item_num  = PE_DDR_O20_0402T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0402].header.item_size = PE_DDR_O20_SCL_04T_FLT_SIZE;
			p_phys_db->t0402.header.version   = p_shdw_db->sec_d[sec_typ_0402].header.version;
			p_phys_db->t0402.header.sec_type  = p_shdw_db->sec_d[sec_typ_0402].header.sec_type;
			p_phys_db->t0402.header.item_num  = p_shdw_db->sec_d[sec_typ_0402].header.item_num;
			p_phys_db->t0402.header.item_size = p_shdw_db->sec_d[sec_typ_0402].header.item_size;
			/* data */
			size = (PE_DDR_O20_0402T_FLT_NUM * PE_DDR_O20_SCL_04T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0402] = \
				p_shdw_db->top_h.sec_base[sec_typ_0402-1]+p_shdw_db->top_h.sec_size[sec_typ_0402-1];
			p_shdw_db->top_h.sec_size[sec_typ_0402] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0402] = p_shdw_db->top_h.sec_base[sec_typ_0402];
			p_phys_db->top_h.sec_size[sec_typ_0402] = p_shdw_db->top_h.sec_size[sec_typ_0402];
			p_shdw_db->sec_d[sec_typ_0402].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0402] + sizeof(PE_DDR_O20_HEADER_T);
			/* wr ddr */
			base_line_0404[0] = 0;
			for (i=1; i<PE_DDR_O20_0404T_FLT_NUM; i++)
			{
				base_line_0404[i] = base_line_0404[i-1]+PE_DDR_O20_SCL_04T_FLT_SIZE;
			}
			base_line_0402[0] = 0;
			for (i=1; i<PE_DDR_O20_0402T_FLT_NUM; i++)
			{
				base_line_0402[i] = base_line_0402[i-1]+PE_DDR_O20_SCL_04T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_O20_SCL_04T_FLT_SIZE; i++)
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
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ_0404), p_shdw_db->top_h.sec_base[sec_typ_0404]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ_0402), p_shdw_db->top_h.sec_base[sec_typ_0402]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * set Psp
 * - use input struct LX_PE_SHP_PSP_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_SetPspCtrl(LX_PE_SHP_PSP_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_PSP_T *pp = pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_HW_O20_DBG_PRINT("PSP ctrl: iir_en:%d, psp_en:%d, chrm_protect_en:%d\n"\
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
				PE_SHP_PSP_O20_QWr02(reg_perspect_gain_ctrl_0, 	iir_en, GET_BITS(pp->iir_en,0,1),\
																iir_gain, GET_BITS(pp->iir_gain,0,8));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_00, 		reg_psp_en, 				GET_BITS(pp->psp_en,0,1),\
															reg_chroma_protection_en, 	GET_BITS(pp->chroma_protection_en,0,1));
				PE_SHP_PSP_O20_QWr01(reg_psp_ctrl_01, 		reg_psp_map_master_gain, 	GET_BITS(pp->map_master_gain,0,8));
																
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_02, 		reg_cb_offset_gain, GET_BITS(pp->cb_offset_gain,0,10),\
															reg_cr_offset_gain, GET_BITS(pp->cr_offset_gain,0,10));
				PE_SHP_PSP_O20_QWr04(reg_perspect_lut_x_3, 	reg_position_lut_x_0, GET_BITS(pp->position_lut_x[0],0,8),\
															reg_position_lut_x_1, GET_BITS(pp->position_lut_x[1],0,8),\
															reg_position_lut_x_2, GET_BITS(pp->position_lut_x[2],0,8),\
															reg_position_lut_x_3, GET_BITS(pp->position_lut_x[3],0,8));
				PE_SHP_PSP_O20_QWr04(reg_perspect_lut_x_2, 	reg_position_lut_x_4, GET_BITS(pp->position_lut_x[4],0,8),\
															reg_position_lut_x_5, GET_BITS(pp->position_lut_x[5],0,8),\
															reg_position_lut_x_6, GET_BITS(pp->position_lut_x[6],0,8),\
															reg_position_lut_x_7, GET_BITS(pp->position_lut_x[7],0,8));
				PE_SHP_PSP_O20_QWr04(reg_perspect_lut_x_1, 	reg_position_lut_x_8, GET_BITS(pp->position_lut_x[8],0,8),\
															reg_position_lut_x_9, GET_BITS(pp->position_lut_x[9],0,8),\
															reg_position_lut_x_10, GET_BITS(pp->position_lut_x[10],0,8),\
															reg_position_lut_x_11, GET_BITS(pp->position_lut_x[11],0,8));
				PE_SHP_PSP_O20_QWr04(reg_perspect_lut_x_0, 	reg_position_lut_x_12, GET_BITS(pp->position_lut_x[12],0,8),\
															reg_position_lut_x_13, GET_BITS(pp->position_lut_x[13],0,8),\
															reg_position_lut_x_14, GET_BITS(pp->position_lut_x[14],0,8),\
															reg_position_lut_x_15, GET_BITS(pp->position_lut_x[15],0,8));
				
				PE_SHP_PSP_O20_QWr04(reg_perspect_lut_y_3, 	reg_position_lut_y_0, GET_BITS(pp->position_lut_y[0],0,8),\
															reg_position_lut_y_1, GET_BITS(pp->position_lut_y[1],0,8),\
															reg_position_lut_y_2, GET_BITS(pp->position_lut_y[2],0,8),\
															reg_position_lut_y_3, GET_BITS(pp->position_lut_y[3],0,8));
				PE_SHP_PSP_O20_QWr04(reg_perspect_lut_y_2, 	reg_position_lut_y_4, GET_BITS(pp->position_lut_y[4],0,8),\
															reg_position_lut_y_5, GET_BITS(pp->position_lut_y[5],0,8),\
															reg_position_lut_y_6, GET_BITS(pp->position_lut_y[6],0,8),\
															reg_position_lut_y_7, GET_BITS(pp->position_lut_y[7],0,8));
				PE_SHP_PSP_O20_QWr04(reg_perspect_lut_y_1, 	reg_position_lut_y_8,  GET_BITS(pp->position_lut_y[8],0,8),\
															reg_position_lut_y_9,  GET_BITS(pp->position_lut_y[9],0,8),\
															reg_position_lut_y_10, GET_BITS(pp->position_lut_y[10],0,8),\
															reg_position_lut_y_11, GET_BITS(pp->position_lut_y[11],0,8));
				PE_SHP_PSP_O20_QWr04(reg_perspect_lut_y_0, 	reg_position_lut_y_12, GET_BITS(pp->position_lut_y[12],0,8),\
															reg_position_lut_y_13, GET_BITS(pp->position_lut_y[13],0,8),\
															reg_position_lut_y_14, GET_BITS(pp->position_lut_y[14],0,8),\
															reg_position_lut_y_15, GET_BITS(pp->position_lut_y[15],0,8));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_05, 	reg_psp_lut_x0, GET_BITS(pp->psp_lut_x[0],0,10),\
														reg_psp_lut_y0, GET_BITS(pp->psp_lut_y[0],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_06, 	reg_psp_lut_x1, GET_BITS(pp->psp_lut_x[1],0,10),\
														reg_psp_lut_y1, GET_BITS(pp->psp_lut_y[1],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_07, 	reg_psp_lut_x2, GET_BITS(pp->psp_lut_x[2],0,10),\
														reg_psp_lut_y2, GET_BITS(pp->psp_lut_y[2],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_08, 	reg_psp_lut_x3, GET_BITS(pp->psp_lut_x[3],0,10),\
														reg_psp_lut_y3, GET_BITS(pp->psp_lut_y[3],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_09, 	reg_psp_lut_x4, GET_BITS(pp->psp_lut_x[4],0,10),\
														reg_psp_lut_y4, GET_BITS(pp->psp_lut_y[4],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_10, 	reg_psp_lut_x5, GET_BITS(pp->psp_lut_x[5],0,10),\
														reg_psp_lut_y5, GET_BITS(pp->psp_lut_y[5],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_11, 	reg_psp_lut_x6, GET_BITS(pp->psp_lut_x[6],0,10),\
														reg_psp_lut_y6, GET_BITS(pp->psp_lut_y[6],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_12, 	reg_psp_lut_x7, GET_BITS(pp->psp_lut_x[7],0,10),\
														reg_psp_lut_y7, GET_BITS(pp->psp_lut_y[7],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_13, 	reg_psp_lut_x8,  GET_BITS(pp->psp_lut_x[8],0,10),\
														reg_psp_lut_y8,  GET_BITS(pp->psp_lut_y[8],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_14, 	reg_psp_lut_x9,  GET_BITS(pp->psp_lut_x[9],0,10),\
														reg_psp_lut_y9,  GET_BITS(pp->psp_lut_y[9],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_15, 	reg_psp_lut_x10, GET_BITS(pp->psp_lut_x[10],0,10),\
														reg_psp_lut_y10, GET_BITS(pp->psp_lut_y[10],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_16, 	reg_psp_lut_x11, GET_BITS(pp->psp_lut_x[11],0,10),\
														reg_psp_lut_y11, GET_BITS(pp->psp_lut_y[11],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_17, 	reg_psp_lut_x12, GET_BITS(pp->psp_lut_x[12],0,10),\
														reg_psp_lut_y12, GET_BITS(pp->psp_lut_y[12],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_18, 	reg_psp_lut_x13, GET_BITS(pp->psp_lut_x[13],0,10),\
														reg_psp_lut_y13, GET_BITS(pp->psp_lut_y[13],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_19, 	reg_psp_lut_x14, GET_BITS(pp->psp_lut_x[14],0,10),\
														reg_psp_lut_y14, GET_BITS(pp->psp_lut_y[14],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_20, 	reg_psp_lut_x15, GET_BITS(pp->psp_lut_x[15],0,10),\
														reg_psp_lut_y15, GET_BITS(pp->psp_lut_y[15],0,10));
				PE_SHP_PSP_O20_QWr02(reg_psp_ctrl_21, 	reg_psp_lut_x16, GET_BITS(pp->psp_lut_x[16],0,10),\
														reg_psp_lut_y16, GET_BITS(pp->psp_lut_y[16],0,10));
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

/**
 * get Psp
 * - use input struct LX_PE_SHP_PSP_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_O20_GetPspCtrl(LX_PE_SHP_PSP_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O20_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_PSP_T *pp = pstParams;
			PE_CHECK_WINID(pp->win_id);
			
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_SHP_PSP_O20_QRd02(reg_perspect_gain_ctrl_0, 	iir_en, 	pp->iir_en,\
																iir_gain, 	pp->iir_gain);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_00, 		reg_psp_en, 				pp->psp_en,\
															reg_chroma_protection_en, 	pp->chroma_protection_en);
				PE_SHP_PSP_O20_QRd01(reg_psp_ctrl_01, 		reg_psp_map_master_gain, 	pp->map_master_gain);
																
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_02, 		reg_cb_offset_gain, 	pp->cb_offset_gain,\
															reg_cr_offset_gain, 	pp->cr_offset_gain);
				PE_SHP_PSP_O20_QRd04(reg_perspect_lut_x_3, 	reg_position_lut_x_0, pp->position_lut_x[0],\
															reg_position_lut_x_1, pp->position_lut_x[1],\
															reg_position_lut_x_2, pp->position_lut_x[2],\
															reg_position_lut_x_3, pp->position_lut_x[3]);
				PE_SHP_PSP_O20_QRd04(reg_perspect_lut_x_2, 	reg_position_lut_x_4, pp->position_lut_x[4],\
															reg_position_lut_x_5, pp->position_lut_x[5],\
															reg_position_lut_x_6, pp->position_lut_x[6],\
															reg_position_lut_x_7, pp->position_lut_x[7]);
				PE_SHP_PSP_O20_QRd04(reg_perspect_lut_x_1, 	reg_position_lut_x_8,  pp->position_lut_x[8],\
															reg_position_lut_x_9,  pp->position_lut_x[9],\
															reg_position_lut_x_10, pp->position_lut_x[10],\
															reg_position_lut_x_11, pp->position_lut_x[11]);
				PE_SHP_PSP_O20_QRd04(reg_perspect_lut_x_0, 	reg_position_lut_x_12, pp->position_lut_x[12],\
															reg_position_lut_x_13, pp->position_lut_x[13],\
															reg_position_lut_x_14, pp->position_lut_x[14],\
															reg_position_lut_x_15, pp->position_lut_x[15]);
				
				PE_SHP_PSP_O20_QRd04(reg_perspect_lut_y_3, 	reg_position_lut_y_0, pp->position_lut_y[0],\
															reg_position_lut_y_1, pp->position_lut_y[1],\
															reg_position_lut_y_2, pp->position_lut_y[2],\
															reg_position_lut_y_3, pp->position_lut_y[3]);
				PE_SHP_PSP_O20_QRd04(reg_perspect_lut_y_2, 	reg_position_lut_y_4, pp->position_lut_y[4],\
															reg_position_lut_y_5, pp->position_lut_y[5],\
															reg_position_lut_y_6, pp->position_lut_y[6],\
															reg_position_lut_y_7, pp->position_lut_y[7]);
				PE_SHP_PSP_O20_QRd04(reg_perspect_lut_y_1, 	reg_position_lut_y_8,  pp->position_lut_y[8],\
															reg_position_lut_y_9,  pp->position_lut_y[9],\
															reg_position_lut_y_10, pp->position_lut_y[10],\
															reg_position_lut_y_11, pp->position_lut_y[11]);
				PE_SHP_PSP_O20_QRd04(reg_perspect_lut_y_0, 	reg_position_lut_y_12, pp->position_lut_y[12],\
															reg_position_lut_y_13, pp->position_lut_y[13],\
															reg_position_lut_y_14, pp->position_lut_y[14],\
															reg_position_lut_y_15, pp->position_lut_y[15]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_05, 	reg_psp_lut_x0, pp->psp_lut_x[0],\
														reg_psp_lut_y0, pp->psp_lut_y[0]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_06, 	reg_psp_lut_x1, pp->psp_lut_x[1],\
														reg_psp_lut_y1, pp->psp_lut_y[1]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_07, 	reg_psp_lut_x2, pp->psp_lut_x[2],\
														reg_psp_lut_y2, pp->psp_lut_y[2]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_08, 	reg_psp_lut_x3, pp->psp_lut_x[3],\
														reg_psp_lut_y3, pp->psp_lut_y[3]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_09, 	reg_psp_lut_x4, pp->psp_lut_x[4],\
														reg_psp_lut_y4, pp->psp_lut_y[4]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_10, 	reg_psp_lut_x5, pp->psp_lut_x[5],\
														reg_psp_lut_y5, pp->psp_lut_y[5]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_11, 	reg_psp_lut_x6, pp->psp_lut_x[6],\
														reg_psp_lut_y6, pp->psp_lut_y[6]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_12, 	reg_psp_lut_x7, pp->psp_lut_x[7],\
														reg_psp_lut_y7, pp->psp_lut_y[7]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_13, 	reg_psp_lut_x8, pp->psp_lut_x[8],\
														reg_psp_lut_y8, pp->psp_lut_y[8]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_14, 	reg_psp_lut_x9, pp->psp_lut_x[9],\
														reg_psp_lut_y9, pp->psp_lut_y[9]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_15, 	reg_psp_lut_x10, pp->psp_lut_x[10],\
														reg_psp_lut_y10, pp->psp_lut_y[10]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_16, 	reg_psp_lut_x11, pp->psp_lut_x[11],\
														reg_psp_lut_y11, pp->psp_lut_y[11]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_17, 	reg_psp_lut_x12, pp->psp_lut_x[12],\
														reg_psp_lut_y12, pp->psp_lut_y[12]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_18, 	reg_psp_lut_x13, pp->psp_lut_x[13],\
														reg_psp_lut_y13, pp->psp_lut_y[13]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_19, 	reg_psp_lut_x14, pp->psp_lut_x[14],\
														reg_psp_lut_y14, pp->psp_lut_y[14]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_20, 	reg_psp_lut_x15, pp->psp_lut_x[15],\
														reg_psp_lut_y15, pp->psp_lut_y[15]);
				PE_SHP_PSP_O20_QRd02(reg_psp_ctrl_21, 	reg_psp_lut_x16, pp->psp_lut_x[16],\
														reg_psp_lut_y16, pp->psp_lut_y[16]);
				PE_SHP_HW_O20_DBG_PRINT("PSP ctrl: iir_en:%d, psp_en:%d, chrm_protect_en:%d\n"\
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
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_SetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_VSD_OBC2_CONT_T *pp=(LX_PE_VSD_OBC2_CONT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o20_trace)
			{
				PE_SHP_HW_O20_DBG_PRINT("[wid:%d] set: n"\
				"obj_fg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"obj_fg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"obj_bg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"obj_bg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"obj_sat_enable: 0x%02X, obj_ch_bst_enable:0x%02X \n"\
				"obj_yy_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_yy_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_cc_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_cc_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_cbst_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_cbst_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_fg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"face_fg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"face_bg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"face_bg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"face_sat_enable: 0x%02X, face_ch_bst_enable:0x%02X \n"\
				"face_yy_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_yy_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_cc_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_cc_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_cbst_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_cbst_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"
				"face_obj_lut_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_obj_lut_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_face_lut_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_face_lut_y: 0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id,\
				pp->obj_fg_gain_x[0],pp->obj_fg_gain_x[1],pp->obj_fg_gain_y[0],pp->obj_fg_gain_y[1], \
				pp->obj_bg_gain_x[0],pp->obj_bg_gain_x[1],pp->obj_bg_gain_y[0],pp->obj_bg_gain_y[1], \
				pp->obj_sat_enable, pp->obj_ch_bst_enable,\
				pp->obj_yy_lut_pts_x[0],pp->obj_yy_lut_pts_x[1],pp->obj_yy_lut_pts_x[2],pp->obj_yy_lut_pts_x[3],\
				pp->obj_yy_lut_pts_y[0],pp->obj_yy_lut_pts_y[1],pp->obj_yy_lut_pts_y[2],pp->obj_yy_lut_pts_y[3],\
				pp->obj_cc_lut_pts_x[0],pp->obj_cc_lut_pts_x[1],pp->obj_cc_lut_pts_x[2],pp->obj_cc_lut_pts_x[3],\
				pp->obj_cc_lut_pts_y[0],pp->obj_cc_lut_pts_y[1],pp->obj_cc_lut_pts_y[2],pp->obj_cc_lut_pts_y[3],\
				pp->obj_cbst_lut_pts_x[0],pp->obj_cbst_lut_pts_x[1],pp->obj_cbst_lut_pts_x[2],pp->obj_cbst_lut_pts_x[3],\
				pp->face_cbst_lut_pts_y[0],pp->face_cbst_lut_pts_y[1],pp->face_cbst_lut_pts_y[2],pp->face_cbst_lut_pts_y[3],\
				pp->face_fg_gain_x[0],pp->face_fg_gain_x[1],pp->face_fg_gain_y[0],pp->face_fg_gain_y[1], \
				pp->face_bg_gain_x[0],pp->face_bg_gain_x[1],pp->face_bg_gain_y[0],pp->face_bg_gain_y[1], \
				pp->face_sat_enable, pp->face_ch_bst_enable,\
				pp->face_yy_lut_pts_x[0],pp->face_yy_lut_pts_x[1],pp->face_yy_lut_pts_x[2],pp->face_yy_lut_pts_x[3],\
				pp->face_yy_lut_pts_y[0],pp->face_yy_lut_pts_y[1],pp->face_yy_lut_pts_y[2],pp->face_yy_lut_pts_y[3],\
				pp->face_cc_lut_pts_x[0],pp->face_cc_lut_pts_x[1],pp->face_cc_lut_pts_x[2],pp->face_cc_lut_pts_x[3],\
				pp->face_cc_lut_pts_y[0],pp->face_cc_lut_pts_y[1],pp->face_cc_lut_pts_y[2],pp->face_cc_lut_pts_y[3],\
				pp->face_cbst_lut_pts_x[0],pp->face_cbst_lut_pts_x[1],pp->face_cbst_lut_pts_x[2],pp->face_cbst_lut_pts_x[3],\
				pp->face_cbst_lut_pts_y[0],pp->face_cbst_lut_pts_y[1],pp->face_cbst_lut_pts_y[2],pp->face_cbst_lut_pts_y[3],\
				pp->face_obj_lut_x[0],pp->face_obj_lut_x[1],pp->face_obj_lut_x[2],pp->face_obj_lut_x[3],\
				pp->face_obj_lut_y[0],pp->face_obj_lut_y[1],pp->face_obj_lut_y[2],pp->face_obj_lut_y[3],\
				pp->obj_face_lut_x[0],pp->obj_face_lut_x[1],pp->obj_face_lut_x[2],pp->obj_face_lut_x[3],\
				pp->obj_face_lut_y[0],pp->obj_face_lut_y[1],pp->obj_face_lut_y[2],pp->obj_face_lut_y[3]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_HW_O20_RCE_O_WR04(reg_rce_objt_ctrl_19, 	reg_psp_gain_lut0_y0,	GET_BITS(pp->obj_fg_gain_y[0],0,8),\
																reg_psp_gain_lut0_x0,	GET_BITS(pp->obj_fg_gain_x[0],0,8),\
																reg_psp_gain_lut0_y1,	GET_BITS(pp->obj_fg_gain_y[1],0,8),\
																reg_psp_gain_lut0_x1,	GET_BITS(pp->obj_fg_gain_x[1],0,8));
				PE_VSD_HW_O20_RCE_O_WR04(reg_rce_objt_ctrl_20, 	reg_psp_gain_lut1_y0,	GET_BITS(pp->obj_bg_gain_y[0],0,8),\
																reg_psp_gain_lut1_x0,	GET_BITS(pp->obj_bg_gain_x[0],0,8),\
																reg_psp_gain_lut1_y1,	GET_BITS(pp->obj_bg_gain_y[1],0,8),\
																reg_psp_gain_lut1_x1,	GET_BITS(pp->obj_bg_gain_x[1],0,8));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_00,	reg_sat_gain_en,		GET_BITS(pp->obj_sat_enable,0,1),\
																reg_cbst_en,			GET_BITS(pp->obj_ch_bst_enable,0,1));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_21, 	reg_yy_lut_pts_x0,	GET_BITS(pp->obj_yy_lut_pts_x[0],0,10),\
																reg_yy_lut_pts_x1,	GET_BITS(pp->obj_yy_lut_pts_x[1],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_22, 	reg_yy_lut_pts_x2,	GET_BITS(pp->obj_yy_lut_pts_x[2],0,10),\
																reg_yy_lut_pts_x3,	GET_BITS(pp->obj_yy_lut_pts_x[3],0,10));
				PE_VSD_HW_O20_RCE_O_WR04(reg_rce_objt_ctrl_23, 	reg_yy_lut_pts_y0,	GET_BITS(pp->obj_yy_lut_pts_y[0],0,8),\
																reg_yy_lut_pts_y1,	GET_BITS(pp->obj_yy_lut_pts_y[1],0,8),\
																reg_yy_lut_pts_y2,	GET_BITS(pp->obj_yy_lut_pts_y[2],0,8),\
																reg_yy_lut_pts_y3,	GET_BITS(pp->obj_yy_lut_pts_y[3],0,8));
				PE_VSD_HW_O20_RCE_O_WR04(reg_rce_objt_ctrl_24, 	reg_cc_lut_pts_y0,	GET_BITS(pp->obj_cc_lut_pts_y[0],0,8),\
																reg_cc_lut_pts_x0,	GET_BITS(pp->obj_cc_lut_pts_x[0],0,8),\
																reg_cc_lut_pts_y1,	GET_BITS(pp->obj_cc_lut_pts_y[1],0,8),\
																reg_cc_lut_pts_x1,	GET_BITS(pp->obj_cc_lut_pts_x[1],0,8));
				PE_VSD_HW_O20_RCE_O_WR04(reg_rce_objt_ctrl_25, 	reg_cc_lut_pts_y2,	GET_BITS(pp->obj_cc_lut_pts_y[2],0,8),\
																reg_cc_lut_pts_x2,	GET_BITS(pp->obj_cc_lut_pts_x[2],0,8),\
																reg_cc_lut_pts_y3,	GET_BITS(pp->obj_cc_lut_pts_y[3],0,8),\
																reg_cc_lut_pts_x3,	GET_BITS(pp->obj_cc_lut_pts_x[3],0,8));
				PE_VSD_HW_O20_RCE_O_WR04(reg_rce_objt_ctrl_26, 	reg_cbst_lut_pts_y0,	GET_BITS(pp->obj_cbst_lut_pts_y[0],0,8),\
																reg_cbst_lut_pts_x0,	GET_BITS(pp->obj_cbst_lut_pts_x[0],0,8),\
																reg_cbst_lut_pts_y1,	GET_BITS(pp->obj_cbst_lut_pts_y[1],0,8),\
																reg_cbst_lut_pts_x1,	GET_BITS(pp->obj_cbst_lut_pts_x[1],0,8));
				PE_VSD_HW_O20_RCE_O_WR04(reg_rce_objt_ctrl_27, 	reg_cbst_lut_pts_y2,	GET_BITS(pp->obj_cbst_lut_pts_y[2],0,8),\
																reg_cbst_lut_pts_x2,	GET_BITS(pp->obj_cbst_lut_pts_x[2],0,8),\
																reg_cbst_lut_pts_y3,	GET_BITS(pp->obj_cbst_lut_pts_y[3],0,8),\
																reg_cbst_lut_pts_x3,	GET_BITS(pp->obj_cbst_lut_pts_x[3],0,8));

				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_19, 	reg_psp_gain_lut0_y0,	GET_BITS(pp->face_fg_gain_y[0],0,8),\
																reg_psp_gain_lut0_x0,	GET_BITS(pp->face_fg_gain_x[0],0,8),\
																reg_psp_gain_lut0_y1,	GET_BITS(pp->face_fg_gain_y[1],0,8),\
																reg_psp_gain_lut0_x1,	GET_BITS(pp->face_fg_gain_x[1],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_20, 	reg_psp_gain_lut1_y0,	GET_BITS(pp->face_bg_gain_y[0],0,8),\
																reg_psp_gain_lut1_x0,	GET_BITS(pp->face_bg_gain_x[0],0,8),\
																reg_psp_gain_lut1_y1,	GET_BITS(pp->face_bg_gain_y[1],0,8),\
																reg_psp_gain_lut1_x1,	GET_BITS(pp->face_bg_gain_x[1],0,8));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_00,	reg_sat_gain_en,		GET_BITS(pp->face_sat_enable,0,1),\
																reg_cbst_en,			GET_BITS(pp->face_ch_bst_enable,0,1));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_21, 	reg_yy_lut_pts_x0,	GET_BITS(pp->face_yy_lut_pts_x[0],0,10),\
																reg_yy_lut_pts_x1,	GET_BITS(pp->face_yy_lut_pts_x[1],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_22, 	reg_yy_lut_pts_x2,	GET_BITS(pp->face_yy_lut_pts_x[2],0,10),\
																reg_yy_lut_pts_x3,	GET_BITS(pp->face_yy_lut_pts_x[3],0,10));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_23, 	reg_yy_lut_pts_y0,	GET_BITS(pp->face_yy_lut_pts_y[0],0,8),\
																reg_yy_lut_pts_y1,	GET_BITS(pp->face_yy_lut_pts_y[1],0,8),\
																reg_yy_lut_pts_y2,	GET_BITS(pp->face_yy_lut_pts_y[2],0,8),\
																reg_yy_lut_pts_y3,	GET_BITS(pp->face_yy_lut_pts_y[3],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_24, 	reg_cc_lut_pts_y0,	GET_BITS(pp->face_cc_lut_pts_y[0],0,8),\
																reg_cc_lut_pts_x0,	GET_BITS(pp->face_cc_lut_pts_x[0],0,8),\
																reg_cc_lut_pts_y1,	GET_BITS(pp->face_cc_lut_pts_y[1],0,8),\
																reg_cc_lut_pts_x1,	GET_BITS(pp->face_cc_lut_pts_x[1],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_25, 	reg_cc_lut_pts_y2,	GET_BITS(pp->face_cc_lut_pts_y[2],0,8),\
																reg_cc_lut_pts_x2,	GET_BITS(pp->face_cc_lut_pts_x[2],0,8),\
																reg_cc_lut_pts_y3,	GET_BITS(pp->face_cc_lut_pts_y[3],0,8),\
																reg_cc_lut_pts_x3,	GET_BITS(pp->face_cc_lut_pts_x[3],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_26, 	reg_cbst_lut_pts_y0,	GET_BITS(pp->face_cbst_lut_pts_y[0],0,8),\
																reg_cbst_lut_pts_x0,	GET_BITS(pp->face_cbst_lut_pts_x[0],0,8),\
																reg_cbst_lut_pts_y1,	GET_BITS(pp->face_cbst_lut_pts_y[1],0,8),\
																reg_cbst_lut_pts_x1,	GET_BITS(pp->face_cbst_lut_pts_x[1],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_27, 	reg_cbst_lut_pts_y2,	GET_BITS(pp->face_cbst_lut_pts_y[2],0,8),\
																reg_cbst_lut_pts_x2,	GET_BITS(pp->face_cbst_lut_pts_x[2],0,8),\
																reg_cbst_lut_pts_y3,	GET_BITS(pp->face_cbst_lut_pts_y[3],0,8),\
																reg_cbst_lut_pts_x3,	GET_BITS(pp->face_cbst_lut_pts_x[3],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_29, 	reg_face_objt_lut_y0,	GET_BITS(pp->face_obj_lut_y[0],0,8),\
																reg_face_objt_lut_x0,	GET_BITS(pp->face_obj_lut_x[0],0,8),\
																reg_face_objt_lut_y1,	GET_BITS(pp->face_obj_lut_y[1],0,8),\
																reg_face_objt_lut_x1,	GET_BITS(pp->face_obj_lut_x[1],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_28, 	reg_face_objt_lut_y2,	GET_BITS(pp->face_obj_lut_y[2],0,8),\
																reg_face_objt_lut_x2,	GET_BITS(pp->face_obj_lut_x[2],0,8),\
																reg_face_objt_lut_y3,	GET_BITS(pp->face_obj_lut_y[3],0,8),\
																reg_face_objt_lut_x3,	GET_BITS(pp->face_obj_lut_x[3],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_31, 	reg_objt_face_lut_y0,	GET_BITS(pp->obj_face_lut_y[0],0,8),\
																reg_objt_face_lut_x0,	GET_BITS(pp->obj_face_lut_x[0],0,8),\
																reg_objt_face_lut_y1,	GET_BITS(pp->obj_face_lut_y[1],0,8),\
																reg_objt_face_lut_x1,	GET_BITS(pp->obj_face_lut_x[1],0,8));
				PE_VSD_HW_O20_RCE_F_WR04(reg_rce_face_ctrl_30, 	reg_objt_face_lut_y2,	GET_BITS(pp->obj_face_lut_y[2],0,8),\
																reg_objt_face_lut_x2,	GET_BITS(pp->obj_face_lut_x[2],0,8),\
																reg_objt_face_lut_y3,	GET_BITS(pp->obj_face_lut_y[3],0,8),\
																reg_objt_face_lut_x3,	GET_BITS(pp->obj_face_lut_x[3],0,8));
				#if 1	/* F20_TBL */
				PE_CHPI_OBC_HW_F20_SetCtrl(pstParams);
				#endif
			}
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_GetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_VSD_OBC2_CONT_T *pp=(LX_PE_VSD_OBC2_CONT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_RCE_O_O20_QRd04(reg_rce_objt_ctrl_19, 	reg_psp_gain_lut0_y0,	pp->obj_fg_gain_y[0],\
																reg_psp_gain_lut0_x0,	pp->obj_fg_gain_x[0],\
																reg_psp_gain_lut0_y1,	pp->obj_fg_gain_y[1],\
																reg_psp_gain_lut0_x1,	pp->obj_fg_gain_x[1]);
				PE_VSD_RCE_O_O20_QRd04(reg_rce_objt_ctrl_20, 	reg_psp_gain_lut1_y0,	pp->obj_bg_gain_y[0],\
																reg_psp_gain_lut1_x0,	pp->obj_bg_gain_x[0],\
																reg_psp_gain_lut1_y1,	pp->obj_bg_gain_y[1],\
																reg_psp_gain_lut1_x1,	pp->obj_bg_gain_x[1]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_00,	reg_sat_gain_en,		pp->obj_sat_enable,\
																reg_cbst_en,			pp->obj_ch_bst_enable);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_21, 	reg_yy_lut_pts_x0,	pp->obj_yy_lut_pts_x[0],\
																reg_yy_lut_pts_x1,	pp->obj_yy_lut_pts_x[1]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_22, 	reg_yy_lut_pts_x2,	pp->obj_yy_lut_pts_x[2],\
																reg_yy_lut_pts_x3,	pp->obj_yy_lut_pts_x[3]);
				PE_VSD_RCE_O_O20_QRd04(reg_rce_objt_ctrl_23, 	reg_yy_lut_pts_y0,	pp->obj_yy_lut_pts_y[0],\
																reg_yy_lut_pts_y1,	pp->obj_yy_lut_pts_y[1],\
																reg_yy_lut_pts_y2,	pp->obj_yy_lut_pts_y[2],\
																reg_yy_lut_pts_y3,	pp->obj_yy_lut_pts_y[3]);
				PE_VSD_RCE_O_O20_QRd04(reg_rce_objt_ctrl_24, 	reg_cc_lut_pts_y0,	pp->obj_cc_lut_pts_y[0],\
																reg_cc_lut_pts_x0,	pp->obj_cc_lut_pts_x[0],\
																reg_cc_lut_pts_y1,	pp->obj_cc_lut_pts_y[1],\
																reg_cc_lut_pts_x1,	pp->obj_cc_lut_pts_x[1]);
				PE_VSD_RCE_O_O20_QRd04(reg_rce_objt_ctrl_25, 	reg_cc_lut_pts_y2,	pp->obj_cc_lut_pts_y[2],\
																reg_cc_lut_pts_x2,	pp->obj_cc_lut_pts_x[2],\
																reg_cc_lut_pts_y3,	pp->obj_cc_lut_pts_y[3],\
																reg_cc_lut_pts_x3,	pp->obj_cc_lut_pts_x[3]);
				PE_VSD_RCE_O_O20_QRd04(reg_rce_objt_ctrl_26, 	reg_cbst_lut_pts_y0,	pp->obj_cbst_lut_pts_y[0],\
																reg_cbst_lut_pts_x0,	pp->obj_cbst_lut_pts_x[0],\
																reg_cbst_lut_pts_y1,	pp->obj_cbst_lut_pts_y[1],\
																reg_cbst_lut_pts_x1,	pp->obj_cbst_lut_pts_x[1]);
				PE_VSD_RCE_O_O20_QRd04(reg_rce_objt_ctrl_27, 	reg_cbst_lut_pts_y2,	pp->obj_cbst_lut_pts_y[2],\
																reg_cbst_lut_pts_x2,	pp->obj_cbst_lut_pts_x[2],\
																reg_cbst_lut_pts_y3,	pp->obj_cbst_lut_pts_y[3],\
																reg_cbst_lut_pts_x3,	pp->obj_cbst_lut_pts_x[3]);

				PE_VSD_RCE_F_O20_QRd04(reg_rce_face_ctrl_19, 	reg_psp_gain_lut0_y0,	pp->face_fg_gain_y[0],\
																reg_psp_gain_lut0_x0,	pp->face_fg_gain_x[0],\
																reg_psp_gain_lut0_y1,	pp->face_fg_gain_y[1],\
																reg_psp_gain_lut0_x1,	pp->face_fg_gain_x[1]);
				PE_VSD_RCE_F_O20_QRd04(reg_rce_face_ctrl_20, 	reg_psp_gain_lut1_y0,	pp->face_bg_gain_y[0],\
																reg_psp_gain_lut1_x0,	pp->face_bg_gain_x[0],\
																reg_psp_gain_lut1_y1,	pp->face_bg_gain_y[1],\
																reg_psp_gain_lut1_x1,	pp->face_bg_gain_x[1]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_00,	reg_sat_gain_en,		pp->face_sat_enable,\
																reg_cbst_en,			pp->face_ch_bst_enable);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_21, 	reg_yy_lut_pts_x0,	pp->face_yy_lut_pts_x[0],\
																reg_yy_lut_pts_x1,	pp->face_yy_lut_pts_x[1]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_22, 	reg_yy_lut_pts_x2,	pp->face_yy_lut_pts_x[2],\
																reg_yy_lut_pts_x3,	pp->face_yy_lut_pts_x[3]);
				PE_VSD_RCE_F_O20_QRd04(reg_rce_face_ctrl_23, 	reg_yy_lut_pts_y0,	pp->face_yy_lut_pts_y[0],\
																reg_yy_lut_pts_y1,	pp->face_yy_lut_pts_y[1],\
																reg_yy_lut_pts_y2,	pp->face_yy_lut_pts_y[2],\
																reg_yy_lut_pts_y3,	pp->face_yy_lut_pts_y[3]);
				PE_VSD_RCE_F_O20_QRd04(reg_rce_face_ctrl_24, 	reg_cc_lut_pts_y0,	pp->face_cc_lut_pts_y[0],\
																reg_cc_lut_pts_x0,	pp->face_cc_lut_pts_x[0],\
																reg_cc_lut_pts_y1,	pp->face_cc_lut_pts_y[1],\
																reg_cc_lut_pts_x1,	pp->face_cc_lut_pts_x[1]);
				PE_VSD_RCE_F_O20_QRd04(reg_rce_face_ctrl_25, 	reg_cc_lut_pts_y2,	pp->face_cc_lut_pts_y[2],\
																reg_cc_lut_pts_x2,	pp->face_cc_lut_pts_x[2],\
																reg_cc_lut_pts_y3,	pp->face_cc_lut_pts_y[3],\
																reg_cc_lut_pts_x3,	pp->face_cc_lut_pts_x[3]);
				PE_VSD_RCE_F_O20_QRd04(reg_rce_face_ctrl_26, 	reg_cbst_lut_pts_y0,	pp->face_cbst_lut_pts_y[0],\
																reg_cbst_lut_pts_x0,	pp->face_cbst_lut_pts_x[0],\
																reg_cbst_lut_pts_y1,	pp->face_cbst_lut_pts_y[1],\
																reg_cbst_lut_pts_x1,	pp->face_cbst_lut_pts_x[1]);
				PE_VSD_RCE_F_O20_QRd04(reg_rce_face_ctrl_27, 	reg_cbst_lut_pts_y2,	pp->face_cbst_lut_pts_y[2],\
																reg_cbst_lut_pts_x2,	pp->face_cbst_lut_pts_x[2],\
																reg_cbst_lut_pts_y3,	pp->face_cbst_lut_pts_y[3],\
																reg_cbst_lut_pts_x3,	pp->face_cbst_lut_pts_x[3]);
			}
			if (_g_shp_hw_o20_trace)
			{
				PE_SHP_HW_O20_DBG_PRINT("[wid:%d] get: n"\
				"obj_fg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"obj_fg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"obj_bg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"obj_bg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"obj_sat_enable: 0x%02X, obj_ch_bst_enable:0x%02X \n"\
				"obj_yy_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_yy_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_cc_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_cc_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_cbst_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"obj_cbst_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_fg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"face_fg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"face_bg_gain_x0,x1: 0x%02X,0x%02X\n"\
				"face_bg_gain_y0,y1: 0x%02X,0x%02X\n"\
				"face_sat_enable: 0x%02X, face_ch_bst_enable:0x%02X \n"\
				"face_yy_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_yy_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_cc_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_cc_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_cbst_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"face_cbst_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n",\
				pp->win_id,\
				pp->obj_fg_gain_x[0],pp->obj_fg_gain_x[1],pp->obj_fg_gain_y[0],pp->obj_fg_gain_y[1], \
				pp->obj_bg_gain_x[0],pp->obj_bg_gain_x[1],pp->obj_bg_gain_y[0],pp->obj_bg_gain_y[1], \
				pp->obj_sat_enable, pp->obj_ch_bst_enable,\
				pp->obj_yy_lut_pts_x[0],pp->obj_yy_lut_pts_x[1],pp->obj_yy_lut_pts_x[2],pp->obj_yy_lut_pts_x[3],\
				pp->obj_yy_lut_pts_y[0],pp->obj_yy_lut_pts_y[1],pp->obj_yy_lut_pts_y[2],pp->obj_yy_lut_pts_y[3],\
				pp->obj_cc_lut_pts_x[0],pp->obj_cc_lut_pts_x[1],pp->obj_cc_lut_pts_x[2],pp->obj_cc_lut_pts_x[3],\
				pp->obj_cc_lut_pts_y[0],pp->obj_cc_lut_pts_y[1],pp->obj_cc_lut_pts_y[2],pp->obj_cc_lut_pts_y[3],\
				pp->obj_cbst_lut_pts_x[0],pp->obj_cbst_lut_pts_x[1],pp->obj_cbst_lut_pts_x[2],pp->obj_cbst_lut_pts_x[3],\
				pp->face_cbst_lut_pts_y[0],pp->face_cbst_lut_pts_y[1],pp->face_cbst_lut_pts_y[2],pp->face_cbst_lut_pts_y[3],\
				pp->face_fg_gain_x[0],pp->face_fg_gain_x[1],pp->face_fg_gain_y[0],pp->face_fg_gain_y[1], \
				pp->face_bg_gain_x[0],pp->face_bg_gain_x[1],pp->face_bg_gain_y[0],pp->face_bg_gain_y[1], \
				pp->face_sat_enable, pp->face_ch_bst_enable,\
				pp->face_yy_lut_pts_x[0],pp->face_yy_lut_pts_x[1],pp->face_yy_lut_pts_x[2],pp->face_yy_lut_pts_x[3],\
				pp->face_yy_lut_pts_y[0],pp->face_yy_lut_pts_y[1],pp->face_yy_lut_pts_y[2],pp->face_yy_lut_pts_y[3],\
				pp->face_cc_lut_pts_x[0],pp->face_cc_lut_pts_x[1],pp->face_cc_lut_pts_x[2],pp->face_cc_lut_pts_x[3],\
				pp->face_cc_lut_pts_y[0],pp->face_cc_lut_pts_y[1],pp->face_cc_lut_pts_y[2],pp->face_cc_lut_pts_y[3],\
				pp->face_cbst_lut_pts_x[0],pp->face_cbst_lut_pts_x[1],pp->face_cbst_lut_pts_x[2],pp->face_cbst_lut_pts_x[3],\
				pp->face_cbst_lut_pts_y[0],pp->face_cbst_lut_pts_y[1],pp->face_cbst_lut_pts_y[2],pp->face_cbst_lut_pts_y[3]);
			}
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_SetObcLUT(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_VSD_OBC1_LUT_T *pp=(LX_PE_VSD_OBC1_LUT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if (_g_shp_hw_o20_trace)
			{
				PE_SHP_HW_O20_DBG_PRINT("[wid:%d] set: n"\
				"object_fg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"object_fg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"object_bg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"object_bg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"face_fg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"face_fg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"face_bg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"face_bg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id,\
				pp->object_fg_x[0],pp->object_fg_x[1],pp->object_fg_x[2],pp->object_fg_x[3], \
				pp->object_fg_x[4],pp->object_fg_x[5],pp->object_fg_x[6],pp->object_fg_x[7], \
				pp->object_fg_y[0],pp->object_fg_y[1],pp->object_fg_y[2],pp->object_fg_y[3], \
				pp->object_fg_y[4],pp->object_fg_y[5],pp->object_fg_y[6],pp->object_fg_y[7], \
				pp->object_bg_x[0],pp->object_bg_x[1],pp->object_bg_x[2],pp->object_bg_x[3], \
				pp->object_bg_x[4],pp->object_bg_x[5],pp->object_bg_x[6],pp->object_bg_x[7], \
				pp->object_bg_y[0],pp->object_bg_y[1],pp->object_bg_y[2],pp->object_bg_y[3], \
				pp->object_bg_y[4],pp->object_bg_y[5],pp->object_bg_y[6],pp->object_bg_y[7], \
				pp->face_fg_x[0],pp->face_fg_x[1],pp->face_fg_x[2],pp->face_fg_x[3], \
				pp->face_fg_x[4],pp->face_fg_x[5],pp->face_fg_x[6],pp->face_fg_x[7], \
				pp->face_fg_y[0],pp->face_fg_y[1],pp->face_fg_y[2],pp->face_fg_y[3], \
				pp->face_fg_y[4],pp->face_fg_y[5],pp->face_fg_y[6],pp->face_fg_y[7], \
				pp->face_bg_x[0],pp->face_bg_x[1],pp->face_bg_x[2],pp->face_bg_x[3], \
				pp->face_bg_x[4],pp->face_bg_x[5],pp->face_bg_x[6],pp->face_bg_x[7], \
				pp->face_bg_y[0],pp->face_bg_y[1],pp->face_bg_y[2],pp->face_bg_y[3], \
				pp->face_bg_y[4],pp->face_bg_y[5],pp->face_bg_y[6],pp->face_bg_y[7]);
			}
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_03, 	reg_psp_lut0_x0,  GET_BITS(pp->object_fg_x[0],0,10),\
																reg_psp_lut0_y0,  GET_BITS(pp->object_fg_y[0],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_04, 	reg_psp_lut0_x1, GET_BITS(pp->object_fg_x[1],0,10),\
																reg_psp_lut0_y1, GET_BITS(pp->object_fg_y[1],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_05, 	reg_psp_lut0_x2, GET_BITS(pp->object_fg_x[2],0,10),\
																reg_psp_lut0_y2, GET_BITS(pp->object_fg_y[2],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_06, 	reg_psp_lut0_x3, GET_BITS(pp->object_fg_x[3],0,10),\
																reg_psp_lut0_y3, GET_BITS(pp->object_fg_y[3],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_07, 	reg_psp_lut0_x4, GET_BITS(pp->object_fg_x[4],0,10),\
																reg_psp_lut0_y4, GET_BITS(pp->object_fg_y[4],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_08, 	reg_psp_lut0_x5, GET_BITS(pp->object_fg_x[5],0,10),\
																reg_psp_lut0_y5, GET_BITS(pp->object_fg_y[5],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_09, 	reg_psp_lut0_x6, GET_BITS(pp->object_fg_x[6],0,10),\
																reg_psp_lut0_y6, GET_BITS(pp->object_fg_y[6],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_10, 	reg_psp_lut0_x7, GET_BITS(pp->object_fg_x[7],0,10),\
																reg_psp_lut0_y7, GET_BITS(pp->object_fg_y[7],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_11, 	reg_psp_lut1_x0, GET_BITS(pp->object_bg_x[0],0,10),\
																reg_psp_lut1_y0, GET_BITS(pp->object_bg_y[0],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_12, 	reg_psp_lut1_x1, GET_BITS(pp->object_bg_x[1],0,10),\
																reg_psp_lut1_y1, GET_BITS(pp->object_bg_y[1],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_13, 	reg_psp_lut1_x2, GET_BITS(pp->object_bg_x[2],0,10),\
																reg_psp_lut1_y2, GET_BITS(pp->object_bg_y[2],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_14, 	reg_psp_lut1_x3, GET_BITS(pp->object_bg_x[3],0,10),\
																reg_psp_lut1_y3, GET_BITS(pp->object_bg_y[3],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_15, 	reg_psp_lut1_x4, GET_BITS(pp->object_bg_x[4],0,10),\
																reg_psp_lut1_y4, GET_BITS(pp->object_bg_y[4],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_16, 	reg_psp_lut1_x5, GET_BITS(pp->object_bg_x[5],0,10),\
																reg_psp_lut1_y5, GET_BITS(pp->object_bg_y[5],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_17, 	reg_psp_lut1_x6, GET_BITS(pp->object_bg_x[6],0,10),\
																reg_psp_lut1_y6, GET_BITS(pp->object_bg_y[6],0,10));
				PE_VSD_HW_O20_RCE_O_WR02(reg_rce_objt_ctrl_18, 	reg_psp_lut1_x7, GET_BITS(pp->object_bg_x[7],0,10),\
																reg_psp_lut1_y7, GET_BITS(pp->object_bg_y[7],0,10));
				
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_03, 	reg_psp_lut0_x0,  GET_BITS(pp->face_fg_x[0],0,10),\
																reg_psp_lut0_y0,  GET_BITS(pp->face_fg_y[0],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_04, 	reg_psp_lut0_x1, GET_BITS(pp->face_fg_x[1],0,10),\
																reg_psp_lut0_y1, GET_BITS(pp->face_fg_y[1],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_05, 	reg_psp_lut0_x2, GET_BITS(pp->face_fg_x[2],0,10),\
																reg_psp_lut0_y2, GET_BITS(pp->face_fg_y[2],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_06, 	reg_psp_lut0_x3, GET_BITS(pp->face_fg_x[3],0,10),\
																reg_psp_lut0_y3, GET_BITS(pp->face_fg_y[3],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_07, 	reg_psp_lut0_x4, GET_BITS(pp->face_fg_x[4],0,10),\
																reg_psp_lut0_y4, GET_BITS(pp->face_fg_y[4],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_08, 	reg_psp_lut0_x5, GET_BITS(pp->face_fg_x[5],0,10),\
																reg_psp_lut0_y5, GET_BITS(pp->face_fg_y[5],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_09, 	reg_psp_lut0_x6, GET_BITS(pp->face_fg_x[6],0,10),\
																reg_psp_lut0_y6, GET_BITS(pp->face_fg_y[6],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_10, 	reg_psp_lut0_x7, GET_BITS(pp->face_fg_x[7],0,10),\
																reg_psp_lut0_y7, GET_BITS(pp->face_fg_y[7],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_11, 	reg_psp_lut1_x0, GET_BITS(pp->face_bg_x[0],0,10),\
																reg_psp_lut1_y0, GET_BITS(pp->face_bg_y[0],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_12, 	reg_psp_lut1_x1, GET_BITS(pp->face_bg_x[1],0,10),\
																reg_psp_lut1_y1, GET_BITS(pp->face_bg_y[1],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_13, 	reg_psp_lut1_x2, GET_BITS(pp->face_bg_x[2],0,10),\
																reg_psp_lut1_y2, GET_BITS(pp->face_bg_y[2],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_14, 	reg_psp_lut1_x3, GET_BITS(pp->face_bg_x[3],0,10),\
																reg_psp_lut1_y3, GET_BITS(pp->face_bg_y[3],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_15, 	reg_psp_lut1_x4, GET_BITS(pp->face_bg_x[4],0,10),\
																reg_psp_lut1_y4, GET_BITS(pp->face_bg_y[4],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_16, 	reg_psp_lut1_x5, GET_BITS(pp->face_bg_x[5],0,10),\
																reg_psp_lut1_y5, GET_BITS(pp->face_bg_y[5],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_17, 	reg_psp_lut1_x6, GET_BITS(pp->face_bg_x[6],0,10),\
																reg_psp_lut1_y6, GET_BITS(pp->face_bg_y[6],0,10));
				PE_VSD_HW_O20_RCE_F_WR02(reg_rce_face_ctrl_18, 	reg_psp_lut1_x7, GET_BITS(pp->face_bg_x[7],0,10),\
																reg_psp_lut1_y7, GET_BITS(pp->face_bg_y[7],0,10));
				#if 1	/* F20_TBL */
				PE_CHPI_OBC_HW_F20_SetLUT(pstParams);
				#endif
			}
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_GetObcLUT(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			LX_PE_VSD_OBC1_LUT_T *pp=(LX_PE_VSD_OBC1_LUT_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_03, 	reg_psp_lut0_x0, pp->object_fg_x[0],\
															reg_psp_lut0_y0, pp->object_fg_y[0]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_04, 	reg_psp_lut0_x1, pp->object_fg_x[1],\
															reg_psp_lut0_y1, pp->object_fg_y[1]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_05, 	reg_psp_lut0_x2, pp->object_fg_x[2],\
															reg_psp_lut0_y2, pp->object_fg_y[2]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_06, 	reg_psp_lut0_x3, pp->object_fg_x[3],\
															reg_psp_lut0_y3, pp->object_fg_y[3]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_07, 	reg_psp_lut0_x4, pp->object_fg_x[4],\
															reg_psp_lut0_y4, pp->object_fg_y[4]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_08, 	reg_psp_lut0_x5, pp->object_fg_x[5],\
															reg_psp_lut0_y5, pp->object_fg_y[5]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_09, 	reg_psp_lut0_x6, pp->object_fg_x[6],\
															reg_psp_lut0_y6, pp->object_fg_y[6]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_10, 	reg_psp_lut0_x7, pp->object_fg_x[7],\
															reg_psp_lut0_y7, pp->object_fg_y[7]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_11, 	reg_psp_lut1_x0, pp->object_bg_x[0],\
															reg_psp_lut1_y0, pp->object_bg_y[0]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_12, 	reg_psp_lut1_x1, pp->object_bg_x[1],\
															reg_psp_lut1_y1, pp->object_bg_y[1]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_13, 	reg_psp_lut1_x2, pp->object_bg_x[2],\
															reg_psp_lut1_y2, pp->object_bg_y[2]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_14, 	reg_psp_lut1_x3, pp->object_bg_x[3],\
															reg_psp_lut1_y3, pp->object_bg_y[3]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_15, 	reg_psp_lut1_x4, pp->object_bg_x[4],\
															reg_psp_lut1_y4, pp->object_bg_y[4]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_16, 	reg_psp_lut1_x5, pp->object_bg_x[5],\
															reg_psp_lut1_y5, pp->object_bg_y[5]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_17, 	reg_psp_lut1_x6, pp->object_bg_x[6],\
															reg_psp_lut1_y6, pp->object_bg_y[6]);
				PE_VSD_RCE_O_O20_QRd02(reg_rce_objt_ctrl_18, 	reg_psp_lut1_x7, pp->object_bg_x[7],\
																reg_psp_lut1_y7, pp->object_bg_y[7]);
				
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_03, 	reg_psp_lut0_x0, pp->face_fg_x[0],\
																reg_psp_lut0_y0, pp->face_fg_y[0]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_04, 	reg_psp_lut0_x1, pp->face_fg_x[1],\
																reg_psp_lut0_y1, pp->face_fg_y[1]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_05, 	reg_psp_lut0_x2, pp->face_fg_x[2],\
																reg_psp_lut0_y2, pp->face_fg_y[2]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_06, 	reg_psp_lut0_x3, pp->face_fg_x[3],\
																reg_psp_lut0_y3, pp->face_fg_y[3]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_07, 	reg_psp_lut0_x4, pp->face_fg_x[4],\
																reg_psp_lut0_y4, pp->face_fg_y[4]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_08, 	reg_psp_lut0_x5, pp->face_fg_x[5],\
																reg_psp_lut0_y5, pp->face_fg_y[5]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_09, 	reg_psp_lut0_x6, pp->face_fg_x[6],\
																reg_psp_lut0_y6, pp->face_fg_y[6]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_10, 	reg_psp_lut0_x7, pp->face_fg_x[7],\
																reg_psp_lut0_y7, pp->face_fg_y[7]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_11, 	reg_psp_lut1_x0, pp->face_bg_x[0],\
																reg_psp_lut1_y0, pp->face_bg_y[0]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_12, 	reg_psp_lut1_x1, pp->face_bg_x[1],\
																reg_psp_lut1_y1, pp->face_bg_y[1]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_13, 	reg_psp_lut1_x2, pp->face_bg_x[2],\
																reg_psp_lut1_y2, pp->face_bg_y[2]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_14, 	reg_psp_lut1_x3, pp->face_bg_x[3],\
																reg_psp_lut1_y3, pp->face_bg_y[3]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_15, 	reg_psp_lut1_x4, pp->face_bg_x[4],\
																reg_psp_lut1_y4, pp->face_bg_y[4]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_16, 	reg_psp_lut1_x5, pp->face_bg_x[5],\
																reg_psp_lut1_y5, pp->face_bg_y[5]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_17, 	reg_psp_lut1_x6, pp->face_bg_x[6],\
																reg_psp_lut1_y6, pp->face_bg_y[6]);
				PE_VSD_RCE_F_O20_QRd02(reg_rce_face_ctrl_18, 	reg_psp_lut1_x7, pp->face_bg_x[7],\
																reg_psp_lut1_y7, pp->face_bg_y[7]);

			}
			if (_g_shp_hw_o20_trace)
			{
				PE_SHP_HW_O20_DBG_PRINT("[wid:%d] get: n"\
					"object_fg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"object_fg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"object_bg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"object_bg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"face_fg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"face_fg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"face_bg_x: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
					"face_bg_y: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
					pp->win_id,\
					pp->object_fg_x[0],pp->object_fg_x[1],pp->object_fg_x[2],pp->object_fg_x[3], \
					pp->object_fg_x[4],pp->object_fg_x[5],pp->object_fg_x[6],pp->object_fg_x[7], \
					pp->object_fg_y[0],pp->object_fg_y[1],pp->object_fg_y[2],pp->object_fg_y[3], \
					pp->object_fg_y[4],pp->object_fg_y[5],pp->object_fg_y[6],pp->object_fg_y[7], \
					pp->object_bg_x[0],pp->object_bg_x[1],pp->object_bg_x[2],pp->object_bg_x[3], \
					pp->object_bg_x[4],pp->object_bg_x[5],pp->object_bg_x[6],pp->object_bg_x[7], \
					pp->object_bg_y[0],pp->object_bg_y[1],pp->object_bg_y[2],pp->object_bg_y[3], \
					pp->object_bg_y[4],pp->object_bg_y[5],pp->object_bg_y[6],pp->object_bg_y[7], \
					pp->face_fg_x[0],pp->face_fg_x[1],pp->face_fg_x[2],pp->face_fg_x[3], \
					pp->face_fg_x[4],pp->face_fg_x[5],pp->face_fg_x[6],pp->face_fg_x[7], \
					pp->face_fg_y[0],pp->face_fg_y[1],pp->face_fg_y[2],pp->face_fg_y[3], \
					pp->face_fg_y[4],pp->face_fg_y[5],pp->face_fg_y[6],pp->face_fg_y[7], \
					pp->face_bg_x[0],pp->face_bg_x[1],pp->face_bg_x[2],pp->face_bg_x[3], \
					pp->face_bg_x[4],pp->face_bg_x[5],pp->face_bg_x[6],pp->face_bg_x[7], \
					pp->face_bg_y[0],pp->face_bg_y[1],pp->face_bg_y[2],pp->face_bg_y[3], \
					pp->face_bg_y[4],pp->face_bg_y[5],pp->face_bg_y[6],pp->face_bg_y[7]);
			}
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_SetObcStereoCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 reg_obj_shp_en,reg_face_en,reg_obj_gain_en,reg_psp_en,reg_obc_debug;
	UINT32 *onoff;
	PE_REG_O20_HW_OPT_T hw_opt = PE_REG_O20_GetDispOpt();
	char buffer[PE_TRACE_STR_SIZE];
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
 			onoff = (UINT32*)pstParams;
			PE_SHP_HW_O20_DBG_PRINT("set OBC Stereo Demo : %d \n",*onoff);

			if (*onoff > 0x2)	{PE_SHP_HW_O20_DBG_PRINT("skip\n");break;}

			if(*onoff == 0x0)
			{
				reg_obj_shp_en = 0;
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
			PE_SHP_HW_O20_RES_WR01(shp_obj_ctrl_00,	reg_obj_shp_en,	reg_obj_shp_en);
			/* decontour */
			PE_DNR0_O20_QWr01(reg_decon_ctrl_56, reg_face_en, reg_face_en);
			PE_DNR1_O20_QWr01(reg_decon_ctrl_56, reg_face_en, reg_face_en);
			/* dc bnr */
			PE_DNR0_O20_QWr01(dc_bnr_ctrl_0, reg_obj_gain_en, reg_obj_gain_en);
			PE_DNR1_O20_QWr01(dc_bnr_ctrl_0, reg_obj_gain_en, reg_obj_gain_en);
			/* RCE */
			if (hw_opt.external_chip==0) //4k model
			{
				PE_VSD_HW_O20_RCE_O_WR01(reg_rce_objt_ctrl_00, reg_psp_en, reg_psp_en);
				PE_VSD_HW_O20_RCE_F_WR01(reg_rce_face_ctrl_00, reg_psp_en, reg_psp_en);
			}
			else //8k model
			{
				PE_VSD_HW_O20_RCE_O_WR01(reg_rce_objt_ctrl_00, reg_psp_en, 0x0);
				PE_VSD_HW_O20_RCE_F_WR01(reg_rce_face_ctrl_00, reg_psp_en, 0x0);
			}
			
			snprintf(buffer, PE_TRACE_STR_SIZE, "SetObcStereoCtrl on/off:%d,shp:%d,face:%d,obj_gain:%d,psp:%d,obc_debug:%d",\
				*onoff,reg_obj_shp_en,reg_face_en,reg_obj_gain_en,reg_psp_en,reg_obc_debug);
			PE_INF_HW_O20_BACKUP_TRACE_DB("%s",buffer);
			ret = PE_FWI_HW_O20_ObcDemoMode(reg_obc_debug);
			PE_SHP_O20_QWr01(shp_fsw_ctrl_02, reg_obc_debug, reg_obc_debug);

			#if 1	/* F20_APB *//* F20_TBL */
			do {
				PE_CHPI_SHP_HW_F20_SetEnable(onoff);
				PE_CHPI_DNR_HW_F20_SetEnable(onoff);
				PE_CHPI_OBC_HW_F20_SetEnable(onoff);
				PE_CHPI_APB0_F20_Wr(fsw0.shp_fsw_ctrl_02.reg_obc_debug,reg_obc_debug);
				PE_CHPI_APB0_F20_WrFL(fsw0.shp_fsw_ctrl_02.udata32);
				PE_INF_O20_SetChipInfoHead(PE_INF_O20_CHPI_BLOCK_FSW0);
			} while(0);
			#endif
 		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_DownloadShp2KSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_ui_sqm_2k.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O20)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O20_SEC_SHP_UI_SQM_2K;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O20_SHP_UI_SQM_2K_SIZE;
			p_phys_db->shp_ui_sqm_2k.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_ui_sqm_2k.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_ui_sqm_2k.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_ui_sqm_2k.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O20_SHP_UI_SQM_2K_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O20_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O20_SHP_UI_SQM_2K_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_2k_cmn_init_o20[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_O20_DownloadShp2KSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_ui_sqm_2k.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_SHP_UI_SQM_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O20_SHP_UI_SQM_2K_T);
			pp = (LX_PE_SHP_SR2K_SQM2_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm___val;
			base = 2;
			for (i=0; i<PE_DDR_O20_SHP_UI_SQM_2K_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_ui_sqm_2k[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_SHP_HW_O20_DBG_PRINT("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	//if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_GetShp2KSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM2_CMN_T *pp = NULL;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_ui_sqm_2k.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_SHP_UI_SQM_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O20_SHP_UI_SQM_2K_T);
			pp = (LX_PE_SHP_SR2K_SQM2_CMN_T *)pstParams;
			pp->shp_sqm___val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O20_SHP_UI_SQM_2K_SIZE-base; i++)
			{
				pp->shp_ui_sqm_2k[i] = p_db_data[base+i] ;
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			UINT32 *pd = pp->shp_ui_sqm_2k;
			printk( \
			"shp_ui_sqm_2k[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_2k[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_2k[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_2k[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
			pd[10],pd[11],	pd[12],  pd[13], pd[14],  pd[15],  pd[16],	pd[17], pd[18],  pd[19], \
			pd[20],pd[21],	pd[22],  pd[23], pd[24],  pd[25],  pd[26],	pd[27], pd[28],  pd[29],\
			pd[30],pd[31],	pd[32],  pd[33], pd[34],  pd[35],  pd[36],	pd[37], pd[38]);
			
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	//if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_DownloadShp2KSqmDetailInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_sqmcmn__2k.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O20)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O20_SEC_SHP_SQM_CMN_2K;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O20_SHP_SQM_CMN_2K_SIZE;
			p_phys_db->shp_sqmcmn__2k.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_sqmcmn__2k.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_sqmcmn__2k.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_sqmcmn__2k.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O20_SHP_SQM_CMN_2K_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O20_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O20_SHP_SQM_CMN_2K_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_2k_dtl_init_o20[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_O20_DownloadShp2KSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM2_DETAIL_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->shp_sqmcmn__2k.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_SHP_SQM_CMN_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O20_SHP_SQM_CMN_2K_T);
			pp = (LX_PE_SHP_SR2K_SQM2_DETAIL_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm____val;
			base = 2;
			for (i=0; i<PE_DDR_O20_SHP_SQM_CMN_2K_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_sqm_cmn_2k[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_SHP_HW_O20_DBG_PRINT("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	//if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_GetShp2KSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_SR2K_SQM2_DETAIL_T *pp = NULL;
	//static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data =  p_phys_db->shp_sqmcmn__2k.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_SHP_SQM_CMN_2K;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O20_SHP_SQM_CMN_2K_T);
			pp = (LX_PE_SHP_SR2K_SQM2_DETAIL_T *)pstParams;
			pp->shp_sqm____val = (UINT8)p_db_data[1] ;
			base = 2;
			for (i=0; i<PE_DDR_O20_SHP_SQM_CMN_2K_SIZE-base; i++)
			{
				pp->shp_sqm_cmn_2k[i] = p_db_data[base+i];
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			UINT32 *pd = pp->shp_sqm_cmn_2k;
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
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	//if (p_phys_shp_sqm_db) vunmap_phys((void *)p_phys_shp_sqm_db);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_DownloadShpSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_ui_sqm_vsd.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O20)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O20_SEC_SHP_UI_SQM_VSD;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O20_SHP_UI_SQM_VSD_SIZE;
			p_phys_db->shp_ui_sqm_vsd.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_ui_sqm_vsd.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_ui_sqm_vsd.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_ui_sqm_vsd.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O20_SHP_UI_SQM_VSD_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O20_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O20_SHP_UI_SQM_VSD_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_vsd_cmn_init_o20[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_O20_DownloadShpSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM2_CMN_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_ui_sqm_vsd.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_SHP_UI_SQM_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O20_SHP_UI_SQM_VSD_T);
			pp = (LX_PE_SHP_RE_SQM2_CMN_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm____val;
			base = 2;
			for (i=0; i<PE_DDR_O20_SHP_UI_SQM_VSD_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_ui_sqm_vsd[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_SHP_HW_O20_DBG_PRINT("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_GetShpSqmCmnUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM2_CMN_T *pp = NULL;
	//static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_ui_sqm_vsd.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_SHP_UI_SQM_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O20_SHP_UI_SQM_VSD_T);
			pp = (LX_PE_SHP_RE_SQM2_CMN_T *)pstParams;
			pp->shp_sqm____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O20_SHP_UI_SQM_VSD_SIZE-base; i++)
			{
				pp->shp_ui_sqm_vsd[i] = p_db_data[base+i];
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			UINT32 *pd = pp->shp_ui_sqm_vsd;
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
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_DownloadShpSqmDetailInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_sqmcmn__vsd.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O20)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_O20_SEC_SHP_SQM_CMN_VSD;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O20_SHP_SQM_CMN_VSD_SIZE;
			p_phys_db->shp_sqmcmn__vsd.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_sqmcmn__vsd.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_sqmcmn__vsd.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_sqmcmn__vsd.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_O20_SHP_SQM_CMN_VSD_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O20_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_O20_SHP_SQM_CMN_VSD_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_vsd_dtl_init_o20[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_O20_DownloadShpSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM2_DETAIL_T *pp = NULL;
	static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_sqmcmn__vsd.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_SHP_SQM_CMN_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O20_SHP_SQM_CMN_VSD_T);
			pp = (LX_PE_SHP_RE_SQM2_DETAIL_T *)pstParams;
			p_db_data[1] = (UINT32)pp->shp_sqm_____val;
			base = 2;
			for (i=0; i<PE_DDR_O20_SHP_SQM_CMN_VSD_SIZE-base; i++)
			{
				p_db_data[base+i] = pp->shp_sqm_cmn_vsd[i];
			}
			wmb();
			count = (count < 0xff)? (count+1):0x0;
			p_db_data[0] = count;
			wmb();
			PE_SHP_HW_O20_DBG_PRINT("%s: DL done.(sec_base:0x%08x,data_base:0x%08x)(cnt:%4d)\n", \
				PE_DDR_REG_O20_SEC_TYPE_TO_STR(sec_typ), \
				p_shdw_db->top_h.sec_base[sec_typ],p_shdw_db->sec_d[sec_typ].data_base, count);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_O20_GetShpSqmDetailUserDb(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base;
	LX_PE_SHP_RE_SQM2_DETAIL_T *pp = NULL;
	//static UINT32 count = 0;
	PE_DDR_DB_SHDW_REG_O20_T *p_shdw_db = gPE_DDR_DB_O20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_O20_T *p_phys_db = gPE_DDR_DB_O20.phys.data;
	volatile UINT32 *p_db_data = p_phys_db->shp_sqmcmn__vsd.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_db_data);
		if (PE_KDRV_VER_O20)
		{
			sec_typ = PE_DDR_O20_SEC_SHP_SQM_CMN_VSD;
			base = p_shdw_db->top_h.sec_base[sec_typ];
			size = sizeof(PE_DDR_O20_SHP_SQM_CMN_VSD_T);
			pp = (LX_PE_SHP_RE_SQM2_DETAIL_T *)pstParams;
			pp->shp_sqm_____val = (UINT8)p_db_data[1];
			base = 2;
			for (i=0; i<PE_DDR_O20_SHP_SQM_CMN_VSD_SIZE-base; i++)
			{
				pp->shp_sqm_cmn_vsd[i] = p_db_data[base+i];
			}
			//wmb();
			//count = (count < 0xff)? (count+1):0x0;
			//p_db_data[0] = count;
			//wmb();
			UINT32 *pd = pp->shp_sqm_cmn_vsd;
			printk( \
			"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[50]0x%08X\n",\
			pd[0],	pd[1],	pd[2],	pd[3], pd[4],  pd[5],  pd[6],  pd[7], pd[8],  pd[9], \
			pd[10],pd[11],	pd[12],  pd[13], pd[14],  pd[15],  pd[16],	pd[17], pd[18],  pd[19], \
			pd[20],pd[21],	pd[22],  pd[23], pd[24],  pd[25],  pd[26],	pd[27], pd[28],  pd[29],\
			pd[30],pd[31],	pd[32],  pd[33], pd[34],  pd[35],  pd[36],	pd[37], pd[38],  pd[39],\
			pd[40],pd[41],	pd[42],  pd[43], pd[34],  pd[45],  pd[46],	pd[47], pd[48],  pd[49],\
			pd[50]);
			
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_F20_DownloadScl12tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, i = 0;
	UINT32 sec_typ_1212 = 0, sec_typ_1206 = 0,sec_typ_1204 = 0;
	UINT32 base_line_1212[PE_DDR_F20_1212T_FLT_NUM];
	UINT32 base_line_1206[PE_DDR_F20_1206T_FLT_NUM];
	UINT32 base_line_1204[PE_DDR_F20_1204T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_F20_T *p_shdw_db = gPE_DDR_DB_F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_F20_T *p_phys_db = gPE_DDR_DB_F20.phys.data;
	volatile UINT32 *p_t1212_data = p_phys_db->t1212.data;
	volatile UINT32 *p_t1206_data = p_phys_db->t1206.data;
	volatile UINT32 *p_t1204_data = p_phys_db->t1204.data;
 	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t1212_data);
		CHECK_KNULL(p_t1206_data);
		CHECK_KNULL(p_t1204_data);
 		if (PE_KDRV_VER_O20)
		{
			/*1. 1212  */
			sec_typ_1212 = PE_DDR_F20_SEC_SCL_1212T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1212].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1212].header.sec_type  = sec_typ_1212;
			p_shdw_db->sec_d[sec_typ_1212].header.item_num  = PE_DDR_F20_1212T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1212].header.item_size = PE_DDR_F20_SCL_12T_FLT_SIZE;
			p_phys_db->t1212.header.version   = p_shdw_db->sec_d[sec_typ_1212].header.version;
			p_phys_db->t1212.header.sec_type  = p_shdw_db->sec_d[sec_typ_1212].header.sec_type;
			p_phys_db->t1212.header.item_num  = p_shdw_db->sec_d[sec_typ_1212].header.item_num;
			p_phys_db->t1212.header.item_size = p_shdw_db->sec_d[sec_typ_1212].header.item_size;

			/* data */
			size = (PE_DDR_F20_1212T_FLT_NUM * PE_DDR_F20_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1212] = \
				p_shdw_db->top_h.sec_base[sec_typ_1212-1]+p_shdw_db->top_h.sec_size[sec_typ_1212-1];
			p_shdw_db->top_h.sec_size[sec_typ_1212] = size + sizeof(PE_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1212] = p_shdw_db->top_h.sec_base[sec_typ_1212];
			p_phys_db->top_h.sec_size[sec_typ_1212] = p_shdw_db->top_h.sec_size[sec_typ_1212];
			p_shdw_db->sec_d[sec_typ_1212].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1212] + sizeof(PE_DDR_F20_HEADER_T);


			/*2. 1206*/
			sec_typ_1206 = PE_DDR_F20_SEC_SCL_1206T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1206].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1206].header.sec_type  = sec_typ_1206;
			p_shdw_db->sec_d[sec_typ_1206].header.item_num  = PE_DDR_F20_1206T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1206].header.item_size = PE_DDR_F20_SCL_12T_FLT_SIZE;
			p_phys_db->t1206.header.version   = p_shdw_db->sec_d[sec_typ_1206].header.version;
			p_phys_db->t1206.header.sec_type  = p_shdw_db->sec_d[sec_typ_1206].header.sec_type;
			p_phys_db->t1206.header.item_num  = p_shdw_db->sec_d[sec_typ_1206].header.item_num;
			p_phys_db->t1206.header.item_size = p_shdw_db->sec_d[sec_typ_1206].header.item_size;
			/* data */
			size = (PE_DDR_F20_1206T_FLT_NUM * PE_DDR_F20_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1206] = \
				p_shdw_db->top_h.sec_base[sec_typ_1206-1]+p_shdw_db->top_h.sec_size[sec_typ_1206-1];
			p_shdw_db->top_h.sec_size[sec_typ_1206] = size + sizeof(PE_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1206] = p_shdw_db->top_h.sec_base[sec_typ_1206];
			p_phys_db->top_h.sec_size[sec_typ_1206] = p_shdw_db->top_h.sec_size[sec_typ_1206];
			p_shdw_db->sec_d[sec_typ_1206].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1206] + sizeof(PE_DDR_F20_HEADER_T);

			/*3. 1204*/
			sec_typ_1204 = PE_DDR_F20_SEC_SCL_1204T;
			/* header */
			p_shdw_db->sec_d[sec_typ_1204].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_1204].header.sec_type  = sec_typ_1204;
			p_shdw_db->sec_d[sec_typ_1204].header.item_num  = PE_DDR_F20_1204T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_1204].header.item_size = PE_DDR_F20_SCL_12T_FLT_SIZE;
			p_phys_db->t1204.header.version   = p_shdw_db->sec_d[sec_typ_1204].header.version;
			p_phys_db->t1204.header.sec_type  = p_shdw_db->sec_d[sec_typ_1204].header.sec_type;
			p_phys_db->t1204.header.item_num  = p_shdw_db->sec_d[sec_typ_1204].header.item_num;
			p_phys_db->t1204.header.item_size = p_shdw_db->sec_d[sec_typ_1204].header.item_size;
			/* data */
			size = (PE_DDR_F20_1204T_FLT_NUM * PE_DDR_F20_SCL_12T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_1204] = \
				p_shdw_db->top_h.sec_base[sec_typ_1204-1]+p_shdw_db->top_h.sec_size[sec_typ_1204-1];
			p_shdw_db->top_h.sec_size[sec_typ_1204] = size + sizeof(PE_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_1204] = p_shdw_db->top_h.sec_base[sec_typ_1204];
			p_phys_db->top_h.sec_size[sec_typ_1204] = p_shdw_db->top_h.sec_size[sec_typ_1204];
			p_shdw_db->sec_d[sec_typ_1204].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_1204] + sizeof(PE_DDR_F20_HEADER_T);


			/* wr ddr */
			base_line_1212[0] = 0;
			base_line_1206[0] = 0;
			base_line_1204[0] = 0;
			for (i=1; i<PE_DDR_F20_1212T_FLT_NUM; i++)
			{
				base_line_1212[i] = base_line_1212[i-1]+PE_DDR_F20_SCL_12T_FLT_SIZE;
			}
			for (i=1; i<PE_DDR_F20_1206T_FLT_NUM; i++)
			{
				base_line_1206[i] = base_line_1206[i-1]+PE_DDR_F20_SCL_12T_FLT_SIZE;;
			}
			for (i=1; i<PE_DDR_F20_1204T_FLT_NUM; i++)
			{
				base_line_1204[i] = base_line_1204[i-1]+PE_DDR_F20_SCL_12T_FLT_SIZE;;
			}
			for (i=0; i<PE_DDR_F20_SCL_12T_FLT_SIZE; i++)
			{
				//1212
				p_t1212_data[base_line_1212[0]+i]  = scl_p256_1212t_flt_0004[i].data;
				p_t1212_data[base_line_1212[1]+i]  = scl_p256_1212t_flt_0306[i].data;
				p_t1212_data[base_line_1212[2]+i]  = scl_p256_1212t_flt_1410[i].data;//dummy
				p_t1212_data[base_line_1212[3]+i]  = scl_p256_1212t_flt_1410[i].data;//dummy
				//1206
				p_t1206_data[base_line_1206[0]+i]  = scl_p256_1206t_flt_0610[i].data;
				p_t1206_data[base_line_1206[1]+i]  = scl_p256_1206t_flt_0306[i].data;//dummy
				//1204
				p_t1204_data[base_line_1204[0]+i]  = scl_p256_1204t_flt_0008[i].data;
				p_t1204_data[base_line_1204[1]+i]  = scl_p256_1204t_flt_0308[i].data;
				p_t1204_data[base_line_1204[2]+i]  = scl_p256_1204t_flt_0910[i].data;
				p_t1204_data[base_line_1204[3]+i]  = scl_p256_1204t_flt_1410[i].data;
				p_t1204_data[base_line_1204[4]+i]  = scl_p256_1204t_flt_1510[i].data;
				p_t1204_data[base_line_1204[5]+i]  = scl_p256_1204t_flt_1510[i].data;//dummy
				p_t1204_data[base_line_1204[6]+i]  = scl_p256_1204t_flt_1510[i].data;//dummy
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ_1212), p_shdw_db->top_h.sec_base[sec_typ_1212]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ_1206), p_shdw_db->top_h.sec_base[sec_typ_1206]);
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ_1204), p_shdw_db->top_h.sec_base[sec_typ_1204]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
static int PE_SHP_HW_F20_DownloadScl08tMainDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 size = 0, i = 0, sec_typ_0804 = 0;
	UINT32 base_line_0804[PE_DDR_F20_0804T_FLT_NUM];
	PE_DDR_DB_SHDW_REG_F20_T *p_shdw_db = gPE_DDR_DB_F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_F20_T *p_phys_db = gPE_DDR_DB_F20.phys.data;
	volatile UINT32 *p_t08_f_data = p_phys_db->t0804.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_t08_f_data);
		if (PE_KDRV_VER_O20)
		{
			/*1. 8t full */
			sec_typ_0804 = PE_DDR_F20_SEC_SCL_0804T;
			/* header */
			p_shdw_db->sec_d[sec_typ_0804].header.version   = 0x0;
			p_shdw_db->sec_d[sec_typ_0804].header.sec_type  = sec_typ_0804;
			p_shdw_db->sec_d[sec_typ_0804].header.item_num  = PE_DDR_F20_0804T_FLT_NUM;
			p_shdw_db->sec_d[sec_typ_0804].header.item_size = PE_DDR_F20_SCL_08T_FLT_SIZE;
			p_phys_db->t0804.header.version   = p_shdw_db->sec_d[sec_typ_0804].header.version;
			p_phys_db->t0804.header.sec_type  = p_shdw_db->sec_d[sec_typ_0804].header.sec_type;
			p_phys_db->t0804.header.item_num  = p_shdw_db->sec_d[sec_typ_0804].header.item_num;
			p_phys_db->t0804.header.item_size = p_shdw_db->sec_d[sec_typ_0804].header.item_size;
			/* data */
			size = (PE_DDR_F20_0804T_FLT_NUM * PE_DDR_F20_SCL_08T_FLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ_0804] = \
				p_shdw_db->top_h.sec_base[sec_typ_0804-1]+p_shdw_db->top_h.sec_size[sec_typ_0804-1];
			p_shdw_db->top_h.sec_size[sec_typ_0804] = size + sizeof(PE_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ_0804] = p_shdw_db->top_h.sec_base[sec_typ_0804];
			p_phys_db->top_h.sec_size[sec_typ_0804] = p_shdw_db->top_h.sec_size[sec_typ_0804];
			p_shdw_db->sec_d[sec_typ_0804].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ_0804] + sizeof(PE_DDR_F20_HEADER_T);

			/* wr ddr */
			base_line_0804[0] = 0;
			for (i=1; i<PE_DDR_F20_0804T_FLT_NUM; i++)
			{
				base_line_0804[i] = base_line_0804[i-1]+PE_DDR_F20_SCL_08T_FLT_SIZE;
			}
			for (i=0; i<PE_DDR_F20_SCL_08T_FLT_SIZE; i++)
			{
				p_t08_f_data[base_line_0804[0]+i]  = scl_p256_0804t_flt_0610[i].data;
				p_t08_f_data[base_line_0804[1]+i]  = scl_p256_0804t_flt_0610[i].data;//dummy
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ_0804), p_shdw_db->top_h.sec_base[sec_typ_0804]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_F20_DownloadSclDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	do{
		/* t12_m **************************************************************/
		ret = PE_SHP_HW_F20_DownloadScl12tMainDb();
		PE_SHP_HW_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_F20_DownloadScl12tMainDb() error.\n",__F__,__L__);
		/* t08_m **************************************************************/
		ret = PE_SHP_HW_F20_DownloadScl08tMainDb();
		PE_SHP_HW_O20_CHECK_CODE(ret, break, \
			"[%s,%d] PE_SHP_HW_F20_DownloadScl08tMainDb() error.\n",__F__,__L__);
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_F20_DownloadShpSqmCmnInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_F20_T *p_shdw_db = gPE_DDR_DB_F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_F20_T *p_phys_db = gPE_DDR_DB_F20.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_ui_sqm_vsd.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O20)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_F20_SEC_SHP_UI_SQM_VSD;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_F20_SHP_UI_SQM_VSD_SIZE;
			p_phys_db->shp_ui_sqm_vsd.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_ui_sqm_vsd.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_ui_sqm_vsd.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_ui_sqm_vsd.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_F20_SHP_UI_SQM_VSD_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_F20_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_F20_SHP_UI_SQM_VSD_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_vsd_cmn_init_f20[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
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
int PE_SHP_HW_F20_DownloadShpSqmDetailInitDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT32 i, size, sec_typ;
	UINT32 base_user_lut;
	PE_DDR_DB_SHDW_REG_F20_T *p_shdw_db = gPE_DDR_DB_F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_F20_T *p_phys_db = gPE_DDR_DB_F20.phys.data;
	volatile UINT32 *p_shp_sqm_data = p_phys_db->shp_sqmcmn__vsd.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_shp_sqm_data);
		if (PE_KDRV_VER_O20)
		{
			/* dnr_user **************************************************************/
			sec_typ = PE_DDR_F20_SEC_SHP_SQM_CMN_VSD;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = 1;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_F20_SHP_SQM_CMN_VSD_SIZE;
			p_phys_db->shp_sqmcmn__vsd.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->shp_sqmcmn__vsd.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->shp_sqmcmn__vsd.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->shp_sqmcmn__vsd.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = ( PE_DDR_F20_SHP_SQM_CMN_VSD_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_F20_HEADER_T);
			/* wr ddr */
			p_shp_sqm_data[0]  = 0x0;
			p_shp_sqm_data[1]  = 0x0;
			base_user_lut = 2;
			for (i= 0; i<PE_DDR_F20_SHP_SQM_CMN_VSD_SIZE-base_user_lut; i++)
			{
				p_shp_sqm_data[i+base_user_lut] = sqm_shp_vsd_dtl_init_f20[i];
			}
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}


/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for O20X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_HW_F20_SetReAllCtrl(void *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O20_BRINGUP
	UINT8 *pd;
	UINT16 *pd16;
	UINT32 *pd32;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_O20)
		{
			LX_PE_SHP_ALL_CMN_T *pp = (LX_PE_SHP_ALL_CMN_T *)pstParams;

			PE_CHECK_WINID(pp->win_id);

			pd = pp->shp_ui_main_vsd;

			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ui_main_vsd\n"
			"shp_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14]);
			pd = pp->shp_face_obj_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_fobj_vsd\n"
			"shp_fobj_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
			
			pd = pp->shp_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_cmn_vsd\n"
			"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24]);
			pd = pp->shp_djg_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_djg_vsd\n"
			"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);
			pd = pp->shp_map_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_map_cmn_vsd\n"
			"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_balance_vsd\n"
			"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ti_cmn_vsd\n"
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_chroma_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_chroma_vsd\n"
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);
			
			pd = pp->shp_ee_vsd;
			PE_SHP_HW_O20_DBG_PRINT("set[%d] : shp_ee_vsd\n"
			"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
			
			pd16 = pp->shp_dnn_sr_vsd;
			PE_SHP_HW_O20_DBG_PRINT("[%d]shp_dnn_sr_vsd\n"
			"shp_dnn_sr_vsd   [00]0x%02X\n",\
			pp->win_id, \
			pd16[0]);

			pd32 = pp->shp_ui_sqm_vsd;
			PE_SHP_HW_O20_DBG_PRINT("[%d]shp_ui_sqm_vsd:%d\n", pp->win_id, pp->shp_val);
			PE_SHP_HW_O20_DBG_PRINT( \
			"shp_ui_sqm_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_ui_sqm_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n",\
			pd32[0],	pd32[1],	pd32[2],	pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
			pd32[10],pd32[11],	pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],	pd32[17], pd32[18],  pd32[19], \
			pd32[20],pd32[21],	pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],	pd32[27], pd32[28],  pd32[29],\
			pd32[30],pd32[31],	pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],	pd32[37], pd32[38],  pd32[39]);

			pd32 = pp->shp_sqm_cmn_vsd;
			PE_SHP_HW_O20_DBG_PRINT("[%d]shp_sqm_cmn_vsd:%d\n", pp->win_id, pp->shp_val);
			PE_SHP_HW_O20_DBG_PRINT( \
			"shp_sqm_cmn_vsd[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[30]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[40]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"shp_sqm_cmn_vsd[50]0x%08X\n",\
			pd32[0],  pd32[1],  pd32[2],  pd32[3], pd32[4],  pd32[5],  pd32[6],  pd32[7], pd32[8],  pd32[9], \
			pd32[10],pd32[11],  pd32[12],  pd32[13], pd32[14],  pd32[15],  pd32[16],  pd32[17], pd32[18],  pd32[19], \
			pd32[20],pd32[21],  pd32[22],  pd32[23], pd32[24],  pd32[25],  pd32[26],  pd32[27], pd32[28],  pd32[29],\
			pd32[30],pd32[31],  pd32[32],  pd32[33], pd32[34],  pd32[35],  pd32[36],  pd32[37], pd32[38],  pd32[39],\
			pd32[40],pd32[41],  pd32[42],  pd32[43], pd32[34],  pd32[45],  pd32[46],  pd32[47], pd32[48],  pd32[49],\
			pd32[50]);

			if(PE_CHECK_WIN2(pp->win_id))
			{
				PE_CHPI_SHP_HW_F20_SetCtrl(pstParams);/* F20_TBL */
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	#endif /*PE_HW_O20_BRINGUP*/
	return ret;
}

int PE_SHP_HW_O20_SetBypassObc(int bypass)
{
	int ret = RET_OK;
	do {
		if(PE_KDRV_VER_O20)
		{
			/* RCE */
			if(bypass)
			{
				PE_VSD_HW_O20_RCE_O_WR01(reg_rce_objt_ctrl_00, reg_psp_en, 0x0);
				PE_VSD_HW_O20_RCE_F_WR01(reg_rce_face_ctrl_00, reg_psp_en, 0x0);
			}
			else
			{
				PE_VSD_HW_O20_RCE_O_WR01(reg_rce_objt_ctrl_00, reg_psp_en, _g_pe_rco_hw_param_data_o20.reg_user.data->reg_rce_objt_ctrl_00.reg_psp_en);
				PE_VSD_HW_O20_RCE_F_WR01(reg_rce_face_ctrl_00, reg_psp_en, _g_pe_rcf_hw_param_data_o20.reg_user.data->reg_rce_face_ctrl_00.reg_psp_en);
			}
		}
		else
		{
			PE_SHP_HW_O20_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

