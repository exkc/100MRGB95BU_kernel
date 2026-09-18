/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

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
 * chip specific definition for BE device.
 *
 * author     dj911.kim
 * version    1.0
 * date       2017.06.07
 * note       Additional information.
 *
 * @addtogroup BE
 * @{
 */

#ifndef  _IPC_DEF_M23_H_
#define  _IPC_DEF_M23_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#define BE_IPC_FROM_CPU_M23A0_BASE
#define BE_IPC_FROM_MCU_M23A0_BASE

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define IPC_SET_DEFAULT_PARAM(structure, name)  \
	structure name;\
	do{\
		memset(&(name), 0xFF, sizeof(structure));\
	}while(0)

#define IPC_SET_GET_PARAM(structure, name)	IPC_SET_DEFAULT_PARAM(structure, name)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef enum {
	BE_TOP_INIT					= 0x60000000,
	BE_TOP_SET_3D_OUT_FORMAT,
	BE_TOP_SET_BLOCK_BYPASS,
	BE_TOP_SET_DEBUG_DISPLAY,
	BE_TOP_GET_SYSTEM_INFO,
	BE_TOP_TOGGLE_3D_LR,
	BE_TOP_SET_3D_CONVERGENCE,
	BE_TOP_SET_BLACK_BAR,
	BE_TOP_SET_REAL_CINEMA,
	BE_TOP_SET_LSR,
	BE_TOP_SET_ORBIT,
	BE_TOP_SET_CPC,
	BE_TOP_SET_GSR,
	BE_TOP_SET_DISP_MODE,
	BE_TOP_SET_GSR2,
	BE_TOP_SET_IRR,

	BE_H3D_SET_MODE				= 0x70000000,
	BE_H3D_T3C_DEPTH_LEVEL,

	BE_FRC_SET_MEMC_MODE			= 0x80000000,
	BE_FRC_SET_LOW_DELAY,
	BE_FRC_SET_YUV444,
	BE_FRC_ENABLE_DEBUG_BOX,
	BE_FRC_SET_FREEZE,
	BE_FRC_SET_USE_TYPE,
	BE_FRC_B0_RUN_COMMAND,

	BE_LED_LOAD_LUT				= 0xB0000000,
	BE_LED_SET_MODE,
	BE_WCG_LOAD_LUT,
	BE_WCG_SET_MODE,
	BE_LED_SET_PWM,
	BE_LED_SET_BPL_DATA
} BE_IPC_DEF_T;

//   BE_IPC_TOP    ////////////////////////////////////////////////

typedef struct
{
	UINT32	bInit;      			// 0: HDP All Block Normal, 1: HDP All Block Init
	UINT32	rsvd[3];
} BE_IPC_INIT_T;

typedef struct
{
	UINT32 	uTDPGMode;			// 0 : Normal PG, 1 : FPR
	UINT32	uTDSingleOn;		// 0 : Normal, 1 : Single
	UINT32	rsvd[2];
} BE_IPC_3D_OUT_FORMAT_T;

typedef struct
{
	UINT32	uFRCBypass;
	UINT32	uH3DBypass;
	UINT32	uWCGBypass;
	UINT32	rsvd;
} BE_IPC_BLOCK_BYPASS_T;

typedef struct
{
	UINT32  	uH3DDebugdisplay;
	UINT32  	uPEDebugDisplay;
	UINT32  	uLEDDebugDisplay;
} BE_IPC_DEBUG_DISPLAY_T;

typedef struct
{

} BE_IPC_SYSTEM_INFO_T;

typedef struct
{
	UINT32	bOutLR;				 // 0: Left/Top First, 1: Right/Bottom First
	UINT32	rsvd[3];
} BE_IPC_3D_LR_T;

typedef struct
{
	UINT32	uTDConvVal;
	UINT32	bTDConvEnable;
	UINT32	rsvd[2];
} BE_IPC_3D_CONVERGENCE_T;

typedef struct
{
	UINT32	uTDBlackBarEnable;
	UINT32	uTDBlackBarVal;
	UINT32	rsvd[2];
} BE_IPC_BLACK_BAR_T;

typedef struct
{
	UINT32	uRealCinemaEnable;
	UINT32	rsvd[3];
} BE_IPC_REAL_CINEMA_T;

typedef struct
{
	UINT32	bLSRMode;	// 0 : OFF, 1 : LO, 2 : HI
	UINT32	uBaseAddr;
	UINT32	uDbtype;	// [31:16] - version, [15:0] sizenum
	UINT32 	rsvd;
} BE_IPC_LSR_T;

typedef struct
{
	UINT32	bOrbitEnable;
	UINT32 	bAutoMode;		// 0: Justscan, 1: Overscan
	UINT32
	bOsdOverscan		: 8,
	bStoreMode			: 8,
	bPartialFrameMode 	: 8,
	rsvd1				: 8;
	UINT32 	rsvd2;
} BE_IPC_ORBIT_T;

