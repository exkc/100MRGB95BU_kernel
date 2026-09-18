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
#include "demod_common_m19.h"
#include "demod_sat_m19.h"


#if 0
#endif
#define	UNLOCKCOUNT								10

/***********************************************************************************
	Global Type Definitions
 ************************************************************************************/
extern LX_DEMOD_L2_Context gM19_LGDBB_Frontend;

/***********************************************************************************
	Static Variable & Function Prototypes Declarations
 ************************************************************************************/



#if 0
#endif

int _DEMOD_M19_DVBS_CheckTuneMode(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbs.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;

		default:			
		{
			printk("[_DEMOD_M19_DVBS_CheckTuneMode] ///// CheckTuneMode tuneMode = %x ///// \n", pDemodInfo->setCfgParam.dvbs.tuneMode);	//woohyung
			return DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		}
	}
	return new_tuneMode;
}

int _DEMOD_M19_DVBS2_CheckTuneMode(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbs2.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;

		default:
		{
			printk("[M19 _DEMOD_M19_DVBS2_CheckTuneMode] ///// CheckTuneMode tuneMode = %x ///// \n", pDemodInfo->setCfgParam.dvbs2.tuneMode);	//woohyung
			return DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		}
	}
	return new_tuneMode;
}

int _DEMOD_M19_DVBS_OperatingMode(DEMOD_CTX_T *pDemodInfo)
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

int _DEMOD_M19_DVBS2_OperatingMode(DEMOD_CTX_T *pDemodInfo)
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


