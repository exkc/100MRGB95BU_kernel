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
 *  PWM reg header file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _BE_PWM_HW_M17_H_
#define _BE_PWM_HW_M17_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "be_kapi.h"

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
int BE_PWM_HW_M17_Init(void);
int BE_PWM_HW_M17_SetPwmControl(BE_PWM_CTRL_T *pstParams);
int BE_PWM_HW_M17_SetPwmAdaptFreqControl(BE_PWM_ADAPT_FREQ_CTRL_T *pstParams);
int BE_PWM_HW_M17_SetPwmFrequency(BE_PWM_FREQ_T *pstParams);
int BE_PWM_HW_M17_SetPwmDutyCycle(BE_PWM_DUTY_T *pstParams);
int BE_PWM_HW_M17_SetPwmDutyRatio(BE_PWM_DUTY_RATIO_T *pstParams);
int BE_PWM_HW_M17_SetPwmParams(LX_BE_PWM_PARAMS_T *pstParams);
int BE_PWM_HW_M17_GetPwmInfo(BE_EXTERNAL_PWM_T *pstParams);

int BE_PWM_HW_M17_SetPwmSync(BE_PWM_FREQ_T *pstParams);
int BE_PWM_HW_M17_ProcHandler(BE_PWM_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _BE_PWM_HW_M17_H_ */

/** @} */



