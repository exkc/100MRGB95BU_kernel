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


#ifndef	_DEMOD_HW_H_
#define _DEMOD_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define __ARM__

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C"
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#ifndef TRUE
    #define TRUE 1
    #define FALSE 0
#endif


#define DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_2K  				0
#define DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_8K  				1
#define DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_4K  				2
#define DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_1K  				3
#define DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_16K  				4
#define DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_32K  				5
#define DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_512K  				6
#define DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_256K  				7

#define DEMOD_DVBT_STATUS_RESPONSE_GI_1_32  					0
#define DEMOD_DVBT_STATUS_RESPONSE_GI_1_16  					1
#define DEMOD_DVBT_STATUS_RESPONSE_GI_1_8   					2
#define DEMOD_DVBT_STATUS_RESPONSE_GI_1_4   					3
#define DEMOD_DVBT_STATUS_RESPONSE_GI_1_128   					4
#define DEMOD_DVBT_STATUS_RESPONSE_GI_19_128   					5
#define DEMOD_DVBT_STATUS_RESPONSE_GI_19_256   					6
#define DEMOD_DVBT_STATUS_RESPONSE_GI_1_64   					7

#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QPSK   				0x0
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_DQPSK   			0x1
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM16   			0x2
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM32  				0x3
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM64   			0x4
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM128  			0x5
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM256  			0x6
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM1024  			0x7
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM4096  			0x8
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_PSK8  				0x9
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_VSB8  				0xa
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM4  				0xb
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_APSK16  			0xc
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_APSK32  			0xd
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM4NR  			0xe
#define DEMOD_STATUS_RESPONSE_CONSTELLATION_UNKNOWN  			0xf

#define DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP				1
#define DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_LP				0

#define DEMOD_DVBT_STATUS_RESPONSE_CR_1_2  						0
#define DEMOD_DVBT_STATUS_RESPONSE_CR_2_3  						1
#define DEMOD_DVBT_STATUS_RESPONSE_CR_3_4  						2
#define DEMOD_DVBT_STATUS_RESPONSE_CR_5_6  						3
#define DEMOD_DVBT_STATUS_RESPONSE_CR_7_8  						4

#define DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_NONE   			0
#define DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA1  			1
#define DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA2  			2
#define DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA4  			3

#define DEMOD_DTMB_STATUS_RESPONSE_IL_MODE_720					1
#define DEMOD_DTMB_STATUS_RESPONSE_IL_MODE_240					0

#define DEMOD_DTMB_STATUS_RESPONSE_CARR_MODE_MC					1
#define DEMOD_DTMB_STATUS_RESPONSE_CARR_MODE_SC					0

#define DEMOD_DTMB_STATUS_RESPONSE_PN_CONST_CONSTANT			1
#define DEMOD_DTMB_STATUS_RESPONSE_PN_CONST_VARIABLE			0

#define DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN945				3
#define DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN595				2
#define DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN420				1


#define DEMOD_STATUS_RESPONSE_CODERATE_2_5						0x05
#define DEMOD_STATUS_RESPONSE_CODERATE_3_5						0x06
#define DEMOD_STATUS_RESPONSE_CODERATE_4_5						0x07
#define DEMOD_STATUS_RESPONSE_CODERATE_UNKNOWN					0x0f

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	DEMOD_CTX_T g_demod_ctx_info[DEMOD_MAX_DEVICE];

/* Common  function */
#if defined(DEMOD_CHIP_NAME_o20)
int DEMOD_Retune(void);
#else
int DEMOD_Retune(LX_DEMOD_OPER_MODE_T reply_opmode);
#endif

