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

/** @file pe_cmg.c
 *
 *  driver for picture enhance color management functions.
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

#include "pe_def.h"
#include "pe_cmg.h"
#include "pe_cmg_hw.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_CMG_DBG_PRINT(fmt, args...)	\
	if (_g_cmg_trace)\
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
	int (*set_cen_enable)(LX_PE_CMG_ENABLE_T *pstParams);
	int (*get_cen_enable)(LX_PE_CMG_ENABLE_T *pstParams);
	int (*set_cen_rgn_enable)(LX_PE_CMG_REGION_ENABLE_T *pstParams);
	int (*get_cen_rgn_enable)(LX_PE_CMG_REGION_ENABLE_T *pstParams);
	int (*set_cen_rgn2)(void *pstParams);
	int (*set_cen_rgn)(LX_PE_CMG_REGION_T *pstParams);
	int (*get_cen_rgn)(LX_PE_CMG_REGION_T *pstParams);
	int (*set_cen_rgn_ctrl)(LX_PE_CMG_REGION_CTRL_T *pstParams);
	int (*get_cen_rgn_ctrl)(LX_PE_CMG_REGION_CTRL_T *pstParams);
	int (*set_cen_gbl_ctrl)(LX_PE_CMG_GLOBAL_CTRL_T *pstParams);
	int (*get_cen_gbl_ctrl)(LX_PE_CMG_GLOBAL_CTRL_T *pstParams);
	int (*set_cen_color_ctrl)(LX_PE_CMG_COLOR_CTRL_T *pstParams);
	int (*get_cen_color_ctrl)(LX_PE_CMG_COLOR_CTRL_T *pstParams);
	int (*set_cw_ctrl)(LX_PE_CMG_CW_CTRL_T *pstParams);
	int (*get_cw_ctrl)(LX_PE_CMG_CW_CTRL_T *pstParams);
	int (*set_cw_gain_ctrl)(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
	int (*get_cw_gain_ctrl)(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
	int (*set_sat_gain_lut)(LX_PE_CMG_SAT_GAIN_LUT_T *pstParams);
	int (*get_sat_gain_lut)(LX_PE_CMG_SAT_GAIN_LUT_T *pstParams);
	int (*set_ext_inner_pattern)(LX_PE_CMG_EXT_PATTERN_INFO_T *pstParams);
	int (*set_cw_table_ctrl)(LX_PE_CMG_CW_TABLE_CTRL_T *pstParams);
	int (*get_cw_table_ctrl)(LX_PE_CMG_CW_TABLE_CTRL_T *pstParams);
	int (*set_vspcc_ctrl2)(void *pstParams);
	int (*set_vspcc_ctrl)(LX_PE_CMG_VSPCC_CTRL_T *pstParams);
	int (*get_vspcc_ctrl)(LX_PE_CMG_VSPCC_CTRL_T *pstParams);
	int (*set_dse_ctrl)(void *pstParams);
	int (*get_dse_ctrl)(void *pstParams);
	int (*set_cen_rgn_all)(LX_PE_CMG_REGION_ALL_T *pstParams);
}
PE_CMG_CB_FUNC_T;

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
static PE_CMG_CB_FUNC_T _g_pe_cmg_cb_fn;
static UINT32 _g_cmg_trace=0x0;	//default should be off.

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
int PE_CMG_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_cmg_cb_fn, 0, sizeof(PE_CMG_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_cmg_cb_fn.hw_init				= PE_CMG_HW_O26_Init;
			_g_pe_cmg_cb_fn.set_default			= NULL;//NULL;
			_g_pe_cmg_cb_fn.set_debug			= PE_CMG_HW_O26_SetDebugSettings;
			_g_pe_cmg_cb_fn.set_cen_enable		= NULL;
			_g_pe_cmg_cb_fn.get_cen_enable		= NULL;
			_g_pe_cmg_cb_fn.set_cen_rgn_enable	= PE_CMG_HW_O26_SetCenRegionEnable;
			_g_pe_cmg_cb_fn.get_cen_rgn_enable	= PE_CMG_HW_O26_GetCenRegionEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn2		= PE_CMG_HW_O26_SetCenRegion2;
			_g_pe_cmg_cb_fn.set_cen_rgn			= PE_CMG_HW_O26_SetCenRegion;
			_g_pe_cmg_cb_fn.get_cen_rgn			= PE_CMG_HW_O26_GetCenRegion;
			_g_pe_cmg_cb_fn.set_cen_rgn_ctrl	= PE_CMG_HW_O26_SetCenRegionCtrl;
			_g_pe_cmg_cb_fn.get_cen_rgn_ctrl	= PE_CMG_HW_O26_GetCenRegionCtrl;
			_g_pe_cmg_cb_fn.set_cen_gbl_ctrl	= NULL;
			_g_pe_cmg_cb_fn.get_cen_gbl_ctrl	= NULL;
			_g_pe_cmg_cb_fn.set_cen_color_ctrl	= PE_CMG_HW_O26_SetCenColorCtrl;
			_g_pe_cmg_cb_fn.get_cen_color_ctrl	= PE_CMG_HW_O26_GetCenColorCtrl;
			_g_pe_cmg_cb_fn.set_cw_ctrl			= PE_CMG_HW_O26_SetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.get_cw_ctrl			= PE_CMG_HW_O26_GetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.set_cw_gain_ctrl	= PE_CMG_HW_O26_SetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.get_cw_gain_ctrl	= PE_CMG_HW_O26_GetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.set_sat_gain_lut	= NULL;
			_g_pe_cmg_cb_fn.get_sat_gain_lut	= NULL;
			_g_pe_cmg_cb_fn.set_ext_inner_pattern	= PE_CMG_HW_O26_SetExtInnerPattern;
			_g_pe_cmg_cb_fn.set_cw_table_ctrl		= PE_CMG_HW_O26_SetClearWhiteTableCtrl;
			_g_pe_cmg_cb_fn.get_cw_table_ctrl		= NULL;
			_g_pe_cmg_cb_fn.set_vspcc_ctrl			= PE_CMG_HW_O26_SetVspccCtrl;
			_g_pe_cmg_cb_fn.set_vspcc_ctrl2			= PE_CMG_HW_O26_SetVspccCtrl2;
			_g_pe_cmg_cb_fn.get_vspcc_ctrl			= NULL;
			_g_pe_cmg_cb_fn.set_dse_ctrl			= PE_CMG_HW_O26_SetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.get_dse_ctrl			= PE_CMG_HW_O26_GetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.set_cen_rgn_all			= PE_CMG_HW_O26_SetCenRegionAll;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_cmg_cb_fn.hw_init				= PE_CMG_HW_O24_Init;
			_g_pe_cmg_cb_fn.set_default			= NULL;//NULL;
			_g_pe_cmg_cb_fn.set_debug			= PE_CMG_HW_O24_SetDebugSettings;
			_g_pe_cmg_cb_fn.set_cen_enable		= NULL;
			_g_pe_cmg_cb_fn.get_cen_enable		= NULL;
			_g_pe_cmg_cb_fn.set_cen_rgn_enable	= PE_CMG_HW_O24_SetCenRegionEnable;
			_g_pe_cmg_cb_fn.get_cen_rgn_enable	= PE_CMG_HW_O24_GetCenRegionEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn			= PE_CMG_HW_O24_SetCenRegion;
			_g_pe_cmg_cb_fn.get_cen_rgn			= PE_CMG_HW_O24_GetCenRegion;
			_g_pe_cmg_cb_fn.set_cen_rgn_ctrl	= PE_CMG_HW_O24_SetCenRegionCtrl;
			_g_pe_cmg_cb_fn.get_cen_rgn_ctrl	= PE_CMG_HW_O24_GetCenRegionCtrl;
			_g_pe_cmg_cb_fn.set_cen_gbl_ctrl	= NULL;
			_g_pe_cmg_cb_fn.get_cen_gbl_ctrl	= NULL;
			_g_pe_cmg_cb_fn.set_cen_color_ctrl	= PE_CMG_HW_O24_SetCenColorCtrl;
			_g_pe_cmg_cb_fn.get_cen_color_ctrl	= PE_CMG_HW_O24_GetCenColorCtrl;
			_g_pe_cmg_cb_fn.set_cw_ctrl			= PE_CMG_HW_O24_SetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.get_cw_ctrl			= PE_CMG_HW_O24_GetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.set_cw_gain_ctrl	= PE_CMG_HW_O24_SetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.get_cw_gain_ctrl	= PE_CMG_HW_O24_GetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.set_sat_gain_lut	= NULL;
			_g_pe_cmg_cb_fn.get_sat_gain_lut	= NULL;
			_g_pe_cmg_cb_fn.set_ext_inner_pattern	= PE_CMG_HW_O24_SetExtInnerPattern;
			_g_pe_cmg_cb_fn.set_cw_table_ctrl		= PE_CMG_HW_O24_SetClearWhiteTableCtrl;
			_g_pe_cmg_cb_fn.get_cw_table_ctrl		= NULL;
			_g_pe_cmg_cb_fn.set_vspcc_ctrl			= PE_CMG_HW_O24_SetVspccCtrl;
			_g_pe_cmg_cb_fn.get_vspcc_ctrl			= NULL;
			_g_pe_cmg_cb_fn.set_dse_ctrl			= PE_CMG_HW_O24_SetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.get_dse_ctrl			= PE_CMG_HW_O24_GetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.set_cen_rgn_all			= PE_CMG_HW_O24_SetCenRegionAll;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_cmg_cb_fn.hw_init				= PE_CMG_HW_M23_Init;
			_g_pe_cmg_cb_fn.set_debug			= PE_CMG_HW_M23_SetDebugSettings;
			_g_pe_cmg_cb_fn.set_cen_rgn_enable	= PE_CMG_HW_M23_SetCenRegionEnable;
			_g_pe_cmg_cb_fn.get_cen_rgn_enable	= PE_CMG_HW_M23_GetCenRegionEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn			= PE_CMG_HW_M23_SetCenRegion;
			_g_pe_cmg_cb_fn.get_cen_rgn			= PE_CMG_HW_M23_GetCenRegion;
			_g_pe_cmg_cb_fn.set_cen_rgn_ctrl	= PE_CMG_HW_M23_SetCenRegionCtrl;
			_g_pe_cmg_cb_fn.get_cen_rgn_ctrl	= PE_CMG_HW_M23_GetCenRegionCtrl;
			_g_pe_cmg_cb_fn.set_cen_color_ctrl	= PE_CMG_HW_M23_SetCenColorCtrl;
			_g_pe_cmg_cb_fn.get_cen_color_ctrl	= PE_CMG_HW_M23_GetCenColorCtrl;
			_g_pe_cmg_cb_fn.set_cw_ctrl			= PE_CMG_HW_M23_SetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.get_cw_ctrl			= PE_CMG_HW_M23_GetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.set_cw_gain_ctrl	= PE_CMG_HW_M23_SetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.get_cw_gain_ctrl	= PE_CMG_HW_M23_GetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.set_ext_inner_pattern	= PE_CMG_HW_M23_SetExtInnerPattern;
			_g_pe_cmg_cb_fn.set_cw_table_ctrl		= PE_CMG_HW_M23_SetClearWhiteTableCtrl;
			_g_pe_cmg_cb_fn.set_vspcc_ctrl			= PE_CMG_HW_M23_SetVspccCtrl;
			_g_pe_cmg_cb_fn.set_dse_ctrl			= PE_CMG_HW_M23_SetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.get_dse_ctrl			= PE_CMG_HW_M23_GetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.set_cen_rgn_all			= PE_CMG_HW_M23_SetCenRegionAll;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_cmg_cb_fn.hw_init				= PE_CMG_HW_O22_Init;
			_g_pe_cmg_cb_fn.set_default			= NULL;//NULL;
			_g_pe_cmg_cb_fn.set_debug			= PE_CMG_HW_O22_SetDebugSettings;
			_g_pe_cmg_cb_fn.set_cen_enable		= NULL;
			_g_pe_cmg_cb_fn.get_cen_enable		= NULL;
			_g_pe_cmg_cb_fn.set_cen_rgn_enable	= PE_CMG_HW_O22_SetCenRegionEnable;
			_g_pe_cmg_cb_fn.get_cen_rgn_enable	= PE_CMG_HW_O22_GetCenRegionEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn			= PE_CMG_HW_O22_SetCenRegion;
			_g_pe_cmg_cb_fn.get_cen_rgn			= PE_CMG_HW_O22_GetCenRegion;
			_g_pe_cmg_cb_fn.set_cen_rgn_ctrl	= PE_CMG_HW_O22_SetCenRegionCtrl;
			_g_pe_cmg_cb_fn.get_cen_rgn_ctrl	= PE_CMG_HW_O22_GetCenRegionCtrl;
			_g_pe_cmg_cb_fn.set_cen_gbl_ctrl	= NULL;
			_g_pe_cmg_cb_fn.get_cen_gbl_ctrl	= NULL;
			_g_pe_cmg_cb_fn.set_cen_color_ctrl	= PE_CMG_HW_O22_SetCenColorCtrl;
			_g_pe_cmg_cb_fn.get_cen_color_ctrl	= PE_CMG_HW_O22_GetCenColorCtrl;
			_g_pe_cmg_cb_fn.set_cw_ctrl			= PE_CMG_HW_O22_SetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.get_cw_ctrl			= PE_CMG_HW_O22_GetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.set_cw_gain_ctrl	= PE_CMG_HW_O22_SetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.get_cw_gain_ctrl	= PE_CMG_HW_O22_GetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.set_sat_gain_lut	= NULL;
			_g_pe_cmg_cb_fn.get_sat_gain_lut	= NULL;
			_g_pe_cmg_cb_fn.set_ext_inner_pattern	= PE_CMG_HW_O22_SetExtInnerPattern;
			_g_pe_cmg_cb_fn.set_cw_table_ctrl		= PE_CMG_HW_O22_SetClearWhiteTableCtrl;
			_g_pe_cmg_cb_fn.get_cw_table_ctrl		= NULL;
			_g_pe_cmg_cb_fn.set_vspcc_ctrl			= PE_CMG_HW_O22_SetVspccCtrl;
			_g_pe_cmg_cb_fn.get_vspcc_ctrl			= NULL;
			_g_pe_cmg_cb_fn.set_dse_ctrl			= PE_CMG_HW_O22_SetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.get_dse_ctrl			= PE_CMG_HW_O22_GetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.set_cen_rgn_all			= PE_CMG_HW_O22_SetCenRegionAll;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_cmg_cb_fn.hw_init				= PE_CMG_HW_E60_Init;
			_g_pe_cmg_cb_fn.set_default			= NULL;//NULL;
			_g_pe_cmg_cb_fn.set_debug			= PE_CMG_HW_E60_SetDebugSettings;
			_g_pe_cmg_cb_fn.set_cen_enable		= NULL;
			_g_pe_cmg_cb_fn.get_cen_enable		= NULL;
			_g_pe_cmg_cb_fn.set_cen_rgn_enable	= PE_CMG_HW_E60_SetCenRegionEnable;
			_g_pe_cmg_cb_fn.get_cen_rgn_enable	= PE_CMG_HW_E60_GetCenRegionEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn			= PE_CMG_HW_E60_SetCenRegion;
			_g_pe_cmg_cb_fn.get_cen_rgn			= PE_CMG_HW_E60_GetCenRegion;
			_g_pe_cmg_cb_fn.set_cen_rgn_ctrl	= PE_CMG_HW_E60_SetCenRegionCtrl;
			_g_pe_cmg_cb_fn.get_cen_rgn_ctrl	= PE_CMG_HW_E60_GetCenRegionCtrl;
			_g_pe_cmg_cb_fn.set_cen_gbl_ctrl	= NULL;
			_g_pe_cmg_cb_fn.get_cen_gbl_ctrl	= NULL;
			_g_pe_cmg_cb_fn.set_cen_color_ctrl	= PE_CMG_HW_E60_SetCenColorCtrl;
			_g_pe_cmg_cb_fn.get_cen_color_ctrl	= PE_CMG_HW_E60_GetCenColorCtrl;
			_g_pe_cmg_cb_fn.set_cw_ctrl			= PE_CMG_HW_E60_SetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.get_cw_ctrl			= PE_CMG_HW_E60_GetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.set_cw_gain_ctrl	= PE_CMG_HW_E60_SetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.get_cw_gain_ctrl	= PE_CMG_HW_E60_GetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.set_sat_gain_lut	= NULL;
			_g_pe_cmg_cb_fn.get_sat_gain_lut	= NULL;
			_g_pe_cmg_cb_fn.set_ext_inner_pattern	= PE_CMG_HW_E60_SetExtInnerPattern;
			_g_pe_cmg_cb_fn.set_cw_table_ctrl		= PE_CMG_HW_E60_SetClearWhiteTableCtrl;
			_g_pe_cmg_cb_fn.get_cw_table_ctrl		= NULL;
			_g_pe_cmg_cb_fn.set_vspcc_ctrl			= PE_CMG_HW_E60_SetVspccCtrl;
			_g_pe_cmg_cb_fn.get_vspcc_ctrl			= NULL;
			_g_pe_cmg_cb_fn.set_dse_ctrl			= PE_CMG_HW_E60_SetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.get_dse_ctrl			= PE_CMG_HW_E60_GetDseCtrl;//TODO:incompatible pointer type
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_cmg_cb_fn.hw_init				= PE_CMG_HW_O20_Init;
			_g_pe_cmg_cb_fn.set_default			= NULL;//NULL;
			_g_pe_cmg_cb_fn.set_debug			= PE_CMG_HW_O20_SetDebugSettings;
			_g_pe_cmg_cb_fn.set_cen_enable		= PE_CMG_HW_O20_SetCenEnable;
			_g_pe_cmg_cb_fn.get_cen_enable		= PE_CMG_HW_O20_GetCenEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn_enable	= PE_CMG_HW_O20_SetCenRegionEnable;
			_g_pe_cmg_cb_fn.get_cen_rgn_enable	= PE_CMG_HW_O20_GetCenRegionEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn			= PE_CMG_HW_O20_SetCenRegion;
			_g_pe_cmg_cb_fn.get_cen_rgn			= PE_CMG_HW_O20_GetCenRegion;
			_g_pe_cmg_cb_fn.set_cen_rgn_ctrl	= PE_CMG_HW_O20_SetCenRegionCtrl;
			_g_pe_cmg_cb_fn.get_cen_rgn_ctrl	= PE_CMG_HW_O20_GetCenRegionCtrl;
			_g_pe_cmg_cb_fn.set_cen_gbl_ctrl	= PE_CMG_HW_O20_SetCenGlobalCtrl;
			_g_pe_cmg_cb_fn.get_cen_gbl_ctrl	= PE_CMG_HW_O20_GetCenGlobalCtrl;
			_g_pe_cmg_cb_fn.set_cen_color_ctrl	= PE_CMG_HW_O20_SetCenColorCtrl;
			_g_pe_cmg_cb_fn.get_cen_color_ctrl	= PE_CMG_HW_O20_GetCenColorCtrl;
			_g_pe_cmg_cb_fn.set_cw_ctrl			= PE_CMG_HW_O20_SetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.get_cw_ctrl			= PE_CMG_HW_O20_GetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.set_cw_gain_ctrl	= PE_CMG_HW_O20_SetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.get_cw_gain_ctrl	= PE_CMG_HW_O20_GetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.set_sat_gain_lut	= PE_CMG_HW_O20_SetSaturationGainLUT;
			_g_pe_cmg_cb_fn.get_sat_gain_lut	= PE_CMG_HW_O20_GetSaturationGainLUT;
			_g_pe_cmg_cb_fn.set_ext_inner_pattern	= PE_CMG_HW_O20_SetExtInnerPattern;
			_g_pe_cmg_cb_fn.set_cw_table_ctrl		= PE_CMG_HW_O20_SetClearWhiteTableCtrl;
			_g_pe_cmg_cb_fn.get_cw_table_ctrl		= NULL;
			_g_pe_cmg_cb_fn.set_vspcc_ctrl			= PE_CMG_HW_O20_SetVspccCtrl;
			_g_pe_cmg_cb_fn.get_vspcc_ctrl			= NULL;
			_g_pe_cmg_cb_fn.set_dse_ctrl			= PE_CMG_HW_O20_SetDseCtrl;//TODO:incompatible pointer type
			_g_pe_cmg_cb_fn.get_dse_ctrl			= PE_CMG_HW_O20_GetDseCtrl;//TODO:incompatible pointer type
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O18
		if (PE_KDRV_VER_O18)
		{
			_g_pe_cmg_cb_fn.hw_init				= PE_CMG_HW_O18_Init;
			_g_pe_cmg_cb_fn.set_default			= NULL;//NULL;
			_g_pe_cmg_cb_fn.set_debug			= PE_CMG_HW_O18_SetDebugSettings;
			_g_pe_cmg_cb_fn.set_cen_enable		= PE_CMG_HW_O18_SetCenEnable;
			_g_pe_cmg_cb_fn.get_cen_enable		= PE_CMG_HW_O18_GetCenEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn_enable	= PE_CMG_HW_O18_SetCenRegionEnable;
			_g_pe_cmg_cb_fn.get_cen_rgn_enable	= PE_CMG_HW_O18_GetCenRegionEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn			= PE_CMG_HW_O18_SetCenRegion;
			_g_pe_cmg_cb_fn.get_cen_rgn			= PE_CMG_HW_O18_GetCenRegion;
			_g_pe_cmg_cb_fn.set_cen_rgn_ctrl	= PE_CMG_HW_O18_SetCenRegionCtrl;
			_g_pe_cmg_cb_fn.get_cen_rgn_ctrl	= PE_CMG_HW_O18_GetCenRegionCtrl;
			_g_pe_cmg_cb_fn.set_cen_gbl_ctrl	= PE_CMG_HW_O18_SetCenGlobalCtrl;
			_g_pe_cmg_cb_fn.get_cen_gbl_ctrl	= PE_CMG_HW_O18_GetCenGlobalCtrl;
			_g_pe_cmg_cb_fn.set_cen_color_ctrl	= PE_CMG_HW_O18_SetCenColorCtrl;
			_g_pe_cmg_cb_fn.get_cen_color_ctrl	= PE_CMG_HW_O18_GetCenColorCtrl;
			_g_pe_cmg_cb_fn.set_cw_ctrl			= PE_CMG_HW_O18_SetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.get_cw_ctrl			= PE_CMG_HW_O18_GetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.set_cw_gain_ctrl	= PE_CMG_HW_O18_SetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.get_cw_gain_ctrl	= PE_CMG_HW_O18_GetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.set_sat_gain_lut	= PE_CMG_HW_O18_SetSaturationGainLUT;
			_g_pe_cmg_cb_fn.get_sat_gain_lut	= PE_CMG_HW_O18_GetSaturationGainLUT;
			_g_pe_cmg_cb_fn.set_ext_inner_pattern	= PE_CMG_HW_O18_SetExtInnerPattern;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M19
		if (PE_KDRV_VER_M19)
		{
			_g_pe_cmg_cb_fn.hw_init				= PE_CMG_HW_M19_Init;
			_g_pe_cmg_cb_fn.set_default			= NULL;//NULL;
			_g_pe_cmg_cb_fn.set_debug			= PE_CMG_HW_M19_SetDebugSettings;
			_g_pe_cmg_cb_fn.set_cen_enable		= PE_CMG_HW_M19_SetCenEnable;
			_g_pe_cmg_cb_fn.get_cen_enable		= PE_CMG_HW_M19_GetCenEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn_enable	= PE_CMG_HW_M19_SetCenRegionEnable;
			_g_pe_cmg_cb_fn.get_cen_rgn_enable	= PE_CMG_HW_M19_GetCenRegionEnable;
			_g_pe_cmg_cb_fn.set_cen_rgn			= PE_CMG_HW_M19_SetCenRegion;
			_g_pe_cmg_cb_fn.get_cen_rgn			= PE_CMG_HW_M19_GetCenRegion;
			_g_pe_cmg_cb_fn.set_cen_rgn_ctrl	= PE_CMG_HW_M19_SetCenRegionCtrl;
			_g_pe_cmg_cb_fn.get_cen_rgn_ctrl	= PE_CMG_HW_M19_GetCenRegionCtrl;
			_g_pe_cmg_cb_fn.set_cen_gbl_ctrl	= PE_CMG_HW_M19_SetCenGlobalCtrl;
			_g_pe_cmg_cb_fn.get_cen_gbl_ctrl	= PE_CMG_HW_M19_GetCenGlobalCtrl;
			_g_pe_cmg_cb_fn.set_cen_color_ctrl	= PE_CMG_HW_M19_SetCenColorCtrl;
			_g_pe_cmg_cb_fn.get_cen_color_ctrl	= PE_CMG_HW_M19_GetCenColorCtrl;
			_g_pe_cmg_cb_fn.set_cw_ctrl			= PE_CMG_HW_M19_SetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.get_cw_ctrl			= PE_CMG_HW_M19_GetClearWhiteCtrl;
			_g_pe_cmg_cb_fn.set_cw_gain_ctrl	= PE_CMG_HW_M19_SetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.get_cw_gain_ctrl	= PE_CMG_HW_M19_GetClearWhiteGainCtrl;
			_g_pe_cmg_cb_fn.set_ext_inner_pattern	= PE_CMG_HW_M19_SetExtInnerPattern;
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
 * init color management
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.hw_init)
		{
			ret = _g_pe_cmg_cb_fn.hw_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_init() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of cmg setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CMG_SET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_CMG_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s, %d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s, %d] %s() error.\n", __F__, __L__, #_func);\
			PE_CMG_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s, %d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_CMG_SET_FUNC(LX_PE_CMG_COLOR_CTRL_T,		PE_CMG_SetCenColorCtrl);
		PE_CMG_SET_FUNC(LX_PE_CMG_ENABLE_T,			PE_CMG_SetCenEnable);
		PE_CMG_SET_FUNC(LX_PE_CMG_REGION_ENABLE_T,	PE_CMG_SetCenRegionEnable);
		PE_CMG_SET_FUNC(LX_PE_CMG_REGION_T,			PE_CMG_SetCenRegion);
		PE_CMG_SET_FUNC(LX_PE_CMG_REGION_CTRL_T,	PE_CMG_SetCenRegionCtrl);
		PE_CMG_SET_FUNC(LX_PE_CMG_GLOBAL_CTRL_T,	PE_CMG_SetCenGlobalCtrl);
		PE_CMG_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_CMG_SetDefaultSettings);
		PE_CMG_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_CMG_SetDebugSettings);
		PE_CMG_SET_FUNC(LX_PE_CMG_CW_CTRL_T,		PE_CMG_SetClearWhiteCtrl);
		PE_CMG_SET_FUNC(LX_PE_CMG_CW_GAIN_CTRL_T,	PE_CMG_SetClearWhiteGainCtrl);
		PE_CMG_SET_FUNC(LX_PE_CMG_SAT_GAIN_LUT_T,	PE_CMG_SetSaturationGainLUT);
		PE_CMG_SET_FUNC(LX_PE_CMG_EXT_PATTERN_INFO_T,	PE_CMG_SetExtInnerPattern);
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
 * standard function of cmg getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CMG_GET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_CMG_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s, %d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s, %d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
			PE_CMG_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s, %d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_CMG_GET_FUNC(LX_PE_CMG_COLOR_CTRL_T,		PE_CMG_GetCenColorCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_ENABLE_T,			PE_CMG_GetCenEnable);
		PE_CMG_GET_FUNC(LX_PE_CMG_REGION_ENABLE_T,	PE_CMG_GetCenRegionEnable);
		PE_CMG_GET_FUNC(LX_PE_CMG_REGION_T,			PE_CMG_GetCenRegion);
		PE_CMG_GET_FUNC(LX_PE_CMG_REGION_CTRL_T,	PE_CMG_GetCenRegionCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_GLOBAL_CTRL_T,	PE_CMG_GetCenGlobalCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_CW_CTRL_T,		PE_CMG_GetClearWhiteCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_CW_GAIN_CTRL_T,	PE_CMG_GetClearWhiteGainCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_SAT_GAIN_LUT_T,	PE_CMG_GetSaturationGainLUT);
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
int PE_CMG_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_DBG_PRINT("[win id:%d]\n", pstParams->win_id);
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
int PE_CMG_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if (pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmg_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(CMG)))? 0x1:0x0;
		}
		if(_g_pe_cmg_cb_fn.set_debug)
		{
			ret = _g_pe_cmg_cb_fn.set_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_debug() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set cen enable
 *
 * @param   *pstParams [in] LX_PE_CMG_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetCenEnable(LX_PE_CMG_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cen_enable)
		{
			ret = _g_pe_cmg_cb_fn.set_cen_enable(pstParams);
			PE_CHECK_CODE(ret, break, "set_cen_enable() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get cen enable
 *
 * @param   *pstParams [in/out] LX_PE_CMG_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetCenEnable(LX_PE_CMG_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.get_cen_enable)
		{
			ret = _g_pe_cmg_cb_fn.get_cen_enable(pstParams);
			PE_CHECK_CODE(ret, break, "get_cen_enable() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set cen region enable
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cen_rgn_enable)
		{
			ret = _g_pe_cmg_cb_fn.set_cen_rgn_enable(pstParams);
			PE_CHECK_CODE(ret, break, "set_cen_rgn_enable() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get cen region enable
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.get_cen_rgn_enable)
		{
			ret = _g_pe_cmg_cb_fn.get_cen_rgn_enable(pstParams);
			PE_CHECK_CODE(ret, break, "get_cen_rgn_enable() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetCenRegion2(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cen_rgn2)
		{
			ret = _g_pe_cmg_cb_fn.set_cen_rgn2(pstParams);
			PE_CHECK_CODE(ret, break, "set_cen_rgn2() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cen_rgn)
		{
			ret = _g_pe_cmg_cb_fn.set_cen_rgn(pstParams);
			PE_CHECK_CODE(ret, break, "set_cen_rgn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get cen region
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.get_cen_rgn)
		{
			ret = _g_pe_cmg_cb_fn.get_cen_rgn(pstParams);
			PE_CHECK_CODE(ret, break, "get_cen_rgn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set cen region all
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetCenRegionAll(LX_PE_CMG_REGION_ALL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cen_rgn_all)
		{
			ret = _g_pe_cmg_cb_fn.set_cen_rgn_all(pstParams);
			PE_CHECK_CODE(ret, break, "set_cen_rgn_all() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set cen region ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cen_rgn_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.set_cen_rgn_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_cen_rgn_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get cen region ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.get_cen_rgn_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.get_cen_rgn_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_cen_rgn_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set cen global ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_GLOBAL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cen_gbl_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.set_cen_gbl_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_cen_gbl_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get cen global ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_GLOBAL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.get_cen_gbl_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.get_cen_gbl_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_cen_gbl_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set cen color ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_COLOR_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cen_color_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.set_cen_color_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_cen_color_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get cen color ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_COLOR_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.get_cen_color_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.get_cen_color_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_cen_color_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set clear white
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cw_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.set_cw_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_cw_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get clear white
 *
 * @param   *pstParams [in/out] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.get_cw_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.get_cw_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_cw_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set clear white gain
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_GAIN_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cw_gain_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.set_cw_gain_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_cw_gain_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get clear white gain
 *
 * @param   *pstParams [in/out] LX_PE_CMG_CW_GAIN_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.get_cw_gain_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.get_cw_gain_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_cw_gain_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set saturation gain LUT
 *
 * @param	*pstParams [in] LX_PE_CMG_SAT_GAIN_LUT_T
 * @return	OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetSaturationGainLUT(LX_PE_CMG_SAT_GAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (_g_pe_cmg_cb_fn.set_sat_gain_lut)
		{
			ret = _g_pe_cmg_cb_fn.set_sat_gain_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_sat_gain_lut() error.\n");
		}
	} while (0);
	return ret;
}
/**
 * get saturation gain LUT
 *
 * @param	*pstParams [in] LX_PE_CMG_SAT_GAIN_LUT_T
 * @return	OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetSaturationGainLUT(LX_PE_CMG_SAT_GAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (_g_pe_cmg_cb_fn.get_sat_gain_lut)
		{
			ret = _g_pe_cmg_cb_fn.get_sat_gain_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_sat_gain_lut() error.\n");
		}
	} while (0);
	return ret;
}
/**
 * set Ext/Inner Pattern
 *
 * @param	*pstParams [in] LX_PE_CMG_EXT_PATTERN_INFO_T
 * @return	OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetExtInnerPattern(LX_PE_CMG_EXT_PATTERN_INFO_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (_g_pe_cmg_cb_fn.set_ext_inner_pattern)
		{
			ret = _g_pe_cmg_cb_fn.set_ext_inner_pattern(pstParams);
			PE_CHECK_CODE(ret, break, "set_ext_inner_pattern() error.\n");
		}
	} while (0);
	return ret;
}
/**
 * set clear white
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetClearWhiteTableCtrl(LX_PE_CMG_CW_TABLE_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_cw_table_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.set_cw_table_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_cw_table_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set clear white
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetVspccCtrl(LX_PE_CMG_VSPCC_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_vspcc_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.set_vspcc_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_vspcc_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set clear white
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetVspccCtrl2(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmg_cb_fn.set_vspcc_ctrl2)
		{
			ret = _g_pe_cmg_cb_fn.set_vspcc_ctrl2(pstParams);
			PE_CHECK_CODE(ret, break, "set_vspcc_ctrl2() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dse
 *
 * @param	*pstParams [in] LX_PE_CMG_DSE_CTRL_T
 * @return	OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (_g_pe_cmg_cb_fn.set_dse_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.set_dse_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_dse_ctrl() error.\n");
		}
	} while (0);
	return ret;
}
/**
 * get dse
 *
 * @param	*pstParams [in] LX_PE_CMG_DSE_CTRL_T
 * @return	OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetDseCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if (_g_pe_cmg_cb_fn.get_dse_ctrl)
		{
			ret = _g_pe_cmg_cb_fn.get_dse_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_dse_ctrl() error.\n");
		}
	} while (0);
	return ret;
}

