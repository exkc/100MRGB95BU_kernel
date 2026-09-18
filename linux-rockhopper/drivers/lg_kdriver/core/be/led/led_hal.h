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
 *  led hal header file for be device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.16
 *  note		Additional information.
 *
 *  @addtogroup be
 *	@{
 */

#ifndef _LED_HAL_H_
#define _LED_HAL_H_

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
enum
{
    BE_LED_HAL_PROC_ID_DETAIL_INFO,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int BE_LED_HAL_Init(void);
int BE_LED_HAL_Close(void);
int BE_LED_HAL_Suspend(void);
int BE_LED_HAL_Resume(void);

int BE_LED_HAL_Set_Lut(LX_BE_LED_LUT_T *pstParams);
int BE_LED_HAL_Set_Lut1(void *pstParams);
int BE_LED_HAL_Get_Version(LX_BE_LED_VERSION_T *pstParams);
int BE_LED_HAL_Set_Mode(LX_BE_LED_MODE_T *pstParams);
int BE_LED_HAL_Control(LX_BE_LED_CONTROL_T *pstParams);
int BE_LED_HAL_Get_Apl(LX_BE_LED_APL_T *pstParams);
int BE_LED_HAL_Set_ClippingValue(UINT32 u32Param);
int BE_LED_HAL_Set_SpiCtrl(LX_BE_LED_SPI_CTRL_T *pstParams);
int BE_LED_HAL_Set_BplData(LX_BE_LED_BPL_DATA_T *pstParams);
int BE_LED_HAL_Update_SensorLuxInfo(UINT32 u32Param);
int BE_LED_HAL_Get_RegInfo(LX_BE_LED_REG_INFO_T *pstParams);
int BE_LED_HAL_Set_Ucr(LX_BE_LED_UCR_PARAM_T *pstParams);
int BE_LED_HAL_GetObjectApl(LX_BE_LED_object_apl *pstParams);
int BE_LED_HAL_SetObjectAplGain(LX_BE_LED_object_apl_gain *pstParams);

int BE_WCG_HAL_Set_Lut(LX_BE_WCG_LUT_T *pstParams);
int BE_WCG_HAL_Calculate_FWLutSize(LX_BE_WCG_CALC_FW_LUT_SIZE_T *pstParams);
int BE_WCG_HAL_Get_FWLut(LX_BE_WCG_FW_LUT_T *pstParams);
int BE_WCG_HAL_Get_Version(LX_BE_WCG_VERSION_T *pstParams);
int BE_WCG_HAL_Set_Mode(LX_BE_WCG_MODE_T *pstParams);
int BE_WCG_HAL_Control(LX_BE_WCG_CONTROL_T *pstParams);

int BE_PQ_HAL_Set_Dpg(LX_BE_PQ_DPG_T *pstParams);
int BE_PQ_HAL_Set_Pcc(LX_BE_PQ_PCC_T *pstParams);
int BE_PQ_HAL_Set_Gamma(BOOLEAN bParam);
int BE_PQ_HAL_Set_DeGamma(BOOLEAN bParam);
int BE_PQ_HAL_Set_PccGamma(LX_BE_PQ_PCC_GAMMA_T *pstParams);
int BE_PQ_HAL_Set_PccMuxBlend(LX_BE_PQ_PCC_MUX_BLEND_T *pstParams);
int BE_PQ_HAL_Set_PccParams(LX_BE_PQ_PCC_PARAMS_T *pstParams);
int BE_PQ_HAL_Set_LuminenceBoost(LX_BE_PQ_LUT_T *pstParams);
int BE_PQ_HAL_Set_Oled_Apl_Gain(LX_BE_PQ_LUT_T *pstParams);
int BE_PQ_HAL_Set_Eotf_Oetf_Lut(LX_BE_PQ_EOTF_OETF_T *pstParams);
int BE_PQ_HAL_Set_Frame_Delay_Mode(LX_BE_FRAME_DELAY_MODE_T *pstParams);
int BE_PQ_HAL_Set_Mcc_Data(LX_BE_MCC_DATA_T *pstParams);
int BE_PQ_HAL_Set_Mcc_Lut(LX_BE_MCC_LUT_T *pstParams);

int BE_LED_HAL_ProcHandler(BE_LED_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _LED_HAL_H_ */

/** @} */
