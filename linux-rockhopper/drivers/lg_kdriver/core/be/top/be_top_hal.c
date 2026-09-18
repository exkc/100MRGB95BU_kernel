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
 *	BE TOP module control Drivers linux module
 *
 *  author     dj911.kim@lge.com
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/timer.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/interrupt.h>

#include "os_util.h"
#include "be_dbg.h"
#include "be_def.h"

#include "be_top_hal.h"
#include "m17/be/top/be_top_hw_m17.h"
#include "o18/be/top/be_top_hw_o18.h"
#include "m19/be/top/be_top_hw_m19.h"
#include "o20/be/top/be_top_hw_o20.h"
#include "e60/be/top/be_top_hw_e60.h"
#include "o22/be/top/be_top_hw_o22.h"
#include "m23/be/top/be_top_hw_m23.h"
#include "o24/be/top/be_top_hw_o24.h"
#include "o26/be/top/be_top_hw_o26.h"

// Add here for register header file
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* SCDCR-4006 */
#define BE_TOP_HAL_PM_INFO(_level,_type,_result)	\
	do {\
		pr_info("LowPower::%s::video::be0::0::%s-%s::%s::%s::be\n",\
			_level,current->group_leader->comm,current->comm,_type,_result);\
	} while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	int (*BE_TOP_HWInitialize)(void);
	int (*BE_TOP_HWClose)(void);
	int (*BE_TOP_HWResume)(void);
	int (*BE_TOP_HWSetBypass)(LX_BE_BLOCK_BYPASS_T *pstParams);
	int (*BE_TOP_HWToggle3DLR)(LX_BE_3D_LR_T *pstParams);
	int (*BE_TOP_HWSet3DConvergence)(LX_BE_3D_CONVERGENCE_T *pstParams);
	int (*BE_TOP_HWSetBlackBar)(LX_BE_BLACK_BAR_T *pstParams);
	int (*BE_TOP_HWSetDebugDisplay)(LX_BE_DEBUG_DISPLAY_T *pstParams);
	int (*BE_TOP_HWSetRealCinema)(LX_BE_REAL_CINEMA_T *pstParams);
	int (*BE_TOP_HWSetOrbit)(LX_BE_ORBIT_T *pstParams);
	int (*BE_TOP_HWSetLSR)(BOOLEAN bParam);
	int (*BE_TOP_HWSetLag)(UINT32 bParam);
	int (*BE_TOP_HWSetLagPattern)(LX_BE_INPUT_LAG_PATTERN_T *pstParams);
	int (*BE_TOP_HWSetLSRParam)(LX_BE_LSR_T *pstParams);
	int (*BE_TOP_HWSetGSR)(LX_BE_GSR_T *pstParams);
	int (*BE_TOP_HWSetGSR2)(LX_BE_GSR_T *pstParams);
	int (*BE_TOP_HWGetGSRStatus)(BOOLEAN *pbParam);
	int (*BE_TOP_HWGetGSRStressCount)(UINT32 *pu32Param);
	int (*BE_TOP_HWSetCPC)(UINT32 u32Param);
	int (*BE_TOP_HWGetOSDAlphaAPL)(LX_BE_LUT_T *pstParams);
	int (*BE_TOP_HWSetOSDRGBLevel)(LX_BE_OSD_RGB_LEVEL_T *pstParams);
	int (*BE_TOP_HWSetIrrAdaptedLum)(LX_BE_LUT_T *pstParams);
	int (*BE_TOP_HWGetIrrResult)(UINT32 *pu32Param);
	int (*BE_TOP_HWGetIrrStatus)(LX_BE_IRR_STATUS_T *pstParams); // only used for kadpd
	int (*BE_TOP_HWSetIrrData)(LX_BE_LUT_T *pstParams); // only used for kadpd
	int (*BE_TOP_HWGetIrrData)(LX_BE_IRR_READ_T *pstParams); // only used for kadpd	
	int (*BE_TOP_HWSetTPCParam)(LX_BE_LUT_T *pstParams);
	int (*BE_TOP_HWGetTPCStatus)(LX_BE_LUT_T *pstParams);
	int (*BE_TOP_HWGetAplTpc)(LX_BE_LUT_T *pstParams);
	int (*BE_TOP_HWGetDispApl)(UINT32 *pu32Param);
	int (*BE_TOP_HWSetOledAplCtrlParam)(LX_BE_LUT_T *pstParams);
	int (*BE_TOP_HWSetDispMode)(LX_BE_DISP_MODE_T *pstParams);
	int (*BE_TOP_HWSetOaplMaxWeight)(int Param);
	int (*BE_TOP_HWSetVideoVReverse)(BOOLEAN bParam);
	int (*BE_TOP_HWSetFRCStatus)(UINT32 u32Param);
	int (*BE_TOP_HWInformFBDEVStatus)(LX_BE_FBDEV_STATUS_T *pstParams);
	int (*BE_TOP_HWGetFWOSDStatus)(LX_BE_FW_OSD_STATUS_T *pstParams);
	int (*BE_TOP_HWProcHandler)(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data);
	int (*BE_TOP_HWSetPmMode)(UINT32 u32Param);
	int (*BE_TOP_HWGetPatternInfo)(void *pParam, UINT32 *size); // only for +W22 AV wireless model W/A(SCDCR-3962)
	int (*BE_TOP_HWSetDClock)(UINT32 *pu32Param);
	int (*BE_TOP_HWSetGenlock)(LX_BE_SET_GENLOCK_T *pstParams);
	int (*BE_TOP_HWSetPcce)(LX_BE_IPC_PCCE_T *pstParams);
	int (*BE_TOP_HWSetOutputTiming)(LX_OVI_TCON_OUTPUT_TIMING_T *pstParams);
} BE_TOP_HW_FUNCTION_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static BE_TOP_HW_FUNCTION_T stBeTopHwFunction;

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
* BE_TOP Module Pre Initialize
*
* @param void
* @return int
*/
int BE_TOP_HAL_PreInit(void)
{
	int ret = RET_OK;

	memset(&stBeTopHwFunction,0,sizeof(BE_TOP_HW_FUNCTION_T));

	if(0)
	{

	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O26 A0\n");
		stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus	= BE_TOP_HW_O26_InformFBDEVStatus;
		stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus		= BE_TOP_HW_O26_GetFWOSDStatus;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O24 A0\n");
		stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus	= BE_TOP_HW_O24_InformFBDEVStatus;
		stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus		= BE_TOP_HW_O24_GetFWOSDStatus;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to M23 A0\n");
		stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus	= BE_TOP_HW_M23_InformFBDEVStatus;
		stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus		= BE_TOP_HW_M23_GetFWOSDStatus;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O22 A0\n");
		stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus	= BE_TOP_HW_O22_InformFBDEVStatus;
		stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus		= BE_TOP_HW_O22_GetFWOSDStatus;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to E60 A0\n");
		stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus 	= BE_TOP_HW_E60_InformFBDEVStatus;
		stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus 		= BE_TOP_HW_E60_GetFWOSDStatus;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O20 A0\n");
		stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus 	= BE_TOP_HW_O20_InformFBDEVStatus;
		stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus 		= BE_TOP_HW_O20_GetFWOSDStatus;
	}
#endif
	else
	{

BE_ERROR("BE TOP ERROR! Unknown chip revision at OVI module\n");
		stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus 	= NULL;
		stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus 		= NULL;
		ret = RET_ERROR;
	}

	return ret;
}

