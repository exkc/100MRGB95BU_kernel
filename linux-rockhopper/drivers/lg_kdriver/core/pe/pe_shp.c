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

/** @file pe_shp.c
 *
 *  driver for picture enhance sharpness functions.
 *  ( used only within kdriver )
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

#include "pe_reg.h"
#include "pe_def.h"
#include "pe_etc.h"
#include "pe_cmn.h"
#include "pe_shp.h"
#include "pe_etc_hw.h"
#include "pe_shp_hw.h"
#include "pe_shp_scl032_def.h"
#include "pe_scl_p032_hw.h"
#include "pe_shp_scl256_def.h"
#include "pe_scl_p256_flt_param.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_SHP_DBG_PRINT(fmt, args...)	\
	if (_g_shp_trace)\
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
	int (*set_res_cmn)(void *pstParams);
	int (*get_res_cmn)(void *pstParams);
	int (*set_res_hor)(void *pstParams);
	int (*get_res_hor)(void *pstParams);
	int (*set_res_ver)(void *pstParams);
	int (*get_res_ver)(void *pstParams);
	int (*set_res_misc)(void *pstParams);
	int (*get_res_misc)(void *pstParams);
	int (*set_edge_enh)(void *pstParams);
	int (*get_edge_enh)(void *pstParams);
	int (*set_detail_enh)(void *pstParams);
	int (*get_detail_enh)(void *pstParams);
	int (*set_sqm_cmn)(void *pstParams);
	int (*set_sqm_cmn2)(void *pstParams);
	int (*get_sqm_cmn)(void *pstParams);
	int (*set_sqm_dtl)(void *pstParams);
	int (*get_sqm_dtl)(void *pstParams);
	int (*set_sre_res_cmn)(void *pstParams);
	int (*get_sre_res_cmn)(void *pstParams);
	int (*set_sre_res_hor)(void *pstParams);
	int (*get_sre_res_hor)(void *pstParams);
	int (*set_sre_res_ver)(void *pstParams);
	int (*get_sre_res_ver)(void *pstParams);
	int (*set_sre_res_misc)(void *pstParams);
	int (*get_sre_res_misc)(void *pstParams);
	int (*set_sre_edge_enh)(void *pstParams);
	int (*get_sre_edge_enh)(void *pstParams);
	int (*set_sre_detail_enh)(void *pstParams);
	int (*get_sre_detail_enh)(void *pstParams);
	int (*set_sre_sqm_cmn)(void *pstParams);
	int (*get_sre_sqm_cmn)(void *pstParams);
	int (*set_sre_sqm_dtl)(void *pstParams);
	int (*get_sre_sqm_dtl)(void *pstParams);
	int (*set_2ks_res_cmn)(void *pstParams);
	int (*get_2ks_res_cmn)(void *pstParams);
	int (*set_2ks_res_hor)(void *pstParams);
	int (*get_2ks_res_hor)(void *pstParams);
	int (*set_2ks_res_ver)(void *pstParams);
	int (*get_2ks_res_ver)(void *pstParams);
	int (*set_2ks_res_misc)(void *pstParams);
	int (*get_2ks_res_misc)(void *pstParams);
	int (*set_2ks_edge_enh)(void *pstParams);
	int (*get_2ks_edge_enh)(void *pstParams);
	int (*set_2ks_detail_enh)(void *pstParams);
	int (*get_2ks_detail_enh)(void *pstParams);
	int (*set_2ks_sqm_cmn)(void *pstParams);
	int (*set_2ks_sqm_cmn2)(void *pstParams);
	int (*get_2ks_sqm_cmn)(void *pstParams);
	int (*set_2ks_sqm_dtl)(void *pstParams);
	int (*get_2ks_sqm_dtl)(void *pstParams);
	int (*set_psp)(LX_PE_SHP_PSP_T *pstParams);
	int (*get_psp)(LX_PE_SHP_PSP_T *pstParams);
	int (*set_obc_ctrl)(void *pstParams);
	int (*get_obc_ctrl)(void *pstParams);
	int (*set_obc_lut)(void *pstParams);
	int (*get_obc_lut)(void *pstParams);
	int (*get_obc_data)(void *pstParams);
	int (*set_res_easy_cmn)(void *pstParams);
	int (*set_2ks_res_easy_cmn)(void *pstParams);
	int (*set_obc_stereo)(void *pstParams);
	int (*set_res_all)(void *pstParams);
	int (*get_res_all)(void);
	int (*set_res_ellips)(void *pstParams);
	int (*set_sub_res_cmn)(void *pstParams);
	int (*set_sub_res_misc)(void *pstParams);
}
PE_SHP_CB_FUNC_T;

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
static PE_SHP_CB_FUNC_T _g_pe_shp_cb_fn;
static UINT32 _g_shp_trace=0x0;	//default should be off.

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
int PE_SHP_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_shp_cb_fn, 0, sizeof(PE_SHP_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_O26_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_O26_SetDefault;
			_g_pe_shp_cb_fn.set_debug				= PE_SHP_HW_O26_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_O26_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_O26_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_misc			= PE_SHP_HW_O26_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc			= PE_SHP_HW_O26_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh			= PE_SHP_HW_O26_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh			= PE_SHP_HW_O26_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_O26_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_O26_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_cmn		= PE_SHP_HW_O26_SetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_cmn		= PE_SHP_HW_O26_GetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_misc		= PE_SHP_HW_O26_SetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_misc		= PE_SHP_HW_O26_GetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.set_2ks_edge_enh		= PE_SHP_HW_O26_SetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_edge_enh		= PE_SHP_HW_O26_GetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_detail_enh	= PE_SHP_HW_O26_SetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_detail_enh	= PE_SHP_HW_O26_GetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_obc_ctrl			= PE_SHP_HW_O26_SetObcCtrl;
			_g_pe_shp_cb_fn.get_obc_ctrl			= PE_SHP_HW_O26_GetObcCtrl;
			_g_pe_shp_cb_fn.set_obc_lut			= PE_SHP_HW_O26_SetObcLUT;
			_g_pe_shp_cb_fn.get_obc_lut			= PE_SHP_HW_O26_GetObcLUT;
			_g_pe_shp_cb_fn.get_obc_data			= PE_SHP_HW_O26_GetObcData;
			_g_pe_shp_cb_fn.set_sqm_cmn			= PE_SHP_HW_O26_SetSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_sqm_cmn			= PE_SHP_HW_O26_GetShpSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_sqm_dtl			= PE_SHP_HW_O26_SetSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_sqm_dtl			= PE_SHP_HW_O26_GetShpSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn		= PE_SHP_HW_O26_SetSre2KSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_cmn		= PE_SHP_HW_O26_GetShp2KSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_dtl		= PE_SHP_HW_O26_SetSre2KSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_dtl		= PE_SHP_HW_O26_GetShp2KSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_res_easy_cmn		= PE_SHP_HW_O26_SetReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_easy_cmn	= PE_SHP_HW_O26_SetSre2KReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_obc_stereo      	= PE_SHP_HW_O26_SetObcStereoCtrl;
			_g_pe_shp_cb_fn.set_res_all         	= NULL;//PE_SHP_HW_O26F22_SetReAllCtrl;
			_g_pe_shp_cb_fn.get_res_all           = NULL;//PE_CHPI_SHP_HW_O26F22_GetCtrl;
			_g_pe_shp_cb_fn.set_res_ellips           = PE_SHP_HW_O26_SetEllipsLutCtrl;
			_g_pe_shp_cb_fn.set_sub_res_cmn           = PE_SHP_HW_O26_SetSreSubReCmnCtrl;
			_g_pe_shp_cb_fn.set_sub_res_misc          = PE_SHP_HW_O26_SetSreSubReMiscCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_O24_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_O24_SetDefault;
			_g_pe_shp_cb_fn.set_debug				= PE_SHP_HW_O24_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_O24_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_O24_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_misc			= PE_SHP_HW_O24_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc			= PE_SHP_HW_O24_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh			= PE_SHP_HW_O24_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh			= PE_SHP_HW_O24_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_O24_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_O24_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_cmn		= PE_SHP_HW_O24_SetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_cmn		= PE_SHP_HW_O24_GetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_misc		= PE_SHP_HW_O24_SetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_misc		= PE_SHP_HW_O24_GetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.set_2ks_edge_enh		= PE_SHP_HW_O24_SetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_edge_enh		= PE_SHP_HW_O24_GetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_detail_enh	= PE_SHP_HW_O24_SetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_detail_enh	= PE_SHP_HW_O24_GetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_obc_ctrl			= PE_SHP_HW_O24_SetObcCtrl;
			_g_pe_shp_cb_fn.get_obc_ctrl			= PE_SHP_HW_O24_GetObcCtrl;
			_g_pe_shp_cb_fn.set_obc_lut			= PE_SHP_HW_O24_SetObcLUT;
			_g_pe_shp_cb_fn.get_obc_lut			= PE_SHP_HW_O24_GetObcLUT;
			_g_pe_shp_cb_fn.get_obc_data			= PE_SHP_HW_O24_GetObcData;
			_g_pe_shp_cb_fn.set_sqm_cmn			= PE_SHP_HW_O24_SetSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_sqm_cmn			= PE_SHP_HW_O24_GetShpSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_sqm_dtl			= PE_SHP_HW_O24_SetSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_sqm_dtl			= PE_SHP_HW_O24_GetShpSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn		= PE_SHP_HW_O24_SetSre2KSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_cmn		= PE_SHP_HW_O24_GetShp2KSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_dtl		= PE_SHP_HW_O24_SetSre2KSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_dtl		= PE_SHP_HW_O24_GetShp2KSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_res_easy_cmn		= PE_SHP_HW_O24_SetReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_easy_cmn	= PE_SHP_HW_O24_SetSre2KReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_obc_stereo      	= PE_SHP_HW_O24_SetObcStereoCtrl;
			_g_pe_shp_cb_fn.set_res_all         	= NULL;//PE_SHP_HW_O24F22_SetReAllCtrl;
			_g_pe_shp_cb_fn.get_res_all           = NULL;//PE_CHPI_SHP_HW_O24F22_GetCtrl;
			_g_pe_shp_cb_fn.set_res_ellips           = PE_SHP_HW_O24_SetEllipsLutCtrl;
			_g_pe_shp_cb_fn.set_sub_res_cmn           = PE_SHP_HW_O24_SetSreSubReCmnCtrl;
			_g_pe_shp_cb_fn.set_sub_res_misc          = PE_SHP_HW_O24_SetSreSubReMiscCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_M23_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_M23_SetDefault;
			_g_pe_shp_cb_fn.set_debug				= PE_SHP_HW_M23_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_M23_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_M23_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_misc			= PE_SHP_HW_M23_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc			= PE_SHP_HW_M23_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh			= PE_SHP_HW_M23_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh			= PE_SHP_HW_M23_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_M23_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_M23_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_cmn		= PE_SHP_HW_M23_SetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_cmn		= PE_SHP_HW_M23_GetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_misc		= PE_SHP_HW_M23_SetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_misc		= PE_SHP_HW_M23_GetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.set_2ks_edge_enh		= PE_SHP_HW_M23_SetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_edge_enh		= PE_SHP_HW_M23_GetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_detail_enh	= PE_SHP_HW_M23_SetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_detail_enh	= PE_SHP_HW_M23_GetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_obc_ctrl			= PE_SHP_HW_M23_SetObcCtrl;
			_g_pe_shp_cb_fn.get_obc_ctrl			= PE_SHP_HW_M23_GetObcCtrl;
			_g_pe_shp_cb_fn.set_obc_lut			= PE_SHP_HW_M23_SetObcLUT;
			_g_pe_shp_cb_fn.get_obc_lut			= PE_SHP_HW_M23_GetObcLUT;
			_g_pe_shp_cb_fn.get_obc_data			= PE_SHP_HW_M23_GetObcData;
			_g_pe_shp_cb_fn.set_sqm_cmn			= PE_SHP_HW_M23_SetSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_sqm_cmn			= PE_SHP_HW_M23_GetShpSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_sqm_dtl			= PE_SHP_HW_M23_SetSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_sqm_dtl			= PE_SHP_HW_M23_GetShpSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn		= PE_SHP_HW_M23_SetSre2KSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_cmn		= PE_SHP_HW_M23_GetShp2KSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_dtl		= PE_SHP_HW_M23_SetSre2KSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_dtl		= PE_SHP_HW_M23_GetShp2KSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_res_easy_cmn		= PE_SHP_HW_M23_SetReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_easy_cmn	= PE_SHP_HW_M23_SetSre2KReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_obc_stereo      	= PE_SHP_HW_M23_SetObcStereoCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_O22_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_O22_SetDefault;
			_g_pe_shp_cb_fn.set_debug				= PE_SHP_HW_O22_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_O22_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_O22_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_misc			= PE_SHP_HW_O22_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc			= PE_SHP_HW_O22_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh			= PE_SHP_HW_O22_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh			= PE_SHP_HW_O22_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_O22_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_O22_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_cmn		= PE_SHP_HW_O22_SetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_cmn		= PE_SHP_HW_O22_GetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_misc		= PE_SHP_HW_O22_SetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_misc		= PE_SHP_HW_O22_GetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.set_2ks_edge_enh		= PE_SHP_HW_O22_SetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_edge_enh		= PE_SHP_HW_O22_GetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_detail_enh	= PE_SHP_HW_O22_SetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_detail_enh	= PE_SHP_HW_O22_GetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_obc_ctrl			= PE_SHP_HW_O22_SetObcCtrl;
			_g_pe_shp_cb_fn.get_obc_ctrl			= PE_SHP_HW_O22_GetObcCtrl;
			_g_pe_shp_cb_fn.set_obc_lut			= PE_SHP_HW_O22_SetObcLUT;
			_g_pe_shp_cb_fn.get_obc_lut			= PE_SHP_HW_O22_GetObcLUT;
			_g_pe_shp_cb_fn.get_obc_data			= PE_SHP_HW_O22_GetObcData;
			_g_pe_shp_cb_fn.set_sqm_cmn			= PE_SHP_HW_O22_SetSqmCmnCtrl;
			_g_pe_shp_cb_fn.set_sqm_cmn2		= PE_SHP_HW_O22_SetSqmCmnCtrl2;
			_g_pe_shp_cb_fn.get_sqm_cmn			= PE_SHP_HW_O22_GetShpSqmCmnUserDb2;
			_g_pe_shp_cb_fn.set_sqm_dtl			= PE_SHP_HW_O22_SetSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_sqm_dtl			= PE_SHP_HW_O22_GetShpSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn		= PE_SHP_HW_O22_SetSre2KSqmCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn2	= PE_SHP_HW_O22_SetSre2KSqmCmnCtrl2;
			_g_pe_shp_cb_fn.get_2ks_sqm_cmn		= PE_SHP_HW_O22_GetShp2KSqmCmnUserDb2;
			_g_pe_shp_cb_fn.set_2ks_sqm_dtl		= PE_SHP_HW_O22_SetSre2KSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_dtl		= PE_SHP_HW_O22_GetShp2KSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_res_easy_cmn		= PE_SHP_HW_O22_SetReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_easy_cmn	= PE_SHP_HW_O22_SetSre2KReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_obc_stereo      	= PE_SHP_HW_O22_SetObcStereoCtrl;
			_g_pe_shp_cb_fn.set_res_all         	= PE_SHP_HW_O22F22_SetReAllCtrl;
			_g_pe_shp_cb_fn.get_res_all           = PE_CHPI_SHP_HW_O22F22_GetCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_E60_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_E60_SetDefault;
			_g_pe_shp_cb_fn.set_debug				= PE_SHP_HW_E60_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_E60_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_E60_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_misc			= PE_SHP_HW_E60_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc			= PE_SHP_HW_E60_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh			= PE_SHP_HW_E60_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh			= PE_SHP_HW_E60_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_E60_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_E60_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_res_cmn		= PE_SHP_HW_E60_SetSreReCmnCtrl;
			_g_pe_shp_cb_fn.get_sre_res_cmn		= PE_SHP_HW_E60_GetSreReCmnCtrl;
			_g_pe_shp_cb_fn.set_sre_res_misc		= PE_SHP_HW_E60_SetSreReMiscCtrl;
			_g_pe_shp_cb_fn.get_sre_res_misc		= PE_SHP_HW_E60_GetSreReMiscCtrl;
			_g_pe_shp_cb_fn.set_sre_edge_enh		= PE_SHP_HW_E60_SetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_edge_enh		= PE_SHP_HW_E60_GetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_detail_enh	= PE_SHP_HW_E60_SetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_detail_enh	= PE_SHP_HW_E60_GetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_sqm_cmn		= PE_SHP_HW_E60_SetSreSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_sre_sqm_cmn		= PE_SHP_HW_E60_GetSreSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_sre_sqm_dtl		= PE_SHP_HW_E60_SetSreSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_sre_sqm_dtl		= PE_SHP_HW_E60_GetSreSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_2ks_res_cmn		= PE_SHP_HW_E60_SetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_cmn		= PE_SHP_HW_E60_GetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_misc		= PE_SHP_HW_E60_SetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_misc		= PE_SHP_HW_E60_GetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.set_2ks_edge_enh		= PE_SHP_HW_E60_SetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_edge_enh		= PE_SHP_HW_E60_GetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_detail_enh	= PE_SHP_HW_E60_SetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_detail_enh	= PE_SHP_HW_E60_GetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_obc_ctrl			= PE_SHP_HW_E60_SetObcCtrl;
			_g_pe_shp_cb_fn.get_obc_ctrl			= PE_SHP_HW_E60_GetObcCtrl;
			_g_pe_shp_cb_fn.set_obc_lut			= PE_SHP_HW_E60_SetObcLUT;
			_g_pe_shp_cb_fn.get_obc_lut			= PE_SHP_HW_E60_GetObcLUT;
			_g_pe_shp_cb_fn.get_obc_data			= PE_SHP_HW_E60_GetObcData;
			_g_pe_shp_cb_fn.set_sqm_cmn			= PE_SHP_HW_E60_SetSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_sqm_cmn			= PE_SHP_HW_E60_GetShpSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_sqm_dtl			= PE_SHP_HW_E60_SetSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_sqm_dtl			= PE_SHP_HW_E60_GetShpSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn		= PE_SHP_HW_E60_SetSre2KSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_cmn		= PE_SHP_HW_E60_GetShp2KSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_dtl		= PE_SHP_HW_E60_SetSre2KSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_dtl		= PE_SHP_HW_E60_GetShp2KSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_res_easy_cmn		= PE_SHP_HW_E60_SetReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_easy_cmn	= PE_SHP_HW_E60_SetSre2KReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_obc_stereo      	= PE_SHP_HW_E60_SetObcStereoCtrl;
			_g_pe_shp_cb_fn.set_res_all         	= PE_SHP_HW_E60F20_SetReAllCtrl;
			_g_pe_shp_cb_fn.get_res_all           = PE_CHPI_SHP_HW_E60F20_GetCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_O20_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_O20_SetDefault;
			_g_pe_shp_cb_fn.set_debug			= PE_SHP_HW_O20_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_O20_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_O20_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_hor			= PE_SHP_HW_O20_SetReHorCtrl;
			_g_pe_shp_cb_fn.get_res_hor			= PE_SHP_HW_O20_GetReHorCtrl;
			_g_pe_shp_cb_fn.set_res_ver			= PE_SHP_HW_O20_SetReVerCtrl;
			_g_pe_shp_cb_fn.get_res_ver			= PE_SHP_HW_O20_GetReVerCtrl;
			_g_pe_shp_cb_fn.set_res_misc		= PE_SHP_HW_O20_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc		= PE_SHP_HW_O20_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh		= PE_SHP_HW_O20_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh		= PE_SHP_HW_O20_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_O20_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_O20_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_res_cmn		= PE_SHP_HW_O20_SetSreReCmnCtrl;
			_g_pe_shp_cb_fn.get_sre_res_cmn		= PE_SHP_HW_O20_GetSreReCmnCtrl;
			_g_pe_shp_cb_fn.set_sre_res_hor		= PE_SHP_HW_O20_SetSreReHorCtrl;
			_g_pe_shp_cb_fn.get_sre_res_hor		= PE_SHP_HW_O20_GetSreReHorCtrl;
			_g_pe_shp_cb_fn.set_sre_res_ver		= PE_SHP_HW_O20_SetSreReVerCtrl;
			_g_pe_shp_cb_fn.get_sre_res_ver		= PE_SHP_HW_O20_GetSreReVerCtrl;
			_g_pe_shp_cb_fn.set_sre_res_misc	= PE_SHP_HW_O20_SetSreReMiscCtrl;
			_g_pe_shp_cb_fn.get_sre_res_misc	= PE_SHP_HW_O20_GetSreReMiscCtrl;
			_g_pe_shp_cb_fn.set_sre_edge_enh	= PE_SHP_HW_O20_SetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_edge_enh	= PE_SHP_HW_O20_GetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_detail_enh	= PE_SHP_HW_O20_SetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_detail_enh	= PE_SHP_HW_O20_GetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_psp				= PE_SHP_HW_O20_SetPspCtrl;
			_g_pe_shp_cb_fn.get_psp				= PE_SHP_HW_O20_GetPspCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_cmn		= PE_SHP_HW_O20_SetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_cmn		= PE_SHP_HW_O20_GetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_hor		= PE_SHP_HW_O20_SetSre2KReHorCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_hor		= PE_SHP_HW_O20_GetSre2KReHorCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_ver		= PE_SHP_HW_O20_SetSre2KReVerCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_ver		= PE_SHP_HW_O20_GetSre2KReVerCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_misc	= PE_SHP_HW_O20_SetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_misc	= PE_SHP_HW_O20_GetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.set_2ks_edge_enh	= PE_SHP_HW_O20_SetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_edge_enh	= PE_SHP_HW_O20_GetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_detail_enh	= PE_SHP_HW_O20_SetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_detail_enh	= PE_SHP_HW_O20_GetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_psp				= PE_SHP_HW_O20_SetPspCtrl;
			_g_pe_shp_cb_fn.get_psp				= PE_SHP_HW_O20_GetPspCtrl;
			_g_pe_shp_cb_fn.set_obc_ctrl		= PE_SHP_HW_O20_SetObcCtrl;
			_g_pe_shp_cb_fn.get_obc_ctrl		= PE_SHP_HW_O20_GetObcCtrl;
			_g_pe_shp_cb_fn.set_obc_lut			= PE_SHP_HW_O20_SetObcLUT;
			_g_pe_shp_cb_fn.get_obc_lut			= PE_SHP_HW_O20_GetObcLUT;
			_g_pe_shp_cb_fn.set_sqm_cmn			= PE_SHP_HW_O20_SetSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_sqm_cmn			= PE_SHP_HW_O20_GetShpSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_sqm_dtl			= PE_SHP_HW_O20_SetSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_sqm_dtl			= PE_SHP_HW_O20_GetShpSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn		= PE_SHP_HW_O20_SetSre2KSqmCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_cmn		= PE_SHP_HW_O20_GetShp2KSqmCmnUserDb;
			_g_pe_shp_cb_fn.set_2ks_sqm_dtl		= PE_SHP_HW_O20_SetSre2KSqmDetailCtrl;
			_g_pe_shp_cb_fn.get_2ks_sqm_dtl		= PE_SHP_HW_O20_GetShp2KSqmDetailUserDb;
			_g_pe_shp_cb_fn.set_res_easy_cmn	= PE_SHP_HW_O20_SetReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_easy_cmn	= PE_SHP_HW_O20_SetSre2KReEasyCmnCtrl;
			_g_pe_shp_cb_fn.set_obc_stereo      = PE_SHP_HW_O20_SetObcStereoCtrl;
			_g_pe_shp_cb_fn.set_res_all          = PE_SHP_HW_F20_SetReAllCtrl;
			_g_pe_shp_cb_fn.get_res_all          = PE_CHPI_SHP_HW_F20_GetCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M19
		if (PE_KDRV_VER_M19)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_M19_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_M19_SetDefault;
			_g_pe_shp_cb_fn.set_debug			= PE_SHP_HW_M19_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_M19_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_M19_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_hor			= PE_SHP_HW_M19_SetReHorCtrl;
			_g_pe_shp_cb_fn.get_res_hor			= PE_SHP_HW_M19_GetReHorCtrl;
			_g_pe_shp_cb_fn.set_res_ver			= PE_SHP_HW_M19_SetReVerCtrl;
			_g_pe_shp_cb_fn.get_res_ver			= PE_SHP_HW_M19_GetReVerCtrl;
			_g_pe_shp_cb_fn.set_res_misc		= PE_SHP_HW_M19_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc		= PE_SHP_HW_M19_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh		= PE_SHP_HW_M19_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh		= PE_SHP_HW_M19_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_M19_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_M19_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_res_cmn		= PE_SHP_HW_M19_SetSreReCmnCtrl;
			_g_pe_shp_cb_fn.get_sre_res_cmn		= PE_SHP_HW_M19_GetSreReCmnCtrl;
			_g_pe_shp_cb_fn.set_sre_res_hor		= PE_SHP_HW_M19_SetSreReHorCtrl;
			_g_pe_shp_cb_fn.get_sre_res_hor		= PE_SHP_HW_M19_GetSreReHorCtrl;
			_g_pe_shp_cb_fn.set_sre_res_ver		= PE_SHP_HW_M19_SetSreReVerCtrl;
			_g_pe_shp_cb_fn.get_sre_res_ver		= PE_SHP_HW_M19_GetSreReVerCtrl;
			_g_pe_shp_cb_fn.set_sre_res_misc	= PE_SHP_HW_M19_SetSreReMiscCtrl;
			_g_pe_shp_cb_fn.get_sre_res_misc	= PE_SHP_HW_M19_GetSreReMiscCtrl;
			_g_pe_shp_cb_fn.set_sre_edge_enh	= PE_SHP_HW_M19_SetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_edge_enh	= PE_SHP_HW_M19_GetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_detail_enh	= PE_SHP_HW_M19_SetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_detail_enh	= PE_SHP_HW_M19_GetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_psp				= PE_SHP_HW_M19_SetPspCtrl;
			_g_pe_shp_cb_fn.get_psp				= PE_SHP_HW_M19_GetPspCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_cmn		= PE_SHP_HW_M19_SetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_cmn		= PE_SHP_HW_M19_GetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_hor		= PE_SHP_HW_M19_SetSre2KReHorCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_hor		= PE_SHP_HW_M19_GetSre2KReHorCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_ver		= PE_SHP_HW_M19_SetSre2KReVerCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_ver		= PE_SHP_HW_M19_GetSre2KReVerCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_misc	= PE_SHP_HW_M19_SetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_misc	= PE_SHP_HW_M19_GetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.set_2ks_edge_enh	= PE_SHP_HW_M19_SetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_edge_enh	= PE_SHP_HW_M19_GetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_detail_enh	= PE_SHP_HW_M19_SetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_detail_enh	= PE_SHP_HW_M19_GetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_psp				= PE_SHP_HW_M19_SetPspCtrl;
			_g_pe_shp_cb_fn.get_psp				= PE_SHP_HW_M19_GetPspCtrl;
			_g_pe_shp_cb_fn.set_obc_ctrl		= PE_SHP_HW_M19_SetObcCtrl;
			_g_pe_shp_cb_fn.get_obc_ctrl		= PE_SHP_HW_M19_GetObcCtrl;
			_g_pe_shp_cb_fn.set_obc_lut			= PE_SHP_HW_M19_SetObcLUT;
			_g_pe_shp_cb_fn.get_obc_lut			= PE_SHP_HW_M19_GetObcLUT;
			_g_pe_shp_cb_fn.set_sqm_cmn			= PE_SHP_HW_M19_SetSqmCmnCtrl;
			_g_pe_shp_cb_fn.set_sqm_dtl			= PE_SHP_HW_M19_SetSqmDetailCtrl;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn		= PE_SHP_HW_M19_SetSre2KSqmCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_sqm_dtl		= PE_SHP_HW_M19_SetSre2KSqmDetailCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O18
		if (PE_KDRV_VER_O18)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_O18_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_O18_SetDefault;
			_g_pe_shp_cb_fn.set_debug			= PE_SHP_HW_O18_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_O18_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_O18_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_hor			= PE_SHP_HW_O18_SetReHorCtrl;
			_g_pe_shp_cb_fn.get_res_hor			= PE_SHP_HW_O18_GetReHorCtrl;
			_g_pe_shp_cb_fn.set_res_ver			= PE_SHP_HW_O18_SetReVerCtrl;
			_g_pe_shp_cb_fn.get_res_ver			= PE_SHP_HW_O18_GetReVerCtrl;
			_g_pe_shp_cb_fn.set_res_misc		= PE_SHP_HW_O18_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc		= PE_SHP_HW_O18_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh		= PE_SHP_HW_O18_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh		= PE_SHP_HW_O18_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_O18_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_O18_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_res_cmn		= PE_SHP_HW_O18_SetSreReCmnCtrl;
			_g_pe_shp_cb_fn.get_sre_res_cmn		= PE_SHP_HW_O18_GetSreReCmnCtrl;
			_g_pe_shp_cb_fn.set_sre_res_hor		= PE_SHP_HW_O18_SetSreReHorCtrl;
			_g_pe_shp_cb_fn.get_sre_res_hor		= PE_SHP_HW_O18_GetSreReHorCtrl;
			_g_pe_shp_cb_fn.set_sre_res_ver		= PE_SHP_HW_O18_SetSreReVerCtrl;
			_g_pe_shp_cb_fn.get_sre_res_ver		= PE_SHP_HW_O18_GetSreReVerCtrl;
			_g_pe_shp_cb_fn.set_sre_res_misc	= PE_SHP_HW_O18_SetSreReMiscCtrl;
			_g_pe_shp_cb_fn.get_sre_res_misc	= PE_SHP_HW_O18_GetSreReMiscCtrl;
			_g_pe_shp_cb_fn.set_sre_edge_enh	= PE_SHP_HW_O18_SetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_edge_enh	= PE_SHP_HW_O18_GetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_detail_enh	= PE_SHP_HW_O18_SetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_detail_enh	= PE_SHP_HW_O18_GetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_cmn		= PE_SHP_HW_O18_SetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_cmn		= PE_SHP_HW_O18_GetSre2KReCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_hor		= PE_SHP_HW_O18_SetSre2KReHorCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_hor		= PE_SHP_HW_O18_GetSre2KReHorCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_ver		= PE_SHP_HW_O18_SetSre2KReVerCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_ver		= PE_SHP_HW_O18_GetSre2KReVerCtrl;
			_g_pe_shp_cb_fn.set_2ks_res_misc	= PE_SHP_HW_O18_SetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.get_2ks_res_misc	= PE_SHP_HW_O18_GetSre2KReMiscCtrl;
			_g_pe_shp_cb_fn.set_2ks_edge_enh	= PE_SHP_HW_O18_SetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_edge_enh	= PE_SHP_HW_O18_GetSre2KEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_2ks_detail_enh	= PE_SHP_HW_O18_SetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_2ks_detail_enh	= PE_SHP_HW_O18_GetSre2KDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_psp				= PE_SHP_HW_O18_SetPspCtrl;
			_g_pe_shp_cb_fn.get_psp				= PE_SHP_HW_O18_GetPspCtrl;
			_g_pe_shp_cb_fn.set_obc_ctrl		= PE_SHP_HW_O18_SetObcCtrl;
			_g_pe_shp_cb_fn.get_obc_ctrl		= PE_SHP_HW_O18_GetObcCtrl;
			_g_pe_shp_cb_fn.set_obc_lut			= PE_SHP_HW_O18_SetObcLUT;
			_g_pe_shp_cb_fn.get_obc_lut			= PE_SHP_HW_O18_GetObcLUT;
			_g_pe_shp_cb_fn.set_sqm_cmn			= PE_SHP_HW_O18_SetSqmCmnCtrl;
			_g_pe_shp_cb_fn.set_sqm_dtl			= PE_SHP_HW_O18_SetSqmDetailCtrl;
			_g_pe_shp_cb_fn.set_2ks_sqm_cmn		= PE_SHP_HW_O18_SetSre2KSqmCmnCtrl;
			_g_pe_shp_cb_fn.set_2ks_sqm_dtl		= PE_SHP_HW_O18_SetSre2KSqmDetailCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M17
		if (PE_KDRV_VER_M17CX)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_M17C0_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_M17C0_SetDefault;
			_g_pe_shp_cb_fn.set_debug			= PE_SHP_HW_M17C0_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_M17C0_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_M17C0_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_hor			= PE_SHP_HW_M17C0_SetReHorCtrl;
			_g_pe_shp_cb_fn.get_res_hor			= PE_SHP_HW_M17C0_GetReHorCtrl;
			_g_pe_shp_cb_fn.set_res_ver			= PE_SHP_HW_M17C0_SetReVerCtrl;
			_g_pe_shp_cb_fn.get_res_ver			= PE_SHP_HW_M17C0_GetReVerCtrl;
			_g_pe_shp_cb_fn.set_res_misc		= PE_SHP_HW_M17C0_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc		= PE_SHP_HW_M17C0_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh		= PE_SHP_HW_M17C0_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh		= PE_SHP_HW_M17C0_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_M17C0_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_M17C0_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_res_cmn		= PE_SHP_HW_M17C0_SetSreReCmnCtrl;
			_g_pe_shp_cb_fn.get_sre_res_cmn		= PE_SHP_HW_M17C0_GetSreReCmnCtrl;
			_g_pe_shp_cb_fn.set_sre_res_hor		= PE_SHP_HW_M17C0_SetSreReHorCtrl;
			_g_pe_shp_cb_fn.get_sre_res_hor		= PE_SHP_HW_M17C0_GetSreReHorCtrl;
			_g_pe_shp_cb_fn.set_sre_res_ver		= PE_SHP_HW_M17C0_SetSreReVerCtrl;
			_g_pe_shp_cb_fn.get_sre_res_ver		= PE_SHP_HW_M17C0_GetSreReVerCtrl;
			_g_pe_shp_cb_fn.set_sre_res_misc	= PE_SHP_HW_M17C0_SetSreReMiscCtrl;
			_g_pe_shp_cb_fn.get_sre_res_misc	= PE_SHP_HW_M17C0_GetSreReMiscCtrl;
			_g_pe_shp_cb_fn.set_sre_edge_enh	= PE_SHP_HW_M17C0_SetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_edge_enh	= PE_SHP_HW_M17C0_GetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_detail_enh	= PE_SHP_HW_M17C0_SetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_detail_enh	= PE_SHP_HW_M17C0_GetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_psp				= PE_SHP_HW_M17C0_SetPspCtrl;
			_g_pe_shp_cb_fn.get_psp				= PE_SHP_HW_M17C0_GetPspCtrl;
		}
		else if (PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
		{
			_g_pe_shp_cb_fn.hw_init				= PE_SHP_HW_M17_Init;
			_g_pe_shp_cb_fn.set_default			= PE_SHP_HW_M17_SetDefault;
			_g_pe_shp_cb_fn.set_debug			= PE_SHP_HW_M17_SetDebugSettings;
			_g_pe_shp_cb_fn.set_res_cmn			= PE_SHP_HW_M17_SetReCmnCtrl;
			_g_pe_shp_cb_fn.get_res_cmn			= PE_SHP_HW_M17_GetReCmnCtrl;
			_g_pe_shp_cb_fn.set_res_hor			= PE_SHP_HW_M17_SetReHorCtrl;
			_g_pe_shp_cb_fn.get_res_hor			= PE_SHP_HW_M17_GetReHorCtrl;
			_g_pe_shp_cb_fn.set_res_ver			= PE_SHP_HW_M17_SetReVerCtrl;
			_g_pe_shp_cb_fn.get_res_ver			= PE_SHP_HW_M17_GetReVerCtrl;
			_g_pe_shp_cb_fn.set_res_misc		= PE_SHP_HW_M17_SetReMiscCtrl;
			_g_pe_shp_cb_fn.get_res_misc		= PE_SHP_HW_M17_GetReMiscCtrl;
			_g_pe_shp_cb_fn.set_edge_enh		= PE_SHP_HW_M17_SetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_edge_enh		= PE_SHP_HW_M17_GetEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_detail_enh		= PE_SHP_HW_M17_SetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_detail_enh		= PE_SHP_HW_M17_GetDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_res_cmn		= PE_SHP_HW_M17_SetSreReCmnCtrl;
			_g_pe_shp_cb_fn.get_sre_res_cmn		= PE_SHP_HW_M17_GetSreReCmnCtrl;
			_g_pe_shp_cb_fn.set_sre_res_hor		= PE_SHP_HW_M17_SetSreReHorCtrl;
			_g_pe_shp_cb_fn.get_sre_res_hor		= PE_SHP_HW_M17_GetSreReHorCtrl;
			_g_pe_shp_cb_fn.set_sre_res_ver		= PE_SHP_HW_M17_SetSreReVerCtrl;
			_g_pe_shp_cb_fn.get_sre_res_ver		= PE_SHP_HW_M17_GetSreReVerCtrl;
			_g_pe_shp_cb_fn.set_sre_res_misc	= PE_SHP_HW_M17_SetSreReMiscCtrl;
			_g_pe_shp_cb_fn.get_sre_res_misc	= PE_SHP_HW_M17_GetSreReMiscCtrl;
			_g_pe_shp_cb_fn.set_sre_edge_enh	= PE_SHP_HW_M17_SetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_edge_enh	= PE_SHP_HW_M17_GetSreEdgeEnhanceCtrl;
			_g_pe_shp_cb_fn.set_sre_detail_enh	= PE_SHP_HW_M17_SetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.get_sre_detail_enh	= PE_SHP_HW_M17_GetSreDetailEnhanceCtrl;
			_g_pe_shp_cb_fn.set_psp				= PE_SHP_HW_M17_SetPspCtrl;
			_g_pe_shp_cb_fn.get_psp				= PE_SHP_HW_M17_GetPspCtrl;
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
 * init shp
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.hw_init)
		{
			ret = _g_pe_shp_cb_fn.hw_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_init() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of shp setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_SHP_SET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_SHP_DBG_PRINT("S TABL %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__); \
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size, 0, 16);\
			PE_CHECK_CODE(!bufsize, break, \
				"[%s,%d] bufsize zero.\n", __F__, __L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CHECK_CODE(!p_data, break, \
				"[%s,%d] p_data is null.\n", __F__, __L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_from_user error.\n", __F__, __L__);\
			param.win_id = p_rcv->win_id;\
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_SHP_DBG_PRINT("E TABL %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

#define PE_SHP_SET_FUNC(_struct, _func, _void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_SHP_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_SHP_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_SHP_SET_FUNC(LX_PE_SHP_RE_PSEUDO_CMN_T,	PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE_PSEUDO_HOR_T,	PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE_PSEUDO_VER_T,	PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_PSEUDO_EE_T,		PE_SHP_SetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_PSEUDO_DE_T,		PE_SHP_SetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE_EASY_CMN_T,	PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE_EASY_DE_T,		PE_SHP_SetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE1_HOR_T,		PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE1_VER_T,		PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE1_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_EE1_T,			PE_SHP_SetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_DE1_T,			PE_SHP_SetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE1_CMN_T,		PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE2_HOR_T,		PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE2_VER_T,		PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE2_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE3_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE3_CMN_T,		PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE4_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE4_CMN_T,		PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE3_HOR_T,		PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE3_VER_T,		PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE5_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_EE2_T,			PE_SHP_SetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_DE2_T,			PE_SHP_SetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE_CMN_T,		PE_SHP_SetSreReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE_HOR_T,		PE_SHP_SetSreReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE_VER_T,		PE_SHP_SetSreReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE_MISC_T,		PE_SHP_SetSreReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_EE_T,			PE_SHP_SetSreEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_DE_T,			PE_SHP_SetSreDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE2_CMN_T,		PE_SHP_SetSreReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE2_HOR_T,		PE_SHP_SetSreReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE2_VER_T,		PE_SHP_SetSreReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_EE2_T,			PE_SHP_SetSreEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_DE2_T,			PE_SHP_SetSreDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE2_MISC_T,		PE_SHP_SetSreReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_SHP_SetDefaultSettings,	_STRUCT_INPUT_);
		PE_SHP_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_SHP_SetDebugSettings,	_STRUCT_INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_PSP_T,			PE_SHP_SetPspCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE5_CMN_T,		PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE4_HOR_T,		PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE4_VER_T,		PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE6_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_EE3_T,			PE_SHP_SetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_DE3_T,			PE_SHP_SetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE3_CMN_T,		PE_SHP_SetSreReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE3_HOR_T,		PE_SHP_SetSreReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE3_VER_T,		PE_SHP_SetSreReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_EE3_T,			PE_SHP_SetSreEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_DE3_T,			PE_SHP_SetSreDetailEnhanceCtrl, _VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE3_MISC_T,	PE_SHP_SetSreReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE6_CMN_T,		PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE5_HOR_T,		PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE5_VER_T,		PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE7_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_EE4_T,			PE_SHP_SetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_DE4_T,			PE_SHP_SetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE4_CMN_T,		PE_SHP_SetSreReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE4_HOR_T,		PE_SHP_SetSreReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE4_VER_T,		PE_SHP_SetSreReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_RE4_MISC_T,	PE_SHP_SetSreReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_EE4_T,			PE_SHP_SetSreEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR_DE4_T,			PE_SHP_SetSreDetailEnhanceCtrl, _VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_EASY_CMN_T,	PE_SHP_SetSre2KReCmnCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_EASY_DE_T,	PE_SHP_SetSre2KDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_RE_CMN_T,	PE_SHP_SetSre2KReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_RE_HOR_T,	PE_SHP_SetSre2KReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_RE_VER_T,	PE_SHP_SetSre2KReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_RE_MISC_T,	PE_SHP_SetSre2KReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_EE_T,		PE_SHP_SetSre2KEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_DE_T,		PE_SHP_SetSre2KDetailEnhanceCtrl, _VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_VSD_OBC_CONT_T,		PE_SHP_SetObcCtrl,			_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_VSD_OBC1_CONT_T,		PE_SHP_SetObcCtrl,			_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_VSD_OBC_LUT_T,		PE_SHP_SetObcLUT,			_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE_SQM_CMN_T,		PE_SHP_SetSqmCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE_SQM_DETAIL_T,	PE_SHP_SetSqmDetailCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_SQM_CMN_T,	PE_SHP_SetSre2KSqmCmnCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_SR2K_SQM_DETAIL_T,PE_SHP_SetSre2KSqmDetailCtrl,	_VOID___INPUT_);
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
 * standard function of shp getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_SHP_GET_FUNC(_struct, _func, _void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_SHP_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
			PE_SHP_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_SHP_GET_FUNC(LX_PE_SHP_RE_PSEUDO_CMN_T,	PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE_PSEUDO_HOR_T,	PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE_PSEUDO_VER_T,	PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_PSEUDO_EE_T,		PE_SHP_GetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_PSEUDO_DE_T,		PE_SHP_GetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE_EASY_CMN_T,	PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE_EASY_DE_T,		PE_SHP_GetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE1_HOR_T,		PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE1_VER_T,		PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE1_MISC_T,		PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_EE1_T,			PE_SHP_GetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_DE1_T,			PE_SHP_GetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE1_CMN_T,		PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE3_CMN_T,		PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE2_HOR_T,		PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE2_VER_T,		PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE2_MISC_T,		PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE3_MISC_T,		PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE4_MISC_T,		PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE4_CMN_T,		PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE3_HOR_T,		PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE3_VER_T,		PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE5_MISC_T,		PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_EE2_T,			PE_SHP_GetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_DE2_T,			PE_SHP_GetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE_CMN_T,		PE_SHP_GetSreReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE_HOR_T,		PE_SHP_GetSreReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE_VER_T,		PE_SHP_GetSreReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE_MISC_T,		PE_SHP_GetSreReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_EE_T,			PE_SHP_GetSreEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_DE_T,			PE_SHP_GetSreDetailEnhanceCtrl, _VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE2_CMN_T,		PE_SHP_GetSreReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE2_HOR_T,		PE_SHP_GetSreReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE2_VER_T,		PE_SHP_GetSreReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE2_MISC_T,	PE_SHP_GetSreReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_EE2_T,			PE_SHP_GetSreEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_DE2_T,			PE_SHP_GetSreDetailEnhanceCtrl, _VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_PSP_T,			PE_SHP_GetPspCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE5_CMN_T,		PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE4_HOR_T,		PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE4_VER_T,		PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE6_MISC_T,		PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_EE3_T,			PE_SHP_GetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_DE3_T,			PE_SHP_GetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE3_CMN_T,		PE_SHP_GetSreReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE3_HOR_T,		PE_SHP_GetSreReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE3_VER_T,		PE_SHP_GetSreReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE3_MISC_T,	PE_SHP_GetSreReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_EE3_T,			PE_SHP_GetSreEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_DE3_T,			PE_SHP_GetSreDetailEnhanceCtrl, _VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE6_CMN_T,		PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE5_HOR_T,		PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE5_VER_T,		PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE7_MISC_T,		PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_EE4_T,			PE_SHP_GetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_DE4_T,			PE_SHP_GetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE4_CMN_T,		PE_SHP_GetSreReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE4_HOR_T,		PE_SHP_GetSreReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE4_VER_T,		PE_SHP_GetSreReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_RE4_MISC_T,	PE_SHP_GetSreReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_EE4_T,			PE_SHP_GetSreEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR_DE4_T,			PE_SHP_GetSreDetailEnhanceCtrl, _VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_EASY_CMN_T,	PE_SHP_GetSre2KReCmnCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_EASY_DE_T,	PE_SHP_GetSre2KDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_RE_CMN_T,	PE_SHP_GetSre2KReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_RE_HOR_T,	PE_SHP_GetSre2KReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_RE_VER_T,	PE_SHP_GetSre2KReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_RE_MISC_T,	PE_SHP_GetSre2KReMiscCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_EE_T,		PE_SHP_GetSre2KEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_DE_T,		PE_SHP_GetSre2KDetailEnhanceCtrl, _VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_VSD_OBC_CONT_T,		PE_SHP_GetObcCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_VSD_OBC1_CONT_T,		PE_SHP_GetObcCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_VSD_OBC_LUT_T,		PE_SHP_GetObcLUT,		_VOID___INPUT_);
		//PE_SHP_GET_FUNC(LX_PE_SHP_RE_SQM_CMN_T,		PE_SHP_GetSqmCmnCtrl,	_VOID___INPUT_);
		//PE_SHP_GET_FUNC(LX_PE_SHP_RE_SQM_DETAIL_T,	PE_SHP_GetSqmDetailCtrl,	_VOID___INPUT_);
		//PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_SQM_CMN_T,	PE_SHP_GetSre2KSqmCmnCtrl,	_VOID___INPUT_);
		//PE_SHP_GET_FUNC(LX_PE_SHP_SR2K_SQM_DETAIL_T,PE_SHP_GetSre2KSqmDetailCtrl,	_VOID___INPUT_);
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
 * set default settings
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_default)
		{
			ret = _g_pe_shp_cb_fn.set_default(pstParams);
			PE_CHECK_CODE(ret, break, "set_default() error.\n");
		}
	}while (0);
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
int PE_SHP_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_shp_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(SHP)))? 0x1:0x0;
		}
		if(_g_pe_shp_cb_fn.set_debug)
		{
			ret = _g_pe_shp_cb_fn.set_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_debug() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE1_CMN_T for O20, E60
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_res_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_res_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_res_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for H13BX and H14A
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_res_cmn)
		{
			ret = _g_pe_shp_cb_fn.get_res_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_res_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set resolution horizontal control
 * - use input struct LX_PE_SHP_RE2_HOR_T for H13BX and H14A
 * - use input struct LX_PE_SHP_RE1_HOR_T for H13AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_res_hor)
		{
			ret = _g_pe_shp_cb_fn.set_res_hor(pstParams);
			PE_CHECK_CODE(ret, break, "set_res_hor() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get resolution horizontal control
 * - use input struct LX_PE_SHP_RE1_HOR_T for H13 and H14A
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_res_hor)
		{
			ret = _g_pe_shp_cb_fn.get_res_hor(pstParams);
			PE_CHECK_CODE(ret, break, "get_res_hor() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for H13BX and H14A
 * - use input struct LX_PE_SHP_RE1_VER_T for H13AX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_res_ver)
		{
			ret = _g_pe_shp_cb_fn.set_res_ver(pstParams);
			PE_CHECK_CODE(ret, break, "set_res_ver() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for H13BX and H14A
 * - use input struct LX_PE_SHP_RE1_VER_T for H13AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_res_ver)
		{
			ret = _g_pe_shp_cb_fn.get_res_ver(pstParams);
			PE_CHECK_CODE(ret, break, "get_res_ver() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for H13BX and H14A
 * - use input struct LX_PE_SHP_RE1_MISC_T for H13AX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_res_misc)
		{
			ret = _g_pe_shp_cb_fn.set_res_misc(pstParams);
			PE_CHECK_CODE(ret, break, "set_res_misc() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for H13BX and H14A
 * - use input struct LX_PE_SHP_RE1_MISC_T for H13AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_res_misc)
		{
			ret = _g_pe_shp_cb_fn.get_res_misc(pstParams);
			PE_CHECK_CODE(ret, break, "get_res_misc() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for H13 and H14A
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_edge_enh)
		{
			ret = _g_pe_shp_cb_fn.set_edge_enh(pstParams);
			PE_CHECK_CODE(ret, break, "set_edge_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for H13 and H14A
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_edge_enh)
		{
			ret = _g_pe_shp_cb_fn.get_edge_enh(pstParams);
			PE_CHECK_CODE(ret, break, "get_edge_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for H13 and H14A
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_detail_enh)
		{
			ret = _g_pe_shp_cb_fn.set_detail_enh(pstParams);
			PE_CHECK_CODE(ret, break, "set_detail_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for H13 and H14A
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_detail_enh)
		{
			ret = _g_pe_shp_cb_fn.get_detail_enh(pstParams);
			PE_CHECK_CODE(ret, break, "get_detail_enh() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSreReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sre_res_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_sre_res_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_sre_res_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSreReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sre_res_cmn)
		{
			ret = _g_pe_shp_cb_fn.get_sre_res_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_sre_res_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSreReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sre_res_hor)
		{
			ret = _g_pe_shp_cb_fn.set_sre_res_hor(pstParams);
			PE_CHECK_CODE(ret, break, "set_sre_res_hor() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for H13 and H14A
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSreReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sre_res_hor)
		{
			ret = _g_pe_shp_cb_fn.get_sre_res_hor(pstParams);
			PE_CHECK_CODE(ret, break, "get_sre_res_hor() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSreReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sre_res_ver)
		{
			ret = _g_pe_shp_cb_fn.set_sre_res_ver(pstParams);
			PE_CHECK_CODE(ret, break, "set_sre_res_ver() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSreReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sre_res_ver)
		{
			ret = _g_pe_shp_cb_fn.get_sre_res_ver(pstParams);
			PE_CHECK_CODE(ret, break, "get_sre_res_ver() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_RE1_MISC_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSreReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sre_res_misc)
		{
			ret = _g_pe_shp_cb_fn.set_sre_res_misc(pstParams);
			PE_CHECK_CODE(ret, break, "set_sre_res_misc() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr resolution misc control
 * - use input struct LX_PE_SHP_RE1_MISC_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSreReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sre_res_misc)
		{
			ret = _g_pe_shp_cb_fn.get_sre_res_misc(pstParams);
			PE_CHECK_CODE(ret, break, "get_sre_res_misc() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSreEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sre_edge_enh)
		{
			ret = _g_pe_shp_cb_fn.set_sre_edge_enh(pstParams);
			PE_CHECK_CODE(ret, break, "set_sre_edge_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSreEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sre_edge_enh)
		{
			ret = _g_pe_shp_cb_fn.get_sre_edge_enh(pstParams);
			PE_CHECK_CODE(ret, break, "get_sre_edge_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSreDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sre_detail_enh)
		{
			ret = _g_pe_shp_cb_fn.set_sre_detail_enh(pstParams);
			PE_CHECK_CODE(ret, break, "set_sre_detail_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSreDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sre_detail_enh)
		{
			ret = _g_pe_shp_cb_fn.get_sre_detail_enh(pstParams);
			PE_CHECK_CODE(ret, break, "get_sre_detail_enh() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSre2KReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_res_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_res_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_res_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSre2KReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_2ks_res_cmn)
		{
			ret = _g_pe_shp_cb_fn.get_2ks_res_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_2ks_res_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSre2KReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_res_hor)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_res_hor(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_res_hor() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr resolution horizontal control
 * - use input struct LX_PE_SHP_SR_RE_HOR_T for H13 and H14A
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSre2KReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_2ks_res_hor)
		{
			ret = _g_pe_shp_cb_fn.get_2ks_res_hor(pstParams);
			PE_CHECK_CODE(ret, break, "get_2ks_res_hor() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSre2KReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_res_ver)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_res_ver(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_res_ver() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr resolution vertical control
 * - use input struct LX_PE_SHP_SR_RE_VER_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSre2KReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_2ks_res_ver)
		{
			ret = _g_pe_shp_cb_fn.get_2ks_res_ver(pstParams);
			PE_CHECK_CODE(ret, break, "get_2ks_res_ver() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_RE1_MISC_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSre2KReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_res_misc)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_res_misc(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_res_misc() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr resolution misc control
 * - use input struct LX_PE_SHP_RE1_MISC_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSre2KReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_2ks_res_misc)
		{
			ret = _g_pe_shp_cb_fn.get_2ks_res_misc(pstParams);
			PE_CHECK_CODE(ret, break, "get_2ks_res_misc() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSre2KEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_edge_enh)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_edge_enh(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_edge_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr edge enhance control
 * - use input struct LX_PE_SHP_SR_EE_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSre2KEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_2ks_edge_enh)
		{
			ret = _g_pe_shp_cb_fn.get_2ks_edge_enh(pstParams);
			PE_CHECK_CODE(ret, break, "get_2ks_edge_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSre2KDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_detail_enh)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_detail_enh(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_detail_enh() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get sr detail enhance control
 * - use input struct LX_PE_SHP_SR_DE_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetSre2KDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_2ks_detail_enh)
		{
			ret = _g_pe_shp_cb_fn.get_2ks_detail_enh(pstParams);
			PE_CHECK_CODE(ret, break, "get_2ks_detail_enh() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set Psp
 * - use input struct LX_PE_SHP_SR_DE_T for H15X
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetPspCtrl(LX_PE_SHP_PSP_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_psp)
		{
			ret = _g_pe_shp_cb_fn.set_psp(pstParams);
			PE_CHECK_CODE(ret, break, "set_psp() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get psp
 * - use input struct LX_PE_SHP_SR_DE_T for H15X
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetPspCtrl(LX_PE_SHP_PSP_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_psp)
		{
			ret = _g_pe_shp_cb_fn.get_psp(pstParams);
			PE_CHECK_CODE(ret, break, "get_psp() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set OBC
 * - use input struct  LX_PE_VSD_OBC_CONT_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_obc_ctrl)
		{
			ret = _g_pe_shp_cb_fn.set_obc_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_obc_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get OBC
 * - use input struct  LX_PE_VSD_OBC_CONT_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetObcCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_obc_ctrl)
		{
			ret = _g_pe_shp_cb_fn.get_obc_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_obc_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set OBC lut
 * - use input struct  LX_PE_VSD_OBC_LUT_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetObcLUT(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_obc_lut)
		{
			ret = _g_pe_shp_cb_fn.set_obc_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_obc_lut() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get OBC lut
 * - use input struct  LX_PE_VSD_OBC_LUT_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetObcLUT(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_obc_lut)
		{
			ret = _g_pe_shp_cb_fn.get_obc_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_obc_lut() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get OBC data
 * - use input struct  LX_PE_VSD_OBC_DATA1_T
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_GetObcData(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_obc_data)
		{
			ret = _g_pe_shp_cb_fn.get_obc_data(pstParams);
			PE_CHECK_CODE(ret, break, "get_obc_data() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_SetSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sqm_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_SetSqmCmnCtrl2(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sqm_cmn2)
		{
			ret = _g_pe_shp_cb_fn.set_sqm_cmn2(pstParams);
			PE_CHECK_CODE(ret, break, "set_sqm_cmn2() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_GetSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sqm_cmn)
		{
			ret = _g_pe_shp_cb_fn.get_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_SetSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sqm_dtl)
		{
			ret = _g_pe_shp_cb_fn.set_sqm_dtl(pstParams);
			PE_CHECK_CODE(ret, break, "set_sqm_dtl() error.\n");
		}
	}while (0);
	return ret;
}
int PE_SHP_GetSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sqm_dtl)
		{
			ret = _g_pe_shp_cb_fn.get_sqm_dtl(pstParams);
			PE_CHECK_CODE(ret, break, "get_sqm_dtl() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_SetSre2KSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_sqm_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
int PE_SHP_SetSre2KSqmCmnCtrl2(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_sqm_cmn2)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_sqm_cmn2(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_sqm_cmn2() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_GetSre2KSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_2ks_sqm_cmn)
		{
			ret = _g_pe_shp_cb_fn.get_2ks_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_2ks_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_SetSre2KSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_sqm_dtl)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_sqm_dtl(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_sqm_dtl() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_GetSre2KSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_2ks_sqm_dtl)
		{
			ret = _g_pe_shp_cb_fn.get_2ks_sqm_dtl(pstParams);
			PE_CHECK_CODE(ret, break, "get_2ks_sqm_dtl() error.\n");
		}
	}while (0);
	return ret;
}
int PE_SHP_SetSreSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sre_sqm_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_sre_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_sre_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
int PE_SHP_GetSreSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sre_sqm_cmn)
		{
			ret = _g_pe_shp_cb_fn.get_sre_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_sre_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_SetSreSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sre_sqm_dtl)
		{
			ret = _g_pe_shp_cb_fn.set_sre_sqm_dtl(pstParams);
			PE_CHECK_CODE(ret, break, "set_sre_sqm_dtl() error.\n");
		}
	}while (0);
	return ret;
}

int PE_SHP_GetSreSqmDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_sre_sqm_dtl)
		{
			ret = _g_pe_shp_cb_fn.get_sre_sqm_dtl(pstParams);
			PE_CHECK_CODE(ret, break, "get_sre_sqm_dtl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set resolution common control -easy DB
 * - use input struct All 
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetReEasyCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_res_easy_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_res_easy_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_res_easy_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSre2KReEasyCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_2ks_res_easy_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_2ks_res_easy_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_2ks_res_easy_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set sr resolution enhance common parameter
 * - use input UINT32
 *
 * @param	*pstParams [in] void
 * @return	OK if success, ERROR otherwise.
 * @see 	function description
 * @author
 */
