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

/** @file pe_nrd.h
 *
 *  driver header for picture enhance noise reduction. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_NRD_H_
#define	_PE_NRD_H_

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
int PE_NRD_RegisterCbFunc(void);
int PE_NRD_Init(PE_CFG_CTRL_T *pstParams);
int PE_NRD_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_NRD_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);

int PE_NRD_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_NRD_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_NRD_SetDnrCmnCtrl(void *pstParams);
int PE_NRD_GetDnrCmnCtrl(void *pstParams);
int PE_NRD_SetDnr2ndCmnCtrl(void *pstParams);
int PE_NRD_GetDnr2ndCmnCtrl(void *pstParams);
int PE_NRD_SetDnrDetailCtrl(void *pstParams);
int PE_NRD_GetDnrDetailCtrl(void *pstParams);
int PE_NRD_SetDnr2ndDetailCtrl(void *pstParams);
int PE_NRD_SetDnrDcntCmnCtrl(void *pstParams);
int PE_NRD_GetDnrDcntCmnCtrl(void *pstParams);
int PE_NRD_SetDnrDcnt2ndCmnCtrl(void *pstParams);
int PE_NRD_GetDnrDcnt2ndCmnCtrl(void *pstParams);
int PE_NRD_SetDnrDcntDetailCtrl(void *pstParams);
int PE_NRD_GetDnrDcntDetailCtrl(void *pstParams);
int PE_NRD_SetDnrDcnt2ndDetailCtrl(void *pstParams);
int PE_NRD_SetTnrCmnCtrl(void *pstParams);
int PE_NRD_GetTnrCmnCtrl(void *pstParams);
int PE_NRD_SetTnrDetailCtrl(void *pstParams);
int PE_NRD_GetTnrDetailCtrl(void *pstParams);
int PE_NRD_SetTnr2ndCmnCtrl(void *pstParams);
int PE_NRD_GetTnr2ndCmnCtrl(void *pstParams);
int PE_NRD_SetTnr2ndDetailCtrl(void *pstParams);
int PE_NRD_GetTnr2ndDetailCtrl(void *pstParams);
int PE_NRD_SetTnr3rdCmnCtrl(void *pstParams);
int PE_NRD_GetTnr3rdCmnCtrl(void *pstParams);
int PE_NRD_SetTnr3rdDetailCtrl(void *pstParams);
int PE_NRD_SetLedDcntCmnCtrl(void *pstParams);
int PE_NRD_GetLedDcntCmnCtrl(void *pstParams);
int PE_NRD_SetLedDcntDetailCtrl(void *pstParams);
int PE_NRD_GetLedDcntDetailCtrl(void *pstParams);
int PE_NRD_SetDnrSqmCmnCtrl(void *pstParams);
int PE_NRD_SetDnr2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_SetTnrSqmCmnCtrl(void *pstParams);
int PE_NRD_SetTnr2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_SetTnr3rdSqmCmnCtrl(void *pstParams);
int PE_NRD_SetDnrDcntSqmCmnCtrl(void *pstParams);
int PE_NRD_SetDnrDcnt2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_SetLedDcntSqmCmnCtrl(void *pstParams);
int PE_NRD_GetDnrSqmCmnCtrl(void *pstParams);
int PE_NRD_GetDnr2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_GetTnrSqmCmnCtrl(void *pstParams);
int PE_NRD_GetTnr2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_GetTnr3rdSqmCmnCtrl(void *pstParams);
int PE_NRD_GetDnrDcntSqmCmnCtrl(void *pstParams);
int PE_NRD_GetDnrDcnt2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_GetLedDcntSqmCmnCtrl(void *pstParams);
int PE_NRD_SetTnrCmnAllCtrl(void *pstParams);
int PE_NRD_SetDnrCmnAllCtrl(void *pstParams);
int PE_NRD_SetDnrDcntCmnAllCtrl(void *pstParams);
int PE_NRD_GetTnrCmnAllCtrl(void);
int PE_NRD_GetDnrCmnAllCtrl(void);
int PE_NRD_GetDnrDcntCmnAllCtrl(void);
int PE_NRD_SetTnrFaceCtrl(void *pstParams);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_NRD_H_ */
