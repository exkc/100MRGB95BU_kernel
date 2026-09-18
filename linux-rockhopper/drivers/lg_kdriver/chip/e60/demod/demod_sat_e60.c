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

#include <linux/timer.h>
#include <asm/div64.h> //do_div


#include "demod_impl.h"
#include "demod_common_e60.h"
#include "demod_sat_e60.h"

#define	UNLOCKCOUNT	10

/***********************************************************************************
	Global Type Definitions
 ************************************************************************************/

/***********************************************************************************
	Static Variable & Function Prototypes Declarations
 ************************************************************************************/

int _DEMOD_E60_DVBS_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbs.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;

		default:
		{
			DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] CheckTuneMode tuneMode = 0x%x\n", pDemodInfo->setCfgParam.dvbs.tuneMode);
			return DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		}
	}
	return new_tuneMode;
}

int _DEMOD_E60_DVBS2_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbs2.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;

		default:
		{
			DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] CheckTuneMode tuneMode = 0x%x\n", pDemodInfo->setCfgParam.dvbs2.tuneMode);
			return DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		}
	}
	return new_tuneMode;
}

int _DEMOD_E60_DVBS_OperatingMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  operatingMode;

	switch (pDemodInfo->setCfgParam.dvbs.operatingMode)
	{
		case	LX_DEMOD_DVBS_NORMAL_MODE:					operatingMode = DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE; break;
		case	LX_DEMOD_DVBS_BLIND_SCAN_MODE: 				operatingMode = DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_SCAN_MODE; break;
		case	LX_DEMOD_DVBS_BLIND_LOCK_MODE: 				operatingMode = DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE ; break;

		default:						return DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE; break;
	}
	return operatingMode;
}

int _DEMOD_E60_DVBS2_OperatingMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  operatingMode;

	switch (pDemodInfo->setCfgParam.dvbs2.operatingMode)
	{
		case	LX_DEMOD_DVBS_NORMAL_MODE:					operatingMode = DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE; break;
		case	LX_DEMOD_DVBS_BLIND_SCAN_MODE: 				operatingMode = DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_SCAN_MODE; break;
		case	LX_DEMOD_DVBS_BLIND_LOCK_MODE: 				operatingMode = DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE ; break;

		default:						return DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE; break;
	}
	return operatingMode;
}

int _DEMOD_E60_LGDBB_DVBS_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			standard;
	UINT32 			freq_Khz;
	UINT16 			symbol_rate_Kbps = 0 ;
	UINT8  			operatingMode;
	UINT8  			new_tuneMode;

	DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] Start\n");

	pFrontend 		= DEMOD_E60_GetContext();

	standard 		= DEMOD_DD_MODE_PROP_MODULATION_DVBS;
	new_tuneMode 		= _DEMOD_E60_DVBS_CheckTuneMode(pDemodInfo);
	operatingMode 		= _DEMOD_E60_DVBS_OperatingMode(pDemodInfo);
	symbol_rate_Kbps 	= (UINT16)(pDemodInfo->setCfgParam.dvbs.symbolRate);// KSym/s
	freq_Khz 		= pDemodInfo->setCfgParam.dvbs.frequency;

	DEMOD_PRINT( "[DEMOD_CHIP] TuneMode = %x\n", new_tuneMode);
	DEMOD_PRINT( "[DEMOD_CHIP] OperatingMode = %x\n", operatingMode);

	DEMOD_L2_SAT_set_demod(pFrontend,
				standard,
				freq_Khz,
				new_tuneMode,
				DEMOD_DD_MODE_PROP_SPECINV_AUTO,
				DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
				symbol_rate_Kbps,
				operatingMode );
	return RET_OK;
}
int _DEMOD_E60_LGDBB_DVBS2_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			standard;
	UINT32 			freq_Khz;
//	UINT16 			dvb_s2_bandwidth_Khz;
	UINT16 			symbol_rate_Kbps = 0 ;
	UINT8  			operatingMode;
	UINT8  			new_tuneMode;

	DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] Start\n");

	pFrontend		= DEMOD_E60_GetContext();

	standard 		= DEMOD_DD_MODE_PROP_MODULATION_DVBS2;
	new_tuneMode 		= _DEMOD_E60_DVBS2_CheckTuneMode(pDemodInfo);
	operatingMode 		= _DEMOD_E60_DVBS2_OperatingMode(pDemodInfo);
	symbol_rate_Kbps 	= (UINT16)(pDemodInfo->setCfgParam.dvbs2.symbolRate);// KSym/s
	freq_Khz 		= pDemodInfo->setCfgParam.dvbs2.frequency;

	DEMOD_PRINT( "[DEMOD_CHIP] TuneMode = %x\n", new_tuneMode);
	DEMOD_PRINT( "[DEMOD_CHIP] OperatingMode = %x\n", operatingMode);

	DEMOD_L2_SAT_set_demod(pFrontend,
				standard,
				freq_Khz,
				new_tuneMode,
				DEMOD_DD_MODE_PROP_SPECINV_AUTO,
				DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
				symbol_rate_Kbps,
				operatingMode );
	return RET_OK;

}