/**
* BE_TOP Module Initialize
*
* @param void
* @return int
*/
int BE_TOP_HAL_Init(void)
{
	int ret = RET_OK;

	stBeTopHwFunction.BE_TOP_HWSetDClock = NULL;
	stBeTopHwFunction.BE_TOP_HWGetDispApl = NULL;
	stBeTopHwFunction.BE_TOP_HWSetPcce = NULL;

	if(0)
	{

	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O26 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize			= BE_TOP_HW_O26_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= BE_TOP_HW_O26_Resume;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_O26_SetBypass;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_O26_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetOrbit 			= BE_TOP_HW_O26_SetOrbit;
		#ifdef BE_TOP_HW_O26_TEST_INPUT_LAG
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= BE_TOP_HW_O26_SetLagParam;
		#else
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= NULL;
		#endif
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= BE_TOP_HW_O26_SetLSRParam;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= BE_TOP_HW_O26_SetGSR;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= BE_TOP_HW_O26_SetGSR2;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus 		= BE_TOP_HW_O26_GetGSRStatus;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount	= BE_TOP_HW_O26_GetGSRStressCount;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= BE_TOP_HW_O26_SetCPC;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= BE_TOP_HW_O26_GetOSDAlphaAPL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= BE_TOP_HW_O26_SetOSDRGBLevel;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= BE_TOP_HW_O26_SetIrrAdaptedLum;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= BE_TOP_HW_O26_GetIrrResult;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= BE_TOP_HW_O26_GetIrrStatus;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= BE_TOP_HW_O26_SetIrrData;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= BE_TOP_HW_O26_GetIrrData;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= BE_TOP_HW_O26_SetTpcParam;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= BE_TOP_HW_O26_GetTpcStatus;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= BE_TOP_HW_O26_GetApiForTpc;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= BE_TOP_HW_O26_SetOledAplCtrlParam;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= BE_TOP_HW_O26_SetDispMode;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse 	= BE_TOP_HW_O26_SetVideoVReverse;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus 		= BE_TOP_HW_O26_SetFRCStatus;
		stBeTopHwFunction.BE_TOP_HWSetPmMode			= BE_TOP_HW_O26_SetPmMode;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= BE_TOP_HW_O26_SetOaplMaxWeight;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_O26_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWGetPatternInfo		= BE_TOP_HW_O26_GetPatternInfo;
		stBeTopHwFunction.BE_TOP_HWSetDClock			= BE_TOP_HW_O26_SetDClock;
		stBeTopHwFunction.BE_TOP_HWGetDispApl			= be_top_hw_o26_get_disp_apl;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= BE_TOP_HW_O26_SetGenlock;
		stBeTopHwFunction.BE_TOP_HWSetPcce				= BE_TOP_HW_O26_SetPcce;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= BE_TOP_HW_O26_SetOutputTiming;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O24 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize			= BE_TOP_HW_O24_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= BE_TOP_HW_O24_Resume;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_O24_SetBypass;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= NULL;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_O24_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;//NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit 			= BE_TOP_HW_O24_SetOrbit;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLag				= NULL;//warning: assignment from incompatible pointer type
		#ifdef BE_TOP_HW_O24_TEST_INPUT_LAG
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= BE_TOP_HW_O24_SetLagParam;
		#else
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= NULL;
		#endif
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= BE_TOP_HW_O24_SetLSRParam;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= BE_TOP_HW_O24_SetGSR;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= BE_TOP_HW_O24_SetGSR2;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus 		= BE_TOP_HW_O24_GetGSRStatus;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount	= BE_TOP_HW_O24_GetGSRStressCount;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= BE_TOP_HW_O24_SetCPC;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= BE_TOP_HW_O24_GetOSDAlphaAPL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= BE_TOP_HW_O24_SetOSDRGBLevel;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= BE_TOP_HW_O24_SetIrrAdaptedLum;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= BE_TOP_HW_O24_GetIrrResult;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= BE_TOP_HW_O24_GetIrrStatus;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= BE_TOP_HW_O24_SetIrrData;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= BE_TOP_HW_O24_GetIrrData;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= BE_TOP_HW_O24_SetTpcParam;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= BE_TOP_HW_O24_GetTpcStatus;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= BE_TOP_HW_O24_GetApiForTpc;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= BE_TOP_HW_O24_SetOledAplCtrlParam;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= BE_TOP_HW_O24_SetDispMode;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse 	= BE_TOP_HW_O24_SetVideoVReverse;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus 		= BE_TOP_HW_O24_SetFRCStatus;
		stBeTopHwFunction.BE_TOP_HWSetPmMode			= BE_TOP_HW_O24_SetPmMode;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= BE_TOP_HW_O24_SetOaplMaxWeight;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_O24_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWGetPatternInfo		= BE_TOP_HW_O24_GetPatternInfo;
		stBeTopHwFunction.BE_TOP_HWSetDClock			= BE_TOP_HW_O24_SetDClock;
		stBeTopHwFunction.BE_TOP_HWGetDispApl			= be_top_hw_o24_get_disp_apl;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to M23 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize				= BE_TOP_HW_M23_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= BE_TOP_HW_M23_Resume;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_M23_SetBypass;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= NULL;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence = NULL;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_M23_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit 			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLag				= NULL;//warning: assignment from incompatible pointer type
	#ifdef BE_TOP_HW_M23_TEST_INPUT_LAG
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= BE_TOP_HW_M23_SetLagParam;
	#else
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= NULL;
	#endif
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= NULL;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus 		= NULL;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= BE_TOP_HW_M23_SetCPC;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= BE_TOP_HW_M23_GetOSDAlphaAPL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum 	= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult 		= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus 		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= BE_TOP_HW_M23_SetDispMode;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse 	= BE_TOP_HW_M23_SetVideoVReverse;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus 		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetPmMode			= BE_TOP_HW_M23_SetPmMode;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_M23_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWGetPatternInfo		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O22 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize				= BE_TOP_HW_O22_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= BE_TOP_HW_O22_Resume;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_O22_SetBypass;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= NULL;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence = NULL;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_O22_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit 			= BE_TOP_HW_O22_SetOrbit;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLag				= NULL;//warning: assignment from incompatible pointer type
		#ifdef BE_TOP_HW_O22_TEST_INPUT_LAG
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= BE_TOP_HW_O22_SetLagParam;
		#else
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= NULL;
		#endif
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= BE_TOP_HW_O22_SetLSRParam;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= BE_TOP_HW_O22_SetGSR;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= BE_TOP_HW_O22_SetGSR2;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus 		= BE_TOP_HW_O22_GetGSRStatus;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount	= BE_TOP_HW_O22_GetGSRStressCount;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= BE_TOP_HW_O22_SetCPC;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= BE_TOP_HW_O22_GetOSDAlphaAPL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= BE_TOP_HW_O22_SetOSDRGBLevel;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= BE_TOP_HW_O22_SetIrrAdaptedLum;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= BE_TOP_HW_O22_GetIrrResult;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= BE_TOP_HW_O22_GetIrrStatus;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= BE_TOP_HW_O22_SetIrrData;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= BE_TOP_HW_O22_GetIrrData;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= BE_TOP_HW_O22_SetTpcParam;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= BE_TOP_HW_O22_GetTpcStatus;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= BE_TOP_HW_O22_GetApiForTpc;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= BE_TOP_HW_O22_SetDispMode;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse 	= BE_TOP_HW_O22_SetVideoVReverse;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus 		= BE_TOP_HW_O22_SetFRCStatus;
		stBeTopHwFunction.BE_TOP_HWSetPmMode			= BE_TOP_HW_O22_SetPmMode;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_O22_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWGetPatternInfo		= BE_TOP_HW_O22_GetPatternInfo;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to E60 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize				= BE_TOP_HW_E60_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= BE_TOP_HW_E60_Resume;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_E60_SetBypass;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= NULL;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence = NULL;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_E60_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit 			= BE_TOP_HW_E60_SetOrbit;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLag				= BE_TOP_HW_E60_SetLagParam;
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= BE_TOP_HW_E60_SetLagParam;
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= BE_TOP_HW_E60_SetLSRParam;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= BE_TOP_HW_E60_SetGSR;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= BE_TOP_HW_E60_SetGSR2;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus 		= BE_TOP_HW_E60_GetGSRStatus;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount 	= BE_TOP_HW_E60_GetGSRStressCount;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= BE_TOP_HW_E60_SetCPC;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= BE_TOP_HW_E60_GetOSDAlphaAPL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= BE_TOP_HW_E60_SetOSDRGBLevel;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= BE_TOP_HW_E60_SetDispMode;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse 	= BE_TOP_HW_E60_SetVideoVReverse;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus 		= BE_TOP_HW_E60_SetFRCStatus;
		stBeTopHwFunction.BE_TOP_HWSetPmMode			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_E60_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O20 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize				= BE_TOP_HW_O20_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= BE_TOP_HW_O20_Resume;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_O20_SetBypass;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= NULL;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence = NULL;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_O20_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit 			= BE_TOP_HW_O20_SetOrbit;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLag				= BE_TOP_HW_O20_SetLagParam;
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= BE_TOP_HW_O20_SetLagParam;
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= BE_TOP_HW_O20_SetLSRParam;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= BE_TOP_HW_O20_SetGSR;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= BE_TOP_HW_O20_SetGSR2;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus 		= BE_TOP_HW_O20_GetGSRStatus;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount 	= BE_TOP_HW_O20_GetGSRStressCount;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= BE_TOP_HW_O20_SetCPC;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= BE_TOP_HW_O20_GetOSDAlphaAPL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= BE_TOP_HW_O20_SetOSDRGBLevel;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= BE_TOP_HW_O20_SetDispMode;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse		= BE_TOP_HW_O20_SetVideoVReverse;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus         = BE_TOP_HW_O20_SetFRCStatus;
		stBeTopHwFunction.BE_TOP_HWSetPmMode			= BE_TOP_HW_O20_SetPmMode;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_O20_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWGetPatternInfo		= BE_TOP_HW_O20_GetPatternInfo;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to M19 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize				= BE_TOP_HW_M19_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= BE_TOP_HW_M19_Resume;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_M19_SetBypass;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= BE_TOP_HW_M19_Toggle3DLR;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence = BE_TOP_HW_M19_Set3DConvergence;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= BE_TOP_HW_M19_SetBlackBar;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_M19_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit				= BE_TOP_HW_M19_SetOrbit;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLag				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= BE_TOP_HW_M19_SetLagPatternParam;
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= BE_TOP_HW_M19_SetLSRParam;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= BE_TOP_HW_M19_SetGSR;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= NULL;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus			= BE_TOP_HW_M19_GetGSRStatus;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount 	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= NULL;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= BE_TOP_HW_M19_GetOSDAlphaAPL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= BE_TOP_HW_M19_SetOSDRGBLevel;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus         = NULL;
		stBeTopHwFunction.BE_TOP_HWSetPmMode			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_M19_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to O18 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize				= BE_TOP_HW_O18_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_O18_SetBypass;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= NULL;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence = NULL;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_O18_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit				= BE_TOP_HW_O18_SetOrbit;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLag				= BE_TOP_HW_O18_SetLagParam;
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= BE_TOP_HW_O18_SetLagParam;
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= BE_TOP_HW_O18_SetLSRParam;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= BE_TOP_HW_O18_SetGSR;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= NULL;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus			= BE_TOP_HW_O18_GetGSRStatus;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount 	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= BE_TOP_HW_O18_SetCPC;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= BE_TOP_HW_O18_GetOSDAlphaAPL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= BE_TOP_HW_O18_SetOSDRGBLevel;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= BE_TOP_HW_O18_SetDispMode;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus         = NULL;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_O18_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		BE_PRINT("BE TOP chip revision is set to M17 A0\n");
		stBeTopHwFunction.BE_TOP_HWInitialize				= BE_TOP_HW_M17_Initialize;
		stBeTopHwFunction.BE_TOP_HWResume				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= BE_TOP_HW_M17_SetBypass;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= BE_TOP_HW_M17_Toggle3DLR;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence = BE_TOP_HW_M17_Set3DConvergence;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= BE_TOP_HW_M17_SetBlackBar;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= BE_TOP_HW_M17_SetDebugDisplay;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit				= BE_TOP_HW_M17_SetOrbit;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= BE_TOP_HW_M17_SetLSR;
		stBeTopHwFunction.BE_TOP_HWSetLag				= BE_TOP_HW_M17_SetLagParam;
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= BE_TOP_HW_M17_SetLSRParam;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= BE_TOP_HW_M17_SetGSR;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= NULL;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus			= BE_TOP_HW_M17_GetGSRStatus;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount 	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= NULL;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= BE_TOP_HW_M17_SetOSDRGBLevel;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus         = NULL;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= BE_TOP_HW_M17_ProcHandler;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
	}
#endif
	else
	{
		BE_ERROR("BE TOP ERROR! Unknown chip revision at BE TOP module\n");
		stBeTopHwFunction.BE_TOP_HWInitialize				= NULL;
		stBeTopHwFunction.BE_TOP_HWResume				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetBypass			= NULL;
		stBeTopHwFunction.BE_TOP_HWToggle3DLR			= NULL;
		stBeTopHwFunction.BE_TOP_HWSet3DConvergence	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetBlackBar			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOrbit				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLag				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLagPattern		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetLSRParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetGSR				= NULL;
		stBeTopHwFunction.BE_TOP_HWSetGSR2				= NULL;
		stBeTopHwFunction.BE_TOP_HWGetGSRStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetGSRStressCount 	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetCPC				= NULL;
		stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrResult			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetIrrData			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetTPCParam			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= NULL;
		stBeTopHwFunction.BE_TOP_HWGetAplTpc			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
		stBeTopHwFunction.BE_TOP_HWSetDispMode			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetVideoVReverse		= NULL;
		stBeTopHwFunction.BE_TOP_HWSetFRCStatus         = NULL;
		stBeTopHwFunction.BE_TOP_HWSetPmMode			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
		stBeTopHwFunction.BE_TOP_HWClose				= NULL;
		stBeTopHwFunction.BE_TOP_HWProcHandler			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
		stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;
		ret = RET_ERROR;
	}

	if(stBeTopHwFunction.BE_TOP_HWInitialize)
	{
		ret = stBeTopHwFunction.BE_TOP_HWInitialize();
	}

	return ret;
}

