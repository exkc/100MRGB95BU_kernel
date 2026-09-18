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

/** @file pe_hdr.h
 *
 *  driver header for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2016.06.24
 *	@see		
 */

#ifndef	_PE_HDR_H_
#define	_PE_HDR_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_HDR_RegisterCbFunc(void);
int PE_HDR_Init(PE_CFG_CTRL_T *pstParams);
int PE_HDR_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_HDR_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);

int PE_HDR_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_HDR_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_HDR_GetHistoInfo(LX_PE_HDR_HISTO_INFO_T *pstParams);
int PE_HDR_GetInfo(LX_PE_HDR_INFO_T *pstParams);
int PE_HDR_Set3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams);
int PE_HDR_Get3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams);
int PE_HDR_SetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams);
int PE_HDR_GetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams);
int PE_HDR_SetHdrTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams);
int PE_HDR_GetHdrTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams);
int PE_HDR_SetHdrYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams);
int PE_HDR_GetHdrYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams);
int PE_HDR_SetCsc(LX_PE_HDR_CSC_T *pstParams);
int PE_HDR_GetCsc(LX_PE_HDR_CSC_T *pstParams);
int PE_HDR_SetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams);
int PE_HDR_GetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams);
int PE_HDR_SetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams);
int PE_HDR_GetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams);
int PE_HDR_SetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams);
int PE_HDR_GetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams);
int PE_HDR_SetColorCorrect(LX_PE_HDR_CCR_T *pstParams);
int PE_HDR_GetColorCorrect(LX_PE_HDR_CCR_T *pstParams);
int PE_HDR_SetLowLevelLut(LX_PE_HDR_LLLUT_T *pstParams);
int PE_HDR_GetLowLevelLut(LX_PE_HDR_LLLUT_T *pstParams);
int PE_HDR_SetPattern(void *pstParams);
int PE_HDR_GetPixelData(void *pstParams);
int pe_hdr_proc_show_histo(int id, void *p, void *data);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_HDR_H_ */
