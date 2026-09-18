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
 *  be_top drv header file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2013.04.27
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _BE_TOP_DRV_H_
#define _BE_TOP_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

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
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int BE_TOP_PreInit(void);
int BE_TOP_Init(void);
int BE_TOP_Close(void);

int BE_TOP_Set_DebugPrint(unsigned long arg);
int BE_TOP_Set_Bypass(unsigned long arg);
int BE_TOP_Toggle_3D_LR(unsigned long arg);
int BE_TOP_Set_3D_Convergence(unsigned long arg);
int BE_TOP_Set_Black_Bar(unsigned long arg);
int BE_TOP_Set_Debug_Display(unsigned long arg);
int BE_TOP_Set_Real_Cinema(unsigned long arg);
int BE_TOP_Set_Orbit(unsigned long arg);
int BE_TOP_Set_LSR(unsigned long arg);
int BE_TOP_Set_Input_Lag(unsigned long arg);
int BE_TOP_Set_Input_Lag_Pattern(unsigned long arg);
int BE_TOP_Set_LSRParam(unsigned long arg);
int BE_TOP_Set_GSR(unsigned long arg);
int BE_TOP_Get_GSRStatus(unsigned long arg);
int BE_TOP_Set_CPC(unsigned long arg);
int BE_TOP_Get_OSDAlphaAPL(unsigned long arg);
int BE_TOP_Set_OSDRGBLevel(unsigned long arg);
int BE_TOP_Set_DispMode(unsigned long arg);
int BE_TOP_Get_IrrStatus(unsigned long arg);
int BE_TOP_Set_IrrData(unsigned long arg);
int BE_TOP_Get_IrrData(unsigned long arg);
int BE_TOP_Ioctl(unsigned int cmd, unsigned long arg);

int BE_TOP_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _BE_TOP_DRV_H_ */

/** @} */


