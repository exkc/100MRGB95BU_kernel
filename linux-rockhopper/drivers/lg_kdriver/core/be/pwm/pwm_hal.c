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
 *  PWM HAL file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2012.06.30
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
//#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <asm/io.h>
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"
#include "be_def.h"

#include "pwm_hal.h"
#include "m17/be/pwm/be_pwm_hw_m17.h"
#include "o18/be/pwm/be_pwm_hw_o18.h"
#include "m19/be/pwm/be_pwm_hw_m19.h"
#include "o20/be/pwm/be_pwm_hw_o20.h"
#include "e60/be/pwm/be_pwm_hw_e60.h"
#include "o22/be/pwm/be_pwm_hw_o22.h"
#include "m23/be/pwm/be_pwm_hw_m23.h"
#include "o24/be/pwm/be_pwm_hw_o24.h"
#include "o26/be/pwm/be_pwm_hw_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	int (*pfnInitializePWM)(void);
	int (*pfnSuspend) (void);
	int (*pfnResume) (void);
	int (*pfnClosePWM)(void);
	int (*pfnSetControlPWM)(BE_PWM_CTRL_T *pstParams);
	int (*pfnSetAdaptFreqControlPWM)(BE_PWM_ADAPT_FREQ_CTRL_T *pstParams);
	int (*pfnSetFrequencyPWM)(BE_PWM_FREQ_T *pstParams);
	int (*pfnSetDutyCyclePWM)(BE_PWM_DUTY_T *pstParams);
	int (*pfnSetDutyRatioPWM)(BE_PWM_DUTY_RATIO_T *pstParams);
	int (*pfnSetParamsPWM)(LX_BE_PWM_PARAMS_T *pstParams);
	int (*pfnGetInfoExternalPWM)(BE_EXTERNAL_PWM_T *pstParams);
	int (*pfnSetSyncPWM)(BE_PWM_FREQ_T *pstParams);
	int (*pfnProcHandler)(BE_PWM_PROC_ID_T proc_id, struct seq_file* m, void* data);
	int (*pfnSetClk)(UINT32 clk);
	int (*pfnSetCtrlStop)(UINT32 stop);
} BE_PWM_HW_FUNCTION_T;

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
static BE_PWM_HW_FUNCTION_T gstBePwmHwFunction;

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_PWM_HAL_Init(void)
{
	int ret = RET_OK;

	memset(&gstBePwmHwFunction,0,sizeof(BE_PWM_HW_FUNCTION_T));

	if(0)
	{

	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to O26 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_O26_Init;
		gstBePwmHwFunction.pfnSuspend 					= BE_PWM_HW_O26_Suspend;
		gstBePwmHwFunction.pfnResume 					= BE_PWM_HW_O26_Resume;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_O26_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM	= BE_PWM_HW_O26_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_O26_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_O26_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_O26_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_O26_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM		= BE_PWM_HW_O26_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_O26_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_O26_ProcHandler;
		gstBePwmHwFunction.pfnSetClk					= BE_PWM_HW_O26_SetClk;
		gstBePwmHwFunction.pfnSetCtrlStop				= BE_PWM_HW_O26_SetCtrlStop;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to O24 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_O24_Init;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_O24_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM	= BE_PWM_HW_O24_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_O24_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_O24_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_O24_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_O24_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM		= BE_PWM_HW_O24_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_O24_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_O24_ProcHandler;
		gstBePwmHwFunction.pfnSetClk					= BE_PWM_HW_O24_SetClk;
		gstBePwmHwFunction.pfnSetCtrlStop				= BE_PWM_HW_O24_SetCtrlStop;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to M23 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_M23_Init;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_M23_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM	= BE_PWM_HW_M23_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_M23_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_M23_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_M23_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_M23_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM		= BE_PWM_HW_M23_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_M23_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_M23_ProcHandler;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to O22 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_O22_Init;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_O22_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM	= BE_PWM_HW_O22_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_O22_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_O22_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_O22_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_O22_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM		= BE_PWM_HW_O22_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_O22_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_O22_ProcHandler;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to E60 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_E60_Init;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_E60_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM	= BE_PWM_HW_E60_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_E60_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_E60_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_E60_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_E60_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM		= BE_PWM_HW_E60_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_E60_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_E60_ProcHandler;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to O20 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_O20_Init;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_O20_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM	= BE_PWM_HW_O20_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_O20_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_O20_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_O20_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_O20_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM		= BE_PWM_HW_O20_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_O20_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_O20_ProcHandler;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to M19 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_M19_Init;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_M19_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM		= BE_PWM_HW_M19_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_M19_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_M19_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_M19_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_M19_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM			= BE_PWM_HW_M19_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_M19_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_M19_ProcHandler;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to O18 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_O18_Init;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_O18_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM	= BE_PWM_HW_O18_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_O18_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_O18_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_O18_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_O18_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM		= BE_PWM_HW_O18_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_O18_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_O18_ProcHandler;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		BE_PRINT("BE PWM chip revision is set to M17 A0\n");
		gstBePwmHwFunction.pfnInitializePWM 			= BE_PWM_HW_M17_Init;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM 			= BE_PWM_HW_M17_SetPwmControl;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM		= BE_PWM_HW_M17_SetPwmAdaptFreqControl;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= BE_PWM_HW_M17_SetPwmFrequency;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= BE_PWM_HW_M17_SetPwmDutyCycle;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= BE_PWM_HW_M17_SetPwmDutyRatio;
		gstBePwmHwFunction.pfnSetParamsPWM				= BE_PWM_HW_M17_SetPwmParams;
		gstBePwmHwFunction.pfnGetInfoExternalPWM			= BE_PWM_HW_M17_GetPwmInfo;
		gstBePwmHwFunction.pfnSetSyncPWM				= BE_PWM_HW_M17_SetPwmSync;
		gstBePwmHwFunction.pfnProcHandler				= BE_PWM_HW_M17_ProcHandler;
	}
#endif
	else
	{
		BE_ERROR("BE PWM ERROR! Unknown chip revision at BE PWM module\n");
		gstBePwmHwFunction.pfnInitializePWM				= NULL;
		gstBePwmHwFunction.pfnClosePWM					= NULL;
		gstBePwmHwFunction.pfnSetControlPWM				= NULL;
		gstBePwmHwFunction.pfnSetAdaptFreqControlPWM		= NULL;
		gstBePwmHwFunction.pfnSetFrequencyPWM			= NULL;
		gstBePwmHwFunction.pfnSetDutyCyclePWM			= NULL;
		gstBePwmHwFunction.pfnSetDutyRatioPWM			= NULL;
		gstBePwmHwFunction.pfnSetParamsPWM				= NULL;
		gstBePwmHwFunction.pfnGetInfoExternalPWM			= NULL;
		gstBePwmHwFunction.pfnSetSyncPWM				= NULL;
		gstBePwmHwFunction.pfnProcHandler				= NULL;

		ret = RET_ERROR;
	}

	if(gstBePwmHwFunction.pfnInitializePWM)
	{
		ret = gstBePwmHwFunction.pfnInitializePWM();
	}

	return ret;
}