extern int DEMOD_MediaChange(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_INIT_PARAM_T *pTranMedia);
extern int DEMOD_ChannelChange(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
extern int DEMOD_Get_TunedCFG(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_Get_signal_status(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_Tuning_Task(void *i_pvParam);
extern int DEMOD_WakeUpTask(void);
extern int DEMOD_Signal_Dump(char * dbglog);
extern int DEMOD_Register_Dump(char * dbglog);

extern int DEMOD_RepeaterEnable(BOOLEAN bEnable);
extern int DEMOD_SoftwareReset(void);
extern int DEMOD_Serial_Control(BOOLEAN bEnable);
extern int DEMOD_Power_Save(BOOLEAN bEnable);
extern int DEMOD_APB_AccessControl(BOOLEAN bEnable);
extern int DEMOD_StdOperModeContrl( LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr);
extern int DEMOD_NeverlockScan(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock);
extern int DEMOD_TPOutCLKEnable(BOOLEAN bEnable);
extern int DEMOD_GetTsClkRate(UINT32 *demodTsClkRate);
extern int DEMOD_Set_IF_Frq(UINT32 ifFrq);
extern int DEMOD_Set_AGCPolarity(LX_DEMOD_AGC_POLAR_T agcPola);
extern int DEMOD_Set_SpectrumCtrl(BOOLEAN bAutoEnable, BOOLEAN bSpecInvEnable);
extern int DEMOD_Get_Id(UINT16 *pId);  //jeongpil.yun
extern int DEMOD_Get_SpectrumStatus(LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv);
extern int DEMOD_Get_IFAGC(UINT16 *pIfAgc);
extern int DEMOD_Get_OperMode(LX_DEMOD_OPER_MODE_T *pOperMode);
extern int DEMOD_Get_CarrierFreqOffset(SINT32 *pFreqOff);
extern int DEMOD_Get_TPIFStatus(BOOLEAN *pbEnable);
extern int DEMOD_Get_VABER(UINT32 *pVber);
extern int DEMOD_Get_Packet_Error(UINT32 *pError);
extern int DEMOD_Get_BandWidthMode( LX_DEMOD_BWMODE_T *ChannelBW );
extern int DEMOD_Get_QAMMode( LX_DEMOD_RF_MODE_T *pQamMode );
extern int DEMOD_Get_MseInfo( LX_DEMOD_MSE_T *pSigMse);
extern int DEMOD_Get_Lock(LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState);
extern int DEMOD_Get_SysLockTime(UINT16 *pSyslocktime);
extern int DEMOD_Get_FecLockTime(UINT16 *pFeclocktime);
extern int DEMOD_Set_Frame_resynchronizaiton(BOOLEAN bEnable);
extern int DEMOD_Get_FW_PartInfo(UINT32 *pFW_Info);
extern int DEMOD_Get_Dump(void);
extern int DEMOD_Total_Signal_infomation(LX_DEMOD_SIGNAL_TOTAL_T *sigStatus);
extern int DEMOD_Tune_Cfg_infomation(LX_DEMOD_SIGNAL_TUNE_CFG_T *sigStatus);
extern int DEMOD_Set_CountryGrp(BOOLEAN bEnable);

extern int KHAL_DEMOD_Init(void);
extern int KHAL_DEMOD_MediaChange(LX_DEMOD_INIT_PARAM_T *pTranMedia);
extern int KHAL_DEMOD_ChannelChange(LX_DEMOD_CONFIG_T *pDemodCfg);
extern int KHAL_Get_DEMOD_Sigstatus(LX_DEMOD_SIGNAL_CTX_T *sigCtx);
extern int KHAL_Get_DEMOD_NotifiedStatus(BOOLEAN *pNotifiedStatus);
extern int KHAL_Get_DEMOD_NotifiedLock(LX_DEMOD_LOCK_STATE_T *pNotifiedLock);
extern int KHAL_Get_DEMOD_ChannelPara(LX_DEMOD_CONFIG_T	*pChannelParams);

extern int DEMOD_ADC_Enable(void);



/* DVB function */


extern int DEMOD_DVBC_AutoSymbolRateDet(LX_DEMOD_SYMRDET_MODE_T symrateMode, UINT16 SymbolRate);
extern int DEMOD_DVBC_IsSymbolRateAuto(BOOLEAN *bAuto);
extern int DEMOD_DVBC_IsQammodeAutoDet (BOOLEAN *bAutoQam);
extern int DEMOD_DVBC_Set_DefaultRegisterValue(void);
extern int DEMOD_DVBC_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_DVBC_Set_QamMode (LX_DEMOD_RF_MODE_T constel);
extern int DEMOD_DVBC_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_DVBC_Get_SymbolRateDetect(UINT16 *pSymbolRate);
extern int DEMOD_DVBC_Get_SymbolRateStatus(LX_DEMOD_SYMBOLRATE_STATE_T *pSymbolRateDet);
extern int DEMOD_DVBC_Get_QamModeDetectStatus(LX_DEMOD_QAMMODE_STATE_T *pQamModeDet);
extern int DEMOD_DVBC_Get_DvbInfo(void);

extern int DEMOD_DVBC_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_DVBC_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);

extern int DEMOD_DVBC2_IsQammodeAutoDet (BOOLEAN *bAutoQam);
extern int DEMOD_DVBC2_Set_DefaultRegisterValue(void);
extern int DEMOD_DVBC2_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_DVBC2_Set_PartialConfig (LX_DEMOD_DVBC2_CONFIG_T *pDvbc2ConfigParam);
extern int DEMOD_DVBC2_Set_FullConfig (LX_DEMOD_DVBC2_CONFIG_T *pDvbc2ConfigParam);
extern int DEMOD_DVBC2_Set_QamMode (UINT8 constel);
extern int DEMOD_DVBC2_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_DVBC2_Set_StartFrequency(UINT32 frequency);
extern int DEMOD_DVBC2_Get_QamModeDetectStatus(LX_DEMOD_QAMMODE_STATE_T *pQamModeDet);
extern int DEMOD_DVBC2_Get_multiPLP_ID(LX_DEMOD_DVBC2_MULTI_PLP_INFO_T *pParamMultiPLPInfo);
extern int DEMOD_DVBC2_Get_DvbInfo(void);

extern int DEMOD_DVBC2_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_DVBC2_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);


extern int DEMOD_DVBT_Set_DefaultRegisterValue(LX_DEMOD_BWMODE_T band);
extern int DEMOD_DVBT_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_DVBT_Set_PartialConfig (LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam);
extern int DEMOD_DVBT_Set_FullConfig (LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam);
extern int DEMOD_DVBT_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_DVBT_Get_DelaySpreadStatus(UINT16 *pDelaySpread);
extern int DEMOD_DVBT_Get_Hierach_HPSel( BOOLEAN *pBSetHp );
extern int DEMOD_DVBT_Get_FFTMode( LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
extern int DEMOD_DVBT_Get_GuradIntervalMode( LX_DEMOD_GIMODE_T *pGIMode );
extern int DEMOD_DVBT_Get_HierachyMode( LX_DEMOD_DVB_TPS_HIERACHY_T *pHierachMode );
extern int DEMOD_DVBT_Get_LpCoderRate( LX_DEMOD_CODERATE_T *pLpCodeRate );
extern int DEMOD_DVBT_Get_HpCoderRate( LX_DEMOD_CODERATE_T *pHpCodeRate );
extern int DEMOD_DVBT_Get_CellId(UINT8 *pCellIDLength, UINT16 *cell_id);
extern int DEMOD_DVBT_Get_TpsInfo( LX_DEMOD_DVBT_CONFIG_T *pTpsParams);
extern int DEMOD_DVBT_Get_TotalInfo( void);
extern int DEMOD_DVBT_Get_IFO_LOCK( BOOLEAN *pIfoLock);
extern int DEMOD_DVBT_Get_CochanDetIndicator( BOOLEAN *pDetStatus);
extern int DEMOD_DVBT_EqualizereReset(void);

extern int DEMOD_DVBT_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_DVBT_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);

extern int DEMOD_DVBT2_Set_DefaultRegisterValue(LX_DEMOD_BWMODE_T band);
extern int DEMOD_DVBT2_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_DVBT2_Set_PartialConfig (LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam);
extern int DEMOD_DVBT2_Set_FullConfig (LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam);
extern int DEMOD_DVBT2_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_DVBT2_Get_DelaySpreadStatus(UINT16 *pDelaySpread);
extern int DEMOD_DVBT2_Get_FFTMode( LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
extern int DEMOD_DVBT2_Get_GuradIntervalMode( LX_DEMOD_GIMODE_T *pGIMode );
extern int DEMOD_DVBT2_Get_CoderRate( LX_DEMOD_CODERATE_T *pLpCodeRate );
extern int DEMOD_DVBT2_Get_multiPLP_ID(LX_DEMOD_DVBT2_MULTI_PLP_INFO_T *pParamMultiPLPInfo);
extern int DEMOD_DVBT2_Get_PlpInfo( LX_DEMOD_DVBT2_CONFIG_T *pPlpParams);
extern int DEMOD_DVBT2_Get_TotalInfo( void);

extern int DEMOD_DVBT2_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_DVBT2_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);

extern int DEMOD_DVBT2_Set_MemSconfig(void);

extern int DEMOD_DVB_Set_MemSconfig(void);

/* VSB/QAM/ISDBT function */
extern int DEMOD_VQI_NeverlockScan(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock);

extern int DEMOD_VSB_SetDemod(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_VSB_Set_DefaultRegisterValue(void);  //jeongpil.yun
extern int DEMOD_VSB_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_VSB_CochannelExist(BOOLEAN *pCochannel);  //jeongpil.yun
extern int DEMOD_VSB_PreMonitor(void);
extern int DEMOD_VSB_Monitor(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_VSB_Get_MSEdynStatus(BOOLEAN *pbEnable);
extern int DEMOD_VSB_Get_TotalInfo( void);

extern int DEMOD_VSB_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_VSB_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);

extern int DEMOD_QAM_SetDemod(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_QAM_SoftwareResetFEC(void); //jeongpil.yun
extern int DEMOD_QAM_Monitor(void);
extern int DEMOD_QAM_ModeAutoDetection(BOOLEAN bEnable);
extern int DEMOD_QAM_64Mode(void);  //jeongpil.yun
extern int DEMOD_QAM_256Mode(void);  //jeongpil.yun
extern int DEMOD_QAM_Set_DefaultRegisterValue(void);  //jeongpil.yun
extern int DEMOD_QAM_Set_NeverLockWaitTime(UINT32 waitMs);

extern int DEMOD_QAM_Get_TotalInfo( void);

extern int DEMOD_QAM_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_QAM_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_QAM_EQ_Signal_Detector(BOOLEAN OnOff);

extern int DEMOD_ISDBT_Set_DefaultRegisterValue(void);
extern int DEMOD_ISDBT_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_ISDBT_Set_PartialConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam);
extern int DEMOD_ISDBT_Set_FullConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam);
extern int DEMOD_ISDBT_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_ISDBT_Get_DelaySpreadStatus(UINT16 *pDelaySpread);
extern int DEMOD_ISDBT_Get_FFTMode( LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
extern int DEMOD_ISDBT_Get_GuradIntervalMode( LX_DEMOD_GIMODE_T *pGIMode );
extern int DEMOD_ISDBT_Get_TMCCInfo( LX_DEMOD_ISDBT_TMCC_CONFIG_T *pTmccParams);
extern int DEMOD_ISDBT_Get_TotalInfo( void);
extern int DEMOD_ISDBT_Get_IFO_LOCK( BOOLEAN *pIfoLock);
extern int DEMOD_ISDBT_Get_CochanDetIndicator( BOOLEAN *pDetStatus);
extern int DEMOD_ISDBT_EqualizereReset(void);

extern int DEMOD_ISDBT_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_ISDBT_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_ISDBT_Set_MemSconfig(void);
extern int DEMOD_ISDBT_GetEmergencyAlertFlagStatus( BOOLEAN *pEalarm);

/* DVBS */
extern int DEMOD_DVBS_Set_DefaultRegisterValue(void);
extern int DEMOD_DVBS_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_DVBS_Set_PartialConfig (LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam);
extern int DEMOD_DVBS_Set_FullConfig (LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam);
extern int DEMOD_DVBS_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate );
extern int DEMOD_DVBS_Get_SymbolRate(UINT32 *pSymbolRate );
extern int DEMOD_DVBS_Get_TotalInfo( void);
extern int DEMOD_DVBS_Set_DiseqcToneMessageCtrl( LX_DEMOD_DVBS_DiSEqC_MSG_T *pDiseqcMsg);
extern int DEMOD_DVBS_Set_EnvelopModeCtrl(LX_DEMOD_MESSAGE_TYPE_T messageType);
extern int DEMOD_DVBS_Get_BlindInfo(UINT32 centerFreq, LX_DEMOD_DVBS_BLIND_PARAM_T *pBlindParam);
extern int DEMOD_DVBS_Set_BlindSpectrumMode(LX_DEMOD_DVBS_OPERATION_MODE_T spectrumMode);
extern int DEMOD_DVBS_Set_SpectrumModeConfig( BOOLEAN isBlindScan, UINT32 symbolRate);
extern int DEMOD_DVBS_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_DVBS_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);


