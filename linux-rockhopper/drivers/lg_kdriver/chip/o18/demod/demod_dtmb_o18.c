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


#include "demod_impl.h"
#include "demod_common_o18.h"
#include "demod_dtmb_o18.h"

#if 0
#endif

/***********************************************************************************
	Global Type Definitions
 ************************************************************************************/

extern LX_DEMOD_L2_Context	gO18_LGDBB_Frontend;
static UINT16 					gO18GBB_FullDTMBPkerrCount 				= 12;
static UINT16 					gO18GBB_FullDTMBPkerrThreshold 			= 255;
static UINT16					gO18GBB_DTMB_UnlockCount_full_packeterr	= 0;

/***********************************************************************************
	Static Variable & Function Prototypes Declarations
 ************************************************************************************/
int _DEMOD_O18_DTMB_CheckTuneMode(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dtmb.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL;		break;
		case	LX_DEMOD_TUNE_AUTO: 					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO;		break;
		case	LX_DEMOD_TUNE_MANUAL:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL;		break;
		case	LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA: 	new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA;	break;

		default:						return DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; 									break;
	}

	return new_tuneMode;
}

int _DEMOD_O18_LGDBB_DTMB_SetDemod(DEMOD_CTX_T *pDemodInfo)
{

	UINT8  					standard;
	UINT32 					freq_Khz;
	UINT16 					dtmb_bandwidth_Khz;
	UINT8  					tuneMode;
	LX_DEMOD_L2_Context 	*pFrontend;

	pFrontend				= &gO18_LGDBB_Frontend;
	standard 					= DEMOD_DD_MODE_PROP_MODULATION_DTMB;
	freq_Khz 					= 0;
	tuneMode 				= _DEMOD_O18_DTMB_CheckTuneMode(pDemodInfo);

	if(RET_OK != DEMOD_O18_Get_BW(pDemodInfo, &dtmb_bandwidth_Khz))
	{
		DEMOD_PRINT("[DEMOD O18 DBB] FAIL (%s:%d) DEMOD_O18_Get_BW !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_L2_DTMB_Set_demod(pFrontend,
								standard,
								freq_Khz,
								tuneMode,
								DEMOD_DD_MODE_PROP_SPECINV_MANUAL,
								DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
								dtmb_bandwidth_Khz); 

	return RET_OK;

}

int _DEMOD_O18_LGDBB_DTMB_CheckSignalState(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend = &gO18_LGDBB_Frontend;

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
	#endif
	DEMOD_PRINT("[%s] packet error : %d\n",__F__, signalStatus.packetError);

	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber			= signalStatus.ber;
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse		= signalStatus.mse_info;
	pDemodInfo->signalStatus.m.constPwr	= signalStatus.constPwr;
	pDemodInfo->freqOffset 				= signalStatus.offsetFrq_Hz / 1000;
	pDemodInfo->signalStatus.operMode 	= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode		= pDemodInfo->systemMode;

	return RET_OK;

}

#if 0
#endif

int DEMOD_O18_DTMB_SW_Init(void)
{
	LX_DEMOD_L2_Context *pFrontend;

	pFrontend = &gO18_LGDBB_Frontend;

//	if(DEMOD_L2_DTMB_SW_Init(pFrontend, 0x26) != NO_DEMOD_ERROR)   // CPBOX
	if(DEMOD_L2_DTMB_SW_Init(pFrontend, 0xb2) != NO_DEMOD_ERROR)     // SOC
	{
		printk("[O18 LGDBB] (%s:%d) DEMOD_O18_DTMB_SW_Init  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	printk("##########DEMOD_O18_DTMB_SW_Init##########\n");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_DTMB_Get_CarrierMode
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CARRIERMODE_T - carrier mode : signal , multi
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/
int DEMOD_O18_DTMB_Get_CarrierMode( LX_DEMOD_CARRIERMODE_T *pCarrierMode )
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend		= &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		DEMOD_RETURN_FAIL(__F__);
	}

	*pCarrierMode = LX_DEMOD_CARRIER_UNKNOWN;

	switch(signalStatus.carr_mode)
	{
		case DEMOD_DD_DTMB_STATUS_RESPONSE_CARR_MODE_SC :
			*pCarrierMode = LX_DEMOD_CARRIER_SINGLE;
			break;
		case DEMOD_DD_DTMB_STATUS_RESPONSE_CARR_MODE_MC :
			*pCarrierMode = LX_DEMOD_CARRIER_MULTI;
			break;
		default :
			*pCarrierMode = LX_DEMOD_CARRIER_UNKNOWN;
			break;
	}
	
	DEMOD_PRINT("(%s) signalStatus.carr_mode : 0x%02x \n", __F__,signalStatus.carr_mode);
	return RET_OK;

}

int DEMOD_O18_DTMB_Get_Time_Interval( BOOLEAN *pbM720)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend		= &gO18_LGDBB_Frontend;


	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		DEMOD_RETURN_FAIL(__F__);
	}

	*pbM720 = FALSE;

	DEMOD_PRINT("(%s) Time Interval : 0x%02x \n", __F__,signalStatus.il_mode);

	if(signalStatus.il_mode == DEMOD_DD_DTMB_STATUS_RESPONSE_IL_MODE_720) *pbM720 = TRUE;

	return RET_OK;

}