int BE_PWM_HAL_Close(void)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnClosePWM)
	{
		ret = gstBePwmHwFunction.pfnClosePWM();
	}

	gstBePwmHwFunction.pfnInitializePWM				= NULL;
	gstBePwmHwFunction.pfnClosePWM					= NULL;
	gstBePwmHwFunction.pfnSetControlPWM				= NULL;
	gstBePwmHwFunction.pfnSetAdaptFreqControlPWM		= NULL;
	gstBePwmHwFunction.pfnSetFrequencyPWM			= NULL;
	gstBePwmHwFunction.pfnSetDutyCyclePWM			= NULL;
	gstBePwmHwFunction.pfnSetDutyRatioPWM			= NULL;
	gstBePwmHwFunction.pfnSetParamsPWM				= NULL;
	gstBePwmHwFunction.pfnGetInfoExternalPWM			= NULL;
	gstBePwmHwFunction.pfnSetSyncPWM				= NULL;
	gstBePwmHwFunction.pfnProcHandler				= NULL;

	return ret;
}

int BE_PWM_HAL_SetPwmControl(BE_PWM_CTRL_T *pstParams)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSetControlPWM)
	{
		ret = gstBePwmHwFunction.pfnSetControlPWM(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_PWM_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_PWM_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_PWM_HAL_SetPwmAdaptFreqControl(BE_PWM_ADAPT_FREQ_CTRL_T *pstParams)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSetAdaptFreqControlPWM)
	{
		ret = gstBePwmHwFunction.pfnSetAdaptFreqControlPWM(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_PWM_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_PWM_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_PWM_HAL_SetPwmFrequency(BE_PWM_FREQ_T *pstParams)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSetFrequencyPWM)
	{
		ret = gstBePwmHwFunction.pfnSetFrequencyPWM(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_PWM_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_PWM_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_PWM_HAL_SetPwmDutyCycle(BE_PWM_DUTY_T *pstParams)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSetDutyCyclePWM)
	{
		ret = gstBePwmHwFunction.pfnSetDutyCyclePWM(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_PWM_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_PWM_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_PWM_HAL_SetPwmDutyRatio(BE_PWM_DUTY_RATIO_T *pstParams)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSetDutyRatioPWM)
	{
		ret = gstBePwmHwFunction.pfnSetDutyRatioPWM(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_PWM_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_PWM_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_PWM_HAL_SetPwmParams(LX_BE_PWM_PARAMS_T *pstParams)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSetParamsPWM)
	{
		ret = gstBePwmHwFunction.pfnSetParamsPWM(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_PWM_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_PWM_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_PWM_HAL_GetPwmInfoExternal(BE_EXTERNAL_PWM_T *pstParams)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnGetInfoExternalPWM)
	{
		ret = gstBePwmHwFunction.pfnGetInfoExternalPWM(pstParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_PWM_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_PWM_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_PWM_HAL_SetPwmSync(UINT32 u32Frequency)
{
	int ret = RET_OK;
	BE_PWM_FREQ_T stParams;

	if(gstBePwmHwFunction.pfnSetSyncPWM)
	{
		stParams.port = BE_PWM_MAX; // Call from ISR
		stParams.frequency = u32Frequency;
		ret = gstBePwmHwFunction.pfnSetSyncPWM(&stParams);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_PWM_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_PWM_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_PWM_HAL_ProcHandler(BE_PWM_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnProcHandler)
	{
		ret = gstBePwmHwFunction.pfnProcHandler(proc_id, m, data);
	}
	else
	{
		ret = RET_ERROR;
	}

	return ret;
}

int BE_PWM_HAL_SetClk(UINT32 clk)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSetClk)
	{
		ret = gstBePwmHwFunction.pfnSetClk(clk);
	}

	return ret;
}

int BE_PWM_HAL_SetCtrlStop(UINT32 stop)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSetCtrlStop)
	{
		ret = gstBePwmHwFunction.pfnSetCtrlStop(stop);
	}

	return ret;
}

int BE_PWM_HAL_Suspend(void)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnSuspend)
	{
		ret = gstBePwmHwFunction.pfnSuspend();
	}

	return ret;
}

int BE_PWM_HAL_Resume(void)
{
	int ret = RET_OK;

	if(gstBePwmHwFunction.pfnResume)
	{
		ret = gstBePwmHwFunction.pfnResume();
	}

	return ret;
}
