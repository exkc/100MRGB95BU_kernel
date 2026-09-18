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
 *  driver interface header for demod device. ( used only within kdriver )
 *	demod device will teach you how to make device driver with new platform.
 *
 *  @author		jeongpil.yun (jeongpil.yun@lge.com)
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#ifndef	_DEMOD_HAL_H_
#define	_DEMOD_HAL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "demod_kapi.h"
#include "demod_module.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef UINT32			LX_ADEMOD_Result;	   /*  return codes 				   */

typedef	struct
{
	const LX_DEMOD_CFG_T*	(*GetCfg)		(void);

/***********************************************************************************
* DVBT/ DVBC/ VSB/ QAM/ ISDBT  common  function
************************************************************************************/

	int (*ResetHW)						(void);
	int (*SetI2C)						(void);
	int (*SetInclk)						(LX_DEMOD_INCLK_SEL_T *inclk);
	int (*AdcInit)						(void);
	int (*SetMemCfg)					(UINT32 staddr, UINT32 size);

	int (*OperModeReset)					(LX_DEMOD_OPER_MODE_T operMode);
	int (*SetPll)						(LX_DEMOD_OPER_MODE_T operMode);
	int (*SetADC)						(LX_DEMOD_OPER_MODE_T operMode);
	int (*SAT_DiSeqContol)					(BOOLEAN OnOff);

	int (*Get_Id)						(UINT16 *pId);
	int (*RepeaterEnable)					(BOOLEAN bEnable);
	int (*SoftwareReset)					(void);
	int (*Serial_Control)					(BOOLEAN bEnable);
	int (*Power_Save)					(BOOLEAN bEnable);
	int (*APB_AccessControl)				(BOOLEAN bEnable);
	int (*StdOperModeContrl)				(LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr);
	int (*NeverlockScan)					(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock);
	int (*TPOutCLKEnable)					(BOOLEAN bEnable);
	int (*Set_IF_Frq)					(UINT32 ifFrq);
	int (*Set_AGCPolarity)					(LX_DEMOD_AGC_POLAR_T agcPola);
	int (*Set_SpectrumCtrl)					(BOOLEAN bAutoEnable, BOOLEAN bSpecInvEnable);
	int (*Get_SpectrumStatus)				(LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv);
	int (*Get_IFAGC)					(UINT16 *pIfAgc);
	int (*Get_OperMode)					(LX_DEMOD_OPER_MODE_T *pOperMode);
	int (*Get_NeverLockStatus)				(LX_DEMOD_OPER_MODE_T scanMode, LX_DEMOD_LOCK_STATE_T *pNeverLockStatus);
	int (*Get_CarrierFreqOffset)				(SINT32 *pFreqOff);
	int (*Get_TPIFStatus)					(BOOLEAN *pbEnable);
	int (*Get_VABER)					(UINT32 *pVber);
	int (*Get_Packet_Error)					(UINT32 *pError);
	int (*Get_BandWidthMode)				(LX_DEMOD_BWMODE_T *ChannelBW );
	int (*Get_QAMMode)					(LX_DEMOD_RF_MODE_T *pQamMode );
	int (*Get_MseInfo)					(LX_DEMOD_MSE_T *pSigMse);
	int (*Get_Lock)						(LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState);
	int (*Get_SysLockTime)					(UINT16 *pSyslocktime);
	int (*Get_FecLockTime)					(UINT16 *pFeclocktime);
	int (*Set_Frame_resynchronizaiton)			(BOOLEAN bEnable);
	int (*Get_I2C_Handle)					(UINT8 portI2C, UINT16 deviceID);
	int (*FW_Initialize)					(void);
	int (*SAT_FW_Initialize)				(void);
	int (*ALL_FW_Initialize)				(void);
	int (*FW_Configuration_Initialize)			(LX_DEMOD_OPER_MODE_T operMode);
	int (*DBB_I2C_Read)					(UINT16 address, UINT16 nBytes, UINT8 *pData);
	int (*DBB_I2C_Write)					(UINT16 address, UINT16 nBytes, UINT8 *pData);
	int (*DBB_APB_DEBUG_Read)				(UINT16 address, UINT32 *pData);
	int (*DBB_APB_Read)					(UINT16 address, UINT32 *pData);
	int (*DBB_APB_Write) 					(UINT16 address, UINT32 *pData);
	int (*DBB_PDB_Write) 					(UINT32 value);
	int (*Get_FW_Info)					(UINT32 *pFW_Info);
	int (*Get_Dump)						(void);
	int (*Get_Total_Signal_Infomation)			(LX_DEMOD_SIGNAL_TOTAL_T *pSignalStatus);
	int (*Get_Cfg_Information)				(LX_DEMOD_SIGNAL_TUNE_CFG_T *pSignalStatus);
	int (*DVB_Set_MemSconfig) 				(void);
	int (*DVB_C_reset)					(void);
	int (*CountryGrpSetting)				(BOOLEAN bEnable);
	int (*GetTsClkRate)					(UINT32 *demodTsClkRate);
	int (*ADC_Enable) 					(void);

/***********************************************************************************
* DVBT/ DVBC common  function
************************************************************************************/

/***********************************************************************************
* DVBC function
************************************************************************************/

	int (*DVBC_AutoSymbolRateDet)				(LX_DEMOD_SYMRDET_MODE_T symrateMode, UINT16 SymbolRate);
	int (*DVBC_IsSymbolRateAuto)				(BOOLEAN *bAuto);
	int (*DVBC_IsQammodeAutoDet)				(BOOLEAN *bAutoQam);
	int (*DVBC_Set_DefaultRegisterValue)			(void);
	int (*DVBC_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DVBC_Set_QamMode) 				(LX_DEMOD_RF_MODE_T constel);
	int (*DVBC_Set_NeverLockWaitTime)			(UINT32 waitMs);
	int (*DVBC_Get_SymbolRateDetect)			(UINT16 *pSymbolRate);
	int (*DVBC_Get_SymbolRateStatus)			(LX_DEMOD_SYMBOLRATE_STATE_T *pSymbolRateDet);
	int (*DVBC_Get_QamModeDetectStatus)			(LX_DEMOD_QAMMODE_STATE_T *pQamModeDet);
	int (*DVBC_Get_DvbInfo)					(void);

	int (*DVBC_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*DVBC_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);

	int (*DVB_SW_Init)					(void);

/***********************************************************************************
* DVBC2 function
************************************************************************************/

	int (*DVBC2_IsQammodeAutoDet)				(BOOLEAN *bAutoQam);
	int (*DVBC2_Set_DefaultRegisterValue)			(void);
	int (*DVBC2_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DVBC2_Set_PartialConfig)				(LX_DEMOD_DVBC2_CONFIG_T *pDvbc2ConfigParam);
	int (*DVBC2_Set_FullConfig)				(LX_DEMOD_DVBC2_CONFIG_T *pDvbt2ConfigParam);
	int (*DVBC2_Set_QamMode) 				(UINT8 constel);
	int (*DVBC2_Set_NeverLockWaitTime)			(UINT32 waitMs);
	int (*DVBC2_Set_StartFrequency)				(UINT32 frequency);
	int (*DVBC2_Get_QamModeDetectStatus)			(LX_DEMOD_QAMMODE_STATE_T *pQamModeDet);
	int (*DVBC2_Get_multiPLP_ID)				(LX_DEMOD_DVBC2_MULTI_PLP_INFO_T *pParamMultiPLPInfo);
	int (*DVBC2_Get_DvbInfo)				(void);

	int (*DVBC2_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*DVBC2_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);

/***********************************************************************************
* DVBT function
************************************************************************************/

	int (*DVBT_Set_DefaultRegisterValue)			(LX_DEMOD_BWMODE_T band);
	int (*DVBT_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DVBT_Set_PartialConfig)				(LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam);
	int (*DVBT_Set_FullConfig)				(LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam);
	int (*DVBT_Set_NeverLockWaitTime)			(UINT32 waitMs);
	int (*DVBT_Get_DelaySpreadStatus)			(UINT16 *pDelaySpread);
	int (*DVBT_Get_Hierach_HPSel)				(BOOLEAN *pBSetHp );
	int (*DVBT_Get_FFTMode)					(LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
	int (*DVBT_Get_GuradIntervalMode)			(LX_DEMOD_GIMODE_T *pGIMode );
	int (*DVBT_Get_HierachyMode)				(LX_DEMOD_DVB_TPS_HIERACHY_T *pHierachMode );
	int (*DVBT_Get_LpCoderRate)				(LX_DEMOD_CODERATE_T *pLpCodeRate );
	int (*DVBT_Get_HpCoderRate)				(LX_DEMOD_CODERATE_T *pHpCodeRate );
	int (*DVBT_Get_CellId)					(UINT8 *pCellIDLength, UINT16 *cell_id);
	int (*DVBT_Get_TpsInfo)					(LX_DEMOD_DVBT_CONFIG_T *pTpsParams);
	int (*DVBT_Get_TotalInfo)				(void);
	int (*DVBT_Get_IFO_LOCK)				(BOOLEAN *pIfoLock);
	int (*DVBT_Get_CochanDetIndicator)			(BOOLEAN *pDetStatus);
	int (*DVBT_EqualizereReset)				(void);
	int (*DVBT_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*DVBT_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);

/***********************************************************************************
* DVBT2 function
************************************************************************************/

	int (*DVBT2_Set_DefaultRegisterValue)			(LX_DEMOD_BWMODE_T band);
	int (*DVBT2_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DVBT2_Set_PartialConfig)				(LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam);
	int (*DVBT2_Set_FullConfig)				(LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam);
	int (*DVBT2_Set_NeverLockWaitTime)			(UINT32 waitMs);
	int (*DVBT2_Get_DelaySpreadStatus)			(UINT16 *pDelaySpread);
	int (*DVBT2_Get_FFTMode)				(LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
	int (*DVBT2_Get_GuradIntervalMode)			(LX_DEMOD_GIMODE_T *pGIMode );
	int (*DVBT2_Get_CoderRate)				(LX_DEMOD_CODERATE_T *pCodeRate );
	int (*DVBT2_Get_multiPLP_ID)				(LX_DEMOD_DVBT2_MULTI_PLP_INFO_T *pParamMultiPLPInfo);
	int (*DVBT2_Get_PlpInfo)				(LX_DEMOD_DVBT2_CONFIG_T *pPlpParams);
	int (*DVBT2_Get_TotalInfo)				(void);
	int (*DVBT2_Set_MemSconfig)				(void);
	int (*DVBT2_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*DVBT2_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);

/***********************************************************************************
* VSB/ QAM/ ISDBT common  function
************************************************************************************/

/***********************************************************************************
* VSB function
************************************************************************************/

	int (*VSB_Set_DefaultRegisterValue)			(void);
	int (*VSB_Set_NeverLockWaitTime)			(UINT32 waitMs);
	int (*VSB_CochannelExist)				(BOOLEAN *pCochannel);
	int (*VSB_PreMonitor)					(void);
	int (*VSB_Monitor)					(DEMOD_CTX_T *pDemodInfo);
	int (*VSB_Get_MSEdynStatus)				(BOOLEAN *pbEnable);
	int (*VSB_Get_TotalInfo)				(void);

	int (*VSB_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*VSB_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);

	int (*ATSC_SW_Init)					(void);
	int (*VSB_SetDemod_Simple)				(void);
	int (*LGDBB_VSB_SetDemod)				(DEMOD_CTX_T *pDemodInfo);

/***********************************************************************************
* QAM function
************************************************************************************/

	int (*QAM_SoftwareResetFEC)				(void);
	int (*QAM_Monitor)					(void);
	int (*QAM_ModeAutoDetection)				(BOOLEAN bEnable);
	int (*QAM_64Mode)					(void);
	int (*QAM_256Mode)					(void);
	int (*QAM_Set_DefaultRegisterValue)			(void);
	int (*QAM_Set_NeverLockWaitTime)			(UINT32 waitMs);
	int (*QAM_Get_TotalInfo)				(void);
	int (*QAM_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*QAM_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*QAM_EQ_Signal_Detector)				(BOOLEAN OnOff);
	int (*LGDBB_QAM_SetDemod)				(DEMOD_CTX_T *pDemodInfo);

/***********************************************************************************
* ISDBT function
************************************************************************************/

	int (*ISDBT_Set_DefaultRegisterValue)			(void);
	int (*ISDBT_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*ISDBT_Set_PartialConfig)				(LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam);
	int (*ISDBT_Set_FullConfig)				(LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam);
	int (*ISDBT_Set_NeverLockWaitTime)			(UINT32 waitMs);
	int (*ISDBT_Get_DelaySpreadStatus)			(UINT16 *pDelaySpread);
	int (*ISDBT_Get_FFTMode)				(LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
	int (*ISDBT_Get_GuradIntervalMode)			(LX_DEMOD_GIMODE_T *pGIMode );
	int (*ISDBT_Get_TMCCInfo)				(LX_DEMOD_ISDBT_TMCC_CONFIG_T *pTmccParams);
	int (*ISDBT_Get_TotalInfo)				(void);
	int (*ISDBT_Get_IFO_LOCK)				(BOOLEAN *pIfoLock);
	int (*ISDBT_Get_CochanDetIndicator)			(BOOLEAN *pDetStatus);
	int (*ISDBT_EqualizereReset)				(void);
	int (*ISDBT_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*ISDBT_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*ISDBT_Set_MemSconfig)				(void);
	int (*ISDBT_GetEmergencyAlertFlagStatus)		(BOOLEAN *pEalarm);


/***********************************************************************************
* DVBS function
************************************************************************************/

	int (*DVBS_Set_DefaultRegisterValue)			(void);
	int (*DVBS_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DVBS_Set_PartialConfig)				(LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam);
	int (*DVBS_Set_FullConfig)				(LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam);
	int (*DVBS_Get_CoderRate)				(LX_DEMOD_CODERATE_T *codeRate );
	int (*DVBS_Get_SymbolRate)				(UINT32 *pSymbolRate);
	int (*DVBS_Get_TotalInfo)				(void);
	int (*DVBS_Set_DiseqcToneMessageCtrl)			(LX_DEMOD_DVBS_DiSEqC_MSG_T *pDiseqcMsg);
	int (*DVBS_Set_EnvelopModeCtrl)				(LX_DEMOD_MESSAGE_TYPE_T messageType);
	int (*DVBS_Get_BlindInfo)				(UINT32 centerFreq, LX_DEMOD_DVBS_BLIND_PARAM_T *pBlindParam);
	int (*DVBS_Set_BlindSpectrumMode)			(LX_DEMOD_DVBS_OPERATION_MODE_T spectrumMode);
	int (*DVBS_Set_SpectrumModeConfig)			(BOOLEAN isBlindScan, UINT32 symbolRate);
	int (*DVBS_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*DVBS_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);


/***********************************************************************************
* DVBS2 function
************************************************************************************/

	int (*DVBS2_Set_DefaultRegisterValue)			(void);
	int (*DVBS2_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DVBS2_Set_PartialConfig)				(LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam);
	int (*DVBS2_Set_FullConfig)				(LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam);
	int (*DVBS2_Get_CoderRate)				(LX_DEMOD_CODERATE_T *pCodeRate );
	int (*DVBS2_Get_Pilot)					(BOOLEAN *pPilot );
	int (*DVBS2_Get_SymbolRate)				(UINT32 *pSymbolRate );
	int (*DVBS2_Get_TotalInfo)				(void);
	int (*DVBS2_Set_MemSconfig)				(void);
	int (*DVBS2_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*DVBS2_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);

/***********************************************************************************
* DVBS/S2 function
************************************************************************************/
	int (*DVBSX_BlindScan_Init)				(LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T *initFreq);
	int (*DVBSX_BlindScan_End)				(void);
	int (*DVBSX_Get_TunerFreq)				(LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T *pFreqInfo);
	int (*DVBSX_Get_OffsetFreq)				(LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T *pOffsetInfo);
	int (*DVBSX_SymbolRate_Detec)				(void);
	int (*DVBSX_BlindLock_Loop)				(void);
	int (*DVBSX_Get_Nextfreq_Status)			(BOOLEAN *pBlindScanEnd);

/***********************************************************************************
* DTMB function
************************************************************************************/

	int (*DTMB_SW_Init)					(void);
	int (*DTMB_Get_CarrierMode)				(LX_DEMOD_CARRIERMODE_T *pCarrierMode );
	int (*DTMB_Get_Time_Interval)				(BOOLEAN *pbM720 );
	int (*DTMB_Get_PnMode)					(LX_DEMOD_PNMODE_T *pPnMode);
	int (*DTMB_Get_CodeRate)				(LX_DEMOD_CODERATE_T *pCodeRate );
	int (*DTMB_Get_Constellation)				(LX_DEMOD_RF_MODE_T *pConstellation );
	int (*DTMB_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*DTMB_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*DTMB_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DTMB_Set_PartialConfig)				(LX_DEMOD_DTMB_CONFIG_T *pDtmbConfigParam);
	int (*DTMB_Set_MemSconfig)				(void);

/***********************************************************************************
* FW Util function (IPC,API, etc...)
************************************************************************************/

	int (*FW_ReInit)					(int mode);
	int (*IPC_Init)						(void);
	int (*IPC_Enable)					(int enable);
	int (*API_Suspend)					(void);
	int (*API_Status)					(char * pDbglog, int * pDbgidx);
	int (*API_Dump) 					(char * pDbglog, int * pDbgidx);
	int (*IPC_Status)					(char * pDbglog, int * pDbgidx);
	int (*IPC_Dump) 					(char * pDbglog, int * pDbgidx);
	int (*Get_UART)						(BOOLEAN *pStatus);
	int (*Set_UART)						(int enable);
	int (*Set_UART_Speed)					(int speed);
	int (*Set_UART_HEX)					(int enable);
	int (*Get_JTAG)						(BOOLEAN *pStatus);
	int (*Set_JTAG)						(int enable);
	int (*Get_Trace)					(char * pDbglog, int * pDbgidx);
	int (*Set_Trace)					(int enable);
/***********************************************************************************
* ABB function
************************************************************************************/

	int (*ADEMOD_Demod_Open)				(UINT32 chipDevID, UINT32 handleI2C,  Handle_t *phDevice);
	int (*ADEMOD_Init)					(Handle_t phDevice, LX_DEMOD_RF_MODE_T rfMode);
	int (*ADEMOD_Set_IF_Frq)				(Handle_t phDevice, UINT32 pllClkSource, UINT32 ifFrq);
	int (*ADEMOD_SoftwareReset)				(Handle_t phDevice);
	int (*ADEMOD_Set_AftRange)				(Handle_t phDevice, LX_DEMOD_ANALOG_ATFRANGE_PARAM_T aftRange);
	int (*ADEMOD_ResetHW)					(void);
	int (*ADEMOD_SetI2C)					(void);
	int (*ADEMOD_Set_AbbMode) 				(BOOLEAN bIsAbbMode);
	int (*ADEMOD_Set_WorkAround) 				(void);
	int (*ADEMOD_Set_CvbsRateConversion) 			(Handle_t phDevice, UINT32 pllClkSource );
	int (*ADEMOD_Set_HighCvbsRateOffset) 			(Handle_t phDevice, BOOLEAN bInitOffsetHigh);
	int (*ADEMOD_Set_SifCtrl) 				(Handle_t phDevice,UINT32 pllClkSource );
	int (*ADEMOD_Set_CvbsDecCtrl) 				(Handle_t phDevice, LX_DEMOD_ANALOG_CVBSDEC_SEL_T sel);
	int (*ADEMOD_Set_ClampingCtrl)				(Handle_t phDevice, UINT8 clampCount, UINT16 stepsize);
	int (*ADEMOD_Set_SifPathCtrl) 				(Handle_t phDevice, UINT32 pllClkSource, LX_DEMOD_ANALOG_SIFPATH_SEL_T sel);
	int (*ADEMOD_Set_SpectrumInv) 				(Handle_t phDevice,BOOLEAN bIsAbbMode, BOOLEAN bforce);
	int (*ADEMOD_Set_SpecialSifData) 			(Handle_t phDevice,  LX_DEMOD_ANALOG_SIF_SOUNDSYSTEM_T audioSystem);
	int (*ADEMOD_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*ADEMOD_Monitoring_Signal_Lock) 			(DEMOD_CTX_T *pDemodInfo);
	int (*ADEMOD_Dbg_Get_RegDump) 				(Handle_t phDevice);
	int (*ADEMOD_Dbg_Set_RegValue) 				(Handle_t phDevice,  UINT32 RegAddr, UINT32 RegSize, UINT32 RegData);
	int (*ADEMOD_Dbg_Set_SmartTune)				(LX_DEMOD_SMARTTUNE_PARAM_T *pSmartTuneParam);
	int (*ADEMOD_Dbg_Get_RegValue) 				(Handle_t phDevice, UINT32 RegAddr, UINT32 RegSize, UINT32 *pRegData);
	int (*ADEMOD_Dbg_TestFunctions) 			(Handle_t phDevice, UINT32 argc, UINT32 *val);

/* Internal point function */

	LX_ADEMOD_Result (*ADEMOD_Preset_Set)			(Handle_t hDevice, UINT32 smartTuneFilter, UINT32 Section);
	LX_ADEMOD_Result (*ADEMOD_Demod_Close)			(Handle_t hDevice);
	LX_ADEMOD_Result (*ADEMOD_Demodulate)			(Handle_t hDevice, UINT32 InputMode, UINT32 VideoStandard, UINT32 AudioStandard);
	LX_ADEMOD_Result (*ADEMOD_Parameter_Set)		(Handle_t hDevice, UINT32 ParamID, UINT32* pParamValue, BOOL UpdateNow);
	LX_ADEMOD_Result (*ADEMOD_Parameter_Get)		(Handle_t hDevice, UINT32 ParamID, UINT32* pParamValue);
	LX_ADEMOD_Result (*ADEMOD_AGC_Set)			(Handle_t hDevice, UINT32* pDescriptor, BOOL UpdateNow);
	LX_ADEMOD_Result (*ADEMOD_AGC_Get)			(Handle_t hDevice, UINT32* pDescriptor);
	LX_ADEMOD_Result (*ADEMOD_ChanScan_Set) 		(Handle_t hDevice, UINT32* pDescriptor, BOOL UpdateNow);
	LX_ADEMOD_Result (*ADEMOD_SleepMode_Set)		(Handle_t hDevice, UINT32 Mode);
	LX_ADEMOD_Result (*ADEMOD_SleepMode_Get)		(Handle_t hDevice, UINT32* pMode);
	LX_ADEMOD_Result (*ADEMOD_HostI2C_Write)		(Handle_t hDevice, UINT8 DevAddr, UINT8 RegAddr, UINT8* pData, UINT32 Size);
	LX_ADEMOD_Result (*ADEMOD_HostI2C_Read) 		(Handle_t hDevice, UINT8 DevAddr, UINT8 RegAddr, UINT8* pData, UINT32 Size);

	/***********************************************************************************
	* ATSC3 function
	************************************************************************************/

	int (*ATSC3_Get_FFTMode)				(LX_DEMOD_FFTMODE_T *pFftMode );
	int (*ATSC3_Get_GuradIntervalMode)			(LX_DEMOD_ATSC3_GIMODE_T *pGIMode);
	int (*ATSC3_Get_CodeRate)				(LX_DEMOD_ATSC3_CODERATE_T *pCodeRate);
	int (*ATSC3_Get_Constellation)				(LX_DEMOD_ATSC3_CONSTELLATION_T *pConstellation);
	int (*ATSC3_Obtaining_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*ATSC3_Monitoring_Signal_Lock)			(DEMOD_CTX_T *pDemodInfo);
	int (*ATSC3_Set_PLP)					(LX_DEMOD_ATSC3_CONFIG_T *pAtsc3ConfigParam);
	int (*ATSC3_Get_MPLP_Info)				(LX_DEMOD_ATSC3_MULTI_PLP_ID_T *pAtsc3mPLPInfo, LX_DEMOD_ATSC3_MULTI_PLP_ID_SEL_T plpSel);
	int (*ATSC3_Set_MemSconfig)				(void);
	int (*ATSC3_Set_OIFType)				(LX_DEMOD_ATSC3_OIF_TYPE_T *pAtsc3OifType); // htlim
/*Internal point function */
}
DEMOD_HAL_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	DEMOD_HAL_T	g_demod_hal;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _GFX_HAL_H_ */

