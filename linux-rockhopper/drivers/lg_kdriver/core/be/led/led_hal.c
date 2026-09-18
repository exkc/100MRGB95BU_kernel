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
 *  frc hal file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2016.05.04
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
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"
#include "be_def.h"

#include "be_kapi.h"
#include "led_hal.h"
#include "m17/be/led/be_led_hw_m17.h"
#include "o18/be/led/be_led_hw_o18.h"
#include "m19/be/led/be_led_hw_m19.h"
#include "o20/be/led/be_led_hw_o20.h"
#include "e60/be/led/be_led_hw_e60.h"
#include "o22/be/led/be_led_hw_o22.h"
#include "m23/be/led/be_led_hw_m23.h"
#include "o24/be/led/be_led_hw_o24.h"
#include "o26/be/led/be_led_hw_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct BE_LED_DRV_CHIP
{
	int 	(*pfnInitialize) (void);
	int 	(*pfnClose) (void);
	int 	(*pfnSuspend) (void);
	int 	(*pfnResume) (void);

	int	(*pfnSetLutLED) (LX_BE_LED_LUT_T *pstParams);
	int	(*pfnSetLutLED1) (void *pstParams);
	int	(*pfnGetVersionLED) (LX_BE_LED_VERSION_T *pstParams);
	int	(*pfnSetModeLED) (LX_BE_LED_MODE_T *pstParams);
	int	(*pfnControlLED) (LX_BE_LED_CONTROL_T *pstParams);
	int	(*pfnGetAplLED) (LX_BE_LED_APL_T *pstParams);
	int	(*pfnSetClippingValueLED) (UINT32 u32Param);
	int (*pfnSetSpiCtrlLED)	(LX_BE_LED_SPI_CTRL_T *pstParams);
	int (*pfnSetBplDataLED) (LX_BE_LED_BPL_DATA_T *pstParams);
	int (*pfnUpdateSensorLuxInfoLED) (UINT32 u32Param);
	int	(*pfnGetRegInfoLED) (LX_BE_LED_REG_INFO_T *pstParams);
	int	(*pfnSetUcrLED) (LX_BE_LED_UCR_PARAM_T *pstParams);
	int (*pfnGetObjectApl) (LX_BE_LED_object_apl *pstParams);
	int (*pfnSetObjectAplGain) (LX_BE_LED_object_apl_gain *pstParams);

	int	(*pfnSetLutWCG) (LX_BE_WCG_LUT_T *pstParams);
	int	(*pfnCalcFwLutSizeWCG) (LX_BE_WCG_CALC_FW_LUT_SIZE_T *pstParams);
	int	(*pfnGetFwLutWCG) (LX_BE_WCG_FW_LUT_T *pstParams);
	int	(*pfnGetVersionWCG) (LX_BE_WCG_VERSION_T *pstParams);
	int	(*pfnSetModeWCG) (LX_BE_WCG_MODE_T *pstParams);
	int	(*pfnControlWCG) (LX_BE_WCG_CONTROL_T *pstParams);

	int	(*pfnSetDpgPQ) (LX_BE_PQ_DPG_T *pstParams);
	int	(*pfnSetPccPQ) (LX_BE_PQ_PCC_T *pstParams);
	int	(*pfnSetGammaPQ) (BOOLEAN bParam);
	int	(*pfnSetDeGammaPQ) (BOOLEAN bParam);
	int	(*pfnSetPccGammaPQ) (LX_BE_PQ_PCC_GAMMA_T *pstParams);
	int	(*pfnSetPccMuxBlendPQ) (LX_BE_PQ_PCC_MUX_BLEND_T *pstParams);
	int	(*pfnSetPccParamsPQ) (LX_BE_PQ_PCC_PARAMS_T *pstParams);
	int	(*pfnSetLuminenceBoostPQ) (LX_BE_PQ_LUT_T *pstParams);
	int	(*pfnSetOledAplGainPQ) (LX_BE_PQ_LUT_T *pstParams);
	int	(*pfnSetEotfOetfLutPQ) (LX_BE_PQ_EOTF_OETF_T *pstParams);
	int (*pfnSetFrameDelayMode) (LX_BE_FRAME_DELAY_MODE_T *pstParams);
	int (*pfnSetMccData) (LX_BE_MCC_DATA_T *pstParams);
	int (*pfnSetMccLut) (LX_BE_MCC_LUT_T *pstParams);

	int	(*pfnProcHandler) (BE_LED_PROC_ID_T proc_id, struct seq_file* m, void* data);
} BE_LED_HW_FUNCTION_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
BE_LED_HW_FUNCTION_T gstBeLedHwFunction;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

