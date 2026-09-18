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
**  Name:demod_drv_m16.c
**
**  Description:    ABB/GBB point functions interface.
**
**  Functions
**  Implemented:   LX_DEMOD_CFG_T*   DEMOD_M16P_GetCfg
**                 void	DEMOD_M16P_InitHAL
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

#include "demod_common_m16p.h"
#include "demod_dvb_m16p.h"
#include "demod_vqi_m16p.h"
#include "demod_analog_m16p.h"

#if 0
LX_DEMOD_COMMON_REG_T	   *gpRegM16PCOMMON = NULL;
LX_DEMOD_SYNC_REG_T 	   *gpRegM16PSYNC = NULL;
LX_DEMOD_SYNC2ND_REG_T	   *gpRegM16PSYNC2ND = NULL;
LX_DEMOD_EQ_V_REG_T 	   *gpRegM16PEQ_V = NULL;
LX_DEMOD_EQ_DI_REG_T	   *gpRegM16PEQ_DI = NULL;
LX_DEMOD_EQ_CQS_REG_T	   *gpRegM16PCQS = NULL;
LX_DEMOD_FEC_REG_T		   *gpRegM16PFEC = NULL;

#endif



const LX_DEMOD_CFG_T*   DEMOD_M16P_GetCfg(void);