int BE_TOP_HAL_Close(void)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWClose)
	{
		ret = stBeTopHwFunction.BE_TOP_HWClose();
	}

	stBeTopHwFunction.BE_TOP_HWInitialize				= NULL;
	stBeTopHwFunction.BE_TOP_HWResume				= NULL;
	stBeTopHwFunction.BE_TOP_HWSetBypass			= NULL;
	stBeTopHwFunction.BE_TOP_HWToggle3DLR			= NULL;
	stBeTopHwFunction.BE_TOP_HWSet3DConvergence	= NULL;
	stBeTopHwFunction.BE_TOP_HWSetBlackBar			= NULL;
	stBeTopHwFunction.BE_TOP_HWSetDebugDisplay		= NULL;
	stBeTopHwFunction.BE_TOP_HWSetRealCinema		= NULL;
	stBeTopHwFunction.BE_TOP_HWSetOrbit				= NULL;
	stBeTopHwFunction.BE_TOP_HWSetLSR				= NULL;
	stBeTopHwFunction.BE_TOP_HWSetLSRParam			= NULL;
	stBeTopHwFunction.BE_TOP_HWSetGSR				= NULL;
	stBeTopHwFunction.BE_TOP_HWSetGSR2				= NULL;
	stBeTopHwFunction.BE_TOP_HWGetGSRStatus			= NULL;
	stBeTopHwFunction.BE_TOP_HWGetGSRStressCount 	= NULL;
	stBeTopHwFunction.BE_TOP_HWSetCPC				= NULL;
	stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL		= NULL;
	stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel		= NULL;
	stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum		= NULL;
	stBeTopHwFunction.BE_TOP_HWGetIrrResult			= NULL;
	stBeTopHwFunction.BE_TOP_HWGetIrrStatus			= NULL;
	stBeTopHwFunction.BE_TOP_HWSetIrrData			= NULL;
	stBeTopHwFunction.BE_TOP_HWGetIrrData			= NULL;
	stBeTopHwFunction.BE_TOP_HWSetTPCParam			= NULL;
	stBeTopHwFunction.BE_TOP_HWGetTPCStatus			= NULL;
	stBeTopHwFunction.BE_TOP_HWGetAplTpc			= NULL;
	stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam	= NULL;
	stBeTopHwFunction.BE_TOP_HWSetDispMode			= NULL;
	stBeTopHwFunction.BE_TOP_HWSetVideoVReverse		= NULL;
	stBeTopHwFunction.BE_TOP_HWSetFRCStatus         = NULL;
	stBeTopHwFunction.BE_TOP_HWSetPmMode			= NULL;
	stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight		= NULL;
	stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus 	= NULL;
	stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus 		= NULL;
	stBeTopHwFunction.BE_TOP_HWClose				= NULL;
	stBeTopHwFunction.BE_TOP_HWProcHandler			= NULL;
	stBeTopHwFunction.BE_TOP_HWGetPatternInfo		= NULL;
	stBeTopHwFunction.BE_TOP_HWSetGenlock			= NULL;
	stBeTopHwFunction.BE_TOP_HWSetPcce				= NULL;
	stBeTopHwFunction.BE_TOP_HWSetOutputTiming		= NULL;

	return ret;
}

