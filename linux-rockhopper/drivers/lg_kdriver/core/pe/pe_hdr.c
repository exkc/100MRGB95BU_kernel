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

/** @file pe_hdr.c
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

#include "pe_reg.h"
#include "pe_reg_hw.h"
#include "pe_def.h"
#include "pe_etc.h"
#include "pe_etc_hw.h"
#include "pe_hdr.h"
#include "pe_hdr_hw.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_HDR_DBG_PRINT(fmt, args...)	\
	if (_g_hdr_trace)\
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
	int (*get_histo_info)(LX_PE_HDR_HISTO_INFO_T *pstParams);
	int (*get_info)(LX_PE_HDR_INFO_T *pstParams);
	int (*set_3d_lut_info)(LX_PE_HDR_3D_LUT_INFO_T *pstParams);
	int (*get_3d_lut_info)(LX_PE_HDR_3D_LUT_INFO_T *pstParams);
	int (*set_mode_info)(LX_PE_HDR_MODE_INFO_T *pstParams);
	int (*get_mode_info)(LX_PE_HDR_MODE_INFO_T *pstParams);
	int (*set_tonemap_lut)(LX_PE_HDR_TONEMAP_LUT_T *pstParams);
	int (*get_tonemap_lut)(LX_PE_HDR_TONEMAP_LUT_T *pstParams);
	int (*set_ygain_lut)(LX_PE_HDR_YGAIN_LUT_T *pstParams);
	int (*get_ygain_lut)(LX_PE_HDR_YGAIN_LUT_T *pstParams);
	int (*set_csc)(LX_PE_HDR_CSC_T *pstParams);
	int (*get_csc)(LX_PE_HDR_CSC_T *pstParams);
	int (*set_eotf_lut)(LX_PE_HDR_EOTF_LUT_T *pstParams);
	int (*get_eotf_lut)(LX_PE_HDR_EOTF_LUT_T *pstParams);
	int (*set_oetf_lut)(LX_PE_HDR_OETF_LUT_T *pstParams);
	int (*get_oetf_lut)(LX_PE_HDR_OETF_LUT_T *pstParams);
	int (*set_gamma_en)(LX_PE_HDR_GAMMA_EN_T *pstParams);
	int (*get_gamma_en)(LX_PE_HDR_GAMMA_EN_T *pstParams);
	int (*set_ccr)(LX_PE_HDR_CCR_T *pstParams);
	int (*get_ccr)(LX_PE_HDR_CCR_T *pstParams);
	int (*set_lllut)(LX_PE_HDR_LLLUT_T *pstParams);
	int (*get_lllut)(LX_PE_HDR_LLLUT_T *pstParams);
	int (*set_pattern)(void *pstParams);
	int (*get_pixeldata)(void *pstParams);
	int (*proc_show_histo)(int id, void *p, void *data);
}
PE_HDR_CB_FUNC_T;

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
static PE_HDR_CB_FUNC_T _g_pe_hdr_cb_fn;
static UINT32 _g_hdr_trace=0x0;	//default should be off.

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
int PE_HDR_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_hdr_cb_fn, 0, sizeof(PE_HDR_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_O26_Init;
			_g_pe_hdr_cb_fn.set_debug			= NULL;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_O26_GetHistoInfo;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_O26_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_O26_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_O26_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_O26_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_O26_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_O26_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_O26_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_O26_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_O26_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_O26_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_O26_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_O26_GetOetfLut;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_O26_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_O26_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_pattern			= PE_HDR_HW_O26_SetPattern;
			_g_pe_hdr_cb_fn.proc_show_histo     = pe_hdr_hw_o26_proc_show_histo;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_O24_Init;
			_g_pe_hdr_cb_fn.set_debug			= NULL;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_O24_GetHistoInfo;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_O24_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_O24_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_O24_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_O24_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_O24_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_O24_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_O24_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_O24_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_O24_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_O24_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_O24_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_O24_GetOetfLut;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_O24_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_O24_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_pattern			= PE_HDR_HW_O24_SetPattern;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_M23_Init;
			_g_pe_hdr_cb_fn.set_debug			= PE_HDR_HW_M23_SetDebugSettings;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_M23_GetHistoInfo;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_M23_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_M23_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_M23_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_M23_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_M23_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_M23_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_M23_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_M23_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_M23_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_M23_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_M23_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_M23_GetOetfLut;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_M23_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_M23_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_pattern			= PE_HDR_HW_M23_SetPattern;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_O22_Init;
			_g_pe_hdr_cb_fn.set_default			= NULL;
			_g_pe_hdr_cb_fn.set_debug			= PE_HDR_HW_O22_SetDebugSettings;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_O22_GetHistoInfo;
			_g_pe_hdr_cb_fn.get_info			= NULL;
			_g_pe_hdr_cb_fn.set_3d_lut_info		= NULL;
			_g_pe_hdr_cb_fn.get_3d_lut_info		= NULL;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_O22_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_O22_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_O22_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_O22_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_O22_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_O22_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_O22_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_O22_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_O22_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_O22_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_O22_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_O22_GetOetfLut;
			_g_pe_hdr_cb_fn.set_gamma_en		= NULL;
			_g_pe_hdr_cb_fn.get_gamma_en		= NULL;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_O22_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_O22_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_lllut			= NULL;
			_g_pe_hdr_cb_fn.get_lllut			= NULL;
			_g_pe_hdr_cb_fn.set_pattern			= PE_HDR_HW_O22_SetPattern;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_E60_Init;
			_g_pe_hdr_cb_fn.set_default			= NULL;
			_g_pe_hdr_cb_fn.set_debug			= PE_HDR_HW_E60_SetDebugSettings;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_E60_GetHistoInfo;
			_g_pe_hdr_cb_fn.get_info			= NULL;
			_g_pe_hdr_cb_fn.set_3d_lut_info		= NULL;
			_g_pe_hdr_cb_fn.get_3d_lut_info		= NULL;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_E60_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_E60_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_E60_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_E60_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_E60_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_E60_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_E60_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_E60_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_E60_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_E60_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_E60_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_E60_GetOetfLut;
			_g_pe_hdr_cb_fn.set_gamma_en		= NULL;
			_g_pe_hdr_cb_fn.get_gamma_en		= NULL;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_E60_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_E60_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_lllut			= NULL;
			_g_pe_hdr_cb_fn.get_lllut			= NULL;
			_g_pe_hdr_cb_fn.set_pattern			= PE_HDR_HW_E60_SetPattern;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_O20_Init;
			_g_pe_hdr_cb_fn.set_default			= NULL;
			_g_pe_hdr_cb_fn.set_debug			= PE_HDR_HW_O20_SetDebugSettings;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_O20_GetHistoInfo;
			_g_pe_hdr_cb_fn.get_info			= PE_HDR_HW_O20_GetInfo;
			_g_pe_hdr_cb_fn.set_3d_lut_info		= PE_HDR_HW_O20_Set3dLutInfo;
			_g_pe_hdr_cb_fn.get_3d_lut_info		= PE_HDR_HW_O20_Get3dLutInfo;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_O20_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_O20_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_O20_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_O20_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_O20_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_O20_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_O20_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_O20_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_O20_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_O20_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_O20_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_O20_GetOetfLut;
			_g_pe_hdr_cb_fn.set_gamma_en		= PE_HDR_HW_O20_SetGammaEn;
			_g_pe_hdr_cb_fn.get_gamma_en		= PE_HDR_HW_O20_GetGammaEn;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_O20_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_O20_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_lllut			= PE_HDR_HW_O20_SetLowLevelLut;
			_g_pe_hdr_cb_fn.get_lllut			= PE_HDR_HW_O20_GetLowLevelLut;
			_g_pe_hdr_cb_fn.set_pattern			= PE_HDR_HW_O20_SetPattern;
			_g_pe_hdr_cb_fn.get_pixeldata		= PE_HDR_HW_O20_GetPixelData;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O18
		if (PE_KDRV_VER_O18)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_O18_Init;
			_g_pe_hdr_cb_fn.set_default			= NULL;
			_g_pe_hdr_cb_fn.set_debug			= PE_HDR_HW_O18_SetDebugSettings;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_O18_GetHistoInfo;
			_g_pe_hdr_cb_fn.get_info			= PE_HDR_HW_O18_GetInfo;
			_g_pe_hdr_cb_fn.set_3d_lut_info		= PE_HDR_HW_O18_Set3dLutInfo;
			_g_pe_hdr_cb_fn.get_3d_lut_info		= PE_HDR_HW_O18_Get3dLutInfo;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_O18_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_O18_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_O18_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_O18_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_O18_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_O18_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_O18_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_O18_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_O18_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_O18_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_O18_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_O18_GetOetfLut;
			_g_pe_hdr_cb_fn.set_gamma_en		= PE_HDR_HW_O18_SetGammaEn;
			_g_pe_hdr_cb_fn.get_gamma_en		= PE_HDR_HW_O18_GetGammaEn;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_O18_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_O18_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_lllut			= NULL;
			_g_pe_hdr_cb_fn.get_lllut			= NULL;
			_g_pe_hdr_cb_fn.set_pattern			= NULL;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M17
		if (PE_KDRV_VER_M17)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_M17_Init;
			_g_pe_hdr_cb_fn.set_default			= NULL;
			_g_pe_hdr_cb_fn.set_debug			= PE_HDR_HW_M17_SetDebugSettings;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_M17_GetHistoInfo;
			_g_pe_hdr_cb_fn.get_info			= PE_HDR_HW_M17_GetInfo;
			_g_pe_hdr_cb_fn.set_3d_lut_info		= PE_HDR_HW_M17_Set3dLutInfo;
			_g_pe_hdr_cb_fn.get_3d_lut_info		= PE_HDR_HW_M17_Get3dLutInfo;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_M17_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_M17_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_M17_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_M17_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_M17_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_M17_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_M17_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_M17_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_M17_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_M17_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_M17_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_M17_GetOetfLut;
			_g_pe_hdr_cb_fn.set_gamma_en		= PE_HDR_HW_M17_SetGammaEn;
			_g_pe_hdr_cb_fn.get_gamma_en		= PE_HDR_HW_M17_GetGammaEn;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_M17_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_M17_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_lllut			= NULL;
			_g_pe_hdr_cb_fn.get_lllut			= NULL;
			_g_pe_hdr_cb_fn.set_pattern			= NULL;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M19
		if (PE_KDRV_VER_M19)
		{
			_g_pe_hdr_cb_fn.hw_init				= PE_HDR_HW_M19_Init;
			_g_pe_hdr_cb_fn.set_default			= NULL;
			_g_pe_hdr_cb_fn.set_debug			= PE_HDR_HW_M19_SetDebugSettings;
			_g_pe_hdr_cb_fn.get_histo_info		= PE_HDR_HW_M19_GetHistoInfo;
			_g_pe_hdr_cb_fn.get_info			= PE_HDR_HW_M19_GetInfo;
			_g_pe_hdr_cb_fn.set_3d_lut_info		= PE_HDR_HW_M19_Set3dLutInfo;
			_g_pe_hdr_cb_fn.get_3d_lut_info		= PE_HDR_HW_M19_Get3dLutInfo;
			_g_pe_hdr_cb_fn.set_mode_info		= PE_HDR_HW_M19_SetModeInfo;
			_g_pe_hdr_cb_fn.get_mode_info		= PE_HDR_HW_M19_GetModeInfo;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= PE_HDR_HW_M19_SetTonemapLut;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= PE_HDR_HW_M19_GetTonemapLut;
			_g_pe_hdr_cb_fn.set_ygain_lut		= PE_HDR_HW_M19_SetYgainLut;
			_g_pe_hdr_cb_fn.get_ygain_lut		= PE_HDR_HW_M19_GetYgainLut;
			_g_pe_hdr_cb_fn.set_csc				= PE_HDR_HW_M19_SetCsc;
			_g_pe_hdr_cb_fn.get_csc				= PE_HDR_HW_M19_GetCsc;
			_g_pe_hdr_cb_fn.set_eotf_lut		= PE_HDR_HW_M19_SetEotfLut;
			_g_pe_hdr_cb_fn.get_eotf_lut		= PE_HDR_HW_M19_GetEotfLut;
			_g_pe_hdr_cb_fn.set_oetf_lut		= PE_HDR_HW_M19_SetOetfLut;
			_g_pe_hdr_cb_fn.get_oetf_lut		= PE_HDR_HW_M19_GetOetfLut;
			_g_pe_hdr_cb_fn.set_gamma_en		= PE_HDR_HW_M19_SetGammaEn;
			_g_pe_hdr_cb_fn.get_gamma_en		= PE_HDR_HW_M19_GetGammaEn;
			_g_pe_hdr_cb_fn.set_ccr				= PE_HDR_HW_M19_SetColorCorrect;
			_g_pe_hdr_cb_fn.get_ccr				= PE_HDR_HW_M19_GetColorCorrect;
			_g_pe_hdr_cb_fn.set_lllut			= NULL;
			_g_pe_hdr_cb_fn.get_lllut			= NULL;
			_g_pe_hdr_cb_fn.set_pattern			= NULL;
		}
		else
		#endif
		{
			_g_pe_hdr_cb_fn.hw_init				= NULL;
			_g_pe_hdr_cb_fn.set_default			= NULL;
			_g_pe_hdr_cb_fn.set_debug			= NULL;
			_g_pe_hdr_cb_fn.get_histo_info		= NULL;
			_g_pe_hdr_cb_fn.get_info			= NULL;
			_g_pe_hdr_cb_fn.set_3d_lut_info		= NULL;
			_g_pe_hdr_cb_fn.get_3d_lut_info		= NULL;
			_g_pe_hdr_cb_fn.set_mode_info		= NULL;
			_g_pe_hdr_cb_fn.get_mode_info		= NULL;
			_g_pe_hdr_cb_fn.set_tonemap_lut		= NULL;
			_g_pe_hdr_cb_fn.get_tonemap_lut		= NULL;
			_g_pe_hdr_cb_fn.set_ygain_lut		= NULL;
			_g_pe_hdr_cb_fn.get_ygain_lut		= NULL;
			_g_pe_hdr_cb_fn.set_csc				= NULL;
			_g_pe_hdr_cb_fn.get_csc				= NULL;
			_g_pe_hdr_cb_fn.set_eotf_lut		= NULL;
			_g_pe_hdr_cb_fn.get_eotf_lut		= NULL;
			_g_pe_hdr_cb_fn.set_oetf_lut		= NULL;
			_g_pe_hdr_cb_fn.get_oetf_lut		= NULL;
			_g_pe_hdr_cb_fn.set_gamma_en		= NULL;
			_g_pe_hdr_cb_fn.get_gamma_en		= NULL;
			_g_pe_hdr_cb_fn.set_ccr				= NULL;
			_g_pe_hdr_cb_fn.get_ccr				= NULL;
			_g_pe_hdr_cb_fn.set_lllut			= NULL;
			_g_pe_hdr_cb_fn.get_lllut			= NULL;
			_g_pe_hdr_cb_fn.set_pattern			= NULL;
			PE_PRINT_ERROR("[%x,%x] not support.\n", \
				PE_CHIP_VER, g_pe_kdrv_ver_mask);
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
int PE_HDR_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.hw_init)
		{
			ret = _g_pe_hdr_cb_fn.hw_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_init() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of hdr setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_HDR_SET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_HDR_DBG_PRINT("S TABL %s\n", #_struct);\
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
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_HDR_DBG_PRINT("E TABL %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

#define PE_HDR_SET_TLWO(_struct, _func)	\
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
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

#define PE_HDR_SET_FUNC(_struct, _func, _void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_HDR_DBG_PRINT("S FUNC %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_HDR_DBG_PRINT("E FUNC %s\n", #_struct);\
		}while (0);\
	}\
	break

/** set func without start,
*   end print(WOPT:WithOut PRint) because of too many prints */
#define PE_HDR_SET_WOPR(_struct, _func)	\
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
		PE_HDR_SET_TABL(LX_PE_HDR_EOTF_LUT_T,		PE_HDR_SetEotfLut);
		PE_HDR_SET_TABL(LX_PE_HDR_OETF_LUT_T,		PE_HDR_SetOetfLut);
		PE_HDR_SET_TABL(LX_PE_HDR_3D_LUT_INFO_T,	PE_HDR_Set3dLutInfo);
		PE_HDR_SET_TLWO(LX_PE_HDR_TONEMAP_LUT_T,	PE_HDR_SetHdrTonemapLut);
		PE_HDR_SET_TLWO(LX_PE_HDR_YGAIN_LUT_T,		PE_HDR_SetHdrYgainLut);
		PE_HDR_SET_FUNC(LX_PE_HDR_MODE_INFO_T,		PE_HDR_SetModeInfo,			_STRUCT_INPUT_);
		PE_HDR_SET_FUNC(LX_PE_HDR_CCR_T, 			PE_HDR_SetColorCorrect,		_STRUCT_INPUT_);
		PE_HDR_SET_FUNC(LX_PE_HDR_GAMMA_EN_T, 		PE_HDR_SetGammaEn,			_STRUCT_INPUT_);
		PE_HDR_SET_FUNC(LX_PE_HDR_CSC_T, 			PE_HDR_SetCsc,				_STRUCT_INPUT_);
		PE_HDR_SET_FUNC(LX_PE_HDR_LLLUT_T, 			PE_HDR_SetLowLevelLut,		_STRUCT_INPUT_);
		PE_HDR_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_HDR_SetDefaultSettings,	_STRUCT_INPUT_);
		PE_HDR_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_HDR_SetDebugSettings,	_STRUCT_INPUT_);

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
 * standard function of hdr getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_HDR_GET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_HDR_DBG_PRINT("S %s\n", #_struct);\
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
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_to_user error.\n", __F__, __L__);\
			PE_HDR_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

/* get table all(including ret size) */
#define PE_HDR_GET_TBLA(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_HDR_DBG_PRINT("S %s\n", #_struct);\
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
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_to_user error.\n", __F__, __L__);\
			p_rcv->oper = param.oper;\
			p_rcv->size = param.size;\
			PE_HDR_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

#define PE_HDR_GET_FUNC(_struct, _func, _void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_HDR_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
			PE_HDR_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

/** get func without start,
*   end print(WOPT:WithOut PRint) because of too many prints */
#define PE_HDR_GET_WOPR(_struct, _func)	\
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
		PE_HDR_GET_WOPR(LX_PE_HDR_HISTO_INFO_T,		PE_HDR_GetHistoInfo);
		PE_HDR_GET_TBLA(LX_PE_HDR_INFO_T,			PE_HDR_GetInfo);
		PE_HDR_GET_TBLA(LX_PE_HDR_3D_LUT_INFO_T,	PE_HDR_Get3dLutInfo);
		PE_HDR_GET_TABL(LX_PE_HDR_TONEMAP_LUT_T,	PE_HDR_GetHdrTonemapLut);
		PE_HDR_GET_TABL(LX_PE_HDR_YGAIN_LUT_T,		PE_HDR_GetHdrYgainLut);
		PE_HDR_GET_TABL(LX_PE_HDR_EOTF_LUT_T,		PE_HDR_GetEotfLut);
		PE_HDR_GET_TABL(LX_PE_HDR_OETF_LUT_T,		PE_HDR_GetOetfLut);
		PE_HDR_GET_FUNC(LX_PE_HDR_MODE_INFO_T,		PE_HDR_GetModeInfo,			_STRUCT_INPUT_);
		PE_HDR_GET_FUNC(LX_PE_HDR_CCR_T,			PE_HDR_GetColorCorrect,		_STRUCT_INPUT_);
		PE_HDR_GET_FUNC(LX_PE_HDR_GAMMA_EN_T,		PE_HDR_GetGammaEn,			_STRUCT_INPUT_);
		PE_HDR_GET_FUNC(LX_PE_HDR_CSC_T,			PE_HDR_GetCsc,				_STRUCT_INPUT_);
		PE_HDR_GET_FUNC(LX_PE_HDR_LLLUT_T,			PE_HDR_GetLowLevelLut,		_STRUCT_INPUT_);
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
int PE_HDR_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HDR_DBG_PRINT("[win id:%d]\n", pstParams->win_id);
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
int PE_HDR_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if (pstParams->type&LX_PE_DBG_LV)
		{
			_g_hdr_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(HDR)))? 0x1:0x0;
		}
		if(_g_pe_hdr_cb_fn.set_debug)
		{
			ret = _g_pe_hdr_cb_fn.set_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_debug() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get histo info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_HISTO_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetHistoInfo(LX_PE_HDR_HISTO_INFO_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_histo_info)
		{
			ret = _g_pe_hdr_cb_fn.get_histo_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_histo_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set hdr tonemap lut
 *
 * @param   *pstParams [in] LX_PE_HDR_TONEMAP_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetHdrTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_tonemap_lut)
		{
			ret = _g_pe_hdr_cb_fn.set_tonemap_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_tonemap_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * get hdr tonemap lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_TONEMAP_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetHdrTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_tonemap_lut)
		{
			ret = _g_pe_hdr_cb_fn.get_tonemap_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_tonemap_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * set hdr ygain lut
 *
 * @param   *pstParams [in] LX_PE_HDR_YGAIN_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetHdrYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_ygain_lut)
		{
			ret = _g_pe_hdr_cb_fn.set_ygain_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_ygain_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * get hdr ygain lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_YGAIN_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetHdrYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_ygain_lut)
		{
			ret = _g_pe_hdr_cb_fn.get_ygain_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_ygain_lut() error.\n");
		}
	}while (0);	
	return ret;
}
/**
 * set csc
 *
 * @param   *pstParams [in] LX_PE_HDR_CSC_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetCsc(LX_PE_HDR_CSC_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_csc)
		{
			ret = _g_pe_hdr_cb_fn.set_csc(pstParams);
			PE_CHECK_CODE(ret, break, "set_csc() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get csc
 *
 * @param   *pstParams [in] LX_PE_HDR_CSC_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetCsc(LX_PE_HDR_CSC_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_csc)
		{
			ret = _g_pe_hdr_cb_fn.get_csc(pstParams);
			PE_CHECK_CODE(ret, break, "get_csc() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetInfo(LX_PE_HDR_INFO_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_info)
		{
			ret = _g_pe_hdr_cb_fn.get_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set eotf lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_EOTF_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_eotf_lut)
		{
			ret = _g_pe_hdr_cb_fn.set_eotf_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_eotf_lut() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get eotf lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_EOTF_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_eotf_lut)
		{
			ret = _g_pe_hdr_cb_fn.get_eotf_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_eotf_lut() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set oetf lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_OETF_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_oetf_lut)
		{
			ret = _g_pe_hdr_cb_fn.set_oetf_lut(pstParams);
			PE_CHECK_CODE(ret, break, "set_oetf_lut() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get oetf lut
 *
 * @param   *pstParams [in/out] LX_PE_HDR_OETF_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_oetf_lut)
		{
			ret = _g_pe_hdr_cb_fn.get_oetf_lut(pstParams);
			PE_CHECK_CODE(ret, break, "get_oetf_lut() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set 3d lut info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_3D_LUT_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_Set3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_3d_lut_info)
		{
			ret = _g_pe_hdr_cb_fn.set_3d_lut_info(pstParams);
			PE_CHECK_CODE(ret, break, "set_3d_lut_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get 3d lut info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_3D_LUT_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_Get3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_3d_lut_info)
		{
			ret = _g_pe_hdr_cb_fn.get_3d_lut_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_3d_lut_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set mode info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_MODE_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_mode_info)
		{
			ret = _g_pe_hdr_cb_fn.set_mode_info(pstParams);
			PE_CHECK_CODE(ret, break, "set_mode_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get mode info
 *
 * @param   *pstParams [in/out] LX_PE_HDR_MODE_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_mode_info)
		{
			ret = _g_pe_hdr_cb_fn.get_mode_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_mode_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set gamma en
 *
 * @param   *pstParams [in] LX_PE_HDR_GAMMA_EN_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_gamma_en)
		{
			ret = _g_pe_hdr_cb_fn.set_gamma_en(pstParams);
			PE_CHECK_CODE(ret, break, "set_gamma_en() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get gamma en
 *
 * @param   *pstParams [in] LX_PE_HDR_GAMMA_EN_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_gamma_en)
		{
			ret = _g_pe_hdr_cb_fn.get_gamma_en(pstParams);
			PE_CHECK_CODE(ret, break, "get_gamma_en() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set ccr
 *
 * @param   *pstParams [in] LX_PE_HDR_CCR_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetColorCorrect(LX_PE_HDR_CCR_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_ccr)
		{
			ret = _g_pe_hdr_cb_fn.set_ccr(pstParams);
			PE_CHECK_CODE(ret, break, "set_ccr() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get ccr
 *
 * @param   *pstParams [in] LX_PE_HDR_CCR_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetColorCorrect(LX_PE_HDR_CCR_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_ccr)
		{
			ret = _g_pe_hdr_cb_fn.get_ccr(pstParams);
			PE_CHECK_CODE(ret, break, "get_ccr() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set lllut
 *
 * @param   *pstParams [in] LX_PE_HDR_LLLUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetLowLevelLut(LX_PE_HDR_LLLUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_lllut)
		{
			ret = _g_pe_hdr_cb_fn.set_lllut(pstParams);
			PE_CHECK_CODE(ret, break, "set_lllut() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get lllut
 *
 * @param   *pstParams [in] LX_PE_HDR_LLLUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetLowLevelLut(LX_PE_HDR_LLLUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_lllut)
		{
			ret = _g_pe_hdr_cb_fn.get_lllut(pstParams);
			PE_CHECK_CODE(ret, break, "get_lllut() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set pattern
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_SetPattern(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.set_pattern)
		{
			ret = _g_pe_hdr_cb_fn.set_pattern(pstParams);
			PE_CHECK_CODE(ret, break, "set_pattern() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get pixel data
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HDR_GetPixelData(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hdr_cb_fn.get_pixeldata)
		{
			ret = _g_pe_hdr_cb_fn.get_pixeldata(pstParams);
			PE_CHECK_CODE(ret, break, "get_pixeldata() error.\n");
		}
	}while (0);
	return ret;
}

int pe_hdr_proc_show_histo(int id, void *p, void *data)
{
	int ret = RET_OK;
	if(_g_pe_hdr_cb_fn.proc_show_histo) {
		ret = _g_pe_hdr_cb_fn.proc_show_histo(id,p,data);
	}
	return ret;
}
