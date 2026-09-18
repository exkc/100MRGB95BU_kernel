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

/** @file pe_dnt.h
 *
 *  driver header for picture enhance deinterlacer. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_DNT_H_
#define	_PE_DNT_H_

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
int PE_DNT_RegisterCbFunc(void);
int PE_DNT_Init(PE_CFG_CTRL_T *pstParams);
int PE_DNT_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_DNT_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);

int PE_DNT_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_DNT_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_DNT_SetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams);
int PE_DNT_GetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams);
int PE_DNT_SetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams);
int PE_DNT_GetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNT_H_ */