int BE_LED_HAL_Init(void)
{
	int ret = RET_OK;

	memset(&gstBeLedHwFunction,0,sizeof(BE_LED_HW_FUNCTION_T));

	if (0)
	{

	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		BE_PRINT("BE LED chip revision is set to O26 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_O26_Initialize;
		gstBeLedHwFunction.pfnClose 				=		BE_LED_HW_O26_Close;
		gstBeLedHwFunction.pfnSuspend				=		BE_LED_HW_O26_Suspend;
		gstBeLedHwFunction.pfnResume				=		BE_LED_HW_O26_Resume;
		gstBeLedHwFunction.pfnSetLutLED 			=		BE_LED_HW_O26_Set_Lut;
		gstBeLedHwFunction.pfnSetLutLED1 			=		BE_LED_HW_O26_Set_Lut1;
		gstBeLedHwFunction.pfnSetModeLED			=		BE_LED_HW_O26_Set_Mode;
		gstBeLedHwFunction.pfnControlLED			=		BE_LED_HW_O26_Control;
		gstBeLedHwFunction.pfnGetAplLED 			=		BE_LED_HW_O26_Get_Apl;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		BE_LED_HW_O26_Set_ClippingValue;
		gstBeLedHwFunction.pfnSetSpiCtrlLED 		=		BE_LED_HW_O26_Set_SpiCtrl;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		BE_LED_HW_O26_Set_BplData;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		BE_LED_HW_O26_Get_RegInfo;
		gstBeLedHwFunction.pfnSetUcrLED 			=		BE_LED_HW_O26_Set_Ucr;
		gstBeLedHwFunction.pfnGetObjectApl			=		BE_LED_HW_O26_GetObjectApl;
		gstBeLedHwFunction.pfnSetObjectAplGain		=		BE_LED_HW_O26_SetObjectAplGain;
		gstBeLedHwFunction.pfnSetLutWCG 			=		BE_WCG_HW_O26_Set_Lut;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG		=		BE_WCG_HW_O26_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG			=		BE_WCG_HW_O26_Get_FWLut;
		gstBeLedHwFunction.pfnSetModeWCG			=		BE_WCG_HW_O26_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG			=		BE_WCG_HW_O26_Control;
		gstBeLedHwFunction.pfnSetPccPQ				=		BE_PQ_HW_O26_Set_Pcc;
		gstBeLedHwFunction.pfnSetPccGammaPQ 		=		BE_PQ_HW_O26_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ		=		BE_PQ_HW_O26_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ		=		BE_PQ_HW_O26_Set_PccParams;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=		BE_PQ_HW_O26_Set_LuminenceBoost;
		gstBeLedHwFunction.pfnSetOledAplGainPQ		=		BE_PQ_HW_O26_Set_OledAplGain;
		gstBeLedHwFunction.pfnProcHandler			=		BE_LED_HW_O26_ProcHandler;
		gstBeLedHwFunction.pfnSetMccData			=		BE_PQ_HW_O26_Set_MccData;
		gstBeLedHwFunction.pfnSetMccLut 			=		BE_PQ_HW_O26_Set_MccLut;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		BE_PRINT("BE LED chip revision is set to O24 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_O24_Initialize;
		gstBeLedHwFunction.pfnClose 				=		BE_LED_HW_O24_Close;
		gstBeLedHwFunction.pfnSuspend				=		BE_LED_HW_O24_Suspend;
		gstBeLedHwFunction.pfnResume				=		BE_LED_HW_O24_Resume;
		gstBeLedHwFunction.pfnSetLutLED 			=		BE_LED_HW_O24_Set_Lut;
		gstBeLedHwFunction.pfnGetVersionLED 		=		NULL;
		gstBeLedHwFunction.pfnSetModeLED			=		BE_LED_HW_O24_Set_Mode;
		gstBeLedHwFunction.pfnControlLED			=		BE_LED_HW_O24_Control;
		gstBeLedHwFunction.pfnGetAplLED 			=		BE_LED_HW_O24_Get_Apl;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		BE_LED_HW_O24_Set_ClippingValue;
		gstBeLedHwFunction.pfnSetSpiCtrlLED 		=		BE_LED_HW_O24_Set_SpiCtrl;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		BE_LED_HW_O24_Set_BplData;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED=		NULL;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		BE_LED_HW_O24_Get_RegInfo;
		gstBeLedHwFunction.pfnSetUcrLED 			=		BE_LED_HW_O24_Set_Ucr;
		gstBeLedHwFunction.pfnSetLutWCG 			=		BE_WCG_HW_O24_Set_Lut;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG		=		BE_WCG_HW_O24_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG			=		BE_WCG_HW_O24_Get_FWLut;
		gstBeLedHwFunction.pfnGetVersionWCG 		=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG			=		BE_WCG_HW_O24_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG			=		BE_WCG_HW_O24_Control;
		gstBeLedHwFunction.pfnSetDpgPQ				=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ				=		BE_PQ_HW_O24_Set_Pcc;
		gstBeLedHwFunction.pfnSetGammaPQ			=		NULL;
		gstBeLedHwFunction.pfnSetDeGammaPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccGammaPQ 		=		BE_PQ_HW_O24_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ		=		BE_PQ_HW_O24_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ		=		BE_PQ_HW_O24_Set_PccParams;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=		BE_PQ_HW_O24_Set_LuminenceBoost;
		gstBeLedHwFunction.pfnSetOledAplGainPQ		=		BE_PQ_HW_O24_Set_OledAplGain;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ 		=		NULL;
		gstBeLedHwFunction.pfnSetFrameDelayMode		=		BE_PQ_HW_O24_Set_FrameDelayMode;
		gstBeLedHwFunction.pfnProcHandler			=		NULL;
		gstBeLedHwFunction.pfnSetMccData			=		NULL;
		gstBeLedHwFunction.pfnSetMccLut 			=		NULL;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE LED chip revision is set to M23 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_M23_Initialize;
		gstBeLedHwFunction.pfnClose 			=		BE_LED_HW_M23_Close;
		gstBeLedHwFunction.pfnSuspend			=		BE_LED_HW_M23_Suspend;
		gstBeLedHwFunction.pfnResume			=		BE_LED_HW_M23_Resume;

		gstBeLedHwFunction.pfnSetLutLED 		=		BE_LED_HW_M23_Set_Lut;
		gstBeLedHwFunction.pfnGetVersionLED 	=		NULL;
		gstBeLedHwFunction.pfnSetModeLED		=		BE_LED_HW_M23_Set_Mode;
		gstBeLedHwFunction.pfnControlLED			=		BE_LED_HW_M23_Control;
		gstBeLedHwFunction.pfnGetAplLED 			=		BE_LED_HW_M23_Get_Apl;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		BE_LED_HW_M23_Set_ClippingValue;
		gstBeLedHwFunction.pfnSetSpiCtrlLED 		=		BE_LED_HW_M23_Set_SpiCtrl;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		BE_LED_HW_M23_Set_BplData;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		NULL;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		BE_LED_HW_M23_Get_RegInfo;
		gstBeLedHwFunction.pfnSetUcrLED 		=		NULL;

		gstBeLedHwFunction.pfnSetLutWCG 		=		BE_WCG_HW_M23_Set_Lut;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG	=		BE_WCG_HW_M23_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG		=		BE_WCG_HW_M23_Get_FWLut;
		gstBeLedHwFunction.pfnGetVersionWCG 	=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG		=		BE_WCG_HW_M23_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG		=		BE_WCG_HW_M23_Control;

		gstBeLedHwFunction.pfnSetDpgPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ			=		BE_PQ_HW_M23_Set_Pcc;
		gstBeLedHwFunction.pfnSetGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetDeGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetPccGammaPQ 	=		BE_PQ_HW_M23_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		BE_PQ_HW_M23_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ	=		BE_PQ_HW_M23_Set_PccParams;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=	NULL;
		gstBeLedHwFunction.pfnSetOledAplGainPQ	=		NULL;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ	=		NULL;
		gstBeLedHwFunction.pfnSetFrameDelayMode =		NULL;
		gstBeLedHwFunction.pfnSetMccData 		=		NULL;
		gstBeLedHwFunction.pfnSetMccLut			=		NULL;
		gstBeLedHwFunction.pfnProcHandler		=		NULL;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		BE_PRINT("BE LED chip revision is set to O22 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_O22_Initialize;
		gstBeLedHwFunction.pfnClose 			=		BE_LED_HW_O22_Close;
		gstBeLedHwFunction.pfnSuspend			=		BE_LED_HW_O22_Suspend;
		gstBeLedHwFunction.pfnResume			=		BE_LED_HW_O22_Resume;

		gstBeLedHwFunction.pfnSetLutLED 		=		BE_LED_HW_O22_Set_Lut;
		gstBeLedHwFunction.pfnGetVersionLED 	=		NULL;
		gstBeLedHwFunction.pfnSetModeLED		=		BE_LED_HW_O22_Set_Mode;
		gstBeLedHwFunction.pfnControlLED			=		BE_LED_HW_O22_Control;
		gstBeLedHwFunction.pfnGetAplLED 			=		BE_LED_HW_O22_Get_Apl;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		BE_LED_HW_O22_Set_ClippingValue;
		gstBeLedHwFunction.pfnSetSpiCtrlLED 		=		BE_LED_HW_O22_Set_SpiCtrl;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		BE_LED_HW_O22_Set_BplData;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		NULL;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		BE_LED_HW_O22_Get_RegInfo;
		gstBeLedHwFunction.pfnSetUcrLED 		=		BE_LED_HW_O22_Set_Ucr;

		gstBeLedHwFunction.pfnSetLutWCG 		=		BE_WCG_HW_O22_Set_Lut;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG	=		BE_WCG_HW_O22_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG		=		BE_WCG_HW_O22_Get_FWLut;
		gstBeLedHwFunction.pfnGetVersionWCG 	=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG		=		BE_WCG_HW_O22_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG		=		BE_WCG_HW_O22_Control;

		gstBeLedHwFunction.pfnSetDpgPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ			=		BE_PQ_HW_O22_Set_Pcc;
		gstBeLedHwFunction.pfnSetGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetDeGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetPccGammaPQ 	=		BE_PQ_HW_O22_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		BE_PQ_HW_O22_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ	=		BE_PQ_HW_O22_Set_PccParams;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=	BE_PQ_HW_O22_Set_LuminenceBoost;
		gstBeLedHwFunction.pfnSetOledAplGainPQ	=		BE_PQ_HW_O22_Set_OledAplGain;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ 	=		NULL;
		gstBeLedHwFunction.pfnSetFrameDelayMode =		NULL;
		gstBeLedHwFunction.pfnSetMccData 		=		NULL;
		gstBeLedHwFunction.pfnSetMccLut			=		NULL;
		gstBeLedHwFunction.pfnProcHandler		=		NULL;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE LED chip revision is set to E60 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_E60_Initialize;
		gstBeLedHwFunction.pfnClose 			=		BE_LED_HW_E60_Close;
		gstBeLedHwFunction.pfnSuspend			=		BE_LED_HW_E60_Suspend;
		gstBeLedHwFunction.pfnResume			=		BE_LED_HW_E60_Resume;

		gstBeLedHwFunction.pfnSetLutLED 		=		BE_LED_HW_E60_Set_Lut;
		gstBeLedHwFunction.pfnGetVersionLED 	=		NULL;
		gstBeLedHwFunction.pfnSetModeLED		=		BE_LED_HW_E60_Set_Mode;
		gstBeLedHwFunction.pfnControlLED			=		BE_LED_HW_E60_Control;
		gstBeLedHwFunction.pfnGetAplLED 			=		BE_LED_HW_E60_Get_Apl;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		BE_LED_HW_E60_Set_ClippingValue;
		gstBeLedHwFunction.pfnSetSpiCtrlLED 		=		BE_LED_HW_E60_Set_SpiCtrl;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		BE_LED_HW_E60_Set_BplData;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		NULL;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		BE_LED_HW_E60_Get_RegInfo;
		gstBeLedHwFunction.pfnSetUcrLED			= 		NULL;

		gstBeLedHwFunction.pfnSetLutWCG 		=		BE_WCG_HW_E60_Set_Lut;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG	=		BE_WCG_HW_E60_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG		=		BE_WCG_HW_E60_Get_FWLut;
		gstBeLedHwFunction.pfnGetVersionWCG 	=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG		=		BE_WCG_HW_E60_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG		=		BE_WCG_HW_E60_Control;

		gstBeLedHwFunction.pfnSetDpgPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ			=		BE_PQ_HW_E60_Set_Pcc;
		gstBeLedHwFunction.pfnSetGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetDeGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetPccGammaPQ 	=		BE_PQ_HW_E60_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		BE_PQ_HW_E60_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ	=		BE_PQ_HW_E60_Set_PccParams;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=	BE_PQ_HW_E60_Set_LuminenceBoost;
		gstBeLedHwFunction.pfnSetOledAplGainPQ	=		NULL;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ 	=		NULL;
		gstBeLedHwFunction.pfnSetFrameDelayMode =		NULL;
		gstBeLedHwFunction.pfnSetMccData 		=		NULL;
		gstBeLedHwFunction.pfnSetMccLut			=		NULL;
		gstBeLedHwFunction.pfnProcHandler		=		NULL;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE LED chip revision is set to O20 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_O20_Initialize;
		gstBeLedHwFunction.pfnClose 			=		BE_LED_HW_O20_Close;
		gstBeLedHwFunction.pfnSuspend			=		BE_LED_HW_O20_Suspend;
		gstBeLedHwFunction.pfnResume			=		BE_LED_HW_O20_Resume;

		gstBeLedHwFunction.pfnSetLutLED 		=		BE_LED_HW_O20_Set_Lut;
		gstBeLedHwFunction.pfnGetVersionLED 	=		NULL;
		gstBeLedHwFunction.pfnSetModeLED		=		BE_LED_HW_O20_Set_Mode;
		gstBeLedHwFunction.pfnControlLED			=		BE_LED_HW_O20_Control;
		gstBeLedHwFunction.pfnGetAplLED 			=		BE_LED_HW_O20_Get_Apl;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		BE_LED_HW_O20_Set_ClippingValue;
		gstBeLedHwFunction.pfnSetSpiCtrlLED 		=		BE_LED_HW_O20_Set_SpiCtrl;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		NULL;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		NULL;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		BE_LED_HW_O20_Get_RegInfo;
		gstBeLedHwFunction.pfnSetUcrLED			= 		BE_LED_HW_O20_Set_Ucr;

		gstBeLedHwFunction.pfnSetLutWCG 		=		BE_WCG_HW_O20_Set_Lut;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG	=		BE_WCG_HW_O20_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG		=		BE_WCG_HW_O20_Get_FWLut;
		gstBeLedHwFunction.pfnGetVersionWCG 	=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG		=		BE_WCG_HW_O20_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG		=		BE_WCG_HW_O20_Control;

		gstBeLedHwFunction.pfnSetDpgPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ			=		BE_PQ_HW_O20_Set_Pcc;
		gstBeLedHwFunction.pfnSetGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetDeGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetPccGammaPQ 	=		BE_PQ_HW_O20_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		BE_PQ_HW_O20_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ	=		BE_PQ_HW_O20_Set_PccParams;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=	BE_PQ_HW_O20_Set_LuminenceBoost;
		gstBeLedHwFunction.pfnSetOledAplGainPQ	=		NULL;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ 	=		BE_PQ_HW_O20_Set_Eotf_Oetf_Lut;
		gstBeLedHwFunction.pfnSetFrameDelayMode =		NULL;
		gstBeLedHwFunction.pfnSetMccData 		=		NULL;
		gstBeLedHwFunction.pfnSetMccLut			=		NULL;
		gstBeLedHwFunction.pfnProcHandler		=		NULL;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		BE_PRINT("BE LED chip revision is set to M19 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_M19_Initialize;
		gstBeLedHwFunction.pfnClose 			=		BE_LED_HW_M19_Close;
		gstBeLedHwFunction.pfnSuspend			=		NULL;
		gstBeLedHwFunction.pfnResume			=		BE_LED_HW_M19_Resume;

		gstBeLedHwFunction.pfnSetLutLED			=		BE_LED_HW_M19_Set_Lut;
		gstBeLedHwFunction.pfnGetVersionLED 	=		NULL;
		gstBeLedHwFunction.pfnSetModeLED		=		BE_LED_HW_M19_Set_Mode;
		gstBeLedHwFunction.pfnControlLED			=		BE_LED_HW_M19_Control;
		gstBeLedHwFunction.pfnGetAplLED 			=		BE_LED_HW_M19_Get_Apl;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		BE_LED_HW_M19_Set_ClippingValue;
		gstBeLedHwFunction.pfnSetSpiCtrlLED		=		BE_LED_HW_M19_Set_SpiCtrl;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		NULL;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		BE_LED_HW_M19_Update_SensorLuxInfo;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		BE_LED_HW_M19_Get_RegInfo;
		gstBeLedHwFunction.pfnSetUcrLED			= 		NULL;

		gstBeLedHwFunction.pfnSetLutWCG			=		BE_WCG_HW_M19_Set_Lut;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG	=		BE_WCG_HW_M19_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG		=		BE_WCG_HW_M19_Get_FWLut;
		gstBeLedHwFunction.pfnGetVersionWCG 	=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG		=		BE_WCG_HW_M19_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG		=		BE_WCG_HW_M19_Control;

		gstBeLedHwFunction.pfnSetDpgPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ			=		BE_PQ_HW_M19_Set_Pcc;
		gstBeLedHwFunction.pfnSetGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetDeGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetPccGammaPQ		=		BE_PQ_HW_M19_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		BE_PQ_HW_M19_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ	=		NULL;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=		NULL;
		gstBeLedHwFunction.pfnSetOledAplGainPQ	=		NULL;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ 	=		NULL;
		gstBeLedHwFunction.pfnSetFrameDelayMode =		NULL;
		gstBeLedHwFunction.pfnSetMccData 		=		NULL;
		gstBeLedHwFunction.pfnSetMccLut			=		NULL;
		gstBeLedHwFunction.pfnProcHandler		=		BE_LED_HW_M19_ProcHandler;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		BE_PRINT("BE LED chip revision is set to O18 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_O18_Initialize;
		gstBeLedHwFunction.pfnClose 			=		BE_LED_HW_O18_Close;
		gstBeLedHwFunction.pfnSuspend			=		NULL;
		gstBeLedHwFunction.pfnResume			=		BE_LED_HW_O18_Resume;

		gstBeLedHwFunction.pfnSetLutLED			=		NULL;
		gstBeLedHwFunction.pfnGetVersionLED 	=		NULL;
		gstBeLedHwFunction.pfnSetModeLED		=		NULL;
		gstBeLedHwFunction.pfnControlLED			=		NULL;
		gstBeLedHwFunction.pfnGetAplLED 			=		NULL;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		NULL;
		gstBeLedHwFunction.pfnSetSpiCtrlLED			=		NULL;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		NULL;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		NULL;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		NULL;
		gstBeLedHwFunction.pfnSetUcrLED			= 		NULL;

		gstBeLedHwFunction.pfnSetLutWCG			=		NULL;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG	=		BE_WCG_HW_O18_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG		=		BE_WCG_HW_O18_Get_FWLut;
		gstBeLedHwFunction.pfnGetVersionWCG 	=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG		=		BE_WCG_HW_O18_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG		=		BE_WCG_HW_O18_Control;

		gstBeLedHwFunction.pfnSetDpgPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ			=		BE_PQ_HW_O18_Set_Pcc;
		gstBeLedHwFunction.pfnSetGammaPQ		=		BE_PQ_HW_O18_Set_Gamma;
		gstBeLedHwFunction.pfnSetDeGammaPQ		=		BE_PQ_HW_O18_Set_DeGamma;
		gstBeLedHwFunction.pfnSetPccGammaPQ		=		BE_PQ_HW_O18_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		BE_PQ_HW_O18_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ	=		NULL;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=		BE_PQ_HW_O18_Set_LuminenceBoost;
		gstBeLedHwFunction.pfnSetOledAplGainPQ	=		NULL;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ 	=		NULL;
		gstBeLedHwFunction.pfnSetFrameDelayMode =		NULL;
		gstBeLedHwFunction.pfnSetMccData 		=		NULL;
		gstBeLedHwFunction.pfnSetMccLut			=		NULL;
		gstBeLedHwFunction.pfnProcHandler		=		NULL;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		BE_PRINT("BE LED chip revision is set to M17 A0\n");
		gstBeLedHwFunction.pfnInitialize			=		BE_LED_HW_M17_Initialize;
		gstBeLedHwFunction.pfnClose 			=		BE_LED_HW_M17_Close;
		gstBeLedHwFunction.pfnSuspend			=		NULL;
		gstBeLedHwFunction.pfnResume			=		BE_LED_HW_M17_Resume;

		gstBeLedHwFunction.pfnSetLutLED			=		NULL;
		gstBeLedHwFunction.pfnGetVersionLED 	=		NULL;
		gstBeLedHwFunction.pfnSetModeLED		=		BE_LED_HW_M17_Set_Mode;
		gstBeLedHwFunction.pfnControlLED			=		BE_LED_HW_M17_Control;
		gstBeLedHwFunction.pfnGetAplLED 			=		BE_LED_HW_M17_Get_Apl;
		gstBeLedHwFunction.pfnSetClippingValueLED	=		BE_LED_HW_M17_Set_ClippingValue;
		gstBeLedHwFunction.pfnSetSpiCtrlLED			=		NULL;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		NULL;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		NULL;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		BE_LED_HW_M17_Get_RegInfo;
		gstBeLedHwFunction.pfnSetUcrLED			= 		NULL;

		gstBeLedHwFunction.pfnSetLutWCG			=		NULL;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG	=		BE_WCG_HW_M17_Calculate_FWLutSize;
		gstBeLedHwFunction.pfnGetFwLutWCG		=		BE_WCG_HW_M17_Get_FWLut;
		gstBeLedHwFunction.pfnGetVersionWCG 	=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG		=		BE_WCG_HW_M17_Set_Mode;
		gstBeLedHwFunction.pfnControlWCG		=		BE_WCG_HW_M17_Control;

		gstBeLedHwFunction.pfnSetDpgPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ			=		BE_PQ_HW_M17_Set_Pcc;
		gstBeLedHwFunction.pfnSetGammaPQ		=		BE_PQ_HW_M17_Set_Gamma;
		gstBeLedHwFunction.pfnSetDeGammaPQ		=		BE_PQ_HW_M17_Set_DeGamma;
		gstBeLedHwFunction.pfnSetPccGammaPQ		=		BE_PQ_HW_M17_Set_PccGamma;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		BE_PQ_HW_M17_Set_PccMuxBlend;
		gstBeLedHwFunction.pfnSetPccParamsPQ	=		NULL;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=		NULL;
		gstBeLedHwFunction.pfnSetOledAplGainPQ	=		NULL;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ 	=		NULL;
		gstBeLedHwFunction.pfnSetFrameDelayMode =		NULL;
		gstBeLedHwFunction.pfnSetMccData 		=		NULL;
		gstBeLedHwFunction.pfnSetMccLut			=		NULL;
		gstBeLedHwFunction.pfnProcHandler		=		BE_LED_HW_M17_ProcHandler;
	}
#endif
	else
	{
		BE_ERROR("BE LED ERROR! Unknown chip revision at BE LED module\n");
		gstBeLedHwFunction.pfnInitialize		 	=		NULL;
		gstBeLedHwFunction.pfnClose				=		NULL;
		gstBeLedHwFunction.pfnSuspend			=		NULL;
		gstBeLedHwFunction.pfnResume			=		NULL;

		gstBeLedHwFunction.pfnSetLutLED			=		NULL;
		gstBeLedHwFunction.pfnGetVersionLED		=		NULL;
		gstBeLedHwFunction.pfnSetModeLED		=		NULL;
		gstBeLedHwFunction.pfnControlLED 			=		NULL;
		gstBeLedHwFunction.pfnGetAplLED 			=		NULL;
		gstBeLedHwFunction.pfnSetClippingValueLED 	=		NULL;
		gstBeLedHwFunction.pfnSetSpiCtrlLED			=		NULL;
		gstBeLedHwFunction.pfnSetBplDataLED 		=		NULL;
		gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		NULL;
		gstBeLedHwFunction.pfnGetRegInfoLED 		=		NULL;
		gstBeLedHwFunction.pfnSetUcrLED			= 		NULL;

		gstBeLedHwFunction.pfnSetLutWCG			=		NULL;
		gstBeLedHwFunction.pfnCalcFwLutSizeWCG 	=		NULL;
		gstBeLedHwFunction.pfnGetFwLutWCG 		=		NULL;
		gstBeLedHwFunction.pfnGetVersionWCG		=		NULL;
		gstBeLedHwFunction.pfnSetModeWCG	 	=		NULL;
		gstBeLedHwFunction.pfnControlWCG	 	=		NULL;

		gstBeLedHwFunction.pfnSetDpgPQ			=		NULL;
		gstBeLedHwFunction.pfnSetPccPQ			=		NULL;
		gstBeLedHwFunction.pfnSetGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetDeGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetPccGammaPQ		=		NULL;
		gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		NULL;
		gstBeLedHwFunction.pfnSetPccParamsPQ	=		NULL;
		gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=		NULL;
		gstBeLedHwFunction.pfnSetOledAplGainPQ	=		NULL;
		gstBeLedHwFunction.pfnSetEotfOetfLutPQ 	=		NULL;
		gstBeLedHwFunction.pfnSetFrameDelayMode =		NULL;
		gstBeLedHwFunction.pfnSetMccData 		=		NULL;
		gstBeLedHwFunction.pfnSetMccLut			=		NULL;
		gstBeLedHwFunction.pfnProcHandler		=		NULL;

		return RET_ERROR;
	}

	if (gstBeLedHwFunction.pfnInitialize)
	{
		ret = gstBeLedHwFunction.pfnInitialize();
	}

	return ret;
}

int BE_LED_HAL_Close(void)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnClose)
	{
		ret = gstBeLedHwFunction.pfnClose();
	}

	gstBeLedHwFunction.pfnInitialize		 	=		NULL;
	gstBeLedHwFunction.pfnClose				=		NULL;
	gstBeLedHwFunction.pfnSuspend			=		NULL;
	gstBeLedHwFunction.pfnResume			=		NULL;

	gstBeLedHwFunction.pfnSetLutLED			=		NULL;
	gstBeLedHwFunction.pfnGetVersionLED		=		NULL;
	gstBeLedHwFunction.pfnSetModeLED		=		NULL;
	gstBeLedHwFunction.pfnControlLED 			=		NULL;
	gstBeLedHwFunction.pfnGetAplLED 			=		NULL;
	gstBeLedHwFunction.pfnSetClippingValueLED 	=		NULL;
	gstBeLedHwFunction.pfnSetSpiCtrlLED			=		NULL;
	gstBeLedHwFunction.pfnSetBplDataLED 		=		NULL;
	gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED =		NULL;
	gstBeLedHwFunction.pfnGetRegInfoLED 		=		NULL;
	gstBeLedHwFunction.pfnSetUcrLED			= 		NULL;

	gstBeLedHwFunction.pfnSetLutWCG			=		NULL;
	gstBeLedHwFunction.pfnCalcFwLutSizeWCG 	=		NULL;
	gstBeLedHwFunction.pfnGetFwLutWCG 		=		NULL;
	gstBeLedHwFunction.pfnGetVersionWCG		=		NULL;
	gstBeLedHwFunction.pfnSetModeWCG	 	=		NULL;
	gstBeLedHwFunction.pfnControlWCG	 	=		NULL;

	gstBeLedHwFunction.pfnSetDpgPQ 			=		NULL;
	gstBeLedHwFunction.pfnSetPccPQ 			=		NULL;
	gstBeLedHwFunction.pfnSetGammaPQ		=		NULL;
	gstBeLedHwFunction.pfnSetDeGammaPQ		=		NULL;
	gstBeLedHwFunction.pfnSetPccGammaPQ		=		NULL;
	gstBeLedHwFunction.pfnSetPccMuxBlendPQ	=		NULL;
	gstBeLedHwFunction.pfnSetLuminenceBoostPQ	=		NULL;
	gstBeLedHwFunction.pfnSetMccData		=		NULL;
	gstBeLedHwFunction.pfnSetMccLut 		=		NULL;
	gstBeLedHwFunction.pfnProcHandler		=		NULL;

	return ret;
}

int BE_LED_HAL_Suspend(void)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSuspend == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSuspend();
	}

	return ret;
}

int BE_LED_HAL_Resume(void)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnResume == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnResume();
	}

	return ret;
}

