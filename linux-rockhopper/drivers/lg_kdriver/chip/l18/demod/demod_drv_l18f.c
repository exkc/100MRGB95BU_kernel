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
**  Implemented:   LX_DEMOD_CFG_T*   DEMOD_L18F_GetCfg
**                 void	DEMOD_L18F_InitHAL
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

#include "demod_common_l18f.h"
#include "demod_dvb_l18f.h"
#include "demod_vqi_l18f.h"
#include "demod_sat_l18f.h"
#include "demod_analog_l18f.h"

#if 0
LX_DEMOD_COMMON_REG_T	   *gpRegL18FCOMMON = NULL;
LX_DEMOD_SYNC_REG_T 	   *gpRegL18FSYNC = NULL;
LX_DEMOD_SYNC2ND_REG_T	   *gpRegL18FSYNC2ND = NULL;
LX_DEMOD_EQ_V_REG_T 	   *gpRegL18FEQ_V = NULL;
LX_DEMOD_EQ_DI_REG_T	   *gpRegL18FEQ_DI = NULL;
LX_DEMOD_EQ_CQS_REG_T	   *gpRegL18FCQS = NULL;
LX_DEMOD_FEC_REG_T		   *gpRegL18FFEC = NULL;

#endif



const LX_DEMOD_CFG_T*   DEMOD_L18F_GetCfg(void);