int _DEMOD_E60_LGDBB_SAT_CheckSignalState (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;;
	}

	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber		= signalStatus.ber;
	pDemodInfo->signalStatus.agc		= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse		= signalStatus.mse_info;
	pDemodInfo->signalStatus.m.constPwr	= signalStatus.constPwr;
	pDemodInfo->freqOffset 			= signalStatus.offsetFrq_Hz / 1000;
	pDemodInfo->signalStatus.operMode 	= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode		= pDemodInfo->systemMode;
	pDemodInfo->signalStatus.cellID		= signalStatus.cell_id;

	return RET_OK;
}

#if 0
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS_Set_Config_auto (BOOLEAN bAutoDetect)
{
/*
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_E60_GetContext();

	if(bAutoDetect == TRUE)
	{
		if(DEMOD_L2_DVB_AutoModeDetectOn(pFrontend))
		{
			DEMOD_PRINT("(%s) FAIL, DEMOD_L2_DVB_AutoModeDetectOn \n", __F__);
			return RET_ERROR;
		}
	}
	else
	{
		if(DEMOD_L2_DVB_AutoModeDetectOff(pFrontend))
		{
			DEMOD_PRINT("(%s) FAIL, DEMOD_L2_DVB_AutoModeDetectOff \n", __F__);
			return RET_ERROR;
		}
	}
*/
	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_E60_DVBS_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBS_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS_Set_FullConfig (LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Get_CoderRate
 * Get the information of code rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS_Get_CoderRate (LX_DEMOD_CODERATE_T *pCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	switch(signalStatus.codeRate)
	{
		case 0x00 :
			*pCodeRate = LX_DEMOD_CODE_1_2;
			break;
		case 0x02:
			*pCodeRate = LX_DEMOD_CODE_2_3;
			break;
		case 0x04 :
			*pCodeRate = LX_DEMOD_CODE_3_4;
			break;
		case 0x08:
			*pCodeRate = LX_DEMOD_CODE_5_6;
			break;
		case 0x09:
			*pCodeRate = LX_DEMOD_CODE_7_8;
			break;
		default :
			*pCodeRate = LX_DEMOD_CODE_UNKNOWN;
			break;

	}

	DEMOD_PRINT("[DEMOD_CHIP] pCodeRate = %d \n", *pCodeRate);

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Get_SymbolRate
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS_Get_SymbolRate (UINT32 *pSymbolRate )
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	*pSymbolRate = signalStatus.sym_rate;

	DEMOD_PRINT("[DEMOD_CHIP] pSymbolRate = %d \n", *pSymbolRate);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS_Get_TotalInfo (void)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	UINT16 			ifagcValue = 0;
	UINT32 			errorCount;
	SINT32 			FreqOff;
	UINT32 			symbolRate;
	LX_DEMOD_LOCK_STATE_T 	agcLockStatus;
	LX_DEMOD_LOCK_STATE_T 	neverLockStatus;
	LX_DEMOD_LOCK_STATE_T 	spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 	spectrumInv;
	LX_DEMOD_CODERATE_T 	codeRate;
	LX_DEMOD_MSE_T 		sigMse;

	DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

	if (RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_AGC_LOCK, &agcLockStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		agcLockStatus = LX_DEMOD_UNKOWN_STATE;
	}
	if(LX_DEMOD_LOCKED == agcLockStatus)
	{
		ifagcValue = signalStatus.if_agc;
		DEMOD_PRINT("[DEMOD_CHIP] IF AGC = 0x%x \n", ifagcValue);
	}

	if (RET_OK != DEMOD_E60_Get_NeverLockStatus(LX_DEMOD_DVBS, &neverLockStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_NeverLockStatus() \n");
		neverLockStatus = LX_DEMOD_UNKOWN_STATE;
	}

	if (RET_OK !=  DEMOD_E60_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_SpectrumStatus() \n");
		spectrumInv = LX_DEMOD_UNKOWN_STATE;
	}

	errorCount 		= signalStatus.packetError;

	DEMOD_PRINT("[DEMOD_CHIP] TP Error Count= %d\n",errorCount);

	FreqOff 		= signalStatus.offsetFrq_Hz / 1000;

	sigMse.bMse 		= 0;
	sigMse.mse 		= signalStatus.mse_info;
	sigMse.constPwr 	= signalStatus.constPwr;

	DEMOD_PRINT("[DEMOD_CHIP] AGC LOCK is %s\n",(agcLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD_CHIP] IF AGC value = %d(0x%x)\n",ifagcValue,ifagcValue);
	DEMOD_PRINT("[DEMOD_CHIP] Neverlock is %s\n",(neverLockStatus == LX_DEMOD_DETECTED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD_CHIP] Spectrum auto = %s, Inversion  = %s\n",(spectrumAuto == LX_DEMOD_AUTO) ? " Auto" : " Manual",
																					(spectrumInv == LX_DEMOD_INVERSION) ? " Inverted" : " Normal" );
	DEMOD_PRINT("[DEMOD_CHIP] offset = %d [KHz]\n",FreqOff);
	DEMOD_PRINT("[DEMOD_CHIP] mse = %d, constPwr = %d\n",sigMse.mse, sigMse.constPwr);

	switch(signalStatus.codeRate)
	{
		case 0x00 :
			codeRate = LX_DEMOD_CODE_1_2;
			break;
		case 0x02:
			codeRate = LX_DEMOD_CODE_2_3;
			break;
		case 0x04 :
			codeRate = LX_DEMOD_CODE_3_4;
			break;
		case 0x08:
			codeRate = LX_DEMOD_CODE_5_6;
			break;
		case 0x09:
			codeRate = LX_DEMOD_CODE_7_8;
			break;
		default :
			codeRate = LX_DEMOD_CODE_UNKNOWN;
			break;
	}

	symbolRate = signalStatus.sym_rate;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Set_DiseqcToneMessageCtrl
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS_Set_DiseqcToneMessageCtrl (LX_DEMOD_DVBS_DiSEqC_MSG_T *pDiseqcMsg)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SAT_send_diseqc_sequence(pFrontend, pDiseqcMsg->sequence_length, pDiseqcMsg->sequenceBuffer, pDiseqcMsg->cont_tone, pDiseqcMsg->tone_burst,pDiseqcMsg->burst_sel, pDiseqcMsg->end_seq))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SAT_send_diseqc_sequence() \n");
		return RET_ERROR;
	}
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Get_BlindInfo
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS_Get_BlindInfo(UINT32 centerFreq, LX_DEMOD_DVBS_BLIND_PARAM_T *pBlindParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBS_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	static LX_DEMOD_FLAG_T 		scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	lockState = LX_DEMOD_UNLOCKED;
	static unsigned int 		sigStablestartTime = 0;
	LX_DEMOD_OPER_MODE_T 		operMode;
	unsigned int			elapsedTime = 0;

	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{

				if(RET_OK != _DEMOD_E60_LGDBB_DVBS_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVBS_SetDemod() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if ( pDemodInfo->setCfgParam.dvbs.symbolRate <= 2000) //2000 is 2MHz
				{
					notifyinglockTimeOut = LX_DEMOD_LOCK_DEALY_10000;
				}
				else
				{
					notifyinglockTimeOut = LX_DEMOD_LOCK_DEALY_5000;
				}

				if(pDemodInfo->setCfgParam.dvbs.operatingMode == LX_DEMOD_DVBS_BLIND_SCAN_MODE)
				{
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START : Blind Spectrum Mode..Going to LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK..... ^0^\n");
					break;
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbs.tuneMode)
				{

					if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");

				}
				else
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
			}
			break;

		/***************************************************/
		/***** Configure demod for scan mode. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_SCAN:
			{
				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "[DEMOD_CHIP] Already Done\n");
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == lockState))
				{
					if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode() \n");
						DEMOD_RETURN_FAIL(__F__);

					}
					DEMOD_PRINT("[DEMOD_CHIP] OperMode(%d)\n",operMode);
					if(LX_DEMOD_DVBS2 == operMode)
					{
						pDemodInfo->operMode		= LX_DEMOD_DVBS2;
						pDemodInfo->scanJobFlag		= LX_DEMOD_FLAG_FINISH;
						pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING; //LX_DEMOD_RETUNE_RF;
						pDemodInfo->setCfgParam.dvbs2.tuneMode = pDemodInfo->setCfgParam.dvbs.tuneMode;
						pDemodInfo->setCfgParam.dvbs2.symbolRate = pDemodInfo->setCfgParam.dvbs.symbolRate;

						DEMOD_PRINT( "[DEMOD_CHIP] Signal is Found (LX_DEMOD_DVBS2)\n");
						DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					}
					else //(LX_DEMOD_DVBS == operMode)
					{
						pDemodInfo->operMode		= LX_DEMOD_DVBS;
						pDemodInfo->scanJobFlag		= LX_DEMOD_FLAG_FINISH;
						pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;

						DEMOD_PRINT( "[DEMOD_CHIP] Signal is Found (LX_DEMOD_DVBS)\n");
						DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					}
				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == lockState))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					elapsedTime 			= jiffies_to_msecs(jiffies) - g_NewTuneReqeustTime;

					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : MSG_DVBS_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;
					DEMOD_PRINT( "[DEMOD_CHIP] Signal is NOT Found \n");
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
//					DEMOD_PRINT( "[DEMOD_CHIP] Detection is on processing\n");
				}
			}
			break;

		/***************************************************/
		/***** Attempting to finish the tuning state machine *****/
		/***************************************************/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK :
			{

			}
			break;

		/***************************************************/
		/***** Attempting to obtain synch lock *****/
		/***************************************************/
		case LX_DEMOD_SYNC_CHECKING :
			{
				if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode() \n");
					DEMOD_RETURN_FAIL(__F__);

				}
				DEMOD_PRINT("[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING : operMode = 0x%x\n", operMode);

				if(LX_DEMOD_DVBS2 == operMode)
				{
					pDemodInfo->operMode 		= LX_DEMOD_DVBS2;
					pDemodInfo->setCfgParam.dvbs2.tuneMode = pDemodInfo->setCfgParam.dvbs.tuneMode;
					pDemodInfo->setCfgParam.dvbs2.symbolRate = pDemodInfo->setCfgParam.dvbs.symbolRate;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING(DVBS) : Going to LX_DEMOD_SYNC_CHECKING(DVBS2 forcely)..... ^0^\n");

					return RET_OK;
				}

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 		= jiffies_to_msecs(jiffies);

					DEMOD_PRINT( "^R^[DEMOD E60] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
				 	/* nothing to do so far */

				}
			}
		   break;

		/***************************************************/
		/***** Attempting to obtain signal stability *****/
		/***************************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				SINT32 freqOffset;

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
					pDemodInfo->signalStatus.bSignalValid = TRUE;

					if (RET_OK != DEMOD_E60_Get_CarrierFreqOffset(&freqOffset))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_CarrierFreqOffset() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->freqOffset 		= freqOffset;
					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;
					pDemodInfo->bNotifiedLock	= TRUE;
					pDemodInfo->bNotifiedUnlock	= FALSE;
					elapsedTime 			= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : MSG_DVBS_FRONT_END_LOCKED..... ^^^0^^^\n");
					DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);


					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != _DEMOD_E60_LGDBB_SAT_CheckSignalState(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_SAT_CheckSignalState() \n");
						DEMOD_RETURN_FAIL(__F__);
					}

					pDemodInfo->bNotifiedLock	= TRUE;
					pDemodInfo->bNotifiedUnlock	= FALSE;

				}
				else
				{
//					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
//					DEMOD_PRINT( "^R^[DEMOD E60] LX_DEMOD_SYNC_CHECKING : Going back to LX_DEMOD_SYNC_CHECKING..... **;\n");
				}
	   		}
			break;

		case LX_DEMOD_SIGNAL_LOCKED:
			break;

		default:
			pDemodInfo->controlState = LX_DEMOD_TUNE_START;
			break;

	}
	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBS_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_LOCK_STATE_T			lockState;
	LX_DEMOD_OPER_MODE_T 			operMode;

	if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount 	= 0;
		pDemodInfo->unLockLongCount	= 0;


		if (RET_OK != _DEMOD_E60_LGDBB_SAT_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_SAT_CheckSignalState() \n");
			DEMOD_RETURN_FAIL(__F__);
		}

		operMode = pDemodInfo->signalStatus.operMode;

		if(operMode == LX_DEMOD_DVBS2)
		{
			pDemodInfo->operMode						= LX_DEMOD_DVBS2;
			pDemodInfo->setCfgParam.dvbs2.tuneMode		= pDemodInfo->setCfgParam.dvbs.tuneMode;
			pDemodInfo->setCfgParam.dvbs2.symbolRate	= pDemodInfo->setCfgParam.dvbs.symbolRate;

			DEMOD_PRINT("[DEMOD_CHIP] FAIL, forcely changed to DVBS2 mode \n");
			DEMOD_PRINT("[DEMOD_CHIP] tuneMode(DVBS2)  = %d \n", pDemodInfo->setCfgParam.dvbs2.tuneMode);
		}
		else if (operMode != LX_DEMOD_DVBS)
		{
			DEMOD_PRINT("[DEMOD_CHIP] FAIL, Invaild operation mode !! \n");
			return RET_ERROR;
		}

		if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)	&& (TRUE != pDemodInfo->bNotifiedLock))
		{
			pDemodInfo->lockCount++;

		}
		if(pDemodInfo->lockCount == 2)
		{
			pDemodInfo->lockStatus				= LX_DEMOD_LOCKED;
			pDemodInfo->bNotifiedLock			= TRUE;
			pDemodInfo->bNotifiedUnlock 			= FALSE;
			pDemodInfo->signalStatus.bSignalValid 		= TRUE;
			pDemodInfo->lockCount 				= 0;

			DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBS_FRONT_END_LOCKED..... ^0^\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
			{
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
			}
		}

		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}
	else
	{
		pDemodInfo->lockCount = 0;

		if(pauseTimeDemod != LX_DEMOD_LOCK_FAIL_PAUSE_TIME )
		{
			pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;
		}

		if((LX_DEMOD_UNLOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedUnlock))
		{
			pDemodInfo->unLockCount++;

			if(pDemodInfo->unLockCount == UNLOCKCOUNT)
			{
				pDemodInfo->lockStatus 				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 		= FALSE;
				pDemodInfo->unLockCount 			= 0;
				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBS_FRONT_END_NOT_LOCKED by UnlockCount\n");
			}
		}
	}
	return RET_OK;
}

#if 0
#endif
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS2_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS2_Set_Config_auto (BOOLEAN bAutoDetect)
{
	DEMOD_INFO("deprecated\n");
/*
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_E60_GetContext();

	if(bAutoDetect == TRUE)
	{
		if(DEMOD_L2_DVB_AutoModeDetectOn(pFrontend))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_DVB_AutoModeDetectOn() \n");
			return RET_ERROR;;
		}
	}
	else
	{

		if(DEMOD_L2_DVB_AutoModeDetectOff(pFrontend))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_DVB_AutoModeDetectOff() \n");
			return RET_ERROR;;
		}
	}
*/
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS2_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_E60_DVBS_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBS_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS2_Set_FullConfig (LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS2_Get_CoderRate
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS2_Get_CoderRate (LX_DEMOD_CODERATE_T *pCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	switch(signalStatus.codeRate)
	{
		case 0x03 :
			*pCodeRate = LX_DEMOD_CODE_1_4;
			break;
		case 0x01:
			*pCodeRate = LX_DEMOD_CODE_1_3;
			break;
		case 0x05 :
			*pCodeRate = LX_DEMOD_CODE_2_5;
			break;
		case 0x00:
			*pCodeRate = LX_DEMOD_CODE_1_2;
			break;
		case 0x06:
			*pCodeRate = LX_DEMOD_CODE_3_5;
			break;
		case 0x02:
			*pCodeRate = LX_DEMOD_CODE_2_3;
			break;
		case 0x04:
			*pCodeRate = LX_DEMOD_CODE_3_4;
			break;
		case 0x07:
			*pCodeRate = LX_DEMOD_CODE_4_5;
			break;
		case 0x08:
			*pCodeRate = LX_DEMOD_CODE_5_6;
			break;
		case 0x0A:
			*pCodeRate = LX_DEMOD_CODE_8_9;
			break;
		case 0x0b:
			*pCodeRate = LX_DEMOD_CODE_9_10;
			break;
		default :
			*pCodeRate = LX_DEMOD_CODE_UNKNOWN;
			break;
	}
	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS2_Get_Pilot
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS2_Get_Pilot (BOOLEAN *pPilot)
{
	*pPilot = FALSE;
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS2_Get_SymbolRate
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS2_Get_SymbolRate (UINT32 *pSymbolRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();
	*pSymbolRate = LX_DEMOD_CODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	*pSymbolRate = signalStatus.sym_rate;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS2_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBS2_Get_TotalInfo (void)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	UINT16 			ifagcValue = 0;
	UINT32 			errorCount;
	SINT32 			FreqOff;
	LX_DEMOD_LOCK_STATE_T 	agcLockStatus;
	LX_DEMOD_LOCK_STATE_T 	neverLockStatus;
	LX_DEMOD_LOCK_STATE_T 	spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 	spectrumInv;
	LX_DEMOD_MSE_T 		sigMse;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}


	if (RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_AGC_LOCK, &agcLockStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		agcLockStatus = LX_DEMOD_UNKOWN_STATE;
	}
	if(LX_DEMOD_LOCKED == agcLockStatus)
	{
		ifagcValue = signalStatus.if_agc;
	}

	if (RET_OK != DEMOD_E60_Get_NeverLockStatus(LX_DEMOD_DVBS2, &neverLockStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_NeverLockStatus() \n");
		neverLockStatus = LX_DEMOD_UNKOWN_STATE;
	}

	if (RET_OK !=  DEMOD_E60_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_SpectrumStatus() \n");
		spectrumInv = LX_DEMOD_UNKOWN_STATE;
	}

	errorCount = signalStatus.packetError;
	DEMOD_PRINT("[DEMOD_CHIP] TP Error Count= %d\n",errorCount);

	FreqOff = signalStatus.offsetFrq_Hz/1000;
	DEMOD_PRINT("[DEMOD_CHIP] Frequency Offset = %d\n",FreqOff);

	sigMse.bMse = 0;
	sigMse.mse = signalStatus.mse_info;
	sigMse.constPwr = signalStatus.constPwr;

//	DEMOD_PRINT("[DEMOD E60] AGC LOCK is %s \n",(agcLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD_CHIP] IF AGC value = %d(0x%x)\n",ifagcValue,ifagcValue);
	DEMOD_PRINT("[DEMOD_CHIP] Neverlock is %s\n",(neverLockStatus == LX_DEMOD_DETECTED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD_CHIP] Spectrum auto = %s, Inversion  = %s\n",(spectrumAuto == LX_DEMOD_AUTO) ? " Auto" : " Manual",
																					(spectrumInv == LX_DEMOD_INVERSION) ? " Inverted" : " Normal" );
	DEMOD_PRINT("[DEMOD_CHIP] offset = %d [KHz]\n",FreqOff);
	DEMOD_PRINT("[DEMOD_CHIP] mse = %d, constPwr = %d\n",sigMse.mse, sigMse.constPwr);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS2_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBS2_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	static LX_DEMOD_FLAG_T 		scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	lockState = LX_DEMOD_UNLOCKED;
	static unsigned int 		sigStablestartTime = 0;
	LX_DEMOD_OPER_MODE_T 		operMode;
	unsigned int 			elapsedTime	= 0;

	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{
				if(RET_OK != _DEMOD_E60_LGDBB_DVBS2_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVBS2_SetDemod() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if ( pDemodInfo->setCfgParam.dvbs2.symbolRate <= 2000) //2000 is 2MHz
				{
					notifyinglockTimeOut = LX_DEMOD_LOCK_DEALY_10000;
				}
				else
				{
					notifyinglockTimeOut = LX_DEMOD_LOCK_DEALY_5000;
				}

				if(pDemodInfo->setCfgParam.dvbs.operatingMode == LX_DEMOD_DVBS_BLIND_SCAN_MODE)
				{
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START : Blind Spectrum Mode..Going to LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK..... ^0^\n");
					break;
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbs.tuneMode)
				{
					if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
			}

			break;
		/***************************************************/
		/***** Configure demod for scan mode. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_SCAN:
			{
				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{

					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "[DEMOD_CHIP] Already Done\n");
					DEMOD_PRINT( "[DEMOD_CHIP]  LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == lockState))
				{
					if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode() \n");
						DEMOD_RETURN_FAIL(__F__);

					}
					DEMOD_PRINT("[DEMOD_CHIP] OperMode = 0x%x\n", operMode);

					if(LX_DEMOD_DVBS == operMode)
					{
						pDemodInfo->operMode		= LX_DEMOD_DVBS;
						pDemodInfo->scanJobFlag		= LX_DEMOD_FLAG_FINISH;
						pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING; //LX_DEMOD_RETUNE_RF;
						pDemodInfo->setCfgParam.dvbs.tuneMode = pDemodInfo->setCfgParam.dvbs2.tuneMode;
						DEMOD_PRINT( "[DEMOD_CHIP] Signal is Found (operMode = LX_DEMOD_DVBS) \n");
						DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					}
					else //(LX_DEMOD_DVBS2 == operMode)
					{
						pDemodInfo->operMode		= LX_DEMOD_DVBS2;
						pDemodInfo->scanJobFlag		= LX_DEMOD_FLAG_FINISH;
						pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;

						DEMOD_PRINT( "[DEMOD_CHIP] Signal is Found (operMode = LX_DEMOD_DVBS2)\n");
						DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					}


				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == lockState))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					elapsedTime 			= jiffies_to_msecs(jiffies) - g_NewTuneReqeustTime;

					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : MSG_DVBS_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;
					DEMOD_PRINT( "[DEMOD_CHIP] Signal is NOT Found \n");
				}
				else
				{
					pDemodInfo->scanJobFlag		= LX_DEMOD_FLAG_ING;
//					DEMOD_PRINT( "[DEMOD_CHIP] Detection is on processing \n");
				}

			}
			break;

		/***************************************************/
		/***** Attempting to finish the tuning state machine *****/
		/***************************************************/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK :
			{

			}
			break;

		/********************************************/
		/***** Attempting to obtain synch lock *****/
		/***************************************************/
		case LX_DEMOD_SYNC_CHECKING :
			{
				if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING : operMode = 0x%x\n", operMode);

				if(LX_DEMOD_DVBS == operMode)
				{
					pDemodInfo->operMode 		= LX_DEMOD_DVBS;
					pDemodInfo->setCfgParam.dvbs.tuneMode = pDemodInfo->setCfgParam.dvbs2.tuneMode;
					pDemodInfo->setCfgParam.dvbs.symbolRate = pDemodInfo->setCfgParam.dvbs2.symbolRate;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING(DVBS2) : Going to LX_DEMOD_SYNC_CHECKING(DVBS forcely)..... ^0^\n");

					return RET_OK;
				}

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 		= jiffies_to_msecs(jiffies);
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
				 	/* nothing to do so far */
				}
			}
		   break;

	   	/********************************************/
	   	/***** Attempting to obtain signal stability *****/
		/***************************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				SINT32 freqOffset;

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					if (LX_DEMOD_TUNE_NORMAL == pDemodInfo->setCfgParam.dvbs2.tuneMode)
					{
						elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;

						if(elapsedTime < LX_DEMOD_DVBS_SIG_STABLE_WAIT_TIMEOUT)
						{
							break;
						}
						else
						{
							pDemodInfo->bNotifiedLock		= TRUE;
							pDemodInfo->bNotifiedUnlock		= FALSE;
							pDemodInfo->lockStatus			= LX_DEMOD_LOCKED;
							pDemodInfo->signalStatus.bSignalValid 	= TRUE;

							if(RET_OK != DEMOD_E60_Get_CarrierFreqOffset(&freqOffset))
							{
								DEMOD_ERROR("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_CarrierFreqOffset() \n");
								return RET_ERROR;
							}

							pDemodInfo->freqOffset		= freqOffset;
							pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;
							elapsedTime			= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

							DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : MSG_DVBS_FRONT_END_LOCKED\n");
							DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms]\n", elapsedTime);
							DEMOD_PRINT("[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz]\n", freqOffset);
						}
					}
					else
					{
						pDemodInfo->bNotifiedLock		= TRUE;
						pDemodInfo->bNotifiedUnlock 		= FALSE;
						pDemodInfo->lockStatus			= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid 	= TRUE;

						if (RET_OK != DEMOD_E60_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_CarrierFreqOffset() \n");
							DEMOD_RETURN_FAIL(__F__);
						}

						pDemodInfo->signalStatus.bSignalValid 	= TRUE;
						pDemodInfo->freqOffset 			= freqOffset;
						pDemodInfo->controlState		= LX_DEMOD_SIGNAL_LOCKED;
						elapsedTime 				= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : MSG_DVBS_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);
					}

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_signal_status() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				else
				{
				}
	   		}
			break;
		case LX_DEMOD_SIGNAL_LOCKED:	break;

		default: pDemodInfo->controlState = LX_DEMOD_TUNE_START; break;

	}
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBS2_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBS2_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_LOCK_STATE_T			lockState;
	LX_DEMOD_OPER_MODE_T 			operMode;

	if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount 		= 0;
		pDemodInfo->unLockLongCount	= 0;

		if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_signal_status() \n");
			DEMOD_RETURN_FAIL(__F__);
		}

		operMode = pDemodInfo->signalStatus.operMode;

		if(operMode == LX_DEMOD_DVBS)
		{
			pDemodInfo->operMode 			= LX_DEMOD_DVBS;
			pDemodInfo->setCfgParam.dvbs.tuneMode 	= pDemodInfo->setCfgParam.dvbs2.tuneMode;
			pDemodInfo->setCfgParam.dvbs.symbolRate = pDemodInfo->setCfgParam.dvbs2.symbolRate;

			DEMOD_PRINT("[DEMOD_CHIP] FAIL, forcely changed to DVBS mode \n");
			DEMOD_PRINT("[DEMOD_CHIP] tuneMode (DVBS)  = %d \n", pDemodInfo->setCfgParam.dvbs.tuneMode);
		}
		else if (operMode != LX_DEMOD_DVBS2)
		{
			DEMOD_PRINT("[DEMOD_CHIP] FAIL, Invaild operation mode !! \n");
			return RET_ERROR;
		}

		if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus) && (TRUE != pDemodInfo->bNotifiedLock))
		{
			pDemodInfo->lockCount++;
		}

		if(pDemodInfo->lockCount == 2)
		{
			pDemodInfo->lockStatus			= LX_DEMOD_LOCKED;
			pDemodInfo->bNotifiedLock		= TRUE;
			pDemodInfo->bNotifiedUnlock 		= FALSE;
			pDemodInfo->signalStatus.bSignalValid 	= TRUE;
			pDemodInfo->lockCount 			= 0;

			DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MONITORING FUNC : MSG_DVBS2_FRONT_END_LOCKED by LockCount\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
			{
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
			}
		}

		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
			DEMOD_RETURN_FAIL(__F__);
		}

	}
	else
	{
		pDemodInfo->lockCount = 0;

		if(pauseTimeDemod != LX_DEMOD_LOCK_FAIL_PAUSE_TIME )
		{
			pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;
		}

		if((LX_DEMOD_UNLOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedUnlock))
		{
			pDemodInfo->unLockCount++;

			if(pDemodInfo->unLockCount == UNLOCKCOUNT)
			{
				pDemodInfo->lockStatus 			= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 		= TRUE;
				pDemodInfo->bNotifiedLock		= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;
				pDemodInfo->unLockCount 		= 0;

				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MONITORING FUNC : MSG_DVBS_FRONT_END_NOT_LOCKED by UnlockCount\n");
			}
		}
	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBSX_BlindScan_Init
 * Notification Blind Scan Init on DVB-S/S2.
 *
 * @param None
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_E60_DVBSX_BlindScan_Init (LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T *initFreq)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	DEMOD_PRINT("[DEMOD_CHIP] DEMOD_E60_DVBSX_BlindScan_Init startFreqKhz : %d, endFreqKhz : %d\n", initFreq->startFreqKhz, initFreq->endFreqKhz);

	DEMOD_L2_SAT_Blind_Init(pFrontend, initFreq->startFreqKhz, initFreq->endFreqKhz);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBSX_BlindScan_End
 * Notification Blind Scan Init on DVB-S/S2.
 *
 * @param None
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_E60_DVBSX_BlindScan_End (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	DEMOD_L2_SAT_Blind_End(pFrontend);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBSX_Get_TunerFreq
 * Get Tuner Freq infomration on DVB-S/S2.
 *
 * @param LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_E60_DVBSX_Get_TunerFreq (LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T *freqInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	DEMOD_L2_SAT_Blind_Info(pFrontend);

	freqInfo->TunerCenterFreqKhz	= pFrontend->demod->rsp->dd_sigsrch_info.center_idx;
	freqInfo->TunerCutOffFreqKhz	= pFrontend->demod->rsp->dd_sigsrch_info.bw_idx;

	DEMOD_PRINT("[DEMOD_CHIP] CenterFreq= %d , BandWidth = %d \n",freqInfo->TunerCenterFreqKhz, freqInfo->TunerCutOffFreqKhz);
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBSX_Get_OffsetFreq
 * Get Tuner Freq infomration on DVB-S/S2.
 *
 * @param SINT32* freqOff
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_E60_DVBSX_Get_OffsetFreq (LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T *pOffsetInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	DEMOD_L2_SAT_Blind_FoundInfo(pFrontend);

	pOffsetInfo->SymbolRateKhz 	= pFrontend->demod->rsp->blind_foundinfo.symrate;
	pOffsetInfo->FreqMhz 		= pFrontend->demod->rsp->blind_foundinfo.center;

	DEMOD_PRINT("[DEMOD_CHIP] Frequency = %d , BandWidth = %d \n", pOffsetInfo->FreqMhz, pOffsetInfo->SymbolRateKhz);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBSX_SymbolRate_Detec
 * Notification Blind Scan Init on DVB-S/S2.
 *
 * @param None
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_E60_DVBSX_SymbolRate_Detec (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	int retc = RET_ERROR;

	DEMOD_PRINT("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	retc = DEMOD_L2_SAT_Blind_SymbolRate_Detect(pFrontend);

	return retc;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBSX_BlindLock_Loop
 * Notification Blind Scan Init on DVB-S/S2.
 *
 * @param None
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_E60_DVBSX_BlindLock_Loop (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	int retc = RET_ERROR;

	DEMOD_PRINT("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	if( DEMOD_L2_Check_BlindLock_loop(pFrontend,DEMOD_DD_MODE_PROP_MODULATION_DVBS))
	{
		retc = RET_OK;
	}

	return retc;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBSX_Get_Nextfreq_Status
 * Get Tuner Freq infomration on DVB-S/S2.
 *
 * @param SINT32* freqOff
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_E60_DVBSX_Get_Nextfreq_Status (BOOLEAN* pBlindScanEnd)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	DEMOD_L2_SAT_Blind_Status(pFrontend);

	if(pFrontend->demod->rsp->blind_status.blindStatus == 2)
	{
		*pBlindScanEnd = TRUE;
	}
	else
	{
		*pBlindScanEnd = FALSE;
	}

	DEMOD_PRINT("[DEMOD_CHIP] pBlindScanEnd = %d \n", *pBlindScanEnd);

	return RET_OK;
}
#if 0
#endif