int _DEMOD_M19_LGDBB_DVBS_SetDemod(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  					standard;
	UINT32 					freq_Khz;
//	UINT16 					dvb_s_bandwidth_Khz;
	UINT16 					symbol_rate_Kbps = 0 ;
	UINT8  					operatingMode;
	UINT8  					new_tuneMode;
	LX_DEMOD_L2_Context 	*pFrontend;
	
	printk("[M19 LGDBB]  SetDemod DVBS \n");

	pFrontend				= &gM19_LGDBB_Frontend;
	standard 					= DEMOD_DD_MODE_PROP_MODULATION_DVBS;
	new_tuneMode 			= _DEMOD_M19_DVBS_CheckTuneMode(pDemodInfo);
	operatingMode 			= _DEMOD_M19_DVBS_OperatingMode(pDemodInfo);
	symbol_rate_Kbps 			= (UINT16)(pDemodInfo->setCfgParam.dvbs.symbolRate);// KSym/s
	freq_Khz 					= pDemodInfo->setCfgParam.dvbs.frequency;

	printk("[M19 _DEMOD_M19_LGDBB_DVBS_SetDemod] ///// tuneMode = %x ///// \n", new_tuneMode);	//woohyung
	printk("[M19 _DEMOD_M19_LGDBB_DVBS_SetDemod] ///// operatingMode = %x ///// \n", operatingMode);	//woohyung

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
int _DEMOD_M19_LGDBB_DVBS2_SetDemod(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  					standard;
	UINT32 					freq_Khz;
//	UINT16 					dvb_s2_bandwidth_Khz;
	UINT16 					symbol_rate_Kbps = 0 ;
	UINT8  					operatingMode;
	UINT8  					new_tuneMode;
	LX_DEMOD_L2_Context 	*pFrontend;
	
	printk("[M19 LGDBB]  SetDemod DVBS2 \n");

	pFrontend				= &gM19_LGDBB_Frontend;
	standard 					= DEMOD_DD_MODE_PROP_MODULATION_DVBS2;
	new_tuneMode 			= _DEMOD_M19_DVBS2_CheckTuneMode(pDemodInfo);
	operatingMode 			= _DEMOD_M19_DVBS2_OperatingMode(pDemodInfo);
	symbol_rate_Kbps 			= (UINT16)(pDemodInfo->setCfgParam.dvbs2.symbolRate);// KSym/s
	freq_Khz 					= pDemodInfo->setCfgParam.dvbs2.frequency;

	printk("[M19 _DEMOD_M19_LGDBB_DVBS2_SetDemod] ///// tuneMode = %x ///// \n", new_tuneMode);	//woohyung
	printk("[M19 _DEMOD_M19_LGDBB_DVBS2_SetDemod] ///// operatingMode = %x ///// \n", operatingMode);	//woohyung

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


int _DEMOD_M19_LGDBB_SAT_CheckSignalState(DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gM19_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;;
	}

	#if 0
	printk("[op_mode: %d]\n"		, signalStatus.operatingMode);
	printk("[if_agc: %d]\n"			, signalStatus.if_agc);
	printk("[mse_info: %d]\n"		,signalStatus.mse_info);
	printk("[snr: %d]\n"			,signalStatus.snr);
	printk("[dl: %d]\n"				, signalStatus.demodLock);
	printk("[ber: %d]\n"			, signalStatus.ber);
	printk("[pe: %d]\n"			, signalStatus.packetError);
	printk("[afc_freq: %d]\n"		, signalStatus.offsetFrq_Hz);
	printk("[constellation: %d]\n"	, signalStatus.constellation);
	printk("[sp_inv: %d]\n"			,signalStatus.spInv);
	printk("[constPwr: %d]\n"			,signalStatus.constPwr);
	printk("[[M16PP] packet error : %d]\n"			, signalStatus.packetError);
	#endif


	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber			= signalStatus.ber;
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse		= signalStatus.mse_info;
	pDemodInfo->signalStatus.m.constPwr	= signalStatus.constPwr;
	pDemodInfo->freqOffset 				= signalStatus.offsetFrq_Hz / 1000;
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
 * DEMOD_M19_DVBS_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS_Set_Config_auto (BOOLEAN bAutoDetect)
{
/*
	LX_DEMOD_L2_Context *pFrontend;

	pFrontend = &gM19_LGDBB_Frontend;

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
 * DEMOD_M19_DVBS_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_M19_DVBS_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBS_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS_Set_FullConfig (LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS_Get_CoderRate
 * Get the information of code rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gM19_LGDBB_Frontend;
	
	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
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

	DEMOD_PRINT("(%s) pCodeRate = %d \n", __F__, *pCodeRate);

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS_Get_SymbolRate
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS_Get_SymbolRate( UINT32 *pSymbolRate )
{

	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend		= &gM19_LGDBB_Frontend;
	
	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		DEMOD_RETURN_FAIL(__F__);
	}

	*pSymbolRate = signalStatus.sym_rate;

	DEMOD_PRINT("(%s) pSymbolRate = %d \n", __F__, *pSymbolRate);
		
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS_Get_TotalInfo( void)
{
	UINT16 						ifagcValue = 0;
	UINT32 						errorCount;
	SINT32 						FreqOff;
	UINT32 						symbolRate;
	LX_DEMOD_LOCK_STATE_T 		agcLockStatus;
	LX_DEMOD_LOCK_STATE_T 		neverLockStatus;
	LX_DEMOD_LOCK_STATE_T 		spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 		spectrumInv;
	LX_DEMOD_CODERATE_T 		codeRate;
	LX_DEMOD_MSE_T 				sigMse;
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;
	
	pFrontend = &gM19_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;
	}
	
	DEMOD_PRINT("^p^[DEMOD M19] @ %s =====\n",__F__);

	if (RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_AGC_LOCK, &agcLockStatus))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
		agcLockStatus = LX_DEMOD_UNKOWN_STATE;
	}
	if(LX_DEMOD_LOCKED == agcLockStatus)
	{
		ifagcValue = signalStatus.if_agc;
		DEMOD_PRINT("(%s) IF AGC = 0x%x \n", __F__, ifagcValue);
/*		
		if (RET_OK != DEMOD_M19_Get_IFAGC(&ifagcValue))
		{
			DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_IFAGC() !!!\n", __F__, __L__);
			ifagcValue = 0;
		}
*/
	}

	if (RET_OK != DEMOD_M19_Get_NeverLockStatus(LX_DEMOD_DVBS, &neverLockStatus))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_DVB_Get_NeverLockStatus() !!!\n", __F__, __L__);
		neverLockStatus = LX_DEMOD_UNKOWN_STATE;
	}

	if (RET_OK !=  DEMOD_M19_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_SpectrumStatus() !!!\n", __F__, __L__);
		spectrumInv = LX_DEMOD_UNKOWN_STATE;
	}

	//TP Error count
/*
	if (RET_OK !=  DEMOD_M19_Get_Packet_Error(&errorCount))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_DVBS_Get_TPError() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
*/
	errorCount 		= signalStatus.packetError;
	
	DEMOD_PRINT("[DEMOD M19] TP Error Count= %d !!!\n",errorCount);
/*
	if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset( &FreqOff ))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
		FreqOff = 0xffff;
	}
*/
	FreqOff 			= signalStatus.offsetFrq_Hz/1000;
/*
	if (RET_OK != DEMOD_M19_Get_MseInfo(&sigMse))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_DVBC_Get_SNR() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
*/
	sigMse.bMse 		= 0;
	sigMse.mse 		= signalStatus.mse_info;
	sigMse.constPwr 	= signalStatus.constPwr;

	DEMOD_PRINT("[DEMOD M19] AGC LOCK is %s !!!\n",(agcLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD M19] IF AGC value = %d(0x%x) !!!\n",ifagcValue,ifagcValue);
	DEMOD_PRINT("[DEMOD M19] Neverlock is %s !!!\n",(neverLockStatus == LX_DEMOD_DETECTED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD M19] Spectrum auto = %s, Inversion  = %s !!!\n",(spectrumAuto == LX_DEMOD_AUTO) ? " Auto" : " Manual",
																					(spectrumInv == LX_DEMOD_INVERSION) ? " Inverted" : " Normal" );
	DEMOD_PRINT("[DEMOD M19] offset = %d [KHz]!!!\n",FreqOff);
	DEMOD_PRINT("[DEMOD M19] mse = %d, constPwr = %d, !!!\n",sigMse.mse, sigMse.constPwr);

/*	if (RET_OK != DEMOD_M19_DVBS_Get_CoderRate(&codeRate ))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_DVBS_Get_CoderRate() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
*/
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

/*	if (RET_OK != DEMOD_M19_DVBS_Get_SymbolRate(&symbolRate ))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_DVBS_Get_SymbolRate() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
*/
	symbolRate = signalStatus.sym_rate;

#ifndef  DEMOD_PRINT

	printk("[DEMOD M19] AGC LOCK is %s !!!\n",(agcLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	printk("[DEMOD M19] IF AGC value = %d !!!\n",ifagcValue);
	printk("[DEMOD M19] Neverlock is %s !!!\n",(neverLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	printk("[DEMOD M19] Spectrum mode = %s !!!\n",(spectrumInv == LX_DEMOD_NORMAL) ? " Normal" :
																	(spectrumInv == LX_DEMOD_INVERSION) ? "Inversion" : 	" Unknown");
	printk("[DEMOD M19] Code rate = %d !!!\n",codeRate);
	printk("[DEMOD M19] Symbol rate = %d !!!\n",symbolRate);


	printk("[DEMOD M19] TP Error Count= %d !!!\n",errorCount);
	printk("[DEMOD M19] MSE = %d, constPwr = %d !!!\n",sigMse.mse, sigMse.constPwr);
#endif

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS_Set_DiseqcToneMessageCtrl
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS_Set_DiseqcToneMessageCtrl( LX_DEMOD_DVBS_DiSEqC_MSG_T *pDiseqcMsg)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	
	pFrontend = &gM19_LGDBB_Frontend;

	if (DEMOD_L2_SAT_send_diseqc_sequence(pFrontend, pDiseqcMsg->sequence_length, pDiseqcMsg->sequenceBuffer, pDiseqcMsg->cont_tone, pDiseqcMsg->tone_burst,pDiseqcMsg->burst_sel, pDiseqcMsg->end_seq))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SAT_send_diseqc_sequence() \n", __F__);
		return RET_ERROR;
	}
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS_Get_BlindInfo
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS_Get_BlindInfo(UINT32 centerFreq, LX_DEMOD_DVBS_BLIND_PARAM_T *pBlindParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_DVBS_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	static LX_DEMOD_FLAG_T 			scanProcessing 		= LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock 			= LX_DEMOD_UNLOCKED;
	static unsigned int 					sigStablestartTime 	= 0;
	LX_DEMOD_OPER_MODE_T 			operMode;

	switch (pDemodInfo->controlState)
	{
											/***************************************************/
											/***** Configure tuner for desired channel No. *****/
		case LX_DEMOD_TUNE_START:			/***************************************************/
			{

				if(RET_OK != _DEMOD_M19_LGDBB_DVBS_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD M19 LGDBB] FAIL (%s:%d) _DEMOD_M19_LGDBB_DVBT_SetDemod() !!!\n", __F__, __L__);
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
					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_TUNE_START : Blind Spectrum Mode..Going to LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK..... ^0^\n");
					break;
				}
				
				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbs.tuneMode)
				{

					if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");

				}
				else
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_TUNE_START : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
			}
			break;
											/***************************************************/
											/***** Configure demod for scan mode. *****/
		case LX_DEMOD_TUNE_SCAN:			/***************************************************/
			{
				unsigned int currentTime 	= 0;
				unsigned int elapsedTime 	= 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "^c^[DEMOD M19] ERR (%s:%d) Already Done !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					if(RET_OK != DEMOD_M19_Get_OperMode(&operMode))
					{
						DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);

					}
					DEMOD_PRINT("[DEMOD M19] (%s:%d) operMode(%d) !!!\n", __F__, __L__,operMode);
					if(LX_DEMOD_DVBS2 == operMode)
					{
						pDemodInfo->operMode 						= LX_DEMOD_DVBS2;
						pDemodInfo->scanJobFlag 					= LX_DEMOD_FLAG_FINISH;
						pDemodInfo->controlState 					= LX_DEMOD_SYNC_CHECKING; //LX_DEMOD_RETUNE_RF;
						pDemodInfo->setCfgParam.dvbs2.tuneMode 		= pDemodInfo->setCfgParam.dvbs.tuneMode;
						pDemodInfo->setCfgParam.dvbs2.symbolRate 	= pDemodInfo->setCfgParam.dvbs.symbolRate;

						DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Signal is Found (LX_DEMOD_DVBS2)  !!!\n", __F__, __L__);
						DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					}
					else //(LX_DEMOD_DVBS == operMode)
					{
						pDemodInfo->operMode 	= LX_DEMOD_DVBS;
						pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
						pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

						DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Signal is Found (LX_DEMOD_DVBS)  !!!\n", __F__, __L__);
						DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					}
				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					currentTime 					= jiffies_to_msecs(jiffies);
					elapsedTime 					= currentTime - g_NewTuneReqeustTime;

					DEMOD_PRINT_ALWAYS("\nLX_DEMOD_TUNE_SCAN : MSG_DVBS_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;
					DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Signal is NOT Found  !!!\n", __F__, __L__);
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
					DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Detection is on processing	!!!\n", __F__, __L__);
				}
			}
			break;
													/********************************************/
													/***** Attempting to finish the tuning state machine *****/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK : 	/********************************************/
			{

			}
			break;
											/********************************************/
											/***** Attempting to obtain synch lock *****/
		case LX_DEMOD_SYNC_CHECKING : 		/********************************************/
			{
				LX_DEMOD_LOCK_STATE_T	lockState;
//				BOOLEAN reacqflagOn;

				if(RET_OK != DEMOD_M19_Get_OperMode(&operMode))
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_OperMode() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);

				}
				DEMOD_PRINT("[DEMOD M19] LX_DEMOD_SYNC_CHECKING() operMode = 0x%x!!!\n", operMode);

				if(LX_DEMOD_DVBS2 == operMode)
				{
					pDemodInfo->operMode 						= LX_DEMOD_DVBS2;
					pDemodInfo->setCfgParam.dvbs2.tuneMode 		= pDemodInfo->setCfgParam.dvbs.tuneMode;
					pDemodInfo->setCfgParam.dvbs2.symbolRate 	= pDemodInfo->setCfgParam.dvbs.symbolRate;

					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SYNC_CHECKING(DVBS) : Going to LX_DEMOD_SYNC_CHECKING(DVBS2 forcely)..... ^0^\n");

					return RET_OK;
				}

				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 				= jiffies_to_msecs(jiffies);

					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
				 	/* nothing to do so far */

				}
			}
		   break;
										   	/********************************************/
										   	/***** Attempting to obtain signal stability *****/
	   	case LX_DEMOD_SIGNAL_STABLE: 		/********************************************/
			{
				LX_DEMOD_LOCK_STATE_T			lockState;
				SINT32							freqOffset;
				unsigned int 					elapsedTime;
//				UINT32 							packetError;

				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->lockStatus				= LX_DEMOD_LOCKED;
					pDemodInfo->signalStatus.bSignalValid 	= TRUE;

					if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
					{
						DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->freqOffset 		= freqOffset;
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_LOCKED;
					pDemodInfo->bNotifiedLock	= TRUE;
					pDemodInfo->bNotifiedUnlock	= FALSE;
					elapsedTime 					= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : MSG_DVBS_FRONT_END_LOCKED..... ^^^0^^^\n");
					DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);
					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);


					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != _DEMOD_M19_LGDBB_SAT_CheckSignalState(pDemodInfo))
					{
						DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}

					pDemodInfo->bNotifiedLock	= TRUE;
					pDemodInfo->bNotifiedUnlock	= FALSE;

				}
				else
				{
//					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
//					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SYNC_CHECKING : Going back to LX_DEMOD_SYNC_CHECKING..... **;\n");
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
 * DEMOD_M19_DVBS_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_DVBS_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_LOCK_STATE_T			lockState;
	LX_DEMOD_OPER_MODE_T 			operMode;

	if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_Get_Lock() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
	
#if 1
	DEMOD_PRINT( " [DEMOD_M19_DVBS_Monitoring_Signal_Lock]pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedLock = %d, (lockCount = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedLock,pDemodInfo->lockCount);
	DEMOD_PRINT( " [DEMOD_M19_DVBS_Monitoring_Signal_Lock]pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedUnlock = %d,(unlockCnt = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedUnlock,pDemodInfo->unLockCount);
	DEMOD_PRINT( " [DEMOD_M19_DVBS_Monitoring_Signal_Lock]lockState = %d) \n",lockState);
#endif

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount 		= 0;
		pDemodInfo->unLockLongCount	= 0;

/*		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
		{
			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
		}
*/		
		if (RET_OK != _DEMOD_M19_LGDBB_SAT_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
/*
		if(RET_OK != DEMOD_M19_Get_OperMode(&operMode))
		{
			DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_OperMode() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
*/
		operMode = pDemodInfo->signalStatus.operMode;
		
		if((operMode == LX_DEMOD_DVBS) || (operMode == LX_DEMOD_DVBS2))
		{
			if(operMode != LX_DEMOD_DVBS)
			{
				pDemodInfo->operMode 						= LX_DEMOD_DVBS2;
				pDemodInfo->setCfgParam.dvbs2.tuneMode 		= pDemodInfo->setCfgParam.dvbs.tuneMode;
				pDemodInfo->setCfgParam.dvbs2.symbolRate 	= pDemodInfo->setCfgParam.dvbs.symbolRate;
				
				DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) forcely changed to DVBS2 mode \n",__F__, __L__);
				DEMOD_PRINT("[DEMOD M19] (%s:%d) tuneMode(DVBS2)  = %d \n",__F__, __L__, pDemodInfo->setCfgParam.dvbs2.tuneMode);
			}

		}
		else
		{
			DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) Invaild operation mode !! \n",__F__, __L__);
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
			pDemodInfo->signalStatus.bSignalValid 	= TRUE;			
			pDemodInfo->lockCount 				= 0;

			DEMOD_PRINT_ALWAYS( "[DEMOD M19] MONITORING FUNC : MSG_DVBS_FRONT_END_LOCKED..... ^0^\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
			{
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
			}
		}

		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
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
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;				
				pDemodInfo->unLockCount 			= 0;
				DEMOD_PRINT_ALWAYS( "[DEMOD M19] MONITORING FUNC : MSG_DVBS_FRONT_END_NOT_LOCKED..... -_-\n");
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
 * DEMOD_M19_DVBS2_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS2_Set_Config_auto (BOOLEAN bAutoDetect)
{
	LX_DEMOD_L2_Context 	*pFrontend;

	pFrontend = &gM19_LGDBB_Frontend;

	if(bAutoDetect == TRUE)
	{
		if(DEMOD_L2_DVB_AutoModeDetectOn(pFrontend))
		{
			DEMOD_PRINT("(%s) FAIL, DEMOD_L2_DVB_AutoModeDetectOn \n", __F__);
			return RET_ERROR;;
		}
	}
	else
	{

		if(DEMOD_L2_DVB_AutoModeDetectOff(pFrontend))
		{
			DEMOD_PRINT("(%s) FAIL, DEMOD_L2_DVB_AutoModeDetectOff \n", __F__);
			return RET_ERROR;;
		}
	}
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS2_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_M19_DVBS_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBS_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS2_Set_FullConfig (LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS2_Get_CoderRate
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS2_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate )
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend		= &gM19_LGDBB_Frontend;

	DEMOD_PRINT("[DEMOD M19] @ %s =====\n",__F__);

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
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
 * DEMOD_M19_DVBS2_Get_Pilot
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS2_Get_Pilot( BOOLEAN *pPilot )
{
	*pPilot = FALSE;
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS2_Get_SymbolRate
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS2_Get_SymbolRate( UINT32 *pSymbolRate )
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend		= &gM19_LGDBB_Frontend;
	*pSymbolRate 	= LX_DEMOD_CODE_UNKNOWN;
	
	DEMOD_PRINT("[DEMOD M19] @ %s =====\n",__F__);

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		DEMOD_RETURN_FAIL(__F__);
	}

	*pSymbolRate = signalStatus.sym_rate;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS2_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_DVBS2_Get_TotalInfo( void)
{
	UINT16 						ifagcValue = 0;
	UINT32 						errorCount;
	SINT32 						FreqOff;
	LX_DEMOD_LOCK_STATE_T 		agcLockStatus;
	LX_DEMOD_LOCK_STATE_T 		neverLockStatus;
	LX_DEMOD_LOCK_STATE_T 		spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 		spectrumInv;
	LX_DEMOD_MSE_T 			sigMse;
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gM19_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;
	}

	DEMOD_PRINT("^p^[DEMOD M19 DTV] @ %s =====\n",__F__);

	if (RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_AGC_LOCK, &agcLockStatus))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
		agcLockStatus = LX_DEMOD_UNKOWN_STATE;
	}
	if(LX_DEMOD_LOCKED == agcLockStatus)
	{
/*
		if (RET_OK != DEMOD_M19_Get_IFAGC(&ifagcValue))
		{
			DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_IFAGC() !!!\n", __F__, __L__);
			ifagcValue = 0;
		}
*/
		ifagcValue 	= signalStatus.if_agc;
	}

	if (RET_OK != DEMOD_M19_Get_NeverLockStatus(LX_DEMOD_DVBS2, &neverLockStatus))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_DVB_Get_NeverLockStatus() !!!\n", __F__, __L__);
		neverLockStatus = LX_DEMOD_UNKOWN_STATE;
	}

	if (RET_OK !=  DEMOD_M19_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_SpectrumStatus() !!!\n", __F__, __L__);
		spectrumInv = LX_DEMOD_UNKOWN_STATE;
	}

/*
	if (RET_OK !=  DEMOD_M19_Get_Packet_Error(&errorCount))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Packet_Error() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
*/
	errorCount 		= signalStatus.packetError;
	DEMOD_PRINT("[DEMOD M19] TP Error Count= %d !!!\n",errorCount);
/*
	if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset( &FreqOff ))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
		FreqOff = 0xffff;
	}
*/
	FreqOff 			= signalStatus.offsetFrq_Hz/1000;	
	DEMOD_PRINT("[DEMOD M19] Frequency Offset = %d !!!\n",FreqOff);
/*
	if (RET_OK != DEMOD_M19_Get_MseInfo(&sigMse))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_MseInfo() !!!\n", __F__, __L__);
		return RET_ERROR;
	}
*/
	sigMse.bMse 		= 0;
	sigMse.mse 		= signalStatus.mse_info;
	sigMse.constPwr 	= signalStatus.constPwr;

//	DEMOD_PRINT("[DEMOD M19] AGC LOCK is %s !!!\n",(agcLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD M19_%s] IF AGC value = %d(0x%x) !!!\n",__F__,ifagcValue,ifagcValue);
	DEMOD_PRINT("[DEMOD M19_%s] Neverlock is %s !!!\n",__F__,(neverLockStatus == LX_DEMOD_DETECTED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD M19_%s] Spectrum auto = %s, Inversion  = %s !!!\n",__F__,(spectrumAuto == LX_DEMOD_AUTO) ? " Auto" : " Manual",
																					(spectrumInv == LX_DEMOD_INVERSION) ? " Inverted" : " Normal" );
	DEMOD_PRINT("[DEMOD M19_%s] offset = %d [KHz]!!!\n",__F__,FreqOff);
	DEMOD_PRINT("[DEMOD M19_%s] mse = %d, constPwr = %d, !!!\n",__F__,sigMse.mse, sigMse.constPwr);


#ifndef  DEMOD_PRINT
	printk("[DEMOD M19_%s] IF AGC value = %d !!!\n",__F__,ifagcValue);
	printk("[DEMOD M19_%s] Neverlock is %s !!!\n",__F__,(neverLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	printk("[DEMOD M19_%s] Spectrum mode = %s !!!\n",__F__,(spectrumInv == LX_DEMOD_NORMAL) ? " Normal" :
																	(spectrumInv == LX_DEMOD_INVERSION) ? "Inversion" : 	" Unknown");

	printk("[DEMOD M19_%s] TP Error Count= %d !!!\n",__F__,errorCount);
	printk("[DEMOD M19_%s] MSE = %d, constPwr = %d !!!\n",__F__,sigMse.mse, sigMse.constPwr);
#endif

	return RET_OK;
}

int DEMOD_M19_DVBS2_Set_MemSconfig(void)
{

	LX_DEMOD_L2_Context 	*pFrontend;
	UINT32					tdi_st_mem;
	UINT32					djb_st_mem;

	pFrontend 				= &gM19_LGDBB_Frontend;
	tdi_st_mem 				= gMemCfgDEMOD_DVB_TDI.memory_base;
	djb_st_mem 				= gMemCfgDEMOD_DVB_DJB.memory_base;
	
	if(tdi_st_mem == 0 || djb_st_mem == 0)
	{
		printk("######[DEMOD M19_%s] Error M19 DEMOD DVB_S2 Wrong Memory Base Address ##### !!!!!!!!!!!!!!!!!!!!!!!\n",__F__);
	}
	else
	{
		printk("######[DEMOD M19_%s] first call DEMOD_M19_DVBS2_Set_MemSconfig TDI_addr[0x%x] , DJB_addr[0x%x] ##### !!!!!!\n", __F__,tdi_st_mem, djb_st_mem );
		if(RET_OK != DEMOD_L2_DVBT2_Set_BaseAddr_AXI(pFrontend, tdi_st_mem, djb_st_mem ))
		{
			printk("[DEMOD] FAIL (%s:%d) DEMOD_L2_DVBT2_Set_BaseAddr_AXI() !!!\n", __F__, __L__);
			return RET_ERROR;
		}
	}
	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBS2_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_DVBS2_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	static LX_DEMOD_FLAG_T 			scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock = LX_DEMOD_UNLOCKED;
	static unsigned int 					sigStablestartTime = 0;
	LX_DEMOD_OPER_MODE_T 			operMode;

	switch (pDemodInfo->controlState)
	{

											/***************************************************/
											/***** Configure tuner for desired channel No. *****/
		case LX_DEMOD_TUNE_START:			/***************************************************/
			{
				if(RET_OK != _DEMOD_M19_LGDBB_DVBS2_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD M19 LGDBB] FAIL (%s:%d) _DEMOD_M19_LGDBB_DVBT_SetDemod() !!!\n", __F__, __L__);
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
					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_TUNE_START : Blind Spectrum Mode..Going to LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK..... ^0^\n");
					break;		
				}
				
				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbs.tuneMode)
				{
					if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;
					
					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_TUNE_START : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
			}

			break;
											/***************************************************/
											/***** Configure demod for scan mode. *****/
		case LX_DEMOD_TUNE_SCAN:			/***************************************************/
			{

				unsigned int currentTime	= 0;
				unsigned int elapsedTime	= 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{

					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "^c^[DEMOD M19] ERR (%s:%d) Already Done !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					if(RET_OK != DEMOD_M19_Get_OperMode(&operMode))
					{
						DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_OperMode() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);

					}
					DEMOD_PRINT("[DEMOD M19] DEMOD_M19_NeverlockScan() operMode = 0x%x!!!\n", operMode);

					if(LX_DEMOD_DVBS == operMode)
					{
						pDemodInfo->operMode 					= LX_DEMOD_DVBS;
						pDemodInfo->scanJobFlag 				= LX_DEMOD_FLAG_FINISH;
						pDemodInfo->controlState 				= LX_DEMOD_SYNC_CHECKING; //LX_DEMOD_RETUNE_RF;
						pDemodInfo->setCfgParam.dvbs.tuneMode 	= pDemodInfo->setCfgParam.dvbs2.tuneMode;
						DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Signal is Found (operMode = LX_DEMOD_DVBS  !!!\n", __F__, __L__);
						DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					}
					else //(LX_DEMOD_DVBS2 == operMode)
					{
						pDemodInfo->operMode 	= LX_DEMOD_DVBS2;
						pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
						pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

						DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Signal is Found (operMode = LX_DEMOD_DVBS2  !!!\n", __F__, __L__);
						DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					}


				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					currentTime 					= jiffies_to_msecs(jiffies);
					elapsedTime 					= currentTime - g_NewTuneReqeustTime;

					DEMOD_PRINT_ALWAYS("\nLX_DEMOD_TUNE_SCAN : MSG_DVBS_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;
					DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Signal is NOT Found  !!!\n", __F__, __L__);
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
					DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Detection is on processing	!!!\n", __F__, __L__);
				}

			}
			break;
													/********************************************/
													/***** Attempting to finish the tuning state machine *****/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK : 	/********************************************/
			{

			}
			break;
											/********************************************/
											/***** Attempting to obtain synch lock *****/
		case LX_DEMOD_SYNC_CHECKING : 		/********************************************/
			{

				LX_DEMOD_LOCK_STATE_T	lockState;
//				BOOLEAN reacqflagOn;
				
				if(RET_OK != DEMOD_M19_Get_OperMode(&operMode))
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_OperMode() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD M19] LX_DEMOD_SYNC_CHECKING() operMode = 0x%x!!!\n", operMode);

				if(LX_DEMOD_DVBS == operMode)
				{
					pDemodInfo->operMode 					= LX_DEMOD_DVBS;
					pDemodInfo->setCfgParam.dvbs.tuneMode 	= pDemodInfo->setCfgParam.dvbs2.tuneMode;
					pDemodInfo->setCfgParam.dvbs.symbolRate 	= pDemodInfo->setCfgParam.dvbs2.symbolRate;

					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SYNC_CHECKING(DVBS2) : Going to LX_DEMOD_SYNC_CHECKING(DVBS forcely)..... ^0^\n");

					return RET_OK;
				}

				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 				= jiffies_to_msecs(jiffies);
					DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
				 	/* nothing to do so far */
				}
			}
		   break;
										   	/********************************************/
										   	/***** Attempting to obtain signal stability *****/
	   	case LX_DEMOD_SIGNAL_STABLE: 		/********************************************/
			{
				LX_DEMOD_LOCK_STATE_T			lockState;
				SINT32							freqOffset;
				unsigned int 					elapsedTime;
				UINT32 							packetError;
//				BOOLEAN 						reacqflagOn;


				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
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
							if(RET_OK != DEMOD_M19_Get_Packet_Error(&packetError))
							{
								DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Packet_Error() !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
							}
							else
							{
								if(1) //(packetError < LX_DEMOD_PACKET_ERROR_THD)
								{
									pDemodInfo->bNotifiedLock			= TRUE;
									pDemodInfo->bNotifiedUnlock			= FALSE;
									pDemodInfo->lockStatus				= LX_DEMOD_LOCKED;
									pDemodInfo->signalStatus.bSignalValid 	= TRUE;

									if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
									{
										DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
										DEMOD_RETURN_FAIL(__F__);
									}
									
									pDemodInfo->freqOffset 		= freqOffset;
									pDemodInfo->controlState		= LX_DEMOD_SIGNAL_LOCKED;
									elapsedTime 					= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

									DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : MSG_DVBS_FRONT_END_LOCKED..... ^^^0^^^\n");
									DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);
									DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);
								}
								else
								{
									DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Packet error = %d .....  --_--\n", packetError);
									elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;
									if(elapsedTime > LX_DEMOD_LOCK_DEALY_100)
									{
										pDemodInfo->bNotifiedLock			= TRUE;
										pDemodInfo->bNotifiedUnlock 			= FALSE;
										pDemodInfo->lockStatus				= LX_DEMOD_LOCKED;
										pDemodInfo->signalStatus.bSignalValid 	= TRUE;

										if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
										{
											DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
											DEMOD_RETURN_FAIL(__F__);
										}
										pDemodInfo->freqOffset 	= freqOffset;
										pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;
										elapsedTime 				= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

										DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : MSG_DVBS_FRONT_END_LOCKED..... ^^0^^\n");
										DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^0^^\n", elapsedTime);
										DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^0^^\n", freqOffset);

									}

								}

							}

						}
					}
					else
					{
						pDemodInfo->bNotifiedLock				= TRUE;
						pDemodInfo->bNotifiedUnlock 				= FALSE;
						pDemodInfo->lockStatus					= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid 		= TRUE;

						if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}
						if(RET_OK != DEMOD_M19_Get_Packet_Error(&packetError))
						{
							DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_Packet_Error() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}

						pDemodInfo->signalStatus.bSignalValid 		= TRUE;
						pDemodInfo->freqOffset 					= freqOffset;
						pDemodInfo->controlState					= LX_DEMOD_SIGNAL_LOCKED;
						elapsedTime 								= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : MSG_DVBS_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);
					}

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
					{
						DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
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
 * DEMOD_M19_DVBS2_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_DVBS2_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_LOCK_STATE_T			lockState;
	LX_DEMOD_OPER_MODE_T 			operMode;

	if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_Get_Lock() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
#if 1
	DEMOD_PRINT( " [%s] pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedLock = %d, (lockCount = %d) \n",__F__,pDemodInfo->lockStatus,pDemodInfo->bNotifiedLock,pDemodInfo->lockCount);
	DEMOD_PRINT( " [%s] pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedUnlock = %d,(unlockCnt = %d) \n",__F__,pDemodInfo->lockStatus,pDemodInfo->bNotifiedUnlock,pDemodInfo->unLockCount);
	DEMOD_PRINT( " [%s] lockState = %d) \n",__F__,lockState);
#endif
	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount 		= 0;
		pDemodInfo->unLockLongCount	= 0;

//		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
//			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
/*
		if(RET_OK != DEMOD_M19_Get_OperMode(&operMode))
		{
			DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_Get_OperMode() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
*/
		operMode = pDemodInfo->signalStatus.operMode;
		
		if((operMode == LX_DEMOD_DVBS) || (operMode == LX_DEMOD_DVBS2))
		{
			if(operMode != LX_DEMOD_DVBS2)
			{
				pDemodInfo->operMode 					= LX_DEMOD_DVBS;
				pDemodInfo->setCfgParam.dvbs.tuneMode 	= pDemodInfo->setCfgParam.dvbs2.tuneMode;
				pDemodInfo->setCfgParam.dvbs.symbolRate 	= pDemodInfo->setCfgParam.dvbs2.symbolRate;

				DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) forcely changed to DVBS mode \n",__F__, __L__);
				DEMOD_PRINT("[DEMOD M19] (%s:%d) tuneMode (DVBS)  = %d \n",__F__, __L__, pDemodInfo->setCfgParam.dvbs.tuneMode);
			}
		}
		else
		{
			DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) Invaild operation mode !! \n",__F__, __L__);
			return RET_ERROR;
		}

		if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)&& (TRUE != pDemodInfo->bNotifiedLock))
		{
			pDemodInfo->lockCount++;
		}
		
		if(pDemodInfo->lockCount == 2)
		{
			pDemodInfo->lockStatus				= LX_DEMOD_LOCKED;
			pDemodInfo->bNotifiedLock			= TRUE;
			pDemodInfo->bNotifiedUnlock 			= FALSE;
			pDemodInfo->signalStatus.bSignalValid 	= TRUE;			
			pDemodInfo->lockCount 				= 0;

			DEMOD_PRINT_ALWAYS( "[DEMOD M19] MONITORING FUNC : MSG_DVBS_FRONT_END_LOCKED..... ^0^\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
			{
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
			}
		}
		
		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
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
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;				
				pDemodInfo->unLockCount 			= 0;
				
				DEMOD_PRINT_ALWAYS( "[DEMOD M19] MONITORING FUNC : MSG_DVBS_FRONT_END_NOT_LOCKED..... -_-\n");
			}
		}
	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBSX_BlindScan_Init
 * Notification Blind Scan Init on DVB-S/S2.
 *
 * @param None
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_M19_DVBSX_BlindScan_Init(LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T *initFreq)
{
	LX_DEMOD_L2_Context *pFrontend;

	DEMOD_PRINT("[DEMOD M19] DEMOD_M19_DVBSX_BlindScan_Init");

	pFrontend = &gM19_LGDBB_Frontend;

	DEMOD_PRINT("[DEMOD M19] DEMOD_M19_DVBSX_BlindScan_Init startFreqKhz : %d, endFreqKhz : %d", initFreq->startFreqKhz, initFreq->endFreqKhz);
	
	DEMOD_L2_SAT_Blind_Init(pFrontend, initFreq->startFreqKhz, initFreq->endFreqKhz);
	
	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBSX_BlindScan_End
 * Notification Blind Scan Init on DVB-S/S2.
 *
 * @param None
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_M19_DVBSX_BlindScan_End(void)
{
	LX_DEMOD_L2_Context *pFrontend;

	DEMOD_PRINT("[DEMOD M19] DEMOD_M19_DVBSX_BlindScan_End");

	pFrontend = &gM19_LGDBB_Frontend;
	
	DEMOD_L2_SAT_Blind_End(pFrontend);
	
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBSX_Get_TunerFreq
 * Get Tuner Freq infomration on DVB-S/S2.
 *
 * @param LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_M19_DVBSX_Get_TunerFreq(LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T *freqInfo)
{
	LX_DEMOD_L2_Context *pFrontend;

	DEMOD_PRINT("[DEMOD M19] DEMOD_M19_DVBSX_Get_TunerFreq");

	pFrontend = &gM19_LGDBB_Frontend;
	
	DEMOD_L2_SAT_Blind_Info(pFrontend);

	freqInfo->TunerCenterFreqKhz	= pFrontend->demod->rsp->dd_sigsrch_info.center_idx;
	freqInfo->TunerCutOffFreqKhz	= pFrontend->demod->rsp->dd_sigsrch_info.bw_idx;

	DEMOD_PRINT("[DEMOD_M19_DVBSX_Get_TunerFreq] CenterFreq= %d , BandWidth = %d \n",freqInfo->TunerCenterFreqKhz, freqInfo->TunerCutOffFreqKhz);
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBSX_Get_OffsetFreq
 * Get Tuner Freq infomration on DVB-S/S2.
 *
 * @param SINT32* freqOff
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_M19_DVBSX_Get_OffsetFreq(LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T *pOffsetInfo)
{
	LX_DEMOD_L2_Context *pFrontend;

	DEMOD_PRINT("[DEMOD M19] DEMOD_M19_DVBSX_Get_OffsetFreq");

	pFrontend = &gM19_LGDBB_Frontend;
	
	DEMOD_L2_SAT_Blind_FoundInfo(pFrontend);

	pOffsetInfo->SymbolRateKhz = pFrontend->demod->rsp->blind_foundinfo.symrate;
	pOffsetInfo->FreqMhz = pFrontend->demod->rsp->blind_foundinfo.center;

	DEMOD_PRINT("[DEMOD BlindScan DEMOD_M19_DVBSX_Get_OffsetFreq] Frequency = %d \n", pOffsetInfo->FreqMhz);
	DEMOD_PRINT("[DEMOD BlindScan DEMOD_M19_DVBSX_Get_OffsetFreq] BandWidth = %d \n", pOffsetInfo->SymbolRateKhz);
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBSX_SymbolRate_Detec
 * Notification Blind Scan Init on DVB-S/S2.
 *
 * @param None
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_M19_DVBSX_SymbolRate_Detec(void)
{	
	UINT8 return_code = RET_ERROR;

	LX_DEMOD_L2_Context *pFrontend;

	DEMOD_PRINT("[DEMOD M19] DEMOD_M19_DVBSX_SymbolRate_Detec");

	pFrontend = &gM19_LGDBB_Frontend;
	
	return_code = DEMOD_L2_SAT_Blind_SymbolRate_Detect(pFrontend);
	
	return return_code;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBSX_BlindLock_Loop
 * Notification Blind Scan Init on DVB-S/S2.
 *
 * @param None
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_M19_DVBSX_BlindLock_Loop(void)
{	
	UINT8 return_code = RET_ERROR;

	LX_DEMOD_L2_Context *pFrontend;

	DEMOD_PRINT("[DEMOD M19] DEMOD_M19_DVBSX_BlindLock_Loop");

	pFrontend = &gM19_LGDBB_Frontend;
	
	if( DEMOD_L2_Check_BlindLock_loop(pFrontend,DEMOD_DD_MODE_PROP_MODULATION_DVBS))
	{
		return_code = RET_OK;
	}
	
	return return_code;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_DVBSX_Get_Nextfreq_Status
 * Get Tuner Freq infomration on DVB-S/S2.
 *
 * @param SINT32* freqOff
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_M19_DVBSX_Get_Nextfreq_Status(BOOLEAN* pBlindScanEnd)
{
	LX_DEMOD_L2_Context *pFrontend;

	DEMOD_PRINT("[DEMOD M19] DEMOD_M19_DVBSX_Get_Nextfreq_Status");

	pFrontend = &gM19_LGDBB_Frontend;
	
	DEMOD_L2_SAT_Blind_Status(pFrontend); 

	if(pFrontend->demod->rsp->blind_status.blindStatus == 2)
	{
		*pBlindScanEnd = TRUE; 
	}
	else
	{
		*pBlindScanEnd = FALSE; 
	}

	DEMOD_PRINT("[DEMOD M19 BlindScan DEMOD_M19_DVBSX_Get_Nextfreq_Status] pBlindScanEnd = %d \n", *pBlindScanEnd);
	
	return RET_OK;
}
#if 0
#endif


