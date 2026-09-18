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

/*****************************************************************************
**
**  Name:demod_drv_O26.c
**
**  Description:    ABB/GBB point functions interface.
**
**  Functions
**  Implemented:   LX_DEMOD_CFG_T*   DEMOD_O26_GetCfg
**                 void	DEMOD_O26_InitHAL
**
**  References:
**
**  Exports:
**
**  Dependencies:   demod_impl.h for system configuration data.
**
**
**  Revision History:
**
**     Date        Author          Description
**  -------------------------------------------------------------------------
**   30-12-2009  Jeongpil Yun    Initial draft.
**   31-07-2013   Jeongpil Yun
**
*****************************************************************************/



#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>			/**< printk() */
#include <linux/slab.h>			 	/**< kmalloc() */
#include <linux/fs.h> 				/**< everything\ldots{} */
#include <linux/types.h>		 	/**< size_t */
#include <linux/fcntl.h>			/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>			/**< For request_region, check_region etc */
#include <asm/io.h>					/**< For ioremap_nocache */
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

#include "demod_impl.h"

#include "demod_common_o26.h"
#include "demod_dvb_o26.h"
#include "demod_vqi_o26.h"
#include "demod_sat_o26.h"
#include "demod_dtmb_o26.h"
#include "demod_ipc_o26.h"
#include "demod_util_o26.h"
#include "demod_api_o26.h"
#include "demod_fw_o26.h"

