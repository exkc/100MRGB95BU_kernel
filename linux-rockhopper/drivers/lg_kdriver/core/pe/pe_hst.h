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

/** @file pe_hst.h
 *
 *  driver header for picture enhance histogram module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.02
 *	@see		
 */

#ifndef	_PE_HST_H_
#define	_PE_HST_H_

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
int PE_HST_RegisterCbFunc(void);
int PE_HST_Init(PE_CFG_CTRL_T *pstParams);
int PE_HST_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_HST_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);

int PE_HST_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_HST_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_HST_GetHistogramInfo(void *pstParams);
int PE_HST_GetHdrInfo(LX_PE_HST_HDR_INFO_T *pstParams);
int PE_HST_SetHistoConfig(LX_PE_HST_HISTO_CFG_T *pstParams);
int PE_HST_GetHistoConfig(LX_PE_HST_HISTO_CFG_T *pstParams);
int PE_HST_GetAplInfo(LX_PE_HST_APL_INFO_T *pstParams);
int PE_HST_GetBlkApl(LX_PE_HST_BLK_APL_T *pstParams);
int pe_hst_proc_show_histo(int id, void *p, void *data);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_HST_H_ */