typedef struct
{
	UINT32	uCPCParam;
	UINT32	rsvd[3];
} BE_IPC_CPC_T;

typedef struct
{
	UINT32	bGSRMode;	// 0 : OFF, 1 : LO, 2 : HI
	UINT32	uBaseAddr;
	UINT32	uDbtype;	// [31:16] - version, [15:0] sizenum
	UINT32 	rsvd;
} BE_IPC_GSR_T;

typedef struct
{
	UINT32	uDispResolution;	// 0 : 4K, 1 : 8K
	UINT32	uFrameRate; // 0 : 60Hz, 1 : 120Hz, 2 : 30Hz, 3 : VRR(120Hz)
	UINT32 	rsvd[2];
} BE_IPC_DISP_MODE_T;

typedef struct
{
	UINT32 	bIrrDataLoad;
	UINT32	uBaseAddr;
	UINT32 	rsvd[2];
} BE_IPC_IRR_T;

//   BE_IPC_H3D    ////////////////////////////////////////////////

typedef struct
{
	UINT32  	uT3CMode;
	UINT32  	rsvd[3];
} BE_IPC_H3D_MODE_T;

typedef struct
{
	UINT32  	uT3CDepth;
	UINT32  	rsvd[3];
} BE_IPC_H3D_T3C_DEPTH_T;

//   BE_IPC_FRC    ////////////////////////////////////////////////

typedef struct
{
	UINT32  	uFRCUserLevel;
	UINT32  	uFRCJudder;
	UINT32  	uFRCBlur;
	UINT32  	uFRCMotionProEn;	
	UINT32  	rsvd;
} BE_IPC_FRC_MEMC_MODE_T;

typedef struct
{
	UINT32  	bFRCLowDelay;
	UINT32  	rsvd[3];
} BE_IPC_FRC_LOW_DELAY_T;

typedef struct
{
	UINT32  	bFRCProcYUV444;      // 0 : 422, 1 : 444
	UINT32  	rsvd[3];
} BE_IPC_FRC_COLOR_YUV444_T;

typedef struct
{
	UINT32  	uDeboxMode;      // 0 : OFF,  1 :FRC, 2: 3D,  3: DE
	UINT32  	rsvd[3];
} BE_IPC_FRC_ENABLE_DEBUG_BOX_T;

  typedef struct
{
	UINT32  	bFRCFreeze;
	UINT32  	rsvd[3];
} BE_IPC_FRC_FREEZE_T;

////   BE_IPC_PE	///////////////////////////////////////////////////////////
typedef struct
{
	UINT32	bInit					:	4,
			reserved				:	28;
} BE_IPC_PE_INIT_BLOCK_T;

typedef struct
{
	UINT32	u8regnNum				:	8,	//	region number 0~15
			u8deltHue				:	8,	//	delta hue, -127 ~ 127
			u8deltSat				:	8,	//	delta saturation, -127 ~ 127
			u8deltVal				:	8;	//	delta value, -127 ~ 127
} BE_IPC_PE_CEN_CTRL0_T;

typedef struct
{
	UINT32	u8deltGrn				:	8,	//	delta green, -127 ~ 127
			u8deltBlu				:	8,	//	delta blue, -127 ~ 127
			u8deltRed				:	8,	//	delta red, -127 ~ 127
			u8gainMst				:	8;	//	master gain, 0 ~ 255
} BE_IPC_PE_CEN_CTRL1_T;

////   BE_IPC_LED WCG    ////////////////////////////////////////////////

typedef struct
{
	UINT32 	uLEDLutLoad;
	UINT32 	rsvd[3];
} BE_IPC_LED_LOAD_LUT_T;

typedef struct
{
	UINT32	uLEDEn;
	UINT32 	uLEDMode;
	UINT32 	rsvd[2];
}  BE_IPC_LED_MODE_T;

typedef struct
{
	UINT32 	bWCGLutLoad;
	UINT32	uBaseAddr;
	UINT32 	rsvd[2];
} BE_IPC_WCG_LOAD_LUT_T;

typedef struct
{
	UINT32	uWCGEn;
	UINT32 	uWCGMode;	// 0:BT709, 1:SMPTE, 2:EBU, 3:Color Extension, 4:BT2020
	UINT32 	rsvd[2];
}  BE_IPC_WCG_MODE_T;

typedef struct
{
	UINT32 	uPwmPort;
	UINT32 	bLowPowerModeEn;
	UINT32	uPwmDutyParams; // [31:16] : offset, [15:0] : duty
	UINT32 	uPwmCtrlParam; // free width
} BE_IPC_LED_PWM_T;

typedef struct
{
	UINT32 	bAiBrightnessAdjEn;
	UINT32 	uSensorLevel;
	UINT32 	rsvd[2];
} BE_IPC_LED_BPL_DATA_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef _IPC_DEF_M23_H_  ----- */
/**  @} */

