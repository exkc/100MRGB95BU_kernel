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

/** @file pe_cmn.h
 *
 *  driver header for picture enhance common functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_CMN_H_
#define	_PE_CMN_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "de_kapi.h"

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
 *	pe common settings type
 */
typedef struct
{
	LX_PE_DEFAULT_SETTINGS_T dflt[LX_PE_WIN_NUM];	///< default info
}
PE_CMN_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_CMN_RegisterCbFunc(void);
int PE_CMN_Init(PE_CFG_CTRL_T *pstParams);
int PE_CMN_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_CMN_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_CMN_CheckChipRev(void);
int PE_CMN_OpenPicEnhanceModule(void);
int PE_CMN_ClosePicEnhanceModule(void);
int PE_CMN_SuspendModule(void);
int PE_CMN_ResumeModule(UINT32 stParams);
int PE_CMN_GetMemInfo(unsigned int *base, unsigned int *size);
int PE_CMN_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_CMN_GetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_CMN_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CMN_GetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CMN_SetContrast(void *pstParams);
int PE_CMN_GetContrast(void *pstParams);
int PE_CMN_SetBrightness(void *pstParams);
int PE_CMN_GetBrightness(void *pstParams);
int PE_CMN_SetSaturation(LX_PE_CMN_SATURATION_T *pstParams);
int PE_CMN_GetSaturation(LX_PE_CMN_SATURATION_T *pstParams);
int PE_CMN_SetHue(LX_PE_CMN_HUE_T *pstParams);
int PE_CMN_GetHue(LX_PE_CMN_HUE_T *pstParams);
int PE_CMN_SetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams);
int PE_CMN_GetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams);
int PE_CMN_SetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);
int PE_CMN_GetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);
int PE_CMN_SetBypassBlocks(LX_PE_CMN_BYPASS_BLOCKS_T *pstParams);
int PE_LGSR_GetMemInfo(void *pstParams);
int PE_LGSR_SetSrSQM(UINT32 pstParams);
int PE_LGSR_RunTRA(UINT32 pstParams);
int PE_LGSR_HaltTRA(UINT32 pstParams);
int PE_LGSR_CropPosition(UINT32 *pstParams);
int PE_LGSR_DoneDownloadDdr(UINT32 pstParams);
int PE_LGSR_UserReady(UINT32 pstParams);
int PE_LGSR_ValidRun(UINT32 pstParams);
int PE_LGSR_Demomode(UINT32 pstParams);
int PE_LGSR_UIOnoff(UINT32 pstParams);
int PE_LGSR_AcclSrsqm(UINT32 pstParams);
int PE_LGSR_AcclTra(UINT32 pstParams);
int PE_LGSR_PrintStatus(void);
int PE_LGSR_GetLneStatus(UINT32 *pstParams);
int PE_LGSR_GetTraStatus(UINT32 *pstParams);
int PE_CMN_CheckDoubleSetting(LX_PE_WIN_ID id, \
				UINT32 *chk, void *prev, void *cur, UINT32 size);
int PE_CMN_SetVcpSaturationCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CMN_H_ */