int BE_LED_HAL_Set_Lut(LX_BE_LED_LUT_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetLutLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetLutLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Set_Lut1(void *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetLutLED1 == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetLutLED1(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Get_Version(LX_BE_LED_VERSION_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnGetVersionLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnGetVersionLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Set_Mode(LX_BE_LED_MODE_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetModeLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetModeLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Control(LX_BE_LED_CONTROL_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnControlLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnControlLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Get_Apl(LX_BE_LED_APL_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnGetAplLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnGetAplLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Set_ClippingValue(UINT32 u32Param)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetClippingValueLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetClippingValueLED(u32Param);
	}

	return ret;
}

int BE_LED_HAL_Set_SpiCtrl(LX_BE_LED_SPI_CTRL_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetSpiCtrlLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetSpiCtrlLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Set_BplData(LX_BE_LED_BPL_DATA_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetBplDataLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetBplDataLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Update_SensorLuxInfo(UINT32 u32Param)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnUpdateSensorLuxInfoLED(u32Param);
	}

	return ret;
}

int BE_LED_HAL_Get_RegInfo(LX_BE_LED_REG_INFO_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnGetRegInfoLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnGetRegInfoLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_Set_Ucr(LX_BE_LED_UCR_PARAM_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetUcrLED == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetUcrLED(pstParams);
	}

	return ret;
}

int BE_LED_HAL_GetObjectApl(LX_BE_LED_object_apl *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnGetObjectApl) {
		ret  = gstBeLedHwFunction.pfnGetObjectApl(pstParams);
	}

	return ret;
}

int BE_LED_HAL_SetObjectAplGain(LX_BE_LED_object_apl_gain *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetObjectAplGain) {
		ret  = gstBeLedHwFunction.pfnSetObjectAplGain(pstParams);
	}

	return ret;
}

int BE_WCG_HAL_Set_Lut(LX_BE_WCG_LUT_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetLutWCG == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetLutWCG(pstParams);
	}

	return ret;
}

int BE_WCG_HAL_Calculate_FWLutSize(LX_BE_WCG_CALC_FW_LUT_SIZE_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnCalcFwLutSizeWCG == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnCalcFwLutSizeWCG(pstParams);
	}

	return ret;
}

int BE_WCG_HAL_Get_FWLut(LX_BE_WCG_FW_LUT_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnGetFwLutWCG == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnGetFwLutWCG(pstParams);
	}

	return ret;
}

