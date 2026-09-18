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
 *  h3d drv header file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef BE_H3D_HW_M19_INC
#define BE_H3D_HW_M19_INC

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "be_kapi.h"
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
int BE_H3D_HW_M19_Set_Mode(LX_BE_H3D_MODE_T *pstParams);
int BE_H3D_HW_M19_Get_Mode(LX_BE_H3D_MODE_T *pstParams);
int BE_H3D_HW_M19_T3C_Depth_Level(LX_BE_H3D_T3C_DEPTH_LEVEL_T *pstParams);
int BE_H3D_HW_M19_Set_TridFmt( LX_BE_TRIDTV_FMT_CTRL_T *pstParams);
int BE_H3D_HW_M19_ProcHandler(BE_H3D_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* BE_H3D_HW_M19_INC */

/** @} */