const LX_DEMOD_CFG_T*   DEMOD_O26_GetCfg(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
void DEMOD_O26_InitHAL (DEMOD_HAL_T * hal);


static const DEMOD_HAL_T g_demod_hal_o26 =
{
	.GetCfg					= DEMOD_O26_GetCfg,

/***************************************************************************************
* DVBT/ DVBC/ VSB/ QAM/ ISDBT  common  function
****************************************************************************************/

	.ResetHW				= DEMOD_O26_ResetHW,
	.SetI2C 				= NULL,	// DEMOD_O26_SetI2C,
	.SetInclk				= NULL, // DEMOD_O26_SetInclk
	.AdcInit				= DEMOD_O26_AdcInit,
	.OperModeReset				= DEMOD_O26_OperModeReset,
	.SetPll					= NULL,
	.SetADC					= NULL,
	.SAT_DiSeqContol			= NULL, // not used after m17
	.Get_Id 				= NULL, // DEMOD_O26_Get_Id
	.RepeaterEnable 			= DEMOD_O26_RepeaterEnable,
	.SoftwareReset				= DEMOD_O26_SoftwareReset,
	.Serial_Control 			= NULL,	// not used after m17
	.Power_Save 				= DEMOD_O26_Power_Save,
	.APB_AccessControl			= DEMOD_O26_APB_Access,
	.StdOperModeContrl			= DEMOD_O26_StdOperModeContrl,
	.NeverlockScan				= DEMOD_O26_NeverlockScan,
	.TPOutCLKEnable 			= DEMOD_O26_TPOutEnable,
	.Set_IF_Frq 				= DEMOD_O26_Set_IF_Frq,
	.Set_AGCPolarity			= DEMOD_O26_Set_AGCPolarity,
	.Set_SpectrumCtrl			= NULL,	// not used after m17
	.Get_SpectrumStatus 			= NULL,	// DEMOD_O26_Get_SpectrumStatus
	.Get_IFAGC				= DEMOD_O26_Get_IFAGC,
	.Get_OperMode				= DEMOD_O26_Get_OperMode,
	.Get_NeverLockStatus			= DEMOD_O26_Get_NeverLockStatus,
	.Get_CarrierFreqOffset			= DEMOD_O26_Get_CarrierFreqOffset,
	.Get_TPIFStatus 			= NULL,	// not used after m17, just return true
	.Get_VABER				= DEMOD_O26_Get_VABER,
	.Get_Packet_Error			= DEMOD_O26_Get_Packet_Error,
	.Get_BandWidthMode			= DEMOD_O26_Get_BandWidthMode,
	.Get_QAMMode				= DEMOD_O26_Get_QAMMode,
	.Get_MseInfo				= DEMOD_O26_Get_MseInfo,
	.Get_Lock				= DEMOD_O26_Get_Lock,
	.Get_SysLockTime			= NULL,	// not used after m17
	.Get_FecLockTime			= NULL,	// not used after m17
	.Set_Frame_resynchronizaiton		= NULL,	// not used after m17
	.Get_I2C_Handle				= DEMOD_O26_Get_I2C_Handle,
	.FW_Initialize				= DEMOD_O26_FW_Initialize,
	.SAT_FW_Initialize			= DEMOD_O26_SAT_FW_Initialize,
	.ALL_FW_Initialize			= NULL,
	.FW_Configuration_Initialize		= DEMOD_O26_FW_Configuration_Initialize,
	.DBB_APB_DEBUG_Read			= DEMOD_O26_Debug_ReadREGvalue,
	.DBB_APB_Read				= DEMOD_O26_Debug_ATSC_ReadREGvalue,
	.DBB_APB_Write				= DEMOD_O26_Debug_ATSC_WriteREGvalue,
	.Get_FW_Info				= DEMOD_O26_Get_FW_PartInfo,
	.Get_Dump				= DEMOD_O26_Get_Dump,
	.Get_Total_Signal_Infomation		= DEMOD_O26_Get_Signal_Information,
	.Get_Cfg_Information			= DEMOD_O26_Get_CFG_Information,
	.DVB_Set_MemSconfig			= DEMOD_O26_DVB_Set_MemSconfig,
	.DVB_C_reset				= DEMOD_O26_DVBC_reset,
	.CountryGrpSetting			= DEMOD_O26_CountryGrpSetting,
	.GetTsClkRate				= DEMOD_O26_GetTsClkRate,
	.ADC_Enable				= DEMOD_O26_ADC_Enable,

/***************************************************************************************
* DVBT/ DVBC common  function
****************************************************************************************/

/***************************************************************************************
* DVBC function
****************************************************************************************/

	.DVBC_AutoSymbolRateDet 		= DEMOD_O26_DVBC_AutoSymbolRateDet,
	.DVBC_IsSymbolRateAuto			= DEMOD_O26_DVBC_IsSymbolRateAuto,
	.DVBC_IsQammodeAutoDet			= DEMOD_O26_DVBC_IsQammodeAutoDet,
	.DVBC_Set_DefaultRegisterValue		= DEMOD_O26_DVBC_Set_DefaultRegisterValue,
	.DVBC_Set_Config_auto			= NULL,	// DEMOD_O26_DVBC_Set_Config_auto
	.DVBC_Set_QamMode			= DEMOD_O26_DVBC_Set_QamMode,
	.DVBC_Set_NeverLockWaitTime 		= NULL,	// DEMOD_O26_DVBC_Set_NeverLockWaitTime
	.DVBC_Get_SymbolRateDetect		= DEMOD_O26_DVBC_Get_SymbolRateDetect,
	.DVBC_Get_SymbolRateStatus		= DEMOD_O26_DVBC_Get_SymbolRateStatus,
	.DVBC_Get_QamModeDetectStatus		= DEMOD_O26_DVBC_Get_QamModeDetectStatus,
	.DVBC_Get_DvbInfo			= NULL,	// DEMOD_O26_DVBC_Get_DvbInfo
	.DVBC_Obtaining_Signal_Lock 		= DEMOD_O26_DVBC_Obtaining_Signal_Lock,
	.DVBC_Monitoring_Signal_Lock		= DEMOD_O26_DVBC_Monitoring_Signal_Lock,
	.DVB_SW_Init				= DEMOD_O26_DVB_SW_Init,

/***************************************************************************************
* DVBC2 function
****************************************************************************************/

	.DVBC2_IsQammodeAutoDet 		= NULL,
	.DVBC2_Set_DefaultRegisterValue 	= NULL,
	.DVBC2_Set_Config_auto			= NULL,
	.DVBC2_Set_PartialConfig		= NULL,
	.DVBC2_Set_QamMode			= NULL,
	.DVBC2_Set_NeverLockWaitTime		= NULL,
	.DVBC2_Set_StartFrequency		= NULL,
	.DVBC2_Get_QamModeDetectStatus		= NULL,
	.DVBC2_Get_multiPLP_ID			= NULL,
	.DVBC2_Get_DvbInfo			= NULL,
	.DVBC2_Obtaining_Signal_Lock		= NULL,
	.DVBC2_Monitoring_Signal_Lock		= NULL,

/***************************************************************************************
* DVBT function
****************************************************************************************/

	.DVBT_Set_DefaultRegisterValue		= DEMOD_O26_DVBT_Set_DefaultRegisterValue,
	.DVBT_Set_Config_auto			= DEMOD_O26_DVBT_Set_Config_auto,
	.DVBT_Set_PartialConfig 		= DEMOD_O26_DVBT_Set_PartialConfig,
	.DVBT_Set_FullConfig			= NULL,
	.DVBT_Set_NeverLockWaitTime 		= NULL,
	.DVBT_Get_DelaySpreadStatus 		= NULL,
	.DVBT_Get_Hierach_HPSel 		= DEMOD_O26_DVBT_Get_Hierach_HPSel,
	.DVBT_Get_FFTMode			= DEMOD_O26_DVBT_Get_FFTMode,
	.DVBT_Get_GuradIntervalMode 		= DEMOD_O26_DVBT_Get_GuradIntervalMode,
	.DVBT_Get_HierachyMode			= DEMOD_O26_DVBT_Get_HierachyMode,
	.DVBT_Get_LpCoderRate			= DEMOD_O26_DVBT_Get_LpCoderRate,
	.DVBT_Get_HpCoderRate			= DEMOD_O26_DVBT_Get_HpCoderRate,
	.DVBT_Get_CellId			= DEMOD_O26_Get_Id,
	.DVBT_Get_TpsInfo			= DEMOD_O26_DVBT_Get_TpsInfo,
	.DVBT_Get_TotalInfo 			= DEMOD_O26_DVBT_Get_TotalInfo,
	.DVBT_Get_IFO_LOCK			= NULL,
	.DVBT_Get_CochanDetIndicator		= NULL, //DEMOD_O18_DVBT_Get_CochanDetIndicator,
	.DVBT_EqualizereReset			= NULL,
	.DVBT_Obtaining_Signal_Lock 		= DEMOD_O26_DVBT_Obtaining_Signal_Lock,
	.DVBT_Monitoring_Signal_Lock		= DEMOD_O26_DVBT_Monitoring_Signal_Lock,

/***************************************************************************************
* DVBT2 function
****************************************************************************************/
	.DVBT2_Set_DefaultRegisterValue		= DEMOD_O26_DVBT_Set_DefaultRegisterValue,
	.DVBT2_Set_Config_auto			= DEMOD_O26_DVBT2_Set_Config_auto,
	.DVBT2_Set_PartialConfig 		= DEMOD_O26_DVBT2_Set_PartialConfig,
	.DVBT2_Set_FullConfig			= NULL,
	.DVBT2_Set_NeverLockWaitTime 		= NULL,
	.DVBT2_Get_DelaySpreadStatus 		= NULL,
	.DVBT2_Get_FFTMode			= DEMOD_O26_DVBT2_Get_FFTMode,
	.DVBT2_Get_GuradIntervalMode 		= DEMOD_O26_DVBT2_Get_GuradIntervalMode,
	.DVBT2_Get_CoderRate			= DEMOD_O26_DVBT2_Get_CoderRate,
	.DVBT2_Get_PlpInfo			= DEMOD_O26_DVBT2_Get_PlpInfo,
	.DVBT2_Get_multiPLP_ID			= DEMOD_O26_DVBT2_Get_multiPLP_ID,
	.DVBT2_Get_TotalInfo 			= DEMOD_O26_DVBT2_Get_TotalInfo,
	.DVBT2_Obtaining_Signal_Lock 		= DEMOD_O26_DVBT2_Obtaining_Signal_Lock,
	.DVBT2_Monitoring_Signal_Lock		= DEMOD_O26_DVBT2_Monitoring_Signal_Lock,
	.DVBT2_Set_MemSconfig			= NULL, //DEMOD_O26_DVBT2_Set_MemSconfig,

/***************************************************************************************
* VSB/ QAM/ ISDBT common  function
****************************************************************************************/

/***************************************************************************************
* VSB function
****************************************************************************************/

	.VSB_Set_DefaultRegisterValue		= NULL,
	.VSB_Set_NeverLockWaitTime		= NULL,
	.VSB_CochannelExist 			= NULL,
	.VSB_PreMonitor 			= NULL,
	.VSB_Monitor				= NULL,
	.VSB_Get_MSEdynStatus			= NULL,
	.VSB_Get_TotalInfo			= NULL,
	.VSB_Obtaining_Signal_Lock		= DEMOD_O26_VSB_Obtaining_Signal_Lock,
	.VSB_Monitoring_Signal_Lock 		= DEMOD_O26_VSB_Monitoring_Signal_Lock,
	.ATSC_SW_Init				= DEMOD_O26_ATSC_SW_Init,
	.VSB_SetDemod_Simple 			= DEMOD_O26_VSB_SetDemod_Simple,

/***************************************************************************************
* QAM function
****************************************************************************************/

	.QAM_SoftwareResetFEC			= NULL,
	.QAM_Monitor				= NULL,
	.QAM_ModeAutoDetection			= NULL,
	.QAM_64Mode 				= NULL,
	.QAM_256Mode				= NULL,
	.QAM_Set_DefaultRegisterValue		= DEMOD_O26_QAM_Set_DefaultRegisterValue,
	.QAM_Set_NeverLockWaitTime		= NULL,
	.QAM_Get_TotalInfo			= NULL,
	.QAM_Obtaining_Signal_Lock		= DEMOD_O26_QAM_Obtaining_Signal_Lock,
	.QAM_Monitoring_Signal_Lock 		= DEMOD_O26_QAM_Monitoring_Signal_Lock,
	.QAM_EQ_Signal_Detector 		= NULL,

/***************************************************************************************
* ISDBT function
****************************************************************************************/

	.ISDBT_Set_DefaultRegisterValue 	= NULL,
	.ISDBT_Set_Config_auto		 	= NULL,
	.ISDBT_Set_PartialConfig	 	= NULL,
	.ISDBT_Set_FullConfig			= NULL,
	.ISDBT_Set_NeverLockWaitTime		= NULL,
	.ISDBT_Get_DelaySpreadStatus		= NULL,
	.ISDBT_Get_FFTMode			= DEMOD_O26_ISDBT_Get_FFTMode,
	.ISDBT_Get_GuradIntervalMode		= DEMOD_O26_ISDBT_Get_GuradIntervalMode,
	.ISDBT_Get_TMCCInfo 	  		= DEMOD_O26_ISDBT_Get_TMCCInfo,
	.ISDBT_Get_TotalInfo	   		= NULL,
	.ISDBT_Get_IFO_LOCK 	  		= NULL,
	.ISDBT_Get_CochanDetIndicator		= NULL,
	.ISDBT_EqualizereReset			= NULL,
	.ISDBT_Obtaining_Signal_Lock		= DEMOD_O26_ISDBT_Obtaining_Signal_Lock,
	.ISDBT_Monitoring_Signal_Lock 		= DEMOD_O26_ISDBT_Monitoring_Signal_Lock,
	.ISDBT_Set_MemSconfig			= DEMOD_O26_ISDBT_Set_MemSconfig,
	.ISDBT_GetEmergencyAlertFlagStatus	= DEMOD_O26_ISDBT_GetEmergencyAlertFlagStatus,

/***********************************************************************************
* DVBS function
************************************************************************************/

	.DVBS_Set_DefaultRegisterValue		= NULL,
	.DVBS_Set_Config_auto			= DEMOD_O26_DVBS_Set_Config_auto,
	.DVBS_Set_PartialConfig			= NULL,
	.DVBS_Set_FullConfig			= DEMOD_O26_DVBS_Set_FullConfig,
	.DVBS_Get_CoderRate			= DEMOD_O26_DVBS_Get_CoderRate,
	.DVBS_Get_SymbolRate			= DEMOD_O26_DVBS_Get_SymbolRate,
	.DVBS_Get_TotalInfo			= DEMOD_O26_DVBS_Get_TotalInfo,
	.DVBS_Set_DiseqcToneMessageCtrl		= DEMOD_O26_DVBS_Set_DiseqcToneMessageCtrl,
	.DVBS_Set_EnvelopModeCtrl		= NULL,
	.DVBS_Get_BlindInfo			= DEMOD_O26_DVBS_Get_BlindInfo,
	.DVBS_Set_BlindSpectrumMode		= NULL,
	.DVBS_Obtaining_Signal_Lock		= DEMOD_O26_DVBS_Obtaining_Signal_Lock,
	.DVBS_Monitoring_Signal_Lock		= DEMOD_O26_DVBS_Monitoring_Signal_Lock,
	.DVBS_Set_SpectrumModeConfig		= NULL,


/***********************************************************************************
* DVBS2 function
************************************************************************************/

	.DVBS2_Set_DefaultRegisterValue		= NULL,
	.DVBS2_Set_Config_auto			= DEMOD_O26_DVBS2_Set_Config_auto,
	.DVBS2_Set_PartialConfig		= NULL,
	.DVBS2_Set_FullConfig			= DEMOD_O26_DVBS2_Set_FullConfig,
	.DVBS2_Get_CoderRate			= DEMOD_O26_DVBS2_Get_CoderRate,
	.DVBS2_Get_Pilot			= DEMOD_O26_DVBS2_Get_Pilot,
	.DVBS2_Get_SymbolRate			= DEMOD_O26_DVBS2_Get_SymbolRate,
	.DVBS2_Get_TotalInfo			= DEMOD_O26_DVBS2_Get_TotalInfo,
	.DVBS2_Set_MemSconfig			= NULL, //DEMOD_O26_DVBS2_Set_MemSconfig,
	.DVBS2_Obtaining_Signal_Lock		= DEMOD_O26_DVBS2_Obtaining_Signal_Lock,
	.DVBS2_Monitoring_Signal_Lock		= DEMOD_O26_DVBS2_Monitoring_Signal_Lock,


/***********************************************************************************
* DVBS/S2 function
************************************************************************************/

	.DVBSX_BlindScan_Init			= DEMOD_O26_DVBSX_BlindScan_Init,
	.DVBSX_BlindScan_End			= DEMOD_O26_DVBSX_BlindScan_End,
	.DVBSX_Get_TunerFreq			= DEMOD_O26_DVBSX_Get_TunerFreq,
	.DVBSX_Get_OffsetFreq			= DEMOD_O26_DVBSX_Get_OffsetFreq,
	.DVBSX_SymbolRate_Detec			= DEMOD_O26_DVBSX_SymbolRate_Detec,
	.DVBSX_BlindLock_Loop			= DEMOD_O26_DVBSX_BlindLock_Loop,
	.DVBSX_Get_Nextfreq_Status		= DEMOD_O26_DVBSX_Get_Nextfreq_Status,


/***********************************************************************************
* DTMB function
************************************************************************************/

	.DTMB_SW_Init				= DEMOD_O26_DTMB_SW_Init,
	.DTMB_Get_CarrierMode			= DEMOD_O26_DTMB_Get_CarrierMode,
	.DTMB_Get_Time_Interval			= DEMOD_O26_DTMB_Get_Time_Interval,
	.DTMB_Get_PnMode			= DEMOD_O26_DTMB_Get_Pn_Mode,
	.DTMB_Get_CodeRate			= DEMOD_O26_DTMB_Get_CodeRate,
	.DTMB_Get_Constellation			= DEMOD_O26_DTMB_Get_Constellation,
	.DTMB_Obtaining_Signal_Lock		= DEMOD_O26_DTMB_Obtaining_Signal_Lock,
	.DTMB_Monitoring_Signal_Lock		= DEMOD_O26_DTMB_Monitoring_Signal_Lock,
	.DTMB_Set_Config_auto			= DEMOD_O26_DTMB_Set_Config_auto,
	.DTMB_Set_PartialConfig 		= DEMOD_O26_DTMB_Set_PartialConfig,
	.DTMB_Set_MemSconfig			= DEMOD_O26_DTMB_Set_MemSconfig,


/***************************************************************************************
* ATSC3 function
****************************************************************************************/

	.ATSC3_Get_FFTMode			= DEMOD_O26_ATSC3_Get_FFTMode,
	.ATSC3_Get_GuradIntervalMode		= DEMOD_O26_ATSC3_Get_GuradIntervalMode,
	.ATSC3_Get_CodeRate			= DEMOD_O26_ATSC3_Get_CodeRate,
	.ATSC3_Get_Constellation 		= DEMOD_O26_ATSC3_Get_Constellation,
	.ATSC3_Obtaining_Signal_Lock		= DEMOD_O26_ATSC3_Obtaining_Signal_Lock,
	.ATSC3_Monitoring_Signal_Lock		= DEMOD_O26_ATSC3_Monitoring_Signal_Lock,
	.ATSC3_Set_PLP				= DEMOD_O26_ATSC3_Set_PLP,
	.ATSC3_Get_MPLP_Info    		= DEMOD_O26_ATSC3_Get_MPLP_Info,
	.ATSC3_Set_MemSconfig			= DEMOD_O26_ATSC3_Set_MemSconfig,
	.ATSC3_Set_OIFType			= DEMOD_O26_ATSC3_Set_OIFType,

/***********************************************************************************
* FW util function
************************************************************************************/
	.FW_ReInit				= NULL,
	.IPC_Init				= DEMOD_O26_IPC_Init,
	.IPC_Enable				= DEMOD_O26_IPC_Enable,
	.API_Suspend				= DEMOD_O26_API_Suspend,
	.API_Status				= DEMOD_O26_API_Status,
	.API_Dump				= DEMOD_O26_API_Dump,
	.IPC_Status				= DEMOD_O26_IPC_Status,
	.IPC_Dump				= DEMOD_O26_IPC_Dump,
	.Get_UART				= DEMOD_O26_Get_UART,
	.Set_UART				= DEMOD_O26_Set_UART,
	.Set_UART_Speed				= DEMOD_O26_MCU_Set_UART_Speed,
	.Set_UART_HEX				= DEMOD_O26_MCU_Set_UART_HEX,
	.Get_JTAG				= DEMOD_O26_Get_JTAG,
	.Set_JTAG				= DEMOD_O26_Set_JTAG,
	.Get_Trace				= DEMOD_O26_Get_Trace,
	.Set_Trace				= DEMOD_O26_Set_Trace,

/***************************************************************************************
* ABB  function
****************************************************************************************/

	.ADEMOD_Demod_Open			= NULL,
	.ADEMOD_Init				= NULL,
	.ADEMOD_Set_IF_Frq			= NULL,
	.ADEMOD_SoftwareReset			= NULL,
	.ADEMOD_Set_AftRange			= NULL,

	.ADEMOD_ResetHW 			= NULL,
	.ADEMOD_SetI2C				= NULL,
	.ADEMOD_Set_AbbMode 			= NULL,
	.ADEMOD_Set_WorkAround			= NULL,
	.ADEMOD_Set_CvbsRateConversion		= NULL,
	.ADEMOD_Set_HighCvbsRateOffset		= NULL,
	.ADEMOD_Set_ClampingCtrl		= NULL,
	.ADEMOD_Set_SifCtrl 			= NULL,
	.ADEMOD_Set_CvbsDecCtrl 		= NULL,
	.ADEMOD_Set_SifPathCtrl 		= NULL,
	.ADEMOD_Set_SpectrumInv 		= NULL,
	.ADEMOD_Set_SpecialSifData		= NULL,
	.ADEMOD_Obtaining_Signal_Lock		= NULL,
	.ADEMOD_Monitoring_Signal_Lock		= NULL,

	.ADEMOD_Dbg_Get_RegDump 		= NULL,
	.ADEMOD_Dbg_Set_RegValue		= NULL,
	.ADEMOD_Dbg_Set_SmartTune		= NULL,
	.ADEMOD_Dbg_Get_RegValue		= NULL,
	.ADEMOD_Dbg_TestFunctions		= NULL,

	.ADEMOD_Preset_Set			= NULL,
	.ADEMOD_Demodulate			= NULL,
	.ADEMOD_Parameter_Set			= NULL,
	.ADEMOD_Parameter_Get			= NULL,
	.ADEMOD_AGC_Set 			= NULL,
	.ADEMOD_AGC_Get 			= NULL,
	.ADEMOD_ChanScan_Set			= NULL,
	.ADEMOD_SleepMode_Set			= NULL,
	.ADEMOD_SleepMode_Get			= NULL,
	.ADEMOD_HostI2C_Write			= NULL,
	.ADEMOD_HostI2C_Read			= NULL,

};

static const LX_DEMOD_CFG_T g_demod_cfg_o26 =
{

};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get L9 specific configuration
 *
 *  @return LX_DEMOD_CFG_T
 */
const LX_DEMOD_CFG_T * DEMOD_O26_GetCfg (void)
{
    return &g_demod_cfg_o26;
}

void DEMOD_O26_InitHAL (DEMOD_HAL_T * hal)
{
	memcpy( hal, &g_demod_hal_o26, sizeof(DEMOD_HAL_T));
}

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