int BE_WCG_HAL_Get_Version(LX_BE_WCG_VERSION_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnGetVersionWCG == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnGetVersionWCG(pstParams);
	}

	return ret;
}

int BE_WCG_HAL_Set_Mode(LX_BE_WCG_MODE_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetModeWCG == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetModeWCG(pstParams);
	}

	return ret;
}

int BE_WCG_HAL_Control(LX_BE_WCG_CONTROL_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnControlWCG == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnControlWCG(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_Dpg(LX_BE_PQ_DPG_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetDpgPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetDpgPQ(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_Pcc(LX_BE_PQ_PCC_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetPccPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetPccPQ(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_Gamma(BOOLEAN bParam)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetGammaPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetGammaPQ(bParam);
	}

	return ret;
}

int BE_PQ_HAL_Set_DeGamma(BOOLEAN bParam)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetDeGammaPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetDeGammaPQ(bParam);
	}

	return ret;
}

int BE_PQ_HAL_Set_PccGamma(LX_BE_PQ_PCC_GAMMA_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetPccGammaPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetPccGammaPQ(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_PccMuxBlend(LX_BE_PQ_PCC_MUX_BLEND_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetPccMuxBlendPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetPccMuxBlendPQ(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_PccParams(LX_BE_PQ_PCC_PARAMS_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetPccParamsPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetPccParamsPQ(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_LuminenceBoost(LX_BE_PQ_LUT_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetLuminenceBoostPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetLuminenceBoostPQ(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_Oled_Apl_Gain(LX_BE_PQ_LUT_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetOledAplGainPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetOledAplGainPQ(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_Eotf_Oetf_Lut(LX_BE_PQ_EOTF_OETF_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetEotfOetfLutPQ == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetEotfOetfLutPQ(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_Frame_Delay_Mode(LX_BE_FRAME_DELAY_MODE_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetFrameDelayMode == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetFrameDelayMode(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_Mcc_Data(LX_BE_MCC_DATA_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetMccData == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetMccData(pstParams);
	}

	return ret;
}

int BE_PQ_HAL_Set_Mcc_Lut(LX_BE_MCC_LUT_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnSetMccLut == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_LED_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_LED_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeLedHwFunction.pfnSetMccLut(pstParams);
	}

	return ret;
}

int BE_LED_HAL_ProcHandler(BE_LED_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int ret = RET_OK;

	if (gstBeLedHwFunction.pfnProcHandler == NULL)
	{
		ret = RET_ERROR;
	}
	else
	{
		ret = gstBeLedHwFunction.pfnProcHandler(proc_id, m, data);
	}

	return ret;
}