/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
const static	DEMOD_HAL_T		g_demod_hal_m16p =
{
		.GetCfg	   					=  DEMOD_M16P_GetCfg,


/***************************************************************************************
* DVBT/ DVBC/ VSB/ QAM/ ISDBT  common  function
****************************************************************************************/

	#if 0
		.ResetHW					= DEMOD_M16P_ResetHW,
		.SetI2C 					= DEMOD_M16P_SetI2C,
		.SetInclk					= DEMOD_M16P_SetInclk,
		.AdcInit					= DEMOD_M16P_AdcInit,


		.Get_Id 					= DEMOD_M16P_Get_Id,
		.RepeaterEnable 			= DEMOD_M16P_RepeaterEnable,
		.SoftwareReset				= DEMOD_M16P_SoftwareReset,
		.Serial_Control 			= DEMOD_M16P_Serial_Control,
		.Power_Save 				= DEMOD_M16P_Power_Save,
		.StdOperModeContrl			= DEMOD_M16P_StdOperModeContrl,
		.NeverlockScan				= DEMOD_M16P_NeverlockScan,
		.TPOutCLKEnable 			= DEMOD_M16P_TPOutEnable,
		.Set_IF_Frq 				= DEMOD_M16P_Set_IF_Frq,
		.Set_AGCPolarity			= DEMOD_M16P_Set_AGCPolarity,
		.Set_SpectrumCtrl			= DEMOD_M16P_Set_SpectrumCtrl,
		.Get_SpectrumStatus 		= DEMOD_M16P_Get_SpectrumStatus,
		.Get_IFAGC					= DEMOD_M16P_Get_IFAGC,
		.Get_OperMode				= DEMOD_M16P_Get_OperMode,
		.Get_NeverLockStatus		= DEMOD_M16P_Get_NeverLockStatus,
		.Get_CarrierFreqOffset		= DEMOD_M16P_Get_CarrierFreqOffset,
		.Get_TPIFStatus 			= DEMOD_M16P_Get_TPIFStatus,
		.Get_VABER					= DEMOD_M16P_Get_VABER,
		.Get_Packet_Error			= DEMOD_M16P_Get_Packet_Error,
		.Get_BandWidthMode			= DEMOD_M16P_Get_BandWidthMode,
		.Get_QAMMode				= DEMOD_M16P_Get_QAMMode,
		.Get_MseInfo				= DEMOD_M16P_Get_MseInfo,
		.Get_Lock					= DEMOD_M16P_Get_Lock,
		.Get_SysLockTime			= DEMOD_M16P_VSB_Get_SysLockTime,
		.Get_FecLockTime			= DEMOD_M16P_VSB_Get_FecLockTime,
		.Set_Frame_resynchronizaiton= DEMOD_M16P_QAM_Set_Frame_resynchronizaiton,
	#else
		.ResetHW					= DEMOD_M16P_ResetHW,
		.SetI2C 					= DEMOD_M16P_SetI2C,
		.SetInclk					= DEMOD_M16P_SetInclk,
		.AdcInit					= DEMOD_M16P_AdcInit,


		.Get_Id 					= NULL,
		.RepeaterEnable 			= DEMOD_M16P_RepeaterEnable,
		.SoftwareReset				= DEMOD_M16P_SoftwareReset,
		.Serial_Control 			= NULL,
		.Power_Save 				= DEMOD_M16P_Power_Save,
		.StdOperModeContrl			= DEMOD_M16P_StdOperModeContrl,
		.NeverlockScan				= DEMOD_M16P_NeverlockScan,
		.TPOutCLKEnable 			= DEMOD_M16P_TPOutEnable,
		.Set_IF_Frq 				= DEMOD_M16P_Set_IF_Frq,
		.Set_AGCPolarity			= DEMOD_M16P_Set_AGCPolarity,
		.Set_SpectrumCtrl			= NULL,
		.Get_SpectrumStatus 		= NULL,
		.Get_IFAGC					= DEMOD_M16P_Get_IFAGC,
		.Get_OperMode				= DEMOD_M16P_Get_OperMode,
		.Get_NeverLockStatus		= DEMOD_M16P_Get_NeverLockStatus,
		.Get_CarrierFreqOffset		= DEMOD_M16P_Get_CarrierFreqOffset,
		.Get_TPIFStatus 			= NULL,
		.Get_VABER					= DEMOD_M16P_Get_VABER,
		.Get_Packet_Error			= DEMOD_M16P_Get_Packet_Error,
		.Get_BandWidthMode			= DEMOD_M16P_Get_BandWidthMode,
		.Get_QAMMode				= DEMOD_M16P_Get_QAMMode,
		.Get_MseInfo				= DEMOD_M16P_Get_MseInfo,
		.Get_Lock					= DEMOD_M16P_Get_Lock,
		.Get_SysLockTime			= NULL,
		.Get_FecLockTime			= NULL,
		.Set_Frame_resynchronizaiton= NULL,
		.Get_I2C_Handle				= DEMOD_M16P_Get_I2C_Handle,
		.FW_Initialize				= DEMOD_M16P_FW_Initialize,
		.DBB_I2C_Read				= DEMOD_M16P_Debug_ATSC_ReadREGvalue,
		.DBB_I2C_Write				= DEMOD_M16P_Debug_ATSC_WriteREGvalue,
		.Get_FW_Info				= DEMOD_M16P_Get_FW_PartInfo,
		.Get_Dump					= DEMOD_M16P_Get_Dump,

	#endif



/***************************************************************************************
* DVBT/ DVBC common  function
****************************************************************************************/


/***************************************************************************************
* DVBC function
****************************************************************************************/

	#if 0
		.DVBC_AutoSymbolRateDet 			= DEMOD_M16P_DVBC_AutoSymbolRateDet,
		.DVBC_IsSymbolRateAuto				= DEMOD_M16P_DVBC_IsSymbolRateAuto,
		.DVBC_IsQammodeAutoDet				= DEMOD_M16P_DVBC_IsQammodeAutoDet,
		.DVBC_Set_DefaultRegisterValue		= DEMOD_M16P_DVBC_Set_DefaultRegisterValue,
		.DVBC_Set_Config_auto				= DEMOD_M16P_DVBC_Set_Config_auto,
		.DVBC_Set_QamMode					= DEMOD_M16P_DVBC_Set_QamMode,
		.DVBC_Set_NeverLockWaitTime 		= DEMOD_M16P_DVBC_Set_NeverLockWaitTime,
		.DVBC_Get_SymbolRateDetect			= DEMOD_M16P_DVBC_Get_SymbolRateDetect,
		.DVBC_Get_SymbolRateStatus			= DEMOD_M16P_DVBC_Get_SymbolRateStatus,
		.DVBC_Get_QamModeDetectStatus		= DEMOD_M16P_DVBC_Get_QamModeDetectStatus,
		.DVBC_Get_DvbInfo					= DEMOD_M16P_DVBC_Get_DvbInfo,

		.DVBC_Obtaining_Signal_Lock 		= DEMOD_M16P_DVBC_Obtaining_Signal_Lock,
		.DVBC_Monitoring_Signal_Lock		= DEMOD_M16P_DVBC_Monitoring_Signal_Lock,

	#else
		.DVBC_AutoSymbolRateDet 			= DEMOD_M16P_DVBC_AutoSymbolRateDet,
		.DVBC_IsSymbolRateAuto			= DEMOD_M16P_DVBC_IsSymbolRateAuto,
		.DVBC_IsQammodeAutoDet			= DEMOD_M16P_DVBC_IsQammodeAutoDet,
		.DVBC_Set_DefaultRegisterValue		= DEMOD_M16P_DVBC_Set_DefaultRegisterValue,
		.DVBC_Set_Config_auto			= NULL,
		.DVBC_Set_QamMode				= DEMOD_M16P_DVBC_Set_QamMode,
		.DVBC_Set_NeverLockWaitTime 		= NULL,
		.DVBC_Get_SymbolRateDetect		= DEMOD_M16P_DVBC_Get_SymbolRateDetect,
		.DVBC_Get_SymbolRateStatus		= DEMOD_M16P_DVBC_Get_SymbolRateStatus,
		.DVBC_Get_QamModeDetectStatus	= DEMOD_M16P_DVBC_Get_QamModeDetectStatus,
		.DVBC_Get_DvbInfo				= NULL,

		.DVBC_Obtaining_Signal_Lock 		= DEMOD_M16P_DVBC_Obtaining_Signal_Lock,
		.DVBC_Monitoring_Signal_Lock		= DEMOD_M16P_DVBC_Monitoring_Signal_Lock,
		.DVB_SW_Init						= DEMOD_M16P_DVB_SW_Init,

	#endif


/***************************************************************************************
* DVBC2 function
****************************************************************************************/

		.DVBC2_IsQammodeAutoDet 			= NULL,
		.DVBC2_Set_DefaultRegisterValue 	= NULL,
		.DVBC2_Set_Config_auto				= NULL,
		.DVBC2_Set_PartialConfig			= NULL,
		.DVBC2_Set_QamMode					= NULL,
		.DVBC2_Set_NeverLockWaitTime		= NULL,
		.DVBC2_Set_StartFrequency			= NULL,
		.DVBC2_Get_QamModeDetectStatus		= NULL,
		.DVBC2_Get_multiPLP_ID				= NULL,
		.DVBC2_Get_DvbInfo					= NULL,

		.DVBC2_Obtaining_Signal_Lock		= NULL,
		.DVBC2_Monitoring_Signal_Lock		= NULL,


/***************************************************************************************
* DVBT function
****************************************************************************************/

	#if 0
		.DVBT_Set_DefaultRegisterValue		= DEMOD_M16P_DVBT_Set_DefaultRegisterValue,
		.DVBT_Set_Config_auto				= DEMOD_M16P_DVBT_Set_Config_auto,
		.DVBT_Set_PartialConfig 			= DEMOD_M16P_DVBT_Set_PartialConfig,
		.DVBT_Set_FullConfig				= DEMOD_M16P_DVBT_Set_FullConfig,
		.DVBT_Set_NeverLockWaitTime 		= DEMOD_M16P_DVBT_Set_NeverLockWaitTime,
		.DVBT_Get_DelaySpreadStatus 		= DEMOD_M16P_DVBT_Get_DelaySpreadStatus,
		.DVBT_Get_Hierach_HPSel 			= DEMOD_M16P_DVBT_Get_Hierach_HPSel,
		.DVBT_Get_FFTMode					= DEMOD_M16P_DVBT_Get_FFTMode,
		.DVBT_Get_GuradIntervalMode 		= DEMOD_M16P_DVBT_Get_GuradIntervalMode,
		.DVBT_Get_HierachyMode				= DEMOD_M16P_DVBT_Get_HierachyMode,
		.DVBT_Get_LpCoderRate				= DEMOD_M16P_DVBT_Get_LpCoderRate,
		.DVBT_Get_HpCoderRate				= DEMOD_M16P_DVBT_Get_HpCoderRate,
		.DVBT_Get_CellId					= DEMOD_M16P_DVBT_Get_CellId,
		.DVBT_Get_TpsInfo					= DEMOD_M16P_DVBT_Get_TpsInfo,
		.DVBT_Get_TotalInfo 				= DEMOD_M16P_DVBT_Get_TotalInfo,
		.DVBT_Get_IFO_LOCK					= DEMOD_M16P_DVBT_Get_IFO_LOCK,
		.DVBT_Get_CochanDetIndicator		= NULL, //DEMOD_M16P_DVBT_Get_CochanDetIndicator,
		.DVBT_EqualizereReset				= DEMOD_M16P_DVBT_EqualizereReset,

		.DVBT_Obtaining_Signal_Lock 		= DEMOD_M16P_DVBT_Obtaining_Signal_Lock,
		.DVBT_Monitoring_Signal_Lock		= DEMOD_M16P_DVBT_Monitoring_Signal_Lock,

	#else
		.DVBT_Set_DefaultRegisterValue		= NULL,
		.DVBT_Set_Config_auto				= NULL,
		.DVBT_Set_PartialConfig 			= NULL,
		.DVBT_Set_FullConfig				= NULL,
		.DVBT_Set_NeverLockWaitTime 		= NULL,
		.DVBT_Get_DelaySpreadStatus 		= NULL,
		.DVBT_Get_Hierach_HPSel 			= NULL,
		.DVBT_Get_FFTMode					= NULL,
		.DVBT_Get_GuradIntervalMode 		= NULL,
		.DVBT_Get_HierachyMode				= NULL,
		.DVBT_Get_LpCoderRate				= NULL,
		.DVBT_Get_HpCoderRate				= NULL,
		.DVBT_Get_CellId					= NULL,
		.DVBT_Get_TpsInfo					= NULL,
		.DVBT_Get_TotalInfo 				= NULL,
		.DVBT_Get_IFO_LOCK					= NULL,
		.DVBT_Get_CochanDetIndicator		= NULL, //DEMOD_M16P_DVBT_Get_CochanDetIndicator,
		.DVBT_EqualizereReset				= NULL,

		.DVBT_Obtaining_Signal_Lock 		= DEMOD_M16P_DVBT_Obtaining_Signal_Lock,
		.DVBT_Monitoring_Signal_Lock		= DEMOD_M16P_DVBT_Monitoring_Signal_Lock,


	#endif



/***************************************************************************************
* DVBT2 function
****************************************************************************************/
	#if 0
		.DVBT2_Set_DefaultRegisterValue 	= NULL,
		.DVBT2_Set_Config_auto				= NULL,
		.DVBT2_Set_PartialConfig			= NULL,
		.DVBT2_Set_FullConfig				= NULL,
		.DVBT2_Set_NeverLockWaitTime		= NULL,
		.DVBT2_Get_DelaySpreadStatus		= NULL,
		.DVBT2_Get_FFTMode					= NULL,
		.DVBT2_Get_GuradIntervalMode		= NULL,
		.DVBT2_Get_CoderRate				= NULL,
		.DVBT2_Get_PlpInfo					= NULL,
		.DVBT2_Get_multiPLP_ID				= NULL,
		.DVBT2_Get_TotalInfo				= NULL,

		.DVBT2_Obtaining_Signal_Lock		= NULL,
		.DVBT2_Monitoring_Signal_Lock		= NULL,

	#else
		.DVBT2_Set_DefaultRegisterValue 	= NULL,
		.DVBT2_Set_Config_auto				= NULL,
		.DVBT2_Set_PartialConfig			= NULL,
		.DVBT2_Set_FullConfig				= NULL,
		.DVBT2_Set_NeverLockWaitTime		= NULL,
		.DVBT2_Get_DelaySpreadStatus		= NULL,
		.DVBT2_Get_FFTMode					= NULL,
		.DVBT2_Get_GuradIntervalMode		= NULL,
		.DVBT2_Get_CoderRate				= NULL,
		.DVBT2_Get_PlpInfo					= NULL,
		.DVBT2_Get_multiPLP_ID				= NULL,
		.DVBT2_Get_TotalInfo				= NULL,

		.DVBT2_Obtaining_Signal_Lock		= NULL,
		.DVBT2_Monitoring_Signal_Lock		= NULL,

	#endif





/***************************************************************************************
* VSB/ QAM/ ISDBT common  function
****************************************************************************************/



/***************************************************************************************
* VSB function
****************************************************************************************/

	#if 0
		.VSB_Set_DefaultRegisterValue		= DEMOD_M16P_VSB_Set_DefaultRegisterValue,
		.VSB_Set_NeverLockWaitTime			= DEMOD_M16P_VSB_Set_NeverLockWaitTime,
		.VSB_CochannelExist 				= DEMOD_M16P_VSB_CochannelExist,
		.VSB_PreMonitor 					= DEMOD_M16P_VSB_PreMonitor,
		.VSB_Monitor						= DEMOD_M16P_VSB_Monitor,
		.VSB_Get_MSEdynStatus				= DEMOD_M16P_VSB_Get_MSEdynStatus,
		.VSB_Get_TotalInfo					= DEMOD_M16P_VSB_Get_TotalInfo,

		.VSB_Obtaining_Signal_Lock			= DEMOD_M16P_VSB_Obtaining_Signal_Lock,
		.VSB_Monitoring_Signal_Lock 		= DEMOD_M16P_VSB_Monitoring_Signal_Lock,

	#else
		.VSB_Set_DefaultRegisterValue		= NULL,
		.VSB_Set_NeverLockWaitTime			= NULL,
		.VSB_CochannelExist 				= NULL,
		.VSB_PreMonitor 					= NULL,
		.VSB_Monitor						= NULL,
		.VSB_Get_MSEdynStatus				= NULL,
		.VSB_Get_TotalInfo					= NULL,

		.VSB_Obtaining_Signal_Lock			= DEMOD_M16P_VSB_Obtaining_Signal_Lock,
		.VSB_Monitoring_Signal_Lock 		= DEMOD_M16P_VSB_Monitoring_Signal_Lock,
		.ATSC_SW_Init						= DEMOD_M16P_ATSC_SW_Init,
		.VSB_SetDemod_Simple 				= DEMOD_M16P_LGDBB_VSB_SetDemod_Simple,
		.LGDBB_VSB_SetDemod 				= DEMOD_M16P_LGDBB_VSB_SetDemod,

	#endif


/***************************************************************************************
* QAM function
****************************************************************************************/

	#if 0
		.QAM_SoftwareResetFEC				= DEMOD_M16P_QAM_SoftwareResetFEC,
		.QAM_Monitor						= DEMOD_M16P_QAM_Monitor,
		.QAM_ModeAutoDetection				= DEMOD_M16P_QAM_ModeAutoDetection,
		.QAM_64Mode 						= DEMOD_M16P_QAM_64Mode,
		.QAM_256Mode						= DEMOD_M16P_QAM_256Mode,
		.QAM_Set_DefaultRegisterValue		= DEMOD_M16P_QAM_Set_DefaultRegisterValue,
		.QAM_Set_NeverLockWaitTime			= DEMOD_M16P_QAM_Set_NeverLockWaitTime,

		.QAM_Get_TotalInfo					= DEMOD_M16P_QAM_Get_TotalInfo,

		.QAM_Obtaining_Signal_Lock			= DEMOD_M16P_QAM_Obtaining_Signal_Lock,
		.QAM_Monitoring_Signal_Lock 		= DEMOD_M16P_QAM_Monitoring_Signal_Lock,
		.QAM_EQ_Signal_Detector 			= DEMOD_M16P_QAM_EQ_Signal_Detector,

	#else
		.QAM_SoftwareResetFEC				= NULL,
		.QAM_Monitor						= NULL,
		.QAM_ModeAutoDetection				= NULL,
		.QAM_64Mode 						= NULL,
		.QAM_256Mode						= NULL,
		.QAM_Set_DefaultRegisterValue		= DEMOD_M16P_QAM_Set_DefaultRegisterValue,
		.QAM_Set_NeverLockWaitTime			= NULL,

		.QAM_Get_TotalInfo					= NULL,

		.QAM_Obtaining_Signal_Lock			= DEMOD_M16P_QAM_Obtaining_Signal_Lock,
		.QAM_Monitoring_Signal_Lock 		= DEMOD_M16P_QAM_Monitoring_Signal_Lock,
		.QAM_EQ_Signal_Detector 			= NULL,
		.LGDBB_QAM_SetDemod					= DEMOD_M16P_LGDBB_QAM_SetDemod,

	#endif




/***************************************************************************************
* ISDBT function
****************************************************************************************/
	#if 0
		.ISDBT_Set_DefaultRegisterValue 	= DEMOD_M16P_ISDBT_Set_DefaultRegisterValue,
		.ISDBT_Set_Config_auto		 		= DEMOD_M16P_ISDBT_Set_Config_auto,
		.ISDBT_Set_PartialConfig	   		= DEMOD_M16P_ISDBT_Set_PartialConfig,
		.ISDBT_Set_FullConfig				= DEMOD_M16P_ISDBT_Set_FullConfig,
		.ISDBT_Set_NeverLockWaitTime	   	= DEMOD_M16P_ISDBT_Set_NeverLockWaitTime,
		.ISDBT_Get_DelaySpreadStatus	   	= DEMOD_M16P_ISDBT_Get_DelaySpreadStatus,
		.ISDBT_Get_FFTMode		 			= DEMOD_M16P_ISDBT_Get_FFTMode,
		.ISDBT_Get_GuradIntervalMode	   	= DEMOD_M16P_ISDBT_Get_GuradIntervalMode,
		.ISDBT_Get_TMCCInfo 	  			= DEMOD_M16P_ISDBT_Get_TMCCInfo,
		.ISDBT_Get_TotalInfo	   			= DEMOD_M16P_ISDBT_Get_TotalInfo,
		.ISDBT_Get_IFO_LOCK 	  			= DEMOD_M16P_ISDBT_Get_IFO_LOCK,
		.ISDBT_Get_CochanDetIndicator		= DEMOD_M16P_ISDBT_Get_CochanDetIndicator,
		.ISDBT_EqualizereReset		 		= DEMOD_M16P_ISDBT_EqualizereReset,

		.ISDBT_Obtaining_Signal_Lock		= DEMOD_M16P_ISDBT_Obtaining_Signal_Lock,
		.ISDBT_Monitoring_Signal_Lock 		= DEMOD_M16P_ISDBT_Monitoring_Signal_Lock,
		.ISDBT_Set_MemSconfig				= DEMOD_M16P_ISDBT_Set_MemSconfig,

	#else
		.ISDBT_Set_DefaultRegisterValue 	= NULL,
		.ISDBT_Set_Config_auto		 		= NULL,
		.ISDBT_Set_PartialConfig	   		= NULL,
		.ISDBT_Set_FullConfig				= NULL,
		.ISDBT_Set_NeverLockWaitTime	   	= NULL,
		.ISDBT_Get_DelaySpreadStatus	   	= NULL,
		.ISDBT_Get_FFTMode		 			= DEMOD_M16P_ISDBT_Get_FFTMode,
		.ISDBT_Get_GuradIntervalMode	   	= DEMOD_M16P_ISDBT_Get_GuradIntervalMode,
		.ISDBT_Get_TMCCInfo 	  			= DEMOD_M16P_ISDBT_Get_TMCCInfo,
		.ISDBT_Get_TotalInfo	   			= NULL,
		.ISDBT_Get_IFO_LOCK 	  			= NULL,
		.ISDBT_Get_CochanDetIndicator		= NULL,
		.ISDBT_EqualizereReset		 		= NULL,

		.ISDBT_Obtaining_Signal_Lock		= DEMOD_M16P_ISDBT_Obtaining_Signal_Lock,
		.ISDBT_Monitoring_Signal_Lock 		= DEMOD_M16P_ISDBT_Monitoring_Signal_Lock,
		.ISDBT_Set_MemSconfig				= DEMOD_M16P_ISDBT_Set_MemSconfig,
		.ISDBT_GetEmergencyAlertFlagStatus	= DEMOD_M16P_ISDBT_GetEmergencyAlertFlagStatus,

	#endif

/***************************************************************************************
* ABB  function
****************************************************************************************/

#if 1
		.ADEMOD_Demod_Open				 	= DEMOD_M16P_ANALOG_Demod_Open,
		.ADEMOD_Init						= DEMOD_M16P_ANALOG_Init,
		.ADEMOD_Set_IF_Frq					= DEMOD_M16P_ANALOG_Set_IF_Frq,
		.ADEMOD_SoftwareReset				= DEMOD_M16P_ANALOG_SoftReset,
		.ADEMOD_Set_AftRange 				= DEMOD_M16P_ANALOG_Set_AftRange,

		.ADEMOD_ResetHW						= DEMOD_M16P_ANALOG_ResetHW,
		.ADEMOD_SetI2C						= DEMOD_M16P_ANALOG_SetI2C,
		.ADEMOD_Set_AbbMode 				= DEMOD_M16P_ANALOG_Set_AbbMode,
		.ADEMOD_Set_WorkAround	 			= NULL,
		.ADEMOD_Set_CvbsRateConversion		= DEMOD_M16P_ANALOG_Set_CvbsRateConversion,
		.ADEMOD_Set_HighCvbsRateOffset		= DEMOD_M16P_ANALOG_Set_HighCvbsRateOffset,
		.ADEMOD_Set_ClampingCtrl			= DEMOD_M16P_ANALOG_Set_ClampingCtrl,
		.ADEMOD_Set_SifCtrl					= DEMOD_M16P_ANALOG_Set_SifCtrl,
		.ADEMOD_Set_CvbsDecCtrl				= DEMOD_M16P_ANALOG_Set_CvbsDecCtrl,
		.ADEMOD_Set_SifPathCtrl				= DEMOD_M16P_ANALOG_Set_SifPathCtrl,
		.ADEMOD_Set_SpectrumInv				= DEMOD_M16P_ANALOG_Set_SpectrumInv,
		.ADEMOD_Set_SpecialSifData 			= DEMOD_M16P_ANALOG_ChangeFilter4SIF,


		.ADEMOD_Obtaining_Signal_Lock		= DEMOD_M16P_ANALOG_Obtaining_Signal_Lock,
		.ADEMOD_Monitoring_Signal_Lock 		= DEMOD_M16P_ANALOG_Monitoring_Signal_Lock,

		.ADEMOD_Dbg_Get_RegDump				= DEMOD_M16P_ANALOG_Dbg_Get_RegDump,
		.ADEMOD_Dbg_Set_RegValue 			= DEMOD_M16P_ANALOG_Dbg_Set_RegisterValue,
		.ADEMOD_Dbg_Set_SmartTune 			= DEMOD_M16P_ANALOG_Dbg_SmartTune,
		.ADEMOD_Dbg_Get_RegValue			= DEMOD_M16P_ANALOG_Dbg_Get_RegisterValue,
		.ADEMOD_Dbg_TestFunctions 			= DEMOD_M16P_ANALOG_Dbg_TestFunctions,

		.ADEMOD_Preset_Set 					= DEMOD_M16P_Analog_Preset_Set,
		.ADEMOD_Demodulate 					= DEMOD_M16P_Analog_Demodulate,
		.ADEMOD_Parameter_Set 				= DEMOD_M16P_Analog_Parameter_Set,
		.ADEMOD_Parameter_Get 				= DEMOD_M16P_Analog_Parameter_Get,
		.ADEMOD_AGC_Set 					= DEMOD_M16P_Analog_AGC_Set,
		.ADEMOD_AGC_Get 					= DEMOD_M16P_Analog_AGC_Get,
		.ADEMOD_ChanScan_Set 				= DEMOD_M16P_Analog_ChanScan_Set,
		.ADEMOD_SleepMode_Set 				= DEMOD_M16P_Analog_SleepMode_Set,
		.ADEMOD_SleepMode_Get 				= DEMOD_M16P_Analog_SleepMode_Get,
		.ADEMOD_HostI2C_Write 				= DEMOD_M16P_Analog_HostI2C_Write,
		.ADEMOD_HostI2C_Read 				= DEMOD_M16P_Analog_HostI2C_Read,
#else
		.ADEMOD_Demod_Open					= NULL,
		.ADEMOD_Init						= NULL,
		.ADEMOD_Set_IF_Frq					= NULL,
		.ADEMOD_SoftwareReset				= NULL,
		.ADEMOD_Set_AftRange				= NULL,

		.ADEMOD_ResetHW 					= NULL,
		.ADEMOD_SetI2C						= NULL,
		.ADEMOD_Set_AbbMode 				= NULL,
		.ADEMOD_Set_WorkAround				= NULL,
		.ADEMOD_Set_CvbsRateConversion		= NULL,
		.ADEMOD_Set_HighCvbsRateOffset		= NULL,
		.ADEMOD_Set_ClampingCtrl			= NULL,
		.ADEMOD_Set_SifCtrl 				= NULL,
		.ADEMOD_Set_CvbsDecCtrl 			= NULL,
		.ADEMOD_Set_SifPathCtrl 			= NULL,
		.ADEMOD_Set_SpectrumInv 			= NULL,
		.ADEMOD_Set_SpecialSifData			= NULL,


		.ADEMOD_Obtaining_Signal_Lock		= NULL,
		.ADEMOD_Monitoring_Signal_Lock		= NULL,

		.ADEMOD_Dbg_Get_RegDump 			= NULL,
		.ADEMOD_Dbg_Set_RegValue			= NULL,
		.ADEMOD_Dbg_Set_SmartTune			= NULL,
		.ADEMOD_Dbg_Get_RegValue			= NULL,
		.ADEMOD_Dbg_TestFunctions			= NULL,

		.ADEMOD_Preset_Set					= NULL,
		.ADEMOD_Demodulate					= NULL,
		.ADEMOD_Parameter_Set				= NULL,
		.ADEMOD_Parameter_Get				= NULL,
		.ADEMOD_AGC_Set 					= NULL,
		.ADEMOD_AGC_Get 					= NULL,
		.ADEMOD_ChanScan_Set				= NULL,
		.ADEMOD_SleepMode_Set				= NULL,
		.ADEMOD_SleepMode_Get				= NULL,
		.ADEMOD_HostI2C_Write				= NULL,
		.ADEMOD_HostI2C_Read				= NULL,

#endif


};