int PE_SHP_SetObcStereoCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_obc_stereo)
		{
			ret = _g_pe_shp_cb_fn.set_obc_stereo(pstParams);
			PE_CHECK_CODE(ret, break, "set_obc_stereo() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set f20 resolution enhance all parameter
 * - use input UINT32
 *
 * @param	*pstParams [in] void
 * @return	OK if success, ERROR otherwise.
 * @see 	function description
 * @author
 */
int PE_SHP_SetReAllCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_res_all)
		{
			ret = _g_pe_shp_cb_fn.set_res_all(pstParams);
			PE_CHECK_CODE(ret, break, "set_res_all() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get f20 resolution enhance all parameter
 * - use input UINT32
 *
 * @param	*pstParams [in] void
 * @return	OK if success, ERROR otherwise.
 * @see 	function description
 * @author
 */
int PE_SHP_GetReAllCtrl(void)
{
	int ret = RET_OK;
	do {
		//CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.get_res_all)
		{
			ret = _g_pe_shp_cb_fn.get_res_all();
			PE_CHECK_CODE(ret, break, "get_res_all() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set shp ellips
 * - use input UINT32
 *
 * @param	*pstParams [in] void
 * @return	OK if success, ERROR otherwise.
 * @see 	function description
 * @author
 */
int PE_SHP_SetEllipsCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_res_ellips)
		{
			ret = _g_pe_shp_cb_fn.set_res_ellips(pstParams);
			PE_CHECK_CODE(ret, break, "set_res_ellips() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE1_CMN_SUB_T for O24
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSreSubReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sub_res_cmn)
		{
			ret = _g_pe_shp_cb_fn.set_sub_res_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_sub_res_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set sr resolution misc control
 * - use input struct LX_PE_SHP_SR_RE1_MISC_SUB_T for O24
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
int PE_SHP_SetSreSubReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_shp_cb_fn.set_sub_res_misc)
		{
			ret = _g_pe_shp_cb_fn.set_sub_res_misc(pstParams);
			PE_CHECK_CODE(ret, break, "set_sub_res_misc() error.\n");
		}
	}while (0);
	return ret;
}