int DEMOD_O18_DTMB_Get_Pn_Mode( LX_DEMOD_PNMODE_T *pPnMode )
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend		= &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		DEMOD_RETURN_FAIL(__F__);
	}

	*pPnMode = LX_DEMOD_TPS_GUARD_UNKNOWN;
	
//	DEMOD_PRINT("(%s) signalStatus.pn_const : 0x%02x \n", __F__,signalStatus.pn_const);
//	DEMOD_PRINT("(%s) signalStatus.pn_mode : 0x%02x \n", __F__,signalStatus.pn_mode);

 	if(signalStatus.pn_const == DEMOD_DD_DTMB_STATUS_RESPONSE_PN_CONST_CONSTANT)
 	{
		switch(signalStatus.pn_mode)
		{
			case DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_PN420 :
				*pPnMode = LX_DEMOD_TPS_GUARD_420_C;
				break;
			case DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_PN595 :
				*pPnMode = LX_DEMOD_TPS_GUARD_595;
				break;
			case DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_PN945 :
				*pPnMode = LX_DEMOD_TPS_GUARD_945_C;
				break;
			default :
				*pPnMode = LX_DEMOD_TPS_GUARD_UNKNOWN;
				break;
		}
	}
	else
	{
		switch(signalStatus.pn_mode)
		{
			case DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_PN420 :
				*pPnMode = LX_DEMOD_TPS_GUARD_420_V;
				break;
			case DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_PN595 :
				*pPnMode = LX_DEMOD_TPS_GUARD_595;
				break;
			case DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_PN945 :
				*pPnMode = LX_DEMOD_TPS_GUARD_945_V;
				break;
			default :
				*pPnMode = LX_DEMOD_TPS_GUARD_UNKNOWN;
				break;
		}
	}
	return RET_OK;

}

int DEMOD_O18_DTMB_Get_CodeRate( LX_DEMOD_CODERATE_T *pCodeRate )
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend		= &gO18_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		DEMOD_RETURN_FAIL(__F__);
	}

	*pCodeRate = LX_DEMOD_CODE_UNKNOWN;

//	DEMOD_PRINT("(%s) signalStatus.codeRate : 0x%02x \n", __F__,signalStatus.codeRate);

	switch(signalStatus.codeRate)
	{
		case DEMOD_DD_STATUS_RESPONSE_CODERATE_2_5:
			*pCodeRate = LX_DEMOD_CODE_2_5;
			break;
		case DEMOD_DD_STATUS_RESPONSE_CODERATE_3_5:
			*pCodeRate = LX_DEMOD_CODE_3_5;
			break;
		case DEMOD_DD_STATUS_RESPONSE_CODERATE_4_5:
			*pCodeRate = LX_DEMOD_CODE_4_5;
			break;
		default :
			*pCodeRate = LX_DEMOD_CODE_UNKNOWN;
			break;
	}
	return RET_OK;

}