const static	LX_DEMOD_CFG_T 		g_demod_cfg_m16p =
{

};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get L9 specific configuration
 *
 *  @return LX_DEMOD_CFG_T
 */
const LX_DEMOD_CFG_T*   DEMOD_M16P_GetCfg(void)
{
    return &g_demod_cfg_m16p;
}

void	DEMOD_M16P_InitHAL( DEMOD_HAL_T*	hal )
{
#if 0
if(NULL==gpRegM16PCOMMON)
{
	gpRegM16PCOMMON	=  (LX_DEMOD_COMMON_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_COMMON_REG_T));
}

if(NULL==gpRegM16PSYNC)
{
	gpRegM16PSYNC	=  (LX_DEMOD_SYNC_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_SYNC_REG_T));
}

if(NULL==gpRegM16PSYNC2ND)
{
	gpRegM16PSYNC2ND =  (LX_DEMOD_SYNC2ND_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_SYNC2ND_REG_T));
}

if(NULL==gpRegM16PEQ_V)
{
	gpRegM16PEQ_V	=  (LX_DEMOD_EQ_V_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_EQ_V_REG_T));
}

if(NULL==gpRegM16PEQ_DI)
{
	gpRegM16PEQ_DI	=  (LX_DEMOD_EQ_DI_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_EQ_DI_REG_T));
}

if(NULL==gpRegM16PCQS)
{
	gpRegM16PCQS 	=  (LX_DEMOD_EQ_CQS_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_EQ_CQS_REG_T));
}

if(NULL==gpRegM16PFEC)
{
	gpRegM16PFEC 	=  (LX_DEMOD_FEC_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_FEC_REG_T));
}

#endif


	memcpy( hal, &g_demod_hal_m16p, sizeof(DEMOD_HAL_T));
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


