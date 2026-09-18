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

/** @file pe_shp.h
 *
 *  driver header for picture enhance sharpness. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_SHP_H_
#define	_PE_SHP_H_

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
int PE_SHP_RegisterCbFunc(void);
int PE_SHP_Init(PE_CFG_CTRL_T *pstParams);
int PE_SHP_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_SHP_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);

int PE_SHP_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_SHP_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_SHP_SetReCmnCtrl(void *pstParams);
int PE_SHP_GetReCmnCtrl(void *pstParams);
int PE_SHP_SetReHorCtrl(void *pstParams);
int PE_SHP_GetReHorCtrl(void *pstParams);
int PE_SHP_SetReVerCtrl(void *pstParams);
int PE_SHP_GetReVerCtrl(void *pstParams);
int PE_SHP_SetReMiscCtrl(void *pstParams);
int PE_SHP_GetReMiscCtrl(void *pstParams);
int PE_SHP_SetEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_GetEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_SetDetailEnhanceCtrl(void *pstParams);
int PE_SHP_GetDetailEnhanceCtrl(void *pstParams);
int PE_SHP_SetSreCmnCtrl(void *pstParams);
int PE_SHP_GetSreCmnCtrl(void *pstParams);
int PE_SHP_SetSreSclFlt(void *pstParams);
int PE_SHP_GetSreSclFlt(void *pstParams);
int PE_SHP_SetSreReCmnCtrl(void *pstParams);
int PE_SHP_GetSreReCmnCtrl(void *pstParams);
int PE_SHP_SetSreReHorCtrl(void *pstParams);
int PE_SHP_GetSreReHorCtrl(void *pstParams);
int PE_SHP_SetSreReVerCtrl(void *pstParams);
int PE_SHP_GetSreReVerCtrl(void *pstParams);
int PE_SHP_SetSreReMiscCtrl(void *pstParams);
int PE_SHP_GetSreReMiscCtrl(void *pstParams);
int PE_SHP_SetSreEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_GetSreEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_SetSreDetailEnhanceCtrl(void *pstParams);
int PE_SHP_GetSreDetailEnhanceCtrl(void *pstParams);
int PE_SHP_SetSre2KReCmnCtrl(void *pstParams);
int PE_SHP_GetSre2KReCmnCtrl(void *pstParams);
int PE_SHP_SetSre2KReHorCtrl(void *pstParams);
int PE_SHP_GetSre2KReHorCtrl(void *pstParams);
int PE_SHP_SetSre2KReVerCtrl(void *pstParams);
int PE_SHP_GetSre2KReVerCtrl(void *pstParams);
int PE_SHP_SetSre2KReMiscCtrl(void *pstParams);
int PE_SHP_GetSre2KReMiscCtrl(void *pstParams);
int PE_SHP_SetSre2KEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_GetSre2KEdgeEnhanceCtrl(void *pstParams);
int PE_SHP_SetSre2KDetailEnhanceCtrl(void *pstParams);
int PE_SHP_GetSre2KDetailEnhanceCtrl(void *pstParams);
int PE_SHP_SetPspCtrl(LX_PE_SHP_PSP_T *pstParams);
int PE_SHP_GetPspCtrl(LX_PE_SHP_PSP_T *pstParams);
int PE_SHP_SetObcCtrl(void *pstParams);
int PE_SHP_GetObcCtrl(void *pstParams);
int PE_SHP_SetObcLUT(void *pstParams);
int PE_SHP_GetObcLUT(void *pstParams);
int PE_SHP_GetObcData(void *pstParams);
int PE_SHP_SetSqmCmnCtrl(void *pstParams);
int PE_SHP_SetSqmCmnCtrl2(void *pstParams);
int PE_SHP_GetSqmCmnCtrl(void *pstParams);
int PE_SHP_SetSqmDetailCtrl(void *pstParams);
int PE_SHP_GetSqmDetailCtrl(void *pstParams);
int PE_SHP_SetSre2KSqmCmnCtrl(void *pstParams);
int PE_SHP_SetSre2KSqmCmnCtrl2(void *pstParams);
int PE_SHP_GetSre2KSqmCmnCtrl(void *pstParams);
int PE_SHP_SetSre2KSqmDetailCtrl(void *pstParams);
int PE_SHP_GetSre2KSqmDetailCtrl(void *pstParams);
int PE_SHP_SetReEasyCmnCtrl(void *pstParams);
int PE_SHP_SetSre2KReEasyCmnCtrl(void *pstParams);
int PE_SHP_SetObcStereoCtrl(void *pstParams);
int PE_SHP_SetReAllCtrl(void *pstParams);
int PE_SHP_GetReAllCtrl(void);
int PE_SHP_SetSreSqmCmnCtrl(void *pstParams);
int PE_SHP_GetSreSqmCmnCtrl(void *pstParams);
int PE_SHP_SetSreSqmDetailCtrl(void *pstParams);
int PE_SHP_GetSreSqmDetailCtrl(void *pstParams);
int PE_SHP_SetEllipsCtrl(void *pstParams);
int PE_SHP_SetSreSubReCmnCtrl(void *pstParams);
int PE_SHP_SetSreSubReMiscCtrl(void *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_SHP_H_ */
