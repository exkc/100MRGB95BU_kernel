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

/** @file pe_dcm.h
 *
 *  driver header for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_DCM_H_
#define	_PE_DCM_H_

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
int PE_DCM_RegisterCbFunc(void);
int PE_DCM_Init(PE_CFG_CTRL_T *pstParams);
int PE_DCM_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_DCM_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);

int PE_DCM_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_DCM_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_DCM_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
int PE_DCM_GetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
int PE_DCM_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
int PE_DCM_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
int PE_DCM_SetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams);
int PE_DCM_GetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams);
int PE_DCM_SetHdrLut(LX_PE_DCM_HDR_LUT_T *pstParams);
int PE_DCM_GetHdrLut(LX_PE_DCM_HDR_LUT_T *pstParams);
int PE_DCM_SetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams);
int PE_DCM_GetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams);
int PE_DCM_SetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams);
int PE_DCM_GetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams);
int PE_DCM_SetHdrMode(LX_PE_DCM_HDR_MODE_T *pstParams);
int PE_DCM_GetHdrMode(LX_PE_DCM_HDR_MODE_T *pstParams);
int PE_DCM_SetDseCtrl(void *pstParams);
int PE_DCM_GetDseCtrl(void *pstParams);
int PE_DCM_SetDrcCurv_Old(void *pstParams);
int PE_DCM_SetDrcCurv(void *pstParams);
int PE_DCM_GetDrcCurv(void *pstParams);
int PE_DCM_SetDrcCtrl(void *pstParams);
int PE_DCM_GetDrcCtrl(void *pstParams);
int PE_DCM_SetObcCtrl(void *pstParams);
int PE_DCM_GetObcCtrl(void *pstParams);
int PE_DCM_GetObcData(void *pstParams);
int PE_DCM_SetDtmLut(void *pstParams);
int PE_DCM_GetDtmLut(void *pstParams);
int PE_DCM_SetAccelDceLut(void);
int PE_DCM_SetDseCtrl2(void *pstParams);
int PE_DCM_GetDseCtrl2(void *pstParams);
int PE_DCM_SetDceLut2(void *pstParams);
int PE_DCM_GetDceLut2(void *pstParams);
int PE_DCM_SetDceDB(void *pstParams);
int PE_DCM_GetDceDB(int idexDb, int lengthOfData);
int PE_DCM_SetDceLut3(void *pstParams);
int PE_DCM_GetDceDBAddr(void);
int PE_DCM_SetDbcDB(void *pstParams);
int PE_DCM_GetDbcDB(void);
int PE_DCM_SetDrcCtrl2(void *pstParams);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DCM_H_ */