int DEMOD_O18_DTMB_Get_Constellation( LX_DEMOD_RF_MODE_T *pConstellation)
{
	LX_DEMOD_L2_Context 		*pFrontend;
	LX_DEMOD_L2_SIG_STATUS		signalStatus;

	pFrontend		= &gO18_LGDBB_Frontend;

	*pConstellation = LX_DEMOD_UNKOWN_MODE;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		DEMOD_RETURN_FAIL(__F__);
	}

//	DEMOD_PRINT("(%s) signalStatus.constellation : 0x%02x \n", __F__,signalStatus.constellation);

	switch(signalStatus.constellation)
	{
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4NR :
			*pConstellation = LX_DEMOD_4QAM_NR;
			break;
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4:
			*pConstellation = LX_DEMOD_4QAM;
			break;
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16:
			*pConstellation = LX_DEMOD_16QAM;
			break;		
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32:
			*pConstellation = LX_DEMOD_32QAM;
			break;
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64:
			*pConstellation = LX_DEMOD_64QAM;
			break;
		default :
			*pConstellation = LX_DEMOD_UNKOWN_MODE;
			break;
	}
	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_DTMB_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O18_DTMB_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
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
				if(RET_OK != _DEMOD_O18_LGDBB_DTMB_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD O18 LGDBB] FAIL (%s:%d) _DEMOD_O18_LGDBB_DTMB_SetDemod() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dtmb.tuneMode)
				{

					if(RET_OK != DEMOD_O18_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_PRINT("[DEMOD O18 GBB] FAIL (%s:%d) DEMOD_O18_NeverlockScan() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState 			= LX_DEMOD_TUNE_SCAN;
					gO18GBB_FullDTMBPkerrThreshold 	= 255;
					gO18GBB_FullDTMBPkerrCount 		= 9;
					
					DEMOD_PRINT( "^R^[DEMOD O18 GBB] LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 			= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 			= LX_DEMOD_SYNC_CHECKING;
					gO18GBB_FullDTMBPkerrThreshold 	= 300;
					gO18GBB_FullDTMBPkerrCount 		= 9;

					DEMOD_PRINT( "^R^[DEMOD O18 GBB] LX_DEMOD_TUNE_START : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
				gO18GBB_DTMB_UnlockCount_full_packeterr = 0;
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
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT( "^c^[DEMOD ] ERR (%s:%d) Already Done !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD ] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_O18_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_PRINT("[DEMOD ] FAIL (%s:%d) DEMOD_O18_NeverlockScan() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					pDemodInfo->operMode 		= LX_DEMOD_DTMB;
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "^G^[DEMOD ] (%s:%d) Signal is Found   !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD ] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

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

					DEMOD_PRINT_ALWAYS("\nLX_DEMOD_TUNE_SCAN : MSG_DTMB_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;
					DEMOD_PRINT( "^G^[DEMOD ] (%s:%d) Signal is NOT Found  !!!\n", __F__, __L__);
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
					DEMOD_PRINT( "^G^[DEMOD ] (%s:%d) Detection is on processing	!!!\n", __F__, __L__);
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

				if(RET_OK != DEMOD_O18_Get_OperMode(&operMode))
				{
					DEMOD_PRINT("[DEMOD ] FAIL (%s:%d) DEMOD_O18_Get_OperMode() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD ] LX_DEMOD_SYNC_CHECKING() operMode = 0x%x!!!\n", operMode);

				if(RET_OK != DEMOD_O18_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD ] FAIL (%s:%d) DEMOD_O18_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 				= jiffies_to_msecs(jiffies);
					DEMOD_PRINT( "^R^[DEMOD ] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
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

				if(RET_OK != DEMOD_O18_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD ] FAIL (%s:%d) DEMOD_O18_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->lockStatus				= LX_DEMOD_LOCKED;
					pDemodInfo->signalStatus.bSignalValid 	= TRUE;

					if (RET_OK != DEMOD_O18_Get_CarrierFreqOffset(&freqOffset))
					{
						DEMOD_PRINT( "^r^[DEMOD ] FAIL (%s:%d) DEMOD_O18_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->freqOffset = freqOffset;

					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

					elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_PRINT_ALWAYS( "[DEMOD ] LX_DEMOD_SIGNAL_STABLE : MSG_DTMB_FRONT_END_LOCKED..... ^^^0^^^\n");
					DEMOD_PRINT_ALWAYS( "[DEMOD ] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);
					DEMOD_PRINT( "^R^[DEMOD ] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT( "^r^[DEMOD ] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != _DEMOD_O18_LGDBB_DTMB_CheckSignalState(pDemodInfo))
					{
						DEMOD_PRINT( "^r^[DEMOD ] FAIL (%s:%d) _DEMOD_O18_LGDBB_DTMB_CheckSignalState() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					
					pDemodInfo->bNotifiedLock	= TRUE;
					pDemodInfo->bNotifiedUnlock	= FALSE;

				}
				else
				{
					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT( "^R^[DEMOD ] LX_DEMOD_SIGNAL_STABLE : Going back to LX_DEMOD_SYNC_CHECKING..... **;\n");
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
 * DEMOD_O18_DTMB_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O18_DTMB_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T			lockState;

	if(RET_OK != DEMOD_O18_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD O18 GBB] FAIL (%s:%d) DEMOD_Get_Lock() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount 		= 0;
		pDemodInfo->unLockLongCount	= 0;

		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
		{
			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
		}

		if (RET_OK != _DEMOD_O18_LGDBB_DTMB_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD O18 GBB] FAIL (%s:%d) _DEMOD_O18_LGDBB_DTMB_CheckSignalState() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
		
		if(pDemodInfo->signalStatus.packetError >= gO18GBB_FullDTMBPkerrThreshold)
		{
			gO18GBB_DTMB_UnlockCount_full_packeterr++;
			DEMOD_PRINT( "^r^[DEMOD O18 GBB](%s) gO18GBB_DTMB_UnlockCount_full_packeterr = %d !!!\n", __F__,gO18GBB_DTMB_UnlockCount_full_packeterr);

			if(gO18GBB_DTMB_UnlockCount_full_packeterr == gO18GBB_FullDTMBPkerrCount)
			{
				DEMOD_PRINT( "^r^[DEMOD O18 GBB] oops !! (%s) Force to NOT LOCK !!\n", __F__);


				if(RET_OK != DEMOD_O18_SoftwareReset())
				{
					DEMOD_PRINT("[DEMOD O18 GBB] FAIL (%s:%d) DEMOD_O18_SoftwareReset() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD O18 GBB](%s) DEMOD_O18_SoftwareReset() !!!\n", __F__);

				pDemodInfo->lockStatus						= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 					= TRUE;
				pDemodInfo->bNotifiedLock					= FALSE;
				pDemodInfo->signalStatus.bSignalValid 			= FALSE;				
				gO18GBB_DTMB_UnlockCount_full_packeterr 	= 0;
				DEMOD_PRINT_ALWAYS( "[DEMOD O18 GBB] MONITORING FUNC : MSG_DTMB_FRONT_END_NOT_LOCKED..... -_-;;\n");
			}
		}
		else
		{
			gO18GBB_DTMB_UnlockCount_full_packeterr = 0;

			if(pDemodInfo->bIsTPoutEn == TRUE)
			{
				if (RET_OK != DEMOD_O18_TPOutEnable(TRUE))
				{
					DEMOD_PRINT( "^r^[DEMOD O18 GBB] FAIL (%s:%d) DEMOD_O18_TPOutEnable(TRUE) !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedLock))
			{
				pDemodInfo->lockCount++;
			}

			if(pDemodInfo->lockCount == 2)
			{
				pDemodInfo->lockStatus 				= LX_DEMOD_LOCKED;
				pDemodInfo->bNotifiedLock 			= TRUE;
				pDemodInfo->bNotifiedUnlock 			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= TRUE;				
				pDemodInfo->lockCount 				= 0;

				DEMOD_PRINT_ALWAYS( "[DEMOD O18 GBB] MONITORING FUNC : MSG_DTMB_FRONT_END_LOCKED..... ^0^\n");

				if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				{
					pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
				}
			}

			if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
			{
				DEMOD_PRINT( "^r^[DEMOD O18 GBB] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
				DEMOD_RETURN_FAIL(__F__);
			}
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

			if(pDemodInfo->unLockCount == 4)
			{
				pDemodInfo->lockStatus 						= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock 					= FALSE;
				pDemodInfo->bNotifiedUnlock 					= TRUE;
				pDemodInfo->signalStatus.bSignalValid 			= FALSE;
				gO18GBB_DTMB_UnlockCount_full_packeterr 	= 0;				
				pDemodInfo->unLockCount 					= 0;

				DEMOD_PRINT_ALWAYS( "[DEMOD O18 GBB] MONITORING FUNC : MSG_DTMB_FRONT_END_NOT_LOCKED..... -_-\n");
			}
		}

	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O18_DTMB_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_DTMB_Set_Config_auto (BOOLEAN bAutoDetect)
{
	LX_DEMOD_L2_Context *pFrontend;

	pFrontend = &gO18_LGDBB_Frontend;
#if 0 // will be update. if needs
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
#endif
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 DEMOD_O18_DTMB_Set_PartialConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_O18_DVBT_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O18_DTMB_Set_PartialConfig (LX_DEMOD_DTMB_CONFIG_T *pDtmbConfigParam)
{
	UINT8 					return_code = NO_DEMOD_ERROR;
	LX_DEMOD_L2_Context 	*pFrontend;

	pFrontend = &gO18_LGDBB_Frontend;
#if 0
	return_code = DEMOD_L2_DVB_Set_PLP_Select(pFrontend,  plp_id, DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO);
	if(return_code != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("DEMOD_L2_DVB_Set_PLP_Select error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return RET_ERROR;
	}
	pFrontend->current_PLP_ID = plp_id;
	
	if(DEMOD_L2_DVB_AutoModeDetectOn(pFrontend))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_DVB_AutoModeDetectOn \n", __F__);
		return RET_ERROR;;
	}
#endif

	return return_code;

}
int DEMOD_O18_DTMB_Set_MemSconfig(void)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	UINT32					base_st_mem;

	pFrontend 				= &gO18_LGDBB_Frontend;
	base_st_mem 			= gMemCfgDEMOD_DTMB.memory_base;
	
	printk("######[DEMOD_O18_DTMB_Set_MemSconfig] first call DEMOD_O18_DTMB_Set_MemSconfig Base_addr[0x%x] ##### !!!!!!\n", base_st_mem );

	if(base_st_mem == 0)
	{
		printk("######[DEMOD_O18_DTMB_Set_MemSconfig] Error O18 DEMOD DTMB Wrong Memory Base Address ##### !!!!!!!!!!!!!!!!!!!!!!!\n");
		return RET_ERROR;
	}
	else
	{
		DEMOD_PRINT("######[DEMOD_O18_DTMB_Set_MemSconfig] first call DEMOD_O18_DTMB_Set_MemSconfig Base_addr[0x%x] ##### !!!!!!\n", base_st_mem );
		if(RET_OK != DEMOD_L2_DTMB_Set_BaseAddr_AXI(pFrontend, base_st_mem ))
		{
			printk("[DEMOD_O18_DTMB_Set_MemSconfig] FAIL DEMOD_L2_DTMB_Set_BaseAddr_AXI() !!!\n");
			return RET_ERROR;
		}
	}
	
	return RET_OK;

}
#if 0
#endif
