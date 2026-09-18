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
 *	BE FRC module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

#ifndef  BE_FRC_HW_O18_INC
#define  BE_FRC_HW_O18_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "be_kapi.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32	u32Blur;							// 0~9 : Blur level
	UINT32	u32Judder;						// 0~9 : Judder level
	UINT32	u32MemcType;					// 0 : OFF, 1: LOW, 2:MID, 3:HIGH, 4:USER, 5: PULLDOWN55 : @ref FRC_MC_TYPE_T
	UINT32	u32LowDelay;					// 0: NORMAL_DELAY, 1:LOW_DELAY
	UINT32	u32MotionPro;					// 0: NORMAL_MODE, 1:MOTION_PRO_MODE
} BE_FRC_HW_O18_INFO_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int BE_FRC_HW_O18_Initialize(void);
int BE_FRC_HW_O18_Close(void);
int BE_FRC_HW_O18_ControlMemc(LX_BE_FRC_MEMC_MODE_T *pstParams);
int BE_FRC_HW_O18_SetMemcMode(BE_FRC_HW_O18_INFO_T *pstParams);
int BE_FRC_HW_O18_SetMemcLowDelay(LX_BE_FRC_LOW_DELAY_T *pstParams);
int BE_FRC_HW_O18_SetMemcMotionPro(LX_BE_FRC_MOTION_PRO_T *pstParams);
int BE_FRC_HW_O18_Set_Demo_Mode(LX_BE_FRC_DEMO_MODE_T *pstParams);
int BE_FRC_HW_O18_Set_Debug_Box(LX_BE_FRC_ENABLE_DEBUG_BOX_T *pstParams);
int BE_FRC_HW_O18_Set_Bypass_Memc_Reg(LX_BE_FRC_MEMC_BYPASS_REGION_T *pstParams);
int BE_FRC_HW_O18_Set_YUV_444_Mode(LX_BE_FRC_COLOR_YUV444_T *pstParams);
int BE_FRC_HW_O18_Set_Low_Delay(LX_BE_FRC_LOW_DELAY_T *pstParams);
int BE_FRC_HW_O18_Get_Firmware_Ver(LX_BE_FRC_VERSION_T *pstParams);
int BE_FRC_HW_O18_Force_Frame_Rate(LX_BE_FRC_FRAME_RATE_T *pstParams);
int BE_FRC_HW_O18_Set_Freeze(LX_BE_FRC_FREEZE_T *pstParams);
int BE_FRC_HW_O18_Update_FrameDelay(LX_BE_LOW_DELAY_T *pstParams);
int BE_FRC_HW_O18_SetConfig(LX_BE_FRC_CFG_T *pstParams);
int BE_FRC_HW_O18_RunCommand(LX_BE_FRC_CMD_T *pstParams);
int BE_FRC_HW_O18_ProcHandler(BE_FRC_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_FRC_HW_O18_INC  ----- */
/**  @} */