/* DVBS2 */
extern int DEMOD_DVBS2_Set_DefaultRegisterValue(void);
extern int DEMOD_DVBS2_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_DVBS2_Set_PartialConfig (LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam);
extern int DEMOD_DVBS2_Set_FullConfig (LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam);
extern int DEMOD_DVBS2_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate );
extern int DEMOD_DVBS2_Get_Pilot(BOOLEAN *pPilot );
extern int DEMOD_DVBS2_Get_SymbolRate(UINT32 *pSymbolRate );
extern int DEMOD_DVBS2_Get_TotalInfo( void);
extern int DEMOD_DVBS2_Set_MemSconfig(void);

extern int DEMOD_DVBS2_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_DVBS2_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);

/*DVBS/S2*/
extern int DEMOD_DVBSX_BlindScan_Init(LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T *initFreq);
extern int DEMOD_DVBSX_BlindScan_End(void);
extern int DEMOD_DVBSX_GetTunerFreq(LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T *pFreqInfo);
extern int DEMOD_DVBSX_Get_OffsetFreq(LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T* pOffsetInfo);
extern int DEMOD_DVBSX_SymbolRate_Detect(void);
extern int DEMOD_DVBSX_BlindLock_Loop(void);
extern int DEMOD_DVBSX_Get_Nextfreq_Status(BOOLEAN *pBlindScanEnd);