int BE_TOP_HAL_Resume(void)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWResume)
	{
		ret = stBeTopHwFunction.BE_TOP_HWResume();
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetBypass)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetBypass(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_Toggle3DLR(LX_BE_3D_LR_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWToggle3DLR)
	{
		ret = stBeTopHwFunction.BE_TOP_HWToggle3DLR(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_Set3DConvergence(LX_BE_3D_CONVERGENCE_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSet3DConvergence)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSet3DConvergence(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetBlackBar(LX_BE_BLACK_BAR_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetBlackBar)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetBlackBar(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetDebugDisplay)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetDebugDisplay(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetRealCinema(LX_BE_REAL_CINEMA_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetRealCinema)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetRealCinema(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetOrbit(LX_BE_ORBIT_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetOrbit)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetOrbit(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetLSR(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetLSR)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetLSR(bParam);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetInputLagTest(UINT32 bParam)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetLag)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetLag(bParam);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetInputLagPattern(LX_BE_INPUT_LAG_PATTERN_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetLagPattern)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetLagPattern(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetLSRParam(LX_BE_LSR_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetLSRParam)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetLSRParam(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetGSR(LX_BE_GSR_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetGSR)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetGSR(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetGSR2(LX_BE_GSR_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetGSR2)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetGSR2(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetGSRStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetGSRStatus)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetGSRStatus(pbParam);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetGSRStressCount(UINT32 *pu32Param)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetGSRStressCount)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetGSRStressCount(pu32Param);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetCPC(UINT32 u32Param)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetCPC)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetCPC(u32Param);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetOSDAlphaAPL(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetOSDRGBLevel(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetIrrAdaptedLum(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetIrrAdaptedLum(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetIrrResult(UINT32 *pu32Param)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetIrrResult)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetIrrResult(pu32Param);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetIrrStatus(LX_BE_IRR_STATUS_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetIrrStatus)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetIrrStatus(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetIrrData(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetIrrData)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetIrrData(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetIrrData(LX_BE_IRR_READ_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetIrrData)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetIrrData(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetTPCParam(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetTPCParam)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetTPCParam(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetTPCStatus(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetTPCStatus)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetTPCStatus(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetAplForTpc(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetAplTpc)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetAplTpc(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetOledAplCtrlParam(LX_BE_LUT_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetOledAplCtrlParam(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetDispMode(LX_BE_DISP_MODE_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetDispMode)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetDispMode(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetVideoVReverse(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetVideoVReverse)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetVideoVReverse(bParam);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetFRCStatus(UINT32 u32Param)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetFRCStatus)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetFRCStatus(u32Param);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetPmMode(UINT32 u32Param)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetPmMode)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetPmMode(u32Param);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	BE_TOP_HAL_PM_INFO("info", "set_mode", ret == RET_OK ? "OK" : "NG");

	return ret;
}

int BE_TOP_HAL_SetOaplMaxWeight(int Param)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetOaplMaxWeight(Param);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus)
	{
		ret = stBeTopHwFunction.BE_TOP_HWInformFBDEVStatus(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetFWOSDStatus(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
    int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWProcHandler)
    {
		ret = stBeTopHwFunction.BE_TOP_HWProcHandler(proc_id, m, data);
    }
    else
    {
        ret = RET_ERROR;
    }

    return ret;
}

// only for +W22 AV wireless model W/A(SCDCR-3962)
int BE_TOP_HAL_Get_PatternInfo(void *pParam, UINT32 *size)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetPatternInfo)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetPatternInfo(pParam, size);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetDClock(UINT32 *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetDClock)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetDClock(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_GetDispApl(UINT32 *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWGetDispApl)
	{
		ret = stBeTopHwFunction.BE_TOP_HWGetDispApl(pstParams);
	}

	return ret;
}

int BE_TOP_HAL_SetGenlock(LX_BE_SET_GENLOCK_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetGenlock)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetGenlock(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_TOP_HAL_SetPcce(LX_BE_IPC_PCCE_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetPcce)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetPcce(pstParams);
	}

	return ret;
}

int BE_TOP_HAL_SetOutputTiming(LX_OVI_TCON_OUTPUT_TIMING_T *pstParams)
{
	int ret = RET_OK;

	if(stBeTopHwFunction.BE_TOP_HWSetOutputTiming)
	{
		ret = stBeTopHwFunction.BE_TOP_HWSetOutputTiming(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

/** @} */
