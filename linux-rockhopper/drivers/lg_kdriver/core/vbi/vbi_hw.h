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
 * VBI module
 *
 *  author      won.hur (won.hur@lge.com)
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg115x_vbi
 *  @{
 */

#ifndef _VBI_HW_H_
#define _VBI_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct{
	unsigned short wss_data;
	unsigned int wss_int_time;
} sWSSBufInform;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
// function pointer
extern int (*VBI_CheckVline625)(void);
extern int (*VBI_CheckAnalogCP)(void);

extern int (*VBI_TTX_HWInitialize)(void);
extern int (*VBI_TTX_SetInputFormat)(eVBIDataType type);
extern int (*VBI_TTX_SetInterrupt)(int on_off);
extern int (*VBI_TTX_ParsingVBIData)(sHeaderData *data);
extern int (*VBI_TTX_PutVBIData)(sHeaderData *data);
extern int (*VBI_TTX_SetInterruptClear)(void);
extern int (*VBI_TTX_Enable_VPS_Slicer)(BOOLEAN Enable);
extern int (*VBI_TTX_Set_TT_Slicer_Mode)(unsigned int mode);
extern int (*VBI_TTX_SetVBILPF)(int onoff);
extern int (*VBI_TTX_CheckOnLine318)(int mode);
extern int (*VBI_TTX_SetTypeLine318)(int onoff);
extern int (*VBI_TTX_DebugPrintMode)(int mode);
#ifdef	KDRV_CONFIG_PM
extern int (*VBI_TTX_RunSuspend)(void);
extern int (*VBI_TTX_RunResume)(void);
#endif

// E60Ax function prototype
int TTX_Hal_HWInitialize(void);
int TTX_Hal_SetInputFormat(eVBIDataType type);
int TTX_Hal_SetInterrupt(int on_off);
int TTX_Hal_ParsingVBIData(sHeaderData *data);
int TTX_Hal_PutVBIData(sHeaderData *data);
int TTX_Hal_SetInterruptClear(void);
int TTX_Hal_Enable_VPS_Slicer(BOOLEAN Enable);
int TTX_Hal_SetVBILPF(int onoff);
int TTX_Hal_CheckOnLine318(int mode);
int TTX_Hal_SetTypeLine318(int onoff);
int TTX_Hal_Set_TT_Slicer_Mode(unsigned int slicer_mode);
int TTX_Hal_DebugPrintMode(int mode);
int TTX_Hal_CheckVline625(void);
int TTX_Hal_CheckAnalogCP(void);

#ifdef	KDRV_CONFIG_PM
int TTX_Hal_RunSuspend(void);
int TTX_Hal_RunResume(void);
#endif

// For CC
extern int (*VBI_CC_HWInitialize)(void);
extern int (*VBI_CC_SetInputFormat)(eVBIDataType type);
extern int (*VBI_CC_SetInterrupt)(int on_off);
extern int (*VBI_CC_ParsingVBIData)(unsigned int *packet);
extern int (*VBI_CC_SetInterruptClear)(void);
extern int (*VBI_CC_DebugPrintMode)(int mode);

#ifdef	KDRV_CONFIG_PM
extern int (*VBI_CC_RunSuspend)(void);
extern int (*VBI_CC_RunResume)(void);
#endif

// E60Ax function prototype
int CC_Hal_HWInitialize(void);
int CC_Hal_SetInputFormat(eVBIDataType type);
int CC_Hal_SetInterrupt(int on_off);
int CC_Hal_ParsingVBIData(unsigned int *packet);
int CC_Hal_SetInterruptClear(void);
int CC_Hal_DebugPrintMode(int mode);
int CC_Hal_CheckVline625(void);
int CC_Hal_CheckAnalogCP(void);

#ifdef	KDRV_CONFIG_PM
int CC_Hal_RunSuspend(void);
int CC_Hal_RunResume(void);
#endif

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VBI_HW_H_ */

/** @} */