/*DTMB*/
extern int DEMOD_DTMB_Get_Carrier_Mode( LX_DEMOD_CARRIERMODE_T *pCarrierMode );
extern int DEMOD_DTMB_Get_Time_Interval( BOOLEAN *pbM720 );
extern int DEMOD_DTMB_Get_PN_Mode( LX_DEMOD_PNMODE_T *pPnMode );
extern int DEMOD_DTMB_Get_Code_Rate( LX_DEMOD_CODERATE_T *pCodeRate );
extern int DEMOD_DTMB_Get_Constellation( LX_DEMOD_RF_MODE_T *pConstellation );
extern int DEMOD_DTMB_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_DTMB_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_DTMB_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_DTMB_Set_PartialConfig (LX_DEMOD_DTMB_CONFIG_T *pDtmbConfigParam);
extern int DEMOD_DTMB_Set_MemSconfig(void);

/*ATSC3*/
extern int DEMOD_ATSC3_Get_FFTMode(LX_DEMOD_FFTMODE_T *pFftMode );
extern int DEMOD_ATSC3_Get_GuradIntervalMode(LX_DEMOD_ATSC3_GIMODE_T *pGIMode);
extern int DEMOD_ATSC3_Get_CodeRate(LX_DEMOD_ATSC3_CODERATE_T *pCodeRate);
extern int DEMOD_ATSC3_Get_Constellation (LX_DEMOD_ATSC3_CONSTELLATION_T *pConstellation);
extern int DEMOD_ATSC3_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_ATSC3_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_ATSC3_Set_PLP (LX_DEMOD_ATSC3_CONFIG_T  *pAtsc3ConfigParam);
extern int DEMOD_ATSC3_Get_MPLP_Info (LX_DEMOD_ATSC3_MULTI_PLP_ID_T *pAtsc3mPLPInfo, LX_DEMOD_ATSC3_MULTI_PLP_ID_SEL_T plpSel);
extern int DEMOD_ATSC3_Set_MemSconfig(void);
extern int DEMOD_ATSC3_Set_OIFType(LX_DEMOD_ATSC3_OIF_TYPE_T *pAtsc3OifType); // htlim

/*ANALOG*/
extern int DEMOD_ANALOG_Set_ClampingCtrl(UINT8 clampCount, UINT16 stepsize);

/*FW util*/
extern int DEMOD_FW_ReInit(int mode);
extern int DEMOD_IPC_Init(void);
extern int DEMOD_IPC_Enable(int enable);
//extern int DEMOD_IPC_Handler(void);
extern int DEMOD_Get_UART(BOOLEAN *pStatus);
extern int DEMOD_Set_UART(int enable);
extern int DEMOD_Set_UART_Speed(int speed);
extern int DEMOD_Set_UART_HEX(int enable);
extern int DEMOD_Get_JTAG(BOOLEAN *pStatus);
extern int DEMOD_Set_JTAG(int enable);
extern int DEMOD_Get_Trace (char * pDbglog, int * pDbgidx);
extern int DEMOD_Set_Trace(int enable);
extern int DEMOD_API_Status( char * pDbglog, int * pDbgidx);
extern int DEMOD_API_Dump( char * pDbglog, int * pDbgidx);
extern int DEMOD_IPC_Status( char * pDbglog, int * pDbgidx);
extern int DEMOD_IPC_Dump( char * pDbglog, int * pDbgidx);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _GFX_HW_H_ */

/** @} */

