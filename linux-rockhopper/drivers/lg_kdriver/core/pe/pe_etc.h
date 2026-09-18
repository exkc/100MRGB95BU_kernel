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

/** @file pe_etc.h
 *
 *  driver header for picture enhance etc functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.07.16
 *	@see		
 */

#ifndef	_PE_ETC_H_
#define	_PE_ETC_H_

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
/**
 *	pe etc misc table function type
 */
typedef struct 
{
	int		(*func)(LX_PE_ETC_TBL_T *);
	char	*fn_name;
}PE_ETC_MISC_TBL_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_ETC_RegisterCbFunc(void);
int PE_ETC_SetTracePacketData(LX_PE_PKT_T *pstParams);
int PE_ETC_Init(PE_CFG_CTRL_T *pstParams);
int PE_ETC_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_ETC_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_ETC_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_ETC_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_ETC_SetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams);
int PE_ETC_GetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams);
int PE_ETC_SetMiscTbl(LX_PE_ETC_TBL_T *pstParams);
int PE_ETC_GetMiscTbl(LX_PE_ETC_TBL_T *pstParams);
int PE_ETC_GetLevelInfo(LX_PE_INF_LEVEL_T *pstParams);
int pe_inf_proc_show_db(int id, void *p, void *data);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_ETC_H_ */
