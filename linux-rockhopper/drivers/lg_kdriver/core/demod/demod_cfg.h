/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file
 *
 *  main configuration file for demod device
 *	demod device will teach you how to make device driver with new platform.
 *
 *  author		jeongpil.yun (jeongpil.yun@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#ifndef	_DEMOD_CFG_H_
#define	_DEMOD_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	DEMOD_MODULE			"demod"
#define DEMOD_MAX_DEVICE		1

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	char*	memory_name;
	UINT32	memory_base;
	UINT32	memory_size;
}
DEMOD_MEM_CFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern DEMOD_MEM_CFG_T gMemCfgDEMOD;
extern DEMOD_MEM_CFG_T gMemCfgDEMOD_ISDBT;
extern DEMOD_MEM_CFG_T gMemCfgDEMOD_DVB_TDI;
extern DEMOD_MEM_CFG_T gMemCfgDEMOD_DVB_DJB;
extern DEMOD_MEM_CFG_T gMemCfgDEMOD_DVB_RISIC;
extern DEMOD_MEM_CFG_T gMemCfgDEMOD_FW;
extern DEMOD_MEM_CFG_T gMemCfgDEMOD_DTMB;
extern DEMOD_MEM_CFG_T gMemCfgDEMOD_ATSC3;

void DEMOD_RegisterMemMap(char* mode);
void DEMOD_UnregisterMemMap( void );

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DEMOD_CFG_H_ */

/** @} */

