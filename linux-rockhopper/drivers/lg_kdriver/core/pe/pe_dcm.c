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

/** @file pe_dcm.c
 *
 *  driver for picture enhance dynamic contrast module functions.
 *  ( used only within kdriver )
 *	- dynamic contrast, saturation enhancement.
 *	
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
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
#include "pe_win.h"
#include "pe_dcm.h"
#include "pe_etc_hw.h"
#include "pe_dcm_hw.h"
#include "pe_drc_def.h"
#include "pe_drc_lut_hw_m16p.h"
#include "pe_drc_lut_hw_init.h"
#include "pe_drc_lut_hw_f20.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_DCM_DBG_PRINT(fmt, args...)	\
	if (_g_dcm_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/
typedef struct
{
	int (*hw_init)(PE_CFG_CTRL_T *pstParams);
	int (*set_default)(LX_PE_DEFAULT_SETTINGS_T *pstParams);
	int (*set_debug)(LX_PE_DBG_SETTINGS_T *pstParams);
	int (*set_dce_config)(LX_PE_DCM_DCE_CONF_T *pstParams);
	int (*get_dce_config)(LX_PE_DCM_DCE_CONF_T *pstParams);
	int (*set_dce_lut)(LX_PE_DCM_DCE_LUT_T *pstParams);
	int (*get_dce_lut)(LX_PE_DCM_DCE_LUT_T *pstParams);
	int (*set_dse_lut)(LX_PE_DCM_DSE_LUT_T *pstParams);
	int (*get_dse_lut)(LX_PE_DCM_DSE_LUT_T *pstParams);
	int (*set_hdr_lut)(LX_PE_DCM_HDR_LUT_T *pstParams);
	int (*get_hdr_lut)(LX_PE_DCM_HDR_LUT_T *pstParams);
	int (*set_dce_blending)(LX_PE_DCM_BLENDING_T *pstParams);
	int (*get_dce_blending)(LX_PE_DCM_BLENDING_T *pstParams);
	int (*set_dce_drc_mode)(LX_PE_DCM_DRC_MODE_T *pstParams);
	int (*get_dce_drc_mode)(LX_PE_DCM_DRC_MODE_T *pstParams);
	int (*set_hdr_mode)(LX_PE_DCM_HDR_MODE_T *pstParams);
	int (*get_hdr_mode)(LX_PE_DCM_HDR_MODE_T *pstParams);
	int (*set_dse_ctrl)(void *pstParams);
	int (*get_dse_ctrl)(void *pstParams);
	int (*set_drc_cuv_old)(void *pstParams);
	int (*set_drc_cuv)(void *pstParams);
	int (*get_drc_cuv)(void *pstParams);
	int (*set_drc_ctrl)(void *pstParams);
	int (*set_drc_ctrl2)(void *pstParams);
	int (*get_drc_ctrl)(void *pstParams);
	int (*set_obc_ctrl)(void *pstParams);
	int (*get_obc_ctrl)(void *pstParams);
	int (*get_obc_data)(void *pstParams);
	int (*set_dtm_lut)(void *pstParams);
	int (*get_dtm_lut)(void *pstParams);
	int (*set_dce_accel)(void);
	int (*set_dse_ctrl2)(void *pstParams);
	int (*get_dse_ctrl2)(void *pstParams);
	int (*set_dce_lut2)(void *pstParams);
	int (*get_dce_lut2)(void *pstParams);
	int (*set_dce_db)(void *pstParams);
	int (*get_dce_db)(int idexDb, int lengthOfData);
	int (*set_dce_lut3)(void *pstParams);
	int (*get_dce_lut3)(void *pstParams);
	int (*get_dce_db_addr)(void);
	int (*set_dbc_db)(void *pstParams);
	int (*get_dbc_db)(void);
}
PE_DCM_CB_FUNC_T;

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Functions
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
static PE_DCM_CB_FUNC_T _g_pe_dcm_cb_fn;
static UINT32 _g_dcm_trace=0x0;	//default should be off.

/*============================================================================
	Implementation Group
============================================================================*/
/**
 * register call back functions
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_dcm_cb_fn, 0, sizeof(PE_DCM_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_dcm_cb_fn.hw_init 			= PE_DCM_HW_O26_Init;
			_g_pe_dcm_cb_fn.set_default 		= NULL;
			_g_pe_dcm_cb_fn.set_debug			= PE_DCM_HW_O26_SetDebugSettings;
			_g_pe_dcm_cb_fn.set_dce_config		= NULL;
			_g_pe_dcm_cb_fn.get_dce_config		= NULL;
			_g_pe_dcm_cb_fn.set_dce_lut 		= PE_DCM_HW_O26_SetDceLut;
			_g_pe_dcm_cb_fn.get_dce_lut 		= PE_DCM_HW_O26_GetDceLut;
			_g_pe_dcm_cb_fn.set_dse_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_dse_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_dce_blending	= NULL;
			_g_pe_dcm_cb_fn.get_dce_blending	= NULL;
			_g_pe_dcm_cb_fn.set_dce_drc_mode	= PE_DCM_HW_O26_SetDceDrcMode;
			_g_pe_dcm_cb_fn.get_dce_drc_mode	= PE_DCM_HW_O26_GetDceDrcMode;
			_g_pe_dcm_cb_fn.set_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.set_dse_ctrl		= PE_DCM_HW_O26_SetDseCtrl;
			_g_pe_dcm_cb_fn.get_dse_ctrl		= NULL;
			_g_pe_dcm_cb_fn.set_drc_cuv_old		= PE_DCM_HW_O26_SetDrcCurv_Old;
			_g_pe_dcm_cb_fn.set_drc_cuv 		= PE_DCM_HW_O26_SetDrcCurv;
			_g_pe_dcm_cb_fn.get_drc_cuv 		= NULL;
			_g_pe_dcm_cb_fn.set_drc_ctrl		= PE_DCM_HW_O26_SetDrcParam;
			_g_pe_dcm_cb_fn.set_drc_ctrl2		= PE_DCM_HW_O26_SetDrcParam2;
			_g_pe_dcm_cb_fn.get_drc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.set_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_data		= NULL;
			_g_pe_dcm_cb_fn.set_dtm_lut 		= PE_DCM_HW_O26_SetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.get_dtm_lut 		= PE_DCM_HW_O26_GetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.set_dce_accel 		= PE_DCM_HW_O26_SetAccelDceLut;
			_g_pe_dcm_cb_fn.set_dse_ctrl2		= //PE_DCM_HW_O26_SetDseCtrl2;// dse ctrl for webos5.0
			_g_pe_dcm_cb_fn.get_dse_ctrl2		= //PE_DCM_HW_O26_GetDseCtrl2;
			_g_pe_dcm_cb_fn.set_dce_lut2 		= PE_DCM_HW_O26_SetDceLut2; // o24 only
			_g_pe_dcm_cb_fn.get_dce_lut2 		= NULL;//PE_DCM_HW_O26_GetChrLut;
			_g_pe_dcm_cb_fn.set_dce_db 			= PE_DCM_HW_O26F22_DownloadLibDb;
			_g_pe_dcm_cb_fn.get_dce_db 			= PE_DCM_HW_O26F22_GetDCDB;
			_g_pe_dcm_cb_fn.set_dce_lut3 		= PE_DCM_HW_O26F22_SetDceLut;// o24+f22
			_g_pe_dcm_cb_fn.get_dce_lut3 		= NULL;
			_g_pe_dcm_cb_fn.get_dce_db_addr		= PE_DCM_HW_O26F22_GetDCDBAddr;
			_g_pe_dcm_cb_fn.set_dbc_db 			= PE_DCM_HW_O26F22_DownloadDBCDb;
			_g_pe_dcm_cb_fn.get_dbc_db 			= PE_DCM_HW_O26F22_GetDBCDb;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_dcm_cb_fn.hw_init 			= PE_DCM_HW_O24_Init;
			_g_pe_dcm_cb_fn.set_default 		= NULL;
			_g_pe_dcm_cb_fn.set_debug			= PE_DCM_HW_O24_SetDebugSettings;
			_g_pe_dcm_cb_fn.set_dce_config		= NULL;
			_g_pe_dcm_cb_fn.get_dce_config		= NULL;
			_g_pe_dcm_cb_fn.set_dce_lut 		= PE_DCM_HW_O24_SetDceLut;
			_g_pe_dcm_cb_fn.get_dce_lut 		= PE_DCM_HW_O24_GetDceLut;
			_g_pe_dcm_cb_fn.set_dse_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_dse_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_dce_blending	= NULL;
			_g_pe_dcm_cb_fn.get_dce_blending	= NULL;
			_g_pe_dcm_cb_fn.set_dce_drc_mode	= PE_DCM_HW_O24_SetDceDrcMode;
			_g_pe_dcm_cb_fn.get_dce_drc_mode	= PE_DCM_HW_O24_GetDceDrcMode;
			_g_pe_dcm_cb_fn.set_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.set_dse_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_dse_ctrl		= NULL;
			_g_pe_dcm_cb_fn.set_drc_cuv 		= PE_DCM_HW_O24_SetDrcCurv;
			_g_pe_dcm_cb_fn.get_drc_cuv 		= NULL;
			_g_pe_dcm_cb_fn.set_drc_ctrl		= PE_DCM_HW_O24_SetDrcParam;
			_g_pe_dcm_cb_fn.set_drc_ctrl2		= PE_DCM_HW_O24_SetDrcParam2;
			_g_pe_dcm_cb_fn.get_drc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.set_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_data		= NULL;
			_g_pe_dcm_cb_fn.set_dtm_lut 		= PE_DCM_HW_O24_SetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.get_dtm_lut 		= PE_DCM_HW_O24_GetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.set_dce_accel 		= PE_DCM_HW_O24_SetAccelDceLut;
			_g_pe_dcm_cb_fn.set_dse_ctrl2		= PE_DCM_HW_O24_SetDseCtrl2;// dse ctrl for webos5.0
			_g_pe_dcm_cb_fn.get_dse_ctrl2		= PE_DCM_HW_O24_GetDseCtrl2;
			_g_pe_dcm_cb_fn.set_dce_lut2 		= PE_DCM_HW_O24_SetDceLut2; // o24 only
			_g_pe_dcm_cb_fn.get_dce_lut2 		= NULL;//PE_DCM_HW_O24_GetChrLut;
			_g_pe_dcm_cb_fn.set_dce_db 			= PE_DCM_HW_O24F22_DownloadLibDb;
			_g_pe_dcm_cb_fn.get_dce_db 			= PE_DCM_HW_O24F22_GetDCDB;
			_g_pe_dcm_cb_fn.set_dce_lut3 		= PE_DCM_HW_O24F22_SetDceLut;// o24+f22
			_g_pe_dcm_cb_fn.get_dce_lut3 		= NULL;
			_g_pe_dcm_cb_fn.get_dce_db_addr		= PE_DCM_HW_O24F22_GetDCDBAddr;
			_g_pe_dcm_cb_fn.set_dbc_db 			= PE_DCM_HW_O24F22_DownloadDBCDb;
			_g_pe_dcm_cb_fn.get_dbc_db 			= PE_DCM_HW_O24F22_GetDBCDb;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_dcm_cb_fn.hw_init 			= PE_DCM_HW_M23_Init;
			_g_pe_dcm_cb_fn.set_debug			= PE_DCM_HW_M23_SetDebugSettings;
			_g_pe_dcm_cb_fn.set_dce_lut 		= PE_DCM_HW_M23_SetDceLut;
			_g_pe_dcm_cb_fn.get_dce_lut 		= PE_DCM_HW_M23_GetDceLut;
			_g_pe_dcm_cb_fn.set_dce_drc_mode	= PE_DCM_HW_M23_SetDceDrcMode;
			_g_pe_dcm_cb_fn.get_dce_drc_mode	= PE_DCM_HW_M23_GetDceDrcMode;
			_g_pe_dcm_cb_fn.set_dse_ctrl		= PE_DCM_HW_M23_SetDseCtrl;// dse ctrl for webos5.0
			_g_pe_dcm_cb_fn.get_dse_ctrl		= PE_DCM_HW_M23_GetDseCtrl;
			_g_pe_dcm_cb_fn.set_drc_cuv 		= PE_DCM_HW_M23_SetDrcCurv;
			_g_pe_dcm_cb_fn.set_drc_ctrl		= PE_DCM_HW_M23_SetDrcParam;
			_g_pe_dcm_cb_fn.set_drc_ctrl2		= PE_DCM_HW_M23_SetDrcParam2;
			_g_pe_dcm_cb_fn.set_dtm_lut 		= PE_DCM_HW_M23_SetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.get_dtm_lut 		= PE_DCM_HW_M23_GetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.set_dce_accel 		= PE_DCM_HW_M23_SetAccelDceLut;
			_g_pe_dcm_cb_fn.set_dse_ctrl2		= PE_DCM_HW_M23_SetDseCtrl2;// dse ctrl for webos5.0
			_g_pe_dcm_cb_fn.get_dse_ctrl2		= PE_DCM_HW_M23_GetDseCtrl2;
			_g_pe_dcm_cb_fn.set_dce_lut2 		= PE_DCM_HW_M23_SetDceLut2; // o22 only
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_dcm_cb_fn.hw_init 			= PE_DCM_HW_O22_Init;
			_g_pe_dcm_cb_fn.set_default 		= NULL;
			_g_pe_dcm_cb_fn.set_debug			= PE_DCM_HW_O22_SetDebugSettings;
			_g_pe_dcm_cb_fn.set_dce_config		= NULL;
			_g_pe_dcm_cb_fn.get_dce_config		= NULL;
			_g_pe_dcm_cb_fn.set_dce_lut 		= PE_DCM_HW_O22_SetDceLut;
			_g_pe_dcm_cb_fn.get_dce_lut 		= PE_DCM_HW_O22_GetDceLut;
			_g_pe_dcm_cb_fn.set_dse_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_dse_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_dce_blending	= NULL;
			_g_pe_dcm_cb_fn.get_dce_blending	= NULL;
			_g_pe_dcm_cb_fn.set_dce_drc_mode	= PE_DCM_HW_O22_SetDceDrcMode;
			_g_pe_dcm_cb_fn.get_dce_drc_mode	= PE_DCM_HW_O22_GetDceDrcMode;
			_g_pe_dcm_cb_fn.set_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.set_dse_ctrl		= PE_DCM_HW_O22_SetDseCtrl;// dse ctrl for webos5.0
			_g_pe_dcm_cb_fn.get_dse_ctrl		= PE_DCM_HW_O22_GetDseCtrl;
			_g_pe_dcm_cb_fn.set_drc_cuv 		= PE_DCM_HW_O22_SetDrcCurv;
			_g_pe_dcm_cb_fn.get_drc_cuv 		= NULL;
			_g_pe_dcm_cb_fn.set_drc_ctrl		= PE_DCM_HW_O22_SetDrcParam;
			_g_pe_dcm_cb_fn.set_drc_ctrl2		= PE_DCM_HW_O22_SetDrcParam2;
			_g_pe_dcm_cb_fn.get_drc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.set_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_data		= NULL;
			_g_pe_dcm_cb_fn.set_dtm_lut 		= PE_DCM_HW_O22_SetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.get_dtm_lut 		= PE_DCM_HW_O22_GetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.set_dce_accel 		= PE_DCM_HW_O22_SetAccelDceLut;
			_g_pe_dcm_cb_fn.set_dse_ctrl2		= PE_DCM_HW_O22_SetDseCtrl2;// dse ctrl for webos5.0
			_g_pe_dcm_cb_fn.get_dse_ctrl2		= PE_DCM_HW_O22_GetDseCtrl2;
			_g_pe_dcm_cb_fn.set_dce_lut2 		= PE_DCM_HW_O22_SetDceLut2; // o22 only
			_g_pe_dcm_cb_fn.get_dce_lut2 		= NULL;//PE_DCM_HW_O22_GetChrLut;
			_g_pe_dcm_cb_fn.set_dce_db 			= PE_DCM_HW_O22F22_DownloadLibDb;
			_g_pe_dcm_cb_fn.get_dce_db 			= PE_DCM_HW_O22F22_GetDCDB;
			_g_pe_dcm_cb_fn.set_dce_lut3 		= PE_DCM_HW_O22F22_SetDceLut;// o22+f22
			_g_pe_dcm_cb_fn.get_dce_lut3 		= NULL;
			_g_pe_dcm_cb_fn.get_dce_db_addr		= PE_DCM_HW_O22F22_GetDCDBAddr;
			_g_pe_dcm_cb_fn.set_dbc_db 			= PE_DCM_HW_O22F22_DownloadDBCDb;
			_g_pe_dcm_cb_fn.get_dbc_db 			= PE_DCM_HW_O22F22_GetDBCDb;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_dcm_cb_fn.hw_init 			= PE_DCM_HW_E60_Init;
			_g_pe_dcm_cb_fn.set_default 		= NULL;
			_g_pe_dcm_cb_fn.set_debug			= PE_DCM_HW_E60_SetDebugSettings;
			_g_pe_dcm_cb_fn.set_dce_config		= NULL;
			_g_pe_dcm_cb_fn.get_dce_config		= NULL;
			_g_pe_dcm_cb_fn.set_dce_lut 		= PE_DCM_HW_E60_SetDceLut;
			_g_pe_dcm_cb_fn.get_dce_lut 		= PE_DCM_HW_E60_GetDceLut;
			_g_pe_dcm_cb_fn.set_dse_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_dse_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_dce_blending	= NULL;
			_g_pe_dcm_cb_fn.get_dce_blending	= NULL;
			_g_pe_dcm_cb_fn.set_dce_drc_mode	= PE_DCM_HW_E60_SetDceDrcMode;
			_g_pe_dcm_cb_fn.get_dce_drc_mode	= PE_DCM_HW_E60_GetDceDrcMode;
			_g_pe_dcm_cb_fn.set_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.set_dse_ctrl		= PE_DCM_HW_E60_SetDseCtrl;// dse ctrl for webos5.0
			_g_pe_dcm_cb_fn.get_dse_ctrl		= PE_DCM_HW_E60_GetDseCtrl;
			_g_pe_dcm_cb_fn.set_drc_cuv 		= PE_DCM_HW_E60_SetDrcCurv;
			_g_pe_dcm_cb_fn.get_drc_cuv 		= NULL;
			_g_pe_dcm_cb_fn.set_drc_ctrl		= PE_DCM_HW_E60_SetDrcParam;
			_g_pe_dcm_cb_fn.get_drc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.set_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_data		= NULL;
			_g_pe_dcm_cb_fn.set_dtm_lut 		= PE_DCM_HW_E60_SetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.get_dtm_lut 		= PE_DCM_HW_E60_GetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.set_dce_accel 		= PE_DCM_HW_E60_SetAccelDceLut;
			_g_pe_dcm_cb_fn.set_dse_ctrl2		= PE_DCM_HW_E60_SetDseCtrl2;// dse ctrl for webos5.0
			_g_pe_dcm_cb_fn.get_dse_ctrl2		= PE_DCM_HW_E60_GetDseCtrl2;
			_g_pe_dcm_cb_fn.set_dce_lut2 		= PE_DCM_HW_E60_SetDceLut2; // e60 only
			_g_pe_dcm_cb_fn.get_dce_lut2 		= NULL;//PE_DCM_HW_E60_GetChrLut;
			_g_pe_dcm_cb_fn.set_dce_db 			= PE_DCM_HW_E60F20_DownloadLibDb;
			_g_pe_dcm_cb_fn.get_dce_db 			= PE_DCM_HW_E60F20_GetDCDB;
			_g_pe_dcm_cb_fn.set_dce_lut3 		= PE_DCM_HW_E60F20_SetDceLut;// e60+f20
			_g_pe_dcm_cb_fn.get_dce_lut3 		= NULL;
			_g_pe_dcm_cb_fn.get_dce_db_addr		= PE_DCM_HW_E60F20_GetDCDBAddr;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_dcm_cb_fn.hw_init 			= PE_DCM_HW_O20_Init;
			_g_pe_dcm_cb_fn.set_default 		= NULL;
			_g_pe_dcm_cb_fn.set_debug			= PE_DCM_HW_O20_SetDebugSettings;
			_g_pe_dcm_cb_fn.set_dce_config		= PE_DCM_HW_O20_SetDceConfig;
			_g_pe_dcm_cb_fn.get_dce_config		= PE_DCM_HW_O20_GetDceConfig;
			_g_pe_dcm_cb_fn.set_dce_lut 		= PE_DCM_HW_O20_SetDceLut;//dce lut for webos5.0
			_g_pe_dcm_cb_fn.get_dce_lut 		= PE_DCM_HW_O20_GetDceLut;
			_g_pe_dcm_cb_fn.set_dse_lut 		= PE_DCM_HW_O20_SetDseLut;
			_g_pe_dcm_cb_fn.get_dse_lut 		= PE_DCM_HW_O20_GetDseLut;
			_g_pe_dcm_cb_fn.set_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_lut 		= NULL;
			_g_pe_dcm_cb_fn.set_dce_blending	= PE_DCM_HW_O20_SetDceBlendingCtrl;
			_g_pe_dcm_cb_fn.get_dce_blending	= PE_DCM_HW_O20_GetDceBlendingCtrl;
			_g_pe_dcm_cb_fn.set_dce_drc_mode	= PE_DCM_HW_O20_SetDceDrcMode;
			_g_pe_dcm_cb_fn.get_dce_drc_mode	= PE_DCM_HW_O20_GetDceDrcMode;
			_g_pe_dcm_cb_fn.set_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.get_hdr_mode		= NULL;
			_g_pe_dcm_cb_fn.set_dse_ctrl		= PE_DCM_HW_O20_SetDseCtrl;
			_g_pe_dcm_cb_fn.get_dse_ctrl		= PE_DCM_HW_O20_GetDseCtrl;
			_g_pe_dcm_cb_fn.set_drc_cuv 		= PE_DCM_HW_O20_SetDrcCurv;
			_g_pe_dcm_cb_fn.get_drc_cuv 		= NULL;
			_g_pe_dcm_cb_fn.set_drc_ctrl		= PE_DCM_HW_O20_SetDrcParam;
			_g_pe_dcm_cb_fn.get_drc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.set_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_ctrl		= NULL;
			_g_pe_dcm_cb_fn.get_obc_data		= PE_DCM_HW_O20_GetObcData;
			_g_pe_dcm_cb_fn.set_dtm_lut 		= PE_DCM_HW_O20_SetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.get_dtm_lut 		= PE_DCM_HW_O20_GetDtmLut;//TODO:incompatible pointer type
			_g_pe_dcm_cb_fn.set_dce_accel 		= PE_DCM_HW_O20_SetAccelDceLut;
			_g_pe_dcm_cb_fn.set_dse_ctrl2		= PE_DCM_HW_O20_SetDseCtrl2;
			_g_pe_dcm_cb_fn.get_dse_ctrl2		= PE_DCM_HW_O20_GetDseCtrl2;
			_g_pe_dcm_cb_fn.set_dce_lut2 		= PE_DCM_HW_O20_SetDceLut2;//dce lut for webos6.0
			_g_pe_dcm_cb_fn.get_dce_lut2 		= NULL;//PE_DCM_HW_O20_GetChrLut;
		}
		else
		#endif
		
		{
			PE_PRINT_ERROR("[%x,%x] kdrv chip ver is wrong.\n", \
				PE_CHIP_VER, g_pe_kdrv_ver_mask);
			ret = RET_ERROR;
		}
	}while (0);
	return ret;
}
/**
 * init dynamic contrast module
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.hw_init)
		{
			ret = _g_pe_dcm_cb_fn.hw_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_init() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of dcm setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_DCM_SET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_DCM_DBG_PRINT("S TABL %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size, 0, 16) * sizeof(UINT32);\
			PE_CHECK_CODE(!bufsize, break, \
				"[%s,%d] bufsize zero.\n", __F__, __L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CHECK_CODE(!p_data, break, \
				"[%s,%d] p_data is null.\n", __F__, __L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_from_user error.\n", __F__, __L__);\
			param.win_id = p_rcv->win_id;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_DCM_DBG_PRINT("E TABL %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

#define PE_DCM_SET_TLWO(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size, 0, 16) * sizeof(UINT32);\
			PE_CHECK_CODE(!bufsize, break, \
				"[%s,%d] bufsize zero.\n", __F__, __L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CHECK_CODE(!p_data, break, \
				"[%s,%d] p_data is null.\n", __F__, __L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_from_user error.\n", __F__, __L__);\
			param.win_id = p_rcv->win_id;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

#define PE_DCM_SET_FUNC(_struct, _func, _void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_DCM_DBG_PRINT("S FUNC %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_DCM_DBG_PRINT("E FUNC %s\n", #_struct);\
		}while (0);\
	}\
	break

/** set func without start,
*   end print(WOPT:WithOut PRint) because of too many prints */
#define PE_DCM_SET_WOPR(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_DCM_SET_TLWO(LX_PE_DCM_DCE_LUT_T,		PE_DCM_SetDceLut);
		PE_DCM_SET_TLWO(LX_PE_DCM_DSE_LUT_T,		PE_DCM_SetDseLut);
		PE_DCM_SET_TLWO(LX_PE_DCM_HDR_LUT_T,		PE_DCM_SetHdrLut);
		PE_DCM_SET_FUNC(LX_PE_DCM_DCE_CONF_T,		PE_DCM_SetDceConfig,		_STRUCT_INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DCM_BLENDING_T,		PE_DCM_SetDceBlendingCtrl,	_STRUCT_INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DCM_DRC_MODE_T,		PE_DCM_SetDceDrcMode,		_STRUCT_INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_DCM_SetDefaultSettings,	_STRUCT_INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_DCM_SetDebugSettings,	_STRUCT_INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DCM_HDR_MODE_T, 		PE_DCM_SetHdrMode,			_STRUCT_INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DCM_DSE_CTRL_T,		PE_DCM_SetDseCtrl,			_VOID___INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DCM_DSE_CTRL2_T,		PE_DCM_SetDseCtrl,			_VOID___INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DCM_DRC_CUV_T,		PE_DCM_SetDrcCurv,			_VOID___INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DCM_DRC_CONT_T,		PE_DCM_SetDrcCtrl,			_VOID___INPUT_);
		PE_DCM_SET_FUNC(LX_PE_DCM_OBC_CTRL_T,		PE_DCM_SetObcCtrl,			_VOID___INPUT_);

		default:
		{
			PE_PRINT_ERROR("functype(%d) default case.\n", functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of dcm getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_DCM_GET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_DCM_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size, 0, 16) * sizeof(UINT32);\
			PE_CHECK_CODE(!bufsize, break, \
				"[%s,%d] bufsize zero.\n", __F__, __L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CHECK_CODE(!p_data, break, \
				"[%s,%d] p_data is null.\n", __F__, __L__);\
			param.win_id = p_rcv->win_id;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_to_user error.\n", __F__, __L__);\
			PE_DCM_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

#define PE_DCM_GET_FUNC(_struct, _func, _void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_DCM_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
			PE_DCM_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

/** get func without start,
*   end print(WOPT:WithOut PRint) because of too many prints */
#define PE_DCM_GET_WOPR(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_DCM_GET_TABL(LX_PE_DCM_DCE_LUT_T,		PE_DCM_GetDceLut);
		PE_DCM_GET_TABL(LX_PE_DCM_DSE_LUT_T,		PE_DCM_GetDseLut);
		PE_DCM_GET_TABL(LX_PE_DCM_HDR_LUT_T,		PE_DCM_GetHdrLut);
		PE_DCM_GET_FUNC(LX_PE_DCM_DCE_CONF_T,		PE_DCM_GetDceConfig,		_STRUCT_INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_BLENDING_T,		PE_DCM_GetDceBlendingCtrl,	_STRUCT_INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_DRC_MODE_T,		PE_DCM_GetDceDrcMode,		_STRUCT_INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_HDR_MODE_T, 	PE_DCM_GetHdrMode,			_STRUCT_INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_DSE_CTRL_T,		PE_DCM_GetDseCtrl,			_VOID___INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_DSE_CTRL2_T,	PE_DCM_GetDseCtrl,			_VOID___INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_DRC_CUV_T,		PE_DCM_GetDrcCurv,			_VOID___INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_DRC_CONT_T,		PE_DCM_GetDrcCtrl,  		_VOID___INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_OBC_CTRL_T,		PE_DCM_GetObcCtrl,  		_VOID___INPUT_);
		PE_DCM_GET_FUNC(LX_PE_DCM_OBC_DATA_T,		PE_DCM_GetObcData,  		_VOID___INPUT_);
		default:
		{
			PE_PRINT_ERROR("functype(%d) default case.\n", functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}
/**
 * default setting
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_DBG_PRINT("[win id:%d]\n", pstParams->win_id);
	}while (0);
	return ret;
}
/**
 * debug setting
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if (pstParams->type&LX_PE_DBG_LV)
		{
			_g_dcm_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(DCM)))? 0x1:0x0;
		}
		if(_g_pe_dcm_cb_fn.set_debug)
		{
			ret = _g_pe_dcm_cb_fn.set_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_debug() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dce config
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_CONF_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dce_config)
		{
			ret = _g_pe_dcm_cb_fn.set_dce_config(pstParams);
			PE_CHECK_CODE(ret, break, "set_dce_config() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dce config
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DCE_CONF_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dce_config)
		{
			ret = _g_pe_dcm_cb_fn.get_dce_config(pstParams);
			PE_CHECK_CODE(ret, break, "get_dce_config() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dce lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dce_lut)
		{
			ret = _g_pe_dcm_cb_fn.set_dce_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_dce_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * get dce lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dce_lut)
		{
			ret = _g_pe_dcm_cb_fn.get_dce_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_dce_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * set dse lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dse_lut)
		{
			ret = _g_pe_dcm_cb_fn.set_dse_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_dse_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * get dse lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DSE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dse_lut)
		{
			ret = _g_pe_dcm_cb_fn.get_dse_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_dse_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * set hdr lut
 *
 * @param   *pstParams [in] LX_PE_DCM_HDR_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetHdrLut(LX_PE_DCM_HDR_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_hdr_lut)
		{
			ret = _g_pe_dcm_cb_fn.set_hdr_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_hdr_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * get hdr lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_HDR_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetHdrLut(LX_PE_DCM_HDR_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_hdr_lut)
		{
			ret = _g_pe_dcm_cb_fn.get_hdr_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_hdr_lut() error.\n");
		}
	}while (0);	
	return ret;
}

/**
 * set dce blending control
 *
 * @param   *pstParams [in] LX_PE_DCM_BLENDING_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dce_blending)
		{
			ret = _g_pe_dcm_cb_fn.set_dce_blending(pstParams);
			PE_CHECK_CODE(ret, break, "set_dce_blending() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dce blending control
 *
 * @param   *pstParams [in/out] LX_PE_DCM_BLENDING_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dce_blending)
		{
			ret = _g_pe_dcm_cb_fn.get_dce_blending(pstParams);
			PE_CHECK_CODE(ret, break, "get_dce_blending() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dce drc mode
 *
 * @param   *pstParams [in] LX_PE_DCM_DRC_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dce_drc_mode)
		{
			ret = _g_pe_dcm_cb_fn.set_dce_drc_mode(pstParams);
			PE_CHECK_CODE(ret, break, "set_dce_drc_mode() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dce drc mode
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DRC_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dce_drc_mode)
		{
			ret = _g_pe_dcm_cb_fn.get_dce_drc_mode(pstParams);
			PE_CHECK_CODE(ret, break, "get_dce_drc_mode() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set hdr mode
 *
 * @param   *pstParams [in] LX_PE_DCM_HDR_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetHdrMode(LX_PE_DCM_HDR_MODE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_hdr_mode)
		{
			ret = _g_pe_dcm_cb_fn.set_hdr_mode(pstParams);
			PE_CHECK_CODE(ret, break, "set_hdr_mode() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get hdr mode
 *
 * @param   *pstParams [in/out] LX_PE_DCM_HDR_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetHdrMode(LX_PE_DCM_HDR_MODE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_hdr_mode)
		{
			ret = _g_pe_dcm_cb_fn.get_hdr_mode(pstParams);
			PE_CHECK_CODE(ret, break, "get_hdr_mode() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dse control
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dse_ctrl)
		{
			ret = _g_pe_dcm_cb_fn.set_dse_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_dse_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dse control
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dse_ctrl)
		{
			ret = _g_pe_dcm_cb_fn.get_dse_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_dse_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dse control
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDrcCurv(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_drc_cuv)
		{
			ret = _g_pe_dcm_cb_fn.set_drc_cuv(pstParams);
			PE_CHECK_CODE(ret, break, "set_drc_cuv() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dse control
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDrcCurv_Old(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_drc_cuv_old)
		{
			ret = _g_pe_dcm_cb_fn.set_drc_cuv(pstParams);
			PE_CHECK_CODE(ret, break, "set_drc_cuv() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get dse control
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDrcCurv(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_drc_cuv)
		{
			ret = _g_pe_dcm_cb_fn.get_drc_cuv(pstParams);
			PE_CHECK_CODE(ret, break, "get_dse_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set drc control
 *
 * @param   *pstParams [in] LX_PE_DCM_DRC_CONT1_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDrcCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_drc_ctrl)
		{
			ret = _g_pe_dcm_cb_fn.set_drc_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_dse_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set drc control for webOS23
 *
 * @param   *pstParams [in] LX_PE_DCM_DRC_CONT2_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDrcCtrl2(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_drc_ctrl2)
		{
			ret = _g_pe_dcm_cb_fn.set_drc_ctrl2(pstParams);
			PE_CHECK_CODE(ret, break, "set_dse_ctrl2() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dse control
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DSE_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDrcCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_drc_ctrl)
		{
			ret = _g_pe_dcm_cb_fn.get_drc_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_drc_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set obc control
 *
 * @param   *pstParams [in/out] LX_PE_DCM_OBC_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_obc_ctrl)
		{
			ret = _g_pe_dcm_cb_fn.set_obc_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_obc_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get obc control
 *
 * @param   *pstParams [in/out] LX_PE_DCM_OBC_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_obc_ctrl)
		{
			ret = _g_pe_dcm_cb_fn.get_obc_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_obc_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get obc control
 *
 * @param   *pstParams [in/out] LX_PE_DCM_OBC_DATA_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetObcData(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_obc_data)
		{
			ret = _g_pe_dcm_cb_fn.get_obc_data(pstParams);
			PE_CHECK_CODE(ret, break, "get_obc_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dtm lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DTM_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDtmLut(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dtm_lut)
		{
			ret = _g_pe_dcm_cb_fn.set_dtm_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_dtm_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * get dtm lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DTM_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDtmLut(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dtm_lut)
		{
			ret = _g_pe_dcm_cb_fn.get_dtm_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_dtm_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * set Dcm lut accel mode for DGMS (prevent recurrence) used only to test
 *
 * @param   *pstParams [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetAccelDceLut(void)
{
	int ret = RET_OK;
	do{
		if(_g_pe_dcm_cb_fn.set_dce_accel)
		{
			ret = _g_pe_dcm_cb_fn.set_dce_accel();
			PE_CHECK_CODE(ret, break, "set_dce_accel() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * set dse control webos6.0
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_CTRL4_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDseCtrl2(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dse_ctrl2)
		{
			ret = _g_pe_dcm_cb_fn.set_dse_ctrl2(pstParams);
			PE_CHECK_CODE(ret, break, "set_dse_ctrl2() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dse control webos6.0
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DSE_CTRL4_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDseCtrl2(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dse_ctrl2)
		{
			ret = _g_pe_dcm_cb_fn.get_dse_ctrl2(pstParams);
			PE_CHECK_CODE(ret, break, "get_dse_ctrl2() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dce lut control webos6.0
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT1_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDceLut2(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dce_lut2)
		{
			ret = _g_pe_dcm_cb_fn.set_dce_lut2(pstParams);
			PE_CHECK_CODE(ret, break, "set_dce_lut2() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dce lut control webos6.0
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DCE_LUT1_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDceLut2(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.get_dce_lut2)
		{
			ret = _g_pe_dcm_cb_fn.get_dce_lut2(pstParams);
			PE_CHECK_CODE(ret, break, "get_dce_lut2() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dce db webos6.0
 *
 * @param   *pstParams [in] LX_PE_DCM_LIB_DB_ALL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDceDB(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dce_db)
		{
			ret = _g_pe_dcm_cb_fn.set_dce_db(pstParams);
			PE_CHECK_CODE(ret, break, "set_dce_db() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dce db webos6.0
 *
 * @param   *pstParams [in] LX_PE_DCM_LIB_DB_ALL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDceDB(int idexDb, int lengthOfData)
{
	int ret = RET_OK;
	do{
		if(_g_pe_dcm_cb_fn.get_dce_db)
		{
			ret = _g_pe_dcm_cb_fn.get_dce_db(idexDb, lengthOfData);
			PE_CHECK_CODE(ret, break, "get_dce_db() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dce lut control webos6.0 for f20
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT1_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDceLut3(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dce_lut3)
		{
			ret = _g_pe_dcm_cb_fn.set_dce_lut3(pstParams);
			PE_CHECK_CODE(ret, break, "set_dce_lut3() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dce db addr webos6.0
 *
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDceDBAddr(void)
{
	int ret = RET_OK;
	do{
		if(_g_pe_dcm_cb_fn.get_dce_db_addr)
		{
			ret = _g_pe_dcm_cb_fn.get_dce_db_addr();
			PE_CHECK_CODE(ret, break, "get_dce_db_addr() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dbc(delta_brightness_conpensation) db webos23
 *
 * @param   *pstParams [in] LX_PE_DCM_DBC_DB_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetDbcDB(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_dcm_cb_fn.set_dbc_db)
		{
			ret = _g_pe_dcm_cb_fn.set_dbc_db(pstParams);
			PE_CHECK_CODE(ret, break, "set_dbc_db() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dbc(delta_brightness_conpensation) db webos23
 *
 * @param   *pstParams [in] LX_PE_DCM_DBC_DB_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetDbcDB(void)
{
	int ret = RET_OK;
	do{
		if(_g_pe_dcm_cb_fn.get_dbc_db)
		{
			ret = _g_pe_dcm_cb_fn.get_dbc_db();
			PE_CHECK_CODE(ret, break, "get_dbc_db() error.\n");
		}
	}while (0);
	return ret;
}