/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
const static	DEMOD_HAL_T		g_demod_hal_l18f =
{
		.GetCfg	   					=  DEMOD_L18F_GetCfg,


/***************************************************************************************
* DVBT/ DVBC/ VSB/ QAM/ ISDBT  common  function
****************************************************************************************/

	#if 0
		.ResetHW					= DEMOD_L18F_ResetHW,
		.SetI2C 					= DEMOD_L18F_SetI2C,
		.SetInclk					= DEMOD_L18F_SetInclk,
		.AdcInit					= DEMOD_L18F_AdcInit,


		.Get_Id 					= DEMOD_L18F_Get_Id,
		.RepeaterEnable 			= DEMOD_L18F_RepeaterEnable,
		.SoftwareReset				= DEMOD_L18F_SoftwareReset,
		.Serial_Control 			= DEMOD_L18F_Serial_Control,
		.Power_Save 				= DEMOD_L18F_Power_Save,
		.StdOperModeContrl			= DEMOD_L18F_StdOperModeContrl,
		.NeverlockScan				= DEMOD_L18F_NeverlockScan,
		.TPOutCLKEnable 			= DEMOD_L18F_TPOutEnable,
		.Set_IF_Frq 				= DEMOD_L18F_Set_IF_Frq,
		.Set_AGCPolarity			= DEMOD_L18F_Set_AGCPolarity,
		.Set_SpectrumCtrl			= DEMOD_L18F_Set_SpectrumCtrl,
		.Get_SpectrumStatus 		= DEMOD_L18F_Get_SpectrumStatus,
		.Get_IFAGC					= DEMOD_L18F_Get_IFAGC,
		.Get_OperMode				= DEMOD_L18F_Get_OperMode,
		.Get_NeverLockStatus		= DEMOD_L18F_Get_NeverLockStatus,
		.Get_CarrierFreqOffset		= DEMOD_L18F_Get_CarrierFreqOffset,
		.Get_TPIFStatus 			= DEMOD_L18F_Get_TPIFStatus,
		.Get_VABER					= DEMOD_L18F_Get_VABER,
		.Get_Packet_Error			= DEMOD_L18F_Get_Packet_Error,
		.Get_BandWidthMode			= DEMOD_L18F_Get_BandWidthMode,
		.Get_QAMMode				= DEMOD_L18F_Get_QAMMode,
		.Get_MseInfo				= DEMOD_L18F_Get_MseInfo,
		.Get_Lock					= DEMOD_L18F_Get_Lock,
		.Get_SysLockTime			= DEMOD_L18F_VSB_Get_SysLockTime,
		.Get_FecLockTime			= DEMOD_L18F_VSB_Get_FecLockTime,
		.Set_Frame_resynchronizaiton= DEMOD_L18F_QAM_Set_Frame_resynchronizaiton,
	#else
		.ResetHW					= DEMOD_L18F_ResetHW,
		.SetI2C 					= DEMOD_L18F_SetI2C,
		.SetInclk					= DEMOD_L18F_SetInclk,
		.AdcInit					= DEMOD_L18F_AdcInit,

		.SetPll					= NULL,
		.SetADC					= NULL,
		.SAT_DiSeqContol			= NULL, //DEMOD_L18F_SAT_DiSeqContol,

		.Get_Id 					= NULL,
		.RepeaterEnable 			= DEMOD_L18F_RepeaterEnable,
		.SoftwareReset				= DEMOD_L18F_SoftwareReset,
		.Serial_Control 			= NULL,
		.Power_Save 				= NULL, //DEMOD_L18F_Power_Save,
		.StdOperModeContrl			= DEMOD_L18F_StdOperModeContrl,
		.NeverlockScan				= DEMOD_L18F_NeverlockScan,
		.TPOutCLKEnable 			= DEMOD_L18F_TPOutEnable,
		.Set_IF_Frq 				= DEMOD_L18F_Set_IF_Frq,
		.Set_AGCPolarity			= DEMOD_L18F_Set_AGCPolarity,
		.Set_SpectrumCtrl			= NULL,
		.Get_SpectrumStatus 		= NULL,
		.Get_IFAGC					= DEMOD_L18F_Get_IFAGC,
		.Get_OperMode				= DEMOD_L18F_Get_OperMode,
		.Get_NeverLockStatus		= DEMOD_L18F_Get_NeverLockStatus,
		.Get_CarrierFreqOffset		= DEMOD_L18F_Get_CarrierFreqOffset,
		.Get_TPIFStatus 			= NULL,
		.Get_VABER					= DEMOD_L18F_Get_VABER,
		.Get_Packet_Error			= DEMOD_L18F_Get_Packet_Error,
		.Get_BandWidthMode			= DEMOD_L18F_Get_BandWidthMode,
		.Get_QAMMode				= DEMOD_L18F_Get_QAMMode,
		.Get_MseInfo				= DEMOD_L18F_Get_MseInfo,
		.Get_Lock					= DEMOD_L18F_Get_Lock,
		.Get_SysLockTime			= NULL,
		.Get_FecLockTime			= NULL,
		.Set_Frame_resynchronizaiton= NULL,
		.Get_I2C_Handle				= DEMOD_L18F_Get_I2C_Handle,
		.FW_Initialize				= DEMOD_L18F_FW_Initialize,
		.DBB_APB_Read				= DEMOD_L18F_Debug_ATSC_ReadREGvalue,
		.DBB_APB_Write				= DEMOD_L18F_Debug_ATSC_WriteREGvalue,
		.DBB_PDB_Write				= DEMOD_L18F_Debug_PDB_WriteREGvalue,
		.Get_FW_Info				= DEMOD_L18F_Get_FW_PartInfo,
		.Get_Dump					= DEMOD_L18F_Get_Dump,

	#endif



/***************************************************************************************
* DVBT/ DVBC common  function
****************************************************************************************/


/***************************************************************************************
* DVBC function
****************************************************************************************/

	#if 0
		.DVBC_AutoSymbolRateDet 			= DEMOD_L18F_DVBC_AutoSymbolRateDet,
		.DVBC_IsSymbolRateAuto				= DEMOD_L18F_DVBC_IsSymbolRateAuto,
		.DVBC_IsQammodeAutoDet				= DEMOD_L18F_DVBC_IsQammodeAutoDet,
		.DVBC_Set_DefaultRegisterValue		= DEMOD_L18F_DVBC_Set_DefaultRegisterValue,
		.DVBC_Set_Config_auto				= DEMOD_L18F_DVBC_Set_Config_auto,
		.DVBC_Set_QamMode					= DEMOD_L18F_DVBC_Set_QamMode,
		.DVBC_Set_NeverLockWaitTime 		= DEMOD_L18F_DVBC_Set_NeverLockWaitTime,
		.DVBC_Get_SymbolRateDetect			= DEMOD_L18F_DVBC_Get_SymbolRateDetect,
		.DVBC_Get_SymbolRateStatus			= DEMOD_L18F_DVBC_Get_SymbolRateStatus,
		.DVBC_Get_QamModeDetectStatus		= DEMOD_L18F_DVBC_Get_QamModeDetectStatus,
		.DVBC_Get_DvbInfo					= DEMOD_L18F_DVBC_Get_DvbInfo,

		.DVBC_Obtaining_Signal_Lock 		= DEMOD_L18F_DVBC_Obtaining_Signal_Lock,
		.DVBC_Monitoring_Signal_Lock		= DEMOD_L18F_DVBC_Monitoring_Signal_Lock,

	#else
		.DVBC_AutoSymbolRateDet 			= DEMOD_L18F_DVBC_AutoSymbolRateDet,
		.DVBC_IsSymbolRateAuto			= DEMOD_L18F_DVBC_IsSymbolRateAuto,
		.DVBC_IsQammodeAutoDet			= DEMOD_L18F_DVBC_IsQammodeAutoDet,
		.DVBC_Set_DefaultRegisterValue		= DEMOD_L18F_DVBC_Set_DefaultRegisterValue,
		.DVBC_Set_Config_auto			= NULL,
		.DVBC_Set_QamMode				= DEMOD_L18F_DVBC_Set_QamMode,
		.DVBC_Set_NeverLockWaitTime 		= NULL,
		.DVBC_Get_SymbolRateDetect		= DEMOD_L18F_DVBC_Get_SymbolRateDetect,
		.DVBC_Get_SymbolRateStatus		= DEMOD_L18F_DVBC_Get_SymbolRateStatus,
		.DVBC_Get_QamModeDetectStatus	= DEMOD_L18F_DVBC_Get_QamModeDetectStatus,
		.DVBC_Get_DvbInfo				= NULL,

		.DVBC_Obtaining_Signal_Lock 		= DEMOD_L18F_DVBC_Obtaining_Signal_Lock,
		.DVBC_Monitoring_Signal_Lock		= DEMOD_L18F_DVBC_Monitoring_Signal_Lock,
		.DVB_SW_Init						= DEMOD_L18F_DVB_SW_Init,

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
		.DVBT_Set_DefaultRegisterValue		= DEMOD_L18F_DVBT_Set_DefaultRegisterValue,
		.DVBT_Set_Config_auto				= DEMOD_L18F_DVBT_Set_Config_auto,
		.DVBT_Set_PartialConfig 			= DEMOD_L18F_DVBT_Set_PartialConfig,
		.DVBT_Set_FullConfig				= DEMOD_L18F_DVBT_Set_FullConfig,
		.DVBT_Set_NeverLockWaitTime 		= DEMOD_L18F_DVBT_Set_NeverLockWaitTime,
		.DVBT_Get_DelaySpreadStatus 		= DEMOD_L18F_DVBT_Get_DelaySpreadStatus,
		.DVBT_Get_Hierach_HPSel 			= DEMOD_L18F_DVBT_Get_Hierach_HPSel,
		.DVBT_Get_FFTMode					= DEMOD_L18F_DVBT_Get_FFTMode,
		.DVBT_Get_GuradIntervalMode 		= DEMOD_L18F_DVBT_Get_GuradIntervalMode,
		.DVBT_Get_HierachyMode				= DEMOD_L18F_DVBT_Get_HierachyMode,
		.DVBT_Get_LpCoderRate				= DEMOD_L18F_DVBT_Get_LpCoderRate,
		.DVBT_Get_HpCoderRate				= DEMOD_L18F_DVBT_Get_HpCoderRate,
		.DVBT_Get_CellId					= DEMOD_L18F_DVBT_Get_CellId,
		.DVBT_Get_TpsInfo					= DEMOD_L18F_DVBT_Get_TpsInfo,
		.DVBT_Get_TotalInfo 				= DEMOD_L18F_DVBT_Get_TotalInfo,
		.DVBT_Get_IFO_LOCK					= DEMOD_L18F_DVBT_Get_IFO_LOCK,
		.DVBT_Get_CochanDetIndicator		= NULL, //DEMOD_L18F_DVBT_Get_CochanDetIndicator,
		.DVBT_EqualizereReset				= DEMOD_L18F_DVBT_EqualizereReset,

		.DVBT_Obtaining_Signal_Lock 		= DEMOD_L18F_DVBT_Obtaining_Signal_Lock,
		.DVBT_Monitoring_Signal_Lock		= DEMOD_L18F_DVBT_Monitoring_Signal_Lock,

	#else
		.DVBT_Set_DefaultRegisterValue		= NULL,
		.DVBT_Set_Config_auto				= DEMOD_L18F_DVBT_Set_Config_auto,
		.DVBT_Set_PartialConfig 			= DEMOD_L18F_DVBT_Set_PartialConfig,
		.DVBT_Set_FullConfig				= NULL,
		.DVBT_Set_NeverLockWaitTime 		= NULL,
		.DVBT_Get_DelaySpreadStatus 		= NULL,
		.DVBT_Get_Hierach_HPSel 			= DEMOD_L18F_DVBT_Get_Hierach_HPSel,
		.DVBT_Get_FFTMode				= DEMOD_L18F_DVBT_Get_FFTMode,
		.DVBT_Get_GuradIntervalMode 		= DEMOD_L18F_DVBT_Get_GuradIntervalMode,
		.DVBT_Get_HierachyMode			= DEMOD_L18F_DVBT_Get_HierachyMode,
		.DVBT_Get_LpCoderRate			= DEMOD_L18F_DVBT_Get_LpCoderRate,
		.DVBT_Get_HpCoderRate			= DEMOD_L18F_DVBT_Get_HpCoderRate,
//		.DVBT_Get_CellId					= DEMOD_L18F_Get_Id,
		.DVBT_Get_TpsInfo				= DEMOD_L18F_DVBT_Get_TpsInfo,
		.DVBT_Get_TotalInfo 				= DEMOD_L18F_DVBT_Get_TotalInfo,
		.DVBT_Get_IFO_LOCK				= NULL,
		.DVBT_Get_CochanDetIndicator		= NULL, //DEMOD_L18F_DVBT_Get_CochanDetIndicator,
		.DVBT_EqualizereReset				= NULL,

		.DVBT_Obtaining_Signal_Lock 		= DEMOD_L18F_DVBT_Obtaining_Signal_Lock,
		.DVBT_Monitoring_Signal_Lock		= DEMOD_L18F_DVBT_Monitoring_Signal_Lock,


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
		.DVBT2_Set_DefaultRegisterValue	= NULL,
		.DVBT2_Set_Config_auto			= DEMOD_L18F_DVBT2_Set_Config_auto,
		.DVBT2_Set_PartialConfig 			= DEMOD_L18F_DVBT2_Set_PartialConfig,
		.DVBT2_Set_FullConfig				= NULL,
		.DVBT2_Set_NeverLockWaitTime 		= NULL,
		.DVBT2_Get_DelaySpreadStatus 		= NULL,
		.DVBT2_Get_FFTMode				= DEMOD_L18F_DVBT2_Get_FFTMode,
		.DVBT2_Get_GuradIntervalMode 		= DEMOD_L18F_DVBT2_Get_GuradIntervalMode,
		.DVBT2_Get_CoderRate				= DEMOD_L18F_DVBT2_Get_CoderRate,
		.DVBT2_Get_PlpInfo				= DEMOD_L18F_DVBT2_Get_PlpInfo,
		.DVBT2_Get_multiPLP_ID			= DEMOD_L18F_DVBT2_Get_multiPLP_ID,
		.DVBT2_Get_TotalInfo 				= DEMOD_L18F_DVBT2_Get_TotalInfo,
		.DVBT2_Obtaining_Signal_Lock 		= DEMOD_L18F_DVBT2_Obtaining_Signal_Lock,
		.DVBT2_Monitoring_Signal_Lock		= DEMOD_L18F_DVBT2_Monitoring_Signal_Lock,
		.DVBT2_Set_MemSconfig			= DEMOD_L18F_DVBT2_Set_MemSconfig,

	#endif





/***************************************************************************************
* VSB/ QAM/ ISDBT common  function
****************************************************************************************/



/***************************************************************************************
* VSB function
****************************************************************************************/

	#if 0
		.VSB_Set_DefaultRegisterValue		= DEMOD_L18F_VSB_Set_DefaultRegisterValue,
		.VSB_Set_NeverLockWaitTime			= DEMOD_L18F_VSB_Set_NeverLockWaitTime,
		.VSB_CochannelExist 				= DEMOD_L18F_VSB_CochannelExist,
		.VSB_PreMonitor 					= DEMOD_L18F_VSB_PreMonitor,
		.VSB_Monitor						= DEMOD_L18F_VSB_Monitor,
		.VSB_Get_MSEdynStatus				= DEMOD_L18F_VSB_Get_MSEdynStatus,
		.VSB_Get_TotalInfo					= DEMOD_L18F_VSB_Get_TotalInfo,

		.VSB_Obtaining_Signal_Lock			= DEMOD_L18F_VSB_Obtaining_Signal_Lock,
		.VSB_Monitoring_Signal_Lock 		= DEMOD_L18F_VSB_Monitoring_Signal_Lock,

	#else
		.VSB_Set_DefaultRegisterValue		= NULL,
		.VSB_Set_NeverLockWaitTime			= NULL,
		.VSB_CochannelExist 				= NULL,
		.VSB_PreMonitor 					= NULL,
		.VSB_Monitor						= NULL,
		.VSB_Get_MSEdynStatus				= NULL,
		.VSB_Get_TotalInfo					= NULL,

		.VSB_Obtaining_Signal_Lock			= DEMOD_L18F_VSB_Obtaining_Signal_Lock,
		.VSB_Monitoring_Signal_Lock 		= DEMOD_L18F_VSB_Monitoring_Signal_Lock,
		.ATSC_SW_Init						= DEMOD_L18F_ATSC_SW_Init,
		.VSB_SetDemod_Simple				= DEMOD_L18F_LGDBB_VSB_SetDemod_Simple,
	#endif


/***************************************************************************************
* QAM function
****************************************************************************************/

	#if 0
		.QAM_SoftwareResetFEC				= DEMOD_L18F_QAM_SoftwareResetFEC,
		.QAM_Monitor						= DEMOD_L18F_QAM_Monitor,
		.QAM_ModeAutoDetection				= DEMOD_L18F_QAM_ModeAutoDetection,
		.QAM_64Mode 						= DEMOD_L18F_QAM_64Mode,
		.QAM_256Mode						= DEMOD_L18F_QAM_256Mode,
		.QAM_Set_DefaultRegisterValue		= DEMOD_L18F_QAM_Set_DefaultRegisterValue,
		.QAM_Set_NeverLockWaitTime			= DEMOD_L18F_QAM_Set_NeverLockWaitTime,

		.QAM_Get_TotalInfo					= DEMOD_L18F_QAM_Get_TotalInfo,

		.QAM_Obtaining_Signal_Lock			= DEMOD_L18F_QAM_Obtaining_Signal_Lock,
		.QAM_Monitoring_Signal_Lock 		= DEMOD_L18F_QAM_Monitoring_Signal_Lock,
		.QAM_EQ_Signal_Detector 			= DEMOD_L18F_QAM_EQ_Signal_Detector,

	#else
		.QAM_SoftwareResetFEC				= NULL,
		.QAM_Monitor						= NULL,
		.QAM_ModeAutoDetection				= NULL,
		.QAM_64Mode 						= NULL,
		.QAM_256Mode						= NULL,
		.QAM_Set_DefaultRegisterValue		= DEMOD_L18F_QAM_Set_DefaultRegisterValue,
		.QAM_Set_NeverLockWaitTime			= NULL,

		.QAM_Get_TotalInfo					= NULL,

		.QAM_Obtaining_Signal_Lock			= DEMOD_L18F_QAM_Obtaining_Signal_Lock,
		.QAM_Monitoring_Signal_Lock 		= DEMOD_L18F_QAM_Monitoring_Signal_Lock,
		.QAM_EQ_Signal_Detector 			= NULL,

	#endif




/***************************************************************************************
* ISDBT function
****************************************************************************************/
	#if 0
		.ISDBT_Set_DefaultRegisterValue 	= DEMOD_L18F_ISDBT_Set_DefaultRegisterValue,
		.ISDBT_Set_Config_auto		 		= DEMOD_L18F_ISDBT_Set_Config_auto,
		.ISDBT_Set_PartialConfig	   		= DEMOD_L18F_ISDBT_Set_PartialConfig,
		.ISDBT_Set_FullConfig				= DEMOD_L18F_ISDBT_Set_FullConfig,
		.ISDBT_Set_NeverLockWaitTime	   	= DEMOD_L18F_ISDBT_Set_NeverLockWaitTime,
		.ISDBT_Get_DelaySpreadStatus	   	= DEMOD_L18F_ISDBT_Get_DelaySpreadStatus,
		.ISDBT_Get_FFTMode		 			= DEMOD_L18F_ISDBT_Get_FFTMode,
		.ISDBT_Get_GuradIntervalMode	   	= DEMOD_L18F_ISDBT_Get_GuradIntervalMode,
		.ISDBT_Get_TMCCInfo 	  			= DEMOD_L18F_ISDBT_Get_TMCCInfo,
		.ISDBT_Get_TotalInfo	   			= DEMOD_L18F_ISDBT_Get_TotalInfo,
		.ISDBT_Get_IFO_LOCK 	  			= DEMOD_L18F_ISDBT_Get_IFO_LOCK,
		.ISDBT_Get_CochanDetIndicator		= DEMOD_L18F_ISDBT_Get_CochanDetIndicator,
		.ISDBT_EqualizereReset		 		= DEMOD_L18F_ISDBT_EqualizereReset,

		.ISDBT_Obtaining_Signal_Lock		= DEMOD_L18F_ISDBT_Obtaining_Signal_Lock,
		.ISDBT_Monitoring_Signal_Lock 		= DEMOD_L18F_ISDBT_Monitoring_Signal_Lock,
		.ISDBT_Set_MemSconfig				= DEMOD_L18F_ISDBT_Set_MemSconfig,

	#else
		.ISDBT_Set_DefaultRegisterValue 	= NULL,
		.ISDBT_Set_Config_auto		 		= NULL,
		.ISDBT_Set_PartialConfig	   		= NULL,
		.ISDBT_Set_FullConfig				= NULL,
		.ISDBT_Set_NeverLockWaitTime	   	= NULL,
		.ISDBT_Get_DelaySpreadStatus	   	= NULL,
		.ISDBT_Get_FFTMode		 			= DEMOD_L18F_ISDBT_Get_FFTMode,
		.ISDBT_Get_GuradIntervalMode	   	= DEMOD_L18F_ISDBT_Get_GuradIntervalMode,
		.ISDBT_Get_TMCCInfo 	  			= DEMOD_L18F_ISDBT_Get_TMCCInfo,
		.ISDBT_Get_TotalInfo	   			= NULL,
		.ISDBT_Get_IFO_LOCK 	  			= NULL,
		.ISDBT_Get_CochanDetIndicator		= NULL,
		.ISDBT_EqualizereReset		 		= NULL,

		.ISDBT_Obtaining_Signal_Lock		= DEMOD_L18F_ISDBT_Obtaining_Signal_Lock,
		.ISDBT_Monitoring_Signal_Lock 		= DEMOD_L18F_ISDBT_Monitoring_Signal_Lock,
		.ISDBT_Set_MemSconfig				= DEMOD_L18F_ISDBT_Set_MemSconfig,
		.ISDBT_GetEmergencyAlertFlagStatus	= DEMOD_L18F_ISDBT_GetEmergencyAlertFlagStatus,

	#endif


/***********************************************************************************
* DVBS function
************************************************************************************/

	.DVBS_Set_DefaultRegisterValue			= NULL,
	.DVBS_Set_Config_auto					= DEMOD_L18F_DVBS_Set_Config_auto,
	.DVBS_Set_PartialConfig				= NULL,
	.DVBS_Set_FullConfig					= DEMOD_L18F_DVBS_Set_FullConfig,
	.DVBS_Get_CoderRate					= DEMOD_L18F_DVBS_Get_CoderRate,
	.DVBS_Get_SymbolRate				= DEMOD_L18F_DVBS_Get_SymbolRate,
	.DVBS_Get_TotalInfo					= DEMOD_L18F_DVBS_Get_TotalInfo,
	.DVBS_Set_DiseqcToneMessageCtrl		= DEMOD_L18F_DVBS_Set_DiseqcToneMessageCtrl,
	.DVBS_Set_EnvelopModeCtrl				= NULL,
	.DVBS_Get_BlindInfo					= DEMOD_L18F_DVBS_Get_BlindInfo,
	.DVBS_Set_BlindSpectrumMode			= NULL,

	.DVBS_Obtaining_Signal_Lock			= DEMOD_L18F_DVBS_Obtaining_Signal_Lock,
	.DVBS_Monitoring_Signal_Lock			= DEMOD_L18F_DVBS_Monitoring_Signal_Lock,
	.DVBS_Set_SpectrumModeConfig			= NULL,

/***********************************************************************************
* DVBS2 function
************************************************************************************/

	.DVBS2_Set_DefaultRegisterValue		= NULL,
	.DVBS2_Set_Config_auto				= DEMOD_L18F_DVBS2_Set_Config_auto,
	.DVBS2_Set_PartialConfig				= NULL,
	.DVBS2_Set_FullConfig					= DEMOD_L18F_DVBS2_Set_FullConfig,
	.DVBS2_Get_CoderRate					= DEMOD_L18F_DVBS2_Get_CoderRate,
	.DVBS2_Get_Pilot						= DEMOD_L18F_DVBS2_Get_Pilot,
	.DVBS2_Get_SymbolRate				= DEMOD_L18F_DVBS2_Get_SymbolRate,
	.DVBS2_Get_TotalInfo					= DEMOD_L18F_DVBS2_Get_TotalInfo,
	.DVBS2_Set_MemSconfig				= DEMOD_L18F_DVBS2_Set_MemSconfig,

	.DVBS2_Obtaining_Signal_Lock			= DEMOD_L18F_DVBS2_Obtaining_Signal_Lock,
	.DVBS2_Monitoring_Signal_Lock			= DEMOD_L18F_DVBS2_Monitoring_Signal_Lock,


/***********************************************************************************
* DVBS/S2 function
************************************************************************************/
	.DVBSX_BlindScan_Init					= DEMOD_L18F_DVBSX_BlindScan_Init,
	.DVBSX_BlindScan_End					= DEMOD_L18F_DVBSX_BlindScan_End,
	.DVBSX_Get_TunerFreq					= DEMOD_L18F_DVBSX_Get_TunerFreq,
	.DVBSX_Get_OffsetFreq					= DEMOD_L18F_DVBSX_Get_OffsetFreq,
	.DVBSX_SymbolRate_Detec				= DEMOD_L18F_DVBSX_SymbolRate_Detec,
	.DVBSX_BlindLock_Loop				= DEMOD_L18F_DVBSX_BlindLock_Loop,	
	.DVBSX_Get_Nextfreq_Status			= DEMOD_L18F_DVBSX_Get_Nextfreq_Status,


/***************************************************************************************
* ABB  function
****************************************************************************************/

#if 1
		.ADEMOD_Demod_Open				 	= DEMOD_L18F_ANALOG_Demod_Open,
		.ADEMOD_Init						= DEMOD_L18F_ANALOG_Init,
		.ADEMOD_Set_IF_Frq					= DEMOD_L18F_ANALOG_Set_IF_Frq,
		.ADEMOD_SoftwareReset				= DEMOD_L18F_ANALOG_SoftReset,
		.ADEMOD_Set_AftRange 				= DEMOD_L18F_ANALOG_Set_AftRange,

		.ADEMOD_ResetHW						= DEMOD_L18F_ANALOG_ResetHW,
		.ADEMOD_SetI2C						= DEMOD_L18F_ANALOG_SetI2C,
		.ADEMOD_Set_AbbMode 				= NULL, //DEMOD_L18F_ANALOG_Set_AbbMode,
		.ADEMOD_Set_WorkAround	 			= NULL,
		.ADEMOD_Set_CvbsRateConversion		= DEMOD_L18F_ANALOG_Set_CvbsRateConversion,
		.ADEMOD_Set_HighCvbsRateOffset		= DEMOD_L18F_ANALOG_Set_HighCvbsRateOffset,
		.ADEMOD_Set_ClampingCtrl			= DEMOD_L18F_ANALOG_Set_ClampingCtrl,
		.ADEMOD_Set_SifCtrl					= DEMOD_L18F_ANALOG_Set_SifCtrl,
		.ADEMOD_Set_CvbsDecCtrl				= DEMOD_L18F_ANALOG_Set_CvbsDecCtrl,
		.ADEMOD_Set_SifPathCtrl				= DEMOD_L18F_ANALOG_Set_SifPathCtrl,
		.ADEMOD_Set_SpectrumInv				= DEMOD_L18F_ANALOG_Set_SpectrumInv,
		.ADEMOD_Set_SpecialSifData 			= DEMOD_L18F_ANALOG_ChangeFilter4SIF,


		.ADEMOD_Obtaining_Signal_Lock		= DEMOD_L18F_ANALOG_Obtaining_Signal_Lock,
		.ADEMOD_Monitoring_Signal_Lock 		= DEMOD_L18F_ANALOG_Monitoring_Signal_Lock,

		.ADEMOD_Dbg_Get_RegDump				= DEMOD_L18F_ANALOG_Dbg_Get_RegDump,
		.ADEMOD_Dbg_Set_RegValue 			= DEMOD_L18F_ANALOG_Dbg_Set_RegisterValue,
		.ADEMOD_Dbg_Set_SmartTune 			= DEMOD_L18F_ANALOG_Dbg_SmartTune,
		.ADEMOD_Dbg_Get_RegValue			= DEMOD_L18F_ANALOG_Dbg_Get_RegisterValue,
		.ADEMOD_Dbg_TestFunctions 			= DEMOD_L18F_ANALOG_Dbg_TestFunctions,

		.ADEMOD_Preset_Set 					= DEMOD_L18F_Analog_Preset_Set,
		.ADEMOD_Demodulate 					= DEMOD_L18F_Analog_Demodulate,
		.ADEMOD_Parameter_Set 				= DEMOD_L18F_Analog_Parameter_Set,
		.ADEMOD_Parameter_Get 				= DEMOD_L18F_Analog_Parameter_Get,
		.ADEMOD_AGC_Set 					= DEMOD_L18F_Analog_AGC_Set,
		.ADEMOD_AGC_Get 					= DEMOD_L18F_Analog_AGC_Get,
		.ADEMOD_ChanScan_Set 				= DEMOD_L18F_Analog_ChanScan_Set,
		.ADEMOD_SleepMode_Set 				= DEMOD_L18F_Analog_SleepMode_Set,
		.ADEMOD_SleepMode_Get 				= DEMOD_L18F_Analog_SleepMode_Get,
		.ADEMOD_HostI2C_Write 				= DEMOD_L18F_Analog_HostI2C_Write,
		.ADEMOD_HostI2C_Read 				= DEMOD_L18F_Analog_HostI2C_Read,
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

const static	LX_DEMOD_CFG_T 		g_demod_cfg_l18f =
{

};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get L9 specific configuration
 *
 *  @return LX_DEMOD_CFG_T
 */
const LX_DEMOD_CFG_T*   DEMOD_L18F_GetCfg(void)
{
    return &g_demod_cfg_l18f;
}

void	DEMOD_L18F_InitHAL( DEMOD_HAL_T*	hal )
{
#if 0
if(NULL==gpRegL18FCOMMON)
{
	gpRegL18FCOMMON	=  (LX_DEMOD_COMMON_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_COMMON_REG_T));
}

if(NULL==gpRegL18FSYNC)
{
	gpRegL18FSYNC	=  (LX_DEMOD_SYNC_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_SYNC_REG_T));
}

if(NULL==gpRegL18FSYNC2ND)
{
	gpRegL18FSYNC2ND =  (LX_DEMOD_SYNC2ND_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_SYNC2ND_REG_T));
}

if(NULL==gpRegL18FEQ_V)
{
	gpRegL18FEQ_V	=  (LX_DEMOD_EQ_V_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_EQ_V_REG_T));
}

if(NULL==gpRegL18FEQ_DI)
{
	gpRegL18FEQ_DI	=  (LX_DEMOD_EQ_DI_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_EQ_DI_REG_T));
}

if(NULL==gpRegL18FCQS)
{
	gpRegL18FCQS 	=  (LX_DEMOD_EQ_CQS_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_EQ_CQS_REG_T));
}

if(NULL==gpRegL18FFEC)
{
	gpRegL18FFEC 	=  (LX_DEMOD_FEC_REG_T*)OS_KMalloc(sizeof(LX_DEMOD_FEC_REG_T));
}

#endif


	memcpy( hal, &g_demod_hal_l18f, sizeof(DEMOD_HAL_T));
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


